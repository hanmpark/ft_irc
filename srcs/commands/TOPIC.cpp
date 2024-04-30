#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

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
