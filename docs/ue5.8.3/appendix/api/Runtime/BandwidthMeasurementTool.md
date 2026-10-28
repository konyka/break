# Runtime / BandwidthMeasurementTool

- module root: `Source/Runtime/Online/Experimental/BandwidthMeasurementTool`
- headers: 1; symbols: 54
- symbol kinds: class=1, delegate=1, function=1, macro=1, member=26, namespace=2, prototype=20, struct=2
- PrivateDependencyModuleNames: BandwidthDebugDelegates, CoreUObject, HTTP
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/Experimental/BandwidthMeasurementTool/Public/BandwidthMeasurementTool.h` (Public)


#### class `FBandwidthMeasurementTool`  
`class FBandwidthMeasurementTool`  
_L19-147_
- L24 _public prototype_ `FBandwidthMeasurementTool();`
- L25 _public prototype_ `~FBandwidthMeasurementTool();`
- L28 _public prototype_ `static FBandwidthMeasurementTool& Get();` — --- Singleton access ---
- L31 _public prototype_ `void Initialize();` — --- Lifecycle (called by module) ---
- L32 _public prototype_ `void Shutdown();`
- L37 _public prototype_ `void RegisterForCompletedMeasurement(TFunction<void(uint64)>&& FunctionPtr);` — Assign to call back function to report when measurement is complete
- L40 _public prototype_ `void BeginMeasurement();` — Trigger measurement
- L43 _public prototype_ `bool IsBandwidthBeingMeasured() const;` — Report out measurement completion
- L46 _public prototype_ `float GetTimeNeededForMeasurement() const;` — Get delay time needed for measurement
- L49 _public prototype_ `void ClearHistory();` — --- Exposed Utility Functions ---
- L51 _public prototype_ `void Log(bool bPrint);`
- L57 _private prototype_ `void CreateRequestTraffic();` — Request Traffic from CDN
- L60 _private prototype_ `void StopMeasuring();` — Tick-able Stop to call after time for measurement has passed
- L63 _private prototype_ `void RecordBandwidthHistory(const uint64 CalculatedBytesPerSecond);` — Queue up bandwidth history
- L66 _private prototype_ `void CalculateAverageBandwidth();` — Calculate base average throughput
- L69 _private prototype_ `void AugmentBandwidthMeasurement(uint64& MeasurementToAlterInBytes) const;` — Apply any alterations to average throughput on case basis, maybe? Think platform needs
- L72 _private prototype_ `uint64 SafeIncrementForUInt64(const uint64 Base, const uint64 Increase) const;` — Helper function to manage uint64 rollover
- L77 _private member_ `static TUniquePtr<FBandwidthMeasurementTool> Instance;` — Singleton instance pointer
- L80 _private member_ `TArray<uint64> RequestMemoryThroughputHistory;` — Queue of fixed size for history average
- L83 _private member_ `UE::BandwidthMeasurement::FOnMeasurementComplete OnBandwidthMeasurementComplete;` — External reporting callback
- L86 _private member_ `uint64 CurrentBandwidthMeasurementInBps = 0;` — Current average throughput
- L89 _private member_ `std::atomic<uint64> TotalBytesReceived = 0;` — The total number of bytes received via http requests this measurement
- L92 _private member_ `TArray<TSharedRef<IHttpRequest>> ActiveRequests;` — Fixed array of TSharedRef<IHttpRequest> to track request states
- L95 _private member_ `FTSTicker::FDelegateHandle MeasurementTimer;` — Tick handle needed to track current measurements time passage
- L98 _private member_ `bool bHasTheLastRequestFinishedEarly = false;` — Used to tell if the final request finished before hitting the maximum run time
- L101 _private member_ `FTSTicker::FDelegateHandle WarmupTimer;` — Tick handle to track time for the "warm up" period
- L104 _private member_ `bool bReadyToMeasureAfterWarmupPeriod = false;` — State Tracking used to allow for communication line warmup
- L107 _private member_ `double MeasurementStartTimestamp = 0.0;` — Wall-clock timestamp (FPlatformTime::Seconds) when post-warmup measurement began
- L110 _private member_ `mutable FTransactionallySafeCriticalSection Mutex;` — Mutex to keep data consistent across multiple potential thread executions
- L128 _public function_ `const FBandwidthSnapshotData& GetTelemetryData() const` — Returns Telemetry Data for reporting
- L139 _public prototype_ `TOptional<FMeasurementQualityStats> ComputeMeasurementQuality() const;` — Computes quality stats from recent measurement history. Returns empty if insufficient data.
- L143 _private member_ `FBandwidthSnapshotData TelemetryData;` — Storage structure for telemetry reporting
- L146 _private member_ `FDelegateHandle EnableChangedDelegate;` — Tracker for Enable state changes

#### struct `FBandwidthMeasurementTool::FBandwidthSnapshotData`  
`struct FBandwidthSnapshotData`  
_L114-125_
- desc: --- Telemetry Data ---
- L116 _public member_ `uint64 FinishRequestCount = 0;`
- L117 _public member_ `uint64 CompleteRequestCount = 0;`
- L118 _public member_ `uint64 PostWarmupCompleteRequestCount = 0;`
- L119 _public member_ `uint64 RecentReportedBytesReceived = 0;`
- L120 _public member_ `double RecentMeasurementTime = 0;`
- L121 _public member_ `uint64 RecentMeasurementInBps = 0;`
- L122 _public member_ `uint64 RecentMeasurementCount = 0;`
- L123 _public member_ `uint64 RecentAverageInBps = 0;`
- L124 _public member_ `TArray<uint64> RecentHistory;`

#### struct `FBandwidthMeasurementTool::FMeasurementQualityStats`  
`struct FMeasurementQualityStats`  
_L131-136_
- desc: Measurement quality stats
- L133 _public member_ `float VariancePercent = 0.f;` — Coefficient of variation as percentage
- L134 _public member_ `uint64 MinBps = 0;`
- L135 _public member_ `uint64 MaxBps = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API BANDWIDTHMEASUREMENTTOOL_API`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBandwidthMeasurementTool, Log, All);`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace BandwidthMeasurement` (scope `UE`)
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMeasurementComplete, uint64);` — Delegate receives a measurement in Bytes Per Second
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMeasurementComplete, uint64);` (scope `UE::BandwidthMeasurement`) — Delegate receives a measurement in Bytes Per Second
