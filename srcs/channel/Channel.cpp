#include "channel/Channel.hpp"
#include "client/ClientList.hpp"
#include "Server.hpp"

Channel::Channel() : _modes(NOMODE) {}

Channel::Channel(string const &name) : _name(name), _limit(0), _modes(TOPIC) {}

Channel::~Channel() {}

string	Channel::getName() const { return _name; }

string	Channel::getTopic() const { return _topic; }

string	Channel::getKey() const { return _key; }

size_t	Channel::getLimit() const { return _limit; }

unsigned int	Channel::getModes() const { return _modes; }

ClientList	&Channel::getClientsList() { return _clients; }

ClientList	&Channel::getOperatorsList() { return _operators; }

ClientList	&Channel::getInvitedList() { return _invited; }

void	Channel::addMode(e_modes mode) { _modes |= mode; }

void	Channel::removeMode(e_modes mode) { _modes &= ~mode; }

void	Channel::removeClient(Client *client) {
	if (_clients.getClientByFd(client->getFd())) {
		_clients.removeClient(client);
	}
	if (_operators.getClientByFd(client->getFd())) {
		_operators.removeClient(client);
	}
	if (_invited.getClientByFd(client->getFd())) {
		_invited.removeClient(client);
	}
}

void	Channel::setTopic(string const &topic) { _topic = topic; }

void	Channel::setKey(string const &key) { _key = key; }

void	Channel::setLimit(int limit) { _limit = limit; }
