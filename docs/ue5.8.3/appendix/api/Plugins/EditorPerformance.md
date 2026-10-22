# Plugins / EditorPerformance

- module root: `Plugins/Experimental/EditorPerformance/Source/EditorPerformance`
- headers: 6; symbols: 232
- symbol kinds: class=10, delegate=2, enum=8, enumerator=34, function=7, macro=1, member=98, prototype=68, typedef=4
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, CrashDiagnostics, DerivedDataCache, EditorFramework, EditorSubsystem, EditorWidgets, Engine, InputCore, MessageLog, OutputLog, Slate, SlateCore, StallLogSubsystem, StudioTelemetry, ToolMenus, ToolWidgets, TypedElementFramework, UnrealEd, Virtualization, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Private/SEditorDiagnosticsTab.h` (Private)


#### class `FEditorDiagnosticsCommands`  
`class FEditorDiagnosticsCommands : public TCommands<FEditorDiagnosticsCommands>`  
_L13-26_
- inherits: `TCommands<FEditorDiagnosticsCommands>`
- L16 _public prototype_ `FEditorDiagnosticsCommands();`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L23 _public member_ `TSharedPtr<FUICommandInfo> SetShowActivityMonitor;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> SetShowStalls;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> SetShowCrashes;`

#### class `SEditorDiagnosticsTab`  
`class SEditorDiagnosticsTab : public SDockTab`  
_L28-47_
- inherits: `SDockTab`
- L31 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _protected prototype_ `TSharedRef<SWidget> CreateToolBar();`
- L36 _protected prototype_ `TSharedRef<SWidget> CreateActivityMonitorPanel();`
- L37 _protected prototype_ `TSharedRef<SWidget> CreateStallLogPanel();`
- L38 _protected prototype_ `TSharedRef<SWidget> CreateCrashesLogPanel();`
- L40 _protected prototype_ `void SetShowActivityMonitor();`
- L41 _protected prototype_ `void SetShowStalls();`
- L42 _protected prototype_ `void SetShowCrashes();`
- L45 _private member_ `TWeakPtr<SBorder> ContentBorder;`
- L46 _private member_ `TWeakPtr<FUICommandInfo> SelectedCommand;`

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Private/SEditorPerformanceDialogs.h` (Private)


#### enum `EEditorPerformanceNotificationOptions`  
`enum class EEditorPerformanceNotificationOptions : uint8`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `Notify`
- L21 _public enumerator_ `Ignore`

