#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

/*
* In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
* The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
*/

int	scanArgs(int argc, char **argv) {
	if (argc != 3) {
		cerr << ERR_ARGS << endl;
		return 1;
	}

	int	port = myAtoi(argv[1]);
	string	password = argv[2];

	/*
	reasoning behind the range is that TCP & UDP have port numbers represented
	by a 16-bit unsigned integer.
	1. 0-1023 reserved for specific services
	2. 1024 to 49151 can be registered for specific purposes
	3. 49152-65535 used by client apps for outgoing conncections.
	*/
	if (port < 0 || port > 65535) {
		cerr << ERR_PORT << endl;
		return 1;
	}
	else if (password.empty()) {
		cerr << ERR_PASS << endl;
	}

	return 0;
}

int main(int argc, char **argv) {
	if (scanArgs(argc, argv) == 1) {
		return 1;
	}

	try {
		Server	server;

		int	port = myAtoi(argv[1]);
		string	password = argv[2];
		server.initServer(port, password);

	} catch(const exception &e) {
		cerr << e.what() << endl;
	} catch (...) {
		cerr << ERR_UNKNOWN << endl;
	}
	
	return 0;
}
