#include "Server.hpp"

void	Server::_handleClient(Client *client) {
	string	buffer = client->getBuffer();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		_commands.select(*this, client, buffer.substr(0, pos));
		if (client && client->getRegistered() == false) {
			if (client->getGotPasswordRight() && !client->getNickname().empty() && !client->getUsername().empty()) {
				client->setRegistered(true);
				Reply::sendRPL(*this, client, RPL::RPL_WELCOME(client->getNickname()), SERVER);
			}
		}
		buffer.erase(0, pos + 2);
	}
	client->clearBuffer();
}

void	Server::_receiveData(int clientFd) {
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	Client	*client = _clients.getClient(clientFd);
	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);

	if (bytesReceived <= 0) {
		_clients.deleteClient(client);
	} else {
		client->addToBuffer(static_cast<string>(buff));
		if (client->getBuffer().find("\r\n") != string::npos) {
			try {
				_handleClient(client);
			} catch (exception &e) {
				_clients.deleteClient(client);
			}
		}
	}
}
