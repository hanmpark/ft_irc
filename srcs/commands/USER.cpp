#include "commands/USER.hpp"

USER::USER() : ACommand() {}

USER::~USER() {}

/**
 * @brief Executes the USER command.
 *
 * Syntax: USER <username> <hostname> <servername> <realname>
 *
 * The USER command is used to set a client's username, hostname, server name, and real name.
 * The <username> parameter must be unique across the server,
 * and the <hostname> and <servername> parameters are typically set to the client's IP address and the name of the server, respectively.
 * The <realname> parameter is the client's real name, which may be displayed to other users.
 *
 * @param server The server object reference.
 * @param client The client object pointer that sent the command.
 * @param args The vector of command arguments.
 */
void	USER::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 4) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		if (client->getRegistered() == true) {
			Reply::sendRPL(server, client, ERR::ERR_ALREADYREGISTRED(client->getNickname()), SERVER);
		} else {
			size_t	len = (args[1].length() > 9 ? 9 : args[1].length());
			client->setUsername(args[1].substr(0, len));
			client->setRealname(args[4]);
		}
	}
}
