#pragma once
//
#include "TScript_UnrealEngine4.h"



namespace UE4 {
	// 获取 全局UObject 数目
	const uint32_t getUE4UObjectCount() {
		uint64_t TMPGUObjectArray = NULL;
		if (NULL == (TMPGUObjectArray = (uint64_t)_2SYMPointer(UE4$GUObjectArray))) {
			return 0;
		}

		//偏移值, 可以从以下位置查看

		//__int64 __fastcall FWeakObjectPtr::Get(FWeakObjectPtr *this)

		//void __fastcall UObject::ProcessEvent(struct UObject *a1, __int64 a2, int *a3)

		uint32_t GUObjectCount = 0;
		if (FALSE == UE4::readMemory((void *)(TMPGUObjectArray + 0x00000014), &GUObjectCount, sizeof(uint32_t))) {
			return 0;
		}

		return GUObjectCount;
	}

	// 获取 第 n 个全局对象
	BOOL getUE4UObjectINFO(int32_t kIndex, UE4$GUObjectINFO & RBuffer) {
		uint64_t TMPGUObjectArray = NULL;
		if (NULL == (TMPGUObjectArray = (uint64_t)_2SYMPointer(UE4$GUObjectArray)))
			return FALSE;
		if (kIndex >= _2UE4UObjectCount())
			return FALSE;

		{
			//__int64 __fastcall FWeakObjectPtr::Get(FWeakObjectPtr *this)

			//void __fastcall UObject::ProcessEvent(struct UObject *a1, __int64 a2, int *a3)

			// v3 = kIndex

			//v8 = *(_QWORD *)(GUObjectArray + 8i64 * (v3 / 0x10000)) + 24i64 * (v3 % -65536);
		}

		//TMPGUObjectArray = *(_QWORD *)(GUObjectArray + 8i64 * (v3 / 0x10000))
		if (FALSE == UE4::readMemory((void *)TMPGUObjectArray, &TMPGUObjectArray, sizeof(uint64_t)))
			return FALSE;

		TMPGUObjectArray = TMPGUObjectArray + 8 * (kIndex / 0x10000);
		if (FALSE == UE4::readMemory((void *)TMPGUObjectArray, &TMPGUObjectArray, sizeof(uint64_t)))
			return FALSE;

		//TMPGUObject = *(_QWORD *)(GUObjectArray + 8i64 * (v3 / 0x10000)) + 24i64 * (v3 % -65536);
		uint64_t TMPGUObject = TMPGUObjectArray + 24 * (kIndex % -65536);// kIndex % -65536 = kIndex % 0x10000

		//--[[ 当前调试信息: address = 0x00000216F4C40000 ]]--

		//+0x0000 : 0x00000216F4A97F40 
		//+0x0008 : 0x0000000040000000 
		//+0x0010 : 0x0000000000000000 //-----------------0x18 == 24 == 每个结构的大小
		//+0x0018 : 0x00000216F2721F00 
		//+0x0020 : 0x0000000042000000 
		//+0x0028 : 0x00000000000003EA 
		//+0x0030 : 0x00000216F4A98300 
		//+0x0038 : 0x0000000040000000 
		//+0x0040 : 0x00000000000003F9 
		//+0x0048 : 0x00000216F272C7C0 
		//+0x0050 : 0x0000000042000000 
		//+0x0058 : 0x0000000000000000 
		//+0x0060 : 0x00000216F4A97FE0 

		if (FALSE == UE4::readMemory((void *)TMPGUObject, &RBuffer, sizeof(UE4$GUObjectINFO)))
			return FALSE;

		return TRUE;
	}

	// 获取 第 n 个全局对象
	const UObject * getUE4UObject(int32_t kIndex) {

		struct UE4$GUObjectINFO TMPUObjectBuffer = { NULL };
		if (FALSE == getUE4UObjectINFO(kIndex, TMPUObjectBuffer))
			return NULL;

		if (false == TMPUObjectBuffer.IsValid())
			return NULL;

		return TMPUObjectBuffer._kUObject;
	}

	//--------------------------------------------------------------------------------------------------------------------------------

	// 获取 世界对象
	const UObject * getUE4World() {
		uint64_t TMPWorldValue = NULL;
		if (NULL == (TMPWorldValue = (uint64_t)_2SYMPointer(UE4$GWorld)))
			return NULL;
		if (FALSE == UE4::readMemory((void *)TMPWorldValue, &TMPWorldValue, sizeof(uint64_t)))
			return NULL;

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == UE4::enterUObjectHEAD((void *)TMPWorldValue, &TMPHeadBuffer))
			return NULL;

