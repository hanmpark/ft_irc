#include "commands/QUIT.hpp"

QUIT::QUIT() : ACommand() {}

QUIT::~QUIT() {}

void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	vector<Channel*>			channelList = server.getChannelList().getChannelsFromClient(client);
	vector<Channel*>::iterator	it;

	for (it = channelList.begin(); it != channelList.end(); it++) {
		Reply::sendRPL(server, client, *it, CMD::QUIT((args[1].empty() ? "Client Quit" : args[1])), CLIENT, true);
		(*it)->removeClient(client);
		if ((*it)->getClientsList().getClients().empty()) {
			server.getChannelList().removeChannel(*it);
		}
	}
}
