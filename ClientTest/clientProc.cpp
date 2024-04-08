#include "pch.h"
#include "clientProc.h" 
//#include "../lib_json/json.h"

#include "msgProtocol.h" 


bool clientProc::init()
{
	if (false == mClient->connect("127.0.0.1", mServerPort))
		return false;
	 
	return ping(); 
}

bool clientProc::ping()
{
	jValue retMsg = sendMsg(MSG_PING);
	if (retMsg.isNull())
		return false;

	if (retMsg["errorCode"].isNumeric() && retMsg["errorCode"].asInt() != 0)
	{
		OutputDebugStringA(format("ÏûÏ¢´íÎó´úÂë:{}  ,´íÎóÄÚÈÝ:{}", retMsg["errorCode"].asInt(), retMsg["errorString"].asString()).c_str());
	}

	if (retMsg["result"].isObject() && retMsg["result"]["keyIndex"].isNumeric()) {
		return updateKey(retMsg["result"]["pid"].asInt(),retMsg["result"]["keyIndex"].asInt());
	}

	return true;
}

bool clientProc::updateKey(int pId,int kIndex)
{
	tagServerReportResponse clientInfo = safeServer.normalQuery(format("{}", pId));
	if (clientInfo.result.code != 0) {
		OutputDebugStringA(format("¸üÐÂÃØÔ¿´íÎó:{}  ,´íÎóÄÚÈÝ:{}", clientInfo.result.code, clientInfo.result.info).c_str());
		return false;
	}
	if (clientInfo.report.keyIndex != kIndex) {
		OutputDebugStringA(format("ÃØÔ¿Ë÷ÒýÒì³£:{}  ,´íÎóÄÚÈÝ:{}", clientInfo.report.keyIndex, kIndex).c_str());
		return false;
	}

	
	 
	jValue retMsg = sendMsg("applyEncryptedKey",jValue::null, clientInfo.report.randomKey);
	if (retMsg.isNull())
		return false;

	if (retMsg["errorCode"].isNumeric() && retMsg["errorCode"].asInt() != 0)
	{
		OutputDebugStringA(format("ÏûÏ¢´íÎó´úÂë:{}  ,´íÎóÄÚÈÝ:{}", retMsg["errorCode"].asInt(), retMsg["errorString"].asString()).c_str());
		return false;
	}
	  

	return true;


}

std::string clientProc::sendMsgByString(std::string styleJsonString, std::string changeKey)
{


	sendMsgProtocol encryptedMsg(styleJsonString, mKey);

	UINT dSize = 0;
	void* data = encryptedMsg.getData(dSize);

	lockSendMsg.OpenRejection();

	if (!mClient->XSend((BYTE*)data, dSize, 1000)) {
		lockSendMsg.CloseRejection();
		return "";
	}
		

	data = mClient->XRecv(dSize, 1000);
	if (NULL == data || dSize <= 0)
	{
		lockSendMsg.CloseRejection();
		return "";
	}

	recvMsgProtocol recvMsg(data, dSize);
	lockSendMsg.CloseRejection();

	if (!changeKey.empty())
		mKey = changeKey;

	std::string strMsg = recvMsg.getMsg(mKey);

	return strMsg;
}

jValue clientProc::sendMsg(std::string msgID, jValue msgArgs, std::string changeKey)
{
	jValue rMsg;
	rMsg["msgID"] = msgID.c_str();
	rMsg["args"] = msgArgs; 
	std::string strMsg = sendMsgByString(rMsg.toStyledString(), changeKey);
	jReader _reader;
	jValue _root;
	if (false == _reader.parse(strMsg, _root, false)) 
		return jValue::null;

	if (!_root["finishTime"].isNumeric() ||  _root["finishTime"].asInt() <= std::time(0) - msgTimeout) {
		return jValue::null;
	}
	 
	return _root;
}

clientProc::clientProc(unsigned short port, std::string gKey)
{
	mServerPort = port;
	mKey = gKey;

	mClient = new CSocketClient();
}

clientProc::~clientProc()
{
	if (mClient != NULL) 
		delete mClient;

}
