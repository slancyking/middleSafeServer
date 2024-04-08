#pragma once
#include "CShareMemory.h"
#include <stdio.h>
#include <memory>



//--------------------------------------------------------------------
//|                    字符串的 互转（ANSI字符集 与 Unicode字符集）
//--------------------------------------------------------------------
//|函数名：bool Char_wchar__in char * InStr, __out wchar_t * OutStrBuffer, __in int OutStrBufferSize)
//|函数名：bool wchar_t_Char(__in wchar_t * InStr, __out char * OutStrBuffer, __in int OutStrBufferSize)
//| 解 释：无
//|返回值：返回true 或 false
//|附加：无
//--------------------------------------------------------------------
bool ShareChar_wchar_t( __in char * InStr, __out wchar_t * OutStrBuffer, __in int OutStrBufferSize){

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

bool Sharewchar_t_Char(__in wchar_t * InStr, __out char * OutStrBuffer, __in int OutStrBufferSize){

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



//负责创建供给其他端使用的构造函数)
ShareMemory::ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize){
	this->InitShareMemory(MutexName, ShareName, MemorySize);
}

//不负责创建(其他端负责创建时使用的构造函数)
ShareMemory::ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]){
	this->InitShareMemory(MutexName, ShareName);
}

//不负责创建(其他端负责创建时使用的构造函数)
ShareMemory::ShareMemory(_tagShareMemoryName InfoName){
	this->InitShareMemory((wchar_t *)InfoName.MutexName, (wchar_t *)InfoName.ShareName);
}
//负责创建供给其他端使用的构造函数)
ShareMemory::ShareMemory(_tagShareMemoryName InfoName, DWORD MemorySize){
	this->InitShareMemory((wchar_t *)InfoName.MutexName, (wchar_t *)InfoName.ShareName, MemorySize);
}


//不负责创建(其他端负责创建时使用的构造函数)
ShareMemory::ShareMemory(wchar_t ShareName[40]){
	wchar_t tMutexName[50] = { NULL };
	wchar_t tShareName[50] = { NULL };
	swprintf_s(tMutexName, 50, L"%s_Mutex", ShareName);
	swprintf_s(tShareName, 50, L"%s_Memory", ShareName);
	this->InitShareMemory(tMutexName, tShareName);
}
//负责创建供给其他端使用的构造函数)
ShareMemory::ShareMemory(wchar_t ShareName[40], DWORD MemorySize){
	wchar_t tMutexName[50] = { NULL };
	wchar_t tShareName[50] = { NULL };
	swprintf_s(tMutexName, 50, L"%s_Mutex", ShareName);
	swprintf_s(tShareName, 50, L"%s_Memory", ShareName);
	this->InitShareMemory(tMutexName, tShareName, MemorySize);
}


//不负责创建(其他端负责创建时使用的构造函数)
ShareMemory::ShareMemory(char MutexName[50], char ShareName[50]){
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	if (false == ShareChar_wchar_t(MutexName, tMutexName, 50)){
		return;
	}
	if (false == ShareChar_wchar_t(ShareName, tShareName, 50)){
		return;
	}
	this->InitShareMemory(tMutexName, tShareName);
}
//负责创建供给其他端使用的构造函数)
ShareMemory::ShareMemory(char MutexName[50], char ShareName[50], DWORD MemorySize){
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	if (false == ShareChar_wchar_t(MutexName, tMutexName, 50)){
		return;
	}
	if (false == ShareChar_wchar_t(ShareName, tShareName, 50)){
		return;
	}
	this->InitShareMemory(tMutexName, tShareName, MemorySize);
}

//不负责创建(其他端负责创建时使用的构造函数)
ShareMemory::ShareMemory(_tagShareMemoryNameA InfoName){
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	if (false == ShareChar_wchar_t((char*)InfoName.MutexName, tMutexName, 50)){
		return;
	}
	if (false == ShareChar_wchar_t((char*)InfoName.ShareName, tShareName, 50)){
		return;
	}
	this->InitShareMemory(tMutexName, tShareName);
}
//负责创建供给其他端使用的构造函数)
ShareMemory::ShareMemory(_tagShareMemoryNameA InfoName, DWORD MemorySize){
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	if (false == ShareChar_wchar_t((char*)InfoName.MutexName, tMutexName, 50)){
		return;
	}
	if (false == ShareChar_wchar_t((char*)InfoName.ShareName, tShareName, 50)){
		return;
	}
	this->InitShareMemory(tMutexName, tShareName, MemorySize);
}

ShareMemory::ShareMemory(){
	//内存的互斥
	ZeroMemory(this->MemoryMutexName, sizeof(wchar_t)* 55);
	//内存的名称
	ZeroMemory(this->MemoryName,sizeof(wchar_t) * 55);
	//内存文件句柄
	this->hMemoryFileMap = NULL;
	//内存文件句柄
	this->hMemoryMutex = NULL;
	//是否初始化 正常
	this->InitMemoryFisinh = FALSE;
}

