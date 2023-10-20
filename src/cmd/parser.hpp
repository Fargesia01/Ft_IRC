#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>

typedef struct s_message
{
	std::string			cmd;
	std::vector<std::string>	args;
	
}		t_msg;

void	parse(std::string text);

#endif