#### enum `EEditorPerformanceFilterOptions`  
`enum class EEditorPerformanceFilterOptions : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `ShowAll`
- L28 _public enumerator_ `WarningsOnly`

#### class `SEditorPerformanceReportDialog`  
`class SEditorPerformanceReportDialog : public SCompoundWidget`  
_L32-56_
- inherits: `SCompoundWidget`
- L34 _private member_ `static const TCHAR* SettingsMenuName;`
- L36 _private function_ `SLATE_BEGIN_ARGS(SEditorPerformanceReportDialog)`
- L39 _private prototype_ `virtual ~SEditorPerformanceReportDialog();`
- L41 _private prototype_ `void Construct(const FArguments& InArgs);`
- L45 _private prototype_ `EActiveTimerReturnType UpdateGridPanels(double InCurrentTime, float InDeltaTime);`
- L47 _private prototype_ `TSharedRef<SWidget> GetKPIGridPanel();`
- L48 _private prototype_ `TSharedRef<SWidget> GetHintGridPanel();`
- L50 _private prototype_ `UToolMenu* RegisterSettingsMenu();`
- L51 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenuWidget();`
- L53 _private member_ `SVerticalBox::FSlot* KPIGridSlot = nullptr;`
- L54 _private member_ `SVerticalBox::FSlot* HintGridSlot = nullptr;`
- L55 _private member_ `uint32 CurrentHintIndex = 0;`

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Private/SEditorPerformanceStatusBar.h` (Private)


#### enum `EEditorPerformanceState`  
`enum class EEditorPerformanceState : uint8`  
_L22-27_
- L24 _public enumerator_ `Good`
- L25 _public enumerator_ `Warnings`
- L26 _public enumerator_ `Critical`

#### class `SEditorPerformanceStatusBarWidget`  
`class SEditorPerformanceStatusBarWidget : public SCompoundWidget`  
_L29-56_
- inherits: `SCompoundWidget`
- L31 _private function_ `SLATE_BEGIN_ARGS(SEditorPerformanceStatusBarWidget)`
- L32 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L37 _private prototype_ `static FReply ViewPerformanceReport_Clicked();`
- L39 _private prototype_ `const FSlateBrush* GetStatusIcon() const;`
- L40 _private prototype_ `const FSlateBrush* GetStatusBadgeIcon() const;`
- L41 _private prototype_ `FText GetStatusToolTipText() const;`
- L42 _private prototype_ `const FButtonStyle* GetButtonStyle() const;`
- L44 _private prototype_ `void UpdateState();`
- L46 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;`
- L47 _private member_ `EEditorPerformanceState EditorPerformanceState= EEditorPerformanceState::Good;`
- L48 _private member_ `FText EditorPerformanceStateMessage;`
- L49 _private member_ `FText CurrentNotificationMessage;`
- L50 _private member_ `FName CurrentNotificationName;`
- L51 _private member_ `TArray<FName> AcknowledgedNotifications;`
- L52 _private member_ `TMap<FName, double> NotificationLastShownTimes;`
- L53 _private member_ `uint32 WarningCount = 0;`
- L55 _private member_ `TSharedPtr<SButton> StatusBarButton;`

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Private/TedsEditorPerformanceFactory.h` (Private)


#### class `UTedsEditorPerformanceFactory`  
`class UTedsEditorPerformanceFactory : public UEditorDataStorageFactory`  
_L11-24_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L16 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L18 _public function_ `UE::Editor::DataStorage::QueryHandle GetDiagnosticWarningQueryHandle() const`
- L19 _public function_ `UE::Editor::DataStorage::QueryHandle GetDiagnosticCriticalQueryHandle() const`
- L22 _private member_ `UE::Editor::DataStorage::QueryHandle DiagnosticWarningQueryHandle = UE::Editor::DataStorage::InvalidQueryHandle;`
- L23 _private member_ `UE::Editor::DataStorage::QueryHandle DiagnosticCriticalQueryHandle = UE::Editor::DataStorage::InvalidQueryHandle;`

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Public/EditorPerformanceModule.h` (Public)


