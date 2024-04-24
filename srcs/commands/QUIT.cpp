#include "commands/QUIT.hpp"

QUIT::QUIT(Server &server) : ACommand(server) {}

QUIT::~QUIT() {}

void	QUIT::execute(Client *client, vector<string> &args) const {
	if (_server.getClientList().getClients().empty())
		return ;
	// * quit message can have a reason as parameter
	if (!args.size())
		args.push_back("Leaving");

	// string	message = ":" + client->getNickname() + "!" \
	// 					+ client->getUsername() + "@" \
	// 					+ client->getHostname() + " QUIT :" + args[0] + "\r\n";

	// * broadcast the message to all the users in the server
	// vector<Client*>::iterator	it;
	// for(it = server.getClients().begin(); it != server.getClients().end(); it++) {
	// 	if ((*it)->getFd() == client->getFd()) // skip the sender as they will automatically be removed
	// 		continue ;
	// 	server.sendMessage((*it)->getFd(), message);
	// }
}
