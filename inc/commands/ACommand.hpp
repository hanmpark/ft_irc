#pragma once

# include "IrcIncludes.hpp"
# include "IRCReplies.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Server;

class ACommand {
public:
	ACommand() {}
	virtual ~ACommand() {}

	virtual void	execute(Server &server, Client *client, vector<string> &args) const = 0;
};
