#include "ProcessInfoShare.h"
#include "../CRejection/CRejection.h"
#include <format>

ShareMemory __middle_server__processID((char*)"__middle_server__processID_mutex", (char*)"__middle_server__processID",sizeof(DWORD));
CMutexRejection _middle_server_pid_option_mutex((WCHAR*)L"_middle_server_pid_option_mutex");
DWORD ProcessInfoShare::getClientPid()
{ 
	DWORD result;
	_middle_server_pid_option_mutex.OpenRejection();

	__middle_server__processID.ReadMemory(&result, sizeof(DWORD));
	OutputDebugStringA( std::format("ClientPid:{}\r\n", result).c_str());

	if (result != 0)
	{
		DWORD newRes = 0;
		__middle_server__processID.WriteMemory(&newRes, sizeof(DWORD));
	}
		
	_middle_server_pid_option_mutex.CloseRejection();

	return result;
}
