#pragma once
#include "CConfig.h"


//--------------------------------------------------------------------
//|                    字符串的 互转（ANSI字符集 与 Unicode字符集）
bool IniChar_wchar_t(__in char * InStr, __out wchar_t * OutStrBuffer, __in int OutStrBufferSize){

	if (NULL == InStr || NULL == OutStrBuffer){ return false; }

	//MultiByteToWideChar
	//http://baike.baidu.com/link?url=R1bYIh3tz9idLOQIRFUwAj0J6XJqFpDWVtz6l8nKFJXKHyTlrlJuKE9lgYe9BZQ4oyV9ns10IlXubvSXPCDtFa

	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, NULL, InStr, -1, NULL, NULL);
	if (NULL == dwMinSize || dwMinSize > (DWORD)OutStrBufferSize){
		return false;
	}
	if (NULL == MultiByteToWideChar(CP_ACP, NULL, InStr, -1, OutStrBuffer, dwMinSize)){
		return false;
	}
	return true;
}

bool Iniwchar_t_Char(__in wchar_t * InStr, __out char * OutStrBuffer, __in int OutStrBufferSize){

	if (NULL == InStr || NULL == OutStrBuffer){ return false; }

	//WideCharToMultiByte
	//http://baike.baidu.com/link?url=-eqWUruIH6bJwG1N1WDjFVglCXFU_KSbP6zrbT5xttb701AmwfYmcfrn6OVefXEy_HlwUkYckFv3L0906tw7q_
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, InStr, -1, NULL, 0, NULL, FALSE);
	if (NULL == dwMinSize || dwMinSize > (DWORD)OutStrBufferSize){
		return false;
	}
	if (NULL == WideCharToMultiByte(CP_OEMCP, NULL, InStr, -1, OutStrBuffer, dwMinSize, NULL, FALSE)){
		return false;
	}
	return true;
}


CConfig::CConfig(){
	ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
	ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
}


bool CConfig::InitIni(__in char * IniPath){
	if (NULL == IniPath){return false;}

	DWORD 	StrSize = (DWORD)strlen(IniPath);
	//当前目录
	if (NULL == strstr(IniPath, ":")){
		if (IniFilePathMax <= StrSize){ goto GoToError; }
#pragma region//|-----------------------------------------------------------------使用的是 当前默认目录
		char AppPath[MAX_PATH] = { NULL };
		if (NULL >= GetModuleFileNameA(NULL, AppPath, MAX_PATH)){
			goto GoToError;
		}
		char * FindPos = strrchr(AppPath,'\\');	//寻找尾部的 \\  结尾

		if (NULL == FindPos){goto GoToError;}
		FindPos[1] = 0x00;
		//再次判断 长度是否超过限制
		StrSize = StrSize + (DWORD)strlen(AppPath);
		if (IniFilePathMax <= StrSize){ goto GoToError; }
		//将内存链接起来
		ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
		wsprintfA(this->IniFileA, "%s%s\0", AppPath, IniPath);
		
		ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
		if (false == IniChar_wchar_t(this->IniFileA, this->IniFileW, IniFilePathMax)){
			goto GoToError;
		}
		return true;
#pragma endregion
	}
	//全局目录
	ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
	CopyMemory(this->IniFileA, (void *)IniPath, sizeof(char)* StrSize);
	
	ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
	if (false == IniChar_wchar_t(this->IniFileA, this->IniFileW, IniFilePathMax)){
		goto GoToError;
	}
	return true;
GoToError:
	ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
	ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
	return false;
}

