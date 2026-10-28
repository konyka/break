# Plugins / AvalancheSequence

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence`
- headers: 36; symbols: 569
- symbol kinds: class=24, delegate=3, enum=13, enumerator=40, function=60, member=102, namespace=4, prototype=292, struct=23, typedef=7, variable=1
- PrivateDependencyModuleNames: AvalancheCore, BlueprintGraph, Sequencer, StateTreeModule
- PublicDependencyModuleNames: AvalancheTag, AvalancheTransition, Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/AvaSequenceController.h` (Private)


#### class `FAvaSequenceController`  
`class FAvaSequenceController : public IAvaSequenceController`  
_L25-80_
- inherits: `IAvaSequenceController`
- L28 _public prototype_ `FAvaSequenceController(UAvaSequence& InSequence, IAvaSequencePlaybackObject* InPlaybackObject);`
- L33 _public prototype_ `virtual void SetTime(const FFrameTime& InNewTime, bool bInResetState) override;`
- L34 _public prototype_ `virtual void Tick(const FAvaSequencePlayerVariant& InPlayerVariant, const FFrameTime& InDeltaFrameTime, float InDeltaSeconds) override;`
- L35 _public function_ `virtual UAvaSequence* GetSequence() const override`
- L36 _public prototype_ `virtual TSharedRef<IAvaSequencePlaybackContext> GetPlaybackContext() const override;`
- L40 _private prototype_ `FString GetMarkRoleAsString(const UAvaSequence& InSequence, const FMovieSceneMarkedFrame& InMark) const;`
- L42 _private prototype_ `FString GetMarkAsString(UMovieScene& InMovieScene, const FMovieSceneMarkedFrame& InMark) const;`
- L44 _private prototype_ `void OnTreeNodeCleanup();`
- L46 _private prototype_ `void ResetState();`
- L48 _private prototype_ `void UpdatePlayers();`
- L51 _private prototype_ `void UpdatePlaybackVariables();` — Updates Current Frame, returning the Old Current Frame
- L53 _private prototype_ `void SortMarks(UMovieScene& InMovieScene);`
- L55 _private prototype_ `TArray<const FMovieSceneMarkedFrame*> FindIntersectedMarks(UMovieScene& InMovieScene);`
- L57 _private prototype_ `bool IsMarkValid(const FMovieSceneMarkedFrame& InMarkedFrame, const UAvaSequence& InSequence) const;`
- L59 _private prototype_ `EAvaMarkRoleReply ExecuteMark(const FMovieSceneMarkedFrame& InMarkedFrame, const UAvaSequence& InSequence);`
- L61 _private member_ `TSharedRef<FAvaSequencePlaybackContext> PlaybackContext;`
- L63 _private member_ `FAvaMarkRoleHandler MarkRoleHandler;`
- L65 _private member_ `EMovieScenePlayerStatus::Type PlaybackStatus;`
- L67 _private member_ `TWeakObjectPtr<UAvaSequence> SequenceWeak;`
- L69 _private member_ `FFrameTime PreviousFrame;`
- L71 _private member_ `FFrameTime CurrentFrame;`
- L74 _private member_ `TSet<FFrameNumber> MarkFramesProcessed;` — The Marks that were processed/executed last time
- L77 _private member_ `const IMovieScenePlayer* LastPlayer = nullptr;` — Used to check if the Players differ
- L79 _private member_ `EPlayDirection PlayDirection;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/AvaSequencePlaybackActor.h` (Private)


#### class `AAvaSequencePlaybackActor`  
`class AAvaSequencePlaybackActor : public AActor, public IAvaSequencePlaybackObject`  
_L17-121_
- reflection: `UCLASS(NotPlaceable, Hidden, DisplayName = "Motion Design Sequence Playback Actor")`
- inherits: `AActor,IAvaSequencePlaybackObject`
- desc: Base Actor for Ava Sequence Playback Management
- L22 _public prototype_ `AAvaSequencePlaybackActor();`
- L24 _public prototype_ `void SetSequenceProvider(IAvaSequenceProvider& InSequenceProvider);`
- L28 _protected function_ `virtual UObject* ToUObject() override`
- L29 _protected function_ `virtual ULevel* GetPlaybackLevel() const`
- L30 _protected prototype_ `virtual void CleanupPlayers() override;`
- L31 _protected prototype_ `virtual UAvaSequencePlayer* PlaySequence(UAvaSequence* InSequence, const FAvaSequencePlayParams& InPlaySettings = FAvaSequencePlayParams()) override;`
- L32 _protected prototype_ `virtual UAvaSequencePlayer* PreviewFrame(UAvaSequence* InSequence) override;`
- L33 _protected prototype_ `virtual UAvaSequencePlayer* PlaySequenceBySoftReference(TSoftObjectPtr<UAvaSequence> InSequence, const FAvaSequencePlayParams& InPlaySettings) override;`
- L34 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByLabel(FName InSequenceLabel, const FAvaSequencePlayParams& InPlaySettings) override;`
- L35 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesBySoftReference(const TArray<TSoftObjectPtr<UAvaSequence>>& InSequences, const FAvaSequencePlayParams& InPlaySettings) override;`
- L36 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByLabels(const TArray<FName>& InSequenceLabels, const FAvaSequencePlayParams& InPlaySettings) override;`
- L37 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch, const FAvaSequencePlayParams& InPlaySettings) override;`
- L38 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> PlayScheduledSequences() override;`
- L39 _protected prototype_ `virtual UAvaSequencePlayer* ContinueSequence(UAvaSequence* InSequence) override;`
- L40 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByLabel(FName InSequenceLabel) override;`
- L41 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByLabels(const TArray<FName>& InSequenceLabels) override;`
- L42 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) override;`
- L43 _protected prototype_ `virtual void PauseSequence(UAvaSequence* InSequence) override;`
- L44 _protected prototype_ `virtual void PauseSequencesByLabel(FName InSequenceLabel) override;`
- L45 _protected prototype_ `virtual void PauseSequencesByLabels(const TArray<FName>& InSequenceLabels) override;`
- L46 _protected prototype_ `virtual void PauseSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) override;`
- L47 _protected prototype_ `virtual void StopSequence(UAvaSequence* InSequence) override;`
- L48 _protected prototype_ `virtual void StopSequencesByLabel(FName InSequenceLabel) override;`
- L49 _protected prototype_ `virtual void StopSequencesByLabels(const TArray<FName>& InSequenceLabels) override;`
- L50 _protected prototype_ `virtual void StopSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) override;`
- L51 _protected prototype_ `virtual UObject* GetPlaybackContext() const override;`
- L52 _protected prototype_ `virtual UAvaSequencePlayer* GetSequencePlayer(const UAvaSequence* InSequence) const override;`
- L53 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayers(TConstArrayView<const UAvaSequence*> InSequences) const override;`
- L54 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByLabel(FName InSequenceLabel) const override;`
- L55 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByLabels(const TArray<FName>& InSequenceLabels) const override;`
- L56 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) const override;`
- L57 _protected prototype_ `virtual TArray<UAvaSequencePlayer*> GetAllSequencePlayers() const override;`
- L58 _protected prototype_ `virtual bool HasActiveSequencePlayers() const override;`
- L59 _protected prototype_ `virtual void UpdateCameraCut(const UE::MovieScene::FOnCameraCutUpdatedParams& InCameraCutParams) override;`
- L60 _protected prototype_ `virtual UObject* CreateDirectorInstance(IMovieScenePlayer& InPlayer, FMovieSceneSequenceID InSequenceID) override;`
- L61 _protected function_ `virtual FOnCameraCut& GetOnCameraCut() override`
- L65 _protected prototype_ `virtual void BeginDestroy() override;`
- L66 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;`
- L68 _protected function_ `virtual bool IsSelectable() const override`
- L69 _protected function_ `virtual bool SupportsExternalPackaging() const override`
- L73 _protected prototype_ `UAvaSequencePlayer* GetOrAddSequencePlayer(UAvaSequence* InSequence);`
- L76 _protected prototype_ `void RegisterPlaybackObject();` — Registers this Playback Object to the World's Sequence Tick Manager
- L79 _protected prototype_ `void UnregisterPlaybackObject();` — Unregisters this Playback Object from the World's Sequence Tick Manager
- L82 _protected prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);` — Called when on FWorldDelegates::OnWorldCleanup
- L84 _protected prototype_ `void OnSequenceFinished(UAvaSequencePlayer* InPlayer, UAvaSequence* InSequence);`
- L87 _private prototype_ `const TArray<UAvaSequence*>& GetAllSequences() const;`
- L89 _private prototype_ `TArray<UAvaSequence*> GetSequencesByLabel(TConstArrayView<FName> InSequenceLabels) const;`
- L91 _private prototype_ `TArray<UAvaSequence*> GetSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) const;`
- L94 _private prototype_ `void BP_PlayScheduledSequences();` — `UFUNCTION(BlueprintCallable, CallInEditor, DisplayName="Play Scheduled Sequences", Category="Scheduled Playback")`
- L98 _private member_ `TArray<FName> ScheduledSequenceNames;` — `UPROPERTY(EditAnywhere, DisplayName="Scheduled Sequences", Category="Scheduled Playback", meta=(AllowPrivateAccess="true"))` — Name of the Sequences play when PlayScheduledSequence is called, separated by comma
- L101 _private member_ `FAvaSequencePlayParams ScheduledPlaySettings;` — `UPROPERTY(EditAnywhere, Category="Scheduled Playback", meta=(AllowPrivateAccess="true"))`
- L105 _private member_ `TSet<TObjectPtr<UAvaSequencePlayer>> ActiveSequencePlayers;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — All the sequence players currently playing
- L109 _private member_ `TSet<TObjectPtr<UAvaSequencePlayer>> StoppedSequencePlayers;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — List of sequence players to cache and clean up when safe
- L112 _private member_ `TScriptInterface<IAvaSequenceProvider> SequenceProvider;` — `UPROPERTY()`
- L115 _private member_ `FOnCameraCut OnCameraCut;` — Called when a Camera Cut occurs.
- L117 _private member_ `FDelegateHandle OnSequenceFinishedDelegate;`
- L118 _private member_ `FDelegateHandle OnWorldCleanupDelegate;`
- L120 _private member_ `bool bStoppingAllSequences = false;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/AvaSequencePlaybackContext.h` (Private)


