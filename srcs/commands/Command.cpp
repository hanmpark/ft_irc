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

/*
 TODO:
 -	Have to complete this part
*/
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
	parseArguments(buff);
	commandIt	launch = _commandList.find(_arguments[0]);
	if (launch != _commandList.end()) {
		cout << "Command: " << _arguments[0] << endl;
		_arguments.erase(_arguments.begin());
		(this->*(launch->second))(client);
	} else {
		string	unknownCmd = IRCErrors::ERR_UNKNOWNCOMMAND(_arguments[0]);
		send(client.getFd(), unknownCmd.c_str(), sizeof(unknownCmd), 0);
	}
	_arguments.clear();
}
