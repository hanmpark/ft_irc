#pragma once

#include "IrcIncludes.hpp"

/* Custom exception */
class TypeConversionError : public std::exception {
public:
	virtual const char *what() const throw() {
		return "Error: Type conversion failed";
	}
};

/* Utilities */
template <typename T>
int myAtoi(const T &str) {
	int res = 0;
	int rest = 0;

	std::istringstream iss(str);
	iss >> res;
	if (iss.fail()) {
		throw TypeConversionError();
	}

	if (iss >> rest) {
		throw TypeConversionError();
	}

	return res;
}
