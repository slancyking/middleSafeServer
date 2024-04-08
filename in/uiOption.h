#pragma once
#include "msgDef.h" 

namespace uiOption
{
	//查找控件  类型 + {属性:值}
	void findControl(jValue args, jValue& result, std::string& errString, uint32_t& errCode);

	//根据控件指针获取属性  指针 + 属性名
	void getControlProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode);

	void getControlFullProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode);
	 
	void regProcess(std::map<std::string, callbackMsgEvent>& mapProcess);

};

