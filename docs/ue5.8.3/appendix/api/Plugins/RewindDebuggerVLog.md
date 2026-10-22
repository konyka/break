# Plugins / RewindDebuggerVLog

- module root: `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog`
- headers: 11; symbols: 190
- symbol kinds: class=13, enum=3, enumerator=7, externvar=1, function=19, member=60, namespace=10, prototype=74, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, GameplayInsights, InputCore, LogVisualizer, RewindDebuggerInterface, RewindDebuggerRuntime, RewindDebuggerVLogRuntime, Slate, SlateCore, ToolMenus, TraceAnalysis, TraceBasedDebuggers, TraceServices, UnrealEd

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/RewindDebuggerVLog.h` (Private)


#### class `FRewindDebuggerVLog`  
`class FRewindDebuggerVLog : public IRewindDebuggerExtension`  
_L28-66_
- inherits: `IRewindDebuggerExtension`
- desc: Rewind debugger extension for Visual Logger support
- L31 _public prototype_ `void OnShowDebugInfo(UCanvas* Canvas, APlayerController* Player);`
- L32 _public prototype_ `virtual ~FRewindDebuggerVLog();`
- L34 _public function_ `virtual FString GetName() override`
- L39 _public prototype_ `void Initialize();`
- L40 _public prototype_ `static void ToggleCategory(const FName& Category);`
- L41 _public prototype_ `static bool IsCategoryActive(const FName& Category);`
- L44 _protected prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;`
- L45 _protected prototype_ `virtual void OnTrackListChanged(IRewindDebugger* RewindDebugger) override;`
- L48 _private prototype_ `void AddLogEntries(const TArray<TSharedPtr<FDebugObjectInfo>>& Components, float StartTime, float EndTime, const class IVisualLoggerProvider* Provider, UCanvas* Canvas);`
- L49 _private prototype_ `void ImmediateRender(const UObject* Object, const FVisualLogEntry& Entry);`
- L50 _private prototype_ `void RenderLogEntry(const FVisualLogEntry& Entry, UCanvas* Canvas);`
- L52 _private prototype_ `AVLogRenderingActor* GetRenderingActor();`
- L54 _private member_ `TWeakObjectPtr<AVLogRenderingActor> VLogActor;`
- L56 _private member_ `TSet<uint64> ObjectsVisited;`
- L57 _private member_ `int32 ScreenTextY = 0;`
- L59 _private member_ `FDelegateHandle DelegateHandle;`
- L60 _private member_ `FDelegateHandle ToolMenuRegistrationHandle;`
- L61 _private member_ `TStrongObjectPtr<UFont> MonospaceFont;`
- L62 _private member_ `TSharedPtr<UE::RewindDebugger::SLogCategoryFilter> LogCategoryFilterWidget;`
- L64 _private member_ `TArray<uint64> DebuggedObjectIds;`
- L65 _private member_ `TArray<FVisualLogEntry> ImmediateRenderQueue;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace TraceBasedDebuggers` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/RewindDebuggerVLogModule.h` (Private)


#### class `FRewindDebuggerVLogModule`  
`class FRewindDebuggerVLogModule : public IModuleInterface`  
_L12-22_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private member_ `FRewindDebuggerVLog RewindDebuggerVLogExtension;`
- L21 _private member_ `FVLogTraceModule VLogTraceModule;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/RewindDebuggerVLogSettings.h` (Private)


#### class `URewindDebuggerVLogSettings`  
`class URewindDebuggerVLogSettings : public UDeveloperSettings`  
_L14-46_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, meta=(DisplayName="Rewind Debugger - Visual Logging"))`
- inherits: `UDeveloperSettings`
- desc: Settings for the Rewind Debugger Visual Logger integration.
- L19 _public prototype_ `URewindDebuggerVLogSettings();`
- L22 _public prototype_ `virtual FText GetSectionText() const override;`
- L23 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L26 _public prototype_ `virtual FName GetCategoryName() const override;`
- L27 _public prototype_ `virtual void PostLoad() override;`
- L28 _public prototype_ `void ToggleCategory(FName Category);`
- L32 _public member_ `uint8 DisplayVerbosity = ELogVerbosity::Display;` — `UE_DEPRECATED(5.8, "Use DisplayCategoryVerbosities via Get/SetCategoryVerbosity instead.")` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Use DisplayCategoryVerbosities instead."))`
- L36 _public member_ `TSet<FName> DisplayCategories;` — `UPROPERTY(EditAnywhere, Config, Category = VisualLogger)` — Display Visual Logger shapes in these categories
- L40 _public member_ `TMap<FName, uint8> DisplayCategoryVerbosities;` — `UPROPERTY(EditAnywhere, Config, Category = VisualLogger)` — Per-category display verbosity. Categories without an entry default to ELogVerbosity::Display.
- L42 _public prototype_ `void SetCategoryVerbosity(FName Category, ELogVerbosity::Type Verbosity);`
- L43 _public prototype_ `ELogVerbosity::Type GetCategoryVerbosity(FName Category) const;`
- L45 _public prototype_ `static URewindDebuggerVLogSettings & Get();`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VLogRenderingActor.h` (Private)


#### class `AVLogRenderingActor`  
`class AVLogRenderingActor : public AVisualLoggerRenderingActorBase`  
_L17-30_
- reflection: `UCLASS(config = Engine, NotBlueprintable, Transient, notplaceable, AdvancedClassDisplay)`
- inherits: `AVisualLoggerRenderingActorBase`
- L21 _public prototype_ `virtual ~AVLogRenderingActor();`
- L22 _public prototype_ `void Reset();`
- L23 _public prototype_ `void AddLogEntry(const FVisualLogEntry& LogEntry);`
- L25 _public prototype_ `virtual void IterateDebugShapes(TFunction<void(const FTimelineDebugShapes&) > Callback) override;`
- L26 _public prototype_ `virtual bool MatchCategoryFilters(const FName& CategoryName, ELogVerbosity::Type Verbosity) const override;`
- L29 _private member_ `FTimelineDebugShapes DebugShapes;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VLogTraceModule.h` (Private)


#### class `FVLogTraceModule`  
`class FVLogTraceModule : public TraceServices::IModule`  
_L10-22_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L21 _private member_ `static FName ModuleName;`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VisualLogEntryRenderer.h` (Private)


