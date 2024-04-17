#include "Server.hpp"
#include "Command.hpp"

void	Server::handleCommand(Client &client) {
	Command	cmd;
	string	buffer = client.getBuffer();
	size_t	pos;

	while ((pos = buffer.find("\r\n")) != string::npos) {
		if (client.getRegistered() == false) {
			if (!client.getNickname().empty() || !client.getUsername().empty() || !client.getHostname().empty()) {
				client.setRegistered(true);
				sendMessage(client.getFd(), IRCReplies::RPL_WELCOME(client.getNickname(), client.getUsername(), client.getHostname()));
			}
		}
		cmd.selectCommand(client, buffer.substr(0, pos));
		buffer.erase(0, pos + 2);
	}
	client.clearCommand();
}

Client	&Server::getClientByFd(int fd) {
	size_t	i;

	for (i = 0; i < _clients.size(); i++) {
		if (_clients[i].getFd() == fd)
			break ;
	}
	return _clients[i];
}

void	Server::receiveData(int clientFd) {
	char	buff[BUFFER_SIZE]; bzero(buff, BUFFER_SIZE);
	Client	client = getClientByFd(clientFd);

	ssize_t	bytesReceived = recv(clientFd, buff, BUFFER_SIZE - 1, 0);
	if (bytesReceived <= 0) {
		removeClient(clientFd);
		close(clientFd);
		return ;
	}
	cout << "INFO: Client " << clientFd << ": " << buff;
	client.addToBuffer(static_cast<string>(buff));
	if (client.getBuffer().find("\r\n") != string::npos) {
		try {
			handleCommand(client);
		} catch (exception &e) { // This is when the client's password mismatches
			cout << "INFO: Client " << clientFd << ": password mismatch" << endl;
			removeClient(clientFd);
			close(clientFd);
		}
	}
}
