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
#include "TSConfig_UE4TypeByBase.h"

#ifndef TSCONFIG_UE4TYPEUI_H
#define TSCONFIG_UE4TYPEUI_H

/** Enumeration to specify different window types for SWindows */
enum class EWindowType : uint32_t {
	/** Value indicating that this is a standard, general-purpose window */
	Normal,
	/** Value indicating that this is a window used for a popup menu */
	Menu,
	/** Value indicating that this is a window used for a tooltip */
	ToolTip,
	/** Value indicating that this is a window used for a notification toast */
	Notification,
	/** Value indicating that this is a window used for a cursor decorator */
	CursorDecorator,
	/** Value indicating that this is a game window */
	GameWindow
};

enum EVisibility$Private : uint8_t {
	/** Entity is visible */
	VISPRIVATE_Visible							= 0x1 << 0,
	/** Entity is invisible and takes up no space */
	VISPRIVATE_Collapsed						= 0x1 << 1,
	/** Entity is invisible, but still takes up space (layout pretends it is visible) */
	VISPRIVATE_Hidden							= 0x1 << 2,
	/** Can we click on this widget or is it just non-interactive decoration? */
	VISPRIVATE_SelfHitTestVisible				= 0x1 << 3,
	/** Can we click on this widget's child widgets? */
	VISPRIVATE_ChildrenHitTestVisible			= 0x1 << 4,

	/** Default widget visibility - visible and can interactive with the cursor */
	VIS_Visible									= VISPRIVATE_Visible | VISPRIVATE_SelfHitTestVisible | VISPRIVATE_ChildrenHitTestVisible,
	/** Not visible and takes up no space in the layout; can never be clicked on because it takes up no space. */
	VIS_Collapsed								= VISPRIVATE_Collapsed,
	/** Not visible, but occupies layout space. Not interactive for obvious reasons. */
	VIS_Hidden									= VISPRIVATE_Hidden,
	/** Visible to the user, but only as art. The cursors hit tests will never see this widget. */
	VIS_HitTestInvisible						= VISPRIVATE_Visible,
	/** Same as HitTestInvisible, but doesn't apply to child widgets. */
	VIS_SelfHitTestInvisible					= VISPRIVATE_Visible | VISPRIVATE_ChildrenHitTestVisible,

	/** Any visibility will do */
	VIS_All										= VISPRIVATE_Visible | VISPRIVATE_Hidden | VISPRIVATE_Collapsed | VISPRIVATE_SelfHitTestVisible | VISPRIVATE_ChildrenHitTestVisible
};



#pragma pack (1)



#pragma region//---------------------------------------------------------------------------------------------特征分组: FGenericWindowVtbl
//00000000 FGenericWindowVtbl struc; (sizeof = 0x120, align = 0x8, copyof_2821)
//00000000 __vecDelDtor    dq ? ; offset
//00000008 gap8            db 32 dup(? )
//00000028 HACK_ForceToFront dq ? ; offset
//00000030 Destroy         dq ? ; offset
//00000038 Minimize        dq ? ; offset
//00000040 Maximize        dq ? ; offset
//00000048 Restore         dq ? ; offset
//00000050 Show            dq ? ; offset
//00000058 Hide            dq ? ; offset
//00000060 SetWindowMode   dq ? ; offset
//00000068 GetWindowMode   dq ? ; offset
//00000070 IsMaximized     dq ? ; offset
//00000078 IsMinimized     dq ? ; offset
//00000080 IsVisible       dq ? ; offset
//00000088 GetRestoredDimensions dq ? ; offset
//00000090 SetWindowFocus  dq ? ; offset
//00000098 SetOpacity      dq ? ; offset
//000000A0 Enable          dq ? ; offset
//000000A8 IsPointInWindow dq ? ; offset
//000000B0 GetWindowBorderSize dq ? ; offset
//000000B8 GetWindowTitleBarSize dq ? ; offset
//000000C0 GetOSWindowHandle dq ? ; offset
//000000C8 IsForegroundWindow dq ? ; offset
//000000D0 SetText         dq ? ; offset
//000000D8 GetDefinition   dq ? ; offset
//000000E0 IsDefinitionValid dq ? ; offset
//000000E8 AdjustCachedSize dq ? ; offset
//000000F0 GetDPIScaleFactor dq ? ; offset
//000000F8 SetDPIScaleFactor dq ? ; offset
//00000100 IsManualManageDPIChanges dq ? ; offset
//00000108 SetManualManageDPIChanges dq ? ; offset
//00000110 DrawAttention   dq ? ; offset
//00000118 SetNativeWindowButtonsVisibility dq ? ; offset
//00000120 FGenericWindowVtbl ends

