#include "server.hpp"

void	Server::join(Client *client, std::vector<std::string> args)
{
	if (client->getRegistered() == false)
	{
		client->setSendBuffer(ERR_NOTREGISTERED(client->getNickname()));
		return ;
	}
	else if (args.empty() || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
		return ;
	}
	// else if(!validName(args[0]))
	// {
	// 	client->setSendBuffer(ERR_BADCHANMASK(args[0]));
	// 	return ;
	// }
	if (channels.find(args[0]) == channels.end())
	{
		Channel *channel = new Channel(args[0]);

		channel->addOps(client);
		channels.insert(std::make_pair(args[0], channel));
	}
	Channel *channel = channels.find(args[0])->second;
	channel->addClient(client);
	channel->sendToAll(RPL_JOIN(user_id(client->getNickname(), client->getUsername()), channel->getName()));
	topic(client, args);
	names(client, args);
}