		return (const UObject *)TMPWorldValue;
	}

	// 获取 实例对象
	const UObject * getUE4GameInstance() {
		uint64_t TMPWorldValue = NULL;
		if (NULL == (TMPWorldValue = (uint64_t)_2UE4GWorld()))
			return NULL;

		static long long _ivar_offset = -1;
		if (NULL > _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/Engine", "World","OwningGameInstance");
		if (NULL > _ivar_offset) return NULL;

		//UWorld::OwningGameInstance, offset = 0x00000178, <8   >, type = UObject, flags = 0x0040000000002000,
		//.object = 0x00000248B3C62500
		//.class = LHGameInstance

		const UObject * TMPGameInstance = NULL;
		if (FALSE == UE4::readMemory((void *)(TMPWorldValue + _ivar_offset), &TMPGameInstance, sizeof(uint64_t)))
			return NULL;

		return (const UObject *)TMPGameInstance;
	}

	// 获取 玩家对象
	const UObject * getUE4LocalPlayers(int lIndex) {
		uint64_t TMPGameInstance = NULL;
		if (NULL == (TMPGameInstance = (uint64_t)_2UE4GameInstance()))
			return NULL;
	
		//UGameInstance::LocalPlayers                                 , offset = 0x00000038, <16  >, type = FArray         , flags = 0x0020080000000000, 
		//.array = 0x00000248B687BAE0   1 \ 4

		static long long _ivar_offset = -1;
		if (NULL > _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/Engine", "GameInstance", "LocalPlayers");
		if (NULL > _ivar_offset) return NULL;

		UE4$FArray TMPLocalPlayers = { NULL };
		if (FALSE == UE4::readMemory((void *)(TMPGameInstance + _ivar_offset), &TMPLocalPlayers, sizeof(UE4$FArray)))
			return NULL;

		if (0 > lIndex || lIndex >= TMPLocalPlayers._count)
			return NULL;

		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == UE4::enterUObjectHEAD(TMPLocalPlayers.objects[lIndex], &TMPHeadBuffer))
			return NULL;

		return TMPLocalPlayers.objects[lIndex];
	}

	// 获取 玩家控制器
	const UObject * getUE4PlayerController() {
		uint64_t TMPUE4Player = NULL;
		if (NULL == (TMPUE4Player = (uint64_t)_2UE4LocalPlayer(0)))
			return NULL;
	
		//UPlayer::PlayerController                                   , offset = 0x00000030, <8   >, type = UObject        , flags = 0x0010000000002000, 
		//.object = 0x00000248B39DC040
		//.class  = LHPlayerController_Login

		static long long _ivar_offset = -1;
		if (NULL > _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/Engine", "Player", "PlayerController");
		if (NULL > _ivar_offset) return NULL;

		const UObject * TMPController = NULL;
		if (FALSE == UE4::readMemory((void *)(TMPUE4Player + _ivar_offset), &TMPController, sizeof(uint64_t)))
			return NULL;

		return (const UObject *)TMPController;
	}

	// 获取 玩家APawn 对象
	const UObject * getUE4AcknowledgedPawn() {
		uint64_t TMPController = NULL;
		if (NULL == (TMPController = (uint64_t)_2UE4MainController()))
			return NULL;

		//APlayerController::AcknowledgedPawn                         , offset = 0x00000298, <8   >, type = UObject        , flags = 0x0010000000000000, 
		//.object = 0x00000248EDF33340
		//.class  = BP_Warrior_C

		static long long _ivar_offset = -1;
		if (NULL > _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/Engine", "PlayerController", "AcknowledgedPawn");
		if (NULL > _ivar_offset) return NULL;

		const UObject * TMPPawnValue = NULL;
		if (FALSE == UE4::readMemory((void *)(TMPController + _ivar_offset), &TMPPawnValue, sizeof(uint64_t)))
			return NULL;

		return (const UObject *)TMPPawnValue;
	}

	// 获取 玩家摄像机管理对象 
	const UObject * getUE4APlayerCameraManager() {
		uint64_t TMPController = NULL;
		if (NULL == (TMPController = (uint64_t)_2UE4MainController()))
			return NULL;

		//APlayerController::PlayerCameraManager                      , offset = 0x000002B0, <8   >, type = UObject        , flags = 0x0010000000000014, 
		//.object = 0x00000248F03AD560
		//.class  = BP_PlayerCameraManager_C

		static long long _ivar_offset = -1;
		if (NULL > _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/Engine", "PlayerController", "PlayerCameraManager");
		if (NULL > _ivar_offset) return NULL;

		const UObject * TMPCameraManager = NULL;
		if (FALSE == UE4::readMemory((void *)(TMPController + _ivar_offset), &TMPCameraManager, sizeof(uint64_t)))
			return NULL;

		return (const UObject *)TMPCameraManager;
	}

	// 获取 FSlateApplication 对象
	const FSlateApplication * getUE4FSlateApplication() {
		uint64_t TMPWorldValue = NULL;
		if (NULL == (TMPWorldValue = (uint64_t)_2SYMPointer(FSlateApplication$CurrentApplication)))
			return NULL;

		if (FALSE == UE4::readMemory((void *)TMPWorldValue, &TMPWorldValue, sizeof(uint64_t)))
			return NULL;

		if (FALSE == UE4::enterVFTable((void *)TMPWorldValue))
			return NULL;

		return (const FSlateApplication *)TMPWorldValue;
	}


}













