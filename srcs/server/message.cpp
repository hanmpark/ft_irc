#include "Server.hpp"

void	Server::sendMessage(Server &server, int fd, string const &message, e_endpoint side) {
	string	log = ":";

	if (side == SERVER) {
		log += server.getName() + " ";
	} else if (side == CLIENT) {
		log += server.getClientByFd(fd)->getNickname() + "!" + server.getClientByFd(fd)->getUsername() + "@" + server.getClientByFd(fd)->getHostname() + " ";
	}
	log += message;
	send(fd, log.c_str(), log.length(), 0);
	sendDebugLogs(log, SEND);
}

void	Server::sendMessage(Server &server, int fd, vector<string> const &message, e_endpoint side) {
	string	log = ":";

	if (side == SERVER) {
		
	}
}

void	Server::sendDebugLogs(string const &message, e_transmit transmitMode) {
#ifdef WLOGS
	if (transmitMode == RECEIVE) {
		cout << "<< " << message << endl;
	} else if (transmitMode == SEND) {
		cout << ">> " << message << endl;
	}
#endif
}

void	Server::sendDebugLogs(vector<string> const &message) {
#ifdef WLOGS
	cout << "<< ";
	for (size_t i = 0; i < message.size(); i++) {
		cout << message.at(i) << (i == n - 1 ? "" : " ");
	}
	cout << endl;
#endif
}

void	Server::sendDebugLogs(Client *client, vector<string> const &message) {
#ifdef WLOGS
	cout << ">> :" + client->getNickname() + "!" + client->getUsername() + "@" + client->getHostname() << " ";
	for (vector<string>::const_iterator it = message.begin(); it != message.end(); it++) {
		cout << *it << (it + 1 == message.end() ? "" : " ");
	}
#endif
}
