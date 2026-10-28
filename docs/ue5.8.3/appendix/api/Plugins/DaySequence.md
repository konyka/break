# Plugins / DaySequence

- module root: `Plugins/Experimental/DaySequence/Source/DaySequence`
- headers: 29; symbols: 885
- symbol kinds: class=25, delegate=22, enum=8, enumerator=25, function=45, macro=19, member=246, namespace=15, prototype=449, struct=21, typedef=10
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, InputCore
- PublicDependencyModuleNames: Core, LevelSequence, MovieScene, MovieSceneTracks, UniversalObjectLocator

### `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequenceCheatManagerExtension.h` (Private)


#### class `UDaySequenceCheatManagerExtension`  
`class UDaySequenceCheatManagerExtension final : public UCheatManagerExtension`  
_L13-28_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UCheatManagerExtension`
- desc: Cheats related to DaySequence
- L18 _public prototype_ `UDaySequenceCheatManagerExtension();`
- L21 _public prototype_ `void SetTimeOfDay(float NewTimeOfDay) const;` — `UFUNCTION(Exec)`
- L24 _public prototype_ `void SetTimeOfDaySpeed(float NewTimeOfDaySpeedMultiplier) const;` — `UFUNCTION(Exec)`
- L27 _private prototype_ `ADaySequenceActor* GetDaySequenceActor() const;`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequenceModule.h` (Private)


