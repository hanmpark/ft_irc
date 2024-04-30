#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstring>

#include "Server.hpp"

#define BLUE	"\033[1;34m"
#define GREEN	"\033[1;32m"
#define RESET	"\033[0m"

void	Server::initServer() {
	int	opt = 1;

	_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverFd == -1)
		throw runtime_error("Failed at socket creation");
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw runtime_error("Failed at socket options setup");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw runtime_error("Failed at setting non-blocking socket");

	struct sockaddr_in	servAddr;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(_port);
	servAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(_serverFd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) < 0)
		throw runtime_error("Failed at binding socket to the address");
	if (listen(_serverFd, SOMAXCONN) < 0)
		throw runtime_error("Failed at listen function");
	_pollfds.push_back(_createSocket(_serverFd));
}

void	Server::_acceptNewClient() {
	struct sockaddr_in	cliAddr;
	socklen_t			cliLen = sizeof(cliAddr);

	int	clientFd = accept(_serverFd, reinterpret_cast<sockaddr*>(&cliAddr), &cliLen);
	if (clientFd == -1)
		cout << BLUE "Failed to accept new client" RESET << endl;
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
		cout << BLUE "Failed to set non-blocking socket" RESET << endl;

	Client	*client = new Client();

	client->setFd(clientFd);
	client->setIpAddr(inet_ntoa(cliAddr.sin_addr));
	_clients.addClient(client);
	_pollfds.push_back(_createSocket(clientFd));

	cout << GREEN "New connection from: " << client->getIpAddr() << RESET << endl;
}

struct pollfd	Server::_createSocket(int fd) const {
	struct pollfd	newSocket;

	newSocket.fd = fd;
	newSocket.events = POLLIN;
	newSocket.revents = 0;

	return newSocket;
}
