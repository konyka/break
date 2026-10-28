# Programs / TraceQuery

- module root: `Source/Programs/TraceQuery`
- headers: 3; symbols: 175
- symbol kinds: class=4, delegate=1, enum=2, enumerator=11, function=16, member=92, prototype=39, struct=10
- PrivateDependencyModuleNames: Core, Json, Projects, TraceAnalysis, TraceServices
- PublicIncludePathModuleNames: Launch

### `Source/Programs/TraceQuery/Private/JsonTraceAnalyzer.h` (Private)


#### struct `FScopeGroupKey`  
`struct FScopeGroupKey`  
_L30-39_
- desc: Key for grouping CPU scope events by (ThreadId, SpecId)
- L32 _public member_ `uint32 ThreadId;`
- L33 _public member_ `uint32 SpecId;`
- L35 _public function_ `bool operator==(const FScopeGroupKey& Other) const`

#### struct `FScopeDataPoint`  
`struct FScopeDataPoint`  
_L46-52_
- L48 _public member_ `double Time = 0.0;`
- L49 _public member_ `double Duration = 0.0;`
- L50 _public member_ `int32 Depth = 0;`
- L51 _public member_ `uint32 ParentSpecId = 0;`

#### class `FTraceQueryCpuProfilerProvider`  
`class FTraceQueryCpuProfilerProvider : public TraceServices::IEditableThreadProvider , public TraceServices::IEditableTimingProfilerProvider`  
_L62-132_
- inherits: `TraceServices::IEditableThreadProvider,TraceServices::IEditableTimingProfilerProvider`
- L68 _public member_ `const FTraceQueryOptions* Options = nullptr;` — Wired by TraceQuery.cpp before analysis begins
- L69 _public member_ `TMap<FScopeGroupKey, TArray<FScopeDataPoint>>* ScopeGroups = nullptr;`
- L70 _public member_ `uint64* NumCpuSpecs = nullptr;`
- L71 _public member_ `uint64* NumCpuEvents = nullptr;`
- L75 _public member_ `TArray<TPair<double, int64>>* CsvFrameNumbers = nullptr;` — Populated when Options->bWantCsvFrameNumbers is set. Each entry is {frame_start_time_s, csv_frame_number}.
- L78 _public prototype_ `const FString* LookupTimerName(uint32 TimerId) const;` — Resolve a TimerIndex (which may be a ~MetadataId) to its scope name, or nullptr
- L81 _public prototype_ `const FString* LookupThreadName(uint32 ThreadId) const;` — Resolve a ThreadId to its human-readable name (e.g. "GameThread"), or nullptr
- L84 _public prototype_ `void SetThreadName(uint32 ThreadId, const FString& Name);` — Store a thread name (called by FJsonTraceAnalyzer::OnThreadInfo)
- L116 _private prototype_ `virtual void AddThread(uint32 Id, const TCHAR* Name, EThreadPriority Priority) override;` — IEditableThreadProvider
- L119 _private prototype_ `virtual uint32 AddTimer(TraceServices::ETimingProfilerTimerType Type) override;` — IEditableTimingProfilerProvider -- methods called by FCpuProfilerAnalyzer
- L120 _private prototype_ `virtual uint32 AddCpuTimer(FStringView Name, const TCHAR* File, uint32 Line) override;`
- L121 _private prototype_ `virtual void SetTimerName(uint32 TimerId, FStringView Name) override;`
- L122 _private prototype_ `virtual uint32 AddMetadata(uint32 MainTimerId, TArray<uint8>&& Metadata) override;`
- L123 _private prototype_ `virtual TArrayView<uint8> GetEditableMetadata(uint32 TimerId) override;`
- L124 _private prototype_ `virtual TraceServices::IEditableTimeline<TraceServices::FTimingProfilerEvent>& GetCpuThreadEditableTimeline(uint32 ThreadId) override;`
- L126 _private prototype_ `uint32 AddTimerInternal(FStringView Name);`
- L128 _private member_ `TArray<TOptional<FString>> TimerNames;`
- L129 _private member_ `TMap<uint32, FString> ThreadNames;`
- L130 _private member_ `TMap<uint32, TUniquePtr<FThread>> Threads;`
- L131 _private member_ `TArray<FMetadata> Metadatas;`

