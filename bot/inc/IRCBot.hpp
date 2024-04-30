#pragma once

# include "BOTIncludes.hpp"

using namespace std;

class IRCBot {
private:
	int		_sockfd;
	string	_host;
	int		_port;
	string	_password;
	string	_buffer;
	map<string, string>	_jokes;
	map<string, string>	_finisher;

	IRCBot();
public:
	IRCBot(string const &host, string const &port, string const &password);
	~IRCBot();

	//* Jokes generator
	void	initJokes();

	//* Accessors
	void	addToBuffer(string const &buffer);
	void	handleInput();

	//* Init bot functions
	void	initBotSocket();
	void	connectToServer();

	void	authToServer();

	//* Send/Recv data to server
	bool	recvData();
	void	sendData(string const &data) const;
	
	//* Run bot function
	void	runBot();

};

// Function to check if the arguments are valid
bool	isValidArgs(string const &host, string const &port, string const &password);
