#include "IRCBot.hpp"

bool	isValidArgs(string const &host, string const &port, string const &password) {
	if (host.empty() || port.empty() || password.empty()) {
		return false;
	} else {
		if (host != "localhost" && host != "127.0.0.1") {
			return false;
		} else if (port.find_last_not_of("0123456789") != string::npos || atoi(port.c_str()) < 0 || atoi(port.c_str()) > 65535) {
			return false;
		}
	}
	return true;
}
