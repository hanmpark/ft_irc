#pragma once

# include "ACommand.hpp"

class USER : public ACommand {
public:
	USER(Server &server);
	~USER();

	void	execute(Client *client, vector<string> &args) const;
};
