# Plugins / LiveLinkCurveDebugUI

- module root: `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI`
- headers: 9; symbols: 95
- symbol kinds: class=8, delegate=2, function=7, member=24, prototype=54
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, InputCore, LiveLinkInterface, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Private/LiveLinkCurveDebugPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkCurveDebugUI, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkCurveDebugUI, Verbose, All);`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/ILiveLinkCurveDebugUIModule.h` (Public)


#### class `ILiveLinkCurveDebugUIModule`  
`class ILiveLinkCurveDebugUIModule : public IModuleInterface`  
_L11-39_
- inherits: `IModuleInterface`
- desc: Interface for messaging modules.
- L19 _public prototype_ `virtual void DisplayLiveLinkCurveDebugUI(FString& LiveLinkSubjectName) = 0;` — Display the LiveLinkCurveDebugUI, either spawned from a tab manager, or as a custom widget attached to our current viewport if the tab manager can not be used
- L23 _public prototype_ `virtual void HideLiveLinkCurveDebugUI() = 0;`
- L30 _public prototype_ `virtual void RegisterTabSpawner() = 0;` — Registers a tab spawner for the LiveLinkCurveDebugUI. @param WorkspaceGroup The workspace group to insert the tab into.
- L33 _public prototype_ `virtual void UnregisterTabSpawner() = 0;` — Unregisters the tab spawner for the LiveLinkCurveDebugUI.
- L38 _public function_ `virtual ~ILiveLinkCurveDebugUIModule()` — Virtual destructor.

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/LiveLinkCurveDebugUIModule.h` (Public)


#### class `FLiveLinkCurveDebugUIModule`  
`class FLiveLinkCurveDebugUIModule : public FSelfRegisteringExec , public ILiveLinkCurveDebugUIModule`  
_L15-67_
- inherits: `FSelfRegisteringExec,ILiveLinkCurveDebugUIModule`
- L21 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FSelfRegisteringExec interface
- L24 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `virtual void DisplayLiveLinkCurveDebugUI(FString& LiveLinkSubjectName) override;` — Functions to control UI
- L29 _public prototype_ `virtual void HideLiveLinkCurveDebugUI() override;`
- L33 _private prototype_ `virtual void RegisterTabSpawner() override;` — Our hooks into the Tab Spawn system
- L34 _private prototype_ `virtual void UnregisterTabSpawner() override;`
- L36 _private prototype_ `void RegisterSettings();`
- L37 _private prototype_ `void UnRegisterSettings();`
- L40 _private prototype_ `void DisplayThroughTab();` — Functions that do the real work of displaying the UI appropriately
- L41 _private prototype_ `void DisplayThroughViewportAdd();`
- L43 _private prototype_ `void SwitchToNextLiveLinkSubject();`
- L46 _private prototype_ `TSharedPtr<SLiveLinkCurveDebugUI> CreateDebugWidget();` — Functions to create what is needed internally
- L47 _private prototype_ `TSharedRef<SDockTab> MakeLiveLinkCurveDebugTab(const FSpawnTabArgs& Args);`
- L50 _private prototype_ `UWorld* GetWorldForDebugUIModule();` — Needed so we can spawn in a UUserWidget in this world
- L51 _private prototype_ `UGameViewportClient* GetGameViewportClientForDebugUIModule();`
- L54 _private prototype_ `bool AddWidgetToViewport();` — Adds/Removes our stored LiveLinkUserWidget to the viewport of the first local player
- L55 _private prototype_ `void RemoveWidgetFromViewport();`
- L57 _private prototype_ `float GetDPIScaleFromSettings();`
- L60 _private member_ `bool bForceDisplayThroughViewport;`
- L61 _private member_ `bool bHasRegisteredTabSpawners;`
- L64 _private member_ `FString LiveLinkSubjectNameToTrack;` — A cached version of what the SubjectName to supply to LiveLink. Gets passed into created widgets
- L66 _private member_ `TSharedPtr<SLiveLinkCurveDebugUI> LiveLinkUserWidget;`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/LiveLinkDebugCurveNodeBase.h` (Public)


