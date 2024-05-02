#include <unistd.h>
#include <cstdlib>

#include "IRCBot.hpp"

IRCBot::IRCBot(string const &host, string const &port, string const &password) : _sockfd(-1) {
	if (!_isValidArgs(host, port, password))
		throw runtime_error("Invalid arguments");
	_host = host;
	_port = atoi(port.c_str());
	_password = password;
}

IRCBot::~IRCBot() {
	if (_sockfd != -1)
		close(_sockfd);
}

/**
 * @brief Checks if the given arguments for the host, port, and password are valid.
 *
 * @param host The host argument to check.
 * @param port The port argument to check.
 * @param password The password argument to check.
 *
 * @return True if the arguments are valid, false otherwise.
 */
bool	IRCBot::_isValidArgs(string const &host, string const &port, string const &password) const {
	if (host.empty() || port.empty() || password.empty()) {
		return false;
	} else {
		if (host != "localhost" && host != "127.0.0.1") {
			return false;
		} else if (port.find_last_not_of("0123456789") != string::npos || atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Initializes a map of jokes with their corresponding responses.
 *
 * This function adds 15 different jokes to the map,
 * each with a unique key that corresponds to the user's request for a specific type of joke.
 * The map is named _jokes and is a member variable of the IRCBot class.
 */
void	IRCBot::_initJokes() {
	_jokes["Tell me a joke"] = "Knock, knock";
	_jokes["Who's there?"] = "Boo";
	_jokes["Boo who?"] = "Don't cry, it's just a joke";
	_jokes["Tell me a dad joke"] = "I'm reading a book on the history of glue. I just can't seem to put it down.";
	_jokes["Tell me a programming joke"] = "Why do programmers prefer dark mode? Because light attracts bugs.";
	_jokes["Tell me a random joke"] = "Why did the scarecrow win an award? Because he was outstanding in his field.";
	_jokes["Tell me a joke about cats"] = "Why was the cat sitting on the computer? To keep an eye on the mouse!";
	_jokes["Tell me a joke about dogs"] = "Why did the dog sit in the shade? Because he didn't want to be a hot dog!";
	_jokes["Tell me a joke about birds"] = "Why do birds fly south in the winter? Because it's too far to walk!";
	_jokes["Tell me a joke about fish"] = "Why did the fish blush? Because it saw the ocean's bottom!";
	_jokes["Tell me a joke about horses"] = "Why did the horse cross the road? To get to the other neigh-bor!";
	_jokes["Tell me a joke about cows"] = "What do you call a cow with no legs? Ground beef!";
	_jokes["Tell me a joke about pigs"] = "What do you call a pig that knows karate? A pork chop!";
	_jokes["Tell me a joke about chickens"] = "Why did the chicken join a band? Because it had the drumsticks!";
	_jokes["Tell me a joke about sheep"] = "What do you call a sheep with no legs? A cloud!";
}

/**
 * @brief Runs the bot.
 *
 * This function initializes the bot's jokes,
 * authenticates the bot with the server,
 * and then enters a loop to continuously receive data from the server.
 * The function exits when the connection to the server is closed.
 */
void	IRCBot::runBot() {
	_initJokes();
	_authToServer();
	while (_recvData());
}

void	IRCBot::_addToBuffer(string const &buffer) { _buffer += buffer; }
