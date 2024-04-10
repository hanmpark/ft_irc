#include "IrcIncludes.hpp"
#include "Server.hpp"

/*
 * In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
 * The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
 */

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << BLUE "Usage: ./ircserv <port> <password>" RESET << endl;
		return 0;
	}

	try {
		Server	server(atoi(argv[1]), argv[2]);

		server.initServer();
	} catch (runtime_error &e) {
		cerr << RED "Error: " << e.what() << RESET << endl;
		return 1;
	} catch (...) {
		cerr << RED ERR_UNKNOWN RESET << endl;
		return 1;
	}

	return 0;
}
