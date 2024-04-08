#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"
//
#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"


static bool findString_lower(const char * mString, const char * fString) {
	if (NULL == mString || NULL == fString) return false;
	std::string mainString = mString;
	std::string findString = fString;

	transform(mainString.begin(), mainString.end(), mainString.begin(), ::tolower);
	transform(findString.begin(), findString.end(), findString.begin(), ::tolower);

	return std::string::npos != mainString.find(findString.c_str());
}

//命令行执行 : 获取所有的 包 信息
static void CMD_ReadPackageLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	retJson.AddEmptySubArray("list");
	UE4::enumUPackage([&retJson](std::string UPackageString) {
		retJson["list"].Add(UPackageString.c_str());
		return false;
	});
}

typedef std::map<const UE4$UClass *, int>  UObjectCountType;

//读取到所有 虚幻对象类型个数
static void CCallBack_ReadUObjectCount(UObjectCountType & _UObjectCount) {
	UE4::enumUObject([&_UObjectCount](const UE4$UObjectHEAD & TMPHeadValue, const UObject *) {

		if (_UObjectCount.find(TMPHeadValue.ClassPrivate) == _UObjectCount.end()) {
			_UObjectCount.insert(std::pair<const UE4$UClass*, int>(
				TMPHeadValue.ClassPrivate,
				0)
			);
		}
		_UObjectCount[TMPHeadValue.ClassPrivate]++;
		return false;
	}); 
}

//读取类的基础信息 到 JSON 缓冲区
static void CCallBack_UClass2JSON(UObjectCountType & _UObjectCount, UE4$UClass * _kClass, std::string CString, 
											std::string PString, std::string NString, JSONBuffer & JSONClass) {

	JSONWriteValue(JSONClass, "package"		, PString.c_str());
	JSONWriteValue(JSONClass, "name"		, NString.c_str());
	JSONWriteValue(JSONClass, "config"		, CString.c_str());
	JSONWriteValue(JSONClass, "size"		, _kClass->PropertiesSize);

	UE4$FArray TMPArrayBuffer = { NULL };
	if (FALSE == UE4::readMemory(_kClass->_2UFunctionArray(), &TMPArrayBuffer, sizeof(UE4$FArray)))
		memset(&TMPArrayBuffer, 0, sizeof(UE4$FArray));

	JSONWriteValue(JSONClass, "funcCount"	, TMPArrayBuffer._count);

	uint32_t propCount = 0;
	UE4::enumUProperty(_kClass, [&propCount](UE4$UProperty * ) {
		propCount = propCount + 1;
		return false;
	});

	JSONWriteValue(JSONClass, "propCount"	, propCount);

	JSONWriteValue_UInt64(JSONClass, "pointer", _kClass);

	uint32_t UObjectCount = 0;
	if (_UObjectCount.find(_kClass) != _UObjectCount.end()) {
		UObjectCount = _UObjectCount[_kClass];
	}

	JSONWriteValue(JSONClass, "objectCount", UObjectCount);
}


//命令行执行 : 获取所有的 类 信息
static void CMD_ReadClassLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_class = "";
	std::string arg_package = "";

	JSONArgsTry_Get(args, "class"	, arg_class   , "");
	JSONArgsTry_Get(args, "package"	, arg_package , "");

	UObjectCountType _UObjectCount; 
	CCallBack_ReadUObjectCount(_UObjectCount); //读取到所有虚幻对象数目

	retJson.AddEmptySubArray("classs");
	UE4::enumUClass([&_UObjectCount, &arg_class, &arg_package, &retJson](UE4$UClass * _kClass, std::string CString, std::string PString, std::string NString) {
		if (NULL == _kClass)
			return false;

		if ("" != arg_package && arg_package != PString){
			return false;
		}

		if ("" != arg_class && false == findString_lower(NString.c_str(), arg_class.c_str())) {
			return false;
		}

		JSONBuffer JSONClass;

		CCallBack_UClass2JSON(_UObjectCount, _kClass, CString, 
									PString, NString, JSONClass);

		retJson["classs"].Add(JSONClass);

		return false;
	});
}


static int CCallBack_ReadSuperARGS(const JSONBuffer & args, std::list<const UE4$UClass *> & allSuperUClass) {
	std::string arg_package = "";

	JSONBuffer _allSuper;
	if (false == args.Get("super", _allSuper) || false == _allSuper.IsArray())
		return 0;

	for (size_t i = 0; i < _allSuper.GetArraySize(); i++){
		if (false == _allSuper[i].KeyExist("class"))
			continue;
		if (false == _allSuper[i].KeyExist("package"))
			continue;

		std::string arg_class = "";
		std::string arg_package = "";

		JSONArgsTry_Get(_allSuper[i], "class"	, arg_class, "");
		JSONArgsTry_Get(_allSuper[i], "package"	, arg_package, "");

		UE4$UClass * _findClass = NULL;
		if (NULL != (_findClass = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str()))) {
			allSuperUClass.push_back((UE4$UClass *)_findClass);
		}
	}
	return (int)allSuperUClass.size();
}

