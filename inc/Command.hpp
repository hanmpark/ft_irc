#pragma once

# include "IrcIncludes.hpp"
# include "Server.hpp"

# define SPECIAL_CHARACTERS "[]\\`_^{|}"

class Command : public Server {
private:
	typedef void	(Command::*ft)(Client &client);
	map<string, ft>	_commandList;
	vector<string>	_arguments;

	typedef map<string, ft>::iterator	commandIt;
	typedef vector<string>::iterator	argumentsIt;

	void	parseArguments(string buff);

	void	PASS(Client &client);
	bool	isValidNickname(string &nickname) const;
	bool	isNicknameInUse(string const &nickname) const;
	void	NICK(Client &client);
	void	USER(Client &client);

public:
	Command();
	~Command();

	void	selectCommand(Client &client, string buff);
};
