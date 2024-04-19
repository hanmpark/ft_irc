#pragma once

# include "IrcIncludes.hpp"
# include "Client.hpp"

class Channel {
private:
	string						_name;
	string						_topic;
	string						_key;
	string						_creator;
	vector<Client*>				_clients;

public:
	Channel();
	Channel(string const &name);
	~Channel();

	string	getName() const;
	string	getTopic() const;
	string	getKey() const;
	string	getCreator() const;

	
};
