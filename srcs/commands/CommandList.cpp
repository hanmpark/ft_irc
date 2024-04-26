#include "commands/CommandList.hpp"
#include "commands/CAP.hpp"
#include "commands/NICK.hpp"
#include "commands/PASS.hpp"
#include "commands/USER.hpp"
#include "commands/PING.hpp"
#include "commands/MODE.hpp"

CommandList::CommandList() {
	_commands["CAP"] = new CAP();
	// _commands["JOIN"] = new JOIN();
	_commands["NICK"] = new NICK();
	_commands["PASS"] = new PASS();
	_commands["USER"] = new USER();
	_commands["PING"] = new PING();
	_commands["MODE"] = new MODE();
	// _commands["PRIVMSG"] = new PRIVMSG();
	// _commands["TOPIC"] = new TOPIC();
}

CommandList::~CommandList() {
	for (commandIt it = _commands.begin(); it != _commands.end(); it++) {
		if (it->second != NULL)
			delete it->second;
	}
	_commands.clear();
}

ACommand	*CommandList::getCommandByName(string const &commandName) const {
	commandIt	it = _commands.find(commandName);

	if (it == _commands.end())
		return NULL;
	return it->second;
}

/*
 TODO:
	- keep whole argument after ":" in one string
*/
vector<string>	CommandList::_split(string const &buffer, string const &limiter) const {
	vector<string>	args;
	size_t			pos = 0;
	size_t			nextPos = 0;

	while ((nextPos = buffer.find(limiter, pos)) != string::npos) {
		string	arg = buffer.substr(pos, nextPos - pos);
		args.push_back(arg);
		pos = nextPos + 1;
	}
	args.push_back(buffer.substr(pos));
	return args;
}

void	CommandList::select(Server &server, Client *client, string const &buffer) {
	vector<string>	args = _split(buffer, " ");
	transform(args[0].begin(), args[0].end(), args[0].begin(), to_upper);

	ACommand	*cmd = getCommandByName(args[0]);
	if (cmd != NULL) {
		RPL::debugLog(args, DEBUG);
		if (!client->getRegistered()) {
			if (args[0] != "CAP" && args[0] != "PASS" && args[0] != "NICK" && args[0] != "USER") {
				RPL::sendRPL(server, client, IRCErrors::ERR_NOTREGISTERED());
				args.clear();
				return;
			}
		}
		if (cmd != NULL) {
			cmd->execute(server, client, args);
		}
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_UNKNOWNCOMMAND(args[0]));
	}
	args.clear();
}
