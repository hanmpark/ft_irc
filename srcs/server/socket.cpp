#include "Server.hpp"

// https://www.geeksforgeeks.org/socket-programming-cc/
void	Server::createSocket() {
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
	cout << _port << endl;
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
	_pollFds.push_back(newFd);
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
}
