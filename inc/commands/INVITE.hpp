#pragma once

# include "ACommand.hpp"

class INVITE : public ACommand {
public:
	INVITE();
	~INVITE();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
