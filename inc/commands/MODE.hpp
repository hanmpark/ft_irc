#pragma once

# include "ACommand.hpp"

class MODE : public ACommand {
private:
	bool	INVITE(Server &server, Client *client, vector<string> &args) const;
	bool	UNINVITE(Server &server, Client *client, vector<string> &args) const;
	bool	TOPIC(Server &server, Client *client, vector<string> &args) const;
	bool	UNTOPIC(Server &server, Client *client, vector<string> &args) const;
	bool	KEY(Server &server, Client *client, vector<string> &args) const;
	bool	UNKEY(Server &server, Client *client, vector<string> &args) const;
	bool	OP(Server &server, Client *client, vector<string> &args) const;
	bool	DEOP(Server &server, Client *client, vector<string> &args) const;
	bool	LIMIT(Server &server, Client *client, vector<string> &args) const;
	bool	UNLIMIT(Server &server, Client *client, vector<string> &args) const;

	typedef bool	(MODE::*modeFunction)(Server &server, Client *client, vector<string> &args) const;
	map<pair<string, bool>, modeFunction> const	_initModeMap() const;

	bool	_addFlagToModeArgs(string const &modeArgs, bool flag) const;
public:
	MODE();
	~MODE();

	void	execute(Server &server, Client *client, std::vector<std::string> &args) const;
};
