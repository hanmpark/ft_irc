#pragma once

# include "ACommand.hpp"

class PART : public ACommand {
private:
	vector<string>	_splitChannels(Server &server, Client *client, string const &channelArg) const;

public:
	PART();
	~PART();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
