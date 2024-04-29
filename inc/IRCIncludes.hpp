#pragma once

/* Basic colours */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

# ifdef WLOGS
#  define DEBUG true
# else
#  define DEBUG false
# endif

/* Includes */
# include <iostream>
# include <string>

# include <sys/types.h>		// socket
# include <sys/socket.h>	// socket
# include <netinet/in.h>	// sockaddr_in
# include <arpa/inet.h>		// htons
# include <unistd.h>		// close
# include <cstring>			// memset
# include <sstream>			// istringstream
# include <poll.h>			// poll
# include <exception>		// exception
# include <vector>
# include <fcntl.h>
# include <signal.h>
# include <cstdlib>
# include <algorithm>
# include <cctype>
# include <map>
# include <cerrno>

/* Namespace */
using namespace std;

/* Error message */
# define ERR_ARGS "Usage: ./ircserv <port> <password>"
# define ERR_CONVERT "Error: Conversion failed"
# define ERR_PORT "Error: Port number must be between 0 and 65535"
# define ERR_PASS "Error: Password cannot be empty"
# define ERR_SOCK "Error: Socket creation failed"
# define ERR_SERVER "Error: Server failed to run"
# define ERR_UNKNOWN "An unknown error occured"
