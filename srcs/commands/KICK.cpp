#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

string const	KICK::_checkParams(Client *client, Channel *channel, string const &nick) const {
	string	error;

	if (channel == NULL) {
		error = ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channel->getName());
	} else if (channel->getClientsList().getClientByNickname(nick) == NULL) {
		error = ERR::ERR_NOSUCHNICK(client->getNickname(), nick);
	} else if (channel->getOperatorsList().getClientByFd(client->getFd()) == NULL) {
		error = ERR::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName());
	}

	return error;
}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel	*channel = server.getChannelList().getChannelByName(args[1]);
		string	error = _checkParams(client, channel, args[2]);

		if (!error.empty()) {
			Reply::sendRPL(server, client, error, SERVER);
		} else {
			channel->getClientsList().removeClient(channel->getClientsList().getClientByNickname(args[2]));
			Reply::sendRPL(server, client, CMD::KICK(args[1], args[2]), CLIENT);
		}
	}
}
