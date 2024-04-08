#pragma once
//
#include "TSConfig_UE4Offset.h"
//
#include "TSConfig_UE4OffsetByUI.h"
//
#include "TScript_UnrealEngine4.h"



namespace UE4 {

	HANDLE get_hProcess() {
		static HANDLE rValue = NULL;
		if (NULL != rValue) return rValue;
		return (rValue = OpenProcess(PROCESS_VM_READ, FALSE, GetCurrentProcessId()));
	}

	BOOL readMemory(const void * pAddress, void *buffer, size_t _size) {
		size_t r_size = 0;
		if (FALSE == ReadProcessMemory(UE4::get_hProcess(), pAddress, buffer, _size, &r_size))
			return FALSE;
		return _size == r_size;
	}

	BOOL readMemory(const void * pAddress, uint64_t offset, void *buffer, size_t _size) {
		return UE4::readMemory((const void *)((uint64_t)pAddress + offset),
			buffer, _size
		);
	}

	BOOL read_text_range(uint8_t ** start, uint8_t ** end) {
		static uint8_t * text_startBuffer = NULL;
		static uint8_t * text_endBuffer = NULL;
		if (NULL != text_startBuffer && NULL != text_endBuffer) {
			*start = text_startBuffer;
			*end = text_endBuffer;
			return TRUE;
		}
		static HANDLE _baseMoudle = 0;
		if (NULL == _baseMoudle) _baseMoudle = GetModuleHandle(NULL);
		if (NULL == _baseMoudle) return FALSE;

		text_startBuffer = (uint8_t *)_baseMoudle;
		text_startBuffer += 0x0000000000001000;
		text_endBuffer = (uint8_t *)text_startBuffer;
		text_endBuffer += TEXTSectionEND;

		*start	= text_startBuffer;
		*end	= text_endBuffer;
		return TRUE;
	}

	BOOL enter_text_range(void * address) {
		uint8_t * text_startBuffer = NULL;
		uint8_t * text_endBuffer = NULL;
		if (FALSE == UE4::read_text_range(&text_startBuffer, &text_endBuffer)) {
			return FALSE;
		}
		if ((long long)text_startBuffer > (long long)address) {
			return FALSE;
		}
		if ((long long)text_endBuffer < (long long)address) {
			return FALSE;
		}
		return TRUE;
	}


	uint64 _2MModuleOffset(void * address) {
		static uint64_t	_baseMoudle = 0;
		if (NULL == _baseMoudle) _baseMoudle = (uint64_t)GetModuleHandle(NULL);
		if (0 == _baseMoudle || _baseMoudle >= (uint64_t)address)
			return 0;

		return ((uint64_t)address - _baseMoudle);
	}

	void * _2MAINMoudleBase(std::string moudleName) {

		HMODULE findMoudle = NULL;
		if (NULL == (findMoudle = GetModuleHandleA(moudleName.c_str())))
			return NULL;

		return (void *)findMoudle;
	}