#### class `FDaySequenceModule`  
`class FDaySequenceModule : public IDaySequenceModule`  
_L12-30_
- inherits: `IDaySequenceModule`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public prototype_ `virtual FDelegateHandle RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner InOnCreateMovieSceneObjectSpawner) override;`
- L21 _public prototype_ `virtual void GenerateObjectSpawners(TArray<TSharedRef<IMovieSceneObjectSpawner>>& OutSpawners) const override;`
- L22 _public prototype_ `virtual void UnregisterObjectSpawner(FDelegateHandle InHandle) override;`
- L26 _public member_ `TArray<FOnCreateMovieSceneObjectSpawner> OnCreateMovieSceneObjectSpawnerDelegates;` — List of object spawner delegates used to extend the spawn register
- L29 _public member_ `FDelegateHandle OnCreateMovieSceneObjectSpawnerDelegateHandle;` — Internal delegate handle used for spawning actors

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDaySequence, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDaySequence, Log, All);`
- L9 _prototype_ `CSV_DECLARE_CATEGORY_EXTERN(DaySequence);`
- L10 _delegate_ `DECLARE_STATS_GROUP(TEXT("Day Sequence Evaluation"), STATGROUP_DaySequenceE`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequencePlayer.h` (Private)


#### struct `FDaySequencePlaybackParams`  
`struct FDaySequencePlaybackParams`  
_L37-60_
- reflection: `USTRUCT()`
- L41 _public function_ `FDaySequencePlaybackParams() : UpdateMethod(EUpdatePositionMethod::Play) , bHasJumped(false)`
- L46 _public function_ `FDaySequencePlaybackParams(FFrameTime InFrame, EUpdatePositionMethod InUpdateMethod) : Frame(InFrame) , UpdateMethod(InUpdateMethod) , bHasJumped(false)`
- L53 _public prototype_ `FFrameTime GetPlaybackPosition (UDaySequencePlayer* Player) const;` — Get the playback position using the player's tick resolution and display rate
- L55 _public member_ `FFrameTime Frame;`
- L57 _public member_ `EUpdatePositionMethod UpdateMethod;`
- L59 _public member_ `bool bHasJumped;`

#### class `UDaySequencePlayer`  
`class UDaySequencePlayer : public UObject , public IMovieScenePlayer , public IDaySequencePlayer`  
_L69-657_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IMovieScenePlayer,IDaySequencePlayer`
- desc: UDaySequencePlayer is used to actually "play" a Day sequence asset at runtime. This class keeps track of playback state and provides functions for manipulating a DaySequence while its playing.
- L79 _public prototype_ `UDaySequencePlayer(const FObjectInitializer&);`
- L84 _public member_ `TScriptInterface<IMovieSceneSequencePlayerObserver> Observer;` — `UPROPERTY(replicated)` — Obeserver interface used for controlling whether this sequence can be played.
- L88 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Start playback forwards from the current time cursor position, using the current play rate.
- L95 _public prototype_ `void PlayLooping(int32 NumLoops = -1);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Start playback from the current time cursor position, looping the specified number of times. @param NumLoops - The number of loops to play. -1 indicates infinite looping.
- L98 _public prototype_ `virtual void Pause() override;` — Pause playback.
- L102 _public prototype_ `void Scrub();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Scrub playback.
- L106 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Stop playback and move the cursor to the end (or start, for reversed playback) of the sequence.
- L110 _public prototype_ `void StopAtCurrentTime();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Stop playback without moving the cursor.
- L114 _public prototype_ `void GoToEndAndStop();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player", meta = (ToolTip = "Go to end of the sequence and stop. Adheres to 'When Finished' section rules."))` — Go to end and stop.
- L116 _public prototype_ `virtual TSharedPtr<UE::DaySequence::FOverrideUpdateIntervalHandle> GetOverrideUpdateIntervalHandle() override;`
- L120 _public prototype_ `virtual bool HasEverEvaluated() const override;`
- L126 _public prototype_ `virtual FQualifiedFrameTime GetCurrentTime() const override;` — Get the current playback position @return The current playback position
- L131 _public prototype_ `virtual FQualifiedFrameTime GetDuration() const override;` — Get the total duration of the sequence
- L137 _public function_ `virtual int32 GetCurrentNumLoops() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Returns the number of times this sequence has been looped
- L143 _public prototype_ `int32 GetFrameDuration() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get this sequence's duration in frames
- L149 _public function_ `FFrameRate GetFrameRate() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get this sequence's display rate.
- L155 _public prototype_ `void SetFrameRate(FFrameRate FrameRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set the frame-rate that this player should play with, making all frame numbers in the specified time-space
- L161 _public function_ `FQualifiedFrameTime GetStartTime() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the offset within the level sequence to start playing
- L167 _public function_ `FQualifiedFrameTime GetEndTime() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the offset within the level sequence to finish playing
- L177 _public prototype_ `void SetWeight(double InWeight);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set a manual weight to be multiplied with all blendable elements within this sequence @note: It is recommended that a weight between 0 and 1 is supplied, though this is not enforced @note: It is recommended that either FMovieSceneSequencePlaybackSettings::DynamicWeighting should be true for this player or the asset it's playing back should be set to enable dynamic weight to avoid undesirable behavior @param InWeight    The weight to suuply to all elements in this sequence
- L183 _public prototype_ `void RemoveWeight();` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Removes a previously assigned weight
- L192 _public prototype_ `void SetWeight(double InWeight, FMovieSceneSequenceID SequenceID);` — Set a manual weight to be multiplied with all blendable elements within the specified sequence @note: It is recommended that a weight between 0 and 1 is supplied, though this is not enforced @note: It is recommended that either FMovieSceneSequencePlaybackSettings::DynamicWeighting should be true for this player or the asset it's playing back should be set to enable dynamic weight to avoid undesirable behavior @param InWeight    The weight to suuply to all elements in this sequence
- L197 _public prototype_ `void RemoveWeight(FMovieSceneSequenceID SequenceID);` — Removes a previously assigned weight
- L208 _public prototype_ `void SetFrameRange( int32 StartFrame, int32 Duration, float SubFrames = 0.f );` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player", DisplayName="Set Play Range (Frames)")` — Set the valid play range for this sequence, determined by a starting frame number (in this sequence player's plaback frame), and a number of frames duration @param StartFrame      The frame number to start playing back the sequence @param Duration        The number of frames to play
- L218 _public prototype_ `void SetPlaybackPosition (FDaySequencePlaybackParams PlaybackParams);` — Set the current time of the player by evaluating from the current time to the specified time, as if the sequence is playing. Triggers events that lie within the evaluated range. Does not alter the persistent playback status of the player (IsPlaying). @param PlaybackParams The position settings (ie. the position to set playback to)
- L222 _public prototype_ `void SetCompletionModeOverride(EMovieSceneCompletionModeOverride CompletionModeOverride);` — `UFUNCTION(BlueprintCallable, Category = "Game|Cinematic")` — Set the state of the completion mode override. Note, setting the state to force restore state will only take effect if the sequence hasn't started playing
- L226 _public prototype_ `EMovieSceneCompletionModeOverride GetCompletionModeOverride() const;` — `UFUNCTION(BlueprintCallable, Category = "Game|Cinematic")` — Get the state of the completion mode override
- L232 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Check whether the sequence is actively playing.
- L236 _public prototype_ `bool IsPaused() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Check whether the sequence is paused.
- L240 _public prototype_ `float GetPlayRate() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the playback rate of this player.
- L247 _public prototype_ `void SetPlayRate(float PlayRate);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set the playback rate of this player. Negative values will play the animation in reverse. @param PlayRate - The new rate of playback for the animation.
- L251 _public function_ `void SetDisableCameraCuts(bool bInDisableCameraCuts)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set whether to disable camera cuts
- L255 _public function_ `bool GetDisableCameraCuts()` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set whether to disable camera cuts
- L258 _public prototype_ `DECLARE_EVENT_ThreeParams( UDaySequencePlayer, FOnDaySequencePlayerUpdated, const UDaySequencePlayer&, FFrameTime , FFrameTime );` — An event that is broadcast each time this level sequence player is updated
- L259 _public function_ `FOnDaySequencePlayerUpdated& OnSequenceUpdated() const`
- L263 _public member_ `FOnDaySequencePlayerEvent OnPlay;` — `UPROPERTY(BlueprintAssignable, Category = "Sequencer|Player")` — Event triggered when the level sequence player is played
- L267 _public member_ `FOnDaySequencePlayerEvent OnPlayReverse;` — `UPROPERTY(BlueprintAssignable, Category = "Sequencer|Player")` — Event triggered when the level sequence player is played in reverse
- L271 _public member_ `FOnDaySequencePlayerEvent OnStop;` — `UPROPERTY(BlueprintAssignable, Category = "Sequencer|Player")` — Event triggered when the level sequence player is stopped
- L275 _public member_ `FOnDaySequencePlayerEvent OnPause;` — `UPROPERTY(BlueprintAssignable, Category = "Sequencer|Player")` — Event triggered when the level sequence player is paused
- L279 _public member_ `FOnDaySequencePlayerEvent OnFinished;` — `UPROPERTY(BlueprintAssignable, Category = "Sequencer|Player")` — Event triggered when the level sequence player finishes naturally (without explicitly calling stop)
- L282 _public member_ `FOnDaySequencePlayerNativeEvent OnNativeFinished;` — Native event triggered when the level sequence player finishes naturally (without explicitly calling stop)
- L288 _public prototype_ `TArray<UObject*> GetBoundObjects(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Retrieve all objects currently bound to the specified binding identifier
- L292 _public prototype_ `TArray<FMovieSceneObjectBindingID> GetObjectBindings(UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the object bindings for the requested object
- L296 _public prototype_ `void RequestInvalidateBinding(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Invalidates the given binding, forcing it to be refetched. This may be useful for some custom bindings that wish their resolution code to be called again.
- L301 _public prototype_ `void SetPlaybackSettings(const FMovieSceneSequencePlaybackSettings& InSettings);` — Assign this player's playback settings
- L304 _public prototype_ `void Initialize(UMovieSceneSequence* InSequence);` — Initialize this player using its existing playback settings
- L307 _public prototype_ `void Initialize(UMovieSceneSequence* InSequence, const FMovieSceneSequencePlaybackSettings& InSettings);` — Initialize this player with a sequence and some settings
- L310 _public prototype_ `void Update(const float DeltaSeconds);` — Update the sequence for the current time, if playing
- L313 _public prototype_ `void UpdateAsync(const float DeltaSeconds);` — Update the sequence for the current time, if playing, asynchronously
- L316 _public prototype_ `void TearDown();` — Perform any tear-down work when this player is no longer (and will never) be needed
- L319 _public prototype_ `bool IsValid() const;` — Returns whether this player is valid, i.e. it has been initialized and not torn down yet
- L328 _public function_ `UMovieSceneSequence* GetSequence() const` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Access the sequence this player is playing @return the sequence currently assigned to this player
- L336 _public prototype_ `FString GetSequenceName(bool bAddClientInfo = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the name of the sequence this player is playing @param bAddClientInfo  If true, add client index if running as a client @return the name of the sequence, or None if no sequence is set
- L341 _public prototype_ `void SetPlaybackClient(TScriptInterface<IMovieScenePlaybackClient> InPlaybackClient);` — Assign a playback client interface for this sequence player, defining instance data and binding overrides
- L346 _public prototype_ `TSharedPtr<FMovieSceneTimeController> GetTimeController() const;` — Retrieve the currently assigned time controller
- L352 _public prototype_ `void SetTimeController(TSharedPtr<FMovieSceneTimeController> InTimeController);` — Assign a time controller for this sequence player allowing custom time management implementations. Will reset the supplied time controller to the current time.
- L359 _public prototype_ `void SetTimeControllerDirectly(TSharedPtr<FMovieSceneTimeController> InTimeController);` — Assign a time controller for this sequence player allowing custom time management implementations. Will not reset the supplied time controller in any way, so the sequence will receive its time directly from the controller.
- L365 _public prototype_ `virtual void SetIgnorePlaybackReplication(bool bState) override;` — Sets whether to listen or ignore playback replication events. @param bState If true, ignores playback replication.
- L369 _protected prototype_ `void PlayInternal();`
- L370 _protected prototype_ `void StopInternal(FFrameTime TimeToResetTo);`
- L371 _protected prototype_ `void FinishPlaybackInternal(FFrameTime TimeToFinishAt);`
- L379 _protected prototype_ `void UpdateMovieSceneInstance(FMovieSceneEvaluationRange InRange, EMovieScenePlayerStatus::Type PlayerStatus, bool bHasJumped = false);`
- L380 _protected prototype_ `virtual void UpdateMovieSceneInstance(FMovieSceneEvaluationRange InRange, EMovieScenePlayerStatus::Type PlayerStatus, const FMovieSceneUpdateArgs& Args);`
- L382 _protected prototype_ `void UpdateTimeCursorPosition(FFrameTime NewPosition, EUpdatePositionMethod Method, bool bHasJumpedOverride = false);`
- L383 _protected prototype_ `bool ShouldStopOrLoop(FFrameTime NewPosition) const;`
- L385 _protected prototype_ `UWorld* GetPlaybackWorld() const;`
- L387 _protected prototype_ `FFrameTime GetLastValidTime() const;`
- L389 _protected prototype_ `FFrameRate GetDisplayRate() const;`
- L391 _protected prototype_ `bool NeedsQueueLatentAction() const;`
- L392 _protected prototype_ `void QueueLatentAction(FMovieSceneSequenceLatentActionDelegate Delegate);`
- L393 _protected prototype_ `void RunLatentActions();`
- L397 _public function_ `virtual FMovieSceneRootEvaluationTemplateInstance& GetEvaluationTemplate() override`
- L401 _protected prototype_ `virtual UMovieSceneEntitySystemLinker* ConstructEntitySystemLinker() override;`
- L402 _protected prototype_ `virtual EMovieScenePlayerStatus::Type GetPlaybackStatus() const override;`
- L403 _protected prototype_ `virtual FMovieSceneSpawnRegister& GetSpawnRegister() override;`
- L404 _protected function_ `virtual UObject* AsUObject() override`
- L406 _protected function_ `virtual void SetPlaybackStatus(EMovieScenePlayerStatus::Type InPlaybackStatus) override`
- L407 _protected function_ `virtual void SetViewportSettings(const TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) override`
- L408 _protected function_ `virtual void GetViewportSettings(TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) const override`
- L410 _protected prototype_ `virtual void ResolveBoundObjects(UE::UniversalObjectLocator::FResolveParams& ResolveParams, const FGuid& InBindingId, FMovieSceneSequenceID SequenceID, UMovieSceneSequence& Sequence, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L411 _protected function_ `virtual IMovieScenePlaybackClient* GetPlaybackClient() override`
- L412 _protected prototype_ `virtual bool HasDynamicWeighting() const override;`
- L413 _protected prototype_ `virtual void PreEvaluation(const FMovieSceneContext& Context) override;`
- L414 _protected prototype_ `virtual void PostEvaluation(const FMovieSceneContext& Context) override;`
- L416 _protected function_ `virtual TScriptInterface<IMovieSceneSequencePlayerObserver> GetObserver() override`
- L419 _protected function_ `virtual bool IsSupportedForNetworking() const` — ~ Begin UObject interface
- L420 _protected prototype_ `virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;`
- L421 _protected prototype_ `virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;`
- L422 _protected prototype_ `virtual void PostNetReceive() override;`
- L423 _protected prototype_ `virtual void BeginDestroy() override;`
- L424 _protected prototype_ `virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;`
- L427 _protected function_ `bool CanPlay() const`
- L431 _private prototype_ `void UpdateTimeCursorPosition_Internal(FFrameTime NewPosition, EUpdatePositionMethod Method, bool bHasJumpedOverride);`
- L433 _private prototype_ `void RunPreEvaluationCallbacks();`
- L434 _private prototype_ `void RunPostEvaluationCallbacks();`
- L436 _private prototype_ `void IncrementServerSerialNumber();`
- L437 _private prototype_ `void AdvanceClientSerialNumberTo(int32 NewSerialNumber);`
- L445 _private prototype_ `void RPC_ExplicitServerUpdateEvent(EUpdatePositionMethod Method, FFrameTime RelevantTime, int32 NewSerialNumber);` — `UFUNCTION(netmulticast, reliable)` — Called on the server whenever an explicit change in time has occurred through one of the (Play|Jump|Scrub)To methods
- L451 _private prototype_ `void RPC_OnStopEvent(FFrameTime StoppedTime, int32 NewSerialNumber);` — `UFUNCTION(netmulticast, reliable)` — Called on the server when Stop() is called in order to differentiate Stops from Pauses.
- L457 _private prototype_ `void RPC_OnFinishPlaybackEvent(FFrameTime StoppedTime, int32 NewSerialNumber);` — `UFUNCTION(netmulticast, reliable)` — Called on the server when playback has reached the end. Could lead to stopping or pausing.
- L463 _private prototype_ `void RPC_OnPlayRateChanged();` — `UFUNCTION(netmulticast, reliable)` — Called on the server when PlaybackSettings.PlayRate changes so that clients can discard server time samples.
- L468 _private prototype_ `bool HasAuthority() const;` — Check whether this sequence player is an authority, as determined by its outer Actor
- L473 _private prototype_ `void UpdateNetworkSyncProperties();` — Update the replicated properties required for synchronizing to clients of this sequence player
- L480 _private prototype_ `FFrameTime UpdateServerTimeSamples();` — Analyse the set of samples we have estimating the server time if we have confidence over the data. Should only be called once per frame. @return An estimation of the server time, or the current local time if we cannot make a strong estimate
- L485 _private prototype_ `void UpdateNetworkSync();` — Check and correct network synchronization for the clients of this sequence player.
- L490 _private prototype_ `float GetPing() const;` — Compute the latency for the client connection.
- L496 _protected member_ `TEnumAsByte<EMovieScenePlayerStatus::Type> Status;` — `UPROPERTY()` — Movie player status.
- L499 _protected member_ `uint32 bPendingOnStartedPlaying : 1;` — Set to true to invoke OnStartedPlaying on first update tick for started playing
- L502 _protected member_ `uint32 bIsAsyncUpdate : 1;` — Set to true when the player is currently in the main level update
- L505 _protected member_ `uint32 bSkipNextUpdate : 1;` — Flag that allows the player to tick its time controller without actually evaluating the sequence
- L508 _protected member_ `uint32 bUpdateNetSync : 1;` — Flag that notifies the player to check network synchronization on next update
- L511 _protected member_ `uint32 bWarnZeroDuration : 1;` — Flag that indicates whether to warn on zero duration playback
- L515 _protected member_ `TObjectPtr<UMovieSceneSequence> Sequence;` — `UPROPERTY(transient)` — The sequence to play back
- L519 _protected member_ `FFrameNumber StartTime;` — `UPROPERTY(replicated)` — Time (in playback frames) at which to start playing the sequence (defaults to the lower bound of the sequence's play range)
- L523 _protected member_ `int32 DurationFrames;` — `UPROPERTY(replicated)` — Time (in playback frames) at which to stop playing the sequence (defaults to the upper bound of the sequence's play range)
- L526 _protected member_ `float DurationSubFrames;` — `UPROPERTY(replicated)`
- L530 _protected member_ `int32 CurrentNumLoops;` — `UPROPERTY(transient)` — The number of times we have looped in the current playback
- L537 _protected member_ `int32 SerialNumber;` — `UPROPERTY(transient)` — The serial number for the current update lifespan It is incremented every time we pass a "gate" such as an RPC call that stops/finishes the sequence.
- L541 _protected member_ `FMovieSceneSequencePlaybackSettings PlaybackSettings;` — `UPROPERTY(replicated)` — Specific playback settings for the animation.
- L545 _protected member_ `FMovieSceneRootEvaluationTemplateInstance RootTemplateInstance;` — `UPROPERTY(transient)` — The root template instance we're evaluating
- L548 _protected member_ `FMovieScenePlaybackPosition PlayPosition;` — Play position helper
- L551 _protected member_ `TSharedPtr<FMovieSceneSpawnRegister> SpawnRegister;` — Spawn register
- L554 _protected member_ `TUniquePtr<UE::MovieScene::FSequenceWeights> SequenceWeights;` — Sequence Weights
- L567 _protected member_ `TArray<FServerTimeSample> ServerTimeSamples;` — Array of server sequence times in seconds, with ping compensation baked in. Samples are sorted chronologically with the oldest samples first
- L572 _protected member_ `float LastEffectiveTimeDilation = 1.0f;` — On UpdateServerTimeSamples, the last recorded time dilation. Used to update the server time samples each update to ensure we can smooth server time even on changing time dilation.
- L576 _protected member_ `FMovieSceneSequenceReplProperties NetSyncProps;` — `UPROPERTY(replicated)` — Replicated playback status and current time that are replicated to clients
- L580 _protected member_ `TScriptInterface<IMovieScenePlaybackClient> PlaybackClient;` — `UPROPERTY(Transient)` — External client pointer in charge of playing back this sequence
- L583 _protected member_ `FMovieSceneLatentActionManager LatentActionManager;` — Local latent action manager for when we're running a blocking sequence
- L586 _protected member_ `TSharedPtr<FMovieSceneTimeController> TimeController;` — (Optional) Externally supplied time controller
- L589 _protected member_ `bool bIgnorePlaybackReplication = false;` — When true, ignore playback replication events.
- L594 _private member_ `mutable FOnDaySequencePlayerUpdated OnDaySequencePlayerUpdate;` — The event that will be broadcast every time the sequence is updated
- L597 _private member_ `TOptional<FMovieSceneSequenceTickInterval> RegisteredTickInterval;` — The tick interval we are currently registered with (if any)
- L600 _private member_ `TOptional<double> OldMaxTickRate;` — The maximum tick rate prior to playing (used for overriding delta time during playback).
- L603 _private member_ `bool bOverridingDynResFrameTimeBudget = false;` — Whether dynamic resolution frame time budget is being overridden.
- L609 _private member_ `TOptional<float> LastTickGameTimeSeconds;` — The last world game time at which we were ticked. Game time used is dependent on bTickEvenWhenPaused Valid only if we've been ticked at least once since having a tick interval
- L612 _private prototype_ `DECLARE_DELEGATE(FOnEvaluationCallback);` — Pre and post evaluation callbacks, for async evaluations
- L613 _private member_ `TArray<FOnEvaluationCallback> PreEvaluationCallbacks;`
- L614 _private member_ `TArray<FOnEvaluationCallback> PostEvaluationCallbacks;`
- L625 _public prototype_ `void Initialize(UDaySequence* InDaySequence, ADaySequenceActor* Owner, const FMovieSceneSequencePlaybackSettings& Settings);` — Initialize the player. @param InDaySequence The DaySequence to play. @param Owner The day sequence actor that owns this player @param Settings The desired playback settings
- L627 _public prototype_ `void Tick(float DeltaSeconds);`
- L630 _public prototype_ `virtual UObject* GetPlaybackContext() const override;` — IMovieScenePlayer interface
- L632 _public prototype_ `void RewindForReplay();`
- L637 _private member_ `TWeakObjectPtr<ADaySequenceActor> WeakOwner;` — The owning Day Sequence Actor that created this player
- L640 _private member_ `TObjectPtr<UMovieSceneEntitySystemLinker> Linker;` — `UPROPERTY(Transient)`
- L642 _private member_ `TSharedPtr<FMovieSceneEntitySystemRunner> Runner;`
- L645 _private member_ `unsigned OverrideUpdateIntervalRequesterCount = 0;` — Set by FOverrideUpdateIntervalHandle
- L647 _private member_ `float DesiredUpdateInterval = 0.f;`
- L648 _private member_ `float DesiredBudgetMs = 0.f;`
- L649 _private member_ `bool bUpdateWhenPaused = false;`
- L652 _private member_ `float LastUnpausedTimeSeconds = -1;` — The value of UWorld::GetUnpausedTimeSeconds last time this player was evaluated
- L654 _private member_ `float LastTimeSeconds = -1;` — The value of UWorld::GetTimeSeconds last time this player was evaluated
- L656 _private member_ `bool bHasEverEvaluated = false;`

#### struct `UDaySequencePlayer::FMovieSceneUpdateArgs`  
`struct FMovieSceneUpdateArgs`  
_L373-377_
- L375 _public member_ `bool bHasJumped = false;`
- L376 _public member_ `bool bIsAsync = false;`

#### struct `UDaySequencePlayer::FServerTimeSample`  
`struct FServerTimeSample`  
_L556-562_
- L559 _public member_ `double ServerTime;` — The actual server sequence time in seconds, with client ping at the time of the sample baked in
- L561 _public member_ `double ReceivedTime;` — Wall-clock time that the sample was receieved

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API DAYSEQUENCE_API`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MovieScene` (scope `UE`)
- L33 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDaySequencePlayerEvent);`
- L33 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDaySequencePlayerEvent);`
- L34 _delegate_ `DECLARE_DELEGATE(FOnDaySequencePlayerNativeEvent);`
- L34 _prototype_ `DECLARE_DELEGATE(FOnDaySequencePlayerNativeEvent);`
- L258 _delegate_ `DECLARE_EVENT_ThreeParams( UDaySequencePlayer, FOnDaySequencePlayerUpdated, const UDaySequencePlayer&, FFrameTime , FFrameTime );` — An event that is broadcast each time this level sequence player is updated
- L612 _delegate_ `DECLARE_DELEGATE(FOnEvaluationCallback);` — Pre and post evaluation callbacks, for async evaluations

### `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequenceProjectSettings.h` (Private)


#### class `UDaySequenceProjectSettings`  
`class UDaySequenceProjectSettings : public UDeveloperSettings`  
_L12-35_
- reflection: `UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Day Sequence"))`
- inherits: `UDeveloperSettings`
- desc: Settings for Day sequences
- L17 _public prototype_ `UDaySequenceProjectSettings();`
- L20 _public member_ `bool bDefaultLockEngineToDisplayRate;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="DaySequence.DefaultLockEngineToDisplayRate", Tooltip="0: Playback locked to playback frames\n1: Unlocked playback with sub frame interpolation"))`
- L23 _public member_ `FString DefaultDisplayRate;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="DaySequence.DefaultDisplayRate", Tooltip="Specifies default display frame rate for newly created Day sequences; also defines frame locked frame rate where sequences are set to be frame locked. Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms)."))`
- L26 _public member_ `FString DefaultTickResolution;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="DaySequence.DefaultTickResolution", Tooltip="Specifies default tick resolution for newly created Day sequences. Examples: 30 fps, 120/1 (120 fps), 30000/1001 (29.97), 0.01s (10ms)."))`
- L29 _public member_ `EUpdateClockSource DefaultClockSource;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ConsoleVariable="DaySequence.DefaultClockSource", Tooltip="Specifies default clock source for newly created Day sequences. Examples: 0: Tick, 1: Platform, 2: Audio, 3: RelativeTimecode, 4: Timecode, 5: Custom"))`
- L31 _public prototype_ `virtual void PostInitProperties() override;`
- L33 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Private/DaySequenceStaticTime.h` (Private)


#### struct `UE::DaySequence::FStaticTimeInfo`  
`struct FStaticTimeInfo`  
_L15-19_
- desc: The fundamental piece of data used by the static time system.
- L17 _public member_ `float BlendWeight = 0.f;`
- L18 _public member_ `float StaticTime = 0.f;`

#### enum `UE::DaySequence::EStaticTimeChannel`  
`enum class EStaticTimeChannel`  
_L27-32_
- L29 _public enumerator_ `None = 0`
- L30 _public enumerator_ `FixedTime = 1 << 0`
- L31 _public enumerator_ `LocalFixedTime = 1 << 1`

#### struct `UE::DaySequence::FStaticTimeContributor`  
`struct FStaticTimeContributor`  
_L36-52_
- desc: Contributors register an instance of this struct in order to request a static time.
- L39 _public member_ `TWeakObjectPtr<UObject> UserObject;` — Determines the lifetime of the object and prevents double registration.
- L42 _public member_ `int32 Priority;` — Used for sorting contributors
- L45 _public member_ `FWantsStaticTimeFunction WantsStaticTime;` — Returns whether or not this contributor is active.
- L48 _public member_ `FGetStaticTimeFunction GetStaticTime;` — Provides caller with desired static time information.
- L51 _public member_ `EStaticTimeChannel Channels = EStaticTimeChannel::FixedTime;` — The channel(s) that this static time contributor affects.

#### struct `UE::DaySequence::FStaticTimeChannelData`  
`struct FStaticTimeChannelData`  
_L54-61_
- L57 _public member_ `int LastBlendWinding = 0;` — Cached blend data
- L58 _public member_ `int LastBlendOffset = 0;`
- L59 _public member_ `TOptional<float> LastBlendDelta;`
- L60 _public member_ `TOptional<int> LastBlendDirection;`

#### struct `UE::DaySequence::FStaticTimeManager`  
`struct FStaticTimeManager`  
_L63-84_
- L65 _public prototype_ `void AddStaticTimeContributor(const FStaticTimeContributor& NewContributor);`
- L66 _public prototype_ `void RemoveStaticTimeContributor(const UObject* UserObject);`
- L67 _public prototype_ `bool HasStaticTime(EStaticTimeChannel InChannels = EStaticTimeChannel::FixedTime) const;`
- L68 _public prototype_ `float GetStaticTime(float InitialTime, float DayLength, EStaticTimeChannel InChannels = EStaticTimeChannel::FixedTime) const;`
- L69 _public prototype_ `float GetTargetStaticTime(float InitialTime, EStaticTimeChannel InChannels) const;`
- L72 _private prototype_ `void ResetBlendState(EStaticTimeChannel InChannels) const;`
- L75 _private prototype_ `FStaticTimeInfo ProcessPriorityGroup(EStaticTimeChannel InChannels, int32 StartIdx, int32 EndIdx, TOptional<float> OverrideWeight = TOptional<float>()) const;` — Handles multiple contributors of the same priority by averaging their weights and times and returning a single desired weight and time
- L77 _private member_ `TArray<FStaticTimeContributor> Contributors;`
- L80 _private member_ `TMap<int32, int32> PriorityGroupSizes;` — We precompute this when mutating the Contributors array to avoid redundant reiteration over Contributors when computing static time
- L83 _private member_ `mutable TMap<EStaticTimeChannel, FStaticTimeChannelData> Channels;` — Mutable because cached data is set in (Has/Get)StaticTime.

#### class `UDaySequenceStaticTimeContributor`  
`class UDaySequenceStaticTimeContributor : public UObject`  
_L92-126_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: A Blueprint exposed static time contributor. Used to contribute to static time blending for the specified Day Sequence Actor without needing to spawn actors and/or components.
- L98 _public prototype_ `UDaySequenceStaticTimeContributor();`
- L100 _public prototype_ `virtual void BeginDestroy() override;`
- L104 _public member_ `float BlendWeight;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Day Sequence")` — The desired blend weight. Once bound to a Day Sequence Actor, this can be freely changed without rebinding.
- L108 _public member_ `float StaticTime;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Day Sequence")` — The desired static time. Once bound to a Day Sequence Actor, this can be freely changed without rebinding.
- L112 _public member_ `bool bWantsStaticTime;` — `UPROPERTY(Interp, BlueprintReadWrite, Category = "Day Sequence")` — Determines whether or not this contributor is effective once we are bound. This can be freely changed to enable/disable the contributor without rebinding.
- L116 _public prototype_ `void BindToDaySequenceActor(ADaySequenceActor* InTargetActor, int32 Priority = 1000);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")` — Begin contributing static time to the specified actor.
- L120 _public prototype_ `void UnbindFromDaySequenceActor();` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")` — Stop contributing static time.
- L125 _private member_ `TObjectPtr<ADaySequenceActor> TargetActor;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DaySequence` (scope `UE`)
- L22 _typedef_ `using FWantsStaticTimeFunction = TFunction<bool()>;` (scope `UE::DaySequence`) — The function signature for the static time requested callback. Must return true for a contributor to be considered
- L25 _typedef_ `using FGetStaticTimeFunction = TFunction<bool(FStaticTimeInfo& OutRequest)>;` (scope `UE::DaySequence`) — The function signature for the static time info getter callback. Only called if WantsStaticTime returns true.
- L33 _prototype_ `ENUM_CLASS_FLAGS(EStaticTimeChannel);` (scope `UE::DaySequence`)

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/Actors/BaseDaySequenceActor.h` (Public)


#### class `ABaseDaySequenceActor`  
`class ABaseDaySequenceActor : public ADaySequenceActor`  
_L24-64_
- reflection: `UCLASS(MinimalAPI, Blueprintable, HideCategories=(Tags, Networking, LevelInstance))`
- inherits: `ADaySequenceActor`
- desc: A self-registering Day Sequence Actor with a simple set of lighting components (some of which are optional). Can be used as-is or extended by derived classes (see ASunPositionDaySequenceActor).
- L30 _public prototype_ `ABaseDaySequenceActor(const FObjectInitializer& Init);`
- L35 _protected prototype_ `virtual void BeginPlay() override;` — BeginPlay and OnConstruction overrides auto-register this actor with the DaySequenceSubsystem.
- L36 _protected prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L43 _protected member_ `TObjectPtr<USceneComponent> SunRootComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L46 _protected member_ `TObjectPtr<UDirectionalLightComponent> SunComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L49 _protected member_ `TObjectPtr<USkyAtmosphereComponent> SkyAtmosphereComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L52 _protected member_ `TObjectPtr<USkyLightComponent> SkyLightComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L57 _protected member_ `TObjectPtr<UExponentialHeightFogComponent> ExponentialHeightFogComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L60 _protected member_ `TObjectPtr<UVolumetricCloudComponent> VolumetricCloudComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day Sequence", meta = (AllowPrivateAccess = "true"))`
- L63 _protected member_ `TObjectPtr<UStaticMeshComponent> SkySphereComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Day Sequence", meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/Actors/DaySequenceModifierVolume.h` (Public)


#### class `ADaySequenceModifierVolume`  
`class ADaySequenceModifierVolume : public AActor`  
_L20-90_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AActor`
- L25 _public prototype_ `ADaySequenceModifierVolume(const FObjectInitializer& Init);`
- L28 _public prototype_ `void OnDaySequenceActorBound(ADaySequenceActor* InActor);` — `UFUNCTION(BlueprintImplementableEvent)`
- L31 _public prototype_ `void OnPostEnableModifier();` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor)`
- L35 _protected prototype_ `virtual void BeginPlay() override;`
- L36 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L37 _protected prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L41 _protected prototype_ `void Initialize();` — Primary initialization entry point to clarify initialization control flow and to consolidate editor and runtime initialization.
- L42 _protected prototype_ `void Deinitialize();`
- L45 _protected prototype_ `void DaySequenceActorSetup();` — Wrapper for SetupDaySequenceSubsystemCallbacks and BindToDaySequenceActor.
- L48 _protected prototype_ `void SetupDaySequenceSubsystemCallbacks();` — Registers a callback that calls BindToDaySequenceActor when the world's current Day Sequence Actor changes.
- L51 _protected prototype_ `void BindToDaySequenceActor();` — Binds all modifier components to the world's current Day Sequence Actor.
- L54 _protected prototype_ `void CreatePlayer(APlayerController* InPC);` — Initializes a modifier component for this player controller. Will create an additional component if necessary.
- L58 _protected member_ `TObjectPtr<UDaySequenceModifierComponent> DaySequenceModifier;` — `UPROPERTY(VisibleAnywhere, Category = "Day Sequence", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L61 _protected member_ `TObjectPtr<UBoxComponent> DefaultBox;` — `UPROPERTY(VisibleAnywhere, Category = "Day Sequence", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))`
- L64 _protected member_ `TObjectPtr<ADaySequenceActor> DaySequenceActor;` — `UPROPERTY(Transient, DuplicateTransient)`
- L68 _protected member_ `TObjectPtr<APlayerController> CachedPlayerController;` — `UE_DEPRECATED(5.8, "Replaced with CachedPlayer")` — `UPROPERTY(Transient, DuplicateTransient, meta = (DeprecatedProperty, DeprecationMessage = "Replaced with CachedPlayer"))`
- L71 _protected member_ `TObjectPtr<UPlayer> CachedPlayer;` — `UPROPERTY(Transient, DuplicateTransient)`
- L73 _protected member_ `FDelegateHandle ReplayScrubbedHandle;`
- L76 _private prototype_ `bool IsSplitscreenSupported() const;`
- L79 _private member_ `bool bEnableSplitscreenSupport;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Day Sequence", DisplayName = "Enable Experimental Splitscreen Support")`
- L87 _private member_ `TMap<TObjectPtr<UPlayer>, TObjectPtr<UDaySequenceModifierComponent>> AdditionalPlayers;` — `UPROPERTY(Transient, DuplicateTransient)` — Transient modifier components associated with additional local players (primarily for split screen support) Key: Local player Value: Optional transient modifier component
- L89 _private member_ `FDelegateHandle ActorSpawnedHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/Actors/SunMoonDaySequenceActor.h` (Public)


#### class `ASunMoonDaySequenceActor`  
`class ASunMoonDaySequenceActor : public ABaseDaySequenceActor`  
_L16-27_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `ABaseDaySequenceActor`
- desc: A Day Sequence Actor that represents a physically accurate 24 hour day cycle.
- L22 _public prototype_ `ASunMoonDaySequenceActor(const FObjectInitializer& Init);`
- L26 _protected member_ `TObjectPtr<UDirectionalLightComponent> MoonComponent;` — `UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category= "Day Sequence", meta = (AllowPrivateAccess = "true"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequence.h` (Public)


#### class `UDaySequence`  
`class UDaySequence : public UMovieSceneSequence , public IInterface_AssetUserData`  
_L17-129_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories=(Object))`
- inherits: `UMovieSceneSequence,IInterface_AssetUserData`
- L25 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()` — Pointer to the movie scene that controls this animation.
- L28 _public prototype_ `UDaySequence(const FObjectInitializer&);`
- L31 _public prototype_ `virtual void Initialize();` — Initialize this sequence.
- L32 _public prototype_ `virtual void Initialize(EObjectFlags Flags);`
- L34 _public prototype_ `void AddDefaultBinding(const FGuid& PossessableGuid);`
- L36 _public prototype_ `void AddSpecializedBinding(EDaySequenceBindingReferenceSpecialization Specialization);`
- L37 _public prototype_ `FGuid GetSpecializedBinding(EDaySequenceBindingReferenceSpecialization Specialization) const;`
- L40 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;` — UMovieSceneSequence interface
- L41 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L42 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L43 _public prototype_ `virtual FGuid FindBindingFromObject(UObject* InObject, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) const override;`
- L44 _public prototype_ `virtual void GatherExpiredObjects(const FMovieSceneObjectCache& InObjectCache, TArray<FGuid>& OutInvalidIDs) const override;`
- L45 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L46 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L47 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L48 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* InContext) override;`
- L49 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* InContext) override;`
- L50 _public prototype_ `virtual bool AllowsSpawnableObjects() const override;`
- L51 _public prototype_ `virtual bool CanRebindPossessable(const FMovieScenePossessable& InPossessable) const override;`
- L52 _public prototype_ `virtual UObject* MakeSpawnableTemplateFromInstance(UObject& InSourceObject, FName ObjectName) override;`
- L53 _public prototype_ `virtual bool CanAnimateObject(UObject& InObject) const override;`
- L54 _public prototype_ `virtual UObject* CreateDirectorInstance(TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID SequenceID) override;`
- L55 _public prototype_ `virtual void PostLoad() override;`
- L56 _public prototype_ `virtual void PostInitProperties() override;`
- L57 _public prototype_ `virtual bool Rename(const TCHAR* NewName = nullptr, UObject* NewOuter = nullptr, ERenameFlags Flags = REN_None) override;`
- L60 _public prototype_ `virtual void AddAssetUserData(UAssetUserData* InUserData) override;`
- L61 _public prototype_ `virtual void RemoveUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L62 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass(TSubclassOf<UAssetUserData> InUserDataClass) override;`
- L63 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L67 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L68 _public prototype_ `virtual bool IsFilterSupportedImpl(const FString& InFilterName) const override;`
- L69 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L71 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, UDaySequence*);`
- L72 _public member_ `static FPostDuplicateEvent PostDuplicateEvent;`
- L75 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L84 _public prototype_ `void SetDirectorBlueprint(UBlueprint* NewDirectorBlueprint);` — Assign a new director blueprint to this sequence. The specified blueprint *must* be contained within this object.?
- L89 _public prototype_ `UBlueprint* GetDirectorBlueprint() const;` — Retrieve the currently assigned director blueprint for this sequence
- L91 _public prototype_ `FString GetDirectorBlueprintName() const;`
- L95 _protected prototype_ `virtual FGuid CreatePossessable(UObject* ObjectToPossess) override;`
- L96 _protected prototype_ `virtual FGuid CreateSpawnable(UObject* ObjectToSpawn) override;`
- L98 _protected prototype_ `FGuid FindOrAddBinding(UObject* ObjectToPossess);`
- L103 _protected prototype_ `void OnDirectorRecompiled(UBlueprint*);` — Invoked when this sequence's director blueprint has been recompiled
- L110 _protected member_ `FDaySequenceBindingReferences BindingReferences;` — `UPROPERTY()` — References to bound objects.
- L115 _protected member_ `TObjectPtr<UBlueprint> DirectorBlueprint;` — `UPROPERTY()` — A pointer to the director blueprint that generates this sequence's DirectorClass.
- L123 _protected member_ `TObjectPtr<UClass> DirectorClass;` — `UPROPERTY()` — The class that is used to spawn this sequence's director instance. Director instances are allocated on-demand one per sequence during evaluation and are used by event tracks for triggering events.
- L128 _protected member_ `TArray<TObjectPtr<UAssetUserData>> AssetUserData;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Instanced, Category = Animation)` — Array of user data stored with the asset

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DAYSEQUENCE_API`
- L71 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, UDaySequence*);`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceActor.h` (Public)


#### struct `UE::DaySequence::FDaySequenceDebugEntry`  
`struct FDaySequenceDebugEntry`  
_L55-66_
- desc: This provides methods for determining if this debug entry should be shown and for getting a pointer to the debug data. Anything (Currently only DaySequenceModifierComponents) can submit one of these entries to a DaySequenceActor. The debug data can be printed in play with the command "showdebug DaySequence" if ShowCondition evaluates to true.
- L57 _public typedef_ `using FShowDebugDataConditionFunction = TFunction<bool()>;`
- L58 _public typedef_ `using FGetDebugDataFunction = TFunction<TSharedPtr<TMap<FString, FString>>()>;`
- L59 _public typedef_ `using FGetNumericValue = TFunction<int32()>;`
- L61 _public prototype_ `FDaySequenceDebugEntry(FShowDebugDataConditionFunction InShowCondition, FGetDebugDataFunction InGetData, FGetNumericValue InGetNumericValue);`
- L63 _public member_ `FShowDebugDataConditionFunction ShowCondition;`
- L64 _public member_ `FGetDebugDataFunction GetData;`
- L65 _public member_ `FGetNumericValue GetNumericValue;`

#### class `ADaySequenceActor`  
`class ADaySequenceActor : public AInfo , public IMovieScenePlaybackClient , public IMovieSceneBindingOwnerInterface`  
_L84-655_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `AInfo,IMovieScenePlaybackClient,IMovieSceneBindingOwnerInterface`
- L92 _public prototype_ `ADaySequenceActor(const FObjectInitializer& Init);`
- L95 _public prototype_ `IDaySequencePlayer* GetSequencePlayer() const;` — Access this actor's sequence player, or None if it is invalid (not yet initialized or already destroyed)
- L104 _public prototype_ `bool ContainsDaySequence(const UDaySequence* InDaySequence);` — `UFUNCTION(BlueprintCallable, Category="Sequence")` — Returns true if the given InDaySequence is referenced by any entry in the DaySequences map property. @param InDaySequence the sequence to search for @return true if InDaySequence exists in the DaySequences map.
- L108 _public prototype_ `void SetReplicatePlayback(bool ReplicatePlayback);` — `UFUNCTION(BlueprintSetter)` — Set whether or not to replicate playback for this actor
- L111 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L117 _public prototype_ `void ConditionalSetTimeOfDayPreview(float InHours);` — Set the TimeOfDayPreview if it is currently different from the specified time. @param InHours preview time to set in hours.
- L123 _public prototype_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnTimeOfDayPreviewChangedEvent, float) FOnTimeOfDayPreviewChangedEvent OnTimeOfDayPreviewChangedEvent;` — Native event invoked when the TimeOfDayPreview property is changed. @param new preview time in hours.
- L131 _public prototype_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnSubSectionRemovedEvent, const UMovieSceneSubSection*) static FOnSubSectionRemovedEvent OnSubSectionRemovedEvent;` — Native event invoked when a subsection is removed from the Root Sequence. Primarily called by modifier components but generally callable by anything that adds a subsection to the root sequence. @param The subsection being removed.
- L137 _public prototype_ `float GetTimeOfDayPreview() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — @return the preview time in hours.
- L144 _public prototype_ `void SetTimeOfDayPreview(float InHours);` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Set the TimeOfDayPreview and broadcast the event. @param InHours preview time to set in hours.
- L150 _public prototype_ `bool GetRunDayCycle() const;` — Get bRunDayCycle, a bool that determines whether or not the day cycle can be played back. @return bRunDayCycle
- L156 _public prototype_ `void SetRunDayCycle(bool bNewRunDayCycle);` — Set bRunDayCycle, a bool that determines whether or not the day cycle can be played back. @param bNewRunDayCycle The new value for bRunDayCycle
- L164 _public prototype_ `float GetDayLength() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get the length of each day in hours. @return float, time in hours.
- L174 _public prototype_ `void SetDayLength(float InHours);` — Set the duration of the day in game time in hours. This is currently intentionally not exposed to Blueprint since this property can only be realized by rebuilding the root sequence. @param InHours day length in hours.
- L182 _public prototype_ `float GetTimePerCycle() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get the duration of each day cycle in hours (assuming PlayRate is 1.0) @return float, time in hours
- L192 _public prototype_ `void SetTimePerCycle(float InHours);` — Set the duration of a day cycle in real time in hours. This is currently intentionally not exposed to Blueprint since the effect is achieved by changing PlayRate at runtime. @param InHours time per cycle in hours.
- L201 _public prototype_ `void SetPlayRate(float NewRate);` — `UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category=RuntimeDayCycle)` — Sets the play rate of the day cycle at runtime. A play rate of 2.0 will result in a day cycle that is half as long as Time Per Cycle. @param NewRate The new play rate.
- L209 _public prototype_ `float GetPlayRate() const;` — `UFUNCTION(BlueprintCallable, Category=RuntimeDayCycle)` — Gets the play rate of the day cycle at runtime. Always 1 in editor worlds. @return The current play rate.
- L225 _public prototype_ `void Multicast_SetTimePerCycle(float InHours);` — `UE_DEPRECATED(5.6, "Multicast_SetTimePerCycle is deprecated, use SetPlayRate instead.")` — `UFUNCTION(NetMulticast, Reliable)` — Set the duration of a day cycle in real time in hours and update the root sequence in game. This method is the network multicast variant of SetTimePerCycle. In game, this will properly update the root sequence and subsequence time scales on both the server and the client. These changes must be invoked on both server and client since only playback position & status are replicated. @param InHours time per cycle in hours.
- L233 _public prototype_ `float GetInitialTimeOfDay() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get the initial time of day in hours. @return float, time in hours
- L243 _public prototype_ `void SetInitialTimeOfDay(float InHours);` — Set the initial time of day in game time in hours. This is currently intentionally not exposed to Blueprint since this property can only be realized by rebuilding the root sequence. @param InHours initial time of day.
- L251 _public prototype_ `float GetTimeOfDay() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get the current time of day in hours. @return float, time in hours
- L260 _public prototype_ `float GetApparentTimeOfDay() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get the current apparent time of day in hours. This is distinct from the actual time of day in that it is affected by static time and the day interp curve. @return float, time in hours
- L270 _public prototype_ `float GetTargetApparentTimeOfDay() const;` — Get the current target apparent time of day in hours. This is distinct from apparent time of day in that it is only capturing the target time of static time contributors. The target time is determined by the highest priority static time contributor independent of blend weight. Multiple contributors at the same priority will return the average of their target times. @return float, time in hours
- L278 _public prototype_ `bool SetTimeOfDay(float InHours);` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Set the current time of day in hours (server only). @param InHours time of day in hours
- L282 _public prototype_ `void Play();` — `UFUNCTION(BlueprintCallable, Category="Playback")` — Resume playback of the sequence.
- L286 _public prototype_ `void Pause();` — `UFUNCTION(BlueprintCallable, Category="Playback")` — Pause playback of the sequence.
- L290 _public prototype_ `bool IsPlaying() const;` — `UFUNCTION(BlueprintCallable, Category="Playback")` — @return true if the sequence is playing.
- L294 _public prototype_ `bool IsPaused() const;` — `UFUNCTION(BlueprintCallable, Category="Playback")` — @return true if the sequence is paused.
- L300 _public prototype_ `bool HasStaticTimeOfDay() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Check whether this day sequence actor has a static (fixed) time-of-day
- L306 _public prototype_ `float GetStaticTimeOfDay() const;` — `UFUNCTION(BlueprintCallable, Category="TimeOfDay")` — Get this day sequence actor's static (fixed) time-of-day, or GetTimeOfDay() if it doesn't have one
- L308 _public prototype_ `void RegisterStaticTimeContributor(const UE::DaySequence::FStaticTimeContributor& NewContributor) const;`
- L309 _public prototype_ `void UnregisterStaticTimeContributor(const UObject* InUserObject) const;`
- L311 _public prototype_ `void RegisterBindingResolveFunction(FMovieSceneSequenceID SequenceID, FGuid Guid, TFunction<bool(TArray<UObject*, TInlineAllocator<1>>&)> InFunction);`
- L312 _public prototype_ `void UnregisterBindingResolveFunction(FMovieSceneSequenceID SequenceID, FGuid Guid = FGuid());`
- L314 _public function_ `UDaySequenceCameraModifierManager* GetCameraModifierManager()`
- L316 _public prototype_ `UDaySequence* GetRootSequence() const;`
- L327 _public prototype_ `virtual void UpdateRootSequence(EUpdateRootSequenceMode Mode = EUpdateRootSequenceMode::Update);`
- L329 _public prototype_ `void UpdateRootSequenceOnTick(EUpdateRootSequenceMode Mode = EUpdateRootSequenceMode::Update);`
- L332 _public prototype_ `bool HasValidRootSequence() const;`
- L333 _public prototype_ `bool RootSequenceHasValidSections() const;`
- L336 _public function_ `DECLARE_EVENT(ADaySequenceActor, FOnRootSequenceChanged) FOnRootSequenceChanged& GetOnPostRootSequenceChanged()`
- L338 _public function_ `FOnRootSequenceChanged& GetOnPreRootSequenceChanged()`
- L347 _public typedef_ `using FSubSectionPreserveMap = TMap<UMovieSceneSubSection*, bool>;` — This delegate is broadcast after the Day Sequence Actor has initialized all of its own sequences to allow other sequence providers to initialize their own sequences. If external providers were previously initialized, they should cache their created subsections and then check to see if they exist in this map. If they do, the bool associated with that subsection in this map can be set to true and it will be preserved. All subsections that map to false will be deleted from the root sequence shortly after this delegate is broadcast.
- L348 _public function_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnPostInitializeDaySequences, FSubSectionPreserveMap*) FOnPostInitializeDaySequences& GetOnPostInitializeDaySequences()`
- L356 _public function_ `DECLARE_EVENT(ADaySequenceActor, FOnDaySequenceUpdate) FOnDaySequenceUpdate& GetOnDaySequenceUpdate()` — This delegate is broadcast at a rate matching this actor's tick interval. It is either broadcast after each sequence player update or by a timer that is configured to run only when the sequence player is paused. Used to synchronize polling logic that is not owned by this actor when it should occur at an interval specified by this actor.
- L359 _public prototype_ `void InvalidateMuteStates() const;`
- L362 _public member_ `const FName ShowDebug_GeneralCategory = "Da`
- L363 _public member_ `const FName ShowDebug_SubSequenceCategory = "Da`
- L365 _public function_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnDebugLevelChanged, int32) FOnDebugLevelChanged& GetOnDebugLevelChanged()`
- L367 _public function_ `int32 GetDebugLevel() const`
- L369 _public prototype_ `bool IsDebugCategoryRegistered(const FName& Category) const;`
- L370 _public prototype_ `void RegisterDebugCategory(const FName& Category, UE::DaySequence::FDebugCategoryDrawFunction DrawFunction);`
- L372 _public prototype_ `void RegisterDebugEntry(const TWeakPtr<UE::DaySequence::FDaySequenceDebugEntry>& DebugEntry, const FName& Category);`
- L373 _public prototype_ `void UnregisterDebugEntry(const TWeakPtr<UE::DaySequence::FDaySequenceDebugEntry>& DebugEntry, const FName& Category);`
- L376 _public prototype_ `static void OnShowDebugInfoDrawFunction(UCanvas* Canvas, TArray<TSharedPtr<TMap<FString, FString>>>& Entries, const FString& Category);` — This will be called once per category and is passed the data for all entries associated with this category
- L383 _public prototype_ `void UpdateSubSectionTimeScale(UMovieSceneSubSection* InSubSection) const;` — Normalizes a subsection's timescale and frame range to the root sequence such that the subsection's sequence represents a full day cycle.
- L392 _public prototype_ `TObjectPtr<UDaySequenceConditionTag> GetOrInstantiateConditionTag(const TSubclassOf<UDaySequenceConditionTag>& ConditionClass);` — Returns a TObjectPtr which is valid if ConditionTagClass is a subclass of UDaySequenceConditionTag and nullptr otherwise.
- L395 _public prototype_ `bool EvaluateSequenceConditions(bool bInitialMuteState, const FDaySequenceConditionSet::FConditionValueMap& InConditions);` — Called to evaluate a particular set of conditions. Instantiates conditions if necessary. TODO: remove bInitialMuteState
- L398 _public prototype_ `void BindToConditionCallbacks(UObject* LifetimeObject, const FDaySequenceConditionSet::FConditionValueMap& InConditions, const TFunction<void(void)>& InFunction);` — Called to register InFunction as a callback for instances matching InConditions with a lifetime equivalent to LifetimeObject.
- L401 _public prototype_ `void HandleConditionReinstanced(const FCoreUObjectDelegates::FReplacementObjectMap& OldToNewInstanceMap);`
- L406 _protected prototype_ `virtual void PostLoad() override;`
- L407 _protected prototype_ `virtual void BeginDestroy() override;`
- L409 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L414 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L415 _protected prototype_ `virtual void BeginPlay() override;`
- L416 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L417 _protected prototype_ `virtual void RewindForReplay() override;`
- L418 _protected prototype_ `virtual void Destroyed() override;`
- L419 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L422 _protected function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L426 _protected prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L428 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L429 _protected prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L433 _protected prototype_ `virtual bool RetrieveBindingOverrides(const FGuid& InBindingId, FMovieSceneSequenceID InSequenceID, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L434 _protected prototype_ `virtual UObject* GetInstanceData() const override;`
- L435 _protected prototype_ `virtual bool GetIsReplicatedPlayback() const override;`
- L436 _protected prototype_ `virtual void WarpEvaluationRange(FMovieSceneEvaluationRange& InOutRange) const override;`
- L441 _protected prototype_ `virtual TSharedPtr<FStructOnScope> GetObjectPickerProxy(TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L442 _protected prototype_ `virtual void UpdateObjectFromProxy(FStructOnScope& Proxy, IPropertyHandle& ObjectPropertyHandle) override;`
- L443 _protected prototype_ `virtual UMovieSceneSequence* RetrieveOwnedSequence() const override;`
- L448 _protected prototype_ `void InitializePlayer();` — Initialize SequencePlayer with transient root sequence
- L449 _protected prototype_ `void InitializeRootSequence();`
- L450 _protected prototype_ `void SetRootSequencePlaybackRange();`
- L453 _protected prototype_ `float GetBasePlayRate() const;` — Returns the rate required for the player to have a duration of TimePerCycle
- L456 _protected prototype_ `float GetBaseDuration() const;` — Returns the duration in hours of the player if its rate is 1
- L459 _protected prototype_ `UDaySequencePlayer* GetSequencePlayerInternal() const;` — Internal getter that validates the player.
- L469 _protected prototype_ `bool MarkDaySequences(FSubSectionPreserveMap* SectionsToPreserve);` — Determines if subsection initialization is necessary or not by verifying all sections in SubSections exist in this map. If they do, we keep all existing subsections. If not, we remove existing subsections and call InitializeDaySequences(). @param SectionsToPreserve A map of RootSequence subsections that allows sequence providers to mark if their cached subsections should be kept or removed. @return Returns true if we need to remove all sections and reinitialize, false if we can keep all existing sections and bypass initialization.
- L477 _protected prototype_ `virtual void InitializeDaySequences();` — Called by InitializeRootSequence. By default this will initialize sequences in DaySequenceCollection. Non-collection sequences should be initialized in an override of this function in order to be properly inspected by the debug overlay.
- L479 _protected prototype_ `UMovieSceneSubSection* InitializeDaySequence(const FDaySequenceCollectionEntry& SequenceAsset);`
- L482 _protected prototype_ `FMovieSceneSequencePlaybackSettings GetPlaybackSettings(const UDaySequence* Sequence) const;` — Compute PlaybackSettings from day cycle properties
- L484 _protected prototype_ `void OnSequencePlayerUpdate(const UDaySequencePlayer& Player, FFrameTime CurrentTime, FFrameTime PreviousTime);`
- L485 _protected prototype_ `virtual void SequencePlayerUpdated(float CurrentTime, float PreviousTime);`
- L487 _protected prototype_ `float GetInterpCurveTimeOfDay(float Time) const;`
- L495 _public member_ `TObjectPtr<UCurveFloat> DayInterpCurve;` — `UPROPERTY(EditAnywhere, replicated, BlueprintReadWrite, Category=RuntimeDayCycle, meta=(EditCondition=bUseInterpCurve, DisplayAfter=bRunDayCycle))` — User-provided interpolation curve that maps day cycle times to desired cycle times (usually from 0-24 hours). When disabled, the cycle will interpolate linearly.
- L499 _public member_ `TObjectPtr<UDaySequenceCollectionAsset> DaySequenceCollection;` — `UE_DEPRECATED(5.6, "DaySequenceCollection is deprecated in favor of the array property. Please use DaySequenceCollections instead.")` — `UPROPERTY()`
- L502 _public member_ `TArray<TObjectPtr<UDaySequenceCollectionAsset>> DaySequenceCollections;` — `UPROPERTY(EditAnywhere, Category="Sequence")`
- L506 _public member_ `int32 Bias;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sequence", DisplayName="Collection Bias", meta=(DisplayAfter="DaySequenceCollection"))` — User-defined bias to apply to sequences in DaySequenceCollection.
- L510 _public member_ `TObjectPtr<UMovieSceneBindingOverrides> BindingOverrides;` — `UPROPERTY(Instanced, BlueprintReadOnly, Category="Sequence")` — Mapping of actors to override the sequence bindings with
- L514 _public member_ `uint8 bReplicatePlayback : 1;` — `UPROPERTY(EditAnywhere, DisplayName="Replicate Playback", BlueprintReadWrite, BlueprintSetter=SetReplicatePlayback, Category=Replication)` — If true, playback of this sequence on the server will be synchronized across other clients
- L517 _public member_ `bool bForceDisableDayInterpCurve = false;` — Used to early out from WarpEvaluationRange. Set to true when editing the root sequence of this actor.
- L527 _protected member_ `bool bOverrideInitialTimeOfDay;` — `UPROPERTY()` — Editor only override for testing in PIE. If true, the actor uses the current preview time as the initial time of day. Otherwise, the initial time of day is InitialTimeOfDay.
- L535 _protected member_ `bool bOverrideRunDayCycle;` — `UPROPERTY()` — Editor only override for testing in PIE. If true, prevents initial playback on BeginPlay. Otherwise, initial playback is determined by bRunDayCycle.
- L538 _public prototype_ `bool GetOverrideInitialTimeOfDay() const;`
- L539 _public prototype_ `void SetOverrideInitialTimeOfDay(bool bNewOverrideInitialTimeOfDay);`
- L542 _public prototype_ `void SetOverrideInitialTimeOfDay(bool bNewOverrideInitialTimeOfDay, float OverrideInitialTimeOfDay);` — Variant of SetOverrideInitialTimeOfDay that will update TimeOfDayPreview if necessary.
- L544 _public prototype_ `bool GetOverrideRunDayCycle() const;`
- L545 _public prototype_ `void SetOverrideRunDayCycle(bool bNewOverrideRunDayCycle);`
- L547 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverrideInitialTimeOfDayChanged, bool, float);`
- L548 _public member_ `FOnOverrideInitialTimeOfDayChanged OnOverrideInitialTimeOfDayChanged;`
- L550 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOverrideRunDayCycleChanged, bool);`
- L551 _public member_ `FOnOverrideRunDayCycleChanged OnOverrideRunDayCycleChanged;`
- L556 _protected member_ `TObjectPtr<UDaySequencePlayer> SequencePlayer;` — `UPROPERTY(Instanced, transient, replicated)`
- L559 _protected member_ `TObjectPtr<UDaySequence> RootSequence;` — `UPROPERTY(Transient)`
- L562 _protected member_ `float SequenceUpdateInterval;` — `UPROPERTY(EditAnywhere, Category=RuntimeDayCycle)`
- L570 _protected member_ `FDaySequenceTime TimeOfDayPreview;` — `UPROPERTY(EditAnywhere, Category = Preview, NonTransactional)` — Sets the time of day to preview in the editor. Does not affect the start time at runtime. Can be used as the initial time of day in PIE if bOverrideInitialTimeOfDay is true.
- L575 _protected member_ `bool bRunDayCycle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter = SetRunDayCycle, Getter = GetRunDayCycle, Category = RuntimeDayCycle)` — Whether or not to run a day cycle. If this is unchecked the day cycle will remain fixed at the time specified by the Initial Time setting
- L578 _protected member_ `bool bUseInterpCurve;` — `UPROPERTY(EditAnywhere, replicated, BlueprintReadWrite, Category = RuntimeDayCycle, meta=(InlineEditConditionToggle))`
- L582 _protected member_ `FDaySequenceTime DayLength;` — `UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)` — How long a single day cycle is
- L586 _protected member_ `FDaySequenceTime TimePerCycle;` — `UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)` — How long does it take for a day cycle to complete in world time. If this is the same value as day duration that means real world time is used
- L590 _protected member_ `FDaySequenceTime InitialTimeOfDay;` — `UPROPERTY(EditAnywhere, Category = RuntimeDayCycle)` — The initial time that the day cycle will start at
- L592 _protected member_ `TSharedPtr<UE::DaySequence::FStaticTimeManager> StaticTimeManager;`
- L595 _protected member_ `TObjectPtr<UDaySequenceCameraModifierManager> CameraModifierManager;` — `UPROPERTY(Transient)`
- L604 _protected member_ `FOnTimeOfDayPreviewChanged OnTimeOfDayPreviewChanged;` — `UPROPERTY(BlueprintAssignable, Transient, meta=(AllowPrivateAccess="true"))` — Blueprint exposed delegate invoked when the TimeOfDayPreview property is changed. @param new preview time in hours.
- L617 _protected member_ `FOnRootSequenceChanged OnPreRootSequenceChanged;`
- L618 _protected member_ `FOnRootSequenceChanged OnPostRootSequenceChanged;`
- L619 _protected member_ `FOnPostInitializeDaySequences OnPostInitializeDaySequences;`
- L620 _protected member_ `UE::DaySequence::FOnInvalidateMuteStates OnInvalidateMuteStates;`
- L622 _protected member_ `FOnDaySequenceUpdate OnDaySequenceUpdate;`
- L623 _protected member_ `FTimerHandle DaySequenceUpdateTimerHandle;`
- L627 _protected prototype_ `void StartDaySequenceUpdateTimer();` — `UFUNCTION()` — Starts a timer that will broadcast OnDaySequenceUpdate when the sequence player is paused.
- L631 _protected prototype_ `void StopDaySequenceUpdateTimer();` — `UFUNCTION()` — Stops the timer that was started by DaySequenceUpdateTimerHandle.
- L634 _protected prototype_ `void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L639 _protected member_ `UE::DaySequence::FDebugEntryMap DebugEntries;` — The keys in this map are debug categories. When a debug entry is registered, it is is added to the array corresponding to the category it specified when registering. When OnShowDebugInfo is called on this actor, the debug data is consolidated and passed to the FDebugCategoryDrawFunction associated with the category
- L642 _protected member_ `TArray<TSharedPtr<UE::DaySequence::FDaySequenceDebugEntry>> SubSectionDebugEntries;` — Debug entries this actor is responsible for. Populated by InitializeDaySequence and cleaned by InitializeRootSequence.
- L645 _protected member_ `FOnDebugLevelChanged OnDebugLevelChanged;` — Notifies any listeners when the CVar "DaySequence.DebugLevel" changes and provides the new value.
- L646 _protected member_ `int32 CachedDebugLevel = 0;`
- L649 _protected member_ `TArray<UMovieSceneSubSection*> SubSections;`
- L651 _protected member_ `TMap<FMovieSceneSequenceID, TMap<FGuid, TFunction<bool(TArray<UObject*, TInlineAllocator<1>>&)>>> BindingResolveFunctions;`
- L654 _protected member_ `TMap<TSubclassOf<UDaySequenceConditionTag>, TObjectPtr<UDaySequenceConditionTag>> TrackConditionMap;` — `UPROPERTY(Transient)`

#### enum `ADaySequenceActor::EUpdateRootSequenceMode`  
`enum class EUpdateRootSequenceMode`  
_L318-325_
- L322 _public enumerator_ `Update = 0` — Compare the current sequence against the new sequence and only add/remove new/old sequences respectively.
- L324 _public enumerator_ `Reinitialize = 1 << 0` — Reset and rebuild the root sequence from scratch.

#### struct `ADaySequenceActor::FUpdateRootSequenceState`  
`struct FUpdateRootSequenceState`  
_L608-612_
- L610 _public member_ `bool bUpdate = false;`
- L611 _public member_ `EUpdateRootSequenceMode Mode = EUpdateRootSequenceMode::Update;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DAYSEQUENCE_API`
- L19 _macro_ `#define ROOT_SEQUENCE_RECONSTRUCTION_ENABLED WITH_EDITOR`
- L23 _macro_ `#define DAY_SEQUENCE_ENABLE_DRAW_DEBUG !UE_BUILD_SHIPPING`
- L30 _namespace_ `namespace EEndPlayReason`
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace DaySequence` (scope `UE`)
- L69 _typedef_ `using FDebugEntryArray = TArray<TWeakPtr<FDaySequenceDebugEntry>>;` (scope `UE::DaySequence`) — Alias type which stores an array of weak pointers to debug entries
- L72 _typedef_ `using FDebugCategoryDrawFunction = TFunction<void(UCanvas*, TArray<TSharedPtr<TMap<FString, FString>>>&, const FString&)>;` (scope `UE::DaySequence`) — Alias type which defines the signature of the draw function a registered category must be associated with
- L75 _typedef_ `using FDebugEntryMap = TMap<FName, TPair<FDebugEntryArray, FDebugCategoryDrawFunction>>;` (scope `UE::DaySequence`) — Alias type which maps a category to its array of debug entries and to a callback which handles drawing the data.
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidateMuteStates);`
- L78 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidateMuteStates);` (scope `UE::DaySequence`)
- L81 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeOfDayPreviewChanged, float, Time);`
- L81 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeOfDayPreviewChanged, float, Time);`
- L123 _delegate_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnTimeOfDayPreviewChangedEvent, float) FOnTimeOfDayPreviewChangedEvent OnTimeOfDayPreviewChangedEvent;` — Native event invoked when the TimeOfDayPreview property is changed. @param new preview time in hours.
- L131 _delegate_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnSubSectionRemovedEvent, const UMovieSceneSubSection*) static FOnSubSectionRemovedEvent OnSubSectionRemovedEvent;` — Native event invoked when a subsection is removed from the Root Sequence. Primarily called by modifier components but generally callable by anything that adds a subsection to the root sequence. @param The subsection being removed.
- L336 _delegate_ `DECLARE_EVENT(ADaySequenceActor, FOnRootSequenceChanged) FOnRootSequenceChanged& GetOnPostRootSequenceChanged() { return OnPostRootSequenceChanged; } FOnRootSequenceChanged& GetOnPreRootSequenceChanged() { return OnPreRootSequenceChanged; } using FSubSectionPreserveMap = TMap<UMovieSceneSubSection*, bool>;`
- L348 _delegate_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnPostInitializeDaySequences, FSubSectionPreserveMap*) FOnPostInitializeDaySequences& GetOnPostInitializeDaySequences() { return OnPostInitializeDaySequences; } DECLARE_EVENT(ADaySequenceActor, FOnDaySequenceUpdate) FOnDaySequenceUpdate& GetOnDaySequenceUpdate() { return OnDaySequenceUpdate; } void InvalidateMuteStates() const;`
- L356 _delegate_ `DECLARE_EVENT(ADaySequenceActor, FOnDaySequenceUpdate) FOnDaySequenceUpdate& GetOnDaySequenceUpdate() { return OnDaySequenceUpdate; } void InvalidateMuteStates() const;` — This delegate is broadcast at a rate matching this actor's tick interval. It is either broadcast after each sequence player update or by a timer that is configured to run only when the sequence player is paused. Used to synchronize polling logic that is not owned by this actor when it should occur at an interval specified by this actor.
- L365 _delegate_ `DECLARE_EVENT_OneParam(ADaySequenceActor, FOnDebugLevelChanged, int32) FOnDebugLevelChanged& GetOnDebugLevelChanged() { return OnDebugLevelChanged; } int32 GetDebugLevel() const { return CachedDebugLevel; } bool IsDebugCategoryRegistered(const FName& Category) const;`
- L547 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOverrideInitialTimeOfDayChanged, bool, float);`
- L550 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOverrideRunDayCycleChanged, bool);`
- L657 _prototype_ `ENUM_CLASS_FLAGS(ADaySequenceActor::EUpdateRootSequenceMode);`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceActorSpawner.h` (Public)


#### class `FDaySequenceActorSpawner`  
`class FDaySequenceActorSpawner : public IMovieSceneObjectSpawner`  
_L9-18_
- inherits: `IMovieSceneObjectSpawner`
- L12 _public prototype_ `static TSharedRef<IMovieSceneObjectSpawner> CreateObjectSpawner();`
- L15 _public prototype_ `virtual UClass* GetSupportedTemplateType() const override;` — IMovieSceneObjectSpawner interface
- L16 _public prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L17 _public prototype_ `virtual void DestroySpawnedObject(UObject& Object) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceBindingReference.h` (Public)


#### enum `EDaySequenceBindingReferenceSpecialization`  
`enum class EDaySequenceBindingReferenceSpecialization`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `None` — An unspecialized binding. Resolution is determined by ExternalObjectPath and ObjectPath given some context.
- L12 _public enumerator_ `Root` — An empty binding with this specialization will always resolve to the Root Day Sequence Actor.
- L13 _public enumerator_ `CameraModifier` — An empty binding with this specialization will attempt to resolve to a camera modifier associated with a modifier's blend target.

#### struct `FDaySequenceBindingReference`  
`struct FDaySequenceBindingReference`  
_L24-90_
- reflection: `USTRUCT()`
- desc: An external reference to a DaySequence object, resolvable through an arbitrary context. Bindings consist of an optional package name, and the path to the object within that package. Where package name is empty, the reference is a relative path from a specific outer (the context). Currently, the package name should only ever be empty for component references, which must remain relative bindings to work correctly with spawnables and reinstanced actors.
- L31 _public function_ `FDaySequenceBindingReference()` — Default construction only used for serialization
- L36 _public prototype_ `FDaySequenceBindingReference(UObject* InObject, UObject* InContext);` — Construct a new binding reference from an object, and a given context (expected to be either a UWorld, or an AActor)
- L41 _public prototype_ `static FDaySequenceBindingReference DefaultRootBinding();` — Construct a new binding that always resolves to the day sequence actor
- L46 _public prototype_ `static FDaySequenceBindingReference SpecializedBinding(EDaySequenceBindingReferenceSpecialization Specialization);` — Construct a new binding that always resolves based on specialization type. This is highly context specific.
- L54 _public prototype_ `UObject* Resolve(UObject* InContext) const;` — Resolve this reference within the specified context @param InContext		The context to resolve the binding within. Either a UWorld, ULevel (when playing in an instanced level) or an AActor where this binding relates to an actor component @return The object (usually an Actor or an ActorComponent).
- L59 _public prototype_ `bool operator==(const FDaySequenceBindingReference& Other) const;` — Check whether this binding reference is equal to the specified object
- L61 _public function_ `EDaySequenceBindingReferenceSpecialization GetSpecialization() const`
- L68 _public prototype_ `void PerformLegacyFixup();` — Perform legacy data fixup as part of PostLoad
- L75 _private member_ `TSoftObjectPtr<UObject> ExternalObjectPath;` — `UPROPERTY()` — Path to a specific actor/component inside an external package
- L79 _private member_ `FString ObjectPath;` — `UPROPERTY()` — Object path relative to a passed in context object, this is used if ExternalObjectPath is invalid
- L83 _private member_ `EDaySequenceBindingReferenceSpecialization Specialization = EDaySequenceBindingReferenceSpecialization::None;` — `UPROPERTY()` — Used when object path data is empty. Generally used for context-specific dynamic bindings.
- L88 _private member_ `TSoftClassPtr<UObject> ObjectClass_DEPRECATED;` — `UPROPERTY()` — The class of the object path.

#### struct `FDaySequenceBindingReferenceArray`  
`struct FDaySequenceBindingReferenceArray`  
_L96-102_
- reflection: `USTRUCT()`
- desc: An array of binding references
- L101 _public member_ `TArray<FDaySequenceBindingReference> References;` — `UPROPERTY()`

#### struct `FDaySequenceBindingReferences`  
`struct FDaySequenceBindingReferences`  
_L109-224_
- reflection: `USTRUCT()`
- desc: Structure that stores a one to many mapping from object binding ID, to object references that pertain to that ID.
- L117 _public prototype_ `bool HasBinding(const FGuid& ObjectId) const;` — Check whether this map has a binding for the specified object id @return true if this map contains a binding for the id, false otherwise
- L124 _public prototype_ `void RemoveBinding(const FGuid& ObjectId);` — Remove a binding for the specified ID @param ObjectId	The ID to remove
- L133 _public prototype_ `void RemoveObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject *InContext);` — Remove specific object references @param ObjectId	The ID to remove @param InObjects The objects to remove @param InContext A context in which InObject resides (either a UWorld, or an AActor)
- L141 _public prototype_ `void RemoveInvalidObjects(const FGuid& ObjectId, UObject *InContext);` — Remove specific object references that do not resolve @param ObjectId	The ID to remove @param InContext A context in which InObject resides (either a UWorld, or an AActor)
- L150 _public prototype_ `void AddBinding(const FGuid& ObjectId, UObject* InObject, UObject* InContext);` — Add a binding for the specified ID @param ObjectId	The ID to associate the object with @param InObject	The object to associate @param InContext	A context in which InObject resides (either a UWorld, or an AActor)
- L158 _public prototype_ `void AddDefaultBinding(const FGuid& ObjectId);` — Adds a default binding that always resolves to the day sequence actor. Prefer using AddSpecializedBinding with the Root specialization. @param ObjectId	The ID to associate the object with
- L166 _public prototype_ `void AddSpecializedBinding(const FGuid& ObjectId, EDaySequenceBindingReferenceSpecialization Specialization);` — Adds a specialized binding. @param ObjectId	The ID to associate the object with @param Specialization The type of specialized binding to create
- L175 _public prototype_ `FGuid FindSpecializedBinding(EDaySequenceBindingReferenceSpecialization Specialization) const;`
- L184 _public prototype_ `void ResolveBinding(const FGuid& ObjectId, UObject* InContext, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const;` — Resolve a binding for the specified ID using a given context @param ObjectId					The ID to associate the object with @param InContext					A context in which InObject resides @param OutObjects				Array to populate with resolved object bindings
- L189 _public function_ `const TSet<FGuid>& GetBoundAnimInstances() const` — Const accessor for the currently bound anim instance IDs
- L199 _public prototype_ `void RemoveInvalidBindings(const TSet<FGuid>& ValidBindingIDs);` — Filter out any bindings that do not match the specified set of GUIDs @param ValidBindingIDs A set of GUIDs that are considered valid. Anything references not matching these will be removed.
- L206 _public prototype_ `void PerformLegacyFixup();` — Perform legacy data fixup as part of PostLoad
- L214 _private member_ `TMap<FGuid, FDaySequenceBindingReferenceArray> BindingIdToReferences;` — `UPROPERTY()` — The map from object binding ID to an array of references that pertain to that ID
- L218 _private member_ `TSet<FGuid> AnimSequenceInstances;` — `UPROPERTY()` — A set of object binding IDs that relate to anim sequence instances (must be a child of USkeletalMeshComponent)
- L221 _private member_ `TMap<EDaySequenceBindingReferenceSpecialization, FGuid> SpecializedReferenceToGuid;` — `UPROPERTY()`
- L223 _private member_ `TMap<FGuid, EDaySequenceBindingReferenceSpecialization> GuidToSpecializedReference;` — `UPROPERTY()`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceCameraModifier.h` (Public)


#### class `UDaySequenceCameraModifierManager`  
`class UDaySequenceCameraModifierManager : public UObject`  
_L21-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Provides: 1) an interface for getting UDaySequenceCameraModifiers associated with player controllers, 2) an editor only camera modifier for resolving camera modifier bindings in editor worlds, 3) an editor only post process component for visualizing the editor only camera modifier.
- L27 _public prototype_ `UCameraModifier* GetCameraModifier(APlayerController* InPC);`
- L30 _public prototype_ `UCameraModifier* GetEditorCameraModifier();`
- L31 _public prototype_ `void UpdateEditorPreview() const;`
- L32 _public function_ `void ResetEditorPreview()`
- L40 _private member_ `TObjectPtr<UDaySequenceCameraModifier> EditorCameraModifier;` — `UPROPERTY(Transient, DuplicateTransient)` — A camera modifier not associated with any player controller, used to resolve the camera modifier binding in editor.
- L44 _private member_ `TObjectPtr<UPostProcessComponent> EditorCameraModiferPreview;` — `UPROPERTY(Transient, DuplicateTransient)` — A post process component used to preview the animation of EditorCameraModifier.
- L48 _private member_ `TMap<TWeakObjectPtr<APlayerController>, TWeakObjectPtr<UCameraModifier>> CameraModifiers;` — Note: We have no ownership over either the controller or the modifier. The modifiers are owned by the player camera manager.

