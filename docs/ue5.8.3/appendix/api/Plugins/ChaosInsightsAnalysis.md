# Plugins / ChaosInsightsAnalysis

- module root: `Plugins/ChaosInsights/Source/ChaosInsightsAnalysis`
- headers: 4; symbols: 77
- symbol kinds: class=6, delegate=1, enum=1, enumerator=3, externvar=1, macro=1, member=16, namespace=6, prototype=41, struct=1
- PrivateDependencyModuleNames: CoreUObject, TraceAnalysis, TraceLog, TraceServices
- PublicDependencyModuleNames: Core

### `Plugins/ChaosInsights/Source/ChaosInsightsAnalysis/Private/Analyzers/ChaosInsightsTraceAnalysis.h` (Private)


#### class `ChaosInsightsAnalysis::FLockRegionsTraceAnalyzer`  
`class FLockRegionsTraceAnalyzer : public UE::Trace::IAnalyzer`  
_L17-36_
- inherits: `UE::Trace::IAnalyzer`
- L20 _public prototype_ `FLockRegionsTraceAnalyzer(TraceServices::IAnalysisSession& Session, FLockRegionProvider& RegionProvider);`
- L22 _public prototype_ `virtual void OnAnalysisBegin(const FOnAnalysisContext& Context) override;`
- L23 _public prototype_ `virtual void OnAnalysisEnd() override;`
- L24 _public prototype_ `virtual bool OnEvent(uint16 RouteId, EStyle Style, const FOnEventContext& Context) override;`
- L34 _private member_ `TraceServices::IAnalysisSession& Session;`
- L35 _private member_ `FLockRegionProvider& RegionProvider;`

#### enum `ChaosInsightsAnalysis::FLockRegionsTraceAnalyzer::ELockRegionEventId`  
`enum class ELockRegionEventId : uint16`  
_L27-32_
- L29 _public enumerator_ `LockBegin`
- L30 _public enumerator_ `LockAcquire`
- L31 _public enumerator_ `LockEnd`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace TraceServices`
- L13 _namespace_ `namespace ChaosInsightsAnalysis`

### `Plugins/ChaosInsights/Source/ChaosInsightsAnalysis/Private/ChaosInsightsAnalysisModule.h` (Private)


#### class `ChaosInsightsAnalysis::FChaosInsightsAnalysisModule`  
`class FChaosInsightsAnalysisModule : public IModuleInterface, TraceServices::IModule`  
_L12-23_
- inherits: `IModuleInterface,TraceServices::IModule`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual void GetModuleInfo(TraceServices::FModuleInfo& OutModuleInfo) override;` — TraceServices::IModule interface
- L22 _public prototype_ `virtual void OnAnalysisBegin(TraceServices::IAnalysisSession& Session) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ChaosInsightsAnalysis`

### `Plugins/ChaosInsights/Source/ChaosInsightsAnalysis/Private/Model/LockRegions.h` (Private)


#### class `ChaosInsightsAnalysis::FLockRegionProvider`  
`class FLockRegionProvider : public ILockRegionProvider, public IEditableLockRegionProvider`  
_L21-66_
- inherits: `ILockRegionProvider,IEditableLockRegionProvider`
- L24 _public prototype_ `explicit FLockRegionProvider(TraceServices::IAnalysisSession& Session);`
- L30 _public prototype_ `virtual void BeginRead() const override;`
- L31 _public prototype_ `virtual void EndRead() const override;`
- L32 _public prototype_ `virtual void ReadAccessCheck() const override;`
- L34 _public prototype_ `virtual uint64 GetRegionCount() const override;`
- L35 _public prototype_ `virtual int32 GetLaneCount() const override;`
- L37 _public prototype_ `virtual const FLockRegionLane* GetLane(int32 Index) const override;`
- L39 _public prototype_ `virtual bool ForEachRegionInRange(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FLockRegion&)> Callback) const override;`
- L40 _public prototype_ `virtual void ForEachLane(TFunctionRef<void(const FLockRegionLane&, const int32)> Callback) const override;`
- L45 _public prototype_ `virtual void BeginEdit() const override;`
- L46 _public prototype_ `virtual void EndEdit() const override;`
- L47 _public prototype_ `virtual void EditAccessCheck() const override;`
- L49 _public prototype_ `virtual void AppendRegionBegin(double Time, uint64 ThreadId, bool bWrite) override;`
- L50 _public prototype_ `virtual void AppendRegionAcquired(double Time, uint64 ThreadId) override;`
- L51 _public prototype_ `virtual void AppendRegionEnd(double Time, uint64 ThreadId) override;`
- L53 _public prototype_ `virtual void OnAnalysisSessionEnded() override;`
- L58 _private prototype_ `int32 CalculateRegionDepth(double NewBeginTime) const;`
- L59 _private prototype_ `void UpdateSession(double InTime);`
- L61 _private member_ `TraceServices::IAnalysisSession& Session;`
- L62 _private member_ `mutable TraceServices::FProviderLock Lock;`
- L64 _private member_ `TMap<uint64_t, FLockRegion*> OpenRegionsByThread;`
- L65 _private member_ `TArray<FLockRegionLane> Lanes;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosInsights, Display, All) namespace TraceServices { class FAnalysisSessionLock; class FStringStore; } namespace ChaosInsightsAnalysis { extern thread_local TraceServices::FProviderLock::FThreadLocalState GLockRegionsProviderLockState; class FLockRegionProvider : public ILockRegionProvider, public IEditableLockRegionProvider { public: explicit FLockRegionProvider(TraceServices::IAnalysisSession& Session); virtual ~FLockRegionProvider() override;`
- L11 _namespace_ `namespace TraceServices`
- L17 _namespace_ `namespace ChaosInsightsAnalysis`
- L19 _externvar_ `extern thread_local TraceServices::FProviderLock::FThreadLocalState GLockRegionsProviderLockState;` (scope `ChaosInsightsAnalysis`)

