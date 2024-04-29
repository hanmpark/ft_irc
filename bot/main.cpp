#include "IRCBot.hpp"

// Function to send data to the server
void sendData(int sockfd, string const &data) {
	send(sockfd, data.c_str(), data.length(), 0);
}

// Bot main function
int main(int ac, char const **av) {
	if (ac != 4) {
		cout << "Usage: :" << av[0] << " <host> <port> <password>" << endl;
		return 0;
	}

	try {
		IRCBot	bot(static_cast<string>(av[1]), static_cast<string>(av[2]), static_cast<string>(av[3]));

		bot.initBotSocket();
		bot.connectToServer();
		bot.runBot();
	} catch (exception &e) {
		cerr << e.what() << endl;
	} catch (...) {
		cerr << "Unknown error" << endl;
	}
	
	return 0;
}
