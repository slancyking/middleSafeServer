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


//���Խӿ�
bool CMDSwitch_DistributionCenter_Debug(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//������� ��ؽӿ�
bool CMDSwitch_DistributionCenter_UnrealEngine4(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, �ƶ���λ
bool CMDSwitch_DistributionCenter_��λ�ƶ�(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, ��Χ����
bool CMDSwitch_DistributionCenter_��Χ����(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, ��ͼ����
bool CMDSwitch_DistributionCenter_��ͼ���(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, ���Թ���
bool CMDSwitch_DistributionCenter_���Թ���(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, ������Ϣ
bool CMDSwitch_DistributionCenter_������Ϣ(const char * method, const JSONBuffer & args, JSONBuffer & retJson);
//�����Ϸ��ؽӿڴ���, ��ɫ��Ϣ
bool CMDSwitch_DistributionCenter_��ɫ����(const char * method, const JSONBuffer & args, JSONBuffer & retJson);

bool CMDSwitch_MainDistributionCenter(const char * method, const JSONBuffer & args, JSONBuffer & retJson) {

	//���� �����Ϸ����ص���
	if (TRUE == CMDSwitch_DistributionCenter_��Χ����(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_��λ�ƶ�(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_��ͼ���(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_������Ϣ(method, args, retJson)) {
		return TRUE;
	}
	if (TRUE == CMDSwitch_DistributionCenter_��ɫ����(method, args, retJson)) {
		return TRUE;
	}



	if (TRUE == CMDSwitch_DistributionCenter_���Թ���(method, args, retJson)) {
		return TRUE;
	}
	//���� ���4 ����ص���
	if (TRUE == CMDSwitch_DistributionCenter_UnrealEngine4(method, args, retJson)) {
		return TRUE;
	}

	//��չ����� cmd ����
	if (TRUE == CMDToolsSwitchCallback_Extend(method, args, retJson)) {
		return TRUE;
	}

	//���Խӿ�
	if (TRUE == CMDSwitch_DistributionCenter_Debug(method, args, retJson)) {
		return TRUE;
	}
	_logFFormat("��, CMDServerCenter, Method not found : %s", method);
	return false;
}




