#pragma once
#include <windows.h>




class CRejection{
public:
	CRejection();
	~CRejection();
	void OpenRejection();
	void CloseRejection();

	BOOL IsCanEnter();

	void Initialization();

private:
	CRITICAL_SECTION NowRejection;         //互斥对象
};


template<class _CrTypeT>
class CrType{
private:
	_CrTypeT _value;
	CRITICAL_SECTION Rejection;         //互斥对象

public:
	CrType(_CrTypeT value){
		InitializeCriticalSection(&this->Rejection);
		EnterCriticalSection(&this->Rejection);
		_value = value;
		LeaveCriticalSection(&this->Rejection);
	};

	~CrType(){ DeleteCriticalSection(&this->Rejection); }//删除临界区

	operator _CrTypeT() throw(){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue;
	}

	bool operator ==(_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue == cpv;

	};
	bool operator !=(_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue != cpv;

	};
	bool operator > (_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue > cpv;

	};
	bool operator < (_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue < cpv;
	};
	bool operator >=(_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue >= cpv;

	};
	bool operator <=(_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_CrTypeT tValue = _value;
		LeaveCriticalSection(&this->Rejection);
		return tValue <= cpv;
	};
	void operator = (_CrTypeT cpv){
		EnterCriticalSection(&this->Rejection);
		_value = cpv;
		LeaveCriticalSection(&this->Rejection);
	};

};




class CMutexRejection{
public:
	CMutexRejection(wchar_t * name);
	CMutexRejection(){ };
	~CMutexRejection();


	BOOL CreateRejection(char * pMutexNameString);

	void OpenRejection();
	void CloseRejection();

	BOOL EnterRejectionStatus(){ return NULL != this->hMemoryMutex; };



	void operator = (CMutexRejection &object){
		this->hMemoryMutex = object.hMemoryMutex;
	}

private:
	HANDLE hMemoryMutex = NULL;
};