#### class `UDaySequenceCameraModifier`  
`class UDaySequenceCameraModifier : public UCameraModifier`  
_L53-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraModifier`
- L59 _public function_ `const FPostProcessSettings& GetSettings() const`
- L70 _private member_ `FPostProcessSettings Settings;` — `UPROPERTY(EditAnywhere, interp, Category = PostProcess, meta = (ShowOnlyInnerProperties))` — Post process settings to use for this modifier. Sequencer should handle this (blending multiple sequences, restoring to default, etc), we just handle forwarding it to the provided settings in ModifyPostProcess()
- L72 _private function_ `virtual void ModifyPostProcess(float DeltaTime, float& PostProcessBlendWeight, FPostProcessSettings& PostProcessSettings) override`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceCollectionAsset.h` (Public)


#### struct `FDaySequenceCollectionEntry`  
`struct FDaySequenceCollectionEntry`  
_L15-43_
- reflection: `USTRUCT()`
- L19 _public function_ `FDaySequenceCollectionEntry(UDaySequence* InDaySequence = nullptr) : Sequence(InDaySequence) , BiasOffset(0) , Conditions(FDaySequenceConditionSet())`
- L25 _public function_ `FDaySequenceCollectionEntry(TObjectPtr<UDaySequence> InDaySequence) : FDaySequenceCollectionEntry(InDaySequence.Get())`
- L31 _public member_ `TObjectPtr<UDaySequence> Sequence;` — `UPROPERTY(EditAnywhere, Category="Day Sequence", meta=(AllowedClasses="/Script/DaySequence.DaySequence"))` — The day sequence asset for this collection entry.
- L35 _public member_ `int BiasOffset = 0;` — `UPROPERTY(EditAnywhere, Category="Day Sequence")` — The offset hierarchical bias assigned to this collection entry.
- L39 _public member_ `FDaySequenceConditionSet Conditions;` — `UPROPERTY(EditAnywhere, Category="Day Sequence")` — The set of conditions which must evaluate to their expected values for this entry to be active.
- L42 _public member_ `bool bEnableHierarchicalBlending = true;` — `UPROPERTY(EditAnywhere, Category="Day Sequence", AdvancedDisplay)`

