#pragma once
//
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
//
#include <windows.h>					// Windows 头文件
//
#include <stdlib.h>
//
#include <stdint.h>

#pragma pack (1)

#pragma region//---------------------------------------------------------------------------------------------特征分组: FSlateApplication
typedef	void				FSlateApplication;

//00000000 FSlateApplication struc; (sizeof = 0x590, align = 0x10, copyof_17203)
//00000000 baseclass_0     FSlateApplicationBase ?
//00000120 PressedMouseButtons TSet<FKey, DefaultKeyFuncs<FKey, 0>, FDefaultSetAllocator> ?
//00000170 bAppIsActive    db ?
//00000171 bSlateWindowActive db ?
//00000172 bRenderOffScreen db ?
//00000173                 db ? ; undefined
//00000174 Scale           dd ?
#define UE4$FSlateApplication$Scale                  0x00000174
//00000178 DragTriggerDistance dd ?
//0000017C                 db ? ; undefined
//0000017D                 db ? ; undefined
//0000017E                 db ? ; undefined
//0000017F                 db ? ; undefined
//00000180 SlateWindows    TArray<TSharedRef<SWindow, 0>, TSizedDefaultAllocator<32> > ?
#define UE4$FSlateApplication$SlateWindows                  0x00000180 
//00000190 SlateVirtualWindows TArray<TSharedRef<SWindow, 0>, TSizedDefaultAllocator<32> > ?
//000001A0 ActiveTopLevelWindow TWeakPtr<SWindow, 0> ?
//000001B0 ActiveModalWindows TArray<TSharedPtr<SWindow, 0>, TSizedDefaultAllocator<32> > ?
//000001C0 WindowDestroyQueue TArray<TSharedRef<SWindow, 0>, TSizedDefaultAllocator<32> > ?
//000001D0 MenuStack       FMenuStack ?
//000002B0 CursorRadius    dd ?
//000002B4                 db ? ; undefined
//000002B5                 db ? ; undefined
//000002B6                 db ? ; undefined
//000002B7                 db ? ; undefined
//000002B8 Users           TArray<TSharedPtr<FSlateUser, 0>, TSizedDefaultAllocator<32> > ?
//000002C8 VirtualUsers    TArray<TWeakPtr<FSlateVirtualUserHandle, 0>, TSizedDefaultAllocator<32> > ?
//000002D8 MouseButtonDownResponsivnessThrottle FThrottleRequest ?
//000002DC UserInteractionResponsivnessThrottle FThrottleRequest ?
//000002E0 LastUserInteractionTime dq ?
//000002E8 LastUserInteractionTimeForThrottling dq ?
//000002F0 LastUserInteractionTimeUpdateEvent FSlateApplication::FSlateLastUserInteractionTimeUpdateEvent ?
//00000308 LastMouseMoveTime dq ?
//00000310 PopupSupport    FPopupSupport ?
//00000320 GameViewportWidget TWeakPtr<SViewport, 0> ?
//00000330 SlateSoundDevice TSharedPtr<ISlateSoundDevice, 0> ?
//00000340 CurrentTime     dq ?
//00000348 LastTickTime    dq ?
//00000350 AverageDeltaTime dd ?
//00000354 AverageDeltaTimeForResponsiveness dd ?
//00000358 OnExitRequested TBaseDelegate<void> ?
//00000368 WidgetReflectorPtr TWeakPtr<IWidgetReflector, 0> ?
//00000378 SourceCodeAccessDelegate TBaseDelegate<bool, FString const &, int, int> ?
//00000388 QuerySourceCodeAccessDelegate TBaseDelegate<bool> ?
//00000398 AssetAccessDelegate TBaseDelegate<bool, UObject *> ?
//000003A8 NumExternalModalWindowsActive dd ?
//000003AC                 db ? ; undefined
//000003AD                 db ? ; undefined
//000003AE                 db ? ; undefined
//000003AF                 db ? ; undefined
//000003B0 OnWindowActionNotifications TArray<TBaseDelegate<bool, TSharedRef<FGenericWindow, 0> const &, enum EWindowAction::Type>, TSizedDefaultAllocator<32> > ?
//000003C0 RootStyleNode   dq ? ; offset
//000003C8 bRequestLeaveDebugMode db ?
//000003C9 bLeaveDebugForSingleStep db ?
//000003CA                 db ? ; undefined
//000003CB                 db ? ; undefined
//000003CC                 db ? ; undefined
//000003CD                 db ? ; undefined
//000003CE                 db ? ; undefined
//000003CF                 db ? ; undefined
//000003D0 NormalExecutionGetter TAttribute<bool> ?
//000003E8 ModalWindowStackStartedDelegate TBaseDelegate<void> ?
//000003F8 ModalWindowStackEndedDelegate TBaseDelegate<void> ?
//00000408 bIsExternalUIOpened db ?
//00000409                 db ? ; undefined
//0000040A                 db ? ; undefined
//0000040B                 db ? ; undefined
//0000040C ThrottleHandle  FThrottleRequest ?
//00000410 DragIsHandled   db ?
//00000411                 db ? ; undefined
//00000412                 db ? ; undefined
//00000413                 db ? ; undefined
//00000414                 db ? ; undefined
//00000415                 db ? ; undefined
//00000416                 db ? ; undefined
//00000417                 db ? ; undefined
//00000418 SlateTextField  dq ? ; offset
//00000420 bIsFakingTouch  db ?
//00000421 bIsGameFakingTouch db ?
//00000422 bIsFakingTouched db ?
//00000423                 db ? ; undefined
//00000424                 db ? ; undefined
//00000425                 db ? ; undefined
//00000426                 db ? ; undefined
//00000427                 db ? ; undefined
//00000428 UnhandledKeyDownEventHandler TBaseDelegate<FReply, FKeyEvent const &> ?
//00000438 UnhandledKeyUpEventHandler TBaseDelegate<FReply, FKeyEvent const &> ?
//00000448 bTouchFallbackToMouse db ?
//00000449 bSoftwareCursorAvailable db ?
//0000044A bMenuAnimationsEnabled db ?
//0000044B                 db ? ; undefined
//0000044C                 db ? ; undefined
//0000044D                 db ? ; undefined
//0000044E                 db ? ; undefined
//0000044F                 db ? ; undefined
//00000450 AppIcon         dq ? ; offset
//00000458 ApplicationActivationStateChangedEvent FSlateApplication::FApplicationActivationStateChangedEvent ?
//00000470 VirtualDesktopRect FSlateRect ?
//00000480 NavigationConfig TSharedRef<FNavigationConfig, 0> ?
//00000490 SimulateGestures TBitArray<FDefaultBitArrayAllocator> ?
//000004B0 PreTickEvent    FSlateApplication::FSlateTickEvent ?
//000004C8 PostTickEvent   FSlateApplication::FSlateTickEvent ?
//000004E0 UserRegisteredEvent FSlateApplication::FUserRegisteredEvent ?
//000004F8 WindowBeingDestroyedEvent FSlateApplication::FOnWindowBeingDestroyed ?
//00000510 ModalLoopTickEvent FSlateApplication::FOnModalLoopTickEvent ?
//00000528 SlateTickCriticalSection FWindowsCriticalSection ?
//00000550 ProcessingInput dd ?
//00000554                 db ? ; undefined
//00000555                 db ? ; undefined
//00000556                 db ? ; undefined
//00000557                 db ? ; undefined
//00000558 InputPreProcessors FSlateApplication::InputPreProcessorsHelper ?
//00000580 InputManager    TSharedRef<ISlateInputManager, 0> ?
//00000590 FSlateApplication ends
#pragma endregion



