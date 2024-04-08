#pragma once

#include "../CSocket/CSocket.h"
#include "msgDef.h"
#include "../CRejection/CRejection.h"

#include <string>

// 请求参数:
// {
//	    "msgID":"ping", 
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

#define msgTimeout 10

class clientProc
{

public:
	bool init();
	
	bool ping();

	bool updateKey(int pId,int kIndex);

	std::string sendMsgByString(std::string styleJsonString, std::string changeKey);

	jValue sendMsg(std::string msgID, jValue msgArgs = jValue::null, std::string changeKey = "");

	CRejection lockSendMsg;
	clientProc(unsigned short port, std::string gKey);
	~clientProc();
private:
	unsigned short mServerPort;
	std::string    mKey;
	CSocketClient*  mClient = NULL;
};

