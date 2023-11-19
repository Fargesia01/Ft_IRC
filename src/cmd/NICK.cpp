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
	else if (!validName(args[0]) || args[0][0] == '#')
		client->setSendBuffer(ERR_ERRONEUSNICKNAME(client->getNickname(), args[0]));
	else if (this->getClient(args[0]))
		client->setSendBuffer(ERR_NICKNAMEINUSE(client->getNickname(), args[0]));
	else if (client->getAuthorized() == false)
		std::cout << "Client not authorized" << std::endl;
	else
	{
		if (!client->getRealname().empty() && client->getNickname().empty())
		{
			client->setNickname(args[0]);
			client->setRegistered(true);
			welcomeClient(client);
			return ;
		}
		client->setSendBuffer(user_id(client->getNickname(), client->getUsername()) + " NICK :" + args[0] + "\r\n");
		client->setNickname(args[0]);
		std::cout << "Nick registered" << std::endl;
	}
}
