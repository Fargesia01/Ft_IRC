#include "server.hpp"

/* List checks:
 	1. No Password given
	2. Client is already registered
	3. Wrong password
	4. User not registered
If everything is clear, registers the client
*/

void	Server::pass(Client *client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
		client->setSendBuffer(ERR_NEEDMOREPARAMS(client->getNickname(), "PASS")); 
	else if (client->getAuthorized() == true)
		client->setSendBuffer(ERR_ALREADYREGISTERED(client->getNickname()));
	else if (args[0] != this->password)
		client->setSendBuffer(ERR_PASSWDMISMATCH(client->getNickname()));
	else
	{
		client->setAuthorized(true);
		std::cout << "Client authorized" << std::endl;
	}
}
