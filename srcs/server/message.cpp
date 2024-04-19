#include "Server.hpp"

void	Server::sendMessage(int fd, string const &message) {
	send(fd, message.c_str(), message.length(), 0);
}
