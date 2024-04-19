#include "Command.hpp"
#include "Channel.hpp"

void	Command::JOIN(Client *client) {
	if (_arguments.size() < 2) {
		sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS("JOIN"));
		return ;
	}
	//* JOIN #caca1,#caca2,#caca3 => _arguments[0] = #caca1,#caca2,#caca3
	cout << "_arguments[0]: " << _arguments[0] << endl;
	cout << "_arguments[1]: " << _arguments[1] << endl;
}
