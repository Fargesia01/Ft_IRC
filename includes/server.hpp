#ifndef SERVER_HPP
# define SERVER_HPP

#include "client.hpp"
#include <map>
#include <vector>
#include <iostream>

class Server
{
	public :

		Server();
		~Server();

		// All Commands implemented
		void	nick(int client, std::vector<std::string> args);
		//void	user();
		//void	pass();
		//etc...

	private :

		std::map<int, Client*>	clients;
};

#endif
