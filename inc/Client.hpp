#pragma once

#include "IrcIncludes.hpp"

class Client {
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
	public:
		Client(int fd, std::string nickname, std::string username);
		~Client();

		/* Accessors */
		int getFd() const;
		std::string getNickname() const;
		std::string getUsername() const;
};
