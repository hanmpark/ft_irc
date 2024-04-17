#include "Command.hpp"

void	Command::PASS(Client &client) {
	if (_arguments.empty()) {
		sendMessage(client.getFd(), IRCErrors::ERR_NEEDMOREPARAMS("PASS"));
	} else if (client.getRegistered() == true) {
		sendMessage(client.getFd(), IRCErrors::ERR_ALREADYREGISTRED());
	} else if (_arguments[0] != _password) {
		sendMessage(client.getFd(), IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		client.setRegistered(true);
		_arguments.clear();
	}
}
