#include "public.h"
#include <iostream>
int main()
{
	char str[] = "HELLO!";
	std::cout << str << std::endl;
	std::cout << strlen(str) << std::endl;
	toLower(str);
	std::cout << str << std::endl;
	std::cout << strlen(str) << std::endl;
	return 0;
}