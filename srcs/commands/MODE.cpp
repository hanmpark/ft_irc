#include <algorithm>

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

	if (modeArgs.empty())
		return false;
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
	if (channel->getClientsList().getClient(modeArgs[*modeArgsIndex]) == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHNICK(client->getNickname(), modeArgs[*modeArgsIndex]), SERVER);
		modeArgs.erase(modeArgs.begin());
		return false;
	} else if (channel->getOperatorsList().getClient(modeArgs[*modeArgsIndex]) == NULL) {
		channel->getOperatorsList().addClient(server.getClient(modeArgs[*modeArgsIndex]));
	}
	(*modeArgsIndex)++;
	return true;
}

bool	MODE::DEOP(Server &server, Channel *channel, Client *client, vector<string> &modeArgs, size_t *modeArgsIndex) const {
	if (channel->getClientsList().getClient(modeArgs[*modeArgsIndex]) == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_NOSUCHNICK(client->getNickname(), modeArgs[*modeArgsIndex]), SERVER);
		modeArgs.erase(modeArgs.begin());
		return false;
	} else if (channel->getOperatorsList().getClient(modeArgs[*modeArgsIndex]) != NULL) {
		channel->getOperatorsList().removeClient(server.getClient(modeArgs[*modeArgsIndex]));
	}
	(*modeArgsIndex)++;
	return true;
}

bool	MODE::_checkLimitArg(string const &arg) const {
	for (size_t i = 0; i < arg.length(); i++) {
		if (!isdigit(arg[i]))
			return false;
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

	if (!(channel->getModes() & Channel::LIMIT))
		return false;
	channel->removeMode(Channel::LIMIT);
	return true;
}

/**
 * @brief Determines whether a flag should be added to the mode string based on the current mode string and the flag being set.
 *
 * @param modeArgs The current mode string.
 * @param flag The flag being set.
 *
 * @return True if the flag should be added to the mode string, false otherwise.
 */
bool	MODE::_addFlagToModeArgs(string const &modeArgs, bool flag) const {
	size_t	plus = modeArgs.find_last_of("+");
	size_t	minus = modeArgs.find_last_of("-");

	if (plus != string::npos && (minus == string::npos || plus > minus)) {
		return true != flag;
	} else if (minus != string::npos && (plus == string::npos || minus > plus)) {
		return false != flag;
	}
	return true;
}

/**
 * @brief Checks if the number of mode arguments provided is valid for the given mode string.
 *
 * @param modeString The mode string to check.
 * @param modeArgsSize The number of mode arguments provided.
 *
 * @return True if the number of arguments is valid, false otherwise.
 */
bool	MODE::_checkNumberModeArgs(string const &modeString, size_t modeArgsSize) const {
	size_t	count = 0;
	bool	applyMode = true;

	for (size_t i = 0; i < modeString.length(); i++) {
		if (modeString[i] == '+' || modeString[i] == '-') {
			applyMode = modeString[i] == '+';
			continue;
		}
		count += modeString[i] == 'o' || (modeString[i] == 'l' && applyMode == true) || modeString[i] == 'k';
	}
	if (count > modeArgsSize)
		return false;
	return true;
}

/**
 * @brief Extracts the mode arguments from the given vector of command arguments.
 *
 * @param args The vector of command arguments.
 *
 * @return A vector of mode arguments.
 */
vector<string>	MODE::_getModeArgs(vector<string> const &args) const {
	vector<string>	modeArgs;

	for (size_t i = 3; i < args.size(); i++) {
		modeArgs.push_back(args[i]);
	}
	return modeArgs;
}

/**
 * @brief Applies the mode setting specified in the modeString parameter to the channel.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param channel The channel object pointer.
 * @param modeString The string containing the mode setting to apply.
 * @param modeArgs The vector of mode arguments.
 *
 * @return A string containing the mode settings that were successfully applied to the channel.
 */
string const	MODE::_applyModeSetting(Server &server, Client *client, Channel *channel, string const &modeString, vector<string> &modeArgs) const {
	bool	applyMode = true;
	size_t	modeArgsIndex = 0;
	string	modeStringApplied;

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
			Reply::sendRPL(server, client, ERR::ERR_UNKNOWNMODE(client->getNickname(), modeString.substr(i, 1)), SERVER);
		}
	}
	return modeStringApplied;
}

/**
 * @brief Parses the mode setting command and applies the changes to the specified channel.
 *
 * @param server The server object reference.
 * @param client The client object pointer.
 * @param channel The channel object pointer.
 * @param args The vector of command arguments.
 */
void	MODE::_parseModeSetting(Server &server, Client *client, Channel *channel, vector<string> &args) const {
	string			modeStringApplied;
	vector<string>	modeArgs;

	if (channel->getOperatorsList().getClient(client->getFd()) == NULL) {
		Reply::sendRPL(server, client, ERR::ERR_CHANOPRIVSNEEDED(client->getNickname(), channel->getName()), SERVER);
	} else if (!_checkNumberModeArgs(args[2], (args.size() < 3 ? 0 : args.size() - 3))) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else {
		modeArgs = _getModeArgs(args);
		modeStringApplied = _applyModeSetting(server, client, channel, args[2], modeArgs);

		if (!modeStringApplied.empty()) {
			string	appliedArgs;
			for (vector<string>::const_iterator it = modeArgs.begin(); it != modeArgs.end(); it++) {
				appliedArgs += *it + (it + 1 != modeArgs.end() ? " " : "");
			}
			Reply::sendRPL(server, client, channel, CMD::MODE(channel->getName(), modeStringApplied, appliedArgs), CLIENT, false);
		}
	}
}

/**
 * @brief Executes the MODE command.
 *
 * Syntax: MODE <channel> [<mode> [<mode params>]]
 *
 * The MODE command is used to set or change the mode of a channel.
 * The first argument is the target of the command.
 * The second argument is the mode to set or change.
 * The third argument (if present) is the mode parameter.
 *
 * @param server The server object reference.
 * @param client The client object that sent the command.
 * @param args The vector of command arguments.
 */
void	MODE::execute(Server &server, Client *client, vector<string> &args) const {
	if (args.size() < 3) {
		Reply::sendRPL(server, client, ERR::ERR_NEEDMOREPARAMS(client->getNickname(), args[0]), SERVER);
	} else if (args.size() > 2) {
		Channel	*channel = server.getChannel(args[1]);

		if (channel) {
			_parseModeSetting(server, client, channel, args);
		} else {
			Reply::sendRPL(server, client, ERR::ERR_NOSUCHCHANNEL(client->getNickname(), args[1]), SERVER);
		}
	}
}
