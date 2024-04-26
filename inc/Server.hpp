#pragma once

# include "IRCIncludes.hpp"
# include "IRCReplies.hpp"
# include "commands/CommandList.hpp"
# include "ChannelList.hpp"
# include "ClientList.hpp"

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
	CommandList				_commands;
	ClientList				_clients;
	ChannelList				_channels;
	string					_name, _password;
	int						_port, _sockfd;
	vector<struct pollfd>	_pollFds;
	static bool				_signalReceived;

	static void		signalHandler(int signum);
	struct pollfd	createSocket(int fd) const;
	void			acceptNewClient();
	void			receiveData(int clientFd);
	void			handleClient(Client *client);
	void			closeFileDescriptors();
	void			removePollFd(int fd);

	Server();

public:
	Server(string const &portString, string const &password);
	~Server();

	/* Accessors */
	int				getPort() const;
	int				getSockfd() const;
	string const 	&getName() const;
	ClientList		&getClientList();
	ChannelList		&getChannelList();
	string			&getPassword();
	bool			&getSignalReceived() const;

	void	initServer();
	void	runServer();
};
