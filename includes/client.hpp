#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <map>

class Client
{
	public :

		Client();
		virtual ~Client();
		
		std::string	getUsername() const;
		std::string	getNickname() const;
		void		setUsername(std::string new_name);
		void		setNickname(std::string new_name);

	private :

		std::string	nickname;
		std::string	username;
};

#endif
