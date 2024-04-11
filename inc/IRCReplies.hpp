#pragma once

# include "IrcIncludes.hpp"

struct IRCReplies {
	static string const RPL_WELCOME(string const &nick, string const &user, string const &host) {
		return ": 001 " + nick + " :Welcome to the Internet Relay Network " + user + "@" + host + "\r\n";
	}

	

};

struct IRCErrors {
	static string const ERR_NEEDMOREPARAMS(string const &command) {
		return ": 461 " + command + " :Not enough parameters\r\n";
	}

	static string const ERR_ALREADYREGISTRED() {
		return ": 462 :Unauthorized command (already registered)";
	}

	static string const ERR_NONICKNAMEGIVEN() {
		return ": 431 :No nickname given";
	}

	static string const ERR_NICKNAMEINUSE(string const &nick) {
		return ": 433 " + nick + " :Nickname is already in use";
	}

	static string const ERR_UNAVAILRESOURCE(string const &input) {
		return ": 437 " + input + " :Nick/channel is temporarily unavailable";
	}

	static string const ERR_ERRONEUSNICKNAME(string const &nick) {
		return ": 432 " + nick + " :Erroneous nickname";
	}

	static string const ERR_NICKCOLLISION(string const &nick, string const &user, string const &host) {
		return ": 436 " + nick + " :Nickname collision KILL from " + user + "@" + host;
	}

	static string const ERR_RESTRICTED() {
		return ": 484 :Your connection is restricted!";
	}

	
};
