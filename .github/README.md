<div align="center">
    <img src="https://github.com/hanmpark/42-project-badges/blob/main/badges/ft_ircm.png"/>
</div>

<h1 align="center">Ft_irc</h1>

<p align="center">
    <b><i>An IRC (Internet Relay Chat) server implemented in C++98.</i></b>
</p></br>

<div align="center">
    <img alt="Repository created at" src="https://img.shields.io/github/created-at/hanmpark/Ft_irc"/>
    <img alt="Repository code size" src="https://img.shields.io/github/languages/code-size/hanmpark/Ft_irc"/>
    <img alt="Mostly used language" src="https://img.shields.io/github/languages/top/hanmpark/Ft_irc"/>
</div>

## 📖 Description
> The **Ft_irc** project consists of building a custom IRC server in **C++98**.
>
> IRC (Internet Relay Chat) is a text-based communication protocol used for real-time messaging.
> The server supports **peer-to-peer communication**, **group communication**, and **data transfer**.
>
> The implementation emphasizes non-blocking I/O, multiplexing, and robust socket management.

## 🛠️ Features
- Handle multiple clients simultaneously without blocking.
- Non-blocking I/O using `poll()` (or equivalent: `select`, `epoll`, `kqueue`).
- No forking (single-process server).
- Communication through TCP/IP (v4 or v6).
- Authentication via password-protected connection.
- Compatible with standard IRC clients (e.g., Irssi).

## 📦 Installation
Clone the repository and compile:
```bash
git clone https://github.com/hanmpark/Ft_irc.git
cd Ft_irc
make
```
The executable will be named:
```bash
ircserv
```

## 🚀 Usage
Run the server with:
```bash
./ircserv <port> <password>
```
- `<port>` → Port number the server listens on.
- `<password>` → Password required for clients to connect.
Example with **Irssi client**:
```bash
irssi -c localhost -p <port> -w <password>
```

## 📑 Requirements
- Must handle multiple clients without blocking.
- Exactly one `poll()` (or equivalent) for all operations (`listen`, `read`, `write`, etc.).
- No use of `fork()`.
- Correct socket option management (`SO_REUSEADDR`, `SO_REUSEPORT`).

## 🔧 Definitions
### Socket
A **socket** is a file descriptor used to send/receive data over a network.
It establishes communication between two endpoints.

<div align="center">
    <img src="../img/socketImg.png" alt="socket representation"/>
</div>

Example:
```c
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

### setsockopt
Used to configure socket options (e.g., allowing port reuse).
```c
#include <sys/types.h>
#include <sys/socket.h>

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```
Common options:
- `SO_REUSEADDR` → allow address reuse after restart.
- `SO_REUSEPORT` → allow multiple sockets to bind to the same address/port.

## 📚 References
- [RFC 1459 – IRC Protocol](https://tools.ietf.org/html/rfc1459)
- [IRC Replies Reference](http://www.iprelax.fr/irc/irc_rfcus6.php)
- [Beej’s Guide to Network Programming](https://beej.us/guide/bgnet/html/)
- [Socket Programming in C](https://www.geeksforgeeks.org/socket-programming-cc/)
- [Linux man page: socket(2)](https://man7.org/linux/man-pages/man2/socket.2.html)
- [Linux man page: setsockopt(2)](https://man7.org/linux/man-pages/man2/setsockopt.2.html)

## 👤 Authors
- [hanmpark](https://github.com/hanmpark)
- [Kariyu42](https://github.com/Kariyu42)
