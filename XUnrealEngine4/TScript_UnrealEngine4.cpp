#pragma once
//
#include "TScript_UnrealEngine4.h"

// Common colors.
const _tagLinearColor _tagLinearColor::White(1.f, 1.f, 1.f);
const _tagLinearColor _tagLinearColor::Gray(0.5f, 0.5f, 0.5f);
const _tagLinearColor _tagLinearColor::Black(0, 0, 0);
const _tagLinearColor _tagLinearColor::Transparent(0, 0, 0, 0);
const _tagLinearColor _tagLinearColor::Red(1.f, 0, 0);
const _tagLinearColor _tagLinearColor::Green(0, 1.f, 0);
const _tagLinearColor _tagLinearColor::Blue(0, 0, 1.f);
const _tagLinearColor _tagLinearColor::Yellow(1.f, 1.f, 0);






namespace UE4 {

	//强制性 结束当前进程
	void TerminateExitCallback() {
		exit(0);
	}

	void logFormat(const char * fString, ...) {
		if (NULL == fString) return;

		va_list arglist;
		va_start(arglist, fString);

		std::string logString = CString::format_va(fString, arglist);

		va_end(arglist);

	}


	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	struct _tagTMPClassINFO{
		CString       _package;
		CString       _name;
		CString       _config;
	};

	CRejection										_GClassBufferRejection;
	std::map<UE4$UClass *, _tagTMPClassINFO>		_GClassBufferLIST;

	void RefUClassLISTByUObject() {
		UE4::_GClassBufferRejection.OpenRejection();

		//第一步: 删除无用的缓冲区
		std::list<UE4$UClass *> TMPInvalidLIST;
		for (auto & kClassBuffer : UE4::_GClassBufferLIST)
			if (FALSE == _UE4ObjectISValid(kClassBuffer.first))
				TMPInvalidLIST.push_back(kClassBuffer.first);

		for (auto & kClassBuffer : TMPInvalidLIST)
			UE4::_GClassBufferLIST.erase(kClassBuffer);

		//第二步: 遍历所有的虚幻对象, 并且初始化到类信息
		UE4::enumUObject([](const UE4$UObjectHEAD & TMPHead, const UObject * TMPObject) {
			UE4$UClass * TMPUClass = TMPHead.ClassPrivate;
			if (NULL == TMPUClass || FALSE == _UE4ObjectISValid(TMPUClass))
				return FALSE;
			if (UE4::_GClassBufferLIST.find(TMPUClass) != UE4::_GClassBufferLIST.end())
				return FALSE;

			CString PString = "";

			UE4$UObjectHEAD TMPUPackageHEAD;
			if (FALSE == UE4::enterUObjectHEAD(TMPUClass->OuterPrivate, &TMPUPackageHEAD))
				return FALSE;

			_tagTMPClassINFO TClassBuffer;

			TClassBuffer._package	= UE4::FName_ToString(&TMPUPackageHEAD.NamePrivate);
			TClassBuffer._name		= UE4::FName_ToString(&TMPUClass->NamePrivate);
			TClassBuffer._config	= UE4::FName_ToString(&TMPUClass->ClassConfigName);

			UE4::_GClassBufferLIST.insert(std::pair<UE4$UClass *, _tagTMPClassINFO>(
				TMPUClass, TClassBuffer
				)
			);
			return FALSE;
		});
		UE4::_GClassBufferRejection.CloseRejection();
	}


	UE4$UClass * findUE4Class(const char * _package, const char * _class) {
		if (NULL == _class || 0 == strlen(_class))
			return NULL;
		if (NULL == _package || 0 == strlen(_package))
			return NULL;
		//第一步: 查找备份
		for (auto & kClassBuffer : UE4::_GClassBufferLIST) {

			if (kClassBuffer.second._package != _package)
				continue;
			if (kClassBuffer.second._name != _class)
				continue;

			if (FALSE == _UE4ObjectISValid(kClassBuffer.first))
				continue;

			return kClassBuffer.first;
		}
		//第二步: 遍历所有对象, 初始化所有类结构
		UE4::RefUClassLISTByUObject();
		//第三步: 再次查找备份
		for (auto & kClassBuffer : UE4::_GClassBufferLIST) {

			if (kClassBuffer.second._package != _package)
				continue;
			if (kClassBuffer.second._name != _class)
				continue;

			if (FALSE == _UE4ObjectISValid(kClassBuffer.first))
				continue;

			return kClassBuffer.first;
		}
		return NULL;
	}

