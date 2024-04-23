#pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Channel {
private:
	string						_name;
	string						_topic;
	string						_key;
	string						_creator;
	vector<Client*>				_users; // conflicts with var in Server Class. So changed to _users
	vector<Client*>				_operators;
	size_t						_limit;

	struct ChannelMODES {
		bool	inviteOnly; // +i => invite only
		bool	topicReserved; // +t => reserved to operators only
		bool	keyProtected; // +k => key is needed to join the channel
		bool	limitSet; // +l => limit of users in the channel
	};

	ChannelMODES				_modes;

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

	void	addClient(Client *client); //? change to addUsers
	void	removeClient(Client *client); //? change to removeUsers
	void	addOperator(Client *client);
	void	removeOperator(Client *client);

	vector<Client*>	&getUsers();
	vector<Client*>	&getOperators();

};
