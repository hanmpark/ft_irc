#include "commands/PING.hpp"

PING::PING() {}

PING::~PING() {}

void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	Server::sendRPL(server, client->getFd(), "PONG " + server.getName() + "\r\n");
}
