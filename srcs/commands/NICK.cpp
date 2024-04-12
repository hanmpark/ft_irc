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
		if (_clients[i].getNickname() == nickname) {
			return true;
		}
	}
	return false;
}

void	Command::NICK(Client &client) {
	if (client.getNickname().empty() && _arguments.empty()) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NONICKNAMEGIVEN
	} else if (!client.getNickname().empty() && _arguments.empty()) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // send nickname
	} else if (!isValidNickname(_arguments.front())) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_ERRONEUSNICKNAME
	} else if (isNicknameInUse(_arguments.front())) {
		send(client.getFd(), KIAN, sizeof(KIAN), 0); // ERR_NICKNAMEINUSE
	} else {
		if (client.getNickname().empty()) {
			send(client.getFd(), KIAN, sizeof(KIAN), 0); // setting nickname
		} else if (client.getNickname() != _arguments.front()) {
			send(client.getFd(), KIAN, sizeof(KIAN), 0); // changing nickname
		}
		client.setNickname(_arguments.front());
		_arguments.clear();
	}
}