#### class `FAvaSequencePlaybackContext`  
`class FAvaSequencePlaybackContext : public IAvaSequencePlaybackContext`  
_L35-128_
- inherits: `IAvaSequencePlaybackContext`
- desc: PlaybackContext contains and resolves data for a given Sequence and its Player This class resolves the Player type to recognized types (e.g. Sequencer or AvaSequencePlayer) to have more things available to call like PlayPosition, Pause, Continue, etc
- L38 _public prototype_ `FAvaSequencePlaybackContext(UAvaSequence& InSequence, IAvaSequencePlaybackObject* InPlaybackObject);`
- L40 _public prototype_ `virtual ~FAvaSequencePlaybackContext() override = default;`
- L42 _public prototype_ `void Resolve(const FAvaSequencePlayerVariant& InPlayerVariant, const FFrameTime& InDeltaFrameTime);`
- L44 _public function_ `UAvaSequence* GetSequence() const`
- L46 _public prototype_ `IAvaSequencePlaybackObject* GetPlaybackObject() const;`
- L48 _public prototype_ `EMovieScenePlayerStatus::Type GetPlaybackStatus() const;`
- L50 _public prototype_ `IMovieScenePlayer* GetPlayer() const;`
- L53 _public function_ `TOptional<FFrameTime> GetLastJumpedFrame() const` — Returns Last Tick's Jumped Frame, if it did jump. Else it returns it unset
- L55 _public prototype_ `void UpdateMarkedFrame(const FMovieSceneMarkedFrame& InMarkedFrame);`
- L57 _public prototype_ `TArray<TSharedRef<IAvaSequencePlaybackContext>> GatherChildContexts() const;`
- L59 _public prototype_ `void RequestRefreshChildren();`
- L62 _public prototype_ `FFrameTime GetGlobalTime() const;`
- L63 _public function_ `FFrameTime GetDeltaFrameTime() const`
- L64 _public function_ `virtual bool IsPlayingForwards() const override`
- L65 _public prototype_ `virtual void Pause() override;`
- L66 _public prototype_ `virtual void Continue() override;`
- L67 _public prototype_ `virtual void Reverse() override;`
- L68 _public prototype_ `virtual void JumpTo(const FFrameTime& InFrameTime, bool bInEvaluateJumpedFrames) override;`
- L69 _public prototype_ `virtual void JumpToSelf() override;`
- L70 _public prototype_ `virtual const FAvaMark& GetMark() const override;`
- L71 _public prototype_ `virtual const TSet<FAvaMark>& GetAllMarks() const override;`
- L72 _public function_ `virtual const FMovieSceneMarkedFrame& GetMarkedFrame() const override`
- L73 _public function_ `virtual FTSTicker& GetTicker() override`
- L74 _public prototype_ `virtual TConstArrayView<TWeakPtr<IAvaSequencePlaybackContext>> GetChildrenInContext() const override;`
- L75 _public prototype_ `virtual void ResolveFromParent(const IAvaSequencePlaybackContext& InParent) override;`
- L81 _private function_ `template<typename Func, typename...Params> void RunChildren(Func&& InFunc, Params&&... InParams)` — Iteratively Execute on all Children and if set also their Children
- L98 _private member_ `TWeakObjectPtr<UAvaSequence> SequenceWeak;`
- L100 _private member_ `TWeakInterfacePtr<IAvaSequencePlaybackObject> PlaybackObjectWeak;`
- L102 _private member_ `TWeakObjectPtr<UAvaSequencePlayer> SequencePlayer;`
- L104 _private member_ `TArray<TWeakPtr<IAvaSequencePlaybackContext>> ChildrenWeak;`
- L107 _private member_ `FMovieSceneMarkedFrame MarkedFrame;` — Marked Frame Reached
- L110 _private member_ `TWeakPtr<ISequencer> EditorSequencer;`
- L113 _private member_ `FFrameNumber LastFrame;`
- L115 _private member_ `IMovieScenePlayer* Player = nullptr;`
- L117 _private member_ `FFrameTime DeltaFrameTime;`
- L119 _private member_ `TOptional<FFrameTime> LastJumpedFrame;`
- L121 _private member_ `TOptional<FFrameTime> JumpedFrame;`
- L123 _private member_ `FTSTicker Ticker;`
- L125 _private member_ `bool bPlayingForwards = true;`
- L126 _private member_ `bool bShouldRunChildren = false;`
- L127 _private member_ `bool bPendingChildrenRefresh = true;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/AvaSequenceVersion.h` (Private)


#### struct `FAvaSequenceVersion`  
`struct FAvaSequenceVersion`  
_L7-28_
- L10 _private prototype_ `FAvaSequenceVersion() = delete;`
- L27 _public member_ `const static FGuid GUID;`