struct UE4$FGenericWindowVtbl {
	void  *			__vecDelDtor;
	uint32_t		gap8[8];
	void  *			HACK_ForceToFront;
	void  *			Destroy;
	void  *			Minimize;
	void  *			Maximize;
	void  *			Restore;
	void  *			Show;
	void  *			Hide;
	void  *			SetWindowMode;
	void  *			GetWindowMode;
	void  *			IsMaximized;
	void  *			IsMinimized;
	void  *			IsVisible;
	void  *			GetRestoredDimensions;
	void  *			SetWindowFocus;
	void  *			SetOpacity;
	void  *			Enable;
	void  *			IsPointInWindow;
	void  *			GetWindowBorderSize;
	void  *			GetWindowTitleBarSize;
	void  *			GetOSWindowHandle;
	void  *			IsForegroundWindow;
	void  *			SetText;
	void  *			GetDefinition;
	void  *			IsDefinitionValid;
	void  *			AdjustCachedSize;
	void  *			GetDPIScaleFactor;
	void  *			SetDPIScaleFactor;
	void  *			IsManualManageDPIChanges;
	void  *			SetManualManageDPIChanges;
	void  *			DrawAttention;
	void  *			SetNativeWindowButtonsVisibility;
};






#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: FGeometry, FSlateWidgetPersistentState

//00000000 FGeometry       struc ; (sizeof=0x38, align=0x4, copyof_2654)
//00000000                                         ; XREF: .data:stru_143352C18/r
//00000000                                         ; .data:stru_1433FA588/r ...
//00000000 Size            FVector2D ?             ; XREF: FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+177/r
//00000000                                         ; FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+636/w ...
//00000008 Scale           dd ?                    ; XREF: sub_140874030+44B/w
//00000008                                         ; SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+753/w ...
//0000000C AbsolutePosition FVector2D ?            ; XREF: FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+17B/r
//0000000C                                         ; FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+63E/w ...
//00000014 Position        FVector2D ?             ; XREF: sub_140874030+456/w
//00000014                                         ; sub_140874030+45C/w ...
//0000001C AccumulatedRenderTransform FTransform2D ?
//0000001C                                         ; XREF: FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility):loc_140861AD1/r
//0000001C                                         ; FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+17F/r ...
//00000034 _bf34           db ?                    ; XREF: sub_140874030+423/r
//00000034                                         ; sub_140874030+442/w ...
//00000035                 db ? ; undefined
//00000036                 db ? ; undefined
//00000037                 db ? ; undefined
//00000038 FGeometry       ends

struct UE4$FGeometry {
	FVector2D           Size;																		 // 00000000 Size      FVector2D ?       ; XREF: FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+177/r
	float               Scale;																		 // 00000008 Scale      dd ?          ; XREF: sub_140874030+44B/w
	FVector2D           AbsolutePosition;															 // 0000000C AbsolutePosition FVector2D ?      ; XREF: FWeakWidgetPath::ToWidgetPath(FWidgetPath &,FWeakWidgetPath::EInterruptedPathHandling::Type,FPointerEvent const *,EVisibility)+17B/r
	FVector2D           Position;																	 // 00000014 Position    FVector2D ?       ; XREF: sub_140874030+456/w
	sbyte                AccumulatedRenderTransform[0x00000018];                                      // 0000001C AccumulatedRenderTransform FTransform2D ?
	sbyte                _bf34[0x00000004];                                                           // 00000034 _bf34      db ?          ; XREF: sub_140874030+423/r
}; // StructSize == 0x00000038



//00000000 FSlateWidgetPersistentState struc ; (sizeof=0x120, align=0x8, copyof_2657)
//00000000                                         ; XREF: SWidget/r
//00000000 PaintParent     TWeakPtr<SWidget,0> ?
//00000010 InitialClipState TOptional<FSlateClippingState> ?
//00000058 AllottedGeometry FGeometry ?
//00000090 DesktopGeometry FGeometry ?
//000000C8 CullingBounds   FSlateRect ?
//000000D8 WidgetStyle     FWidgetStyle ?
//00000108 CachedElementListNode dq ?              ; offset
//00000110 LayerId         dd ?
//00000114 OutgoingLayerId dd ?
//00000118 IncomingFlowDirection db ?
//00000119 _bf119          db ?
//0000011A                 db ? ; undefined
//0000011B                 db ? ; undefined
//0000011C                 db ? ; undefined
//0000011D                 db ? ; undefined
//0000011E                 db ? ; undefined
//0000011F                 db ? ; undefined
//00000120 FSlateWidgetPersistentState ends
struct UE4$FSlateWidgetPersistentState {
	sbyte                PaintParent[0x00000010];                                                     // 00000000 PaintParent   TWeakPtr<SWidget,0> ?
	sbyte                InitialClipState[0x00000048];                                                // 00000010 InitialClipState TOptional<FSlateClippingState> ?
	UE4$FGeometry       AllottedGeometry;															 // 00000058 AllottedGeometry FGeometry ?
	UE4$FGeometry       DesktopGeometry;															 // 00000090 DesktopGeometry FGeometry ?
	FSlateRect          CullingBounds;																 // 000000C8 CullingBounds  FSlateRect ?
	sbyte                WidgetStyle[0x00000030];                                                     // 000000D8 WidgetStyle   FWidgetStyle ?
	sbyte                CachedElementListNode[0x00000008];                                           // 00000108 CachedElementListNode dq ?       ; offset
	uint32_t            LayerId;																	 // 00000110 LayerId     dd ?
	uint32_t            OutgoingLayerId;															 // 00000114 OutgoingLayerId dd ?
	sbyte                IncomingFlowDirection[0x00000001];                                           // 00000118 IncomingFlowDirection db ?
	sbyte                _bf119[0x00000007];                                                          // 00000119 _bf119     db ?
}; // StructSize == 0x00000120











