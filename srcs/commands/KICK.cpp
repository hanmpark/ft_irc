#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

/**
 * @brief Checks the parameters of the KICK command.
 *
 * @param server The Server object reference.
 * @param client The Client object pointer that issued the command.
 * @param channel The Channel object pointer that the command is being executed on.
 * @param nick The nickname of the user to be kicked.
 *
 * @return An error message string if any of the conditions are not met, or an empty string if all conditions are met.
 */
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

/**
 * @brief Executes the KICK command.
 *
 * Syntax: KICK <channel> <user> [<comment>]
 *
 * This command is used to kick a user from a channel.
 * The user must be a member of the channel and have the appropriate permissions to kick other users.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of command arguments.
 */
void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel	*channel = server.getChannel(args[1]);
		string	error = _checkParams(server, client, channel, args[2]);

		if (!error.empty()) {
			Reply::sendRPL(server, client, error, SERVER);
		} else {
			Reply::sendRPL(server, client, channel, CMD::KICK(args[1], args[2], (args.size() > 2 ? args[3] : "")), CLIENT, false);
			channel->getClientsList().removeClient(channel->getClientsList().getClient(args[2]));
		}
	}
}
