#ifndef DEFINES_H
#define DEFINES_H

/* HERE ALL MACROS ARE DEFINED, THEY ARE EACH A SPECIFIC ERROR
	THEY EACH TAKE ONE OR TWO ARGUMENTS
	THE ARGUMENTS USUALLY ARE THE CLIENT NICKNAME AND THE COMMAND
*/

#define RPL_WELCOME(client) ("001 " + client + " :Welcome to the Internet Relay Network " + client + "\r\n")
#define RPL_YOURHOST(client) ("002 " + client + " :Your host is ft_irc, running version 1.0\r\n")
#define RPL_CREATED(client, datetime) ("003 " + client + " :This server was created " + datetime + "\r\n")
#define RPL_MYINFO(client, user_modes, chan_modes, chan_param_modes) ("004 " + client + " :ft_irc 1.0 " + user_modes + "\n" + chan_modes + " " + chan_param_modes + "\r\n")
#define RPL_LUSERCLIENT(client, nbrUser) ("251 " + client + ": There are " + nbrUser + " users and 0 invisible on 1 servers\r\n") 
#define RPL_LUSEROP(client, nbrOps) ("252 " + client + " " + nbrOps + ": operator(s) online\r\n")
#define RPL_LUSERCHANNELS(client, nbrChan) ("254 " + client + " " + nbrChan + ": channels formed\r\n")
#define RPL_LUSERME(client, nbrClient) ("255 " + client + " : I have " + nbrClient + " clients and 1 servers\r\n")
#define ERR_NONICKNAMEGIVEN(client) ("431 " + client + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(client, nick) ("432 " + client + " " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(client, nick) ("433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(client, cmd) ("461 " + client + " " + cmd + ": Not enough parameters\r\n")
#define ERR_ALREADYREGISTERED(client) ("462 " + client + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(client) ("464 " + client + " :Password incorrect\r\n")

#define VALID_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|"

# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

#endif
