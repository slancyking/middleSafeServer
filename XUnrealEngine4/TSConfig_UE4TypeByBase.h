#pragma once
//
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
//
#include <windows.h>					// Windows 头文件
//
#include <stdlib.h>
//
#include <stdint.h>
//
#include "TSConfig_UE4Type.h"

#ifndef TSCONFIG_UE4TYPEBAST_H
#define TSCONFIG_UE4TYPEBAST_H

struct						UE4$UClass;
struct						UE4$UObjectBase;
struct						UE4$UProperty;
struct                      UE4$UStruct;
struct                      UE4$UEnum;
struct                      UE4$FString;
struct                      UE4$FArray;

typedef void				UObject;
typedef wchar_t				UE4Char;
typedef void				FText;
typedef void				FString;
typedef void				FName;
typedef unsigned char       sbyte;

#pragma pack (1)


//00000000 FSlateSound     struc ; (sizeof=0x18, align=0x8, copyof_2804)
//00000000                                         ; XREF: ?PlaySound@UUserWidget@@QEAAXPEAVUSoundBase@@@Z/r
//00000000                                         ; FButtonStyle/r ...
//00000000 ResourceObject  dq ?                    ; XREF: UUserWidget::PlaySound(USoundBase *)+12/w ; offset
//00000008 LegacyResourceName_DEPRECATED FName ?   ; XREF: UUserWidget::PlaySound(USoundBase *)+1F/w
//00000010 LegacyResourceObject_DEPRECATED TWeakObjectPtr<UObject,FWeakObjectPtr> ?
//00000010                                         ; XREF: UUserWidget::PlaySound(USoundBase *)+24/w
//00000010                                         ; UUserWidget::PlaySound(USoundBase *)+28/w
//00000018 FSlateSound     ends

typedef struct _tagSlateSound {
	UObject *   ResourceObject;
	uint64_t    LegacyResourceName_DEPRECATED;
	uint64_t    LegacyResourceObject_DEPRECATED;
} FSlateSound;


typedef struct _tagMargin {
	float               	Left                                    ;//    offset = 0x00000000, flags = 0x0010000000000005, 
	float               	Top                                     ;//    offset = 0x00000004, flags = 0x0010000000000005, 
	float               	Right                                   ;//    offset = 0x00000008, flags = 0x0010000000000005, 
	float               	Bottom                                  ;//    offset = 0x0000000C, flags = 0x0010000000000005, 
	                    	                                        ;//      Size = 0x00000010
} FMargin;




typedef struct _tagVector {
	float     x;
	float     y;
	float     z;

	//获取两点距离, 点 -> 点
	float dis(_tagVector toFVector) {
		float x1 = x;
		float y1 = y;

		float x2 = toFVector.x;
		float y2 = toFVector.y;

		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}
} FVector;

typedef struct _tagVector2D {
	float     x;
	float     y;

} FVector2D;

typedef struct _tagRotator {
	float     Pitch;
	float     Yaw;
	float     Roll;
} FRotator;



//00000000 FSlateRect      struc; (sizeof = 0x10, align = 0x4, copyof_2655)
//00000000; XREF: ? ComputePopupFitInRect@@YA?AUFVector2D@@AEBVFSlateRect@@0AEBW4EOrientation@@0@Z/r
//00000000; sub_140884870 / r ...
//00000000 Left            dd ? ; XREF: ComputePopupFitInRect(FSlateRect const &, FSlateRect const &, EOrientation const &, FSlateRect const &) + B / r
//00000000; ComputePopupFitInRect(FSlateRect const &, FSlateRect const &, EOrientation const &, FSlateRect const &) + 1D2 / w ...
//00000004 Top             dd ? ; XREF: SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 1D6 / r
//00000004; SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 1FA / w ...
//00000008 Right           dd ? ; XREF: SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 1E5 / r
//00000008; SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 200 / w ...
//0000000C Bottom          dd ? ; XREF: SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 1CB / r
//0000000C; SWidget::CalculateCullingAndClippingRules(FGeometry const &, FSlateRect const &, bool &, bool &, bool &) + 206 / w ...
//00000010 FSlateRect      ends

typedef struct _tagSlateRect {
	LONG    left;
	LONG    top;
	LONG    right;
	LONG    bottom;
} FSlateRect;



