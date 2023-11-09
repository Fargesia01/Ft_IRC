#include "client.hpp"

// Constructor and Destructor

Client::Client(int socket): socket(socket) 
{
}

Client::~Client() {};

// Utils

void	Client::clearAll()
{
	readBuffer.clear();
	sendBuffer.clear();
	cmd.cmd.clear();
	for (int i = 0; i < (int)cmd.args.size(); i++)
	{
		cmd.args[i].clear();
	}
}

// Getters and Setters

int				Client::getSocket() const { return (socket); }
std::string			Client::getReadBuffer() const { return (readBuffer); }
std::string			Client::getSendBuffer() const { return (sendBuffer); }
std::string 			Client::getUsername() const { return (username); }
std::string			Client::getNickname() const { return (nickname); }
std::string 			Client::getRealname() const { return (realname); }
bool 				Client::getRegistered() const { return (registered); }
bool 				Client::getAuthorized() const { return (authorized); }
std::string			Client::getCmd() const { return (cmd.cmd); }
std::vector<std::string>	Client::getArgs() const { return (cmd.args); }

void				Client::setReadBuffer(std::string buf) { readBuffer = buf; }
void				Client::setSendBuffer(std::string buf) { sendBuffer = buf; }
void				Client::setUsername(std::string new_name) { username = new_name; }
void 				Client::setNickname(std::string new_name) { nickname = new_name; }
void 				Client::setRealname(std::string new_name) { realname = new_name; }
void				Client::setRegistered(bool regi) { registered = regi; }
void 				Client::setAuthorized(bool auth) { authorized = auth; }
