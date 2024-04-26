#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	Channel	*channel = server.getChannelList().getChannelByName(args[1]);
	static_cast<void>(client);
	// 1. Check if the channel exists
	if (channel == NULL) {
		// send(client->getFd(), IRCErrors::ERR_NOSUCHCHANNEL(args[1])); // >> 403 No such channel
		return ;
	}
	// 2. Check if the client is in the channel
	Client	*target = channel->getUsers().getClientByNickname(args[3]);
	if (target == NULL) {
		// send(); // >> 401 No such nick/channel
		return ;
	}

	// 3. Check if the client is an operator
	if (channel->getOperators().getClientByNickname(args[3]) == NULL) {
		// send(); // >> 482 You're not channel operator
		return ;
	}

	// 4. Kick the client
	channel->getUsers().removeClient(target);

}
