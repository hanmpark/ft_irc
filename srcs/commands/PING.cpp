#include "commands/PING.hpp"

PING::PING() : ACommand() {}

PING::~PING() {}

/**
 * @brief Executes the PING command.
 *
 * Syntax: PING <server>
 *
 * The PING command is used to test the connection between the client and the server.
 * The server responds with a PONG message containing the server name.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of arguments passed to the command.
 */
void	PING::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		Reply::sendRPL(server, client, CMD::PING(server.getName(), args[1]), SERVER);
	}
}
