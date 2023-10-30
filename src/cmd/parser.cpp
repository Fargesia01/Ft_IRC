#include "../../includes/parser.hpp"

void	parse(std::string text)
{
	std::vector<std::string> tab = split(text, ' '); 
	std::cout << tab.size() << std::endl;
	std::cout << tab[2] << std::endl; 
}
