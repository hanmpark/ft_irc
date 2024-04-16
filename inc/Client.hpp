#pragma once

# include "IrcIncludes.hpp"
# include "IRCReplies.hpp"

/* Client class:
 * - Client class is responsible for keeping track of all the
 * information about the client.
 * - It has a private attribute _fd to store the file descriptor
 * of the client.
 */
class Client {
private:
	int		_fd;
	string	_nickname;
	string	_username;
	string	_hostname;
	string	_realname;
	string	_ipAddr;
	string	_command;
	bool	_registered;

public:
	Client();
	~Client();

	Client(int fd, string const &nickname, string const &username);

	/* Accessors */

	int		getFd() const;
	string	getNickname() const;
	string	getUsername() const;
	string	getHostname() const;
	string	getRealname() const;
	string	getIpAddr() const;
	string	getCommand() const;
	bool	getRegistered() const;

	void	setFd(int fd);
	void	setNickname(string const &nickname);
	void	setUsername(string const &username);
	void	setHostname(string const &hostname);
	void	setRealname(string const &realname);
	void	setIpAddr(string const &ipAddr);
	void	setCommand(string const &command);
	void	setRegistered(bool registered);

	void	addToCommand(string const &buffer);
	void	clearCommand();
};
