#include "server.hpp"

int	Server::newClient()
{
	int	clientSocket = acceptSocket(server_socket);
	if (clientSocket == -1)
	{
		std::cout << "Error accepting the socket" << std::endl;
		return (-1);
	}
	Client *client = new Client(clientSocket);
	pollfd	client_poll;
	client_poll.fd = clientSocket;
	client_poll.events = POLLIN | POLLOUT;
	polls.push_back(client_poll);
	clients.insert(std::pair<int, Client*>(clientSocket, client));
	std::cout << "[SERVER]: Client " << clientSocket << " added." << std::endl;
	std::cout << "[SERVER]: Total number of clients now is: " << clients.size() << std::endl;
	return (0);
}

void	Server::deleteClient(Client *client)
{
	int	tmp = client->getSocket();

	close(tmp);
	clients.erase(tmp);
	for (int i = 0; i < (int)polls.size(); i++)
	{
		if (polls[i].fd == tmp)
			polls.erase(polls.begin() + i);
	}
	std::cout << "[SERVER]: CLIENT #" << tmp << " DISCONNECTED" << std::endl;
	std::cout << "[SERVER]: CLIENT DELETED. TOTAL CLIENT IS NOW: " << clients.size() << std::endl;
}

void	Server::welcomeClient(Client *client) const
{
	client->setSendBuffer(RPL_WELCOME(client->getNickname()));
	client->setSendBuffer(RPL_YOURHOST(client->getNickname()));
	client->setSendBuffer(RPL_CREATED(client->getNickname(), datetime));
	client->setSendBuffer(RPL_MYINFO(client->getNickname(), "users: operator_user, basic_user", "channel modes: invite only, password required"));
	client->setSendBuffer(RPL_LUSERCLIENT(client->getNickname(), intToString((int)clients.size())));
	client->setSendBuffer(RPL_LUSEROP(client->getNickname(), "0"));
	client->setSendBuffer(RPL_LUSERCHANNELS(client->getNickname(), "0"));
	client->setSendBuffer(RPL_LUSERME(client->getNickname(), intToString((int)clients.size())));
}
