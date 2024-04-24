#pragma once

# include "ACommand.hpp"

# define SPECIAL_CHARACTERS "[]\\`_^{|}"

class NICK : public ACommand {
private:
	bool	_isValidNickname(string &nick) const;
	bool	_isNicknameInUse(vector<Client*> const &clients, int fd, string const &nick) const;

public:
	NICK();
	~NICK();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
