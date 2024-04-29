#include "commands/PART.hpp"

PART::PART() : ACommand() {}

PART::~PART() {}

vector<string>	PART::_getChannels(Server &server, Client *client, string const &channelArg) const {
	vector<string>	channels;
	istringstream	ssChannel(channelArg);
	string			channelToken;

	while (getline(ssChannel, channelToken, ',')) {
		if (channelToken.at(0) != '#') {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), channelToken), SERVER);
			continue;
		}
		channels.push_back(channelToken);
	}

	return channels;
}

void	PART::execute(Server &server, Client *client, std::vector<std::string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		vector<string> channelNames = _getChannels(server, client, args[1]);

		for (vector<string>::iterator it = channelNames.begin(); it != channelNames.end(); it++) {
			Channel *channel;
			if ((channel = server.getChannelList().getChannel(*it)) != NULL) {
				Reply::sendRPL(server, client, channel, CMD::PART(channel->getName(), (args.size() < 3 ? "" : args[2])), CLIENT, false);
				channel->removeClient(client);
				if (channel->getClientsList().getClients().empty()) {
					server.getChannelList().removeChannel(channel);
				}
			}
		}
	}
}
