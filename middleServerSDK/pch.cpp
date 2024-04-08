// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"   

#include <uchar.h> 

//#include <atlconv.h>
// 当使用预编译的头时，需要使用此源文件，编译才能成功。
//字符转换成整形
int hex2int(char c)
{
    if ((c >= 'A') && (c <= 'Z'))
    {
        return c - 'A' + 10;
    }
    else if ((c >= 'a') && (c <= 'z'))
    {
        return c - 'a' + 10;
    }
    else if ((c >= '0') && (c <= '9'))
    {
        return c - '0';
    }
    return 0;
}

/**
 * 字符串替换函数
 * #function name   : replace_str()
 * #param str       : 操作之前的字符串
 * #param before    : 将要被替换的字符串
 * #param after     : 替换目标字符串
 * #return          : void
 */
void replace_str(std::string& str, const std::string& before, const std::string& after)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos += after.length())
    {
        pos = str.find(before, pos);
        if (pos != std::string::npos)
            str.replace(pos, before.length(), after);
        else
            break;
    }
}

int split(std::string pszSrc, const char* flag, std::vector<std::string>& vecDat)
{
	if (pszSrc.empty() || !flag)
		return -1;

	std::string strContent, strTemp;
	strContent = pszSrc;
	std::string::size_type nBeginPos = 0, nEndPos = 0;
	while (true)
	{
		nEndPos = strContent.find(flag, nBeginPos);
		if (nEndPos == std::string::npos)
		{
			strTemp = strContent.substr(nBeginPos, strContent.length());
			if (!strTemp.empty())
			{
				vecDat.push_back(strTemp);
			}
			break;
		}
		strTemp = strContent.substr(nBeginPos, nEndPos - nBeginPos);
		nBeginPos = nEndPos + strlen(flag);
		vecDat.push_back(strTemp);
	}
	return vecDat.size();
} 

string UnicodeToChinese(string str)
{  

	std::vector<std::string> vecDat;
	int _count = split(str, "\\u", vecDat);
	WCHAR* sle = new WCHAR[_count + 1];
	char* csle = new char[_count + 1];
	char* p = csle;
	mbstate_t ps{};
	size_t length;

	memset(sle, 0, sizeof(TCHAR) * (_count + 1));

	for (int i = 0; i < _count; i++) {
		sle[i] = strtol(vecDat[i].c_str(), NULL, 16); 
	}
	for (size_t n = 0; n < _count; ++n) {
		int rc = c16rtomb(p, sle[n], &ps);
		if (rc == -1) break;
		p += rc;
	}
	string result(csle);
	delete[]  sle;
	delete[]  csle;

	return result;
}


//std::string std_string_format( const char* _Format, ...) {
//	std::string tmp;
//
//	va_list marker = NULL;
//	va_start(marker, _Format);
//
//	size_t num_of_chars = _vscprintf(_Format, marker);
//
//	if (num_of_chars > tmp.capacity()) {
//		tmp.resize(num_of_chars + 1);
//	}
//
//	vsprintf_s((char*)tmp.data(), tmp.capacity(), _Format, marker);
//
//	va_end(marker);
//	 
//	return tmp;
//} 