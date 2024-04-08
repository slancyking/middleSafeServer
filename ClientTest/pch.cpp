// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include "Tlhelp32.h"
//ServerApi  safeServer("3A077E34-5F72-90E4-61C2-523F25A5A6CA","http://mss.slancyking.xyz:44367");
ServerApi  safeServer("3A07C004-8992-1DC2-C2CE-25C65D2338F6", "http://mss.d4d.top:44367");

 

std::string rand_str(const int len)  /*参数为字符串的长度*/
{
    /*初始化*/
    std::string str;                 /*声明用来保存随机字符串的str*/
    char c;                     /*声明字符c，用来保存随机生成的字符*/
    int idx;                    /*用来循环的变量*/
    char t;                     
    /*循环向字符串中添加随机生成的字符*/
    for (idx = 0; idx < len; idx++)
    {
        t = rand() % 62; 
        if (t < 10)
            c = '0' + rand() % 10;
        else if (t < 36)
            c = 'a' + rand() % 26;
        else
            c = 'A' + rand() % 26; 
        str.push_back(c);
    }
    return str;
}


//回调处理
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	//if (data.process_id != process_id || !IsMainWindow(handle)) 
	if (data.process_id != process_id)
	{
		return TRUE;
	}
	data.best_handle = handle;
	return FALSE;
}

HWND FindMainWindow(unsigned long process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.best_handle = 0;
	::EnumWindows(EnumWindowsCallback, (LPARAM)&data);
	return data.best_handle;
}


vector<DWORD> FindProcessByName(string processName) {
	vector<DWORD> result;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hSnapshot)
		return result;
	PROCESSENTRY32 pi;
	pi.dwSize = sizeof(PROCESSENTRY32); //第一次使用必须初始化成员
	BOOL bRet = Process32First(hSnapshot, &pi);
	while (bRet)
	{
		/*
		循环遍历添加自己的额外代码
		*/
		if (processName == string(CT2A(pi.szExeFile))) 
			result.push_back(pi.th32ProcessID);

		bRet = Process32Next(hSnapshot, &pi);
	}
	return result;
}



std::string getAppPath() { 
	char ModuleFileName[_MAX_PATH];
	GetModuleFileNameA(NULL, ModuleFileName, _MAX_PATH);
	char ExePath[_MAX_DIR];           //当前文件夹
	char ExtName[_MAX_EXT];           //文件后缀
	char ExeFName[_MAX_FNAME];        //文件名
	char ExeDiver[_MAX_DRIVE];        //文件驱动器，如C:
	_splitpath_s(ModuleFileName, ExeDiver, ExePath, ExeFName, ExtName);
	std::string result = std::format("{}{}", ExeDiver, ExePath);
	return result;
}

