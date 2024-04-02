# Ft_irc (Internet Relay Chat)

The aim of this project is to create our own IRC server in C++98. <br>
IRC is a text-based communication protocol used for real-time messaging. <br>

### Purpose:
1. peer-to-peer communication
2. group communication
3. data transfer

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Definitions](#definitions)

## Installation

Simply clone the project, and, since we have a Makefile up and ready, just enter the command at the root of the project:

```bash
make
```

We should have an **ircserv** executable located at the root of the directory.

## Usage

The ircserv executable after compiling the project will need the 2 following arguments: <br>
```bash
./ircserv <port> <password>
```
Where:
1. __port__: port on which the server will listen to for incoming IRC connections.
2. __password__: the password that the IRC client will require in order to connect to the server.

## Requirements
- Capable of handling multiple clients simultaneously, and never hang.
- Forking is forbidden. All Input/Output must be non-blocking.
- Only 1 poll()$*^1$ (or other equivalent like select(), kqueue(), or epoll()) can be used for handling all these operations (read, write, but also listen, and so forth).

> If we try to read/reacv or write/send in any file descriptor without the use of poll() or equivalent, that's cheating.

- Several IRC client exist. We have chosen Irssi (might change ?).

- Communication between the two is done via TCP/IP (v4 or v6) protocol.

## Contributing

Guidelines for contributing to your project.

## License

Information about the license for your project.

## Contact

How to get in touch with you or the project team.

## Definitions
**socket**: socket is a file descriptor. It is used to send/receive data over a network. They are used to create a connection between 2 endpoints.

![socker_representation](./img/socketImg.png)

```c
#include <sys/socket.h>

int	socket(int domain, int type, int protocol)


1. `domain` => specifies the domain for the socket.
	- `AF_INET`: This specifies the Internet Protocol version 4 (IPv4) communication domain.

	- `AF_INET6`: This specifies the Internet Protocol version 6 (IPv6) communication domain.

	- `AF_UNIX`: This specifies the Unix domain communication domain.

2. `type` => type of socket to be created.
	- `SOCK_STREAM`: This specifies a stream-oriented socket, which provides a reliable, connection-oriented byte stream. This is typically used for TCP connections.

	- `SOCK_DGRAM`: This specifies a datagram-oriented socket, which provides a connectionless, unreliable message delivery service. This is typically used for UDP connections.

3. `protocol` => protocol to be used with the socket.
	- can be set to 0 to use the default protocol for the specified domain and type.
```

