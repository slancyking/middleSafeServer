// Created by MsNiu on 2018/8/12.
#include "CString.h"
//
#include "..\\CBase64\\Base64.h"

 

CString::CString() {
	this->ascIIString = "";
}

CString::CString(const char    * _fString, ...) {
	if (NULL == _fString) _fString = "";

	va_list arglist;
	va_start(arglist, _fString);

	this->ascIIString = CString::format_va(_fString, arglist);

	va_end(arglist);
}

CString::CString(const wchar_t * _wString) {
	this->ascIIString = CString::unicode_gb2312(_wString);
}

CString::~CString() {

}

CString & CString::initWithUtf8String(const u8char * _u8String) {
	this->ascIIString = CString::utf8_gb2312(_u8String);
	return (*this);
}

CString & CString::initWithString(const char * _aString) {
	this->ascIIString = _aString ? _aString : "";
	return (*this);
}

CString & CString::initWithFormat(const char * _fString, ...) {
	if (NULL == _fString) return (*this);

	va_list arglist;
	va_start(arglist, _fString);

	this->ascIIString = CString::format_va(_fString, arglist);

	va_end(arglist);

	return (*this);
}

CString & CString::initWithFILE(const char * _pathString) {
	FILE * handle = NULL;
	if (NULL == (handle = fopen(_pathString, "r"))) {
		return (*this);
	}

	this->ascIIString = "";
	char  lineString[1024]	= { NULL };

	fseek(handle, 0, SEEK_SET);
	while (NULL != fgets(lineString, 1020, handle)) {
		this->ascIIString += lineString;
		memset(lineString, 0, 1024);
	}
	fclose(handle);

	return (*this);
}

CString & CString::initWithUtf8FILE(const char * _pathString) {
	FILE * handle = NULL;
	if (NULL == (handle = fopen(_pathString, "r"))) {
		return (*this);
	}

	std::string allString = "";
	char  lineString[1024] = { NULL };

	fseek(handle, 0, SEEK_SET);
	while (NULL != fgets(lineString, 1020, handle)) {
		allString += lineString;
		memset(lineString, 0, 1024);
	}
	fclose(handle);

	this->ascIIString = CString::utf8_gb2312((const u8char *)allString.c_str());

	return (*this);
}

void CString::addFormat(const char * _fString, ...) {
	if (NULL == _fString) return;

	va_list arglist;
	va_start(arglist, _fString);

	this->ascIIString += CString::format_va(_fString, arglist);

	va_end(arglist);
}

char CString::at(int sIndex){
	if (this->ascIIString.size() <= sIndex)
		return '\0';
	return this->ascIIString.at(sIndex);
}

void CString::replace(const char * to_replaced, const char * newchars) {
	if (NULL == to_replaced || NULL == newchars) 
		return ;
	CString::replace(this->ascIIString, to_replaced, newchars);
}

std::string & CString::replace(std::string & SBuffer, const char * to_replaced, const char * newchars) {
	if (NULL == to_replaced || NULL == newchars) return SBuffer;
	for (std::string::size_type pos(0); pos != std::string::npos; pos += strlen(newchars)) {
		pos = SBuffer.find(to_replaced, pos);
		if (pos != std::string::npos)
			SBuffer.replace(pos, strlen(to_replaced), newchars);
		else
			break;
	}
	return SBuffer;
}

void CString::trim() {
	int s = (int)this->ascIIString.find_first_not_of(" ");
	int e = (int)this->ascIIString.find_last_not_of(" ");
	if (-1 == s || -1 == e) return ;
	this->ascIIString = this->ascIIString.substr(s, e - s + 1);
}

std::string CString::getMiddleString(const char * leftStr, const char * rightStr) {
	size_t iStartIndex = this->ascIIString.find(leftStr);
	size_t iEndIndex = this->ascIIString.find(rightStr, iStartIndex + strlen(leftStr));

	if (-1 == iStartIndex || -1 == iEndIndex) { return std::string(""); }

	iStartIndex = iStartIndex + strlen(leftStr);

	if (iStartIndex >= iEndIndex) { return std::string(""); }

	return this->ascIIString.substr(iStartIndex, iEndIndex - iStartIndex);
}

//获取左侧字符串
std::string CString::left(int Count) {
	return this->ascIIString.substr(0, Count);
}

//获取中间字符串
std::string CString::mid(int Start, int endPos) {
	return this->ascIIString.substr(Start, endPos);
}

//获取右侧字符串
std::string CString::right(int Start) {
	return this->ascIIString.substr(Start, std::string::npos);
}

