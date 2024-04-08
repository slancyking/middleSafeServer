#pragma once
//
#include "TScript_UnrealEngine4.h"


#define DUMPPATH             "E:\\1_Python\\UE4."  MOBULENAME_ProjectLH ".json"


namespace UE4 {
	std::list<JSONBuffer>         TMPMethodBufferLIST;

	std::string _2TYPEString( UE4$UProperty * _kProperty , BOOL ODebugFlags = TRUE) {
		std::string rString = "";

		uint64_t tmpPropertyFlags = _kProperty->PropertyFlags;

#define DELPropertyFlags( f, k, sb, as)        if (k == (f &  k)) { f = (f ^ k); if (0 != std::string(as).length()) { sb = sb + as; sb = sb + " "; } }

#define ADDEXPTYPE(SBuffer, Ivar ,T, def)             {																									\
															UE4$UObjectBase TMPBuffer;  T kBuffer;														\
															if (UE4::readMemory(_kProperty, &kBuffer, sizeof(T))) {										\
																if (UE4::readMemory(kBuffer.Ivar, &TMPBuffer, sizeof(UE4$UObjectBase))) {				\
																	SBuffer = SBuffer + UE4::FName_ToString(&TMPBuffer.NamePrivate).c_str();			\
																	SBuffer = SBuffer + " ";															\
																	break;																				\
																}																						\
															}																							\
															rString = rString + def " "; break;															\
														}

		if (CPF_ReturnParm != (tmpPropertyFlags & CPF_ReturnParm)) {
			DELPropertyFlags(tmpPropertyFlags, CPF_OutParm,
				rString, "__out"
			);
		}
		DELPropertyFlags(tmpPropertyFlags, CPF_ConstParm, rString, "const");

		switch (EPropertyTYPE_GetTYPE(_kProperty)) {
		case EPropertyGenFlags::Byte:
			rString = rString + "byte ";
			break;
		case EPropertyGenFlags::Int8:
			rString = rString + "int8_t ";
			break;
		case EPropertyGenFlags::Int16:
			rString = rString + "int16_t ";
			break;
		case EPropertyGenFlags::Int:
			rString = rString + "int32_t ";
			break;
		case EPropertyGenFlags::Int64:
			rString = rString + "int64_t ";
			break;
		case EPropertyGenFlags::UInt16:
			rString = rString + "uint16_t ";
			break;
		case EPropertyGenFlags::UInt32:
			rString = rString + "uint32_t ";
			break;
		case EPropertyGenFlags::UInt64:
			rString = rString + "uint64_t ";
			break;
		case EPropertyGenFlags::UnsizedInt:
			rString = rString + "UnsizedInt ";
			break;
		case EPropertyGenFlags::UnsizedUInt:
			rString = rString + "UnsizedUInt ";
			break;
		case EPropertyGenFlags::Float:
			rString = rString + "float ";
			break;
		case EPropertyGenFlags::Double:
			rString = rString + "double ";
			break;
		case EPropertyGenFlags::Bool:
			rString = rString + "bool ";
			break;
		case EPropertyGenFlags::SoftClass: {
			ADDEXPTYPE(rString, PropertyClass, UE4$USoftClassProperty, "SoftClass");
		}
			break;
		case EPropertyGenFlags::WeakObject:

			rString = rString + "WeakObject ";
			break;
		case EPropertyGenFlags::LazyObject:
			rString = rString + "LazyObject ";
			break;
		case EPropertyGenFlags::SoftObject:
			rString = rString + "SoftObject ";
			break;
		case EPropertyGenFlags::Class: {
			ADDEXPTYPE(rString, PropertyClass, UE4$UClassProperty, "UClass");
		}
			 break;
		case EPropertyGenFlags::Object: {
			ADDEXPTYPE(rString, PropertyClass, UE4$UObjectProperty, "UObject");
		}
			break;
		case EPropertyGenFlags::Interface: {
			ADDEXPTYPE(rString, InterfaceClass, UE4$UInterfaceProperty, "Interface");
		}
			break;
		case EPropertyGenFlags::Name:
			rString = rString + "FName ";
			break;
		case EPropertyGenFlags::Str:
			rString = rString + "FString ";
			break;
		case EPropertyGenFlags::Array:
			rString = rString + "FArray ";
			break;
		case EPropertyGenFlags::Map:
			rString = rString + "FMap ";
			break;
		case EPropertyGenFlags::Set:
			rString = rString + "Set ";
			break;
		case EPropertyGenFlags::Struct: {
			ADDEXPTYPE(rString, Struct, UE4$UStructProperty, "UStruct");
		}
			break;
		case EPropertyGenFlags::Delegate:
			rString = rString + "Delegate ";
			break;
		case EPropertyGenFlags::InlineMulticastDelegate:
			rString = rString + "InlineMulticastDelegate ";
			break;
		case EPropertyGenFlags::SparseMulticastDelegate:
			rString = rString + "SparseMulticastDelegate ";
			break;
		case EPropertyGenFlags::Text:
			rString = rString + "FText ";
			break;
		case EPropertyGenFlags::Enum: {
			ADDEXPTYPE(rString, Enum, UE4$UEnumProperty, "UEnum");
		}
			break;
		default:
			ADDEXPTYPE(rString, ClassPrivate, UE4$UEnumProperty, "ERROR");
			break;
		}

