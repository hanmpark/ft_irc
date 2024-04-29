#include "IRCBot.hpp"

IRCBot::IRCBot(string const &host, string const &port, string const &password) {
	if (!isValidArgs(host, port, password)) {
		throw runtime_error("Invalid arguments");
	}
	_host = host;
	_port = atoi(port.c_str());
	_password = password;
	_sockfd = -1;
}

IRCBot::~IRCBot() {
	if (_sockfd != -1) {
		close(_sockfd);
	}
}

void	IRCBot::initJokes() {
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
	_jokes["Tell me a about sheep"] = "What do you call a sheep with no legs? A cloud!";
	_jokes["Dark humor"] = "I'm sorry, I can't do that.";
}

void	IRCBot::addToBuffer(string const &buffer) { _buffer += buffer; }

void	IRCBot::handleInput() {
	size_t	end, triggerBegin, msgBegin;
	string	target, message;

	while ((end = _buffer.find("\r\n")) != string::npos) {
		cout << YELLOW "OUILLE: " << BLUE << _buffer << RESET << endl; // Debug
		if ((triggerBegin = _buffer.find("PRIVMSG")) != string::npos) {
			target = _buffer.substr(triggerBegin + 8, _buffer.find(" ", triggerBegin + 8) - triggerBegin - 8);
			cout << RED "Target: " << BLUE << target << RESET << endl; // Debug
			msgBegin = _buffer.find(":", triggerBegin + 8 + target.length());
			message = _buffer.substr(msgBegin + 1, end - msgBegin - 1);
			cout << RED "Message: " << BLUE << message << RESET << endl; // Debug
			if (_jokes.find(message) != _jokes.end()) {
				sendData("PRIVMSG " + target + " :" + _jokes[message] + "\r\n");
			}
		}
		_buffer.erase(0, end + 2);
	}
}

void	IRCBot::initBotSocket() {
	_sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
	if (_sockfd < 0) {
		throw runtime_error("Error opening socket");
	}
}

void	IRCBot::connectToServer() {
	if (_sockfd == -1) {
		throw runtime_error("Socket not initialized");
	}
	struct sockaddr_in	serv_addr; // Declare server address to use it in connect()

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; // Set address family to IPv4
	serv_addr.sin_port = htons(_port); // Convert port to network byte order
	if (inet_pton(AF_INET, _host.c_str(), &serv_addr.sin_addr) <= 0) { // Convert IPv4 and IPv6 addresses from text to binary form
		throw runtime_error("Invalid address");
	} else if (connect(_sockfd, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
		throw runtime_error("Connection failed");
	}

	cout << GREEN "Connected to " << _host << ":" << BLUE << _port << RESET << endl;
}

void	IRCBot::authToServer() {
	if (_sockfd == -1) {
		throw runtime_error("Socket not initialized");
	}
	sendData("PASS " + _password + "\r\n");
	sendData("NICK IRCBot\r\n");
	sendData("USER IRCBot 0 * :IRCBot\r\n");
}

bool	IRCBot::recvData() {
	cout << GREEN "Waiting for data..." << RESET << endl;
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	int		bytesReceived;

	bytesReceived = recv(_sockfd, buff, BUFFER_SIZE - 1, 0); // Receive data from server
	if (bytesReceived <= 0) {
		return false;
	}
	addToBuffer(static_cast<string>(buff));
	if (_buffer.find("\r\n") != string::npos) {
		try {
			cout << YELLOW "Buffer: " << BLUE << _buffer << RESET << endl; // Debug
			handleInput();
		} catch (exception &e) {
			return false;
		}
	}
	_buffer.clear();
	return true;
}

void	IRCBot::runBot() {
	initJokes();
	authToServer();
	while (recvData());
}

void	IRCBot::sendData(string const &data) const {
	send(_sockfd, data.c_str(), data.length(), 0);
}
