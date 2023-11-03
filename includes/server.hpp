#ifndef IRC_HPP
#define IRC_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <poll.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <cerrno>
#include <ctime>
#include <fstream>
#include <csignal>
#include <stdlib.h>
#include <stdio.h>
#include "client.hpp"
#include "numeric.hpp"

# define BACKLOG 10    
# define SUCCESS 0
# define BUF_SIZE_MSG 4096
# define BREAK 2
# define CONTINUE 3

extern bool	server_shutdown;

class Server
{
private:
    	struct addrinfo			hints;
	struct addrinfo			*servinfo; // will point to the results
    	struct sockaddr_storage         clientinfo;
    	socklen_t                       addr_size;
	int				server_socket_fd;
	std::map<const int, Client>	clients;
   	int                             client_fd;
	std::string			port;
	std::string			password;
	std::string			datetime;
public:
	Server(std::string port, std::string password, struct tm *timeinfo);
    	Server();
	void							setDatetime(struct tm *timeinfo);
	std::string 						getDatetime() const;
	void							setHints();
	int								fillServinfo(char *port);
	int								launchServer();
	int								serverLoop();
	std::map<const int, Client>&					getClients();
	int								handlePollout(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd);
	void 								addClient(int client_socket, std::vector<pollfd> &poll_fds);
	int								createClient(std::vector<pollfd>& poll_fds, std::vector<pollfd>& new_pollfds);
	int 								manageClient(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it);
	void 								checkReg(int const client_fd, std::string message);
	void								deleteClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator &it, int current_fd);
    ~Server();
};


#endif
