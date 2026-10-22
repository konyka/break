# Plugins / MovieSceneAnimMixer

- module root: `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer`
- headers: 37; symbols: 840
- symbol kinds: class=31, delegate=1, enum=12, enumerator=37, externvar=2, function=92, macro=1, member=291, namespace=18, prototype=297, struct=56, typedef=2
- PrivateDependencyModuleNames: EditorFramework, MovieSceneTracks, Settings, UnrealEd
- PublicDependencyModuleNames: AnimGraphRuntime, Core, CoreUObject, DeveloperSettings, Engine, MovieScene, MovieSceneTracks, SlateCore, UAF, UAFAnimGraph, UAFMirroring

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimMixerBakeEvaluation.h` (Public)


#### struct `UE::MovieScene::AnimMixerBakeEvaluation::FBakeFilter`  
`struct FBakeFilter`  
_L22-48_
- desc: Filter for controlling which mixer entries are included during bake evaluation.
- L25 _public member_ `TSet<FObjectKey> IncludeOnlySections;` — If non-empty, only include entries whose EntityOwner matches
- L28 _public member_ `TSet<FObjectKey> ExcludeSections;` — Entries whose EntityOwner matches are excluded
- L31 _public member_ `int32 MinPriority = -1;` — If >= 0, only entries with priority >= this value are included
- L34 _public member_ `int32 MaxPriority = -1;` — If >= 0, only entries with priority <= this value are included
- L39 _public member_ `bool bSkipRootMotionConversion = false;` — When true, the ConvertRootMotionToWorldSpaceTask is omitted from the evaluation program. The resulting RootMotionTransform will be in animation space rather than world space.
- L43 _public member_ `TSharedPtr<FTransform> CaptureAnimSpaceRoot;` — When set, the conversion task writes the pre-conversion animation-space root here. Populated automatically by FBakeEvaluationScope.
- L47 _public member_ `TSharedPtr<FTransform> CaptureAnimSpaceAccumulated;` — When set, the conversion task writes the accumulated/initial-root transform the offset is applied relative to here. Populated automatically by FBakeEvaluationScope.

#### struct `UE::MovieScene::AnimMixerBakeEvaluation::FBakeResult`  
`struct FBakeResult`  
_L50-61_
- L52 _public member_ `FFrameTime Time;`
- L53 _public member_ `FTransform RootMotionTransform = FTransform::Identity;`
- L54 _public member_ `FTransform AnimationSpaceRootMotion = FTransform::Identity;`
- L55 _public member_ `FTransform AnimSpaceAccumulatedTransform = FTransform::Identity;`
- L56 _public member_ `UE::UAF::FLODPoseHeap Pose;`
- L57 _public member_ `FBlendedHeapCurve Curves;`
- L58 _public member_ `UE::Anim::FHeapAttributeContainer Attributes;`
- L60 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MovieScene` (scope `UE`)
- L18 _namespace_ `namespace AnimMixerBakeEvaluation` (scope `UE::MovieScene`)
- L66 _prototype_ `FBakeResult EvaluateAtTime( UMovieSceneEntitySystemLinker* Linker, FInstanceHandle InstanceHandle, UMovieSceneAnimationMixerTrack* MixerTrack, FFrameTime Time, const FBakeFilter& Filter = {});` (scope `UE::MovieScene::AnimMixerBakeEvaluation`) — Evaluate the mixer at a single time, capturing results through the bake target system. Temporarily swaps the track's target, sets a bake filter on the mixer system, then re-evaluates the ECS and restores original state.
- L76 _prototype_ `TArray<FBakeResult> EvaluateRange( UMovieSceneEntitySystemLinker* Linker, FInstanceHandle InstanceHandle, UMovieSceneAnimationMixerTrack* MixerTrack, FFrameTime StartTime, FFrameTime FrameStep, int32 NumSamples, const FBakeFilter& Filter = {});` (scope `UE::MovieScene::AnimMixerBakeEvaluation`) — Evaluate the mixer at regular intervals from StartTime (inclusive) for NumSamples. More efficient than calling EvaluateAtTime in a loop because save/restore only happens once around the entire batch.

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimMixerBoneMatching.h` (Public)


#### struct `UE::MovieScene::AnimMixerBoneMatching::FBoneMatchingContext`  
`struct FBoneMatchingContext`  
_L20-28_
- L22 _public member_ `UMovieSceneEntitySystemLinker* Linker = nullptr;`
- L23 _public member_ `FInstanceHandle InstanceHandle;`
- L24 _public member_ `UMovieSceneAnimationMixerTrack* MixerTrack = nullptr;`
- L27 _public member_ `FFrameTime CurrentTime;` — Sequencer playhead time, used when MatchTimeMode == AtCurrentTime

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MovieScene` (scope `UE`)
- L17 _namespace_ `namespace AnimMixerBoneMatching` (scope `UE::MovieScene`)
- L37 _prototype_ `FMovieSceneBoneMatchData ComputeBoneMatch( UMovieSceneSection* TargetSection, const FMovieSceneBoneMatchData& Settings, const FBoneMatchingContext& Context);` (scope `UE::MovieScene::AnimMixerBoneMatching`) — Compute the bone match transform for a target section. Evaluates the ECS at the resolved match time to get both the underlying pose (everything except the target, capped at the target's priority) and the target section's isolated pose, then computes the selective per-axis match offset between them. Returns a copy of Settings with MatchTransform, bIsValid, and bIsDirty updated.
- L47 _prototype_ `bool DoesSectionAffectBoneMatch( UMovieSceneSection* UpdatedSection, UMovieSceneSection* Other, FFrameNumber MatchKeyTime, UMovieSceneSection* OtherReferenceSection);` (scope `UE::MovieScene::AnimMixerBoneMatching`) — Returns true when an edit to UpdatedSection could affect Other's bone match transform. Considers UpdatedSection's row index (must sit at or below Other's, to fall within ComputeBoneMatch's underlying-pose filter) and its start frame relative to MatchKeyTime. Always returns true when UpdatedSection is Other's explicit ReferenceSection.
- L56 _prototype_ `void PropagateRematch( UMovieSceneSection* UpdatedSection, const FBoneMatchingContext& Context, TSet<UMovieSceneSection*>& Visited);` (scope `UE::MovieScene::AnimMixerBoneMatching`) — Propagate bone match rebakes from UpdatedSection to every bone-matched section on the mixer track whose underlying pose depends on it. Recurses through the dependency chain using Visited to prevent cycles.

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimMixerBusUtils.h` (Public)


#### struct `FBusDependencyGraph`  
`struct FBusDependencyGraph`  
_L12-32_
- desc: Dependency graph for bus-target mixers. Callers populate Nodes, then call TopologicalSort or IsReachable.
- L24 _public member_ `TArray<FNode> Nodes;`
- L28 _public prototype_ `TArray<int32> TopologicalSort();` — Kahn's algorithm. Returns sorted node indices; nodes in cycles keep InDegree > 0 and are excluded. Self-references are skipped.
- L31 _public prototype_ `bool IsReachable(FName StartBus, FName TargetBus) const;` — True if TargetBus is reachable from StartBus through dependency edges.

#### struct `FBusDependencyGraph::FNode`  
`struct FNode`  
_L14-22_
- L16 _public member_ `FName WritesToBus;`
- L17 _public member_ `TArray<FName> ReadsFromBuses;`
- L20 _public member_ `int32 InDegree = 0;` — Set by TopologicalSort
- L21 _public member_ `TArray<int32> Dependents;`

#### struct `FAnimMixerBusValidationResult`  
`struct FAnimMixerBusValidationResult`  
_L34-42_
- L36 _public member_ `TArray<FString> Errors;`
- L37 _public member_ `TArray<FString> Warnings;`
- L39 _public function_ `bool HasErrors() const`
- L40 _public function_ `bool HasWarnings() const`
- L41 _public function_ `bool IsClean() const`

#### struct `FAnimMixerBusUtils`  
`struct FAnimMixerBusUtils`  
_L46-65_
- desc: Bus topology utilities. Functions that take mixer tracks expect all tracks for a single bound object.
- L49 _public prototype_ `static TArray<FName> GatherBusNamesFromSequence(UMovieSceneSequence* RootSequence);` — Gather all bus names across the sequence hierarchy
- L53 _public prototype_ `static TArray<FName> ComputeBusEvaluationOrder(TArrayView<UMovieSceneAnimationMixerTrack* const> MixerTracks);` — Build a dependency graph from mixer tracks and return topologically sorted bus names. Cyclic buses are excluded (with an ensure).
- L56 _public prototype_ `static FAnimMixerBusValidationResult ValidateBusTopology(TArrayView<UMovieSceneAnimationMixerTrack* const> MixerTracks);` — Validate bus topology: cycles, self-references, duplicate writers, orphans.
- L59 _public prototype_ `static bool WouldBusSectionCreateCycle(FName BusName, UMovieSceneAnimationMixerTrack* Track, TArrayView<UMovieSceneAnimationMixerTrack* const> MixerTracks);` — Would adding a bus section reading BusName to Track create a cycle?
- L63 _public prototype_ `static bool WouldBusTargetCreateCycle(FName BusName, UMovieSceneAnimationMixerTrack* Track, TArrayView<UMovieSceneAnimationMixerTrack* const> MixerTracks);` — Would setting Track's target to BusName create a cycle?

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimMixerComponentTypes.h` (Public)


#### struct `FLayerBlendTaskBuilder`  
`struct FLayerBlendTaskBuilder`  
_L27-39_
- desc: Builder for layer-level blend tasks. Stored as an ECS component on entities produced by blend type systems (e.g., the mask system). Called by the mixer at evaluation time with the computed layer weight.
- L29 _public member_ `TFunction<TSharedPtr<FAnimNextEvaluationTask>(double LayerWeight)> BuildTask;`
- L35 _public member_ `float MaskMaxBoneWeight = 1.0f;` — Maximum mask passthrough across all bones in the layer's accumulated mask, in [0,1]. 1.0 = at least one bone fully exposes the layer (or no mask at all); 0.0 = fully masked out. Used by the mixer's anim-notify exposure pass to decide how much a layer suppresses notifies from lower layers.
- L37 _public function_ `bool IsValid() const`
- L38 _public function_ `TSharedPtr<FAnimNextEvaluationTask> Build(double LayerWeight) const`

#### struct `UE::MovieScene::FAnimMixerComponentTypes`  
`struct FAnimMixerComponentTypes`  
_L43-92_
- L45 _public prototype_ `static FAnimMixerComponentTypes* Get();`
- L46 _public prototype_ `static void Destroy();`
- L49 _public member_ `static const UE::Anim::FAttributeId RootTransformAttributeId;` — A root motion transform in animation space to be applied (after space conversion)
- L50 _public member_ `static const UE::Anim::FAttributeId RootTransformWeightAttributeId;`
- L53 _public member_ `static const UE::Anim::FAttributeId RootTransformIsAuthoritativeAttributeId;` — Internal flag marking a section as authoritative source of root motion. Some sections, e.g. stitch sections, should not have their root motion blended with others, since it's using motion matching to blend into the animation already.
- L55 _public member_ `TComponentTypeID<int32> Priority;`
- L56 _public member_ `TComponentTypeID<TInstancedStruct<FMovieSceneMixedAnimationTarget>> Target;`
- L57 _public member_ `TComponentTypeID<TSharedPtr<FAnimNextEvaluationTask>> Task;`
- L58 _public member_ `TComponentTypeID<TSharedPtr<FAnimNextEvaluationTask>> MixerTask;`
- L59 _public member_ `TComponentTypeID<TInstancedStruct<FMovieSceneAnimMixerBlendProviderData>> BlendProviderData;`
- L60 _public member_ `TComponentTypeID<TSharedPtr<FMovieSceneAnimMixerEntry>> MixerEntry;`
- L61 _public member_ `TComponentTypeID<FMovieSceneRootMotionSettings> RootMotionSettings;`
- L62 _public member_ `TComponentTypeID<EMovieSceneRootMotionDestination> RootDestination;`
- L63 _public member_ `TComponentTypeID<FObjectComponent> MeshComponent;`
- L64 _public member_ `TComponentTypeID<TSharedPtr<FMovieSceneMixerRootMotionComponentData>> MixerRootMotion;`
- L65 _public member_ `TComponentTypeID<TObjectPtr<UMovieSceneAnimationMixerLayer>> MixerLayer;`
- L66 _public member_ `TComponentTypeID<TObjectPtr<UMirrorDataTable>> MirrorTable;`
- L68 _public member_ `TComponentTypeID<FTransform> BoneMatchTransform;`
- L69 _public member_ `TComponentTypeID<EMovieSceneRootMotionGapBehavior> GapBehavior;`
- L72 _public member_ `TComponentTypeID<FObjectKey> EntityOwner;` — The object (section or track) that owns/created this entity
- L77 _public member_ `TComponentTypeID<FLayerBlendTaskBuilder> LayerBlendTask;` — Layer-level blend task builder. Provided by mask system or simple blend decorations. Entities with this + MixerLayer + BoundObjectKey define how a layer blends with layers below. The builder is called with the computed layer weight and returns the blend task.
- L80 _public member_ `TComponentTypeID<FName> BusName;` — Bus name for bus sections. Identifies which named bus this section reads from.
- L88 _public member_ `} Tags;`
- L91 _private prototype_ `FAnimMixerComponentTypes();`

#### struct `UE::MovieScene::FAnimMixerComponentTypes::(anonymous)`  
``  
_L83-88_

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace MovieScene` (scope `UE`)
- L84 _member_ `FComponentTypeID Transition;` (scope `UE::MovieScene::FAnimMixerComponentTypes::__anonf30ab7680108`)
- L85 _member_ `FComponentTypeID SkipPoseWeight;` (scope `UE::MovieScene::FAnimMixerComponentTypes::__anonf30ab7680108`)
- L86 _member_ `FComponentTypeID LayerWeight;` (scope `UE::MovieScene::FAnimMixerComponentTypes::__anonf30ab7680108`)
- L87 _member_ `FComponentTypeID PreBakeRootMotion;` (scope `UE::MovieScene::FAnimMixerComponentTypes::__anonf30ab7680108`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimMixerUtils.h` (Public)


#### struct `FAnimMixerUtils`  
`struct FAnimMixerUtils`  
_L8-44_
- L10 _public function_ `static void RegisterUAFSystem(UUAFComponent* InComponent)`
- L18 _public function_ `static void UnregisterUAFSystem(UUAFComponent* InComponent)`
- L26 _public function_ `static void SetUAFComponentModule(UUAFComponent* InComponent, TObjectPtr<const UUAFSystem> InModule)`
- L34 _public function_ `static bool IsUAFModuleValid(UUAFComponent* InComponent)`
- L39 _public function_ `static TObjectPtr<const UUAFSystem> GetUAFModule(UUAFComponent* InComponent)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimNode_SequencerMixerTarget.h` (Public)


#### struct `FAnimNode_SequencerMixerTarget`  
`struct FAnimNode_SequencerMixerTarget final : public FAnimNode_Base`  
_L10-33_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L14 _public member_ `static const FName DefaultTargetName;`
- L18 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Links)` — The source input. This is passed through if there is no animation received from the level sequence, otherwise it's blended in.
- L22 _public member_ `FName TargetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setttings, meta=(CustomizePropery))` — The target name for the level sequence to match with when applying its animation.
- L25 _public prototype_ `static void ApplySequencerMixedPose(FPoseContext& Output, FName InTargetName);` — We expose this so that the anim slot node can (through IAnimGraph_SequencerMixerTargetConnector) be backwards compatible with the mixer when the mixer plugin is enabled
- L28 _public prototype_ `FAnimNode_SequencerMixerTarget();` — FAnimNode_Base overrides
- L29 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L30 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L31 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L32 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/AnimSubsystem_SequencerMixer.h` (Public)


