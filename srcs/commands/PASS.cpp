#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

void	PASS::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.empty()) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS("PASS"));
	} else if (client->getRegistered() == true) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_ALREADYREGISTRED());
	} else if (args[0] != server.getPassword()) {
		cout << "INFO: password mismatch : " << args[0] << endl;
		Server::sendMessage(client->getFd(), IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		cout << "INFO: Client " << client->getFd() << ": got the right password" << endl;
		client->setGotPasswordRight(true);
		args.clear();
	}
}
