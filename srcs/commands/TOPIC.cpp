#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

void	TOPIC::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		throw IRCErrors::ERR_NEEDMOREPARAMS(args[0]);
	}
	Channel *channel = server.getChannelList().getChannelByName(args[1]);
	if (channel) {
		if (args.size() == 2) {
			if (channel->getTopic().empty()) {
				// NO TOPIC
			} else {
				// TOPIC
			}
		} else {
			if (channel->getModes() & Channel::TOPIC) {
				throw IRCErrors::ERR_CHANOPRIVSNEEDED(args[1]);
			} else {
				channel->setTopic(args[2]);
				RPL::sendRPL(server, client, args);
			}
		}
	} else {
		throw IRCErrors::ERR_NOSUCHCHANNEL(args[1]);
	}
}
