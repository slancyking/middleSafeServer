#pragma once
//
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
//
#include <windows.h>					// Windows 头文件
//
#include <functional>
//
#include <future>
//
#include "TSConfig_UE4Offset.h"
//
#include "TSConfig_UE4OffsetByUI.h"
//
#include "TScript_UnrealEngine4ByTYPE.h"
//
#include "TScript_UnrealEngine4ByTYPE.h"
//
#include "..\\CString\\CString.h"
//
#include "..\\CRejection\\CRejection.h"
//
#include "..\\CJsonObject-master\\CJsonObject.hpp"

typedef  neb::CJsonObject  JSONBuffer;

#define UE4JSONWriteValue(b, n, v)            { b.Add(n, v); }


struct _tagDBGUClassINFO {
	UE4$UClass   * _UClass;
	std::string    _package;
	std::string    _class;

	uint32_t       _start;
	uint32_t       _end;
};

struct _tagDBGPropertyINFO {

	_tagDBGUClassINFO   UClass;

	UE4$UProperty   *   kProperty;

	std::string		    nProperty;

	EPropertyTYPE       Type;

	uint32_t            Offset;

	uint32_t            Size;

	EPropertyFlags		PropertyFlags;

	uint32_t            mask;

	std::string         value;  
};

namespace UE4 {

	// 获取 全局UObject 数目
	const uint32_t getUE4UObjectCount();
	// 获取 第 n 个全局对象
	const UObject * getUE4UObject(int32_t kIndex);
	// 获取 第 n 个全局对象
	BOOL getUE4UObjectINFO(int32_t kIndex, UE4$GUObjectINFO & RBuffer);

	//寻找一个类对象
	UE4$UClass * findUE4Class(const char * _package, const char * _class);

	//从一个类对象中, 寻找父级类对象
	UE4$UClass * findUE4SuperClass(UE4$UClass * _StartUClass, const char * superClass);

	//获取一个类的 指定成员偏移量
	long long	findPropertyOffset(UE4$UClass * _kUClass, const char * _symbol);
	//获取一个类的 指定成员偏移量
	long long	findPropertyOffset(const char * _package, const char * _class, const char * _symbol);
	//获取一个类的 指定函数结构
	UE4$UFunction * findUFunction(const char * _package, const char * _class, const char * _symbol);


	//获取类的 包名
	std::string UClass2UPackage(UE4$UClass * kClass);


	const UObject * ProcessEventCallback(const UObject * _pthis, const UE4$UFunction * uFunction, void * params);


	void enumUObject(std::function<bool(const UE4$UObjectHEAD &, const UObject *)> enumCallback);
	void enumUObject(const void * kObject, std::function<bool(const UE4$UObjectHEAD &, const UObject *)> enumCallback);

	void enumUPackage(std::function<bool(std::string UPackageString)> enumCallback);
	void enumUClass(std::function<bool(UE4$UClass *, std::string CString, std::string PString, std::string NString)> enumCallback);
	void enumUFunction(UE4$UClass * _kClass, std::function<bool(UE4$UFunction *)> enumCallback);
	void enumUProperty(UE4$UClass * _kClass, std::function<bool(UE4$UProperty *)> enumCallback);
	void enumUProperty(UE4$UProperty * _kProperty, std::function<bool(UE4$UProperty *)> enumCallback);
	void enumUEnum(std::function<bool(UE4$UEnum *)> enumCallback);
	void enumUStruct(std::function<bool(UE4$UStruct *)> enumCallback);

	//获取 UE4$UProperty 的 类型
	EPropertyGenFlags _2PropertyTYPE(UE4$UProperty * _kProperty);


	//解析一个函数的 原型字符串
	std::string _2MethodOString(std::string _CString, UE4$UFunction * TMPFunction);
	//dump 所有接口, 到 json 文件
	int DumpMethod2JSON(std::string & rPathString);
	//dump UObject 的基础调试想信息
	std::string DumpUObjectString(const UObject * TMPUObjcetBuffer);
	//dump UObject 内存信息
	void DumpUObjectINFO(const UObject * TMPUObjcetBuffer, std::function<void(_tagDBGPropertyINFO &)> enumCallback);

	// 获取 世界对象
	const UObject * getUE4World();
	// 获取 实例对象
	const UObject * getUE4GameInstance();
	// 获取 玩家对象
	const UObject * getUE4LocalPlayers(int lIndex = 0);
	// 获取 玩家主控制器
	const UObject * getUE4PlayerController();
	// 获取 玩家APawn 对象
	const UObject * getUE4AcknowledgedPawn();
	// 获取 玩家摄像机管理对象 
	const UObject * getUE4APlayerCameraManager();
	// 获取 FSlateApplication 对象
	const FSlateApplication * getUE4FSlateApplication();
}

