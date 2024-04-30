#pragma once

# include "Server.hpp"
# include "client/Client.hpp"
# include "channel/Channel.hpp"

# ifdef WLOGS
#  define DEBUG true
# else
#  define DEBUG false
# endif

class Server;

enum e_endpoint {
	CLIENT,
	SERVER
};

class Reply {
private:
	Reply();

public:
	static string const	findPrefix(Server &server, Client *client, e_endpoint const &side);
	static void			sendRPL(Server &server, Client *client, string const &message, e_endpoint const &endPoint);
	static void			sendRPL(Server &server, Client *from, Client *to, string const &message, e_endpoint const &endPoint);
	static void			sendRPL(Server &server, Client *from, Channel *to, string const &message, e_endpoint const &endPoint, bool const &withoutUser);
	static void			debugLog(string const &errorLog, bool const &debug);
	static void			debugLog(vector<string> const &args, bool const &debug);
};

class RPL {
private:
	RPL();

public:
	static string const RPL_WELCOME(string const &client) { return "001 " + client + " :Welcome to the Internet Relay Network " + client + "\r\n"; }
	static string const RPL_NOTOPIC(string const &client, string const &channel) { return "331 " + client + " " + channel + " :No topic is set\r\n"; }
	static string const RPL_TOPIC(string const &client, string const &channel, string const &topic) { return "332 " + client + " " + channel + " :" + topic + "\r\n"; }
	static string const RPL_INVITING(string const &client, string const &destNick, string const &channel) { return "341 " + client + " " + destNick + " " + channel + "\r\n"; }
	static string const RPL_NAMREPLY(string const &client, string const &channel, string const &names) { return "353 " + client + " = " + channel + " :" + names + "\r\n"; }
	static string const RPL_ENDOFNAMES(string const &client, string const &channel) { return "366 " + client + " " + channel + " :End of /NAMES list\r\n"; }
	static string const RPL_MOTD(string const &client, string const &message) { return "372 " + client + " :- " + message + "\r\n"; }
	static string const RPL_MOTDSTART(string const &client, string const &serverName) { return "375 " + client + " :- " + serverName + " Message of the day -\r\n"; }
	static string const RPL_ENDOFMOTD(string const &client) { return "376 " + client + " :End of /MOTD command.\r\n"; }
	static string const RPL_YOUREOPER(string const &client) { return "381 " + client + " :You are now an IRC operator\r\n"; }
};

class ERR {
private:
	ERR();

public:
	static string const ERR_NOSUCHNICK(string const &client, string const &nick) { return "401 " + client + " " + nick + " :No such nick/channel\r\n"; }
	static string const ERR_NOSUCHCHANNEL(string const &client, string const &channel) { return "403 " + client + " " + channel + " :No such channel\r\n"; }
	static string const ERR_CANNOTSENDTOCHAN(string const &client, string const &channel) { return "404 " + client + " " + channel + " :Cannot send to channel\r\n"; }
	static string const ERR_NORECIPIENT(string const &client, string const &command) { return "411 " + client + " :No recipient given (" + command + ")\r\n"; }
	static string const ERR_NOTEXTTOSEND(string const &client) { return "412 " + client + " :No text to send\r\n"; }
	static string const ERR_UNKNOWNCOMMAND(string const &client, string const &command) { return "421 " + (client.empty() ? "*" : client) + " " + command + " :Unknown command\r\n"; }
	static string const ERR_NONICKNAMEGIVEN(string const &client) { return "431 " + (client.empty() ? "*" : client) + " :No nickname given\r\n"; }
	static string const ERR_ERRONEUSNICKNAME(string const &client, string const &nick) { return "432 " + (client.empty() ? "*" : client) + " " + nick + " :Erroneous nickname\r\n"; }
	static string const ERR_NICKNAMEINUSE(string const &client, string const &nick) { return "433 " + (client.empty() ? "*" : client) + " " + nick + " :Nickname is already in use\r\n"; }
	static string const ERR_USERNOTINCHANNEL(string const &client, string const &nick, string const &channel) { return "441 " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n"; }
	static string const ERR_NOTONCHANNEL(string const &client, string const &channel) { return "442 " + client + " " + channel + " :You're not on that channel\r\n"; }
	static string const ERR_USERONCHANNEL(string const &client, string const &nick, string const &channel) { return "443 " + (client.empty() ? "*" : client) + " " + nick + " " + channel + " :is already on channel\r\n"; }
	static string const ERR_NOTREGISTERED(string const &client) { return "451 " + (client.empty() ? "*" : client) + " :You have not registered\r\n"; }
	static string const ERR_NEEDMOREPARAMS(string const &client, string const &command) { return "461 " + (client.empty() ? "*" : client) + " " + command + " :Not enough parameters\r\n"; }
	static string const ERR_ALREADYREGISTRED(string const &client) { return "462 " + client + " :You may not reregister\r\n"; }
	static string const ERR_PASSWDMISMATCH(string const &client) { return "464 " + (client.empty() ? "*" : client) + " :Password incorrect\r\n"; }
	static string const ERR_CHANNELISFULL(string const &client, string const &channel) { return "471 " + client + " " + channel + " :Cannot join channel (+l)\r\n"; }
	static string const ERR_UNKNOWNMODE(string const &client, string const &mode) { return "472 " + client + " " + mode + " :is unknown mode char to me\r\n"; }
	static string const ERR_INVITEONLYCHAN(string const &client, string const &channel) { return "473 " + client + " " + channel + " :Cannot join channel (+i)\r\n"; }
	static string const ERR_BADCHANNELKEY(string const &client, string const &channel) { return "475 " + client + " " + channel + " :Cannot join channel (+k)\r\n"; }
	static string const ERR_CHANOPRIVSNEEDED(string const &client, string const &channel) { return "482 " + client + " " + channel + " :You're not channel operator\r\n"; }
};

class CMD {
private:
	CMD();

public:
	static string const INVITE(string const &nick, string const &channel) { return "INVITE " + nick + " :" + channel + "\r\n"; }
	static string const JOIN(string const &channel) { return "JOIN " + channel + "\r\n"; }
	static string const KICK(string const &channel, string const &nick, string const &message) { return "KICK " + channel + " " + nick + " :" + (message.empty() ? nick : message) + "\r\n"; }
	static string const MODE(string const &channel, string const &modeString, string const &modeArgs) { return "MODE " + channel + " " + modeString + " " + modeArgs + "\r\n"; }
	static string const NICK(string const &nick) { return "NICK :" + nick + "\r\n"; }
	static string const PART(string const &channel, string const &message) { return "PART " + channel + (message.empty() ? " " : " :" + message) + "\r\n"; }
	static string const PING(string const &server, string const &token) { return "PONG " + server + " " + token + "\r\n"; }
	static string const PRIVMSG(string const &target, string const &message) { return "PRIVMSG " + target + " :" + message + "\r\n"; }
	static string const QUIT(string const &message) { return "QUIT :" + message + "\r\n"; }
	static string const TOPIC(string const &channel, string const &topic) { return "TOPIC " + channel + " :" + topic + "\r\n"; }
};
