#include "Command.hpp"

void	Command::USER(Client &client) {
	if (_arguments.size() < 4) {
		sendMessage(client.getFd(), IRCErrors::ERR_NEEDMOREPARAMS("USER"));
		return;
	}
	client.setUsername(_arguments[0]);
	cout << "INFO: Client " << client.getFd() << ": set username to " << _arguments[0] << endl;
	client.setRealname(_arguments[3]);
	cout << "INFO: Client " << client.getFd() << ": set realname to " << _arguments[3] << endl;
}
