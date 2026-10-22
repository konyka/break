# Plugins / HarmonixMetasound

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMetasound`
- headers: 97; symbols: 2461
- symbol kinds: class=63, delegate=19, enum=15, enumerator=194, externvar=13, function=224, macro=52, member=530, namespace=228, prototype=1036, struct=51, typedef=21, variable=15
- PrivateDependencyModuleNames: AssetRegistry, AudioExtensions, MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, SignalProcessing, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Harmonix, HarmonixDsp, HarmonixMidi, MetasoundStandardNodes, MovieScene, MusicEnvironment, TimeManagement

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Private/HarmonixMetasound/Components/MetasoundMusicClockDriver.h` (Private)


#### class `FMetasoundMusicClockDriver`  
`class FMetasoundMusicClockDriver : public FMusicClockDriverBase`  
_L14-145_
- inherits: `FMusicClockDriverBase`
- L17 _public function_ `FMetasoundMusicClockDriver(UObject* WorldContextObj, const FMetasoundMusicClockSettings& Settings) : FMusicClockDriverBase(WorldContextObj, Settings)`
- L20 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L22 _public prototype_ `virtual bool CalculateSongPosWithOffset(float MsOffset, ECalibratedMusicTimebase Timebase, FMidiSongPos& OutResult) const override;`
- L24 _public prototype_ `virtual void Disconnect() override;`
- L25 _public prototype_ `virtual bool RefreshCurrentSongPos() override;`
- L26 _public prototype_ `virtual void OnStart() override;`
- L27 _public prototype_ `virtual void OnPause() override;`
- L28 _public prototype_ `virtual void OnContinue() override;`
- L29 _public prototype_ `virtual void OnStop() override;`
- L30 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const override;`
- L32 _public prototype_ `virtual bool LoopedThisFrame(ECalibratedMusicTimebase Timebase) const override;`
- L33 _public prototype_ `virtual bool SeekedThisFrame(ECalibratedMusicTimebase Timebase) const override;`
- L36 _public prototype_ `virtual FString GetDisplayName() const override;`
- L39 _public prototype_ `bool ConnectToAudioComponentsMetasound( UAudioComponent* InAudioComponent, FName MetasoundOuputPinName = "MIDI Clock", UMetasoundGeneratorHandle::FOnAttached::FDelegate OnGeneratorAttachedCallback = UMetasoundGeneratorHandle::FOnAttached::FDelegate::CreateLambda([](){}), UMetasoundGeneratorHandle::FOnDetached::FDelegate OnGeneratorDetachedCallback = UMetasoundGeneratorHandle::FOnDetached::FDelegate::CreateLambda([](){}));`
- L42 _public function_ `UAudioComponent* InAudioComponent, FName MetasoundOuputPinName = "MIDI Clock", UMetasoundGeneratorHandle::FOnAttached::FDelegate OnGeneratorAttachedCallback = UMetasoundGeneratorHandle::FOnAttached::FDelegate::CreateLambda([](){}), UMetasoundGeneratorHandle::FOnDetached::FDelegate OnGeneratorDetachedCallback = UMetasoundGeneratorHandle::FOnDetached::FDelegate::CreateLambda([](){}));`
- L45 _public member_ `bool RunPastMusicEnd = false;`
- L48 _protected prototype_ `void OnGeneratorAttached();`
- L49 _protected prototype_ `void OnGeneratorDetached();`
- L50 _protected prototype_ `void OnGraphSet();`
- L51 _protected prototype_ `void OnGeneratorIOUpdatedWithChanges(const TArray<Metasound::FVertexInterfaceChange>& VertexInterfaceChanges);`
- L54 _private member_ `FName MetasoundOutputName;`
- L57 _private member_ `TWeakObjectPtr<UAudioComponent> AudioComponentToWatch;` — We can keep a week reference to this because our "owner" is a UClass and also has a reference to it...
- L59 _private member_ `TStrongObjectPtr<UMetasoundGeneratorHandle> CurrentGeneratorHandle;` — We need a strong object ptr to this next thing since we will be the only one holding a reference to it...
- L60 _private member_ `TWeakPtr<Metasound::FMetasoundGenerator> UnderlyingGenerator;`
- L62 _private member_ `Metasound::Frontend::FAnalyzerAddress MidiSongPosAnalyzerAddress;`
- L64 _private member_ `UMidiClockUpdateSubsystem::FClockHistoryPtr ClockHistory;`
- L65 _private member_ `HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor SmoothedAudioRenderClockHistoryCursor;`
- L66 _private member_ `HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor SmoothedPlayerExperienceClockHistoryCursor;`
- L67 _private member_ `HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor SmoothedVideoRenderClockHistoryCursor;`
- L69 _private member_ `TSharedPtr<const HarmonixMetasound::Analysis::FSongMapChain> CurrentMapChain;`
- L71 _private member_ `bool bRunning = false;`
- L72 _private member_ `double FreeRunStartTimeSecs = 0.0;`
- L73 _private member_ `bool WasEverConnected = false;`
- L74 _private member_ `float SongPosOffsetMs = 0.0f;`
- L75 _private member_ `int32 LastTickSeen = 0;`
- L76 _private member_ `float RenderSmoothingLagSeconds = 0.030f;`
- L78 _private member_ `double RenderStartWallClockTimeSeconds = 0.0;`
- L79 _private member_ `double LastRefreshWallClockTimeSeconds = 0.0;`
- L80 _private member_ `double DeltaSecondsBetweenRefreshes = 0.0;`
- L82 _private member_ `Metasound::FSampleCount RenderStartSampleCount {0};`
- L84 _private member_ `static const int kFramesOfErrorHistory = 10;`
- L85 _private member_ `FLocalMinimumMagnitudeTracker<double, kFramesOfErrorHistory> ErrorTracker;`
- L86 _private member_ `double SyncSpeed = 1.0;`
- L95 _private member_ `FPerTimebaseSmoothedClockState AudioRenderState;`
- L96 _private member_ `FPerTimebaseSmoothedClockState PlayerExperienceState;`
- L97 _private member_ `FPerTimebaseSmoothedClockState VideoRenderState;`
- L99 _private member_ `UMetasoundGeneratorHandle::FOnAttached::FDelegate OnAttachedDelegate;`
- L100 _private member_ `UMetasoundGeneratorHandle::FOnDetached::FDelegate OnDetachedDelegate;`
- L102 _private member_ `FDelegateHandle GeneratorAttachedCallbackHandle;`
- L103 _private member_ `FDelegateHandle GeneratorDetachedCallbackHandle;`
- L104 _private member_ `FDelegateHandle GeneratorIOUpdatedCallbackHandle;`
- L105 _private member_ `FDelegateHandle GraphChangedCallbackHandle;`
- L107 _private member_ `bool AudioRenderSeekDetected = false;`
- L108 _private member_ `bool AudioRenderLoopDetected = false;`
- L109 _private member_ `bool PlayerExperiencedSeekDetected = false;`
- L110 _private member_ `bool PlayerExperiencedLoopDetected = false;`
- L111 _private member_ `bool VideoRenderSeekDetected = false;`
- L112 _private member_ `bool VideoRenderLoopDetected = false;`
- L114 _private prototype_ `FMidiSongPos CalculateSongPosAtMsForLoopingOrMonotonicClock(float AbsoluteMs, float& PositionTick, bool& SeekDetected, bool& LoopDetected) const;`
- L115 _private prototype_ `FMidiSongPos CalculateSongPosAtMsForOffsetClock(float PositionMs, float ClockTickOffsetFromDrivingClock, float& PositionTick, bool& SeekDetected) const;`
- L116 _private prototype_ `bool CheckForSeek(float FirstTick, float NextTick, float CurrentTempo, int32 TicksPerQuarter) const;`
- L118 _private prototype_ `void UpdateCurrentTicksForOffsetClock(float SmoothedTick, float SmoothedTempoMapTick);`
- L119 _private prototype_ `void UpdateCurrentTicksForLoopingOrMonotonicClock(float SmoothedTick, float SmoothedTempoMapTick);`
- L121 _private prototype_ `bool AttemptToConnectToAudioComponentsMetasound( UAudioComponent* InAudioComponent, UMetasoundGeneratorHandle::FOnAttached::FDelegate OnGeneratorAttachedCallback, UMetasoundGeneratorHandle::FOnDetached::FDelegate OnGeneratorDetachedCallback);`
- L125 _private prototype_ `void DetachAllCallbacks();`
- L126 _private prototype_ `void RefreshCurrentSongPosFromWallClock();`
- L127 _private prototype_ `void RefreshCurrentSongPosFromHistory();`
- L129 _private prototype_ `void SetClockHistory(const UMidiClockUpdateSubsystem::FClockHistoryPtr&);` — always go through this to change ClockHistory
- L140 _private prototype_ `EHistoryFailureType CalculateSmoothedTick(Metasound::FSampleCount ExpectedRenderPosSampleCount, Metasound::FSampleCount LastRenderPosSampleCount, float& SmoothedTick, float& SmoothedTempoMapTick, float& CurrentSpeed, HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor& ReadCursor, float LookBehindSeconds);`
- L144 _private prototype_ `static FString HistoryFailureTypeToString(FMetasoundMusicClockDriver::EHistoryFailureType Error);`

#### struct `FMetasoundMusicClockDriver::FPerTimebaseSmoothedClockState`  
`struct FPerTimebaseSmoothedClockState`  
_L88-93_
- L90 _public member_ `float TempoMapMs = 0.0f;`
- L91 _public member_ `float TempoMapTick = 0.0f;`
- L92 _public member_ `float LocalTick = 0.0f;`

#### enum `FMetasoundMusicClockDriver::EHistoryFailureType`  
`enum class EHistoryFailureType : uint8`  
_L131-138_
- L133 _public enumerator_ `None`
- L134 _public enumerator_ `NotEnoughDataInTheHistoryRing`
- L135 _public enumerator_ `NotEnoughHistory`
- L136 _public enumerator_ `LookingForTimeInTheFutureOfWhatHasEvenRendered`
- L137 _public enumerator_ `CaughtUpToRenderPosition`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Private/HarmonixMetasound/Components/WallClockMusicClockDriver.h` (Private)


