#include "commands/JOIN.hpp"

#include <stdio.h>

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

map<string, string>	JOIN::_tokenizeChannels(Server &server, Client *client, vector<string> &args) const {
	istringstream	ss(args[1]);
	string			channelToken;
	map<string, string>	tokenizedChannels;
	string		keyToken;

	while (getline(ss, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
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

string	getNamesChannel(Channel *channel, vector<Client*> &clients) {
	string	namesChannel;

	for (size_t i = 0; i < clients.size(); i++) {
		namesChannel += (channel->getOperators().getClientByFd(clients[i]->getFd()) != NULL ? "@" : "") + clients[i]->getNickname();
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
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
		return;
	}

	tokenizedChannels = _tokenizeChannels(server, client, args);

	map<string, string>::iterator	it = tokenizedChannels.begin();
	for (; it != tokenizedChannels.end(); it++) {
		Channel	*channel = server.getChannelList().getChannelByName(it->first);

		if (channel == NULL) {
			channel = new Channel(it->first);

			channel->getOperators().addClient(client);
			server.getChannelList().addChannel(it->first, channel);
		}
		else {
			if (channel->getModes() & Channel::KEY) {
				if (channel->getKey() != it->second) {
					RPL::sendRPL(server, client, IRCErrors::ERR_BADCHANNELKEY(client->getNickname(), it->first), SERVER);
					continue ;
				}
			}
			if (channel->getModes() & Channel::INVITE) {
				if (channel->getInvited().getClientByNickname(client->getNickname()) == NULL) {
					RPL::sendRPL(server, client, IRCErrors::ERR_INVITEONLYCHAN(client->getNickname(), it->first), SERVER);
					continue ;
				} else {
					channel->getInvited().removeClient(client);
				}
			}
			if (channel->getModes() & Channel::LIMIT) {
				if (channel->getUsers().getClients().size() >= channel->getLimit()) {
					RPL::sendRPL(server, client, IRCErrors::ERR_CHANNELISFULL(client->getNickname(), it->first), SERVER);
					continue ;
				}
			}
		}

		channel->getUsers().addClient(client);
		RPL::sendRPL(server, client, "JOIN " + it->first + "\r\n", CLIENT);
		string namesChannel = getNamesChannel(channel, channel->getUsers().getClients());
		RPL::sendRPL(server, client, IRCReplies::RPL_NAMREPLY(client->getNickname(), it->first, namesChannel), SERVER);
		RPL::sendRPL(server, client, IRCReplies::RPL_ENDOFNAMES(client->getNickname(), it->first), SERVER);
	}
}
