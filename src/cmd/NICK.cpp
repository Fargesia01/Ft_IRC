#include "../../includes/client.hpp"
#include "../../includes/server.hpp"

void	Server::nick(int client, std::vector<std::string> args)
{
	if (args.empty() || args[0].empty())
	{
		std::cout << "Not enough arguments" << std::endl;
		return ;
	}
	std::cout << "Good to go" << std::endl;
	return ;
}
