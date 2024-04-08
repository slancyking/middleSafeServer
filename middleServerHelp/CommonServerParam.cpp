#include "pch.h"
#include "CommonServerParam.h"
#include "json/json.h"

CommonServerParam::CommonServerParam(string cardPwd, string param)
{
	mCardPassword = cardPwd;
	mParam =  param; 
}

string CommonServerParam::getRequestString()
{
	Json::Value dto;
	dto["password"] = mCardPassword;
	dto["param"] = mParam;  
	return dto.toStyledString();
}
