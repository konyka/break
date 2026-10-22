# Plugins / TemplateSequence

- module root: `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence`
- headers: 12; symbols: 260
- symbol kinds: class=18, delegate=1, enum=1, enumerator=3, function=22, macro=8, member=71, namespace=3, prototype=121, struct=7, typedef=5
- PublicDependencyModuleNames: CinematicCamera, Core, CoreUObject, Engine, LevelSequence, MovieScene, MovieSceneTracks, TimeManagement

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Private/Systems/TemplateSequenceSystem.h` (Private)


#### class `UTemplateSequenceSystem`  
`class UTemplateSequenceSystem : public UMovieSceneEntitySystem`  
_L13-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L18 _public prototype_ `UTemplateSequenceSystem(const FObjectInitializer& ObjInit);`
- L21 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L24 _private member_ `UE::MovieScene::FCachedEntityFilterResult_Match ApplicableFilter;`

#### class `UTemplateSequencePropertyScalingInstantiatorSystem`  
`class UTemplateSequencePropertyScalingInstantiatorSystem : public UMovieSceneEntitySystem`  
_L28-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L34 _public prototype_ `UTemplateSequencePropertyScalingInstantiatorSystem(const FObjectInitializer& ObjInit);`
- L36 _public function_ `bool HasAnyFloatScales() const`
- L37 _public function_ `bool HasAnyTransformScales() const`
- L41 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L45 _private typedef_ `using FPropertyScaledInstanceKey = TTuple<UE::MovieScene::FRootInstanceHandle, FMovieSceneSequenceID>;`
- L47 _private typedef_ `using FPropertyScaleEntityIDs = TArray<UE::MovieScene::FMovieSceneEntityID, TInlineAllocator<2>>;`
- L48 _private member_ `TMap<FPropertyScaledInstanceKey, FPropertyScaleEntityIDs> PropertyScaledInstances;`
- L50 _private member_ `int32 FloatScaleUseCount = 0;`
- L51 _private member_ `int32 TransformScaleUseCount = 0;`

#### class `UTemplateSequencePropertyScalingEvaluatorSystem`  
`class UTemplateSequencePropertyScalingEvaluatorSystem : public UMovieSceneEntitySystem`  
_L55-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L61 _public prototype_ `UTemplateSequencePropertyScalingEvaluatorSystem(const FObjectInitializer& ObjInit);`
- L63 _public typedef_ `using FPropertyScaleKey = TTuple<UE::MovieScene::FRootInstanceHandle, FMovieSceneSequenceID, FGuid, FName>;`
- L64 _public typedef_ `using FPropertyScaleValue = TTuple<ETemplateSectionPropertyScaleType, float>;`
- L66 _public typedef_ `using FPropertyScaleValueArray = TArray<FPropertyScaleValue, TInlineAllocator<2>>;`
- L68 _public prototype_ `void ResetPropertyScales();`
- L69 _public prototype_ `void AddPropertyScale(const FPropertyScaleKey& Key, const FPropertyScaleValue& Value);`
- L70 _public prototype_ `void FindPropertyScales(const FPropertyScaleKey& Key, FPropertyScaleValueArray& OutValues) const;`
- L74 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override final;`
- L75 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override final;`
- L84 _private member_ `TMap<FPropertyScaleKey, FMultiPropertyScaleValue> PropertyScales;`

#### struct `UTemplateSequencePropertyScalingEvaluatorSystem::FMultiPropertyScaleValue`  
`struct FMultiPropertyScaleValue`  
_L79-82_
- L81 _public member_ `FPropertyScaleValueArray Values;`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/CameraAnimationSequence.h` (Public)