static BOOL CCallBack_EnterSuperClass(UE4$UClass * _StartUClass, std::list<const UE4$UClass *> & allSuperUClass) {

	int _findLevel = 0;
	for (UE4$UClass * i = _StartUClass; NULL != i; i = UE4::UClass2SuperClass(i)) {

		for (auto _SuperClass : allSuperUClass) {
			if (_SuperClass != i) 
				continue;
			return TRUE;
		}
		
		if (30 < _findLevel++) break;

		if (FALSE == _UE4ObjectISValid(_StartUClass))
			break;
	}
	return FALSE;
}

//命令行执行 : 获取所有的 类 信息
static void CMD_ReadClassLISTBySuper(const JSONBuffer & args, JSONBuffer & retJson) {
	JSONArgsAssert(args, retJson, "super");
	
	std::list<const UE4$UClass *>  tSuperClassLIST;  //得到传入的 所有 父级类 信息
	if (0 >= CCallBack_ReadSuperARGS(args, tSuperClassLIST)) {
		JSONWriteERRString(retJson, "super empty");
		return;
	}

	UObjectCountType _UObjectCount;
	CCallBack_ReadUObjectCount(_UObjectCount); //读取到所有虚幻对象数目

	//第二步: 得到类对象
	retJson.AddEmptySubArray("classs");
	UE4::enumUClass([&_UObjectCount, &tSuperClassLIST, &retJson](UE4$UClass * _kClass, std::string CString, std::string PString, std::string NString) {
		if (FALSE == CCallBack_EnterSuperClass(_kClass, tSuperClassLIST)) {
			return false;
		}

		JSONBuffer JSONClass;

		CCallBack_UClass2JSON(_UObjectCount, _kClass, CString,
			PString, NString, JSONClass);

		retJson["classs"].Add(JSONClass);

		return false;
	});
}

