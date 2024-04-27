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

bool	MODE::INVITE(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	static_cast<void>(modeArgsIndex);
	if (!(channel->getModes() & Channel::INVITE)) {
		channel->addMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::UNINVITE(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	static_cast<void>(modeArgsIndex);
	if (channel->getModes() & Channel::INVITE) {
		channel->removeMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::TOPIC(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	static_cast<void>(modeArgsIndex);
	if (!(channel->getModes() & Channel::TOPIC)) {
		channel->addMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::UNTOPIC(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	static_cast<void>(modeArgsIndex);
	if (channel->getModes() & Channel::TOPIC) {
		channel->removeMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::KEY(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (modeArgs.empty()) {
		return false;
	}
	channel->addMode(Channel::KEY);
	channel->setKey(modeArgs[*modeArgsIndex]);
	(*modeArgsIndex)++;
	return true;
}

bool	MODE::UNKEY(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (modeArgs.empty()) {
		return false;
	} else if (!(channel->getModes() & Channel::KEY)) {
		modeArgs.erase(modeArgs.begin());
		return false;
	}
	channel->removeMode(Channel::KEY);
	modeArgs[*modeArgsIndex] = "*";
	(*modeArgsIndex)++;
	return true;
}

bool	MODE::OP(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	if (server.getClientList().getClientByNickname(modeArgs[*modeArgsIndex]) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(client->getNickname(), modeArgs[*modeArgsIndex]), SERVER);
		modeArgs.erase(modeArgs.begin());
		return false;
	} else {
		channel->getOperators().addClient(server.getClientList().getClientByNickname(modeArgs[*modeArgsIndex]));
		(*modeArgsIndex)++;
	}
	return true;
}

bool	MODE::DEOP(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	if (server.getClientList().getClientByNickname(modeArgs[*modeArgsIndex]) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(client->getNickname(), modeArgs[*modeArgsIndex]), SERVER);
		modeArgs.erase(modeArgs.begin());
		return false;
	} else {
		channel->getOperators().removeClient(server.getClientList().getClientByNickname(modeArgs[*modeArgsIndex]));
		(*modeArgsIndex)++;
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

bool	MODE::LIMIT(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	if (!_checkLimitArg(modeArgs[*modeArgsIndex])) {
		modeArgs.erase(modeArgs.begin());
		return false;
	}
	channel->addMode(Channel::LIMIT);
	channel->setLimit(atoi(modeArgs[*modeArgsIndex].c_str()));
	(*modeArgsIndex)++;
	return true;
}

bool	MODE::UNLIMIT(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(modeArgs);
	static_cast<void>(modeArgsIndex);
	if (!(channel->getModes() & Channel::LIMIT)) {
		return false;
	}
	channel->removeMode(Channel::LIMIT);
	return true;
}

bool	MODE::_addFlagToModeArgs(string const &modeArgs, bool flag) const {
	size_t	plus = modeArgs.find_last_of("+");
	size_t	minus = modeArgs.find_last_of("-");

	if ((plus != string::npos && minus == string::npos) || plus > minus) {
		return true != flag;
	} else if ((minus != string::npos && plus == string::npos) || minus > plus) {
		return false != flag;
	}
	return true;
}

bool	MODE::_formatModeArgs(string const &modeString, size_t modeArgsSize) const {
	size_t	count = 0;
	bool	applyMode = true;

	for (size_t i = 0; i < modeString.length(); i++) {
		if (modeString[i] == '+' || modeString[i] == '-') {
			applyMode = modeString[i] == '+';
			continue;
		}
		count += modeString[i] == 'o' || (modeString[i] == 'l' && applyMode == true) || modeString[i] == 'k';
		if ((modeString[i] == 'o' || (modeString[i] == 'l' && applyMode == true)) && count > modeArgsSize) {
			return false;
		}
	}
	return true;
}

vector<string>	MODE::_getModeArgs(vector<string> const &args) const {
	vector<string>	modeArgs;

	for (size_t i = 3; i < args.size(); i++) {
		modeArgs.push_back(args[i]);
	}
	return modeArgs;
}

void	MODE::_applyModeSetting(Server &server, Client *client, Channel *channel, vector<string> &args) const {
	bool			applyMode = true;
	string			modeString = args[2];
	string			modeStringApplied;
	vector<string>	modeArgs;

	if (!_formatModeArgs(modeString, (args.size() - 3 < 0 ? 0 : args.size() - 3))) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		modeArgs = _getModeArgs(args);
		size_t	modeArgsIndex = 0;
		for (size_t i = 0; i < modeString.length(); i++) {
			if (modeString[i] == '+' || modeString[i] == '-') {
				applyMode = modeString[i] == '+';
				continue;
			}
			if (_modeMap.find(make_pair(modeString.substr(i, 1), applyMode)) != _modeMap.end()) {
				if ((this->*_modeMap.at(make_pair(modeString.substr(i, 1), applyMode)))(server, channel, client, modeArgs, &modeArgsIndex)) {
					if (_addFlagToModeArgs(modeStringApplied, applyMode)) {
						modeStringApplied += (applyMode == true ? "+" : "-") + modeString.substr(i, 1);
					} else {
						modeStringApplied += modeString.substr(i, 1);
					}
				}
			} else {
				RPL::sendRPL(server, client, IRCErrors::ERR_UNKNOWNMODE(client->getNickname(), modeString.substr(i, 1)), SERVER);
			}
		}
	}
	if (!modeStringApplied.empty()) {
		string	appliedArgs;

		for (vector<string>::const_iterator it = modeArgs.begin(); it != modeArgs.end(); it++) {
			appliedArgs += *it + (it + 1 != modeArgs.end() ? " " : "");
		}
		RPL::sendRPL(server, client, "MODE " + channel->getName() + " " + modeStringApplied + " " + appliedArgs + "\r\n", CLIENT);
	}
}

void	MODE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else if (args.size() > 2 && args[1][0] == '#') {
		Channel	*channel = server.getChannelList().getChannelByName(args[1]);

		if (channel) {
			_applyModeSetting(server, client, channel, args);
		} else {
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(client->getNickname(), args[1]), SERVER);
		}
	}
}
