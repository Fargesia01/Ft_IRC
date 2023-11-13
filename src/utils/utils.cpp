#include "utils.hpp"

std::vector<std::string> split(const std::string &str, const char &sep)
{
	std::string	cpy = str;
	std::vector<std::string> tab;
	std::string::size_type	pos = cpy.find(sep);
	
	while (pos != std::string::npos)
	{
		tab.push_back(cpy.substr(0, pos));
		cpy.erase(0, pos + 1);
		pos = cpy.find(sep);
	
	}

	if (cpy.empty() == false)
		tab.push_back(cpy);
	return (tab);
}

std::string	intToString(int nbr)
{
	std::stringstream oss;
	oss << nbr;
	return (oss.str());
}