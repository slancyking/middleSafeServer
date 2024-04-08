#pragma once

#include "..\\XUnrealEngine4\\TScript_UnrealEngine4.h"
#include "..\\XUnrealEngine4\\TSConfig_UE4OffsetByUI.h"
#include <string>

namespace UE4_UI
{ 
#define UI_OBJECT  "SWidgetObject"
#define UI_CHILE "SChildObject"



	class CSlateWinodw/* SWindow 类 */ {
	public:
		CSlateWinodw(const void* _kObject) {
			_SWindow = _kObject;
		};
	public:
		std::string	ToString() {
			static void* _call = 0;
			if (NULL == _call) _call = _2SYMPointer(SWindow$ToString);
			if (NULL == _call) UE4_logEString("定位方法: FString __cdecl SWindow::ToString(void)const , 异常!!");

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
			//获取 UE4$FGenericWindowVtbl 指针
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
			//获取 UE4$FGenericWindowVtbl 指针
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
			//获取 UE4$FGenericWindowVtbl 指针
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
			//获取 UE4$FGenericWindowVtbl 指针
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
			//获取 UE4$FGenericWindowVtbl 指针
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


	//----------------------------------------控件数据读取部分

	// 子控件的数据信息获取, 注: 当前只处理 FSlateBrush    类型
	BOOL GetSWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SWidget(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_STextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SRichTextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SButton(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetUE4Game$SWidgetControlINFO_SImage(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);

	BOOL GetCMD_UE4Game$SWidgetControlINFO_SEditableText(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer);


	//----------------------------------------枚举查找控件部分

	// 子控件的数据信息获取, 注: 当前只处理 FSlateBrush    类型
	BOOL CMD_UE4Game$SWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 SWidget     类型
	BOOL CMD_UE4Game$SWidgetControlINFO_SWidget(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 STextBlock 类型
	BOOL CMD_UE4Game$SWidgetControlINFO_STextBlock(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 SRichTextBlock 类型
	BOOL CMD_UE4Game$SWidgetControlINFO_SRichTextBlock(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 SButton    类型
	BOOL CMD_UE4Game$SWidgetControlINFO_SButton(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 SImage     类型
	BOOL CMD_UE4Game$SWidgetControlINFO_SImage(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 注: 当前只处理 SEditableText  类型
	BOOL CMD_UE4Game$SWidgetControlINFO_SEditableText(const SWidget* _kControlObject, Json::Value args);

	// 子控件的数据信息获取, 以及, 子控件的递归处理
	PVOID CMD_UE4Game$SWidgetControlINFO(const SWidget* _kControlObject, string type, Json::Value args, BOOL EnumChild, int level);

	// 主窗口的遍历过程, 基于 PrepassWindowAndChildren 逆向!!
	PVOID CMD_UE4Game$SlateWinodwINFO(const SWindow* _SlateWinodwObject, string type, Json::Value args);
	// 主窗口的遍历过程, 基于 PrepassWindowAndChildren 逆向!!
	PVOID CMD_UE4Game$GetSlateWindowLIST(std::function<PVOID(void*)> enumCallback);

	// 子控件的遍历过程, 基于 SWidget::Prepass_Internal 逆向!!
	PVOID CMD_UE4Game$SWidgetControlINFO_Prepass_Internal(const SWidget* _kObject, std::function<PVOID(const SWidget* _kObject, int kIndex)> EnmuCallback);

	//----------------------------------------接口部分

	//查找控件  类型 + {属性:值}
	PVOID findControl(string type,Json::Value args);

	//根据控件指针获取属性  指针 + 属性名
	string getControlProperty(PVOID pControl,string cType, string pName);
	//获取控件的完整属性
	string getControlFullProperty(PVOID pControl, string cType);


	//获取控件的子控件列表  指针


};

