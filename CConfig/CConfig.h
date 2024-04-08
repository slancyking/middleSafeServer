#pragma once
#include <windows.h>
//
#include <stdlib.h>
//
#include <stdio.h>
//
#include <stdarg.h>



#define IniFilePathMax  500  

class CConfig{
public:
	CConfig();
public:
	//初始化 Ini 配置文件路径
	bool InitIni(__in char * IniPath);
	bool InitIni(__in wchar_t * IniPath);
	bool InitByFormat(char * pPathFormat, ...);


	//读取当前类指向的文件,注意,只有初始化完毕后 才可以有路径
	void * GetIniPath(bool IsAscii = false);

	//删除 指定 项  或者 子健
	bool DeleteItemName(__in char * lpAppName);
	bool DeleteItemName(__in wchar_t * lpAppName);
	bool DeleteKeyName(__in char * ItemName, __in char * KeyName);
	bool DeleteKeyName(__in wchar_t * ItemName, __in wchar_t * KeyName);

public:
	//读取(写入)字符串
	bool  GetString(__in char * ItemName, __in char * KeyName, __out char * StrBuffer, __in unsigned int BuffSize);
	bool  GetString(__in wchar_t * ItemName, __in wchar_t * KeyName, __out wchar_t * StrBuffer, __in unsigned int BuffSize);
	bool  SetString(__in char * ItemName, __in char * KeyName, __in char * StrBuffer);
	bool  SetString(__in wchar_t * ItemName, __in wchar_t * KeyName, __in wchar_t * StrBuffer);

	//读取(写入) 数值类型
	DWORD GetDword_(__in char * ItemName, __in char * KeyName, __in DWORD DefaultData = NULL);
	DWORD GetDword_(__in wchar_t * ItemName, __in wchar_t * KeyName, __in DWORD DefaultData = NULL);
	UINT  GetUInt(__in char * ItemName, __in char * KeyName, __in UINT DefaultData = NULL);
	UINT  GetUInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UINT DefaultData = NULL);
	WORD  GetWord(__in char * ItemName, __in char * KeyName, __in WORD DefaultData = NULL);
	WORD  GetWord(__in wchar_t * ItemName, __in wchar_t * KeyName, __in WORD DefaultData = NULL);
	UCHAR GetUChar(__in char * ItemName, __in char * KeyName, __in UCHAR DefaultData = NULL);
	UCHAR GetUChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UCHAR DefaultData = NULL);

	long   GetLong(__in char * ItemName, __in char * KeyName, __in long DefaultData = NULL);
	long   GetLong(__in wchar_t * ItemName, __in wchar_t * KeyName, __in long DefaultData = NULL);
	int    GetInt(__in char * ItemName, __in char * KeyName, __in int DefaultData = NULL);
	int    GetInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in int DefaultData = NULL);
	short  GetShort(__in char * ItemName, __in char * KeyName, __in short DefaultData = NULL);
	short  GetShort(__in wchar_t * ItemName, __in wchar_t * KeyName, __in short DefaultData = NULL);
	char   GetChar(__in char * ItemName, __in char * KeyName, __in char DefaultData = NULL);
	char   GetChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in char DefaultData = NULL);


	bool  SetDword(__in char * ItemName, __in char * KeyName, __in DWORD BuffData);
	bool  SetDword(__in wchar_t * ItemName, __in wchar_t * KeyName, __in DWORD BuffData);
	bool  SetUInt(__in char * ItemName, __in char * KeyName, __in UINT BuffData);
	bool  SetUInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UINT BuffData);
	bool  SetWord(__in char * ItemName, __in char * KeyName, __in WORD BuffData);
	bool  SetWord(__in wchar_t * ItemName, __in wchar_t * KeyName, __in WORD BuffData);
	bool  SetUChar(__in char * ItemName, __in char * KeyName, __in UCHAR BuffData);
	bool  SetUChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UCHAR BuffData);

	bool  SetLong(__in char * ItemName, __in char * KeyName, __in long BuffData);
	bool  SetLong(__in wchar_t * ItemName, __in wchar_t * KeyName, __in long BuffData);
	bool  SetInt(__in char * ItemName, __in char * KeyName, __in int BuffData);
	bool  SetInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in int BuffData);
	bool  SetShort(__in char * ItemName, __in char * KeyName, __in short BuffData);
	bool  SetShort(__in wchar_t * ItemName, __in wchar_t * KeyName, __in short BuffData);
	bool  SetChar(__in char * ItemName, __in char * KeyName, __in char BuffData);
	bool  SetChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in char BuffData);



private:
	char      IniFileA[IniFilePathMax];
	wchar_t   IniFileW[IniFilePathMax];
};
