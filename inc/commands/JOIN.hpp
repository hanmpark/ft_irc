#pragma once

# include "ACommand.hpp"

class JOIN : public ACommand {
public:
	JOIN();
	~JOIN();

	void	execute(Server &server, Client *client, vector<string> &args) const;

	map<string, string>	tokenizeChannels(Server &server, Client *client, vector<string> &args) const;
};