#### enum `FAvaSequenceVersion::Type`  
`enum Type : uint8`  
_L13-25_
- L15 _public enumerator_ `PreVersioning = 0`
- L18 _public enumerator_ `LevelSequence` — Moved to become child class of ULevelSequence
- L21 _public enumerator_ `SequenceTimeConstraintOption` — Introduced Time Constraint Option to FAvaSequenceTime
- L23 _public enumerator_ `VersionPlusOne`
- L24 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/Marks/AvaMarkRole_Jump.h` (Private)


#### class `FAvaMarkRole_Jump`  
`class FAvaMarkRole_Jump : public FAvaMarkRole`  
_L7-16_
- inherits: `FAvaMarkRole`
- L10 _public prototype_ `virtual ~FAvaMarkRole_Jump() override = default;`
- L13 _public function_ `virtual EAvaMarkRole GetRole() const override`
- L14 _public prototype_ `virtual EAvaMarkRoleReply Execute() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/Marks/AvaMarkRole_Pause.h` (Private)


#### class `FAvaMarkRole_Pause`  
`class FAvaMarkRole_Pause : public FAvaMarkRole`  
_L9-26_
- inherits: `FAvaMarkRole`
- L15 _public function_ `virtual EAvaMarkRole GetRole() const override`
- L16 _public prototype_ `virtual EAvaMarkRoleReply Execute() override;`
- L17 _public prototype_ `virtual void Reset() override;`
- L21 _protected prototype_ `bool Unpause(float DeltaTime);`
- L23 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L25 _protected member_ `FFrameNumber PauseStartFrame;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/Marks/AvaMarkRole_Reverse.h` (Private)


#### class `FAvaMarkRole_Reverse`  
`class FAvaMarkRole_Reverse : public FAvaMarkRole`  
_L7-16_
- inherits: `FAvaMarkRole`
- L10 _public prototype_ `virtual ~FAvaMarkRole_Reverse() override = default;`
- L13 _public function_ `virtual EAvaMarkRole GetRole() const override`
- L14 _public prototype_ `virtual EAvaMarkRoleReply Execute() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Private/Marks/AvaMarkRole_Stop.h` (Private)


#### class `FAvaMarkRole_Stop`  
`class FAvaMarkRole_Stop : public FAvaMarkRole`  
_L7-16_
- inherits: `FAvaMarkRole`
- L10 _public prototype_ `virtual ~FAvaMarkRole_Stop() override = default;`
- L13 _public function_ `virtual EAvaMarkRole GetRole() const override`
- L14 _public prototype_ `virtual EAvaMarkRoleReply Execute() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequence.h` (Public)


#### class `UAvaSequence`  
`class UAvaSequence : public ULevelSequence`  
_L32-190_
- reflection: `UCLASS(BlueprintType, Config=MotionDesign)`
- inherits: `ULevelSequence`
- L37 _public prototype_ `UAvaSequence(const FObjectInitializer& InObjectInitializer);`
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceEditUndoEvent, UAvaSequence*);`
- L45 _public function_ `static FOnSequenceEditUndoEvent::RegistrationType& OnSequenceEditUndo()` — Called on Sequence Edit Undo
- L51 _public prototype_ `IAvaSequenceProvider* GetSequenceProvider() const;`
- L57 _public prototype_ `UWorld* GetContextWorld() const;` — Gets the World of the Sequencer Provider. May be null if world has not been set Note: UObject::GetWorld isn't overriden to allow the IAvaSequenceProvider or other Outer to decide on the UWorld to return for that.
- L60 _public prototype_ `FName GetLabel() const;` — `UFUNCTION(BlueprintPure, Category = "Label")`
- L63 _public prototype_ `void SetLabel(FName InLabel);` — `UFUNCTION(BlueprintCallable, Category = "Label")`
- L66 _public prototype_ `FAvaTagHandle GetSequenceTag() const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Sequence")`
- L68 _public prototype_ `void SetSequenceTag(const FAvaTagHandle& InSequenceTag);`
- L72 _public prototype_ `double GetStartTime() const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Sequence")` — Gets the Start Time of this Sequence
- L76 _public prototype_ `double GetEndTime() const;` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Sequence")` — Gets the End Time of this Sequence
- L79 _public prototype_ `void UpdateTreeNode();` — Cleans up this sequence and recursively calls this on each Child Sequence
- L81 _public function_ `FSimpleMulticastDelegate& GetOnTreeNodeUpdated()`
- L84 _public prototype_ `void OnSequenceRemoved();` — Called when this Sequence has been removed from its Manager
- L86 _public prototype_ `int32 AddChild(UAvaSequence* InChild);`
- L88 _public prototype_ `bool RemoveChild(UAvaSequence* InChild);`
- L90 _public prototype_ `void RemoveAllChildren();`
- L92 _public prototype_ `void SetParent(UAvaSequence* InParent);`
- L94 _public prototype_ `UAvaSequence* GetParent() const;`
- L96 _public function_ `const TArray<TWeakObjectPtr<UAvaSequence>>& GetChildren() const`
- L99 _public function_ `const TSet<FAvaMark>& GetMarks() const` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Sequence")`
- L105 _public prototype_ `const FAvaMark* GetPreviewMark() const;` — Returns the Preview Mark found using PreviewMarkLabel @return Pointer to the Mark set as Preview. Might be null if no preview mark was found, or if PreviewMarkLabel is empty
- L107 _public prototype_ `const FAvaMark* FindMark(const FMovieSceneMarkedFrame& InMarkedFrame) const;`
- L109 _public prototype_ `FAvaMark& FindOrAddMark(const FString& InMarkLabel);`
- L112 _public prototype_ `bool GetMark(const FString& InMarkLabel, FAvaMark& OutMark) const;` — `UFUNCTION(BlueprintCallable, Category = "Marks")`
- L115 _public prototype_ `bool SetMark(const FString& InMarkLabel, const FAvaMark& InMark);` — `UFUNCTION(BlueprintCallable, Category = "Marks")`
- L117 _public prototype_ `void UpdateMarkList();`
- L119 _public prototype_ `TArray<UObject*> GetBoundObjects(UObject* InPlaybackContext) const;`
- L122 _public prototype_ `virtual void Initialize() override;`
- L127 _public prototype_ `virtual FText GetDisplayName() const override;`
- L129 _public prototype_ `virtual UObject* CreateDirectorInstance(TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID InSequenceID) override;`
- L130 _public prototype_ `virtual bool CanPossessObject(UObject& InObject, UObject* InPlaybackContext) const override;`
- L131 _public prototype_ `virtual UObject* GetParentObject(UObject* InObject) const override;`
- L132 _public prototype_ `virtual bool CanAnimateObject(UObject& InObject) const override;`
- L136 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L137 _public prototype_ `virtual void PostLoad() override;`
- L139 _public prototype_ `virtual void PostEditUndo() override;`
- L140 _public prototype_ `void OnObjectTransacted(UObject* InObject, const FTransactionObjectEvent& InTransactionEvent);`
- L144 _public prototype_ `int32 UpdateBindings(const FTopLevelAssetPath* InOldContext, const FTopLevelAssetPath& InNewContext);`
- L147 _public prototype_ `TArrayView<TWeakObjectPtr<>> FindObjectsFromGuid(const FGuid& InGuid);` — Gets the Objects Bound for this Sequence. Potentially slow
- L150 _public prototype_ `FGuid FindGuidFromObject(UObject* InObject);` — Gets the Object Id for the given Object in this Sequence. Potentially slow
- L153 _public prototype_ `void OnOuterWorldRenamed(UObject* InNewOuter);`
- L157 _public prototype_ `void Cleanup();` — Called to clean up resources
- L159 _public prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);`
- L164 _protected member_ `static FOnSequenceEditUndoEvent OnSequenceEditUndoDelegate;` — Called on Sequence Edit Undo
- L169 _protected member_ `FName Label;` — `UPROPERTY()` — Label used to identify a sequence. Multiple sequences can share the same label.
- L172 _protected member_ `TWeakObjectPtr<UAvaSequence> ParentAnimation;` — `UPROPERTY(DuplicateTransient, TextExportTransient)`
- L175 _protected member_ `TArray<TWeakObjectPtr<UAvaSequence>> ChildAnimations;` — `UPROPERTY(DuplicateTransient, TextExportTransient)`
- L178 _protected member_ `FAvaTagHandle Tag;` — `UPROPERTY(EditAnywhere, DisplayName="Tags", Category = "Sequence Settings", meta=(AllowPrivateAccess="true"))`
- L182 _protected member_ `FString PreviewMarkLabel;` — `UPROPERTY(EditAnywhere, DisplayName="Preview Mark", Category = "Sequence Settings", meta=(AllowPrivateAccess="true"))` — The Mark to use to Preview the Sequence
- L186 _protected member_ `TSet<FAvaMark> Marks;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = "Sequence Settings", meta=(NoResetToDefault, AllowPrivateAccess="true"))` — The list of Marks in this Sequence
- L189 _protected member_ `FSimpleMulticastDelegate OnTreeNodeUpdated;` — Delegate called after the node has finished cleaning up itself its children

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequenceEditUndoEvent, UAvaSequence*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequenceActor.h` (Public)


#### class `AAvaSequenceActor`  
`class AAvaSequenceActor : public ALevelSequenceActor`  
_L12-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ALevelSequenceActor`
- L17 _public prototype_ `AAvaSequenceActor(const FObjectInitializer& InObjectInitializer);`
- L19 _public prototype_ `void Initialize(UAvaSequence* InSequence);`
- L23 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L27 _private prototype_ `void InitSequencePlayer(UAvaSequence* InSequence);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequenceLibrary.h` (Public)


#### class `UAvaSequenceLibrary`  
`class UAvaSequenceLibrary : public UBlueprintFunctionLibrary`  
_L15-26_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Sequence Library", meta=(ScriptName = "MotionDesignSequenceLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static TScriptInterface<IAvaSequencePlaybackObject> GetPlaybackObject(const UObject* InWorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = "Motion Design|Sequence", meta=(WorldContext = "InWorldContextObject"))`
- L25 _public prototype_ `static FAvaSequencePlayParams MakeSingleFramePlaySettings(const FAvaSequenceTime& InTargetTime, EAvaSequencePlayMode InPlayMode);` — `UFUNCTION(BlueprintPure, Category = "Motion Design|Sequence")` — Helper function to build Play Settings for Single Frame Playback

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequenceName.h` (Public)


#### struct `FAvaSequenceName`  
`struct FAvaSequenceName`  
_L9-34_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Sequence Name")`
- L13 _public prototype_ `FAvaSequenceName() = default;`
- L15 _public function_ `FAvaSequenceName(FName InSequenceName) : Name(InSequenceName)`
- L20 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& InPropertyTag, FStructuredArchive::FSlot InSlot);`
- L22 _public function_ `bool IsNone() const`
- L27 _public function_ `operator FName() const`
- L33 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion Design Sequence")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaSequenceName> : public TStructOpsTypeTraitsBase2<FAvaSequenceName>`  
_L37-43_
- inherits: `TStructOpsTypeTraitsBase2<FAvaSequenceName>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L40-42_

#### Free symbols / members of external scopes

- L41 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonf924c3f70103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequencePlaybackObject.h` (Public)


