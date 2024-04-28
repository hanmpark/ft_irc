#include "ChannelList.hpp"

ChannelList::ChannelList() {}

ChannelList::~ChannelList() {
	for (map<string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		delete it->second;
	}
	_channels.clear();
}

void	ChannelList::addChannel(string const &channelName, Channel *channel) {
	_channels[channelName] = channel;
}

void	ChannelList::removeChannel(string const &name) {
	for (map<string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++) {
		if (it->second->getName() == name) {
			delete it->second;
			_channels.erase(it);
			break;
		}
	}
}

Channel	*ChannelList::getChannelByName(string const &name) const {
	for (map<string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); it++) {
		if (it->second->getName() == name) {
			return it->second;
		}
	}
	return NULL;
}

vector<Channel*>	ChannelList::getChannelsFromClient(Client *client) const{
	vector<Channel*>	channels;
	map<string, Channel*>::const_iterator	it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (it->second->getUsers().getClientByNickname(client->getNickname())) {
			channels.push_back(it->second);
		}
	}
	return channels;
}
