#include "CRegedit.h"







CRegedit::CRegedit(HKEY hKey, char * pItemPath){
	if (ERROR_SUCCESS != ::RegOpenKeyExA(hKey, pItemPath, NULL, KEY_ALL_ACCESS, &this->m_hk) && ERROR_SUCCESS != ::RegCreateKeyA(hKey, pItemPath, &this->m_hk)){
		this->m_OpenSuccess = FALSE;
		return;
	}
	this->m_OpenSuccess = TRUE;
}

CRegedit::CRegedit(HKEY hKey, wchar_t * pItemPath){
	if (ERROR_SUCCESS != ::RegOpenKeyExW(hKey, pItemPath, NULL, KEY_ALL_ACCESS, &this->m_hk) && ERROR_SUCCESS != ::RegCreateKeyW(hKey, pItemPath, &this->m_hk)){
		this->m_OpenSuccess = FALSE;
		return;
	}
	this->m_OpenSuccess = TRUE;
}

CRegedit::~CRegedit(){
	if (TRUE == this->m_OpenSuccess && NULL != this->m_hk){
		RegCloseKey(this->m_hk);
	}
}


//获取某项下的指定数据类型
DWORD CRegedit::GetItemDatatype(char * pDataname){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD ttype;
	DWORD lsize;
	if (ERROR_SUCCESS != RegQueryValueExA(this->m_hk, pDataname, NULL, &ttype, NULL, &lsize)){
		return NULL;
	}

	return ttype;
}

DWORD CRegedit::GetItemDatatype(wchar_t * pDataname){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD ttype;
	DWORD lsize;
	if (ERROR_SUCCESS != RegQueryValueExW(this->m_hk, pDataname, NULL, &ttype, NULL, &lsize)){
		return NULL;
	}

	return ttype;
}

//获取某项下的指定数据长度
DWORD CRegedit::GetItemDatasize(char * pDataname){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD lsize;
	if (ERROR_SUCCESS != RegQueryValueExA(this->m_hk, pDataname, NULL, NULL, NULL, &lsize)){
		return NULL;
	}
	
	return lsize;
}

DWORD CRegedit::GetItemDatasize(wchar_t * pDataname){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD lsize;
	if (ERROR_SUCCESS != RegQueryValueExW(this->m_hk, pDataname, NULL, NULL, NULL, &lsize)){
		return NULL;
	}

	return lsize;
}

//获取某项下的指定数据
DWORD CRegedit::GetItemData(char * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD lsize = *lpvaluelen;
	if (ERROR_SUCCESS != RegQueryValueExA(this->m_hk, pDataname, NULL, NULL, lpvalue, &lsize)){
		return NULL;
	}
	*lpvaluelen = lsize;
	return lsize;
}

DWORD CRegedit::GetItemData(wchar_t * pDataname, BYTE * lpvalue, __inout DWORD * lpvaluelen){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){
		return NULL;
	}
	DWORD lsize = *lpvaluelen;
	if (ERROR_SUCCESS != RegQueryValueExW(this->m_hk, pDataname, NULL, NULL, lpvalue, &lsize)){
		return NULL;
	}
	*lpvaluelen = lsize;
	return lsize;
}


//设置一个 注册表数据
BOOL CRegedit::SetItemData(char * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){ return FALSE; }
	if (ERROR_SUCCESS != RegSetValueExA(this->m_hk, pDataname, NULL, type, (BYTE *)lpvalue, valuelen)){
		return FALSE;
	}
	return TRUE;
}

BOOL CRegedit::SetItemData(wchar_t * pDataname, DWORD type, void * lpvalue, __inout DWORD valuelen){
	if (FALSE == this->m_OpenSuccess || NULL == this->m_hk){ return FALSE; }
	if (ERROR_SUCCESS != RegSetValueExW(this->m_hk, pDataname, NULL, type, (BYTE *)lpvalue, valuelen)){
		return FALSE;
	}
	return TRUE;
}