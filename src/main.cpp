#include "../includes/server.hpp"

bool server_shutdown = false;

static void	signal_handler(int signal)
{
	(void)signal;
	server_shutdown = true;
}


Server::Server(std::string port, std::string password, struct tm *timeinfo)
: servinfo(NULL), server_socket_fd(0) , port(port), password(password)
{
	memset(&hints, 0, sizeof(hints)); // verifier si la struct est vide
	this->setDatetime(timeinfo);
}

Server::~Server() {};

void							Server::setDatetime(struct tm *timeinfo)
{
	char buffer[80];

	strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  	std::string str(buffer);

	datetime = str;
}

void Server::setHints()
{
	hints.ai_family = AF_INET;		  // Ipv4
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;	  // mon ip
}

int Server::fillServinfo(char *port)
{
	if (getaddrinfo(NULL, port, &hints, &servinfo) < 0)
	{
		std::cerr << "[ERROR] addrinfo problem" << std::endl;
		return (-1);
	}
	return (0);
}

int Server::launchServer()
{
	server_socket_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (server_socket_fd == -1)
	{
		std::cerr << "[ERROR] socket problem" << std::endl;
		return (-1);
	}
	int yes = 1;
	if (setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		std::cerr << "[ERROR] Address already in use" << std::endl;
		return (-1);
	}
	if (bind(server_socket_fd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		std::cerr << "[ERROR] bind failed" << std::endl;
		return (1);
	}
	if (listen(server_socket_fd, BACKLOG) == -1)
	{
		std::cerr << "[ERROR] listen failed" << std::endl;
		return (-1);
	}
	freeaddrinfo(servinfo);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		time_t rawtime;
		struct tm * timeinfo;

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		signal(SIGINT, signal_handler);

        Server  server(argv[1], argv[2], timeinfo);
        server.setHints();
		if (server.fillServinfo(argv[1]) == -1)
			return (-1);
		server.launchServer(); //mise en place du serveur
        std::cout << "server on" << std::endl;
		try
		{
			server.serverLoop(); //lancement de la boucle pour le serveur
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n' << std::endl;
		}
		return (SUCCESS);
	}
    else
	{
        std::cout << "need 2 arguments: \"./ircserv port password\"" << std::endl;
		return (-1);
	}
}