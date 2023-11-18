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
	changeModes(client, channel, args);
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
	if (channel->getMode('l'))
		modes += "User limit ";
	client->setSendBuffer(RPL_CHANNELMODEIS(client->getNickname(), channel->getName(), modes));
	
}

void	Server::changeModes(Client *client, Channel *channel, std::vector<std::string> args)
{
	bool	add = true;
	std::string	mode = "+";
	int	count = 2;

	for (int i = 0; i < (int)args[1].size(); i++)
	{
		switch (args[1][i])
		{
			case '+':
				add = true;
				mode = '+';
				break;
			case '-':
				add = false;
				mode = '-';
				break;
			case 'i':
				channel->setMode('i', add);
				channel->sendToAll(MODEMSG(user_id(client->getNickname(), client->getUsername()), channel->getName(), mode + "i"));
				break;
			case 't':
				channel->setMode('t', add);
				channel->sendToAll(MODEMSG(user_id(client->getNickname(), client->getUsername()), channel->getName(), mode + "t"));
				break;
			case 'k':
				if (add == true && ((int)args.size() < (count + 1) || args[count].empty()))
				{
					client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
					return ;
				}
				channel->setMode('k', add);
				if (add == true)
					channel->setPassword(args[count++]);
				channel->sendToAll(MODEMSG2(user_id(client->getNickname(), client->getUsername()), channel->getName(), mode + "k", args[2]));
				break;
			case 'o':
				if ((int)args.size() < (count + 1) || args[count].empty())
				{
					client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
					return ;
				}
				else if (!channel->isMember(client))
				{
					client->setSendBuffer(ERR_USERNOTINCHANNEL(client->getNickname(), channel->getName(), args[count]));
					return ;
				}
				if (add == true)
					channel->addOps(getClient(args[count++]));
				else
					channel->rmOps(getClient(args[count++]));
				channel->sendToAll(MODEMSG2(user_id(client->getNickname(), client->getUsername()), channel->getName(), mode + "o", args[2]));
				break;
			case 'l':
				if (add == true && ((int)args.size() < (count + 1) || args[count].empty()))
				{
					client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
					return ;
				}
				if (add == true)
				{
					int new_limit = atoi(args[count++].c_str());
					if (new_limit <= 0)
					{
						client->setSendBuffer("Invalid limit mode parameter.\r\n");
						return ;
					}
					channel->setUserLimit(new_limit);
				}
				channel->setMode('l', add);
				channel->sendToAll(MODEMSG2(user_id(client->getNickname(), client->getUsername()), channel->getName(), mode + "l", args[2]));
				break;
			default:
				break;
		}
	}
}