#### class `FEditorPerformanceModule`  
`class FEditorPerformanceModule : public IModuleInterface`  
_L24-142_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for EditorPerformance
- L41 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L46 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L48 _public prototype_ `TSharedRef<SWidget> CreateStatusBarWidget();`
- L49 _public prototype_ `void ShowPerformanceReportTab();`
- L51 _public prototype_ `const FKPIRegistry& GetKPIRegistry() const;`
- L52 _public prototype_ `const FString& GetKPIProfileName() const;`
- L54 _public prototype_ `bool RecordInsightsSnapshot(const FKPIValue& Value);`
- L55 _public prototype_ `bool RecordTelemetryEvent(const FKPIValue& Value);`
- L56 _public prototype_ `bool IsHotLocalCacheCase() const;`
- L57 _public prototype_ `FEditorPerformanceModule::EEditorState GetEditorState() const;`
- L59 _public prototype_ `DECLARE_EVENT(FEditorPerformanceModule, FPerformanceStateChangedEvent);`
- L60 _public function_ `FPerformanceStateChangedEvent& GetOnPerformanceStateChanged()`
- L63 _private prototype_ `TSharedRef<SDockTab> CreatePerformanceReportTab(const FSpawnTabArgs& Args);`
- L64 _private member_ `TWeakPtr<SDockTab> PerformanceReportTab;`
- L66 _private prototype_ `void InitializeEditor();`
- L67 _private prototype_ `void TerminateEditor();`
- L69 _private prototype_ `void InitializeKPIs();`
- L70 _private prototype_ `void TerminateKPIs();`
- L72 _private prototype_ `void UpdateKPIsHighFrequency();`
- L73 _private prototype_ `void UpdateKPIsLowFrequency();`
- L74 _private prototype_ `void HitchSamplerCallback();`
- L76 _private prototype_ `void DebugForceKPIIntoBadStateIfNeeded();`
- L78 _private prototype_ `FText GetMemoryPressureDisplayValue(const float) const;`
- L79 _private prototype_ `FText GetDynamicInvalidationDisplayValue(const float) const;`
- L81 _private member_ `FKPIRegistry KPIRegistry;`
- L82 _private member_ `TMap<FString,FKPIProfile> KPIProfiles;`
- L83 _private member_ `FString KPIProfileName=TEXT("Def`
- L85 _private member_ `FPerformanceStateChangedEvent OnPerformanceStateChanged;`
- L87 _private member_ `FDateTime LoadMapStartTime;`
- L88 _private member_ `FDateTime PIEStartTime;`
- L89 _private member_ `FDateTime PIEEndTime;`
- L90 _private member_ `FDateTime AssetRegistryScanStartTime;`
- L91 _private member_ `bool IsFirstTimeToPIE = true;`
- L92 _private member_ `bool IsLoadingMap = false;`
- L93 _private member_ `EEditorState EditorState = EEditorState::Editor_Boot;`
- L94 _private member_ `float BootToPIETime=0;`
- L95 _private member_ `float EditorBootTime = 0;`
- L96 _private member_ `float EditorStartUpTime = 0;`
- L97 _private member_ `float EditorLoadMapTime = 0;`
- L98 _private member_ `float EditorAssetRegistryScanTime = 0;`
- L99 _private member_ `volatile int32 EditorAssetRegistryScanCount = 0;`
- L100 _private member_ `FString EditorMapName=TEXT("Boo`
- L102 _private member_ `FTimerHandle HighFrequencyUpdateTimerHandle;`
- L103 _private member_ `const float HighFrequencyUpdateIntervalSeconds = 1.0f;`
- L104 _private member_ `FTimerHandle LowFrequencyUpdateTimerHandle;`
- L105 _private member_ `const float LowFrequencyUpdateIntervalSeconds = 60.0f;`
- L107 _private member_ `FTimerHandle HitchSamplerTimerHandle;`
- L108 _private member_ `const float HitchSamplerIntervalSeconds = 0.1f;`
- L109 _private member_ `const float MinFPSForHitching = 15.0f;`
- L110 _private member_ `const uint32 MinSamplesForHitching = 10;`
- L111 _private member_ `volatile int32 StallDetectedCount = 0;`
- L112 _private member_ `float HitchRate = 0;`
- L113 _private member_ `float StallRate = 0;`
- L114 _private member_ `uint32 TotalPluginCount = 0;`
- L116 _private member_ `FGuid EditorBootKPI;`
- L117 _private member_ `FGuid EditorInitializeKPI;`
- L118 _private member_ `FGuid EditorLoadMapKPI;`
- L119 _private member_ `FGuid EditorHitchRateKPI;`
- L120 _private member_ `FGuid EditorStallRateKPI;`
- L121 _private member_ `FGuid EditorAssetRegistryScanKPI;`
- L122 _private member_ `FGuid EditorPluginCountKPI;`
- L123 _private member_ `FGuid TotalTimeToEditorKPI;`
- L124 _private member_ `FGuid TotalTimeToPIEKPI;`
- L125 _private member_ `FGuid PIEFirstTransitionKPI;`
- L126 _private member_ `FGuid PIETransitionKPI;`
- L127 _private member_ `FGuid PIEShutdownKPI;`
- L128 _private member_ `FGuid PIEHitchRateKPI;`
- L129 _private member_ `FGuid PIEStallRateKPI;`
- L130 _private member_ `FGuid CloudDDCLatencyKPI;`
- L131 _private member_ `FGuid CloudDDCReadSpeedKPI;`
- L132 _private member_ `FGuid TotalDDCEfficiencyKPI;`
- L133 _private member_ `FGuid LocalDDCEfficiencyKPI;`
- L134 _private member_ `FGuid VirtualAssetEfficiencyKPI;`
- L135 _private member_ `FGuid AvailableMemoryKPI;`
- L136 _private member_ `FGuid MemoryPressureKPI;`
- L137 _private member_ `FGuid DynamicInvalidationKPI;`
- L139 _private member_ `FGuid EngineDirFreeSpaceKPI;`
- L140 _private member_ `FGuid ProjectDirFreeSpaceKPI;`
- L141 _private member_ `FGuid UserDirFreeSpaceKPI;`