//字符串分割, 返回数目
int CString::split(const char * splitString, std::list<std::string> & oBuffer) {
	if (NULL == splitString || NULL == strlen(splitString)) {
		return 0;
	}

	size_t pos = 0;
	int    length_f = (int)strlen(splitString);
	int    length_s = (int)this->ascIIString.size();
	if (0 == length_s) return 0;

	while (pos < (size_t)length_s) {
		int find_pos = (int)this->ascIIString.find(splitString, pos);

		switch (find_pos) {
		case -1:
			oBuffer.push_back(this->ascIIString.substr(pos, length_s - pos));
			return (int)oBuffer.size();
		default:
			oBuffer.push_back(this->ascIIString.substr(pos, find_pos - pos));
			pos = find_pos + length_f;
			break;
		}
	}
	return (int)oBuffer.size();
}

//字符串分割, 返回数目
int CString::split(const char * splitString, std::map<int, std::string> & oBuffer) {
	if ( NULL == splitString || NULL == strlen(splitString)) {
		return 0;
	}

	int    length_s = (int)this->ascIIString.size();
	if (0 == length_s) return 0;

	std::shared_ptr<char >IsStringBuffer(new char[length_s + 2]);
	memset(IsStringBuffer.get(), 0, sizeof(char) * (length_s + 2));
	strcat(IsStringBuffer.get(), this->ascIIString.c_str());

	for (char * i = strtok(IsStringBuffer.get(), splitString); NULL != i; i = strtok(NULL, splitString)) {
		std::string tString = (NULL == i ? "" : i);
		if ("" == tString) { break; }
		oBuffer.insert(std::pair<int, std::string>(
			(int)oBuffer.size(),
			tString)
		);
	}
	return (int)oBuffer.size();
}

size_t CString::find(const char * findStr, int Start) {
	if (NULL == findStr) return std::string::npos;
	return this->ascIIString.find_first_not_of(findStr, Start);
}

bool CString::isEmpty() {
	return 0 == this->ascIIString.size();
}

// 转到 大写
void CString::toupper() {
	transform(this->ascIIString.begin(),
		this->ascIIString.end(),
		this->ascIIString.begin(),
		::toupper
	);
}

// 转到 小写
void CString::tolower() {
	transform(this->ascIIString.begin(),
		this->ascIIString.end(),
		this->ascIIString.begin(),
		::tolower
	);
}

// 不区分大小写 比较
bool CString::stricmp(const char * cmpString) {
	std::string tString = cmpString;
	return this->stricmp(tString);
}

// 不区分大小写 比较
bool CString::stricmp(std::string  cmpString) {
	std::string tString_t = this->ascIIString;
	std::string tString_c = cmpString;

	transform(tString_t.begin(), tString_t.end(), tString_t.begin(), ::toupper);
	transform(tString_c.begin(), tString_c.end(), tString_c.begin(), ::toupper);

	return tString_t == tString_c;
}

// 删除字符串
void CString::del(size_t iIndex, size_t dCount) {
	this->ascIIString.erase(iIndex, dCount);
}


std::string CString::utf8_gb2312(const u8char * _u8String) {
	size_t _sSize = 0;
	if (NULL == _u8String || 0 == (_sSize = strlen((const char *)_u8String))) {
		return  std::string("");
	}

	//得到长度, 用于申请内存使用
	int dwMinSize = ::MultiByteToWideChar(CP_UTF8, 0, (char *)_u8String, -1, NULL, 0);
	if (NULL == dwMinSize) { return  std::string(""); }
	//申请 unicode 编码缓冲区
	std::shared_ptr< wchar_t > tUnicodeString(new wchar_t[dwMinSize + 10]);
	if (NULL == tUnicodeString.get()) { return std::string(""); }
	ZeroMemory(tUnicodeString.get(), sizeof(wchar_t)* (dwMinSize + 10));
	if (NULL != ::MultiByteToWideChar(CP_UTF8, 0, (char *)_u8String, -1, tUnicodeString.get(), dwMinSize + 5)) {
		return CString::unicode_gb2312(tUnicodeString.get());
	}
	return  std::string("");
}

