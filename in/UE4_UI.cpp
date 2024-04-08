#include "pch.h"
#include "UE4_UI.h"




// 子控件的数据信息获取, 注: 当前只处理 FSlateBrush    类型
BOOL UE4_UI::GetSWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {

	FSlateBrush TMPBrushBuffer;
	if (FALSE == UE4::readMemory(_kControlObject, &TMPBrushBuffer, sizeof(FSlateBrush)))
		return FALSE;

	retJSONBuffer["ResourceObject"] = CString::format("0x%016I64X", TMPBrushBuffer.ResourceObject);  
	retJSONBuffer["ResourceName"] = UE4::FName_ToString(&TMPBrushBuffer.ResourceName); 
	retJSONBuffer["ImageSize"] = CString::format("%-5d, %d", TMPBrushBuffer.ImageSize.x, TMPBrushBuffer.ImageSize.y); 

	UE4$UObjectHEAD TMPHeadBuffer = { NULL };
	if (TRUE == _UE4ObjectISValid(TMPBrushBuffer.ResourceObject, &TMPHeadBuffer)) {
		retJSONBuffer["ResourceType"] = UE4::FName_ToString(&TMPHeadBuffer.NamePrivate); 
	}
	retJSONBuffer["ResourceType"] = UE4::FName_ToString(&TMPHeadBuffer.NamePrivate);
	retJSONBuffer["Margin"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPBrushBuffer.Margin.Left,
		TMPBrushBuffer.Margin.Top,
		TMPBrushBuffer.Margin.Right,
		TMPBrushBuffer.Margin.Bottom
	);

	retJSONBuffer["DrawAs"] = format("{}", (int)TMPBrushBuffer.DrawAs);
	retJSONBuffer["Tiling"] = format("{}", (int)TMPBrushBuffer.Tiling);
	retJSONBuffer["Mirroring"] = format("{}", (int)TMPBrushBuffer.Mirroring);
	retJSONBuffer["ImageType"] = format("{}", (int)TMPBrushBuffer.ImageType);
  
	retJSONBuffer["UVRegion.Min"] =  CString::format("%.3f * %.3f",
		TMPBrushBuffer.UVRegion.Min.x, TMPBrushBuffer.UVRegion.Min.y);

	retJSONBuffer["UVRegion.Max"] =  CString::format("%.3f * %.3f",
		TMPBrushBuffer.UVRegion.Max.x, TMPBrushBuffer.UVRegion.Max.y);

	retJSONBuffer["UVRegion.IsValid"] =  CString::format("%d",
		TMPBrushBuffer.UVRegion.bIsValid);

	retJSONBuffer["TintColor"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPBrushBuffer.TintColor.SpecifiedColor.R,
		TMPBrushBuffer.TintColor.SpecifiedColor.G,
		TMPBrushBuffer.TintColor.SpecifiedColor.B,
		TMPBrushBuffer.TintColor.SpecifiedColor.A);

	retJSONBuffer["TintColor.UseRule"] = CString::format("%016I64X",
		TMPBrushBuffer.TintColor.ColorUseRule);

	return TRUE;
}