//释放掉 所有的资源
ShareMemory::~ShareMemory(){
	this->DeleteShareMemory();
}


//不负责创建(其他端负责创建时使用的构造函数)
BOOL ShareMemory::InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]){
	if (TRUE == this->InitMemoryFisinh){ return TRUE; }

	if (NULL == MutexName || 50 < wcslen(MutexName) || NULL == ShareName || 50 < wcslen(ShareName)){
		return FALSE;
	}
	//http://baike.baidu.com/link?url=Ttq0mzWS_NsjsuOfueS5vqPy9KTEhmliT5xvHP7_1IZzlBxHbI8T2Q4gccmCp0fyuf7koIV6LCriOpSFamBkZ_
	this->hMemoryFileMap = OpenFileMappingW(FILE_MAP_ALL_ACCESS, false, ShareName);
	if (NULL == this->hMemoryFileMap){ return FALSE; }

	//http://baike.baidu.com/link?url=lIcZ2Pv0SGo1oP-zzzwpq1F2XOwXpAQu6KlhbSdpCffosayFjvuO0v4GBzNKz0W5VIkYFmSI_9OqVECn4kpioa
	this->hMemoryMutex = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, MutexName);
	if (NULL == this->hMemoryMutex){ goto GoToError; }

	this->InitMemoryFisinh = TRUE;
	CopyMemory(this->MemoryMutexName, MutexName, wcslen(MutexName) * sizeof(wchar_t)+sizeof(wchar_t));
	CopyMemory(this->MemoryName, ShareName, wcslen(ShareName) * sizeof(wchar_t)+sizeof(wchar_t));

	return TRUE;
GoToError:
	if (NULL != this->hMemoryFileMap){ CloseHandle(this->hMemoryFileMap); this->hMemoryFileMap = NULL; }
	if (NULL != this->hMemoryMutex){ CloseHandle(this->hMemoryMutex); this->hMemoryMutex = NULL; }
	return FALSE;
}

//负责创建供给其他端使用的构造函数)
BOOL ShareMemory::InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize){
	if (TRUE == this->InitMemoryFisinh || NULL == MemorySize){ return FALSE; }

	if (NULL == MutexName || 50 < wcslen(MutexName) || NULL == ShareName || 50 < wcslen(ShareName) || NULL >= MemorySize){
		return FALSE;
	}
	std::shared_ptr<byte> nopBuffer(new byte[MemorySize]);
	ZeroMemory(nopBuffer.get(), sizeof(byte)* MemorySize);

	//http://baike.baidu.com/link?url=EcRFOWE6MJ6aaHGMQcwNlQmh9TU5LUV26CLnZzXM7ex98eUGlYOXuJ8bbePhvT37A7s2alwIyUrqKPZNbIA-MK
	this->hMemoryFileMap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MemorySize, ShareName);
	if (NULL == this->hMemoryFileMap){ goto GoToError; }
	if (ERROR_ALREADY_EXISTS == GetLastError()){ goto GoToError; } //检测是不是之前已经创建

	//http://baike.baidu.com/link?url=ugCeO5xCBjPpNYxMva4XjEYK8Oam79pTDIP3U6RH1WkmT2tIjFrhgWtxgBR-_p7Cg0By5mQGLGoe78MwlF-Y7_
	this->hMemoryMutex = CreateMutexW(NULL, FALSE, MutexName);
	if (NULL == this->hMemoryMutex){ goto GoToError; }

	this->InitMemoryFisinh = TRUE;

	CopyMemory(this->MemoryMutexName, MutexName, wcslen(MutexName) * sizeof(wchar_t)+sizeof(wchar_t));
	CopyMemory(this->MemoryName, ShareName, wcslen(ShareName) * sizeof(wchar_t)+sizeof(wchar_t));

	//下面 清除内存为空
	this->WriteMemory(nopBuffer.get(), sizeof(byte)* MemorySize);
	return TRUE;
GoToError:
	if (NULL != this->hMemoryFileMap){ CloseHandle(this->hMemoryFileMap); this->hMemoryFileMap = NULL; }
	if (NULL != this->hMemoryMutex){ CloseHandle(this->hMemoryMutex); this->hMemoryMutex = NULL; }
	return FALSE;
}


//不负责创建(其他端负责创建时使用的构造函数)
BOOL ShareMemory::InitShareMemory(wchar_t ShareName[40]){
	wchar_t tMutexName[50] = { NULL };
	wchar_t tShareName[50] = { NULL };
	swprintf_s(tMutexName, 50, L"%s_Mutex", ShareName);
	swprintf_s(tShareName, 50, L"%s_Memory", ShareName);
	return this->InitShareMemory(tMutexName, tShareName);
}

