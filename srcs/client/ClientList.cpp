#include "ClientList.hpp"

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
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		delete *it;
	}
	_clients.clear();
}

void	ClientList::addClient(Client *client) {
	_clients.push_back(client);
}

void	ClientList::removeClient(int fd) {
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it)->getFd() == fd) {
			delete *it;
			_clients.erase(it);
			break;
		}
	}
}

Client	*ClientList::getClientByFd(int fd) const {
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it)->getFd() == fd) {
			return *it;
		}
	}
	return NULL;
}

Client	*ClientList::getClientByNickname(string const &nickname) const {
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); it++) {
		if ((*it)->getNickname() == nickname) {
			return *it;
		}
	}
	return NULL;
}

vector<Client *> &ClientList::getClients() { return _clients; }

void	ClientList::closeFileDescriptors() {
	for (size_t i = 0; i < _clients.size(); i++) {
		cout << RED << "Client: " << _clients[i]->getFd() << " Disconnected" << RESET << endl;
		close(_clients[i]->getFd());
	}
}