#### struct `FTraceQueryCpuProfilerProvider::FScopeEnter`  
`struct FScopeEnter`  
_L87-91_
- L89 _public member_ `uint32 TimerId;`
- L90 _public member_ `double StartTime;`

#### struct `FTraceQueryCpuProfilerProvider::FThread`  
`struct FThread : public TraceServices::IEditableTimeline<TraceServices::FTimingProfilerEvent>`  
_L93-107_
- inherits: `TraceServices::IEditableTimeline<TraceServices::FTimingProfilerEvent>`
- L95 _public function_ `FThread(uint32 InThreadId, FTraceQueryCpuProfilerProvider* InProvider) : ThreadId(InThreadId) , Provider(InProvider)`
- L101 _public prototype_ `virtual void AppendBeginEvent(double StartTime, const TraceServices::FTimingProfilerEvent& Event) override;`
- L102 _public prototype_ `virtual void AppendEndEvent(double EndTime) override;`
- L104 _public member_ `uint32 ThreadId;`
- L105 _public member_ `FTraceQueryCpuProfilerProvider* Provider;`
- L106 _public member_ `TArray<FScopeEnter> ScopeStack;`

#### struct `FTraceQueryCpuProfilerProvider::FMetadata`  
`struct FMetadata`  
_L109-113_
- L111 _public member_ `TArray<uint8> Payload;`
- L112 _public member_ `uint32 TimerId;`

#### class `FTraceQueryCounter`  
`class FTraceQueryCounter : public TraceServices::IEditableCounter`  
_L141-169_
- inherits: `TraceServices::IEditableCounter`
- L145 _public member_ `const FTraceQueryOptions* Options = nullptr;` — Wired by provider on creation
- L146 _public member_ `TFunction<void(const char*)> EmitCallback;`
- L147 _public member_ `TFunction<bool(double)> TimeFilterCallback;`
- L148 _public member_ `TFunction<FString(const FString&)> JsonEscapeCallback;`
- L149 _public member_ `uint64* NumCounterValues = nullptr;`
- L151 _public member_ `uint16 CounterId = 0;`
- L154 _public function_ `virtual void SetName(const TCHAR* InName) override` — IEditableCounter
- L155 _public function_ `virtual void SetGroup(const TCHAR* Group) override`
- L156 _public function_ `virtual void SetDescription(const TCHAR* Description) override`
- L157 _public function_ `virtual void SetIsFloatingPoint(bool bIsFloatingPoint) override`
- L158 _public function_ `virtual void SetIsResetEveryFrame(bool bInIsResetEveryFrame) override`
- L159 _public function_ `virtual void SetDisplayHint(TraceServices::ECounterDisplayHint DisplayHint) override`
- L161 _public function_ `virtual void AddValue(double Time, int64 Value) override`
- L162 _public prototype_ `virtual void SetValue(double Time, int64 Value) override;`
- L163 _public function_ `virtual void AddValue(double Time, double Value) override`
- L164 _public prototype_ `virtual void SetValue(double Time, double Value) override;`
- L167 _private member_ `FString Name;`
- L168 _private member_ `bool bIsFloat = false;`

