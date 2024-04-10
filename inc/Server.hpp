# pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Client;

# define BUFFER_SIZE 1024

/*
 * Server class:
 * - Server class is responsible for creating a socket, accepting connections, receiving and sending data.
 * - It containes all of the information about the server.
 * - It has a private attribute _clients to keep track of all the clients connected to the server, as well as manage their requests.
 * - It contains as well a list of pollfds.
 * pollfds = is used for manipulating file descriptors in order to handle I/O events
 * That way, instead of waiting for a single event coming from one client,
 * we can handle more events simultaneously in an effective way using the struct.
 * Which prevents the block events.
 */
class Server {
private:
	int						_port;
	int						_sockfd;
	vector<Client>			_clients;	// vector of clients
	vector<struct pollfd>	_pollFds;	// vector of pollfds
	string					_password;
	static bool				_signalReceived;

	static void	signalHandler(int signum);

public:
	Server(int const port, string const &password);
	Server();
	~Server();

	/* Accessors */

	int	getPort() const;
	int	getSockfd() const;
	vector<Client>	getClients() const;
	string	getPassword() const;

	/* Server methods */

	void	initServer();
	void	createSocket();
	int		runServer();
	void	acceptConnection();
	void	receiveData(int clientFd);
	void	sendData();

	void	closeFileDescriptors();
	void	removeClient(int fd);
};

