#include "client.hpp"

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

int	Client::parse()
{
	if (readBuffer.empty())
		return (-1);
	if (!msgChecks(readBuffer))
		return (-1);

	//readBuffer = readBuffer.substr(0, readBuffer.find("\r\n"));
	readBuffer = readBuffer.substr(0, readBuffer.find("\n"));

	std::vector<std::string> tmp = split(readBuffer, ' ');

	if (tmp[0][0] == ':')
		parseSrc();

	cmd.cmd = tmp[0];
	tmp.erase(tmp.begin());
	cmd.args = tmp;
	return (0);
}

void	Client::parseSrc(Client *client, std::string text)
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
	else if (text.find("\n") == std::string::npos)
	{
		std::cout << "No end chars" << std::endl;
		return (false);
	}
	else
		return (true);
}
