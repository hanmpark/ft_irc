#include "Command.hpp"

Command::Command(Server &parent) {
	_clients = parent.getClients();
	_password = parent.getPassword();

	_commandsList["CAP"] = &Command::CAP;
	_commandsList["PASS"] = &Command::PASS;
	_commandsList["NICK"] = &Command::NICK;
	_commandsList["USER"] = &Command::USER;
	_commandsList["JOIN"] = &Command::JOIN;
}

Command::~Command() {
	_commandsList.clear();
	_clients.clear();
}

char	to_upper(unsigned char c) {
	return static_cast<char>(toupper(c));
}

/*
 ! This function is not completed yet
*/
void	Command::parseArguments(string const &buff) {
	stringstream	ss(buff);
	string			tmp;

	cout << endl << "DEBUG:" << endl;
	while (getline(ss, tmp, ' ')) {
		cerr << "tmp: " << tmp << endl; // checking
		if (_arguments.empty()) {
			transform(tmp.begin(), tmp.end(), tmp.begin(), to_upper); // putting the first argument in uppercase to match with _commandsList's commands
		}
		_arguments.push_back(tmp);
	}
	cout << endl;
}

void	Command::selectCommand(Client *client, string const &buff) {
	parseArguments(buff);
	// print after pareArguments, the arguments
	for (size_t i = 0; i < _arguments.size(); i++) {
		cout << BLUE "ARGUMENTS[" << i << "]: " << _arguments[i] << RESET << endl;
	}
	commandIt	launch = _commandsList.find(_arguments[0]);
	cout << "INFO: Command " << _arguments[0] << endl;
	if (launch != _commandsList.end() && client->getRegistered()) {
		cout << RED "1: LAUNCHING COMMAND: " << _arguments[0] << RESET << endl;
		_arguments.erase(_arguments.begin());
		(this->*(launch->second))(client);
	} else if (launch != _commandsList.end() && !client->getRegistered()) {
		if (_arguments[0] != "CAP" && _arguments[0] != "PASS" && _arguments[0] != "NICK" && _arguments[0] != "USER") {
			sendMessage(client->getFd(), IRCErrors::ERR_NOTREGISTERED());
		} else {
			_arguments.erase(_arguments.begin());
			if (launch->second != NULL) {
				(this->*(launch->second))(client);
			}
		}
	} else if (launch != _commandsList.end()) {
		cout << RED "3: LAUNCHING COMMAND: " << _arguments[0] << RESET << endl;
		_arguments.erase(_arguments.begin());
		if (launch->second != NULL) {
			(this->*(launch->second))(client);
		}
	} else {
		cout << "FUCK" << endl;
		sendMessage(client->getFd(), IRCErrors::ERR_UNKNOWNCOMMAND(_arguments[0]));
	}
	_arguments.clear();
}