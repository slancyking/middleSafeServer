#pragma once

 

class appSetting
{
	struct tagAppSetting
	{ 
		WCHAR dllFile[MAX_PATH] = { NULL };				//dll路径
		WCHAR targetProcessName[_MAX_FNAME] = { NULL };	//目标进程 名
		WCHAR processDescription[512] = { NULL };		//目标进程 描述
		bool  autoInject = false;						//自动注入 
	};
	 
	 
public: 
	appSetting();
	~appSetting();
	tagAppSetting mAppSetting;


	void loadSetting();
	void saveSettiang();



};