//获取 UE4$UProperty 的 类型
#define EPropertyTYPE_GetTYPE( pProperty)     UE4::_2PropertyTYPE( pProperty )

//获取一个类的 指定成员偏移量
#define _2UE4IvarOffset           UE4::findPropertyOffset



// 获取 全局类对象 总数
#define _2UE4UObjectCount			UE4::getUE4UObjectCount
// 获取 第n个索引下的 UE4对象指针
#define _2UE4UObjectPtr  			UE4::getUE4UObject
//
#define _2UE4UObjectINFO  			UE4::getUE4UObjectINFO

// 获取 世界对象
#define _2UE4GWorld					UE4::getUE4World
// 获取 实例对象
#define _2UE4GameInstance			UE4::getUE4GameInstance
// 获取 玩家对象
#define _2UE4LocalPlayer			UE4::getUE4LocalPlayers
// 获取 玩家主控制器
#define _2UE4MainController			UE4::getUE4PlayerController
// 获取 玩家APawn 对象
#define _2UE4MainAPawn				UE4::getUE4AcknowledgedPawn
// 获取 玩家摄像机管理对象 
#define _2UE4MainCamera				UE4::getUE4APlayerCameraManager
// 获取 FSlateApplication 对象 
#define _2UE4FSlateApplication		UE4::getUE4FSlateApplication



namespace UE4 {
	//获取 主模块的 代码段范围
	BOOL read_text_range(uint8_t ** start, uint8_t ** end);

	//获取 主模块的 偏移地址
	uint64 _2MModuleOffset(void * address);

	void * _2MethodPointer(const char * kString, int64_t offset);

	BOOL readMemory(const void * pAddress, void *buffer, size_t _size);
	BOOL readMemory(const void * pAddress, uint64_t offset, void *buffer, size_t _size);

}

namespace UE4 {

	void TerminateExitCallback();
	void logFormat(const char * fString, ...);
}

namespace UE4 {
	
	//获取一个 类对象的 父级
	UE4$UClass * UClass2SuperClass(UE4$UClass *_UClass);
	//确认一个类对象的父级关系
	BOOL UClassEnterSuperClass(UE4$UClass *_UClass, UE4$UClass  * _SuperClass);
	//获取指针是否为一个UE4对象
	BOOL enterUObjectHEAD(const UObject * _pthis, UE4$UObjectHEAD * headBuffer);
	BOOL enterUObjectHEAD(const UObject * _pthis);

	BOOL enterVFTable(const void * _pthis);


	void	FMemory_Free(const void * _FMemory);

	BOOL	FString_ToBuffer(const FString * _FString, UE4$FString & retBuffer);

	std::string FString_ToString(const FString * _FString);

	const FString * FText_ToFString(const FText * fTextString);

	std::string FText_ToString(const FText * fTextString);

	std::string	FName_ToString(const FName * _FName);
}


#define _UE4ObjectISValid           UE4::enterUObjectHEAD








//---------------------------------------------------------------------------------------------------------------------------------------------------


//
//const UFunction * findUFunction(const UObject * _UObject, const char * _funString);
//const UFunction * findUFunction(const char * _package, const char * _class, const char * _funString);
//




//---------------------------------------------------------------------------------------------------------------------------------------------------

//获取控件信息 : 进度条控件, 当前百分比
float UProgressBar_getPercent(const UObject * _UProgressBar);
//获取控件信息 : 文本块 绑定的字符串内容
std::string UTextBlock_getTEXT(const UObject * _UBLRichTextBlock);
//获取控件信息 : 图像控件的资源名称
std::string UImage_getResourceName(const UObject * _UImageCtrl);
//获取控件信息 : 按钮控件的资源名称
std::string UButton_getResourceName(const UObject * _UButtonCtrl);
//获取控件信息 : 富文本块
std::string URichTextBlock_getTEXT(const UObject * _UTextBlock);

//  ---------------------------------------------------------------------------------------------------------------------------------------以下, 针对游戏的处理过程




//---------------------------------------------------------------------------------------------------------------------------------------------------

//
//void USceneComponent_SetupAttachment(const UObject * _USceneComponent, const UObject * InParent);

//void UTextRenderComponent::SetText(FString  Value)
void UTextRenderComponent_SetText(const UObject * _UTextRenderComponent, const char * textBuffer);

//void USceneComponent::K2_SetRelativeLocation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  NewLocation)
void USceneComponent_SetRelativeLocation(const UObject * _USceneComponent, FVector NewLocation);





