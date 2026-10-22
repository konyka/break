# Plugins / StageDataProvider

- module root: `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider`
- headers: 7; symbols: 111
- symbol kinds: class=7, delegate=1, externvar=1, function=6, member=43, prototype=48, struct=5
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, GameplayTags, LevelSequence, RHI, RenderCore, StageDataCore, StageMonitorCommon, TakeRecorder, TimeManagement, VPRoles, VPUtilities
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/FramePerformanceProvider.h` (Private)


#### struct `FHitchDetectionMessage`  
`struct FHitchDetectionMessage : public FStageProviderEventMessage`  
_L18-69_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- desc: Message sent when a hitch was detected on a provider machine.
- L23 _public prototype_ `FHitchDetectionMessage() = default;`
- L25 _public function_ `FHitchDetectionMessage(float InGameThreadTimeWithWaits, float InRenderThreadTimeWithWaits, float InGameThreadTime, float InRenderThreadTime, float InGPUTime, float InTimingThreshold, float InHitchedFPS) : GameThreadWithWaitsMS(InGameThreadTimeWithWaits) , RenderThreadWithWaitsMS(InRenderThreadTimeWithWaits) , GameThreadMS(InGameThreadTime) , RenderThreadMS(InRenderThreadTime) , GPU_MS(InGPUTime) , TimingThreshold(InTimingThreshold) , HitchedTimeFPS(InHitchedFPS)`
- L40 _public member_ `float GameThreadWithWaitsMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Current GameThread time including any waits read from StatsThread in milliseconds
- L44 _public member_ `float RenderThreadWithWaitsMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Current RenderThread time including any waits read from StatsThread in milliseconds
- L48 _public member_ `float GameThreadMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Current GameThread time read from GGameThreadTime in milliseconds
- L52 _public member_ `float RenderThreadMS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Current RenderThread time read from GRenderThreadTime in milliseconds
- L56 _public member_ `float GPU_MS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Current GPU time read from RHIGetGPUFrameCycles() in milliseconds
- L60 _public member_ `float TimingThreshold = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch", meta = (Unit = "ms"))` — Timing threshold that was crossed in milliseconds
- L64 _public member_ `float HitchedTimeFPS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch")` — FPS correspondent to the timing that triggered the hitch (game or render thread)
- L68 _public member_ `float AverageFPS = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = "Hitch")` — Average FPS when hitch occured

#### class `FFramePerformanceProvider`  
`class FFramePerformanceProvider`  
_L75-111_
- desc: Handles sending frame performance messages periodically and hitch messages if detected Either one can be enabled / disabled using project settings
- L78 _public prototype_ `FFramePerformanceProvider();`
- L79 _public prototype_ `~FFramePerformanceProvider();`
- L84 _private prototype_ `void CheckHitches(int64 Frame);` — Callback by the stat module to detect if a hitch happened
- L88 _private prototype_ `void OnStageSettingsChanged(UObject* Object, struct FPropertyChangedEvent& PropertyChangedEvent);`
- L92 _private prototype_ `void EnableHitchDetection(bool bShouldEnable);` — Enables/disables hitch detection
- L97 _private prototype_ `void HandleAssetReload(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Delegate for when package reload occurs.
- L100 _private prototype_ `void HandlePreLoadMap(const FString& MapName);` — Delegate for pre-load map
- L103 _private prototype_ `void HandlePostLoadMap(UWorld* );` — Delegate for post load of map.
- L106 _private member_ `FStageHitchDetectionSettings CachedHitchSettings;` — Cached settings for hitch detection since it's called on another thread, we can't access UObject
- L108 _private member_ `bool bIsHitchDetectionEnabled = false;`
- L110 _private member_ `TUniquePtr<FFrameProviderRunner> ProviderThread;`

#### Free symbols / members of external scopes

- L34 _externvar_ `extern float GAverageFPS;` (scope `FHitchDetectionMessage::FHitchDetectionMessage`)

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/GenlockWatchdog.h` (Private)


#### struct `FGenlockHitchEvent`  
`struct FGenlockHitchEvent : public FStageProviderEventMessage`  
_L18-33_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- desc: Stage event to notify of missed sync (genlock) signals When sync signal are lost, it means the engine is not running fast enough to keep track of the genlock source.
- L23 _public prototype_ `FGenlockHitchEvent() = default;`
- L24 _public function_ `FGenlockHitchEvent(int32 InMissedSyncs) : MissedSyncSignals(InMissedSyncs)`
- L28 _public prototype_ `virtual FString ToString() const override;`
- L32 _public member_ `int32 MissedSyncSignals = 0;` — `UPROPERTY(VisibleAnywhere, Category="GenlockState")` — Number of sync counts that were missed between tick

