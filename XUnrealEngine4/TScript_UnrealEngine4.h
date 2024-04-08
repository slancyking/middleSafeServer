#pragma once
//
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
//
#include <windows.h>					// Windows ͷ�ļ�
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

	// ��ȡ ȫ��UObject ��Ŀ
	const uint32_t getUE4UObjectCount();
	// ��ȡ �� n ��ȫ�ֶ���
	const UObject * getUE4UObject(int32_t kIndex);
	// ��ȡ �� n ��ȫ�ֶ���
	BOOL getUE4UObjectINFO(int32_t kIndex, UE4$GUObjectINFO & RBuffer);

	//Ѱ��һ�������
	UE4$UClass * findUE4Class(const char * _package, const char * _class);

	//��һ���������, Ѱ�Ҹ��������
	UE4$UClass * findUE4SuperClass(UE4$UClass * _StartUClass, const char * superClass);

	//��ȡһ����� ָ����Աƫ����
	long long	findPropertyOffset(UE4$UClass * _kUClass, const char * _symbol);
	//��ȡһ����� ָ����Աƫ����
	long long	findPropertyOffset(const char * _package, const char * _class, const char * _symbol);
	//��ȡһ����� ָ�������ṹ
	UE4$UFunction * findUFunction(const char * _package, const char * _class, const char * _symbol);


	//��ȡ��� ����
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

	//��ȡ UE4$UProperty �� ����
	EPropertyGenFlags _2PropertyTYPE(UE4$UProperty * _kProperty);


	//����һ�������� ԭ���ַ���
	std::string _2MethodOString(std::string _CString, UE4$UFunction * TMPFunction);
	//dump ���нӿ�, �� json �ļ�
	int DumpMethod2JSON(std::string & rPathString);
	//dump UObject �Ļ�����������Ϣ
	std::string DumpUObjectString(const UObject * TMPUObjcetBuffer);
	//dump UObject �ڴ���Ϣ
	void DumpUObjectINFO(const UObject * TMPUObjcetBuffer, std::function<void(_tagDBGPropertyINFO &)> enumCallback);

	// ��ȡ �������
	const UObject * getUE4World();
	// ��ȡ ʵ������
	const UObject * getUE4GameInstance();
	// ��ȡ ��Ҷ���
	const UObject * getUE4LocalPlayers(int lIndex = 0);
	// ��ȡ �����������
	const UObject * getUE4PlayerController();
	// ��ȡ ���APawn ����
	const UObject * getUE4AcknowledgedPawn();
	// ��ȡ ��������������� 
	const UObject * getUE4APlayerCameraManager();
	// ��ȡ FSlateApplication ����
	const FSlateApplication * getUE4FSlateApplication();
}

//��ȡ UE4$UProperty �� ����
#define EPropertyTYPE_GetTYPE( pProperty)     UE4::_2PropertyTYPE( pProperty )

//��ȡһ����� ָ����Աƫ����
#define _2UE4IvarOffset           UE4::findPropertyOffset



// ��ȡ ȫ������� ����
#define _2UE4UObjectCount			UE4::getUE4UObjectCount
// ��ȡ ��n�������µ� UE4����ָ��
#define _2UE4UObjectPtr  			UE4::getUE4UObject
//
#define _2UE4UObjectINFO  			UE4::getUE4UObjectINFO

// ��ȡ �������
#define _2UE4GWorld					UE4::getUE4World
// ��ȡ ʵ������
#define _2UE4GameInstance			UE4::getUE4GameInstance
// ��ȡ ��Ҷ���
#define _2UE4LocalPlayer			UE4::getUE4LocalPlayers
// ��ȡ �����������
#define _2UE4MainController			UE4::getUE4PlayerController
// ��ȡ ���APawn ����
#define _2UE4MainAPawn				UE4::getUE4AcknowledgedPawn
// ��ȡ ��������������� 
#define _2UE4MainCamera				UE4::getUE4APlayerCameraManager
// ��ȡ FSlateApplication ���� 
#define _2UE4FSlateApplication		UE4::getUE4FSlateApplication



namespace UE4 {
	//��ȡ ��ģ��� ����η�Χ
	BOOL read_text_range(uint8_t ** start, uint8_t ** end);

	//��ȡ ��ģ��� ƫ�Ƶ�ַ
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
	
	//��ȡһ�� ������ ����
	UE4$UClass * UClass2SuperClass(UE4$UClass *_UClass);
	//ȷ��һ�������ĸ�����ϵ
	BOOL UClassEnterSuperClass(UE4$UClass *_UClass, UE4$UClass  * _SuperClass);
	//��ȡָ���Ƿ�Ϊһ��UE4����
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

//��ȡ�ؼ���Ϣ : �������ؼ�, ��ǰ�ٷֱ�
float UProgressBar_getPercent(const UObject * _UProgressBar);
//��ȡ�ؼ���Ϣ : �ı��� �󶨵��ַ�������
std::string UTextBlock_getTEXT(const UObject * _UBLRichTextBlock);
//��ȡ�ؼ���Ϣ : ͼ��ؼ�����Դ����
std::string UImage_getResourceName(const UObject * _UImageCtrl);
//��ȡ�ؼ���Ϣ : ��ť�ؼ�����Դ����
std::string UButton_getResourceName(const UObject * _UButtonCtrl);
//��ȡ�ؼ���Ϣ : ���ı���
std::string URichTextBlock_getTEXT(const UObject * _UTextBlock);

//  ---------------------------------------------------------------------------------------------------------------------------------------����, �����Ϸ�Ĵ������




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









//m == ģ������, ����� .exe .dll .*
#define _2SYMPointer(s)					 UE4::_2MethodPointer(NULL, s)

#define _2SYMPointerByModule(m, s)       UE4::_2MethodPointer(m, s)


#define _2UObjectPointer(b, o)             (const UObject *)((NULL == b || 0 == o ) ? NULL : ((ULONG64)b + o))

#define UE4_logFormat(f, ...)				   UE4::logFormat(f, __VA_ARGS__); 

#define UE4_logEString(s)					  { UE4_logFormat("#ERROR#, %s", s);				UE4::TerminateExitCallback(); }
#define UE4_logEFormat(f, ...)				  { UE4_logFormat("#ERROR#, " f, __VA_ARGS__);		UE4::TerminateExitCallback(); }

//�Ա� �ַ��� �Ƿ�Ϊ��ͬ��
#define UE4_stricmpex(str,strex)       (BOOL)(NULL != str && NULL != strex && strlen(str) == strlen(strex) && 0 == _stricmp(str,strex))   

#define __CallUObject$ProcessEvent(_this, uf, args)  (NULL == _this? NULL : UE4::ProcessEventCallback(_this, uf, args))
