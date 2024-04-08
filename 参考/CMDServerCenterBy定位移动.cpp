#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"
//
#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"

#define PI 3.1415926

float angle(FVector p1, FVector p2) {
	FVector tmp = { NULL };
	tmp.x = p2.x - p1.x;
	tmp.y = p2.y - p1.y;
	return atan2(tmp.y, tmp.x) * 180 / PI;
}


//APlayerController->AcknowledgedPawn->CharacterMovement->Velocity
void CMD_UE4Game$CharacterMovementByVelocity(const JSONBuffer & args, JSONBuffer & retJson) {
	
	static long long	 _CharacterMovement_offset = -1;
	CMD_AssertClassSymbol(_CharacterMovement_offset, "/Script/Engine", "Character", "CharacterMovement");

	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	const UObject * _UBLCharacterMovementComponent = NULL;
	if (NULL == (_UBLCharacterMovementComponent = *(UObject**)((uint64_t)_PlayerAPawn + _CharacterMovement_offset))) {
		JSONWriteERRString(retJson, "CharacterMovement value is null");
		return;
	}

	static long long	 _Velocity_offset = -1;
	CMD_AssertClassSymbol(_CharacterMovement_offset, "/Script/Engine", "MovementComponent", "Velocity");

	double off_x = 0.0f;
	JSONArgsAssert_Get(args, retJson, "x", off_x);
	double off_y = 0.0f;
	JSONArgsAssert_Get(args, retJson, "y", off_y);

	//_logFFormat("CMD_UE4Game$CharacterMovementByVelocity, x = %.3f, y = %.3f", off_x, off_y);

	FVector * _VelocityBuffer = (FVector*)((uint64_t)_UBLCharacterMovementComponent + _Velocity_offset);

	if (0.0f != off_x) _VelocityBuffer->x += off_x;
	if (0.0f != off_y) _VelocityBuffer->y += off_y;

	JSONWriteValue_Double(retJson, "x", _VelocityBuffer->x);
	JSONWriteValue_Double(retJson, "y", _VelocityBuffer->y);
}

//void APawn::AddMovementInput(bool  bForce, float  ScaleValue, Struct  WorldDirection)
void CMD_UE4Game$AddMovementInput(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	struct _tag$AddMovementInput{
		FVector   	WorldDirection      ;//    offset = 0x00000000, flags = 0x0010000000000080, 使用世界方向向量表示移动方向
		float     	ScaleValue          ;//    offset = 0x0000000C, flags = 0x0010000000000080, 通常使用鼠标位移表示
		BOOL      	bForce              ;//    offset = 0x00000001, flags = 0x0010000000000080, 如果为真，表示总是使用此输入，忽略IsMoveInputIgnored()作用
	          							;//      Size = 0x00000014
	}_args = { NULL };

	JSONArgsTry_Get(args, "x", _args.WorldDirection.x, 0.0f);
	JSONArgsTry_Get(args, "y", _args.WorldDirection.y, 0.0f);
	JSONArgsTry_Get(args, "z", _args.WorldDirection.z, 0.0f);

	APawn_AddMovementInput(_PlayerAPawn, true, 1.0f, _args.WorldDirection);

	JSONWriteValue(retJson, "x", _args.WorldDirection.x);
	JSONWriteValue(retJson, "y", _args.WorldDirection.y);
	JSONWriteValue(retJson, "z", _args.WorldDirection.z);
}

//void AActor::K2_AddActorWorldOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void CMD_UE4Game$K2_AddActorWorldOffset(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	struct _tag$K2_AddActorWorldOffset{
		FVector   	DeltaLocation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		byte     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	JSONArgsTry_Get(args, "x", _args.DeltaLocation.x, 0.0f);
	JSONArgsTry_Get(args, "y", _args.DeltaLocation.y, 0.0f);
	JSONArgsTry_Get(args, "z", _args.DeltaLocation.z, 0.0f);

	AActor_AddActorWorldOffset(_PlayerAPawn, true, _args.DeltaLocation);

	JSONWriteValue(retJson, "x", _args.DeltaLocation.x);
	JSONWriteValue(retJson, "y", _args.DeltaLocation.y);
	JSONWriteValue(retJson, "z", _args.DeltaLocation.z);
}

