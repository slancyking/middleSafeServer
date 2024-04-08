#pragma once
//
#include "TScript_UnrealEngine4.h"




//void AHUD::DrawRect(float  ScreenH, float  ScreenW, float  ScreenY, float  ScreenX, Struct  RectColor)  // \ 
void AHUD_DrawRect(const UObject * _AHUD,  float  ScreenX, float  ScreenY, float  ScreenW, float  ScreenH, FLinearColor  RectColor) {
#define _CALL_INPACKAGE    "/Script/Engine"
#define _CALL_INCLASS      "HUD"
#define _CALL_UFUNCTION    "DrawRect"

	static UE4$UFunction * _CALLUFunction = NULL;
	if (NULL == _CALLUFunction && NULL == (_CALLUFunction = UE4::findUFunction(_CALL_INPACKAGE,
															_CALL_INCLASS, _CALL_UFUNCTION))) {
		return ;
	}

	struct _tag$DrawRect{
		FLinearColor   	RectColor           ;//    offset = 0x00000000, flags = 0x0010000000000080, _tagLinearColor
		float     		ScreenX             ;//    offset = 0x00000010, flags = 0x0010000000000080, 
		float     		ScreenY             ;//    offset = 0x00000014, flags = 0x0010000000000080, 
		float     		ScreenW             ;//    offset = 0x00000018, flags = 0x0010000000000080, 
		float     		ScreenH             ;//    offset = 0x0000001C, flags = 0x0010000000000080, 
	          								;//      Size = 0x00000020
	}_args = { };

	_args.RectColor = RectColor;
	_args.ScreenX = ScreenX;
	_args.ScreenY = ScreenY;
	_args.ScreenW = ScreenW;
	_args.ScreenH = ScreenH;

	__CallUObject$ProcessEvent(_AHUD, _CALLUFunction, &_args);
}








