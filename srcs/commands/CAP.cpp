#include "commands/CAP.hpp"

CAP::CAP(Server &server) : ACommand(server) {}

CAP::~CAP() {}

void	CAP::execute(Client *client, vector<string> &args) const {
	static_cast<void>(args);
	static_cast<void>(client);
}