#### class `UDaySequenceCollectionAsset`  
`class UDaySequenceCollectionAsset : public UDataAsset`  
_L46-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L52 _public member_ `TArray<FDaySequenceCollectionEntry> DaySequences;` — `UPROPERTY(EditAnywhere, Category="Day Sequence")`
- L55 _public member_ `TArray<TInstancedStruct<FProceduralDaySequence>> ProceduralDaySequences;` — `UPROPERTY(EditAnywhere, Category="Day Sequence", meta = (ExcludeBaseStruct))`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceConditionSet.h` (Public)


#### struct `FDaySequenceConditionSet`  
`struct FDaySequenceConditionSet`  
_L13-27_
- reflection: `USTRUCT()`
- L23 _public typedef_ `typedef TMap<TSubclassOf<UDaySequenceConditionTag>, bool> FConditionValueMap;` — TMap where the key specifies a condition tag and the value specifies the expected value for that condition when evaluating this condition set. Note: This type needs to be specified explicitly for Conditions because we can't use a typedef for a UPROPERTY.
- L26 _public member_ `TMap<TSubclassOf<UDaySequenceConditionTag>, bool> Conditions;` — `UPROPERTY(EditAnywhere, Category = "Conditions")`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceConditionTag.h` (Public)


#### enum `EDaySequenceConditionTagInitializationPhase`  
`enum class EDaySequenceConditionTagInitializationPhase : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- desc: Enum specifying when a day sequence condition tag will be initialized.
- L17 _public enumerator_ `Immediate`
- L18 _public enumerator_ `GameStateReady`

#### class `UDaySequenceConditionTag`  
`class UDaySequenceConditionTag : public UObject`  
_L22-83_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, Const)`
- inherits: `UObject`
- L33 _public prototype_ `void Initialize();` — This needs to be called before this condition is expected to function properly. We do initialization here because there is some uncertainty about which blueprint functions/events can be safely called while this object is still being constructed.
- L37 _public prototype_ `bool Evaluate() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "General")` — Evaluates a preconfigured boolean condition.
- L39 _public prototype_ `FString GetConditionName() const;`
- L40 _public prototype_ `EDaySequenceConditionTagInitializationPhase GetInitializationPhase() const;`
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConditionValueChanged);`
- L43 _public function_ `FOnConditionValueChanged& GetOnConditionValueChanged()`
- L45 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L55 _protected prototype_ `void SetupOnConditionValueChanged() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "General")` — Derived classes should override this function if the condition being evaluated is associated with external delegates which are broadcast when the condition may change. The intent is to bind BroadcastOnConditionValueChanged to all relevant external delegates so that we can propagate those broadcasts to notify users of this condition that the condition needs reevaluating.
- L62 _protected prototype_ `void BroadcastOnConditionValueChanged() const;` — `UFUNCTION(BlueprintCallable, Category = "General")` — Derived classes should call this function to notify listeners that the underlying condition may have changed. This will only trigger a broadcast if Evaluate() returns a different value than the last invocation of this function.
- L70 _protected member_ `FString ConditionName;` — `UPROPERTY(EditDefaultsOnly, Category = "General")` — Derived classes should give this a meaningful default value which is displayed when prompting users with a list of possible conditions to apply to a given sequence.
- L76 _protected member_ `EDaySequenceConditionTagInitializationPhase InitializationPhase = EDaySequenceConditionTagInitializationPhase::Immediate;` — `UPROPERTY(EditDefaultsOnly, Category = "General")` — Determines when SetupOnConditionValueChanged is called.
- L79 _private member_ `FOnConditionValueChanged OnConditionValueChanged;`
- L82 _private member_ `mutable TOptional<bool> bCachedEvalResult;` — This is an optional because it is unset until the first time BroadcastOnConditionValueChanged is called.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DAYSEQUENCE_API`
- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConditionValueChanged);`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceDirector.h` (Public)


