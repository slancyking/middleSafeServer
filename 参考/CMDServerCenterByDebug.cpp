#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"
//
#include <functional>
//
#include <future>



extern HWND    _GAMESystemUI_HWND;
void CMD_DebugSendMessage(const JSONBuffer & args, JSONBuffer & retJson) {

	uint32 msg		= 0;
	WPARAM wParam	= 0; 
	LPARAM lParam	= 0;
	JSONArgsTry_Get(args, "msg"   , (int&)msg, NULL);
	JSONArgsTry_Get(args, "wParam", (int&)wParam, NULL);
	JSONArgsTry_Get(args, "lParam", (int&)lParam, NULL);

	LRESULT rValue = __CallSendMessage2Game(_GAMESystemUI_HWND, msg, wParam, lParam);

	JSONWriteValue(retJson, "code", rValue);
}

void CMD_TouchDurationPress(const JSONBuffer & args, JSONBuffer & retJson) {

	int kValue = 0;
	JSONArgsTry_Get(args, "kValue", kValue, 0);

	std::string kValueString = "";
	JSONArgsTry_Get(args, "kValue", kValueString, "");

	int dTime = 0;
	JSONArgsTry_Get(args, "dTime", (int&)dTime, NULL);

	if (0 != kValue && "" == kValueString) 
		TSTouchDurationPress(kValue, 
			dTime
		);

	if (0 == kValue && "" != kValueString)
		TSTouchDurationPress(kValueString.c_str(),
			dTime
		);

	JSONWriteValue(retJson, "time", dTime);
}

void CMD_DebugCmdString(const JSONBuffer & args, JSONBuffer & retJson) {
	











}

bool CMDSwitch_DistributionCenter_Debug(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //得到字符串 长度,

	if (strlen("debug_JSONString") == lenth_method && 0 == strcmp("debug_JSONString", method)) {
		CMD_DebugCmdString(args, retJson);
		return TRUE;
	}

	if (strlen("debug_SendMessage") == lenth_method && 0 == strcmp("debug_SendMessage", method)) {
		CMD_DebugSendMessage(args, retJson);
		return TRUE;
	}

	if (strlen("debug_TouchDurationPress") == lenth_method && 0 == strcmp("debug_TouchDurationPress", method)) {
		CMD_TouchDurationPress(args, retJson);
		return TRUE;
	}







	return false;
}






