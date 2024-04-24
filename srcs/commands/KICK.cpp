#include "commands/KICK.hpp"

KICK::KICK() : ACommand() {}

KICK::~KICK() {}

void	KICK::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
}