#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SWidget, SLeafWidget
typedef void									SWidget;

struct UE4$SWidget {
	uint64_t            vfTable;																	 // 00000000 baseclass_0   FSlateControlledConstruction ?
	sbyte                baseclass_8[0x00000010];                                                     // 00000008 baseclass_8   TSharedFromThis<SWidget, 0> ?
	sbyte                FastPathProxyHandle[0x00000010];                                             // 00000018 FastPathProxyHandle FWidgetProxyHandle ?
	sbyte                _bf28[0x00000001];                                                           // 00000028 _bf28      db ?
	sbyte                _bf29[0x00000001];                                                           // 00000029 _bf29      db ?
	sbyte                AccessibleBehavior[0x00000001];                                              // 0000002A AccessibleBehavior db ?
	sbyte                AccessibleSummaryBehavior[0x00000001];                                       // 0000002B AccessibleSummaryBehavior db ?
	sbyte                Clipping[0x00000001];                                                        // 0000002C Clipping    db ?
	sbyte                FlowDirectionPreference[0x00000001];                                         // 0000002D FlowDirectionPreference db ?
	sbyte                UpdateFlags[0x00000002];                                                     // 0000002E UpdateFlags   db ?
	UE4$FSlateWidgetPersistentState    PersistentState;                                              // 00000030 PersistentState FSlateWidgetPersistentState ?
	sbyte                DesiredSize[0x00000010];                                                     // 00000150 DesiredSize   TOptional<FVector2D> ?
	sbyte                ActiveTimers[0x00000010];                                                    // 00000160 ActiveTimers  TArray<TSharedRef<FActiveTimerHandle, 0>, TSizedDefaultAllocator<32> > ?
	sbyte                PrepassLayoutScaleMultiplier[0x00000008];                                    // 00000170 PrepassLayoutScaleMultiplier TOptional<float> ?
	FMargin             CullingBoundsExtension;														 // 00000178 CullingBoundsExtension FMargin ?
	sbyte                EnabledState[0x00000018];                                                    // 00000188 EnabledState  TAttribute<bool> ?
	sbyte                Visibility[0x00000018];                                                      // 000001A0 Visibility   TAttribute<EVisibility> ? 
	sbyte                RenderOpacity[0x00000008];                                                   // 000001B8 RenderOpacity  dd ?
	sbyte                RenderTransform[0x00000030];                                                 // 000001C0 RenderTransform TAttribute<TOptional<FTransform2D> > ?
	sbyte                RenderTransformPivot[0x00000020];                                            // 000001F0 RenderTransformPivot TAttribute<FVector2D> ?
	uint64_t            TypeOfWidget;																 // 00000210 TypeOfWidget  FName ?
	uint64_t            Tag;																		 // 00000218 Tag       FName ?
	sbyte                MetaData[0x00000010];                                                        // 00000220 MetaData    TArray<TSharedRef<ISlateMetaData, 0>, TSizedDefaultAllocator<32> > ?
	sbyte                Cursor[0x00000020];                                                          // 00000230 Cursor     TAttribute<TOptional<enum EMouseCursor::Type> > ?
	sbyte                ToolTip[0x00000010];                                                         // 00000250 ToolTip     TSharedPtr<IToolTip, 0> ?
	sbyte                ParentWidgetPtr[0x00000010];                                                 // 00000260 ParentWidgetPtr TWeakPtr<SWidget, 0> ?
	sbyte                PointerEvents[0x00000010];                                                   // 00000270 PointerEvents  TArray<TTuple<FName, TBaseDelegate<FReply, FGeometry const &, FPointerEvent const &> >, TSizedDefaultAllocator<32> > ?
	sbyte                MouseEnterHandler[0x00000010];                                               // 00000280 MouseEnterHandler TBaseDelegate<void, FGeometry const &, FPointerEvent const &> ?
	sbyte                MouseLeaveHandler[0x00000010];                                               // 00000290 MouseLeaveHandler TBaseDelegate<void, FPointerEvent const &> ?
};
 
//00000000 SLeafWidget     struc; (sizeof = 0x2A0, align = 0x8, copyof_4711)
//00000000; XREF: STextBlock / r
//00000000 baseclass_0     SWidget ?
//000002A0 SLeafWidget     ends

struct UE4$SLeafWidget : public UE4$SWidget {

};

