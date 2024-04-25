#include "commands/MODE.hpp"

MODE::MODE() {}

MODE::~MODE() {}

bool	MODE::INVITE(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (!(channel->getModes() & Channel::INVITE)) {
			channel->addMode(Channel::INVITE);
			return true;
		}
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::UNINVITE(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (channel->getModes() & Channel::INVITE) {
			channel->removeMode(Channel::INVITE);
			return true;
		}
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::TOPIC(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (!(channel->getModes() & Channel::TOPIC)) {
			channel->addMode(Channel::TOPIC);
			return true;
		}
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::UNTOPIC(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (channel->getModes() & Channel::TOPIC) {
			channel->removeMode(Channel::TOPIC);
			return true;
		}
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::KEY(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (args.size() != 4) {
			return false;
		}
		channel->addMode(Channel::KEY);
		channel->setKey(args[3]);
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::UNKEY(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		channel->removeMode(Channel::KEY);
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::OP(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (channel->getOperators().getClientByNickname(client->getNickname()) == NULL) {
			channel->getOperators().addClient(client);
		}
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::DEOP(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (channel->getOperators().getClientByNickname(client->getNickname()) != NULL) {
			channel->getOperators().removeClient(client);
		}
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::LIMIT(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (args.size() != 4) {
			return false;
		}
		channel->addMode(Channel::LIMIT);
		channel->setLimit(atoi(args[3].c_str()));
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

bool	MODE::UNLIMIT(Server &server, Client *client, vector<string> &args) const {
	Channel *channel = server.getChannelList().getChannelByName(args[1]);

	if (channel) {
		if (args.size() < 3) {
			return false;
		}
		channel->removeMode(Channel::LIMIT);
		return true;
	} else {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
	}
	return false;
}

map<pair<string, bool>, MODE::modeFunction> const	MODE::_initModeMap() const {
	map<pair<string, bool>, modeFunction>	modeMap;

	modeMap[{"i", true}] = &INVITE;
	modeMap[{"i", false}] = &UNINVITE;
	modeMap[{"t", true}] = &TOPIC;
	modeMap[{"t", false}] = &UNTOPIC;
	modeMap[{"k", true}] = &KEY;
	modeMap[{"k", false}] = &UNKEY;
	modeMap[{"o", true}] = &OP;
	modeMap[{"o", false}] = &DEOP;
	modeMap[{"l", true}] = &LIMIT;
	modeMap[{"l", false}] = &UNLIMIT;
	return modeMap;
}

bool	MODE::_addFlagToModeArgs(string const &modeArgs, bool flag) const {
	size_t	plus = modeArgs.find_last_of("+");
	size_t	minus = modeArgs.find_last_of("-");

	if (plus == string::npos && minus == string::npos) {
		return true;
	}
	return (plus > minus) != flag;
}

void	MODE::execute(Server &server, Client *client, std::vector<std::string> &args) const {
	static map<pair<string, bool>, modeFunction> const	modeFunctions = _initModeMap();
	bool	changedMode = false;

	if (args.size() < 2) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
	} else if (args.size() > 2) {
		bool			flagOn = true;
		string			mode = args[2], modeArgs;
		for (size_t i = 0; i < mode.length(); i++) {
			if (mode[i] == '+' || mode[i] == '-') {
				flagOn = mode[i] == '+';
				i++;
			}
			if (modeFunctions.find({mode.substr(i, 1), flagOn}) != modeFunctions.end()) {
				if ((this->*modeFunctions.at({mode.substr(i, 1), flagOn}))(server, client, args)) {
					changedMode = true;
					if (_addFlagToModeArgs(modeArgs, flagOn)) {
						modeArgs += (flagOn == true ? "+" : "-") + mode.substr(i, 1);
					} else {
						modeArgs += mode.substr(i, 1);
					}
				}
			} else {
				RPL::sendRPL(server, client, IRCErrors::ERR_UNKNOWNMODE(mode.substr(i, 1)));
				return;
			}
		}
		if (changedMode) {
			args.insert(args.begin() + 2, modeArgs);
			args.erase(args.begin() + 2);
			RPL::sendRPL(server, client, args);
		}
	}
}
