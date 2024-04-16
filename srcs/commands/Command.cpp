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

char	Command::to_upper(unsigned char c) {
	return static_cast<char>(toupper(c));
}

void	Command::parseArguments(string buff) {
	stringstream	ss(buff);
	string			tmp;

	while (getline(ss, tmp, ' ')) {
		cerr << "tmp: " << tmp << endl; // checking
		if (_arguments.empty()) {
			transform(tmp.begin(), tmp.end(), tmp.begin(), to_upper); // putting the first argument in uppercase to match with _commandList's commands
		}
		_arguments.push_back(tmp);
	}
}

void	Command::selectCommand(Client &client, string buff) {
	buff.erase(buff.find_last_not_of("\n") + 1); // NOT SURE

	parseArguments(buff);
	for (commandIt it = _commandList.begin(); it != _commandList.end(); it++) {
		if (_arguments.front() == it->first) {
			_arguments.erase(_arguments.begin());
			(this->*(it->second))(client);
			return;
		}
	}
	_arguments.clear();
	throw runtime_error("Command not found");
}