#### class `UDaySequenceDirector`  
`class UDaySequenceDirector : public UObject`  
_L19-102_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L26 _public prototype_ `void OnCreated();` — `UFUNCTION(BlueprintImplementableEvent, Category="Sequencer")` — Called when this director is created
- L33 _public prototype_ `FQualifiedFrameTime GetRootSequenceTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — Get the current time for the outermost (root) sequence @return The current playback position of the root sequence
- L40 _public prototype_ `FQualifiedFrameTime GetCurrentTime() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Director")` — Get the current time for this director's sub-sequence (or the root sequence, if this is a root sequence director) @return The current playback position of this director's sequence
- L49 _public prototype_ `TArray<UObject*> GetBoundObjects(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the bindings inside this sub-sequence that relate to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L59 _public prototype_ `UObject* GetBoundObject(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the first valid binding inside this sub-sequence that relates to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L69 _public prototype_ `TArray<AActor*> GetBoundActors(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the actor bindings inside this sub-sequence that relate to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L79 _public prototype_ `AActor* GetBoundActor(FMovieSceneObjectBindingID ObjectBinding);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Resolve the first valid Actor binding inside this sub-sequence that relates to the specified ID @note: ObjectBinding should be constructed from the same sequence as this Sequence Director's owning Sequence (see the GetSequenceBinding node) @param ObjectBinding The ID for the object binding inside this sub-sequence or one of its children to resolve
- L85 _public prototype_ `UMovieSceneSequence* GetSequence();` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Director")` — Get the current sequence that this director is playing back within
- L89 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L93 _public member_ `TObjectPtr<UDaySequencePlayer> Player;` — `UPROPERTY(BlueprintReadOnly, Category="Cinematics")` — Pointer to the player that's playing back this director's sequence. Only valid in game or in PIE/Simulate.
- L97 _public member_ `int32 SubSequenceID;` — `UPROPERTY()` — The Sequence ID for the sequence this director is playing back within - has to be stored as an int32 so that it is reinstanced correctly
- L101 _public member_ `int32 MovieScenePlayerIndex;` — `UPROPERTY()` — Native player interface index - stored by index so that it can be reinstanced correctly

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceModifierComponent.h` (Public)


#### enum `EDayNightCycleMode`  
`enum class EDayNightCycleMode : uint8`  
_L36-53_
- reflection: `UENUM(BlueprintType)`
- desc: Enum specifying how to control a day / night cycle from a modifier
- L39 _public enumerator_ `Default` — (default) Make no changes to the day/night cycle time
- L41 _public enumerator_ `FixedTime` — Force the day/night cycle to be fixed at the specified constant time
- L43 _public enumerator_ `StartAtSpecifiedTime` — Set an initial time for the day/night cycle when the modifier is enabled
- L45 _public enumerator_ `RandomFixedTime` — Use a random, fixed time for the day/night cycle
- L47 _public enumerator_ `RandomStartTime` — Start the day/night cycle at a random time, and allow it to continue from there
- L52 _public enumerator_ `LocalFixedTime` — Apply a time warp local to the modifier's sequence evaluation time. Local time warp will not affect global time.

#### enum `EDaySequenceModifierMode`  
`enum class EDaySequenceModifierMode : uint8`  
_L57-67_
- reflection: `UENUM(BlueprintType)`
- desc: Enum that defines modifier behavior for auto enabling and computing the internal blend weight.
- L60 _public enumerator_ `Global` — Blend weight is always 1.0.
- L63 _public enumerator_ `Volume` — Blend weight smoothly moves between 0.0 and 1.0 according to how far the blend target is from the volume boundary.
- L66 _public enumerator_ `Time` — Blend weight smoothly moves between 0.0 and 1.0 at a fixed rate according to when the blend target last crossed the volume boundary.

#### enum `EDaySequenceModifierUserBlendPolicy`  
`enum class EDaySequenceModifierUserBlendPolicy : uint8`  
_L71-84_
- reflection: `UENUM(BlueprintType)`
- desc: Enum specifying how the modifier resolves the user specified blend weight against the internal blend weight.
- L74 _public enumerator_ `Ignored` — User specified weights are ignored (i.e. the effective weight is InternallyComputedWeight
- L77 _public enumerator_ `Minimum` — (default) The effective weight is FMath::Min(InternallyComputedWeight, UserSpecifiedWeight
- L80 _public enumerator_ `Maximum` — The effective weight is FMath::Max(InternallyComputedWeight, UserSpecifiedWeight
- L83 _public enumerator_ `Override` — The effective weight is UserSpecifiedWeight

#### struct `FDaySequenceModifierComponentTickableBase`  
`struct FDaySequenceModifierComponentTickableBase : public FTickableGameObject`  
_L91-106_
- inherits: `FTickableGameObject`
- desc: Editor-only tickable class that allows us to enable trigger volume previews based on persepective camera position in the level viewport.
- L93 _public function_ `FDaySequenceModifierComponentTickableBase() : FTickableGameObject(ETickableTickType::Never)`
- L97 _public function_ `virtual void UpdateEditorPreview(float DeltaTime)`
- L100 _public function_ `void Tick(float DeltaTime) override`

#### struct `FDaySequenceModifierComponentTickableBase`  
`struct FDaySequenceModifierComponentTickableBase`  
_L109-109_
- desc: Empty in non-editor builds
- L93 _public function_ `FDaySequenceModifierComponentTickableBase() : FTickableGameObject(ETickableTickType::Never)`
- L97 _public function_ `virtual void UpdateEditorPreview(float DeltaTime)`
- L100 _public function_ `void Tick(float DeltaTime) override`

#### class `UDaySequenceModifierEasingFunction`  
`class UDaySequenceModifierEasingFunction : public UObject , public IMovieSceneEasingFunction`  
_L113-132_
- reflection: `UCLASS()`
- inherits: `UObject,IMovieSceneEasingFunction`
- L126 _public prototype_ `void Initialize(EEasingFunctionType EasingType);`
- L128 _public prototype_ `virtual float Evaluate(float Interp) const override;`
- L131 _private member_ `TFunction<float(float)> EvaluateImpl;`

#### enum `UDaySequenceModifierEasingFunction::EEasingFunctionType`  
`enum class EEasingFunctionType`  
_L120-124_
- L122 _public enumerator_ `EaseIn`
- L123 _public enumerator_ `EaseOut`

#### class `UDaySequenceModifierComponent`  
`class UDaySequenceModifierComponent : public USceneComponent , public FDaySequenceModifierComponentTickableBase`  
_L138-440_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, config=Game, HideCategories=(Physics,Navigation,Collision,HLOD,Rendering,Cooking,Mobile,RayTracing,AssetUserData), meta=(BlueprintSpawnableComponent))`
- inherits: `USceneComponent,FDaySequenceModifierComponentTickableBase`
- L145 _public prototype_ `UDaySequenceModifierComponent(const FObjectInitializer& Init);`
- L148 _public prototype_ `static void SetVolumePreviewLocation(const FVector& Location);`
- L149 _public prototype_ `static void SetIsSimulating(bool bInIsSimulating);`
- L157 _public prototype_ `void BindToDaySequenceActor(ADaySequenceActor* DaySequenceActor);` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Bind this component to the specified day sequence actor. Will not add our overrides to the sub-sequence until EnableModifier is called.
- L164 _public prototype_ `void UnbindFromDaySequenceActor();` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Unbind this component from its day sequence actor if valid. Will removes the sub-sequence from the root sequence if it's set up.
- L170 _public prototype_ `void EnableComponent();` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Enable this component.
- L177 _public prototype_ `void DisableComponent();` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Disable this component. Will remove the sub-sequence from the root sequence if it's set up.
- L184 _public prototype_ `void ReinitializeSubSequences();` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Rebuilds this component's subsections in the root sequence from the current UserDaySequence/DaySequenceCollections. Call after swapping collection assets at runtime.
- L187 _public prototype_ `void SetUserDaySequence(UDaySequence* InDaySequence);` — Sets the user day sequence. This must be a user created asset.
- L188 _public prototype_ `UDaySequence* GetUserDaySequence() const;`
- L191 _public prototype_ `void SetTransientSequence(UDaySequence* InDaySequence);` — Sets a user specified transient sequence.
- L192 _public prototype_ `UDaySequence* GetTransientSequence() const;`
- L195 _public prototype_ `void SetDayNightCycle(EDayNightCycleMode NewMode);` — Sets the Day Night Cycle mode. This will reenable the component.
- L196 _public prototype_ `EDayNightCycleMode GetDayNightCycle() const;`
- L198 _public prototype_ `void SetBias(int32 NewBias);`
- L199 _public prototype_ `int32 GetBias() const;`
- L201 _public prototype_ `void SetDayNightCycleTime(float Time);`
- L202 _public prototype_ `float GetDayNightCycleTime() const;`
- L204 _public prototype_ `void SetMode(EDaySequenceModifierMode NewMode);`
- L205 _public prototype_ `EDaySequenceModifierMode GetMode() const;`
- L207 _public prototype_ `void SetBlendPolicy(EDaySequenceModifierUserBlendPolicy NewPolicy);`
- L208 _public prototype_ `EDaySequenceModifierUserBlendPolicy GetBlendPolicy() const;`
- L211 _public prototype_ `void SetBlendTime(float TimeInSeconds);` — Sets the time to blend towards the target weight.
- L212 _public prototype_ `float GetBlendTime() const;`
- L215 _public prototype_ `void SetUserBlendWeight(float Weight);` — Sets a custom blend weight for volume based blends. Final weight depends on BlendPolicy.
- L216 _public prototype_ `float GetUserBlendWeight() const;`
- L220 _public prototype_ `void SetBlendTarget(APlayerController* InActor);` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Sets the blend target to use when in Volume mode.
- L224 _public prototype_ `float GetBlendWeight() const;` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")` — Get the current blend weight.
- L226 _public prototype_ `void EmptyVolumeShapeComponents();`
- L227 _public prototype_ `void AddVolumeShapeComponent(const FComponentReference& InShapeReference);`
- L228 _public prototype_ `TArray<UShapeComponent*> GetVolumeShapeComponents() const;`
- L230 _public prototype_ `FOnPostEnableModifier& GetOnPostEnableModifier();`
- L233 _public prototype_ `virtual void PostLoad() override;` — ~ Begin UObject interface
- L237 _public prototype_ `virtual void BeginPlay() override;` — ~ Begin UActorComponent interface
- L238 _public prototype_ `virtual void EndPlay(EEndPlayReason::Type Reason) override;`
- L239 _public prototype_ `virtual void OnRegister() override;`
- L240 _public prototype_ `virtual void OnUnregister() override;`
- L245 _public prototype_ `virtual void UpdateEditorPreview(float DeltaTime) override;` — ~ Begin FTickableGameObject interface
- L246 _public prototype_ `virtual TStatId GetStatId() const override;`
- L247 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L248 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L249 _public function_ `virtual bool IsTickableInEditor() const override`
- L250 _public function_ `virtual bool IsTickable() const override`
- L253 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L259 _protected prototype_ `void EnableModifier();` — Enable the modifier by enabling its subsection (creating it if necessary) in the Root Sequence.
- L262 _protected prototype_ `void DisableModifier();` — Disable the modifier by disabling its subsection.
- L264 _protected prototype_ `bool CanBeEnabled() const;`
- L266 _protected prototype_ `void SetInitialTimeOfDay();`
- L269 _protected prototype_ `void InvalidateMuteStates() const;` — Called to properly update the mute states of all managed subsections.
- L275 _protected member_ `TObjectPtr<ADaySequenceActor> TargetActor;` — `UPROPERTY(Transient, DuplicateTransient, BlueprintReadWrite, Category="Day Sequence")` — Non-serialized target actor we are currently bound to
- L278 _protected member_ `TSharedPtr<UE::DaySequence::FOverrideUpdateIntervalHandle> OverrideUpdateIntervalHandle;` — A handle used to force an override of the TargetActor's evaluation interval.
- L282 _protected member_ `TArray<FComponentReference> VolumeShapeComponents;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Day Sequence", meta=(UseComponentPicker, AllowedClasses="/Script/Engine.ShapeComponent", AllowAnyActor))` — When set, the shape components will be used for the modifier volume, otherwise the default Box component will be used.
- L286 _protected member_ `TWeakObjectPtr<APlayerController> WeakBlendTarget;` — `UPROPERTY(Transient, DuplicateTransient)` — The actor to use for distance-based volume blend calculations
- L290 _protected member_ `TObjectPtr<UDaySequence> UserDaySequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Day Sequence", meta=(EditCondition="!bUseCollection", EditConditionHides, DisplayAfter="bUseCollection"))` — The user provided Day Sequence.
- L294 _protected member_ `TObjectPtr<UDaySequence> TransientSequence;` — `UPROPERTY(Transient, BlueprintReadWrite, Setter, Getter, Category="Day Sequence", meta=(EditCondition="!bUseCollection", EditConditionHides, DisplayAfter="bUseCollection"))` — The user provided Transient Day Sequence.
- L299 _protected member_ `TObjectPtr<UDaySequenceCollectionAsset> DaySequenceCollection;` — `UE_DEPRECATED(5.6, "DaySequenceCollection is deprecated in favor of the array property. Please use DaySequenceCollections instead.")` — `UPROPERTY()` — The user provided collection. This is an alternative to UserDaySequence.
- L303 _protected member_ `TArray<TObjectPtr<UDaySequenceCollectionAsset>> DaySequenceCollections;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Day Sequence", meta=(EditCondition="bUseCollection", EditConditionHides, DisplayAfter="bUseCollection"))` — The user provided collection. This is an alternative to UserDaySequence.
- L306 _protected member_ `TObjectPtr<UDaySequenceModifierEasingFunction> EasingFunction;` — `UPROPERTY(Instanced, Transient)`
- L310 _protected member_ `int32 Bias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Day Sequence", meta=(EditCondition="!bIgnoreBias"))` — User-defined bias.
- L314 _protected member_ `float DayNightCycleTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, DisplayName="Time", Category="Time", meta=(DisplayAfter="DayNightCycle", EditCondition="DayNightCycle==EDayNightCycleMode::FixedTime || DayNightCycle==EDayNightCycleMode::StartAtSpecifiedTime || DayNightCycle==EDayNightCycleMode::LocalFixedTime", EditConditionHides))` — The time to use for the day/night cycle.
- L318 _protected member_ `float BlendAmount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Day Sequence", meta=(DisplayAfter="Mode", EditCondition="Mode==EDaySequenceModifierMode::Volume", EditConditionHides))` — Defines the region in which the effective blend weight is in the range (0.0, 1.0) (not inclusive) when Mode == EDaySequenceModifierMode::Volume.
- L322 _protected member_ `float BlendTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Day Sequence", meta=(DisplayAfter="Mode"))` — Defines the amount of time (in seconds) that it takes for the blend weight to reach the target weight
- L326 _protected member_ `float UserBlendWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Day Sequence", meta=(DisplayAfter="BlendPolicy", EditCondition="BlendPolicy!=EDaySequenceModifierUserBlendPolicy::Ignored", EditConditionHides))` — User specified blend weight. The final blend weight is determined by BlendPolicy.
- L330 _protected member_ `EDayNightCycleMode DayNightCycle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, DisplayName="Day/Night Cycle", Category="Time")` — Changes the way the modifier controls the day/night cycle time when enabled.
- L334 _protected member_ `EDaySequenceModifierMode Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Day Sequence")` — Determines how the modifier computes InternalBlendWeight.
- L338 _protected member_ `EDaySequenceModifierUserBlendPolicy BlendPolicy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, Category="Day Sequence")` — Determines how the modifier uses UserBlendWeight to compute effective blend weight.
- L342 _protected member_ `FOnPostReinitializeSubSequences OnPostReinitializeSubSequences;` — `UPROPERTY(BlueprintAssignable, Transient, meta=(AllowPrivateAccess="true"))` — Blueprint exposed delegate invoked after the component's subsequences are reinitialized.
- L346 _protected member_ `FOnPostEnableModifier OnPostEnableModifier;` — `UPROPERTY(BlueprintAssignable, Transient, meta=(AllowPrivateAccess="true"))` — Blueprint exposed delegate invoked after the modifier component is enabled.
- L350 _protected member_ `uint8 bIgnoreBias : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Day Sequence", meta=(InlineEditConditionToggle))` — When enabled, these overrides will always override all settings regardless of their bias.
- L354 _protected member_ `uint8 bIsComponentEnabled : 1;` — `UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, Category="Day Sequence")` — Flag used track whether or not this component is enabled or disabled.
- L358 _protected member_ `uint8 bIsEnabled : 1;` — `UPROPERTY(Transient, DuplicateTransient, BlueprintReadOnly, Category="Day Sequence")` — Non-serialized variable for tracking whether our overrides are enabled or not.
- L362 _protected member_ `uint8 bPreview : 1;` — `UPROPERTY(Transient, BlueprintReadWrite, EditAnywhere, Category="Day Sequence")` — When enabled, preview this day sequence modifier in the editor.
- L366 _protected member_ `uint8 bUseCollection : 1;` — `UPROPERTY(EditAnywhere, Category="Day Sequence")` — If true, hide UserDaySequence and expose DaySequenceCollection.
- L370 _protected member_ `uint8 bSmoothBlending : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category="Day Sequence")` — If true, day sequence evaluation while within the blending region will be smooth. Note: Can be very expensive.
- L374 _protected member_ `uint8 bForceSmoothBlending : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category="Day Sequence", meta=(EditCondition="bSmoothBlending", EditConditionHides))` — If true, day sequence evaluation will be smooth regardless of blend weight. Note: Is always be very expensive!
- L382 _private prototype_ `void DaySequenceUpdate();` — Bound to delegate on the DaySequenceActor that allows all modifiers to do work at appropriate times at the specific actors tick interval. Effectively a 'tick' function.
- L388 _private prototype_ `bool GetBlendPosition(FVector& InPosition) const;` — Get the blend position (handles preview and game world). @return Returns true if we have a valid blend position and InPosition was set, false if InPosition was not set.
- L394 _private prototype_ `float UpdateInternalBlendWeight();` — Updates InternalBlendWeight, the update method is determined by Mode. @return Returns InternalBlendWeight.
- L401 _private member_ `float InternalBlendWeight;` — The blend weight computed by the modifier. When this is non-zero the modifier is automatically enabled. Used to compute effective blend weight along with BlendPolicy and UserBlendWeight.
- L404 _private member_ `float TimedBlendingLastUpdated;` — Used by UpdateInternalBlendWeight to compute time delta between InternalBlendWeight updates.
- L406 _private member_ `float TimedBlendingStartWeight;` — Used by UpdateInternalBlendWeight to compute the weight delta for timed blends
- L407 _private member_ `float TimedBlendingTargetWeight;`
- L409 _private member_ `float TimedBlendingTargetWeightLastUpdated;` — Used by UpdateInternalBlendWeight to compute time delta between TimedBlendingTargetWeight updates for global/volume timed blends.
- L415 _private prototype_ `void ReinitializeSubSequence(ADaySequenceActor::FSubSectionPreserveMap* SectionsToPreserve);` — Creates and adds or marks for preserve all subsections that the modifier is responsible for. Optionally provided a map of all sections that exist in the root sequence to a bool flag used to mark that section as still relevant.
- L416 _private prototype_ `UMovieSceneSubSection* InitializeDaySequence(const FDaySequenceCollectionEntry& SequenceAsset);`
- L417 _private prototype_ `void RemoveSubSequenceTrack();`
- L419 _private prototype_ `void UpdateCachedExternalShapes() const;`
- L420 _private member_ `mutable TArray<TWeakObjectPtr<UShapeComponent>> CachedExternalShapes;`
- L421 _private member_ `mutable bool bCachedExternalShapesInvalid = true;`
- L424 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSubSection>> SubSections;` — ~ Transient state for active gameplay
- L426 _private member_ `UE::DaySequence::FOnInvalidateMuteStates OnInvalidateMuteStates;`
- L429 _private member_ `const FName ShowDebug_ModifierCategory = "Da`
- L431 _private prototype_ `void OnDebugLevelChanged(int32 InDebugLevel);`
- L432 _private prototype_ `bool ShouldShowDebugInfo() const;`
- L435 _private member_ `int32 DebugLevel;` — Determines whether or not the modifier will show debug info
- L437 _private member_ `TSharedPtr<UE::DaySequence::FDaySequenceDebugEntry> DebugEntry;`
- L438 _private member_ `TArray<TSharedPtr<UE::DaySequence::FDaySequenceDebugEntry>> SubSectionDebugEntries;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ECollisionEnabled`
- L18 _namespace_ `namespace EEndPlayReason`
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace DaySequence` (scope `UE`)
- L134 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostReinitializeSubSequences);`
- L134 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostReinitializeSubSequences);`
- L135 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostEnableModifier);`
- L135 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostEnableModifier);`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceSpawnRegister.h` (Public)


