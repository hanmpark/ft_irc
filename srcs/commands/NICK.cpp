#include <cstring>
#include <cctype>

#include "commands/NICK.hpp"

NICK::NICK() : ACommand() {}

NICK::~NICK() {}

/**
 * @brief Checks if the first character of a nickname is valid according to the IRC specifications.
 *
 * @param c The character to check.
 *
 * @return True if the character is valid, false otherwise.
 */
bool	NICK::_checkFirstChar(char const &c) const {
	if (isdigit(c) || c == '-' || c == '#' || c == ':' || (!isalpha(c) && !strchr(SPECIAL_CHARACTERS, c))) {
		return false;
	}
	return true;
}

/**
 * @brief Checks if a given nickname is valid according to the IRC specifications.
 *
 * @param nick The nickname to check.
 *
 * @return True if the nickname is valid, false otherwise.
 */
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

/**
 * @brief Checks if a given nickname is already in use by another client in the server.
 *
 * @param clients The vector of Client pointers representing all the clients currently connected to the server.
 * @param client The Client pointer representing the client who is trying to change their nickname.
 * @param nickname The string representing the new nickname that the client wants to use.
 *
 * @return True if the nickname is already in use by another client, false otherwise.
 */
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

/**
 * @brief Executes the NICK command.
 *
 * Syntax: NICK <new nickname>
 *
 * The NICK command changes the nickname of the client sending the command.
 * The new nickname must be unique and cannot be in use by another client.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param args The vector of arguments passed to the command.
 */
void	NICK::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		Reply::sendRPL(server, client, ERR::ERR_NONICKNAMEGIVEN(client->getNickname()), SERVER);
	} else if (!_isValidNickname(args[1])) {
		Reply::sendRPL(server, client, ERR::ERR_ERRONEUSNICKNAME(client->getNickname(), args[1]), SERVER);
	} else if (_isNicknameInUse(server.getClientsList().getClients(), client, args[1])) {
		Reply::sendRPL(server, client, ERR::ERR_NICKNAMEINUSE(client->getNickname(), args[1]), SERVER);
	} else {
		if (client->getRegistered() && client->getNickname() != args[1]) {
			Reply::sendRPL(server, client, CMD::NICK(args[1]), SERVER);
		}
		client->setNickname(args[1]);
	}
}
