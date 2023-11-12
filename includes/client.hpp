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

		void				parse();
		int				parseSrc(std::string text);

		// Utils

		void				popCmd();

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
		int				getNbrCmds() const;

		void				setReadBuffer(std::string buf);
		void				setSendBuffer(std::string buf);
		void				clearSendBuffer();
		void				setUsername(std::string new_name);
		void				setNickname(std::string new_name);
		void				setRealname(std::string new_name);
		void				setRegistered(bool regi);
		void				setAuthorized(bool auth);
		void				setNbrCmds(int nbr);

	private :

		int			socket;
		std::string		readBuffer;
		std::string		sendBuffer;

		std::vector<t_cmd>	cmds;
		int			nbr_cmds;

		std::string		nickname;
		std::string		username;
		std::string		realname;

		bool			authorized;
		bool			registered;

};

bool	msgChecks(std::string text);

#endif
