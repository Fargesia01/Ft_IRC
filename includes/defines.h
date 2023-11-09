#ifndef DEFINES_H
#define DEFINES_H

/* HERE ALL MACROS ARE DEFINED, THEY ARE EACH A SPECIFIC ERROR
	THEY EACH TAKE ONE OR TWO ARGUMENTS
	THE ARGUMENTS USUALLY ARE THE CLIENT NICKNAME AND THE COMMAND
*/

# define RPL_WELCOME(client, user_id) ("001 " + client + " :Welcome to the Internet Relay Network " + user_id + "\r\n")
# define RPL_YOURHOST(client, servername, version) ("002 " + client + " :Your host is " + servername + ", running version " + version + "\r\n")
# define RPL_CREATED(client, datetime) ("003 " + client + " :This server was created " + datetime + "\r\n")
# define RPL_MYINFO(client, servername, version, user_modes, chan_modes, chan_param_modes) ("004 " + client + " :" + servername + " " + version + " " + user_modes + " " + chan_modes + " " + chan_param_modes + "\r\n")

#define ERR_NONICKNAMEGIVEN(client) "431 " + client + " :No nickname given"
#define ERR_ERRONEUSNICKNAME(client, nick) " 432 " + client + " " + nick + " :Erroneus nickname"
#define ERR_NICKNAMEINUSE(client, nick) " 433 " + client + " " + nick + " :Nickname is already in use"
#define ERR_NEEDMOREPARAMS(client, cmd) " 461 " + client + " " + cmd + ": Not enough parameters"
#define ERR_ALREADYREGISTERED(client) " 462 " + client + " :You may not reregister"
#define ERR_PASSWDMISMATCH(client) " 464 " + client + " :Password incorrect"

#define VALID_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|"

# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

#endif
