#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "defines.h"

std::vector<std::string>	split(const std::string &str, const char &sep);
std::string			intToString(int nbr);
bool				validName(std::string name);

#endif
