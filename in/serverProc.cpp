#include "pch.h"
#include "serverProc.h"
#include "msgDef.h"

#include "socketCommon.h" 
#include "msgProtocol.h"
#include "msgProcess.h"
#include "ProcessInfoShare.h"



std::string serverProc::xKey; //������Կ
USHORT randPort;  //ͨѶ�˿�
CSocketServer mSocketServer;
int mSocketID = 0;

UINT serverProc::lastRenKeyTime = 0; //��������Կ��ʱ��
std::string serverProc::tmpRanKey; //��ʱ������Կ
UINT serverProc::reportInterval = 10 * 60;//��Կ������
int serverProc::tmpKeyIndex = 0;


CMutexRejection lockLastRecvTime; 
UINT lastRecvTime = std::time(0);
UINT recvTimeout = 5 * 60;

void serverProc::updateLastRecvTime()
{
	lockLastRecvTime.OpenRejection();
	lastRecvTime = std::time(0);
	lockLastRecvTime.CloseRejection();
}

bool serverProc::cb_accept(int socketID, char* ip, int port)
{
	if (mSocketID == 0) {
		mSocketID = socketID;
		return true;
	} 
	return false;
}

void serverProc::cb_recv(int socketID, void* buffer, int len)
{
	recvMsgProtocol newMsg(buffer, len);
	string strMsg = newMsg.getMsg(xKey);
	OutputDebugStringA(format("���յ���Ϣ:{}", strMsg).c_str());
	Json::Reader _reader;
	Json::Value _root;
	_reader.parse(strMsg, _root, false);
	 
	string retMsg = msgProcess::msgEventProcess(_root, newMsg.header->uTime);
	OutputDebugStringA(format("��Ϣ������:{}", retMsg).c_str());
	sendMsgProtocol encryptedMsg(retMsg, xKey);
	UINT msgSize = 0;
	void* msgBuffer = encryptedMsg.getData(msgSize);

	mSocketServer.XSend_buffer(socketID, msgBuffer, msgSize);
	updateLastRecvTime();
}

void serverProc::cb_close(int socketID, int quitCode)
{
	mSocketID = 0;
}

void serverProc::cb_error(int socketID, int errCode, const char* errString)
{

}

void serverProc::cb_log(int socketID, const char* JournalString)
{
	OutputDebugStringA(format("socket id:{} Log: {}\r\n", socketID, JournalString).c_str());
}
  
bool serverProc::init()
{
	xKey = rand_str(0x20);
	randPort = socketCommon::getRandPortUnuse();
	lastRenKeyTime = std::time(0);
	mSocketServer.bindProc(randPort);
	 
	mSocketServer.addCallbackByAccept(cb_accept);
	mSocketServer.addCallbackByRecv(cb_recv);
	mSocketServer.addCallbackByClose(cb_close);
	mSocketServer.addCallbackByError(cb_error);
	mSocketServer.addCallbackByJournal(cb_log);
	 
	msgProcess::regMsgProcess(); //ע����Ϣ�ص�

	return true;
} 
DWORD serverProc::thread_run(void*  pra)
{
	mSocketServer.start(); 
	  
	while (true)
	{
		if (std::time(0) - lastRecvTime > recvTimeout)
		{
			OutputDebugStringA("ͨѶ��ʱ!");
			break;
		} 

		if (std::time(0) - lastRenKeyTime > reportInterval) { 
			if (tmpRanKey != "" && tmpRanKey != xKey) {
				OutputDebugStringA("��Կû����!");
				break;
			}
			lastRenKeyTime = std::time(0);
			tmpKeyIndex = rand();
			tmpRanKey = rand_str(0x20);
			//���浽������
			tagServerReportQuery spq;
			spq.flag = format("{}", GetCurrentProcessId());
			spq.keyIndex = tmpKeyIndex;
			spq.randomKey = tmpRanKey;
			spq.randomPort = randPort;
			tagServerResponse result = safeServer.normalReport(spq);
			if (result.code != 0) {
				OutputDebugStringA(format("�����쳣! ����:{} ,��Ϣ:{}", result.code, result.info).c_str());
				return false;
			}

		}


		Sleep(50);
	}
	return 0;
}
bool serverProc::run()
{
	CreateThread(NULL, 1024, thread_run, NULL, NULL, NULL);

	if (!safeServer.getLoginStatus()) {
		return false;
	}

	//���浽������
	tagServerReportQuery spq;
	spq.flag = format("{}", GetCurrentProcessId());
	spq.keyIndex = 0;
	spq.randomKey = xKey;
	spq.randomPort = randPort;
	tagServerResponse result = safeServer.normalReport(spq);
	if (result.code != 0) {
		OutputDebugStringA(format("�����쳣! ����:{} ,��Ϣ:{}", result.code, result.info).c_str());
		return false;
	}
	
	Sleep(1000);

	ProcessInfoShare::writeProcessId(GetCurrentProcessId());

	return true;

}