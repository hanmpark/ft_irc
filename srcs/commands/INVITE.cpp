#include "commands/INVITE.hpp"

INVITE::INVITE() : ACommand() {}

INVITE::~INVITE() {}

void	INVITE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() != 3) {
		throw IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname() + " " + args[0]);
	}
	Client	*target = server.getClientList().getClientByNickname(args[1]);
	Channel	*channel = server.getChannelList().getChannelByName(args[2]);
	if (target == NULL) {
		throw IRCErrors::ERR_NOSUCHNICK(client->getNickname() + " " + args[1]);
	} else if (channel == NULL) {
		throw IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname() + " " + args[2]);
	} else if (channel->getUsers().getClientByFd(target->getFd())) {
		throw IRCErrors::ERR_USERONCHANNEL(client->getNickname() + " " + args[1], args[2]);
	} else if (!channel->getInvited().getClientByFd(target->getFd()) && channel->getModes() & Channel::INVITE) {
		channel->getInvited().addClient(target);
	}
	RPL::sendRPL(server, client, IRCReplies::RPL_INVITING(args[2], args[1]));
}