#### class `FTraceQueryCounterProvider`  
`class FTraceQueryCounterProvider : public TraceServices::IEditableCounterProvider`  
_L171-190_
- inherits: `TraceServices::IEditableCounterProvider`
- L175 _public member_ `const FTraceQueryOptions* Options = nullptr;` — Wired by TraceQuery.cpp before analysis begins
- L176 _public member_ `TFunction<void(const char*)> EmitCallback;`
- L177 _public member_ `TFunction<bool(double)> TimeFilterCallback;`
- L178 _public member_ `TFunction<FString(const FString&)> JsonEscapeCallback;`
- L179 _public member_ `uint64* NumCounterSpecs = nullptr;`
- L180 _public member_ `uint64* NumCounterValues = nullptr;`
- L183 _public function_ `virtual const TraceServices::ICounter* GetCounter(TraceServices::IEditableCounter* EditableCounter) override` — IEditableCounterProvider
- L184 _public prototype_ `virtual TraceServices::IEditableCounter* CreateEditableCounter() override;`
- L185 _public function_ `virtual void AddCounter(const TraceServices::ICounter* Counter) override`
- L188 _private member_ `uint16 NextCounterId = 0;`
- L189 _private member_ `TArray<TUniquePtr<FTraceQueryCounter>> Counters;`

#### class `FJsonTraceAnalyzer`  
`class FJsonTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L204-300_
- inherits: `UE::Trace::IAnalyzer`
- L207 _public prototype_ `explicit FJsonTraceAnalyzer(const FTraceQueryOptions& InOptions);`
- L210 _public prototype_ `static FString JsonEscape(const FString& Input);` — Escape a string for JSON output (handles quotes, backslashes, control chars)
- L213 _public prototype_ `bool PassesTimeFilter(double Time) const;` — Output helpers -- public so providers can access them
- L214 _public prototype_ `void EmitJsonLine(const char* JsonLine);`
- L217 _public prototype_ `void EmitMemoryTags(const TraceServices::IMemoryProvider& MemProvider);` — Post-analysis emission -- called from TraceQuery.cpp after Process().Wait()
- L218 _public prototype_ `void EmitMemoryTimeline(const TraceServices::IAllocationsProvider& AllocProvider);`
- L219 _public prototype_ `void EmitAllocationTags(const TraceServices::IAllocationsProvider& AllocProvider);`
- L220 _public prototype_ `void EmitPackageMemory( const TraceServices::IAllocationsProvider& AllocProvider, const TraceServices::IMetadataProvider& MetadataProvider, const TraceServices::IDefinitionProvider& DefinitionProvider, const FPackageMemoryQuery& Query);`
- L225 _public prototype_ `void EmitRegions(const TraceServices::IRegionProvider& RegionProvider);`
- L226 _public prototype_ `void EmitLogMessages(const TraceServices::ILogProvider& LogProvider);`
- L229 _public member_ `TMap<FScopeGroupKey, TArray<FScopeDataPoint>> ScopeGroups;` — Buffered CPU scope data -- populated by CpuProfiler provider, flushed in OnAnalysisEnd
- L233 _public member_ `TArray<TPair<double, int64>> CsvFrameNumbers;` — CSV frame numbers -- populated by CpuProfiler provider when bWantCsvFrameNumbers is set. Entries: {frame_start_time_s, csv_frame_number}, emitted as csv_frame_number records.
- L236 _public member_ `uint64 NumStatsSpecs = 0;` — Summary mode counters -- providers write to these via pointers
- L237 _public member_ `uint64 NumStatsBatches = 0;`
- L238 _public member_ `uint64 NumStatsOps = 0;`
- L239 _public member_ `uint64 NumCounterSpecs = 0;`
- L240 _public member_ `uint64 NumCounterValues = 0;`
- L241 _public member_ `uint64 NumFrames = 0;`
- L242 _public member_ `uint64 NumCpuSpecs = 0;`
- L243 _public member_ `uint64 NumCpuEvents = 0;`
- L244 _public member_ `uint64 NumTotalEvents = 0;`
- L247 _public member_ `FTraceQueryCpuProfilerProvider* CpuProfilerProvider = nullptr;` — Set by TraceQuery.cpp to enable timer/thread name resolution in OnAnalysisEnd
- L251 _private prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;` — IAnalyzer interface
- L252 _private prototype_ `virtual void OnAnalysisEnd() override;`
- L253 _private prototype_ `virtual void OnThreadInfo(const FThreadInfo& ThreadInfo) override;`
- L254 _private prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L257 _private prototype_ `void OnStatsSpec(const FOnEventContext& Context);` — Stats decode (kept -- no factory exists for Stats)
- L258 _private prototype_ `void OnStatsEventBatch(const FOnEventContext& Context, bool bV2);`
- L261 _private prototype_ `void OnDiagnosticsSession2(const FOnEventContext& Context);` — Simple event handlers
- L262 _private prototype_ `void OnBeginFrame(const FOnEventContext& Context);`
- L290 _private member_ `const FTraceQueryOptions& Options;`
- L292 _private member_ `TMap<uint32, FStatSpec> StatSpecs;`
- L293 _private member_ `TMap<uint32, TSharedPtr<FThreadState>> ThreadStates;`
- L297 _private member_ `TMap<uint8, TArray<double>> FrameGroups;` — Buffered frame timestamps -- flushed as grouped JSONL in OnAnalysisEnd Key: frameType (0=game, 1=render)
- L299 _private prototype_ `FThreadState& GetThreadState(uint32 ThreadId);`