#### struct `FAnimSubsystem_SequencerMixer`  
`struct FAnimSubsystem_SequencerMixer : public FAnimSubsystemInstance`  
_L13-34_
- reflection: `USTRUCT()`
- inherits: `FAnimSubsystemInstance`
- desc: Allows sequencer's anim mixer system to communicate with mixer nodes in an anim blueprint
- L18 _public prototype_ `virtual void Initialize_WorkerThread() override;` — FAnimSubsystemInstance interface
- L20 _public prototype_ `void RegisterEvalTask(FName TargetName, TSharedPtr<FAnimNextEvaluationTask> EvalTask);`
- L22 _public prototype_ `const TSharedPtr<FAnimNextEvaluationTask>* GetEvalTask(FName TargetName) const;`
- L24 _public prototype_ `void ResetEvalTasks();`
- L26 _public prototype_ `void StagePendingNotifyBatches(FName TargetName, TArray<FSequencerMixerPendingNotifyBatch>&& InBatches);`
- L28 _public prototype_ `TArray<FSequencerMixerPendingNotifyBatch> ConsumePendingNotifyBatches(FName TargetName);`
- L31 _private member_ `TMap<FName, TSharedPtr<FAnimNextEvaluationTask>> TargetToTaskMap;`
- L32 _private member_ `TMap<FName, TArray<FSequencerMixerPendingNotifyBatch>> TargetToPendingNotifiesMap;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/EvaluationVM/Tasks/TransitionEvaluationTask.h` (Public)


#### struct `FAnimNextTransitionEvaluationTask`  
`struct FAnimNextTransitionEvaluationTask : public FAnimNextEvaluationTask`  
_L21-59_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: FAnimNextTransitionEvaluationTask Abstract base class for all Sequencer transition evaluation tasks. Provides common from/to task references and a virtual Update method that the mixer system calls each frame before execution. Derived classes must implement Execute() and can override Update() to perform additional per-frame setup, such as managing state for stateful transitions like dead blending.
- L27 _public prototype_ `FAnimNextTransitionEvaluationTask() = default;`
- L28 _public prototype_ `virtual ~FAnimNextTransitionEvaluationTask() = default;`
- L38 _public prototype_ `virtual void Update( const TSharedPtr<FAnimNextEvaluationTask>& InFromTask, const TSharedPtr<FAnimNextEvaluationTask>& InToTask, double InBlendWeight, float InDeltaTime);` — Update the task with the current frame's data. Called by the mixer system each frame before the task is executed. The base implementation stores the from/to tasks and blend weight. Derived classes should call the base implementation and then perform any additional per-frame setup.
- L44 _public function_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override`
- L49 _protected member_ `TSharedPtr<FAnimNextEvaluationTask> FromTask;` — The task that evaluates the "from" section's pose
- L52 _protected member_ `TSharedPtr<FAnimNextEvaluationTask> ToTask;` — The task that evaluates the "to" section's pose
- L55 _protected member_ `double BlendWeight = 0.0;` — Current blend weight (0 = full from, 1 = full to)
- L58 _protected member_ `float DeltaTime = 0.0f;` — Delta time since last update

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimBusSection.h` (Public)


#### class `UMovieSceneAnimBusSection`  
`class UMovieSceneAnimBusSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L17-48_
- reflection: `UCLASS(MinimalAPI, DisplayName="Bus")`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- desc: Section type for reading a stored pose from a named bus into a mixer layer. Place this on a mixer layer to pull in the pose that another mixer wrote to the specified bus via a bus target. Defaults to infinite range but can be trimmed to only pull from the bus during part of the sequence.
- L24 _public prototype_ `UMovieSceneAnimBusSection();`
- L30 _public member_ `FName BusName;` — `UPROPERTY(EditAnywhere, Category="Animation Bus")` — Name of the bus to read the pose from
- L34 _public member_ `FMovieSceneFloatChannel Weight;` — `UPROPERTY()` — Weight channel controlling how much the bus pose contributes to the mix
- L37 _public function_ `virtual FColor GetMixerItemTint() const override`
- L44 _private prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L45 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L47 _private member_ `static constexpr FColor BusSectionTintColor = FColor(140, 70, 180);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimCrossfadeTransitionSection.h` (Public)


#### class `UMovieSceneAnimCrossfadeTransitionSection`  
`class UMovieSceneAnimCrossfadeTransitionSection : public UMovieSceneAnimTransitionSectionBase`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, DisplayName="Crossfade Transition")`
- inherits: `UMovieSceneAnimTransitionSectionBase`
- desc: Crossfade transition section that blends between two animation sections using a blend curve. The blend curve controls the interpolation: 0.0 = full FromSection, 1.0 = full ToSection.
- L21 _public prototype_ `UMovieSceneAnimCrossfadeTransitionSection(const FObjectInitializer& ObjInit);`
- L29 _public member_ `FMovieSceneFloatChannel BlendCurve;` — `UPROPERTY()` — The blend curve controlling the transition. Value of 0.0 = full FromSection pose Value of 1.0 = full ToSection pose
- L32 _public prototype_ `virtual void InitializeDefaultCurve() override;` — Initialize the blend curve with a default linear ramp from 0 to 1
- L35 _public prototype_ `virtual TSharedPtr<FAnimNextTransitionEvaluationTask> CreateTransitionTask() const override;`
- L36 _public prototype_ `virtual FName GetTransitionIconStyleName() const override;`
- L37 _public prototype_ `virtual FText GetTransitionDisplayName() const override;`
- L42 _protected prototype_ `virtual void RebuildChannelProxy(FMovieSceneChannelProxyData& Channels) override;`
- L43 _protected function_ `virtual const FMovieSceneFloatChannel* GetBlendWeightChannel() const override`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimInertialDeadBlendTransitionSection.h` (Public)


#### class `UMovieSceneAnimInertialDeadBlendTransitionSection`  
`class UMovieSceneAnimInertialDeadBlendTransitionSection : public UMovieSceneAnimTransitionSectionBase`  
_L22-94_
- reflection: `UCLASS(MinimalAPI, DisplayName="Inertial Dead Blend Transition")`
- inherits: `UMovieSceneAnimTransitionSectionBase`
- desc: Inertial dead blend transition section that provides smooth, velocity-aware blending between two animation sections. Unlike crossfade which simply interpolates between poses, dead blending: - Captures the velocity of the outgoing animation - Extrapolates that motion forward during the blend - Provides smoother transitions especially for fast-moving animations
- L28 _public prototype_ `UMovieSceneAnimInertialDeadBlendTransitionSection(const FObjectInitializer& ObjInit);`
- L34 _public member_ `EAlphaBlendOption BlendMode = EAlphaBlendOption::HermiteCubic;` — `UPROPERTY(EditAnywhere, Category = "Blending")` — The blend mode to use for the alpha curve
- L38 _public member_ `TObjectPtr<UCurveFloat> CustomBlendCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Blending")` — Optional custom blend curve (used when BlendMode is set to Custom)
- L48 _public member_ `float ExtrapolationHalfLife = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The average half-life of decay in seconds to use when extrapolating the animation. This value is scaled based on how much the outgoing velocity aligns with the direction toward the target pose.
- L55 _public member_ `float ExtrapolationHalfLifeMin = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The minimum half-life of decay in seconds. Used when velocities are very small or moving away from the target pose.
- L62 _public member_ `float ExtrapolationHalfLifeMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The maximum half-life of decay in seconds. Limits how long extrapolation can continue when velocities are small but aligned with the target.
- L69 _public member_ `float MaximumTranslationVelocity = 500.0f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Maximum translation velocity in cm/s. Velocities above this are clamped to prevent extreme extrapolation.
- L76 _public member_ `float MaximumRotationVelocity = 360.0f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Maximum rotation velocity in degrees/s. Velocities above this are clamped to prevent extreme extrapolation.
- L83 _public member_ `float MaximumScaleVelocity = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Extrapolation", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Maximum scale velocity. Velocities above this are clamped to prevent extreme extrapolation.
- L86 _public prototype_ `virtual TSharedPtr<FAnimNextTransitionEvaluationTask> CreateTransitionTask() const override;`
- L87 _public prototype_ `virtual FName GetTransitionIconStyleName() const override;`
- L88 _public prototype_ `virtual FText GetTransitionDisplayName() const override;`
- L93 _protected prototype_ `virtual void RebuildChannelProxy(FMovieSceneChannelProxyData& Channels) override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerBlendProvider.h` (Public)


#### struct `FMovieSceneAnimMixerBlendProviderData`  
`struct FMovieSceneAnimMixerBlendProviderData`  
_L11-14_
- reflection: `USTRUCT()`

#### class `ULayerBlendDecoration`  
`class ULayerBlendDecoration : public UInterface`  
_L17-21_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ILayerBlendDecoration`  
`class ILayerBlendDecoration`  
_L28-32_
- desc: Marker interface for layer blend decorations. Only one layer blend decoration is allowed per mixer layer (mutually exclusive). Used to enforce this constraint in the UI and at runtime.

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerLayerWeightSection.h` (Public)


#### class `UMovieSceneAnimMixerLayerWeightSection`  
`class UMovieSceneAnimMixerLayerWeightSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L16-43_
- reflection: `UCLASS(MinimalAPI, DisplayName="Layer Weight")`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- desc: Section for the layer weight decoration. Imports an entity tagged with LayerWeight so the mixer can read the evaluated weight channel from the owning decoration.
- L23 _public prototype_ `UMovieSceneAnimMixerLayerWeightSection();`
- L27 _public function_ `void SetAnimMixerLayer(UMovieSceneAnimationMixerLayer* InLayer)`
- L30 _public function_ `virtual bool SupportsVerticalDragging() const override`
- L31 _public function_ `virtual bool IsVisibleInAddSectionMenu() const override`
- L37 _private member_ `TObjectPtr<UMovieSceneAnimationMixerLayer> OwningLayer;` — `UPROPERTY()`
- L39 _private prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L40 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L42 _private member_ `FColor LayerWeightTintColor = FColor(25, 80, 110);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerMaskSection.h` (Public)


#### class `UMovieSceneAnimMixerMaskSection`  
`class UMovieSceneAnimMixerMaskSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L19-55_
- reflection: `UCLASS(MinimalAPI, DisplayName="Mask")`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- L26 _public prototype_ `UMovieSceneAnimMixerMaskSection();`
- L30 _public function_ `void SetAnimMixerLayer(UMovieSceneAnimationMixerLayer* InLayer)`
- L32 _public function_ `TObjectKey<UUAFBlendMask> GetBlendMask()`
- L34 _public prototype_ `void SetBlendMask(UObject* InMask);`
- L37 _public function_ `virtual bool SupportsVerticalDragging() const override`
- L39 _public function_ `virtual bool IsVisibleInAddSectionMenu() const override`
- L45 _private member_ `TObjectPtr<UUAFBlendMask> BlendMask = nullptr;` — `UPROPERTY(EditAnywhere, Category="Default")`
- L47 _private member_ `TSharedPtr<FMovieSceneMaskBlendProvider> BlendProvider;`
- L50 _private member_ `TObjectPtr<UMovieSceneAnimationMixerLayer> OwningLayer;` — `UPROPERTY()`
- L52 _private prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L54 _private member_ `FColor MaskTintColor = FColor(110, 25, 50);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIESCENEANIMMIXER_API`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerModule.h` (Public)


#### class `UE::MovieScene::FMovieSceneAnimMixerModule`  
`class FMovieSceneAnimMixerModule : public IModuleInterface, public IAnimGraphRuntime_SequencerMixerTargetConnector`  
_L27-35_
- inherits: `IModuleInterface,IAnimGraphRuntime_SequencerMixerTargetConnector`
- L30 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L31 _private prototype_ `virtual void ShutdownModule() override;`
- L33 _private prototype_ `virtual void ApplySequencerMixedPose(FPoseContext& Output, FName InTargetName) const override;`

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMovieSceneAnimMixer, Log, All);`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)
- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPreEvaluateMixerTasks, const FAnimationUpdateContext&, UE::UAF::FEvaluationVM&);`
- L19 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FPreEvaluateMixerTasks, const FAnimationUpdateContext&, UE::UAF::FEvaluationVM&);`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MovieScene` (scope `UE`)
- L23 _externvar_ `extern FName GSequencerDefaultAnimNextInjectionSite;` (scope `UE::MovieScene`)
- L25 _externvar_ `extern FAutoConsoleVariableRef CVarDefaultAnimNextInjectionSite;` (scope `UE::MovieScene`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerNotifyTypes.h` (Public)


#### struct `FSequencerMixerPendingNotifyBatch`  
`struct FSequencerMixerPendingNotifyBatch`  
_L11-15_
- desc: One section's notifies plus the blend weight at which to fire them. One batch per section so FAnimNotifyQueue::AddAnimNotifies receives the per-section InstanceWeight rather than a single combined weight across the mix.
- L13 _public member_ `TArray<FAnimNotifyEventReference> Notifies;`
- L14 _public member_ `float Weight = 1.f;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimMixerSettings.h` (Public)


#### class `UMovieSceneAnimMixerSettings`  
`class UMovieSceneAnimMixerSettings : public UDeveloperSettings`  
_L12-35_
- reflection: `UCLASS(config = Engine, defaultconfig, meta=(DisplayName="Anim Mixer"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L19 _public member_ `FName DefaultInjectionSite;` — `UPROPERTY(Config, EditAnywhere, Category="Animation", meta = (AllowedType = "FAnimNextAnimGraph"))` — Default injection site for the anim mixer to use, when no site is specified in their target. Can be overridden with the console variable Sequencer.AnimNext.DefaultInjectionSite
- L23 _public member_ `TSoftObjectPtr<UUAFSystem> DefaultUAFModule = nullptr;` — `UPROPERTY(Config, EditAnywhere, Category="Module")` — The default UAF module to use when a mixer is animating a mesh with an AnimNext component
- L25 _public prototype_ `virtual FName GetCategoryName() const override;`
- L30 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual FText GetSectionText() const override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimTransitionSectionBase.h` (Public)


