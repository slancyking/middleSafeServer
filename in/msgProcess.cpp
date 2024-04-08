#include "pch.h"
#include "msgProcess.h"
#include "msgDef.h"
#include "serverProc.h"
#include "msgProcessSetting.h"
#include "uiOption.h"

// �������:
// {
//	    "msgID":"ping",
//		"time":1650372911,
//		"args":null
// 
// }
//
// ���ؽ��:
// {
//      "msgID":"ping",    --��Ϣid
//		"time":1650372911, --����ʱ��
//		"finishTime":      --���ʱ��
//		"args":{},         --������
//		"result":{},       --ִ�н����
//		"errorCode":0,     --�쳣����
//	    "errorString":""   --�쳣����
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
	//������ʱ�� 
	//��Ϣ��ʱ
	if (std::time(0) > sendTime + 60) {
		errorCode = MSG_ERROR_ID_ErrTime;
		errorString = MSG_ERROR_DES_ErrTime;
		goto gotoReturn;
	}

	//�����Ϣid
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
