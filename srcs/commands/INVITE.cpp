#include "commands/INVITE.hpp"

INVITE::INVITE() : ACommand() {}

INVITE::~INVITE() {}

void	INVITE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() != 3) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
		return;
	}
	string	error;
	Client	*target = server.getClientList().getClientByNickname(args[1]);
	Channel	*channel = server.getChannelList().getChannelByName(args[2]);
	if (target == NULL) {
		error = IRCErrors::ERR_NOSUCHNICK(client->getNickname(), args[1]);
	} else if (channel == NULL) {
		error = IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), args[2]);
	} else if (channel->getUsers().getClientByFd(target->getFd())) {
		error = IRCErrors::ERR_USERONCHANNEL(client->getNickname(), args[2]);
	} else if (!channel->getInvited().getClientByFd(target->getFd()) && channel->getModes() & Channel::INVITE) {
		channel->getInvited().addClient(target);
	}
	if (!error.empty()) {
		RPL::sendRPL(server, client, error, SERVER);
	} else {
		RPL::sendRPL(server, client, IRCReplies::RPL_INVITING(client->getNickname(), args[1], args[2]), SERVER);
		RPL::sendRPL(server, client, target, "INVITE " + args[1] + " :" + args[2] + "\r\n", CLIENT);
	}
}
