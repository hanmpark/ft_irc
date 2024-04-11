#pragma once

# include "IrcIncludes.hpp"
# include "Server.hpp"

class Command : public Server {
private:
	typedef void	(Command::*ft)(Client &client);
	map<string, ft>	_commandList;
	deque<string>	_arguments;

	typedef map<string, ft>::iterator	commandIt;
	typedef deque<string>::iterator		argumentsIt;

	void	parseArguments(string buff);

	void	PASS(Client &client);
	void	NICK(Client &client);
	void	USER(Client &client);

public:
	Command();
	~Command();

	void	selectCommand(Client &client, string buff);
};
