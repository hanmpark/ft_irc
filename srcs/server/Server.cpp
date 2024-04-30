#include "Server.hpp"

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(string const &portString, string const &password) : _name("irc.yobouhle.chat"), _serverFd(-1) {
	if (portString.find_last_not_of("0123456789") != string::npos || atoi(portString.c_str()) < 0 || atoi(portString.c_str()) > 65535) { // Check Range
		throw runtime_error("Invalid port\n");
	}
	if (password.empty()) {
		throw runtime_error("Password empty\n");
	}
	_port = atoi(portString.c_str());
	_password = password;
}

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
