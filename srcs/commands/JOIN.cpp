# include <sstream>

#include "commands/JOIN.hpp"

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

/**
 * @brief Tokenizes the channel names and their corresponding keys from the input arguments.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of input arguments.
 *
 * @return A map containing the tokenized channel names and their corresponding keys.
 */
map<string, string>	JOIN::_tokenizeChannels(Server &server, Client *client, vector<string> &args) const {
	map<string, string>	tokenizedChannels;
	istringstream		ssChannel(args[1]);
	string				channelToken;

	while (getline(ssChannel, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
			continue;
		}
		tokenizedChannels.insert(make_pair(channelToken, ""));
	}

	if (args.size() == 3) {
		map<string, string>::iterator	it = tokenizedChannels.begin();
		istringstream					ssKey(args[2]);
		string							keyToken;

		while (it != tokenizedChannels.end() && getline(ssKey, keyToken, ',')) {
			it->second = keyToken;
			it++;
		}
	}
	return tokenizedChannels;
}

/**
 * @brief Generates a string containing the nicknames of all clients in a given channel,
 * prefixed with an "@" symbol if the client is an operator in the channel.
 * The nicknames are separated by a single space.
 *
 * @param channel The channel to generate the names string for.
 * @param clients A vector of client pointers in the channel.
 *
 * @return A string containing the nicknames of all clients in the channel, prefixed with an "@" symbol if the client is an operator in the channel. The nicknames are separated by a single space.
 */
string const	JOIN::_getNamesChannel(Channel *channel, vector<Client*> const &clients) const {
	string	namesChannel;

	for (size_t i = 0; i < clients.size(); i++) {
		namesChannel += (channel->getOperatorsList().getClient(clients[i]->getFd()) != NULL ? "@" : "") + clients[i]->getNickname();
		if (i + 1 < clients.size())
			namesChannel += " ";
	}
	return namesChannel;
}

/**
 * @brief Sends a JOIN message to the client and adds the client to the channel's client list.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param channel The channel object pointer.
 */
void	JOIN::_sendJOIN(Server &server, Client *client, Channel *channel) const {
	string const	namesChannel = _getNamesChannel(channel, channel->getClientsList().getClients());

	channel->getClientsList().addClient(client);
	Reply::sendRPL(server, client, channel, CMD::JOIN(channel->getName()), CLIENT, false);
	if (!channel->getTopic().empty())
		Reply::sendRPL(server, client, RPL::RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopic()), SERVER);
	Reply::sendRPL(server, client, RPL::RPL_NAMREPLY(client->getNickname(), channel->getName(), namesChannel), SERVER);
	Reply::sendRPL(server, client, RPL::RPL_ENDOFNAMES(client->getNickname(), channel->getName()), SERVER);
}

/**
 * @brief Checks if a client can join a channel.
 *
 * @param server The server object.
 * @param client The client object.
 * @param channelName The name of the channel to join.
 * @param key The key to join the channel, if required.
 *
 * @return The channel object if the client can join, NULL otherwise.
 */
Channel	*JOIN::_checkChannel(Server &server, Client *client, string const &channelName, string const &key) const {
	Channel	*channel = server.getChannel(channelName);

	if (channel == NULL) {
		channel = new Channel(channelName);
		channel->getOperatorsList().addClient(client);
		server.getChannelList().addChannel(channel);
	} else {
		if (channel->getModes() & Channel::KEY) {
			if (channel->getKey() != key) {
				Reply::sendRPL(server, client, ERR::ERR_BADCHANNELKEY(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
		if (channel->getModes() & Channel::LIMIT) {
			if (channel->getClientsList().getClients().size() >= channel->getLimit()) {
				Reply::sendRPL(server, client, ERR::ERR_CHANNELISFULL(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
		if (channel->getModes() & Channel::INVITE) {
			if (channel->getInvitedList().getClient(client->getFd())) {
				channel->getInvitedList().removeClient(client);
			} else {
				Reply::sendRPL(server, client, ERR::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
	}
	return channel;
}

/**
 * @brief Executes the JOIN command.
 *
 * Syntax: JOIN <channel>{,<channel>} [<key>{,<key>}]
 *
 * This command allows a client to join one or more channels.
 * The channel names are specified as a comma-separated list, and the optional keys are also specified as a comma-separated list.
 * If a key is provided for a channel, it must match the key set for that channel if the mode +k is activated.
 *
 * @param server The server object.
 * @param client The client object.
 * @param args The command arguments.
 */
void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		map<string, string>	tokenizedChannels = _tokenizeChannels(server, client, args); // channelName, key

		for (map<string, string>::iterator it = tokenizedChannels.begin(); it != tokenizedChannels.end(); it++) {
			Channel	*channel;
			if ((channel = _checkChannel(server, client, it->first, it->second)) != NULL)
				_sendJOIN(server, client, channel);
		}
	}
}
