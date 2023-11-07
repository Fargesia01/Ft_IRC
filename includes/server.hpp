#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <csignal>
#include <map>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <vector>
#include <poll.h>
#include "client.hpp"

#define SUCCESS 0
#define BACKLOG 10

class Server;

extern bool	server_shutdown;

typedef void (Server::*cmdPtr)(Client *client, std::vector<std::string> args);

class Server
{
	public :

		// Constructors and destructor

		Server(std::string port, std::string password, struct tm *timeinfo);
		~Server();

		// Initialisation

		void		createMap();
		int		fillServinfo();
		int		launchServer();

		// Server management

		int		serverLoop();

		// Getters and Setters
		
		void		getPassword() const;
		void		setDatetime(struct tm *timeinfo);

	private :

		struct addrinfo			*servinfo;
		int				server_socket;
		std::vector<pollfd>		polls;
		std::string			port;
		std::string			password;
		std::string			datetime;
		std::map<std::string, cmdPtr>	cmd_map;
};

#endif