std::string CCallBack_2OtherTYPEString(EPropertyTYPE Type, UE4$UProperty * _kProperty) {
	std::string  rString = "";

	UE4$UClass TMPClassBuffer;

	switch (Type) {
	case EPropertyTYPE::SoftClass: {
		UE4$USoftClassProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$USoftClassProperty))){
			if (UE4::readMemory(kBuffer.PropertyClass, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		 break;
	case  EPropertyTYPE::Class: {
		UE4$UClassProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UClassProperty))) {
			if (UE4::readMemory(kBuffer.PropertyClass, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;
	case  EPropertyTYPE::Object: {
		UE4$UObjectProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UObjectProperty))) {
			if (UE4::readMemory(kBuffer.PropertyClass, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;
	case  EPropertyTYPE::Interface: {
		UE4$UInterfaceProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UInterfaceProperty))) {
			if (UE4::readMemory(kBuffer.InterfaceClass, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;

	case  EPropertyTYPE::Struct: {
		UE4$UStructProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UStructProperty))) {
			if (UE4::readMemory(kBuffer.Struct, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;
	case  EPropertyTYPE::Enum: {
		UE4$UEnumProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UEnumProperty))) {
			if (UE4::readMemory(kBuffer.Enum, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;
	case  EPropertyTYPE::unknown: {
		UE4$UProperty kBuffer;
		if (UE4::readMemory(_kProperty, &kBuffer, sizeof(UE4$UProperty))) {
			if (UE4::readMemory(kBuffer.ClassPrivate, &TMPClassBuffer, sizeof(UE4$UClass))) {
				rString = UE4::FName_ToString(&TMPClassBuffer.NamePrivate);
			}
		}
	}
		break;
	default:
		break;
	}
	return rString;
}
static void CCallBack_Property2JSON(UE4$UProperty * _kProperty, JSONBuffer & retJson) {
	EPropertyTYPE TMPType = EPropertyTYPE_GetTYPE(_kProperty);

	JSONBuffer JSONProperty;

	JSONWriteValue(JSONProperty, "name"			, UE4::FName_ToString(&_kProperty->NamePrivate).c_str());
	JSONWriteValue(JSONProperty, "type"			, (int)TMPType);
	JSONWriteValue(JSONProperty, "ObjectFlags"	, _kProperty->ObjectFlags);
	JSONWriteValue(JSONProperty, "ArrayDim"		, _kProperty->ArrayDim);
	JSONWriteValue(JSONProperty, "Offset"		, _kProperty->Offset_Internal);

	switch ((EPropertyGenFlags)TMPType) {
	case EPropertyGenFlags::Bool:
		JSONWriteValue(JSONProperty, "mask", ((UE4$UBoolProperty*)_kProperty)->ByteMask);
		break;
	default:
		JSONWriteValue(JSONProperty, "mask", 0)
			break;
	}

	JSONWriteValue_UInt64(JSONProperty, "PropertyFlags", _kProperty->PropertyFlags);

	JSONWriteValue(JSONProperty, "type_other", CCallBack_2OtherTYPEString(TMPType, _kProperty).c_str());

	retJson.Add(JSONProperty);
}
static void CCallBack_EnumPropertyLIST(UE4$UClass * _kClass, JSONBuffer & retJson) {
	UE4::enumUProperty(_kClass, [&retJson](UE4$UProperty * _kProperty) {
		CCallBack_Property2JSON(_kProperty, retJson);
		return FALSE;
	});
}
static void CCallBack_EnumPropertyLIST(UE4$UProperty * _kProperty, JSONBuffer & retJson) {
	UE4::enumUProperty(_kProperty, [&retJson](UE4$UProperty * _kProperty) {
		CCallBack_Property2JSON(_kProperty, retJson);
		return FALSE;
	});
}

//命令行执行 : 获取所有的 类 的 函数列表
static void CMD_ReadFunctionLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_class = "";
	std::string arg_package = "";

	JSONArgsAssert_Get(args, retJson, "class"	, arg_class);
	JSONArgsAssert_Get(args, retJson, "package"	, arg_package);

	if ("" == arg_class || "" == arg_package || "" == arg_package) {
		JSONWriteERRString(retJson, "arg empty");
		return;
	}

	UE4$UClass * _kClass = NULL;
	if (NULL == (_kClass = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str()))) {
		JSONWriteERRString(retJson, "not find class");
		return;
	}

	retJson.AddEmptySubArray("Functions");

	UE4::enumUFunction(_kClass, [_kClass, arg_class, &retJson](UE4$UFunction * TMPFunction) {
		std::string NString = UE4::FName_ToString(&TMPFunction->NamePrivate);

		JSONBuffer JSONFunction;
		JSONWriteValue_UInt64(JSONFunction, "class"		, _kClass);
		JSONWriteValue_UInt64(JSONFunction, "pointer"	, UE4::_2MModuleOffset(TMPFunction->Func));
		JSONWriteValue		 (JSONFunction, "name"		, NString.c_str());
		JSONWriteValue		 (JSONFunction, "argsSize"	, TMPFunction->PropertiesSize);
		JSONWriteValue		 (JSONFunction, "original"  , UE4::_2MethodOString(arg_class, TMPFunction));

		JSONBuffer JSONArgsLIST;

		CCallBack_EnumPropertyLIST(TMPFunction->PropertyLink, JSONArgsLIST);
		JSONWriteValue		 (JSONFunction, "args"		, JSONArgsLIST);

		retJson["Functions"].Add(JSONFunction);
		return false;
	});
}

//命令行执行 : 获取所有的 类 的 成员变量列表
static void CMD_ReadPropertyLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_class = "";
	std::string arg_package = "";

	JSONArgsAssert_Get(args, retJson, "class", arg_class);
	JSONArgsAssert_Get(args, retJson, "package", arg_package);

	if ("" == arg_class || "" == arg_package || "" == arg_package) {
		JSONWriteERRString(retJson, "arg empty");
		return;
	}

	UE4$UClass * _kClass = NULL;
	if (NULL == (_kClass = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str()))) {
		JSONWriteERRString(retJson, "not find class");
		return;
	}

	JSONBuffer JSONPropertyLIST;

	CCallBack_EnumPropertyLIST(_kClass, JSONPropertyLIST);

	JSONWriteValue(retJson, "PropertyLIST", JSONPropertyLIST);
}

//const _tagUFunction* findUE4Function(const UClass * _kUClass, const char * _symbol) {
//	//第一步: 遍历所有的 类 对象
//	const  _tagUFunction *   _rValue;
//	struct _tagClassInfo     _UClassInfo;
//	
//	int _findLevel = 0;
//	for (const UClass * i = _kUClass; NULL != i; i = UClass2SuperClass(i)) {
//		//第二步: 得到类的所有ivar偏移
//		UE4::enumUFunction(i, [_symbol, &_rValue](const _tagUFunction * UFunctionBuffer) {
//			if (NULL == UFunctionBuffer->_name)
//				return false;
//
//			if (FALSE == stricmpex(UFunctionBuffer->_name, _symbol))
//				return false;
//
//			_rValue = UFunctionBuffer;
//			return true;
//		});
//
//		if (NULL != _rValue || 30 < _findLevel++) 
//			break;
//
//		struct _tagClassInfo _TMPUClassBuffer;
//		if (FALSE == UE4::readUClassInfo(i, _TMPUClassBuffer)) {
//			continue;
//		}
//		if (TRUE == stricmpex(_TMPUClassBuffer._name, "UObject"))
//			break;
//	}
//	return _rValue;
//}
//
//static void ue4_getUFunction(const JSONBuffer & args, JSONBuffer & retJson) {
//	std::string arg_class = "";
//	std::string arg_package = "";
//	std::string arg_method = "";
//
//	JSONArgsAssert_Get(args, retJson, "class"	, arg_class);
//	JSONArgsAssert_Get(args, retJson, "package"	, arg_package);
//	JSONArgsAssert_Get(args, retJson, "method"	, arg_method);
//
//	if ("" == arg_class || "" == arg_package || "" == arg_method) {
//		JSONWriteERRString(retJson, "arg empty");
//		return;
//	}
//
//	const UClass * t_findUClass = NULL;
//	if (NULL == (t_findUClass = findUE4Class(arg_package.c_str(), arg_class.c_str()))) {
//		JSONWriteERRString(retJson, "not find class");
//		return;
//	}
//
//	const _tagUFunction * t_findUFunction = NULL;
//	if (NULL == (t_findUFunction = findUE4Function(t_findUClass, arg_method.c_str()))) {
//		JSONWriteERRString(retJson, "not find method");
//		return;
//	}
//
//	struct _tagClassInfo _UClassInfo = { NULL };
//	if (FALSE == UE4::readUClassInfo(t_findUFunction->_UClass, _UClassInfo)) {
//		JSONWriteERRString(retJson, "not find class");
//		return;
//	}
//		
//	JSONBuffer _UFunctionJSON;
//	JSONWriteValue(_UFunctionJSON, "class_start"		, arg_class);
//	JSONWriteValue(_UFunctionJSON, "package_start"	    , arg_package);
//	JSONWriteValue(_UFunctionJSON, "class_end"			, _UClassInfo._name);
//	JSONWriteValue(_UFunctionJSON, "package_end"		, _UClassInfo._package);
//	JSONWriteValue(_UFunctionJSON, "method"				, arg_method);
//	JSONWriteValue(_UFunctionJSON, "original"			, getMethod_original(&_UClassInfo, t_findUFunction));
//	JSONWriteValue(_UFunctionJSON, "argsSize"			, t_findUFunction->_argSize);
//
//	JSONBuffer _UFunctionArgsJSON;
//
//	ue4_getPropertylist(t_findUFunction->_UFunction, _UFunctionArgsJSON);
//
//	JSONWriteValue(_UFunctionJSON, "args", _UFunctionArgsJSON);
//
//	//获取 类的继承关系
//	JSONBuffer _UFunctionSuperJSON;
//
//	int _findLevel = 0;
//	for (const UClass * _UClass = findUE4Class(arg_package.c_str(), arg_class.c_str()); NULL != _UClass; _UClass = UClass2SuperClass(_UClass)) {
//		JSONBuffer _classJSON;
//
//		struct _tagClassInfo _UClassInfo = { NULL };
//		if (NULL != _UClass && TRUE == UE4::readUClassInfo(_UClass, _UClassInfo)) {
//			JSONWriteValue(_classJSON, "package", _UClassInfo._package);
//			JSONWriteValue(_classJSON, "class"  , _UClassInfo._name);
//		}
//
//		_UFunctionSuperJSON.Add(_classJSON);
//
//		//检测是否为 UObject
//		if (30 < _findLevel++ || TRUE == stricmpex(_UClassInfo._name, "UObject"))
//			break;
//	}
//
//	JSONWriteValue(_UFunctionJSON, "super", _UFunctionSuperJSON);
//
//	//最后, 返回 函数的基础信息
//	JSONWriteValue(retJson, "info", _UFunctionJSON);
//}

//命令行执行 : 获取所有的 类 的所有父级类
static void CMD_ReadSuperClassLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_class	= "";
	std::string arg_package = "";

	JSONArgsAssert_Get(args, retJson, "class"	, arg_class);
	JSONArgsAssert_Get(args, retJson, "package"	, arg_package);

	if ("" == arg_class || "" == arg_package || "" == arg_package){
		JSONWriteERRString(retJson, "arg empty");
		return;
	}

	retJson.AddEmptySubArray("super");

	for (UE4$UClass * _UClass = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str()); 
							NULL != _UClass; _UClass = UE4::UClass2SuperClass(_UClass)) {

		std::string PString = UE4::UClass2UPackage(_UClass);
		std::string NString = UE4::FName_ToString(&_UClass->NamePrivate);

		if (NString == "" || NString == "*INVALID*")
			break;

		JSONBuffer JSONClass;

		JSONWriteValue(JSONClass, "package"	, PString.c_str());
		JSONWriteValue(JSONClass, "class"	, NString.c_str());

		retJson["super"].Add(JSONClass);
	}
}

