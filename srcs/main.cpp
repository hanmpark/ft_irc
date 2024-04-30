#include "Server.hpp"

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define RESET	"\033[0m"

/*
 * In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
 * The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.

// -------------------------------------------------------------------------- //
 TODO: SOCKET RANGE
 TODO: localhost ?
 */
int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << BLUE "Usage: ./ircserv <port> <password>" RESET << endl;
		return 1;
	}
	try {
		Server	server(static_cast<string>(argv[1]), static_cast<string>(argv[2]));
		server.initServer();
		server.runServer();
	} catch (runtime_error &e) {
		cerr << RED "Error: " << e.what() << RESET << endl;
		return 2;
	} catch (...) {
		cerr << RED "An unknown error occured" RESET << endl;
		return 3;
	}

	return 0;
}
