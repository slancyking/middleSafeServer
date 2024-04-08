#include "pch.h"
#include "appSetting.h"
#include <io.h>
#include <fstream>

using namespace std;

appSetting* gInstance = NULL;
  
appSetting::appSetting()
{
	loadSetting();
}

appSetting::~appSetting()
{
	saveSettiang();
}

void appSetting::loadSetting()
{
	string setPath = getAppPath() + "ct.setting";
	if (_access(setPath.c_str(), 0) == -1) 
		return;

	FILE* pClientFile = NULL;
	fopen_s(&pClientFile, setPath.c_str(), "r");

	if (NULL == pClientFile)
		return;

	fseek(pClientFile, 0, SEEK_END);
	long ret = ftell(pClientFile);

	if (ret != sizeof(tagAppSetting))
	{
		fclose(pClientFile);
		return;
	}
	fseek(pClientFile, 0, SEEK_SET);
	if (0 >= fread(&mAppSetting, sizeof(tagAppSetting), 1, pClientFile)) {
		OutputDebugString(L"¶Á ct.setting ÎÄ¼þÒì³£!");
	}

	fclose(pClientFile); 
}

void appSetting::saveSettiang()
{
	string setPath = getAppPath() + "ct.setting"; 
	ofstream outFile(setPath, ios::out | ios::binary);  
	outFile.write((char*)&mAppSetting, sizeof(tagAppSetting));
	outFile.close(); 
}
 
