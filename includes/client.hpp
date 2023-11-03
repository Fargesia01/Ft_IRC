#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "server.hpp"

class Server;

class Client
{
private:
    int             client_fd;
    std::string     readbuf;
    std::string     sendbuf;
    std::string     nickname;
    std::string     username;
    bool            to_deconnect;
    bool			connexion_password;
	bool			registrationDone;
	bool			welcomeSent;
	bool			hasAllInfo;
	int				nbInfo;
    
public:
    Client(int client_fd);
    ~Client();
	std::string&	getReadBuffer();
    std::string&	getSendBuffer();
    std::string&	getNickname();
    std::string 	getUsername() const;
    void            setReadBuffer(std::string const &buf);
    void	        setSendBuffer(std::string const &buf);
    bool&			getConnexionPassword();
    bool&			isRegistrationDone();
    bool&			reg();
};

Client*		getClient(Server *server, int const client_fd);

#endif