typedef struct _tagLinearColor {
	float	R, G, B, A;

	_tagLinearColor(float InR, float InG, float InB, float InA = 1.0f) :
		R(InR), G(InG), B(InB), A(InA) {
	}

	_tagLinearColor() : R(0.0f), G(0.0f), B(0.0f), A(0.0f) {

	}

	// Common colors.	
	static  const _tagLinearColor White;
	static  const _tagLinearColor Gray;
	static  const _tagLinearColor Black;
	static  const _tagLinearColor Transparent;
	static  const _tagLinearColor Red;
	static  const _tagLinearColor Green;
	static  const _tagLinearColor Blue;
	static  const _tagLinearColor Yellow;
} FLinearColor;



//00000000 FSlateColor     struc ; (sizeof=0x28, align=0x8, copyof_2711)
//00000000                                         ; XREF: STextBlock::OnPaint(FPaintArgs const &,FGeometry const &,FSlateRect const &,FSlateWindowElementList &,int,FWidgetStyle const &,bool)+323/w
//00000000                                         ; .data:stru_14334C4B0/r ...
//00000000 SpecifiedColor  FLinearColor ?          ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+B2/w
//00000000                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+F7/w ...
//00000010 ColorUseRule    TEnumAsByte<enum ESlateColorStylingMode::Type> ?
//00000010                                         ; XREF: SCompoundWidget::SCompoundWidget(void)+102/w
//00000010                                         ; SWindow::SWindow(void)+102/w ...
//00000011                 db ? ; undefined
//00000012                 db ? ; undefined
//00000013                 db ? ; undefined
//00000014                 db ? ; undefined
//00000015                 db ? ; undefined
//00000016                 db ? ; undefined
//00000017                 db ? ; undefined
//00000018 LinkedSpecifiedColor TSharedPtr<FLinearColor,0> ?
//00000018                                         ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+D5/w
//00000018                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+E7/w ...
//00000028 FSlateColor     ends
typedef struct _tagSlateColor {
	FLinearColor            SpecifiedColor                          ;//    offset = 0x00000000, flags = 0x0020080000000004, LinearColor
	uint64_t                ColorUseRule							;//    offset = 0x00000010, flags = 0x0020080000000004, 
	sbyte                    LinkedSpecifiedColor[0x00000010];
	                    	                                        ;//      Size = 0x00000028
} FSlateColor;


typedef struct _tagBox2D {
	FVector2D             	Min                                     ;//    offset = 0x00000000, flags = 0x0010000001000005, Vector2D
	FVector2D             	Max                                     ;//    offset = 0x00000008, flags = 0x0010000001000005, Vector2D
	uint32_t                bIsValid                                ;//    offset = 0x00000010, flags = 0x0010000000000000, 
	                    	                                        ;//      Size = 0x00000014
} FBox2D;

