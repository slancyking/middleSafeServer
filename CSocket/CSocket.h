// Created by MsNiu on 2018/7/28.
#ifndef ANDROIDPOOK_CSOCKET_H
#define ANDROIDPOOK_CSOCKET_H
//
//#include <windows.h> //默认的window标准API函数头文件

#include <WinSock2.h> //windows.h 已经包含了此头文件所以只需要导入静态库

//#include <winsock.h>//无用 做下记录
#include <ws2tcpip.h>

#pragma comment(lib,"Ws2_32")//用于网络连接、Sock

#define SOCKET_ERROR            (-1)
//
#include <memory>
//
#include <list>
//
#include <map>
//
#include <string>
//
using namespace std;
//
#include "..//CRejection//CRejection.h"


class CSocketClient {

    public: CSocketClient();
    public: CSocketClient(int socketID);
    public: ~CSocketClient();

    public: bool connect(const char *  ip, int prot);
    public: bool Sockopt(int optname, int OutTime);
    public: bool Recv(char * buffer, unsigned int buflen, unsigned int outtime);
    public: bool Send(char * buffer, unsigned int  buflen, unsigned int  outtime);

	public: void * XRecv(unsigned int & buflen, unsigned int outtime);
	public: bool   XSend(BYTE * buffer, unsigned int  buflen, unsigned int  outtime);
	public: bool   XSendString(char * buffer, unsigned int  outtime);
	public: bool   XSendString(std::string & buffer, unsigned int  outtime);


			

    public: bool ReadStatus(){ return this->gConnectStatus;};

	public: int ReadError() { return this->gErrorCode; };

    public: void Close();

    public: int ReadSocket() { return this->gSocketBuffer; };


private:
    bool       gConnectStatus  = false;
    int        gSocketBuffer = 0;
	int        gErrorCode = 0;

	bool       gDisConnect = true;


	char *     gXRecvBuffer      = NULL;
	int        gXRecvBufferLenth = 0;
};


struct _tagClientINFO {
	int		_socket;

	DWORD   _thread;
};


class CSocketServer
{
public:
	CSocketServer();
	~CSocketServer();

private:
	int		_socket = 0;
	int		_proc = 0;

	int			_errCode = 0;
	std::string _errString = "";

	HANDLE   _thread_acc	= 0;                                                                //记录 主线程句柄
	DWORD    _thread_acc_id = 0;                                                                //记录 主线程id  

	CRejection    _clientMutex;

	std::map<int, _tagClientINFO>  _clientLIST;

	bool(*callback_Accept)(int socketID, char * ip, int port) = NULL;
	void(*callback_Recv)(int socketID, void * buffer, int len) = NULL;
	void(*callback_Close)(int socketID, int quitCode) = NULL;
	void(*callback_Error)(int socketID, int errCode, const char * errString) = NULL;
	void(*callback_Journal)(int socketID, const char * JournalString) = NULL;


	//线程回调, 禁止使用
public: void acceptClient();
public: void clientRecv(int socketID);

public:
	void writeClientBuffer(int socketID, _tagClientINFO wBuffer);

	int thread2socket(DWORD _thread);

public:
	void bindProc(int proc) { this->_proc = proc; }

	bool start(int sendSize = 0, int recvSize = 0);
	void close();
	void closeClient(int _socket = 0);

	int err();

	const char * errString();

	void addCallbackByAccept(bool(*callback)(int socketID, char * ip, int port)) {
		callback_Accept = callback;
	}

	void addCallbackByRecv(void(*callback)(int socketID, void * buffer, int len)) {
		callback_Recv = callback;
	}

	void addCallbackByClose(void(*callback)(int socketID, int quitCode)) {
		callback_Close = callback;
	}

	void addCallbackByError(void(*callback)(int socketID, int errCode, const char * errString)) {
		callback_Error = callback;
	}

	void addCallbackByJournal(void(*callback)(int socketID, const char * JournalString)) {
		callback_Journal = callback;
	}

private:
	void call_error(int socketID, int errCode);
	void call_journal(int socketID, const char * fString, ...);

public:
	static int Send(int socketID, const void * buffer, int sendLenth);
	static int XSend_buffer(int socketID, const void * buffer, int sendLenth);
	static int XSend(int socketID, const char * buffer);
	static int XSend(int socketID, std::string buffer) {
		return CSocketServer::XSend(socketID, buffer.c_str());
	}



public:
	static int Recv(int socketID, void * buffer, int buflen, unsigned long outtime);
	static void * XRecv(int socketID, unsigned int & rlenth, int & errCode);
	 
};
 

#endif //ANDROIDPOOK_CSOCKET_H
