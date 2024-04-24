#pragma once

# include "ACommand.hpp"

class CAP : public ACommand {
public:
	CAP(Server &server);
	~CAP();

	void	execute(Client *client, vector<string> &args) const;
};
