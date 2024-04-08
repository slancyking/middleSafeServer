// Created by MsNiu on 2018/7/28.
#include "CSocket.h"  

CSocketClient::CSocketClient(){
	//需要预先初始化 socket
	this->gSocketBuffer = NULL;

	WSADATA wsaData = { 0 };
	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData)){
		this->gErrorCode = WSAGetLastError();
		return ;
	}

	this->gDisConnect = true;
}

CSocketClient::CSocketClient(int socketID){
	this->gErrorCode = NULL;
	this->gSocketBuffer = socketID;
	this->gConnectStatus = true;

	this->gDisConnect = false;
}


CSocketClient::~CSocketClient(){
    if (0 >= this->gSocketBuffer){ return ; }
	
	if (true == this->gDisConnect)
		this->Close();

	if (NULL != this->gXRecvBuffer)
		delete this->gXRecvBuffer;
	
	//WSACleanup();
}

//连接 服务器
bool CSocketClient::connect(const char * ip, int prot){
	this->gErrorCode = 0;

	if (0 >= (this->gSocketBuffer = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))) {
		this->gErrorCode = WSAGetLastError();
		return false;
	}

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(sockaddr_in));

	struct in_addr addr;
	inet_pton(AF_INET, ip, &addr);


    serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr = addr;// .s_addr = inet_addr(ip); //IP地址
    serverAddr.sin_port = htons(prot);//端口

    if (SOCKET_ERROR == ::connect(this->gSocketBuffer, (const sockaddr *)&serverAddr, sizeof(sockaddr))){
		this->gErrorCode = WSAGetLastError();
		this->Close();
        return false;
    }
    this->gConnectStatus = true;
    return true;
}

//设置  套接字  属性值
bool CSocketClient::Sockopt(int optname, int OutTime){
    if (0 >=  this->gSocketBuffer || NULL == OutTime){ return false; }
    if (SOCKET_ERROR == ::setsockopt(this->gSocketBuffer, SOL_SOCKET, optname, (char *)&OutTime, sizeof(int))){
		this->gErrorCode = WSAGetLastError();
        return false;
    }

    return true;
}

bool CSocketClient::Send(char * buffer, unsigned int  buflen, unsigned int outtime){
    if (0 >=  this->gSocketBuffer || NULL == buffer){ return false; }

	unsigned long  tStartTimeBuffer  = GetTickCount();
    long           tCurrentSendLenth = NULL;

    while (GetTickCount() - tStartTimeBuffer <= outtime){
        char * pbuffer = (char *)&buffer[tCurrentSendLenth];
        int    bufferlen = buflen - tCurrentSendLenth;

        int    tsendlen = ::send( this->gSocketBuffer , pbuffer, bufferlen, 0);
		if (SOCKET_ERROR == tsendlen) { this->gErrorCode = WSAGetLastError(); }
        if (0 >= tsendlen){ return false; } //-1 发送失败, 0 链接中断

        tCurrentSendLenth += tsendlen;

		if ((long)buflen <= tCurrentSendLenth){
            return true;
        }
		Sleep(1);
    }
    return false;
}

bool   CSocketClient::XSend(BYTE * buffer, unsigned int  buflen, unsigned int  outtime) {
	if (0 >= this->gSocketBuffer || NULL == buffer) { return false; }

	std::unique_ptr< BYTE > tSendBuffer(new BYTE[buflen + 4]);
	if (NULL == tSendBuffer.get() || NULL == buffer)
		return false;

	memset(tSendBuffer.get(), 0, buflen + 4);
	CopyMemory(tSendBuffer.get() + 0, &buflen, 4);
	CopyMemory(tSendBuffer.get() + 4, buffer, buflen);

	return this->Send((char *)tSendBuffer.get(), buflen + 4, outtime);
}

bool  CSocketClient::XSendString(char * buffer, unsigned int  outtime) {
	return this->XSend((BYTE*)buffer, strlen(buffer) + 1, outtime);
}

bool  CSocketClient::XSendString(std::string & buffer, unsigned int  outtime) {
	return this->XSendString((char * )buffer.c_str(), outtime);
}

