#pragma once
#include "Outputlog.h"
#include <ctime>


//--------------------------------------------------------------------
//|                    �ַ����� ��ת��ANSI�ַ��� �� Unicode�ַ�����
//--------------------------------------------------------------------
//|��������bool Char_wchar__in char * InStr, __out wchar_t * OutStrBuffer, __in int OutStrBufferSize)
//|��������bool wchar_t_Char(__in wchar_t * InStr, __out char * OutStrBuffer, __in int OutStrBufferSize)
//| �� �ͣ���
//|����ֵ������true �� false
//|���ӣ���
//--------------------------------------------------------------------
bool logChar_wchar_t(__in char * InStr, __out wchar_t * OutStrBuffer, __in int OutStrBufferSize){

	if (NULL == InStr || NULL == OutStrBuffer){ return false; }

	//MultiByteToWideChar
	//http://baike.baidu.com/link?url=R1bYIh3tz9idLOQIRFUwAj0J6XJqFpDWVtz6l8nKFJXKHyTlrlJuKE9lgYe9BZQ4oyV9ns10IlXubvSXPCDtFa

	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, NULL, InStr, -1, NULL, NULL);
	if (NULL == dwMinSize || dwMinSize > (DWORD)OutStrBufferSize){
		return false;
	}
	if (NULL == MultiByteToWideChar(CP_ACP, NULL, InStr, -1, OutStrBuffer, dwMinSize)){
		return false;
	}
	return true;
}

bool logwchar_t_Char(__in wchar_t * InStr, __out char * OutStrBuffer, __in int OutStrBufferSize){

	if (NULL == InStr || NULL == OutStrBuffer){ return false; }

	//WideCharToMultiByte
	//http://baike.baidu.com/link?url=-eqWUruIH6bJwG1N1WDjFVglCXFU_KSbP6zrbT5xttb701AmwfYmcfrn6OVefXEy_HlwUkYckFv3L0906tw7q_
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, InStr, -1, NULL, 0, NULL, FALSE);
	if (NULL == dwMinSize || dwMinSize > (DWORD)OutStrBufferSize){
		return false;
	}
	if (NULL == WideCharToMultiByte(CP_OEMCP, NULL, InStr, -1, OutStrBuffer, dwMinSize, NULL, FALSE)){
		return false;
	}
	return true;
}

//��ȡ��ǰϵͳʱ��   1000 - 00 - 00 00:00:00
string logGetNowTime(){
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime); 
	char tTimeString[50] = { NULL };
	wsprintfA(tTimeString, "%04d-%02d-%02d %02d:%02d:%02d:%03d", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, sysTime.wMilliseconds);
	return string(tTimeString);
}



//��ʼ�� ���е� ����������Ϣ
void Outputlog::ZeroClassInfo(){
	this->logfilepath = "";
	if (true == this->logfileobject.is_open()){
		this->logfileobject.clear();//������
		this->logfileobject.close();//�ر�
	}
	this->logOpenFileSuccess = FALSE;
}

Outputlog::Outputlog(){
	this->ZeroClassInfo();
};

Outputlog::Outputlog(char    * pPathFormat, ...){
	if (NULL == pPathFormat){ return ; }
	va_list args;
	va_start(args, pPathFormat);
	char tPath[500] = { NULL };
	vsnprintf_s(tPath, 500, pPathFormat, args);
	this->InitOutputlog(tPath);
};

