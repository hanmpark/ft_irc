#include <sstream>

#include "commands/PRIVMSG.hpp"

PRIVMSG::PRIVMSG() : ACommand() {}

PRIVMSG::~PRIVMSG() {}

/**
 * @brief Splits a string containing a list of channels separated by commas into a vector of strings,
 * where each string represents a single channel.
 *
 * @param channelArg The string to be split.
 *
 * @return A vector of strings representing the individual channels.
 */
vector<string>	PRIVMSG::_splitChannels(string const &channelArg) const {
	string			channelToken;
	vector<string>	channels;
	istringstream	ss(channelArg);

	while (getline(ss, channelToken, ',')) {
		channels.push_back(channelToken);
	}
	return channels;
}

/**
 * @brief Sends a message to a specific channel.
 *
 * @param server The server object reference.
 * @param client The client object pointer that sent the message.
 * @param channelName The name of the channel to send the message to.
 * @param message The message to be sent.
 */
void	PRIVMSG::_sendToChannel(Server &server, Client *client, string const &channelName, string const &message) const {
	Channel	*channel = server.getChannel(channelName);

	if (channel == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelName), SERVER);
	} else {
		if (channel->getClientsList().getClient(client->getFd()) == NULL) {
			Reply::sendRPL(server, client, ERR::ERR_CANNOTSENDTOCHAN(client->getNickname(), channelName), SERVER);
		} else {
			vector<Client*>	clients = channel->getClientsList().getClients();
			for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++) {
				if ((*it)->getFd() != client->getFd())
					Reply::sendRPL(server, client, *it, CMD::PRIVMSG(channel->getName(), message), CLIENT);
			}
		}
	}
}

/**
 * @brief Sends a private message to a specific client.
 *
 * @param server The server object reference.
 * @param client The sender client object pointer.
 * @param clientNickname The nickname of the target client.
 * @param message The message to be sent.
 */
void	PRIVMSG::_sendToClient(Server &server, Client *client, string const &clientNickname, string const &message) const {
	Client	*target = server.getClient(clientNickname);

	if (target == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHNICK(client->getNickname(), clientNickname), SERVER);
	} else {
		Reply::sendRPL(server, client, target, CMD::PRIVMSG(target->getNickname(), message), CLIENT);
	}
}

/**
 * @brief Executes the PRIVMSG command.
 *
 * Syntax: PRIVMSG <recipient> :<message>
 *
 * The PRIVMSG command is used to send a private message to a user or a channel.
 * The recipient is specified as an argument to the command, followed by the message text.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of command arguments.
 */
void	PRIVMSG::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		Reply::sendRPL(server, client, ERR::ERR_NORECIPIENT(client->getNickname(), args[0]), SERVER);
	} else if (args.size() == 2) {
		if (args[1][0] == ':') {
			Reply::sendRPL(server, client, ERR::ERR_NORECIPIENT(client->getNickname(), args[0]), SERVER);
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOTEXTTOSEND(client->getNickname()), SERVER);
		}
	} else {
		vector<string>	targets = _splitChannels(args[1]);

		for (size_t i = 0; i < targets.size(); i++) {
			if (targets[i][0] == '#') {
				_sendToChannel(server, client, targets[i], args[2]);
			} else {
				_sendToClient(server, client, targets[i], args[2]);
			}
		}
	}
}
