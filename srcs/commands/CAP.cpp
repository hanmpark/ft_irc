#include "commands/CAP.hpp"

CAP::CAP() : ACommand() {}

CAP::~CAP() {}

/**
 * @brief Executes the command CAP which does nothing.
 *
 * @param server the server object.
 * @param client the client that executed the command.
 * @param args the command arguments.
 */
void	CAP::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	static_cast<void>(args);
	static_cast<void>(client);
}