BOOL Outputlog::InitOutputlog(char * pFilePath){
	if (NULL == pFilePath){ goto GoToError; }
	//��ʼ���ڴ�����
	this->ZeroClassInfo();

	DWORD 	tFileStrSize = (DWORD)strlen(pFilePath);
	//��ǰĿ¼
	if (NULL == strstr(pFilePath, ":")){
#pragma region//|-----------------------------------------------------------------ʹ�õ��� ��ǰĬ��Ŀ¼
		char tNowCatalog[MAX_PATH] = { NULL };
		if (NULL >= GetModuleFileNameA(NULL, tNowCatalog, MAX_PATH)){
			goto GoToError;
		}
		char * pCatalogZero = strrchr(tNowCatalog, '\\');	//Ѱ��β���� \\  ��β
		if (NULL == pCatalogZero){ goto GoToError; }
		pCatalogZero[1] = 0x00;

		this->logfilepath = tNowCatalog;
		this->logfilepath = this->logfilepath + pFilePath;
#pragma endregion
	}
	else{
//|-----------------------------------------------------------------ʹ�õ��� �ļ�ȫ��·��
		this->logfilepath = pFilePath;
	}

	this->logfileobject.open(this->logfilepath, ios::in | ios::out | ios::app);
	this->logOpenFileSuccess = (true == this->logfileobject.is_open());
	return this->logOpenFileSuccess;
GoToError:;
	this->ZeroClassInfo();
	return FALSE;
}

BOOL Outputlog::InitOutputlog(wchar_t * pFilePath){
	if (NULL == pFilePath){ goto GoToError; }
	char tFilePath[500] = { NULL };
	if (false == logwchar_t_Char(pFilePath, tFilePath, 500)){
		goto GoToError;
	}
	return this->InitOutputlog(tFilePath);
GoToError:;
	this->ZeroClassInfo();
	return FALSE;
}

BOOL Outputlog::InitOutputlogEx(char    * pPathFormat, ...){
	if (NULL == pPathFormat){ return FALSE; }
	va_list args;
	va_start(args, pPathFormat);
	char tPath[500] = { NULL };
	vsnprintf_s(tPath, 500, pPathFormat, args);
	va_end(args);
	return this->InitOutputlog(tPath);
}

Outputlog::~Outputlog(){
	//���˵��һ������־,��ôɾ����
	if (TRUE == this->logOpenFileSuccess && NULL == this->GetLogfilesize()){
		
		this->logfileobject.clear();//������
		this->logfileobject.close();//�ر�

		DeleteFileA(this->logfilepath.c_str());
	}
	this->ZeroClassInfo();
};

//�õ� ��״̬
BOOL Outputlog::Getopenstatus(){
	return this->logOpenFileSuccess;
}

//�ر� log ��д��
BOOL Outputlog::Closelog(){
	this->ZeroClassInfo();
	return TRUE;
}

//ɾ�� log ���ļ�
BOOL Outputlog::Deletelog(){
	if (TRUE == this->logOpenFileSuccess){

		this->logfileobject.clear();//������
		this->logfileobject.close();//�ر�

		DeleteFileA(this->logfilepath.c_str());

		this->logfileobject.open(this->logfilepath, ios::in | ios::out | ios::app);
		this->logOpenFileSuccess = (true == this->logfileobject.is_open());
	}
	return TRUE;
}

size_t Outputlog::GetLogfilesize(){
	if (FALSE == this->logOpenFileSuccess){
		return 0;
	}
	streampos curPos = this->logfileobject.tellg();  // ��ǰ�ļ�ָ��λ��
	this->logfileobject.seekg(0, ios::end);          // ���ļ�ָ��ָ���ļ�ĩβ 
	streampos pos = this->logfileobject.tellg();     // ��ȡ�ļ�ָ���λ�� ��ֵ��Ϊ�ļ���С
	this->logfileobject.seekg(curPos);               // �ָ��ļ�ָ��λ��
	return static_cast<size_t>(pos);
}

//д��־ 
void Outputlog::OutputlogByString(char    * pString){
	if (FALSE == this->logOpenFileSuccess || NULL == pString){ return; }

	string tNowlogStr = logGetNowTime();
	//[1000 - 00 - 00 00:00:00] :  ��ǰ�� ��־����
	tNowlogStr = "[" + tNowlogStr + "] : ";
	tNowlogStr = tNowlogStr + pString;
	tNowlogStr = tNowlogStr + _r_n;
	this->logfileobject.write(tNowlogStr.c_str(), tNowlogStr.size());
	//ˢ�� �ļ���
	this->logfileobject.flush();
};

