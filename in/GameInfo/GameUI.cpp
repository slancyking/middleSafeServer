
#include "GameUI.h"

BOOL MAINWindow_IsValid(const UObject* _MAINWindow) {
	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_MAINWindow, &TMPHeadBuffer))
		return FALSE;

	//--[[ 当前调试信息: address = 0x0000026269E1A4C0 ]]-- 所属类: UCanvasPanel  有效
	//
	//UObject::vfTable                                            , offset = 0x00000000, <8   >, type = uint64_t       , flags = 0x0000092A57BC5E11, 
	//value = 140698575953416       -> 0x00007FF6F0A3DE08
	//
	//UObject::ObjectFlags                                        , offset = 0x00000008, <4   >, type = uint32_t       , flags = 0x0000092A57BC5E11, 
	//value = 8                     -> 00000008
	if (EObjectFlags::RF_LoadCompleted == (TMPHeadBuffer.ObjectFlags & EObjectFlags::RF_LoadCompleted)) {
		return FALSE;
	}
	//--[[ 当前调试信息: address = 0x0000026269E11780 ]]-- 所属类: UCanvasPanel   无效
	//
	//UObject::vfTable                                            , offset = 0x00000000, <8   >, type = uint64_t       , flags = 0x0000092A57BC5E11, 
	//value = 140698575953416       -> 0x00007FF6F0A3DE08
	//
	//UObject::ObjectFlags                                        , offset = 0x00000008, <4   >, type = uint32_t       , flags = 0x0000092A57BC5E11, 
	//value = 2621448               -> 00280008
	return TRUE;
}

BOOL _EnterType_UCanvasPanel(const UObject* _UE4Object) {
	static UE4$UClass* _MAINWindowClass = NULL;
	if (NULL == _MAINWindowClass && NULL == (_MAINWindowClass = UE4::findUE4Class(
		"/Script/UMG", "CanvasPanel"))) {
		return FALSE;
	}

	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_UE4Object, &TMPHeadBuffer))
		return FALSE;

	return UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _MAINWindowClass);
}

BOOL _EnterType_UCanvasPanelSlot(const UObject* _UE4Object) {
	static UE4$UClass* _BaseClass = NULL;
	if (NULL == _BaseClass && NULL == (_BaseClass = UE4::findUE4Class(
		"/Script/UMG", "CanvasPanelSlot"))) {
		return FALSE;
	}

	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_UE4Object, &TMPHeadBuffer))
		return FALSE;

	return UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _BaseClass);
}


//确认一个类型,  是否为 主窗口
BOOL _EnterType_ISWindow(const UObject* _UE4Object) {
	if (TRUE == _EnterType_UCanvasPanel(_UE4Object))
		return TRUE;



	return FALSE;
}


BOOL readMAINWindowSlotsBuffer(const UObject* _UWindowObject, UE4$FArray& rArrayBuffer) {
	static long long _Slots_offset = -1;
	if (-1 == _Slots_offset) _Slots_offset = _2UE4IvarOffset("/Script/UMG", "PanelWidget", "Slots");
	if (-1 != _Slots_offset && UE4::readMemory(_2UObjectPointer(_UWindowObject, _Slots_offset), &rArrayBuffer, sizeof(UE4$FArray))) {
		return rArrayBuffer._count <= rArrayBuffer._max && 0 < rArrayBuffer._count;
	}
	return FALSE;
}

const UObject* readUCanvasPanelSlotBuffer(const UObject* _UWindowObject) {
	static long long _Content_offset = -1;
	if (-1 == _Content_offset && -1 == (_Content_offset = _2UE4IvarOffset(
		"/Script/UMG", "PanelSlot", "Content"))) {
		return NULL;
	}

	const UObject* rBuffer = NULL;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _Content_offset), &rBuffer, sizeof(const UObject*)))
		return NULL;

	return rBuffer;
}


//获取 详情信息 , 基础数据信息
void CMD_UE4Game$BaseINFO(const UObject* _UWindowObject, JSONBuffer& retJson) {
	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_UWindowObject, &TMPHeadBuffer))
		return;

	JSONWriteValue_UInt64(retJson, "object", _UWindowObject);

	JSONWriteValue(retJson, "name", UE4::FName_ToString(&TMPHeadBuffer.NamePrivate));

	JSONWriteValue(retJson, "type", UE4::FName_ToString(&TMPHeadBuffer.ClassPrivate->NamePrivate));
}



