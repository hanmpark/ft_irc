#pragma once

# include <vector>

# include "Channel.hpp"

class ChannelList {
private:
	vector<Channel*>	_channels;

public:
	ChannelList();
	~ChannelList();

	void				addChannel(Channel *channel);
	void				removeChannel(Channel *channel);
	Channel				*getChannel(string const &name) const;
	vector<Channel*>	getChannelsFromClient(Client *client);
};
