#include "commands/NICK.hpp"

NICK::NICK() : ACommand() {}

NICK::~NICK() {}

bool	NICK::_checkFirstChar(char const &c) const {
	if (isdigit(c) || c == '-' || c == '#' || c == ':' || (!isalpha(c) && !strchr(SPECIAL_CHARACTERS, c))) {
		return false;
	}
	return true;
}

bool	NICK::_isValidNickname(string &nick) const {
	if (nick.empty()) {
		return false;
	}
	size_t	len = (nick.length() > 9 ? 9 : nick.length());
	nick = nick.substr(0, len);
	for (size_t i = 0; i < len; i++) {
		if ((i == 0 && !_checkFirstChar(nick[i])) || (!isalnum(nick[i]) && !strchr(SPECIAL_CHARACTERS, nick[i]) && nick[i] != '-')) {
			return false;
		}
	}
	return true;
}

bool	NICK::_isNicknameInUse(vector<Client*> const &clients, Client *client, string const &nickname) const {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i] == client) {
			continue;
		} else if (clients[i]->getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

void	NICK::_setNewNick(Client *client, string const &nick) const {
	static long	nickNumber = 1;

	stringstream iss;
	string		nickNumberStr;

	iss << nickNumber;
	iss >> nickNumberStr;

	client->setNickname(nick + nickNumberStr);
	nickNumber++;
}

void	NICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (client->getNickname().empty() && args.size() == 1) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NONICKNAMEGIVEN(client->getNickname()), SERVER);
	} else if (!_isValidNickname(args[1])) {
		RPL::sendRPL(server, client, IRCErrors::ERR_ERRONEUSNICKNAME(args[1]), SERVER);
	} else if (_isNicknameInUse(server.getClientList().getClients(), client, args[1])) {
		if (!client->getRegistered()) {
			_setNewNick(client, args[1]);
		} else {
			RPL::sendRPL(server, client, IRCErrors::ERR_NICKNAMEINUSE(args[1]), SERVER);
		}
	} else {
		if (client->getRegistered() && client->getNickname() != args[1]) {
			RPL::sendRPL(server, client, IRCCommands::NICK(args[1]), SERVER);
		}
		client->setNickname(args[1]);
	}
}
