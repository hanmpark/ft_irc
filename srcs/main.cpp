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

	struct sockaddr serv_addr = {
		AF_INET,
		htons(9999),
		0
	};


	//* Bind the socket to an address, therefore we can start listening
	bind(sockfd, &serv_addr, sizeof(serv_addr));

	//* Listen for incoming connections
	listen(sockfd, 5);

	//* Accept a connection from a client
	int client_sockfd = accept(sockfd, NULL, NULL);

	/*
	* once we have a connection with a client, we can send and receive data
	TODO:
		- print the data received from the client
		- enable the server to send data to the client
	*/

	struct pollfd {
		STDIN_FILENO,
	};

	//* Use the poll() function to wait for data to be received
	poll()


	return 0;
}
