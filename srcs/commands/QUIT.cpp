#include "commands/QUIT.hpp"

QUIT::QUIT() : ACommand() {}

QUIT::~QUIT() {}

void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	vector<Channel*>	channelList = server.getChannelList().getChannelsFromClient(client);
	vector<Channel*>::const_iterator	it;
	for (it = channelList.begin(); it != channelList.end(); it++) {
		vector<Client*>::const_iterator	clientIt = (*it)->getClientsList().getClients().begin();
		vector<Client*>::const_iterator	clientEnd = (*it)->getClientsList().getClients().end();
		for (; clientIt != clientEnd; clientIt++) {
			Reply::sendRPL(server, client, *clientIt, CMD::QUIT((args.size() == 1 ? "Client Quit" : args[1])), CLIENT);
		}
		(*it)->removeClient(client);
	}
}