#### class `UCameraAnimationSequence`  
`class UCameraAnimationSequence : public UTemplateSequence`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UTemplateSequence`
- desc: A template sequence specifically designed for playing on cameras.
- L19 _public prototype_ `UCameraAnimationSequence(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `virtual FText GetDisplayName() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/CameraAnimationSequencePlayer.h` (Public)


#### class `UCameraAnimationSequenceCameraStandIn`  
`class UCameraAnimationSequenceCameraStandIn : public UObject`  
_L17-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: A dummy class that we give to a sequence in lieu of an actual camera actor.
- L23 _public prototype_ `UCameraAnimationSequenceCameraStandIn(const FObjectInitializer& ObjInit);`
- L32 _public function_ `const FTransform& GetTransform() const` — Scene component properties Transform doesn't need to be a UPROPERTY because we register a custom getter/setter. This is because the sequence runtime expects that in order to use the intermediate transform struct.
- L33 _public function_ `void SetTransform(const FTransform& InTransform)`
- L37 _public member_ `float FieldOfView;` — `UPROPERTY()` — Camera component properties
- L40 _public member_ `uint8 bConstrainAspectRatio : 1;` — `UPROPERTY()`
- L43 _public member_ `float AspectRatio;` — `UPROPERTY()`
- L46 _public member_ `FPostProcessSettings PostProcessSettings;` — `UPROPERTY()`
- L49 _public member_ `float PostProcessBlendWeight;` — `UPROPERTY()`
- L53 _public member_ `FCameraFilmbackSettings Filmback;` — `UPROPERTY()` — Cine camera component properties
- L56 _public member_ `FCameraLensSettings LensSettings;` — `UPROPERTY()`
- L59 _public member_ `FCameraFocusSettings FocusSettings;` — `UPROPERTY()`
- L62 _public member_ `float CurrentFocalLength;` — `UPROPERTY()`
- L65 _public member_ `float CurrentAperture;` — `UPROPERTY()`
- L68 _public member_ `float CurrentFocusDistance;` — `UPROPERTY()`
- L72 _public prototype_ `void Initialize(UTemplateSequence* TemplateSequence);` — Initialize this object's properties based on the given sequence's root object template
- L75 _public prototype_ `void Reset(const FMinimalViewInfo& ViewInfo, UMovieSceneEntitySystemLinker* Linker);` — Reset the properties of the stand-in every frame before animation
- L78 _public prototype_ `void RecalcDerivedData();` — Recompute camera and lens settings after each frame
- L81 _private prototype_ `void ResetDefaultValues(const FMinimalViewInfo& ViewInfo);`
- L82 _private prototype_ `void UpdateInitialPropertyValues(UMovieSceneEntitySystemLinker* Linker);`
- L85 _private prototype_ `static void RegisterCameraStandIn();` — Register the stand-in class with the sequencer ECS component registry
- L87 _private prototype_ `static void UnregisterCameraStandIn();` — Unregister the stand-in class with the sequencer ECS component registry
- L90 _private member_ `static bool bRegistered;`
- L92 _private member_ `FTransform Transform;`
- L94 _private member_ `bool bIsCineCamera = false;`
- L95 _private member_ `float WorldToMeters = 0.f;`

#### class `UCameraAnimationSequencePlayer`  
`class UCameraAnimationSequencePlayer : public UObject , public IMovieScenePlayer`  
_L104-236_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IMovieScenePlayer`
- desc: A lightweight sequence player for playing camera animation sequences.
- L111 _public prototype_ `UCameraAnimationSequencePlayer(const FObjectInitializer& ObjInit);`
- L112 _public prototype_ `virtual ~UCameraAnimationSequencePlayer();`
- L121 _public prototype_ `void Initialize(UMovieSceneSequence* InSequence, int32 StartOffset = 0, float DurationOverride = 0.f);` — Initializes this player with the given sequence @param InSequence    The sequence to play @param StartOffset   The offset to start at, in frames (display rate) @param DurationOverride  A duration to use instead of the natural duration of the sequence
- L127 _public prototype_ `bool IsValid() const;` — Returns whether this player is still valid. It could be forcibly torn-down if the camera animation subsystem was destroyed with the world.
- L138 _public prototype_ `void Play(bool bLoop = false, bool bRandomStartTime = false);` — Start playing the sequence @param bLoop              Whether to loop playback @param bRandomStartTime   Whether to start at a random time inside the playback range Note that if StartOffset was set, the random start time will be chosen within the reduced (offset) playback range.
- L145 _public prototype_ `void Update(FFrameTime NewPosition);` — Advance play to the given time @param NewPosition   The time to advance to, in ticks
- L152 _public prototype_ `void Jump(FFrameTime NewPosition);` — Jumps to the given time, in ticks @param New Position   The time to jump to, in ticks
- L155 _public prototype_ `void Stop();` — Stop playing the sequence
- L158 _public function_ `bool GetIsLooping() const` — Gets whether playback is looping
- L160 _public function_ `FFrameRate GetInputRate() const` — Get the sequence display rate
- L162 _public function_ `FFrameRate GetOutputRate() const` — Get the sequence tick resolution
- L164 _public function_ `FFrameNumber GetStartFrame() const` — Get the start frame of the current sequence
- L166 _public prototype_ `FFrameTime GetDuration() const;` — Get the duration of the current sequence in frames (display rate)
- L168 _public prototype_ `FFrameTime GetCurrentPosition() const;` — Gets the current play position in frames (display rate)
- L171 _public prototype_ `void SetBoundObjectOverride(UObject* InObject);` — Sets an object that can be used to bind everything in the sequence
- L176 _public function_ `virtual FMovieSceneRootEvaluationTemplateInstance& GetEvaluationTemplate() override` — IMovieScenePlayer interface
- L177 _public prototype_ `virtual UMovieSceneEntitySystemLinker* ConstructEntitySystemLinker() override;`
- L178 _public prototype_ `virtual EMovieScenePlayerStatus::Type GetPlaybackStatus() const override;`
- L179 _public function_ `virtual UObject* AsUObject() override`
- L180 _public function_ `virtual FMovieSceneSpawnRegister& GetSpawnRegister() override`
- L182 _public function_ `virtual void SetPlaybackStatus(EMovieScenePlayerStatus::Type InPlaybackStatus) override`
- L183 _public function_ `virtual void SetViewportSettings(const TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) override`
- L184 _public function_ `virtual void GetViewportSettings(TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) const override`
- L185 _public function_ `virtual bool CanUpdateCameraCut() const override`
- L186 _public function_ `virtual void UpdateCameraCut(UObject* CameraObject, const EMovieSceneCameraCutParams& CameraCutParams) override`
- L189 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L193 _protected prototype_ `virtual void ResolveBoundObjects(UE::UniversalObjectLocator::FResolveParams& ResolveParams, const FGuid& InBindingId, FMovieSceneSequenceID SequenceID, UMovieSceneSequence& Sequence, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L195 _protected prototype_ `void OnAbandonLinker(UMovieSceneEntitySystemLinker* InLinker);`
- L199 _private member_ `FSequenceCameraShakeSpawnRegister SpawnRegister;`
- L203 _private member_ `TObjectPtr<UObject> BoundObjectOverride;` — `UPROPERTY(transient)` — Bound object overrides
- L207 _private member_ `TObjectPtr<UMovieSceneSequence> Sequence;` — `UPROPERTY(transient)` — The sequence to play back
- L211 _private member_ `FMovieSceneRootEvaluationTemplateInstance RootTemplateInstance;` — `UPROPERTY(transient)` — The evaluation template instance
- L214 _private member_ `FMovieScenePlaybackPosition PlayPosition;` — Play position helper
- L217 _private member_ `FFrameNumber StartFrame;` — Start frame for the sequence
- L220 _private member_ `FFrameTime DurationFrames;` — The sequence duration in frames
- L223 _private member_ `FFrameTime TotalDurationFrames;` — The total duration we need to play
- L226 _private member_ `uint16 LoopsPlayed = 0;` — Accumulated number of loops played so far
- L229 _private member_ `bool bIsLooping = false;` — Whether we should be looping
- L232 _private member_ `bool bDurationRequiresLooping = false;` — Whether we need to loop due to a duration override
- L235 _private member_ `TEnumAsByte<EMovieScenePlayerStatus::Type> Status;` — Movie player status.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/CameraAnimationSequenceSubsystem.h` (Public)


#### class `UCameraAnimationSpawnableSystem`  
`class UCameraAnimationSpawnableSystem : public UMovieSceneEntitySystem`  
_L14-25_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystem`
- L19 _public prototype_ `UCameraAnimationSpawnableSystem(const FObjectInitializer& ObjInit);`
- L21 _public prototype_ `void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents);`
- L24 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const;`

#### class `UCameraAnimationBoundObjectInstantiator`  
`class UCameraAnimationBoundObjectInstantiator : public UMovieSceneEntityInstantiatorSystem`  
_L28-39_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- L33 _public prototype_ `UCameraAnimationBoundObjectInstantiator(const FObjectInitializer& ObjInit);`
- L35 _public prototype_ `void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents);`
- L38 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const;`

#### class `UCameraAnimationEntitySystemLinker`  
`class UCameraAnimationEntitySystemLinker : public UMovieSceneEntitySystemLinker`  
_L42-48_
- reflection: `UCLASS()`
- inherits: `UMovieSceneEntitySystemLinker`
- L47 _public prototype_ `UCameraAnimationEntitySystemLinker(const FObjectInitializer& ObjInit);`

#### class `UCameraAnimationSequenceSubsystem`  
`class UCameraAnimationSequenceSubsystem : public UWorldSubsystem`  
_L54-92_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- desc: World subsystem that holds global objects for handling camera animation sequences.
- L60 _public prototype_ `static UCameraAnimationSequenceSubsystem* GetCameraAnimationSequenceSubsystem(const UWorld* InWorld);` — Get the camera animation sequence subsystem for the given world
- L63 _public prototype_ `static UMovieSceneEntitySystemLinker* CreateLinker(UObject* Outer, FName Name);` — Create a new linker setup for handling camera animation sequences
- L66 _public prototype_ `static UE::MovieScene::EEntitySystemCategory GetCameraAnimationSystemCategory();` — Gets the system category for camera animation specific systems
- L69 _public prototype_ `UCameraAnimationSequenceSubsystem();` — Construct a new camera animation sequence subsystem
- L71 _public prototype_ `virtual ~UCameraAnimationSequenceSubsystem();` — Destroy the camera animation sequence subsystem
- L74 _public prototype_ `UMovieSceneEntitySystemLinker* GetLinker(bool bAutoCreate = true);` — Gets the Sequencer linker owned by this sybsystem
- L77 _public prototype_ `TSharedPtr<FMovieSceneEntitySystemRunner> GetRunner() const;` — Get's this subsystem's camera anim runner
- L81 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L82 _private prototype_ `virtual void Deinitialize() override;`
- L88 _private member_ `TObjectPtr<UMovieSceneEntitySystemLinker> Linker;` — `UPROPERTY(transient)` — The global Sequencer linker that contains all the shakes and camera animations
- L91 _private member_ `TSharedPtr<FMovieSceneEntitySystemRunner> Runner;` — The global Sequencer runner that runs all the shakes and camera animations

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/Sections/TemplateSequenceSection.h` (Public)


#### enum `ETemplateSectionPropertyScaleType`  
`enum class ETemplateSectionPropertyScaleType`  
_L18-26_
- reflection: `UENUM()`
- desc: Defines the type of property scaling for a template sequence.
- L21 _public enumerator_ `FloatProperty` — Scales a float property
- L23 _public enumerator_ `TransformPropertyLocationOnly` — Scales the location channels (X, Y, Z) of a transform property
- L25 _public enumerator_ `TransformPropertyRotationOnly` — Scales the rotation channels (yaw, pitch, roll) of a transform property

#### struct `FTemplateSectionPropertyScale`  
`struct FTemplateSectionPropertyScale`  
_L32-47_
- reflection: `USTRUCT()`
- desc: Defines a property scaling for a template sequence.
- L37 _public member_ `FGuid ObjectBinding;` — `UPROPERTY()`
- L40 _public member_ `FMovieScenePropertyBinding PropertyBinding;` — `UPROPERTY()`
- L43 _public member_ `ETemplateSectionPropertyScaleType PropertyScaleType= ETemplateSectionPropertyScaleType::FloatProperty;` — `UPROPERTY()`
- L46 _public member_ `FMovieSceneFloatChannel FloatChannel;` — `UPROPERTY()`

#### class `UTemplateSequenceSection`  
`class UTemplateSequenceSection : public UMovieSceneSubSection`  
_L53-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSubSection`
- desc: Defines the section for a template sequence track.
- L60 _public prototype_ `UTemplateSequenceSection(const FObjectInitializer& ObjInitializer);`
- L62 _public prototype_ `void AddPropertyScale(const FTemplateSectionPropertyScale& InPropertyScale);`
- L63 _public prototype_ `void RemovePropertyScale(int32 InIndex);`
- L66 _public prototype_ `virtual bool ShowCurveForChannel(const void *Channel) const override;` — UMovieSceneSection interface
- L67 _public prototype_ `virtual void OnDilated(float DilationFactor, FFrameNumber Origin) override;`
- L71 _protected prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L73 _protected prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L74 _protected prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const UE::MovieScene::FEntityImportParams& Params, UE::MovieScene::FImportedEntity* OutImportedEntity) override;`
- L77 _protected prototype_ `virtual void PostInitProperties() override;` — ~ UObject implementation
- L82 _public member_ `TArray<FTemplateSectionPropertyScale> PropertyScales;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/SequenceCameraShake.h` (Public)


#### class `USequenceCameraShakePattern`  
`class USequenceCameraShakePattern : public UCameraShakePattern`  
_L21-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCameraShakePattern`
- desc: A camera shake pattern that plays a sequencer animation.
- L27 _public prototype_ `USequenceCameraShakePattern(const FObjectInitializer& ObjInit);`
- L33 _public member_ `TObjectPtr<class UCameraAnimationSequence> Sequence;` — `UPROPERTY(EditAnywhere, Category=CameraShake)` — Source camera animation sequence to play.
- L37 _public member_ `float PlayRate;` — `UPROPERTY(EditAnywhere, Category=CameraShake, meta=(ClampMin="0.001"))` — Scalar defining how fast to play the anim.
- L41 _public member_ `float Scale;` — `UPROPERTY(EditAnywhere, Category=CameraShake, meta=(ClampMin="0.0"))` — Scalar defining how "intense" to play the anim.
- L45 _public member_ `float BlendInTime;` — `UPROPERTY(EditAnywhere, Category=CameraShake, meta=(ClampMin="0.0"))` — Linear blend-in time.
- L49 _public member_ `float BlendOutTime;` — `UPROPERTY(EditAnywhere, Category=CameraShake, meta=(ClampMin="0.0"))` — Linear blend-out time.
- L53 _public member_ `float RandomSegmentDuration;` — `UPROPERTY(EditAnywhere, Category=CameraShake, meta=(ClampMin="0.0", EditCondition="bRandomSegment"))` — When bRandomSegment is true, defines how long the sequence should play.
- L62 _public member_ `bool bRandomSegment;` — `UPROPERTY(EditAnywhere, Category=CameraShake)` — When true, plays a random snippet of the sequence for RandomSegmentDuration seconds. @note The sequence we be forced to loop when bRandomSegment is enabled, in case the duration is longer than what's left to play from the random start time.
- L67 _private prototype_ `virtual void GetShakePatternInfoImpl(FCameraShakeInfo& OutInfo) const override;` — UCameraShakeBase interface
- L68 _private prototype_ `virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;`
- L69 _private prototype_ `virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L70 _private prototype_ `virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;`
- L71 _private prototype_ `virtual bool IsFinishedImpl() const override;`
- L72 _private prototype_ `virtual void StopShakePatternImpl(const FCameraShakePatternStopParams& Params) override;`
- L73 _private prototype_ `virtual void TeardownShakePatternImpl() override;`
- L75 _private prototype_ `void UpdateCamera(FFrameTime NewPosition, const FMinimalViewInfo& InPOV, FCameraShakePatternUpdateResult& OutResult);`
- L81 _private member_ `TObjectPtr<UCameraAnimationSequencePlayer> Player;` — `UPROPERTY(Instanced, Transient)` — The player we use to play the camera animation sequence
- L85 _private member_ `TObjectPtr<UCameraAnimationSequenceCameraStandIn> CameraStandIn;` — `UPROPERTY(Instanced, Transient)` — Standin for the camera actor and components
- L88 _private member_ `FCameraShakeState State;` — State tracking

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/TemplateSequence.h` (Public)