#### class `UMovieSceneAnimTransitionSectionBase`  
`class UMovieSceneAnimTransitionSectionBase : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L29-116_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- desc: Abstract base class for all Anim Mixer transition section types. Transition sections handle blending between two overlapping animation sections on the same layer. Transition tasks follow a create-once, update-each-frame pattern: 1. CreateTransitionTask() is called once during entity import to create the task 2. The mixer system calls Update() on the task each frame to set from/to tasks and timing 3. The task persists as an entity component, allowing it to maintain state across frames
- L38 _public prototype_ `UMovieSceneAnimTransitionSectionBase(const FObjectInitializer& ObjInit);`
- L42 _public member_ `TObjectPtr<UMovieSceneSection> FromSection;` — `UPROPERTY()` — The section that this transition blends FROM (earlier in time)
- L46 _public member_ `TObjectPtr<UMovieSceneSection> ToSection;` — `UPROPERTY()` — The section that this transition blends TO (later in time)
- L49 _public prototype_ `bool IsValid() const;` — Check if this transition is structurally valid (sections exist, same row, bounded, overlap exists, neither fully contained)
- L52 _public prototype_ `bool UpdateBoundsFromSourceSections();` — Update this transition's bounds to match the current overlap of from/to sections
- L55 _public prototype_ `void ScaleKeysToRange(const TRange<FFrameNumber>& OldRange, const TRange<FFrameNumber>& NewRange);` — Scale blend weight keys proportionally from old range to new range
- L58 _public prototype_ `TRange<FFrameNumber> ComputeOverlapRange() const;` — Get the computed overlap range between from and to sections
- L61 _public prototype_ `float GetTransitionProgress(FFrameTime InTime) const;` — Get transition progress [0,1] at the given time. 0 = start of transition, 1 = end
- L64 _public function_ `virtual void InitializeDefaultCurve()` — Called after the section range is set to initialize any default curves/channels
- L71 _public prototype_ `virtual TSharedPtr<FAnimNextTransitionEvaluationTask> CreateTransitionTask() const PURE_VIRTUAL(UMovieSceneAnimTransitionSectionBase::CreateTransitionTask, return nullptr;);` — Create the evaluation task for this transition. Called once during entity import. The task will persist as an entity component and have its Update() method called each frame by the mixer system.
- L78 _public function_ `virtual const FMovieSceneFloatChannel* GetBlendWeightChannel() const` — Get the blend weight channel for evaluation. The result will be used as the blend weight (0 = from, 1 = to).
- L84 _public function_ `virtual FName GetTransitionIconStyleName() const` — Get the icon style name for this transition type. Used by the editor to display a small icon in the transition section.
- L90 _public function_ `virtual FText GetTransitionDisplayName() const` — Get a short display name for this transition type. Used for tooltips and other UI elements.
- L93 _public function_ `virtual FColor GetMixerItemTint() const override`
- L95 _public function_ `virtual bool SupportsVerticalDragging() const override`
- L97 _public function_ `virtual bool IsVisibleInAddSectionMenu() const override`
- L100 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override final;`
- L102 _public prototype_ `virtual bool IsLocalEvalDisabled() const override;`
- L106 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L107 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L112 _protected prototype_ `virtual void RebuildChannelProxy(FMovieSceneChannelProxyData& Channels) PURE_VIRTUAL(UMovieSceneAnimTransitionSectionBase::RebuildChannelProxy, );` — Subclasses implement to register their specific channels
- L115 _protected member_ `FColor TransitionTintColor = FColor(120, 80, 160, 200);` — Tint color for transition sections in the timeline

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimationMaskDecoration.h` (Public)


#### struct `FMovieSceneMaskBlendProviderData`  
`struct FMovieSceneMaskBlendProviderData : public FMovieSceneAnimMixerBlendProviderData`  
_L16-20_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneAnimMixerBlendProviderData`
- L19 _public member_ `TWeakObjectPtr<UUAFBlendMask> BlendMask;`

#### class `UMovieSceneAnimationMaskDecoration`  
`class UMovieSceneAnimationMaskDecoration : public UMovieSceneSignedObject , public IMovieSceneSectionProviderDecoration , public ILayerBlendDecoration`  
_L30-58_
- reflection: `UCLASS(MinimalAPI, DisplayName="Mask")`
- inherits: `UMovieSceneSignedObject,IMovieSceneSectionProviderDecoration,ILayerBlendDecoration`
- desc: Decorator for associating a mixer layer with per-bone blend masks (UAF Blend Mask). The mask system will accumulate bone weights from all mask sections on the layer and produce a per-bone blend task for inter-layer blending. Bone, attribute and curve weights can be blended using sequencer easing.
- L38 _public prototype_ `UMovieSceneAnimationMaskDecoration(const FObjectInitializer& ObjInit);`
- L40 _public function_ `virtual TArrayView<TObjectPtr<UMovieSceneSection>> GetSections() override`
- L42 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L44 _public prototype_ `virtual void AddSection(UMovieSceneSection* InSection) override;`
- L46 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& SectionToRemove) override;`
- L48 _public function_ `virtual bool SupportsMultipleSections() override`
- L50 _public prototype_ `virtual TSubclassOf<UMovieSceneSection> GetHostedSectionClass() const override;`
- L53 _public member_ `TArray<TObjectPtr<UMovieSceneSection>> MaskSections;` — `UPROPERTY()`
- L56 _public prototype_ `virtual void PostEditUndo() override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimationMixerLayer.h` (Public)


#### class `UMovieSceneAnimationMixerLayer`  
`class UMovieSceneAnimationMixerLayer : public UMovieSceneDecorationContainerObject`  
_L34-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneDecorationContainerObject`
- desc: Represents a single layer in an Animation Mixer track. Layers can contain either: - Multiple sections (of any type/mixed types that can produce animation poses) - A single child track (e.g., Control Rig track) that occupies the entire layer Layers store references to sections/tracks but do not own them. - Sections are owned by the outer Animation Mixer Track. - Child tracks are owned by the Object Binding as regular tracks are, but they contain a pointer to their parent track and they will not be shown underneath the Object Binding This allows efficient reorganization (moving sections between layers) without changing object outers, and allows easier discovery by other code. The layer index is determined by the layer's position in the parent track's Layers array. Inherits from UMovieSceneDecorationContainerObject to support features like: - Masks - Custom blend modes
- L39 _public prototype_ `UMovieSceneAnimationMixerLayer(const FObjectInitializer& ObjInit);`
- L42 _public function_ `bool HasChildTrack() const` — Check if this layer contains a child track (vs sections)
- L45 _public function_ `UMovieSceneTrack* GetChildTrack() const` — Get the child track occupying this layer (if any)
- L48 _public prototype_ `void SetChildTrack(UMovieSceneTrack* InTrack);` — Set the child track for this layer
- L51 _public function_ `const TArray<TObjectPtr<UMovieSceneSection>>& GetSections() const` — Get all section references in this layer
- L54 _public prototype_ `void AddSection(UMovieSceneSection* Section);` — Add a section reference to this layer
- L57 _public prototype_ `void RemoveSection(UMovieSceneSection* Section);` — Remove a section reference from this layer
- L60 _public prototype_ `bool ContainsSection(UMovieSceneSection* Section) const;` — Check if this layer contains the given section
- L63 _public function_ `int32 GetNumSections() const` — Get the number of sections in this layer
- L66 _public function_ `bool IsEmpty() const` — Check if this layer is empty (no sections, no child track)
- L68 _public prototype_ `int32 GetLayerIndex() const;`
- L70 _public prototype_ `const UMovieSceneAnimationMixerTrack* GetMixerTrack() const;`
- L74 _public prototype_ `FText GetDisplayName() const;` — Get the display name for this layer
- L77 _public prototype_ `void SetDisplayName(const FText& InDisplayName);` — Set a custom display name for this layer
- L80 _public function_ `bool HasCustomDisplayName() const` — Check if this layer has a custom display name
- L86 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — Section references contained in this layer (mutually exclusive with ChildTrack)
- L90 _private member_ `TObjectPtr<UMovieSceneTrack> ChildTrack;` — `UPROPERTY()` — Child track reference occupying this layer (mutually exclusive with Sections)
- L95 _private member_ `FText DisplayName;` — `UPROPERTY()` — Optional custom display name for this layer

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimationMixerTrack.h` (Public)


#### enum `EMovieSceneRootMotionKeepState`  
`enum class EMovieSceneRootMotionKeepState : uint8`  
_L30-34_
- reflection: `UENUM()`
- L32 _public enumerator_ `DontKeep UMETA(ToolTip = "Root motion offsets are discarded when the section ends; the actor returns to its pre-section pose.")`
- L33 _public enumerator_ `KeepState UMETA(DisplayName = "Keep", ToolTip = "Root motion offsets accumulated during the section are preserved after it ends; the actor remains at the moved-to location.")`

#### struct `FMovieSceneByteChannelDefaultOnly`  
`struct FMovieSceneByteChannelDefaultOnly : public FMovieSceneByteChannel`  
_L37-42_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneByteChannel`
- L41 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneByteChannelDefaultOnly> : public TStructOpsTypeTraitsBase2<FMovieSceneByteChannelDefaultOnly>`  
_L45-48_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneByteChannelDefaultOnly>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L47-47_

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneByteChannelDefaultOnly> : TMovieSceneChannelTraitsBase<FMovieSceneByteChannelDefaultOnly>`  
_L51-62_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneByteChannelDefaultOnly>`
- L59 _public typedef_ `typedef TMovieSceneExternalValue<uint8> ExtendedEditorDataType;` — Byte channels can have external values (ie, they can get their values from external objects for UI purposes)

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L54-54_
- desc: Default-only channels cannot be keyed - they only support default values

#### class `UMovieSceneAnimationSectionDecoration`  
`class UMovieSceneAnimationSectionDecoration : public UMovieSceneSignedObject , public IMovieSceneEntityDecorator , public IMovieSceneSectionDecoration , public IMovieSceneAnimationMixerItemInterface`  
_L65-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSignedObject,IMovieSceneEntityDecorator,IMovieSceneSectionDecoration,IMovieSceneAnimationMixerItemInterface`
- L76 _public member_ `TObjectPtr<UMovieSceneAnimationMixerTrack> MixerTrack;` — `UPROPERTY()`
- L80 _protected prototype_ `virtual void ExtendEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L82 _protected function_ `virtual FColor GetMixerItemTint() const override`
- L88 _private member_ `FColor MixerTintOverride = FColor();`

#### class `UMovieSceneRootMotionHostSection`  
`class UMovieSceneRootMotionHostSection : public UMovieSceneSection`  
_L94-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: Section that hosts channels from a root motion settings decoration when it lives on a track rather than a section. Delegates CacheChannelProxy to the decoration.
- L99 _public function_ `UMovieSceneRootMotionHostSection()`
- L104 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L106 _public prototype_ `void SetOwnerDecoration(UObject* InOwnerDecoration);`
- L109 _public member_ `TObjectPtr<UObject> OwnerDecoration;` — `UPROPERTY()`

#### class `UMovieSceneRootMotionSettingsDecoration`  
`class UMovieSceneRootMotionSettingsDecoration : public UMovieSceneSignedObject , public IMovieSceneChannelDecoration , public IMovieSceneEntityDecorator , public IMovieSceneSectionProviderDecoration , public IMovieSceneSectionDecoration , public IMovieSceneTrackDecoration`  
_L119-243_
- reflection: `UCLASS(MinimalAPI, collapseCategories, meta=(DisplayName="Root Motion Settings"))`
- inherits: `UMovieSceneSignedObject,IMovieSceneChannelDecoration,IMovieSceneEntityDecorator,IMovieSceneSectionProviderDecoration,IMovieSceneSectionDecoration,IMovieSceneTrackDecoration`
- desc: Decoration that provides root motion offset settings. Can live on a section (skeletal animation) or on a track (control rig child track). When on a section, channels are hosted by the parent section via IMovieSceneChannelDecoration. When on a track, an internal host section is created via IMovieSceneSectionProviderDecoration.
- L131 _public prototype_ `UMovieSceneRootMotionSettingsDecoration(const FObjectInitializer& ObjInit);`
- L133 _public prototype_ `EMovieSceneRootMotionTransformMode GetRootTransformMode() const;`
- L134 _public prototype_ `EMovieSceneRootMotionSource GetRootMotionSource() const;`
- L139 _public prototype_ `TOptional<FFrameTime> GetFirstLoopBoundary(const FFrameRate& TickResolution) const;` — Returns the first loop boundary time for the owning section, or TOptional empty if the section doesn't loop. Uses the section's timing transform to find the actual loop wrap point (preserving sub-frames).
- L144 _public prototype_ `FTransform GetInitialRootTransformAtTime(FFrameTime Time, const FFrameRate& TickResolution) const;` — Returns the appropriate initial root transform for the given time - either InitialRootTransform for the first loop iteration, or LoopStartRootTransform for subsequent iterations.
- L146 _public prototype_ `virtual EMovieSceneChannelProxyType PopulateChannelProxy(FMovieSceneChannelProxyData& OutProxyData) override;`
- L147 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L150 _public prototype_ `virtual TArrayView<TObjectPtr<UMovieSceneSection>> GetSections() override;` — IMovieSceneSectionProviderDecoration - provides an internal section when on a track
- L153 _public prototype_ `virtual void OnDecorationAdded(UMovieSceneSection* Section) override;` — IMovieSceneSectionDecoration - auto-creates Root Motion Target when added to a section
- L156 _public prototype_ `virtual void OnDecorationAdded(UMovieSceneTrack* Track) override;` — IMovieSceneTrackDecoration - auto-creates Root Motion Target when added to a child track
- L159 _public prototype_ `void EnsureHostSection();` — Creates the internal host section when the decoration is added to a track
- L164 _public member_ `FMovieSceneDoubleChannel Location[3];` — `UPROPERTY()`
- L167 _public member_ `FMovieSceneDoubleChannel Rotation[3];` — `UPROPERTY()`
- L170 _public member_ `FVector RootOriginLocation;` — `UPROPERTY(EditAnywhere, Category="Root Transform")`
- L173 _public member_ `FMovieSceneByteChannelDefaultOnly RootMotionSpace;` — `UPROPERTY()`
- L176 _public member_ `FMovieSceneByteChannelDefaultOnly RootMotionSourceChannel;` — `UPROPERTY()`
- L179 _public member_ `FMovieSceneByteChannelDefaultOnly TransformMode;` — `UPROPERTY()`
- L184 _public member_ `FMovieSceneBoneMatchChannel BoneMatchChannel;` — `UPROPERTY()`
- L187 _public function_ `FMovieSceneBoneMatchData GetBoneMatchData() const` — Read the first key from the channel, or return a default (invalid) match
- L194 _public function_ `bool HasBoneMatch() const`
- L202 _public member_ `FMovieSceneByteChannelDefaultOnly KeepStateChannel;` — `UPROPERTY()`
- L204 _public function_ `bool GetKeepStateAfterSectionEnds() const`
- L211 _public member_ `FMovieSceneByteChannelDefaultOnly LoopModeChannel;` — `UPROPERTY()`
- L213 _public function_ `EMovieSceneAnimLoopMode GetLoopMode() const`
- L222 _public member_ `FTransform InitialRootTransform = FTransform::Identity;` — `UPROPERTY()` — Cached initial root transform at the section's start time, computed via isolated bake evaluation. Used by AccumulatedOffset mode to compute the delta from the animation's starting position.
- L229 _public member_ `FTransform LoopStartRootTransform = FTransform::Identity;` — `UPROPERTY()` — Root transform at the animation's natural start (frame 0). When the section is extended left, the first loop starts mid-animation so InitialRootTransform differs from the animation start. After the first loop wraps, all subsequent iterations start from this transform instead.
- L232 _public member_ `bool bInitialRootTransformValid = false;` — `UPROPERTY()`
- L236 _public member_ `TObjectPtr<UMovieSceneSection> HostSection;` — `UPROPERTY()` — Internal section for hosting channels when the decoration lives on a track
- L241 _public member_ `bool bShowSkeleton = false;` — `UPROPERTY(Transient)` — When true, the edit mode draws this section's skeleton in the viewport. Useful for bone matching.

#### class `UMovieSceneAnimationMixerTrack`  
`class UMovieSceneAnimationMixerTrack : public UMovieSceneCommonAnimationTrack`  
_L253-407_
- reflection: `UCLASS(MinimalAPI, HideCategories=("RootMotions"))`
- inherits: `UMovieSceneCommonAnimationTrack`
- L260 _public prototype_ `UMovieSceneAnimationMixerTrack(const FObjectInitializer& Init);`
- L262 _public prototype_ `virtual bool FixRowIndices() override;`
- L263 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L264 _public prototype_ `virtual UMovieSceneDecorationContainerObject* GetDecorationContainerForRow(int32 RowIndex) const override;`
- L267 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L268 _public prototype_ `virtual bool PopulateEvaluationTree(TMovieSceneEvaluationTree<FMovieSceneTrackEvaluationData>& OutData) const override;`
- L270 _public prototype_ `virtual void OnSectionAddedImpl(UMovieSceneSection* Secton) override;`
- L271 _public prototype_ `virtual void OnSectionRemovedImpl(UMovieSceneSection* Section) override;`
- L272 _public prototype_ `virtual void OnRemovedFromMovieSceneImpl() override;`
- L274 _public prototype_ `virtual EMovieSceneSectionMovedResult OnSectionMoved(UMovieSceneSection& Section, const FMovieSceneSectionMovedParams& Params) override;`
- L276 _public prototype_ `virtual EMovieSceneTrackEasingSupportFlags SupportsEasing(FMovieSceneSupportsEasingParams& Params) const override;`
- L278 _public prototype_ `virtual void UpdateEasing() override;`
- L280 _public prototype_ `virtual UMovieSceneSection* AddNewAnimationOnRow(FFrameNumber KeyTime, UAnimSequenceBase* AnimSequence, int32 RowIndex) override;`
- L281 _public prototype_ `virtual void AddSectionWithAutoRow(UMovieSceneSection* Section) override;`
- L282 _public prototype_ `virtual int32 ComputeNextAvailableRowIndex() const override;`
- L286 _public prototype_ `void InvalidateAccumulatedOffsetCache();` — Invalidate the accumulated offset cache on the root motion section. Call whenever sections change (add/remove/move) to mark the cache for rebuild.
- L288 _public prototype_ `bool HasDirtyAccumulatedOffsetCache() const;`
- L293 _public prototype_ `void RebuildDirtyAccumulatedOffsetCache( class UMovieSceneEntitySystemLinker* Linker, UE::MovieScene::FInstanceHandle InstanceHandle);` — Rebuild the accumulated offset cache on the root motion section if dirty. Must be called from outside the ECS evaluation pipeline — the rebuild uses isolated bake evaluations that re-enter the ECS.
- L298 _public prototype_ `virtual FText GetTrackRowDisplayName(int32 RowIndex) const override;`
- L299 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L300 _public prototype_ `virtual bool CanRename() const override;`
- L304 _public prototype_ `virtual UMovieSceneTrack* AddChildTrack(FGuid ObjectBinding, TSubclassOf<UMovieSceneTrack> TrackClass, int32 RowIndex) override;`
- L305 _public prototype_ `int32 GetNextChildTrackRowIndex() const;`
- L306 _public prototype_ `virtual void GetAllChildTracks(TArray<TObjectPtr<UMovieSceneTrack>>& OutChildTracks) const override;`
- L307 _public prototype_ `void RemoveChildTrack(UMovieSceneTrack* Track);`
- L309 _public prototype_ `UMovieSceneTrack* GetChildTrackAtRow(int32 RowIndex) const;`
- L311 _public prototype_ `bool IsChildTrack(UMovieSceneTrack* Track) const;`
- L312 _public prototype_ `int32 GetChildTrackRow(UMovieSceneTrack* Track) const;`
- L313 _public prototype_ `void SetChildTrackRow(UMovieSceneTrack* Track, int32 NewRowIndex);`
- L321 _public prototype_ `UMovieSceneAnimationMixerLayer* GetOrCreateLayer(int32 RowIndex);` — Create or get a layer at the specified row index
- L324 _public prototype_ `UMovieSceneAnimationMixerLayer* GetLayer(int32 RowIndex) const;` — Get the layer at the specified row index (returns null if doesn't exist)
- L327 _public function_ `const TArray<TObjectPtr<UMovieSceneAnimationMixerLayer>>& GetLayers() const` — Get all layers (sorted by row index)
- L330 _public prototype_ `UMovieSceneAnimationMixerLayer* GetLayerForSection(UMovieSceneSection* Section) const;` — Get the layer containing the given section (uses section's row index)
- L333 _public prototype_ `UMovieSceneAnimationMixerLayer* GetLayerForChildTrack(UMovieSceneTrack* Track) const;` — Get the layer containing the given child track
- L336 _public prototype_ `UMovieSceneAnimationMixerLayer* InsertLayer(int32 InsertIndex);` — Insert a new empty layer at the specified index, shifting existing layers down
- L344 _public prototype_ `template<typename TransitionClass> TransitionClass* CreateTransitionSection(UMovieSceneSection* FromSection, UMovieSceneSection* ToSection);` — Create a transition section between two overlapping sections on the same layer.
- L349 _public prototype_ `UMovieSceneAnimTransitionSectionBase* CreateTransitionSectionOfType( UMovieSceneSection* FromSection, UMovieSceneSection* ToSection, TSubclassOf<UMovieSceneAnimTransitionSectionBase> TransitionClass);` — Create a transition section of the specified type between two overlapping sections (runtime class selection).
- L355 _public prototype_ `TArray<UMovieSceneAnimTransitionSectionBase*> FindTransitionsForSection(UMovieSceneSection* Section) const;` — Find transition sections that reference the given section as either from or to
- L358 _public prototype_ `TArray<UMovieSceneSection*> FindOverlappingSections(UMovieSceneSection* Section) const;` — Find sections that overlap with the given section on the same layer (excluding transitions)
- L365 _public prototype_ `static bool IsOverlapLargeEnoughForTransition(const TRange<FFrameNumber>& Overlap, const UObject* ContextObject);` — Returns true if the given overlap range is large enough to warrant a transition. Sub-frame overlaps (from section endpoints that don't align to display frame boundaries) are rejected so that abutting sections don't produce zero-width transitions.
- L368 _public prototype_ `int32 CountSectionsOverlappingRange(const TRange<FFrameNumber>& Range, int32 RowIndex) const;` — Count how many non-transition sections overlap the given range on the specified row
- L371 _public prototype_ `UMovieSceneAnimTransitionSectionBase* FindTransitionForPair(UMovieSceneSection* FromSection, UMovieSceneSection* ToSection) const;` — Check if a transition already exists for the given from/to section pair
- L374 _public prototype_ `void AutoCreateTransitionsForSection(UMovieSceneSection* Section);` — Auto-create transitions for any overlapping sections involving the given section
- L382 _public prototype_ `bool UpdateTransitionsForRow(int32 RowIndex);` — Validates and updates all transitions on the specified row. This removes invalid transitions and creates new ones for valid overlaps. Call this after any operation that might affect transition validity on a row (section added, moved, removed, or row changed).
- L388 _public prototype_ `bool UpdateTransitionsForRows(const TSet<int32>& RowIndices);` — Validates and updates all transitions on the specified rows. Convenience method that calls UpdateTransitionsForRow for each row.
- L392 _public member_ `TInstancedStruct<FMovieSceneMixedAnimationTarget> MixedAnimationTarget;` — `UPROPERTY(EditAnywhere, Category = "Mixed Animation")`
- L397 _private prototype_ `EMovieSceneSectionMovedResult HandleTransitionSectionMoved(UMovieSceneAnimTransitionSectionBase& TransitionSection);` — Handle when a transition section is moved - adjusts from/to sections and constrains row changes
- L401 _private member_ `TMap<TObjectPtr<UMovieSceneTrack>, int32> ChildTracks;` — `UPROPERTY()` — Row assignment for child tracks
- L406 _private member_ `TArray<TObjectPtr<UMovieSceneAnimationMixerLayer>> Layers;` — `UPROPERTY()` — Layers organizing sections and child tracks by row index Array is kept sorted by row index for efficient lookup
- L410 _function_ `template<typename TransitionClass> TransitionClass* UMovieSceneAnimationMixerTrack::CreateTransitionSection(UMovieSceneSection* FromSection, UMovieSceneSection* ToSection)`

#### Free symbols / members of external scopes

- L47 _enumerator_ `enum { WithStructuredSerializeFromMismatchedTag = true };` (scope `TStructOpsTypeTraits::__anonb421845e0103`)
- L54 _enumerator_ `enum { SupportsKeying = false }; #if WITH_EDITOR typedef TMovieSceneExternalValue<uint8> ExtendedEditorDataType; #endif` (scope `TMovieSceneChannelTraits::__anonb421845e0203`) — Default-only channels cannot be keyed - they only support default values
- L247 _prototype_ `bool WouldCreateBoneMatchCycle(UMovieSceneSection* CandidateSection, UMovieSceneSection* TargetSection);` — Returns true if setting TargetSection to reference CandidateSection would create a bone match dependency cycle

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneAnimationTrackDecoration.h` (Public)


#### class `UMovieSceneAnimationTrackDecoration`  
`class UMovieSceneAnimationTrackDecoration : public UMovieSceneSignedObject , public IMovieSceneTrackDecoration , public IMovieSceneEntityDecorator`  
_L18-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSignedObject,IMovieSceneTrackDecoration,IMovieSceneEntityDecorator`
- desc: Track decoration that adds animation mixer components to child track entities. Priority is determined by the track's layer assignment within the mixer track.
- L28 _public member_ `TObjectPtr<UMovieSceneAnimationMixerTrack> MixerTrack;` — `UPROPERTY()`
- L31 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityDecorator interface

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneBoneMatchChannel.h` (Public)


#### struct `FMovieSceneBoneMatchChannel`  
`struct FMovieSceneBoneMatchChannel : public FMovieSceneChannel`  
_L16-60_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- desc: Channel that stores FMovieSceneBoneMatchData as discrete (non-interpolated) keys. Typically holds 0 or 1 keys: one bone match per section.
- L20 _public typedef_ `typedef FMovieSceneBoneMatchData CurveValueType;`
- L22 _public function_ `TMovieSceneChannelData<FMovieSceneBoneMatchData> GetData()`
- L27 _public function_ `TMovieSceneChannelData<const FMovieSceneBoneMatchData> GetData() const`
- L33 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;` — FMovieSceneChannel interface
- L34 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L35 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L36 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L37 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L38 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L39 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L40 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L41 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L42 _public prototype_ `virtual void Reset() override;`
- L43 _public prototype_ `void NotifyReferenceChanged(FFrameNumber NewResolvedTime);`
- L44 _public prototype_ `void ApplyOwningSectionRange(TOptional<FFrameNumber> NewStart, TOptional<FFrameNumber> NewEnd);`
- L45 _public prototype_ `virtual void Optimize(const FKeyDataOptimizationParams& InParameters) override;`
- L46 _public prototype_ `virtual void ClearDefault() override;`
- L47 _public prototype_ `virtual FKeyHandle GetHandle(int32 Index) override;`
- L48 _public prototype_ `virtual int32 GetIndex(FKeyHandle Handle) override;`
- L53 _private member_ `TArray<FFrameNumber> Times;` — `UPROPERTY(meta=(KeyTimes))`
- L56 _private member_ `TArray<FMovieSceneBoneMatchData> Values;` — `UPROPERTY(meta=(KeyValues))`
- L59 _private member_ `FMovieSceneKeyHandleMap KeyHandles;` — `UPROPERTY(Transient)`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneBoneMatchChannel> : TMovieSceneChannelTraitsBase<FMovieSceneBoneMatchChannel>`  
_L63-66_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneBoneMatchChannel>`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L65-65_