	UE4$UClass * findUE4SuperClass(UE4$UClass * _StartUClass, const char * superClass) {
		if (FALSE == _UE4ObjectISValid(_StartUClass))
			return NULL;

		int _findLevel = 0;
		for (UE4$UClass * i = _StartUClass; i != NULL; i = UE4::UClass2SuperClass(i)) {
			std::string NString = "";
			if ("" != (NString = UE4::FName_ToString(&i->NamePrivate))) {
				const char * kString = NString.c_str();

				if (TRUE == UE4_stricmpex(kString, superClass))
					return i;

				//检测是否为 Object
				if (TRUE == UE4_stricmpex(kString, "Object"))
					break;
			};
			if (30 < _findLevel++)
				break;
		}
		return NULL;
	}

	CRejection									_UE4TYPEBufferRejection;
	std::map<uint64_t, EPropertyGenFlags>		_UE4TYPEBufferLIST;

	//获取 UE4$UProperty 的 类型
	EPropertyGenFlags _2PropertyTYPE(UE4$UProperty * _kProperty) {
		if (NULL == _kProperty || FALSE == _UE4ObjectISValid(_kProperty))
			return EPropertyGenFlags::None;

		//--[[ 当前调试信息: address = 0x0000023FC7A3AD80 ]]-- 所属类: UObjectProperty

		//UObject::ClassPrivate                                       , offset = 0x00000010, <8   >, type = UClass         , flags = 0x0000686F508A1E51, 
		//.class  = 0x0000023FB36B5BC0
		//.class  = ObjectProperty
		UE4$UClass * TMPUClass = _kProperty->ClassPrivate;
		if (NULL == TMPUClass || FALSE == _UE4ObjectISValid(TMPUClass))
			return EPropertyGenFlags::None;

		EPropertyGenFlags TMPTypeBuffer = EPropertyGenFlags::None;
		std::string       TMPTypeString = "";

		//从备份中, 获取数据并且返回
		UE4::_UE4TYPEBufferRejection.OpenRejection();
		if (_UE4TYPEBufferLIST.find(TMPUClass->NamePrivate) != _UE4TYPEBufferLIST.end())
			TMPTypeBuffer = _UE4TYPEBufferLIST[TMPUClass->NamePrivate];
		UE4::_UE4TYPEBufferRejection.CloseRejection();
		
		if (EPropertyGenFlags::None != TMPTypeBuffer) return TMPTypeBuffer;  //已找到类型备份

		//未从备份中获取到时, 主动检测类型, 并且备份
		std::string TMPNameString = UE4::FName_ToString(&TMPUClass->NamePrivate);
		if ("" == TMPNameString || "*INVALID*" == TMPNameString)
			return EPropertyGenFlags::None;

#define RTypeValue(c, v)	{																										\
								UE4::_UE4TYPEBufferRejection.OpenRejection();														\
								if (UE4::_UE4TYPEBufferLIST.find(c->NamePrivate) == UE4::_UE4TYPEBufferLIST.end())					\
									_UE4TYPEBufferLIST.insert(std::pair<uint64_t, EPropertyGenFlags>(								\
																c->NamePrivate, v  )											    \
															  );																	\
								UE4::_UE4TYPEBufferRejection.CloseRejection();														\
								return v;																							\
							}																										\

