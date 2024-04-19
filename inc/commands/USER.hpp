#pragma once

# include "ACommand.hpp"

class USER : public ACommand {
public:
	USER();
	~USER();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
