#pragma once

#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"
#include "..\\XUnrealEngine4\\TSConfig_UE4OffsetByUI.h"
#include <string>

namespace UE4_UI
{ 
#define UI_OBJECT  "SWidgetObject"
#define UI_CHILE "SChildObject"



	class CSlateWinodw/* SWindow �� */ {
	public:
		CSlateWinodw(const void* _kObject) {
			_SWindow = _kObject;
		};
	public:
		std::string	ToString() {
			static void* _call = 0;
			if (NULL == _call) _call = _2SYMPointer(SWindow$ToString);
			if (NULL == _call) UE4_logEString("��λ����: FString __cdecl SWindow::ToString(void)const , �쳣!!");

			const FString* (*debug_call)(const SWindow*, FString*) = (const FString * (*)(const SWindow*, FString*))_call;

			UE4$FString _tagFStringBuffer = { NULL };
			if (NULL == debug_call(_SWindow, (FString*)&_tagFStringBuffer)) {
				return "";
			}

			std::string rString = UE4::FString_ToString((const FString*)&_tagFStringBuffer);

			if (NULL != _tagFStringBuffer._string)
				UE4::FMemory_Free(_tagFStringBuffer._string);

			return rString;
		}

		std::string	ToType() {

			uint64_t TMPValue = NULL;
			if (NULL == (TMPValue = (uint64_t)_SWindow))
				return "Normal";

			TMPValue += UE4$SWindow$Type;

			uint32_t kTypeBuffer = (uint32_t)EWindowType::Normal;
			if (FALSE == UE4::readMemory((void*)TMPValue, &kTypeBuffer, sizeof(EWindowType)))
				return "";

			switch (kTypeBuffer) {
			case (uint32_t)EWindowType::Menu:
				return "Menu";
				break;
			case (uint32_t)EWindowType::ToolTip:
				return "ToolTip";
				break;
			case (uint32_t)EWindowType::Notification:
				return "Notification";
				break;
			case (uint32_t)EWindowType::CursorDecorator:
				return "CursorDecorator";
				break;
			case (uint32_t)EWindowType::GameWindow:
				return "GameWindow";
				break;
			default:
				break;
			}
			return "Normal";
		}

		FVector2D  ToPosition() {
			uint64_t TMPValue = NULL;
			if (NULL == (TMPValue = (uint64_t)_SWindow))
				return { NULL };

			TMPValue += UE4$SWindow$ScreenPosition;

			FVector2D TMPBuffer = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &TMPBuffer, sizeof(FVector2D)))
				return { NULL };

