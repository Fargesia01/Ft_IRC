#include "../includes/server.hpp"

std::map<const int, Client>&	Server::getClients()		{ return (clients); }
std::string 					Server::getDatetime() const { return (datetime); }

static int acceptSocket(int listenSocket)
{
	sockaddr_in client;
	socklen_t addr_size = sizeof(sockaddr_in);
	return (accept(listenSocket, (sockaddr *)&client, &addr_size));
}

void    Server::addClient(int client_socket, std::vector<pollfd> &poll_fds)
{
    pollfd  client_pollfd;
    Client  new_client(client_socket);

    client_pollfd.fd = client_socket;
    client_pollfd.events = POLLIN | POLLOUT;
    poll_fds.push_back(client_pollfd);

    clients.insert(std::pair<int, Client>(client_socket, new_client));
    std::cout << "[SERVER]: CLIENT #" << client_socket << " ADDED" << std::endl;
}

int	Server::createClient(std::vector<pollfd>& poll_fds, std::vector<pollfd>& new_pollfds)
{
	int client_sock = acceptSocket(server_socket_fd); // on accept() le nouveau client
	if (client_sock == -1)
	{
		std::cerr << "[ERROR] accept() failed" << std::endl;
		return (3);
	}
	addClient(client_sock, new_pollfds); // on met le client_sock dans le new_pollfds
    std::cout << "[SERVER]: CLIENT ADDED. TOTAL CLIENT IS NOW: " << (unsigned int)(poll_fds.size()) << std::endl;
	return (SUCCESS);
}

int	Server::handlePollout(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd)
{
	Client *client = getClient(this, current_fd);
	if (!client)
		std::cout << "[SERVER]: CLIENT CONNEXION NOT FOUND" << std::endl;
	else
	{
		sendToClient(current_fd, client->getSendBuffer()); // on envoie les données stockées dans sendbuf au client
		client->getSendBuffer().clear(); // on efface les données qu on vient d envoyer car plus besoin
	}
	return (SUCCESS);
}

int Server::serverLoop()
{
    std::vector<pollfd> poll_fds; //vecteur de struct poll
    pollfd              server_poll_fd; //struct pour le poll de notre serveur

    server_poll_fd.fd = server_socket_fd;
    server_poll_fd.events = POLLIN;

    poll_fds.push_back(server_poll_fd);
    while (server_shutdown == false)
    {
        std::vector<pollfd> new_pollfds;
        if (poll((pollfd *)&poll_fds[0], (unsigned int)poll_fds.size(), -1) <= SUCCESS)
        {
            if (errno == EINTR)
                break ;
            std::cerr << "[ERROR] poll failed" << std::endl;
            throw ;
        }
        std::vector<pollfd>::iterator it = poll_fds.begin();
        while (it != poll_fds.end())
        {
            if (it->revents & POLLIN) // si l event est un POLLIN (données pretes à recv()) on creer le client et si il existe on gere ses actions 
            {
                if (it->fd == server_socket_fd)
                {
                    std::cout << " test test" << std::endl;
                    if (this->createClient(poll_fds, new_pollfds) == CONTINUE)
                        continue;
                }
                else
                {
                    std::cout << " ytrtes" << std::endl;
                    if (this->manageClient(poll_fds, it) == BREAK)
                        break ;
                }
            }
            else if (it->revents & POLLOUT) // si l event est un POLLOUT (données pretes à send() on envoie au client)
            {
                if (handlePollout(poll_fds, it, it->fd) == BREAK)
                    break ;
            }
            it++;
        }
        poll_fds.insert(poll_fds.end(), new_pollfds.begin(), new_pollfds.end());
    }
    return (SUCCESS);
}

static void print(std::string type, int client_socket, char *message)
{
	if (message)
		std::cout << std::endl << type << client_socket << "# => " << message;
}

int Server::manageClient(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it)
{
    Client *client;
    client = getClient(this, it->fd); //on prend le client qu on va gerer
    char message[BUF_SIZE_MSG];
    int read_count;

    memset(message, 0, sizeof(message));
    read_count = recv(it->fd, message, BUF_SIZE_MSG, 0);

    std::cout << "readcount = " << read_count << std::endl;
    if (read_count <= -1)
    {
        std::cerr << "[SERVER]: recv() FAILED" << std::endl;
        deleteClient(poll_fds, it, it->fd);
        return (BREAK);
    }
    else if (read_count == 0) // read_count == 0 si le client se deconnecte et donc on supprime le client
    {
        std::cout << "[SERVER]: A CLIENT JUST DISCONNECTED\n";
        deleteClient(poll_fds, it ,it->fd);
        return (BREAK);
    }
    else // si le read_count est positif on va gerer le message reçu par le client
    {
       print("[CLIENT]: MESSAGE RECEIVED FROM CLIENT ", it->fd, message); //on print le message reçu
       client->setReadBuffer(message); //on met le message reçu dans notre buffer

       if (client->getReadBuffer().find("\r\n") != std::string::npos)
       {
            checkReg(it->fd, client->getReadBuffer()); // vérifie si le client est enregistré sur le serveur et si il ne l est pas on 
            if (client->getReadBuffer().find("\r\n"))  // l'acceuil sur le serv avec les messages RPL qui vont aussi permettrent 
                client->getReadBuffer().clear();       // avec RPL_WELCOME d'accepter la connexion au serveur irc
       }
    }
    return (SUCCESS);
}

void	welcomeClient(Server *server, int const client_fd, std::map<const int, Client>::iterator &it)
{
	addToClientBuffer(server, client_fd, RPL_WELCOME(it->second.getNickname(), user_id(it->second.getNickname(), it->second.getUsername()))); // accepte la connexion du client au serveur irc
	addToClientBuffer(server, client_fd, RPL_YOURHOST(it->second.getNickname(), "test", "42"));                                               // https://www.rfc-editor.org/rfc/rfc2812 Paragraphe 5.1
	addToClientBuffer(server, client_fd, RPL_CREATED(it->second.getNickname(), server->getDatetime()));
	addToClientBuffer(server, client_fd, RPL_MYINFO(it->second.getNickname(), "test", "42", "usermodes", "chmodes", "chpmodes"));
} 

void Server::checkReg(int const client_fd, std::string message)
{
    std::map<const int, Client>::iterator it = clients.find(client_fd);

    if (it->second.isRegistrationDone() == false)
    {
        if (it->second.reg() == false)
        {
            welcomeClient(this, client_fd, it);
            it->second.reg() = true;
        }
    }
}

void Server::deleteClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator &it, int current_fd)
{
    std::cout << "[SERVER]: CLIENT #" << current_fd << " DISCONNECTED" << std::endl;

    int key = current_fd;

    close(current_fd);
    clients.erase(key);
    poll_fds.erase(it);

    std::cout << "[SERVER]: CLIENT DELETED. TOTAL CLIENT IS NOW: " << (unsigned int)(poll_fds.size() - 1) << std::endl;
}

Client* getClient(Server *server, int const client_fd)
{
    std::map<const int, Client>&            client_list = server->getClients();
    std::map<const int, Client>::iterator   it_client = client_list.find(client_fd);

    if (it_client == client_list.end())
        return (NULL);
    return (&it_client->second);
}   
