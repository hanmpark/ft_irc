#include "IrcInclude.hpp"
#include "Server.hpp"
#include "Utils.hpp"

//https://www.geeksforgeeks.org/socket-programming-cc/
int	Server::createSocket() {
	// Create a socket
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		return 1;
	}

	// Set the socket options
	struct sockaddr_in	servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET; // IPv4
	servAddr.sin_port = htons(_port); // Convert to network byte order
	servAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any address

	// Set socket options to reuse the address and port for multiple connections.
	if (setsockopt(_sockfd, SOL_SOCKET, \
		SO_REUSEADDR | SO_REUSEPORT, &(int){1}, sizeof(int)) < 0) {
		return 1;
	}

	// Set the socket to non-blocking
	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0) {
		return 1;
	}

	// Bind the socket to the address
	if (bind(_sockfd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) < 0) {
		return 1;
	}

	// Listen for incoming connections
	if (listen(_sockfd, SOMAXCONN) < 0) {
		return 1;
	}

	// Add the server socket to the pollfd structure
	struct pollfd	newFd;
	newFd.fd = _sockfd;
	newFd.events = POLLIN; // know when a client is trying to connect
	newFd.revents = 0; // no events yet, will be filled by poll later on.
	_fds.push_back(newFd); // adding our server to the private list of pollfds.

	return 0;
}

int	Server::runServer()
{
	while ("quoicoubeh") {
		if (poll(&_fds[0], _fds.size()m, -1))
	}
	return 0;
}

void	Server::initServer(int port, string const &password) {
	_port = port;
	_password = password;

	// need to include signal handler for not leaking fds?

	if (createSocket() == 1) {
		throw CustomError(ERR_SOCK);
	}
	else if (runServer() == 1) {
		throw CustomError(ERR_SERVER);
	}

}

Server::Server() : _port(0), _sockfd(0), _password("") {

	return ;
}

Server::Server(Server const &src) {
	*this = src;
}

Server::Server(int port, int sockfd, string const &password) : _port(port), \
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

list<Client>	Server::getClients() const {
	return _clients;
}

string	Server::getPassword() const {
	return _password;
}
