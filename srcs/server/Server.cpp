#include "Server.hpp"
#include "commands/CAP.hpp"
#include "commands/JOIN.hpp"
#include "commands/NICK.hpp"
// #include "commands/NAMES.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/PING.hpp"
#include "commands/PRIVMSG.hpp"
// #include "commands/MODE.hpp"

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(string const &portString, string const &password) : _name("yobouhle"), _sockfd(-1) {
	if (portString.find_last_not_of("0123456789") != string::npos || atoi(portString.c_str()) < 0 || atoi(portString.c_str()) > 65535) { // Check Range
		throw runtime_error("Invalid port\n");
	}
	if (password.empty())
		throw runtime_error("Password empty\n");

	_port = atoi(portString.c_str());
	_password = password;
	_commands["CAP"] = new CAP();
	_commands["JOIN"] = new JOIN();
	_commands["NICK"] = new NICK();
	// _commands["NAMES"] = new NAMES();
	_commands["PASS"] = new PASS();
	_commands["USER"] = new USER();
	_commands["PING"] = new PING();
	// _commands["PONG"] = new PONG();
	_commands["PRIVMSG"] = new PRIVMSG();  
	// _commands["MODE"] = new MODE();
}

Server::~Server() {
	for (commandIt it = _commands.begin(); it != _commands.end(); it++) {
		if (it->second != NULL)
			delete it->second;
	}
	for (clientIt it = _clients.begin(); it != _clients.end(); it++) {
		if (*it != NULL)
			delete *it;
	}
	for (channelIt it = _channels.begin(); it != _channels.end(); it++) {
		if (it->second != NULL)
			delete it->second;
	}
	_commands.clear();
	_clients.clear();
	_channels.clear();
	_pollFds.clear();
}

int	Server::getPort() const { return _port; }

int	Server::getSockfd() const { return _sockfd; }

string const	&Server::getName() const { return _name; }

vector<Client*>	&Server::getClients() { return _clients; }

string	&Server::getPassword() { return _password; }

Channel	*Server::getChannelByName(string const &channel) {
	channelIt	it = _channels.find(channel);

	if (it == _channels.end())
		return NULL;
	return it->second;
}

void	Server::addChannel(string const &channelName, Channel *channel) {
	_channels[channelName] = channel;
}

void	Server::removeChannel(string const &channelName) {
	channelIt	it = _channels.find(channelName);

	if (it != _channels.end()) {
		delete it->second;
		_channels.erase(it);
	}
}

void	Server::sendPrivMessage(string const &nickname, string const &message, int fd) {
	Client	*client = getClientByNickname(nickname);

	if (client != NULL) {
		string	message = ":" + client->getNickname() + "!" \
						+ client->getUsername() + "@" \
						+ client->getHostname() + " PRIVMSG " \
						+ client->getNickname() + " :" + message + "\r\n";
		sendMessage(client->getFd(), message);
	}
	else {
		sendMessage(fd, IRCErrors::ERR_NOSUCHNICK(nickname));
	}
}

void	Server::broadcastMessage(string const &channelName, string const &message, int fd) {
	// iterate over the users/clients in the channel to send the messages.
	Channel	*channel = getChannelByName(channelName);
	if (channel != NULL) {
		vector<Client*>	users = channel->getUsers();
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i]->getFd() == fd) // skip the sender
				continue ;
			string	message = ":" + users[i]->getNickname() + "!" \
							+ users[i]->getUsername() + "@" \
							+ users[i]->getHostname() + " PRIVMSG " \
							+ channelName + " :" + message + "\r\n";
			sendMessage(users[i]->getFd(), message);
		}
	}
	else {
		sendMessage(fd, IRCErrors::ERR_CANNOTSENDTOCHAN(channelName));
	}
}

Client	*Server::getClientByNickname(string const &nickname) {
	clientIt	it = find(_clients.begin(), _clients.end(), nickname);

	if (it != _clients.end())
		return *it;
	return NULL;
}