#pragma region//---------------------------------------------------------------------------------------------特征分组: SCompoundWidget, SWidget

typedef	void				SCompoundWidget;

//00000000 SCompoundWidget struc; (sizeof = 0x388, align = 0x8, copyof_2714)
//00000000; XREF: SWindow / r
//00000000 baseclass_0     SWidget ?
//000002A0 ChildSlot       FSimpleSlot ?
#define UE4$SCompoundWidget$ChildSlot       0x000002A0
//00000300 ContentScale    TAttribute<FVector2D> ?
//00000320 ColorAndOpacity TAttribute<FLinearColor> ?
//00000348 ForegroundColor TAttribute<FSlateColor> ?
//00000388 SCompoundWidget ends


//00000000 FSimpleSlot     struc; (sizeof = 0x60, align = 0x8, copyof_2706)
//00000000; XREF: SCompoundWidget / r
//00000000 baseclass_0     TSupportsOneChildMixin<FSimpleSlot> ?
//00000030 baseclass_30    TSupportsContentAlignmentMixin<FSimpleSlot> ?
//00000038 baseclass_38    TSupportsContentPaddingMixin<FSimpleSlot> ?
//00000060 FSimpleSlot     ends


//00000000 FSlateWidgetPersistentState struc; (sizeof = 0x120, align = 0x8, copyof_2657)
//00000000; XREF: SWidget / r
//00000000 PaintParent     TWeakPtr<SWidget, 0> ?
//00000010 InitialClipState TOptional<FSlateClippingState> ?
//00000058 AllottedGeometry FGeometry ?
//00000090 DesktopGeometry FGeometry ?
//000000C8 CullingBounds   FSlateRect ?
//000000D8 WidgetStyle     FWidgetStyle ?
//00000108 CachedElementListNode dq ? ; offset
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