static BOOL CCallBack_UEnum2PNString(UE4$UEnum * _kUEnum, std::string & rPString, std::string & rNString) {
	if (FALSE == _UE4ObjectISValid(_kUEnum))
		return FALSE;

	UE4$UObjectBase * TMPUPackage = (UE4$UObjectBase*)_kUEnum->OuterPrivate;
	if (NULL == TMPUPackage || FALSE == _UE4ObjectISValid(TMPUPackage))
		return false;

	rNString = UE4::FName_ToString(&_kUEnum->NamePrivate);
	rPString = UE4::FName_ToString(&TMPUPackage->NamePrivate);

	return "" != rPString && "" != rNString;
}

//命令行执行 : 获取所有的 枚举 的 基础属性信息
static void CMD_ReadUEnumLIST(const JSONBuffer & args, JSONBuffer & retJson) {

	std::string arg_enum = "";
	std::string arg_package = "";

	JSONArgsTry_Get(args, "enum"	, arg_enum   , "");
	JSONArgsTry_Get(args, "package"	, arg_package, "");

	retJson.AddEmptySubArray("enums");
	UE4::enumUEnum([arg_enum, arg_package, &retJson](UE4$UEnum * TMPUEnumBuffer) {
		std::string _PString = "";
		std::string _NString = "";
		if (FALSE == CCallBack_UEnum2PNString(TMPUEnumBuffer, _PString, _NString))
			return false;
		
		//根据 key, 进行 匹配信息
		if ("" != arg_enum && NULL == findString_lower(_NString.c_str(), arg_enum.c_str())) {
			return false;
		}
		if ("" != arg_package && arg_package != _PString) {
			return false;
		}

		JSONBuffer JSONEnumBuffer;

		JSONWriteValue(JSONEnumBuffer, "name"	, _NString.c_str());
		JSONWriteValue(JSONEnumBuffer, "package", _PString.c_str());
		JSONWriteValue(JSONEnumBuffer, "count"	, TMPUEnumBuffer->Names._count);

		JSONEnumBuffer.AddEmptySubArray("values");
		for (size_t iIndex = 0; iIndex < TMPUEnumBuffer->Names._count; iIndex = iIndex + 1) {
			uint64_t kName = 0;
			if (0 == (kName = TMPUEnumBuffer->I2FName(iIndex)))
				break;

			JSONBuffer _valueJSON;

			JSONWriteValue(_valueJSON, "key"  , UE4::FName_ToString(&kName).c_str());
			JSONWriteValue(_valueJSON, "value", TMPUEnumBuffer->I2Value(iIndex));

			JSONEnumBuffer["values"].Add(_valueJSON);
		}

		JSONWriteValue(retJson, "pointer", CString::format("0x%016I64X", TMPUEnumBuffer));

		retJson["enums"].Add(JSONEnumBuffer);
		return false;
	});
}

