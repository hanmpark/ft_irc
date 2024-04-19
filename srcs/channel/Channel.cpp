#include "Channel.hpp"

string	Channel::getName() const {
	return _name;
}

string	Channel::getTopic() const {
	return _topic;
}

string	Channel::getKey() const {
	return _key;
}

string	Channel::getCreator() const {
	return _creator;
}

Channel::Channel() {}

Channel::Channel(string const &name) : _name(name) {}

Channel::~Channel() {}
