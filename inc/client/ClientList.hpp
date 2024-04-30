#pragma once

# include <vector>

# include "Client.hpp"

class ClientList {
private:
	vector<Client*>	_clients;

public:
	ClientList();
	~ClientList();

	void			addClient(Client *client);
	void			removeClient(Client *client);
	void			deleteClient(Client *client);

	Client			*getClient(int fd) const;
	Client			*getClient(string const &nickname) const;
	vector<Client*>	&getClients();
};