#### class `FDaySequenceSpawnRegister`  
`class FDaySequenceSpawnRegister : public FMovieSceneSpawnRegister`  
_L15-32_
- inherits: `FMovieSceneSpawnRegister`
- desc: Movie scene spawn register that knows how to handle spawning objects (actors) for a DaySequence
- L18 _public prototype_ `FDaySequenceSpawnRegister();`
- L22 _protected prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;` — ~ FMovieSceneSpawnRegister interface
- L23 _protected prototype_ `virtual void DestroySpawnedObject(UObject& Object, UMovieSceneSpawnableBindingBase* CustomSpawnableBinding) override;`
- L26 _protected prototype_ `virtual bool CanSpawnObject(UClass* InClass) const override;`
- L31 _protected member_ `TArray<TSharedRef<IMovieSceneObjectSpawner>> MovieSceneObjectSpawners;` — Extension object spawners

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceSubsystem.h` (Public)


#### class `UDaySequenceSubsystem`  
`class UDaySequenceSubsystem : public UWorldSubsystem`  
_L19-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L24 _public prototype_ `virtual bool DoesSupportWorldType(EWorldType::Type WorldType) const override;` — UWorldSubsystem interface
- L25 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L26 _public prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `ADaySequenceActor* GetDaySequenceActor(bool bFindFallbackOnNull = true) const;` — `UFUNCTION(BlueprintCallable, Category=DaySequence)`
- L32 _public prototype_ `void SetDaySequenceActor(ADaySequenceActor* InActor);` — `UFUNCTION(BlueprintCallable, Category=DaySequence)`
- L36 _public member_ `FOnDaySequenceActorSet OnDaySequenceActorSet;` — `UPROPERTY(BlueprintAssignable, Category=DaySequence)` — Blueprint exposed delegate that is broadcast when the active DaySequenceActor changes.
- L39 _public member_ `FOnDaySequenceActorSetEvent OnDaySequenceActorSetEvent;` — Natively exposed delegate that is broadcast when the active DaySequenceActor changes.
- L41 _public prototype_ `void OnCheatManagerCreated(UCheatManager* InCheatManager);`
- L45 _private prototype_ `void BroadcastOnDaySequenceActorSet(ADaySequenceActor* InActor) const;` — Utility function that broadcasts both OnDaySequenceActorSet and OnDaySequenceActorSetEvent.
- L47 _private member_ `TWeakObjectPtr<ADaySequenceActor> DaySequenceActor;`
- L49 _private member_ `TWeakObjectPtr<UDaySequenceCheatManagerExtension> CheatManagerExtension;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DAYSEQUENCE_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDaySequenceActorSet, ADaySequenceActor*, NewActor);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDaySequenceActorSet, ADaySequenceActor*, NewActor);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDaySequenceActorSetEvent, ADaySequenceActor*);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDaySequenceActorSetEvent, ADaySequenceActor*);`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceTime.h` (Public)


#### struct `FDaySequenceTime`  
`struct FDaySequenceTime`  
_L8-49_
- reflection: `USTRUCT()`
- L13 _public member_ `static constexpr float SecondsPerHour = 3600.f;`
- L14 _public member_ `static constexpr float SecondsPerMinute = 60.f;`
- L17 _public prototype_ `FDaySequenceTime(int32 InHours = 0, int32 InMinutes = 0, int32 InSeconds = 0);`
- L19 _public prototype_ `bool operator==(const FDaySequenceTime& RHS) const;`
- L20 _public prototype_ `bool operator!=(const FDaySequenceTime& RHS) const;`
- L22 _public prototype_ `float ToHours() const;`
- L23 _public prototype_ `float ToSeconds() const;`
- L25 _public prototype_ `static FDaySequenceTime FromHours(float InHours);`
- L26 _public prototype_ `static FDaySequenceTime FromSeconds(float InSeconds);`
- L28 _public function_ `FString ToString(bool bForceSignDisplay = false) const`
- L42 _public member_ `int32 Hours;` — `UPROPERTY()`
- L45 _public member_ `int32 Minutes;` — `UPROPERTY()`
- L48 _public member_ `int32 Seconds;` — `UPROPERTY()`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/DaySequenceTrack.h` (Public)


