#pragma once

# include <iostream>

using namespace std;

class Client {
private:
	int		_fd;
	string	_nickname, _username, _hostname, _realname, _ipAddr, _buffer;
	bool	_gotPasswordRight, _registered;

public:
	Client();
	~Client();

	Client(int fd, string const &nickname, string const &username);

	/* Accessors */

	int		getFd() const;
	string	getNickname() const;
	string	getUsername() const;
	string	getHostname() const;
	string	getIpAddr() const;
	string	getBuffer() const;
	bool	getGotPasswordRight() const;
	bool	getRegistered() const;

	void	setFd(int const &fd);
	void	setNickname(string const &nickname);
	void	setUsername(string const &username);
	void	setRealname(string const &realname);
	void	setIpAddr(string const &ipAddr);
	void	setGotPasswordRight(bool const &password);
	void	setRegistered(bool const &registered);

	void	addToBuffer(string const &buffer);
	void	clearBuffer();
	void	closeFd();
};
