#pragma once

# include <signal.h>

/* Global variable */
extern bool	g_signalReceived;

void	signalHandler(int signum);
