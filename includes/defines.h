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
#define RPL_CHANNELMODEIS(client, channel, mode) ("324 " + client + " " + channel + " " + mode + "\r\n")
#define RPL_NOTOPIC(client, channel) ("331 " + client + " " + channel + " :No topic is set\r\n")
#define RPL_TOPIC(client, channel, topic) ("332 " + client + " " + channel + " :" + topic + "\r\n")
#define RPL_INVITING(client, channel, nick) ("341 " + client + " " + nick + " " + channel + "\r\n")
#define RPL_NAMREPLY(client, channel, target) (":localhost 353 " + client + " = " + channel + " " + target + "\r\n")
#define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /NAMES list\r\n")
#define ERR_NOSUCHNICK(client, target) ("401 " + client + " " + target + " :No such nick/channel\r\n")
#define ERR_NOSUCHCHANNEL(client, channel) ("403 " + client + " " + channel + " :No such channel\r\n")
#define ERR_NONICKNAMEGIVEN(client) ("431 " + client + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(client, nick) ("432 " + client + " " + nick + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(client, nick) ("433 " + client + " " + nick + " :Nickname is already in use\r\n")
#define ERR_USERNOTINCHANNEL(client, channel, nick) ("441 " + client + " " + nick + " " + channel + + " :They aren't on that channel\r\n")
#define ERR_NOTONCHANNEL(client, channel) ("442 " + client + " " + channel + " :You're not on that channel\r\n")
#define ERR_USERONCHANNEL(client, channel, nick) ("443 " + client + " " + nick + " " + channel + " :is already on channel\r\n")
#define ERR_NOTREGISTERED(client) ("451 " + client + " :You have not registered\r\n")
#define ERR_NEEDMOREPARAMS(client, cmd) ("461 " + client + " " + cmd + ": Not enough parameters\r\n")
#define ERR_ALREADYREGISTERED(client) ("462 " + client + " :You may not reregister\r\n")
#define ERR_PASSWDMISMATCH(client) ("464 " + client + " :Password incorrect\r\n")
#define ERR_CHANNELISFULL(client, channel) ("471 " + client + " " + channel + " :Cannot join channel (+l)\r\n")
#define ERR_INVITEONLYCHAN(client, channel) ("473 " + client + " " + channel + " :Cannot join channel (+i)\r\n")
#define ERR_BADCHANNELKEY(client, channel) ("475 " + client + " " + channel + " :Cannot join channel (+k)\r\n")
#define ERR_BADCHANMASK(channel) ("476 " + channel + " :Bad channel mask\r\n")
#define ERR_CHANOPRIVSNEEDED(client, channel) ("482 " + client + " " + channel + " :You're not channel operator\r\n")

#define VALID_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]{}\\|#"

# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")
# define RPL_JOIN(user_id, channel) (user_id + " JOIN :" +  channel + "\r\n")
# define RPL_PART(user_id, channel, reason) (user_id + " PART " + channel + " " + (reason.empty() ? "." : reason ) + "\r\n")
# define RPL_NOTICE(nick, username, target, message) (":" + nick + "!" + username + "@localhost NOTICE " + target + " " + message + "\r\n")
# define RPL_KICK(user_id, channel, target, reason) (user_id + " KICK " + channel + " " + target + " " + reason + "\r\n")

#endif
