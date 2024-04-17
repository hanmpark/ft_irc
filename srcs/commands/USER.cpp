#include "Command.hpp"

void	Command::USER(Client &client) {
	if (_arguments.size() < 4) {
		sendMessage(client.getFd(), IRCErrors::ERR_NEEDMOREPARAMS("USER"));
		return;
	}
	client.setUsername(_arguments[0]);
	client.setRealname(_arguments[3]);
}
