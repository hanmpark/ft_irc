#pragma once

# include "IRCIncludes.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "IRCReplies.hpp"

class Server;

class ACommand {
public:
	ACommand() {}
	virtual	~ACommand() {}

	virtual void	execute(Server &server, Client *client, vector<string> &args) const = 0;
};
