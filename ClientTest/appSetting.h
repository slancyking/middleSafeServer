#pragma once

 

class appSetting
{
	struct tagAppSetting
	{ 
		WCHAR dllFile[MAX_PATH] = { NULL };				//dll·��
		WCHAR targetProcessName[_MAX_FNAME] = { NULL };	//Ŀ����� ��
		WCHAR processDescription[512] = { NULL };		//Ŀ����� ����
		bool  autoInject = false;						//�Զ�ע�� 
	};
	 
	 
public: 
	appSetting();
	~appSetting();
	tagAppSetting mAppSetting;


	void loadSetting();
	void saveSettiang();



};

