#include "IRCBot.hpp"

#define BLUE	"\033[1;34m"
#define RED		"\033[1;31m"
#define RESET	"\033[0m"

/**
 * @brief Main function of the IRC bot program.
 *
 * @param ac The number of command line arguments.
 * @param av The array of command line arguments.
 */
int	main(int ac, char **av) {
	if (ac != 4) {
		cout << BLUE "Usage: ./IRCBot <host> <port> <password>" RESET << endl;
		return 1;
	}
	try {
		IRCBot	bot(static_cast<string>(av[1]), static_cast<string>(av[2]), static_cast<string>(av[3]));

		bot.initBotSocket();
		bot.connectToServer();
		bot.runBot();
	} catch (exception &e) {
		cerr << RED "Error: " << e.what() << RESET << endl;
		return 2;
	} catch (...) {
		cerr << RED "An unknown error occured" RESET << endl;
		return 3;
	}
	return 0;
}
