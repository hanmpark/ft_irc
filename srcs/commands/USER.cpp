#include "Command.hpp"

void	Command::USER(Client &client) {
	if (_arguments.size() < 4) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NEEDMOREPARAMS
		return;
	}
	client.setUsername(_arguments.front());
	_arguments.pop_front();
	send(client.getFd(), KIAN, sizeof(KIAN), 0); // RPL_WELCOME
}
