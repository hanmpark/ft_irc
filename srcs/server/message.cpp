#include "Server.hpp"

string	Server::findPrefix(Server &server, int fd, e_endpoint side) {
	string	prefix = ":";

	if (side == SERVER) {
		prefix += server.getName() + " ";
	} else if (side == CLIENT) {
		prefix += server.getClientByFd(fd)->getNickname() + "!" + server.getClientByFd(fd)->getUsername() + "@" + server.getClientByFd(fd)->getHostname() + " ";
	}
	return prefix;
}

// Sends server replies to the client
void	Server::sendRPL(Server &server, int fd, string const &message) {
	string	log = Server::findPrefix(server, fd, SERVER) + message;

	send(fd, log.c_str(), log.length(), 0);
	debugLog(log);
}

void	Server::sendRPL(Server &server, int fd, vector<string> const &args) {
	string	log = Server::findPrefix(server, fd, CLIENT);

	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		if (it == args.begin()) {
			log += *it + " :";
		} else {
			log += *it + (it + 1 == args.end() ? "\r\n" : " ");
		}
	}
	send(fd, log.c_str(), log.length(), 0);
	debugLog(log);
}

void	Server::debugLog(string const &log) {
#ifdef WLOGS
	cout << ">> " << log;
#else
	static_cast<void>(log);
#endif
}

void	Server::debugLog(vector<string> const &args) {
#ifdef WLOGS
	cout << "<< ";
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
#else
	static_cast<void>(args);
#endif
}

void	Server::debugLog(Server &server, int fd, vector<string> const &args, e_endpoint endPoint) {
#ifdef WLOGS
	string	log = Server::findPrefix(server, fd, endPoint);
	cout << ">> " << log;
	for (vector<string>::const_iterator it = args.begin(); it != args.end(); it++) {
		cout << *it << (it + 1 == args.end() ? "" : " ");
	}
	cout << endl;
#else
	static_cast<void>(server);
	static_cast<void>(fd);
	static_cast<void>(args);
#endif
}
