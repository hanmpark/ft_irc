#pragma once

#include "IrcIncludes.hpp"

class Client {
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _ipAddr;
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
