#pragma once
//
#include "pch.h"
//
#include "TScript_export.h"
//
#include "CMDServer_toolsCenter.h"

extern std::list<callback_CMDExtend>  allCMDExtendCallback;

bool CMDToolsSwitchCallback_Extend(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {
	if (0 >= allCMDExtendCallback.size() || NULL == method) {
		return false;
	}

	bool         rStatus = false;
	const char * rString = NULL;
	std::string argString = args.ToString();

	if ("" == argString) argString = "{ }";
	for (std::list<callback_CMDExtend>::iterator i = allCMDExtendCallback.begin(); i != allCMDExtendCallback.end(); i++) {
		callback_CMDExtend debug_extendCall = *i;
		if (NULL == debug_extendCall) continue;

		if (NULL == (rString = debug_extendCall(method, argString.c_str())))
			continue;

		if (false == retJson.Parse(rString)) {
			free((void *)rString);
			break;
		}

		free((void *)rString);
		rStatus = true;
		break;
	}


	return rStatus;
}


//测试接口
bool CMDSwitch_DistributionCenter_Debug(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻引擎 相关接口
bool CMDSwitch_DistributionCenter_UnrealEngine4(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 移动定位
bool CMDSwitch_DistributionCenter_定位移动(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 周围对象
bool CMDSwitch_DistributionCenter_周围对象(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 视图处理
bool CMDSwitch_DistributionCenter_视图相关(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 调试功能
bool CMDSwitch_DistributionCenter_调试功能(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 任务信息
bool CMDSwitch_DistributionCenter_任务信息(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//虚幻游戏相关接口处理, 角色信息
bool CMDSwitch_DistributionCenter_角色属性(const char * method, const JSONBuffer & args, JSONBuffer & retJson);

bool CMDSwitch_MainDistributionCenter(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {

	//关于 虚幻游戏的相关调用
	if (TRUE == CMDSwitch_DistributionCenter_周围对象(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_定位移动(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_视图相关(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_任务信息(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_角色属性(method, args, retJson)) {
		return TRUE;
	}



	if (TRUE == CMDSwitch_DistributionCenter_调试功能(method, args, retJson)) {
		return TRUE;
	}
	//关于 虚幻4 的相关调用
	if (TRUE == CMDSwitch_DistributionCenter_UnrealEngine4(method, args, retJson)) {
		return TRUE;
	}

	//扩展插件的 cmd 调用
	if (TRUE == CMDToolsSwitchCallback_Extend(method, args, retJson)) {
		return TRUE;
	}

	//测试接口
	if (TRUE == CMDSwitch_DistributionCenter_Debug(method, args, retJson)) {
		return TRUE;
	}
	_logFFormat("×, CMDServerCenter, Method not found : %s", method);
	return false;
}




