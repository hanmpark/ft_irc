#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

void	TOPIC::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel *channel = server.getChannelList().getChannel(args[1]);
		if (channel) {
			if (args.size() == 2) { // get TOPIC
				if (channel->getTopic().empty()) { // no topic
					Reply::sendRPL(server, client, RPL::RPL_NOTOPIC(client->getNickname(), args[1]), SERVER);
				} else { // topic exists
					if (channel->getClientsList().getClient(client->getFd())) { // client is in channel
						Reply::sendRPL(server, client, RPL::RPL_TOPIC(client->getNickname(), args[1], channel->getTopic()), SERVER);
					} else { // client is not in channel
						Reply::sendRPL(server, client, ERR::ERR_NOTONCHANNEL(client->getNickname(), args[1]), SERVER);
					}
				}
			} else { // set TOPIC
				if (channel->getModes() & Channel::TOPIC) { // check if client is operator to set TOPIC
					if (channel->getOperatorsList().getClient(client->getFd()) == NULL) {
						Reply::sendRPL(server, client, ERR::ERR_CHANOPRIVSNEEDED(client->getNickname(), args[1]), SERVER);
						return;
					}
					channel->setTopic(args[2]);
					Reply::sendRPL(server, client, channel, CMD::TOPIC(args[1], args[2]), CLIENT, false);
				}
			}
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), args[1]), SERVER);
		}
	}
}
