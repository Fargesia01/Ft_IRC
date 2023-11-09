#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <iostream>

#include "utils.hpp"

typedef struct s_cmd
{
	std::string			cmd;
	std::vector<std::string>	args;
}		t_cmd;

class Client
{
	public :
		
		// Constructor and Destructor

		Client(int socket);
		~Client();

		// Parsing

		int				parse();
		void				parseSrc(Client *client, std::string text);

		// Utils

		void				clearAll();

		// Getters and Setters

		int				getSocket() const;
		std::string			getReadBuffer() const;
		std::string			getSendBuffer() const;
		std::string 			getUsername() const;
		std::string			getNickname() const;
		std::string			getRealname() const;
		bool				getRegistered() const;
		bool				getAuthorized() const;
		std::string			getCmd() const;
		std::vector<std::string>	getArgs() const;

		void				setReadBuffer(std::string buf);
		void				setSendBuffer(std::string buf);
		void				setUsername(std::string new_name);
		void				setNickname(std::string new_name);
		void				setRealname(std::string new_name);
		void				setRegistered(bool regi);
		void				setAuthorized(bool auth);

	private :

		int		socket;
		std::string	readBuffer;
		std::string	sendBuffer;

		t_cmd		cmd;

		std::string	nickname;
		std::string	username;
		std::string	realname;

		bool		authorized;
		bool		registered;

};

bool	msgChecks(std::string text);

#endif
