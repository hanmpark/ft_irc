#pragma once

#include "IrcIncludes.hpp"

/* Utilities */

template <typename T>
int myAtoi(const T &str) {
	int		res = 0;
	char	rest = 0;

	istringstream iss(str);
	iss >> res;
	if (iss.fail() || iss >> rest) {
		throw runtime_error(ERR_CONVERT);
	}

	return res;
}