//命令行执行 : 获取所有的 类 的 基础属性信息
static void CMD_ReadUClassINFO(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_class = "";
	std::string arg_package = "";

	JSONArgsAssert_Get(args, retJson, "class"	, arg_class);
	JSONArgsAssert_Get(args, retJson, "package"	, arg_package);

	if ("" == arg_class || "" == arg_package || "" == arg_package) {
		JSONWriteERRString(retJson, "arg empty");
		return;
	}

	UE4$UClass * TMPUClass = NULL;
	if (NULL == (TMPUClass = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str()))) {
		JSONWriteERRString(retJson, "not find class");
		return;
	}


	JSONBuffer JSONUClass;

	JSONWriteValue(JSONUClass, "name"		, UE4::FName_ToString(&TMPUClass->NamePrivate).c_str());
	JSONWriteValue(JSONUClass, "package"	, UE4::UClass2UPackage(TMPUClass).c_str());
	JSONWriteValue(JSONUClass, "config"		, UE4::FName_ToString(&TMPUClass->ClassConfigName).c_str());
	JSONWriteValue(JSONUClass, "size"		, TMPUClass->PropertiesSize);

	JSONWriteValue_UInt64(JSONUClass, "pointer", TMPUClass);

	JSONWriteValue(retJson	, "info", JSONUClass);
}

static BOOL CCallBack_UStruct2PNString(UE4$UStruct * _kUStruct, std::string & rPString, std::string & rNString) {
	if (FALSE == _UE4ObjectISValid(_kUStruct))
		return FALSE;

	UE4$UObjectBase * TMPUPackage = (UE4$UObjectBase*)_kUStruct->OuterPrivate;
	if (NULL == TMPUPackage || FALSE == _UE4ObjectISValid(TMPUPackage))
		return false;

	rNString = UE4::FName_ToString(&_kUStruct->NamePrivate);
	rPString = UE4::FName_ToString(&TMPUPackage->NamePrivate);

	return "" != rPString && "" != rNString;
}

