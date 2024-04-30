#include <signal.h>
#include <cerrno>

#include "Server.hpp"

bool	Server::_signalReceived = false;

void Server::_signalHandler(int signum)
{
	(void)signum;
	_signalReceived = true;
}

void	Server::runServer() {
	signal(SIGINT, &_signalHandler);
	signal(SIGQUIT, &_signalHandler);

	while (_signalReceived == false) {
		if (poll(&_pollfds[0], _pollfds.size(), -1) < 0) {
			if (errno == EINTR)
				break;
			throw runtime_error("poll()");
		}
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == _serverFd) {
					_acceptNewClient();
				} else {
					_receiveData(_pollfds[i].fd);
				}
			}
		}
	}
}