#### class `UAvaSequencePlaybackObject`  
`class UAvaSequencePlaybackObject : public UInterface`  
_L23-26_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IAvaSequencePlaybackObject`  
`class IAvaSequencePlaybackObject`  
_L28-224_
- L33 _public prototype_ `virtual UObject* ToUObject() = 0;`
- L35 _public prototype_ `virtual ULevel* GetPlaybackLevel() const = 0;`
- L41 _public prototype_ `virtual void CleanupPlayers() = 0;` — Tears down both the Active and Stopped Players in this Playback Object Should be only be called when ending play
- L43 _public prototype_ `virtual UAvaSequencePlayer* PlaySequence(UAvaSequence* InSequence, const FAvaSequencePlayParams& InPlaySettings = FAvaSequencePlayParams()) = 0;`
- L51 _public prototype_ `virtual UAvaSequencePlayer* PreviewFrame(UAvaSequence* InSequence) = 0;` — Evaluates the Preview Frame of a Sequence. Does nothing if the Sequence has no preview frame. @param InSequence the sequence to preview @return the player instantiated for the Sequence, or null if Sequence was not valid or did not have a preview mark
- L60 _public prototype_ `virtual UAvaSequencePlayer* PlaySequenceBySoftReference(TSoftObjectPtr<UAvaSequence> InSequence, const FAvaSequencePlayParams& InPlaySettings) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Play Sequence (by Soft Reference)", Category = "Playback")` — Plays a single sequence by its soft reference @param InSequence soft reference of the sequence to play @param InPlaySettings the play settings to use for playback @return the player instantiated for the Sequence, or null if Sequence was not valid for playback
- L69 _public prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByLabel(FName InSequenceLabel, const FAvaSequencePlayParams& InPlaySettings) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Play Sequences (by Label)", Category = "Playback")` — Plays all the sequences that have the provided label @param InSequenceLabel the label of the sequences to play @param InPlaySettings the play settings to use for playback @return an array of the Sequence Players with possible invalid/null entries kept so that each Player matches in Index with the input Sequence it is playing
- L78 _public prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesBySoftReference(const TArray<TSoftObjectPtr<UAvaSequence>>& InSequences, const FAvaSequencePlayParams& InPlaySettings) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Play Sequences (by Soft Reference)", Category = "Playback")` — Plays multiple Sequences by their Soft Reference @param InSequences the array of soft reference sequences to play @param InPlaySettings the play settings to use for playback @return an array of the Sequence Players with possible invalid/null entries kept so that each Player matches in Index with the input Sequence it is playing
- L87 _public prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByLabels(const TArray<FName>& InSequenceLabels, const FAvaSequencePlayParams& InPlaySettings) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Play Sequences (by Labels)", Category = "Playback")` — Plays multiple Sequences by an array of sequence labels @param InSequenceLabels the array of sequence labels to play @param InPlaySettings the play settings to use for playback @return an array of the Sequence Players with possible invalid/null entries kept so that each Player matches in Index with the input Sequence it is playing
- L97 _public prototype_ `virtual TArray<UAvaSequencePlayer*> PlaySequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch, const FAvaSequencePlayParams& InPlaySettings) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Play Sequences (by Tag)", Category = "Playback")` — Plays all the Sequences that match the given gameplay tag(s) @param InTagHandle the tag to match @param bInExactMatch whether to only consider sequences that have the tag exactly @param InPlaySettings the play settings to use for playback @return an array of the Sequence Players with only valid entries kept
- L104 _public prototype_ `virtual TArray<UAvaSequencePlayer*> PlayScheduledSequences() = 0;` — `UFUNCTION(BlueprintCallable, Category = "Playback")` — Plays the Scheduled Sequences with the Scheduled Play Settings @return an array of the Sequence Players with possible invalid/null entries kept so that each Player matches in Index with the Scheduled Sequence it is playing
- L111 _public prototype_ `virtual UAvaSequencePlayer* ContinueSequence(UAvaSequence* InSequence) = 0;` — Triggers Continue for given sequence @param InSequence the sequence to continue @return the active sequence player that fired the continue, or null if there was no active player for the sequence
- L119 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByLabel(FName InSequenceLabel) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Continue Sequences (by Label)", Category = "Playback")` — Triggers Continue for the playing sequences that match the given label @param InSequenceLabel the label of the sequences to continue @return the sequence players that fired the continue, or null if there were no active players
- L127 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByLabels(const TArray<FName>& InSequenceLabels) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Continue Sequences (by Labels)", Category = "Playback")` — Triggers Continues in multiple playing sequences given by an array of sequence labels @param InSequenceLabels the array of sequence labels to trigger continue (must be an active sequence playing) @return the sequence player array that fired the continue. It might have possible invalid/null entries so that each Player matches in Index with the input Sequence labels
- L136 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ContinueSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Continue Sequences (by Tag)", Category = "Playback")` — Triggers Continues in all the sequences matching the provided tag @param InTagHandle the tag to match @param bInExactMatch whether to only consider sequences that have the tag exactly @return the array of the Sequence Players with only valid entries that fired the continue
- L142 _public prototype_ `virtual void PauseSequence(UAvaSequence* InSequence) = 0;` — Pauses all players for a given sequence @param InSequence the sequence to pause
- L149 _public prototype_ `virtual void PauseSequencesByLabel(FName InSequenceLabel) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Pause Sequences (by Label)", Category = "Playback")` — Pauses all players for sequences that match the given label @param InSequenceLabel the label of the sequences to pause
- L156 _public prototype_ `virtual void PauseSequencesByLabels(const TArray<FName>& InSequenceLabels) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Pause Sequences (by Labels)", Category = "Playback")` — Pauses all players for sequences that match the given labels @param InSequenceLabels the array of sequence labels to pause (must be an active sequence playing)
- L164 _public prototype_ `virtual void PauseSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Pause Sequences (by Tag)", Category = "Playback")` — Pauses all players for sequences that match the provided tag @param InTagHandle the tag to match @param bInExactMatch whether to only consider sequences that match the tag exactly
- L170 _public prototype_ `virtual void StopSequence(UAvaSequence* InSequence) = 0;` — Stops all players for a given sequence @param InSequence the sequence to stop
- L177 _public prototype_ `virtual void StopSequencesByLabel(FName InSequenceLabel) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Stop Sequences (by Label)", Category = "Playback")` — Stops all players for sequences that match the given label @param InSequenceLabel the label of the sequences to stop
- L184 _public prototype_ `virtual void StopSequencesByLabels(const TArray<FName>& InSequenceLabels) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Stop Sequences (by Labels)", Category = "Playback")` — Stops all players for sequences that match the given labels @param InSequenceLabels the array of sequence labels to stop (must be an active sequence playing)
- L192 _public prototype_ `virtual void StopSequencesByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Stop Sequences (by Tag)", Category = "Playback")` — Stops all players for sequences that match the provided tag @param InTagHandle the tag to match @param bInExactMatch whether to only consider sequences that match the tag exactly
- L194 _public prototype_ `virtual void UpdateCameraCut(const UE::MovieScene::FOnCameraCutUpdatedParams& InCameraCutParams) = 0;`
- L196 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraCut, UObject* , bool ) virtual FOnCameraCut& GetOnCameraCut() = 0;`
- L199 _public prototype_ `virtual UObject* GetPlaybackContext() const = 0;`
- L201 _public prototype_ `virtual UObject* CreateDirectorInstance(IMovieScenePlayer& InPlayer, FMovieSceneSequenceID InSequenceID) = 0;`
- L203 _public prototype_ `virtual UAvaSequencePlayer* GetSequencePlayer(const UAvaSequence* InSequence) const = 0;`
- L206 _public prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayers(TConstArrayView<const UAvaSequence*> InSequences) const = 0;` — Retrieves the active sequence players for the given sequences, if any
- L209 _public prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByLabel(FName InSequenceLabel) const = 0;` — Retrieves the active sequence players for the given sequences that match the given label, if any
- L212 _public prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByLabels(const TArray<FName>& InSequenceLabels) const = 0;` — Retrieves the active sequence players for the given sequences that match the given labels, if any
- L215 _public prototype_ `virtual TArray<UAvaSequencePlayer*> GetSequencePlayersByTag(const FAvaTagHandle& InTagHandle, bool bInExactMatch) const = 0;` — Retrieves the active sequence players for the given sequences that match the given tag, if any
- L219 _public prototype_ `virtual TArray<UAvaSequencePlayer*> GetAllSequencePlayers() const = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Get Active Sequence Players", Category = "Playback")` — Retrieves all Active Sequence Players
- L223 _public prototype_ `virtual bool HasActiveSequencePlayers() const = 0;` — `UFUNCTION(BlueprintCallable, DisplayName = "Has Active Sequence Players", Category = "Playback")` — Returns true if there are any Active Sequence Players

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieScene` (scope `UE`)
- L196 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCameraCut, UObject* , bool ) virtual FOnCameraCut& GetOnCameraCut() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequencePlayer.h` (Public)


#### class `UAvaSequencePlayer`  
`class UAvaSequencePlayer : public ULevelSequencePlayer`  
_L19-95_
- reflection: `UCLASS(Transient, BlueprintType)`
- inherits: `ULevelSequencePlayer`
- L24 _public prototype_ `UAvaSequencePlayer(const FObjectInitializer& InObjectInitializer);`
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSequenceEvent, UAvaSequencePlayer*, UAvaSequence*);`
- L27 _public function_ `static FOnSequenceEvent& OnSequenceStarted()`
- L28 _public function_ `static FOnSequenceEvent& OnSequencePaused()`
- L29 _public function_ `static FOnSequenceEvent& OnSequenceFinished()`
- L31 _public prototype_ `void InitSequence(UAvaSequence* InSequence, IAvaSequencePlaybackObject* InPlaybackObject, ULevel* InLevel, const FLevelSequenceCameraSettings& InCameraSettings);`
- L33 _public prototype_ `UAvaSequence* GetAvaSequence() const;`
- L35 _public prototype_ `IAvaSequencePlaybackObject* GetPlaybackObject() const;`
- L37 _public function_ `TSharedPtr<IAvaSequenceController> GetSequenceController() const`
- L39 _public prototype_ `FQualifiedFrameTime GetGlobalTime() const;`
- L41 _public prototype_ `void SetPlaySettings(const FAvaSequencePlayParams& InPlaySettings);`
- L43 _public prototype_ `void PlaySequence();`
- L45 _public prototype_ `void ContinueSequence();`
- L48 _public prototype_ `void JumpTo(FFrameTime InJumpToFrame, bool bInEvaluate);` — Jump to the given Frame, in Tick Resolution space
- L54 _public prototype_ `FFrameRate GetTickResolution() const;`
- L56 _public prototype_ `void Cleanup();`
- L61 _protected prototype_ `virtual void OnStartedPlaying() override;`
- L62 _protected prototype_ `virtual void OnStopped() override;`
- L66 _protected prototype_ `virtual void TickFromSequenceTickManager(float InDeltaSeconds, FMovieSceneEntitySystemRunner* InRunner) override;`
- L70 _protected prototype_ `virtual void OnCameraCutUpdated(const UE::MovieScene::FOnCameraCutUpdatedParams& InCameraCutParams) override;`
- L74 _private prototype_ `FFrameTime CalculateDeltaFrameTime(float InDeltaSeconds) const;`
- L76 _private prototype_ `void NotifySequenceStarted();`
- L79 _private prototype_ `void NotifySequencePaused();` — `UFUNCTION()`
- L81 _private prototype_ `void NotifySequenceFinished();`
- L83 _private member_ `static FOnSequenceEvent OnSequenceStartedDelegate;`
- L84 _private member_ `static FOnSequenceEvent OnSequencePausedDelegate;`
- L85 _private member_ `static FOnSequenceEvent OnSequenceFinishedDelegate;`
- L90 _private member_ `TWeakInterfacePtr<IAvaSequencePlaybackObject> PlaybackObjectWeak;`
- L92 _private member_ `TSharedPtr<IAvaSequenceController> SequenceController;`
- L94 _private member_ `TWeakObjectPtr<ULevel> PlaybackLevelWeak;`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSequenceEvent, UAvaSequencePlayer*, UAvaSequence*);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequencePlayerVariant.h` (Public)


