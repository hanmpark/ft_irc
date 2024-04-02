#include "Server.hpp"

int	Server::createSocket() {
	// Create a socket
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		std::cerr << ERR_SOCK << std::endl;
		return 0;
	}

	// Set the socket options
	struct sockaddr_in	servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(_port);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
		std::cerr << ERR_SOCK << std::endl;
		return 0;
	}

	// Bind the socket

}

void	Server::initServer(int port, std::string const &password) {
	_port = port;
	_password = password;

	if (!createSocket()) {
		throw std::exception();
	}

}

Server::Server() : _port(0), _sockfd(0), _password("") {

	return ;
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
