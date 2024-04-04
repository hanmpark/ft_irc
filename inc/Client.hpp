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
		int	_fd;
		std::string	_nickname;
		std::string	_username;
		std::string	_ipAddr;

		Client();
		Client(Client const &src);
		Client	&operator=(Client const &rhs);
	public:
		Client(int fd, std::string const &nickname, std::string const &username);
		~Client();

		/* Accessors */
		int	getFd() const;
		std::string	getNickname() const;
		std::string	getUsername() const;
		std::string	getIpAddr() const;

		void	setIpAddr(std::string const &ipAddr);
};
