#include "Server.hpp"

bool	Server::_signalReceived = false;

void Server::signalHandler(int signum)
{
	(void)signum;
	_signalReceived = true;
	//! when signal is received, need to call QUIT command and close all file descriptors
}

void Server::closeFileDescriptors() {
	for (size_t i = 0; i < _clients.size(); i++) {
		cout << RED << "Client: " << _clients[i]->getFd() << " Disconnected" << RESET << endl;
		close(_clients[i]->getFd());
	}
	if (_sockfd != -1) {
		cout << RED << "Server: " << _sockfd << " Disconnected" << RESET << endl;
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
		if (_clients[i]->getFd() == fd) {
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

void	Server::runServer()
{
	signal(SIGINT, &signalHandler);
	signal(SIGQUIT, &signalHandler);

	// Run the server, must handle signals
	while (_signalReceived == false) {
		// Poll for incoming events
		if (poll(&_pollFds[0], _pollFds.size(), -1) < 0) {
			throw runtime_error("Failed at trying to run the server\n");
		}
		// Check if the server socket has an event
		for (size_t i = 0; i < _pollFds.size(); i++) {
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _sockfd) {
					acceptNewClient();
				} else {
					receiveData(_pollFds[i].fd);
				}
			}
		}
	}

	closeFileDescriptors(); // Close the server socket and all client sockets if they are still open
}
