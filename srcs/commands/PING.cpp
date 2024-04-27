#include "commands/PING.hpp"

PING::PING() : ACommand() {}

PING::~PING() {}

void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	RPL::sendRPL(server, client, "PONG " + server.getName() + "\r\n", SERVER);
}
