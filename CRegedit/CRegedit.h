#pragma once
#include <windows.h>


class CRegedit{
public:
	//默认的 起始注册表 HKEY_
	CRegedit(HKEY hKey, char * pItemPath);
	CRegedit(HKEY hKey, wchar_t * pItemPath);
	~CRegedit();

	//获取某项下的指定数据类型
	DWORD GetItemDatatype(char * pDataname);
	DWORD GetItemDatatype(wchar_t * pDataname);

	//获取某项下的指定数据长度
	DWORD GetItemDatasize(char * pDataname);
	DWORD GetItemDatasize(wchar_t * pDataname);

	//获取某项下的指定数据
	DWORD GetItemData(char * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen);
	DWORD GetItemData(wchar_t * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen);


	
	//设置一个 注册表数据
	BOOL SetItemData(char * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen);
	BOOL SetItemData(wchar_t * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen);




private://内部

	BOOL m_OpenSuccess = FALSE; //构造函数 是否成功
	HKEY m_hk = NULL;           //打开的句柄
};
