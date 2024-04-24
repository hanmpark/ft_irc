#include "Server.hpp"

// https://www.geeksforgeeks.org/socket-programming-cc/
void	Server::initServer() {
	int	opt = 1;

	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		throw runtime_error("Failed at socket creation\n");
	}
	if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		throw runtime_error("Failed at socket options setup\n");
	}
	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0) {
		throw runtime_error("Failed at setting non-blocking socket\n");
	}

	struct sockaddr_in	servAddr;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET; // IPv4
	servAddr.sin_port = htons(_port); // Convert to network byte order
	servAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any address

	if (bind(_sockfd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) < 0) {
		throw runtime_error("Failed at binding socket to the address\n");
	}
	if (listen(_sockfd, SOMAXCONN) < 0) {
		throw runtime_error("Failed at listen function\n");
	}
	_pollFds.push_back(createSocket(_sockfd));
}

void	Server::acceptNewClient() {
	struct sockaddr_in	cliAddr; // Client address
	socklen_t			cliLen = sizeof(cliAddr); // Client address length for accept()

	int	clientFd = accept(_sockfd, reinterpret_cast<sockaddr*>(&cliAddr), &cliLen); // accept() returns a new fd which is the client socket
	if (clientFd < 0) {
		return ;
	}
	// Set the client socket to non-blocking
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0) {
		return ;
	}

	Client	*client = new Client(); // Create a new instance of the client

	client->setFd(clientFd);
	client->setIpAddr(inet_ntoa(cliAddr.sin_addr)); // inet_ntoa() converts the client address to a string.
	_clients.addClient(client);
	_pollFds.push_back(createSocket(clientFd));

	cout << GREEN "New connection from: " << client->getIpAddr() << RESET << endl;
}

struct pollfd	Server::createSocket(int fd) const {
	struct pollfd	newSocket;

	newSocket.fd = fd;
	newSocket.events = POLLIN;
	newSocket.revents = 0;

	return newSocket;
}
