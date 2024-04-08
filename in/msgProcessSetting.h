#pragma once
namespace msgProcessSetting
{ 
	void applyEncryptedKey(jValue args, jValue& result, std::string& errString, uint32_t& errCode);
	 
	void regProcess(std::map<std::string, callbackMsgEvent>& mapProcess);


};

