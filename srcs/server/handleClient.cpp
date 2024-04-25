#include "Server.hpp"

void	Server::handleClient(Client *client) {
	string	buffer = client->getBuffer();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		_commands.select(*this, client, buffer.substr(0, pos));
		if (client->getRegistered() == false) {
			if (client->getGotPasswordRight() && !client->getNickname().empty() && !client->getUsername().empty()) {
				client->setRegistered(true);
				RPL::sendRPL(*this, client, IRCReplies::RPL_WELCOME(client->getNickname(), client->getUsername()));
			}
		}
		buffer.erase(0, pos + 2);
	}
	client->clearCommand();
}

void	Server::receiveData(int clientFd) {
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	Client	*client = _clients.getClientByFd(clientFd);

	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0) {
		removePollFd(clientFd);
		_clients.deleteClient(_clients.getClientByFd(clientFd));
		close(clientFd);
		return ;
	}
	client->addToBuffer(static_cast<string>(buff));
	if (client->getBuffer().find("\r\n") != string::npos) {
		try {
			handleClient(client);
		} catch (exception &e) { // This is when the client's password mismatches
			removePollFd(clientFd);
			_clients.deleteClient(_clients.getClientByFd(clientFd));
			close(clientFd);
		}
	}
}
