#pragma once

# include "IrcIncludes.hpp"

struct IRCReplies {
	static string const RPL_WELCOME(string const &nick, string const &user) {
		return ": 001 " + nick + " :Welcome to the Internet Relay Network " + user + "\r\n";
	}

	static string const RPL_YOUREOPER() {
		return ": 381 :You are now an IRC operator\r\n";
	}

	static string const RPL_TOPIC(string const &channel, string const &topic) {
		return ": 332 " + channel + " :" + topic + "\r\n";
	}

	static string const RPL_UMODEIS(string const &userModeString) {
		return ": 221 :" + userModeString + "\r\n";
	}
};

struct IRCErrors {
	static string const ERR_NEEDMOREPARAMS(string const &command) {
		return ": 461 " + command + " :Not enough parameters\r\n";
	}

	static string const ERR_ALREADYREGISTRED() {
		return ": 462 :Unauthorized command (already registered)\r\n";
	}

	static string const ERR_NONICKNAMEGIVEN() {
		return ": 431 :No nickname given\r\n";
	}

	static string const ERR_NICKNAMEINUSE(string const &nick) {
		return ": 433 " + nick + " :Nickname is already in use\r\n";
	}

	static string const ERR_UNAVAILRESOURCE(string const &input) {
		return ": 437 " + input + " :Nick/channel is temporarily unavailable\r\n";
	}

	static string const ERR_ERRONEUSNICKNAME(string const &nick) {
		return ": 432 " + nick + " :Erroneous nickname\r\n";
	}

	static string const ERR_NICKCOLLISION(string const &nick, string const &user, string const &host) {
		return ": 436 " + nick + " :Nickname collision KILL from " + user + "@" + host + "\r\n";
	}

	static string const ERR_RESTRICTED() {
		return ": 484 :Your connection is restricted!\r\n";
	}

	static string const ERR_NOOPERHOST() {
		return ": 491 :No O-lines for your host\r\n";
	}

	static string const ERR_PASSWDMISMATCH() {
		return ": 464 :Password incorrect\r\n";
	}

	static string const ERR_UMODEUNKNOWNFLAG() {
		return ": 501 :Unknown MODE flag\r\n";
	}

	static string const ERR_USERSDONTMATCH() {
		return ": 502 :Cannot change mode for other users\r\n";
	}

	static string const ERR_UNKNOWNCOMMAND(string const &command) {
		return ": 421 " + command + " :Unknown command\r\n";
	}

	static string const ERR_NOTREGISTERED() {
		return ": 451 :You have not registered\r\n";
	}
};
