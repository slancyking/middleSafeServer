// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include "times.h"
#include "xxtea.h"
#include <vector>


//# pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "rpcrt4.lib")

std::string rand_str(const int len); /*参数为字符串的长度*/



#define MSG_CLOSE_CLIENT (WM_USER + 0x100)
#define MSG_OPEN_CLIENT  (WM_USER + 0x101)
 
 

#include "ServerApi.h"

//进程id对应相应句柄结构
struct handle_data {
	unsigned long process_id;
	HWND best_handle;
};

//回调处理
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);

HWND FindMainWindow(unsigned long process_id);

std::string getAppPath();

//验证服务器
extern ServerApi  safeServer;


vector<DWORD> FindProcessByName(string processName);




#endif //PCH_H