//负责创建供给其他端使用的构造函数)
BOOL ShareMemory::InitShareMemory(wchar_t ShareName[40], DWORD MemorySize){
	wchar_t tMutexName[50] = { NULL };
	wchar_t tShareName[50] = { NULL };
	swprintf_s(tMutexName, 50, L"%s_Mutex", ShareName);
	swprintf_s(tShareName, 50, L"%s_Memory", ShareName);
	return this->InitShareMemory(tMutexName, tShareName, MemorySize);
}

//不负责创建(其他端负责创建时使用的构造函数)
BOOL ShareMemory::InitShareMemory(DWORD ShareType, DWORD64 ShareMark){
	if (TRUE == this->InitMemoryFisinh){ return TRUE; }
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	//DWORD  %08X 整数型范围最多8位字符       DWORD64  %llu 64位整数型最大长度为 20位字符   
	swprintf_s(tMutexName, 50, L"ShareMutex_%08X_%llu", ShareType, ShareMark);
	swprintf_s(tShareName, 50, L"ShareMemoryName_%08X_%llu", ShareType, ShareMark);
	return this->InitShareMemory(tMutexName, tShareName);
}

//负责创建供给其他端使用的构造函数)
BOOL ShareMemory::InitShareMemory(DWORD ShareType, DWORD64 ShareMark, DWORD MemorySize){
	if (TRUE == this->InitMemoryFisinh || NULL == MemorySize){ return this->InitMemoryFisinh; }
	wchar_t tMutexName[55] = { NULL };
	wchar_t tShareName[55] = { NULL };
	//DWORD  %08X 整数型范围最多8位字符       DWORD64  %llu 64位整数型最大长度为 20位字符   
	swprintf_s(tMutexName, 50, L"ShareMutex_%08X_%llu", ShareType, ShareMark);
	swprintf_s(tShareName, 50, L"ShareMemoryName_%08X_%llu", ShareType, ShareMark);

	return this->InitShareMemory(tMutexName, tShareName, MemorySize);
}

//清除 全局内存  用于后期重复使用
BOOL ShareMemory::DeleteShareMemory(){
	if (NULL != this->hMemoryFileMap){ CloseHandle(this->hMemoryFileMap); this->hMemoryFileMap = NULL; }
	if (NULL != this->hMemoryMutex){ CloseHandle(this->hMemoryMutex); this->hMemoryMutex = NULL; }
	ZeroMemory(this->MemoryMutexName, sizeof(wchar_t)* 55);
	ZeroMemory(this->MemoryName, sizeof(wchar_t)* 55);
	this->InitMemoryFisinh = FALSE;
	return TRUE;
}

//读取一个内存
BOOL ShareMemory::ReadMemory(__out void * outinfo, __in DWORD ReadSize){
	if (FALSE == this->InitMemoryFisinh){ return FALSE; }

	WaitForSingleObject(this->hMemoryMutex, INFINITE);//进入 互斥体

	LPVOID lpMapAddress = MapViewOfFile(this->hMemoryFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (NULL == lpMapAddress){ goto GoToError; }

	__try{
		CopyMemory(outinfo, lpMapAddress, ReadSize);
	}__except (EXCEPTION_EXECUTE_HANDLER){ goto GoToError; }

	ReleaseMutex(this->hMemoryMutex);//退出 互斥体 
	return TRUE;
GoToError:
	ReleaseMutex(this->hMemoryMutex);//退出 互斥体  
	return FALSE;
}

//写入一个内存
BOOL ShareMemory::WriteMemory(__in void * ininfo, __in DWORD WriteSize){
	if (FALSE == this->InitMemoryFisinh || NULL == ininfo || NULL == WriteSize){ return FALSE; }

	WaitForSingleObject(this->hMemoryMutex, INFINITE);//进入 互斥体

	LPVOID lpMapAddress = MapViewOfFile(this->hMemoryFileMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (NULL == lpMapAddress){ goto GoToError; }

	__try{
		CopyMemory(lpMapAddress, ininfo, WriteSize);
		if (FALSE == UnmapViewOfFile(lpMapAddress)){
			goto GoToError;
		}
	}__except (EXCEPTION_EXECUTE_HANDLER){ goto GoToError; }

	ReleaseMutex(this->hMemoryMutex);//退出 互斥体 
	return TRUE;
GoToError:
	ReleaseMutex(this->hMemoryMutex);//退出 互斥体  
	return FALSE;
}

//读取状态,检测是否已经成功创建
BOOL ShareMemory::CreateFisinh(){
	return this->InitMemoryFisinh;
}


