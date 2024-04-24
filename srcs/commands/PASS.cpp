#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

void	PASS::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
	} else if (client->getRegistered() == true) {
		RPL::sendRPL(server, client, IRCErrors::ERR_ALREADYREGISTRED());
	} else if (args[1] != server.getPassword()) {
		RPL::sendRPL(server, client, IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		client->setGotPasswordRight(true);
	}
}
