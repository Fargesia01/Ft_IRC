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

void	Server::manageClient(Client *client)
{
	char	message[BUF_SIZE_MSG];
	int	readCount;

	memset(message, 0, sizeof(message));
	readCount = recv(client->getSocket(), message, BUF_SIZE_MSG, 0);
	if (readCount <= -1)
	{
		std::cerr << "[SERVER]: recv() FAILED" << std::endl;
		deleteClient(client);
		return ;
	}
	else if (readCount == 0)
	{
		std::cout << "[SERVER]: A CLIENT JUST DISCONNECTED\n";
		deleteClient(client);
		return ;
	}
	else
	{
	   std::cout << "[CLIENT]: MESSAGE RECEIVED FROM CLIENT : " << client->getSocket() << std::endl << message << std::endl;
	   client->setReadBuffer(message);
	}
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
