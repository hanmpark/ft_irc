#pragma once

# include "ACommand.hpp"

# define CAP_LS_RETURN "CAP * LS :\r\n"

class CAP : public ACommand {
public:
	CAP();
	~CAP();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