//获取 详情信息 , 控件数据信息, 按钮控件
void CMD_UE4Game$ControlINFO_Button(const UObject* _UWindowObject, JSONBuffer& retJson) {
	static long long _WidgetStyle_offset = -1;
	if (-1 == _WidgetStyle_offset) _WidgetStyle_offset = _2UE4IvarOffset("/Script/UMG", "Button", "WidgetStyle");
	if (-1 == _WidgetStyle_offset) return;

	FButtonStyle TMPButtonStyleBuffer;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _WidgetStyle_offset),
		&TMPButtonStyleBuffer, sizeof(FButtonStyle)))
		return;

	JSONWriteValue(retJson, "Normal", UE4::FName_ToString(&TMPButtonStyleBuffer.Normal.ResourceName));
	JSONWriteValue(retJson, "Hovered", UE4::FName_ToString(&TMPButtonStyleBuffer.Hovered.ResourceName));
	JSONWriteValue(retJson, "Pressed", UE4::FName_ToString(&TMPButtonStyleBuffer.Pressed.ResourceName));
	JSONWriteValue(retJson, "Disabled", UE4::FName_ToString(&TMPButtonStyleBuffer.Disabled.ResourceName));

	std::string tString = "";

	if (0 != (tString = UE4::FName_ToString(&TMPButtonStyleBuffer.PressedSlateSound.ResourceName)).length()) {
		JSONWriteValue(retJson, "PressedSound", tString.c_str());
	}
	if (0 != (tString = UE4::FName_ToString(&TMPButtonStyleBuffer.HoveredSlateSound.ResourceName)).length()) {
		JSONWriteValue(retJson, "HoveredSound", tString.c_str());
	}

	uint64_t callBack[3] = { NULL };

	static long long _OnClicked_offset = -1;
	if (-1 == _OnClicked_offset) _OnClicked_offset = _2UE4IvarOffset("/Script/UMG", "Button", "OnClicked");
	if (-1 == _OnClicked_offset) return;

	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _OnClicked_offset),
		&callBack[0], sizeof(uint64_t) * 3))
		return;

	if (NULL != callBack[0]) JSONWriteValue_UInt64(retJson, "OnClicked1", callBack[0]);
	if (NULL != callBack[1]) JSONWriteValue_UInt64(retJson, "OnClicked2", callBack[1]);
	if (NULL != callBack[2]) JSONWriteValue_UInt64(retJson, "OnClicked3", callBack[2]);

	static long long _OnReleased_offset = -1;
	if (-1 == _OnReleased_offset) _OnClicked_offset = _2UE4IvarOffset("/Script/UMG", "Button", "OnReleased");
	if (-1 == _OnReleased_offset) return;

	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _OnReleased_offset),
		&callBack[0], sizeof(uint64_t) * 3))
		return;

	if (NULL != callBack[0]) JSONWriteValue_UInt64(retJson, "OnReleased1", callBack[0]);
	if (NULL != callBack[1]) JSONWriteValue_UInt64(retJson, "OnReleased2", callBack[1]);
	if (NULL != callBack[2]) JSONWriteValue_UInt64(retJson, "OnReleased3", callBack[2]);

	static long long _OnUnhovered_offset = -1;
	if (-1 == _OnUnhovered_offset) _OnClicked_offset = _2UE4IvarOffset("/Script/UMG", "Button", "OnUnhovered");
	if (-1 == _OnUnhovered_offset) return;


	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _OnUnhovered_offset),
		&callBack[0], sizeof(uint64_t) * 3))
		return;

	if (NULL != callBack[0]) JSONWriteValue_UInt64(retJson, "OnUnhovered1", callBack[0]);
	if (NULL != callBack[1]) JSONWriteValue_UInt64(retJson, "OnUnhovered2", callBack[1]);
	if (NULL != callBack[2]) JSONWriteValue_UInt64(retJson, "OnUnhovered3", callBack[2]);
}

//获取 详情信息 , 控件数据信息, 文本块控件
void CMD_UE4Game$ControlINFO_TextBlock(const UObject* _UWindowObject, JSONBuffer& retJson) {
	static long long _Text_offset = -1;
	if (-1 == _Text_offset) _Text_offset = _2UE4IvarOffset("/Script/UMG", "TextBlock", "Text");
	if (-1 == _Text_offset) return;

	JSONWriteValue(retJson, "Text", UE4::FText_ToString(_2UObjectPointer(_UWindowObject, _Text_offset)));

	static long long _Font_offset = -1;
	if (-1 == _Font_offset) _Font_offset = _2UE4IvarOffset("/Script/UMG", "TextBlock", "Font");
	if (-1 == _Font_offset) return;

	FSlateFontInfo TMPFontBuffer;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _Font_offset),
		&TMPFontBuffer, sizeof(FSlateFontInfo)))
		return;

	JSONWriteValue(retJson, "FontSize", TMPFontBuffer.Size);
	JSONWriteValue(retJson, "FontName", UE4::FName_ToString(&TMPFontBuffer.TypefaceFontName));

	JSONWriteValue_UInt64(retJson, "FontObject", TMPFontBuffer.FontObject);
}

