#include "commands/INVITE.hpp"

INVITE::INVITE() : ACommand() {}

INVITE::~INVITE() {}

/**
 * @brief Checks the parameters of the INVITE command.
 *
 * @param server The Server object.
 * @param client The Client object that issued the command.
 * @param nick The nickname of the target client to invite.
 * @param channelName The name of the channel to invite the target client to.
 *
 * @return An error message string if the command parameters are invalid, or an empty string if they are valid.
 */
string const	INVITE::_checkParams(Server &server, Client *client, string const &nick, string const &channelName) const {
	string	error;
	Client	*target = server.getClient(nick);
	Channel *channel = server.getChannel(channelName);

	if (target == NULL) {
		error = ERR::ERR_NOSUCHNICK(client->getNickname(), nick);
	} else if (channel == NULL) {
		error = ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelName);
	} else if (channel->getClientsList().getClient(client->getFd()) == NULL) {
		error = ERR::ERR_NOTONCHANNEL(client->getNickname(), channelName);
	} else if (channel->getClientsList().getClient(target->getFd())) {
		error = ERR::ERR_USERONCHANNEL(client->getNickname(), nick, channelName);
	} else if (!channel->getInvitedList().getClient(target->getFd()) && channel->getModes() & Channel::INVITE) {
		channel->getInvitedList().addClient(target);
	}
	return error;
}

/**
 * @brief Executes the INVITE command.
 *
 * Syntax: INVITE <nickname> <channel>
 * Where <nickname> is the nickname of the user to invite, and <channel> is the name of the channel to invite them to.
 *
 * @param server The server object.
 * @param client The client that sent the command.
 * @param args The arguments provided with the command.
 */
void	INVITE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		string	error = _checkParams(server, client, args[1], args[2]);

		if (!error.empty()) {
			Reply::sendRPL(server, client, error, SERVER);
		} else {
			Reply::sendRPL(server, client, RPL::RPL_INVITING(client->getNickname(), args[1], args[2]), SERVER);
			Reply::sendRPL(server, client, server.getClient(args[1]), CMD::INVITE(args[1], args[2]), CLIENT);
		}
	}
}
