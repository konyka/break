# Runtime / MovieSceneTracks

- module root: `Source/Runtime/MovieSceneTracks`
- headers: 196; symbols: 3747
- symbol kinds: class=189, delegate=8, enum=37, enumerator=93, function=496, macro=9, member=989, namespace=102, prototype=1493, struct=233, typedef=97, variable=1
- PrivateDependencyModuleNames: AnimGraphRuntime, AnimationBlueprintLibrary, DataLayerEditor, EditorFramework, PropertyPath, UnrealEd
- PublicDependencyModuleNames: AnimationCore, AudioMixer, BlueprintGraph, Constraints, Core, CoreUObject, Engine, MovieScene, SlateCore, TimeManagement

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieScene3DPathTemplate.h` (Private)


#### struct `FMovieScene3DPathSectionTemplate`  
`struct FMovieScene3DPathSectionTemplate : public FMovieSceneEvalTemplate`  
_L15-60_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L19 _public function_ `FMovieScene3DPathSectionTemplate() : FrontAxisEnum(MovieScene3DPathSection_Axis::X) , UpAxisEnum(MovieScene3DPathSection_Axis::X) , bFollow(false) , bReverse(false) , bForceUpright(false)`
- L26 _public prototype_ `FMovieScene3DPathSectionTemplate(const UMovieScene3DPathSection& Section);`
- L30 _public member_ `FMovieSceneObjectBindingID PathBindingID;` — `UPROPERTY()` — The object binding ID of the path we should attach to
- L34 _public member_ `FMovieSceneFloatChannel TimingCurve;` — `UPROPERTY()` — The timing curve
- L38 _public member_ `MovieScene3DPathSection_Axis FrontAxisEnum;` — `UPROPERTY()` — Front Axis
- L42 _public member_ `MovieScene3DPathSection_Axis UpAxisEnum;` — `UPROPERTY()` — Up Axis
- L46 _public member_ `uint32 bFollow:1;` — `UPROPERTY()` — Follow Curve
- L50 _public member_ `uint32 bReverse:1;` — `UPROPERTY()` — Reverse Timing
- L54 _public member_ `uint32 bForceUpright:1;` — `UPROPERTY()` — Force Upright
- L58 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L59 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieSceneEventTemplate.h` (Private)


#### struct `FMovieSceneEventSectionTemplate`  
`struct FMovieSceneEventSectionTemplate : public FMovieSceneEvalTemplate`  
_L19-39_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L23 _public function_ `FMovieSceneEventSectionTemplate() : bFireEventsWhenForwards(false), bFireEventsWhenBackwards(false)`
- L24 _public prototype_ `FMovieSceneEventSectionTemplate(const UMovieSceneEventSection& Section, const UMovieSceneEventTrack& Track);`
- L27 _public member_ `FMovieSceneEventSectionData EventData;` — `UPROPERTY()`
- L30 _public member_ `uint32 bFireEventsWhenForwards : 1;` — `UPROPERTY()`
- L33 _public member_ `uint32 bFireEventsWhenBackwards : 1;` — `UPROPERTY()`
- L37 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L38 _private prototype_ `virtual void EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieSceneParticleParameterTemplate.h` (Private)


#### struct `FMovieSceneParticleParameterSectionTemplate`  
`struct FMovieSceneParticleParameterSectionTemplate : public FMovieSceneParameterSectionTemplate`  
_L13-24_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneParameterSectionTemplate`
- L17 _public function_ `FMovieSceneParticleParameterSectionTemplate()`
- L18 _public prototype_ `FMovieSceneParticleParameterSectionTemplate(const UMovieSceneParameterSection& Section, const UMovieSceneParticleParameterTrack& Track);`
- L22 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L23 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieSceneParticleTemplate.h` (Private)


#### struct `FMovieSceneParticleSectionTemplate`  
`struct FMovieSceneParticleSectionTemplate : public FMovieSceneEvalTemplate`  
_L15-29_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- L19 _public function_ `FMovieSceneParticleSectionTemplate()`
- L20 _public prototype_ `FMovieSceneParticleSectionTemplate(const UMovieSceneParticleSection& Section);`
- L23 _public member_ `FMovieSceneParticleChannel ParticleKeys;` — `UPROPERTY()`
- L27 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L28 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieScenePropertyTemplates.h` (Private)


#### struct `FMovieSceneBoolPropertySectionTemplate`  
`struct FMovieSceneBoolPropertySectionTemplate : public FMovieScenePropertySectionTemplate`  
_L28-43_
- reflection: `USTRUCT()`
- inherits: `FMovieScenePropertySectionTemplate`
- L32 _public function_ `FMovieSceneBoolPropertySectionTemplate()`
- L33 _public prototype_ `FMovieSceneBoolPropertySectionTemplate(const UMovieSceneBoolSection& Section, const UMovieScenePropertyTrack& Track);`
- L37 _protected function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L38 _protected function_ `virtual void SetupOverrides() override`
- L39 _protected prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L42 _protected member_ `FMovieSceneBoolChannel BoolCurve;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Private/Evaluation/MovieSceneTemplateCommon.h` (Private)


#### struct `FMobilityTokenProducer`  
`struct FMobilityTokenProducer : IMovieScenePreAnimatedTokenProducer`  
_L11-17_
- inherits: `IMovieScenePreAnimatedTokenProducer`
- L13 _public prototype_ `static FMovieSceneAnimTypeID GetAnimTypeID();`
- L16 _private prototype_ `virtual IMovieScenePreAnimatedTokenPtr CacheExistingState(UObject& Object) const override;`

#### struct `F3DTransformTrackToken`  
`struct F3DTransformTrackToken`  
_L20-36_
- desc: A token that sets a component's relative transform
- L22 _public function_ `F3DTransformTrackToken() : Translation(FVector::ZeroVector), Rotation(FRotator::ZeroRotator), Scale(FVector::OneVector)`
- L26 _public function_ `F3DTransformTrackToken(FVector InTranslation, FRotator InRotation, FVector InScale) : Translation(InTranslation), Rotation(InRotation), Scale(InScale)`
- L31 _public member_ `FVector Translation;`
- L32 _public member_ `FRotator Rotation;`
- L33 _public member_ `FVector Scale;`
- L35 _public prototype_ `void Apply(USceneComponent& SceneComponent) const;`

#### struct `F3DTransformTokenProducer`  
`struct F3DTransformTokenProducer : IMovieScenePreAnimatedTokenProducer`  
_L38-44_
- inherits: `IMovieScenePreAnimatedTokenProducer`
- L40 _public prototype_ `static FMovieSceneAnimTypeID GetAnimTypeID();`
- L43 _private prototype_ `virtual IMovieScenePreAnimatedTokenPtr CacheExistingState(UObject& Object) const override;`

### `Source/Runtime/MovieSceneTracks/Private/MovieSceneTracksCustomAccessors.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieScene` (scope `UE`)
- L16 _prototype_ `void InitializeMovieSceneTracksAccessors(FMovieSceneTracksComponentTypes* TracksComponents);` (scope `UE::MovieScene`)
- L18 _prototype_ `FIntermediate3DTransform GetComponentTransform(const UObject* Object);` (scope `UE::MovieScene`)
- L19 _prototype_ `void SetComponentTranslationAndRotation(USceneComponent* SceneComponent, const FIntermediate3DTransform& Transform);` (scope `UE::MovieScene`)
- L20 _prototype_ `void SetComponentTransform(USceneComponent* SceneComponent, const FIntermediate3DTransform& Transform);` (scope `UE::MovieScene`)
- L21 _prototype_ `void SetComponentTransformAndVelocity(UObject* Object, const FIntermediate3DTransform& InTransform);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Private/Systems/MovieSceneAudioSystem.h` (Private)


#### struct `UE::MovieScene::FAudioComponentInputEvaluationData`  
`struct FAudioComponentInputEvaluationData`  
_L30-37_
- L32 _public member_ `TMap<FName, float> Inputs_Float;`
- L33 _public member_ `TMap<FName, FString> Inputs_String;`
- L34 _public member_ `TMap<FName, bool> Inputs_Bool;`
- L35 _public member_ `TMap<FName, int32> Inputs_Int;`
- L36 _public member_ `TArray<FName> Inputs_Trigger;`

#### struct `UE::MovieScene::FAudioComponentEvaluationData`  
`struct FAudioComponentEvaluationData`  
_L39-83_
- L42 _public member_ `TWeakObjectPtr<UAudioComponent> AudioComponent;` — The audio component that was created to play audio
- L45 _public member_ `TWeakObjectPtr<UMovieSceneAudioSection> OwningSection;` — The audio section that currently owns this entry. Stamped when the entry is created or stolen so the reuse loop can ask the section directly (e.g. PUF state).
- L48 _public member_ `TObjectPtr<UMovieSceneSection> AudioComponentLifespanControlSection = nullptr;` — The movie section managing the lifespan of the audio component
- L54 _public member_ `EMovieScenePlayerStatus::Type LastSeenStatus = EMovieScenePlayerStatus::Stopped;` — Last player status seen during UpdatePreAnimatedStorage. Drives invalidation of AudioComponentLifespanControlSection on Scrubbing transitions so re-tracking picks up the new effective bWantsRestoreState.
- L58 _public member_ `TObjectPtr<UScrubbedSound> ScrubbedSound;` — While in editor, we can scrub the audio in the audio component.
- L62 _public member_ `double VolumeMultiplier = 1.0;` — Volume multiplier to use this frame
- L65 _public member_ `double PitchMultiplier = 1.0;` — Pitch multiplier to use this frame
- L71 _public member_ `TOptional<float> PartialDesyncComputation;` — Set whenever we ask the Audio component to start playing a sound. Used to detect desyncs caused when Sequencer evaluates at more-than-real-time.
- L74 _public member_ `TOptional<float> LastAudioTime;` — Previous audio time taking into account any time dilation
- L76 _public member_ `TOptional<float> LastContextTime;` — The context time from the previous evaluation pass
- L79 _public member_ `bool bEvaluatedThisFrame = false;` — Flag to keep track of audio components evaluated on a given frame
- L82 _public member_ `bool bAudioComponentHasBeenPlayed = false;` — Flag to keep track of if the audio component was played in a previous frame.

#### class `UMovieSceneAudioSystem`  
`class UMovieSceneAudioSystem : public UMovieSceneEntitySystem`  
_L90-166_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- desc: System for evaluating audio tracks
- L96 _public typedef_ `using FInstanceHandle = UE::MovieScene::FInstanceHandle;`
- L97 _public typedef_ `using FMovieSceneEntityID = UE::MovieScene::FMovieSceneEntityID;`
- L98 _public typedef_ `using FAudioComponentEvaluationData = UE::MovieScene::FAudioComponentEvaluationData;`
- L99 _public typedef_ `using FAudioComponentInputEvaluationData = UE::MovieScene::FAudioComponentInputEvaluationData;`
- L101 _public prototype_ `UMovieSceneAudioSystem(const FObjectInitializer& ObjInit);`
- L104 _public prototype_ `virtual void OnLink() override;`
- L105 _public prototype_ `virtual void OnUnlink() override;`
- L106 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L107 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L114 _public prototype_ `FAudioComponentEvaluationData* GetAudioComponentEvaluationData(FInstanceHandle InstanceHandle, FObjectKey ActorKey, FObjectKey SectionKey, UMovieSceneAudioSection* Section);` — Get the evaluation data for the given actor and section. Pass a null actor key for root (world) audio. Section is the audio section requesting the entry; when the fallback steal path adopts an existing entry, the moved data has its OwningSection re-stamped to Section so subsequent reuse-loop checks see the new owner.
- L120 _public prototype_ `FAudioComponentEvaluationData* AddBoundObjectAudioComponent(FInstanceHandle InstanceHandle, UMovieSceneAudioSection* Section, UObject* PrincipalObject);` — Adds an audio component to the given bound sequencer object. WARNING: Only to be called on the game thread.
- L126 _public prototype_ `FAudioComponentEvaluationData* AddRootAudioComponent(FInstanceHandle InstanceHandle, UMovieSceneAudioSection* Section, UWorld* World);` — Adds an audio component to the world, for playing root audio tracks. WARNING: Only to be called on the game thread.
- L131 _public prototype_ `void StopSound(FInstanceHandle InstanceHandle, FObjectKey ActorKey, FObjectKey SectionKey, bool bIsRecordingAudio);` — Stop (or just pause if bIsRecordingAudio) the audio on the audio component associated with the given audio section.
- L136 _public prototype_ `void ResetSharedData();` — Reset shared accumulation data required every evaluation frame
- L139 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);` — To expose the class to GC //
- L143 _private typedef_ `using FInstanceObjectKey = TTuple<FInstanceHandle, FObjectKey>;`
- L146 _private typedef_ `using FAudioComponentBySectionKey = TMap<FInstanceObjectKey, FAudioComponentEvaluationData>;` — Map of all created audio components
- L147 _private typedef_ `using FAudioComponentsByActorKey = TMap<FObjectKey, FAudioComponentBySectionKey>;`
- L148 _private member_ `FAudioComponentsByActorKey AudioComponentsByActorKey;`
- L151 _private typedef_ `using FAudioInputsBySectionKey = TMap<FInstanceObjectKey, FAudioComponentInputEvaluationData>;` — Map of audio input values, rebuilt every frame
- L152 _private member_ `FAudioInputsBySectionKey AudioInputsBySectionKey;`
- L155 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedAudioStorage> PreAnimatedStorage;` — Pre-animated state
- L158 _private member_ `bool bLifespanTrackingInvalidatedThisFrame = false;` — Set by InvalidateLifespanTracking() to suppress redundant full-map walks within a single frame when many entities transition in or out of Scrubbing simultaneously. Reset in ResetSharedData().
- L161 _private prototype_ `void InvalidateLifespanTracking();` — Reset the cached AudioComponentLifespanControlSection on every tracked component so the next eval re-issues BeginTrackingEntity with the current effective bWantsRestoreState. Idempotent within a frame.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/Systems/MovieSceneDataLayerSystem.h` (Private)


#### class `UMovieSceneDataLayerSystem`  
`class UMovieSceneDataLayerSystem : public UMovieSceneEntitySystem`  
_L30-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that applies all data layer changes to the world
- L37 _public prototype_ `UMovieSceneDataLayerSystem(const FObjectInitializer& ObjInit);`
- L41 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L42 _private prototype_ `virtual void OnLink() override;`
- L43 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L45 _private prototype_ `UDataLayerManager* GetDataLayerManager(UE::MovieScene::FMovieSceneEntityID EntityID, UE::MovieScene::FRootInstanceHandle RootInstance);`
- L46 _private prototype_ `void UpdateDesiredStates();`
- L47 _private prototype_ `void BeginTrackingEntities();`
- L52 _private member_ `UE::MovieScene::FCachedEntityFilterResult_Match ApplicableFilter;` — Cached filter that tells us whether we need to run this frame
- L54 _private member_ `TSharedPtr<UE::MovieScene::FDesiredLayerStates> DesiredLayerStates;` — Impl class that stores the desired layer states for the current (and last) frame
- L56 _private member_ `TWeakPtr<UE::MovieScene::FPreAnimatedDataLayerStorage> WeakPreAnimatedStorage;` — Weak ptr to the pre-animated storage if we need to cache previous states for layers

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/Systems/MovieSceneFadeSystem.h` (Private)


#### class `UMovieSceneFadeSystem`  
`class UMovieSceneFadeSystem : public UMovieSceneEntitySystem`  
_L16-29_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- L21 _public prototype_ `UMovieSceneFadeSystem(const FObjectInitializer& ObjInit);`
- L23 _public prototype_ `virtual void OnLink() override;`
- L24 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L25 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L28 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedFadeStateStorage> PreAnimatedStorage;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/Systems/MovieSceneLevelVisibilitySystem.h` (Private)


#### struct `UE::MovieScene::FMovieSceneLevelStreamingSharedData`  
`struct FMovieSceneLevelStreamingSharedData`  
_L23-70_
- L25 _public prototype_ `bool HasAnythingToDo() const;`
- L26 _public prototype_ `void AssignLevelVisibilityOverrides(FInstanceHandle Instance, TArrayView<const FName> LevelNames, ELevelVisibility Visibility, int32 Bias, FMovieSceneEntityID EntityID);`
- L27 _public prototype_ `void UnassignLevelVisibilityOverrides(TArrayView<const FName> LevelNames, FMovieSceneEntityID EntityID);`
- L28 _public prototype_ `void Flush(UMovieSceneEntitySystemLinker* Linker);`
- L29 _public prototype_ `void RestoreLevels(UMovieSceneEntitySystemLinker* Linker);`
- L32 _private prototype_ `ULevelStreaming* GetLevel(FName SafeLevelName, UWorld& World);`
- L65 _private member_ `TMap<FName, FVisibilityData> VisibilityMap;`
- L67 _private member_ `TMap<FName, TWeakObjectPtr<ULevelStreaming>> NameToLevelMap;`
- L69 _private member_ `TArray<FName, TInlineAllocator<8>> LevelsToRestore;`

#### struct `UE::MovieScene::FMovieSceneLevelStreamingSharedData::FVisibilityData`  
`struct FVisibilityData`  
_L35-64_
- L37 _public member_ `TOptional<bool> bPreviousState;`
- L39 _public prototype_ `void Add(FMovieSceneEntityID EntityID, FInstanceHandle Instance, int32 Bias, ELevelVisibility Visibility);`
- L40 _public prototype_ `void Remove(FMovieSceneEntityID EntityID);`
- L43 _public prototype_ `bool IsEmpty() const;` — Check whether this visibility data is empty
- L46 _public prototype_ `TOptional<ELevelVisibility> CalculateVisibility() const;` — Returns whether or not this level name should be visible or not
- L49 _public prototype_ `void GetSharedPlaybackStates(FInstanceRegistry* InstanceRegistry, TArray<TSharedRef<FSharedPlaybackState>>& OutSharedPlaybackStates) const;` — Retrieve all shared playback states that are animating this level's visibility
- L63 _private member_ `TArray<FVisibilityRequest, TInlineAllocator<2>> Requests;`

#### struct `UE::MovieScene::FMovieSceneLevelStreamingSharedData::FVisibilityData::FVisibilityRequest`  
`struct FVisibilityRequest`  
_L52-62_
- L55 _public member_ `FInstanceHandle Instance;` — The instance that contains the entity that made the request
- L57 _public member_ `FMovieSceneEntityID EntityID;` — The entity that made the request
- L59 _public member_ `int32 Bias;` — The bias of the entity
- L61 _public member_ `ELevelVisibility Visibility;` — The actual visibility requested

#### class `UMovieSceneLevelVisibilitySystem`  
`class UMovieSceneLevelVisibilitySystem : public UMovieSceneEntitySystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L75-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem,IMovieScenePreAnimatedStateSystemInterface`
- L83 _public prototype_ `UMovieSceneLevelVisibilitySystem(const FObjectInitializer& ObjInit);`
- L87 _private prototype_ `virtual void OnLink() override;`
- L88 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L90 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L91 _private prototype_ `virtual void RestorePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L96 _private member_ `UE::MovieScene::FCachedEntityFilterResult_Match ApplicableFilter;` — Cached filter that tells us whether we need to run this frame
- L97 _private member_ `UE::MovieScene::FMovieSceneLevelStreamingSharedData SharedData;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/Systems/MovieSceneSlomoSystem.h` (Private)


#### class `UMovieSceneSlomoSystem`  
`class UMovieSceneSlomoSystem : public UMovieSceneEntitySystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L20-38_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem,IMovieScenePreAnimatedStateSystemInterface`
- desc: System for evaluating and applying world time dilation
- L27 _public prototype_ `UMovieSceneSlomoSystem(const FObjectInitializer& ObjInit);`
- L29 _public prototype_ `virtual void OnLink() override;`
- L30 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L31 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L34 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L37 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedSlomoStateStorage> PreAnimatedStorage;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/TrackInstances/MovieSceneCVarTrackInstance.h` (Private)


#### class `UMovieSceneCVarTrackInstance`  
`class UMovieSceneCVarTrackInstance : public UMovieSceneTrackInstance`  
_L13-26_
- reflection: `UCLASS()`
- inherits: `UMovieSceneTrackInstance`
- L18 _private prototype_ `virtual void OnBeginUpdateInputs() override;`
- L19 _private prototype_ `virtual void OnAnimate() override;`
- L20 _private prototype_ `virtual void OnInputAdded(const FMovieSceneTrackInstanceInput& InInput) override;`
- L21 _private prototype_ `virtual void OnInputRemoved(const FMovieSceneTrackInstanceInput& InInput) override;`
- L22 _private prototype_ `virtual void OnEndUpdateInputs() override;`
- L23 _private prototype_ `virtual void OnDestroyed() override;`
- L25 _private member_ `TSet<FString> CVarsNeedingUpdate;`

### `Source/Runtime/MovieSceneTracks/Private/TrackInstances/MovieSceneCameraCutEditorHandler.h` (Private)


#### struct `UE::MovieScene::FPreAnimatedCameraCutEditorState`  
`struct FPreAnimatedCameraCutEditorState`  
_L27-31_
- desc: Pre-animated editor viewpoint
- L29 _public member_ `FVector ViewportLocation;`
- L30 _public member_ `FRotator ViewportRotation;`

#### struct `UE::MovieScene::FPreAnimatedCameraCutEditorTraits`  
`struct FPreAnimatedCameraCutEditorTraits : FPreAnimatedStateTraits`  
_L34-44_
- inherits: `FPreAnimatedStateTraits`
- desc: Pre-animated traits for in-editor camera cuts
- L37 _public typedef_ `using KeyType = FLevelEditorViewportClient*;` — Key type is the viewport to restore location/rotation/FOV on.
- L38 _public typedef_ `using StorageType = FPreAnimatedCameraCutEditorState;`
- L40 _public prototype_ `static bool ShouldHandleViewportCameraCuts(UWorld* ViewportWorld);`
- L41 _public prototype_ `static StorageType CachePreAnimatedValue(KeyType InKey);`
- L43 _public prototype_ `void RestorePreAnimatedValue(KeyType InKey, const StorageType& CachedValue, const FRestoreStateParams& Params);`

#### struct `UE::MovieScene::THasAddReferencedObjectForComponent`  
`template<> struct THasAddReferencedObjectForComponent<FLevelEditorViewportClient*>`  
_L48-51_
- desc: Make it possible to declare our storage below with a forward-declared FLevelEditorViewportClient.
- L50 _public member_ `static constexpr bool Value = false;`

#### struct `UE::MovieScene::FPreAnimatedCameraCutEditorStorage`  
`struct FPreAnimatedCameraCutEditorStorage : TPreAnimatedStateStorage<FPreAnimatedCameraCutEditorTraits>`  
_L54-57_
- inherits: `TPreAnimatedStateStorage<FPreAnimatedCameraCutEditorTraits>`
- desc: Pre-animated state storage for in-editor camera cuts
- L56 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedCameraCutEditorStorage> StorageID;`

#### enum `UE::MovieScene::EForcedCameraCutPreAnimatedStorageOperation`  
`enum class EForcedCameraCutPreAnimatedStorageOperation`  
_L60-65_
- desc: Type of forced operation on camera cut editor pre-animated state storage
- L62 _public enumerator_ `Cache`
- L63 _public enumerator_ `Restore`
- L64 _public enumerator_ `Discard`

#### struct `UE::MovieScene::FCameraCutEditorHandler`  
`struct FCameraCutEditorHandler`  
_L70-106_
- desc: Utility class for executing camera cuts in the editor viewports.
- L72 _public prototype_ `FCameraCutEditorHandler( UMovieSceneEntitySystemLinker* InLinker, const FSequenceInstance& InSequenceInstance, FCameraCutViewportPreviewer& InViewportPreviewer);`
- L78 _public prototype_ `void SetCameraCut( UObject* CameraObject, const FMovieSceneCameraCutParams& CameraCutParams);` — Sets the given camera cut in all editor viewport with cinematic control enabled
- L83 _public prototype_ `static void CachePreAnimatedValue( UMovieSceneEntitySystemLinker* Linker, const FSequenceInstance& SequenceInstance);` — Cache any pre-animated values required for handling camera cuts in editor.
- L87 _public prototype_ `static void ForcePreAnimatedValueOperation( UMovieSceneEntitySystemLinker* Linker, const FSequenceInstance& SequenceInstance, EForcedCameraCutPreAnimatedStorageOperation Operation);` — Force cache/discard/restore pre-animated values
- L94 _private prototype_ `void SetCameraCutForViewport( FLevelEditorViewportClient& ViewportClient, AActor* CameraActor, UCameraComponent* CameraComponent, const FMovieSceneCameraCutParams& CameraCutParams);`
- L99 _private prototype_ `void ReleaseCameraCutForViewport( FLevelEditorViewportClient& ViewportClient);`
- L103 _private member_ `UMovieSceneEntitySystemLinker* Linker;`
- L104 _private member_ `const FSequenceInstance& SequenceInstance;`
- L105 _private member_ `FCameraCutViewportPreviewer& ViewportPreviewer;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Private/TrackInstances/MovieSceneCameraCutGameHandler.h` (Private)


#### struct `UE::MovieScene::FPreAnimatedCameraCutState`  
`struct FPreAnimatedCameraCutState`  
_L21-27_
- desc: Pre-animated view target info
- L23 _public member_ `FObjectKey LastWorld;`
- L24 _public member_ `FObjectKey LastLocalPlayer;`
- L25 _public member_ `FObjectKey LastViewTarget;`
- L26 _public member_ `TOptional<EAspectRatioAxisConstraint> LastAspectRatioAxisConstraint;`

#### struct `UE::MovieScene::FPreAnimatedCameraCutTraits`  
`struct FPreAnimatedCameraCutTraits : FPreAnimatedStateTraits`  
_L30-40_
- inherits: `FPreAnimatedStateTraits`
- desc: Pre-animated traits for in-game camera cuts
- L33 _public typedef_ `using KeyType = uint8;` — Key type is an integer, to be maybe later used as the splitscreen index.
- L34 _public typedef_ `using StorageType = FPreAnimatedCameraCutState;`
- L36 _public prototype_ `static bool ShouldHandleWorldCameraCuts(UWorld* World);`
- L37 _public prototype_ `static StorageType CachePreAnimatedValue(UObject* PlaybackContext, uint8 InKey);`
- L39 _public prototype_ `void RestorePreAnimatedValue(uint8 InKey, const StorageType& CachedValue, const FRestoreStateParams& Params);`

#### struct `UE::MovieScene::FPreAnimatedCameraCutStorage`  
`struct FPreAnimatedCameraCutStorage : TPreAnimatedStateStorage<FPreAnimatedCameraCutTraits>`  
_L43-46_
- inherits: `TPreAnimatedStateStorage<FPreAnimatedCameraCutTraits>`
- desc: Pre-aniamted state storage for in-game camera cuts
- L45 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedCameraCutStorage> StorageID;`

#### struct `UE::MovieScene::FCameraCutGameHandler`  
`struct FCameraCutGameHandler`  
_L51-73_
- desc: Utility class for executing camera cuts in game worlds (including PIE).
- L53 _public prototype_ `FCameraCutGameHandler( UMovieSceneEntitySystemLinker* InLinker, const FSequenceInstance& InSequenceInstance);`
- L58 _public prototype_ `void SetCameraCut( UObject* CameraObject, const FMovieSceneCameraCutParams& CameraCutParams);` — Sets the given camera cut in all qualifying game worlds.
- L63 _public prototype_ `static void CachePreAnimatedValue( UMovieSceneEntitySystemLinker* Linker, const FSequenceInstance& SequenceInstance);` — Cache any pre-animated values required for handling camera cuts in game.
- L66 _public prototype_ `static void ForcePreAnimatedValueRestore( UMovieSceneEntitySystemLinker* Linker, const FSequenceInstance& SequenceInstance);`
- L71 _private member_ `UMovieSceneEntitySystemLinker* Linker;`
- L72 _private member_ `const FSequenceInstance& SequenceInstance;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)
- L75 _prototype_ `APlayerController* GetPlaybackController(const UObject* PlaybackContext);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Private/TrackInstances/MovieSceneCameraCutViewportPreviewer.h` (Private)


#### struct `UE::MovieScene::FCameraCutViewportPreviewerTarget`  
`struct FCameraCutViewportPreviewerTarget`  
_L25-36_
- desc: View target for the camera viewport previewer.
- L28 _public member_ `AActor* CameraActor = nullptr;` — Either an actor with an optional camera component...
- L29 _public member_ `UCameraComponent* CameraComponent = nullptr;`
- L32 _public member_ `TSharedPtr<FPreAnimatedCameraCutEditorStorage> PreAnimatedStorage;` — ...or a pre-animated viewport position, to be found in the given storage.
- L35 _public prototype_ `void Get(FLevelEditorViewportClient* InClient, FVector& OutLocation, FRotator& OutRotation, float& OutFOV, FPostProcessSettings& OutPP, float& OutPPWeight) const;` — Returns the target's location, rotation, and FOV

#### class `UE::MovieScene::FCameraCutViewportPreviewer`  
`class FCameraCutViewportPreviewer`  
_L46-93_
- desc: Utility class for previewing camera cut blends in editor. This class is able to register view modifiers on editor viewports and, if needed, move the viewport's point-of-view into a blend between two targets. This is used by FCameraCutEditorHandler to preview blending, but should be inactive when no blending is needed.
- L49 _public prototype_ `FCameraCutViewportPreviewer();`
- L50 _public prototype_ `~FCameraCutViewportPreviewer();`
- L57 _public prototype_ `void ToggleViewportPreviewModifiers(bool bEnable);` — Toggle whether this previewer is running a blend preview. This will register/unregister the view modifiers on all editor viewports that have cinematic control enabled.
- L64 _public prototype_ `void SetupBlend(const FCameraCutViewportPreviewerTarget& From, const FCameraCutViewportPreviewerTarget& To, float InBlendFactor);` — Sets up a blend to be previewed between the specified targets, using the specified blend factor. This will only do something if ToggleViewportPreviewModifiers(true) has been called.
- L70 _public prototype_ `void TeardownBlend();` — Stops previewing any blend. This will make the view modifier dormant but won't unregister it (that's only done with ToggleViewportPreviewModifiers(false)).
- L74 _private prototype_ `void UpdatePreviewLevelViewportClientFromCameraCut(FLevelEditorViewportClient& InViewportClient, UObject* InCameraObject, const FMovieSceneCameraCutParams& CameraCutParams);`
- L75 _private prototype_ `void ModifyViewportClientView(FEditorViewportViewModifierParams& Params);`
- L76 _private prototype_ `void OnLevelViewportClientListChanged();`
- L80 _private member_ `FCameraCutViewportPreviewerTarget FromTarget;` — Target from which to blend
- L82 _private member_ `FCameraCutViewportPreviewerTarget ToTarget;` — Target towards which to blend
- L84 _private member_ `float BlendFactor;` — Blend factor between both targets
- L87 _private member_ `bool bApplyViewModifier;` — Whether to apply the modifier with the blended view information
- L90 _private member_ `bool bViewportModifiersRegistered = false;` — Whether we have registered viewport modifiers in the editor.
- L92 _private member_ `TArray<FLevelEditorViewportClient*> RegisteredViewportClients;` — Which viewport clients we have registered with

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Bindings/MovieSceneReplaceableActorBinding.h` (Public)


#### class `UMovieSceneReplaceableActorBinding`  
`class UMovieSceneReplaceableActorBinding : public UMovieSceneReplaceableBindingBase`  
_L15-46_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, DefaultToInstanced, Meta=(DisplayName="Replaceable Actor"))`
- inherits: `UMovieSceneReplaceableBindingBase`
- desc: An implementation of UMovieSceneReplaceableBindingBase that uses UMovieSceneSpawnableActorBinding as the preview spawnable, and has no implementation of ResolveRuntimeBindingInternal, relying instead of Sequencer's built in BindingOverride mechanism for binding at runtime.
- L29 _public prototype_ `FText GetBindingTypePrettyName() const override;`
- L37 _protected function_ `virtual FMovieSceneBindingResolveResult ResolveRuntimeBindingInternal(const FMovieSceneBindingResolveParams& ResolveParams, int32 BindingIndex, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override` — By default we return nullptr here, as we rely on Sequencer's BindingOverride mechanism to bind these actors during runtime. This can be overridden if desired in subclasses to provide a different way to resolve to an actor at runtime while still using spawnable actor as the preview.
- L40 _protected function_ `virtual void InitReplaceableBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override` — Empty implementation by default as we don't need to initialize any data members other than the spawnable,which is initialized by CreateInnerSpawnable above
- L42 _protected prototype_ `virtual TSubclassOf<UMovieSceneSpawnableBindingBase> GetInnerSpawnableClass() const override;`
- L44 _protected function_ `virtual int32 GetCustomBindingPriority() const override`

#### class `UMovieSceneReplaceableActorBinding_BPBase`  
`class UMovieSceneReplaceableActorBinding_BPBase : public UMovieSceneReplaceableBindingBase`  
_L51-129_
- reflection: `UCLASS(Abstract, Blueprintable, MinimalAPI, EditInlineNew, DefaultToInstanced, Meta=(ShowWorldContextPin, DisplayName="Replaceable Blueprint Base"))`
- inherits: `UMovieSceneReplaceableBindingBase`
- L62 _public prototype_ `FText GetBindingTypePrettyName() const override final;`
- L63 _public prototype_ `virtual FText GetBindingTrackIconTooltip() const override final;`
- L65 _public prototype_ `void OnBindingAddedOrChanged(UMovieScene& OwnerMovieScene) override final;`
- L72 _public member_ `FText BindingTypePrettyName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sequencer")` — Name to show in Sequencer for the custom binding type.
- L76 _public member_ `FText BindingTypeTooltip;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sequencer")` — Tooltip to show in Sequencer for the custom binding type.
- L88 _public member_ `int32 CustomBindingPriority = BaseEnginePriority;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sequencer")` — Priority with which to consider this binding type over others when considering binding an object to Sequencer. As a guideline, a priority of BaseEnginePriority will ensure that engine types(such as Spawnable Actor, Replaceable Actor) will be higher priority than your custom binding, and so your binding type will not automatically be created(but may be converted to manually). A priority of BaseCustomPriority and higher will ensure that your binding type is considered more highly than engine types, so if your binding type's 'SupportsBindingCreationFromObject' returns true for an object, your binding type will be created by default rather than an engine type.
- L92 _public member_ `TSubclassOf<UMovieSceneSpawnableBindingBase> PreviewSpawnableType;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Preview", meta=(AllowAbstract=false))` — Preview Spawnable Type to use for this replaceable
- L94 _public function_ `int32 GetCustomBindingPriority() const override final`
- L101 _public prototype_ `FMovieSceneBindingResolveResult BP_ResolveRuntimeBinding(const FMovieSceneBindingResolveContext& ResolveContext) const;` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, meta=(DisplayName = "Resolve Runtime Binding"))` — Must be implemented. Called during non-editor/runtime to resolve the binding dynamically. In editor worlds/Sequencer will instead use the PreviewSpawnable binding to spawn a preview object. If no object is returned, Sequencer's BindingOverrides can still be used to dynamically bind the object.
- L105 _public prototype_ `void BP_InitReplaceableBinding(UObject* SourceObject, UMovieScene* OwnerMovieScene);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, meta=(DisplayName = "Init Replaceable Binding"))` — Called after binding creation to allow the replaceable to initialize any data members from the source object.
- L109 _public prototype_ `bool BP_SupportsBindingCreationFromObject(const UObject* SourceObject) const;` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, meta=(DisplayName = "Supports Binding Creation From Object"))` — Called on the binding to determine whether this binding type supports creating a binding from the passed in object.
- L115 _protected prototype_ `UMovieSceneCustomBinding* CreateCustomBindingFromBinding(const FMovieSceneBindingReference& BindingReference, UObject* SourceObject, UMovieScene& OwnerMovieScene) override final;`
- L120 _protected prototype_ `FMovieSceneBindingResolveResult ResolveRuntimeBindingInternal(const FMovieSceneBindingResolveParams& ResolveParams, int32 BindingIndex, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — By default we return nullptr here, as we rely on Sequencer's BindingOverride mechanism to bind these actors during runtime. This can be overridden if desired in subclasses to provide a different way to resolve to an actor at runtime while still using spawnable actor as the preview.
- L122 _protected prototype_ `void InitReplaceableBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override final;`
- L124 _protected function_ `TSubclassOf<UMovieSceneSpawnableBindingBase> GetInnerSpawnableClass() const override final`
- L126 _protected prototype_ `bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override final;`

### `Source/Runtime/MovieSceneTracks/Public/Bindings/MovieSceneReplaceableDirectorBlueprintBinding.h` (Public)


#### class `UMovieSceneReplaceableDirectorBlueprintBinding`  
`class UMovieSceneReplaceableDirectorBlueprintBinding : public UMovieSceneReplaceableBindingBase`  
_L18-60_
- reflection: `UCLASS(BlueprintType, MinimalAPI, EditInlineNew, DefaultToInstanced, Meta=(DisplayName="Replaceable from Director Blueprint"))`
- inherits: `UMovieSceneReplaceableBindingBase`
- L29 _public prototype_ `FText GetBindingTypePrettyName() const override;`
- L30 _public prototype_ `void OnBindingAddedOrChanged(UMovieScene& OwnerMovieScene) override;`
- L35 _public member_ `FMovieSceneDynamicBinding DynamicBinding;` — `UPROPERTY(EditAnywhere, Category="Sequencer")` — Director Blueprint defined binding info
- L39 _public member_ `TSubclassOf<UMovieSceneSpawnableBindingBase> PreviewSpawnableType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer")` — Preview Spawnable Type to use for this replaceable
- L44 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L47 _protected prototype_ `virtual UMovieSceneCustomBinding* CreateCustomBindingFromBinding(const FMovieSceneBindingReference& BindingReference, UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L52 _protected prototype_ `virtual FMovieSceneBindingResolveResult ResolveRuntimeBindingInternal(const FMovieSceneBindingResolveParams& ResolveParams, int32 BindingIndex, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — By default we return nullptr here, as we rely on Sequencer's BindingOverride mechanism to bind these actors during runtime. This can be overridden if desired in subclasses to provide a different way to resolve to an actor at runtime while still using spawnable actor as the preview.
- L55 _protected function_ `virtual void InitReplaceableBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override` — Empty implementation by default as we don't need to initialize any data members other than the spawnable, which is initialized by CreateInnerSpawnable in the base class
- L57 _protected function_ `virtual TSubclassOf<UMovieSceneSpawnableBindingBase> GetInnerSpawnableClass() const override`
- L59 _protected function_ `virtual bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override`

### `Source/Runtime/MovieSceneTracks/Public/Bindings/MovieSceneSpawnableActorBinding.h` (Public)


#### class `UMovieSceneSpawnableActorBindingBase`  
`class UMovieSceneSpawnableActorBindingBase : public UMovieSceneSpawnableBindingBase`  
_L17-106_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMovieSceneSpawnableBindingBase`
- desc: The base class for actor-specific spawnable bindings. Contains a default implementation that can handle spawning an Actor from provided Actor class and optional Actor template. Can be overridden in C++ or blueprint to provide an Actor class and to add custom PostSpawnObject behavior such as mesh setup based on an asset. The below UMovieSceneSpawnableActorBinding class implements this base class and replicates the old FMovieSceneSpawnable behavior by using a specified Actor template to spawn an Actor and can be used out of the box.
- L29 _public function_ `virtual bool SupportsObjectTemplates() const` — Override and return true if the binding type supports object templates.
- L32 _public function_ `virtual UObject* GetObjectTemplate()` — Override and return the object template if the binding type supports object templates
- L38 _public function_ `virtual void SetObjectTemplate(UObject* InObjectTemplate)` — Sets the object template to the specified object directly. Used for Copy/Paste, typically you should use CopyObjectTemplate.
- L46 _public function_ `virtual void CopyObjectTemplate(UObject* InSourceObject, UMovieSceneSequence& MovieSceneSequence)` — Copy the specified object into this spawnable's template @param InSourceObject The source object to use. This object will be duplicated into the spawnable. @param MovieSceneSequence The movie scene sequence to which this spawnable belongs
- L52 _public prototype_ `void AutoSetNetAddressableName();` — Automatically determine a value for bNetAddressableName based on the spawnable type
- L57 _public function_ `FName GetLevelName() const` — Returns the optional level name to spawn the actor in, otherwise the Persistent level is used.
- L62 _public function_ `void SetLevelName(FName InLevelName)` — Used to provide an optional level name to spawn the actor in, otherwise the Persistent level is used.
- L68 _public member_ `bool bNetAddressableName = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spawnable)` — When enabled, the actor will be spawned with a unique name so that it can be addressable between clients and servers.
- L72 _public member_ `FName LevelName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawnable)` — Name of level to spawn into
- L78 _protected prototype_ `virtual TSubclassOf<AActor> GetActorClass() const PURE_VIRTUAL(UMovieSceneSpawnableActorBindingBase::GetActorClass, return AActor::StaticClass(););` — TODO: Make UFUNCTION
- L81 _protected function_ `virtual AActor* GetActorTemplate() const` — Optionally override to provide an Actor template to use during Spawn
- L84 _protected prototype_ `FTransform GetSpawnTransform() const;` — Returns the transform to spawn the actor at
- L86 _protected function_ `UClass* GetBoundObjectClass() const override`
- L89 _protected function_ `virtual int32 GetCustomBindingPriority() const override` — MovieSceneCustomBinding overrides
- L96 _protected prototype_ `virtual UObject* SpawnObjectInternal(UWorld* WorldContext, FName SpawnName, const FGuid& BindingId, int32 BindingIndex, UMovieScene& MovieScene, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;` — Overridden to handle Actor-specific spawning
- L99 _protected prototype_ `virtual void DestroySpawnedObjectInternal(UObject* Object) override;` — Overridden to handle Actor-specific destruction
- L101 _protected prototype_ `FName GetSpawnName(const FGuid& BindingId, UMovieScene& MovieScene, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;`
- L105 _private prototype_ `FName GetNetAddressableName(TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, const FGuid& BindingId, FMovieSceneSequenceID SequenceID, const FString& BaseName) const;`

#### class `UMovieSceneSpawnableActorBinding`  
`class UMovieSceneSpawnableActorBinding : public UMovieSceneSpawnableActorBindingBase`  
_L113-158_
- reflection: `UCLASS(BlueprintType, MinimalAPI, EditInlineNew, DefaultToInstanced, Meta=(DisplayName="Spawnable Actor"))`
- inherits: `UMovieSceneSpawnableActorBindingBase`
- desc: An implementation of UMovieSceneSpawnableActorBindingBase that matches the old FMovieSceneSpawnable spawnable implementation, allowing the spawning of Actors from a UObject template which is serialized inside the Sequence.
- L123 _public function_ `bool SupportsObjectTemplates() const override` — MovieSceneSpawnableActorBindingBase overrides
- L126 _public function_ `UObject* GetObjectTemplate() override` — Override and return the object template if the binding type supports object templates
- L129 _public prototype_ `void SetObjectTemplate(UObject* InObjectTemplate) override;` — MovieSceneSpawnableBindingBase overrides
- L130 _public prototype_ `void CopyObjectTemplate(UObject* InSourceObject, UMovieSceneSequence& MovieSceneSequence) override;`
- L133 _public prototype_ `virtual bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override;` — MovieSceneCustomBinding overrides
- L134 _public prototype_ `virtual UMovieSceneCustomBinding* CreateNewCustomBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L137 _public prototype_ `virtual bool SupportsConversionFromBinding(const FMovieSceneBindingReference& BindingReference, const UObject* SourceObject) const override;`
- L138 _public prototype_ `virtual UMovieSceneCustomBinding* CreateCustomBindingFromBinding(const FMovieSceneBindingReference& BindingReference, UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L139 _public prototype_ `virtual FText GetBindingTypePrettyName() const override;`
- L144 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L147 _protected prototype_ `UWorld* GetWorldContext(TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — MovieSceneSpawnableBindingBase overrides
- L150 _protected prototype_ `TSubclassOf<AActor> GetActorClass() const override;` — MovieSceneSpawnableActorBindingBase overrides
- L151 _protected function_ `AActor* GetActorTemplate() const override`
- L155 _protected member_ `TObjectPtr<AActor> ActorTemplate;` — `UPROPERTY(VisibleAnywhere, Category="Spawnable")`

### `Source/Runtime/MovieSceneTracks/Public/Bindings/MovieSceneSpawnableDirectorBlueprintBinding.h` (Public)


#### class `UMovieSceneSpawnableDirectorBlueprintBinding`  
`class UMovieSceneSpawnableDirectorBlueprintBinding : public UMovieSceneSpawnableBindingBase`  
_L16-59_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UMovieSceneSpawnableBindingBase`
- desc: Custom binding type that uses a Director Blueprint endpoint to allow the user to define how to spawn an actor for this binding.
- L24 _public function_ `UClass* GetBoundObjectClass() const override` — MovieSceneCustomBinding overrides- todo?
- L28 _public member_ `FMovieSceneDynamicBinding DynamicBinding;` — `UPROPERTY(EditAnywhere, Category="Sequencer")` — Director Blueprint defined binding info
- L35 _protected prototype_ `virtual UObject* SpawnObjectInternal(UWorld* WorldContext, FName SpawnName, const FGuid& BindingId, int32 BindingIndex, UMovieScene& MovieScene, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;` — Overridden to handle spawning
- L38 _protected prototype_ `virtual void DestroySpawnedObjectInternal(UObject* Object) override;` — Overridden to handle destruction
- L40 _protected prototype_ `FName GetSpawnName(const FGuid& BindingId, UMovieScene& MovieScene, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;`
- L43 _protected prototype_ `bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override;` — MovieSceneCustomBinding overrides
- L44 _protected prototype_ `UMovieSceneCustomBinding* CreateNewCustomBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L47 _protected prototype_ `bool SupportsConversionFromBinding(const FMovieSceneBindingReference& BindingReference, const UObject* SourceObject) const override;`
- L48 _protected prototype_ `UMovieSceneCustomBinding* CreateCustomBindingFromBinding(const FMovieSceneBindingReference& BindingReference, UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L49 _protected prototype_ `FText GetBindingTypePrettyName() const override;`
- L50 _protected prototype_ `FText GetBindingTrackIconTooltip() const override;`
- L54 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;` — UObject overrides
- L58 _private prototype_ `UWorld* GetWorldContext(TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — MovieSceneSpawnableBindingBase overrides

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneActorReferenceChannel.h` (Public)


#### struct `FMovieSceneActorReferenceKey`  
`struct FMovieSceneActorReferenceKey`  
_L17-46_
- reflection: `USTRUCT()`
- desc: Keyframe value type for actor references.
- L21 _public function_ `FMovieSceneActorReferenceKey()`
- L24 _public function_ `FMovieSceneActorReferenceKey(const FMovieSceneObjectBindingID& InBindingID) : Object(InBindingID)`
- L39 _public member_ `FMovieSceneObjectBindingID Object;` — `UPROPERTY(EditAnywhere, Category="Key")`
- L42 _public member_ `FName ComponentName;` — `UPROPERTY(EditAnywhere, Category="Key")`
- L45 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, Category="Key")`

#### struct `FMovieSceneActorReferenceChannel`  
`struct FMovieSceneActorReferenceChannel : public FMovieSceneChannel`  
_L52-162_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- desc: A channel containing keyframes referencing an actor elsewhere in a Sequence.
- L56 _public typedef_ `typedef FMovieSceneActorReferenceKey CurveValueType;`
- L58 _public function_ `FMovieSceneActorReferenceChannel() : DefaultValue()`
- L67 _public function_ `inline TMovieSceneChannelData<FMovieSceneActorReferenceKey> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L77 _public function_ `inline TMovieSceneChannelData<const FMovieSceneActorReferenceKey> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L89 _public prototype_ `bool Evaluate(FFrameTime InTime, FMovieSceneActorReferenceKey& OutValue) const;` — Evaluate this channel @param InTime     The time to evaluate at @param OutValue   A value to receive the result @return true if the channel was evaluated successfully, false otherwise
- L94 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L95 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L96 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L97 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L98 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L99 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L100 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L101 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L102 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L103 _public prototype_ `virtual void Reset() override;`
- L104 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L105 _public prototype_ `virtual void ClearDefault() override;`
- L106 _public prototype_ `virtual FKeyHandle GetHandle(int32 Index) override;`
- L107 _public prototype_ `virtual int32 GetIndex(FKeyHandle Handle) override;`
- L116 _public function_ `inline void SetDefault(FMovieSceneActorReferenceKey InDefaultValue)` — Set this channel's default value that should be used when no keys are present @param InDefaultValue The desired default value
- L126 _public function_ `inline const FMovieSceneActorReferenceKey& GetDefault() const` — Get this channel's default value that will be used when no keys are present @return (Optional) The channel's default value
- L134 _public function_ `void UpgradeLegacyTime(UObject* Context, double Time, FMovieSceneActorReferenceKey Value)` — Upgrade legacy data by appending to the end of the array. Assumes sorted data
- L149 _private member_ `TArray<FFrameNumber> KeyTimes;` — `UPROPERTY(meta=(KeyTimes))` — Sorted array of key times
- L153 _private member_ `FMovieSceneActorReferenceKey DefaultValue;` — `UPROPERTY()` — Default value used when there are no keys
- L157 _private member_ `TArray<FMovieSceneActorReferenceKey> KeyValues;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L161 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets.

#### Free symbols / members of external scopes

- L28 _function_ `friend bool operator==(const FMovieSceneActorReferenceKey& A, const FMovieSceneActorReferenceKey& B)`
- L33 _function_ `friend bool operator!=(const FMovieSceneActorReferenceKey& A, const FMovieSceneActorReferenceKey& B)`
- L165 _typedef_ `using FMovieSceneActorReferenceData UE_DEPRECATED(5.8, "Please use FMovieSceneActorReferenceCh` — Backwards compatibility for C++ code.
- L167 _function_ `inline bool EvaluateChannel(const FMovieSceneActorReferenceChannel* InChannel, FFrameTime InTime, FMovieSceneActorReferenceKey& OutValue)`
- L172 _function_ `inline bool GetChannelDefault(const FMovieSceneActorReferenceChannel* Channel, FMovieSceneActorReferenceKey& OutDefaultValue)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneCameraShakeSourceTriggerChannel.h` (Public)


#### struct `FMovieSceneCameraShakeSourceTrigger`  
`struct FMovieSceneCameraShakeSourceTrigger`  
_L28-59_
- reflection: `USTRUCT(BlueprintType)`
- L32 _public function_ `FMovieSceneCameraShakeSourceTrigger() : ShakeClass(nullptr) , PlayScale(1.f) , PlaySpace(ECameraShakePlaySpace::CameraLocal) , UserDefinedPlaySpace(ForceInitToZero)`
- L39 _public function_ `FMovieSceneCameraShakeSourceTrigger(TSubclassOf<UCameraShakeBase> InShakeClass) : ShakeClass(InShakeClass) , PlayScale(1.f) , PlaySpace(ECameraShakePlaySpace::CameraLocal) , UserDefinedPlaySpace(ForceInitToZero)`
- L48 _public member_ `TSubclassOf<UCameraShakeBase> ShakeClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Shake")` — Class of the camera shake to play
- L52 _public member_ `float PlayScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Shake")` — Scalar that affects shake intensity
- L55 _public member_ `ECameraShakePlaySpace PlaySpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Shake")`
- L58 _public member_ `FRotator UserDefinedPlaySpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Shake")`

#### struct `FMovieSceneCameraShakeSourceTriggerChannel`  
`struct FMovieSceneCameraShakeSourceTriggerChannel : public FMovieSceneChannel`  
_L62-104_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L66 _public typedef_ `typedef FMovieSceneCameraShakeSourceTrigger CurveValueType;`
- L68 _public function_ `inline TMovieSceneChannelData<FMovieSceneCameraShakeSourceTrigger> GetData()`
- L73 _public function_ `inline TMovieSceneChannelData<const FMovieSceneCameraShakeSourceTrigger> GetData() const`
- L80 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L81 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L82 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L83 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L84 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L85 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L86 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L87 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L88 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L89 _public prototype_ `virtual void Reset() override;`
- L90 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L95 _private member_ `TArray<FFrameNumber> KeyTimes;` — `UPROPERTY(meta=(KeyTimes))` — Array of times for each key
- L99 _private member_ `TArray<FMovieSceneCameraShakeSourceTrigger> KeyValues;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L103 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets.

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneCameraShakeSourceTriggerChannel> : TMovieSceneChannelTraitsBase<FMovieSceneCameraShakeSourceTriggerChannel>`  
_L107-110_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneCameraShakeSourceTriggerChannel>`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L109-109_

#### Free symbols / members of external scopes

- L109 _enumerator_ `enum { SupportsDefaults = false };` (scope `TMovieSceneChannelTraits::__anon375cea8e0103`)
- L112 _function_ `inline bool EvaluateChannel(const FMovieSceneCameraShakeSourceTriggerChannel* InChannel, FFrameTime InTime, FMovieSceneCameraShakeSourceTrigger& OutValue)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneDoublePerlinNoiseChannel.h` (Public)


#### struct `FMovieSceneDoublePerlinNoiseChannel`  
`struct FMovieSceneDoublePerlinNoiseChannel : public FMovieSceneChannel`  
_L11-50_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L15 _public typedef_ `using CurveValueType = double;`
- L17 _public prototype_ `FMovieSceneDoublePerlinNoiseChannel();`
- L25 _public prototype_ `double Evaluate(double InSeconds) const;` — Evaluate this channel at the given time @param InSeconds		The time, in seconds, to evaluate at @return				The evaluated noise value
- L35 _public prototype_ `bool Evaluate(const UMovieSceneSection* InSection, FFrameTime InTime, double& OutValue) const;` — Evaluate this channel at the given time @param InSection		The section that contains this channel, used to lookup the sequence's tick resolution @param InTime		The time, in ticks, to evaluate at @param OutValue		The evaluated noise value @return				Whether the noise was successfully evaluated
- L39 _public member_ `FPerlinNoiseParams PerlinNoiseParams;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise")` — The noise parameters
- L49 _public prototype_ `static double Evaluate(const FPerlinNoiseParams& InParams, double InSeconds);` — Evaluate perlin noise @params InParams			Perlin noise parameters @params InInitialOffset	The initial offset for the noise @params InSeconds		The time at which to evaluate the noise @return					The evaluated noise value

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneDoublePerlinNoiseChannel> : TMovieSceneChannelTraitsBase<FMovieSceneDoublePerlinNoiseChannel>`  
_L53-61_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneDoublePerlinNoiseChannel>`
- L58 _public typedef_ `typedef TMovieSceneExternalValue<double> ExtendedEditorDataType;` — Perlin noise channels can have external values (ie, they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L63 _function_ `inline bool EvaluateChannel(const UMovieSceneSection* InSection, const FMovieSceneDoublePerlinNoiseChannel* InChannel, FFrameTime InTime, double& OutValue)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneDoublePerlinNoiseChannelContainer.h` (Public)


#### class `UMovieSceneDoublePerlinNoiseChannelContainer`  
`class UMovieSceneDoublePerlinNoiseChannelContainer : public UMovieSceneChannelOverrideContainer`  
_L13-42_
- reflection: `UCLASS(meta=(DisplayName="Double Perlin Noise", ToolTip="Override a channel to use double perlin noise"), MinimalAPI)`
- inherits: `UMovieSceneChannelOverrideContainer`
- desc: Double perlin noise channel overriden container
- L19 _public typedef_ `using ChannelType = FMovieSceneDoublePerlinNoiseChannel;`
- L21 _public prototype_ `void InitializeOverride(FMovieSceneChannel* InChannel) override;`
- L22 _public prototype_ `bool SupportsOverride(FName DefaultChannelTypeName) const override;`
- L23 _public prototype_ `void ImportEntityImpl( const UE::MovieScene::FChannelOverrideEntityImportParams& OverrideParams, const UE::MovieScene::FEntityImportParams& ImportParams, UE::MovieScene::FImportedEntity* OutImportedEntity) override;`
- L27 _public function_ `const FMovieSceneChannel* GetChannel() const override`
- L28 _public function_ `FMovieSceneChannel* GetChannel() override`
- L31 _public prototype_ `FMovieSceneChannelHandle AddChannelProxy(FName ChannelName, FMovieSceneChannelProxyData& ProxyData, const FMovieSceneChannelMetaData& MetaData) override;`
- L33 _public prototype_ `void AddChannelProxy(FName ChannelName, FMovieSceneChannelProxyData& ProxyData) override;`
- L39 _private member_ `FMovieSceneDoublePerlinNoiseChannel PerlinNoiseChannel;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise")`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneEvent.h` (Public)


#### struct `FMovieSceneEventPayloadVariable`  
`struct FMovieSceneEventPayloadVariable`  
_L33-43_
- reflection: `USTRUCT(BlueprintType)`
- desc: Value definition for any type-agnostic variable (exported as text)
- L39 _public member_ `FSoftObjectPath ObjectValue;` — If the value for this pin should be an object, we store a pointer to it
- L42 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Event")`

#### struct `FMovieSceneEventPtrs`  
`struct FMovieSceneEventPtrs`  
_L47-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Compiled reflection pointers for the event function and parameters
- L51 _public function_ `FMovieSceneEventPtrs() : Function(nullptr) , BoundObjectProperty(nullptr)`
- L57 _public member_ `TObjectPtr<UFunction> Function;` — `UPROPERTY()`
- L60 _public member_ `TFieldPath<FProperty> BoundObjectProperty;` — `UPROPERTY()`

#### struct `FMovieSceneEvent`  
`struct FMovieSceneEvent`  
_L64-109_
- reflection: `USTRUCT(BlueprintType)`
- L73 _public member_ `FMovieSceneEventPtrs Ptrs;` — `UPROPERTY()` — The function that should be called to invoke this event. Functions must have either no parameters, or a single, pass-by-value object/interface parameter, with no return parameter.
- L78 _public prototype_ `UClass* GetBoundObjectPropertyClass() const;` — Return the class of the bound object property
- L84 _public member_ `TMap<FName, FMovieSceneEventPayloadVariable> PayloadVariables;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Event")` — Array of payload variables to be added to the generated function
- L87 _public member_ `FName CompiledFunctionName;` — `UPROPERTY(transient)`
- L90 _public member_ `FName BoundObjectPinName;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Event")`
- L94 _public member_ `TWeakObjectPtr<UObject> WeakEndpoint;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Event")` — Serialized weak pointer to the function entry (UK2Node_FunctionEntry) or custom event node (UK2Node_CustomEvent) within the blueprint graph for this event. Stored as an editor-only UObject so UHT can parse it when building for non-editor.
- L98 _public member_ `FGuid GraphGuid_DEPRECATED;` — `UPROPERTY()` — (deprecated) The UEdGraph::GraphGuid property that relates the graph within which our endpoint lives.
- L102 _public member_ `FGuid NodeGuid_DEPRECATED;` — `UPROPERTY()` — (deprecated) When valid, relates to the The UEdGraphNode::NodeGuid for a custom event node that defines our event endpoint. When invalid, we must be bound to a UBlueprint::FunctionGraphs graph.
- L106 _public member_ `TWeakObjectPtr<UObject> FunctionEntry_DEPRECATED;` — `UPROPERTY()` — Deprecated weak pointer to the function entry to call - no longer serialized but cached on load. Predates GraphGuid and NodeGuid

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneEventChannel.h` (Public)


#### struct `FMovieSceneEventChannel`  
`struct FMovieSceneEventChannel : public FMovieSceneChannel`  
_L25-80_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L29 _public typedef_ `typedef FMovieSceneEvent CurveValueType;`
- L36 _public function_ `inline TMovieSceneChannelData<FMovieSceneEvent> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L46 _public function_ `inline TMovieSceneChannelData<const FMovieSceneEvent> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L54 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L55 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L56 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L57 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L58 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L59 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L60 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L61 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L62 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L63 _public prototype_ `virtual void Reset() override;`
- L64 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L65 _public prototype_ `virtual FKeyHandle GetHandle(int32 Index) override;`
- L66 _public prototype_ `virtual int32 GetIndex(FKeyHandle Handle) override;`
- L71 _private member_ `TArray<FFrameNumber> KeyTimes;` — `UPROPERTY(meta=(KeyTimes))` — Array of times for each key
- L75 _private member_ `TArray<FMovieSceneEvent> KeyValues;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L79 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets.

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneEventChannel> : TMovieSceneChannelTraitsBase<FMovieSceneEventChannel>`  
_L83-86_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneEventChannel>`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L85-85_

#### Free symbols / members of external scopes

- L85 _enumerator_ `enum { SupportsDefaults = false };` (scope `TMovieSceneChannelTraits::__anon38dd5e960103`)
- L88 _function_ `inline bool EvaluateChannel(const FMovieSceneEventChannel* InChannel, FFrameTime InTime, FMovieSceneEvent& OutValue)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneFloatPerlinNoiseChannel.h` (Public)


#### struct `FMovieSceneFloatPerlinNoiseChannel`  
`struct FMovieSceneFloatPerlinNoiseChannel : public FMovieSceneChannel`  
_L11-50_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L15 _public typedef_ `using CurveValueType = float;`
- L17 _public prototype_ `FMovieSceneFloatPerlinNoiseChannel();`
- L25 _public prototype_ `float Evaluate(double InSeconds) const;` — Evaluate this channel at the given time @param InSeconds		The time, in seconds, to evaluate at @return				The evaluated noise value
- L35 _public prototype_ `bool Evaluate(const UMovieSceneSection* InSection, FFrameTime InTime, float& OutValue) const;` — Evaluate this channel at the given time @param InSection		The section that contains this channel, used to lookup the sequence's tick resolution @param InTime		The time, in ticks, to evaluate at @param OutValue		The evaluated noise value @return				Whether the noise was successfully evaluated
- L39 _public member_ `FPerlinNoiseParams PerlinNoiseParams;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")` — The noise parameters
- L49 _public prototype_ `static float Evaluate(const FPerlinNoiseParams& InParams, double InSeconds);` — Evaluate perlin noise @params InParams			Perlin noise parameters @params InInitialOffset	The initial offset for the noise @params InSeconds		The time at which to evaluate the noise @return					The evaluated noise value

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneFloatPerlinNoiseChannel> : TMovieSceneChannelTraitsBase<FMovieSceneFloatPerlinNoiseChannel>`  
_L53-61_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneFloatPerlinNoiseChannel>`
- L58 _public typedef_ `typedef TMovieSceneExternalValue<float> ExtendedEditorDataType;` — Perlin noise channels can have external values (ie, they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L63 _function_ `inline bool EvaluateChannel(const UMovieSceneSection* InSection, const FMovieSceneFloatPerlinNoiseChannel* InChannel, FFrameTime InTime, float& OutValue)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneFloatPerlinNoiseChannelContainer.h` (Public)


#### class `UMovieSceneFloatPerlinNoiseChannelContainer`  
`class UMovieSceneFloatPerlinNoiseChannelContainer : public UMovieSceneChannelOverrideContainer`  
_L14-43_
- reflection: `UCLASS(meta=(DisplayName="Float Perlin Noise", ToolTip="Override a channel to use float perlin noise"), MinimalAPI)`
- inherits: `UMovieSceneChannelOverrideContainer`
- desc: Float perlin noise channel overriden container
- L20 _public typedef_ `using ChannelType = FMovieSceneFloatPerlinNoiseChannel;`
- L22 _public prototype_ `void InitializeOverride(FMovieSceneChannel* InChannel) override;`
- L23 _public prototype_ `bool SupportsOverride(FName DefaultChannelTypeName) const override;`
- L24 _public prototype_ `void ImportEntityImpl( const UE::MovieScene::FChannelOverrideEntityImportParams& OverrideParams, const UE::MovieScene::FEntityImportParams& ImportParams, UE::MovieScene::FImportedEntity* OutImportedEntity) override;`
- L28 _public function_ `const FMovieSceneChannel* GetChannel() const override`
- L29 _public function_ `FMovieSceneChannel* GetChannel() override`
- L32 _public prototype_ `FMovieSceneChannelHandle AddChannelProxy(FName ChannelName, FMovieSceneChannelProxyData& ProxyData, const FMovieSceneChannelMetaData& MetaData) override;`
- L34 _public prototype_ `void AddChannelProxy(FName ChannelName, FMovieSceneChannelProxyData& ProxyData) override;`
- L40 _private member_ `FMovieSceneFloatPerlinNoiseChannel PerlinNoiseChannel;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise")`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneStringChannel.h` (Public)


#### struct `FMovieSceneStringChannel`  
`struct FMovieSceneStringChannel : public FMovieSceneChannel`  
_L30-171_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L34 _public typedef_ `typedef FString CurveValueType;`
- L36 _public function_ `FMovieSceneStringChannel() : DefaultValue(), bHasDefaultValue(false)`
- L43 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Serialize this type from another
- L50 _public function_ `inline TMovieSceneChannelData<FString> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L60 _public function_ `inline TMovieSceneChannelData<const FString> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L68 _public function_ `inline TArrayView<const FFrameNumber> GetTimes() const` — Const access to this channel's times
- L76 _public function_ `inline bool HasAnyData() const` — Returns whether this channel has any values
- L87 _public prototype_ `const FString* Evaluate(FFrameTime InTime) const;` — Evaluate this channel @param InTime     The time to evaluate at @return A pointer to the string, or nullptr
- L94 _public function_ `inline void AddKeys(const TArray<FFrameNumber>& InTimes, const TArray<FString>& InValues)` — Add keys with these times to channel. The number of elements in both arrays much match or nothing is added. @param InTimes Times to add @param InValues Values to add
- L104 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L105 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L106 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L107 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L108 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L109 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L110 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L111 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L112 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L113 _public prototype_ `virtual void Reset() override;`
- L114 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L115 _public prototype_ `virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override;`
- L116 _public prototype_ `virtual void ClearDefault() override;`
- L117 _public prototype_ `virtual FKeyHandle GetHandle(int32 Index) override;`
- L118 _public prototype_ `virtual int32 GetIndex(FKeyHandle Handle) override;`
- L127 _public function_ `inline void SetDefault(FString InDefaultValue)` — Set this channel's default value that should be used when no keys are present @param InDefaultValue The desired default value
- L138 _public function_ `inline TOptional<FString> GetDefault() const` — Get this channel's default value that will be used when no keys are present @return (Optional) The channel's default value
- L146 _public function_ `inline void RemoveDefault()` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L154 _private member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(meta=(KeyTimes))`
- L158 _private member_ `TArray<FString> Values;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L162 _private member_ `FString DefaultValue;` — `UPROPERTY()` — Default value used when there are no keys
- L166 _private member_ `bool bHasDefaultValue;` — `UPROPERTY()`
- L170 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneStringChannel> : public TStructOpsTypeTraitsBase2<FMovieSceneStringChannel>`  
_L174-177_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneStringChannel>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L176-176_

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneStringChannel> : TMovieSceneChannelTraitsBase<FMovieSceneStringChannel>`  
_L181-189_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneStringChannel>`
- L186 _public typedef_ `typedef TMovieSceneExternalValue<FString> ExtendedEditorDataType;` — String channels can have external values (ie, they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L176 _enumerator_ `enum { WithStructuredSerializeFromMismatchedTag = true };` (scope `TStructOpsTypeTraits::__anon080efe2b0103`)
- L191 _function_ `inline bool EvaluateChannel(const FMovieSceneStringChannel* InChannel, FFrameTime InTime, FString& OutValue)`
- L201 _function_ `inline bool ValueExistsAtTime(const FMovieSceneStringChannel* Channel, FFrameNumber InFrameNumber, const FString& Value)`

### `Source/Runtime/MovieSceneTracks/Public/Channels/MovieSceneTextChannel.h` (Public)


#### struct `FMovieSceneTextChannel`  
`struct FMovieSceneTextChannel : public FMovieSceneChannel`  
_L20-144_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L24 _public typedef_ `typedef FText CurveValueType;`
- L27 _public prototype_ `void SetPackage(UPackage* InPackage);`
- L29 _public prototype_ `UPackage* GetPackage() const;`
- L36 _public function_ `inline TMovieSceneChannelData<FText> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L45 _public function_ `inline TMovieSceneChannelData<const FText> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L50 _public function_ `inline TConstArrayView<FFrameNumber> GetTimes() const`
- L56 _public function_ `inline bool HasAnyData() const` — Returns whether this channel has any values
- L66 _public prototype_ `const FText* Evaluate(FFrameTime InTime) const;` — Evaluate this channel @param InTime     The time to evaluate at @return A pointer to the string, or nullptr
- L73 _public function_ `inline void AddKeys(const TArray<FFrameNumber>& InTimes, const TArray<FText>& InValues)` — Add keys with these times to channel. The number of elements in both arrays much match or nothing is added. @param InTimes Times to add @param InValues Values to add
- L84 _public function_ `inline void SetDefault(FText InDefaultValue)` — Set this channel's default value that should be used when no keys are present @param InDefaultValue The desired default value
- L94 _public function_ `inline TOptional<FText> GetDefault() const` — Get this channel's default value that will be used when no keys are present @return (Optional) The channel's default value
- L100 _public function_ `inline void RemoveDefault()` — Remove this channel's default value causing the channel to have no effect where no keys are present
- L106 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L107 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L108 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L109 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L110 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L111 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L112 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L113 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L114 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L115 _public prototype_ `virtual void Reset() override;`
- L116 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L117 _public prototype_ `virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override;`
- L118 _public prototype_ `virtual void ClearDefault() override;`
- L123 _private member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(meta=(KeyTimes))`
- L127 _private member_ `TArray<FText> Values;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L131 _private member_ `FText DefaultValue;` — `UPROPERTY()` — Default value used when there are no keys
- L134 _private member_ `bool bHasDefaultValue = false;` — `UPROPERTY()`
- L138 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it does not get saved into assets.
- L142 _private member_ `TWeakObjectPtr<UPackage> Package;` — Package to use for Text Localization. Always set to the Package of the Section holding this Channel.

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneTextChannel> : TMovieSceneChannelTraitsBase<FMovieSceneTextChannel>`  
_L147-153_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneTextChannel>`
- L151 _public typedef_ `typedef TMovieSceneExternalValue<FText> ExtendedEditorDataType;` — Text channels can have external values (ie, they can get their values from external objects for UI purposes)

#### Free symbols / members of external scopes

- L155 _function_ `inline bool EvaluateChannel(const FMovieSceneTextChannel* InChannel, FFrameTime InTime, FText& OutValue)`
- L165 _function_ `inline bool ValueExistsAtTime(const FMovieSceneTextChannel* Channel, FFrameNumber InFrameNumber, const FText& Value)`

### `Source/Runtime/MovieSceneTracks/Public/Conditions/MovieSceneDirectorBlueprintCondition.h` (Public)


#### struct `FMovieSceneDirectorBlueprintConditionPayloadVariable`  
`struct FMovieSceneDirectorBlueprintConditionPayloadVariable`  
_L26-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: Value definition for any type-agnostic variable (exported as text)
- L31 _public member_ `FSoftObjectPath ObjectValue;` — `UPROPERTY()`
- L34 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = "Sequencer|Condition")`

#### struct `FMovieSceneDirectorBlueprintConditionData`  
`struct FMovieSceneDirectorBlueprintConditionData`  
_L41-72_
- reflection: `USTRUCT()`
- desc: Data for a director blueprint condition endpoint call.
- L47 _public member_ `TObjectPtr<UFunction> Function;` — `UPROPERTY()` — The function to call (normally a generated blueprint function on the sequence director)
- L51 _public member_ `TFieldPath<FProperty> ConditionContextProperty;` — `UPROPERTY()` — Property pointer for the function parameter that should receive the condition context params
- L57 _public member_ `TMap<FName, FMovieSceneDirectorBlueprintConditionPayloadVariable> PayloadVariables;` — `UPROPERTY(EditAnywhere, Category = "Sequencer|Condition")` — Array of payload variables to be added to the generated function
- L61 _public member_ `FName CompiledFunctionName;` — `UPROPERTY(transient)` — Name of the generated blueprint function
- L65 _public member_ `FName ConditionContextPinName;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")` — Pin name for passing the condition context params
- L69 _public member_ `TWeakObjectPtr<UObject> WeakEndpoint;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")` — Endpoint node in the sequence director

#### struct `FMovieSceneDirectorBlueprintConditionInvoker`  
`struct FMovieSceneDirectorBlueprintConditionInvoker`  
_L77-85_
- desc: Utility class for invoking director blueprint condition endpoints.
- L79 _public typedef_ `using FSharedPlaybackState = UE::MovieScene::FSharedPlaybackState;`
- L81 _public prototype_ `static bool EvaluateDirectorBlueprintCondition(FGuid BindingGuid, FMovieSceneSequenceID SequenceID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState, const FMovieSceneDirectorBlueprintConditionData& DirectorBlueprintCondition);`
- L84 _private prototype_ `static bool InvokeDirectorBlueprintCondition(UObject* DirectorInstance, const FMovieSceneDirectorBlueprintConditionData& DirectorBlueprintCondition, const FMovieSceneConditionContext& ConditionContext);`

#### class `UMovieSceneDirectorBlueprintCondition`  
`class UMovieSceneDirectorBlueprintCondition : public UMovieSceneCondition`  
_L93-121_
- reflection: `UCLASS(MinimalAPI, DisplayName="Director Blueprint Condition")`
- inherits: `UMovieSceneCondition`
- desc: Condition class allowing users to create a director blueprint endpoint in the Sequence to evaluate a condition.
- L101 _public member_ `FMovieSceneDirectorBlueprintConditionData DirectorBlueprintConditionData;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L108 _protected prototype_ `virtual bool EvaluateConditionInternal(FGuid BindingGuid, FMovieSceneSequenceID SequenceID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — UMovieSceneCondition overrides
- L110 _protected function_ `virtual EMovieSceneConditionScope GetScopeInternal() const override`
- L112 _protected function_ `virtual EMovieSceneConditionCheckFrequency GetCheckFrequencyInternal() const override`
- L117 _protected member_ `EMovieSceneConditionScope Scope = EMovieSceneConditionScope::Global;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L120 _protected member_ `EMovieSceneConditionCheckFrequency CheckFrequency = EMovieSceneConditionCheckFrequency::Once;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIESCENETRACKS_API`
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Conditions/MovieScenePlatformCondition.h` (Public)


#### class `UMovieScenePlatformCondition`  
`class UMovieScenePlatformCondition : public UMovieSceneCondition`  
_L23-44_
- reflection: `UCLASS(MinimalAPI, DisplayName="Platform Condition")`
- inherits: `UMovieSceneCondition`
- desc: Condition on whether the platform running the executable matches one of the given platforms.
- L31 _public member_ `TArray<FName> ValidPlatforms;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L38 _protected prototype_ `virtual bool EvaluateConditionInternal(FGuid BindingGuid, FMovieSceneSequenceID SequenceID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — UMovieSceneCondition overrides
- L40 _protected function_ `virtual EMovieSceneConditionScope GetScopeInternal() const override`
- L42 _protected function_ `virtual EMovieSceneConditionCheckFrequency GetCheckFrequencyInternal() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIESCENETRACKS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Conditions/MovieSceneScalabilityCondition.h` (Public)


#### enum `EMovieSceneScalabilityConditionGroup`  
`enum class EMovieSceneScalabilityConditionGroup : uint8`  
_L26-39_
- reflection: `UENUM()`
- L28 _public enumerator_ `ViewDistance`
- L29 _public enumerator_ `AntiAliasing`
- L30 _public enumerator_ `Shadow`
- L31 _public enumerator_ `GlobalIllumination`
- L32 _public enumerator_ `Reflection`
- L33 _public enumerator_ `PostProcess`
- L34 _public enumerator_ `Texture`
- L35 _public enumerator_ `Effects`
- L36 _public enumerator_ `Foliage`
- L37 _public enumerator_ `Shading`
- L38 _public enumerator_ `Landscape`

#### enum `EMovieSceneScalabilityConditionOperator`  
`enum class EMovieSceneScalabilityConditionOperator : uint8`  
_L43-50_
- reflection: `UENUM()`
- L45 _public enumerator_ `LessThan`
- L46 _public enumerator_ `LessThanOrEqualTo`
- L47 _public enumerator_ `EqualTo`
- L48 _public enumerator_ `GreaterThanOrEqualTo`
- L49 _public enumerator_ `GreaterThan`

#### enum `EMovieSceneScalabilityConditionLevel`  
`enum class EMovieSceneScalabilityConditionLevel : uint8`  
_L54-61_
- reflection: `UENUM()`
- L56 _public enumerator_ `Low`
- L57 _public enumerator_ `Medium`
- L58 _public enumerator_ `High`
- L59 _public enumerator_ `Epic`
- L60 _public enumerator_ `Cinematic`

#### class `UMovieSceneScalabilityCondition`  
`class UMovieSceneScalabilityCondition : public UMovieSceneCondition`  
_L67-94_
- reflection: `UCLASS(MinimalAPI, DisplayName="Scalability Condition")`
- inherits: `UMovieSceneCondition`
- desc: Condition on whether the current engine scalability settings fulfill a given constraint.
- L75 _public member_ `EMovieSceneScalabilityConditionGroup Group;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L78 _public member_ `EMovieSceneScalabilityConditionOperator Operator;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L81 _public member_ `EMovieSceneScalabilityConditionLevel Level;` — `UPROPERTY(EditAnywhere, Category="Sequencer|Condition")`
- L88 _protected prototype_ `virtual bool EvaluateConditionInternal(FGuid BindingGuid, FMovieSceneSequenceID SequenceID, TSharedRef<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) const override;` — UMovieSceneCondition overrides
- L90 _protected function_ `virtual EMovieSceneConditionScope GetScopeInternal() const override`
- L92 _protected function_ `virtual EMovieSceneConditionCheckFrequency GetCheckFrequencyInternal() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIESCENETRACKS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/EntitySystem/Interrogation/MovieSceneInterrogatedPropertyInstantiator.h` (Public)


#### class `UMovieSceneInterrogatedPropertyInstantiatorSystem`  
`class UMovieSceneInterrogatedPropertyInstantiatorSystem : public UMovieSceneEntityInstantiatorSystem`  
_L18-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: Class responsible for resolving all property types registered with FBuiltInComponentTypes::PropertyRegistry
- L23 _public typedef_ `using FMovieSceneEntityID = UE::MovieScene::FMovieSceneEntityID;`
- L24 _public typedef_ `using FValueRecompositionResult = UE::MovieScene::TRecompositionResult<double>;`
- L28 _public prototype_ `UMovieSceneInterrogatedPropertyInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L39 _public prototype_ `FValueRecompositionResult RecomposeBlendChannel(const UE::MovieScene::FPropertyDefinition& PropertyDefinition, int32 ChannelCompositeIndex, const UE::MovieScene::FDecompositionQuery& InQuery, double InCurrentValue);` — Recompose a value from the constituent parts specified in InQuery, taking into accounts the wieghtings of the specific channel defined by ChannelCompositeIndex. @param PropertyDefinition  The property that this float channel is bound to @param ChannelCompositeIndex  The index of the composite that this float channel represents, if it is part of a composite value (for instance when keying/recomposing Translation.Z) @param InQuery        The query defining the entities and object to recompose @param InCurrentValue The value of the property to recompose @return A result containing the recomposed value for each of the entities specified in InQuery
- L52 _public function_ `template<typename PropertyTraits, typename ValueType> UE::MovieScene::TRecompositionResult<ValueType> RecomposeBlend(const UE::MovieScene::TPropertyComponents<PropertyTraits>& InComponents, const UE::MovieScene::FDecompositionQuery& InQuery, const ValueType& InCurrentValue)` — Recompose a value from the constituent parts specified in InQuery, taking into account the weightings of each channel. For instance, if a property comprises 3 additive values (a:1, b:2, c:3), and we recompose 'a' with an InCurrentValue of 10, the result for a would be 5. @note: ValueType must be either copy assignable to/from the storage type of the property, or must have a ConvertOperationalProperty overload @param InComponents   The components that define the property to decompose @param InQuery        The query defining the entities and object to recompose @param InCurrentValue The value of the property to recompose @return A result matching the storage type of the components, containing recomposed values for each of the entities specified in InQuery
- L74 _public prototype_ `template<typename PropertyTraits> UE::MovieScene::TRecompositionResult<typename PropertyTraits::StorageType> RecomposeBlendOperational(const UE::MovieScene::TPropertyComponents<PropertyTraits>& InComponents, const UE::MovieScene::FDecompositionQuery& InQuery, const typename PropertyTraits::StorageType& InCurrentValue);` — Recompose a value from the constituent parts specified in InQuery, taking into account the weightings of each channel. For instance, if a property comprises 3 additive values (a:1, b:2, c:3), and we recompose 'a' with an InCurrentValue of 10, the result for a would be 5. @param InComponents   The components that define the property to decompose @param InQuery        The query defining the entities and object to recompose @param InCurrentValue The value of the property to recompose @return A result matching the storage type of the components, containing recomposed values for each of the entities specified in InQuery
- L93 _public prototype_ `void InitializeOutput(UE::MovieScene::FInterrogationKey Key, TArrayView<const FMovieSceneEntityID> Inputs, FPropertyInfo* Output, UE::MovieScene::FEntityOutputAggregate Aggregate);` — TOverlappingEntityTracker handler interface
- L94 _public prototype_ `void UpdateOutput(UE::MovieScene::FInterrogationKey Key, TArrayView<const FMovieSceneEntityID> Inputs, FPropertyInfo* Output, UE::MovieScene::FEntityOutputAggregate Aggregate);`
- L95 _public prototype_ `void DestroyOutput(UE::MovieScene::FInterrogationKey Key, FPropertyInfo* Output, UE::MovieScene::FEntityOutputAggregate Aggregate);`
- L97 _public function_ `const FPropertyInfo* FindPropertyInfo(UE::MovieScene::FInterrogationKey Key) const`
- L102 _public function_ `void FindEntityIDs(UE::MovieScene::FInterrogationKey Key, TArray<FMovieSceneEntityID>& OutEntityIDs) const`
- L109 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L110 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L112 _private prototype_ `bool PropertySupportsFastPath(TArrayView<const FMovieSceneEntityID> Inputs, FPropertyInfo* Output) const;`
- L113 _private prototype_ `UClass* ResolveBlenderClass(const UE::MovieScene::FPropertyDefinition& PropertyDefinition, TArrayView<const FMovieSceneEntityID> Inputs) const;`
- L114 _private prototype_ `UE::MovieScene::FPropertyRecomposerPropertyInfo FindPropertyFromSource(FMovieSceneEntityID EntityID, UObject* Object) const;`
- L118 _private member_ `static constexpr uint16 INVALID_BLEND_CHANNEL = uint16(-1);`
- L120 _private member_ `UE::MovieScene::TOverlappingEntityTracker<FPropertyInfo, UE::MovieScene::FInterrogationKey> PropertyTracker;`
- L121 _private member_ `UE::MovieScene::FComponentMask CleanFastPathMask;`
- L122 _private member_ `UE::MovieScene::FBuiltInComponentTypes* BuiltInComponents;`
- L123 _private member_ `UE::MovieScene::FPropertyRecomposerImpl RecomposerImpl;`
- L127 _function_ `template<typename PropertyTraits> UE::MovieScene::TRecompositionResult<typename PropertyTraits::StorageType> UMovieSceneInterrogatedPropertyInstantiatorSystem::RecomposeBlendOperational(const UE::MovieScene::TPropertyComponents<PropertyTraits>& Components, const UE::MovieScene::FDecompositionQuery& InQuery, const typename PropertyTraits::StorageType& InCurrentValue)`

#### struct `UMovieSceneInterrogatedPropertyInstantiatorSystem::FPropertyInfo`  
`struct FPropertyInfo`  
_L78-90_
- L80 _public function_ `FPropertyInfo() : BlendChannel(INVALID_BLEND_CHANNEL)`
- L84 _public member_ `TWeakObjectPtr<UMovieSceneBlenderSystem> Blender;` — POinter to the blender system to use for this property, if its blended
- L85 _public member_ `UE::MovieScene::FInterrogationChannel InterrogationChannel;`
- L87 _public member_ `UE::MovieScene::FMovieSceneEntityID PropertyEntityID;` — The entity that contains the property component itself. For fast path properties this is the actual child entity produced from the bound object instantiators.
- L89 _public member_ `uint16 BlendChannel;` — Blend channel allocated from Blender, or INVALID_BLEND_CHANNEL if unblended.

### `Source/Runtime/MovieSceneTracks/Public/EntitySystem/Interrogation/MovieSceneInterrogationLinker.h` (Public)


#### struct `UE::MovieScene::FInterrogationParams`  
`struct FInterrogationParams`  
_L35-45_
- L37 _public member_ `FFrameTime Time;`
- L39 _public function_ `FInterrogationParams(FFrameTime InTime) : Time(InTime)`
- L42 _public function_ `FInterrogationParams(FFrameNumber InTime) : Time(InTime)`

#### class `UE::MovieScene::FInterrogationChannels`  
`class FInterrogationChannels`  
_L72-270_
- desc: A class specialized for interrogating Sequencer entity data without applying any state to objects. Currently only tracks within the same time-base are supported. Will not link systems that are in the custom "ExcludedFromInterrogation" category. Multiple different outputs can be interrogated simultaneously by Importing tracks onto separate channels allocated through AllocateChannel. Systems may implement their own interrogation logic that can be run after updates to allow third-party interrogation behavior for specific channels or time. Example usage: Interrogator.ImportTrack(MyTrack, FInterrogationChannel::Default()); for (int32 FrameNumber = 0; FrameNumber < 100; ++FrameNumber) Interrogator.InterrogateTime(FrameNumber); Interrogator.Update(); UMyTrackSystem* MySystem = Interrogator.GetLinker()->FindSystem<UMyTrackSystem>(); if (MySystem) { TArray<DataType> OutData; MySystem->Interrogate(FInterogationKey::Default(), OutData); }
- L76 _public prototype_ `FInterrogationChannels();`
- L77 _public prototype_ `~FInterrogationChannels();`
- L79 _public prototype_ `void Reset();`
- L81 _public function_ `const FSparseInterrogationChannelInfo& GetSparseChannelInfo() const`
- L92 _public prototype_ `FInterrogationChannel AllocateChannel(FInterrogationChannel ParentChannel, const FMovieScenePropertyBinding& PropertyBinding);` — Allocate a new interrogation channel that can be used to uniquely identify groups of tracks that animate the same property or output. @param ParentChannel     The channel that should be considered this channel's parent, or FInterrogationChannel::Invalid if there is none @return A new interrogation channel
- L98 _public prototype_ `FInterrogationChannel AllocateChannel(UObject* Object, const FMovieScenePropertyBinding& PropertyBinding);` — Allocate a new interrogation channel that relates to a specific object
- L104 _public prototype_ `FInterrogationChannel AllocateChannel(UObject* Object, FInterrogationChannel ParentChannel, const FMovieScenePropertyBinding& PropertyBinding);` — Allocate a new interrogation channel that relates to a specific object
- L114 _public prototype_ `FInterrogationChannel AllocateUnboundChannel(FInterrogationChannel ParentChannel, const FTransform& CurrentValueLocalSpace);` — Allocate a new channel for a set of transform tracks that isn't bound to any particular object (but can still exist within a hierarchy) @param ParentChannel     The channel that should be considered this channel's parent, or FInterrogationChannel::Invalid if there is none @param CurrentValue      A value to use if this channel has now animated data after the interrogation @return A new interrogation channel that can be passed to ImportUnboundTrack
- L125 _public prototype_ `FInterrogationChannel ImportTransformHierarchy(USceneComponent* SceneComponent);` — Import the entire transform hierarchy for the specified component, including all attached parents and tracks relating to them. @param SceneComponent    The scene component to import. A new channel will be allocated for this if one does not already exist. @param InPlayer          The player interface to use for looking up object binding IDs pertaining to scene components or actors @param SequenceID        The current sequence ID for the interrogation @return The channel that was either pre-existing or allocated for SceneComponent
- L134 _public prototype_ `FInterrogationChannel FindChannel(UObject* Object);` — Find the existing interrogation channel for the specified object @param Object    The object to find a channel for @return The (potentially invalid) interrogation channel that the specified object is on
- L142 _public prototype_ `void ActivateChannel(FInterrogationChannel InChannel);` — Called to activate the specified channel. Inactive channels will only ever use their object's current value. @param InChannel The channel to activate
- L149 _public prototype_ `void DeactivateChannel(FInterrogationChannel InChannel);` — Called to deactivate the specified channel. Inactive channels will only ever use their object's current value. @param InChannel The channel to deactivate
- L158 _public prototype_ `int32 AddInterrogation(const FInterrogationParams& Params);` — Add a new time to interrogate this linker at, in the time-base of the imported tracks. @param Params    The desired time to interrogate at @return A unique index identifier for the specified time, or INDEX_NONE if the maximum number have been reached
- L166 _public function_ `int32 GetNumChannels() const` — Retrieve the number of channels allocated
- L175 _public function_ `TArrayView<const FInterrogationParams> GetInterrogations() const` — Retrieve the current interrogations
- L188 _public prototype_ `void QueryLocalSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, USceneComponent* SceneComponent, TArray<FIntermediate3DTransform>& OutTransforms) const;` — Query local space transforms @param SceneComponent    The scene component to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L196 _public prototype_ `void QueryLocalSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, FInterrogationChannel InChannel, TArray<FIntermediate3DTransform>& OutTransforms) const;` — Query local space transforms @param InChannel         The channel to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L203 _public prototype_ `void QueryLocalSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, TSparseArray<TArray<FIntermediate3DTransform>>& OutTransformsByChannel) const;` — Query all local space transforms, even including channels that do not have any variable track data @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L211 _public prototype_ `void QueryLocalSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, const TBitArray<>& ChannelsToQuery, TSparseArray<TArray<FIntermediate3DTransform>>& OutTransformsByChannel) const;` — Query a specific set of channels for their local space transforms as defined by set bits within ChannelsToQuery @param ChannelsToQuery         Bit array containing set bits for each channel to query @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L221 _public prototype_ `void QueryWorldSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, USceneComponent* SceneComponent, TArray<FTransform>& OutTransforms) const;` — Query world space transforms for a component @param SceneComponent    The scene component to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L229 _public prototype_ `void QueryWorldSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, FInterrogationChannel InChannel, TArray<FTransform>& OutTransforms) const;` — Query world space transforms for a channel @param InChannel         The channel to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L236 _public prototype_ `void QueryWorldSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, TSparseArray<TArray<FTransform>>& OutTransformsByChannel) const;` — Query all world space transforms, even including channels that do not have any variable track data @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L244 _public prototype_ `void QueryWorldSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, const TBitArray<>& ChannelsToQuery, TSparseArray<TArray<FTransform>>& OutTransformsByChannel) const;` — Query a specific set of channels for their world space transforms as defined by set bits within ChannelsToQuery @param ChannelsToQuery         Bit array containing set bits for each channel to query @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L246 _public prototype_ `void QueryTransformOrigins(UMovieSceneEntitySystemLinker* Linker, const FMovieSceneSequenceHierarchy* Hierarchy, TArray<FTransform>& OutTransformOrigins, TArray<FMovieSceneSequenceID>& SubsequenceHierarchy, const UObject* InstanceData) const;`
- L252 _private prototype_ `template<typename GetOutputForChannelType> void QueryWorldSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, const TBitArray<>& ChannelsToQuery, GetOutputForChannelType&& OnGetOutputForChannel) const;` — Query implementation functions
- L255 _private prototype_ `template<typename GetOutputForChannelType> void QueryLocalSpaceTransforms(UMovieSceneEntitySystemLinker* Linker, const TBitArray<>& ChannelsToQuery, GetOutputForChannelType&& OnGetOutputForChannel) const;`
- L260 _protected member_ `TMap<FObjectKey, FInterrogationChannel> ObjectToChannel;` — Map from an object to its interrogation channel
- L263 _protected member_ `FSparseInterrogationChannelInfo SparseChannelInfo;` — Array of information pertaining to a given channel
- L266 _protected member_ `TBitArray<> ActiveChannelBits;` — BitArray containing set bits for any channel that has data associated with it. The number of bits (0 or 1) in this array defines how many channels are allocated
- L269 _protected member_ `TArray<FInterrogationParams> Interrogations;` — An array of interrogation times

#### class `UE::MovieScene::FSystemInterrogator`  
`class FSystemInterrogator : FGCObject , IInterrogationExtension`  
_L274-652_
- inherits: `FGCObject,IInterrogationExtension`
- L279 _public prototype_ `FSystemInterrogator();`
- L280 _public prototype_ `~FSystemInterrogator();`
- L286 _public prototype_ `static EEntitySystemCategory GetInterrogationCategory();` — Gets the custom system category for interrogation-specific systems
- L292 _public prototype_ `static EEntitySystemCategory GetExcludedFromInterrogationCategory();` — Gets the custom system category for systems who should be excluded from interrogation linkers
- L298 _public function_ `FInterrogationChannel AllocateChannel(UObject* Object, const FMovieScenePropertyBinding& PropertyBinding)` — Allocate a new interrogation channel that relates to a specific object
- L313 _public prototype_ `void ImportTrack(UMovieSceneTrack* Track, FInterrogationChannel InChannel, FMovieSceneSequenceID SequenceID = MovieSceneSequenceID::Invalid);` — Import a track into this linker. This will add the track to the linker's evaluation field and cause entities to be created for it at each interrogation channel (if it is relevant at such times) Must be called before InterrogateTime() and Update(). @param Track      The track to import @param InChannel  The channel to import this track onto. FInterrogationChannel::Default() can be used if this interrogator is only being used for a single output. @param SequenceID The SequenceID of the subsequence if importing one.
- L326 _public prototype_ `void ImportTrack(UMovieSceneTrack* Track, const FGuid& ObjectBindingID, FInterrogationChannel InChannel, FMovieSceneSequenceID SequenceID = MovieSceneSequenceID::Invalid);` — Import a track into this linker. This will add the track to the linker's evaluation field and cause entities to be created for it at each interrogation channel (if it is relevant at such times) Must be called before InterrogateTime() and Update(). @param Track            The track to import @param ObjectBindingID  The binding ID for the object binding that this track resides within @param InChannel        The channel to import this track onto. FInterrogationChannel::Default() can be used if this interrogator is only being used for a single output. @param SequenceID	   The SequenceID of the subsequence if importing one.
- L337 _public prototype_ `FInterrogationChannel ImportTransformHierarchy(USceneComponent* SceneComponent, IMovieScenePlayer* InPlayer, FMovieSceneSequenceID SequenceID);` — Import the entire transform hierarchy for the specified component, including all attached parents and tracks relating to them. @param SceneComponent    The scene component to import. A new channel will be allocated for this if one does not already exist. @param InPlayer          The player interface to use for looking up object binding IDs pertaining to scene components or actors @param SequenceID        The current sequence ID for the interrogation @return The channel that was either pre-existing or allocated for SceneComponent
- L348 _public prototype_ `FInterrogationChannel ImportLocalTransforms(USceneComponent* SceneComponent, IMovieScenePlayer* InPlayer, FMovieSceneSequenceID SequenceID);` — Import any transform tracks that relate to the specified scene component, or it's AActor if it is the root @param SceneComponent    The scene component to import. A new channel will be allocated for this if one does not already exist. @param InPlayer          The player interface to use for looking up object binding IDs pertaining to scene components or actors @param SequenceID        The current sequence ID for the interrogation @return The channel that was either pre-existing or allocated for SceneComponent
- L354 _public function_ `void ImportTracks(TArrayView<UMovieSceneTrack* const> Tracks, FInterrogationChannel InChannel)` — Import multiple tracks into this linker. See ImporTrack above.
- L366 _public function_ `void ImportTracks(TArrayView<UMovieSceneTrack* const> Tracks, const FGuid& ObjectBindingID, FInterrogationChannel InChannel)` — Import multiple tracks into this linker. See ImporTrack above.
- L381 _public prototype_ `int32 AddInterrogation(const FInterrogationParams& Params);` — Add a new time to interrogate this linker at, in the time-base of the imported tracks. @param Params    The desired time to interrogate at @return A unique index identifier for the specified time, or INDEX_NONE if the maximum number have been reached
- L387 _public prototype_ `void Update();` — Flush this interrogator by running all the systems relevant to the current data and populating the interrogation outputs.
- L393 _public prototype_ `void Reset();` — Reset this linker back to its original state
- L401 _public prototype_ `void TrackImportedEntities(bool bInTrackImportedEntities);` — Indicate that consumers of this class require a reverse-lookup table for imported entities to be maintained such that the various FindEntity functions can be called. (Not enabled by default due to performance cost with high interrogation counts)
- L408 _public prototype_ `FMovieSceneEntityID FindEntityFromOwner(FInterrogationKey InterrogationKey, UObject* Owner, uint32 EntityID) const;` — Find an entity given the entity's owner. @note: Must call TrackImportedEntities(true) prior to calling ImportTrack for this function to return the correct entity
- L414 _public function_ `UMovieSceneEntitySystemLinker* GetLinker() const` — Access the underlying linker used for interrogation.
- L423 _public function_ `int32 GetNumChannels() const` — Retrieve the number of channels allocated
- L432 _public function_ `TArrayView<const FInterrogationParams> GetInterrogations() const` — Retrieve the current interrogations
- L439 _private prototype_ `void FindPropertyOutputEntityIDs(const FPropertyDefinition& PropertyDefinition, FInterrogationChannel Channel, TArray<FMovieSceneEntityID>& OutEntityIDs) const;`
- L449 _public function_ `void QueryLocalSpaceTransforms(USceneComponent* SceneComponent, TArray<FIntermediate3DTransform>& OutTransforms) const` — Query local space transforms @param SceneComponent    The scene component to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L460 _public function_ `void QueryLocalSpaceTransforms(FInterrogationChannel InChannel, TArray<FIntermediate3DTransform>& OutTransforms) const` — Query local space transforms @param InChannel         The channel to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L470 _public function_ `void QueryLocalSpaceTransforms(TSparseArray<TArray<FIntermediate3DTransform>>& OutTransformsByChannel) const` — Query all local space transforms, even including channels that do not have any variable track data @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L481 _public function_ `void QueryLocalSpaceTransforms(const TBitArray<>& ChannelsToQuery, TSparseArray<TArray<FIntermediate3DTransform>>& OutTransformsByChannel) const` — Query a specific set of channels for their local space transforms as defined by set bits within ChannelsToQuery @param ChannelsToQuery         Bit array containing set bits for each channel to query @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L494 _public function_ `void QueryWorldSpaceTransforms(USceneComponent* SceneComponent, TArray<FTransform>& OutTransforms) const` — Query world space transforms for a component @param SceneComponent    The scene component to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L505 _public function_ `void QueryWorldSpaceTransforms(FInterrogationChannel InChannel, TArray<FTransform>& OutTransforms) const` — Query world space transforms for a channel @param InChannel         The channel to query @param OutTransforms     Array to output transforms into, one per Interrogation
- L515 _public function_ `void QueryWorldSpaceTransforms(TSparseArray<TArray<FTransform>>& OutTransformsByChannel) const` — Query all world space transforms, even including channels that do not have any variable track data @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L526 _public function_ `void QueryWorldSpaceTransforms(const TBitArray<>& ChannelsToQuery, TSparseArray<TArray<FTransform>>& OutTransformsByChannel) const` — Query a specific set of channels for their world space transforms as defined by set bits within ChannelsToQuery @param ChannelsToQuery         Bit array containing set bits for each channel to query @param OutTransformsByChannel  Sparse array to receive transforms allocated by their Channel index
- L540 _public function_ `template<typename PropertyTraits> void QueryPropertyValues(const TPropertyComponents<PropertyTraits>& InPropertyComponents, TArray<typename PropertyTraits::StorageType>& OutValues) const` — Query the computed value of an animated property. See the other QueryPropertyValues method description. @param InPropertyComponent		The type of property being animated on the default channel. @param OutValues					The animated values, one for each interrogation time.
- L556 _public function_ `template<typename PropertyTraits> void QueryPropertyValues(const TPropertyComponents<PropertyTraits>& InPropertyComponents, FInterrogationChannel InChannel, TArray<typename PropertyTraits::StorageType>& OutValues) const` — Query the computed value of an animated property. All the tracks imported on the given channel are expected to be animating a property of the type described by the InPropertyComponents parameter. @param InPropertyComponent		The type of property being animated on the given channel. @param InChannel					The channel on which the property is being animated. @param OutValues					The animated values, one for each interrogation time.
- L581 _public function_ `void QueryTransformOrigins(TArray<FTransform>& OutTransformOrigins, TArray<FMovieSceneSequenceID>& SubsequenceHierarchy, const UObject* InstanceData) const` — Query the transform origin of a subsection based on the imported hiearchy @param OutTransformOrigins	The interrogated transforms for the currently focused sequence. @param SubsequenceHierarchy	The currently focused sequence hierarchy @param InstanceData			The object that contains the origin overrides for the world context object of the root sequence.
- L588 _public function_ `const FSparseInterrogationChannelInfo& GetSparseChannelInfo() const override`
- L593 _public function_ `virtual const FMovieSceneSequenceHierarchy* GetHierarchy() const override`
- L598 _public function_ `void SetHierarchy(FMovieSceneSequenceHierarchy* InHierarchy)`
- L608 _private prototype_ `void ImportTransformTracks(const FMovieSceneBinding& Binding, FInterrogationChannel Channel);` — Import transform tracks from this binding
- L613 _private prototype_ `void InterrogateEntity(int32 InterrogationIndex, const FMovieSceneEvaluationFieldEntityQuery& Query);` — Import an entity for the specified query and index
- L618 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector);`
- L619 _private prototype_ `virtual FString GetReferencerName() const;`
- L624 _protected member_ `FInterrogationChannels Channels;` — Object <-> Channel tracker
- L627 _protected member_ `FMovieSceneEvaluationFieldEntitySet EntitiesScratch;` — Scratch buffer used for generating entities for interrogation times
- L630 _protected member_ `FMovieSceneEntityComponentField EntityComponentField;` — Entity component field containing all the entity owners relevant at specific times
- L633 _protected member_ `TUniquePtr<FSystemInterrogatorEntityTracker> EntityTracker;` — Tracker class that is used for keeping track of imported entities
- L636 _protected member_ `TObjectPtr<UMovieSceneEntitySystemLinker> Linker;` — The linker we own
- L639 _protected member_ `TSharedPtr<FInitialValueCache> InitialValueCache;` — Initial value cache
- L642 _protected member_ `FMovieSceneSequenceHierarchy* Hierarchy;` — SubSection Hiearchy, for interrogating subsequence data e.g. subsequence transform origins
- L651 _protected member_ `TSparseArray<FExtraMetaData> ExtraMetaData;`

#### struct `UE::MovieScene::FSystemInterrogator::FExtraMetaData`  
`struct FExtraMetaData`  
_L645-650_
- desc: Array of shared extra metadata on entities
- L647 _public member_ `UE::MovieScene::FInterrogationInstance InterrogationInstance;`
- L648 _public member_ `UE::MovieScene::FInterrogationChannel InterrogationChannel;`
- L649 _public member_ `FMovieSceneSequenceID InterrogationSequenceID;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L28 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Evaluation/CameraCutPlaybackCapability.h` (Public)


#### struct `UE::MovieScene::FOnCameraCutUpdatedParams`  
`struct FOnCameraCutUpdatedParams`  
_L16-21_
- desc: Parameter struct for notifying a playback client that a camera cut has happened.
- L18 _public member_ `AActor* ViewTarget = nullptr;`
- L19 _public member_ `UCameraComponent* ViewTargetCamera = nullptr;`
- L20 _public member_ `bool bIsJumpCut = true;`

#### struct `UE::MovieScene::FCameraCutPlaybackCapability`  
`struct FCameraCutPlaybackCapability`  
_L26-46_
- desc: Playback capability for sequences that can run camera cuts.
- L31 _public function_ `virtual bool ShouldUpdateCameraCut()` — Whether the associated sequence should execute camera cuts
- L34 _public function_ `virtual float GetCameraBlendPlayRate()` — The play rate at which to run camera blends
- L37 _public function_ `virtual TOptional<EAspectRatioAxisConstraint> GetAspectRatioAxisConstraintOverride()` — Whether the associated sequence requires a custom aspect ratio axis constraint
- L40 _public function_ `virtual void OnCameraCutUpdated(const FOnCameraCutUpdatedParams& Params)` — Called when a camera cut has happened
- L44 _public function_ `virtual bool ShouldRestoreEditorViewports()` — Whether the editor should cache the pre-animated viewport position

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Evaluation/MovieSceneBaseCacheTemplate.h` (Public)


#### struct `FMovieSceneBaseCacheSectionTemplateParameters`  
`struct FMovieSceneBaseCacheSectionTemplateParameters`  
_L11-30_
- reflection: `USTRUCT()`
- desc: Base cache parameters that will be used for all the base cache sections
- L14 _public function_ `FMovieSceneBaseCacheSectionTemplateParameters()`
- L15 _public function_ `FMovieSceneBaseCacheSectionTemplateParameters(FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime) : SectionStartTime(InSectionStartTime) , SectionEndTime(InSectionEndTime)`
- L21 _public prototype_ `float MapTimeToAnimation(const FMovieSceneBaseCacheParams& BaseParams, float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L25 _public member_ `FFrameNumber SectionStartTime;` — `UPROPERTY()` — Section start time
- L29 _public member_ `FFrameNumber SectionEndTime;` — `UPROPERTY()` — Section end time

### `Source/Runtime/MovieSceneTracks/Public/Evaluation/MovieSceneCameraShakePreviewer.h` (Public)


#### struct `FCameraShakePreviewerAddParams`  
`struct FCameraShakePreviewerAddParams`  
_L17-33_
- L20 _public member_ `TSubclassOf<UCameraShakeBase> ShakeClass;` — The class of the shake.
- L23 _public member_ `TObjectPtr<const UCameraShakeSourceComponent> SourceComponent;` — Optional shake source.
- L26 _public member_ `float GlobalStartTime;` — Start time of the shake, for scrubbing.
- L29 _public member_ `float Scale = 1.f;` — Parameters to be passed to the shake's start method.
- L30 _public member_ `ECameraShakePlaySpace PlaySpace = ECameraShakePlaySpace::CameraLocal;`
- L31 _public member_ `FRotator UserPlaySpaceRot = FRotator::ZeroRotator;`
- L32 _public member_ `TOptional<float> DurationOverride;`

#### class `FCameraShakePreviewer`  
`class FCameraShakePreviewer : public FGCObject, public TSharedFromThis<FCameraShakePreviewer>`  
_L38-104_
- inherits: `FGCObject,TSharedFromThis<FCameraShakePreviewer>`
- desc: A class that owns a gameplay camera shake manager, so that we can us it to preview shakes in editor.
- L41 _public typedef_ `using FViewportFilter = TFunctionRef<bool(FLevelEditorViewportClient*)>;`
- L43 _public prototype_ `FCameraShakePreviewer(UWorld* InWorld);`
- L44 _public prototype_ `~FCameraShakePreviewer();`
- L46 _public function_ `UWorld* GetWorld() const`
- L48 _public prototype_ `void ModifyView(FEditorViewportViewModifierParams& Params);`
- L50 _public prototype_ `void RegisterViewModifiers(bool bIgnoreDuplicateRegistration = false);`
- L51 _public prototype_ `void RegisterViewModifiers(FViewportFilter InViewportFilter, bool bIgnoreDuplicateRegistration = false);`
- L52 _public prototype_ `void UnRegisterViewModifiers();`
- L54 _public prototype_ `void RegisterViewModifier(FLevelEditorViewportClient* ViewportClient, bool bIgnoreDuplicateRegistration = false);`
- L55 _public prototype_ `void UnRegisterViewModifier(FLevelEditorViewportClient* ViewportClient);`
- L57 _public prototype_ `void Update(float DeltaTime, bool bIsPlaying);`
- L58 _public prototype_ `void Scrub(float ScrubTime);`
- L60 _public prototype_ `UCameraShakeBase* AddCameraShake(const FCameraShakePreviewerAddParams& Params);`
- L61 _public prototype_ `void RemoveCameraShake(UCameraShakeBase* ShakeInstance);`
- L62 _public prototype_ `void RemoveAllCameraShakesFromSource(const UCameraShakeSourceComponent* SourceComponent);`
- L63 _public prototype_ `void RemoveAllCameraShakes();`
- L65 _public function_ `int32 NumActiveCameraShakes() const`
- L66 _public prototype_ `void GetActiveCameraShakes(TArray<FActiveCameraShakeInfo>& ActiveCameraShakes) const;`
- L68 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L72 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L73 _private function_ `virtual FString GetReferencerName() const override`
- L76 _private prototype_ `void OnModifyView(FEditorViewportViewModifierParams& Params);`
- L77 _private prototype_ `void OnLevelViewportClientListChanged();`
- L79 _private prototype_ `void ResetModifiers();`
- L82 _private member_ `UWorld* World;`
- L84 _private member_ `TArray<FLevelEditorViewportClient*> RegisteredViewportClients;`
- L93 _private member_ `TArray<FPreviewCameraShakeInfo> ActiveShakes;`
- L95 _private member_ `TOptional<float> LastDeltaTime;`
- L96 _private member_ `TOptional<float> LastScrubTime;`
- L98 _private member_ `FVector LastLocationModifier;`
- L99 _private member_ `FRotator LastRotationModifier;`
- L100 _private member_ `float LastFOVModifier;`
- L102 _private member_ `TArray<FPostProcessSettings> LastPostProcessSettings;`
- L103 _private member_ `TArray<float> LastPostProcessBlendWeights;`

#### struct `FCameraShakePreviewer::FPreviewCameraShakeInfo`  
`struct FPreviewCameraShakeInfo`  
_L86-92_
- L88 _public member_ `FCameraShakeBaseStartParams StartParams;`
- L89 _public member_ `TObjectPtr<UCameraShakeBase> ShakeInstance;`
- L90 _public member_ `TWeakObjectPtr<const UCameraShakeSourceComponent> SourceComponent;`
- L91 _public member_ `float StartTime;`

### `Source/Runtime/MovieSceneTracks/Public/Evaluation/MovieSceneParameterTemplate.h` (Public)


#### struct `FEvaluatedParameterSectionValues`  
`struct FEvaluatedParameterSectionValues`  
_L18-41_
- desc: Evaluation structure that holds evaluated values
- L20 _public prototype_ `FEvaluatedParameterSectionValues() = default;`
- L22 _public prototype_ `FEvaluatedParameterSectionValues(FEvaluatedParameterSectionValues&&) = default;`
- L23 _public prototype_ `FEvaluatedParameterSectionValues& operator=(FEvaluatedParameterSectionValues&&) = default;`
- L26 _public prototype_ `FEvaluatedParameterSectionValues(const FEvaluatedParameterSectionValues&) = delete;` — Non-copyable
- L27 _public prototype_ `FEvaluatedParameterSectionValues& operator=(const FEvaluatedParameterSectionValues&) = delete;`
- L30 _public member_ `TArray<FScalarParameterNameAndValue, TInlineAllocator<2>> ScalarValues;` — Array of evaluated scalar values
- L32 _public member_ `TArray<FBoolParameterNameAndValue, TInlineAllocator<2>> BoolValues;` — Array of evaluated bool values
- L34 _public member_ `TArray<FVector2DParameterNameAndValue, TInlineAllocator<2>> Vector2DValues;` — Array of evaluated vector2D values
- L36 _public member_ `TArray<FVectorParameterNameAndValue, TInlineAllocator<2>> VectorValues;` — Array of evaluated vector values
- L38 _public member_ `TArray<FColorParameterNameAndValue, TInlineAllocator<2>> ColorValues;` — Array of evaluated color values
- L40 _public member_ `TArray<FTransformParameterNameAndValue, TInlineAllocator<2>> TransformValues;` — Array of evaluated transform values

#### struct `FMovieSceneParameterSectionTemplate`  
`struct FMovieSceneParameterSectionTemplate : public FMovieSceneEvalTemplate`  
_L45-83_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneEvalTemplate`
- desc: Template that performs evaluation of parameter sections
- L49 _public function_ `FMovieSceneParameterSectionTemplate()`
- L54 _protected prototype_ `FMovieSceneParameterSectionTemplate(const UMovieSceneParameterSection& Section);` — Protected constructor to initialize from a parameter section
- L57 _protected prototype_ `void EvaluateCurves(const FMovieSceneContext& Context, FEvaluatedParameterSectionValues& OutValues) const;` — Evaluate our curves, outputting evaluated values into the specified container
- L63 _protected member_ `TArray<FScalarParameterNameAndCurve> Scalars;` — `UPROPERTY()` — The scalar parameter names and their associated curves.
- L67 _protected member_ `TArray<FBoolParameterNameAndCurve> Bools;` — `UPROPERTY()` — The bool parameter names and their associated curves.
- L71 _protected member_ `TArray<FVector2DParameterNameAndCurves> Vector2Ds;` — `UPROPERTY()` — The vector parameter names and their associated curves.
- L75 _protected member_ `TArray<FVectorParameterNameAndCurves> Vectors;` — `UPROPERTY()` — The vector parameter names and their associated curves.
- L79 _protected member_ `TArray<FColorParameterNameAndCurves> Colors;` — `UPROPERTY()` — The color parameter names and their associated curves.
- L82 _protected member_ `TArray<FTransformParameterNameAndCurves> Transforms;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Evaluation/ViewportSettingsPlaybackCapability.h` (Public)


#### struct `EMovieSceneViewportParams`  
`struct EMovieSceneViewportParams`  
_L12-35_
- L14 _public function_ `EMovieSceneViewportParams()`
- L29 _public member_ `SetViewportParam SetWhichViewportParam;`
- L31 _public member_ `float FadeAmount;`
- L32 _public member_ `FLinearColor FadeColor;`
- L33 _public member_ `FVector ColorScale;`
- L34 _public member_ `bool bEnableColorScaling;`

#### enum `EMovieSceneViewportParams::SetViewportParam`  
`enum SetViewportParam`  
_L21-27_
- L23 _public enumerator_ `SVP_FadeAmount = 0x00000001`
- L24 _public enumerator_ `SVP_FadeColor = 0x00000002`
- L25 _public enumerator_ `SVP_ColorScaling = 0x00000004`
- L26 _public enumerator_ `SVP_All = SVP_FadeAmount | SVP_FadeColor | SVP_ColorScaling`

#### struct `UE::MovieScene::FViewportSettingsPlaybackCapability`  
`struct FViewportSettingsPlaybackCapability`  
_L43-60_
- desc: Playback capability for controlling game and editor viewports.
- L59 _public prototype_ `virtual void GetViewportSettings(TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) const = 0;` — Get the current perspective viewport settings @param ViewportParamMap A map from the viewport client to its settings

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/IMovieSceneTracksModule.h` (Public)


#### enum `EBuiltInEvaluationGroup::Type`  
`enum Type`  
_L12-17_
- L14 _public enumerator_ `PreEvaluation`
- L15 _public enumerator_ `SpawnObjects`
- L16 _public enumerator_ `PostEvaluation`

#### class `IMovieSceneTracksModule`  
`class IMovieSceneTracksModule : public IModuleInterface`  
_L23-52_
- inherits: `IModuleInterface`
- desc: The public interface of the MovieSceneTracks module
- L33 _public function_ `static inline IMovieSceneTracksModule& Get()` — Singleton-like access to IMovieSceneTracksModule @return Returns MovieSceneTracksModule singleton instance, loading the module on demand if needed
- L43 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L51 _public prototype_ `static FName GetEvaluationGroupName(EBuiltInEvaluationGroup::Type InEvalGroup);` — Retrieve the name of an evaluation group

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace EBuiltInEvaluationGroup`

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneAnimationMixerItemInterface.h` (Public)


#### class `UMovieSceneAnimationMixerItemInterface`  
`class UMovieSceneAnimationMixerItemInterface : public UInterface`  
_L16-19_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for items (sections or tracks) that can be added to Animation Mixer tracks. Provides metadata for menu display and visual customization.

#### class `IMovieSceneAnimationMixerItemInterface`  
`class IMovieSceneAnimationMixerItemInterface`  
_L21-43_
- L27 _public function_ `virtual FColor GetMixerItemTint() const` — Color tint when displayed in mixer track
- L30 _public function_ `virtual FText GetDisplayName() const` — Display name for add menu entry
- L33 _public function_ `virtual FText GetDescription() const` — Tooltip description for add menu entry
- L36 _public function_ `virtual FSlateIcon GetIcon() const` — Icon for add menu entry (default: no icon)
- L39 _public function_ `virtual bool SupportsVerticalDragging() const` — If this item supports vertical dragging within the mixer
- L42 _public function_ `virtual bool IsVisibleInAddSectionMenu() const` — Some items such as decorations and transitions are not added through the section add menu

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneAnimationRotationUtils.h` (Public)


#### enum `UE::MovieScene::ERotationOrder`  
`enum class ERotationOrder`  
_L16-19_
- desc: Euler decomposition order for rotation matching. When matching specific rotation axes, the matched axis should be decomposed first to avoid gimbal lock artifacts on the axes we care about.
- L18 _public enumerator_ `XYZ`
- L18 _public enumerator_ `XYZ`
- L18 _public enumerator_ `XYZ`
- L18 _public enumerator_ `XYZ`
- L18 _public enumerator_ `XYZ`
- L18 _public enumerator_ `XYZ`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieScene` (scope `UE`)
- L23 _function_ `inline ERotationOrder FindBestRotationOrder(bool bMatchRoll, bool bMatchPitch, bool bMatchYaw)` (scope `UE::MovieScene`) — Choose the decomposition order that puts the matched axis first. Yaw (Z) is the most common match axis, so YXZ is the default when matching yaw.
- L36 _function_ `inline FQuat QuatFromEuler(const FVector& XYZAnglesInDegrees, ERotationOrder RotationOrder)` (scope `UE::MovieScene`)
- L92 _function_ `inline FVector EulerFromQuat(const FQuat& Rotation, ERotationOrder RotationOrder)` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneHitProxy.h` (Public)


#### struct `HMovieSceneKeyProxy`  
`struct HMovieSceneKeyProxy : public HHitProxy`  
_L11-24_
- inherits: `HHitProxy`
- L13 _public prototype_ `DECLARE_HIT_PROXY( );`
- L16 _public member_ `TWeakObjectPtr<UMovieSceneTrack> MovieSceneTrack;` — The track that contains the section
- L19 _public member_ `FTrajectoryKey Key;` — The trajectory key data
- L21 _public prototype_ `HMovieSceneKeyProxy(class UMovieSceneTrack* InTrack, const FTrajectoryKey& InKey);`
- L23 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneMixedAnimationTarget.h` (Public)


#### struct `FMovieSceneMixedAnimationTarget`  
`struct FMovieSceneMixedAnimationTarget`  
_L19-44_
- reflection: `USTRUCT(meta=(DisplayName="Automatic"))`
- desc: Defines a Mixed Anim Target that animation pose-producing tracks can send pose-producing tasks to. Multiple pose producing tasks sent to the same target will be chained and mixed based on priority, pose weight, masks, and sequence hierarchy. Inheriting from this struct allows the user to create new animation target types with their own metadata and custom component types. Coupled with a custom component type, these mixer pose results can be read from a custom Movie Scene ECS system and passed as appropriate to an anim system. If no target struct is assigned, a default animation target will be assigned based on the makeup of the object being animated.
- L23 _public prototype_ `virtual ~FMovieSceneMixedAnimationTarget() = default;`
- L30 _public function_ `bool HasFiredWarningForTarget() const`
- L32 _public function_ `void SetHasFiredWarningForTarget(bool bNewHasFiredState)`
- L36 _public function_ `virtual const FSlateBrush* GetIcon() const` — Get the icon to display for this target type in the Sequencer outliner. Returns nullptr for no icon.
- L39 _public function_ `virtual FText GetShortDisplayName() const` — Get a short display name for this target (e.g., "Automatic", specific target node name, etc.)
- L43 _private member_ `bool bHasFiredWarningForTarget = false;`

#### Free symbols / members of external scopes

- L25 _function_ `inline friend uint32 GetTypeHash(const FMovieSceneMixedAnimationTarget& Target)`

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneSkeletalAnimationRootHitProxy.h` (Public)


#### struct `HMovieSceneSkeletalAnimationRootHitProxy`  
`struct HMovieSceneSkeletalAnimationRootHitProxy : public HHitProxy`  
_L11-21_
- inherits: `HHitProxy`
- L13 _public prototype_ `DECLARE_HIT_PROXY( );`
- L15 _public member_ `TWeakObjectPtr<UMovieSceneSkeletalAnimationSection> AnimSection;`
- L16 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelMeshComp;`
- L18 _public prototype_ `HMovieSceneSkeletalAnimationRootHitProxy(UMovieSceneSkeletalAnimationSection* InSection, USkeletalMeshComponent* InSkelMeshComp);`
- L20 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksComponentTypes.h` (Public)


#### struct `UE::MovieScene::TPropertyMatch`  
`template<> struct TPropertyMatch<FIntermediate3DTransform>`  
_L42-48_
- L44 _public function_ `static bool SupportsProperty(const FProperty& InProperty)`

#### struct `FPerlinNoiseParams`  
`struct FPerlinNoiseParams`  
_L53-74_
- reflection: `USTRUCT()`
- desc: Component data for Perlin Noise channels
- L59 _public member_ `float Frequency;` — `UPROPERTY(EditAnywhere, Category="Perlin Noise")` — The frequency of the noise, i.e. how many times per second does the noise peak
- L63 _public member_ `double Amplitude;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise")` — The amplitude of the noise, which will vary between [-Amplitude, +Amplitude]
- L67 _public member_ `float Offset;` — `UPROPERTY(EditAnywhere, Category = "Perlin Noise")` — Starting offset, in seconds, into the noise pattern
- L69 _public prototype_ `FPerlinNoiseParams();`
- L70 _public prototype_ `FPerlinNoiseParams(float InFrequency, double InAmplitude);`
- L73 _public prototype_ `void RandomizeOffset(float InMaxOffset = 100.f);` — Generates a new random offset between [0, InMaxOffset] and sets it

#### struct `FLevelVisibilityComponentData`  
`struct FLevelVisibilityComponentData`  
_L78-84_
- reflection: `USTRUCT()`
- desc: Component data for the level visibility system
- L83 _public member_ `TObjectPtr<const UMovieSceneLevelVisibilitySection> Section = nullptr;` — `UPROPERTY()`

#### struct `FMovieSceneDataLayerComponentData`  
`struct FMovieSceneDataLayerComponentData`  
_L88-94_
- reflection: `USTRUCT()`
- desc: Component data for the data layer system
- L93 _public member_ `TObjectPtr<const UMovieSceneDataLayerSection> Section = nullptr;` — `UPROPERTY()`

#### struct `FConstraintComponentData`  
`struct FConstraintComponentData`  
_L98-105_
- reflection: `USTRUCT()`
- desc: Component data for the constraint system
- L103 _public member_ `FGuid ConstraintID;` — `UPROPERTY()`
- L104 _public member_ `UMovieScene3DTransformSection* Section;`

#### struct `FMovieSceneSkeletalAnimationComponentData`  
`struct FMovieSceneSkeletalAnimationComponentData`  
_L109-115_
- reflection: `USTRUCT()`
- desc: Component data for a skeletal mesh animation
- L114 _public member_ `TObjectPtr<UMovieSceneSkeletalAnimationSection> Section;` — `UPROPERTY()`

#### struct `FMovieSceneAudioComponentData`  
`struct FMovieSceneAudioComponentData`  
_L119-125_
- reflection: `USTRUCT()`
- desc: Component data for audio tracks
- L124 _public member_ `TObjectPtr<UMovieSceneAudioSection> Section = nullptr;` — `UPROPERTY()`

#### struct `FMovieSceneCameraShakeComponentData`  
`struct FMovieSceneCameraShakeComponentData`  
_L129-157_
- reflection: `USTRUCT()`
- desc: Component data for camera shakes
- L135 _public member_ `FMovieSceneCameraShakeSectionData SectionData;` — `UPROPERTY()` — The shake data from the section that created this component
- L139 _public member_ `FFrameNumber SectionStartTime;` — `UPROPERTY()` — The range of the section that created this component
- L141 _public member_ `FFrameNumber SectionEndTime;` — `UPROPERTY()`
- L145 _public member_ `FGuid SectionSignature;` — `UPROPERTY()` — The signature of the source section at the time the shake instance was created
- L147 _public function_ `FMovieSceneCameraShakeComponentData()`
- L149 _public function_ `FMovieSceneCameraShakeComponentData(const FMovieSceneCameraShakeSectionData& InSectionData, const UMovieSceneSection& InSection) : SectionData(InSectionData) , SectionSignature(InSection.GetSignature())`

#### struct `FMovieSceneCameraShakeInstanceData`  
`struct FMovieSceneCameraShakeInstanceData`  
_L166-181_
- reflection: `USTRUCT()`
- desc: Component data for camera shakes created by the shake system This is separate from FMovieSceneCameraShakeComponentData because that one it imported from source shake sections, and our component data here will be preserved on reimported entities.
- L172 _public member_ `TObjectPtr<UCameraShakeBase> ShakeInstance;` — `UPROPERTY()` — Shake instance created by the shake evaluation system
- L176 _public member_ `FGuid SectionSignature;` — `UPROPERTY()` — The signature of the source section at the time the shake instance was created
- L180 _public member_ `bool bManagedByPreviewer = false;` — `UPROPERTY()` — Whether this instance is managed by a shake previewer

#### struct `FMovieSceneAudioInputData`  
`struct FMovieSceneAudioInputData`  
_L190-210_
- reflection: `USTRUCT()`
- desc: Component data for audio tracks inputs This provides the names of the inputs whose values are stored on the same entity using the DoubleResult, StringResult, BoolResult, and IntegerResult components.
- L197 _public member_ `static constexpr int32 NumFloatChannels = sizeof(UE::MovieScene::FBuiltInComponentTypes::FloatChannel) / sizeof(UE::MovieScene::TComponentTypeID<UE::MovieScene::FSourceFloatChannel>);`
- L200 _public member_ `FName FloatInputs[NumFloatChannels];` — `UPROPERTY()`
- L203 _public member_ `FName StringInput;` — `UPROPERTY()`
- L206 _public member_ `FName BoolInput;` — `UPROPERTY()`
- L209 _public member_ `FName IntInput;` — `UPROPERTY()`

#### struct `UE::MovieScene::FSourceActorReferenceChannel`  
`struct FSourceActorReferenceChannel`  
_L217-228_
- L219 _public function_ `FSourceActorReferenceChannel() : Source(nullptr)`
- L223 _public function_ `FSourceActorReferenceChannel(const FMovieSceneActorReferenceChannel* InSource) : Source(InSource)`
- L227 _public member_ `const FMovieSceneActorReferenceChannel* Source;`

#### enum `UE::MovieScene::EActorReferenceType`  
`enum class EActorReferenceType`  
_L230-234_
- L232 _public enumerator_ `ObjectPointer`
- L233 _public enumerator_ `SoftObjectPointer`

#### struct `UE::MovieScene::FActorReferenceComponent`  
`struct FActorReferenceComponent`  
_L236-241_
- L238 _public member_ `FMovieSceneObjectBindingID ObjectBindingID;`
- L239 _public member_ `TWeakObjectPtr<AActor> WeakActor;`
- L240 _public member_ `EActorReferenceType Type = EActorReferenceType::ObjectPointer;`

#### struct `UE::MovieScene::FComponentAttachParamsDestination`  
`struct FComponentAttachParamsDestination`  
_L243-249_
- L245 _public member_ `FName SocketName = NAME_None;`
- L246 _public member_ `FName ComponentName = NAME_None;`
- L248 _public prototype_ `USceneComponent* ResolveAttachment(AActor* InParentActor) const;`

#### struct `UE::MovieScene::FComponentAttachParams`  
`struct FComponentAttachParams`  
_L251-258_
- L253 _public member_ `EAttachmentRule AttachmentLocationRule = EAttachmentRule::KeepRelative;`
- L254 _public member_ `EAttachmentRule AttachmentRotationRule = EAttachmentRule::KeepRelative;`
- L255 _public member_ `EAttachmentRule AttachmentScaleRule = EAttachmentRule::KeepRelative;`
- L257 _public prototype_ `void ApplyAttach(USceneComponent* NewAttachParent, USceneComponent* ChildComponentToAttach, const FName& SocketName) const;`

#### struct `UE::MovieScene::FComponentDetachParams`  
`struct FComponentDetachParams`  
_L260-267_
- L262 _public member_ `EDetachmentRule DetachmentLocationRule = EDetachmentRule::KeepRelative;`
- L263 _public member_ `EDetachmentRule DetachmentRotationRule = EDetachmentRule::KeepRelative;`
- L264 _public member_ `EDetachmentRule DetachmentScaleRule = EDetachmentRule::KeepRelative;`
- L266 _public prototype_ `void ApplyDetach(USceneComponent* NewAttachParent, USceneComponent* ChildComponentToAttach, const FName& SocketName) const;`

#### struct `UE::MovieScene::FAttachmentComponent`  
`struct FAttachmentComponent`  
_L269-275_
- L271 _public member_ `FComponentAttachParamsDestination Destination;`
- L273 _public member_ `FComponentAttachParams AttachParams;`
- L274 _public member_ `FComponentDetachParams DetachParams;`

#### struct `UE::MovieScene::FFadeComponentData`  
`struct FFadeComponentData`  
_L277-281_
- L279 _public member_ `FLinearColor FadeColor;`
- L280 _public member_ `bool bFadeAudio;`

#### struct `UE::MovieScene::FPropertyNotifyComponentData`  
`struct FPropertyNotifyComponentData`  
_L283-288_
- L285 _public member_ `FName NotifyFunctionName;`
- L286 _public member_ `TWeakObjectPtr<UFunction> WeakNotifyFunction;`
- L287 _public member_ `bool bNotifyFunctionCached = false;`

#### struct `UE::MovieScene::FFloatPropertyTraits`  
`struct FFloatPropertyTraits : IPropertyTraits`  
_L290-354_
- inherits: `IPropertyTraits`
- L292 _public member_ `static constexpr bool bIsComposite = false;`
- L294 _public typedef_ `using StorageType = double;`
- L295 _public typedef_ `using CustomAccessorStorageType = float;`
- L297 _public typedef_ `using FloatTraitsImpl = TDirectPropertyTraits<float>;`
- L299 _public function_ `FORCEINLINE static bool SupportsProperty(const FProperty& InProperty)`
- L303 _public function_ `FORCEINLINE static FIntermediatePropertyValue CoercePropertyValue(const FProperty& InProperty, const FSourcePropertyValue& InPropertyValue)`
- L308 _public function_ `FORCEINLINE static void UnpackChannels(float InValue, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues)`
- L313 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, const FCustomPropertyAccessor& BaseCustomAccessor, double& OutValue)`
- L319 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, uint16 PropertyOffset, double& OutValue)`
- L325 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FTrackInstancePropertyBindings* PropertyBindings, double& OutValue)`
- L331 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, const FName& PropertyPath, double& OutValue)`
- L338 _public function_ `static void SetObjectPropertyValue(UObject* InObject, const FCustomPropertyAccessor& BaseCustomAccessor, double InValue)`
- L344 _public function_ `static void SetObjectPropertyValue(UObject* InObject, uint16 PropertyOffset, double InValue)`
- L349 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FTrackInstancePropertyBindings* PropertyBindings, double InValue)`

#### struct `UE::MovieScene::FBoolPropertyTraits`  
`struct FBoolPropertyTraits : IPropertyTraits`  
_L356-440_
- inherits: `IPropertyTraits`
- L358 _public member_ `static constexpr bool bIsComposite = false;`
- L366 _public typedef_ `using StorageType = bool;`
- L367 _public typedef_ `using MetaDataType = TPropertyMetaData<FBoolMetaData>;`
- L369 _public function_ `FORCEINLINE static bool SupportsProperty(const FProperty& InProperty)`
- L373 _public function_ `FORCEINLINE static FIntermediatePropertyValue CoercePropertyValue(const FProperty& InProperty, const FSourcePropertyValue& InPropertyValue)`
- L377 _public function_ `FORCEINLINE static void UnpackChannels(bool bInValue, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues)`
- L383 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FBoolMetaData MetaData, const FCustomPropertyAccessor& BaseCustomAccessor, bool& OutValue)` — Property Value Getters
- L388 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FBoolMetaData MetaData, uint16 PropertyOffset, bool& OutValue)`
- L400 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FBoolMetaData MetaData, FTrackInstancePropertyBindings* PropertyBindings, bool& OutValue)`
- L404 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FBoolMetaData MetaData, const FName& PropertyPath, bool& OutValue)`
- L414 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FBoolMetaData MetaData, const FCustomPropertyAccessor& BaseCustomAccessor, bool InValue)` — Property Value Setters
- L419 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FBoolMetaData MetaData, uint16 PropertyOffset, bool InValue)`
- L436 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FBoolMetaData MetaData, FTrackInstancePropertyBindings* PropertyBindings, bool InValue)`

#### struct `UE::MovieScene::FBoolPropertyTraits::FBoolMetaData`  
`struct FBoolMetaData`  
_L360-365_
- L363 _public member_ `uint8 BitFieldSize = 0;` — Size of the bitfield/bool property in bytes. Must be one of 1(uint8), 2(uint16), 4(uint32), 8(uint64), or 0 signifying that this is not a bitfield, but a regular bool..
- L364 _public member_ `uint8 BitIndex = 0;`

#### struct `UE::MovieScene::FObjectPropertyTraits`  
`struct FObjectPropertyTraits : IPropertyTraits`  
_L442-525_
- inherits: `IPropertyTraits`
- L444 _public member_ `static constexpr bool bIsComposite = false;`
- L452 _public typedef_ `using StorageType = FObjectComponent;`
- L453 _public typedef_ `using MetaDataType = TPropertyMetaData<FObjectMetadata>;`
- L455 _public typedef_ `using ObjectTraitsImpl = TPropertyTraits<UObject*, FObjectComponent>;`
- L457 _public function_ `FORCEINLINE static bool SupportsProperty(const FProperty& InProperty)`
- L461 _public function_ `FORCEINLINE static FIntermediatePropertyValue CoercePropertyValue(const FProperty& InProperty, const FSourcePropertyValue& InPropertyValue)`
- L465 _public function_ `FORCEINLINE static void UnpackChannels(const FObjectComponent& InValue, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues)`
- L471 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FObjectMetadata ObjectMetadata, const FCustomPropertyAccessor& BaseCustomAccessor, FObjectComponent& OutValue)`
- L476 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FObjectMetadata ObjectMetadata, uint16 PropertyOffset, FObjectComponent& OutValue)`
- L480 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FObjectMetadata ObjectMetadata, FTrackInstancePropertyBindings* PropertyBindings, FObjectComponent& OutValue)`
- L484 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FObjectMetadata ObjectMetadata, const FName& PropertyPath, StorageType& OutValue)`
- L489 _public function_ `static bool CanAssignValue(const FObjectMetadata& ObjectMetadata, UObject* DesiredValue)`
- L506 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FObjectMetadata ObjectMetadata, const FCustomPropertyAccessor& BaseCustomAccessor, const FObjectComponent& InValue)`
- L511 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FObjectMetadata ObjectMetadata, uint16 PropertyOffset, const FObjectComponent& InValue)`
- L518 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FObjectMetadata ObjectMetadata, FTrackInstancePropertyBindings* PropertyBindings, const FObjectComponent& InValue)`

#### struct `UE::MovieScene::FObjectPropertyTraits::FObjectMetadata`  
`struct FObjectMetadata`  
_L446-450_
- L448 _public member_ `TObjectPtr<UClass> ObjectClass = UObject::StaticClass();`
- L449 _public member_ `bool bAllowsClear = true;`

#### struct `UE::MovieScene::FActorReferencePropertyTraits`  
`struct FActorReferencePropertyTraits : IPropertyTraits`  
_L527-643_
- inherits: `IPropertyTraits`
- L529 _public member_ `static constexpr bool bIsComposite = false;`
- L536 _public typedef_ `using StorageType = FActorReferenceComponent;`
- L537 _public typedef_ `using MetaDataType = TPropertyMetaData<FActorReferenceMetaData>;`
- L539 _public typedef_ `using ObjectPointerTraitsImpl = TPropertyTraits<TObjectPtr<AActor>, FActorReferenceComponent>;`
- L540 _public typedef_ `using SoftObjectPointerTraitsImpl = TPropertyTraits<TSoftObjectPtr<AActor>, FActorReferenceComponent>;`
- L542 _public function_ `FORCEINLINE static bool SupportsProperty(const FProperty& InProperty)`
- L554 _public function_ `FORCEINLINE static FIntermediatePropertyValue CoercePropertyValue(const FProperty& InProperty, const FSourcePropertyValue& InPropertyValue)`
- L563 _public function_ `FORCEINLINE static void UnpackChannels(const FActorReferenceComponent& InValue, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues)`
- L572 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FActorReferenceMetaData MetaData, const FCustomPropertyAccessor& BaseCustomAccessor, FActorReferenceComponent& OutValue)`
- L577 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FActorReferenceMetaData MetaData, uint16 PropertyOffset, FActorReferenceComponent& OutValue)`
- L589 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FActorReferenceMetaData MetaData, FTrackInstancePropertyBindings* PropertyBindings, FActorReferenceComponent& OutValue)`
- L601 _public function_ `static void GetObjectPropertyValue(const UObject* InObject, FActorReferenceMetaData MetaData, const FName& PropertyPath, StorageType& OutValue)`
- L614 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FActorReferenceMetaData MetaData, const FCustomPropertyAccessor& BaseCustomAccessor, const FActorReferenceComponent& InValue)`
- L619 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FActorReferenceMetaData MetaData, uint16 PropertyOffset, const FActorReferenceComponent& InValue)`
- L631 _public function_ `static void SetObjectPropertyValue(UObject* InObject, FActorReferenceMetaData MetaData, FTrackInstancePropertyBindings* PropertyBindings, const FActorReferenceComponent& InValue)`

#### struct `UE::MovieScene::FActorReferencePropertyTraits::FActorReferenceMetaData`  
`struct FActorReferenceMetaData`  
_L531-534_
- L533 _public member_ `EActorReferenceType Type = EActorReferenceType::ObjectPointer;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes`  
`struct FMovieSceneTracksComponentTypes`  
_L669-833_
- L671 _public prototype_ `~FMovieSceneTracksComponentTypes();`
- L673 _public member_ `TPropertyComponents<FBoolPropertyTraits> Bool;`
- L674 _public member_ `TPropertyComponents<FBytePropertyTraits> Byte;`
- L675 _public member_ `TPropertyComponents<FEnumPropertyTraits> Enum;`
- L676 _public member_ `TPropertyComponents<FIntPropertyTraits> Integer;`
- L677 _public member_ `TPropertyComponents<FFloatPropertyTraits> Float;`
- L678 _public member_ `TPropertyComponents<FDoublePropertyTraits> Double;`
- L679 _public member_ `TPropertyComponents<FColorPropertyTraits> Color;`
- L680 _public member_ `TPropertyComponents<FFloatVectorPropertyTraits> FloatVector;`
- L681 _public member_ `TPropertyComponents<FDoubleVectorPropertyTraits> DoubleVector;`
- L682 _public member_ `TPropertyComponents<FTransformPropertyTraits> Transform;`
- L683 _public member_ `TPropertyComponents<FEulerTransformPropertyTraits> EulerTransform;`
- L684 _public member_ `TPropertyComponents<FComponentTransformPropertyTraits> ComponentTransform;`
- L685 _public member_ `TPropertyComponents<FRotatorPropertyTraits> Rotator;`
- L686 _public member_ `TPropertyComponents<FStringPropertyTraits> String;`
- L687 _public member_ `TPropertyComponents<FTextPropertyTraits> Text;`
- L688 _public member_ `TPropertyComponents<FObjectPropertyTraits> Object;`
- L689 _public member_ `TPropertyComponents<FActorReferencePropertyTraits> ActorReference;`
- L691 _public member_ `TPropertyComponents<FFloatParameterTraits> FloatParameter;`
- L692 _public member_ `TPropertyComponents<FColorParameterTraits> ColorParameter;`
- L694 _public member_ `TComponentTypeID<FSourceDoubleChannel> QuaternionRotationChannel[3];`
- L695 _public member_ `TComponentTypeID<FSourceDoubleChannel> RotatorChannel[3];`
- L697 _public member_ `TComponentTypeID<FConstraintComponentData> ConstraintChannel;`
- L699 _public member_ `TComponentTypeID<FSourceActorReferenceChannel> ActorReferenceChannel;`
- L700 _public member_ `TComponentTypeID<FActorReferenceComponent> ActorReferenceResult;`
- L702 _public member_ `TComponentTypeID<TWeakObjectPtr<USceneComponent>> AttachParent;`
- L703 _public member_ `TComponentTypeID<FAttachmentComponent> AttachComponent;`
- L704 _public member_ `TComponentTypeID<FMovieSceneObjectBindingID> AttachParentBinding;`
- L705 _public member_ `TComponentTypeID<FPerlinNoiseParams> FloatPerlinNoiseChannel;`
- L706 _public member_ `TComponentTypeID<FPerlinNoiseParams> DoublePerlinNoiseChannel;`
- L708 _public member_ `TComponentTypeID<FMovieSceneSkeletalAnimationComponentData> SkeletalAnimation;`
- L710 _public member_ `TComponentTypeID<FComponentMaterialInfo> ComponentMaterialInfo;`
- L712 _public member_ `TComponentTypeID<FName> BoolParameterName;`
- L713 _public member_ `TComponentTypeID<FName> ScalarParameterName;`
- L714 _public member_ `TComponentTypeID<FName> Vector2DParameterName;`
- L715 _public member_ `TComponentTypeID<FName> VectorParameterName;`
- L716 _public member_ `TComponentTypeID<FName> ColorParameterName;`
- L717 _public member_ `TComponentTypeID<FName> TransformParameterName;`
- L719 _public member_ `TComponentTypeID<FName> GenericParameterName;`
- L731 _public member_ `} Parameters;`
- L733 _public member_ `TComponentTypeID<FMaterialParameterInfo> ScalarMaterialParameterInfo;`
- L734 _public member_ `TComponentTypeID<FMaterialParameterInfo> ColorMaterialParameterInfo;`
- L735 _public member_ `TComponentTypeID<FMaterialParameterInfo> VectorMaterialParameterInfo;`
- L737 _public member_ `TComponentTypeID<FObjectComponent> BoundMaterial;`
- L738 _public member_ `TComponentTypeID<TWeakObjectPtr<UMaterialParameterCollection>> MPC;`
- L740 _public member_ `TComponentTypeID<FFadeComponentData> Fade;`
- L742 _public member_ `TComponentTypeID<FPropertyNotifyComponentData> PropertyNotify;`
- L744 _public member_ `TComponentTypeID<FMovieSceneAudioComponentData> Audio;`
- L745 _public member_ `TComponentTypeID<FMovieSceneAudioInputData> AudioInputs;`
- L746 _public member_ `TComponentTypeID<FName> AudioTriggerName;`
- L748 _public member_ `TComponentTypeID<FMovieSceneCameraShakeComponentData> CameraShake;`
- L749 _public member_ `TComponentTypeID<FMovieSceneCameraShakeInstanceData> CameraShakeInstance;`
- L812 _public member_ `} Accessors;`
- L822 _public member_ `} Tags;`
- L824 _public member_ `TComponentTypeID<FLevelVisibilityComponentData> LevelVisibility;`
- L825 _public member_ `TComponentTypeID<FMovieSceneDataLayerComponentData> DataLayer;`
- L827 _public prototype_ `static void Destroy();`
- L829 _public prototype_ `static FMovieSceneTracksComponentTypes* Get();`
- L832 _private prototype_ `FMovieSceneTracksComponentTypes();`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::(anonymous)`  
``  
_L722-731_

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::FObjectPropertyRegistration`  
`struct FObjectPropertyRegistration : TCustomPropertyRegistration<FObjectPropertyTraits>`  
_L751-772_
- inherits: `TCustomPropertyRegistration<FObjectPropertyTraits>`
- L759 _public function_ `void Add(UClass* ClassType, FName PropertyName, GetterFunc Getter, SetterFunc Setter)`
- L764 _public function_ `void Add(UClass* ClassType, FName PropertyName, GetterFunc Getter, SetterFunc Setter, FMetaData InMetaData)`
- L771 _public member_ `TMap<int32, FMovieSceneTracksComponentTypes::FObjectPropertyRegistration::FMetaData> MetaData;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::FObjectPropertyRegistration::FMetaData`  
`struct FMetaData`  
_L753-757_
- L755 _public member_ `TWeakObjectPtr<UClass> AllowedClass;`
- L756 _public member_ `bool bAllowsClear = true;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::FActorReferencePropertyRegistration`  
`struct FActorReferencePropertyRegistration : TCustomPropertyRegistration<FActorReferencePropertyTraits>`  
_L774-794_
- inherits: `TCustomPropertyRegistration<FActorReferencePropertyTraits>`
- L781 _public function_ `void Add(UClass* ClassType, FName PropertyName, GetterFunc Getter, SetterFunc Setter)`
- L786 _public function_ `void Add(UClass* ClassType, FName PropertyName, GetterFunc Getter, SetterFunc Setter, FMetaData InMetaData)`
- L793 _public member_ `TMap<int32, FMovieSceneTracksComponentTypes::FActorReferencePropertyRegistration::FMetaData> MetaData;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::FActorReferencePropertyRegistration::FMetaData`  
`struct FMetaData`  
_L776-779_
- L778 _public member_ `EActorReferenceType Type = EActorReferenceType::ObjectPointer;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::FAccessors`  
`struct FAccessors`  
_L796-812_
- L798 _public member_ `TCustomPropertyRegistration<FBoolPropertyTraits> Bool;`
- L799 _public member_ `TCustomPropertyRegistration<FBytePropertyTraits> Byte;`
- L800 _public member_ `TCustomPropertyRegistration<FEnumPropertyTraits> Enum;`
- L801 _public member_ `TCustomPropertyRegistration<FIntPropertyTraits> Integer;`
- L802 _public member_ `TCustomPropertyRegistration<FFloatPropertyTraits> Float;`
- L803 _public member_ `TCustomPropertyRegistration<FDoublePropertyTraits> Double;`
- L804 _public member_ `TCustomPropertyRegistration<FColorPropertyTraits> Color;`
- L805 _public member_ `TCustomPropertyRegistration<FFloatVectorPropertyTraits> FloatVector;`
- L806 _public member_ `TCustomPropertyRegistration<FDoubleVectorPropertyTraits> DoubleVector;`
- L807 _public member_ `TCustomPropertyRegistration<FTransformPropertyTraits> Transform;`
- L808 _public member_ `TCustomPropertyRegistration<FComponentTransformPropertyTraits, 1> ComponentTransform;`
- L809 _public member_ `FObjectPropertyRegistration Object;`
- L810 _public member_ `FActorReferencePropertyRegistration ActorReference;`

#### struct `UE::MovieScene::FMovieSceneTracksComponentTypes::(anonymous)`  
``  
_L815-822_

#### Free symbols / members of external scopes

- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace MovieScene` (scope `UE`)
- L212 _namespace_ `namespace UE`
- L214 _namespace_ `namespace MovieScene` (scope `UE`)
- L645 _typedef_ `using FBytePropertyTraits = TPropertyTraits<uint8, uint8>;` (scope `UE::MovieScene`)
- L646 _typedef_ `using FEnumPropertyTraits = TPropertyTraits<uint8, uint8>;` (scope `UE::MovieScene`)
- L647 _typedef_ `using FIntPropertyTraits = TDynamicVariantPropertyTraits<int64, int64, int32, int16, int8>;` (scope `UE::MovieScene`)
- L648 _typedef_ `using FDoublePropertyTraits = TDynamicVariantPropertyTraits<double, double>;` (scope `UE::MovieScene`)
- L649 _typedef_ `using FTransformPropertyTraits = TDynamicVariantPropertyTraits<FIntermediate3DTransform, FTransform>;` (scope `UE::MovieScene`)
- L650 _typedef_ `using FEulerTransformPropertyTraits = TPropertyTraits<FEulerTransform, FIntermediate3DTransform>;` (scope `UE::MovieScene`)
- L651 _typedef_ `using FComponentTransformPropertyTraits = TDirectPropertyTraits<FIntermediate3DTransform>;` (scope `UE::MovieScene`)
- L652 _typedef_ `using FRotatorPropertyTraits = TDirectPropertyTraits<FRotator>;` (scope `UE::MovieScene`)
- L653 _typedef_ `using FStringPropertyTraits = TDirectPropertyTraits<FString>;` (scope `UE::MovieScene`)
- L654 _typedef_ `using FTextPropertyTraits = TDirectPropertyTraits<FText>;` (scope `UE::MovieScene`)
- L656 _typedef_ `using FBoolParameterTraits = TDirectPropertyTraits<bool>;` (scope `UE::MovieScene`)
- L657 _typedef_ `using FByteParameterTraits = TDirectPropertyTraits<uint8>;` (scope `UE::MovieScene`)
- L658 _typedef_ `using FIntegerParameterTraits = TDirectPropertyTraits<int32>;` (scope `UE::MovieScene`)
- L659 _typedef_ `using FFloatParameterTraits = TPropertyTraits<float, double>;` (scope `UE::MovieScene`)
- L660 _typedef_ `using FColorParameterTraits = TPropertyTraits<FLinearColor, FIntermediateColor>;` (scope `UE::MovieScene`)
- L661 _typedef_ `using FVector2ParameterTraits = TPropertyTraits<FVector2f, FFloatIntermediateVector>;` (scope `UE::MovieScene`)
- L662 _typedef_ `using FVector3ParameterTraits = TPropertyTraits<FVector3f, FFloatIntermediateVector>;` (scope `UE::MovieScene`)
- L663 _typedef_ `using FTransformParameterTraits = TPropertyTraits<FEulerTransform, FIntermediate3DTransform>;` (scope `UE::MovieScene`)
- L665 _typedef_ `using FColorPropertyTraits = TDynamicVariantPropertyTraits<FIntermediateColor, FLinearColor, FColor, FSlateColor>;` (scope `UE::MovieScene`)
- L666 _typedef_ `using FDoubleVectorPropertyTraits = TDynamicVariantPropertyTraits<FDoubleIntermediateVector, FVector2D, FVector, FVector3d, FVector4d, FVector4>;` (scope `UE::MovieScene`)
- L667 _typedef_ `using FFloatVectorPropertyTraits = TDynamicVariantPropertyTraits<FFloatIntermediateVector, FVector2f, FVector3f, FVector4f>;` (scope `UE::MovieScene`)
- L723 _member_ `TPropertyComponents<FBoolParameterTraits> Bool;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L724 _member_ `TPropertyComponents<FByteParameterTraits> Byte;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L725 _member_ `TPropertyComponents<FIntegerParameterTraits> Integer;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L726 _member_ `TPropertyComponents<FFloatParameterTraits> Scalar;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L727 _member_ `TPropertyComponents<FVector2ParameterTraits> Vector2;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L728 _member_ `TPropertyComponents<FVector3ParameterTraits> Vector3;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L729 _member_ `TPropertyComponents<FColorParameterTraits> Color;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L730 _member_ `TPropertyComponents<FTransformParameterTraits> Transform;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900108`)
- L816 _member_ `FComponentTypeID BoundMaterialChanged;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900208`)
- L817 _member_ `FComponentTypeID CustomPrimitiveData;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900208`)
- L818 _member_ `FComponentTypeID Slomo;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900208`)
- L819 _member_ `FComponentTypeID Visibility;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900208`)
- L821 _member_ `FComponentTypeID AnimMixerPoseProducer;` (scope `UE::MovieScene::FMovieSceneTracksComponentTypes::__anon088dd4900208`) — Tag specifying that this entity produces skeleton poses that are evaluated through the anim mixer.

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksFwd.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksPropertyTraits.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MovieScene` (scope `UE`)
- L21 _prototype_ `void UnpackChannelsFromOperational(uint8 Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L22 _prototype_ `void UnpackChannelsFromOperational(int64 Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L23 _prototype_ `void UnpackChannelsFromOperational(double Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L24 _prototype_ `void UnpackChannelsFromOperational(float Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L25 _prototype_ `void UnpackChannelsFromOperational(const FString& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L26 _prototype_ `void UnpackChannelsFromOperational(const FText& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L27 _prototype_ `void UnpackChannelsFromOperational(const FRotator& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L28 _prototype_ `void UnpackChannelsFromOperational(const FFloatIntermediateVector& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L29 _prototype_ `void UnpackChannelsFromOperational(const FDoubleIntermediateVector& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L30 _prototype_ `void UnpackChannelsFromOperational(const FIntermediateColor& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)
- L31 _prototype_ `void UnpackChannelsFromOperational(const FIntermediate3DTransform& Value, const FProperty& Property, FUnpackedChannelValues& OutUnpackedValues);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksPropertyTypes.h` (Public)


#### struct `UE::MovieScene::FVectorPropertyMetaData`  
`struct FVectorPropertyMetaData`  
_L26-29_
- L28 _public member_ `uint8 NumChannels = 0;`

#### struct `UE::MovieScene::FFloatIntermediateVector`  
`struct FFloatIntermediateVector`  
_L32-78_
- desc: Intermediate type for the vector property system that lets us store how many dimensions the vector should have
- L34 _public member_ `double X, Y, Z, W;`
- L34 _public member_ `double X, Y, Z, W;`
- L34 _public member_ `double X, Y, Z, W;`
- L34 _public member_ `double X, Y, Z, W;`
- L36 _public function_ `FFloatIntermediateVector() : X(0), Y(0), Z(0), W(0)`
- L40 _public function_ `FFloatIntermediateVector(double InX, double InY) : X(InX), Y(InY), Z(0), W(0)`
- L44 _public function_ `FFloatIntermediateVector(double InX, double InY, double InZ) : X(InX), Y(InY), Z(InZ), W(0)`
- L48 _public function_ `FFloatIntermediateVector(double InX, double InY, double InZ, double InW) : X(InX), Y(InY), Z(InZ), W(InW)`
- L52 _public function_ `FVector2f AsVector2f() const`
- L56 _public function_ `FVector2d AsVector2d() const`
- L61 _public function_ `FVector3f AsVector3f() const`
- L65 _public function_ `FVector3d AsVector3d() const`
- L70 _public function_ `FVector4f AsVector4f() const`
- L74 _public function_ `FVector4d AsVector4d() const`

#### struct `UE::MovieScene::FDoubleIntermediateVector`  
`struct FDoubleIntermediateVector`  
_L80-99_
- L82 _public member_ `double X, Y, Z, W;`
- L82 _public member_ `double X, Y, Z, W;`
- L82 _public member_ `double X, Y, Z, W;`
- L82 _public member_ `double X, Y, Z, W;`
- L84 _public function_ `FDoubleIntermediateVector() : X(0), Y(0), Z(0), W(0)`
- L88 _public function_ `FDoubleIntermediateVector(double InX, double InY) : X(InX), Y(InY), Z(0), W(0)`
- L92 _public function_ `FDoubleIntermediateVector(double InX, double InY, double InZ) : X(InX), Y(InY), Z(InZ), W(0)`
- L96 _public function_ `FDoubleIntermediateVector(double InX, double InY, double InZ, double InW) : X(InX), Y(InY), Z(InZ), W(InW)`

#### enum `UE::MovieScene::EColorPropertyType`  
`enum class EColorPropertyType : uint8`  
_L103-113_
- desc: Color type for the color property system
- L106 _public enumerator_ `Undefined` — Undefined
- L108 _public enumerator_ `Slate` — FSlateColor
- L110 _public enumerator_ `Linear` — FLinearColor
- L112 _public enumerator_ `Color` — FColor

#### struct `UE::MovieScene::FIntermediateColor`  
`struct FIntermediateColor`  
_L116-170_
- desc: Intermediate type for the color property system that lets us store what kind of color type we should use
- L118 _public member_ `double R, G, B, A;`
- L118 _public member_ `double R, G, B, A;`
- L118 _public member_ `double R, G, B, A;`
- L118 _public member_ `double R, G, B, A;`
- L120 _public function_ `FIntermediateColor() : R(0.f), G(0.f), B(0.f), A(0.f)`
- L124 _public function_ `explicit FIntermediateColor(double InR, double InG, double InB, double InA) : R(InR), G(InG), B(InB), A(InA)`
- L127 _public function_ `explicit FIntermediateColor(const FLinearColor& InColor) : R(InColor.R), G(InColor.G), B(InColor.B), A(InColor.A)`
- L130 _public function_ `explicit FIntermediateColor(const FColor& InColor)`
- L139 _public function_ `explicit FIntermediateColor(const FSlateColor& InSlateColor)`
- L148 _public function_ `double operator[](int32 Index) const`
- L154 _public function_ `FColor GetColor() const`
- L161 _public function_ `FLinearColor GetLinearColor() const`
- L166 _public function_ `FSlateColor GetSlateColor() const`

#### struct `UE::MovieScene::FIntermediate3DTransform`  
`struct FIntermediate3DTransform`  
_L175-222_
- desc: Intermediate type used for applying partially animated transforms. Saves us from repteatedly recomposing quaternions from euler angles
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L178 _public member_ `double T_X, T_Y, T_Z, R_X, R_Y, R_Z, S_X, S_Y, S_Z;` — When LWC is enabled, translations are manipulated as doubles.
- L180 _public function_ `FIntermediate3DTransform() : T_X(0.), T_Y(0.), T_Z(0.), R_X(0.), R_Y(0.), R_Z(0.), S_X(0.), S_Y(0.), S_Z(0.)`
- L184 _public function_ `FIntermediate3DTransform( double InT_X, double InT_Y, double InT_Z, double InR_X, double InR_Y, double InR_Z, double InS_X, double InS_Y, double InS_Z) : T_X(InT_X), T_Y(InT_Y), T_Z(InT_Z), R_X(InR_X), R_Y(InR_Y), R_Z(InR_Z), S_X(InS_X), S_Y(InS_Y), S_Z(InS_Z)`
- L189 _public function_ `FIntermediate3DTransform(const FVector& InLocation, const FRotator& InRotation, const FVector& InScale) : T_X(InLocation.X), T_Y(InLocation.Y), T_Z(InLocation.Z) , R_X(InRotation.Roll), R_Y(InRotation.Pitch), R_Z(InRotation.Yaw) , S_X(InScale.X), S_Y(InScale.Y), S_Z(InScale.Z)`
- L195 _public function_ `double operator[](int32 Index) const`
- L201 _public function_ `FVector GetTranslation() const`
- L205 _public function_ `FRotator GetRotation() const`
- L209 _public function_ `FVector GetScale() const`
- L213 _public function_ `FEulerTransform AsEuler() const`
- L218 _public prototype_ `void ApplyTo(USceneComponent* SceneComponent) const;`
- L220 _public prototype_ `static void ApplyTransformTo(USceneComponent* SceneComponent, const FIntermediate3DTransform& Transform);`
- L221 _public prototype_ `static void ApplyTranslationAndRotationTo(USceneComponent* SceneComponent, const FIntermediate3DTransform& Transform);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)
- L224 _prototype_ `FIntermediate3DTransform GetComponentTransform(const UObject* Object);` (scope `UE::MovieScene`)
- L225 _prototype_ `void SetComponentTransform(USceneComponent* SceneComponent, const FIntermediate3DTransform& InTransform);` (scope `UE::MovieScene`)
- L226 _prototype_ `void SetComponentTransformAndVelocity(UObject* Object, const FIntermediate3DTransform& InTransform);` (scope `UE::MovieScene`)
- L228 _prototype_ `void ConvertOperationalProperty(float In, double& Out);` (scope `UE::MovieScene`)
- L229 _prototype_ `void ConvertOperationalProperty(double In, float& Out);` (scope `UE::MovieScene`)
- L231 _prototype_ `void ConvertOperationalProperty(int64 In, int8& Out);` (scope `UE::MovieScene`)
- L232 _prototype_ `void ConvertOperationalProperty(int64 In, int16& Out);` (scope `UE::MovieScene`)
- L233 _prototype_ `void ConvertOperationalProperty(int64 In, int32& Out);` (scope `UE::MovieScene`)
- L235 _prototype_ `void ConvertOperationalProperty(const FIntermediate3DTransform& In, FEulerTransform& Out);` (scope `UE::MovieScene`)
- L236 _prototype_ `void ConvertOperationalProperty(const FEulerTransform& In, FIntermediate3DTransform& Out);` (scope `UE::MovieScene`)
- L237 _prototype_ `void ConvertOperationalProperty(const FIntermediate3DTransform& In, FTransform& Out);` (scope `UE::MovieScene`)
- L238 _prototype_ `void ConvertOperationalProperty(const FTransform& In, FIntermediate3DTransform& Out);` (scope `UE::MovieScene`)
- L240 _prototype_ `void ConvertOperationalProperty(const FIntermediateColor& InColor, FColor& Out);` (scope `UE::MovieScene`)
- L241 _prototype_ `void ConvertOperationalProperty(const FIntermediateColor& InColor, FLinearColor& Out);` (scope `UE::MovieScene`)
- L242 _prototype_ `void ConvertOperationalProperty(const FIntermediateColor& InColor, FSlateColor& Out);` (scope `UE::MovieScene`)
- L243 _prototype_ `void ConvertOperationalProperty(const FColor& InColor, FIntermediateColor& OutIntermediate);` (scope `UE::MovieScene`)
- L244 _prototype_ `void ConvertOperationalProperty(const FLinearColor& InColor, FIntermediateColor& OutIntermediate);` (scope `UE::MovieScene`)
- L245 _prototype_ `void ConvertOperationalProperty(const FSlateColor& InColor, FIntermediateColor& OutIntermediate);` (scope `UE::MovieScene`)
- L247 _prototype_ `void ConvertOperationalProperty(const FFloatIntermediateVector& InVector, FVector2f& Out);` (scope `UE::MovieScene`)
- L248 _prototype_ `void ConvertOperationalProperty(const FFloatIntermediateVector& InVector, FVector3f& Out);` (scope `UE::MovieScene`)
- L249 _prototype_ `void ConvertOperationalProperty(const FFloatIntermediateVector& InVector, FVector4f& Out);` (scope `UE::MovieScene`)
- L250 _prototype_ `void ConvertOperationalProperty(const FVector2f& In, FFloatIntermediateVector& Out);` (scope `UE::MovieScene`)
- L251 _prototype_ `void ConvertOperationalProperty(const FVector3f& In, FFloatIntermediateVector& Out);` (scope `UE::MovieScene`)
- L252 _prototype_ `void ConvertOperationalProperty(const FVector4f& In, FFloatIntermediateVector& Out);` (scope `UE::MovieScene`)
- L254 _prototype_ `void ConvertOperationalProperty(const FDoubleIntermediateVector& InVector, FVector2d& Out);` (scope `UE::MovieScene`)
- L255 _prototype_ `void ConvertOperationalProperty(const FDoubleIntermediateVector& InVector, FVector3d& Out);` (scope `UE::MovieScene`)
- L256 _prototype_ `void ConvertOperationalProperty(const FDoubleIntermediateVector& InVector, FVector4d& Out);` (scope `UE::MovieScene`)
- L257 _prototype_ `void ConvertOperationalProperty(const FVector2d& In, FDoubleIntermediateVector& Out);` (scope `UE::MovieScene`)
- L258 _prototype_ `void ConvertOperationalProperty(const FVector3d& In, FDoubleIntermediateVector& Out);` (scope `UE::MovieScene`)
- L259 _prototype_ `void ConvertOperationalProperty(const FVector4d& In, FDoubleIntermediateVector& Out);` (scope `UE::MovieScene`)
- L261 _prototype_ `void ConvertOperationalProperty(const FObjectComponent& In, UObject*& Out);` (scope `UE::MovieScene`)
- L262 _prototype_ `void ConvertOperationalProperty(UObject* In, FObjectComponent& Out);` (scope `UE::MovieScene`)
- L264 _prototype_ `void ConvertOperationalProperty(const FActorReferenceComponent& InComponentData, TObjectPtr<AActor>& Out);` (scope `UE::MovieScene`)
- L265 _prototype_ `void ConvertOperationalProperty(const FActorReferenceComponent& InComponentData, TSoftObjectPtr<AActor>& Out);` (scope `UE::MovieScene`)
- L266 _prototype_ `void ConvertOperationalProperty(const TSoftObjectPtr<AActor> InActor, FActorReferenceComponent& Out);` (scope `UE::MovieScene`)
- L267 _prototype_ `void ConvertOperationalProperty(const TObjectPtr<AActor> InActor, FActorReferenceComponent& Out);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/MovieSceneTracksSettings.h` (Public)


#### class `UMovieSceneTracksSettings`  
`class UMovieSceneTracksSettings : public UObject`  
_L14-40_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, PerObjectConfig)`
- inherits: `UObject`
- desc: Options for some of the Sequencer systems in this module.
- L20 _public prototype_ `UMovieSceneTracksSettings(const FObjectInitializer& ObjectInitializer);`
- L25 _public function_ `bool GetPreviewCameraCutsInSimulate() const` — Gets whether camera cut tracks should take control of the viewport in SIE, or PIE while ejected from the player controller.
- L30 _public prototype_ `void SetPreviewCameraCutsInSimulate(bool bInPreviewCameraCutsInSimulate);` — Sets whether camera cut tracks should take control of the viewport in SIE, or PIE while ejected from the player controller.
- L39 _protected member_ `bool bPreviewCameraCutsInSimulate;` — `UPROPERTY(config, EditAnywhere, Category=General)` — Whether camera cut tracks should take control of the viewport in SIE (Simulate in Editor) or after ejecting from the player controller while in PIE.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETRACKS_API`

### `Source/Runtime/MovieSceneTracks/Public/PreAnimatedState/MovieScenePreAnimatedComponentTransformStorage.h` (Public)


#### struct `UE::MovieScene::FComponentTransformPreAnimatedTraits`  
`struct FComponentTransformPreAnimatedTraits : FComponentTransformPropertyTraits`  
_L17-26_
- inherits: `FComponentTransformPropertyTraits`
- L19 _public typedef_ `using KeyType = FObjectKey;`
- L20 _public typedef_ `using StorageType = FIntermediate3DTransform;`
- L23 _public prototype_ `static void SetObjectPropertyValue(UObject* InObject, const FCustomPropertyAccessor& BaseCustomAccessor, const FIntermediate3DTransform& CachedTransform);` — These override the functions in FComponentTransformPropertyTraits in order to wrap them with a temporary mobility assignment
- L24 _public prototype_ `static void SetObjectPropertyValue(UObject* InObject, uint16 PropertyOffset, const FIntermediate3DTransform& CachedTransform);`
- L25 _public prototype_ `static void SetObjectPropertyValue(UObject* InObject, FTrackInstancePropertyBindings* PropertyBindings, const FIntermediate3DTransform& CachedTransform);`

#### struct `UE::MovieScene::FPreAnimatedComponentTransformStorage`  
`struct FPreAnimatedComponentTransformStorage : TPreAnimatedPropertyStorage<FComponentTransformPreAnimatedTraits>`  
_L28-37_
- inherits: `TPreAnimatedPropertyStorage<FComponentTransformPreAnimatedTraits>`
- L31 _public prototype_ `FPreAnimatedComponentTransformStorage();`
- L33 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedComponentTransformStorage> StorageID;`
- L35 _public prototype_ `void CachePreAnimatedTransform(const FCachePreAnimatedValueParams& Params, UObject* BoundObject);`
- L36 _public prototype_ `void CachePreAnimatedTransforms(const FCachePreAnimatedValueParams& Params, TArrayView<UObject* const> BoundObjects, TOptional<TFunctionRef<bool(int32)>> Predicate = TOptional<TFunctionRef<bool(int32)>>());`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETRACKS_API`
- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieScene3DAttachSection.h` (Public)


#### class `UMovieScene3DAttachSection`  
`class UMovieScene3DAttachSection : public UMovieScene3DConstraintSection , public IMovieSceneEntityProvider`  
_L19-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScene3DConstraintSection,IMovieSceneEntityProvider`
- desc: A 3D Attach section
- L32 _public prototype_ `void SetAttachTargetID(const FMovieSceneObjectBindingID& InAttachBindingID);` — Sets the object to attach to @param InAttachBindingId The object binding id to the path
- L36 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L41 _public member_ `FName AttachSocketName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L44 _public member_ `FName AttachComponentName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L50 _public member_ `bool bFullRevertOnDetach;` — `UPROPERTY(transient)`
- L53 _public member_ `TSoftObjectPtr<USceneComponent> ReAttachOnDetach;` — `UPROPERTY(transient)`
- L58 _public member_ `EAttachmentRule AttachmentLocationRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L61 _public member_ `EAttachmentRule AttachmentRotationRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L64 _public member_ `EAttachmentRule AttachmentScaleRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L67 _public member_ `EDetachmentRule DetachmentLocationRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L70 _public member_ `EDetachmentRule DetachmentRotationRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`
- L73 _public member_ `EDetachmentRule DetachmentScaleRule;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Attach")`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieScene3DConstraintSection.h` (Public)


#### class `UMovieScene3DConstraintSection`  
`class UMovieScene3DConstraintSection : public UMovieSceneSection`  
_L28-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Base class for 3D constraint section
- L37 _public function_ `const FMovieSceneObjectBindingID& GetConstraintBindingID() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Gets the constraint binding for this Constraint section
- L44 _public function_ `void SetConstraintBindingID(const FMovieSceneObjectBindingID& InConstraintBindingID)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Sets the constraint binding for this Constraint section
- L53 _public prototype_ `virtual void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L55 _public prototype_ `virtual void GetReferencedBindings(TArray<FGuid>& OutBindings) override;`
- L58 _public prototype_ `virtual void PostLoad() override;` — ~UObject interface
- L64 _protected member_ `FGuid ConstraintId_DEPRECATED;` — `UPROPERTY()` — The possessable guid that this constraint uses
- L68 _protected member_ `FMovieSceneObjectBindingID ConstraintBindingID;` — `UPROPERTY(EditAnywhere, Category="Section")` — The constraint binding that this movie Constraint uses

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieScene3DPathSection.h` (Public)


#### enum `MovieScene3DPathSection_Axis`  
`enum class MovieScene3DPathSection_Axis : uint8`  
_L18-26_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `X UMETA(DisplayName = "X")`
- L21 _public enumerator_ `Y UMETA(DisplayName = "Y")`
- L22 _public enumerator_ `Z UMETA(DisplayName = "Z")`
- L23 _public enumerator_ `NEG_X UMETA(DisplayName = "-X")`
- L24 _public enumerator_ `NEG_Y UMETA(DisplayName = "-Y")`
- L25 _public enumerator_ `NEG_Z UMETA(DisplayName = "-Z")`

#### class `UMovieScene3DPathSection`  
`class UMovieScene3DPathSection : public UMovieScene3DConstraintSection`  
_L33-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScene3DConstraintSection`
- desc: A 3D Path section
- L40 _public prototype_ `virtual void InitialPlacement(const TArray<UMovieSceneSection*>& Sections, FFrameNumber InStartTime, int32 Duration, bool bAllowMultipleRows) override;`
- L47 _public prototype_ `void Eval(USceneComponent* SceneComponent, FFrameTime Time, USplineComponent* SplineComponent, FVector& OutTranslation, FRotator& OutRotation) const;` — Evaluates the path track. @param Time The position in time within the movie scene.
- L54 _public prototype_ `void SetPathBindingID(const FMovieSceneObjectBindingID& InPathBindingID);` — Sets the path binding ID @param InPathBindingID The object binding id to the path.
- L56 _public function_ `MovieScene3DPathSection_Axis GetFrontAxisEnum() const`
- L57 _public function_ `MovieScene3DPathSection_Axis GetUpAxisEnum() const`
- L58 _public function_ `bool GetFollow() const`
- L59 _public function_ `bool GetReverse() const`
- L60 _public function_ `bool GetForceUpright() const`
- L64 _public function_ `const FMovieSceneFloatChannel& GetTimingChannel() const`
- L65 _public function_ `FMovieSceneFloatChannel& GetTimingChannel()`
- L69 _public member_ `FMovieSceneFloatChannel TimingCurve;` — `UPROPERTY()` — Timing Curve
- L73 _public member_ `MovieScene3DPathSection_Axis FrontAxisEnum;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Path")` — Front Axis
- L77 _public member_ `MovieScene3DPathSection_Axis UpAxisEnum;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Path")` — Up Axis
- L81 _public member_ `uint32 bFollow:1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Path")` — Follow Curve
- L85 _public member_ `uint32 bReverse:1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Path")` — Reverse Timing
- L89 _public member_ `uint32 bForceUpright:1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Path")` — Force Upright

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENETRACKS_API`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieScene3DTransformSection.h` (Public)


#### enum `EShow3DTrajectory`  
`enum class EShow3DTrajectory : uint8`  
_L26-31_
- reflection: `UENUM()`
- desc: Visibility options for 3d trajectory.
- L28 _public enumerator_ `EST_OnlyWhenSelected UMETA(DisplayName="Only When Selected")`
- L29 _public enumerator_ `EST_Always UMETA(DisplayName="Always")`
- L30 _public enumerator_ `EST_Never UMETA(DisplayName="Never")`

#### struct `FMovieScene3DLocationKeyStruct`  
`struct FMovieScene3DLocationKeyStruct : public FMovieSceneKeyStruct`  
_L39-55_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Proxy structure for translation keys in 3D transform sections.
- L46 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Key, meta=(Spatial))` — The key's translation value.
- L50 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L52 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L54 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DLocationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DLocationKeyStruct>`  
_L56-56_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DLocationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DLocationKeyStruct>`  
_L56-56_
- inherits: `TStructOpsTypeTraitsBase2<FMovieScene3DLocationKeyStruct>`

#### struct `FMovieScene3DRotationKeyStruct`  
`struct FMovieScene3DRotationKeyStruct : public FMovieSceneKeyStruct`  
_L63-79_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Proxy structure for translation keys in 3D transform sections.
- L70 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's rotation value.
- L74 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L76 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L78 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DRotationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DRotationKeyStruct>`  
_L80-80_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DRotationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DRotationKeyStruct>`  
_L80-80_
- inherits: `TStructOpsTypeTraitsBase2<FMovieScene3DRotationKeyStruct>`

#### struct `FMovieScene3DScaleKeyStruct`  
`struct FMovieScene3DScaleKeyStruct : public FMovieSceneKeyStruct`  
_L86-102_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Proxy structure for translation keys in 3D transform sections.
- L93 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Category=Key, meta=(Spatial))` — The key's scale value.
- L97 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L99 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L101 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DScaleKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DScaleKeyStruct>`  
_L103-103_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DScaleKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DScaleKeyStruct>`  
_L103-103_
- inherits: `TStructOpsTypeTraitsBase2<FMovieScene3DScaleKeyStruct>`

#### struct `FMovieScene3DTransformKeyStruct`  
`struct FMovieScene3DTransformKeyStruct : public FMovieSceneKeyStruct`  
_L110-134_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Proxy structure for 3D transform section key data.
- L117 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Key, meta=(Spatial))` — The key's translation value.
- L121 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's rotation value.
- L125 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, Category=Key, meta=(Spatial))` — The key's scale value.
- L129 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L131 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L133 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DTransformKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DTransformKeyStruct>`  
_L135-135_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieScene3DTransformKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DTransformKeyStruct>`  
_L135-135_
- inherits: `TStructOpsTypeTraitsBase2<FMovieScene3DTransformKeyStruct>`

#### struct `FMovieSceneTransformMask`  
`struct FMovieSceneTransformMask`  
_L141-189_
- reflection: `USTRUCT()`
- L145 _public function_ `FMovieSceneTransformMask() : Mask(0)`
- L149 _public function_ `FMovieSceneTransformMask(EMovieSceneTransformChannel Channel) : Mask((__underlying_type(EMovieSceneTransformChannel))Channel)`
- L153 _public function_ `EMovieSceneTransformChannel GetChannels() const`
- L158 _public function_ `FVector GetTranslationFactor() const`
- L167 _public function_ `FVector GetRotationFactor() const`
- L176 _public function_ `FVector GetScaleFactor() const`
- L188 _private member_ `uint32 Mask;` — `UPROPERTY()`

#### class `UMovieScene3DTransformSectionConstraints`  
`class UMovieScene3DTransformSectionConstraints : public UObject`  
_L195-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This object contains information needed for constraint channels on the transform section
- L203 _public member_ `TArray<FConstraintAndActiveChannel> ConstraintsChannels;` — `UPROPERTY()` — Constraint Channels
- L207 _public prototype_ `virtual void PostEditUndo() override;`

#### class `UMovieScene3DTransformSection`  
`class UMovieScene3DTransformSection : public UMovieSceneSection , public IMovieSceneConstrainedSection , public IMovieSceneEntityProvider , public IMovieSceneChannelOverrideProvider`  
_L215-399_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneConstrainedSection,IMovieSceneEntityProvider,IMovieSceneChannelOverrideProvider`
- desc: A 3D transform section
- L225 _public prototype_ `virtual void PostLoad() override;`
- L229 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;` — From UObject
- L230 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L235 _public prototype_ `virtual bool ShowCurveForChannel(const void* Channel) const override;`
- L236 _public prototype_ `virtual void SetBlendType(EMovieSceneBlendType InBlendType) override;`
- L237 _public prototype_ `virtual void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L238 _public prototype_ `virtual void GetReferencedBindings(TArray<FGuid>& OutBindings) override;`
- L239 _public prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;`
- L242 _public prototype_ `virtual void PostPaste() override;`
- L250 _public prototype_ `FMovieSceneTransformMask GetMask() const;` — Access the mask that defines which channels this track should animate
- L255 _public prototype_ `void SetMask(FMovieSceneTransformMask NewMask);` — Set the mask that defines which channels this track should animate
- L260 _public prototype_ `FMovieSceneTransformMask GetMaskByName(const FName& InName) const;` — Get the mask by name
- L265 _public prototype_ `bool GetUseQuaternionInterpolation() const;` — Get whether we should use quaternion interpolation for our rotations.
- L270 _public prototype_ `void SetUseQuaternionInterpolation(bool bInUseQuaternionInterpolation);` — Set whether we should use quaternion interpolation for our rotations.
- L275 _public function_ `FMovieSceneFloatChannel* GetWeightChannel()` — Get Weight Channel
- L278 _protected prototype_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles) override;`
- L279 _protected prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L283 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L284 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L285 _private prototype_ `virtual void InterrogateEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L288 _private prototype_ `template<typename BaseBuilderType> void BuildEntity(BaseBuilderType& InBaseBuilder, UMovieSceneEntitySystemLinker* Linker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity);`
- L289 _private prototype_ `void PopulateConstraintEntities(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder);`
- L290 _private prototype_ `void ImportConstraintEntity(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity);`
- L294 _private member_ `static UE::MovieScene::FChannelOverrideNames ChannelOverrideNames;`
- L296 _private prototype_ `UMovieSceneSectionChannelOverrideRegistry* GetChannelOverrideRegistry(bool bCreateIfMissing) override;`
- L297 _private prototype_ `UE::MovieScene::FChannelOverrideProviderTraitsHandle GetChannelOverrideProviderTraits() const override;`
- L298 _private prototype_ `void OnChannelOverridesChanged() override;`
- L303 _private member_ `FMovieSceneTransformMask TransformMask;` — `UPROPERTY()`
- L307 _private member_ `FMovieSceneDoubleChannel Translation[3];` — `UPROPERTY()` — Translation curves
- L311 _private member_ `FMovieSceneDoubleChannel Rotation[3];` — `UPROPERTY()` — Rotation curves
- L315 _private member_ `FMovieSceneDoubleChannel Scale[3];` — `UPROPERTY()` — Scale curves
- L319 _private member_ `FMovieSceneFloatChannel ManualWeight;` — `UPROPERTY()` — Manual weight curve
- L323 _private member_ `TObjectPtr<UMovieSceneSectionChannelOverrideRegistry> OverrideRegistry;` — `UPROPERTY()` — Optional pointer to a "channels override" container object. This object would only be allocated if any channels are overridden with a non-standard channel
- L327 _private member_ `TObjectPtr<UMovieScene3DTransformSectionConstraints> Constraints;` — `UPROPERTY()` — Optional pointer to constraint channels
- L331 _private member_ `bool bUseQuaternionInterpolation;` — `UPROPERTY(EditAnywhere, DisplayName = "Use Quaternion Interpolation", Category = "Rotation")` — Whether to use a quaternion linear interpolation between keys. This finds the 'shortest' rotation between keyed orientations.
- L339 _public prototype_ `virtual bool HasConstraintChannel(const FGuid& InGuid) const override;` — If it has that constraint with that Name
- L344 _public prototype_ `virtual FConstraintAndActiveChannel* GetConstraintChannel(const FGuid& InConstraintGuid) override;` — Get constraint with that name
- L349 _public prototype_ `virtual void AddConstraintChannel(UTickableConstraint* InConstraint) override;` — Add Constraint channel
- L354 _public prototype_ `virtual void RemoveConstraintChannel(const UTickableConstraint* InConstraint) override;` — Remove Constraint channel
- L359 _public prototype_ `virtual TArray<FConstraintAndActiveChannel>& GetConstraintsChannels() override;` — Get a reference to the channels
- L364 _public prototype_ `virtual const TArray<FConstraintAndActiveChannel>& GetConstraintsChannels() const override;` — Get a const reference to the channels
- L369 _public prototype_ `virtual void ReplaceConstraint(const FName InConstraintName, UTickableConstraint* InConstraint) override;` — Replace the constraint with the specified name with the new one
- L374 _public prototype_ `virtual void OnConstraintsChanged() override;` — Clear proxy if changed
- L385 _public function_ `EShow3DTrajectory GetShow3DTrajectory() const` — Return the trajectory visibility
- L390 _public function_ `void SetShow3DTrajectory(EShow3DTrajectory InShow3DTrajectory)` — Return the trajectory visibility
- L396 _private member_ `EShow3DTrajectory Show3DTrajectory;` — `UPROPERTY(EditAnywhere, DisplayName = "Show 3D Trajectory", Category = "Transform")` — Whether to show the 3d trajectory

#### Free symbols / members of external scopes

- L56 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieScene3DLocationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DLocationKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for translation keys in 3D transform sections. */ USTRUCT() struct FMovieScene3DRotationKeyStruct` (scope `TStructOpsTypeTraits::__anon1245df1f0103`)
- L80 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieScene3DRotationKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DRotationKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for translation keys in 3D transform sections. */ USTRUCT() struct FMovieScene3DScaleKeyStruct : public FMovieSceneKeyStruct` (scope `TStructOpsTypeTraits::__anon1245df1f0203`)
- L103 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieScene3DScaleKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DScaleKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for 3D transform section key data. */ USTRUCT() struct FMovieScene3DTransformKeyStruct` (scope `TStructOpsTypeTraits::__anon1245df1f0303`)
- L135 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieScene3DTransformKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieScene3DTransformKeyStruct> { enum { WithCopy = false }; }; ENUM_CLASS_FLAGS(EMovieSceneTransformChannel) USTRUCT() struct FMovieSceneTransformMask {` (scope `TStructOpsTypeTraits::__anon1245df1f0403`)

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneActorReferenceSection.h` (Public)


#### class `UMovieSceneActorReferenceSection`  
`class UMovieSceneActorReferenceSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L18-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single actor reference point section
- L27 _public prototype_ `virtual void PostLoad() override;`
- L30 _public prototype_ `virtual void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L32 _public function_ `const FMovieSceneActorReferenceChannel& GetActorReferenceData() const`
- L37 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L42 _private member_ `FMovieSceneActorReferenceChannel ActorReferenceData;` — `UPROPERTY()`
- L48 _private member_ `FIntegralCurve ActorGuidIndexCurve_DEPRECATED;` — `UPROPERTY()` — Curve data
- L51 _private member_ `TArray<FString> ActorGuidStrings_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneAudioSection.h` (Public)


#### class `UMovieSceneAudioSection`  
`class UMovieSceneAudioSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneScalingDriver`  
_L27-386_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneScalingDriver`
- desc: Audio section, for use in the audio track, or by attached audio objects
- L38 _public prototype_ `void SetSound(class USoundBase* InSound);` — `UFUNCTION(BlueprintCallable, Category="Sequencer|Section")` — Sets this section's sound
- L42 _public function_ `class USoundBase* GetSound() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Gets the sound for this section
- L46 _public prototype_ `USoundBase* GetPlaybackSound() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Gets the sound that this section should use for playback, taking into account localization concerns
- L50 _public function_ `void SetStartOffset(FFrameNumber InStartOffset)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set the offset into the beginning of the audio clip
- L54 _public function_ `FFrameNumber GetStartOffset() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Get the offset into the beginning of the audio clip
- L61 _public function_ `const FMovieSceneFloatChannel& GetSoundVolumeChannel() const` — Gets the sound volume curve @return The rich curve for this sound volume
- L68 _public function_ `const FMovieSceneFloatChannel& GetPitchMultiplierChannel() const` — Gets the sound pitch curve @return The rich curve for this sound pitch
- L76 _public function_ `float GetSoundVolume(FFrameTime InTime) const` — Return the sound volume @param InTime	The position in time within the movie scene @return The volume the sound will be played with.
- L89 _public function_ `float GetPitchMultiplier(FFrameTime InTime) const` — Return the pitch multiplier @param Position	The position in time within the movie scene @return The pitch multiplier the sound will be played with.
- L102 _public function_ `bool GetLooping() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — @return Whether to allow looping if the section length is greater than the sound duration Note: Prefer IsRepeating(). This accessor will be deprecated once the Sequencer.Audio.UseRepeating CVar is removed and bRepeating becomes the sole property.
- L108 _public prototype_ `void SetLooping(bool bInLooping);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set whether the sound should be looped. Note: Prefer SetRepeating(). Will be deprecated once the Sequencer.Audio.UseRepeating CVar is removed.
- L112 _public prototype_ `void SetRepeating(bool bInRepeating);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set whether the sound should repeat
- L115 _public prototype_ `bool IsRepeating() const;` — Returns true if this section should repeat: reads bRepeating when CVAR is on, bLooping when off
- L118 _public prototype_ `bool IsSoundLoopingAsset() const;` — True if current sound is a natively looping asset (not one-shot)
- L122 _public prototype_ `bool IsLoopingOrRepeating() const;` — True if playback should continue past the sound's natural duration (repeating one-shot or natively looping asset). Handles CVar legacy fallback: returns bLooping when Sequencer.Audio.UseRepeating is off.
- L126 _public function_ `bool GetPlayUntilFinished() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Returns true if the section should play through the sound's full duration past its visual end.
- L129 _public prototype_ `bool IsPlayUntilFinishedActive() const;` — True only when PlayUntilFinished is both set on the section and globally enabled by the Sequencer.Audio.UsePlayUntilFinished CVar.
- L133 _public prototype_ `void SetPlayUntilFinished(bool bInPlayUntilFinished);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Sets whether the section should play through the sound's full duration past its visual end.
- L140 _public prototype_ `TOptional<FFrameNumber> ComputeDeterministicSoundEndFrame() const;` — Returns the section frame at which a deterministic-duration one-shot sound naturally finishes, accounting for StartFrameOffset. Returns unset for procedural, looping, or duration-unknown sounds, or when the section has no start frame / no outer MovieScene.
- L146 _public function_ `bool GetSuppressSubtitles() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — @return Whether subtitles should be suppressed
- L150 _public function_ `void SetSuppressSubtitles(bool bInSuppressSubtitles)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set whether subtitles should be suppressed
- L156 _public function_ `bool GetOverrideAttenuation() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — @return Whether override settings on this section should be used
- L160 _public function_ `void SetOverrideAttenuation(bool bInOverrideAttenuation)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set whether the attentuation should be overriden
- L166 _public function_ `USoundAttenuation* GetAttenuationSettings() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — @return The attenuation settings
- L170 _public function_ `void SetAttenuationSettings(USoundAttenuation* InAttenuationSettings)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set the attenuation settings for this audio section
- L175 _public function_ `const FMovieSceneActorReferenceChannel& GetAttachActorData() const` — @return The attach actor data
- L177 _public prototype_ `void SetDefaultActorKey(const FMovieSceneObjectBindingID& NewBinding);`
- L182 _public prototype_ `USceneComponent* GetAttachComponent(const AActor* InParentActor, const FMovieSceneActorReferenceKey& Key) const;` — @return The attach component given the bound actor and the actor attach key with the component and socket names
- L185 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — ~UObject interface
- L186 _public prototype_ `virtual void PostLoad() override;`
- L188 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L192 _public function_ `void SetOnQueueSubtitles(const FOnQueueSubtitles& InOnQueueSubtitles)` — Called when subtitles are sent to the SubtitleManager.  Set this delegate if you want to hijack the subtitles for other purposes
- L198 _public function_ `const FOnQueueSubtitles& GetOnQueueSubtitles() const` — Called when subtitles are sent to the SubtitleManager.  Set this delegate if you want to hijack the subtitles for other purposes
- L204 _public function_ `void SetOnAudioFinished(const FOnAudioFinished& InOnAudioFinished)` — called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early
- L210 _public function_ `const FOnAudioFinished& GetOnAudioFinished() const` — called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early
- L215 _public function_ `void SetOnAudioPlaybackPercent(const FOnAudioPlaybackPercent& InOnAudioPlaybackPercent)`
- L220 _public function_ `const FOnAudioPlaybackPercent& GetOnAudioPlaybackPercent() const`
- L226 _public function_ `void ForEachInput(TFunction<void(FName, const FMovieSceneBoolChannel&)> InFunction) const` — Overloads for each input type, const
- L227 _public function_ `void ForEachInput(TFunction<void(FName, const FMovieSceneStringChannel&)> InFunction) const`
- L228 _public function_ `void ForEachInput(TFunction<void(FName, const FMovieSceneIntegerChannel&)> InFunction) const`
- L229 _public function_ `void ForEachInput(TFunction<void(FName, const FMovieSceneFloatChannel&)> InFunction) const`
- L230 _public function_ `void ForEachInput(TFunction<void(FName, const FMovieSceneAudioTriggerChannel&)> InFunction) const`
- L235 _public prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L236 _public prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L237 _public prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L238 _public prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L239 _public prototype_ `virtual void MigrateFrameTimes(FFrameRate SourceRate, FFrameRate DestinationRate) override;`
- L240 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L241 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L244 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L245 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L248 _public prototype_ `virtual void PopulateInitialAnchors(TMap<FGuid, FMovieSceneScalingAnchor>& OutAnchors) override;`
- L249 _public prototype_ `virtual void PopulateAnchors(TMap<FGuid, FMovieSceneScalingAnchor>& OutAnchors) override;`
- L252 _public prototype_ `static void OnUseRepeatingCVarChanged(IConsoleVariable* Variable);` — CVar change callback -- updates all existing audio sections when Sequencer.Audio.UseRepeating changes.
- L255 _public prototype_ `static void OnUsePlayUntilFinishedCVarChanged(IConsoleVariable* Variable);` — CVar change callback -- hides/shows the When Finished UI on existing sections when Sequencer.Audio.UsePlayUntilFinished flips.
- L260 _private function_ `template<typename ChannelType, typename ForEachFunction> inline static void ForEachInternal(ForEachFunction InFunction, const TMap<FName, ChannelType>& InMapToIterate)`
- L268 _private prototype_ `void SetupSoundInputParameters(USoundBase* InSoundBase);`
- L272 _private prototype_ `static bool IsRepeatingCVarEnabled();` — `UFUNCTION()` — Reflects Sequencer.Audio.UseRepeating for EditCondition visibility of bLooping/bRepeating.
- L279 _private prototype_ `bool IsPlayUntilFinishedEditable() const;` — `UFUNCTION()` — Reflects Sequencer.Audio.UsePlayUntilFinished AND the sound being one-shot (and not a branching SoundCue). Used as the EditCondition for the bPlayUntilFinished UPROPERTY so the checkbox greys out when PUF can't apply.
- L282 _private prototype_ `void UpdateCompletionMode();` — Updates completion mode in response to looping state changes.
- L285 _private prototype_ `void RefreshPlayUntilFinishedCompatibilityAndMigrate();` — Refreshes the cached Play Until Finished compatibility flag and migrates legacy KeepState sections to bPlayUntilFinished on first load.
- L288 _private prototype_ `TRange<FFrameNumber> ComputePlayUntilFinishedRange() const;` — Computes the (potentially extended) evaluation range for Play Until Finished.
- L290 _private prototype_ `void SetSoundInternal(class USoundBase* InSound, const bool bInvalidateChannelProxy, const bool bSoundChanged);`
- L295 _private member_ `EMovieSceneCompletionMode CachedCompletionMode = EMovieSceneCompletionMode::ProjectDefault;` — `UPROPERTY()` — Cache the users intended CompletionMode. Used to revert the CompletionMode back to the users intent when not looping (when looping, completion mode is always RestoreState)
- L299 _private member_ `bool bSoundIsPlayUntilFinishedCompatible = false;` — Cached PUF-compatibility of the current Sound asset. Refreshed only when Sound changes, since IsPlayUntilFinishedEditable() is hit per-tick by the property grid and the underlying SoundCue node walk is non-trivial.
- L303 _private member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditAnywhere, Category="Audio", BlueprintGetter=GetSound, BlueprintSetter=SetSound)` — The sound cue or wave that this section plays
- L307 _private member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(EditAnywhere, Category="Audio", meta=(UIFrameDisplayAs="NonMusical|Position"))` — The offset into the beginning of the audio clip
- L311 _private member_ `float StartOffset_DEPRECATED;` — `UPROPERTY()` — The offset into the beginning of the audio clip
- L315 _private member_ `float AudioStartTime_DEPRECATED;` — `UPROPERTY()` — The absolute time that the sound starts playing at
- L319 _private member_ `float AudioDilationFactor_DEPRECATED;` — `UPROPERTY()` — The amount which this audio is time dilated by
- L323 _private member_ `float AudioVolume_DEPRECATED;` — `UPROPERTY()` — The volume the sound will be played with.
- L327 _private member_ `FMovieSceneFloatChannel SoundVolume;` — `UPROPERTY()` — The volume the sound will be played with.
- L331 _private member_ `FMovieSceneFloatChannel PitchMultiplier;` — `UPROPERTY()` — The pitch multiplier the sound will be played with.
- L335 _private member_ `TMap<FName, FMovieSceneFloatChannel> Inputs_Float;` — `UPROPERTY()` — Generic inputs for the sound
- L337 _private member_ `TMap<FName, FMovieSceneStringChannel> Inputs_String;` — `UPROPERTY()`
- L339 _private member_ `TMap<FName, FMovieSceneBoolChannel> Inputs_Bool;` — `UPROPERTY()`
- L341 _private member_ `TMap<FName, FMovieSceneIntegerChannel> Inputs_Int;` — `UPROPERTY()`
- L343 _private member_ `TMap<FName, FMovieSceneAudioTriggerChannel> Inputs_Trigger;` — `UPROPERTY()`
- L346 _private member_ `FMovieSceneActorReferenceChannel AttachActorData;` — `UPROPERTY()`
- L350 _private member_ `bool bLooping;` — `UPROPERTY(EditAnywhere, Category = "Audio", meta = (EditCondition = "!IsRepeatingCVarEnabled()"))` — Allow looping if the section length is greater than the sound duration
- L355 _private member_ `bool bRepeating;` — `UPROPERTY(EditAnywhere, Category = "Audio", meta = (EditCondition = "IsRepeatingCVarEnabled()"))` — Restart a one-shot sound at frame boundaries when section length exceeds sound duration. Active when Sequencer.Audio.UseRepeating CVAR is enabled.
- L363 _private member_ `bool bPlayUntilFinished = false;` — `UPROPERTY(EditAnywhere, Category = "Audio", DisplayName = "Play Until Finished", meta = (EditCondition = "IsPlayUntilFinishedEditable()"))` — When true, the section's evaluation range is extended past its visual end so the sound plays to completion while remaining under sequencer control (pause, volume/pitch keyframes still apply). Only used for one-shot sounds. Active when Sequencer.Audio.UsePlayUntilFinished CVAR is enabled.
- L366 _private member_ `bool bSuppressSubtitles;` — `UPROPERTY(EditAnywhere, Category = "Audio")`
- L370 _private member_ `bool bOverrideAttenuation;` — `UPROPERTY(EditAnywhere, Category="Attenuation")` — Should the attenuation settings on this section be used.
- L374 _private member_ `TObjectPtr<class USoundAttenuation> AttenuationSettings;` — `UPROPERTY(EditAnywhere, Category="Attenuation", meta = (EditCondition = "bOverrideAttenuation"))` — The attenuation settings to use.
- L378 _private member_ `FOnQueueSubtitles OnQueueSubtitles;` — `UPROPERTY()` — Called when subtitles are sent to the SubtitleManager.  Set this delegate if you want to hijack the subtitles for other purposes
- L382 _private member_ `FOnAudioFinished OnAudioFinished;` — `UPROPERTY()` — called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early
- L385 _private member_ `FOnAudioPlaybackPercent OnAudioPlaybackPercent;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneBaseCacheSection.h` (Public)


#### struct `FMovieSceneBaseCacheParams`  
`struct FMovieSceneBaseCacheParams`  
_L12-42_
- reflection: `USTRUCT()`
- desc: Base class for the cache parameters that will be used in all the cache sections
- L17 _public prototype_ `FMovieSceneBaseCacheParams();` — Constructor/Destructor
- L18 _public prototype_ `virtual ~FMovieSceneBaseCacheParams() = default;`
- L21 _public function_ `virtual float GetSequenceLength() const` — Gets the animation sequence length, not modified by play rate
- L25 _public member_ `FFrameNumber FirstLoopStartFrameOffset;` — `UPROPERTY(EditAnywhere, Category = "Cache")` — The offset for the first loop of the animation clip
- L29 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(EditAnywhere, Category = "Cache")` — The offset into the beginning of the animation clip
- L33 _public member_ `FFrameNumber EndFrameOffset;` — `UPROPERTY(EditAnywhere, Category = "Cache")` — The offset into the end of the animation clip
- L37 _public member_ `float PlayRate;` — `UPROPERTY(EditAnywhere, Category = "Cache")` — The playback rate of the animation clip
- L41 _public member_ `uint32 bReverse : 1;` — `UPROPERTY(EditAnywhere, Category = "Cache")` — Reverse the playback of the animation clip

#### class `UMovieSceneBaseCacheSection`  
`class UMovieSceneBaseCacheSection : public UMovieSceneSection`  
_L48-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Movie scene section that control base cache playback
- L55 _public member_ `FMovieSceneBaseCacheParams* ParamsPtr = nullptr;` — Pointer to the concrete uproperty that will be instanced in each BaseCacheSection children
- L58 _public prototype_ `virtual float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L59 _public prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L63 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L64 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L65 _protected prototype_ `virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;`
- L66 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L69 _protected prototype_ `void InitializePlayRate();`
- L72 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L73 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L75 _public member_ `float PreviousPlayRate;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneByteSection.h` (Public)


#### class `UMovieSceneByteSection`  
`class UMovieSceneByteSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single byte section.
- L26 _public member_ `FMovieSceneByteChannel ByteCurve;` — `UPROPERTY()` — Ordered curve data
- L31 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L32 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCVarSection.h` (Public)


#### struct `FMovieSceneConsoleVariableCollection`  
`struct FMovieSceneConsoleVariableCollection`  
_L24-35_
- reflection: `USTRUCT()`
- L30 _public member_ `TScriptInterface<IMovieSceneConsoleVariableTrackInterface> Interface;` — `UPROPERTY(EditAnywhere, DisplayName="Collection Asset", Category="Collection")` — Array of console variable preset assets that this track should operate on
- L34 _public member_ `bool bOnlyIncludeChecked = false;` — `UPROPERTY(EditAnywhere, Category="Collection")` — Whether to include checked consolve variables or not

#### struct `FMovieSceneCVarOverrides`  
`struct FMovieSceneCVarOverrides`  
_L38-50_
- reflection: `USTRUCT()`
- L42 _public prototype_ `void SetFromString(const FString& InString);`
- L44 _public prototype_ `void GetString(TStringBuilder<256>& OutBuilder) const;`
- L45 _public prototype_ `FString GetString() const;`
- L49 _public member_ `TMap<FString, FString> ValuesByCVar;` — `UPROPERTY(EditAnywhere, Category="Console Variables")` — The name of the console variable and the value, separated by ' ' or '=', ie: "foo.bar=1" or "foo.bar 1".

#### class `UMovieSceneCVarSection`  
`class UMovieSceneCVarSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L56-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A CVar section is responsible for applying a user-supplied value to the specified cvar, and then restoring the previous value after the section ends.
- L64 _public prototype_ `UMovieSceneCVarSection(const FObjectInitializer& Init);` — Constructs a new console variable section
- L67 _public prototype_ `void SetFromString(const FString& InString);` — `UFUNCTION(BlueprintCallable, Category="CVars")`
- L70 _public prototype_ `FString GetString() const;` — `UFUNCTION(BlueprintCallable, Category="CVars")`
- L74 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L80 _public member_ `TArray<FMovieSceneConsoleVariableCollection> ConsoleVariableCollections;` — `UPROPERTY(EditAnywhere, Category="Console Variable Collections")` — Array of console variable preset assets that this track should operate on
- L84 _public member_ `FMovieSceneCVarOverrides ConsoleVariables;` — `UPROPERTY(EditAnywhere, Category="Console Variables")` — The name of the console variable and the value, separated by ' ' or '=', ie: "foo.bar=1" or "foo.bar 1".

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCameraCutSection.h` (Public)


#### class `UMovieSceneCameraCutSection`  
`class UMovieSceneCameraCutSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L24-127_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: Movie CameraCuts are sections on the CameraCuts track, that show what the viewer "sees"
- L32 _public prototype_ `UMovieSceneCameraCutSection(const FObjectInitializer& Init);` — Constructs a new camera cut section
- L35 _public function_ `void SetCameraGuid(const FGuid& InGuid)` — Sets the camera binding for this CameraCut section. Evaluates from the sequence binding ID
- L42 _public function_ `const FMovieSceneObjectBindingID& GetCameraBindingID() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Gets the camera binding for this CameraCut section
- L49 _public function_ `void SetCameraBindingID(const FMovieSceneObjectBindingID& InCameraBindingID)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Sets the camera binding for this CameraCut section
- L55 _public prototype_ `virtual void OnBindingIDsUpdated(const TMap<UE::MovieScene::FFixedObjectBindingID, UE::MovieScene::FFixedObjectBindingID>& OldFixedToNewFixedMap, FMovieSceneSequenceID LocalSequenceID, TSharedRef<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState) override;`
- L56 _public prototype_ `virtual void GetReferencedBindings(TArray<FGuid>& OutBindings) override;`
- L59 _public prototype_ `virtual void PostLoad() override;` — ~UObject interface
- L69 _public prototype_ `UCameraComponent* GetFirstCamera(IMovieScenePlayer& Player, FMovieSceneSequenceID SequenceID) const;` — Resolve a camera component for this cut section from the specified player and sequence ID @param Player     The sequence player to use to resolve the object binding for this camera @param SequenceID The sequence ID for the specific instance that this section exists within @return A camera component to be used for this cut section, or nullptr if one was not found.
- L72 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L79 _public prototype_ `void ComputeInitialCameraCutTransform();` — Computes the transform of the bound camera at the section's start time. This is for internal use by UMovieSceneCameraCutTrack during pre-compilation.
- L82 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L87 _public member_ `bool bLockPreviousCamera = false;` — `UPROPERTY(EditAnywhere, Category="Section")` — When blending, lock the previous camera (camera cut or gameplay camera).
- L92 _private member_ `FGuid CameraGuid_DEPRECATED;` — `UPROPERTY()` — The camera possessable or spawnable that this movie CameraCut uses
- L96 _private member_ `FMovieSceneObjectBindingID CameraBindingID;` — `UPROPERTY(EditAnywhere, Category="Section")` — The camera binding that this movie CameraCut uses
- L100 _private member_ `FTransform InitialCameraCutTransform;` — `UPROPERTY()` — Camera transform at the start of the cut, computed at compile time
- L102 _private member_ `bool bHasInitialCameraCutTransform = false;` — `UPROPERTY()`
- L107 _public function_ `float GetThumbnailReferenceOffset() const` — @return The thumbnail reference frame offset from the start of this section
- L113 _public function_ `void SetThumbnailReferenceOffset(float InNewOffset)` — Set the thumbnail reference offset
- L123 _private member_ `float ThumbnailReferenceOffset;` — `UPROPERTY()` — The reference frame offset for single thumbnail rendering

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCameraShakeSection.h` (Public)


#### struct `FMovieSceneCameraShakeSectionData`  
`struct FMovieSceneCameraShakeSectionData`  
_L22-47_
- reflection: `USTRUCT()`
- L26 _public function_ `FMovieSceneCameraShakeSectionData() : ShakeClass(nullptr) , PlayScale(1.f) , PlaySpace(ECameraShakePlaySpace::CameraLocal) , UserDefinedPlaySpace(ForceInitToZero)`
- L36 _public member_ `TSubclassOf<UCameraShakeBase> ShakeClass;` — `UPROPERTY(EditAnywhere, Category = "Camera Shake")` — Class of the camera shake to play
- L40 _public member_ `float PlayScale;` — `UPROPERTY(EditAnywhere, Category = "Camera Shake")` — Scalar that affects shake intensity
- L43 _public member_ `ECameraShakePlaySpace PlaySpace;` — `UPROPERTY(EditAnywhere, Category = "Camera Shake")`
- L46 _public member_ `FRotator UserDefinedPlaySpace;` — `UPROPERTY(EditAnywhere, Category = "Camera Shake")`

#### class `UMovieSceneCameraShakeSection`  
`class UMovieSceneCameraShakeSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L50-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L58 _public prototype_ `UMovieSceneCameraShakeSection(const FObjectInitializer& ObjectInitializer);`
- L60 _public prototype_ `virtual void PostLoad() override;`
- L61 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L64 _public prototype_ `void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L69 _public member_ `FMovieSceneCameraShakeSectionData ShakeData;` — `UPROPERTY(EditAnywhere, Category="Camera Shake", meta=(ShowOnlyInnerProperties))`
- L74 _public member_ `TSubclassOf<UCameraShakeBase> ShakeClass_DEPRECATED;` — `UPROPERTY()`
- L77 _public member_ `float PlayScale_DEPRECATED;` — `UPROPERTY()`
- L80 _public member_ `ECameraShakePlaySpace PlaySpace_DEPRECATED;` — `UPROPERTY()`
- L83 _public member_ `FRotator UserDefinedPlaySpace_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCameraShakeSourceShakeSection.h` (Public)


#### class `UMovieSceneCameraShakeSourceShakeSection`  
`class UMovieSceneCameraShakeSourceShakeSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L17-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L24 _public prototype_ `UMovieSceneCameraShakeSourceShakeSection(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L29 _public prototype_ `void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L33 _public member_ `FMovieSceneCameraShakeSectionData ShakeData;` — `UPROPERTY(EditAnywhere, Category="Camera Shake", meta=(ShowOnlyInnerProperties))`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCameraShakeSourceTriggerSection.h` (Public)


#### class `UMovieSceneCameraShakeSourceTriggerSection`  
`class UMovieSceneCameraShakeSourceTriggerSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L18-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L25 _public prototype_ `UMovieSceneCameraShakeSourceTriggerSection(const FObjectInitializer& Init);`
- L27 _public function_ `const FMovieSceneCameraShakeSourceTriggerChannel& GetChannel() const`
- L30 _public prototype_ `bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;` — IMovieSceneEntityProvider interface
- L31 _public prototype_ `void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L35 _private member_ `FMovieSceneCameraShakeSourceTriggerChannel Channel;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCinematicShotSection.h` (Public)


#### class `UMovieSceneCinematicShotSection`  
`class UMovieSceneCinematicShotSection : public UMovieSceneSubSection`  
_L22-84_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UMovieSceneSubSection`
- desc: Implements a cinematic shot section.
- L30 _public prototype_ `UMovieSceneCinematicShotSection(const FObjectInitializer& ObjInitializer);` — Object constructor.
- L35 _private prototype_ `virtual void PostLoad() override;` — ~UObject interface
- L41 _public prototype_ `FString GetShotDisplayName() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — @return The shot display name. if empty, returns the sequence's name
- L45 _public function_ `void SetShotDisplayName(const FString& InShotDisplayName)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Set the shot display name
- L57 _private member_ `FString ShotDisplayName;` — `UPROPERTY()` — The Shot's display name
- L61 _private member_ `FText DisplayName_DEPRECATED;` — `UPROPERTY()` — The Shot's display name
- L66 _public function_ `float GetThumbnailReferenceOffset() const` — @return The shot thumbnail reference frame offset from the start of this section
- L72 _public function_ `void SetThumbnailReferenceOffset(float InNewOffset)` — Set the thumbnail reference offset
- L82 _private member_ `float ThumbnailReferenceOffset;` — `UPROPERTY()` — The shot's reference frame offset for single thumbnail rendering

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneColorSection.h` (Public)


#### struct `FMovieSceneColorKeyStruct`  
`struct FMovieSceneColorKeyStruct : public FMovieSceneKeyStruct`  
_L21-37_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Proxy structure for color section key data.
- L28 _public member_ `FLinearColor Color = FLinearColor(0.f, 0.f, 0.f, 1.f);` — `UPROPERTY(EditAnywhere, Category=Key, meta=(InlineColorPicker))` — The key's color value.
- L32 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L34 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L36 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneColorKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneColorKeyStruct>`  
_L38-38_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneColorKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneColorKeyStruct>`  
_L38-38_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneColorKeyStruct>`

#### class `UMovieSceneColorSection`  
`class UMovieSceneColorSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L45-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single floating point section
- L54 _public function_ `FMovieSceneFloatChannel& GetRedChannel()` — Access the underlying generation function for the red component of this section
- L55 _public function_ `const FMovieSceneFloatChannel& GetRedChannel() const`
- L58 _public function_ `FMovieSceneFloatChannel& GetGreenChannel()` — Access the underlying generation function for the green component of this section
- L59 _public function_ `const FMovieSceneFloatChannel& GetGreenChannel() const`
- L62 _public function_ `FMovieSceneFloatChannel& GetBlueChannel()` — Access the underlying generation function for the blue component of this section
- L63 _public function_ `const FMovieSceneFloatChannel& GetBlueChannel() const`
- L66 _public function_ `FMovieSceneFloatChannel& GetAlphaChannel()` — Access the underlying generation function for the alpha component of this section
- L67 _public function_ `const FMovieSceneFloatChannel& GetAlphaChannel() const`
- L72 _protected prototype_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles) override;`
- L77 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L78 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L84 _private member_ `FMovieSceneFloatChannel RedCurve;` — `UPROPERTY()` — Red curve data
- L88 _private member_ `FMovieSceneFloatChannel GreenCurve;` — `UPROPERTY()` — Green curve data
- L92 _private member_ `FMovieSceneFloatChannel BlueCurve;` — `UPROPERTY()` — Blue curve data
- L96 _private member_ `FMovieSceneFloatChannel AlphaCurve;` — `UPROPERTY()` — Alpha curve data

#### Free symbols / members of external scopes

- L38 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneColorKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneColorKeyStruct> { enum { WithCopy = false }; }; /** * A single floating point section */ UCLASS(MinimalAPI) class UMovieSceneColorSection` (scope `TStructOpsTypeTraits::__anonbe530e6b0103`)

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneComponentMaterialParameterSection.h` (Public)


#### struct `FScalarMaterialParameterInfoAndCurve`  
`struct FScalarMaterialParameterInfoAndCurve`  
_L19-46_
- reflection: `USTRUCT()`
- desc: Structure representing an animated scalar parameter and it's associated animation curve.
- L23 _public function_ `FScalarMaterialParameterInfoAndCurve()`
- L27 _public prototype_ `FScalarMaterialParameterInfoAndCurve(const FMaterialParameterInfo& InParameterInfo);` — Creates a new FScalarMaterialParameterInfoAndCurve for a specific scalar parameter.
- L31 _public member_ `FMaterialParameterInfo ParameterInfo;` — `UPROPERTY()` — The material parameter info of the scalar parameter which is being animated.
- L35 _public member_ `FMovieSceneFloatChannel ParameterCurve;` — `UPROPERTY()` — The curve which contains the animation data for the scalar parameter.
- L40 _public member_ `FString ParameterLayerName;` — `UPROPERTY()` — Editor-only name of parameter layer, if applicable
- L44 _public member_ `FString ParameterAssetName;` — `UPROPERTY()` — Editor-only name of parameter asset, if applicable

#### struct `FColorMaterialParameterInfoAndCurves`  
`struct FColorMaterialParameterInfoAndCurves`  
_L52-95_
- reflection: `USTRUCT()`
- desc: Structure representing an animated color parameter and it's associated animation curve.
- L56 _public function_ `FColorMaterialParameterInfoAndCurves()`
- L60 _public prototype_ `FColorMaterialParameterInfoAndCurves(const FMaterialParameterInfo& InParameterInfo);` — Creates a new FVectorParameterNameAndCurve for a specific color parameter.
- L64 _public member_ `FMaterialParameterInfo ParameterInfo;` — `UPROPERTY()` — The name of the color parameter which is being animated.
- L68 _public member_ `FMovieSceneFloatChannel RedCurve;` — `UPROPERTY()` — The curve which contains the animation data for the red component of the color parameter.
- L72 _public member_ `FMovieSceneFloatChannel GreenCurve;` — `UPROPERTY()` — The curve which contains the animation data for the green component of the color parameter.
- L76 _public member_ `FMovieSceneFloatChannel BlueCurve;` — `UPROPERTY()` — The curve which contains the animation data for the blue component of the color parameter.
- L80 _public member_ `FMovieSceneFloatChannel AlphaCurve;` — `UPROPERTY()` — The curve which contains the animation data for the alpha component of the color parameter.
- L85 _public member_ `FString ParameterLayerName;` — `UPROPERTY()` — Name of parameter layer, if applicable
- L89 _public member_ `FString ParameterAssetName;` — `UPROPERTY()` — Name of parameter asset, if applicable
- L93 _public member_ `FParameterChannelNames ParameterChannelNames;` — `UPROPERTY()` — Optional UI names for parameter channels, if applicable

#### class `UMovieSceneComponentMaterialParameterSection`  
`class UMovieSceneComponentMaterialParameterSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L101-177_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A movie scene section containing data for material parameters.
- L110 _public prototype_ `void AddScalarParameterKey(const FMaterialParameterInfo& InParameterInfo, FFrameNumber InTime, float InValue, const FString& InLayerName, const FString& InAssetName, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific scalar parameter at the specified time with the specified value.
- L114 _public prototype_ `void AddColorParameterKey(const FMaterialParameterInfo& InParameterInfo, FFrameNumber InTime, FLinearColor InValue, const FString& InLayerName, const FString& InAssetName, const FParameterChannelNames& InChannelNames=FParameterChannelNames(), EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific color parameter at the specified time with the specified value.
- L123 _public prototype_ `bool RemoveScalarParameter(const FMaterialParameterInfo& InParameterInfo);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a scalar parameter from this section. @param InParameterInfo The material parameter info of the scalar parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L132 _public prototype_ `bool RemoveColorParameter(const FMaterialParameterInfo& InParameterInfo);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a color parameter from this section. @param InParameterInfo The material parameter info of the color parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L142 _public prototype_ `bool RemoveScalarParameter(FName InParameterPath);` — Removes a scalar parameter from this section. @param InParameterPath The full path name of the scalar parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L150 _public prototype_ `bool RemoveColorParameter(FName InParameterPath);` — Removes a color parameter from this section. @param InParameterPath The full path name of the color parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L153 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L154 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L156 _public prototype_ `void ExternalPopulateEvaluationField(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder);`
- L163 _public member_ `TArray<FScalarMaterialParameterInfoAndCurve> ScalarParameterInfosAndCurves;` — `UPROPERTY()` — The scalar parameter infos and their associated curves.
- L167 _public member_ `TArray<FColorMaterialParameterInfoAndCurves> ColorParameterInfosAndCurves;` — `UPROPERTY()` — The color parameter infos and their associated curves.
- L172 _protected prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L173 _protected prototype_ `virtual void PostEditImport() override;`
- L175 _protected prototype_ `virtual void PostEditUndo() override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneConsoleVariableTrackInterface.h` (Public)


#### class `UMovieSceneConsoleVariableTrackInterface`  
`class UMovieSceneConsoleVariableTrackInterface : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieSceneConsoleVariableTrackInterface`  
`class IMovieSceneConsoleVariableTrackInterface`  
_L19-26_
- L24 _public prototype_ `virtual void GetConsoleVariablesForTrack(bool bOnlyIncludeChecked, TArray<TTuple<FString, FString>>& OutVariables) = 0;`
- L25 _public prototype_ `virtual bool IsConsoleVariableEnabled(const FString& ConsoleVariableName) = 0;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneConstrainedSection.h` (Public)


#### class `UMovieSceneConstrainedSection`  
`class UMovieSceneConstrainedSection : public UInterface`  
_L22-26_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieSceneConstrainedSection`  
`class IMovieSceneConstrainedSection`  
_L31-121_
- desc: Interface to be added to UMovieSceneSection types when they contain entity data
- L36 _public prototype_ `IMovieSceneConstrainedSection();`
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConstraintChannelAddedEvent, IMovieSceneConstrainedSection*, FMovieSceneConstraintChannel*);`
- L44 _public prototype_ `virtual bool HasConstraintChannel(const FGuid& InGuid) const = 0;` — If it has that constraint with that Name
- L49 _public prototype_ `virtual FConstraintAndActiveChannel* GetConstraintChannel(const FGuid& InConstraintGuid) = 0;` — Get constraint with that name
- L54 _public prototype_ `virtual void AddConstraintChannel(UTickableConstraint* InConstraint) = 0;` — Add Constraint channel
- L59 _public prototype_ `virtual void RemoveConstraintChannel(const UTickableConstraint* InConstraint) = 0;` — Remove Constraint channel
- L64 _public prototype_ `virtual TArray<FConstraintAndActiveChannel>& GetConstraintsChannels() = 0;` — Get a reference to the channels
- L69 _public prototype_ `virtual const TArray<FConstraintAndActiveChannel>& GetConstraintsChannels() const = 0;` — Get a const reference to the channels
- L74 _public prototype_ `virtual void ReplaceConstraint(const FName InConstraintName, UTickableConstraint* InConstraint) = 0;` — Replace the constraint with the specified name with the new one
- L79 _public function_ `FConstraintChannelAddedEvent& ConstraintChannelAdded()` — Added Delegate
- L84 _public function_ `virtual void OnConstraintsChanged()` — What to do if the constraint object has been changed, for example by an undo or redo. By default nothing to be overriden if needed.
- L89 _public prototype_ `void SetDoNoRemoveChannel(bool bInDoNotRemoveChannel);` — SetToNotRemoveChannel when we are told a constraint is removed, we need this sometimes sincet his will be destructive
- L94 _public member_ `FDelegateHandle OnConstraintRemovedHandle;` — Removed delegate that get's added by the track editor
- L99 _public prototype_ `UTickableConstraint* FindConstraint(const FName InConstraintName) const;` — Find the constraint named ConstraintName
- L104 _public prototype_ `UTickableConstraint* FindConstraint(FMovieSceneChannel* InChannel) const;` — Find the constraint from the channel
- L109 _public prototype_ `bool RemoveConstraint(UWorld* InWorld, const FName InConstraintName, const bool bDoNotCompensate) const;` — Removes the constraint named ConstraintName
- L114 _public prototype_ `bool RemoveAllConstraints(UWorld* InWorld, const bool bDoNotCompensate) const;` — Removes all the constraints stored in this section
- L118 _protected member_ `FConstraintChannelAddedEvent OnConstraintChannelAdded;`
- L119 _protected member_ `bool bDoNotRemoveChannel = false;`

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FConstraintChannelAddedEvent, IMovieSceneConstrainedSection*, FMovieSceneConstraintChannel*);`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneCustomPrimitiveDataSection.h` (Public)


#### class `UMovieSceneCustomPrimitiveDataSection`  
`class UMovieSceneCustomPrimitiveDataSection : public UMovieSceneParameterSection`  
_L15-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneParameterSection`
- desc: Movie scene section that animates custom primitive data scalars, vector2s, vector3s, and colors
- L21 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L23 _public prototype_ `void ExternalPopulateEvaluationField(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder);`
- L26 _public prototype_ `void ReconstructChannelProxy() override;`
- L33 _public function_ `uint64 GetChannelsUsed() const`
- L38 _protected member_ `uint64 ChannelsUsedBitmap = 0;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneDataLayerSection.h` (Public)


#### class `UMovieSceneDataLayerSection`  
`class UMovieSceneDataLayerSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L13-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L21 _public prototype_ `UMovieSceneDataLayerSection(const FObjectInitializer& ObjInit);`
- L24 _public prototype_ `EDataLayerRuntimeState GetDesiredState() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L27 _public prototype_ `void SetDesiredState(EDataLayerRuntimeState InDesiredState);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L30 _public prototype_ `EDataLayerRuntimeState GetPrerollState() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L33 _public prototype_ `void SetPrerollState(EDataLayerRuntimeState InPrerollState);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L36 _public prototype_ `bool GetFlushOnActivated() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L39 _public prototype_ `void SetFlushOnActivated(bool bFlushOnActivated);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L42 _public prototype_ `bool GetFlushOnUnload() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L45 _public prototype_ `void SetFlushOnUnload(bool bFlushOnUnload);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L48 _public function_ `const TArray<UDataLayerAsset*>& GetDataLayerAssets() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L51 _public function_ `void SetDataLayerAssets(const TArray<UDataLayerAsset*>& InDataLayerAssets)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L55 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L60 _private member_ `TArray<TObjectPtr<UDataLayerAsset>> DataLayerAssets;` — `UPROPERTY(EditAnywhere, Category = DataLayer)` — A list of data layers that should be loaded or unloaded by this section
- L64 _private member_ `EDataLayerRuntimeState DesiredState;` — `UPROPERTY(EditAnywhere, Category=DataLayer)` — The desired state for the data layers on this section when the section is actively evaluating.
- L68 _private member_ `EDataLayerRuntimeState PrerollState;` — `UPROPERTY(EditAnywhere, Category=DataLayer, Meta=(EditCondition="HasPreRoll", EditConditionHides))` — The desired state for the data layers on this section when the section is pre or post-rolling.
- L72 _private member_ `bool bFlushOnActivated;` — `UPROPERTY(EditAnywhere, Category=DataLayer, Meta=(EditCondition="DesiredState == EDataLayerRuntimeState::Activated", EditConditionHides))` — Determine if we need to flush level streaming when the data layers are activated. May result in a hitch.
- L76 _private member_ `bool bFlushOnUnload;` — `UPROPERTY(EditAnywhere, Category=DataLayer, Meta=(EditCondition="DesiredState == EDataLayerRuntimeState::Unloaded", EditConditionHides))` — Determine if we need to flush level streaming when the data layers unloads.
- L79 _private function_ `bool HasPreRoll() const` — `UFUNCTION()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneDoubleSection.h` (Public)


#### class `UMovieSceneDoubleSection`  
`class UMovieSceneDoubleSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L19-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A double precision floating point section
- L25 _private prototype_ `UMovieSceneDoubleSection(const FObjectInitializer& ObjectInitializer);`
- L32 _public function_ `FMovieSceneDoubleChannel& GetChannel()` — Public access to this section's internal data function
- L33 _public function_ `const FMovieSceneDoubleChannel& GetChannel() const`
- L39 _protected member_ `FMovieSceneDoubleChannel DoubleCurve;` — `UPROPERTY()` — Double data
- L43 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L44 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L46 _private prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneEnumSection.h` (Public)


#### class `UMovieSceneEnumSection`  
`class UMovieSceneEnumSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single enum section.
- L26 _public member_ `FMovieSceneByteChannel EnumCurve;` — `UPROPERTY()` — Ordered curve data
- L31 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L32 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneEventRepeaterSection.h` (Public)


#### class `UMovieSceneEventRepeaterSection`  
`class UMovieSceneEventRepeaterSection : public UMovieSceneEventSectionBase , public IMovieSceneEntityProvider`  
_L15-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEventSectionBase,IMovieSceneEntityProvider`
- desc: Event section that will trigger its event exactly once, every time it is evaluated.
- L22 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L23 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L26 _public function_ `virtual TArrayView<FMovieSceneEvent> GetAllEntryPoints() override`
- L31 _public member_ `FMovieSceneEvent Event;` — `UPROPERTY(EditAnywhere, Category="Event")` — The event that should be triggered each time this section is evaluated

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneEventSection.h` (Public)


#### struct `FMovieSceneEventParameters`  
`struct FMovieSceneEventParameters`  
_L22-101_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public function_ `FMovieSceneEventParameters() : PackageFileVersion(GPackageFileUEVersion) , LicenseePackageFileVersion(GPackageFileLicenseeUEVersion )`
- L32 _public function_ `FMovieSceneEventParameters(UScriptStruct& InStruct) : StructType(&InStruct) , PackageFileVersion(GPackageFileUEVersion) , LicenseePackageFileVersion(GPackageFileLicenseeUEVersion )` — Construction from a struct type
- L47 _public function_ `UScriptStruct* GetStructType() const` — Access the struct type of this event parameter payload @return A valid UScriptStruct* or nullptr if the struct is not set, or no longer available
- L55 _public function_ `void Reassign(UScriptStruct* NewStruct)` — Change the type of this event parameter payload to be the specified struct
- L70 _public prototype_ `void GetInstance(FStructOnScope& OutStruct) const;` — Retrieve an instance of this payload @param OutStruct Structure to receive the instance
- L77 _public prototype_ `void OverwriteWith(uint8* InstancePtr);` — Overwrite this payload with another instance of the same type. @param InstancePtr A valid pointer to an instance of the type represented by GetStructType
- L82 _public prototype_ `bool Serialize(FArchive& Ar);` — Serialization implementation
- L93 _private member_ `FSoftObjectPath StructType;` — Soft object path to the type of this parameter payload
- L96 _private member_ `FPackageFileVersion PackageFileVersion;` — Used while loading to pass along to the FEventParameterReader
- L97 _private member_ `int32 LicenseePackageFileVersion;`
- L100 _private member_ `TArray<uint8> StructBytes;` — Serialized bytes that represent the payload. Serialized internally with FEventParameterArchive

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneEventParameters> : public TStructOpsTypeTraitsBase2<FMovieSceneEventParameters>`  
_L104-111_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneEventParameters>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L107-110_

#### struct `FEventPayload`  
`struct FEventPayload`  
_L114-137_
- reflection: `USTRUCT(BlueprintType)`
- L118 _public function_ `FEventPayload()`
- L119 _public function_ `FEventPayload(FName InEventName) : EventName(InEventName)`
- L132 _public member_ `FName EventName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Event)` — The name of the event to trigger
- L136 _public member_ `FMovieSceneEventParameters Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Event, meta=(ShowOnlyInnerProperties))` — The event parameters

#### struct `FMovieSceneEventSectionData`  
`struct FMovieSceneEventSectionData : public FMovieSceneChannel`  
_L141-221_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- desc: A curve of events
- L149 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called after this section data has been serialized to upgrade old data
- L157 _public function_ `inline TMovieSceneChannelData<FEventPayload> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L167 _public function_ `inline TMovieSceneChannelData<const FEventPayload> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L172 _public function_ `TArrayView<const FFrameNumber> GetKeyTimes() const`
- L177 _public function_ `TArrayView<const FEventPayload> GetKeyValues() const`
- L185 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L186 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L187 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L188 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L189 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L190 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L191 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L192 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L193 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L194 _public prototype_ `virtual void Reset() override;`
- L195 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L196 _public prototype_ `virtual FKeyHandle GetHandle(int32 Index) override;`
- L197 _public prototype_ `virtual int32 GetIndex(FKeyHandle Handle) override;`
- L198 _public function_ `virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override`
- L199 _public function_ `virtual void ClearDefault() override`
- L204 _private member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(meta=(KeyTimes))`
- L208 _private member_ `TArray<FEventPayload> KeyValues;` — `UPROPERTY(meta=(KeyValues))` — Array of values that correspond to each key time
- L212 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)` — This needs to be a UPROPERTY so it gets saved into editor transactions but transient so it doesn't get saved into assets.
- L218 _private member_ `TArray<float> KeyTimes_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneEventSectionData> : public TStructOpsTypeTraitsBase2<FMovieSceneEventSectionData>`  
_L225-228_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneEventSectionData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L227-227_

#### class `UMovieSceneEventSection`  
`class UMovieSceneEventSection : public UMovieSceneSection`  
_L235-264_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Implements a section in movie scene event tracks.
- L241 _private prototype_ `UMovieSceneEventSection();` — Default constructor.
- L246 _public prototype_ `virtual void PostLoad() override;`
- L253 _public function_ `const FMovieSceneEventSectionData& GetEventData() const` — Get the section's event data. @return Event data.
- L260 _private member_ `FNameCurve Events_DEPRECATED;` — `UPROPERTY()`
- L263 _private member_ `FMovieSceneEventSectionData EventData;` — `UPROPERTY()`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneEventSectionData> : TMovieSceneChannelTraitsBase<FMovieSceneEventSectionData>`  
_L267-270_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneEventSectionData>`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L269-269_

#### Free symbols / members of external scopes

- L84 _function_ `friend FArchive& operator<<(FArchive& Ar, FMovieSceneEventParameters& Payload)`
- L108 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon8c7da38e0103`)
- L109 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon8c7da38e0103`)
- L121 _function_ `friend bool operator==(const FEventPayload& A, const FEventPayload& B)`
- L126 _function_ `friend bool operator!=(const FEventPayload& A, const FEventPayload& B)`
- L227 _enumerator_ `enum { WithPostSerialize = true };` (scope `TStructOpsTypeTraits::__anon8c7da38e0203`)
- L269 _enumerator_ `enum { SupportsDefaults = false };` (scope `TMovieSceneChannelTraits::__anon8c7da38e0303`)
- L273 _function_ `inline bool EvaluateChannel(const FMovieSceneEventSectionData* InChannel, FFrameTime InTime, FEventPayload& OutValue)` — Stub out unnecessary functions
- L279 _function_ `inline bool ValueExistsAtTime(const FMovieSceneEventSectionData* InChannel, FFrameNumber Time, const FEventPayload& Value)`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneEventSectionBase.h` (Public)


#### class `UMovieSceneEventSectionBase`  
`class UMovieSceneEventSectionBase : public UMovieSceneSection`  
_L15-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Base class for all event sections. Manages dirtying the section and track on recompilation of the director blueprint.
- L21 _public prototype_ `UMovieSceneEventSectionBase(const FObjectInitializer& ObjInit);`
- L23 _public function_ `virtual TArrayView<FMovieSceneEvent> GetAllEntryPoints()`
- L25 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L29 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L30 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L31 _public prototype_ `virtual void RemoveForCook() override;`
- L33 _public prototype_ `void AttemptUpgrade();`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FFixupPayloadParameterNameEvent, UMovieSceneEventSectionBase*, UK2Node*, FName, FName);`
- L36 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpgradeLegacyEventEndpoint, UMovieSceneEventSectionBase*);`
- L37 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, UMovieSceneEventSectionBase*);`
- L38 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(void, FRemoveForCookEvent, UMovieSceneEventSectionBase*);`
- L43 _public function_ `void OnUserDefinedPinRenamed(UK2Node* InNode, FName OldPinName, FName NewPinName)` — Handler should be invoked when an event endpoint that is referenced from this section has one of its pins renamed
- L51 _public prototype_ `void OnPostCompile(UBlueprint* Blueprint);` — Post compilation handler that is invoked once generated function graphs have been compiled. Fixes up UFunction pointers for each event.
- L57 _public member_ `static FFixupPayloadParameterNameEvent FixupPayloadParameterNameEvent;` — Event that is broadcast when event payloads may need fixing up due to a pin rename
- L62 _public member_ `static FUpgradeLegacyEventEndpoint UpgradeLegacyEventEndpoint;` — Delegate that is used to upgrade legacy event sections that need fixing up against a blueprint. Called on serialization and on compilation if necessary until successful upgrade occurs.
- L67 _public member_ `static FPostDuplicateEvent PostDuplicateSectionEvent;` — Delegate that is used to ensure that a blueprint compile hook exists for this event section after it has been duplicated.
- L72 _public member_ `static FRemoveForCookEvent RemoveForCookEvent;` — Delegate that is used to ensure that a hook exists for this event section before it has been removed for cook.
- L78 _private member_ `bool bDataUpgradeRequired;` — Boolean that specifies whether AttemptUpgrade needs to do any work. This is necessary because all the data required for the upgrade may not be loaded at the time ::Serialize is called, so another attempt may be necessary as the blueprint is compiled

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FFixupPayloadParameterNameEvent, UMovieSceneEventSectionBase*, UK2Node*, FName, FName);`
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FUpgradeLegacyEventEndpoint, UMovieSceneEventSectionBase*);`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(void, FPostDuplicateEvent, UMovieSceneEventSectionBase*);`
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(void, FRemoveForCookEvent, UMovieSceneEventSectionBase*);`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneEventTriggerSection.h` (Public)


#### class `UMovieSceneEventTriggerSection`  
`class UMovieSceneEventTriggerSection : public UMovieSceneEventSectionBase , public IMovieSceneEntityProvider`  
_L15-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEventSectionBase,IMovieSceneEntityProvider`
- desc: Event section that triggeres specific timed events.
- L22 _public prototype_ `UMovieSceneEventTriggerSection(const FObjectInitializer& ObjInit);`
- L24 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L25 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L28 _public function_ `virtual TArrayView<FMovieSceneEvent> GetAllEntryPoints() override`
- L33 _public member_ `FMovieSceneEventChannel EventChannel;` — `UPROPERTY()` — The channel that defines this section's timed events

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneFadeSection.h` (Public)


#### class `UMovieSceneFadeSection`  
`class UMovieSceneFadeSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L23-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single floating point section.
- L30 _private prototype_ `UMovieSceneFadeSection();` — Default constructor.
- L33 _private prototype_ `void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L39 _public member_ `FMovieSceneFloatChannel FloatCurve;` — `UPROPERTY()` — Float data
- L43 _public member_ `FLinearColor FadeColor;` — `UPROPERTY(EditAnywhere, Category="Fade")` — Fade color.
- L47 _public member_ `uint32 bFadeAudio:1;` — `UPROPERTY(EditAnywhere, Category="Fade")` — Fade audio.

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneFloatSection.h` (Public)


#### class `UMovieSceneFloatSection`  
`class UMovieSceneFloatSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneChannelOverrideProvider`  
_L20-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneChannelOverrideProvider`
- desc: A single floating point section
- L27 _private prototype_ `UMovieSceneFloatSection(const FObjectInitializer& ObjectInitializer);`
- L34 _public function_ `FMovieSceneFloatChannel& GetChannel()` — Public access to this section's internal data function
- L35 _public function_ `const FMovieSceneFloatChannel& GetChannel() const`
- L39 _protected prototype_ `virtual UMovieSceneSectionChannelOverrideRegistry* GetChannelOverrideRegistry(bool bCreateIfMissing) override;`
- L40 _protected prototype_ `virtual UE::MovieScene::FChannelOverrideProviderTraitsHandle GetChannelOverrideProviderTraits() const override;`
- L41 _protected prototype_ `virtual void OnChannelOverridesChanged() override;`
- L47 _protected member_ `FMovieSceneFloatChannel FloatCurve;` — `UPROPERTY()` — Float data
- L51 _protected member_ `TObjectPtr<UMovieSceneSectionChannelOverrideRegistry> OverrideRegistry;` — `UPROPERTY()` — Channel overrides
- L55 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L56 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L58 _private prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L61 _private prototype_ `virtual void PostPaste() override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneIntegerSection.h` (Public)


#### class `UMovieSceneIntegerSection`  
`class UMovieSceneIntegerSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L19-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single integer section.
- L29 _public function_ `const FMovieSceneIntegerChannel& GetChannel() const` — Access this section's underlying raw data
- L34 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L35 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L41 _private member_ `FMovieSceneIntegerChannel IntegerCurve;` — `UPROPERTY()` — Ordered curve data

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneLevelVisibilitySection.h` (Public)


#### enum `ELevelVisibility`  
`enum class ELevelVisibility : uint8`  
_L17-24_
- reflection: `UENUM()`
- desc: Visibility options for the level visibility section.
- L20 _public enumerator_ `Visible` — The streamed levels should be visible.
- L23 _public enumerator_ `Hidden` — The streamed levels should be hidden.

#### class `UMovieSceneLevelVisibilitySection`  
`class UMovieSceneLevelVisibilitySection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L31-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A section for use with the movie scene level visibility track, which controls streamed level visibility.
- L40 _public prototype_ `ELevelVisibility GetVisibility() const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L43 _public prototype_ `void SetVisibility(ELevelVisibility InVisibility);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L46 _public function_ `const TArray<FName>& GetLevelNames() const` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")`
- L49 _public function_ `void SetLevelNames(const TArray<FName>& InLevelNames)` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")`
- L53 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L59 _private member_ `ELevelVisibility Visibility;` — `UPROPERTY(EditAnywhere, Category = LevelVisibility)` — Whether or not the levels in this section should be visible or hidden.
- L63 _private member_ `TArray<FName> LevelNames;` — `UPROPERTY(EditAnywhere, Category = LevelVisibility)` — The short names of the levels who's visibility is controlled by this section.

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneObjectPropertySection.h` (Public)


#### class `UMovieSceneObjectPropertySection`  
`class UMovieSceneObjectPropertySection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L16-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L24 _public prototype_ `UMovieSceneObjectPropertySection(const FObjectInitializer& ObjInit);`
- L27 _public prototype_ `virtual void PostLoad() override;`
- L32 _public member_ `FMovieSceneObjectPathChannel ObjectChannel;` — `UPROPERTY()`
- L35 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L36 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneParameterSection.h` (Public)


#### class `UMovieSceneParameterSectionExtender`  
`class UMovieSceneParameterSectionExtender : public UInterface`  
_L21-25_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieSceneParameterSectionExtender`  
`class IMovieSceneParameterSectionExtender`  
_L27-38_
- L33 _public prototype_ `void ExtendEntity(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity);`
- L37 _private prototype_ `virtual void ExtendEntityImpl(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) = 0;`

#### struct `FScalarParameterNameAndValue`  
`struct FScalarParameterNameAndValue`  
_L45-59_
- desc: Structure representing the animated value of a scalar parameter.
- L48 _public function_ `FScalarParameterNameAndValue(FName InParameterName, float InValue)` — Creates a new FScalarParameterAndValue with a parameter name and a value.
- L55 _public member_ `FName ParameterName;` — The name of the scalar parameter.
- L58 _public member_ `float Value;` — The animated value of the scalar parameter.

#### struct `FBoolParameterNameAndValue`  
`struct FBoolParameterNameAndValue`  
_L64-78_
- desc: Structure representing the value of a bool parameter.
- L67 _public function_ `FBoolParameterNameAndValue(FName InParameterName, bool InValue)` — Creates a new FScalarParameterAndValue with a parameter name and a value.
- L74 _public member_ `FName ParameterName;` — The name of the bool parameter.
- L77 _public member_ `bool Value;` — The value of the bool parameter.

#### struct `FVector2DParameterNameAndValue`  
`struct FVector2DParameterNameAndValue`  
_L83-97_
- desc: Structure representing the animated value of a vector2D parameter.
- L86 _public function_ `FVector2DParameterNameAndValue(FName InParameterName, FVector2D InValue)` — Creates a new FVectorParameterAndValue with a parameter name and a value.
- L93 _public member_ `FName ParameterName;` — The name of the vector parameter.
- L96 _public member_ `FVector2D Value;` — The animated value of the vector parameter.

#### struct `FVectorParameterNameAndValue`  
`struct FVectorParameterNameAndValue`  
_L102-116_
- desc: Structure representing the animated value of a vector parameter.
- L105 _public function_ `FVectorParameterNameAndValue(FName InParameterName, FVector InValue)` — Creates a new FVectorParameterAndValue with a parameter name and a value.
- L112 _public member_ `FName ParameterName;` — The name of the vector parameter.
- L115 _public member_ `FVector Value;` — The animated value of the vector parameter.

#### struct `FColorParameterNameAndValue`  
`struct FColorParameterNameAndValue`  
_L121-135_
- desc: Structure representing the animated value of a color parameter.
- L124 _public function_ `FColorParameterNameAndValue(FName InParameterName, FLinearColor InValue)` — Creates a new FColorParameterAndValue with a parameter name and a value.
- L131 _public member_ `FName ParameterName;` — The name of the color parameter.
- L134 _public member_ `FLinearColor Value;` — The animated value of the color parameter.

#### struct `FTransformParameterNameAndValue`  
`struct FTransformParameterNameAndValue`  
_L137-155_
- L141 _public member_ `FName ParameterName;` — The name of the transform  parameter.
- L143 _public member_ `FVector Translation;` — Translation component
- L145 _public member_ `FRotator Rotation;` — Rotation component
- L147 _public member_ `FVector Scale;` — Scale component
- L149 _public function_ `FTransformParameterNameAndValue(FName InParameterName,const FVector& InTranslation, const FRotator& InRotation, const FVector& InScale) : Translation(InTranslation), Rotation(InRotation), Scale(InScale)`

#### struct `FBaseParameterNameAndValue`  
`struct FBaseParameterNameAndValue`  
_L161-177_
- reflection: `USTRUCT()`
- desc: Structure representing a parameter name without a value
- L165 _public function_ `FBaseParameterNameAndValue() : ParameterName(NAME_None)`
- L170 _public function_ `FBaseParameterNameAndValue(FName InParameterName) : ParameterName(InParameterName)` — Creates a new FScalarParameterNameAndCurve for a specific scalar parameter.
- L176 _public member_ `FName ParameterName;` — `UPROPERTY()` — The name of the parameter which is being animated.

#### struct `FBoolParameterNameAndCurve`  
`struct FBoolParameterNameAndCurve : public FBaseParameterNameAndValue`  
_L183-197_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing a bool parameter and it's associated animation curve.
- L187 _public function_ `FBoolParameterNameAndCurve()`
- L190 _public function_ `FBoolParameterNameAndCurve(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L196 _public member_ `FMovieSceneBoolChannel ParameterCurve;` — `UPROPERTY()` — The curve which contains the animation data for the scalar parameter.

#### struct `FScalarParameterNameAndCurve`  
`struct FScalarParameterNameAndCurve : public FBaseParameterNameAndValue`  
_L203-217_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing an animated scalar parameter and it's associated animation curve.
- L207 _public function_ `FScalarParameterNameAndCurve()`
- L210 _public function_ `FScalarParameterNameAndCurve(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L216 _public member_ `FMovieSceneFloatChannel ParameterCurve;` — `UPROPERTY()` — The curve which contains the animation data for the scalar parameter.

#### struct `FVector2DParameterNameAndCurves`  
`struct FVector2DParameterNameAndCurves : public FBaseParameterNameAndValue`  
_L223-242_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing an animated vector2D parameter and it's associated animation curve.
- L227 _public function_ `FVector2DParameterNameAndCurves()`
- L230 _public function_ `FVector2DParameterNameAndCurves(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L236 _public member_ `FMovieSceneFloatChannel XCurve;` — `UPROPERTY()` — The curve which contains the animation data for the x component of the vector parameter.
- L240 _public member_ `FMovieSceneFloatChannel YCurve;` — `UPROPERTY()` — The curve which contains the animation data for the y component of the vector parameter.

#### struct `FVectorParameterNameAndCurves`  
`struct FVectorParameterNameAndCurves : public FBaseParameterNameAndValue`  
_L249-271_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing an animated vector parameter and it's associated animation curve.
- L253 _public function_ `FVectorParameterNameAndCurves()`
- L256 _public function_ `FVectorParameterNameAndCurves(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L262 _public member_ `FMovieSceneFloatChannel XCurve;` — `UPROPERTY()` — The curve which contains the animation data for the x component of the vector parameter.
- L266 _public member_ `FMovieSceneFloatChannel YCurve;` — `UPROPERTY()` — The curve which contains the animation data for the y component of the vector parameter.
- L270 _public member_ `FMovieSceneFloatChannel ZCurve;` — `UPROPERTY()` — The curve which contains the animation data for the z component of the vector parameter.

#### struct `FColorParameterNameAndCurves`  
`struct FColorParameterNameAndCurves : public FBaseParameterNameAndValue`  
_L278-304_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing an animated color parameter and it's associated animation curve.
- L282 _public function_ `FColorParameterNameAndCurves()`
- L285 _public function_ `FColorParameterNameAndCurves(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L291 _public member_ `FMovieSceneFloatChannel RedCurve;` — `UPROPERTY()` — The curve which contains the animation data for the red component of the color parameter.
- L295 _public member_ `FMovieSceneFloatChannel GreenCurve;` — `UPROPERTY()` — The curve which contains the animation data for the green component of the color parameter.
- L299 _public member_ `FMovieSceneFloatChannel BlueCurve;` — `UPROPERTY()` — The curve which contains the animation data for the blue component of the color parameter.
- L303 _public member_ `FMovieSceneFloatChannel AlphaCurve;` — `UPROPERTY()` — The curve which contains the animation data for the alpha component of the color parameter.

#### struct `FTransformParameterNameAndCurves`  
`struct FTransformParameterNameAndCurves : public FBaseParameterNameAndValue`  
_L310-332_
- reflection: `USTRUCT()`
- inherits: `FBaseParameterNameAndValue`
- desc: Structure representing an animated transform parameter and it's associated animation curve.
- L314 _public function_ `FTransformParameterNameAndCurves()`
- L317 _public function_ `FTransformParameterNameAndCurves(FName InParameterName) : FBaseParameterNameAndValue(InParameterName)`
- L323 _public member_ `FMovieSceneFloatChannel Translation[3];` — `UPROPERTY()` — Translation curves
- L327 _public member_ `FMovieSceneFloatChannel Rotation[3];` — `UPROPERTY()` — Rotation curves
- L331 _public member_ `FMovieSceneFloatChannel Scale[3];` — `UPROPERTY()` — Scale curves

#### class `UMovieSceneParameterSection`  
`class UMovieSceneParameterSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L337-486_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single movie scene section which can contain data for multiple named parameters.
- L346 _public prototype_ `void AddScalarParameterKey(FName InParameterName, FFrameNumber InTime, float InValue, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific scalar parameter at the specified time with the specified value.
- L350 _public prototype_ `void AddBoolParameterKey(FName InParameterName, FFrameNumber InTime, bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific bool parameter at the specified time with the specified value.
- L354 _public prototype_ `void AddVector2DParameterKey(FName InParameterName, FFrameNumber InTime, FVector2D InValue, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific vector2D parameter at the specified time with the specified value.
- L358 _public prototype_ `void AddVectorParameterKey(FName InParameterName, FFrameNumber InTime, FVector InValue, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific vector parameter at the specified time with the specified value.
- L362 _public prototype_ `void AddColorParameterKey(FName InParameterName, FFrameNumber InTime, FLinearColor InValue, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific color parameter at the specified time with the specified value.
- L366 _public prototype_ `void AddTransformParameterKey(FName InParameterName, FFrameNumber InTime, const FTransform& InValue, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Adds a a key for a specific color parameter at the specified time with the specified value.
- L375 _public prototype_ `bool RemoveScalarParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a scalar parameter from this section. @param InParameterName The name of the scalar parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L384 _public prototype_ `bool RemoveBoolParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a bool parameter from this section. @param InParameterName The name of the bool parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L393 _public prototype_ `bool RemoveVector2DParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a vector2D parameter from this section. @param InParameterName The name of the vector2D parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L402 _public prototype_ `bool RemoveVectorParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a vector parameter from this section. @param InParameterName The name of the vector parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L411 _public prototype_ `bool RemoveColorParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a color parameter from this section. @param InParameterName The name of the color parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L420 _public prototype_ `bool RemoveTransformParameter(FName InParameterName);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Section")` — Removes a transform parameter from this section. @param InParameterName The name of the transform parameter to remove. @returns True if a parameter with that name was found and removed, otherwise false.
- L423 _public prototype_ `TArray<FScalarParameterNameAndCurve>& GetScalarParameterNamesAndCurves();` — Gets the animated scalar parameters and their associated curves.
- L424 _public prototype_ `const TArray<FScalarParameterNameAndCurve>& GetScalarParameterNamesAndCurves() const;`
- L427 _public prototype_ `TArray<FBoolParameterNameAndCurve>& GetBoolParameterNamesAndCurves();` — Gets the animated bool parameters and their associated curves.
- L428 _public prototype_ `const TArray<FBoolParameterNameAndCurve>& GetBoolParameterNamesAndCurves() const;`
- L431 _public prototype_ `TArray<FVector2DParameterNameAndCurves>& GetVector2DParameterNamesAndCurves();` — Gets the animated vector2D parameters and their associated curves.
- L432 _public prototype_ `const TArray<FVector2DParameterNameAndCurves>& GetVector2DParameterNamesAndCurves() const;`
- L435 _public prototype_ `TArray<FVectorParameterNameAndCurves>& GetVectorParameterNamesAndCurves();` — Gets the animated vector parameters and their associated curves.
- L436 _public prototype_ `const TArray<FVectorParameterNameAndCurves>& GetVectorParameterNamesAndCurves() const;`
- L439 _public prototype_ `TArray<FColorParameterNameAndCurves>& GetColorParameterNamesAndCurves();` — Gets the animated color parameters and their associated curves.
- L440 _public prototype_ `const TArray<FColorParameterNameAndCurves>& GetColorParameterNamesAndCurves() const;`
- L443 _public prototype_ `TArray<FTransformParameterNameAndCurves>& GetTransformParameterNamesAndCurves();` — Gets the animated transform parameters and their associated curves.
- L444 _public prototype_ `const TArray<FTransformParameterNameAndCurves>& GetTransformParameterNamesAndCurves() const;`
- L448 _public prototype_ `void GetParameterNames(TSet<FName>& ParameterNames) const;` — `UFUNCTION(BlueprintPure, Category = "Sequencer|Section")` — Gets the set of all parameter names used by this section.
- L450 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L451 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L453 _public prototype_ `void ExternalPopulateEvaluationField(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder);`
- L458 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L459 _protected prototype_ `virtual void PostEditImport() override;`
- L460 _protected prototype_ `virtual void ReconstructChannelProxy();`
- L465 _protected member_ `TArray<FBoolParameterNameAndCurve> BoolParameterNamesAndCurves;` — `UPROPERTY()` — The bool parameter names and their associated curves.
- L469 _protected member_ `TArray<FScalarParameterNameAndCurve> ScalarParameterNamesAndCurves;` — `UPROPERTY()` — The scalar parameter names and their associated curves.
- L473 _protected member_ `TArray<FVector2DParameterNameAndCurves> Vector2DParameterNamesAndCurves;` — `UPROPERTY()` — The vector3D parameter names and their associated curves.
- L477 _protected member_ `TArray<FVectorParameterNameAndCurves> VectorParameterNamesAndCurves;` — `UPROPERTY()` — The vector parameter names and their associated curves.
- L481 _protected member_ `TArray<FColorParameterNameAndCurves> ColorParameterNamesAndCurves;` — `UPROPERTY()` — The color parameter names and their associated curves.
- L485 _protected member_ `TArray<FTransformParameterNameAndCurves> TransformParameterNamesAndCurves;` — `UPROPERTY()` — The transform  parameter names and their associated curves.

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneParticleSection.h` (Public)


#### enum `EParticleKey`  
`enum class EParticleKey : uint8`  
_L28-33_
- reflection: `UENUM(BlueprintType)`
- desc: Defines the types of particle keys.
- L30 _public enumerator_ `Activate = 0`
- L31 _public enumerator_ `Deactivate = 1`
- L32 _public enumerator_ `Trigger = 2`

#### struct `FMovieSceneParticleChannel`  
`struct FMovieSceneParticleChannel : public FMovieSceneByteChannel`  
_L36-41_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneByteChannel`
- L40 _public prototype_ `FMovieSceneParticleChannel();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneParticleChannel> : public TStructOpsTypeTraitsBase2<FMovieSceneParticleChannel>`  
_L44-47_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneParticleChannel>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L46-46_

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneParticleChannel> : TMovieSceneChannelTraitsBase<FMovieSceneParticleChannel>`  
_L51-61_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneParticleChannel>`
- L58 _public typedef_ `typedef TMovieSceneExternalValue<uint8> ExtendedEditorDataType;` — Byte channels can have external values (ie, they can get their values from external objects for UI purposes)

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L53-53_

#### class `UMovieSceneParticleSection`  
`class UMovieSceneParticleSection : public UMovieSceneSection`  
_L67-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Particle section, for particle toggling and triggering.
- L76 _public member_ `FMovieSceneParticleChannel ParticleKeys;` — `UPROPERTY()` — Curve containing the particle keys.

#### Free symbols / members of external scopes

- L46 _enumerator_ `enum { WithStructuredSerializeFromMismatchedTag = true };` (scope `TStructOpsTypeTraits::__anon035139400103`)
- L53 _enumerator_ `enum { SupportsDefaults = false }; #if WITH_EDITOR typedef TMovieSceneExternalValue<uint8> ExtendedEditorDataType; #endif` (scope `TMovieSceneChannelTraits::__anon035139400203`)
- L80 _function_ `inline void AssignValue(FMovieSceneParticleChannel* InChannel, FKeyHandle InKeyHandle, EParticleKey InValue)`
- L91 _function_ `inline bool EvaluateChannel(const FMovieSceneParticleChannel* InChannel, FFrameTime InTime, EParticleKey& OutValue)`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieScenePrimitiveMaterialSection.h` (Public)


#### class `UMovieScenePrimitiveMaterialSection`  
`class UMovieScenePrimitiveMaterialSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L11-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L19 _public prototype_ `UMovieScenePrimitiveMaterialSection(const FObjectInitializer& ObjInit);`
- L21 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L22 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* Linker, const FEntityImportParams& ImportParams, FImportedEntity* OutImportedEntity) override;`
- L25 _public member_ `FMovieSceneObjectPathChannel MaterialChannel;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneRotatorSection.h` (Public)


#### class `UMovieSceneRotatorSection`  
`class UMovieSceneRotatorSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L12-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: Movie scene section that animates each component (X, Y, Z) of an FRotator property
- L19 _public member_ `static constexpr int32 RollChannelIndex = 2;`
- L20 _public member_ `static constexpr int32 PitchChannelIndex = 0;`
- L21 _public member_ `static constexpr int32 YawChannelIndex = 1;`
- L23 _public prototype_ `UMovieSceneRotatorSection(const FObjectInitializer& InObjectInitializer);`
- L26 _public function_ `const FMovieSceneDoubleChannel& GetChannelX() const` — Get the Roll channel
- L32 _public function_ `const FMovieSceneDoubleChannel& GetChannelY() const` — Get the Pitch channel
- L38 _public function_ `const FMovieSceneDoubleChannel& GetChannelZ() const` — Get the Yaw channel
- L43 _public function_ `const FMovieSceneDoubleChannel& GetChannel(int32 InIndex) const`
- L51 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& InEffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L52 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* InEntityLinker, const FEntityImportParams& InParams, FImportedEntity* OutImportedEntity) override;`
- L57 _private member_ `FMovieSceneDoubleChannel Rotation[3];` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneSkeletalAnimationSection.h` (Public)


#### struct `FMovieSceneSkeletalAnimationParams`  
`struct FMovieSceneSkeletalAnimationParams`  
_L20-105_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public prototype_ `FMovieSceneSkeletalAnimationParams();`
- L28 _public function_ `float GetDuration() const` — `UE_DEPRECATED(5.5, "Animation lengh no longer has a single, consistent length if there is timewarp.")` — Gets the animation duration, modified by play rate
- L31 _public function_ `float GetSequenceLength() const` — Gets the animation sequence length, not modified by play rate
- L37 _public prototype_ `double MapTimeToAnimation(const UMovieSceneSection* InSection, FFrameTime InPosition, FFrameRate InTickResolution, UAnimSequenceBase* OverrideSequence = nullptr) const;` — Convert a sequence frame to a time in seconds inside the animation clip, taking into account start/end offsets, looping, etc.
- L42 _public prototype_ `double MapTimeToAnimation(FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime, FFrameTime InPosition, FFrameRate InTickResolution, UAnimSequenceBase* OverrideSequence = nullptr) const;` — As above, but with already computed section bounds.
- L47 _public prototype_ `FMovieSceneSequenceTransform MakeTransform(const FFrameRate& OuterFrameRate, const TRange<FFrameNumber>& OuterRange, UAnimSequenceBase* OverrideSequence = nullptr, bool bClampToOuterRange = true, bool bForceLoop = false) const;` — Make a transform structure from these animation parameters
- L51 _public member_ `TObjectPtr<UAnimSequenceBase> Animation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation", meta=(AllowedClasses = "/Script/Engine.AnimSequence,/Script/Engine.AnimComposite,/Script/Engine.AnimStreamable"))` — The animation this section plays
- L55 _public member_ `FFrameNumber FirstLoopStartFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation|Offset")` — The offset into the beginning of the animation clip for the first loop of play.
- L59 _public member_ `FFrameNumber StartFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation|Offset")` — The offset into the beginning of the animation clip
- L63 _public member_ `FFrameNumber EndFrameOffset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation|Offset")` — The offset into the end of the animation clip
- L67 _public member_ `FMovieSceneTimeWarpVariant PlayRate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation|Playback")` — The playback rate of the animation clip
- L71 _public member_ `uint32 bReverse:1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Animation|Playback")` — Reverse the playback of the animation clip
- L75 _public member_ `FName SlotName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")` — The slot name to use for the animation
- L78 _public member_ `TObjectPtr<class UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")`
- L82 _public member_ `FMovieSceneFloatChannel Weight;` — `UPROPERTY()` — The weight curve for this animation section
- L86 _public member_ `bool bSkipAnimNotifiers;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")` — If on will skip sending animation notifies
- L90 _public member_ `bool bForceCustomMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")` — If on animation sequence will always play when active even if the animation is controlled by a Blueprint or Anim Instance Class
- L94 _public member_ `ESwapRootBone SwapRootBone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")` — If on the root bone transform will be swapped to the specified root
- L97 _public member_ `bool bLinearPlaybackWhenScaled;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation|Playback")`
- L100 _public member_ `float StartOffset_DEPRECATED;` — `UPROPERTY()`
- L103 _public member_ `float EndOffset_DEPRECATED;` — `UPROPERTY()`

#### class `UMovieSceneSkeletalAnimationSection`  
`class UMovieSceneSkeletalAnimationSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L111-302_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: Movie scene section that control skeletal animation
- L120 _public member_ `FMovieSceneSkeletalAnimationParams Params;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation", meta=(ShowOnlyInnerProperties))`
- L123 _public prototype_ `double MapTimeToAnimation(FFrameTime InPosition, FFrameRate InTickResolution) const;` — Get Frame Time as Animation Time
- L125 _public prototype_ `UAnimSequenceBase* GetAnimation() const;`
- L126 _public prototype_ `UAnimSequenceBase* GetPlaybackAnimation() const;`
- L129 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L130 _public prototype_ `virtual void SetRange(const TRange<FFrameNumber>& NewRange) override;`
- L131 _public prototype_ `virtual void SetStartFrame(TRangeBound<FFrameNumber> NewStartFrame) override;`
- L132 _public prototype_ `virtual void SetEndFrame(TRangeBound<FFrameNumber> NewEndFrame)override;`
- L133 _public prototype_ `virtual FMovieSceneTimeWarpVariant* GetTimeWarp() override;`
- L134 _public prototype_ `virtual UObject* GetSourceObject() const override;`
- L136 _public prototype_ `void DeleteChannels(TArrayView<const FName> ChannelNames);`
- L147 _protected prototype_ `virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;`
- L148 _protected prototype_ `virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;`
- L149 _protected prototype_ `virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;`
- L150 _protected prototype_ `virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;`
- L151 _protected prototype_ `virtual TOptional<FFrameTime> GetOffsetTime() const override;`
- L152 _protected prototype_ `virtual void MigrateFrameTimes(FFrameRate SourceRate, FFrameRate DestinationRate) override;`
- L153 _protected prototype_ `virtual float GetTotalWeightValue(FFrameTime InTime) const override;`
- L156 _protected prototype_ `virtual void PostLoad() override;` — ~UObject interface
- L157 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L160 _protected prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& InParams, FImportedEntity* OutImportedEntity) override;` — ~IMovieSceneEntityProvider interface
- L161 _protected prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L168 _private prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L169 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L172 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L173 _public member_ `float PreviousPlayRate;`
- L175 _private prototype_ `virtual void PostEditImport() override;`
- L176 _private prototype_ `virtual void PostEditUndo() override;`
- L183 _private member_ `TObjectPtr<class UAnimSequence> AnimSequence_DEPRECATED;` — `UPROPERTY()`
- L186 _private member_ `TObjectPtr<UAnimSequenceBase> Animation_DEPRECATED;` — `UPROPERTY()`
- L189 _private member_ `float StartOffset_DEPRECATED;` — `UPROPERTY()`
- L192 _private member_ `float EndOffset_DEPRECATED;` — `UPROPERTY()`
- L195 _private member_ `float PlayRate_DEPRECATED;` — `UPROPERTY()`
- L198 _private member_ `uint32 bReverse_DEPRECATED:1;` — `UPROPERTY()`
- L201 _private member_ `FName SlotName_DEPRECATED;` — `UPROPERTY()`
- L206 _public member_ `FVector StartLocationOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root Motions")` — Location offset applied before the matched offset
- L211 _public member_ `FRotator StartRotationOffset;`
- L214 _public member_ `FName MatchedBoneName;` — `UPROPERTY()`
- L218 _public member_ `FVector MatchedLocationOffset;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root Motions")` — Location offset determined by matching
- L222 _public member_ `FRotator MatchedRotationOffset;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root Motions")` — Rotation offset determined by matching
- L225 _public member_ `uint8 bMatchWithPrevious : 1;` — `UPROPERTY()`
- L228 _public member_ `uint8 bMatchTranslation : 1;` — `UPROPERTY()`
- L231 _public member_ `uint8 bMatchIncludeZHeight : 1;` — `UPROPERTY()`
- L234 _public member_ `uint8 bMatchRotationYaw : 1;` — `UPROPERTY()`
- L237 _public member_ `uint8 bMatchRotationPitch : 1;` — `UPROPERTY()`
- L240 _public member_ `uint8 bMatchRotationRoll : 1;` — `UPROPERTY()`
- L243 _public member_ `uint8 bDebugForceTickPose : 1;` — `UPROPERTY()`
- L248 _public member_ `uint8 bShowSkeleton : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Root Motions")` — Whether to show the underlying skeleton for this section.
- L252 _public member_ `FTransform PreviousTransform;` — Previous transform used to specify the global OffsetTransform while calculting the root motions.
- L255 _public member_ `TOptional<int32> TempRootBoneIndex;` — Temporary index used by GetRootMotionTransform and set by SetBoneIndexforRootMotionCalculations
- L271 _public prototype_ `FMovieSceneSkeletalAnimRootMotionTrackParams* GetRootMotionParams() const;` — Functions/params related to root motion calcuations.
- L273 _public prototype_ `bool GetRootMotionVelocity(FFrameTime PreviousTime, FFrameTime CurrentTime, FFrameRate InTickResolution, FTransform& OutVelocity, float& OutWeight) const;`
- L274 _public prototype_ `int32 SetBoneIndexForRootMotionCalculations(bool bBlendFirstChildOfRoot);`
- L275 _public prototype_ `bool GetRootMotionTransform(FAnimationPoseData& PoseData, FRootMotionTransformParam& InOutParams) const;`
- L276 _public prototype_ `void MatchSectionByBoneTransform(USkeletalMeshComponent* SkelMeshComp, FFrameTime CurrentFrame, FFrameRate InTickResolution, const FName& BoneName);`
- L279 _public prototype_ `void ClearMatchedOffsetTransforms();`
- L281 _public prototype_ `void GetRootMotion(FFrameTime CurrentTime, FRootMotionParams& OutRootMotionParams) const;`
- L283 _public prototype_ `void ToggleMatchTranslation();`
- L285 _public prototype_ `void ToggleMatchIncludeZHeight();`
- L287 _public prototype_ `void ToggleMatchIncludeYawRotation();`
- L289 _public prototype_ `void ToggleMatchIncludePitchRotation();`
- L291 _public prototype_ `void ToggleMatchIncludeRollRotation();`
- L294 _public prototype_ `void ToggleShowSkeleton();`
- L297 _public prototype_ `FTransform GetRootMotionStartOffset() const;`
- L300 _private prototype_ `void MultiplyOutInverseOnNextClips(FVector PreviousMatchedLocationOffset, FRotator PreviousMatchedRotationOffset);`

#### struct `UMovieSceneSkeletalAnimationSection::FRootMotionParams`  
`struct FRootMotionParams`  
_L138-144_
- L140 _public member_ `bool bBlendFirstChildOfRoot;`
- L141 _public member_ `int32 ChildBoneIndex;`
- L142 _public member_ `TOptional<FTransform> Transform;`
- L143 _public member_ `TOptional<FTransform> PreviousTransform;`

#### struct `UMovieSceneSkeletalAnimationSection::FRootMotionTransformParam`  
`struct FRootMotionTransformParam`  
_L258-268_
- L260 _public member_ `FFrameTime CurrentTime;` — current time
- L261 _public member_ `FFrameRate FrameRate;` — scene frame rate
- L262 _public member_ `bool bOutIsAdditive;` — if this is additive or not
- L263 _public member_ `FTransform OutTransform;` — total transform including current pose plus offset
- L264 _public member_ `FTransform OutParentTransform;` — offset transform not including original bone transform
- L265 _public member_ `FTransform OutPoseTransform;` — original bone transform
- L266 _public member_ `FTransform OutRootStartTransform;` — start of the root
- L267 _public member_ `float OutWeight;` — weight at specified time

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneSlomoSection.h` (Public)


#### class `UMovieSceneSlomoSection`  
`class UMovieSceneSlomoSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L22-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single floating point section.
- L29 _private prototype_ `UMovieSceneSlomoSection();` — Default constructor.
- L32 _private prototype_ `void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L38 _public member_ `FMovieSceneFloatChannel FloatCurve;` — `UPROPERTY()` — Float data

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneStringSection.h` (Public)


#### class `UMovieSceneStringSection`  
`class UMovieSceneStringSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L20-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A single string section
- L31 _public function_ `const FMovieSceneStringChannel& GetChannel() const` — Public access to this section's internal data function
- L34 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L35 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L41 _private member_ `FMovieSceneStringChannel StringCurve;` — `UPROPERTY()` — Curve data

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneTextSection.h` (Public)


#### class `UMovieSceneTextSection`  
`class UMovieSceneTextSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L11-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- L18 _public prototype_ `UMovieSceneTextSection(const FObjectInitializer& InObjectInitializer);`
- L21 _public function_ `const FMovieSceneTextChannel& GetChannel() const` — Public access to this section's internal data function
- L27 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L28 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L33 _private member_ `FMovieSceneTextChannel TextChannel;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneVectorSection.h` (Public)


#### struct `FMovieSceneFloatVectorKeyStructBase`  
`struct FMovieSceneFloatVectorKeyStructBase : public FMovieSceneKeyStruct`  
_L23-38_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Base Proxy structure for float vector section key data.
- L30 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L32 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L34 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`
- L37 _public prototype_ `virtual float* GetPropertyChannelByIndex(int32 Index) PURE_VIRTUAL(FMovieSceneFloatVectorKeyStructBase::GetPropertyChannelByIndex, return nullptr; );` — Gets a ptr value of a channel by index, 0-3 = x-w

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneFloatVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneFloatVectorKeyStructBase>`  
_L39-39_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneFloatVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneFloatVectorKeyStructBase>`  
_L39-39_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneFloatVectorKeyStructBase>`

#### struct `FMovieSceneVector2fKeyStruct`  
`struct FMovieSceneVector2fKeyStruct : public FMovieSceneFloatVectorKeyStructBase`  
_L46-57_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneFloatVectorKeyStructBase`
- desc: Proxy structure for 2f vector section key data.
- L53 _public member_ `FVector2f Vector = FVector2f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Key)` — They key's vector value.
- L56 _public function_ `virtual float* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector2fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2fKeyStruct>`  
_L58-58_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector2fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2fKeyStruct>`  
_L58-58_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector2fKeyStruct>`

#### struct `FMovieSceneVector3fKeyStruct`  
`struct FMovieSceneVector3fKeyStruct : public FMovieSceneFloatVectorKeyStructBase`  
_L64-75_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneFloatVectorKeyStructBase`
- desc: Proxy structure for float vector section key data.
- L71 _public member_ `FVector3f Vector = FVector3f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Key)` — They key's vector value.
- L74 _public function_ `virtual float* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector3fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3fKeyStruct>`  
_L76-76_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector3fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3fKeyStruct>`  
_L76-76_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector3fKeyStruct>`

#### struct `FMovieSceneVector4fKeyStruct`  
`struct FMovieSceneVector4fKeyStruct : public FMovieSceneFloatVectorKeyStructBase`  
_L82-93_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneFloatVectorKeyStructBase`
- desc: Proxy structure for vector4f section key data.
- L89 _public member_ `FVector4f Vector = FVector4f(FVector3f::ZeroVector);` — `UPROPERTY(EditAnywhere, Category = Key)` — They key's vector value.
- L92 _public function_ `virtual float* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector4fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4fKeyStruct>`  
_L94-94_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector4fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4fKeyStruct>`  
_L94-94_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector4fKeyStruct>`

#### struct `FMovieSceneDoubleVectorKeyStructBase`  
`struct FMovieSceneDoubleVectorKeyStructBase : public FMovieSceneKeyStruct`  
_L101-116_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneKeyStruct`
- desc: Base Proxy structure for double vector section key data.
- L108 _public member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category=Key)` — The key's time.
- L110 _public member_ `FMovieSceneKeyStructHelper KeyStructInterop;`
- L112 _public prototype_ `virtual void PropagateChanges(const FPropertyChangedEvent& ChangeEvent) override;`
- L115 _public prototype_ `virtual double* GetPropertyChannelByIndex(int32 Index) PURE_VIRTUAL(FMovieSceneDoubleVectorKeyStructBase::GetPropertyChannelByIndex, return nullptr; );` — Gets a ptr value of a channel by index, 0-3 = x-w

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneDoubleVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneDoubleVectorKeyStructBase>`  
_L117-117_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneDoubleVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneDoubleVectorKeyStructBase>`  
_L117-117_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneDoubleVectorKeyStructBase>`

#### struct `FMovieSceneVector2DKeyStruct`  
`struct FMovieSceneVector2DKeyStruct : public FMovieSceneDoubleVectorKeyStructBase`  
_L123-134_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneDoubleVectorKeyStructBase`
- desc: Proxy structure for 2D vector section key data.
- L130 _public member_ `FVector2D Vector = FVector2D::ZeroVector;` — `UPROPERTY(EditAnywhere, Category=Key)` — They key's vector value.
- L133 _public function_ `virtual double* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector2DKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2DKeyStruct>`  
_L135-135_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector2DKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2DKeyStruct>`  
_L135-135_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector2DKeyStruct>`

#### struct `FMovieSceneVector3dKeyStruct`  
`struct FMovieSceneVector3dKeyStruct : public FMovieSceneDoubleVectorKeyStructBase`  
_L141-152_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneDoubleVectorKeyStructBase`
- desc: Proxy structure for double vector section key data.
- L148 _public member_ `FVector3d Vector = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Key)` — They key's vector value.
- L151 _public function_ `virtual double* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector3dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3dKeyStruct>`  
_L153-153_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector3dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3dKeyStruct>`  
_L153-153_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector3dKeyStruct>`

#### struct `FMovieSceneVector4dKeyStruct`  
`struct FMovieSceneVector4dKeyStruct : public FMovieSceneDoubleVectorKeyStructBase`  
_L160-171_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneDoubleVectorKeyStructBase`
- desc: Proxy structure for double vector section key data.
- L167 _public member_ `FVector4d Vector = FVector4d(FVector3d::ZeroVector);` — `UPROPERTY(EditAnywhere, Category = Key)` — They key's vector value.
- L170 _public function_ `virtual double* GetPropertyChannelByIndex(int32 Index) override`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector4dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4dKeyStruct>`  
_L172-172_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneVector4dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4dKeyStruct>`  
_L172-172_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneVector4dKeyStruct>`

#### class `UMovieSceneFloatVectorSection`  
`class UMovieSceneFloatVectorSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L179-231_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A float vector section.
- L188 _public function_ `void SetChannelsUsed(int32 InChannelsUsed)` — Sets how many channels are to be used
- L196 _public function_ `int32 GetChannelsUsed() const` — Gets the number of channels in use
- L201 _public function_ `const FMovieSceneFloatChannel& GetChannel(int32 Index) const` — Public access to this section's internal data function
- L210 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L211 _protected prototype_ `virtual void PostEditImport() override;`
- L212 _protected prototype_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles) override;`
- L214 _protected prototype_ `void RecreateChannelProxy();`
- L219 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L220 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L226 _private member_ `FMovieSceneFloatChannel Curves[4];` — `UPROPERTY()` — Float functions for the X,Y,Z,W components of the vector
- L230 _private member_ `int32 ChannelsUsed;` — `UPROPERTY()` — How many curves are actually used

#### class `UMovieSceneDoubleVectorSection`  
`class UMovieSceneDoubleVectorSection : public UMovieSceneSection , public IMovieSceneEntityProvider`  
_L238-290_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider`
- desc: A double vector section.
- L247 _public function_ `void SetChannelsUsed(int32 InChannelsUsed)` — Sets how many channels are to be used
- L255 _public function_ `int32 GetChannelsUsed() const` — Gets the number of channels in use
- L260 _public function_ `const FMovieSceneDoubleChannel& GetChannel(int32 Index) const` — Public access to this section's internal data function
- L269 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L270 _protected prototype_ `virtual void PostEditImport() override;`
- L271 _protected prototype_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct(TArrayView<const FKeyHandle> KeyHandles) override;`
- L273 _protected prototype_ `void RecreateChannelProxy();`
- L278 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L279 _private prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L285 _private member_ `FMovieSceneDoubleChannel Curves[4];` — `UPROPERTY()` — Double functions for the X,Y,Z,W components of the vector
- L289 _private member_ `int32 ChannelsUsed;` — `UPROPERTY()` — How many curves are actually used

#### Free symbols / members of external scopes

- L39 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneFloatVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneFloatVectorKeyStructBase> { enum { WithCopy = false, WithPureVirtual = true, }; }; /** * Proxy structure for 2f vector section key data. */ USTRUCT() struct FMovieSceneVector2fKeyStruct` (scope `TStructOpsTypeTraits::__anon127e21bf0103`)
- L39 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneFloatVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneFloatVectorKeyStructBase> { enum { WithCopy = false, WithPureVirtual = true, }; }; /** * Proxy structure for 2f vector section key data. */ USTRUCT() struct FMovieSceneVector2fKeyStruct` (scope `TStructOpsTypeTraits::__anon127e21bf0103`)
- L58 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector2fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2fKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for float vector section key data. */ USTRUCT() struct FMovieSceneVector3fKeyStruct : public FMovieSceneFloatVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0203`)
- L76 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector3fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3fKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for vector4f section key data. */ USTRUCT() struct FMovieSceneVector4fKeyStruct : public FMovieSceneFloatVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0303`)
- L94 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector4fKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4fKeyStruct> { enum { WithCopy = false }; }; /** * Base Proxy structure for double vector section key data. */ USTRUCT() struct FMovieSceneDoubleVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0403`)
- L117 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneDoubleVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneDoubleVectorKeyStructBase> { enum { WithCopy = false, WithPureVirtual = true, }; }; /** * Proxy structure for 2D vector section key data. */ USTRUCT() struct FMovieSceneVector2DKeyStruct : public FMovieSceneDoubleVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0503`)
- L117 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneDoubleVectorKeyStructBase> : public TStructOpsTypeTraitsBase2<FMovieSceneDoubleVectorKeyStructBase> { enum { WithCopy = false, WithPureVirtual = true, }; }; /** * Proxy structure for 2D vector section key data. */ USTRUCT() struct FMovieSceneVector2DKeyStruct : public FMovieSceneDoubleVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0503`)
- L135 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector2DKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector2DKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for double vector section key data. */ USTRUCT() struct FMovieSceneVector3dKeyStruct : public FMovieSceneDoubleVectorKeyStructBase` (scope `TStructOpsTypeTraits::__anon127e21bf0603`)
- L153 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector3dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector3dKeyStruct> { enum { WithCopy = false }; }; /** * Proxy structure for double vector section key data. */ USTRUCT() struct FMovieSceneVector4dKeyStruct` (scope `TStructOpsTypeTraits::__anon127e21bf0703`)
- L172 _enumerator_ `template<> struct TStructOpsTypeTraits<FMovieSceneVector4dKeyStruct> : public TStructOpsTypeTraitsBase2<FMovieSceneVector4dKeyStruct> { enum { WithCopy = false }; }; /** * A float vector section. */ UCLASS(MinimalAPI) class UMovieSceneFloatVectorSection` (scope `TStructOpsTypeTraits::__anon127e21bf0803`)

### `Source/Runtime/MovieSceneTracks/Public/Sections/MovieSceneVisibilitySection.h` (Public)


#### class `UMovieSceneVisibilitySection`  
`class UMovieSceneVisibilitySection : public UMovieSceneBoolSection , public IMovieSceneEntityProvider`  
_L17-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBoolSection,IMovieSceneEntityProvider`
- desc: A spawn section.
- L25 _public prototype_ `UMovieSceneVisibilitySection(const FObjectInitializer& Init);`
- L30 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityProvider interface
- L31 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/ActorReferenceChannelEvaluatorSystem.h` (Public)


#### class `UActorReferenceChannelEvaluatorSystem`  
`class UActorReferenceChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L13-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating actor reference channels.
- L19 _public prototype_ `UActorReferenceChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L21 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L22 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/BoolChannelEvaluatorSystem.h` (Public)


#### class `UBoolChannelEvaluatorSystem`  
`class UBoolChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating bool channels.
- L23 _public prototype_ `UBoolChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L25 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L26 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/ByteChannelEvaluatorSystem.h` (Public)


#### class `UByteChannelEvaluatorSystem`  
`class UByteChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating byte channels.
- L23 _public prototype_ `UByteChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L25 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L26 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/DoubleChannelEvaluatorSystem.h` (Public)


#### class `UDoubleChannelEvaluatorSystem`  
`class UDoubleChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L33-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating double channels.
- L40 _public prototype_ `UDoubleChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L42 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L43 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L44 _public prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L46 _public prototype_ `static void RegisterChannelType(TComponentTypeID<UE::MovieScene::FSourceDoubleChannel> SourceChannelType, TComponentTypeID<UE::MovieScene::Interpolation::FCachedInterpolation> CachedInterpolationType, TComponentTypeID<double> ResultType);`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)
- L23 _namespace_ `namespace Interpolation` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/DoublePerlinNoiseChannelEvaluatorSystem.h` (Public)


#### class `UDoublePerlinNoiseChannelEvaluatorSystem`  
`class UDoublePerlinNoiseChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L12-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating double perlin noise channels.
- L17 _public prototype_ `UDoublePerlinNoiseChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L18 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L19 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/FloatChannelEvaluatorSystem.h` (Public)


#### class `UFloatChannelEvaluatorSystem`  
`class UFloatChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L29-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating double channels.
- L36 _public prototype_ `UFloatChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L38 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L39 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L40 _public prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L42 _public prototype_ `static void RegisterChannelType(TComponentTypeID<UE::MovieScene::FSourceFloatChannel> SourceChannelType, TComponentTypeID<UE::MovieScene::Interpolation::FCachedInterpolation> CachedInterpolationType, TComponentTypeID<double> ResultType);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L19 _namespace_ `namespace Interpolation` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/FloatPerlinNoiseChannelEvaluatorSystem.h` (Public)


#### class `UFloatPerlinNoiseChannelEvaluatorSystem`  
`class UFloatPerlinNoiseChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L12-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating double perlin noise channels.
- L17 _public prototype_ `UFloatPerlinNoiseChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L19 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L20 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/IntegerChannelEvaluatorSystem.h` (Public)


#### class `UIntegerChannelEvaluatorSystem`  
`class UIntegerChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L15-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating integer channels.
- L21 _public prototype_ `UIntegerChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L23 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L24 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScene3DTransformPropertySystem.h` (Public)


#### class `UMovieScene3DTransformPropertySystem`  
`class UMovieScene3DTransformPropertySystem : public UMovieScenePropertySystem`  
_L10-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L16 _public prototype_ `UMovieScene3DTransformPropertySystem(const FObjectInitializer& ObjInit);`
- L18 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneActorReferencePropertySystem.h` (Public)


#### class `UMovieSceneActorReferencePropertySystem`  
`class UMovieSceneActorReferencePropertySystem : public UMovieScenePropertySystem`  
_L10-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L14 _private prototype_ `UMovieSceneActorReferencePropertySystem(const FObjectInitializer& ObjInit);`
- L16 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneBaseValueEvaluatorSystem.h` (Public)


#### class `UMovieSceneBaseValueEvaluatorSystem`  
`class UMovieSceneBaseValueEvaluatorSystem : public UMovieSceneEntitySystem`  
_L17-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating base values, for "additive from base" blending.
- L23 _public prototype_ `UMovieSceneBaseValueEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L25 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneBlenderSystemHelper.h` (Public)


#### struct `UE::MovieScene::TSimpleBlendResult`  
`template<typename PropertyType> struct TSimpleBlendResult`  
_L21-25_
- desc: Simple blended result where a value has been accumulated by a number of contributors.
- L23 _public member_ `PropertyType Value;`
- L24 _public member_ `uint32 NumContributors;`

#### struct `UE::MovieScene::TSimpleBlendResultTraits`  
`template<typename PropertyType> struct TSimpleBlendResultTraits`  
_L33-56_
- desc: Traits class for knowing how to deal with a simply blended property type. This is the default implementation which returns the average of all contributions.
- L36 _public function_ `static void ZeroAccumulationBuffer(TArrayView<TSimpleBlendResult<PropertyType>> Buffer)` — Reset accumulated values to their default
- L45 _public function_ `static void AccumulateResult(TSimpleBlendResult<PropertyType>& InOutValue, typename TCallTraits<PropertyType>::ParamType Contributor)` — Accumulate a value on top of already accumulated values
- L52 _public function_ `static PropertyType BlendResult(const TSimpleBlendResult<PropertyType>& InResult)` — Get the final blended value

#### struct `UE::MovieScene::TSimpleBlenderGatherResults`  
`template<typename PropertyType, typename ResultTraits = TSimpleBlendResultTraits<PropertyType>> struct TSimpleBlenderGatherResults`  
_L59-77_
- L61 _public member_ `FMovieSceneBlenderSystemID SystemID;`
- L62 _public member_ `TArray<TSimpleBlendResult<PropertyType>>& BlendChannelResults;`
- L64 _public function_ `TSimpleBlenderGatherResults(FMovieSceneBlenderSystemID InSystemID, TArray<TSimpleBlendResult<PropertyType>>& InBlendChannelResults) : SystemID(InSystemID) , BlendChannelResults(InBlendChannelResults)`
- L69 _public function_ `void ForEachEntity(FMovieSceneBlendChannelID BlendChannelInput, PropertyType Value) const`

#### struct `UE::MovieScene::TSimpleBlenderCombineResults`  
`template<typename PropertyType, typename ResultTraits = TSimpleBlendResultTraits<PropertyType>> struct TSimpleBlenderCombineResults`  
_L80-98_
- L82 _public member_ `FMovieSceneBlenderSystemID SystemID;`
- L83 _public member_ `TArray<TSimpleBlendResult<PropertyType>>& BlendChannelResults;`
- L85 _public function_ `TSimpleBlenderCombineResults(FMovieSceneBlenderSystemID InSystemID, TArray<TSimpleBlendResult<PropertyType>>& InBlendChannelResults) : SystemID(InSystemID) , BlendChannelResults(InBlendChannelResults)`
- L90 _public function_ `void ForEachEntity(FMovieSceneBlendChannelID BlendChannelOutput, PropertyType& OutValue) const`

#### class `UE::MovieScene::TSimpleBlenderSystemImpl`  
`template<typename PropertyType, typename ResultTraits = TSimpleBlendResultTraits<PropertyType>> class TSimpleBlenderSystemImpl`  
_L107-262_
- desc: A helper class for simple blender systems. This class implements a simple blender system that accumulates all contributors to a blend channel, and returns the blended value, as defined by the value type's traits class (above).
- L111 _public typedef_ `using FGatherResults = TSimpleBlenderGatherResults<PropertyType, ResultTraits>;`
- L112 _public typedef_ `using FCombineResults = TSimpleBlenderCombineResults<PropertyType, ResultTraits>;`
- L114 _public function_ `TSimpleBlenderSystemImpl() : BlenderSystem(nullptr)`
- L125 _public function_ `void Setup(UMovieSceneBlenderSystem* InBlenderSystem, TComponentTypeID<PropertyType> InResultComponentID, UClass* ChannelEvaluatorSystem = nullptr)` — Sets up this helper class. To be called in the owning blender system's constructor. @param InBlenderSystem       The owning blender system @param InResultComponentID   The component type for the values to blend @param ChannelEvaluationSystem  The evaluation system for the value to blend. If set, the owner blender system will be automatically made a downstream dependency of it (optional)
- L136 _public function_ `void Schedule(UMovieSceneEntitySystemLinker* Linker, TBitArray<>& AllocatedBlendChannels, IEntitySystemScheduler* TaskScheduler)`
- L191 _public function_ `void Run(UMovieSceneEntitySystemLinker* Linker, TBitArray<>& AllocatedBlendChannels, FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents)` — Runs the blender system
- L249 _public function_ `void ZeroAccumulationBuffers()`
- L256 _private member_ `UMovieSceneBlenderSystem* BlenderSystem;`
- L257 _private member_ `TComponentTypeID<PropertyType> ResultComponentID;`
- L259 _private member_ `FCachedEntityManagerState ChannelRelevancyCache;`
- L261 _private member_ `TArray<TSimpleBlendResult<PropertyType>> BlendChannelResults;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieScene` (scope `UE`)
- L219 _typedef_ `using FResultTraits = TSimpleBlendResultTraits<PropertyType>;` (scope `UE::MovieScene::TSimpleBlenderSystemImpl::Run`)
- L251 _typedef_ `using FResultTraits = TSimpleBlendResultTraits<PropertyType>;` (scope `UE::MovieScene::TSimpleBlenderSystemImpl::ZeroAccumulationBuffers`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneBoolPropertySystem.h` (Public)


#### class `UMovieSceneBoolPropertySystem`  
`class UMovieSceneBoolPropertySystem : public UMovieScenePropertySystem`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneBoolPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneBytePropertySystem.h` (Public)


#### class `UMovieSceneBytePropertySystem`  
`class UMovieSceneBytePropertySystem : public UMovieScenePropertySystem`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L13 _private prototype_ `UMovieSceneBytePropertySystem(const FObjectInitializer& ObjInit);`
- L15 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneCameraShakeSystem.h` (Public)


#### struct `UE::MovieScene::FCameraShakePreviewerLinkerExtension`  
`struct FCameraShakePreviewerLinkerExtension : public TSharedEntitySystemLinkerExtension<FCameraShakePreviewerLinkerExtension>`  
_L26-53_
- inherits: `TSharedEntitySystemLinkerExtension<FCameraShakePreviewerLinkerExtension>`
- desc: Linker extension for storing camera shake previewers shared between the instantiator and the evaluation systems below. This extension is held by a shared pointer, so it should unregister and delete itself when both systems are unlinked.
- L29 _public prototype_ `static TEntitySystemLinkerExtensionID<FCameraShakePreviewerLinkerExtension> GetExtensionID();` — The ID of this extension
- L32 _public prototype_ `static TSharedPtr<FCameraShakePreviewerLinkerExtension> GetOrCreateExtension(UMovieSceneEntitySystemLinker* Linker);` — Get the extension from the given linker, or create a new one
- L35 _public prototype_ `FCameraShakePreviewerLinkerExtension(UMovieSceneEntitySystemLinker* Linker);` — Constructor
- L37 _public prototype_ `virtual ~FCameraShakePreviewerLinkerExtension();` — Destructor
- L40 _public prototype_ `TSharedPtr<FCameraShakePreviewer> FindPreviewer(FInstanceHandle InstanceHandle);` — Find the previewer for the given sequence instance, if it has already been created
- L42 _public prototype_ `TSharedRef<FCameraShakePreviewer> GetPreviewer(FInstanceHandle InstanceHandle);` — Get or create the previewer for the given sequence instance
- L44 _public prototype_ `void UpdateAllPreviewers();` — Update all previewers by using the update context of each matching sequence instance
- L46 _public prototype_ `bool HasAnyShake() const;` — Whether there is any previewer with any shake
- L49 _private prototype_ `void OnLevelViewportClientListChanged();`
- L52 _private member_ `TMap<FInstanceHandle, TSharedRef<FCameraShakePreviewer>> Previewers;`

#### class `UMovieSceneCameraShakeInstantiatorSystem`  
`class UMovieSceneCameraShakeInstantiatorSystem : public UMovieSceneEntitySystem`  
_L63-103_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- desc: The instantiator system for camera shakes. This system will create and initialize camera shakes as they come in, and save pre-animated state.
- L68 _public prototype_ `UMovieSceneCameraShakeInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L70 _public prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L71 _public prototype_ `virtual void OnLink() override;`
- L72 _public prototype_ `virtual void OnUnlink() override;`
- L74 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L77 _public prototype_ `void AddShakeTrigger(UE::MovieScene::FInstanceHandle InInstance, const FGuid& ObjectBindingID, const FFrameTime& InTime, const FMovieSceneCameraShakeSourceTrigger& InTrigger);` — Add a fire-and-forget shake trigger
- L80 _private prototype_ `void TriggerOneShotShakes();`
- L83 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L94 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedCameraShakeStateStorage> PreAnimatedCameraShakeStorage;`
- L95 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedCameraComponentShakeStateStorage> PreAnimatedCameraComponentShakeStorage;`
- L96 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedCameraSourceShakeStateStorage> PreAnimatedCameraSourceShakeStorage;`
- L98 _private member_ `TMap<UE::MovieScene::FInstanceHandle, TArray<FTimedTrigger>> TriggersByInstance;`
- L101 _private member_ `TSharedPtr<UE::MovieScene::FCameraShakePreviewerLinkerExtension> PreviewerExtension;`

#### struct `UMovieSceneCameraShakeInstantiatorSystem::FTimedTrigger`  
`struct FTimedTrigger`  
_L87-92_
- L89 _public member_ `FGuid ObjectBindingID;`
- L90 _public member_ `FFrameTime Time;`
- L91 _public member_ `FMovieSceneCameraShakeSourceTrigger Trigger;`

#### class `UMovieSceneCameraShakeEvaluatorSystem`  
`class UMovieSceneCameraShakeEvaluatorSystem : public UMovieSceneEntitySystem`  
_L111-127_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- desc: The evaluator system for camera shakes. This system takes care of updating ongoing camera shakes according to the evaluation range.
- L116 _public prototype_ `UMovieSceneCameraShakeEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L118 _public prototype_ `virtual void OnLink() override;`
- L119 _public prototype_ `virtual void OnUnlink() override;`
- L120 _public prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L121 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L125 _private member_ `TSharedPtr<UE::MovieScene::FCameraShakePreviewerLinkerExtension> PreviewerExtension;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneColorPropertySystem.h` (Public)


#### class `UMovieSceneColorPropertySystem`  
`class UMovieSceneColorPropertySystem : public UMovieScenePropertySystem`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneColorPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneComponentAttachmentSystem.h` (Public)


#### struct `UE::MovieScene::FPreAnimAttachment`  
`struct FPreAnimAttachment`  
_L24-29_
- L26 _public member_ `TWeakObjectPtr<USceneComponent> OldAttachParent;`
- L27 _public member_ `FName OldAttachSocket;`
- L28 _public member_ `UE::MovieScene::FComponentDetachParams DetachParams;`

#### class `UMovieSceneComponentAttachmentInvalidatorSystem`  
`class UMovieSceneComponentAttachmentInvalidatorSystem : public UMovieSceneEntityInstantiatorSystem`  
_L36-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- L43 _public prototype_ `UMovieSceneComponentAttachmentInvalidatorSystem(const FObjectInitializer& ObjInit);`
- L47 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`

#### class `UMovieSceneComponentAttachmentSystem`  
`class UMovieSceneComponentAttachmentSystem : public UMovieSceneEntityInstantiatorSystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L51-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem,IMovieScenePreAnimatedStateSystemInterface`
- L59 _public prototype_ `UMovieSceneComponentAttachmentSystem(const FObjectInitializer& ObjInit);`
- L61 _public prototype_ `void AddPendingDetach(USceneComponent* SceneComponent, const UE::MovieScene::FPreAnimAttachment& Attachment);`
- L65 _private prototype_ `virtual void OnLink() override final;`
- L66 _private prototype_ `virtual void OnUnlink() override final;`
- L67 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L70 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L71 _private prototype_ `virtual void RestorePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L73 _private member_ `UE::MovieScene::TOverlappingEntityTracker<UE::MovieScene::FPreAnimAttachment, FObjectKey> AttachmentTracker;`
- L75 _private member_ `TArray<TTuple<USceneComponent*, UE::MovieScene::FPreAnimAttachment>> PendingAttachmentsToRestore;`
- L77 _private member_ `UE::MovieScene::FEntityGroupingPolicyKey GroupingKey;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneComponentMaterialSystem.h` (Public)


#### struct `UE::MovieScene::FComponentMaterialKey`  
`struct FComponentMaterialKey`  
_L19-32_
- L21 _public member_ `FObjectKey Object;`
- L22 _public member_ `FComponentMaterialInfo MaterialInfo;`

#### struct `UE::MovieScene::FComponentMaterialAccessor`  
`struct FComponentMaterialAccessor`  
_L34-50_
- L36 _public typedef_ `using KeyType = FComponentMaterialKey;`
- L38 _public member_ `UObject* Object;`
- L39 _public member_ `FComponentMaterialInfo MaterialInfo;`
- L41 _public prototype_ `FComponentMaterialAccessor(const FComponentMaterialKey& InKey);`
- L42 _public prototype_ `FComponentMaterialAccessor(UObject* InObject, const FComponentMaterialInfo& InMaterialInfo);`
- L44 _public prototype_ `explicit operator bool() const;`
- L46 _public prototype_ `UMaterialInterface* GetMaterial() const;`
- L47 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial) const;`
- L48 _public prototype_ `UMaterialInstanceDynamic* CreateDynamicMaterial(UMaterialInterface* InMaterial);`
- L49 _public prototype_ `FString ToString() const;`

#### struct `UE::MovieScene::FPreAnimatedComponentMaterialSwitcherStorage`  
`struct FPreAnimatedComponentMaterialSwitcherStorage : public TPreAnimatedStateStorage<TPreAnimatedMaterialTraits<FComponentMaterialAccessor, UObject*, FComponentMaterialInfo>>`  
_L55-59_
- inherits: `TPreAnimatedStateStorage<TPreAnimatedMaterialTraits<FComponentMaterialAccessor,UObject*,FComponentMaterialInfo>>`
- L58 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedComponentMaterialSwitcherStorage> StorageID;`

#### struct `UE::MovieScene::FPreAnimatedComponentMaterialParameterStorage`  
`struct FPreAnimatedComponentMaterialParameterStorage : public TPreAnimatedStateStorage<TPreAnimatedMaterialParameterTraits<FComponentMaterialAccessor, UObject*, FComponentMaterialInfo>>`  
_L61-65_
- inherits: `TPreAnimatedStateStorage<TPreAnimatedMaterialParameterTraits<FComponentMaterialAccessor,UObject*,FComponentMaterialInfo>>`
- L64 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedComponentMaterialParameterStorage> StorageID;`

#### class `UMovieSceneComponentMaterialSystem`  
`class UMovieSceneComponentMaterialSystem : public UMovieSceneEntitySystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L71-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem,IMovieScenePreAnimatedStateSystemInterface`
- L79 _public prototype_ `UMovieSceneComponentMaterialSystem(const FObjectInitializer& ObjInit);`
- L83 _private prototype_ `virtual void OnLink() override;`
- L84 _private prototype_ `virtual void OnUnlink() override;`
- L85 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L87 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L91 _private member_ `UE::MovieScene::TMovieSceneMaterialSystem<UE::MovieScene::FComponentMaterialAccessor, UObject*, FComponentMaterialInfo> SystemImpl;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L24 _function_ `friend uint32 GetTypeHash(const FComponentMaterialKey& In)` (scope `UE::MovieScene`)
- L28 _function_ `friend bool operator==(const FComponentMaterialKey& A, const FComponentMaterialKey& B)` (scope `UE::MovieScene`)
- L52 _typedef_ `using FPreAnimatedComponentMaterialTraits = TPreAnimatedMaterialTraits<FComponentMaterialAccessor, UObject*, FComponentMaterialInfo>;` (scope `UE::MovieScene`)
- L53 _typedef_ `using FPreAnimatedComponentMaterialParameterTraits = TPreAnimatedMaterialParameterTraits<FComponentMaterialAccessor, UObject*, FComponentMaterialInfo>;` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneComponentMobilitySystem.h` (Public)


#### class `UMovieSceneComponentMobilitySystem`  
`class UMovieSceneComponentMobilitySystem : public UMovieSceneEntityInstantiatorSystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L16-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem,IMovieScenePreAnimatedStateSystemInterface`
- L24 _public prototype_ `UMovieSceneComponentMobilitySystem(const FObjectInitializer& ObjInit);`
- L28 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L29 _private prototype_ `virtual void OnLink() override final;`
- L30 _private prototype_ `virtual void OnUnlink() override final;`
- L31 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L34 _private prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L35 _private prototype_ `virtual void RestorePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L39 _private member_ `UE::MovieScene::TOverlappingEntityTracker<EComponentMobility::Type, FObjectKey> MobilityTracker;`
- L41 _private member_ `UE::MovieScene::FEntityComponentFilter Filter;`
- L43 _private member_ `TArray<TTuple<USceneComponent*, EComponentMobility::Type>> PendingMobilitiesToRestore;`

#### struct `UE::MovieScene::FPreAnimatedMobilityTraits`  
`struct FPreAnimatedMobilityTraits : FBoundObjectPreAnimatedStateTraits`  
_L52-59_
- inherits: `FBoundObjectPreAnimatedStateTraits`
- L54 _public typedef_ `using KeyType = FObjectKey;`
- L55 _public typedef_ `using StorageType = EComponentMobility::Type;`
- L57 _public prototype_ `void RestorePreAnimatedValue(const FObjectKey& InKey, EComponentMobility::Type Mobility, const FRestoreStateParams& Params);`
- L58 _public prototype_ `EComponentMobility::Type CachePreAnimatedValue(UObject* InObject);`

#### struct `UE::MovieScene::FPreAnimatedComponentMobilityStorage`  
`struct FPreAnimatedComponentMobilityStorage : TPreAnimatedStateStorage_ObjectTraits<FPreAnimatedMobilityTraits>`  
_L61-67_
- inherits: `TPreAnimatedStateStorage_ObjectTraits<FPreAnimatedMobilityTraits>`
- L63 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedComponentMobilityStorage> StorageID;`
- L65 _public prototype_ `FPreAnimatedStateEntry FindEntry(USceneComponent* InSceneComponent);`
- L66 _public prototype_ `FPreAnimatedStateEntry MakeEntry(USceneComponent* InSceneComponent);`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace UE`
- L49 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneComponentTransformSystem.h` (Public)


#### class `UMovieSceneComponentTransformSystem`  
`class UMovieSceneComponentTransformSystem : public UMovieScenePropertySystem`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L21 _public prototype_ `UMovieSceneComponentTransformSystem(const FObjectInitializer& ObjInit);`
- L25 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneConstraintSystem.h` (Public)


#### class `UMovieSceneConstraintSystem`  
`class UMovieSceneConstraintSystem : public UMovieSceneEntitySystem`  
_L20-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for propagating constraints to a bound object's FConstraintsManagerController.
- L32 _public prototype_ `UMovieSceneConstraintSystem(const FObjectInitializer& ObjInit);`
- L33 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L34 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L39 _protected member_ `TArray<FUpdateHandleForConstraint> DynamicOffsets;`

#### struct `UMovieSceneConstraintSystem::FUpdateHandleForConstraint`  
`struct FUpdateHandleForConstraint`  
_L26-30_
- desc: if constraint has a dynamic offset we need to make sure the constraint get's notified the handle is updated
- L28 _public member_ `TWeakObjectPtr<UTickableTransformConstraint> Constraint;`
- L29 _public member_ `TWeakObjectPtr<UTransformableComponentHandle> TransformHandle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneCustomPrimitiveDataSystem.h` (Public)


#### struct `UE::MovieScene::FAnimatedCustomPrimitiveDataInfo`  
`struct FAnimatedCustomPrimitiveDataInfo`  
_L20-31_
- L23 _public member_ `TWeakObjectPtr<UMovieSceneEntitySystemLinker> WeakLinker;` — Weak linker ptr - only assigned if the output entity is ever allocated
- L25 _public member_ `TWeakObjectPtr<UMovieSceneBlenderSystem> WeakBlenderSystem;` — Weak blender system ptr - only assigned if the blend channel is ever allocated
- L26 _public member_ `int32 NumContributors = 0;`
- L27 _public member_ `FMovieSceneEntityID OutputEntityID;`
- L28 _public member_ `FMovieSceneBlendChannelID BlendChannelID;`
- L30 _public prototype_ `~FAnimatedCustomPrimitiveDataInfo();`

#### class `UMovieSceneCustomPrimitiveDataSystem`  
`class UMovieSceneCustomPrimitiveDataSystem : public UMovieSceneEntitySystem`  
_L49-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System responsible for tracking and animating custom primitive data entities. Operates on the following component types from FMovieSceneTracksComponentTypes: Instantiation: Tracks any ScalarParameterName with a CustomPrimitiveData tag on a BoundObject where that BoundObject is a Primitive Component. Manages adding BlendChannelInputs and Outputs where multiple entities animate the same custom primitive data index. Evaluation:    Visits any BoundObject with the supported parameter name and either a BlendChannelOutput component or no BlendChannelInput, and applies the resulting parameter to the Custom Primitive Data on the Primitive Component.
- L56 _public prototype_ `UMovieSceneCustomPrimitiveDataSystem(const FObjectInitializer& ObjInit);`
- L60 _private prototype_ `virtual void OnLink() override;`
- L61 _private prototype_ `virtual void OnUnlink() override;`
- L62 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L63 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L65 _private prototype_ `void OnInstantiation();`
- L66 _private prototype_ `void OnEvaluation(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents);`
- L71 _private member_ `UE::MovieScene::TOverlappingEntityTracker<UE::MovieScene::FAnimatedCustomPrimitiveDataInfo, FObjectKey, FName> ScalarParameterTracker;` — Overlapping trackers that track multiple entities animating the same bound object and name
- L74 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedCustomPrimitiveDataEntryStorage> ScalarParameterStorage;` — Holds pre-animated values for custom primitive data entries
- L76 _private member_ `UE::MovieScene::FEntityGroupingPolicyKey GroupingKey;`
- L81 _public member_ `TObjectPtr<UMovieScenePiecewiseDoubleBlenderSystem> DoubleBlenderSystem;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)
- L33 _prototype_ `void CollectGarbageForOutput(FAnimatedCustomPrimitiveDataInfo* Output);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneDeferredComponentMovementSystem.h` (Public)


#### class `UMovieSceneDeferredComponentMovementSystem`  
`class UMovieSceneDeferredComponentMovementSystem : public UMovieSceneEntitySystem`  
_L28-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that maintains a FScopedMovementUpdate for any USceneComponent that has an animated transform or attachment for the duration of the evaluation to avoid repeatedly updating child transforms and/or overlaps. This system can be enabled/disabled using the cvar Sequencer.DeferMovementUpdates (is disabled by default) Output logging options are controlled by Sequencer.OutputDeferredMovementMode which is useful for tracking how many components are being moved in any given frame. This system runs in the Initialization and Evaluaion phases: Initialization: Gathers and initializes deferred movement for any AttachParent components that need (un)link Evaluation: Gathers and initializes deferred movement for any Component Transforms; queues up an event trigger to be executed at the end of the phase Finalization: Applys all pending movement updates in reverse order
- L35 _public prototype_ `UMovieSceneDeferredComponentMovementSystem(const FObjectInitializer& ObjInit);`
- L38 _public prototype_ `void DeferMovementUpdates(USceneComponent* InComponent);` — Request that movement updates for the specified component be deferred until the end of the evaluation
- L42 _private prototype_ `virtual void BeginDestroy() override;`
- L44 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L45 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L46 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L47 _private prototype_ `virtual void OnUnlink() override final;`
- L50 _private prototype_ `void ApplyMovementUpdates();` — Apply all currently pending movement updates
- L53 _private prototype_ `void OutputDeferredMovements();` — Output the current movement updates to the log
- L56 _private prototype_ `void EnsureMovementsFlushed();` — Check all movements have been flush
- L87 _private member_ `TChunkedArray<TOptional<FScopedMovementUpdateContainer>, 8192> ScopedUpdates;` — Chunked array of movement updates to ensure that once allocated, a movement update's address can never change

#### struct `UMovieSceneDeferredComponentMovementSystem::FScopedSequencerMovementUpdate`  
`struct FScopedSequencerMovementUpdate : FScopedMovementUpdate`  
_L65-76_
- inherits: `FScopedMovementUpdate`
- desc: WARNING: FScopedMovementUpdate is very specifically designed with strict ordering constraints on its constructor and destructor. Care is taken here to ensure 2 things: 1. FScopedMovementUpdate can never be moved or copied (its address is cached inside USceneComponent::ScopedMovementStack) 2. Once constructed, they must be destructed in strictly reverse order
- L67 _public function_ `FScopedSequencerMovementUpdate(USceneComponent* Component) : FScopedMovementUpdate(Component)`
- L69 _public prototype_ `void operator=(const FScopedSequencerMovementUpdate&) = delete;`
- L70 _public prototype_ `FScopedSequencerMovementUpdate(const FScopedSequencerMovementUpdate&) = delete;`
- L72 _public prototype_ `void operator=(FScopedSequencerMovementUpdate&&) = delete;`
- L73 _public prototype_ `FScopedSequencerMovementUpdate(FScopedSequencerMovementUpdate&&) = delete;`
- L75 _public prototype_ `USceneComponent* GetComponent() const;`

#### struct `UMovieSceneDeferredComponentMovementSystem::FScopedMovementUpdateContainer`  
`struct FScopedMovementUpdateContainer`  
_L79-84_
- desc: Struct that allows us to use FScopedMovementUpdate on the heap
- L81 _public function_ `FScopedMovementUpdateContainer(USceneComponent* Component) : Value(Component)`
- L83 _public member_ `FScopedSequencerMovementUpdate Value;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneDoublePropertySystem.h` (Public)


#### class `UMovieSceneDoublePropertySystem`  
`class UMovieSceneDoublePropertySystem : public UMovieScenePropertySystem`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneDoublePropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneEnumPropertySystem.h` (Public)


#### class `UMovieSceneEnumPropertySystem`  
`class UMovieSceneEnumPropertySystem : public UMovieScenePropertySystem`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L13 _private prototype_ `UMovieSceneEnumPropertySystem(const FObjectInitializer& ObjInit);`
- L15 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneEulerTransformPropertySystem.h` (Public)


#### class `UMovieSceneEulerTransformPropertySystem`  
`class UMovieSceneEulerTransformPropertySystem : public UMovieScenePropertySystem`  
_L10-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L16 _public prototype_ `UMovieSceneEulerTransformPropertySystem(const FObjectInitializer& ObjInit);`
- L18 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneEventSystems.h` (Public)


#### struct `FMovieSceneEventTriggerData`  
`struct FMovieSceneEventTriggerData`  
_L18-31_
- reflection: `USTRUCT()`
- L23 _public member_ `FMovieSceneEventPtrs Ptrs;` — `UPROPERTY()`
- L26 _public member_ `FGuid ObjectBindingID;` — `UPROPERTY()`
- L28 _public member_ `FMovieSceneSequenceID SequenceID;`
- L30 _public member_ `FFrameTime RootTime;`

#### class `UMovieSceneEventSystem`  
`class UMovieSceneEventSystem : public UMovieSceneEntitySystem`  
_L40-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L45 _public prototype_ `UMovieSceneEventSystem(const FObjectInitializer& ObjInit);`
- L47 _public prototype_ `void AddEvent(UE::MovieScene::FInstanceHandle RootInstance, const FMovieSceneEventTriggerData& TriggerData);`
- L51 _protected prototype_ `bool HasEvents() const;`
- L52 _protected prototype_ `void TriggerAllEvents();`
- L56 _private typedef_ `using FSharedPlaybackState = UE::MovieScene::FSharedPlaybackState;`
- L58 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L59 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L60 _private prototype_ `virtual void OnUnlink() override final;`
- L62 _private prototype_ `static void TriggerEvents(TArrayView<const FMovieSceneEventTriggerData> Events, TSharedRef<const FSharedPlaybackState> SharedPlaybackState);`
- L63 _private prototype_ `static void TriggerEventWithParameters(UObject* DirectorInstance, const FMovieSceneEventTriggerData& Event, TArrayView<UObject* const> GlobalContexts, TSharedRef<const FSharedPlaybackState> SharedPlaybackState);`
- L64 _private prototype_ `static bool PatchBoundObject(uint8* Parameters, UObject* BoundObject, FProperty* BoundObjectProperty, TSharedRef<const FSharedPlaybackState> SharedPlaybackState, FMovieSceneSequenceID SequenceID);`
- L67 _private member_ `TMap< UE::MovieScene::FInstanceHandle, TArray<FMovieSceneEventTriggerData> > EventsByRoot;` — Events grouped by root sequence instance handle

#### class `UMovieScenePreSpawnEventSystem`  
`class UMovieScenePreSpawnEventSystem : public UMovieSceneEventSystem`  
_L72-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEventSystem`
- desc: System that triggers events before any spawnables
- L77 _public prototype_ `UMovieScenePreSpawnEventSystem(const FObjectInitializer& ObjInit);`

#### class `UMovieScenePostSpawnEventSystem`  
`class UMovieScenePostSpawnEventSystem : public UMovieSceneEventSystem`  
_L83-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEventSystem`
- desc: System that triggers events after any spawnables
- L88 _public prototype_ `UMovieScenePostSpawnEventSystem(const FObjectInitializer& ObjInit);`

#### class `UMovieScenePostEvalEventSystem`  
`class UMovieScenePostEvalEventSystem : public UMovieSceneEventSystem`  
_L93-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEventSystem`
- desc: System that triggers events right at the end of evaluation
- L98 _public prototype_ `UMovieScenePostEvalEventSystem(const FObjectInitializer& ObjInit);`
- L100 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents)override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneFloatPropertySystem.h` (Public)


#### class `UMovieSceneFloatPropertySystem`  
`class UMovieSceneFloatPropertySystem : public UMovieScenePropertySystem`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneFloatPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneHierarchicalBiasSystem.h` (Public)


#### class `UMovieSceneHierarchicalBiasSystem`  
`class UMovieSceneHierarchicalBiasSystem : public UMovieSceneEntityInstantiatorSystem`  
_L17-33_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- L23 _public prototype_ `UMovieSceneHierarchicalBiasSystem(const FObjectInitializer& ObjInit);`
- L27 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L28 _private prototype_ `virtual void OnLink() override;`
- L29 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L32 _private member_ `TObjectPtr<UMovieSceneEntityGroupingSystem> GroupingSystem;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneInitialValueSystem.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneIntegerPropertySystem.h` (Public)


#### class `UMovieSceneIntegerPropertySystem`  
`class UMovieSceneIntegerPropertySystem : public UMovieScenePropertySystem`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L13 _private prototype_ `UMovieSceneIntegerPropertySystem(const FObjectInitializer& ObjInit);`
- L15 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneMaterialParameterCollectionSystem.h` (Public)


#### class `UMovieSceneMaterialParameterCollectionSystem`  
`class UMovieSceneMaterialParameterCollectionSystem : public UMovieSceneEntitySystem`  
_L27-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that resolves MPC components into BoundMaterial components that can be used by downstream parameter systems
- L34 _public prototype_ `UMovieSceneMaterialParameterCollectionSystem(const FObjectInitializer& ObjInit);`
- L38 _private prototype_ `virtual void OnLink() override;`
- L39 _private prototype_ `virtual void OnUnlink() override;`
- L40 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L45 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedScalarMaterialParameterStorage> ScalarParameterStorage;` — Holds pre-animated values for scalar MPC values
- L47 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedVectorMaterialParameterStorage> VectorParameterStorage;` — Holds pre-animated values for vector or color MPC values
- L49 _private member_ `UE::MovieScene::FEntityGroupingPolicyKey GroupingKey;` — Registered key for the grouping policy that groups MPC tracks together

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneMaterialParameterSystem.h` (Public)


#### struct `UE::MovieScene::FAnimatedMaterialParameterInfo`  
`struct FAnimatedMaterialParameterInfo`  
_L22-33_
- L25 _public member_ `TWeakObjectPtr<UMovieSceneEntitySystemLinker> WeakLinker;` — Weak linker ptr - only assigned if the output entity is ever allocated
- L27 _public member_ `TWeakObjectPtr<UMovieSceneBlenderSystem> WeakBlenderSystem;` — Weak blender system ptr - only assigned if the blend channel is ever allocated
- L28 _public member_ `int32 NumContributors = 0;`
- L29 _public member_ `FMovieSceneEntityID OutputEntityID;`
- L30 _public member_ `FMovieSceneBlendChannelID BlendChannelID;`
- L32 _public prototype_ `~FAnimatedMaterialParameterInfo();`

#### class `UMovieSceneMaterialParameterInstantiatorSystem`  
`class UMovieSceneMaterialParameterInstantiatorSystem : public UMovieSceneEntityInstantiatorSystem`  
_L50-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System responsible for tracking material parameter entities. Tracks any BoundMaterial with a MaterialParameterInfo, as well as deprecated ScalarParameterName, ColorParameterName or VectorParameterName. Manages adding BlendChannelInputs and Outputs where multiple entities animate the same parameter on the same bound material. BoundMaterials may be a UMaterialInstanceDynamic, or a UMaterialParameterCollectionInstance.
- L56 _public prototype_ `UMovieSceneMaterialParameterInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L60 _private prototype_ `virtual void OnLink() override;`
- L61 _private prototype_ `virtual void OnUnlink() override;`
- L62 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L67 _private member_ `UE::MovieScene::TOverlappingEntityTracker<UE::MovieScene::FAnimatedMaterialParameterInfo, UE::MovieScene::FObjectComponent, FMaterialParameterInfo> ScalarParameterTracker;` — Overlapping trackers that track multiple entities animating the same bound object and name
- L68 _private member_ `UE::MovieScene::TOverlappingEntityTracker<UE::MovieScene::FAnimatedMaterialParameterInfo, UE::MovieScene::FObjectComponent, FMaterialParameterInfo> VectorParameterTracker;`
- L71 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedScalarMaterialParameterStorage> ScalarParameterStorage;` — Holds pre-animated values for scalar values
- L73 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedVectorMaterialParameterStorage> VectorParameterStorage;` — Holds pre-animated values for vector or color values
- L78 _public member_ `TObjectPtr<UMovieScenePiecewiseDoubleBlenderSystem> DoubleBlenderSystem;` — `UPROPERTY()`

#### class `UMovieSceneMaterialParameterEvaluationSystem`  
`class UMovieSceneMaterialParameterEvaluationSystem : public UMovieSceneEntitySystem`  
_L89-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System responsible for animating material parameter entities. Visits any BoundMaterial with the supported parameter names and either a BlendChannelOutput component or no BlendChannelInput, and applies the resulting parameter to the bound material instance.
- L95 _public prototype_ `UMovieSceneMaterialParameterEvaluationSystem(const FObjectInitializer& ObjInit);`
- L99 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L100 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L35 _prototype_ `void CollectGarbageForOutput(FAnimatedMaterialParameterInfo* Output);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneMaterialSystem.h` (Public)


#### struct `FMovieScenePreAnimatedMaterialParameters`  
`struct FMovieScenePreAnimatedMaterialParameters`  
_L27-44_
- reflection: `USTRUCT()`
- L31 _public prototype_ `UMaterialInterface* GetMaterial() const;`
- L33 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);`
- L39 _private member_ `TObjectPtr<UMaterialInterface> PreviousMaterial;` — `UPROPERTY()` — Strong ptr to the previously assigned material interface (used when Sequencer.UseSoftObjectPtrsForPreAnimatedMaterial is false)
- L43 _private member_ `TSoftObjectPtr<UMaterialInterface> SoftPreviousMaterial;` — `UPROPERTY()` — Soft ptr to the previously assigned material interface (used when Sequencer.UseSoftObjectPtrsForPreAnimatedMaterial is true)

#### struct `UE::MovieScene::TPreAnimatedMaterialTraits`  
`template<typename AccessorType, typename... RequiredComponents> struct TPreAnimatedMaterialTraits : FBoundObjectPreAnimatedStateTraits`  
_L50-82_
- inherits: `FBoundObjectPreAnimatedStateTraits`
- L52 _public typedef_ `using KeyType = typename AccessorType::KeyType;`
- L53 _public typedef_ `using StorageType = FMovieScenePreAnimatedMaterialParameters;`
- L57 _public function_ `static FMovieScenePreAnimatedMaterialParameters CachePreAnimatedValue(typename TCallTraits<RequiredComponents>::ParamType... InRequiredComponents)`
- L71 _public function_ `static void RestorePreAnimatedValue(const KeyType& InKey, const FMovieScenePreAnimatedMaterialParameters& PreAnimatedValue, const FRestoreStateParams& Params)`

#### class `UE::MovieScene::TMovieSceneMaterialSystem`  
`template<typename AccessorType, typename... RequiredComponents> class TMovieSceneMaterialSystem`  
_L88-190_
- L92 _public typedef_ `using MaterialSwitcherStorageType = TPreAnimatedStateStorage<TPreAnimatedMaterialTraits<AccessorType, RequiredComponents...>>;`
- L93 _public typedef_ `using MaterialParameterStorageType = TPreAnimatedStateStorage<TPreAnimatedMaterialParameterTraits<AccessorType, RequiredComponents...>>;`
- L95 _public member_ `TSharedPtr<MaterialSwitcherStorageType> MaterialSwitcherStorage;`
- L96 _public member_ `TSharedPtr<MaterialParameterStorageType> MaterialParameterStorage;`
- L98 _public prototype_ `void OnLink(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents);`
- L99 _public prototype_ `void OnUnlink(UMovieSceneEntitySystemLinker* Linker);`
- L100 _public prototype_ `void OnRun(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents, FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents);`
- L102 _public prototype_ `void SavePreAnimatedState(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents, const IMovieScenePreAnimatedStateSystemInterface::FPreAnimationParameters& InParameters);`
- L104 _public prototype_ `void OnPostSpawn(UMovieSceneEntitySystemLinker* InLinker, TComponentTypeID<RequiredComponents>... InRequiredComponents);`
- L184 _protected member_ `UE::MovieScene::FEntityGroupingPolicyKey GroupingKey;`
- L186 _protected member_ `FEntityComponentFilter MaterialSwitcherFilter;`
- L187 _protected member_ `FEntityComponentFilter MaterialParameterFilter;`
- L189 _protected member_ `FCachedEntityFilterResult_Allocations ReinitializeBoundMaterials;`
- L351 _function_ `template<typename AccessorType, typename... RequiredComponents> void TMovieSceneMaterialSystem<AccessorType, RequiredComponents...>::OnLink(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents)`
- L379 _function_ `template<typename AccessorType, typename... RequiredComponents> void TMovieSceneMaterialSystem<AccessorType, RequiredComponents...>::OnUnlink(UMovieSceneEntitySystemLinker* Linker)`
- L392 _function_ `template<typename AccessorType, typename... RequiredComponents> void TMovieSceneMaterialSystem<AccessorType, RequiredComponents...>::OnPostSpawn(UMovieSceneEntitySystemLinker* InLinker, TComponentTypeID<RequiredComponents>... InRequiredComponents)`
- L417 _function_ `template<typename AccessorType, typename... RequiredComponents> void TMovieSceneMaterialSystem<AccessorType, RequiredComponents...>::OnRun(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents, FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents)`
- L464 _function_ `template<typename AccessorType, typename... RequiredComponents> void TMovieSceneMaterialSystem<AccessorType, RequiredComponents...>::SavePreAnimatedState(UMovieSceneEntitySystemLinker* Linker, TComponentTypeID<RequiredComponents>... InRequiredComponents, const IMovieScenePreAnimatedStateSystemInterface::FPreAnimationParameters& InParameters)`

#### struct `UE::MovieScene::TMovieSceneMaterialSystem::FMaterialGroupingPolicy`  
`struct FMaterialGroupingPolicy`  
_L108-182_
- L110 _public typedef_ `using GroupKeyType = TTuple<RequiredComponents..., FMaterialParameterInfo>;`
- L112 _public function_ `void InitializeGroupKeys( TEntityGroupingHandlerBase<FMaterialGroupingPolicy>& Handler, FEntityGroupBuilder* Builder, FEntityAllocationIteratorItem Item, FReadEntityIDs EntityIDs, TWrite<FEntityGroupID> GroupIDs, TRead<RequiredComponents>... Components)`
- L177 _public function_ `bool OnObjectsReplaced(GroupKeyType& InOutKey, const TMap<UObject*, UObject*>& ReplacementMap)`

#### struct `UE::MovieScene::TApplyMaterialSwitchers`  
`template<typename AccessorType, typename... RequiredComponents> struct TApplyMaterialSwitchers`  
_L193-218_
- L195 _public function_ `static void ForEachEntity(typename TCallTraits<RequiredComponents>::ParamType... Inputs, const FObjectComponent& ObjectResult)`

#### struct `UE::MovieScene::TInitializeBoundMaterials`  
`template<typename AccessorType, typename... RequiredComponents> struct TInitializeBoundMaterials`  
_L221-272_
- L223 _public function_ `static bool InitializeBoundMaterial(typename TCallTraits<RequiredComponents>::ParamType... Inputs, FObjectComponent& OutDynamicMaterial)`
- L268 _public function_ `static void ForEachEntity(typename TCallTraits<RequiredComponents>::ParamType... Inputs, FObjectComponent& OutDynamicMaterial)`

#### struct `UE::MovieScene::TReinitializeBoundMaterials`  
`template<typename AccessorType, typename... RequiredComponents> struct TReinitializeBoundMaterials`  
_L276-309_
- L278 _public member_ `UMovieSceneEntitySystemLinker* Linker;`
- L279 _public member_ `TArray<FMovieSceneEntityID> ReboundMaterials;`
- L281 _public function_ `TReinitializeBoundMaterials(UMovieSceneEntitySystemLinker* InLinker) : Linker(InLinker)`
- L285 _public function_ `void ForEachAllocation(int32 Num, const FMovieSceneEntityID* EntityIDs, const RequiredComponents*... Inputs, FObjectComponent* Objects)`
- L293 _public function_ `void ForEachEntity(FMovieSceneEntityID EntityID, typename TCallTraits<RequiredComponents>::ParamType... Inputs, FObjectComponent& OutDynamicMaterial)`
- L301 _public function_ `void PostTask()`

#### struct `UE::MovieScene::TAddBoundMaterialMutationImpl`  
`template<typename AccessorType, typename... RequiredComponents, int... Indices> struct TAddBoundMaterialMutationImpl<AccessorType, TIntegerSequence<int, Indices...>, RequiredComponents...> : IMovieSceneEntityMutation`  
_L315-347_
- inherits: `IMovieSceneEntityMutation`
- L317 _public function_ `TAddBoundMaterialMutationImpl(TComponentTypeID<RequiredComponents>... InRequiredComponents) : ComponentTypes(InRequiredComponents...)`
- L323 _public function_ `virtual void CreateMutation(FEntityManager* EntityManager, FComponentMask* InOutEntityComponentTypes) const override`
- L327 _public function_ `virtual void InitializeAllocation(FEntityAllocation* Allocation, const FComponentMask& AllocationType) const`
- L333 _public function_ `void InitializeAllocation(FEntityAllocation* Allocation, FObjectComponent* OutBoundMaterials, const RequiredComponents*... InRequiredComponents) const`
- L343 _private member_ `FBuiltInComponentTypes* BuiltInComponents;`
- L344 _private member_ `FMovieSceneTracksComponentTypes* TracksComponents;`
- L346 _private member_ `TTuple<TComponentTypeID<RequiredComponents>...> ComponentTypes;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Reinitialize Bound Materials"), MovieSceneEval_ReinitializeBoundMaterials, STATGROUP_MovieScen`
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace MovieScene` (scope `UE`)
- L85 _typedef_ `template<typename AccessorType, typename... RequiredComponents> using TPreAnimatedMaterialParameterTraits = TPreAnimatedMaterialTraits<AccessorType, RequiredComponents...>;` (scope `UE::MovieScene`)
- L446 _typedef_ `using MutationType = TAddBoundMaterialMutationImpl<AccessorType, TMakeIntegerSequence<int, sizeof...(RequiredComponents)>, RequiredComponents...>;` (scope `UE::MovieScene::TMovieSceneMaterialSystem::OnRun`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneMotionVectorSimulationSystem.h` (Public)


#### class `UMovieSceneMotionVectorSimulationSystem`  
`class UMovieSceneMotionVectorSimulationSystem : public UMovieSceneEntitySystem`  
_L28-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L34 _public prototype_ `UMovieSceneMotionVectorSimulationSystem(const FObjectInitializer& ObjInit);`
- L36 _public prototype_ `void EnableThisFrame();`
- L37 _public prototype_ `void SimulateAllTransforms();`
- L38 _public function_ `bool IsSimulationEnabled() const`
- L43 _public prototype_ `void PreserveSimulatedMotion(bool bShouldPreserveTransforms);`
- L45 _public prototype_ `void AddSimulatedTransform(USceneComponent* Component, const FTransform& SimulatedTransform, FName SocketName);`
- L49 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L50 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L52 _private prototype_ `void OnPostEvaluation();`
- L54 _private prototype_ `void ComputeSimulatedMotion();`
- L58 _private prototype_ `void PropagateMotionToComponents();`
- L60 _private prototype_ `FTransform GetTransform(USceneComponent* Component);`
- L62 _private prototype_ `FTransform GetSocketTransform(USceneComponent* Component, FName SocketName);`
- L64 _private prototype_ `bool HavePreviousTransformForParent(USceneComponent* InComponent) const;`
- L66 _private prototype_ `void ApplySimulatedTransforms(USceneComponent* InComponent, const FTransform& InPreviousTransform);`
- L85 _private member_ `TMultiMap<FObjectKey, FSimulatedTransform> TransformData;` — Map of object -> previous transform data
- L88 _private member_ `bool bPreserveTransforms = false;` — Whether to reset TransformData at the end of the frame or not
- L90 _private member_ `bool bSimulationEnabled = false;`
- L92 _private member_ `bool bSimulateTransformsRequested = false;`

#### struct `UMovieSceneMotionVectorSimulationSystem::FSimulatedTransform`  
`struct FSimulatedTransform`  
_L71-82_
- desc: Transform data relating to a specific object or socket
- L73 _public function_ `FSimulatedTransform(const FTransform& InTransform, FName InSocketName = NAME_None) : Transform(InTransform), SocketName(InSocketName)`
- L78 _public member_ `FTransform Transform;` — The transform for the object
- L81 _public member_ `FName SocketName;` — The socket name to which this relates

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieScene` (scope `UE`)
- L21 _prototype_ `FFrameTime GetSimulatedMotionVectorTime(const FMovieSceneContext& Context);` (scope `UE::MovieScene`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneObjectPropertySystem.h` (Public)


#### class `UMovieSceneObjectPropertySystem`  
`class UMovieSceneObjectPropertySystem : public UMovieScenePropertySystem`  
_L9-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L13 _private prototype_ `UMovieSceneObjectPropertySystem(const FObjectInitializer& ObjInit);`
- L15 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePiecewiseBoolBlenderSystem.h` (Public)


#### class `UMovieScenePiecewiseBoolBlenderSystem`  
`class UMovieScenePiecewiseBoolBlenderSystem : public UMovieSceneBlenderSystem`  
_L18-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem`
- L24 _public prototype_ `UMovieScenePiecewiseBoolBlenderSystem(const FObjectInitializer& ObjInit);`
- L26 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L27 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L31 _private member_ `UE::MovieScene::TSimpleBlenderSystemImpl<bool> Impl;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePiecewiseByteBlenderSystem.h` (Public)


#### class `UMovieScenePiecewiseByteBlenderSystem`  
`class UMovieScenePiecewiseByteBlenderSystem : public UMovieSceneBlenderSystem`  
_L19-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem`
- L25 _public prototype_ `UMovieScenePiecewiseByteBlenderSystem(const FObjectInitializer& ObjInit);`
- L27 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L31 _private member_ `UE::MovieScene::TSimpleBlenderSystemImpl<uint8> Impl;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePiecewiseDoubleBlenderSystem.h` (Public)


#### struct `UE::MovieScene::FBlendResult`  
`struct FBlendResult`  
_L19-25_
- desc: Blend result struct that stores the cumulative sum of pre-weighted values, alongside the total weight
- L22 _public member_ `double Total = 0.f;` — Cumulative sum of blend values pre-multiplied with each value's weight.
- L24 _public member_ `float Weight = 0.f;` — Cumulative sum of weights.

#### struct `UE::MovieScene::FAdditveAndOverrideData`  
`struct FAdditveAndOverrideData`  
_L28-42_
- desc: Data for each additive/override section, we don't accumulate until we recieve all of the data
- L31 _public member_ `bool bIsAdditive;` — If Additive, if not then override
- L33 _public member_ `double Value;` — Section Value
- L35 _public member_ `float Weight;` — Section Weight
- L37 _public member_ `int32 BlendingOrder;` — Section Blending Order
- L38 _public function_ `bool operator<(const FAdditveAndOverrideData& RHS) const`

#### struct `UE::MovieScene::FAdditiveAndOverrides`  
`struct FAdditiveAndOverrides`  
_L44-47_
- desc: Structure for holding the sorted blending order data for the additive and override data
- L46 _public member_ `mutable TSortedMap<int32, FAdditveAndOverrideData> Data;`

#### struct `UE::MovieScene::FAccumulationResult`  
`struct FAccumulationResult`  
_L50-83_
- desc: Structure for holding the blend results of each blend type
- L52 _public member_ `const FBlendResult* Absolutes = nullptr;`
- L53 _public member_ `const FBlendResult* Relatives = nullptr;`
- L54 _public member_ `const FBlendResult* Additives = nullptr;`
- L55 _public member_ `const FBlendResult* AdditivesFromBase = nullptr;`
- L56 _public member_ `const FAdditiveAndOverrides* Overrides = nullptr;`
- L57 _public function_ `bool IsValid() const`
- L63 _public function_ `FBlendResult GetAbsoluteResult(uint16 BlendID) const`
- L67 _public function_ `FBlendResult GetRelativeResult(uint16 BlendID) const`
- L71 _public function_ `FBlendResult GetAdditiveResult(uint16 BlendID) const`
- L75 _public function_ `FBlendResult GetAdditiveFromBaseResult(uint16 BlendID) const`
- L79 _public function_ `FAdditiveAndOverrides GetAdditiveAndOverrideResult(uint16 BlendID) const`

#### struct `UE::MovieScene::FAdditiveAndOverrideBuffer`  
`struct FAdditiveAndOverrideBuffer`  
_L86-89_
- desc: Bufffer used for additive/override values
- L88 _public member_ `TArray<FAdditiveAndOverrides> Values;`

#### struct `UE::MovieScene::FAdditiveFromBaseBuffer`  
`struct FAdditiveFromBaseBuffer`  
_L92-96_
- desc: Buffer used for accumulating additive-from-base values
- L94 _public member_ `TArray<FBlendResult> Buffer;`
- L95 _public member_ `TComponentTypeID<double> BaseComponent;`

#### struct `UE::MovieScene::FAccumulationBuffers`  
`struct FAccumulationBuffers`  
_L99-118_
- desc: Struct that maintains accumulation buffers for each blend type, one buffer per float result component type
- L101 _public prototype_ `bool IsEmpty() const;`
- L103 _public prototype_ `void Reset();`
- L105 _public prototype_ `FAccumulationResult FindResults(FComponentTypeID InComponentType) const;`
- L108 _public member_ `TSortedMap<FComponentTypeID, TArray<FBlendResult>> Absolute;` — Map from value result component type -> Absolute blend accumulation buffer for that channel type
- L110 _public member_ `TSortedMap<FComponentTypeID, TArray<FBlendResult>> Relative;` — Map from value result component type -> Relative blend accumulation buffer for that channel type
- L112 _public member_ `TSortedMap<FComponentTypeID, TArray<FBlendResult>> Additive;` — Map from value result component type -> Additive blend accumulation buffer for that channel type
- L114 _public member_ `TSortedMap<FComponentTypeID, FAdditiveFromBaseBuffer> AdditiveFromBase;` — Map from value result component type -> Additive From Base blend accumulation buffer for that channel type
- L116 _public member_ `TSortedMap<FComponentTypeID, FAdditiveAndOverrideBuffer> AdditiveAndOverrides;` — Map from value result component type -> Additive and Override blending order blneds for that channel type

#### class `UMovieScenePiecewiseDoubleBlenderSystem`  
`class UMovieScenePiecewiseDoubleBlenderSystem : public UMovieSceneBlenderSystem, public IMovieSceneValueDecomposer`  
_L124-161_
- reflection: `UCLASS(DisplayName="Weighted per-channel", meta=(Tooltip="Blends each channel of this object's transform as separate scalar components. Useful for blending to/from over-rotated objects (ie, 0 < rotation > 360."), MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem,IMovieSceneValueDecomposer`
- L129 _public prototype_ `UMovieScenePiecewiseDoubleBlenderSystem(const FObjectInitializer& ObjInit);`
- L131 _public typedef_ `using FMovieSceneEntityID = UE::MovieScene::FMovieSceneEntityID;`
- L132 _public typedef_ `using FComponentTypeID = UE::MovieScene::FComponentTypeID;`
- L134 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L135 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L137 _public prototype_ `virtual FGraphEventRef DispatchDecomposeTask(const UE::MovieScene::FValueDecompositionParams& Params, UE::MovieScene::FAlignedDecomposedValue* Output) override;`
- L141 _private prototype_ `void ReinitializeAccumulationBuffers();`
- L142 _private prototype_ `void ZeroAccumulationBuffers();`
- L145 _private member_ `UE::MovieScene::FAccumulationBuffers AccumulationBuffers;` — Buffers that contain accumulated blend values, separated by blend type
- L148 _private member_ `FComponentMask BlendedResultMask;` — Mask that contains value result components that have BlendChannelInput components
- L151 _private member_ `FComponentMask BlendedPropertyMask;` — Mask that contains property tags for any property type that has has at least one BlendChannelOutput
- L154 _private member_ `UE::MovieScene::FCachedEntityManagerState ChannelRelevancyCache;` — Cache state that is used to invalidate and reset the accumulation buffers when the entity manager has structurally changed
- L157 _private member_ `TBitArray<> CachedRelevantProperties;` — Bit array specifying FCompositePropertyTypeID's for properties contained within BlendedPropertyMask
- L160 _private member_ `bool bContainsNonPropertyBlends = false;` — Whether the current entity manager contains any non-property based blends

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePiecewiseEnumBlenderSystem.h` (Public)


#### struct `UE::MovieScene::FSimpleBlenderEnumResultTraits`  
`struct FSimpleBlenderEnumResultTraits`  
_L29-46_
- desc: Custom blend result traits for enums: - We don't blend enums, unlike bytes, because we don't even know if the in-between values are valid enumerations. - Number of contributors doesn't matter. The last one wins.
- L31 _public function_ `static void ZeroAccumulationBuffer(TArrayView<TSimpleBlendResult<uint8>> Buffer)`
- L36 _public function_ `static void AccumulateResult(TSimpleBlendResult<uint8>& InOutValue, uint8 Contributor)`
- L42 _public function_ `static uint8 BlendResult(const TSimpleBlendResult<uint8>& InResult)`

#### class `UMovieScenePiecewiseEnumBlenderSystem`  
`class UMovieScenePiecewiseEnumBlenderSystem : public UMovieSceneBlenderSystem`  
_L52-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem`
- L58 _public prototype_ `UMovieScenePiecewiseEnumBlenderSystem(const FObjectInitializer& ObjInit);`
- L60 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L64 _private member_ `UE::MovieScene::TSimpleBlenderSystemImpl<uint8, UE::MovieScene::FSimpleBlenderEnumResultTraits> Impl;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePiecewiseIntegerBlenderSystem.h` (Public)


#### struct `UE::MovieScene::FIntegerBlendResult`  
`struct FIntegerBlendResult`  
_L17-23_
- desc: Blend result struct that stores the cumulative sum of pre-weighted values, alongside the total weight
- L20 _public member_ `int64 Total = 0;` — Cumulative sum of blend values pre-multiplied with each value's weight.
- L22 _public member_ `double Weight = 0.f;` — Cumulative sum of weights.

#### struct `UE::MovieScene::FIntegerAccumulationBuffers`  
`struct FIntegerAccumulationBuffers`  
_L26-36_
- desc: Struct that maintains accumulation buffers for each blend type
- L28 _public prototype_ `bool IsEmpty() const;`
- L30 _public prototype_ `void Reset();`
- L32 _public member_ `TArray<FIntegerBlendResult> Absolute;`
- L33 _public member_ `TArray<FIntegerBlendResult> Relative;`
- L34 _public member_ `TArray<FIntegerBlendResult> Additive;`
- L35 _public member_ `TArray<FIntegerBlendResult> AdditiveFromBase;`

#### class `UMovieScenePiecewiseIntegerBlenderSystem`  
`class UMovieScenePiecewiseIntegerBlenderSystem : public UMovieSceneBlenderSystem`  
_L43-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem`
- L48 _public prototype_ `UMovieScenePiecewiseIntegerBlenderSystem(const FObjectInitializer& ObjInit);`
- L50 _public typedef_ `using FMovieSceneEntityID = UE::MovieScene::FMovieSceneEntityID;`
- L51 _public typedef_ `using FComponentTypeID = UE::MovieScene::FComponentTypeID;`
- L53 _public prototype_ `virtual void OnLink() override;`
- L54 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L55 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L59 _private prototype_ `void ReinitializeAccumulationBuffers();`
- L60 _private prototype_ `void ZeroAccumulationBuffers();`
- L64 _private member_ `UE::MovieScene::FIntegerAccumulationBuffers AccumulationBuffers;`
- L66 _private member_ `UE::MovieScene::FCachedEntityManagerState ChannelRelevancyCache;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePreAnimatedMaterialParameters.h` (Public)


#### struct `UE::MovieScene::FMaterialParameterKey`  
`struct FMaterialParameterKey`  
_L14-25_
- L16 _public member_ `FObjectKey BoundMaterial;`
- L17 _public member_ `FMaterialParameterInfo ParameterInfo;`
- L19 _public prototype_ `FMaterialParameterKey(const FObjectComponent& InBoundMaterial, const FName& InParameterName);`
- L20 _public prototype_ `FMaterialParameterKey(const FObjectComponent& InBoundMaterial, const FMaterialParameterInfo& InParameterInfo);`

#### struct `UE::MovieScene::FMaterialParameterCollectionScalarTraits`  
`struct FMaterialParameterCollectionScalarTraits : FBoundObjectPreAnimatedStateTraits`  
_L27-38_
- inherits: `FBoundObjectPreAnimatedStateTraits`
- L29 _public typedef_ `using KeyType = FMaterialParameterKey;`
- L30 _public typedef_ `using StorageType = float;`
- L32 _public prototype_ `static void ReplaceObject(FMaterialParameterKey& InOutKey, const FObjectKey& NewObject);`
- L34 _public prototype_ `static float CachePreAnimatedValue(const FObjectComponent& InBoundMaterial, const FName& ParameterName);`
- L35 _public prototype_ `static float CachePreAnimatedValue(const FObjectComponent& InBoundMaterial, const FMaterialParameterInfo& ParameterInfo);`
- L37 _public prototype_ `static void RestorePreAnimatedValue(const FMaterialParameterKey& InKey, float OldValue, const FRestoreStateParams& Params);`

#### struct `UE::MovieScene::FMaterialParameterCollectionVectorTraits`  
`struct FMaterialParameterCollectionVectorTraits : FBoundObjectPreAnimatedStateTraits`  
_L40-51_
- inherits: `FBoundObjectPreAnimatedStateTraits`
- L42 _public typedef_ `using KeyType = FMaterialParameterKey;`
- L43 _public typedef_ `using StorageType = FLinearColor;`
- L45 _public prototype_ `static void ReplaceObject(FMaterialParameterKey& InOutKey, const FObjectKey& NewObject);`
- L47 _public prototype_ `static FLinearColor CachePreAnimatedValue(const FObjectComponent& InBoundMaterial, const FName& ParameterName);`
- L48 _public prototype_ `static FLinearColor CachePreAnimatedValue(const FObjectComponent& InBoundMaterial, const FMaterialParameterInfo& ParameterInfo);`
- L50 _public prototype_ `static void RestorePreAnimatedValue(const FMaterialParameterKey& InKey, const FLinearColor& OldValue, const FRestoreStateParams& Params);`

#### struct `UE::MovieScene::FPreAnimatedScalarMaterialParameterStorage`  
`struct FPreAnimatedScalarMaterialParameterStorage : public TPreAnimatedStateStorage<FMaterialParameterCollectionScalarTraits>`  
_L53-57_
- inherits: `TPreAnimatedStateStorage<FMaterialParameterCollectionScalarTraits>`
- L56 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedScalarMaterialParameterStorage> StorageID;`

#### struct `UE::MovieScene::FPreAnimatedVectorMaterialParameterStorage`  
`struct FPreAnimatedVectorMaterialParameterStorage : public TPreAnimatedStateStorage<FMaterialParameterCollectionVectorTraits>`  
_L59-63_
- inherits: `TPreAnimatedStateStorage<FMaterialParameterCollectionVectorTraits>`
- L62 _public member_ `static TAutoRegisterPreAnimatedStorageID<FPreAnimatedVectorMaterialParameterStorage> StorageID;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePredictionSystem.h` (Public)


#### class `UMovieSceneAsyncAction_SequencePrediction`  
`class UMovieSceneAsyncAction_SequencePrediction : public UBlueprintAsyncActionBase`  
_L42-171_
- reflection: `UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "AsyncTask", HasDedicatedAsyncNode))`
- inherits: `UBlueprintAsyncActionBase`
- desc: Async BP action that represents a pending prediction that is dispatched on a playing sequence.
- L59 _public prototype_ `static UMovieSceneAsyncAction_SequencePrediction* PredictWorldTransformAtTime(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, float TimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category=Cinematics)` — Initiate an asynchronous prediction for the specified component's world transform at a specific time in a sequence Changes in attachment between the sequence's current time, and the predicted time are not accounted for Calling this function on a stopped sequence player is undefined. @param Player          An active, currently playing sequence player to use for predicting the transform @param TargetComponent The component to predict a world transform for @param TimeInSeconds   The time within the sequence to predict the transform at @return An asynchronous prediction object that contains Result and Failure delegates
- L73 _public prototype_ `static UMovieSceneAsyncAction_SequencePrediction* PredictWorldTransformAtFrame(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, FFrameTime FrameTime);` — `UFUNCTION(BlueprintCallable, Category=Cinematics)` — Initiate an asynchronous prediction for the specified component's world transform at a specific time in a sequence Changes in attachment between the sequence's current time, and the predicted time are not accounted for Calling this function on a stopped sequence player is undefined. @param Player          An active, currently playing sequence player to use for predicting the transform @param TargetComponent The component to predict a world transform for @param FrameTime       The frame time to predict at in the sequence's display rate @return An asynchronous prediction object that contains Result and Failure delegates
- L87 _public prototype_ `static UMovieSceneAsyncAction_SequencePrediction* PredictLocalTransformAtTime(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, float TimeInSeconds);` — `UFUNCTION(BlueprintCallable, Category=Cinematics)` — Initiate an asynchronous prediction for the specified component's local transform at a specific time in a sequence Changes in attachment between the sequence's current time, and the predicted time are not accounted for Calling this function on a stopped sequence player is undefined. @param Player          An active, currently playing sequence player to use for predicting the transform @param TargetComponent The component to predict a world transform for @param TimeInSeconds   The time within the sequence to predict the transform at @return An asynchronous prediction object that contains Result and Failure delegates
- L101 _public prototype_ `static UMovieSceneAsyncAction_SequencePrediction* PredictLocalTransformAtFrame(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, FFrameTime FrameTime);` — `UFUNCTION(BlueprintCallable, Category=Cinematics)` — Initiate an asynchronous prediction for the specified component's local transform at a specific time in a sequence Changes in attachment between the sequence's current time, and the predicted time are not accounted for Calling this function on a stopped sequence player is undefined. @param Player          An active, currently playing sequence player to use for predicting the transform @param TargetComponent The component to predict a world transform for @param FrameTime       The frame time to predict at in the sequence's display rate @return An asynchronous prediction object that contains Result and Failure delegates
- L109 _public prototype_ `void ImportEntities(UE::MovieScene::FInterrogationChannels* Channels);` — Called during the instantiation phase to query the sequence for any transform track entities in the field and import the necessary entities into the Entity Manager. @param Channels Interrogation channel map for tracking channels for objects
- L115 _public prototype_ `void Reset(UMovieSceneEntitySystemLinker* Linker);` — Reset this prediction by marking all its entities for unlink
- L124 _public prototype_ `void ReportResult(UE::MovieScene::FInterrogationChannels* Channels, const TSparseArray<TArray<FTransform>>& AllResults);` — Report the result for this prediction to any observers @param Channels    Interrogation channel map for retrieving channels for objects @param AllResults  The interrogation results for all predictions, in the space requested by this prediction
- L125 _public prototype_ `void ReportResult(UE::MovieScene::FInterrogationChannels* Channels, const TSparseArray<TArray<UE::MovieScene::FIntermediate3DTransform>>& AllResults);`
- L129 _private prototype_ `static UMovieSceneAsyncAction_SequencePrediction* MakePredictionImpl(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, float TimeInSeconds, bool bInWorldSpace);`
- L130 _private prototype_ `static UMovieSceneAsyncAction_SequencePrediction* MakePredictionImpl(UMovieSceneSequencePlayer* Player, USceneComponent* TargetComponent, FFrameTime TickResolutionTime, bool bInWorldSpace);`
- L132 _private prototype_ `int32 ImportTransformEntities(UMovieSceneEntitySystemLinker* Linker, const UE::MovieScene::FEntityImportSequenceParams& ImportParams, const FGuid& ObjectGuid, FFrameTime PredictedTime, const FMovieSceneEntityComponentField* ComponentField, const UE::MovieScene::FInterrogationKey& InterrogationKey);`
- L133 _private prototype_ `int32 ImportTransformEntities(UObject* PredicateObject, UObject* ObjectContext, const UE::MovieScene::FInterrogationKey& InterrogationKey);`
- L135 _private prototype_ `void ImportLocalTransforms(UE::MovieScene::FInterrogationChannels* Channels, USceneComponent* InSceneComponent);`
- L136 _private prototype_ `void ImportTransformHierarchy(UE::MovieScene::FInterrogationChannels* Channels, USceneComponent* InSceneComponent);`
- L142 _public member_ `FMovieSceneActorPredictionResult Result;` — `UPROPERTY(BlueprintAssignable)` — Called when a message is broadcast on the specified channel. Use GetPayload() to request the message payload.
- L146 _public member_ `FMovieSceneActorPredictionFailure Failure;` — `UPROPERTY(BlueprintAssignable)` — Called when a message is broadcast on the specified channel. Use GetPayload() to request the message payload.
- L153 _private member_ `TArray<UE::MovieScene::FMovieSceneEntityID> ImportedEntities;` — Cached array of all the entities created by this prediction
- L157 _private member_ `TObjectPtr<UMovieSceneSequencePlayer> SequencePlayer;` — `UPROPERTY()` — The sequence player we're interrogating
- L161 _private member_ `TObjectPtr<USceneComponent> SceneComponent;` — `UPROPERTY()` — The target scene component we're interrogating
- L164 _private member_ `FFrameTime RootPredictedTime;` — The time at which the interrogation should run
- L167 _private member_ `int32 InterrogationIndex;` — The interrogation index used for any FInterrogationKeys that this prediction creates. Unique to this prediction
- L170 _private member_ `bool bWorldSpace;` — Whether we're capturing world space or local space transforms

#### class `UMovieScenePredictionSystem`  
`class UMovieScenePredictionSystem : public UMovieSceneEntitySystem`  
_L178-202_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System responsible for managing and reporting on pending UMovieSceneAsyncAction_SequencePrediction tasks
- L184 _public prototype_ `UMovieScenePredictionSystem(const FObjectInitializer& ObjInit);`
- L186 _public prototype_ `void AddPendingPrediction(UMovieSceneAsyncAction_SequencePrediction* Prediction);`
- L188 _public prototype_ `int32 MakeNewInterrogation(FFrameTime InTime);`
- L192 _private prototype_ `bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L193 _private prototype_ `void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L195 _private member_ `UE::MovieScene::FInterrogationChannels InterrogationChannels;`
- L198 _private member_ `TArray<TObjectPtr<UMovieSceneAsyncAction_SequencePrediction>> PendingPredictions;` — `UPROPERTY()`
- L201 _private member_ `TArray<TObjectPtr<UMovieSceneAsyncAction_SequencePrediction>> ProcessingPredictions;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L26 _namespace_ `namespace MovieScene` (scope `UE`)
- L35 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovieSceneActorPredictionResult, FTransform, PredictedTransform);`
- L35 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovieSceneActorPredictionResult, FTransform, PredictedTransform);`
- L36 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMovieSceneActorPredictionFailure);`
- L36 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMovieSceneActorPredictionFailure);`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePropertyInstantiator.h` (Public)


#### class `UMovieScenePropertyInstantiatorSystem`  
`class UMovieScenePropertyInstantiatorSystem : public UMovieSceneEntityInstantiatorSystem`  
_L38-245_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: Class responsible for resolving all property types registered with FBuiltInComponentTypes::PropertyRegistry
- L43 _public typedef_ `using FMovieSceneEntityID = UE::MovieScene::FMovieSceneEntityID;`
- L47 _public prototype_ `UMovieScenePropertyInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L52 _public prototype_ `UE::MovieScene::FPropertyStats GetStatsForProperty(UE::MovieScene::FCompositePropertyTypeID PropertyID) const;` — Retrieve the stats for a specific property
- L65 _public function_ `template<typename PropertyTraits, typename ValueType> UE::MovieScene::TRecompositionResult<ValueType> RecomposeBlend(const UE::MovieScene::TPropertyComponents<PropertyTraits>& InComponents, const UE::MovieScene::FDecompositionQuery& InQuery, const ValueType& InCurrentValue)` — Recompose a value from the constituent parts specified in InQuery, taking into account the weightings of each channel. For instance, if a property comprises 3 additive values (a:1, b:2, c:3), and we recompose 'a' with an InCurrentValue of 10, the result for a would be 5. @note: ValueType must be either copy assignable to/from the storage type of the property, or must have a ConvertOperationalProperty overload @param InComponents   The components that define the property to decompose @param InQuery        The query defining the entities and object to recompose @param InCurrentValue The value of the property to recompose @return A result matching the storage type of the components, containing recomposed values for each of the entities specified in InQuery
- L95 _public prototype_ `template<typename PropertyTraits> UE::MovieScene::TRecompositionResult<typename PropertyTraits::StorageType> RecomposeBlendOperational(const UE::MovieScene::TPropertyComponents<PropertyTraits>& InComponents, const UE::MovieScene::FDecompositionQuery& InQuery, const typename PropertyTraits::StorageType& InCurrentValue);` — Recompose a value from the constituent parts specified in InQuery, taking into account the weightings of each channel. For instance, if a property comprises 3 additive values (a:1, b:2, c:3), and we recompose 'a' with an InCurrentValue of 10, the result for a would be 5. @param InComponents   The components that define the property to decompose @param InQuery        The query defining the entities and object to recompose @param InCurrentValue The value of the property to recompose @return A result matching the storage type of the components, containing recomposed values for each of the entities specified in InQuery
- L97 _public prototype_ `UE::MovieScene::FPropertyRecomposerPropertyInfo FindPropertyFromSource(FMovieSceneEntityID EntityID, UObject* Object) const;`
- L101 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L102 _private prototype_ `virtual void OnLink() override;`
- L103 _private prototype_ `virtual void OnUnlink() override;`
- L104 _private prototype_ `virtual void OnCleanTaggedGarbage() override;`
- L108 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L112 _private typedef_ `using FChannelMask = TBitArray<TFixedAllocator< 1 >>;`
- L113 _private typedef_ `using FSlowPropertyPtr = TSharedPtr<FTrackInstancePropertyBindings>;`
- L123 _private function_ `friend uint32 GetTypeHash(FContributorKey In)`
- L128 _private function_ `friend bool operator==(FContributorKey A, FContributorKey B)`
- L206 _private prototype_ `void DiscoverInvalidatedProperties(TBitArray<>& OutInvalidatedProperties);`
- L207 _private prototype_ `void DiscoverExpiredProperties(TBitArray<>& OutInvalidatedProperties);`
- L208 _private prototype_ `void DiscoverNewProperties(TBitArray<>& OutInvalidatedProperties);`
- L209 _private prototype_ `void UpgradeFloatToDoubleProperties(const TBitArray<>& InvalidatedProperties);`
- L210 _private prototype_ `void ProcessInvalidatedProperties(const TBitArray<>& InvalidatedProperties);`
- L211 _private prototype_ `void UpdatePropertyInfo(const FPropertyParameters& Params);`
- L212 _private prototype_ `void InitializeFastPath(const FPropertyParameters& Params);`
- L213 _private prototype_ `void InitializeBlendPath(const FPropertyParameters& Params);`
- L215 _private prototype_ `void DestroyStaleProperty(int32 PropertyIndex);`
- L216 _private prototype_ `void PostDestroyStaleProperties();`
- L218 _private prototype_ `FSetupBlenderSystemResult SetupBlenderSystem(const FPropertyParameters& Params);`
- L220 _private prototype_ `bool ResolveProperty(UE::MovieScene::FCustomAccessorView CustomAccessors, UObject* Object, const FMovieScenePropertyBinding& PropertyBinding, const UE::MovieScene::FEntityGroupID& GroupID, int32 PropertyDefinitionIndex);`
- L222 _private prototype_ `void InitializePropertyMetaData(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents);`
- L226 _private member_ `static constexpr uint16 INVALID_BLEND_CHANNEL = uint16(-1);`
- L228 _private member_ `UE::MovieScene::FEntityGroupingPolicyKey PropertyGroupingKey;`
- L230 _private member_ `TSparseArray<FObjectPropertyInfo> ResolvedProperties;`
- L231 _private member_ `TMultiMap<FContributorKey, FMovieSceneEntityID> Contributors;`
- L232 _private member_ `TMultiMap<FContributorKey, FMovieSceneEntityID> NewContributors;`
- L234 _private member_ `TArray<UE::MovieScene::FPropertyStats> PropertyStats;`
- L236 _private member_ `UE::MovieScene::FComponentMask CleanFastPathMask;`
- L238 _private member_ `TBitArray<> PendingInvalidatedProperties;`
- L239 _private member_ `TBitArray<> InitializePropertyMetaDataTasks;`
- L240 _private member_ `TBitArray<> SaveGlobalStateTasks;`
- L242 _private member_ `UE::MovieScene::FBuiltInComponentTypes* BuiltInComponents;`
- L244 _private member_ `UE::MovieScene::FPropertyRecomposerImpl RecomposerImpl;`
- L249 _function_ `template<typename PropertyTraits> UE::MovieScene::TRecompositionResult<typename PropertyTraits::StorageType> UMovieScenePropertyInstantiatorSystem::RecomposeBlendOperational(const UE::MovieScene::TPropertyComponents<PropertyTraits>& Components, const UE::MovieScene::FDecompositionQuery& InQuery, const typename PropertyTraits::StorageType& InCurrentValue)`

#### struct `UMovieScenePropertyInstantiatorSystem::FContributorKey`  
`struct FContributorKey`  
_L115-132_
- L117 _public function_ `FContributorKey(int32 InPropertyIndex) : PropertyIndex(InPropertyIndex)`
- L121 _public member_ `int32 PropertyIndex;`

#### struct `UMovieScenePropertyInstantiatorSystem::FObjectPropertyInfo`  
`struct FObjectPropertyInfo`  
_L134-172_
- L136 _public function_ `FObjectPropertyInfo(UE::MovieScene::FResolvedProperty&& InProperty) : Property(MoveTemp(InProperty)) , BoundObject(nullptr) , BlendChannel(FMovieSceneBlendChannelID::INVALID_BLEND_CHANNEL) , bWantsRestoreState( false) , bSupportsFastPath( true) , bNeedsInitialValue( false) , bMaxHBiasHasChanged(false) , bIsPartiallyAnimated(false)`
- L148 _public member_ `UE::MovieScene::FResolvedProperty Property;` — Variant of the property itself as either a pointer offset, a custom property index, or slow track instance bindings object
- L150 _public member_ `TWeakObjectPtr<UMovieSceneBlenderSystem> Blender;` — Pointer to the blender system to use for this property, if its blended
- L152 _public member_ `UObject* BoundObject;` — The object being animated
- L154 _public member_ `FMovieScenePropertyBinding PropertyBinding;` — The path of the property being animated
- L156 _public member_ `FChannelMask EmptyChannels;` — Mask of composite channels that are not animated (set bits indicate an unanimated channel)
- L158 _public member_ `UE::MovieScene::FMovieSceneEntityID FinalBlendOutputID;` — The entity that contains the property component itself. Invalid for fast path properties.
- L159 _public member_ `UE::MovieScene::FMovieSceneEntityID PreviousFastPathID;`
- L161 _public member_ `uint16 BlendChannel;` — Final blend channel for this object.
- L163 _public member_ `int32 PropertyDefinitionIndex;` — The index of this property within FPropertyRegistry::GetProperties.
- L165 _public member_ `TOptional<int32> ConvertedFromPropertyDefinitionIndex;` — Index of a float-based property if this property has been set for float-to-double conversion
- L166 _public member_ `int16 HBias = 0;`
- L167 _public member_ `uint8 bWantsRestoreState : 1;`
- L168 _public member_ `uint8 bSupportsFastPath : 1;`
- L169 _public member_ `uint8 bNeedsInitialValue : 1;`
- L170 _public member_ `uint8 bMaxHBiasHasChanged : 1;`
- L171 _public member_ `uint8 bIsPartiallyAnimated : 1;`

#### struct `UMovieScenePropertyInstantiatorSystem::FBlenderSystemInfo`  
`struct FBlenderSystemInfo`  
_L176-180_
- L178 _public member_ `UClass* BlenderSystemClass = nullptr;`
- L179 _public member_ `UE::MovieScene::FComponentTypeID BlenderTypeTag;`

#### struct `UMovieScenePropertyInstantiatorSystem::FSetupBlenderSystemResult`  
`struct FSetupBlenderSystemResult`  
_L182-186_
- L184 _public member_ `FBlenderSystemInfo CurrentInfo;`
- L185 _public member_ `FBlenderSystemInfo PreviousInfo;`

#### struct `UMovieScenePropertyInstantiatorSystem::FPropertyParameters`  
`struct FPropertyParameters`  
_L189-204_
- desc: Parameter structure passed around when instantiating a specific instance of a property
- L192 _public member_ `FObjectPropertyInfo* PropertyInfo;` — Pointer to the property instance to be animated
- L194 _public member_ `const UE::MovieScene::FPropertyDefinition* PropertyDefinition;` — Pointer to the property type definition from FPropertyRegistry
- L196 _public member_ `int32 PropertyInfoIndex;` — The index of the PropertyInfo member within UMovieScenePropertyInstantiatorSystem::ResolvedProperties
- L198 _public prototype_ `FContributorKey MakeContributorKey() const;`
- L200 _public prototype_ `void MakeOutputComponentType( const UE::MovieScene::FEntityManager& EntityManager, TArrayView<const UE::MovieScene::FPropertyCompositeDefinition> Composites, UE::MovieScene::FComponentMask& OutComponentType) const;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MovieScene` (scope `UE`)
- L69 _typedef_ `using StorageType = typename PropertyTraits::StorageType;` (scope `UMovieScenePropertyInstantiatorSystem::RecomposeBlend`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePropertyNotificationSystem.h` (Public)


#### class `UMovieScenePropertyNotificationSystem`  
`class UMovieScenePropertyNotificationSystem : public UMovieSceneEntitySystem`  
_L13-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: A system that can notify an object that some of its properties are being animated.
- L19 _public prototype_ `UMovieScenePropertyNotificationSystem(const FObjectInitializer& ObjInit);`
- L23 _protected prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieScenePropertySystem.h` (Public)


#### class `UMovieScenePropertySystem`  
`class UMovieScenePropertySystem : public UMovieSceneEntitySystem , public IMovieScenePreAnimatedStateSystemInterface`  
_L16-55_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMovieSceneEntitySystem,IMovieScenePreAnimatedStateSystemInterface`
- desc: Abstract base class for any property system that deals with a property registered with FBuiltInComponentTypes::PropertyRegistry
- L23 _public prototype_ `UMovieScenePropertySystem(const FObjectInitializer& ObjInit);`
- L29 _public function_ `template<typename PropertyTraits> void BindToProperty(const UE::MovieScene::TPropertyComponents<PropertyTraits>& InComponents)` — Must be called on construction of derived classes to initialize the members necessary for this system to animate its property
- L39 _protected prototype_ `virtual void OnLink() override;`
- L40 _protected prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L41 _protected prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L43 _protected prototype_ `virtual void SavePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L44 _protected prototype_ `virtual void RestorePreAnimatedState(const FPreAnimationParameters& InParameters) override;`
- L48 _protected member_ `TObjectPtr<UMovieScenePropertyInstantiatorSystem> InstantiatorSystem;` — `UPROPERTY()` — Pointer to the property instantiator system for retrieving property stats
- L51 _protected member_ `UE::MovieScene::FCompositePropertyTypeID CompositePropertyID;` — Must be set on construction - the composite type of the property this system operates with
- L54 _protected member_ `UE::MovieScene::FPreAnimatedStorageID PreAnimatedStorageID;` — Pre-animated storage ID saved when we create pre-animated state

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneQuaternionBlenderSystem.h` (Public)


#### struct `UE::MovieScene::FQuatTransform`  
`struct FQuatTransform`  
_L15-20_
- L17 _public member_ `FVector Translation;`
- L18 _public member_ `FQuat Rotation;`
- L19 _public member_ `FVector Scale;`

#### struct `UE::MovieScene::FQuaternionBlenderAccumulationBuffers`  
`struct FQuaternionBlenderAccumulationBuffers`  
_L22-27_
- L24 _public member_ `TSparseArray<double> AbsoluteWeights;`
- L25 _public member_ `TArray<FQuatTransform> Absolutes;`
- L26 _public member_ `TArray<FQuatTransform> Additives;`

#### class `UMovieSceneQuaternionBlenderSystem`  
`class UMovieSceneQuaternionBlenderSystem : public UMovieSceneBlenderSystem, public IMovieSceneValueDecomposer`  
_L31-46_
- reflection: `UCLASS(DisplayName="Shortest Rotation (quaternion slerp)", meta=(Tooltip="Uses a quaternion spherical interpolation (slerp) to blend between transforms using the shortest rotation path. Does not support over-rotation."), MinimalAPI)`
- inherits: `UMovieSceneBlenderSystem,IMovieSceneValueDecomposer`
- L36 _public prototype_ `UMovieSceneQuaternionBlenderSystem(const FObjectInitializer& ObjInit);`
- L38 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L39 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L41 _public prototype_ `virtual FGraphEventRef DispatchDecomposeTask(const UE::MovieScene::FValueDecompositionParams& Params, UE::MovieScene::FAlignedDecomposedValue* Output) override;`
- L45 _private member_ `UE::MovieScene::FQuaternionBlenderAccumulationBuffers Buffers;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneQuaternionInterpolationRotationSystem.h` (Public)


#### class `UMovieSceneQuaternionInterpolationRotationSystem`  
`class UMovieSceneQuaternionInterpolationRotationSystem : public UMovieSceneEntitySystem`  
_L10-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L16 _public prototype_ `UMovieSceneQuaternionInterpolationRotationSystem(const FObjectInitializer& ObjInit);`
- L19 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L20 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L21 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneRotatorPropertySystem.h` (Public)


#### class `UMovieSceneRotatorPropertySystem`  
`class UMovieSceneRotatorPropertySystem : public UMovieScenePropertySystem`  
_L10-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- desc: System for rotator property registered within PropertyRegistry
- L15 _public prototype_ `UMovieSceneRotatorPropertySystem(const FObjectInitializer& InObjectInitializer);`
- L18 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& InSubsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneSkeletalAnimationSystem.h` (Public)


#### struct `UE::MovieScene::FActiveSkeletalAnimation`  
`struct FActiveSkeletalAnimation`  
_L22-38_
- desc: Information for a single skeletal animation playing on a bound object
- L24 _public member_ `const UMovieSceneSkeletalAnimationSection* AnimSection;`
- L25 _public member_ `FMovieSceneContext Context;`
- L26 _public member_ `FFrameTime EvalFrameTime;`
- L27 _public member_ `FMovieSceneEntityID EntityID;`
- L28 _public member_ `FRootInstanceHandle RootInstanceHandle;`
- L29 _public member_ `double BlendWeight;`
- L30 _public member_ `float FromEvalTime;`
- L31 _public member_ `float ToEvalTime;`
- L32 _public member_ `EMovieScenePlayerStatus::Type PlayerStatus;`
- L33 _public member_ `uint8 bFireNotifies : 1;`
- L34 _public member_ `uint8 bPlaying : 1;`
- L35 _public member_ `uint8 bResetDynamics : 1;`
- L36 _public member_ `uint8 bWantsRestoreState : 1;`
- L37 _public member_ `uint8 bPreviewPlayback : 1;`

#### struct `UE::MovieScene::FBoneTransformFinalizeData`  
`struct FBoneTransformFinalizeData`  
_L41-61_
- desc: DelegateHandle and Skeletal Mesh for bone transform finalized
- L43 _public prototype_ `FBoneTransformFinalizeData();`
- L44 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;`
- L45 _public member_ `ESwapRootBone SwapRootBone;`
- L46 _public member_ `FTransform MeshRelativeRootMotionTransform;`
- L47 _public member_ `TOptional<FTransform> InitialActorTransform;`
- L48 _public member_ `TOptional<FQuat> InverseMeshToActorRotation;`
- L50 _public member_ `FDelegateHandle OnBoneTransformsFinalizedHandle;` — Delegate Handle for skel mesh bone transform finalized callback
- L53 _public member_ `FDelegateHandle OnBeginActorMovementHandle;`
- L54 _public member_ `FDelegateHandle OnEndActorMovementHandle;`
- L55 _public member_ `bool bActorBeingMoved = false;`
- L58 _public prototype_ `void Register(USkeletalMeshComponent* InSkeleletalMeshCompononent, ESwapRootBone InSwapRootBone, FTransform& InMeshRelativeRootMotionTransform, TOptional<FTransform> InInitialActorTransform);`
- L59 _public prototype_ `void Unregister();`
- L60 _public prototype_ `void BoneTransformFinalized();`

#### struct `UE::MovieScene::FBoundObjectActiveSkeletalAnimations`  
`struct FBoundObjectActiveSkeletalAnimations`  
_L64-75_
- desc: Information for all skeletal animations playing on a bound object
- L66 _public typedef_ `using FAnimationArray = TArray<FActiveSkeletalAnimation, TInlineAllocator<2>>;`
- L69 _public member_ `FAnimationArray Animations;` — All active animations on the corresponding bound object
- L71 _public member_ `FAnimationArray SimulatedAnimations;` — Motion vector simulation animations on the corresponding bound object
- L73 _public member_ `FBoneTransformFinalizeData BoneTransformFinalizeData;` — SkelMesh and the bone finalize Delegate

#### struct `UE::MovieScene::FMontagePlayerPerSectionData`  
`struct FMontagePlayerPerSectionData`  
_L78-82_
- desc: Temporary information about montage setups.
- L80 _public member_ `TWeakObjectPtr<UAnimMontage> Montage;`
- L81 _public member_ `int32 MontageInstanceId;`

#### struct `UE::MovieScene::FSkeletalAnimationSystemData`  
`struct FSkeletalAnimationSystemData`  
_L84-93_
- L86 _public prototype_ `void ResetSkeletalAnimations();`
- L89 _public member_ `TMap<TWeakObjectPtr<USkeletalMeshComponent>, FBoundObjectActiveSkeletalAnimations> SkeletalAnimations;` — Map of active skeletal animations for each bound object
- L92 _public member_ `TMap<FObjectKey, TMap<FObjectKey, FMontagePlayerPerSectionData>> MontageData;` — Map of persistent montage data

#### class `UMovieSceneSkeletalAnimationSystem`  
`class UMovieSceneSkeletalAnimationSystem : public UMovieSceneEntitySystem`  
_L98-158_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L105 _public prototype_ `UMovieSceneSkeletalAnimationSystem(const FObjectInitializer& ObjInit);`
- L107 _public prototype_ `static UObject* ResolveSkeletalMeshComponentBinding(UObject* InObject);`
- L109 _public prototype_ `FTransform GetRootMotionOffset(UObject* InObject) const;`
- L110 _public prototype_ `void UpdateRootMotionOffset(UObject* InObject);`
- L112 _public prototype_ `TOptional<FTransform> GetInitialActorTransform(UObject* InObject) const;`
- L113 _public prototype_ `TOptional<FQuat> GetInverseMeshToActorRotation(UObject* InObject) const;`
- L145 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L146 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L147 _private prototype_ `virtual void OnLink() override;`
- L148 _private prototype_ `virtual void OnUnlink() override;`
- L150 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L152 _private prototype_ `void CleanSystemData();`
- L156 _private member_ `UE::MovieScene::FSkeletalAnimationSystemData SystemData;`
- L157 _private member_ `UE::MovieScene::FEntityGroupingPolicyKey GroupingKey;`

#### struct `UMovieSceneSkeletalAnimationSystem::FAnimationGroupingPolicy`  
`struct FAnimationGroupingPolicy`  
_L117-141_
- L119 _public typedef_ `using GroupKeyType = FObjectKey;`
- L121 _public function_ `bool GetGroupKey(UObject* Object, FMovieSceneSkeletalAnimationComponentData ComponentData, GroupKeyType& OutGroupKey)`
- L130 _public function_ `bool OnObjectsReplaced(GroupKeyType& InOutKey, const TMap<UObject*, UObject*>& ReplacementMap)`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneStringPropertySystem.h` (Public)


#### class `UMovieSceneStringPropertySystem`  
`class UMovieSceneStringPropertySystem : public UMovieScenePropertySystem`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneStringPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneTextPropertySystem.h` (Public)


#### class `UMovieSceneTextPropertySystem`  
`class UMovieSceneTextPropertySystem : public UMovieScenePropertySystem`  
_L9-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L14 _public prototype_ `UMovieSceneTextPropertySystem(const FObjectInitializer& InObjectInitializer);`
- L17 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneTransformOriginSystem.h` (Public)


#### struct `FInstanceToParentPair`  
`struct FInstanceToParentPair`  
_L14-37_
- desc: Helper struct to define sorting behavior for parent to child mapping.
- L17 _public member_ `UE::MovieScene::FInstanceHandle Child;` — In this struct representation the Child represents this sequence.
- L18 _public member_ `UE::MovieScene::FInstanceHandle Parent;`
- L19 _public member_ `int32 Depth = 0;`
- L21 _public function_ `FInstanceToParentPair(const UE::MovieScene::FInstanceHandle Child, const UE::MovieScene::FInstanceHandle Parent, const int32 Depth)`
- L28 _public function_ `bool operator<(const FInstanceToParentPair& Other) const`
- L33 _public function_ `bool operator==(const FInstanceToParentPair& Other) const`

#### class `UMovieSceneTransformOriginInstantiatorSystem`  
`class UMovieSceneTransformOriginInstantiatorSystem : public UMovieSceneEntitySystem`  
_L40-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L46 _public prototype_ `UMovieSceneTransformOriginInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L50 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`

#### class `UMovieSceneTransformOriginSystem`  
`class UMovieSceneTransformOriginSystem : public UMovieSceneEntitySystem`  
_L55-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L61 _public prototype_ `UMovieSceneTransformOriginSystem(const FObjectInitializer& ObjInit);`
- L66 _public prototype_ `bool GetTransformOrigin(UE::MovieScene::FInstanceHandle InstanceHandle, FTransform& OutTransform) const;`
- L68 _public function_ `const TSparseArray<FTransform>& GetTransformOriginsByInstanceID() const`
- L71 _public function_ `const TMap<FMovieSceneSequenceID, UE::MovieScene::FInstanceHandle>& GetSequenceIDToInstanceHandle() const`
- L75 _private prototype_ `virtual void OnLink() override;`
- L76 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L77 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L78 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L82 _private member_ `TSparseArray<FTransform> TransformOriginsByInstanceID;`
- L83 _private member_ `TArray<FInstanceToParentPair> InstanceHandleToParentHandle;`
- L84 _private member_ `UE::MovieScene::FEntityComponentFilter LocationAndRotationFilterResults;`
- L87 _private member_ `TMap<FMovieSceneSequenceID, UE::MovieScene::FInstanceHandle> SequenceIDToInstanceHandle;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneVectorPropertySystem.h` (Public)


#### class `UMovieSceneFloatVectorPropertySystem`  
`class UMovieSceneFloatVectorPropertySystem : public UMovieScenePropertySystem`  
_L10-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L15 _private prototype_ `UMovieSceneFloatVectorPropertySystem(const FObjectInitializer& ObjInit);`
- L17 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

#### class `UMovieSceneDoubleVectorPropertySystem`  
`class UMovieSceneDoubleVectorPropertySystem : public UMovieScenePropertySystem`  
_L21-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertySystem`
- L26 _private prototype_ `UMovieSceneDoubleVectorPropertySystem(const FObjectInitializer& ObjInit);`
- L28 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/MovieSceneVisibilitySystem.h` (Public)


#### class `UMovieSceneVisibilitySystem`  
`class UMovieSceneVisibilitySystem : public UMovieSceneEntityInstantiatorSystem`  
_L21-38_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- L27 _public prototype_ `UMovieSceneVisibilitySystem(const FObjectInitializer& ObjInit);`
- L31 _private prototype_ `virtual void OnLink() override;`
- L32 _private prototype_ `virtual void OnUnlink() override;`
- L33 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L37 _private member_ `TSharedPtr<UE::MovieScene::FPreAnimatedVisibilityStorage> PreAnimatedStorage;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Systems/ObjectPathChannelEvaluatorSystem.h` (Public)


#### class `UObjectPathChannelEvaluatorSystem`  
`class UObjectPathChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating object path channels.
- L23 _public prototype_ `UObjectPathChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L25 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L26 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/StringChannelEvaluatorSystem.h` (Public)


#### class `UStringChannelEvaluatorSystem`  
`class UStringChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L17-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that is responsible for evaluating string channels.
- L23 _public prototype_ `UStringChannelEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L25 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L26 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/TextChannelEvaluatorSystem.h` (Public)


#### class `UTextChannelEvaluatorSystem`  
`class UTextChannelEvaluatorSystem : public UMovieSceneEntitySystem`  
_L10-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System responsible for evaluating Text channels
- L15 _public prototype_ `UTextChannelEvaluatorSystem(const FObjectInitializer& InObjectInitializer);`
- L18 _public prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L19 _public prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`

### `Source/Runtime/MovieSceneTracks/Public/Systems/WeightAndEasingEvaluatorSystem.h` (Public)


#### enum `UE::MovieScene::EHierarchicalBlendMode`  
`enum class EHierarchicalBlendMode : uint8`  
_L42-60_
- L45 _public enumerator_ `AccumulateParentToChild` — Blend hierarchical weights by multiplying children with all parent weights (default)
- L55 _public enumerator_ `ChildFirstBlendTarget` — Combine weights from child -> parent using an increasingly small factor based on previously accumulated weights For example: values = ( (a,t1), (b, t2), (c, t3), (d, t4)) float final_weight = 1; float t = 1; for (i : size(values)) float this = values[i].value*t*values[i].weight t = max(t - this, 0) final_weight *= this
- L58 _public enumerator_ `BezierSeries` — Combine weights from child -> parent using a bezier interpolation series

#### struct `UE::MovieScene::FHierarchicalEasingChannelData`  
`struct FHierarchicalEasingChannelData`  
_L63-86_
- desc: Computation data used for accumulating hierarchical weights for sub sequences
- L66 _public member_ `double FinalResult = 1.0;` — The final result of this easing channel, accumulated with all parents
- L68 _public member_ `double UnaccumulatedResult = 1.0;` — Initial easing result from manual and easing weights, not accumulated with all parents
- L71 _public member_ `uint16 ParentChannel = uint16(-1);` — Our parent's computation data within PreAllocatedComputationData (in order to support one -> many multiplications).
- L73 _public member_ `uint16 ResultChannel = uint16(-1);` — An optional result channel to feed our result to (in order to support many -> one multiplications)
- L76 _public member_ `int16 HBias = 0;` — This channel's HBias
- L80 _public member_ `float CoeffA = 1.f;` — Bezier blending coefficients of the form a(1-t)^b + t^c
- L81 _public member_ `float ExpB = 1.f;`
- L82 _public member_ `float ExpC = 1.f;`
- L85 _public member_ `EHierarchicalBlendMode BlendMode = EHierarchicalBlendMode::AccumulateParentToChild;`

#### struct `UE::MovieScene::FHierarchicalEasingChannelBuffer`  
`struct FHierarchicalEasingChannelBuffer`  
_L88-100_
- L90 _public prototype_ `bool IsEmpty() const;`
- L92 _public prototype_ `void Reset();`
- L93 _public prototype_ `void ResetBlendTargets();`
- L95 _public prototype_ `uint16 AddBaseChannel(const FHierarchicalEasingChannelData& InChannelData);`
- L96 _public prototype_ `uint16 AddBlendTargetChannel(const FHierarchicalEasingChannelData& InChannelData);`
- L98 _public member_ `TArray<FHierarchicalEasingChannelData> Channels;`
- L99 _public member_ `int32 BlendTargetStartIndex = INDEX_NONE;`

#### class `UMovieSceneHierarchicalEasingInstantiatorSystem`  
`class UMovieSceneHierarchicalEasingInstantiatorSystem : public UMovieSceneEntityInstantiatorSystem`  
_L108-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System that creates hierarchical easing channels for any newly introduced HierarchicalEasingProvider components
- L121 _public prototype_ `UMovieSceneHierarchicalEasingInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L123 _public prototype_ `void FinalizeBlendTargets();`
- L127 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const;`
- L128 _private prototype_ `virtual void OnLink() override;`
- L129 _private prototype_ `virtual void OnUnlink() override;`
- L130 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L135 _private member_ `TSparseArray<uint16> CachedInstanceIDToChannel;` — Map between a sub-sequence handle and the easing channel affecting it
- L138 _private member_ `TMap<TTuple<int16, UE::MovieScene::FHierarchicalBlendTarget>, uint16> CachedHierarchicalBlendTargetChannels;` — Cached output channels for a specific pair (source, target) of hierarchical blends
- L141 _private member_ `TObjectPtr<UWeightAndEasingEvaluatorSystem> EvaluatorSystem;` — `UPROPERTY()`
- L144 _private member_ `bool bChannelsHaveBeenInvalidated;` — True of this system just updated all its channels

#### struct `UMovieSceneHierarchicalEasingInstantiatorSystem::FHierarchicalInstanceData`  
`struct FHierarchicalInstanceData`  
_L112-117_
- L114 _public member_ `int32 HierarchicalDepth = -1;`
- L115 _public member_ `uint16 StrongRefCount = 0;`
- L116 _public member_ `uint16 WeakRefCount = 0;`

#### class `UMovieSceneHierarchicalEasingFinalizationSystem`  
`class UE_DEPRECATED(5.5, "This system is no longer functional") UMovieSceneHierarchicalEasingFinalizationSystem : public UMovieSceneEntityInstantiatorSystem`  
_L154-160_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System that finalizes creation of easing channels by allocating new channels for hierarchical blend targets if necessary This is required in order to solve the problem that the hierarchical instantiator needs to run before the property instantiator, but we can't allocate channels for blend targets until _after_ the property instantiator (which sets up the relevant BlendTarget components)
- L159 _public prototype_ `UMovieSceneHierarchicalEasingFinalizationSystem(const FObjectInitializer& ObjInit);`

#### class `UWeightAndEasingEvaluatorSystem`  
`class UWeightAndEasingEvaluatorSystem : public UMovieSceneEntitySystem`  
_L166-191_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that combines manual weights and easings and propagates them to entities with matching EasingChannelID components
- L172 _public prototype_ `UWeightAndEasingEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L177 _public prototype_ `UE::MovieScene::FHierarchicalEasingChannelBuffer& GetComputationBuffer();` — Called from the instantiator system once channel IDs have been calculated
- L181 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L182 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L183 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L184 _private prototype_ `virtual void OnLink() override final;`
- L185 _private prototype_ `virtual void OnUnlink() override final;`
- L190 _private member_ `UE::MovieScene::FHierarchicalEasingChannelBuffer PreAllocatedComputationData;` — Unstable array of preallocated storage for computing easing results sorted by hierarchical depth.

#### Free symbols / members of external scopes

- L32 _macro_ `#define UE_ENABLE_MOVIESCENE_BEZIER_BLENDING 0`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/TrackInstances/MovieSceneCameraCutTrackInstance.h` (Public)


#### struct `UE::MovieScene::FCameraCutPlaybackCapabilityCompatibilityWrapper`  
`struct FCameraCutPlaybackCapabilityCompatibilityWrapper`  
_L26-38_
- desc: Backwards compatibilty wrapper for camera cut playback capability.
- L28 _public prototype_ `FCameraCutPlaybackCapabilityCompatibilityWrapper(const FSequenceInstance& SequenceInstance);`
- L30 _public prototype_ `bool ShouldUpdateCameraCut();`
- L31 _public prototype_ `void OnCameraCutUpdated(const FOnCameraCutUpdatedParams& Params);`
- L33 _public prototype_ `bool ShouldRestoreEditorViewports();`
- L36 _public member_ `FCameraCutPlaybackCapability* CameraCutCapability;`
- L37 _public member_ `IMovieScenePlayer* Player;`

#### class `UMovieSceneCameraCutTrackInstance`  
`class UMovieSceneCameraCutTrackInstance : public UMovieSceneTrackInstance`  
_L45-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneTrackInstance`
- desc: Track instance used to animate camera cuts.
- L56 _public prototype_ `static void ToggleCameraCutLock(UMovieSceneEntitySystemLinker* Linker, bool bEnableCameraCuts, bool bRestoreViewports);` — Toggle camera cut lock on cinematic editor viewports while also correctly managing remember/restoring/discarding pre-animated viewport positions based on sequencer settings.
- L60 _private prototype_ `virtual void OnInitialize() override;`
- L61 _private prototype_ `virtual void OnAnimate() override;`
- L62 _private prototype_ `virtual void OnEndUpdateInputs() override;`
- L63 _private prototype_ `virtual void OnDestroyed() override;`
- L88 _private member_ `FCameraCutCache CameraCutCache;`
- L89 _private member_ `TArray<FCameraCutInputInfo> SortedInputInfos;`
- L92 _private member_ `TUniquePtr<UE::MovieScene::FCameraCutViewportPreviewer> ViewportPreviewer;`

#### struct `UMovieSceneCameraCutTrackInstance::FCameraCutCache`  
`struct FCameraCutCache`  
_L70-74_
- desc: Stores information about the last set camera in order to differentiate between new and pre-existing cuts.
- L72 _public member_ `TWeakObjectPtr<> LastLockedCamera;`
- L73 _public member_ `FMovieSceneTrackInstanceInput LastInput;`

#### struct `UMovieSceneCameraCutTrackInstance::FCameraCutInputInfo`  
`struct FCameraCutInputInfo`  
_L81-86_
- desc: Track instance input qualified with the global start time of its corresponding section, used for sorting inputs and prioritizing more "recent" camera cuts over "older" ones.
- L83 _public member_ `FMovieSceneTrackInstanceInput Input;`
- L84 _public member_ `float GlobalStartTime = 0.f;`
- L85 _public member_ `bool bSavePreAnimatedValue = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENETRACKS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Runtime/MovieSceneTracks/Public/Tracks/IMovieSceneSectionsToKey.h` (Public)


#### class `UMovieSceneSectionsToKey`  
`class UMovieSceneSectionsToKey : public UInterface`  
_L18-22_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieSceneSectionsToKey`  
`class IMovieSceneSectionsToKey`  
_L27-37_
- desc: Interface to be added to UMovieSceneTrack when they have multiple sections to key
- L32 _public prototype_ `IMovieSceneSectionsToKey();`
- L35 _public prototype_ `virtual TArray<TWeakObjectPtr<UMovieSceneSection>> GetSectionsToKey() const = 0;` — Get multiple sections to key

### `Source/Runtime/MovieSceneTracks/Public/Tracks/IMovieSceneTransformOrigin.h` (Public)


#### class `UMovieSceneTransformOrigin`  
`class UMovieSceneTransformOrigin : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(Category="Sequencer", Blueprintable, meta=(DisplayName = "Transform Origin"), MinimalAPI)`
- inherits: `UInterface`

#### class `IMovieSceneTransformOrigin`  
`class IMovieSceneTransformOrigin`  
_L19-36_
- desc: Interface that should be implemented to provide transform tracks with an origin transform. Scale is ignored.
- L25 _public function_ `FTransform GetTransformOrigin() const` — Get the transform origin for this interface
- L34 _protected prototype_ `FTransform BP_GetTransformOrigin() const;` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Sequencer|Section", DisplayName = "GetTransformOrigin", meta=(CallInEditor="true"))` — Get the transform from which all absolute component transform sections should be relative. Scale is ignored.
- L35 _protected function_ `virtual FTransform NativeGetTransformOrigin() const`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScene3DAttachTrack.h` (Public)


#### class `UMovieScene3DAttachTrack`  
`class UMovieScene3DAttachTrack : public UMovieScene3DConstraintTrack`  
_L25-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScene3DConstraintTrack`
- desc: Handles manipulation of path tracks in a movie scene.
- L34 _public prototype_ `virtual UMovieSceneSection* AddConstraint( FFrameNumber Time, int32 Duration, const FName SocketName, const FName ComponentName, const FMovieSceneObjectBindingID& ConstraintBindingID ) override;`
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L36 _public prototype_ `virtual class UMovieSceneSection* CreateNewSection() override;`
- L41 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScene3DConstraintTrack.h` (Public)


#### class `UMovieScene3DConstraintTrack`  
`class UMovieScene3DConstraintTrack : public UMovieSceneTrack`  
_L27-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneTrack`
- desc: Base class for constraint tracks (tracks that are dependent upon other objects).
- L44 _public function_ `virtual UMovieSceneSection* AddConstraint(FFrameNumber Time, int32 Duration, const FName SocketName, const FName ComponentName, const FMovieSceneObjectBindingID& ConstraintBindingID)` — Adds a constraint. @param Time The time relative to the owning movie scene where the section should be. @param Duration The length of the constraint section @param SocketName The socket name for the constraint. @param ComponentName The name of the component the socket resides in. @param FMovieSceneObjectBindingID The object binding id to the constraint. @return The newly created constraint section
- L50 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L51 _public prototype_ `virtual class UMovieSceneSection* CreateNewSection() override;`
- L52 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L53 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L54 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L55 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L56 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L57 _public prototype_ `virtual bool IsEmpty() const override;`
- L58 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L61 _public prototype_ `virtual FText GetDisplayName() const override;`
- L68 _protected member_ `TArray<TObjectPtr<UMovieSceneSection>> ConstraintSections;` — `UPROPERTY()` — List of all constraint sections.

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScene3DPathTrack.h` (Public)


#### class `UMovieScene3DPathTrack`  
`class UMovieScene3DPathTrack : public UMovieScene3DConstraintTrack , public IMovieSceneTrackTemplateProducer`  
_L27-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScene3DConstraintTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles manipulation of path tracks in a movie scene
- L37 _public prototype_ `virtual UMovieSceneSection* AddConstraint(FFrameNumber Time, int32 Duration, const FName SocketName, const FName ComponentName, const FMovieSceneObjectBindingID& ConstraintBindingID) override;`
- L43 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L44 _public prototype_ `virtual class UMovieSceneSection* CreateNewSection() override;`
- L45 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L48 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScene3DTransformTrack.h` (Public)


#### struct `FTrajectoryKey`  
`struct FTrajectoryKey`  
_L16-51_
- L30 _public function_ `FTrajectoryKey(FFrameNumber InTime) : Time(InTime)`
- L32 _public function_ `bool Is(ERichCurveInterpMode InInterpMode) const`
- L48 _public member_ `FFrameNumber Time;`
- L50 _public member_ `TArray<FData, TInlineAllocator<1>> KeyData;`

#### struct `FTrajectoryKey::FData`  
`struct FData`  
_L18-28_
- L20 _public function_ `FData(UMovieScene3DTransformSection* InSection, TOptional<FKeyHandle> InKeyHandle, ERichCurveInterpMode InInterpMode, FName InChannelName) : Section(InSection), KeyHandle(InKeyHandle), ChannelName(InChannelName), InterpMode(InInterpMode)`
- L24 _public member_ `TWeakObjectPtr<UMovieScene3DTransformSection> Section;`
- L25 _public member_ `TOptional<FKeyHandle> KeyHandle;`
- L26 _public member_ `FName ChannelName;`
- L27 _public member_ `ERichCurveInterpMode InterpMode;`

#### class `UMovieScene3DTransformTrack`  
`class UMovieScene3DTransformTrack : public UMovieScenePropertyTrack , public IMovieSceneBlenderSystemSupport`  
_L57-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneBlenderSystemSupport`
- desc: Handles manipulation of component transforms in a movie scene
- L67 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L68 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L71 _public function_ `virtual bool CanRename() const override`
- L72 _public prototype_ `virtual FText GetDisplayName() const override;`
- L76 _public prototype_ `TSubclassOf<UMovieSceneBlenderSystem> GetBlenderSystem() const override;` — IMovieSceneBlenderSystemSupport
- L77 _public prototype_ `void SetBlenderSystem(TSubclassOf<UMovieSceneBlenderSystem> BlenderSystemClass) override;`
- L78 _public prototype_ `void GetSupportedBlenderSystems(TArray<TSubclassOf<UMovieSceneBlenderSystem>>& OutSystemClasses) const override;`
- L82 _public prototype_ `TArray<FTrajectoryKey> GetTrajectoryData(FFrameNumber Time, int32 MaxNumDataPoints, TRange<FFrameNumber>) const;`
- L83 _public prototype_ `FSlateColor GetLabelColor(const FMovieSceneLabelParams& LabelParams) const override;`
- L90 _private member_ `TSubclassOf<UMovieSceneBlenderSystem> BlenderSystemClass;` — `UPROPERTY()` — User-defined blender system to use for this track

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneActorReferenceTrack.h` (Public)


#### class `UMovieSceneActorReferenceTrack`  
`class UMovieSceneActorReferenceTrack : public UMovieScenePropertyTrack`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of actor reference properties in a movie scene
- L20 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L21 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneAudioTrack.h` (Public)


#### class `UMovieSceneAudioTrack`  
`class UMovieSceneAudioTrack : public UMovieSceneNameableTrack`  
_L22-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Handles manipulation of audio.
- L30 _public prototype_ `virtual UMovieSceneSection* AddNewSoundOnRow(USoundBase* Sound, FFrameNumber Time, int32 RowIndex);` — Adds a new sound cue to the audio
- L33 _public function_ `virtual UMovieSceneSection* AddNewSound(USoundBase* Sound, FFrameNumber Time)` — Adds a new sound cue on the next available/non-overlapping row
- L36 _public function_ `const TArray<UMovieSceneSection*>& GetAudioSections() const` — @return The audio sections on this track
- L45 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L46 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L47 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L48 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L49 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L50 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L51 _public prototype_ `virtual bool IsEmpty() const override;`
- L52 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L53 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L54 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L56 _public prototype_ `virtual void GetCompatibleUserDecorationsImpl(TSet<UClass*>& OutClasses) const override;`
- L59 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L65 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> AudioSections;` — `UPROPERTY()` — List of all root audio sections
- L74 _public function_ `int32 GetRowHeight() const` — Get the height of this track's rows
- L82 _public function_ `void SetRowHeight(int32 NewRowHeight)` — Set the height of this track's rows
- L91 _private member_ `int32 RowHeight;` — `UPROPERTY()` — The height for each row of this track

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace AudioTrackConstants`
- L14 _variable_ `const float ScrubDuration = 0.050f;` (scope `AudioTrackConstants`)

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneBoolTrack.h` (Public)


#### class `UMovieSceneBoolTrack`  
`class UMovieSceneBoolTrack : public UMovieScenePropertyTrack , public IMovieSceneTrackTemplateProducer , public IMovieSceneEntityProvider`  
_L16-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneTrackTemplateProducer,IMovieSceneEntityProvider`
- desc: Handles manipulation of float properties in a movie scene
- L27 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L28 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L29 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L32 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L33 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneByteTrack.h` (Public)


#### class `UMovieSceneByteTrack`  
`class UMovieSceneByteTrack : public UMovieScenePropertyTrack`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of byte properties in a movie scene
- L22 _public prototype_ `virtual void PostLoad() override;` — UMovieSceneTrack interface
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L24 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L26 _public prototype_ `void SetEnum(UEnum* Enum);`
- L28 _public prototype_ `class UEnum* GetEnum() const;`
- L32 _protected member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCVarTrack.h` (Public)


#### class `UMovieSceneCVarTrack`  
`class UMovieSceneCVarTrack : public UMovieSceneNameableTrack`  
_L25-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Track for setting (and restoring) Console Variables during playback.
- L29 _private prototype_ `UMovieSceneCVarTrack( const FObjectInitializer& ObjectInitializer );`
- L34 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — UMovieSceneTrack interface
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L36 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L37 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L38 _public prototype_ `virtual EMovieSceneTrackEasingSupportFlags SupportsEasing(FMovieSceneSupportsEasingParams& Params) const override;`
- L39 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L40 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L41 _public prototype_ `virtual bool IsEmpty() const override;`
- L42 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L43 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L44 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L47 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L54 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — All movie scene sections.

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCameraCutTrack.h` (Public)


#### class `UMovieSceneCameraCutTrack`  
`class UMovieSceneCameraCutTrack : public UMovieSceneNameableTrack`  
_L29-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Handles manipulation of CameraCut properties in a movie scene.
- L33 _private prototype_ `UMovieSceneCameraCutTrack( const FObjectInitializer& ObjectInitializer );`
- L44 _public prototype_ `UMovieSceneCameraCutSection* AddNewCameraCut(const FMovieSceneObjectBindingID& CameraBindingID, FFrameNumber Time);` — Adds a new CameraCut at the specified time. @param CameraBindingID Handle to the camera that the CameraCut switches to when active. @param Time The within this track's movie scene where the CameraCut is initially placed. @return The newly created camera cut section
- L49 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — UMovieSceneTrack interface
- L50 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L51 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L52 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L53 _public prototype_ `virtual EMovieSceneTrackEasingSupportFlags SupportsEasing(FMovieSceneSupportsEasingParams& Params) const override;`
- L54 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L55 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L56 _public prototype_ `virtual bool IsEmpty() const override;`
- L57 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L58 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L59 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L62 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L66 _public prototype_ `bool IsAutoManagingSections() const;` — @return Whether camera cut sections should automatically resize to fill gaps
- L69 _public prototype_ `void SetIsAutoManagingSections(bool bInAutoArrangeSections);` — Sets whether camera cut sections should automatically resize to fill gaps
- L72 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;`
- L75 _public prototype_ `void RearrangeAllSections();`
- L76 _public prototype_ `FFrameNumber FindEndTimeForCameraCut(FFrameNumber StartTime);`
- L80 _protected prototype_ `virtual void PreCompileImpl(FMovieSceneTrackPreCompileResult& OutPreCompileResult) override;`
- L82 _protected prototype_ `bool AutoArrangeSectionsIfNeeded(UMovieSceneSection& ChangedSection, bool bWasDeletion, bool bCleanUp = false);`
- L86 _public member_ `bool bCanBlend;` — `UPROPERTY()`
- L92 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — All movie scene sections.
- L96 _private member_ `bool bAutoArrangeSections;` — `UPROPERTY()` — Whether camera cut sections should automatically resize to fill gaps

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCameraShakeSourceShakeTrack.h` (Public)


#### class `UMovieSceneCameraShakeSourceShakeTrack`  
`class UMovieSceneCameraShakeSourceShakeTrack : public UMovieSceneNameableTrack`  
_L31-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L37 _public prototype_ `UMovieSceneSection* AddNewCameraShake(const FFrameNumber KeyTime, const UCameraShakeSourceComponent& ShakeSourceComponent);`
- L38 _public prototype_ `UMovieSceneSection* AddNewCameraShake(const FFrameNumber KeyTime, const TSubclassOf<UCameraShakeBase> ShakeClass, bool bIsAutomaticShake);`
- L42 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;` — UMovieSceneTrack interface
- L43 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L44 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L45 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L46 _public prototype_ `virtual bool IsEmpty() const override;`
- L47 _public function_ `virtual bool SupportsMultipleRows() const override`
- L48 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L49 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L50 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L51 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L54 _public prototype_ `virtual FText GetDisplayName() const override;`
- L60 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> CameraShakeSections;` — `UPROPERTY()` — List of all sections

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCameraShakeSourceTriggerTrack.h` (Public)


#### class `UMovieSceneCameraShakeSourceTriggerTrack`  
`class UMovieSceneCameraShakeSourceTriggerTrack : public UMovieSceneTrack`  
_L22-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneTrack`
- L29 _public prototype_ `UMovieSceneCameraShakeSourceTriggerTrack(const FObjectInitializer& Obj);`
- L32 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L33 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L34 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L35 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L36 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L37 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L38 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L39 _public prototype_ `virtual bool IsEmpty() const override;`
- L40 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L43 _public prototype_ `virtual FText GetDisplayName() const override;`
- L50 _protected member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — All the sections in this track

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCameraShakeTrack.h` (Public)


#### class `UMovieSceneCameraShakeTrack`  
`class UMovieSceneCameraShakeTrack : public UMovieSceneNameableTrack`  
_L30-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L35 _public prototype_ `virtual UMovieSceneSection* AddNewCameraShake(FFrameNumber KeyTime, TSubclassOf<UCameraShakeBase> ShakeClass);`
- L40 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;` — UMovieSceneTrack interface
- L41 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L42 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L43 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L44 _public prototype_ `virtual bool IsEmpty() const override;`
- L45 _public function_ `virtual bool SupportsMultipleRows() const override`
- L46 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L47 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L48 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L49 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L52 _public prototype_ `virtual FText GetDisplayName() const override;`
- L58 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> CameraShakeSections;` — `UPROPERTY()` — List of all sections

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCinematicShotTrack.h` (Public)


#### class `UMovieSceneCinematicShotTrack`  
`class UMovieSceneCinematicShotTrack : public UMovieSceneSubTrack`  
_L30-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSubTrack`
- desc: A track that holds consecutive sub sequences.
- L37 _public prototype_ `UMovieSceneCinematicShotTrack(const FObjectInitializer& ObjectInitializer);`
- L39 _public prototype_ `void SortSections();`
- L42 _public function_ `virtual UMovieSceneSubSection* AddSequence(UMovieSceneSequence* Sequence, FFrameNumber StartTime, int32 Duration)` — UMovieSceneSubTrack interface
- L44 _public prototype_ `virtual UMovieSceneSubSection* AddSequenceOnRow(UMovieSceneSequence* Sequence, FFrameNumber StartTime, int32 Duration, int32 RowIndex);`
- L47 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;` — UMovieSceneTrack interface
- L48 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L49 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L50 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L51 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L52 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L53 _public prototype_ `virtual bool PopulateEvaluationTree(TMovieSceneEvaluationTree<FMovieSceneTrackEvaluationData>& OutData) const override;`
- L54 _public prototype_ `virtual int8 GetEvaluationFieldVersion() const override;`
- L57 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;`
- L61 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneColorTrack.h` (Public)


#### class `UMovieSceneColorTrack`  
`class UMovieSceneColorTrack : public UMovieScenePropertyTrack`  
_L14-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of float properties in a movie scene
- L20 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L21 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L25 _private member_ `bool bIsSlateColor_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCommonAnimationTrack.h` (Public)


#### struct `FMovieSceneSkeletalAnimRootMotionTrackParams`  
`struct FMovieSceneSkeletalAnimRootMotionTrackParams`  
_L21-38_
- reflection: `USTRUCT()`
- L25 _public member_ `FFrameTime FrameTick;`
- L26 _public member_ `FFrameTime StartFrame;`
- L27 _public member_ `FFrameTime EndFrame;`
- L28 _public member_ `bool bRootMotionsDirty;`
- L29 _public member_ `bool bHaveRootMotion;`
- L30 _public member_ `FTransform RootMotionStartOffset;` — root motion may not be in Mesh Space if we are putting values on a bone that is a child of a root with an offset
- L32 _public function_ `FMovieSceneSkeletalAnimRootMotionTrackParams() : bRootMotionsDirty(true),bHaveRootMotion(false)` — Get the Root Motion transform at the specified time.
- L35 _public member_ `bool bCacheRootTransforms = false;`
- L36 _public member_ `TArray<FTransform> RootTransforms;`

#### class `UMovieSceneCommonAnimationTrack`  
`class UMovieSceneCommonAnimationTrack : public UMovieSceneNameableTrack`  
_L41-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- L48 _public prototype_ `UMovieSceneCommonAnimationTrack(const FObjectInitializer& ObjInit);`
- L51 _public prototype_ `virtual UMovieSceneSection* AddNewAnimationOnRow(FFrameNumber KeyTime, UAnimSequenceBase* AnimSequence, int32 RowIndex);` — Adds a new animation to this track
- L54 _public function_ `virtual UMovieSceneSection* AddNewAnimation(FFrameNumber KeyTime, UAnimSequenceBase* AnimSequence)` — Adds a new animation to this track on the next available/non-overlapping row
- L57 _public prototype_ `virtual void AddSectionWithAutoRow(UMovieSceneSection* Section);` — Adds a section to the track with automatically computed row index. For mixer tracks, computes row based on existing sections and child tracks.
- L60 _public prototype_ `virtual int32 ComputeNextAvailableRowIndex() const;` — Computes the next available row index. For mixer tracks, considers both sections and child tracks.
- L63 _public function_ `virtual UMovieSceneTrack* AddChildTrack(FGuid ObjectBinding, TSubclassOf<UMovieSceneTrack> TrackClass, int32 RowIndex)` — Adds a child track of the specified class at the given row index. Only valid for mixer tracks.
- L70 _public function_ `virtual void GetAllChildTracks(TArray<TObjectPtr<UMovieSceneTrack>>& OutChildTracks) const` — Gets all child tracks. Only valid for mixer tracks. Base implementation returns empty array.
- L72 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L73 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L74 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L75 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L76 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L77 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L78 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L79 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L80 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L81 _public prototype_ `virtual bool IsEmpty() const override;`
- L82 _public prototype_ `virtual void UpdateEasing() override;`
- L85 _public prototype_ `virtual void PostEditImport() override;`
- L86 _public prototype_ `virtual void PostEditUndo() override;`
- L87 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L90 _public function_ `virtual bool ShouldUseRootMotions() const`
- L97 _public prototype_ `void SetRootMotionsDirty();`
- L98 _public prototype_ `void SetUpRootMotions(bool bForce);`
- L99 _public prototype_ `TOptional<FTransform> GetRootMotion(FFrameTime CurrentTime);`
- L100 _public prototype_ `void MatchSectionByBoneTransform(bool bMatchWithPrevious, USkeletalMeshComponent* SkelMeshComp, UMovieSceneSkeletalAnimationSection* CurrentSection, FFrameTime CurrentFrame, FFrameRate InTickResolution, const FName& BoneName, FTransform& SecondSectionRootDiff, FVector& TranslationDiff, FQuat& RotationDiff);`
- L103 _public prototype_ `void ToggleShowRootMotionTrail();`
- L107 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;`
- L112 _private prototype_ `void AutoMatchSectionRoot(UMovieSceneSkeletalAnimationSection* AnimSection);` — Not called yet, will be used to automatch a section when it's added to another
- L114 _private prototype_ `void SortSections();`
- L120 _public member_ `TArray<TObjectPtr<UMovieSceneSection>> AnimationSections;` — `UPROPERTY()` — List of all animation sections
- L123 _public member_ `FMovieSceneSkeletalAnimRootMotionTrackParams RootMotionParams;` — `UPROPERTY()`
- L127 _public member_ `bool bBlendFirstChildOfRoot;` — `UPROPERTY(EditAnywhere, Category = "RootMotions")` — Whether to blend and adjust the first child node with animation instead of the root, this should be true for blending when the root is static, false if the animations have proper root motion
- L133 _public member_ `bool bShowRootMotionTrail;` — `UPROPERTY(EditAnywhere, Category = "RootMotions")` — Whether to show the position of the root for this sections

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETRACKS_API`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneCustomPrimitiveDataTrack.h` (Public)


#### struct `FCustomPrimitiveDataMaterialParametersData`  
`struct FCustomPrimitiveDataMaterialParametersData`  
_L20-26_
- desc: Used to cache mapping between custom primitive data indices and found material parameters using those indices. This is used for nicer display names on channels animating those parameters.
- L22 _public member_ `EMaterialParameterType MaterialParameterType;`
- L23 _public member_ `FComponentMaterialInfo MaterialInfo;`
- L24 _public member_ `FMaterialParameterInfo ParameterInfo;`
- L25 _public member_ `TWeakObjectPtr<UMaterialInterface> MaterialAsset;`

#### class `UMovieSceneCustomPrimitiveDataTrack`  
`class UMovieSceneCustomPrimitiveDataTrack : public UMovieSceneNameableTrack , public IMovieSceneEntityProvider , public IMovieSceneParameterSectionExtender`  
_L34-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneEntityProvider,IMovieSceneParameterSectionExtender`
- desc: Handles manipulation of custom primitive data in a movie scene.
- L43 _public prototype_ `UMovieSceneCustomPrimitiveDataTrack(const FObjectInitializer& ObjectInitializer);`
- L47 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L48 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L49 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L50 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L51 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L52 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L53 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L54 _public prototype_ `virtual bool IsEmpty() const override;`
- L55 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L56 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L57 _public prototype_ `virtual void SetSectionToKey(UMovieSceneSection* Section) override;`
- L58 _public prototype_ `virtual UMovieSceneSection* GetSectionToKey() const override;`
- L69 _public prototype_ `void AddScalarParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, float Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L79 _public prototype_ `void AddScalarParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, int32 RowIndex, float Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L88 _public prototype_ `void AddVector2DParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, FVector2D Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector2D parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L98 _public prototype_ `void AddVector2DParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, int32 RowIndex, FVector2D Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector2D parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L107 _public prototype_ `void AddVectorParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, FVector Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L117 _public prototype_ `void AddVectorParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, int32 RowIndex, FVector Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L126 _public prototype_ `void AddColorParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, FLinearColor Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector2D parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L136 _public prototype_ `void AddColorParameterKey(uint8 CustomPrimitiveDataStartIndex, FFrameNumber Time, int32 RowIndex, FLinearColor Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector2D parameter key to the track. @param CustomPrimitiveDataStartIndex The start index for the custom primitive data @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L139 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneEntityProvider
- L140 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L143 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneParameterSectionExtender
- L153 _public prototype_ `void GetCPDMaterialData(IMovieScenePlayer& Player, FGuid BoundObjectId, FMovieSceneSequenceID SequenceID, TSortedMap<uint8, TArray<FCustomPrimitiveDataMaterialParametersData>>& OutCPDMaterialData);` — Returns the mappings from custom primitive data indices to any material parameters on the bound object. @param Player Movie scene player @param BoundObjectID Bound object ID for the component this track is on @param SequenceID The sequence ID this track is on
- L158 _public prototype_ `FText GetDefaultDisplayName() const override;`
- L168 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The sections owned by this track .
- L172 _private member_ `TObjectPtr<UMovieSceneSection> SectionToKey;` — `UPROPERTY()` — Section we should Key

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneDataLayerTrack.h` (Public)


#### class `UMovieSceneDataLayerTrack`  
`class UMovieSceneDataLayerTrack : public UMovieSceneNameableTrack`  
_L23-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: A track that controls loading, unloading and visibility of data layers
- L28 _public prototype_ `UMovieSceneDataLayerTrack(const FObjectInitializer& ObjectInitializer);`
- L31 _public prototype_ `virtual bool IsEmpty() const override;` — UMovieSceneTrack interface
- L32 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L33 _public prototype_ `virtual void RemoveSection( UMovieSceneSection& Section ) override;`
- L34 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L36 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L37 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L38 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L39 _public function_ `virtual bool SupportsMultipleRows() const override`
- L42 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L48 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneDoubleTrack.h` (Public)


#### class `UMovieSceneDoubleTrack`  
`class UMovieSceneDoubleTrack : public UMovieScenePropertyTrack`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of double properties in a movie scene
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneEnumTrack.h` (Public)


#### class `UMovieSceneEnumTrack`  
`class UMovieSceneEnumTrack : public UMovieScenePropertyTrack`  
_L16-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of byte properties in a movie scene
- L22 _public prototype_ `virtual void PostLoad() override;` — UMovieSceneTrack interface
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L24 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L26 _public prototype_ `void SetEnum(UEnum* Enum);`
- L28 _public prototype_ `class UEnum* GetEnum() const;`
- L32 _protected member_ `TObjectPtr<UEnum> Enum;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneEulerTransformTrack.h` (Public)


#### class `UMovieSceneEulerTransformTrack`  
`class UMovieSceneEulerTransformTrack : public UMovieScenePropertyTrack`  
_L14-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of 3D euler transform properties in a movie scene
- L23 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L24 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneEventTrack.h` (Public)


#### enum `EFireEventsAtPosition`  
`enum class EFireEventsAtPosition : uint8`  
_L18-26_
- reflection: `UENUM()`
- desc: Indicates at what point in the sequence evaluation events should fire
- L21 _public enumerator_ `AtStartOfEvaluation` — Fire events before anything else is evaluated in the sequence
- L23 _public enumerator_ `AtEndOfEvaluation` — Fire events after everything else has been evaluated in the sequence
- L25 _public enumerator_ `AfterSpawn` — Fire events right after any spawn tracks have been evaluated

#### class `UMovieSceneEventTrack`  
`class UMovieSceneEventTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer , public IMovieSceneDeterminismSource`  
_L32-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer,IMovieSceneDeterminismSource`
- desc: Implements a movie scene track that triggers discrete events during playback.
- L42 _public function_ `UMovieSceneEventTrack() : bFireEventsWhenForwards(true) , bFireEventsWhenBackwards(true) , EventPosition(EFireEventsAtPosition::AtEndOfEvaluation)` — Default constructor.
- L56 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L57 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L58 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L59 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L60 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L61 _public prototype_ `virtual bool IsEmpty() const override;`
- L62 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L63 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L64 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L65 _public prototype_ `virtual EMovieSceneCompileResult CustomCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const override;`
- L66 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L67 _public prototype_ `virtual void PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const override;`
- L68 _public function_ `virtual bool SupportsMultipleRows() const override`
- L70 _public prototype_ `virtual void PopulateDeterminismData(FMovieSceneDeterminismData& OutData, const TRange<FFrameNumber>& Range) const override;`
- L73 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L74 _public prototype_ `virtual void PostRename(UObject* OldOuter, const FName OldName) override;`
- L78 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L85 _public member_ `uint32 bFireEventsWhenForwards:1;` — `UPROPERTY(EditAnywhere, Category=TrackEvent)` — If events should be fired when passed playing the sequence forwards.
- L89 _public member_ `uint32 bFireEventsWhenBackwards:1;` — `UPROPERTY(EditAnywhere, Category=TrackEvent)` — If events should be fired when passed playing the sequence backwards.
- L93 _public member_ `EFireEventsAtPosition EventPosition;` — `UPROPERTY(EditAnywhere, Category=TrackEvent)` — Defines where in the evaluation to trigger events
- L99 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The track's sections.

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneFadeTrack.h` (Public)


#### class `UMovieSceneFadeTrack`  
`class UMovieSceneFadeTrack : public UMovieSceneFloatTrack`  
_L14-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneFloatTrack`
- desc: Implements a movie scene track that controls a fade.
- L21 _public prototype_ `UMovieSceneFadeTrack(const FObjectInitializer& Init);`
- L25 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L26 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L29 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L30 _public function_ `virtual bool CanRename() const override`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneFloatTrack.h` (Public)


#### class `UMovieSceneFloatTrack`  
`class UMovieSceneFloatTrack : public UMovieScenePropertyTrack`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of float properties in a movie scene
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneIntegerTrack.h` (Public)


#### class `UMovieSceneIntegerTrack`  
`class UMovieSceneIntegerTrack : public UMovieScenePropertyTrack`  
_L15-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of integer properties in a movie scene
- L21 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L22 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneLevelVisibilityTrack.h` (Public)


#### class `UMovieSceneLevelVisibilityTrack`  
`class UMovieSceneLevelVisibilityTrack : public UMovieSceneNameableTrack`  
_L18-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: A track for controlling the visibility of streamed levels.
- L24 _public function_ `static uint16 GetEvaluationPriority()`
- L27 _public prototype_ `virtual bool IsEmpty() const override;` — UMovieSceneTrack interface
- L28 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L29 _public prototype_ `virtual void RemoveSection( UMovieSceneSection& Section ) override;`
- L30 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L31 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L32 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L33 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L34 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L35 _public function_ `virtual bool SupportsMultipleRows() const override`
- L38 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L44 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneMaterialParameterCollectionTrack.h` (Public)


#### class `UMovieSceneMaterialParameterCollectionTrack`  
`class UMovieSceneMaterialParameterCollectionTrack : public UMovieSceneMaterialTrack , public IMovieSceneEntityProvider , public IMovieSceneParameterSectionExtender`  
_L17-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneMaterialTrack,IMovieSceneEntityProvider,IMovieSceneParameterSectionExtender`
- desc: Handles manipulation of material parameter collections in a movie scene.
- L28 _public member_ `TObjectPtr<UMaterialParameterCollection> MPC;` — `UPROPERTY(EditAnywhere, Category=General, DisplayName="Material Parameter Collection")` — The material parameter collection to manipulate
- L30 _public prototype_ `UMovieSceneMaterialParameterCollectionTrack(const FObjectInitializer& ObjectInitializer);`
- L32 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L33 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L36 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneEntityProvider
- L37 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L40 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneParameterSectionExtender
- L43 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L49 _protected prototype_ `virtual void PostLoad() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneMaterialTrack.h` (Public)


#### enum `EComponentMaterialType`  
`enum class EComponentMaterialType : uint8`  
_L17-31_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Empty` — Empty/Uninitialized
- L22 _public enumerator_ `IndexedMaterial` — A material in one of the indexed slots on a primitive component
- L24 _public enumerator_ `OverlayMaterial` — An overlay material on a mesh component
- L26 _public enumerator_ `DecalMaterial` — A decal material
- L28 _public enumerator_ `VolumetricCloudMaterial` — Volumetric Cloud Material
- L30 _public enumerator_ `SlotOverlayMaterial` — A per-slot overlay material on a mesh component

#### struct `FComponentMaterialInfo`  
`struct FComponentMaterialInfo`  
_L37-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains what is necessary to uniquely identify a material on a component, whether that be an indexed material, one with a slot name, or an overlay material.
- L42 _public member_ `FName MaterialSlotName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sequencer|Material")`
- L45 _public member_ `int32 MaterialSlotIndex = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequencer|Material")`
- L48 _public member_ `EComponentMaterialType MaterialType = EComponentMaterialType::Empty;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sequencer|Material")`
- L59 _public function_ `FString ToString() const`

#### class `UMovieSceneMaterialTrack`  
`class UMovieSceneMaterialTrack : public UMovieSceneNameableTrack`  
_L98-230_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Handles manipulation of material parameters in a movie scene.
- L105 _public prototype_ `UMovieSceneMaterialTrack(const FObjectInitializer& ObjectInitializer);`
- L109 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L110 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L111 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L112 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L113 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L114 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L115 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L116 _public prototype_ `virtual bool IsEmpty() const override;`
- L117 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L118 _public prototype_ `virtual bool SupportsMultipleRows() const override;`
- L119 _public prototype_ `virtual void SetSectionToKey(UMovieSceneSection* Section) override;`
- L120 _public prototype_ `virtual UMovieSceneSection* GetSectionToKey() const override;`
- L131 _public prototype_ `void AddScalarParameterKey(FName ParameterName, FFrameNumber Time, float Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L141 _public prototype_ `void AddScalarParameterKey(FName ParameterName, FFrameNumber Time, int32 RowIndex, float Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L152 _public prototype_ `void AddScalarParameterKey(const FMaterialParameterInfo& ParameterInfo, FFrameNumber Time, float Value, const FString& InLayerName, const FString& InAssetName, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param ParameterInfo The material parameter info for the parameter you want to add a key for. @param Time The time to add the new key. @param The value for the new key. @param InLayerName Optional layer name for use in UI. @param InAssetName Optional asset name for use in UI. @param DefaultInterpolation The default interpolation to use for thew new key.
- L164 _public prototype_ `void AddScalarParameterKey(const FMaterialParameterInfo& ParameterInfo, FFrameNumber Time, int32 RowIndex, float Value, const FString& InLayerName, const FString& InAssetName, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param ParameterInfo The material parameter info for the parameter you want to add a key for. @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param InLayerName Optional layer name for use in UI. @param InAssetName Optional asset name for use in UI. @param DefaultInterpolation The default interpolation to use for thew new key.
- L173 _public prototype_ `void AddColorParameterKey(FName ParameterName, FFrameNumber Time, FLinearColor Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L183 _public prototype_ `void AddColorParameterKey(FName ParameterName, FFrameNumber Time, int32 RowIndex, FLinearColor Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterInfo The material parameter info for the parameter you want to add a key for. @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L194 _public prototype_ `void AddColorParameterKey(const FMaterialParameterInfo& ParameterInfo, FFrameNumber Time, FLinearColor Value, const FString& InLayerName, const FString& InAssetName, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param InLayerName Optional layer name for use in UI. @param InAssetName Optional asset name for use in UI. @param DefaultInterpolation The default interpolation to use for thew new key.
- L206 _public prototype_ `void AddColorParameterKey(const FMaterialParameterInfo& ParameterInfo, FFrameNumber Time, int32 RowIndex, FLinearColor Value, const FString& InLayerName, const FString& InAssetName, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterInfo The material parameter info for the parameter you want to add a key for. @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param InLayerName Optional layer name for use in UI. @param InAssetName Optional asset name for use in UI. @param DefaultInterpolation The default interpolation to use for thew new key.
- L219 _public prototype_ `void AddColorParameterKey(const FMaterialParameterInfo& ParameterInfo, FFrameNumber Time, int32 RowIndex, FLinearColor Value, const FString& InLayerName, const FString& InAssetName, const FParameterChannelNames& InChannelNames, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterInfo The material parameter info for the parameter you want to add a key for. @param Time The time to add the new key. @param RowIndex The preferred row index on which to look for sections. @param The value for the new key. @param InLayerName Optional layer name for use in UI. @param InAssetName Optional asset name for use in UI. @param InChannelNames Optional channel names for the 4 vector channels for use in the UI. @param DefaultInterpolation The default interpolation to use for thew new key.
- L225 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The sections owned by this track .
- L229 _private member_ `TObjectPtr<UMovieSceneSection> SectionToKey;` — `UPROPERTY()` — Section we should Key

#### class `UMovieSceneComponentMaterialTrack`  
`class UMovieSceneComponentMaterialTrack : public UMovieSceneMaterialTrack , public IMovieSceneEntityProvider , public IMovieSceneParameterSectionExtender`  
_L237-292_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneMaterialTrack,IMovieSceneEntityProvider,IMovieSceneParameterSectionExtender`
- desc: A material track which is specialized for animation materials which are owned by actor components.
- L247 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneEntityProvider
- L248 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L251 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneParameterSection* Section, UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) override;` — ~ IMovieSceneParameterSectionExtender
- L255 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L260 _public function_ `const FComponentMaterialInfo& GetMaterialInfo() const` — Gets the index of the material in the component.
- L263 _public function_ `void SetMaterialInfo(const FComponentMaterialInfo& InMaterialInfo)` — Sets the index of the material in the component.
- L269 _public prototype_ `virtual FText GetDisplayNameToolTipText(const FMovieSceneLabelParams& LabelParams) const override;`
- L272 _public prototype_ `virtual FSlateColor GetLabelColor(const FMovieSceneLabelParams& LabelParams) const override;` — We override label color if material binding is broken/partially broken.
- L279 _protected prototype_ `void PostLoad() override;`
- L284 _private member_ `int32 MaterialIndex_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use MaterialInfo instead."))` — The index of this material this track is animating. Has been deprecated in favor of MaterialInfo
- L290 _private member_ `FComponentMaterialInfo MaterialInfo;` — `UPROPERTY()` — The info on the material this track is animating.

#### Free symbols / members of external scopes

- L50 _function_ `friend uint32 GetTypeHash(const FComponentMaterialInfo& In)`
- L54 _function_ `friend bool operator==(const FComponentMaterialInfo& A, const FComponentMaterialInfo& B)`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneObjectPropertyTrack.h` (Public)


#### class `UMovieSceneObjectPropertyTrack`  
`class UMovieSceneObjectPropertyTrack : public UMovieScenePropertyTrack`  
_L10-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- L17 _public member_ `TObjectPtr<UClass> PropertyClass;` — `UPROPERTY()`
- L21 _public member_ `bool bClassProperty = false;` — `UPROPERTY()`
- L24 _public prototype_ `UMovieSceneObjectPropertyTrack(const FObjectInitializer& ObjInit);`
- L27 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — ~ UMovieSceneTrack interface
- L28 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneParticleParameterTrack.h` (Public)


#### class `UMovieSceneParticleParameterTrack`  
`class UMovieSceneParticleParameterTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L30-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles manipulation of material parameters in a movie scene.
- L40 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L41 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L42 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L43 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L44 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L45 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L46 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L47 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L48 _public prototype_ `virtual bool IsEmpty() const override;`
- L49 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L52 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L65 _public prototype_ `void AddScalarParameterKey( FName ParameterName, FFrameNumber Time, float Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a scalar parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L74 _public prototype_ `void AddVectorParameterKey( FName ParameterName, FFrameNumber Time, FVector Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a Vector parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L83 _public prototype_ `void AddColorParameterKey( FName ParameterName, FFrameNumber Time, FLinearColor Value, EMovieSceneKeyInterpolation DefaultInterpolation = EMovieSceneKeyInterpolation::Auto);` — Adds a color parameter key to the track. @param ParameterName The name of the parameter to add a key for. @param Time The time to add the new key. @param The value for the new key. @param DefaultInterpolation The default interpolation to use for thew new key.
- L89 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The sections owned by this track .

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneParticleTrack.h` (Public)


#### class `UMovieSceneParticleTrack`  
`class UMovieSceneParticleTrack : public UMovieSceneNameableTrack , public IMovieSceneTrackTemplateProducer`  
_L27-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack,IMovieSceneTrackTemplateProducer`
- desc: Handles triggering of particle emitters
- L40 _public function_ `virtual TArray<UMovieSceneSection*> GetAllParticleSections() const` — Get the track's particle sections. @return Particle sections collection.
- L49 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L50 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L51 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L52 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L53 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L54 _public prototype_ `virtual bool IsEmpty() const override;`
- L55 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L56 _public prototype_ `virtual void AddNewSection(FFrameNumber SectionTime);`
- L57 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L58 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L61 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L64 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L71 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> ParticleSections;` — `UPROPERTY()` — List of all particle sections.

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScenePrimitiveMaterialTrack.h` (Public)


#### class `UMovieScenePrimitiveMaterialTrack`  
`class UMovieScenePrimitiveMaterialTrack : public UMovieScenePropertyTrack`  
_L11-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- L17 _public prototype_ `UMovieScenePrimitiveMaterialTrack(const FObjectInitializer& ObjInit);`
- L21 _public prototype_ `void SetMaterialIndex(int32 MaterialIndex);` — `UE_DEPRECATED(5.4, "SetMaterialIndex is deprecated, use SetMaterialInfo instead")` — Set the material index that this track is assigned to
- L25 _public prototype_ `int32 GetMaterialIndex() const;` — `UE_DEPRECATED(5.4, "GetMaterialIndex is deprecated, use GetMaterialInfo instead")` — Get the material index that this track is assigned to
- L28 _public prototype_ `void SetMaterialInfo(const FComponentMaterialInfo& InMaterialInfo);` — Set the material info for the material that this track is assigned to
- L31 _public prototype_ `const FComponentMaterialInfo& GetMaterialInfo() const;` — Get the material info for the material that this track is assigned to
- L34 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;` — ~ UMovieSceneTrack interface
- L35 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L38 _public prototype_ `virtual FText GetDisplayNameToolTipText(const FMovieSceneLabelParams& LabelParams) const override;`
- L41 _public prototype_ `virtual FSlateColor GetLabelColor(const FMovieSceneLabelParams& LabelParams) const override;` — We override label color if material binding is broken/partially broken.
- L46 _protected prototype_ `void PostLoad() override;`
- L50 _private member_ `int32 MaterialIndex_DEPRECATED;` — `UPROPERTY()`
- L56 _private member_ `FComponentMaterialInfo MaterialInfo;` — `UPROPERTY()`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieScenePropertyTrack.h` (Public)


#### class `UMovieScenePropertyTrack`  
`class UMovieScenePropertyTrack : public UMovieSceneNameableTrack`  
_L29-175_
- reflection: `UCLASS(abstract, MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Base class for tracks that animate an object property
- L38 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L39 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L40 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L41 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L42 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L43 _public prototype_ `virtual bool IsEmpty() const override;`
- L44 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L45 _public function_ `virtual void InitializeFromProperty(const FProperty* Property, const UE::MovieScene::FPropertyDefinition* Definition)`
- L60 _public function_ `virtual void ProcessSourceValueForKeying(const FProperty* Property, UE::MovieScene::FSourcePropertyValue& InOutValue) const` — Allow specialized property tracks to process a property value before it is used to generate keys. UMovieSceneVisibilityTrack overrides this to invert bool values: the bound property (e.g. AActor::bHidden) stores hidden semantics while the track's bool channel stores visible semantics, so the value must be inverted at key time. @param Property    The property whose value is being keyed. @param InOutValue  The source property value, transformed in place.
- L64 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L65 _public prototype_ `virtual FText GetDisplayNameToolTipText(const FMovieSceneLabelParams& LabelParams) const override;`
- L66 _public prototype_ `virtual FSlateColor GetLabelColor(const FMovieSceneLabelParams& LabelParams) const override;`
- L68 _public prototype_ `virtual FName GetTrackName() const override;`
- L70 _public prototype_ `virtual void PostLoad() override;`
- L71 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L80 _public prototype_ `void SetPropertyNameAndPath(FName InPropertyName, const FString& InPropertyPath);` — Sets the property name for this animatable property @param InPropertyName The property being animated
- L83 _public function_ `FName GetPropertyName() const` — @return the name of the property being animated by this track
- L86 _public function_ `FName GetPropertyPath() const` — @return The property path for this track
- L89 _public function_ `const FMovieScenePropertyBinding& GetPropertyBinding() const` — Access the property binding for this track
- L92 _public function_ `template <typename ValueType> TOptional<ValueType> GetCurrentValue(const UObject* Object) const`
- L103 _public prototype_ `TArray<UMovieSceneSection*, TInlineAllocator<4>> FindAllSections(FFrameNumber Time);` — Find all sections at the current time. @param Time  The Time relative to the owning movie scene where the section should be @Return All sections at that time
- L111 _public prototype_ `class UMovieSceneSection* FindSection(FFrameNumber Time);` — Finds a section at the current time. @param Time The time relative to the owning movie scene where the section should be @return The found section.
- L120 _public prototype_ `class UMovieSceneSection* FindOrExtendSection(FFrameNumber Time, float& OutWeight);` — Finds a section at the current time or extends an existing one @param Time The time relative to the owning movie scene where the section should be @param OutWeight The weight of the section if found @return The found section.
- L129 _public prototype_ `class UMovieSceneSection* FindOrAddSection(FFrameNumber Time, bool& bSectionAdded);` — Finds a section at the current time. @param Time The time relative to the owning movie scene where the section should be @param bSectionAdded Whether a section was added or not @return The found section, or the new section.
- L136 _public prototype_ `virtual void SetSectionToKey(UMovieSceneSection* Section) override;` — Set the section we want to key and recieve globally changed values. @param Section The section that changes.
- L142 _public prototype_ `virtual UMovieSceneSection* GetSectionToKey() const override;` — Finds a section we want to key and recieve globally changed values. @return The Section that changes.
- L149 _public member_ `FName UniqueTrackName;` — `UE_DEPRECATED(5.6, "UniqueTrackName is deprecated, use GetTrackName instead.")` — `UPROPERTY()` — Unique name for this track to afford multiple tracks on a given object (i.e. for array properties)
- L153 _public member_ `FName PropertyName_DEPRECATED;` — `UPROPERTY()` — Name of the property being changed
- L157 _public member_ `FString PropertyPath_DEPRECATED;` — `UPROPERTY()` — Path to the property from the source object being changed
- L165 _private member_ `TObjectPtr<UMovieSceneSection> SectionToKey;` — `UPROPERTY()` — Section we should Key
- L170 _protected member_ `FMovieScenePropertyBinding PropertyBinding;` — `UPROPERTY()`
- L174 _protected member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — All the sections in this list

#### struct `FMovieScenePropertyTrackEntityImportHelper`  
`struct FMovieScenePropertyTrackEntityImportHelper`  
_L178-190_
- L180 _public member_ `static const int32 SectionPropertyValueImportingID;`
- L181 _public member_ `static const int32 SectionEditConditionToggleImportingID;`
- L183 _public prototype_ `static void PopulateEvaluationField(UMovieSceneSection& Section, const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder);`
- L185 _public prototype_ `static bool IsPropertyValueID(const UE::MovieScene::FEntityImportParams& Params);`
- L186 _public prototype_ `static bool IsEditConditionToggleID(const UE::MovieScene::FEntityImportParams& Params);`
- L187 _public prototype_ `static void ImportEditConditionToggleEntity(const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity);`
- L189 _public prototype_ `static FName SanitizeBoolPropertyName(FName InPropertyName);`

#### struct `UE::MovieScene::TPropertyTrackEntityImportHelperImpl`  
`template<typename... T> struct TPropertyTrackEntityImportHelperImpl`  
_L203-261_
- desc: Utility class for importing a customizable property track entity in a way that automatically supports being inside a bound property track or not, and being hooked up to a property with an edit condition or not.
- L205 _public function_ `TPropertyTrackEntityImportHelperImpl(TEntityBuilder<T...>&& InBuilder, FComponentTypeID InPropertyTag = {}) : Builder(MoveTemp(InBuilder)) , PropertyTag(InPropertyTag)`
- L212 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAdd<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload)`
- L218 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition)`
- L223 _public function_ `void Commit(const UMovieSceneSection* InSection, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity)`
- L259 _protected member_ `TEntityBuilder<T...> Builder;`
- L260 _protected member_ `FComponentTypeID PropertyTag;`
- L270 _public function_ `TPropertyTrackEntityImportHelperImpl(FComponentTypeID InPropertyTag) : Builder(FEntityBuilder().AddTag(InPropertyTag)) , PropertyTag(InPropertyTag)`
- L277 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<FAdd, TAdd<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload)`
- L283 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<FAdd, TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition)`
- L290 _protected member_ `TEntityBuilder<FAdd> Builder;`

#### struct `UE::MovieScene::TPropertyTrackEntityImportHelperImpl`  
`template<> struct TPropertyTrackEntityImportHelperImpl<>`  
_L268-292_
- desc: The starting point for TPropertyTrackEntityImportHelperImpl<...T>
- L205 _public function_ `TPropertyTrackEntityImportHelperImpl(TEntityBuilder<T...>&& InBuilder, FComponentTypeID InPropertyTag = {}) : Builder(MoveTemp(InBuilder)) , PropertyTag(InPropertyTag)`
- L212 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAdd<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload)`
- L218 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition)`
- L223 _public function_ `void Commit(const UMovieSceneSection* InSection, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity)`
- L259 _protected member_ `TEntityBuilder<T...> Builder;`
- L260 _protected member_ `FComponentTypeID PropertyTag;`
- L270 _public function_ `TPropertyTrackEntityImportHelperImpl(FComponentTypeID InPropertyTag) : Builder(FEntityBuilder().AddTag(InPropertyTag)) , PropertyTag(InPropertyTag)`
- L277 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<FAdd, TAdd<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload)`
- L283 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<FAdd, TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition)`
- L290 _protected member_ `TEntityBuilder<FAdd> Builder;`

#### struct `UE::MovieScene::FPropertyTrackEntityImportHelper`  
`struct FPropertyTrackEntityImportHelper : TPropertyTrackEntityImportHelperImpl<>`  
_L294-300_
- inherits: `TPropertyTrackEntityImportHelperImpl<>`
- L297 _public function_ `template<typename PropertyTraits> FPropertyTrackEntityImportHelper(const TPropertyComponents<PropertyTraits>& PropertyComponents) : TPropertyTrackEntityImportHelperImpl<>(PropertyComponents.PropertyTag)`

#### struct `UE::MovieScene::FPropertyTrackEntityImportHelperParamsImpl`  
`struct FPropertyTrackEntityImportHelperParamsImpl`  
_L302-315_
- L304 _public function_ `FPropertyTrackEntityImportHelperParamsImpl(TScriptInterface<IMovieSceneChannelOverrideProvider> InRegistryProvider) : RegistryProvider(InRegistryProvider)`
- L312 _public member_ `TScriptInterface<IMovieSceneChannelOverrideProvider> RegistryProvider;`
- L313 _public member_ `TObjectPtr<UMovieSceneSectionChannelOverrideRegistry> Registry;`
- L314 _public member_ `TArray<FChannelOverrideEntityImportParams> ImportParams;`

#### struct `UE::MovieScene::TPropertyTrackWithOverridableChannelsEntityImportHelperImpl`  
`template<typename... T> struct TPropertyTrackWithOverridableChannelsEntityImportHelperImpl`  
_L321-416_
- desc: Same as TPropertyTrackEntityImportHelperImpl but with support for overridable channels.
- L323 _public function_ `TPropertyTrackWithOverridableChannelsEntityImportHelperImpl(TEntityBuilder<T...>&& InBuilder, FPropertyTrackEntityImportHelperParamsImpl& InOverrideInfo, FComponentTypeID InPropertyTag = {}) : Builder(MoveTemp(InBuilder)) , OverrideInfo(InOverrideInfo) , PropertyTag(InPropertyTag)`
- L331 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, FChannelOverrideEntityImportParams OverrideParams)`
- L342 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition, FChannelOverrideEntityImportParams OverrideParams)`
- L352 _public function_ `void Commit(const UMovieSceneSection* InSection, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity)`
- L413 _protected member_ `TEntityBuilder<T...> Builder;`
- L414 _protected member_ `FPropertyTrackEntityImportHelperParamsImpl OverrideInfo;`
- L415 _protected member_ `FComponentTypeID PropertyTag;`
- L425 _public function_ `TPropertyTrackWithOverridableChannelsEntityImportHelperImpl(FComponentTypeID InPropertyTag, TScriptInterface<IMovieSceneChannelOverrideProvider> InRegistryProvider) : Builder(FEntityBuilder().AddTag(InPropertyTag)) , OverrideInfo(InRegistryProvider) , PropertyTag(InPropertyTag)`
- L433 _public function_ `template<typename U, typename PayloadType> TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<FAdd, TAddConditional<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, FChannelOverrideEntityImportParams OverrideParams)`
- L444 _public function_ `template<typename U, typename PayloadType> TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<FAdd, TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition, FChannelOverrideEntityImportParams OverrideParams)`
- L456 _protected member_ `TEntityBuilder<FAdd> Builder;`

#### struct `UE::MovieScene::TPropertyTrackWithOverridableChannelsEntityImportHelperImpl`  
`template<> struct TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<>`  
_L423-459_
- desc: The starting point for TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<...T>
- L323 _public function_ `TPropertyTrackWithOverridableChannelsEntityImportHelperImpl(TEntityBuilder<T...>&& InBuilder, FPropertyTrackEntityImportHelperParamsImpl& InOverrideInfo, FComponentTypeID InPropertyTag = {}) : Builder(MoveTemp(InBuilder)) , OverrideInfo(InOverrideInfo) , PropertyTag(InPropertyTag)`
- L331 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, FChannelOverrideEntityImportParams OverrideParams)`
- L342 _public function_ `template<typename U, typename PayloadType> TPropertyTrackEntityImportHelperImpl<T..., TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition, FChannelOverrideEntityImportParams OverrideParams)`
- L352 _public function_ `void Commit(const UMovieSceneSection* InSection, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity)`
- L413 _protected member_ `TEntityBuilder<T...> Builder;`
- L414 _protected member_ `FPropertyTrackEntityImportHelperParamsImpl OverrideInfo;`
- L415 _protected member_ `FComponentTypeID PropertyTag;`
- L425 _public function_ `TPropertyTrackWithOverridableChannelsEntityImportHelperImpl(FComponentTypeID InPropertyTag, TScriptInterface<IMovieSceneChannelOverrideProvider> InRegistryProvider) : Builder(FEntityBuilder().AddTag(InPropertyTag)) , OverrideInfo(InRegistryProvider) , PropertyTag(InPropertyTag)`
- L433 _public function_ `template<typename U, typename PayloadType> TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<FAdd, TAddConditional<U>> Add(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, FChannelOverrideEntityImportParams OverrideParams)`
- L444 _public function_ `template<typename U, typename PayloadType> TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<FAdd, TAddConditional<U>> AddConditional(TComponentTypeID<U> ComponentType, PayloadType&& InPayload, bool bCondition, FChannelOverrideEntityImportParams OverrideParams)`
- L456 _protected member_ `TEntityBuilder<FAdd> Builder;`

#### struct `UE::MovieScene::FPropertyTrackWithOverridableChannelsEntityImportHelper`  
`struct FPropertyTrackWithOverridableChannelsEntityImportHelper : TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<>`  
_L461-467_
- inherits: `TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<>`
- L464 _public function_ `template<typename PropertyTraits> FPropertyTrackWithOverridableChannelsEntityImportHelper(const TPropertyComponents<PropertyTraits>& PropertyComponents, TScriptInterface<IMovieSceneChannelOverrideProvider> InRegistryProvider) : TPropertyTrackWithOverridableChannelsEntityImportHelperImpl<>(PropertyComponents.PropertyTag, InRegistryProvider)`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MovieScene` (scope `UE`)
- L193 _namespace_ `namespace UE`
- L195 _namespace_ `namespace MovieScene` (scope `UE`)
- L393 _function_ `` (scope `UE::MovieScene::TPropertyTrackWithOverridableChannelsEntityImportHelperImpl::Commit`)

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneRotatorTrack.h` (Public)


#### class `UMovieSceneRotatorTrack`  
`class UMovieSceneRotatorTrack : public UMovieScenePropertyTrack`  
_L10-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Movie scene track that animates an FRotator property
- L15 _public prototype_ `UMovieSceneRotatorTrack(const FObjectInitializer& InObjectInitializer);`
- L18 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> InSectionClass) const override;`
- L19 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L20 _public prototype_ `virtual void AddSection(UMovieSceneSection& InSection) override;`
- L21 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L22 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& InSection) const override;`
- L23 _public prototype_ `virtual bool IsEmpty() const override;`
- L24 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L25 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& InSection) override;`
- L26 _public prototype_ `virtual void RemoveSectionAt(int32 InSectionIndex) override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneSkeletalAnimationTrack.h` (Public)


#### class `UMovieSceneSkeletalAnimationTrack`  
`class UMovieSceneSkeletalAnimationTrack : public UMovieSceneCommonAnimationTrack`  
_L18-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneCommonAnimationTrack`
- desc: Handles animation of skeletal mesh actors
- L26 _public prototype_ `TArray<UMovieSceneSection*> GetAnimSectionsAtTime(FFrameNumber Time);` — Gets the animation sections at a certain time
- L32 _public prototype_ `virtual void PostLoad() override;`
- L33 _public prototype_ `virtual bool PopulateEvaluationTree(TMovieSceneEvaluationTree<FMovieSceneTrackEvaluationData>& OutData) const override;`
- L34 _public prototype_ `virtual bool ShouldUseRootMotions() const override;`
- L37 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L43 _public member_ `bool bUseLegacySectionIndexBlend;` — `UPROPERTY()`
- L47 _public member_ `ESwapRootBone SwapRootBone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Setter,Getter, Category = "Root Motions")` — If on the root bone transform will be swapped to the specified root
- L50 _public prototype_ `void SetSwapRootBone(ESwapRootBone InValue);` — `UFUNCTION()`
- L52 _public prototype_ `ESwapRootBone GetSwapRootBone() const;` — `UFUNCTION()`
- L55 _public member_ `static FColor LinkedAnimSeqTrackColor;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneSlomoTrack.h` (Public)


#### class `UMovieSceneSlomoTrack`  
`class UMovieSceneSlomoTrack : public UMovieSceneFloatTrack`  
_L14-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneFloatTrack`
- desc: Implements a movie scene track that controls a movie scene's world time dilation.
- L21 _public prototype_ `UMovieSceneSlomoTrack(const FObjectInitializer& Init);`
- L25 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L26 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L29 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L30 _public function_ `virtual bool CanRename() const override`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneStringTrack.h` (Public)


#### class `UMovieSceneStringTrack`  
`class UMovieSceneStringTrack : public UMovieScenePropertyTrack`  
_L14-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Implements a movie scene track that holds a series of strings.
- L22 _public function_ `UMovieSceneStringTrack()` — Default constructor.
- L33 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L34 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L35 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L36 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L37 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L38 _public prototype_ `virtual bool IsEmpty() const override;`
- L39 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L40 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L41 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneTextTrack.h` (Public)


#### class `UMovieSceneTextTrack`  
`class UMovieSceneTextTrack : public UMovieScenePropertyTrack`  
_L10-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Movie Scene Track that holds a series of texts.
- L15 _public prototype_ `UMovieSceneTextTrack();`
- L18 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L19 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L20 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L21 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L22 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L23 _public prototype_ `virtual bool IsEmpty() const override;`
- L24 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L25 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L26 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneTransformTrack.h` (Public)


#### class `UMovieSceneTransformTrack`  
`class UMovieSceneTransformTrack : public UMovieScenePropertyTrack`  
_L16-27_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of 3D transform properties in a movie scene
- L25 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L26 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneVectorTrack.h` (Public)


#### class `UMovieSceneFloatVectorTrack`  
`class UMovieSceneFloatVectorTrack : public UMovieScenePropertyTrack`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of float vectors in a movie scene
- L21 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L22 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L24 _public prototype_ `virtual void InitializeFromProperty(const FProperty* Property, const UE::MovieScene::FPropertyDefinition* Definition) override;`
- L27 _public function_ `int32 GetNumChannelsUsed() const` — @return Get the number of channels used by the vector
- L30 _public function_ `void SetNumChannelsUsed( int32 InNumChannelsUsed )` — Set the number of channels used by the vector
- L35 _private member_ `int32 NumChannelsUsed;` — `UPROPERTY()` — The number of channels used by the vector (2,3, or 4)

#### class `UMovieSceneDoubleVectorTrack`  
`class UMovieSceneDoubleVectorTrack : public UMovieScenePropertyTrack`  
_L42-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of double vectors in a movie scene
- L48 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L49 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L51 _public prototype_ `virtual void InitializeFromProperty(const FProperty* Property, const UE::MovieScene::FPropertyDefinition* Definition) override;`
- L54 _public function_ `int32 GetNumChannelsUsed() const` — @return Get the number of channels used by the vector
- L57 _public function_ `void SetNumChannelsUsed( int32 InNumChannelsUsed )` — Set the number of channels used by the vector
- L62 _private member_ `int32 NumChannelsUsed;` — `UPROPERTY()` — The number of channels used by the vector (2,3, or 4)

### `Source/Runtime/MovieSceneTracks/Public/Tracks/MovieSceneVisibilityTrack.h` (Public)


#### class `UMovieSceneVisibilityTrack`  
`class UMovieSceneVisibilityTrack : public UMovieScenePropertyTrack`  
_L15-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack`
- desc: Handles manipulation of visibility properties in a movie scene
- L23 _public prototype_ `virtual void PostLoad() override;` — UMovieSceneTrack interface
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L26 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L29 _public prototype_ `virtual void ProcessSourceValueForKeying(const FProperty* Property, UE::MovieScene::FSourcePropertyValue& InOutValue) const override;`
- L33 _public prototype_ `virtual FText GetDisplayName() const override;`
