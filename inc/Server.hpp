# pragma once

# include "IrcIncludes.hpp"
# include "IRCReplies.hpp"
# include "commands/ACommand.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define BUFFER_SIZE 1024

class ACommand;

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
	map<string, ACommand*>	_commands;	// map of commands
	vector<Client*>			_clients;	// vector of clients
	map<string, Channel*>	_channels;	// map of channels
	string					_password;
	string					_name;
	int						_port, _sockfd;
	vector<struct pollfd>	_pollFds;	// vector of pollfds
	static bool				_signalReceived;

	typedef vector<Client*>::iterator			clientIt;USER_IDENTIFIER
	typedef map<string, ACommand*>::iterator	commandIt;
	typedef map<string, Channel*>::iterator		channelIt;

	static void		signalHandler(int signum);

	struct pollfd	createSocket(int fd) const;
	void			acceptNewClient();
	void			receiveData(int clientFd);
	Client			*getClientByFd(int fd);

	void			handleClient(Client *client);
	vector<string>	splitBuffer(string const &buffer, string const &limiter) const;
	void			selectCommand(Client *client, string const &buffer);

	void			closeFileDescriptors();
	void			removeClient(int fd);

	Server();

public:
	Server(string const &portString, string const &password);
	~Server();

	static string	findPrefix(Server &server, int fd, e_endpoint side);
	static void		sendRPL(Server &server, int fd, string const &message);
	static void		sendRPL(Server &server, int fd, vector<string> const &args);
	static void		debugLog(string const &errorLog);
	static void		debugLog(vector<string> const &args);
	static void		debugLog(Server &server, int fd, vector<string> const &args, e_endpoint endPoint);

	/* Accessors */

	int				getPort() const;
	int				getSockfd() const;
	string const 	&getName() const;
	vector<Client*>	&getClients();
	string			&getPassword();

	/* Channel methods */
	Channel	*getChannelByName(string const &channel);
	void	addChannel(string const &channelName, Channel *channel);

	/* Server method */

	void	initServer();
	void	runServer();
};
