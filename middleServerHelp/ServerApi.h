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
	/// ���ݿ��ܵ�½
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
	/// ����ʱ��
	/// </summary>
	INT64 mExpired;

	/// <summary>
	/// ʣ������
	/// </summary>
	INT64 mSurplusSecond;

	/// <summary>
	/// ����
	/// </summary>
	string mCardPassword;

	/// <summary>
	/// �Ƿ��Ѿ���½
	/// </summary>
	bool bLogin;

	/// <summary>
	/// ���ܹ���token
	/// </summary>
	string mEncryptToken;

	/// <summary>
	/// rsa��Կ
	/// </summary>
	/// <returns></returns>
	string mRSAPublicKey;

	/// <summary>
	/// ��ȡ��½ƾ֤
	/// </summary>
	/// <returns></returns>
	string getDecToken();

	/// <summary>
	/// ��ȡ��ʵ��������
	/// </summary>
	/// <param name="recv"></param>
	/// <returns></returns>
	Json::Value getRealRecvDto(string recv);

};

