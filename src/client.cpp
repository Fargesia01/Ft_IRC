#include "../includes/server.hpp"

std::string&	Client::getSendBuffer()  	{ return (sendbuf); }
std::string&	Client::getReadBuffer()  	{ return (readbuf); }
std::string&	Client::getNickname()  		{ return (nickname); }
std::string 	Client::getUsername() const { return (username); }
bool&			Client::getConnexionPassword()	{ return (connexion_password); }
bool&			Client::isRegistrationDone() 	{ return (registrationDone); }
bool&			Client::reg()			{ return (welcomeSent); }

void	Client::setReadBuffer(std::string const &buf)
{
	readbuf += buf;
}

void	Client::setSendBuffer(std::string const &buf)
{
	sendbuf += buf;
}

Client::Client(int client_fd)
:  to_deconnect(false), connexion_password(false),\
 registrationDone(false), welcomeSent(false)
{}

Client::~Client() {}