//---------------------------------------------------------------------------------------------------------------------------------------------------


//UObject  APawn::GetController()
const UObject * APawn_GetController(const UObject * _APawn);

//bool  APlayerController::ProjectWorldLocationToScreen(bool  bPlayerViewportRelative, __out Struct  ScreenLocation, Struct  WorldLocation) // \\ /
FVector2D APlayerController_ProjectWorldLocationToScreen(const UObject * _APlayerController, FVector WorldLocation);


//---------------------------------------------------------------------------------------------------------------------------------------------------   AHUD


//void AHUD::DrawRect(float  ScreenH, float  ScreenW, float  ScreenY, float  ScreenX, Struct  RectColor)  // \ 
void AHUD_DrawRect(const UObject * _AHUD, float  ScreenX, float  ScreenY, float  ScreenW, float  ScreenH, FLinearColor  RectColor);





//---------------------------------------------------------------------------------------------------------------------------------------------------

//Struct  AActor::K2_GetActorRotation()
FRotator AActor_GetActorRotation(const UObject * _AActor);
//Struct  AActor::K2_GetActorLocation()
FVector  AActor_GetActorLocation(const UObject * _AActor);
//Struct  AActor::GetActorForwardVector()
FVector  AActor_GetActorForwardVector(const UObject * _AActor);
//Struct  AActor::GetActorRightVector()
FVector  AActor_GetActorRightVector(const UObject * _AActor);

//Struct  APlayerCameraManager::GetCameraRotation()
FRotator APlayerCameraManager_GetCameraRotation(const UObject * _APlayerCamera);
//Struct  APlayerCameraManager::GetCameraLocation()
FVector  APlayerCameraManager_GetCameraLocation(const UObject * _APlayerCamera);

//void AController::SetControlRotation(__out const Struct &  NewRotation)
void AController_SetControlRotation(const UObject * _AController, FRotator NewRotation);


//---------------------------------------------------------------------------------------------------------------------------------------------------


//void APawn::AddMovementInput(bool  bForce, float  ScaleValue, Struct  WorldDirection)
void APawn_AddMovementInput(const UObject * _APawn, bool  bForce, float  ScaleValue, FVector WorldDirection);
//bool  AActor::K2_SetActorLocation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  NewLocation)
void AActor_SetActorLocation(const UObject * _AActor, bool  bSweep, FVector NewLocation);
//bool  AActor::K2_SetActorRotation(bool  bTeleportPhysics, Struct  NewRotation)
void AActor_SetActorRotation(const UObject * _AActor, FRotator NewRotation);
//bool  AActor::K2_TeleportTo(Struct  DestRotation, Struct  DestLocation)
void AActor_TeleportTo(const UObject * _AActor, FRotator DestRotation, FVector DestLocation);
//void AActor::K2_AddActorWorldOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void AActor_AddActorWorldOffset(const UObject * _AActor, bool  bSweep, FVector DeltaLocation);
//void AActor::K2_AddActorWorldRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void AActor_AddActorWorldRotation(const UObject * _AActor, bool  bSweep, FRotator DeltaRotation);
//void AActor::K2_AddActorLocalOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void AActor_AddActorLocalOffset(const UObject * _AActor, bool  bSweep, FVector DeltaLocation);
//void AActor::K2_AddActorLocalRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void AActor_AddActorLocalRotation(const UObject * _AActor, bool  bSweep, FRotator DeltaRotation);









//m == 模块名称, 必须带 .exe .dll .*
#define _2SYMPointer(s)					 UE4::_2MethodPointer(NULL, s)

#define _2SYMPointerByModule(m, s)       UE4::_2MethodPointer(m, s)


#define _2UObjectPointer(b, o)             (const UObject *)((NULL == b || 0 == o ) ? NULL : ((ULONG64)b + o))

#define UE4_logFormat(f, ...)				   UE4::logFormat(f, __VA_ARGS__); 

#define UE4_logEString(s)					  { UE4_logFormat("#ERROR#, %s", s);				UE4::TerminateExitCallback(); }
#define UE4_logEFormat(f, ...)				  { UE4_logFormat("#ERROR#, " f, __VA_ARGS__);		UE4::TerminateExitCallback(); }

//对比 字符串 是否为相同的
#define UE4_stricmpex(str,strex)       (BOOL)(NULL != str && NULL != strex && strlen(str) == strlen(strex) && 0 == _stricmp(str,strex))   

#define __CallUObject$ProcessEvent(_this, uf, args)  (NULL == _this? NULL : UE4::ProcessEventCallback(_this, uf, args))
