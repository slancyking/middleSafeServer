#include "pch.h"
#include "msgProcess.h"
#include "msgDef.h"
#include "serverProc.h"
#include "msgProcessSetting.h"
#include "uiOption.h"

// 请求参数:
// {
//	    "msgID":"ping",
//		"time":1650372911,
//		"args":null
// 
// }
//
// 返回结果:
// {
//      "msgID":"ping",    --消息id
//		"time":1650372911, --请求时间
//		"finishTime":      --完成时间
//		"args":{},         --参数表
//		"result":{},       --执行结果表
//		"errorCode":0,     --异常代码
//	    "errorString":""   --异常描述
// }
//
//
 
std::map<std::string, callbackMsgEvent> mapEventCallback;


std::string msgProcess::msgEventProcess(Json::Value msg,UINT64 sendTime)
{
	UINT errorCode = 0;
	std::string errorString = "";
	
	jValue msgID = msg["msgID"]; 
	jValue args = msg["args"];
	jValue result;
	std::string strMsgEventId;
	std::map<std::string, callbackMsgEvent>::iterator  proc;
	//检测操作时间 
	//消息超时
	if (std::time(0) > sendTime + 60) {
		errorCode = MSG_ERROR_ID_ErrTime;
		errorString = MSG_ERROR_DES_ErrTime;
		goto gotoReturn;
	}

	//检测消息id
	if (!msgID.isString()) {
		errorCode = MSG_ERROR_ID_NOTID;
		errorString = MSG_ERROR_DES_NOTID;
		goto gotoReturn;
	}

	if (msgID.asString() == MSG_PING)
	{
		if (std::time(0) - serverProc::lastRenKeyTime > 10 
			&& serverProc::tmpRanKey != "" && serverProc::tmpRanKey != serverProc::xKey
			) { 
			result["pid"] = (int)GetCurrentProcessId();
			result["keyIndex"] = serverProc::tmpKeyIndex;
		} 

		goto gotoReturn;
	}
	else {
		strMsgEventId = msgID.asString();

		proc = mapEventCallback.find(strMsgEventId);
		if (proc == mapEventCallback.end()) {
			errorCode = MSG_ERROR_ID_NOT_ID_EVNT;
			errorString = MSG_ERROR_DES_NOT_ID_EVNT;
			goto gotoReturn;
		}
		proc->second(args, result, errorString, errorCode);
		
	}

gotoReturn:
	msg["errorCode"] = errorCode;
	msg["errorString"] = errorString; 
	msg["finishTime"] = (UINT)std::time(0);
	msg["result"] = result;
	return msg.toStyledString();
}

bool msgProcess::regMsgProcess()
{

	msgProcessSetting::regProcess(mapEventCallback);
	uiOption::regProcess(mapEventCallback);

	return true;
}
