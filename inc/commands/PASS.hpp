#pragma once

# include "ACommand.hpp"

class PASS : public ACommand {
public:
	PASS();
	~PASS();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
