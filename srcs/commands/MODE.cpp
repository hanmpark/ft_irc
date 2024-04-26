#include "commands/MODE.hpp"

MODE::MODE() {
	_modeMap[{"i", true}] = &INVITE;
	_modeMap[{"i", false}] = &UNINVITE;
	_modeMap[{"t", true}] = &TOPIC;
	_modeMap[{"t", false}] = &UNTOPIC;
	_modeMap[{"k", true}] = &KEY;
	_modeMap[{"k", false}] = &UNKEY;
	_modeMap[{"o", true}] = &OP;
	_modeMap[{"o", false}] = &DEOP;
	_modeMap[{"l", true}] = &LIMIT;
	_modeMap[{"l", false}] = &UNLIMIT;
}

MODE::~MODE() { _modeMap.clear(); }

bool	MODE::INVITE(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
	static_cast<void>(modeArgs);
	if (!(channel->getModes() & Channel::INVITE)) {
		channel->addMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::UNINVITE(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
	static_cast<void>(modeArgs);
	if (channel->getModes() & Channel::INVITE) {
		channel->removeMode(Channel::INVITE);
		return true;
	}
	return false;
}

bool	MODE::TOPIC(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
	static_cast<void>(modeArgs);
	if (!(channel->getModes() & Channel::TOPIC)) {
		channel->addMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::UNTOPIC(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
	static_cast<void>(modeArgs);
	if (channel->getModes() & Channel::TOPIC) {
		channel->removeMode(Channel::TOPIC);
		return true;
	}
	return false;
}

bool	MODE::KEY(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
	if (modeArgs.empty()) {
		return false;
	}
	channel->addMode(Channel::KEY);
	channel->setKey(modeArgs.front());
	modeArgs.pop_front();
	return true;
}

bool	MODE::UNKEY(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	static_cast<void>(server);
	static_cast<void>(client);
	static_cast<void>(args);
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

bool	MODE::OP(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	if (server.getClientList().getClientByNickname(modeArgs.front()) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(modeArgs.front()));
		modeArgs.pop_front();
		return false;
	} else {
		channel->getOperators().addClient(server.getClientList().getClientByNickname(modeArgs.front()));
		modeArgs.pop_front();
	}
	return true;
}

bool	MODE::DEOP(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	if (server.getClientList().getClientByNickname(modeArgs.front()) == NULL) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHNICK(modeArgs.front()));
		modeArgs.pop_front();
		return false;
	} else {
		channel->getOperators().removeClient(server.getClientList().getClientByNickname(modeArgs.front()));
		modeArgs.pop_front();
	}
	return true;
}

bool	MODE::LIMIT(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	if (args.size() != 4) {
		return false;
	}
	channel->addMode(Channel::LIMIT);
	channel->setLimit(atoi(args[3].c_str()));
	return true;
}

bool	MODE::UNLIMIT(Server &server, Channel *channel, Client *client, vector<string> &args, deque<string> &modeArgs) const {
	if (args.size() < 3) {
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

bool	MODE::_isEnoughModeArgs(string const &modeString, deque<string> const &modeArgs) const {
	size_t	count = 0;

	for (size_t i = 0; i < modeString.length(); i++) {
		count += modeString[i] == 'o' || modeString[i] == 'l' || modeString[i] == 'k';
		if ((modeString[i] == 'o' || modeString[i] == 'l') && count > modeArgs.size()) {
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
	deque<string>	modeArgs = _getModeArgs(args);

	if (!_isEnoughModeArgs(modeString, modeArgs)) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
		return "";
	}
	for (size_t i = 0; i < modeString.length(); i++) {
		if (modeString[i] == '+' || modeString[i] == '-') {
			applyMode = modeString[i] == '+';
			i++;
		}
		// if (_modeMap.find({modeString.substr(i, 1), applyMode}) != _modeMap.end()) {
		// 	if ((this->*_modeMap.at({modeString.substr(i, 1), applyMode}))(channel, client, modeArgs)) {
		// 		if (_addFlagToModeArgs(modeStringApplied, applyMode)) {
		// 			modeStringApplied += (applyMode == true ? "+" : "-") + modeString.substr(i, 1);
		// 		} else {
		// 			modeStringApplied += modeString.substr(i, 1);
		// 		}
		// 	}
		// } else {
		// 	RPL::sendRPL(server, client, IRCErrors::ERR_UNKNOWNMODE(modeString.substr(i, 1)));
		// 	return "";
		// }
	}
	return modeStringApplied;
}

void	MODE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 2) {
		RPL::sendRPL(server, client, IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
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
			RPL::sendRPL(server, client, IRCErrors::ERR_NOSUCHCHANNEL(args[1]));
		}
	}
}
