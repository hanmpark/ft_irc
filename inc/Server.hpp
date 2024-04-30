#pragma once

# include <iostream>
# include <poll.h>
# include <vector>

# include "commands/CommandList.hpp"
# include "channel/ChannelList.hpp"
# include "client/ClientList.hpp"

using namespace std;

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
	int						_port, _serverFd;
	vector<struct pollfd>	_pollfds;
	static bool				_signalReceived;

	static void		_signalHandler(int signum);
	struct pollfd	_createSocket(int fd) const;
	void			_acceptNewClient();
	void			_receiveData(int clientFd);
	void			_handleClient(Client *client);
	void			_welcome(Server &server, Client *client) const;

	Server();

public:
	Server(string const &portString, string const &password);
	~Server();

	int				getPort() const;
	int				getSockfd() const;
	string const 	&getName() const;
	ClientList		&getClientsList();
	ChannelList		&getChannelList();
	string			&getPassword();
	bool			&getSignalReceived() const;

	Client	*getClient(string const &nickname) const;
	Client	*getClient(int const &fd) const;
	Channel	*getChannel(string const &name) const;

	void	initServer();
	void	runServer();
};
