#pragma once
#include <list>
 
namespace networkVerifycation
{
#pragma pack(push,1)
	struct tagProcessInfoReport
	{
		char key[0x22] = { 0 };
		USHORT port = 0;
		DWORD processId = 0;
		time_t startTime = 0;
		tagProcessInfoReport() {}
		tagProcessInfoReport(std::string _key, USHORT _port, DWORD _processID) : port(_port), processId(_processID) {
			startTime = std::time(0);
			if (_key.length() != 0x20)
				return;
			strcpy_s(key, _key.data());
		}
	};
#pragma pack(pop)
	tagProcessInfoReport getKeyPort(DWORD pid);

	void removeClient(DWORD pid);
	 
	std::list<DWORD> getClients();

	std::string getClientPath();

	/// <summary>
	/// 删除本次报告记录
	/// </summary>
	/// <param name="key"></param>
	/// <param name="port"></param>
	/// <param name="processID"></param>
	/// <returns></returns>
	bool deleteKeyPort( DWORD processID);
}