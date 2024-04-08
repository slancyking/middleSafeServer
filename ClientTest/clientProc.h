#pragma once

#include "../CSocket/CSocket.h"
#include "msgDef.h"
#include "../CRejection/CRejection.h"

#include <string>

// �������:
// {
//	    "msgID":"ping", 
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

