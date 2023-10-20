#include "parser.hpp"

void	parse(std::string text)
{
	std::vector<std::string> tab = split(text, ' '); 
	std::cout << tab.size() << std::endl;
	std::cout << tab[7] << std::endl; 
}
