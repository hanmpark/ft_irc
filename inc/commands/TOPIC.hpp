#pragma once

# include "ACommand.hpp"

class TOPIC : public ACommand {
public:
	TOPIC();
	~TOPIC();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
