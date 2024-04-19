#include "Server.hpp"

Server::Server() : _port(0), _sockfd(-1) {}

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(string const &portString, string const &password) : _sockfd(-1) {
	if (portString.find_last_not_of("0123456789") != string::npos || atoi(portString.c_str()) < 0 || atoi(portString.c_str()) > 65535) { // Check Range
		throw runtime_error("Invalid port\n");
	}
	if (password.empty())
		throw runtime_error("Password empty\n");

	_port = atoi(portString.c_str());
	_password = password;
}

Server::~Server() {}

int	Server::getPort() const { return _port; }

int	Server::getSockfd() const { return _sockfd; }

vector<Client*>	&Server::getClients() { return _clients; }

string	&Server::getPassword() { return _password; }