bool CSocketClient::Recv(char * buffer, unsigned int buflen, unsigned int outtime) {
	if (0 >= this->gSocketBuffer || NULL == buffer) { return false; }

	unsigned long  tStartTimeBuffer = GetTickCount();
	long           tCurrentRecvLenth = NULL;

	while (GetTickCount() - tStartTimeBuffer <= outtime) {
		char * pbuffer = (char *)&buffer[tCurrentRecvLenth];
		int    bufferlen = buflen - tCurrentRecvLenth;

		int    trecvlen = ::recv(this->gSocketBuffer, pbuffer, bufferlen, 0);

		if (SOCKET_ERROR == trecvlen) { this->gErrorCode = WSAGetLastError(); }
		if (0 >= trecvlen) {
			return false;
		} //-1 接收失败, 0 链接中断

		tCurrentRecvLenth += trecvlen;

		if ((long)buflen <= tCurrentRecvLenth) { 
			return true;
		}

		Sleep(1);
	}

	return false;
}

void * CSocketClient::XRecv(unsigned int & buflen, unsigned int outtime) {
	if (0 >= this->gSocketBuffer || false == this->gConnectStatus)
		return NULL;

	int t_bufferLen = 0;
	int t_recvLenth = 0;
	int t_errCodeBuffer = 0;
	int t_startTimeBuffer = GetTickCount();

	do
	{
		Sleep(1);
		  
		//先获取到头的长度
		if (-1 == (t_recvLenth = recv(this->gSocketBuffer, (char *)&t_bufferLen, 4, MSG_PEEK))) {
			this->gErrorCode = WSAGetLastError();
			return NULL;
		}
		//不存在数据, 继续等待
		if (0 == t_bufferLen || 4 > t_recvLenth)
			continue;

		if (NULL != this->gXRecvBuffer) {
			delete this->gXRecvBuffer;
		}
		this->gXRecvBuffer = new char[(4 >= t_bufferLen ? 4 : t_bufferLen) + 1];
		memset(this->gXRecvBuffer, 0, (4 >= t_bufferLen ? 4 : t_bufferLen) + 1);

		//获取真实的数据包
		if (false == this->Recv((char *)&t_bufferLen, 4, outtime)) {
			return NULL;
		}

		if (false == this->Recv(this->gXRecvBuffer, t_bufferLen, outtime)) {
			return NULL;
		}
		buflen = t_bufferLen;
		return this->gXRecvBuffer;

	} while (GetTickCount() - t_startTimeBuffer <= outtime);

	this->gErrorCode = 99999;
	return NULL;
}

#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

void CSocketClient::Close() {

	if (0 != this->gSocketBuffer)
		shutdown(this->gSocketBuffer, SD_BOTH);

	if (0 != this->gSocketBuffer)
		closesocket(this->gSocketBuffer);

    this->gSocketBuffer = NULL;
    this->gConnectStatus = false;
}


CSocketServer::CSocketServer() {
	
}

CSocketServer::~CSocketServer() {


}


void CSocketServer::call_error(int socketID, int errCode) {
	char _eString[1024] = { NULL };
	strerror_s(_eString, 1020, errCode);

	_errCode	= errCode;
	_errString	= _eString;

	if (NULL == this->callback_Error) return;

	this->callback_Error(socketID, _errCode, _errString.c_str());
}

void CSocketServer::call_journal(int socketID, const char * fString, ...) {
	int _sSize = 0;

	if (NULL == this->callback_Journal) return;

	va_list arglist;
	va_start(arglist, fString);
	if (0 >= (_sSize = vsnprintf(NULL, 0, fString, arglist))) {
		va_end(arglist);
		return;
	}

	std::unique_ptr<char >IsStringBuffer(new char[_sSize + 2]);
	memset(IsStringBuffer.get(), 0, sizeof(char) * (_sSize + 2));

	vsnprintf(IsStringBuffer.get(), _sSize + 1, fString, arglist);

	va_end(arglist);

	//__android_log_print(ANDROID_LOG_DEBUG, _tagKEY, s)

	return this->callback_Journal(socketID, IsStringBuffer.get());
}


int CSocketServer::err() {
	return _errCode;
}

