#include "public.h"
#include <iostream>
int main()
{
	std::string time = getTime("", -120);
	std::cout << time << std::endl;
	return 0;
}