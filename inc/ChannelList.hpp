#pragma once

# include "Channel.hpp"

class ChannelList {
private:
	map<string, Channel*>	_channels;

public:
	ChannelList();
	~ChannelList();

	void	addChannel(string const &channelName, Channel *channel);
	void	removeChannel(string const &name);
	Channel	*getChannelByName(string const &name) const;
};
