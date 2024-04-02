#include "Server.hpp"

Server::Server() {

}

Server::Server(Server const &src) {
	*this = src;
}

Server::Server(int port, int sockfd, std::string const &password) : _port(port), \
																	_sockfd(sockfd), \
																	_password(password) {

}

Server::~Server() {

}

Server	&Server::operator=(Server const &rhs) {
	if (this != &rhs) {
		_port = rhs.getPort();
		_sockfd = rhs.getSockfd();
		_clients = rhs.getClients();
		_password = rhs.getPassword();
	}
	return *this;
}

int	Server::getPort() const {
	return _port;
}

int	Server::getSockfd() const {
	return _sockfd;
}

std::vector<Client>	Server::getClients() const {
	return _clients;
}

std::string	Server::getPassword() const {
	return _password;
}
