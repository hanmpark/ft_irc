#include "Command.hpp"

Command::Command() {
	_commandList["CAP"] = NULL;
	_commandList["PASS"] = &PASS;
	_commandList["NICK"] = &NICK;
	_commandList["USER"] = &USER;
}

Command::~Command() {
	_commandList.clear();
	_clients.clear();
}

void	Command::parseArguments(string buff) {
	stringstream	ss(buff);
	string		tmp;

	while (getline(ss, tmp, ' ')) {
		_arguments.push_back(tmp);
	}
}

void	Command::selectCommand(Client &client, string buff) {
	buff.erase(buff.find_last_not_of("\n") + 1);

	for (commandIt it = _commandList.begin(); it != _commandList.end(); it++) {
		if (_arguments.front() == it->first) {
			_arguments.pop_front();
			(this->*(it->second))(client);
			return;
		}
	}
	throw runtime_error("Command not found");
}
