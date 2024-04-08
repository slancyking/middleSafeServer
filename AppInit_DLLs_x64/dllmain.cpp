// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL     gInstallStatusSuccess = FALSE;   //是否已经初始化完毕
HMODULE  gCurrentModuleHandle = NULL;    //当前模块的 模块句柄


//当前注册表操作对象
CRegedit gCurrentRegeditObject(HKEY_CURRENT_USER, "SOFTWARE\\MainConsole");

//主控台程序根路径
char     gCurrentConsoleRoot[1024] = { NULL };

char * ReadMainConsoleRootPathString(){
	if ('\0' != gCurrentConsoleRoot[0]){ return gCurrentConsoleRoot; }

	DWORD tBufferSize = 1024;
	ZeroMemory(gCurrentConsoleRoot, sizeof(char) * 1024);
	if (FALSE == gCurrentRegeditObject.GetItemData("rootPath", (BYTE *)gCurrentConsoleRoot, &tBufferSize) || NULL == tBufferSize){
		return NULL;
	}

	return gCurrentConsoleRoot;
}


//获取当前进程的 进程名称
char     gCurrentProcessName[1024] = { NULL };
char * ReadCurrentProcessNameString(){
	if ('\0' != gCurrentProcessName[0]){ return gCurrentProcessName; }

	DWORD   tCurrentProcessPid = GetCurrentProcessId(); //得到 自身进程 pid

	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);//创建 进程快照
	PROCESSENTRY32 tProcessInfo = { NULL };//进程结构
	tProcessInfo.dwSize = sizeof(PROCESSENTRY32);//如果不做长度初始化，那么将无法使用，GetLastEroor()返回24错误
	if (INVALID_HANDLE_VALUE != hProcessSnapshot && TRUE == Process32First(hProcessSnapshot, &tProcessInfo)){
		do
		{
			if (tProcessInfo.th32ProcessID != tCurrentProcessPid){
				continue;
			}
			wsprintfA(gCurrentProcessName, tProcessInfo.szExeFile);
			break;
		} while (TRUE == Process32Next(hProcessSnapshot, &tProcessInfo));
	}
	CloseHandle(hProcessSnapshot);
	if ('\0' != gCurrentProcessName[0]){ return gCurrentProcessName; }
	return NULL;
}


void OutputString(char * informatString, ...){

	char     tOutputStringBuffer[1024] = { NULL };

	va_list args;
	va_start(args, informatString);
	vsprintf_s(tOutputStringBuffer, 1024, informatString, args); // C4996
	va_end(args);

	OutputDebugStringA(tOutputStringBuffer);

	return;
}

//对比 字符串 是否为相同的
#define wcsicmpex(str,strex)       (BOOL)(wcslen(str) == wcslen(strex) && 0 == _wcsicmp(str,strex))      
#define stricmpex(str,strex)       (BOOL)(NULL != str && NULL != strex && strlen(str) == strlen(strex) && 0 == _stricmp(str,strex))   

#define EnterProcessName(str)      (BOOL)stricmpex(ReadCurrentProcessNameString(), str)




//模块卸载函数
DWORD WINAPI Thread_QuitCurrentDllcallback(PVOID param){
	FreeLibraryAndExitThread(gCurrentModuleHandle, NULL);
}

//加载一个 插件 dll , 这个 dll 才是真正的功能 dll
void LoadPluginLibrary(const char * pname){
	char  tPluginLibrarypath[1024] = { NULL };
	sprintf_s(tPluginLibrarypath, 1024, "%s%s", ReadMainConsoleRootPathString(), pname);

	HMODULE tPluginLibraryModule = LoadLibraryA(tPluginLibrarypath);
	if (NULL != tPluginLibraryModule){ return; }

	Outputlog tOutputObject("%sMainLog.log", ReadMainConsoleRootPathString());
	if (FALSE == tOutputObject.Getopenstatus()){ return; }

	const char * pProcessName = ReadCurrentProcessNameString();
	const char * pCommandLine = GetCommandLineA();

	tOutputObject.OutputlogByFormat("加载插件, 0x%08X, 模块 = %s \r\n                错误代码为 = 0x%08X, 进程名称 = %s, 命令行 = %s",
		tPluginLibraryModule,
		tPluginLibrarypath,
		GetLastError(),
		pProcessName,
		pCommandLine
		);
}

//加载 扩展插件 dll
void LoadEPluginLibrary(const char * catalogString) {
	char _pathString[MAX_PATH] = { NULL };

	strcat_s(_pathString, MAX_PATH, ReadMainConsoleRootPathString());
	strcat_s(_pathString, MAX_PATH, catalogString);
	strcat_s(_pathString, MAX_PATH, "*.dll");

	WIN32_FIND_DATA fileBuffer = { NULL };
	for (HANDLE hFile = ::FindFirstFile(_pathString, &fileBuffer); INVALID_HANDLE_VALUE != hFile;) {
		if (FILE_ATTRIBUTE_ARCHIVE == (fileBuffer.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE)) {
			memset(_pathString, 0, MAX_PATH);

			strcat_s(_pathString, MAX_PATH, catalogString);
			strcat_s(_pathString, MAX_PATH, fileBuffer.cFileName);

			LoadPluginLibrary(_pathString);  //加载 dll
		}
		if (FALSE == FindNextFile(hFile, &fileBuffer)) {
			FindClose(hFile);
			break;
		}
	}
}


void OutputCommandLineString(){
	const char * pProcessName = ReadCurrentProcessNameString();
	const char * pCommandLine = GetCommandLineA();

	if (NULL == pCommandLine) pCommandLine = "";

	if (NULL == pProcessName || NULL == pCommandLine){
		return;
	}

	Outputlog tOutputObject("%sCommandLine.log", ReadMainConsoleRootPathString());
	if (FALSE == tOutputObject.Getopenstatus()){ return; }
	tOutputObject.OutputlogByFormat("启动进程 = %-40s, 启动命令行 = %s", pProcessName, pCommandLine);
}

std::string ReadStartPathString() {
	TCHAR szPath[MAX_PATH] = { NULL };
	if (FALSE == GetModuleFileName(NULL, szPath, MAX_PATH)) {
		return "";
	}
	return szPath;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	if (ul_reason_for_call == DLL_PROCESS_ATTACH && FALSE == ::gInstallStatusSuccess){
		::gInstallStatusSuccess = TRUE;
		::gCurrentModuleHandle = hModule;

		if (NULL != ReadMainConsoleRootPathString() && NULL != ReadCurrentProcessNameString()){
			if (std::string::npos != ReadStartPathString().find(模块_STeam游戏主程序)) {
				OutputCommandLineString();
			}
			if (TRUE == EnterProcessName(模块_STeam游戏主程序)){
				LoadPluginLibrary(模块_守护进程主服务);
				LoadEPluginLibrary(STR_PLUGINCATALOG);
			}
		}
		CreateThread(NULL, 0, Thread_QuitCurrentDllcallback, NULL, 0, NULL); //将 自身模块卸载掉
	}
	return TRUE;
}

