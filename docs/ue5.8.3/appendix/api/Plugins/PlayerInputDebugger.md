# Plugins / PlayerInputDebugger

- module root: `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger`
- headers: 6; symbols: 185
- symbol kinds: class=6, enum=1, enumerator=4, function=6, member=109, prototype=53, struct=6
- PrivateDependencyModuleNames: ApplicationCore, CommonInput, CommonUI, Core, CoreUObject, EditorWidgets, Engine, EnhancedInput, GameplayTags, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, UMG, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/PlayerInputDebuggerModule.h` (Private)


#### class `FPlayerInputDebuggerModule`  
`class FPlayerInputDebuggerModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private prototype_ `void RegisterMenus();`
- L19 _private prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);`
- L21 _private member_ `FDelegateHandle MenusStartupHandle;`

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/SEnhancedInputTab.h` (Private)


#### struct `FEnhancedInputDisplayItem`  
`struct FEnhancedInputDisplayItem`  
_L15-40_
- desc: A single row in the Enhanced Input display: a context header, an IMC mode info row, or an action mapping row.
- L17 _public member_ `bool bIsHeader = false;`
- L18 _public member_ `bool bIsInputModeInfo = false;`
- L21 _public member_ `FText ContextName;` — Header fields
- L22 _public member_ `int32 Priority = 0;`
- L26 _public member_ `uint8 FilterOptionsOrdinal = 0;` — Input mode info row fields (appears once per IMC, directly after its header) Enums stored as uint8 to avoid pulling InputMappingContext.h into this header.
- L27 _public member_ `uint8 RegTrackingModeOrdinal = 0;` — EMappingContextRegistrationTrackingMode
- L28 _public member_ `FText ModeQueryText;`
- L29 _public member_ `bool bShouldApplyModeFilter = false;` — False when DoNotFilter or global filtering is disabled
- L30 _public member_ `bool bPassesModeFilter = false;` — Only meaningful when bShouldApplyModeFilter is true
- L33 _public member_ `FText ActionName;` — Action mapping row fields
- L34 _public member_ `FKey BoundKey;`
- L35 _public member_ `uint8 TriggerEventOrdinal = 0;` — ETriggerEvent stored as uint8 to avoid including InputAction.h in header
- L36 _public member_ `FText ValueText;`
- L39 _public member_ `TWeakObjectPtr<const UObject> WeakAsset;` — Asset reference for hyperlink navigation and details panel (IMC for headers/info rows, IA for action rows).