#### enum `FEditorPerformanceModule::EEditorState`  
`enum EEditorState : uint8`  
_L28-36_
- L30 _public enumerator_ `Editor_Boot`
- L31 _public enumerator_ `Editor_Initialize`
- L32 _public enumerator_ `Editor_Interact`
- L33 _public enumerator_ `PIE_Startup`
- L34 _public enumerator_ `PIE_Interact`
- L35 _public enumerator_ `PIE_Shutdown`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API EDITORPERFORMANCE_API`
- L59 _delegate_ `DECLARE_EVENT(FEditorPerformanceModule, FPerformanceStateChangedEvent);`

### `Plugins/Experimental/EditorPerformance/Source/EditorPerformance/Public/KPIValue.h` (Public)


#### class `FKPIValue`  
`class FKPIValue`  
_L10-102_
- L13 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetCustomDisplayValue, const float);`
- L52 _public function_ `FKPIValue(FName NewCategory, FText NewDisplayCategory, FName NewName, FText NewDisplayName, FKPIValue::ESeverity NewSeverity, float NewInitialValue, TOptional<float> NewThresholdValue, FKPIValue::ECompare NewCompare = ECompare::LessThan, FKPIValue::EDisplayType NewDisplayType=EDisplayType::Number, FKPIValue::EState NewState=NotSet): Id(FGuid::NewGuid()), Category(NewCategory), DisplayCategory(NewDisplayCategory), Name(NewName), DisplayName(NewDisplayName), Severity(NewSeverity), CurrentValue(NewInitialValue), ThresholdValue(NewThresholdValue), State(NewState), Compare(NewCompare), DisplayType(NewDisplayType)`
- L69 _public function_ `FKPIValue()`
- L72 _public prototype_ `EState GetState() const;`
- L73 _public prototype_ `void SetValue(float Value);`
- L74 _public prototype_ `static FString GetValueAsString(float Value, FKPIValue::EDisplayType Type, const FGetCustomDisplayValue& CustomDisplayValueGetter);`
- L75 _public prototype_ `static FString GetComparisonAsString(FKPIValue::ECompare Compare);`
- L76 _public prototype_ `static FString GetComparisonAsPrettyString(FKPIValue::ECompare Compare);`
- L77 _public prototype_ `static FString GetDisplayTypeAsString(FKPIValue::EDisplayType Type);`
- L79 _public member_ `FGuid Id;`
- L81 _public member_ `FName Category;`
- L82 _public member_ `FText DisplayCategory;`
- L84 _public member_ `FName Name;`
- L85 _public member_ `FText DisplayName;`
- L87 _public member_ `FName Path;`
- L89 _public member_ `ESeverity Severity;`
- L91 _public member_ `float CurrentValue = 0;`
- L92 _public member_ `TOptional<float> ThresholdValue;`
- L93 _public member_ `uint32 FailureCount = 0;`
- L94 _public member_ `EState State = EState::NotSet;`
- L95 _public member_ `ECompare Compare = ECompare::LessThan;`
- L96 _public member_ `EDisplayType DisplayType = EDisplayType::Number;`
- L97 _public member_ `FGetCustomDisplayValue CustomDisplayValueGetter;`
- L100 _protected prototype_ `void UpdateState();`

