#include "server.hpp"

void    Server::notice(Client *client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty())
    {
        client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "NOTICE"));
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
        channel->clientToAll(RPL_NOTICE(client->getNickname(), client->getUsername(), channel->getName(), message), client->getSocket());
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
        receiver->setSendBuffer(RPL_NOTICE(client->getNickname(), client->getUsername(), receiver->getNickname(), message));
    }

}
