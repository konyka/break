# Plugins / UAFPoseSearch

- module root: `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch`
- headers: 19; symbols: 267
- symbol kinds: class=3, externvar=1, function=4, macro=3, member=150, namespace=21, prototype=52, struct=30, typedef=3
- PublicDependencyModuleNames: Chooser, Core, CoreUObject, Engine, EvaluationNotifiesRuntime, HierarchyTableAnimationRuntime, HierarchyTableRuntime, PoseSearch, RigVM, UAF, UAFAnimGraph, UAFAnimNode

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Internal/HistoryCollectorTraitData.h` (Internal)


#### struct `FAnimNextHistoryCollectorTraitSharedData`  
`struct FAnimNextHistoryCollectorTraitSharedData : public FAnimNextTraitSharedData`  
_L15-114_
- reflection: `USTRUCT(meta = (DisplayName = "Pose History"))`
- inherits: `FAnimNextTraitSharedData`
- L21 _public member_ `int32 PoseCount = 2;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin="2"))` — The maximum amount of poses that can be stored
- L25 _public member_ `float SamplingInterval = 0.04f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin="0"))` — how often in seconds poses are collected (if 0, it will collect every update)
- L28 _public member_ `TArray<FBoneReference> CollectedBones;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L31 _public member_ `TArray<FName> CollectedCurves;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L35 _public member_ `bool bResetOnBecomingRelevant = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Reset the pose history if it has become relevant to the graph after not being updated on previous frames.
- L39 _public member_ `bool bStoreScales = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — if true pose scales will be cached, otherwise implied to be unitary scales
- L44 _public member_ `float RootBoneRecoveryTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin="0"))` — time in seconds to recover to the reference skeleton root bone transform by RootBoneTranslationRecoveryRatio and RootBoneRotationRecoveryRatio from any eventual root bone modification. if zero the behaviour will be disabled (Experimental)
- L48 _public member_ `float RootBoneTranslationRecoveryRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin="0", ClampMax="1", EditCondition = "RootBoneRecoveryTime > 0", EditConditionHides))` — ratio to recover to the reference skeleton root bone translation from any eventual root bone modification. zero for no recovery, 1 for full recovery
- L52 _public member_ `float RootBoneRotationRecoveryRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin="0", ClampMax="1", EditCondition = "RootBoneRecoveryTime > 0", EditConditionHides))` — ratio to recover to the reference skeleton root bone rotation from any eventual root bone modification. zero for no recovery, 1 for full recovery
- L61 _public member_ `bool bGenerateTrajectory = false;` — `UPROPERTY(EditAnywhere, Category = Experimental)` — if true Trajectory the pose history node will generate the trajectory using the TrajectoryData parameters instead of relying on the input Trajectory (Experimental)
- L66 _public member_ `FTransformTrajectory Trajectory;` — `UPROPERTY(EditAnywhere, Transient, Category = Settings, meta = (PinShownByDefault, EditCondition="!bGenerateTrajectory", EditConditionHides))` — input Trajectory samples for pose search queries in Motion Matching. These are expected to be in the world space of the SkeletalMeshComponent. the trajectory sample with AccumulatedSeconds equals to zero (Trajectory.Samples[i].AccumulatedSeconds) is the sample of the previous frame of simulation (since MM works by matching the previous character pose)
- L70 _public member_ `float TrajectorySpeedMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (PinHiddenByDefault, ClampMin="0", EditCondition="!bGenerateTrajectory", EditConditionHides))` — Input Trajectory velocity will be multiplied by TrajectorySpeedMultiplier: values below 1 will result in selecting animation slower than requested from the original Trajectory
- L74 _public member_ `int32 TrajectoryHistoryCount = 10;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin = "2", EditCondition = "bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the number of trajectory past (collected) samples
- L78 _public member_ `int32 TrajectoryPredictionCount = 8;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin="2", EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the number of trajectory future (prediction) samples
- L82 _public member_ `float PredictionSamplingInterval = 0.4f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (ClampMin="0.001", EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the sampling interval between trajectory future (prediction) samples
- L86 _public member_ `FName PoseHistoryReferenceVariable;` — `UPROPERTY(EditAnywhere, Category = Experimental)` — Property to store a reference to the PoseHistory struct in
- L90 _public member_ `FPoseSearchTrajectoryData TrajectoryData;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta=(EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, TrajectoryData contains the tuning parameters to generate the trajectory

#### Free symbols / members of external scopes

- L93 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Internal/MotionMatchingTraitData.h` (Internal)


#### struct `FMotionMatchingTraitSharedData`  
`struct FMotionMatchingTraitSharedData : public FAnimNextTraitSharedData`  
_L18-176_
- reflection: `USTRUCT(meta = (DisplayName = "Motion Matching"))`
- inherits: `FAnimNextTraitSharedData`
- L23 _public member_ `TArray<TObjectPtr<const UPoseSearchDatabase>> Databases;` — `UPROPERTY(EditAnywhere, Category = "Default", meta=(FactorySource))`
- L26 _public member_ `FAlphaBlendArgs BlendArguments;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L30 _public member_ `FFloatInterval PoseJumpThresholdTime = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Don't jump to poses of the same segment that are within the interval this many seconds away from the continuing pose.
- L34 _public member_ `float XAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space")` — The location on the x-axis to sample. Used if selection is a blend space.
- L38 _public member_ `float YAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Blend Space")` — The location on the y-axis to sample. Used if selection is a blend space.
- L42 _public member_ `float PoseReselectHistory = 0.3f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0"))` — Prevent re-selection of poses that have been selected previously within this much time (in seconds) in the past. This is across all animation segments that have been selected within this time range.
- L46 _public member_ `bool bShouldSearch = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If set to false, the motion matching node will perform a search only if the continuing pose is invalid. This is useful if you want to stagger searches of different nodes for performance reasons
- L50 _public member_ `float SearchThrottleTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin="0"))` — Minimum amount of time to wait between searching for a new pose segment. It allows users to define how often the system searches, default for locomotion is searching every update, but you may only want to search once for other situations, like jump.
- L54 _public member_ `FFloatInterval PlayRate = FFloatInterval(1.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0.2", ClampMax = "3.0", UIMin = "0.2", UIMax = "3.0"))` — Effective range of play rate that can be applied to the animations to account for discrepancies in estimated velocity between the movement model and the animation.
- L60 _public member_ `bool bShouldUseCachedChannelData = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If set to true, the search of multiple databases with different schemas will try to share pose features data calculated during query build the idea is to be able to share as much as possible the continuing pose features vector across different schemas (and potentially improve performances) defaulted to false to preserve behavior backward compatibility
- L63 _public member_ `FPoseSearchEvent EventToSearch;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))`
- L67 _public member_ `bool bUpdateBlendSpaceInputs = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If set to true, blend space inputs are continuously set based on input pins.
- L71 _public member_ `bool bTrySkipBlendsForBlendSpaces = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — if bTrySkipBlendsForBlendSpaces is true and blendstack is already playing the currently selected blendspace, MM trait will try reusing the same graph by only changing the blend parameters
- L74 _public member_ `float MaxDeltaAssetTimeToTrySkipBlendsForBlendSpaces = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L78 _public member_ `EAnimGroupSynchronizationMode SyncMode = EAnimGroupSynchronizationMode::SynchronizeUsingUniqueGroupName;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The synchronization mode
- L83 _public member_ `EPoseSearchInterruptMode NextUpdateInterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;` — Applied EPoseSearchInterruptMode on the next update that controls the continuing pose search evaluation. This is set back to EPoseSearchInterruptMode::DoNotInterrupt after each update.
- L87 _public member_ `FName MotionMatchingResultVariableName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If set, the motion matching result will be written to this variable
- L90 _public member_ `FName AlignmentTransformVariableName;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L94 _public member_ `FUAFWeakSystemReference MotionMatchingResultSystemReference;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If set along with result variable name, the motion matching result will be written to the variable in this system, otherwise the variable will be written in the module containing the MotionMatchingTrait
- L98 _public member_ `FName MotionMatchingResultVariableNameAlt = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Same as MotionMatchingResultVariableName but for an alternative destination variable
- L102 _public member_ `FUAFWeakSystemReference MotionMatchingResultSystemReferenceAlt;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Same as MotionMatchingResultSystemReference but for an alternative destination variable
- L106 _public member_ `TObjectPtr<UUAFBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Optional blend profile to use when new graph request is made
- L109 _public member_ `TArray<FPoseSearchInteractionAvailability> Availabilities;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L112 _public member_ `bool bValidateResultAgainstAvailabilities = true;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L115 _public member_ `bool bKeepInteractionAlive = false;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L122 _public member_ `bool bEnableWarp = false;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use if bEnableWarp is true and this node is performing an interaction, warp aligment will be caluculated and requested to be applied by the anim root motion provider (IAnimRootMotionProvider interface) set it to false if a different warp aligment strategy is used
- L125 _public member_ `bool bWarpUsingRootBone = true;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L128 _public member_ `float WarpingRotationRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L131 _public member_ `float WarpingTranslationRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L134 _public member_ `FName WarpingRotationCurveName;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`
- L137 _public member_ `FName WarpingTranslationCurveName;` — `UPROPERTY(EditAnywhere, Category = Interaction, meta = (PinHiddenByDefault))`