#### Free symbols / members of external scopes

- L65 _enumerator_ `enum { SupportsDefaults = false };` (scope `TMovieSceneChannelTraits::__anon4deda16e0103`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneBoneMatchData.h` (Public)


#### enum `EBoneMatchTimeMode`  
`enum class EBoneMatchTimeMode : uint8`  
_L14-22_
- reflection: `UENUM()`
- L16 _public enumerator_ `AtCurrentTime`
- L17 _public enumerator_ `AtStartOfSelectedSection`
- L18 _public enumerator_ `AtEndOfSelectedSection`
- L19 _public enumerator_ `AtStartOfReferenceSection`
- L20 _public enumerator_ `AtEndOfReferenceSection`
- L21 _public enumerator_ `InBetween`

#### struct `FMovieSceneBoneMatchData`  
`struct FMovieSceneBoneMatchData`  
_L25-95_
- reflection: `USTRUCT()`
- L31 _public member_ `FTransform MatchTransform = FTransform::Identity;` — `UPROPERTY(VisibleAnywhere, Category="Bone Matching")` — Computed match transform offset
- L35 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")` — Bone to match
- L39 _public member_ `TWeakObjectPtr<UMovieSceneSection> ReferenceSection;` — `UPROPERTY()` — Reference section for determining match time
- L42 _public member_ `EBoneMatchTimeMode MatchTimeMode = EBoneMatchTimeMode::AtCurrentTime;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L45 _public member_ `bool bMatchLocationX = true;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L48 _public member_ `bool bMatchLocationY = true;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L51 _public member_ `bool bMatchLocationZ = false;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L54 _public member_ `bool bMatchRotationX = false;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L57 _public member_ `bool bMatchRotationY = false;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L60 _public member_ `bool bMatchRotationZ = true;` — `UPROPERTY(EditAnywhere, Category="Bone Matching")`
- L63 _public member_ `bool bIsValid = false;` — `UPROPERTY()`
- L67 _public member_ `bool bIsDirty = false;` — `UPROPERTY()` — Set when section moves after a valid match
- L72 _public member_ `FFrameNumber MatchTime;` — `UPROPERTY()` — Resolved match time (frame number) filled in by ComputeBoneMatch. Used by the editor to place the key on the channel.

#### Free symbols / members of external scopes

- L77 _function_ `friend bool operator==(const FMovieSceneBoneMatchData& A, const FMovieSceneBoneMatchData& B)` — Compares user-specified settings and validity state. Computed results (MatchTransform, MatchTime) and transient state (bIsDirty) are excluded since they change on every re-evaluation.
- L91 _function_ `friend bool operator!=(const FMovieSceneBoneMatchData& A, const FMovieSceneBoneMatchData& B)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneLayerWeightDecoration.h` (Public)


#### class `UMovieSceneLayerWeightDecoration`  
`class UMovieSceneLayerWeightDecoration : public UMovieSceneSignedObject , public IMovieSceneSectionProviderDecoration , public IMovieSceneChannelDecoration`  
_L18-50_
- reflection: `UCLASS(MinimalAPI, DisplayName="Layer Weight")`
- inherits: `UMovieSceneSignedObject,IMovieSceneSectionProviderDecoration,IMovieSceneChannelDecoration`
- desc: Decoration that adds a keyframeable weight channel to a mixer layer. The weight (default 1.0) multiplies with the section weight before inter-layer blending, scaling the layer's contribution to the final pose.
- L26 _public prototype_ `UMovieSceneLayerWeightDecoration(const FObjectInitializer& ObjInit);`
- L29 _public function_ `virtual TArrayView<TObjectPtr<UMovieSceneSection>> GetSections() override` — IMovieSceneSectionProviderDecoration
- L30 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L31 _public prototype_ `virtual void AddSection(UMovieSceneSection* InSection) override;`
- L32 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& SectionToRemove) override;`
- L33 _public function_ `virtual bool SupportsMultipleSections() override`
- L34 _public prototype_ `virtual TSubclassOf<UMovieSceneSection> GetHostedSectionClass() const override;`
- L37 _public prototype_ `virtual EMovieSceneChannelProxyType PopulateChannelProxy(FMovieSceneChannelProxyData& OutProxyData) override;` — IMovieSceneChannelDecoration
- L39 _public function_ `const FMovieSceneFloatChannel& GetWeightChannel() const`
- L42 _public member_ `FMovieSceneFloatChannel WeightChannel;` — `UPROPERTY()`
- L45 _public member_ `TArray<TObjectPtr<UMovieSceneSection>> WeightSections;` — `UPROPERTY()`
- L48 _public prototype_ `virtual void PostEditUndo() override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneMirroringDecoration.h` (Public)


#### class `UMovieSceneMirroringDecoration`  
`class UMovieSceneMirroringDecoration : public UMovieSceneSignedObject , public IMovieSceneSectionDecoration , public IMovieSceneTrackDecoration , public IMovieSceneEntityDecorator`  
_L19-35_
- reflection: `UCLASS(MinimalAPI, collapseCategories, meta=(DisplayName="Mirroring"))`
- inherits: `UMovieSceneSignedObject,IMovieSceneSectionDecoration,IMovieSceneTrackDecoration,IMovieSceneEntityDecorator`
- desc: Decoration that applies mirroring to animation poses produced by sections or tracks in the Anim Mixer.
- L31 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mirroring")` — The mirror data table used to mirror the animation pose
- L34 _public prototype_ `virtual void ExtendEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;` — IMovieSceneEntityDecorator interface

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneRootMotionSection.h` (Public)


#### enum `EMovieSceneRootMotionDestination`  
`enum class EMovieSceneRootMotionDestination : uint8`  
_L16-28_
- reflection: `UENUM()`
- L19 _public enumerator_ `Discard` — Throw away any transform on the root bone
- L21 _public enumerator_ `RootBone` — Leave the root bone with whatever transform it ended up with after evaluation
- L23 _public enumerator_ `Component` — Copy the root bone's transform onto the owning Component, and reset the root transform
- L25 _public enumerator_ `Actor` — Copy the root bone's transform onto the owning Actor, and reset the root transform
- L27 _public enumerator_ `Attribute` — Leave the root motion transform on an attribute for external systems to pick up

#### enum `EMovieSceneRootMotionGapBehavior`  
`enum class EMovieSceneRootMotionGapBehavior : uint8`  
_L32-38_
- reflection: `UENUM()`
- desc: Behavior during gaps where no root motion sections are active
- L35 _public enumerator_ `ResetToOrigin` — Reset to origin during gaps - current default behavior
- L37 _public enumerator_ `PersistPreviousTransform` — Persist the transform from the previous section that had KeepState enabled

#### struct `FRootMotionAccumulatedOffset`  
`struct FRootMotionAccumulatedOffset`  
_L46-69_
- reflection: `USTRUCT()`
- desc: Cached accumulated offset from sections with KeepState enabled. For non-AccumulatedOffset sections, AccumulatedOffset holds world-space and AnimSpaceAccumulatedOffset holds animation-space. For AccumulatedOffset sections, both fields hold animation-space values because the world conversion is applied at runtime by the conversion task.
- L52 _public member_ `FFrameTime StartFrame;` — `UPROPERTY()` — Time at which this accumulated offset takes effect
- L56 _public member_ `FTransform AccumulatedOffset = FTransform::Identity;` — `UPROPERTY()` — The accumulated transform offset at this point (world space)
- L60 _public member_ `FTransform AnimSpaceAccumulatedOffset = FTransform::Identity;` — `UPROPERTY()` — The accumulated transform offset in animation space (pre-world conversion)
- L64 _public member_ `float Weight = 1.0f;` — `UPROPERTY()` — Weight of this offset for blending
- L68 _public member_ `TObjectPtr<UMovieSceneSection> OwnerSection = nullptr;` — `UPROPERTY()` — The section that generated this cache entry

#### class `UMovieSceneRootMotionSection`  
`class UMovieSceneRootMotionSection : public UMovieSceneSection , public IMovieSceneEntityProvider , public IMovieSceneAnimationMixerItemInterface`  
_L76-160_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Root Motion Target", Hidden))`
- inherits: `UMovieSceneSection,IMovieSceneEntityProvider,IMovieSceneAnimationMixerItemInterface`
- desc: Section that controls where root motion is applied for animation mixer tracks. Created internally by UMovieSceneRootMotionTargetDecoration - not added directly.
- L85 _public prototype_ `UMovieSceneRootMotionSection(const FObjectInitializer& Init);`
- L87 _public prototype_ `virtual int32 GetRowSortOrder() const;`
- L89 _public function_ `virtual FColor GetMixerItemTint() const override`
- L94 _public prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L96 _public prototype_ `virtual void ImportEntityImpl(UMovieSceneEntitySystemLinker* EntityLinker, const FEntityImportParams& Params, FImportedEntity* OutImportedEntity) override;`
- L97 _public prototype_ `virtual bool PopulateEvaluationFieldImpl(const TRange<FFrameNumber>& EffectiveRange, const FMovieSceneEvaluationFieldEntityMetaData& InMetaData, FMovieSceneEntityComponentFieldBuilder* OutFieldBuilder) override;`
- L100 _public prototype_ `FTransform GetAccumulatedOffsetAt(FFrameTime Time) const;` — Get the accumulated offset at a given time (world space)
- L105 _public prototype_ `FTransform GetAccumulatedOffsetForSection(FFrameTime Time, UMovieSceneSection* Section, bool bAllowCrossSection) const;` — Section-filtered accumulated offset lookup. bAllowCrossSection lets the query see entries owned by other sections that fall before this section's start, for AccumulatedOffset-style chaining.
- L108 _public prototype_ `FTransform GetAnimSpaceAccumulatedOffsetAt(FFrameTime Time) const;` — Get the accumulated offset at a given time in animation space (pre-world conversion)
- L111 _public prototype_ `FTransform GetAnimSpaceAccumulatedOffsetForSection(FFrameTime Time, UMovieSceneSection* Section, bool bAllowCrossSection) const;` — Anim-space variant of GetAccumulatedOffsetForSection.
- L114 _public prototype_ `bool HasApplicableAccumulatedEntry(FFrameTime Time, UMovieSceneSection* Section, bool bAllowCrossSection) const;` — Existence check using the same filter rules as GetAccumulatedOffsetForSection.
- L117 _private prototype_ `FTransform FindAccumulatedOffsetForSection(FFrameTime Time, UMovieSceneSection* Section, bool bAnimSpace, bool bAllowCrossSection) const;`
- L121 _public prototype_ `void RebuildAccumulatedOffsetCache( class UMovieSceneEntitySystemLinker* Linker, UE::MovieScene::FInstanceHandle InstanceHandle, class UMovieSceneAnimationMixerTrack* MixerTrack);` — Rebuild the accumulated offset cache using isolated bake evaluations.
- L126 _public function_ `void InvalidateAccumulatedOffsetCache()`
- L127 _public function_ `bool IsAccumulatedOffsetCacheDirty() const`
- L132 _public prototype_ `static FFrameNumber ResolveLoopTransitionTick( const FMovieSceneSequenceTransform& Transform, FFrameTime ApproximateBoundary, float Duration);` — Resolve a loop boundary returned by ExtractBoundariesWithinRange to the integer outer tick at which the runtime's loop index actually transitions. Used so cache entries land on exactly the same tick as runtime wraps.
- L141 _public member_ `EMovieSceneRootMotionGapBehavior GapBehavior = EMovieSceneRootMotionGapBehavior::PersistPreviousTransform;` — `UPROPERTY(EditAnywhere, Category="Root Motion")` — How to handle gaps where no sections with root motion are active
- L146 _public member_ `TArray<FRootMotionAccumulatedOffset> AccumulatedOffsetCache;` — `UPROPERTY()` — Cached accumulated offsets from sections with KeepState enabled. Serialized so the correct values are available at runtime without needing to rebuild.
- L148 _public member_ `bool bAccumulatedOffsetCacheDirty = false;`
- L152 _public member_ `uint32 CacheBuiltEvalDisabledSig = 0;` — Eval-disabled (mute/deactivate) signature the cache was last built against; a mismatch means a mute/enable change made it stale. Sits in the bool's padding.
- L157 _private member_ `FMovieSceneByteChannel RootDestinationChannel;` — `UPROPERTY()`
- L159 _private member_ `FColor MixerTintOverride = FColor(20, 70, 70, 200);`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/MovieSceneRootMotionTargetDecoration.h` (Public)


#### class `UMovieSceneRootMotionTargetDecoration`  
`class UMovieSceneRootMotionTargetDecoration : public UMovieSceneSignedObject , public IMovieSceneTrackDecoration , public IMovieSceneSectionProviderDecoration`  
_L20-47_
- reflection: `UCLASS(MinimalAPI, collapseCategories, meta=(DisplayName="Root Motion Target"))`
- inherits: `UMovieSceneSignedObject,IMovieSceneTrackDecoration,IMovieSceneSectionProviderDecoration`
- desc: Track-level decoration that controls where root motion is applied. Wraps a UMovieSceneRootMotionSection
- L29 _public prototype_ `UMovieSceneRootMotionTargetDecoration(const FObjectInitializer& Init);`
- L32 _public prototype_ `virtual void OnDecorationAdded(UMovieSceneTrack* Track) override;` — IMovieSceneTrackDecoration interface
- L33 _public prototype_ `virtual void OnDecorationRemoved() override;`
- L36 _public prototype_ `virtual TArrayView<TObjectPtr<UMovieSceneSection>> GetSections() override;` — IMovieSceneSectionProviderDecoration interface
- L37 _public prototype_ `virtual TSubclassOf<UMovieSceneSection> GetHostedSectionClass() const override;`
- L40 _public function_ `UMovieSceneRootMotionSection* GetRootMotionSection() const` — Get the internal root motion section
- L46 _protected member_ `TObjectPtr<UMovieSceneSection> RootMotionSection;` — `UPROPERTY()` — Internal root motion section that provides the destination channel and entity logic

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimBlueprintTargetSystem.h` (Public)


