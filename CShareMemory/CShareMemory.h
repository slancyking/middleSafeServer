#pragma once

#include <Windows.h>



struct _tagShareMemoryName{
	const wchar_t  * MutexName;  //互斥名称
	const wchar_t  * ShareName;  //全局内存名称
};

struct _tagShareMemoryNameA{
	const char  * MutexName;  //互斥名称
	const char  * ShareName;  //全局内存名称
};

class ShareMemory{
public://构造函数

	//不负责创建(其他端负责创建时使用的构造函数)
	ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]);
	//负责创建供给其他端使用的构造函数)
	ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize);
	
	//不负责创建(其他端负责创建时使用的构造函数)
	ShareMemory(_tagShareMemoryName InfoName);
	//负责创建供给其他端使用的构造函数)
	ShareMemory(_tagShareMemoryName InfoName, DWORD MemorySize);

	//不负责创建(其他端负责创建时使用的构造函数)
	ShareMemory(wchar_t ShareName[40]);
	//负责创建供给其他端使用的构造函数)
	ShareMemory(wchar_t ShareName[40], DWORD MemorySize);

	//不负责创建(其他端负责创建时使用的构造函数)
	ShareMemory(char MutexName[50], char ShareName[50]);
	//负责创建供给其他端使用的构造函数)
	ShareMemory(char MutexName[50], char ShareName[50], DWORD MemorySize);

	//不负责创建(其他端负责创建时使用的构造函数)
	ShareMemory(_tagShareMemoryNameA InfoName);
	//负责创建供给其他端使用的构造函数)
	ShareMemory(_tagShareMemoryNameA InfoName, DWORD MemorySize);

	ShareMemory();
	~ShareMemory();


public://一些特殊情况下,使用的 初始化函数

	//不负责创建(其他端负责创建时使用的构造函数)
	BOOL InitShareMemory(wchar_t ShareName[40]);
	//负责创建供给其他端使用的构造函数)
	BOOL InitShareMemory(wchar_t ShareName[40], DWORD MemorySize);

	//不负责创建(其他端负责创建时使用的构造函数)
	BOOL InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]);
	//负责创建供给其他端使用的构造函数)
	BOOL InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize);

	//不负责创建(其他端负责创建时使用的构造函数)
	BOOL InitShareMemory(DWORD ShareType, DWORD64 ShareMark);
	//负责创建供给其他端使用的构造函数)
	BOOL InitShareMemory(DWORD ShareType, DWORD64 ShareMark, DWORD MemorySize);

	//清除 全局内存  用于后期重复使用
	BOOL DeleteShareMemory();

	//读取状态,检测是否已经成功创建
	BOOL CreateFisinh();
public://读写函数

	//读取一个内存
	BOOL ReadMemory(__out void * outinfo, __in DWORD ReadSize);
	//写入一个内存
	BOOL WriteMemory(__in void * ininfo, __in DWORD WriteSize);

private:
	//内存的互斥
	wchar_t MemoryMutexName[55];
	//内存的名称
	wchar_t MemoryName[55];
	//内存文件句柄
	HANDLE hMemoryFileMap = NULL;
	//内存文件句柄
	HANDLE hMemoryMutex = NULL;
	//是否初始化 正常
	BOOL  InitMemoryFisinh = FALSE;
};

