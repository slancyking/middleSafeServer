#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"
//
#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"

bool			    _WalkRecordTHREADStatus = false;

CRejection			_WalkRecordBufferRejection;

const UObject *     _APlayerPawnBuffer      = NULL;
std::string			_WalkRecordFilePath		= "";
FVector   			_WalkLastLocation		= { NULL }; //�״����������λ,�������¼
int                 _WalkRecordFrameIndex	= 0;
HWND                _WalkRecordHWND         = NULL;
DWORD				_WalkRecordRefTIME	    = NULL;

BOOL thread_WalkRecordCallback() {
	int _errorStatusCode = 0;

	_tagWalkFrame wBuffer = { NULL };

	_WalkRecordBufferRejection.OpenRejection(); //ÿ xx ����, �������һ��
	FILE * _file = NULL;
	do
	{
		//��ȡ ���µĶ�λ����
		FVector _location = AActor_GetActorLocation(_APlayerPawnBuffer);
		if (0.0f == _location.x && 0.0f == _location.y) {
			_errorStatusCode = 1;
			break;
		}
		_WalkRecordRefTIME = GetTickCount();

		//��������Ƿ�仯,  ����δ�仯ʱ, �������¼
		if ((int)_location.x == (int)_WalkLastLocation.x) {
			if ((int)_location.y == (int)_WalkLastLocation.y) {
				break;
			}
		}
		_WalkLastLocation = _location;

		FRotator _rotation = AActor_GetActorRotation(_APlayerPawnBuffer);

		if (NULL == (_file = fopen(_WalkRecordFilePath.c_str(), "ab+"))) {
			_errorStatusCode = 2;
			break;
		}

		_WalkRecordFrameIndex = _WalkRecordFrameIndex + 1;

		wBuffer.x		= _location.x;
		wBuffer.y		= _location.y;
		wBuffer.z		= _location.z;
		wBuffer.yaw		= _rotation.Yaw;

		fwrite(&wBuffer, sizeof(_tagWalkFrame), 1, _file);

		//֪ͨ, ֡������
		PostMessage(_WalkRecordHWND, WM_WALKRECORD_REFFRAME, _WalkRecordFrameIndex, 1);

	} while (false);
	if (NULL != _file) fclose(_file);

	_WalkRecordBufferRejection.CloseRejection();

	if (0 == _errorStatusCode) return TRUE;

	//֪ͨ, ¼�����쳣ֹͣ
 	PostMessage(_WalkRecordHWND, WM_WALKRECORD_QUIT, _errorStatusCode, 0);

	_WalkRecordBufferRejection.OpenRejection(); //ÿ xx ����, �������һ��

	_WalkRecordFilePath     = "";
	_WalkRecordTHREADStatus = false;

	_WalkRecordBufferRejection.CloseRejection();

	return FALSE;
}


void CMD_Debug$StartWalkRecording(const JSONBuffer & args, JSONBuffer & retJson) {
	if (NULL == (_APlayerPawnBuffer = _2UE4MainAPawn())) {
		JSONWriteERRString(retJson, "not find playerAPawn");
		return;
	}

	if (NULL == _APlayerPawnBuffer || true == _WalkRecordTHREADStatus) {  //¼����, ���󷵻�
		JSONWriteERRString(retJson, "recording");
		return;
	}

	_WalkRecordBufferRejection.OpenRejection();

	//��ȡ��, ����¼�ƵĻ���������Ϣ
	JSONArgsTry_Get(args, "path", _WalkRecordFilePath, "");
	JSONArgsTry_Get(args, "hwnd", (int&)_WalkRecordHWND, NULL);
	if ("" == _WalkRecordFilePath || FALSE == IsWindow(_WalkRecordHWND)){
		JSONWriteERRString(retJson, "args error");
		_WalkRecordBufferRejection.CloseRejection();
		return;
	}

	//��¼, ���µ�������Ϣ, ע��: ���Ȼ�ȡ
	_WalkLastLocation  = AActor_GetActorLocation(_APlayerPawnBuffer);
	_WalkRecordRefTIME = GetTickCount();
	if (0.0f == _WalkLastLocation.x && 0.0f == _WalkLastLocation.y){
		JSONWriteERRString(retJson, "location error");
		_WalkRecordBufferRejection.CloseRejection();
		return;
	}

	//����, ֡����
	_WalkRecordFrameIndex = 0;

	//�����߳�, ��ʼ¼��
	_WalkRecordTHREADStatus = true;
	::SetTimer(NULL, NULL, 50, [](HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
		if ("" == _WalkRecordFilePath || NULL == _APlayerPawnBuffer) {
			_WalkRecordTHREADStatus = false;
			KillTimer(hwnd, idEvent);
			return;
		}
		if (FALSE == thread_WalkRecordCallback()){
			_WalkRecordTHREADStatus = false;
			KillTimer(hwnd, idEvent);
			return;
		}
	});

	_WalkRecordBufferRejection.CloseRejection();

	JSONWriteValue_Bool(retJson, "status", true);

	//֪ͨ, ¼���Ѿ���ʼ
	PostMessage(_WalkRecordHWND, WM_WALKRECORD_START, 0, 0);
}

void CMD_Debug$StopWalkRecording(const JSONBuffer & args, JSONBuffer & retJson) {
	_WalkRecordBufferRejection.OpenRejection();

	//����, ֡����, �Լ���������
	_WalkRecordFrameIndex	= 0;
	_WalkRecordFilePath		= "";
	_WalkRecordHWND			= NULL;
	_WalkRecordTHREADStatus = false;

	_WalkRecordBufferRejection.CloseRejection();

	JSONWriteValue_Bool(retJson, "status", true);
}




bool CMDSwitch_DistributionCenter_���Թ���(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //�õ��ַ��� ����,

	if (strlen("DEBUG$StartWalkRecord") == lenth_method && 0 == strcmp("DEBUG$StartWalkRecord", method)) {
		CMD_Debug$StartWalkRecording(args, retJson);
		return TRUE;
	}

	if (strlen("DEBUG$StopWalkRecord") == lenth_method && 0 == strcmp("DEBUG$StopWalkRecord", method)) {
		CMD_Debug$StopWalkRecording(args, retJson);
		return TRUE;
	}

	return false;
}