const char * CSocketServer::errString() {
	return _errString.c_str();
}

template <typename TYPE, void (TYPE::*acceptClient)() >
DWORD WINAPI _thread_accept(LPVOID lpThreadParameter) {//线程启动函数，声明为模板函数  
	CSocketServer* This = (CSocketServer*)lpThreadParameter;
	This->acceptClient();
	return NULL;
}

bool CSocketServer::start(int sendSize, int recvSize) {
	if (0 != _socket) this->close();

	WSADATA wsaData = { 0 };
	if (0 != WSAStartup(MAKEWORD(2, 1), &wsaData)) {
		int err = WSAGetLastError(); 
		this->call_error(1, err); 
		return false;
	}


	if (0 == (_socket = socket(AF_INET, SOCK_STREAM, 0))) {
		this->call_error(0, errno);
		return false;
	}
	struct linger t_linger;

	t_linger.l_onoff = 1;
	t_linger.l_linger = 0;

	setsockopt(_socket, SOL_SOCKET, SO_LINGER, (const char*)&t_linger, sizeof(struct linger));

	int t_reuseaddr = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&t_reuseaddr, sizeof(int));

	if (0 != sendSize) setsockopt(_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&sendSize, sizeof(int));
	if (0 != recvSize) setsockopt(_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&recvSize, sizeof(int));

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_proc);
	addr.sin_addr.s_addr = INADDR_ANY; //

	if (0 != bind(_socket, (const struct sockaddr *)&addr, sizeof(addr))) {
		this->call_error(_socket, errno);
		this->close();
		return false;
	}

	this->call_journal(_socket, "创建socket完毕, 开始接收新客户端连接...");

	listen(_socket, 50);

	if (NULL == (this->_thread_acc = CreateThread(NULL, 0, _thread_accept<CSocketServer, &CSocketServer::acceptClient>, this, CREATE_SUSPENDED, &this->_thread_acc_id))){
		this->call_error(_socket, errno);
		this->close();
		return false;
	};

	ResumeThread(this->_thread_acc);  //上面创建的线程, 全部为<暂停>状态, 循环线程
	return true;
}

void CSocketServer::clientRecv(int socketID) {
	UINT t_recvLenth = 0;
	void * t_buffer = NULL;
	int    t_errCode = 0;

	this->call_journal(socketID, "客户端Socket, 开始接收数据流程...");

	while (0 != socketID && 0 == t_errCode) {
		if (NULL != t_buffer) { free(t_buffer); t_buffer = NULL; }  //释放之前的数据缓冲区

		if (NULL != (t_buffer = CSocketServer::XRecv(socketID, t_recvLenth, t_errCode))) {
			if (NULL != this->callback_Recv) this->callback_Recv(
				socketID, t_buffer, t_recvLenth
			);
		} 
	}

	this->call_journal(socketID, "客户端Socket, 退出客户端数据数据过程...");

	if (NULL != t_buffer) free(t_buffer);

	if (NULL != this->callback_Close) this->callback_Close(
		socketID, t_errCode
	);
	this->closeClient(socketID);
}

template <typename TYPE, void (TYPE::*clientRecv)(int socketID) >
DWORD WINAPI  _thread_recv(LPVOID lpThreadParameter) {//线程启动函数，声明为模板函数  
	TYPE* This = (TYPE*)lpThreadParameter;

	int    t_clientSocket = 0;
	unsigned long  startTIME = GetTickCount();    //第一步: 等待正常添加 buffer
	while (NULL != This && GetTickCount() - startTIME < 5 * 1000) {
		t_clientSocket = This->thread2socket(GetCurrentThreadId());
		if (0 != t_clientSocket) break;
		Sleep(10);  // xx 毫秒触发一次
	}

	if (0 == t_clientSocket) return NULL;

	This->clientRecv(t_clientSocket);
	return NULL;
}

