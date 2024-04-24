#pragma once

# include "IRCIncludes.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "IRCReplies.hpp"

class Server;

class ACommand {
protected:
	Server	&_server;

public:
	ACommand(Server &server) : _server(server) {}
	virtual	~ACommand() {}

	virtual void	execute(Client *client, vector<string> &args) const = 0;
};
