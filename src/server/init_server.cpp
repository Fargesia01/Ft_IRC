#include "server.hpp"

void	Server::createMap()
{
	this->cmd_map["NICK"] = &Server::nick;
	this->cmd_map["PASS"] = &Server::pass;
	this->cmd_map["USER"] = &Server::user;
	this->cmd_map["PING"] = &Server::ping;
	this->cmd_map["JOIN"] = &Server::join;
	this->cmd_map["TOPIC"] = &Server::topic;
	this->cmd_map["NAMES"] = &Server::names;
	this->cmd_map["PART"] = &Server::part;
	this->cmd_map["PRIVMSG"] = &Server::privmsg;
	this->cmd_map["NOTICE"] = &Server::notice;
	this->cmd_map["MODE"] = &Server::mode;
	this->cmd_map["KICK"] = &Server::kick;
	this->cmd_map["INVITE"] = &Server::invite;
}

int Server::fillServinfo()
{
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints)); // verifier si la struct est vide
	hints.ai_family = AF_INET;		  // Ipv4
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;	  // mon ip
	if (getaddrinfo(NULL, port.c_str(), &hints, &servinfo) < 0)
	{
		std::cerr << "[ERROR] addrinfo problem" << std::endl;
		return (-1);
	}
	return (0);
}

int Server::launchServer()
{
	if (this->fillServinfo() == -1)
		return (-1);
	server_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (server_socket == -1)
	{
		std::cerr << "[ERROR] socket problem" << std::endl;
		return (-1);
	}
	int yes = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		std::cerr << "[ERROR] Address already in use" << std::endl;
		return (-1);
	}
	if (bind(server_socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		std::cerr << "[ERROR] bind failed" << std::endl;
		return (1);
	}
	if (listen(server_socket, BACKLOG) == -1)
	{
		std::cerr << "[ERROR] listen failed" << std::endl;
		return (-1);
	}
	freeaddrinfo(servinfo);
	pollfd	server_poll;
	server_poll.fd = server_socket;
	server_poll.events = POLLIN;
	polls.push_back(server_poll);
	std::cout << "server on" << std::endl;
	return (0);
}
