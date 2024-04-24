#include "commands/USER.hpp"

USER::USER(Server &server) : ACommand(server) {}

USER::~USER() {}

void	USER::execute(Client *client, vector<string> &args) const {
	if (args.size() < 5) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return;
	}
	client->setUsername(args[1]);
	client->setRealname(args[4]); // check realname after ":"
}