//00000000 FSlateBrush     struc ; (sizeof=0x88, align=0x8, copyof_2793)
//00000000                                         ; XREF: .data:stru_143352C70/r
//00000000                                         ; ?MakeBrushFromSprite@UPaperSpriteBlueprintLibrary@@SA?AUFSlateBrush@@PEAVUPaperSprite@@HH@Z/r ...
//00000000 vfptr           dq ?                    ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+95/w
//00000000                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+18F/w ... ; offset
//00000008 ImageSize       FVector2D ?             ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+9A/w
//00000008                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+A7/w ...
//00000010 Margin          FMargin ?               ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+F3/w
//00000010                                         ; SImage::Construct(SImage::FArguments const &)+8E/w ...
//00000020 TintColor       FSlateColor ?           ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+B2/w
//00000020                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+D5/w ...
//00000048 ResourceObject  dq ?                    ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+D0/w
//00000048                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+E2/w ... ; offset
//00000050 ResourceName    FName ?                 ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+FF/w
//00000050                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+102/w ...
//00000058 UVRegion        FBox2D ?                ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+88/w
//00000058                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+DD/w ...
//0000006C DrawAs          TEnumAsByte<enum ESlateBrushDrawType::Type> ?
//0000006C                                         ; XREF: SImage::Construct(SImage::FArguments const &)+DF/w
//0000006C                                         ; FInvalidatableBrushAttribute::SetImage(SWidget &,TAttribute<FSlateBrush const *> const &)+219/r ...
//0000006D Tiling          TEnumAsByte<enum ESlateBrushTileType::Type> ?
//0000006D                                         ; XREF: FInvalidatableBrushAttribute::SetImage(SWidget &,TAttribute<FSlateBrush const *> const &)+276/r
//0000006D                                         ; SEditableText::SynchronizeTextStyle(void)+2C1/r ...
//0000006E Mirroring       TEnumAsByte<enum ESlateBrushMirrorType::Type> ?
//0000006E                                         ; XREF: FInvalidatableBrushAttribute::SetImage(SWidget &,TAttribute<FSlateBrush const *> const &)+282/r
//0000006E                                         ; SEditableText::SynchronizeTextStyle(void)+2CD/r
//0000006F ImageType       TEnumAsByte<enum ESlateBrushImageType::Type> ?
//0000006F                                         ; XREF: FDeferredCleanupSlateBrush::CreateBrush(UTexture *,FLinearColor const &,ESlateBrushTileType::Type,ESlateBrushImageType::Type)+131/w
//00000070 ResourceHandle  FSlateResourceHandle ?  ; XREF: UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+40/o
//00000070                                         ; UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(UPaperSprite *,int,int)+4A/r ...
//00000080 _bf80           db ?                    ; XREF: SImage::Construct(SImage::FArguments const &)+64/w
//00000080                                         ; FInvalidatableBrushAttribute::SetImage(SWidget &,TAttribute<FSlateBrush const *> const &)+2B5/r ...
//00000081                 db ? ; undefined
//00000082                 db ? ; undefined
//00000083                 db ? ; undefined
//00000084                 db ? ; undefined
//00000085                 db ? ; undefined
//00000086                 db ? ; undefined
//00000087                 db ? ; undefined
//00000088 FSlateBrush     ends
typedef struct _tagSlateBrush {
	uint64_t                vfptr;
	FVector2D             	ImageSize                               ;//    offset = 0x00000008, flags = 0x0010000000000005, Vector2D
	FMargin             	Margin                                  ;//    offset = 0x00000010, flags = 0x0010000000000005, Margin
	FSlateColor             TintColor                               ;//    offset = 0x00000020, flags = 0x0010000000000005, SlateColor
	UObject   *         	ResourceObject                          ;//    offset = 0x00000048, flags = 0x0040000000000004, UObject
	uint64_t                ResourceName                            ;//    offset = 0x00000050, flags = 0x0020080000000000, 
	FBox2D             	    UVRegion                                ;//    offset = 0x00000058, flags = 0x0020080000000000, Box2D
	sbyte                	DrawAs                                  ;//    offset = 0x0000006C, flags = 0x0010000000000005, 
	sbyte                	Tiling                                  ;//    offset = 0x0000006D, flags = 0x0010000000000005, 
	sbyte                	Mirroring                               ;//    offset = 0x0000006E, flags = 0x0010000000000005, 
	sbyte                	ImageType                               ;//    offset = 0x0000006F, flags = 0x0010000000000000, 
	uint64_t                ResourceHandle[2];
	uint64_t                _bf80;
	                    	                                        ;//      Size = 0x00000088
} FSlateBrush;




typedef struct _tagSlateWidgetStyle {
	uint64_t                vfptr;
	                    	                                        ;//      Size = 0x00000008
} FSlateWidgetStyle;


typedef struct _tagButtonStyle : FSlateWidgetStyle {  // ButtonStyle -> SlateWidgetStyle
	FSlateBrush             	Normal                                  ;//    offset = 0x00000008, flags = 0x0010000000000005, SlateBrush
	FSlateBrush             	Hovered                                 ;//    offset = 0x00000090, flags = 0x0010000000000005, SlateBrush
	FSlateBrush             	Pressed                                 ;//    offset = 0x00000118, flags = 0x0010000000000005, SlateBrush
	FSlateBrush             	Disabled                                ;//    offset = 0x000001A0, flags = 0x0010000000000005, SlateBrush
	FMargin             		NormalPadding							;//    offset = 0x00000228, flags = 0x0010000000000005, Margin
	FMargin             		PressedPadding							;//    offset = 0x00000238, flags = 0x0010000000000005, Margin
	FSlateSound             	PressedSlateSound                       ;//    offset = 0x00000248, flags = 0x0010000000000005, SlateSound
	FSlateSound             	HoveredSlateSound                       ;//    offset = 0x00000260, flags = 0x0010000000000005, SlateSound
	                    												;//      Size = 0x00000278
} FButtonStyle;