#### struct `TAvaSequencePlayerVariant`  
`template<typename... InPlayerTypes> struct TAvaSequencePlayerVariant`  
_L10-41_
- L13 _public function_ `template<typename InPlayerType UE_REQUIRES(TIsDerivedFrom<InPlayerType, IMovieScenePlayer>::Value)> TAvaSequencePlayerVariant(InPlayerType* InPlayer) : PlayerVariant(TInPlaceType<InPlayerType*>(), InPlayer)`
- L18 _public function_ `IMovieScenePlayer* Get() const`
- L24 _public function_ `template<typename InPlayerType> IMovieScenePlayer* operator()(InPlayerType* InPlayer) const`
- L30 _public function_ `template<typename InPlayerType> InPlayerType* TryGet() const`
- L40 _private member_ `TVariant<InPlayerTypes*...> PlayerVariant;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequenceShared.h` (Public)


#### enum `EAvaSequenceActionType`  
`enum class EAvaSequenceActionType : uint8`  
_L21-28_
- reflection: `UENUM()`
- desc: Enumeration of actions that can be performed on a sequence
- L23 _public enumerator_ `None UMETA(Hidden)`
- L24 _public enumerator_ `Play`
- L25 _public enumerator_ `Continue`
- L26 _public enumerator_ `Pause`
- L27 _public enumerator_ `Stop`

#### enum `EAvaSequencePlayMode`  
`enum class EAvaSequencePlayMode : uint8`  
_L31-38_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Sequence Play Mode")`
- L34 _public enumerator_ `Forward` — Sequence plays and loops from the beginning to the end.
- L37 _public enumerator_ `Reverse` — Sequence plays and loops from the end to the beginning.

#### enum `EAvaSequenceTimeType`  
`enum class EAvaSequenceTimeType : uint8`  
_L41-47_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Sequence Time Type")`
- L43 _public enumerator_ `None UMETA(Hidden)`
- L44 _public enumerator_ `Frame`
- L45 _public enumerator_ `Seconds`
- L46 _public enumerator_ `Mark`

#### struct `FAvaSequenceTime`  
`struct FAvaSequenceTime`  
_L50-119_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Sequence Time")`
- L56 _public prototype_ `FAvaSequenceTime() = default;`
- L58 _public function_ `explicit FAvaSequenceTime(ENoTimeConstraint) : bHasTimeConstraint(false)`
- L63 _public function_ `explicit FAvaSequenceTime(FFrameTime FrameTime) : TimeType(EAvaSequenceTimeType::Frame) , Frame(FrameTime.GetFrame().Value) , SubFrame(FrameTime.GetSubFrame()) , bHasTimeConstraint(true)`
- L71 _public function_ `explicit FAvaSequenceTime(double InSeconds) : TimeType(EAvaSequenceTimeType::Seconds) , Seconds(InSeconds) , bHasTimeConstraint(true)`
- L78 _public function_ `explicit FAvaSequenceTime(const FString& InMarkLabel) : TimeType(EAvaSequenceTimeType::Mark) , MarkLabel(InMarkLabel) , bHasTimeConstraint(true)`
- L86 _public function_ `bool IsAbsoluteTime() const` — Returns whether the provided Time is 'absolute' (i.e. should not be manipulated by whether it's playing forward/reversed) or not
- L91 _public prototype_ `bool Serialize(FArchive& Ar);`
- L100 _public prototype_ `double ToSeconds(const UAvaSequence& InSequence, const UMovieScene& InMovieScene, double InDefaultTime) const;` — Converts this Motion Design Sequence Time struct to time frame in seconds @param InSequence the sequence to use to query for marks (only applicable if TimeType is set to Mark) @param InMovieScene the movie scene used to get the Tick Resolution or Display Rate @param InDefaultTime the default time to return if time is invalid or unset @return the timeframe in seconds
- L103 _public member_ `EAvaSequenceTimeType TimeType = EAvaSequenceTimeType::Frame;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(EditCondition="bHasTimeConstraint"))`
- L106 _public member_ `int32 Frame = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(EditCondition="bHasTimeConstraint && TimeType==EAvaSequenceTimeType::Frame"))`
- L109 _public member_ `double SubFrame = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(EditCondition="bHasTimeConstraint && TimeType==EAvaSequenceTimeType::Frame"))`
- L112 _public member_ `double Seconds = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(EditCondition="bHasTimeConstraint && TimeType==EAvaSequenceTimeType::Seconds", Unit=s))`
- L115 _public member_ `FString MarkLabel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(EditCondition="bHasTimeConstraint && TimeType==EAvaSequenceTimeType::Mark"))`
- L118 _public member_ `bool bHasTimeConstraint = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`

#### enum `FAvaSequenceTime::ENoTimeConstraint`  
`enum ENoTimeConstraint`  
_L54-54_
- L54 _public enumerator_ `enum ENoTimeConstraint {NoTimeConstraint}; FAvaSequenceTime() = default; explicit FAvaSequenceTime(ENoTimeConstraint) : bHasTimeConstraint(false) { }`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAvaSequenceTime> : public TStructOpsTypeTraitsBase2<FAvaSequenceTime>`  
_L122-128_
- inherits: `TStructOpsTypeTraitsBase2<FAvaSequenceTime>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L125-127_

#### struct `FAvaSequencePlayAdvancedSettings`  
`struct FAvaSequencePlayAdvancedSettings`  
_L131-144_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Sequence Play Advanced Settings")`
- L137 _public member_ `int32 LoopCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")` — Number of times to loop playback. -1 for infinite, else the number of times to loop before stopping
- L140 _public member_ `float PlaybackSpeed = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`
- L143 _public member_ `bool bRestoreState = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`

#### struct `FAvaSequencePlayParams`  
`struct FAvaSequencePlayParams`  
_L147-162_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Sequence Play Parameters")`
- L152 _public member_ `FAvaSequenceTime Start = FAvaSequenceTime(0.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`
- L155 _public member_ `FAvaSequenceTime End = FAvaSequenceTime(FAvaSequenceTime::NoTimeConstraint);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`
- L158 _public member_ `EAvaSequencePlayMode PlayMode = EAvaSequencePlayMode::Forward;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`
- L161 _public member_ `FAvaSequencePlayAdvancedSettings AdvancedSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace AvaSequence` (scope `UE`)
- L16 _variable_ `constexpr double SmallSubFrame = 0.00000005;` (scope `UE::AvaSequence`)
- L126 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon7291e48d0103`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/AvaSequenceSubsystem.h` (Public)


#### class `UAvaSequenceSubsystem`  
`class UAvaSequenceSubsystem : public UWorldSubsystem`  
_L20-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L25 _public prototype_ `UAvaSequenceSubsystem() = default;`
- L27 _public prototype_ `static UAvaSequenceSubsystem* Get(UObject* InPlaybackContext);`
- L29 _public prototype_ `static TSharedRef<IAvaSequenceController> CreateSequenceController(UAvaSequence& InSequence, IAvaSequencePlaybackObject* InPlaybackObject);`
- L31 _public prototype_ `IAvaSequencePlaybackObject* FindOrCreatePlaybackObject(ULevel* InLevel, IAvaSequenceProvider& InSequenceProvider);`
- L33 _public prototype_ `IAvaSequencePlaybackObject* FindPlaybackObject(ULevel* InLevel) const;`
- L35 _public prototype_ `void AddPlaybackObject(IAvaSequencePlaybackObject* InPlaybackObject);`
- L36 _public prototype_ `void RemovePlaybackObject(IAvaSequencePlaybackObject* InPlaybackObject);`
- L38 _public prototype_ `IAvaSequenceProvider* FindSequenceProvider(const ULevel* InLevel) const;`
- L40 _public prototype_ `void RegisterSequenceProvider(const ULevel* InLevel, IAvaSequenceProvider* InSequenceProvider);`
- L41 _public prototype_ `bool UnregisterSequenceProvider(const ULevel* InLevel, IAvaSequenceProvider* InSequenceProvider);`
- L45 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L49 _private prototype_ `bool EnsureLevelIsAppropriate(ULevel*& InLevel) const;`
- L51 _private member_ `TArray<TWeakInterfacePtr<IAvaSequencePlaybackObject>> PlaybackObjects;`
- L53 _private member_ `TMap<TObjectKey<ULevel>, TWeakInterfacePtr<IAvaSequenceProvider>> SequenceProviders;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Director/AvaSequenceDirector.h` (Public)


#### class `UAvaSequenceDirector`  
`class UAvaSequenceDirector : public ULevelSequenceDirector`  
_L16-48_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `ULevelSequenceDirector`
- L23 _public prototype_ `void UpdateProperties();`
- L27 _protected prototype_ `virtual void PostLoad() override;`
- L28 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InDuplicateMode) override;`
- L32 _private prototype_ `void Initialize(IMovieScenePlayer& InPlayer, IAvaSequenceProvider* InSequenceProvider);`
- L35 _private prototype_ `void PlayScheduledSequences();` — `UFUNCTION(BlueprintCallable, Category = "Playback")`
- L38 _private prototype_ `void PlaySequencesByLabel(FName InSequenceLabel, FAvaSequencePlayParams InPlaySettings);` — `UFUNCTION(BlueprintCallable, Category = "Playback")`
- L41 _private prototype_ `TScriptInterface<IAvaSequencePlaybackObject> GetPlaybackObject() const;` — `UFUNCTION(BlueprintPure, Category = "Playback")`
- L43 _private prototype_ `void UpdatePlaybackObject();`
- L45 _private member_ `TWeakObjectPtr<UAvaSequencePlayer> SequencePlayerWeak;`
- L47 _private member_ `TWeakInterfacePtr<IAvaSequencePlaybackObject> PlaybackObjectInterfaceWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Director/AvaSequenceDirectorBlueprint.h` (Public)


#### class `UAvaSequenceDirectorBlueprint`  
`class UAvaSequenceDirectorBlueprint : public UBlueprint`  
_L12-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprint`
- L17 _public prototype_ `TConstArrayView<FAvaSequenceInfo> GetSequenceInfos();`
- L22 _protected prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L23 _protected prototype_ `virtual void GetReparentingRules(TSet<const UClass*>& OutAllowedChildrenOfClasses, TSet<const UClass*>& OutDisallowedChildrenOfClasses) const override;`
- L28 _private prototype_ `void UpdateSequenceInfos();`
- L31 _private member_ `TArray<FAvaSequenceInfo> SequenceInfos;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Director/AvaSequenceDirectorGeneratedClass.h` (Public)