//void AActor::K2_AddActorWorldRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void CMD_UE4Game$K2_AddActorWorldRotation(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	struct _tag$K2_AddActorWorldRotation{
		FRotator   	DeltaRotation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagRotator
		bool      	bSweep              ;//    offset = 0x00000001, flags = 0x0010040000000080, 
		byte     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010048000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010040000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	JSONArgsTry_Get(args, "pitch"	, _args.DeltaRotation.Pitch, 0.0f);
	JSONArgsTry_Get(args, "yaw"		, _args.DeltaRotation.Yaw  , 0.0f);
	JSONArgsTry_Get(args, "roll"	, _args.DeltaRotation.Roll , 0.0f);

	AActor_AddActorWorldRotation(_PlayerAPawn, true, _args.DeltaRotation);

	JSONWriteValue(retJson, "pitch"	, _args.DeltaRotation.Pitch);
	JSONWriteValue(retJson, "yaw"	, _args.DeltaRotation.Yaw);
	JSONWriteValue(retJson, "roll"	, _args.DeltaRotation.Roll);
}

//bool  AActor::K2_TeleportTo(Struct  DestRotation, Struct  DestLocation)
void CMD_UE4Game$K2_TeleportTo(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	struct _tag$K2_TeleportTo{
		FVector   	DestLocation        ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		FRotator   	DestRotation        ;//    offset = 0x0000000C, flags = 0x0010000000000080, _tagRotator
		bool      	ReturnValue         ;//    offset = 0x00000001, flags = 0x0010000000000580, 
	          							;//      Size = 0x0000001C
	}_args = { NULL };

	JSONArgsAssert_Get(args, retJson, "x", _args.DestLocation.x);
	JSONArgsAssert_Get(args, retJson, "y", _args.DestLocation.y);
	JSONArgsAssert_Get(args, retJson, "z", _args.DestLocation.z);


	JSONArgsTry_Get(args, "pitch"	, _args.DestRotation.Pitch, 0.0f);
	JSONArgsTry_Get(args, "yaw"		, _args.DestRotation.Yaw  , 0.0f);
	JSONArgsTry_Get(args, "roll"	, _args.DestRotation.Roll , 0.0f);

	if (0.0f == _args.DestRotation.Yaw && 0.0f == _args.DestRotation.Pitch && 0.0f == _args.DestRotation.Roll){
		_args.DestRotation = AActor_GetActorRotation(_PlayerAPawn);
	}

	AActor_TeleportTo(_PlayerAPawn, _args.DestRotation, _args.DestLocation);

	JSONWriteValue(retJson, "x", _args.DestLocation.x);
	JSONWriteValue(retJson, "y", _args.DestLocation.y);
	JSONWriteValue(retJson, "z", _args.DestLocation.z);

	JSONWriteValue(retJson, "pitch"	, _args.DestRotation.Pitch);
	JSONWriteValue(retJson, "yaw"	, _args.DestRotation.Yaw);
	JSONWriteValue(retJson, "roll"	, _args.DestRotation.Roll);
}

