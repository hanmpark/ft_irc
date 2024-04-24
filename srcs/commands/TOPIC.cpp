#include "commands/TOPIC.hpp"

TOPIC::TOPIC() : ACommand() {}

TOPIC::~TOPIC() {}

void	TOPIC::execute(Server &server, Client *client, vector<string> &args) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
}