#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: STextBlock
//00000000 STextBlock      struc; (sizeof = 0x790, align = 0x8, copyof_4720)
//00000000 baseclass_0     SLeafWidget ?
//000002A0 BoundText       TAttribute<FText> ?
//000002D0 TextLayoutCache TUniquePtr<FSlateTextBlockLayout, TDefaultDelete<FSlateTextBlockLayout> > ?
//000002D8 TextStyle       FTextBlockStyle ?
//00000540 Font            TAttribute<FSlateFontInfo> ?
//000005A8 StrikeBrush     TAttribute<FSlateBrush const *> ?
//000005C8 ColorAndOpacity TAttribute<FSlateColor> ?
//00000608 ShadowOffset    TAttribute<FVector2D> ?
//00000628 ShadowColorAndOpacity TAttribute<FLinearColor> ?
//00000650 HighlightColor  TAttribute<FLinearColor> ?
//00000678 HighlightShape  TAttribute<FSlateBrush const *> ?
//00000698 HighlightText   TAttribute<FText> ?
//000006C8 WrapTextAt      TAttribute<float> ?
//000006E0 AutoWrapText    TAttribute<bool> ?
//000006F8 WrappingPolicy  TAttribute<enum ETextWrappingPolicy> ?
//00000710 Margin          TAttribute<FMargin> ?
//00000738 Justification   TAttribute<enum ETextJustify::Type> ?
//00000750 LineHeightPercentage TAttribute<float> ?
//00000768 MinDesiredWidth TAttribute<float> ?
//00000780 CachedSimpleDesiredSize TOptional<FVector2D> ?
//0000078C bSimpleTextMode db ?
//0000078D                 db ? ; undefined
//0000078E                 db ? ; undefined
//0000078F                 db ? ; undefined
//00000790 STextBlock      ends
struct UE4$STextBlock : public UE4$SLeafWidget {
	sbyte                BoundText[0x00000030];                                                       // 000002A0 BoundText    TAttribute<FText> ?
	sbyte                TextLayoutCache[0x00000008];                                                 // 000002D0 TextLayoutCache TUniquePtr<FSlateTextBlockLayout,TDefaultDelete<FSlateTextBlockLayout> > ?
	sbyte                TextStyle[0x00000268];                                                       // 000002D8 TextStyle    FTextBlockStyle ?
	sbyte                Font[0x00000068];                                                            // 00000540 Font      TAttribute<FSlateFontInfo> ?
	sbyte                StrikeBrush[0x00000020];                                                     // 000005A8 StrikeBrush   TAttribute<FSlateBrush const *> ?
	sbyte                ColorAndOpacity[0x00000040];                                                 // 000005C8 ColorAndOpacity TAttribute<FSlateColor> ?
	sbyte                ShadowOffset[0x00000020];                                                    // 00000608 ShadowOffset  TAttribute<FVector2D> ?
	sbyte                ShadowColorAndOpacity[0x00000028];                                           // 00000628 ShadowColorAndOpacity TAttribute<FLinearColor> ?
	sbyte                HighlightColor[0x00000028];                                                  // 00000650 HighlightColor TAttribute<FLinearColor> ?
	sbyte                HighlightShape[0x00000020];                                                  // 00000678 HighlightShape TAttribute<FSlateBrush const *> ?
	sbyte                HighlightText[0x00000030];                                                   // 00000698 HighlightText  TAttribute<FText> ?
	sbyte                WrapTextAt[0x00000018];                                                      // 000006C8 WrapTextAt   TAttribute<float> ?
	sbyte                AutoWrapText[0x00000018];                                                    // 000006E0 AutoWrapText  TAttribute<bool> ?
	sbyte                WrappingPolicy[0x00000018];                                                  // 000006F8 WrappingPolicy TAttribute<enum ETextWrappingPolicy> ?
	sbyte                Margin[0x00000028];                                                          // 00000710 Margin     TAttribute<FMargin> ?
	sbyte                Justification[0x00000018];                                                   // 00000738 Justification  TAttribute<enum ETextJustify::Type> ?
	sbyte                LineHeightPercentage[0x00000018];                                            // 00000750 LineHeightPercentage TAttribute<float> ?
	sbyte                MinDesiredWidth[0x00000018];                                                 // 00000768 MinDesiredWidth TAttribute<float> ?
	sbyte                CachedSimpleDesiredSize[0x0000000C];                                         // 00000780 CachedSimpleDesiredSize TOptional<FVector2D> ?
	sbyte                bSimpleTextMode[0x00000004];                                                 // 0000078C bSimpleTextMode db ?
};



#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SCompoundWidget, SBorder

//00000000 SCompoundWidget struc; (sizeof = 0x388, align = 0x8, copyof_2714)
//00000000; XREF: SWindow / r
//00000000; SBorder / r
//00000000 baseclass_0     SWidget ?
//000002A0 ChildSlot       FSimpleSlot ?
//00000300 ContentScale    TAttribute<FVector2D> ?
//00000320 ColorAndOpacity TAttribute<FLinearColor> ?
//00000348 ForegroundColor TAttribute<FSlateColor> ?
//00000388 SCompoundWidget ends

struct UE4$SCompoundWidget : public UE4$SWidget {
																									 // 00000000 baseclass_0   SWidget ?
	sbyte                ChildSlot[0x00000060];                                                       // 000002A0 ChildSlot    FSimpleSlot ?
	sbyte                ContentScale[0x00000020];                                                    // 00000300 ContentScale  TAttribute<FVector2D> ?
	sbyte                ColorAndOpacity[0x00000028];                                                 // 00000320 ColorAndOpacity TAttribute<FLinearColor> ?
	sbyte                ForegroundColor[0x00000040];                                                 // 00000348 ForegroundColor TAttribute<FSlateColor> ?

