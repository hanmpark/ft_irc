#include "commands/NICK.hpp"

NICK::NICK(Server &server) : ACommand(server) {}

NICK::~NICK() {}

bool	NICK::_isValidNickname(string &nick) const {
	if (nick.empty()) {
		return false;
	}
	size_t	len = (nick.length() > 9 ? 9 : nick.length());
	nick = nick.substr(0, len);
	for (size_t i = 0; i < len; i++) {
		if (i == 0 && (isdigit(nick[0]) || nick[0] == '-' || (!isalpha(nick[0]) && !strchr(SPECIAL_CHARACTERS, nick[0])))) {
			return false;
		} else if (!isalnum(nick[i]) && !strchr(SPECIAL_CHARACTERS, nick[i]) && nick[i] != '-') {
			return false;
		}
	}
	return true;
}

bool	NICK::_isNicknameInUse(vector<Client*> const &clients, int fd, string const &nickname) const {
	for (size_t i = 0; i < clients.size(); i++) {
		if (fd == clients[i]->getFd()) {
			continue;
		} else if (clients[i]->getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

void	NICK::execute(Client *client, vector<string> &args) const {
	if (client->getNickname().empty() && args.size() == 1) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_NONICKNAMEGIVEN());
	} else if (!_isValidNickname(args[1])) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_ERRONEUSNICKNAME(args[1]));
	} else if (_isNicknameInUse(_server.getClientList().getClients(), client->getFd(), args[1])) {
		RPL::sendRPL(_server, client, IRCErrors::ERR_NICKNAMEINUSE(args[1]));
	} else {
		if (!client->getNickname().empty() && client->getNickname() != args[1]) {
			RPL::sendRPL(_server, client, args);
		}
		client->setNickname(args[1]);
	}
}
