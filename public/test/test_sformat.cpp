#include "public.h"
#include <iostream>
int main()
{
	std::string buffer = sformat("name = %s,age = %d", "duanchenggang", 26);
	std::cout << buffer << std::endl;
	return 0;
}