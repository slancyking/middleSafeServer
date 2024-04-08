#pragma once
 
#include "httplib.h"
#include "string"
#include "json/json.h"
#include "ServerReport.h"
using namespace std;


#define WEBAPI_LOGIN "/api/app/card/login"
#define WEBAPI_LOGOUT "/api/app/card/logout"
#define WEBAPI_PING "/api/app/card/ping"
#define WEBAPI_PAUSE  "/api/app/card/pause"
#define WEBAPI_NORMALREPORT "/api/app/middle-report/normal-report"
#define WEBAPI_NormalQuery "/api/app/middle-report/normal-query"

class ServerApi
{
public:
  
	ServerApi(string host);
	~ServerApi();

	/// <summary>
	/// 根据卡密登陆
	/// </summary>
	/// <param name="cardPassword"></param>
	/// <returns></returns>
	bool login(string cardPassword);

	bool logout();

	int ping();

	int pause();
	
	int normalReport(tagServerReport input);

	tagServerReport normalQuery(std::string flag);

	INT64 getExpired();
	


private:

	string getFormatKey();

	string mHost;
	httplib::Client* mClient = NULL;

	/// <summary>
	/// 过期时间
	/// </summary>
	INT64 mExpired;

	/// <summary>
	/// 剩余秒数
	/// </summary>
	INT64 mSurplusSecond;

	/// <summary>
	/// 卡密
	/// </summary>
	string mCardPassword;

	/// <summary>
	/// 是否已经登陆
	/// </summary>
	bool bLogin;

	/// <summary>
	/// 加密过的token
	/// </summary>
	string mEncryptToken;

	/// <summary>
	/// rsa公钥
	/// </summary>
	/// <returns></returns>
	string mRSAPublicKey;

	/// <summary>
	/// 获取登陆凭证
	/// </summary>
	/// <returns></returns>
	string getDecToken();

	/// <summary>
	/// 获取真实的输出结果
	/// </summary>
	/// <param name="recv"></param>
	/// <returns></returns>
	Json::Value getRealRecvDto(string recv);

};