	UE4$SWidget * getChildSlot() {
		uint64_t TMPBuffer = NULL;
		//000002A0 ChildSlot       FSimpleSlot ?
		//00000300 ContentScale    TAttribute<FVector2D> ?
		if (NULL == (TMPBuffer = (uint64_t)&ChildSlot[0]))
			return NULL;

		//00000000 FSimpleSlot     struc ; (sizeof=0x60, align=0x8, copyof_2706)
		//00000000                                         ; XREF: SCompoundWidget/r
		//00000000 baseclass_0     TSupportsOneChildMixin<FSimpleSlot> ?
		//00000030 baseclass_30    TSupportsContentAlignmentMixin<FSimpleSlot> ?
		//00000038 baseclass_38    TSupportsContentPaddingMixin<FSimpleSlot> ?
		//00000060 FSimpleSlot     ends
		TMPBuffer += 0x00000000;  // 指向  TSupportsOneChildMixin<FSimpleSlot>

		//00000000 TSupportsOneChildMixin<FSimpleSlot> struc ; (sizeof=0x30, align=0x8, copyof_2701)
		//00000000                                         ; XREF: FSimpleSlot/r
		//00000000 baseclass_0     FChildren ?
		//00000010 baseclass_10    TSlotBase<FSimpleSlot> ?
		//00000030 TSupportsOneChildMixin<FSimpleSlot> ends

		TMPBuffer += 0x00000010;  // 指向  TSlotBase<FSimpleSlot> ?

		//00000000 TSlotBase<FSimpleSlot> struc ; (sizeof=0x20, align=0x8, copyof_2700)
		//00000000                                         ; XREF: TSupportsOneChildMixin<FSimpleSlot>/r
		//00000000 baseclass_0     FSlotBase ?
		//00000020 TSlotBase<FSimpleSlot> ends

		TMPBuffer += 0x00000000;  // 指向  baseclass_0     FSlotBase ?

		//00000000 FSlotBase       struc ; (sizeof=0x20, align=0x8, copyof_2696)
		//00000000                                         ; XREF: .data:FSlotBase `TSlotlessChildren<SDockTab>::GetSlotAt(int)'::`2'::NullSlot/r
		//00000000                                         ; .data:FSlotBase `TSlotlessChildren<SWidget>::GetSlotAt(int)'::`2'::NullSlot/r ...
		//00000000 vfptr           dq ?                    ; offset
		//00000008 RawParentPtr    dq ?                    ; offset
		//00000010 Widget          TSharedRef<SWidget,0> ?
		//00000020 FSlotBase       ends

		TMPBuffer += 0x00000010;  // 指向  Widget          TSharedRef<SWidget,0> ?

		//00000000 TSharedRef<SWidget,0> struc ; (sizeof=0x10, align=0x8, copyof_2681)
		//00000000                                         ; XREF: FSlotBase/r
		//00000000                                         ; FArrangedWidget/r ...
		//00000000 Object          dq ?                    ; XREF: SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+77A/w
		//00000000                                         ; SDockingTabWell::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+314/w ... ; offset
		//00000008 SharedReferenceCount SharedPointerInternals::FSharedReferencer<0> ?
		//00000008                                         ; XREF: SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &):loc_1408BFC23/w
		//00000008                                         ; SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+7D9/r ...
		//00000010 TSharedRef<SWidget,0> ends

		TMPBuffer += 0x00000000;  // 指向  Object          dq ? ; 

		return *(UE4$SWidget **)TMPBuffer;
	}
};

//00000000 SBorder         struc; (sizeof = 0x4B0, align = 0x8, copyof_3661)
//00000000; XREF: SButton / r
//00000000 baseclass_0     SCompoundWidget ?
//00000388 BorderImage     FInvalidatableBrushAttribute ?
//00000430 BorderBackgroundColor TAttribute<FSlateColor> ?
//00000470 DesiredSizeScale TAttribute<FVector2D> ?
//00000490 ShowDisabledEffect TAttribute<bool> ?
//000004A8 bFlipForRightToLeftFlowDirection db ?
//000004A9                 db ? ; undefined
//000004AA                 db ? ; undefined
//000004AB                 db ? ; undefined
//000004AC                 db ? ; undefined
//000004AD                 db ? ; undefined
//000004AE                 db ? ; undefined
//000004AF                 db ? ; undefined
//000004B0 SBorder         ends
struct UE4$SBorder : public UE4$SCompoundWidget {
																									 // 00000000 baseclass_0   SCompoundWidget ?
	sbyte                BorderImage[0x000000A8];                                                     // 00000388 BorderImage   FInvalidatableBrushAttribute ?
	sbyte                BorderBackgroundColor[0x00000040];                                           // 00000430 BorderBackgroundColor TAttribute<FSlateColor> ?
	sbyte                DesiredSizeScale[0x00000020];                                                // 00000470 DesiredSizeScale TAttribute<FVector2D> ?
	sbyte                ShowDisabledEffect[0x00000018];                                              // 00000490 ShowDisabledEffect TAttribute<bool> ?
	sbyte                bFlipForRightToLeftFlowDirection[0x00000008];                                // 000004A8 bFlipForRightToLeftFlowDirection db ?
};
#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SButton