#### class `UAvaSequenceDirectorGeneratedClass`  
`class UAvaSequenceDirectorGeneratedClass : public UBlueprintGeneratedClass`  
_L14-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- L19 _public prototype_ `void UpdateProperties(UAvaSequenceDirector* InDirector);`
- L22 _public member_ `TArray<FAvaSequenceInfo> SequenceInfos;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Director/AvaSequenceDirectorShared.h` (Public)


#### struct `FAvaSequenceInfo`  
`struct FAvaSequenceInfo`  
_L12-21_
- reflection: `USTRUCT()`
- L17 _public member_ `FName SequenceName;` — `UPROPERTY()`
- L20 _public member_ `TSoftObjectPtr<UAvaSequence> Sequence;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/IAvaSequenceController.h` (Public)


#### class `IAvaSequenceController`  
`class IAvaSequenceController`  
_L22-34_
- desc: Interface to processing how Marks are processed when ticking a sequence
- L25 _public prototype_ `virtual ~IAvaSequenceController() = default;`
- L27 _public prototype_ `virtual void SetTime(const FFrameTime& InNewTime, bool bInResetState) = 0;`
- L29 _public prototype_ `virtual void Tick(const FAvaSequencePlayerVariant& InPlayerVariant, const FFrameTime& InDeltaFrameTime, float InDeltaSeconds) = 0;`
- L31 _public prototype_ `virtual UAvaSequence* GetSequence() const = 0;`
- L33 _public prototype_ `virtual TSharedRef<IAvaSequencePlaybackContext> GetPlaybackContext() const = 0;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using FAvaSequencePlayerVariant = TAvaSequencePlayerVariant<UAvaSequencePlayer, ISequencer>;`
- L18 _typedef_ `using FAvaSequencePlayerVariant = TAvaSequencePlayerVariant<UAvaSequencePlayer>;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/IAvaSequencePlaybackContext.h` (Public)


#### class `IAvaSequencePlaybackContext`  
`class IAvaSequencePlaybackContext : public TSharedFromThis<IAvaSequencePlaybackContext>`  
_L14-46_
- inherits: `TSharedFromThis<IAvaSequencePlaybackContext>`
- desc: Interface for Marks to interact with the Sequence being played
- L17 _public prototype_ `virtual ~IAvaSequencePlaybackContext() = default;`
- L19 _public prototype_ `virtual FFrameTime GetGlobalTime() const = 0;`
- L21 _public prototype_ `virtual FFrameTime GetDeltaFrameTime() const = 0;`
- L23 _public prototype_ `virtual bool IsPlayingForwards() const = 0;`
- L25 _public prototype_ `virtual void Continue() = 0;`
- L27 _public prototype_ `virtual void Pause() = 0;`
- L29 _public prototype_ `virtual void Reverse() = 0;`
- L31 _public prototype_ `virtual void JumpTo(const FFrameTime& InFrameTime, bool bInEvaluateJumpedFrames) = 0;`
- L33 _public prototype_ `virtual void JumpToSelf() = 0;`
- L35 _public prototype_ `virtual const FAvaMark& GetMark() const = 0;`
- L37 _public prototype_ `virtual const TSet<FAvaMark>& GetAllMarks() const = 0;`
- L39 _public prototype_ `virtual const FMovieSceneMarkedFrame& GetMarkedFrame() const = 0;`
- L41 _public prototype_ `virtual FTSTicker& GetTicker() = 0;`
- L43 _public prototype_ `virtual TConstArrayView<TWeakPtr<IAvaSequencePlaybackContext>> GetChildrenInContext() const = 0;`
- L45 _public prototype_ `virtual void ResolveFromParent(const IAvaSequencePlaybackContext& InParent) = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/IAvaSequenceProvider.h` (Public)


#### class `UAvaSequenceProvider`  
`class UAvaSequenceProvider : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for Objects that use UAvaSequence and need to be handled by IAvaSequencer

#### class `IAvaSequenceProvider`  
`class IAvaSequenceProvider`  
_L30-119_
- L36 _public prototype_ `virtual FName GetSequenceProviderDebugName() const = 0;` — returns a debug name for the Sequence Provider
- L40 _public prototype_ `virtual void OnEditorSequencerCreated(const TSharedPtr<ISequencer>& InSequencer) = 0;` — Called after the ISequencer Instance has been created
- L42 _public prototype_ `virtual TSharedPtr<ISequencer> GetEditorSequencer() const = 0;`
- L45 _public prototype_ `virtual bool GetDirectorBlueprint(UAvaSequence& InSequence, UBlueprint*& OutBlueprint) = 0;` — Called to retrieve the Director Blueprint which should only be called in Editor Time
- L49 _public prototype_ `virtual UObject* ToUObject() = 0;` — Returns this as UObject Outer to use when handling Sequence Objects
- L51 _public prototype_ `virtual UWorld* GetContextWorld() const = 0;`
- L53 _public prototype_ `virtual bool CreateDirectorInstance(UAvaSequence& InSequence, IMovieScenePlayer& InPlayer, const FMovieSceneSequenceID& InSequenceID, UObject*& OutDirectorInstance) = 0;`
- L55 _public prototype_ `virtual bool AddSequence(UAvaSequence* InSequence) = 0;`
- L62 _public prototype_ `virtual uint32 AddSequences(TConstArrayView<UAvaSequence*> InSequences) = 0;` — Adds the given sequences to the sequence provider @param InSequences the sequences to add, if valid and not already in the list. @return the number of sequences that were successfully added.
- L64 _public prototype_ `virtual void RemoveSequence(UAvaSequence* InSequence) = 0;`
- L67 _public prototype_ `virtual void SetDefaultSequence(UAvaSequence* InSequence) = 0;` — Sets the Default Sequence to use when no particular sequence is active
- L70 _public prototype_ `virtual UAvaSequence* GetDefaultSequence() const = 0;` — Gets the Default Sequence to use when no particular sequence is active. May return null
- L72 _public prototype_ `virtual const TArray<TObjectPtr<UAvaSequence>>& GetSequences() const = 0;`
- L74 _public prototype_ `virtual const TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequences() const = 0;`
- L76 _public prototype_ `virtual TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequencesMutable() = 0;`
- L79 _public prototype_ `virtual FSimpleMulticastDelegate& GetOnSequenceTreeRebuilt() = 0;` — Delegate called when the Sequence Tree has been Rebuilt
- L82 _public prototype_ `virtual void ScheduleRebuildSequenceTree() = 0;` — Executes Rebuild Sequence Tree in a Deferred way rather than executing immediately
- L84 _public function_ `virtual void RebuildSequenceTree()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Marks/AvaMark.h` (Public)


#### struct `FAvaMark`  
`struct FAvaMark`  
_L14-80_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `FAvaMark() = default;`
- L19 _public prototype_ `FAvaMark(const FMovieSceneMarkedFrame& InMarkedFrame);`
- L20 _public prototype_ `FAvaMark(const FString& InLabel);`
- L21 _public prototype_ `explicit FAvaMark(const FStringView& InLabel);`
- L24 _public prototype_ `void CopyFromMark(const FAvaMark& InOther);` — Set all Values without changing its Label or Frames
- L26 _public function_ `bool operator==(const FAvaMark& Other) const`
- L31 _public function_ `FStringView GetLabel() const`
- L33 _public function_ `static const FName GetLabelPropertyName()`
- L45 _private member_ `FString Label;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design", meta=(NoResetToDefault, AllowPrivateAccess="true"))`
- L49 _public member_ `EAvaMarkDirection Direction = EAvaMarkDirection::Both;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks")`
- L52 _public member_ `EAvaMarkRole Role = EAvaMarkRole::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks")`
- L60 _public member_ `bool bIsLocalMark = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks")` — Whether Executing this Mark should affect the Local Sequence Set to True to only Execute Roles in the Owning Sequence Set to False to Affect Child Sequences of the Owning Sequence
- L63 _public member_ `bool bLimitPlayCountEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks")`
- L66 _public member_ `int32 LimitPlayCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks", meta = (EditCondition = "bLimitPlayCountEnabled"))`
- L69 _public member_ `float PauseTime = 3.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks", meta = (EditCondition = "Role==EAvaMarkRole::Pause", EditConditionHides))`
- L72 _public member_ `FString JumpLabel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks", meta = (EditCondition = "Role==EAvaMarkRole::Jump", EditConditionHides))`
- L75 _public member_ `EAvaMarkSearchDirection SearchDirection = EAvaMarkSearchDirection::All;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marks", meta = (EditCondition = "Role==EAvaMarkRole::Jump", EditConditionHides))`
- L79 _public member_ `TArray<int32> Frames;` — `UPROPERTY(Transient)` — The Frames where the Marked Frames with the same Label are at

