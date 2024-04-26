#include "commands/JOIN.hpp"

#include <stdio.h>

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

map<string, string>	JOIN::tokenizeChannels(Server &server, Client *client, vector<string> &args) const {
	istringstream	ss(args[1]);
	string			channelToken;
	map<string, string>	tokenizedChannels;
	string		keyToken;

	while (getline(ss, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(channelToken));
			continue ;
		}
		tokenizedChannels.insert(pair<string, string>(channelToken, ""));
	}

	// check if there is a key for the channel
	if (args.size() == 3) {
		map<string, string>::iterator	it = tokenizedChannels.begin();
		istringstream	ss(args[2]);

		while (it != tokenizedChannels.end() && getline(ss, keyToken, ',')) {
			it->second = keyToken;
			it++;
		}
	}

	return tokenizedChannels;
}

string	getNamesChannel(vector<Client*> &clients) {
	string	namesChannel;

	for (size_t i = 0; i < clients.size(); i++) {
		namesChannel += clients[i]->getNickname();
		if (i + 1 < clients.size())
			namesChannel += " ";
	}
	return namesChannel;
}


/*
	JOIN #caca
	:KQUE!~KQUE@157a-3894-3542-9a96-157a.129.62.ip JOIN :#caca
	:bitcoin.uk.eu.dal.net 353 KQUE = #caca :KQUE kquetat-1 @kquetat- 
	:bitcoin.uk.eu.dal.net 366 KQUE #caca :End of /NAMES list.
*/
void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	map<string, string>	tokenizedChannels; // channelName, key

	if (args.size() < 2) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return;
	}

	tokenizedChannels = tokenizeChannels(server, client, args);

	map<string, string>::iterator	it = tokenizedChannels.begin();
	for (; it != tokenizedChannels.end(); it++) {
		Channel	*channel = server.getChannelList().getChannelByName(it->first);

		if (channel == NULL) {
			channel = new Channel(it->first);

			channel->getUsers().addClient(client);
			channel->getOperators().addClient(client);
			server.getChannelList().addChannel(it->first, channel);
		}
		else {
			if (channel->getModes() & Channel::INVITE) {
				if (channel->getInvited().getClientByNickname(client->getNickname()) == NULL) {
					RPL::sendRPL(server, client, IRCErrors::ERR_INVITEONLYCHAN(it->first));
					continue ;
				} else {
					channel->getInvited().removeClient(client);
				}
			}
			if (channel->getModes() & Channel::KEY) {
				if (channel->getKey() != it->second) {
					RPL::sendRPL(server, client, IRCErrors::ERR_BADCHANNELKEY(it->first));
					continue ;
				}
			}
			if (channel->getModes() & Channel::LIMIT) {
				if (channel->getUsers().getClients().size() >= channel->getLimit()) {
					RPL::sendRPL(server, client, IRCErrors::ERR_CHANNELISFULL(it->first));
					continue ;
				}
			}
		}

		RPL::sendRPL(server, client, "JOIN :" + it->first);
		string namesChannel = getNamesChannel(channel->getUsers().getClients());
		RPL::sendRPL(server, client, IRCReplies::RPL_NAMREPLY(client->getNickname(), it->first, namesChannel));
		RPL::sendRPL(server, client, IRCReplies::RPL_ENDOFNAMES(client->getNickname(), it->first));
	}
// 	if (args[0].empty() || args.size() > 2) {
// 		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
// 		return ;
// 	}
// 	// find if within args[1] there is more than one channel.
// 	// args[0] = /JOIN | args[1] = #channel1,#channel2,#channel3 | args[2] = key | args[2] = key,key2,key3

// 	istringstream	ss(args[0]);
// 	string			channelToken; // tokenize the channels

// 	while (getline(ss, channelToken, ',')) {
// 		cout << GREEN "channelToken: " << RESET << channelToken << endl;
// 		if (channelToken.at(0) != '#') {
// 			Server::sendMessage(client->getFd(), IRCErrors::ERR_BADCHANMASK());
// 			return ;
// 		}
// 		// Channel	*channel = server.getChannelByName(channelToken);
// 		if (channel == NULL) {
// 			Channel	*newChannel = new(nothrow) Channel(channelToken);
// 			if (newChannel == NULL)
// 				return ;
// 			newChannel->setCreator(client->getNickname());
// 			newChannel->addOperator(client);
// 			newChannel->addClient(client);
// 			// server.addChannel(channelToken, newChannel);
// 		}
// 		else {
// 			if (channel->getLimit() != 0 && channel->getUsers().size() >= channel->getLimit()) {
// 				// Server::sendMessage(client->getFd(), IRCErrors::ERR_CHANNELISFULL(channelToken));
// 				return ;
// 			}
// 			channel->addClient(client);
// 		}
// 	}

// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_NAMREPLY(client->getNickname(), args[1], ""));
// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_ENDOFNAMES(client->getNickname(), args[1]));
// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_CHANNELMODEIS(args[1], ""));

}
