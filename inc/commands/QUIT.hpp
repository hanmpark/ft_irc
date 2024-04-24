#pragma once

# include "ACommand.hpp"

class QUIT : public ACommand {
public:
	QUIT(Server &server);
	~QUIT();

	void	execute(Client *client, vector<string> &args) const;
};