#### enum `FJsonTraceAnalyzer::(anonymous)`  
``  
_L265-273_

#### struct `FJsonTraceAnalyzer::FStatSpec`  
`struct FStatSpec`  
_L275-282_
- L277 _public member_ `FString Name;`
- L278 _public member_ `FString Group;`
- L279 _public member_ `FString Description;`
- L280 _public member_ `bool bIsFloatingPoint = false;`
- L281 _public member_ `bool bIsResetEveryFrame = false;`

#### struct `FJsonTraceAnalyzer::FThreadState`  
`struct FThreadState`  
_L285-288_
- desc: Per-thread state for Stats batch decode
- L287 _public member_ `uint64 LastCycle = 0;`

#### struct `FPackageMemoryQuery`  
`struct FPackageMemoryQuery`  
_L306-315_
- L308 _public member_ `FString Id;`
- L309 _public member_ `TraceServices::IAllocationsProvider::EQueryRule Rule = TraceServices::IAllocationsProvider::EQueryRule::Aaf;`
- L311 _public member_ `double TimeA = 0.0;`
- L312 _public member_ `double TimeB = -1.0;`
- L313 _public member_ `double TimeC = 0.0;`
- L314 _public member_ `double TimeD = 0.0;`

#### Free symbols / members of external scopes

- L41 _function_ `inline uint32 GetTypeHash(const FScopeGroupKey& Key)`
- L266 _enumerator_ `RouteId_StatsSpec` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L267 _enumerator_ `RouteId_StatsEventBatch` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L268 _enumerator_ `RouteId_StatsEventBatch2` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L269 _enumerator_ `RouteId_DiagSession` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L270 _enumerator_ `RouteId_DiagSession2` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L271 _enumerator_ `RouteId_BeginFrame` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)
- L272 _enumerator_ `RouteId_AllEvents` (scope `FJsonTraceAnalyzer::__anonc4f612b30103`)

### `Source/Programs/TraceQuery/Private/RegionAnalyzer.h` (Private)


#### struct `FRegionAnalyzer`  
`struct FRegionAnalyzer : public UE::Trace::IAnalyzer`  
_L16-41_
- inherits: `UE::Trace::IAnalyzer`
- L18 _public function_ `FRegionAnalyzer(TraceServices::IAnalysisSession& InSession, TraceServices::FRegionProvider& InProvider) : Session(InSession), RegionProvider(InProvider)`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L29 _private function_ `template <typename TCallback> void DispatchEvent(const FOnEventContext& Context, uint64 CycleValue, TCallback&& ProviderCall)` — Factors out the repeated lock + UpdateDurationSeconds pattern across all 4 OnEvent cases.
- L39 _private member_ `TraceServices::IAnalysisSession& Session;`
- L40 _private member_ `TraceServices::IEditableRegionProvider& RegionProvider;`

#### enum `FRegionAnalyzer::(anonymous)`  
`enum : uint16`  
_L37-38_

#### Free symbols / members of external scopes

