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