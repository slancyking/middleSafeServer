#pragma once
#include <string>

class WebAlgorithm
{
public:
	static std::string  GUIDDecrypt(std::string source);

	static std::string GetstringDecrypt(std::string _content, std::string sguid);
};

