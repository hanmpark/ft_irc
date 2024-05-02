#include "commands/PASS.hpp"

PASS::PASS() : ACommand() {}

PASS::~PASS() {}

/**
 * @brief Executes the PASS command.
 *
 * Syntax: PASS <password>
 *
 * The PASS command is used to send the password to the server. The password is provided as an argument to the command.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of command arguments.
 */
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