//00000000 SButton         struc; (sizeof = 0x5B0, align = 0x8, copyof_3666)
//00000000 baseclass_0     SBorder ?
//000004B0 ContentPadding  TAttribute<FMargin> ?
//000004D8 BorderPadding   FMargin ?
//000004E8 PressedBorderPadding FMargin ?
//000004F8 PressedScreenSpacePosition FVector2D ?
//00000500 Style           dq ? ; offset
//00000508 NormalImage     dq ? ; offset
//00000510 HoverImage      dq ? ; offset
//00000518 PressedImage    dq ? ; offset
//00000520 DisabledImage   dq ? ; offset
//00000528 OnClicked       TBaseDelegate<FReply> ?
//00000538 OnPressed       TBaseDelegate<void> ?
//00000548 OnReleased      TBaseDelegate<void> ?
//00000558 OnHovered       TBaseDelegate<void> ?
//00000568 OnUnhovered     TBaseDelegate<void> ?
//00000578 HoveredSound    FSlateSound ?
//00000590 PressedSound    FSlateSound ?
//000005A8 ClickMethod     TEnumAsByte<enum EButtonClickMethod::Type> ?
//000005A9 TouchMethod     TEnumAsByte<enum EButtonTouchMethod::Type> ?
//000005AA PressMethod     TEnumAsByte<enum EButtonPressMethod::Type> ?
//000005AB _bf5ab          db ?
//000005AC                 db ? ; undefined
//000005AD                 db ? ; undefined
//000005AE                 db ? ; undefined
//000005AF                 db ? ; undefined
//000005B0 SButton         ends
struct UE4$SButton : public UE4$SBorder {
																						 // 00000000 baseclass_0   SBorder ?
	sbyte                ContentPadding[0x00000028];                                      // 000004B0 ContentPadding TAttribute<FMargin> ?
	FMargin             BorderPadding;                                                   // 000004D8 BorderPadding  FMargin ?
	FMargin             PressedBorderPadding;                                            // 000004E8 PressedBorderPadding FMargin ?
	FVector2D           PressedScreenSpacePosition;                                      // 000004F8 PressedScreenSpacePosition FVector2D ?
	uint64_t            Style;                                                           // 00000500 Style      dq ?          ; offset
	uint64_t            NormalImage;                                                     // 00000508 NormalImage   dq ?          ; offset
	uint64_t            HoverImage;                                                      // 00000510 HoverImage   dq ?          ; offset
	uint64_t            PressedImage;                                                    // 00000518 PressedImage  dq ?          ; offset
	uint64_t            DisabledImage;                                                   // 00000520 DisabledImage  dq ?          ; offset
	sbyte                OnClicked[0x00000010];                                           // 00000528 OnClicked    TBaseDelegate<FReply> ?
	sbyte                OnPressed[0x00000010];                                           // 00000538 OnPressed    TBaseDelegate<void> ?
	sbyte                OnReleased[0x00000010];                                          // 00000548 OnReleased   TBaseDelegate<void> ?
	sbyte                OnHovered[0x00000010];                                           // 00000558 OnHovered    TBaseDelegate<void> ?
	sbyte                OnUnhovered[0x00000010];                                         // 00000568 OnUnhovered   TBaseDelegate<void> ?
	FSlateSound         HoveredSound;                                                    // 00000578 HoveredSound  FSlateSound ?
	FSlateSound         PressedSound;                                                    // 00000590 PressedSound  FSlateSound ?
	sbyte                ClickMethod;                                                     // 000005A8 ClickMethod   TEnumAssbyte<enum EButtonClickMethod::Type> ?
	sbyte                TouchMethod;                                                     // 000005A9 TouchMethod   TEnumAssbyte<enum EButtonTouchMethod::Type> ?
	sbyte                PressMethod;                                                     // 000005AA PressMethod   TEnumAssbyte<enum EButtonPressMethod::Type> ?
	sbyte                _bf5ab[0x00000005];                                              // 000005AB _bf5ab     db ?

};

#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SImage
//00000000 FInvalidatableBrushAttribute struc; (sizeof = 0xA8, align = 0x8, copyof_3660)
//00000000;										XREF: SBorder / r
//00000000 Image           TAttribute<FSlateBrush const *> ?
//00000020 ImageCache      FSlateBrush ?
//000000A8 FInvalidatableBrushAttribute ends

struct UE4$FInvalidatableBrushAttribute {
	sbyte				Image[0x00000020];                                      
	sbyte				ImageCache[0x00000088];
};

///** The slate brush to draw for the image that we can invalidate. */
//FInvalidatableBrushAttribute Image;
//
///** Color and opacity scale for this image */
//TAttribute<FSlateColor> ColorAndOpacity;
//
///** Flips the image if the localization's flow direction is RightToLeft */
//bool bFlipForRightToLeftFlowDirection;
//
///** Invoked when the mouse is pressed in the image */
//FPointerEventHandler OnMouseButtonDownHandler;