#### class `UDaySequenceTrack`  
`class UDaySequenceTrack : public UMovieSceneSubTrack`  
_L9-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSubTrack`
- L13 _public prototype_ `UDaySequenceTrack(const FObjectInitializer& ObjectInitializer);`
- L15 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;`
- L19 _public member_ `FText DisplayName;`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/IDaySequenceModule.h` (Public)


#### class `IDaySequenceModule`  
`class IDaySequenceModule : public IModuleInterface`  
_L11-23_
- inherits: `IModuleInterface`
- desc: Implements the DaySequence module.
- L16 _public prototype_ `virtual FDelegateHandle RegisterObjectSpawner(FOnCreateMovieSceneObjectSpawner InOnCreateMovieSceneObjectSpawner) = 0;` — Register an object spawner
- L19 _public prototype_ `virtual void GenerateObjectSpawners(TArray<TSharedRef<IMovieSceneObjectSpawner>>& OutSpawners) const = 0;` — Populate the specified array with new object spawner instances for all registered object spawner types
- L22 _public prototype_ `virtual void UnregisterObjectSpawner(FDelegateHandle InHandle) = 0;` — Unregister an object spawner

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/IDaySequencePlayer.h` (Public)


#### class `UE::DaySequence::FOverrideUpdateIntervalHandle`  
`class FOverrideUpdateIntervalHandle`  
_L15-28_
- L18 _public prototype_ `FOverrideUpdateIntervalHandle(UDaySequencePlayer* InPlayer);`
- L19 _public prototype_ `~FOverrideUpdateIntervalHandle();`
- L21 _public prototype_ `void StartOverriding();`
- L22 _public prototype_ `void StopOverriding();`
- L25 _private member_ `TWeakObjectPtr<UDaySequencePlayer> WeakPlayer;`
- L27 _private member_ `bool bIsOverriding;`