	void * _2MethodPointer(const char * kString, int64_t offset) {
		if (NULL == kString) kString = MOBULENAME_ProjectLH;

		void * baseAddress = UE4::_2MAINMoudleBase(kString);
		if (NULL == baseAddress) return NULL;

		return (void *)((uint64_t)baseAddress + offset);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------

	//获取一个 类对象的 父级
	UE4$UClass * UClass2SuperClass(UE4$UClass * _UClass) {
		UE4$UObjectHEAD TMPBuffer = { NULL };
		if (FALSE == _UE4ObjectISValid(_UClass, &TMPBuffer))
			return NULL;
		UE4$UClass * rValueBuffer = _UClass->_2SuperUClass();
		if (FALSE == _UE4ObjectISValid(rValueBuffer, &TMPBuffer))
			return NULL;
		return rValueBuffer;
	}

	//确认一个类对象的父级关系
	BOOL UClassEnterSuperClass(UE4$UClass *_UClass, UE4$UClass  * _SuperClass) {
		int _findLevel = 0;
		for (UE4$UClass * i = _UClass; NULL != i; i = UE4::UClass2SuperClass(i)) {
			if (i == _SuperClass)
				return TRUE;
			if (50 < _findLevel++)
				break;
		}
		return FALSE;
	}


	//获取指针是否为一个UE4对象
	BOOL enterUObjectHEAD(const UObject * _pthis, UE4$UObjectHEAD * headBuffer) {
		if (NULL == _pthis || NULL == headBuffer)
			return FALSE;

		//第一步: 读取 UObject 对象内存部分
		if (FALSE == UE4::readMemory(_pthis, headBuffer, sizeof(UE4$UObjectHEAD)))
			return FALSE;

		//第二步: 读取出 vf 表首个函数
		void * t_vfTableValue = (void *)headBuffer->vfTable;
		if (FALSE == UE4::readMemory(t_vfTableValue, &t_vfTableValue, sizeof(void *)))
			return FALSE;

		//第三步: 读取出主模块的 TEXT 区块范围
		return enter_text_range(t_vfTableValue);
	}

	BOOL enterUObjectHEAD(const UObject * _pthis) {
		UE4$UObjectHEAD TMPBuffer;
		return enterUObjectHEAD(_pthis, &TMPBuffer);
	}


	BOOL enterVFTable(const void * _pthis) {
		if (NULL == _pthis)
			return FALSE;

		void * t_vfTableValue = NULL;
		//第一步: 读取 vftable 信息
		if (FALSE == UE4::readMemory(_pthis, &t_vfTableValue, sizeof(void *)))
			return FALSE;

		//第二步: 读取出 vf 表首个函数
		if (FALSE == UE4::readMemory(t_vfTableValue, &t_vfTableValue, sizeof(void *)))
			return FALSE;
		//第三步: 读取出主模块的 TEXT 区块范围
		return enter_text_range(t_vfTableValue);
	}


	//------------------------------------------------------------------------------------------------------------------------------------------------

	void	FMemory_Free(const void * _FMemory) {
		static void * _call = 0;

		if (NULL == _call) _call = _2SYMPointer(FMemory$Free);
		if (NULL == _call) UE4_logEString("定位方法: public: static void FMemory::Free(void *) , 异常!!");

		void(*debug_call)(const void *) = (void(*)(const void *))_call;

		return debug_call(_FMemory);
	}

	BOOL	FString_ToBuffer(const FString * _FString, UE4$FString & retBuffer) {
		if (FALSE == UE4::readMemory(_FString, &retBuffer, sizeof(UE4$FString)))
			return FALSE;

		if (0 == retBuffer._count || retBuffer._count > retBuffer._max) {
			return FALSE;
		}
		wchar_t dCharBuffer = 0; //尝试读取一个符号, 读取失败错误返回
		if (FALSE == UE4::readMemory(retBuffer._string, &dCharBuffer, sizeof(wchar_t)))
			return FALSE;

		return TRUE;
	}

	std::string FString_ToString(const FString * _FString) {
		if (NULL == _FString)
			return "";

		UE4$FString fString;
		if (FALSE == FString_ToBuffer(_FString, fString))
			return "";

		std::shared_ptr< wchar_t > tAsciiString(new wchar_t[fString._count + 2]);
		if (NULL == tAsciiString.get()) { return std::string(""); }
		ZeroMemory(tAsciiString.get(), sizeof(wchar_t) * (fString._count + 2));
		CopyMemory(tAsciiString.get(), fString._string, sizeof(wchar_t) * fString._count);

		return CString::unicode_gb2312(tAsciiString.get());
	}

	const FString * FText_ToFString(const FText * fTextString) {
		if (NULL == fTextString)
			return NULL;

		static void * _call = 0;
		if (NULL == _call) _call = _2SYMPointer(FText$ToString);
		if (NULL == _call) UE4_logEString("定位方法: public: class FString const & FText::ToString(void)const , 异常!!");

		const FString * (*debug_call)(const FText *) = (const FString * (*)(const FText *))_call;

		return debug_call(fTextString);
	}

	std::string FText_ToString(const FText * fTextString) {
		if (NULL == fTextString)
			return "";

		static void * _call = 0;
		if (NULL == _call) _call = _2SYMPointer(FText$ToString);
		if (NULL == _call) UE4_logEString("定位方法: public: class FString const & FText::ToString(void)const , 异常!!");

		const FString * (*debug_call)(const FText *) = (const FString * (*)(const FText *))_call;

		const FString * rString = debug_call(fTextString);

		return FString_ToString(rString);
	}

	BOOL FName_IsValid(const FName * _FName) {

		_tagFName fNameBuffer;
		if (FALSE == UE4::readMemory(_FName, &fNameBuffer, sizeof(_tagFName)))
			return FALSE;

		static void * _NameEntryPointer = NULL;
		if (NULL == _NameEntryPointer) _NameEntryPointer = _2SYMPointer(FNamePool$NamePoolData);
		if (NULL == _NameEntryPointer)  UE4_logEString("定位方法: FNamePool& FNamePool( ????? ) , 异常!!");


		//    v19 = (unsigned __int16)*a1;        UE4 版本: 4.26.xxx
		//    v4 = (unsigned int)(*a1 >> 16);
		//    v11 = (unsigned __int16 *)(v9[(unsigned int)v4 + 2] + (unsigned int)(2 * v19));

		//if (!byte_4D5EE10)                      UE4 版本: 4.24.xxx
		//	FNamePool::FNamePool((unsigned __int16)a1, (__int64)&unk_4D5EE40);
		//v3 = (_WORD *)(*((_QWORD *)&unk_4D5EE40 + ((unsigned int)a1 >> 16) + 2) + 2 * (unsigned int)(unsigned __int16)a1);
		//v4 = (signed __int64)(v3 + 1);


		uint32_t v4 = (uint32_t)(fNameBuffer.index >> 16);
		uint16_t v19 = (uint16_t)fNameBuffer.index;

		void * TMPPointer = NULL;

		TMPPointer = (void *)((uint64_t)_NameEntryPointer + sizeof(__int64) * (v4 + 2));
		if (FALSE == UE4::readMemory((void *)TMPPointer, &TMPPointer, sizeof(uint64_t)))
			return FALSE;

		TMPPointer = (void *)((uint64_t)TMPPointer + 2 * v19);
		if (FALSE == UE4::readMemory((void *)TMPPointer, &TMPPointer, sizeof(uint64_t)))
			return FALSE;

		return TRUE;
	}

	std::string	FName_ToString(const FName * _FName) {

		if (NULL == _FName || NULL == *(uint64_t *)_FName)
			return "";

		static void * _call = 0;
		if (NULL == _call) _call = _2SYMPointer(FName$ToString);
		if (NULL == _call) UE4_logEString("定位方法: public: class FString FName::ToString(void)const , 异常!!");

		if (FALSE == FName_IsValid(_FName))
			return "*INVALID*";

		const FString *(*debug_call)(const FName *, const FString *) = (const FString *(*)(const FName *, const FString *))_call;

		UE4$FString _tagFStringBuffer = { NULL };
		if (NULL == debug_call(_FName, (const FString *)&_tagFStringBuffer)) {
			return "*INVALID*";
		}

		std::string rString = FString_ToString((const FString *)&_tagFStringBuffer);

		if (NULL != _tagFStringBuffer._string)
			FMemory_Free(_tagFStringBuffer._string);

		return rString;
	}

	uint64_t String_ToFName(const wchar_t * nameString) {

		static void * _call = 0;
		if (NULL == _call) _call = _2SYMPointer(FName$FName);
		if (NULL == _call) UE4_logEString("定位方法: public: FName::FName(wchar_t const *, enum  EFindName) , 异常!!");

		//FName(const WIDECHAR* Name, EFindName FindType=FNAME_Add);

		typedef const uint64_t *(*API_CreateFName)(const void *, const wchar_t *, int FindType);

		API_CreateFName debug_call = (API_CreateFName)_call;

		uint64_t FNameBuffer = 0;

		return *debug_call(&FNameBuffer, nameString, 1/*FNAME_Add*/);
	}

}