struct UE4$SImage : public UE4$SLeafWidget {
																						 // class SLATECORE_API SImage : public SLeafWidget

	UE4$FInvalidatableBrushAttribute			Image;									 // The slate brush to draw for the image that we can invalidate. 
	sbyte										ColorAndOpacity[0x00000040];             // Color and opacity scale for this image
	sbyte										bFlipForRightToLeftFlowDirection;        // Flips the image if the localization's flow direction is RightToLeft
	uint64_t									OnMouseButtonDownHandler[4];             // Invoked when the mouse is pressed in the image
};

#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SPanel, SBox

//00000000 SPanel          struc ; (sizeof=0x2A0, align=0x8, copyof_2830)
//00000000                                         ; XREF: SBox/r
//00000000 baseclass_0     SWidget ?
//000002A0 SPanel          ends

struct UE4$SPanel : public UE4$SWidget {

};

//00000000 SBox            struc ; (sizeof=0x3C0, align=0x8, copyof_22589)
//00000000 baseclass_0     SPanel ?
//000002A0 ChildSlot       SBox::FBoxSlot ?
//00000300 WidthOverride   TAttribute<FOptionalSize> ?
//00000318 HeightOverride  TAttribute<FOptionalSize> ?
//00000330 MinDesiredWidth TAttribute<FOptionalSize> ?
//00000348 MinDesiredHeight TAttribute<FOptionalSize> ?
//00000360 MaxDesiredWidth TAttribute<FOptionalSize> ?
//00000378 MaxDesiredHeight TAttribute<FOptionalSize> ?
//00000390 MinAspectRatio  TAttribute<FOptionalSize> ?
//000003A8 MaxAspectRatio  TAttribute<FOptionalSize> ?
//000003C0 SBox            ends

struct UE4$SBox : public UE4$SPanel {
												                                                     // 00000000 baseclass_0   SPanel ?
	sbyte                ChildSlot[0x00000060];                                                       // 000002A0 ChildSlot    SBox::FBoxSlot ?
	sbyte                WidthOverride[0x00000018];                                                   // 00000300 WidthOverride  TAttribute<FOptionalSize> ?
	sbyte                HeightOverride[0x00000018];                                                  // 00000318 HeightOverride TAttribute<FOptionalSize> ?
	sbyte                MinDesiredWidth[0x00000018];                                                 // 00000330 MinDesiredWidth TAttribute<FOptionalSize> ?
	sbyte                MinDesiredHeight[0x00000018];                                                // 00000348 MinDesiredHeight TAttribute<FOptionalSize> ?
	sbyte                MaxDesiredWidth[0x00000018];                                                 // 00000360 MaxDesiredWidth TAttribute<FOptionalSize> ?
	sbyte                MaxDesiredHeight[0x00000018];                                                // 00000378 MaxDesiredHeight TAttribute<FOptionalSize> ?
	sbyte                MinAspectRatio[0x00000018];                                                  // 00000390 MinAspectRatio TAttribute<FOptionalSize> ?
	sbyte                MaxAspectRatio[0x00000018];                                                  // 000003A8 MaxAspectRatio TAttribute<FOptionalSize> ?

	UE4$SWidget * getChildSlot() {
		uint64_t TMPBuffer = NULL;
		//000002A0 ChildSlot    SBox::FBoxSlot ?
		if (NULL == (TMPBuffer = (uint64_t)&ChildSlot[0]))
			return NULL;

		//00000000 SBox::FBoxSlot  struc ; (sizeof=0x60, align=0x8, copyof_8868)
		//00000000                                         ; XREF: SBox/r
		//00000000 baseclass_0     TSupportsOneChildMixin<SBox::FBoxSlot> ?
		//00000030 baseclass_30    TSupportsContentAlignmentMixin<SBox::FBoxSlot> ?
		//00000038 baseclass_38    TSupportsContentPaddingMixin<SBox::FBoxSlot> ?
		//00000060 SBox::FBoxSlot  ends
		TMPBuffer += 0x00000000;  // 指向  TSupportsOneChildMixin<SBox::FBoxSlot> ?

		//00000000 TSupportsOneChildMixin<SBox::FBoxSlot> struc ; (sizeof=0x30, align=0x8, copyof_5772)
		//00000000                                         ; XREF: SBox::FBoxSlot/r
		//00000000 baseclass_0     FChildren ?
		//00000010 baseclass_10    TSlotBase<SBox::FBoxSlot> ?
		//00000030 TSupportsOneChildMixin<SBox::FBoxSlot> ends

		TMPBuffer += 0x00000010;  // 指向  TSlotBase<SBox::FBoxSlot> ?

		//00000000 TSlotBase<SBox::FBoxSlot> struc ; (sizeof=0x20, align=0x8, copyof_5771)
		//00000000                                         ; XREF: TSupportsOneChildMixin<SBox::FBoxSlot>/r
		//00000000 baseclass_0     FSlotBase ?
		//00000020 TSlotBase<SBox::FBoxSlot> ends

		TMPBuffer += 0x00000000;  // 指向  baseclass_0     FSlotBase ?

		//00000000 FSlotBase       struc ; (sizeof=0x20, align=0x8, copyof_2696)
		//00000000                                         ; XREF: .data:FSlotBase `TSlotlessChildren<SDockTab>::GetSlotAt(int)'::`2'::NullSlot/r
		//00000000                                         ; .data:FSlotBase `TSlotlessChildren<SWidget>::GetSlotAt(int)'::`2'::NullSlot/r ...
		//00000000 vfptr           dq ?                    ; offset
		//00000008 RawParentPtr    dq ?                    ; offset
		//00000010 Widget          TSharedRef<SWidget,0> ?
		//00000020 FSlotBase       ends

		TMPBuffer += 0x00000010;  // 指向  Widget          TSharedRef<SWidget,0> ?

		//00000000 TSharedRef<SWidget,0> struc ; (sizeof=0x10, align=0x8, copyof_2681)
		//00000000                                         ; XREF: FSlotBase/r
		//00000000                                         ; FArrangedWidget/r ...
		//00000000 Object          dq ?                    ; XREF: SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+77A/w
		//00000000                                         ; SDockingTabWell::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+314/w ... ; offset
		//00000008 SharedReferenceCount SharedPointerInternals::FSharedReferencer<0> ?
		//00000008                                         ; XREF: SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &):loc_1408BFC23/w
		//00000008                                         ; SPopupLayer::OnArrangeChildren(FGeometry const &,FArrangedChildren &)+7D9/r ...
		//00000010 TSharedRef<SWidget,0> ends

		TMPBuffer += 0x00000000;  // 指向  Object          dq ? ; 

		return *(UE4$SWidget **)TMPBuffer;
	}

}; // StructSize == 0x000003C0

