# Plugins / LearningAgentsReplay

- module root: `Plugins/Experimental/LearningAgents/Source/LearningAgentsReplay`
- headers: 3; symbols: 40
- symbol kinds: class=5, delegate=1, function=5, macro=1, member=8, prototype=20
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, NetworkReplayStreaming

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsReplay/Public/AsyncAction_LearningAgentsQueryReplays.h` (Public)


#### class `UAsyncAction_LearningAgentsQueryReplays`  
`class UAsyncAction_LearningAgentsQueryReplays : public UBlueprintAsyncActionBase`  
_L23-50_
- reflection: `UCLASS()`
- inherits: `UBlueprintAsyncActionBase`
- desc: Returns a list of stored replays for a given player controller
- L28 _public prototype_ `UAsyncAction_LearningAgentsQueryReplays(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `static UAsyncAction_LearningAgentsQueryReplays* QueryLearningAgentsReplays(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))`
- L33 _public prototype_ `virtual void Activate() override;`
- L38 _public member_ `FQueryReplayAsyncDelegate QueryComplete;` — `UPROPERTY(BlueprintAssignable)` — Called when the replay query completes
- L41 _private prototype_ `void OnEnumerateStreamsComplete(const FEnumerateStreamsResult& Result);`
- L45 _private member_ `TObjectPtr<ULearningAgentsReplayList> ResultList;` — `UPROPERTY()`
- L47 _private member_ `TWeakObjectPtr<APlayerController> PlayerController;`
- L49 _private member_ `TSharedPtr<INetworkReplayStreamer> ReplayStreamer;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueryReplayAsyncDelegate, ULearningAgentsReplayList*, Results);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueryReplayAsyncDelegate, ULearningAgentsReplayList*, Results);`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsReplay/Public/LearningAgentsReplay.h` (Public)


#### class `FLearningAgentsReplayModule`  
`class FLearningAgentsReplayModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsReplay/Public/LearningAgentsReplaySubsystem.h` (Public)


#### class `ULearningAgentsReplayListEntry`  
`class ULearningAgentsReplayListEntry : public UObject`  
_L17-43_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: An available replay for display in the UI
- L22 _public member_ `FNetworkReplayStreamInfo StreamInfo;`
- L26 _public function_ `FString GetFriendlyName() const` — `UFUNCTION(BlueprintPure, Category=Replays)` — The UI friendly name of the stream
- L30 _public function_ `FDateTime GetTimestamp() const` — `UFUNCTION(BlueprintPure, Category=Replays)` — The date and time the stream was recorded
- L34 _public function_ `FTimespan GetDuration() const` — `UFUNCTION(BlueprintPure, Category=Replays)` — The duration of the stream in MS
- L38 _public function_ `int32 GetNumViewers() const` — `UFUNCTION(BlueprintPure, Category=Replays)` — Number of viewers viewing this stream
- L42 _public function_ `bool GetIsLive() const` — `UFUNCTION(BlueprintPure, Category=Replays)` — True if the stream is live and the game hasn't completed yet

#### class `ULearningAgentsReplayList`  
`class ULearningAgentsReplayList : public UObject`  
_L47-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Results of querying for replays list of results for the UI
- L53 _public member_ `TArray<TObjectPtr<ULearningAgentsReplayListEntry>> Results;` — `UPROPERTY(BlueprintReadWrite, Category=Replays)`

#### class `ULearningAgentsReplaySubsystem`  
`class ULearningAgentsReplaySubsystem : public UGameInstanceSubsystem`  
_L58-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameInstanceSubsystem`
- desc: Subsystem to handle recording/loading replays. Exposes functionality to Blueprints
- L63 _public prototype_ `ULearningAgentsReplaySubsystem();`
- L65 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L66 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L67 _public prototype_ `virtual void Deinitialize() override;`
- L70 _public prototype_ `void OnDemoPlayStarted();` — `UFUNCTION()`
- L74 _public prototype_ `static bool DoesPlatformSupportReplays();` — `UFUNCTION(BlueprintCallable, Category = Replays, BlueprintPure = false)` — Returns true if this platform supports replays at all
- L78 _public prototype_ `void PlayReplay(ULearningAgentsReplayListEntry* Replay);` — `UFUNCTION(BlueprintCallable, Category=Replays)` — Loads the appropriate map and plays a replay
- L82 _public prototype_ `void StopRecordingReplay();` — `UFUNCTION(BlueprintCallable, Category=Replays)` — Stops the current active recording
- L86 _public prototype_ `void RecordClientReplay(APlayerController* PlayerController);` — `UFUNCTION(BlueprintCallable, Category = Replays)` — Starts recording a client replay, and handles any file cleanup needed
- L90 _public prototype_ `void SeekInActiveReplay(float TimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category=Replays)` — Move forward or back in currently playing replay
- L94 _public prototype_ `float GetReplayLengthInSeconds() const;` — `UFUNCTION(BlueprintCallable, Category = Replays, BlueprintPure = false)` — Gets length of current replay
- L98 _public prototype_ `float GetReplayCurrentTime() const;` — `UFUNCTION(BlueprintCallable, Category=Replays, BlueprintPure=false)` — Gets current playback time
- L101 _private member_ `TSharedPtr<INetworkReplayStreamer> CurrentReplayStreamer;`
- L104 _private member_ `TObjectPtr<ULocalPlayer> LocalPlayerDeletingReplays;` — `UPROPERTY()`
- L106 _private prototype_ `UDemoNetDriver* GetDemoDriver() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSREPLAY_API`
