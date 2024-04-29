#include "commands/PRIVMSG.hpp"

PRIVMSG::PRIVMSG() : ACommand() {}

PRIVMSG::~PRIVMSG() {}

vector<string>	PRIVMSG::_splitChannels(string const &channelArg) const {
	string			channelToken;
	vector<string>	channels;
	istringstream	ss(channelArg);

	while (getline(ss, channelToken, ',')) {
		channels.push_back(channelToken);
	}
	return channels;
}

void	PRIVMSG::_sendToChannel(Server &server, Client *client, string const &channelName, string const &message) const {
	Channel	*channel = server.getChannelList().getChannel(channelName);

	if (channel == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelName), SERVER);
	} else {
		if (channel->getClientsList().getClient(client->getFd()) == NULL) {
			Reply::sendRPL(server, client, ERR::ERR_CANNOTSENDTOCHAN(client->getNickname(), channelName), SERVER);
		} else {
			vector<Client*>	clients = channel->getClientsList().getClients();
			for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++) {
				if ((*it)->getFd() != client->getFd()) {
					Reply::sendRPL(server, client, *it, CMD::PRIVMSG(channel->getName(), message), CLIENT);
				}
			}
		}
	}
}

void	PRIVMSG::_sendToClient(Server &server, Client *client, string const &clientNickname, string const &message) const {
	Client	*target = server.getClientList().getClient(clientNickname);

	if (target == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHNICK(client->getNickname(), clientNickname), SERVER);
	} else {
		Reply::sendRPL(server, client, target, CMD::PRIVMSG(target->getNickname(), message), CLIENT);
	}
}

void	PRIVMSG::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		Reply::sendRPL(server, client, ERR::ERR_NORECIPIENT(client->getNickname(), args[0]), SERVER);
	} else if (args.size() == 2) {
		if (args[1][0] == ':') {
			Reply::sendRPL(server, client, ERR::ERR_NORECIPIENT(client->getNickname(), args[0]), SERVER);
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOTEXTTOSEND(client->getNickname()), SERVER);
		}
	} else {
		vector<string>	targets = _splitChannels(args[1]);

		for (size_t i = 0; i < targets.size(); i++) {
			if (targets[i][0] == '#') {
				_sendToChannel(server, client, targets[i], args[2]);
			} else {
				_sendToClient(server, client, targets[i], args[2]);
			}
		}
	}
}
