#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"
//
#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"


struct _tagTMPPoolINFO {
	std::list<const UObject *>		_ObjectLIST;
};



//��ȡ ������Ϣ ,  APawn
BOOL CMD_UE4Game$GetAPawnJSON(const UObject * _UObject, JSONBuffer & retJson) {
	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_UObject, &TMPHeadBuffer))
		return FALSE;

	__int64(*APawn_GetWorld)(const UObject *) = NULL;

	// AActor::ProcessEvent -> AActor::GetWorld
	//if ( (v6 = byte_5B2EC42, (v7 = (*(__int64 (**)(void))(*(_QWORD *)a1 + 0x150i64))()) != 0) && (sub_2FAE860(v7) || v6)
	if (TRUE == UE4::readMemory(_2UObjectPointer(TMPHeadBuffer.vfTable, 0x150), &APawn_GetWorld, sizeof(void *)))
		JSONWriteValue_UInt64(retJson, "world", APawn_GetWorld(_UObject));

	FVector _ALocation = AActor_GetActorLocation(_UObject);
	JSONWriteValue_Double(retJson, "x", _ALocation.x);
	JSONWriteValue_Double(retJson, "y", _ALocation.y);
	JSONWriteValue_Double(retJson, "z", _ALocation.z);

	FRotator _ARotator = AActor_GetActorRotation(_UObject);
	JSONWriteValue_Double(retJson, "pitch"	, _ARotator.Pitch);
	JSONWriteValue_Double(retJson, "yaw"	, _ARotator.Yaw);
	JSONWriteValue_Double(retJson, "roll"	, _ARotator.Roll);


	JSONWriteValue_UInt64(retJson, "controller", APawn_GetController(_UObject));

	JSONWriteValue_UInt64(retJson, "keyClass"	, TMPHeadBuffer.ClassPrivate);
	JSONWriteValue_UInt64(retJson, "vfTable"	, UE4::_2MModuleOffset(TMPHeadBuffer.vfTable));

	JSONWriteValue_UInt64(retJson, "object", _UObject);


	uint64_t         ivar_PlayerState    = NULL;
	static long long _PlayerState_offset = -1;
	if (-1 == _PlayerState_offset) _PlayerState_offset = _2UE4IvarOffset("/Script/Engine", "Pawn", "PlayerState");
	if (-1 != _PlayerState_offset && UE4::readMemory(_2UObjectPointer(_UObject, _PlayerState_offset), &ivar_PlayerState, sizeof(uint64_t))) {
		JSONWriteValue_UInt64(retJson, "PlayerState", ivar_PlayerState);
	}

	const UObject * _PlayerAActor = NULL;

	// ת�����������ɫ�ľ�����Ϣ
	FVector _PlayerLocation = AActor_GetActorLocation(_PlayerAActor = _2UE4MainAPawn());
	JSONWriteValue_Double(retJson, "dis", _PlayerLocation.dis(_ALocation));

	//�������� ת ��Ļ����
	FVector2D _SLocation = APlayerController_ProjectWorldLocationToScreen(_PlayerAActor = _2UE4MainController(), _ALocation);
	JSONWriteValue_Double(retJson, "screen_x", _SLocation.x);
	JSONWriteValue_Double(retJson, "screen_y", _SLocation.y);

	return TRUE;
}

//��ȡ ���е� APawn ��չ������Ϣ
void CMD_UE4Game$GetAPawnLIST(const JSONBuffer & args, JSONBuffer & retJson) {

	//��һ��: �õ� APawn ����ָ��
	static UE4$UClass  * _APawnClass = NULL;
	if (NULL == _APawnClass && NULL == (_APawnClass = UE4::findUE4Class(
											"/Script/Engine", "Pawn"))) {
		JSONWriteERRString(retJson, "not find class");
		return;
	}

	//�ڶ���: �õ����м̳��� APawn �Ķ�����Ϣ
	std::map<const UE4$UClass *, std::list<const UObject *>> allAPawnUObjectLIST;
	UE4::enumUObject([&allAPawnUObjectLIST](const UE4$UObjectHEAD & _HeadBuffer, const UObject * _UObject) {
		if (FALSE == UE4::UClassEnterSuperClass(_HeadBuffer.ClassPrivate, _APawnClass))
			return FALSE;
		if (allAPawnUObjectLIST.find(_HeadBuffer.ClassPrivate) == allAPawnUObjectLIST.end()){
			allAPawnUObjectLIST.insert(std::pair<const UE4$UClass *, std::list<const UObject *>>(
				_HeadBuffer.ClassPrivate, { }
			));
		}
		allAPawnUObjectLIST[_HeadBuffer.ClassPrivate].push_back(_UObject);
		return FALSE;
	});

	//������: ���� ÿ�����ݵ���ϸ��Ϣ
	for (auto TMPAPawnMember = allAPawnUObjectLIST.begin(); TMPAPawnMember != allAPawnUObjectLIST.end(); TMPAPawnMember++){
		const UE4$UClass * TMPUClass = TMPAPawnMember->first;
		
		if (FALSE == _UE4ObjectISValid(TMPUClass))
			break;

		std::string NString = UE4::FName_ToString(&TMPUClass->NamePrivate);
		
		if (FALSE == retJson.KeyExist(NString.c_str()))
			retJson.AddEmptySubArray(NString.c_str());

		for (auto & TMPAPawnObject : TMPAPawnMember->second){
			JSONBuffer _JsonBuffer;
			if (TRUE == CMD_UE4Game$GetAPawnJSON(TMPAPawnObject, _JsonBuffer)) {
				retJson[NString.c_str()].Add(_JsonBuffer);
			}
		}
	}
}



bool CMDSwitch_DistributionCenter_��Χ����(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //�õ��ַ��� ����,

	if (strlen("UE4Game$GetAPawnLISTMember") == lenth_method && 0 == strcmp("UE4Game$GetAPawnLISTMember", method)) {
		CMD_UE4Game$GetAPawnLIST(args, retJson);
		return TRUE;
	}


	return false;
}











