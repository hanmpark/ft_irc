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
*/
class Server {
	private:
		int	_port;
		int	_sockfd;
		std::vector<Client>	_clients;
		std::string	_password;

		Server();
		Server(Server const &src);
		Server	&operator=(Server const &rhs);
	public:
		Server(int port, int sockfd, std::string const &password);
		~Server();

		/* Accessors */
		int	getPort() const;
		int	getSockfd() const;
		std::vector<Client>	getClients() const;
		std::string	getPassword() const;

		/* Server methods */
		void	initServer();
		void	createSocket();
		void	acceptConnection();
		void	receiveData(int fd);
		void	sendData();

		/* Handle signals */
		void	signalHandler(int signum);

		void	closeFileDescriptors();
		void	removeClient(int fd);

};
