#include "Server.hpp"

bool	Server::_signalReceived = false;

void Server::closeFileDescriptors() {
	for (size_t i = 0; i < _clients.size(); i++) {
		cout << RED << "Client: " << _clients[i].getFd() << " Disconnected" << RESET << endl;
		close(_clients[i].getFd());
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
		if (_clients[i].getFd() == fd) {
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

void	Server::handleCommand(Client &client) {
	Command	command;
	string	buffer = client.getCommand();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		if (client.getRegistered() == false) {
			if (!client.getNickname().empty() || !client.getUsername().empty() || !client.getHostname().empty()) {
				client.setRegistered(true);
				// send RPL_WELCOME
			}
		} else {
			command.selectCommand(client, client.getCommand());
		}
	}
}

void	Server::receiveData(int clientFd) {
	char		buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	Client		&client = *find(_clients.begin(), _clients.end(), clientFd);

	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0) {
		removeClient(clientFd);
		close(clientFd);
		return ;
	}
	cout << "Client " << clientFd << ": " << buff;
	client.addToCommand(static_cast<string>(buff));
	if (client.getCommand().find("\r\n") != string::npos) {
		handleCommand(client);
	}
}

void	Server::signalHandler(int signum) {
	(void)signum;
	_signalReceived = true;
}

int	Server::runServer()
{
	signal(SIGINT, &signalHandler);
	signal(SIGQUIT, &signalHandler);

	// Run the server, must handle signals
	while (_signalReceived == false) {
		// Poll for incoming events
		if (poll(&_pollFds[0], _pollFds.size(), -1) < 0) {
			return -1;
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

	return 0;
}

void	Server::initServer() {
	initServerSocket();
	if (_sockfd == -1)
		throw runtime_error("Could not run server\n");
	else if (runServer() == -1)
		throw runtime_error("Failed trying to run the server\n");
}