BOOL UE4_UI::GetUE4Game$SWidgetControlINFO_SWidget(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	UE4$SWidget* kObject = (UE4$SWidget*)_kControlObject;

	retJSONBuffer[ "Tag"] = UE4::FName_ToString(&kObject->Tag);
	retJSONBuffer["EnabledState"] = format("{}", (int)kObject->EnabledState[0]);
	retJSONBuffer["Visibility"] = format("{}", (int)kObject->Visibility[0]);
 
	TBaseDelegate TMPDelegateBuffer;
	if (FALSE == UE4::readMemory(kObject->MouseEnterHandler, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;

	retJSONBuffer["MouseEnterHandler"] =  CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	if (FALSE == UE4::readMemory(kObject->MouseLeaveHandler, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;

	retJSONBuffer["MouseLeaveHandler"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	UE4$FSlateWidgetPersistentState  TMPPersistentState = { NULL };
	if (FALSE == UE4::readMemory(&kObject->PersistentState, &TMPPersistentState, sizeof(UE4$FSlateWidgetPersistentState)))
		return FALSE;

	retJSONBuffer["PaintParent"] =  CString::format("0x%016I64X", TMPPersistentState.PaintParent);
	retJSONBuffer["LayerId"] = format("{}", TMPPersistentState.LayerId);
	retJSONBuffer["OutgoingLayerId"] = format("{}", TMPPersistentState.OutgoingLayerId);
 
	retJSONBuffer["DesktopGeometry.Size"] = CString::format("%.3f, %.3f",
		TMPPersistentState.DesktopGeometry.Size.x,
		TMPPersistentState.DesktopGeometry.Size.y
	);
	retJSONBuffer["DesktopGeometry.Position"] =  CString::format("%.3f, %.3f",
		TMPPersistentState.DesktopGeometry.Position.x,
		TMPPersistentState.DesktopGeometry.Position.y
	);
	retJSONBuffer["DesktopGeometry.AbsolutePosition"] = CString::format("%.3f, %.3f",
		TMPPersistentState.DesktopGeometry.AbsolutePosition.x,
		TMPPersistentState.DesktopGeometry.AbsolutePosition.y
	);
	retJSONBuffer["DesktopGeometry.Scale"] =  CString::format("%.3f",
		TMPPersistentState.DesktopGeometry.Scale
	);
	 

	return TRUE;
}

BOOL UE4_UI::GetUE4Game$SWidgetControlINFO_STextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	UE4$STextBlock* kObject = (UE4$STextBlock*)_kControlObject;

 
	retJSONBuffer["BoundText"] = UE4::FText_ToString((const FText*)&kObject->BoundText);

	FSlateFontInfo TMPFontBuffer = { NULL };
	if (FALSE == UE4::readMemory(kObject->Font, &TMPFontBuffer, sizeof(FSlateFontInfo)))
		return FALSE;

	retJSONBuffer["FontSize"] = format("{}", TMPFontBuffer.Size);
	retJSONBuffer["FontName"] = UE4::FName_ToString(&TMPFontBuffer.TypefaceFontName);
	retJSONBuffer["FontObject"] =  CString::format("0x%016I64X", TMPFontBuffer.FontObject);
	retJSONBuffer["HighlightText"] = UE4::FText_ToString((const FText*)&kObject->HighlightText);

	FLinearColor TMPColorBuffer;
	if (FALSE == UE4::readMemory(kObject->HighlightColor, &TMPColorBuffer, sizeof(FLinearColor)))
		return FALSE;
	retJSONBuffer["HighlightColor"] =  CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPColorBuffer.R,
		TMPColorBuffer.G,
		TMPColorBuffer.B,
		TMPColorBuffer.A
	);

	if (FALSE == UE4::readMemory(kObject->ColorAndOpacity, &TMPColorBuffer, sizeof(FLinearColor)))
		return FALSE;
	retJSONBuffer["ColorAndOpacity"] =  CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPColorBuffer.R,
		TMPColorBuffer.G,
		TMPColorBuffer.B,
		TMPColorBuffer.A
	);


	if (FALSE == UE4::readMemory(kObject->ShadowColorAndOpacity, &TMPColorBuffer, sizeof(FLinearColor)))
		return FALSE;
	retJSONBuffer["ShadowColorAndOpacity"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPColorBuffer.R,
		TMPColorBuffer.G,
		TMPColorBuffer.B,
		TMPColorBuffer.A
	);

	FVector2D TMPVectorBuffer;
	if (FALSE == UE4::readMemory(kObject->ShadowOffset, &TMPVectorBuffer, sizeof(FVector2D)))
		return FALSE;
	retJSONBuffer["ShadowOffset"] = CString::format("%.3f,%.3f",
		TMPVectorBuffer.x,
		TMPVectorBuffer.y
	);
}

BOOL UE4_UI::GetUE4Game$SWidgetControlINFO_SRichTextBlock(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	UE4$SRichTextBlock* kObject = (UE4$SRichTextBlock*)_kControlObject;


	retJSONBuffer["BoundText"] = UE4::FText_ToString((const FText*)&kObject->BoundText);
	retJSONBuffer["HighlightText"] =  UE4::FText_ToString((const FText*)&kObject->HighlightText);
	return  TRUE;
}
 
BOOL UE4_UI::GetUE4Game$SWidgetControlINFO_SButton(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	UE4$SButton* kObject = (UE4$SButton*)_kControlObject;
	retJSONBuffer["Style"] = CString::format("0x%016I64X", kObject->Style);

	FMargin TMPMarginBuffer;
	if (FALSE == UE4::readMemory(kObject->ContentPadding, &TMPMarginBuffer, sizeof(FMargin)))
		return FALSE;
	retJSONBuffer["ContentPadding"] =  CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPMarginBuffer.Left,
		TMPMarginBuffer.Top,
		TMPMarginBuffer.Right,
		TMPMarginBuffer.Bottom
	);

	if (FALSE == UE4::readMemory(&kObject->BorderPadding, &TMPMarginBuffer, sizeof(FMargin)))
		return FALSE;
	retJSONBuffer["BorderPadding"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPMarginBuffer.Left,
		TMPMarginBuffer.Top,
		TMPMarginBuffer.Right,
		TMPMarginBuffer.Bottom
	);

	if (FALSE == UE4::readMemory(&kObject->PressedBorderPadding, &TMPMarginBuffer, sizeof(FMargin)))
		return FALSE;
	retJSONBuffer["PressedBorderPadding"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		TMPMarginBuffer.Left,
		TMPMarginBuffer.Top,
		TMPMarginBuffer.Right,
		TMPMarginBuffer.Bottom
	);

	FVector2D TMPVectorBuffer;
	if (FALSE == UE4::readMemory(&kObject->PressedScreenSpacePosition, &TMPVectorBuffer, sizeof(FVector2D)))
		return FALSE;
	retJSONBuffer["PressedScreenSpacePosition"] = CString::format("%.3f,%.3f",
		TMPVectorBuffer.x,
		TMPVectorBuffer.y
	);


	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->NormalImage, TMPJsonBuffer)) {
			retJSONBuffer["NormalImage"] = TMPJsonBuffer;

		};
	}
	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->HoverImage, TMPJsonBuffer)) { 
			retJSONBuffer["HoverImage"] = TMPJsonBuffer;
		};
	}
	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->PressedImage, TMPJsonBuffer)) {
			retJSONBuffer["PressedImage"] = TMPJsonBuffer;
		};
	}
	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->DisabledImage, TMPJsonBuffer)) {
			retJSONBuffer["DisabledImage"] = TMPJsonBuffer;
		};
	}

	TBaseDelegate TMPDelegateBuffer;
	if (FALSE == UE4::readMemory(kObject->OnClicked, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;
	retJSONBuffer["OnClicked"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	if (FALSE == UE4::readMemory(kObject->OnPressed, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;
	retJSONBuffer["OnPressed"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	if (FALSE == UE4::readMemory(kObject->OnReleased, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;
	retJSONBuffer["OnReleased"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	if (FALSE == UE4::readMemory(kObject->OnHovered, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;
	retJSONBuffer["OnHovered"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	if (FALSE == UE4::readMemory(kObject->OnUnhovered, &TMPDelegateBuffer, sizeof(_tagTBaseDelegate)))
		return FALSE;
	retJSONBuffer["OnUnhovered"] = CString::format("0x%016I64X, 0x%08X, 0x%08X",
		TMPDelegateBuffer.DelegateAllocator,
		TMPDelegateBuffer.DelegateSize,
		TMPDelegateBuffer.unknown
	);

	retJSONBuffer["ClickMethod"] = format("{}", (int)kObject->ClickMethod);
	retJSONBuffer["TouchMethod"] = format("{}", (int)kObject->TouchMethod);
	retJSONBuffer["PressMethod"] = format("{}", (int)kObject->PressMethod); 

	FSlateSound TMPSlateSoundBuffer;
	if (FALSE == UE4::readMemory(&kObject->HoveredSound, &TMPSlateSoundBuffer, sizeof(FSlateSound)))
		return FALSE;


	UE4$UObjectHEAD TMPHeadBuffer = { NULL };
	if (FALSE == _UE4ObjectISValid(TMPSlateSoundBuffer.ResourceObject, &TMPHeadBuffer)) {
		ZeroMemory(&TMPHeadBuffer, sizeof(UE4$UObjectHEAD));
	}
	retJSONBuffer["HoveredSound"] = CString::format("0x%016I64X, 0x%08X, 0x%08X, %s",
		TMPSlateSoundBuffer.ResourceObject,
		TMPSlateSoundBuffer.LegacyResourceName_DEPRECATED,
		TMPSlateSoundBuffer.LegacyResourceObject_DEPRECATED,
		UE4::FName_ToString(&TMPHeadBuffer.NamePrivate).c_str()
	);

	if (FALSE == UE4::readMemory(&kObject->PressedSound, &TMPSlateSoundBuffer, sizeof(FSlateSound)))
		return FALSE;

	if (FALSE == _UE4ObjectISValid(TMPSlateSoundBuffer.ResourceObject, &TMPHeadBuffer)) {
		ZeroMemory(&TMPHeadBuffer, sizeof(UE4$UObjectHEAD));
	}
	retJSONBuffer["PressedSound"] = CString::format("0x%016I64X, 0x%08X, 0x%08X, %s",
		TMPSlateSoundBuffer.ResourceObject,
		TMPSlateSoundBuffer.LegacyResourceName_DEPRECATED,
		TMPSlateSoundBuffer.LegacyResourceObject_DEPRECATED,
		UE4::FName_ToString(&TMPHeadBuffer.NamePrivate).c_str()
	);

	return TRUE;
}

BOOL UE4_UI::GetUE4Game$SWidgetControlINFO_SImage(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	UE4$SImage* kObject = (UE4$SImage*)_kControlObject;

	retJSONBuffer["bFlipForRightToLeftFlowDirection"] = CString::format("%02X",
		kObject->bFlipForRightToLeftFlowDirection
	);

	uint64_t TMPMouseEvents[4] = { NULL };
	if (TRUE == UE4::readMemory(kObject->OnMouseButtonDownHandler, &TMPMouseEvents, sizeof(uint64_t) * 4)) {
		retJSONBuffer["OnMouseButtonDownHandler"] = CString::format(
			"0x%016I64X, 0x%016I64X, 0x%016I64X, 0x%016I64X",
			TMPMouseEvents[0],
			TMPMouseEvents[1],
			TMPMouseEvents[2],
			TMPMouseEvents[3]
		);
	}

	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->Image.ImageCache, TMPJsonBuffer)) {
			retJSONBuffer["CacheResource"] = TMPJsonBuffer; 
		};
	}

	{
		Json::Value TMPJsonBuffer;
		if (CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)*(void**)kObject->Image.Image, TMPJsonBuffer)) {
			retJSONBuffer["CacheResource"] = TMPJsonBuffer;
		};
	}
	retJSONBuffer["ColorAndOpacity"] = CString::format("%.3f,%.3f,%.3f,%.3f",
		((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.R,
		((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.G,
		((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.B,
		((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.A
	);
	retJSONBuffer["ColorAndOpacity.UseRule"] = CString::format("%016I64X",
		((FSlateColor*)(&kObject->ColorAndOpacity))->ColorUseRule
	);
	return TRUE;
}

BOOL UE4_UI::GetCMD_UE4Game$SWidgetControlINFO_SEditableText(const FSlateBrush* _kControlObject, Json::Value& retJSONBuffer) {
	uint64_t kObject = (uint64_t)_kControlObject;

#pragma region//---------------------------------------------------------------------------------------------SEditableText::SetIsPassword
	//__int64 __fastcall SEditableText::SetIsPassword(__int64 a1, _BYTE *a2)
	//{
	//	signed __int64 v2; // rdi
	//	__int64 v3; // rsi
	//	__int64 v4; // rcx

	//	v2 = (signed __int64)(a2 + 8);
	//	*(_BYTE *)(a1 + 0x3A0) = *a2;
	//	v3 = a1;
	//	*(_BYTE *)(a1 + 0x3A1) = a2[1];
	//	TBaseDelegate<TTypeWrapper<void>, TSharedPtr<FString, 0>, enum  ESelectInfo::Type>::operator=(a1 + 936, a2 + 8);
	//	v4 = *(_QWORD *)(v3 + 680);
	//	*(_BYTE *)(v4 + 16) = *(_BYTE *)(v3 + 928);
	//	*(_BYTE *)(v4 + 17) = *(_BYTE *)(v3 + 929);
	//	TBaseDelegate<TTypeWrapper<void>, TSharedPtr<FString, 0>, enum  ESelectInfo::Type>::operator=(v4 + 24, v3 + 936);
	//	return TBaseDelegate<EVisibility, >::~TBaseDelegate<EVisibility, >(v2);
	//}
	retJSONBuffer["IsPassword"] = CString::format("%02X, %02X",
		*(byte*)(kObject + 0x3A0),
		*(byte*)(kObject + 0x3A1)
	);
#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------SEditableText::SetIsReadOnly
	//__int64 __fastcall SEditableText::SetIsReadOnly(__int64 a1, _BYTE *a2)
	//{
	//	signed __int64 v2; // rbx

	//	v2 = (signed __int64)(a2 + 8);
	//	*(_BYTE *)(a1 + 0x388) = *a2;
	//	*(_BYTE *)(a1 + 0x389) = a2[1];
	//	TBaseDelegate<TTypeWrapper<void>, TSharedPtr<FString, 0>, enum  ESelectInfo::Type>::operator=(a1 + 912, a2 + 8);
	//	return TBaseDelegate<EVisibility, >::~TBaseDelegate<EVisibility, >(v2);
	//}
	retJSONBuffer["IsReadOnly"] = CString::format("%02X, %02X",
		*(byte*)(kObject + 0x388),
		*(byte*)(kObject + 0x389)
	);
#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------SEditableText::SetText
	//void __fastcall SEditableText::SetText(__int64 a1, __int64 a2)
	//{
	//	FSlateEditableTextLayout::SetText(*(FSlateEditableTextLayout **)(a1 + 0x2B8), a2);
	//}

	typedef void       FSlateEditableTextLayout;
	FSlateEditableTextLayout* TMPTextCtrl = NULL;

	if (NULL != (TMPTextCtrl = *(FSlateEditableTextLayout**)(kObject + 0x2B8))) {
		//void __fastcall FSlateEditableTextLayout::SetText(FSlateEditableTextLayout *this, __int64 a2){
		//	if (*((_BYTE *)v3 + 0x548))
		//		v4 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);

		//	FText::operator=((char *)v3 + 0x530, v2);

		//	if (*((_BYTE *)v3 + 0x548))
		//		v6 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);
		//}

		const FText* TMPTextObject = (FText*)((uint64_t)TMPTextCtrl + 0x530);

		if (NULL != TMPTextObject && /*测试一次读取*/TRUE == UE4::readMemory(TMPTextObject, &TMPTextCtrl, sizeof(uint64_t))) {
			retJSONBuffer["text"] = UE4::FText_ToString(TMPTextObject);
		}
	}
#pragma endregion
	return TRUE;
}




// 子控件的数据信息获取, 注: 当前只处理 FSlateBrush    类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_FSlateBrush(const FSlateBrush* _kControlObject, Json::Value args) {
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	FSlateBrush TMPBrushBuffer;
	if (FALSE == UE4::readMemory(_kControlObject, &TMPBrushBuffer, sizeof(FSlateBrush)))
		return FALSE;
	UE4$UObjectHEAD TMPHeadBuffer = { NULL };
	if (FALSE == _UE4ObjectISValid(TMPBrushBuffer.ResourceObject, &TMPHeadBuffer)) 
		return FALSE;

	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		if ((f == "ResourceObject" && (int64)TMPBrushBuffer.ResourceObject != args[f].asInt64())
			|| (f == "ResourceName" && UE4::FName_ToString(&TMPBrushBuffer.ResourceName) != args[f].asString())
			|| (f == "ImageSize" && CString::format("%.3f,%.3f",
				TMPBrushBuffer.ImageSize.x,
				TMPBrushBuffer.ImageSize.y) != args[f].asString())
			|| (f == "ResourceType" && UE4::FName_ToString(
				&TMPHeadBuffer.NamePrivate) != args[f].asString())
			|| (f == "Margin" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPBrushBuffer.Margin.Left,
				TMPBrushBuffer.Margin.Top,
				TMPBrushBuffer.Margin.Right,
				TMPBrushBuffer.Margin.Bottom) != args[f].asString())
			|| (f == "DrawAs" && (int)TMPBrushBuffer.DrawAs != args[f].asInt())
			|| (f == "Tiling" && (int)TMPBrushBuffer.Tiling != args[f].asInt())
			|| (f == "Mirroring" && (int)TMPBrushBuffer.Mirroring != args[f].asInt())
			|| (f == "ImageType" && (int)TMPBrushBuffer.ImageType != args[f].asInt())
			|| (f == "UVRegion.Min" && CString::format("%.3f * %.3f",
				TMPBrushBuffer.UVRegion.Min.x, TMPBrushBuffer.UVRegion.Min.y) != args[f].asString())
			|| (f == "UVRegion.Max" && CString::format("%.3f * %.3f",
				TMPBrushBuffer.UVRegion.Max.x, TMPBrushBuffer.UVRegion.Max.y) != args[f].asString())
			|| (f == "UVRegion.IsValid" && CString::format("%d",
				TMPBrushBuffer.UVRegion.bIsValid) != args[f].asString())
			|| (f == "TintColor" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPBrushBuffer.TintColor.SpecifiedColor.R,
				TMPBrushBuffer.TintColor.SpecifiedColor.G,
				TMPBrushBuffer.TintColor.SpecifiedColor.B,
				TMPBrushBuffer.TintColor.SpecifiedColor.A) != args[f].asString())
			|| (f == "TintColor.UseRule" && CString::format("%016I64X",
				TMPBrushBuffer.TintColor.ColorUseRule) != args[f].asString())
			) {
			allHit = FALSE;
			break;
		}

	}
	return allHit;
	  
}


// 子控件的数据信息获取, 注: 当前只处理 SWidget     类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_SWidget(const SWidget* _kControlObject, Json::Value args) {
	UE4$SWidget* kObject = (UE4$SWidget*)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	UE4$FSlateWidgetPersistentState  TMPPersistentState = { NULL };
	if (FALSE == UE4::readMemory(&kObject->PersistentState, &TMPPersistentState, sizeof(UE4$FSlateWidgetPersistentState)))
		return FALSE;
  
	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		
		if ((f == "Tag" && UE4::FName_ToString(&kObject->Tag) != args[f].asString())
			|| (f == "EnabledState" && (int)kObject->EnabledState[0] != args[f].asInt())
			|| (f == "Visibility" && (int)kObject->Visibility[0] != args[f].asInt()) 
			|| (f == "PaintParent" && (uint64)TMPPersistentState.PaintParent != args[f].asInt64())
			|| (f == "LayerId" && (int)TMPPersistentState.LayerId != args[f].asInt())
			|| (f == "OutgoingLayerId" && (int)TMPPersistentState.OutgoingLayerId != args[f].asInt())
			|| (f == "DesktopGeometry.Size" && CString::format("%.3f, %.3f",
				TMPPersistentState.DesktopGeometry.Size.x,
				TMPPersistentState.DesktopGeometry.Size.y) != args[f].asString())
			|| (f == "DesktopGeometry.Position" && CString::format("%.3f, %.3f",
				TMPPersistentState.DesktopGeometry.Position.x,
				TMPPersistentState.DesktopGeometry.Position.y) != args[f].asString())
			|| (f == "DesktopGeometry.AbsolutePosition" && CString::format("%.3f, %.3f",
				TMPPersistentState.DesktopGeometry.AbsolutePosition.x,
				TMPPersistentState.DesktopGeometry.AbsolutePosition.y) != args[f].asString())
			|| (f == "DesktopGeometry.Scale" && CString::format("%.3f",
				TMPPersistentState.DesktopGeometry.Scale) != args[f].asString())
			){
			allHit = FALSE;
			break;
		}  
	} 
	return allHit;
}

// 子控件的数据信息获取, 注: 当前只处理 STextBlock 类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_STextBlock(const SWidget* _kControlObject, Json::Value args) {


	UE4$STextBlock* kObject = (UE4$STextBlock*)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	FSlateFontInfo TMPFontBuffer = { NULL };
	if (FALSE == UE4::readMemory(kObject->Font, &TMPFontBuffer, sizeof(FSlateFontInfo)))
		return FALSE;

	FLinearColor TMPHighlightColor;
	if (FALSE == UE4::readMemory(kObject->HighlightColor, &TMPHighlightColor, sizeof(FLinearColor)))
		return FALSE;

	FLinearColor TMPColorAndOpacity;
	if (FALSE == UE4::readMemory(kObject->ColorAndOpacity, &TMPColorAndOpacity, sizeof(FLinearColor)))
		return FALSE;

	FLinearColor TMPShadowColorAndOpacity;
	if (FALSE == UE4::readMemory(kObject->ShadowColorAndOpacity, &TMPShadowColorAndOpacity, sizeof(FLinearColor)))
		return FALSE;

	FVector2D TMPVectorBuffer;
	if (FALSE == UE4::readMemory(kObject->ShadowOffset, &TMPVectorBuffer, sizeof(FVector2D)))
		return FALSE;

	OutputDebugStringA(format("※※CMD_UE4Game$SWidgetControlINFO_STextBlock. {}", UE4::FText_ToString((const FText*)&kObject->BoundText)).c_str());
	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		if ((f == "BoundText" && UE4::FText_ToString((const FText*)&kObject->BoundText) != args[f].asString())
			|| (f == "FontSize" && TMPFontBuffer.Size != args[f].asInt())
			|| (f == "FontName" && UE4::FName_ToString(&TMPFontBuffer.TypefaceFontName) != args[f].asString())
			|| (f == "FontObject" && (int64)TMPFontBuffer.FontObject != args[f].asInt64())
			|| (f == "HighlightText" && UE4::FText_ToString((const FText*)&kObject->HighlightText) != args[f].asString())
			|| (f == "HighlightColor" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPHighlightColor.R,
				TMPHighlightColor.G,
				TMPHighlightColor.B,
				TMPHighlightColor.A) != args[f].asString())
			|| (f == "ColorAndOpacity" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPColorAndOpacity.R,
				TMPColorAndOpacity.G,
				TMPColorAndOpacity.B,
				TMPColorAndOpacity.A) != args[f].asString())
			|| (f == "ShadowColorAndOpacity" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPShadowColorAndOpacity.R,
				TMPShadowColorAndOpacity.G,
				TMPShadowColorAndOpacity.B,
				TMPShadowColorAndOpacity.A) != args[f].asString())
			|| (f == "ShadowOffset" && CString::format("%.3f,%.3f",
				TMPVectorBuffer.x,
				TMPVectorBuffer.y) != args[f].asString())

			) {
			allHit = FALSE;
			break;
		}

	}
	return allHit;
}

// 子控件的数据信息获取, 注: 当前只处理 SRichTextBlock 类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_SRichTextBlock(const SWidget* _kControlObject, Json::Value args) {
	UE4$SRichTextBlock* kObject = (UE4$SRichTextBlock*)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		if ((f == "BoundText" && UE4::FText_ToString((const FText*)&kObject->BoundText) != args[f].asString())
			|| (f == "HighlightText" && UE4::FText_ToString((const FText*)&kObject->HighlightText) != args[f].asString())
			) {
			allHit = FALSE;
			break;
		}

	}
	return allHit; 
}


// 子控件的数据信息获取, 注: 当前只处理 SButton    类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_SButton(const SWidget* _kControlObject, Json::Value args) {
	UE4$SButton* kObject = (UE4$SButton*)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	FMargin TMPContentPadding;
	if (FALSE == UE4::readMemory(kObject->ContentPadding, &TMPContentPadding, sizeof(FMargin)))
		return NULL;
	FMargin TMPBorderPadding;
	if (FALSE == UE4::readMemory(&kObject->BorderPadding, &TMPBorderPadding, sizeof(FMargin)))
		return NULL;
	FMargin TMPPressedBorderPadding;
	if (FALSE == UE4::readMemory(&kObject->PressedBorderPadding, &TMPPressedBorderPadding, sizeof(FMargin)))
		return NULL;
	FVector2D TMPVectorBuffer;
	if (FALSE == UE4::readMemory(&kObject->PressedScreenSpacePosition, &TMPVectorBuffer, sizeof(FVector2D)))
		return NULL;

	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		if ((f == "Style" && kObject->Style != args[f].asUInt64())
			|| (f == "ContentPadding" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPContentPadding.Left,
				TMPContentPadding.Top,
				TMPContentPadding.Right,
				TMPContentPadding.Bottom) != args[f].asString())
			|| (f == "BorderPadding" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPBorderPadding.Left,
				TMPBorderPadding.Top,
				TMPBorderPadding.Right,
				TMPBorderPadding.Bottom) != args[f].asString())
			|| (f == "PressedBorderPadding" && CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPPressedBorderPadding.Left,
				TMPPressedBorderPadding.Top,
				TMPPressedBorderPadding.Right,
				TMPPressedBorderPadding.Bottom) != args[f].asString())
			|| (f == "PressedScreenSpacePosition" && CString::format("%.3f,%.3f",
				TMPVectorBuffer.x,
				TMPVectorBuffer.y) != args[f].asString())
			
			|| (f == "NormalImage" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->NormalImage, args[f]))
			|| (f == "HoverImage" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->HoverImage, args[f]))
			|| (f == "PressedImage" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->PressedImage, args[f]))
			|| (f == "DisabledImage" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->DisabledImage, args[f]))
			|| (f == "ClickMethod" && (int)kObject->ClickMethod != args[f].asInt())
			|| (f == "TouchMethod" && (int)kObject->TouchMethod != args[f].asInt())
			|| (f == "PressMethod" && (int)kObject->PressMethod != args[f].asInt())
			 
			) {
			allHit = FALSE;
			break;
		}

	}

	return allHit;
     
}

