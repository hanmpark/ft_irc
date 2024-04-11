#include "Command.hpp"

void	Command::PASS(Client &client) {
	if (client.getRegistered() == true) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_ALREADYREGISTRED
	} else if (_arguments.empty()) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NEEDMOREPARAMS
	} else if (_arguments.front() != _password) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_PASSWDMISMATCH
	} else {
		client.setRegistered(true);
		_arguments.pop_front();
	}
}
