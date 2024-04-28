#pragma once

# include "ACommand.hpp"

class JOIN : public ACommand {
private:
	map<string, string>	_tokenizeChannels(Server &server, Client *client, vector<string> &args) const;
	bool				_checkChannel(Server &server, Client *client, Channel *channel, string const &key) const;
	void				_sendJOIN(Server &server, Client *client, Channel *channel) const;

	string const		_getNamesChannel(Channel *channel, vector<Client*> const &clients) const;

public:
	JOIN();
	~JOIN();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