// 子控件的数据信息获取, 注: 当前只处理 SImage     类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_SImage(const SWidget* _kControlObject, Json::Value args) {
	UE4$SImage* kObject = (UE4$SImage*)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();

	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;
		if ((f == "bFlipForRightToLeftFlowDirection" && (int)kObject->OnMouseButtonDownHandler != args[f].asInt())
			|| (f == "CacheResource" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->Image.ImageCache, args[f]))
			|| (f == "Resource" && !CMD_UE4Game$SWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->Image.Image, args[f]))
			|| (f == "ColorAndOpacity.UseRule" && (int64)((FSlateColor*)(&kObject->ColorAndOpacity))->ColorUseRule != args[f].asInt64())
			|| (f == "ColorAndOpacity" && CString::format("%.3f,%.3f,%.3f,%.3f",
				((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.R,
				((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.G,
				((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.B,
				((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.A) != args[f].asString())
			)
		{
			allHit = FALSE;
			break;
		}

	}
	return allHit;
  
}

// 子控件的数据信息获取, 注: 当前只处理 SEditableText  类型
BOOL UE4_UI::CMD_UE4Game$SWidgetControlINFO_SEditableText(const SWidget* _kControlObject, Json::Value args) {
	uint64_t kObject = (uint64_t)_kControlObject;
	BOOL allHit = TRUE; //所有属性匹配
	Json::Value::Members fields = args.getMemberNames();


	typedef void       FSlateEditableTextLayout;
	FSlateEditableTextLayout* TMPTextCtrl = NULL;

	if (NULL == (TMPTextCtrl = *(FSlateEditableTextLayout**)(kObject + 0x2B8))) {
		//void __fastcall FSlateEditableTextLayout::SetText(FSlateEditableTextLayout *this, __int64 a2){
		//	if (*((_BYTE *)v3 + 0x548))
		//		v4 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);

		//	FText::operator=((char *)v3 + 0x530, v2);

		//	if (*((_BYTE *)v3 + 0x548))
		//		v6 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);
		//} 
		return FALSE;
	}
	const FText* TMPTextObject = (FText*)((uint64_t)TMPTextCtrl + 0x530);

	if (FALSE == UE4::readMemory(TMPTextObject, &TMPTextCtrl, sizeof(uint64_t)))
		return FALSE;
	for (auto& f : fields) { //遍历属性  忽略对象类型和子对象列表
		if (f == UI_OBJECT) continue;
		if (f == UI_CHILE) continue;

		if ((f == "IsPassword" && CString::format("%02X, %02X",
			*(BYTE*)(kObject + 0x3A0),
			*(BYTE*)(kObject + 0x3A1)) != args[f].asString())

			|| (f == "IsReadOnly" && CString::format("%02X, %02X",
				*(BYTE*)(kObject + 0x388),
				*(BYTE*)(kObject + 0x389)) != args[f].asString())

			|| (f == "text" && UE4::FText_ToString(TMPTextObject) != args[f].asString())

			)
		{
			allHit = FALSE;
			break;
		}

	}
	 
	return allHit;

}
 
// 子控件的遍历过程, 基于 SWidget::Prepass_Internal 逆向!!
PVOID UE4_UI::CMD_UE4Game$SWidgetControlINFO_Prepass_Internal(const SWidget* _kObject, std::function<PVOID(const SWidget* _kObject, int kIndex)> EnmuCallback) {
	//void SWidget::Prepass_Internal(float InLayoutScaleMultiplier)
	//{
	//	PrepassLayoutScaleMultiplier = InLayoutScaleMultiplier;
	//
	//	bool bShouldPrepassChildren = true;
	//	if (bHasCustomPrepass)
	//	{
	//		bShouldPrepassChildren = CustomPrepass(InLayoutScaleMultiplier);
	//	}
	//
	//	if (bCanHaveChildren && bShouldPrepassChildren)
	//	{
	//		// Cache child desired sizes first. This widget's desired size is
	//		// a function of its children's sizes.
	//		FChildren* MyChildren = this->GetChildren();
	//		const int32 NumChildren = MyChildren->Num();
	//		for (int32 ChildIndex = 0; ChildIndex < MyChildren->Num(); ++ChildIndex)
	//		{
	//			const TSharedRef<SWidget>& Child = MyChildren->GetChildAt(ChildIndex);
	//
	//			if (Child->Visibility.Get() != EVisibility::Collapsed)
	//			{
	//				const float ChildLayoutScaleMultiplier = GetRelativeLayoutScale(MyChildren->GetSlotAt(ChildIndex), InLayoutScaleMultiplier);
	//				// Recur: Descend down the widget tree.
	//				Child->Prepass_Internal(InLayoutScaleMultiplier * ChildLayoutScaleMultiplier);
	//			}
	//		}
	//		ensure(NumChildren == MyChildren->Num());
	//	}
	//
	//	{
	//		// Cache this widget's desired size.
	//		CacheDesiredSize(PrepassLayoutScaleMultiplier.Get(1.0f));
	//		bNeedsPrepass = false;
	//	}
	//}

	do
	{
		//__int64 v6 = ((__int64(__fastcall *)(SWidget *))v4->vfptr[48].__vecDelDtor)(v4);

		uint64_t TMPVfptr = NULL;
		if (FALSE == UE4::readMemory(_kObject, &TMPVfptr, sizeof(uint64_t))) {
			break;
		}

		TMPVfptr += (sizeof(void*) * 48);

		uint64_t(*SWidget$GetChildren)(const SWidget*) = NULL;
		if (FALSE == UE4::readMemory((void*)TMPVfptr, &SWidget$GetChildren, sizeof(void*)))
			break;

		uint64_t v6 = NULL;
		if (NULL == (v6 = SWidget$GetChildren(_kObject)))
			break;

		// while ( (signed int)v7 /* for 的 递增值 */ < (**(signed int (__fastcall ***)(__int64))v6)(v6) );
		signed int NumChildren = (**(signed int(__fastcall***)(uint64_t))v6)(v6);
		OutputDebugStringA(format("※※ v6:{},NumChildren:{},_kObject:{}",v6, NumChildren, _kObject).c_str());
		for (uint32_t kIndex = 0; kIndex < NumChildren; kIndex++) {
			uint32_t v7 = kIndex;

			// const TSharedRef<SWidget>& Child = MyChildren->GetChildAt(ChildIndex);
			//(*(void(__fastcall **)(__int64, SWidget **, _QWORD))(*(_QWORD *)v6 + 16i64))(v6, &v16, v7);
			//v8 = v16;

			SWidget* v16[2] = { NULL };
			(*(void(__fastcall**)(uint64_t, SWidget**, uint64_t))(*(uint64_t*)v6 + 16i64))(v6, &v16[0], v7);
			if (NULL == v16[0]) break;
			OutputDebugStringA(format("※※ v16:{},v7:{},_kObject:{}", v16[0], v7, _kObject).c_str());
			//传入回调函数
			PVOID result = EnmuCallback(v16[0], kIndex);
			if (result != NULL)
				return result;
		}
	} while (false);
	OutputDebugStringA(format("※※子控件的遍历过程, 基于 SWidget::Prepass_Internal 逆向!!.NULL,{}", _kObject).c_str());
	return NULL;
}

// 子控件的数据信息获取, 以及, 子控件的递归处理
PVOID UE4_UI::CMD_UE4Game$SWidgetControlINFO(const SWidget* _kControlObject, string type, Json::Value args, BOOL EnumChild,int level) {
	UE4$SWidget* kObject = (UE4$SWidget*)_kControlObject;
	OutputDebugStringA(format("※※开始枚举子控件.{} - {}", type, level).c_str());
	//获取控件的所有基础数据信息
	std::string TMPTypeString = UE4::FName_ToString(&kObject->TypeOfWidget);

	if (type == TMPTypeString) { 
		if (TRUE == CMD_UE4Game$SWidgetControlINFO_SWidget(_kControlObject, args))
		{
			//各类型子控件的处理流程
			if ("STextBlock" == TMPTypeString && TRUE == CMD_UE4Game$SWidgetControlINFO_STextBlock(_kControlObject, args)
				|| ("SEditableText" == TMPTypeString && TRUE == CMD_UE4Game$SWidgetControlINFO_SEditableText(_kControlObject, args))
				|| ("SRichTextBlock" == TMPTypeString && TRUE == CMD_UE4Game$SWidgetControlINFO_SRichTextBlock(_kControlObject, args)) 
				|| ("SImage" == TMPTypeString && TRUE == CMD_UE4Game$SWidgetControlINFO_SImage(_kControlObject, args)) 
				|| ("SLHEditableText" == TMPTypeString && TRUE == CMD_UE4Game$SWidgetControlINFO_SEditableText(_kControlObject, args))
				|| ("SLHButton" == TMPTypeString && NULL != CMD_UE4Game$SWidgetControlINFO_SButton(_kControlObject, args))
				|| ("SButton" == TMPTypeString && NULL != CMD_UE4Game$SWidgetControlINFO_SButton(_kControlObject, args))
				) { 
				return (PVOID)_kControlObject;
			}  
		} 
	}
	 
	if (FALSE == EnumChild) {
		OutputDebugStringA(format("※※不枚举子控件.{}", type).c_str());
		return NULL;
	}

	//遍历, 所有的子控件 
	return CMD_UE4Game$SWidgetControlINFO_Prepass_Internal(_kControlObject, [type, args, level](const SWidget* _kObject, int kIndex) {
			return  CMD_UE4Game$SWidgetControlINFO(_kObject, type, args, TRUE, level+1);
		});
	OutputDebugStringA(format("※※子控件枚举完毕退出.{}", type).c_str());
	return NULL;
}
 
// 主窗口的遍历过程, 基于 PrepassWindowAndChildren 逆向!!
PVOID UE4_UI::CMD_UE4Game$SlateWinodwINFO(const SWindow* _SlateWinodwObject, string type, Json::Value args) { 

	if (FALSE == UE4::enterVFTable((SWindow*)_SlateWinodwObject)) {
		OutputDebugStringA(format("※※CMD_UE4Game$SlateWinodwINFO.Err 1").c_str());
		return NULL;
	}


	CSlateWinodw _SWindowBuffer(_SlateWinodwObject);

	if (!_SWindowBuffer.IsVisible() || _SWindowBuffer.IsMinimized()) {
		OutputDebugStringA(format("※※CMD_UE4Game$SlateWinodwINFO.Err 2").c_str());
		return NULL; //如果不可视或者最小化则不参与遍历
	}
	//if (!_SWindowBuffer.Enable()) {
	//	OutputDebugStringA(format("※※CMD_UE4Game$SlateWinodwINFO.Err 3").c_str());
	//	return NULL;
	//}
  
	//遍历, 所有的子控件 
	return CMD_UE4Game$SWidgetControlINFO_Prepass_Internal(_SlateWinodwObject, [&type, &args](const SWidget* _kObject, int kIndex) {
		   
			return CMD_UE4Game$SWidgetControlINFO(_kObject, type, args, TRUE,0);
		});
	OutputDebugStringA(format(" 基于 PrepassWindowAndChildren 逆向!!").c_str());
	return NULL;
}

// 主窗口的遍历过程, 基于 PrepassWindowAndChildren 逆向!!
PVOID UE4_UI::CMD_UE4Game$GetSlateWindowLIST(std::function<PVOID(void*)> enumCallback) {
	const FSlateApplication* TMPFSlateApplication = NULL;
	if (NULL == (TMPFSlateApplication = _2UE4FSlateApplication())) { 
		OutputDebugStringA(format("※※CMD_UE4Game$GetSlateWindowLIST.Err 1").c_str());
		return NULL;
	}
	UE4$FArray SlateWindowsLIST = { NULL };
	if (FALSE == UE4::readMemory(_2UObjectPointer(TMPFSlateApplication, UE4$FSlateApplication$SlateWindows), &SlateWindowsLIST, sizeof(UE4$FArray))) { 
		OutputDebugStringA(format("※※CMD_UE4Game$GetSlateWindowLIST.Err 2").c_str());
		return NULL;
	}
	if (SlateWindowsLIST._count > SlateWindowsLIST._max || 0 == SlateWindowsLIST._count) { 
		OutputDebugStringA(format("※※CMD_UE4Game$GetSlateWindowLIST.Err 3").c_str());
		return NULL;
	};

	

	for (uint32_t kIndex = 0; kIndex < SlateWindowsLIST._count; kIndex++) {
		OutputDebugStringA(format("※※CMD_UE4Game$GetSlateWindowLIST.for {}", kIndex).c_str());
		uint64_t TMPValue = NULL;
		if (NULL == (TMPValue = (uint64_t)SlateWindowsLIST.objects))
			continue;

		TMPValue += (sizeof(void*) * 2 * kIndex);

		JSONBuffer _JsonBuffer;
		 
		void* TMPValue_object = ((void**)TMPValue)[0];
		void* TMPValue_unknown = ((void**)TMPValue)[1];

		PVOID result = enumCallback(TMPValue_object);
		if (NULL != result) {
			return result;
		}
	}

	OutputDebugStringA(format("※※CMD_UE4Game$GetSlateWindowLIST.return NULL").c_str());
	return NULL;
}
 

/*

{
	SWidgetObject : "SConstraintCanvas",
	EnabledState : 1,
	SChildObject : {
		SWidgetObject : "SImage",
		Resource : {
			ResourceType : "Bg_Instantmessage"
		}
	}
}


*/


PVOID UE4_UI::findControl(string type, Json::Value args)
{
	if (type != "STextBlock"
		&& type != "SEditableText"
		&& type != "SRichTextBlock"
		&& type != "SButton"
		&& type != "SImage"
		&& type != "SLHButton"
		&& type != "SLHEditableText"
		)
	{
		OutputDebugStringA(format("※※无符合的控件类型.{}",type).c_str());
		return NULL;
	}
		

	if (args.isNull()) {
		OutputDebugStringA(format("※※参数为空").c_str());
		return NULL;
	}

	return CMD_UE4Game$GetSlateWindowLIST([&type, &args] (void* a1) {
		return  CMD_UE4Game$SlateWinodwINFO((const SWindow*)a1, type, args);
		});
}

string UE4_UI::getControlProperty(PVOID pControl, string cType, string pName)
{
	{
		UE4$SWidget* kObject = (UE4$SWidget*)pControl;
		if (pName == "Tag") return UE4::FName_ToString(&kObject->Tag);
		if (pName == "EnabledState") return format("{}", (int)kObject->EnabledState[0]);
		if (pName == "Visibility") return format("{}", (int)kObject->Visibility[0]);

		if (pName == "PaintParent"
			|| pName == "LayerId"
			|| pName == "OutgoingLayerId"
			|| pName == "DesktopGeometry.Size"
			|| pName == "DesktopGeometry.Position"
			|| pName == "DesktopGeometry.AbsolutePosition"
			|| pName == "DesktopGeometry.Scale"
			)
		{
			UE4$FSlateWidgetPersistentState  TMPPersistentState = { NULL };
			if (FALSE == UE4::readMemory(&kObject->PersistentState, &TMPPersistentState, sizeof(UE4$FSlateWidgetPersistentState)))
				return "";

			if (pName == "PaintParent") return format("{}", (uint64)TMPPersistentState.PaintParent);
			if (pName == "LayerId") return format("{}", (int)TMPPersistentState.LayerId);
			if (pName == "OutgoingLayerId") return format("{}", (int)TMPPersistentState.OutgoingLayerId);
			if (pName == "DesktopGeometry.Size") return format("{:.3f},{:.3f}", TMPPersistentState.DesktopGeometry.Size.x,
				TMPPersistentState.DesktopGeometry.Size.y);
			if (pName == "DesktopGeometry.Position") return format("{:.3f},{:.3f}", TMPPersistentState.DesktopGeometry.Position.x,
				TMPPersistentState.DesktopGeometry.Position.y);
			if (pName == "DesktopGeometry.AbsolutePosition") return format("{:.3f},{:.3f}", TMPPersistentState.DesktopGeometry.AbsolutePosition.x,
				TMPPersistentState.DesktopGeometry.AbsolutePosition.y);
			if (pName == "DesktopGeometry.Scale") return format("{:.3f}", TMPPersistentState.DesktopGeometry.Scale);
		}
	}
	 
	if ("STextBlock" == cType) {
		UE4$STextBlock* STextBlockObject = (UE4$STextBlock*)pControl;
		if (pName == "BoundText") {
			return UE4::FText_ToString((const FText*)&STextBlockObject->BoundText);
		}  
		if (pName == "HighlightText") {
			return UE4::FText_ToString((const FText*)&STextBlockObject->HighlightText);
		}

 
		if (pName == "FontSize" || pName == "FontName" || pName == "FontObject") {
			FSlateFontInfo TMPFontBuffer = { NULL };
			if (FALSE == UE4::readMemory(STextBlockObject->Font, &TMPFontBuffer, sizeof(FSlateFontInfo)))
				return "";
			if (pName == "FontSize") {
				return  format("{}", TMPFontBuffer.Size);
			}
			if (pName == "FontName") {
				return UE4::FName_ToString(&TMPFontBuffer.TypefaceFontName);
			}
			if (pName == "FontObject") {
				return  format("{}", (int64)TMPFontBuffer.FontObject);
			} 
		}
		if (pName == "HighlightColor") {
			FLinearColor TMPHighlightColor;
			if (FALSE == UE4::readMemory(STextBlockObject->HighlightColor, &TMPHighlightColor, sizeof(FLinearColor)))
				return "";
			return CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPHighlightColor.R,
				TMPHighlightColor.G,
				TMPHighlightColor.B,
				TMPHighlightColor.A);
		}
		if (pName == "ColorAndOpacity") {
			FLinearColor TMPColorAndOpacity;
			if (FALSE == UE4::readMemory(STextBlockObject->ColorAndOpacity, &TMPColorAndOpacity, sizeof(FLinearColor)))
				return "";
			return CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPColorAndOpacity.R,
				TMPColorAndOpacity.G,
				TMPColorAndOpacity.B,
				TMPColorAndOpacity.A);
		}
		if (pName == "ShadowColorAndOpacity") {
			FLinearColor TMPShadowColorAndOpacity;
			if (FALSE == UE4::readMemory(STextBlockObject->ShadowColorAndOpacity, &TMPShadowColorAndOpacity, sizeof(FLinearColor)))
				return "";
			return CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPShadowColorAndOpacity.R,
				TMPShadowColorAndOpacity.G,
				TMPShadowColorAndOpacity.B,
				TMPShadowColorAndOpacity.A);
		}
		if (pName == "ShadowOffset") {
			FVector2D TMPVectorBuffer;
			if (FALSE == UE4::readMemory(STextBlockObject->ShadowOffset, &TMPVectorBuffer, sizeof(FVector2D)))
				return "";
			return CString::format("%.3f,%.3f",
				TMPVectorBuffer.x,
				TMPVectorBuffer.y);
		}



		return "";
	}
	 
	if ("SEditableText" == cType || "SLHEditableText" == cType) {
		uint64_t kObject = (uint64_t)pControl;
		if (pName == "IsPassword") return CString::format("%02X, %02X",
			*(BYTE*)(kObject + 0x3A0),
			*(BYTE*)(kObject + 0x3A1));

		if (pName == "IsReadOnly") return CString::format("%02X, %02X",
			*(BYTE*)(kObject + 0x388),
			*(BYTE*)(kObject + 0x389));

		//if (pName == "text") return CString::format("%02X, %02X",
		//	*(BYTE*)(kObject + 0x388),
		//	*(BYTE*)(kObject + 0x389));
		if (pName == "text") {
			typedef void       FSlateEditableTextLayout;
			FSlateEditableTextLayout* TMPTextCtrl = NULL;

			if (NULL == (TMPTextCtrl = *(FSlateEditableTextLayout**)(kObject + 0x2B8))) {
				//void __fastcall FSlateEditableTextLayout::SetText(FSlateEditableTextLayout *this, __int64 a2){
				//	if (*((_BYTE *)v3 + 0x548))
				//		v4 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);

				//	FText::operator=((char *)v3 + 0x530, v2);

				//	if (*((_BYTE *)v3 + 0x548))
				//		v6 = (const struct FText *)TAttribute<FText>::Get((__int64)v3 + 0x530);
				//} 
				return "";
			}
			const FText* TMPTextObject = (FText*)((uint64_t)TMPTextCtrl + 0x530);
			return UE4::FText_ToString(TMPTextObject);
		}

		return "";
	}
	if ("SRichTextBlock" == cType) {
		UE4$SRichTextBlock* kObject = (UE4$SRichTextBlock*)pControl;
		if (pName == "BoundText") return UE4::FText_ToString((const FText*)&kObject->BoundText);
		if (pName == "HighlightText") return UE4::FText_ToString((const FText*)&kObject->HighlightText);
		 
		return "";
	}
	if ("SImage" == cType) {
		UE4$SImage* kObject = (UE4$SImage*)pControl; 
		if (pName == "bFlipForRightToLeftFlowDirection") return format("{}", (int)kObject->OnMouseButtonDownHandler) ;
		if (pName == "ColorAndOpacity.UseRule") return format("{}", (int64)((FSlateColor*)(&kObject->ColorAndOpacity))->ColorUseRule);
		if (pName == "ColorAndOpacity") return CString::format("%.3f,%.3f,%.3f,%.3f",
			((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.R,
			((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.G,
			((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.B,
			((FSlateColor*)(&kObject->ColorAndOpacity))->SpecifiedColor.A);

		if (pName == "CacheResource") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->Image.ImageCache, cr); 
			return cr.toStyledString();
		}

		if (pName == "Resource") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->Image.Image, cr);
			return cr.toStyledString();
		}
	}
 
	if ("SLHButton" == cType || "SButton" == cType) {
		UE4$SButton* kObject = (UE4$SButton*)pControl;
		if (pName == "Style") return format("{}", kObject->Style);
		if (pName == "ContentPadding") {
			FMargin TMPContentPadding;
			if (FALSE == UE4::readMemory(kObject->ContentPadding, &TMPContentPadding, sizeof(FMargin))) return "";
			return  CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPContentPadding.Left,
				TMPContentPadding.Top,
				TMPContentPadding.Right,
				TMPContentPadding.Bottom);
		}
		if (pName == "BorderPadding") {
			FMargin TMPBorderPadding;
			if (FALSE == UE4::readMemory(&kObject->BorderPadding, &TMPBorderPadding, sizeof(FMargin))) return "";
			return  CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPBorderPadding.Left,
				TMPBorderPadding.Top,
				TMPBorderPadding.Right,
				TMPBorderPadding.Bottom);
		}
		if (pName == "PressedBorderPadding") {
			FMargin TMPPressedBorderPadding;
			if (FALSE == UE4::readMemory(&kObject->PressedBorderPadding, &TMPPressedBorderPadding, sizeof(FMargin))) return "";
			return  CString::format("%.3f,%.3f,%.3f,%.3f",
				TMPPressedBorderPadding.Left,
				TMPPressedBorderPadding.Top,
				TMPPressedBorderPadding.Right,
				TMPPressedBorderPadding.Bottom);
		}
		if (pName == "ClickMethod") return format("{}", (int)kObject->ClickMethod);
		if (pName == "TouchMethod") return format("{}", (int)kObject->TouchMethod);
		if (pName == "PressMethod") return format("{}", (int)kObject->PressMethod);
   
		if (pName == "NormalImage") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->NormalImage, cr);
			return cr.toStyledString();
		}
		if (pName == "HoverImage") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->HoverImage, cr);
			return cr.toStyledString();
		}
		if (pName == "PressedImage") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->PressedImage, cr);
			return cr.toStyledString();
		} 
		if (pName == "DisabledImage") {
			Json::Value cr = Json::Value::null;
			GetSWidgetControlINFO_FSlateBrush((const FSlateBrush*)kObject->DisabledImage, cr);
			return cr.toStyledString();
		}
  
	}
  
	return string("");
}

