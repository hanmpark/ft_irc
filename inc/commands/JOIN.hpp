#pragma once

# include "ACommand.hpp"

class JOIN : public ACommand {
private:
	map<string, string>	_tokenizeChannels(Server &server, Client *client, vector<string> &args) const;

public:
	JOIN();
	~JOIN();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
