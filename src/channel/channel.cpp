#include "channel.hpp"

// Constructor and Destructor

Channel::Channel(std::string name): name(name)
{
	password = "";
	i_only = false;
	op_topic = false;
	pass_req = false;
	user_limit = false;
}

Channel::~Channel() {};

// Add and Remove client and ops

void	Channel::addOps(Client *client)
{
	ops.push_back(client);
}

void	Channel::addClient(Client *client)
{
	clients.push_back(client);
}

void	Channel::addInvited(Client *client)
{
	invited.push_back(client);
}

void	Channel::rmClient(Client *client)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (clients[i] == client)
		{
			clients.erase(clients.begin() + i);
			return ;
		}
	}
}

void	Channel::rmOps(Client *client)
{
	for (int i = 0; i < (int)ops.size(); i++)
	{
		if (ops[i] == client)
		{
			ops.erase(ops.begin() + i);
			return ;
		}
	}
}

void	Channel::rmInvited(Client *client)
{
	for (int i = 0; i < (int)invited.size(); i++)
	{
		if (invited[i] == client)
		{
			invited.erase(invited.begin() + i);
			return ;
		}
	}
}

// Utils

void	Channel::sendToAll(std::string msg)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
			clients[i]->setSendBuffer(msg);
	}
}

void	Channel::clientToAll(std::string msg, int fd)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (clients[i]->getSocket() != fd)
			clients[i]->setSendBuffer(msg);
	}
}

bool	Channel::isMember(Client *client)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (client == clients[i])
			return (true);
	}
	return (false);
}

bool	Channel::isMember(std::string client_name)
{
	for (int i = 0; i < (int)clients.size(); i++)
	{
		if (client_name == clients[i]->getNickname())
			return (true);
	}
	return (false);
}

bool	Channel::isInvited(Client *client)
{
	for (int i = 0; i < (int)invited.size(); i++)
	{
		if (client == invited[i])
			return (true);
	}
	return (false);
}

bool	Channel::isOps(Client *client)
{
	for (int i = 0; i < (int)ops.size(); i++)
	{
		if (client == ops[i])
			return (true);
	}
	return (false);
}

// Getters and Setters

std::string		Channel::getPassword() const { return (password); }
std::string		Channel::getName() const { return (name); }
std::string		Channel::getTopic() const { return (topic); }
std::vector<Client *>	Channel::getClients() const { return (clients); }
int			Channel::getUserLimit() const { return (limit); }

bool			Channel::getMode(char mode) const
{
	if (mode == 'i')
		return (i_only);
	else if (mode == 't')
		return (op_topic);
	else if (mode == 'k')
		return (pass_req);
	else if (mode == 'l')
		return (user_limit);
	return (false);
}

void		Channel::setPassword(std::string pass) { password = pass; }
void		Channel::setName(std::string new_name) { name = new_name; }
void		Channel::setTopic(std::string new_topic) { topic = new_topic; }
void		Channel::setUserLimit(int new_limit) { limit = new_limit; }

void		Channel::setMode(char mode, bool value)
{
	if (mode == 'i')
		i_only = value;
	else if (mode == 't')
		op_topic = value;
	else if (mode == 'k')
		pass_req = value;
	else if (mode == 'l')
		user_limit = value;
	return ;
}
