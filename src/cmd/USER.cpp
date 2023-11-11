#include "server.hpp"

void	Server::user(Client *client, std::vector<std::string> args)
{
	if (args.size() < 4 || args[0].empty() || args[1].empty() || \
			args[2].empty() || args[3].empty())
		std::cout << ERR_NEEDMOREPARAMS(client->getNickname(), "USER") << std::endl;
	else if (client->getAuthorized() == false)
		std::cout << "Client is not authorized" << std::endl; 
	else if (client->getRegistered() == true)
		std::cout << ERR_ALREADYREGISTERED(client->getNickname()) << std::endl;
	else
	{
		client->setUsername(args[0]);
		client->setRealname(args[3]);
		if (!client->getNickname().empty())
			client->setRegistered(true);
	}
}
