#pragma once

# include "ACommand.hpp"

class MODE : public ACommand {
public:
	MODE();
	~MODE();

	void	execute(Server &server, Client *client, std::vector<std::string> &args) const;
};
