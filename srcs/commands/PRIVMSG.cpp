#include "PRIVMSG.hpp"

PRIVMSG::PRIVMSG() : ACommand() {}

PRIVMSG::~PRIVMSG() {}


/*
* Possible cases: args[0] = #channel | args[0] = <nickname>
*/
void	PRIVMSG::execute(Server &server, Client *client, vector<string> &args) const {
	string	channelName = "";
	string	nickname = "";
	string	message = "";

	if (args[0].at(0) == '#') {
		channelName = args[0];
		if (server.getChannelByName(channelName) == NULL) {
			Server::sendMessage(client->getFd(), IRCErrors::ERR_NOSUCHCHANNEL(channelName));
		}
		else {
			message = args[1];
			server.broadcastMessage(channelName, message, client->getFd());
		}
	}
	else {
		nickname = args[0];
		if (server.getClientByNickname(nickname) == NULL) {
			Server::sendMessage(client->getFd(), IRCErrors::ERR_NOSUCHNICK(nickname));
		}
		else {
			// send the message to the client.
			message = args[1];
			server.sendPrivMessage(nickname, message, client->getFd());
		}
	}
}