#### struct `FMovieSceneAnimBlueprintTarget`  
`struct FMovieSceneAnimBlueprintTarget : public FMovieSceneMixedAnimationTarget`  
_L15-46_
- reflection: `USTRUCT(meta=(DisplayName="Anim Blueprint Target"))`
- inherits: `FMovieSceneMixedAnimationTarget`
- desc: Declaring a unique target for the "Sequencer Mixer Target" node in an Anim BP. Will match the node's name with the name specified here.
- L21 _public member_ `FName BlueprintNodeName;` — `UPROPERTY(EditAnywhere, Category="Animation")` — Node name to use for injection.
- L28 _public function_ `FMovieSceneAnimBlueprintTarget(FName InBlueprintNodeName) : BlueprintNodeName(InBlueprintNodeName)`
- L34 _public function_ `FMovieSceneAnimBlueprintTarget() : BlueprintNodeName(FAnimNode_SequencerMixerTarget::DefaultTargetName)`
- L41 _public function_ `virtual FText GetShortDisplayName() const override`

#### class `UMovieSceneAnimBlueprintTargetSystem`  
`class UMovieSceneAnimBlueprintTargetSystem : public UMovieSceneEntitySystem`  
_L49-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- L55 _public prototype_ `UMovieSceneAnimBlueprintTargetSystem(const FObjectInitializer& ObjInit);`
- L59 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

#### Free symbols / members of external scopes

- L23 _function_ `inline friend uint32 GetTypeHash(const FMovieSceneAnimBlueprintTarget& Target)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimBusSystem.h` (Public)


#### struct `FMovieSceneAnimBusReadTask`  
`struct FMovieSceneAnimBusReadTask : public FAnimNextEvaluationTask`  
_L17-33_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Evaluation task that reads a stored pose from a named bus and pushes it onto the VM's keyframe stack. Used by UMovieSceneAnimBusSection to inject poses written by bus-target mixers into a consuming mixer's program.
- L21 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FMovieSceneAnimBusReadTask) static FMovieSceneAnimBusReadTask Make(FName InBusName, FObjectKey InBoundObjectKey, UMovieSceneAnimMixerSystem* InMixerSystem);`
- L25 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L28 _public member_ `FName BusName;` — `UPROPERTY()`
- L30 _public member_ `FObjectKey BoundObjectKey;`
- L32 _public member_ `TWeakObjectPtr<UMovieSceneAnimMixerSystem> MixerSystem;`

#### class `UMovieSceneAnimBusSystem`  
`class UMovieSceneAnimBusSystem : public UMovieSceneEntitySystem`  
_L39-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that creates/updates FMovieSceneAnimBusReadTask instances on entities with BusName components. Runs before UMovieSceneAnimMixerSystem so bus read tasks are in place before the mixer builds its evaluation program.
- L45 _public prototype_ `UMovieSceneAnimBusSystem(const FObjectInitializer& ObjInit);`
- L49 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimInstanceTargetSystem.h` (Public)


#### struct `FMovieSceneAnimInstanceTarget`  
`struct FMovieSceneAnimInstanceTarget : public FMovieSceneMixedAnimationTarget`  
_L22-37_
- reflection: `USTRUCT(meta=(DisplayName="Custom Anim Instance"))`
- inherits: `FMovieSceneMixedAnimationTarget`
- desc: Declaring a unique target for targeting a custom anim instance on the skeletal mesh component. Doesn't need additional metadata.
- L32 _public function_ `virtual FText GetShortDisplayName() const override`

