#include <iostream>
#include "cmd/parser.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return (0);
	}
	parse("TEST");
}
