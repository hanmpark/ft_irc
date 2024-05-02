#include "Server.hpp"

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define RESET	"\033[0m"

/**
 * @brief The main function of the IRC server.
 *
 * This function is the entry point of the IRC server program. It takes two command-line arguments: the port number and the password.
 * If the number of arguments is not equal to 3, it prints a usage message and returns 1.
 *
 * It creates an instance of the Server class with the provided port number and password, and then initializes and runs the server.
 *
 * If any runtime error occurs during the execution of the server, it catches the exception, prints the error message, and returns 2.
 * If an unknown error occurs, it prints a generic error message and returns 3.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 *
 * @return int The exit status of the program.
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
