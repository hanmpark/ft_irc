#include "signalHandler.hpp"

bool	g_signalReceived = false;

void	signalHandler(int signum) {
	if (signum == SIGINT || signum == SIGQUIT) {
		g_signalReceived = true;
	}
}
