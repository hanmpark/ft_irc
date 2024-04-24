#pragma once

# include "IRCIncludes.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Server;

enum e_endpoint {
	CLIENT,
	SERVER
};

enum e_transmit {
	SEND,
	RECEIVE
};

class RPL {
private:
	RPL();

public:
	static string	findPrefix(Server &server, Client *client, e_endpoint const &side);
	static void		sendRPL(Server &server, Client *client, string const &message);
	static void		sendRPL(Server &server, Client *client, vector<string> const &args);
	static void		debugLog(string const &errorLog, bool const &debug);
	static void		debugLog(vector<string> const &args, bool const &debug);
	static void		debugLog(Server &server, Client *client, vector<string> const &args, e_endpoint const &endPoint, bool const &debug);
};

struct IRCReplies {
	static string const RPL_WELCOME(string const &nick, string const &user) {
		return "001 " + nick + " :Welcome to the Internet Relay Network " + user + "\r\n";
	}

	static string const RPL_NAMREPLY(string const &nick, string const &channel, string const &names) {
		return ": 353 " + nick + " = " + channel + " :" + names + "\r\n";
	}

	static string const RPL_ENDOFNAMES(string const &nick, string const &channel) {
		return ": 366 " + nick + " " + channel + " :End of /NAMES list\r\n";
	}

	static string const RPL_CHANNELMODEIS(string const &channel, string const &mode) {
		return ": 324 " + channel + " " + mode + "\r\n";
	}

	static string const RPL_YOUREOPER() {
		return "381 :You are now an IRC operator\r\n";
	}

	static string const RPL_TOPIC(string const &channel, string const &topic) {
		return "332 " + channel + " :" + topic + "\r\n";
	}

	static string const RPL_UMODEIS(string const &userModeString) {
		return "221 :" + userModeString + "\r\n";
	}
};

struct IRCErrors {
	static string const ERR_NEEDMOREPARAMS(string const &command) {
		return "461 " + command + " :Not enough parameters\r\n";
	}

	static string const ERR_ALREADYREGISTRED() {
		return "462 :Unauthorized command (already registered)\r\n";
	}

	static string const ERR_NONICKNAMEGIVEN() {
		return "431 :No nickname given\r\n";
	}

	static string const ERR_NICKNAMEINUSE(string const &nick) {
		return "433 " + nick + " :Nickname is already in use\r\n";
	}

	static string const ERR_UNAVAILRESOURCE(string const &input) {
		return "437 " + input + " :Nick/channel is temporarily unavailable\r\n";
	}

	static string const ERR_ERRONEUSNICKNAME(string const &nick) {
		return "432 " + nick + " :Erroneous nickname\r\n";
	}

	static string const ERR_NICKCOLLISION(string const &nick, string const &user, string const &host) {
		return "436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n";
	}

	static string const ERR_RESTRICTED() {
		return "484 :Your connection is restricted!\r\n";
	}

	static string const ERR_NOOPERHOST() {
		return "491 :No O-lines for your host\r\n";
	}

	static string const ERR_PASSWDMISMATCH() {
		return "464 :Password incorrect\r\n";
	}

	static string const ERR_UMODEUNKNOWNFLAG() {
		return "501 :Unknown MODE flag\r\n";
	}

	static string const ERR_USERSDONTMATCH() {
		return "502 :Cannot change mode for other users\r\n";
	}

	static string const ERR_UNKNOWNCOMMAND(string const &command) {
		return "421 " + command + " :Unknown command\r\n";
	}

	static string const ERR_NOTREGISTERED() {
		return "451 :You have not registered\r\n";
	}

	static string const ERR_NOSUCHNICK(string const &nick) {
		return ": 401 " + nick + " :No such nick/channel\r\n";
	}

	static string const ERR_NOSUCHCHANNEL(string const &channel) {
		return "403 " + channel + " :No such channel\r\n";
	}

	static string const ERR_CANNOTSENDTOCHAN(string const &channel) {
		return ": 404 " + channel + " :Cannot send to channel\r\n";
	}

	static string const ERR_BADCHANMASK() {
		return "476 : Bad Channel Mask\r\n";
	}

	static string const ERR_CHANNELISFULL(string const &channel) {
		return ": 471 " + channel + " :Cannot join channel (+l)\r\n";
	}
};
