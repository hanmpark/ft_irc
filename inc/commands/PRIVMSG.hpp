#pragma once

# include "ACommand.hpp"

class PRIVMSG : public ACommand {
private:
	vector<string>	_splitChannels(string const &channelArg) const;
	void			_sendToChannel(Server &server, Client *client, string const &channelName, string const &message) const;
	void			_sendToClient(Server &server, Client *client, string const &ClientNickname, string const &message) const;

public:
	PRIVMSG();
	~PRIVMSG();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