#### class `USequencerMixedAnimInstance`  
`class USequencerMixedAnimInstance : public UAnimInstance, public ISequencerAnimationSupport`  
_L42-70_
- reflection: `UCLASS(transient, NotBlueprintable, MinimalAPI)`
- inherits: `UAnimInstance,ISequencerAnimationSupport`
- desc: Custom anim instance and proxy that take an anim evaluation task, evaluate it, and push the resulting pose to the skeleton.
- L46 _private prototype_ `USequencerMixedAnimInstance(const FObjectInitializer& ObjectInitializer);`
- L49 _public prototype_ `void SetMixerTask(TSharedPtr<FAnimNextEvaluationTask> InEvalTask);`
- L51 _public prototype_ `void StagePendingNotifyBatches(TArray<FSequencerMixerPendingNotifyBatch>&& InBatches);`
- L55 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;` — UAnimInstance interface
- L60 _protected function_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InPosition, float Weight, bool bFireNotifies) override` — Empty ISequencerAnimationSupport things we don't use- would be better to have 2 interfaces, but deprecation would be a pain.
- L61 _protected function_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InFromPosition, float InToPosition, float Weight, bool bFireNotifies) override`
- L62 _protected function_ `virtual void ConstructNodes() override`
- L63 _protected function_ `virtual void ResetNodes() override`
- L64 _protected function_ `virtual void ResetPose() override`
- L65 _protected function_ `virtual void SavePose() override`
- L67 _protected prototype_ `virtual UAnimInstance* GetSourceAnimInstance() override;`
- L68 _protected prototype_ `virtual void SetSourceAnimInstance(UAnimInstance* SourceAnimInstance) override;`
- L69 _protected function_ `virtual bool DoesSupportDifferentSourceAnimInstance() const override`

#### struct `FSequencerMixedAnimInstanceProxy`  
`struct FSequencerMixedAnimInstanceProxy : public FAnimInstanceProxy`  
_L75-122_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L80 _public function_ `FSequencerMixedAnimInstanceProxy()`
- L84 _public function_ `FSequencerMixedAnimInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy(InAnimInstance)`
- L89 _public function_ `virtual ~FSequencerMixedAnimInstanceProxy()`
- L92 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;` — FAnimInstanceProxy interface
- L93 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L94 _public prototype_ `virtual void CacheBones() override;`
- L95 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L96 _public prototype_ `virtual void PreEvaluateAnimation(UAnimInstance* InAnimInstance) override;`
- L99 _public prototype_ `void SetSourceAnimInstance(UAnimInstance* SourceAnimInstance, FAnimInstanceProxy* SourceAnimInputProxy);` — Anim Instance Source info - created externally and used here
- L100 _public function_ `UAnimInstance* GetSourceAnimInstance() const`
- L102 _public prototype_ `void SetMixerTask(TSharedPtr<FAnimNextEvaluationTask> InEvalTask);`
- L103 _public prototype_ `void LinkSourcePose(UAnimInstance* InInputInstance, FAnimInstanceProxy* InInputProxy);`
- L104 _public prototype_ `void UnlinkSourcePose();`
- L106 _public prototype_ `void StagePendingNotifyBatches(TArray<FSequencerMixerPendingNotifyBatch>&& InBatches);`
- L111 _protected member_ `TObjectPtr<UAnimInstance> CurrentSourceAnimInstance;` — Source Anim Instance
- L112 _protected member_ `FAnimInstanceProxy* CurrentSourceProxy = nullptr;`
- L115 _protected member_ `FPoseLink SourcePose;` — Optional link to root node if the source anim instance exists and has one
- L118 _protected member_ `TSharedPtr<FAnimNextEvaluationTask> MixerTask;` — Pointer to the task passed from the mixer.
- L121 _protected member_ `TArray<FSequencerMixerPendingNotifyBatch> PendingNotifyBatches;` — One batch per active section's PendingNotifies, with that section's effective blend weight.

#### class `UMovieSceneAnimInstanceTargetSystem`  
`class UMovieSceneAnimInstanceTargetSystem : public UMovieSceneEntitySystem`  
_L129-148_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that handles applying animation mixer evaluation tasks to a custom anim instance on a skeletal mesh component.
- L136 _public prototype_ `UMovieSceneAnimInstanceTargetSystem(const FObjectInitializer& ObjInit);`
- L141 _public member_ `TArray<FDelegateHandle> PreCompileHandles;`
- L146 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

#### Free symbols / members of external scopes

- L26 _function_ `inline friend uint32 GetTypeHash(const FMovieSceneAnimInstanceTarget& Target)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimMixerMaskSystem.h` (Public)


#### struct `FCachedMaskAssetData`  
`struct FCachedMaskAssetData`  
_L17-27_
- desc: Cached data from a single mask asset. Invalidated when the asset changes.
- L19 _public member_ `TWeakObjectPtr<UUAFBlendMask> BlendMask;`
- L20 _public member_ `TArray<float> DampingValues;`
- L21 _public member_ `TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight> AttributeDampingValues;`
- L23 _public member_ `TMap<FName, float> CurveDampingValues;` — Curve damping cached as name→damping pairs
- L25 _public prototype_ `void CacheFromAsset(UUAFBlendMask* InBlendMask);`
- L26 _public prototype_ `bool IsStale(const UUAFBlendMask* InBlendMask) const;`

#### struct `FMaskLayerAccumulation`  
`struct FMaskLayerAccumulation`  
_L30-59_
- desc: Per-{BoundObject, MixerLayer} accumulation state for mask blending.
- L32 _public member_ `UE::MovieScene::FMovieSceneEntityID OutputEntityID;`
- L33 _public member_ `TWeakObjectPtr<USkeleton> MaskSkeleton;`
- L36 _public member_ `TArray<float> AccumulationBoneWeights;` — Damping values accumulated from all contributing mask sections, weighted by easing
- L37 _public member_ `TMap<FName, float> CurveWeightsMap;`
- L38 _public member_ `TMap<UE::Anim::FAttributeId, float> AttributeWeightsMap;`
- L42 _public member_ `TArray<float> TaskBoneWeights;` — Final task data arrays (reused across frames to avoid allocation). These must persist past BuildBlendTask since the task holds pointers to them.
- L43 _public member_ `TArray<FBlendProfileStandaloneCachedData::FMaskedAttributeWeight> TaskAttributeWeights;`
- L44 _public member_ `UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement> TaskCurveWeights;`
- L47 _public member_ `TMap<TObjectKey<UUAFBlendMask>, FCachedMaskAssetData> CachedAssets;` — Cached per-asset data for contributing mask sections
- L50 _public member_ `int32 NumContributingSections = 0;` — Number of contributing mask sections this frame
- L52 _public member_ `TWeakObjectPtr<UUAFBlendMask> SingleContributingMask;` — For the single-section fast path: the mask that contributed this frame
- L54 _public member_ `bool bSingleSectionFullWeight = false;` — True if the single section fast path can be used
- L56 _public prototype_ `void ResetAccumulation();`
- L57 _public prototype_ `void AccumulateMask(UUAFBlendMask* BlendMask, double EasingWeight);`
- L58 _public prototype_ `TSharedPtr<FAnimNextEvaluationTask> BuildBlendTask(float LayerWeight);`

#### struct `FMaskLayerKey`  
`struct FMaskLayerKey`  
_L62-76_
- desc: Key for the accumulation map
- L64 _public member_ `FObjectKey BoundObjectKey;`
- L65 _public member_ `TWeakObjectPtr<UMovieSceneAnimationMixerLayer> MixerLayer;`

#### class `UMovieSceneAnimMixerMaskSystem`  
`class UMovieSceneAnimMixerMaskSystem : public UMovieSceneEntitySystem`  
_L82-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: Gathers mask section entities and produces layer blend task entities for the mixer. Runs before the mixer system. Creates one output entity per {BoundObject, MixerLayer} that has active mask sections, with a LayerBlendTask component.
- L87 _public prototype_ `UMovieSceneAnimMixerMaskSystem(const FObjectInitializer& ObjInit);`
- L90 _private member_ `TMap<FMaskLayerKey, FMaskLayerAccumulation> Accumulations;`
- L92 _private prototype_ `void UpdateAccumulationLifetimes();`
- L94 _private prototype_ `virtual void OnLink() override;`
- L95 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L96 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L97 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L98 _private prototype_ `virtual void OnCleanTaggedGarbage() override;`

#### Free symbols / members of external scopes

- L67 _function_ `friend bool operator==(const FMaskLayerKey& A, const FMaskLayerKey& B)`
- L72 _function_ `friend uint32 GetTypeHash(const FMaskLayerKey& Key)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimMixerSystem.h` (Public)


#### struct `FMovieSceneAnimBusTarget`  
`struct FMovieSceneAnimBusTarget : public FMovieSceneMixedAnimationTarget`  
_L32-64_
- reflection: `USTRUCT(meta=(DisplayName="Bus Target"))`
- inherits: `FMovieSceneMixedAnimationTarget`
- desc: Target type that writes the mixer's evaluated pose to a named bus. Other mixers can then read from the bus via UMovieSceneAnimBusSection.
- L37 _public member_ `FName BusName;` — `UPROPERTY(EditAnywhere, Category="Animation")`
- L44 _public function_ `FMovieSceneAnimBusTarget(FName InBusName) : BusName(InBusName)`
- L49 _public function_ `FMovieSceneAnimBusTarget() : BusName(NAME_None)`
- L55 _public function_ `virtual FText GetShortDisplayName() const override`

#### struct `FMovieSceneAnimMixerEntry`  
`struct FMovieSceneAnimMixerEntry`  
_L68-123_
- L71 _public member_ `TWeakPtr<FMovieSceneAnimMixer> WeakMixer;`
- L72 _public member_ `TSharedPtr<FAnimNextEvaluationTask> EvalTask;`
- L76 _public member_ `TSharedPtr<FMovieSceneMixerRootMotionComponentData> RootMotionLifetimeReference;` — Shared pointer to the root motion for this entry if it came from a FMovieSceneRootMotionSettings on a mixer @note: Only to be used for lifetime management to keep FMovieSceneAnimMixer::WeakRootMotion alive! This may be null even if the result of the mix still has root motion
- L77 _public member_ `TOptional<FMovieSceneRootMotionSettings> RootMotionSettings;`
- L79 _public member_ `double CombinedWeight = 1.0;` — Combined weight and easing (WeightResult * EasingResult). Used for backwards-compat weighted average.
- L81 _public member_ `double EasingWeight = 1.0;` — Easing-only weight from section overlap. Controls intra-layer blending when using mixer track.
- L83 _public member_ `double SectionWeight = 1.0;` — Section weight (from weight channel). Contributes to inter-layer blend weight.
- L84 _public member_ `int32 Priority = 0;`
- L85 _public member_ `bool bAdditive = false;`
- L86 _public member_ `bool bSkipPoseWeight = false;`
- L91 _public member_ `bool bPreBakeRootMotion = false;` — True when this entry's eval task reads bone[0] from the previous pose on the stack (layered Control Rigs). The mixer brackets such tasks with a bake-into-bone[0] before and an extract or reset after to maintain the bone[0]=identity / attribute-populated invariant downstream layers rely on.
- L92 _public member_ `TObjectPtr<UMirrorDataTable> MirrorTable;`
- L93 _public member_ `UE::MovieScene::FMovieSceneEntityID EntityID;`
- L94 _public member_ `UE::MovieScene::FInstanceHandle InstanceHandle;`
- L96 _public member_ `FObjectKey EntityOwner;` — The section or track that owns this entity - used for transition section lookups
- L98 _public member_ `TWeakObjectPtr<UMovieSceneAnimationMixerLayer> MixerLayer;` — The mixer layer this entry belongs to (null for backwards-compat standalone tracks)
- L100 _public member_ `bool bIsTransition = false;` — True if this entry is from a transition section
- L103 _public member_ `TOptional<FTransform> BoneMatchTransform;` — Bone match transform for this entry (set only when a valid match exists)
- L108 _public member_ `TArray<FAnimNotifyEventReference> PendingNotifies;` — Per-section anim-notify references for this frame's evaluation window. Filled by FUpdateTaskEntities; moved out by BuildProgramFromEntries onto FMovieSceneAnimMixer::PendingNotifyBatches with a resolved blend weight. Not read directly by target consumer systems.
- L110 _public function_ `inline bool operator<(const FMovieSceneAnimMixerEntry& RHS) const`

#### struct `FMovieSceneAnimMixerKey`  
`struct FMovieSceneAnimMixerKey`  
_L127-143_
- L129 _public member_ `FObjectKey BoundObjectKey;`
- L130 _public member_ `TInstancedStruct<FMovieSceneMixedAnimationTarget> Target;`

#### struct `FMovieSceneAnimMixer`  
`struct FMovieSceneAnimMixer`  
_L147-180_
- L149 _public member_ `UE::MovieScene::FMovieSceneEntityID MixerEntityID;`
- L150 _public member_ `TArray<TWeakPtr<FMovieSceneAnimMixerEntry>> WeakEntries;`
- L151 _public member_ `TSharedPtr<UE::UAF::FEvaluationProgram> EvaluationProgram;`
- L152 _public member_ `TWeakPtr<FMovieSceneMixerRootMotionComponentData> WeakRootMotion;`
- L157 _public member_ `TArray<FSequencerMixerPendingNotifyBatch> PendingNotifyBatches;` — Per-section anim-notify dispatch list, refreshed each frame alongside EvaluationProgram. Each batch carries one section's notifies with its final blend weight (intra-layer normalize * layer weight * exposure factor). Consumers move-and-clear this list.
- L159 _public member_ `TWeakObjectPtr<UMovieSceneAnimationMixerTrack> OwnerTrack;`
- L160 _public member_ `bool bNeedsResort = false;`
- L166 _public function_ `TSharedPtr<FMovieSceneAnimMixerEntry> FindEntryByOwner(const FObjectKey& InOwner) const` — Find a mixer entry by its EntityOwner (the section or track that created it). Used by transition sections to find from/to entries for building transition programs.

#### struct `FMovieSceneAccumulateAbsoluteBlendTask`  
`struct FMovieSceneAccumulateAbsoluteBlendTask : public FAnimNextEvaluationTask`  
_L194-208_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Sequencer weighted average addition blend task This happens to be identical to FAnimNextBlendAddKeyframeWithScaleTask except the operatnds are reversed, so the resulting stack state is: Top = (Top-1) + (Top * ScaleFactor) Note that rotations will not be normalized after this task.
- L198 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FMovieSceneAccumulateAbsoluteBlendTask) static FMovieSceneAccumulateAbsoluteBlendTask Make(float ScaleFactor);`
- L203 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L207 _public member_ `float ScaleFactor = 0.0f;` — `UPROPERTY()` — The scale factor to apply to the keyframe

#### struct `FAnimNextBlendTwoKeyframesPreserveRootMotionTask`  
`struct FAnimNextBlendTwoKeyframesPreserveRootMotionTask : public FAnimNextBlendTwoKeyframesTask`  
_L211-221_
- reflection: `USTRUCT()`
- inherits: `FAnimNextBlendTwoKeyframesTask`
- L215 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextBlendTwoKeyframesPreserveRootMotionTask) static FAnimNextBlendTwoKeyframesPreserveRootMotionTask Make(float InterpolationAlpha);`
- L220 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point

#### struct `FMovieSceneAnimBusStorageKey`  
`struct FMovieSceneAnimBusStorageKey`  
_L226-240_
- desc: Key for per-object, per-bus-name storage.
- L228 _public member_ `FObjectKey BoundObjectKey;`
- L229 _public member_ `FName BusName;`

#### struct `FMovieSceneAnimBusData`  
`struct FMovieSceneAnimBusData`  
_L244-252_
- desc: Stored evaluation program for a bus-target mixer. Executed inline in the consuming mixer's VM so the pose is evaluated in the correct context.
- L246 _public member_ `TSharedPtr<UE::UAF::FEvaluationProgram> Program;`
- L249 _public member_ `bool bHasRootMotion = false;` — True if the bus-target mixer has entries with root motion settings.
- L251 _public function_ `bool IsValid() const`

