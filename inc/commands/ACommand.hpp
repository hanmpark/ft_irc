#pragma once

# include "IRCIncludes.hpp"
# include "Replies.hpp"
# include "Server.hpp"
# include "client/Client.hpp"

class Server;

class ACommand {
public:
	ACommand() {}
	virtual	~ACommand() {}

	virtual void	execute(Server &server, Client *client, vector<string> &args) const = 0;
};
