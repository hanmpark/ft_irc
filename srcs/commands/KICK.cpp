#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

string const	KICK::_checkParams(Server &server, Client *client, Channel *channel, string const &nick) const {
	string	error;

	if (channel == NULL) {
		error = ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channel->getName());
	} else if (server.getClient(nick) == NULL) {
		error = ERR::ERR_NOSUCHNICK(client->getNickname(), nick);
	} else if (!channel->getClientsList().getClient(client->getFd())) {
		error = ERR::ERR_NOTONCHANNEL(client->getNickname(), channel->getName());
	} else if (channel->getOperatorsList().getClient(client->getFd()) == NULL) {
		error = ERR::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName());
	} else if (channel->getClientsList().getClient(nick) == NULL) {
		error = ERR::ERR_USERNOTINCHANNEL(client->getNickname(), nick, channel->getName());
	}

	return error;
}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel	*channel = server.getChannel(args[1]);
		string	error = _checkParams(server, client, channel, args[2]);

		if (!error.empty()) {
			Reply::sendRPL(server, client, error, SERVER);
		} else {
			Reply::sendRPL(server, client, channel, CMD::KICK(args[1], args[2]), CLIENT, false);
			channel->getClientsList().removeClient(channel->getClientsList().getClient(args[2]));
		}
	}
}
