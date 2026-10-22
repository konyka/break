# Plugins / TimecodeSynchronizer

- module root: `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer`
- headers: 3; symbols: 159
- symbol kinds: class=4, delegate=2, enum=6, enumerator=20, function=26, macro=1, member=53, prototype=43, struct=4
- PrivateDependencyModuleNames: MediaPlayerEditor, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MediaAssets, MediaUtils, TimeManagement

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer/Public/TimecodeSynchronizer.h` (Public)


#### enum `ETimecodeSynchronizationSyncMode`  
`enum class UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.") ETimecodeSynchronizationSyncMode`  
_L25-50_
- reflection: `UENUM()`
- desc: Defines the various modes that the synchronizer can use to try and achieve synchronization.
- L35 _public enumerator_ `UserDefinedOffset` — User will specify an offset (number of frames) from the Timecode Source (see ETimecodeSycnrhonizationTimecodeType). This offset may be positive or negative depending on the latency of the source. Synchronization will be achieved once the synchronizer detects all input sources have frames that correspond with the offset timecode. This is suitable for applications trying to keep multiple Unreal Engine instances in sync while using nDisplay / genlock.
- L43 _public enumerator_ `Auto` — Engine will try and automatically determine an appropriate offset based on what frames are available on the given sources. This is suitable for running a single Unreal Engine instance that just wants to synchronize its inputs.
- L49 _public enumerator_ `AutoOldest` — The same as Auto except that instead of trying to find a suitable timecode nearest to the newest common frame, we try to find a suitable timecode nearest to the oldest common frame.

#### enum `ETimecodeSynchronizationTimecodeType`  
`enum class UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.") ETimecodeSynchronizationTimecodeType`  
_L56-66_
- reflection: `UENUM()`
- desc: Enumerates Timecode source type.
- L59 _public enumerator_ `DefaultProvider` — Use the configured Engine Default Timecode provider.
- L62 _public enumerator_ `TimecodeProvider` — Use an external Timecode Provider to provide the timecode to follow.
- L65 _public enumerator_ `InputSource` — Use one of the InputSource as the Timecode Provider.

#### enum `ETimecodeSynchronizationFrameRateSources`  
`enum class UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.") ETimecodeSynchronizationFrameRateSources: uint8`  
_L72-76_
- reflection: `UENUM()`
- desc: Enumerates possible framerate source
- L74 _public enumerator_ `EngineCustomTimeStepFrameRate UMETA(ToolTip="Frame Rate of engine custom time step if it is of type UFixedFrameRateCustomTimeStep.")`
- L75 _public enumerator_ `CustomFrameRate UMETA(ToolTip = "Custom Frame Rate selected by the user.")`

#### enum `ETimecodeSynchronizationEvent`  
`enum class UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.") ETimecodeSynchronizationEvent`  
_L82-95_
- desc: Enumerates Synchronization related events.
- L85 _public enumerator_ `SynchronizationStarted` — The synchronization procedure has started.
- L88 _public enumerator_ `SynchronizationFailed` — The synchronization procedure failed.
- L91 _public enumerator_ `SynchronizationSucceeded` — The synchronization procedure succeeded.
- L94 _public enumerator_ `SynchronizationStopped` — Synchronization was stopped. Note, this won't be called if Synchronization failed.

#### struct `FTimecodeSynchronizerCachedSyncState`  
`struct FTimecodeSynchronizerCachedSyncState`  
_L99-112_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- desc: Cached values to use during synchronization / while synchronized
- L102 _public member_ `TOptional<FFrameTime> RolloverFrame;` — If we're using rollover, the frame time that represents the rollover point (e.g., the modulus).
- L105 _public member_ `FFrameRate FrameRate;` — The FrameRate of the synchronizer.
- L108 _public member_ `ETimecodeSynchronizationSyncMode SyncMode;` — Synchronization mode that's being used.
- L111 _public member_ `int32 FrameOffset;` — Frame offset that will be used if SyncMode != Auto;