#### class `UTemplateSequence`  
`class UTemplateSequence : public UMovieSceneSequence`  
_L17-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneSequence`
- desc: Movie scene animation that can be instanced multiple times inside a level sequence.
- L22 _public prototype_ `UTemplateSequence(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `void Initialize();`
- L27 _public prototype_ `FGuid GetRootObjectBindingID() const;` — Gets the object binding that corresponds to the root spawnable that serves as the template.
- L30 _public prototype_ `const UObject* GetRootObjectSpawnableTemplate() const;` — Gets the root spawnable object template.
- L33 _public prototype_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override;`
- L34 _public prototype_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override;`
- L35 _public prototype_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L36 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L37 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L38 _public prototype_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override;`
- L39 _public prototype_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override;`
- L40 _public prototype_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override;`
- L42 _public prototype_ `virtual FGuid CreatePossessable(UObject* ObjectToPossess) override;`
- L43 _public prototype_ `virtual bool AllowsSpawnableObjects() const override;`
- L45 _public prototype_ `virtual UObject* MakeSpawnableTemplateFromInstance(UObject& InSourceObject, FName ObjectName) override;`
- L47 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L49 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L52 _public prototype_ `virtual FText GetDisplayName() const override;`
- L54 _public prototype_ `virtual ETrackSupport IsTrackSupportedImpl(TSubclassOf<class UMovieSceneTrack> InTrackClass) const override;`
- L55 _public prototype_ `virtual void GetAssetRegistryTagMetadata(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L57 _protected prototype_ `virtual void ThreadedPostLoadAssetRegistryTagsOverride(FPostLoadAssetRegistryTagsContext& Context) const;`
- L62 _private prototype_ `FGuid FindOrAddBinding(UObject* ObjectToPossess);`
- L67 _public member_ `TObjectPtr<UMovieScene> MovieScene;` — `UPROPERTY()`
- L70 _public member_ `TSoftClassPtr<AActor> BoundActorClass;` — `UPROPERTY()`
- L73 _public member_ `TMap<FGuid, FName> BoundActorComponents;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEMPLATESEQUENCE_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTemplateSequence, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTemplateSequence, Log, All);`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/TemplateSequenceActor.h` (Public)


#### struct `FTemplateSequenceBindingOverrideData`  
`struct FTemplateSequenceBindingOverrideData`  
_L24-40_
- reflection: `USTRUCT(BlueprintType)`
- desc: Template sequence binding override data This is similar to FMovieSceneBindingOverrideData, but works only for a template sequence's root object, so we don't need it to store the object binding ID.
- L28 _public function_ `FTemplateSequenceBindingOverrideData() : bOverridesDefault(true)`
- L35 _public member_ `TWeakObjectPtr<UObject> Object;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Specifies the object binding to override.
- L39 _public member_ `bool bOverridesDefault;` — `UPROPERTY(EditAnywhere, Category = "Binding")` — Specifies whether the default assignment should remain bound (false) or if this should completely override the default binding (true).

#### class `ATemplateSequenceActor`  
`class ATemplateSequenceActor : public AActor , public IMovieScenePlaybackClient`  
_L46-137_
- reflection: `UCLASS(MinimalAPI, hideCategories = (Rendering, Physics, LOD, Activation, Input))`
- inherits: `AActor,IMovieScenePlaybackClient`
- desc: Actor responsible for controlling a specific template sequence in the world.
- L54 _public prototype_ `ATemplateSequenceActor(const FObjectInitializer& ObjectInitializer);`
- L59 _public member_ `FMovieSceneSequencePlaybackSettings PlaybackSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Playback", meta = (ShowOnlyInnerProperties))`
- L62 _public member_ `TObjectPtr<UTemplateSequencePlayer> SequencePlayer;` — `UPROPERTY(Instanced, Transient, Replicated, BlueprintReadOnly, BlueprintGetter = GetSequencePlayer, Category = "Playback", meta = (ExposeFunctionCategories = "Sequencer|Player"))`
- L65 _public member_ `FSoftObjectPath TemplateSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General", meta = (AllowedClasses = "/Script/TemplateSequence.TemplateSequence"))`
- L69 _public member_ `FTemplateSequenceBindingOverrideData BindingOverride;` — `UPROPERTY(BlueprintReadOnly, Category = "General")` — The override for the template sequence's root object binding. See SetBinding.
- L79 _public prototype_ `UTemplateSequence* GetSequence() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the template sequence being played by this actor. @return the template sequence, or nullptr if it is not assigned or cannot be loaded
- L87 _public prototype_ `UTemplateSequence* LoadSequence() const;` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Get the template sequence being played by this actor. @return the template sequence, or nullptr if it is not assigned or cannot be loaded
- L93 _public prototype_ `void SetSequence(UTemplateSequence* InSequence);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player")` — Set the template sequence being played by this actor.
- L99 _public prototype_ `UTemplateSequencePlayer* GetSequencePlayer() const;` — `UFUNCTION(BlueprintGetter)` — Get the actor's sequence player, or nullptr if it not yet initialized.
- L106 _public prototype_ `void SetBinding(AActor* Actor, bool bOverridesDefault = true);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player|Bindings")` — Set the actor to play the template sequence onto, by setting up an override for the template sequence's root object binding.
- L111 _protected prototype_ `virtual bool RetrieveBindingOverrides(const FGuid& InBindingId, FMovieSceneSequenceID InSequenceID, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override;`
- L112 _protected prototype_ `virtual UObject* GetInstanceData() const override;`
- L116 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L117 _protected prototype_ `virtual void BeginPlay() override;`
- L118 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L122 _protected prototype_ `virtual void PostInitProperties() override;`
- L123 _protected prototype_ `virtual void PostLoad() override;`
- L128 _public prototype_ `void InitializePlayer();`
- L131 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L136 _private prototype_ `void OnSequenceLoaded(const FName& PackageName, UPackage* Package, EAsyncLoadingResult::Type Result);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEMPLATESEQUENCE_API`
- L13 _namespace_ `namespace EEndPlayReason`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/TemplateSequenceComponentTypes.h` (Public)


#### struct `UE::MovieScene::FTemplateSequenceComponentData`  
`struct FTemplateSequenceComponentData`  
_L19-22_
- desc: Component data for how a template sequence should remap its object bindings to that of a parent object binding
- L21 _public member_ `FMovieSceneEvaluationOperand InnerOperand;`

#### struct `UE::MovieScene::FTemplateSequencePropertyScaleComponentData`  
`struct FTemplateSequencePropertyScaleComponentData`  
_L25-35_
- desc: Component data for what property to scale inside a template sequence
- L28 _public member_ `FMovieSceneSequenceID SubSequenceID;` — Sequence ID where the property track lives
- L30 _public member_ `FGuid ObjectBinding;` — The object binding ID of the object for which to scale the given property
- L32 _public member_ `FMovieScenePropertyBinding PropertyBinding;` — The property to scale
- L34 _public member_ `ETemplateSectionPropertyScaleType PropertyScaleType;` — The type of property scaling to do

#### struct `UE::MovieScene::FTemplateSequenceComponentTypes`  
`struct FTemplateSequenceComponentTypes`  
_L37-53_
- L40 _public prototype_ `static FTemplateSequenceComponentTypes* Get();`
- L42 _public member_ `TComponentTypeID<FTemplateSequenceComponentData> TemplateSequence;`
- L43 _public member_ `TComponentTypeID<FTemplateSequencePropertyScaleComponentData> PropertyScale;`
- L44 _public member_ `TComponentTypeID<FGuid> PropertyScaleReverseBindingLookup;`
- L49 _public member_ `} Tags;`
- L52 _private prototype_ `FTemplateSequenceComponentTypes();`

#### struct `UE::MovieScene::FTemplateSequenceComponentTypes::(anonymous)`  
``  
_L47-49_

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieScene` (scope `UE`)
- L48 _member_ `FComponentTypeID IsPropertyScaled;` (scope `UE::MovieScene::FTemplateSequenceComponentTypes::__anonb4f8d56d0108`)

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/TemplateSequencePlayer.h` (Public)


#### class `UTemplateSequencePlayer`  
`class UTemplateSequencePlayer : public UMovieSceneSequencePlayer`  
_L17-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMovieSceneSequencePlayer`
- L23 _public prototype_ `UTemplateSequencePlayer(const FObjectInitializer&);`
- L28 _public prototype_ `static UTemplateSequencePlayer* CreateTemplateSequencePlayer(UObject* WorldContextObject, UTemplateSequence* TemplateSequence, FMovieSceneSequencePlaybackSettings Settings, ATemplateSequenceActor*& OutActor);` — `UFUNCTION(BlueprintCallable, Category = "Sequencer|Player", meta = (WorldContext = "WorldContextObject", DynamicOutputParam = "OutActor"))`
- L32 _public prototype_ `void Initialize(UMovieSceneSequence* InSequence, UWorld* InWorld, const FMovieSceneSequencePlaybackSettings& InSettings);`
- L35 _public prototype_ `virtual UObject* GetPlaybackContext() const override;` — IMovieScenePlayer interface
- L40 _private member_ `TWeakObjectPtr<UWorld> World;` — The world this player will spawn actors in, if needed.

#### class `FSequenceCameraShakeSpawnRegister`  
`class FSequenceCameraShakeSpawnRegister : public FMovieSceneSpawnRegister`  
_L46-60_
- inherits: `FMovieSceneSpawnRegister`
- desc: A spawn register that accepts a "wildcard" object.
- L49 _public function_ `void SetSpawnedObject(UObject* InObject)`
- L51 _public function_ `virtual UObject* SpawnObject(FMovieSceneSpawnable&, FMovieSceneSequenceIDRef, TSharedRef<const UE::MovieScene::FSharedPlaybackState>) override`
- L52 _public function_ `virtual void DestroySpawnedObject(UObject&, UMovieSceneSpawnableBindingBase* CustomSpawnableBinding) override`
- L55 _public function_ `virtual bool CanSpawnObject(UClass* InClass) const override`
- L59 _private member_ `FWeakObjectPtr SpawnedObject;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/TemplateSequenceSpawnRegister.h` (Public)


#### class `FTemplateSequenceSpawnRegister`  
`class FTemplateSequenceSpawnRegister : public FLevelSequenceSpawnRegister`  
_L10-15_
- inherits: `FLevelSequenceSpawnRegister`
- desc: Movie scene spawn register that knows how to handle spawning objects (actors) for a template sequence
- L14 _public prototype_ `FTemplateSequenceSpawnRegister();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEMPLATESEQUENCE_API`

### `Plugins/MovieScene/TemplateSequence/Source/TemplateSequence/Public/Tracks/TemplateSequenceTrack.h` (Public)


#### class `UTemplateSequenceTrack`  
`class UTemplateSequenceTrack : public UMovieSceneSubTrack`  
_L13-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSubTrack`
- L19 _public prototype_ `UTemplateSequenceTrack(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual UMovieSceneSection* AddNewTemplateSequenceSection(FFrameNumber KeyTime, UTemplateSequence* InSequence);`
- L24 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L25 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L28 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _private function_ `static uint16 GetEvaluationPriority()` — One more than spawn tracks.
