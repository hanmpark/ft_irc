# include <sstream>

#include "commands/JOIN.hpp"

JOIN::JOIN() : ACommand() {}

JOIN::~JOIN() {}

map<string, string>	JOIN::_tokenizeChannels(Server &server, Client *client, vector<string> &args) const {
	map<string, string>	tokenizedChannels;
	istringstream		ssChannel(args[1]);
	string				channelToken;

	while (getline(ssChannel, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
			continue;
		}
		tokenizedChannels.insert(make_pair(channelToken, ""));
	}

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
		namesChannel += (channel->getOperatorsList().getClient(clients[i]->getFd()) != NULL ? "@" : "") + clients[i]->getNickname();
		if (i + 1 < clients.size()) {
			namesChannel += " ";
		}
	}
	return namesChannel;
}

void	JOIN::_sendJOIN(Server &server, Client *client, Channel *channel) const {
	channel->getClientsList().addClient(client);
	Reply::sendRPL(server, client, channel, CMD::JOIN(channel->getName()), CLIENT, false);
	if (!channel->getTopic().empty()) {
		Reply::sendRPL(server, client, RPL::RPL_TOPIC(client->getNickname(), channel->getName(), channel->getTopic()), SERVER);
	}

	string const namesChannel = _getNamesChannel(channel, channel->getClientsList().getClients());
	Reply::sendRPL(server, client, RPL::RPL_NAMREPLY(client->getNickname(), channel->getName(), namesChannel), SERVER);
	Reply::sendRPL(server, client, RPL::RPL_ENDOFNAMES(client->getNickname(), channel->getName()), SERVER);
}

Channel	*JOIN::_checkChannel(Server &server, Client *client, string const &channelName, string const &key) const {
	Channel	*channel = server.getChannelList().getChannel(channelName);

	if (channel == NULL) {
		channel = new Channel(channelName);
		channel->getOperatorsList().addClient(client);
		server.getChannelList().addChannel(channel);
	} else {
		if (channel->getModes() & Channel::KEY) {
			if (channel->getKey() != key) {
				Reply::sendRPL(server, client, ERR::ERR_BADCHANNELKEY(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
		if (channel->getModes() & Channel::LIMIT) {
			if (channel->getClientsList().getClients().size() >= channel->getLimit()) {
				Reply::sendRPL(server, client, ERR::ERR_CHANNELISFULL(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
		if (channel->getModes() & Channel::INVITE) {
			if (channel->getInvitedList().getClient(client->getFd())) {
				channel->getInvitedList().removeClient(client);
			} else {
				Reply::sendRPL(server, client, ERR::ERR_INVITEONLYCHAN(client->getNickname(), channel->getName()), SERVER);
				return NULL;
			}
		}
	}
	return channel;
}

/*
	JOIN #caca
	:KQUE!~KQUE@157a-3894-3542-9a96-157a.129.62.ip JOIN :#caca
	:bitcoin.uk.eu.dal.net 353 KQUE = #caca :KQUE kquetat-1 @kquetat- 
	:bitcoin.uk.eu.dal.net 366 KQUE #caca :End of /NAMES list.
*/
void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		map<string, string>	tokenizedChannels = _tokenizeChannels(server, client, args); // channelName, key

		for (map<string, string>::iterator it = tokenizedChannels.begin(); it != tokenizedChannels.end(); it++) {
			Channel	*channel;
			if ((channel = _checkChannel(server, client, it->first, it->second)) != NULL) {
				_sendJOIN(server, client, channel);
			}
		}
	}
}
