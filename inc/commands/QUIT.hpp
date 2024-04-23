#pragma once

# include "ACommand.hpp"

class QUIT : public ACommand {
public:
	QUIT();
	~QUIT();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
