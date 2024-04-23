#include "PRIVMSG.hpp"

PRIVMSG::PRIVMSG() : ACommand() {}

PRIVMSG::~PRIVMSG() {}


/*
* Possible cases: args[0] = #channel | args[0] = <nickname>
*/
void	PRIVMSG::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2)
		return ;
	string	channelName = "";
	string	nickname = "";
	string	message = "";


	if (args[0].at(0) == '#') {
		// must check if there are multiple channels
		channelName = args[0];
		// tokenize channelName => token[1] = #channel1, token[2] = #channel2
		//split();
		istringstream iss(channelName);
		vector<string>	tokens;
		while (getline(iss, channelName, ',')) {
			tokens.push_back(channelName);
		}
		vector<string>::iterator	it = tokens.begin();
		while (it != tokens.end()) {
			if (server.getChannelByName(*it) == NULL) {
				Server::sendMessage(client->getFd(), IRCErrors::ERR_NOSUCHCHANNEL(*it));
			}
			else {
				message = args[1];
				server.broadcastMessage(*it, message, client->getFd());
			}
		}
		// if (server.getChannelByName(channelName) == NULL) {
		// 	Server::sendMessage(client->getFd(), IRCErrors::ERR_NOSUCHCHANNEL(channelName));
		// }
		// else {
		// 	message = args[1];
		// 	server.broadcastMessage(channelName, message, client->getFd());
		// }
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
