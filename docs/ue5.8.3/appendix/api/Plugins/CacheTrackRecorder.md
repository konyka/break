# Plugins / CacheTrackRecorder

- module root: `Plugins/VirtualProduction/Takes/Source/CacheTrackRecorder`
- headers: 2; symbols: 78
- symbol kinds: class=2, enum=1, enumerator=6, function=2, macro=1, member=33, prototype=28, struct=5

### `Plugins/VirtualProduction/Takes/Source/CacheTrackRecorder/Private/CacheTrackRecorderModule.h` (Private)


#### class `FCacheTrackRecorderModule`  
`class FCacheTrackRecorderModule : public IModuleInterface`  
_L12-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `FCacheTrackRecorderModule();`
- L18 _private prototype_ `virtual void StartupModule() override;`
- L19 _private prototype_ `virtual void ShutdownModule() override;`
- L21 _private prototype_ `void OnEditorClose();`

### `Plugins/VirtualProduction/Takes/Source/CacheTrackRecorder/Public/Recorder/CacheTrackRecorder.h` (Public)


#### struct `FCacheRecorderUserParameters`  
`struct FCacheRecorderUserParameters`  
_L16-37_
- reflection: `USTRUCT()`
- L20 _public prototype_ `FCacheRecorderUserParameters();`
- L24 _public member_ `bool bMaximizeViewport;` — `UPROPERTY(config, EditAnywhere, Category="User Settings")` — Whether to maximize the viewport (enter Immersive Mode) when recording
- L28 _public member_ `float EngineTimeDilation;` — `UPROPERTY(config, EditAnywhere, Category="User Settings", meta=(Units=Multiplier, ClampMin="0.00001", UIMin="0.00001"))` — The engine time dilation to apply during the recording
- L32 _public member_ `bool bResetPlayhead;` — `UPROPERTY(config, EditAnywhere, Category = "User Settings")` — Reset playhead to beginning of the playback range when starting recording
- L36 _public member_ `bool bStopAtPlaybackEnd;` — `UPROPERTY(config, EditAnywhere, Category = "User Settings")` — Automatically stop recording when reaching the end of the playback range

#### struct `FCacheRecorderProjectParameters`  
`struct FCacheRecorderProjectParameters`  
_L40-80_
- reflection: `USTRUCT()`
- L44 _public prototype_ `FCacheRecorderProjectParameters();`
- L50 _public member_ `FString DefaultSlate;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder")` — The default name to use for the Slate information
- L57 _public member_ `bool bCacheTrackRecorderControlsClockTime = true;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder")` — If true then take recorder will control the sequencer timing when recording with a fixed editor time step. The delta time is derived by the sequence's target frame rate. This is useful when recording cache data where frame accuracy is important (e.g. Niagara systems), but should be set to false when dealing with data from external sources (e.g. LiveLink).
- L63 _public member_ `EUpdateClockSource RecordingClockSource;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder", meta=(EditCondition="!bCacheTrackRecorderControlsClockTime"))` — The clock source to use when recording
- L69 _public member_ `bool bStartAtCurrentTimecode;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder")` — If enabled, track sections will start at the current timecode. Otherwise, 0.
- L75 _public member_ `bool bRecordTimecode;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder")` — If enabled, timecode will be recorded into each actor track
- L79 _public member_ `bool bShowNotifications;` — `UPROPERTY(config, EditAnywhere, Category = "Cache Recorder")` — Whether to show notification windows or not when recording

#### struct `FCacheRecorderParameters`  
`struct FCacheRecorderParameters`  
_L86-98_
- reflection: `USTRUCT()`
- desc: Structure housing all configurable parameters for a take recorder instance
- L91 _public member_ `FCacheRecorderUserParameters User;` — `UPROPERTY(EditAnywhere, Category="Cache Recorder")`
- L94 _public member_ `FCacheRecorderProjectParameters Project;` — `UPROPERTY(EditAnywhere, Category="Cache Recorder")`
- L97 _public member_ `FFrameNumber StartFrame;` — `UPROPERTY(EditAnywhere, Category = "Cache Recorder")`

#### enum `ECacheTrackRecorderState`  
`enum class ECacheTrackRecorderState : uint8`  
_L101-109_
- reflection: `UENUM(BlueprintType)`
- L103 _public enumerator_ `Starting`
- L104 _public enumerator_ `PreRecord`
- L105 _public enumerator_ `TickingAfterPre`
- L106 _public enumerator_ `Started`
- L107 _public enumerator_ `Stopped`
- L108 _public enumerator_ `Cancelled`

#### struct `FCachedTrackSource`  
`struct FCachedTrackSource`  
_L112-120_
- reflection: `USTRUCT()`
- L116 _public member_ `IMovieSceneCachedTrack* Track = nullptr;`
- L119 _public member_ `TObjectPtr<UMovieSceneTrackRecorder> Recorder;` — `UPROPERTY()`

