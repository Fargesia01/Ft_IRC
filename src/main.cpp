#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "../includes/parser.hpp"

#define BACKLOG 10

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return (0);
	}
	
	struct addrinfo		hints, *res;
	int			sockfd, new_fd;
	socklen_t		addr_size;
	struct sockaddr_storage	their_addr;

	// Fill in setup parameters for getaddrinfo()
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// Prepares the struct for the socket
	getaddrinfo(NULL, "6667", &hints, &res);

	// Creates the socket
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// Binds the socket with the struct
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	// Prompts the socket to listen for incoming connections
	listen(sockfd, BACKLOG);

	// Creates new socket for the new connection
	addr_size = sizeof(their_addr);
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

	// Loop to print every new message on the new socket
	while (1)
	{
		char buffer[1024];
		ssize_t bytes_received = recv(new_fd, buffer, sizeof(buffer), 0);

		if (bytes_received > 1)
		{
			std::cout << buffer << std::endl;
		}
		else
			break ;
	}

	// Closes all sockets
	close(sockfd);
	close(new_fd);
}
