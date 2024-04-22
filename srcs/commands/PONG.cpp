#include "commands/PONG.hpp"

PONG::PONG() {}

PONG::~PONG() {}

void	PONG::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	if (args.size() < 2)
		return ;
	string	message = ":" + client->getNickname() + "!" \
						+ client->getUsername() + "@" \
						+ client->getHostname() + " PING " \
						+ client->getNickname() + " :" + message + "\r\n";
	Server::sendMessage(client->getFd(), message);
}