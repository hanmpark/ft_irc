#include "commands/PONG.hpp"

PONG::PONG() : ACommand() {}

PONG::~PONG() {}

void	PONG::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	RPL::sendRPL(server, client, "PONG " + server.getName() + "\r\n");
}