typedef  FVector   FVector_NetQuantize;
typedef  FVector   FVector_NetQuantizeNormal;


typedef struct _tagHitResult {
	sbyte                	bBlockingHit                            ;//    offset = 0x00000000, flags = 0x0010000000000000, 
	sbyte                	bStartPenetrating                       ;//    offset = 0x00000000, flags = 0x0010000000000000, 
	sbyte					unknown_1;								 //    ռλ
	sbyte					unknown_2;								 //    ռλ
	int32_t             	FaceIndex                               ;//    offset = 0x00000004, flags = 0x0010000000000000, 
	float               	Time                                    ;//    offset = 0x00000008, flags = 0x0010000000000000, 
	float               	Distance                                ;//    offset = 0x0000000C, flags = 0x0010000000000000, 
	FVector_NetQuantize     Location                                ;//    offset = 0x00000010, flags = 0x0010000000000000, Vector_NetQuantize
	FVector_NetQuantize     ImpactPoint                             ;//    offset = 0x0000001C, flags = 0x0010000000000000, Vector_NetQuantize
	FVector_NetQuantizeNormal Normal                                ;//    offset = 0x00000028, flags = 0x0010000000000000, Vector_NetQuantizeNormal
	FVector_NetQuantizeNormal ImpactNormal                          ;//    offset = 0x00000034, flags = 0x0010000000000000, Vector_NetQuantizeNormal
	FVector_NetQuantize     TraceStart                              ;//    offset = 0x00000040, flags = 0x0010000000000000, Vector_NetQuantize
	FVector_NetQuantize     TraceEnd                                ;//    offset = 0x0000004C, flags = 0x0010000000000000, Vector_NetQuantize
	float               	PenetrationDepth                        ;//    offset = 0x00000058, flags = 0x0010000000000000, 
	int32_t             	Item                                    ;//    offset = 0x0000005C, flags = 0x0010000000000000, 
	UObject *           	PhysMaterial                            ;//    offset = 0x00000060, flags = 0x0014000000000000, 
	UObject *          		Actor                                   ;//    offset = 0x00000068, flags = 0x0014000000000000, 
	UObject *          		Component                               ;//    offset = 0x00000070, flags = 0x0014000000080008, 
	uint64_t               	BoneName                                ;//    offset = 0x00000078, flags = 0x0010000000000000, 
	uint64_t               	MyBoneName                              ;//    offset = 0x00000080, flags = 0x0010000000000000, 
	                    	                                        ;//      Size = 0x00000088
} FHitResult;


typedef struct _tagFontOutlineSettings {
	int32_t             	OutlineSize                             ;//    offset = 0x00000000, flags = 0x0010000000000005, 
	bool                	bSeparateFillAlpha                      ;//    offset = 0x00000004, flags = 0x0010000000000005, 
	bool                	bApplyOutlineToDropShadows              ;//    offset = 0x00000005, flags = 0x0010000000000005, 
	UObject       *     	OutlineMaterial                         ;//    offset = 0x00000008, flags = 0x0010000000000005, UObject
	FLinearColor            OutlineColor                            ;//    offset = 0x00000010, flags = 0x0010000000000005, LinearColor
	                    	                                        ;//      Size = 0x00000020
} FFontOutlineSettings;



typedef struct _tagSlateFontInfo {
	UObject     *       	FontObject                              ;//    offset = 0x00000000, flags = 0x0010000000000005, UObject
	UObject     *       	FontMaterial                            ;//    offset = 0x00000008, flags = 0x0010000000000005, UObject
	FFontOutlineSettings    OutlineSettings                         ;//    offset = 0x00000010, flags = 0x0010000000000005, FontOutlineSettings
	uint64_t               	TypefaceFontName                        ;//    offset = 0x00000040, flags = 0x0010000000000005, 
	int32_t             	Size                                    ;//    offset = 0x00000048, flags = 0x0010000000000005, 
	                    	                                        ;//      Size = 0x00000050
} FSlateFontInfo;








#pragma pack ()
#endif
