#include "../pch.h"
#include "ServerApi.h"
#include "../Algorithm/WebAlgorithm.h"

#include "CommonServerParam.h"
#include "../Algorithm/CEncrypt.h"
#include "../stringHelp.h" 
#include "../Algorithm/Base64.h"


 

ServerApi::ServerApi()
{
	_share_middle_server__obj__ = new ShareMemory((char*)"__middle_server__obj__mutex", (char*)"__middle_server__obj__");
	tagShareServerApi consoleInfo;;
	_share_middle_server__obj__->ReadMemory(&consoleInfo, sizeof(tagShareServerApi));

	this->mHost = consoleInfo.mHost; 
	this->mEncryptToken = consoleInfo.mEncryptToken;
	this->mRSAPublicKey = consoleInfo.mRSAPublicKey;
	this->bLogin = consoleInfo.bLogin;
	this->mExpired = consoleInfo.mExpired;
	this->mCardPassword = consoleInfo.mCardPassword;
	this->mSurplusSecond = consoleInfo.mSurplusSecond;

	this->mClient = new httplib::Client(mHost);
	this->mClient->enable_server_certificate_verification(false);


	this->bPingThreadFinish = false;
}

ServerApi::ServerApi(string branchKey, string host)
{
	this->mHost = host;
	this->mBranchKey = branchKey;
	bLogin = false;
	bPingThreadFinish = false;
	this->mClient = new httplib::Client(host); 
	this->mClient->enable_server_certificate_verification(false);
	this->mClient->set_connection_timeout(10, 0);
	this->mClient->set_read_timeout(30);
	this->mClient->set_write_timeout(10);
	_share_middle_server__obj__ = new ShareMemory((char*)"__middle_server__obj__mutex", (char*)"__middle_server__obj__", sizeof(tagShareServerApi));
}




ServerApi::~ServerApi()
{
	this->log("[ServerAPI] 释放");
	if (this->mClient != NULL) {
		delete this->mClient;
		this->mClient = NULL;
	}

	if (_share_middle_server__obj__ != NULL)
		delete this->_share_middle_server__obj__;
	 
}


string ServerApi::getDecToken() { 
	return mEncryptToken == "" ? "" : WebAlgorithm::GUIDDecrypt(mEncryptToken);
}