#### class `UCacheTrackRecorder`  
`class UCacheTrackRecorder : public UObject`  
_L123-300_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L132 _public prototype_ `static UCacheTrackRecorder* GetActiveRecorder();` — Retrieve the currently active take recorder instance
- L137 _public prototype_ `static void RecordCacheTrack(IMovieSceneCachedTrack* Track, TSharedPtr<ISequencer> Sequencer, FCacheRecorderParameters Parameters = FCacheRecorderParameters());` — Utility method to record a single cache track
- L142 _public prototype_ `static void RecordCacheTracks(const TArray<IMovieSceneCachedTrack*>& CacheTracks, TSharedPtr<ISequencer> Sequencer, FCacheRecorderParameters Parameters = FCacheRecorderParameters());` — Utility method to record several cache tracks at once
- L147 _public prototype_ `static void RecordSelectedTracks(TSharedPtr<ISequencer> Sequencer, FCacheRecorderParameters Parameters = FCacheRecorderParameters());` — Utility method to record all the cache tracks selected in sequencer
- L153 _public function_ `ULevelSequence* GetSequence() const` — `UFUNCTION(BlueprintCallable, Category="Cache Recorder")` — Access the sequence asset that this recorder is recording into
- L162 _public function_ `ECacheTrackRecorderState GetState() const` — `UFUNCTION(BlueprintCallable, Category="Cache Recorder")` — Get the current state of this recorder
- L171 _public prototype_ `bool Initialize(ULevelSequence* RootLevelSequence, const TArray<IMovieSceneCachedTrack*>& CacheTracks, const FString& Slate, const FCacheRecorderParameters& InParameters, FText* OutError = nullptr);` — Initialize a new recording with the specified parameters. Fails if another recording is currently in progress.
- L176 _public prototype_ `void Stop();` — Called to stop the recording
- L181 _public prototype_ `void Cancel();` — Called to cancel the recording
- L184 _public prototype_ `FQualifiedFrameTime GetRecordTime() const;` — The time at which to record. Taken from the Sequencer global time, otherwise based on timecode
- L191 _private prototype_ `void PreRecord();` — Called after the countdown to PreRecord
- L196 _private prototype_ `void Start();` — Called after PreRecord To Start
- L201 _private prototype_ `void StopInternal(const bool bCancelled);` — Stop or cancel
- L206 _private prototype_ `void Tick(float DeltaTime);` — Ticked by a tickable game object to performe any necessary time-sliced logic
- L211 _private prototype_ `void HandlePIE(bool bIsSimulating);` — Called if we're currently recording a PIE world that has been shut down or if we start PIE in a non-PIE world. Bound in Initialize, and unbound in Stop.
- L216 _private prototype_ `void DiscoverSourceWorld();` — Discovers the source world to record from, and initializes it for recording
- L221 _private prototype_ `void InitializeFromParameters();` — Called to perform any initialization based on the user-provided parameters
- L227 _private prototype_ `bool ShouldShowNotifications();` — Returns true if notification widgets should be shown when recording. It takes into account CacheTrackRecorder project settings, the command line, and global unattended settings.
- L230 _private prototype_ `void BackupEditorTickState();` — Called before setting the editor into a fixed time step mode
- L233 _private prototype_ `void ModifyEditorTickState();` — Sets the editor up to tick in a fixed time step
- L236 _private prototype_ `void RestoreEditorTickState();` — Restores the editor tick state if necessary
- L239 _private prototype_ `void InternalTick(float DeltaTime);` — Called by Tick and Start to make sure we record at start
- L241 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L244 _private member_ `ECacheTrackRecorderState State;` — The state of this recorder instance
- L247 _private member_ `FFrameTime CurrentFrameTime;` — FFrameTime in MovieScene Resolution we are at
- L250 _private member_ `FTimecode TimecodeAtStart;` — Timecode at the start of recording
- L253 _private member_ `TOptional<FFrameNumber> StopRecordingFrame;` — Optional frame to stop recording at
- L257 _private member_ `TObjectPtr<ULevelSequence> SequenceAsset;` — `UPROPERTY(transient)` — The asset that we should output recorded data into
- L261 _private member_ `TWeakObjectPtr<UWorld> WeakWorld;` — `UPROPERTY(transient)` — The world that we are recording within
- L265 _private member_ `FCacheRecorderParameters Parameters;` — `UPROPERTY()` — Parameters for the recorder - marked up as a uproperty to support reference collection
- L268 _private member_ `TArray<FCachedTrackSource> CacheTracks;` — `UPROPERTY()`
- L271 _private member_ `TArray<TFunction<void()>> OnStopCleanup;` — Anonymous array of cleanup functions to perform when a recording has finished
- L274 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Sequencer ptr that controls playback of the desination asset during the recording
- L277 _private member_ `int32 NumberOfTicksAfterPre;` — Due a few ticks after the pre so we are set up with asset creation
- L279 _private member_ `TRange<double> CachedViewRange;`
- L286 _private prototype_ `static bool SetActiveRecorder(UCacheTrackRecorder* NewActiveRecorder);` — Set the currently active take recorder instance
- L288 _private member_ `EUpdateClockSource CachedClockSource;`
- L289 _private member_ `TRange<FFrameNumber> CachedPlaybackRange;`
- L299 _private member_ `FSavedState SavedState;`

#### struct `UCacheTrackRecorder::FSavedState`  
`struct FSavedState`  
_L291-297_
- L293 _public member_ `bool bBackedUp = false;`
- L295 _public member_ `bool bUseFixedTimeStep = false;`
- L296 _public member_ `double FixedDeltaTime = 1.0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CACHETRACKRECORDER_API`