bool CConfig::InitIni(__in wchar_t * IniPath){
	if (NULL == IniPath){ return false; }

	DWORD 	StrSize = (DWORD)wcslen(IniPath);
	//当前目录
	if (NULL == wcsstr(IniPath, L":")){
		if (IniFilePathMax <= StrSize){ goto GoToError; }
#pragma region//|-----------------------------------------------------------------使用的是 当前默认目录
		wchar_t AppPath[MAX_PATH] = { NULL };
		if (NULL >= GetModuleFileNameW(NULL, AppPath, MAX_PATH)){
			goto GoToError;
		}
		wchar_t * FindPos = wcsrchr(AppPath, L'\\');	//寻找尾部的 \\
				
		if (NULL == FindPos){ goto GoToError; }
		FindPos[1] = (wchar_t)0x0000;

		//再次判断 长度是否超过限制
		StrSize = StrSize + (DWORD)wcslen(AppPath);
		if (IniFilePathMax <= StrSize){ goto GoToError; }
		//将内存链接起来
		ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
		wsprintfW(this->IniFileW, L"%s%s\0", AppPath, IniPath);

		ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
		if (false == Iniwchar_t_Char(this->IniFileW, this->IniFileA, IniFilePathMax)){
			goto GoToError;
		}
		return true;
#pragma endregion
	}
	//全局目录
	ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
	CopyMemory(this->IniFileW, (void *)IniPath, sizeof(wchar_t)* StrSize);

	ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
	if (false == Iniwchar_t_Char(this->IniFileW, this->IniFileA, IniFilePathMax)){
		goto GoToError;
	}
	return true;
GoToError:
	ZeroMemory(this->IniFileA, sizeof(char) * IniFilePathMax);
	ZeroMemory(this->IniFileW, sizeof(wchar_t) * IniFilePathMax);
	return false;

}

bool CConfig::InitByFormat(char * pPathFormat, ...){
	if (NULL == pPathFormat){ return false; }
	va_list args;
	va_start(args, pPathFormat);
	char tPath[1024] = { NULL };
	vsnprintf_s(tPath, 1024, pPathFormat, args);
	return this->InitIni(tPath);
}



void * CConfig::GetIniPath(bool IsAscii){
	if (NULL >= strlen(this->IniFileA)){
		return NULL;
	}
	
	if (true == IsAscii){
		return (void*)(this->IniFileA);
	}
	return (void*)(this->IniFileW);
}


//删除 指定 项  或者 子健
bool CConfig::DeleteItemName(__in char * ItemName){
	return (NULL != WritePrivateProfileStructA(ItemName, NULL, NULL, NULL, this->IniFileA));
}

bool CConfig::DeleteItemName(__in wchar_t * ItemName){
	return (NULL != WritePrivateProfileStructW(ItemName, NULL, NULL, NULL, this->IniFileW));
}

bool CConfig::DeleteKeyName(__in char * ItemName, __in char * KeyName){
	return (NULL != WritePrivateProfileStructA(ItemName, KeyName, NULL, NULL, this->IniFileA));
}

bool CConfig::DeleteKeyName(__in wchar_t * ItemName, __in wchar_t * KeyName){
	return (NULL != WritePrivateProfileStructW(ItemName, KeyName, NULL, NULL, this->IniFileW));
}


bool CConfig::GetString(__in char * ItemName, __in char * KeyName, __out char * StrBuffer, __in unsigned int BuffSize){
	if (NULL < GetPrivateProfileStringA(ItemName, KeyName, NULL, StrBuffer, BuffSize, this->IniFileA)){
		return true;
	}
	return false;
}

bool CConfig::GetString(__in wchar_t * ItemName, __in wchar_t * KeyName, __out wchar_t * StrBuffer, __in unsigned int BuffSize){
	if (NULL < GetPrivateProfileStringW(ItemName, KeyName, NULL, StrBuffer, BuffSize, this->IniFileW)){
		return true;
	}
	return false;
}

bool CConfig::SetString(__in char * ItemName, __in char * KeyName, __out char * StrBuffer){
	if (NULL == WritePrivateProfileStringA(ItemName, KeyName, StrBuffer, this->IniFileA)){
		return false;
	}
	return true;
}

bool CConfig::SetString(__in wchar_t * ItemName, __in wchar_t * KeyName, __out wchar_t * StrBuffer){
	if (NULL == WritePrivateProfileStringW(ItemName, KeyName, StrBuffer, this->IniFileW)){
		return false;
	}
	return true;
}




bool CConfig::SetDword(char * ItemName, char * KeyName, DWORD BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(DWORD), this->IniFileA));
}

bool CConfig::SetDword(wchar_t * ItemName, wchar_t * KeyName, DWORD BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(DWORD), this->IniFileW));
}

DWORD CConfig::GetDword_(char * ItemName, char * KeyName, DWORD DefaultData){
	DWORD RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(DWORD), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

DWORD CConfig::GetDword_(wchar_t * ItemName, wchar_t * KeyName, DWORD DefaultData){
	DWORD RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(DWORD), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}




bool  CConfig::SetUInt(__in char * ItemName, __in char * KeyName, __in UINT BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(UINT), this->IniFileA));
}