void Outputlog::OutputlogByString(wchar_t * pString){
	if (FALSE == this->logOpenFileSuccess || NULL == pString){ return; }
	char tNowlogStr[1024] = { NULL };
	if (false == logwchar_t_Char(pString, tNowlogStr, 1020)){
		return;
	}
	return OutputlogByString(tNowlogStr);
};

void Outputlog::OutputlogByFormat(char    * pFormat, ...){
	if (FALSE == this->logOpenFileSuccess || NULL == pFormat){ return; }
	char tNowlogStr[1024] = { NULL };
	va_list args;
	va_start(args, pFormat);
	vsnprintf_s(tNowlogStr, 1024, pFormat, args);
	va_end(args);
	return OutputlogByString(tNowlogStr);
};

void Outputlog::OutputlogByType(OutputType tOutputType, void * pOutputinfo){
	if (FALSE == this->logOpenFileSuccess){ return; }
	string tNowlogStr = "";
	char   tStrBuffer[200] = { NULL };
	switch (tOutputType){
		case outTimeType:{
			tNowlogStr = logGetNowTime();
			tNowlogStr = "[" + tNowlogStr + "] : ";
		}break;
		case outDwordType:{
			sprintf_s(tStrBuffer, 200, "%d", *(DWORD*)pOutputinfo);
			tNowlogStr = tStrBuffer;
		}break;
		case outcharType:{
			tNowlogStr = (char*)pOutputinfo;
		}break;
		case outWchar_tType:{
			if (false == logwchar_t_Char((wchar_t*)pOutputinfo, tStrBuffer,200)){
				return;
			}
			tNowlogStr = tStrBuffer;
		}break;
		case outEndType:{
			tNowlogStr = _r_n;
		}break;
		default:
		return;
		break;
	}

	//д���ļ���
	this->logfileobject.write(tNowlogStr.c_str(), tNowlogStr.size());
	//ˢ�� �ļ���
	this->logfileobject.flush();
}

void Outputlog::OutputlogByByte(byte * pByte, DWORD ByteSize, DWORD OneLineSize, BOOL ShowStr){
	if (FALSE == this->logOpenFileSuccess || NULL == pByte || NULL == ByteSize || NULL == OneLineSize){ return; }
	
	std::auto_ptr<byte> lineByteBuffer(new byte[OneLineSize + 1]);
	
	DWORD tLineMunber = (ByteSize / OneLineSize) + 1;
	for (size_t i = 0; i < tLineMunber; i++){
		//��ʼ���ڴ�,���ҿ���һ�����ݵ��ڴ���
		ZeroMemory(lineByteBuffer.get(), sizeof(byte)* (OneLineSize + 1));
		CopyMemory(lineByteBuffer.get(), pByte + i * OneLineSize, OneLineSize);

		string tNowlogStr = "";
		//�������ֽ� ��ӡ�� �ַ�����
		for (size_t j = 0; j < OneLineSize; j++){
			char tByteStr[5] = { NULL };
			wsprintfA(tByteStr, "%02X ", lineByteBuffer.get()[j]);
			tNowlogStr = tNowlogStr + tByteStr;
		}

		if (FALSE == ShowStr){ goto GoToSave; }
		//������\0,ת�� .
		for (size_t j = 0; j < OneLineSize; j++){
			if ('\0' == (char)lineByteBuffer.get()[j]){
				lineByteBuffer.get()[j] = '.';
			}
		}
		tNowlogStr = tNowlogStr + "     ";
		tNowlogStr = tNowlogStr + (char*)lineByteBuffer.get();
GoToSave:
		tNowlogStr = tNowlogStr + _r_n;
		this->logfileobject.write(tNowlogStr.c_str(), tNowlogStr.size());
	}
	this->logfileobject.flush();//ˢ�� �ļ���
}