//获取 详情信息 , 控件数据信息, 图形控件
void CMD_UE4Game$ControlINFO_UImage(const UObject* _UWindowObject, JSONBuffer& retJson) {
	static long long _Brush_offset = -1;
	if (-1 == _Brush_offset) _Brush_offset = _2UE4IvarOffset("/Script/UMG", "Image", "Brush");
	if (-1 == _Brush_offset) return;

	_tagSlateBrush TMPBrushBuffer;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _Brush_offset),
		&TMPBrushBuffer, sizeof(_tagSlateBrush)))
		return;

	JSONWriteValue(retJson, "ImageName", UE4::FName_ToString(&TMPBrushBuffer.ResourceName));

	JSONWriteValue(retJson, "ImageSize", CString::format("%-5d, %d", TMPBrushBuffer.ImageSize.x, TMPBrushBuffer.ImageSize.y));
}


//获取 详情信息 , 控件数据信息, 文本块控件
void CMD_UE4Game$ControlINFO_RichTextBlock(const UObject* _UWindowObject, JSONBuffer& retJson) {
	static long long _Text_offset = -1;
	if (-1 == _Text_offset) _Text_offset = _2UE4IvarOffset("/Script/UMG", "RichTextBlock", "Text");
	if (-1 == _Text_offset) return;

	JSONWriteValue(retJson, "Text", UE4::FText_ToString(_2UObjectPointer(_UWindowObject, _Text_offset)));

	//static long long _Font_offset = -1;
	//if (-1 == _Font_offset) _Font_offset = _2UE4IvarOffset("/Script/UMG", "UTextBlock", "Font");
	//if (-1 == _Font_offset) return;

	//FSlateFontInfo TMPFontBuffer;
	//if (FALSE == UE4::readMemory(_2UObjectPointer(_UWindowObject, _Font_offset),
	//	&TMPFontBuffer, sizeof(FSlateFontInfo)))
	//	return;

	//JSONWriteValue(retJson, "FontSize", TMPFontBuffer.Size);
	//JSONWriteValue(retJson, "FontName", FName_ToString(&TMPFontBuffer.TypefaceFontName).getBuffer());

	//JSONWriteValue_UInt64(retJson, "FontObject", TMPFontBuffer.FontObject);
}


//获取 详情信息 , 控件数据信息
BOOL CMD_UE4Game$ControlINFO(const UObject* _UWindowObject, JSONBuffer& retJson) {
	//第一步: 读取出自身的对象信息
	UE4$UObjectHEAD TMPHeadBuffer;
	if (FALSE == _UE4ObjectISValid(_UWindowObject, &TMPHeadBuffer))
		return FALSE;

	//确认是否为 按钮控件
	static UE4$UClass* _UCClass_Button = NULL;
	if (NULL == _UCClass_Button && NULL == (_UCClass_Button = UE4::findUE4Class(
		"/Script/UMG", "Button"))) {
		return FALSE;
	}
	if (TRUE == UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _UCClass_Button)) {
		CMD_UE4Game$ControlINFO_Button(_UWindowObject, retJson);
		return TRUE;
	}

	//确认是否为 按钮文本块
	static UE4$UClass* _UCClass_TextBlock = NULL;
	if (NULL == _UCClass_TextBlock && NULL == (_UCClass_TextBlock = UE4::findUE4Class(
		"/Script/UMG", "TextBlock"))) {
		return FALSE;
	}
	if (TRUE == UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _UCClass_TextBlock)) {
		CMD_UE4Game$ControlINFO_TextBlock(_UWindowObject, retJson);
		return TRUE;
	}

	//确认是否为 按钮富文本块
	static UE4$UClass* _UCClass_RichTextBlock = NULL;
	if (NULL == _UCClass_RichTextBlock && NULL == (_UCClass_RichTextBlock = UE4::findUE4Class(
		"/Script/UMG", "RichTextBlock"))) {
		return FALSE;
	}
	if (TRUE == UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _UCClass_RichTextBlock)) {
		CMD_UE4Game$ControlINFO_RichTextBlock(_UWindowObject, retJson);
		return TRUE;
	}

	//确认是否为 图形控件
	static UE4$UClass* _UCClass_UImage = NULL;
	if (NULL == _UCClass_UImage && NULL == (_UCClass_UImage = UE4::findUE4Class(
		"/Script/UMG", "Image"))) {
		return FALSE;
	}
	if (TRUE == UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _UCClass_UImage)) {
		CMD_UE4Game$ControlINFO_UImage(_UWindowObject, retJson);
		return TRUE;
	}


	return FALSE;
}

