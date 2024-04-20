#include "commands/JOIN.hpp"
#include "Channel.hpp"
#include "IRCReplies.hpp"

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	if (args[1].empty() || args.size() < 2 || args.size() > 3) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	// Can enter multiple channels if separated by a comma
	string	channelName = args[1];
	// find if channelName contains more than one channel
	// args[0] = /JOIN | args[1] = #channel1,#channel2,#channel3 | args[2] = key
	size_t	pos = channelName.find(',');

	if (channelName.at(0) != '#') {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_BADCHANMASK());
		return ;
	}
	Channel	*channel = server.getChannelByName(channelName);
	if (channel == NULL) {
		Channel	*newChannel = new(nothrow) Channel(channelName);
		if (newChannel == NULL)
			return ;
		newChannel->setCreator(client->getNickname());
		newChannel->addOperator(client);
		newChannel->addClient(client);
		server.addChannel(channelName, newChannel);
	}

	Server::sendMessage(client->getFd(), IRCReplies::RPL_NAMREPLY(client->getNickname(), args[1], ""));
	Server::sendMessage(client->getFd(), IRCReplies::RPL_ENDOFNAMES(client->getNickname(), args[1]));
	Server::sendMessage(client->getFd(), IRCReplies::RPL_CHANNELMODEIS(args[1], ""));

}
