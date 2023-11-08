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
				{
					manageClient(clients[i]);
					// Handle client 
				}
			}
			else if (polls[i].revents & POLLOUT)
			{
				//std::cout << "Handle Pollout" << std::endl;
			}
		}
	}
	return (SUCCESS);
}

// Setters

void	Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	datetime = str;
}