		if (TMPNameString == "ByteProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::Byte);

		if (TMPNameString == "Int8Property")   RTypeValue(TMPUClass, EPropertyGenFlags::Int8);
		if (TMPNameString == "Int16Property")  RTypeValue(TMPUClass, EPropertyGenFlags::Int16);
		if (TMPNameString == "IntProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::Int);
		if (TMPNameString == "Int64Property")  RTypeValue(TMPUClass, EPropertyGenFlags::Int64);

		if (TMPNameString == "UInt16Property") RTypeValue(TMPUClass, EPropertyGenFlags::UInt16);
		if (TMPNameString == "UInt32Property") RTypeValue(TMPUClass, EPropertyGenFlags::UInt32);
		if (TMPNameString == "UInt64Property") RTypeValue(TMPUClass, EPropertyGenFlags::UInt64); // UnsizedInt, UnsizedUInt

		if (TMPNameString == "FloatProperty")  RTypeValue(TMPUClass, EPropertyGenFlags::Float);
		if (TMPNameString == "DoubleProperty") RTypeValue(TMPUClass, EPropertyGenFlags::Double);

		if (TMPNameString == "BoolProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::Bool);

		if (TMPNameString == "SoftClassProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::SoftClass);
		if (TMPNameString == "WeakObjectProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::WeakObject);
		if (TMPNameString == "LazyObjectProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::LazyObject);
		if (TMPNameString == "SoftObjectProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::SoftObject);

		if (TMPNameString == "ClassProperty")		 RTypeValue(TMPUClass, EPropertyGenFlags::Class);
		if (TMPNameString == "ObjectProperty")		 RTypeValue(TMPUClass, EPropertyGenFlags::Object);
		if (TMPNameString == "InterfaceProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::Interface);

		if (TMPNameString == "NameProperty")   RTypeValue(TMPUClass, EPropertyGenFlags::Name);
		if (TMPNameString == "StrProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::Str);
		if (TMPNameString == "ArrayProperty")  RTypeValue(TMPUClass, EPropertyGenFlags::Array);
		if (TMPNameString == "MapProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::Map);
		if (TMPNameString == "SetProperty")    RTypeValue(TMPUClass, EPropertyGenFlags::Set);

		if (TMPNameString == "StructProperty")			RTypeValue(TMPUClass, EPropertyGenFlags::Struct);
		if (TMPNameString == "DelegateProperty")		RTypeValue(TMPUClass, EPropertyGenFlags::Delegate);

		if (TMPNameString == "MulticastInlineDelegateProperty")		RTypeValue(TMPUClass, EPropertyGenFlags::InlineMulticastDelegate);
		if (TMPNameString == "MulticastSparseDelegateProperty")		RTypeValue(TMPUClass, EPropertyGenFlags::SparseMulticastDelegate);

		if (TMPNameString == "TextProperty")		RTypeValue(TMPUClass, EPropertyGenFlags::Text);
		if (TMPNameString == "EnumProperty")		RTypeValue(TMPUClass, EPropertyGenFlags::Enum);

		if (TMPNameString == "Function")			RTypeValue(TMPUClass, EPropertyGenFlags::Function);
		if (TMPNameString == "DelegateFunction")	RTypeValue(TMPUClass, EPropertyGenFlags::DelegateFunction);


		
		return EPropertyGenFlags::unknown;
	}

	//获取一个类的 指定成员偏移量
	long long findPropertyOffset(UE4$UClass * _kUClass, const char * _symbol) {
		UE4$UProperty * TMPProperty = NULL;
		//第一步: 遍历所有的 类 对象
		for (UE4$UClass * i = _kUClass; i != NULL; i = UE4::UClass2SuperClass(i)) {
			//第二步: 遍历类的所有ivar偏移
			UE4::enumUProperty(i, [_symbol, &TMPProperty](UE4$UProperty * _kProperty) {
				if (UE4::FName_ToString(&_kProperty->NamePrivate) == _symbol)
					TMPProperty = _kProperty;
				return (TMPProperty != NULL);
			});
		}
		return ((NULL == TMPProperty) ? -1 : TMPProperty->Offset_Internal);
	}

	//获取一个类的 指定成员偏移量
	long long findPropertyOffset(const char * _package, const char * _class, const char * _symbol) {
		UE4$UClass * kClass = UE4::findUE4Class(_package, _class);
		if (NULL == kClass) return -1;
		return UE4::findPropertyOffset(kClass, _symbol);
	}

	UE4$UFunction * findUFunction(const char * _package, const char * _class, const char * _symbol) {
		UE4$UClass * kClass = UE4::findUE4Class(_package, _class);
		if (NULL == kClass) return NULL;

		for (UE4$UClass * i = kClass; i != NULL; i = UE4::UClass2SuperClass(i)) {
			UE4$UFunction * rUFunction = NULL;
			UE4::enumUFunction(kClass, [&rUFunction, _symbol](UE4$UFunction * TMPUFunction) {
				uint64_t    TMPNamePrivate  = TMPUFunction->NamePrivate;
				if (UE4::FName_ToString(&TMPNamePrivate) != _symbol)
					return false;

				return NULL != (rUFunction = TMPUFunction);
			});

			if (TRUE == _UE4ObjectISValid(rUFunction))
				return rUFunction;
		}
		return NULL;
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	void enumUObject(std::function<bool(const UE4$UObjectHEAD &, const UObject *)> enumCallback) {
		uint32_t TMPObjectCount = _2UE4UObjectCount();
		for (uint32_t kIndex = 0; kIndex < TMPObjectCount; kIndex++) {
			const UObject * _UObject = NULL;
			if (NULL == (_UObject = _2UE4UObjectPtr(kIndex)))
				continue;

			UE4$UObjectHEAD TMPHeadValue;
			if (FALSE == UE4::enterUObjectHEAD(_UObject, &TMPHeadValue))
				continue;

			if (true == enumCallback(TMPHeadValue, _UObject))
				break;
		}
	}
	void enumUObject(const void * kObject, std::function<bool(const UE4$UObjectHEAD &, const UObject *)> enumCallback) {
		uint32_t TMPObjectCount = _2UE4UObjectCount();
		for (uint32_t kIndex = 0; kIndex < TMPObjectCount; kIndex++) {
			const UObject * _UObject = NULL;
			if (NULL == (_UObject = _2UE4UObjectPtr(kIndex)))
				continue;

			UE4$UObjectHEAD TMPHeadValue;
			if (FALSE == UE4::enterUObjectHEAD(_UObject, &TMPHeadValue))
				continue;

			if ((uint64_t)kObject != (uint64_t)TMPHeadValue.ClassPrivate)
				continue;

			if (true == enumCallback(TMPHeadValue, _UObject))
				break;
		}
	}

	void enumUPackage(std::function<bool(std::string UPackageString)> enumCallback) {
		//第一步: 遍历所有对象, 初始化所有类结构
		UE4::RefUClassLISTByUObject();
		//第二步: 遍历所有的 类信息, 并且记录相关包信息
		std::map<std::string, int>	TMPBufferLIST;
		for (auto & kClassBuffer : UE4::_GClassBufferLIST) {
			const char * kString = 
				kClassBuffer.second._package.getBuffer();

			if (TMPBufferLIST.find(kString) == TMPBufferLIST.end()){
				TMPBufferLIST.insert(std::pair<std::string, int>(
					kString,
					0)
				);
			}

			TMPBufferLIST[kString]++;
		}
		//第三步: 降所有记录的包名称, 返回
		for (auto  i = TMPBufferLIST.begin(); i != TMPBufferLIST.end(); i++)
			if (true == enumCallback(i->first))
				break;
	}

	void enumUClass(std::function<bool(UE4$UClass *, std::string CString, std::string PString, std::string NString)> enumCallback) {
		//第一步: 遍历所有对象, 初始化所有类结构
		UE4::RefUClassLISTByUObject();
		//第二步: 遍历所有的 类信息,传回相关信息
		for (auto & kClassBuffer : UE4::_GClassBufferLIST) {
			_tagTMPClassINFO TMPString = kClassBuffer.second;

			if (true == enumCallback(kClassBuffer.first,
				TMPString._config.getBuffer(),
				TMPString._package.getBuffer(),
				TMPString._name.getBuffer()))
				break;
		}
	}

	void enumUFunction(UE4$UClass * _kClass, std::function<bool(UE4$UFunction *)> enumCallback) {

		UE4$FArray TMPArrayBuffer = { NULL };
		if (FALSE == UE4::readMemory(_kClass->_2UFunctionArray(), &TMPArrayBuffer, sizeof(UE4$FArray)))
			return;

		for (uint32_t fIndex = 0; NULL != TMPArrayBuffer.objects && fIndex < TMPArrayBuffer._count; fIndex++) {
			uint64_t TMPFunctionBuffer = NULL;
			
			TMPFunctionBuffer += (uint64_t)TMPArrayBuffer.objects;
			TMPFunctionBuffer += (sizeof(UE4$UFunctionMAP) * fIndex);

			UE4$UFunctionMAP TMPArrayBuffer;
			if (FALSE == UE4::readMemory((void *)TMPFunctionBuffer, &TMPArrayBuffer, sizeof(UE4$UFunctionMAP)))
				continue;

			UE4$UFunction TMPBuffer;
			if (FALSE == UE4::readMemory(TMPArrayBuffer.uFunction, &TMPBuffer, sizeof(UE4$UFunction)))
				continue;

			if (true == enumCallback((UE4$UFunction *)TMPArrayBuffer.uFunction))
				break;
		}
	}

#define ENTERPropertyBuffer(p)    UE4::readMemory(p, &TMPBuffer, sizeof(UE4$UProperty))

	void enumUProperty(UE4$UClass * _kClass, std::function<bool(UE4$UProperty *)> enumCallback) {
		UE4$UProperty TMPBuffer;

		//第一步: 记下所有 方法信息
		std::list<UE4$UFunction * > TMPFunctionLIST;
		UE4::enumUFunction(_kClass, [&TMPFunctionLIST](UE4$UFunction * TMPFunction) {
			TMPFunctionLIST.push_back(TMPFunction);
			return FALSE;
		});

		//第二步: 遍历所有的属性表
		for (UE4$UProperty * i = _kClass->PropertyLink; ENTERPropertyBuffer(i); i = i->_2NextProperty()) {
			if (_kClass != i->OuterPrivate)
				break;

			BOOL fUFunctionStatus = FALSE; //检测是否为 一个 函数信息
			for (auto kf = TMPFunctionLIST.begin(); kf != TMPFunctionLIST.end(); kf++){
				if ((uint64_t)*kf != (uint64_t)i)
					continue;

				fUFunctionStatus = TRUE;
				break;
			}

			if (TRUE == fUFunctionStatus ? FALSE : true == enumCallback(i))
				break;
		}
	}
	void enumUProperty(UE4$UProperty * _kProperty, std::function<bool(UE4$UProperty *)> enumCallback) {
		UE4$UProperty TMPBuffer;

		for (UE4$UProperty * i = _kProperty; ENTERPropertyBuffer(i); i = i->_2NextProperty()) {
			if (true == enumCallback(i))
				break;
		}
	}

	void enumUEnum(std::function<bool(UE4$UEnum *)> enumCallback) {
		UE4$UClass * _kClass = NULL;
		if (NULL == (_kClass = UE4::findUE4Class("/Script/CoreUObject", "EnumProperty"))) {
			return;
		}

		std::map<const UObject *, int> TMPUObjectLIST;

#define PUSHUObjectBuffer(b, cmd)		{														\
											auto TMPIterator = TMPUObjectLIST.find(b);			\
											if (TMPIterator == TMPUObjectLIST.end()){			\
												TMPUObjectLIST.insert(std::pair<				\
													const UObject *, int>(b, 1)					\
												);	cmd;										\
											}													\
											TMPIterator->second++;								\
										}

		UE4::enumUObject([_kClass, &TMPUObjectLIST](const UE4$UObjectHEAD & _UObjectHead, const UObject * _UObject) {
			//类 是否 为 EnumProperty
			if (_kClass != _UObjectHead.ClassPrivate)
				return false;

			//直接强转即可
			UE4$UEnumProperty * kEnumValue = (UE4$UEnumProperty *)_UObject;

			UE4$UObjectHEAD TMPHeadValue;
			if (FALSE == UE4::enterUObjectHEAD(kEnumValue->Enum, &TMPHeadValue))
				return false;

			PUSHUObjectBuffer(kEnumValue->Enum, return false);
		}); //遍历所有的 UEnumProperty 属性, 得到所有的 UEnum 对象

		//遍历所有的数据结构, 并且返回
		for (auto i = TMPUObjectLIST.begin(); i != TMPUObjectLIST.end(); i++){
			if (true == enumCallback((UE4$UEnum *)i->first))
				break;
		}
	}

	void enumUStruct(std::function<bool(UE4$UStruct *)> enumCallback) {
		UE4$UClass * _kClass = NULL;
		if (NULL == (_kClass = UE4::findUE4Class("/Script/CoreUObject", "StructProperty"))) {
			return;
		}

		std::map<const UObject *, int> TMPUObjectLIST;

#define PUSHUObjectBuffer(b, cmd)		{														\
											auto TMPIterator = TMPUObjectLIST.find(b);			\
											if (TMPIterator == TMPUObjectLIST.end()){			\
												TMPUObjectLIST.insert(std::pair<				\
													const UObject *, int>(b, 1)					\
												);	cmd;										\
											}													\
											TMPIterator->second++;								\
										}

		UE4::enumUObject([_kClass, &TMPUObjectLIST](const UE4$UObjectHEAD & _UObjectHead, const UObject * _UObject) {
			//类 是否 为 StructProperty
			if (_kClass != _UObjectHead.ClassPrivate)
				return false;

			//直接强转即可
			UE4$UStructProperty * kStructValue = (UE4$UStructProperty *)_UObject;

			if (FALSE == _UE4ObjectISValid(kStructValue))
				return false;
			
			for (auto i = kStructValue->Struct; _UE4ObjectISValid(i); i = i->SuperStruct){
				PUSHUObjectBuffer(i, continue);
			}
			//PUSHUObjectBuffer(kStructValue->Struct, return false);

			return false;
		}); //遍历所有的 StructProperty 属性, 得到所有的 UE4$UStruct 对象

		//遍历所有的数据结构, 并且返回
		for (auto i = TMPUObjectLIST.begin(); i != TMPUObjectLIST.end(); i++) {
			if (true == enumCallback((UE4$UStruct *)i->first))
				break;
		}
	}


	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	//获取类的 包名
	std::string UClass2UPackage(UE4$UClass * kClass) {
		if (NULL == kClass) return "";

		UE4$UObjectHEAD TMPUPackageHEAD;
		if (FALSE == UE4::enterUObjectHEAD(kClass->OuterPrivate, &TMPUPackageHEAD))
			return "";

		return UE4::FName_ToString(&TMPUPackageHEAD.NamePrivate);
	}

	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


	const UObject * ProcessEventCallback(const UObject * _pthis, const UE4$UFunction * uFunction, void * params) {
		static void * _call = 0;
		if (NULL == _call) _call = _2SYMPointer(UObject$ProcessEvent);
		if (NULL == _call) UE4_logEString("定位方法: public: class FString const & FText::ToString(void)const , 异常!!");

		typedef const UObject * (*CALLProcessEvent)(const UObject *, const UE4$UFunction *, void *);

		return ((CALLProcessEvent)_call)(_pthis, uFunction, params);
	}

}










//std::list<UE4$UEnumProperty *> TMPPropertyLIST;
//
//UE4::enumUClass([&TMPPropertyLIST](UE4$UClass * _kClass, std::string CString, std::string PString, std::string NString) {
//
//	UE4::enumUProperty(_kClass, [&TMPPropertyLIST](UE4$UProperty * _kProperty) {
//		if (EPropertyTYPE::Enum == EPropertyTYPE_GetTYPE(_kProperty)){
//			TMPPropertyLIST.push_back((UE4$UEnumProperty *)
//				_kProperty
//			);
//		}
//		return false;
//	});

//	std::list<UE4$UProperty *> TMPPropertyLinkLIST;
//	UE4::enumUFunction(_kClass, [&TMPPropertyLinkLIST](UE4$UFunction * TMPFunction) {
//		TMPPropertyLinkLIST.push_back(TMPFunction->PropertyLink);
//		return false;
//	});

//	for (auto i = TMPPropertyLinkLIST.begin(); i != TMPPropertyLinkLIST.end(); i++) {
//		UE4::enumUProperty(*i, [&TMPPropertyLIST](UE4$UProperty * _kProperty) {
//			if (EPropertyTYPE::Enum == EPropertyTYPE_GetTYPE(_kProperty)) {
//				TMPPropertyLIST.push_back((UE4$UEnumProperty *)
//					_kProperty
//				);
//			}
//			return false;
//		});
//	}

//	return false;
//});  //枚举所有的 类对象, 并且遍历所有的相关结构信息

//for (auto i = TMPPropertyLIST.begin(); i != TMPPropertyLIST.end(); i++){
//	UE4$UObjectHEAD TMPHeadValue;
//	if (FALSE == UE4::enterUObjectHEAD((*i)->Enum, &TMPHeadValue))
//		continue;

//	PUSHUObjectBuffer((*i)->Enum, continue);
//}












//const UFunction * findUFunctionBySuper(const UClass * arg_UClass, const char * _funString) {
//	int _findLevel = 0; const UFunction  * _keyFunction = NULL;
//	for (const UClass * i = arg_UClass; i != NULL; i = UClass2SuperClass(i)) {
//
//		
//		UE4::enumUFunction(i, [&_keyFunction, _funString](const _tagUFunction * _UFunction) {
//
//			if (false == stricmpex(_UFunction->_name, _funString))
//				return false;;
//
//			return NULL != (_keyFunction = _UFunction->_UFunction);
//		});
//
//		if (NULL != _keyFunction || 30 < _findLevel++)
//			break;
//	}
//
//	return _keyFunction;
//}
//
//const UFunction * findUFunction(const UObject * _UObject, const char * _funString) {
//	struct _tagUObjectHead t_headBuffer;
//	if (FALSE == UE4::enterUObjectPointer(_UObject, &t_headBuffer)) {
//		return NULL;
//	}
//	return findUFunctionBySuper(t_headBuffer.ClassPrivate, _funString);
//}
//
//const UFunction * findUFunction(const char * _package, const char * _class, const char * _funString) {
//	const UClass  * _keyClass = NULL;
//	if (NULL == (_keyClass = findUE4Class(_package, _class))) {
//		return NULL;
//	}
//	return findUFunctionBySuper(_keyClass, _funString);
//}
//
