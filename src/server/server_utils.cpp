#include "server.hpp"

void	Server::deleteAll()
{
	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		delete(it->second);
	}
	clients.clear();
	for (std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		delete(it->second);
	}
	channels.clear();
}

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
