// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"

BOOL     gInstallStatusSuccess = FALSE;   //�Ƿ��Ѿ���ʼ�����
HMODULE  gCurrentModuleHandle = NULL;    //��ǰģ��� ģ����


//��ǰע����������
CRegedit gCurrentRegeditObject(HKEY_CURRENT_USER, "SOFTWARE\\MainConsole");

//����̨�����·��
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


//��ȡ��ǰ���̵� ��������
char     gCurrentProcessName[1024] = { NULL };
char * ReadCurrentProcessNameString(){
	if ('\0' != gCurrentProcessName[0]){ return gCurrentProcessName; }

	DWORD   tCurrentProcessPid = GetCurrentProcessId(); //�õ� ������� pid

	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);//���� ���̿���
	PROCESSENTRY32 tProcessInfo = { NULL };//���̽ṹ
	tProcessInfo.dwSize = sizeof(PROCESSENTRY32);//����������ȳ�ʼ������ô���޷�ʹ�ã�GetLastEroor()����24����
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

//�Ա� �ַ��� �Ƿ�Ϊ��ͬ��
#define wcsicmpex(str,strex)       (BOOL)(wcslen(str) == wcslen(strex) && 0 == _wcsicmp(str,strex))      
#define stricmpex(str,strex)       (BOOL)(NULL != str && NULL != strex && strlen(str) == strlen(strex) && 0 == _stricmp(str,strex))   

#define EnterProcessName(str)      (BOOL)stricmpex(ReadCurrentProcessNameString(), str)




//ģ��ж�غ���
DWORD WINAPI Thread_QuitCurrentDllcallback(PVOID param){
	FreeLibraryAndExitThread(gCurrentModuleHandle, NULL);
}

//����һ�� ��� dll , ��� dll ���������Ĺ��� dll
void LoadPluginLibrary(const char * pname){
	char  tPluginLibrarypath[1024] = { NULL };
	sprintf_s(tPluginLibrarypath, 1024, "%s%s", ReadMainConsoleRootPathString(), pname);

	HMODULE tPluginLibraryModule = LoadLibraryA(tPluginLibrarypath);
	if (NULL != tPluginLibraryModule){ return; }

	Outputlog tOutputObject("%sMainLog.log", ReadMainConsoleRootPathString());
	if (FALSE == tOutputObject.Getopenstatus()){ return; }

	const char * pProcessName = ReadCurrentProcessNameString();
	const char * pCommandLine = GetCommandLineA();

	tOutputObject.OutputlogByFormat("���ز��, 0x%08X, ģ�� = %s \r\n                �������Ϊ = 0x%08X, �������� = %s, ������ = %s",
		tPluginLibraryModule,
		tPluginLibrarypath,
		GetLastError(),
		pProcessName,
		pCommandLine
		);
}

//���� ��չ��� dll
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

			LoadPluginLibrary(_pathString);  //���� dll
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
	tOutputObject.OutputlogByFormat("�������� = %-40s, ���������� = %s", pProcessName, pCommandLine);
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
			if (std::string::npos != ReadStartPathString().find(ģ��_STeam��Ϸ������)) {
				OutputCommandLineString();
			}
			if (TRUE == EnterProcessName(ģ��_STeam��Ϸ������)){
				LoadPluginLibrary(ģ��_�ػ�����������);
				LoadEPluginLibrary(STR_PLUGINCATALOG);
			}
		}
		CreateThread(NULL, 0, Thread_QuitCurrentDllcallback, NULL, 0, NULL); //�� ����ģ��ж�ص�
	}
	return TRUE;
}