#pragma endregion






#pragma region//---------------------------------------------------------------------------------------------特征分组: SWindow
typedef	void	SWindow;

//00000000 SWindow         struc; (sizeof = 0xA70, align = 0x8, copyof_2716)
//00000000 baseclass_0     SCompoundWidget ?
//00000388 baseclass_388   FSlateInvalidationRoot ?
//00000710 MoveResizeZone  dd ? ; enum EWindowZone::Type
//00000714 MoveResizeStart FVector2D ?
//0000071C MoveResizeRect  FSlateRect ?
#define UE4$SWindow$MoveResizeRect       0x0000071C
//0000072C Type            dd ? ; enum EWindowType
#define UE4$SWindow$Type                 0x0000072C
//00000730 Title           TAttribute<FText> ?
#define UE4$SWindow$Title                0x00000730
//00000760 bDragAnywhere   db ?
//00000761                 db ? ; undefined
//00000762                 db ? ; undefined
//00000763                 db ? ; undefined
//00000764 Opacity         dd ?
//00000768 SizingRule      db ?
//00000769 AutoCenterRule  db ?
//0000076A                 db ? ; undefined
//0000076B                 db ? ; undefined
//0000076C TransparencySupport dd ? ; enum EWindowTransparency
//00000770 _bf770          db ?
//00000771 _bf771          db ?
//00000772 _bf772          db ?
//00000773                 db ? ; undefined
//00000774 WindowActivationPolicy dd ? ; enum EWindowActivationPolicy
//00000778 InitialDesiredScreenPosition FVector2D ?
//00000780 InitialDesiredSize FVector2D ?
//00000788 ScreenPosition  FVector2D ?
#define UE4$SWindow$ScreenPosition		 0x00000788
//00000790 PreFullscreenPosition FVector2D ?
//00000798 Size            FVector2D ?
#define UE4$SWindow$Size				 0x00000798
//000007A0 ViewportSize    FVector2D ?
//000007A8 Viewport        TWeakPtr<ISlateViewport, 0> ?
//000007B8 TitleBarSize    dd ?
//000007BC                 db ? ; undefined
//000007BD                 db ? ; undefined
//000007BE                 db ? ; undefined
//000007BF                 db ? ; undefined
//000007C0 Morpher         SWindow::FMorpher ?
//00000850 WindowZone      dd ? ; enum EWindowZone::Type
//00000854                 db ? ; undefined
//00000855                 db ? ; undefined
//00000856                 db ? ; undefined
//00000857                 db ? ; undefined
//00000858 TitleArea       TSharedPtr<SWidget, 0> ?
//00000868 ContentSlot     dq ? ; offset
//00000870 WidgetToFocusOnActivate TWeakPtr<SWidget, 0> ?
//00000880 WidgetFocusedOnDeactivate TWeakPtr<SWidget, 0> ?
//00000890 Style           dq ? ; offset
//00000898 WindowBackground dq ? ; offset
//000008A0 WindowBackgroundImage TSharedPtr<SImage, 0> ?
//000008B0 WindowBorder    TSharedPtr<SImage, 0> ?
//000008C0 WindowOutline   TSharedPtr<SImage, 0> ?
//000008D0 ContentAreaVBox TSharedPtr<SWidget, 0> ?
//000008E0 WindowContentVisibility EVisibility ?
//000008E1                 db ? ; undefined
//000008E2                 db ? ; undefined
//000008E3                 db ? ; undefined
//000008E4 SizeLimits      FWindowSizeLimits ?
//00000904                 db ? ; undefined
//00000905                 db ? ; undefined
//00000906                 db ? ; undefined
//00000907                 db ? ; undefined
//00000908 NativeWindow    TSharedPtr<FGenericWindow, 0> ?
#define UE4$SWindow$NativeWindow		0x00000908
//00000918 HittestGrid     TUniquePtr<FHittestGrid, TDefaultDelete<FHittestGrid> > ?
//00000920 OnWindowActivated TBaseDelegate<void> ?
//00000930 WindowActivatedEvent TMulticastDelegate<void> ?
//00000948 OnWindowDeactivated TBaseDelegate<void> ?
//00000958 WindowDeactivatedEvent TMulticastDelegate<void> ?
//00000970 OnWindowClosed  TBaseDelegate<void, TSharedRef<SWindow, 0> const &> ?
//00000980 WindowClosedEvent TMulticastDelegate<void, TSharedRef<SWindow, 0> const &> ?
//00000998 OnWindowMoved   TBaseDelegate<void, TSharedRef<SWindow, 0> const &> ?
//000009A8 RequestDestroyWindowOverride TBaseDelegate<void, TSharedRef<SWindow, 0> const &> ?
//000009B8 WindowOverlay   TSharedPtr<SOverlay, 0> ?
//000009C8 PopupLayer      TSharedPtr<SPopupLayer, 0> ?
//000009D8 FullWindowOverlayWidget TSharedPtr<SWidget, 0> ?
//000009E8 ParentWindowPtr TWeakPtr<SWindow, 0> ?
//000009F8 ChildWindows    TArray<TSharedRef<SWindow, 0>, TSizedDefaultAllocator<32> > ?
//00000A08 OnWorldSwitchHack TBaseDelegate<int, int> ?
//00000A18 bShouldShowWindowContentDuringOverlay db ?
//00000A19                 db ? ; undefined
//00000A1A                 db ? ; undefined
//00000A1B                 db ? ; undefined
//00000A1C ExpectedMaxWidth dd ?
//00000A20 ExpectedMaxHeight dd ?
//00000A24                 db ? ; undefined
//00000A25                 db ? ; undefined
//00000A26                 db ? ; undefined
//00000A27                 db ? ; undefined
//00000A28 TitleBar        TSharedPtr<IWindowTitleBar, 0> ?
//00000A38 LayoutBorder    FMargin ?
//00000A48 UserResizeBorder FMargin ?
//00000A58 bIsDrawingEnabled db ?
//00000A59                 db ? ; undefined
//00000A5A                 db ? ; undefined
//00000A5B                 db ? ; undefined
//00000A5C                 db ? ; undefined
//00000A5D                 db ? ; undefined
//00000A5E                 db ? ; undefined
//00000A5F                 db ? ; undefined
//00000A60 ActiveTimerHandle TWeakPtr<FActiveTimerHandle, 0> ?
//00000A70 SWindow         ends
#pragma endregion

























#pragma pack ()