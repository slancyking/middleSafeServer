
#pragma once
#include "CRejection.h"


CRejection::CRejection(){
	InitializeCriticalSection(&this->NowRejection);
}


CRejection::~CRejection(){
	DeleteCriticalSection(&this->NowRejection);//ɾ���ٽ���
}

void CRejection::OpenRejection(){
	EnterCriticalSection(&this->NowRejection);
}

void CRejection::CloseRejection(){
	LeaveCriticalSection(&this->NowRejection);
}

BOOL CRejection::IsCanEnter(){
	return (-1 == this->NowRejection.LockCount);
}


void CRejection::Initialization() {
	DeleteCriticalSection(&this->NowRejection);//ɾ���ٽ���
	InitializeCriticalSection(&this->NowRejection);
}


CMutexRejection::CMutexRejection(wchar_t * name){
	this->hMemoryMutex = CreateMutexW(NULL, FALSE, name);
}

CMutexRejection::~CMutexRejection(){


}


BOOL CMutexRejection::CreateRejection(char * pMutexNameString){
	if (NULL != this->hMemoryMutex || NULL == pMutexNameString){ return FALSE; }
	this->hMemoryMutex = CreateMutexA(NULL, FALSE, pMutexNameString);
	if (NULL == this->hMemoryMutex){ return FALSE; }
	return TRUE;
}


void CMutexRejection::OpenRejection(){
	if (NULL == this->hMemoryMutex){ return; }
	WaitForSingleObject(this->hMemoryMutex, INFINITE);//���� ������
}

void CMutexRejection::CloseRejection(){
	if (NULL == this->hMemoryMutex){ return; }
	ReleaseMutex(this->hMemoryMutex);//�˳� ������
}