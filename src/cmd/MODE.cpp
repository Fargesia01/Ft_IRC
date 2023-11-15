#include "server.hpp"

void	Server::mode(Client *client, std::vector<std::string> args)
{
	if ((int)args.size() < 1 || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
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
	if ((int)args.size() == 1)
	{
		sendModes(client, channel);
		return ;
	}
	else if (!channel->isOps(client))
	{
		client->setSendBuffer(ERR_CHANOPRIVSNEEDED(client->getNickname(), args[0]));
		return ;
	}
	changeModes(client, channel, args[1]);
}

void	Server::sendModes(Client *client, Channel *channel)
{
	std::string modes = "";
	if (channel->getMode('i'))
		modes += "Invite Only ";
	if (channel->getMode('t'))
		modes += "Topic protected ";
	if (channel->getMode('k'))
		modes += "Password required ";
	client->setSendBuffer(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), modes));
	
}

void	Server::changeModes(Client *client, Channel *channel, std::string arg)
{
	bool	add = true;

	for (int i = 0; i < (int)arg.size(); i++)
	{
		switch (arg[i])
		{
			case '+':
				add = true;
				break;
			case'-':
				add = false;
				break;
			case 'i':
				channel->setMode('i', add);
				break;
			case 't':
				channel->setMode('t', add);
				break;
			case 'k':
				channel->setMode('k', add);
				break;
			case 'o':
				break;
			case 'l':
				break;
			default:
				break;
		}
	}
}
