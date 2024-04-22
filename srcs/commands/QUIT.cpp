#include "QUIT.hpp"

QUIT::QUIT() {}

QUIT::~QUIT() {}

void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	if (server.getClients().empty())
		return ;
	// quit message can have a reason as parameter
	if (!args.size())
		args.push_back("Leaving");
	// send QUIT message to all clients if ctrl+d
	
	string	message = ":" + client->getNickname() + "!" \
						+ client->getUsername() + "@" \
						+ client->getHostname() + " QUIT :" + args[0] + "\r\n";
	Server::sendMessage(client->getFd(), message);
}
