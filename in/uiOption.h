#pragma once
#include "msgDef.h" 

namespace uiOption
{
	//���ҿؼ�  ���� + {����:ֵ}
	void findControl(jValue args, jValue& result, std::string& errString, uint32_t& errCode);

	//���ݿؼ�ָ���ȡ����  ָ�� + ������
	void getControlProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode);

	void getControlFullProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode);
	 
	void regProcess(std::map<std::string, callbackMsgEvent>& mapProcess);

};

