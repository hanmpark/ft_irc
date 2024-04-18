#include "Command.hpp"

void	Command::PASS(Client &client) {
	if (_arguments.empty()) {
		sendMessage(client.getFd(), IRCErrors::ERR_NEEDMOREPARAMS("PASS"));
	} else if (client.getRegistered() == true) {
		sendMessage(client.getFd(), IRCErrors::ERR_ALREADYREGISTRED());
	} else if (_arguments[0] != _password) {
		cout << "INFO: password mismatch : " << _arguments[0] << endl;
		sendMessage(client.getFd(), IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		cout << "INFO: Client " << client.getFd() << ": got the right password" << endl;
		client.setPassword(true);
		_arguments.clear();
	}
}
