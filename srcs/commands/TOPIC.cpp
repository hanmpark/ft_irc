#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

/**
 * @brief Retrieves the topic of a channel and sends it to the client that requested it.
 *
 * @param server The server object reference.
 * @param client The client object pointer that sent the request.
 * @param channel The channel object pointer.
 */
void	TOPIC::_getTopic(Server &server, Client *client, Channel *channel) const {
	if (channel->getTopic().empty()) {
		Reply::sendRPL(server, client, RPL::RPL_NOTOPIC(client->getNickname(), channel->getName()), SERVER);
	} else {
		if (channel->getClientsList().getClient(client->getFd())) {
			Reply::sendRPL(server, client, RPL::RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopic()), SERVER);
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOTONCHANNEL(client->getNickname(), channel->getName()), SERVER);
		}
	}
}

/**
 * @brief Sets the topic of a channel.
 *
 * @param server The server object reference.
 * @param client The client object pointer that sent the TOPIC command.
 * @param channel The channel object pointer.
 * @param topic The new topic string.
 */
void	TOPIC::_setTopic(Server &server, Client *client, Channel *channel, string const &topic) const {
	if (!channel->getClientsList().getClient(client->getFd())) {
		Reply::sendRPL(server, client, ERR::ERR_NOTONCHANNEL(client->getNickname(), channel->getName()), SERVER);
	} else if (channel->getModes() & Channel::TOPIC) {
		if (channel->getOperatorsList().getClient(client->getFd()) == NULL) {
			Reply::sendRPL(server, client, ERR::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName()), SERVER);
		} else {
			channel->setTopic(topic);
			Reply::sendRPL(server, client, channel, CMD::TOPIC(channel->getName(), topic), CLIENT, false);
		}
	} else {
		channel->setTopic(topic);
		Reply::sendRPL(server, client, channel, CMD::TOPIC(channel->getName(), topic), CLIENT, false);
	}
}

/**
 * @brief Executes the TOPIC command.
 *
 * Syntax: TOPIC <channel> [<topic>]
 *
 * The TOPIC command is used to set or get the topic of a channel.
 * If the <topic> parameter is provided, it sets the topic of the channel to the specified value.
 * If the <topic> parameter is not provided, it retrieves the current topic of the channel.
 *
 * @param server The server object reference.
 * @param client The client object pointer that sent the command.
 * @param args The vector of command arguments.
 */
void	TOPIC::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel	*channel = server.getChannel(args[1]);

		if (channel) {
			if (args.size() == 2) {
				_getTopic(server, client, channel);
			} else {
				_setTopic(server, client, channel, args[2]);
			}
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), args[1]), SERVER);
		}
	}
}
