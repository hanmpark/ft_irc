#include <sstream>
#include <iostream>

int myAtoi(const char* str) {
	std::istringstream iss(str);
	int res = 0;
	iss >> res;
	if (iss.fail()) {
	}
}
