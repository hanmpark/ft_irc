#pragma once

/* Basic colours */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

/* Includes */
# include <iostream>
# include <string>

# include <sys/socket.h>
# include <arpa/inet.h>

/* Error message */
# define ERR_ARGS "Usage: ./ircserv <port> <server>"
# define ERR_UNKNOWN "An unknown error occured"
