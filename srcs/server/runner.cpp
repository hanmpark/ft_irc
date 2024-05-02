#include <signal.h>
#include <cerrno>

#include "Server.hpp"

bool	Server::_signalReceived = false;

/**
 * @brief Handles signals received by the server.
 *
 * @param signum The signal number received.
 */
void	Server::_signalHandler(int signum) {
	static_cast<void>(signum);
	_signalReceived = true;
}

/**
 * @brief Runs the server main loop, which listens for incoming connections and data.
 * The loop continues until a signal is received to stop the server.
 *
 * @throws runtime_error if poll() fails with an error other than EINTR.
 */
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
					if (!_receiveData(_pollfds[i].fd)) {
						_pollfds.erase(_pollfds.begin() + i);
						i--;
					}
				}
			}
		}
	}
}
