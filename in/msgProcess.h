#pragma once
#include <json/json.h>




namespace msgProcess {

	std::string msgEventProcess(Json::Value msg, UINT64 sendTime);



	//ע����Ϣ����
	bool regMsgProcess();


}