#### class `UMovieSceneAnimMixerSystem`  
`class UMovieSceneAnimMixerSystem : public UMovieSceneEntitySystem`  
_L260-355_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: Takes in evaluation tasks with optional pose weight, masks, priority and a given animation target. Constructs a hierarchical 'mixer' per bound object per target. Similar to blender systems, in a 'many to one' operation, each mixer will create an entity with a single evaluation task wrapping the full blend operation, with the target component. This entity is then consumed by the appropriate target animation system in order to produce the result on the mesh.
- L267 _public prototype_ `UMovieSceneAnimMixerSystem(const FObjectInitializer& ObjInit);`
- L269 _public prototype_ `static TInstancedStruct<FMovieSceneMixedAnimationTarget> ResolveAnimationTarget(FObjectKey ObjectKey, const TInstancedStruct<FMovieSceneMixedAnimationTarget>& InTarget, const FMovieSceneSkeletalAnimationComponentData* SkelAnimData = nullptr);`
- L271 _public prototype_ `TSharedPtr<FMovieSceneMixerRootMotionComponentData> FindRootMotion(FObjectKey InObject) const;`
- L272 _public prototype_ `void AssignRootMotion(FObjectKey InObjectKey, TSharedPtr<FMovieSceneMixerRootMotionComponentData> RootMotion);`
- L276 _public prototype_ `void UpdateRootMotionOffset(UObject* InObject);` — Re-bases the root motion baseline for an object after it has been manually moved and keyed, so the next evaluation doesn't re-apply root motion on top of the previous baseline.
- L279 _public prototype_ `TSharedPtr<FMovieSceneAnimMixer> FindMixer(const FMovieSceneAnimMixerKey& InKey) const;` — Look up a mixer by (bound object, target).
- L283 _public prototype_ `static TArray<FSequencerMixerPendingNotifyBatch> ConsumeMixerNotifyBatches( UMovieSceneEntitySystemLinker* Linker, UObject* BoundObject, const TInstancedStruct<FMovieSceneMixedAnimationTarget>& Target);` — Move-and-erase the per-frame notify dispatch list from the mixer keyed by (BoundObject, Target). Empty when no mixer exists or no batches were produced this frame.
- L289 _public prototype_ `UMovieSceneAnimationMixerLayer* FindMixerLayer( TFunctionRef<bool(UMovieSceneAnimationMixerLayer*)> Predicate) const;` — Iterate all mixer layers known to this system and return the first one matching the predicate.
- L292 _public prototype_ `void PreInitializeAllRootMotion();`
- L293 _public prototype_ `void InitializeAllRootMotion();`
- L298 _public prototype_ `void StoreBusData(FObjectKey BoundObject, FName BusName, TSharedPtr<FMovieSceneAnimBusData> Data);` — Store a pose result into the named bus for the given bound object
- L301 _public prototype_ `TSharedPtr<FMovieSceneAnimBusData> ReadBusData(FObjectKey BoundObject, FName BusName) const;` — Read a stored bus pose for the given bound object and bus name (returns null if not written this frame)
- L304 _public prototype_ `void ClearBusStorage();` — Clear all bus storage (called at the start of each evaluation frame)
- L313 _public prototype_ `FBusTopologyCache& GetOrCreateBusTopology(FObjectKey ObjectKey);`
- L314 _public prototype_ `void RemoveStaleBusTopologies(const TSet<FObjectKey>& ActiveObjects);`
- L320 _public prototype_ `static void PushForceRootBoneDestinationScope();` — Force-root-bone scope: while the counter is non-zero, normal (non-bus, non-bake-target) mixer programs flip bForceRootBoneDestination on their FAnimNextStoreRootTransformTask. Used by the binding-level Bake to Control Rig flow so the recorder captures root motion on the root bone rather than having it applied to the actor.
- L321 _public prototype_ `static void PopForceRootBoneDestinationScope();`
- L322 _public prototype_ `static bool IsForceRootBoneDestinationScopeActive();`
- L327 _private member_ `TMap<FMovieSceneAnimMixerKey, TSharedPtr<FMovieSceneAnimMixer>> Mixers;` — Map of animation mixers
- L331 _private member_ `TMap<FMovieSceneAnimBusStorageKey, TSharedPtr<FMovieSceneAnimBusData>> BusStorage;` — Bus storage: per-object, per-bus-name pose data written by bus-target mixers and read by bus sections. Cleared at the start of each evaluation frame.
- L333 _private member_ `TMap<FObjectKey, FBusTopologyCache> BusTopologyByObject;`
- L336 _private member_ `TMap<FObjectKey, TWeakPtr<FMovieSceneMixerRootMotionComponentData>> RootMotionByObject;` — Map of Root Motion data for each object
- L339 _private member_ `TMultiMap<FObjectKey, TWeakPtr<FMovieSceneMixerRootMotionComponentData>> ActorToRootMotion;` — Map from actor to all the root motions that may contribute to the actor's transform
- L341 _private prototype_ `virtual void OnLink() override;`
- L342 _private prototype_ `virtual void OnUnlink() override;`
- L343 _private prototype_ `virtual bool IsRelevantImpl(UMovieSceneEntitySystemLinker* InLinker) const override;`
- L344 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L345 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L346 _private prototype_ `virtual void OnCleanTaggedGarbage() override;`
- L348 _private prototype_ `void HandlePreFlush(UMovieSceneEntitySystemLinker* InLinker);`
- L351 _private member_ `TObjectPtr<UMovieSceneRootMotionSystem> RootMotionSystem;` — `UPROPERTY()`
- L353 _private member_ `FDelegateHandle PreFlushHandle;`
- L354 _private member_ `bool bInsidePreFlush = false;`

#### struct `UMovieSceneAnimMixerSystem::FBusTopologyCache`  
`struct FBusTopologyCache`  
_L307-311_
- desc: Cached bus evaluation order per bound object
- L309 _public member_ `TArray<FName> EvalOrder;`
- L310 _public member_ `bool bDirty = true;`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace UAF` (scope `UE`)
- L39 _function_ `inline friend uint32 GetTypeHash(const FMovieSceneAnimBusTarget& Target)`
- L133 _function_ `friend bool operator==(const FMovieSceneAnimMixerKey& A, const FMovieSceneAnimMixerKey& B)` — Equality operator
- L139 _function_ `friend uint32 GetTypeHash(const FMovieSceneAnimMixerKey& AnimMixerKey)` — Generate a type hash from this component
- L231 _function_ `friend bool operator==(const FMovieSceneAnimBusStorageKey& A, const FMovieSceneAnimBusStorageKey& B)`
- L236 _function_ `friend uint32 GetTypeHash(const FMovieSceneAnimBusStorageKey& Key)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneAnimNextTargetSystem.h` (Public)


#### struct `FMovieSceneAnimMixerEvaluationModifier`  
`struct FMovieSceneAnimMixerEvaluationModifier : public UE::UAF::IEvaluationModifier`  
_L16-30_
- inherits: `UE::UAF::IEvaluationModifier`
- L18 _public function_ `FMovieSceneAnimMixerEvaluationModifier(TSharedPtr<FAnimNextEvaluationTask> InTaskToInject) : TaskToInject(InTaskToInject)`
- L24 _public function_ `virtual void PreEvaluate(UE::UAF::FEvaluateTraversalContext& Context) const override` — IEvaluationModifier interface
- L26 _public prototype_ `virtual void PostEvaluate(UE::UAF::FEvaluateTraversalContext& Context) const override;`
- L28 _public member_ `TSharedPtr<FAnimNextEvaluationTask> TaskToInject = nullptr;`

#### struct `FMovieSceneAnimNextInjectionTarget`  
`struct FMovieSceneAnimNextInjectionTarget : public FMovieSceneMixedAnimationTarget`  
_L36-80_
- reflection: `USTRUCT(meta=(DisplayName="UAF Module Injection"))`
- inherits: `FMovieSceneMixedAnimationTarget`
- desc: Declaring a unique target for targeting an injection site on an Unreal Animation Framework module. Will find the default injection site, or one specified by name.
- L40 _public function_ `FMovieSceneAnimNextInjectionTarget(const FAnimNextSoftVariableReference& InVariableReference) : InjectionSite(InVariableReference)`
- L46 _public function_ `FMovieSceneAnimNextInjectionTarget() : InjectionSite()`
- L54 _public member_ `FName InjectionSiteName_DEPRECATED;` — `UPROPERTY()`
- L58 _public member_ `FAnimNextVariableReference InjectionSite;` — `UPROPERTY(EditAnywhere, Category="Animation", meta = (AllowedType = "FAnimNextAnimGraph"))` — Site to use for injection. If empty will use the default one found for the actor.
- L66 _public prototype_ `bool Serialize(FArchive& Ar);`
- L67 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L71 _public function_ `virtual FText GetShortDisplayName() const override`

#### struct `FMovieSceneAnimNextTargetData`  
`struct FMovieSceneAnimNextTargetData`  
_L82-88_
- L84 _public member_ `TWeakObjectPtr<UUAFComponent> AnimNextComponent = nullptr;`
- L85 _public member_ `UE::UAF::FInjectionSite InjectionSite;`
- L86 _public member_ `UE::UAF::FInjectionRequestPtr InjectionRequestHandle = nullptr;`
- L87 _public member_ `TSharedPtr<FMovieSceneAnimMixerEvaluationModifier> Modifier = nullptr;`

#### class `UMovieSceneAnimNextTargetSystem`  
`class UMovieSceneAnimNextTargetSystem : public UMovieSceneEntitySystem`  
_L92-110_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: System that handles applying animation mixer evaluation tasks to an injection site in an Unreal Animation Framework module
- L99 _public prototype_ `UMovieSceneAnimNextTargetSystem(const FObjectInitializer& ObjInit);`
- L101 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L103 _public prototype_ `void OnUnlink() override;`
- L105 _public member_ `TArray<FMovieSceneAnimNextTargetData> CurrentTargets;`
- L109 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

#### Free symbols / members of external scopes

- L60 _function_ `inline friend uint32 GetTypeHash(const FMovieSceneAnimNextInjectionTarget& Target)`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneMixedSkeletalAnimationSystem.h` (Public)


#### struct `FMixedAnimSkeletalAnimationData`  
`struct FMixedAnimSkeletalAnimationData`  
_L21-49_
- reflection: `USTRUCT()`
- L26 _public member_ `TWeakObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY()`
- L29 _public member_ `TOptional<FSkeletalAnimationRootMotionOverride> RootMotionOverride;` — `UPROPERTY()`
- L32 _public member_ `double FromPosition = -1.0f;` — `UPROPERTY()`
- L35 _public member_ `double ToPosition = -1.0f;` — `UPROPERTY()`
- L38 _public member_ `bool bFireNotifies = true;` — `UPROPERTY()`
- L41 _public member_ `bool bAdditive = false;` — `UPROPERTY()`
- L44 _public member_ `bool bSuppressForceRootLock = false;` — `UPROPERTY()`
- L48 _public member_ `TArray<FAnimNotifyEventReference> PendingNotifies;` — Notifies harvested from the source UAnimSequence for this frame's evaluation window. Not a UPROPERTY: FAnimNotifyEventReference holds raw pointers, not GC references.

#### struct `FMovieSceneSkeletalAnimationEvaluationTask`  
`struct FMovieSceneSkeletalAnimationEvaluationTask : public FAnimNextEvaluationTask`  
_L52-63_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L56 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FMovieSceneSkeletalAnimationEvaluationTask)`
- L62 _public member_ `FMixedAnimSkeletalAnimationData AnimationData;` — `UPROPERTY()`

#### class `UMovieSceneMixedSkeletalAnimationSystem`  
`class UMovieSceneMixedSkeletalAnimationSystem : public UMovieSceneEntityInstantiatorSystem`  
_L67-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntityInstantiatorSystem`
- desc: System to handle creating evaluation tasks from skeletal animation track sections for the anim mixer.
- L74 _public prototype_ `UMovieSceneMixedSkeletalAnimationSystem(const FObjectInitializer& ObjInit);`
- L78 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L79 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneMixerBakeTargetSystem.h` (Public)


#### struct `FMovieSceneMixerBakeTarget`  
`struct FMovieSceneMixerBakeTarget : public FMovieSceneMixedAnimationTarget`  
_L24-35_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FMovieSceneMixedAnimationTarget`
- desc: Hidden target struct used during bake evaluation to tell the target system to cache results instead of applying them. Never user-facing.
- L32 _public member_ `int32 ScopeID = 0;` — `UPROPERTY()` — Identifies the owning FBakeEvaluationScope. UPROPERTY so that FMovieSceneAnimMixerKey (which hashes the target via reflection over UPROPERTY fields) keys each scope to a distinct mixer entity.
- L34 _public member_ `UE::MovieScene::AnimMixerBakeEvaluation::FBakeFilter Filter;`

#### class `UMovieSceneMixerBakeTargetSystem`  
`class UMovieSceneMixerBakeTargetSystem : public UMovieSceneEntitySystem`  
_L42-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: Entity system that captures mixer evaluation results during bake evaluation. When bBakeActive is true, this system executes mixer programs in a temporary VM and stores results (root motion transform + keyframe) instead of applying them to any skeletal mesh.
- L48 _public prototype_ `UMovieSceneMixerBakeTargetSystem(const FObjectInitializer& Init);`
- L63 _public member_ `TArray<FBakedResult> BakedResults;` — Accumulated baked results, populated during bake evaluation
- L66 _public member_ `bool bBakeActive = false;` — When true, the system captures results instead of being a no-op
- L70 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`

#### struct `UMovieSceneMixerBakeTargetSystem::FBakedResult`  
`struct FBakedResult`  
_L52-60_
- desc: Result from a single bake evaluation frame. One per mixer entity that matches FMovieSceneMixerBakeTarget during a flush.
- L54 _public member_ `UE::UAF::FLODPoseHeap Pose;`
- L55 _public member_ `FBlendedHeapCurve Curves;`
- L56 _public member_ `UE::Anim::FHeapAttributeContainer Attributes;`
- L57 _public member_ `FTransform RootMotionTransform = FTransform::Identity;`
- L59 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/MovieSceneAnimMixer/Source/MovieSceneAnimMixer/Public/Systems/MovieSceneRootMotionSystem.h` (Public)


#### enum `EMovieSceneRootMotionSource`  
`enum class EMovieSceneRootMotionSource : uint8`  
_L22-29_
- reflection: `UENUM()`
- desc: Which bone to extract root motion from in the pose
- L25 _public enumerator_ `RootBone` — Extract root motion from skeleton bone 0 (standard root motion)
- L28 _public enumerator_ `FirstAnimatedChild` — Auto-detect the first child of root that has animation data. Use when the root bone is static and locomotion lives on a child bone.

#### enum `EMovieSceneRootMotionSpace`  
`enum class EMovieSceneRootMotionSpace : uint8`  
_L33-39_
- reflection: `UENUM()`
- desc: Enum describing what space that root motion should be applied in.
- L36 _public enumerator_ `AnimationSpace` — Root motion should be applied in animation space, meaning that it will be applied on top of the blended transform track and transform origin.
- L38 _public enumerator_ `WorldSpace` — Root motion should be applied in world space, meaning that it will override any transform track or transform origin.

#### enum `EMovieSceneRootMotionTransformMode`  
`enum class EMovieSceneRootMotionTransformMode : uint8`  
_L44-59_
- reflection: `UENUM()`
- desc: Enum describing what space that root motion should be applied in.
- L47 _public enumerator_ `Asset` — Uses root motion exclusively from the asset as is
- L49 _public enumerator_ `Offset` — Adds on the offset field onto the root motion from the asset
- L51 _public enumerator_ `Override` — Uses the offset field as the entire root motion, ignoring root motion from the asset
- L54 _public enumerator_ `AccumulatedOffset` — Uses the accumulated offset from previous KeepState sections as a starting position. The section's own root motion plays on top of this accumulated transform.
- L58 _public enumerator_ `BoneMatch` — Uses a bone-match-derived offset to position the section so a specific bone aligns with the underlying pose at the match time. Set automatically by the bone match dialog. Manual offsets are additive on top.

