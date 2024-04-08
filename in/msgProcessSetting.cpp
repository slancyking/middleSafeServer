#include "msgDef.h"
#include "msgProcessSetting.h"
#include "pch.h"
#include "serverProc.h"
 

void msgProcessSetting::applyEncryptedKey(jValue args, jValue& result, std::string& errString, uint32_t& errCode)
{
	serverProc::xKey = serverProc::tmpRanKey;
	result["success"] = true;
}





void msgProcessSetting::regProcess(std::map<std::string, callbackMsgEvent>& mapProcess)
{ 
	mapProcess.insert(std::pair<std::string, callbackMsgEvent>("applyEncryptedKey", applyEncryptedKey)); //”¶”√º”√‹√ÿ‘ø
}
