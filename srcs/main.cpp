#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

/*
* In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
* The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
*/

int	scanArgs(char **argv) {
	try {
		int port = myAtoi(argv[1]);
		std::string server = argv[2];
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << ERR_UNKNOWN << std::endl;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << ERR_ARGS << std::endl;
		return 1;
	}
	else if (scanArgs(argv) == 1) {
		return 1;
	}

	return 0;
}
