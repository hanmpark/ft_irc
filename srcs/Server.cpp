#include "Server.hpp"
#include "IrcIncludes.hpp"
#include "Client.hpp"
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
	_pollFds.push_back(newFd); // adding our server to the private list of pollfds.

	return 0;
}

void	Server::acceptConnection() {
	Client				client; // Create a new instance of the client
	struct sockaddr_in	cliAddr; // Client address
	socklen_t			cliLen = sizeof(cliAddr); // Client address length for accept()

	/* Accept the connection
	* accept() returns a new fd which is the client socket
	*/
	int	clientFd = accept(_sockfd, reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
	if (clientFd < 0) {
		return ;
	}

	// Set the client socket to non-blocking
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0) {
		return ;
	}

	// Add the client socket to the pollfd structure
	struct pollfd	newFd;
	newFd.fd = clientFd;
	newFd.events = POLLIN; // for reading data
	newFd.revents = 0;
	_clients.push_back(client); // Add the client to the list of clients
	_pollFds.push_back(newFd); // Add the client to the list of pollfds

	

}

int	Server::runServer()
{
	while (1) {
		// Poll for incoming events
		int ret = poll(&_pollFds[0], _pollFds.size(), -1);
		if (ret < 0) {
			return 1;
		}

		// Check if the server socket has an event
		for (size_t i = 0; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _sockfd) {
					acceptConnection();
				}
				else {
					receiveData(_pollFds[i].fd);
				}
			}
		}
	}

	/* Close the server socket and all client sockets if they are still open */
	// cleanupFileDescriptors();
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

vector<Client>	Server::getClients() const {
	return _clients;
}

string	Server::getPassword() const {
	return _password;
}
