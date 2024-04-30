#include "client/ClientList.hpp"

#define YELLOW	"\033[1;33m"
#define RESET	"\033[0m"

ClientList::ClientList() {}

ClientList::ClientList(ClientList const &copy) {
	*this = copy;
}

ClientList	&ClientList::operator=(ClientList const &rhs) {
	if (this != &rhs) {
		_clients = rhs._clients;
	}
	return *this;
}

ClientList::~ClientList() {
	_clients.clear();
}

void	ClientList::addClient(Client *client) {
	_clients.push_back(client);
}

void	ClientList::removeClient(Client *client) {
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (*it == client) {
			_clients.erase(it);
			break;
		}
	}
}

void	ClientList::deleteClient(Client *client) {
	if (!client)
		return ;
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (client && *it == client) {
			cout << YELLOW "Client " << (client->getNickname().empty() ? "*" : client->getNickname()) << " disconnected" RESET << endl;
			delete *it;
			(*it)->closeFd();
			_clients.erase(it);
			break;
		}
	}
}

Client	*ClientList::getClient(int fd) const {
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it)->getFd() == fd) {
			return *it;
		}
	}
	return NULL;
}

Client	*ClientList::getClient(string const &nickname) const {
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it)->getNickname() == nickname) {
			return *it;
		}
	}
	return NULL;
}

vector<Client *>	&ClientList::getClients() { return _clients; }
