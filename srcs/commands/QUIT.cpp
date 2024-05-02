#include "commands/QUIT.hpp"

QUIT::QUIT() : ACommand() {}

QUIT::~QUIT() {}

/**
 * @brief Executes the QUIT command.
 *
 * Syntax: QUIT [<message>]
 *
 * The QUIT command is used to disconnect a client from the server.
 * The optional <message> parameter can be used to specify a reason for quitting.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of arguments passed to the command.
 */
void	QUIT::execute(Server &server, Client *client, vector<string> &args) const {
	vector<Channel*>			channelList = server.getChannelList().getChannelsFromClient(client);
	vector<Channel*>::iterator	it;

	for (it = channelList.begin(); it != channelList.end(); it++) {
		Reply::sendRPL(server, client, *it, CMD::QUIT((args.size() < 2 ? "Client Quit" : args[1])), CLIENT, true);
		(*it)->removeClient(client);
		if ((*it)->getClientsList().getClients().empty())
			server.getChannelList().removeChannel(*it);
	}
}