#### struct `FTimecodeSourceState`  
`struct FTimecodeSourceState`  
_L116-123_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- desc: Cached frame values for a given source.
- L119 _public member_ `FFrameTime NewestAvailableSample;` — Frame time of the newest available sample.
- L122 _public member_ `FFrameTime OldestAvailableSample;` — Frame time of the oldest available sample.

#### struct `FTimecodeSynchronizerActiveTimecodedInputSource`  
`struct FTimecodeSynchronizerActiveTimecodedInputSource`  
_L133-231_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- reflection: `USTRUCT()`
- desc: Provides a wrapper around a UTimeSynchronizerSource, and caches data necessary to provide synchronization. The values are typically updated once per frame.
- L139 _public function_ `FTimecodeSynchronizerActiveTimecodedInputSource() : bIsReady(false) , bCanBeSynchronized(false) , TotalNumberOfSamples(0) , FrameRate(60, 1) , InputSource(nullptr)`
- L148 _public function_ `FTimecodeSynchronizerActiveTimecodedInputSource(UTimeSynchronizationSource* Source) : bIsReady(false) , bCanBeSynchronized(Source->bUseForSynchronization) , TotalNumberOfSamples(0) , FrameRate(60, 1) , InputSource(Source)`
- L158 _public prototype_ `const bool UpdateSourceState(const FFrameRate& SynchronizerFrameRate);` — Updates the internal state of this source, returning whether or not the source is ready (e.g. IsReady() == true).
- L160 _public function_ `inline const UTimeSynchronizationSource* GetInputSource() const`
- L165 _public function_ `inline bool IsInputSourceValid() const`
- L170 _public function_ `inline FString GetDisplayName() const`
- L176 _public function_ `inline bool IsReady() const` — Whether or not this source is ready.
- L182 _public function_ `inline bool CanBeSynchronized() const` — Whether or not this source can be synchronized.
- L188 _public function_ `inline const FFrameRate& GetFrameRate() const` — Gets the FrameRate of the source.
- L194 _public function_ `inline const FTimecodeSourceState& GetInputSourceState() const` — Gets the state of the Source relative to its own frame rate.
- L200 _public function_ `inline const FTimecodeSourceState& GetSynchronizerRelativeState() const` — Gets the state of the Source relative to the Synchronizer's frame rate.
- L209 _private member_ `bool bIsReady;` — `UPROPERTY(VisibleAnywhere, Transient, Category=Debug, Meta=(DisplayName = "Is Ready"))` — Flag stating if the source is ready
- L213 _private member_ `bool bCanBeSynchronized;` — `UPROPERTY(VisibleAnywhere, Transient, Category=Debug, Meta=(DisplayName = "Can Be Synchronized"))` — Flag stating if this source can be synchronized
- L216 _private member_ `int32 TotalNumberOfSamples;` — `UPROPERTY(VisibleAnywhere, Transient, Category=Debug)`
- L218 _private member_ `FFrameRate FrameRate;`
- L220 _private member_ `FTimecodeSourceState InputSourceState;`
- L221 _private member_ `FTimecodeSourceState SynchronizerRelativeState;`
- L225 _private member_ `TObjectPtr<UTimeSynchronizationSource> InputSource;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Debug, Meta=(DisplayName="Input Source"))` — Associated source pointers
- L227 _private prototype_ `FTimecodeSynchronizerActiveTimecodedInputSource(const FTimecodeSynchronizerActiveTimecodedInputSource&) = delete;`
- L228 _private prototype_ `FTimecodeSynchronizerActiveTimecodedInputSource& operator=(const FTimecodeSynchronizerActiveTimecodedInputSource&) = delete;`
- L229 _private prototype_ `FTimecodeSynchronizerActiveTimecodedInputSource(FTimecodeSynchronizerActiveTimecodedInputSource&&) = delete;`
- L230 _private prototype_ `FTimecodeSynchronizerActiveTimecodedInputSource& operator=(FTimecodeSynchronizerActiveTimecodedInputSource&&) = delete;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTimecodeSynchronizerActiveTimecodedInputSource> : public TStructOpsTypeTraitsBase2<FTimecodeSynchronizerActiveTimecodedInputSource>`  
_L236-242_
- inherits: `TStructOpsTypeTraitsBase2<FTimecodeSynchronizerActiveTimecodedInputSource>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L239-241_

#### class `UTimecodeSynchronizer`  
`class UTimecodeSynchronizer : public UTimecodeProvider, public FTickableGameObject`  
_L259-588_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- reflection: `UCLASS()`
- inherits: `UTimecodeProvider,FTickableGameObject`
- desc: Timecode Synchronizer is intended to correlate multiple timecode sources to help ensure that all sources can produce data that is frame aligned. This typically works by having sources buffer data until we have enough frames that such that we can find an overlap. Once that process is finished, the Synchronizer will provide the appropriate timecode to the engine (which can be retrieved via FApp::GetTimecode and FApp::GetTimecodeFrameRate). Note, the Synchronizer doesn't perform any buffering of data itself (that is left up to TimeSynchronizationSources). Instead, the synchronizer simply acts as a coordinator making sure all sources are ready, determining if sync is possible, etc.
- L265 _public prototype_ `UTimecodeSynchronizer();`
- L268 _public prototype_ `virtual void BeginDestroy() override;`
- L270 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L271 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L276 _public prototype_ `FQualifiedFrameTime GetQualifiedFrameTime() const override;`
- L277 _public prototype_ `virtual ETimecodeProviderSynchronizationState GetSynchronizationState() const override;`
- L278 _public prototype_ `virtual bool Initialize(class UEngine* InEngine) override;`
- L279 _public prototype_ `virtual void Shutdown(class UEngine* InEngine) override;`
- L283 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L284 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L285 _public function_ `virtual bool IsTickableInEditor() const override`
- L286 _public prototype_ `virtual bool IsTickable() const override;`
- L287 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L288 _public function_ `virtual TStatId GetStatId() const override`
- L298 _public prototype_ `bool StartSynchronization();` — Starts the synchronization process. Does nothing if we're already synchronized, or attempting to synchronize. @return True if the synchronization process was successfully started (or was previously started).
- L301 _public prototype_ `void StopSynchronization();` — Stops the synchronization process. Does nothing if we're not synchronized, or attempting to synchronize.
- L304 _public function_ `const TArray<FTimecodeSynchronizerActiveTimecodedInputSource>& GetTimecodedSources() const` — `UE_DEPRECATED(4.21, "Please use GetSynchronizedSources.")`
- L307 _public function_ `const TArray<FTimecodeSynchronizerActiveTimecodedInputSource>& GetSynchronizationSources() const` — `UE_DEPRECATED(4.21, "Please use GetNonSynchronizedSources.")`
- L310 _public function_ `const TArray<FTimecodeSynchronizerActiveTimecodedInputSource>& GetSynchronizedSources() const` — Returns the list of sources that are used to perform synchronization.
- L313 _public function_ `const TArray<FTimecodeSynchronizerActiveTimecodedInputSource>& GetNonSynchronizedSources() const` — Returns the list of sources that are not actively being used in synchronization.
- L316 _public function_ `int32 GetActiveMainSynchronizationTimecodedSourceIndex() const` — Returns the index of the Main Synchronization Source in the Synchronized Sources list.
- L323 _public function_ `DECLARE_EVENT_OneParam(UTimecodeSynchronizer, FOnTimecodeSynchronizationEvent, ETimecodeSynchronizationEvent ) FOnTimecodeSynchronizationEvent& OnSynchronizationEvent()` — Get an event delegate that is invoked when a Asset synchronization event occurred. @return The delegate.
- L339 _public prototype_ `void AddRuntimeTimeSynchronizationSource(UTimeSynchronizationSource* Source);` — Adds a "runtime" source to the synchronizer. These sources can only be added from StartSynchronization callback, and will automatically be removed once synchronization has stopped (or failed). While the synchronization process is active, it's guaranteed that the TimecodeSynchronizer will keep a hard reference to the source. Sources added this way should be added every time the StartSynchronization event is fired.
- L346 _public function_ `FFrameTime GetCurrentSystemFrameTime() const` — Get Current System Frame Time which is synchronized @return FrameTime
- L373 _private function_ `inline static FString SynchronizationStateToString(ESynchronizationState InState)`
- L404 _private prototype_ `void OnTimecodeProviderChanged();` — Callback when the engine's TimecodeProvider changed.
- L407 _private prototype_ `void SetTickEnabled(bool bEnabled);` — Registers asset to MediaModule tick
- L410 _private prototype_ `void Tick_Switch();` — Switches on current state and ticks it
- L412 _private prototype_ `bool ShouldTick();`
- L415 _private prototype_ `bool Tick_TestGenlock();` — Test if the genlock & timecode provider are properly setup
- L416 _private prototype_ `bool Tick_TestTimecode();`
- L419 _private prototype_ `void TickPreRolling_WaitGenlockTimecodeProvider();` — Process PreRolling_WaitGenlockTimecodeProvider state.
- L422 _private prototype_ `void TickPreRolling_WaitReadiness();` — Process PreRolling_WaitReadiness state.
- L425 _private prototype_ `void TickPreRolling_Synchronizing();` — Process PreRolling_Synchronizing state.
- L428 _private prototype_ `void Tick_Synchronized();` — Process Synchronized state.
- L431 _private prototype_ `void Register();` — Register TimecodeSynchronizer as the TimecodeProvider
- L434 _private prototype_ `void Unregister();` — Unregister TimecodeSynchronizer as the TimecodeProvider
- L436 _private prototype_ `void OpenSources();`
- L437 _private prototype_ `void StartSources();`
- L438 _private prototype_ `void CloseSources();`
- L441 _private prototype_ `void UpdateSourceStates();` — Updates and caches the state of the sources.
- L442 _private prototype_ `FFrameTime CalculateSyncTime();`
- L444 _private prototype_ `FTimecode GetTimecodeInternal() const;`
- L445 _private prototype_ `FFrameRate GetFrameRateInternal() const;`
- L447 _private prototype_ `bool IsSynchronizing() const;`
- L448 _private prototype_ `bool IsSynchronized() const;`
- L449 _private prototype_ `bool IsError() const;`
- L452 _private prototype_ `void SwitchState(const ESynchronizationState NewState);` — Changes internal state and execute it if required
- L454 _private prototype_ `FFrameTime GetProviderFrameTime() const;`
- L460 _public member_ `ETimecodeSynchronizationFrameRateSources FrameRateSource;` — `UPROPERTY(EditAnywhere, Category = "Frame Rate Settings", Meta = (DisplayName = "Frame Rate Source"))` — Frame Rate Source.
- L464 _public member_ `FFrameRate FixedFrameRate;` — `UPROPERTY(EditAnywhere, Category="Frame Rate Settings", Meta=(ClampMin="15.0"))` — The fixed framerate to use.
- L469 _public member_ `ETimecodeSynchronizationTimecodeType TimecodeProviderType;` — `UPROPERTY(EditAnywhere, Category="Timecode Provider", Meta=(DisplayName="Select"))` — Use a Timecode Provider.
- L473 _public member_ `TObjectPtr<UTimecodeProvider> TimecodeProvider;` — `UPROPERTY(EditAnywhere, Instanced, Category="Timecode Provider", Meta=(DisplayName="Timecode Source"))` — Custom strategy to tick in a interval.
- L480 _public member_ `int32 MainSynchronizationSourceIndex;` — `UPROPERTY(EditAnywhere, Category="Timecode Provider")` — Index of the source that drives the synchronized Timecode. The source need to be timecoded and flag as bUseForSynchronization
- L485 _public member_ `bool bUsePreRollingTimecodeMarginOfErrors;` — `UPROPERTY()` — Enable verification of margin between synchronized time and source time
- L489 _public member_ `int32 PreRollingTimecodeMarginOfErrors;` — `UPROPERTY(EditAnywhere, Category="Synchronization", Meta=(EditCondition="bUsePreRollingTimecodeMarginOfErrors", ClampMin="0"))` — Maximum gap size between synchronized time and source time
- L493 _public member_ `bool bUsePreRollingTimeout;` — `UPROPERTY()` — Enable PreRoll timeout
- L497 _public member_ `float PreRollingTimeout;` — `UPROPERTY(EditAnywhere, Category="Synchronization", Meta=(EditCondition="bUsePreRollingTimeout", ClampMin="0.0", ForceUnits=s))` — How long to wait for all source to be ready
- L504 _public member_ `TArray<TObjectPtr<UTimeSynchronizationSource>> TimeSynchronizationInputSources;` — `UPROPERTY(EditAnywhere, Instanced, Category="Input")` — ONLY MODIFY THESE IN EDITOR TODO: Deprecate this and make it private.
- L509 _private member_ `TArray<TObjectPtr<UTimeSynchronizationSource>> DynamicSources;` — `UPROPERTY(Transient)`
- L513 _private member_ `ETimecodeSynchronizationSyncMode SyncMode;` — `UPROPERTY(EditAnywhere, Category = "Synchronization")` — What mode will be used for synchronization.
- L520 _private member_ `int32 FrameOffset;` — `UPROPERTY(EditAnywhere, Category = "Synchronization", Meta=(ClampMin="-640", ClampMax="640"))` — When UserDefined mode is used, the number of frames delayed from the Provider's timecode. Negative values indicate the used timecode will be ahead of the Provider's.
- L528 _private member_ `int32 AutoFrameOffset = 3;` — `UPROPERTY(EditAnywhere, Category = "Synchronization", Meta = (ClampMin = "0", ClampMax = "640"))` — Similar to FrameOffset. For Auto mode, this represents the number of frames behind the newest synced frame. For AutoModeOldest, the is the of frames ahead of the last synced frame.
- L532 _private member_ `bool bWithRollover = false;` — `UPROPERTY(EditAnywhere, Category = "Synchronization")` — Whether or not the specified Provider's timecode rolls over. (Rollover is expected to occur at Timecode 24:00:00:00).
- L536 _private member_ `TArray<FTimecodeSynchronizerActiveTimecodedInputSource> SynchronizedSources;` — `UPROPERTY(Transient, DuplicateTransient, VisibleAnywhere, Category=Debug)` — Sources used for synchronization
- L540 _private member_ `TArray<FTimecodeSynchronizerActiveTimecodedInputSource> NonSynchronizedSources;` — `UPROPERTY(Transient, DuplicateTransient, VisibleAnywhere, Category=Debug)` — Sources that wants to be synchronized
- L543 _private member_ `TObjectPtr<UFixedFrameRateCustomTimeStep> RegisteredCustomTimeStep;` — `UPROPERTY(Transient)`
- L546 _private member_ `TObjectPtr<UTimecodeProvider> CachedPreviousTimecodeProvider;` — `UPROPERTY(Transient)`
- L549 _private member_ `TObjectPtr<UTimecodeProvider> CachedProxiedTimecodeProvider;` — `UPROPERTY(Transient)`
- L552 _private member_ `int32 ActualFrameOffset;` — `UPROPERTY(Transient, DuplicateTransient, VisibleAnywhere, Category = "Synchronization")`
- L556 _private member_ `bool bIsTickEnabled;`
- L558 _private member_ `int64 LastUpdatedSources = 0;`
- L561 _private member_ `ESynchronizationState State;` — The actual synchronization state
- L564 _private member_ `TOptional<FFrameTime> CurrentSystemFrameTime;` — Frame time that we'll use for the system
- L567 _private member_ `FFrameTime CurrentProviderFrameTime;` — The current frame from our specified provider.
- L570 _private member_ `double StartPreRollingTime;` — Timestamp when PreRolling has started
- L573 _private member_ `bool bRegistered;` — Whether or not we are registered as the TimecodeProvider
- L574 _private member_ `float PreviousFixedFrameRate;`
- L575 _private member_ `bool bPreviousUseFixedFrameRate;`
- L578 _private member_ `int32 ActiveMainSynchronizationTimecodedSourceIndex;` — Index of the active source that drives the synchronized Timecode
- L581 _private member_ `FOnTimecodeSynchronizationEvent SynchronizationEvent;` — An event delegate that is invoked when a synchronization event occurred.
- L583 _private member_ `FTimecodeSynchronizerCachedSyncState CachedSyncState;`
- L585 _private member_ `bool bFailGuard;`
- L586 _private member_ `bool bAddSourcesGuard;`
- L587 _private member_ `bool bShouldResetTimecodeProvider;`

#### enum `UTimecodeSynchronizer::ESynchronizationState`  
`enum class ESynchronizationState : uint8`  
_L362-371_
- desc: Synchronization states
- L364 _public enumerator_ `None`
- L365 _public enumerator_ `Error`
- L366 _public enumerator_ `Initializing` — Kicking off the initialization process.
- L367 _public enumerator_ `PreRolling_WaitGenlockTimecodeProvider` — wait for the TimecodeProvider & CustomTimeStep to be Ready
- L368 _public enumerator_ `PreRolling_WaitReadiness` — wait for all source to be Ready
- L369 _public enumerator_ `PreRolling_Synchronizing` — wait and find a valid Timecode to start with
- L370 _public enumerator_ `Synchronized` — all sources are running and synchronized

#### Free symbols / members of external scopes

- L240 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anone9a98c000103`)
- L323 _delegate_ `DECLARE_EVENT_OneParam(UTimecodeSynchronizer, FOnTimecodeSynchronizationEvent, ETimecodeSynchronizationEvent ) FOnTimecodeSynchronizationEvent& OnSynchronizationEvent() { return SynchronizationEvent; } void AddRuntimeTimeSynchronizationSource(UTimeSynchronizationSource* Source);` — Get an event delegate that is invoked when a Asset synchronization event occurred. @return The delegate.

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer/Public/TimecodeSynchronizerModule.h` (Public)


#### class `ITimecodeSynchronizerModule`  
`class ITimecodeSynchronizerModule : public IModuleInterface`  
_L15-35_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- inherits: `IModuleInterface`
- L22 _public function_ `static inline ITimecodeSynchronizerModule& Get()` — Singleton-like access to ITimecodeSynchronizerModule @return Returns TimecodeSynchronizerModule singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L10 _macro_ `#define TIMECODESYNCHRONIZER_MODULE_NAME TEXT("TimecodeSynchronizer")`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimecodeSynchronizer, Verbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTimecodeSynchronizer, Verbose, All);`

