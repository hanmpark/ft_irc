#include "commands/PONG.hpp"

PONG::PONG(Server &server) : ACommand(server) {}

PONG::~PONG() {}

void	PONG::execute(Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	RPL::sendRPL(_server, client, "PONG " + _server.getName() + "\r\n");
}