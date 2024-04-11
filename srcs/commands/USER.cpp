#include "Command.hpp"

void	Command::USER(Client &client) {
	client.setUsername(_arguments.front());
	_arguments.pop_front();
}
