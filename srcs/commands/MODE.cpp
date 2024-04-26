#include "commands/MODE.hpp"

MODE::MODE() {
	_modeMap[make_pair("i", true)] = &MODE::INVITE;
	_modeMap[make_pair("i", false)] = &MODE::UNINVITE;
	_modeMap[make_pair("t", true)] = &MODE::TOPIC;
	_modeMap[make_pair("t", false)] = &MODE::UNTOPIC;
	_modeMap[make_pair("k", true)] = &MODE::KEY;
	_modeMap[make_pair("k", false)] = &MODE::UNKEY;
	_modeMap[make_pair("o", true)] = &MODE::OP;
	_modeMap[make_pair("o", false)] = &MODE::DEOP;
	_modeMap[make_pair("l", true)] = &MODE::LIMIT;
	_modeMap[make_pair("l", false)] = &MODE::UNLIMIT;
}

MODE::~MODE() { _modeMap.clear(); }

bool	MODE::INVITE(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	if (!(channel->getModes() & Channel::INVITE)) {
		channel->addMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::UNINVITE(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	if (channel->getModes() & Channel::INVITE) {
		channel->removeMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::TOPIC(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	if (!(channel->getModes() & Channel::TOPIC)) {
		channel->addMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::UNTOPIC(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	if (channel->getModes() & Channel::TOPIC) {
		channel->removeMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::KEY(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (modeArgs.empty()) {
		return false;
	}
	channel->addMode(Channel::KEY);
	channel->setKey(modeArgs.front());
	modeArgs.pop_front();
	return true;
}

bool	MODE::UNKEY(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (modeArgs.empty()) {
		return false;
	} else if (!(channel->getModes() & Channel::KEY)) {
		modeArgs.pop_front();
		return false;
	}
	channel->removeMode(Channel::KEY);
	modeArgs.pop_front();
	return true;
}

bool	MODE::OP(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	if (server.getClientList().getClientByNickname(modeArgs.front()) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(client->getNickname() + " " + modeArgs.front()));
		modeArgs.pop_front();
		return false;
	} else {
		channel->getOperators().addClient(server.getClientList().getClientByNickname(modeArgs.front()));
		modeArgs.pop_front();
	}
	return true;
}

bool	MODE::DEOP(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	if (server.getClientList().getClientByNickname(modeArgs.front()) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(client->getNickname() + " " + modeArgs.front()));
		modeArgs.pop_front();
		return false;
	} else {
		channel->getOperators().removeClient(server.getClientList().getClientByNickname(modeArgs.front()));
		modeArgs.pop_front();
	}
	return true;
}

bool	MODE::_checkLimitArg(string const &arg) const {
	for (size_t i = 0; i < arg.length(); i++) {
		if (!isdigit(arg[i])) {
			return false;
		}
	}
	return true;
}

bool	MODE::LIMIT(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (!_checkLimitArg(modeArgs.front())) {
		modeArgs.pop_front();
		return false;
	}
	channel->addMode(Channel::LIMIT);
	channel->setLimit(atoi(modeArgs.front().c_str()));
	modeArgs.pop_front();
	return true;
}

bool	MODE::UNLIMIT(Server &server, Channel *channel, Client *client, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	if (!(channel->getModes() & Channel::LIMIT)) {
		return false;
	}
	channel->removeMode(Channel::LIMIT);
	return true;
}

bool	MODE::_addFlagToModeArgs(string const &modeArgs, bool flag) const {
	size_t	plus = modeArgs.find_last_of("+");
	size_t	minus = modeArgs.find_last_of("-");

	if (plus == string::npos && minus == string::npos) {
		return true;
	}
	return (plus > minus) != flag;
}

bool	MODE::_formatModeArgs(string const &modeString, vector<string> &args) const {
	size_t	count = 0, modeArgsSize = (args.size() - 3 < 0 ? 0 : args.size() - 3);
	bool	applyMode = true;

	for (size_t i = 0; i < modeString.length(); i++) {
		if (modeString[i] == '+' || modeString[i] == '-') {
			applyMode = modeString[i] == '+';
			continue;
		} else if (modeString[i] == 'k') {
			args[count] = "*";
		}
		count += modeString[i] == 'o' || (modeString[i] == 'l' && applyMode == true) || modeString[i] == 'k';
		if ((modeString[i] == 'o' || (modeString[i] == 'l' && applyMode == true)) && count > modeArgsSize) {
			return false;
		}
	}
	return true;
}

deque<string>	MODE::_getModeArgs(vector<string> const &args) const {
	deque<string>	modeArgs;

	for (size_t i = 2; i < args.size(); i++) {
		modeArgs.push_back(args[i]);
	}
	return modeArgs;
}

string const	MODE::_applyModeSetting(Server &server, Client *client, Channel *channel, vector<string> &args) const {
	bool	applyMode = true;
	string	modeStringApplied, modeString = args[2];

	if (!_formatModeArgs(modeString, args)) {
		throw IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname() + " " + args[0]);
	}
	deque<string>	modeArgs = _getModeArgs(args);
	for (size_t i = 0; i < modeString.length(); i++) {
		if (modeString[i] == '+' || modeString[i] == '-') {
			applyMode = modeString[i] == '+';
			continue;
		}
		if (_modeMap.find(make_pair(modeString.substr(i, 1), applyMode)) != _modeMap.end()) {
			if ((this->*_modeMap.at(make_pair(modeString.substr(i, 1), applyMode)))(server, channel, client, modeArgs)) {
				if (_addFlagToModeArgs(modeStringApplied, applyMode)) {
					modeStringApplied += (applyMode == true ? "+" : "-") + modeString.substr(i, 1);
				} else {
					modeStringApplied += modeString.substr(i, 1);
				}
			}
		} else {
			throw IRCErrors::ERR_UNKNOWNCOMMAND(client->getNickname() + " " + modeString.substr(i, 1));
		}
	}
	return modeStringApplied;
}

void	MODE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		throw IRCErrors::ERR_NEEDMOREPARAMS(args[0]);
	} else if (args.size() > 2) {
		Channel	*channel = server.getChannelList().getChannelByName(args[1]);

		if (channel) {
			string	modeStringApplied = _applyModeSetting(server, client, channel, args);
			if (!modeStringApplied.empty()) {
				args.erase(args.begin() + 2);
				args.insert(args.begin() + 2, modeStringApplied);
				RPL::sendRPL(server, client, args);
			}
		} else {
			throw IRCErrors::ERR_NOSUCHCHANNEL(args[1]);
		}
	}
}
