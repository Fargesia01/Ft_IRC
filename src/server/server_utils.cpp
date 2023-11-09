#include "server.hpp"

int	acceptSocket(int socket)
{
	sockaddr_in client;
	socklen_t addr_size = sizeof(sockaddr_in);
	return (accept(socket, (sockaddr *)&client, &addr_size));
}

void	sendToClient(Client *client)
{
	std::istringstream	buf(client->getSendBuffer());
	std::string		reply;
	
	send(client->getSocket(), client->getSendBuffer().c_str(), client->getSendBuffer().size(), 0);
	while (getline(buf, reply))
	{
		std::cout << "[SERVER]: MESSAGE SENT TO CLIENT " << client->getSocket() << "# => " << reply << std::endl;
	}
}
