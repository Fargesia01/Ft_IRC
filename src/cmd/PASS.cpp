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
		std::cout << ERR_NEEDMOREPARAMS(client->getNickname(), "PASS") << std::endl; 
	else if (client->getAuthorized() == true)
		std::cout << ERR_ALREADYREGISTERED(client->getNickname()) << std::endl;
	else if (args[0] != this->password)
		std::cout << ERR_PASSWDMISMATCH(client->getNickname()) << std::endl;
	else
	{
		client->setAuthorized(true);
		std::cout << "Client authorized" << std::endl;
	}
}
