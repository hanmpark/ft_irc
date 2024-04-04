#pragma once

/* Basic colours */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

/* Includes */
# include <iostream>
# include <string>

# include <sys/socket.h>	// socket
# include <sys/types.h>		// socket
# include <netinet/in.h>	// sockaddr_in
# include <arpa/inet.h>		// htons
# include <unistd.h>		// close
# include <cstring>			// memset
# include <sstream>			// istringstream
# include <poll.h>			// poll
# include <exception>		// exception
# include <list>
# include <fcntl.h>

using namespace std;

/* Error message */
# define ERR_ARGS "Usage: ./ircserv <port> <password>"
# define ERR_TYPE "Error: Type conversion failed"
# define ERR_PORT "Error: Port number must be between 0 and 65535"
# define ERR_PASS "Error: Password cannot be empty"
# define ERR_SOCK "Error: Socket creation failed"
# define ERR_UNKNOWN "An unknown error occured"