### `Plugins/Media/TimecodeSynchronizer/Source/TimecodeSynchronizer/Public/TimecodeSynchronizerProjectSettings.h` (Public)


#### class `UTimecodeSynchronizerProjectSettings`  
`class UTimecodeSynchronizerProjectSettings : public UObject`  
_L18-48_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- reflection: `UCLASS(config=Engine)`
- inherits: `UObject`
- desc: Global settings for TimecodeSynchronizer
- L23 _public function_ `UTimecodeSynchronizerProjectSettings() : bDisplayInToolbar(false)`
- L30 _public member_ `bool bDisplayInToolbar;` — `UPROPERTY(Config, EditAnywhere, Category="TimecodeSynchronizer", meta=(ConfigRestartRequired=true))` — Display the timecode synchronizer icon in the editor toolbar.
- L33 _public member_ `TSoftObjectPtr<UTimecodeSynchronizer> DefaultTimecodeSynchronizer;` — `UPROPERTY(config, EditAnywhere, Category="TimecodeSynchronizer")`
- L36 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)`
- L47 _public member_ `FSimpleMulticastDelegate OnDefaultTimecodeSynchronizerChanged;`

#### class `UTimecodeSynchronizerEditorSettings`  
`class UTimecodeSynchronizerEditorSettings : public UObject`  
_L55-64_
- reflection: `UE_DEPRECATED(5.0, "The TimecodeSynchronizer plugin is deprecated. Please update your project to use the features of the TimedDataMonitor plugin.")`
- reflection: `UCLASS(config= EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Editor settings for TimecodeSynchronizer
- L63 _public member_ `TSoftObjectPtr<UTimecodeSynchronizer> UserTimecodeSynchronizer;` — `UPROPERTY(config, EditAnywhere, Category="TimecodeSynchronizer")`
