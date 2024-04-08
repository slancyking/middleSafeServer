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
FVector   			_WalkLastLocation		= { NULL }; //首次设置这个定位,不参与记录
int                 _WalkRecordFrameIndex	= 0;
HWND                _WalkRecordHWND         = NULL;
DWORD				_WalkRecordRefTIME	    = NULL;

BOOL thread_WalkRecordCallback() {
	int _errorStatusCode = 0;

	_tagWalkFrame wBuffer = { NULL };

	_WalkRecordBufferRejection.OpenRejection(); //每 xx 毫秒, 允许进入一次
	FILE * _file = NULL;
	do
	{
		//获取 最新的定位坐标
		FVector _location = AActor_GetActorLocation(_APlayerPawnBuffer);
		if (0.0f == _location.x && 0.0f == _location.y) {
			_errorStatusCode = 1;
			break;
		}
		_WalkRecordRefTIME = GetTickCount();

		//检测坐标是否变化,  坐标未变化时, 不参与记录
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

		//通知, 帧数更新
		PostMessage(_WalkRecordHWND, WM_WALKRECORD_REFFRAME, _WalkRecordFrameIndex, 1);

	} while (false);
	if (NULL != _file) fclose(_file);

	_WalkRecordBufferRejection.CloseRejection();

	if (0 == _errorStatusCode) return TRUE;

	//通知, 录制已异常停止
 	PostMessage(_WalkRecordHWND, WM_WALKRECORD_QUIT, _errorStatusCode, 0);

	_WalkRecordBufferRejection.OpenRejection(); //每 xx 毫秒, 允许进入一次

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

	if (NULL == _APlayerPawnBuffer || true == _WalkRecordTHREADStatus) {  //录制中, 错误返回
		JSONWriteERRString(retJson, "recording");
		return;
	}

	_WalkRecordBufferRejection.OpenRejection();

	//读取出, 本次录制的基础参数信息
	JSONArgsTry_Get(args, "path", _WalkRecordFilePath, "");
	JSONArgsTry_Get(args, "hwnd", (int&)_WalkRecordHWND, NULL);
	if ("" == _WalkRecordFilePath || FALSE == IsWindow(_WalkRecordHWND)){
		JSONWriteERRString(retJson, "args error");
		_WalkRecordBufferRejection.CloseRejection();
		return;
	}

	//记录, 最新的坐标信息, 注意: 优先获取
	_WalkLastLocation  = AActor_GetActorLocation(_APlayerPawnBuffer);
	_WalkRecordRefTIME = GetTickCount();
	if (0.0f == _WalkLastLocation.x && 0.0f == _WalkLastLocation.y){
		JSONWriteERRString(retJson, "location error");
		_WalkRecordBufferRejection.CloseRejection();
		return;
	}

	//重置, 帧索引
	_WalkRecordFrameIndex = 0;

	//启动线程, 开始录制
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

	//通知, 录制已经开始
	PostMessage(_WalkRecordHWND, WM_WALKRECORD_START, 0, 0);
}

void CMD_Debug$StopWalkRecording(const JSONBuffer & args, JSONBuffer & retJson) {
	_WalkRecordBufferRejection.OpenRejection();

	//重置, 帧索引, 以及其他变量
	_WalkRecordFrameIndex	= 0;
	_WalkRecordFilePath		= "";
	_WalkRecordHWND			= NULL;
	_WalkRecordTHREADStatus = false;

	_WalkRecordBufferRejection.CloseRejection();

	JSONWriteValue_Bool(retJson, "status", true);
}




bool CMDSwitch_DistributionCenter_调试功能(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	size_t lenth_method = strlen(method); //得到字符串 长度,

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


