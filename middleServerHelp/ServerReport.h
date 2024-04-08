#pragma once
#include <string>

struct tagServerReport
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
	/// <summary>
	/// 执行信息,查询报告用
	/// </summary>
	std::string info;

	/// <summary>
	/// 执行代码
	/// </summary>
	int code;
};