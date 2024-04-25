#include "Channel.hpp"
#include "ClientList.hpp"

Channel::Channel() {}

Channel::Channel(string const &name) : _name(name), _limit(0), _modes(_modes | TOPIC) {}

Channel::~Channel() {}

string	Channel::getName() const { return _name; }

string	Channel::getTopic() const { return _topic; }

string	Channel::getKey() const { return _key; }

size_t	Channel::getLimit() const { return _limit; }

unsigned int	Channel::getModes() const { return _modes; }

ClientList	&Channel::getUsers() { return _users; }

ClientList	&Channel::getOperators() { return _operators; }

ClientList	&Channel::getInvited() { return _invited; }

void	Channel::setTopic(string const &topic) { _topic = topic; }

void	Channel::setKey(string const &key) { _key = key; }

void	Channel::setLimit(int limit) { _limit = limit; }

void	Channel::addMode(e_modes mode) { _modes |= mode; }

void	Channel::removeMode(e_modes mode) { _modes &= ~mode; }