#### class `FLiveLinkDebugCurveNodeBase`  
`class FLiveLinkDebugCurveNodeBase`  
_L9-27_
- L12 _public prototype_ `FLiveLinkDebugCurveNodeBase(FName InCurveName, float InCurveValue);`
- L13 _public function_ `virtual ~FLiveLinkDebugCurveNodeBase()`
- L16 _public function_ `virtual FText GetCurveName() const` — Name of the curve we are tracking
- L19 _public function_ `virtual float GetCurveValue() const` — Value of the curve we are tracking
- L22 _public prototype_ `virtual FSlateColor GetCurveFillColor() const;` — Color we should set the progress fill bar to be when rendering debug info for this curve
- L25 _protected member_ `FName CurveName;`
- L26 _protected member_ `float CurveValue;`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/LiveLinkDebuggerBlueprintLibrary.h` (Public)


#### class `ULiveLinkDebuggerBlueprintLibrary`  
`class ULiveLinkDebuggerBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L15 _private prototype_ `static void DisplayLiveLinkDebugger(FString SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkDebug")`
- L18 _private prototype_ `static void HideLiveLinkDebugger();` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkDebug")`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/LiveLinkDebuggerSettings.h` (Public)


#### class `ULiveLinkDebuggerSettings`  
`class ULiveLinkDebuggerSettings : public UObject`  
_L15-47_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- L21 _public prototype_ `ULiveLinkDebuggerSettings();`
- L32 _public member_ `FSlateColor MinBarColor;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkDebugger", meta= ( DisplayName = "Minimum Bar Color Value"))` — Color used when the CurveValue bar is at 0
- L36 _public member_ `FSlateColor MaxBarColor;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkDebugger", meta = (DisplayName = "Maximum Bar Color Value"))` — Color used when the CurveValueBar is at 1.0
- L40 _public member_ `float DPIScaleMultiplier;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLinkDebugger", meta = (DisplayName = "DPI Scale Multiplier"))` — This multiplier is used on the Viewport Widget version (IE: In Game) as it needs to be slightly more aggresive then the PC version
- L43 _public prototype_ `float GetDPIScaleBasedOnSize(FIntPoint Size) const;` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkDebugger")`
- L46 _public prototype_ `FSlateColor GetBarColorForCurveValue(float CurveValue) const;` — `UFUNCTION(BlueprintCallable, Category = "LiveLinkDebugger")`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/SLiveLinkCurveDebugUI.h` (Public)


#### class `SLiveLinkCurveDebugUI`  
`class SLiveLinkCurveDebugUI : public SUserWidget`  
_L13-73_
- inherits: `SUserWidget`
- L19 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSubjectNameChanged, FName);` — Delegate used to call back when this widget sets its own SubjectName from the LiveLink client instead of any supplied InitialLiveLinkSubjectName
- L21 _public function_ `SLATE_USER_ARGS(SLiveLinkCurveDebugUI) : _DPIScale(1.0f) , _InitialLiveLinkSubjectName(FName()) , _UpdateRate(0.0f) , _ShowLiveLinkSubjectNameHeader(true)`
- L27 _public prototype_ `SLATE_ARGUMENT(float, DPIScale) SLATE_ARGUMENT(FName, InitialLiveLinkSubjectName) SLATE_ARGUMENT(float, UpdateRate) SLATE_ARGUMENT(bool, ShowLiveLinkSubjectNameHeader) SLATE_EVENT(FOnSubjectNameChanged, OnSubjectNameChanged) SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L40 _public prototype_ `virtual void SetLiveLinkSubjectName(FName SubjectName);`
- L43 _public prototype_ `virtual void GetAllSubjectNames(TArray<FName>& OutSubjectNames) const;` — Gets all current LiveLink subject names from our internal LiveLink client and stores it in the OutSubjectNames parameter. Clears OutSubjectNames if no SubjectNames are found!
- L47 _public prototype_ `virtual void ChangeToNextValidLiveLinkSubjectName();` — If we don't have a suplied CachedLiveLinkSubjectName, we try to pull it from LiveLink by looking at All available subjects and picking the first one we find with curves to supply
- L50 _private prototype_ `FText GetLiveLinkSubjectNameHeader() const;`
- L52 _private prototype_ `void UpdateCurveData();`
- L55 _private prototype_ `TSharedRef<ITableRow> GenerateListRow(TSharedPtr<FLiveLinkDebugCurveNodeBase> InItem, const TSharedRef<STableViewBase>& InOwningTable);` — Called by the list view to generate a row widget from the supplied data
- L58 _private member_ `FName CachedLiveLinkSubjectName;` — Cached information to generate LiveLinkData
- L59 _private member_ `class ILiveLinkClient* CachedLiveLinkClient;`
- L62 _private member_ `TArray<TSharedPtr<FLiveLinkDebugCurveNodeBase>> CurveData;` — Actual generated data being used to generate items in the ListView
- L65 _private member_ `FOnSubjectNameChanged OnSubjectNameChanged;` — Callback we use if our widget updates its SubjectName
- L68 _private member_ `float UpdateRate;` — Used to limit how often we update curve data for performance
- L69 _private member_ `double NextQueuedUpdateTime;`
- L70 _private member_ `double NextUpdateTime;`
- L72 _private member_ `TSharedPtr<SListView<TSharedPtr<FLiveLinkDebugCurveNodeBase>>> DebugListView;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSubjectNameChanged, FName);` — Delegate used to call back when this widget sets its own SubjectName from the LiveLink client instead of any supplied InitialLiveLinkSubjectName

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/SLiveLinkCurveDebugUIListItem.h` (Public)


