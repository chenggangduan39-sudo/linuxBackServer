#pragma once
#include <string.h>
#include <string>
#include <vector>
char* deleteLeftChar(char* str, char target = ' ');
std::string& deleteLeftChar(std::string& str, char target = ' ');
char* deleteRightChar(char* str, char target = ' ');
std::string& deleteRightChar(std::string& str, char target = ' ');
char* deleteLeftRightChar(char* str, char target = ' ');
std::string& deleteLeftRightChar(std::string& str, char target = ' ');
char* toUpper(char* str);
std::string& toUpper(std::string& str);
char* toLower(char* str);
std::string& toLower(std::string& str);
std::string& replace(std::string& str, std::string target, std::string source, bool isAll = false);
void pickNumber(std::string& source, std::string& destination, bool hasSign, bool hasDot);
class StringSplitter
{
private:
	std::vector<std::string> fields;

public:
	void split(const std::string& str, const std::string delimiter);
	const std::string& operator[](int i);
	int size();
};
template <typename... Args>
std::string sformat(const char* fmt, Args... args)
{
	std::string buffer;
	int length = snprintf(nullptr, 0, fmt, args...);
	if (length < 0)
		return buffer;
	buffer.resize(length + 1);
	snprintf(&buffer[0], length + 1, fmt, args...);
	return buffer;
}
std::string timeToString(time_t timePoint, const std::string& fmt);
std::string getTime(const std::string& fmt = "", int offsetSeconds = 0);
time_t stringToTime(const std::string& textTime);
std::string calculateTime(const std::string& textTime, int offsetSeconds, const std::string& fmt = "");
class Stopwatch
{
private:
	timeval startTime;
	timeval endTime;

public:
	Stopwatch();
	void start();
	double elapsed();
};
bool createDirectory(const std::string& pathname, bool isFileName);
bool renameFile(const std::string& srcFile, const std::string& dstFile);
off_t getFileSize(const std::string& fileName);
std::string getFileModificationTime(const std::string& fileName, const std::string& fmt = "");
bool setFileModificationTime(const std::string& fileName, const std::string& time);