//命令行执行 : 获取所有的 结构 的 基础属性信息
static void CMD_ReadUStructLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_struct  = "";
	std::string arg_package = "";

	JSONArgsTry_Get(args, "struct"	, arg_struct, "");
	JSONArgsTry_Get(args, "package"	, arg_package, "");

	retJson.AddEmptySubArray("structs");

	UE4::enumUStruct([arg_struct, arg_package, &retJson](UE4$UStruct * TMPStructBuffer) {

		std::string _PString = "";
		std::string _NString = "";
		if (FALSE == CCallBack_UStruct2PNString(TMPStructBuffer, _PString, _NString))
			return false;

		//根据 key, 进行 匹配信息
		if ("" != arg_struct && NULL == findString_lower(_NString.c_str(), arg_struct.c_str())) {
			return false;
		}
		if ("" != arg_package && arg_package != _PString) {
			return false;
		}

		JSONBuffer _structJSON;

		JSONWriteValue(_structJSON, "package"	, _PString.c_str());
		JSONWriteValue(_structJSON, "name"		, _NString.c_str());
		JSONWriteValue(_structJSON, "size"		, TMPStructBuffer->PropertiesSize);

		uint32_t TMPCount = 0;
		UE4::enumUProperty(TMPStructBuffer->PropertyLink, [&TMPCount](UE4$UProperty * _kProperty) {
			TMPCount = TMPCount + 1;
			return FALSE;
		});

		JSONWriteValue(_structJSON, "propCount"	, TMPCount);
	
		retJson["structs"].Add(_structJSON);
		return false;
	});
}

//命令行执行 : 获取所有的 结构 的 详细信息
static void CMD_ReadUStructINFO(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_struct = "";
	std::string arg_package = "";

	JSONArgsAssert_Get(args, retJson, "struct"	, arg_struct);
	JSONArgsAssert_Get(args, retJson, "package"	, arg_package);

	if ("" == arg_struct) { JSONWriteERRString(retJson, "arg empty"); return; }

	UE4$UStruct * TMPFindUStruct = NULL;
	UE4::enumUStruct([arg_struct, arg_package, &TMPFindUStruct](UE4$UStruct * TMPStructBuffer) {

		std::string _PString = "";
		std::string _NString = "";
		if (FALSE == CCallBack_UStruct2PNString(TMPStructBuffer, _PString, _NString))
			return false;

		if ( ("" != arg_package && _PString != arg_package) || _NString != arg_struct)
			return false;

		return NULL != (TMPFindUStruct = TMPStructBuffer);
	});

	if (NULL == TMPFindUStruct || FALSE == _UE4ObjectISValid(TMPFindUStruct)) {
		JSONWriteERRString(retJson, "not find struct");
		return;
	}

	JSONBuffer _UPropertyJSON;

	CCallBack_EnumPropertyLIST(TMPFindUStruct->PropertyLink, _UPropertyJSON);

	JSONWriteValue(retJson, "PropertyLIST", _UPropertyJSON);

	JSONWriteValue(retJson, "structSize", TMPFindUStruct->PropertiesSize);

	JSONBuffer _SuperJSON;

	for (UE4$UStruct * i = TMPFindUStruct;  _UE4ObjectISValid(i); i = i->SuperStruct){
		std::string _PString = "";
		std::string _NString = "";
		if (FALSE == CCallBack_UStruct2PNString(i, _PString, _NString))
			break ;

		JSONBuffer TMPSuperJSON;

		JSONWriteValue(TMPSuperJSON, "package", _PString);
		JSONWriteValue(TMPSuperJSON, "struct", _NString);

		_SuperJSON.Add(TMPSuperJSON);
	}

	JSONWriteValue(retJson, "super", _SuperJSON);

	JSONWriteValue(retJson, "pointer", CString::format("0x%016I64X", TMPFindUStruct));
}

