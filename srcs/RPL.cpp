#include "IRCReplies.hpp"

string	RPL::findPrefix(Server &server, Client *client, e_endpoint const &side) {
	string	prefix = ":";

	if (side == SERVER) {
		prefix += server.getName() + " ";
	} else if (side == CLIENT) {
		prefix += client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() + " ";
	}
	return prefix;
}

// Sends server replies to the client
void	RPL::sendRPL(Server &server, Client *client, string const &message) {
	string	log = RPL::findPrefix(server, client, SERVER) + message;

	send(client->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

void	RPL::sendRPL(Server &server, Client *client, vector<string> const &args) {
	string	log = RPL::findPrefix(server, client, CLIENT);

	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		if (it == args.begin()) {
			log += *it + " :";
		} else {
			log += *it + (it + 1 == args.end() ? "\r\n" : " ");
		}
	}
	send(client->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

void	RPL::debugLog(string const &log, bool const &debug) {
	if (!debug)
		return ;
	cout << ">> " << log;
}

void	RPL::debugLog(vector<string> const &args, bool const &debug) {
	if (!debug)
		return ;
	cout << "<< ";
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
}

void	RPL::debugLog(Server &server, Client *client, vector<string> const &args, e_endpoint const &endPoint, bool const &debug) {
	if (!debug)
		return ;
	string	log = RPL::findPrefix(server, client, endPoint);
	cout << ">> " << log;
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
}
