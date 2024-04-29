#pragma once

/* Basic colours */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

# define BUFFER_SIZE 1024

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
# include <deque>

/* Namespace */
using namespace std;
