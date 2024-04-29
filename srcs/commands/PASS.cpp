#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

void	PASS::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else if (client->getRegistered() == true) {
		Reply::sendRPL(server, client, ERR::ERR_ALREADYREGISTRED(client->getNickname()), SERVER);
	} else if (args[1] != server.getPassword()) {
		Reply::sendRPL(server, client, ERR::ERR_PASSWDMISMATCH(client->getNickname()), SERVER);
		throw exception();
	} else {
		client->setGotPasswordRight(true);
	}
}
