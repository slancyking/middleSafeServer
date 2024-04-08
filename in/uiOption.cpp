#include "uiOption.h"

#include "pch.h"
#include "serverProc.h"
#include "UE4_UI.h"

void uiOption::findControl(jValue args, jValue& result, std::string& errString, uint32_t& errCode)
{
	PVOID rs = UE4_UI::findControl(args["SWidgetObject"].asString(), args);
	result["result"] = (int64)rs;
	result["success"] = true;
}

void uiOption::getControlProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode)
{
	string rs = UE4_UI::getControlProperty((PVOID)args["pObject"].asInt64(), args["type"].asString(), args["property"].asString());
	result["result"] = rs;
	result["success"] = true;
}

void uiOption::getControlFullProperty(jValue args, jValue& result, std::string& errString, uint32_t& errCode)
{
	string rs = UE4_UI::getControlFullProperty((PVOID)args["pObject"].asInt64(), args["type"].asString());
	result["result"] = rs;
	result["success"] = true;
}

void uiOption::regProcess(std::map<std::string, callbackMsgEvent>& mapProcess)
{
	mapProcess.insert(std::pair<std::string, callbackMsgEvent>("findControl", findControl)); //寻找控件
	mapProcess.insert(std::pair<std::string, callbackMsgEvent>("getControlProperty", getControlProperty)); //获取控件指定属性
	mapProcess.insert(std::pair<std::string, callbackMsgEvent>("getControlFullProperty", getControlFullProperty)); //获取控件所有属性

}
