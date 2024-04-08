#pragma once

#include <Windows.h>



struct _tagShareMemoryName{
	const wchar_t  * MutexName;  //��������
	const wchar_t  * ShareName;  //ȫ���ڴ�����
};

struct _tagShareMemoryNameA{
	const char  * MutexName;  //��������
	const char  * ShareName;  //ȫ���ڴ�����
};

class ShareMemory{
public://���캯��

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]);
	//���𴴽�����������ʹ�õĹ��캯��)
	ShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize);
	
	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	ShareMemory(_tagShareMemoryName InfoName);
	//���𴴽�����������ʹ�õĹ��캯��)
	ShareMemory(_tagShareMemoryName InfoName, DWORD MemorySize);

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	ShareMemory(wchar_t ShareName[40]);
	//���𴴽�����������ʹ�õĹ��캯��)
	ShareMemory(wchar_t ShareName[40], DWORD MemorySize);

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	ShareMemory(char MutexName[50], char ShareName[50]);
	//���𴴽�����������ʹ�õĹ��캯��)
	ShareMemory(char MutexName[50], char ShareName[50], DWORD MemorySize);

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	ShareMemory(_tagShareMemoryNameA InfoName);
	//���𴴽�����������ʹ�õĹ��캯��)
	ShareMemory(_tagShareMemoryNameA InfoName, DWORD MemorySize);

	ShareMemory();
	~ShareMemory();


public://һЩ���������,ʹ�õ� ��ʼ������

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	BOOL InitShareMemory(wchar_t ShareName[40]);
	//���𴴽�����������ʹ�õĹ��캯��)
	BOOL InitShareMemory(wchar_t ShareName[40], DWORD MemorySize);

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	BOOL InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50]);
	//���𴴽�����������ʹ�õĹ��캯��)
	BOOL InitShareMemory(wchar_t MutexName[50], wchar_t ShareName[50], DWORD MemorySize);

	//�����𴴽�(�����˸��𴴽�ʱʹ�õĹ��캯��)
	BOOL InitShareMemory(DWORD ShareType, DWORD64 ShareMark);
	//���𴴽�����������ʹ�õĹ��캯��)
	BOOL InitShareMemory(DWORD ShareType, DWORD64 ShareMark, DWORD MemorySize);

	//��� ȫ���ڴ�  ���ں����ظ�ʹ��
	BOOL DeleteShareMemory();

	//��ȡ״̬,����Ƿ��Ѿ��ɹ�����
	BOOL CreateFisinh();
public://��д����

	//��ȡһ���ڴ�
	BOOL ReadMemory(__out void * outinfo, __in DWORD ReadSize);
	//д��һ���ڴ�
	BOOL WriteMemory(__in void * ininfo, __in DWORD WriteSize);

private:
	//�ڴ�Ļ���
	wchar_t MemoryMutexName[55];
	//�ڴ������
	wchar_t MemoryName[55];
	//�ڴ��ļ����
	HANDLE hMemoryFileMap = NULL;
	//�ڴ��ļ����
	HANDLE hMemoryMutex = NULL;
	//�Ƿ��ʼ�� ����
	BOOL  InitMemoryFisinh = FALSE;
};

