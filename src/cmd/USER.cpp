#include "server.hpp"

void	Server::user(Client *client, std::vector<std::string> args)
{
	if (args.size() < 4 || args[0].empty() || args[1].empty() || \
			args[2].empty() || args[3].empty())
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "USER"));
	else if (client->getAuthorized() == false)
		std::cout << "Client is not authorized" << std::endl; 
	else if (client->getRegistered() == true)
		client->setSendBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
	else
	{
		client->setUsername(args[0]);
		client->setRealname(args[3]);
		if (!client->getNickname().empty())
		{
			client->setRegistered(true);
			welcomeClient(client);
		}
		std::cout << "Real and User set" << std::endl;
	}
}
