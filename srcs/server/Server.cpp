#include "Server.hpp"
#include "commands/CAP.hpp"
#include "commands/JOIN.hpp"
#include "commands/NICK.hpp"
// #include "commands/NAMES.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/PING.hpp"
// #include "commands/MODE.hpp"

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(string const &portString, string const &password) : _name("yobouhle.chat"), _sockfd(-1) {
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
	// _commands["MODE"] = new MODE();
}

Server::~Server() {
	for (commandIt it = _commands.begin(); it != _commands.end(); it++) {
		delete it->second;
	}
	for (clientIt it = _clients.begin(); it != _clients.end(); it++) {
		delete *it;
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
