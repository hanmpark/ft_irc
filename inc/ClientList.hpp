#pragma once

# include "Client.hpp"

class ClientList {
private:
	vector<Client*>	_clients;

public:
	ClientList();
	ClientList(ClientList const &copy);
	ClientList	&operator=(ClientList const &rhs);
	~ClientList();

	void			addClient(Client *client);
	void			removeClient(int fd);

	Client			*getClientByFd(int fd) const;
	Client			*getClientByNickname(string const &nickname) const;
	vector<Client*>	&getClients();

	void			closeFileDescriptors();
};
