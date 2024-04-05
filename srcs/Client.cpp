#include "Client.hpp"

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

void	Client::setIpAddr(string const &ipAddr) {
	_ipAddr = ipAddr;
}

Client::Client() : _fd(0), _nickname(""), _username(""), _ipAddr("") {

	return ;
}

Client::Client(int fd, string const &nickname, string const &username) : _fd(fd), \
																			_nickname(nickname), \
																			_username(username), \
																			_ipAddr("") {

	return ;
}

Client::~Client() {

	return ;
}

Client::Client(Client const &src) {
	*this = src;
}

Client	&Client::operator=(Client const &rhs) {
	if (this != &rhs) {
		_fd = rhs.getFd();
		_nickname = rhs.getNickname();
		_username = rhs.getUsername();
		_ipAddr = rhs.getIpAddr();
	}
	return *this;
}