#### Free symbols / members of external scopes

- L38 _function_ `friend uint32 GetTypeHash(const FAvaMark& InMark)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Marks/AvaMarkRole.h` (Public)


#### class `FAvaMarkRole`  
`class FAvaMarkRole : public TSharedFromThis<FAvaMarkRole>`  
_L19-36_
- inherits: `TSharedFromThis<FAvaMarkRole>`
- desc: Class involved in executing specific role-related logic via its Context
- L24 _public prototype_ `FAvaMarkRole() = default;`
- L26 _public function_ `virtual ~FAvaMarkRole()`
- L28 _public prototype_ `virtual EAvaMarkRole GetRole() const = 0;`
- L30 _public prototype_ `virtual EAvaMarkRoleReply Execute() = 0;`
- L32 _public function_ `virtual void Reset()`
- L35 _protected member_ `TSharedPtr<IAvaSequencePlaybackContext> Context;`

#### class `FAvaMarkInstance`  
`class FAvaMarkInstance`  
_L39-99_
- desc: Class Containing Instance data of a Mark, such as current Play Count
- L42 _public prototype_ `FAvaMarkInstance() = default;`
- L44 _public function_ `FAvaMarkInstance(const FAvaMark& InMark, const FFrameNumber& InFrame) : Label(InMark.GetLabel()) , Frame(InFrame) , MaxPlayCounts(InMark.LimitPlayCount) , bPlayCountEnabled(InMark.bLimitPlayCountEnabled)`
- L52 _public function_ `FAvaMarkInstance(const TSharedPtr<IAvaSequencePlaybackContext>& InContext) : FAvaMarkInstance(InContext->GetMark(), InContext->GetMarkedFrame().FrameNumber)`
- L62 _public function_ `bool operator==(const FAvaMarkInstance& Other) const`
- L67 _public function_ `void IncreasePlayCount()`
- L75 _public function_ `bool CanExecuteMark() const`
- L86 _private member_ `FString Label;` — Label of the Mark
- L89 _private member_ `FFrameNumber Frame;` — Frame that this Mark Instance is at
- L92 _private member_ `int32 PlayCounts = 0;` — Number of current Play Counts
- L95 _private member_ `int32 MaxPlayCounts = 0;` — Max number of Play Counts allowed, if bPlayCountEnabled is true
- L98 _private member_ `bool bPlayCountEnabled = false;` — Determines if there if Play Count should be considered when determining if Role can be executed

#### class `FAvaMarkRoleHandler`  
`class FAvaMarkRoleHandler`  
_L101-193_
- L105 _public function_ `template<typename InMarkRoleType, typename = typename TEnableIf<TIsDerivedFrom<InMarkRoleType, FAvaMarkRole>::IsDerived>::Type> void RegisterRole()`
- L111 _public function_ `bool IsMarkValid(const FAvaMark& InMark, const FFrameNumber& InFrame, EPlayDirection InPlayDirection) const`
- L149 _public function_ `EAvaMarkRoleReply ExecuteRole(const TSharedPtr<IAvaSequencePlaybackContext>& InContext)`
- L177 _public function_ `void ResetMarkStates()`
- L190 _private member_ `TMap<EAvaMarkRole, TSharedPtr<FAvaMarkRole>> MarkRoles;`
- L192 _private member_ `TSet<FAvaMarkInstance> MarkInstances;`

#### Free symbols / members of external scopes

- L57 _function_ `friend uint32 GetTypeHash(const FAvaMarkInstance& Instance)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Marks/AvaMarkShared.h` (Public)


#### enum `EAvaMarkRole`  
`enum class EAvaMarkRole : uint8`  
_L9-25_
- reflection: `UENUM()`
- L12 _public enumerator_ `None UMETA(DisplayName="Mark")` — Mark: Does nothing. Used for frame referencing
- L15 _public enumerator_ `Stop` — Stop Point: Waits for 'Continue' input before resuming playback
- L18 _public enumerator_ `Pause` — Pause Point: Waits a set amount of time before resuming playback
- L21 _public enumerator_ `Jump` — Jump Point: Jumps to the nearest Marked Frame with the given Label, or continues playback if it doesn't exist
- L24 _public enumerator_ `Reverse` — Reverse Point: Reverses the Playback Direction

#### enum `EAvaMarkDirection`  
`enum class EAvaMarkDirection : uint8`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `Both`
- L31 _public enumerator_ `Forwards`
- L32 _public enumerator_ `Backwards`

#### enum `EAvaMarkSearchDirection`  
`enum class EAvaMarkSearchDirection : uint8`  
_L36-52_
- reflection: `UENUM()`
- L39 _public enumerator_ `All` — Search All Directions
- L42 _public enumerator_ `SameDirection` — Search in the Same Direction of Playback
- L45 _public enumerator_ `OppositeDirection` — Search Opposite in the opposite Direction of Playback (what causes Loops)
- L48 _public enumerator_ `AbsoluteForwards` — Forwards Fixed Direction, regardless of Playback Direction
- L51 _public enumerator_ `AbsoluteBackwards` — Backwards Fixed Direction, regardless of Playback Direction

#### enum `EAvaMarkRoleReply`  
`enum class EAvaMarkRoleReply : uint8`  
_L54-58_
- L56 _public enumerator_ `NotExecuted = 0`
- L57 _public enumerator_ `Executed = 1 << 0`

#### Free symbols / members of external scopes

- L59 _prototype_ `ENUM_CLASS_FLAGS(EAvaMarkRoleReply);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionContinueSequenceTask.h` (Public)


