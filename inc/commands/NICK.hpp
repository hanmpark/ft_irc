#pragma once

# include "ACommand.hpp"

# define SPECIAL_CHARACTERS "[]\\`_^{|}"

class NICK : public ACommand {
private:
	bool	_isValidNickname(string &nick) const;
	bool	_isNicknameInUse(vector<Client*> const &clients, Client *client, string const &nick) const;
	void	_setNewNick(Client *client, string const &nick) const;

	bool	_checkFirstChar(char const &c) const;

public:
	NICK();
	~NICK();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
