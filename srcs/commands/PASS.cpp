#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

void	PASS::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS("PASS"));
	} else if (client->getRegistered() == true) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_ALREADYREGISTRED());
	} else if (args[1] != server.getPassword()) {
		cout << "INFO: password mismatch : " << args[1] << endl;
		Server::sendMessage(client->getFd(), IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		cout << "INFO: Client " << client->getFd() << ": got the right password" << endl;
		client->setGotPasswordRight(true);
		args.clear();
	}
}