#### class `FWallClockMusicClockDriver`  
`class FWallClockMusicClockDriver : public FMusicClockDriverBase`  
_L6-36_
- inherits: `FMusicClockDriverBase`
- L9 _public function_ `FWallClockMusicClockDriver(UObject* WorldContextObj, const FWallClockMusicClockSettings& Settings) : FMusicClockDriverBase(WorldContextObj, Settings) , TempoMapMidi(Settings.TempoMap)`
- L14 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L16 _public prototype_ `virtual void Disconnect() override;`
- L17 _public prototype_ `virtual bool RefreshCurrentSongPos() override;`
- L18 _public prototype_ `virtual void OnStart() override;`
- L19 _public prototype_ `virtual void OnPause() override;`
- L20 _public prototype_ `virtual void OnContinue() override;`
- L21 _public function_ `virtual void OnStop() override`
- L22 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const override;`
- L24 _public function_ `virtual bool LoopedThisFrame(ECalibratedMusicTimebase Timebase) const override`
- L25 _public function_ `virtual bool SeekedThisFrame(ECalibratedMusicTimebase Timebase) const override`
- L28 _public prototype_ `virtual FString GetDisplayName() const override;`
- L32 _private member_ `TWeakObjectPtr<UMidiFile> TempoMapMidi;`
- L34 _private member_ `double StartTimeSecs = 0.0;`
- L35 _private member_ `double PauseTimeSecs = 0.0f;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Private/HarmonixMetasound/DataTypes/FusionSyncLink.h` (Private)


#### class `HarmonixMetasound::FFusionSyncLink`  
`class FFusionSyncLink`  
_L17-77_
- desc: This class is a thin wrapper around a task handle that allows multiple Fusion Sampler Nodes to kick asynchronous rendering jobs that are "joined" later by a MultiThreadedFusionSynchronizerNode.
- L20 _public typedef_ `using FRenderFunction = TUniqueFunction<void(void)>;`
- L22 _public function_ `FFusionSyncLink()`
- L25 _public function_ `~FFusionSyncLink()`
- L33 _public function_ `void KickAsyncRender(FRenderFunction&& InRenderFunction)` — This function is called by the FusionSamplerNode when it is enabled for multi-threaded rendering.
- L42 _public function_ `UE::Tasks::FTask GetTask() const` — This function is called by the MultiThreadedFusionSynchronizerNode where it gathers the task handles from all of the samplers it is "synchronizing" so it can then optimally "join" on the completion of all of those tasks.
- L53 _public function_ `void PostExecute()` — This function is called by the FusionSamplerNode "PostExecute" so that if no down-stream MultiThreadedFusionSynchronizerNode does a join we can detect that and at least (a) notify the user, and (b) ensure the task is completed before the metasound tries to render another block.
- L66 _public function_ `void Reset()` — This function is called by the FusionSamplerNode "Reset" We need to block on reset and make sure the task completes and clear it out
- L76 _private member_ `UE::Tasks::FTask Task;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionAsync, Log, Log) namespace HarmonixMetasound { class FFusionSyncLink { public: using FRenderFunction = TUniqueFunction<void(void)>; FFusionSyncLink() {} ~FFusionSyncLink() { Task.Wait(); } void KickAsyncRender(FRenderFunction&& InRenderFunction) { Task = UE::Tasks::Launch(UE_SOURCE_LOCATION, MoveTemp(InRenderFunction), LowLevelTasks::ETaskPriority::High); } UE::Tasks::FTask GetTask() const { return Task; } /** This function is called by the FusionSamplerNode "PostExecute" * so that if no down-stream MultiThreadedFusionSynchronizerNode does a`
- L11 _namespace_ `namespace HarmonixMetasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Private/HarmonixMetasound/Interfaces/HarmonixMusicInterfaces.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace MusicAssetInterface` (scope `HarmonixMetasound`)
- L11 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `HarmonixMetasound::MusicAssetInterface`)
- L12 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `HarmonixMetasound::MusicAssetInterface`)
- L14 _externvar_ `const extern FMetasoundFrontendVersion FrontendVersion;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L15 _externvar_ `const extern FLazyName PlayIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L16 _externvar_ `const extern FLazyName PauseIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L17 _externvar_ `const extern FLazyName ContinueIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L18 _externvar_ `const extern FLazyName StopIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L19 _externvar_ `const extern FLazyName KillIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L20 _externvar_ `const extern FLazyName SeekIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L21 _externvar_ `const extern FLazyName SeekTargetSecondsIn;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L22 _externvar_ `const extern FLazyName MidiClockOut;` (scope `HarmonixMetasound::MusicAssetInterface`)
- L25 _prototype_ `void RegisterHarmonixMetasoundMusicInterfaces();` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Private/HarmonixMetasound/MusicEnvironmentSupport/HarmonixMusicEnvironmentMetronome.h` (Private)


#### class `UHarmonixMusicEnvironmentMetronome`  
`class UHarmonixMusicEnvironmentMetronome : public UObject, public IMusicEnvironmentMetronome`  
_L26-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IMusicEnvironmentMetronome`
- desc: Implementation of the generic MusicEnvironmentSubsystem's metronome interface. So that subsystem can create metronomes based on the Harmonix tech.
- L31 _public prototype_ `virtual bool Initialize(UWorld* InWorld) override;`
- L32 _public prototype_ `virtual void Tick(float DeltaSecs) override;`
- L33 _public prototype_ `virtual void Start(double FromSeconds = 0.0) override;`
- L34 _public prototype_ `virtual void Seek(double ToSeconds) override;`
- L35 _public prototype_ `virtual void Stop() override;`
- L36 _public prototype_ `virtual void Pause() override;`
- L37 _public prototype_ `virtual void Resume() override;`
- L39 _public prototype_ `virtual float GetCurrentTempo() const override;`
- L40 _public prototype_ `virtual float GetCurrentVolume() const override;`
- L41 _public prototype_ `virtual float GetCurrentSpeed() const override;`
- L42 _public prototype_ `virtual double GetCurrentPositionSeconds() const override;`
- L43 _public prototype_ `virtual bool IsMuted() const override;`
- L46 _public prototype_ `virtual float GetPositionSeconds() const override;` — vvv BEGIN  IMusicEnvironmentClockSource Implementation vvv
- L47 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime() const override;`
- L48 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime(const FMusicalTime& SourceSpaceOffset) const override;`
- L49 _public prototype_ `virtual int32 GetPositionAbsoluteTick() const override;`
- L50 _public prototype_ `virtual int32 GetPositionAbsoluteTick(const FMusicalTime& SourceSpaceOffset) const override;`
- L51 _public prototype_ `virtual FMusicalTime Quantize(const FMusicalTime& MusicalTime, int32 QuantizationInterval, UFrameBasedMusicMap::EQuantizeDirection Direction = UFrameBasedMusicMap::EQuantizeDirection::Nearest) const override;`
- L52 _public function_ `virtual bool CanAuditionInEditor() const override`
- L55 _public prototype_ `virtual void BeginDestroy() override;`
- L58 _protected prototype_ `virtual void OnMusicMapSet() override;`
- L59 _protected prototype_ `virtual bool OnSetTempo(float Bpm) override;`
- L60 _protected prototype_ `virtual void OnSetSpeed(const float Speed) override;`
- L61 _protected prototype_ `virtual void OnSetVolume(float InVolume) override;`
- L62 _protected prototype_ `virtual void OnSetMuted(bool bNewMuted) override;`
- L66 _private member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(Transient)`
- L68 _private member_ `TObjectPtr<UMusicClockComponent> MusicClockComponent;` — `UPROPERTY(Transient)`
- L71 _private member_ `TObjectPtr<UMidiFile> MidiFile;` — `UPROPERTY(Transient)`
- L74 _private member_ `TObjectPtr<UMetaSoundSourceBuilder> SourceBuilder;` — `UPROPERTY(Transient)`
- L76 _private member_ `FMetaSoundBuilderNodeOutputHandle OnPlayNodeOutput;` — `UPROPERTY(Transient)`
- L78 _private member_ `FMetaSoundBuilderNodeInputHandle OnFinishedNodeInput;` — `UPROPERTY(Transient)`
- L80 _private member_ `TArray<FMetaSoundBuilderNodeInputHandle> AudioOutNodeInputs;` — `UPROPERTY(Transient)`
- L82 _private member_ `bool bMetasoundIsPlaying = false;`
- L83 _private member_ `float CurrentTempo = 120.0f;`
- L84 _private member_ `float CurrentSpeed = 1.0f;`
- L85 _private member_ `bool bIsMuted = false;`
- L86 _private member_ `float CurrentVolume = 1.0f;`
- L87 _private member_ `double SecondsWhenStarted = 0.0;`
- L88 _private member_ `FMusicalTime MusicalTimeWhenStarted;`
- L90 _private prototype_ `bool BuildAndStartMetasound(UWorld* InWorld);`
- L91 _private prototype_ `bool RebuildMidiFile();`
- L92 _private prototype_ `bool BuildMetasound();`
- L93 _private prototype_ `FMetaSoundBuilderNodeOutputHandle AddGraphInput(const FName& InputName, UMidiFile* MidiFile) const;`
- L94 _private prototype_ `FMetaSoundBuilderNodeOutputHandle AddGraphInput(const FName& InputName, const float Value) const;`
- L95 _private prototype_ `FMetaSoundBuilderNodeOutputHandle AddGraphInput(const FName& InputName, const bool Value) const;`
- L96 _private prototype_ `FMetaSoundBuilderNodeOutputHandle AddGraphInputTrigger(const FName& InputName) const;`
- L97 _private prototype_ `bool SetNodeInputDefault(const FMetaSoundNodeHandle& Node, const FName& InputName, const int32 Value) const;`
- L98 _private prototype_ `bool SetNodeInputDefault(const FMetaSoundNodeHandle& Node, const FName& InputName, const float Value) const;`
- L99 _private prototype_ `bool SetNodeInputDefault(const FMetaSoundNodeHandle& Node, const FName& InputName, const TArray<float>& Values) const;`
- L100 _private prototype_ `bool ConnectGraphInputToNodeInput(const FName& GraphInputName, const FMetaSoundNodeHandle& Node, const FName& NodeInputName) const;`
- L101 _private prototype_ `bool ConnectNodeOutputToGraphOutput(const FMetaSoundNodeHandle& Node, const FName& NodeOutputName, const FName& GraphOutputName) const;`
- L102 _private prototype_ `bool ConnectNodes(const FMetaSoundNodeHandle& SourceNode, const FName& OutName, const FMetaSoundNodeHandle& DestinationNode, const FName& InName) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/FFTAnalyzerResultVertexAnalyzer.h` (Public)


#### class `HarmonixMetasound::Analysis::FFFTAnalyzerResultVertexAnalyzer`  
`class FFFTAnalyzerResultVertexAnalyzer final : public Metasound::Frontend::FVertexAnalyzerBase`  
_L14-38_
- inherits: `Metasound::Frontend::FVertexAnalyzerBase`
- L17 _public prototype_ `static const FName& GetAnalyzerName();`
- L18 _public prototype_ `static const FName& GetDataType();`
- L31 _public prototype_ `explicit FFFTAnalyzerResultVertexAnalyzer(const Metasound::Frontend::FCreateAnalyzerParams& InParams);`
- L32 _public prototype_ `virtual ~FFFTAnalyzerResultVertexAnalyzer() override = default;`
- L34 _public prototype_ `virtual void Execute() override;`
- L37 _private member_ `FHarmonixFFTAnalyzerResultsWriteRef LastAnalyzerResult;`

#### struct `HarmonixMetasound::Analysis::FFFTAnalyzerResultVertexAnalyzer::FOutputs`  
`struct FOutputs`  
_L20-23_
- L22 _public prototype_ `static const Metasound::Frontend::FAnalyzerOutput& GetValue();`

#### class `HarmonixMetasound::Analysis::FFFTAnalyzerResultVertexAnalyzer::FFactory`  
`class FFactory final : public Metasound::Frontend::TVertexAnalyzerFactory<FFFTAnalyzerResultVertexAnalyzer>`  
_L25-29_
- inherits: `Metasound::Frontend::TVertexAnalyzerFactory<FFFTAnalyzerResultVertexAnalyzer>`
- L28 _public prototype_ `virtual const TArray<Metasound::Frontend::FAnalyzerOutput>& GetAnalyzerOutputs() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L12 _namespace_ `namespace HarmonixMetasound`
- L12 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/MidiClockSongPos.h` (Public)


#### struct `HarmonixMetasound::Analysis::FMidiClockSongPosition`  
`struct FMidiClockSongPosition`  
_L13-27_
- L21 _public member_ `Metasound::FSampleCount SampleCount {0};`
- L22 _public member_ `int32 UpToTick;`
- L23 _public member_ `int32 TempoMapTick;`
- L24 _public member_ `float CurrentSpeed {1.0f};`
- L25 _public member_ `EMusicPlayerTransportState CurrentTransportState {EMusicPlayerTransportState::Invalid};`
- L26 _public member_ `EMarkerType MarkerType {EMarkerType::None};`

#### enum `HarmonixMetasound::Analysis::FMidiClockSongPosition::EMarkerType`  
`enum class EMarkerType : uint8`  
_L15-20_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `LastPositionBeforeSeekLoop`
- L19 _public enumerator_ `FirstPositionAfterSeekLoop`

#### struct `HarmonixMetasound::Analysis::FSongMapChain`  
`struct FSongMapChain : TSharedFromThis<FSongMapChain>`  
_L29-71_
- inherits: `TSharedFromThis<FSongMapChain>`
- L31 _public function_ `FSongMapChain()`
- L32 _public function_ `FSongMapChain(TSharedPtr<const ISongMapEvaluator>& InMaps, int32 InFirstTickInLoop, int32 InLoopLengthTicks) : SongMaps(InMaps) , FirstTickInLoop(InFirstTickInLoop) , LoopLengthTicks(InLoopLengthTicks)`
- L38 _public member_ `TSharedPtr<const ISongMapEvaluator> SongMaps;`
- L39 _public member_ `int32 FirstTickInLoop {-1};`
- L40 _public member_ `int32 LoopLengthTicks {0};`
- L42 _public function_ `TSharedPtr<FSongMapChain> GetLatest()`
- L52 _public function_ `void Update(TSharedPtr<const ISongMapEvaluator>& InMaps, int32 InFirstTickInLoop, int32 InLoopLengthTicks)`
- L63 _public function_ `bool IsLatest() const`
- L69 _private member_ `std::atomic<FSongMapChain*> NewSongMapsPtr = nullptr;`
- L70 _private member_ `TSharedPtr<FSongMapChain> NewSongMaps;`

#### struct `HarmonixMetasound::Analysis::FMidiClockSongPositionHistory`  
`struct FMidiClockSongPositionHistory`  
_L76-115_
- L78 _public typedef_ `using FPositionQueue = FSpmcAnalysisResultQueue<FMidiClockSongPosition>;`
- L79 _public typedef_ `using FScopedItemWriteRef = FPositionQueue::FScopedItemWriteRef;`
- L80 _public typedef_ `using FScopedItemConsumeRef = FPositionQueue::FScopedItemConsumeRef;`
- L81 _public typedef_ `using FScopedItemPeekRef = FPositionQueue::FScopedItemPeekRef;`
- L82 _public typedef_ `using FReadCursor = FPositionQueue::FReadCursor;`
- L84 _public function_ `FMidiClockSongPositionHistory(int32 NumItems) : Positions(NumItems) , SongMapChain(MakeShared<FSongMapChain>())`
- L89 _public member_ `FPositionQueue Positions;`
- L91 _public member_ `TSharedPtr<FSongMapChain> SongMapChain;`
- L93 _public member_ `float SampleRate {48000.0f};`
- L95 _public function_ `FReadCursor CreateReadCursor()`
- L100 _public function_ `TSharedPtr<const FSongMapChain> GetLatestMapsForConsumer()`
- L106 _public function_ `TSharedPtr<const FSongMapChain> GetLatestMapsForProducer() const`
- L111 _public function_ `void UpdateMaps(TSharedPtr<const ISongMapEvaluator> Maps, int32 InFirstTickInLoop, int32 InLoopLengthTicks)`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HarmonixMetasound`
- L11 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/MidiClockVertexAnalyzer.h` (Public)


#### class `HarmonixMetasound::Analysis::FMidiClockVertexAnalyzer`  
`class FMidiClockVertexAnalyzer final : public Metasound::Frontend::FVertexAnalyzerBase`  
_L15-50_
- inherits: `Metasound::Frontend::FVertexAnalyzerBase`
- L38 _public prototype_ `static const FName& GetAnalyzerName();`
- L39 _public prototype_ `static const FName& GetDataType();`
- L41 _public prototype_ `explicit FMidiClockVertexAnalyzer(const Metasound::Frontend::FCreateAnalyzerParams& InParams);`
- L43 _public prototype_ `virtual void Execute() override;`
- L46 _private member_ `FMusicTimestampWriteRef Timestamp;`
- L47 _private member_ `Metasound::FFloatWriteRef Tempo;`
- L48 _private member_ `FTimeSignatureWriteRef TimeSignature;`
- L49 _private member_ `Metasound::FFloatWriteRef Speed;`

#### struct `HarmonixMetasound::Analysis::FMidiClockVertexAnalyzer::FOutputs`  
`struct FOutputs`  
_L18-30_
- L24 _public prototype_ `static const Metasound::Frontend::FAnalyzerOutput& GetValue();` — @brief Get the default output for this analyzer @return The default output
- L26 _public member_ `static const Metasound::Frontend::FAnalyzerOutput Timestamp;`
- L27 _public member_ `static const Metasound::Frontend::FAnalyzerOutput Tempo;`
- L28 _public member_ `static const Metasound::Frontend::FAnalyzerOutput TimeSignature;`
- L29 _public member_ `static const Metasound::Frontend::FAnalyzerOutput Speed;`

#### class `HarmonixMetasound::Analysis::FMidiClockVertexAnalyzer::FFactory`  
`class FFactory final : public Metasound::Frontend::TVertexAnalyzerFactory<FMidiClockVertexAnalyzer>`  
_L32-36_
- inherits: `Metasound::Frontend::TVertexAnalyzerFactory<FMidiClockVertexAnalyzer>`
- L35 _public prototype_ `virtual const TArray<Metasound::Frontend::FAnalyzerOutput>& GetAnalyzerOutputs() const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L13 _namespace_ `namespace HarmonixMetasound`
- L13 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/MidiSongPosVertexAnalyzer.h` (Public)


#### class `HarmonixMetasound::Analysis::FMidiSongPosVertexAnalyzer`  
`class FMidiSongPosVertexAnalyzer final : public Metasound::Frontend::FVertexAnalyzerBase`  
_L26-66_
- inherits: `Metasound::Frontend::FVertexAnalyzerBase`
- L29 _public member_ `static const Metasound::Frontend::FAnalyzerOutput SongPosition;`
- L37 _public prototype_ `static const FName& GetAnalyzerName();`
- L38 _public prototype_ `static const FName& GetDataType();`
- L40 _public prototype_ `explicit FMidiSongPosVertexAnalyzer(const Metasound::Frontend::FCreateAnalyzerParams& InParams);`
- L41 _public prototype_ `virtual ~FMidiSongPosVertexAnalyzer();`
- L43 _public prototype_ `virtual void Execute() override;`
- L46 _private member_ `TWeakPtr<const FMidiClock, ESPMode::NotThreadSafe> LastClock;`
- L47 _private member_ `FMidiClockSongPositionWriteRef LastMidiClockSongPos;`
- L48 _private member_ `TSharedPtr<FMidiClockSongPositionHistory> History;`
- L49 _private member_ `bool LastPosWasSeekOrLoop {false};`
- L50 _private member_ `float SampleRate {0.0f};`
- L51 _private member_ `int32 BlockSize {0};`
- L52 _private member_ `Metasound::FSampleCount SampleCount {0};`
- L53 _private member_ `int32 LastTickProcessed {-1};`
- L54 _private member_ `int32 LastTempoMapTickProcessed {-1};`
- L55 _private member_ `int32 LastAdvanceUpToTick {-1};`
- L56 _private member_ `float CurrentFramesPerTick {0.0f};`
- L57 _private member_ `const ISongMapEvaluator* CurrentSongMapEvaluator {nullptr};`
- L59 _private prototype_ `bool TryProcessAsAdvance(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L60 _private prototype_ `bool TryProcessAsTempoChange(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L61 _private prototype_ `bool TryProcessAsTimeSignatureChange(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L62 _private prototype_ `bool TryProcessAsSpeedChange(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L63 _private prototype_ `bool TryProcessAsTransportChange(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L64 _private prototype_ `bool TryProcessAsLoop(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`
- L65 _private prototype_ `bool TryProcessAsSeek(const HarmonixMetasound::FMidiClockEvent& Event, int32& BlockFrameAdvance, bool FirstEventAfterSeekOrLoop);`

#### class `HarmonixMetasound::Analysis::FMidiSongPosVertexAnalyzer::FFactory`  
`class FFactory final : public Metasound::Frontend::TVertexAnalyzerFactory<FMidiSongPosVertexAnalyzer>`  
_L31-35_
- inherits: `Metasound::Frontend::TVertexAnalyzerFactory<FMidiSongPosVertexAnalyzer>`
- L34 _public prototype_ `virtual const TArray<Metasound::Frontend::FAnalyzerOutput>& GetAnalyzerOutputs() const override;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L19 _namespace_ `namespace HarmonixMetasound`
- L24 _namespace_ `namespace HarmonixMetasound`
- L24 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/MidiStreamVertexAnalyzer.h` (Public)


#### class `HarmonixMetasound::Analysis::FMidiStreamVertexAnalyzer`  
`class FMidiStreamVertexAnalyzer final : public Metasound::Frontend::FVertexAnalyzerBase`  
_L14-38_
- inherits: `Metasound::Frontend::FVertexAnalyzerBase`
- L17 _public prototype_ `static const FName& GetAnalyzerName();`
- L18 _public prototype_ `static const FName& GetDataType();`
- L31 _public prototype_ `explicit FMidiStreamVertexAnalyzer(const Metasound::Frontend::FCreateAnalyzerParams& InParams);`
- L32 _public prototype_ `virtual ~FMidiStreamVertexAnalyzer() override = default;`
- L34 _public prototype_ `virtual void Execute() override;`
- L37 _private member_ `FMidiEventInfoWriteRef LastMidiEvent;`

#### struct `HarmonixMetasound::Analysis::FMidiStreamVertexAnalyzer::FOutputs`  
`struct FOutputs`  
_L20-23_
- L22 _public prototype_ `static const Metasound::Frontend::FAnalyzerOutput& GetValue();`

#### class `HarmonixMetasound::Analysis::FMidiStreamVertexAnalyzer::FFactory`  
`class FFactory final : public Metasound::Frontend::TVertexAnalyzerFactory<FMidiStreamVertexAnalyzer>`  
_L25-29_
- inherits: `Metasound::Frontend::TVertexAnalyzerFactory<FMidiStreamVertexAnalyzer>`
- L28 _public prototype_ `virtual const TArray<Metasound::Frontend::FAnalyzerOutput>& GetAnalyzerOutputs() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L12 _namespace_ `namespace HarmonixMetasound`
- L12 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/MusicTransportEventStreamVertexAnalyzer.h` (Public)


#### class `HarmonixMetasound::Analysis::FMusicTransportEventStreamVertexAnalyzer`  
`class FMusicTransportEventStreamVertexAnalyzer final : public Metasound::Frontend::FVertexAnalyzerBase`  
_L14-54_
- inherits: `Metasound::Frontend::FVertexAnalyzerBase`
- L17 _public prototype_ `static const FName& GetAnalyzerName();`
- L18 _public prototype_ `static const FName& GetDataType();`
- L41 _public prototype_ `explicit FMusicTransportEventStreamVertexAnalyzer(const Metasound::Frontend::FCreateAnalyzerParams& InParams);`
- L42 _public prototype_ `virtual ~FMusicTransportEventStreamVertexAnalyzer() override = default;`
- L44 _public prototype_ `virtual void Execute() override;`
- L47 _private member_ `FMusicSeekTargetWriteRef SeekDestination;`
- L48 _private member_ `FMusicTransportEventWriteRef LastMusicTransportEvent;`
- L49 _private member_ `int64 NumFrames{ 0 };`
- L50 _private member_ `int32 FramesPerBlock{ 0 };`
- L51 _private member_ `float SampleRate{ 0 };`
- L53 _private member_ `static const FName AnalyzerName;`

#### struct `HarmonixMetasound::Analysis::FMusicTransportEventStreamVertexAnalyzer::FOutputs`  
`struct FOutputs`  
_L20-30_
- L26 _public prototype_ `static const Metasound::Frontend::FAnalyzerOutput& GetValue();` — @brief Get the default output for this analyzer @return The default output
- L28 _public member_ `static const Metasound::Frontend::FAnalyzerOutput SeekDestination;`
- L29 _public member_ `static const Metasound::Frontend::FAnalyzerOutput TransportEvent;`

#### class `HarmonixMetasound::Analysis::FMusicTransportEventStreamVertexAnalyzer::FFactory`  
`class FFactory final : public Metasound::Frontend::TVertexAnalyzerFactory<FMusicTransportEventStreamVertexAnalyzer>`  
_L32-39_
- inherits: `Metasound::Frontend::TVertexAnalyzerFactory<FMusicTransportEventStreamVertexAnalyzer>`
- L35 _public prototype_ `virtual const TArray<Metasound::Frontend::FAnalyzerOutput>& GetAnalyzerOutputs() const override;`
- L38 _private member_ `static const TArray<Metasound::Frontend::FAnalyzerOutput> AnalyzerOutputs;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L12 _namespace_ `namespace HarmonixMetasound`
- L12 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/PeakTamer.h` (Public)


#### struct `FHarmonixPeakTamerSettings`  
`struct FHarmonixPeakTamerSettings`  
_L10-28_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `float PeakAttackTimeSeconds = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AudioAnalysis")`
- L18 _public member_ `float PeakReleaseTimeSeconds = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AudioAnalysis")`
- L21 _public member_ `bool bEnableValueSmoothing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AudioAnalysis")`
- L24 _public member_ `float ValueAttackTimeSeconds = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AudioAnalysis")`
- L27 _public member_ `float ValueReleaseTimeSeconds = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AudioAnalysis")`

#### class `Harmonix::AudioReactivity::FPeakTamer`  
`class FPeakTamer final`  
_L42-57_
- desc: Takes a raw peak value from an audio analyzer and outputs a smoothed, compressed value in range [0, 1]
- L45 _public prototype_ `void Configure(const FHarmonixPeakTamerSettings& InSettings);`
- L47 _public prototype_ `void Update(float InputValue, float DeltaTimeSeconds);`
- L49 _public function_ `float GetPeak() const`
- L51 _public function_ `float GetValue() const`
- L54 _private member_ `FHarmonixPeakTamerSettings Settings{};`
- L55 _private member_ `float Peak{ 0.0f };`
- L56 _private member_ `float Value{ 0.0f };`

#### class `UHarmonixPeakTamer`  
`class UHarmonixPeakTamer final : public UObject`  
_L64-86_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Takes a raw peak value from an audio analyzer and outputs a smoothed, compressed value in range [0, 1]
- L70 _public prototype_ `static UHarmonixPeakTamer* CreateHarmonixPeakTamer();` — `UFUNCTION(BlueprintCallable, Category="AudioAnalysis")`
- L73 _public prototype_ `void Configure(const FHarmonixPeakTamerSettings& Settings);` — `UFUNCTION(BlueprintCallable, Category="AudioAnalysis")`
- L76 _public prototype_ `void Update(float InputValue, float DeltaTimeSeconds);` — `UFUNCTION(BlueprintCallable, Category="AudioAnalysis")`
- L79 _public prototype_ `float GetPeak() const;` — `UFUNCTION(BlueprintCallable, Category="AudioAnalysis")`
- L82 _public prototype_ `float GetValue() const;` — `UFUNCTION(BlueprintCallable, Category="AudioAnalysis")`
- L85 _private member_ `Harmonix::AudioReactivity::FPeakTamer PeakTamer;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L30 _namespace_ `namespace Harmonix`
- L30 _namespace_ `namespace AudioReactivity` (scope `Harmonix`)
- L32 _namespace_ `namespace PeakTamerPrivate` (scope `Harmonix::AudioReactivity`)
- L36 _prototype_ `float SmoothValue(float X0, float Y1, float DeltaTime, float SmoothTime);` (scope `Harmonix::AudioReactivity::PeakTamerPrivate`) — Smooth a value given a delta time, a smoothing time, and the last value. This is pretty much a one-pole lowpass filter.

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Analysis/SpmcAnalysisResultQueue.h` (Public)


#### class `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue`  
`template <typename T> class FSpmcAnalysisResultQueue`  
_L12-414_
- L23 _public typedef_ `using ItemType = T;`
- L346 _public function_ `FSpmcAnalysisResultQueue()`
- L348 _public function_ `FSpmcAnalysisResultQueue(int32 InitialItemCount)`
- L353 _public function_ `void SetNumItems(int32 NumItems)`
- L357 _public function_ `int32 NumItems() const`
- L359 _public function_ `int32 GetNextWriteIndex() const`
- L360 _public function_ `int32 GetLastWriteIndex() const`
- L370 _public function_ `const FEntry* GetEntry(int32 Index) const`
- L376 _public function_ `SIZE_T GetAllocatedSize() const`
- L381 _public function_ `FScopedItemWriteRef GetNextAtomicWriteSlot()`
- L386 _public function_ `void IncrementIndex(int32& Index, int32 NumberAhead = 1) const`
- L395 _public function_ `void DecrementIndex(int32& Index) const`
- L404 _public function_ `const FEntry& operator[](int32 Index)`
- L411 _private member_ `int32 NextItemSerialNumber{ 0 };`
- L412 _private member_ `int32 NextWritePos{ 0 };`
- L413 _private member_ `TArray<FEntry> Items;`

#### struct `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue::FEntry`  
`struct FEntry`  
_L15-20_
- L17 _public member_ `int32 SerialNumber{ -1 };`
- L18 _public member_ `mutable std::atomic_flag Locked = ATOMIC_FLAG_INIT;`
- L19 _public member_ `T Item;`

#### class `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue::FReadCursor`  
`class FReadCursor`  
_L30-114_
- L33 _public function_ `FReadCursor() : Queue(nullptr) , NextReadIndex(0)`
- L40 _public function_ `FReadCursor(FSpmcAnalysisResultQueue& InQueue) : Queue(&InQueue) , NextReadIndex(InQueue.GetNextWriteIndex())`
- L47 _public function_ `FScopedItemConsumeRef ConsumeNext()`
- L56 _public function_ `FScopedItemPeekRef PeekNext()`
- L66 _public function_ `FScopedItemPeekRef PeekAhead(int32 NumberAhead)`
- L78 _public function_ `void PeekAhead(int32 NumberAhead, FScopedItemPeekRef& Target)`
- L91 _public function_ `bool DataAvailable() const`
- L96 _public function_ `int32 NumDataAvailable() const`
- L111 _public member_ `const FSpmcAnalysisResultQueue* Queue;`
- L112 _public member_ `int32 NextReadIndex{ 0 };`
- L113 _public member_ `int32 NextExpectedSerialNumber{ -1 };`

#### class `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue::FScopedItemConsumeRef`  
`class FScopedItemConsumeRef`  
_L116-191_
- L119 _public function_ `FScopedItemConsumeRef() : Entry(nullptr) , ReadCursor(nullptr)`
- L125 _public function_ `FScopedItemConsumeRef(const FEntry* InEntry, FReadCursor* InReadCursor) : Entry(InEntry) , ReadCursor(InReadCursor)`
- L153 _public prototype_ `FScopedItemConsumeRef(const FScopedItemConsumeRef& Other) = delete;`
- L154 _public function_ `FScopedItemConsumeRef(FScopedItemConsumeRef&& Other) : DiscontinuityDetectedInLastRead(Other.DiscontinuityDetectedInLastRead) , Entry(Other.Entry) , ReadCursor(Other.ReadCursor)`
- L161 _public prototype_ `FScopedItemConsumeRef& operator=(const FScopedItemConsumeRef& Other) = delete;`
- L163 _public function_ `~FScopedItemConsumeRef()`
- L172 _public function_ `const T* operator->()`
- L177 _public function_ `const T& operator*()`
- L183 _public function_ `operator bool() const`
- L188 _public member_ `bool DiscontinuityDetectedInLastRead{ false };`
- L189 _public member_ `const FEntry* Entry;`
- L190 _public member_ `FReadCursor* ReadCursor;`

#### class `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue::FScopedItemPeekRef`  
`class FScopedItemPeekRef`  
_L193-309_
- L196 _public function_ `FScopedItemPeekRef() : Entry(nullptr) , ReadCursor(nullptr)`
- L201 _public function_ `FScopedItemPeekRef(const FEntry* InEntry, FReadCursor* InReadCursor) : Entry(InEntry) , ReadCursor(InReadCursor)`
- L223 _public prototype_ `FScopedItemPeekRef(const FScopedItemConsumeRef& Other) = delete;`
- L224 _public function_ `FScopedItemPeekRef(FScopedItemPeekRef&& Other) : DiscontinuityDetectedInLastRead(Other.DiscontinuityDetectedInLastRead) , Entry(Other.Entry) , ReadCursor(Other.ReadCursor)`
- L231 _public prototype_ `FScopedItemPeekRef& operator=(const FScopedItemConsumeRef& Other) = delete;`
- L232 _public function_ `FScopedItemPeekRef& operator=(FScopedItemConsumeRef&& Other)`
- L240 _public function_ `void Release()`
- L251 _public function_ `void ConnectTo(const FEntry* InEntry, FReadCursor* InReadCursor)`
- L271 _public function_ `~FScopedItemPeekRef()`
- L280 _public function_ `const T* operator->()`
- L285 _public function_ `const T& operator*()`
- L291 _public function_ `operator bool() const`
- L296 _public function_ `bool operator==(const FEntry& Other)`
- L301 _public function_ `bool operator!=(const FEntry& Other)`
- L306 _public member_ `bool DiscontinuityDetectedInLastRead{ false };`
- L307 _public member_ `const FEntry* Entry;`
- L308 _public member_ `FReadCursor* ReadCursor;`

#### class `HarmonixMetasound::Analysis::FSpmcAnalysisResultQueue::FScopedItemWriteRef`  
`class FScopedItemWriteRef`  
_L311-344_
- L314 _public prototype_ `FScopedItemWriteRef() = delete;`
- L315 _public function_ `FScopedItemWriteRef(FEntry& InEntry, FSpmcAnalysisResultQueue& InQueue) : Entry(InEntry) , Queue(InQueue)`
- L323 _public function_ `~FScopedItemWriteRef()`
- L331 _public function_ `T* operator->()`
- L336 _public function_ `T& operator*()`
- L342 _private member_ `FEntry& Entry;`
- L343 _private member_ `FSpmcAnalysisResultQueue& Queue;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Common.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HarmonixMetasound`
- L13 _externvar_ `extern const FName HarmonixNodeNamespace;` (scope `HarmonixMetasound`)
- L15 _namespace_ `namespace MetasoundNodeCategories` (scope `HarmonixMetasound`)
- L17 _externvar_ `extern const FText Harmonix;` (scope `HarmonixMetasound::MetasoundNodeCategories`)
- L18 _externvar_ `extern const FText Modulation;` (scope `HarmonixMetasound::MetasoundNodeCategories`)
- L19 _externvar_ `extern const FText Analysis;` (scope `HarmonixMetasound::MetasoundNodeCategories`)
- L24 _macro_ `#define DECLARE_METASOUND_PARAM_EXTERN(NAME) \`
- L29 _macro_ `#define DECLARE_METASOUND_PARAM_ALIAS(NAME) \`
- L34 _macro_ `#define DEFINE_INPUT_METASOUND_PARAM(NAME, NAME_TEXT, TOOLTIP_TEXT) \`
- L38 _macro_ `#define DEFINE_OUTPUT_METASOUND_PARAM(NAME, NAME_TEXT, TOOLTIP_TEXT) \`
- L44 _macro_ `#define DEFINE_METASOUND_PARAM_ALIAS(ALIAS_NAME, TARGET_NAME) \` — Alias an existing param definition. Helpful for re-using definitions while providing a public node API.
- L68 _namespace_ `namespace CommonPinNames` (scope `HarmonixMetasound`)
- L70 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::CommonPinNames`)
- L73 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MidiStream) DECLARE_METASOUND_PARAM_EXTERN(MidiChannelNumber) DECLARE_METASOUND_PARAM_EXTERN(MidiChannelFilterSpecifier) DECLARE_METASOUND_PARAM_EXTERN(MidiTrackNumber) DECLARE_METASOUND_PARAM_EXTERN(MidiTrackIndexFilterSpecifier) DECLARE_METASOUND_PARAM_EXTERN(MinMidiNote) DECLARE_METASOUND_PARAM_EXTERN(MaxMidiNote) DECLARE_METASOUND_PARAM_EXTERN(MinMidiVelocity) DECLARE_METASOUND_PARAM_EXTERN(MaxMidiVelocity) DECLARE_METASOUND_PARAM_EXTERN(MidiFileAsset) DECLARE_METASOUND_PARAM_EXTERN(Transport) DECLARE_METASOUND_PARAM_EXTERN(MidiClock) DECLARE_METASOUND_PARAM_EXTERN(Tempo) DECLARE_METASOUND_PARAM_EXTERN(TimeSigNumerator) DECLARE_METASOUND_PARAM_EXTERN(TimeSigDenominator) DECLARE_METASOUND_PARAM_EXTERN(Speed) DECLARE_METASOUND_PARAM_EXTERN(Loop) DECLARE_METASOUND_PARAM_EXTERN(LoopLengthBars) DECLARE_METASOUND_PARAM_EXTERN(TransportPrepare) DECLARE_METASOUND_PARAM_EXTERN(TransportPlay) DECLARE_METASOUND_PARAM_EXTERN(TransportPause) DECLARE_METASOUND_PARAM_EXTERN(TransportContinue) DECLARE_METASOUND_PARAM_EXTERN(TransportStop) DECLARE_METASOUND_PARAM_EXTERN(TransportKill) DECLARE_METASOUND_PARAM_EXTERN(TriggerSeek) DECLARE_METASOUND_PARAM_EXTERN(SeekDestination) DECLARE_METASOUND_PARAM_EXTERN(PrerollBars) DECLARE_METASOUND_PARAM_EXTERN(GridSizeUnits) DECLARE_METASOUND_PARAM_EXTERN(GridSizeMult) DECLARE_METASOUND_PARAM_EXTERN(OffsetUnits) DECLARE_METASOUND_PARAM_EXTERN(OffsetMult) DECLARE_METASOUND_PARAM_EXTERN(Bar) DECLARE_METASOUND_PARAM_EXTERN ...` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L111 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFOFrequency);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L112 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFOInvert);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L113 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFOShape);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L114 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AudioMono);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L115 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AudioLeft);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L116 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AudioRight);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L118 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AudioLFE) DECLARE_METASOUND_PARAM_EXTERN(AudioLeftBack) DECLARE_METASOUND_PARAM_EXTERN(AudioRightBack) DECLARE_METASOUND_PARAM_EXTERN(AudioLeftSide) DECLARE_METASOUND_PARAM_EXTERN(AudioRightSide) DECLARE_METASOUND_PARAM_EXTERN(Timestamp);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L124 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(ShouldQuantizeTimestamp);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L125 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(QuantizationUnit);` (scope `HarmonixMetasound::CommonPinNames::Inputs`)
- L127 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::CommonPinNames`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MetasoundOfflinePlayerComponent.h` (Public)


#### class `UMetasoundOfflinePlayerComponent`  
`class UMetasoundOfflinePlayerComponent : public UActorComponent`  
_L19-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent`
- L24 _public prototype_ `UMetasoundOfflinePlayerComponent();`
- L27 _public prototype_ `UMetasoundGeneratorHandle* CreateGeneratorBasedOnAudioComponent(UAudioComponent* AudioComponent, int32 InSampleRate = 12000, int32 InBlockSize = 256);` — To deprecate, only required to keep engine-only integrated backends happy
- L29 _public prototype_ `TSharedPtr<Metasound::FMetasoundGeneratorHandle> CreateSharedGeneratorBasedOnAudioComponent(UAudioComponent* AudioComponent, int32 InSampleRate = 12000, int32 InBlockSize = 256);`
- L30 _public prototype_ `void ReleaseGenerator();`
- L32 _public prototype_ `virtual void BeginPlay() override;`
- L33 _public prototype_ `virtual void BeginDestroy() override;`
- L35 _public prototype_ `TSharedPtr<Metasound::FMetasoundGenerator> GetGenerator();`
- L38 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L41 _private member_ `ISoundGeneratorPtr Generator;`
- L44 _private member_ `TObjectPtr<UMetaSoundSource> MetasoundSource;` — `UPROPERTY(Transient)`
- L46 _private member_ `int32 SampleRate;`
- L47 _private member_ `int32 BlockSize;`
- L48 _private member_ `int32 GeneratorBlockSize;`
- L50 _private member_ `double StartSecond = 0.0;`
- L51 _private member_ `int64 RenderedSamples = 0;`
- L52 _private member_ `TArray<float> ScratchBuffer;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L11 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicClockComponent.h` (Public)


#### enum `EMusicClockDriveMethod`  
`enum class EMusicClockDriveMethod : uint8`  
_L28-33_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `WallClock`
- L31 _public enumerator_ `MetaSound`
- L32 _public enumerator_ `Custom`

#### enum `EMusicTimeDiscontinuityType`  
`enum class EMusicTimeDiscontinuityType : uint8`  
_L36-40_
- reflection: `UENUM(BlueprintType)`
- L38 _public enumerator_ `Loop`
- L39 _public enumerator_ `Seek`

#### class `UMusicClockComponent`  
`class UMusicClockComponent : public UActorComponent, public IMusicEnvironmentClockSource`  
_L52-591_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (MetaSoundMusic), PrioritizeCategories = "MusicClock", meta = (BlueprintSpawnableComponent, DisplayName = "Music Clock", ScriptName = MusicClockComponent))`
- inherits: `UActorComponent,IMusicEnvironmentClockSource`
- L58 _public prototype_ `UMusicClockComponent();` — Sets default values for this component's properties
- L66 _public prototype_ `void Activate(bool bReset) override;` — Start this clock ticking and start tracking music time Same as "Start()" Setting bReset to true will restart (trigger "Stop" and then "Start") the clock is already Running
- L72 _public prototype_ `void Deactivate() override;` — Stop this clock ticking and stop tracking music time Same as "Stop()"
- L74 _public prototype_ `void BeginPlay() override;`
- L75 _public prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L76 _public prototype_ `void BeginDestroy() override;`
- L79 _public member_ `EMusicClockDriveMethod DriveMethod = EMusicClockDriveMethod::MetaSound;` — `UPROPERTY(EditAnywhere, Category = "MusicClock")`
- L82 _public member_ `FName MetasoundOutputName = "MI` — `UPROPERTY(EditAnywhere, Category = "MusicClock", meta = (EditCondition = "DriveMethod == EMusicClockDriveMethod::MetaSound", EditConditionHides))`
- L85 _public member_ `TObjectPtr<UAudioComponent> MetasoundsAudioComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MusicClock", meta = (EditCondition = "DriveMethod == EMusicClockDriveMethod::MetaSound", EditConditionHides))`
- L88 _public member_ `TObjectPtr<UMidiFile> TempoMap;` — `UPROPERTY(EditAnywhere, Category = "MusicClock", meta = (EditCondition = "DriveMethod == EMusicClockDriveMethod::WallClock", EditConditionHides))`
- L91 _public member_ `TInstancedStruct<FMusicClockSettingsBase> MusicClockSettings = TInstancedStruct<FMetasoundMusicClockSettings>::Make();` — `UPROPERTY(EditAnywhere, Category = "MusicClock", NoClear, meta = (EditCondition = "DriveMethod == EMusicClockDriveMethod::Custom"))`
- L98 _public prototype_ `void Start();` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Start the clock ticking and tracking music time Same as "Activate"
- L104 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Pause the clock at the current running time
- L110 _public prototype_ `void Continue();` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Continue the clock from paused
- L117 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Stop this clock ticking and no longer track music time Same as "Deactivate"
- L127 _public prototype_ `float GetCurrentTempo() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Tempo of the running clock 0 if the clock is stopped This is Midi Tempo, which is QuarterNotesPerMinute. This does not consider the advance rate, if you want that, use GetBeats|BarsPerSecond.
- L137 _public prototype_ `float GetCurrentBeatsPerMinute() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current BPM of the running clock 0 if the clock is stopped This is in units of our Beats, not Quarter notes. This does not consider the advance rate, if you want that, use GetBeats|BarsPerSecond.
- L145 _public prototype_ `void GetCurrentTimeSignature(int& OutNumerator, int& OutDenominator) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Time Signature 0 if the clock is stopped
- L153 _public prototype_ `FTimeSignature GetCurrentTimeSignatureStruct() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Time Signature 0 if the clock is stopped
- L162 _public prototype_ `float GetCurrentBarsPerSecond() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Bars per Second. Based on the current tempo, advance rate and time signature 0 if the clock is stopped.
- L173 _public prototype_ `float GetCurrentSecondsPerBar() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Seconds per Bar Based on the current tempo, advance rate and time signature 0 if the clock is stopped Don't use this method, use GetCurrentBarsPerSecond instead if possible because this method returns zero when the clock is stopped rather than inf, which is what it should be.
- L182 _public prototype_ `float GetCurrentBeatsPerSecond() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Beats per Second. Based on the current tempo, advance rate and time signature 0 if the clock is stopped.
- L193 _public prototype_ `float GetCurrentSecondsPerBeat() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Seconds per Beat Based on the current tempo, advance rate and time signature 0 if the clock is stopped. Don't use this method, use GetCurrentBeatsPerSecond instead if possible because this method returns zero when the clock is stopped rather than inf, which is what it should be.
- L201 _public prototype_ `float GetCurrentClockAdvanceRate() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get The Current Clock advance rate 0 if the clock is stopped
- L204 _public prototype_ `EMusicClockState GetState() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L208 _public prototype_ `void SetTempoMapForWallClock(UMidiFile* InTempoMap);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Set the tempo map when running off of wall clock
- L211 _public prototype_ `void SetRunPastMusicEnd(bool bRunPastMusicEnd);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")`
- L214 _public prototype_ `bool GetRunPastMusicEnd() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L221 _public prototype_ `float GetSecondsIncludingCountIn(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Time from the beginning of the authored music content. NOTE: INCLUDES time for count-in and pickup bars.
- L226 _public prototype_ `float GetSecondsFromBarOne(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Time from Bar 1 Beat 1. The classic "start of the song". NOTE: DOES NOT INCLUDE time for count-in and pickup bars.
- L231 _public prototype_ `float GetBarsIncludingCountIn(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the fractional total bars from the beginning of the authored music content. NOTE: INCLUDES time for count-in and pickup bars.
- L236 _public prototype_ `float GetBeatsIncludingCountIn(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the fractional total beats from the beginning of the authored music content. NOTE: INCLUDES time for count-in and pickup bars.
- L241 _public prototype_ `float GetTicksFromBarOne(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — NOTE: Working in ticks is a little risky. Midi files have have different numbers of ticks per quarter note, Ticks change duration with tempo changes, etc. So we don't expose ticks to blueprints and recommend using them in c++ code. That said, sometimes there is a use for them... so...
- L242 _public prototype_ `float GetTicksIncludingCountIn(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;`
- L249 _public prototype_ `FMusicTimestamp GetCurrentTimestamp(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the "classic" musical timestamp in the form Bar (int) & Beat (float). In this form... - Bar 1, Beat 1.0 is the "beginning of the song" AFTER count-in/pickups - Bar 0, Beat 1.0 would be one bar BEFORE the "beginning of the song"... eg. a bar of count-in or pickup. - While Bar can be positive or negative, Beat is always >= 1.0 and is read as "beat in the bar". Again... '1' based!
- L253 _public prototype_ `FString GetCurrentSectionName(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the name of the section that we're currently in (intro, chorus, outro)
- L257 _public prototype_ `int32 GetCurrentSectionIndex(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the index of the current section for the provided time base. [0, Num-1]
- L260 _public prototype_ `const TArray<FSongSection>& GetSongSections() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L264 _public prototype_ `float GetCurrentSectionStartMs(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the start time of the current section in milliseconds
- L268 _public prototype_ `float GetCurrentSectionLengthMs(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the length of the current section in milliseconds
- L272 _public prototype_ `float GetDistanceFromCurrentBeat(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets a value expressed in beats between 0-1 that indicates how much progress we made in the current beat
- L276 _public prototype_ `float GetDistanceToNextBeat(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets a value expressed in beats between 0-1 that indicates how close we are to the next beat.
- L280 _public prototype_ `float GetDistanceToClosestBeat(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets a value expressed in beats between 0-1 that indicates how close we are to the closest beat (current beat or next beat).
- L284 _public prototype_ `float GetDistanceFromCurrentBar(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets a value expressed in bars between 0-1 that indicates how much progress we made towards the current bar to the next one.
- L288 _public prototype_ `float GetDistanceToNextBar(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets a value expressed in bars between 0-1 that indicates how close we are to the next bar.
- L292 _public prototype_ `float GetDistanceToClosestBar(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Gets value expressed in bars between 0-1 that indicates how close we are to the closest bar (current bar or next bar).
- L295 _public prototype_ `float GetDeltaBar(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L298 _public prototype_ `float GetDeltaBeat(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L301 _public prototype_ `const FMidiSongPos& GetSongPos(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L304 _public prototype_ `const FMidiSongPos& GetPreviousSongPos(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L308 _public prototype_ `float GetSongRemainingMs(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns the remaining time until the end of the MIDI in milliseconds based on the timestamp corresponding to the passed Timebase
- L312 _public prototype_ `bool SeekedThisFrame(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns true if there was a seek in the specified timebase
- L316 _public prototype_ `bool LoopedThisFrame(ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Returns true if there was a seek in the specified timebase
- L319 _public prototype_ `TOptional<FVector> TryGetAudioSourceLocation() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L322 _public prototype_ `float GetCountInSeconds() const;` — `UFUNCTION(BlueprintPure, Category = "Count In")`
- L325 _public prototype_ `float TickToMs(float Tick) const;` — `UFUNCTION(BlueprintPure, Category = "Tick")`
- L329 _public prototype_ `float BeatToMs(float Beat) const;` — `UFUNCTION(BlueprintPure, Category = "Beat")` — Convert zero indexed fractional beat to Ms
- L333 _public prototype_ `float MsToBeat(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Beat")` — Convert Ms to zero indexed fractional beat
- L336 _public prototype_ `float GetMsPerBeatAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Beat")`
- L339 _public prototype_ `float GetNumBeatsInBarAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Beat")`
- L342 _public prototype_ `float GetBeatInBarAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Beat")`
- L345 _public prototype_ `float BarToMs(float Bar) const;` — `UFUNCTION(BlueprintPure, Category = "Bar")`
- L348 _public prototype_ `float GetMsPerBarAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Bar")`
- L351 _public prototype_ `FString GetSectionNameAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L354 _public prototype_ `float GetSectionLengthMsAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L357 _public prototype_ `float GetSectionStartMsAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L360 _public prototype_ `float GetSectionEndMsAtMs(float Ms) const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L363 _public prototype_ `int32 GetNumSections() const;` — `UFUNCTION(BlueprintPure, Category = "Section")`
- L366 _public prototype_ `float GetSongLengthMs() const;` — `UFUNCTION(BlueprintPure, Category = "Song Data")`
- L369 _public prototype_ `float GetSongLengthBeats() const;` — `UFUNCTION(BlueprintPure, Category = "Song Data")`
- L372 _public prototype_ `float GetSongLengthBars() const;` — `UFUNCTION(BlueprintPure, Category = "Song Data")`
- L374 _public prototype_ `const ISongMapEvaluator& GetSongMaps() const;`
- L387 _public prototype_ `FMusicTimerHandle BP_AddTimer(const FMusicTimeInterval& TimerInterval, TOptional<FMusicTimestamp> StartTime, ECalibratedMusicTimebase Timebase, bool bLooping, FOnMusicalTimerExecute TimerDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")` — Adds a musical timer. @param TimerInterval  Interval configuration for the timer. @param StartTime      Optional start time. If unset, the current musical time (floored) is used. @param Timebase       Timebase used to evaluate the timer. @param bLooping       Whether the timer should loop. @param TimerDelegate  Delegate executed when the timer fires.
- L399 _public prototype_ `FMusicTimerHandle AddTimerNative(const FMusicTimeInterval& TimerInterval, TOptional<FMusicTimestamp> StartTime, ECalibratedMusicTimebase Timebase, bool bLooping, FSimpleDelegate TimerDelegate);` — Adds a musical timer. @param TimerInterval  Interval configuration for the timer. @param StartTime      Optional start time. If unset, the current musical time (floored) is used. @param Timebase       Timebase used to evaluate the timer. @param bLooping       Whether the timer should loop. @param TimerDelegate  Delegate executed when the timer fires.
- L402 _public prototype_ `void RemoveTimer(const FMusicTimerHandle& Handle);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L405 _public prototype_ `void PauseTimer(const FMusicTimerHandle& Handle, bool bPause);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L408 _public prototype_ `FMusicTimestamp Quantize(const FMusicTimestamp& Time, EMidiClockSubdivisionQuantization QuantizationInterval, EMidiFileQuantizeDirection InDirection) const;` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L412 _public prototype_ `FString GetDisplayName() const;` — A short string description of the clock, for debugging, like song name or animation name or whatever is driving it.
- L415 _public prototype_ `void SetDisplayName(FString Name);` — Sets the DisplayName. Will be used by GetDisplayName if set, otherwise falls back to drivers.
- L419 _public member_ `ECalibratedMusicTimebase TimebaseForBarAndBeatEvents = ECalibratedMusicTimebase::VideoRenderTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicClock")`
- L422 _public member_ `FPlayStateEvent PlayStateEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L425 _public member_ `FBeatEvent BeatEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L428 _public member_ `FBarEvent BarEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L431 _public member_ `FSectionEvent SectionEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L434 _public member_ `FMusicClockConnected MusicClockConnectedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L437 _public member_ `FMusicClockDisconnected MusicClockDisconnectedEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L440 _public member_ `FMusicTimeDiscontinuityEvent AudioRenderMusicTimeDiscontinuityEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L443 _public member_ `FMusicTimeDiscontinuityEvent PlayerExperienceMusicTimeDiscontinuityEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L446 _public member_ `FMusicTimeDiscontinuityEvent VideoRenderMusicTimeDiscontinuityEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L449 _public prototype_ `void SetDefaultTempo(float TempoBpm);` — Set the default tempo, only call when there's no tempo map.
- L451 _public prototype_ `void SetDefaultTimeSignatureNum(int Num);` — Set the default time signature numerator, only call when there's no tempo map.
- L453 _public prototype_ `void SetDefaultTimeSignatureDenom(int Denom);` — Set the default time signature denominator, only call when there's no tempo map.
- L464 _protected member_ `float DefaultTempo = 120.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicClock|Defaults")` — Default Tempo (BPM) used for Wall clock with no tempo map NOT THE CURRENT RUNNING TEMPO
- L473 _protected member_ `int DefaultTimeSignatureNum = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicClock|Defaults")` — Default Time Signature (Numerator) used for the Wall Clock with no tempo map NOT THE CURRENT RUNNING TIME SIG
- L482 _protected member_ `int DefaultTimeSignatureDenom = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicClock|Defaults")` — Default Time Signature (Denominator) used for the Wall clock with no tempo map NOT THE CURRENT RUNNING TIME SIG
- L485 _protected member_ `bool RunPastMusicEnd = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicClock")`
- L490 _public prototype_ `FMidiSongPos GetCurrentSmoothedAudioRenderSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")` — Getter functions for the Blueprint properties exposed above...
- L493 _public prototype_ `FMidiSongPos GetPreviousSmoothedAudioRenderSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L496 _public prototype_ `FMidiSongPos GetCurrentVideoRenderSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L499 _public prototype_ `FMidiSongPos GetPreviousVideoRenderSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L502 _public prototype_ `FMidiSongPos GetCurrentPlayerExperiencedSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L505 _public prototype_ `FMidiSongPos GetPreviousPlayerExperiencedSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L508 _public prototype_ `FMidiSongPos GetCurrentRawAudioRenderSongPos() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MusicClock")`
- L511 _public prototype_ `float MeasureSpanProgress(const FMusicalTimeSpan& Span, ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L514 _public prototype_ `static UMusicClockComponent* CreateMetasoundDrivenMusicClock(UObject* WorldContextObject, UAudioComponent* InAudioComponent, FName MetasoundOuputPinName = "MIDI Clock", bool Start = true, bool bPersistAcrossLevelTransition` — `UFUNCTION(BlueprintCallable, Category = "Audio|MusicClock", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L517 _public prototype_ `static UMusicClockComponent* CreateWallClockDrivenMusicClock(UObject* WorldContextObject, UMidiFile* WithTempoMap, bool Start = true, bool bPersistAcrossLevelTransition = false);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MusicClock", meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))`
- L519 _public prototype_ `static UMusicClockComponent* CreateMusicClockWithSettings(UObject* WorldContextObject, TInstancedStruct<FMusicClockSettingsBase> MusicClockSettings, bool Start = true, bool bPersistAcrossLevelTransition = false);`
- L522 _public function_ `template<typename MusicClockSettingsType = FMusicClockSettingsBase> static UMusicClockComponent* CreateMusicClockWithSettings(UObject* WorldContextObject, const MusicClockSettingsType& InMusicClockSettings, bool Start = true, bool bPersistAcrossLevelTransition = false)`
- L528 _public prototype_ `bool ConnectToMetasoundOnAudioComponent(UAudioComponent* InAudioComponent);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")`
- L531 _public prototype_ `void ConnectToWallClockForMidi(UMidiFile* InTempoMap);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")`
- L534 _public prototype_ `void ConnectToCustomClockWithSettings(TInstancedStruct<FMusicClockSettingsBase> InMusicClockSettings);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")`
- L537 _public function_ `template<typename MusicClockSettingsType = FMusicClockSettingsBase> void ConnectToCustomClockWithSettings(const MusicClockSettingsType& InMusicClockSettings)`
- L542 _public prototype_ `FMidiSongPos CalculateSongPosWithOffset(float MsOffset, ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime) const;`
- L544 _public prototype_ `const FMidiSongPos& GetRawUnsmoothedAudioRenderPos() const;`
- L547 _public prototype_ `virtual float GetPositionSeconds() const override;` — vvv BEGIN  IMusicEnvironmentClockSource Implementation vvv
- L548 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime() const override;`
- L549 _public prototype_ `virtual FMusicalTime GetPositionMusicalTime(const FMusicalTime& SourceSpaceOOffset) const override;`
- L550 _public prototype_ `virtual int32 GetPositionAbsoluteTick() const override;`
- L551 _public prototype_ `virtual int32 GetPositionAbsoluteTick(const FMusicalTime& SourceSpaceOffset) const override;`
- L552 _public prototype_ `virtual FMusicalTime Quantize(const FMusicalTime& MusicalTime, int32 QuantizationInterval, UFrameBasedMusicMap::EQuantizeDirection Direction = UFrameBasedMusicMap::EQuantizeDirection::Nearest) const;`
- L553 _public function_ `virtual bool CanAuditionInEditor() const override`
- L556 _public function_ `bool HasValidClockDriver() const`
- L561 _private member_ `TSharedPtr<FMusicClockDriverBase> ClockDriver;`
- L563 _private member_ `FSongMaps DefaultMaps;`
- L565 _private member_ `int32 LastBroadcastBar = -1;`
- L566 _private member_ `int32 LastBroadcastBeat = -1;`
- L567 _private member_ `FSongSection LastBroadcastSongSection;`
- L570 _private member_ `FString DisplayName;` — Holds a name for display, ideally shows the original source for the clock.
- L574 _private member_ `TObjectPtr<UMusicTimerManager> MusicTimerManager;` — `UPROPERTY(Transient)`
- L576 _private prototype_ `static TNotNull<UMusicClockComponent*> CreateMusicClockShared(UObject* WorldContextObject, bool bPersistAcrossLevelTransition);`
- L578 _private prototype_ `void CreateClockDriver();`
- L579 _private prototype_ `void BroadcastSongPosChanges(ECalibratedMusicTimebase Timebase);`
- L580 _private prototype_ `void BroadcastSeekLoopDetections(ECalibratedMusicTimebase Timebase) const;`
- L581 _private prototype_ `const FMusicTimeDiscontinuityEvent* GetMusicTimeDiscontinuityEventInternal(ECalibratedMusicTimebase Timebase) const;`
- L582 _private prototype_ `void MakeDefaultSongMap();`
- L583 _private prototype_ `bool ConnectToMetasound();`
- L584 _private prototype_ `void ConnectToWallClock();`
- L585 _private prototype_ `void ConnectToCustomClock();`
- L586 _private prototype_ `void DisconnectFromClockDriver();`
- L588 _private prototype_ `void UpdateClock();`
- L589 _private prototype_ `const FMidiSongPos& GetCurrentSongPosInternal(ECalibratedMusicTimebase Timebase) const;`
- L590 _private prototype_ `const FMidiSongPos& GetPreviousSongPosInternal(ECalibratedMusicTimebase Timebase) const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicClock, Log, All) namespace Metasound { class FMetasoundGenerator; } struct FMusicalTimeSpan;`
- L21 _namespace_ `namespace Metasound`
- L42 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBeatEvent, int, BeatNumber, int, BeatInBar);`
- L42 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBeatEvent, int, BeatNumber, int, BeatInBar);`
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBarEvent, int, BarNumber);`
- L43 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBarEvent, int, BarNumber);`
- L44 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSectionEvent, const FString&, SectionName, float, SectionStartMs, float, SectionLengthMs);`
- L44 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSectionEvent, const FString&, SectionName, float, SectionStartMs, float, SectionLengthMs);`
- L45 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayStateEvent, EMusicClockState, State);`
- L45 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayStateEvent, EMusicClockState, State);`
- L46 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMusicTimeDiscontinuityEvent, EMusicTimeDiscontinuityType, Type, FMidiSongPos, PreviousPos, FMidiSongPos, NewPos);`
- L46 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMusicTimeDiscontinuityEvent, EMusicTimeDiscontinuityType, Type, FMidiSongPos, PreviousPos, FMidiSongPos, NewPos);`
- L48 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMusicClockConnected);`
- L48 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMusicClockConnected);`
- L49 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMusicClockDisconnected);`
- L49 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMusicClockDisconnected);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicClockDriverBase.h` (Public)


#### class `FMusicClockDriverBase`  
`class FMusicClockDriverBase : public TSharedFromThis<FMusicClockDriverBase>`  
_L15-104_
- inherits: `TSharedFromThis<FMusicClockDriverBase>`
- L18 _public prototype_ `FMusicClockDriverBase(UObject* WorldContextObject, const FMusicClockSettingsBase& Settings);`
- L19 _public prototype_ `virtual ~FMusicClockDriverBase();`
- L21 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const = 0;`
- L23 _public prototype_ `void UpdateClockForGameFrame();`
- L25 _public prototype_ `virtual bool CalculateSongPosWithOffset(float MsOffset, ECalibratedMusicTimebase Timebase, FMidiSongPos& OutResult) const;`
- L27 _public prototype_ `double GetWallClockTime() const;`
- L29 _public function_ `EMusicClockState GetState() const`
- L30 _public prototype_ `const FMidiSongPos& GetCurrentSongPos(ECalibratedMusicTimebase Timebase) const;`
- L31 _public prototype_ `const FMidiSongPos& GetPreviousSongPos(ECalibratedMusicTimebase Timebase) const;`
- L32 _public prototype_ `float GetDeltaBarF(ECalibratedMusicTimebase Timebase) const;`
- L33 _public prototype_ `float GetDeltaBeatF(ECalibratedMusicTimebase Timebase) const;`
- L35 _public function_ `const FMidiSongPos& GetCurrentSmoothedAudioRenderSongPos() const`
- L36 _public function_ `const FMidiSongPos& GetCurrentPlayerExperiencedSongPos() const`
- L37 _public function_ `const FMidiSongPos& GetCurrentVideoRenderSongPos() const`
- L38 _public function_ `const FMidiSongPos& GetCurrentRawAudioRenderSongPos() const`
- L40 _public prototype_ `void Start();`
- L41 _public prototype_ `void Pause();`
- L42 _public prototype_ `void Continue();`
- L43 _public prototype_ `void Stop();`
- L45 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const = 0;`
- L47 _public prototype_ `virtual bool LoopedThisFrame(ECalibratedMusicTimebase Timebase) const = 0;`
- L48 _public prototype_ `virtual bool SeekedThisFrame(ECalibratedMusicTimebase Timebase) const = 0;`
- L50 _public prototype_ `virtual void Disconnect() = 0;`
- L52 _public prototype_ `void UpdateMusicPlaybackRate(float InTempo, float InClockAdvanceRate, int32 InTimeSigNum, int32 InTimeSigDenom);`
- L55 _public prototype_ `float GetBeatsPerMinute() const;` — This returns our BeatsPerMinute which is our true beats, not quarter notes.
- L59 _public prototype_ `virtual FString GetDisplayName() const = 0;` — Short user readable description good for logging. Should include name of song or sound source or whatnot.
- L62 _public member_ `FSongMaps DefaultMaps;`
- L65 _public member_ `float Tempo = 0.0f;` — Note that tempo is MidiTempo, quarter notes per minute.
- L66 _public member_ `int TimeSignatureNum = 0;`
- L67 _public member_ `int TimeSignatureDenom = 0;`
- L69 _public member_ `float CurrentBeatsPerSecond = 0.0f;`
- L70 _public member_ `float CurrentBarsPerSecond = 0.0f;`
- L71 _public member_ `float CurrentClockAdvanceRate = 1.0f;`
- L73 _public member_ `TStaticArray<FMidiSongPos, (int32)ECalibratedMusicTimebase::Count> CurrentSongPos;`
- L74 _public member_ `TStaticArray<FMidiSongPos, (int32)ECalibratedMusicTimebase::Count> PrevSongPos;`
- L77 _public member_ `float DeltaBarF[(int32)ECalibratedMusicTimebase::Count];` — TODO shouldn't these deltas be rolled into the MidiSongPos?
- L78 _public member_ `float DeltaBeatF[(int32)ECalibratedMusicTimebase::Count];`
- L82 _protected prototype_ `virtual void OnStart() = 0;`
- L83 _protected prototype_ `virtual void OnPause() = 0;`
- L84 _protected prototype_ `virtual void OnContinue() = 0;`
- L85 _protected prototype_ `virtual void OnStop() = 0;`
- L87 _protected prototype_ `int32 GetArrayIndexForTimebase(ECalibratedMusicTimebase Timebase) const;`
- L89 _protected prototype_ `void SetCurrentSongPos(ECalibratedMusicTimebase Timebase, const FMidiSongPos& InSongPos);`
- L90 _protected prototype_ `void SetCurrentSongPosByTime(ECalibratedMusicTimebase Timebase, float InElapsedMs, const ISongMapEvaluator& Map);`
- L91 _protected prototype_ `void SetCurrentSongPosByTick(ECalibratedMusicTimebase Timebase, float InTick, const ISongMapEvaluator& Map);`
- L95 _private prototype_ `void ResetDefaultSongMaps(float DefaultTempo, int32 DefaultTimeSigNum, int32 DefaultTimeSigDenom);`
- L96 _private prototype_ `virtual bool RefreshCurrentSongPos() = 0;`
- L97 _private prototype_ `void UpdateBeatsAndBarsPerSecond();`
- L99 _private member_ `uint64 LastUpdateFrame = 0;`
- L101 _private member_ `EMusicClockState MusicClockState = EMusicClockState::Stopped;`
- L103 _private member_ `TWeakObjectPtr<UObject> ContextObj;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicClockTypes.h` (Public)


#### struct `FMusicClockSettingsBase`  
`struct FMusicClockSettingsBase`  
_L13-33_
- reflection: `USTRUCT(MinimalAPI)`
- L18 _public member_ `float DefaultTempo = 120.f;` — `UPROPERTY()`
- L21 _public member_ `int32 DefaultTimeSigNumerator = 4;` — `UPROPERTY()`
- L24 _public member_ `int32 DefaultTimeSigDenominator = 4;` — `UPROPERTY()`
- L26 _public function_ `virtual TSharedPtr<FMusicClockDriverBase> MakeInstance(UObject* WorldContextObj) const`
- L32 _public prototype_ `virtual ~FMusicClockSettingsBase() = default;`

#### struct `FWallClockMusicClockSettings`  
`struct FWallClockMusicClockSettings final : public FMusicClockSettingsBase`  
_L36-44_
- reflection: `USTRUCT(DisplayName = "Wall Clock")`
- inherits: `FMusicClockSettingsBase`
- L41 _public member_ `TObjectPtr<UMidiFile> TempoMap;` — `UPROPERTY(EditAnywhere, Category = "MusicClock")`
- L43 _public prototype_ `virtual TSharedPtr<FMusicClockDriverBase> MakeInstance(UObject* WorldContextObj) const override;`

#### struct `FMetasoundMusicClockSettings`  
`struct FMetasoundMusicClockSettings final : public FMusicClockSettingsBase`  
_L47-58_
- reflection: `USTRUCT(DisplayName = "MetaSound Clock")`
- inherits: `FMusicClockSettingsBase`
- L52 _public member_ `FName MetasoundOutputName = "MI` — `UPROPERTY(EditAnywhere, Category = "MusicClock")`
- L55 _public member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(VisibleAnywhere, Category = "MusicClock")`
- L57 _public prototype_ `virtual TSharedPtr<FMusicClockDriverBase> MakeInstance(UObject* WorldContextObj) const override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicTempometerComponent.h` (Public)


#### class `UMusicTempometerComponent`  
`class UMusicTempometerComponent : public UActorComponent`  
_L21-334_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (MetaSoundMusic), PrioritizeCategories = "MusicClock", meta = (BlueprintSpawnableComponent, DisplayName = "Music Tempometer", ScriptName = MusicTempometerComponent))`
- inherits: `UActorComponent`
- desc: UMusicTempometerComponent provides playback properties of a UMusicClockComponent on its actor and optionally updates a UMaterialParameterCollection.
- L26 _public prototype_ `UMusicTempometerComponent();`
- L32 _public member_ `FName SecondsIncludingCountInParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L38 _public member_ `FName BarsIncludingCountInParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L44 _public member_ `FName BeatsIncludingCountInParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L50 _public member_ `FName SecondsFromBarOneParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L56 _public member_ `FName TimestampBarParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L62 _public member_ `FName TimestampBeatInBarParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L68 _public member_ `FName BarProgressParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L74 _public member_ `FName BeatProgressParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L80 _public member_ `FName TimeSignatureNumeratorParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L86 _public member_ `FName TimeSignatureDenominatorParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L92 _public member_ `FName TempoParameterName_DEPRECATED = "Mu` — `UPROPERTY()` — Deprecated, has moved into structure within MPCParameters
- L98 _public member_ `FMusicTempometerMPCParameters MPCParameters;` — `UPROPERTY(EditAnywhere, Category = "MusicClock")` — Parameter names to use for the values in the material parameter collection.
- L104 _public function_ `const FMidiSongPos& GetSongPos() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — The FSongPos for which the game thread is currently issuing graphics rendering commands, according to calibration data.
- L114 _public function_ `const FMidiSongPos& GetPreviousFrameSongPos() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — The FSongPos for which the game thread previously issued graphics rendering commands.
- L126 _public function_ `float GetSecondsIncludingCountIn() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Seconds from the beginning of the entire music authoring. Includes all count-in and pickup bars (ie. won't be negative when the music starts, and bar 1 beat 1 may not be at 0.0 seconds!
- L138 _public function_ `float GetBarsIncludingCountIn() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Bars from the beginning of the music. Includes all count-in and pickup bars (ie. won't be negative when the music starts, and bar 1 beat 1 of the music may not be equal to elapsed bar 0.0!
- L150 _public function_ `float GetBeatsIncludingCountIn() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Beats from the beginning of the music. Includes all count-in and pickup bars/beats (ie. won't be negative when the music starts, and elapsed beat 0.0 may not equal a timestamp of bar 1 beat 1!
- L161 _public function_ `float GetSecondsFromBarOne() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Seconds from Bar 1 Beat 1 of the music. If the music has a count-in or pickup bars this number may be negative when the music starts!
- L174 _public function_ `FMusicTimestamp GetTimestamp() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current bar & beat in the traditional format, where... - bar 1 beat 1 is the beginning of the song. - bars BEFORE bar 1 are count-in or "pickup" bars. - beat is always 1 or greater.
- L184 _public function_ `float GetBarProgress() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Progress of the current bar [0, 1).
- L194 _public function_ `float GetBeatProgress() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Progress of the current beat [0, 1).
- L204 _public function_ `float GetTimeSignatureNumerator() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current time signature numerator (beats per bar for a simple meter).
- L214 _public function_ `float GetTimeSignatureDenominator() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current time signature denominator (scale from note duration to beat fraction for a simple meter).
- L224 _public function_ `float GetTempo() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current tempo (beats per minute).
- L235 _public function_ `void SetMaterialParameterCollection(UMaterialParameterCollection* InMaterialParameterCollection)` — `UFUNCTION(BlueprintSetter, Category = "MusicClock")` — Set the MaterialParameterCollection whose parameters will be updated. If any of the named parameters are missing they will be ignored.
- L243 _public function_ `UMaterialParameterCollection* GetMaterialParameterCollection() const` — `UFUNCTION(BlueprintPure, Category = "MusicClock")`
- L253 _public function_ `void SetClock(UMusicClockComponent* InClockComponent)` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — SetSongPosInterface allows setting any UObject implementing the ISongPosInterface as the attribute source.
- L264 _public function_ `void SetClockFromActor(AActor* Actor)` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — SetSongPosInterfaceFromActor sets the actor or the first of its owned components that implements ISongPosInterface as the attribute source. BeginPlay calls this on the owning actor when the source ISongPosInterface is not set.
- L271 _public function_ `const UMusicClockComponent* GetClock() const` — `UFUNCTION(BlueprintGetter, Category = "MusicClock")`
- L278 _public prototype_ `virtual void PostLoad() override;`
- L279 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L281 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L286 _private prototype_ `UMusicClockComponent* FindClock(AActor* Actor) const;`
- L287 _private prototype_ `void SetOwnerClock() const;`
- L290 _private function_ `const UMusicClockComponent* GetClockNoMutex() const` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")`
- L299 _private function_ `UMusicClockComponent* GetMutableClockNoMutex() const`
- L308 _private prototype_ `void UpdateCachedSongPos() const;`
- L309 _private prototype_ `void UpdateCachedSongPosIfNeeded() const;`
- L312 _private member_ `mutable FMidiSongPos SongPos;` — `UPROPERTY(BlueprintGetter = GetSongPos, Transient, Category = "MusicClock")`
- L315 _private member_ `mutable FMidiSongPos PreviousFrameSongPos;` — `UPROPERTY(BlueprintGetter = GetPreviousFrameSongPos, Transient, Category = "MusicClock")`
- L317 _private member_ `mutable FCriticalSection SongPosUpdateMutex;`
- L318 _private member_ `mutable uint64 LastFrameCounter;`
- L324 _private member_ `mutable TObjectPtr<UMusicClockComponent> MusicClock;` — `UPROPERTY(BlueprintGetter = GetClock, BlueprintSetter = SetClock, Category = "MusicClock")` — Music whose tempo to detect.
- L327 _private member_ `TObjectPtr<UMaterialParameterCollection> MaterialParameterCollection;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetMaterialParameterCollection, BlueprintSetter = SetMaterialParameterCollection, Category = "MusicClock")`
- L333 _private member_ `mutable TWeakObjectPtr<UMaterialParameterCollectionInstance> MaterialParameterCollectionInstance;` — `UPROPERTY(Transient)` — Pinned material parameter collection instance

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicTimer.h` (Public)


#### class `FMusicTimer`  
`class FMusicTimer`  
_L13-39_
- L17 _public prototype_ `FMusicTimer(uint64 InUniqueIdentifier, const FMusicTimeInterval& InTimeInterval, const FMusicTimestamp& InStartTime, ECalibratedMusicTimebase InTimebase, bool InbLooping, FSimpleDelegate InDelegate);`
- L19 _public function_ `ECalibratedMusicTimebase GetTimebase() const`
- L20 _public prototype_ `uint64 GetUniqueIdentifier() const;`
- L22 _public function_ `bool IsLooping() const`
- L23 _public function_ `bool IsPaused() const`
- L26 _public prototype_ `bool Update(const FMusicTimestamp& CurrentMusicalTimestamp, const FTimeSignature& TimeSignature);` — Returns whether or not the timer is finished
- L27 _public prototype_ `void Reset();`
- L31 _private member_ `ECalibratedMusicTimebase Timebase = ECalibratedMusicTimebase::VideoRenderTime;` — `UPROPERTY(EditAnywhere, Category = "Music|Timer")`
- L33 _private member_ `FSimpleDelegate Delegate;`
- L34 _private member_ `FMusicTimeInterval TimeInterval;`
- L35 _private member_ `FMusicTimestamp StartTime;`
- L36 _private member_ `TOptional<FMusicTimestamp> PausedTime;`
- L37 _private member_ `uint64 UniqueIdentifier = 0;`
- L38 _private member_ `bool bLooping = false;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicTimer, Warning, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicTimer, Warning, All);`
- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicTimerHandle.h` (Public)


#### struct `FMusicTimerHandle`  
`struct FMusicTimerHandle`  
_L12-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: Unique handle that can be used to distinguish timers that have identical delegates.
- L18 _public prototype_ `FMusicTimerHandle(uint64 InHandle = 0);`
- L20 _public prototype_ `bool IsValid() const;`
- L21 _public prototype_ `void Invalidate();`
- L23 _public prototype_ `FString ToString() const;`
- L24 _public prototype_ `uint64 GetUniqueIdentifier() const;`
- L27 _public prototype_ `bool operator==(const FMusicTimerHandle& Other) const;`
- L28 _public prototype_ `bool operator!=(const FMusicTimerHandle& Other) const;`
- L33 _private member_ `uint64 Handle;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Components/MusicTimerManager.h` (Public)


#### class `UMusicTimerManager`  
`class UMusicTimerManager : public UObject`  
_L22-73_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UObject`
- L29 _public prototype_ `void UpdateForGameFrame(const TStaticArray<FMidiSongPos, (int32)ECalibratedMusicTimebase::Count>& CurrentSongPositions);` — We need the MidiSongPosition in each calibrated time, because each timer can be operating on their own timebase.
- L41 _public prototype_ `FMusicTimerHandle BP_AddTimer(const FMusicTimeInterval& TimerInterval, FMusicTimestamp StartTime, ECalibratedMusicTimebase Timebase, bool bLooping, FOnMusicalTimerExecute TimerDelegate);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")` — Adds a musical timer. @param TimerInterval  Interval configuration for the timer. @param StartTime      Start time. You can use the Quantize function below to snap to interval boundaries. @param Timebase       Timebase used to evaluate the timer. @param bLooping       Whether the timer should loop. @param TimerDelegate  Delegate executed when the timer fires.
- L52 _public prototype_ `FMusicTimerHandle AddTimerNative(const FMusicTimeInterval& TimerInterval, FMusicTimestamp StartTime, ECalibratedMusicTimebase Timebase, bool bLooping, FSimpleDelegate TimerDelegate);` — Adds a musical timer. @param TimerInterval  Interval configuration for the timer. @param StartTime      Start time. You can use the Quantize function below to snap to interval boundaries. @param Timebase       Timebase used to evaluate the timer. @param bLooping       Whether the timer should loop. @param TimerDelegate  Delegate executed when the timer fires.
- L55 _public prototype_ `void RemoveTimer(const FMusicTimerHandle& Handle);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L58 _public prototype_ `void PauseTimer(const FMusicTimerHandle& Handle, bool bPause);` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L61 _public prototype_ `FMusicTimestamp Quantize(const UMusicClockComponent* MusicClock, const FMusicTimestamp& Time, EMidiClockSubdivisionQuantization QuantizationInterval, EMidiFileQuantizeDirection InDirection) const;` — `UFUNCTION(BlueprintCallable, Category = "Music|Timer")`
- L63 _public function_ `uint64 GetUniqueTimerId()`
- L67 _private member_ `TStaticArray<FMidiSongPos, (int32)ECalibratedMusicTimebase::Count> LastUpdateFrameSongPositions;` — Used so pause doesn't need to pass in this info
- L69 _private member_ `TArray<TUniquePtr<FMusicTimer>> ActiveTimers;` — Current Timers being processed
- L70 _private member_ `TArray<TUniquePtr<FMusicTimer>> PendingTimers;` — New timers added during execution
- L71 _private member_ `uint64 LastUpdateFrame = 0;`
- L72 _private member_ `static std::atomic<uint64> NextTimerId;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicTimerManager, Warning, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMusicTimerManager, Warning, All);`
- L13 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnMusicalTimerExecute);`
- L13 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnMusicalTimerExecute);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/AudioRenderableAsset.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace HarmonixMetasound`
- L12 _macro_ `#define DECLARE_AUDIORENDERABLE_ASSET(InNamespace, AssetStructName, ProxyName, ModuleApi) \` — This next macro declares the class that will be registered with Metasound, creating the TypeInfo, ReadRef, and WriteRef types needed for that. You must use this macro in the header where your USTRUCT is defined, and you must use the corresponding "DEFINE_AUDIORENDERABLE_ASSET" macro in the cpp file.
- L49 _macro_ `#define DEFINE_AUDIORENDERABLE_ASSET(InNamespace, AssetStructName, AssetPlainName, AssetUObjectClass) \` — This next macro defines the "audio renderable asset" declared with the macro above. Use this one in your cpp file.

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/DelayFilterType.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/DelayStereoType.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/FFTAnalyzerResult.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/FusionPatchRenderableAsset.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/HarmonixMetasoundMusicAsset.h` (Public)


#### class `UHarmonixMetasoundMusicAsset`  
`class UHarmonixMetasoundMusicAsset : public UHarmonixMusicAsset`  
_L29-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", Meta = (DisplayName = "Harmonix MetaSound Music"))`
- inherits: `UHarmonixMusicAsset`
- desc: UHarmonixMetasoundMusicAsset: In this case, the music asset is comprised of a MetaSound that uses the Harmonix MetaSound nodes to generate musical time, and a midi file which maps the tempo and time signatures that define the music's form.
- L35 _public member_ `TObjectPtr<UMetaSoundSource> MetaSoundSource;` — `UPROPERTY(EditAnywhere, Category = "Music", meta = (GetAssetFilter = "AssetIsMissingHarmoixMusicInterface"))`
- L38 _public prototype_ `static bool AssetIsMissingHarmoixMusicInterface(const FAssetData& AssetData);` — `UFUNCTION()`
- L41 _protected function_ `virtual UMetaSoundSource* GetMetaSoundSource()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/HarmonixMusicAsset.h` (Public)


#### class `UHarmonixMusicAsset`  
`class UHarmonixMusicAsset : public UObject, public IMusicalAsset`  
_L28-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", Meta = (DisplayName = "Harmonix MetaSound Music"))`
- inherits: `UObject,IMusicalAsset`
- desc: UHarmonixMusicAsset An implementation of the pure virtual IMusicalAsset interface that will act as a base class for UHarmonixMetasoundMusicAsset and UHarmonixWaveMusicAsset. As such, it can return an FMusicHandle when it is asked to PrepareToPlay or Play.
- L34 _public member_ `TObjectPtr<UMidiFile> MidiSongMap;` — `UPROPERTY(EditAnywhere, Category = "Music")`
- L36 _public function_ `virtual UMetaSoundSource* GetMetaSoundSource()`
- L40 _public prototype_ `virtual void CreateFrameBasedMusicMap(UFrameBasedMusicMap* Map) const override;`
- L41 _public prototype_ `virtual FMarkerProviderResults GatherMarkers(const UFrameBasedMusicMap* Map) const override;`
- L43 _protected prototype_ `virtual FMusicHandle PrepareToPlay_Internal(UObject* PlaybackContext, UAudioComponent* OnComponennt = nullptr, float FromSeconds = 0.0f, bool IsAudition = false) override;`
- L44 _protected prototype_ `virtual FMusicHandle Play_Internal(UObject* PlaybackContext, UAudioComponent* OnComponennt = nullptr, float FromSeconds = 0.0f, bool IsAudition = false) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/HarmonixMusicHandle.h` (Public)


#### class `UHarmonixMusicHandle`  
`class UHarmonixMusicHandle : public UObject, public IMusicHandle`  
_L31-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IMusicHandle`
- L36 _public prototype_ `static UHarmonixMusicHandle* Instantiate(UHarmonixMusicAsset* Asset, UObject* PlaybackContext, UAudioComponent* OnComponent, float FromSeconds = 0.0f, bool bIsAudition = false);`
- L38 _public prototype_ `virtual bool IsValid() const override;`
- L39 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L42 _public prototype_ `virtual bool Play(float FromSeconds = 0.0f) override;` — /  Transport
- L43 _public prototype_ `virtual void Pause() override;`
- L44 _public prototype_ `virtual void Continue() override;`
- L46 _protected prototype_ `virtual void Stop_Internal() override;`
- L47 _protected prototype_ `virtual void Kill_Internal() override;`
- L50 _public prototype_ `virtual bool IsUsingAsset(const UObject* Asset) const override;`
- L52 _public prototype_ `virtual TScriptInterface<IMusicEnvironmentClockSource> GetMusicClockSource() override;`
- L56 _private member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(Transient)`
- L59 _private member_ `TObjectPtr<UMusicClockComponent> MusicClockComponent;` — `UPROPERTY(Transient)`
- L62 _private member_ `TObjectPtr<UHarmonixMusicAsset> PlayingAsset;` — `UPROPERTY(Transient)`
- L64 _private member_ `bool bHasStarted = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/HarmonixWaveMusicAsset.h` (Public)


#### class `UHarmonixWaveMusicAsset`  
`class UHarmonixWaveMusicAsset : public UHarmonixMusicAsset`  
_L25-45_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", Meta = (DisplayName = "Harmonix Wave Music"))`
- inherits: `UHarmonixMusicAsset`
- L31 _public member_ `TObjectPtr<USoundWave> WaveFile;` — `UPROPERTY(EditAnywhere, Category = "Music")`
- L33 _public prototype_ `virtual float GetSongLengthSeconds() const override;`
- L36 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L40 _protected prototype_ `virtual UMetaSoundSource* GetMetaSoundSource();`
- L44 _private member_ `TObjectPtr<UMetaSoundSource> CachedMetasound;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiAsset.h` (Public)


#### class `HarmonixMetasound::FMidiAsset`  
`class FMidiAsset`  
_L15-43_
- L17 _private member_ `FMidiFileProxyPtr MidiFileProxy;`
- L21 _public prototype_ `FMidiAsset() = default;`
- L22 _public prototype_ `FMidiAsset(const FMidiAsset&) = default;`
- L23 _public prototype_ `FMidiAsset& operator=(const FMidiAsset& Other) = default;`
- L25 _public prototype_ `FMidiAsset(const TSharedPtr<Audio::IProxyData>& InInitData);`
- L27 _public prototype_ `bool IsMidiValid() const;`
- L29 _public function_ `const FMidiFileProxyPtr& GetMidiProxy() const`
- L34 _public function_ `const FMidiFileProxy* operator->() const`
- L39 _public function_ `FMidiFileProxy* operator->()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L13 _namespace_ `namespace HarmonixMetasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiClock.h` (Public)


#### class `HarmonixMetasound::FMidiClock`  
`class FMidiClock : public TSharedFromThis<FMidiClock, ESPMode::NotThreadSafe>`  
_L41-234_
- inherits: `TSharedFromThis<FMidiClock,ESPMode::NotThreadSafe>`
- L44 _public member_ `static constexpr int32 kMidiGranularity = 128;`
- L46 _public prototype_ `explicit FMidiClock(const Metasound::FOperatorSettings& InSettings);`
- L47 _public prototype_ `FMidiClock(const FMidiClock& Other);`
- L48 _public prototype_ `virtual ~FMidiClock();`
- L49 _public prototype_ `FMidiClock& operator=(const FMidiClock& Other);`
- L51 _public prototype_ `void AttachToSongMapEvaluator(TSharedPtr<ISongMapEvaluator> SongMaps, bool ResetToStart = true);`
- L52 _public prototype_ `void SongMapsChanged();`
- L53 _public prototype_ `void DetachFromSongMaps();`
- L54 _public prototype_ `void Reset(const Metasound::FOperatorSettings& InSettings);`
- L56 _public function_ `const ISongMapEvaluator& GetSongMapEvaluator() const`
- L58 _public prototype_ `void SetDrivingClock(FConstSharedMidiClockPtr NewExternalClockDriver);`
- L59 _public function_ `FConstSharedMidiClockPtr GetDrivingClock() const`
- L61 _public prototype_ `void PrepareBlock();`
- L63 _public prototype_ `void SetTransportState(int32 BlockFrameIndex, EMusicPlayerTransportState TransportState);`
- L64 _public prototype_ `void SetSpeed(int32 BlockFrameIndex, float Speed);`
- L65 _public prototype_ `void SetTempo(int32 BlockFrameIndex, int32 Tick, float Bpm, int32 TempoMapTick);`
- L66 _public prototype_ `void SetTimeSignature(int32 BlockFrameIndex, int32 Tick, const FTimeSignature& TimeSignature, int32 TempoMapTick);`
- L69 _public prototype_ `void SeekTo(int32 BlockFrameIndex, const FMusicSeekTarget& InTarget);` — directly seek this clock with a musical seek target or a specific tick
- L70 _public prototype_ `void SeekTo(int32 BlockFrameIndex, int32 Tick, int32 TempoMapTick);`
- L76 _public prototype_ `void AddTransientLoop(int32 BlockFrameIndex, int32 NewFirstTiokInLoop, int32 NewLoopLengthTicks);` — This will add a loop event to the clock event stream WITHOUT having to set this clock to looping. This is used when this clock is being driven by an external clock and THAT clock's looping setup causes this clock to loop.
- L77 _public prototype_ `void SetupPersistentLoop(int32 NewFirstTickInLoop, int32 NewLoopLengthTicks);`
- L78 _public prototype_ `void ClearPersistentLoop();`
- L79 _public prototype_ `bool HasPersistentLoop() const;`
- L80 _public function_ `int32 GetFirstTickInLoop() const`
- L81 _public function_ `int32 GetLoopLengthTicks() const`
- L82 _public prototype_ `float GetLoopStartMs() const;`
- L83 _public prototype_ `float GetLoopEndMs() const;`
- L84 _public prototype_ `float GetLoopLengthMs() const;`
- L88 _public prototype_ `void Advance(const FMidiClock& DrivingClock, int32 StartFrame, int32 NumFrames);` — process and advance the clock based on the driving clock given sample frames will handle the driving clock events based on the frame range
- L91 _public prototype_ `void Advance(int32 StartFrame, int32 NumFrames);` — process and advance the clock normally based on the given sample frames
- L93 _public prototype_ `bool AdvanceToTick(int32 BlockFrameIndex, int32 UpToTick, int32 TempoMapTick);`
- L94 _public prototype_ `bool AdvanceToMs(int32 BlockFrameIndex, float Ms);`
- L96 _public function_ `bool HasTransportStateChangesInBlock() const`
- L97 _public function_ `int32 GetNumTransportStateChangesInBlock() const`
- L98 _public function_ `bool HasSpeedChangesInBlock() const`
- L99 _public function_ `int32 GetNumSpeedChangesInBlock() const`
- L100 _public function_ `bool HasTempoChangesInBlock() const`
- L101 _public function_ `int32 GetNumTempoChangesInBlock() const`
- L103 _public function_ `const FMidiClockEvents& GetMidiClockEventsInBlock() const`
- L105 _public function_ `EMusicPlayerTransportState GetTransportStateAtStartOfBlock() const`
- L106 _public function_ `EMusicPlayerTransportState GetTransportStateAtEndOfBlock() const`
- L108 _public function_ `float GetSpeedAtStartOfBlock() const`
- L109 _public prototype_ `float GetSpeedAtBlockSampleFrame(int32 FrameIndex) const;`
- L110 _public function_ `float GetSpeedAtEndOfBlock() const`
- L112 _public function_ `float GetTempoAtStartOfBlock() const`
- L113 _public prototype_ `float GetTempoAtBlockSampleFrame(int32 FrameIndex) const;`
- L114 _public function_ `float GetTempoAtEndOfBlock() const`
- L116 _public function_ `int32 GetLastProcessedMidiTick() const`
- L117 _public function_ `int32 GetNextMidiTickToProcess() const`
- L119 _public prototype_ `float GetCurrentSongPosMs() const;`
- L125 _public prototype_ `FMusicTimestamp GetMusicTimestampAtBlockEnd() const;` — @brief Get the timestamp after the most recent clock update @return The current timestamp
- L132 _public prototype_ `FMusicTimestamp GetMusicTimestampAtBlockOffset(int32 Offset) const;` — @brief Get the music timestamp at a given frame offset from the last processed audio block. @param Offset - The frame index from the beginning of the last processed audio block @return The music timestamp
- L142 _public prototype_ `float GetSongPosMsAtBlockOffset(int32 Offset) const;` — @brief Get the absolute "music time" in ms for a frame within the last audio block. This is the time in the musical content that the clock has advanced "up to". Note: This time will not be sample accurate as midi processing advances by ticks, and the time is calculated by turning the "current tick" at the offset provided into a time in ms. @param Offset - The frame index from the beginning of the last processed audio block @return The absolute time in ms
- L167 _public prototype_ `int32 WrapTickIfLooping(int32 Tick) const;` — Given an input tick, outputs a looped tick if the input tick is > the StartTick of the Loop Region If the clock is not looping, or loop region length is 0, then the output will be unchanged. The output tick will be in range [Min(Tick, LoopStartTick), LoopEndTick). Example: LoopRegion: (0, 100): 10 -> 10 100 -> 0 110 -> 10 -10 -> 90 LoopRegion: (40, 100): 0 -> 0 10 -> 10 -10 -> -10 99  -> 99 100 -> 40 110 -> 50 @param		Tick - Absolute Tick @return		Looped Tick if Tick > LoopEnd: LoopedTick = LoopStart + (Tick - LoopStart) % (LoopEnd - LoopStart)
- L169 _public function_ `bool GetSongMapsChangedInBlock() const`
- L171 _public prototype_ `int32 GetNextTickToProcessAtBlockFrame(int32 BlockFrame) const;`
- L174 _private prototype_ `void AddEvent(const FMidiClockEvent& InEvent, bool bRequireSequential = true);`
- L175 _private prototype_ `void HandleClockEvent(const FMidiClock& DrivingClock, const FMidiClockEvent& Event);`
- L176 _private prototype_ `void PostTempoOrTimeSignatureEventsIfNeeded();`
- L179 _private prototype_ `template <typename MSGTYPE> MSGTYPE* LookForEventOnMidiTick(int32 Tick);`
- L181 _private prototype_ `template <typename MSGTYPE> MSGTYPE* LookForEventOnBlockFrameIndex(int32 BlockFrameIndex);`
- L183 _private prototype_ `void AddTransportStateChangeToBlock(int32 BlockFrameIndex, EMusicPlayerTransportState TransportState);`
- L184 _private prototype_ `void AddTimeSignatureChangeToBlock(int32 BlockFrameIndex, int32 Tick, const FTimeSignature& TimeSignature, int32 TempoMapTick);`
- L185 _private prototype_ `void AddTempoChangeToBlock(int32 BlockFrameIndex, int32 Tick, float Tempo, int32 TempoMapTick);`
- L186 _private prototype_ `void AddSpeedChangeToBlock(int32 BlockFrameIndex, float Speed, bool bIsNewLocalSpeed);`
- L187 _private prototype_ `void AddLoopToBlock(int32 BlockFrameIndex, int32 FirstTick, int32 LoopLength, int32 TempoMapTick);`
- L188 _private prototype_ `void AddSeekToBlock(int32 BlockFrameIndex, int32 ToTick, int32 TempoMapTick);`
- L189 _private prototype_ `void AddAdvanceToBlock(int32 BlockFrameIndex, int32 FirstTick, int32 NumTicks, int32 TempoMapTick);`
- L190 _private prototype_ `void RebuildSongMapEvaluator(const TSharedPtr<const ISongMapEvaluator>& MidiWithTempo, const TSharedPtr<const ISongMapEvaluator>& MidiWithOtherMaps);`
- L192 _private member_ `TSharedPtr<FSongMapsWithAlternateTempoSource> SongMapEvaluator;`
- L193 _private member_ `int32 CurrentTempoInfoPointIndex;`
- L194 _private member_ `int32 CurrentTimeSignaturePointIndex;`
- L196 _private member_ `FConstSharedMidiClockPtr ExternalClockDriver;`
- L197 _private member_ `float TickResidualWhenDriven;`
- L199 _private member_ `int32 BlockSize;`
- L200 _private member_ `int32 CurrentBlockFrameIndex;`
- L201 _private member_ `int32 FirstTickProcessedThisBlock;`
- L202 _private member_ `int32 LastProcessedMidiTick;`
- L203 _private member_ `int32 NextMidiTickToProcess;`
- L204 _private member_ `int32 NextTempoMapTickToProcess;`
- L205 _private member_ `float SampleRate;`
- L206 _private member_ `Metasound::FSampleCount SampleCount;`
- L207 _private member_ `int32 FramesUntilNextProcess;`
- L208 _private member_ `EMusicPlayerTransportState TransportAtBlockStart;`
- L209 _private member_ `EMusicPlayerTransportState TransportAtBlockEnd;`
- L210 _private member_ `float SpeedAtBlockStart;`
- L211 _private member_ `float SpeedAtBlockEnd;`
- L212 _private member_ `float CurrentLocalSpeed;`
- L213 _private member_ `float TempoAtBlockStart;`
- L214 _private member_ `float TempoAtBlockEnd;`
- L215 _private member_ `FTimeSignature TimeSignatureAtBlockStart;`
- L216 _private member_ `FTimeSignature TimeSignatureAtBlockEnd;`
- L218 _private member_ `int32 NumTransportChangeInBlock;`
- L219 _private member_ `int32 NumSpeedChangeInBlock;`
- L220 _private member_ `int32 NumTempoChangeInBlock;`
- L221 _private member_ `int32 NumTimeSignatureChangeInBlock;`
- L223 _private member_ `int32 NextTempoChangeTick;`
- L224 _private member_ `int32 NextTimeSigChangeTick;`
- L225 _private member_ `int32 NextTempoOrTimeSigChangeTick;`
- L227 _private member_ `int32 FirstTickInLoop;`
- L228 _private member_ `int32 LoopLengthTicks;`
- L230 _private member_ `bool MidiDataChangedInBlock;`
- L231 _private member_ `bool NeedsSeekToDrivingClock;`
- L233 _private member_ `FMidiClockEvents MidiClockEventsInBlock;`
- L257 _function_ `template <typename MSGTYPE> MSGTYPE* FMidiClock::LookForEventOnBlockFrameIndex(int32 BlockFrameIndex)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L22 _namespace_ `namespace Metasound`
- L35 _namespace_ `namespace HarmonixMetasound`
- L38 _typedef_ `using FConstSharedMidiClockPtr = TSharedPtr<const FMidiClock, ESPMode::NotThreadSafe>;` (scope `HarmonixMetasound`)
- L39 _typedef_ `using FMidiClockEvents = TArray<FMidiClockEvent>;` (scope `HarmonixMetasound`)
- L237 _function_ `DECLARE_METASOUND_DATA_REFERENCE_ALIAS_TYPES(FMidiClock, FMidiClockTypeInfo, FMidiClockReadRef, FMidiClockWriteRef) template <typename MSGTYPE> MSGTYPE* FMidiClock::LookForEventOnMidiTick(int32 Tick)` (scope `HarmonixMetasound`) — Declare aliases IN the namespace...

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiClockEvent.h` (Public)


#### struct `HarmonixMetasound::MidiClockMessageTypes::FLoop`  
`struct FLoop`  
_L10-21_
- L12 _public member_ `int32 FirstTickInLoop;`
- L13 _public member_ `int32 LengthInTicks;`
- L14 _public member_ `int32 TempoMapTick;`
- L16 _public function_ `FLoop(const int32 FirstTickInLoop, const int32 LengthInTicks, const int32 TempoMapTick) : FirstTickInLoop(FirstTickInLoop) , LengthInTicks(LengthInTicks) , TempoMapTick(TempoMapTick)`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FSeek`  
`struct FSeek`  
_L23-34_
- L25 _public member_ `int32 LastTickProcessedBeforeSeek;`
- L26 _public member_ `int32 NewNextTick;`
- L27 _public member_ `int32 TempoMapTick;`
- L29 _public function_ `FSeek(const int32 LastTickProcessedBeforeSeek, const int32 NewNextTick, const int32 TempoMapTick) : LastTickProcessedBeforeSeek(LastTickProcessedBeforeSeek) , NewNextTick(NewNextTick) , TempoMapTick(TempoMapTick)`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FAdvance`  
`struct FAdvance`  
_L36-51_
- L38 _public member_ `int32 FirstTickToProcess;`
- L39 _public member_ `int32 NumberOfTicksToProcess;`
- L40 _public member_ `int32 TempoMapTick;`
- L42 _public function_ `FAdvance(const int32 FirstTickToProcess, const int32 NumberOfTicksToProcess, const int32 TempoMapTick) : FirstTickToProcess(FirstTickToProcess) , NumberOfTicksToProcess(NumberOfTicksToProcess) , TempoMapTick(TempoMapTick)`
- L48 _public function_ `int32 LastTickToProcess() const`
- L50 _public function_ `bool ContainsTick(int32 InTick) const`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FTempoChange`  
`struct FTempoChange`  
_L53-66_
- L55 _public member_ `int32 Tick;`
- L56 _public member_ `float Tempo;`
- L57 _public member_ `int32 TempoMapTick;`
- L59 _public function_ `FTempoChange(const int32 Tick, const float Tempo, const int32 TempoMapTick) : Tick(Tick) , Tempo(Tempo) , TempoMapTick(TempoMapTick)`
- L65 _public function_ `bool ContainsTick(int32 InTick) const`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FTimeSignatureChange`  
`struct FTimeSignatureChange`  
_L68-81_
- L70 _public member_ `int32 Tick;`
- L71 _public member_ `FTimeSignature TimeSignature;`
- L72 _public member_ `int32 TempoMapTick;`
- L74 _public function_ `FTimeSignatureChange(const int32 Tick, FTimeSignature&& TimeSignature, const int32 TempoMapTick) : Tick(Tick) , TimeSignature(MoveTemp(TimeSignature)) , TempoMapTick(TempoMapTick)`
- L80 _public function_ `bool ContainsTick(int32 InTick) const`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FTransportChange`  
`struct FTransportChange`  
_L83-90_
- L85 _public member_ `EMusicPlayerTransportState TransportState;`
- L87 _public function_ `FTransportChange(EMusicPlayerTransportState NewTransportState) : TransportState(NewTransportState)`

#### struct `HarmonixMetasound::MidiClockMessageTypes::FSpeedChange`  
`struct FSpeedChange`  
_L92-99_
- L94 _public member_ `float Speed;`
- L96 _public function_ `FSpeedChange(float NewSpeed) : Speed(NewSpeed)`

#### struct `HarmonixMetasound::FMidiClockEvent`  
`struct FMidiClockEvent`  
_L112-132_
- L114 _public member_ `const int32 BlockFrameIndex;`
- L115 _public member_ `FMidiClockMsg Msg;`
- L118 _public function_ `template<typename T> FMidiClockEvent(const int32 InBlockFrameIndex, T&& Msg) : BlockFrameIndex(InBlockFrameIndex) , Msg(TInPlaceType<T>(), MoveTemp(Msg))`
- L125 _public function_ `template<typename T> bool IsType() const`
- L128 _public function_ `template<typename T> const T* TryGet() const`
- L131 _public function_ `template<typename T> T* TryGet()`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace HarmonixMetasound`
- L8 _namespace_ `namespace MidiClockMessageTypes` (scope `HarmonixMetasound`)
- L102 _typedef_ `using FMidiClockMsg = TVariant< MidiClockMessageTypes::FLoop, MidiClockMessageTypes::FSeek, MidiClockMessageTypes::FAdvance, MidiClockMessageTypes::FTempoChange, MidiClockMessageTypes::FTimeSignatureChange, MidiClockMessageTypes::FTransportChange, MidiClockMessageTypes::FSpeedChange >;` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiControllerID.h` (Public)


#### enum `EStdMidiControllerID`  
`enum class EStdMidiControllerID: uint8`  
_L16-166_
- reflection: `UENUM()`
- L18 _public enumerator_ `BankSelection = 0`
- L19 _public enumerator_ `ModWheel = 1`
- L20 _public enumerator_ `Breath = 2`
- L22 _public enumerator_ `Undefined3`
- L24 _public enumerator_ `FootController = 4`
- L25 _public enumerator_ `PortamentoTime = 5`
- L26 _public enumerator_ `DataCoarse = 6`
- L27 _public enumerator_ `Volume = 7`
- L28 _public enumerator_ `Balance = 8`
- L29 _public enumerator_ `Undefined9 = 9`
- L30 _public enumerator_ `Pan = 10`
- L31 _public enumerator_ `Expression = 11`
- L32 _public enumerator_ `EffectControl1 = 12`
- L33 _public enumerator_ `EffectControl2 = 13`
- L35 _public enumerator_ `Undefined14`
- L36 _public enumerator_ `Undefined15`
- L38 _public enumerator_ `GeneralPurposeController1 = 16`
- L39 _public enumerator_ `GeneralPurposeController2 = 17`
- L40 _public enumerator_ `GeneralPurposeController3 = 18`
- L41 _public enumerator_ `GeneralPurposeController4 = 19`
- L43 _public enumerator_ `Undefined20`
- L44 _public enumerator_ `Undefined21`
- L45 _public enumerator_ `Undefined22`
- L46 _public enumerator_ `Undefined23`
- L47 _public enumerator_ `Undefined24`
- L48 _public enumerator_ `Undefined25`
- L49 _public enumerator_ `Undefined26`
- L50 _public enumerator_ `Undefined27`
- L51 _public enumerator_ `Undefined28`
- L52 _public enumerator_ `Undefined29`
- L53 _public enumerator_ `Undefined30`
- L54 _public enumerator_ `Undefined31`
- L57 _public enumerator_ `LSBControl0 = 32` — LSB of controller IDs 0-31 (0-31 are MSB)
- L58 _public enumerator_ `LSBControl1 = 33`
- L59 _public enumerator_ `LSBControl2 = 34`
- L60 _public enumerator_ `LSBControl3 = 35`
- L61 _public enumerator_ `LSBControl4 = 36`
- L62 _public enumerator_ `LSBControl5 = 37`
- L63 _public enumerator_ `LSBControl6 = 38`
- L64 _public enumerator_ `LSBControl7 = 39`
- L65 _public enumerator_ `LSBControl8 = 40`
- L66 _public enumerator_ `LSBControl9 = 41`
- L67 _public enumerator_ `LSBControl10 = 42`
- L68 _public enumerator_ `LSBControl11 = 43`
- L69 _public enumerator_ `LSBControl12 = 44`
- L70 _public enumerator_ `LSBControl13 = 45`
- L71 _public enumerator_ `LSBControl14 = 46`
- L72 _public enumerator_ `LSBControl15 = 47`
- L73 _public enumerator_ `LSBControl16 = 48`
- L74 _public enumerator_ `LSBControl17 = 49`
- L75 _public enumerator_ `LSBControl18 = 50`
- L76 _public enumerator_ `LSBControl19 = 51`
- L77 _public enumerator_ `LSBControl20 = 52`
- L78 _public enumerator_ `LSBControl21 = 53`
- L79 _public enumerator_ `LSBControl22 = 54`
- L80 _public enumerator_ `LSBControl23 = 55`
- L81 _public enumerator_ `LSBControl24 = 56`
- L82 _public enumerator_ `LSBControl25 = 57`
- L83 _public enumerator_ `LSBControl26 = 58`
- L84 _public enumerator_ `LSBControl27 = 59`
- L85 _public enumerator_ `LSBControl28 = 60`
- L86 _public enumerator_ `LSBControl29 = 61`
- L87 _public enumerator_ `LSBControl30 = 62`
- L88 _public enumerator_ `LSBControl31 = 63`
- L90 _public enumerator_ `Hold = 64`
- L91 _public enumerator_ `PortamentoSwitch = 65`
- L92 _public enumerator_ `Sustenuto = 66`
- L93 _public enumerator_ `SoftPedal = 67`
- L94 _public enumerator_ `Legato = 68`
- L95 _public enumerator_ `Hold2 = 69`
- L97 _public enumerator_ `SoundController1 = 70`
- L98 _public enumerator_ `SoundController2 = 71`
- L99 _public enumerator_ `SoundController3 = 72`
- L100 _public enumerator_ `SoundController4 = 73`
- L101 _public enumerator_ `SoundController5 = 74`
- L102 _public enumerator_ `SoundController6 = 75`
- L103 _public enumerator_ `SoundController7 = 76`
- L104 _public enumerator_ `SoundController8 = 77`
- L105 _public enumerator_ `SoundController9 = 78`
- L106 _public enumerator_ `SoundController10 = 79`
- L108 _public enumerator_ `GeneralPurposeController5 = 80`
- L109 _public enumerator_ `GeneralPurposeController6 = 81`
- L110 _public enumerator_ `GeneralPurposeController7 = 82`
- L111 _public enumerator_ `GeneralPurposeController8 = 83`
- L113 _public enumerator_ `PortamentoControl = 84`
- L115 _public enumerator_ `Undefined85`
- L116 _public enumerator_ `Undefined86`
- L117 _public enumerator_ `Undefined87`
- L119 _public enumerator_ `HighResolutionVelocityPrefix = 88`
- L121 _public enumerator_ `Undefined89`
- L122 _public enumerator_ `Undefined90`
- L124 _public enumerator_ `Effects1Depth = 91`
- L125 _public enumerator_ `Effects2Depth = 92`
- L126 _public enumerator_ `Effects3Depth = 93`
- L127 _public enumerator_ `Effects4Depth = 94`
- L128 _public enumerator_ `Effects5Depth = 95`
- L129 _public enumerator_ `DataIncrement = 96`
- L130 _public enumerator_ `DataDecrement = 97`
- L131 _public enumerator_ `NRPNFine = 98`
- L132 _public enumerator_ `NRPNCoarse = 99`
- L133 _public enumerator_ `RPNFine = 100`
- L134 _public enumerator_ `RPNCoarse = 101`
- L136 _public enumerator_ `Undefined102`
- L137 _public enumerator_ `Undefined103`
- L138 _public enumerator_ `Undefined104`
- L139 _public enumerator_ `Undefined105`
- L140 _public enumerator_ `Undefined106`
- L141 _public enumerator_ `Undefined107`
- L142 _public enumerator_ `Undefined108`
- L143 _public enumerator_ `Undefined109`
- L144 _public enumerator_ `Undefined110`
- L145 _public enumerator_ `Undefined111`
- L146 _public enumerator_ `Undefined112`
- L147 _public enumerator_ `Undefined113`
- L148 _public enumerator_ `Undefined114`
- L149 _public enumerator_ `Undefined115`
- L150 _public enumerator_ `Undefined116`
- L151 _public enumerator_ `Undefined117`
- L152 _public enumerator_ `Undefined118`
- L153 _public enumerator_ `Undefined119`
- L155 _public enumerator_ `AllSoundOff = 120`
- L156 _public enumerator_ `Reset = 121`
- L157 _public enumerator_ `LocalKeyboardSwitch = 122`
- L158 _public enumerator_ `AllNotesOff = 123`
- L159 _public enumerator_ `OmniModeOff = 124`
- L160 _public enumerator_ `OmniModeOn = 125`
- L161 _public enumerator_ `MonoMode = 126`
- L162 _public enumerator_ `PolyMode = 127`
- L164 _public enumerator_ `NUM UMETA(Hidden)`

#### Free symbols / members of external scopes

- L168 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiEventInfo.h` (Public)


#### struct `FMidiEventInfo`  
`struct FMidiEventInfo`  
_L15-41_
- reflection: `USTRUCT(BlueprintType, Meta = (DisplayName = "MIDI Event Info"))`
- L20 _public member_ `FMusicTimestamp Timestamp{ 0, 0 };` — `UPROPERTY(Category = "Music", EditAnywhere, BlueprintReadWrite)`
- L23 _public member_ `int32 TrackIndex{ 0 };` — `UPROPERTY(Category = "Music", EditAnywhere, BlueprintReadWrite)`
- L25 _public member_ `FMidiMsg MidiMessage{ 0, 0, 0 };`
- L27 _public prototype_ `uint8 GetChannel() const;`
- L29 _public prototype_ `bool IsNote() const;`
- L30 _public prototype_ `bool IsNoteOn() const;`
- L31 _public prototype_ `bool IsNoteOff() const;`
- L32 _public prototype_ `uint8 GetNoteNumber() const;`
- L33 _public prototype_ `uint8 GetVelocity() const;`

#### class `UMidiEventInfoBlueprintLibrary`  
`class UMidiEventInfoBlueprintLibrary final : public UBlueprintFunctionLibrary`  
_L44-71_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L49 _private prototype_ `static bool IsMidiEventInfo(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L52 _private prototype_ `static FMidiEventInfo GetMidiEventInfo(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L55 _private prototype_ `static int32 GetChannel(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L58 _private prototype_ `static bool IsNote(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L61 _private prototype_ `static bool IsNoteOn(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L64 _private prototype_ `static bool IsNoteOff(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L67 _private prototype_ `static int32 GetNoteNumber(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`
- L70 _private prototype_ `static int32 GetVelocity(const FMidiEventInfo& Event);` — `UFUNCTION(BlueprintCallable, Category = "Music")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L35 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMidiEventInfo& InMidiEventInfo)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiStepSequence.h` (Public)


#### struct `FStepSequenceCell`  
`struct FStepSequenceCell`  
_L20-39_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public prototype_ `FStepSequenceCell() = default;`
- L26 _public prototype_ `FStepSequenceCell(const FStepSequenceCell&) = default;`
- L27 _public prototype_ `FStepSequenceCell& operator=(const FStepSequenceCell&) = default;`
- L28 _public prototype_ `FStepSequenceCell(FStepSequenceCell&&) = default;`
- L29 _public function_ `FStepSequenceCell(bool bEnabled, bool bContinuation) : bEnabled(bEnabled) , bContinuation(bContinuation)`
- L35 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence", Meta = (PostEditType = "Trivial"))`
- L38 _public member_ `bool bContinuation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence", Meta = (PostEditType = "Trivial"))`

#### struct `FStepSequenceRow`  
`struct FStepSequenceRow`  
_L42-58_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public prototype_ `FStepSequenceRow() = default;`
- L48 _public prototype_ `FStepSequenceRow(const FStepSequenceRow&) = default;`
- L49 _public prototype_ `FStepSequenceRow& operator=(const FStepSequenceRow&) = default;`
- L50 _public prototype_ `FStepSequenceRow(FStepSequenceRow&&) = default;`
- L53 _public member_ `TArray<FStepSequenceCell> Cells;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence")`
- L57 _public member_ `bool bRowEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category = "MidiStepSequence")` — If the row is disabled, no notes in that row will play

#### struct `FStepSequenceNote`  
`struct FStepSequenceNote`  
_L61-84_
- reflection: `USTRUCT(BlueprintType)`
- L66 _public prototype_ `FStepSequenceNote() = default;`
- L67 _public prototype_ `FStepSequenceNote(const FStepSequenceNote&) = default;`
- L68 _public prototype_ `FStepSequenceNote& operator=(const FStepSequenceNote&) = default;`
- L69 _public prototype_ `FStepSequenceNote(FStepSequenceNote&&) = default;`
- L72 _public member_ `int32 NoteNumber = 60;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (PostEditType = "Trivial", ClampMin = "0", ClampMax = "127"), Category = "MidiStepSequence")`
- L75 _public member_ `int32 Velocity = 120;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (PostEditType = "Trivial", ClampMin = "0", ClampMax = "127"), Category = "MidiStepSequence")`
- L83 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);` — if additional fields are added to this struct, we need to handle versioning in NetSerialize

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FStepSequenceNote > : public TStructOpsTypeTraitsBase2< FStepSequenceNote >`  
_L87-93_
- inherits: `TStructOpsTypeTraitsBase2<FStepSequenceNote>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L90-92_

#### struct `FStepSequencePage`  
`struct FStepSequencePage`  
_L96-125_
- reflection: `USTRUCT(BlueprintType)`
- L101 _public function_ `FStepSequencePage() : Rows()`
- L105 _public function_ `FStepSequencePage(const FStepSequencePage& Other) : Rows(Other.Rows)`
- L108 _public function_ `FStepSequencePage& operator=(const FStepSequencePage& Other)`
- L113 _public function_ `FStepSequencePage(FStepSequencePage&& Other) noexcept : Rows(MoveTemp(Other.Rows))`
- L116 _public function_ `FStepSequencePage& operator=(FStepSequencePage&& Other)`
- L121 _public prototype_ `~FStepSequencePage() = default;`
- L124 _public member_ `TArray<FStepSequenceRow> Rows;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence")`

#### struct `FStepSequenceTable`  
`struct FStepSequenceTable`  
_L128-188_
- reflection: `USTRUCT(BlueprintType)`
- L139 _public function_ `FStepSequenceTable() : Pages() , Notes()`
- L143 _public function_ `FStepSequenceTable(const FStepSequenceTable& Other) : Pages(Other.Pages) , Notes(Other.Notes) , StepSkipIndex(Other.StepSkipIndex)`
- L148 _public function_ `FStepSequenceTable& operator=(const FStepSequenceTable& Other)`
- L155 _public function_ `FStepSequenceTable(FStepSequenceTable&& Other) noexcept : Pages(MoveTemp(Other.Pages)) , Notes(MoveTemp(Other.Notes)) , StepSkipIndex(Other.StepSkipIndex)`
- L160 _public function_ `FStepSequenceTable& operator=(FStepSequenceTable&& Other)`
- L167 _public prototype_ `~FStepSequenceTable() = default;`
- L169 _public prototype_ `bool IsPageBlank(int32 PageIdx) const;`
- L171 _public prototype_ `int32 GetFirstValidPage(bool bPlayBlankPages) const;`
- L172 _public prototype_ `int32 CalculateNumValidPages(bool bPlayBlankPages) const;`
- L174 _public prototype_ `int32 CalculateAutoPageIndex(int32 TotalPagesProgressed, bool bPlayBlankPages, bool bLoop) const;`
- L177 _public member_ `TArray<FStepSequencePage> Pages;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence")`
- L180 _public member_ `TArray<FStepSequenceNote> Notes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence")`
- L184 _public member_ `int32 StepSkipIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, editfixedsize, Category = "MidiStepSequence")` — If >0, any step at index X will be skipped if X % N == N - 1
- L187 _private prototype_ `void GetUnusedPages(bool bPlayBlankPages, TBitArray<FDefaultBitArrayAllocator>& OutBlankPages) const;`

#### class `UMidiStepSequence`  
`class UMidiStepSequence : public UObject, public IAudioProxyDataFactory`  
_L211-316_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", Meta = (DisplayName = "MIDI Step Sequence"))`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: This class represents a step sequence table. It is used by the MetasSound Step Sequence node to generate midi note on/off messages.
- L217 _public member_ `static const int32 kMinPages = 1;`
- L218 _public member_ `static const int32 kMaxPages = 8;`
- L219 _public member_ `static const int32 kMinRows = 1;`
- L220 _public member_ `static const int32 kMaxRows = 16;`
- L221 _public member_ `static const int32 kMinColumns = 4;`
- L222 _public member_ `static const int32 kMaxColumns = 64;`
- L225 _public member_ `int32 Pages = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetNumPages, meta = (ClampMin = "1", ClampMax = "8"), Category = "MidiStepSequence")`
- L228 _public member_ `int32 Rows = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetNumRows, meta = (ClampMin = "1", ClampMax = "16"), Category = "MidiStepSequence")`
- L231 _public member_ `int32 Columns = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetNumColumns, meta = (ClampMin = "4", ClampMax = "64"), Category = "MidiStepSequence")`
- L233 _public prototype_ `UMidiStepSequence(const FObjectInitializer& Initializer);`
- L235 _public prototype_ `virtual void PostReinitProperties() override;`
- L238 _public prototype_ `void SetNumPages(int32 Count);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L241 _public prototype_ `void SetNumColumns(int32 Count);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L244 _public prototype_ `void SetNumRows(int32 Count);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L247 _public prototype_ `void DisableRowsAbove(int32 FirstDisabledRow);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L250 _public prototype_ `bool SetRowNoteNumber(int32 RowIndex, int32 MidiNoteNumber);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L253 _public prototype_ `bool SetRowVelocity(int32 RowIndex, int32 MidiVelocoty);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L256 _public prototype_ `bool SetStepSkipIndex(int32 StepIndex);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L259 _public prototype_ `FStepSequenceCell SetCell(int32 Row, int32 Column, bool State);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L262 _public prototype_ `FStepSequenceCell SetCellOnPage(int32 Page, int32 Row, int32 Column, bool State);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L265 _public prototype_ `FStepSequenceCell SetCellContinuation(int32 Row, int32 Column, bool bState);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L268 _public prototype_ `FStepSequenceCell SetCellContinuationOnPage(int32 Page, int32 Row, int32 Column, bool bState);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L271 _public prototype_ `FStepSequenceCell GetCell(int32 Row, int32 Column);` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MidiStepSequence")`
- L274 _public prototype_ `FStepSequenceCell GetCellOnPage(int32 Page, int32 Row, int32 Column);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L277 _public prototype_ `FStepSequenceCell ToggleCell(int32 Row, int32 Column);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L280 _public prototype_ `FStepSequenceCell ToggleCellOnPage(int32 Page, int32 Row, int32 Column);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L283 _public prototype_ `void SetStepTable(const FStepSequenceTable& NewStepTable);` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L286 _public function_ `const FStepSequenceTable& GetStepTable() const` — `UFUNCTION(BlueprintCallable, Category = "MidiStepSequence")`
- L289 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L292 _public prototype_ `TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L296 _public member_ `int32 CurrentPageNumber = 1;` — `UPROPERTY(EditAnywhere, Transient, DuplicateTransient,Category = "MidiStepSequence")`
- L297 _public prototype_ `const int32 GetClampedCurrentPageNumber();`
- L298 _public prototype_ `void SetClampedCurrentPageNumber(int32 InPageNumber);`
- L303 _protected member_ `FStepSequenceTable StepTable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStepSequence")`
- L313 _private member_ `TSharedPtr<FStepSequenceTableProxy::QueueType> RenderableSequenceTable;` — Notice here that we cache a pointer the Proxy's "Queue" so we can... 1 - Supply it to all instances of Metasound nodes rendering this data. How? CreateNewProxyData instantiates a NEW unique ptr to an FStepSequenceTableProxy every time it is called. All of those unique proxy instances refer to the same queue... this one that we have cached. 2 - Modify that data in response to changes to this class's UPROPERTIES so that we can hear data changes reflected in the rendered audio.
- L315 _private prototype_ `void UpdateRenderableForNonTrivialChange();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L77 _function_ `friend bool operator==(const FStepSequenceNote& A, const FStepSequenceNote& B)`
- L91 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon65f107f30103`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiStream.h` (Public)


#### struct `HarmonixMetasound::FMidiStreamEvent`  
`struct FMidiStreamEvent`  
_L20-38_
- L22 _public member_ `int32 BlockSampleFrameIndex = 0;`
- L23 _public member_ `int32 TrackIndex = 0;`
- L24 _public member_ `int32 AuthoredMidiTick = 0;`
- L25 _public member_ `int32 CurrentMidiTick = 0;`
- L26 _public member_ `FMidiMsg MidiMessage;`
- L28 _public prototype_ `FMidiStreamEvent(const FMidiVoiceGeneratorBase* Owner, const FMidiMsg& Message);`
- L30 _public prototype_ `FMidiStreamEvent(const uint32 OwnerId, const FMidiMsg& Message);`
- L32 _public function_ `FMidiVoiceId GetVoiceId() const`
- L37 _private member_ `FMidiVoiceId VoiceId;`

#### class `HarmonixMetasound::FMidiStream`  
`class FMidiStream`  
_L40-106_
- L43 _public prototype_ `void SetClock(const FMidiClock& InClock);`
- L44 _public prototype_ `void ResetClock();`
- L45 _public prototype_ `TSharedPtr<const FMidiClock, ESPMode::NotThreadSafe> GetClock() const;`
- L47 _public prototype_ `void PrepareBlock();`
- L49 _public prototype_ `void AddMidiEvent(const FMidiStreamEvent& Event);`
- L50 _public prototype_ `void InsertMidiEvent(const FMidiStreamEvent& Event);`
- L51 _public prototype_ `void AddNoteOffEventOrCancelPendingNoteOn(const FMidiStreamEvent& Event);`
- L52 _public prototype_ `void InsertNoteOffEventOrCancelPendingNoteOn(const FMidiStreamEvent& Event);`
- L54 _public function_ `void SetMidiFile(const FMidiFileProxyPtr& MidiFile)`
- L55 _public prototype_ `const FString* GetMidiTrackText(int32 TrackNumber, int32 TextIndex) const;`
- L58 _public function_ `const TArray<FMidiStreamEvent>& GetEventsInBlock() const`
- L63 _public function_ `int32 GetTicksPerQuarterNote() const`
- L64 _public function_ `void SetTicksPerQuarterNote(int32 InTicksPerQuarterNote)`
- L66 _public typedef_ `using FEventFilter = TFunction<bool(const FMidiStreamEvent&)>;`
- L67 _public function_ `inline static const FEventFilter NoOpFilter = [](const FMidiStreamEvent&)`
- L67 _public member_ `inline static const FEventFilter NoOpFilter = [](const FMidiStreamEvent&) { return true; };`
- L69 _public typedef_ `using FEventTransformer = TFunction<FMidiStreamEvent(const FMidiStreamEvent&)>;`
- L70 _public function_ `inline static const FEventTransformer NoOpTransformer = [](const FMidiStreamEvent& Event)`
- L70 _public member_ `inline static const FEventTransformer NoOpTransformer = [](const FMidiStreamEvent& Event) { return Event; };`
- L72 _public prototype_ `static void Copy( const FMidiStream& From, FMidiStream& To, const FEventFilter& Filter = NoOpFilter, const FEventTransformer& Transformer = NoOpTransformer);`
- L78 _public prototype_ `static void Merge( const FMidiStream& From, FMidiStream& To, const FEventFilter& Filter = NoOpFilter, const FEventTransformer& Transformer = NoOpTransformer);`
- L84 _public prototype_ `static void Merge( const FMidiStream& FromA, const FMidiStream& FromB, FMidiStream& To, const FEventFilter& Filter = NoOpFilter, const FEventTransformer& Transformer = NoOpTransformer);`
- L91 _public prototype_ `bool NoteIsActive(const FMidiStreamEvent& Event) const;`
- L94 _private member_ `FMidiFileProxyPtr MidiFileSourceOfEvents;`
- L95 _private member_ `int32 TicksPerQuarterNote = Harmonix::Midi::Constants::GTicksPerQuarterNoteInt;`
- L97 _private member_ `TArray<FMidiStreamEvent> EventsInBlock;`
- L99 _private member_ `TWeakPtr<const FMidiClock, ESPMode::NotThreadSafe> Clock;`
- L102 _private member_ `TMap<uint32, FMidiVoiceGeneratorBase> GeneratorMap;` — Map to handle re-mapping merged MIDI events, which helps to disambiguate split/transposed notes
- L104 _private prototype_ `void TrackNote(const FMidiStreamEvent& Event);`
- L105 _private member_ `TArray<FMidiStreamEvent> ActiveNotes;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L16 _namespace_ `namespace HarmonixMetasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MidiStutterSequence.h` (Public)


#### struct `FStutterSequenceEntry`  
`struct FStutterSequenceEntry`  
_L17-49_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public prototype_ `FStutterSequenceEntry() = default;`
- L23 _public prototype_ `FStutterSequenceEntry(const FStutterSequenceEntry&) = default;`
- L24 _public prototype_ `FStutterSequenceEntry& operator=(const FStutterSequenceEntry&) = default;`
- L25 _public prototype_ `FStutterSequenceEntry(FStutterSequenceEntry&&) = default;`
- L26 _public function_ `FStutterSequenceEntry(EMusicTimeSpanLengthUnits Spacing, EMusicTimeSpanLengthUnits AudibleDuration, bool Reverse, int32 Count) : Spacing(Spacing) , AudibleDuration(AudibleDuration) , Reverse(Reverse) , Count(Count)`
- L36 _public member_ `EMusicTimeSpanLengthUnits Spacing = EMusicTimeSpanLengthUnits::QuarterNotes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial"))` — Space between stutters
- L40 _public member_ `EMusicTimeSpanLengthUnits AudibleDuration = EMusicTimeSpanLengthUnits::EighthNotes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial"))` — Duration of the audible portion of the stutter
- L44 _public member_ `bool Reverse = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial"))` — Play the audio backwards?
- L48 _public member_ `int32 Count = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial", ClampMin = "1", ClampMax = "64"))` — How many stutters to play with these settings

#### struct `FStutterSequenceTable`  
`struct FStutterSequenceTable`  
_L52-104_
- reflection: `USTRUCT(BlueprintType)`
- L63 _public function_ `FStutterSequenceTable() : Stutters()`
- L66 _public function_ `FStutterSequenceTable(const FStutterSequenceTable& Other) : CaptureDuration(Other.CaptureDuration) , ResetOnCompletion(Other.ResetOnCompletion) , Stutters(Other.Stutters)`
- L71 _public function_ `FStutterSequenceTable& operator=(const FStutterSequenceTable& Other)`
- L78 _public function_ `FStutterSequenceTable(FStutterSequenceTable&& Other) noexcept : CaptureDuration(Other.CaptureDuration) , ResetOnCompletion(Other.ResetOnCompletion) , Stutters(MoveTemp(Other.Stutters))`
- L84 _public function_ `FStutterSequenceTable& operator=(FStutterSequenceTable&& Other)`
- L91 _public prototype_ `~FStutterSequenceTable() = default;`
- L95 _public member_ `EMusicTimeSpanLengthUnits CaptureDuration = EMusicTimeSpanLengthUnits::HalfNotes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial"))` — The amount of audio to tell the sampler node to capture
- L99 _public member_ `bool ResetOnCompletion = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence", Meta = (PostEditType = "Trivial"))` — Reset the Sampler node after the last stutter plays? This will cause the sampler node to start passing its input to its output again.
- L103 _public member_ `TArray<FStutterSequenceEntry> Stutters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStutterSequence")` — A sequence of stutter 'sections'...

#### class `UMidiStutterSequence`  
`class UMidiStutterSequence : public UObject, public IAudioProxyDataFactory`  
_L125-154_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Music", Meta = (DisplayName = "MIDI Stutter Sequence"))`
- inherits: `UObject,IAudioProxyDataFactory`
- desc: This class represents a stutter sequence. It is used by the MetasSound Stutter Sequencer node to generate triggers for a Simple Sampler node to create a classic Stutter Edit effect.
- L132 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L135 _public prototype_ `TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L140 _protected member_ `FStutterSequenceTable StutterTable;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MidiStepSequence")`
- L151 _private member_ `TSharedPtr<FStutterSequenceTableProxy::QueueType> RenderableStutterTable;` — Notice here that we cache a pointer the Proxy's "Queue" so we can... 1 - Supply it to all instances of Metasound nodes rendering this data. How? CreateNewProxyData instantiates a NEW unique ptr to an FStepSequenceTableProxy every time it is called. All of those unique proxy instances refer to the same queue... this one that we have cached. 2 - Modify that data in response to changes to this class's UPROPERTIES so that we can hear data changes reflected in the rendered audio.
- L153 _private prototype_ `void UpdateRenderableForNonTrivialChange();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicLoopConfiguration.h` (Public)


#### struct `FMusicLoopConfiguration`  
`struct FMusicLoopConfiguration`  
_L15-43_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public member_ `bool Enabled = false;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicLoopConfiguration")`
- L24 _public member_ `FMusicTimestamp RegionStart;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicLoopConfiguration")`
- L27 _public member_ `FMusicTimestamp RegionEnd;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicLoopConfiguration")`
- L29 _public prototype_ `FMusicLoopConfiguration() = default;`
- L30 _public function_ `FMusicLoopConfiguration(const Metasound::FOperatorSettings& InSettings, bool InEnabled = false, const FMusicTimestamp& InRegionStart = FMusicTimestamp(), const FMusicTimestamp& InRegionEnd = FMusicTimestamp()) : FMusicLoopConfiguration(InEnabled, InRegionStart, InRegionEnd)`
- L33 _public function_ `FMusicLoopConfiguration(bool InEnabled, const FMusicTimestamp& InRegionStart, const FMusicTimestamp& InRegionEnd) : Enabled(InEnabled) , RegionStart(InRegionStart) , RegionEnd(InRegionEnd)`

#### Free symbols / members of external scopes

- L39 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMusicLoopConfiguration& InConfiguration)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicParameterBlueprintLibrary.h` (Public)


#### class `UMusicParameterBlueprintLibrary`  
`class UMusicParameterBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L18-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L26 _private prototype_ `static void SetMusicTimestamp(UMetasoundParameterPack* Target, FName ParameterName, UPARAM(ref) FMusicTimestamp& Value, ESetParamResult& Result, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L29 _private prototype_ `FMusicTimestamp GetMusicTimestamp(UMetasoundParameterPack* Target, FName ParameterName, ESetParamResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L32 _private prototype_ `bool HasMusicTimestamp(UMetasoundParameterPack* Target, FName Name);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L38 _private prototype_ `static void SetMusicLoopConfiguration(UMetasoundParameterPack* Target, FName ParameterName, UPARAM(ref) FMusicLoopConfiguration& Value, ESetParamResult& Result, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L41 _private prototype_ `FMusicLoopConfiguration GetMusicLoopConfiguration(UMetasoundParameterPack* Target, FName ParameterName, ESetParamResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L44 _private prototype_ `bool HasMusicLoopConfiguration(UMetasoundParameterPack* Target, FName Name);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`
- L50 _private prototype_ `static void SetMusicSeekRequest(UMetasoundParameterPack* Target, FName ParameterName, UPARAM(ref) FMusicSeekRequest& Value, ESetParamResult& Result, bool OnlyIfExists = true);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L53 _private prototype_ `FMusicSeekRequest GetMusicSeekRequest(UMetasoundParameterPack* Target, FName ParameterName, ESetParamResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = "Result"))`
- L56 _private prototype_ `bool HasMusicSeekRequest(UMetasoundParameterPack* Target, FName Name);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundParameterPack", meta = (ExpandEnumAsExecs = ReturnValue))`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicSeekRequest.h` (Public)


#### enum `ESeekPointType`  
`enum class ESeekPointType : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `BarBeat`
- L16 _public enumerator_ `Millisecond`

#### struct `FMusicSeekTarget`  
`struct FMusicSeekTarget`  
_L20-38_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `ESeekPointType Type = ESeekPointType::BarBeat;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport")`
- L29 _public member_ `FMusicTimestamp BarBeat;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport", meta = (EditCondition = "Type == ESeekPointType::BarBeat", EditConditionHides))`
- L32 _public member_ `float Ms = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport", meta = (EditCondition = "Type == ESeekPointType::Millisecond", EditConditionHides))`

#### struct `FMusicSeekRequest`  
`struct FMusicSeekRequest`  
_L41-75_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public member_ `bool EmmediateIfPastFromPoint = true;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport")`
- L50 _public member_ `FMusicTimestamp FromPoint;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport")`
- L53 _public member_ `FMusicTimestamp ToPoint;` — `UPROPERTY(BlueprintReadWrite, Category = "MusicTransport")`
- L55 _public prototype_ `FMusicSeekRequest() = default;`
- L56 _public function_ `FMusicSeekRequest(const Metasound::FOperatorSettings& InSettings, bool InEmmediateIfPastFromPoint = true, const FMusicTimestamp& InFromPoint = FMusicTimestamp(), const FMusicTimestamp& InToPoint = FMusicTimestamp()) : FMusicSeekRequest(InEmmediateIfPastFromPoint, InFromPoint, InToPoint)`
- L59 _public function_ `FMusicSeekRequest(bool InEmmediateIfPastFromPoint, const FMusicTimestamp& InFromPoint, const FMusicTimestamp& InToPoint) : EmmediateIfPastFromPoint(InEmmediateIfPastFromPoint) , FromPoint(InFromPoint) , ToPoint(InToPoint)`
- L65 _public function_ `void OneshotSubmitted()`

#### Free symbols / members of external scopes

- L34 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMusicSeekTarget& InSeekTarget)`
- L71 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FMusicSeekRequest& InSeekRequest)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicTimeInterval.h` (Public)


#### struct `FMusicTimeInterval`  
`struct FMusicTimeInterval`  
_L11-32_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- L15 _public prototype_ `FMusicTimeInterval();`
- L16 _public prototype_ `FMusicTimeInterval(EMidiClockSubdivisionQuantization InInterval, EMidiClockSubdivisionQuantization InOffset, int32 InIntervalMultiplier, int32 InOffsetMultiplier);`
- L19 _public member_ `EMidiClockSubdivisionQuantization Interval = EMidiClockSubdivisionQuantization::Beat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Interval Settings")`
- L22 _public member_ `EMidiClockSubdivisionQuantization Offset = EMidiClockSubdivisionQuantization::Beat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Interval Settings")`
- L25 _public member_ `int32 IntervalMultiplier = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Interval Settings")`
- L28 _public member_ `int32 OffsetMultiplier = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Interval Settings")`
- L30 _public prototype_ `float GetIntervalBeats(const FTimeSignature& TimeSignature) const;`
- L31 _public prototype_ `float GetOffsetBeats(const FTimeSignature& TimeSignature) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L34 _namespace_ `namespace Harmonix`
- L36 _prototype_ `void IncrementTimestampByInterval( FMusicTimestamp& Timestamp, const FMusicTimeInterval& Interval, const FTimeSignature& TimeSignature);` (scope `Harmonix`)
- L41 _prototype_ `void IncrementTimestampByOffset( FMusicTimestamp& Timestamp, const FMusicTimeInterval& Interval, const FTimeSignature& TimeSignature);` (scope `Harmonix`)
- L46 _prototype_ `void IncrementTimestampByBeats( FMusicTimestamp& Timestamp, float Beats, const FTimeSignature& TimeSignature);` (scope `Harmonix`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicTimestamp.h` (Public)


#### class `UMusicTimestampBlueprintLibrary`  
`class UMusicTimestampBlueprintLibrary final : public UBlueprintFunctionLibrary`  
_L16-25_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L21 _private prototype_ `static bool IsMusicTimestamp(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L24 _private prototype_ `static FMusicTimestamp GetMusicTimestamp(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/MusicTransport.h` (Public)


#### enum `HarmonixMetasound::EMusicPlayerTransportRequest`  
`enum class EMusicPlayerTransportRequest : uint8`  
_L16-27_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Prepare`
- L20 _public enumerator_ `Play`
- L21 _public enumerator_ `Pause`
- L22 _public enumerator_ `Continue`
- L23 _public enumerator_ `Stop`
- L24 _public enumerator_ `Kill`
- L25 _public enumerator_ `Seek`
- L26 _public enumerator_ `Count`

#### struct `HarmonixMetasound::FMusicTransportEvent`  
`struct FMusicTransportEvent`  
_L29-33_
- L31 _public member_ `Metasound::FTime Time;`
- L32 _public member_ `EMusicPlayerTransportRequest Request;`

#### class `HarmonixMetasound::FMusicTransportEventStream`  
`class FMusicTransportEventStream`  
_L39-73_
- L42 _public prototype_ `FMusicTransportEventStream(const Metasound::FOperatorSettings& InSettings);`
- L44 _public prototype_ `void AddTransportRequest(EMusicPlayerTransportRequest InRequest, int32 AtSampleIndex);`
- L45 _public prototype_ `void AddSeekRequest(int32 AtSampleIndex, const FMusicSeekTarget& Target);`
- L48 _public prototype_ `void AdvanceBlock();` — Advance internal frame counters by block size.
- L50 _public prototype_ `void Reset();`
- L58 _public typedef_ `using FEventList = TArray<FRequestEvent>;`
- L60 _public function_ `const FEventList& GetTransportEventsInBlock() const`
- L62 _public function_ `const FMusicSeekTarget& GetNextSeekDestination() const`
- L64 _public member_ `static constexpr EMusicPlayerTransportRequest InitialTransportStateRequest = EMusicPlayerTransportRequest::None;`
- L66 _public function_ `EMusicPlayerTransportRequest GetLastTransportStateRequest() const`
- L69 _private member_ `FEventList TransportEventsThisBlock;`
- L70 _private member_ `FMusicSeekTarget NextSeekDestination;`
- L72 _private member_ `EMusicPlayerTransportRequest LastTransportStateRequest = InitialTransportStateRequest;` — The last transport request that would result in a state change (so, *not* Seek)

#### struct `HarmonixMetasound::FMusicTransportEventStream::FRequestEvent`  
`struct FRequestEvent`  
_L52-57_
- L54 _public member_ `int32 SampleIndex;`
- L55 _public member_ `EMusicPlayerTransportRequest Request;`
- L56 _public function_ `bool operator<(const FRequestEvent& other)`

#### enum `HarmonixMetasound::EMusicPlayerTransportState`  
`enum class EMusicPlayerTransportState : uint8`  
_L79-93_
- L81 _public enumerator_ `Invalid` — --> Preparing
- L82 _public enumerator_ `Preparing` — --> Prepared
- L83 _public enumerator_ `Prepared` — --> Starting or Invalid
- L84 _public enumerator_ `Starting` — --> Playing or Paused
- L85 _public enumerator_ `Playing` — --> Pausing or Stopping or Killing
- L86 _public enumerator_ `Seeking` — --> Invalid, Preparing, Prepared, Playing, Paused
- L87 _public enumerator_ `Pausing` — --> Paused
- L88 _public enumerator_ `Paused` — --> Continuing or Stopping or Killing
- L89 _public enumerator_ `Continuing` — --> Playing
- L90 _public enumerator_ `Stopping` — --> Preparing or Prepared or Invalid
- L91 _public enumerator_ `Killing` — --> Preparing or Prepared or Invalid
- L92 _public enumerator_ `NumStates`

#### class `HarmonixMetasound::FMusicTransportControllable`  
`class FMusicTransportControllable`  
_L97-127_
- L100 _public prototype_ `FMusicTransportControllable(EMusicPlayerTransportState InitialState);`
- L102 _public typedef_ `using FTransportInitFn = TUniqueFunction<EMusicPlayerTransportState(EMusicPlayerTransportState)>;`
- L103 _public prototype_ `void Init(const FMusicTransportEventStream& TransportEventStream, FTransportInitFn&& InitFn);`
- L105 _public function_ `EMusicPlayerTransportState GetTransportState() const`
- L106 _public function_ `void SetTransportState(EMusicPlayerTransportState NewState)`
- L107 _public prototype_ `EMusicPlayerTransportState GetNextTransportState(EMusicPlayerTransportState DesiredState) const;`
- L109 _public typedef_ `using TransportSpanProcessor = TUniqueFunction<EMusicPlayerTransportState(int32,int32,EMusicPlayerTransportState)>;`
- L111 _public typedef_ `using TransportSpanPostProcessor = TUniqueFunction<void(int32, int32, EMusicPlayerTransportState)>;` — post processor gets called immediately after the SpanProcessor so that the TransportState has been updated
- L112 _public prototype_ `void ExecuteTransportSpans(FMusicTransportEventStreamReadRef& InTransportPin, int32 InBlockSize, TransportSpanProcessor& Callback);`
- L113 _public prototype_ `void ExecuteTransportSpans(FMusicTransportEventStreamReadRef& InTransportPin, int32 InBlockSize, TransportSpanProcessor& Callback, TransportSpanPostProcessor& PostProcessor);`
- L115 _public prototype_ `static FString StateToString(EMusicPlayerTransportState S);`
- L118 _protected prototype_ `EMusicPlayerTransportState GetDesiredState(EMusicPlayerTransportRequest Request) const;`
- L120 _protected prototype_ `bool IsEffectivelyStopped() const;`
- L122 _protected function_ `bool ReceivedSeekWhileStopped() const`
- L125 _private member_ `EMusicPlayerTransportState TransportState = EMusicPlayerTransportState::Invalid;`
- L126 _private member_ `bool bReceivedSeekWhileStopped = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L14 _namespace_ `namespace HarmonixMetasound`
- L95 _prototype_ `FString MusicPlayerTransportStateToString(EMusicPlayerTransportState State);` (scope `HarmonixMetasound`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/TimeSignature.h` (Public)


#### class `UTimeSignatureBlueprintLibrary`  
`class UTimeSignatureBlueprintLibrary final : public UBlueprintFunctionLibrary`  
_L15-24_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _private prototype_ `static bool IsTimeSignature(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L23 _private prototype_ `static FTimeSignature GetTimeSignature(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/DataTypes/TimeSyncOption.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/MidiChannelFilter.h` (Public)


#### class `Harmonix::Midi::Ops::FMidiChannelFilter`  
`class FMidiChannelFilter`  
_L17-46_
- desc: Includes MIDI events from enabled channels only
- L25 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream, HarmonixMetasound::FMidiStream& OutStream);` — Pass the filtered events from the input stream to the output stream @param InStream The MIDI stream to filter @param OutStream The filtered MIDI stream
- L32 _public prototype_ `void SetChannelEnabled(uint8 Channel, bool Enabled);` — Enable or disable a channel (or all channels) @param Channel The MIDI channel (1-16, 0 is all channels) @param Enabled Whether the channel(s) should be enabled
- L39 _public prototype_ `bool GetChannelEnabled(uint8 Channel) const;` — Find out if a channel is enabled @param Channel The MIDI channel (1-16, 0 is all channels) @return true if the channel is (or all channels are) enabled
- L43 _private member_ `uint16 EnabledChannels = AllChannelsOff;` — bitfield to store which channels are enabled
- L45 _private member_ `FStuckNoteGuard StuckNoteGuard;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L12 _namespace_ `namespace Harmonix`
- L12 _namespace_ `namespace Midi` (scope `Harmonix`)
- L12 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/MidiNoteFilter.h` (Public)


#### class `Harmonix::Midi::Ops::FMidiNoteFilter`  
`class FMidiNoteFilter`  
_L18-57_
- desc: Filters MIDI note events based on note number and velocity
- L26 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream, HarmonixMetasound::FMidiStream& OutStream);` — Pass the filtered events from the input stream to the output stream @param InStream The MIDI stream to filter @param OutStream The filtered MIDI stream
- L31 _public member_ `Dsp::Parameters::FBoolParameter IncludeOtherEvents{ true };` — Includes non-note events from the input into the output
- L33 _public typedef_ `using FMidiDataParam = Dsp::Parameters::TParameter<uint8>;`
- L38 _public member_ `FMidiDataParam MinNoteNumber{ 0, 127, 0 };` — The minimum note number the note can have to be included (inclusive)
- L43 _public member_ `FMidiDataParam MaxNoteNumber{ 0, 127, 127 };` — The maximum note number the note can have to be included (inclusive)
- L48 _public member_ `FMidiDataParam MinVelocity{ 0, 127, 0 };` — The minimum velocity the note can have to be included (inclusive)
- L53 _public member_ `FMidiDataParam MaxVelocity{ 0, 127, 127 };` — The maximum velocity the note can have to be included (inclusive)
- L56 _private member_ `FStuckNoteGuard StuckNoteGuard;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L13 _namespace_ `namespace Harmonix`
- L13 _namespace_ `namespace Midi` (scope `Harmonix`)
- L13 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/MidiOps.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMidiOps, Log, All) namespace Harmonix::Midi::Ops { using FMidiTrackIndex = uint16; constexpr uint16 AllChannelsOn = 0xffff; constexpr uint16 AllChannelsOff = 0; uint16 MidiChannelToBitmask(uint8 MidiChannel); }`
- L9 _namespace_ `namespace Harmonix`
- L9 _namespace_ `namespace Midi` (scope `Harmonix`)
- L9 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)
- L11 _typedef_ `using FMidiTrackIndex = uint16;` (scope `Harmonix::Midi::Ops`)
- L13 _variable_ `constexpr uint16 AllChannelsOn = 0xffff;` (scope `Harmonix::Midi::Ops`)
- L14 _variable_ `constexpr uint16 AllChannelsOff = 0;` (scope `Harmonix::Midi::Ops`)
- L21 _prototype_ `uint16 MidiChannelToBitmask(uint8 MidiChannel);` (scope `Harmonix::Midi::Ops`) — Get a bitmask from a MIDI channel number (e.g. for use when creating a bitfield for disabling/enabling channels) @param MidiChannel The MIDI channel (1-16, or 0 for all) @return The bitmask for the channel(s)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/MidiStreamWriter.h` (Public)


#### class `Harmonix::Midi::Ops::FMidiStreamWriter`  
`class FMidiStreamWriter`  
_L20-48_
- desc: Write the midi events from a midi stream into a midi file
- L24 _public prototype_ `FMidiStreamWriter(TUniquePtr<FArchive>&& Archive);`
- L32 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream);` — Writes the midi events in the midi stream Midi events are appended to the existing midi events @param InStream The MIDI stream to read from
- L40 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream, int32 FirstTickToProcess, int32 LastTickToProcess);` — Writes the midi events in the midi stream Midi events are appended to the existing midi events @param InStream The MIDI stream to read from
- L44 _private member_ `TUniquePtr<FArchive> Archive;`
- L45 _private member_ `TMap<int32, FMidiTrack> MidiTracks;`
- L46 _private member_ `int32 NextWriteTick = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L9 _namespace_ `namespace HarmonixMetasound`
- L15 _namespace_ `namespace Harmonix`
- L15 _namespace_ `namespace Midi` (scope `Harmonix`)
- L15 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/MidiTrackFilter.h` (Public)


#### class `Harmonix::Midi::Ops::FMidiTrackFilter`  
`class FMidiTrackFilter`  
_L16-41_
- desc: Filters MIDI events based on which track they're on
- L24 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream, HarmonixMetasound::FMidiStream& OutStream);` — Pass the filtered events from the input stream to the output stream @param InStream The MIDI stream to filter @param OutStream The filtered MIDI stream
- L33 _public prototype_ `void SetTrackRange(uint16 InMinTrackIdx, uint16 InMaxTrackIdx, bool InIncludeConductorTrack);` — Set the range of tracks to include. Track 0 is reserved as the "conductor" track, which only contains timing information. The first track with notes and other messages on it will be track 1. @param InMinTrackIdx The first track to include in the range of tracks (inclusive). @param InMaxTrackIdx The last track to include in th range of tracks (inclusive). @param InIncludeConductorTrack Whether or not to include the conductor track (track 0)
- L36 _private member_ `uint16 MinTrackIdx = 0;`
- L37 _private member_ `uint16 MaxTrackIdx = 0;`
- L38 _private member_ `bool IncludeConductorTrack = false;`
- L40 _private member_ `FStuckNoteGuard StuckNoteGuard;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L11 _namespace_ `namespace Harmonix`
- L11 _namespace_ `namespace Midi` (scope `Harmonix`)
- L11 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/PulseGenerator.h` (Public)


#### class `Harmonix::Midi::Ops::FPulseGenerator`  
`class FPulseGenerator`  
_L17-90_
- L20 _public prototype_ `virtual ~FPulseGenerator() = default;`
- L22 _public prototype_ `void Enable(bool bEnable);`
- L27 _public prototype_ `void SetInterval(const FMusicTimeInterval& NewInterval);` — Set the interval for each pulse in Musical Time.
- L28 _public function_ `FMusicTimeInterval GetInterval() const`
- L39 _public prototype_ `void SetDutyCycle(float InDutyCycle);` — Set the Duty Cycle of the pulse The Duty Cycle defines the duration of the pulse as a percentage of the Interval. for example: - Duty Cycle = 1.0: pulse will span the entire length of the interval - Duty Cycle = 0.5: pulse will span half the length of the interval
- L40 _public function_ `float GetDutyCycle() const`
- L42 _public prototype_ `virtual void Reset();`
- L50 _public prototype_ `void Process( const HarmonixMetasound::FMidiClock& MidiClock, const TFunctionRef<void(const FPulseInfo&)>& TriggerPulseOn, const TFunctionRef<void(const FPulseInfo&)>& TriggerPulseOff);`
- L56 _protected member_ `bool Enabled{ true };`
- L59 _protected member_ `FMusicTimeInterval Interval{};` — the interval of the pulse
- L62 _protected member_ `FTimeSignature CurrentTimeSignature{};` — cache the time signature from the clock to calculate seconds from musical time
- L65 _protected member_ `float DutyCycle = 1.0f;` — pulse width as a percentage of the current interval
- L89 _protected member_ `TArray<FPulse> NextPulses;`

#### struct `Harmonix::Midi::Ops::FPulseGenerator::FPulseInfo`  
`struct FPulseInfo`  
_L44-48_
- L46 _public member_ `int32 BlockFrameIndex;`
- L47 _public member_ `int32 Tick;`

#### struct `Harmonix::Midi::Ops::FPulseGenerator::FPulse`  
`struct FPulse`  
_L67-87_
- L75 _public member_ `FMusicTimestamp Timestamp;`
- L76 _public member_ `EType Type = EType::On;`
- L78 _public function_ `static FPulse On(const FMusicTimestamp& Timestamp)`
- L83 _public function_ `static FPulse Off(const FMusicTimestamp& Timestamp)`

#### enum `Harmonix::Midi::Ops::FPulseGenerator::FPulse::EType`  
`enum class EType`  
_L69-73_
- L71 _public enumerator_ `Off = 0`
- L72 _public enumerator_ `On = 1`

#### class `Harmonix::Midi::Ops::FMidiPulseGenerator`  
`class FMidiPulseGenerator : public FPulseGenerator`  
_L92-115_
- inherits: `FPulseGenerator`
- L95 _public prototype_ `virtual ~FMidiPulseGenerator() override = default;`
- L97 _public member_ `Dsp::Parameters::TParameter<uint8> Channel{ 1, 16, 1 };`
- L99 _public member_ `Dsp::Parameters::TParameter<uint16> Track{ 1, UINT16_MAX, 1 };`
- L101 _public member_ `Dsp::Parameters::TParameter<uint8> NoteNumber{ 0, 127, 60 };`
- L103 _public member_ `Dsp::Parameters::TParameter<uint8> Velocity{ 0, 127, 127 };`
- L105 _public prototype_ `virtual void Reset() override;`
- L107 _public prototype_ `void Process(const HarmonixMetasound::FMidiClock& MidiClock, HarmonixMetasound::FMidiStream& OutStream);`
- L110 _private prototype_ `void PulseNoteOn(const int32 BlockFrameIndex, const int32 PulseTick, HarmonixMetasound::FMidiStream& OutStream);`
- L111 _private prototype_ `void PulseNoteOff(const int32 BlockFrameIndex, const int32 PulseTick, HarmonixMetasound::FMidiStream& OutStream);`
- L113 _private member_ `FMidiVoiceGeneratorBase VoiceGenerator{};`
- L114 _private member_ `TOptional<HarmonixMetasound::FMidiStreamEvent> LastNoteOn;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L15 _namespace_ `namespace Harmonix`
- L15 _namespace_ `namespace Midi` (scope `Harmonix`)
- L15 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MidiOps/StuckNoteGuard.h` (Public)


#### class `Harmonix::Midi::Ops::FStuckNoteGuard`  
`class FStuckNoteGuard`  
_L14-40_
- desc: Tracks incoming note messages and sends note offs when a note would become "stuck" because of a filter change
- L17 _public typedef_ `using FIncludeNotePredicate = TFunctionRef<bool(const HarmonixMetasound::FMidiStreamEvent& Event)>;`
- L25 _public prototype_ `void Process(const HarmonixMetasound::FMidiStream& InStream, HarmonixMetasound::FMidiStream& OutStream, const FIncludeNotePredicate& Predicate);` — Track incoming note messages and send note offs for notes that would have become "stuck" because the caller's filter changed. @param InStream The input MIDI stream @param OutStream The output MIDI stream @param Predicate The predicate which indicates whether an event is still included in the caller's filter
- L27 _public typedef_ `using FUnstickNoteFn = TFunction<void(const HarmonixMetasound::FMidiStreamEvent&)>;`
- L34 _public prototype_ `void UnstickNotes(const HarmonixMetasound::FMidiStream& StreamToCompare, const FUnstickNoteFn& UnstickNoteFn);` — If any active notes we're tracking are no longer present in the input stream, trigger a function so the caller can turn them off. @param StreamToCompare The stream to use to check whether an active note has disappeared @param UnstickNoteFn The function to call when an active note has disappeared from the incoming stream
- L37 _private prototype_ `void TrackNotes(const HarmonixMetasound::FMidiStream& InStream, const FIncludeNotePredicate& Predicate);`
- L39 _private member_ `TArray<HarmonixMetasound::FMidiStreamEvent> ActiveNotes;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L9 _namespace_ `namespace Harmonix`
- L9 _namespace_ `namespace Midi` (scope `Harmonix`)
- L9 _namespace_ `namespace Ops` (scope `Harmonix::Midi`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicClock/MusicClock.h` (Public)


#### class `UMusicClock`  
`class UMusicClock : public UObject`  
_L33-281_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A read-only view into a music source's time. UMusicClock does not own or control playback. It observes an IMusicSource and provides: - Current/previous musical position (FMidiSongPos) - Tempo, time signature, BPM queries - Beat/bar/section event broadcasting - Song map delegation for time conversions A single UMusicClock represents a single time stream with no ECalibratedMusicTimebase parameter. For calibrated offsets (experienced, video render, etc.) use UOffsetMusicSource feeding into a separate UMusicClock.
- L38 _public prototype_ `UMusicClock();`
- L39 _public prototype_ `virtual void BeginDestroy() override;`
- L43 _public prototype_ `void SetSource(const TScriptInterface<IMusicSource>& InSource);` — `UFUNCTION(BlueprintCallable, Category = "MusicClock")` — Bind this clock to a music source. The clock becomes a read-only view into that source.
- L47 _public prototype_ `TScriptInterface<IMusicSource> GetSource() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the source this clock is bound to.
- L54 _public prototype_ `virtual void UpdateForGameFrame();` — Update the clock for the current game frame. Called by the update subsystem. Pulls position from the source, computes deltas, and broadcasts events.
- L60 _public prototype_ `virtual EMusicClockState GetState() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the current clock state (Stopped, Paused, Running).
- L66 _public prototype_ `const FMidiSongPos& GetCurrentSongPos() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the current musical position for this frame.
- L70 _public prototype_ `const FMidiSongPos& GetPreviousSongPos() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the previous frame's musical position.
- L74 _public prototype_ `float GetSecondsIncludingCountIn() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Time from the beginning of the authored music content, including count-in/pickup bars.
- L78 _public prototype_ `float GetSecondsFromBarOne() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Time from Bar 1 Beat 1 (the classic "start of the song"), excluding count-in/pickup.
- L82 _public prototype_ `float GetBarsIncludingCountIn() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional total bars from the beginning, including count-in.
- L86 _public prototype_ `float GetBeatsIncludingCountIn() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional total beats from the beginning, including count-in.
- L93 _public prototype_ `FMusicTimestamp GetCurrentTimestamp() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the current musical timestamp (Bar + Beat). Bar 1, Beat 1.0 is the beginning of the song after count-in.
- L99 _public prototype_ `float GetCurrentTempo() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current tempo in MIDI quarter notes per minute.
- L103 _public prototype_ `float GetCurrentBeatsPerMinute() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current BPM in true beats (not quarter notes).
- L107 _public prototype_ `float GetCurrentBeatsPerSecond() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current beats per second, accounting for tempo, time signature, and speed.
- L111 _public prototype_ `float GetCurrentBarsPerSecond() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current bars per second, accounting for tempo, time signature, and speed.
- L115 _public prototype_ `float GetCurrentClockAdvanceRate() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Current playback speed multiplier from the source.
- L119 _public prototype_ `void GetCurrentTimeSignature(int& OutNumerator, int& OutDenominator) const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the current time signature as numerator and denominator.
- L125 _public prototype_ `FString GetCurrentSectionName() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Name of the current song section (from MIDI section markers).
- L129 _public prototype_ `int32 GetCurrentSectionIndex() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Index of the current section in the section map.
- L133 _public prototype_ `float GetCurrentSectionStartMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Start time of the current section in milliseconds.
- L137 _public prototype_ `float GetCurrentSectionLengthMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Length of the current section in milliseconds.
- L144 _public prototype_ `float GetDistanceFromCurrentBeat() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance past the most recent beat (0.0 = exactly on beat).
- L148 _public prototype_ `float GetDistanceToNextBeat() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance until the next beat (0.0 = exactly on next beat).
- L152 _public prototype_ `float GetDistanceToClosestBeat() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance to the closest beat (past or future), always <= 0.5.
- L156 _public prototype_ `float GetDistanceFromCurrentBar() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance past the most recent bar (0.0 = exactly on bar).
- L160 _public prototype_ `float GetDistanceToNextBar() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance until the next bar.
- L164 _public prototype_ `float GetDistanceToClosestBar() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional distance to the closest bar (past or future), always <= 0.5.
- L170 _public prototype_ `float GetDeltaBar() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional bars advanced this frame.
- L174 _public prototype_ `float GetDeltaBeat() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Fractional beats advanced this frame.
- L180 _public prototype_ `bool LoopedThisFrame() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Whether the source crossed a loop boundary this frame.
- L184 _public prototype_ `bool SeekedThisFrame() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Whether the source performed a non-contiguous time jump this frame.
- L190 _public prototype_ `virtual bool IsLooping() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Whether the source is looping.
- L194 _public prototype_ `virtual float GetLoopStartMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Start of loop region in ms. Only meaningful if IsLooping().
- L198 _public prototype_ `virtual float GetLoopLengthMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Length of loop region in ms. Only meaningful if IsLooping().
- L203 _public prototype_ `virtual const ISongMapEvaluator* GetSongMaps() const;` — Get the song maps from the bound source, for time<->beat conversions.
- L209 _public prototype_ `float GetSongLengthMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Total length of the song in milliseconds.
- L213 _public prototype_ `float GetSongRemainingMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Remaining time until the end of the song in milliseconds.
- L219 _public prototype_ `TOptional<FVector> TryGetAudioSourceLocation() const;` — `UFUNCTION(BlueprintPure, Category = "MusicClock")` — Get the world-space location of the audio source, if available.
- L224 _public member_ `FMusicClockBeatEvent BeatEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L227 _public member_ `FMusicClockBarEvent BarEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L230 _public member_ `FMusicClockSectionEvent SectionEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L233 _public member_ `FMusicClockPlayStateEvent PlayStateEvent;` — `UPROPERTY(BlueprintAssignable, Category = "MusicClock")`
- L236 _public prototype_ `FString GetDisplayName() const;`
- L242 _protected member_ `TWeakObjectPtr<UObject> SourceObject;` — Weak reference to the source UObject. Does not prevent GC.
- L245 _protected member_ `IMusicSource* SourceInterfaceCache = nullptr;` — Cached interface pointer — valid only when SourceObject is valid.
- L248 _protected prototype_ `IMusicSource* GetValidSource() const;` — Get the source if still alive, or nullptr.
- L251 _protected member_ `FMidiSongPos CurrentPos;`
- L252 _protected member_ `FMidiSongPos PrevPos;`
- L254 _protected member_ `float DeltaBarF = 0.f;`
- L255 _protected member_ `float DeltaBeatF = 0.f;`
- L257 _protected member_ `float Tempo = 0.f;`
- L258 _protected member_ `int32 TimeSignatureNum = 0;`
- L259 _protected member_ `int32 TimeSignatureDenom = 0;`
- L260 _protected member_ `float CurrentBeatsPerSecondCached = 0.f;`
- L261 _protected member_ `float CurrentBarsPerSecondCached = 0.f;`
- L262 _protected member_ `float ClockAdvanceRate = 1.f;`
- L265 _protected member_ `int32 LastBroadcastBar = -1;` — Event broadcasting state
- L266 _protected member_ `int32 LastBroadcastBeat = -1;`
- L267 _protected member_ `FSongSection LastBroadcastSection;`
- L269 _protected member_ `uint64 LastUpdateFrame = 0;`
- L271 _protected member_ `EMusicClockState CachedClockState = EMusicClockState::Stopped;`
- L273 _protected member_ `bool bLoopedThisFrame = false;`
- L274 _protected member_ `bool bSeekedThisFrame = false;`
- L277 _protected prototype_ `void UpdatePlaybackRate(const FMidiSongPos& SongPos, float InClockAdvanceRate);` — Update cached tempo, time signature, and derived rates when the song position changes.
- L280 _protected prototype_ `void BroadcastSongPosChanges();` — Broadcast beat, bar, and section events if thresholds were crossed this frame.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMusicClockBeatEvent, int, BeatNumber, int, BeatInBar);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMusicClockBeatEvent, int, BeatNumber, int, BeatInBar);`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicClockBarEvent, int, BarNumber);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicClockBarEvent, int, BarNumber);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMusicClockSectionEvent, const FString&, SectionName, float, SectionStartMs, float, SectionLengthMs);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMusicClockSectionEvent, const FString&, SectionName, float, SectionStartMs, float, SectionLengthMs);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicClockPlayStateEvent, EMusicClockState, State);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMusicClockPlayStateEvent, EMusicClockState, State);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicClock/MusicClockState.h` (Public)


#### enum `EMusicClockState`  
`enum class EMusicClockState : uint8`  
_L7-12_
- reflection: `UENUM(BlueprintType)`
- L9 _public enumerator_ `Stopped`
- L10 _public enumerator_ `Paused`
- L11 _public enumerator_ `Running`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicClock/TimeSource.h` (Public)


#### enum `Harmonix::ESourceState`  
`enum class ESourceState : uint8`  
_L10-16_
- L12 _public enumerator_ `Stopped`
- L13 _public enumerator_ `Preparing` — Intent to run, but no data available yet (e.g., Metasound not yet connected)
- L14 _public enumerator_ `Paused`
- L15 _public enumerator_ `Running`

#### enum `Harmonix::ESourceEvent`  
`enum class ESourceEvent : uint8`  
_L18-28_
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `Start`
- L22 _public enumerator_ `Advance`
- L23 _public enumerator_ `Stop`
- L24 _public enumerator_ `Pause`
- L25 _public enumerator_ `Continue`
- L26 _public enumerator_ `Seek`
- L27 _public enumerator_ `Loop`

#### class `Harmonix::ITimeSource`  
`class ITimeSource`  
_L33-108_
- desc: Base class for Time Sources used by the Runtime Music Clock
- L36 _public function_ `virtual ~ITimeSource()`
- L47 _public prototype_ `static ESourceEvent SourceEventFromStateTransition(ESourceState PrevState, ESourceState NewState);` — Determine the source event from a given state transition e.g. Stopped => Running, return ESourceEvent::Start @param PrevState @param NewState @return The source event representing the state transition
- L50 _public prototype_ `virtual FString GetDisplayName() const = 0;` — @return DisplayName of this time source for debugging
- L53 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const = 0;` — @return The location of the Audio Source for this Time Source
- L61 _public prototype_ `virtual void Update() = 0;` — Used to update the time source once per frame CurrentTime, CurrentSourceState, and LatestSourceEvent Should all be updated & valid for this frame when Update is called
- L69 _public prototype_ `virtual double GetCurrentTime() const = 0;` — Get the current tme of this time source Is updated every frame via Update @return Current Time in Seconds
- L76 _public prototype_ `virtual float GetSpeed() const = 0;` — Get the speed at which time is advancing @return Speed
- L83 _public prototype_ `virtual ESourceState GetCurrentSourceState() const = 0;` — Get whether the source is Running, Stopped, or Paused @return The Current State of the Source
- L92 _public prototype_ `virtual ESourceEvent GetLatestSourceEvent() const = 0;` — Retrieve the latest "Event" from this source Whether it "Advanced", "Stopped", "Continued", etc. Also whether it "Seeked" or "Looped" @return The Latest Event of the Source
- L98 _public function_ `virtual void RequestStart(float StartTime = 0.f)`
- L99 _public function_ `virtual void RequestStop()`
- L100 _public function_ `virtual void RequestPause()`
- L101 _public function_ `virtual void RequestContinue()`
- L104 _public function_ `virtual void RequestSeek(float TimeInSeconds)` — Seek to an absolute time position in seconds. Default is no-op.
- L107 _public function_ `virtual void RequestSetSpeed(float InSpeed)` — Set the playback speed multiplier. Default is no-op.

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L8 _namespace_ `namespace Harmonix`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicClock/TransportContoller.h` (Public)


#### enum `Harmonix::ETransportRequest`  
`enum class ETransportRequest : uint8`  
_L7-15_
- L9 _public enumerator_ `None`
- L10 _public enumerator_ `Play`
- L11 _public enumerator_ `Pause`
- L12 _public enumerator_ `Continue`
- L13 _public enumerator_ `Stop`
- L14 _public enumerator_ `Seek`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Harmonix`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicClock/WorldTimeSourceController.h` (Public)


#### class `Harmonix::FWorldTimeSourceController`  
`class FWorldTimeSourceController : public ITimeSource`  
_L19-71_
- inherits: `ITimeSource`
- desc: A time source driven by UWorld delta time. Provides a simple wall-clock time stream suitable for non-audio-driven use cases. Supports transport control (Start/Stop/Pause/Continue/Seek) and variable speed playback. Time advances by the world's delta time each frame, scaled by the speed multiplier and time dilation.
- L23 _public prototype_ `FWorldTimeSourceController(UObject* InContextObj);`
- L25 _public prototype_ `virtual FString GetDisplayName() const override;`
- L27 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L29 _public prototype_ `virtual void Update() override;`
- L31 _public prototype_ `virtual ESourceState GetCurrentSourceState() const override;`
- L33 _public prototype_ `virtual ESourceEvent GetLatestSourceEvent() const override;`
- L35 _public prototype_ `virtual double GetCurrentTime() const override;`
- L37 _public prototype_ `virtual float GetSpeed() const override;`
- L40 _public prototype_ `void SetSpeed(float InSpeed);` — Set the playback speed multiplier. Clamped to [0.01, 10.0].
- L43 _public prototype_ `void Start(float StartTime = 0.0f);` — Start playback from the given time in seconds.
- L44 _public prototype_ `void Stop();`
- L45 _public prototype_ `void Pause();`
- L46 _public prototype_ `void Continue();`
- L49 _public function_ `virtual void RequestStart(float StartTime = 0.f) override` — ITimeSource optional transport
- L50 _public function_ `virtual void RequestStop() override`
- L51 _public function_ `virtual void RequestPause() override`
- L52 _public function_ `virtual void RequestContinue() override`
- L53 _public function_ `virtual void RequestSeek(float TimeInSeconds) override`
- L54 _public function_ `virtual void RequestSetSpeed(float InSpeed) override`
- L57 _public prototype_ `void Seek(float InSeekTime);` — Seek to an absolute time position in seconds.
- L61 _private prototype_ `double GetDeltaTime() const;`
- L63 _private member_ `float Speed = 1.0f;`
- L64 _private member_ `double RunTimeSeconds = 0.0;`
- L65 _private member_ `double SeekRequestTime = 0.0;`
- L66 _private member_ `ETransportRequest TransportRequest = ETransportRequest::None;`
- L67 _private member_ `ESourceEvent LatestSourceEvent = ESourceEvent::None;`
- L68 _private member_ `ESourceState CurrentSourceState = ESourceState::Stopped;`
- L70 _private member_ `FWeakObjectPtr ContextObj;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Harmonix`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/MetasoundMusicSource.h` (Public)


#### class `UMetasoundMusicSource`  
`class UMetasoundMusicSource : public UObject, public IMusicSource`  
_L49-216_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMusicSource`
- desc: A music source driven by a Metasound's MIDI clock output. Connects to a Metasound via UAudioComponent, reads the MIDI clock history ring buffer produced by the audio render thread, and smooths it into a game-thread-rate position suitable for gameplay. Produces a single time stream: the smoothed audio render position. Calibration offsets (experienced time, video render time) should be applied externally via UOffsetMusicSource. State is derived from the Metasound's actual transport state, not from explicit Start/Stop calls. If the AudioComponent starts playing externally, the source detects it and reports Running. Transport methods on IMusicSource are no-ops — control the Metasound through its AudioComponent or Metasound interfaces directly. Reports Preparing when connected to an AudioComponent but the generator is not yet attached or no clock history is available.
- L55 _public prototype_ `virtual void BeginDestroy() override;`
- L64 _public prototype_ `bool ConnectToAudioComponent( UAudioComponent* InAudioComponent, FName OutputPinName = "MID` — Connect to a Metasound on an audio component. @param InAudioComponent   The audio component playing a MetaSound. @param OutputPinName      The name of the MIDI Clock output pin on the MetaSound. @return true if connection was initiated (may complete asynchronously).
- L69 _public prototype_ `void Disconnect();` — Disconnect from the Metasound and release all handles.
- L73 _public prototype_ `virtual void Start() override;`
- L74 _public prototype_ `virtual void Pause() override;`
- L75 _public prototype_ `virtual void Continue() override;`
- L76 _public prototype_ `virtual void Stop() override;`
- L78 _public prototype_ `virtual Harmonix::ESourceState GetSourceState() const override;`
- L79 _public prototype_ `virtual Harmonix::ESourceEvent GetLatestSourceEvent() const override;`
- L81 _public prototype_ `virtual const FMidiSongPos& GetCurrentSongPos() const override;`
- L82 _public prototype_ `virtual const FMidiSongPos& GetPreviousSongPos() const override;`
- L83 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const override;`
- L84 _public prototype_ `virtual float GetCurrentClockAdvanceRate() const override;`
- L86 _public prototype_ `virtual bool LoopedThisFrame() const override;`
- L87 _public prototype_ `virtual bool SeekedThisFrame() const override;`
- L89 _public prototype_ `virtual bool IsLooping() const override;`
- L90 _public prototype_ `virtual float GetLoopStartMs() const override;`
- L91 _public prototype_ `virtual float GetLoopLengthMs() const override;`
- L93 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L95 _public prototype_ `virtual void Update() override;`
- L98 _public prototype_ `virtual FString GetDisplayName() const override;`
- L104 _private member_ `FName MetasoundOutputName;`
- L105 _private member_ `TWeakObjectPtr<UAudioComponent> AudioComponentToWatch;`
- L106 _private member_ `TStrongObjectPtr<UMetasoundGeneratorHandle> CurrentGeneratorHandle;`
- L107 _private member_ `TWeakPtr<Metasound::FMetasoundGenerator> UnderlyingGenerator;`
- L109 _private member_ `Metasound::Frontend::FAnalyzerAddress MidiSongPosAnalyzerAddress;`
- L111 _private member_ `UMetasoundGeneratorHandle::FOnAttached::FDelegate OnAttachedDelegate;`
- L112 _private member_ `UMetasoundGeneratorHandle::FOnDetached::FDelegate OnDetachedDelegate;`
- L114 _private member_ `FDelegateHandle GeneratorAttachedCallbackHandle;`
- L115 _private member_ `FDelegateHandle GeneratorDetachedCallbackHandle;`
- L116 _private member_ `FDelegateHandle GeneratorIOUpdatedCallbackHandle;`
- L117 _private member_ `FDelegateHandle GraphChangedCallbackHandle;`
- L121 _private member_ `UMidiClockUpdateSubsystem::FClockHistoryPtr ClockHistory;`
- L122 _private member_ `HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor SmoothedClockHistoryCursor;`
- L123 _private member_ `TSharedPtr<const HarmonixMetasound::Analysis::FSongMapChain> CurrentMapChain;`
- L134 _private member_ `FSmoothedClockState SmoothedState;`
- L136 _private member_ `double RenderStartWallClockTimeSeconds = 0.0;`
- L137 _private member_ `double LastRefreshWallClockTimeSeconds = 0.0;`
- L138 _private member_ `double DeltaSecondsBetweenRefreshes = 0.0;`
- L139 _private member_ `Metasound::FSampleCount RenderStartSampleCount {0};`
- L141 _private member_ `static const int kFramesOfErrorHistory = 10;`
- L142 _private member_ `FLocalMinimumMagnitudeTracker<double, kFramesOfErrorHistory> ErrorTracker;`
- L143 _private member_ `double SyncSpeed = 1.0;`
- L145 _private member_ `float RenderSmoothingLagSeconds = 0.030f;`
- L149 _private member_ `FMidiSongPos CurrentPos;`
- L150 _private member_ `FMidiSongPos PrevPos;`
- L152 _private member_ `float CurrentAdvanceRate = 1.f;`
- L153 _private member_ `int32 LastTickSeen = 0;`
- L156 _private member_ `Harmonix::ESourceState CachedSourceState = Harmonix::ESourceState::Stopped;` — Cached source state, derived from clock history transport each frame.
- L158 _private member_ `bool bSeekDetected = false;`
- L159 _private member_ `bool bLoopDetected = false;`
- L164 _private prototype_ `bool AttemptToConnect(UAudioComponent* InAudioComponent);` — Try to create a generator handle and wire up analyzer callbacks for the watched audio component.
- L167 _private prototype_ `void DetachAllCallbacks();` — Remove all generator handle callbacks.
- L170 _private prototype_ `void OnGeneratorAttached();` — Generator lifecycle callbacks
- L171 _private prototype_ `void OnGeneratorDetached();`
- L172 _private prototype_ `void OnGraphSet();`
- L173 _private prototype_ `void OnGeneratorIOUpdatedWithChanges(const TArray<Metasound::FVertexInterfaceChange>& VertexInterfaceChanges);`
- L176 _private prototype_ `void SetClockHistory(const UMidiClockUpdateSubsystem::FClockHistoryPtr& NewHistory);` — Set (or clear) the shared clock history ring buffer used for position smoothing.
- L179 _private prototype_ `void RefreshFromHistory();` — Read the latest position from the clock history ring and apply PLL smoothing.
- L182 _private prototype_ `void UpdateSmoothedPosition(float SmoothedTick, float SmoothedTempoMapTick);` — Apply the smoothed tick to CurrentPos for non-offset (normal or looping) playback.
- L185 _private prototype_ `void UpdateSmoothedPositionForOffsetClock(float SmoothedTick, float SmoothedTempoMapTick);` — Apply the smoothed tick to CurrentPos for offset clock playback (clock tick != tempo map tick).
- L188 _private prototype_ `FMidiSongPos CalculateSongPosForLoopingOrMonotonic(float AbsoluteMs, float& InOutPositionTick, bool& OutSeekDetected, bool& OutLoopDetected) const;` — Calculate song position with loop wrapping or monotonic advancement.
- L191 _private prototype_ `FMidiSongPos CalculateSongPosForOffsetClock(float PositionMs, float ClockTickOffset, float& InOutPositionTick, bool& OutSeekDetected) const;` — Calculate song position for an offset clock with a tick delta from the tempo map.
- L194 _private prototype_ `bool CheckForSeek(float FirstTick, float NextTick, float CurrentTempo, int32 TicksPerQuarter) const;` — Detect a seek by comparing actual tick delta to expected delta based on tempo and frame time.
- L206 _private prototype_ `EHistoryFailureType CalculateSmoothedTick( Metasound::FSampleCount ExpectedRenderPosSampleCount, Metasound::FSampleCount LastRenderPosSampleCount, float& SmoothedLocalTick, float& SmoothedTempoMapTick, float& CurrentSpeed, HarmonixMetasound::Analysis::FMidiClockSongPositionHistory::FReadCursor& ReadCursor, float LookBehindSeconds);` — Interpolate the clock history ring buffer to find the smoothed tick at the expected render position.
- L215 _private prototype_ `static FString HistoryFailureTypeToString(EHistoryFailureType Error);`

#### struct `UMetasoundMusicSource::FSmoothedClockState`  
`struct FSmoothedClockState`  
_L127-132_
- L129 _public member_ `float TempoMapMs = 0.f;`
- L130 _public member_ `float TempoMapTick = 0.f;`
- L131 _public member_ `float LocalTick = 0.f;`

#### enum `UMetasoundMusicSource::EHistoryFailureType`  
`enum class EHistoryFailureType : uint8`  
_L196-203_
- L198 _public enumerator_ `None`
- L199 _public enumerator_ `NotEnoughDataInTheHistoryRing`
- L200 _public enumerator_ `NotEnoughHistory`
- L201 _public enumerator_ `LookingForTimeInTheFutureOfWhatHasEvenRendered`
- L202 _public enumerator_ `CaughtUpToRenderPosition`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L18 _namespace_ `namespace HarmonixMetasound`
- L18 _namespace_ `namespace Analysis` (scope `HarmonixMetasound`)
- L23 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/MusicSource.h` (Public)


#### class `UMusicSource`  
`class UMusicSource : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IMusicSource`  
`class IMusicSource`  
_L32-158_
- desc: Interface for objects that produce musical time. An IMusicSource is the owner of a music playback stream. It provides: - Transport controls (Start/Stop/Pause/Continue) - Current musical position (FMidiSongPos) - Song map access for time<->beat conversions - Discontinuity detection (loop/seek) A single IMusicSource produces a single time stream. Calibrated time offsets (experienced, video render, etc.) are handled externally by UOffsetMusicSource feeding into a UMusicClock.
- L42 _public prototype_ `virtual void Start() = 0;` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")`
- L45 _public prototype_ `virtual void Pause() = 0;` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")`
- L48 _public prototype_ `virtual void Continue() = 0;` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")`
- L51 _public prototype_ `virtual void Stop() = 0;` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")`
- L59 _public function_ `virtual void Seek(const FMusicTimestamp& Timestamp)` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Seek to a musical position. For RuntimeMusicSource: converts the timestamp to seconds via song maps and seeks the time source. For MetasoundMusicSource: requires Metasound interface support (future work).
- L64 _public prototype_ `virtual Harmonix::ESourceState GetSourceState() const = 0;` — Get the current transport state of the source (Stopped, Preparing, Paused, Running).
- L67 _public prototype_ `virtual Harmonix::ESourceEvent GetLatestSourceEvent() const = 0;` — Get the most recent source event for this frame (Start, Advance, Stop, Pause, Continue, Seek, Loop).
- L71 _public function_ `virtual bool IsPlaying() const` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Whether the source is currently producing musical time.
- L75 _public function_ `virtual bool IsStopped() const` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Whether the source is stopped (not producing time, position at zero).
- L79 _public function_ `virtual bool IsPreparing() const` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Whether the source intends to run but is waiting for data (e.g., Metasound not yet connected).
- L84 _public prototype_ `virtual const FMidiSongPos& GetCurrentSongPos() const = 0;` — The current musical position, updated once per frame via Update().
- L87 _public prototype_ `virtual const FMidiSongPos& GetPreviousSongPos() const = 0;` — The previous frame's musical position.
- L90 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const = 0;` — The song maps used to convert between time and musical position.
- L93 _public prototype_ `virtual float GetCurrentClockAdvanceRate() const = 0;` — The current playback speed multiplier.
- L98 _public prototype_ `virtual bool LoopedThisFrame() const = 0;` — Whether the source crossed a loop boundary this frame.
- L101 _public prototype_ `virtual bool SeekedThisFrame() const = 0;` — Whether the source performed a non-contiguous time jump (seek) this frame.
- L106 _public prototype_ `virtual bool IsLooping() const = 0;` — Whether this source is currently looping.
- L109 _public prototype_ `virtual float GetLoopStartMs() const = 0;` — Start of the loop region in milliseconds. Only valid if IsLooping() is true.
- L112 _public prototype_ `virtual float GetLoopLengthMs() const = 0;` — Length of the loop region in milliseconds. Only valid if IsLooping() is true.
- L122 _public function_ `virtual void SetTempo(float BPM)` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Set the tempo in BPM. For RuntimeMusicSource: modifies the underlying song maps directly. For MetasoundMusicSource: requires Metasound interface support (future work).
- L130 _public function_ `virtual void SetTimeSignature(int32 Numerator, int32 Denominator)` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Set the time signature. For RuntimeMusicSource: modifies the underlying song maps directly. For MetasoundMusicSource: requires Metasound interface support (future work).
- L138 _public function_ `virtual void SetSpeed(float Speed)` — `UFUNCTION(BlueprintCallable, Category = "MusicSource")` — Set the playback speed multiplier (1.0 = normal speed). For RuntimeMusicSource: sets the speed on the underlying ITimeSource. For MetasoundMusicSource: requires Metasound interface support (future work).
- L143 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const = 0;` — Get the world-space location of the audio source, if available.
- L151 _public prototype_ `virtual void Update() = 0;` — Called once per frame by the update subsystem. Implementations should refresh their internal position state.
- L156 _public prototype_ `virtual FString GetDisplayName() const = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/MusicSourceBlueprintLibrary.h` (Public)


#### class `UMusicSourceBlueprintLibrary`  
`class UMusicSourceBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L21-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library for creating and managing music sources and clocks. These factory functions handle creation, connection, and subsystem registration in one call. The source type is determined by the settings struct — new source types can be added by game plugins without modifying this library.
- L39 _public prototype_ `static TScriptInterface<IMusicSource> CreateMusicSource( UObject* Outer, const TInstancedStruct<FMusicSourceSettings>& Settings);` — `UFUNCTION(BlueprintCallable, Category = "Music|Source", Meta = (DefaultToSelf = "Outer"))` — Create a music source from settings. The settings struct type determines what kind of source is created. The source is automatically registered with the update subsystem. @param Outer             Outer object for the new source (determines GC lifetime). @param Settings          Configuration determining source type and parameters. @return The created music source, or invalid if creation failed.
- L56 _public prototype_ `static UMusicClock* CreateMusicClock( UObject* Outer, const TScriptInterface<IMusicSource>& Source);` — `UFUNCTION(BlueprintCallable, Category = "Music|Clock", Meta = (DefaultToSelf = "Outer"))` — Create a read-only music clock bound to a source. The clock holds a weak reference to the source — if the source is destroyed, the clock gracefully reports Stopped. The clock is automatically registered with the update subsystem. @param Outer             Outer object for the new clock (determines GC lifetime). @param Source            The music source to observe. @return The created music clock, or null if Source is invalid.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/MusicSourceSettings.h` (Public)


#### struct `FMusicSourceSettings`  
`struct FMusicSourceSettings`  
_L26-34_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- desc: Base struct for music source configuration. Subclass this to define new music source types. The CreateSource() factory method is called by UMusicSourceBlueprintLibrary::CreateMusicSource() — Blueprint users pick the settings type from a TInstancedStruct dropdown, fill in the type-specific fields, and get back an IMusicSource. Game plugins can add new source types without modifying engine code: just subclass FMusicSourceSettings and implement CreateSource().
- L30 _public prototype_ `virtual ~FMusicSourceSettings() = default;`
- L33 _public prototype_ `virtual TScriptInterface<IMusicSource> CreateSource(UObject* Outer) const;` — Create the music source described by these settings and register it with the update subsystem.

#### struct `FMetasoundMusicSourceSettings`  
`struct FMetasoundMusicSourceSettings : public FMusicSourceSettings`  
_L40-53_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Metasound Music Source Settings")`
- inherits: `FMusicSourceSettings`
- desc: Creates a UMetasoundMusicSource connected to an AudioComponent.
- L46 _public member_ `TObjectPtr<UAudioComponent> AudioComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource")` — The audio component playing a MetaSound.
- L50 _public member_ `FName OutputPinName = "MI` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource")` — The name of the MIDI Clock output pin on the MetaSound.
- L52 _public prototype_ `virtual TScriptInterface<IMusicSource> CreateSource(UObject* Outer) const override;`

#### struct `FMidiMusicSourceSettings`  
`struct FMidiMusicSourceSettings : public FMusicSourceSettings`  
_L59-68_
- reflection: `USTRUCT(BlueprintType, DisplayName = "MIDI Music Source Settings")`
- inherits: `FMusicSourceSettings`
- desc: Creates a URuntimeMusicSource driven by wall clock with tempo/time-sig from a MIDI file.
- L65 _public member_ `TObjectPtr<UMidiFile> MidiFile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource")` — MIDI file providing tempo map and time signature data.
- L67 _public prototype_ `virtual TScriptInterface<IMusicSource> CreateSource(UObject* Outer) const override;`

#### struct `FManualMusicSourceSettings`  
`struct FManualMusicSourceSettings : public FMusicSourceSettings`  
_L75-92_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Manual Music Source Settings")`
- inherits: `FMusicSourceSettings`
- desc: Creates a URuntimeMusicSource driven by wall clock with manually specified tempo and time signature. Tempo and time signature can be changed at runtime via SetTempo() / SetTimeSignature() on the source.
- L81 _public member_ `float Tempo = 120.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource", Meta = (ClampMin = "1.0", ClampMax = "999.0"))` — Initial tempo in BPM.
- L85 _public member_ `int32 TimeSigNumerator = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource", Meta = (ClampMin = "1", ClampMax = "32"))` — Initial time signature numerator (beats per bar).
- L89 _public member_ `int32 TimeSigDenominator = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource", Meta = (ClampMin = "1", ClampMax = "32"))` — Initial time signature denominator (beat unit).
- L91 _public prototype_ `virtual TScriptInterface<IMusicSource> CreateSource(UObject* Outer) const override;`

#### struct `FOffsetMusicSourceSettings`  
`struct FOffsetMusicSourceSettings : public FMusicSourceSettings`  
_L99-112_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Offset Music Source Settings")`
- inherits: `FMusicSourceSettings`
- desc: Creates a UOffsetMusicSource that applies a millisecond offset to a parent source. Used for calibrated time streams (e.g., video render, experienced time).
- L105 _public member_ `TScriptInterface<IMusicSource> ParentSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource")` — The parent music source to offset from.
- L109 _public member_ `float OffsetMs = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MusicSource")` — Offset in milliseconds. Positive = ahead, negative = behind.
- L111 _public prototype_ `virtual TScriptInterface<IMusicSource> CreateSource(UObject* Outer) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/OffsetMusicSource.h` (Public)


#### class `UOffsetMusicSource`  
`class UOffsetMusicSource : public UObject, public IMusicSource`  
_L28-102_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMusicSource`
- desc: An IMusicSource that reads from a parent IMusicSource and applies a millisecond offset. This is how calibrated time clocks (experienced, video render) are created: UMetasoundMusicSource (audio render) -> UOffsetMusicSource (-30ms) -> UMusicClock (video render) -> UOffsetMusicSource (-50ms) -> UMusicClock (experienced) Offset sources can also chain: SourceA -> OffsetB -> OffsetC, where each offset reads directly from the previous IMusicSource. Loop handling: when the parent source is looping, the offset time is wrapped around the loop boundary. On the first pass through the loop (before the parent has ever looped), negative offsets are NOT wrapped — the offset time stays negative until the parent advances past the threshold.
- L36 _public prototype_ `void SetParentSource(const TScriptInterface<IMusicSource>& InParentSource);` — `UFUNCTION(BlueprintCallable, Category = "MusicSource|Offset")` — Set the parent source this offset reads from.
- L40 _public prototype_ `TScriptInterface<IMusicSource> GetParentSource() const;` — `UFUNCTION(BlueprintPure, Category = "MusicSource|Offset")` — Get the parent source.
- L44 _public prototype_ `void SetOffsetMs(float InOffsetMs);` — `UFUNCTION(BlueprintCallable, Category = "MusicSource|Offset")` — Set the offset in milliseconds. Positive = ahead, negative = behind.
- L48 _public prototype_ `float GetOffsetMs() const;` — `UFUNCTION(BlueprintPure, Category = "MusicSource|Offset")` — Get the current offset.
- L53 _public function_ `virtual void Start() override` — Transport is a no-op — the parent source owns playback.
- L54 _public function_ `virtual void Pause() override`
- L55 _public function_ `virtual void Continue() override`
- L56 _public function_ `virtual void Stop() override`
- L58 _public prototype_ `virtual Harmonix::ESourceState GetSourceState() const override;`
- L59 _public prototype_ `virtual Harmonix::ESourceEvent GetLatestSourceEvent() const override;`
- L61 _public prototype_ `virtual const FMidiSongPos& GetCurrentSongPos() const override;`
- L62 _public prototype_ `virtual const FMidiSongPos& GetPreviousSongPos() const override;`
- L63 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const override;`
- L64 _public prototype_ `virtual float GetCurrentClockAdvanceRate() const override;`
- L66 _public prototype_ `virtual bool LoopedThisFrame() const override;`
- L67 _public prototype_ `virtual bool SeekedThisFrame() const override;`
- L69 _public prototype_ `virtual bool IsLooping() const override;`
- L70 _public prototype_ `virtual float GetLoopStartMs() const override;`
- L71 _public prototype_ `virtual float GetLoopLengthMs() const override;`
- L73 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L75 _public prototype_ `virtual void Update() override;`
- L78 _public prototype_ `virtual FString GetDisplayName() const override;`
- L84 _private member_ `TWeakObjectPtr<UObject> ParentSourceObject;` — Weak reference to the parent source UObject.
- L87 _private member_ `IMusicSource* ParentSourceCache = nullptr;` — Cached interface pointer — valid only when ParentSourceObject is valid.
- L90 _private prototype_ `IMusicSource* GetValidParentSource() const;` — Get the parent source if still alive, or nullptr.
- L92 _private member_ `float OffsetMs = 0.f;`
- L94 _private member_ `FMidiSongPos CurrentPos;`
- L95 _private member_ `FMidiSongPos PrevPos;`
- L96 _private member_ `bool bLoopedThisFrame = false;`
- L97 _private member_ `bool bSeekedThisFrame = false;`
- L101 _private member_ `bool bParentHasLooped = false;` — True once the parent source has completed at least one loop pass. Prevents negative offsets from wrapping to the loop end on the first pass.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/MusicSource/RuntimeMusicSource.h` (Public)


#### class `URuntimeMusicSource`  
`class URuntimeMusicSource : public UObject, public IMusicSource`  
_L26-123_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMusicSource`
- desc: A music source that combines an ITimeSource (providing raw time in seconds) with an ISongMapEvaluator (providing time-to-musical-position mapping). This is the "simple" music source for non-Metasound use cases: wall clock, animation-driven, media-driven, etc. The specific time behavior is determined by which ITimeSource implementation is provided. Transport controls delegate to the ITimeSource if it supports them (e.g., FWorldTimeSourceController has Start/Stop/Pause/Continue).
- L32 _public prototype_ `virtual void BeginDestroy() override;`
- L40 _public prototype_ `void Initialize(TSharedPtr<Harmonix::ITimeSource> InTimeSource, const ISongMapEvaluator* InSongMaps);` — Initialize this source with a time source and song maps. @param InTimeSource   Provides raw elapsed time in seconds. @param InSongMaps     Provides time<->musical position mapping. Can be null for default maps.
- L45 _public prototype_ `void InitializeWithMidi(TSharedPtr<Harmonix::ITimeSource> InTimeSource, UMidiFile* InMidiFile);` — Initialize from a MIDI file's song maps.
- L48 _public function_ `TSharedPtr<Harmonix::ITimeSource> GetTimeSource() const` — Get the underlying time source.
- L52 _public prototype_ `virtual void Start() override;`
- L53 _public prototype_ `virtual void Pause() override;`
- L54 _public prototype_ `virtual void Continue() override;`
- L55 _public prototype_ `virtual void Stop() override;`
- L57 _public prototype_ `virtual Harmonix::ESourceState GetSourceState() const override;`
- L58 _public prototype_ `virtual Harmonix::ESourceEvent GetLatestSourceEvent() const override;`
- L60 _public prototype_ `virtual const FMidiSongPos& GetCurrentSongPos() const override;`
- L61 _public prototype_ `virtual const FMidiSongPos& GetPreviousSongPos() const override;`
- L62 _public prototype_ `virtual const ISongMapEvaluator* GetCurrentSongMapEvaluator() const override;`
- L63 _public prototype_ `virtual float GetCurrentClockAdvanceRate() const override;`
- L65 _public prototype_ `virtual bool LoopedThisFrame() const override;`
- L66 _public prototype_ `virtual bool SeekedThisFrame() const override;`
- L68 _public prototype_ `virtual bool IsLooping() const override;`
- L69 _public prototype_ `virtual float GetLoopStartMs() const override;`
- L70 _public prototype_ `virtual float GetLoopLengthMs() const override;`
- L78 _public prototype_ `void SetLoopRegionByBars(int32 StartBar, int32 NumBars);` — `UFUNCTION(BlueprintCallable, Category = "MusicSource|Loop")` — Set a loop region by musical time. @param StartBar   The bar to start looping at (1-based, where Bar 1 = start of song). @param NumBars    Number of bars in the loop. Pass 0 to disable looping.
- L82 _public prototype_ `void ClearLoopRegion();` — `UFUNCTION(BlueprintCallable, Category = "MusicSource|Loop")` — Clear the loop region, disabling looping.
- L84 _public prototype_ `virtual void Seek(const FMusicTimestamp& Timestamp) override;`
- L85 _public prototype_ `virtual void SetTempo(float BPM) override;`
- L86 _public prototype_ `virtual void SetTimeSignature(int32 Numerator, int32 Denominator) override;`
- L87 _public prototype_ `virtual void SetSpeed(float Speed) override;`
- L89 _public prototype_ `virtual TOptional<FVector> TryGetAudioSourceLocation() const override;`
- L91 _public prototype_ `virtual void Update() override;`
- L94 _public prototype_ `virtual FString GetDisplayName() const override;`
- L99 _private member_ `TSharedPtr<Harmonix::ITimeSource> TimeSource;`
- L102 _private member_ `TWeakObjectPtr<UMidiFile> MidiFile;` — External song maps (from MIDI file).
- L105 _private member_ `FSongMaps DefaultMaps;` — Default maps used when no external maps are provided.
- L107 _private member_ `FMidiSongPos CurrentPos;`
- L108 _private member_ `FMidiSongPos PrevPos;`
- L111 _private member_ `int32 LoopStartBar = 0;` — Loop region defined in musical time
- L112 _private member_ `int32 LoopNumBars = 0;`
- L115 _private member_ `float CachedLoopStartMs = 0.f;` — Cached ms values, recomputed from bar values + song maps
- L116 _private member_ `float CachedLoopLengthMs = 0.f;`
- L119 _private prototype_ `void RecomputeLoopRegionMs();` — Recompute cached loop start/length in ms from bar values + current song maps.
- L122 _private prototype_ `const ISongMapEvaluator* GetMaps() const;` — Get the active song map evaluator (MIDI file maps or DefaultMaps).

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXMETASOUND_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/DelayNode.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace HarmonixMetasound`
- L7 _namespace_ `namespace DelayNode` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace Constants` (scope `HarmonixMetasound::DelayNode`)
- L11 _variable_ `inline constexpr int32 NumChannels = 2;` (scope `HarmonixMetasound::DelayNode::Constants`)
- L12 _variable_ `inline constexpr float MaxDelayTime = 2500.0f;` (scope `HarmonixMetasound::DelayNode::Constants`)
- L15 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::DelayNode`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioLeft);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioRight);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(DelayTimeType);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(DelayTime);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Feedback);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(DryLevel);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(WetLevel);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(WetFilterEnabled);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(FeedbackFilterEnabled);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(FilterType);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(FilterCutoff);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L29 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(FilterQ);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L30 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFOEnabled);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L31 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFOTimeType);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L32 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(LFOFrequency);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L33 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFODepth);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L34 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StereoType);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L35 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StereoSpreadLeft);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L36 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StereoSpreadRight);` (scope `HarmonixMetasound::DelayNode::Inputs`)
- L39 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::DelayNode`)
- L41 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioLeft);` (scope `HarmonixMetasound::DelayNode::Outputs`)
- L42 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioRight);` (scope `HarmonixMetasound::DelayNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/DjFilterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace DjFilter` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::DjFilter`)
- L13 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::DjFilter`)
- L15 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioMono);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Amount);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Resonance);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LowPassMinFrequency);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LowPassMaxFrequency);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(HighPassMinFrequency);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(HighPassMaxFrequency);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(DeadZoneSize);` (scope `HarmonixMetasound::Nodes::DjFilter::Inputs`)
- L25 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::DjFilter`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioMono);` (scope `HarmonixMetasound::Nodes::DjFilter::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MetronomeNode.h` (Public)


#### class `HarmonixMetasound::Nodes::MetronomeNode::FMetronomeOperatorBase`  
`class FMetronomeOperatorBase : public TExecutableOperator<FMetronomeOperatorBase>, public FMusicTransportControllable`  
_L54-114_
- inherits: `TExecutableOperator<FMetronomeOperatorBase>,FMusicTransportControllable`
- L58 _public prototype_ `FMetronomeOperatorBase(const FBuildOperatorParams& InParams, const FMusicTransportEventStreamReadRef& InTransport, const bool InLoop, const int32 InLoopLengthBars, const FInt32ReadRef& InTimSigNumerator, const FInt32ReadRef& InTimeSigDenominator, const FFloatReadRef& InTempo, const FFloatReadRef& InSpeedMultiplier, const int32 InSeekPrerollBars);`
- L68 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InVertexData) override;`
- L69 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InVertexData) override;`
- L71 _public prototype_ `void Reset(const FResetParams& Params);`
- L72 _public prototype_ `void Execute();`
- L75 _protected prototype_ `void Init();`
- L78 _protected member_ `FMusicTransportEventStreamReadRef TransportInPin;` — /  INPUTS
- L79 _protected member_ `const bool LoopInPin;`
- L80 _protected member_ `const int32 LoopLengthBarsInPin;`
- L81 _protected member_ `FInt32ReadRef TimeSigNumInPin;`
- L82 _protected member_ `FInt32ReadRef TimeSigDenomInPin;`
- L83 _protected member_ `FFloatReadRef TempoInPin;`
- L84 _protected member_ `FFloatReadRef SpeedMultInPin;`
- L85 _protected member_ `const int32 SeekPreRollBarsInPin;`
- L88 _protected member_ `FMidiClockWriteRef MidiClockOutPin;` — /  OUTPUTS
- L91 _protected member_ `TSharedPtr<FMidiClock, ESPMode::NotThreadSafe> MonotonicallyIncreasingClock;` — /  DATA
- L92 _protected member_ `TSharedPtr<FSongMaps> SongMaps;`
- L93 _protected member_ `FSampleCount BlockSize;`
- L94 _protected member_ `float SampleRate;`
- L95 _protected member_ `float CurrentTempo = 0.0f;`
- L96 _protected member_ `int32 CurrentTimeSigNum = 0;`
- L97 _protected member_ `int32 CurrentTimeSigDenom = 0;`
- L98 _protected member_ `int32 LastProcessedClockTick = -1;`
- L99 _protected member_ `int32 NextClockTickToProcess = 0;`
- L100 _protected member_ `bool bClocksArePreparedForExecute = true;`
- L102 _protected prototype_ `void BuildSongMaps(bool ResetToStart = true);`
- L103 _protected prototype_ `float GetInputTempoClamped() const;`
- L104 _protected prototype_ `int32 GetInputTimeSigNumeratorClamped() const;`
- L105 _protected prototype_ `int32 GetInputTimeSigDenominatorClamped() const;`
- L106 _protected prototype_ `void UpdateMidi();`
- L107 _protected prototype_ `void AddTempoChangeForMidi(float TempoBPM);`
- L108 _protected prototype_ `virtual void HandleTimeSigChangeForMidi(int32 TimeSigNum, int32 TimeSigDenom);`
- L109 _protected prototype_ `void HandleTransportChange(int32 StartFrameIndex, EMusicPlayerTransportState NewTransportState);`
- L110 _protected prototype_ `void PrepareClocksForExecute();`
- L111 _protected prototype_ `void MarkClocksAsExecuted();`
- L113 _protected function_ `FMidiClock& GetDrivingMidiClock()`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L21 _namespace_ `namespace HarmonixMetasound`
- L21 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L21 _namespace_ `namespace MetronomeNode` (scope `HarmonixMetasound::Nodes`)
- L25 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L26 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L28 _variable_ `constexpr float kMinTempoBpm = 1.0f;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L29 _variable_ `constexpr float kMaxTempoBpm = 999.0f;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L31 _variable_ `constexpr int32 kMinTimeSigNumerator = 1;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L32 _variable_ `constexpr int32 kMaxTimeSigNumerator = 64;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L34 _variable_ `constexpr int32 kMinTimeSigDenominator = 1;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L35 _variable_ `constexpr int32 kMaxTimeSigDenominator = 64;` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L37 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L39 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L40 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Loop);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L41 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(LoopLengthBars);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L42 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TimeSigNumerator);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L43 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TimeSigDenominator);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L44 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Tempo);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L45 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Speed);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L46 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(PrerollBars);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Inputs`)
- L49 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MetronomeNode`)
- L51 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MetronomeNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiCCTriggerNode.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace HarmonixMetasound`
- L8 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L8 _namespace_ `namespace MidiCCTriggerNode` (scope `HarmonixMetasound::Nodes`)
- L10 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode`)
- L11 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode`)
- L13 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode`)
- L15 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode::Inputs`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(InputMidiControllerID);` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode::Inputs`)
- L20 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OutputControlChangeValueInt32);` (scope `HarmonixMetasound::Nodes::MidiCCTriggerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiChannelFilterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiChannelFilter` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `Metasound::FNodeClassName GetClassName();` (scope `HarmonixMetasound::Nodes::MidiChannelFilter`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiChannelFilter`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiChannelFilter`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiChannelFilter::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiChannelFilter::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Channel);` (scope `HarmonixMetasound::Nodes::MidiChannelFilter::Inputs`)
- L21 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiChannelFilter`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiChannelFilter::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiClockOffsetNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiClockOffset` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `Metasound::FNodeClassName GetClassName();` (scope `HarmonixMetasound::Nodes::MidiClockOffset`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiClockOffset`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiClockOffset`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OffsetMs);` (scope `HarmonixMetasound::Nodes::MidiClockOffset::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OffsetBars);` (scope `HarmonixMetasound::Nodes::MidiClockOffset::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OffsetBeats);` (scope `HarmonixMetasound::Nodes::MidiClockOffset::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiClockOffset::Inputs`)
- L22 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiClockOffset`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiClockOffset::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiClockSubdivisionTriggerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiClockSubdivisionTriggerNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(GridSizeUnits);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(GridSizeMult);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(OffsetUnits);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(OffsetMult);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Inputs`)
- L24 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(TriggerOutput);` (scope `HarmonixMetasound::Nodes::MidiClockSubdivisionTriggerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiNoteFilterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiNoteFilter` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `Metasound::FNodeClassName GetClassName();` (scope `HarmonixMetasound::Nodes::MidiNoteFilter`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiNoteFilter`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiNoteFilter`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MinNoteNumber);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MaxNoteNumber);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MinVelocity);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MaxVelocity);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(IncludeOtherEvents);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Inputs`)
- L25 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiNoteFilter`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteFilter::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiNoteGeneratorNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "HarmonixMetasound_MidiNoteGeneratorNode"`
- L13 _namespace_ `namespace HarmonixMetasound`
- L13 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L13 _namespace_ `namespace MidiNoteGeneratorNode` (scope `HarmonixMetasound::Nodes`)
- L15 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode`)
- L16 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode`)
- L18 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiChannelNumber);` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode::Inputs`)
- L30 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode`)
- L32 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteGeneratorNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiNoteTriggerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiNoteTriggerNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Inputs`)
- L20 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(NoteOnTrigger);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Outputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(NoteOffTrigger);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Outputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiNoteNumber);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Outputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiVelocity);` (scope `HarmonixMetasound::Nodes::MidiNoteTriggerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiPlayerNode.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HarmonixMetasound`
- L11 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L11 _namespace_ `namespace MidiPlayerNode` (scope `HarmonixMetasound::Nodes`)
- L15 _prototype_ `const FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L16 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L18 _variable_ `static constexpr float kMinClockSpeed = 0.01f;` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L19 _variable_ `static constexpr float kMaxClockSpeed = 10.0f;` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L21 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiFileAsset);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Loop);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Speed);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(PrerollBars);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L29 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(KillVoicesOnSeek);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L30 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(KillVoicesOnMidiChange);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Inputs`)
- L33 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiPlayerNode`)
- L35 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Outputs`)
- L36 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiPlayerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiPulseGeneratorNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiPulseGeneratorNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(DutyCycle);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Interval);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(IntervalMultiplier);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Offset);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OffsetMultiplier);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiTrack);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiChannel);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MidiNoteNumber);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MidiVelocity);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Inputs`)
- L28 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode`)
- L30 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiPulseGeneratorNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiQuantizeTriggerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L11 _namespace_ `namespace HarmonixMetasound`
- L11 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L11 _namespace_ `namespace MidiQuantizeTriggerNode` (scope `HarmonixMetasound::Nodes`)
- L13 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode`)
- L14 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode`)
- L16 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(TriggerInput);` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode::Inputs`)
- L24 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(TriggerOutput);` (scope `HarmonixMetasound::Nodes::MidiQuantizeTriggerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiStreamTrackFilterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiTrackFilter` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiTrackFilter`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiTrackFilter`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiTrackFilter`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MinTrackIndex);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MaxTrackIndex);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(IncludeConductorTrack);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Inputs`)
- L23 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiTrackFilter`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiTrackFilter::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiStreamTransposerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiNoteTranspose` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transposition);` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose::Inputs`)
- L21 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiNoteTranspose::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MidiStreamWriterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MidiStreamWriter` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MidiStreamWriter`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MidiStreamWriter`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MidiStreamWriter`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MidiStreamWriter::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::MidiStreamWriter::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(FilenamePrefix);` (scope `HarmonixMetasound::Nodes::MidiStreamWriter::Inputs`)
- L21 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MidiStreamWriter`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MorphingLfoNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace MorphingLFO` (scope `HarmonixMetasound::Nodes`)
- L12 _function_ `template<typename OutputDataType> const Metasound::FNodeClassName& GetClassName()` (scope `HarmonixMetasound::Nodes::MorphingLFO`)
- L23 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MorphingLFO`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::MorphingLFO::Inputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(LFOSyncType);` (scope `HarmonixMetasound::Nodes::MorphingLFO::Inputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(LFOFrequency);` (scope `HarmonixMetasound::Nodes::MorphingLFO::Inputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(LFOInvert);` (scope `HarmonixMetasound::Nodes::MorphingLFO::Inputs`)
- L32 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MorphingLFO`)
- L34 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(LFO);` (scope `HarmonixMetasound::Nodes::MorphingLFO::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MultibandAnalyzerNode.h` (Public)


#### struct `HarmonixMetasound::Nodes::MultibandAnalyzer::FSettings`  
`struct FSettings`  
_L14-22_
- L16 _public member_ `bool Enable{ true };`
- L17 _public member_ `TArray<float> CrossoverFrequencies{ 200, 400, 800 };`
- L18 _public member_ `bool ApplySmoothing{ true };`
- L19 _public member_ `Metasound::FTime AttackTime = Metasound::FTime::FromMilliseconds(10);`
- L20 _public member_ `Metasound::FTime ReleaseTime = Metasound::FTime::FromMilliseconds(10);`
- L21 _public member_ `Metasound::EEnvelopePeakMode PeakMode = Metasound::EEnvelopePeakMode::Peak;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace HarmonixMetasound`
- L10 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L10 _namespace_ `namespace MultibandAnalyzer` (scope `HarmonixMetasound::Nodes`)
- L12 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer`)
- L24 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioMono);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CrossoverFrequencies);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L29 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(ApplySmoothing);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L30 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AttackTime);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L31 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(ReleaseTime);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L32 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(PeakMode);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Inputs`)
- L35 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer`)
- L37 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(BandLevels);` (scope `HarmonixMetasound::Nodes::MultibandAnalyzer::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/MusicSeekTargetBuilder.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace BarBeatToSeekTarget` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Bar);` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Beat);` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget::Inputs`)
- L20 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(SeekTarget);` (scope `HarmonixMetasound::Nodes::BarBeatToSeekTarget::Outputs`)
- L26 _namespace_ `namespace HarmonixMetasound`
- L26 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L26 _namespace_ `namespace MusicTimeStampToSeekTarget` (scope `HarmonixMetasound::Nodes`)
- L28 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget`)
- L29 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget`)
- L31 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget`)
- L33 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MusicTimestamp);` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget::Inputs`)
- L36 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget`)
- L38 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(SeekTarget);` (scope `HarmonixMetasound::Nodes::MusicTimeStampToSeekTarget::Outputs`)
- L42 _namespace_ `namespace HarmonixMetasound`
- L42 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L42 _namespace_ `namespace TimeMsToSeekTarget` (scope `HarmonixMetasound::Nodes`)
- L44 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget`)
- L45 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget`)
- L47 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget`)
- L49 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(TimeMs);` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget::Inputs`)
- L52 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget`)
- L54 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(SeekTarget);` (scope `HarmonixMetasound::Nodes::TimeMsToSeekTarget::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/PeakNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace Peak` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::Peak`)
- L13 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::Peak`)
- L15 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::Peak::Inputs`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(AudioMono);` (scope `HarmonixMetasound::Nodes::Peak::Inputs`)
- L19 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::Peak`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Peak);` (scope `HarmonixMetasound::Nodes::Peak::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/SecsUntilMusicTimestampNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace SecsUntilMusicTimestampNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enable);` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Timestamp);` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode::Inputs`)
- L21 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::SecsUntilMusicTimestampNode`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/SimpleSamplerNode.h` (Public)


#### struct `FHarmonixSimpleSamplerNodeConfiguration`  
`struct FHarmonixSimpleSamplerNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L17-31_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L22 _public member_ `uint32 NumChannels = 1;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "8"))`
- L25 _public member_ `float MaxCaptureSeconds = 5.0f;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "10"))`
- L28 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const;` — Get the current interface for the class based upon the node extension
- L30 _public prototype_ `TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`

#### class `HarmonixMetasound::SimpleSamplerNode::FSimpleSamplerNodeOperatorData`  
`class FSimpleSamplerNodeOperatorData : public Metasound::TOperatorData<FSimpleSamplerNodeOperatorData>`  
_L35-43_
- inherits: `Metasound::TOperatorData<FSimpleSamplerNodeOperatorData>`
- L38 _public member_ `static const FLazyName OperatorDataTypeName;`
- L39 _public function_ `FSimpleSamplerNodeOperatorData(const float& InMaxCaptureSeconds) : MaxCaptureSeconds(InMaxCaptureSeconds)`
- L42 _public member_ `float MaxCaptureSeconds = 5.0f;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HarmonixMetasound`
- L11 _namespace_ `namespace SimpleSamplerNode` (scope `HarmonixMetasound`)
- L33 _namespace_ `namespace HarmonixMetasound`
- L33 _namespace_ `namespace SimpleSamplerNode` (scope `HarmonixMetasound`)
- L45 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::SimpleSamplerNode`)
- L47 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enabled);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L48 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Capture);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L49 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CaptureDuration);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L50 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Play);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L51 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(PlayDuration);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L52 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reverse);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L53 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reset);` (scope `HarmonixMetasound::SimpleSamplerNode::Inputs`)
- L56 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::SimpleSamplerNode`)
- L58 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(InputAudioInUse);` (scope `HarmonixMetasound::SimpleSamplerNode::Outputs`)
- L61 _variable_ `static constexpr int32 kMaxChannels = 8;` (scope `HarmonixMetasound::SimpleSamplerNode`)
- L62 _variable_ `static constexpr int32 kNumFadeFrames = 32;` (scope `HarmonixMetasound::SimpleSamplerNode`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/StepSequencePlayerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace StepSequencePlayer` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::StepSequencePlayer`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::StepSequencePlayer`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::StepSequencePlayer`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(SequenceAsset);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(VelocityMultiplier);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(MaxColumns);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AdditionalOctaves);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StepSizeQuarterNotes);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(ActivePage);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AutoPage);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AutoPagePlaysBlankPages);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Speed);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Loop);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enabled);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Inputs`)
- L31 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::StepSequencePlayer`)
- L33 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiStream);` (scope `HarmonixMetasound::Nodes::StepSequencePlayer::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/StutterControllerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace StutterSequencerNode` (scope `HarmonixMetasound`)
- L11 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::StutterSequencerNode`)
- L13 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enabled);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L14 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StutterSequence);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L15 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Start);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Stop);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CaptureDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Spacing);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(AudibleDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reverse);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L24 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::StutterSequencerNode`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Capture);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CaptureDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Play);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L29 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(PlayDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L30 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reverse);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L31 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reset);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/StutterSequencerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace StutterSequencerNode` (scope `HarmonixMetasound`)
- L11 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::StutterSequencerNode`)
- L13 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enabled);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L14 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StutterSequence);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L15 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Start);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Stop);` (scope `HarmonixMetasound::StutterSequencerNode::Inputs`)
- L20 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::StutterSequencerNode`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Capture);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CaptureDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Play);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(PlayDuration);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reverse);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Reset);` (scope `HarmonixMetasound::StutterSequencerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/TapeSSNode.h` (Public)


#### struct `FHarmonixTapeSSNodeConfiguration`  
`struct FHarmonixTapeSSNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L17-31_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L22 _public member_ `uint32 NumChannels = 1;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "8"))`
- L25 _public member_ `float MaxRampSeconds = 5.0f;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "10"))`
- L28 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const;` — Get the current interface for the class based upon the node extension
- L30 _public prototype_ `TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`

#### class `HarmonixMetasound::TapeSSNode::FTapeSSNodeOperatorData`  
`class FTapeSSNodeOperatorData : public Metasound::TOperatorData<FTapeSSNodeOperatorData>`  
_L35-43_
- inherits: `Metasound::TOperatorData<FTapeSSNodeOperatorData>`
- L38 _public member_ `static const FLazyName OperatorDataTypeName;`
- L39 _public function_ `FTapeSSNodeOperatorData(const float& InMaxRampSeconds) : MaxRampSeconds(InMaxRampSeconds)`
- L42 _public member_ `float MaxRampSeconds = 5.0f;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HarmonixMetasound`
- L11 _namespace_ `namespace TapeSSNode` (scope `HarmonixMetasound`)
- L33 _namespace_ `namespace HarmonixMetasound`
- L33 _namespace_ `namespace TapeSSNode` (scope `HarmonixMetasound`)
- L45 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::TapeSSNode`)
- L47 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Enabled);` (scope `HarmonixMetasound::TapeSSNode::Inputs`)
- L48 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(Stop);` (scope `HarmonixMetasound::TapeSSNode::Inputs`)
- L49 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(RampDuration);` (scope `HarmonixMetasound::TapeSSNode::Inputs`)
- L52 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::TapeSSNode`)
- L54 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(InputAudioInUse);` (scope `HarmonixMetasound::TapeSSNode::Outputs`)
- L55 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OnStopped);` (scope `HarmonixMetasound::TapeSSNode::Outputs`)
- L56 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(OnFullSpeed);` (scope `HarmonixMetasound::TapeSSNode::Outputs`)
- L57 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(CurrentSpeed);` (scope `HarmonixMetasound::TapeSSNode::Outputs`)
- L60 _variable_ `static constexpr int32 kMaxChannels = 8;` (scope `HarmonixMetasound::TapeSSNode`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/TransportToTriggerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace TransportToTriggerNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Inputs`)
- L19 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPrepare);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPlay);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPause);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportContinue);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L25 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportStop);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L26 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportKill);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)
- L27 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportSeek);` (scope `HarmonixMetasound::Nodes::TransportToTriggerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/TransportWavePlayerControllerNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace TransportWavePlayerControllerNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(MidiClock);` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode::Inputs`)
- L20 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPlay);` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode::Outputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportStop);` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode::Outputs`)
- L24 _prototype_ `DECLARE_METASOUND_PARAM_EXTERN(StartTime);` (scope `HarmonixMetasound::Nodes::TransportWavePlayerControllerNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Nodes/TriggerToTransportNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace HarmonixMetasound`
- L9 _namespace_ `namespace Nodes` (scope `HarmonixMetasound`)
- L9 _namespace_ `namespace TriggerToTransportNode` (scope `HarmonixMetasound::Nodes`)
- L11 _prototype_ `const Metasound::FNodeClassName& GetClassName();` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode`)
- L12 _prototype_ `int32 GetCurrentMajorVersion();` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode`)
- L14 _namespace_ `namespace Inputs` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode`)
- L16 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPrepare);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L17 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPlay);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L18 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportPause);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L19 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportContinue);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L20 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportStop);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L21 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TransportKill);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L22 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(TriggerSeek);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L23 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(SeekDestination);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Inputs`)
- L26 _namespace_ `namespace Outputs` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode`)
- L28 _prototype_ `DECLARE_METASOUND_PARAM_ALIAS(Transport);` (scope `HarmonixMetasound::Nodes::TriggerToTransportNode::Outputs`)

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Subsystems/MidiClockUpdateSubsystem.h` (Public)


#### class `UMidiClockUpdateSubsystem`  
`class UMidiClockUpdateSubsystem final : public UEngineSubsystem`  
_L39-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- desc: Handles updating low-resolution play cursors associated with a MIDI clock. This now includes both FMidiClock and UMusicClockComponents. MidiClock: Because FMidiClock instances do not have their lifecycle managed by the garbage collector, we need a way to tick them on the game thread while avoiding races. This gives us a way to register clocks to be ticked from within their constructors/destructor, and provides no user-facing API. MusicClockComponent: Because the "current music time" is typically of interest to many game systems, and some of those systems run in parallel in different threads (e.g. TickComponent functions and animation jobs), it is important that the current music time is updated at the beginning of the game frame, and then that same time can be used for all systems for the frame. This subsystem solves for those problems.
- L45 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L46 _public prototype_ `virtual void Deinitialize() override;`
- L49 _public prototype_ `static void TrackMusicClockComponent(UMusicClockComponent* Clock);`
- L50 _public prototype_ `static void StopTrackingMusicClockComponent(UMusicClockComponent* Clock);`
- L53 _public prototype_ `static void TrackMusicSource(UObject* Source);` — Track a music source for per-frame updates. The source's Update() will be called each frame.
- L54 _public prototype_ `static void StopTrackingMusicSource(UObject* Source);`
- L57 _public prototype_ `static void TrackMusicClock(UMusicClock* Clock);` — Track a music clock for per-frame updates. The clock's UpdateForGameFrame() will be called each frame.
- L58 _public prototype_ `static void StopTrackingMusicClock(UMusicClock* Clock);`
- L60 _public prototype_ `static double GetUpdateTimeSeconds();`
- L62 _public typedef_ `using FClockHistoryPtr = TSharedPtr<HarmonixMetasound::Analysis::FMidiClockSongPositionHistory>;`
- L63 _public prototype_ `static FClockHistoryPtr GetOrCreateClockHistory(const Metasound::Frontend::FAnalyzerAddress& ForAddress);`
- L65 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMusicClockComponentsUpdated, const TArray<TWeakObjectPtr<UMusicClockComponent>>&);`
- L66 _public function_ `FOnMusicClockComponentsUpdated& OnMusicClockComponentsUpdated()`
- L72 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackMusicClockComponentChange, UMusicClockComponent*);`
- L73 _public function_ `FOnTrackMusicClockComponentChange& OnTrackMusicClockComponent()`
- L79 _public function_ `FOnTrackMusicClockComponentChange& OnStopTrackingMusicClockComponent()`
- L85 _public function_ `const TArray<TWeakObjectPtr<UMusicClockComponent>>& GetTrackedMusicClockComponents() const`
- L92 _private member_ `mutable FCriticalSection TrackedMidiClocksMutex;`
- L93 _private member_ `static double UpdateTimeSeconds;`
- L95 _private member_ `TArray<TWeakObjectPtr<UMusicClockComponent>> TrackedMusicClockComponents;`
- L96 _private prototype_ `void TrackMusicClockComponentImpl(UMusicClockComponent* Clock);`
- L97 _private prototype_ `void StopTrackingMusicClockComponentImpl(UMusicClockComponent* Clock);`
- L98 _private prototype_ `void UpdateUMusicClockComponents();`
- L101 _private member_ `TArray<TWeakObjectPtr<UObject>> TrackedMusicSources;` — Music sources tracked for per-frame Update() calls.
- L102 _private prototype_ `void TrackMusicSourceImpl(UObject* Source);`
- L103 _private prototype_ `void StopTrackingMusicSourceImpl(UObject* Source);`
- L104 _private prototype_ `void UpdateMusicSources();`
- L107 _private member_ `TArray<TWeakObjectPtr<UMusicClock>> TrackedMusicClocks;` — Music clocks tracked for per-frame UpdateForGameFrame() calls.
- L108 _private prototype_ `void TrackMusicClockImpl(UMusicClock* Clock);`
- L109 _private prototype_ `void StopTrackingMusicClockImpl(UMusicClock* Clock);`
- L110 _private prototype_ `void UpdateMusicClocks();`
- L112 _private member_ `FDelegateHandle EngineSamplingInputDelegate;`
- L113 _private prototype_ `void CoreDelegatesSamplingInput();`
- L115 _private member_ `static FCriticalSection ClockHistoryMapLocker;`
- L116 _private member_ `static TMap<uint32, TWeakPtr<HarmonixMetasound::Analysis::FMidiClockSongPositionHistory>> ClockHistories;`
- L118 _private prototype_ `static uint32 MakeMidiSongPosAnalyzerAddressHash(const Metasound::Frontend::FAnalyzerAddress& ForAddress);`
- L120 _private member_ `FOnTrackMusicClockComponentChange OnTrackMusicClockComponentDelegate;`
- L121 _private member_ `FOnTrackMusicClockComponentChange OnStopTrackingMusicClockComponentDelegate;`
- L122 _private member_ `FOnMusicClockComponentsUpdated OnMusicClockComponentsUpdatedDelegate;`
- L127 _public prototype_ `void TickForTesting();` — Declare a "tick" method that can be used during automated testing so that the test code doesn't need knowledge of how the low-res clocks are being ticked...

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API HARMONIXMETASOUND_API`
- L21 _namespace_ `namespace HarmonixMetasound`
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMusicClockComponentsUpdated, const TArray<TWeakObjectPtr<UMusicClockComponent>>&);`
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTrackMusicClockComponentChange, UMusicClockComponent*);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasound/Utils/MusicTempometerUtilities.h` (Public)


#### struct `FMusicTempometerMPCParameterNames`  
`struct FMusicTempometerMPCParameterNames`  
_L14-131_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `FName SecondsIncludingCountInParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category="MusicClock")` — Seconds from the beginning of the entire music authoring. Includes all count-in and pickup bars (ie. won't be negative when the music starts, and bar 1 beat 1 may not be at 0.0 seconds!
- L34 _public member_ `FName BarsIncludingCountInParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Bars from the beginning of the music. Includes all count-in and pickup bars (ie. won't be negative when the music starts, and bar 1 beat 1 of the music may not be equal to elapsed bar 0.0! NOTE: This Bar, unlike the Bar in the MusicTimestamp structure, is floating point and will include a fractional portion.
- L42 _public member_ `FName BeatsIncludingCountInParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Total Beats from the beginning of the music. Includes all count-in and pickup bars/beats (ie. won't be negative when the music starts, and elapsed beat 0.0 may not equal a timestamp of bar 1 beat 1!
- L49 _public member_ `FName SecondsFromBarOneParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Seconds from Bar 1 Beat 1 of the music. If the music has a count-in or pickup bars this number may be negative when the music starts!
- L61 _public member_ `FName TimestampBarParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — This is the bar member of the MusicTimestamp structure which represents a classic "music time" where bar 1 beat 1 is the beginning of the music AFTER count-in and pickups. If the music has a count-in or pickup bars this number may be negative (or zero) until bar 1 beat 1 is reached! NOTE: Unlike "BarsFromCountIn", Bar here will be an integer! This because it is the bar from the MusicTimestamp structure which also provides a "beat in bar" member to denote a "distance into the bar".
- L72 _public member_ `FName TimestampBeatInBarParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — This is the beat member of the MusicTimestamp structure which represents a classic "music time" where bar 1 beat 1 is the beginning of the music AFTER count-in and pickups. If the music has a count-in or pickup bars this number may be negative (or zero) until bar 1 beat 1 is reached! NOTE: beat in this context is 1 based! The first beat in a bar is beat 1! Note: This is a floating point number.
- L79 _public member_ `FName BarProgressParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Progress of the current bar [0, 1]. This is the same as the fractional part of BarsFromCountIn.
- L86 _public member_ `FName BeatProgressParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Progress of the current beat [0, 1]. This is the same as the fractional part of BeatsFromCountIn;
- L92 _public member_ `FName TimeSignatureNumeratorParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Current time signature numerator (beats per bar).
- L98 _public member_ `FName TimeSignatureDenominatorParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Current time signature denominator (scale from note duration to beat).
- L104 _public member_ `FName TempoParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — Current tempo (beats per minute).
- L110 _public member_ `FName TimestampValidParameterName = "Mu` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock")` — 0 or 1, represents whether the rest of the parameters are defaults (0) or the current state of a clock (1).
- L112 _public function_ `bool IsValid() const`

#### struct `FMusicTempometerMPCParameters`  
`struct FMusicTempometerMPCParameters`  
_L136-162_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters used when creating/updating the corresponding Material Parameter Collection
- L141 _public member_ `FMusicTempometerMPCParameterNames CurrentFrameParameterNames;` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock", meta = (ShowOnlyInnerProperties))`
- L144 _public member_ `FMusicTempometerMPCParameterNames PreviousFrameParameterNames{ "PreviousFrameMusicSecondsIncludingCountIn", "PreviousFrameMusicBarsIncludingCountIn", "PreviousFrameMusicBeatsIncludingCountIn", "PreviousFrameMusicSecondsFromBarOne", "PreviousFrameMusicTimestampBar", "PreviousFrameMusicTimestampBeatInBar", "PreviousFrameMusicBarProgress", "PreviousFrameMusicBeatProgress", "PreviousFrameMusicTimeSignatureNumerator", "PreviousFrameMusicTimeSignatureDenominator", "PreviousFrameMusicTempo", "Prev` — `UPROPERTY(EditDefaultsOnly, Category = "MusicClock", meta = (ShowOnlyInnerProperties))`
- L158 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L167 _namespace_ `namespace MusicTempometerUtilities`
- L173 _prototype_ `void UpdateMaterialParameterCollectionFromClock(const UObject* InWorldContextObject, TWeakObjectPtr<UMaterialParameterCollectionInstance>& InOutMaterialParameterCollectionInstance, const TObjectPtr<UMaterialParameterCollection>& InMaterialParameterCollection, const FMusicTempometerMPCParameters& InMCPParameters, const UMusicClockComponent* InClockComponent);` (scope `MusicTempometerUtilities`) — `UE_DEPRECATED(5.6, "This implementation of UpdateMaterialParameterCollectionFromClock() is deprecated. Please use the implementation with an 'InPreviousFrameMidiSongPos' argument instead.")` — Update the supplied material parameter collection instance (create if null) with song position data extracted from the supplied clock
- L179 _prototype_ `void UpdateMaterialParameterCollectionFromSongPos(const UObject* InWorldContextObject, TWeakObjectPtr<UMaterialParameterCollectionInstance>& InOutMaterialParameterCollectionInstance, const TObjectPtr<UMaterialParameterCollection>& InMaterialParameterCollection, const FMusicTempometerMPCParameters& InMCPParameters, const FMidiSongPos& InMidiSongPos);` (scope `MusicTempometerUtilities`) — `UE_DEPRECATED(5.6, "This implementation of UpdateMaterialParameterCollectionFromSongPos() is deprecated. Please use the implementation with an 'InPreviousFrameMidiSongPos' argument instead.")` — Update the supplied material parameter collection instance (create if null) with data from the supplied song position
- L184 _prototype_ `FMidiSongPos UpdateMaterialParameterCollectionFromClock(const UMusicClockComponent* InClockComponent, const FMidiSongPos& InPreviousFrameMidiSongPos, const UMaterialParameterCollection* InMaterialParameterCollection, const FMusicTempometerMPCParameters& InMPCParameters, TWeakObjectPtr<UMaterialParameterCollectionInstance>& InOutMaterialParameterCollectionInstance);` (scope `MusicTempometerUtilities`) — Update the supplied material parameter collection instance (create from the supplied material parameter collection if null) from the supplied clock and song position, and return the current song position according to the supplied clock.
- L189 _prototype_ `void UpdateMaterialParameterCollectionFromSongPos(const UObject* InWorldContextObject, const FMidiSongPos& InCurrentFrameMidiSongPos, const FMidiSongPos& InPreviousFrameMidiSongPos, const UMaterialParameterCollection* InMaterialParameterCollection, const FMusicTempometerMPCParameters& InMPCParameters, TWeakObjectPtr<UMaterialParameterCollectionInstance>& InOutMaterialParameterCollectionInstance);` (scope `MusicTempometerUtilities`) — Update the supplied material parameter collection instance (create from the supplied material parameter collection if null) from the supplied song positions.

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasound/Public/HarmonixMetasoundModule.h` (Public)


#### class `FHarmonixMetasoundModule`  
`class FHarmonixMetasoundModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _public prototype_ `virtual void StartupModule();`
- L11 _public prototype_ `virtual void ShutdownModule();`
