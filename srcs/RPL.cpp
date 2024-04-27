#include "IRCReplies.hpp"

string	RPL::findPrefix(Server &server, Client *client, e_endpoint const &side) {
	string	prefix = ":";

	if (side == SERVER) {
		prefix += server.getName() + " ";
	} else if (side == CLIENT) {
		prefix += client->getNickname() + "!~" + client->getUsername() + "@" + client->getHostname() + " ";
	}
	return prefix;
}

// Sends server replies to the client, usually errors
void	RPL::sendRPL(Server &server, Client *client, string const &message, e_endpoint const &endPoint) {
	string	log = RPL::findPrefix(server, client, endPoint) + message;

	send(client->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

void	RPL::sendRPL(Server &server, Client *from, Client *to, string const &message, e_endpoint const &endPoint) {
	string	log = RPL::findPrefix(server, from, endPoint) + message;

	send(to->getFd(), log.c_str(), log.length(), 0);
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
