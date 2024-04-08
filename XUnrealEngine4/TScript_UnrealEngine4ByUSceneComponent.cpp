#pragma once
//
#include "TScript_UnrealEngine4.h"


////
//void USceneComponent_SetupAttachment(const UObject * _USceneComponent, const UObject * InParent) {
//	static void * _call = 0;
//	//if (NULL == _call) _call = toMethodPointer(defModuleNAME, "?SetupAttachment@USceneComponent@@QEAAXPEAV1@VFName@@@Z");
//	if (NULL == _call) _logEString("定位方法: public: void USceneComponent::SetupAttachment(class USceneComponent *, class FName) , 异常!!");
//
//	void(*debug_call)(const UObject *, const UObject *, uint64_t) = (void(*)(const UObject *, const UObject *, uint64_t))_call;
//
//	return debug_call(_USceneComponent, InParent, 0/* FName InSocketName = NAME_None*/);
//}

//void UTextRenderComponent::SetText(FString  Value)
void UTextRenderComponent_SetText(const UObject * _UTextRenderComponent, const char * textBuffer) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "TextRenderComponent"
#define _CALL_UFUNCTION    "SetText"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$SetText {
		UE4$FString Value	;//    offset = 0x00000000, flags = 0x0010000000000080, 
							;//      Size = 0x00000010
	}_args = { NULL };

	if (NULL != (_args.Value._string = CString::gb2312_unicode(textBuffer))) {
		_args.Value._count = wcslen(_args.Value._string);
		_args.Value._max = _args.Value._count + 1;

		__CallUObject$ProcessEvent(_UTextRenderComponent, _CALLUFunction, &_args);

		CString::free(_args.Value._string);
	};
}

//void USceneComponent::K2_SetRelativeLocation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  NewLocation)
void USceneComponent_SetRelativeLocation(const UObject * _USceneComponent, FVector NewLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "SceneComponent"
#define _CALL_UFUNCTION    "K2_SetRelativeLocation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_SetRelativeLocation{
		FVector   	NewLocation         ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x0000000C, flags = 0x0010000000000080, 
		BYTE     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		BOOL      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep = TRUE;
	_args.NewLocation = NewLocation;

	__CallUObject$ProcessEvent(_USceneComponent, _CALLUFunction, &_args);
}