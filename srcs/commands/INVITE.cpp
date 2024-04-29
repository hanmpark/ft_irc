#include "commands/INVITE.hpp"

INVITE::INVITE() : ACommand() {}

INVITE::~INVITE() {}

string const	INVITE::_checkParams(Server &server, Client *client, string const &nick, string const &channelName) const {
	string	error;
	Client	*target = server.getClientList().getClientByNickname(nick);
	Channel *channel = server.getChannelList().getChannelByName(channelName);

	if (target == NULL) {
		error = ERR::ERR_NOSUCHNICK(client->getNickname(), nick);
	} else if (channel == NULL) {
		error = ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
	} else if (channel->getClientsList().getClientByFd(target->getFd())) {
		error = ERR::ERR_USERONCHANNEL(client->getNickname(), channelName);
	} else if (!channel->getInvitedList().getClientByFd(target->getFd()) && channel->getModes() & Channel::INVITE) {
		channel->getInvitedList().addClient(target);
	}

	return error;
}

void	INVITE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() != 3) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		string	error = _checkParams(server, client, args[1], args[2]);
		if (!error.empty()) {
			Reply::sendRPL(server, client, error, SERVER);
		} else {
			Reply::sendRPL(server, client, RPL::RPL_INVITING(client->getNickname(), args[1], args[2]), SERVER);
			Reply::sendRPL(server, client, server.getClientList().getClientByNickname(args[1]), CMD::INVITE(args[1], args[2]), CLIENT);
		}
	}
}