//命令行执行 : 获取所有的 类 的 基础属性信息
static void CMD_ReadUObjectLIST(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string arg_key = "";
	std::string arg_class = "";
	std::string arg_package = "";
	uint64_t    arg_address = NULL;


	JSONArgsTry_Get(args, "key"		, arg_key		, "");
	JSONArgsTry_Get(args, "class"	, arg_class     , "");
	JSONArgsTry_Get(args, "package"	, arg_package	, "");
	JSONArgsTry_Get(args, "address" , arg_address   , 0 );

	UE4$UClass * _kClass  = UE4::findUE4Class(arg_package.c_str(), arg_class.c_str());
	std::string  _nString = (NULL == _kClass ? "" : UE4::FName_ToString(&_kClass->NamePrivate));
	std::string  _pString = UE4::UClass2UPackage(_kClass).c_str();

	int32_t TMPObjectCount = 0;

	retJson.AddEmptySubArray("objects");
	UE4::enumUObject([_kClass, _pString, _nString, arg_address, arg_key, &retJson, &TMPObjectCount](const UE4$UObjectHEAD & _UObjectHead, const UObject * _UObject) {
		//包名 + 类名 匹配
		if (NULL != _kClass && _kClass != _UObjectHead.ClassPrivate)
			return false;

		// key 或 直接通过
		if (NULL == _kClass && "" != arg_key && false == findString_lower(_nString.c_str(), arg_key.c_str()))
			return false;

		//如果传入地址, 检测内存地址的范围
		if (0 != arg_address && (uint64_t)_UObject > arg_address)
			return false;
		if (0 != arg_address && (uint64_t)_UObject + _UObjectHead.ClassPrivate->PropertiesSize < arg_address)
			return false;

		JSONBuffer JSONObject;

		JSONWriteValue(JSONObject, "package"		, _pString.c_str());
		JSONWriteValue(JSONObject, "name"			, _nString.c_str());
		JSONWriteValue(JSONObject, "size"			, _UObjectHead.ClassPrivate->PropertiesSize);
		JSONWriteValue(JSONObject, "debug_value"	, UE4::DumpUObjectString(_UObject).c_str());

		JSONWriteValue_UInt64(JSONObject, "object"	, _UObject);

		retJson["objects"].Add(JSONObject);

		if ((TMPObjectCount = TMPObjectCount + 1) < 5000)
			return false;

		return true;
	});

	JSONWriteValue(retJson, "count", TMPObjectCount);
}

//命令行执行 : 获取 一个 对象的 调试报告
static void CMD_ReadUObjectDebugReport(const JSONBuffer & args, JSONBuffer & retJson) {
	uint64_t _UObject = NULL;
	JSONArgsAssert_Get(args, retJson, "object", _UObject);

	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid((const UObject *)_UObject, &TMPHeadBuffer)) {
		JSONWriteERRString(retJson, "object pointer invalid");
		return;
	}
	if (FALSE == _UE4ObjectISValid(TMPHeadBuffer.ClassPrivate)) {
		JSONWriteERRString(retJson, "object pointer invalid");
		return;
	}

	JSONWriteValue(retJson, "package"	, UE4::UClass2UPackage(TMPHeadBuffer.ClassPrivate));
	JSONWriteValue(retJson, "class"		, UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate));

	JSONBuffer JSONBufferLIST;

	UE4::DumpUObjectINFO((const UObject *)_UObject, [&JSONBufferLIST](_tagDBGPropertyINFO & kProperty) {
	
		JSONBuffer JSONProperty;

		JSONWriteValue(JSONProperty			, "package"			, kProperty.UClass._package.c_str());
		JSONWriteValue(JSONProperty			, "class"			, kProperty.UClass._class.c_str());
		JSONWriteValue(JSONProperty			, "property"		, kProperty.nProperty.c_str());
		JSONWriteValue(JSONProperty			, "type"			, (int)kProperty.Type);
		JSONWriteValue(JSONProperty			, "Offset"			, kProperty.Offset);
		JSONWriteValue(JSONProperty			, "Size"			, kProperty.Size);
		JSONWriteValue(JSONProperty			, "value"			, kProperty.value.c_str());
		JSONWriteValue_UInt64(JSONProperty	, "PropertyFlags"	, kProperty.PropertyFlags);
		JSONBufferLIST.Add(JSONProperty);
	});

	JSONWriteValue(retJson, "debug", JSONBufferLIST);
}

//命令行执行 : dump 所有的虚幻接口, 到 json 文件
static void CMD_DumpUE4MethonJSON(const JSONBuffer & args, JSONBuffer & retJson) {
	std::string pathString;
	JSONWriteValue(retJson, "count", UE4::DumpMethod2JSON(pathString));
	JSONWriteValue(retJson, "path" , pathString.c_str());
}

