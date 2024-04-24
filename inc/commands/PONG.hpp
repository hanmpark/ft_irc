#pragma once

# include "ACommand.hpp"

class PONG : public ACommand {
public:
	PONG(Server &server);
	~PONG();

	void	execute(Client *client, vector<string> &args) const;
};
