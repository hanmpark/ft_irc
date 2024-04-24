#pragma once

# include "ACommand.hpp"

class KICK : public ACommand {
public:
	KICK();
	~KICK();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