void CSocketServer::acceptClient() {
	while (NULL != this && 0 != this->_socket && this->_thread_acc_id == this->_thread_acc_id) {
		if (0 == this->_socket || 0 != this->_errCode)
			break;

		Sleep(1);  // 1毫秒触发一次

		_tagClientINFO addBuffer = { 0 };
		struct sockaddr_in addr;
		int  addrLen = sizeof(struct sockaddr_in);

		//接受新的客户端连接
		if (-1 == (addBuffer._socket = accept(this->_socket, (struct sockaddr *)&addr, &addrLen))) {
			this->call_error(this->_socket, errno);
			continue;
		}

		this->call_journal(this->_socket, "主Socket, 收到新客户端连接, socket = %d", addBuffer._socket);

		//触发回调
		do {
			if (NULL == this->callback_Accept) {
				break;
			}
			char str[INET_ADDRSTRLEN]; 
			const char* ptr = InetNtopA(AF_INET, &addr.sin_addr, str, sizeof(str)); //代替 ptr =  inet_ntoa(addr.sin_addr)

			if (false == this->callback_Accept(addBuffer._socket, (char*)ptr, ntohs(addr.sin_port))) {
				::shutdown(addBuffer._socket, SD_BOTH);
				::closesocket(addBuffer._socket);
				addBuffer._socket = 0;
			}
		} while (false);

		if (0 == addBuffer._socket) continue;

		//创建一条新的线程, 用于实时接受客户端数据, 注: 不需要管线程, 关闭后将主动释放线程
		HANDLE threadHandle = NULL;
		if (NULL == (threadHandle = CreateThread(NULL, 0, _thread_recv<CSocketServer, &CSocketServer::clientRecv>, this, CREATE_SUSPENDED, &addBuffer._thread))) {
			::shutdown(addBuffer._socket, SD_BOTH);
			::closesocket(addBuffer._socket);
			continue;
		};

		//将客户端socket添加到队列
		this->writeClientBuffer(addBuffer._socket, addBuffer);

		ResumeThread(threadHandle);  //上面创建的线程, 全部为<暂停>状态, 运行线程
		CloseHandle(threadHandle);
	}
	if (NULL != this) this->_thread_acc = NULL;
}

int CSocketServer::thread2socket(DWORD _thread) {
	int socketID = 0;

	this->_clientMutex.OpenRejection();
	for (std::map<int, _tagClientINFO>::iterator i = _clientLIST.begin(); i != _clientLIST.end(); i++) {
		if (_thread != i->second._thread)
			continue;
		socketID = i->first;
		break;
	}
	this->_clientMutex.CloseRejection();

	return socketID;
}


void CSocketServer::writeClientBuffer(int socketID, _tagClientINFO wBuffer) {
	this->_clientMutex.OpenRejection();
	if (_clientLIST.find(socketID) == _clientLIST.end()) {
		_clientLIST.insert(std::pair<int, _tagClientINFO>(
			socketID, wBuffer
			));
	}
	_clientLIST[socketID] = wBuffer;
	this->_clientMutex.CloseRejection();
}

void CSocketServer::closeClient(int _socket) {
	this->_clientMutex.OpenRejection();

	std::list<int> delSocketLIST;

	for (std::map<int, _tagClientINFO>::iterator i = _clientLIST.begin(); i != _clientLIST.end(); i++) {

		if (0 != _socket && _socket != i->first)
			continue;

		::shutdown(i->first, SD_BOTH);
		::closesocket(i->first);

		delSocketLIST.push_back(i->first);
	}

	while (0 < delSocketLIST.size() && 0 < _clientLIST.size()) {
		_clientLIST.erase(delSocketLIST.front());
		delSocketLIST.pop_front();
	}

	this->_clientMutex.CloseRejection();
}

void CSocketServer::close() {
	if (0 != _socket) ::shutdown(_socket, SD_BOTH);
	if (0 != _socket) ::closesocket(_socket);

	if (NULL != this->callback_Close) this->callback_Close(
		_socket, 0
	);

	_socket = 0;

	_errCode = 0;
	_errString = "";

	this->closeClient(0);//删除所有的客户端连接
}

 