- L37 _enumerator_ `enum : uint16 { RouteId_RegionBegin, RouteId_RegionBeginWithId, RouteId_RegionEnd, RouteId_RegionEndWithId }; TraceServices::IAnalysisSession& Session; TraceServices::IEditableRegionProvider& RegionProvider;` (scope `FRegionAnalyzer::__anon67dd5a8e0103`)
- L37 _enumerator_ `enum : uint16 { RouteId_RegionBegin, RouteId_RegionBeginWithId, RouteId_RegionEnd, RouteId_RegionEndWithId }; TraceServices::IAnalysisSession& Session; TraceServices::IEditableRegionProvider& RegionProvider;` (scope `FRegionAnalyzer::__anon67dd5a8e0103`)
- L38 _enumerator_ `RouteId_RegionEnd` (scope `FRegionAnalyzer::__anon67dd5a8e0103`)
- L38 _enumerator_ `RouteId_RegionEnd` (scope `FRegionAnalyzer::__anon67dd5a8e0103`)

### `Source/Programs/TraceQuery/Private/TraceQuery.h` (Private)


#### struct `FTraceQueryOptions`  
`struct FTraceQueryOptions`  
_L15-131_
- desc: Options parsed from the command line that control which trace events are decoded and how the JSONL output is filtered and formatted.
- L17 _public member_ `FString InputFile;`
- L20 _public member_ `FString Logger;` — Filter by logger name (e.g., "Stats", "Counters", "CpuProfiler")
- L23 _public member_ `FString EventPattern;` — Filter by event name pattern (* wildcard)
- L26 _public member_ `FString CounterFilter;` — Filter counters by name substring (matches both Stats-sourced and Counters-channel events)
- L29 _public member_ `FString TimerFilter;` — Filter CPU profiler scopes by name substring
- L33 _public member_ `double TimeA = -1.0;` — Time markers. TimeA/TimeB double as the generic start/end time filter for non-MemoryPackages loggers. -startTime=/-endTime= are accepted as aliases.
- L34 _public member_ `double TimeB = -1.0;`
- L35 _public member_ `double TimeC = 0.0;`
- L36 _public member_ `double TimeD = 0.0;`
- L40 _public member_ `FString ExplicitRule;` — Explicit query rule for -logger=MemoryPackages single-query mode. Empty = auto-derive from TimeA/TimeB (backward compatible).
- L43 _public member_ `bool bSummaryOnly = false;` — Print event type summary to stdout, then exit
- L46 _public member_ `bool bWantStats = true;` — Whether to include specific loggers (derived from -logger and filter flags)
- L47 _public member_ `bool bWantCounters = true;`
- L48 _public member_ `bool bWantCpuProfiler = true;` — Enabled by default  --  cycle stats live in CpuProfiler
- L49 _public member_ `bool bWantAllEvents = false;`
- L52 _public member_ `bool bWantMemoryTags = false;` — Memory logger flags (mutually exclusive with CPU/stats loggers)
- L53 _public member_ `bool bWantMemoryTimeline = false;` — emit total-allocated-memory timeline for spike detection
- L54 _public member_ `bool bWantAllocationTags = false;` — emit per-package/asset allocation tag names (from IAllocationsProvider)
- L55 _public member_ `bool bWantPackageMemory = false;` — emit per-package memory sizes (from allocation metadata "Asset" field)
- L58 _public member_ `bool bWantRegions = false;` — Regions logger flag
- L61 _public member_ `bool bWantLog = false;` — Log logger flag
- L64 _public member_ `bool bWantCsvFrameNumbers = false;` — CsvFrames logger flag
- L67 _public member_ `FString MemoryTagFilter;` — Filter: only emit LLM tags whose name contains this substring (case-insensitive)
- L72 _public member_ `FString QueryFile;` — Path to a JSON file containing multiple MemoryPackages query entries. When set with -logger=MemoryPackages, all queries run in one TraceQuery process. Individual -timeA / -timeB (and their -startTime/-endTime aliases) are ignored when this is set.
- L74 _public function_ `void ResolveLoggerFlags()`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceQuery, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTraceQuery, Log, All);`
