// #include "commands/JOIN.hpp"

// JOIN::JOIN() : ACommand() {}

// JOIN::~JOIN() {}

// void	JOIN::execute(Server &server, Client *client, vector<string> &args) const {
// 	// print the args
// 	cout << YELLOW "args[0]: " << RESET << args[0] << endl;
	
// 	if (args[0].empty() || args.size() > 2) {
// 		Server::sendMessage(client->getFd(), IRCErrors::ERR_NEEDMOREPARAMS(args[0]));
// 		return ;
// 	}
// 	// find if within args[1] there is more than one channel.
// 	// args[0] = /JOIN | args[1] = #channel1,#channel2,#channel3 | args[2] = key | args[2] = key,key2,key3

// 	istringstream	ss(args[0]);
// 	string			channelToken; // tokenize the channels

// 	while (getline(ss, channelToken, ',')) {
// 		cout << GREEN "channelToken: " << RESET << channelToken << endl;
// 		if (channelToken.at(0) != '#') {
// 			Server::sendMessage(client->getFd(), IRCErrors::ERR_BADCHANMASK());
// 			return ;
// 		}
// 		// Channel	*channel = server.getChannelByName(channelToken);
// 		if (channel == NULL) {
// 			Channel	*newChannel = new(nothrow) Channel(channelToken);
// 			if (newChannel == NULL)
// 				return ;
// 			newChannel->setCreator(client->getNickname());
// 			newChannel->addOperator(client);
// 			newChannel->addClient(client);
// 			// server.addChannel(channelToken, newChannel);
// 		}
// 		else {
// 			if (channel->getLimit() != 0 && channel->getUsers().size() >= channel->getLimit()) {
// 				// Server::sendMessage(client->getFd(), IRCErrors::ERR_CHANNELISFULL(channelToken));
// 				return ;
// 			}
// 			channel->addClient(client);
// 		}
// 	}

// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_NAMREPLY(client->getNickname(), args[1], ""));
// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_ENDOFNAMES(client->getNickname(), args[1]));
// 	// Server::sendMessage(client->getFd(), IRCReplies::RPL_CHANNELMODEIS(args[1], ""));

// }
