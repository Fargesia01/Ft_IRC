#include "server.hpp"

void	Server::invite(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() < 2 || args[0].empty() || args[1].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "INVITE"));
		return ;
	}
	if (channels.find(args[1]) == channels.end())
	{
		client->setSendBuffer(ERR_NOSUCHCHANNEL(client->getNickname(), args[0]));
		return ;
	}
	Channel *channel = channels.find(args[1])->second;
	if (!channel->isMember(client))
	{
		client->setSendBuffer(ERR_NOTONCHANNEL(client->getNickname(), args[1]));
		return ;
	}
	if (channel->isMember(args[0]))
	{
		client->setSendBuffer(ERR_USERONCHANNEL(client->getNickname(), args[1], args[0]));
		return ;
	}
	if (getClient(args[0]) == NULL)
	{
		client->setSendBuffer(ERR_NOSUCHNICK(client->getNickname(), args[0]));
		return ;
	}
	if (channel->getMode('i') == true && !channel->isOps(client))
	{
		client->setSendBuffer(ERR_CHANOPRIVSNEEDED(client->getNickname(), args[1]));
		return ;
	}
	channel->addInvited(getClient(args[0]));
	client->setSendBuffer(RPL_INVITING(client->getNickname(), args[1], args[0]));
	getClient(args[0])->setSendBuffer(user_id(client->getNickname(), client->getUsername()) + " INVITE " + args[0] + " " + args[1] + "\r\n");
}