#### class `IDaySequencePlayer`  
`class IDaySequencePlayer`  
_L31-48_
- L35 _public prototype_ `virtual void Pause() = 0;`
- L37 _public prototype_ `virtual bool HasEverEvaluated() const = 0;`
- L39 _public prototype_ `virtual FQualifiedFrameTime GetCurrentTime() const = 0;`
- L41 _public prototype_ `virtual FQualifiedFrameTime GetDuration() const = 0;`
- L43 _public prototype_ `virtual int32 GetCurrentNumLoops() const = 0;`
- L45 _public prototype_ `virtual void SetIgnorePlaybackReplication(bool bState) = 0;`
- L47 _public prototype_ `virtual TSharedPtr<UE::DaySequence::FOverrideUpdateIntervalHandle> GetOverrideUpdateIntervalHandle() = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DAYSEQUENCE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DaySequence` (scope `UE`)

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/ProceduralDaySequence.h` (Public)


#### struct `FProceduralDaySequence`  
`struct FProceduralDaySequence`  
_L41-57_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base class for procedural sequences. To create a procedural sequence, a subclass of this type should be created that overrides BuildSequence. See FSunPositionSequence, FSunAngleSequence, and FSineSequence for examples.
- L45 _public prototype_ `virtual ~FProceduralDaySequence() = default;`
- L47 _public prototype_ `UDaySequence* GetSequence(ADaySequenceActor* InActor);`
- L50 _public member_ `FDaySequenceConditionSet Conditions;` — `UPROPERTY(EditAnywhere, Category="Day Sequence")`
- L54 _protected function_ `virtual void BuildSequence(UProceduralDaySequenceBuilder* InBuilder)`
- L56 _protected member_ `TWeakObjectPtr<ADaySequenceActor> WeakTargetActor = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DAYSEQUENCE_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace DaySequence` (scope `UE`)
- L21 _function_ `template <typename T> T* GetComponentByName(AActor* InActor, FName Name)` (scope `UE::DaySequence`) — Utility function to simplify looking for owned components by type and name.

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/ProceduralDaySequenceBuilder.h` (Public)


#### class `UProceduralDaySequenceBuilder`  
`class UProceduralDaySequenceBuilder : public UObject`  
_L24-136_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A utility class for creating procedural Day Sequences. Before adding any keys, SetActiveBoundObject should be called and provided a Day Sequence Actor or a component owned by a Day Sequence Actor. All time values are currently normalized to the range [0, 1], inclusive on both ends. A time of 1 is handled as a special case and maps to the final frame. This class assumes the target Day Sequence Actor will stay alive and that users will keep the generated sequence alive, it manages no lifetimes. Consider using FProceduralDaySequence instead of using this class directly.
- L39 _public prototype_ `UDaySequence* Initialize(ADaySequenceActor* InActor, UDaySequence* InitialSequence = nullptr, bool bClearInitialSequence = true);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")` — Initialize the procedural sequence and set the TargetActor for this builder. @param InActor The target DaySequenceActor that will be animated by the generated sequence. @param InitialSequence Optional sequence that this builder can operate on instead of allocating a new sequence. @param bClearInitialSequence If true, calls ClearKeys(). @return The sequence which will be modified when calling SetActiveBoundObject and the Add*Key(s) functions.
- L43 _public prototype_ `bool IsInitialized() const;` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")` — Returns true Initialize has been called with a valid actor.
- L47 _public prototype_ `void SetActiveBoundObject(UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")` — Prepare the builder to begin adding keys animating properties on InObject.
- L53 _public prototype_ `void AddBoolOverride(FName PropertyName, bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L55 _public prototype_ `void AddBoolKey(FName PropertyName, float Key, bool Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L56 _public prototype_ `void AddBoolKey(FName PropertyName, const TPair<float, bool>& KeyValue);`
- L57 _public prototype_ `void AddBoolKeys(FName PropertyName, const TArray<TPair<float, bool>>& KeysAndValues);`
- L61 _public prototype_ `void AddScalarOverride(FName PropertyName, double Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L63 _public prototype_ `void AddScalarKey(FName PropertyName, float Key, double Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L64 _public prototype_ `void AddScalarKey(FName PropertyName, const TPair<float, double>& KeyValue, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L65 _public prototype_ `void AddScalarKeys(FName PropertyName, const TArray<TPair<float, double>>& KeysAndValues, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L69 _public prototype_ `void AddVectorOverride(FName PropertyName, FVector Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L71 _public prototype_ `void AddVectorKey(FName PropertyName, float Key, FVector Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L72 _public prototype_ `void AddVectorKey(FName PropertyName, const TPair<float, FVector>& KeyValue, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L73 _public prototype_ `void AddVectorKeys(FName PropertyName, const TArray<TPair<float, FVector>>& KeysAndValues, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L77 _public prototype_ `void AddColorOverride(FName PropertyName, FLinearColor Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L78 _public prototype_ `void AddColorKeys(FName PropertyName, const TArray<TPair<float, FLinearColor>>& KeysAndValues, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L82 _public prototype_ `void AddTransformOverride(const FTransform& Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L83 _public prototype_ `void AddTransformKey(float Key, const FTransform& Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);`
- L85 _public prototype_ `void AddTranslationKey(float Key, const FVector& Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L87 _public prototype_ `void AddRotationKey(float Key, const FRotator& Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L89 _public prototype_ `void AddScaleKey(float Key, const FVector& Value, ERichCurveInterpMode InterpMode = RCIM_Cubic);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L93 _public prototype_ `void AddMaterialOverride(int32 MaterialIndex, UMaterialInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L97 _public prototype_ `void AddScalarMaterialParameterOverride(FName ParameterName, int32 MaterialIndex, float Value);` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")`
- L98 _public prototype_ `void AddScalarMaterialParameterKeys(FName ParameterName, int32 MaterialIndex, const TArray<TPair<float, float>>& KeysAndValues);`
- L102 _public prototype_ `void AddColorMaterialParameterOverride(FName ParameterName, int32 MaterialIndex, FLinearColor Value);` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")`
- L103 _public prototype_ `void AddColorMaterialParameterKeys(FName ParameterName, int32 MaterialIndex, const TArray<TPair<float, FLinearColor>>& KeysAndValues);`
- L107 _public prototype_ `void AddVisibilityOverride(bool bValue);` — `UFUNCTION(BlueprintCallable, Category="Day Sequence")`
- L108 _public prototype_ `void AddVisibilityKeys(const TArray<TPair<float, bool>>& KeysAndValues);`
- L114 _public prototype_ `void ClearKeys();` — `UFUNCTION(BlueprintCallable, Category = "Day Sequence")`
- L117 _private prototype_ `FGuid GetOrCreateProceduralBinding(UObject* Object) const;`
- L120 _private prototype_ `template<typename TrackType> TrackType* CreateOrAddOverrideTrack(FName Name);`
- L123 _private prototype_ `template<typename TrackType> TrackType* CreateOrAddPropertyOverrideTrack(FName Name);`
- L126 _private prototype_ `template<typename TrackType, typename SectionType> SectionType* CreateOrAddPropertyOverrideSection(FName Name);`
- L130 _private member_ `TObjectPtr<UDaySequence> ProceduralDaySequence = nullptr;` — This is returned immediately upon creation in InitializeSequence. The caller is responsible for holding a reference to prevent GC.
- L132 _private member_ `TObjectPtr<ADaySequenceActor> TargetActor = nullptr;`
- L134 _private member_ `TObjectPtr<UObject> ActiveBoundObject = nullptr;`
- L135 _private member_ `FGuid ActiveBinding;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/ProceduralSequences/SineSequence.h` (Public)


#### struct `FSineSequence`  
`struct FSineSequence : public FProceduralDaySequence`  
_L15-47_
- reflection: `USTRUCT()`
- inherits: `FProceduralDaySequence`
- desc: A procedural sequence that animates a user specified property according to a sine wave.
- L19 _public prototype_ `virtual ~FSineSequence() override = default;`
- L23 _public member_ `FName PropertyName = FName(TEXT(""));` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")` — The name of the float property to animate.
- L27 _public member_ `FName ComponentName = FName(TEXT(""));` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")` — Optional component, used if the property being animated is on a component owned by the Day Sequence Actor.
- L30 _public member_ `unsigned KeyCount = 5;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L33 _public member_ `float Amplitude = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L36 _public member_ `float Frequency = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L39 _public member_ `float PhaseShift = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L42 _public member_ `float VerticalShift = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L46 _private prototype_ `virtual void BuildSequence(UProceduralDaySequenceBuilder* InBuilder) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/ProceduralSequences/SunAngleSequence.h` (Public)


#### struct `FSunAngleSequence`  
`struct FSunAngleSequence : public FProceduralDaySequence`  
_L15-27_
- reflection: `USTRUCT()`
- inherits: `FProceduralDaySequence`
- desc: A procedural sequence that linearly animates the sun.
- L19 _public prototype_ `virtual ~FSunAngleSequence() override = default;`
- L22 _public member_ `FName SunComponentName = FName(TEXT("Sun"` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L26 _private prototype_ `virtual void BuildSequence(UProceduralDaySequenceBuilder* InBuilder) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DAYSEQUENCE_API`

### `Plugins/Experimental/DaySequence/Source/DaySequence/Public/ProceduralSequences/SunPositionSequence.h` (Public)


#### struct `FSunPositionSequence`  
`struct FSunPositionSequence : public FProceduralDaySequence`  
_L15-45_
- reflection: `USTRUCT()`
- inherits: `FProceduralDaySequence`
- desc: A procedural sequence that animates a sun in a physically accurate way based on geographic data.
- L19 _public prototype_ `virtual ~FSunPositionSequence() override = default;`
- L22 _public member_ `FName SunComponentName = FName(TEXT("Sun"` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L25 _public member_ `unsigned KeyCount = 24;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L28 _public member_ `FDateTime Time;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L31 _public member_ `double TimeZone = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L34 _public member_ `double Latitude = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L37 _public member_ `double Longitude = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L40 _public member_ `bool bIsDaylightSavings = false;` — `UPROPERTY(EditAnywhere, Category = "Procedural Parameters")`
- L44 _private prototype_ `virtual void BuildSequence(UProceduralDaySequenceBuilder* InBuilder) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DAYSEQUENCE_API`
