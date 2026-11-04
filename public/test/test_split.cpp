#include "public.h"
#include <iostream>
int main()
{
	std::string str = "abc-|def-|";
	StringSplitter splitter;
	splitter.split(str, "-|");
	for (int i = 0; i < splitter.size(); i++)
	{
		std::cout << splitter[i] << std::endl;
	}
	return 0;
}