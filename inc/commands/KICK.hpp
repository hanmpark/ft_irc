#pragma once

# include "ACommand.hpp"

class KICK : public ACommand {
private:
	string const	_checkParams(Client *client, Channel *channel, string const &nick) const;

public:
	KICK();
	~KICK();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