#### struct `FAvaTransitionContinueSequenceTask`  
`struct FAvaTransitionContinueSequenceTask : public FAvaTransitionSequenceTask`  
_L9-22_
- reflection: `USTRUCT(DisplayName = "Continue Sequence", Category="Sequence Playback")`
- inherits: `FAvaTransitionSequenceTask`
- L15 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L20 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ExecuteSequenceTask(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionInitializeSequence.h` (Public)


#### struct `FAvaTransitionInitSequenceTaskInstanceData`  
`struct FAvaTransitionInitSequenceTaskInstanceData : public FAvaTransitionSequenceTaskBaseInstanceData`  
_L10-19_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionSequenceTaskBaseInstanceData`
- L15 _public member_ `FAvaSequenceTime InitializeTime = FAvaSequenceTime(0.0);` — `UPROPERTY(EditAnywhere, Category = "Parameter")`
- L18 _public member_ `EAvaSequencePlayMode PlayMode = EAvaSequencePlayMode::Forward;` — `UPROPERTY(EditAnywhere, Category = "Parameter")`

#### struct `FAvaTransitionInitializeSequence`  
`struct FAvaTransitionInitializeSequence : public FAvaTransitionSequenceTaskBase`  
_L22-36_
- reflection: `USTRUCT(DisplayName = "Initialize Sequence", Category = "Sequence Playback")`
- inherits: `FAvaTransitionSequenceTaskBase`
- L26 _public typedef_ `using FInstanceDataType = FAvaTransitionInitSequenceTaskInstanceData;`
- L29 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L33 _public prototype_ `virtual EAvaTransitionSequenceWaitType GetWaitType(FStateTreeExecutionContext& InContext) const override;`
- L34 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ExecuteSequenceTask(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionPlaySequenceTask.h` (Public)


#### struct `FAvaTransitionPlaySequenceTaskInstanceData`  
`struct FAvaTransitionPlaySequenceTaskInstanceData : public FAvaTransitionSequenceTaskInstanceData`  
_L10-17_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionSequenceTaskInstanceData`
- L16 _public member_ `FAvaSequencePlayParams PlaySettings;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — Sequence Play Settings

#### struct `FAvaTransitionPlaySequenceTask`  
`struct FAvaTransitionPlaySequenceTask : public FAvaTransitionSequenceTask`  
_L20-36_
- reflection: `USTRUCT(DisplayName = "Play Sequence", Category="Sequence Playback")`
- inherits: `FAvaTransitionSequenceTask`
- L24 _public typedef_ `using FInstanceDataType = FAvaTransitionPlaySequenceTaskInstanceData;`
- L27 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L29 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L34 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ExecuteSequenceTask(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionSequenceEnums.h` (Public)


#### enum `EAvaTransitionSequenceWaitType`  
`enum class EAvaTransitionSequenceWaitType : uint8`  
_L8-17_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Sequence Wait Type")`
- L10 _public enumerator_ `None UMETA(Hidden)`
- L13 _public enumerator_ `NoWait` — Fire and Forget
- L16 _public enumerator_ `WaitUntilStop` — Wait until the Sequence stops midway or finishes to complete

#### enum `EAvaTransitionSequenceQueryType`  
`enum class EAvaTransitionSequenceQueryType : uint8`  
_L20-29_
- reflection: `UENUM(BlueprintType, DisplayName="Motion Design Sequence Query Type")`
- L22 _public enumerator_ `None UMETA(Hidden)`
- L25 _public enumerator_ `Name` — Identify the Sequence by its Name
- L28 _public enumerator_ `Tag` — Identify the Sequence by its Tag

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionSequenceTask.h` (Public)


#### struct `FAvaTransitionSequenceTaskInstanceData`  
`struct FAvaTransitionSequenceTaskInstanceData : public FAvaTransitionSequenceTaskBaseInstanceData`  
_L9-16_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionSequenceTaskBaseInstanceData`
- L15 _public member_ `EAvaTransitionSequenceWaitType WaitType = EAvaTransitionSequenceWaitType::WaitUntilStop;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — The wait type before this task completes

#### struct `FAvaTransitionSequenceTask`  
`struct FAvaTransitionSequenceTask : public FAvaTransitionSequenceTaskBase`  
_L20-33_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FAvaTransitionSequenceTaskBase`
- desc: Base Task but with additional Parameters
- L24 _public typedef_ `using FInstanceDataType = FAvaTransitionSequenceTaskInstanceData;`
- L27 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L31 _public prototype_ `virtual EAvaTransitionSequenceWaitType GetWaitType(FStateTreeExecutionContext& InContext) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionSequenceTaskBase.h` (Public)


#### struct `FAvaTransitionSequenceInstanceData`  
`struct FAvaTransitionSequenceInstanceData`  
_L18-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TArray<TWeakObjectPtr<UAvaSequence>> ActiveSequences;` — `UPROPERTY()` — Sequences being played

#### struct `FAvaTransitionSequenceTaskBaseInstanceData`  
`struct FAvaTransitionSequenceTaskBaseInstanceData : public FAvaTransitionSequenceInstanceData`  
_L28-43_
- reflection: `USTRUCT()`
- inherits: `FAvaTransitionSequenceInstanceData`
- L33 _public member_ `EAvaTransitionSequenceQueryType QueryType = EAvaTransitionSequenceQueryType::Name;` — `UPROPERTY(EditAnywhere, Category="Parameter", DisplayName="Sequence Query Type", meta=(DisplayPriority=1))`
- L36 _public member_ `FAvaSequenceName SequenceName;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(DisplayPriority=1, EditCondition="QueryType==EAvaTransitionSequenceQueryType::Name", EditConditionHides))`
- L39 _public member_ `FAvaTagHandle SequenceTag;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(DisplayPriority=1, EditCondition="QueryType==EAvaTransitionSequenceQueryType::Tag", EditConditionHides))`
- L42 _public member_ `bool bPerformExactMatch = false;` — `UPROPERTY()`

#### struct `FAvaTransitionSequenceTaskBase`  
`struct FAvaTransitionSequenceTaskBase : public FAvaTransitionTask`  
_L46-101_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FAvaTransitionTask`
- L50 _public typedef_ `using FInstanceDataType = FAvaTransitionSequenceTaskBaseInstanceData;`
- L56 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ExecuteSequenceTask(FStateTreeExecutionContext& InContext) const;` — Execute the Sequence Task (overriden by implementation) @return the sequence players that are relevant to the task
- L59 _public function_ `virtual EAvaTransitionSequenceWaitType GetWaitType(FStateTreeExecutionContext& InContext) const` — Gets the Wait Type to use when Waiting for Active Sequences
- L65 _public prototype_ `bool IsSequenceQueryValid(const FInstanceDataType& InInstanceData) const;` — Determines whether the Current Sequence information is valid for query
- L68 _public prototype_ `IAvaSequencePlaybackObject* GetPlaybackObject(FStateTreeExecutionContext& InContext) const;` — Attempts to Retrieve the Playback Object from the given Execution Context
- L71 _public prototype_ `TArray<TWeakObjectPtr<UAvaSequence>> GetActiveSequences(TConstArrayView<UAvaSequencePlayer*> InSequencePlayers) const;` — Gets all the Sequences from the provided Sequence Players that are Active (playing)
- L79 _public prototype_ `EStateTreeRunStatus WaitForActiveSequences(FStateTreeExecutionContext& InContext) const;` — Helper function to determine the Tree Run Status by updating and checking if all activated Sequence Players are in a state that match the Wait Type @param InContext the execution context where the Instance Data of the Active Sequences is retrieved @return the suggested tree run status
- L85 _public prototype_ `void StopActiveSequences(FStateTreeExecutionContext& InContext) const;` — Helper function to stop all the currently active sequences @param InContext the execution context where the Instance Data of the Active Sequences is retrieved
- L87 _public prototype_ `FText GetSequenceQueryText(const FInstanceDataType& InInstanceData, EStateTreeNodeFormatting InFormatting) const;`
- L90 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L91 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& InContext, const float InDeltaTime) const override;`
- L92 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L96 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L97 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L100 _public member_ `TStateTreeExternalDataHandle<UAvaSequenceSubsystem> SequenceSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionSequenceUtils.h` (Public)


#### struct `FAvaTransitionSequenceUtils`  
`struct FAvaTransitionSequenceUtils`  
_L17-30_
- L20 _public prototype_ `static IAvaSequencePlaybackObject* GetPlaybackObject(const FAvaTransitionContext& InTransitionContext , const UAvaSequenceSubsystem& InSequenceSubsystem);` — Attempts to Retrieve the Playback Object from the given Execution Context
- L24 _public prototype_ `static EStateTreeRunStatus UpdatePlayerRunStatus(const IAvaSequencePlaybackObject& InPlaybackObject , TArray<TWeakObjectPtr<UAvaSequence>>& InOutSequences , EAvaTransitionSequenceWaitType InWaitType);` — Retrieves the Player Run Status and Updates the Sequence Array for a given Wait Type
- L29 _public prototype_ `static TArray<TWeakObjectPtr<UAvaSequence>> GetSequences(TConstArrayView<UAvaSequencePlayer*> InSequencePlayers);` — Retrieves an array of Weak Sequences based on a list of Sequence Players

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionWaitForAllSequencesTask.h` (Public)


#### struct `FAvaTransitionWaitForAllSequencesTask`  
`struct FAvaTransitionWaitForAllSequencesTask : public FAvaTransitionTask`  
_L10-31_
- reflection: `USTRUCT(DisplayName = "Wait for all Sequences", Category="Sequence Playback")`
- inherits: `FAvaTransitionTask`
- L14 _public typedef_ `using FInstanceDataType = FAvaTransitionSequenceInstanceData;`
- L17 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`
- L18 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& InContext, const float InDeltaTime) const override;`
- L22 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L23 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L26 _public prototype_ `IAvaSequencePlaybackObject* GetPlaybackObject(FStateTreeExecutionContext& InContext) const;`
- L28 _public prototype_ `EStateTreeRunStatus WaitForAllSequences(FStateTreeExecutionContext& InContext) const;`
- L30 _public member_ `TStateTreeExternalDataHandle<UAvaSequenceSubsystem> SequenceSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSequence/Public/Transition/AvaTransitionWaitForSequenceTask.h` (Public)


#### struct `FAvaTransitionWaitForSequenceTask`  
`struct FAvaTransitionWaitForSequenceTask : public FAvaTransitionSequenceTask`  
_L9-22_
- reflection: `USTRUCT(DisplayName = "Wait for Sequence", Category="Sequence Playback")`
- inherits: `FAvaTransitionSequenceTask`
- L15 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L20 _public prototype_ `virtual TArray<UAvaSequencePlayer*> ExecuteSequenceTask(FStateTreeExecutionContext& InContext) const override;`
