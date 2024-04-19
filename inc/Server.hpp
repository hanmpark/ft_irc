# pragma once

# include "IrcIncludes.hpp"
# include "IRCReplies.hpp"
# include "Client.hpp"
# include "Channel.hpp"

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
protected:
	vector<Client*>	_clients;	// vector of clients
	vector<string>	_channels;	// vector of channels
	string			_password;

	typedef vector<Client>::iterator	clientIt;

	void	sendMessage(int fd, string const &message) const;

private:
	int						_port;
	int						_sockfd;
	vector<struct pollfd>	_pollFds;	// vector of pollfds
	static bool				_signalReceived;

	static void		signalHandler(int signum);

	struct pollfd	createSocket(int fd) const;
	void			initServerSocket();
	int				runServer();
	void			acceptNewClient();
	void			receiveData(int clientFd);
	Client			*getClientByFd(int fd);
	void			handleCommand(Client *client);

	void			closeFileDescriptors();
	void			removeClient(int fd);

public:
	Server(string const &portString, string const &password);
	Server();
	virtual ~Server();

	/* Accessors */

	int				getPort() const;
	int				getSockfd() const;
	vector<Client*>	&getClients();
	string			&getPassword();



	/* Server method */

	void	initServer();
};
