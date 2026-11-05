#include "public.h"
#include <iostream>
int main()
{
	time_t now = time(nullptr);
	std::string time = timeToString(now, "yyyy-mm-dd hh:mi:ss");
	std::cout << time << std::endl;
	return 0;
}