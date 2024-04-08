#include "ProcessInfoShare.h"
#include "../CShareMemory/CShareMemory.h"
#include "../CRejection/CRejection.h"
#include <wchar.h>

ShareMemory __middle_server__processID((char*)"__middle_server__processID_mutex", (char*)"__middle_server__processID");
CMutexRejection _middle_server_pid_option_mutex((WCHAR*)L"_middle_server_pid_option_mutex");
bool ProcessInfoShare::writeProcessId(DWORD pid)
{
	DWORD result = 0;
	_middle_server_pid_option_mutex.OpenRejection();
	__middle_server__processID.ReadMemory(&result, sizeof(DWORD));

	while (result != 0)
	{
		__middle_server__processID.ReadMemory(&result, sizeof(DWORD));
		Sleep(1000);
	}
	__middle_server__processID.WriteMemory(&pid, sizeof(DWORD));
	_middle_server_pid_option_mutex.CloseRejection();
	return result;
}