#pragma once

# include "CAP.hpp"
// # include "JOIN.hpp"
// # include "KICK.hpp"
// # include "MODE.hpp"
# include "NICK.hpp"
# include "PASS.hpp"
# include "PING.hpp"
# include "PONG.hpp"
// # include "PRIVMSG.hpp"
# include "QUIT.hpp"
// # include "TOPIC.hpp"
# include "USER.hpp"

class CommandList {
private:
	map<string, ACommand*>	_commands;

	typedef map<string, ACommand*>::const_iterator	commandIt;

	vector<string>	_splitBuffer(string const &buffer, string const &limiter) const;

public:
	CommandList(Server &server);
	~CommandList();

	ACommand	*getCommandByName(string const &command) const;
	void		select(Server &server, Client *client, string const &buffer);
};

static inline char	to_upper(unsigned char c) {
	return static_cast<char>(toupper(c));
}