		DELPropertyFlags(tmpPropertyFlags, CPF_ContainsInstancedReference	, rString, "*");
		DELPropertyFlags(tmpPropertyFlags, CPF_InstancedReference			, rString, "*");
		DELPropertyFlags(tmpPropertyFlags, CPF_ReferenceParm				, rString, "&");

		DELPropertyFlags(tmpPropertyFlags, CPF_ReturnParm		, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_OutParm			, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_Parm				, rString, "");

		DELPropertyFlags(tmpPropertyFlags, CPF_NativeAccessSpecifierPublic	, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_AdvancedDisplay				, rString, "");

		DELPropertyFlags(tmpPropertyFlags, CPF_ZeroConstructor				, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_IsPlainOldData				, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_NoDestructor					, rString, "");
		DELPropertyFlags(tmpPropertyFlags, CPF_HasGetValueTypeHash			, rString, "");

		if (0	 == tmpPropertyFlags) return rString.c_str();
		if (TRUE == ODebugFlags     ) rString += CString::format("/*0x%016I64X, 0x%016I64X*/ ", _kProperty->PropertyFlags, tmpPropertyFlags);
		return rString.c_str();
	}

	std::string _2MethodOString(std::string _CString, UE4$UFunction * TMPFunction) {
		//��һ��: �õ�����ֵ����
		std::string _retString = "void";
		UE4::enumUProperty(TMPFunction->PropertyLink, [&_retString](UE4$UProperty * _kProperty) {
			std::string NString = UE4::FName_ToString(&_kProperty->NamePrivate);
			if (NString != "ReturnValue")
				return false;
			return "" != (_retString = UE4::_2TYPEString(_kProperty, FALSE));
		});

		//�ڶ���: �õ���������
		std::string _nameString = CString::format("%s::%s", _CString.c_str(), UE4::FName_ToString(&TMPFunction->NamePrivate).c_str());

		//������: �õ������б�
		std::string _argsString = "";
		UE4::enumUProperty(TMPFunction->PropertyLink, [&_argsString](UE4$UProperty * _kProperty) {
			std::string NString = UE4::FName_ToString(&_kProperty->NamePrivate);
			if ("" == NString || NString == "ReturnValue")
				return false;

			if ("" != _argsString) _argsString += ", ";

			_argsString = _argsString + CString::format("%s %s",
				UE4::_2TYPEString(_kProperty, TRUE).c_str(),
				NString.c_str()
			);
				
			return false;
		});

		//���Ĳ�: ���� ��������������Ϣ
		std::string rString = CString::format("%s %s(%s)",
			_retString.c_str(), 
			_nameString.c_str(), 
			_argsString.c_str()
		);
		//���岽: ˫�ո� �滻�� ���ո�
		return CString::replace(rString, "  ", " ").c_str();
	}

	int DumpMethod2JSON(UE4$UClass * _kClass, std::string _ConfigString, std::string _PackageString, std::string _ClassNameString) {
		int TMPDumpCount = 0;
		UE4::enumUFunction(_kClass, [_kClass, &TMPDumpCount, _ConfigString, _PackageString, _ClassNameString](UE4$UFunction * TMPFunction) {
			//��ȡ�� ��������
			std::string NString = UE4::FName_ToString(&TMPFunction->NamePrivate);
			//��ȡ�� ����ԭ���ַ���
			std::string OString = UE4::_2MethodOString(_ClassNameString, TMPFunction);

			//��װjson �ṹ
			JSONBuffer JSONFunction;

			UE4JSONWriteValue(JSONFunction, "package"	, _PackageString.c_str());
			UE4JSONWriteValue(JSONFunction, "config"	, _ConfigString.c_str());
			UE4JSONWriteValue(JSONFunction, "name"		, CString::format("%s::%s", _ClassNameString.c_str(), NString.c_str()));
			UE4JSONWriteValue(JSONFunction, "offset"	, UE4::_2MModuleOffset(TMPFunction->Func));
			UE4JSONWriteValue(JSONFunction, "original"	, OString.c_str());

			//����� �ܱ�
			UE4::TMPMethodBufferLIST.push_back(JSONFunction);

			TMPDumpCount = TMPDumpCount + 1;
			return false;
		});

		return TMPDumpCount;
	}

	//dump ���нӿ�, �� json �ļ�
	int DumpMethod2JSON( std::string & rPathString ) {
		int TMPDumpCount = 0;
		//��һ��: ����ļ�, ��������
		DeleteFileA(DUMPPATH);
		UE4::TMPMethodBufferLIST.clear();

		//�ڶ���: ����������, ���ҽ��з�֧����
		UE4::enumUClass([&TMPDumpCount](UE4$UClass * _kClass, std::string CString, std::string PString, std::string NString) {
			TMPDumpCount += DumpMethod2JSON(_kClass, CString, PString, NString);
			return false;
		});

		//������: �����еĽӿ���Ϣ, д���ļ�
		FILE *  _UE4JsonFile = NULL;
		if (NULL == (_UE4JsonFile = fopen(DUMPPATH, "w+"))) {
			return 0;
		};

		fwrite("{\"method\":[\n", strlen("{\"method\":[\n"), 1, _UE4JsonFile);

		int	_TMPWriteCount = 0;
		for (auto & JSONBuffer : UE4::TMPMethodBufferLIST){
			std::string JSONString = "";

			JSONString = JSONBuffer.ToFormattedString().c_str();

			JSONString = CString::replace(JSONString, "\r", "");
			JSONString = CString::replace(JSONString, "\n", "");

			switch (_TMPWriteCount) {  	//д���ļ�
			case 0:
				fwrite(JSONString.c_str(), JSONString.length(), 1, _UE4JsonFile);
				break;
			default:
				fwrite(",\n", strlen(",\n"), 1, _UE4JsonFile);
				fwrite(JSONString.c_str(), JSONString.length(), 1, _UE4JsonFile);
				break;
			}

			_TMPWriteCount = _TMPWriteCount + 1;
		}
		fwrite("\n]}", strlen("\n]}"), 1, _UE4JsonFile);
		fclose(_UE4JsonFile);

		rPathString = DUMPPATH;
		return TMPDumpCount;
	}


	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//����չ������Ϣʱ, ��� FName �ֶ�
	std::string SCALLBACK_FNameString(const UObject * _pthis) {
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(_pthis, &TMPHeadBuffer)) {
			return "";
		}
		std::string rString = UE4::FName_ToString(&TMPHeadBuffer.NamePrivate);

		return CString::format("FName:%s", rString.c_str());
	}

	//Ĭ�ϵĻ����ؼ���Ϣ
	std::string SCALLBACK_UCtrlString(const UObject * _pthis) {
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(_pthis, &TMPHeadBuffer)) {
			return "";
		}
		//�ǿؼ�����
		if (NULL == UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "Widget"))
			return "";

		//����Ϊ�ؼ�����
		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "TextBlock"))
			return UTextBlock_getTEXT(_pthis);

		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "Image"))
			return UImage_getResourceName(_pthis);

		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "Button"))
			return UButton_getResourceName(_pthis);

		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "ProgressBar"))
			return CString::format("%.3f", UProgressBar_getPercent(_pthis));


		return "";
	}

	// UE4 ϵͳԭʼ ��    ����: ���뷽���Ķ��� ���̳��� UPanelSlot
	std::string SCALLBACK_UPanelSlot(const UObject * _pthis) {
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(_pthis, &TMPHeadBuffer)) {
			return "";
		}

		static long long _ivar_offset = -1;
		if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset(TMPHeadBuffer.ClassPrivate, "Content");
		if (-1 == _ivar_offset) return ("#ERROR# : content not find");

		const UObject * p_Content = (const FText *)((uint64_t)_pthis + _ivar_offset);
		if (FALSE == UE4::readMemory(p_Content, &p_Content, sizeof(UObject *)))
			return ("#ERROR# : content read error");

		if (NULL == p_Content || FALSE == _UE4ObjectISValid(p_Content, &TMPHeadBuffer))
			return ("#ERROR# : content value empty");

		std::string rCtrlString = ""; //�Ƿ�Ϊ��׼�ؼ�
		if ("" != (rCtrlString = SCALLBACK_UCtrlString(p_Content)))
			return rCtrlString;

		return std::string("#TYPE# :") + UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate);
	}

	// UE4 ϵͳԭʼ ���  ����: ���뷽���Ķ��� ���̳��� UCanvasPanel
	std::string SCALLBACK_UCanvasPanel(const UObject * _pthis) {
		return SCALLBACK_FNameString(_pthis);
	}

	//dump UObject �Ļ�����������Ϣ
	std::string DumpUObjectString( const UObject * TMPUObjcetBuffer) {
		//��һ��: ��ȡ�� ��ǰ����Ļ���ͷ��Ϣ
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcetBuffer, &TMPHeadBuffer)) {
			return "";
		}
		//�ڶ���: ��ȡ�� ��ǰ���������Ϣ
		if (FALSE == _UE4ObjectISValid(TMPHeadBuffer.ClassPrivate)) {
			return "";
		}
		std::string TMPString = "";
		//������: ����Ϊ ͨ���͵Ĵ���, UE4 ԭʼ��
		if ("" != (TMPString = SCALLBACK_UCtrlString(TMPUObjcetBuffer)))				  //�Ƿ�Ϊ��׼�ؼ�
			return TMPString;
		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "PanelSlot"))      //ҳ��
			return SCALLBACK_UPanelSlot(TMPUObjcetBuffer);
		if (NULL != UE4::findUE4SuperClass(TMPHeadBuffer.ClassPrivate, "CanvasPanel"))    //���
			return SCALLBACK_UCanvasPanel(TMPUObjcetBuffer);

		return "";
	}


	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------


	void DCALLBACK_InstallUClassLIST(UE4$UClass * TMPUClass, std::list<_tagDBGUClassINFO> & RUClassBuffer ) {
		for (UE4$UClass * i = TMPUClass; _UE4ObjectISValid(i); i = UE4::UClass2SuperClass(i)) {
			std::string NString = "";
			if ("" == (NString = UE4::FName_ToString(&i->NamePrivate)))
				break;

			_tagDBGUClassINFO TMPBuffer;

			TMPBuffer._UClass	= i;
			TMPBuffer._package	= UE4::UClass2UPackage(i);
			TMPBuffer._class	= NString;
			TMPBuffer._start	= 0;
			TMPBuffer._end		= i->PropertiesSize;

			if (0 < i->PropertiesSize && 0 < RUClassBuffer.size()) //  д���ϴ�д�����ʼλ��
				RUClassBuffer.back()._start = i->PropertiesSize;

			RUClassBuffer.push_back(TMPBuffer);
		}
	}

	void DCALLBACK_DefaultSymbol(std::list<_tagDBGUClassINFO> & kUClassBuffer, std::list<_tagDBGPropertyINFO> & RPropertyBuffer) {
		for (std::list<_tagDBGUClassINFO>::iterator iClass = kUClassBuffer.begin(); iClass != kUClassBuffer.end(); iClass++) {
			if (iClass->_class != "Object")  continue;//����Ƿ�Ϊ UObject

			_tagDBGPropertyINFO TMPBuffer;

			TMPBuffer.UClass = *iClass;

			//  + 0x00000000
			TMPBuffer.nProperty	= "vfTable";
			TMPBuffer.Type		= EPropertyTYPE::UInt64;
			TMPBuffer.Offset	= 0x00000000;
			TMPBuffer.Size		= sizeof(uint64_t);
			RPropertyBuffer.push_back(TMPBuffer);

			//  + 0x00000008
			TMPBuffer.nProperty = "ObjectFlags";
			TMPBuffer.Type		= EPropertyTYPE::UInt32;
			TMPBuffer.Offset	= 0x00000008;
			TMPBuffer.Size		= sizeof(uint32_t);
			RPropertyBuffer.push_back(TMPBuffer);

			//  + 0x0000000C
			TMPBuffer.nProperty = "InternalIndex";
			TMPBuffer.Type		= EPropertyTYPE::UInt32;
			TMPBuffer.Offset	= 0x0000000C;
			TMPBuffer.Size		= sizeof(uint32_t);
			RPropertyBuffer.push_back(TMPBuffer);

			//  + 0x00000010
			TMPBuffer.nProperty = "ClassPrivate";
			TMPBuffer.Type		= EPropertyTYPE::Class;
			TMPBuffer.Offset	= 0x00000010;
			TMPBuffer.Size		= sizeof(void *);
			RPropertyBuffer.push_back(TMPBuffer);

			//  + 0x00000018
			TMPBuffer.nProperty = "NamePrivate";
			TMPBuffer.Type		= EPropertyTYPE::Name;
			TMPBuffer.Offset	= 0x00000018;
			TMPBuffer.Size		= sizeof(uint64_t);
			RPropertyBuffer.push_back(TMPBuffer);

			//  + 0x00000020
			TMPBuffer.nProperty = "OuterPrivate";
			TMPBuffer.Type		= EPropertyTYPE::UInt64;
			TMPBuffer.Offset	= 0x00000020;
			TMPBuffer.Size		= sizeof(uint64_t);
			RPropertyBuffer.push_back(TMPBuffer);

			break;
		}
	}

	void DCALLBACK_UE4ExportSymbol(std::list<_tagDBGUClassINFO> & kUClassBuffer, std::list<_tagDBGPropertyINFO> & RPropertyBuffer) {
		for (std::list<_tagDBGUClassINFO>::iterator iClass = kUClassBuffer.begin(); iClass != kUClassBuffer.end(); iClass++) {
			if (iClass->_class == "Object")  continue;//����Ƿ�Ϊ UObject

			UE4::enumUProperty(iClass->_UClass, [iClass, &RPropertyBuffer](UE4$UProperty * _kProperty) {
				if (_kProperty->Offset_Internal < iClass->_start)
					return false;
				if (_kProperty->Offset_Internal > iClass->_end)
					return false;

				_tagDBGPropertyINFO TMPBuffer;

				TMPBuffer.UClass			= *iClass;
				TMPBuffer.kProperty			= _kProperty;
				TMPBuffer.nProperty			= UE4::FName_ToString(&_kProperty->NamePrivate);
				TMPBuffer.Type				= EPropertyTYPE_GetTYPE(_kProperty);
				TMPBuffer.Offset			= _kProperty->Offset_Internal;
				TMPBuffer.Size				= _kProperty->ElementSize;
				TMPBuffer.PropertyFlags		= _kProperty->PropertyFlags;

				if (EPropertyGenFlags::Bool == (EPropertyGenFlags)TMPBuffer.Type)
					TMPBuffer.mask = ((UE4$UBoolProperty*)_kProperty)->ByteMask;



				RPropertyBuffer.push_back(TMPBuffer);
				return false;
			});

		}
	}

	BOOL DCALLBACK_EnterUE4ExportSymbol(int hexOffset, std::list<_tagDBGPropertyINFO> & kPropertyBuffer, uint32_t & RSizeBuffer) {
		for (_tagDBGPropertyINFO & kSymbol : kPropertyBuffer) {
			if (kSymbol.Offset != hexOffset) 
				continue;
			RSizeBuffer = kSymbol.Size;
			return TRUE;
		}
		return FALSE;
	}
	BOOL DCALLBACK_EnterUE4ExportSymbol(int hexOffset, std::list<_tagDBGPropertyINFO> & kPropertyBuffer) {
		uint32_t RSizeBuffer = 0;
		return DCALLBACK_EnterUE4ExportSymbol(hexOffset, kPropertyBuffer, RSizeBuffer);
	}

	void DCALLBACK_Offset2UClassINFO(int hexOffset, std::list<_tagDBGUClassINFO> & kUClassBuffer, _tagDBGUClassINFO & RClassBuffer) {
		for (_tagDBGUClassINFO & kUClass : kUClassBuffer) {
			if (hexOffset < kUClass._start ||
				hexOffset >= kUClass._end)
				continue;

			RClassBuffer = kUClass;
			break;
		}
	}

	UINT DCALLBACK_Offset2HEXSize(int hexOffset, std::list<_tagDBGUClassINFO> & kUClassBuffer, std::list<_tagDBGPropertyINFO> & kPropertyBuffer) {
		for (auto kUClass = kUClassBuffer.begin(); kUClass != kUClassBuffer.end(); kUClass++){
			if (hexOffset < kUClass->_start || hexOffset >= kUClass->_end)
				continue;

			//��ǰ�ڴ�, ���� ��ǰ �� ����, ���� ����������ʼ
			for (int iSizeIndex = 1; hexOffset + iSizeIndex < kUClass->_end; iSizeIndex = iSizeIndex + 1) {
				if (TRUE == DCALLBACK_EnterUE4ExportSymbol(hexOffset + iSizeIndex, kPropertyBuffer)) {
					return iSizeIndex;
				}
			}

			return kUClass->_end - hexOffset;
		}
		return 1;
	}

	void DCALLBACK_UNKnownHEXSymbol(std::list<_tagDBGUClassINFO> & kUClassBuffer, std::list<_tagDBGPropertyINFO> & RPropertyBuffer) {
		//��һ��: �õ��������ڴ�
		size_t TMPMaxSize = 0;
		for (auto & iClass : kUClassBuffer)
			if (TMPMaxSize < iClass._end)
				TMPMaxSize = iClass._end;

		_tagDBGPropertyINFO TMPBuffer; TMPBuffer.Size = 0;
		//�ڶ���: ���������ֽ�, �ҵ��з��ŵ�, �޷��ŵ�תhex
		for (int iHexIndex = 0; iHexIndex < TMPMaxSize; iHexIndex += TMPBuffer.Size) {

			//��⵱ǰƫ��ֵ, �Ƿ�Ϊ ��Ա����
			if (TRUE == DCALLBACK_EnterUE4ExportSymbol(iHexIndex, RPropertyBuffer,
																  TMPBuffer.Size)){
				continue;
			}

			//�޷�����Ϣʱ, ��� hex ��Ϣ
			DCALLBACK_Offset2UClassINFO(iHexIndex, kUClassBuffer, TMPBuffer.UClass);

			TMPBuffer.nProperty		= CString::format("unknown.%08X", iHexIndex);
			TMPBuffer.Type			= EPropertyTYPE::HEX;
			TMPBuffer.Offset		= iHexIndex;
			TMPBuffer.PropertyFlags = EPropertyFlags::CPF_None;
			TMPBuffer.Size			= DCALLBACK_Offset2HEXSize(iHexIndex, kUClassBuffer, RPropertyBuffer);

			RPropertyBuffer.push_back(TMPBuffer);
		}
	}

	std::string DCallBack_ReadHexString(uint64_t _start, uint32_t _offset, size_t _size) {
		if (0 == _start) return "";
		if (0 >= _size) _size = 500;
		if (30000 <= _size) _size = 30000;

		std::shared_ptr< BYTE > byteBuffer(new BYTE[_size + 10]);
		if (NULL == byteBuffer.get()) { return std::string(""); }
		ZeroMemory(byteBuffer.get(), sizeof(BYTE)* (_size + 10));

		if (FALSE == UE4::readMemory((void *)(_start + _offset), byteBuffer.get(), _size))
			return "";

		CString rString = "";
		for (size_t i = 0; i < _size; i++) {
			rString.addFormat("%02X",
				byteBuffer.get()[i]
			);
		}
		return std::string(rString.getBuffer());
	}

