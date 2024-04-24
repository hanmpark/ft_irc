#pragma once

# include "ACommand.hpp"

class PING : public ACommand {
public:
	PING(Server &server);
	~PING();

	void	execute(Client *client, vector<string> &args) const;
};
