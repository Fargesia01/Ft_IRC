#include "server.hpp"

void	Server::topic(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "TOPIC"));
		return ;
	}
	if (args[0][0] == ':')
		args[0] = args[0].substr(1);
	if (channels.find(args[0]) == channels.end())
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
	if (args.size() == 1)
	{
		if (channel->getTopic().empty())
			client->setSendBuffer(RPL_NOTOPIC(client->getNickname(), args[0]));
		else
			client->setSendBuffer(RPL_TOPIC(client->getNickname(), args[0], channel->getTopic()));
	}
	else
	{
		if (channel->getMode('t') && !channel->isOps(client))
			client->setSendBuffer(ERR_CHANOPRIVSNEEDED(client->getNickname(), args[0]));
		else
		{
			channel->setTopic(args[1]);
			channel->sendToAll(RPL_TOPIC(client->getNickname(), args[0], args[1]));
		}
	}
}
