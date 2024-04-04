#pragma once

#include "IrcIncludes.hpp"

/* Custom exceptions */

class CustomError : public std::exception {
	private:
		std::string	_msg;
	public:
		CustomError(std::string const &msg) : _msg(msg) {}

		virtual const char *what() const throw() {
			return _msg.c_str();
		}
};

/* Utilities */

template <typename T>
int myAtoi(const T &str) {
	int		res = 0;
	char	rest = 0;

	std::istringstream iss(str);
	iss >> res;
	iss >> res;
	if (iss.fail() || iss >> rest) {
		throw CustomError(ERR_TYPE)
	}

	return res;
}
