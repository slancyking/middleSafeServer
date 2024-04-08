#include "pch.h"
#include "inject.h"
#include "../CRegedit/CRegedit.h"

const char* inject::ReadAppInit_DLLs_x64PathString()
{
	static char tAppInit_DLLs_x64PathBuffer[1024] = { NULL };
	if ('\0' != tAppInit_DLLs_x64PathBuffer[0]) { return tAppInit_DLLs_x64PathBuffer; }

	char tSpecialPathBuffer[MAX_PATH] = { NULL };
	if (FALSE == SHGetSpecialFolderPathA(NULL, tSpecialPathBuffer, CSIDL_WINDOWS, FALSE)) {
		return "#异常#， 获取系统WINDOWS目录失败.";
	}

	ZeroMemory(tAppInit_DLLs_x64PathBuffer, sizeof(char) * 1024);
	wsprintfA(tAppInit_DLLs_x64PathBuffer, "%s\\%s", tSpecialPathBuffer, "AppInit_DLLs_x64.dll");
	return tAppInit_DLLs_x64PathBuffer;
}

bool inject::regInject()
{
	//将当前的辅助环境, 写入到注册表中
	CRegedit tReg_MainConsole(HKEY_CURRENT_USER, (char*)"SOFTWARE\\MainConsole");

	std::string pathString = getAppPath();

	tReg_MainConsole.SetItemData((char*)"rootPath", REG_SZ, (void*)pathString.c_str(), pathString.length());

	//if (NULL == GetCommandLineA() || (NULL == strstr(GetCommandLineA(), "start") && NULL == strstr(GetCommandLineA(), "end"))) {
	//	return ShowError("启动参数异常, 禁止手动启动当前辅助程序...\r\n", GetLastError());
	//}
	BOOL     tLoadAppInit_DLLsStatus = TRUE;
	BOOL     tRequireSignedAppInit_DLLsStatus = FALSE;
	CRegedit tReg_AppInit_DLLs_x64(HKEY_LOCAL_MACHINE, (char*)"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows");



	const char* pAppInit_DLLsPathString = "";

	if (FALSE == PathFileExistsA(pAppInit_DLLsPathString = ReadAppInit_DLLs_x64PathString())) {
		return false;
	}

	if (FALSE == tReg_AppInit_DLLs_x64.SetItemData((char*)"AppInit_DLLs", REG_SZ, (VOID*)pAppInit_DLLsPathString, (DWORD)strlen(pAppInit_DLLsPathString) * sizeof(char))) {
		return false;
	}

	if (FALSE == tReg_AppInit_DLLs_x64.SetItemData((char*)"RequireSignedAppInit_DLLs", REG_DWORD, &tRequireSignedAppInit_DLLsStatus, sizeof(BOOL))) {
		return false;
	}

	tLoadAppInit_DLLsStatus = TRUE;
	if (FALSE == tReg_AppInit_DLLs_x64.SetItemData((char*)"LoadAppInit_DLLs", REG_DWORD, &tLoadAppInit_DLLsStatus, sizeof(BOOL))) {
		return false;
	} 
	return true;
}

bool inject::regUnInject()
{
	CRegedit tReg_AppInit_DLLs_x64(HKEY_LOCAL_MACHINE, (char*)"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows");
	BOOL tLoadAppInit_DLLsStatus = FALSE;		  //设置 结束加载 dll
	if (FALSE == tReg_AppInit_DLLs_x64.SetItemData((char*)"LoadAppInit_DLLs", REG_DWORD, &tLoadAppInit_DLLsStatus, sizeof(BOOL))) {
		return false;
	}
	return true;
}

