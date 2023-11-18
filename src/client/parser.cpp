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

void	Client::parse()
{
	std::string				actual;
	t_cmd					cmd;

	while (!readBuffer.empty())
	{
		std::vector<std::string> args;
		bool					last_arg = false;

		if (readBuffer.empty())
			return ;
		if (!msgChecks(readBuffer))
			return ;

		actual = readBuffer.substr(0, readBuffer.find("\r\n"));
		readBuffer.erase(0, readBuffer.find("\r\n") + 2);

		std::vector<std::string> tmp = split(actual, ' ');

		if (tmp[0][0] == ':')
		{
			if (parseSrc(tmp[0]) == 0)
				tmp.erase(tmp.begin());
		}

		for (int i = 0; i < (int)tmp.size(); i++)
		{
			if (tmp[i][0] == ':')
			{
				last_arg = true;
				tmp[i].erase(0, 1);
				args.push_back(tmp[i]);
				continue ;
			}
			if (last_arg)
				args.back() += " " + tmp[i];
			else
				args.push_back(tmp[i]);
		}

		cmd.cmd = args[0];
		args.erase(args.begin());
		cmd.args = args;
		cmds.push_back(cmd);
		nbr_cmds++;
	}
	readBuffer.clear();
}

int	Client::parseSrc(std::string text)
{
	if (text.find("!") == std::string::npos)
		return (-1);
	text.erase(0, text.find("!") + 1);
	if (text.find("@") == std::string::npos)
		return (-1);
	return (0);
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
	else if (text.find("\r\n") == std::string::npos)
	{
		std::cout << "No end chars" << std::endl;
		return (false);
	}
	else
		return (true);
}