#### class `FVisualLogEntryRenderer`  
`class FVisualLogEntryRenderer`  
_L6-11_
- L9 _public prototype_ `static void RenderLogEntry(class UWorld* World, const struct FVisualLogEntry& Entry, TFunctionRef<bool(const FName&, ELogVerbosity::Type)> MatchCategoryFilters, class UCanvas* Canvas, class UFont* Font, class UFont* MonospaceFont, int32& ScreenTextY);`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VisualLogTrack.h` (Private)


#### class `RewindDebugger::FVisualLogCategoryTrack`  
`class FVisualLogCategoryTrack : public FRewindDebuggerTrack`  
_L18-74_
- inherits: `FRewindDebuggerTrack`
- desc: Tracks representing all log lines of a given category
- L21 _public prototype_ `FVisualLogCategoryTrack(uint64 InObjectId, const FName& Category);`
- L22 _public function_ `FName GetCategory() const`
- L28 _private prototype_ `virtual bool UpdateInternal() override;`
- L29 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L30 _private prototype_ `virtual TSharedPtr<SWidget> GetTimelineViewInternal() override;`
- L31 _private prototype_ `virtual FText GetStepCommandTooltipInternal(EStepMode) const override;`
- L32 _private prototype_ `virtual TOptional<double> GetStepFrameTimeInternal(EStepMode, const FScrubTimeInformation&) const override;`
- L34 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L39 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L44 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L49 _private function_ `virtual FName GetNameInternal() const override`
- L54 _private prototype_ `TSharedPtr<SEventTimelineView::FTimelineEventData> GetEventData() const;`
- L56 _private member_ `mutable TSharedPtr<SEventTimelineView::FTimelineEventData> EventData;`
- L57 _private member_ `mutable int EventUpdateRequested = 0;`
- L59 _private member_ `uint64 ObjectId;`
- L60 _private member_ `FName Category;`
- L61 _private member_ `FSlateIcon Icon;`
- L62 _private member_ `FText TrackName;`
- L63 _private member_ `TSharedPtr<SListView<TSharedPtr<FLogEntryItem>>> ListView;`
- L64 _private member_ `TArray<TSharedPtr<FLogEntryItem>> LogEntries;`
- L66 _private member_ `double PreviousScrubTime = 0.0f;`

#### enum `RewindDebugger::FVisualLogCategoryTrack::EFilterType`  
`enum class EFilterType`  
_L68-73_
- L70 _public enumerator_ `VisualLog`
- L71 _public enumerator_ `VisualLogState`
- L72 _public enumerator_ `SyncMarker`

#### class `RewindDebugger::FVisualLogTrack`  
`class FVisualLogTrack : public FRewindDebuggerTrack`  
_L79-98_
- inherits: `FRewindDebuggerTrack`
- desc: Parent track for category tracks
- L82 _public prototype_ `explicit FVisualLogTrack(uint64 InObjectId);`
- L85 _private prototype_ `virtual bool UpdateInternal() override;`
- L86 _private prototype_ `virtual TSharedPtr<SWidget> GetDetailsViewInternal() override;`
- L88 _private function_ `virtual FSlateIcon GetIconInternal() override`
- L89 _private function_ `virtual FName GetNameInternal() const override`
- L90 _private function_ `virtual FText GetDisplayNameInternal() const override`
- L91 _private function_ `virtual uint64 GetObjectIdInternal() const override`
- L92 _private prototype_ `virtual TConstArrayView<TSharedPtr<FRewindDebuggerTrack>> GetChildrenInternal(TArray<TSharedPtr<FRewindDebuggerTrack>>& OutTracks) const override;`
- L94 _private member_ `FSlateIcon Icon;`
- L95 _private member_ `uint64 ObjectId;`
- L97 _private member_ `TArray<TSharedPtr<FVisualLogCategoryTrack>> Children;`

#### class `RewindDebugger::FVisualLogTrackCreator`  
`class FVisualLogTrackCreator : public IRewindDebuggerTrackCreator`  
_L104-111_
- inherits: `IRewindDebuggerTrackCreator`
- desc: Track creator for VisualLogger recorded entries
- L106 _private prototype_ `virtual FName GetTargetTypeNameInternal() const override;`
- L107 _private prototype_ `virtual FName GetNameInternal() const override;`
- L108 _private prototype_ `virtual void GetTrackTypesInternal(TArray<FRewindDebuggerTrackType>& Types) const override;`
- L109 _private prototype_ `virtual TSharedPtr<FRewindDebuggerTrack> CreateTrackInternal(const FObjectId& InObjectId) const override;`
- L110 _private prototype_ `virtual bool HasDebugInfoInternal(const FObjectId& InObjectId) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace RewindDebugger`

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VisualLoggerAnalyzer.h` (Private)


