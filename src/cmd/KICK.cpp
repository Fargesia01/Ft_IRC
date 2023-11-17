#include "server.hpp"

void	Server::kick(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() < 2 || args[0].empty() || args[1].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"));
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
	else if (!channel->isOps(client))
	{
		client->setSendBuffer(ERR_CHANOPRIVSNEEDED(client->getNickname(), args[0]));
		return ;
	}
	else if (!channel->isMember(args[1]))
	{
		client->setSendBuffer(ERR_USERNOTINCHANNEL(client->getNickname(), args[0], args[1]));
		return ;
	}
	channel->sendToAll(user_id(client->getNickname(), client->getUsername()) + " KICK " + args[1] + " of " + args[0] + "\r\n");
	channel->rmClient(getClient(args[1]));
	channel->rmOps(getClient(args[1]));
}
