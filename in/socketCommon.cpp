#include "pch.h" 
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "socketCommon.h"


bool socketCommon::GetSocketPortState(USHORT nPort)
{ 
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(nPort);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	if (WSAGetLastError() == WSAEADDRINUSE)
	{
		//端口已被占用
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

USHORT socketCommon::getRandPortUnuse()
{
	USHORT p = 0;
	
	for (UINT i = 0; i < 10086; i++)
	{
		p = ((rand() << 15) + rand()) % (1 << 16);
		if (!GetSocketPortState(p))
			break;
	} 
	return p;
}
