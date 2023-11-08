#include "client.hpp"

Client::Client(int socket): socket(socket) 
{
}

Client::~Client() {};

int	Client::getSocket() const { return (socket); }