tagServerResponse ServerApi::login(string cardPassword)
{
	this->log("[ServerAPI] 登陆,卡密:%s", cardPassword);
	WebAlgorithm wa;
	tagServerResponse result;
	std::string params = std::format("{{\"cardPassword\":\"{}\",\"branchId\":\"{}\"}}", cardPassword, this->mBranchKey);
   
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化"; 
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	} 
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_LOGIN, params.c_str(), params.size(), "application/json");
	this->log("[ServerAPI -> login] 网络耗时:%ld 毫秒 ", GetTickCount() - st);

	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常"; 
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].asInt() != 0) {
		result.code = jResult["result"].asInt();
		result.info = jResult["info"].asString();
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	mEncryptToken = wa.GetstringDecrypt(jResult["token"].asString(), cardPassword);
	if (mEncryptToken == "")
	{
		result.code = -11;
		result.info = "登陆凭证异常";
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	string token = getDecToken();
	if (token == "") {
		result.code = -12;
		result.info = "登陆凭证异常2";
		this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	string encTokenEx = jResult["tokenEx"].asString();
	mRSAPublicKey = jResult["tokenEx"].asString();
	mExpired = jResult["expired"].asInt64();
	mSurplusSecond = jResult["surplusSecond"].asInt64();
	this->mCardPassword = cardPassword;
	this->bLogin = true;
	tagShareServerApi shareInfo(this);
	this->_share_middle_server__obj__->WriteMemory(&shareInfo,sizeof(tagShareServerApi));
	__CreateThreadCall(this, threadPing);
	result.code = 0;
	result.info = "操作成功";
	this->log("[ServerAPI -> login] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::logout()
{
	tagServerResponse result;
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	if(bLogin == false) {
		result.code = -2;
		result.info = "还未登陆";
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}


	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_LOGOUT, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> logout] 网络耗时:%ld 毫秒 ", GetTickCount() - st);

	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());
	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
 

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->bLogin = false;

	UINT64 t = GetTickCount64();
	while (!bPingThreadFinish)
	{
		if (GetTickCount64() - t > 5 * 1000)
			break;
		Sleep(100);
	}
	this->log("[ServerAPI -> logout] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::ping()
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (bLogin == false) {
		result.code = -2;
		result.info = "还未登陆";
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));

	DWORD st = GetTickCount(); 
	auto res = mClient->Post(WEBAPI_PING, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> ping] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	 
	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> ping] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::setCardTitle(std::string title)
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["title"] = stringHelp::GBKToUTF8(title);



	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt( dto.toStyledString(), getFormatKey()));

	DWORD st = GetTickCount(); 
	auto res = mClient->Post(WEBAPI_SETTITLE, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> setCardTitle] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> setCardTitle] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::pause()
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (bLogin == false) {
		result.code = -2;
		result.info = "还未登陆";
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value dto;
	dto["token"] = this->getDecToken();
	dto["postUnix"] = std::time(0);
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount(); 
	auto res = mClient->Post(WEBAPI_PAUSE, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> pause] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());



	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	this->bLogin = false;
	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	UINT64 t = GetTickCount64();
	while (!bPingThreadFinish)
	{
		if (GetTickCount64() - t > 5 * 1000)
			break;
		Sleep(100);
	}
	this->log("[ServerAPI -> pause] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::normalReport(tagServerReportQuery input)
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
		return result;
	} 
	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["flag"] = input.flag;
	dto["keyIndex"] = input.keyIndex;
	dto["randomPort"] = input.randomPort;
	dto["randomKey"] = input.randomKey;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount(); 
	auto res = mClient->Post(WEBAPI_NORMALREPORT, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> normalReport] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> normalReport] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerReportResponse ServerApi::normalQuery(std::string flag)
{
	tagServerReportResponse result;
	if (mClient == NULL) {
		result.result.code = -1;
		result.result.info = "客户端未初始化";
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	if (bLogin == false) {
		result.result.code = -2;
		result.result.info = "还未登陆";
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["flag"] = flag;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount(); 
	auto res = mClient->Post(WEBAPI_NormalQuery, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> normalQuery] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.result.code = -5;
		result.result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
		
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.result.code = -10;
		result.result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.result.code = jResult["result"]["Result"].asInt();
		result.result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.result.code = -11;
		result.result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	result.result.code = 0;
	result.report.flag = realRecv["Flag"].asString();
	result.report.keyIndex = realRecv["KeyIndex"].asInt();
	result.report.randomPort = realRecv["RandomPort"].asInt();
	result.report.randomKey = realRecv["RandomKey"].asString();
	this->log("[ServerAPI -> normalQuery] 执行结果:%d ,%s", result.result.code, result.result.info);
	return result;
}
  
tagServerResponse ServerApi::tryUseIp(std::string ip, std::string logMark, std::string nation, std::string province, std::string city, std::string district)
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["ipAddress"] = ip;
	dto["logMark"] = stringHelp::GBKToUTF8(logMark);
	dto["nation"] = stringHelp::GBKToUTF8(nation);
	dto["province"] = stringHelp::GBKToUTF8(province);
	dto["city"] = stringHelp::GBKToUTF8(city);
	dto["district"] = stringHelp::GBKToUTF8(district);

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_TRYUSEIP, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> tryUseIp] 网络耗时:%ld 毫秒 ", GetTickCount() - st);

	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> tryUseIp] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::nameCollect(std::string jsonStringForNames)
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value jNames;
	Json::Reader  jReader;
	if (!jReader.parse(jsonStringForNames, jNames)) {
		result.code = -2;
		result.info = "参数初始化异常";
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	 
	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["nameCollects"] = jNames;
	 
	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(   dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_NAMECOLLECT, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> nameCollect] 网络耗时:%ld 毫秒 ", GetTickCount() - st);

	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult; 
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> nameCollect] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerRandomNameCollectResponse ServerApi::getRandomNameCollect(std::string infoAgentId)
{
	tagServerRandomNameCollectResponse result;
	if (mClient == NULL) {
		result.result.code = -1;
		result.result.info = "客户端未初始化";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	if (bLogin == false) {
		result.result.code = -2;
		result.result.info = "还未登陆";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["infoAgentId"] = infoAgentId;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_NAMEINFORANDOM, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> getRandomNameCollect] 网络耗时:%ld 毫秒 ", GetTickCount() - st);
	if (res->status != 200)
	{
		result.result.code = -5;
		result.result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.result.code = -10;
		result.result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	if (_ISDEBUG)
		this->log(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.result.code = jResult["result"]["Result"].asInt();
		result.result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	Base64 b64; 
	string result1 = jResult["result"].asString();
	string result2 = stringHelp::UTF8ToGBK( b64.Decode(result1.c_str(), result1.length()));
	

	Json::Value realRecv; // getRealRecvDto(jResult["result"].asString());
	jReader.parse(result2, realRecv);
	if (_ISDEBUG)
		this->log(jResult["result"].asString().c_str());
	if (realRecv.empty())
	{
		result.result.code = -11;
		result.result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	if (realRecv["Result"].asInt() != 0)
	{
		result.result.code = realRecv["Result"].asInt();
		result.result.info = realRecv["Info"].asString();
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}
	if (!realRecv["Data"].isObject())
	{
		result.result.code = -12;
		result.result.info = "中间服务返回关键数据为空!";
		this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
		return result;
	}

	result.result.code = realRecv["Result"].asInt();
	result.result.info = realRecv["Info"].asString();
	result.content.infoAgent = realRecv["Data"]["InfoAgent"].asString();
	result.content.name = realRecv["Data"]["Name"].asString();
	result.content.sex = realRecv["Data"]["Sex"].asInt();
	result.content.headIconUrl = realRecv["Data"]["HeadIconUrl"].asString();
	result.content.imageCollect = realRecv["Data"]["ImageCollect"].asString();
	this->log("[ServerAPI -> getRandomNameCollect] 执行结果:%d ,%s", result.result.code, result.result.info);
	return result; 
}




tagServerResponse ServerApi::errorCollect(std::string errorTitle, std::string errorMessage, std::string backStackTraceBack)
{
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	 
	Json::Reader  jReader; 

	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["errorTitle"] = stringHelp::GBKToUTF8(errorTitle);
	dto["errorMessage"] = stringHelp::GBKToUTF8(errorMessage);
	dto["backStackTraceBack"] = stringHelp::GBKToUTF8(backStackTraceBack);

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_ERRORCOLLECT, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> errorCollect] 网络耗时:%ld 毫秒 ", GetTickCount() - st); 
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> errorCollect] 执行结果:%d ,%s", result.code, result.info);
	return result;
}

tagServerResponse ServerApi::reportPropCollect(std::string propName, std::string propId, int propNum, std::string remark)
{ 
	tagServerResponse result;
	if (mClient == NULL) {
		result.code = -1;
		result.info = "客户端未初始化";
		this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Reader  jReader;

	Json::Value dto;
	dto["postUnix"] = std::time(0);
	dto["token"] = this->getDecToken();
	dto["propName"] = stringHelp::GBKToUTF8(propName);
	dto["propId"] = stringHelp::GBKToUTF8(propId);
	dto["remark"] = stringHelp::GBKToUTF8(remark);
	dto["propNum"] = propNum;

	CommonServerParam csp(this->mCardPassword, CEncrypt::RsaPubEncrypt(dto.toStyledString(), getFormatKey()));
	DWORD st = GetTickCount();
	auto res = mClient->Post(WEBAPI_PROPCOLLECT, csp.getRequestString(), "application/json");
	this->log("[ServerAPI -> reportPropCollect] 网络耗时:%ld 毫秒 ", GetTickCount() - st); 
	if (res->status != 200)
	{
		result.code = -5;
		result.info = "中间服务返回状态异常";
		this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	Json::Value jResult;
	if (!jReader.parse(stringHelp::UTF8ToGBK(res->body), jResult))
	{
		result.code = -10;
		result.info = "中间服务返回内容格式异常";
		this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}
	if (_ISDEBUG)
		OutputDebugStringA(jResult.toStyledString().c_str());

	if (jResult["result"].isObject()) {
		result.code = jResult["result"]["Result"].asInt();
		result.info = jResult["result"]["Info"].asString();
		this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	Json::Value realRecv = getRealRecvDto(jResult["result"].asString());

	if (realRecv.empty())
	{
		result.code = -11;
		result.info = "中间服务返回内容格式异常2";
		this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
		return result;
	}

	result.code = realRecv["Result"].asInt();
	result.info = realRecv["Info"].asString();
	this->log("[ServerAPI -> reportPropCollect] 执行结果:%d ,%s", result.code, result.info);
	return result;

	return tagServerResponse();
}

INT64 ServerApi::getExpired()
{
	return this->mExpired;
}

bool ServerApi::getLoginStatus()
{
	return bLogin && !bPingThreadFinish; //登陆成功并且心跳线程没有退出
}

void ServerApi::setLogFunc(logFunc func)
{
	mLogFunc = func;
}
 
  
void ServerApi::log(const char* _Format, ...)
{ 
	if (mLogFunc != NULL) {

		std::string tmp;

		va_list marker = NULL;
		va_start(marker, _Format);

		size_t num_of_chars = _vscprintf(_Format, marker);

		if (num_of_chars > tmp.capacity()) {
			tmp.resize(num_of_chars + 1);
		}

		vsprintf_s((char*)tmp.data(), tmp.capacity(), _Format, marker);

		va_end(marker);
		 
		mLogFunc(tmp);
	}
		
}

DWORD WINAPI ServerApi::threadPing(void* thiz) {
	ServerApi* pthis = (ServerApi*)thiz;
	UINT64 t = GetTickCount64();
	while (pthis->bLogin)
	{
		if (GetTickCount64() - t < 2 * 60 * 1000)
		{
			Sleep(500);
			continue;
		} 
		tagServerResponse pRes = pthis->ping(); 
		if (pRes.code != 0) {
			pthis->log("[ServerAPI -> threadPing 心跳异常,代码:{} , 内容:{}", pRes.code, pRes.info);
			//exit(0);
		}
		
		t = GetTickCount64();
		Sleep(500);
	}
	pthis->bPingThreadFinish = true;
	return 0;
}

string ServerApi::getFormatKey()
{ 
	WebAlgorithm wa;
	return std::format("-----BEGIN PUBLIC KEY-----\n{}\n-----END PUBLIC KEY-----", wa.GetstringDecrypt(mRSAPublicKey, getDecToken()));
}

Json::Value ServerApi::getRealRecvDto(string recv) {
	string result = stringHelp::UTF8ToGBK(CEncrypt::RsaPubDecrypt(recv, getFormatKey()));
	OutputDebugStringA(result.c_str());
	Json::Value jResult;
	Json::Reader  jReader;
	if (!jReader.parse(result, jResult))
		return Json::ValueType::nullValue;
	return jResult;
}