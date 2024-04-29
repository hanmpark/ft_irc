#include "commands/CommandList.hpp"
#include "commands/CAP.hpp"
#include "commands/INVITE.hpp"
#include "commands/JOIN.hpp"
#include "commands/KICK.hpp"
#include "commands/MODE.hpp"
#include "commands/NICK.hpp"
#include "commands/PASS.hpp"
#include "commands/PING.hpp"
#include "commands/PRIVMSG.hpp"
#include "commands/QUIT.hpp"
#include "commands/TOPIC.hpp"
#include "commands/USER.hpp"

CommandList::CommandList() {
	_commands["CAP"] = new CAP();
	_commands["INVITE"] = new INVITE();
	_commands["JOIN"] = new JOIN();
	_commands["KICK"] = new KICK();
	_commands["MODE"] = new MODE();
	_commands["NICK"] = new NICK();
	_commands["PASS"] = new PASS();
	_commands["PING"] = new PING();
	_commands["PRIVMSG"] = new PRIVMSG();
	_commands["QUIT"] = new QUIT();
	_commands["TOPIC"] = new TOPIC();
	_commands["USER"] = new USER();
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

vector<string>	CommandList::_split(string const &buffer, string const &limiter) const {
	vector<string>	args;
	size_t			pos = 0;
	size_t			nextPos = 0;

	while ((nextPos = buffer.find(limiter, pos)) != string::npos) {
		string	arg = buffer.substr(pos, nextPos - pos);
		args.push_back(arg);
		pos = nextPos + 1;
		if (buffer[pos] == ':') {
			pos++;
			break;
		}
	}
	args.push_back(buffer.substr(pos));
	return args;
}

void	CommandList::select(Server &server, Client *client, string const &buffer) {
	vector<string>	args = _split(buffer, " ");

	ACommand	*cmd = getCommandByName(args[0]);
	if (cmd != NULL) {
		Reply::debugLog(args, DEBUG);
		if (!client->getRegistered()) {
			if (args[0] != "CAP" && args[0] != "PASS" && args[0] != "NICK" && args[0] != "USER") {
				Reply::sendRPL(server, client, ERR::ERR_NOTREGISTERED(client->getNickname()), SERVER);
				args.clear();
				return;
			}
		}
		cmd->execute(server, client, args);
	} else {
		Reply::sendRPL(server, client, ERR::ERR_UNKNOWNCOMMAND(client->getNickname(), args[0]), SERVER);
	}
	args.clear();
}
