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
	static void		sendRPL(Server &server, Client *client, string const &message, e_endpoint const &endPoint);
	static void		sendRPL(Server &server, Client *from, Client *to, string const &message, e_endpoint const &endPoint);
	static void		debugLog(string const &errorLog, bool const &debug);
	static void		debugLog(vector<string> const &args, bool const &debug);
	static void		debugLog(Server &server, Client *client, vector<string> const &args, e_endpoint const &endPoint, bool const &debug);
};

struct IRCReplies {
	static string const RPL_WELCOME(string const &nick, string const &user) { return "001 " + nick + " :Welcome to the Internet Relay Network " + user + "\r\n"; }
	static string const RPL_NOTOPIC(string const &nick, string const &channel) { return "331 " + nick + " " + channel + " :No topic is set\r\n"; }
	static string const RPL_TOPIC(string const &nick, string const &channel, string const &topic) { return "332 " + nick + " " + channel + " :" + topic + "\r\n"; }
	static string const RPL_INVITING(string const &nick, string const &destNick, string const &channel) { return "341 " + nick + " " + destNick + " " + channel + "\r\n"; }
	static string const RPL_NAMREPLY(string const &nick, string const &channel, string const &names) { return "353 " + nick + " = " + channel + " :" + names + "\r\n"; }
	static string const RPL_ENDOFNAMES(string const &nick, string const &channel) { return "366 " + nick + " " + channel + " :End of /NAMES list\r\n"; }
	static string const RPL_YOUREOPER(string const &nick) { return "381 " + nick + " :You are now an IRC operator\r\n"; }
};

class IRCErrors {
private:
	IRCErrors();

public:
	static string const ERR_NOSUCHNICK(string const &nick, string const &newNick) { return "401 " + nick + " " + newNick + " :No such nick/channel\r\n"; }
	static string const ERR_NOSUCHCHANNEL(string const &nick, string const &channel) { return "403 " + nick + " " + channel + " :No such channel\r\n"; }
	static string const ERR_CANNOTSENDTOCHAN(string const &nick, string const &channel) { return "404 " + nick + " " + channel + " :Cannot send to channel\r\n"; }
	static string const ERR_NORECIPIENT(string const &nick, string const &command) { return "411 " + nick + " :No recipient given (" + command + ")\r\n"; }
	static string const ERR_NOTEXTTOSEND(string const &nick) { return "412 " + nick + " :No text to send\r\n"; }
	static string const ERR_UNKNOWNCOMMAND(string const &nick, string const &command) { return "421 " + nick + " " + command + " :Unknown command\r\n"; }
	static string const ERR_NONICKNAMEGIVEN(string const &nick) { return "431 " + nick + " :No nickname given\r\n"; }
	static string const ERR_ERRONEUSNICKNAME(string const &nick) { return "432 " + nick + " :Erroneous nickname\r\n"; }
	static string const ERR_NICKNAMEINUSE(string const &nick) { return "433 " + nick + " :Nickname is already in use\r\n"; }
	static string const ERR_NOTONCHANNEL(string const &nick, string const &channel) { return "442 " + nick + " " + channel + " :You're not on that channel\r\n"; }
	static string const ERR_USERONCHANNEL(string const &nick, string const &channel) { return "443 " + nick + " " + channel + " :is already on channel\r\n"; }
	static string const ERR_NOTREGISTERED(string const &nick) { return "451 " + nick + " :You have not registered\r\n"; }
	static string const ERR_NEEDMOREPARAMS(string const &nick, string const &command) { return "461 " + nick + " " + command + " :Not enough parameters\r\n"; }
	static string const ERR_ALREADYREGISTRED(string const &nick) { return "462 " + nick + " :You may not reregister\r\n"; }
	static string const ERR_PASSWDMISMATCH(string const &nick) { return "464 " + nick + " :Password incorrect\r\n"; }
	static string const ERR_CHANNELISFULL(string const &nick, string const &channel) { return "471 " + nick + " " + channel + " :Cannot join channel (+l)\r\n"; }
	static string const ERR_UNKNOWNMODE(string const &nick, string const &mode) { return "472 " + nick + " " + mode + " :is unknown mode char to me\r\n"; }
	static string const ERR_INVITEONLYCHAN(string const &nick, string const &channel) { return "473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n"; }
	static string const ERR_BADCHANNELKEY(string const &nick, string const &channel) { return "475 " + nick + " " + channel + " :Cannot join channel (+k)\r\n"; }
	static string const ERR_CHANOPRIVSNEEDED(string const &nick, string const &channel) { return "482 " + nick + " " + channel + " :You're not channel operator\r\n"; }
};
