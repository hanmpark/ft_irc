#include "IrcIncludes.hpp"
#include "Server.hpp"
#include "Utils.hpp"

int	scanArgs(char **argv) {
	int port = myAtoi(argv[1]);
	if 
}

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cerr << ERR_ARGS << std::endl;
		return 1;
	}
	if (scanArgs(argv) == 1)
		return 1;

	socket(AF_INET, SOCK_STREAM, 0);
	return 0;
}
