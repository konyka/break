# Runtime / MassDeveloper

- module root: `Source/Runtime/Mass/MassDeveloper`
- headers: 3; symbols: 150
- symbol kinds: class=5, delegate=1, enum=3, enumerator=18, externvar=1, function=11, macro=1, member=35, namespace=11, prototype=60, struct=4
- PrivateDependencyModuleNames: TraceAnalysis, TraceLog
- PublicDependencyModuleNames: Core, TraceServices

### `Source/Runtime/Mass/MassDeveloper/Private/Trace/MassTraceAnalyzer.h` (Private)


#### class `UE::Mass::Trace::FMassTraceAnalyzer`  
`class FMassTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L22-45_
- inherits: `UE::Trace::IAnalyzer`
- desc: Analyzer for Mass trace events, parses the trace events from the 'MassTrace' Logger.
- L26 _public prototype_ `FMassTraceAnalyzer(TraceServices::IAnalysisSession& InSession, TSharedRef<FMassTraceProvider> InProvider);`
- L27 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L28 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L29 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L43 _private member_ `TraceServices::IAnalysisSession& Session;`
- L44 _private member_ `TSharedRef<FMassTraceProvider> MassTraceProvider;`

#### enum `UE::Mass::Trace::FMassTraceAnalyzer::(anonymous)`  
``  
_L33-41_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace TraceServices`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mass` (scope `UE`)
- L15 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L34 _enumerator_ `RouteId_RegisterMassFragment` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L35 _enumerator_ `RouteId_RegisterMassArchetype` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L36 _enumerator_ `RouteId_MassBulkAddEntity` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L37 _enumerator_ `RouteId_MassEntityMoved` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L38 _enumerator_ `RouteId_MassBulkEntityDestroyed` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L39 _enumerator_ `RouteId_MassPhaseBegin` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)
- L40 _enumerator_ `RouteId_MassPhaseEnd` (scope `UE::Mass::Trace::FMassTraceAnalyzer::__anon33be059c0103`)

### `Source/Runtime/Mass/MassDeveloper/Private/Trace/MassTraceProvider.h` (Private)


#### class `UE::Mass::Trace::FMassTraceProvider`  
`class FMassTraceProvider : public IMassTraceProvider , public IEditableMassTraceProvider`  
_L26-142_
- inherits: `IMassTraceProvider,IEditableMassTraceProvider`
- L31 _public prototype_ `explicit FMassTraceProvider(TraceServices::IAnalysisSession& InSession);`
- L32 _public prototype_ `virtual ~FMassTraceProvider() override = default;`
- L36 _public function_ `virtual void BeginRead() const override`
- L40 _public function_ `virtual void EndRead() const override`
- L44 _public function_ `virtual void ReadAccessCheck() const override`
- L49 _public prototype_ `virtual int32 GetFragmentCount() const override;`
- L50 _public prototype_ `virtual const FFragmentInfo* FindFragmentById(uint64 FragmentId) const override;`
- L51 _public prototype_ `virtual const FArchetypeInfo* FindArchetypeById(uint64 ArchetypeId) const override;`
- L53 _public prototype_ `virtual void EnumerateFragments(TFunctionRef<void(const FFragmentInfo& FragmentInfo, int32 Index)> Callback, int32 BeginIndex = 0) const override;`
- L55 _public prototype_ `virtual uint64 GetEntityEventCount() const override;`
- L56 _public prototype_ `virtual TValueOrError<FEntityEventRecord, void> GetEntityEvent(uint64 EventIndex) const override;`
- L57 _public prototype_ `virtual void EnumerateEntityEvents( uint64 StartIndex, uint64 Count, TFunctionRef<void(const FEntityEventRecord&, uint64 )> Callback) const override;`
- L62 _public prototype_ `virtual uint64 GetRegionCount() const override;`
- L63 _public prototype_ `virtual int32 GetLaneCount() const override;`
- L65 _public prototype_ `virtual const FRegionLane* GetLane(int32 Index) const override;`
- L67 _public prototype_ `virtual bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FRegion&)> Callback) const override;`
- L68 _public prototype_ `virtual void EnumerateLanes(TFunctionRef<void(const FRegionLane&, const int32)> Callback) const override;`
- L70 _public function_ `virtual uint64 GetUpdateCounter() const override`
- L78 _public function_ `virtual void BeginEdit() const override`
- L82 _public function_ `virtual void EndEdit() const override`
- L86 _public function_ `virtual void EditAccessCheck() const override`
- L91 _public prototype_ `virtual void AddFragment(const FFragmentInfo& FragmentInfo) override;`
- L92 _public prototype_ `virtual void AddArchetype(const FArchetypeInfo& ArchetypeInfo) override;`
- L94 _public prototype_ `virtual void BulkAddEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities, TConstArrayView<uint64> ArchetypeIDs) override;`
- L95 _public prototype_ `virtual void BulkMoveEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities, TConstArrayView<uint64> ArchetypeIDs) override;`
- L96 _public prototype_ `virtual void BulkDestroyEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities) override;`
- L98 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, uint64 ID, double Time) override;`
- L99 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, double Time) override;`
- L100 _public prototype_ `virtual void AppendRegionEnd(const TCHAR* Name, double Time) override;`
- L101 _public prototype_ `virtual void AppendRegionEnd(const uint64 ID, double Time) override;`
- L103 _public prototype_ `virtual void OnAnalysisSessionEnded() override;`
- L107 _private prototype_ `int32 CalculateRegionDepth(const FRegion& Item) const;` — Update the depth member of a region to allow overlapping regions to be displayed on separate lanes.
- L108 _private prototype_ `void AppendRegionEndInternal(FRegion* OpenRegion, double Time);`
- L111 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L113 _private member_ `TraceServices::IAnalysisSession& Session;`
- L115 _private member_ `TMap<uint64, const FFragmentInfo*> FragmentInfoByID;`
- L116 _private member_ `TChunkedArray<FFragmentInfo> FragmentInfos;`
- L119 _private member_ `TChunkedArray<const FFragmentInfo*> FragmentInfoRanges;` — Allocation of ranges of fragments, mostly for ArchetypeInfo
- L121 _private member_ `TMap<uint64, const FArchetypeInfo*> ArchetypeByID;`
- L122 _private member_ `TChunkedArray<FArchetypeInfo> ArchetypeInfos;`
- L125 _private member_ `TraceServices::TPagedArray<FEntityEventRecord> EntityEvents;` — Sorted by Cycle
- L128 _private member_ `TMap<FStringView, FRegion*> OpenRegionsByName;` — Open regions inside lanes
- L129 _private member_ `TMap<uint64, FRegion*> OpenRegionsByID;`
- L132 _private member_ `TArray<FRegionLane> Lanes;` — Closed regions
- L135 _private member_ `uint64 UpdateCounter = 0;` — Counter incremented each time region data changes during analysis
- L137 _private member_ `static constexpr uint32 MaxWarningMessages = 100;`
- L138 _private member_ `static constexpr uint32 MaxErrorMessages = 100;`
- L140 _private member_ `uint32 NumWarnings = 0;`
- L141 _private member_ `uint32 NumErrors = 0;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassTrace, Display, All) namespace TraceServices { class FAnalysisSessionLock; class FStringStore; } namespace UE::Mass::Trace { extern thread_local TraceServices::FProviderLock::FThreadLocalState GMassInsightsProviderLockState; class FMassTraceProvider : public IMassTraceProvider , public IEditableMassTraceProvider { public: explicit FMassTraceProvider(TraceServices::IAnalysisSession& InSession); virtual ~FMassTraceProvider() override = default;`
- L15 _namespace_ `namespace TraceServices`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Mass` (scope `UE`)
- L21 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L24 _externvar_ `extern thread_local TraceServices::FProviderLock::FThreadLocalState GMassInsightsProviderLockState;` (scope `UE::Mass::Trace`)

### `Source/Runtime/Mass/MassDeveloper/Public/Trace/MassTraceTypes.h` (Public)


#### struct `UE::Mass::Trace::FRegion`  
`struct FRegion`  
_L17-25_
- L19 _public member_ `double BeginTime = std::numeric_limits<double>::infinity();`
- L20 _public member_ `double EndTime = std::numeric_limits<double>::infinity();`
- L21 _public member_ `const TCHAR* Text = nullptr;`
- L23 _public member_ `uint64 ID = 0;` — ID will be zero if the region is identified by Name only
- L24 _public member_ `int32 Depth = -1;`

#### class `UE::Mass::Trace::FRegionLane`  
`class FRegionLane`  
_L27-52_
- L32 _public function_ `explicit FRegionLane(TraceServices::ILinearAllocator& InAllocator) : Regions(InAllocator, 512)`
- L36 _public function_ `int32 Num() const`
- L48 _public prototype_ `bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FRegion&)> Callback) const;` — Call Callback for every region overlapping the interval defined by IntervalStart and IntervalEnd @param IntervalStart the start time of the interval to enumerate regions for. @param IntervalEnd the end time of the interval to enumerate regions for. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L51 _private member_ `TraceServices::TPagedArray<FRegion> Regions;`

#### enum `UE::Mass::Trace::EFragmentType`  
`enum class EFragmentType : uint8`  
_L54-63_
- L56 _public enumerator_ `Unknown`
- L57 _public enumerator_ `Fragment`
- L58 _public enumerator_ `Tag`
- L59 _public enumerator_ `Shared`
- L60 _public enumerator_ `Sparse`
- L61 _public enumerator_ `ConstShared`
- L62 _public enumerator_ `SparseTag`

#### struct `UE::Mass::Trace::FFragmentInfo`  
`struct FFragmentInfo`  
_L65-76_
- L67 _public member_ `uint64 Id = INDEX_NONE;`
- L68 _public member_ `FString Name;`
- L69 _public member_ `uint32 Size = 0;`
- L70 _public member_ `EFragmentType Type = EFragmentType::Unknown;`
- L72 _public function_ `const TCHAR* GetName() const`

#### struct `UE::Mass::Trace::FArchetypeInfo`  
`struct FArchetypeInfo`  
_L78-87_
- L80 _public member_ `uint64 Id = INDEX_NONE;`
- L81 _public member_ `TArray<const FFragmentInfo*> Fragments;`
- L83 _public function_ `TConstArrayView<const FFragmentInfo*> GetFragments() const`

#### enum `UE::Mass::Trace::EEntityEventType`  
`enum class EEntityEventType : uint8`  
_L89-95_
- L91 _public enumerator_ `Unknown`
- L92 _public enumerator_ `Created`
- L93 _public enumerator_ `ArchetypeChange`
- L94 _public enumerator_ `Destroyed`

#### struct `UE::Mass::Trace::FEntityEventRecord`  
`struct FEntityEventRecord`  
_L97-108_
- L101 _public member_ `double Time = 0;` — RecordingTime (ElapsedTime) — game time that freezes during pauses. This is the time domain the RewindDebugger scrub/view range operates in.
- L104 _public member_ `double ProfileTime = 0;` — ProfileTime — wall-clock time that keeps advancing during pauses. Used for frame index resolution via IFrameProvider.
- L105 _public member_ `uint64 Entity = INDEX_NONE;`
- L106 _public member_ `uint64 ArchetypeID = INDEX_NONE;`
- L107 _public member_ `EEntityEventType Operation = EEntityEventType::Unknown;`

#### class `UE::Mass::Trace::IMassTraceProvider`  
`class IMassTraceProvider : public TraceServices::IProvider`  
_L110-171_
- inherits: `TraceServices::IProvider`
- L114 _public prototype_ `virtual ~IMassTraceProvider() override = default;`
- L116 _public prototype_ `virtual int32 GetFragmentCount() const = 0;`
- L117 _public prototype_ `virtual const FFragmentInfo* FindFragmentById(uint64 FragmentId) const = 0;`
- L118 _public prototype_ `virtual const FArchetypeInfo* FindArchetypeById(uint64 ArchetypeId) const = 0;`
- L120 _public prototype_ `virtual void EnumerateFragments(TFunctionRef<void(const FFragmentInfo& FragmentInfo, int32 Index)> Callback, int32 BeginIndex = 0) const = 0;`
- L122 _public prototype_ `virtual TValueOrError<FEntityEventRecord, void> GetEntityEvent(uint64 EventIndex) const = 0;`
- L124 _public prototype_ `virtual uint64 GetEntityEventCount() const = 0;`
- L130 _public prototype_ `virtual void EnumerateEntityEvents( uint64 StartIndex, uint64 Count, TFunctionRef<void(const FEntityEventRecord&, uint64 EventIndex)> Callback) const = 0;` — Enumerate up to Count number of events starting at the StartIndex Enumeration will end early if there is not enough events or if Callback returns false
- L138 _public prototype_ `virtual uint64 GetRegionCount() const = 0;` — @return the amount of currently known regions (including open-ended ones)
- L143 _public prototype_ `virtual int32 GetLaneCount() const = 0;` — @return the number of lanes
- L150 _public prototype_ `virtual const FRegionLane* GetLane(int32 Index) const = 0;` — Direct access to a certain lane at a given index/depth. The pointer is valid only in the current read scope. @return a pointer to the lane at the specified depth index or nullptr if Index > GetLaneCount()-1
- L159 _public prototype_ `virtual bool EnumerateRegions(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FRegion&)> Callback) const = 0;` — Enumerates all regions that overlap a certain time interval. Will enumerate by depth but does not expose lanes. @param IntervalStart the start time of the interval to enumerate regions for. @param IntervalEnd the end time of the interval to enumerate regions for. @param Callback a callback called for each region. Return false to abort iteration. @returns true if the enumeration finished, false if it was aborted by the callback returning false
- L164 _public prototype_ `virtual void EnumerateLanes(TFunctionRef<void(const FRegionLane&, const int32)> Callback) const = 0;` — Will call Callback(Lane, Depth) for each lane in order.
- L170 _public prototype_ `virtual uint64 GetUpdateCounter() const = 0;` — @return A monotonically increasing counter that that changes each time new data is added to the provider. This can be used to detect when to update any (UI-)state dependent on the provider during analysis.

#### class `UE::Mass::Trace::IEditableMassTraceProvider`  
`class IEditableMassTraceProvider : public TraceServices::IEditableProvider`  
_L176-227_
- inherits: `TraceServices::IEditableProvider`
- desc: The interface to a provider that can consume mutations of region events from a session.
- L180 _public prototype_ `virtual ~IEditableMassTraceProvider() override = default;`
- L182 _public prototype_ `virtual void AddFragment(const FFragmentInfo& FragmentInfo) = 0;`
- L183 _public prototype_ `virtual void AddArchetype(const FArchetypeInfo& ArchetypeInfo) = 0;`
- L185 _public prototype_ `virtual void BulkAddEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities, TConstArrayView<uint64> ArchetypeIDs) = 0;`
- L186 _public prototype_ `virtual void BulkMoveEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities, TConstArrayView<uint64> ArchetypeIDs) = 0;`
- L187 _public prototype_ `virtual void BulkDestroyEntity(double RecordingTime, double ProfileTime, TConstArrayView<uint64> Entities) = 0;`
- L195 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, double Time) = 0;` — Append a new begin event of a region from the trace session. @param Name		The string name of the region. @param Time		The time in seconds of the begin event of this region.
- L204 _public prototype_ `virtual void AppendRegionBegin(const TCHAR* Name, uint64 ID, double Time) = 0;` — Append a new begin event of a region from the trace session. @param Name		The string name of the region. @param ID		The ID of the region. Used to uniquely identify regions with the same name. @param Time		The time in seconds of the begin event of this region.
- L212 _public prototype_ `virtual void AppendRegionEnd(const TCHAR* Name, double Time) = 0;` — Append a new end event of a region from the trace session (by Name). @param Name		The string name of the region. @param Time		The time in seconds of the end event of this region.
- L220 _public prototype_ `virtual void AppendRegionEnd(const uint64 ID, double Time) = 0;` — Append a new end event of a region from the trace session (by ID). @param ID		The ID of the region. @param Time		The time in seconds of the end event of this region.
- L226 _public prototype_ `virtual void OnAnalysisSessionEnded() = 0;` — Called from the analyzer once all events have been processed. Allows postprocessing and error reporting for regions that were never closed.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MASSDEVELOPER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mass` (scope `UE`)
- L14 _namespace_ `namespace Trace` (scope `UE::Mass`)
- L231 _prototype_ `FName GetProviderName();` (scope `UE::Mass::Trace`)
- L232 _prototype_ `void SetupMassTraceAnalysis(TraceServices::IAnalysisSession& InSession);` (scope `UE::Mass::Trace`)
- L234 _prototype_ `const IMassTraceProvider& ReadMassTraceProvider(const TraceServices::IAnalysisSession& Session);` (scope `UE::Mass::Trace`)
- L235 _prototype_ `IEditableMassTraceProvider& EditMassTraceProvider(TraceServices::IAnalysisSession& Session);` (scope `UE::Mass::Trace`)
