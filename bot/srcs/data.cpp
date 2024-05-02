#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>

#include "IRCBot.hpp"

# define BUFFER_SIZE 1024

/**
 * @brief Sends data to the server.
 *
 * @param data The data to be sent to the server.
 */
void	IRCBot::_sendData(string const &data) const {
	send(_sockfd, data.c_str(), data.length(), 0);
}

/**
 * @brief Handles incoming messages from the IRC server.
 *
 * This function searches for PRIVMSG messages and extracts the target and message from the message string.
 * If the message matches a joke command, it sends the corresponding joke response back to the target.
 */
void	IRCBot::_handleInput() {
	size_t	pos, triggerBegin, msgBegin, targetBegin, targetEnd;
	string	target, message;

	while ((pos = _buffer.find("\r\n")) != string::npos) {
		if ((triggerBegin = _buffer.find("PRIVMSG")) != string::npos) {
			targetBegin = _buffer.find(":") + 1;
			targetEnd = _buffer.find("!");
			target = _buffer.substr(targetBegin, targetEnd - targetBegin);
			msgBegin = _buffer.find(":", triggerBegin + 8 + target.length());
			message = _buffer.substr(msgBegin + 1, pos - msgBegin - 1);
			if (_jokes.find(message) != _jokes.end())
				_sendData("PRIVMSG " + target + " :" + _jokes[message] + "\r\n");
		}
		_buffer.erase(0, pos + 2);
	}
}

/**
 * @brief Receives data from the server and adds it to a buffer.
 *
 * @return True if the function was able to receive data and process it successfully, false otherwise.
 */
bool	IRCBot::_recvData() {
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	int		bytesReceived;

	bytesReceived = recv(_sockfd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0)
		return false;
	_addToBuffer(static_cast<string>(buff));
	if (_buffer.find("\r\n") != string::npos) {
		try {
			_handleInput();
		} catch (exception &e) {
			return false;
		}
	}
	_buffer.clear();
	return true;
}
