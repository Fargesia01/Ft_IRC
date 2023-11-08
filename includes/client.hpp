#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
	public :
		
		// Constructor and Destructor

		Client(int socket);
		~Client();

		// Getters and Setters

		int		getSocket() const;
		std::string	getReadBuffer() const;
		std::string	getSendBuffer() const;

		void		setReadBuffer(std::string buf);
		void		setSendBuffer(std::string buf);

	private :

		int		socket;
		std::string	readBuffer;
		std::string	sendBuffer;

};

#endif
