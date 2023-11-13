#include "server.hpp"

/* List checks:
	1. No parameters given
	2. Forbidden chars in nickname
	3. Nickname already in use
	4. User is registered
If everything is clear, sets the nickname to arg[0]*/

void	Server::nick(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
		client->setSendBuffer(ERR_NONICKNAMEGIVEN(client->getNickname()));
	else if (!validName(args[0]))
		client->setSendBuffer(ERR_ERRONEUSNICKNAME(client->getNickname(), args[0]));
	else if (this->getClient(args[0]))
		client->setSendBuffer(ERR_NICKNAMEINUSE(client->getNickname(), args[0]));
	else if (client->getAuthorized() == false)
		std::cout << "Client not authorized" << std::endl;
	else
	{
		client->setNickname(args[0]);
		if (!client->getRealname().empty())
		{
			client->setRegistered(true);
			welcomeClient(client);
		}
		std::cout << "Nick registered" << std::endl;
	}
}
