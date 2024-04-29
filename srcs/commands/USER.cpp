#include "commands/USER.hpp"

USER::USER() : ACommand() {}

USER::~USER() {}

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