#### class `FVisualLoggerAnalyzer`  
`class FVisualLoggerAnalyzer : public UE::Trace::IAnalyzer`  
_L10-29_
- inherits: `UE::Trace::IAnalyzer`
- L13 _public prototype_ `FVisualLoggerAnalyzer(TraceServices::IAnalysisSession& InSession, FVisualLoggerProvider& InProvider);`
- L15 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L16 _public function_ `virtual void OnAnalysisEnd() override`
- L17 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L27 _private member_ `TraceServices::IAnalysisSession& Session;`
- L28 _private member_ `FVisualLoggerProvider& Provider;`

#### enum `FVisualLoggerAnalyzer::(anonymous)`  
``  
_L21-25_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L22 _enumerator_ `RouteId_VisualLogEntry UE_DEPRECATED(5.8, "Used only to read old recordings; now using header + chunk to handle large events")` (scope `FVisualLoggerAnalyzer::__anon79695e6d0103`)
- L23 _enumerator_ `RouteId_VisualLogEntryHeader` (scope `FVisualLoggerAnalyzer::__anon79695e6d0103`)
- L24 _enumerator_ `RouteId_VisualLogEntryChunk` (scope `FVisualLoggerAnalyzer::__anon79695e6d0103`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/VisualLoggerProvider.h` (Private)


#### struct `FVLogTimelineSettings`  
`struct FVLogTimelineSettings`  
_L18-24_

#### enum `FVLogTimelineSettings::(anonymous)`  
``  
_L21-23_

#### struct `FVLogEntry`  
`struct FVLogEntry`  
_L26-35_
- L28 _public member_ `uint32 EntryID = INDEX_NONE;`
- L29 _public member_ `uint32 Size = 0;`
- L30 _public member_ `uint64 OwnerID = INDEX_NONE;`
- L31 _public member_ `double RecordingTime = 0;`
- L32 _public member_ `double RecordingWorldTime = 0;`
- L33 _public member_ `TArray<uint8> Data;`
- L34 _public member_ `uint16 ChunkNum = 0;`

#### class `FVisualLoggerProvider`  
`class FVisualLoggerProvider : public IVisualLoggerProvider`  
_L37-90_
- inherits: `IVisualLoggerProvider`
- L40 _public member_ `static FName ProviderName;`
- L42 _public prototype_ `explicit FVisualLoggerProvider(TraceServices::IAnalysisSession& InSession);`
- L45 _public function_ `virtual void BeginRead() const override`
- L49 _public function_ `virtual void EndRead() const override`
- L53 _public function_ `virtual void ReadAccessCheck() const override`
- L59 _public function_ `virtual void BeginEdit() const override`
- L63 _public function_ `virtual void EndEdit() const override`
- L67 _public function_ `virtual void EditAccessCheck() const override`
- L73 _public prototype_ `virtual bool ReadVisualLogEntryTimeline(uint64 InObjectId, TFunctionRef<void(const VisualLogEntryTimeline&)> Callback) const override;`
- L74 _public prototype_ `virtual void EnumerateCategories(TFunctionRef<void(const FName&)> Callback) const override;`
- L77 _public prototype_ `void AppendVisualLogEntry(uint64 InObjectId, double InTime, const FVisualLogEntry& Entry);` — Add an object event message
- L79 _public prototype_ `FVLogEntry& AddLogEntry();`
- L80 _public prototype_ `void AddLogEntryChunk(uint32 ID, uint32 ChunkNum, uint16 Size, const TArrayView<const uint8>& ChunkData);`
- L83 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L84 _private member_ `TraceServices::IAnalysisSession& Session;`
- L86 _private member_ `TArray<FVLogEntry> LogEntries;`
- L87 _private member_ `TMap<uint64, uint32> ObjectIdToLogEntryTimelines;`
- L88 _private member_ `TArray<TSharedRef<TraceServices::TPointTimeline<FVisualLogEntry, FVLogTimelineSettings>>> LogEntryTimelines;`
- L89 _private member_ `TArray<FName> Categories;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace TraceServices`
- L15 _externvar_ `extern thread_local FProviderLock::FThreadLocalState GVisualLoggerProviderLockState;` (scope `TraceServices`)
- L22 _enumerator_ `EventsPerPage = 4096` (scope `FVLogTimelineSettings::__anon4e7902120103`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Private/Widgets/LogCategoryVerbositySelector.h` (Private)


#### class `UE::RewindDebugger::SLogCategoryFilter`  
`class SLogCategoryFilter : public SCompoundWidget`  
_L22-69_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SLogCategoryFilter)`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void RefreshCategoryList();`
- L33 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FLogCategoryVerbosity> InItem, const TSharedRef<STableViewBase>& InTable);`
- L35 _private prototype_ `TSharedRef<SWidget> BuildContent();`
- L36 _private prototype_ `void BuildHeaderRow();`
- L37 _private prototype_ `void BuildSwitcher();`
- L38 _private prototype_ `void OnSearchTextChanged(const FText& InText);`
- L39 _private prototype_ `void MeasureCategoryColumnWidth();`
- L40 _private prototype_ `FOptionalSize GetTotalWidth() const;`
- L42 _private prototype_ `void SetUseVerbosityLevelFiltering(bool bEnable);`
- L43 _private prototype_ `void SetRecordingColumnVisibility(bool bVisible);`
- L45 _private prototype_ `void SyncVerbosityLevels();`
- L46 _private prototype_ `bool CanChangeCategoryVerbosity(FName InCategoryName) const;`
- L47 _private prototype_ `void SetCategoryRecordingVerbosity(FName InCategoryName, ELogVerbosity::Type InVerbosity) const;`
- L48 _private prototype_ `ELogVerbosity::Type GetCategoryRecordingVerbosity(FName InCategoryName) const;`
- L50 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L51 _private member_ `TSharedPtr<SListView<TSharedPtr<FLogCategoryVerbosity>>> ListView;`
- L52 _private member_ `TSharedPtr<SWidgetSwitcher> Switcher;`
- L53 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L54 _private member_ `FHeaderRowStyle HeaderRowStyle;`
- L55 _private member_ `FTableRowStyle RowStyle;`
- L57 _private member_ `TArray<TSharedPtr<FLogCategoryVerbosity>> AllCategories;`
- L58 _private member_ `TArray<TSharedPtr<FLogCategoryVerbosity>> FilteredCategories;`
- L59 _private member_ `TArray<TSharedPtr<ELogVerbosity::Type>> VerbosityOptions;`
- L60 _private member_ `FText SearchText;`
- L62 _private member_ `static constexpr float DefaultCategoryColumnWidth = 120.f;`
- L63 _private member_ `float CategoryColumnWidth = DefaultCategoryColumnWidth;`
- L65 _private member_ `bool bUsingVerbosityFilterWhenRecording = false;`
- L66 _private member_ `static constexpr int32 SwitcherSlotIndexForWaitingState = 0;`
- L67 _private member_ `static constexpr int32 SwitcherSlotIndexForReadyState = 1;`
- L68 _private member_ `static constexpr int32 SwitcherSlotIndexForNoConnectionState = 2;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ELogVerbosity`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace RewindDebugger` (scope `UE`)

### `Plugins/Animation/GameplayInsights/Source/RewindDebuggerVLog/Public/IVisualLoggerProvider.h` (Public)


#### class `IVisualLoggerProvider`  
`class IVisualLoggerProvider : public TraceServices::IProvider , public TraceServices::IEditableProvider`  
_L18-27_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L23 _public typedef_ `typedef TraceServices::ITimeline<FVisualLogEntry> VisualLogEntryTimeline;`
- L25 _public prototype_ `virtual bool ReadVisualLogEntryTimeline(uint64 InObjectId, TFunctionRef<void(const VisualLogEntryTimeline&)> Callback) const = 0;`
- L26 _public prototype_ `virtual void EnumerateCategories(TFunctionRef<void(const FName&)> Callback) const = 0;`
