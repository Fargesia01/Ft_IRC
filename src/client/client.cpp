#include "client.hpp"

// Constructor and Destructor

Client::Client(int socket): socket(socket) 
{
}

Client::~Client() {};

// Getters and Setters

int		Client::getSocket() const { return (socket); }
std::string	Client::getReadBuffer() const { return (readBuffer); }
std::string	Client::getSendBuffer() const { return (sendBuffer); }

void		Client::setReadBuffer(std::string buf) { readBuffer = buf; }
void		Client::setSendBuffer(std::string buf) { sendBuffer = buf; }
