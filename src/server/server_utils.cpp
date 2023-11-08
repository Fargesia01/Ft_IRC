#include "server.hpp"

int	acceptSocket(int socket)
{
	sockaddr_in client;
	socklen_t addr_size = sizeof(sockaddr_in);
	return (accept(socket, (sockaddr *)&client, &addr_size));
}
