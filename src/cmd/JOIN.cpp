#include "server.hpp"

void	Server::join(Client *client, std::vector<std::string> args)
{
	if (client->getRegistered() == false)
		client->setSendBuffer(ERR_NOTREGISTERED(client->getNickname()));
	else if (args.empty() || args[0].empty())
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
	else if(!validName(args[0]))
		client->setSendBuffer(ERR_BADCHANMASK(args[0]));
	if (channels.find(args[0]) == channels.end())
	{
		Channel *channel = new Channel(args[0]);

		channel->addOps(client);
		channel->addClient(client);
		channels.insert(std::make_pair(args[0], channel));
		client->setSendBuffer(client->getNickname() + " JOIN " + args[0] + "\r\n");
		//topic(client, args)
		//names(client, args)
	}
}
