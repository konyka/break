# Plugins / IoStoreInsights

- module root: `Plugins/IoStoreInsights/Source/IoStoreInsights`
- headers: 12; symbols: 276
- symbol kinds: class=13, enum=4, enumerator=14, function=21, member=95, namespace=40, prototype=71, struct=11, typedef=7
- PrivateDependencyModuleNames: Core, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceServices

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/Analyzers/IoStoreInsightsAnalyzer.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreInsightsAnalyzer`  
`class FIoStoreInsightsAnalyzer : public UE::Trace::IAnalyzer`  
_L17-56_
- inherits: `UE::Trace::IAnalyzer`
- L20 _public prototype_ `FIoStoreInsightsAnalyzer(TraceServices::IAnalysisSession& InSession, FIoStoreInsightsProvider& InIoStoreProvider);`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L26 _private prototype_ `bool GetPackageDetailFromMetadata( const FOnEventContext& Context, uint32 ThreadId, FString& OutPackageName, FString& OutExtraTag, uint64& OutPackageId ) const;`
- L51 _private member_ `TraceServices::IAnalysisSession& Session;`
- L52 _private member_ `FIoStoreInsightsProvider& Provider;`
- L53 _private member_ `TMap<uint64, FPendingActivity> ActiveReadsMap;`
- L54 _private member_ `TMap<uint64, FPendingRequest> ActiveRequestsMap;`
- L55 _private member_ `TMap<uint64, uint64> ActiveBatchMap;`

#### enum `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::(anonymous)`  
``  
_L29-37_

#### struct `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::FPendingActivity`  
`struct FPendingActivity`  
_L39-43_
- L41 _public member_ `uint64 ActivityIndex;`
- L42 _public member_ `uint32 IoStoreRequestIndex;`

#### struct `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::FPendingRequest`  
`struct FPendingRequest`  
_L45-49_
- L47 _public member_ `uint32 IoStoreRequestIndex;`
- L48 _public member_ `uint64 CreateActivityIndex;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L30 _enumerator_ `RouteId_BackendName` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L31 _enumerator_ `RouteId_RequestCreate` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L32 _enumerator_ `RouteId_RequestStarted` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L33 _enumerator_ `RouteId_RequestCompleted` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L34 _enumerator_ `RouteId_RequestFailed` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L35 _enumerator_ `RouteId_PackageMapping` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)
- L36 _enumerator_ `RouteId_RequestUnresolved` (scope `UE::IoStoreInsights::FIoStoreInsightsAnalyzer::__anonac2228bd0103`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/IoStoreInsightsModule.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreInsightsModule`  
`class FIoStoreInsightsModule : public IModuleInterface`  
_L16-33_
- inherits: `IModuleInterface`
- L19 _public prototype_ `static FIoStoreInsightsModule& Get();`
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _public prototype_ `TSharedPtr<SIoStoreAnalysisTab> GetIoStoreAnalysisViewTab(bool bInvoke);`
- L27 _private prototype_ `void RegisterTimingProfilerLayoutExtensions(FInsightsMajorTabExtender& InOutExtender);`
- L28 _private member_ `TWeakPtr<SIoStoreAnalysisTab> IoStoreAnalysisView;`
- L29 _private member_ `TWeakPtr<FTabManager> InsightsTabManager;`
- L31 _private member_ `FIoStoreInsightsTraceModule TraceModule;`
- L32 _private member_ `FIoStoreInsightsTimingViewExtender TimingViewExtender;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/IoStoreInsightsTraceModule.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreInsightsTraceModule`  
`class FIoStoreInsightsTraceModule : public TraceServices::IModule`  
_L10-24_
- inherits: `TraceServices::IModule`
- L13 _public prototype_ `virtual ~FIoStoreInsightsTraceModule() = default;`
- L16 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L17 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L18 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L19 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L20 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`
- L23 _private member_ `static FName ModuleName;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/Model/IoStoreInsightsProvider.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreInsightsProvider`  
`class FIoStoreInsightsProvider : public IIoStoreInsightsProvider`  
_L15-59_
- inherits: `IIoStoreInsightsProvider`
- L25 _public typedef_ `typedef TraceServices::TIntervalTimeline<FIoStoreActivity*, FTimelineSettings> TimelineInternal;`
- L27 _public prototype_ `explicit FIoStoreInsightsProvider(TraceServices::IAnalysisSession& Session);`
- L28 _public prototype_ `virtual ~FIoStoreInsightsProvider() = default;`
- L30 _public prototype_ `virtual void EnumerateIoStoreRequests(TFunctionRef<bool(const FIoStoreRequest&, const Timeline&)> Callback) const override;`
- L32 _public prototype_ `uint32 GetIoStoreRequestIndex(uint32 ChunkIdHash, uint8 ChunkType, uint64 Offset, uint64 Size, uint32 CallstackId, uint64 PackageId, const TCHAR* PackageName, const TCHAR* ExtraTag);`
- L33 _public prototype_ `uint32 GetUnknownIoStoreRequestIndex();`
- L35 _public prototype_ `uint64 BeginIoStoreActivity(uint32 IoStoreRequestIndex, EIoStoreActivityType Type, uint32 ThreadId, uint64 BackendHandle, double Time);`
- L36 _public prototype_ `void EndIoStoreActivity(uint32 IoStoreRequestIndex, uint64 ActivityIndex, uint64 ActualSize, bool Failed, double Time);`
- L38 _public prototype_ `void AddPackageMapping(uint64 PackageId, const TCHAR* PackageName);`
- L40 _public prototype_ `void AddBackendName(uint64 BackendHandle, const TCHAR* BackendName);`
- L42 _public prototype_ `virtual const FIoStoreRequest& GetIoStoreRequest(uint32 IoStoreRequestIndex) const override;`
- L51 _private member_ `TraceServices::IAnalysisSession& Session;`
- L52 _private member_ `TraceServices::TPagedArray<FIoStoreRequestInfoInternal> IoStoreRequests;`
- L53 _private member_ `TraceServices::TPagedArray<FIoStoreActivity> IoStoreRequestStates;`
- L54 _private member_ `TMap<uint64, const TCHAR*> PackageMap;`
- L55 _private member_ `TMap<uint64, const TCHAR*> BackendNameMap;`
- L57 _private member_ `TMap<uint64,TArray<uint32>> PendingPackageNameMap;`
- L58 _private member_ `TMap<uint64,TArray<FIoStoreActivity*>> PendingBackendNameMap;`

#### struct `UE::IoStoreInsights::FIoStoreInsightsProvider::FTimelineSettings`  
`struct FTimelineSettings`  
_L18-24_

#### enum `UE::IoStoreInsights::FIoStoreInsightsProvider::FTimelineSettings::(anonymous)`  
``  
_L21-23_

#### struct `UE::IoStoreInsights::FIoStoreInsightsProvider::FIoStoreRequestInfoInternal`  
`struct FIoStoreRequestInfoInternal`  
_L45-49_
- L47 _public member_ `FIoStoreRequest IoStoreRequestInfo;`
- L48 _public member_ `TSharedPtr<TimelineInternal> ActivityTimeline;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L22 _enumerator_ `EventsPerPage = 128` (scope `UE::IoStoreInsights::FIoStoreInsightsProvider::FTimelineSettings::__anon324c7d9a0103`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/ViewModels/IoStoreActivityTable.h` (Private)


#### struct `UE::IoStoreInsights::FActivityTableColumns`  
`struct FActivityTableColumns`  
_L16-26_
- L18 _public member_ `static const FName ColumnRequestPackage;`
- L19 _public member_ `static const FName ColumnRequestOffset;`
- L20 _public member_ `static const FName ColumnRequestSize;`
- L21 _public member_ `static const FName ColumnRequestDuration;`
- L22 _public member_ `static const FName ColumnRequestChunkId;`
- L23 _public member_ `static const FName ColumnRequestChunkType;`
- L24 _public member_ `static const FName ColumnRequestStartTime;`
- L25 _public member_ `static const FName ColumnRequestBackend;`

#### class `UE::IoStoreInsights::FIoStoreActivityTable`  
`class FIoStoreActivityTable : public UE::Insights::FTable`  
_L28-46_
- inherits: `UE::Insights::FTable`
- L31 _public prototype_ `virtual ~FIoStoreActivityTable() = default;`
- L33 _public prototype_ `virtual void Reset() override;`
- L35 _public function_ `TArray<const FIoStoreActivity*>& GetActivities()`
- L36 _public function_ `const TArray<const FIoStoreActivity*>& GetActivities() const`
- L38 _public function_ `bool IsValidRowIndex(int32 InIndex) const`
- L39 _public function_ `const FIoStoreActivity* GetActivity(int32 InIndex) const`
- L40 _public function_ `const FIoStoreActivity* GetActivityChecked(int32 InIndex) const`
- L43 _private prototype_ `void AddDefaultColumns();`
- L45 _private member_ `TArray<const FIoStoreActivity*> Activities;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/ViewModels/IoStoreActivityTableTreeNode.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreActivityNode`  
`class FIoStoreActivityNode : public UE::Insights::FTableTreeNode`  
_L28-54_
- inherits: `UE::Insights::FTableTreeNode`
- desc: Class used to store information about an IoStore activity (used in SActivityTreeView)
- L33 _public function_ `explicit FIoStoreActivityNode(TWeakPtr<FIoStoreActivityTable> InParentTable, int32 InRowIndex, uint32 InRequestIndex) : UE::Insights::FTableTreeNode(InParentTable, InRowIndex) , RequestIndex(InRequestIndex)`
- L39 _public prototype_ `virtual const FText GetDisplayName() const override;`
- L41 _public function_ `FIoStoreActivityTable& GetActivityTableChecked() const`
- L48 _public function_ `bool IsValidActivity() const`
- L49 _public function_ `const FIoStoreActivity* GetActivity() const`
- L50 _public function_ `const FIoStoreActivity* GetActivityChecked() const`
- L53 _private member_ `uint32 RequestIndex;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L16 _typedef_ `typedef TSharedPtr<class FIoStoreActivityNode> FActivityNodePtr;` (scope `UE::IoStoreInsights`) — Type definition for shared pointers to instances of FIoStoreActivityNode
- L19 _typedef_ `typedef TSharedRef<class FIoStoreActivityNode> FActivityNodeRef;` (scope `UE::IoStoreInsights`) — Type definition for shared references to instances of FIoStoreActivityNode
- L22 _typedef_ `typedef TSharedRef<const class FIoStoreActivityNode> FActivityNodeRefConst;` (scope `UE::IoStoreInsights`) — Type definition for shared references to const instances of FIoStoreActivityNode
- L25 _typedef_ `typedef TWeakPtr<class FIoStoreActivityNode> FActivityNodeWeak;` (scope `UE::IoStoreInsights`) — Type definition for weak references to instances of FIoStoreActivityNode

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/ViewModels/IoStoreInsightsTimingViewExtender.h` (Private)


#### struct `UE::IoStoreInsights::FIoStoreRequestState`  
`struct FIoStoreRequestState`  
_L23-30_
- L25 _public member_ `uint32 IoStoreRequestIndex;`
- L26 _public member_ `double StartTime;`
- L27 _public member_ `double EndTime;`
- L28 _public member_ `int32 MaxConcurrentEvents;` — only used during layout
- L29 _public member_ `uint32 StartingDepth;` — only used during layout

#### struct `UE::IoStoreInsights::FIoStoreEventState`  
`struct FIoStoreEventState`  
_L32-42_
- L34 _public member_ `TSharedPtr<FIoStoreRequestState> RequestState;`
- L35 _public member_ `double StartTime;`
- L36 _public member_ `double EndTime;`
- L37 _public member_ `uint64 ActualSize;`
- L38 _public member_ `const TCHAR* BackendName;`
- L39 _public member_ `uint64 TimingEventType;`
- L40 _public member_ `uint32 Depth;` — During update, this is local within a track - then it's set to a global depth
- L41 _public member_ `uint32 Type;` — EIoStoreActivityType + "Failed" flag

#### class `UE::IoStoreInsights::FIoStoreInsightsViewSharedState`  
`class FIoStoreInsightsViewSharedState`  
_L44-64_
- L47 _public prototype_ `void Tick(const TraceServices::IAnalysisSession& InAnalysisSession);`
- L49 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const`
- L50 _public function_ `const TArray<FIoStoreEventState>& GetAllEvents() const`
- L52 _public function_ `void RequestUpdate()`
- L54 _public function_ `bool IsShowingOnlyReadEvents() const`
- L55 _public function_ `void ToggleShowOnlyReadEvents()`
- L57 _public member_ `static const uint32 MaxLanes;`
- L60 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;` — cached in Tick()
- L61 _private member_ `bool bForceIoEventsUpdate = false;`
- L62 _private member_ `bool bShowOnlyReadEvents = true;`
- L63 _private member_ `TArray<FIoStoreEventState> AllIoEvents;`

#### class `UE::IoStoreInsights::FIoStoreInsightsTimingViewExtender`  
`class FIoStoreInsightsTimingViewExtender : public Insights::Timing::ITimingViewExtender`  
_L66-91_
- inherits: `Insights::Timing::ITimingViewExtender`
- L69 _public prototype_ `virtual void OnBeginSession(Insights::Timing::ITimingViewSession& InSession) override;`
- L70 _public prototype_ `virtual void OnEndSession(Insights::Timing::ITimingViewSession& InSession) override;`
- L71 _public prototype_ `virtual void Tick(Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L72 _public prototype_ `virtual void ExtendOtherTracksFilterMenu(Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L75 _private prototype_ `bool IsIoStoreActivityTrackVisible(TSharedPtr<FIoStoreInsightsTrack> IoStoreActivityTrack) const;`
- L76 _private prototype_ `void ToggleActivityTrackVisibility(TSharedPtr<FIoStoreInsightsTrack> IoStoreActivityTrack);`
- L79 _private member_ `bool bWasAnalysisComplete = false;`
- L80 _private member_ `double PreviousAnalysisSessionDuration = 0.0f;`
- L81 _private member_ `FIoStoreInsightsViewSharedState SharedState;`
- L88 _private member_ `TMap<Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;`

#### struct `UE::IoStoreInsights::FIoStoreInsightsTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L83-87_
- L85 _public member_ `TSharedPtr<FIoStoreInsightsTrack> IoStoreActivityTrack;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Insights` (scope `UE`)
- L14 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/ViewModels/IoStoreInsightsTrack.h` (Private)


#### class `UE::IoStoreInsights::FIoStoreInsightsTrack`  
`class FIoStoreInsightsTrack : public FTimingEventsTrack`  
_L17-36_
- inherits: `FTimingEventsTrack`
- L20 _public prototype_ `explicit FIoStoreInsightsTrack(FIoStoreInsightsViewSharedState& InSharedState);`
- L21 _public prototype_ `virtual ~FIoStoreInsightsTrack() override = default;`
- L23 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L24 _public prototype_ `virtual void BuildDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L25 _public prototype_ `virtual void BuildFilteredDrawState(ITimingEventsTrackDrawStateBuilder& Builder, const ITimingTrackUpdateContext& Context) override;`
- L26 _public prototype_ `virtual const TSharedPtr<const ITimingEvent> SearchEvent(const FTimingEventSearchParameters& InSearchParameters) const override;`
- L29 _protected prototype_ `void AddIoStoreEventToBuilder(const FIoStoreEventState& Event, ITimingEventsTrackDrawStateBuilder& Builder, const class IIoStoreInsightsProvider* IoStoreActivityProvider) const;`
- L30 _protected prototype_ `bool FindIoStoreEvent(const FTimingEventSearchParameters& InParameters, TFunctionRef<void(double, double, uint32, const FIoStoreEventState&)> InFoundPredicate) const;`
- L32 _protected prototype_ `uint32 GetIoStoreActivityTypeColor(EIoStoreActivityType Type) const;`
- L35 _protected member_ `FIoStoreInsightsViewSharedState& SharedState;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/Widgets/SIoStoreActivityTableTreeView.h` (Private)


#### class `UE::IoStoreInsights::SActivityTableTreeView`  
`class SActivityTableTreeView : public UE::Insights::STableTreeView`  
_L13-37_
- inherits: `UE::Insights::STableTreeView`
- L16 _public prototype_ `virtual ~SActivityTableTreeView() = default;`
- L18 _public function_ `SLATE_BEGIN_ARGS(SActivityTableTreeView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FIoStoreActivityTable> InTablePtr);`
- L23 _public function_ `TSharedPtr<FIoStoreActivityTable> GetActivityTable()`
- L24 _public function_ `const TSharedPtr<FIoStoreActivityTable> GetActivityTable() const`
- L26 _public prototype_ `void SetRange(double InStartTime, double InEndTime);`
- L27 _public prototype_ `void SetAnalysisSession(const TraceServices::IAnalysisSession* InAnalysisSession);`
- L29 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L30 _public prototype_ `virtual void RebuildTree(bool bResync);`
- L33 _private member_ `bool bRangeDirty = false;`
- L34 _private member_ `double StartTime = 0.0;`
- L35 _private member_ `double EndTime = -1.0;`
- L36 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace TraceServices`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace IoStoreInsights` (scope `UE`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/Widgets/SIoStoreAnalysisReadSizeHistogramView.h` (Private)


#### struct `UE::IoStoreInsights::Private::FReadSizeHistogramItem`  
`struct FReadSizeHistogramItem`  
_L16-24_
- L18 _public member_ `uint64 QuantizedReadSize = 0;`
- L19 _public member_ `uint32 Count = 0;`
- L20 _public member_ `float CountAsPct = 0;`
- L21 _public member_ `float CountAsPctNormalized = 0;`
- L22 _public member_ `double MinDuration = 0;`
- L23 _public member_ `double MaxDuration = 0;`

#### class `UE::IoStoreInsights::SIoStoreAnalysisReadSizeHistogramView`  
`class SIoStoreAnalysisReadSizeHistogramView : public SListView<TSharedPtr<Private::FReadSizeHistogramItem>>`  
_L27-44_
- inherits: `SListView<TSharedPtr<Private::FReadSizeHistogramItem>>`
- L29 _private typedef_ `typedef SListView<TSharedPtr<Private::FReadSizeHistogramItem>> Super;`
- L32 _public function_ `SLATE_BEGIN_ARGS(SIoStoreAnalysisReadSizeHistogramView)`
- L33 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<Private::FReadSizeHistogramItem>>*, ListItemsSource) SLATE_END_ARGS() ~SIoStoreAnalysisReadSizeHistogramView() = default;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `void SetAnalysisSession( const TraceServices::IAnalysisSession* InAnalysisSession );`
- L41 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L43 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<Private::FReadSizeHistogramItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::IoStoreInsights`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Private/Widgets/SIoStoreAnalysisTab.h` (Private)


#### class `UE::IoStoreInsights::SIoStoreAnalysisTab`  
`class SIoStoreAnalysisTab : public SCompoundWidget`  
_L29-72_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SIoStoreAnalysisTab)`
- L34 _public prototype_ `~SIoStoreAnalysisTab();`
- L36 _public prototype_ `void Construct(const FArguments& InArgs);`
- L38 _public prototype_ `void SetSession(UE::Insights::Timing::ITimingViewSession* InTimingViewSession, const TraceServices::IAnalysisSession* InAnalysisSession, const FIoStoreInsightsViewSharedState* InSharedStatePtr);`
- L39 _public prototype_ `bool IsSessionSet() const;`
- L48 _private prototype_ `void HandleTimeMarkerChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double InTimeMarker);`
- L49 _private prototype_ `void HandleSelectionChanged(UE::Insights::Timing::ETimeChangedFlags InFlags, double StartTime, double EndTime);`
- L50 _private prototype_ `void HandleSelectionEventChanged(const TSharedPtr<const ITimingEvent> InEvent);`
- L52 _private prototype_ `int32 GetSelectedViewModeIndex() const;`
- L53 _private prototype_ `ECheckBoxState IsViewModeSelected(EViewMode Mode) const;`
- L54 _private prototype_ `void OnViewModeCheckStateChange(ECheckBoxState State, EViewMode Mode);`
- L56 _private prototype_ `void RefreshNodes();`
- L57 _private prototype_ `void RefreshNodes_IoStoreActivity(const FIoStoreInsightsProvider* Provider);`
- L60 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession = nullptr;`
- L61 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L62 _private member_ `const FIoStoreInsightsViewSharedState* SharedStatePtr = nullptr;`
- L64 _private member_ `double StartTime = -1;`
- L65 _private member_ `double EndTime = -1;`
- L66 _private member_ `EViewMode ViewMode = EViewMode::ReadActivity;`
- L68 _private member_ `TArray<TSharedPtr<Private::FReadSizeHistogramItem>> ReadSizeHistogramItems;`
- L69 _private member_ `TSharedPtr<SIoStoreAnalysisReadSizeHistogramView> ReadSizeHistogramView;`
- L71 _private member_ `TSharedPtr<SActivityTableTreeView> ActivityTableTreeView;`

#### enum `UE::IoStoreInsights::SIoStoreAnalysisTab::EViewMode`  
`enum class EViewMode : uint8`  
_L42-46_
- L44 _public enumerator_ `ReadActivity`
- L45 _public enumerator_ `ReadSizes`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L16 _namespace_ `namespace TraceServices`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L27 _namespace_ `namespace Private` (scope `UE::IoStoreInsights`)

### `Plugins/IoStoreInsights/Source/IoStoreInsights/Public/IIoStoreInsightsProvider.h` (Public)


#### enum `UE::IoStoreInsights::EIoStoreActivityType`  
`enum class EIoStoreActivityType : uint8`  
_L11-18_
- L13 _public enumerator_ `Request_Pending`
- L14 _public enumerator_ `Request_Read`
- L16 _public enumerator_ `Count`
- L17 _public enumerator_ `Invalid = Count`

#### struct `UE::IoStoreInsights::FIoStoreRequest`  
`struct FIoStoreRequest`  
_L20-31_
- L22 _public member_ `uint32 IoStoreRequestIndex = uint32(-1);`
- L23 _public member_ `uint32 ChunkIdHash = 0;`
- L24 _public member_ `uint8 ChunkType = 0;`
- L25 _public member_ `uint64 Offset = 0;`
- L26 _public member_ `uint64 Size = 0;`
- L27 _public member_ `uint64 CallstackId = 0;`
- L28 _public member_ `uint64 PackageId = 0;`
- L29 _public member_ `const TCHAR* PackageName = nullptr;`
- L30 _public member_ `const TCHAR* ExtraTag = nullptr;`

#### struct `UE::IoStoreInsights::FIoStoreActivity`  
`struct FIoStoreActivity`  
_L33-43_
- L35 _public member_ `const FIoStoreRequest* IoStoreRequest = nullptr;`
- L36 _public member_ `double StartTime = 0.0;`
- L37 _public member_ `double EndTime = 0.0;`
- L38 _public member_ `uint64 ActualSize = 0;`
- L39 _public member_ `const TCHAR* BackendName = nullptr;`
- L40 _public member_ `uint32 ThreadId = 0;`
- L41 _public member_ `EIoStoreActivityType ActivityType = EIoStoreActivityType::Invalid;`
- L42 _public member_ `bool Failed = false;`

#### class `UE::IoStoreInsights::IIoStoreInsightsProvider`  
`class IIoStoreInsightsProvider : public TraceServices::IProvider`  
_L45-56_
- inherits: `TraceServices::IProvider`
- L48 _public member_ `static FName ProviderName;`
- L50 _public typedef_ `typedef TraceServices::ITimeline<FIoStoreActivity*> Timeline;`
- L52 _public prototype_ `virtual ~IIoStoreInsightsProvider() = default;`
- L53 _public prototype_ `virtual void EnumerateIoStoreRequests(TFunctionRef<bool(const FIoStoreRequest&, const Timeline&)> Callback) const = 0;`
- L55 _public prototype_ `virtual const FIoStoreRequest& GetIoStoreRequest(uint32 IoStoreRequestIndex) const = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace IoStoreInsights` (scope `UE`)
- L58 _prototype_ `const IIoStoreInsightsProvider* ReadIoStoreInsightsProvider(const TraceServices::IAnalysisSession& Session);` (scope `UE::IoStoreInsights`)
- L60 _prototype_ `const TCHAR* LexToString(EIoStoreActivityType ActivityType);` (scope `UE::IoStoreInsights`)