string UE4_UI::getControlFullProperty(PVOID pControl, string cType)
{
	if (cType != "STextBlock"
		&& cType != "SEditableText"
		&& cType != "SRichTextBlock"
		&& cType != "SButton"
		&& cType != "SImage"
		&& cType != "SLHButton"
		&& cType != "SLHEditableText"
		)
	{
		OutputDebugStringA(format("※※无符合的控件类型.{}", cType).c_str());
		return "";
	}

	Json::Value rs;

	GetUE4Game$SWidgetControlINFO_SWidget((const FSlateBrush*)pControl, rs);

	if (cType == "STextBlock")
		GetUE4Game$SWidgetControlINFO_STextBlock((const FSlateBrush*)pControl, rs);
	else if (cType == "SEditableText" || cType == "SLHEditableText")
		GetCMD_UE4Game$SWidgetControlINFO_SEditableText((const FSlateBrush*)pControl, rs);
	else if (cType == "SRichTextBlock")
		GetUE4Game$SWidgetControlINFO_SRichTextBlock((const FSlateBrush*)pControl, rs);
	else if (cType == "SImage")
		GetUE4Game$SWidgetControlINFO_SImage((const FSlateBrush*)pControl, rs);
	else if (cType == "SLHButton" || cType == "SButton")
		GetUE4Game$SWidgetControlINFO_SButton((const FSlateBrush*)pControl, rs);
  

	return rs.toStyledString();
}
