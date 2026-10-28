# Runtime / DownlinkBandwidthManager

- module root: `Source/Runtime/Online/Experimental/DownlinkBandwidthManager`
- headers: 2; symbols: 112
- symbol kinds: class=2, delegate=1, enum=2, enumerator=6, function=7, macro=3, member=53, namespace=2, prototype=29, struct=4, typedef=2, variable=1
- PrivateDependencyModuleNames: BandwidthDebugDelegates, BandwidthMeasurementTool, CoreUObject
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/Experimental/DownlinkBandwidthManager/Public/DownlinkBandwidthManager.h` (Public)


#### enum `UE::BandwidthManager::EBandwidthPriority`  
`enum EBandwidthPriority : uint8`  
_L23-29_
- L25 _public enumerator_ `HighPriority = 0`
- L26 _public enumerator_ `MediumPriority = 1`
- L27 _public enumerator_ `LowPriority = 2`
- L28 _public enumerator_ `WhenAvailable = 3`

#### enum `UE::BandwidthManager::EBandwidthDistributionPriorityState`  
`enum EBandwidthDistributionPriorityState : uint8`  
_L31-35_
- L33 _public enumerator_ `InGameplay`
- L34 _public enumerator_ `IdleGameplay`

#### struct `UE::BandwidthManager::FManagedServiceConfigurableData`  
`struct FManagedServiceConfigurableData`  
_L41-62_
- L43 _public function_ `FManagedServiceConfigurableData() : ComparisonValue(nullptr), InGameplayPriority(EBandwidthPriority::WhenAvailable), IdleGameplayPriority(EBandwidthPriority::WhenAvailable)`
- L49 _public function_ `FManagedServiceConfigurableData(const FManagedServiceConfigurableData& Copyable) : ComparisonValue(Copyable.ComparisonValue), InGameplayPriority(Copyable.InGameplayPriority), IdleGameplayPriority(Copyable.IdleGameplayPriority)`
- L57 _public member_ `TSharedPtr<int32> ComparisonValue;` — Shared Pointer for a preferred bandwidth cap, distribution will prefer the minimum between this and the calculated bandwidth.
- L59 _public member_ `EBandwidthPriority InGameplayPriority;` — The priority to use when the client is considered in active gameplay
- L61 _public member_ `EBandwidthPriority IdleGameplayPriority;` — The priority to use when the client is considered in less active gameplay

#### struct `UE::BandwidthManager::FPriorityBucket`  
`struct FPriorityBucket`  
_L64-69_
- L66 _public function_ `FPriorityBucket()`
- L67 _public member_ `int32 BandwidthAllocationForPriority = 0;`
- L68 _public member_ `uint8 NumberOfServicesAtPriority = 0;`

#### struct `FManagedService`  
`struct FManagedService`  
_L75-98_
- L78 _public function_ `FManagedService(FOnBandwidthUpdate&& CallBack) : bActiveConnection(false), ConfigData(), AllotedBandwidthKbps(0), OnBandwidthUpdate(MoveTemp(CallBack))`
- L85 _public function_ `FManagedService(const FManagedService& Copyable) : DebugName(Copyable.DebugName), bActiveConnection(Copyable.bActiveConnection), ConfigData(Copyable.ConfigData), AllotedBandwidthKbps(Copyable.AllotedBandwidthKbps), OnBandwidthUpdate(MoveTemp(Copyable.OnBandwidthUpdate))`
- L92 _public member_ `FString DebugName;`
- L93 _public member_ `bool bActiveConnection;`
- L94 _public member_ `UE::BandwidthManager::FManagedServiceConfigurableData ConfigData;`
- L95 _public member_ `int32 AllotedBandwidthKbps;`

#### struct `FBandwidthAllocatorTelemetry`  
`struct FBandwidthAllocatorTelemetry`  
_L101-126_
- desc: Telemetry snapshot for analytics reporting
- L103 _public member_ `bool bEnabled = false;`
- L104 _public member_ `bool bEnforcing = false;`
- L105 _public member_ `int32 MeasuredBandwidthKbps = 0;`
- L106 _public member_ `float MeasurementDurationSec = 0.f;`
- L107 _public member_ `int32 MeasurementRequestCount = 0;`
- L108 _public member_ `int32 MeasurementCompletedCount = 0;`
- L109 _public member_ `int32 MeasurementHistoryCount = 0;`
- L110 _public member_ `int32 MeasurementAverageKbps = 0;`
- L111 _public member_ `int32 EffectiveBandwidthKbps = 0;`
- L112 _public member_ `float BandwidthPercentage = 0.f;`
- L113 _public member_ `int32 MinGameplayReserveKbps = 0;`
- L114 _public member_ `int32 NumRegisteredSystems = 0;`
- L115 _public member_ `int32 DecisionCount = 0;`
- L116 _public member_ `int32 ReallocationCount = 0;`
- L117 _public member_ `int32 AllocatorErrors = 0;`
- L118 _public member_ `bool bInGameplay = false;`
- L119 _public member_ `bool bMeasurementSuccess = false;`
- L120 _public member_ `FString MeasurementResult;` — "Success", "Failed", "NotAttempted"
- L122 _public member_ `float MeasurementVariancePercent = 0.f;` — Measurement quality
- L123 _public member_ `int32 MeasurementMinKbps = 0;`
- L124 _public member_ `int32 MeasurementMaxKbps = 0;`
- L125 _public member_ `float MeasurementWarmupSec = 0.f;`

#### class `FDownlinkBandwidthManager`  
`class FDownlinkBandwidthManager`  
_L128-262_
- L134 _public prototype_ `FDownlinkBandwidthManager();`
- L135 _public prototype_ `~FDownlinkBandwidthManager();`
- L137 _public prototype_ `static FDownlinkBandwidthManager& Get();` — --- Singleton access ---
- L140 _public prototype_ `static bool HasLocalUserPassedRolloutCheck();` — Check to see if the probability check for roll out has passed/failed
- L143 _public prototype_ `static bool HasValueEnforcementPassed();` — Check to see if the probability check for roll out has passed/failed and Enforcement is enabled
- L146 _public prototype_ `void Initialize();` — --- Lifecycle (called by module) ---
- L147 _public prototype_ `void Shutdown();`
- L150 _public prototype_ `UE::BandwidthManager::FServiceHandleID RegisterMonitoredService( const FString& ServiceName, UE::BandwidthManager::FManagedServiceConfigurableData& ServiceConfigData, bool StartActive = false, FOnBandwidthUpdate&& Callback = nullptr);` — Service Initialization and registration with Distribution Manager, FOnBandwidthUpdate will report back in Kbps
- L157 _public prototype_ `void UnregisterMonitoredService(UE::BandwidthManager::FServiceHandleID& ServiceID);` — Removes service from manager considerations and invalidates ServiceID after
- L160 _public prototype_ `void SetActivationForService(const UE::BandwidthManager::FServiceHandleID& ServiceID, bool ActiveState);` — Determines if service should be considered for distribution
- L163 _public prototype_ `void ChangeServicePriority(const UE::BandwidthManager::FServiceHandleID& ServiceID, UE::BandwidthManager::EBandwidthPriority NewPriority, UE::BandwidthManager::EBandwidthDistributionPriorityState PriorityState);` — Changes the associated Services Priority according to the priority state
- L166 _public prototype_ `void SetDistributionGameplayState(UE::BandwidthManager::EBandwidthDistributionPriorityState State);` — Ways for the game to communicate back or check to see what priority distribution pattern the manager is in
- L169 _public prototype_ `void SetIncomingBandwidthCap(int32 InKbps);` — Sets the bandwidth Cap for the Manager to distribute across all services
- L172 _public function_ `void SetGameplayBandwidthCap(int32 InKbps)` — Sets the Gameplay bandwidth for the Manager to reserve during the gameplay state
- L175 _public prototype_ `int32 GetNumRegisteredServices() const;` — Returns the number of registered services (for telemetry A/B population flags)
- L178 _public prototype_ `FBandwidthAllocatorTelemetry GetTelemetrySnapshot() const;` — Returns a snapshot of telemetry state for analytics reporting
- L181 _public prototype_ `void ResetTelemetryCounters();` — Resets accumulated telemetry counters (called after analytics flush)
- L184 _public prototype_ `void Log(bool bPrint);` — Allows for logging output of FDownlinkBandwidthManager, enabled via CVarDLBWEnableBandwidthLogging
- L187 _public prototype_ `FDelegateHandle BindToCVarSubscription(TFunction<void()> CallBack);` — Binds for Subscription when CVar values get set/changed
- L190 _public prototype_ `void UnbindToCVarSubscription(FDelegateHandle& Handle);` — Removes Delegate Callback for CVarSubscriptionDelegate
- L193 _private prototype_ `void Tick();` — Called once per frame/tick to apply an updated allotment based on active services
- L197 _private prototype_ `void UpdateCsvStats();` — Emits allocator state, per-tick deltas, and measurement data to the CSV profiler
- L201 _private prototype_ `void DistributeBandwidth();` — Source of Bandwidth Assignment
- L204 _private prototype_ `void GeneratePriorityBucketMap();` — Called when services are altered to maintain PriorityBucketMapping
- L207 _private prototype_ `UE::BandwidthManager::EBandwidthPriority GetPriorityValueForService(const FManagedService& MonitoredService) const;` — Helper function to get priority based on CurrentGameplayPriority
- L210 _private prototype_ `int32 GetCurrentMaxAvailableBandwidthInBytes();` — Helper function to get the current available bandwidth to distribute based on gameplay state
- L216 _private member_ `static TUniquePtr<FDownlinkBandwidthManager> Instance;` — Singleton instance pointer
- L218 _private member_ `mutable FTransactionallySafeCriticalSection Mutex;`
- L221 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — Handle for the polling tick
- L224 _private member_ `int32 CapKbps = 0;` — The hard cap used for determining bandwidth distribution
- L227 _private member_ `int32 ReservedGameplayBandwidthKbps = 10000;` — The amount of bandwidth to reserve during gameplay
- L230 _private member_ `int32 NextServiceId = UE_INVALID_BANDWIDTH_SERVICE_HANDLE;` — Incrementing Handle value for external services to track their FManagedService data within the manager
- L233 _private member_ `TMap<UE::BandwidthManager::FServiceHandleID, FManagedService> TrackedServices;` — Service Data Mapping
- L236 _private member_ `TMap<UE::BandwidthManager::EBandwidthPriority, UE::BandwidthManager::FPriorityBucket> PriorityBucketMapping;` — Mapping of expected priorities to their calculated allotment of bandwidth
- L239 _private member_ `UE::BandwidthManager::EBandwidthDistributionPriorityState CurrentGameplayPriorityState = UE::BandwidthManager::EBandwidthDistributionPriorityState::IdleGameplay;` — The Managers perceived state of gameplay to consider for distribution
- L242 _private member_ `float RolloutPercentage = 0.0f;` — Randomized chance roll at initialization to determine if the manager should rollout for this client's launch
- L245 _private member_ `int32 TelemetryDecisionCount = 0;` — Telemetry counters (accumulated between analytics flushes)
- L246 _private member_ `int32 TelemetryReallocationCount = 0;`
- L247 _private member_ `int32 TelemetryAllocatorErrors = 0;`
- L248 _private member_ `bool bTelemetryMeasurementCompleted = false;`
- L249 _private member_ `bool bTelemetryMeasurementSuccess = false;`
- L252 _private member_ `TMap<UE::BandwidthManager::FServiceHandleID, int32> PreviousAllocations;` — Previous per-service bandwidth allocations (in Kbps), used to detect reallocations between ticks for telemetry
- L255 _private member_ `int32 CsvPreviousDecisionCount = 0;`
- L256 _private member_ `int32 CsvPreviousReallocationCount = 0;`
- L257 _private member_ `int32 CsvPreviousAllocatorErrors = 0;`
- L261 _private member_ `UE::BandwidthManager::FOnCVarSetSubscription CVarSubscriptionDelegate;` — Delegate to be triggered when rollout CVars are set

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API DOWNLINKBANDWIDTHMANAGER_API`
- L7 _macro_ `#define UE_INVALID_BANDWIDTH_SERVICE_HANDLE -1`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDownlinkBandwidthManager, Log, All);`
- L19 _typedef_ `using FOnBandwidthUpdate = TUniqueFunction<void(int32&&)>;` — Usage for this callback will receive a parameter in Kbps
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace BandwidthManager` (scope `UE`)
- L37 _typedef_ `typedef int32 FServiceHandleID;` (scope `UE::BandwidthManager`)
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCVarSetSubscription);`
- L39 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCVarSetSubscription);` (scope `UE::BandwidthManager`)
- L72 _variable_ `constexpr int32 KilobitsToBytesConversionValue = 1000 / 8;` (scope `UE::BandwidthManager`) — Conversion value for Kb to bytes

### `Source/Runtime/Online/Experimental/DownlinkBandwidthManager/Public/DownlinkBandwidthManagerConfig.h` (Public)


#### class `UDownlinkBandwidthManagerConfig`  
`class UDownlinkBandwidthManagerConfig : public UObject`  
_L11-28_
- reflection: `UCLASS(config = Engine, MinimalAPI)`
- inherits: `UObject`
- L15 _public function_ `UDownlinkBandwidthManagerConfig()`
- L17 _public prototype_ `virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;`
- L19 _public prototype_ `void SetConsoleVariablesFromConfigurables();`
- L23 _public member_ `int32 RolloutPercentage = 0;` — `UPROPERTY(Config)` — The pass percentage for the user to run the Distribution Manager.
- L27 _public member_ `bool EnforceDistributionAllocation = false;` — `UPROPERTY(Config)` — Enables the application of the distributor's calculated allocations to subscribed systems if percentage check has passed

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DOWNLINKBANDWIDTHMANAGER_API`