int CSocketServer::Send(int socketID, const void * buffer, int lenth) {

	unsigned long  tStartTimeBuffer = GetTickCount();
	int            tCurrentSendLenth = 0;

	while (0 != socketID && GetTickCount() - tStartTimeBuffer <= 10 * 1000) {

		char * pbuffer = &((char *)buffer)[tCurrentSendLenth];
		int    bufferlen = lenth - tCurrentSendLenth;

		int  tsendlen = (int)send(socketID, pbuffer, (size_t)bufferlen, 0);

		if (0 >= tsendlen)  goto GotoErrorRet;

		tCurrentSendLenth += tsendlen;

		if (lenth <= tCurrentSendLenth) {
			return 0;
		}

		Sleep(1);
	}

	return 99999;
GotoErrorRet:;
	return errno;
}

int CSocketServer::XSend_buffer(int socketID, const void * buffer, int lenth) {
	int       t_sendStatus = 0;

	char * t_sendBuffer = (char *)malloc(lenth + 4);
	if (NULL == t_sendBuffer) return 77777;

	//拷贝长度
	memcpy(&t_sendBuffer[0], &lenth, 4);
	//拷贝真实内容
	memcpy(&t_sendBuffer[4], buffer, lenth);

	//发送
	t_sendStatus = CSocketServer::Send(socketID, t_sendBuffer, lenth + 4);

	free(t_sendBuffer);

	return t_sendStatus;
}

int  CSocketServer::XSend(int socketID, const char * buffer) {

	size_t lenth = strlen(buffer);

	return CSocketServer::XSend_buffer(socketID, buffer, lenth);
}



int CSocketServer::Recv(int socketID, void * buffer, int buflen, unsigned long outtime) {
	unsigned long  tStartTimeBuffer = GetTickCount();
	int            t_curBufIndex = 0;

	while (GetTickCount() - tStartTimeBuffer <= outtime) {
		char * pbuffer = &(((char *)buffer)[t_curBufIndex]);
		int    bufferlen = buflen - t_curBufIndex;

		size_t trecvlen = recv(socketID, pbuffer, bufferlen, 0);

		if (0 >= trecvlen)  return errno; //-1 接收失败, 0 链接中断

		t_curBufIndex += trecvlen;

		if ((long)buflen <= t_curBufIndex) { return 0; }

		Sleep(1);
	}

	return 99999;
}

void * CSocketServer::XRecv(int socketID, unsigned int & rlenth, int & errCode) {
	size_t  t_recvLenth = 0;
	unsigned long t_startTimeBuffer = GetTickCount();

	do {
		Sleep(1);
		 
		//第一步: 检测缓冲区中是否存在指定长度的数据
		if (-1 == (t_recvLenth = recv(socketID, (char *)&rlenth, 4, MSG_PEEK))) {
			errCode = errno;
			return NULL;
		}

		//第二步: 检测读取到的长度, 是否不符合要求
		if (0 == rlenth || 4 > t_recvLenth)
			continue;

		if (4 == t_recvLenth && 0 == rlenth) { //不会触发
			errCode = 888888;
			return NULL;
		}

		//第三步: 申请一块内存
		int    _rlenth = (rlenth < 0 ? 0 : rlenth) + 1;
		void * _XRecvBuffer = malloc(_rlenth);
		if (NULL == _XRecvBuffer) {
			errCode = 123456;
			return NULL;
		}

		//NSLog(@"--------------------------------------new buffer.size = %d, %zd!!!", t_bufferLen,  t_recvLenth);

		//第四步: 返回真实数据信息
		if (0 != (errCode = CSocketServer::Recv(socketID, &rlenth, 4, 5 * 1000))) {
			free(_XRecvBuffer);
			return NULL;
		}

		//NSLog(@"--------------------------------------new buffer.size = %d, %zd!!!, ok", t_bufferLen,  t_recvLenth);

		memset(_XRecvBuffer, 0, _rlenth);
		if (0 != (errCode = CSocketServer::Recv(socketID, _XRecvBuffer, rlenth, 10 * 1000))) {
			free(_XRecvBuffer);
			return NULL;
		}

		//NSLog(@"--------------------------------------new buffer.buffer = %d, %zd!!!, ok", t_bufferLen,  t_recvLenth);
		return _XRecvBuffer;

	} while (GetTickCount() - t_startTimeBuffer <= 60 * 1000);

	errCode = 99999;  //返回 超时
	return NULL;
}
 







