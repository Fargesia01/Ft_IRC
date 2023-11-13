#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <string>
#include "client.hpp"

class Channel
{
	public :
		
		// Constructor and Destructor

		Channel(std::string name);
		~Channel();

		// Utils

		void	addOps(Client *client);
		void	addClient(Client *client);
		bool	isMember(Client *client);
		bool	isOps(Client *client);

		// Getters and Setters

		std::string		getPassword() const;
		std::string		getName() const;
		std::string		getTopic() const;
		std::vector<Client *>	getClients() const;

		void		setPassword(std::string pass);
		void		setName(std::string new_name);
		void		setTopic(std::string);

	private :

		std::string		password;
		std::string		name;
		std::string		topic;
		std::vector<Client *>	clients;
		std::vector<Client *>	ops;

};

#endif
