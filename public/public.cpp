#include "public.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
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
Stopwatch::Stopwatch()
{
	start();
}
void Stopwatch::start()
{
	gettimeofday(&startTime, nullptr);
}
double Stopwatch::elapsed()
{
	gettimeofday(&endTime, nullptr);
	double startPoint = startTime.tv_sec * 1000000 + startTime.tv_usec;
	double endPoint = endTime.tv_sec * 1000000 + endTime.tv_usec;
	double elapsed = (endPoint - startPoint) / 1000000;
	start();
	return elapsed;
}
bool createDirectory(const std::string& pathName, bool isFileName)
{
	if (access(pathName.c_str(), F_OK) == 0)
		return true;
	int pos = 1;
	std::string subDir;
	while (subDir != pathName)
	{
		size_t next = pathName.find('/', pos);
		if (next == std::string::npos && isFileName == true)
			return true;
		subDir += pathName.substr(pos - 1, next - pos + 1);
		if (access(subDir.c_str(), F_OK) != 0)
		{
			int res = mkdir(subDir.c_str(), 0755);
			if (res == -1)
				return false;
		}
		pos = next + 1;
	}
	return true;
}
bool renameFile(const std::string& srcFile, const std::string& dstFile)
{
	if (access(srcFile.c_str(), F_OK) != 0)
		return false;
	if (createDirectory(dstFile, true) == false)
		return false;
	if (rename(srcFile.c_str(), dstFile.c_str()) == 0)
		return true;
	else
		return false;
}
off_t getFileSize(const std::string& fileName)
{
	struct stat st;
	int res = stat(fileName.c_str(), &st);
	if (res == -1)
		return -1;
	return st.st_size;
}
std::string getFileModificationTime(const std::string& fileName, const std::string& fmt)
{
	std::string time;
	struct stat st;
	int res = stat(fileName.c_str(), &st);
	if (res == -1)
		return time;
	time = timeToString(st.st_mtime, fmt);
	return time;
}
bool setFileModificationTime(const std::string& fileName, const std::string& time)
{
	utimbuf mtime;
	time_t dstTime = stringToTime(time);
	if (dstTime == -1)
		return false;
	mtime.actime = dstTime;
	mtime.modtime = dstTime;
	int res = utime(fileName.c_str(), &mtime);
	if (res == 0)
		return true;
	else
		return false;
}
bool copyFile(const std::string& srcFileName, const std::string& dstFileName)
{
	if (srcFileName == dstFileName)
		return true;
	std::ifstream ifs;
	std::ofstream ofs;
	ifs.open(srcFileName, std::ios::binary | std::ios::in);
	if (ifs.is_open() == false)
		return false;
	std::string buffer;
	buffer.resize(1024);
	ofs.open(dstFileName, std::ios::binary | std::ios::out);
	if (ofs.is_open() == false)
	{
		bool res = createDirectory(dstFileName, true);
		if (res == false)
			return false;
		ofs.open(dstFileName, std::ios::binary | std::ios::out);
	}
	while (true)
	{
		ifs.read(&buffer[0], 1024);
		std::streamsize count = ifs.gcount();
		if (count == 0)
			break;
		ofs.write(&buffer[0], count);
	}
	ifs.close();
	ofs.close();
	std::string mtime = getTime();
	setFileModificationTime(dstFileName, mtime);
	return true;
}
bool matchstr(const std::string& str, const std::string& rules)
{
	if (rules.length() == 0)
		return false;
	if (rules == "*")
		return true;
	int ii, jj;
	int pos1, pos2;
	StringSplitter cmdstr, cmdsubstr;
	std::string filename = str;
	std::string matchstr = rules;
	toUpper(filename);
	toUpper(matchstr);
	cmdstr.split(matchstr, ",");
	for (ii = 0; ii < cmdstr.size(); ii++)
	{
		if (cmdstr[ii].empty() == true)
			continue;
		pos1 = pos2 = 0;
		cmdsubstr.split(cmdstr[ii], "*");
		for (jj = 0; jj < cmdsubstr.size(); jj++)
		{
			if (jj == 0)
				if (filename.substr(0, cmdsubstr[jj].length()) != cmdsubstr[jj])
					break;
			if (jj == cmdsubstr.size() - 1)
				if (filename.find(cmdsubstr[jj], filename.length() - cmdsubstr[jj].length()) == std::string::npos)
					break;
			pos2 = filename.find(cmdsubstr[jj], pos1);
			if (pos2 == std::string::npos)
				break;
			pos1 = pos2 + cmdsubstr[jj].length();
		}
		if (jj == cmdsubstr.size())
			return true;
	}
	return false;
}
void DirectoryScanner::scan(const std::string& pathName, const std::string& rules, bool isDeep)
{
	DIR* dirp = opendir(pathName.data());
	if (dirp == nullptr)
		return;
	while (true)
	{
		dirent* res = readdir(dirp);
		if (res == nullptr)
			break;
		std::string name = res->d_name;
		if (matchstr(name, ".*") == true)
			continue;
		std::string info = pathName + "/" + name;
		fileInfo.push_back(info);
		if (res->d_type == DT_DIR && isDeep == true)
		{
			std::string subPathName = pathName + "/" + name;
			scan(subPathName.data(), rules, isDeep);
		}
	}
	closedir(dirp);
	return;
}
void DirectoryScanner::printFileInfo()
{
	if (fileInfo.size() == 0)
		return;
	for (auto& info : fileInfo)
		std::cout << info << std::endl;
}