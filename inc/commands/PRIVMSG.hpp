#pragma once

# include "IrcIncludes.hpp"
# include "ACommand.hpp"

class PRIVMSG : public ACommand {
private:
	string		_target;
	string		_message;

public:
	PRIVMSG();
	~PRIVMSG();

	void	execute(Server &server, Client *client, vector<string> &args) const;
};
