#include "server.hpp"

void	Server::ping(Client *client, std::vector<std::string> args)
{
	if (args.size() != 1)
		std::cout << ERR_NEEDMOREPARAMS(client->getNickname(), "PING") << std::endl;
	else
		std::cout << "Execute ping command" << std::endl;
}
