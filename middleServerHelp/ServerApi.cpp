#include "pch.h"
#include "ServerApi.h"
#include "WebAlgorithm.h"
#include "json/json.h"
#include "CommonServerParam.h"
#include "CEncrypt.h"

ServerApi::ServerApi(string host)
{
	this->mHost = host; 
	bLogin = false;
	this->mClient = new httplib::Client(host); 
	this->mClient->enable_server_certificate_verification(false);
}

ServerApi::~ServerApi()
{
	if (this->mClient != NULL) {
		delete this->mClient;
		this->mClient = NULL;
	}
}


string ServerApi::getDecToken() { 
	return mEncryptToken == "" ? "" : WebAlgorithm::GUIDDecrypt(mEncryptToken);
}

bool ServerApi::login(string cardPassword)
{
	WebAlgorithm wa;

	std::string params = format("{{\"CardPassword\":\"{}\"}}", cardPassword);
  
	if (mClient == NULL) return false;
	
	auto res = mClient->Post(WEBAPI_LOGIN, params, "application/json");
	if (res->status != 200)
		return false;
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
		return false;
	
	OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].asInt() != 0) {
		return false;
	}

	mEncryptToken = wa.GetstringDecrypt(jResult["token"].asString(), cardPassword);
	if (mEncryptToken == "")
		return false;
	string token = getDecToken();
	if (token == "") return false;

	string encTokenEx = jResult["tokenEx"].asString();
	mRSAPublicKey = wa.GetstringDecrypt(encTokenEx, token);
	mExpired = jResult["expired"].asInt64();
	mSurplusSecond = jResult["surplusSecond"].asInt64();
	this->mCardPassword = cardPassword;
	this->bLogin = true;
	return true;
}

bool ServerApi::logout()
{
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	auto res = mClient->Post(WEBAPI_LOGOUT, csp.getRequestString(), "application/json");
	if (res->status != 200)
		return false;
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
		return false;
	
	if (!jResult["result"].isString())
		return false;

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
		return false;

	if (realRecv["result"].asInt() != 0)
		return false;

	return true;
}

int ServerApi::ping()
{
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	auto res = mClient->Post(WEBAPI_PING, csp.getRequestString(), "application/json");
	if (res->status != 200)
		return -1;
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
		return -2;

	if (!jResult["result"].isString())
		return -3;
	OutputDebugStringA(jResult.toStyledString().c_str());
	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
		return -4;

	if (realRecv["Result"].asInt() != 0)
		return realRecv["Result"].asInt();
	 
	return atoi(realRecv["Info"].asString().c_str());
}

int ServerApi::pause()
{
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	auto res = mClient->Post(WEBAPI_PAUSE, csp.getRequestString(), "application/json");
	if (res->status != 200)
		return -1;
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
		return -2;

	if (!jResult["result"].isString())
		return -3;

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
		return -4; 

	return realRecv["Result"].asInt();
}

int ServerApi::normalReport(tagServerReport input)
{
	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["flag"] = input.flag;
	dto["keyIndex"] = input.keyIndex;
	dto["randomPort"] = input.randomPort;
	dto["randomKey"] = input.randomKey;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	auto res = mClient->Post(WEBAPI_NORMALREPORT, csp.getRequestString(), "application/json");
	if (res->status != 200)
		return -1;
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
		return -2;

	if (!jResult["result"].isString())
		return -3;

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
		return -4;

	return realRecv["Result"].asInt();
}

tagServerReport ServerApi::normalQuery(std::string flag)
{
	tagServerReport result;

	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["flag"] = flag;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	auto res = mClient->Post(WEBAPI_NORMALREPORT, csp.getRequestString(), "application/json");
	if (res->status != 200) {
		result.code = -1;
		return result;
	}
		
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(res->body, jResult))
	{
		result.code = -2;
		return result;
	}

	if (!jResult["result"].isString())
	{
		result.code = -3;
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -4;
		return result;
	}

	result.code = 0;
	result.flag = realRecv["flag"].asString();
	result.keyIndex = realRecv["keyIndex"].asInt();
	result.randomPort = realRecv["randomPort"].asInt();
	result.randomKey = realRecv["randomKey"].asString(); 
	return result;
}





INT64 ServerApi::getExpired()
{
	return this->mExpired;
}

string ServerApi::getFormatKey()
{
	return format("-----BEGIN PUBLIC KEY-----\n{}\n-----END PUBLIC KEY-----", mRSAPublicKey);
}

Json::Value ServerApi::getRealRecvDto(string recv) {
	string result = CEncrypt::RsaPubDecrypt(recv, getFormatKey());
	OutputDebugStringA(result.c_str());
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(result, jResult))
		return Json::ValueType::nullValue;
	return jResult;
}