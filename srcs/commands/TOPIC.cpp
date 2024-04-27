#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

void	TOPIC::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Channel *channel = server.getChannelList().getChannelByName(args[1]);
		if (channel) {
			if (args.size() == 2) { // get TOPIC
				if (channel->getTopic().empty()) { // no topic
					RPL::sendRPL(server, client, IRCReplies::RPL_NOTOPIC(client->getNickname(), args[1]), SERVER);
				} else { // topic exists
					if (channel->getUsers().getClientByFd(client->getFd())) { // client is in channel
						RPL::sendRPL(server, client, IRCReplies::RPL_TOPIC(client->getNickname(), args[1], channel->getTopic()), SERVER);
					} else { // client is not in channel
						RPL::sendRPL(server, client, IRCErrors::ERR_NOTONCHANNEL(client->getNickname(), args[1]), SERVER);
					}
				}
			} else { // set TOPIC
				if (channel->getModes() & Channel::TOPIC) { // check if client is operator to set TOPIC
					if (channel->getOperators().getClientByFd(client->getFd()) == NULL) {
						RPL::sendRPL(server, client, IRCErrors::ERR_CHANOPRIVSNEEDED(client->getNickname(), args[1]), SERVER);
						return;
					}
					channel->setTopic(args[2]);
					RPL::sendRPL(server, client, "TOPIC " + args[1] + " :" + args[2], CLIENT);
				}
			}
		} else {
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), args[1]), SERVER);
		}
	}
}
