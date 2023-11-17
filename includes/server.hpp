#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstdlib>
#include <map>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <vector>
#include <poll.h>
#include <cerrno>
#include <sstream>
#include "client.hpp"
#include "defines.h"
#include "utils.hpp"
#include "channel.hpp"

#define SUCCESS 0
#define BACKLOG 10
#define BUF_SIZE_MSG 4096

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

		// Client Management

		int		newClient();
		void		deleteClient(Client *client);
		void		welcomeClient(Client *client) const;

		// Server management

		int		serverLoop();
		void		handlePollin(Client *client);
		void		handlePollout(Client *client);
		void		execute(Client *client);
		
		// Utils
		
		void	deleteAll();

		// Commands

		void		nick(Client *client, std::vector<std::string> args);
		void		pass(Client *client, std::vector<std::string> args);
		void		user(Client *client, std::vector<std::string> args);
		void		ping(Client *client, std::vector<std::string> args);
		void		join(Client *client, std::vector<std::string> args);
		void		topic(Client *client, std::vector<std::string> args);
		void		names(Client *client, std::vector<std::string> args);
		void		part(Client *client, std::vector<std::string> args);
		void		privmsg(Client *client, std::vector<std::string> args);
		void		notice(Client *client, std::vector<std::string> args);
		void		partAll(Client *client);
		void		kick(Client *client, std::vector<std::string> args);
		void		invite(Client *client, std::vector<std::string> args);
		void		mode(Client *client, std::vector<std::string> args);
		void		sendModes(Client *client, Channel *channel);
		void		changeModes(Client *client, Channel *channel, std::vector<std::string> args);

		// Getters and Setters
		
		std::string	getPassword() const;
		void		setDatetime(struct tm *timeinfo);
		Client*		getClient(std::string nickname);
		Channel*	getChannel(std::string name);

	private :

		struct addrinfo				*servinfo;
		int					server_socket;
		std::vector<pollfd>			polls;
		std::string				port;
		std::string				password;
		std::string				datetime;
		std::map<std::string, cmdPtr>		cmd_map;
		std::map<int, Client*>			clients;
		std::map<std::string, Channel *>	channels;
};

// Server Utils

int		acceptSocket(int socket);
void		sendToClient(Client *client);

#endif
