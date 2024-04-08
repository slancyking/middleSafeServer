#pragma once

#include "httplib.h"
#include "string"
#include <json/json.h>
#include "../CShareMemory/CShareMemory.h"

using namespace std;


#define _ISDEBUG true

/// <summary>
/// ����������ͨ�����
/// </summary>
struct tagServerResponse
{
	/// <summary>
	/// ִ����Ϣ,��ѯ������
	/// </summary>
	std::string info;

	/// <summary>
	/// ִ�д���
	/// </summary>
	int code;
};

/// <summary>
/// ����������
/// </summary>
struct tagServerReportQuery
{
	/// <summary>
	/// ����˵ı�־λ,�����ǽ���id.֮���
	/// </summary>
	std::string flag;
	/// <summary>
	/// ��Կ���� ���ع����� 
	/// </summary>
	int keyIndex;
	/// <summary>
	/// ����˿�
	/// </summary>
	unsigned short randomPort;
	/// <summary>
	/// �����Կ
	/// </summary>
	std::string randomKey;
};

/// <summary>
/// ��ѯ�������
/// </summary>
struct tagServerReportResponse {
	/// <summary>
	/// ͨ�ý��
	/// </summary>
	tagServerResponse result;
	/// <summary>
	/// ��������
	/// </summary>
	tagServerReportQuery report;
};



/// <summary>
/// ���������Ϣ���ʵ��
/// </summary>
struct tagServerNameCollectDto
{
	/// <summary>
	/// ������
	/// </summary>
	std::string infoAgent;
	/// <summary>
	/// ����
	/// </summary>
	std::string name;
	/// <summary>
	/// //�Ա� 0δ֪ 1�� 2Ů 
	/// </summary>
	int sex;
	/// <summary>
	/// ͷ����ַ
	/// </summary>
	std::string headIconUrl;
	/// <summary>
	/// ͷ������
	/// </summary>
	std::string imageCollect;
};

/// <summary>
/// ��ȡ���������Ϣ���
/// </summary>
struct tagServerRandomNameCollectResponse {
	/// <summary>
	/// ͨ�ý��
	/// </summary>
	tagServerResponse result;
	/// <summary>
	/// ��Ϣ����
	/// </summary>
	tagServerNameCollectDto content;
};




//��־����
using logFunc = void(*)(std::string);




class ServerApi
{
public:
	/// <summary>
	/// �ͻ��˵���
	/// </summary>
	ServerApi();
	/// <summary>
	/// ���ص���
	/// </summary>
	/// <param name="host"></param>
	ServerApi(string branchKey, string host);
	~ServerApi();

	/// <summary>
	/// ���ݿ��ܵ�½
	/// </summary>
	/// <param name="cardPassword"></param>
	/// <returns></returns>
	tagServerResponse login(string cardPassword);

	/// <summary>
	/// �˳���½
	/// </summary>
	/// <returns></returns>
	tagServerResponse logout();

	/// <summary>
	/// ����
	/// </summary>
	/// <returns>���ص�ǰunixʱ���</returns>
	tagServerResponse ping();

	/// <summary>
	/// ���ÿ�����
	/// </summary>
	/// <param name="title"></param>
	/// <returns></returns>
	tagServerResponse setCardTitle(std::string title);

	/// <summary>
	/// ��ͣ����
	/// </summary>
	/// <returns></returns>
	tagServerResponse pause();

	/// <summary>
	/// ����һ���˿���Կ
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	tagServerResponse normalReport(tagServerReportQuery input);


	/// <summary>
	/// ��ѯ�˿���Կ
	/// </summary>
	/// <param name="flag"></param>
	/// <returns></returns>
	tagServerReportResponse normalQuery(std::string flag);

	/// <summary>
	/// ��ѯip�Ƿ����
	/// </summary>
	/// <param name="ip">ip��ַ</param>
	/// <param name="logMark">��¼��־</param>
	/// <param name="nation">����</param>
	/// <param name="province">ʡ��</param>
	/// <param name="city">����</param>
	/// <param name="district">����</param>
	/// <returns></returns>
	tagServerResponse tryUseIp(std::string ip, std::string logMark, std::string nation, std::string province, std::string city, std::string district);

	/// <summary>
	/// ������Ϣ�ռ�
	/// </summary>
	/// <param name="jsonStringForNames">json�ַ���</param>
	/// <returns></returns>
	tagServerResponse nameCollect(std::string jsonStringForNames);

	/// <summary>
	/// �ӷ������������һ��������Ϣ
	/// </summary>
	/// <param name="infoAgentId">����key</param>
	/// <returns></returns>
	tagServerRandomNameCollectResponse getRandomNameCollect(std::string infoAgentId);

	/// <summary>
	/// �쳣�ռ�
	/// </summary>
	/// <param name="errorTitle">�������</param>
	/// <param name="errorMessage">������Ϣ</param>
	/// <param name="backStackTraceBack">�����ջ</param>
	/// <returns></returns>
	tagServerResponse errorCollect(std::string errorTitle, std::string errorMessage, std::string backStackTraceBack);

	/// <summary>
	/// ��Ʒ�ռ�
	/// </summary>
	/// <param name="propName">��Ʒ��</param>
	/// <param name="propId">��Ʒid</param>
	/// <param name="propNum">��Ŀ</param>
	/// <param name="remark">��ע</param>
	/// <returns></returns>
	tagServerResponse reportPropCollect(std::string propName, std::string propId, int propNum, std::string remark);



	/// <summary>
	/// ��ȡ����ʱ��
	/// </summary>
	/// <returns></returns>
	INT64 getExpired();

	/// <summary>
	/// ��ȡ��½״̬
	/// </summary>
	/// <returns></returns>
	bool getLoginStatus();

	/// <summary>
	/// ������־����
	/// </summary>
	void setLogFunc(logFunc func);

	struct tagShareServerApi {
		char mHost[1024];
		char mEncryptToken[128];
		char mRSAPublicKey[4096];
		bool bLogin;
		UINT64 mExpired;
		char mCardPassword[256];
		UINT64 mSurplusSecond;

		tagShareServerApi(ServerApi* svapi) {
			memset(mHost, 0, 1024);
			memset(mEncryptToken, 0, 128);
			memset(mRSAPublicKey, 0, 4096);
			bLogin = 0;
			mExpired = 0;
			memset(mCardPassword, 0, 256);
			mSurplusSecond = 0;

			strcpy_s(mHost, svapi->mHost.c_str());
			strcpy_s(mEncryptToken, svapi->mEncryptToken.c_str());
			strcpy_s(mRSAPublicKey, svapi->mRSAPublicKey.c_str());
			bLogin = svapi->bLogin;
			mExpired = svapi->mExpired;
			strcpy_s(mCardPassword, svapi->mCardPassword.c_str());
			mSurplusSecond = svapi->mSurplusSecond;
		}

		tagShareServerApi() {

		}

	};

private:



	ShareMemory* _share_middle_server__obj__ = NULL;

	logFunc mLogFunc = NULL;


	void log(const char* _Format, ...);

	/// <summary>
	/// �����߳��Ƿ����
	/// </summary>
	bool bPingThreadFinish;

	static DWORD WINAPI  threadPing(void* thiz);

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
	/// ��Ŀ��֧��־
	/// </summary>
	string mBranchKey;

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
	/// ���ܹ���rsa��Կ
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



