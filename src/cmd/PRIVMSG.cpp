#include "server.hpp"

void    Server::privmsg(Client *client, std::vector<std::string> args)
{
	if (client->getRegistered() == false)
	{
		client->setSendBuffer(ERR_NOTREGISTERED(client->getNickname()));
		return ;
	}
	else if (args.empty() || args[0].empty())
	{
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "PRIVMSG"));
		return ;
	}

    std::string message;
    for (int i = 1; i < (int)args.size(); i++)
    {
        message += args[i];
        if (i != (int)args.size() - 1)
            message += " ";
    }
    if (args[0][0] == '#')
    {
		if (channels.find(args[0]) == channels.end())
        {
            client->setSendBuffer(ERR_NOSUCHCHANNEL(client->getNickname(), args[0]));
            return;
        }
        Channel *channel = getChannel(args[0]);
        channel->clientToAll(RPL_PRIVMSG(client->getNickname(), client->getUsername(), channel->getName(), message), client->getSocket());
        return;
    }
    else
    {
        Client *receiver = getClient(args[0]);
        if (!receiver)
        {
            client->setSendBuffer(ERR_NOSUCHNICK(client->getNickname(), args[0]));
            return;
        }
        receiver->setSendBuffer(RPL_PRIVMSG(client->getNickname(), client->getUsername(), receiver->getNickname(), message));
    }
}
