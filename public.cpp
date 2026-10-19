#include "public.h"
char* deleteLeftChar(char* str, char target)
{
	if (str == nullptr)
		return nullptr;
	size_t length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] != target)
		{
			memmove(str, str + i, length - i + 1);
			return str;
		}
	}
	str[0] = '\0';
	return str;
}
std::string& deleteLeftChar(std::string& str, char target)
{
	size_t pos = str.find_first_not_of(target);
	str.erase(0, pos);
	return str;
}
char* deleteRightChar(char* str, char target)
{
	if (str == nullptr)
		return nullptr;
	size_t length = strlen(str);
	if (length == 0)
		return str;
	for (size_t i = length - 1; i > 0; i--)
	{
		if (str[i] != target)
		{
			str[i + 1] = '\0';
			return str;
		}
	}
	if (str[0] == target)
		str[0] = '\0';
	else
		str[1] = '\0';
	return str;
}
std::string& deleteRightChar(std::string& str, char target)
{
	size_t pos = str.find_last_not_of(target);
	if (pos == std::string::npos)
		str.clear();
	else
		str.erase(pos + 1);
	return str;
}
char* deleteLeftRightChar(char* str, char target)
{
	if (str == nullptr)
		return nullptr;
	size_t length = strlen(str);
	if (length == 0)
		return str;
	int lpos = 0;
	int rpos = length - 1;
	char* left = str;
	char* right = str + rpos;
	while (lpos < length && *left == target)
	{
		left++;
		lpos++;
	}
	while (rpos >= 0 && *right == target)
	{
		right--;
		rpos--;
	}
	if (lpos > rpos)
	{
		str[0] = '\0';
		return str;
	}
	memmove(str, left, rpos - lpos + 1);
	str[rpos - lpos + 1] = '\0';
	return str;
}
std::string& deleteLeftRightChar(std::string& str, char target)
{
	size_t lpos = str.find_first_not_of(target);
	str.erase(0, lpos);
	size_t rpos = str.find_last_not_of(target);
	if (rpos == std::string::npos)
		str.clear();
	else
		str.erase(rpos + 1);
	return str;
}
char* toUpper(char* str)
{
	size_t length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
	return str;
}
std::string& toUpper(std::string& str)
{
	for (auto chr : str)
	{
		if (chr >= 'a' && chr <= 'z')
			chr -= 32;
	}
	return str;
}
char* toLower(char* str)
{
	size_t length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return str;
}
std::string& toLower(std::string& str)
{
	for (auto chr : str)
	{
		if (chr >= 'A' && chr <= 'Z')
			chr += 32;
	}
	return str;
}
