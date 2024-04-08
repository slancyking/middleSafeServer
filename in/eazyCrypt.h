#pragma once

namespace eazyCrypt {



	/// <summary>
	/// 根据文本计算md5
	/// </summary>
	/// <param name="str">源文本</param>
	/// <param name="longger">是否长结果</param>
	/// <param name="upper">是否大写</param>
	/// <returns></returns>
	std::string makeMd5ByString(std::string str, bool longger = true, bool upper = false);

	std::string makeMd5ByBuffer(void* buf, size_t size, bool longger = true, bool upper = false);


#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))
	std::string XXTeaEncrypted(std::string str, std::string key);


}

 

