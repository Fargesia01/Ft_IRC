#include "server.hpp"

// Constructor and Destructor

Server::Server(std::string port, std::string password, struct tm *timeinfo)
: servinfo(NULL), server_socket(0) , port(port), password(password)
{
	this->setDatetime(timeinfo);
	createMap();
}

Server::~Server() {};

// Management

int	Server::serverLoop()
{
	while (server_shutdown == false)
	{
		int status = poll(polls.data(), polls.size(), -1);
		if (status == -1)
		{
			std::cout << "Error in poll() call" << std::endl;
			return (-1);
		}
		for (int i = 0; i < (int)polls.size(); i++)
		{
			if (polls[i].revents & POLLIN)
			{
				if (i == 0)
					newClient();
				else
					handlePollin(clients[polls[i].fd]);
			}
			else if (polls[i].revents & POLLOUT)
				handlePollout(clients[polls[i].fd]);
		}
		for (int i = 0; i < (int)polls.size(); i++)
		{
			// Parsing and executing the readBuffer for each client
		}
	}
	return (SUCCESS);
}

void	Server::handlePollin(Client *client)
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

void	Server::handlePollout(Client *client)
{
	sendToClient(client);
}

// Getters

std::string	Server::getPassword() const { return (password); }

Client* Server::getClient(std::string nickname)
{
	if (clients.empty())
		return (NULL);
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (clients[i]->getNickname() == nickname)
			return (clients[i]);
	}
	return (NULL);
}

// Setters

void	Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	datetime = str;
}
