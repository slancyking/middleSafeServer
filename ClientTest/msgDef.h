#pragma once
#include "json/json.h"

 

#define MSG_PING "ping" 


#define MSG_ERROR_ID_NOTID       1  
#define MSG_ERROR_DES_NOTID      "丢失消息id"
  
#define MSG_ERROR_ID_ErrTime       2
#define MSG_ERROR_DES_ErrTime      "消息时间异常"

#define MSG_ERROR_ID_NOT_ID_EVNT       3
#define MSG_ERROR_DES_NOT_ID_EVNT      "没有该消息处理过程"


using jValue = Json::Value;
using jReader = Json::Reader;
using callbackMsgEvent = void(*)(jValue args, jValue& result,std::string& errString,uint32_t& errCode); //消息处理回调
