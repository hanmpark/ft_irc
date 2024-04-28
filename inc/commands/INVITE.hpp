#pragma once

# include "ACommand.hpp"

class INVITE : public ACommand {
private:
	string const _checkParams(Server &server, Client *client, string const &nick, string const &channelName) const;

public:
	INVITE();
	~INVITE();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
