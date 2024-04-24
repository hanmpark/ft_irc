#include "commands/PASS.hpp"

PASS::PASS(Server &server) : ACommand(server) {}

PASS::~PASS() {}

void	PASS::execute(Client *client, vector<string> &args) const {
	if (args.size() == 1) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
	} else if (client->getRegistered() == true) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_ALREADYREGISTRED());
	} else if (args[1] != _server.getPassword()) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_PASSWDMISMATCH());
		throw exception();
	} else {
		client->setGotPasswordRight(true);
	}
}
