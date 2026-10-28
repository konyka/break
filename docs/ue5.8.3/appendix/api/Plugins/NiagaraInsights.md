# Plugins / NiagaraInsights

- module root: `Plugins/FX/NiagaraInsights/Source/NiagaraInsights`
- headers: 12; symbols: 284
- symbol kinds: class=11, delegate=3, enum=1, enumerator=7, externvar=7, function=12, member=113, namespace=38, prototype=73, struct=15, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, InputCore, Slate, SlateCore, TraceAnalysis, TraceInsights, TraceInsightsCore, TraceLog, TraceServices

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraAnalyzer.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraAnalyzer`  
`class FNiagaraAnalyzer : public UE::Trace::IAnalyzer`  
_L14-39_
- inherits: `UE::Trace::IAnalyzer`
- L17 _public prototype_ `FNiagaraAnalyzer(TraceServices::IAnalysisSession& InSession, FNiagaraProvider& InProvider);`
- L19 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L20 _public function_ `virtual void OnAnalysisEnd() override`
- L21 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L37 _private member_ `TraceServices::IAnalysisSession& Session;`
- L38 _private member_ `FNiagaraProvider& Provider;`

#### enum `UE::NiagaraInsights::FNiagaraAnalyzer::(anonymous)`  
``  
_L25-35_

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NiagaraInsights` (scope `UE`)
- L26 _enumerator_ `RouteId_SystemPerformance_GT` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L27 _enumerator_ `RouteId_SystemPerformance_RT` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L29 _enumerator_ `RouteId_ComponentActivate` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L30 _enumerator_ `RouteId_ComponentDeactivate` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L31 _enumerator_ `RouteId_ComponentComplete` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L33 _enumerator_ `RouteId_DataChannelPublish` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)
- L34 _enumerator_ `RouteId_DataChannelWrite` (scope `UE::NiagaraInsights::FNiagaraAnalyzer::__anon43537fa30103`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraDataChannelTrack.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraDataChannelTrack`  
`class FNiagaraDataChannelTrack : public FGraphTrack`  
_L12-28_
- inherits: `FGraphTrack`
- L14 _private typedef_ `using Super = FGraphTrack;`
- L19 _public prototype_ `explicit FNiagaraDataChannelTrack(const FNiagaraTimingViewSession& InSharedData);`
- L22 _public prototype_ `virtual void Update(const ITimingTrackUpdateContext& Context) override;` — BEGIN: FGraphTrack interface
- L23 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L27 _private member_ `const FNiagaraTimingViewSession& SharedData;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraInsightsCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NiagaraInsights` (scope `UE`)
- L7 _namespace_ `namespace Common` (scope `UE::NiagaraInsights`)
- L10 _externvar_ `extern const FLinearColor Color_InstanceCount;` (scope `UE::NiagaraInsights::Common`)
- L11 _externvar_ `extern const FLinearColor Color_GTCostTotal;` (scope `UE::NiagaraInsights::Common`)
- L12 _externvar_ `extern const FLinearColor Color_GTCostPerInst;` (scope `UE::NiagaraInsights::Common`)
- L13 _externvar_ `extern const FLinearColor Color_RTCostTotal;` (scope `UE::NiagaraInsights::Common`)
- L14 _externvar_ `extern const FLinearColor Color_RTCostPerInst;` (scope `UE::NiagaraInsights::Common`)
- L15 _externvar_ `extern const FLinearColor Color_GpuCostTotal;` (scope `UE::NiagaraInsights::Common`)
- L16 _externvar_ `extern const FLinearColor Color_MemoryCostTotal;` (scope `UE::NiagaraInsights::Common`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraInsightsComponent.h` (Private)


#### struct `UE::NiagaraInsights::FNiagaraInsightsTabs`  
`struct FNiagaraInsightsTabs`  
_L11-14_
- desc: Tab IDs for the Niagara Insights minor tabs inside the Timing Profiler.
- L13 _public member_ `static const FName RangeStatsViewID;`

#### class `UE::NiagaraInsights::FNiagaraInsightsComponent`  
`class FNiagaraInsightsComponent : public IInsightsComponent`  
_L21-37_
- inherits: `IInsightsComponent`
- desc: IInsightsComponent that adds the Niagara Range Stats minor tab into the Timing Profiler. The tab shows top-5 offenders by instance count, GT cost, GT cost/instance, RT cost, RT cost/instance, and GPU cost for the currently selected time range.
- L25 _public prototype_ `virtual void Initialize(IUnrealInsightsModule& InsightsModule) override;`
- L26 _public prototype_ `virtual void Shutdown() override;`
- L27 _public prototype_ `virtual void RegisterMajorTabs(IUnrealInsightsModule& InsightsModule) override;`
- L28 _public prototype_ `virtual void UnregisterMajorTabs() override;`
- L32 _private prototype_ `void OnRegisterTimingProfilerTabExtensions(FInsightsMajorTabExtender& Extender);`
- L34 _private prototype_ `TSharedRef<SDockTab> SpawnTab_RangeStatsView(const FSpawnTabArgs& Args);`
- L36 _private member_ `FDelegateHandle ExtensionDelegateHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraInsightsModule.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraInsightsModule`  
`class FNiagaraInsightsModule : public IModuleInterface`  
_L15-35_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `static FNiagaraInsightsModule& Get();`
- L25 _public function_ `FNiagaraTimingViewExtender& GetTimingViewExtender()`
- L28 _private prototype_ `void TryRegisterInsightsComponent();`
- L29 _private prototype_ `void OnModulesChanged(FName ModuleName, EModuleChangeReason Reason);`
- L31 _private member_ `FNiagaraTraceModule TraceModule;`
- L32 _private member_ `FNiagaraTimingViewExtender TimingViewExtender;`
- L33 _private member_ `TSharedPtr<FNiagaraInsightsComponent> InsightsComponent;`
- L34 _private member_ `FDelegateHandle ModuleChangedHandle;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraInstanceLifecycleTrack.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraInstanceLifecycleTrack`  
`class FNiagaraInstanceLifecycleTrack : public FGraphTrack`  
_L12-28_
- inherits: `FGraphTrack`
- L14 _private typedef_ `using Super = FGraphTrack;`
- L19 _public prototype_ `explicit FNiagaraInstanceLifecycleTrack(const FNiagaraTimingViewSession& InSharedData);`
- L22 _public prototype_ `virtual void Update(const ITimingTrackUpdateContext& Context) override;` — BEGIN: FGraphTrack interface
- L23 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L27 _private member_ `const FNiagaraTimingViewSession& SharedData;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraPerformanceGraphTrack.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraPerformanceGraphTrack`  
`class FNiagaraPerformanceGraphTrack : public FGraphTrack`  
_L14-34_
- inherits: `FGraphTrack`
- L16 _private typedef_ `using Super = FGraphTrack;`
- L21 _public prototype_ `explicit FNiagaraPerformanceGraphTrack(const FNiagaraTimingViewSession& InSharedData);`
- L24 _public prototype_ `virtual void Update(const ITimingTrackUpdateContext& Context) override;` — BEGIN: FGraphTrack interface
- L25 _public prototype_ `virtual void InitTooltip(FTooltipDrawState& InOutTooltip, const ITimingEvent& InTooltipEvent) const override;`
- L29 _private member_ `const FNiagaraTimingViewSession& SharedData;`
- L30 _private member_ `TSharedPtr<FGraphSeries> GameTimeSeries;`
- L31 _private member_ `TSharedPtr<FGraphSeries> RenderTimeSeries;`
- L32 _private member_ `TSharedPtr<FGraphSeries> GpuTimeSeries;`
- L33 _private member_ `TSharedPtr<FGraphSeries> MemoryUsageSeries;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraProvider.h` (Private)


#### struct `UE::NiagaraInsights::FSystemPerformanceFrame_GT`  
`struct FSystemPerformanceFrame_GT`  
_L15-32_
- L29 _public member_ `double Time = 0.0;`
- L30 _public member_ `TArray<TPair<FString, FStats>> SystemData;`
- L31 _public member_ `FStats AccumulatedStats;`

#### struct `UE::NiagaraInsights::FSystemPerformanceFrame_GT::FStats`  
`struct FStats`  
_L17-27_
- L19 _public member_ `uint64 NumInstances = 0;`
- L20 _public member_ `double TickGameThreadSeconds = 0.0;`
- L21 _public member_ `double TickConcurrentSeconds = 0.0;`
- L22 _public member_ `double FinalizeSeconds = 0.0;`
- L23 _public member_ `double EndOfFrameSeconds = 0.0;`
- L24 _public member_ `double ActivationSeconds = 0.0;`
- L25 _public member_ `double WaitSeconds = 0.0;`
- L26 _public member_ `uint64 MemoryBytes = 0;`

#### struct `UE::NiagaraInsights::FSystemPerformanceFrame_RT`  
`struct FSystemPerformanceFrame_RT`  
_L34-49_
- L46 _public member_ `double Time = 0.0;`
- L47 _public member_ `TArray<TPair<FString, FStats>> SystemData;`
- L48 _public member_ `FStats AccumulatedStats;`

#### struct `UE::NiagaraInsights::FSystemPerformanceFrame_RT::FStats`  
`struct FStats`  
_L36-44_
- L38 _public member_ `uint64 NumInstances = 0;`
- L39 _public member_ `double RenderUpdateSeconds = 0.0;`
- L40 _public member_ `double GetDynamicMeshElementsSeconds = 0.0;`
- L42 _public member_ `uint64 GpuNumInstances = 0;`
- L43 _public member_ `uint64 GpuTotalMicroseconds = 0;`

#### struct `UE::NiagaraInsights::FLifetimeEvent`  
`struct FLifetimeEvent`  
_L51-73_
- L69 _public member_ `double Time = 0.0;`
- L70 _public member_ `FString ComponentName;`
- L71 _public member_ `FString SystemName;`
- L72 _public member_ `TVariant<FActivate, FDeactivate, FComplete> Payload;`

#### struct `UE::NiagaraInsights::FLifetimeEvent::FActivate`  
`struct FActivate`  
_L53-58_
- L55 _public member_ `bool bReset = false;`
- L56 _public member_ `bool bIsScalabilityCull = false;`
- L57 _public member_ `bool bAwaitingActivationDueToNotReady = false;`

#### struct `UE::NiagaraInsights::FLifetimeEvent::FDeactivate`  
`struct FDeactivate`  
_L59-63_
- L61 _public member_ `bool bImmediate = false;`
- L62 _public member_ `bool bIsScalabilityCull = false;`

#### struct `UE::NiagaraInsights::FLifetimeEvent::FComplete`  
`struct FComplete`  
_L64-67_
- L66 _public member_ `bool bExternalCompletion = false;`

#### struct `UE::NiagaraInsights::FDataChannelEvent`  
`struct FDataChannelEvent`  
_L75-100_
- L98 _public member_ `double Time = 0.0;`
- L99 _public member_ `TVariant<FPublish, FWrite> Payload;`

#### struct `UE::NiagaraInsights::FDataChannelEvent::FPublish`  
`struct FPublish`  
_L77-86_
- L79 _public member_ `FString SourceName;`
- L80 _public member_ `bool bGpuRequest = false;`
- L81 _public member_ `bool bVisibleToGame = false;`
- L82 _public member_ `bool bVisibleToCPUSims = false;`
- L83 _public member_ `bool bVisibleToGPUSims = false;`
- L84 _public member_ `uint32 NumInstances = 0;`
- L85 _public member_ `uint32 NumInstanceAllocated = 0;`

#### struct `UE::NiagaraInsights::FDataChannelEvent::FWrite`  
`struct FWrite`  
_L88-96_
- L90 _public member_ `FString DataChannelName;`
- L91 _public member_ `FString SourceName;`
- L92 _public member_ `int32 NumInstances = 0;`
- L93 _public member_ `bool bVisibleToGame = false;`
- L94 _public member_ `bool bVisibleToCPU = false;`
- L95 _public member_ `bool bVisibleToGPU = false;`

#### class `UE::NiagaraInsights::FNiagaraProvider`  
`class FNiagaraProvider : public TraceServices::IProvider, public TraceServices::IEditableProvider`  
_L102-163_
- inherits: `TraceServices::IProvider,TraceServices::IEditableProvider`
- L105 _public prototype_ `explicit FNiagaraProvider(TraceServices::IAnalysisSession& InSession);`
- L108 _public prototype_ `virtual void BeginRead() const override;`
- L109 _public prototype_ `virtual void EndRead() const override;`
- L110 _public prototype_ `virtual void ReadAccessCheck() const override;`
- L114 _public prototype_ `virtual void BeginEdit() const override;`
- L115 _public prototype_ `virtual void EndEdit() const override;`
- L116 _public prototype_ `virtual void EditAccessCheck() const override;`
- L119 _public prototype_ `static FName GetProviderName();`
- L122 _public prototype_ `bool HasAnyData() const;` — Returns true if any trace events have been received
- L125 _public prototype_ `void AddSystemPerformance_GT(double EventTime, FStringView SystemName, uint64 NumInstances, double TickGameThreadSeconds, double TickConcurrentSeconds, double FinalizeSeconds, double EndOfFrameSeconds, double ActivationSeconds, double WaitSeconds, uint64 MemoryBytes);` — Add system performance data for the game thread
- L127 _public prototype_ `void AddSystemPerformance_RT(double EventTime, FStringView SystemName, uint64 NumInstances, double RenderUpdateSeconds, double GetDynamicMeshElementsSeconds, uint64 GpuNumInstances, uint64 GpuTotalMicroseconds);` — Add system performnace data for the render thread
- L130 _public prototype_ `void EnumeratePerformance_GT(double StartTime, double EndTime, bool bIncludeOverlapping, TFunction<void(const FSystemPerformanceFrame_GT&)> Evaluate) const;` — Enumerate a range of game thread frames
- L132 _public prototype_ `void EnumeratePerformance_RT(double StartTime, double EndTime, bool bIncludeOverlapping, TFunction<void(const FSystemPerformanceFrame_RT&)> Evaluate) const;` — Enumerate a range of render thread frames
- L135 _public prototype_ `void AddComponentActivate(double EventTime, FStringView ComponentName, bool bReset, bool bIsScalabilityCull, bool bAwaitingActivationDueToNotReady);` — Add component activate event
- L137 _public prototype_ `void AddComponentDeactivate(double EventTime, FStringView ComponentName, bool bImmediate, bool bIsScalabilityCull);` — Add component deactivate event
- L139 _public prototype_ `void AddComponentComplete(double EventTime, FStringView ComponentName, bool bExternalCompletion);` — Add component complete event
- L142 _public prototype_ `void EnumerateComponentEvent(double StartTime, double EndTime, TFunction<void(const FLifetimeEvent&)> Evaluate) const;` — Enumerate a range of component events
- L145 _public prototype_ `void AddDataChannelPublish(double EventTime, FStringView SourceName, bool bGpuRequest, bool bVisibleToGame, bool bVisibleToCPUSims, bool bVisibleToGPUSims, uint32 NumInstances, uint32 NumInstanceAllocated);` — Add data channel publish event
- L147 _public prototype_ `void AddDataChannelWrite(double EventTime, FStringView DataChannelName, FStringView SourceName, int32 NumInstances, bool bVisibleToGame, bool bVisibleToCPU, bool bVisibleToGPU);` — Add data channel write event
- L150 _public prototype_ `void EnumerateDataChannelEvent(double StartTime, double EndTime, TFunction<void(const FDataChannelEvent&)> Evaluate) const;` — Enumerate a range of data channel events
- L153 _private member_ `mutable TraceServices::FProviderLock ProviderLock;`
- L155 _private member_ `TraceServices::IAnalysisSession& Session;`
- L157 _private member_ `TArray<FSystemPerformanceFrame_GT> PerformanceFrames_GT;`
- L158 _private member_ `TArray<FSystemPerformanceFrame_RT> PerformanceFrames_RT;`
- L160 _private member_ `TArray<FLifetimeEvent> LifetimeEvents;`
- L162 _private member_ `TArray<FDataChannelEvent> DataChannelEvents;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraTimingViewExtender.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraTimingViewExtender`  
`class FNiagaraTimingViewExtender : public UE::Insights::Timing::ITimingViewExtender`  
_L16-48_
- inherits: `UE::Insights::Timing::ITimingViewExtender`
- L19 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionBegun, FNiagaraTimingViewSession& );`
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionEnded, FNiagaraTimingViewSession& );`
- L23 _public prototype_ `virtual void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L24 _public prototype_ `virtual void OnEndSession(UE::Insights::Timing::ITimingViewSession& InSession) override;`
- L25 _public prototype_ `virtual void Tick(UE::Insights::Timing::ITimingViewSession& InSession, const TraceServices::IAnalysisSession& InAnalysisSession) override;`
- L26 _public prototype_ `virtual void ExtendFilterMenu(UE::Insights::Timing::ITimingViewSession& InSession, FMenuBuilder& InMenuBuilder) override;`
- L31 _public prototype_ `FNiagaraTimingViewSession* FindFirstActiveSession();` — Returns the first active Niagara timing-view session, or nullptr if none has started. The stats view uses this to bind to the range-selection delegate.
- L35 _public member_ `FOnSessionBegun OnSessionBegun;` — Fired when a new timing-view session begins (after tracks are created). Observers can use this to late-bind to the session's OnRangeChanged delegate.
- L39 _public member_ `FOnSessionEnded OnSessionEnded;` — Fired when a timing-view session is about to be destroyed. Observers must release any raw pointers to the session before returning.
- L47 _private member_ `TMap<UE::Insights::Timing::ITimingViewSession*, FPerSessionData> PerSessionDataMap;`

#### struct `UE::NiagaraInsights::FNiagaraTimingViewExtender::FPerSessionData`  
`struct FPerSessionData`  
_L42-45_
- L44 _public member_ `TUniquePtr<FNiagaraTimingViewSession> SharedData;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Insights` (scope `UE`)
- L8 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L9 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NiagaraInsights` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionBegun, FNiagaraTimingViewSession& );`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionEnded, FNiagaraTimingViewSession& );`

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraTimingViewSession.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraTimingViewSession`  
`class FNiagaraTimingViewSession`  
_L23-56_
- L26 _public prototype_ `void OnBeginSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L27 _public prototype_ `void OnEndSession(UE::Insights::Timing::ITimingViewSession& InTimingViewSession);`
- L28 _public prototype_ `void Tick(UE::Insights::Timing::ITimingViewSession& InTimingViewSession, const TraceServices::IAnalysisSession& InAnalysisSession);`
- L29 _public prototype_ `void ExtendFilterMenu(FMenuBuilder& InMenuBuilder);`
- L31 _public function_ `bool IsAnalysisSessionValid() const`
- L32 _public function_ `const TraceServices::IAnalysisSession& GetAnalysisSession() const`
- L34 _public function_ `double GetSelectionStartTime() const`
- L35 _public function_ `double GetSelectionEndTime() const`
- L38 _public member_ `FOnNiagaraTimingRangeChanged OnRangeChanged;` — Broadcast when the timing-view selection range changes.
- L41 _public prototype_ `void ToggleNiagaraTrack();` — Show / hide the track
- L44 _private prototype_ `void HandleTimingViewSelectionChanged(UE::Insights::Timing::ETimeChangedFlags Flags, double StartTime, double EndTime);`
- L46 _private member_ `const TraceServices::IAnalysisSession* AnalysisSession = nullptr;`
- L47 _private member_ `UE::Insights::Timing::ITimingViewSession* TimingViewSession = nullptr;`
- L49 _private member_ `TSharedPtr<FNiagaraDataChannelTrack> DataChannelTrack;`
- L50 _private member_ `TSharedPtr<FNiagaraInstanceLifecycleTrack> InstanceLifecycleTrack;`
- L51 _private member_ `TSharedPtr<FNiagaraPerformanceGraphTrack> PerformanceGraphTrack;`
- L53 _private member_ `bool bTrackVisible = true;`
- L54 _private member_ `double SelectionStartTime = 0.0;`
- L55 _private member_ `double SelectionEndTime = 0.0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Insights` (scope `UE`)
- L9 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Insights` (scope `UE`)
- L10 _namespace_ `namespace Timing` (scope `UE::Insights`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NiagaraInsights` (scope `UE`)
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNiagaraTimingRangeChanged, double , double );` — Fired when the user changes the time range selection in the Timing Profiler.
- L21 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNiagaraTimingRangeChanged, double , double );` (scope `UE::NiagaraInsights`) — Fired when the user changes the time range selection in the Timing Profiler.

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/NiagaraTraceModule.h` (Private)


#### class `UE::NiagaraInsights::FNiagaraTraceModule`  
`class FNiagaraTraceModule : public TraceServices::IModule`  
_L10-20_
- inherits: `TraceServices::IModule`
- L14 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;`
- L15 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`
- L16 _public prototype_ `virtual void GetLoggers(TArray<const TCHAR *>& OutLoggers) override;`
- L17 _public prototype_ `virtual void GenerateReports(const TraceServices::IAnalysisSession& Session, const TCHAR* CmdLine, const TCHAR* OutputDirectory) override;`
- L18 _public function_ `virtual const TCHAR* GetCommandLineArgument() override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NiagaraInsights` (scope `UE`)

### `Plugins/FX/NiagaraInsights/Source/NiagaraInsights/Private/Widgets/SNiagaraRangeStatsView.h` (Private)


#### struct `UE::NiagaraInsights::FNiagaraStatsRow`  
`struct FNiagaraStatsRow`  
_L15-23_
- desc: One row in a top-5 table.
- L17 _public member_ `int32 Rank = 0;`
- L18 _public member_ `FString SystemName;`
- L19 _public member_ `float PrimaryValue = 0.f;` — The metric used for ranking (ms, count, …)
- L20 _public member_ `FString PrimaryUnit;` — e.g. "ms", "instances", "ms/inst"
- L21 _public member_ `float SecondaryValue = 0.f;` — Supplementary context (instances, total ms, …)
- L22 _public member_ `FString SecondaryUnit;`

#### class `UE::NiagaraInsights::SNiagaraRangeStatsView`  
`class SNiagaraRangeStatsView : public SCompoundWidget`  
_L39-141_
- inherits: `SCompoundWidget`
- desc: Displays top-5 Niagara systems across six metric categories for the time range selected in the Timing Profiler. Categories: 1. Instance Count           — avg active instances (GT) 2. Game Thread Cost         — total GT cost (ms) 3. GT Cost / Instance       — avg GT ms per live instance 4. Render Thread Cost       — total RT cost (ms) 5. RT Cost / Instance       — avg RT ms per live instance 6. GPU Cost                 — total GPU cost (ms)
- L42 _public function_ `SLATE_BEGIN_ARGS(SNiagaraRangeStatsView)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public prototype_ `virtual ~SNiagaraRangeStatsView();`
- L77 _private prototype_ `void RebuildStats(double StartTime, double EndTime);`
- L79 _private prototype_ `static TArray<FNiagaraStatsRowPtr> BuildTop5( const TArray<FAggregated>& Data, TFunctionRef<float(const FAggregated&)> PrimaryGetter, const FString& PrimaryUnit, TFunctionRef<float(const FAggregated&)> SecondaryGetter, const FString& SecondaryUnit);`
- L88 _private prototype_ `TSharedRef<SWidget> MakeRangeHeaderBar();`
- L91 _private prototype_ `TSharedRef<SWidget> MakeStatsSection( const FText& SectionTitle, const FLinearColor& HeaderColor, const FText& PrimaryColumnLabel, const FText& SecondaryColumnLabel, TArray<FNiagaraStatsRowPtr>& Rows);` — Build one collapsible top-5 section.
- L98 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow( FNiagaraStatsRowPtr Item, const TSharedRef<STableViewBase>& OwnerTable, const FText& PrimaryColumnLabel, const FText& SecondaryColumnLabel);`
- L106 _private prototype_ `void TryBindToActiveSession();`
- L107 _private prototype_ `void OnNiagaraTimingSessionBegun(FNiagaraTimingViewSession& Session);`
- L108 _private prototype_ `void OnNiagaraTimingSessionEnded(FNiagaraTimingViewSession& Session);`
- L109 _private prototype_ `void OnTimingRangeChanged(double StartTime, double EndTime);`
- L110 _private prototype_ `void UnbindCurrentSession();`
- L112 _private member_ `FNiagaraTimingViewSession* BoundSession = nullptr;`
- L113 _private member_ `FDelegateHandle RangeChangedHandle;`
- L117 _private member_ `FText RangeText;`
- L118 _private member_ `FText FrameCountText;`
- L119 _private member_ `double CurrentStartTime = 0.0;`
- L120 _private member_ `double CurrentEndTime = 0.0;`
- L123 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_InstanceCount;` — Six top-5 row arrays — rebuilt whenever the range changes.
- L124 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_GTCostTotal;`
- L125 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_GTCostPerInst;`
- L126 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_RTCostTotal;`
- L127 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_RTCostPerInst;`
- L128 _private member_ `TArray<FNiagaraStatsRowPtr> Rows_GpuCostTotal;`
- L131 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_InstanceCount;` — List-view widgets so we can call RequestListRefresh().
- L132 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_GTCostTotal;`
- L133 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_GTCostPerInst;`
- L134 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_RTCostTotal;`
- L135 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_RTCostPerInst;`
- L136 _private member_ `TSharedPtr<SListView<FNiagaraStatsRowPtr>> ListView_GpuCostTotal;`
- L139 _private member_ `TSharedPtr<STextBlock> RangeTextWidget;` — Range header text widgets so we can update them in-place.
- L140 _private member_ `TSharedPtr<STextBlock> FrameCountWidget;`

#### struct `UE::NiagaraInsights::SNiagaraRangeStatsView::FAggregated`  
`struct FAggregated`  
_L52-75_
- desc: Aggregated per-system data accumulated while scanning a range.
- L54 _public member_ `FString SystemName;`
- L57 _public member_ `uint64 GTSamples = 0;` — Game thread
- L58 _public member_ `double GTTotalInstances = 0.0;` — sum of NumInstances across GT frames
- L59 _public member_ `double GTTotalMs = 0.0;` — total GT wall-clock ms
- L62 _public member_ `uint64 RTSamples = 0;` — Render thread
- L63 _public member_ `double RTTotalInstances = 0.0;`
- L64 _public member_ `double RTTotalMs = 0.0;`
- L67 _public member_ `double GpuTotalMs = 0.0;` — GPU
- L68 _public member_ `double GpuTotalInst = 0.0;`
- L71 _public function_ `double AvgGTInstances() const` — Derived
- L72 _public function_ `double GTCostPerInst() const`
- L73 _public function_ `double RTCostPerInst() const`
- L74 _public function_ `double GpuCostPerInst() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NiagaraInsights` (scope `UE`)
- L25 _typedef_ `using FNiagaraStatsRowPtr = TSharedPtr<FNiagaraStatsRow>;` (scope `UE::NiagaraInsights`)
