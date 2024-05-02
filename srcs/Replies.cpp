#include <sys/socket.h>

#include "Replies.hpp"

/**
 * @brief Finds the appropirate prefix for a reply based on the server or client side.
 *
 * @param server Reference to the Server object.
 * @param client Pointer to the Client object.
 * @param side Specifies the side of the communication (SERVER or CLIENT).
 *
 * @return A string containing the appropriate prefix.
 */
string const	Reply::findPrefix(Server &server, Client *client, e_side const &side) {
	string	prefix = ":";

	if (side == SERVER) {
		prefix += server.getName() + " ";
	} else if (side == CLIENT) {
		prefix += client->getNickname() + "!~" + client->getUsername() + "@" + client->getHostname() + " ";
	}
	return prefix;
}

/**
 * @brief Sends a reply to a client with a given message.
 *
 * @param server Reference to the Server object.
 * @param client Pointer to the Client object.
 * @param message The message to send to the client.
 * @param side Specifies the side of the communication (SERVER or CLIENT).
 */
void	Reply::sendRPL(Server &server, Client *client, string const &message, e_side const &side) {
	string const	log = Reply::findPrefix(server, client, side) + message;

	send(client->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

/**
 * @brief Sends a reply to a client with a given message and from a specified sender.
 *
 * @param server Reference to the Server object.
 * @param from Pointer to the Client object that is sending the message.
 * @param to Pointer to the Client object that is receiving the message.
 * @param message The message to send to the client.
 * @param side Specifies the side of the communication (SERVER or CLIENT).
 */
void	Reply::sendRPL(Server &server, Client *from, Client *to, string const &message, e_side const &side) {
	string const	log = Reply::findPrefix(server, from, side) + message;

	send(to->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

/**
 * @brief Sends a reply to all clients in a channel with a given message and from a specified sender.
 *
 * @param server Reference to the Server object.
 * @param from Pointer to the Client object that is sending the message.
 * @param to Pointer to the Channel object that contains the recipients of the message.
 * @param message The message to send to the clients.
 * @param side Specifies the side of the communication (SERVER or CLIENT).
 * @param withoutUser If true, the sender will not receive the message.
 */
void	Reply::sendRPL(Server &server, Client *from, Channel *to, string const &message, e_side const &side, bool const &withoutUser) {
	vector<Client*>	clients = to->getClientsList().getClients();
	string const	log = Reply::findPrefix(server, from, side) + message;

	for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++) {
		if ((withoutUser && (*it)->getFd() != from->getFd()) || !withoutUser) {
			send((*it)->getFd(), log.c_str(), log.length(), 0);
			debugLog(log, DEBUG);
		}
	}
}

/**
 * @brief Logs a debug message if DEBUG mode is enabled.
 *
 * @param log The message to log.
 * @param debug A boolean indicating whether debug mode is enabled.
 */
void	Reply::debugLog(string const &log, bool const &debug) {
	if (!debug)
		return;
	cout << ">> " << log;
}

/**
 * @brief Logs a debug message if DEBUG mode is enabled.
 *
 * @param args The vector of strings to log.
 * @param debug A boolean indicating whether debug mode is enabled.
 */
void	Reply::debugLog(vector<string> const &args, bool const &debug) {
	if (!debug)
		return;
	cout << "<< ";
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
}