#### struct `FGenlockStateEvent`  
`struct FGenlockStateEvent : public FStageProviderEventMessage`  
_L39-54_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- desc: Stage event to notify of genlock custom timestep state change
- L44 _public prototype_ `FGenlockStateEvent() = default;`
- L45 _public function_ `FGenlockStateEvent(ECustomTimeStepSynchronizationState InState) : NewState(InState)`
- L49 _public prototype_ `virtual FString ToString() const override;`
- L53 _public member_ `ECustomTimeStepSynchronizationState NewState = ECustomTimeStepSynchronizationState::Closed;` — `UPROPERTY(VisibleAnywhere, Category = "GenlockState")` — New state of genlock custom timestep (i.e. Synchronized, Error, etc...)

#### class `FGenlockWatchdog`  
`class FGenlockWatchdog`  
_L59-74_
- desc: Verifies the state of the genlock and missed sync events if any and send stage event if required
- L62 _public prototype_ `FGenlockWatchdog();`
- L63 _public prototype_ `~FGenlockWatchdog();`
- L68 _private prototype_ `void OnEndFrame();` — At end of frame, verify genlock signal / state and notify state monitor if something changed
- L73 _private member_ `ECustomTimeStepSynchronizationState LastState = ECustomTimeStepSynchronizationState::Closed;` — Previous value of the genlock state.

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/StageDataProvider.h` (Private)


#### class `FStageDataProvider`  
`class FStageDataProvider : public IStageDataProvider`  
_L17-77_
- inherits: `IStageDataProvider`
- desc: Implementation of the stage data provider. Uses message bus to send messages to monitors
- L20 _public prototype_ `FStageDataProvider();`
- L21 _public prototype_ `virtual ~FStageDataProvider();`
- L24 _public prototype_ `void Start();` — Setup everything required to be able to listen for monitors and send data
- L27 _public prototype_ `void Stop();` — Let monitors know we're closing and cleanup endpoint
- L32 _protected prototype_ `virtual bool SendMessageInternal(FStageDataBaseMessage* Payload, UScriptStruct* Type, EStageMessageFlags InFlags) override;`
- L38 _private prototype_ `void HandleDiscoveryMessage(const FStageProviderDiscoveryMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles reception of a discovery message sent by monitors. Will send descriptor back if its coming from a new monitor
- L41 _private prototype_ `void HandleMonitorCloseMessage(const FStageMonitorCloseMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);` — Handles reception of a monitor closing message. Removes it from the linked monitor list
- L44 _private prototype_ `bool Tick(float DeltaTime);` — Used to verify if monitors have timedout
- L47 _private prototype_ `void RemoveTimeoutedMonitors();` — Remove monitors for which we haven't received any message for a while
- L50 _private prototype_ `bool IsMessageTypeExcluded(UScriptStruct* MessageType) const;` — Verify if this message type is excluded using project settings
- L64 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ProviderEndpoint;`
- L65 _private member_ `TArray<FMonitorEndpoints> Monitors;`
- L68 _private member_ `TArray<FMessageAddress> CachedMonitorAddresses;` — Used to easily convert to an array when sending to the attached monitors
- L69 _private member_ `bool bIsActive = false;`
- L70 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L73 _private member_ `TArray<FGuid> InvalidMonitors;` — Used to keep track of monitors that were not compatible with us to avoid log spamming
- L76 _private member_ `FGuid Identifier;` — Identifier of this provider

#### struct `FStageDataProvider::FMonitorEndpoints`  
`struct FMonitorEndpoints`  
_L56-62_
- desc: Holds information about monitors that discovered us
- L58 _public member_ `FGuid Identifier;`
- L59 _public member_ `FStageInstanceDescriptor Descriptor;`
- L60 _public member_ `FMessageAddress Address;`
- L61 _public member_ `double LastReceivedMessageTime = 0.0;`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/StageDataProviderModule.h` (Private)


#### class `FStageDataProviderModule`  
`class FStageDataProviderModule : public IStageDataProviderModule`  
_L20-67_
- inherits: `IStageDataProviderModule`
- desc: Interface for the stage data provider module.
- L23 _public prototype_ `FStageDataProviderModule();`
- L26 _public prototype_ `virtual void StartupModule() override;`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _private prototype_ `void OnPostEngineInit();` — We rely on VPUtilities module, make sure everything is loaded before we use it
- L36 _private prototype_ `void OnPreExit();` — WHen exiting the app, stop data providers so data providers can be closed
- L39 _private prototype_ `void StartDataProvider();` — Starts data provider
- L42 _private prototype_ `void StopDataProvider();` — Stops data provider
- L47 _private member_ `TUniquePtr<FStageDataProvider> DataProvider;` — Instance of the data provider
- L50 _private member_ `TUniquePtr<FFramePerformanceProvider> FramePerformanceProvider;` — Frame performance provider instance sending information about hitch and performance
- L53 _private member_ `TUniquePtr<FGenlockWatchdog> GenlockWatchdog;` — Monitors the genlock custom timestep, if available, to notify of hitches
- L56 _private member_ `TUniquePtr<FTimecodeProviderWatchdog> TimecodeWatchdog;` — Monitors the TimecodeProvider, if available, to notify of state change or missed frames
- L60 _private member_ `TUniquePtr<FTakeRecorderStateProvider> TakeRecorderStateProvider;` — TakeRecorder provider instance sends information about stage critical state
- L64 _private member_ `TUniquePtr<FAutoConsoleCommand> CommandStart;`
- L65 _private member_ `TUniquePtr<FAutoConsoleCommand> CommandStop;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageDataProvider, Log, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStageDataProvider, Log, All);`

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/TakeRecorderStateProvider.h` (Private)


#### class `FTakeRecorderStateProvider`  
`class FTakeRecorderStateProvider`  
_L15-37_
- L18 _public prototype_ `FTakeRecorderStateProvider();`
- L22 _private prototype_ `void OnTakeRecorderInitializer(UTakeRecorder* InRecorder);` — When a take recorder is initialized, hooks us to different delegates to know its state
- L25 _private prototype_ `void OnTakeRecorderStarted(UTakeRecorder* InRecorder);` — Sends out active state based on take recorder
- L28 _private prototype_ `void OnTakeRecorderStopped(UTakeRecorder* InRecorder);` — Sends out inactive state based on take recorder
- L33 _private member_ `FName TakeName;` — Name of the take being done
- L36 _private member_ `EStageCriticalStateEvent CurrentState = EStageCriticalStateEvent::Exit;` — Current state of this stage critical status

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Private/TimecodeProviderWatchdog.h` (Private)


#### struct `FTimecodeProviderStateEvent`  
`struct FTimecodeProviderStateEvent : public FStageProviderEventMessage`  
_L16-46_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- desc: Stage event to notify of TimecodeProvider state change
- L21 _public prototype_ `FTimecodeProviderStateEvent() = default;`
- L22 _public function_ `FTimecodeProviderStateEvent(FString InProviderName, FString InProviderType, FFrameRate InFrameRate, ETimecodeProviderSynchronizationState InState) : ProviderName(MoveTemp(InProviderName)) , ProviderType(MoveTemp(InProviderType)) , FrameRate(MoveTemp(InFrameRate)) , NewState(InState)`
- L29 _public prototype_ `virtual FString ToString() const override;`
- L33 _public member_ `FString ProviderName;` — `UPROPERTY(VisibleAnywhere, Category = "Timecode")` — Name of the TimeodeProvider for this event
- L37 _public member_ `FString ProviderType;` — `UPROPERTY(VisibleAnywhere, Category = "Timecode")` — Type of the TimecodeProvider for this event
- L41 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(VisibleAnywhere, Category = "Timecode")` — FrameRate of the provider
- L45 _public member_ `ETimecodeProviderSynchronizationState NewState = ETimecodeProviderSynchronizationState::Closed;` — `UPROPERTY(VisibleAnywhere, Category = "Timecode")` — New state of TimecodeProvider (i.e. Synchronized, Error, etc...)

#### class `FTimecodeProviderWatchdog`  
`class FTimecodeProviderWatchdog`  
_L52-88_
- desc: Simple TimecodeProvider watcher notifying stage mon if state changes Timecode validation could also be added in the future
- L55 _public prototype_ `FTimecodeProviderWatchdog();`
- L56 _public prototype_ `~FTimecodeProviderWatchdog();`
- L61 _private prototype_ `void OnEndFrame();` — At end of frame, verify timecode state and notify stage monitor if something changed
- L64 _private prototype_ `void OnPostEngineInit();` — Delegate post engine to have access to GEngine and get current TimecodeProvider
- L67 _private prototype_ `void OnTimecodeProviderChanged();` — Detect when a provider has changed to send a closed notification for the previous one
- L70 _private prototype_ `void CacheProviderInfo();` — Cache info about the current provider if there is one
- L73 _private prototype_ `void UpdateProviderState();` — Update internal TimecodeProvider state and trigger event if it has changed or first time checked
- L78 _private member_ `TOptional<ETimecodeProviderSynchronizationState> LastState;` — Previous value of the timecode provider state.
- L81 _private member_ `FString ProviderName;` — Cached provider name
- L84 _private member_ `FString ProviderType;` — Cached provider class type
- L87 _private member_ `FFrameRate FrameRate;` — Last FrameRate provider had

### `Plugins/VirtualProduction/StageMonitoring/Source/StageDataProvider/Public/IStageDataProviderModule.h` (Public)


#### class `IStageDataProviderModule`  
`class IStageDataProviderModule : public IModuleInterface`  
_L15-44_
- inherits: `IModuleInterface`
- desc: Interface for the stage data provider module.
- L19 _public prototype_ `virtual ~IStageDataProviderModule() = default;`
- L27 _public function_ `static inline IStageDataProviderModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L37 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L43 _private member_ `static const FName ModuleName;`
