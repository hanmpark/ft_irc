#pragma once

# include <iostream>
# include <map>

using namespace std;

class IRCBot {
private:
	int					_sockfd, _port;
	string				_host, _password, _buffer;
	map<string, string>	_jokes, _finisher;

	bool	_isValidArgs(string const &host, string const &port, string const &password) const;
	void	_initJokes();
	void	_addToBuffer(string const &buffer);

	void	_sendData(string const &data) const;
	void	_handleInput();
	bool	_recvData();

	void	_authToServer() const;

	IRCBot();

public:
	IRCBot(string const &host, string const &port, string const &password);
	~IRCBot();

	void	initBotSocket();
	void	connectToServer();
	void	runBot();

};
