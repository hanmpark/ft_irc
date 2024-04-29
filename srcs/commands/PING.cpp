#include "commands/PING.hpp"

PING::PING() : ACommand() {}

PING::~PING() {}

void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Reply::sendRPL(server, client, CMD::PING(server.getName(), args[1]), SERVER);
	}
}