			return TMPBuffer;
		}

		FVector2D  ToSize() {
			uint64_t TMPValue = NULL;
			if (NULL == (TMPValue = (uint64_t)_SWindow))
				return { NULL };

			TMPValue += UE4$SWindow$Size;

			FVector2D TMPBuffer = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &TMPBuffer, sizeof(FVector2D)))
				return { NULL };

			return TMPBuffer;
		}

		void* NativeWindow() {
			uint64_t TMPValue = NULL;
			if (NULL == (TMPValue = (uint64_t)_SWindow))
				return { NULL };

			TMPValue += UE4$SWindow$NativeWindow;

			if (FALSE == UE4::readMemory((void*)TMPValue, &TMPValue, sizeof(uint64_t)))
				return { NULL };

			return (void*)TMPValue;
		}

		BOOL       IsVisible() {
			void* TMPNativeWindow = NULL;
			if (NULL == (TMPNativeWindow = NativeWindow()))
				return FALSE;

			uint64_t TMPValue = NULL;
			//��ȡ UE4$FGenericWindowVtbl ָ��
			if (FALSE == UE4::readMemory(TMPNativeWindow, &TMPValue, sizeof(uint64_t)))
				return FALSE;

			UE4$FGenericWindowVtbl VFTable = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &VFTable, sizeof(UE4$FGenericWindowVtbl)))
				return FALSE;

			typedef BOOL(*API_DebugCall)(const void*);

			API_DebugCall debug_call = (API_DebugCall)VFTable.IsVisible;

			return debug_call(TMPNativeWindow);
		}

		BOOL       IsMinimized() {
			void* TMPNativeWindow = NULL;
			if (NULL == (TMPNativeWindow = NativeWindow()))
				return FALSE;

			uint64_t TMPValue = NULL;
			//��ȡ UE4$FGenericWindowVtbl ָ��
			if (FALSE == UE4::readMemory(TMPNativeWindow, &TMPValue, sizeof(uint64_t)))
				return FALSE;

			UE4$FGenericWindowVtbl VFTable = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &VFTable, sizeof(UE4$FGenericWindowVtbl)))
				return FALSE;

			typedef BOOL(*API_DebugCall)(const void*);

			API_DebugCall debug_call = (API_DebugCall)VFTable.IsMinimized;

			return debug_call(TMPNativeWindow);
		}

		BOOL       IsMaximized() {
			void* TMPNativeWindow = NULL;
			if (NULL == (TMPNativeWindow = NativeWindow()))
				return FALSE;

			uint64_t TMPValue = NULL;
			//��ȡ UE4$FGenericWindowVtbl ָ��
			if (FALSE == UE4::readMemory(TMPNativeWindow, &TMPValue, sizeof(uint64_t)))
				return FALSE;

			UE4$FGenericWindowVtbl VFTable = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &VFTable, sizeof(UE4$FGenericWindowVtbl)))
				return FALSE;

			typedef BOOL(*API_DebugCall)(const void*);

			API_DebugCall debug_call = (API_DebugCall)VFTable.IsMaximized;

			return debug_call(TMPNativeWindow);
		}

		BOOL       Enable() {
			void* TMPNativeWindow = NULL;
			if (NULL == (TMPNativeWindow = NativeWindow()))
				return FALSE;

			uint64_t TMPValue = NULL;
			//��ȡ UE4$FGenericWindowVtbl ָ��
			if (FALSE == UE4::readMemory(TMPNativeWindow, &TMPValue, sizeof(uint64_t)))
				return FALSE;

			UE4$FGenericWindowVtbl VFTable = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &VFTable, sizeof(UE4$FGenericWindowVtbl)))
				return FALSE;

			typedef BOOL(*API_DebugCall)(const void*);

			API_DebugCall debug_call = (API_DebugCall)VFTable.Enable;

			return debug_call(TMPNativeWindow);
		}

		float      DPIScaleFactor() {
			void* TMPNativeWindow = NULL;
			if (NULL == (TMPNativeWindow = NativeWindow()))
				return FALSE;

			uint64_t TMPValue = NULL;
			//��ȡ UE4$FGenericWindowVtbl ָ��
			if (FALSE == UE4::readMemory(TMPNativeWindow, &TMPValue, sizeof(uint64_t)))
				return FALSE;

			UE4$FGenericWindowVtbl VFTable = { NULL };
			if (FALSE == UE4::readMemory((void*)TMPValue, &VFTable, sizeof(UE4$FGenericWindowVtbl)))
				return FALSE;

			typedef float (*API_DebugCall)(const void*);

			API_DebugCall debug_call = (API_DebugCall)VFTable.GetDPIScaleFactor;

			return debug_call(TMPNativeWindow);
		}





	private:
		const SWindow* _SWindow;
	};

	typedef struct _tagTBaseDelegate {
		uint64_t  DelegateAllocator;
		uint32_t  DelegateSize;
		uint32_t  unknown;
	}TBaseDelegate;


	//----------------------------------------�ؼ����ݶ�ȡ����

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� FSlateBrush    ����
	BOOL GetSWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SWidget(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_STextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SRichTextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SButton(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SImage(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetCMD_UE4Game$SWidgetControlINFO_SEditableText(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);


	//----------------------------------------ö�ٲ��ҿؼ�����

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� FSlateBrush    ����
	BOOL CMD_UE4Game$SWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� SWidget     ����
	BOOL CMD_UE4Game$SWidgetControlINFO_SWidget(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� STextBlock ����
	BOOL CMD_UE4Game$SWidgetControlINFO_STextBlock(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� SRichTextBlock ����
	BOOL CMD_UE4Game$SWidgetControlINFO_SRichTextBlock(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� SButton    ����
	BOOL CMD_UE4Game$SWidgetControlINFO_SButton(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� SImage     ����
	BOOL CMD_UE4Game$SWidgetControlINFO_SImage(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, ע: ��ǰֻ���� SEditableText  ����
	BOOL CMD_UE4Game$SWidgetControlINFO_SEditableText(const SWidget* _kControlObject, Json::Value args);

	// �ӿؼ���������Ϣ��ȡ, �Լ�, �ӿؼ��ĵݹ鴦��
	PVOID CMD_UE4Game$SWidgetControlINFO(const SWidget* _kControlObject, string type, Json::Value args, BOOL EnumChild, int level);

	// �����ڵı�������, ���� PrepassWindowAndChildren ����!!
	PVOID CMD_UE4Game$SlateWinodwINFO(const SWindow* _SlateWinodwObject, string type, Json::Value args);
	// �����ڵı�������, ���� PrepassWindowAndChildren ����!!
	PVOID CMD_UE4Game$GetSlateWindowLIST(std::function<PVOID(void*)> enumCallback);

	// �ӿؼ��ı�������, ���� SWidget::Prepass_Internal ����!!
	PVOID CMD_UE4Game$SWidgetControlINFO_Prepass_Internal(const SWidget* _kObject, std::function<PVOID(const SWidget* _kObject, int kIndex)> EnmuCallback);

	//----------------------------------------�ӿڲ���

	//���ҿؼ�  ���� + {����:ֵ}
	PVOID findControl(string type,Json::Value args);

	//���ݿؼ�ָ���ȡ����  ָ�� + ������
	string getControlProperty(PVOID pControl,string cType, string pName);
	//��ȡ�ؼ�����������
	string getControlFullProperty(PVOID pControl, string cType);


	//��ȡ�ؼ����ӿؼ��б�  ָ��


};