std::string CString::gb2312_utf8(const char * _aString) {
	size_t _sSize = 0;
	if (NULL == _aString || 0 == (_sSize = strlen(_aString)) ) {
		return  std::string("");
	}
	//转换 unicode 编码
	int tInStringLenth = MultiByteToWideChar(CP_ACP, NULL, _aString, -1, NULL, NULL);
	if (NULL == tInStringLenth) { return  std::string(""); }
	std::shared_ptr< wchar_t > tUnicodeString(new wchar_t[tInStringLenth + 10]);
	ZeroMemory(tUnicodeString.get(), sizeof(wchar_t) * (tInStringLenth + 10));
	if (NULL == MultiByteToWideChar(CP_ACP, NULL, _aString, -1, tUnicodeString.get(), tInStringLenth)) {
		return  std::string("");
	}

	//转换  utf-8 编码
	tInStringLenth = WideCharToMultiByte(CP_UTF8, NULL, tUnicodeString.get(), -1, NULL, NULL, NULL, NULL) + 6;
	std::shared_ptr< byte > tUtf8BufferString(new byte[tInStringLenth + 10]);
	ZeroMemory(tUtf8BufferString.get(), sizeof(byte) * (tInStringLenth + 10));
	if (NULL == ::WideCharToMultiByte(CP_UTF8, 0, tUnicodeString.get(), -1, (char *)tUtf8BufferString.get(), tInStringLenth, NULL, NULL)) {
		return  std::string("");
	}

	return  std::string((char *)tUtf8BufferString.get());
}

wchar_t *   CString::gb2312_unicode(const char * _aString) {
	size_t _sSize = 0;
	if (NULL == _aString || 0 == (_sSize = strlen(_aString))) {
		return NULL;
	}

	//转换 unicode 编码
	int tInStringLenth = MultiByteToWideChar(CP_ACP, NULL, _aString, -1, NULL, NULL);
	if (NULL == tInStringLenth) { return NULL; }

	tInStringLenth = tInStringLenth * 2; 

	wchar_t * wString = (wchar_t *)malloc(tInStringLenth + 10);
	if (NULL == wString) { return NULL; }
	memset(wString, 0, tInStringLenth + 10 );

	if (NULL == MultiByteToWideChar(CP_ACP, NULL, _aString, -1, wString, tInStringLenth)) {
		return NULL;
	}
	return wString;
}

std::string CString::unicode_utf8(const wchar_t * _wString) {
	size_t _sSize = 0;
	if (NULL == _wString || 0 == (_sSize = wcslen(_wString))) {
		return  std::string("");
	}
	
	std::string ascString = CString::unicode_gb2312(_wString);

	return CString::gb2312_utf8(ascString.c_str());
}

std::string CString::unicode_gb2312(const wchar_t * _wString) {
	size_t _sSize = 0;
	if (NULL == _wString || 0 == (_sSize = wcslen(_wString))) {
		return  std::string("");
	}
	//WideCharToMultiByte

	//http://baike.baidu.com/link?url=-eqWUruIH6bJwG1N1WDjFVglCXFU_KSbP6zrbT5xttb701AmwfYmcfrn6OVefXEy_HlwUkYckFv3L0906tw7q_
	DWORD dwMinSize = NULL;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, _wString, -1, NULL, 0, NULL, FALSE);
	if (NULL == dwMinSize) { return std::string(""); }

	std::shared_ptr< char > tAsciiString(new char[dwMinSize + 10]);
	if (NULL == tAsciiString.get()) { return std::string(""); }
	ZeroMemory(tAsciiString.get(), sizeof(char)* (dwMinSize + 10));
	if (NULL == WideCharToMultiByte(CP_OEMCP, NULL, _wString, -1, tAsciiString.get(), dwMinSize, NULL, FALSE)) {
		return std::string("");
	}
	return std::string(tAsciiString.get());
}

void		CString::free(wchar_t * _wString) {
	if (NULL != _wString) ::free(_wString);
}

std::string	CString::format_va(const char * _fString, va_list & args) {
	int _sSize = 0;
	if (0 >= (_sSize = vsnprintf(NULL, 0, _fString, args))) {
		return "";
	}

	std::shared_ptr<char >IsStringBuffer(new char[_sSize + 2]);
	memset(IsStringBuffer.get(), 0, sizeof(char) * (_sSize + 2));

	vsnprintf(IsStringBuffer.get(), _sSize + 1, _fString, args);

	return std::string(IsStringBuffer.get());
}

std::string	CString::format(const char * _fString, ...) {
	if (NULL == _fString) return "";

	va_list arglist;
	va_start(arglist, _fString);

	std::string rString = CString::format_va(_fString, arglist);

	va_end(arglist);

	return rString;
}

// 编码转换, base64
std::string CString::en_base64(const char * _aString) {
	return CBase64::Encode(_aString);
}

std::string CString::de_base64(const char * _aString) {
	return CBase64::Decode(_aString);
}

std::string CString::en_base64() {
	return CBase64::Encode(this->ascIIString.c_str());
}

std::string CString::de_base64() {
	return CBase64::Decode(this->ascIIString.c_str());
}

























