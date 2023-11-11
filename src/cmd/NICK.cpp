#include "server.hpp"

// Checks wether the nickname contains only allowed chars

bool	validNick(std::string nick)
{
	if (nick.find_first_not_of(VALID_CHARS) != std::string::npos)
		return (false);
	else
		return (true);
}

/* List checks:
	1. No parameters given
	2. Forbidden chars in nickname
	3. Nickname already in use
	4. User is registered
If everything is clear, sets the nickname to arg[0]*/

void	Server::nick(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
		std::cout << ERR_NONICKNAMEGIVEN(client->getNickname()) << std::endl;
	else if (!validNick(args[0]))
		std::cout << ERR_ERRONEUSNICKNAME(client->getNickname(), args[0]) << std::endl;
	else if (this->getClient(args[0]))
		std::cout << ERR_NICKNAMEINUSE(client->getNickname(), args[0]) << std::endl;
	else if (client->getAuthorized() == false)
		std::cout << "Client not authorized" << std::endl;
	else
	{
		client->setNickname(args[0]);
		if (!client->getRealname().emppty())
			client->setRegistered(true);
	}
}
