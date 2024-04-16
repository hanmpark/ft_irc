#include "Command.hpp"

void	Command::USER(Client &client) {
	if (_arguments.size() < 4) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NEEDMOREPARAMS
		return;
	}
	client.setUsername(_arguments[0]);
	client.setRealname(_arguments[3]);
	_arguments.clear();
}
