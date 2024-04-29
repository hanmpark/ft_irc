#pragma once

# include "ACommand.hpp"

class MODE : public ACommand {
private:
	typedef bool	(MODE::*modeFunction)(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	map<pair<string, bool>, modeFunction>	_modeMap;
	string const							_modeChars = "itkol";

	bool	INVITE(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	UNINVITE(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	TOPIC(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	UNTOPIC(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	KEY(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	UNKEY(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	OP(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	DEOP(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	LIMIT(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;
	bool	UNLIMIT(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const;

	bool			_addFlagToModeArgs(string const &modeArgs, bool flag) const;
	bool			_checkNumberModeArgs(string const &modeString, size_t modeArgsSize) const;
	vector<string>	_getModeArgs(vector<string> const &args) const;
	void			_applyModeSetting(Server &server, Client *client, Channel *channel, vector<string> &args) const;

	bool			_checkLimitArg(string const &arg) const;

public:
	MODE();
	~MODE();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