### `Plugins/ChaosInsights/Source/ChaosInsightsAnalysis/Public/ChaosInsightsAnalysis/Model/LockRegions.h` (Public)


#### struct `ChaosInsightsAnalysis::FLockRegion`  
`struct FLockRegion`  
_L16-44_
- L19 _public member_ `double BeginTime = std::numeric_limits<double>::infinity();` — Time that the caller attempted to take the lock
- L22 _public member_ `double AcquireTime = std::numeric_limits<double>::infinity();` — Time that the lock was actually acquired (including waiting on the lock if it was already taken)
- L25 _public member_ `double EndTime = std::numeric_limits<double>::infinity();` — Time that the caller relinquished the lock
- L28 _public member_ `const TCHAR* Text = nullptr;` — Name of the thread that took the lock
- L31 _public member_ `uint64 Thread;` — The local thread Id for the thread that took the lock
- L34 _public member_ `int32 Depth = -1;` — UI depth
- L37 _public member_ `int32 LockCount = 0;` — Number of times a lock was taken during the region
- L40 _public member_ `int32 LockDepth = 0;` — Tracking for the lock depth to combine all recursive locks into one region
- L43 _public member_ `bool bIsWrite = false;` — Whether this is a write-lock (as opposed to a read-lock)

#### class `ChaosInsightsAnalysis::FLockRegionLane`  
`class FLockRegionLane`  
_L46-59_
- L51 _public prototype_ `FLockRegionLane(TraceServices::ILinearAllocator& InAllocator);`
- L53 _public prototype_ `int32 Num() const;`
- L55 _public prototype_ `bool ForEachRegionInRange(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FLockRegion&)> Callback) const;`
- L58 _private member_ `TraceServices::TPagedArray<FLockRegion> Regions;`

#### class `ChaosInsightsAnalysis::ILockRegionProvider`  
`class ILockRegionProvider : public TraceServices::IProvider`  
_L61-72_
- inherits: `TraceServices::IProvider`
- L66 _public prototype_ `virtual uint64 GetRegionCount() const = 0;`
- L67 _public prototype_ `virtual int32 GetLaneCount() const = 0;`
- L68 _public prototype_ `virtual const FLockRegionLane* GetLane(int32 Index) const = 0;`
- L70 _public prototype_ `virtual bool ForEachRegionInRange(double IntervalStart, double IntervalEnd, TFunctionRef<bool(const FLockRegion&)> Callback) const = 0;`
- L71 _public prototype_ `virtual void ForEachLane(TFunctionRef<void(const FLockRegionLane&, const int32)> Callback) const = 0;`

#### class `ChaosInsightsAnalysis::IEditableLockRegionProvider`  
`class IEditableLockRegionProvider : public TraceServices::IEditableProvider`  
_L74-84_
- inherits: `TraceServices::IEditableProvider`
- L79 _public prototype_ `virtual void AppendRegionBegin(double Time, uint64 ThreadId, bool bIsWrite) = 0;`
- L80 _public prototype_ `virtual void AppendRegionAcquired(double Time, uint64 ThreadId) = 0;`
- L81 _public prototype_ `virtual void AppendRegionEnd(double Time, uint64 ThreadId) = 0;`
- L83 _public prototype_ `virtual void OnAnalysisSessionEnded() = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSINSIGHTSANALYSIS_API`
- L13 _namespace_ `namespace ChaosInsightsAnalysis`
- L88 _prototype_ `FName GetLockRegionProviderName();` (scope `ChaosInsightsAnalysis`)
- L89 _prototype_ `const ILockRegionProvider& ReadRegionProvider(const TraceServices::IAnalysisSession& Session);` (scope `ChaosInsightsAnalysis`)
- L90 _prototype_ `IEditableLockRegionProvider& EditRegionProvider(TraceServices::IAnalysisSession& Session);` (scope `ChaosInsightsAnalysis`)
