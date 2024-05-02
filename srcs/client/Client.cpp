#include <unistd.h>

#include "client/Client.hpp"

Client::Client() : _fd(0), _hostname("127.0.0.1"), _gotPasswordRight(false), _registered(false) {}

Client::~Client() {}

Client::Client(int fd, string const &nickname, string const &username) : _fd(fd), _nickname(nickname), _username(username), _registered(false) {}

int	Client::getFd() const { return _fd; }

string	Client::getNickname() const { return _nickname; }

string	Client::getUsername() const { return _username; }

string 	Client::getHostname() const { return _hostname; }

string	Client::getIpAddr() const { return _ipAddr; }

string	Client::getBuffer() const { return _buffer; }

bool	Client::getGotPasswordRight() const { return _gotPasswordRight; }

bool	Client::getRegistered() const { return _registered; }

void	Client::setFd(int const &fd) { _fd = fd; }

void	Client::setNickname(string const &nickname) { _nickname = nickname; }

void	Client::setUsername(string const &username) { _username = username; }

void	Client::setRealname(string const &realname) { _realname = realname; }

void	Client::setIpAddr(string const &ipAddr) { _ipAddr = ipAddr; }

void	Client::setGotPasswordRight(bool const &password) { _gotPasswordRight = password; }

void	Client::setRegistered(bool const &registered) { _registered = registered; }

void	Client::addToBuffer(string const &buffer) { _buffer += buffer; }

void	Client::clearBuffer() { _buffer.clear(); }

void	Client::closeFd() { close(_fd); }
