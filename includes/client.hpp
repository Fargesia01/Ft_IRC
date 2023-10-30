#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <map>

class Client
{
	public :

		// Constructors & Destructor
		Client();
		virtual ~Client();
		
		// Getters
		std::string	getUsername() const;
		std::string	getNickname() const;

		// Setters
		void		setUsername(std::string new_name);
		void		setNickname(std::string new_name);

	private :

		std::string	nickname;
		std::string	username;
};

#endif
