#pragma once
#include "json/json.h"

 

#define MSG_PING "ping" 


#define MSG_ERROR_ID_NOTID       1  
#define MSG_ERROR_DES_NOTID      "��ʧ��Ϣid"
  
#define MSG_ERROR_ID_ErrTime       2
#define MSG_ERROR_DES_ErrTime      "��Ϣʱ���쳣"

#define MSG_ERROR_ID_NOT_ID_EVNT       3
#define MSG_ERROR_DES_NOT_ID_EVNT      "û�и���Ϣ�������"


using jValue = Json::Value;
using jReader = Json::Reader;
using callbackMsgEvent = void(*)(jValue args, jValue& result,std::string& errString,uint32_t& errCode); //��Ϣ����ص�
