# Plugins / DisplayClusterStageMonitoring

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterStageMonitoring`
- headers: 3; symbols: 48
- symbol kinds: class=3, function=2, member=21, prototype=19, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, DisplayCluster, DisplayClusterConfiguration, Engine, RHI, RenderCore, StageDataCore

### `Plugins/Runtime/nDisplay/Source/DisplayClusterStageMonitoring/Private/DWMSyncWatchdog.h` (Private)


#### struct `FDWMSyncEvent`  
`struct FDWMSyncEvent : public FStageProviderEventMessage`  
_L12-43_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- L17 _public prototype_ `FDWMSyncEvent() = default;`
- L19 _public function_ `FDWMSyncEvent(uint32 InMissedFrames, uint32 InPresentCount, uint32 InLastPresentCount, uint32 InPresentRefreshCount) : MissedFrames(InMissedFrames) , PresentCount(InPresentCount) , LastPresentCount(InLastPresentCount) , PresentRefreshCount(InPresentRefreshCount)`
- L27 _public prototype_ `virtual FString ToString() const override;`
- L33 _public member_ `uint32 MissedFrames = 0;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync")` — Number of sync counts that were missed between presents
- L36 _public member_ `uint32 PresentCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync")`
- L39 _public member_ `uint32 LastPresentCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync")`
- L42 _public member_ `uint32 PresentRefreshCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync")`

#### class `FDWMSyncWatchdog`  
`class FDWMSyncWatchdog`  
_L49-74_
- desc: Verifies the frame counter using DWM stats
- L52 _public prototype_ `FDWMSyncWatchdog();`
- L53 _public prototype_ `~FDWMSyncWatchdog();`
- L57 _private prototype_ `void OnCustomPresentCreated();`
- L58 _private prototype_ `void OnPresentationPreSynchronization_RHIThread(FRHIViewport* Viewport);`
- L59 _private prototype_ `void OnPresentationPostSynchronization_RHIThread(FRHIViewport* Viewport);`
- L67 _private member_ `TOptional<uint32> PreviousFrameCount;` — Previous vblank counter queried from frame stats We expect this to increment by 1 every frame or else a hitch happened
- L70 _private member_ `uint64 LastPreSyncCycles = 0;` — Cycle count when last pre synchronization happened
- L73 _private member_ `uint64 LastPreSyncDeltaCycles = 0;` — Cycles it took between two pre synchronization i.e. time it took to render and present the frame

### `Plugins/Runtime/nDisplay/Source/DisplayClusterStageMonitoring/Private/DisplayClusterStageMonitoringSettings.h` (Private)


#### class `UDisplayClusterStageMonitoringSettings`  
`class UDisplayClusterStageMonitoringSettings : public UDeveloperSettings`  
_L14-62_
- reflection: `UCLASS(config=Game)`
- inherits: `UDeveloperSettings`
- desc: Settings for the DisplayCluster StageMonitor hooks plugin modules.
- L19 _public prototype_ `UDisplayClusterStageMonitoringSettings();`
- L22 _public prototype_ `virtual FName GetCategoryName() const;`
- L24 _public prototype_ `virtual FText GetSectionText() const override;`
- L31 _public prototype_ `bool ShouldEnableNvidiaWatchdog() const;` — Whether nvidia hitch detection should be enabled or not
- L35 _public prototype_ `bool ShouldEnableDWMWatchdog() const;` — Whether DWM hitch detection should be enabled or not
- L45 _protected member_ `bool bEnableDWMHitchDetection = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — Whether DWM hitch detection is enabled by default @note It may be overriden via the command line, "-EnableDisplayClusterDWMHitchDetect=1" @note Only works with sync policy 1
- L53 _protected member_ `bool bEnableNvidiaHitchDetection = true;` — `UPROPERTY(config, EditAnywhere, Category = "Settings")` — Whether Nvidia hitch detection is enabled by default @note It may be overriden via the command line, "-EnableDisplayClusterNvidiaHitchDetect=1" @note Only works with sync policy 2
- L58 _public member_ `TOptional<bool> CommandLineEnableNvidiaHitch;` — Command line value to override enable settings
- L61 _public member_ `TOptional<bool> CommandLineEnableDWMHitch;` — Command line value to override enable settings

### `Plugins/Runtime/nDisplay/Source/DisplayClusterStageMonitoring/Private/NvidiaSyncWatchdog.h` (Private)


#### struct `FNvidiaSyncEvent`  
`struct FNvidiaSyncEvent : public FStageProviderEventMessage`  
_L16-43_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- L21 _public prototype_ `FNvidiaSyncEvent() = default;`
- L23 _public function_ `FNvidiaSyncEvent(int32 InMissedFrames, float InFrameDuration, float InSynchronizationDuration) : MissedFrames(InMissedFrames) , LastFrameDuration(InFrameDuration) , SynchronizationDuration(InSynchronizationDuration)`
- L30 _public prototype_ `virtual FString ToString() const override;`
- L36 _public member_ `int32 MissedFrames = 0;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync")` — Number of sync counts that were missed between presents
- L39 _public member_ `float LastFrameDuration = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync", meta = (Unit = "ms"))`
- L42 _public member_ `float SynchronizationDuration = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = "NvidiaSync", meta = (Unit = "ms"))`

#### class `FNvidiaSyncWatchdog`  
`class FNvidiaSyncWatchdog`  
_L49-85_
- desc: Verifies the frame counter using NvAPI
- L52 _public prototype_ `FNvidiaSyncWatchdog();`
- L53 _public prototype_ `~FNvidiaSyncWatchdog();`
- L57 _private prototype_ `void OnCustomPresentCreated();`
- L58 _private prototype_ `void OnPresentationPreSynchronization_RHIThread(FRHIViewport* Viewport);`
- L59 _private prototype_ `void OnPresentationPostSynchronization_RHIThread(FRHIViewport* Viewport);`
- L67 _private member_ `TOptional<uint32> PreviousFrameCount;` — Previous frame counter queried from nvapi quadro card We expect this to increment by 1 every frame or else a hitch happened
- L70 _private member_ `IUnknown* D3DDevice = nullptr;` — Current DynamicRHI as D3DDevice
- L73 _private member_ `uint64 LastPreSyncCycles = 0;` — Cycle count when last pre synchronization happened
- L76 _private member_ `uint64 LastPreSyncDeltaCycles = 0;` — Cycles it took between two pre synchronization i.e. time it took to render and present the frame
- L84 _private member_ `TFuture<FQueryFrameCounterResult> AsyncFrameCountFuture;`

#### struct `FNvidiaSyncWatchdog::FQueryFrameCounterResult`  
`struct FQueryFrameCounterResult`  
_L78-82_
- L80 _public member_ `uint32 FrameCount = 0;`
- L81 _public member_ `int32 QueryResult = 0;`
