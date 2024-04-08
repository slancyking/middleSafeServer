#pragma once
//
#include "TScript_UnrealEngine4.h"






//-------------------------------------------------------------------------------------------------------------------------------杂项接口

//UObject  APawn::GetController()
const UObject * APawn_GetController(const UObject * _APawn) {
	struct _tag$GetController{
		UObject *  	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, UObject_AController
	          							;//      Size = 0x00000008
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Pawn"
#define _CALL_UFUNCTION    "GetController"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return NULL;
	}

	__CallUObject$ProcessEvent(_APawn, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//bool  APlayerController::ProjectWorldLocationToScreen(bool  bPlayerViewportRelative, __out Struct  ScreenLocation, Struct  WorldLocation) // \\ /
FVector2D APlayerController_ProjectWorldLocationToScreen(const UObject * _APlayerController, FVector WorldLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "PlayerController"
#define _CALL_UFUNCTION    "ProjectWorldLocationToScreen"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return { 0.0f, 0.0f };
	}

	struct _tag$ProjectWorldLocationToScreen{
		FVector   	WorldLocation			;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		FVector2D   ScreenLocation			;//    offset = 0x0000000C, flags = 0x0010000000000180, _tagVector2D
		bool      	bPlayerViewportRelative	;//    offset = 0x00000001, flags = 0x0010000000000080, 
		bool      	ReturnValue				;//    offset = 0x00000001, flags = 0x0010000000000580, 
	          								;//      Size = 0x00000018
	}_args = { NULL };

	_args.ScreenLocation			= { NULL };
	_args.WorldLocation				= WorldLocation;
	_args.bPlayerViewportRelative	= false;

	__CallUObject$ProcessEvent(_APlayerController, _CALLUFunction, &_args);

	return _args.ScreenLocation;
}


//-------------------------------------------------------------------------------------------------------------------------------定位相关

//Struct  AActor::K2_GetActorRotation()
FRotator AActor_GetActorRotation(const UObject * _AActor) {
	struct _tag$K2_GetActorRotation{
		FRotator   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagRotator
	          							;//    offset = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_GetActorRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
																_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//Struct  AActor::K2_GetActorLocation()
FVector AActor_GetActorLocation(const UObject * _AActor) {
	struct _tag$K2_GetActorLocation{
		FVector   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagVector
	          							;//      Size = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_GetActorLocation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
																_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//Struct  AActor::GetActorForwardVector()
FVector AActor_GetActorForwardVector(const UObject * _AActor) {
	struct _tag$K2_GetActorLocation{
		FVector   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagVector
	          							;//      Size = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "GetActorForwardVector"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
																_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//Struct  AActor::GetActorRightVector()
FVector AActor_GetActorRightVector(const UObject * _AActor) {
	struct _tag$K2_GetActorLocation{
		FVector   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagVector
	          							;//      Size = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "GetActorRightVector"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
																_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);

	return _args.ReturnValue;
}


//Struct  APlayerCameraManager::GetCameraRotation()
FRotator APlayerCameraManager_GetCameraRotation(const UObject * _APlayerCamera) {
	struct _tag$GetCameraRotation{
		FRotator   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagRotator
	          							;//      Size = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "PlayerCameraManager"
#define _CALL_UFUNCTION    "GetCameraRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_APlayerCamera, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//Struct  APlayerCameraManager::GetCameraLocation()
FVector APlayerCameraManager_GetCameraLocation(const UObject * _APlayerCamera) {
	struct _tag$GetCameraLocation{
		FVector   	ReturnValue         ;//    offset = 0x00000000, flags = 0x0010000000000580, _tagVector
	          							;//      Size = 0x0000000C
	}_args = { NULL };

#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "PlayerCameraManager"
#define _CALL_UFUNCTION    "GetCameraLocation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return _args.ReturnValue;
	}

	__CallUObject$ProcessEvent(_APlayerCamera, _CALLUFunction, &_args);

	return _args.ReturnValue;
}

//void AController::SetControlRotation(__out const Struct &  NewRotation)
void AController_SetControlRotation(const UObject * _AController, FRotator NewRotation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Controller"
#define _CALL_UFUNCTION    "SetControlRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$SetControlRotation {
		FRotator   	NewRotation		;	//    offset = 0x00000000, flags = 0x0010000008000182, _tagRotator
									;	//      Size = 0x0000000C
	}_args = { NULL };

	_args.NewRotation = NewRotation;

	__CallUObject$ProcessEvent(_AController, _CALLUFunction, &_args);
}

//bool  AActor::K2_SetActorRotation(bool  bTeleportPhysics, Struct  NewRotation)
void AActor_SetActorRotation(const UObject * _AActor, FRotator NewRotation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_SetActorRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_SetActorRotation{
		FRotator   	NewRotation         ;//    offset = 0x00000000, flags = 0x0010000000000080, Rotator
		bool      	bTeleportPhysics    ;//    offset = 0x0000000C, flags = 0x0010000000000080, 
		bool      	ReturnValue         ;//    offset = 0x0000000D, flags = 0x0010000000000580, 
	          							;//      Size = 0x00000010
	}_args = { NULL };


	_args.bTeleportPhysics = TRUE;
	_args.NewRotation = NewRotation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}




//-------------------------------------------------------------------------------------------------------------------------------移动相关

//void APawn::AddMovementInput(bool  bForce, float  ScaleValue, Struct  WorldDirection)
void APawn_AddMovementInput(const UObject * _APawn, bool  bForce, float  ScaleValue, FVector WorldDirection) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Pawn"
#define _CALL_UFUNCTION    "AddMovementInput"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$AddMovementInput{
		FVector   	WorldDirection      ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		float     	ScaleValue          ;//    offset = 0x0000000C, flags = 0x0010000000000080, 
		BOOL      	bForce              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x00000014
	}_args = { NULL };

	_args.bForce		 = bForce;
	_args.ScaleValue	 = ScaleValue;
	_args.WorldDirection = WorldDirection;

	__CallUObject$ProcessEvent(_APawn, _CALLUFunction, &_args);
}

//void AActor::K2_AddActorWorldOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void AActor_AddActorWorldOffset(const UObject * _AActor, bool  bSweep, FVector DeltaLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_AddActorWorldOffset"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_AddActorWorldOffset{
		FVector   	DeltaLocation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		FHitResult  SweepHitResult      ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep        = bSweep;
	_args.DeltaLocation = DeltaLocation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

//void AActor::K2_AddActorWorldRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void AActor_AddActorWorldRotation(const UObject * _AActor, bool  bSweep, FRotator DeltaRotation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_AddActorWorldRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}
	struct _tag$K2_AddActorWorldRotation{
		FRotator   	DeltaRotation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagRotator
		bool      	bSweep              ;//    offset = 0x00000001, flags = 0x0010040000000080, 
		FHitResult  SweepHitResult      ;//    offset = 0x00000010, flags = 0x0010048000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010040000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep = bSweep;
	_args.DeltaRotation = DeltaRotation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

//void AActor::K2_AddActorLocalOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void AActor_AddActorLocalOffset(const UObject * _AActor, bool  bSweep, FVector DeltaLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_AddActorLocalOffset"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_AddActorLocalOffset{
		FVector   	DeltaLocation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		FHitResult  SweepHitResult      ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep        = bSweep;
	_args.DeltaLocation = DeltaLocation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

//void AActor::K2_AddActorLocalRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void AActor_AddActorLocalRotation(const UObject * _AActor, bool  bSweep, FRotator DeltaRotation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_AddActorLocalRotation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}
	struct _tag$K2_AddActorLocalRotation{
		FRotator   	DeltaRotation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagRotator
		bool      	bSweep              ;//    offset = 0x00000001, flags = 0x0010040000000080, 
		FHitResult  SweepHitResult      ;//    offset = 0x00000010, flags = 0x0010048000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010040000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep = bSweep;
	_args.DeltaRotation = DeltaRotation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

//bool  AActor::K2_SetActorLocation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  NewLocation)
void AActor_SetActorLocation(const UObject * _AActor, bool  bSweep, FVector NewLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_SetActorLocation"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE, 
																_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_SetActorLocation{
		FVector   	NewLocation         ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		FHitResult  SweepHitResult      ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		BOOL      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		BOOL      	ReturnValue         ;//    offset = 0x00000001, flags = 0x0010000000000580, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	_args.bSweep		= bSweep;
	_args.NewLocation	= NewLocation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

//bool  AActor::K2_TeleportTo(Struct  DestRotation, Struct  DestLocation)
void AActor_TeleportTo(const UObject * _AActor, FRotator DestRotation, FVector DestLocation) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "Actor"
#define _CALL_UFUNCTION    "K2_TeleportTo"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return;
	}

	struct _tag$K2_TeleportTo{
		FVector   	DestLocation        ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		FRotator   	DestRotation        ;//    offset = 0x0000000C, flags = 0x0010000000000080, _tagRotator
		bool      	ReturnValue         ;//    offset = 0x00000001, flags = 0x0010000000000580, 
	          							;//      Size = 0x0000001C
	}_args = { NULL };

	_args.DestLocation = DestLocation;
	_args.DestRotation = DestRotation;

	__CallUObject$ProcessEvent(_AActor, _CALLUFunction, &_args);
}

























