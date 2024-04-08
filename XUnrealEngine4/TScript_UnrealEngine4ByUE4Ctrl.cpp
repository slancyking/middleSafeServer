#pragma once
//
#include "TScript_UnrealEngine4.h"

float UProgressBar_getPercent(const UObject * _UProgressBar) {
	static long long _ivar_offset = -1;
	if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/UMG", "ProgressBar", "Percent");
	if (-1 == _ivar_offset) return 0.0f;


	float rValueBuffer = 0.0f;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UProgressBar, _ivar_offset),
									&rValueBuffer, sizeof(float)))
		return 0.0f;

	return rValueBuffer;
}

std::string UTextBlock_getTEXT(const UObject * _UTextBlock) {
	static long long _ivar_offset = -1;
	if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/UMG", "TextBlock", "Text");
	if (-1 == _ivar_offset) return "";

	return UE4::FText_ToString(_2UObjectPointer(_UTextBlock, _ivar_offset));
}


std::string UImage_getResourceName(const UObject * _UImageCtrl) {
	static long long _ivar_offset = -1;
	if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/UMG", "Image", "Brush");
	if (-1 == _ivar_offset) return "";

	_tagSlateBrush TMPBrushBuffer;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UImageCtrl, _ivar_offset),
										&TMPBrushBuffer, sizeof(_tagSlateBrush)))
		return "";

	return UE4::FName_ToString(&TMPBrushBuffer.ResourceName);
}


std::string UButton_getResourceName(const UObject * _UButtonCtrl) {
	static long long _ivar_offset = -1;
	if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/UMG", "Button", "WidgetStyle");
	if (-1 == _ivar_offset) return "";

	FButtonStyle TMPButtonStyleBuffer;
	if (FALSE == UE4::readMemory(_2UObjectPointer(_UButtonCtrl, _ivar_offset),
							&TMPButtonStyleBuffer, sizeof(FButtonStyle)))
		return "";

	return UE4::FName_ToString(&TMPButtonStyleBuffer.Normal.ResourceName);
}


std::string URichTextBlock_getTEXT(const UObject * _UTextBlock) {
	static long long _ivar_offset = -1;
	if (-1 == _ivar_offset) _ivar_offset = _2UE4IvarOffset("/Script/UMG", "RichTextBlock", "Text");
	if (-1 == _ivar_offset) return "";

	return UE4::FText_ToString(_2UObjectPointer(_UTextBlock, _ivar_offset));
}



//  ---------------------------------------------------------------------------------------------------------------------------------------以下, 针对游戏的处理过程






























































