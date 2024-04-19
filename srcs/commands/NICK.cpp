#include "Command.hpp"

// ERR_ERRONEUSNICKNAME
bool	Command::isValidNickname(string &nickname) const {
	if (nickname.empty()) {
		return false;
	}
	size_t	len = nickname.length();
	if (len > 9) {
		len = 9;
	}
	nickname = nickname.substr(0, len);
	if (isdigit(nickname[0]) || nickname[0] == '-' || (!isalpha(nickname[0]) && !strchr(SPECIAL_CHARACTERS, nickname[0]))) {
		return false;
	}
	for (size_t i = 1; i < len; i++) {
		if (!isalnum(nickname[i]) && !strchr(SPECIAL_CHARACTERS, nickname[i]) && nickname[i] != '-') {
			return false;
		}
	}
	return true;
}

// ERR_NICKNAMEINUSE
bool	Command::isNicknameInUse(string const &nickname) const {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

void	Command::NICK(Client *client) {
	if (client->getNickname().empty() && _arguments.empty()) {
		sendMessage(client->getFd(), IRCErrors::ERR_NONICKNAMEGIVEN());
	} else if (!isValidNickname(_arguments[0])) {
		sendMessage(client->getFd(), IRCErrors::ERR_ERRONEUSNICKNAME(_arguments[0]));
	} else if (isNicknameInUse(_arguments[0])) {
		sendMessage(client->getFd(), IRCErrors::ERR_NICKNAMEINUSE(_arguments[0]));
	} else {
		if (client->getNickname().empty()) {
			cout << "INFO: Client " << client->getFd() << ": set nickname to " << _arguments[0] << endl; // setting nickname
		} else if (client->getNickname() != _arguments[0]) {
			cout << "INFO: Client " << client->getFd() << ": changed nickname to " << _arguments[0] << endl; // changing nickname
		}
		client->setNickname(_arguments[0]);
		sendMessage(client->getFd(), ": NICK " + client->getNickname() + "\r\n");
		_arguments.clear();
	}
}
