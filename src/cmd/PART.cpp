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
	std::string reason;
	reason.erase();
	channel->sendToAll(RPL_PART(user_id(client->getNickname(), client->getUsername()), channel->getName(), reason));
	channel->rmClient(client);
	channel->rmOps(client);
	if (channel->getClients().size() == 0)
	{
		std::cout << "Erasing channel" << std::endl;
		delete(channel);
		channels.erase(channels.find(channel->getName()));
	}
}

void	Server::partAll(Client *client)
{
	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end();)
	{
		if (it->second->isMember(client))
		{
			it->second->sendToAll(user_id(client->getNickname(), client->getUsername()) + " PART " + it->first + " :Leaving\r\n");
			it->second->rmClient(client);
			if (it->second->getClients().size() == 0)
			{
				std::cout << "Erasing channel" << std::endl;
				delete it->second;
				channels.erase(it++);
			}
			else
			{
				//it->second->sendToAll(user_id(client->getNickname(), client->getUsername()) + " PART " + it->first + " :Leaving\r\n");
				++it;
			}
		}
		else
			++it;
	}
}