std::string CCallBack_ReadHexString(uint64_t _start, uint32_t _offset, size_t _size) {
	if (0 == _start) return "";
	if (0     >= _size) _size = 500;
	if (30000 <= _size) _size = 30000;

	std::auto_ptr< byte > byteBuffer(new byte[_size + 10]);
	if (NULL == byteBuffer.get()) { return std::string(""); }
	ZeroMemory(byteBuffer.get(), sizeof(byte)* (_size + 10));

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

#define _2HexString(a, l)   CCallBack_ReadHexString((uint64_t)a, 0, l)

//命令行执行 : 获取所有的 内存地址的 字节信息
static void CMD_ReadMemoryHEXString(const JSONBuffer & args, JSONBuffer & retJson) {
	uint64_t _MEMAddress = NULL;
	JSONArgsAssert_Get(args, retJson, "address", _MEMAddress);
	uint32_t _MEMSize = NULL;
	JSONArgsAssert_Get(args, retJson, "size", _MEMSize);

	JSONWriteValue(retJson, "hex", _2HexString(_MEMAddress, _MEMSize));
}

//命令行执行 : 获取所有的 主模块 基础信息
static void CMD_ReadMemoryINFO(const JSONBuffer & args, JSONBuffer & retJson) {
	uint8_t * text_startBuffer = NULL;
	uint8_t * text_endBuffer = NULL;

	UE4::read_text_range(&text_startBuffer, &text_endBuffer);

	JSONWriteValue_UInt64(retJson, "base", GetModuleHandle(NULL));

	JSONWriteValue_UInt64(retJson, "text_start", text_startBuffer);
	JSONWriteValue_UInt64(retJson, "text_end"  , text_endBuffer);
}

//命令行执行 : 获取 FName 的字符串信息
static void CMD_ReadFNameString(const JSONBuffer & args, JSONBuffer & retJson) {
	uint64_t _FName_A = NULL;
	JSONArgsAssert_Get(args, retJson, "FA", _FName_A);
	uint64_t _FName_V = NULL;
	JSONArgsAssert_Get(args, retJson, "FV", _FName_V);

	CString aString = "*INVALID*";
	CString vString = "*INVALID*";

	uint64_t _FName_Value = 0;
	if (TRUE == UE4::readMemory((const void *)_FName_A, &_FName_Value, sizeof(uint64_t))) {
		aString = UE4::FName_ToString(&_FName_Value);
	}
		
	vString = UE4::FName_ToString(&_FName_V);

	JSONWriteValue(retJson, "aString", aString.getBuffer());
	JSONWriteValue(retJson, "vString", vString.getBuffer());
}


bool CMDSwitch_DistributionCenter_UnrealEngine4(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //得到字符串 长度,

	if (strlen("UE4$ReadPackageLIST") == lenth_method && 0 == strcmp("UE4$ReadPackageLIST", method)) {
		CMD_ReadPackageLIST(args, retJson);
		return TRUE;
	}

	if (strlen("UE4$ReadClassLIST") == lenth_method && 0 == strcmp("UE4$ReadClassLIST", method)) {
		CMD_ReadClassLIST(args, retJson);
		return TRUE;
	}

	if (strlen("UE4$ReadClassLISTBySuper") == lenth_method && 0 == strcmp("UE4$ReadClassLISTBySuper", method)) {
		CMD_ReadClassLISTBySuper(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadFunctionLIST") == lenth_method && 0 == strcmp("UE4$ReadFunctionLIST", method)) {
		CMD_ReadFunctionLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadSuperClassLIST") == lenth_method && 0 == strcmp("UE4$ReadSuperClassLIST", method)) {
		CMD_ReadSuperClassLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadPropertyLIST") == lenth_method && 0 == strcmp("UE4$ReadPropertyLIST", method)) {
		CMD_ReadPropertyLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadUClassINFO") == lenth_method && 0 == strcmp("UE4$ReadUClassINFO", method)) {
		CMD_ReadUClassINFO(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadEnumLIST") == lenth_method && 0 == strcmp("UE4$ReadEnumLIST", method)) {
		CMD_ReadUEnumLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadStructLIST") == lenth_method && 0 == strcmp("UE4$ReadStructLIST", method)) {
		CMD_ReadUStructLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadStructINFO") == lenth_method && 0 == strcmp("UE4$ReadStructINFO", method)) {
		CMD_ReadUStructINFO(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$DumpMethonJSON") == lenth_method && 0 == strcmp("UE4$DumpMethonJSON", method)) {
		CMD_DumpUE4MethonJSON(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadUObjectLIST") == lenth_method && 0 == strcmp("UE4$ReadUObjectLIST", method)) {
		CMD_ReadUObjectLIST(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadUObjectDebugReport") == lenth_method && 0 == strcmp("UE4$ReadUObjectDebugReport", method)) {
		CMD_ReadUObjectDebugReport(args, retJson);
		return TRUE;
	}

	if (strlen("UE4$ReadMemoryHEXString") == lenth_method  && 0 == strcmp("UE4$ReadMemoryHEXString", method)) {
		CMD_ReadMemoryHEXString(args, retJson);
		return TRUE;
	}
	if (strlen("UE4$ReadMModuleINFO") == lenth_method && 0 == strcmp("UE4$ReadMModuleINFO", method)) {
		CMD_ReadMemoryINFO(args, retJson);
		return TRUE;
	}
	//if (strlen("ue4_getBEventBuffer") == lenth_method && 0 == strcmp("ue4_getBEventBuffer", method)) {
	//	ue4_getBEventBuffer(args, retJson);
	//	return TRUE;
	//}

	//if (strlen("ue4_getUFunction") == lenth_method && 0 == strcmp("ue4_getUFunction", method)) {
	//	ue4_getUFunction(args, retJson);
	//	return TRUE;
	//}

	if (strlen("UE4$ReadFNameString") == lenth_method && 0 == strcmp("UE4$ReadFNameString", method)) {
		CMD_ReadFNameString(args, retJson);
		return TRUE;
	}

	return FALSE;
}