#define _2HexString(a, o, l)    UE4::DCallBack_ReadHexString((uint64_t)a, (uint64_t)o, l)

	void DCALLBACK_2PropertyValueByBOOL(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, sizeof(uint32_t));
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		for (auto i = RPropertyBuffer.begin(); i != RPropertyBuffer.end(); i++) {
			if (kProperty->Offset != i->Offset)
				continue;

			char TNameString[302] = { NULL };
			memcpy_s(TNameString, 300, i->nProperty.c_str(), i->nProperty.size());

			TMPOtherString += _2HexString(TNameString	, 0, 300);
			TMPOtherString += _2HexString(&i->mask		, 0, sizeof(uint32_t));
		}

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueByENUM(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, sizeof(uint64_t));
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcet, &TMPHeadBuffer) || 
			FALSE == _UE4ObjectISValid(TMPHeadBuffer.ClassPrivate)) {
			kProperty->value = TMPHexString;
			return ;
		}

		std::string NString = UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate);

		char TNameString[302] = { NULL };
		memcpy_s(TNameString, 300, NString.c_str(), NString.size());

		TMPOtherString += _2HexString(TNameString, 0, 300);

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueBySTRUCT(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcet, &TMPHeadBuffer) ||
			FALSE == _UE4ObjectISValid(TMPHeadBuffer.ClassPrivate)) {
			TMPOtherString += _2HexString("unknow", 0, 300);
			kProperty->value = TMPOtherString + TMPHexString;
			return;
		}

		std::string NString = UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate);

		char TNameString[302] = { NULL };
		memcpy_s(TNameString, 300, NString.c_str(), NString.size());

		TMPOtherString += _2HexString(TNameString, 0, 300);

		kProperty->value = TMPOtherString + TMPHexString;
	}

	void DCALLBACK_2PropertyValueByFSTRING(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		UE4$FString FStringBuffer = { NULL };
		if (FALSE == UE4::FString_ToBuffer((const FString *)_2UObjectPointer(TMPUObjcet, kProperty->Offset), FStringBuffer)) {
			kProperty->value = TMPHexString;
			return;
		}

		TMPOtherString += _2HexString(FStringBuffer._string, 0, 2 * FStringBuffer._count);
		TMPOtherString += "0000000000";

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueByFNAME(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		std::string TMPString = UE4::FName_ToString((const FName *)_2UObjectPointer(TMPUObjcet, kProperty->Offset));

		char TNameString[302] = { NULL };
		memcpy_s(TNameString, 300, TMPString.c_str(), TMPString.size());

		TMPOtherString += _2HexString(TNameString, 0, TMPString.size());
		TMPOtherString += "0000000000";

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueByFTEXT(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		const FString * p_fString = NULL;
		if (NULL == (p_fString = UE4::FText_ToFString((const FText *)_2UObjectPointer(TMPUObjcet, kProperty->Offset)))){
			kProperty->value = TMPHexString;
			return;
		}
		UE4$FString FStringBuffer = { NULL };
		if (FALSE == UE4::FString_ToBuffer(p_fString, FStringBuffer)) {
			kProperty->value = TMPHexString;
			return;
		}

		TMPOtherString += _2HexString(FStringBuffer._string, 0, 2 * FStringBuffer._count);
		TMPOtherString += "0000000000";

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueByUOBJECT(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ

		if (FALSE == UE4::readMemory(_2UObjectPointer(TMPUObjcet, kProperty->Offset),
												&TMPUObjcet, sizeof(UObject *))) {
			kProperty->value = TMPHexString;
			return;
		}

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcet, &TMPHeadBuffer) ||
			FALSE == _UE4ObjectISValid(TMPHeadBuffer.ClassPrivate) ) {
			kProperty->value = TMPHexString;
			return;
		}

		std::string NString = UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate);

		char TNameString[302] = { NULL };
		memcpy_s(TNameString, 300, NString.c_str(), NString.size());

		TMPOtherString += _2HexString(TNameString, 0, 300);

		kProperty->value = TMPHexString + TMPOtherString;
	}

	void DCALLBACK_2PropertyValueByUUCLASS(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer, _tagDBGPropertyINFO * kProperty) {
		std::string TMPHexString = _2HexString(TMPUObjcet, kProperty->Offset, kProperty->Size);
		std::string TMPOtherString = "";    // ��β�� hex ��չ


		if (FALSE == UE4::readMemory(_2UObjectPointer(TMPUObjcet, kProperty->Offset),
													&TMPUObjcet, sizeof(UObject *))) {
			kProperty->value = TMPHexString;
			return;
		}

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcet, &TMPHeadBuffer)) {
			kProperty->value = TMPHexString;
			return;
		}

		std::string NString = UE4::FName_ToString(&TMPHeadBuffer.NamePrivate);

		char TNameString[302] = { NULL };
		memcpy_s(TNameString, 300, NString.c_str(), NString.size());

		TMPOtherString += _2HexString(TNameString, 0, 300);

		kProperty->value = TMPHexString + TMPOtherString;
	}


	void DCALLBACK_2PropertyValue(const UObject * TMPUObjcet, std::list<_tagDBGPropertyINFO> & RPropertyBuffer) {
		
		//��һ��: ����ƫ��ֵ, ������������
		RPropertyBuffer.sort([](_tagDBGPropertyINFO & a, _tagDBGPropertyINFO & b) {
			return a.Offset < b.Offset;
		});

		//�ڶ���: �������г�Ա, ���ҽ������ݸ���
		for (auto i = RPropertyBuffer.begin(); i != RPropertyBuffer.end(); i++){
			switch ((EPropertyTYPE)i->Type){
			case EPropertyTYPE::Bool: {		//bool		, ���⴦��
				DCALLBACK_2PropertyValueByBOOL(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			case EPropertyTYPE::Enum: {		//enum		, ���⴦��
				DCALLBACK_2PropertyValueByENUM(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			case EPropertyTYPE::Struct: {   //struct	, ���⴦��
				DCALLBACK_2PropertyValueBySTRUCT(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			case EPropertyTYPE::Str: {		//FString	, ���⴦��
				DCALLBACK_2PropertyValueByFSTRING(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			case EPropertyTYPE::Name: {		//FName		, ���⴦��
				DCALLBACK_2PropertyValueByFNAME(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			case EPropertyTYPE::Text: {		//FText		, ���⴦��
				DCALLBACK_2PropertyValueByFTEXT(TMPUObjcet, RPropertyBuffer, &*i);
			}break;
			default:
				if (EPropertyTYPE::Object == i->Type || EPropertyTYPE::WeakObject == i->Type || 
														EPropertyTYPE::LazyObject == i->Type || 
														EPropertyTYPE::SoftObject == i->Type) {

					DCALLBACK_2PropertyValueByUOBJECT(TMPUObjcet, RPropertyBuffer, &*i);
					break;
				}
				if ( EPropertyTYPE::SoftClass == i->Type || EPropertyTYPE::Class == i->Type) {
					DCALLBACK_2PropertyValueByUUCLASS(TMPUObjcet, RPropertyBuffer, &*i);
					break;
				}
				i->value = _2HexString(TMPUObjcet, i->Offset, i->Size);
				break;
			}
		}
	}

	void DumpUObjectINFO(const UObject * TMPUObjcetBuffer, std::function<void(_tagDBGPropertyINFO & )> enumCallback) {
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(TMPUObjcetBuffer, &TMPHeadBuffer)) {
			return;
		}
	
		std::list<_tagDBGUClassINFO>	TMPUClassBuffer;
		std::list<_tagDBGPropertyINFO>	TMPUPropertyBuffer;

		//��һ��: ���� ClassPrivate �õ����еĸ�������Ϣ
		DCALLBACK_InstallUClassLIST(TMPHeadBuffer.ClassPrivate, TMPUClassBuffer);
		//�ڶ���: ��ȡ������֪��, δ֪��, ������Ϣ
		DCALLBACK_DefaultSymbol(TMPUClassBuffer, TMPUPropertyBuffer);
		DCALLBACK_UE4ExportSymbol(TMPUClassBuffer, TMPUPropertyBuffer);
		DCALLBACK_UNKnownHEXSymbol(TMPUClassBuffer, TMPUPropertyBuffer);
		//������: ��ȡ���еĳ�Ա ��������
		DCALLBACK_2PropertyValue(TMPUObjcetBuffer, TMPUPropertyBuffer);
		//���Ĳ�: ��������Ϣ, ���ص��ص�����
		for (auto & kUProperty : TMPUPropertyBuffer) {
			enumCallback(kUProperty);
		}
	}
}






































