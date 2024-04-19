#include "Server.hpp"

char	to_upper(unsigned char c) {
	return static_cast<char>(toupper(c));
}

vector<string>	Server::splitCommand(string const &buffer) const {
	vector<string>	args;
	size_t			pos = 0;
	size_t			nextPos = 0;

	while ((nextPos = buffer.find(" ", pos)) != string::npos) {
		string	arg = buffer.substr(pos, nextPos - pos);
		if (args.empty()) {
			transform(arg.begin(), arg.end(), arg.begin(), ::toupper);
		}
		args.push_back(arg);
		pos = nextPos + 1;
	}
	args.push_back(buffer.substr(pos));
	return args;
}

void	Server::selectCommand(Client *client, string const &buffer) {
	vector<string>	args = splitCommand(buffer);

	for (size_t i = 0; i < args.size(); i++) {
		cout << BLUE "ARGUMENTS[" << i << "]: " << args[i] << RESET << endl;
	}
	commandIt	command = _commands.find(args[0]);
	cout << "INFO: Command " << args[0] << endl;
	if (command != _commands.end() && client->getRegistered()) {
		cout << RED "1: LAUNCHING COMMAND: " << args[0] << RESET << endl;
		args.erase(args.begin());
		command->second->execute(*this, client, args);
	} else if (command != _commands.end() && !client->getRegistered()) {
		if (args[0] != "CAP" && args[0] != "PASS" && args[0] != "NICK" && args[0] != "USER") {
			sendMessage(client->getFd(), IRCErrors::ERR_NOTREGISTERED());
		} else {
			args.erase(args.begin());
			if (command->second != NULL) {
				command->second->execute(*this, client, args);
			}
		}
	} else {
		cout << "FUCK" << endl;
		sendMessage(client->getFd(), IRCErrors::ERR_UNKNOWNCOMMAND(args[0]));
	}
	args.clear();
}

void	Server::handleClient(Client *client) {
	string	buffer = client->getBuffer();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		selectCommand(client, buffer.substr(0, pos));
		cout << "register: " << client->getRegistered() << endl; // "register: 0" or "register: 1
		cout << "nickname: " << client->getNickname() << endl; // "nickname:
		cout << "username: " << client->getUsername() << endl; // "username:
		if (client->getRegistered() == false) {
			if (client->getGotPasswordRight() && !client->getNickname().empty() && !client->getUsername().empty()) {
				client->setRegistered(true);
				cout << GREEN "INFO: Client " << client->getFd() << ": is registered" RESET << endl;
				cout << RED << IRCReplies::RPL_WELCOME(client->getNickname(), client->getUsername()) << RESET << endl;
				sendMessage(client->getFd(), IRCReplies::RPL_WELCOME(client->getNickname(), client->getUsername()));
			}
		}
		buffer.erase(0, pos + 2);
	}
	client->clearCommand();
}

Client	*Server::getClientByFd(int fd) {
	size_t	i;

	for (i = 0; i < _clients.size(); i++) {
		if (_clients[i]->getFd() == fd)
			break ;
	}
	return _clients[i];
}

void	Server::receiveData(int clientFd) {
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	Client	*client = getClientByFd(clientFd);

	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0) {
		removeClient(clientFd);
		close(clientFd);
		return ;
	}
	cout << "INFO: Client " << clientFd << ": " << buff;
	client->addToBuffer(static_cast<string>(buff));
	if (client->getBuffer().find("\r\n") != string::npos) {
		try {
			handleClient(client);
		} catch (exception &e) { // This is when the client's password mismatches
			cout << "INFO: Client " << clientFd << ": password mismatch" << endl;
			removeClient(clientFd);
			close(clientFd);
		}
	}
}
