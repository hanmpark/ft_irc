#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

/*
* In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
* The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
*/

int	scanArgs(int argc, char **argv) {
	try {
		if (argc != 3) {
			throw ArgsError();
		}

		int	port = myAtoi(argv[1]);
		std::string	password = argv[2];
		if (port < 0 || port > 65535) {
			throw PortArgError();
		}
		else if (password.empty()) {
			throw ArgsError();
		}

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << ERR_UNKNOWN << std::endl;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (scanArgs(argc, argv) == 1) {
		return 1;
	}

	try {
		Server	server;

	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