//void AActor::K2_AddActorLocalOffset(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaLocation)
void CMD_UE4Game$K2_AddActorLocalOffset(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	struct _tag$K2_AddActorLocalOffset{
		FVector   	DeltaLocation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		byte     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010008000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	JSONArgsTry_Get(args, "x", _args.DeltaLocation.x, 0.0f);
	JSONArgsTry_Get(args, "y", _args.DeltaLocation.y, 0.0f);
	JSONArgsTry_Get(args, "z", _args.DeltaLocation.z, 0.0f);

	AActor_AddActorLocalOffset(_PlayerAPawn, true, _args.DeltaLocation);

	JSONWriteValue(retJson, "x", _args.DeltaLocation.x);
	JSONWriteValue(retJson, "y", _args.DeltaLocation.y);
	JSONWriteValue(retJson, "z", _args.DeltaLocation.z);
}

//void AActor::K2_AddActorLocalRotation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  DeltaRotation)
void CMD_UE4Game$K2_AddActorLocalRotation(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAPawn = NULL;
	if (NULL == (_PlayerAPawn = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	struct _tag$K2_AddActorLocalRotation{
		FRotator   	DeltaRotation       ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagRotator
		bool      	bSweep              ;//    offset = 0x00000001, flags = 0x0010040000000080, 
		byte     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010048000000180, _tagHitResult
		bool      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010040000000080, 
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	JSONArgsTry_Get(args, "pitch"	, _args.DeltaRotation.Pitch, 0.0f);
	JSONArgsTry_Get(args, "yaw"		, _args.DeltaRotation.Yaw  , 0.0f);
	JSONArgsTry_Get(args, "roll"	, _args.DeltaRotation.Roll , 0.0f);

	AActor_AddActorLocalRotation(_PlayerAPawn, true, _args.DeltaRotation);

	JSONWriteValue(retJson, "pitch"	, _args.DeltaRotation.Pitch);
	JSONWriteValue(retJson, "yaw"	, _args.DeltaRotation.Yaw);
	JSONWriteValue(retJson, "roll"	, _args.DeltaRotation.Roll);
}


//bool  AActor::K2_SetActorLocation(bool  bTeleport, __out Struct *  SweepHitResult, bool  bSweep, Struct  NewLocation)
void CMD_UE4Game$K2_SetActorLocation(const JSONBuffer & args, JSONBuffer & retJson) {
	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	struct _tag$K2_SetActorLocation{
		FVector   	NewLocation         ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagVector
		BOOL      	bSweep              ;//    offset = 0x00000001, flags = 0x0010000000000080, 控制是否穿墙
		byte     	SweepHitResult[300] ;//    offset = 0x00000010, flags = 0x0010008000000180, 返回
		BOOL      	bTeleport           ;//    offset = 0x00000001, flags = 0x0010000000000080, 返回
		BOOL      	ReturnValue         ;//    offset = 0x00000001, flags = 0x0010000000000580, 返回
	          							;//      Size = 0x000000A0
	}_args = { NULL };

	JSONArgsTry_Get(args, "x", _args.NewLocation.x, 0.0f);
	JSONArgsTry_Get(args, "y", _args.NewLocation.y, 0.0f);
	JSONArgsTry_Get(args, "z", _args.NewLocation.z, 0.0f);

	JSONArgsTry_Get(args, "sweep", _args.bSweep, 0);

	AActor_SetActorLocation(_PlayerAActor, 0 != _args.bSweep, _args.NewLocation);

	JSONWriteValue(retJson, "x", _args.NewLocation.x);
	JSONWriteValue(retJson, "y", _args.NewLocation.y);
	JSONWriteValue(retJson, "z", _args.NewLocation.z);
}


void CMD_UE4Game$SetActorRotation(FRotator NewRotation, const UObject * _AActor, BOOL _PlayerAActor = FALSE) {
	AActor_SetActorRotation(_AActor, NewRotation);
	if (FALSE == _PlayerAActor) 
		return;
	const UObject * _AController = NULL;
	if (NULL == (_AController = _2UE4MainController()) || _AActor == _AController) {
		return;
	}

	AController_SetControlRotation(_AController, NewRotation);
}

//通过目标坐标, 切换角度
void CMD_UE4Game$SetActorRotationByLocation(const JSONBuffer & args, JSONBuffer & retJson) {
	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FVector		_location = AActor_GetActorLocation(_PlayerAActor);
	FRotator   	_rotation = AActor_GetActorRotation(_PlayerAActor);

	FVector   _toLocation;
	JSONArgsTry_Get(args, "x", _toLocation.x, 0.0f);
	JSONArgsTry_Get(args, "y", _toLocation.y, 0.0f);

	_rotation.Yaw = angle(_location, _toLocation);

	CMD_UE4Game$SetActorRotation(_rotation, _PlayerAActor, 0 != _type ? true : false);

	JSONWriteValue(retJson, "pitch"	, _rotation.Pitch);
	JSONWriteValue(retJson, "yaw"	, _rotation.Yaw);
	JSONWriteValue(retJson, "roll"	, _rotation.Roll);
}

//bool  AActor::K2_SetActorRotation(bool  bTeleportPhysics, Struct  NewRotation)
void CMD_UE4Game$K2_SetActorRotation(const JSONBuffer & args, JSONBuffer & retJson) {
	if (true == args.KeyExist("x") && true == args.KeyExist("y")) {
		return CMD_UE4Game$SetActorRotationByLocation(
			args, retJson
		);
	}

	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	struct _tag$K2_SetActorRotation{
		FRotator   	NewRotation         ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagRotator
		bool      	bTeleportPhysics    ;//    offset = 0x00000001, flags = 0x0010000000000080, 
		bool      	ReturnValue         ;//    offset = 0x00000001, flags = 0x0010000000000580, 
	          							;//      Size = 0x00000010
	}_args = { NULL };

	JSONArgsTry_Get(args, "pitch"	, _args.NewRotation.Pitch, 0.0f);
	JSONArgsTry_Get(args, "yaw"		, _args.NewRotation.Yaw  , 0.0f);
	JSONArgsTry_Get(args, "roll"	, _args.NewRotation.Roll , 0.0f);

	CMD_UE4Game$SetActorRotation(_args.NewRotation, _PlayerAActor , 0 != _type ? true : false);

	JSONWriteValue(retJson, "pitch"	, _args.NewRotation.Pitch);
	JSONWriteValue(retJson, "yaw"	, _args.NewRotation.Yaw);
	JSONWriteValue(retJson, "roll"	, _args.NewRotation.Roll);
}

//Struct  AActor::GetActorForwardVector()  +  AActor::GetActorRightVector()
void CMD_UE4Game$GetActorFRVector(const JSONBuffer & args, JSONBuffer & retJson) {
	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FVector   	ReturnValue = { NULL };

	ReturnValue = AActor_GetActorForwardVector(_PlayerAActor);
	JSONWriteValue(retJson, "forward_x", ReturnValue.x);
	JSONWriteValue(retJson, "forward_y", ReturnValue.y);
	JSONWriteValue(retJson, "forward_z", ReturnValue.z);

	ReturnValue = AActor_GetActorRightVector(_PlayerAActor);
	JSONWriteValue(retJson, "right_x", ReturnValue.x);
	JSONWriteValue(retJson, "right_y", ReturnValue.y);
	JSONWriteValue(retJson, "right_z", ReturnValue.z);
}

//Struct  AActor::K2_GetActorRotation()
void CMD_UE4Game$K2_GetActorRotation(const JSONBuffer & args, JSONBuffer & retJson) {
	
	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FRotator   	ReturnValue = AActor_GetActorRotation(_PlayerAActor);

	JSONWriteValue(retJson, "pitch"	, ReturnValue.Pitch);
	JSONWriteValue(retJson, "yaw"	, ReturnValue.Yaw);
	JSONWriteValue(retJson, "roll"	, ReturnValue.Roll);

}

//Struct  AActor::K2_GetActorLocation()
void CMD_UE4Game$K2_GetActorLocation(const JSONBuffer & args, JSONBuffer & retJson) {
	int _type = 0;
	JSONArgsTry_Get(args, "type", _type, 1);

	const UObject * _PlayerAActor = NULL;
	if (0 == _type && NULL == (_PlayerAActor = _2UE4MainController())) {
		JSONWriteERRString(retJson, "not find controller");
		return;
	}
	if (1 == _type && NULL == (_PlayerAActor = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}
	if (2 == _type && NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FVector   	ReturnValue = AActor_GetActorLocation(_PlayerAActor);

	JSONWriteValue(retJson, "x", ReturnValue.x);
	JSONWriteValue(retJson, "y", ReturnValue.y);
	JSONWriteValue(retJson, "z", ReturnValue.z);
}

//Struct  APlayerCameraManager::GetCameraRotation()
void CMD_UE4Game$GetCameraRotation(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAActor = NULL;
	if (NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FRotator   	ReturnValue = APlayerCameraManager_GetCameraRotation(_PlayerAActor);

	JSONWriteValue(retJson, "pitch", ReturnValue.Pitch);
	JSONWriteValue(retJson, "yaw", ReturnValue.Yaw);
	JSONWriteValue(retJson, "roll", ReturnValue.Roll);

}

//Struct  APlayerCameraManager::GetCameraLocation()
void CMD_UE4Game$GetCameraLocation(const JSONBuffer & args, JSONBuffer & retJson) {
	const UObject * _PlayerAActor = NULL;
	if (NULL == (_PlayerAActor = _2UE4MainCamera())) {
		JSONWriteERRString(retJson, "not find camera");
		return;
	}

	FVector   	ReturnValue = APlayerCameraManager_GetCameraLocation(_PlayerAActor);

	JSONWriteValue(retJson, "x", ReturnValue.x);
	JSONWriteValue(retJson, "y", ReturnValue.y);
	JSONWriteValue(retJson, "z", ReturnValue.z);
}





namespace WFrame {
	CRejection						_WFrameBufferLISTRejection;
	std::map<int, _tagWalkFrame>	_WFrameBufferLIST;
	FVector							_WDestination = { NULL }; //寻路的目的地位置
	const UObject *					_WPlayerAPwan = NULL;
	const UObject *					_WPlayerAController = NULL;

	int								_WPlayFrameIndex[2] = { 0, 0 }; //播放帧索引,0 == 最高帧, 1 == 最后使用帧

	DWORD                           _lastMoveTIME = NULL;
	FVector							_lastLocation = { NULL };

#define _Walk_时钟编号				    50001            
#define _Walk_播放速度					50               // xx 毫秒, 模拟一次
#define _Walk_超出距离					50.0f           //距离太远检测            
#define _Walk_成功距离					10.0f            //距离目的地, 低于当前值, 算作移动完成      

	std::string                     _errString = "";


	void WriteSCode(BOOL Success, std::string eString = "") {
		if (TRUE  == Success) _errString = "SUCCESS";
		if (FALSE == Success) _errString = eString;
	}

	//清空, 寻路帧配置
	void ClearWFrameBuffer() {
		_WFrameBufferLIST.clear();
		_WDestination		= { NULL };
		_WPlayerAPwan		= NULL;
		_WPlayerAController = NULL;
		_WPlayFrameIndex[0] = 0;
		_WPlayFrameIndex[1] = 0;
		_errString			= "";
		_lastMoveTIME		= NULL;
		_lastLocation		= { NULL };
	}

	//加载配置, 读取到所有帧
	int loadWalkFrameConfig(std::string filePath) {
		if (FALSE == PathFileExistsA(filePath.c_str()))
			return 0;

		FILE  *  _rRecordFile = NULL;
		if (NULL == (_rRecordFile = fopen(filePath.c_str(), "ab+")))
			return 0;

		fseek(_rRecordFile, 0, SEEK_SET);

		_tagWalkFrame tBuffer = { NULL };
		while (1 == fread(&tBuffer, sizeof(_tagWalkFrame), 1, _rRecordFile)) {

			_WFrameBufferLIST.insert(std::pair<int, _tagWalkFrame>(
				(int)_WFrameBufferLIST.size(), tBuffer
			));

			memset(&tBuffer, 0, sizeof(_tagWalkFrame));
		}

		fclose(_rRecordFile);

		_WPlayFrameIndex[0] = _WFrameBufferLIST.size();
		_WPlayFrameIndex[1] = 0;

		return _WPlayFrameIndex[0];
	}

	//获取 第 n 帧 的xy 坐标
	FVector getFrameLocation(int fIndex) {
		if (_WFrameBufferLIST.find(fIndex) 
			== _WFrameBufferLIST.end()){
			return { 0.0f, 0.0f, 0.0f };
		}

		_tagWalkFrame fBuffer = _WFrameBufferLIST[fIndex];

		return { fBuffer.x, fBuffer.y, fBuffer.z };
	}

	//获取两点距离, 帧 -> 点
	float dis_f2p(_tagWalkFrame frame, FVector point) {
		float x1 = frame.x;
		float y1 = frame.y;

		float x2 = point.x;
		float y2 = point.y;

		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	//获取两点距离, 点 -> 点
	float dis_p2p(FVector point1, FVector point2) {
		return point1.dis(point2);
	}

	//寻找与指定点, 距离最近的帧
	int findFrameByPoint(FVector point, _tagWalkFrame & fBuffer) {
		int lastIndex = -1;
		int lastDIS = 99999;
		for (auto & i : _WFrameBufferLIST) {

			int fdis = dis_f2p(i.second, point);

			if (fdis >= lastDIS)
				continue;

			lastIndex	= i.first;
			lastDIS		= fdis;
			fBuffer		= i.second;
		}
		return lastIndex;
	}

	//获取到点到帧 的视角 角度
	float yaw_p2f(FVector _location, _tagWalkFrame _2FrameBuffer) {
		FVector   _toLocation;
		_toLocation.x = _2FrameBuffer.x;
		_toLocation.y = _2FrameBuffer.y;
		_toLocation.z = _2FrameBuffer.z;

		return angle(_location, _toLocation);;
	}

	//模拟当前帧的 视角 + 前进
	void TIME_WalkFramePalyCallback(FVector _location, _tagWalkFrame actorFrameBuffer) {
		//本次模拟的 视角 角度
		float to_yaw = actorFrameBuffer.yaw;

		//当前坐标, 与 目的帧, 距离超出 xx 时, 修正目的地为当前帧
		if (20 < WFrame::dis_f2p(actorFrameBuffer, _location)) {  //已偏航太远, 设置临时目的地为 当前帧
			to_yaw = yaw_p2f(_location, actorFrameBuffer);
		}

		//获取当前角色的 朝向, 使用 Pitch, Roll
		FRotator _rotator = AActor_GetActorRotation(WFrame::_WPlayerAPwan);

		//主动设置一次, 当前控制器的角度
		AController_SetControlRotation(WFrame::_WPlayerAController, 
			{ _rotator.Pitch, to_yaw, _rotator.Roll }
		);

		//检测当前帧的 按键状态, 并且添加按住的时间
		TSTouchDurationPress("w", _Walk_播放速度 * 2);

		// 检测 是否可以按 Shift 进行加速跑

		//TSTouchDurationPress("left_shift", _walk_sleep * 2);
	}

	//周期事件, 播放寻路过程
	BOOL TIME_WalkFramePalyCallback() {

#define EBreak(ok, eString)  WFrame::WriteSCode(ok, eString);		\
							 break;

		int lastFIndex = 0;

		WFrame::_WFrameBufferLISTRejection.OpenRejection();
		do
		{
			//获取 最新的定位坐标
			FVector _location = AActor_GetActorLocation(_WPlayerAPwan);
			if (0.0f == _location.x && 0.0f == _location.y) {
				EBreak(FALSE, "取自身坐标异常!!");
			}

			if (0.0f == _lastLocation.x || 1 <= dis_p2p(_lastLocation, _location)){
				_lastMoveTIME = GetTickCount();
				_lastLocation = _location;
			}

			_logFFormat("寻路中, 当前坐标 = %.3f, %.3f" , _location.x, _location.y);

			if (_Walk_成功距离 >= dis_p2p(_location, WFrame::_WDestination)) {  //当前坐标, 与目的地 距离低于 x , 自动退出
				EBreak(TRUE, "已寻路到达目的地!!");
			}

			//获取当前所在的 坐标索引值
			_tagWalkFrame  actorFrameBuffer = { NULL };
			if (-1 == (lastFIndex = findFrameByPoint(_location, actorFrameBuffer))) {
				EBreak(FALSE, "寻找最近点失败!!"); //此项不会触发, 除非所有点 距离 > 9999
			}

			_logFFormat("寻路中, 当前坐标 = %.3f, %.3f, 当前帧 = %.3f, %.3f, frameIndex = %d", 
				_location.x, _location.y, actorFrameBuffer.x,
				actorFrameBuffer.y, lastFIndex
			);

			if (_Walk_超出距离 <= dis_f2p(actorFrameBuffer, _location)) {  //当前坐标, 与最近的坐标, 超出可移动范围, 跳出
				EBreak(FALSE, "最近距离已超出可模拟范围!!");
			}

			if (GetTickCount() - _lastMoveTIME >= 5 * 1000){
				EBreak(FALSE, "移动已异常停止!!");
			}

			// 更新, 最后使用的 帧
			WFrame::_WPlayFrameIndex[1] = lastFIndex;
			// 模拟一帧 的事件
			TIME_WalkFramePalyCallback(_location, actorFrameBuffer);
		
		} while (false);
		WFrame::_WFrameBufferLISTRejection.CloseRejection();

		if ("" == WFrame::_errString) return TRUE;   

		_logFormat("#寻路完成#, 执行寻路结果信息 = %s", WFrame::_errString.c_str());

		//最后, 无论相差多少距离, 瞬移一次
		AActor_TeleportTo(WFrame::_WPlayerAPwan, AActor_GetActorRotation(WFrame::_WPlayerAPwan),
			WFrame::_WDestination
		);

		WFrame::_WFrameBufferLISTRejection.OpenRejection();
		WFrame::_WFrameBufferLIST.clear();
		WFrame::_WFrameBufferLISTRejection.CloseRejection();

		TSTouch::TouchKeyUPAll();
		return FALSE;
	}

	void StartPlayWalkFrame() {
		SetTimer(NULL, _Walk_时钟编号, _Walk_播放速度, [](HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
			if (FALSE == TIME_WalkFramePalyCallback()) {
				::KillTimer(hwnd, idEvent);
			}
		});
	}

	void StopPlayWalkFrame() {
		TSTouch::TouchKeyUPAll();
		KillTimer(NULL, _Walk_时钟编号);
	}
}


std::string __2FullPathString(const char * nameString) {
	std::string rString = "";

	rString += getMainConsoleRootPathString();
	rString += "config\\walk\\";
	rString += nameString;

	return rString;
}

void CMD_UE4Game$StartPlayFrameConfig(const JSONBuffer & args, JSONBuffer & retJson) {

	// 获取到 帧文件的 全局路径
	std::string fPathString = "";
	JSONArgsAssert_Get(args, retJson, "path"   , fPathString);
	if (FALSE == PathFileExistsA(fPathString.c_str())){
		fPathString = __2FullPathString(fPathString.c_str());
		if (FALSE == PathFileExistsA(fPathString.c_str())) {
			JSONWriteERRString(retJson, "not find file");
			return;
		}
	}

	WFrame::_WFrameBufferLISTRejection.OpenRejection();
	
	//清除 buffer
	WFrame::ClearWFrameBuffer();
	WFrame::StopPlayWalkFrame();

	do
	{
		//-------------更新必要参数: 玩家的控制器
		if (NULL == (WFrame::_WPlayerAPwan			= _2UE4MainAPawn())) {		// 用于 短距离 瞬间移位
			JSONWriteERRString(retJson, "not find playerAPawn");
			break;
		}
		if (NULL == (WFrame::_WPlayerAController	= _2UE4MainController())) {	// 用于 控制视角
			JSONWriteERRString(retJson, "not find playerAController");
			break;
		}

		//-------------更新必要参数: 寻路的帧信息
		int fCount = 0;
		if (0 >= (fCount = WFrame::loadWalkFrameConfig(fPathString))){
			JSONWriteERRString(retJson, "frame is empty");
			break;
		}
		//-------------更新必要参数: 寻路目的地的 X Y 坐标
		WFrame::_WDestination = WFrame::getFrameLocation(fCount - 1);

		//开始播放 每一帧
		WFrame::StartPlayWalkFrame();

		//设置函数 返回值, 总帧数
		JSONWriteValue(retJson, "frame", fCount);

		JSONWriteValue(retJson, "to_x", WFrame::_WDestination.x);
		JSONWriteValue(retJson, "to_y", WFrame::_WDestination.y);

	} while (false);

	WFrame::_WFrameBufferLISTRejection.CloseRejection();
}

void CMD_UE4Game$StopPlayFrameConfig(const JSONBuffer & args, JSONBuffer & retJson) {
	WFrame::_WFrameBufferLISTRejection.OpenRejection();

	WFrame::ClearWFrameBuffer();

	WFrame::StopPlayWalkFrame();

	JSONWriteValue(retJson, "frame", WFrame::_WFrameBufferLIST.size());

	WFrame::_WFrameBufferLISTRejection.CloseRejection();
}

void CMD_UE4Game$GetPlayFrameProcess(const JSONBuffer & args, JSONBuffer & retJson) {
	WFrame::_WFrameBufferLISTRejection.OpenRejection();

	JSONWriteValue(retJson, "frame_cur"	, WFrame::_WPlayFrameIndex[1]);

	JSONWriteValue(retJson, "frame_max"	, WFrame::_WPlayFrameIndex[0]);

	JSONWriteValue(retJson, "status"	, WFrame::_errString);

	WFrame::_WFrameBufferLISTRejection.CloseRejection();

	FVector  lastXYZ = { NULL };

	lastXYZ = AActor_GetActorLocation(_2UE4MainAPawn());

	JSONWriteValue(retJson, "x", lastXYZ.x);
	JSONWriteValue(retJson, "y", lastXYZ.y);
	JSONWriteValue(retJson, "z", lastXYZ.z);
}

extern BOOL _UCharacterPerformMovementStatus;
void CMD_UE4Game$SetMovementStatus(const JSONBuffer & args, JSONBuffer & retJson) {
	int _WriteStatus = 0;
	JSONArgsTry_Get(retJson, "status", _WriteStatus, 2);

	switch (_WriteStatus){
	case 0:
		_UCharacterPerformMovementStatus = FALSE;
	case 1:
		_UCharacterPerformMovementStatus = TRUE;
		break;
	default:
		_UCharacterPerformMovementStatus = !_UCharacterPerformMovementStatus;
		break;
	}

	JSONWriteValue(retJson, "status", _UCharacterPerformMovementStatus);
}




bool CMDSwitch_DistributionCenter_定位移动(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //得到字符串 长度,

	if (strlen("UE4Game$GetActorFRVector") == lenth_method && 0 == strcmp("UE4Game$GetActorFRVector", method)) {
		CMD_UE4Game$GetActorFRVector(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$GetActorLocation") == lenth_method && 0 == strcmp("UE4Game$GetActorLocation", method)) {
		CMD_UE4Game$K2_GetActorLocation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$GetActorRotation") == lenth_method && 0 == strcmp("UE4Game$GetActorRotation", method)) {
		CMD_UE4Game$K2_GetActorRotation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$GetCameraRotation") == lenth_method && 0 == strcmp("UE4Game$GetCameraRotation", method)) {
		CMD_UE4Game$GetCameraRotation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$GetCameraLocation") == lenth_method && 0 == strcmp("UE4Game$GetCameraLocation", method)) {
		CMD_UE4Game$GetCameraLocation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$SetActorRotation") == lenth_method && 0 == strcmp("UE4Game$SetActorRotation", method)) {
		CMD_UE4Game$K2_SetActorRotation(args, retJson);
		return TRUE;
	}


	if (strlen("UE4Game$SetMovementStatus") == lenth_method && 0 == strcmp("UE4Game$SetMovementStatus", method)) {
		CMD_UE4Game$SetMovementStatus(args, retJson);
		return TRUE;
	}



	if (strlen("UE4Game$CharacterVelocity") == lenth_method && 0 == strcmp("UE4Game$CharacterVelocity", method)) {
		CMD_UE4Game$CharacterMovementByVelocity(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$AddMovementInput") == lenth_method && 0 == strcmp("UE4Game$AddMovementInput", method)) {
		CMD_UE4Game$AddMovementInput(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$AddWorldOffset") == lenth_method && 0 == strcmp("UE4Game$AddWorldOffset", method)) {
		CMD_UE4Game$K2_AddActorWorldOffset(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$AddWorldRotation") == lenth_method && 0 == strcmp("UE4Game$AddWorldRotation", method)) {
		CMD_UE4Game$K2_AddActorWorldRotation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$AddLocalOffset") == lenth_method && 0 == strcmp("UE4Game$AddLocalOffset", method)) {
		CMD_UE4Game$K2_AddActorLocalOffset(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$AddLocalRotation") == lenth_method && 0 == strcmp("UE4Game$AddLocalRotation", method)) {
		CMD_UE4Game$K2_AddActorLocalRotation(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$SetActorLocation") == lenth_method && 0 == strcmp("UE4Game$SetActorLocation", method)) {
		CMD_UE4Game$K2_SetActorLocation(args, retJson);
		return TRUE;
	}

	if (strlen("UE4Game$Teleport") == lenth_method && 0 == strcmp("UE4Game$Teleport", method)) {
		CMD_UE4Game$K2_TeleportTo(args, retJson);
		return TRUE;
	}

	//寻路的录制文件, 播放配置文件
	if (strlen("UE4Game$PlayMoveFrameConfig") == lenth_method && 0 == strcmp("UE4Game$PlayMoveFrameConfig", method)) {
		CMD_UE4Game$StartPlayFrameConfig(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$StopMoveFrameConfig") == lenth_method && 0 == strcmp("UE4Game$StopMoveFrameConfig", method)) {
		CMD_UE4Game$StopPlayFrameConfig(args, retJson);
		return TRUE;
	}
	if (strlen("UE4Game$GetMoveFrameProcess") == lenth_method && 0 == strcmp("UE4Game$GetMoveFrameProcess", method)) {
		CMD_UE4Game$GetPlayFrameProcess(args, retJson);
		return TRUE;
	}




	return false;
}