bool  CConfig::SetUInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UINT BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(UINT), this->IniFileW));
}

UINT  CConfig::GetUInt(__in char * ItemName, __in char * KeyName, __in UINT DefaultData ){
	return GetPrivateProfileIntA(ItemName, KeyName, DefaultData, this->IniFileA);
}

UINT  CConfig::GetUInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UINT DefaultData ){
	return GetPrivateProfileIntW(ItemName, KeyName, DefaultData, this->IniFileW);
}




bool CConfig::SetWord(__in char * ItemName, __in char * KeyName, __in WORD BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(WORD), this->IniFileA));
}

bool CConfig::SetWord(__in wchar_t * ItemName, __in wchar_t * KeyName, __in WORD BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(WORD), this->IniFileW));
}

WORD CConfig::GetWord(__in char * ItemName, __in char * KeyName, __in WORD DefaultData){
	WORD RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(WORD), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

WORD CConfig::GetWord(__in wchar_t * ItemName, __in wchar_t * KeyName, __in WORD DefaultData){
	WORD RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(WORD), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}




bool CConfig::SetUChar(__in char * ItemName, __in char * KeyName, __in UCHAR BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(UCHAR), this->IniFileA));
}

bool CConfig::SetUChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UCHAR BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(UCHAR), this->IniFileW));
}

UCHAR CConfig::GetUChar(__in char * ItemName, __in char * KeyName, __in UCHAR DefaultData ){
	UCHAR RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(UCHAR), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

UCHAR CConfig::GetUChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in UCHAR DefaultData ){
	UCHAR RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(UCHAR), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}





bool CConfig::SetLong(__in char * ItemName, __in char * KeyName, __in long BuffData) {
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(long), this->IniFileA));
}

bool CConfig::SetLong(__in wchar_t * ItemName, __in wchar_t * KeyName, __in long BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(long), this->IniFileW));
}

long CConfig::GetLong(__in char * ItemName, __in char * KeyName, __in long DefaultData ) {
	long RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(long), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

long CConfig::GetLong(__in wchar_t * ItemName, __in wchar_t * KeyName, __in long DefaultData){
	long RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData,sizeof(long), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}



bool CConfig::SetInt(__in char * ItemName, __in char * KeyName, __in int BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(int), this->IniFileA));
}

bool CConfig::SetInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in int BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(int), this->IniFileW));
}

int CConfig::GetInt(__in char * ItemName, __in char * KeyName, __in int DefaultData ){
	int RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(int), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

int CConfig::GetInt(__in wchar_t * ItemName, __in wchar_t * KeyName, __in int DefaultData ){
	int RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(int), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}




bool  CConfig::SetShort(__in char * ItemName, __in char * KeyName, __in short BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(short), this->IniFileA));
}

bool CConfig::SetShort(__in wchar_t * ItemName, __in wchar_t * KeyName, __in short BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(short), this->IniFileW));
}

short  CConfig::GetShort(__in char * ItemName, __in char * KeyName, __in short DefaultData ){
	short RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(short), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

short CConfig::GetShort(__in wchar_t * ItemName, __in wchar_t * KeyName, __in short DefaultData ){
	short RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(short), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}



bool  CConfig::SetChar(__in char * ItemName, __in char * KeyName, __in char BuffData){
	return (TRUE == WritePrivateProfileStructA(ItemName, KeyName, &BuffData, sizeof(char), this->IniFileA));
}

bool  CConfig::SetChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in char BuffData){
	return (TRUE == WritePrivateProfileStructW(ItemName, KeyName, &BuffData, sizeof(char), this->IniFileW));
}

char  CConfig::GetChar(__in char * ItemName, __in char * KeyName, __in char DefaultData ){
	char RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructA(ItemName, KeyName, &RetData, sizeof(char), this->IniFileA)){
		return DefaultData;
	}
	return RetData;
}

char  CConfig::GetChar(__in wchar_t * ItemName, __in wchar_t * KeyName, __in char DefaultData ){
	char RetData = DefaultData;
	if (FALSE == GetPrivateProfileStructW(ItemName, KeyName, &RetData, sizeof(char), this->IniFileW)){
		return DefaultData;
	}
	return RetData;
}


