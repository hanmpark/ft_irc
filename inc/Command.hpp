#pragma once

# include "IrcIncludes.hpp"
# include "IRCReplies.hpp"
# include "Server.hpp"
# include "Client.hpp"

# define SPECIAL_CHARACTERS "[]\\`_^{|}"

class Command : public Server {
private:
	typedef void	(Command::*ft)(Client *client);
	map<string, ft>	_commandsList;
	vector<string>	_arguments;

	typedef map<string, ft>::iterator	commandIt;
	typedef vector<string>::iterator	argumentsIt;

	void	parseArguments(string const &buff);

	void	PASS(Client *client);
	bool	isValidNickname(string &nickname) const;
	bool	isNicknameInUse(string const &nickname) const;
	void	CAP(Client *client);
	void	NICK(Client *client);
	void	USER(Client *client);
	void	JOIN(Client *client);

	Command();

public:
	Command(Server &parent);
	~Command();

	void	selectCommand(Client *client, string const &buff);
};

char	to_upper(unsigned char c);
