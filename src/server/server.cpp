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
		// Need to parse the polls
		std::cout << "lol" << std::endl;
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
