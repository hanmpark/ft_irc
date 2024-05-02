#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "IRCBot.hpp"

# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;34m"
# define RESET	"\033[0m"

/**
 * @brief Initializes the socket for the bot.
 *
 * @throws runtime_error if the socket creation fails
 */
void	IRCBot::initBotSocket() {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd == -1)
		throw runtime_error("Failed at socket creation");
}

/**
 * @brief Connects the bot to the server.
 *
 * @throws runtime_error if any step of the initialization process fails
 */
void	IRCBot::connectToServer() {
	if (_sockfd == -1)
		throw runtime_error("Socket not initialized");

	struct sockaddr_in	serv_addr;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(_port);
	if (inet_pton(AF_INET, _host.c_str(), &serv_addr.sin_addr) <= 0) {
		throw runtime_error("Invalid address");
	} else if (connect(_sockfd, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) == -1) {
		throw runtime_error("Connection failed");
	}

	cout << GREEN "Connected to " << _host << ":" << BLUE << _port << RESET << endl;
}

/**
 * @brief Authenticates the bot to the server.
 *
 * This function sends the server the bot's password, nickname, and username using the PASS, NICK, and USER commands, respectively.
 *
 * @throws runtime_error if the socket file descriptor is invalid
 */
void	IRCBot::_authToServer() const {
	if (_sockfd == -1)
		throw runtime_error("Socket not initialized");
	_sendData("PASS " + _password + "\r\n");
	_sendData("NICK IRCBot\r\n");
	_sendData("USER IRCBot 0 * :IRCBot\r\n");
}
