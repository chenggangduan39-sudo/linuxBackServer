#include "public.h"
#include <iostream>
int main()
{
	std::string now = "2026-11-05 17:19:26";
	std::cout << "Your time:" << now << std::endl;
	std::string time = calculateTime("2026-11-05 17:19:26", 120);
	std::cout << "New time:" << time << std::endl;
	return 0;
}