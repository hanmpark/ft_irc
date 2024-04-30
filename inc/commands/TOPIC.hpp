#pragma once

# include "ACommand.hpp"

class TOPIC : public ACommand {
private:
	void	_getTopic(Server &server, Client *client, Channel *channel) const;
	void	_setTopic(Server &server, Client *client, Channel *channel, string const &topic) const;

public:
	TOPIC();
	~TOPIC();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
