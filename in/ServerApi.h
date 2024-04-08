#pragma once

#include "httplib.h"
#include "string"
#include <json/json.h>
#include "../CShareMemory/CShareMemory.h"

using namespace std;


#define _ISDEBUG true

/// <summary>
/// 服务器请求通用输出
/// </summary>
struct tagServerResponse
{
	/// <summary>
	/// 执行信息,查询报告用
	/// </summary>
	std::string info;

	/// <summary>
	/// 执行代码
	/// </summary>
	int code;
};

/// <summary>
/// 报告服务参数
/// </summary>
struct tagServerReportQuery
{
	/// <summary>
	/// 服务端的标志位,可以是进程id.之类的
	/// </summary>
	std::string flag;
	/// <summary>
	/// 秘钥索引 本地管理用 
	/// </summary>
	int keyIndex;
	/// <summary>
	/// 随机端口
	/// </summary>
	unsigned short randomPort;
	/// <summary>
	/// 随机秘钥
	/// </summary>
	std::string randomKey;
};

/// <summary>
/// 查询报告输出
/// </summary>
struct tagServerReportResponse {
	/// <summary>
	/// 通用结果
	/// </summary>
	tagServerResponse result;
	/// <summary>
	/// 报告内容
	/// </summary>
	tagServerReportQuery report;
};



/// <summary>
/// 随机人名信息输出实体
/// </summary>
struct tagServerNameCollectDto
{
	/// <summary>
	/// 渠道名
	/// </summary>
	std::string infoAgent;
	/// <summary>
	/// 名字
	/// </summary>
	std::string name;
	/// <summary>
	/// //性别 0未知 1男 2女 
	/// </summary>
	int sex;
	/// <summary>
	/// 头像网址
	/// </summary>
	std::string headIconUrl;
	/// <summary>
	/// 头像数据
	/// </summary>
	std::string imageCollect;
};

/// <summary>
/// 获取随机人名信息输出
/// </summary>
struct tagServerRandomNameCollectResponse {
	/// <summary>
	/// 通用结果
	/// </summary>
	tagServerResponse result;
	/// <summary>
	/// 信息内容
	/// </summary>
	tagServerNameCollectDto content;
};




//日志函数
using logFunc = void(*)(std::string);




class ServerApi
{
public:
	/// <summary>
	/// 客户端调用
	/// </summary>
	ServerApi();
	/// <summary>
	/// 主控调用
	/// </summary>
	/// <param name="host"></param>
	ServerApi(string branchKey, string host);
	~ServerApi();

	/// <summary>
	/// 根据卡密登陆
	/// </summary>
	/// <param name="cardPassword"></param>
	/// <returns></returns>
	tagServerResponse login(string cardPassword);

	/// <summary>
	/// 退出登陆
	/// </summary>
	/// <returns></returns>
	tagServerResponse logout();

	/// <summary>
	/// 心跳
	/// </summary>
	/// <returns>返回当前unix时间戳</returns>
	tagServerResponse ping();

	/// <summary>
	/// 设置卡标题
	/// </summary>
	/// <param name="title"></param>
	/// <returns></returns>
	tagServerResponse setCardTitle(std::string title);

	/// <summary>
	/// 暂停卡密
	/// </summary>
	/// <returns></returns>
	tagServerResponse pause();

	/// <summary>
	/// 报告一个端口秘钥
	/// </summary>
	/// <param name="input"></param>
	/// <returns></returns>
	tagServerResponse normalReport(tagServerReportQuery input);


	/// <summary>
	/// 查询端口秘钥
	/// </summary>
	/// <param name="flag"></param>
	/// <returns></returns>
	tagServerReportResponse normalQuery(std::string flag);

	/// <summary>
	/// 查询ip是否可用
	/// </summary>
	/// <param name="ip">ip地址</param>
	/// <param name="logMark">记录标志</param>
	/// <param name="nation">国家</param>
	/// <param name="province">省份</param>
	/// <param name="city">城市</param>
	/// <param name="district">地区</param>
	/// <returns></returns>
	tagServerResponse tryUseIp(std::string ip, std::string logMark, std::string nation, std::string province, std::string city, std::string district);

	/// <summary>
	/// 名称信息收集
	/// </summary>
	/// <param name="jsonStringForNames">json字符串</param>
	/// <returns></returns>
	tagServerResponse nameCollect(std::string jsonStringForNames);

	/// <summary>
	/// 从服务器渠道随机一个人名信息
	/// </summary>
	/// <param name="infoAgentId">渠道key</param>
	/// <returns></returns>
	tagServerRandomNameCollectResponse getRandomNameCollect(std::string infoAgentId);

	/// <summary>
	/// 异常收集
	/// </summary>
	/// <param name="errorTitle">错误标题</param>
	/// <param name="errorMessage">错误消息</param>
	/// <param name="backStackTraceBack">错误堆栈</param>
	/// <returns></returns>
	tagServerResponse errorCollect(std::string errorTitle, std::string errorMessage, std::string backStackTraceBack);

	/// <summary>
	/// 物品收集
	/// </summary>
	/// <param name="propName">物品名</param>
	/// <param name="propId">物品id</param>
	/// <param name="propNum">数目</param>
	/// <param name="remark">备注</param>
	/// <returns></returns>
	tagServerResponse reportPropCollect(std::string propName, std::string propId, int propNum, std::string remark);



	/// <summary>
	/// 获取过期时间
	/// </summary>
	/// <returns></returns>
	INT64 getExpired();

	/// <summary>
	/// 获取登陆状态
	/// </summary>
	/// <returns></returns>
	bool getLoginStatus();

	/// <summary>
	/// 设置日志函数
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
	/// 心跳线程是否完成
	/// </summary>
	bool bPingThreadFinish;

	static DWORD WINAPI  threadPing(void* thiz);

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
	/// 项目分支标志
	/// </summary>
	string mBranchKey;

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
	/// 加密过的rsa公钥
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



