#pragma once

# include "ACommand.hpp"

class PONG : public ACommand {
public:
	PONG();
	~PONG();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
