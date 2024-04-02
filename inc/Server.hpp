# pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Client;

class Server {
	private:
		int	_port;
		int	_sockfd;
		std::vector<Client>	_clients;
		std::string	_serverName;
	public:
		Server(int port, std::string const &serverName);
		~Server();

		/* Accessors */
		int	getPort() const;
		int	getSockfd() const;
		std::vector<Client>	getClients() const;
		std::string	getServerName() const;

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
