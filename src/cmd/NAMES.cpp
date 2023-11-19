#include "server.hpp"

void	Server::names(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "NAMES"));
		return ;
	}
	else if (channels.find(args[0]) == channels.end())
	{
		client->setSendBuffer(RPL_ENDOFNAMES(client->getNickname(), args[0]));
		return ;
	}
	else
	{
		Channel *channel = channels.find(args[0])->second;
		std::vector<Client *>	list = channel->getClients();
		for (int i = 0; i < (int)list.size(); i++)
		{
			if (channel->isOps(list[i]))
				client->setSendBuffer(RPL_NAMREPLY(client->getNickname(), args[0], ("@" + list[i]->getNickname())));
			else
				client->setSendBuffer(RPL_NAMREPLY(client->getNickname(), args[0], list[i]->getNickname()));
		}
		client->setSendBuffer(RPL_ENDOFNAMES(client->getNickname(), args[0]));
	}
}
