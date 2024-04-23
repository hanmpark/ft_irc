#include "Server.hpp"

char	to_upper(unsigned char c) {
	return static_cast<char>(toupper(c));
}

/*
 TODO:
	- keep whole argument after ":" in one string
*/
vector<string>	Server::splitBuffer(string const &buffer, string const &limiter) const {
	vector<string>	args;
	size_t			pos = 0;
	size_t			nextPos = 0;

	while ((nextPos = buffer.find(limiter, pos)) != string::npos) {
		string	arg = buffer.substr(pos, nextPos - pos);
		args.push_back(arg);
		pos = nextPos + 1;
	}
	args.push_back(buffer.substr(pos));
	return args;
}

void	Server::selectCommand(Client *client, string const &buffer) {
	vector<string>	args = splitBuffer(buffer, " ");
	transform(args[0].begin(), args[0].end(), args[0].begin(), ::to_upper);

	commandIt	command = _commands.find(args[0]);
	if (command != _commands.end()) {
		debugLog(args);
		if (!client->getRegistered()) {
			if (args[0] != "CAP" && args[0] != "PASS" && args[0] != "NICK" && args[0] != "USER") {
				sendRPL(*this, client->getFd(), IRCErrors::ERR_NOTREGISTERED());
				args.clear();
				return;
			}
		}
		if (command->second != NULL) {
			command->second->execute(*this, client, args);
		}
	} else {
		sendRPL(*this, client->getFd(), IRCErrors::ERR_UNKNOWNCOMMAND(args[0]));
	}
	args.clear();
}

void	Server::handleClient(Client *client) {
	string	buffer = client->getBuffer();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		selectCommand(client, buffer.substr(0, pos));
		if (client->getRegistered() == false) {
			if (client->getGotPasswordRight() && !client->getNickname().empty() && !client->getUsername().empty()) {
				client->setRegistered(true);
				sendRPL(*this, client->getFd(), IRCReplies::RPL_WELCOME(client->getNickname(), client->getUsername()));
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
	client->addToBuffer(static_cast<string>(buff));
	if (client->getBuffer().find("\r\n") != string::npos) {
		try {
			handleClient(client);
		} catch (exception &e) { // This is when the client's password mismatches
			removeClient(clientFd);
			close(clientFd);
		}
	}
}
