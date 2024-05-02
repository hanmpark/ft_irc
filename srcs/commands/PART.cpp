#include <sstream>

#include "commands/PART.hpp"

PART::PART() : ACommand() {}

PART::~PART() {}

/**
 * @brief Parses a list of channels separated by commas and returns a vector of channel names.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param channelArg The string containing the list of channels separated by commas.
 *
 * @return A vector of strings containing the channel names.
 */
vector<string>	PART::_splitChannels(Server &server, Client *client, string const &channelArg) const {
	vector<string>	channels;
	istringstream	ssChannel(channelArg);
	string			channelToken;

	while (getline(ssChannel, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
			continue;
		}
		channels.push_back(channelToken);
	}
	return channels;
}

/**
 * @brief Executes the PART command.
 *
 * Syntax: PART <channel> *( "," <channel> ) [<message>]
 *
 * The PART command is used to leave a channel.
 * The <channel> parameter specifies the name of the channel to leave,
 * and the optional <message> parameter can be used to send a message to the channel when leaving.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of arguments passed to the command.
 */
void	PART::execute(Server &server, Client *client, std::vector<std::string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		vector<string> channelNames = _splitChannels(server, client, args[1]);

		for (vector<string>::iterator it = channelNames.begin(); it != channelNames.end(); it++) {
			Channel *channel;

			if ((channel = server.getChannel(*it)) != NULL) {
				if (channel->getClientsList().getClient(client->getFd()) == NULL) {
					Reply::sendRPL(server, client, ERR::ERR_NOTONCHANNEL(client->getNickname(), channel->getName()), SERVER);
				} else {
					Reply::sendRPL(server, client, channel, CMD::PART(channel->getName(), (args.size() < 3 ? "" : args[2])), CLIENT, false);
					channel->removeClient(client);
					if (channel->getClientsList().getClients().empty()) {
						server.getChannelList().removeChannel(channel);
					}
				}
			}
		}
	}
}