//获取 详情信息 , 
BOOL CMD_UE4Game$AnalysisUE4SysmetUI(const UObject* _UWindowObject, JSONBuffer& retJson, int aCount = 0) {
	if (20 <= aCount) return FALSE;

	JSONBuffer _JsonBuffer;

	//第一步: 无论是什么类型对象, 添加基础对象信息
	CMD_UE4Game$BaseINFO(_UWindowObject, _JsonBuffer);

	do
	{
		//第二步: 检测, 是否为 控件类型
		if (TRUE == CMD_UE4Game$ControlINFO(_UWindowObject, _JsonBuffer)) {
			break;
		}

		//第三步: 检测, 是否为 窗口类型
		if (NULL != _UWindowObject && TRUE == _EnterType_ISWindow(_UWindowObject)) {
			UE4$FArray tSlotsValue = { NULL };
			if (TRUE == readMAINWindowSlotsBuffer(_UWindowObject, tSlotsValue)) {

				JSONWriteValue(_JsonBuffer, "Slots_count", tSlotsValue._count);
				JSONWriteValue(_JsonBuffer, "Slots_max", tSlotsValue._max);
				JSONWriteValue_UInt64(_JsonBuffer, "Slots_mem", tSlotsValue.objects);

				_JsonBuffer.AddEmptySubArray("Slots");

				for (int tIndex = 0; tIndex < tSlotsValue._count; tIndex++) {
					const UObject* tUE4Object = NULL;

					if (NULL == (tUE4Object = tSlotsValue.objects[tIndex]))
						continue;

					//检测, 是否为 槽 对象 
					if (NULL != tUE4Object && TRUE == _EnterType_UCanvasPanelSlot(tUE4Object)) {
						tUE4Object = readUCanvasPanelSlotBuffer(tUE4Object);
					}

					//递归, 处理所有 子UI数据
					CMD_UE4Game$AnalysisUE4SysmetUI(tUE4Object, _JsonBuffer["Slots"], aCount + 1);
				}
			}
			break;
		}
	} while (false);

	retJson.Add(_JsonBuffer);
	return TRUE;


}

void CMD_UE4Game$GetMainWindowLIST(const JSONBuffer& args, JSONBuffer& retJson) {
	static UE4$UClass* _MAINWindowClass = NULL;
	if (NULL == _MAINWindowClass && NULL == (_MAINWindowClass = UE4::findUE4Class(
		"/Script/UMG", "CanvasPanel"))) {
		JSONWriteERRString(retJson, "not find class");
		return;
	}

	retJson.AddEmptySubArray("winodws");

	uint32_t TMPObjectCount = _2UE4UObjectCount();
	for (uint32_t kIndex = 0; kIndex < TMPObjectCount; kIndex++) {
		const UObject* _UObject = NULL;
		if (NULL == (_UObject = _2UE4UObjectPtr(kIndex)))
			continue;
		UE4$UObjectHEAD TMPHeadBuffer;
		if (FALSE == _UE4ObjectISValid(_UObject, &TMPHeadBuffer))
			continue;

		if (FALSE == UE4::UClassEnterSuperClass(TMPHeadBuffer.ClassPrivate, _MAINWindowClass))
			continue;

		if (FALSE == MAINWindow_IsValid(_UObject))
			continue;

		CMD_UE4Game$AnalysisUE4SysmetUI(_UObject, retJson["winodws"]);
	}
}


bool CMDSwitch_DistributionCenter_视图相关(const char* method, const JSONBuffer& args, JSONBuffer& retJson) {
	size_t lenth_method = strlen(method); //得到字符串 长度,

	if (strlen("UE4Game$GetMainWindowLIST") == lenth_method && 0 == strcmp("UE4Game$GetMainWindowLIST", method)) {
		CMD_UE4Game$GetMainWindowLIST(args, retJson);
		return TRUE;
	}



	return false;
}









