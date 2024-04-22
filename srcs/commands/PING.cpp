#include "commands/PING.hpp"

PING::PING() {}

PING::~PING() {}

void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	if (args.size() < 2)
		return ;
	string	message = ":" + client->getNickname() + "!" \
						+ client->getUsername() + "@" \
						+ client->getHostname() + " PONG " \
						+ client->getNickname() + " :" + message + "\r\n";
	Server::sendMessage(client->getFd(), message);
}
