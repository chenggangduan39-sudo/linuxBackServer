#include "public.h"
#include <stdio.h>
#include <time.h>
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
	for (auto& chr : str)
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
	for (auto& chr : str)
	{
		if (chr >= 'A' && chr <= 'Z')
			chr += 32;
	}
	return str;
}
std::string& replace(std::string& str, std::string target, std::string source, bool isAll)
{
	if (str.size() == 0 || target.size() == 0)
		return str;
	size_t size = source.size();
	size_t length = target.size();
	size_t pos = 0;
	while (pos < str.size())
	{
		size_t res = str.find(target, pos);
		if (res == std::string::npos)
			break;
		str.replace(res, length, source);
		if (isAll == false)
			break;
		pos = res + size;
	}
	return str;
}
void pickNumber(const std::string& source, std::string& destination, bool hasSign, bool hasDot)
{
	for (auto chr : source)
	{
		if (isdigit(chr))
			destination.push_back(chr);
		else if (hasSign == true && (chr == '+' || chr == '-'))
			destination.push_back(chr);
		else if (hasDot == true && chr == '.')
			destination.push_back(chr);
	}
}
void StringSplitter::split(const std::string& str, const std::string delimiter)
{
	if (fields.size() != 0)
		fields.clear();
	if (delimiter.empty())
		return;
	size_t pos = 0;
	size_t start = 0;
	while (start <= str.size())
	{
		pos = str.find(delimiter, start);
		std::string field = str.substr(start, pos - start);
		fields.push_back(field);
		if (pos != std::string::npos)
			start = pos + delimiter.size();
		else
			break;
	}
}
const std::string& StringSplitter::operator[](int i)
{
	return fields[i];
}
int StringSplitter::size()
{
	return fields.size();
}
std::string timeToString(time_t timePoint, const std::string& fmt)
{
	std::string time;
	tm localTime;
	localtime_r(&timePoint, &localTime);
	int year = localTime.tm_year + 1900;
	int month = localTime.tm_mon + 1;
	int day = localTime.tm_mday;
	int hour = localTime.tm_hour;
	int minute = localTime.tm_min;
	int second = localTime.tm_sec;
	if (fmt == "" || fmt == "yyyy-mm-dd hh:mi:ss")
		time = sformat("%04d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
	return time;
}
std::string getTime(const std::string& fmt, int offsetSeconds)
{
	time_t now = time(nullptr);
	time_t timePoint = now + offsetSeconds;
	std::string res = timeToString(timePoint, fmt);
	return res;
}
time_t stringToTime(const std::string& textTime)
{
	std::string destination;
	pickNumber(textTime, destination, false, false);
	if (destination.size() != 14)
		return -1;
	std::vector<std::string> timeElements;
	int ptr = 0;
	for (int i = 0; i < 6; i++)
	{
		std::string timeElement;
		if (i == 0)
		{
			timeElement = destination.substr(ptr, 4);
			ptr += 4;
		}
		else
		{
			timeElement = destination.substr(ptr, 2);
			ptr += 2;
		}
		timeElements.push_back(timeElement);
	}
	tm timePoint;
	timePoint.tm_isdst = 0;
	timePoint.tm_year = std::stoi(timeElements[0]) - 1900;
	timePoint.tm_mon = std::stoi(timeElements[1]) - 1;
	timePoint.tm_mday = std::stoi(timeElements[2]);
	timePoint.tm_hour = std::stoi(timeElements[3]);
	timePoint.tm_min = std::stoi(timeElements[4]);
	timePoint.tm_sec = std::stoi(timeElements[5]);
	time_t time = mktime(&timePoint);
	return time;
}
std::string calculateTime(const std::string& textTime, int offsetSeconds, const std::string& fmt)
{
	std::string time;
	time_t timePoint = stringToTime(textTime);
	if (timePoint == -1)
		return time;
	time_t newTime = timePoint + offsetSeconds;
	time = timeToString(newTime, fmt);
	return time;
}