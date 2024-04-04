#pragma once

#include "IrcIncludes.hpp"

/* Custom exceptions */

class TypeConversionError : public std::exception {
public:
	virtual const char *what() const throw() {
		return ERR_TYPE;
	}
};

class ArgsError : public std::exception {
public:
	virtual const char *what() const throw() {
		return ERR_ARGS;
	}
};

class PortArgError : public std::exception {
public:
	virtual const char *what() const throw() {
		return ERR_PORT;
	}
};

class PasswordArgError : public std::exception {
public:
	virtual const char *what() const throw() {
		return ERR_PASS;
	}
};

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
	int res = 0;
	int rest = 0;

	std::istringstream iss(str);
	iss >> res;
	if (iss.fail() || iss >> rest) {
		throw CustomError(ERR_TYPE)
	}

	return res;
}
