#include "Server.hpp"
#include "IrcIncludes.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "signalHandler.hpp"

//https://www.geeksforgeeks.org/socket-programming-cc/
void	Server::createSocket() {
	try {
		int					ret, opt = 1;
		struct sockaddr_in	servAddr;
		struct pollfd		newFd;

		_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (_sockfd < 0) {
			throw runtime_error("Error: Failed at socket creation\n");
		}

		ret = setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		if (ret < 0) {
			throw runtime_error("Error: Failed at socket options setup\n");
		}

		ret = fcntl(_sockfd, F_SETFL, O_NONBLOCK);
		if (ret < 0) {
			throw runtime_error("Error: Failed at setting non-blocking socket\n");
		}

		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET; // IPv4
		servAddr.sin_port = htons(_port); // Convert to network byte order
		servAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any address
		ret = bind(_sockfd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr));
		if (ret < 0) {
			throw runtime_error("Error: Failed at binding socket to the address\n");
		}

		ret = listen(_sockfd, SOMAXCONN);
		if (ret < 0) {
			throw runtime_error("Error: Failed at listen function\n");
		}
		// Add the server socket to the pollfd structure
		newFd.fd = _sockfd;
		newFd.events = POLLIN; // know when a client is trying to connect
		newFd.revents = 0; // no events yet, will be filled by poll later on.
		this->_pollFds.push_back(newFd);
	} catch (runtime_error &e) {
		cout << e.what() << endl;
	}

	return ;
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

	client.setFd(clientFd);
	// inet_ntoa() converts the client address to a string.
	client.setIpAddr(inet_ntoa(cliAddr.sin_addr));
	_clients.push_back(client);
	_pollFds.push_back(newFd);

	cout << "New connection from: " << client.getIpAddr() << endl;

	return ;
}

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
	return ;
}

int	Server::runServer()
{
	signal(SIGINT, &signalHandler);
	signal(SIGQUIT, &signalHandler);
	// Run the server, must handle signals
	while (g_signalReceived == false) {
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

void	Server::initServer(int port, string const &password) {

	this->createSocket();
	this->runServer();

	return ;
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

Server::Server() : _port(0), _sockfd(-1), _password("") {

	return ;
}

Server::Server(Server const &src) {
	*this = src;
}

/*
reasoning behind the port range is that TCP & UDP have port numbers represented
by a 16-bit unsigned integer.
1. 0-1023 reserved for specific services
2. 1024 to 49151 can be registered for specific purposes
3. 49152-65535 used by client apps for outgoing conncections.
*/
Server::Server(int const port, string const &password) {
	if (port < 0 || port > 65535)
		throw runtime_error("Error: Invalid port\n");
	else if (password.empty())
		throw runtime_error("Error: Password empty\n");

	this->_port = port;
	this->_password = password;
	this->_sockfd = -1;

	return ;
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