#### class `SLiveLinkCurveDebugUIListItem`  
`class SLiveLinkCurveDebugUIListItem : public SMultiColumnTableRow<TSharedPtr<FLiveLinkDebugCurveNodeBase>>`  
_L12-45_
- inherits: `SMultiColumnTableRow<TSharedPtr<FLiveLinkDebugCurveNodeBase>>`
- L16 _public member_ `static FName NAME_CurveName;`
- L17 _public member_ `static FName NAME_CurveValue;`
- L19 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkCurveDebugUIListItem) : _CurveInfo()`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L31 _public prototype_ `virtual FText GetCurveName() const;`
- L33 _public prototype_ `virtual TOptional<float> GetCurveValue() const;`
- L35 _public prototype_ `virtual FSlateColor GetProgressFillColor() const;`
- L37 _public prototype_ `const FSlateBrush* GetProgressBackgroundImage() const;`
- L40 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow overrides
- L44 _private member_ `TSharedPtr<FLiveLinkDebugCurveNodeBase> CurveInfo;`

### `Plugins/Animation/LiveLinkCurveDebugUI/Source/LiveLinkCurveDebugUI/Public/SLiveLinkCurveDebugUITab.h` (Public)


#### class `SLiveLinkCurveDebugUITab`  
`class SLiveLinkCurveDebugUITab : public SDockTab`  
_L12-45_
- inherits: `SDockTab`
- L17 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkCurveDebugUITab)`
- L20 _public prototype_ `SLATE_ARGUMENT(FName, InitialLiveLinkSubjectName) SLATE_END_ARGS() virtual void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `void SetLiveLinkSubjectName(FName SubjectName);`
- L28 _protected prototype_ `TSharedRef<SWidget> MakeComboButtonItemWidget(TSharedPtr<FString> StringItem);`
- L29 _protected prototype_ `void OnSelectionChanged(TSharedPtr<FString> StringItem, ESelectInfo::Type SelectInfo);`
- L30 _protected prototype_ `FText GetSelectedSubjectName() const;`
- L31 _protected prototype_ `void OnSubjectNameComboBoxOpened();`
- L33 _protected prototype_ `void RefreshSubjectNames();`
- L36 _protected prototype_ `void UpdateSubjectNameEditor(FName SubjectName);` — This is for when our subject name is updated by the underlying widget and we need to change our selected SubjectName
- L39 _protected member_ `TSharedPtr<SLiveLinkCurveDebugUI> MyDebugUI;` — Our embedded LiveLink Curve Debugger
- L41 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> SubjectNameComboBox;`
- L43 _protected member_ `TSharedPtr<FString> CurrentSelectedSubjectName;`
- L44 _protected member_ `TArray<TSharedPtr<FString>> SubjectNames;`
