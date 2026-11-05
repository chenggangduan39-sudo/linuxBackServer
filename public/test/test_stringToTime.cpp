#include "public.h"
#include <iostream>
int main()
{
	std::string timeText = "2026-11-05 16:56:28";
	time_t time = stringToTime(timeText);
	std::cout << "Your time:" << timeText << std::endl;
	std::cout << "time_t:" << time << std::endl;
	return 0;
}