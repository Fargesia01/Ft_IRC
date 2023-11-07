#include "server.hpp"

bool server_shutdown = false;

static void	signal_handler(int signal)
{
	(void)signal;
	server_shutdown = true;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "need 2 arguments: \"./ircserv port password\"" << std::endl;
		return (-1);
	}
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	signal(SIGINT, signal_handler);

	Server  server(argv[1], argv[2], timeinfo);
	if (server.launchServer() == -1) //mise en place du serveur
		return (-1);

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
