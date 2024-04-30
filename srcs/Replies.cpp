#include "Replies.hpp"

string const	Reply::findPrefix(Server &server, Client *client, e_endpoint const &side) {
	string	prefix = ":";

	if (side == SERVER) {
		prefix += server.getName() + " ";
	} else if (side == CLIENT) {
		prefix += client->getNickname() + "!~" + client->getUsername() + "@" + client->getHostname() + " ";
	}
	return prefix;
}

// Sends server replies to the client, usually errors
void	Reply::sendRPL(Server &server, Client *client, string const &message, e_endpoint const &endPoint) {
	string const	log = Reply::findPrefix(server, client, endPoint) + message;

	send(client->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

void	Reply::sendRPL(Server &server, Client *from, Client *to, string const &message, e_endpoint const &endPoint) {
	string const	log = Reply::findPrefix(server, from, endPoint) + message;

	send(to->getFd(), log.c_str(), log.length(), 0);
	debugLog(log, DEBUG);
}

void	Reply::sendRPL(Server &server, Client *from, Channel *to, string const &message, e_endpoint const &endPoint, bool const &withoutUser) {
	vector<Client*>	clients = to->getClientsList().getClients();
	string const	log = Reply::findPrefix(server, from, endPoint) + message;

	for (vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); it++) {
		if ((withoutUser && (*it)->getFd() != from->getFd()) || !withoutUser) {
			send((*it)->getFd(), log.c_str(), log.length(), 0);
			debugLog(log, DEBUG);
		}
	}
}

void	Reply::debugLog(string const &log, bool const &debug) {
	if (!debug)
		return ;
	cout << ">> " << log;
}

void	Reply::debugLog(vector<string> const &args, bool const &debug) {
	if (!debug)
		return ;
	cout << "<< ";
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
}
