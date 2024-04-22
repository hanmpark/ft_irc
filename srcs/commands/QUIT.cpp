#include "QUIT.hpp"

QUIT::QUIT() {}

QUIT::~QUIT() {}

void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	if (server.getClients().empty())
		return ;
	// * quit message can have a reason as parameter
	if (!args.size())
		args.push_back("Leaving");

	string	message = ":" + client->getNickname() + "!" \
						+ client->getUsername() + "@" \
						+ client->getHostname() + " QUIT :" + args[0] + "\r\n";
	if (server.getClients().size() > 1 && server.getSignalReceived()) { // if signal received, broadcast QUIT
		for (size_t i = 0; i < server.getClients().size(); i++) {
			Server::sendMessage(server.getClients()[i]->getFd(), message);
		}
		return ;
	}
	// 
	Server::sendMessage(client->getFd(), message);
}
