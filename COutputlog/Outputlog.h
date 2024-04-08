#pragma once
#include <windows.h>// Windows 头文件
//
#include <fstream>
using std::string;
using std::fstream;
using std::ios;
using std::streampos;


enum OutputType{
	outTimeType,         //不需要传入参数
	outDwordType,        //DWORD
	outcharType,         //char *         200字节内
	outWchar_tType,      //wchar_t *      200字节内
	outEndType,          //不需要传入参数
};

#define _r_n     "\n"


class Outputlog{
public:
	//构造函数
	Outputlog(char * pPathFormat, ...);
	Outputlog();
	~Outputlog();

public:
	//初始化 log 文件路径
	BOOL InitOutputlog(char    * pFilePath);
	BOOL InitOutputlog(wchar_t * pFilePath);
	BOOL InitOutputlogEx(char    * pPathFormat, ...);


	//得到 打开状态
	BOOL Getopenstatus();
	//关闭 log
	BOOL Closelog();
	//删除 log 的文件
	BOOL Deletelog();
	//获取当前文件大小
	size_t GetLogfilesize();

	//写日志 
	void OutputlogByString(char    * pString);
	void OutputlogByString(wchar_t * pString);
	void OutputlogByFormat(char    * pFormat, ...);
	void OutputlogByByte(byte * pByte, DWORD ByteSize, DWORD OneLineSize = 16, BOOL ShowStr = FALSE);

	//根据类型 去输出数据
	void OutputlogByType(OutputType tOutputType, void * pOutputinfo = NULL);

private:
	//初始化 类中的 所有数据信息
	void ZeroClassInfo();

private:
	string   logfilepath;
	fstream  logfileobject;
	BOOL     logOpenFileSuccess;

};