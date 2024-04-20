#include "commands/NICK.hpp"

NICK::NICK() : ACommand() {}

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

// ERR_NICKNAMEINUSE
bool	NICK::_isNicknameInUse(vector<Client*> const &clients, string const &nickname) const {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i]->getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

void	NICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (client->getNickname().empty() && args.empty()) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NONICKNAMEGIVEN());
	} else if (!_isValidNickname(args[0])) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_ERRONEUSNICKNAME(args[0]));
	} else if (_isNicknameInUse(server.getClients(), args[0])) {
		Server::sendMessage(client->getFd(), IRCErrors::ERR_NICKNAMEINUSE(args[0]));
	} else {
		if (client->getNickname().empty()) {
			cout << "INFO: Client " << client->getFd() << ": set nickname to " << args[0] << endl; // setting nickname
		} else if (client->getNickname() != args[0]) {
			cout << "INFO: Client " << client->getFd() << ": changed nickname to " << args[0] << endl; // changing nickname
		}
		client->setNickname(args[0]);
		Server::sendMessage(client->getFd(), ": NICK " + client->getNickname() + "\r\n");
	}
}
