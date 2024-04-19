#include "commands/USER.hpp"

USER::USER() : ACommand() {}

USER::~USER() {}

void	USER::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	if (args.size() < 4) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS("USER"));
		return;
	}
	client->setUsername(args[0]);
	cout << "INFO: Client " << client->getFd() << ": set username to " << args[0] << endl;
	client->setRealname(args[3]);
	cout << "INFO: Client " << client->getFd() << ": set realname to " << args[3] << endl;
}
