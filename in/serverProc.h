#pragma once
#include "../CSocket/CSocket.h"


namespace serverProc
{  

	bool run();
	bool init();

	DWORD thread_run(void* pra);

	bool cb_accept(int socketID, char* ip, int port);
	void cb_recv(int socketID, void* buffer, int len);
	void cb_close(int socketID, int quitCode);
	void cb_error(int socketID, int errCode, const char* errString);
	void cb_log(int socketID, const char* JournalString);


	void updateLastRecvTime();

	extern std::string xKey;


	extern  UINT lastRenKeyTime; //��������Կ��ʱ��
	extern std::string tmpRanKey; //��ʱ������Կ
	extern UINT reportInterval;//��Կ������
	extern int tmpKeyIndex;
};
 