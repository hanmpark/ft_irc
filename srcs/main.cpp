#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

/*
* In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
* The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
*/

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Usage: ./ircserv <port> <password>" << endl;
		return 0;
	}

	try {
		int		port = myAtoi(argv[1]);
		string	password = argv[2];
		Server	server(port, password);

		server.initServer(port, password);
	} catch (runtime_error &e) {
		cerr << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << ERR_UNKNOWN << endl;
		return 1;
	}
	
	return 0;
}
