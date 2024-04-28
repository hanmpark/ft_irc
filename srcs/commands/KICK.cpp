#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

string const	KICK::_checkParams(Server &server, Client *client, Channel *channel, string const &nick) const {
	string	error;

	if (channel == NULL) {
		error = IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), channel->getName());
	} else if (channel->getClientsList().getClientByNickname(nick) == NULL) {
		error = IRCErrors::ERR_NOSUCHNICK(client->getNickname(), nick);
	} else if (channel->getOperatorsList().getClientByFd(client->getFd()) == NULL) {
		error = IRCErrors::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName());
	}

	return error;
}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel	*channel = server.getChannelList().getChannelByName(args[1]);
		string	error = _checkParams(server, client, channel, args[2]);

		if (!error.empty()) {
			RPL::sendRPL(server, client, error, SERVER);
		} else {
			channel->getClientsList().removeClient(channel->getClientsList().getClientByNickname(args[2]));
			RPL::sendRPL(server, client, IRCCommands::KICK(args[1], args[2]), CLIENT);
		}
	}
}
