#pragma once

# include "ACommand.hpp"

class PASS : public ACommand {
public:
	PASS(Server &server);
	~PASS();

	void	execute(Client *client, vector<string> &args) const;
};
