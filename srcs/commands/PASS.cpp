#include "Command.hpp"

void	Command::PASS(Client &client) {
	if (_arguments.empty()) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NEEDMOREPARAMS
	} else if (client.getRegistered() == true) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_ALREADYREGISTERED
	} else if (_arguments[0] != _password) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_PASSWDMISMATCH
		throw exception();
	} else {
		client.setRegistered(true);
		_arguments.clear();
	}
}
