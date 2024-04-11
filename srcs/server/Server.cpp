#include "Server.hpp"

Server::Server() : _port(0), _sockfd(-1), _password("") {}

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(string const &portString, string const &password) : _sockfd(-1) {
	if (portString.empty() || portString.length() > 5) {
		throw runtime_error("Invalid port\n");
	}
	for (size_t i = 0; i < portString.length(); i++) {
		if (isdigit(portString.at(i)) == false) {
			throw runtime_error("Invalid port\n");
		}
	}
	int	port = atoi(portString.c_str());
	if (port < 0 || port > 65535)
		throw runtime_error("Invalid port\n");
	else if (password.empty())
		throw runtime_error("Password empty\n");

	_port = port;
	_password = password;
}

Server::~Server() {}

int	Server::getPort() const { return _port; }

int	Server::getSockfd() const { return _sockfd; }

vector<Client>	Server::getClients() const { return _clients; }

string	Server::getPassword() const { return _password; }
