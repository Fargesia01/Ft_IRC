#ifndef NUMERIC_HPP
#define NUMERIC_HPP

void	      sendToClient(int const client_fd, std::string client_buffer);
Client&	      retrieveClient(Server *server, int const client_fd);
void	      addToClientBuffer(Server *server, int const client_fd, std::string reply);

# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

# define RPL_WELCOME(client, user_id) ("001 " + client + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
# define RPL_YOURHOST(client, servername, version) ("002 " + client + " :Your host is " + servername + ", running version " + version + "\r\n")
# define RPL_CREATED(client, datetime) ("003 " + client + " :This server was created " + datetime + "\r\n")
# define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) ("004 " + client + " :" + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes + "\r\n")

#endif