#### enum `EMovieSceneAnimLoopMode`  
`enum class EMovieSceneAnimLoopMode : uint8`  
_L62-70_
- reflection: `UENUM()`
- L66 _public enumerator_ `Accumulated` — Preserves the section's root bone offset at the loop boundary so the animation continues spatially from where the previous loop ended.
- L69 _public enumerator_ `Reset` — Resets the section's root bone back to its original start position at each loop boundary.

#### struct `FSkeletalAnimationRootMotionOverride`  
`struct FSkeletalAnimationRootMotionOverride`  
_L73-86_
- reflection: `USTRUCT()`
- L78 _public member_ `FTransform RootMotion = FTransform::Identity;` — `UPROPERTY()`
- L81 _public member_ `int32 ChildBoneIndex = INDEX_NONE;` — `UPROPERTY()`
- L85 _public member_ `bool bBlendFirstChildOfRoot = false;` — `UPROPERTY()` — If true we use the ChildBoneIndex otherwise we use the root

#### struct `FMovieSceneRootMotionSettings`  
`struct FMovieSceneRootMotionSettings`  
_L89-118_
- desc: Structure used for animation tracks to communicate to the mixer how they would like root motion handled if at all.
- L91 _public member_ `FVector RootLocation = FVector(EForceInit::ForceInit);`
- L92 _public member_ `FVector RootOriginLocation = FVector(EForceInit::ForceInit);`
- L93 _public member_ `FVector RootOverrideLocation = FVector(EForceInit::ForceInit);`
- L95 _public member_ `FQuat RootRotation = FQuat(EForceInit::ForceInit);`
- L96 _public member_ `FQuat RootOverrideRotation = FQuat(EForceInit::ForceInit);`
- L98 _public member_ `int32 ChildBoneIndex = INDEX_NONE;`
- L101 _public member_ `EMovieSceneRootMotionSpace RootMotionSpace = EMovieSceneRootMotionSpace::AnimationSpace;` — What space to apply root motion in. Defaults to animation space.
- L102 _public member_ `EMovieSceneRootMotionTransformMode TransformMode = EMovieSceneRootMotionTransformMode::Offset;`
- L103 _public member_ `EMovieSceneRootMotionSource RootMotionSource = EMovieSceneRootMotionSource::RootBone;`
- L104 _public member_ `ESwapRootBone LegacySwapRootBone = ESwapRootBone::SwapRootBone_None;`
- L105 _public member_ `EMovieSceneAnimLoopMode LoopMode = EMovieSceneAnimLoopMode::Accumulated;`
- L107 _public member_ `uint8 bHasRootMotionOverride : 1 = 0;`
- L109 _public member_ `uint8 bBlendFirstChildOfRoot : 1 = 0;` — If true we use the ChildBoneIndex otherwise we use the root
- L112 _public member_ `uint8 bForceRootLock : 1 = 0;` — If true, the animation has Force Root Lock + Enable Root Motion. The extraction task handles root locking, and the eval task suppresses the lock during pose evaluation.
- L117 _public member_ `const FMovieSceneDoubleChannel* OffsetChannels[6] = {};` — Offset channels from the root motion settings decoration. Evaluated per-frame by the consumer to populate RootLocation/RootRotation. [0..2] = Location X/Y/Z, [3..5] = Rotation Roll/Pitch/Yaw.

#### struct `FMovieSceneMixerRootMotionComponentData`  
`struct FMovieSceneMixerRootMotionComponentData`  
_L122-174_
- desc: Structure that is shared between entities for handling the mixer's root motion result. As this can get read/written from multiple threads, access is threadsafe.
- L126 _public prototype_ `TOptional<FQuat> GetInverseMeshToActorRotation() const;`
- L128 _public prototype_ `void Initialize();`
- L133 _public prototype_ `void UpdateActorTransformBaseline();` — Re-bases ActorTransform to the object's current position so a subsequent evaluation doesn't apply root motion on top of the stale baseline. Used after the user manually moves and keys the object.
- L137 _public prototype_ `FTransform ConvertWorldSpaceRootToComponentSpace(const FTransform& InWorldSpaceRoot) const;` — Project a world-space root motion transform into the component/bone space the store task writes onto the root bone. No-op unless bComponentSpaceRoot. Exposed so the editor offset gizmo can place its drawn root the way the runtime renders it.
- L141 _public member_ `TWeakObjectPtr<USceneComponent> OriginalBoundObject;`
- L144 _public member_ `TWeakObjectPtr<USceneComponent> Target;` — Where to apply the root motion
- L147 _public member_ `UE::MovieScene::FMovieSceneEntityID MixerEntityID;` — EntityID for the anim mixer
- L149 _public member_ `EMovieSceneRootMotionDestination RootDestination;`
- L151 _public member_ `FTransform ActorTransform;`
- L152 _public member_ `FTransform ComponentToActorTransform;`
- L157 _private member_ `TOptional<FQuat> InverseMeshToActorRotation;` — Optional inverse mesh component to actor rotation used to offset any mesh component rotation where applicable.
- L159 _private member_ `mutable FTransactionallySafeRWLock RootMotionLock;`
- L165 _public member_ `FTransform AppliedRootMotionOffset = FTransform::Identity;` — The root motion offset applied to the component, relative to the actor heading. Stored each evaluation so the transform track editor can subtract it during auto-key.
- L167 _public member_ `bool bComponentSpaceRoot = false;`
- L168 _public member_ `bool bActorTransformSet = false;`
- L171 _public member_ `EMovieSceneRootMotionGapBehavior GapBehavior{};` — Gap behavior fields
- L172 _public member_ `FTransform CachedGapTransform = FTransform::Identity;`
- L173 _public member_ `TWeakObjectPtr<UMovieSceneRootMotionSection> WeakRootMotionSection;`

#### struct `FAnimNextConvertRootMotionToWorldSpaceTask`  
`struct FAnimNextConvertRootMotionToWorldSpaceTask : public FAnimNextEvaluationTask`  
_L178-235_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task that converts the root motion attribute on the top pose of the pose stack to world space by adding on the actor transformation, root base transform, and/or transform origin.
- L204 _public prototype_ `FAnimNextConvertRootMotionToWorldSpaceTask() = default;`
- L205 _public prototype_ `FAnimNextConvertRootMotionToWorldSpaceTask(const TSharedPtr<FMovieSceneMixerRootMotionComponentData>& InRootMotionData, const FTransform& InTransformOrigin, const FTransform& InRootTransform, const FVector& InRootOffsetOrigin, ESpaceConversions InConversions);`
- L207 _public prototype_ `static FAnimNextConvertRootMotionToWorldSpaceTask Make(const TSharedPtr<FMovieSceneMixerRootMotionComponentData>& InRootMotionData, const FTransform& InTransformOrigin, const FTransform& InRootTransform, const FVector& InRootOffsetOrigin, ESpaceConversions InConversions);`
- L209 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L212 _public member_ `TWeakPtr<FMovieSceneMixerRootMotionComponentData> WeakRootMotionData;` — Weak pointer to the root motion data for all mixed animations. May be null if only a transform origin transformation is required.
- L214 _public member_ `FTransform RootTransform;` — Base transformation to apply to the root in Actor space, before transform origins. Can be used in place of a transform track.
- L216 _public member_ `FTransform TransformOrigin;` — Transform origin to apply to the root, if Conversions & ESpaceConversions::TransformOriginToWorld
- L218 _public member_ `FVector RootOffsetOrigin;` — Origin around which to apply RootTransform when space conversion is RootTransformOffset.
- L221 _public member_ `FTransform AnimSpaceAccumulatedTransform;` — Anchor the rotated delta is multiplied by after offset application: the accumulated chain when the section is accumulating, InitialAnimRootTransform otherwise.
- L224 _public member_ `FTransform InitialAnimRootTransform;` — Initial root transform of this section evaluated in isolation at its start time. Used to compute the section-local delta: Delta = N_t * Inv(InitialAnimRootTransform).
- L227 _public member_ `FTransform BoneMatchTransform;` — Bone-match-derived root offset. Applied as post-multiply in animation space so the matched bone aligns with the underlying pose at the match time.
- L229 _public member_ `ESpaceConversions Conversions;` — Bitmask specifying the conversions to perform
- L231 _public member_ `TSharedPtr<FTransform> CaptureAnimSpaceRoot;` — When set (bake only), the pre-conversion animation-space root is written here
- L234 _public member_ `TSharedPtr<FTransform> CaptureAnimSpaceAccumulated;` — When set (bake only), the accumulated/initial-root transform the offset is applied relative to is written here, so editors can map a world drag back to the offset.

#### enum `FAnimNextConvertRootMotionToWorldSpaceTask::ESpaceConversions`  
`enum class ESpaceConversions : uint8`  
_L185-202_
- desc: Enum specifying which conversions to perform
- L187 _public enumerator_ `None = 0`
- L189 _public enumerator_ `AnimationToWorld = 1 << 0` — Convert the root motion from animation space to world space
- L191 _public enumerator_ `TransformOriginToWorld = 1 << 1` — Convert the root motion from transform origin space to world space (used when there is no transform track in Sequencer)
- L193 _public enumerator_ `ComponentToActorRotation = 1 << 2` — Convert the root motion from component -> actor space using the inverse component rotation only
- L195 _public enumerator_ `WorldSpaceComponentTransformCompensation = 1 << 3` — Compensate for component rotation and translation offsets when applying root motion in world space
- L197 _public enumerator_ `RootTransformOffset = 1 << 4` — Apply RootBaseTransform as an offset around RootOffsetOrigin where Root = Root * RootBaseTransform
- L199 _public enumerator_ `RootTransformOverride = 1 << 5` — Completely override the root transform with RootTransform
- L201 _public enumerator_ `BoneMatchOffset = 1 << 7` — Apply bone-match-derived offset to align a specific bone with the underlying pose

#### struct `FAnimNextStoreRootTransformTask`  
`struct FAnimNextStoreRootTransformTask : public FAnimNextEvaluationTask`  
_L242-263_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task that gets the final mixed root transform and stores it in the root motion data for later application. TODO: it's not ideal that we're writing things outside of the animation system during an evaluation task. Consider refactoring this once we have a way to hook into anim next post execution
- L248 _public prototype_ `FAnimNextStoreRootTransformTask() = default;`
- L249 _public prototype_ `FAnimNextStoreRootTransformTask(const TSharedPtr<FMovieSceneMixerRootMotionComponentData>& InRootMotionData, bool bInComponentHasKeyedTransform, bool bInRootComponentHasKeyedTransform);`
- L251 _public prototype_ `static FAnimNextStoreRootTransformTask Make(const TSharedPtr<FMovieSceneMixerRootMotionComponentData>& InRootMotionData, bool bInComponentHasKeyedTransform, bool bInRootComponentHasKeyedTransform);`
- L253 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L255 _public member_ `TWeakPtr<FMovieSceneMixerRootMotionComponentData> WeakRootMotionData;`
- L256 _public member_ `bool bComponentHasKeyedTransform = false;`
- L257 _public member_ `bool bRootComponentHasKeyedTransform = false;`
- L262 _public member_ `bool bForceRootBoneDestination = false;` — When true, forces RootBone destination regardless of the Root Motion Target settings. Used by bus-target mixers to put world-space root motion back onto the root bone so that outer mixers can re-extract and apply it.

#### struct `FAnimNextSetRootTransformAttributeTask`  
`struct FAnimNextSetRootTransformAttributeTask : public FAnimNextEvaluationTask`  
_L274-287_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task that sets the RootTransformAttribute on the top keyframe, creating it if it doesn't exist. Used for gap behavior (PersistPreviousTransform) where we need to inject a cached world-space transform into an empty or non-root-motion pose. Unlike FAnimNextConvertRootMotionToWorldSpaceTask, this doesn't require an existing attribute and performs no space conversion (the gap transform is already in the correct post-conversion space from the trajectory cache).
- L280 _public prototype_ `FAnimNextSetRootTransformAttributeTask() = default;`
- L282 _public prototype_ `static FAnimNextSetRootTransformAttributeTask Make(const FTransform& InTransform);`
- L284 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L286 _public member_ `FTransform Transform;`

#### struct `FAnimNextBakeRootAttributeToBoneTask`  
`struct FAnimNextBakeRootAttributeToBoneTask : public FAnimNextEvaluationTask`  
_L293-306_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Writes the RootTransformAttribute onto the top pose's bone[0] in actor-relative space so a non-consuming eval task (e.g. a layered Control Rig) can read it. Paired with FAnimNextResetRootBoneTask to restore the input pose afterwards.
- L299 _public prototype_ `FAnimNextBakeRootAttributeToBoneTask() = default;`
- L301 _public prototype_ `static FAnimNextBakeRootAttributeToBoneTask Make(const TSharedPtr<FMovieSceneMixerRootMotionComponentData>& InRootMotionData);`
- L303 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L305 _public member_ `TWeakPtr<FMovieSceneMixerRootMotionComponentData> WeakRootMotionData;`

#### struct `FAnimNextResetRootBoneTask`  
`struct FAnimNextResetRootBoneTask : public FAnimNextEvaluationTask`  
_L311-322_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Undoes FAnimNextBakeRootAttributeToBoneTask: targets stack index 1 (the bake's pose, pushed down when a non-consuming eval task ran on top) and resets bone[0] to identity.
- L317 _public prototype_ `FAnimNextResetRootBoneTask() = default;`
- L319 _public prototype_ `static FAnimNextResetRootBoneTask Make();`
- L321 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`

#### struct `FAnimNextExtractRootMotionTask`  
`struct FAnimNextExtractRootMotionTask : public FAnimNextEvaluationTask`  
_L333-346_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Generic root motion extraction task. Reads the top keyframe's pose, extracts root motion from either the root bone or the first animated child of root based on the Source setting, and stores the transform as a RootTransformAttribute. For the root bone, the bone is zeroed in the pose. For a child bone, the delta from the reference pose is extracted and the bone is restored to its reference transform. Inserted into an entry mixer program after the section's eval task and before the space conversion task.
- L339 _public prototype_ `FAnimNextExtractRootMotionTask() = default;`
- L341 _public prototype_ `static FAnimNextExtractRootMotionTask Make(EMovieSceneRootMotionSource InSource);`
- L343 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L345 _public member_ `EMovieSceneRootMotionSource Source = EMovieSceneRootMotionSource::RootBone;`

#### class `UMovieSceneRootMotionSystem`  
`class UMovieSceneRootMotionSystem : public UMovieSceneEntitySystem`  
_L353-371_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneEntitySystem`
- desc: Takes in evaluation tasks on mixers. Mixes just the root motion attributes. Converts it from animation space to either additive actor or component space (based on which attribute used). Writes it out as an additive transform to be mixed alongside other transform track values.
- L360 _public prototype_ `UMovieSceneRootMotionSystem(const FObjectInitializer& ObjInit);`
- L362 _public prototype_ `bool IsTransformKeyed(const FObjectKey& Object) const;`
- L366 _private prototype_ `virtual void OnLink() override;`
- L367 _private prototype_ `virtual void OnRun(FSystemTaskPrerequisites& InPrerequisites, FSystemSubsequentTasks& Subsequents) override;`
- L368 _private prototype_ `virtual void OnSchedulePersistentTasks(UE::MovieScene::IEntitySystemScheduler* TaskScheduler) override;`
- L370 _private member_ `TSet<FObjectKey> ObjectsWithTransforms;`

#### Free symbols / members of external scopes

- L236 _prototype_ `ENUM_CLASS_FLAGS(FAnimNextConvertRootMotionToWorldSpaceTask::ESpaceConversions);`
