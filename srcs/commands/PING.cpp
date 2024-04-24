#include "commands/PING.hpp"

PING::PING(Server &server) : ACommand(server) {}

PING::~PING() {}

void	PING::execute(Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	RPL::sendRPL(_server, client, "PONG " + _server.getName() + "\r\n");
}
