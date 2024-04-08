#pragma once
#include <string>
#include <vector>
namespace stringHelp
{ 
	int split(std::string pszSrc, const char* flag, std::vector<std::string>& vecDat);
	std::string UnicodeToChinese(std::string str);
	std::string UTF8ToGBK(const std::string& strUTF8);
};

