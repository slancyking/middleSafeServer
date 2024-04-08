#include "stringHelp.h"
#include <uchar.h>  
#include <windows.h>
#include <memory>


int stringHelp::split(std::string pszSrc, const char* flag, std::vector<std::string>& vecDat)
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
};

std::string stringHelp::UnicodeToChinese(std::string str)
{

	std::vector<std::string> vecDat;
	int _count = split(str, "\\u", vecDat);
	wchar_t* sle = new wchar_t[_count + 1];
	char* csle = new char[_count + 1];
	char* p = csle;
	mbstate_t ps{};
	size_t length;

	memset(sle, 0, sizeof(wchar_t) * (_count + 1));

	for (int i = 0; i < _count; i++) {
		sle[i] = strtol(vecDat[i].c_str(), NULL, 16);
	}
	for (size_t n = 0; n < _count; ++n) {
		int rc = c16rtomb(p, sle[n], &ps);
		if (rc == -1) break;
		p += rc;
	}
	std::string result(csle);
	delete[]  sle;
	delete[]  csle;

	return result;
};

std::string stringHelp::UTF8ToGBK(const std::string& strUTF8)

{

	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);

	unsigned short* wszGBK = new unsigned short[len + 1];

	memset(wszGBK, 0, len * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, (char*)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);

	char* szGBK = new char[len + 1];

	memset(szGBK, 0, len + 1);

	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);

	//strUTF8 = szGBK;

	std::string strTemp(szGBK);

	delete[]szGBK;

	delete[]wszGBK;

	return strTemp;

}


std::string stringHelp::GBKToUTF8(const std::string& strGBK)
{
	size_t _sSize = 0;
	if (0 == (_sSize = strlen(strGBK.c_str()))) {
		return  std::string("");
	}
	//×ª»» unicode ±àÂë
	int tInStringLenth = MultiByteToWideChar(CP_ACP, NULL, strGBK.c_str(), -1, NULL, NULL);
	if (NULL == tInStringLenth) { return  std::string(""); }
	std::shared_ptr< wchar_t > tUnicodeString(new wchar_t[tInStringLenth + 10]);
	ZeroMemory(tUnicodeString.get(), sizeof(wchar_t) * (tInStringLenth + 10));
	if (NULL == MultiByteToWideChar(CP_ACP, NULL, strGBK.c_str(), -1, tUnicodeString.get(), tInStringLenth)) {
		return  std::string("");
	}

	//×ª»»  utf-8 ±àÂë
	tInStringLenth = WideCharToMultiByte(CP_UTF8, NULL, tUnicodeString.get(), -1, NULL, NULL, NULL, NULL) + 6;
	std::shared_ptr< byte > tUtf8BufferString(new byte[tInStringLenth + 10]);
	ZeroMemory(tUtf8BufferString.get(), sizeof(byte) * (tInStringLenth + 10));
	if (NULL == ::WideCharToMultiByte(CP_UTF8, 0, tUnicodeString.get(), -1, (char*)tUtf8BufferString.get(), tInStringLenth, NULL, NULL)) {
		return  std::string("");
	}

	return  std::string((char*)tUtf8BufferString.get());


}