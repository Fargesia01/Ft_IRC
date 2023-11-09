#include "server.hpp"

/* Several criteria need to be met for the message to be accepted,
	I'll detail each of the test and opertation I'm doing, in the order:

	1. Is the string empty?
	2. If the message is longer than 512 bytes, then it's too long to handle
	3. The message needs to have a delimiting "\r\n" at the end, everyting
		after those chars will be ignored. 
		If they're not present, ignore the message recieved

We then split the message for it to be correctly handled:
	1. Remove the ending chars and everything after
	2. We split the message using the split() function (space as delimiter)
	3. We save the command parameters in args
	4. We look the the command in our map of available commands
		If not, then command is either wrong or not handled
	5. We finally execute the command
*/

void	Server::parse(Client *client, std::string text)
{
	if (!msgChecks(text))
		return ;

	text = text.substr(0, text.find("\r\n"));

	//if (text[0] == ':')
	//	parseSrc();

	std::vector<std::string> msg = split(text, ' ');
	std::vector<std::string> args = msg;

	args.erase(args.begin());

	if (cmd_map.find(msg[0]) == cmd_map.end())
	{
		std::cout << "Error invalid command" << std::endl;
		return ;
	}

	(this->*cmd_map[msg[0]])(client, args);

	std::cout << clients[0]->getNickname() << std::endl;
	std::cout << clients[1]->getNickname() << std::endl;
}

void	Server::parseSrc(Client *client, std::string text)
{

}

bool	msgChecks(std::string text)
{
	if (text.empty())
		return (false);
	else if (text.size() > 512)
	{
		std::cout << "Message too long" << std::endl;
		return (false);
	}
	//else if (text.find("\r\n") == std::string::npos)
	//{
	//	std::cout << "No end chars" << std::endl;
	//	return (false);
	//}
	else
		return (true);
}
