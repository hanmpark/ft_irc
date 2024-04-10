#include "Server.hpp"
#include "IrcIncludes.hpp"
#include "Client.hpp"

bool	Server::_signalReceived = false;

void	Server::receiveData(int clientFd) {
	char	buff[BUFFER_SIZE];
	bzero(buff, BUFFER_SIZE); // clear the buffer

	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0) {
		removeClient(clientFd);
		close(clientFd);
		return ;
	}
	cout << "Client <" << clientFd << "> Received data: " << buff << endl;
	// deal with commands here ?
}

int	Server::runServer()
{
	signal(SIGINT, &signalHandler);
	signal(SIGQUIT, &signalHandler);
	// Run the server, must handle signals
	while (_signalReceived == false) {
		// Poll for incoming events
		if (poll(&_pollFds[0], _pollFds.size(), -1) < 0) {
			return 1;
		}
		// Check if the server socket has an event
		for (size_t i = 0; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _sockfd) {
					acceptConnection();
				} else {
					receiveData(_pollFds[i].fd);
				}
			}
		}
	}

	/* Close the server socket and all client sockets if they are still open */
	closeFileDescriptors();
	return 0;
}

void	Server::initServer() {
	createSocket();
	if (_sockfd == -1)
		throw runtime_error("Could not run server\n");
	else if (runServer() == 1)
		throw runtime_error("Failed trying to run the server\n");
}

void Server::closeFileDescriptors() {
	for (size_t i = 0; i < _clients.size(); i++) {
		cout << RED << "Client <" << _clients[i].getFd() << "> Disconnected" << RESET << endl;
		close(_clients[i].getFd());
	}
	if (_sockfd != -1) {
		cout << RED << "Server <" << _sockfd << "> Disconnected" << RESET << endl;
		close(_sockfd);
	}
}

void Server::removeClient(int fd)
{
	for (size_t i = 0; i < _pollFds.size(); i++) {
		if (_pollFds[i].fd == fd) {
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i].getFd() == fd) {
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

void	Server::signalHandler(int signum) {
	if (signum == SIGINT || signum == SIGQUIT) {
		_signalReceived = true;
		cout << "PASS" << endl;
	}
}

Server::Server() : _port(0), _sockfd(-1), _password("") {}

/*
 * reasoning behind the port range is that TCP & UDP have port numbers represented
 * by a 16-bit unsigned integer.
 * 1. 0-1023 reserved for specific services
 * 2. 1024 to 49151 can be registered for specific purposes
 * 3. 49152-65535 used by client apps for outgoing conncections.
 */
Server::Server(int const port, string const &password) {
	if (port < 0 || port > 65535)
		throw runtime_error("Error: Invalid port\n");
	else if (password.empty())
		throw runtime_error("Error: Password empty\n");

	_port = port;
	_password = password;
	_sockfd = -1;
}

Server::~Server() {}

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
