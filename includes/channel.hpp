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

		// Add and Remove client and ops

		void	addOps(Client *client);
		void	addClient(Client *client);
		void	addInvited(Client *client);
		void	rmClient(Client *client);
		void	rmOps(Client *client);
		void	rmInvited(Client *client);

		// Utils

		bool	isMember(Client *client);
		bool	isMember(std::string client_name);
		bool	isOps(Client *client);
		bool	isInvited(Client *client);
		void	sendToAll(std::string msg);
		void	clientToAll(std::string msg, int fd);

		// Getters and Setters

		std::string		getPassword() const;
		std::string		getName() const;
		std::string		getTopic() const;
		std::vector<Client *>	getClients() const;
		bool			getMode(char mode) const;
		int			getUserLimit() const;

		void		setPassword(std::string pass);
		void		setName(std::string new_name);
		void		setTopic(std::string);
		void		setMode(char mode, bool value);
		void		setUserLimit(int new_limit);

	private :

		std::string		password;
		std::string		name;
		std::string		topic;
		std::vector<Client *>	clients;
		std::vector<Client *>	ops;
		std::vector<Client *>	invited;
		bool			i_only;
		bool			op_topic;
		bool			pass_req;
		unsigned int		limit;
		bool			user_limit;

};

#endif
