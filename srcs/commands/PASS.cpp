#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

void	PASS::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else if (client->getRegistered() == true) {
		RPL::sendRPL(server, client, IRCErrors::ERR_ALREADYREGISTRED(client->getNickname()), SERVER);
	} else if (args[1] != server.getPassword()) {
		RPL::sendRPL(server, client, IRCErrors::ERR_PASSWDMISMATCH(client->getNickname()), SERVER);
		throw exception();
	} else {
		client->setGotPasswordRight(true);
	}
}