#### class `SEnhancedInputTab`  
`class SEnhancedInputTab : public SCompoundWidget`  
_L44-97_
- inherits: `SCompoundWidget`
- desc: Tab showing active Enhanced Input mapping contexts, their actions, bound keys, trigger states and values for the selected player controller. Refreshes every frame.
- L47 _public function_ `SLATE_BEGIN_ARGS(SEnhancedInputTab)`
- L48 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<APlayerController>, PlayerController) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L52 _public prototype_ `virtual ~SEnhancedInputTab();`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L55 _public prototype_ `void SetPlayerController(APlayerController* PC);`
- L58 _private prototype_ `void RebuildDisplayItems();`
- L59 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FEnhancedInputDisplayItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L62 _private prototype_ `void RemoveFilterContext(int32 Index);` — Context filter helpers
- L63 _private prototype_ `void RebuildFilterTagsWidget();`
- L66 _private prototype_ `void RemoveFilterAction(int32 Index);` — Action filter helpers
- L67 _private prototype_ `void RebuildActionFilterTagsWidget();`
- L70 _private prototype_ `TSharedRef<SWidget> MakeKeyFilterMenuContent();` — Key type filter — dropdown menu content for the Key column header
- L72 _private prototype_ `void RebuildDetails();`
- L74 _private member_ `TWeakObjectPtr<APlayerController> WeakPC;`
- L75 _private member_ `TArray<TSharedPtr<FEnhancedInputDisplayItem>> DisplayItems;`
- L76 _private member_ `TSharedPtr<SListView<TSharedPtr<FEnhancedInputDisplayItem>>> ListView;`
- L79 _private member_ `TArray<TWeakObjectPtr<UInputMappingContext>> FilterContexts;` — Contexts to show; empty = show all.
- L80 _private member_ `TSharedPtr<SBox> FilterTagsContainer;`
- L83 _private member_ `TArray<TWeakObjectPtr<UInputAction>> FilterActions;` — Actions to show; empty = show all.
- L84 _private member_ `TSharedPtr<SBox> ActionFilterTagsContainer;`
- L87 _private member_ `bool bShowKeyboardKeys = true;` — Key type visibility flags (default all visible)
- L88 _private member_ `bool bShowGamepadKeys = true;`
- L89 _private member_ `bool bShowTouchKeys = true;`
- L92 _private member_ `TSharedPtr<SEditableTextBox> ProfileIdInput;` — Mappable Key Profiles section
- L95 _private member_ `TSharedPtr<FEnhancedInputDisplayItem> SelectedItem;` — Selection and details panel
- L96 _private member_ `TSharedPtr<SBox> DetailsBox;`

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/SGlobalInputInfoSection.h` (Private)


#### struct `FGlobalStackRow`  
`struct FGlobalStackRow`  
_L13-19_
- desc: Stack row used by the global input overview.
- L15 _public member_ `int32 Priority = 0;`
- L16 _public member_ `FString ComponentName;`
- L17 _public member_ `FString OwnerName;`
- L18 _public member_ `bool bIsBlockingComponent = false;`

#### class `SGlobalInputInfoSection`  
`class SGlobalInputInfoSection : public SCompoundWidget`  
_L26-52_
- inherits: `SCompoundWidget`
- desc: Persistent collapsible section shown at the top of the debugger window regardless of which tab is active. Displays: • Currently focused Slate widget • Input Configuration (input mode, mouse settings, CommonUI state) • Input Component Stack
- L29 _public function_ `SLATE_BEGIN_ARGS(SGlobalInputInfoSection)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `virtual ~SGlobalInputInfoSection();`
- L34 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L36 _public prototype_ `void SetPlayerController(APlayerController* PC);`
- L39 _private prototype_ `void RebuildStackRows();`
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateStackRow(TSharedPtr<FGlobalStackRow> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L42 _private member_ `TWeakObjectPtr<APlayerController> WeakPC;`
- L45 _private member_ `TArray<TSharedPtr<FGlobalStackRow>> StackRows;` — Input Component Stack section
- L46 _private member_ `TSharedPtr<SListView<TSharedPtr<FGlobalStackRow>>> StackListView;`
- L49 _private member_ `FString CachedInputConfigString;` — Active Input Config — cached from UCommonUIActionRouterBase::OnActiveInputConfigChanged()
- L50 _private member_ `FDelegateHandle InputConfigChangedHandle;`
- L51 _private member_ `TWeakObjectPtr<UCommonUIActionRouterBase> WeakRouter;`

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/SInputDevicesTab.h` (Private)


#### struct `FKnownDevice`  
`struct FKnownDevice`  
_L15-20_
- desc: Cached record for a device that has been seen at least once. Retained even after disconnection so it stays visible in the list.
- L17 _public member_ `FPlatformUserId UserId;`
- L18 _public member_ `FHardwareDeviceIdentifier HardwareId;`
- L19 _public member_ `EInputDeviceConnectionState LastState = EInputDeviceConnectionState::Unknown;`

#### struct `FDeviceListItem`  
`struct FDeviceListItem`  
_L23-30_
- desc: A single item in the device list view — either a platform-user group header or a device row.
- L25 _public member_ `bool bIsUserHeader = false;`
- L26 _public member_ `FPlatformUserId UserId;`
- L27 _public member_ `FInputDeviceId DeviceId;`
- L28 _public member_ `bool bAnyConnected = false;` — header tint: green if any device still connected
- L29 _public member_ `int32 DeviceCount = 0;` — only meaningful for header items

#### class `SInputDevicesTab`  
`class SInputDevicesTab : public SCompoundWidget`  
_L36-70_
- inherits: `SCompoundWidget`
- desc: Tab that shows input hardware devices per platform user. Devices remain visible after disconnecting, shown with a "Disconnected" state.
- L39 _public function_ `SLATE_BEGIN_ARGS(SInputDevicesTab)`
- L40 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `virtual ~SInputDevicesTab();`
- L45 _public function_ `void SetPlayerController(APlayerController* PC)`
- L48 _private prototype_ `void RebuildDeviceList();`
- L49 _private prototype_ `void RebuildDetails();`
- L50 _private prototype_ `TSharedRef<ITableRow> OnGenerateDeviceRow(TSharedPtr<FDeviceListItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L51 _private prototype_ `void OnDeviceConnectionChanged(EInputDeviceConnectionState NewState, FPlatformUserId UserId, FInputDeviceId DeviceId);`
- L52 _private prototype_ `void OnHardwareDeviceChanged(FPlatformUserId UserId, FInputDeviceId DeviceId);`
- L53 _private prototype_ `void OnDevicePairingChanged(FInputDeviceId DeviceId, FPlatformUserId NewUserId, FPlatformUserId OldUserId);`
- L55 _private member_ `TArray<TSharedPtr<FDeviceListItem>> DeviceDisplayItems;`
- L56 _private member_ `TSharedPtr<SListView<TSharedPtr<FDeviceListItem>>> DeviceListView;`
- L57 _private member_ `TSharedPtr<SBox> DetailsBox;`
- L58 _private member_ `TOptional<FInputDeviceId> SelectedDeviceId;`
- L59 _private member_ `FDelegateHandle ConnectionChangedHandle;`
- L60 _private member_ `FDelegateHandle HardwareDeviceChangedHandle;`
- L61 _private member_ `FDelegateHandle PairingChangeHandle;`
- L62 _private member_ `TMap<FInputDeviceId, TSharedPtr<FKnownDevice>> KnownDevices;`
- L63 _private member_ `TWeakObjectPtr<APlayerController> WeakPC;`
- L66 _private member_ `TArray<TSharedPtr<FHardwareDeviceIdentifier>> AvailableHardwareDevices;` — Simulated descriptor support
- L67 _private member_ `TMap<FInputDeviceId, FHardwareDeviceIdentifier> ActiveSimulatedDescriptors;`
- L69 _private member_ `TMap<FInputDeviceId, TSharedPtr<FHardwareDeviceIdentifier>> PendingSimDescriptors;` — Per-device pending selection in the inline sim descriptor combo box.

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/SPlayerInputDebugger.h` (Private)


#### struct `FPlayerControllerEntry`  
`struct FPlayerControllerEntry`  
_L20-24_
- desc: Entry in the player controller dropdown.
- L22 _public member_ `TWeakObjectPtr<APlayerController> PC;`
- L23 _public member_ `FText DisplayName;`

#### class `SPlayerInputDebugger`  
`class SPlayerInputDebugger : public SCompoundWidget`  
_L29-69_
- inherits: `SCompoundWidget`
- desc: Root widget for the Player Input Debugger window. Contains a player controller selector, a persistent global info section, and three dockable sub-tabs managed by a local FTabManager.
- L32 _public function_ `SLATE_BEGIN_ARGS(SPlayerInputDebugger)`
- L34 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SDockTab>, ParentTab) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The nomad SDockTab that hosts this widget. Required to create the local tab manager.
- L38 _public prototype_ `virtual ~SPlayerInputDebugger();`
- L41 _private prototype_ `void RefreshPlayerControllers(const bool bIsPlayEnding = false);`
- L42 _private prototype_ `void OnBeginPIE(const bool bIsSimulating);`
- L43 _private prototype_ `void OnEndPIE(const bool bIsSimulating);`
- L44 _private prototype_ `void OnGameModePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);`
- L45 _private prototype_ `void OnGameModeLogout(AGameModeBase* GameMode, AController* Exiting);`
- L46 _private prototype_ `void OnPCSelected(TSharedPtr<FPlayerControllerEntry> Entry, ESelectInfo::Type SelectInfo);`
- L47 _private prototype_ `TSharedRef<SWidget> MakePCComboEntry(TSharedPtr<FPlayerControllerEntry> Entry);`
- L48 _private prototype_ `FText GetSelectedPCText() const;`
- L49 _private prototype_ `void SelectEntry(TSharedPtr<FPlayerControllerEntry> Entry);`
- L50 _private prototype_ `void OnParentTabClosed(TSharedRef<SDockTab> ClosedTab);`
- L52 _private member_ `TArray<TSharedPtr<FPlayerControllerEntry>> PCEntries;`
- L53 _private member_ `TSharedPtr<FPlayerControllerEntry> SelectedEntry;`
- L55 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FPlayerControllerEntry>>> PCCombo;`
- L57 _private member_ `TSharedPtr<SPlayerInputEventsTab> PlayerInputEventsTab;`
- L58 _private member_ `TSharedPtr<SInputDevicesTab> DevicesTab;`
- L59 _private member_ `TSharedPtr<SEnhancedInputTab> EnhancedInputTab;`
- L60 _private member_ `TSharedPtr<SGlobalInputInfoSection> GlobalInfoSection;`
- L62 _private member_ `TSharedPtr<FTabManager> TabManager;`
- L63 _private member_ `TSharedPtr<FTabManager::FLayout> TabLayout;`
- L65 _private member_ `FDelegateHandle BeginPIEHandle;`
- L66 _private member_ `FDelegateHandle EndPIEHandle;`
- L67 _private member_ `FDelegateHandle PostLoginHandle;`
- L68 _private member_ `FDelegateHandle LogoutHandle;`

### `Plugins/Experimental/PlayerInputDebugger/Source/PlayerInputDebugger/Private/SPlayerInputEventsTab.h` (Private)


#### enum `EInputEventSource`  
`enum class EInputEventSource : uint8`  
_L14-20_
- desc: Discriminates each log entry in the combined Input Events tab.
- L16 _public enumerator_ `Slate` — from FSlateDebugging::InputEvent
- L17 _public enumerator_ `SlateMouseCapture` — from FSlateDebugging::MouseCaptureEvent
- L18 _public enumerator_ `Player` — from FPlayerInputDebugging::OnPlayerInputEventExecuted
- L19 _public enumerator_ `PlayerFlush` — flush marker from FPlayerInputDebugging::OnPlayerInputFlushed

#### struct `FUnifiedInputEventRecord`  
`struct FUnifiedInputEventRecord`  
_L23-55_
- desc: A single entry in the combined input event log.
- L25 _public member_ `uint32 FrameNumber = 0;`
- L26 _public member_ `EInputEventSource Source = EInputEventSource::Slate;`
- L29 _public member_ `ESlateDebuggingInputEvent SlateEventType = ESlateDebuggingInputEvent::MAX;` — ── Slate fields ─────────────────────────────────────────────────────────
- L30 _public member_ `FKey Key;`
- L31 _public member_ `float RawValue = 0.f;`
- L32 _public member_ `FString HandlerWidgetType;`
- L33 _public member_ `FString UserWidgetName;` — nearest UUserWidget class name, if any
- L34 _public member_ `TWeakObjectPtr<UObject> UserWidgetBlueprint;` — ClassGeneratedBy for hyperlink
- L35 _public member_ `FString AdditionalContent;`
- L36 _public member_ `bool bReplyHandled = false;` — Slate: reply handled; SlateMouseCapture: true=captured, false=lost
- L39 _public member_ `FString PlayerControllerName;` — ── Player fields ─────────────────────────────────────────────────────────
- L40 _public member_ `FString ActionName;`
- L41 _public member_ `TWeakObjectPtr<UObject> ActionAsset;`
- L42 _public member_ `FString InputComponentName;`
- L43 _public member_ `int32 InputComponentPriority = 0;`
- L44 _public member_ `FString OwnerName;`
- L45 _public member_ `TWeakObjectPtr<UObject> OwnerBlueprint;`
- L46 _public member_ `FString ListeningObjectName;`
- L47 _public member_ `TWeakObjectPtr<UObject> ListeningObjectBlueprint;`
- L48 _public member_ `FVector InputValue = FVector::ZeroVector;`
- L54 _public member_ `FString ScriptCallstack;` — ── Flush fields ────────────────────────────────────────────────────────── Script (Blueprint VM) callstack captured at the moment the flush happened, so the user can see what actually triggered it. Empty if the flush wasn't invoked from script.

#### class `SPlayerInputEventsTab`  
`class SPlayerInputEventsTab : public SCompoundWidget`  
_L59-104_
- inherits: `SCompoundWidget`
- desc: Combined Input Events tab: Slate input events (FSlateDebugging::InputEvent) and Player input events (FPlayerInputDebugging) in a single clickable log.
- L62 _public function_ `SLATE_BEGIN_ARGS(SPlayerInputEventsTab)`
- L63 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L66 _public prototype_ `virtual ~SPlayerInputEventsTab();`
- L68 _public prototype_ `void SetPlayerController(APlayerController* PC);`
- L71 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FUnifiedInputEventRecord> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L72 _private prototype_ `void AppendRecord(TSharedPtr<FUnifiedInputEventRecord> Record);`
- L73 _private prototype_ `void RebuildDetails();`
- L74 _private prototype_ `void OnBeginPIE(const bool bIsSimulating);`
- L77 _private prototype_ `void OnSlateInputEvent(const FSlateDebuggingInputEventArgs& EventArgs);`
- L78 _private prototype_ `void OnSlateMouseCaptureEvent(const FSlateDebuggingMouseCaptureEventArgs& EventArgs);`
- L79 _private member_ `FDelegateHandle SlateInputEventHandle;`
- L80 _private member_ `FDelegateHandle SlateMouseCaptureHandle;`
- L84 _private prototype_ `void OnPlayerInputEventExecuted(const UPlayerInput* PlayerInput, const UE::Input::FPlayerInputDebuggingArgs& Args);`
- L85 _private prototype_ `void OnPlayerInputFlushed(const UPlayerInput* PlayerInput);`
- L86 _private member_ `FDelegateHandle EventExecutedHandle;`
- L87 _private member_ `FDelegateHandle FlushedHandle;`
- L90 _private member_ `FDelegateHandle BeginPIEHandle;`
- L91 _private member_ `TWeakPtr<SWidget> WeakSelfWidget;` — used to identify our window for event filtering
- L93 _private member_ `TArray<TSharedPtr<FUnifiedInputEventRecord>> LogItems;`
- L94 _private member_ `TSharedPtr<SListView<TSharedPtr<FUnifiedInputEventRecord>>> ListView;`
- L95 _private member_ `bool bAutoScroll = true;`
- L96 _private member_ `bool bIgnoreDebuggerWindowEvents = true;`
- L97 _private member_ `bool bFilterZeroLegacyInputs = true;`
- L98 _private member_ `bool bShowSlateMouseFocusEvents = false;`
- L100 _private member_ `TSharedPtr<FUnifiedInputEventRecord> SelectedItem;`
- L101 _private member_ `TSharedPtr<SBox> DetailsBox;`
- L103 _private member_ `static constexpr int32 MaxLogEntries = 1024;`
