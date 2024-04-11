#include "Command.hpp"

void	Command::NICK(Client &client) {
	client.setNickname(_arguments.front());
	if (client.getNickname().empty() == false) {
		string	KIAN = KIAN::FTKIAN();
		send(client.getFd(), KIAN, sizeof(KIAN), 0);
	}
}
