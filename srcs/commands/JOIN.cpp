#include "commands/JOIN.hpp"

#include <stdio.h>

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

map<string, string>	JOIN::_tokenizeChannels(Server &server, Client *client, vector<string> &args) const {
	map<string, string>	tokenizedChannels;
	istringstream		ssChannel(args[1]);
	string				channelToken;

	while (getline(ssChannel, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
			continue ;
		}
		tokenizedChannels.insert(make_pair(channelToken, ""));
	}

	// check if there is a key for the channel
	if (args.size() == 3) {
		map<string, string>::iterator	it = tokenizedChannels.begin();
		istringstream					ssKey(args[2]);
		string							keyToken;

		while (it != tokenizedChannels.end() && getline(ssKey, keyToken, ',')) {
			it->second = keyToken;
			it++;
		}
	}

	return tokenizedChannels;
}

string const	JOIN::_getNamesChannel(Channel *channel, vector<Client*> const &clients) const {
	string	namesChannel;

	for (size_t i = 0; i < clients.size(); i++) {
		namesChannel += (channel->getOperatorsList().getClientByFd(clients[i]->getFd()) != NULL ? "@" : "") + clients[i]->getNickname();
		if (i + 1 < clients.size()) {
			namesChannel += " ";
		}
	}
	return namesChannel;
}

void	JOIN::_sendJOIN(Server &server, Client *client, Channel *channel) const {
	channel->getClientsList().addClient(client);
	RPL::sendRPL(server, client, IRCCommands::JOIN(channel->getName()), CLIENT);

	string const namesChannel = _getNamesChannel(channel, channel->getClientsList().getClients());
	RPL::sendRPL(server, client, IRCReplies::RPL_NAMREPLY(client->getNickname(), channel->getName(), namesChannel), SERVER);
	RPL::sendRPL(server, client, IRCReplies::RPL_ENDOFNAMES(client->getNickname(), channel->getName()), SERVER);

}

bool	JOIN::_checkChannel(Server &server, Client *client, Channel *channel, string const &key) const {
	if (channel == NULL) {
		channel = new Channel(channel->getName());
		channel->getOperatorsList().addClient(client);
		server.getChannelList().addChannel(channel->getName(), channel);
	} else {
		if (channel->getModes() & Channel::KEY) {
			if (channel->getKey() != key) {
				RPL::sendRPL(server, client, IRCErrors::ERR_BADCHANNELKEY(client->getNickname(), channel->getName()), SERVER);
				return false;
			}
		}
		if (channel->getModes() & Channel::INVITE) {
			if (channel->getInvitedList().getClientByFd(client->getFd())) {
				channel->getInvitedList().removeClient(client);
			} else {
				RPL::sendRPL(server, client, IRCErrors::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()), SERVER);
				return false;
			}
		}
		if (channel->getModes() & Channel::LIMIT) {
			if (channel->getClientsList().getClients().size() >= channel->getLimit()) {
				RPL::sendRPL(server, client, IRCErrors::ERR_CHANNELISFULL(client->getNickname(), channel->getName()), SERVER);
				return false;
			}
		}
	}
	return true;
}

/*
	JOIN #caca
	:KQUE!~KQUE@157a-3894-3542-9a96-157a.129.62.ip JOIN :#caca
	:bitcoin.uk.eu.dal.net 353 KQUE = #caca :KQUE kquetat-1 @kquetat- 
	:bitcoin.uk.eu.dal.net 366 KQUE #caca :End of /NAMES list.
*/
void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		map<string, string>	tokenizedChannels = _tokenizeChannels(server, client, args); // channelName, key

		for (map<string, string>::iterator it = tokenizedChannels.begin(); it != tokenizedChannels.end(); it++) {
			Channel	*channel = server.getChannelList().getChannelByName(it->first);

			if (_checkChannel(server, client, channel, it->second)) {
				_sendJOIN(server, client, channel);
			}
		}
	}

}
