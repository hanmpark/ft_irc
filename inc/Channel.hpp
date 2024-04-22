#pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Channel {
private:
	string						_name;
	string						_topic;
	string						_key;
	string						_creator;
	vector<Client*>				_users;
	vector<Client*>				_operators;
	size_t						_limit;

public:
	Channel();
	Channel(string const &name);
	~Channel();

	string	getName() const;
	string	getTopic() const;
	string	getKey() const;
	string	getCreator() const;
	size_t	getLimit() const;

	void	setCreator(string const &creator);
	void	setTopic(string const &topic);
	void	setKey(string const &key);

	void	addClient(Client *client);
	void	removeClient(Client *client);
	void	addOperator(Client *client);
	void	removeOperator(Client *client);

	// Needed ?
	vector<Client*>	&getUsers();
	vector<Client*>	&getOperators();

};
