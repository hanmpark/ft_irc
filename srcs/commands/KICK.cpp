#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return;
	}
	string	error;
	Channel	*channel = server.getChannelList().getChannelByName(args[1]);
	if (channel == NULL) { // 1. Check if the channel exists
		error = IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname() + " " + args[1]);
	} else if (channel->getUsers().getClientByNickname(args[2]) == NULL) { // 2. Check if the client is in the channel
		error = IRCErrors::ERR_NOSUCHNICK(client->getNickname() + " " + args[1]);
	} else if (channel->getOperators().getClientByNickname(args[2]) == NULL) { // 3. Check if the client is an operator
		error = IRCErrors::ERR_CHANOPRIVSNEEDED(client->getNickname() + " " + args[1]);
	}
	if (!error.empty()) {
		RPL::sendRPL(server, client, error);
	} else {
		channel->getUsers().removeClient(channel->getUsers().getClientByNickname(args[2]));
	}
}
