#pragma once
#include <windows.h>


class CRegedit{
public:
	//Ĭ�ϵ� ��ʼע��� HKEY_
	CRegedit(HKEY hKey, char * pItemPath);
	CRegedit(HKEY hKey, wchar_t * pItemPath);
	~CRegedit();

	//��ȡĳ���µ�ָ����������
	DWORD GetItemDatatype(char * pDataname);
	DWORD GetItemDatatype(wchar_t * pDataname);

	//��ȡĳ���µ�ָ�����ݳ���
	DWORD GetItemDatasize(char * pDataname);
	DWORD GetItemDatasize(wchar_t * pDataname);

	//��ȡĳ���µ�ָ������
	DWORD GetItemData(char * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen);
	DWORD GetItemData(wchar_t * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen);


	
	//����һ�� ע�������
	BOOL SetItemData(char * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen);
	BOOL SetItemData(wchar_t * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen);




private://�ڲ�

	BOOL m_OpenSuccess = FALSE; //���캯�� �Ƿ�ɹ�
	HKEY m_hk = NULL;           //�򿪵ľ��
};
