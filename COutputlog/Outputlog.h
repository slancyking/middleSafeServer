#pragma once
#include <windows.h>// Windows ͷ�ļ�
//
#include <fstream>
using std::string;
using std::fstream;
using std::ios;
using std::streampos;


enum OutputType{
	outTimeType,         //����Ҫ�������
	outDwordType,        //DWORD
	outcharType,         //char *         200�ֽ���
	outWchar_tType,      //wchar_t *      200�ֽ���
	outEndType,          //����Ҫ�������
};

#define _r_n     "\n"


class Outputlog{
public:
	//���캯��
	Outputlog(char * pPathFormat, ...);
	Outputlog();
	~Outputlog();

public:
	//��ʼ�� log �ļ�·��
	BOOL InitOutputlog(char    * pFilePath);
	BOOL InitOutputlog(wchar_t * pFilePath);
	BOOL InitOutputlogEx(char    * pPathFormat, ...);


	//�õ� ��״̬
	BOOL Getopenstatus();
	//�ر� log
	BOOL Closelog();
	//ɾ�� log ���ļ�
	BOOL Deletelog();
	//��ȡ��ǰ�ļ���С
	size_t GetLogfilesize();

	//д��־ 
	void OutputlogByString(char    * pString);
	void OutputlogByString(wchar_t * pString);
	void OutputlogByFormat(char    * pFormat, ...);
	void OutputlogByByte(byte * pByte, DWORD ByteSize, DWORD OneLineSize = 16, BOOL ShowStr = FALSE);

	//�������� ȥ�������
	void OutputlogByType(OutputType tOutputType, void * pOutputinfo = NULL);

private:
	//��ʼ�� ���е� ����������Ϣ
	void ZeroClassInfo();

private:
	string   logfilepath;
	fstream  logfileobject;
	BOOL     logOpenFileSuccess;

};