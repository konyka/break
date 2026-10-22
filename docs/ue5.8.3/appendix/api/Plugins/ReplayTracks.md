# Plugins / ReplayTracks

- module root: `Plugins/MovieScene/ReplayTracks/Source/ReplayTracks`
- headers: 4; symbols: 83
- symbol kinds: class=5, enum=1, enumerator=3, function=14, member=19, namespace=2, prototype=35, struct=4
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTracks, TimeManagement

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracks/Private/Systems/MovieSceneReplaySystem.h` (Private)


#### struct `UE::MovieScene::FReplayComponentData`  
`struct FReplayComponentData`  
_L24-30_
- L26 _public function_ `FReplayComponentData() : Section(nullptr)`
- L27 _public function_ `FReplayComponentData(const UMovieSceneReplaySection* InSection) : Section(InSection)`
- L29 _public member_ `const UMovieSceneReplaySection* Section = nullptr;`

#### struct `UE::MovieScene::FReplayComponentTypes`  
`struct FReplayComponentTypes`  
_L32-41_
- L35 _public prototype_ `static FReplayComponentTypes* Get();`
- L37 _public member_ `TComponentTypeID<FReplayComponentData> Replay;`
- L40 _private prototype_ `FReplayComponentTypes();`

#### class `UMovieSceneReplaySystem`  
`class UMovieSceneReplaySystem : public UMovieSceneEntitySystem`  
_L47-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L52 _public prototype_ `UMovieSceneReplaySystem(const FObjectInitializer& ObjInit);`
- L55 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L57 _private prototype_ `void OnRunInstantiation();`
- L58 _private prototype_ `void OnRunEvaluation();`
- L69 _private function_ `friend bool operator==(const FReplayInfo& A, const FReplayInfo& B)`
- L73 _private function_ `friend bool operator!=(const FReplayInfo& A, const FReplayInfo& B)`
- L79 _private prototype_ `void StartReplay(const FReplayInfo& ReplayInfo);`
- L80 _private prototype_ `void StopReplay(const FReplayInfo& ReplayInfo);`
- L84 _private member_ `TArray<FReplayInfo> CurrentReplayInfos;`
- L85 _private member_ `bool bReplayActive = false;`
- L86 _private member_ `bool bNeedsInit = true;`
- L88 _private member_ `EMovieScenePlayerStatus::Type PreviousPlayerStatus = EMovieScenePlayerStatus::Stopped;`
- L90 _private member_ `IConsoleVariable* ShowFlagMotionBlur = nullptr;`
- L97 _private prototype_ `static void OnPreLoadMap(const FString& MapName, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState);` — Handlers for replay events. These are all static because they happen across level reloads, which mean that the current object may have been wiped out and re-created, so we can't rely on any instance data.
- L98 _private prototype_ `static void OnPostLoadMap(UWorld* World, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, FMovieSceneContext LastContext);`
- L99 _private prototype_ `static void OnEndPlayMap();`
- L101 _private member_ `static FDelegateHandle PreLoadMapHandle;`
- L102 _private member_ `static FDelegateHandle PostLoadMapHandle;`
- L103 _private member_ `static FDelegateHandle EndPlayMapHandle;`
- L104 _private member_ `static FTimerHandle ReEvaluateHandle;`

#### struct `UMovieSceneReplaySystem::FReplayInfo`  
`struct FReplayInfo`  
_L62-77_
- L64 _public member_ `const UMovieSceneReplaySection* Section = nullptr;`
- L65 _public member_ `UE::MovieScene::FInstanceHandle InstanceHandle;`
- L67 _public prototype_ `bool IsValid() const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracks/Public/MovieSceneReplayManager.h` (Public)


#### class `FMovieSceneReplayBroker`  
`class FMovieSceneReplayBroker`  
_L14-29_
- desc: Base class for providing game-specific functionality required for managing replay.
- L17 _public function_ `virtual ~FMovieSceneReplayBroker()`
- L19 _public function_ `virtual bool SupportsWorld(const UWorld* InWorld) const`
- L21 _public function_ `virtual bool CanStartReplay(const UWorld* InWorld) const`
- L22 _public function_ `virtual void OnReplayStarted(UWorld* InWorld)`
- L24 _public function_ `virtual void OnGoToTime(UWorld* InWorld, float TimeInSeconds)`
- L25 _public function_ `virtual void OnReplayPlay(UWorld* InWorld)`
- L26 _public function_ `virtual void OnReplayPause(UWorld* InWorld)`
- L28 _public function_ `virtual void OnReplayStopped(UWorld* InWorld)`

#### struct `FMovieSceneReplayBrokerHandle`  
`struct FMovieSceneReplayBrokerHandle`  
_L34-37_
- desc: Handle for a registered replay broker.
- L36 _public member_ `int32 Value = INDEX_NONE;`

#### enum `EMovieSceneReplayStatus`  
`enum class EMovieSceneReplayStatus`  
_L42-47_
- desc: Current status of the replay, as managed by the replay manager.
- L44 _public enumerator_ `Stopped`
- L45 _public enumerator_ `Loading`
- L46 _public enumerator_ `Playing`

#### class `FMovieSceneReplayManager`  
`class FMovieSceneReplayManager`  
_L52-93_
- desc: Utility class for managing replay and replay brokers.
- L56 _public prototype_ `static FMovieSceneReplayManager& Get();` — Gets the global replay manager.
- L59 _public prototype_ `bool IsReplayArmed() const;` — Returns whether replay is armed.
- L61 _public prototype_ `void ArmReplay();` — Arms replay, i.e. indicates that it's ready to start.
- L63 _public prototype_ `void DisarmReplay();` — Disarms replay, i.e. indicates that it's not ready anymore, or should be stopped if currently playing.
- L66 _public function_ `EMovieSceneReplayStatus GetReplayStatus() const` — Gets the current replay status.
- L70 _public function_ `template<typename BrokerClass, typename... Args> FMovieSceneReplayBrokerHandle RegisterBroker(Args&&... ArgList)` — Registers a new broker.
- L77 _public prototype_ `bool UnregisterBroker(FMovieSceneReplayBrokerHandle InHandle);` — Unregisters an existing broker.
- L80 _public prototype_ `FMovieSceneReplayBroker* FindBroker(const UWorld* InWorld) const;` — Finds the broker appropriate for a given world.
- L83 _private prototype_ `FMovieSceneReplayManager();`
- L84 _private prototype_ `FMovieSceneReplayManager(const FMovieSceneReplayManager&) = delete;`
- L85 _private prototype_ `FMovieSceneReplayManager& operator=(const FMovieSceneReplayManager& In) = delete;`
- L87 _private member_ `bool bIsReplayArmed = false;`
- L88 _private member_ `EMovieSceneReplayStatus ReplayStatus = EMovieSceneReplayStatus::Stopped;`
- L90 _private member_ `TArray<TInlineValue<FMovieSceneReplayBroker>, TInlineAllocator<4>> Brokers;`

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracks/Public/Sections/MovieSceneReplaySection.h` (Public)


#### class `UMovieSceneReplaySection`  
`class UMovieSceneReplaySection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L13-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L21 _public prototype_ `UMovieSceneReplaySection(const FObjectInitializer& ObjInitializer);`
- L25 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L31 _public member_ `FString ReplayName;` — `UPROPERTY(EditAnywhere, Category="Replay")` — The name of the replay to run

### `Plugins/MovieScene/ReplayTracks/Source/ReplayTracks/Public/Tracks/MovieSceneReplayTrack.h` (Public)


#### class `UMovieSceneReplayTrack`  
`class UMovieSceneReplayTrack : public UMovieSceneTrack`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneTrack`
- L20 _public prototype_ `UMovieSceneReplayTrack(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `UMovieSceneReplaySection* AddNewReplaySection(FFrameNumber KeyTime);`
- L25 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — UMovieSceneTrack interface
- L26 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L27 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L28 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L29 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L30 _public prototype_ `virtual bool IsEmpty() const override;`
- L31 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L32 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L33 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L36 _public prototype_ `virtual FText GetDisplayName() const override;`
- L41 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`
