#include "public.h"
#include <iostream>
int main()
{
	std::string str = "abc-23.56";
	std::cout << str << std::endl;
	// std::cout << strlen(str) << std::endl;
	std::string target;
	pickNumber(str, target, true, true);
	std::cout << target << std::endl;
	// std::cout << strlen(str) << std::endl;
	return 0;
}