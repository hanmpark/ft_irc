#pragma once

# include "IrcIncludes.hpp"

/* Client class:
- Client class is responsible for keeping track of all the
information about the client.
- It has a private attribute _fd to store the file descriptor
of the client.
*/
class Client {
	private:
		int		_fd;
		string	_nickname;
		string	_username;
		string	_ipAddr;

	public:
		Client();
		Client(Client const &src);
		Client(int fd, string const &nickname, string const &username);
		Client	&operator=(Client const &rhs);
		~Client();

		/* Accessors */
		int		getFd() const;
		string	getNickname() const;
		string	getUsername() const;
		string	getIpAddr() const;

		/* Mutators */
		void	setFd(int fd);
		void	setNickname(string const &nickname);
		void	setUsername(string const &username);
		void	setIpAddr(string const &ipAddr);
};
