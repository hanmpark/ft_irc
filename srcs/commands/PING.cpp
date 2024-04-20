#include "commands/PING.hpp"

PING::PING() {}

PING::~PING() {}

void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	if (args.size() < 2)
		return ;
	Server::sendMessage(client->getFd(), "PONG " + server.getName() + "\r\n");
}