#### Free symbols / members of external scopes

- L141 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/AnimNextInteractionIslandDependency.h` (Private)


#### struct `UE::PoseSearch::FAnimNextInteractionIslandDependency`  
`struct FAnimNextInteractionIslandDependency : public IInteractionIslandDependency`  
_L15-30_
- inherits: `IInteractionIslandDependency`
- L20 _private prototype_ `virtual bool CanMakeDependency(const UObject* InIslandObject, const UObject* InObject) const override;`
- L21 _private prototype_ `virtual const FTickFunction* FindTickFunction(UObject* InObject) const override;`
- L23 _private prototype_ `virtual void AddPrerequisite(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const override;`
- L24 _private prototype_ `virtual void AddSubsequent(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const override;`
- L25 _private prototype_ `virtual void RemovePrerequisite(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const override;`
- L26 _private prototype_ `virtual void RemoveSubsequent(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const override;`
- L29 _private member_ `static FAnimNextInteractionIslandDependency ModularFeature;` — Single impl for modular feature

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace PoseSearch` (scope `UE::UAF`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/AnimNode/UAFPoseHistoryNode.h` (Private)


#### struct `UE::UAF::FUAFHistoryCollectorPreAnimOp`  
`struct FUAFHistoryCollectorPreAnimOp : public FUAFAnimOp`  
_L19-29_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L24 _public prototype_ `FUAFHistoryCollectorPreAnimOp();`
- L26 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;`
- L28 _public member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory> PoseHistory;`

#### struct `UE::UAF::FUAFHistoryCollectorPostAnimOp`  
`struct FUAFHistoryCollectorPostAnimOp : public FUAFAnimOp`  
_L32-59_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L37 _public prototype_ `FUAFHistoryCollectorPostAnimOp();`
- L39 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;`
- L41 _public member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory> PoseHistory;`
- L42 _public member_ `bool bStoreScales = false;`
- L43 _public member_ `float DeltaTime = 0.f;`
- L44 _public member_ `TWeakObjectPtr<const UObject> HostObject;`
- L47 _public member_ `TWeakObjectPtr<const UObject> AnimContext;`
- L50 _public member_ `int32 PoseCount = 0;`
- L51 _public member_ `float SamplingInterval = 0.f;`
- L52 _public member_ `float RootBoneRecoveryTime = 0.f;`
- L53 _public member_ `float RootBoneTranslationRecoveryRatio = 0.f;`
- L54 _public member_ `float RootBoneRotationRecoveryRatio = 0.f;`
- L57 _public member_ `TArray<FBoneReference> CollectedBones;` — @todo: minimize allocations
- L58 _public member_ `TArray<FName> CollectedCurves;`

#### struct `UE::UAF::FUAFPoseHistoryNode`  
`struct FUAFPoseHistoryNode : public FUAFModifierAnimNode`  
_L61-80_
- inherits: `FUAFModifierAnimNode`
- L63 _public prototype_ `FUAFPoseHistoryNode(FUAFAnimGraphUpdateContext& Context, const FUAFPoseHistoryNodeData& InData);`
- L66 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& GraphContext) override;` — FUAFAnimNode impl
- L69 _public prototype_ `virtual FString GetDebugName() const override;`
- L70 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L74 _private member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory> PoseHistory;`
- L76 _private member_ `FUAFHistoryCollectorPreAnimOp PreAnimOp;`
- L77 _private member_ `FUAFHistoryCollectorPostAnimOp PostAnimOp;`
- L79 _private member_ `const FUAFPoseHistoryNodeData* Data = nullptr;`

#### struct `UE::UAF::FUAFPoseHistoryNodeData`  
`struct FUAFPoseHistoryNodeData : public FUAFModifierAnimNodeData`  
_L84-102_
- reflection: `USTRUCT(DisplayName = "Pose History")`
- inherits: `FUAFModifierAnimNodeData`
- L90 _public member_ `FAnimNextVariableReference PoseHistory;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — todo: this should be some sort of output binding when we build that system
- L94 _public member_ `FAnimNextVariableReference Trajectory;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — todo: this should be some sort of input binding when we build that system
- L98 _public member_ `FAnimNextHistoryCollectorTraitSharedData Settings;` — `UPROPERTY(EditAnywhere, Category = "NodeData")` — Use Trait Shared Data for settings to keep feature set in sync
- L100 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;`
- L101 _public prototype_ `virtual void* GetInterface(FUAFAnimNodeInterfaceId Id) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/HistoryCollectorTrait.h` (Private)


#### struct `FAnimNextHistoryCollectorTask`  
`struct FAnimNextHistoryCollectorTask : public FAnimNextEvaluationTask`  
_L17-42_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L21 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextHistoryCollectorTask) virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L25 _public member_ `UE::PoseSearch::FPoseHistory* PoseHistory = nullptr;`
- L26 _public member_ `bool bStoreScales = false;`
- L27 _public member_ `float DeltaTime = 0.f;`
- L28 _public member_ `TWeakObjectPtr<const UObject> HostObject;`
- L30 _public member_ `TWeakObjectPtr<const UObject> AnimContext;`
- L33 _public member_ `int32 PoseCount = 0;`
- L34 _public member_ `float SamplingInterval = 0.f;`
- L35 _public member_ `float RootBoneRecoveryTime = 0.f;`
- L36 _public member_ `float RootBoneTranslationRecoveryRatio = 0.f;`
- L37 _public member_ `float RootBoneRotationRecoveryRatio = 0.f;`
- L40 _public member_ `TArray<FBoneReference> CollectedBones;` — @todo: minimize allocations
- L41 _public member_ `TArray<FName> CollectedCurves;`

#### struct `UE::UAF::FHistoryCollectorTrait`  
`struct FHistoryCollectorTrait : FAdditiveTrait, IUpdate, IEvaluate, IPoseHistory`  
_L46-76_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate,IPoseHistory`
- L50 _public typedef_ `using FSharedData = FAnimNextHistoryCollectorTraitSharedData;`
- L64 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L65 _public prototype_ `virtual void PostUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L68 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L72 _public prototype_ `virtual void PreEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — @TODO: this is a HACK. We're pushing a task with the pose history so that evaluation modifiers can see the pose history. "Evaluation" modifiers should have an Update callback with Scoped Interface access, just like any other trait.
- L75 _public prototype_ `virtual const UE::PoseSearch::IPoseHistory* GetPoseHistory(FExecutionContext& Context, const TTraitBinding<IPoseHistory>& Binding) const override;` — IPoseHistory impl

#### struct `UE::UAF::FHistoryCollectorTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L52-61_
- inherits: `FTrait::FInstanceData`
- L54 _public function_ `FInstanceData() : PoseHistoryPtr(MakeShareable(new UE::PoseSearch::FGenerateTrajectoryPoseHistory()))`
- L55 _public member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory, ESPMode::ThreadSafe> PoseHistoryPtr;`
- L56 _public member_ `float DeltaTime = 0.f;`
- L59 _public member_ `bool bIsPostEvaluateBeingCalled = true;`

#### struct `FAnimNextHistoryCollectorPreEvaluateTask`  
`struct FAnimNextHistoryCollectorPreEvaluateTask : public FAnimNextEvaluationTask`  
_L80-88_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- L84 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextHistoryCollectorPreEvaluateTask) virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L87 _public member_ `UE::UAF::FHistoryCollectorTrait::FInstanceData* InstanceData = nullptr;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace UE`
- L44 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/MotionMatchingTrait.h` (Private)


#### struct `UE::UAF::FMotionMatchingTrait`  
`struct FMotionMatchingTrait : FAdditiveTrait, IUpdate, IEvaluate, IGarbageCollection`  
_L21-48_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate,IGarbageCollection`
- L25 _public typedef_ `using FSharedData = FMotionMatchingTraitSharedData;`
- L37 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L38 _public prototype_ `virtual void OnBecomeRelevant(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;`
- L41 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L44 _public prototype_ `virtual void AddReferencedObjects(const FExecutionContext& Context, const TTraitBinding<IGarbageCollection>& Binding, FReferenceCollector& Collector) const override;` — IGarbageCollection impl
- L47 _private prototype_ `void PublishResults(const TTraitBinding<IUpdate>& Binding) const;`

#### struct `UE::UAF::FMotionMatchingTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L27-34_
- inherits: `FTrait::FInstanceData`
- L29 _public member_ `FMotionMatchingState MotionMatchingState;`
- L32 _public member_ `bool bIsPostEvaluateBeingCalled = true;`

#### struct `FAnimNextMotionMatchingTask`  
`struct FAnimNextMotionMatchingTask : public FAnimNextEvaluationTask`  
_L53-74_
- reflection: `USTRUCT(Experimental)`
- inherits: `FAnimNextEvaluationTask`
- L57 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextMotionMatchingTask) virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L61 _public member_ `FTransform ComponentTransform = FTransform::Identity;`
- L62 _public member_ `UE::UAF::FMotionMatchingTrait::FInstanceData* InstanceData = nullptr;`
- L63 _public member_ `int32 CurrentResultRoleIndex = INDEX_NONE;`
- L64 _public member_ `bool bWarpUsingRootBone = true;`
- L65 _public member_ `float WarpingRotationRatio = 1.f;`
- L66 _public member_ `float WarpingTranslationRatio = 1.f;`
- L67 _public member_ `FName WarpingRotationCurveName;`
- L68 _public member_ `FName WarpingTranslationCurveName;`
- L72 _public member_ `const UObject* HostObject = nullptr;` — Debug Object for VisualLogger

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/PoseHistoryChooserParameter.h` (Private)


#### struct `FPoseHistoryAnimProperty`  
`struct FPoseHistoryAnimProperty : public FChooserParameterPoseHistoryBase`  
_L13-34_
- reflection: `USTRUCT(DisplayName = "Pose History Anim Param")`
- inherits: `FChooserParameterPoseHistoryBase`
- L20 _public member_ `FName VariableName_DEPRECATED;` — `UPROPERTY()`
- L24 _public member_ `FAnimNextVariableReference Variable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable")`
- L26 _public prototype_ `bool GetValue(FChooserEvaluationContext& Context, FPoseHistoryReference& OutResult) const override;`
- L27 _public prototype_ `bool GetValue(FChooserEvaluationContext& Context, FPoseSearchHistory& OutResult) const override;`
- L28 _public function_ `virtual bool IsBound() const`
- L31 _public prototype_ `bool Serialize(FArchive& Ar);`
- L32 _public prototype_ `void PostSerialize(const FArchive& Ar);`

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/PoseSearchFeatureChannel_DistanceFromAnimNextVar.h` (Private)


#### class `UPoseSearchFeatureChannel_DistanceFromAnimNextVar`  
`class UPoseSearchFeatureChannel_DistanceFromAnimNextVar : public UPoseSearchFeatureChannel_Distance`  
_L10-24_
- reflection: `UCLASS(Experimental, EditInlineNew, Blueprintable, meta = (DisplayName = "Distance Channel (AnimNext Variable)"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel_Distance`
- L16 _private member_ `FName DistanceVariableName_DEPRECATED;` — `UPROPERTY()`
- L20 _private member_ `FAnimNextVariableReference DistanceVariable;` — `UPROPERTY(DisplayName = "Variable", EditAnywhere, Category="Variable")`
- L22 _private prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L23 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/PoseSearchInteractionAlignment.h` (Private)


#### struct `FEvaluationNotify_PoseSearchInteractionAlignment`  
`struct FEvaluationNotify_PoseSearchInteractionAlignment : public FEvaluationNotify_BaseInstance`  
_L10-22_
- reflection: `USTRUCT(Experimental)`
- inherits: `FEvaluationNotify_BaseInstance`
- L14 _public prototype_ `virtual void Start() override;`
- L15 _public prototype_ `virtual void Update(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& InstanceData, UE::UAF::FEvaluationVM& VM) override;`
- L17 _public member_ `FTransform WarpStart = FTransform::Identity;`
- L18 _public member_ `FTransform WarpEnd = FTransform::Identity;`
- L19 _public member_ `float WarpEndTime = 0.f;`
- L20 _public member_ `float WarpCurrentTime = 0.f;`
- L21 _public member_ `bool bFirstFrame = true;`

#### class `UNotifyState_PoseSearchInteractionAlignment`  
`class UNotifyState_PoseSearchInteractionAlignment : public UAnimNotifyState`  
_L25-28_
- reflection: `UCLASS(Experimental, MinimalAPI, BlueprintType, DisplayName="MMI Alignment")`
- inherits: `UAnimNotifyState`

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/PoseSearchResultEmulatorTrait.h` (Private)


#### struct `FPoseSearchResultEmulatorTraitSharedData`  
`struct FPoseSearchResultEmulatorTraitSharedData : public FAnimNextTraitSharedData`  
_L15-69_
- reflection: `USTRUCT(meta = (DisplayName = "Pose Search Result Emulator"))`
- inherits: `FAnimNextTraitSharedData`
- L20 _public member_ `TObjectPtr<UObject> SelectedAnim = nullptr;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L24 _public member_ `FPoseSearchBlueprintResult PoseSearchResult;` — `UPROPERTY(EditAnywhere, Category = Default)` — @TODO: This is a super hack, but we don't have a good way to use TWeakObjectPtr pose search result. Do this for now.
- L27 _public member_ `float SelectedTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L30 _public member_ `float WantedPlayRate = 0.f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L33 _public member_ `bool bLoop = false;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L36 _public member_ `float XAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L39 _public member_ `float YAxisSamplePoint = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L42 _public member_ `FName Role;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L45 _public member_ `FAlphaBlendArgs BlendArguments;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L48 _public member_ `float MaxTimeDeltaAllowed = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Default)`
- L51 _public member_ `bool bDisableRootMotion = false;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### struct `UE::UAF::FPoseSearchResultEmulatorTrait`  
`struct FPoseSearchResultEmulatorTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L74-89_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- L78 _public typedef_ `using FSharedData = FPoseSearchResultEmulatorTraitSharedData;`
- L85 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L88 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FPoseSearchResultEmulatorTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L80-82_
- inherits: `FTrait::FInstanceData`

#### struct `FAnimNextPoseSearchResultEmulatorTask`  
`struct FAnimNextPoseSearchResultEmulatorTask : public FAnimNextEvaluationTask`  
_L94-101_
- reflection: `USTRUCT(Experimental)`
- inherits: `FAnimNextEvaluationTask`
- L98 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextPoseSearchResultEmulatorTask) virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`

#### Free symbols / members of external scopes

- L54 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L71 _namespace_ `namespace UE`
- L71 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/PoseSearchSteerAlongTrajectory.h` (Private)


#### struct `FEvaluationNotify_PoseSearchSteerAlongTrajectory`  
`struct FEvaluationNotify_PoseSearchSteerAlongTrajectory : public FEvaluationNotify_BaseInstance`  
_L10-18_
- reflection: `USTRUCT(Experimental)`
- inherits: `FEvaluationNotify_BaseInstance`
- L14 _public prototype_ `virtual void Start() override;`
- L15 _public prototype_ `virtual void Update(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& InstanceData, UE::UAF::FEvaluationVM& VM) override;`
- L17 _public member_ `FVector AngularVelocity = FVector::ZeroVector;`

#### class `UNotifyState_PoseSearchSteerAlongTrajectory`  
`class UNotifyState_PoseSearchSteerAlongTrajectory : public UAnimNotifyState`  
_L21-37_
- reflection: `UCLASS(Experimental, MinimalAPI, BlueprintType, DisplayName="MMI Steer Along Trajectory")`
- inherits: `UAnimNotifyState`
- L27 _public member_ `FAnimNextVariableReference Trajectory;` — `UPROPERTY(EditAnywhere, Category="Steering")`
- L30 _public member_ `float StartTrajectorySampleTime = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Steering")`
- L33 _public member_ `float EndTrajectorySampleTime = 1.f;` — `UPROPERTY(EditAnywhere, Category="Steering")`
- L36 _public member_ `float SmoothingTime = 1.f;` — `UPROPERTY(EditAnywhere, Category="Steering")`

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_DebugDrawTrajectory.h` (Private)


#### struct `FRigUnit_DebugDrawTrajectory`  
`struct FRigUnit_DebugDrawTrajectory: public FRigUnit_AnimNextBase`  
_L15-45_
- reflection: `USTRUCT(meta = (DisplayName = "Debug Draw Trajectory", Category = "Trajectory", NodeColor = "0, 1, 1", Keywords = "Mover, Trajectory, Debug"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: A debug drawing node to draw a transform trajectory
- L19 _public prototype_ `RIGVM_METHOD() void Execute();`
- L24 _public member_ `FTransformTrajectory Trajectory;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Trajectory", meta = (Input, Output))` — The trajectory to draw
- L28 _public member_ `float DebugThickness = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Trajectory", meta = (Input))` — The line thickness to use for the debug drawing
- L32 _public member_ `float DebugOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Trajectory", meta = (Input))` — The transform offset to use for the debug drawing
- L36 _public member_ `bool Enabled = false;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Trajectory", meta = (Input))` — If False the debug drawing will be skipped
- L40 _public member_ `bool DisplayVelocity = false;` — `UPROPERTY(EditAnywhere, Category = "Debug Draw - Trajectory", meta = (Input))` — Whether to display the velocity of the samples in on screen text
- L44 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_GenerateCharacterMovementComponentTrajectory.h` (Private)


#### struct `FRigUnit_GenerateCharacterMovementComponentTrajectory`  
`struct FRigUnit_GenerateCharacterMovementComponentTrajectory : public FRigUnit_AnimNextBase`  
_L17-63_
- reflection: `USTRUCT(meta = (DisplayName = "Generate Trajectory from Character Movement Component", Category = "Character Movement", NodeColor = "0, 1, 1", Keywords = "Trajectory"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: A utility node to generate a character movement trajectory from a character movement component
- L21 _public prototype_ `RIGVM_METHOD() void Execute();`
- L26 _public member_ `TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The input character movement component to create the trajectory for
- L30 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — This should be the most recent simulation time that was used to get us to our current state
- L34 _public member_ `float HistorySamplingInterval = -1.f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The sampling interval to use for the history
- L38 _public member_ `int32 NumHistorySamples = 30;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The upper limit of samples to use for the history
- L42 _public member_ `float PredictionSamplingInterval = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The interval to use for prediction
- L46 _public member_ `int32 NumPredictionSamples = 15;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The upper limit of samples to use for prediction
- L50 _public member_ `FPoseSearchTrajectoryData TrajectoryData;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input))` — The input trajectory data to use
- L54 _public member_ `FTransformTrajectory InOutTrajectory;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input, Output))` — The resulting trajectory
- L58 _public member_ `float InOutDesiredControllerYawLastUpdate = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Trajectory", meta = (Input, Output))` — The resulting yaw at the last update
- L62 _public member_ `FAnimNextExecuteContext ExecuteContext;` — `UPROPERTY(EditAnywhere, DisplayName = "Execute", Category = "BeginExecution", meta = (Input, Output))` — The execution result

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_GetMotionMatchInteractionConstraint.h` (Private)


#### struct `FRigUnit_GetMotionMatchInteractionConstraint`  
`struct FRigUnit_GetMotionMatchInteractionConstraint : public FRigUnit_AnimNextBase`  
_L10-36_
- reflection: `USTRUCT(meta=(DisplayName="Get Motion Match Interaction Constraint", Category="Animation Graph", NodeColor="0, 1, 1"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets the motion matching interaction constraint property associated to SocketName
- L14 _public prototype_ `RIGVM_METHOD() void Execute();`
- L19 _public member_ `FName SocketName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Socket name associated with the constraint
- L23 _public member_ `bool bCompareOwningActors = false;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — search the constraint for the owning actor instead of using the AnimContext
- L27 _public member_ `float DesiredReach = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — output desired reach for the constraint
- L31 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — output transform for the constraint
- L35 _public member_ `bool IsValid = false;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — validity of the requested constraint

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_MultiAnimGetAnimationAsset.h` (Private)


#### struct `FRigUnit_MultiAnimGetAnimationAsset`  
`struct FRigUnit_MultiAnimGetAnimationAsset : public FRigUnit_AnimNextBase`  
_L13-31_
- reflection: `USTRUCT(meta=(DisplayName="Multi Anim Get Animation Asset", Category="Animation Graph", NodeColor="0, 1, 1", Keywords="MultiAnim"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets anim asset for a particular role from a MultiAnimAsset
- L17 _public prototype_ `RIGVM_METHOD() void Execute();`
- L22 _public member_ `TObjectPtr<UMultiAnimAsset> MultiAnimAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — MultiAnim Asset to search for role on
- L26 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Input))` — Role to search for within the MultiAnimAsset
- L30 _public member_ `TObjectPtr<UAnimationAsset> Result = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (Output))` — Result of the role search in the MultiAnimAsset

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_PoseSearchDatabaseGetTags.h` (Private)


#### struct `FRigUnit_PoseSearchDatabaseGetTags`  
`struct FRigUnit_PoseSearchDatabaseGetTags : public FRigUnit_AnimNextBase`  
_L12-26_
- reflection: `USTRUCT(meta=(DisplayName="Get Database Tags", Category="Pose Search", NodeColor="0, 1, 1", Keywords="PoseSearch"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Get metadata tags for a specified pose search database
- L16 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L21 _public member_ `TObjectPtr<UPoseSearchDatabase> Database;` — `UPROPERTY(EditAnywhere, Transient, Category = "Pose Search", meta = (Input))` — The data base to retrieve the meta data tags from
- L25 _public member_ `TArray<FName> OutTags;` — `UPROPERTY(EditAnywhere, Transient, Category = "Pose Search", meta = (Output))` — The resulting array of meta data tags

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Private/RigUnit_PoseSearchResultGetSelectedDatabase.h` (Private)


#### struct `FRigUnit_PoseSearchResultGetSelectedDatabase`  
`struct FRigUnit_PoseSearchResultGetSelectedDatabase : public FRigUnit_AnimNextBase`  
_L12-26_
- reflection: `USTRUCT(meta=(DisplayName="Get Selected Database ", Category="Pose Search", NodeColor="0, 1, 1", Keywords="PoseSearch"))`
- inherits: `FRigUnit_AnimNextBase`
- desc: Gets selected database from a pose search result
- L16 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L21 _public member_ `FPoseSearchBlueprintResult PoseSearchResult;` — `UPROPERTY(EditAnywhere, Transient, Category = "Pose Search", meta = (Input))` — Role to search for within the MultiAnimAsset
- L25 _public member_ `TObjectPtr<UPoseSearchDatabase> OutDatabase = nullptr;` — `UPROPERTY(EditAnywhere, Transient, Category = "Pose Search", meta = (Output))` — Result of the role search in the MultiAnimAsset

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Public/IPoseHistory.h` (Public)


#### struct `UE::UAF::IPoseHistory`  
`struct IPoseHistory : IScopedTraitInterface`  
_L19-29_
- inherits: `IScopedTraitInterface`
- desc: IPoseHistory
- L21 _public prototype_ `DECLARE_ANIM_TRAIT_INTERFACE(IPoseHistory) virtual const UE::PoseSearch::IPoseHistory* GetPoseHistory(FExecutionContext& Context, const TTraitBinding<IPoseHistory>& Binding) const;`
- L26 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L27 _public prototype_ `virtual const FText& GetDisplayShortName() const override;`

#### struct `UE::UAF::TTraitBinding`  
`template<> struct TTraitBinding<IPoseHistory> : FTraitBinding`  
_L35-44_
- inherits: `FTraitBinding`
- desc: Specialization for trait binding.
- L37 _public function_ `const UE::PoseSearch::IPoseHistory* GetPoseHistory(FExecutionContext& Context) const`
- L43 _protected function_ `const IPoseHistory* GetInterface() const`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFPoseSearch/Source/UAFPoseSearch/Public/PoseHistoryEvaluation.h` (Public)


#### struct `UE::PoseSearch::FPoseHistoryEvaluationHelper`  
`struct FPoseHistoryEvaluationHelper`  
_L12-15_
- L14 _public member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory, ESPMode::ThreadSafe> PoseHistoryPtr = nullptr;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PoseSearch` (scope `UE`)
- L10 _externvar_ `extern const UE::UAF::FEvaluationVMStackName POSEHISTORY_STACK_NAME;` (scope `UE::PoseSearch`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UAF` (scope `UE`)
- L20 _prototype_ `ANIM_NEXT_ENABLE_EVALUATION_STACK_USAGE(TUniquePtr<UE::PoseSearch::FPoseHistoryEvaluationHelper>);` (scope `UE::UAF`)
