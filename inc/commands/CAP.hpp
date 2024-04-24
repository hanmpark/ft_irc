#pragma once

# include "ACommand.hpp"

class CAP : public ACommand {
public:
	CAP();
	~CAP();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