#### enum `FKPIValue::ECompare`  
`enum ECompare : uint8`  
_L15-21_
- L17 _public enumerator_ `LessThan`
- L18 _public enumerator_ `LessThanOrEqual`
- L19 _public enumerator_ `GreaterThan`
- L20 _public enumerator_ `GreaterThanOrEqual`

#### enum `FKPIValue::EDisplayType`  
`enum EDisplayType : uint8`  
_L23-36_
- L25 _public enumerator_ `Number`
- L26 _public enumerator_ `Decimal`
- L27 _public enumerator_ `Seconds`
- L28 _public enumerator_ `Milliseconds`
- L29 _public enumerator_ `Minutes`
- L30 _public enumerator_ `Bytes`
- L31 _public enumerator_ `MegaBytes`
- L32 _public enumerator_ `GigaBytes`
- L33 _public enumerator_ `MegaBitsPerSecond`
- L34 _public enumerator_ `Percent`
- L35 _public enumerator_ `Custom`

#### enum `FKPIValue::EState`  
`enum EState : uint8`  
_L38-43_
- L40 _public enumerator_ `NotSet`
- L41 _public enumerator_ `Good`
- L42 _public enumerator_ `Bad`

#### enum `FKPIValue::ESeverity`  
`enum ESeverity : uint8`  
_L45-50_
- L47 _public enumerator_ `Minor`
- L48 _public enumerator_ `Major`
- L49 _public enumerator_ `Critical`

#### class `FKPIProfile`  
`class FKPIProfile`  
_L107-112_
- L110 _public member_ `FString MapName=TEXT("");`
- L111 _public member_ `FKPIThesholds Thresholds;`

#### class `FKPIHint`  
`class FKPIHint`  
_L116-122_
- L119 _public member_ `FGuid Id;`
- L120 _public member_ `FText Message;`
- L121 _public member_ `FString DocumentationLink;`

#### class `FKPIRegistry`  
`class FKPIRegistry`  
_L126-151_
- L130 _public prototype_ `FGuid DeclareKPIValue(const FName Category, const FText DisplayCategory, const FName Name, const FText DisplayName, float InitialValue, TOptional<float> ThresholdValue, FKPIValue::ECompare Compare, FKPIValue::EDisplayType Type);`
- L131 _public prototype_ `FGuid DeclareKPIValue(const FKPIValue& Value);`
- L132 _public prototype_ `bool DeclareKPIHint(FGuid Id, const FText& HintMessage, const FString& DocumentationLink = FString());`
- L134 _public prototype_ `bool SetKPIValue(FGuid Id, float CurrentValue);`
- L135 _public prototype_ `bool SetKPIThreshold(FGuid Id, float ThresholdValue);`
- L136 _public prototype_ `bool InvalidateKPIValue(FGuid Id);`
- L137 _public prototype_ `bool GetKPIValue(FGuid Id, FKPIValue& Result) const;`
- L138 _public prototype_ `bool GetKPIHint(FGuid Id, FKPIHint& Result) const;`
- L139 _public prototype_ `const FKPIValues& GetKPIValues() const;`
- L140 _public prototype_ `const FKPIProfiles& GetKPIProfiles() const;`
- L142 _public prototype_ `void LoadKPIHints(const FString& HintSectionName, const FString& FileName);`
- L143 _public prototype_ `void LoadKPIProfiles(const FString& ProfileSectionName, const FString& FileName);`
- L144 _public prototype_ `bool ApplyKPIProfile(const FKPIProfile& Profile);`
- L148 _private member_ `FKPIValues Values;`
- L149 _private member_ `FKPIProfiles Profiles;`
- L150 _private member_ `FKPIHints Hints;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetCustomDisplayValue, const float);`
- L104 _typedef_ `typedef TMap<FGuid, FKPIValue> FKPIValues;`
- L105 _typedef_ `typedef TMap<FGuid, float> FKPIThesholds;`
- L114 _typedef_ `typedef TMap<FString, FKPIProfile> FKPIProfiles;`
- L124 _typedef_ `typedef TMap<FGuid, FKPIHint> FKPIHints;`
