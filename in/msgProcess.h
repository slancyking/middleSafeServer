#pragma once
#include <json/json.h>




namespace msgProcess {

	std::string msgEventProcess(Json::Value msg, UINT64 sendTime);



	//注册消息过程
	bool regMsgProcess();


}