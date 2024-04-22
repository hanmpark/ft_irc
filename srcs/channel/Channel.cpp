#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(string const &name) : _name(name) {}

Channel::~Channel() {}

string	Channel::getName() const { return _name; }

string	Channel::getTopic() const { return _topic; }

string	Channel::getKey() const { return _key; }

string	Channel::getCreator() const { return _creator; }

size_t	Channel::getLimit() const { return _limit; }

void	Channel::setCreator(string const &creator) { _creator = creator; }

void	Channel::setTopic(string const &topic) { _topic = topic; }

void	Channel::setKey(string const &key) { _key = key; }

void	Channel::addClient(Client *client) { _users.push_back(client); }

void	Channel::removeClient(Client *client) {
	vector<Client*>::iterator it = find(_users.begin(), _users.end(), client);

	if (it != _users.end())
		_users.erase(it);
}

void	Channel::addOperator(Client *client) { _operators.push_back(client); }

void	Channel::removeOperator(Client *client) {
	vector<Client*>::iterator it = find(_operators.begin(), _operators.end(), client);

	if (it != _operators.end())
		_operators.erase(it);
}

vector<Client*>	&Channel::getUsers() { return _users; }

vector<Client*>	&Channel::getOperators() { return _operators; }
