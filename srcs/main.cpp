#include "IrcIncludes.hpp"
#include "Server.hpp"

/*
 * In the sockaddr_in structure, the sin_port field is used to store the port number for a socket.
 * The sin_port field is a 16-bit integer, which means that it can store values in the range 0-65535.

// -------------------------------------------------------------------------- //
 TODO:
 -	Once the server is setup and running, follow up with the client registration.
 TODO-	Password message:
		* -> Command: PASS
		* -> Parameters: <password>
		* -> Numeric Replies: ERR_NEEDMOREPARAMS, ERR_ALREADYREGISTRED, ERR_PASSWDMISMATCH
		* -> it is required that a client send the PASS command before sending the NICK/USER commands.
 TODO-	Nick message:
		* -> Command: NICK
		* -> Parameters: <nickname>
		* -> Numeric Replies: ERR_NONICKNAMEGIVEN, ERR_ERRONEUSNICKNAME, ERR_NICKCOLLISION, ERR_NICKNAMEINUSE, ERR_RESTRICTED, ERR_UNAVAILRESOURCE
		* -> The NICK message is used to give a user a nickname or change the nickname of a user.
 TODO-	User message:
		* -> Command: USER
		* -> Parameters: <user> <mode> <unused> <realname>
		* -> Numeric Replies: ERR_NEEDMOREPARAMS, ERR_ALREADYREGISTRED
		* -> the USER command is used at the beginning to specify the username, hostname and realname of a new user.
		* -> realname: must handle spaces.
		* -> <mode>: set to 0 for no mode. <unused>: not used. So send a '*'.
 
// -------------------------------------------------------------------------- //
 TODO:
 -	Once the client is registered, follow up with oper commands.
 TODO-	Oper message:
		* -> Command: OPER
		* -> Parameters: <name> <password>
		* -> A normal user uses the OPER command to obtain operator privileges. Both parameters are required.
		* Upon success, the user receives a RPL_YOUREOPER message.
		* -> Numeric Replies: ERR_NEEDMOREPARAMS, ERR_PASSWDMISMATCH, ERR_NOOPERHOST, RPL_YOUREOPER
		

 */
int main(int argc, char **argv) {
	if (argc != 3) {
		cout << BLUE "Usage: ./ircserv <port> <password>" RESET << endl;
		return 0;
	}

	try {
		Server	server(static_cast<string>(argv[1]), static_cast<string>(argv[2]));

		server.initServer();
	} catch (runtime_error &e) {
		cerr << RED "Error: " << e.what() << RESET << endl;
		return 1;
	} catch (...) {
		cerr << RED ERR_UNKNOWN RESET << endl;
		return 1;
	}

	return 0;
}