//00000000 FOptionalSize   struc ; (sizeof=0x4, align=0x4, copyof_7223)
//00000000                                         ; XREF: TAttribute<FOptionalSize>/r
//00000000 Size            dd ?
//00000004 FOptionalSize   ends

struct UE4$FOptionalSize {

	uint32_t   Size;
};

#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SRichTextBlock

	///** The text displayed in this text block */
	//TAttribute< FText > BoundText;

	///** The wrapped layout for this text block */
	//TUniquePtr< FSlateTextBlockLayout > TextLayoutCache;

	///** Default style used by the TextLayout */
	//FTextBlockStyle TextStyle;

	///** Highlight this text in the textblock */
	//TAttribute<FText> HighlightText;

	///** Whether text wraps onto a new line when it's length exceeds this width; if this value is zero or negative, no wrapping occurs. */
	//TAttribute<float> WrapTextAt;
	//
	///** True if we're wrapping text automatically based on the computed horizontal space for this widget */
	//TAttribute<bool> AutoWrapText;

	///** The wrapping policy we're using */
	//TAttribute<ETextWrappingPolicy> WrappingPolicy;

	///** The amount of blank space left around the edges of text area. */
	//TAttribute< FMargin > Margin;

	///** The amount to scale each lines height by. */
	//TAttribute< ETextJustify::Type > Justification; 

	///** How the text should be aligned with the margin. */
	//TAttribute< float > LineHeightPercentage;

	///** Prevents the text block from being smaller than desired in certain cases (e.g. when it is empty) */
	//TAttribute<float> MinDesiredWidth;

	///**  */
	//TSharedPtr<FRichTextLayoutMarshaller> Marshaller;

struct UE4$SRichTextBlock : public UE4$SWidget {
	sbyte                BoundText[0x00000030];                                                       //  BoundText    TAttribute<FText> ?
	sbyte                TextLayoutCache[0x00000008];                                                 //  TextLayoutCache TUniquePtr<FSlateTextBlockLayout,TDefaultDelete<FSlateTextBlockLayout> > ?
	sbyte                TextStyle[0x00000268];                                                       //  TextStyle    FTextBlockStyle ?   字体相关信息, 在样式结构中
	sbyte                HighlightText[0x00000030];                                                   //  HighlightText  TAttribute<FText> ?
	sbyte                WrapTextAt[0x00000018];                                                      //  WrapTextAt   TAttribute<float> ?
	sbyte                AutoWrapText[0x00000018];                                                    //  AutoWrapText  TAttribute<bool> ?
	sbyte                WrappingPolicy[0x00000018];                                                  //  WrappingPolicy TAttribute<enum ETextWrappingPolicy> ?
	sbyte                Margin[0x00000028];                                                          //  Margin     TAttribute<FMargin> ?
	sbyte                Justification[0x00000018];                                                   //  Justification  TAttribute<enum ETextJustify::Type> ?
	sbyte                LineHeightPercentage[0x00000018];                                            //  LineHeightPercentage TAttribute<float> ?
	sbyte                MinDesiredWidth[0x00000018];                                                 //  MinDesiredWidth TAttribute<float> ?

	///** Prevents the text block from being smaller than desired in certain cases (e.g. when it is empty) */
	//TAttribute<float> MinDesiredWidth;

	///**  */
	//TSharedPtr<FRichTextLayoutMarshaller> Marshaller;
};

#pragma endregion

#pragma region//---------------------------------------------------------------------------------------------特征分组: SButton


#pragma endregion





#pragma pack ()

#endif