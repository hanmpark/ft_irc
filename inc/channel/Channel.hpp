#pragma once

# include "IRCIncludes.hpp"
# include "client/ClientList.hpp"

class ClientList;

class Channel {
private:
	string			_name, _topic, _key;
	ClientList		_clients, _operators, _invited;
	size_t			_limit;
	unsigned int	_modes;

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

	ClientList		&getClientsList();
	ClientList		&getOperatorsList();
	ClientList		&getInvitedList();

	void	addMode(e_modes mode);
	void	removeMode(e_modes mode);
	void	removeClient(Client *client);

	void	setTopic(string const &topic);
	void	setKey(string const &key);
	void	setLimit(int limit);
};
