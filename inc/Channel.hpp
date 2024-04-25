#pragma once

# include "IRCIncludes.hpp"

class ClientList;

class Channel {
private:
	string			_name;
	string			_topic;
	string			_key;
	ClientList		_users;
	ClientList		_operators;
	ClientList		_invited;
	size_t			_limit;
	unsigned int	_modes = NOMODE;

public:
	Channel();
	Channel(string const &name);
	~Channel();

	enum e_modes {
		NOMODE	= 0,
		INVITE	= 1,
		TOPIC	= 1 << 1,
		KEY		= 1 << 2,
		LIMIT	= 1 << 3
	};

	string			getName() const;
	string			getTopic() const;
	string			getKey() const;
	size_t			getLimit() const;
	unsigned int	getModes() const;

	ClientList		&getUsers();
	ClientList		&getOperators();
	ClientList		&getInvited();

	void	addMode(e_modes mode);
	void	removeMode(e_modes mode);

	void	setTopic(string const &topic);
	void	setKey(string const &key);
	void	setLimit(int limit);
};
