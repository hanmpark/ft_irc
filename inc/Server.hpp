# pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Client;

/*
* Server class:
- Server class is responsible for creating a socket,
accepting connections, receiving and sending data.
- It containes all of the information about the server.
- It has a private attribute _clients to keep track of all
the clients connected to the server, as well as manage their
requests.
- It contains as well a list of pollfds.
pollfds = is used for manipulating file descriptors in order to handle I/O events
That way, instead of waiting for a single event coming from one client,
we can handle more events simultaneously in an effective way using the struct.
Which prevents the block events.
*/
class Server {
	private:
		int	_port;
		int	_sockfd;
		vector<Client>	_clients; // vector of clients
		vector<struct pollfd>	_fds; // vector of pollfds
		string	_password;

		Server(Server const &src);
		Server	&operator=(Server const &rhs);
	public:
		Server();
		Server(int port, int sockfd, string const &password);
		~Server();

		/* Accessors */
		int	getPort() const;
		int	getSockfd() const;
		vector<Client>	getClients() const;
		string	getPassword() const;

		/* Server methods */
		void	initServer(int port, string const &password);
		int		createSocket();
		int		runServer();
		void	acceptConnection();
		void	receiveData(int fd);
		void	sendData();

		/* Handle signals */
		void	signalHandler(int signum);

		void	closeFileDescriptors();
		void	removeClient(int fd);

};
