#include "server.hpp"

void	Server::part(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
		return ;
	}
	else if (channels.find(args[0]) == channels.end())
	{
		client->setSendBuffer(ERR_NOSUCHCHANNEL(client->getNickname(), args[0]));
		return ;
	}
	Channel *channel = channels.find(args[0])->second;
	if (!channel->isMember(client))
	{
		client->setSendBuffer(ERR_NOTONCHANNEL(client->getNickname(), args[0]));
		return ;
	}
	if (args.size() > 1)
		channel->sendToAll(client->getNickname() + " PART " + args[0] + " :" + args[1] + "\r\n");
	else
		channel->sendToAll(client->getNickname() + " PART " + args[0] + " :Leaving\r\n");
	channel->rmClient(client);
	channel->rmOps(client);
	if (channel->getClients().size() == 0)
		channels.erase(channels.find(channel->getName()));
}

void	Server::partAll(Client *client)
{
	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end();)
	{
		if (it->second->isMember(client))
		{
			it->second->rmClient(client);
			if (it->second->getClients().size() == 0)
			{
				delete it->second;
				channels.erase(it++);
			}
			else
			{
				it->second->sendToAll(client->getNickname() + " PART " + it->first + " :Leaving");
				++it;
			}
		}
		else
			++it;
	}
}
