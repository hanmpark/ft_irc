#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

// int	scanArgs(char **argv) {
// 	try {
// 		int port = myAtoi(argv[1]);
// 		std::string server = argv[2];
// 	} catch (std::exception &e) {
// 		std::cerr << e.what() << std::endl;
// 		return 1;
// 	} catch (...) {
// 		std::cerr << ERR_UNKNOWN << std::endl;
// 	}

// }

/*
* In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
* The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.
*/

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << ERR_ARGS << std::endl;
		return 1;
	}
	// if (scanArgs(argv) == 1)
	// 	return 1;

	//* Create a socket
	/*
	* AF_INET: IPv4
	* SOCK_STREAM: TCP
	* 0: Default protocol
	*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cerr << "Error creating socket" << std::endl;
		return 1;
	}

	struct sockaddr_in serv_addr = {
		AF_INET,
		htons(9999),
		0
	};


	//* Bind the socket to an address, therefore we can start listening
	bind(sockfd, &serv_addr, sizeof(serv_addr));
	return 0;
}
