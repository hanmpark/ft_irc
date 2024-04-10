#include "Client.hpp"

/* Constructors / Destructors */

Client::Client() : _fd(0) {}

Client::~Client() {}

Client::Client(int fd, string const &nickname, string const &username) :	_fd(fd), \
																			_nickname(nickname), \
																			_username(username), \
																			_ipAddr("") {}

/* Getters */

int	Client::getFd() const {
	return _fd;
}

string	Client::getNickname() const {
	return _nickname;
}

string	Client::getUsername() const {
	return _username;
}

string	Client::getIpAddr() const {
	return _ipAddr;
}

/* Setters */

void	Client::setFd(int fd) {
	_fd = fd;
}

void	Client::setNickname(string const &nickname) {
	_nickname = nickname;
}

void	Client::setUsername(string const &username) {
	_username = username;
}

void	Client::setIpAddr(string const &ipAddr) {
	_ipAddr = ipAddr;
}
