#include "commands/JOIN.hpp"
#include "Channel.hpp"
#include "IRCReplies.hpp"

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return ;
	}
	else if (args[1][0] != '#') {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_BADCHANMASK());
		return ;
	}
	Channel	*channel = server.getChannelByName(args[1]);
	if (channel == NULL) {
		Channel	*newChannel = new(nothrow) Channel(args[1]);
		if (newChannel == NULL)
			return ;
		
	}
}
