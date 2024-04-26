#pragma once

# include "Channel.hpp"

class ChannelList {
private:
	map<string, Channel*>	_channels;

public:
	ChannelList();
	ChannelList(ChannelList const &copy);
	ChannelList	&operator=(ChannelList const &rhs);
	~ChannelList();

	void	addChannel(string const &channelName, Channel *channel);
	void	removeChannel(string const &name);
	Channel	*getChannelByName(string const &name) const;
};
