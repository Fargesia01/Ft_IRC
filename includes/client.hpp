#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client
{
	public :
		
		// Constructor and Destructor

		Client(int socket);
		~Client();

		// Getters and Setters

		int	getSocket() const;

	private :

		int	socket;

};

#endif
