# Plugins / EOSOverlayInputProvider

- module root: `Plugins/Online/EOSOverlayInputProvider/Source/EOSOverlayInputProvider`
- headers: 2; symbols: 48
- symbol kinds: class=2, function=10, member=9, prototype=25, struct=1, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EOSSDK, EOSShared, Engine, InputCore, Slate, SlateCore

### `Plugins/Online/EOSOverlayInputProvider/Source/EOSOverlayInputProvider/Private/EOSOverlayInputProviderModule.h` (Private)


#### class `FEOSOverlayInputProviderModule`  
`class FEOSOverlayInputProviderModule : public IModuleInterface`  
_L8-32_
- inherits: `IModuleInterface`
- L11 _public prototype_ `FEOSOverlayInputProviderModule() = default;`
- L12 _public prototype_ `~FEOSOverlayInputProviderModule() = default;`
- L15 _private prototype_ `void StartupTicker();`
- L16 _private prototype_ `void ShutdownTicker();`
- L17 _private prototype_ `bool Tick(float);`
- L20 _private prototype_ `virtual void StartupModule() override;`
- L21 _private prototype_ `virtual void ShutdownModule() override;`
- L24 _private prototype_ `bool IsRenderReady();`
- L27 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L29 _private member_ `bool bRenderReady = false;`
- L31 _private member_ `TSharedPtr<FEOSOverlayInputProviderPreProcessor> InputPreprocessor;`

### `Plugins/Online/EOSOverlayInputProvider/Source/EOSOverlayInputProvider/Private/EOSOverlayInputProviderPreProcessor.h` (Private)


#### struct `FEOSInputState`  
`struct FEOSInputState : EOS_UI_ReportInputStateOptions`  
_L14-89_
- inherits: `EOS_UI_ReportInputStateOptions`
- L16 _public function_ `FEOSInputState()`
- L34 _public function_ `FEOSInputState& WithButtonDownFlags(const EOS_UI_EInputStateButtonFlags InButtonDownFlags)`
- L40 _public function_ `FEOSInputState& WithMouseButtonDown(const bool InMouseButtonDown)`
- L46 _public function_ `FEOSInputState& WithMousePosX(const uint32_t InMousePosX)`
- L52 _public function_ `FEOSInputState& WithMousePosY(const uint32_t InMousePosY)`
- L58 _public function_ `FEOSInputState& WithGamepadIndex(const uint32_t InGamepadIndex)`
- L64 _public function_ `FEOSInputState& WithLeftStick(const float X, const float Y)`
- L71 _public function_ `FEOSInputState& WithRightStick(const float X, const float Y)`
- L78 _public function_ `FEOSInputState& WithLeftTrigger(const float InLeftTrigger)`
- L84 _public function_ `FEOSInputState& WithRightTrigger(const float InRightTrigger)`

#### class `FEOSOverlayInputProviderPreProcessor`  
`class FEOSOverlayInputProviderPreProcessor : public IInputProcessor , public TSharedFromThis<FEOSOverlayInputProviderPreProcessor, ESPMode::ThreadSafe>`  
_L91-134_
- inherits: `IInputProcessor,TSharedFromThis<FEOSOverlayInputProviderPreProcessor,ESPMode::ThreadSafe>`
- L96 _public prototype_ `void Initialize();`
- L98 _public prototype_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override;`
- L99 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L100 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L101 _public prototype_ `virtual bool HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L102 _public prototype_ `virtual bool HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L104 _public prototype_ `virtual bool HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent) override;`
- L105 _public prototype_ `virtual bool HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L106 _public prototype_ `virtual bool HandleMouseButtonDoubleClickEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent) override;`
- L107 _public prototype_ `virtual bool HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent) override;`
- L108 _public prototype_ `virtual bool HandleMotionDetectedEvent(FSlateApplication& SlateApp, const FMotionEvent& MotionEvent) override;`
- L111 _private prototype_ `void OnPlatformCreated(const IEOSPlatformHandlePtr& PlatformHandlePtr);`
- L112 _private prototype_ `void OnPreReleasePlatform(const EOS_HPlatform& PlatformHandle);`
- L114 _private prototype_ `virtual void HandleInput(const FEOSInputState& NewInputState);`
- L115 _private prototype_ `bool ProcessInputEvent(const FEOSInputState& NewInputState);`
- L116 _private prototype_ `FEOSInputState& GetCurrentInputState(uint32_t GamepadIndex);`
- L117 _private prototype_ `const TMap<FKey, EOS_UI_EInputStateButtonFlags>& GetUEKeyToEOSKeyMap();`
- L120 _private typedef_ `typedef TEOSGlobalCallback<EOS_UI_OnDisplaySettingsUpdatedCallback, EOS_UI_OnDisplaySettingsUpdatedCallbackInfo, FEOSOverlayInputProviderPreProcessor> FOnDisplaySettingsUpdatedCallback;`
- L122 _private member_ `TMap<EOS_HPlatform, EOS_NotificationId> DisplaySettingsUpdatedIdPerPlatform;`
- L123 _private member_ `TUniquePtr<FOnDisplaySettingsUpdatedCallback> DisplaySettingsUpdatedCallback;`
- L126 _private member_ `bool bIsExclusiveInput = false;` — True if the EOS overlay is open in exclusive input mode
- L129 _private member_ `bool bIsReportInputStateSupported = true;` — False if we have received an EOS_NotImplemented from EOS_UI_ReportInputState
- L131 _private member_ `bool bIsRenderReady = false;`
- L133 _private member_ `TMap<uint32_t, FEOSInputState> CurrentInputStates;`
