#include "Command.hpp"

void	Command::CAP(Client *client) {
	sendMessage(client.getFd(), "CAP * LS :\r\n");
}
