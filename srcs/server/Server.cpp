#include <algorithm>
#include <unistd.h>

#include "Server.hpp"

#define RED		"\033[1;31m"
#define RESET	"\033[0m"

/**
 * @brief Creates a new Server object with the given port and password.
 *
 * @param portString the port number as a string
 * @param password the server password
 *
 * @throws runtime_error if the port is invalid or the password is empty
 */
Server::Server(string const &portString, string const &password) : _name("irc.yobouhle.chat"), _serverFd(-1) {
	if (portString.find_last_not_of("0123456789") != string::npos || atoi(portString.c_str()) < 1024 || atoi(portString.c_str()) > 65535)
		throw runtime_error("Invalid port");
	if (password.empty())
		throw runtime_error("Password empty");
	_port = atoi(portString.c_str());
	_password = password;
}

/**
 * @brief Destroys the Server object and closes all associated file descriptors.
 */
Server::~Server() {
	vector<Client*>	clients = _clients.getClients();

	cout << RED "Server shutting down..." RESET << endl;
	for (vector<Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
		_clients.deleteClient(*it);
	}
	clients.clear();
	close(_serverFd);
}

int	Server::getPort() const { return _port; }

int	Server::getSockfd() const { return _serverFd; }

string const	&Server::getName() const { return _name; }

ClientList	&Server::getClientsList() { return _clients; }

ChannelList	&Server::getChannelList() { return _channels; }

string	&Server::getPassword() { return _password; }

bool	&Server::getSignalReceived() const { return _signalReceived; }

Client	*Server::getClient(string const &nickname) const { return _clients.getClient(nickname); }

Client	*Server::getClient(int const &fd) const { return _clients.getClient(fd); }

Channel	*Server::getChannel(string const &name) const { return _channels.getChannel(name); }
