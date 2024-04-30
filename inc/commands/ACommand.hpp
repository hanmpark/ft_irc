#pragma once

# include "Server.hpp"
# include "client/Client.hpp"
# include "Replies.hpp"

class Server;

class ACommand {
public:
	ACommand() {}
	virtual	~ACommand() {}

	virtual void	execute(Server &server, Client *client, vector<string> &args) const = 0;
};
