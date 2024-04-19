#pragma once

# include "ACommand.hpp"

class PING : public ACommand {
public:
	PING();
	~PING();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
