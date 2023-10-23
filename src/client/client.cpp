#include "../../includes/client.hpp"

Client::Client()
{
	return ;
}

Client::~Client()
{
	return ;
}

std::string Client::getUsername() const
{
	return(this->username);
}

void Client::setUsername(std::string new_name)
{
	this->username = new_name;
	return ;
}

std::string Client::getNickname() const
{
	return (this->nickname);
}

void Client::setNickname(std::string new_name)
{
	this->nickname = new_name;
	return ;
}
