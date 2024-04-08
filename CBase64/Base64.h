#pragma once
#include<string>

namespace CBase64 {
	/* Base64 ±àÂë */
	std::string Encode(const char* data);
	/* Base64 ½âÂë */
	std::string Decode(const char* Data);
}

