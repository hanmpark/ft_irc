#pragma once

#include "IrcIncludes.hpp"

/* Utilities */

template <typename T>
int myAtoi(const T &str) {
	int		res = 0;
	char	rest = 0;

	std::istringstream iss(str);
	iss >> res;
	iss >> res;
	if (iss.fail() || iss >> rest) {
		throw std::runtime_error(ERR_TYPE);
	}

	return res;
}
