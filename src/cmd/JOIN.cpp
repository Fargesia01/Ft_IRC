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
	else if(!validName(args[0]))
	{
		client->setSendBuffer(ERR_BADCHANMASK(args[0]));
		return ;
	}
	if (args[0][0] == '0')
	{
		partAll(client);
		return ;
	}
	if (channels.find(args[0]) == channels.end())
	{
		Channel *channel = new Channel(args[0]);

		channel->addOps(client);
		channels.insert(std::make_pair(args[0], channel));
	}
	Channel *channel = channels.find(args[0])->second;
	if (channel->isMember(client))
	{
		client->setSendBuffer(client->getNickname() + " already in channel " + channel->getName() + "\r\n");
		return ;
	}
	if (channel->getMode('i') && !channel->isInvited(client))
	{
		client->setSendBuffer(ERR_INVITEONLYCHAN(client->getNickname(), args[0]));
		return ;
	}
	if (channel->getMode('k') && ((int)args.size() < 2 || channel->getPassword() != args[1]))
	{
		client->setSendBuffer(ERR_BADCHANNELKEY(client->getNickname(), args[0]));
		return ;
	}
	if (channel->getMode('l') && (int)channel->getClients().size() == channel->getUserLimit())
	{
		client->setSendBuffer(ERR_CHANNELISFULL(client->getNickname(), args[0]));
		return ;
	}
	channel->addClient(client);
	channel->rmInvited(client);
	channel->sendToAll(client->getNickname() + " JOIN " + args[0] + "\r\n");
	topic(client, args);
	names(client, args);
}
