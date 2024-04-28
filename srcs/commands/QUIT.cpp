#include "commands/QUIT.hpp"

QUIT::QUIT() : ACommand() {}

QUIT::~QUIT() {}

void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	vector<Channel*>	channelList = server.getChannelList().getChannelsFromClient(client);
	vector<Channel*>::const_iterator	it;
	for (it = channelList.begin(); it != channelList.end(); it++) {
		vector<Client*>::const_iterator	clientIt = (*it)->getUsers().getClients().begin();
		vector<Client*>::const_iterator	clientEnd = (*it)->getUsers().getClients().end();
		for (; clientIt != clientEnd; clientIt++) {
			RPL::sendRPL(server, client, *clientIt, "QUIT :" + (args.size() == 1 ? "Client Quit" : args[1]) + "\r\n", CLIENT);
		}
		(*it)->getUsers().removeClient(client);
		// server.removePollFd(client->getFd());
		// server.getClientList().deleteClient(client);
	}
}
