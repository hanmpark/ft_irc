#include "channel/ChannelList.hpp"

ChannelList::ChannelList() {}

ChannelList::~ChannelList() {
	for (vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		delete *it;
	}
	_channels.clear();
}

void	ChannelList::addChannel(Channel *channel) {
	_channels.push_back(channel);
}

void	ChannelList::removeChannel(Channel *channel) {
	for (vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if (*it == channel) {
			delete *it;
			_channels.erase(it);
			break;
		}
	}
}

Channel	*ChannelList::getChannel(string const &name) const {
	for (vector<Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}
	return NULL;
}

vector<Channel*>	ChannelList::getChannelsFromClient(Client *client) {
	vector<Channel*>	channels;

	for (vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if ((*it)->getClientsList().getClient(client->getNickname())) {
			channels.push_back(*it);
		}
	}
	return channels;
}
