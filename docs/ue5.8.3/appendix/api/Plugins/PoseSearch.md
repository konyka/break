# Plugins / PoseSearch

- module root: `Plugins/Animation/PoseSearch/Source/Runtime`
- headers: 63; symbols: 2739
- symbol kinds: class=53, delegate=3, enum=38, enumerator=95, externvar=1, function=419, macro=54, member=778, namespace=66, prototype=1013, struct=153, typedef=47, variable=19
- PrivateDependencyModuleNames: AnimationBlueprintLibrary, AnimationModifiers, AnimationWarpingRuntime, DerivedDataCache, DeveloperSettings, GameplayTags, MotionWarping, RewindDebuggerRuntimeInterface, RigVM, RigVMDeveloper, UnrealEd
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, BlendStack, Chooser, Core, CoreUObject, Engine, TraceLog

### `Plugins/Animation/PoseSearch/Source/Runtime/Private/PoseSearchEigenHelper.h` (Private)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_POSE_SEARCH_EIGEN_DEBUG 1`
- L13 _macro_ `#define UE_POSE_SEARCH_EIGEN_DEBUG 0`
- L19 _macro_ `#define EIGEN_NO_AUTOMATIC_RESIZING` — #define EIGEN_INITIALIZE_MATRICES_BY_NAN
- L35 _macro_ `#define EIGEN_MPL2_ONLY`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace PoseSearch` (scope `UE`)
- L56 _typedef_ `using RowMajorVector = Eigen::Matrix<float, 1, Eigen::Dynamic, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L57 _typedef_ `using RowMajorVectorMap = Eigen::Map<RowMajorVector, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L58 _typedef_ `using RowMajorVectorMapConst = Eigen::Map<const RowMajorVector, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L60 _typedef_ `using RowMajorMatrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L61 _typedef_ `using RowMajorMatrixMap = Eigen::Map<RowMajorMatrix, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L62 _typedef_ `using RowMajorMatrixMapConst = Eigen::Map<const RowMajorMatrix, Eigen::RowMajor>;` (scope `UE::PoseSearch`)
- L64 _typedef_ `using ColMajorMatrix = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>;` (scope `UE::PoseSearch`)
- L65 _typedef_ `using ColMajorMatrixMap = Eigen::Map<ColMajorMatrix, Eigen::ColMajor>;` (scope `UE::PoseSearch`)
- L66 _typedef_ `using ColMajorMatrixMapConst = Eigen::Map<const ColMajorMatrix, Eigen::ColMajor>;` (scope `UE::PoseSearch`)
- L70 _function_ `template<typename EigenDenseBaseDerivedType> FString EigenMatrixToString(const Eigen::DenseBase<EigenDenseBaseDerivedType>& Matrix)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Private/PoseSearchIndex.inl` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace PoseSearch` (scope `UE`)
- L12 _function_ `template <bool bAlignedAndPadded> static FORCEINLINE float CompareFeatureVectors(TConstArrayView<float> A, TConstArrayView<float> B, TConstArrayView<float> WeightsSqrt)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/AnimNode_MotionMatching.h` (Public)


#### struct `FAnimNode_MotionMatching`  
`struct FAnimNode_MotionMatching : public FAnimNode_BlendStack_Standalone`  
_L18-233_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendStack_Standalone`
- L24 _public prototype_ `void SetDatabaseToSearch(UPoseSearchDatabase* InDatabase, EPoseSearchInterruptMode InterruptMode);` — Search InDatabase instead of the Database property on this node. Use InterruptMode to control the continuing pose search
- L27 _public prototype_ `void SetDatabasesToSearch(TConstArrayView<UPoseSearchDatabase*> InDatabases, EPoseSearchInterruptMode InterruptMode);` — Search InDatabases instead of the Database property on the node. Use InterruptMode to control the continuing pose search.
- L30 _public prototype_ `void ResetDatabasesToSearch(EPoseSearchInterruptMode InterruptMode);` — Reset the effects of SetDatabaseToSearch/SetDatabasesToSearch and use the Database property on this node.
- L33 _public prototype_ `void SetInterruptMode(EPoseSearchInterruptMode InterruptMode);` — Use InterruptMode to control the continuing pose search
- L35 _public function_ `const FMotionMatchingState& GetMotionMatchingState() const`
- L37 _public prototype_ `FVector GetEstimatedFutureRootMotionVelocity() const;`
- L39 _public prototype_ `const FAnimNodeFunctionRef& GetOnUpdateMotionMatchingStateFunction() const;`
- L43 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface @todo: implement CacheBones_AnyThread to rebind the schema bones
- L44 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L45 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L46 _public prototype_ `virtual FName GetGroupName() const override;`
- L47 _public prototype_ `virtual EAnimGroupRole::Type GetGroupRole() const override;`
- L48 _public prototype_ `virtual EAnimSyncMethod GetGroupMethod() const override;`
- L49 _public prototype_ `virtual bool GetOverridePositionWhenJoiningSyncGroupAsLeader() const override;`
- L50 _public prototype_ `virtual bool IsLooping() const override;`
- L51 _public prototype_ `virtual bool SetGroupName(FName InGroupName) override;`
- L52 _public prototype_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override;`
- L53 _public prototype_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override;`
- L54 _public prototype_ `virtual bool SetOverridePositionWhenJoiningSyncGroupAsLeader(bool InOverridePositionWhenJoiningSyncGroupAsLeader) override;`
- L57 _public prototype_ `const FVector& GetBlendspaceParameters() const;`
- L58 _public prototype_ `float GetBlendspaceParametersDeltaThreshold() const;`
- L59 _public prototype_ `EBlendStack_BlendspaceUpdateMode GetBlendspaceUpdateMode() const;`
- L62 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;` — FAnimNode_AssetPlayerBase interface
- L63 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L72 _private member_ `FVector BlendParameters = FVector::Zero();` — `UPROPERTY(EditAnywhere, Category = Blendspace, meta = (PinHiddenByDefault, FoldProperty))` — requested blend space blend parameters (if AnimationAsset is a blend space)
- L77 _private member_ `float BlendParametersDeltaThreshold = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Blendspace, meta = (FoldProperty))` — Use this to define a threshold to trigger a new blend when blendspace xy input pins change. By default, any delta will trigger a blend.
- L83 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it.
- L88 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::ExclusiveAlwaysLeader;` — `UPROPERTY(VisibleAnywhere, Category = Sync, meta = (FoldProperty))` — The role this node can assume within the group (ignored if GroupName is not set). Note that this is the role of the output of this node, not of animations contained by it.
- L92 _private member_ `bool bOverridePositionWhenJoiningSyncGroupAsLeader = true;` — `UPROPERTY(VisibleAnywhere, Category = Sync, meta = (FoldProperty, EditCondition = "GroupRole != EAnimGroupRole::TransitionFollower && GroupRole != EAnimGroupRole::AlwaysFollower", EditConditionHides))` — When enabled, acting as the leader, and using marker-based sync, this asset player will not sync to the previous leader's sync position when joining a sync group and before becoming the leader but instead force everyone else to match its position.
- L96 _private member_ `EBlendStack_BlendspaceUpdateMode BlendspaceUpdateMode = EBlendStack_BlendspaceUpdateMode::InitialOnly;` — `UPROPERTY(EditAnywhere, Category = Blendspace, meta = (FoldProperty))` — How we should update individual blend space parameters. See dropdown options tooltips.
- L101 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — How this node will synchronize with other animations. Note that this determines how the output of this node is used for synchronization, not of animations contained by it.
- L105 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L111 _private member_ `TObjectPtr<const UPoseSearchDatabase> Database = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))` — The database to search. This can be overridden by Anim Node Functions such as "On Become Relevant" and "On Update" via SetDatabaseToSearch/SetDatabasesToSearch.
- L115 _private member_ `float BlendTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin="0"))` — Time in seconds to blend out to the new pose. Uses either inertial blending, requiring an Inertialization node after this node, or the internal blend stack, if MaxActiveBlends is greater than zero.
- L119 _private member_ `TObjectPtr<UBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, UseAsBlendProfile = true))` — Set Blend Profiles (editable in the skeleton) to determine how the blending is distributed among your character's bones. It could be used to differentiate between upper body and lower body to blend timing.
- L123 _private member_ `EAlphaBlendOption BlendOption = EAlphaBlendOption::Linear;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — How the blend is applied over time to the bones. Common selections are linear, ease in, ease out, and ease in and out.
- L127 _private member_ `FFloatInterval PoseJumpThresholdTime = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Don't jump to poses of the same segment that are within the interval this many seconds away from the continuing pose.
- L131 _private member_ `float PoseReselectHistory = 0.3f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0"))` — Prevent re-selection of poses that have been selected previously within this much time (in seconds) in the past. This is across all animation segments that have been selected within this time range.
- L135 _private member_ `float SearchThrottleTime = 0.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin="0"))` — Minimum amount of time to wait between searching for a new pose segment. It allows users to define how often the system searches, default for locomotion is searching every update, but you may only want to search once for other situations, like jump.
- L139 _private member_ `FFloatInterval PlayRate = FFloatInterval(1.f, 1.f);` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0.2", ClampMax = "3.0", UIMin = "0.2", UIMax = "3.0"))` — Effective range of play rate that can be applied to the animations to account for discrepancies in estimated velocity between the movement model and the animation.
- L143 _private member_ `float PlayRateMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings | Experimental", meta = (PinHiddenByDefault))` — Experimental: Multiplier applied to the play rate of the selected animation after Motion Matching State has been updated.
- L146 _private member_ `bool bUseInertialBlend = false;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L150 _private member_ `bool bResetOnBecomingRelevant = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Reset the motion matching selection state if it has become relevant to the graph after not being updated on previous frames.
- L154 _private member_ `bool bShouldSearch = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If set to false, the motion matching node will perform a search only if the continuing pose is invalid. This is useful if you want to stagger searches of different nodes for performance reasons
- L160 _private member_ `bool bShouldUseCachedChannelData = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If set to true, the search of multiple databases with different schemas will try to share pose features data calculated during query build the idea is to be able to share as much as possible the continuing pose features vector across different schemas (and potentially improve performances) defaulted to false to preserve behavior backward compatibility
- L164 _private member_ `FPoseSearchEvent EventToSearch;` — `UPROPERTY(EditAnywhere, Category = "Settings | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use
- L168 _private member_ `FMotionMatchingState MotionMatchingState;` — `UPROPERTY(Transient)` — Encapsulated motion matching algorithm and internal state
- L171 _private member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant
- L175 _private member_ `TArray<TObjectPtr<const UPoseSearchDatabase>> DatabasesToSearch;` — `UPROPERTY(Transient)` — List of databases this node is searching.
- L178 _private member_ `EPoseSearchInterruptMode NextUpdateInterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;` — Applied EPoseSearchInterruptMode on the next update that controls the continuing pose search evaluation. This is set back to EPoseSearchInterruptMode::DoNotInterrupt after each update.
- L181 _private member_ `bool bOverrideDatabaseInput = false;` — True if the Database property on this node has been overridden by SetDatabaseToSearch/SetDatabasesToSearch.
- L185 _private member_ `TArray<FPoseSearchInteractionAvailability> Availabilities;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use
- L189 _private member_ `bool bValidateResultAgainstAvailabilities = true;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use
- L193 _private member_ `bool bKeepInteractionAlive = false;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use
- L200 _private member_ `bool bEnableWarp = false;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use if bEnableWarp is true and this node is performing an interaction, warp aligment will be caluculated and requested to be applied by the anim root motion provider (IAnimRootMotionProvider interface) set it to false if a different warp aligment strategy is used
- L206 _private member_ `bool bWarpUsingRootBone = true;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault))` — Experimental, this feature might be removed without warning, not for production use if bWarpUsingRootBone is true, warping will be calculated using the interacting actors previous frame root bone transforms (effective for setups with OffsetRootBone node allowing root bone drifting from capsule) if bWarpUsingRootBone is true, warping will be calculated using the previous frame root transforms (effective root motion driven for setups)
- L211 _private member_ `float WarpingTranslationRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault, ClampMin = "0", ClampMax = "1"))` — Experimental, this feature might be removed without warning, not for production use amount or translation warping to apply
- L216 _private member_ `float WarpingRotationRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Interaction | Experimental", meta = (PinHiddenByDefault, ClampMin = "0", ClampMax = "1"))` — Experimental, this feature might be removed without warning, not for production use amount or rotation warping to apply
- L221 _private member_ `FAnimNodeFunctionRef OnMotionMatchingStateUpdated;` — `UPROPERTY(meta=(FoldProperty))`
- L230 _private member_ `FTransform MeshWithOffset = FTransform::Identity;` — Experimental, this feature might be removed without warning, not for production use
- L232 _private member_ `FTransform MeshWithoutOffset = FTransform::Identity;` — Experimental, this feature might be removed without warning, not for production use

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/AnimNode_PoseSearchHistoryCollector.h` (Public)


#### struct `FAnimNode_PoseSearchHistoryCollector_Base`  
`struct FAnimNode_PoseSearchHistoryCollector_Base : public FAnimNode_Base`  
_L14-150_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L22 _public member_ `int32 PoseCount = 2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin="2"))` — The maximum amount of poses that can be stored
- L26 _public member_ `float SamplingInterval = 0.04f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin="0"))` — how often in seconds poses are collected (if 0, it will collect every update)
- L29 _public member_ `TArray<FBoneReference> CollectedBones;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L32 _public member_ `TArray<FName> CollectedCurves;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L35 _public member_ `bool bInitializeWithRefPose_DEPRECATED = false;` — `UPROPERTY()`
- L39 _public member_ `bool bResetOnBecomingRelevant = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Reset the pose history if it has become relevant to the graph after not being updated on previous frames.
- L43 _public member_ `bool bStoreScales = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — if true pose scales will be cached, otherwise implied to be unitary scales
- L49 _public member_ `float RootBoneRecoveryTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin="0"))` — time in seconds to recover to the reference skeleton root bone transform by RootBoneTranslationRecoveryRatio and RootBoneRotationRecoveryRatio from any eventual root bone modification. if zero the behaviour will be disabled Experimental, this feature might be removed without warning, not for production use
- L53 _public member_ `float RootBoneTranslationRecoveryRatio = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin="0", ClampMax="1", EditCondition = "RootBoneRecoveryTime > 0", EditConditionHides))` — ratio to recover to the reference skeleton root bone translation from any eventual root bone modification. zero for no recovery, 1 for full recovery
- L57 _public member_ `float RootBoneRotationRecoveryRatio = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin="0", ClampMax="1", EditCondition = "RootBoneRecoveryTime > 0", EditConditionHides))` — ratio to recover to the reference skeleton root bone rotation from any eventual root bone modification. zero for no recovery, 1 for full recovery
- L60 _public member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant
- L64 _public member_ `FLinearColor DebugColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = Debug)`
- L70 _public member_ `bool bGenerateTrajectory = false;` — `UPROPERTY(EditAnywhere, Category = Experimental)` — if true Trajectory the pose history node will generate the trajectory using the TrajectoryData parameters instead of relying on the input Trajectory Experimental, this feature might be removed without warning, not for production use
- L76 _public member_ `FPoseSearchQueryTrajectory Trajectory;` — `UE_DEPRECATED(5.6, "Please use TransformTrajectory variable instead.")`
- L84 _public member_ `FTransformTrajectory TransformTrajectory;` — `UPROPERTY(EditAnywhere, Transient, Category = Settings, DisplayName="Trajectory", meta = (PinShownByDefault, EditCondition="!bGenerateTrajectory", EditConditionHides))` — Input Trajectory samples for pose search queries in Motion Matching. These are expected to be in the world space of the SkeletalMeshComponent. the trajectory sample with AccumulatedSeconds equals to zero (Trajectory.Samples[i].AccumulatedSeconds) is the sample of the previous frame of simulation (since MM works by matching the previous character pose)
- L88 _public member_ `float TrajectorySpeedMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta = (PinHiddenByDefault, ClampMin="0", EditCondition="!bGenerateTrajectory", EditConditionHides))` — Input Trajectory velocity will be multiplied by TrajectorySpeedMultiplier: values below 1 will result in selecting animation slower than requested from the original Trajectory
- L92 _public member_ `int32 TrajectoryHistoryCount = 10;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin = "2", EditCondition = "bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the number of trajectory past (collected) samples
- L96 _public member_ `int32 TrajectoryPredictionCount = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin="2", EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the number of trajectory future (prediction) samples
- L100 _public member_ `float PredictionSamplingInterval = 0.4f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (ClampMin="0.001", EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, this is the sampling interval between trajectory future (prediction) samples
- L104 _public member_ `FPoseSearchTrajectoryData TrajectoryData;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta=(EditCondition="bGenerateTrajectory", EditConditionHides))` — if bGenerateTrajectory is true, TrajectoryData contains the tuning parameters to generate the trajectory
- L106 _public member_ `bool bCacheBones = false;`
- L109 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override` — FAnimNode_Base interface
- L110 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L111 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L112 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L113 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L118 _public function_ `const UE::PoseSearch::FPoseHistory* GetPoseHistoryPtr() const` — GetPoseHistory got deprecated in favor of GetPoseHistoryPtr, since FAnimNode_PoseSearchHistoryCollector_Base::PoseHistoryPtr can be invalid during blue print recompilation when the pose history node exists in the graph but on an inactive branch, for instance on a never activated branch of a blend by bool node
- L119 _public function_ `UE::PoseSearch::FPoseHistory* GetPoseHistoryPtr()`
- L122 _public function_ `const UE::PoseSearch::FPoseHistory& GetPoseHistory() const` — `UE_DEPRECATED(5.8, "Use GetPoseHistoryPtr instead")`
- L125 _public function_ `UE::PoseSearch::FPoseHistory& GetPoseHistory()` — `UE_DEPRECATED(5.8, "Use GetPoseHistoryPtr instead")`
- L127 _public function_ `FPoseHistoryReference GetPoseHistoryReference() const`
- L132 _public prototype_ `FAnimNode_PoseSearchHistoryCollector_Base() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables this is a requirement for clang to compile without warnings.
- L133 _public prototype_ `~FAnimNode_PoseSearchHistoryCollector_Base() = default;`
- L134 _public prototype_ `FAnimNode_PoseSearchHistoryCollector_Base(const FAnimNode_PoseSearchHistoryCollector_Base&) = default;`
- L135 _public prototype_ `FAnimNode_PoseSearchHistoryCollector_Base(FAnimNode_PoseSearchHistoryCollector_Base&&) = default;`
- L136 _public prototype_ `FAnimNode_PoseSearchHistoryCollector_Base& operator=(const FAnimNode_PoseSearchHistoryCollector_Base&) = default;`
- L137 _public prototype_ `FAnimNode_PoseSearchHistoryCollector_Base& operator=(FAnimNode_PoseSearchHistoryCollector_Base&&) = default;`
- L142 _public prototype_ `TArray<FBoneIndexType> GetRequiredBones(const USkeletalMeshComponent* SkeletalMeshComponent) const;` — Experimental, this feature might be removed without warning, not for production use
- L146 _protected prototype_ `TArray<FBoneIndexType> GetRequiredBones(const FAnimInstanceProxy* AnimInstanceProxy) const;` — returns an array of skeleton bone indexes (encoded as FBoneIndexType)
- L149 _private member_ `TSharedPtr<UE::PoseSearch::FGenerateTrajectoryPoseHistory, ESPMode::ThreadSafe> PoseHistoryPtr;`

#### struct `FAnimNode_PoseSearchHistoryCollector`  
`struct FAnimNode_PoseSearchHistoryCollector : public FAnimNode_PoseSearchHistoryCollector_Base`  
_L153-168_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_PoseSearchHistoryCollector_Base`
- L159 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (DisplayPriority = 0))`
- L162 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L163 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L164 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L165 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L166 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

#### struct `FAnimNode_PoseSearchComponentSpaceHistoryCollector`  
`struct FAnimNode_PoseSearchComponentSpaceHistoryCollector : public FAnimNode_PoseSearchHistoryCollector_Base`  
_L171-186_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_PoseSearchHistoryCollector_Base`
- L177 _public member_ `FComponentSpacePoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (DisplayPriority = 0))`
- L180 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L181 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L182 _public prototype_ `virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override;`
- L183 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L184 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/Chooser/ChooserParameterPoseHistoryBase.h` (Public)


#### struct `FChooserParameterPoseHistoryBase`  
`struct FChooserParameterPoseHistoryBase : public FChooserParameterBase`  
_L12-18_
- reflection: `USTRUCT()`
- inherits: `FChooserParameterBase`
- L15 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FPoseHistoryReference& OutResult) const`
- L16 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FPoseSearchHistory& OutResult) const`
- L17 _public function_ `virtual bool IsBound() const`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/Chooser/PoseSearchChooserColumn.h` (Public)


#### struct `UE::PoseSearch::FActiveColumnCost`  
`struct FActiveColumnCost`  
_L19-23_
- desc: Experimental, this feature might be removed without warning, not for production use
- L21 _public member_ `int32 RowIndex = INDEX_NONE;`
- L22 _public member_ `float RowCost = 0.f;`

#### struct `UE::PoseSearch::FMapping`  
`struct FMapping`  
_L27-61_
- desc: Experimental, this feature might be removed without warning, not for production use
- L41 _private typedef_ `typedef TArray<FTableCell> FTableCells;`
- L42 _private member_ `TMap<UPoseSearchDatabase*, FTableCells> Map;`
- L46 _public prototype_ `explicit FMapping(UChooserTable* Chooser = nullptr);`
- L47 _public prototype_ `void Init(UChooserTable* Chooser);`
- L48 _public prototype_ `bool Equals(const FMapping& Other) const;`
- L49 _public prototype_ `int32 GetNumIndexesInDatabase(const UPoseSearchDatabase* Database) const;`
- L50 _public prototype_ `int32 FindIndexInDatabase(int32 RowIndex, const FPoseSearchColumn* Column, const UPoseSearchDatabase* Database) const;`
- L51 _public prototype_ `const FPoseSearchDatabaseAnimationAsset* FindDatabaseAnimationAsset(int32 IndexInDatabase, const UPoseSearchDatabase* Database) const;`
- L54 _public prototype_ `void SetAnimationAssetAt(const FPoseSearchDatabaseAnimationAsset& AnimationAsset, int32 IndexInDatabase, const UPoseSearchDatabase* Database);`
- L57 _public prototype_ `int32 GetRowIndex(int32 IndexInDatabase, const UPoseSearchDatabase* Database) const;`
- L58 _public prototype_ `void ApplyMappingToAllColumns();`
- L60 _public prototype_ `static FMapping* FindMapping(UChooserTable* Chooser);`

#### struct `UE::PoseSearch::FMapping::FTableCell`  
`struct FTableCell`  
_L30-39_
- L32 _public member_ `FPoseSearchColumn* Column = nullptr;`
- L33 _public member_ `int32 RowIndex = INDEX_NONE;`
- L35 _public function_ `bool operator == (const FTableCell& Other) const`

#### struct `FPoseHistoryContextProperty`  
`struct FPoseHistoryContextProperty : public FChooserParameterPoseHistoryBase`  
_L67-90_
- reflection: `USTRUCT(Experimental, DisplayName = "Pose History Property Binding")`
- inherits: `FChooserParameterPoseHistoryBase`
- L72 _public member_ `FChooserPropertyBinding Binding;` — `UPROPERTY(EditAnywhere, Meta = (BindingType = "FPoseHistoryReference", BindingAllowFunctions = "true", BindingColor = "StructPinTypeColor"), Category = "Binding")`
- L74 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FPoseHistoryReference& OutResult) const override`
- L79 _public function_ `virtual bool GetValue(FChooserEvaluationContext& Context, FPoseSearchHistory& OutResult) const override`
- L84 _public function_ `virtual bool IsBound() const override`
- L89 _public prototype_ `CHOOSER_PARAMETER_BOILERPLATE();`

#### struct `FPoseSearchColumnRow`  
`struct FPoseSearchColumnRow`  
_L93-107_
- reflection: `USTRUCT(Experimental)`
- L98 _public member_ `FPoseSearchDatabaseAnimationAsset Data;` — `UPROPERTY(EditAnywhere, Category = "Data")`
- L101 _public member_ `TObjectPtr<UPoseSearchDatabase> Database;` — `UPROPERTY(EditAnywhere, Category = "Data")`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchColumnRow> : public TStructOpsTypeTraitsBase2<FPoseSearchColumnRow>`  
_L108-111_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchColumnRow>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L110-110_

#### struct `FPoseSearchColumnRowReflection`  
`struct FPoseSearchColumnRowReflection : public FPoseSearchColumnRow`  
_L114-124_
- reflection: `USTRUCT(Experimental)`
- inherits: `FPoseSearchColumnRow`
- L121 _public member_ `TObjectPtr<UChooserTable> RootChooser;` — `UPROPERTY(EditAnywhere, Category = "Data")`

#### struct `FPoseSearchColumn`  
`struct FPoseSearchColumn : public FChooserColumnBase`  
_L127-262_
- reflection: `USTRUCT(DisplayName = "Pose Match", Meta = (Experimental, Category = "Experimental", Tooltip = "This column filters out all assets except the one which is selected by motion matching query. Results must be AnimationAssets with a PoseSearchBranchIn notify state. It also outputs OutputStartTime to specify the frame which matched pose best. To work as intended it must be placed last (furthest right) in the Chooser so that other filters are applied first."))`
- inherits: `FChooserColumnBase`
- L134 _private member_ `TObjectPtr<UPoseSearchDatabase> InternalDatabase_DEPRECATED;` — `UPROPERTY()`
- L138 _private member_ `TArray<FPoseSearchColumnRow> RowValues;` — `UPROPERTY(VisibleAnywhere, Category = "Data")`
- L141 _private member_ `FPoseSearchColumnRow FallbackValue;` — `UPROPERTY(VisibleAnywhere, Category = "Data")`
- L144 _private member_ `TObjectPtr<UChooserTable> Chooser;` — `UPROPERTY(VisibleAnywhere, Category = "Data")`
- L151 _private member_ `UE::PoseSearch::FMapping Mapping;` — @todo: currently Mapping is duplicated in every FPoseSearchColumn and it'd be nice to store it somewhere in the RootChooserTable only. That would also speed up the complexity of FMapping::FindMapping. structure containing the mapping between (FPoseSearchColumn, RowIndex) to (UPoseSearchDatabase, IndexInDatabase). Not serialized, but generated on PostLoad and regenerated when Chooser->GetRootChooser() properties changes
- L157 _public member_ `float PoseReselectHistory = 0.3f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, ClampMin = "0"))` — @todo: expose it as pinnable parameter Prevent re-selection of poses that have been selected previously within this much time (in seconds) in the past. This is across all animation segments that have been selected within this time range.
- L165 _public member_ `int32 MaxNumberOfResults = 1;` — `UPROPERTY(EditAnywhere, Category = "Data")` — @todo: expose it as pinnable parameter MaxNumberOfResults represent the maximum number of results from the motion matching search. if MaxNumberOfResults <= 0 the column will add ALL the results to the output if bEnableMultiSelection is true, this FPoseSearchColumn will be set as cost column, retrieving multiple results from the MM search (one per chooser table entry) and setting their relative costs to be used with subsequent column such as the FRandomizeColumn for additional results refinements. if bEnableMultiSelection is false, this FPoseSearchColumn will return ONLY the best result, the one with the lowest cost
- L169 _public member_ `FInstancedStruct InterruptMode;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterEnumBase", ToolTip="Applied EPoseSearchInterruptMode controlling the continuing pose search evaluation. Defaulted to EPoseSearchInterruptMode::DoNotInterrupt if not set"), Category = "Data")` — @todo: filter to allow only enums of type EPoseSearchInterruptMode
- L173 _public member_ `FInstancedStruct InputValue;` — `UPROPERTY(EditAnywhere, DisplayName = "Pose History", NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/PoseSearch.ChooserParameterPoseHistoryBase"), Category = "Data")` — Pose History
- L177 _public member_ `FInstancedStruct OutputStartTime;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterFloatBase"), Category = "Output")` — Float output for the start time with the best matching pose
- L181 _public member_ `FInstancedStruct OutputMirror;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterBoolBase"), Category = "Output")` — Bool output for if asset should be mirrored
- L185 _public member_ `FInstancedStruct OutputForceBlendTo;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterBoolBase"), Category = "Output")` — Bool output for suggesting a chooser player to force a blend into the newly selected asset
- L189 _public member_ `FInstancedStruct OutputCost;` — `UPROPERTY(EditAnywhere, NoClear, Meta = (ExcludeBaseStruct, BaseStruct = "/Script/Chooser.ChooserParameterFloatBase"), Category = "Output")` — Float output for the cost of the selected pose
- L191 _public prototype_ `FPoseSearchColumn() = default;`
- L192 _public prototype_ `FPoseSearchColumn(const FPoseSearchColumn& Other);`
- L193 _public prototype_ `FPoseSearchColumn& operator=(const FPoseSearchColumn& Other);`
- L195 _public prototype_ `virtual void PostLoad() override;`
- L197 _public prototype_ `UPoseSearchDatabase* GetDatabase(int32 RowIndex) const;`
- L199 _public prototype_ `void SwitchDatabase(UPoseSearchDatabase* NewDatabase, int32 RowIndex);`
- L202 _public prototype_ `const FPoseSearchColumnRow& GetRowValue(int32 RowIndex) const;`
- L203 _public prototype_ `FPoseSearchColumnRow& EditRowValue(int32 RowIndex);`
- L206 _public prototype_ `static void InsertAnimationAssetAt(const FPoseSearchDatabaseAnimationAsset& AnimationAsset, int32 AnimationAssetIndex, UChooserTable* Chooser, const UPoseSearchDatabase* Database);`
- L207 _public prototype_ `static void RemoveAnimationAssetAt(int32 AnimationAssetIndex, UChooserTable* Chooser, const UPoseSearchDatabase* Database);`
- L208 _public prototype_ `static void SetAnimationAssetAt(const FPoseSearchDatabaseAnimationAsset& AnimationAsset, int32 AnimationAssetIndex, UChooserTable* Chooser, const UPoseSearchDatabase* Database);`
- L209 _public function_ `const UChooserTable* GetChooser() const`
- L212 _public prototype_ `static const FPoseSearchDatabaseAnimationAsset* GetDatabaseAnimationAsset(int32 AnimationAssetIndex, UChooserTable* Chooser, const UPoseSearchDatabase* Database);`
- L213 _public prototype_ `static int32 GetNumAnimationAssets(UChooserTable* Chooser, const UPoseSearchDatabase* Database);`
- L215 _public function_ `UE::PoseSearch::FMapping& GetMapping()`
- L216 _public prototype_ `void UpdateMapping(UE::PoseSearch::FMapping& NewMapping);`
- L218 _public function_ `int32 GetNumRows() const`
- L220 _private function_ `virtual bool HasFilters() const override`
- L221 _private prototype_ `virtual void Filter(FChooserEvaluationContext& Context, const FChooserIndexArray& IndexListIn, FChooserIndexArray& IndexListOut, TArrayView<uint8> ScratchArea) const override;`
- L222 _private function_ `virtual bool HasCosts() const override`
- L223 _private function_ `virtual bool HasOutputs() const`
- L224 _private prototype_ `virtual void SetOutputs(FChooserEvaluationContext& Context, int RowIndex, TArrayView<uint8> ScratchArea) const override;`
- L226 _private prototype_ `virtual int32 GetScratchAreaSize() const override;`
- L227 _private prototype_ `virtual void InitializeScratchArea(TArrayView<uint8> ScratchArea) const override;`
- L228 _private prototype_ `virtual void DeinitializeScratchArea(TArrayView<uint8> ScratchArea) const override;`
- L231 _private prototype_ `virtual void Initialize(UChooserTable* OuterChooser) override;`
- L233 _private member_ `mutable TArray<UE::PoseSearch::FActiveColumnCost> ActiveColumnCosts;`
- L235 _private prototype_ `virtual bool EditorTestFilter(int32 RowIndex) const override;`
- L236 _private prototype_ `virtual float EditorTestCost(int32 RowIndex) const override;`
- L237 _private prototype_ `virtual void SetTestValue(TArrayView<const uint8> Value) override;`
- L239 _private prototype_ `virtual void AddToDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L240 _private prototype_ `virtual void SetFromDetails(FInstancedPropertyBag& PropertyBag, int32 ColumnIndex, int32 RowIndex) override;`
- L242 _private prototype_ `virtual void ReplaceReferences(UObject* ReferenceToReplace, UObject* ReplaceWith) override;`
- L244 _private prototype_ `virtual FName RowValuesPropertyName() override;`
- L245 _private prototype_ `virtual void SetNumRows(int32 NumRows) override;`
- L246 _private prototype_ `virtual void InsertRows(int Index, int Count);`
- L247 _private prototype_ `virtual void DeleteRows(TArrayView<int> RowIndices);`
- L248 _private prototype_ `virtual void MoveRow(int SourceRowIndex, int TargetRowIndex);`
- L249 _private prototype_ `virtual void CopyRow(FChooserColumnBase& SourceColumn, int SourceRowIndex, int TargetRowIndex) override;`
- L250 _private prototype_ `virtual void CopyFallback(FChooserColumnBase& SourceColumn) override;`
- L252 _private function_ `virtual bool AutoPopulates() const override`
- L253 _private prototype_ `virtual void AutoPopulate(int32 RowIndex, UObject* OutputObject) override;`
- L255 _private prototype_ `virtual UScriptStruct* GetInputBaseType() const override;`
- L256 _private prototype_ `virtual const UScriptStruct* GetInputType() const override;`
- L257 _private prototype_ `virtual FInstancedStruct* GetInputValuePtr() override;`
- L258 _private prototype_ `virtual void SetInputType(const UScriptStruct* Type) override;`
- L261 _private prototype_ `virtual FChooserParameterBase* GetInputValue() override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API POSESEARCH_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)
- L24 _prototype_ `FArchive& operator<<(FArchive& Ar, FActiveColumnCost& ActiveColumnCost);` (scope `UE::PoseSearch`)
- L103 _function_ `friend bool operator==(const FPoseSearchColumnRow& A, const FPoseSearchColumnRow& B)`
- L110 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon554848d50103`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/KDTree.h` (Public)


#### enum `UE::PoseSearch::(anonymous)`  
`enum`  
_L18-18_

#### struct `UE::PoseSearch::FKDTree`  
`struct FKDTree`  
_L23-341_
- L308 _public prototype_ `FKDTree(AccessorType Count, AccessorType Dim, const float* Data, AccessorType MaxLeafSize = 16 #if UE_POSE_SEARCH_ENABLE_ITERATIVE_KDTREE_CONSTRUCTION_VALIDATION , bool bUseRecursiveDivideTree = false #endif`
- L313 _public prototype_ `FKDTree();`
- L314 _public prototype_ `FKDTree(const FKDTree& Other);`
- L315 _public prototype_ `FKDTree(FKDTree&& Other);`
- L317 _public prototype_ `~FKDTree();`
- L319 _public prototype_ `FKDTree& operator=(const FKDTree& Other);`
- L320 _public prototype_ `FKDTree& operator=(FKDTree&& Other);`
- L321 _public prototype_ `bool operator==(const FKDTree& Other) const;`
- L323 _public prototype_ `void Reset();`
- L324 _public prototype_ `void Construct(AccessorType Count, AccessorType Dim, const float* Data, AccessorType MaxLeafSize = 16);`
- L326 _public prototype_ `int32 FindNeighbors(FKNNResultSet& Result, TConstArrayView<float> Query) const;`
- L327 _public prototype_ `int32 FindNeighbors(FFilteredKNNResultSet& Result, TConstArrayView<float> Query) const;`
- L328 _public prototype_ `int32 FindNeighbors(FRadiusResultSet& Result, TConstArrayView<float> Query) const;`
- L331 _public prototype_ `int32 FindNeighbors(FKNNMaxHeapResultSet& Result, TConstArrayView<float> Query) const;` — Experimental, this feature might be removed without warning, not for production use
- L333 _public prototype_ `int32 FindNeighbors(FFilteredKNNMaxHeapResultSet& Result, TConstArrayView<float> Query) const;` — Experimental, this feature might be removed without warning, not for production use
- L335 _public prototype_ `int32 FindNeighbors(FRadiusMaxHeapResultSet& Result, TConstArrayView<float> Query) const;` — Experimental, this feature might be removed without warning, not for production use
- L337 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L339 _public member_ `FDataSource DataSource;`
- L340 _public member_ `FKDTreeImplementation* KDTreeImplementation = nullptr;`

#### struct `UE::PoseSearch::FKDTree::FDataSource`  
`struct FDataSource`  
_L25-90_
- L27 _public function_ `FDataSource(AccessorType pointCount, AccessorType pointDim, const float* data) : PointCount((pointDim > 0 && data) ? pointCount : 0) , PointDim(pointDim) , Data(data)`
- L34 _public function_ `~FDataSource()`
- L41 _public prototype_ `FDataSource() = default;`
- L42 _public prototype_ `FDataSource(const FDataSource& Other) = default;`
- L43 _public prototype_ `FDataSource(FDataSource&& Other) = default;`
- L44 _public prototype_ `FDataSource& operator=(const FDataSource& Other) = default;`
- L45 _public prototype_ `FDataSource& operator=(FDataSource&& Other) = default;`
- L46 _public function_ `bool operator==(const FDataSource& Other) const`
- L71 _public function_ `inline AccessorType kdtree_get_point_count() const` — Must return the number of data points
- L74 _public function_ `inline float kdtree_get_pt(const AccessorType idx, const AccessorType dim) const` — this method is called by nanoflann::findNeighbors -> nanoflann::searchLevel, so it has to be as fast as possible
- L81 _public function_ `template <class BBOX> bool kdtree_get_bbox(BBOX& ) const` — Optional bounding-box computation: return false to default to a standard bbox computation loop. Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again. Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
- L83 _public member_ `AccessorType PointCount = 0;`
- L84 _public member_ `AccessorType PointDim = 0;`
- L85 _public member_ `const float* Data = nullptr;`
- L88 _public member_ `bool bUseRecursiveDivideTree = false;`

#### struct `UE::PoseSearch::FKDTree::FKNNResultSet`  
`struct FKNNResultSet`  
_L92-150_
- L94 _public function_ `inline FKNNResultSet(AccessorType InNumNeighbors, TArrayView<AccessorType> InIndexes, TArrayView<float> InDistances, float InitValue = UE_BIG_NUMBER) : Indexes(InIndexes) , Distances(InDistances) , NumNeighbors(InNumNeighbors) , Count(0)`
- L108 _public function_ `inline AccessorType Num() const`
- L113 _public function_ `inline bool full() const`
- L118 _public function_ `inline bool addPoint(float dist, AccessorType index)`
- L143 _public function_ `inline float worstDist() const`
- L146 _protected member_ `TArrayView<AccessorType> Indexes;`
- L147 _protected member_ `TArrayView<float> Distances;`
- L148 _protected member_ `AccessorType NumNeighbors;`
- L149 _protected member_ `AccessorType Count;`

#### struct `UE::PoseSearch::FKDTree::FFilteredKNNResultSet`  
`struct FFilteredKNNResultSet : public FKNNResultSet`  
_L152-172_
- inherits: `FKNNResultSet`
- L154 _public function_ `inline FFilteredKNNResultSet(AccessorType InNumNeighbors, TArrayView<AccessorType> InIndexes, TArrayView<float> InDistances, TConstArrayView<AccessorType> InExcludeFromSearchIndexes = TConstArrayView<AccessorType>()) : FKNNResultSet(InNumNeighbors, InIndexes, InDistances) , ExcludeFromSearchIndexes(InExcludeFromSearchIndexes)`
- L161 _public function_ `inline bool addPoint(float dist, AccessorType index)`
- L171 _protected member_ `TConstArrayView<AccessorType> ExcludeFromSearchIndexes;` — sorted array view

#### struct `UE::PoseSearch::FKDTree::FRadiusResultSet`  
`struct FRadiusResultSet : public FKNNResultSet`  
_L174-189_
- inherits: `FKNNResultSet`
- L176 _public function_ `inline FRadiusResultSet(float Radius, AccessorType InNumNeighbors, TArrayView<AccessorType> InIndexes, TArrayView<float> InDistances) : FKNNResultSet(InNumNeighbors, InIndexes, InDistances, Radius)`
- L181 _public function_ `inline bool addPoint(float dist, AccessorType index)`

#### struct `UE::PoseSearch::FKDTree::FKNNMaxHeapResultSet`  
`struct FKNNMaxHeapResultSet`  
_L192-264_
- desc: Experimental, this feature might be removed without warning, not for production use
- L206 _public function_ `inline FKNNMaxHeapResultSet(TArrayView<FResult> Results, float InitWorstDist = UE_BIG_NUMBER) : MaxHeap(Results) , MaxHeapNum(0) , WorstDist(InitWorstDist)`
- L213 _public function_ `inline int32 Num() const`
- L218 _public function_ `inline bool full() const`
- L223 _public function_ `inline bool addPoint(float dist, AccessorType index)`
- L255 _public function_ `inline float worstDist() const`
- L261 _protected member_ `TArrayView<FResult> MaxHeap;`
- L262 _protected member_ `int32 MaxHeapNum;`
- L263 _protected member_ `float WorstDist;`

#### struct `UE::PoseSearch::FKDTree::FKNNMaxHeapResultSet::FResult`  
`struct FResult`  
_L194-204_
- L196 _public member_ `float Distance;`
- L197 _public member_ `AccessorType Index;`
- L199 _public function_ `inline bool operator()(const FResult& A, const FResult& B) const`

#### struct `UE::PoseSearch::FKDTree::FFilteredKNNMaxHeapResultSet`  
`struct FFilteredKNNMaxHeapResultSet : public FKNNMaxHeapResultSet`  
_L267-287_
- inherits: `FKNNMaxHeapResultSet`
- desc: Experimental, this feature might be removed without warning, not for production use
- L269 _public function_ `inline FFilteredKNNMaxHeapResultSet(TArrayView<FResult> Results, TConstArrayView<AccessorType> InExcludeFromSearchIndexes) : FKNNMaxHeapResultSet(Results) , ExcludeFromSearchIndexes(InExcludeFromSearchIndexes)`
- L276 _public function_ `inline bool addPoint(float dist, AccessorType index)`
- L286 _private member_ `TConstArrayView<AccessorType> ExcludeFromSearchIndexes;` — sorted array view

#### struct `UE::PoseSearch::FKDTree::FRadiusMaxHeapResultSet`  
`struct FRadiusMaxHeapResultSet : public FKNNMaxHeapResultSet`  
_L290-305_
- inherits: `FKNNMaxHeapResultSet`
- desc: Experimental, this feature might be removed without warning, not for production use
- L292 _public function_ `inline FRadiusMaxHeapResultSet(TArrayView<FResult> Results, float Radius) : FKNNMaxHeapResultSet(Results, Radius)`
- L297 _public function_ `inline bool addPoint(float dist, AccessorType index)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_POSE_SEARCH_ENABLE_ITERATIVE_KDTREE_CONSTRUCTION_VALIDATION ENABLE_ANIM_DEBUG`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)
- L18 _enumerator_ `enum { AccessorTypeMax = INT_MAX }; typedef int32 AccessorType; struct FKDTreeImplementation; struct FKDTree { struct FDataSource` (scope `UE::PoseSearch::__anonca3710640103`)
- L19 _typedef_ `typedef int32 AccessorType;` (scope `UE::PoseSearch`)
- L343 _prototype_ `FArchive& Serialize(FArchive& Ar, FKDTree& KDTree, const float* data);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/MotionMatchingAnimNodeLibrary.h` (Public)


#### struct `FMotionMatchingBlueprintBlendSettings`  
`struct FMotionMatchingBlueprintBlendSettings`  
_L18-38_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public prototype_ `FMotionMatchingBlueprintBlendSettings();`
- L24 _public prototype_ `bool Serialize(FArchive& Ar);`
- L25 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);`
- L28 _public member_ `float BlendTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L31 _public member_ `TObjectPtr<UBlendProfile> BlendProfile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L34 _public member_ `EAlphaBlendOption BlendOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L37 _public member_ `bool bUseInertialBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMotionMatchingBlueprintBlendSettings> : public TStructOpsTypeTraitsBase2<FMotionMatchingBlueprintBlendSettings>`  
_L40-47_
- inherits: `TStructOpsTypeTraitsBase2<FMotionMatchingBlueprintBlendSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L43-46_

#### struct `FMotionMatchingAnimNodeReference`  
`struct FMotionMatchingAnimNodeReference : public FAnimNodeReference`  
_L50-55_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L54 _public typedef_ `typedef FAnimNode_MotionMatching FInternalNodeType;`

#### class `UMotionMatchingAnimNodeLibrary`  
`class UMotionMatchingAnimNodeLibrary : public UBlueprintFunctionLibrary`  
_L59-128_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Motion Matching node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L66 _public prototype_ `static FMotionMatchingAnimNodeReference ConvertToMotionMatchingNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a motion matching node context from an anim node context
- L70 _public function_ `static void ConvertToMotionMatchingNodePure(const FAnimNodeReference& Node, FMotionMatchingAnimNodeReference& MotionMatchingNode, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe, DisplayName = "Convert to Motion Matching Node"))` — Get a motion matching node context from an anim node context (pure)
- L78 _public prototype_ `static void GetMotionMatchingSearchResult(const FMotionMatchingAnimNodeReference& MotionMatchingNode, FPoseSearchBlueprintResult& Result, bool& bIsResultValid);` — `UFUNCTION(BlueprintPure, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe, DisplayName = "Get Motion Matching Search Result"))`
- L82 _public prototype_ `static void GetMotionMatchingBlendSettings(const FMotionMatchingAnimNodeReference& MotionMatchingNode, FMotionMatchingBlueprintBlendSettings& BlendSettings, bool& bIsResultValid);` — `UFUNCTION(BlueprintPure, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe, DisplayName = "Get Motion Matching Blend Settings"))` — Get current blend settings used when blending into a new asset
- L86 _public prototype_ `static void OverrideMotionMatchingBlendSettings(const FMotionMatchingAnimNodeReference& MotionMatchingNode, const FMotionMatchingBlueprintBlendSettings& BlendSettings);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe, DisplayName = "Override Motion Matching Blend Settings"))` — Override current blend settings for motion matching. Note that any pinned parameters will stomp this override on the next update.
- L95 _public prototype_ `static void SetDatabaseToSearch(const FMotionMatchingAnimNodeReference& MotionMatchingNode, UPoseSearchDatabase* Database, EPoseSearchInterruptMode InterruptMode);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe))` — Set the database to search on the motion matching node. This overrides the Database property on the motion matching node. @param MotionMatchingNode - The motion matching node to operate on. @param Database - The database for the motion matching node to search. @param InterruptMode - mode to control the continuing pose search (the current animation that's playing)
- L104 _public prototype_ `static void SetDatabasesToSearch(const FMotionMatchingAnimNodeReference& MotionMatchingNode, const TArray<UPoseSearchDatabase*>& Databases, EPoseSearchInterruptMode InterruptMode);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe))` — Set the database to search on the motion matching node. This overrides the Database property on the motion matching node. @param MotionMatchingNode - The motion matching node to operate on. @param Databases - Array of databases for the motion matching node to search. @param InterruptMode - mode to control the continuing pose search (the current animation that's playing)
- L112 _public prototype_ `static void ResetDatabasesToSearch(const FMotionMatchingAnimNodeReference& MotionMatchingNode, EPoseSearchInterruptMode InterruptMode);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe))` — Clear the effects of SetDatabaseToSearch/SetDatabasesToSearch and resume searching the Database property on the motion matching node. @param MotionMatchingNode - The motion matching node to operate on. @param InterruptMode - mode to control the continuing pose search (the current animation that's playing)
- L120 _public prototype_ `static void SetInterruptMode(const FMotionMatchingAnimNodeReference& MotionMatchingNode, EPoseSearchInterruptMode InterruptMode);` — `UFUNCTION(BlueprintCallable, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe))` — Ignore the continuing pose (the current clip that's playing) and force a new search. @param MotionMatchingNode - The motion matching node to operate on. @param InterruptMode - mode to control the continuing pose search (the current animation that's playing)
- L127 _public prototype_ `static bool AnyNewBlendToThisFrame(const FMotionMatchingAnimNodeReference& MotionMatchingNode);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|MotionMatching", meta = (BlueprintThreadSafe))` — returns true if any new BlendTo API has been called so far during the current frame. BlendTo is the BlendStack API used by the motion matching node to blend into a newly selected animation @param MotionMatchingNode - The motion matching node to operate on.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`
- L44 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon063aefa60103`)
- L45 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anon063aefa60103`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/MultiAnimAsset.h` (Public)


#### class `UMultiAnimAsset`  
`class UMultiAnimAsset : public UObject`  
_L17-49_
- reflection: `UCLASS(MinimalAPI, Abstract, Experimental, BlueprintType, Category = "Animation")`
- inherits: `UObject`
- desc: UObject defining tuples of UAnimationAsset(s) with associated Role(s) and relative transforms from a shared reference system via GetOrigin
- L22 _public prototype_ `[[nodiscard]] virtual bool IsLooping() const PURE_VIRTUAL(UMultiAnimAsset::IsLooping, return false;);`
- L23 _public prototype_ `[[nodiscard]] virtual bool HasRootMotion() const PURE_VIRTUAL(UMultiAnimAsset::HasRootMotion, return false;);`
- L24 _public prototype_ `[[nodiscard]] virtual float GetPlayLength(const FVector& BlendParameters) const PURE_VIRTUAL(UMultiAnimAsset::GetPlayLength, return 0.f;);`
- L27 _public prototype_ `[[nodiscard]] virtual USkeletalMesh* GetPreviewMesh(const FName& Role) const PURE_VIRTUAL(UMultiAnimAsset::GetPreviewMesh, return nullptr;);`
- L30 _public prototype_ `[[nodiscard]] virtual int32 GetNumRoles() const PURE_VIRTUAL(UMultiAnimAsset::GetNumRoles, return 0;);`
- L31 _public prototype_ `[[nodiscard]] virtual FName GetRole(int32 RoleIndex) const PURE_VIRTUAL(UMultiAnimAsset::GetRole, return FName(););`
- L32 _public prototype_ `[[nodiscard]] virtual UAnimationAsset* GetAnimationAsset(const FName& Role) const PURE_VIRTUAL(UMultiAnimAsset::GetAnimationAsset, return nullptr;);`
- L33 _public prototype_ `[[nodiscard]] virtual FTransform GetOrigin(const FName& Role) const PURE_VIRTUAL(UMultiAnimAsset::GetOrigin, return FTransform::Identity;);`
- L40 _public prototype_ `virtual void CalculateWarpTransforms(float Time, float TimeOffset, const TConstArrayView<const FTransform> ActorRootBoneTransforms, TArrayView<FTransform> FullAlignedActorRootBoneTransforms, const TConstArrayView<const UMirrorDataTable*> MirrorDataTables = TConstArrayView<const UMirrorDataTable*>(), const TConstArrayView<TObjectPtr<const UObject>> DebugAnimContexts = TConstArrayView<TObjectPtr<const UObject>>()) const PURE_VIRTUAL(UMultiAnimAsset::CalculateWarpTransforms, );` — calculates the full aligned root bone transforms (FullAlignedActorRootBoneTransforms) at time "Time + TimeOffset" given the current actors root bone transforms (ActorRootBoneTransforms) at "Time" the mirror data tables. DebugAnimContexts can be used to draw debug lines For example if the actors are playing the associated GetAnimationAsset(Role) at time Time, by providing the ActorRootBoneTransforms and an TimeOffset of zero, CalculateWarpTransforms will return the FullAlignedActorRootBoneTransforms should be NOW to be in full alignment. Any TimeOffset > 0 will have the method returning a future FullAlignedActorRootBoneTransforms. This is useful in synergy with Motion Warping to provide a transform to use as full aligment at the ned of the notify state time
- L45 _public function_ `UAnimationAsset* BP_GetAnimationAsset(const FName& Role) const` — `UFUNCTION(BlueprintPure, Category = "Animation", meta=(BlueprintThreadSafe, DisplayName = "Get Animation Asset"))`
- L48 _public function_ `FTransform BP_GetOrigin(const FName& Role) const` — `UFUNCTION(BlueprintPure, Category = "Animation", meta=(BlueprintThreadSafe, DisplayName = "Get Origin"))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseHistoryProvider.h` (Public)


#### class `UE::PoseSearch::FPoseHistoryProvider`  
`class FPoseHistoryProvider : public UE::Anim::IGraphMessage`  
_L16-30_
- inherits: `UE::Anim::IGraphMessage`
- L21 _public function_ `FPoseHistoryProvider(const FAnimNode_PoseSearchHistoryCollector_Base* InHistoryCollector) : HistoryCollector(InHistoryCollector)`
- L24 _public prototype_ `const IPoseHistory& GetPoseHistory() const;` — `UE_DEPRECATED(5.8, "Use GetPoseHistoryPtr instead")`
- L26 _public prototype_ `const IPoseHistory* GetPoseHistoryPtr() const;`
- L29 _private member_ `const FAnimNode_PoseSearchHistoryCollector_Base* HistoryCollector = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API POSESEARCH_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchAnimNotifies.h` (Public)


#### class `UAnimNotifyState_PoseSearchBase`  
`class UAnimNotifyState_PoseSearchBase : public UAnimNotifyState`  
_L17-20_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimNotifyState`
- desc: Base class for ALL pose search anim notify states

#### class `UAnimNotifyState_PoseSearchExcludeFromDatabase`  
`class UAnimNotifyState_PoseSearchExcludeFromDatabase : public UAnimNotifyState_PoseSearchBase`  
_L25-28_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Exclude From Database"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: Use this notify state to remove animation segments from the database completely, they will never play or return from a search result. PSD indexing will report errors in case the sampled animation asset contains conflicting UAnimNotifyState_PoseSearchSamplingRange(s)

#### class `UAnimNotifyState_PoseSearchSamplingRange`  
`class UAnimNotifyState_PoseSearchSamplingRange : public UAnimNotifyState_PoseSearchBase`  
_L33-36_
- reflection: `UCLASS(MinimalAPI, Experimental, Blueprintable, meta = (DisplayName = "Pose Search: Sampling Range"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: Use this notify state to include animation segments into the database, whatever excluded will never play or return from a search result. PSD indexing will report errors in case the sampled animation asset contains conflicting UAnimNotifyState_PoseSearchExcludeFromDatabase(s)

#### class `UAnimNotifyState_PoseSearchBlockTransition`  
`class UAnimNotifyState_PoseSearchBlockTransition : public UAnimNotifyState_PoseSearchBase`  
_L41-44_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Block Transition In"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: A pose search search will not return results that overlap this notify, but the animation segment can still play if a previous search result advances into it.

#### class `UAnimNotifyState_PoseSearchModifyCost`  
`class UAnimNotifyState_PoseSearchModifyCost : public UAnimNotifyState_PoseSearchBase`  
_L50-60_
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: @todo: rename into UAnimNotifyState_PoseSearchOverrideBaseCostBias
- L59 _public member_ `float CostAddend = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayName = "Modifier"))` — A negative value reduces the cost and makes the segment more likely to be chosen. A positive value, conversely, makes the segment less likely to be chosen

#### class `UAnimNotifyState_PoseSearchOverrideContinuingPoseCostBias`  
`class UAnimNotifyState_PoseSearchOverrideContinuingPoseCostBias : public UAnimNotifyState_PoseSearchBase`  
_L65-75_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Override Continuing Pose Cost Bias"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: Pose search cost for the continuing pose will be affected by this, making the animation segment more or less likely to be continuing playing based on the notify parameters
- L74 _public member_ `float CostAddend = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayName = "Modifier"))` — A negative value reduces the cost and makes the segment more likely to continuing playing. A positive value, conversely, makes the segment less likely to continuing playing

#### class `UAnimNotifyState_PoseSearchOverrideContinuingInteractionPoseCostBias`  
`class UAnimNotifyState_PoseSearchOverrideContinuingInteractionPoseCostBias : public UAnimNotifyState_PoseSearchBase`  
_L80-90_
- reflection: `UCLASS(MinimalAPI, Experimental, Blueprintable, meta = (DisplayName = "Pose Search: Override Continuing Interaction Cost Bias"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: Pose search cost for the continuing interaction (same anim contexts with the same assigned roles), making the animation segment more or less likely to be continuing playing based on the notify parameters
- L89 _public member_ `float CostAddend = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayName = "Modifier"))` — A negative value reduces the cost and makes the segment more likely to continuing playing. A positive value, conversely, makes the segment less likely to continuing playing

#### class `UAnimNotifyState_PoseSearchOverrideContinuingContextInteractionCostBias`  
`class UAnimNotifyState_PoseSearchOverrideContinuingContextInteractionCostBias : public UAnimNotifyState_PoseSearchBase`  
_L95-104_
- reflection: `UCLASS(MinimalAPI, Experimental, Blueprintable, meta = (DisplayName = "Pose Search: Override Continuing Context Interaction Cost Bias"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: Pose search cost for the continuing context interaction (same anim contexts, assigned roles may differ), making the animation segment more or less likely to be continuing playing based on the notify parameters
- L103 _public member_ `float CostAddend = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (DisplayName = "Modifier"))` — A negative value reduces the cost and makes selecting a new interaction less likely

#### class `UAnimNotifyState_PoseSearchSamplingEvent`  
`class UAnimNotifyState_PoseSearchSamplingEvent : public UAnimNotifyState_PoseSearchBase`  
_L109-121_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Sampling Event"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: UPoseSearchFeatureChannel(s) can use this UAnimNotifyState_PoseSearchSamplingEvent to demarcate events identified by SamplingAttributeId during database indexing by specifying their SamplingAttributeId property to match UAnimNotifyState_PoseSearchSamplingAttribute::SamplingAttributeId
- L118 _public member_ `int32 SamplingAttributeId = 0;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ClampMin=0))`

#### class `UAnimNotifyState_PoseSearchSamplingAttribute`  
`class UAnimNotifyState_PoseSearchSamplingAttribute : public UAnimNotifyState_PoseSearchSamplingEvent`  
_L126-147_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Sampling Attribute"))`
- inherits: `UAnimNotifyState_PoseSearchSamplingEvent`
- desc: UPoseSearchFeatureChannel(s) can use this UAnimNotifyState_PoseSearchSamplingAttribute as animation space position, rotation, and linear velocity provider during database indexing by specifying their SamplingAttributeId property to match UAnimNotifyState_PoseSearchSamplingAttribute::SamplingAttributeId
- L135 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L138 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L141 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L144 _public member_ `FVector LinearVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Config)`

#### class `UAnimNotifyState_PoseSearchBranchIn`  
`class UAnimNotifyState_PoseSearchBranchIn : public UAnimNotifyState_PoseSearchBase`  
_L150-160_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Pose Search: Motion Matched Branch In"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- L157 _public member_ `TObjectPtr<UPoseSearchDatabase> Database;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L159 _public prototype_ `uint32 GetBranchInId() const;`

#### class `UAnimNotifyState_PoseSearchConstraint`  
`class UAnimNotifyState_PoseSearchConstraint : public UAnimNotifyState_PoseSearchBase`  
_L164-199_
- reflection: `UCLASS(MinimalAPI, Experimental, Blueprintable, meta = (DisplayName = "Pose Search: Constraint"))`
- inherits: `UAnimNotifyState_PoseSearchBase`
- desc: multi character interaction constraint notify state: used to calculate relative bone positions in UPoseSearchInteractionAsset items
- L170 _public member_ `FName FromSocketName;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L173 _public member_ `FName FromSocketRole;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L176 _public member_ `FName ToSocketName;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L179 _public member_ `FName ToSocketRole;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L183 _public member_ `float TranslationWeight = 0.f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — who should translate to reach full alignment? FromSocket or ToSocket? If TranslationWeight is 0 FromSocket will move 100% and ToSocket 0%, if TranslationWeight is 1 FromSocket will move 0% and ToSocket 100%,
- L187 _public member_ `float RotationWeight = 0.f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))` — who should rotate to reach full alignment? FromSocket or ToSocket? If RotationWeight is 0 FromSocket will move 100% and ToSocket 0%, if RotationWeight is 1 FromSocket will move 0% and ToSocket 100%,
- L192 _public member_ `float RampUpTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ClampMin = "0", UIMin = "0"))` — ramp up time used to calculate the desired reach for this constraint (it doesn't start at the beginning of this notify state, BUT when this notify state is first seen, since MM can jump into a random frame of the animation containing the notify state)
- L198 _public member_ `float CoolDownTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ClampMin = "0", UIMin = "0"))` — cool down time used to calculate the desired reach for this constraint (it doesn't start at the end of this notify state, BUT when this notify state gets out of scope (ultimately getting out of scope when reaching the notify state end time minus CoolDownTime, since MM can jump into a random frame of the animation containing the notify state)

#### class `UAnimNotify_PoseSearchBase`  
`class UAnimNotify_PoseSearchBase : public UAnimNotify`  
_L203-206_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimNotify`
- desc: Base class for ALL pose search anim notifies

#### class `UAnimNotify_PoseSearchEvent`  
`class UAnimNotify_PoseSearchEvent : public UAnimNotify_PoseSearchBase`  
_L209-217_
- reflection: `UCLASS(MinimalAPI, Experimental, Blueprintable, meta = (DisplayName = "Pose Search: Event"))`
- inherits: `UAnimNotify_PoseSearchBase`
- L216 _public member_ `FGameplayTag EventTag;` — `UPROPERTY(EditAnywhere, Category = Config)` — Tag identifying this event

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchAssetIndexer.h` (Public)


#### struct `UE::PoseSearch::FAssetSamplingContext`  
`struct FAssetSamplingContext`  
_L24-30_
- L26 _public member_ `float BaseCostBias = 0.f;`
- L27 _public member_ `float LoopingCostBias = 0.f;`
- L29 _public prototype_ `FAssetSamplingContext(const UPoseSearchDatabase& Database);`

#### struct `UE::PoseSearch::FAnimationAssetSamplers`  
`struct FAnimationAssetSamplers`  
_L32-52_
- L34 _public prototype_ `void Reset();`
- L35 _public prototype_ `int32 Num() const;`
- L37 _public prototype_ `float GetPlayLength() const;`
- L38 _public prototype_ `bool IsLoopable() const;`
- L39 _public prototype_ `void ExtractAnimNotifyStates(float Time, FAnimNotifyContext& PreAllocatedNotifyContext, const TFunction<bool(UAnimNotifyState*)>& ProcessAnimNotifyState) const;`
- L40 _public prototype_ `bool ProcessAllAnimNotifyEvents(const TFunction<bool(TConstArrayView<FAnimNotifyEvent>)>& ProcessAnimNotifyEvents) const;`
- L41 _public prototype_ `const FString GetAssetName() const;`
- L43 _public prototype_ `FTransform ExtractRootTransform(float Time, int32 RoleIndex) const;`
- L44 _public prototype_ `FTransform GetTotalRootTransform(int32 RoleIndex) const;`
- L45 _public prototype_ `void ExtractPose(float Time, FCompactPose& OutPose, int32 RoleIndex) const;`
- L46 _public prototype_ `void ExtractPose(float Time, FCompactPose& OutPose, FBlendedCurve& OutCurve, int32 RoleIndex) const;`
- L47 _public prototype_ `FTransform MirrorTransform(const FTransform& InTransform, int32 RoleIndex) const;`
- L48 _public prototype_ `void MirrorPose(FCompactPose& Pose, int32 RoleIndex) const;`
- L50 _public member_ `TArray<const FAnimationAssetSampler*, TInlineAllocator<PreallocatedRolesNum>> AnimationAssetSamplers;`
- L51 _public member_ `TArray<const FMirrorDataCache*, TInlineAllocator<PreallocatedRolesNum>> MirrorDataCaches;`

#### class `UE::PoseSearch::FAssetIndexer`  
`class FAssetIndexer`  
_L54-180_
- L66 _public prototype_ `FAssetIndexer(const TConstArrayView<FBoneContainer> InBoneContainers, const FSearchIndexAsset& InSearchIndexAsset, const FAssetSamplingContext& InSamplingContext, const UPoseSearchSchema& InSchema, const FAnimationAssetSamplers& InAssetSamplers, const FRoleToIndex& InRoleToIndex, const FFloatInterval& InExtrapolationTimeInterval);`
- L68 _public prototype_ `void AssignWorkingData(int32 InStartPoseIdx, TArrayView<float> InOutFeatureVectorTable, TArrayView<FPoseMetadata> InOutPoseMetadata);`
- L69 _public prototype_ `void Process(int32 AssetIdx);`
- L70 _public function_ `const FStats& GetStats() const`
- L72 _public function_ `const FEventDataCollector& GetEventDataCollector() const` — Experimental, this feature might be removed without warning, not for production use
- L75 _public prototype_ `bool GetSampleCurveValue(float& OutCurveValue, float SampleTimeOffset, int32 SampleIdx, const FName& CurveName, const FRole& SampleRole);` — Returns the value of float curve CurveName at time CalculateSampleTime(SampleIdx) + SampleTimeOffset.
- L80 _public prototype_ `bool GetSampleRotation(FQuat& OutSampleRotation, float SampleTimeOffset, float OriginTimeOffset, int32 SampleIdx, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, int32 SamplingAttributeId = INDEX_NONE);` — Returns OutSampleRotation as the rotation of the bone Schema.BoneReferences[SchemaSampleBoneIdx] at time CalculateSampleTime(SampleIdx) + SampleTimeOffset relative to the transform of the bone Schema.BoneReferences[SchemaOriginBoneIdx] at time CalculateSampleTime(SampleIdx) + OriginTimeOffset Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...)
- L85 _public prototype_ `bool GetSamplePosition(FVector& OutSamplePosition, float SampleTimeOffset, float OriginTimeOffset, int32 SampleIdx, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, int32 SamplingAttributeId = INDEX_NONE);` — Returns OutSamplePosition as the position of the bone Schema.BoneReferences[SchemaSampleBoneIdx] at time CalculateSampleTime(SampleIdx) + SampleTimeOffset relative to the transform of the bone Schema.BoneReferences[SchemaOriginBoneIdx] at time CalculateSampleTime(SampleIdx) + OriginTimeOffset. Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...)
- L91 _public prototype_ `bool GetSampleVelocity(FVector& OutSampleVelocity, float SampleTimeOffset, float OriginTimeOffset, int32 SampleIdx, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, bool bUseCharacterSpaceVelocities = true, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, int32 SamplingAttributeId = INDEX_NONE);` — Returns OutSampleVelocity as the delta velocity of the bone Schema.BoneReferences[SchemaSampleBoneIdx] velocity at time CalculateSampleTime(SampleIdx) + SampleTimeOffset minus the velocity of the bone Schema.BoneReferences[SchemaOriginBoneIdx] at time CalculateSampleTime(SampleIdx) + OriginTimeOffset. Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...) if bUseCharacterSpaceVelocities is true, velocities will be computed in root bone space, rather than animation (world) space
- L93 _public prototype_ `bool ProcessAllAnimNotifyEvents(const TFunction<bool(TConstArrayView<FAnimNotifyEvent>)>& ProcessAnimNotifyEvents) const;`
- L94 _public prototype_ `const FString GetAssetName() const;`
- L95 _public prototype_ `float GetPlayLength() const;`
- L97 _public prototype_ `int32 GetBeginSampleIdx() const;`
- L98 _public prototype_ `int32 GetEndSampleIdx() const;`
- L99 _public prototype_ `int32 GetNumIndexedPoses() const;`
- L101 _public prototype_ `TArrayView<float> GetPoseVector(int32 SampleIdx) const;`
- L102 _public prototype_ `const UPoseSearchSchema* GetSchema() const;`
- L103 _public prototype_ `float CalculateSampleTime(int32 SampleIdx) const;`
- L104 _public function_ `bool IsProcessFailed() const`
- L107 _public prototype_ `float CalculatePermutationTimeOffset() const;`
- L111 _public prototype_ `void CompareCachedEntries(const FAssetIndexer& Other) const;`
- L115 _private prototype_ `int32 GetVectorIdx(int32 SampleIdx) const;`
- L118 _private prototype_ `FTransform GetTransform(float SampleTime, const FRole& Role, int8 SchemaBoneIdx = RootSchemaBoneIdx);` — Returns the animation (world) space transform of the bone Schema.BoneReferences[SchemaBoneIdx] at time SampleTime
- L119 _private prototype_ `FTransform GetTransform(float SampleTime, int32 RoleIndex, const FBoneReference& BoneReference);`
- L122 _private prototype_ `float GetSampleCurveValueInternal(float SampleTime, const FName& CurveName, const FRole& Role);` — Returns the value of float curve CurveName at time SampleTime
- L125 _private prototype_ `FTransform GetComponentSpaceTransform(float SampleTime, const FRole& Role, int8 SchemaBoneIdx = RootSchemaBoneIdx);` — Returns the component space transform of the bone Schema.BoneReferences[SchemaBoneIdx] at time SampleTime
- L129 _private prototype_ `bool GetSamplePositionInternal(FVector& OutSamplePosition, float SampleTime, float OriginTime, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, int32 SamplingAttributeId);` — Returns OutSamplePosition as the displacement of the bone Schema.BoneReferences[SchemaSampleBoneIdx] position at time SampleTime relative to the position of the bone Schema.BoneReferences[SchemaOriginBoneIdx] at time OriginTime in root bone space
- L152 _private prototype_ `FTransform MirrorTransform(const FTransform& Transform, int32 RoleIndex) const;`
- L153 _private prototype_ `FCachedEntry& GetEntry(float SampleTime);`
- L154 _private prototype_ `FTransform CalculateComponentSpaceTransform(FCachedEntry& Entry, const FBoneReference& BoneReference, int32 RoleIndex);`
- L156 _private prototype_ `void ComputeStats();`
- L158 _private member_ `TArray<FBoneContainer> BoneContainers;`
- L159 _private member_ `TMap<float, FCachedEntry> CachedEntries;`
- L160 _private member_ `const FSearchIndexAsset& SearchIndexAsset;`
- L161 _private member_ `const FAssetSamplingContext& SamplingContext;`
- L162 _private member_ `const UPoseSearchSchema& Schema;`
- L163 _private member_ `const FAnimationAssetSamplers AssetSamplers;`
- L167 _private member_ `const FRoleToIndex RoleToIndex;` — NoTe: mapping Role to the index of the associated asset that this FAssetIndexer is indexing. NOT the index of the UPoseSearchSchema::Skeletons! Use UPoseSearchSchema::GetRoledSkeleton API to resolve that Role to FPoseSearchRoledSkeleton
- L169 _private member_ `FFloatInterval ExtrapolationTimeInterval = FFloatInterval(-UE_BIG_NUMBER, UE_BIG_NUMBER);`
- L171 _private member_ `int32 StartPoseIdx = 0;`
- L173 _private member_ `TArrayView<float> FeatureVectorTable;`
- L174 _private member_ `TArrayView<FPoseMetadata> PoseMetadata;`
- L176 _private member_ `FEventDataCollector EventDataCollector;`
- L177 _private member_ `FStats Stats;`
- L179 _private member_ `bool bProcessFailed = false;`

#### struct `UE::PoseSearch::FAssetIndexer::FStats`  
`struct FStats`  
_L57-64_
- L59 _public member_ `int32 NumAccumulatedSamples = 0;`
- L60 _public member_ `float AccumulatedSpeed = 0.f;`
- L61 _public member_ `float MaxSpeed = 0.f;`
- L62 _public member_ `float AccumulatedAcceleration = 0.f;`
- L63 _public member_ `float MaxAcceleration = 0.f;`

#### struct `UE::PoseSearch::FAssetIndexer::FCachedCSPose`  
`struct FCachedCSPose : public FCSPose<FCompactHeapPose>`  
_L131-140_
- inherits: `FCSPose<FCompactHeapPose>`
- L133 _public function_ `void InitPose(const FCompactPose& SrcPose)`

#### struct `UE::PoseSearch::FAssetIndexer::FCachedEntry`  
`struct FCachedEntry`  
_L142-150_
- L144 _public member_ `float SampleTime = 0.f;`
- L147 _public member_ `TArray<FTransform, TInlineAllocator<PreallocatedRolesNum>> RootTransform;` — RootTransform and ComponentSpacePose are stored mirrored in case SearchIndexAsset.IsMirrored
- L148 _public member_ `TArray<FCachedCSPose, TInlineAllocator<PreallocatedRolesNum>> ComponentSpacePose;`
- L149 _public member_ `TArray<FBlendedHeapCurve, TInlineAllocator<PreallocatedRolesNum>> Curves;`

#### struct `UE::PoseSearch::FPoseSearchTimedNotifies`  
`template <class TAnimNotifyState> struct FPoseSearchTimedNotifies`  
_L183-257_
- L193 _public function_ `FPoseSearchTimedNotifies()`
- L197 _public function_ `FPoseSearchTimedNotifies(int32 SamplingAttributeId, FAssetIndexer& Indexer)`
- L202 _public function_ `void Initialize(int32 SamplingAttributeId, FAssetIndexer& Indexer)`
- L230 _public function_ `FItem GetClosestFutureEvent(float SampleTime) const`
- L255 _private member_ `TArray<FItem, TInlineAllocator<128>> Items;`
- L256 _private member_ `float CachedPlayLength = 0.f;`

#### struct `UE::PoseSearch::FPoseSearchTimedNotifies::FItem`  
`struct FItem`  
_L187-191_
- L189 _public member_ `float Time = 0.f;`
- L190 _public member_ `const TAnimNotifyState* NotifyState = nullptr;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PoseSearch` (scope `UE`)
- L209 _function_ `` (scope `UE::PoseSearch::FPoseSearchTimedNotifies::Initialize`)
- L224 _function_ `Items.Sort([](const FItem& A, const FItem& B) { return A.Time < B.Time; });` (scope `UE::PoseSearch::FPoseSearchTimedNotifies::Initialize`)
- L246 _function_ `` (scope `UE::PoseSearch::FPoseSearchTimedNotifies::GetClosestFutureEvent`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchAssetSampler.h` (Public)


#### struct `UE::PoseSearch::FAnimationAssetSampler`  
`struct FAnimationAssetSampler`  
_L21-85_
- desc: Helper for sampling data from animation assets
- L24 _public prototype_ `FAnimationAssetSampler();`
- L25 _public prototype_ `FAnimationAssetSampler(const UAnimationAsset* InAnimationAsset, const FTransform& InRootTransformOrigin = FTransform::Identity, const FVector& InBlendParameters = FVector::ZeroVector, int32 InRootTransformSamplingRate = DefaultRootTransformSamplingRate, bool bPreProcessRootTransform = true, bool bInEnforceCompressedDataSampling = true);`
- L26 _public prototype_ `~FAnimationAssetSampler();`
- L27 _public prototype_ `void Init(const UAnimationAsset* InAnimationAsset, const FTransform& InRootTransformOrigin = FTransform::Identity, const FVector& InBlendParameters = FVector::ZeroVector, int32 InRootTransformSamplingRate = DefaultRootTransformSamplingRate, bool bPreProcessRootTransform = true, bool bInEnforceCompressedDataSampling = true);`
- L29 _public prototype_ `bool IsInitialized() const;`
- L30 _public prototype_ `float GetPlayLength() const;`
- L31 _public prototype_ `float ToRealTime(float NormalizedTime) const;`
- L32 _public prototype_ `float ToNormalizedTime(float RealTime) const;`
- L33 _public prototype_ `bool IsLoopable() const;`
- L36 _public prototype_ `FTransform GetTotalRootTransform() const;` — Gets the final root transformation at the end of the asset's playback time
- L39 _public prototype_ `void ExtractPose(const FAnimExtractContext& ExtractionCtx, FAnimationPoseData& OutAnimPoseData) const;` — `UE_DEPRECATED(5.8, "This ExtractPose signatures will be made private. Use other signatures")`
- L42 _public prototype_ `void ExtractPose(float Time, FCompactPose& OutPose) const;` — Extracts pose for this asset at a given Time
- L43 _public prototype_ `void ExtractPose(float Time, FCompactPose& OutPose, FBlendedCurve& OutCurve) const;`
- L47 _public prototype_ `FTransform ExtractRootTransform(float Time) const;` — Extracts root transform at the given time, using the extremities of the sequence to extrapolate beyond the sequence limits when Time is less than zero or greater than the sequence length.
- L50 _public prototype_ `void ExtractAnimNotifyContext(float Time, FAnimNotifyContext& PreAllocatedNotifyContext) const;` — Populates FAnimNotifyContext from the animation asset at Time
- L52 _public prototype_ `void ExtractAnimNotifyStates(float Time, FAnimNotifyContext& PreAllocatedNotifyContext, const TFunction<bool(UAnimNotifyState*)>& ProcessAnimNotifyState) const;` — Extracts notify states present in the animation asset at Time
- L54 _public prototype_ `void ExtractAnimNotifyEvents(float Time, FAnimNotifyContext& PreAllocatedNotifyContext, const TFunction<bool(const FAnimNotifyEvent*)>& ProcessAnimNotifyEvent) const;` — Extracts notify events present in the animation asset at Time
- L56 _public prototype_ `TConstArrayView<FAnimNotifyEvent> GetAllAnimNotifyEvents() const;`
- L58 _public prototype_ `const UAnimationAsset* GetAsset() const;`
- L60 _public prototype_ `void Process();`
- L62 _public prototype_ `static float GetPlayLength(const UAnimationAsset* AnimAsset, const FVector& BlendParameters = FVector::ZeroVector);`
- L63 _public prototype_ `static float WrapOrClampTime(float Time, float PlayLength, bool bLoopable);`
- L65 _public function_ `void SetRootTransformOrigin(const FTransform& InRootTransformOrigin)`
- L66 _public function_ `const FTransform& GetRootTransformOrigin() const`
- L69 _protected member_ `TWeakObjectPtr<const UAnimationAsset> AnimationAssetPtr;`
- L70 _protected member_ `FTransform RootTransformOrigin = FTransform::Identity;`
- L73 _protected member_ `FVector BlendParameters = FVector::ZeroVector;` — members used to sample blend spaces only!
- L74 _protected member_ `int32 RootTransformSamplingRate = DefaultRootTransformSamplingRate;`
- L75 _protected member_ `float CachedPlayLength = -1.f;`
- L76 _protected member_ `TArray<FTransform> AccumulatedRootTransform;`
- L78 _protected member_ `const float ExtrapolationSampleTime = 1.f / 30.f;`
- L79 _protected member_ `const float ExtractionInterval = 1.0f / 120.0f;`
- L81 _protected member_ `bool bEnforceCompressedDataSampling = true;`
- L83 _protected member_ `FIoHash PlatformHash;`

#### enum `UE::PoseSearch::FAnimationAssetSampler::(anonymous)`  
`enum`  
_L23-23_

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)
- L23 _enumerator_ `enum { DefaultRootTransformSamplingRate = 30 }; POSESEARCH_API FAnimationAssetSampler(); POSESEARCH_API FAnimationAssetSampler(const UAnimationAsset* InAnimationAsset, const FTransform& InRootTransformOrigin = FTransform::Identity, const FVector& InBlendParameters = FVector::ZeroVector, int32 InRootTransformSamplingRate = DefaultRootTransformSamplingRate, bool bPreProcessRootTransform = true, bool bInEnforceCompressedDataSampling = true); POSESEARCH_API ~FAnimationAssetSampler(); POSESEARCH_API void Init(const UAnimationAsset* InAnimationAsset, const FTransform& InRootTransformOrigin = FTransform::Identity, const FVector& InBlendParameters = FVector::ZeroVector, int32 InRootTransformSamplingRate = DefaultRootTransformSamplingRate, bool bPreProcessRootTransform = true, bool bInEnforceCompressedDataSampling = true); POSESEARCH_API bool IsInitialized() const; POSESEARCH_API float GetPlayLength() const;` (scope `UE::PoseSearch::FAnimationAssetSampler::__anone198f4860103`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchAssetSamplerLibrary.h` (Public)


#### struct `FPoseSearchAssetSamplerInput`  
`struct FPoseSearchAssetSamplerInput`  
_L16-41_
- reflection: `USTRUCT(Experimental, BlueprintType, Category="Animation|Pose Search")`
- L22 _public member_ `TObjectPtr<const UAnimationAsset> Animation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Animation to sample
- L26 _public member_ `float AnimationTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Sampling time for Animation
- L30 _public member_ `FTransform RootTransformOrigin = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — origin used to start sampling Animation at time of zero
- L33 _public member_ `bool bMirrored = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L36 _public member_ `TObjectPtr<const UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L40 _public member_ `FVector BlendParameters = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — blend parameters if Animation is a blend space

#### struct `FPoseSearchAssetSamplerPose`  
`struct FPoseSearchAssetSamplerPose`  
_L44-79_
- reflection: `USTRUCT(Experimental, BlueprintType, Category="Animation|Pose Search")`
- L48 _public prototype_ `FPoseSearchAssetSamplerPose() = default;`
- L50 _public function_ `FPoseSearchAssetSamplerPose(const FPoseSearchAssetSamplerPose& Other) : RootTransform(Other.RootTransform) , BoneContainer(Other.BoneContainer) , Pose(Other.Pose) , Curve(Other.Curve) , ComponentSpacePose(Other.ComponentSpacePose)`
- L61 _public function_ `FPoseSearchAssetSamplerPose& operator=(const FPoseSearchAssetSamplerPose& Other)`
- L71 _public member_ `FTransform RootTransform = FTransform::Identity;`
- L72 _public member_ `FBoneContainer BoneContainer;`
- L73 _public member_ `FCompactHeapPose Pose;`
- L74 _public member_ `FBlendedHeapCurve Curve;`
- L78 _public member_ `FCSPose<FCompactHeapPose> ComponentSpacePose;`

#### enum `EPoseSearchAssetSamplerSpace`  
`enum class EPoseSearchAssetSamplerSpace : uint8`  
_L82-87_
- reflection: `UENUM()`
- L84 _public enumerator_ `Local`
- L85 _public enumerator_ `Component`
- L86 _public enumerator_ `World`

#### class `UPoseSearchAssetSamplerLibrary`  
`class UPoseSearchAssetSamplerLibrary : public UBlueprintFunctionLibrary`  
_L90-204_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- L96 _public prototype_ `static FPoseSearchAssetSamplerPose SamplePose(const FPoseSearchAssetSamplerInput Input, const UAnimInstance* AnimInstance = nullptr);` — `UFUNCTION(BlueprintPure, Category = "Animation|Pose Search|Experimental", meta = (BlueprintThreadSafe, AdvancedDisplay = "AnimInstance"))`
- L98 _public prototype_ `static FPoseSearchAssetSamplerPose SamplePose(const FBoneContainer& BoneContainer, const FPoseSearchAssetSamplerInput Input);`
- L101 _public prototype_ `static FTransform GetTransformByName(UPARAM(ref) FPoseSearchAssetSamplerPose& AssetSamplerPose, FName BoneName, EPoseSearchAssetSamplerSpace Space = EPoseSearchAssetSamplerSpace::World);` — `UFUNCTION(BlueprintPure, Category = "Animation|Pose Search|Experimental", meta = (BlueprintThreadSafe))`
- L103 _public prototype_ `static FTransform GetTransform(FPoseSearchAssetSamplerPose& AssetSamplerPose, FCompactPoseBoneIndex CompactPoseBoneIndex = FCompactPoseBoneIndex(INDEX_NONE), EPoseSearchAssetSamplerSpace Space = EPoseSearchAssetSamplerSpace::World);`
- L107 _public prototype_ `static void Draw(const UAnimInstance* AnimInstance, UPARAM(ref) FPoseSearchAssetSamplerPose& AssetSamplerPose);` — `UFUNCTION(BlueprintCallable, Category="Animation|Pose Search|Experimental")` — @todo: it'd be nice if it was threadsafe...
- L110 _public function_ `template<typename FComponentSpacePoseType> static FTransform GetTransform(FComponentSpacePoseType& ComponentSpacePose, const FTransform& RootTransform, FCompactPoseBoneIndex CompactPoseBoneIndex = FCompactPoseBoneIndex(INDEX_NONE), EPoseSearchAssetSamplerSpace Space = EPoseSearchAssetSamplerSpace::World)`
- L151 _public function_ `template<typename FComponentSpacePoseType> static void Draw(const UWorld* World, FComponentSpacePoseType& ComponentSpacePose, const FTransform& RootTransform, const FColor Color = FColor::Red, float DebugDrawSamplerRootAxisLength = 20.f, float DebugDrawSamplerSize = 6.f)`
- L174 _public function_ `template<typename FComponentSpacePoseType> static void VLogDraw(const UObject* VLogContext, FComponentSpacePoseType& ComponentSpacePose, const FTransform& RootTransform, const TCHAR* VLogName, const FColor Color = FColor::Red, float DebugDrawSamplerRootAxisLength = 20.f)`
- L201 _public prototype_ `static void VLogDraw(const UObject* VLogContext, const USkeletalMeshComponent* Mesh, const TCHAR* VLogName, const FColor Color = FColor::Red, float DebugDrawSamplerRootAxisLength = 20.f);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchConstraints.h` (Public)


#### struct `FPoseSearchConstraint`  
`struct FPoseSearchConstraint`  
_L20-80_
- reflection: `USTRUCT(Experimental, BlueprintType, Category = "Animation|Pose Search")`
- L24 _public prototype_ `void Initialize(const UAnimNotifyState_PoseSearchConstraint* ConstraintNotifyState);`
- L25 _public prototype_ `const FTransform* GetSocketTransform(UE::PoseSearch::FRole Role, FName SocketName) const;`
- L28 _public function_ `template<typename T> bool HasTheSameRoledSockets(const T& Other) const`
- L46 _public member_ `FName FromSocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L48 _public member_ `FName FromSocketRole;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L50 _public member_ `FName ToSocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L52 _public member_ `FName ToSocketRole;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L56 _public member_ `float TranslationWeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — who should translate to reach full alignment? FromBone or ToBone? If TranslationWeight is 0 FromBone will move 100% and ToBone 0%, if TranslationWeight is 1 FromBone will move 0% and ToBone 100%,
- L60 _public member_ `float RotationWeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — who should rotate to reach full alignment? FromBone or ToBone? If RotationWeight is 0 FromBone will move 100% and ToBone 0%, if RotationWeight is 1 FromBone will move 0% and ToBone 100%,
- L65 _public member_ `float RampUpTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — ramp up time used to calculate the desired reach for this constraint (it doesn't start at the beginning of this notify state, BUT when this notify state is first seen, since MM can jump into a random frame of the animation containing the notify state)
- L71 _public member_ `float CoolDownTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — cool down time used to calculate the desired reach for this constraint (it doesn't start at the end of this notify state, BUT when this notify state gets out of scope (ultimately getting out of scope when reaching the notify state end time minus CoolDownTime, since MM can jump into a random frame of the animation containing the notify state)
- L74 _public member_ `FTransform FromSocketTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L76 _public member_ `FTransform ToSocketTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L79 _public member_ `float DesiredReach = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchContext.h` (Public)


#### struct `UE::PoseSearch::FStackAssetSet`  
`struct FStackAssetSet : public TSet<const UObject*, DefaultKeyFuncs<const UObject*>, TInlineSetAllocator<8, TMemStackSetAllocator<>>>`  
_L24-37_
- inherits: `TSet<constUObject*,DefaultKeyFuncs<constUObject*>,TInlineSetAllocator<8,TMemStackSetAllocator<>>>`
- desc: usually used as set of asset to consider during a search of a database
- L26 _public function_ `bool ContainsAnyOf(TConstArrayView<const UObject*> Objects) const`

#### enum `UE::PoseSearch::EPoseCandidateFlags`  
`enum class EPoseCandidateFlags : uint32`  
_L62-81_
- L64 _public enumerator_ `None = 0`
- L66 _public enumerator_ `Valid_Pose = 1 << 0`
- L67 _public enumerator_ `Valid_ContinuingPose = 1 << 1`
- L68 _public enumerator_ `Valid_CurrentPose = 1 << 2`
- L70 _public enumerator_ `AnyValidMask = Valid_Pose | Valid_ContinuingPose | Valid_CurrentPose`
- L72 _public enumerator_ `DiscardedBy_PoseJumpThresholdTime = 1 << 3`
- L73 _public enumerator_ `DiscardedBy_PoseReselectHistory = 1 << 4`
- L74 _public enumerator_ `DiscardedBy_BlockTransition = 1 << 5`
- L75 _public enumerator_ `DiscardedBy_PoseFilter = 1 << 6`
- L76 _public enumerator_ `DiscardedBy_AssetIdxFilter = 1 << 7`
- L77 _public enumerator_ `DiscardedBy_Search = 1 << 8`
- L78 _public enumerator_ `DiscardedBy_AssetReselection = 1 << 9`
- L80 _public enumerator_ `AnyDiscardedMask = DiscardedBy_PoseJumpThresholdTime | DiscardedBy_PoseReselectHistory | DiscardedBy_BlockTransition | DiscardedBy_PoseFilter | DiscardedBy_AssetIdxFilter | DiscardedBy_Search | DiscardedBy_AssetReselection`

#### struct `UE::PoseSearch::FDebugDrawParams`  
`struct FDebugDrawParams`  
_L85-141_
- L93 _public prototype_ `FDebugDrawParams(TConstArrayView<FChooserEvaluationContext*> InAnimContexts, TConstArrayView<const IPoseHistory*> InPoseHistories, const FRoleToIndex& InRoleToIndex, const UPoseSearchDatabase* InDatabase, EDrawContext InDrawContext = EDrawContext::DrawQuery);`
- L94 _public prototype_ `FDebugDrawParams() = default;`
- L96 _public prototype_ `FDebugDrawParams(const FDebugDrawParams& Other);`
- L97 _public prototype_ `FDebugDrawParams(FDebugDrawParams&& Other);`
- L98 _public prototype_ `FDebugDrawParams& operator=(const FDebugDrawParams& Other);`
- L99 _public prototype_ `FDebugDrawParams& operator=(FDebugDrawParams&& Other);`
- L101 _public prototype_ `void Init(TConstArrayView<FChooserEvaluationContext*> InAnimContexts, TConstArrayView<const IPoseHistory*> InPoseHistories, const FRoleToIndex& InRoleToIndex, const UPoseSearchDatabase* InDatabase, EDrawContext InDrawContext = EDrawContext::DrawQuery);`
- L103 _public prototype_ `const FSearchIndex* GetSearchIndex() const;`
- L104 _public prototype_ `const UPoseSearchSchema* GetSchema() const;`
- L106 _public prototype_ `float ExtractPermutationTime(TConstArrayView<float> PoseVector) const;`
- L107 _public prototype_ `FVector ExtractPosition(TConstArrayView<float> PoseVector, float SampleTimeOffset, int8 SchemaBoneIdx, const FRole& Role, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, int32 SamplingAttributeId = INDEX_NONE, float PermutationSampleTimeOffset = 0.f) const;`
- L108 _public prototype_ `FQuat ExtractRotation(TConstArrayView<float> PoseVector, float SampleTimeOffset, int8 SchemaBoneIdx, const FRole& Role, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, int32 SamplingAttributeId = INDEX_NONE, float PermutationSampleTimeOffset = 0.f) const;`
- L109 _public prototype_ `FTransform GetRootBoneTransform(const FRole& Role, float SampleTimeOffset = 0.f) const;`
- L111 _public prototype_ `void DrawLine(const FVector& LineStart, const FVector& LineEnd, const FColor& Color, float Thickness = 0.f) const;`
- L112 _public prototype_ `void DrawPoint(const FVector& Position, const FColor& Color, float Thickness = 6.f) const;`
- L113 _public prototype_ `void DrawCircle(const FVector& Center, const FVector& UpVector, float Radius, int32 Segments, const FColor& Color, float Thickness = 0.f) const;`
- L114 _public prototype_ `void DrawCircle(const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, float Thickness = 0.f) const;`
- L115 _public prototype_ `void DrawWedge(const FVector& Origin, const FVector& Direction, float InnerRadius, float OuterRadius, float WidthInDegrees, int32 Segments, const FColor& Color, float Thickness = 0.f) const;`
- L116 _public prototype_ `void DrawSphere(const FVector& Center, float Radius, int32 Segments, const FColor& Color, float Thickness = 0.f) const;`
- L117 _public prototype_ `void DrawCentripetalCatmullRomSpline(TConstArrayView<FVector> Points, TConstArrayView<FColor> Colors, float Alpha, int32 NumSamplesPerSegment, float Thickness = 1.f) const;`
- L119 _public prototype_ `void DrawFeatureVector(TConstArrayView<float> PoseVector);`
- L120 _public prototype_ `void DrawFeatureVector(int32 PoseIdx);`
- L122 _public prototype_ `bool IsAnyWeightRelevant(const UPoseSearchFeatureChannel* Channel) const;`
- L124 _public function_ `EDrawContext GetDrawContext() const`
- L127 _private prototype_ `bool CanDraw() const;`
- L129 _private member_ `TConstArrayView<FChooserEvaluationContext*> AnimContexts;`
- L130 _private member_ `TConstArrayView<const IPoseHistory*> PoseHistories;`
- L134 _private member_ `FRoleToIndex RoleToIndex;` — NoTe: mapping Role to the index of the associated asset that this FDebugDrawParams is drawing. NOT the index of the UPoseSearchSchema::Skeletons! Use UPoseSearchSchema::GetRoledSkeleton API to resolve that Role to FPoseSearchRoledSkeleton
- L136 _private member_ `const UPoseSearchDatabase* Database = nullptr;`
- L137 _private member_ `EDrawContext DrawContext = EDrawContext::DrawCandidate;`
- L139 _private member_ `TAlignedArray<float> DynamicWeightsSqrtBuffer;`
- L140 _private member_ `TConstArrayView<float> DynamicWeightsSqrt;`

#### enum `UE::PoseSearch::FDebugDrawParams::EDrawContext`  
`enum EDrawContext`  
_L87-91_
- L89 _public enumerator_ `DrawQuery`
- L90 _public enumerator_ `DrawCandidate`

#### struct `UE::PoseSearch::FCachedQuery`  
`struct FCachedQuery`  
_L146-159_
- desc: float buffer of features according to a UPoseSearchSchema layout. Used to build search queries at runtime
- L149 _public prototype_ `explicit FCachedQuery(const UPoseSearchSchema* InSchema);`
- L150 _public function_ `const UPoseSearchSchema* GetSchema() const`
- L151 _public function_ `TArrayView<float> EditValues()`
- L152 _public function_ `TConstArrayView<float> GetValues() const`
- L155 _private member_ `TStackAlignedArray<float> Values;`
- L158 _private member_ `const UPoseSearchSchema* Schema;` — no need for a TWeakObjectPtr since it doesn't persist across multiple frames (same lifespan as FSearchContext)

#### struct `UE::PoseSearch::FCachedPCAQuery`  
`struct FCachedPCAQuery`  
_L162-175_
- desc: Experimental, this feature might be removed without warning, not for production use
- L165 _public prototype_ `explicit FCachedPCAQuery(const UPoseSearchDatabase* InDatabase);`
- L166 _public function_ `const UPoseSearchDatabase* GetDatabase() const`
- L167 _public function_ `TArrayView<float> EditValues()`
- L168 _public function_ `TConstArrayView<float> GetValues() const`
- L171 _private member_ `TStackAlignedArray<float> Values;`
- L174 _private member_ `const UPoseSearchDatabase* Database;` — no need for a TWeakObjectPtr since it doesn't persist across multiple frames (same lifespan as FSearchContext)

#### struct `UE::PoseSearch::FCachedChannel`  
`struct FCachedChannel`  
_L178-185_
- desc: CachedChannels uses hashed unique identifiers to determine channels that can share feature vector data during the building of the query
- L181 _public member_ `const UPoseSearchFeatureChannel* Channel = nullptr;` — no need for a TWeakObjectPtr since it doesn't persist across multiple frames (same lifespan as FSearchContext)
- L184 _public member_ `int32 CachedQueryIndex = INDEX_NONE;` — index of the associated query in FSearchContext::CachedQueries

#### struct `UE::PoseSearch::FSearchContext`  
`struct FSearchContext`  
_L187-500_
- L190 _public prototype_ `FSearchContext(float InDesiredPermutationTimeOffset, const FPoseIndicesHistory* InPoseIndicesHistory, const FSearchResult& InCurrentResult, const FFloatInterval& InPoseJumpThresholdTime, const FPoseSearchEvent& InEventToSearch);` — `UE_DEPRECATED(5.7, "Use other signaure instead")`
- L193 _public prototype_ `FSearchContext(float InDesiredPermutationTimeOffset, const FFloatInterval& InPoseJumpThresholdTime, const FPoseSearchEvent& InEventToSearch);`
- L196 _public prototype_ `FSearchContext(const FSearchContext& Other) = delete;` — deleting copies and moves since members could reference other members (e.g.: ContinuingPoseValues could point to ContinuingPoseValuesData, so it'll require proper copies and movers implementations)
- L197 _public prototype_ `FSearchContext(FSearchContext&& Other) = delete;`
- L198 _public prototype_ `FSearchContext& operator=(const FSearchContext& Other) = delete;`
- L199 _public prototype_ `FSearchContext& operator=(FSearchContext&& Other) = delete;`
- L201 _public prototype_ `void AddRole(const FRole& Role, FChooserEvaluationContext* AnimContext, const IPoseHistory* PoseHistory);`
- L205 _public prototype_ `float GetSampleCurveValue(float SampleTimeOffset, const FName& CurveName, const FRole& SampleRole);` — Returns the curve value of name CurveName at an offset time of SampleTimeOffset. If the curve is not found, assume value of 0, which is consistent with curve behavior in the animation update.
- L210 _public prototype_ `FQuat GetSampleRotation(float SampleTimeOffset, float OriginTimeOffset, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, const FQuat* SampleBoneRotationWorldOverride = nullptr);` — Returns the rotation of the bone with index Schema.BoneReferences[SchemaSampleBoneIdx] at an offset time of SampleTimeOffset relative to the transform of the bone with index Schema.BoneReferences[SchemaOriginBoneIdx] at an offset time of time OriginTimeOffset Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...)
- L215 _public prototype_ `FVector GetSamplePosition(float SampleTimeOffset, float OriginTimeOffset, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, const FVector* SampleBonePositionWorldOverride = nullptr);` — Returns the displacement of the bone with index Schema.BoneReferences[SchemaSampleBoneIdx] at an offset time of SampleTimeOffset relative to the position of the bone with index Schema.BoneReferences[SchemaOriginBoneIdx] at an offset time of OriginTimeOffset in root bone space Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...)
- L221 _public prototype_ `FVector GetSampleVelocity(float SampleTimeOffset, float OriginTimeOffset, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, bool bUseCharacterSpaceVelocities = true, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, const FVector* SampleBoneVelocityWorldOverride = nullptr);` — Returns the delta velocity of the velocity of the bone with index Schema.BoneReferences[SchemaSampleBoneIdx] at an offset time of SampleTimeOffset minus the velocity of the bone with index Schema.BoneReferences[SchemaOriginBoneIdx] at an offset time of OriginTimeOffset Times will be processed by GetPermutationTimeOffsets(PermutationTimeType, ...) if bUseCharacterSpaceVelocities is true, velocities will be computed in root bone space, rather than world space
- L224 _public prototype_ `void ResetCurrentBestCost();` — `UE_DEPRECATED(5.7, "No longer necessary API")`
- L227 _public prototype_ `void UpdateCurrentBestCost(const FPoseSearchCost& PoseSearchCost);` — `UE_DEPRECATED(5.7, "No longer necessary API")`
- L230 _public function_ `float GetCurrentBestTotalCost() const` — `UE_DEPRECATED(5.7, "No longer necessary API. Use the FSearchResult::PoseCost from UPoseSearchDatabase::Search if a search cost is needed")`
- L232 _public prototype_ `TConstArrayView<float> GetCachedQuery(const UPoseSearchSchema* Schema) const;`
- L233 _public prototype_ `TConstArrayView<float> GetOrBuildQuery(const UPoseSearchSchema* Schema);`
- L235 _public prototype_ `TConstArrayView<float> GetOrBuildPCAQuery(const UPoseSearchDatabase* Database);` — Experimental, this feature might be removed without warning, not for production use
- L238 _public prototype_ `bool IsCurrentResultFromDatabase(const UPoseSearchDatabase* Database) const;` — `UE_DEPRECATED(5.7, "compare Database against GetContinuingPoseSearchResult().Database instead (the internal replacement IsContinuingPoseDatabase is not going to be dll exported)")`
- L239 _public prototype_ `bool IsContinuingPoseDatabase(const UPoseSearchDatabase* Database) const;`
- L242 _public prototype_ `bool CanUseCurrentResult() const;` — `UE_DEPRECATED(5.7, "Use CanUseContinuingPoseValues instead")`
- L243 _public prototype_ `bool CanUseContinuingPoseValues() const;`
- L246 _public function_ `TConstArrayView<float> GetCurrentResultPoseVector() const` — `UE_DEPRECATED(5.7, "Use GetContinuingPoseValues")`
- L247 _public function_ `TConstArrayView<float> GetContinuingPoseValues() const`
- L250 _public prototype_ `void UpdateCurrentResultPoseVector();` — `UE_DEPRECATED(5.7, "Use UpdateContinuingPoseSearchResult to update the continuing pose search result AND values - previously referenced as 'CurrentResultPoseVector' ")`
- L251 _public prototype_ `void UpdateContinuingPoseSearchResult(const FSearchResult& InContinuingPoseSearchResult, const FDatabasePoseIdx& InContinuingPoseValuesDatabasePoseIdx);`
- L254 _public function_ `const FSearchResult& GetCurrentResult() const` — `UE_DEPRECATED(5.7, "Use GetContinuingPoseSearchResult")`
- L255 _public function_ `const FSearchResult& GetContinuingPoseSearchResult() const`
- L257 _public function_ `const FFloatInterval& GetPoseJumpThresholdTime() const`
- L260 _public prototype_ `const FPoseIndicesHistory* GetPoseIndicesHistory() const;` — `UE_DEPRECATED(5.7, "use GetPoseHistory(Role)->GetPoseIndicesHistory() with the appropriate Role instead")`
- L263 _public prototype_ `bool ArePoseHistoriesValid() const;` — `UE_DEPRECATED(5.7, "ArePoseHistoriesValid is no longer necessary, since PoseHistories MUST be valid since it contains necessary information for MM to function like trajectory, historical poses, etc")`
- L265 _public function_ `TConstArrayView<const IPoseHistory*> GetPoseHistories() const`
- L266 _public prototype_ `const IPoseHistory* GetPoseHistory(const FRole& Role) const;`
- L268 _public function_ `float GetDesiredPermutationTimeOffset() const`
- L270 _public prototype_ `const FChooserEvaluationContext* GetContext(const FRole& Role) const;`
- L271 _public prototype_ `FChooserEvaluationContext* GetContext(const FRole& Role);`
- L273 _public function_ `TArrayView<FChooserEvaluationContext*> GetContexts()`
- L275 _public function_ `const FRoleToIndex& GetRoleToIndex() const`
- L278 _public function_ `void SetAssetsToConsider(TConstArrayView<const UObject*> InAssetsToConsider)` — `UE_DEPRECATED(5.7, "Use SetAssetsToConsiderSet instead")`
- L288 _public function_ `TConstArrayView<const UObject*> GetAssetsToConsider() const` — `UE_DEPRECATED(5.7, "Use GetAssetsToConsiderSet instead")`
- L298 _public function_ `const TArray<const UObject*>& GetInternalDeprecatedAssetsToConsider() const` — `UE_DEPRECATED(5.7, "Unnecessary once deprecated GetAssetsToConsiderSet / SetAssetsToConsiderSet have been removed")`
- L306 _public function_ `void SetInternalDeprecatedAssetsToConsider(TArray<const UObject*>& InAssetsToConsider)` — `UE_DEPRECATED(5.7, "Unnecessary once deprecated GetAssetsToConsiderSet / SetAssetsToConsiderSet have been removed")`
- L313 _public function_ `void SetAssetsToConsiderSet(const FStackAssetSet* InAssetsToConsider)`
- L322 _public function_ `const FStackAssetSet* GetAssetsToConsiderSet() const`
- L331 _public function_ `void SetAssetIndexesToConsiderPerDatabase(const FStackDatabaseToAssetIndexes* InAssetIndexesToConsiderPerDatabase)`
- L336 _public function_ `const FStackDatabaseToAssetIndexes* GetAssetIndexesToConsiderPerDatabase() const`
- L342 _public function_ `const FPoseSearchEvent& GetEventToSearch() const` — Experimental, this feature might be removed without warning, not for production use
- L345 _public prototype_ `FTransform GetWorldBoneTransformAtTime(float SampleTime, const FRole& SampleRole, int8 SchemaBoneIdx);` — returns the world space transform of the bone SchemaBoneIdx at time SampleTime
- L348 _public function_ `void SetAsyncBuildIndexInProgress()`
- L349 _public function_ `void ResetAsyncBuildIndexInProgress()`
- L350 _public function_ `bool IsAsyncBuildIndexInProgress() const`
- L353 _public function_ `bool AnyCachedQuery() const`
- L354 _public function_ `void AddNewFeatureVectorBuilder(const UPoseSearchSchema* Schema)`
- L355 _public prototype_ `TArrayView<float> EditFeatureVector();`
- L357 _public prototype_ `const UPoseSearchFeatureChannel* GetCachedChannelData(uint32 ChannelUniqueIdentifier, const UPoseSearchFeatureChannel* Channel, TConstArrayView<float>& CachedChannelData);`
- L358 _public function_ `bool IsUseCachedChannelData() const`
- L359 _public function_ `void SetUseCachedChannelData(bool bInUseCachedChannelData)`
- L362 _public function_ `bool IsContinuingInteraction() const` — Experimental, this feature might be removed without warning, not for production use
- L364 _public function_ `void SetContinuingInteraction(bool bInIsContinuingInteraction)` — Experimental, this feature might be removed without warning, not for production use
- L367 _public function_ `bool IsContinuingContextInteraction() const` — Experimental, this feature might be removed without warning, not for production use
- L369 _public function_ `void SetContinuingContextInteraction(bool bInIsContinuingContextInteraction)` — Experimental, this feature might be removed without warning, not for production use
- L372 _private prototype_ `float GetSampleCurveValueInternal(float SampleTime, const FName& CurveName, const FRole& SampleRole);`
- L373 _private prototype_ `FVector GetSamplePositionInternal(float SampleTime, float OriginTime, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, const FVector* SampleBonePositionWorldOverride = nullptr);`
- L374 _private prototype_ `FQuat GetSampleRotationInternal(float SampleTime, float OriginTime, int8 SchemaSampleBoneIdx, int8 SchemaOriginBoneIdx, const FRole& SampleRole, const FRole& OriginRole, const FQuat* SampleBoneRotationWorldOverride = nullptr);`
- L375 _private prototype_ `FTransform GetWorldRootBoneTransformAtTime(float SampleTime, const FRole& SampleRole) const;`
- L376 _private prototype_ `void UpdateContinuingPoseValues();`
- L378 _private member_ `TArray<FChooserEvaluationContext*, TInlineAllocator<PreallocatedRolesNum, TMemStackAllocator<>>> AnimContexts;`
- L379 _private member_ `TArray<const IPoseHistory*, TInlineAllocator<PreallocatedRolesNum, TMemStackAllocator<>>> PoseHistories;`
- L380 _private member_ `FRoleToIndex RoleToIndex;`
- L383 _private member_ `const FStackAssetSet* AssetsToConsider = nullptr;` — if AssetsToConsider is not empty, we'll search only for poses from UObject(s) that are in the AssetsToConsider
- L385 _private member_ `const FStackDatabaseToAssetIndexes* AssetIndexesToConsiderPerDatabase = nullptr;`
- L388 _private member_ `TArray<const UObject*> AssetsToConsider_DEPRECATED;` — `UE_DEPRECATED(5.7, "Unnecessary once deprecated GetAssetsToConsiderSet / SetAssetsToConsiderSet have been removed")`
- L390 _private member_ `const FPoseSearchEvent EventToSearch;`
- L392 _private member_ `const float DesiredPermutationTimeOffset = 0.f;`
- L396 _private member_ `FSearchResult ContinuingPoseSearchResult;` — search result used to extract the continuing pose properties, except for gathering the continuing pose values, where we use ContinuingPoseValuesDatabasePoseIdx. More details in ContinuingPoseValuesDatabasePoseIdx comments
- L406 _private member_ `FDatabasePoseIdx ContinuingPoseValuesDatabasePoseIdx;` — database - pose index pair used to extract the continuing pose vector properties (values) the reason it can differ from the ContinuingPoseSearchResult (database - pose index pair) is because we build and cache a query only using a schema, NOT a database (for performance reasons), BUT we want to be able to calculate the continuing pose from different databases sharing the same animation assets AND same schema, and evaluate the continuing pose feature data across both of them. When this happens, the query gets created using the FIRST database pose value that could slightly differs, because of quantization of time, numerical errors, not common normalization sets, etc, BUT we still want to keep this logic consistent to the fact we created the query and cached it for the common schema, NOT per database, so we need to "lie" to the system by providing a ContinuingPoseSearchResult to gather continuing pose properties such as pose index, database etc, and rely on "ContinuingPoseValuesDatabasePoseIdx" to gather the continuing pose feature values vector (ContinuingPoseValues), used in the channels as cached version of the data that could have been caluclated from the pose history
- L408 _private member_ `const FFloatInterval PoseJumpThresholdTime;`
- L409 _private member_ `bool bUseCachedChannelData = false;`
- L412 _private member_ `TConstArrayView<float> ContinuingPoseValues;` — if ContinuingPoseValuesDatabasePoseIdx is valid, this array view references the continuing pose values (feature vector data)
- L414 _private member_ `TStackAlignedArray<float> ContinuingPoseValuesData;` — buffer optionally used in case the continuing pose needed to be reconstructed. ContinuingPoseValues will reference it
- L417 _private member_ `TMap<uint32, FTransform, TInlineSetAllocator<64, TMemStackSetAllocator<>>> CachedTransforms;` — transforms cached in world space
- L419 _private member_ `TArray<FCachedQuery, TInlineAllocator<PreallocatedCachedQueriesNum, TMemStackAllocator<>>> CachedQueries;`
- L420 _private member_ `TArray<FCachedPCAQuery, TInlineAllocator<PreallocatedCachedQueriesNum, TMemStackAllocator<>>> CachedPCAQueries;`
- L423 _private member_ `TMap<uint32, FCachedChannel, TInlineSetAllocator<PreallocatedCachedChannelDataNum, TMemStackSetAllocator<>>> CachedChannels;` — mapping channel unique identifier (hash) to FCachedChannel
- L426 _private member_ `bool bIsContinuingInteraction = false;` — Experimental, this feature might be removed without warning, not for production use
- L429 _private member_ `bool bIsContinuingContextInteraction = false;` — Experimental, this feature might be removed without warning, not for production use
- L432 _private member_ `bool bAsyncBuildIndexInProgress = false;`
- L489 _public prototype_ `void Track(const UPoseSearchDatabase* Database, int32 PoseIdx = INDEX_NONE, EPoseCandidateFlags PoseCandidateFlags = EPoseCandidateFlags::None, const FPoseSearchCost& Cost = FPoseSearchCost());`
- L490 _public prototype_ `void Track(const UPoseSearchDatabase* Database, int32 PoseIdx, EPoseCandidateFlags PoseCandidateFlags, TConstArrayView<float> DynamicWeightsSqrt, float ContinuingPoseCostAddend, float ContinuingInteractionCostAddend, float ContinuingContextInteractionCostAddend);`
- L492 _public function_ `const TMap<const UPoseSearchDatabase*, FBestPoseCandidates>& GetBestPoseCandidatesMap() const`
- L498 _private member_ `TMap<const UPoseSearchDatabase*, FBestPoseCandidates> BestPoseCandidatesMap;`

#### struct `UE::PoseSearch::FSearchContext::FPoseCandidate`  
`struct FPoseCandidate`  
_L439-451_
- L441 _public function_ `FPoseCandidate(int32 InPoseIdx = 0, FPoseSearchCost InCost = FPoseSearchCost(), EPoseCandidateFlags InPoseCandidateFlags = EPoseCandidateFlags::None) : PoseIdx(InPoseIdx) , Cost(InCost) , PoseCandidateFlags(InPoseCandidateFlags)`
- L448 _public member_ `int32 PoseIdx = 0;`
- L449 _public member_ `FPoseSearchCost Cost;`
- L450 _public member_ `EPoseCandidateFlags PoseCandidateFlags = EPoseCandidateFlags::None;`

#### struct `UE::PoseSearch::FSearchContext::FBestPoseCandidates`  
`struct FBestPoseCandidates`  
_L453-487_
- L455 _public prototype_ `FBestPoseCandidates();`
- L456 _public prototype_ `void Add(int32 PoseIdx, EPoseCandidateFlags PoseCandidateFlags, const FPoseSearchCost& Cost);`
- L457 _public prototype_ `bool IterateOverBestPoseCandidates(const TFunctionRef<bool(const FPoseCandidate& PoseCandidate)> IterateOverBestPoseCandidatesFunction) const;`
- L460 _public prototype_ `int32 Num() const;` — `UE_DEPRECATED(5.7, "Use IterateOverBestPoseCandidates to iterate over FBestPoseCandidates instead")`
- L462 _public prototype_ `FPoseCandidate GetUnsortedCandidate(int32 Index) const;` — `UE_DEPRECATED(5.7, "Use IterateOverBestPoseCandidates to iterate over FBestPoseCandidates instead")`
- L476 _private member_ `TArray<FPoseCandidate> TransientPoseCandidates;` — max heap of Valid_Pose(s). It could contains duplicate poses, that we filter out in IterateOverBestPoseCandidates!
- L486 _private member_ `TSet<FPoseCandidate, FPoseCandidatePoseIdxKeyFunc> PermanentPoseCandidates;` — set of Valid_ContinuingPose(s) and Valid_CurrentPose(s). the set contains unique poses with the lowest cost and an union of their EPoseCandidateFlags

#### struct `UE::PoseSearch::FSearchContext::FBestPoseCandidates::FPoseCandidateHeapCompare`  
`struct FPoseCandidateHeapCompare`  
_L466-473_
- L468 _public function_ `bool operator()(const FPoseCandidate& A, const FPoseCandidate& B) const`

#### struct `UE::PoseSearch::FSearchContext::FBestPoseCandidates::FPoseCandidatePoseIdxKeyFunc`  
`struct FPoseCandidatePoseIdxKeyFunc : BaseKeyFuncs<FPoseCandidate, FPoseCandidate, false>`  
_L478-483_
- inherits: `BaseKeyFuncs<FPoseCandidate,FPoseCandidate,false>`
- L480 _public function_ `static KeyInitType GetSetKey(ElementInitType& Element)`
- L481 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L482 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API POSESEARCH_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace PoseSearch` (scope `UE`)
- L42 _typedef_ `typedef TSet<int32, DefaultKeyFuncs<int32>, TInlineSetAllocator<8, TMemStackSetAllocator<>>> FStackAssetIndexes;` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use usually used as set of asset indexes to consider (per database) Experimental, this feature might be removed without warning, not for production use
- L44 _typedef_ `typedef TMap<const UPoseSearchDatabase*, FStackAssetIndexes, TInlineSetAllocator<8, TMemStackSetAllocator<>>> FStackDatabaseToAssetIndexes;` (scope `UE::PoseSearch`) — usually used as container to map database to what asset indexes to consider
- L47 _prototype_ `const UObject* GetAnimContext(const FChooserEvaluationContext* Context);` (scope `UE::PoseSearch`) — Utils functions
- L49 _prototype_ `const FTransform& GetContextTransform(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L50 _prototype_ `const USkeleton* GetContextSkeleton(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`)
- L51 _prototype_ `const AActor* GetContextOwningActor(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`)
- L52 _prototype_ `FVector GetContextLocation(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`)
- L55 _prototype_ `const USkeletalMeshComponent* GetContextSkeletalMeshComponent(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L57 _prototype_ `const FBoneContainer GetBoneContainer(const UObject* AnimContext, bool bCheckIsInGameThread = true);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L82 _prototype_ `ENUM_CLASS_FLAGS(EPoseCandidateFlags);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchCost.h` (Public)


#### struct `FPoseSearchCost`  
`struct FPoseSearchCost`  
_L8-102_
- reflection: `USTRUCT()`
- L13 _public prototype_ `FPoseSearchCost() = default;`
- L14 _public prototype_ `~FPoseSearchCost() = default;`
- L15 _public prototype_ `FPoseSearchCost(const FPoseSearchCost&) = default;`
- L16 _public prototype_ `FPoseSearchCost(FPoseSearchCost&&) = default;`
- L17 _public prototype_ `FPoseSearchCost& operator=(const FPoseSearchCost&) = default;`
- L18 _public prototype_ `FPoseSearchCost& operator=(FPoseSearchCost&&) = default;`
- L20 _public function_ `FPoseSearchCost(float DissimilarityCost, float InNotifyCostAddend = 0.f, float InContinuingPoseCostAddend = 0.f, float InContinuingInteractionCostAddend = 0.f, float InContinuingContextInteractionCostAddend = 0.f) : TotalCost(DissimilarityCost + InNotifyCostAddend + InContinuingPoseCostAddend + InContinuingInteractionCostAddend + InContinuingContextInteractionCostAddend) #if WITH_EDITORONLY_DATA , NotifyCostAddend(InNotifyCostAddend) , ContinuingPoseCostAddend(InContinuingPoseCostAddend) , ContinuingInteractionCostAddend(InContinuingInteractionCostAddend) , ContinuingContextInteractionCostAddend(InContinuingContextInteractionCostAddend) #endif`
- L31 _public function_ `static bool IsCostValid(const float Cost)`
- L32 _public function_ `bool IsValid() const`
- L34 _public function_ `operator float() const`
- L37 _public function_ `float GetCostAddend() const`
- L39 _public function_ `float GetNotifyCostAddend() const`
- L40 _public function_ `float GetContinuingPoseCostAddend() const`
- L41 _public function_ `float GetContinuingInteractionCostAddend() const`
- L42 _public function_ `float GetContinuingContextInteractionCostAddend() const`
- L79 _protected member_ `float TotalCost = MAX_flt;` — `UPROPERTY()` — TotalCost is the sum of all the Cost contributions (dissimilarity, notifies, continuing pose, continuing interaction, and continuing context interaction costs)
- L85 _protected member_ `float NotifyCostAddend = 0.f;` — `UPROPERTY()` — Notify Cost Bias contribution
- L89 _protected member_ `float ContinuingPoseCostAddend = 0.f;` — `UPROPERTY()` — Continuing Pose Cost Bias contribution
- L94 _protected member_ `float ContinuingInteractionCostAddend = 0.f;` — `UPROPERTY()` — Experimental, this feature might be removed without warning, not for production use Continuing Interaction Cost Bias contribution
- L99 _protected member_ `float ContinuingContextInteractionCostAddend = 0.f;` — `UPROPERTY()` — Experimental, this feature might be removed without warning, not for production use Continuing Context Interaction Cost Bias contribution

#### Free symbols / members of external scopes

- L45 _function_ `friend FArchive& operator<<(FArchive& Ar, FPoseSearchCost& PoseSearchCost)`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchCustomVersion.h` (Public)


#### struct `FPoseSearchCustomVersion`  
`struct FPoseSearchCustomVersion`  
_L11-37_
- desc: Custom serialization version for all packages containing PoseSearch dependent asset types
- L33 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L36 _private function_ `FPoseSearchCustomVersion()`

#### enum `FPoseSearchCustomVersion::Type`  
`enum Type`  
_L13-30_
- L16 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L19 _public enumerator_ `DeprecatedTrajectoryTypes` — Deprecated FPoseSearchQueryTrajectory and FPoseSearchQueryTrajectorySample. This version matches the RouteId_MotionMatchingState2 event.
- L22 _public enumerator_ `AddedInterruptModeToDebugger` — Added InterruptMode to posesearch debugger. This version matches the RouteId_MotionMatchingState3 event.
- L25 _public enumerator_ `StripOutDisabledDatabaseAnimationsDuringCook` — Strip out disabled Pose Search Database animations during cook
- L28 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L29 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchDatabase.h` (Public)


#### enum `EPoseSearchMode`  
`enum class EPoseSearchMode : int32`  
_L30-45_
- reflection: `UENUM()`
- L33 _public enumerator_ `BruteForce` — Database searches will be evaluated extensively. the system will evaluate all the indexed poses to search for the best one.
- L36 _public enumerator_ `PCAKDTree` — Optimized search mode: the database projects the poses into a PCA space using only the most significant "NumberOfPrincipalComponents" dimensions, and construct a kdtree to facilitate the search.
- L40 _public enumerator_ `VPTree UMETA(DisplayName = "VPTree (Experimental)")` — Experimental, this feature might be removed without warning, not for production use Optimized search mode using a vantage point tree
- L44 _public enumerator_ `EventOnly UMETA(DisplayName = "EventOnly (Experimental)")` — Experimental, this feature might be removed without warning, not for production use search will only be performed on events.

#### enum `EPoseSearchMirrorOption`  
`enum class EPoseSearchMirrorOption : int32`  
_L48-53_
- reflection: `UENUM()`
- L50 _public enumerator_ `UnmirroredOnly UMETA(DisplayName = "Original Only")`
- L51 _public enumerator_ `MirroredOnly UMETA(DisplayName = "Mirrored Only")`
- L52 _public enumerator_ `UnmirroredAndMirrored UMETA(DisplayName = "Original and Mirrored")`

#### struct `FPoseSearchDatabaseAnimationAssetBase`  
`struct FPoseSearchDatabaseAnimationAssetBase`  
_L56-131_
- reflection: `USTRUCT()`
- L59 _public prototype_ `virtual ~FPoseSearchDatabaseAnimationAssetBase() = default;`
- L60 _public function_ `virtual UObject* GetAnimationAsset() const`
- L62 _public prototype_ `virtual float GetPlayLength(const FVector& BlendParameters) const;`
- L64 _public function_ `virtual int32 GetNumRoles() const`
- L65 _public function_ `virtual UE::PoseSearch::FRole GetRole(int32 RoleIndex) const`
- L66 _public prototype_ `virtual UAnimationAsset* GetAnimationAssetForRole(const UE::PoseSearch::FRole& Role) const;`
- L67 _public prototype_ `virtual FTransform GetRootTransformOriginForRole(const UE::PoseSearch::FRole& Role) const;`
- L69 _public prototype_ `virtual bool IsSkeletonCompatible(TObjectPtr<const UPoseSearchSchema> InSchema) const;`
- L71 _public prototype_ `virtual bool IsMirrorOptionCompatible(TObjectPtr<const UPoseSearchSchema> InSchema) const;` — Experimental, this feature might be removed without warning, not for production use
- L73 _public prototype_ `virtual USkeletalMesh* GetPreviewMeshForRole(const UE::PoseSearch::FRole& Role) const;` — Experimental, this feature might be removed without warning, not for production use
- L74 _public prototype_ `virtual void IterateOverSamplingParameter(const TFunction<void(const FVector& BlendParameters)>& ProcessSamplingParameter) const;`
- L78 _public prototype_ `virtual bool UpdateFrom(const FPoseSearchDatabaseAnimationAssetBase& Source);`
- L79 _public function_ `virtual bool IsDisableReselection() const`
- L80 _public function_ `virtual void SetDisableReselection(bool bValue)`
- L81 _public function_ `virtual UClass* GetAnimationAssetStaticClass() const`
- L82 _public function_ `virtual bool IsLooping() const`
- L83 _public prototype_ `virtual const FString GetName() const;`
- L84 _public function_ `virtual bool IsEnabled() const`
- L85 _public function_ `virtual void SetIsEnabled(bool bValue)`
- L86 _public function_ `virtual bool IsRootMotionEnabled() const`
- L87 _public function_ `virtual EPoseSearchMirrorOption GetMirrorOption() const`
- L90 _public function_ `virtual FFloatInterval GetSamplingRange() const` — [0, 0] represents the entire frame range of the original animation.
- L91 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange)`
- L92 _public prototype_ `virtual FFloatInterval GetEffectiveSamplingRange(const FVector& BlendParameters) const;`
- L94 _public prototype_ `static FFloatInterval GetEffectiveSamplingRange(float PlayLength, const FFloatInterval& SamplingRange);`
- L96 _public prototype_ `virtual int64 GetEditorMemSize() const;`
- L97 _public function_ `virtual int64 GetApproxCookedSize() const`
- L99 _public function_ `bool IsSynchronizedWithExternalDependency() const`
- L103 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 1))` — This allows users to enable or exclude animations from this database. Useful for debugging.
- L107 _public member_ `bool bDisableReselection = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 2))` — if bDisableReselection is true, poses from the same asset cannot be reselected. Useful to avoid jumping on frames on the same looping animations
- L112 _public member_ `EPoseSearchMirrorOption MirrorOption = EPoseSearchMirrorOption::UnmirroredOnly;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 3))` — This allows users to set if this animation is original only (no mirrored data), original and mirrored, or only the mirrored version of this animation. It requires the mirror table to be set up in the database Schema.
- L117 _public member_ `uint32 BranchInId = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", meta = (DisplayPriority = 20))` — BranchInId != 0 when this asset has been added via SynchronizeWithExternalDependencies. To delete it, remove the PoseSearchBranchIn notify state

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseAnimationAssetBase> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimationAssetBase>`  
_L133-136_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimationAssetBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L135-135_

#### struct `FPoseSearchDatabaseAnimationAsset`  
`struct FPoseSearchDatabaseAnimationAsset : public FPoseSearchDatabaseAnimationAssetBase`  
_L139-218_
- reflection: `USTRUCT(BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- L144 _public member_ `TObjectPtr<UObject> AnimAsset;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L150 _public member_ `bool bUseSingleSample = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 4))` — If true this BlendSpace will output a single segment in the database.
- L154 _public member_ `bool bUseGridForSampling = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample", EditConditionHides, DisplayPriority = 5))` — When turned on, this will use the set grid samples of the blend space asset for sampling. This will override the Number of Horizontal/Vertical Samples.
- L158 _public member_ `int32 NumberOfHorizontalSamples = 9;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample && !bUseGridForSampling", EditConditionHides, ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 6))` — Sets the number of horizontal samples in the blend space to pull the animation data coverage from. The larger the samples the more the data, but also the more memory and performance it takes.
- L162 _public member_ `int32 NumberOfVerticalSamples = 2;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample && !bUseGridForSampling", EditConditionHides, ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 7))` — Sets the number of vertical samples in the blend space to pull the animation data coverage from.The larger the samples the more the data, but also the more memory and performance it takes.
- L166 _public member_ `float BlendParamX = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseSingleSample", EditConditionHides, DisplayPriority = 8))` — BlendParams used to sample this BlendSpace
- L170 _public member_ `float BlendParamY = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseSingleSample", EditConditionHides, DisplayPriority = 9))` — BlendParams used to sample this BlendSpace
- L176 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampToMinMaxLimits, DisplayPriority = 2))` — It allows users to set a time range to an individual blend space in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original blend space). If set to [0, 0] it will be the entire frame range of the original blend space.
- L178 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L179 _public prototype_ `static bool IsLooping(const UObject* AnimAsset, const FFloatInterval& SamplingRange);`
- L180 _public prototype_ `virtual bool IsLooping() const override;`
- L182 _public prototype_ `static bool IsRootMotionEnabled(const UObject* AnimAsset);`
- L183 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L185 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L186 _public prototype_ `virtual FFloatInterval GetEffectiveSamplingRange(const FVector& BlendParameters) const override;`
- L187 _public prototype_ `virtual void IterateOverSamplingParameter(const TFunction<void(const FVector& BlendParameters)>& ProcessSamplingParameter) const override;`
- L188 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L192 _public prototype_ `USkeletalMesh* GetPreviewMeshForRole(const UE::PoseSearch::FRole& Role) const;`
- L195 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`
- L196 _public prototype_ `virtual float GetPlayLength(const FVector& BlendParameters) const override;`
- L198 _public prototype_ `virtual int32 GetNumRoles() const override;`
- L199 _public prototype_ `virtual UE::PoseSearch::FRole GetRole(int32 RoleIndex) const override;`
- L200 _public prototype_ `virtual UAnimationAsset* GetAnimationAssetForRole(const UE::PoseSearch::FRole& Role) const override;`
- L201 _public prototype_ `virtual FTransform GetRootTransformOriginForRole(const UE::PoseSearch::FRole& Role) const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseAnimationAsset> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimationAsset>`  
_L220-223_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimationAsset>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L222-222_

#### struct `FPoseSearchDatabaseSequence`  
`struct UE_DEPRECATED(5.7, "Use FPoseSearchDatabaseAnimationAsset instead. To convert your struct to support the new APIs use ") FPoseSearchDatabaseSequence : public FPoseSearchDatabaseAnimationAssetBase`  
_L228-262_
- reflection: `USTRUCT(BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- desc: A sequence entry in a UPoseSearchDatabase.
- L233 _public member_ `TObjectPtr<UAnimSequence> Sequence;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L242 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition="BranchInId == 0", ClampToMinMaxLimits, DisplayPriority = 2))` — It allows users to set a time range to an individual animation sequence in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original sequence). If set to [0, 0] it will be the entire frame range of the original sequence. Set to readonly if this asset is synchronized via PoseSearchBranchIn notify state. To edit its value update the associated PoseSearchBranchIn in Sequence
- L244 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L245 _public prototype_ `virtual bool IsLooping() const override;`
- L246 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L247 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L248 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L251 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseSequence> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseSequence>`  
_L265-268_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseSequence>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L267-267_

#### struct `FPoseSearchDatabaseBlendSpace`  
`struct UE_DEPRECATED(5.7, "Use FPoseSearchDatabaseAnimationAsset instead. To convert your struct to support the new APIs use ") FPoseSearchDatabaseBlendSpace : public FPoseSearchDatabaseAnimationAssetBase`  
_L273-339_
- reflection: `USTRUCT(BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- desc: An blend space entry in a UPoseSearchDatabase.
- L278 _public member_ `TObjectPtr<UBlendSpace> BlendSpace;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L284 _public member_ `bool bUseSingleSample = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 4))` — If true this BlendSpace will output a single segment in the database.
- L288 _public member_ `bool bUseGridForSampling = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample", EditConditionHides, DisplayPriority = 5))` — When turned on, this will use the set grid samples of the blend space asset for sampling. This will override the Number of Horizontal/Vertical Samples.
- L292 _public member_ `int32 NumberOfHorizontalSamples = 9;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample && !bUseGridForSampling", EditConditionHides, ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 6))` — Sets the number of horizontal samples in the blend space to pull the animation data coverage from. The larger the samples the more the data, but also the more memory and performance it takes.
- L296 _public member_ `int32 NumberOfVerticalSamples = 2;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "!bUseSingleSample && !bUseGridForSampling", EditConditionHides, ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 7))` — Sets the number of vertical samples in the blend space to pull the animation data coverage from.The larger the samples the more the data, but also the more memory and performance it takes.
- L300 _public member_ `float BlendParamX = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseSingleSample", EditConditionHides, DisplayPriority = 8))` — BlendParams used to sample this BlendSpace
- L304 _public member_ `float BlendParamY = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bUseSingleSample", EditConditionHides, DisplayPriority = 9))` — BlendParams used to sample this BlendSpace
- L310 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampToMinMaxLimits, DisplayPriority = 2))` — It allows users to set a time range to an individual blend space in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original blend space). If set to [0, 0] it will be the entire frame range of the original blend space.
- L312 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L313 _public prototype_ `virtual bool IsLooping() const override;`
- L314 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L315 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L316 _public prototype_ `virtual FFloatInterval GetEffectiveSamplingRange(const FVector& BlendParameters) const override;`
- L317 _public prototype_ `virtual void IterateOverSamplingParameter(const TFunction<void(const FVector& BlendParameters)>& ProcessSamplingParameter) const override;`
- L318 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L321 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`
- L322 _public prototype_ `virtual float GetPlayLength(const FVector& BlendParameters) const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseBlendSpace> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseBlendSpace>`  
_L342-345_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseBlendSpace>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L344-344_

#### struct `FPoseSearchDatabaseAnimComposite`  
`struct UE_DEPRECATED(5.7, "Use FPoseSearchDatabaseAnimationAsset instead. To convert your struct to support the new APIs use ") FPoseSearchDatabaseAnimComposite : public FPoseSearchDatabaseAnimationAssetBase`  
_L350-384_
- reflection: `USTRUCT(BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- desc: An entry in a UPoseSearchDatabase.
- L355 _public member_ `TObjectPtr<UAnimComposite> AnimComposite;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L364 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition="BranchInId == 0", ClampToMinMaxLimits, DisplayPriority = 3))` — It allows users to set a time range to an individual animation composite in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original composite). If set to [0, 0] it will be the entire frame range of the original composite. Set to readonly if this asset is synchronized via PoseSearchBranchIn notify state. To edit its value update the associated PoseSearchBranchIn in AnimComposite
- L366 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L367 _public prototype_ `virtual bool IsLooping() const override;`
- L368 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L369 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L370 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L373 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseAnimComposite> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimComposite>`  
_L387-390_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimComposite>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L389-389_

#### struct `FPoseSearchDatabaseAnimMontage`  
`struct UE_DEPRECATED(5.7, "Use FPoseSearchDatabaseAnimationAsset instead. To convert your struct to support the new APIs use ") FPoseSearchDatabaseAnimMontage : public FPoseSearchDatabaseAnimationAssetBase`  
_L395-429_
- reflection: `USTRUCT(BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- desc: An anim montage entry in a UPoseSearchDatabase.
- L400 _public member_ `TObjectPtr<UAnimMontage> AnimMontage;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L409 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition="BranchInId == 0", ClampToMinMaxLimits, DisplayPriority = 2))` — It allows users to set a time range to an individual animation montage in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original montage). If set to [0, 0] it will be the entire frame range of the original montage. Set to readonly if this asset is synchronized via PoseSearchBranchIn notify state. To edit its value update the associated PoseSearchBranchIn in AnimMontage
- L411 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L412 _public prototype_ `virtual bool IsLooping() const override;`
- L413 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L414 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L415 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L418 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseAnimMontage> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimMontage>`  
_L432-435_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseAnimMontage>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L434-434_

#### struct `FPoseSearchDatabaseMultiAnimAsset`  
`struct UE_DEPRECATED(5.7, "Use FPoseSearchDatabaseAnimationAsset instead. To convert your struct to support the new APIs use ") FPoseSearchDatabaseMultiAnimAsset : public FPoseSearchDatabaseAnimationAssetBase`  
_L439-491_
- reflection: `USTRUCT(Experimental, BlueprintType, Category = "Animation|Pose Search")`
- inherits: `FPoseSearchDatabaseAnimationAssetBase`
- L444 _public member_ `TObjectPtr<UMultiAnimAsset> MultiAnimAsset;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayPriority = 0))`
- L449 _public member_ `int32 NumberOfHorizontalSamples = 1;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 6))` — Sets the number of horizontal samples in the blend spaces referenced by the UMultiAnimAsset to pull the animation data coverage from. The larger the samples the more the data, but also the more memory and performance it takes.
- L453 _public member_ `int32 NumberOfVerticalSamples = 1;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", UIMin = "1", UIMax = "25", DisplayPriority = 7))` — Sets the number of vertical samples for the blend spaces referenced by the UMultiAnimAsset to pull the animation data coverage from. The larger the samples the more the data, but also the more memory and performance it takes.
- L459 _public member_ `FFloatInterval SamplingRange = FFloatInterval(0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampToMinMaxLimits, DisplayPriority = 2))` — It allows users to set a time range to an individual UMultiAnimAsset in the database. This is effectively trimming the beginning and end of the animation in the database (not in the original UMultiAnimAsset). If set to [0, 0] it will be the entire frame range of the original UMultiAnimAsset.
- L461 _public prototype_ `virtual UClass* GetAnimationAssetStaticClass() const override;`
- L462 _public prototype_ `virtual bool IsLooping() const override;`
- L463 _public prototype_ `virtual bool IsRootMotionEnabled() const override;`
- L464 _public function_ `virtual FFloatInterval GetSamplingRange() const override`
- L465 _public prototype_ `virtual void IterateOverSamplingParameter(const TFunction<void(const FVector& BlendParameters)>& ProcessSamplingParameter) const override;`
- L466 _public function_ `virtual void SetSamplingRange(const FFloatInterval& NewRange) override`
- L470 _public prototype_ `USkeletalMesh* GetPreviewMeshForRole(const UE::PoseSearch::FRole& Role) const;`
- L473 _public prototype_ `virtual UObject* GetAnimationAsset() const override;`
- L474 _public prototype_ `virtual float GetPlayLength(const FVector& BlendParameters) const override;`
- L475 _public prototype_ `virtual int32 GetNumRoles() const override;`
- L476 _public prototype_ `virtual UE::PoseSearch::FRole GetRole(int32 RoleIndex) const override;`
- L477 _public prototype_ `virtual UAnimationAsset* GetAnimationAssetForRole(const UE::PoseSearch::FRole& Role) const override;`
- L478 _public prototype_ `virtual FTransform GetRootTransformOriginForRole(const UE::PoseSearch::FRole& Role) const override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchDatabaseMultiAnimAsset> : public TStructOpsTypeTraitsBase2<FPoseSearchDatabaseMultiAnimAsset>`  
_L494-497_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchDatabaseMultiAnimAsset>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L496-496_

#### class `UPoseSearchDatabase`  
`class UPoseSearchDatabase : public UDataAsset`  
_L502-755_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Animation|Pose Search", meta = (DisplayName = "Pose Search Database"))`
- inherits: `UDataAsset`
- desc: A data asset for indexing a collection of animation sequences.
- L509 _public member_ `TObjectPtr<const UPoseSearchSchema> Schema;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Database")` — The Schema sets what channels this database will use to match against (bones, trajectory and what properties of those you’re interested in, such as position and velocity).
- L516 _public member_ `float ContinuingPoseCostBias = -0.01f;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ExcludeFromHash))` — Cost added to the continuing pose from this database. This allows users to apply a cost bias (positive or negative) to the continuing pose. This is useful to help the system stay in one animation segment longer, or shorter depending on how you set this bias. Negative values make it more likely to be picked, or stayed in, positive values make it less likely to be picked or stay in. Note: excluded from DDC hash, since used only at runtime in SearchContinuingPose
- L521 _public member_ `float BaseCostBias = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Base Cost added or removed to all poses from this database. It can be overridden by Anim Notify: Pose Search Modify Cost at the frame level of animation data. Negative values make it more likely to be picked, or stayed in, Positive values make it less likely to be picked or stay in.
- L526 _public member_ `float LoopingCostBias = -0.005f;` — `UPROPERTY(EditAnywhere, Category = "Database")` — Cost added to all looping animation assets in this database. This allows users to make it more or less likely to pick the looping animation segments. Negative values make it more likely to be picked, or stayed in, Positive values make it less likely to be picked or stay in.
- L535 _public member_ `float ContinuingInteractionCostBias = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ExcludeFromHash))` — Cost added to poses from this database (if setup with UMultiAnimAsset assets in "interaction mode") as continuation of a previous interaction (same anim contexts with the same assigned roles) This allows users to apply a cost bias (positive or negative) to poses following up an interaction. This is useful to help the system stay in one animation segment longer, or shorter depending on how you set this bias. Negative values make it more likely to be picked, or stayed in, positive values make it less likely to be picked or stay in. Note: excluded from DDC hash, since used only at runtime Experimental, this feature might be removed without warning, not for production use
- L540 _public member_ `float ContinuingContextInteractionCostBias = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (ExcludeFromHash))` — behaving like ContinuingInteractionCostBias, but for continuing interactions with the same anim contexts (e.g. same actors) Experimental, this feature might be removed without warning, not for production use
- L546 _public member_ `FFloatInterval ExcludeFromDatabaseParameters = FFloatInterval(0.f, -0.3f);` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (AllowInvertedInterval))` — These settings allow users to trim the start and end of animations in the database to preserve start/end frames for blending, and prevent the system from selecting the very last frames before it blends out. valid animation frames will be AnimationAssetTimeStart + ExcludeFromDatabaseParameters.Min, AnimationAssetTimeEnd + ExcludeFromDatabaseParameters.Max
- L550 _public member_ `FFloatInterval AdditionalExtrapolationTime = FFloatInterval(-100.f, 100.f);` — `UPROPERTY(EditAnywhere, Category = "Database", meta = (AllowInvertedInterval))` — extrapolation of animation assets will be clamped by AnimationAssetTimeStart + AdditionalExtrapolationTime.Min, AnimationAssetTimeEnd + AdditionalExtrapolationTime.Max
- L556 _private member_ `TArray<FInstancedStruct> AnimationAssets_DEPRECATED;` — `UE_DEPRECATED(5.7, "Please reference DatabaseAnimationAssets instead")` — `UPROPERTY()`
- L559 _private member_ `TArray<FPoseSearchDatabaseAnimationAsset> DatabaseAnimationAssets;` — `UPROPERTY()`
- L565 _public member_ `TArray<FName> Tags;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")` — Array of tags that can be used as metadata.
- L571 _public member_ `TObjectPtr<const UPoseSearchNormalizationSet> NormalizationSet;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Database")` — This optional asset defines a list of databases you want to normalize together. Without it, it would be difficult to compare costs from separately normalized databases containing different types of animation, like only idles versus only runs animations, given that the range of movement would be dramatically different.
- L576 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (ExcludeFromHash))` — If null, the default preview mesh for the skeleton will be used. Otherwise, this will be used in preview scenes. @todo: Move this to be a setting in the Pose Search Database editor.
- L581 _public member_ `EPoseSearchMode PoseSearchMode = EPoseSearchMode::PCAKDTree;` — `UPROPERTY(EditAnywhere, Category = "Performance")` — This dictates how the database will perform the search.
- L586 _public member_ `int32 NumberOfPrincipalComponents = 4;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (EditCondition = "PoseSearchMode == EPoseSearchMode::PCAKDTree", EditConditionHides, ClampMin = "1", ClampMax = "64", UIMin = "1", UIMax = "64"))` — Number of dimensions used to create the kdtree. More dimensions allows a better explanation of the variance of the dataset that usually translates in better search results, but will imply more memory usage and worse performances.
- L589 _public member_ `int32 KDTreeMaxLeafSize = 16;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (EditCondition = "PoseSearchMode == EPoseSearchMode::PCAKDTree", EditConditionHides, ClampMin = "1", ClampMax = "256", UIMin = "1", UIMax = "256"))`
- L596 _public member_ `int32 KDTreeQueryNumNeighbors = 200;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (DisplayName = "KNNQueryNumNeighbors", EditCondition = "PoseSearchMode == EPoseSearchMode::PCAKDTree || PoseSearchMode == EPoseSearchMode::VPTree", EditConditionHides, ClampMin = "1", ClampMax = "600", UIMin = "1"))` — @todo: rename to KNNQueryNumNeighbors to be usable with the VPTree as well Out of a kdtree search, results will have only an approximate cost, so the database search will select the best “KDTree Query Num Neighbors” poses to perform the full cost analysis, and be able to elect the best pose. Memory & Performance Optimization! If KDTreeQueryNumNeighbors is 1 all the SearchIndexPrivate::Values will be stripped away, and the search will exclusively rely on the KDTree query result from the PCA space encoded values (SearchIndexPrivate::PCAValues).
- L602 _public member_ `float PosePruningSimilarityThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Performance")` — if two poses values (multi dimensional point with the schema cardinality) are closer than PosePruningSimilarityThreshold, only one will be saved into the database FSearchIndexBase (to save memory) and accessed by the two different pose indexes
- L607 _public member_ `float PCAValuesPruningSimilarityThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (EditCondition = "PoseSearchMode == EPoseSearchMode::PCAKDTree", EditConditionHides))` — if two PCA values (multi dimensional point with the GetNumberOfPrincipalComponents cardinality) are closer than PCAValuesPruningSimilarityThreshold, only one will be saved into the database FSearchIndex (to save memory).
- L614 _public member_ `int32 KDTreeQueryNumNeighborsWithDuplicates = 0;` — `UPROPERTY(EditAnywhere, Category = "Performance", meta = (DisplayName = "KNNQueryNumNeighborsWithDuplicates", EditCondition = "PoseSearchMode == EPoseSearchMode::PCAKDTree && PCAValuesPruningSimilarityThreshold > 0", EditConditionHides, ClampMin = "0", ClampMax = "600", UIMin = "1"))` — @todo: rename to KNNQueryNumNeighborsWithDuplicates to be usable with the VPTree as well if PCAValuesPruningSimilarityThreshold > 0 the kdtree will remove duplicates, every result out of the KDTreeQueryNumNeighbors could potentially references multiple poses. KDTreeQueryNumNeighborsWithDuplicates is the upper bound number of poses the system will perform the full cost evaluation. if KDTreeQueryNumNeighborsWithDuplicates is zero then there's no upper bound
- L618 _private member_ `UE::PoseSearch::FSearchIndex SearchIndexPrivate;` — Do not use it directly. Use GetSearchIndex / SetSearchIndex interact with it and validate that is ok to do so.
- L622 _private typedef_ `typedef TMap<const UObject*, TArray<int32>> FCachedAssetMap;` — CachedAssetMap is NOT serialized in operator<< but recalculated by UpdateCachedProperties every time SearchIndexPrivate changes accessing the key const UObject* is protected by FAsyncPoseSearchDatabasesManagement::RequestAsyncBuildIndex so it doesn't have to be TWeakObjectPtr<const UObject> / FObjectKey for GC protection
- L623 _private typedef_ `typedef TPair<const UObject*, TArray<int32>> FCachedAssetMapPair;`
- L624 _private member_ `FCachedAssetMap CachedAssetMap;`
- L627 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDerivedDataRebuildMulticaster);`
- L628 _private member_ `FOnDerivedDataRebuildMulticaster OnDerivedDataRebuild;`
- L630 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSynchronizeWithExternalDependenciesMulticaster);`
- L631 _private member_ `FOnSynchronizeWithExternalDependenciesMulticaster OnSynchronizeWithExternalDependencies;`
- L635 _public prototype_ `virtual ~UPoseSearchDatabase();`
- L637 _public prototype_ `void SetSearchIndex(const UE::PoseSearch::FSearchIndex& SearchIndex);`
- L638 _public prototype_ `const UE::PoseSearch::FSearchIndex& GetSearchIndex() const;`
- L641 _public prototype_ `bool GetSkipSearchIfPossible() const;` — `UE_DEPRECATED(5.8, "no longer necessary API")`
- L646 _public prototype_ `int32 GetPoseIndex(const UObject* AnimationAsset, float AnimationAssetTime, bool bMirrored, const FVector& BlendParameters, const UE::PoseSearch::FStackAssetIndexes* AssetIndexesToConsider = nullptr) const;` — given an AnimationAsset, a normalized time AnimationAssetTime (in [0-1] range for blend spaces), and mirror state bMirrored will retrieve the associated pose index from this database closest in distance to BlendParameters. It'll return INDEX_NONE if it cannot find a pose
- L650 _public prototype_ `void AddAnimationAsset(FInstancedStruct AnimationAsset);` — `UE_DEPRECATED(5.7, "Use AddAnimationAsset(const FPoseSearchDatabaseAnimationAsset& AnimationAsset) instead")`
- L652 _public prototype_ `void AddAnimationAsset(const FPoseSearchDatabaseAnimationAsset& AnimationAsset);`
- L654 _public prototype_ `void InsertAnimationAssetAt(const FPoseSearchDatabaseAnimationAsset& AnimationAsset, int32 AnimationAssetIndex);` — Experimental, this feature might be removed without warning, not for production use
- L655 _public prototype_ `void RemoveAnimationAssetAt(int32 AnimationAssetIndex);`
- L657 _public prototype_ `void SetAnimationAssetAt(const FPoseSearchDatabaseAnimationAsset& AnimationAsset, int32 AnimationAssetIndex);`
- L660 _public prototype_ `const FPoseSearchDatabaseAnimationAsset* GetDatabaseAnimationAsset(int32 AnimationAssetIndex) const;`
- L663 _public prototype_ `const FPoseSearchDatabaseAnimationAsset* GetDatabaseAnimationAsset(const UE::PoseSearch::FSearchIndexAsset& SearchIndexAsset) const;` — `UE_DEPRECATED(5.8, "Use GetDatabaseAnimationAsset(SearchIndexAsset.GetSourceAssetIdx()) instead")`
- L666 _public prototype_ `FPoseSearchDatabaseAnimationAsset* GetMutableDatabaseAnimationAsset(int32 AnimationAssetIndex);` — `UE_DEPRECATED(5.8, "Use SetAnimationAssetAt(AnimationAsset, AnimationAssetIndex) instead")`
- L668 _public prototype_ `FPoseSearchDatabaseAnimationAsset* GetMutableDatabaseAnimationAsset(const UE::PoseSearch::FSearchIndexAsset& SearchIndexAsset);` — `UE_DEPRECATED(5.8, "Use SetAnimationAssetAt(AnimationAsset, SearchIndexAsset.GetSourceAssetIdx()) instead")`
- L670 _public prototype_ `template<typename TDatabaseAnimationAsset> UE_DEPRECATED(5.7, "Use the non templated version of this API") const TDatabaseAnimationAsset* GetDatabaseAnimati`
- L672 _public prototype_ `template<typename TDatabaseAnimationAsset> UE_DEPRECATED(5.7, "Use the non templated version of this API") const TDatabaseAnimationAsset* GetDatabaseAnimati`
- L675 _public prototype_ `float GetRealAssetTime(int32 PoseIdx) const;`
- L676 _public prototype_ `float GetNormalizedAssetTime(int32 PoseIdx) const;`
- L679 _public prototype_ `virtual void PostLoad() override;`
- L680 _public prototype_ `virtual void PreSaveRoot(FObjectPreSaveRootContext ObjectSaveContext) override;`
- L681 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L685 _public prototype_ `UE::PoseSearch::FSearchResult Search(UE::PoseSearch::FSearchContext& SearchContext) const;` — deprecate in favor of Search(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) once we settle on FSearchResults API signatures
- L687 _public prototype_ `UE::PoseSearch::FSearchResult SearchContinuingPose(UE::PoseSearch::FSearchContext& SearchContext) const;` — deprecate in favor of SearchContinuingPose(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) once we settle on FSearchResults API signatures
- L690 _public prototype_ `void Search(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;` — Experimental, this feature might be removed without warning, not for production use
- L692 _public prototype_ `void SearchContinuingPose(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;` — Experimental, this feature might be removed without warning, not for production use
- L694 _public prototype_ `bool Contains(const UObject* Object) const;`
- L697 _public prototype_ `int32 GetNumAnimationAssets() const;` — `UFUNCTION(BlueprintPure, Category = "Animation|Pose Search|Experimental", meta = (BlueprintThreadSafe))`
- L700 _public prototype_ `UObject* GetAnimationAsset(int32 Index) const;` — `UFUNCTION(BlueprintPure, Category = "Animation|Pose Search|Experimental", meta = (BlueprintThreadSafe))`
- L703 _public prototype_ `int32 GetNumberOfPrincipalComponents() const;`
- L705 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L706 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L708 _public typedef_ `typedef FOnDerivedDataRebuildMulticaster::FDelegate FOnDerivedDataRebuild;`
- L709 _public function_ `void RegisterOnDerivedDataRebuild(const FOnDerivedDataRebuild& Delegate)`
- L710 _public function_ `void UnregisterOnDerivedDataRebuild(FDelegateUserObject Unregister)`
- L711 _public function_ `void NotifyDerivedDataRebuild() const`
- L713 _public typedef_ `typedef FOnSynchronizeWithExternalDependenciesMulticaster::FDelegate FOnSynchronizeWithExternalDependencies;`
- L714 _public function_ `void RegisterOnSynchronizeWithExternalDependencies(const FOnSynchronizeWithExternalDependencies& Delegate)`
- L715 _public function_ `void UnregisterOnSynchronizeWithExternalDependencies(FDelegateUserObject Unregister)`
- L716 _public function_ `void NotifySynchronizeWithExternalDependencies() const`
- L718 _public prototype_ `void SynchronizeWithExternalDependencies();`
- L719 _public prototype_ `void SynchronizeWithExternalDependencies(TConstArrayView<UAnimSequenceBase*> SequencesBase);`
- L723 _public prototype_ `void TestSynchronizeWithExternalDependencies();`
- L726 _public prototype_ `TConstArrayView<int32> GetAssetIndexesForSourceAsset(const UObject* SourceAsset) const;`
- L728 _public prototype_ `TConstArrayView<float> CalculateDynamicWeightsSqrt(TArrayView<float> DynamicWeightsSqrtBuffer) const;` — Experimental, this feature might be removed without warning, not for production use
- L731 _public prototype_ `static void AppendToClassSchema(FAppendToClassSchemaContext& Context);`
- L735 _private prototype_ `void SearchPCAKDTree(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;`
- L736 _private prototype_ `void SearchVPTree(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;`
- L737 _private prototype_ `void SearchBruteForce(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;`
- L738 _private prototype_ `void SearchEvent(UE::PoseSearch::FSearchContext& SearchContext, UE::PoseSearch::FSearchResults& SearchResults) const;`
- L740 _private typedef_ `typedef TArray<int32, TInlineAllocator<256, TMemStackAllocator<>>> FSelectableAssetIdx;`
- L742 _private prototype_ `void PopulateSelectableAssetIdx(FSelectableAssetIdx& SelectableAssetIdx, TConstArrayView<const UObject*> AssetsToConsider) const;` — `UE_DEPRECATED(5.7, "Use PopulateSelectableAssetIdx taking FStackAssetSet as input instead")`
- L743 _private prototype_ `void PopulateSelectableAssetIdx(FSelectableAssetIdx& SelectableAssetIdx, const UE::PoseSearch::FStackAssetSet* AssetsToConsider) const;`
- L744 _private prototype_ `void PopulateSelectableAssetIdx(FSelectableAssetIdx& SelectableAssetIdx, const UE::PoseSearch::FStackDatabaseToAssetIndexes* AssetIndexesToConsiderPerDatabase) const;`
- L746 _private typedef_ `typedef TArray<int32, TInlineAllocator<256, TMemStackAllocator<>>> FNonSelectableIdx;`
- L747 _private prototype_ `void PopulateNonSelectableIdx(FNonSelectableIdx& NonSelectableIdx, UE::PoseSearch::FSearchContext& SearchContext #if UE_POSE_SEARCH_TRACE_ENABLED , float ContinuingPoseCostAddend, float ContinuingInteractionCostAddend, float ContinuingContextInteractionCostAddend, TConstArrayView<float> DynamicWeightsSqrt #endif`
- L753 _private prototype_ `void UpdateCachedProperties();`
- L754 _private prototype_ `void ExtractCostAddends(const UE::PoseSearch::FSearchContext& SearchContext, bool bIsContinuingPoseSearch, float& ContinuingPoseCostAddend, float& ContinuingInteractionCostAddend, float& ContinuingContextInteractionCostAddend) const;`
- L758 _function_ `template<typename TDatabaseAnimationAsset> inline const TDatabaseAnimationAsset* UPoseSearchDatabase::GetDatabaseAnimationAsset(int32 AnimationAssetIndex) const`
- L771 _function_ `template<typename TDatabaseAnimationAsset> inline const TDatabaseAnimationAsset* UPoseSearchDatabase::GetDatabaseAnimationAsset(const UE::PoseSearch::FSearchIndexAsset& SearchIndexAsset) const`
- L779 _function_ `template<typename TDatabaseAnimationAsset> inline TDatabaseAnimationAsset* UPoseSearchDatabase::GetMutableDatabaseAnimationAsset(int32 AnimationAssetIndex)`
- L792 _function_ `template<typename TDatabaseAnimationAsset> inline TDatabaseAnimationAsset* UPoseSearchDatabase::GetMutableDatabaseAnimationAsset(const UE::PoseSearch::FSearchIndexAsset& SearchIndexAsset)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PoseSearch` (scope `UE`)
- L26 _prototype_ `FPoseSearchDatabaseAnimationAsset UpgradeToDatabaseAnimationAsset(FInstancedStruct& AnimationAsset);` (scope `UE::PoseSearch`) — `UE_DEPRECATED(5.7, "UpgradeToDatabaseAnimationAsset will be removed once all the classes inheriting from FPoseSearchDatabaseAnimationAssetBase are removed")`
- L120 _function_ `friend bool operator==(const FPoseSearchDatabaseAnimationAssetBase& A, const FPoseSearchDatabaseAnimationAssetBase& B)`
- L135 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70103`)
- L203 _function_ `friend bool operator==(const FPoseSearchDatabaseAnimationAsset& A, const FPoseSearchDatabaseAnimationAsset& B)`
- L222 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70203`)
- L253 _function_ `friend bool operator==(const FPoseSearchDatabaseSequence& A, const FPoseSearchDatabaseSequence& B)`
- L267 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70303`)
- L324 _function_ `friend bool operator==(const FPoseSearchDatabaseBlendSpace& A, const FPoseSearchDatabaseBlendSpace& B)`
- L344 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70403`)
- L375 _function_ `friend bool operator==(const FPoseSearchDatabaseAnimComposite& A, const FPoseSearchDatabaseAnimComposite& B)`
- L389 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70503`)
- L420 _function_ `friend bool operator==(const FPoseSearchDatabaseAnimMontage& A, const FPoseSearchDatabaseAnimMontage& B)`
- L434 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70603`)
- L480 _function_ `friend bool operator==(const FPoseSearchDatabaseMultiAnimAsset& A, const FPoseSearchDatabaseMultiAnimAsset& B)`
- L496 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon595be5a70703`)
- L627 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDerivedDataRebuildMulticaster);`
- L630 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSynchronizeWithExternalDependenciesMulticaster);`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchDefines.h` (Public)


#### class `UE::PoseSearch::TMemStackSetAllocator`  
`template<uint32 Alignment = DEFAULT_ALIGNMENT> class TMemStackSetAllocator : public TSetAllocator<TSparseArrayAllocator<TMemStackAllocator<Alignment>, TMemStackAllocator<Alignment>>, TMemStackAllocator<Alignment>>`  
_L49-49_
- inherits: `TSetAllocator<TSparseArrayAllocator<TMemStackAllocator<Alignment>,TMemStackAllocator<Alignment>>,TMemStackAllocator<Alignment>>`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_POSE_SEARCH_TRACE_ENABLED ANIM_TRACE_ENABLED`
- L16 _macro_ `#define UE_POSE_SEARCH_FORCE_SINGLE_THREAD 0`
- L20 _variable_ `constexpr EParallelForFlags ParallelForFlags = EParallelForFlags::ForceSingleThread;`
- L22 _variable_ `constexpr EParallelForFlags ParallelForFlags = EParallelForFlags::None;`
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPoseSearch, Log, All);`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace PoseSearch` (scope `UE`)
- L29 _variable_ `static constexpr int8 RootSchemaBoneIdx = 0;` (scope `UE::PoseSearch`)
- L30 _variable_ `static constexpr int8 TrajectorySchemaBoneIdx = -1;` (scope `UE::PoseSearch`)
- L31 _variable_ `static constexpr int8 InvalidSchemaBoneIdx = -2;` (scope `UE::PoseSearch`)
- L33 _variable_ `static constexpr int8 InvalidSchemaCurveIdx = -1;` (scope `UE::PoseSearch`)
- L35 _variable_ `static constexpr FBoneIndexType RootBoneIndexType = 0;` (scope `UE::PoseSearch`)
- L36 _variable_ `static constexpr FBoneIndexType ComponentSpaceIndexType = FBoneIndexType(-1);` (scope `UE::PoseSearch`)
- L37 _variable_ `static constexpr FBoneIndexType WorldSpaceIndexType = FBoneIndexType(-2);` (scope `UE::PoseSearch`)
- L39 _variable_ `static constexpr int32 PreallocatedRolesNum = 4;` (scope `UE::PoseSearch`)
- L40 _variable_ `static constexpr int32 PreallocatedCachedQueriesNum = 8;` (scope `UE::PoseSearch`)
- L41 _variable_ `static constexpr int32 PreallocatedCachedChannelDataNum = 64;` (scope `UE::PoseSearch`)
- L42 _variable_ `static constexpr int32 PreallocatedSearchesNum = 4;` (scope `UE::PoseSearch`)
- L43 _variable_ `static constexpr float FiniteDelta = 1 / 60.0f;` (scope `UE::PoseSearch`) — Time delta used for computing pose derivatives
- L44 _variable_ `static constexpr int32 MaxNumberOfCollectedPoseCandidatesPerDatabase = 256;` (scope `UE::PoseSearch`)
- L45 _variable_ `static constexpr int32 InvalidSearchId = INDEX_NONE;` (scope `UE::PoseSearch`) — @todo: it should be 0, since the search id is an hash!
- L46 _variable_ `static constexpr int32 DatabaseIndexDerivedDataCacheKeyVersion = 2737;` (scope `UE::PoseSearch`) — bump this value to force reindex ALL the UPoseSearchDatabases, without having to change the global FDevSystemGuids::POSESEARCHDB_DERIVEDDATA_VER
- L47 _variable_ `static constexpr int32 DefaultTickPriority = 100;` (scope `UE::PoseSearch`)
- L51 _function_ `constexpr int32 TMax(int32 A, int32 B)` (scope `UE::PoseSearch`)
- L52 _function_ `template<typename ElementType> constexpr int32 TAlignOf()` (scope `UE::PoseSearch`)
- L53 _typedef_ `template<typename ElementType> constexpr int32 TAlignOf() { return TMax(alignof(ElementType), 16); } template<typename ElementType> using TAlignedArray = TArray<ElementType, TAlignedHeapAllocator<TAlignOf<ElementType>()>>;` (scope `UE::PoseSearch`)
- L54 _typedef_ `template<typename ElementType> constexpr int32 TAlignOf() { return TMax(alignof(ElementType), 16); } template<typename ElementType> using TAlignedArray = TArray<ElementType, TAlignedHeapAllocator<TAlignOf<ElementType>()>>;` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchDerivedData.h` (Public)


#### enum `UE::PoseSearch::ERequestAsyncBuildFlag`  
`enum class ERequestAsyncBuildFlag`  
_L21-26_
- L23 _public enumerator_ `NewRequest = 1 << 0` — generates new key and kick off a task to get updated data (it'll cancel for eventual previous Database request, unless WaitPreviousRequest)
- L24 _public enumerator_ `ContinueRequest = 1 << 1` — make sure there's associated data to the Database (doesn't have to be up to date)
- L25 _public enumerator_ `WaitForCompletion = 1 << 2` — wait the termination of the NewRequest or ContinueRequest

#### enum `UE::PoseSearch::EAsyncBuildIndexResult`  
`enum class EAsyncBuildIndexResult`  
_L29-34_
- L31 _public enumerator_ `InProgress` — indexing in progress
- L32 _public enumerator_ `Success` — the index has been built and the Database updated correctly
- L33 _public enumerator_ `Failed` — indexing failed

#### class `UE::PoseSearch::FAsyncPoseSearchDatabasesManagement`  
`class FAsyncPoseSearchDatabasesManagement : public FTickableGameObject, public FTickableCookObject, public FGCObject`  
_L36-97_
- inherits: `FTickableGameObject,FTickableCookObject,FGCObject`
- L39 _public prototype_ `static EAsyncBuildIndexResult RequestAsyncBuildIndex(const UPoseSearchDatabase* Database, ERequestAsyncBuildFlag Flag);`
- L41 _public prototype_ `static void Clear();`
- L44 _private prototype_ `FAsyncPoseSearchDatabasesManagement();`
- L45 _private prototype_ `~FAsyncPoseSearchDatabasesManagement();`
- L47 _private prototype_ `static FAsyncPoseSearchDatabasesManagement& Get();`
- L48 _private prototype_ `static EAsyncBuildIndexResult RequestAsyncBuildIndexInternal(const UPoseSearchDatabase* Database, ERequestAsyncBuildFlag Flag);`
- L50 _private prototype_ `void OnObjectModified(UObject* Object);`
- L51 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);`
- L52 _private prototype_ `void OnPackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);`
- L53 _private prototype_ `void OnPreObjectPropertyChanged(UObject* InObject, const FEditPropertyChain& InPropertyChain);`
- L54 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L56 _private prototype_ `void Shutdown();`
- L57 _private prototype_ `void StartQueuedTasks(int32 MaxActiveTasks);`
- L58 _private prototype_ `void PreModified(UObject* Object, EObjectFlags ObjectFlagsToCheck);`
- L59 _private prototype_ `void PostModified(UObject* Object, EObjectFlags ObjectFlagsToCheck);`
- L62 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L63 _private function_ `virtual ETickableTickType GetTickableTickType() const override`
- L64 _private prototype_ `virtual TStatId GetStatId() const override;`
- L65 _private function_ `virtual bool IsTickableWhenPaused() const override`
- L66 _private function_ `virtual bool IsTickableInEditor() const override`
- L70 _private prototype_ `virtual void TickCook(float DeltaTime, bool bCookCompete) override;`
- L74 _private prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L75 _private function_ `virtual FString GetReferencerName() const override`
- L78 _private prototype_ `void CollectDatabasesToSynchronize(UObject* Object);`
- L79 _private prototype_ `void SynchronizeDatabases();`
- L82 _private typedef_ `typedef TMap<TWeakObjectPtr<UPoseSearchDatabase>, TArray<TWeakObjectPtr<UAnimSequenceBase>>> TDatabasesToSynchronize;` — map of all those databases UAnimSequenceBase(s) that were containing or are containing UAnimNotifyState_PoseSearchBranchIn that requires synchronization
- L83 _private typedef_ `typedef TPair<TWeakObjectPtr<UPoseSearchDatabase>, TArray<TWeakObjectPtr<UAnimSequenceBase>>> TDatabasesToSynchronizePair;`
- L84 _private member_ `TDatabasesToSynchronize DatabasesToSynchronize;`
- L86 _private member_ `FPoseSearchDatabaseAsyncCacheTasks& Tasks;`
- L87 _private member_ `FDelegateHandle OnObjectModifiedHandle;`
- L88 _private member_ `FDelegateHandle OnObjectTransactedHandle;`
- L89 _private member_ `FDelegateHandle OnPackageReloadedHandle;`
- L90 _private member_ `FDelegateHandle OnPreObjectPropertyChangedHandle;`
- L91 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;`
- L94 _private member_ `FPartialKeyHashes PartialKeyHashes;` — Experimental, this feature might be removed without warning, not for production use
- L96 _private member_ `static FCriticalSection Mutex;`

#### struct `UE::PoseSearch::FAsyncPoseSearchDatabasesManagementCache`  
`struct FAsyncPoseSearchDatabasesManagementCache`  
_L100-105_
- desc: Experimental, this feature might be removed without warning, not for production use
- L102 _public prototype_ `EAsyncBuildIndexResult operator()(const UPoseSearchDatabase* Database, ERequestAsyncBuildFlag RequestAsyncBuildFlag = ERequestAsyncBuildFlag::ContinueRequest);`
- L104 _private member_ `TMap<const UPoseSearchDatabase*, EAsyncBuildIndexResult, TInlineSetAllocator<32>> CachedRequests;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)
- L27 _prototype_ `ENUM_CLASS_FLAGS(ERequestAsyncBuildFlag);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchDerivedDataKey.h` (Public)


#### struct `UE::PoseSearch::FPartialKeyHashes`  
`struct FPartialKeyHashes`  
_L35-144_
- desc: Experimental, this feature might be removed without warning, not for production use FPartialKeyHashes contains the combined hash of all the properties, excluding the references to other UObject(s), for each UObject encountered during FKeyBuilder creation (serialization via FArchiveUObject)
- L65 _public typedef_ `typedef TPair<FObjectKey, FEntry> FPair;`
- L67 _public function_ `void Reset()`
- L72 _public function_ `void InvalidateKeysFor(UObject* Object)`
- L81 _public function_ `const FEntry* Add(FObjectKey& ObjectKey, const HashDigestType& Hash, TArrayView<UObject*> Dependencies)`
- L98 _public function_ `FEntry* FindAndRemoveResolved(FObjectKey& ObjectKey)`
- L124 _public function_ `const FEntry* Find(const FObjectKey& ObjectKey) const`
- L137 _public function_ `const FEntries& GetEntries() const`
- L143 _private member_ `FEntries Entries;`

#### struct `UE::PoseSearch::FPartialKeyHashes::FEntry`  
`struct FEntry`  
_L37-63_
- L39 _public member_ `HashDigestType Hash;`
- L40 _public member_ `TArray<FObjectKey> Dependencies;`
- L42 _public function_ `bool CheckDependencies(TArrayView<UObject*> OtherDependencies) const`

#### struct `UE::PoseSearch::FPartialKeyHashes::FEntries`  
`struct FEntries : public TMap<FObjectKey, FEntry>`  
_L129-135_
- inherits: `TMap<FObjectKey,FEntry>`
- L131 _public function_ `FPair* FindPair(const FObjectKey& ObjectKey)`

#### class `UE::PoseSearch::FKeyBuilder`  
`class FKeyBuilder : public FArchiveUObject`  
_L146-225_
- inherits: `FArchiveUObject`
- L149 _public member_ `inline static const FName ExcludeFromHashName = FName(TEXT("Excl`
- L150 _public member_ `inline static const FName NeverInHashName = FName(TEXT("Neve`
- L151 _public member_ `inline static const FName IgnoreForMemberInitializationTestName = FName(TEXT("Igno`
- L155 _public prototype_ `FKeyBuilder();`
- L158 _public prototype_ `FKeyBuilder(const UObject* Object, bool bUseDataVer, bool bPerformConditionalPostLoadIfRequired, FPartialKeyHashes* PartialKeyHashes = nullptr, bool bInPerformSequenceResidencyRequests = true);` — Experimental, this feature might be removed without warning, not for production use
- L161 _public prototype_ `bool ValidateAgainst(const FKeyBuilder& Other) const;` — Experimental, this feature might be removed without warning, not for production use
- L167 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L168 _public prototype_ `virtual bool ShouldSkipProperty(const FProperty* InProperty) const override;`
- L169 _public prototype_ `virtual void Serialize(void* Data, int64 Length) override;`
- L170 _public prototype_ `virtual FArchive& operator<<(FName& Name) override;`
- L171 _public prototype_ `virtual FArchive& operator<<(FText& Value) override;`
- L172 _public prototype_ `virtual FArchive& operator<<(class UObject*& Object) override;`
- L173 _public prototype_ `virtual FString GetArchiveName() const override;`
- L176 _public prototype_ `bool AnyAssetNotFullyLoaded() const;`
- L177 _public prototype_ `bool AnyAssetNotReady() const;`
- L178 _public prototype_ `FIoHash Finalize();`
- L179 _public prototype_ `const TSet<const UObject*>& GetDependencies() const;`
- L182 _public member_ `static constexpr EObjectFlags ShouldIncludeFlagsToCheckOnReload = RF_Transient | RF_MirroredGarbage | RF_BeginDestroyed | RF_FinishDestroyed | RF_DuplicateTransient | RF_NonPIEDuplicateTransient;` — Experimental, this feature might be removed without warning, not for production use
- L184 _public member_ `static constexpr EObjectFlags ShouldIncludeFlagsToCheck = ShouldIncludeFlagsToCheckOnReload | RF_NewerVersionExists;` — Experimental, this feature might be removed without warning, not for production use
- L186 _public prototype_ `static bool ShouldInclude(const UObject* Object, EObjectFlags ObjectFlagsToCheck);` — Experimental, this feature might be removed without warning, not for production use
- L190 _protected prototype_ `static bool IsExcludedType(const UObject* Object);` — to keep the key generation lightweight, we don't hash these types
- L193 _protected prototype_ `static bool IsAddNameOnlyType(const UObject* Object);` — to keep the key generation lightweight, we hash only the full names for these types. Object(s) will be added to Dependencies
- L195 _protected member_ `HashBuilderType Hasher;`
- L198 _protected member_ `UObject* KeyOwner = nullptr;` — UPoseSearchDatabase instance "owner" of the key generation
- L201 _protected member_ `TSet<const UObject*> Dependencies;` — Set of objects that have already been serialized
- L204 _protected member_ `bool bAnyAssetNotFullyLoaded = false;` — true if some dependent assets are not fully loaded
- L207 _protected member_ `bool bPerformConditionalPostLoad = false;` — if true ConditionalPostLoad will be performed on the dependant assets requiring it
- L210 _private member_ `bool bPerformSequenceResidencyRequests = false;`
- L212 _private prototype_ `void SerializeObjectInternal(UObject* Object);`
- L213 _private prototype_ `FArchive& TryAddDependency(UObject* Object);`
- L215 _private function_ `FPartialKeyHashes& GetPartialKeyHashes()`
- L216 _private prototype_ `FArchive& operator<<(FStringBuilderBase& StringBuilderBase);`
- L218 _private member_ `TArray<UObject*> ObjectsToSerialize;`
- L219 _private member_ `TArray<UObject*> ObjectBeingSerializedDependencies;`
- L221 _private member_ `FPartialKeyHashes* ExternalPartialKeyHashes = nullptr;`
- L222 _private member_ `FPartialKeyHashes InternalPartialKeyHashes;`
- L224 _private member_ `TStringBuilder<256> StringBuilder;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PoseSearch` (scope `UE`)
- L17 _typedef_ `using HashDigestType = FBlake3Hash;` (scope `UE::PoseSearch`)
- L18 _typedef_ `using HashBuilderType = FBlake3;` (scope `UE::PoseSearch`)
- L20 _function_ `static UObject* GetNonPackageOuter(UObject* Object)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchEvent.h` (Public)


#### struct `FPoseSearchEvent`  
`struct FPoseSearchEvent`  
_L12-44_
- reflection: `USTRUCT(Experimental, BlueprintType, Category="Animation|Pose Search|Experimental")`
- L16 _public prototype_ `bool IsValid() const;`
- L17 _public prototype_ `void Reset();`
- L18 _public prototype_ `UE_INTERNAL FPoseSearchEvent GetPlayRateOverriddenEvent(const FFloatInterval& PlayRateRangeBase) const;`
- L22 _public member_ `FGameplayTag EventTag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Tag identifying this event
- L26 _public member_ `float TimeToEvent = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Time in seconds until this event occurs
- L31 _public member_ `bool bEnablePoseFilters = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — if true pose candidates will be filtered by MotionMatching node 'PoseJumpThresholdTime' (DiscardedBy_PoseJumpThresholdTime) and 'PoseReselectHistory' (DiscardedBy_PoseReselectHistory), as well as database assets FPoseSearchDatabaseAnimationAssetBase::bDisableReselection (DiscardedBy_AssetReselection)
- L36 _public member_ `bool bUsePlayRateRangeOverride = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — @todo: add PlayRate / PlayRateRangeOverride concept to UPoseSearchLibrary::MotionMatch if true PlayRateRangeOverride will be used instead of FAnimNode_MotionMatching::PlayRate
- L43 _public member_ `FFloatInterval PlayRateRangeOverride = FFloatInterval(1.f, 1.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State, meta = (ClampMin = "0.2", ClampMax = "3.0", UIMin = "0.2", UIMax = "3.0"))` — @todo: support the concept of time to event channel weight, as wey of scoring better poses that are closer to the TimeToEvent Effective range of play rate that can be applied to the selected animation to play, to account for better pose and trajectory matches. that means the event search will evaluate poses in the range [TimeToEvent * PlayRate.Min, TimeToEvent * PlayRate.Max] seconds from any poses tagged with EventTag PlayRateRangeOverride will be used if bUsePlayRateRangeOverride is true, otherwise FAnimNode_MotionMatching::PlayRate will be used instead

#### class `UPoseSearchEventLibrary`  
`class UPoseSearchEventLibrary : public UBlueprintFunctionLibrary`  
_L47-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L52 _private prototype_ `static void UpdatePoseSearchEvent(const FPoseSearchEvent& InNewEvent, bool bIsNewEventValid, float DeltaSeconds, UPARAM(ref) FPoseSearchEvent& InOutCurrentEvent);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe), Category="Animation|Pose Search|Experimental")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel.h` (Public)


#### enum `EInputQueryPose`  
`enum class EInputQueryPose : uint8`  
_L18-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `UseCharacterPose` — Use character pose to compose the query.
- L24 _public enumerator_ `UseContinuingPose` — If available reuse continuing pose from the database to compose the query, or else UseCharacterPose.

#### enum `EPermutationTimeType`  
`enum class EPermutationTimeType : uint8`  
_L31-44_
- reflection: `UENUM()`
- desc: this enumeration controls the channel sampling time: for example if a channel specifies a bone and an origin bone (used to generate the reference system of the features associated to the bone), bone and origin bone will be evaluated at potentially different times:
- L35 _public enumerator_ `UseSampleTime` — Bone and origin bone are sampled at the same sample time (plus eventual SampleTimeOffset for the bone): it's defined as the current animation evaluation time.
- L40 _public enumerator_ `UsePermutationTime` — Bone and origin bone are sampled at the same permutation time (plus eventual SampleTimeOffset for the bone): it's defined as SamplingTime (as UseSampleTime) + Schema->PermutationsTimeOffset + PermutationIndex / Schema->PermutationsSampleRate where PermutationIndex is in range [0, Schema->NumberOfPermutations).
- L43 _public enumerator_ `UseSampleToPermutationTime` — Bone is evaluated at sample time (and plus eventual SampleTimeOffset) and origin bone is evaluated at permutation time.

#### enum `UE::PoseSearch::ELabelFormat`  
`enum class ELabelFormat : uint8`  
_L56-66_
- L59 _public enumerator_ `Full_Horizontal` — output label example: "Traj_Vel_xy 1.20"
- L62 _public enumerator_ `Full_Vertical` — output label example: "Traj\nVel_xy\n1.20"
- L65 _public enumerator_ `Compact_Horizontal` — output label example: "Vel_xy 1.20"

#### class `UPoseSearchFeatureChannel`  
`class UPoseSearchFeatureChannel : public UObject, public IBoneReferenceSkeletonProvider, public IPoseSearchFilter`  
_L78-159_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, EditInlineNew)`
- inherits: `UObject,IBoneReferenceSkeletonProvider,IPoseSearchFilter`
- desc: Feature channels interface
- L84 _public function_ `int32 GetChannelCardinality() const`
- L85 _public function_ `int32 GetChannelDataOffset() const`
- L88 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) PURE_VIRTUAL(UPoseSearchFeatureChannel::Finalize, return false;);` — Called during UPoseSearchSchema::Finalize to prepare the schema for this channel
- L91 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const PURE_VIRTUAL(UPoseSearchFeatureChannel::BuildQuery, );` — Called at runtime to add this channel's data to the query pose vector
- L94 _public function_ `virtual TArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels()` — UPoseSearchFeatureChannels can hold sub channels
- L95 _public function_ `virtual TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() const`
- L97 _public function_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const`
- L99 _public function_ `int32 GetNumFilters() const`
- L100 _public function_ `const FPoseSearchFilter* GetFilter(int32 FilterIndex) const`
- L102 _public function_ `virtual EPermutationTimeType GetPermutationTimeType() const`
- L103 _public prototype_ `static void GetPermutationTimeOffsets(EPermutationTimeType PermutationTimeType, float DesiredPermutationTimeOffset, float& OutPermutationSampleTimeOffset, float& OutPermutationOriginTimeOffset);`
- L107 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const;` — Draw this channel's data for the given pose vector
- L114 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const PURE_VIRTUAL(UPoseSearchFeatureChannel::FillWeights, );` — Called at database build time to collect feature weights. Weights is sized to the cardinality of the schema and the feature channel should write its weights at the channel's data offset. Channels should provide a weight for each dimension.
- L117 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const PURE_VIRTUAL(UPoseSearchFeatureChannel::IndexAsset, return false;);` — Called at database build time to populate pose vectors with this channel's data
- L120 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const;` — returns the TLabelBuilder used editor side to identify this UPoseSearchFeatureChannel (for instance in the pose search debugger)
- L123 _public prototype_ `virtual bool CanBeNormalizedWith(const UPoseSearchFeatureChannel* Other) const;` — returns true if the data associated to this channel can be normalized toghether with the associated with Other
- L129 _public function_ `virtual FName GetNormalizationGroup() const` — if this channel GetNormalizationGroup returns a valid FName, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will make CanBeNormalizedWith return true and will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity, so you'd want those channels returning the same GetNormalizationGroup value
- L131 _public prototype_ `const UPoseSearchSchema* GetSchema() const;`
- L133 _public prototype_ `virtual const UE::PoseSearch::FRole GetDefaultRole() const;`
- L137 _public function_ `virtual FLinearColor GetDebugColor() const`
- L142 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider interface Note this function is exclusively for FBoneReference details customization
- L146 _protected prototype_ `void GetOuterLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat) const;`
- L147 _protected prototype_ `static void AppendLabelSeparator(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat, bool bTryUsingSpace = false);`
- L152 _protected member_ `int32 ChannelDataOffset = INDEX_NONE;` — `UPROPERTY(Transient)`
- L155 _protected member_ `int32 ChannelCardinality = INDEX_NONE;` — `UPROPERTY(Transient)`
- L158 _protected member_ `TArray<FInstancedStruct> Filters;` — `UPROPERTY(EditAnywhere, Category = "Filters", meta = (ExcludeBaseStruct, BaseStruct = "/Script/PoseSearch.PoseSearchFilter"))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API POSESEARCH_API`
- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace PoseSearch` (scope `UE`)
- L68 _typedef_ `typedef TStringBuilder<256> TLabelBuilder;` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Curve.h` (Public)


#### class `UPoseSearchFeatureChannel_Curve`  
`class UPoseSearchFeatureChannel_Curve : public UPoseSearchFeatureChannel`  
_L11-77_
- reflection: `UCLASS(MinimalAPI, Experimental, BlueprintType, EditInlineNew, Blueprintable, meta = (DisplayName = "Curve Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L18 _public member_ `FName CurveName = NAME_None;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")`
- L21 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L24 _public member_ `int8 CurveIdx = UE::PoseSearch::InvalidSchemaCurveIdx;` — `UPROPERTY(Transient)`
- L28 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L34 _public member_ `float SampleTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel will be offset by SampleTimeOffset seconds. For example, if Curve is DistanceToWall, and SampleTimeOffset is 0.5, this channel will try to match the future DistanceToWall curve of the character 0.5 seconds ahead
- L38 _public member_ `FLinearColor DebugColor = FLinearColor::Green;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L42 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L49 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and Curve
- L54 _public prototype_ `float BP_GetCurveValue(const UAnimInstance* AnimInstance) const;` — `UE_DEPRECATED(5.8, "Use BP_GetCurveValueFromContext instead")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Curve"), Category = "Settings")`
- L57 _public prototype_ `float BP_GetCurveValueFromContext(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Curve From Context"), Category = "Settings")`
- L59 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L61 _public prototype_ `UPoseSearchFeatureChannel_Curve();`
- L64 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L65 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L68 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L69 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L70 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L71 _public function_ `virtual FName GetNormalizationGroup() const override`
- L75 _public function_ `virtual FLinearColor GetDebugColor() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Distance.h` (Public)


#### class `UPoseSearchFeatureChannel_Distance`  
`class UPoseSearchFeatureChannel_Distance : public UPoseSearchFeatureChannel`  
_L13-128_
- reflection: `UCLASS(MinimalAPI, Experimental, EditInlineNew, Blueprintable, meta = (DisplayName = "Distance Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L22 _public member_ `bool bDefaultWithRootBone = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Experimental, this feature might be removed without warning, not for production use if bDefaultWithRootBone is true Bone.BoneName and OriginBone.BoneName get initialized to the associated skeleton root bone if equals to NAME_None, otherwise transforms from the trajectory will be used
- L25 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L28 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L31 _public member_ `FBoneReference OriginBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L34 _public member_ `FName OriginRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L41 _public member_ `float MaxDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Filter")` — Experimental, this feature might be removed without warning, not for production use During pose selection if the distance between query versus candidate poses for this distance channel is greater than MaxDistance the candidate will be discarded. the filtering will be enabled only for MaxDistance > 0
- L45 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L52 _public member_ `int32 SamplingAttributeId = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if SamplingAttributeId >= 0, ALL the animations contained in the pose search database referencing the schema containing this channel are expected to have UAnimNotifyState_PoseSearchSamplingAttribute notify state with a matching SamplingAttributeId, and the UAnimNotifyState_PoseSearchSamplingAttribute properties will be used as source of data instead of this channel "Bone". UAnimNotifyState_PoseSearchSamplingAttribute properties will be then converted into OriginBone space
- L57 _public member_ `float SampleTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel will be offsetted by SampleTimeOffset seconds. For example, if Bone is the head bone, and SampleTimeOffset is 0.5, this channel will try to match the future distance of the character head bone 0.5 seconds ahead
- L63 _public member_ `float OriginTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel origin (root / trajectory bone) will be offsetted by OriginTimeOffset seconds. For example, if Bone is the head bone, SampleTimeOffset is 0.5, and OriginTimeOffset is 0.5, this channel will try to match the future distance of the character head bone 0.5 seconds ahead, relative to the future root bone 0.5 seconds ahead
- L67 _public member_ `int8 SchemaBoneIdx = 0;` — `UPROPERTY(Transient)` — index referencing the associated bone in UPoseSearchSchema::BoneReferences
- L70 _public member_ `int8 SchemaOriginBoneIdx = 0;` — `UPROPERTY(Transient)`
- L74 _public member_ `FLinearColor DebugColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L78 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L81 _public member_ `EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L88 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together all the distances
- L92 _public prototype_ `float BP_GetDistance(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get Distance"), Category = "Settings")`
- L94 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L96 _public prototype_ `UPoseSearchFeatureChannel_Distance();`
- L99 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L100 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L102 _public function_ `virtual EPermutationTimeType GetPermutationTimeType() const override`
- L103 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L107 _public function_ `virtual bool IsFilterActive() const override` — IPoseSearchFilter interface Experimental, this feature might be removed without warning, not for production use
- L109 _public prototype_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata) const override;` — Experimental, this feature might be removed without warning, not for production use
- L112 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L116 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L117 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L118 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L119 _public function_ `virtual FName GetNormalizationGroup() const override`
- L122 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider interface
- L126 _public function_ `virtual FLinearColor GetDebugColor() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_FilterCrashingLegs.h` (Public)


#### class `UPoseSearchFeatureChannel_FilterCrashingLegs`  
`class UPoseSearchFeatureChannel_FilterCrashingLegs : public UPoseSearchFeatureChannel`  
_L19-81_
- reflection: `UCLASS(MinimalAPI, Experimental, BlueprintType, EditInlineNew, meta = (DisplayName = "CrashingLegs Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- desc: the idea is to calculate the angle between the direction from LeftThigh position to RightThigh position and the direction from LeftFoot position to RightFoot position, and divide it by PI to have values in range [-1,1] the number (called 'CrashingLegsValue' calculated in ComputeCrashingLegsValue) is gonna be 0 if the feet are aligned with the thighs (for example in an idle standing position) 0.5 if the right foot is exactly in front of the left foot (for example when a character is running  following a line) -0.5 if the left foot is exactly in front of the right foot close to 1 or -1 if the feet (and so the legs) are completely crossed at runtime we'll match the CrashingLegsValue and also filter by discarding pose candidates that don't respect the 'AllowedTolerance' between query and database values (happening in IsFilterValid)
- L25 _public member_ `FBoneReference LeftThigh;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L28 _public member_ `FBoneReference RightThigh;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L31 _public member_ `FBoneReference LeftFoot;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L34 _public member_ `FBoneReference RightFoot;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L37 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L40 _public member_ `float Weight = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L43 _public member_ `int8 LeftThighIdx;` — `UPROPERTY()`
- L46 _public member_ `int8 RightThighIdx;` — `UPROPERTY()`
- L49 _public member_ `int8 LeftFootIdx;` — `UPROPERTY()`
- L52 _public member_ `int8 RightFootIdx;` — `UPROPERTY()`
- L55 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L59 _public member_ `float AllowedTolerance = 0.3f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))` — if AllowedTolerance is zero the filter is disabled
- L62 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L63 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L65 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L68 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L72 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L73 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L74 _public function_ `virtual const UE::PoseSearch::FRole GetDefaultRole() const override`
- L79 _public prototype_ `virtual bool IsFilterActive() const override;` — @todo: reimplement this using the new FPoseSearchFilter IPoseSearchFilter interface
- L80 _public prototype_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Group.h` (Public)


#### class `UPoseSearchFeatureChannel_GroupBase`  
`class UPoseSearchFeatureChannel_GroupBase : public UPoseSearchFeatureChannel`  
_L13-45_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, EditInlineNew)`
- inherits: `UPoseSearchFeatureChannel`
- desc: Feature channels interface
- L19 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L25 _public member_ `int32 DebugWeightGroupID = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Experimental, this feature might be removed without warning, not for production use identifier / metadata to categorize this group base channel weights to be able to zero them via UPoseSearchDatabase::CalculateDynamicWeightsSqrt
- L28 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L29 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L30 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L33 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L37 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L38 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L39 _public function_ `virtual const UE::PoseSearch::FRole GetDefaultRole() const override`
- L43 _public prototype_ `virtual bool IsFilterActive() const override;` — IPoseSearchFilter interface
- L44 _public prototype_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata) const override;`

#### class `UPoseSearchFeatureChannel_Group`  
`class UPoseSearchFeatureChannel_Group : public UPoseSearchFeatureChannel_GroupBase`  
_L48-62_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, meta = (DisplayName = "Group Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel_GroupBase`
- L52 _private function_ `virtual TArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() override`
- L53 _private function_ `virtual TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() const override`
- L56 _private prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L61 _public member_ `TArray<TObjectPtr<UPoseSearchFeatureChannel>> SubChannels;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "SubChannels")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Heading.h` (Public)


#### enum `EHeadingAxis`  
`enum class EHeadingAxis : uint8`  
_L12-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `X`
- L15 _public enumerator_ `Y`
- L16 _public enumerator_ `Z`
- L18 _public enumerator_ `Num UMETA(Hidden)`

#### class `UPoseSearchFeatureChannel_Heading`  
`class UPoseSearchFeatureChannel_Heading : public UPoseSearchFeatureChannel`  
_L22-137_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Blueprintable, meta = (DisplayName = "Heading Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L31 _public member_ `bool bDefaultWithRootBone = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Experimental, this feature might be removed without warning, not for production use if bDefaultWithRootBone is true Bone.BoneName and OriginBone.BoneName get initialized to the associated skeleton root bone if equals to NAME_None, otherwise transforms from the trajectory will be used
- L34 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L37 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L40 _public member_ `FBoneReference OriginBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L43 _public member_ `FName OriginRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L47 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L54 _public member_ `int32 SamplingAttributeId = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if SamplingAttributeId >= 0, ALL the animations contained in the pose search database referencing the schema containing this channel are expected to have UAnimNotifyState_PoseSearchSamplingAttribute notify state with a matching SamplingAttributeId, and the UAnimNotifyState_PoseSearchSamplingAttribute properties will be used as source of data instead of this channel "Bone". UAnimNotifyState_PoseSearchSamplingAttribute properties will be then converted into OriginBone space
- L59 _public member_ `float SampleTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel will be offsetted by SampleTimeOffset seconds. For example, if Bone is the head bone, and SampleTimeOffset is 0.5, this channel will try to match the future heading of the character head bone 0.5 seconds ahead
- L65 _public member_ `float OriginTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel origin (root / trajectory bone) will be offsetted by OriginTimeOffset seconds. For example, if Bone is the head bone, SampleTimeOffset is 0.5, and OriginTimeOffset is 0.5, this channel will try to match the future heading of the character head bone 0.5 seconds ahead, relative to the future root bone 0.5 seconds ahead
- L68 _public member_ `EHeadingAxis HeadingAxis = EHeadingAxis::X;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L72 _public member_ `int8 SchemaBoneIdx = 0;` — `UPROPERTY(Transient)` — index referencing the associated bone in UPoseSearchSchema::BoneReferences
- L75 _public member_ `int8 SchemaOriginBoneIdx = 0;` — `UPROPERTY(Transient)`
- L79 _public member_ `FLinearColor DebugColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L83 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L86 _public member_ `EComponentStrippingVector ComponentStripping = EComponentStrippingVector::None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L89 _public member_ `EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L96 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L101 _public prototype_ `FQuat BP_GetWorldRotation(const UAnimInstance* AnimInstance) const;` — `UE_DEPRECATED(5.8, "Use BP_GetWorldRotationFromContext instead")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Rotation"), Category = "Settings")`
- L104 _public prototype_ `FQuat BP_GetWorldRotationFromContext(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Rotation From Context"), Category = "Settings")`
- L106 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L108 _public prototype_ `UPoseSearchFeatureChannel_Heading();`
- L111 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L112 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L114 _public function_ `virtual EPermutationTimeType GetPermutationTimeType() const override`
- L115 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L118 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L122 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L123 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L124 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L125 _public function_ `virtual FName GetNormalizationGroup() const override`
- L128 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider interface
- L132 _public function_ `virtual FLinearColor GetDebugColor() const override`
- L135 _public prototype_ `FVector GetAxis(const FQuat& Rotation) const;`
- L136 _public prototype_ `static void FindOrAddToSchema(UPoseSearchSchema* Schema, float SampleTimeOffset, const FName& BoneName, const UE::PoseSearch::FRole& Role, EHeadingAxis HeadingAxis = EHeadingAxis::X, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, bool bDefaultWithRootBone = true);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Padding.h` (Public)


#### class `UPoseSearchFeatureChannel_Padding`  
`class UPoseSearchFeatureChannel_Padding : public UPoseSearchFeatureChannel`  
_L11-30_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, meta = (DisplayName = "Padding Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L17 _public member_ `int32 PaddingSize = 1;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L20 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L21 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L24 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L25 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L26 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L29 _public prototype_ `static void AddToSchema(UPoseSearchSchema* Schema, int32 PaddingSize);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_PermutationTime.h` (Public)


#### class `UPoseSearchFeatureChannel_PermutationTime`  
`class UPoseSearchFeatureChannel_PermutationTime : public UPoseSearchFeatureChannel`  
_L11-34_
- reflection: `UCLASS(MinimalAPI, Experimental, EditInlineNew, meta = (DisplayName = "Permutation Time Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L18 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L22 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L23 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L26 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L27 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L28 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L31 _public prototype_ `float GetPermutationTime(TConstArrayView<float> PoseVector) const;`
- L33 _public prototype_ `static void FindOrAddToSchema(UPoseSearchSchema* Schema);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Phase.h` (Public)


#### class `UPoseSearchFeatureChannel_Phase`  
`class UPoseSearchFeatureChannel_Phase : public UPoseSearchFeatureChannel`  
_L12-69_
- reflection: `UCLASS(MinimalAPI, Experimental, BlueprintType, EditInlineNew, meta = (DisplayName = "Phase Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L18 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L21 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L25 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L30 _public member_ `int8 SchemaBoneIdx = 0;` — `UPROPERTY(Transient)` — index referencing the associated bone in UPoseSearchSchema::BoneReferences
- L34 _public member_ `FLinearColor DebugColor = FLinearColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L38 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L45 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L49 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L50 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L52 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L55 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L59 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L60 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L61 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L62 _public function_ `virtual FName GetNormalizationGroup() const override`
- L63 _public function_ `virtual const UE::PoseSearch::FRole GetDefaultRole() const override`
- L67 _public function_ `virtual FLinearColor GetDebugColor() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Pose.h` (Public)


#### enum `EPoseSearchBoneFlags`  
`enum class EPoseSearchBoneFlags : uint32`  
_L11-17_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L13 _public enumerator_ `Velocity = 1 << 0`
- L14 _public enumerator_ `Position = 1 << 1`
- L15 _public enumerator_ `Rotation = 1 << 2`
- L16 _public enumerator_ `Phase = 1 << 3`

#### struct `FPoseSearchBone`  
`struct FPoseSearchBone`  
_L23-47_
- reflection: `USTRUCT()`
- L28 _public member_ `FBoneReference Reference;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L32 _public member_ `int32 Flags = int32(EPoseSearchBoneFlags::Position);` — `UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "/Script/PoseSearch.EPoseSearchBoneFlags"), Category = Config)` — This allows the user to define what information from the channel you want to compare to.
- L39 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L42 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L45 _public member_ `FLinearColor DebugColor = FLinearColor::Green;` — `UPROPERTY(EditAnywhere, Category = Config, meta=(ExcludeFromHash, DisplayPriority = 0))`

#### class `UPoseSearchFeatureChannel_Pose`  
`class UPoseSearchFeatureChannel_Pose : public UPoseSearchFeatureChannel_GroupBase`  
_L51-93_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, meta = (DisplayName = "Pose Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel_GroupBase`
- desc: UPoseSearchFeatureChannel_Pose
- L58 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L63 _public member_ `TArray<FPoseSearchBone> SampledBones;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — List of skeletal joints and associated Flags (Velocity, Position, etc) to sample.
- L66 _public member_ `TArray<int8> SchemaBoneIdx;` — `UPROPERTY()`
- L69 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L73 _public member_ `bool bUseCharacterSpaceVelocities = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if bUseCharacterSpaceVelocities is true, velocities will be calculated from the positions in character space, otherwise they will be calculated using global space positions
- L76 _public member_ `EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L79 _public member_ `TArray<TObjectPtr<UPoseSearchFeatureChannel>> SubChannels;` — `UPROPERTY(Transient)`
- L81 _public prototype_ `UPoseSearchFeatureChannel_Pose();`
- L84 _public function_ `virtual TArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() override` — UPoseSearchFeatureChannel_GroupBase interface
- L85 _public function_ `virtual TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() const override`
- L88 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L91 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`
- L18 _prototype_ `ENUM_CLASS_FLAGS(EPoseSearchBoneFlags);`
- L19 _function_ `constexpr bool EnumHasAnyFlags(int32 Flags, EPoseSearchBoneFlags Contains)`
- L20 _function_ `inline int32& operator|=(int32& Lhs, EPoseSearchBoneFlags Rhs)`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Position.h` (Public)


#### class `UPoseSearchFeatureChannel_Position`  
`class UPoseSearchFeatureChannel_Position : public UPoseSearchFeatureChannel`  
_L12-131_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Blueprintable, meta = (DisplayName = "Position Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L21 _public member_ `bool bDefaultWithRootBone = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Experimental, this feature might be removed without warning, not for production use if bDefaultWithRootBone is true Bone.BoneName and OriginBone.BoneName get initialized to the associated skeleton root bone if equals to NAME_None, otherwise transforms from the trajectory will be used
- L24 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L27 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L30 _public member_ `FBoneReference OriginBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L33 _public member_ `FName OriginRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L37 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L44 _public member_ `int32 SamplingAttributeId = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if SamplingAttributeId >= 0, ALL the animations contained in the pose search database referencing the schema containing this channel are expected to have UAnimNotifyState_PoseSearchSamplingAttribute notify state with a matching SamplingAttributeId, and the UAnimNotifyState_PoseSearchSamplingAttribute properties will be used as source of data instead of this channel "Bone". UAnimNotifyState_PoseSearchSamplingAttribute properties will be then converted into OriginBone space
- L49 _public member_ `float SampleTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel will be offsetted by SampleTimeOffset seconds. For example, if Bone is the head bone, and SampleTimeOffset is 0.5, this channel will try to match the future position of the character head bone 0.5 seconds ahead
- L55 _public member_ `float OriginTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel origin (root / trajectory bone) will be offsetted by OriginTimeOffset seconds. For example, if Bone is the head bone, SampleTimeOffset is 0.5, and OriginTimeOffset is 0.5, this channel will try to match the future position of the character head bone 0.5 seconds ahead, relative to the future root bone 0.5 seconds ahead
- L59 _public member_ `int8 SchemaBoneIdx = 0;` — `UPROPERTY(Transient)` — index referencing the associated bone in UPoseSearchSchema::BoneReferences
- L62 _public member_ `int8 SchemaOriginBoneIdx = 0;` — `UPROPERTY(Transient)`
- L66 _public member_ `FLinearColor DebugColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L70 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L73 _public member_ `EComponentStrippingVector ComponentStripping = EComponentStrippingVector::None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L76 _public member_ `EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L84 _public member_ `bool bNormalizeDisplacement = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Settings")` — Experimental, this feature might be removed without warning, not for production use UPoseSearchFeatureChannel_Position represents / calculates the position (displacement) of Bone relative to OriginBone if bNormalizeDisplacement is true, the displacement will be normalized. if zero it'll stay zero, so it'll be like matching the direction towards the position is pointing at. useful to match "trajectory points" when the velocity is not consistent between query and database poses. Look at the debug lines to have an idea what it'd match
- L91 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L96 _public prototype_ `FVector BP_GetWorldPosition(const UAnimInstance* AnimInstance) const;` — `UE_DEPRECATED(5.8, "Use BP_GetWorldPositionFromContext instead")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Position"), Category = "Settings")`
- L99 _public prototype_ `FVector BP_GetWorldPositionFromContext(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Position From Context"), Category = "Settings")`
- L101 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L103 _public prototype_ `UPoseSearchFeatureChannel_Position();`
- L106 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L107 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L109 _public function_ `virtual EPermutationTimeType GetPermutationTimeType() const override`
- L110 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L113 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L117 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L118 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L119 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L120 _public function_ `virtual FName GetNormalizationGroup() const override`
- L123 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider interface
- L127 _public function_ `virtual FLinearColor GetDebugColor() const override`
- L130 _public prototype_ `static void FindOrAddToSchema(UPoseSearchSchema* Schema, float SampleTimeOffset, const FName& BoneName, const UE::PoseSearch::FRole& Role, EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime, bool bDefaultWithRootBone = true);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_SamplingTime.h` (Public)


#### class `UPoseSearchFeatureChannel_SamplingTime`  
`class UPoseSearchFeatureChannel_SamplingTime : public UPoseSearchFeatureChannel`  
_L12-32_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, meta = (DisplayName = "Sampling Time Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- desc: this channel is mainly for debug purposes to augment the features data with the sampling time (default weight is set to zero to be irrelevant during searches)
- L18 _public member_ `float Weight = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L21 _public member_ `float TimeToMatch = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L24 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L25 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L28 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L29 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L30 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_TimeToEvent.h` (Public)


#### class `UPoseSearchFeatureChannel_TimeToEvent`  
`class UPoseSearchFeatureChannel_TimeToEvent : public UPoseSearchFeatureChannel`  
_L11-42_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Blueprintable, meta = (DisplayName = "Time To Event Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L17 _public member_ `float Weight = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L20 _public member_ `int32 SamplingAttributeId = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L24 _public prototype_ `float BP_GetTimeToEvent(const UAnimInstance* AnimInstance) const;` — `UE_DEPRECATED(5.8, "Use BP_GetTimeToEventFromContext instead")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get Time To Event"), Category = "Settings")`
- L27 _public prototype_ `float BP_GetTimeToEventFromContext(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(BlueprintThreadSafe, DisplayName = "Get Time To Event From Context"), Category = "Settings")`
- L29 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L31 _public prototype_ `UPoseSearchFeatureChannel_TimeToEvent();`
- L34 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L35 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L38 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L39 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L40 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Trajectory.h` (Public)


#### enum `EPoseSearchTrajectoryFlags`  
`enum class EPoseSearchTrajectoryFlags : uint32`  
_L12-22_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L14 _public enumerator_ `Velocity = 1 << 0`
- L15 _public enumerator_ `Position = 1 << 1`
- L16 _public enumerator_ `VelocityDirection = 1 << 2`
- L17 _public enumerator_ `FacingDirection = 1 << 3`
- L18 _public enumerator_ `VelocityXY = 1 << 4`
- L19 _public enumerator_ `PositionXY = 1 << 5`
- L20 _public enumerator_ `VelocityDirectionXY = 1 << 6`
- L21 _public enumerator_ `FacingDirectionXY = 1 << 7`

#### struct `FPoseSearchTrajectorySample`  
`struct FPoseSearchTrajectorySample`  
_L28-54_
- reflection: `USTRUCT()`
- L35 _public member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = Config)` — the data relative to the sampling time associated to this FPoseSearchTrajectorySample will be offsetted by Offset seconds. For example, Flags is Position, and Offset is 0.5, this channel will try to match the future position of the trajectory 0.5 seconds ahead
- L39 _public member_ `int32 Flags = int32(EPoseSearchTrajectoryFlags::Position);` — `UPROPERTY(EditAnywhere, meta = (Bitmask, BitmaskEnum = "/Script/PoseSearch.EPoseSearchTrajectoryFlags"), Category = Config)` — This allows the user to define what information from the channel you want to compare to.
- L43 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L49 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = Config)` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L52 _public member_ `FLinearColor DebugColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = Config, meta = (ExcludeFromHash, DisplayPriority = 0))`

#### class `UPoseSearchFeatureChannel_Trajectory`  
`class UPoseSearchFeatureChannel_Trajectory : public UPoseSearchFeatureChannel_GroupBase`  
_L57-92_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, meta = (DisplayName = "Trajectory Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel_GroupBase`
- L64 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L68 _public member_ `TArray<FPoseSearchTrajectorySample> Samples;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L71 _public member_ `TArray<TObjectPtr<UPoseSearchFeatureChannel>> SubChannels;` — `UPROPERTY(Transient)`
- L73 _public prototype_ `UPoseSearchFeatureChannel_Trajectory();`
- L76 _public function_ `virtual TArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() override` — UPoseSearchFeatureChannel_GroupBase interface
- L77 _public function_ `virtual TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetSubChannels() const override`
- L80 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L83 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L87 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L90 _public prototype_ `float GetEstimatedSpeedRatio(TConstArrayView<float> QueryVector, TConstArrayView<float> PoseVector) const;`
- L91 _public prototype_ `FVector GetEstimatedFutureRootMotionVelocity(TConstArrayView<float> PoseVector) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`
- L23 _prototype_ `ENUM_CLASS_FLAGS(EPoseSearchTrajectoryFlags);`
- L24 _function_ `constexpr bool EnumHasAnyFlags(int32 Flags, EPoseSearchTrajectoryFlags Contains)`
- L25 _function_ `inline int32& operator|=(int32& Lhs, EPoseSearchTrajectoryFlags Rhs)`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureChannel_Velocity.h` (Public)


#### class `UPoseSearchFeatureChannel_Velocity`  
`class UPoseSearchFeatureChannel_Velocity : public UPoseSearchFeatureChannel`  
_L12-129_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Blueprintable, meta = (DisplayName = "Velocity Channel"), CollapseCategories)`
- inherits: `UPoseSearchFeatureChannel`
- L21 _public member_ `bool bDefaultWithRootBone = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Experimental, this feature might be removed without warning, not for production use if bDefaultWithRootBone is true Bone.BoneName and OriginBone.BoneName get initialized to the associated skeleton root bone if equals to NAME_None, otherwise transforms from the trajectory will be used
- L24 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L27 _public member_ `FName SampleRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L30 _public member_ `FBoneReference OriginBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L33 _public member_ `FName OriginRole = UE::PoseSearch::DefaultRole;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L37 _public member_ `float Weight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L44 _public member_ `int32 SamplingAttributeId = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if SamplingAttributeId >= 0, ALL the animations contained in the pose search database referencing the schema containing this channel are expected to have UAnimNotifyState_PoseSearchSamplingAttribute notify state with a matching SamplingAttributeId, and the UAnimNotifyState_PoseSearchSamplingAttribute properties will be used as source of data instead of this channel "Bone". UAnimNotifyState_PoseSearchSamplingAttribute properties will be then converted into OriginBone space
- L49 _public member_ `float SampleTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel will be offsetted by SampleTimeOffset seconds. For example, if Bone is the head bone, and SampleTimeOffset is 0.5, this channel will try to match the future velocity of the character head bone 0.5 seconds ahead
- L55 _public member_ `float OriginTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — the data relative to the sampling time associated to this channel origin (root / trajectory bone) will be offsetted by OriginTimeOffset seconds. For example, if Bone is the head bone, SampleTimeOffset is 0.5, and OriginTimeOffset is 0.5, this channel will try to match the future velocity of the character head bone 0.5 seconds ahead, relative to the future root bone 0.5 seconds ahead
- L59 _public member_ `int8 SchemaBoneIdx = 0;` — `UPROPERTY(Transient)` — index referencing the associated bone in UPoseSearchSchema::BoneReferences
- L62 _public member_ `int8 SchemaOriginBoneIdx = 0;` — `UPROPERTY(Transient)`
- L66 _public member_ `FLinearColor DebugColor = FLinearColor::Green;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ExcludeFromHash, DisplayPriority = 0))`
- L70 _public member_ `EInputQueryPose InputQueryPose = EInputQueryPose::UseContinuingPose;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L74 _public member_ `bool bUseCharacterSpaceVelocities = true;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if bUseCharacterSpaceVelocities is true, velocities will be calculated from the positions in character space, otherwise they will be calculated using global space positions
- L78 _public member_ `bool bNormalize = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if bNormalize is true, velocity will be clamped to a maximum size of one (UPoseSearchFeatureChannel_Velocity will be matching the "direction" of the velocity)
- L81 _public member_ `EComponentStrippingVector ComponentStripping = EComponentStrippingVector::None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L84 _public member_ `EPermutationTimeType PermutationTimeType = EPermutationTimeType::UseSampleTime;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L91 _public member_ `FName NormalizationGroup;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — if set, all the channels of the same class with the same cardinality, and the same NormalizationGroup, will be normalized together. for example in a locomotion database of a character holding a weapon, containing non mirrorable animations, you'd still want to normalize together left foot and right foot position and velocity
- L96 _public prototype_ `FVector BP_GetWorldVelocity(const UAnimInstance* AnimInstance) const;` — `UE_DEPRECATED(5.8, "Use BP_GetWorldVelocityFromContext instead")` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Velocity"), Category = "Settings")`
- L99 _public prototype_ `FVector BP_GetWorldVelocityFromContext(UPARAM(Ref) FChooserEvaluationContext& Context) const;` — `UFUNCTION(BlueprintPure, BlueprintNativeEvent, meta=(BlueprintThreadSafe, DisplayName = "Get World Velocity From Context"), Category = "Settings")`
- L101 _public member_ `bool bUseBlueprintQueryOverride = false;`
- L103 _public prototype_ `UPoseSearchFeatureChannel_Velocity();`
- L106 _public prototype_ `virtual bool Finalize(UPoseSearchSchema* Schema) override;` — UPoseSearchFeatureChannel interface
- L107 _public prototype_ `virtual void BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L109 _public function_ `virtual EPermutationTimeType GetPermutationTimeType() const override`
- L110 _public prototype_ `virtual void AddDependentChannels(UPoseSearchSchema* Schema) const override;`
- L113 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector) const override;`
- L117 _public prototype_ `virtual void FillWeights(TArrayView<float> Weights) const override;`
- L118 _public prototype_ `virtual bool IndexAsset(UE::PoseSearch::FAssetIndexer& Indexer) const override;`
- L119 _public prototype_ `virtual UE::PoseSearch::TLabelBuilder& GetLabel(UE::PoseSearch::TLabelBuilder& LabelBuilder, UE::PoseSearch::ELabelFormat LabelFormat = UE::PoseSearch::ELabelFormat::Full_Horizontal) const override;`
- L120 _public function_ `virtual FName GetNormalizationGroup() const override`
- L123 _public prototype_ `USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider interface
- L127 _public function_ `virtual FLinearColor GetDebugColor() const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFeatureVectorHelper.h` (Public)


#### enum `EComponentStrippingVector`  
`enum class EComponentStrippingVector : uint8`  
_L10-20_
- reflection: `UENUM()`
- L13 _public enumerator_ `None` — No component stripping.
- L16 _public enumerator_ `StripXY` — Stripping X and Y components (matching only on the horizontal plane).
- L19 _public enumerator_ `StripZ` — Stripping Z (matching only vertically - caring only about the height of the feature).

#### class `UE::PoseSearch::FFeatureVectorHelper`  
`class FFeatureVectorHelper`  
_L26-40_
- desc: Helper class for extracting and encoding features into a float buffer
- L29 _public prototype_ `static int32 GetVectorCardinality(EComponentStrippingVector ComponentStrippingVector);`
- L30 _public prototype_ `static void EncodeVector(TArrayView<float> Values, int32 DataOffset, const FVector& Vector, EComponentStrippingVector ComponentStrippingVector, bool bNormalize);`
- L31 _public prototype_ `static FVector DecodeVector(TConstArrayView<float> Values, int32 DataOffset, EComponentStrippingVector ComponentStrippingVector);`
- L33 _public prototype_ `static void EncodeVector2D(TArrayView<float> Values, int32 DataOffset, const FVector2D& Vector2D);`
- L34 _public prototype_ `static FVector2D DecodeVector2D(TConstArrayView<float> Values, int32 DataOffset);`
- L36 _public prototype_ `static void EncodeFloat(TArrayView<float> Values, int32 DataOffset, const float Value);`
- L37 _public prototype_ `static float DecodeFloat(TConstArrayView<float> Values, int32 DataOffset);`
- L39 _public prototype_ `static void Copy(TArrayView<float> Values, int32 DataOffset, int32 DataCardinality, TConstArrayView<float> OriginValues);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API POSESEARCH_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchFilter.h` (Public)


#### class `IPoseSearchFilter`  
`class UE_DEPRECATED(5.8, "Use FPoseSearchFilter instead") IPoseSearchFilter`  
_L23-35_
- L26 _public function_ `virtual ~IPoseSearchFilter()`
- L30 _public function_ `virtual bool IsFilterActive() const` — `UE_DEPRECATED(5.8, "Use FPoseSearchFilter::GetRequiredDataSize instead")` — if true this filter will be evaluated
- L34 _public function_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata) const` — `UE_DEPRECATED(5.8, "Use FPoseSearchFilter::IsFilterValid instead")` — if it returns false the pose candidate will be discarded

#### struct `FPoseSearchFilter`  
`struct FPoseSearchFilter`  
_L38-65_
- reflection: `USTRUCT(Experimental)`
- L45 _public function_ `virtual ~FPoseSearchFilter()`
- L48 _public function_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const` — returns require data size in bytes for this filter. InvalidFilterDataSize if the filter is NOT active
- L53 _public function_ `virtual bool InitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, TConstArrayView<float> QueryValues, UE::PoseSearch::FSearchContext& SearchContext) const` — called to initialize Data with this FPoseSearchFilter data  only if GetRequiredDataSize returns >= 0. Data.Num() == GetRequiredDataSize() returns successful it returns true, or else DeinitializeData will be called right away and IsFilterValid will NOT be called it is safe to use Data to perform a new inplace in InitializeData and call the destructor in DeinitializeData.. but not recommended
- L57 _public function_ `virtual void DeinitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, UE::PoseSearch::FSearchContext& SearchContext) const` — called to deinitialize Data with this FPoseSearchFilter data  only if GetRequiredDataSize returns >= 0. Data.Num() == GetRequiredDataSize() it is safe to use Data to perform a new inplace in InitializeData and call the destructor in DeinitializeData.. but not recommended
- L60 _public function_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const` — called for EVERY evaluated pose (be sure it's as fast as possible). if it returns false the pose candidate will be discarded
- L63 _public function_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseVector, const UPoseSearchFeatureChannel* Channel) const`

#### enum `FPoseSearchFilter::(anonymous)`  
`enum`  
_L42-42_

#### enum `FPoseSearchFilter::(anonymous)`  
`enum`  
_L43-43_

#### struct `FPoseSearchFilterPadding`  
`struct FPoseSearchFilterPadding : public FPoseSearchFilter`  
_L69-74_
- reflection: `USTRUCT(MinimalAPI, Experimental)`
- inherits: `FPoseSearchFilter`
- desc: debug FPoseSearchFilter to test InitializeData / DeinitializeData by padding the data by 1 byte
- L73 _public prototype_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override;`

#### struct `FPoseSearchFilterMaxPosition`  
`struct FPoseSearchFilterMaxPosition : public FPoseSearchFilter`  
_L78-103_
- reflection: `USTRUCT(MinimalAPI, Experimental)`
- inherits: `FPoseSearchFilter`
- desc: FPoseSearchFilterMaxPosition is invalid if the query for the associated UPoseSearchFeatureChannel_Position is too far from the candidate pose
- L82 _public prototype_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override;`
- L83 _public prototype_ `virtual bool InitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, TConstArrayView<float> QueryValues, UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L84 _public prototype_ `virtual void DeinitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L85 _public prototype_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const override;`
- L88 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseValues, const UPoseSearchFeatureChannel* Channel) const override;`
- L95 _public member_ `float MaxPositionDistanceSquared = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Filter", meta = (ClampMin = "0", UIMin = "0"))` — During pose selection if the squared distance between query versus candidate poses for the associated UPoseSearchFeatureChannel_Position is greater than MaxPositionDistanceSquared the candidate will be discarded. The filtering will be enabled only for MaxPositionDistanceSquared != 0

#### struct `FPoseSearchFilterMaxPosition::FData`  
`struct FData`  
_L98-101_
- L100 _public member_ `FVector Query;`

#### struct `FPoseSearchFilterWedge`  
`struct FPoseSearchFilterWedge : public FPoseSearchFilter`  
_L107-136_
- reflection: `USTRUCT(MinimalAPI, Experimental)`
- inherits: `FPoseSearchFilter`
- desc: FPoseSearchFilterWedge is invalid if the query for the associated UPoseSearchFeatureChannel_Position doesn't land in the defined wedge relative to the trajectory
- L111 _public prototype_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override;`
- L112 _public prototype_ `virtual bool InitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, TConstArrayView<float> QueryValues, UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L113 _public prototype_ `virtual void DeinitializeData(TArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel, UE::PoseSearch::FSearchContext& SearchContext) const override;`
- L114 _public prototype_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const override;`
- L117 _public prototype_ `virtual void DebugDraw(const UE::PoseSearch::FDebugDrawParams& DrawParams, TConstArrayView<float> PoseValues, const UPoseSearchFeatureChannel* Channel) const override;`
- L121 _public member_ `FFloatInterval RadiusOffsets = FFloatInterval(-100.f, 100.f);` — `UPROPERTY(EditAnywhere, Category = "Experimental|Filter", meta = (ClampToMinMaxLimits))`
- L125 _public member_ `float WedgeWidthInDegrees = 70.f;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Filter", meta = (ClampMin = "0"))` — wedge filter width in degrees

#### struct `FPoseSearchFilterWedge::FData`  
`struct FData`  
_L128-134_
- L130 _public member_ `FVector NormalizedQuery;`
- L131 _public member_ `float InnerRadius;`
- L132 _public member_ `float OuterRadius;`
- L133 _public member_ `float DotWedgeWidth;`

#### struct `UE::PoseSearch::FSelectableAssetIdxFilter`  
`struct FSelectableAssetIdxFilter : public FPoseSearchFilter`  
_L141-161_
- inherits: `FPoseSearchFilter`
- desc: Experimental, this feature might be removed without warning, not for production use
- L143 _public function_ `const FSelectableAssetIdxFilter& Init(TConstArrayView<int32> InSelectableAssetIdxFilter)`
- L150 _public function_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override`
- L155 _public function_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const override`
- L160 _public member_ `TConstArrayView<int32> SelectableAssetIdxFilter;`

#### struct `UE::PoseSearch::FNonSelectableIdxFilter`  
`struct FNonSelectableIdxFilter : public FPoseSearchFilter`  
_L164-183_
- inherits: `FPoseSearchFilter`
- desc: Experimental, this feature might be removed without warning, not for production use
- L166 _public function_ `const FNonSelectableIdxFilter& Init(TConstArrayView<int32> InNonSelectableIdx)`
- L173 _public function_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override`
- L177 _public function_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const override`
- L182 _public member_ `TConstArrayView<int32> NonSelectableIdx;`

#### struct `UE::PoseSearch::FBlockTransitionFilter`  
`struct FBlockTransitionFilter : public FPoseSearchFilter`  
_L186-197_
- inherits: `FPoseSearchFilter`
- desc: Experimental, this feature might be removed without warning, not for production use
- L188 _public function_ `virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const override`
- L193 _public function_ `virtual bool IsFilterValid(TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, int32 PoseIdx, const UE::PoseSearch::FPoseMetadata& Metadata, TConstArrayView<uint8> Data, const UPoseSearchFeatureChannel* Channel) const override`

#### struct `UE::PoseSearch::FSearchFilters`  
`struct FSearchFilters`  
_L200-241_
- desc: Experimental, this feature might be removed without warning, not for production use
- L202 _public prototype_ `FSearchFilters(const UPoseSearchSchema* Schema, TConstArrayView<int32> NonSelectableIdx, TConstArrayView<int32> SelectableAssetIdx, bool bAddBlockTransitionFilter, TConstArrayView<float> QueryValues, FSearchContext& InSearchContext);`
- L204 _public prototype_ `~FSearchFilters();`
- L207 _public prototype_ `bool AreFiltersValid(const FSearchIndex& SearchIndex, TConstArrayView<float> PoseValues, TConstArrayView<float> QueryValues, TConstArrayView<float> DynamicWeightsSqrt, int32 PoseIdx #if UE_POSE_SEARCH_TRACE_ENABLED , float ContinuingPoseCostAddend, float ContinuingInteractionCostAddend, float ContinuingContextInteractionCostAddend, const UPoseSearchDatabase* Database #endif` — @todo: template this with bAlignedAndPadded to be able to use faster ComparePoses
- L213 _public function_ `FSearchContext& GetSearchContext() const`
- L217 _private member_ `FSearchContext& SearchContext;`
- L218 _private member_ `FNonSelectableIdxFilter NonSelectableIdxFilter;`
- L219 _private member_ `FSelectableAssetIdxFilter SelectableAssetIdxFilter;`
- L220 _private member_ `FBlockTransitionFilter BlockTransitionFilter;`
- L223 _private member_ `TArray<const IPoseSearchFilter*, TInlineAllocator<64, TMemStackAllocator<>>> Filters_DEPRECATED;`
- L239 _private member_ `TArray<FFilterContext, TInlineAllocator<64, TMemStackAllocator<>>> FilterContexts;`
- L240 _private member_ `TArray<uint8, TMemStackAllocator<FPoseSearchFilter::DataAlignment>> FiltersData;`

#### struct `UE::PoseSearch::FSearchFilters::FFilterContext`  
`struct FFilterContext`  
_L226-238_
- L228 _public function_ `FFilterContext(const FPoseSearchFilter* InFilter, const UPoseSearchFeatureChannel* InChannel, TArrayView<uint8> InData) : Filter(InFilter) , Channel(InChannel) , Data(InData)`
- L235 _public member_ `const FPoseSearchFilter* Filter;`
- L236 _public member_ `const UPoseSearchFeatureChannel* Channel;`
- L237 _public member_ `TArrayView<uint8> Data;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace PoseSearch` (scope `UE`)
- L42 _enumerator_ `enum { InvalidFilterDataSize = -1 }; enum { DataAlignment = 16 }; virtual ~FPoseSearchFilter() {} virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const { return InvalidFilterDataSize; }` (scope `FPoseSearchFilter::__anon7e8fd7f80103`)
- L43 _enumerator_ `enum { DataAlignment = 16 }; virtual ~FPoseSearchFilter() {} virtual int32 GetRequiredDataSize(const UPoseSearchFeatureChannel* Channel) const { return InvalidFilterDataSize; }` (scope `FPoseSearchFilter::__anon7e8fd7f80203`)
- L138 _namespace_ `namespace UE`
- L138 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchHistory.h` (Public)


#### struct `UE::PoseSearch::FHistoricalPoseIndex`  
`struct FHistoricalPoseIndex`  
_L34-48_
- L36 _public function_ `bool operator==(const FHistoricalPoseIndex& Index) const`
- L46 _public member_ `int32 PoseIndex = INDEX_NONE;`
- L47 _public member_ `FObjectKey DatabaseKey;`

#### struct `UE::PoseSearch::FPoseIndicesHistory`  
`struct FPoseIndicesHistory`  
_L50-57_
- L52 _public prototype_ `UE_INTERNAL void Update(const FSearchResult& SearchResult, float DeltaTime, float MaxTime);`
- L53 _public function_ `void Reset()`
- L54 _public prototype_ `bool operator==(const FPoseIndicesHistory& Other) const;`
- L56 _public member_ `TMap<FHistoricalPoseIndex, float> IndexToTime;`

#### struct `UE::PoseSearch::IComponentSpacePoseProvider`  
`struct IComponentSpacePoseProvider`  
_L59-64_
- L61 _public prototype_ `virtual ~IComponentSpacePoseProvider() = default;`
- L62 _public prototype_ `virtual FTransform CalculateComponentSpaceTransform(const FSkeletonPoseBoneIndex SkeletonBoneIdx) = 0;`
- L63 _public prototype_ `virtual const USkeleton* GetSkeletonAsset() const = 0;`

#### struct `UE::PoseSearch::FComponentSpacePoseProvider`  
`struct FComponentSpacePoseProvider : public IComponentSpacePoseProvider`  
_L66-75_
- inherits: `IComponentSpacePoseProvider`
- L68 _public prototype_ `FComponentSpacePoseProvider(FCSPose<FCompactPose>& InComponentSpacePose);`
- L70 _public prototype_ `virtual FTransform CalculateComponentSpaceTransform(const FSkeletonPoseBoneIndex SkeletonBoneIdx) override;`
- L71 _public prototype_ `virtual const USkeleton* GetSkeletonAsset() const override;`
- L74 _private member_ `FCSPose<FCompactPose>& ComponentSpacePose;`

#### struct `UE::PoseSearch::FAIPComponentSpacePoseProvider`  
`struct FAIPComponentSpacePoseProvider : public IComponentSpacePoseProvider`  
_L77-86_
- inherits: `IComponentSpacePoseProvider`
- L79 _public prototype_ `FAIPComponentSpacePoseProvider(const FAnimInstanceProxy* InAnimInstanceProxy);`
- L81 _public prototype_ `virtual FTransform CalculateComponentSpaceTransform(const FSkeletonPoseBoneIndex SkeletonBoneIdx) override;`
- L82 _public prototype_ `virtual const USkeleton* GetSkeletonAsset() const override;`
- L85 _private member_ `FCSPose<FCompactPose> ComponentSpacePose;`

#### struct `UE::PoseSearch::FSKMCComponentSpacePoseProvider`  
`struct UE_EXPERIMENTAL(5.8, "This API is experimental and might be removed without warning, not for production use.") FSKMCComponentSpacePoseProvider : public IComponentSpacePoseProvider`  
_L89-100_
- inherits: `IComponentSpacePoseProvider`
- desc: Experimental, this feature might be removed without warning, not for production use
- L91 _public prototype_ `FSKMCComponentSpacePoseProvider(const USkeletalMeshComponent* InSkeletalMeshComponent);`
- L93 _public prototype_ `virtual FTransform CalculateComponentSpaceTransform(const FSkeletonPoseBoneIndex SkeletonBoneIdx) override;`
- L94 _public prototype_ `virtual const USkeleton* GetSkeletonAsset() const override;`
- L97 _private member_ `USkeleton* Skeleton = nullptr;`
- L98 _private member_ `const TArray<int32>* SkeletonToMeshTable = nullptr;`
- L99 _private member_ `const USkeletalMeshComponent* SkeletalMeshComponent = nullptr;`

#### struct `UE::PoseSearch::FPoseHistoryEntry`  
`struct FPoseHistoryEntry`  
_L102-127_
- L105 _public member_ `TArray<FQuat4f> ComponentSpaceRotations;` — collected bones transforms in component space
- L106 _public member_ `TArray<FVector> ComponentSpacePositions;`
- L107 _public member_ `TArray<FVector3f> ComponentSpaceScales;`
- L108 _public member_ `TArray<float> CurveValues;`
- L109 _public member_ `float AccumulatedSeconds = 0.f;`
- L112 _public member_ `FTransform DebugMeshTransform;`
- L115 _public prototype_ `void Update(float Time, IComponentSpacePoseProvider& ComponentSpacePoseProvider, const FBoneToTransformMap& BoneToTransformMap, bool bStoreScales, const FBlendedCurve& Curves, const TConstArrayView<FName>& CollectedCurves #if WITH_EDITORONLY_DATA , const FTransform& InDebugMeshTransform = FTransform::Identity #endif`
- L121 _public prototype_ `void SetNum(int32 Num, bool bStoreScales);`
- L122 _public prototype_ `int32 Num() const;`
- L124 _public prototype_ `void SetComponentSpaceTransform(int32 Index, const FTransform& Transform);`
- L125 _public prototype_ `FTransform GetComponentSpaceTransform(int32 Index) const;`
- L126 _public prototype_ `float GetCurveValue(int32 Index) const;`

#### struct `FPoseSearchHistory`  
`struct FPoseSearchHistory`  
_L134-208_
- reflection: `USTRUCT(Experimental, BlueprintType)`
- desc: Experimental, this feature might be removed without warning, not for production use
- L138 _public prototype_ `void Initialize(int32 InNumPoses, float InSamplingInterval);`
- L139 _public prototype_ `void EvaluateComponentSpace(float DeltaTime, UE::PoseSearch::IComponentSpacePoseProvider& ComponentSpacePoseProvider, bool bStoreScales, float RootBoneRecoveryTime, float RootBoneTranslationRecoveryRatio, float RootBoneRotationRecoveryRatio, bool bNeedsReset, bool bCacheBones, const TArray<FBoneIndexType>& RequiredBones, const FBlendedCurve& Curves = FBlendedCurve(), const TConstArrayView<FName>& InCollectedCurves = TConstArrayView<FName>() #if WITH_EDITORONLY_DATA , const FTransform& InDebugMeshTransform = FTransform::Identity #endif`
- L148 _public prototype_ `bool GetTransformAtTime(float Time, FTransform& OutBoneTransform, const USkeleton* BoneIndexSkeleton = nullptr, FBoneIndexType BoneIndexType = UE::PoseSearch::RootBoneIndexType, FBoneIndexType ReferenceBoneIndexType = UE::PoseSearch::ComponentSpaceIndexType, bool bExtrapolate = false) const;`
- L149 _public prototype_ `bool GetCurveValueAtTime(float Time, const FName& CurveName, float& outcurvevalue, bool bExtrapolate = false) const;`
- L150 _public prototype_ `void SetTrajectory(const FTransformTrajectory& InTrajectory, float InTrajectorySpeedMultiplier = 1.f);`
- L151 _public prototype_ `void GenerateTrajectory(const UObject* AnimContext, float DeltaTime);`
- L152 _public function_ `float GetTrajectorySpeedMultiplier() const`
- L153 _public function_ `bool IsEmpty() const`
- L154 _public function_ `const UE::PoseSearch::FBoneToTransformMap& GetBoneToTransformMap() const`
- L155 _public function_ `const TConstArrayView<FName> GetCollectedCurves() const`
- L157 _public function_ `int32 GetNumEntries() const`
- L158 _public function_ `const UE::PoseSearch::FPoseHistoryEntry& GetEntry(int32 EntryIndex) const`
- L159 _public function_ `const UE::PoseSearch::FPoseIndicesHistory* GetPoseIndicesHistory() const`
- L161 _public function_ `int32 GetMaxNumPoses() const`
- L162 _public function_ `float GetSamplingInterval() const`
- L165 _public function_ `void SetSamplingInterval(float InSamplingInterval)` — Experimental, this feature might be removed without warning, not for production use
- L167 _public function_ `const FTransformTrajectory& GetTrajectory() const`
- L168 _public function_ `FTransformTrajectory& EditTrajectory()`
- L172 _private member_ `FTransformTrajectory Trajectory;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess=true))`
- L176 _private member_ `int32 MaxNumPoses = 2;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess=true))` — max number of stored poses in this pose history
- L180 _private member_ `float SamplingInterval = -1.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess=true))` — frequency of sampling of poses in this pose history. negative numbers will store a new pose on every update
- L183 _private member_ `float TrajectorySpeedMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess=true))`
- L186 _private member_ `TWeakObjectPtr<const USkeleton> LastUpdateSkeleton;` — skeleton from the last Update, to keep tracking skeleton changes, and support compatible skeletons
- L193 _private member_ `UE::PoseSearch::FBoneToTransformMap BoneToTransformMap;` — @todo: make it a UPROPERTY typedef TMap<FBoneIndexType, FComponentSpaceTransformIndex> FBoneToTransformMap;
- L196 _private member_ `TArray<FName> CollectedCurves;` — list of curves that we want to collect into our history.
- L199 _private member_ `uint32 BoneToTransformMapTypeHash = 0;` — GetTypeHash for BoneToTransformMap
- L203 _private member_ `TRingBuffer<UE::PoseSearch::FPoseHistoryEntry> Entries;` — @todo: make it a UPROPERTY ring buffer of collected bones
- L207 _private member_ `UE::PoseSearch::FPoseIndicesHistory PoseIndicesHistory;` — @todo: make it a UPROPERTY data structure containing the previously played pose indexes with their respective datababases

#### struct `UE::PoseSearch::IPoseHistory`  
`struct IPoseHistory : public TSharedFromThis<IPoseHistory, ESPMode::ThreadSafe>`  
_L213-249_
- inherits: `TSharedFromThis<IPoseHistory,ESPMode::ThreadSafe>`
- L215 _public prototype_ `virtual ~IPoseHistory() = default;`
- L221 _public prototype_ `virtual bool GetTransformAtTime(float Time, FTransform& OutBoneTransform, const USkeleton* BoneIndexSkeleton = nullptr, FBoneIndexType BoneIndexType = RootBoneIndexType, FBoneIndexType ReferenceBoneIndexType = ComponentSpaceIndexType, bool bExtrapolate = false) const = 0;` — returns transform of the the skeleton bone index BoneIndexType (encoded as FBoneIndexType) relative to the transform of ReferenceBoneIndexType: if ReferenceBoneIndexType is 0 (RootBoneIndexType), OutBoneTransform is in root bone space if ReferenceBoneIndexType is FBoneIndexType(-1) (ComponentSpaceIndexType), OutBoneTransform is in component space if ReferenceBoneIndexType is FBoneIndexType(-2) (WorldSpaceIndexType), OutBoneTransform is in world space
- L223 _public prototype_ `virtual bool GetCurveValueAtTime(float Time, const FName& CurveName, float& OutCurveValue, bool bExtrapolate = false) const = 0;` — @todo: consider consolidating into a (templated?) get X value at time once we add custom attributes to pose history.
- L228 _public prototype_ `virtual const FTransformTrajectory& GetTrajectory() const = 0;` — @note for review: Here we are just changing the return type to force users to update immediately. Will cause project to not compile for users who override the pure virtual func getter, not sure how we can gracefully deprecate this. Another option is to just have a new function signature GetTransformTrajectory() and add a final tag to the GetTrajectory() to also force users to upgrade. Lastly, to me this seems like a struct not many licensees would inherent from tbh.
- L231 _public prototype_ `virtual void SetTrajectory(const FTransformTrajectory& InTrajectory, float InTrajectorySpeedMultiplier = 1.f) = 0;` — Experimental, this feature might be removed without warning, not for production use
- L233 _public prototype_ `virtual void GenerateTrajectory(const UObject* AnimContext, float DeltaTime) = 0;` — Experimental, this feature might be removed without warning, not for production use
- L235 _public prototype_ `virtual float GetTrajectorySpeedMultiplier() const = 0;` — @todo: deprecate this API. TrajectorySpeedMultiplier should be a global query scaling value passed as input parameter of FSearchContext during config BuildQuery
- L236 _public prototype_ `virtual bool IsEmpty() const = 0;`
- L238 _public prototype_ `virtual const FBoneToTransformMap& GetBoneToTransformMap() const = 0;`
- L239 _public prototype_ `virtual const TConstArrayView<FName> GetCollectedCurves() const = 0;`
- L240 _public prototype_ `virtual int32 GetNumEntries() const = 0;`
- L241 _public prototype_ `virtual const FPoseHistoryEntry& GetEntry(int32 EntryIndex) const = 0;`
- L242 _public function_ `virtual const FPoseIndicesHistory* GetPoseIndicesHistory() const`
- L245 _public prototype_ `virtual void DebugDraw(const UWorld* World, FColor Color) const = 0;`
- L246 _public prototype_ `virtual void DebugDraw(FAnimInstanceProxy& AnimInstanceProxy, FColor Color) const = 0;`
- L247 _public prototype_ `virtual void DebugDraw(FAnimInstanceProxy& AnimInstanceProxy, FColor Color, float Time, float PointSize = 6.f, bool bExtrapolate = false) const;`

#### struct `UE::PoseSearch::FArchivedPoseHistory`  
`struct FArchivedPoseHistory : public IPoseHistory`  
_L251-282_
- inherits: `IPoseHistory`
- L253 _public prototype_ `void InitFrom(const IPoseHistory* PoseHistory);`
- L256 _public prototype_ `virtual bool GetTransformAtTime(float Time, FTransform& OutBoneTransform, const USkeleton* BoneIndexSkeleton = nullptr, FBoneIndexType BoneIndexType = RootBoneIndexType, FBoneIndexType ReferenceBoneIndexType = ComponentSpaceIndexType, bool bExtrapolate = false) const override;` — IPoseHistory interface
- L257 _public prototype_ `virtual bool GetCurveValueAtTime(float Time, const FName& CurveName, float& outcurvevalue, bool bExtrapolate = false) const override;`
- L258 _public function_ `virtual const FTransformTrajectory& GetTrajectory() const override`
- L260 _public function_ `virtual void SetTrajectory(const FTransformTrajectory& InTrajectory, float InTrajectorySpeedMultiplier = 1.f) override` — Experimental, this feature might be removed without warning, not for production use
- L262 _public function_ `virtual void GenerateTrajectory(const UObject* AnimContext, float DeltaTime) override` — Experimental, this feature might be removed without warning, not for production use
- L263 _public function_ `virtual float GetTrajectorySpeedMultiplier() const override`
- L264 _public function_ `virtual bool IsEmpty() const override`
- L265 _public function_ `virtual const FBoneToTransformMap& GetBoneToTransformMap() const override`
- L266 _public function_ `virtual const TConstArrayView<FName> GetCollectedCurves() const override`
- L267 _public function_ `virtual int32 GetNumEntries() const override`
- L268 _public function_ `virtual const FPoseHistoryEntry& GetEntry(int32 EntryIndex) const override`
- L271 _public prototype_ `virtual void DebugDraw(const UWorld* World, FColor Color) const override;`
- L272 _public function_ `virtual void DebugDraw(FAnimInstanceProxy& AnimInstanceProxy, FColor Color) const override`
- L276 _public member_ `FBoneToTransformMap BoneToTransformMap;`
- L278 _public member_ `TArray<FName> CollectedCurves;` — @todo: Make this a map if this is expected to be big.
- L279 _public member_ `TArray<FPoseHistoryEntry> Entries;`
- L281 _public member_ `FTransformTrajectory Trajectory;`

#### struct `UE::PoseSearch::FPoseHistory`  
`struct FPoseHistory : public IPoseHistory`  
_L285-346_
- inherits: `IPoseHistory`
- L287 _public prototype_ `FPoseHistory() = default;`
- L288 _public prototype_ `virtual ~FPoseHistory() override = default;`
- L290 _public prototype_ `FPoseHistory(const FPoseHistory& Other);`
- L291 _public prototype_ `FPoseHistory(FPoseHistory&& Other);`
- L292 _public prototype_ `FPoseHistory& operator=(const FPoseHistory& Other);`
- L293 _public prototype_ `FPoseHistory& operator=(FPoseHistory&& Other);`
- L296 _public prototype_ `void GenerateTrajectory(const UObject* AnimContext, float DeltaTime, const FPoseSearchTrajectoryData& TrajectoryData, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling);` — @todo: deprecate and delete this method in favor of providing the trajectory via SetTrajectory
- L298 _public prototype_ `void Initialize_AnyThread(int32 InNumPoses, float InSamplingInterval);`
- L299 _public prototype_ `void EvaluateComponentSpace_AnyThread(float DeltaTime, IComponentSpacePoseProvider& ComponentSpacePoseProvider, bool bStoreScales, float RootBoneRecoveryTime, float RootBoneTranslationRecoveryRatio, float RootBoneRotationRecoveryRatio, bool bNeedsReset, bool bCacheBones, const TArray<FBoneIndexType>& RequiredBones, const FBlendedCurve& Curves = FBlendedCurve(), const TConstArrayView<FName>& InCollectedCurves = TConstArrayView<FName>() #if WITH_EDITORONLY_DATA , const FTransform& InDebugMeshTransform = FTransform::Identity #endif`
- L309 _public prototype_ `virtual bool GetTransformAtTime(float Time, FTransform& OutBoneTransform, const USkeleton* BoneIndexSkeleton = nullptr, FBoneIndexType BoneIndexType = RootBoneIndexType, FBoneIndexType ReferenceBoneIndexType = ComponentSpaceIndexType, bool bExtrapolate = false) const override;` — IPoseHistory interface
- L310 _public prototype_ `virtual bool GetCurveValueAtTime(float Time, const FName& CurveName, float& outcurvevalue, bool bExtrapolate = false) const override;`
- L311 _public prototype_ `virtual const FTransformTrajectory& GetTrajectory() const override;`
- L313 _public prototype_ `virtual void SetTrajectory(const FTransformTrajectory& InTrajectory, float InTrajectorySpeedMultiplier = 1.f) override;` — Experimental, this feature might be removed without warning, not for production use
- L315 _public prototype_ `virtual void GenerateTrajectory(const UObject* AnimContext, float DeltaTime) override;` — Experimental, this feature might be removed without warning, not for production use
- L316 _public prototype_ `virtual float GetTrajectorySpeedMultiplier() const override;`
- L317 _public prototype_ `virtual bool IsEmpty() const override;`
- L318 _public prototype_ `virtual const FBoneToTransformMap& GetBoneToTransformMap() const override;`
- L319 _public prototype_ `virtual const TConstArrayView<FName> GetCollectedCurves() const override;`
- L321 _public prototype_ `virtual int32 GetNumEntries() const override;`
- L322 _public prototype_ `virtual const FPoseHistoryEntry& GetEntry(int32 EntryIndex) const override;`
- L323 _public prototype_ `virtual const FPoseIndicesHistory* GetPoseIndicesHistory() const override;`
- L326 _public function_ `virtual void DebugDraw(const UWorld* World, FColor Color) const override`
- L327 _public prototype_ `virtual void DebugDraw(FAnimInstanceProxy& AnimInstanceProxy, FColor Color) const override;`
- L331 _public prototype_ `int32 GetMaxNumPoses() const;`
- L332 _public prototype_ `float GetSamplingInterval() const;`
- L338 _public prototype_ `const FPoseSearchHistory& GetPoseSearchHistory() const;` — Experimental, this feature might be removed without warning, not for production use
- L340 _public prototype_ `FPoseSearchHistory& EditPoseSearchHistory();` — Experimental, this feature might be removed without warning, not for production use
- L343 _private member_ `FPoseSearchHistory PoseSearchHistory;`
- L344 _private member_ `FPoseSearchTrajectoryData::FState TrajectoryDataState;`
- L345 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(PoseDataThreadSafeCounter);`

#### struct `UE::PoseSearch::FGenerateTrajectoryPoseHistory`  
`struct FGenerateTrajectoryPoseHistory : public FPoseHistory`  
_L349-357_
- inherits: `FPoseHistory`
- desc: pose history struct that can generate a trajectory properly by calling it's IPoseHistory::GenerateTrajectory API (something other IPoseHistory don't do fully)
- L351 _public member_ `bool bGenerateTrajectory = false;`
- L352 _public member_ `bool bIsTrajectoryGeneratedBeforePreUpdate = false;`
- L353 _public member_ `FPoseSearchTrajectoryData::FSampling TrajectoryDataSampling;`
- L354 _public member_ `FPoseSearchTrajectoryData TrajectoryData;`
- L356 _public prototype_ `virtual void GenerateTrajectory(const UObject* AnimContext, float DeltaTime) override;`

#### struct `UE::PoseSearch::FMemStackPoseHistory`  
`struct FMemStackPoseHistory : public IPoseHistory`  
_L359-407_
- inherits: `IPoseHistory`
- L361 _public prototype_ `void Init(const IPoseHistory* InPoseHistory);`
- L364 _public prototype_ `virtual bool GetTransformAtTime(float Time, FTransform& OutBoneTransform, const USkeleton* BoneIndexSkeleton = nullptr, FBoneIndexType BoneIndexType = RootBoneIndexType, FBoneIndexType ReferenceBoneIndexType = ComponentSpaceIndexType, bool bExtrapolate = false) const override;` — IPoseHistory interface
- L365 _public prototype_ `virtual bool GetCurveValueAtTime(float Time, const FName& CurveName, float& outcurvevalue, bool bExtrapolate = false) const override;`
- L366 _public function_ `virtual const FTransformTrajectory& GetTrajectory() const override`
- L368 _public prototype_ `virtual void SetTrajectory(const FTransformTrajectory& InTrajectory, float InTrajectorySpeedMultiplier = 1.f) override;` — Experimental, this feature might be removed without warning, not for production use
- L370 _public prototype_ `virtual void GenerateTrajectory(const UObject* AnimContext, float DeltaTime) override;` — Experimental, this feature might be removed without warning, not for production use
- L371 _public function_ `virtual float GetTrajectorySpeedMultiplier() const override`
- L372 _public function_ `virtual bool IsEmpty() const override`
- L373 _public function_ `virtual const FBoneToTransformMap& GetBoneToTransformMap() const override`
- L374 _public function_ `virtual const TConstArrayView<FName> GetCollectedCurves() const override`
- L376 _public prototype_ `virtual int32 GetNumEntries() const override;`
- L377 _public prototype_ `virtual const FPoseHistoryEntry& GetEntry(int32 EntryIndex) const override;`
- L378 _public prototype_ `virtual const FPoseIndicesHistory* GetPoseIndicesHistory() const override;`
- L381 _public function_ `virtual void DebugDraw(const UWorld* World, FColor Color) const override`
- L382 _public prototype_ `virtual void DebugDraw(FAnimInstanceProxy& AnimInstanceProxy, FColor Color) const override;`
- L386 _public prototype_ `void AddFutureRootBone(float Time, const FTransform& FutureRootBoneTransform, bool bStoreScales);`
- L387 _public prototype_ `void AddFuturePose(float Time, IComponentSpacePoseProvider& ComponentSpacePoseProvider, const FBlendedCurve& Curves = FBlendedCurve() #if WITH_EDITORONLY_DATA , const FTransform& InDebugMeshTransform = FTransform::Identity #endif`
- L396 _public prototype_ `void ExtractAndAddFuturePoses(const UAnimationAsset* AnimationAsset, float AnimationTime, float FiniteDeltaTime, const FVector& BlendParameters, float IntervalTime, const USkeleton* OverrideSkeleton = nullptr, bool bUseRefPoseRootBone = false #if WITH_EDITORONLY_DATA , const FTransform& InDebugMeshTransform = FTransform::Identity #endif` — Experimental, this feature might be removed without warning, not for production use extracting a pose from AnimationAsset at AnimationTime and  (using BlendParameters in case it's a blend space) and placing it in the FMemStackPoseHistory at IntervalTime seconds if FiniteDeltaTime is > FiniteDeltaTime a second pose will be extracted at AnimationTime - FiniteDeltaTime and placed at IntervalTime - FiniteDeltaTime (for MM to be able to calculate velocities)
- L402 _public function_ `const IPoseHistory* GetThisOrPoseHistory() const`
- L405 _private member_ `const IPoseHistory* PoseHistory = nullptr;`
- L406 _private member_ `TArray<FPoseHistoryEntry, TInlineAllocator<4, TMemStackAllocator<>>> FutureEntries;`

#### struct `FPoseHistoryReference`  
`struct FPoseHistoryReference`  
_L412-416_
- reflection: `USTRUCT(BlueprintType)`
- L415 _public member_ `TSharedPtr<UE::PoseSearch::IPoseHistory> PoseHistory;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API POSESEARCH_API`
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace PoseSearch` (scope `UE`)
- L30 _typedef_ `typedef uint16 FComponentSpaceTransformIndex;` (scope `UE::PoseSearch`)
- L31 _typedef_ `typedef TPair<FBoneIndexType, FComponentSpaceTransformIndex> FBoneToTransformPair;` (scope `UE::PoseSearch`)
- L32 _typedef_ `typedef TMap<FBoneIndexType, FComponentSpaceTransformIndex> FBoneToTransformMap;` (scope `UE::PoseSearch`)
- L41 _function_ `friend inline uint32 GetTypeHash(const FHistoricalPoseIndex& Index)` (scope `UE::PoseSearch`)
- L128 _prototype_ `FArchive& operator<<(FArchive& Ar, FPoseHistoryEntry& Entry);` (scope `UE::PoseSearch`)
- L210 _namespace_ `namespace UE`
- L210 _namespace_ `namespace PoseSearch` (scope `UE`)
- L283 _prototype_ `FArchive& operator<<(FArchive& Ar, FArchivedPoseHistory& Entry);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchHistoryAttribute.h` (Public)


#### struct `FPoseHistoryAnimationAttribute`  
`struct FPoseHistoryAnimationAttribute`  
_L17-28_
- reflection: `USTRUCT(Experimental)`
- desc: Attribute type containing a const pointer to pose history for use by downstream systems. Uses a TWeakObjectPtr for scope checks.
- L21 _public member_ `const UE::PoseSearch::IPoseHistory* PoseHistory = nullptr;`
- L22 _public member_ `TWeakObjectPtr<const UObject> ScopeObject;`
- L24 _public function_ `bool IsValid() const`

#### struct `UE::Anim::TAttributeTypeTraits`  
`template<> struct TAttributeTypeTraits<FPoseHistoryAnimationAttribute> : public TAttributeTypeTraitsBase<FPoseHistoryAnimationAttribute>`  
_L39-45_
- inherits: `TAttributeTypeTraitsBase<FPoseHistoryAnimationAttribute>`
- desc: Pose history attribute is not blend-able by default

#### enum `UE::Anim::TAttributeTypeTraits::(anonymous)`  
``  
_L42-44_

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)
- L12 _externvar_ `extern const UE::Anim::FAttributeId PoseHistoryAttributeId;` (scope `UE::PoseSearch`)
- L30 _function_ `inline uint32 GetTypeHash(const FPoseHistoryAnimationAttribute& Key)`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Anim` (scope `UE`)
- L43 _enumerator_ `IsBlendable = false` (scope `UE::Anim::TAttributeTypeTraits::__anon25e839780103`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchHistoryCollectorAnimNodeLibrary.h` (Public)


#### struct `FPoseSearchHistoryCollectorAnimNodeReference`  
`struct FPoseSearchHistoryCollectorAnimNodeReference : public FAnimNodeReference`  
_L21-26_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L25 _public typedef_ `typedef FAnimNode_PoseSearchHistoryCollector FInternalNodeType;`

#### class `UPoseSearchHistoryCollectorAnimNodeLibrary`  
`class UPoseSearchHistoryCollectorAnimNodeLibrary : public UBlueprintFunctionLibrary`  
_L30-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Pose History node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L37 _public prototype_ `static FPoseSearchHistoryCollectorAnimNodeReference ConvertToPoseHistoryNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a Pose History node context from an anim node context
- L41 _public prototype_ `static void ConvertToPoseHistoryNodePure(const FAnimNodeReference& Node, FPoseSearchHistoryCollectorAnimNodeReference& PoseSearchHistoryCollectorNode, bool& Result);` — `UFUNCTION(BlueprintPure, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe, DisplayName = "Convert to Pose History Node"))` — Get a Pose History node context from an anim node context (pure)
- L44 _public prototype_ `static void GetPoseHistoryNodeTransformTrajectory(const FPoseSearchHistoryCollectorAnimNodeReference& PoseSearchHistoryCollectorNode, FTransformTrajectory& Trajectory);` — `UFUNCTION(BlueprintPure, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe, DisplayName = "Get Pose History Node Trajectory"))`
- L47 _public prototype_ `static void SetPoseHistoryNodeTransformTrajectory(const FPoseSearchHistoryCollectorAnimNodeReference& PoseSearchHistoryCollectorNode, const FTransformTrajectory& Trajectory);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe, DisplayName = "Set Pose History Node Trajectory"))`
- L50 _public prototype_ `static FPoseHistoryReference GetPoseHistoryReference(const FPoseSearchHistoryCollectorAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe))`
- L53 _public prototype_ `static bool GetPoseHistoryBoneWorldTransform(FTransform& OutTransform, const FPoseSearchHistoryCollectorAnimNodeReference& Node, const USkeleton* Skeleton, const FName BoneName, const float Time);` — `UFUNCTION(BlueprintPure, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe))`
- L56 _public prototype_ `static bool GetPoseHistoryBoneWorldLinearVelocity(FVector& OutVelocity, const FPoseSearchHistoryCollectorAnimNodeReference& Node, const USkeleton* Skeleton, const FName BoneName, const float Time, const float DeltaTime);` — `UFUNCTION(BlueprintPure, Category = "Animation|PoseHistory", meta = (BlueprintThreadSafe))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchIndex.h` (Public)


#### struct `UE::PoseSearch::FPoseMetadata`  
`struct FPoseMetadata`  
_L20-80_
- desc: This is kept for each pose in the search index along side the feature vector values and is used to influence the search.
- L27 _private member_ `uint32 ValueOffset : ValueOffsetNumBits = 0;`
- L28 _private member_ `uint32 AssetIndex : AssetIndexNumBits = 0;`
- L29 _private member_ `bool bBlockTransition : BlockTransitionNumBits = 0;`
- L30 _private member_ `FFloat16 CostAddend = 0.f;`
- L33 _public function_ `FPoseMetadata(uint32 InValueOffset = 0, uint32 InAssetIndex = 0, bool bInBlockTransition = false, float InCostAddend = 0.f) : ValueOffset(InValueOffset) , AssetIndex(InAssetIndex) , bBlockTransition(bInBlockTransition) , CostAddend(InCostAddend)`
- L44 _public function_ `bool IsBlockTransition() const`
- L49 _public function_ `uint32 GetAssetIndex() const`
- L54 _public function_ `float GetCostAddend() const`
- L59 _public function_ `uint32 GetValueOffset() const`
- L64 _public function_ `void SetValueOffset(uint32 Value)`
- L70 _public function_ `bool operator==(const FPoseMetadata& Other) const`

#### enum `UE::PoseSearch::FPoseMetadata::(anonymous)`  
`enum`  
_L23-23_

#### enum `UE::PoseSearch::FPoseMetadata::(anonymous)`  
`enum`  
_L24-24_

#### enum `UE::PoseSearch::FPoseMetadata::(anonymous)`  
`enum`  
_L25-25_

#### struct `UE::PoseSearch::FSearchIndexAsset`  
`struct FSearchIndexAsset`  
_L86-291_
- desc: Information about a source animation asset used by a search index. Some source animation entries may generate multiple FSearchIndexAsset entries.
- L88 _public function_ `FSearchIndexAsset()`
- L90 _public function_ `FSearchIndexAsset( int32 InSourceAssetIdx, bool bInMirrored, bool bInLooping, bool bInDisableReselection, int32 InPermutationIdx, const FVector& InBlendParameters, int32 InFirstPoseIdx, int32 InFirstSampleIdx, int32 InLastSampleIdx, float InToRealTimeFactor = 1.f) : SourceAssetIdx(InSourceAssetIdx) , bMirrored(bInMirrored) , bLooping(bInLooping) , bDisableReselection(bInDisableReselection) , PermutationIdx(InPermutationIdx) , BlendParameterX(InBlendParameters.X) , BlendParameterY(InBlendParameters.Y) , FirstPoseIdx(InFirstPoseIdx) , FirstSampleIdx(InFirstSampleIdx) , LastSampleIdx(InLastSampleIdx) , ToRealTimeFactor(InToRealTimeFactor)`
- L117 _public function_ `FSearchIndexAsset( int32 InSourceAssetIdx, int32 InFirstPoseIdx, bool bInMirrored, bool bInLooping, bool bInDisableReselection, const FFloatInterval& InSamplingInterval, int32 SchemaSampleRate, int32 InPermutationIdx, FVector InBlendParameters = FVector::Zero(), float InToRealTimeFactor = 1.f) : FSearchIndexAsset( InSourceAssetIdx, bInMirrored, bInLooping, bInDisableReselection, InPermutationIdx, InBlendParameters, InFirstPoseIdx, FMath::CeilToInt(InSamplingInterval.Min * SchemaSampleRate), FMath::FloorToInt(InSamplingInterval.Max * SchemaSampleRate), InToRealTimeFactor)`
- L143 _public prototype_ `FFloatInterval GetExtrapolationTimeInterval(int32 SchemaSampleRate, const FFloatInterval& AdditionalExtrapolationTime) const;`
- L144 _public function_ `int32 GetSourceAssetIdx() const`
- L145 _public function_ `bool IsMirrored() const`
- L146 _public function_ `bool IsLooping() const`
- L147 _public function_ `bool IsDisableReselection() const`
- L148 _public function_ `int32 GetPermutationIdx() const`
- L149 _public function_ `FVector GetBlendParameters() const`
- L150 _public function_ `float GetToRealTimeFactor() const`
- L151 _public function_ `int32 GetFirstPoseIdx() const`
- L153 _public function_ `bool IsPoseInRange(int32 PoseIdx) const`
- L154 _public prototype_ `bool operator==(const FSearchIndexAsset& Other) const;`
- L157 _public function_ `bool IsInitialized() const`
- L168 _public function_ `int32 GetBeginSampleIdx() const`
- L169 _public function_ `int32 GetEndSampleIdx() const`
- L170 _public function_ `int32 GetNumPoses() const`
- L172 _public function_ `float GetFirstSampleTime(int32 SchemaSampleRate) const`
- L173 _public function_ `float GetLastSampleTime(int32 SchemaSampleRate) const`
- L175 _public function_ `int32 GetPoseIndexFromTime(float RealTimeInSeconds, int32 SchemaSampleRate) const`
- L197 _public function_ `void IteratePoseIndexesOverTime(float StartTime, float EndTime, int32 SchemaSampleRate, const TFunction<void(int32 PoseIdx)>& ProcessPoseIndex) const` — iteractes over all the valid pose indexes contained in this FSearchIndexAsset from StartTime to EndTime, calling ProcessPoseIndex function on every pose accounting for looping
- L242 _public function_ `float GetTimeFromPoseIndex(int32 PoseIdx, int32 SchemaSampleRate) const`
- L254 _public function_ `float GetDeltaTimeBetweenPoseIndexes(int32 FromPoseIdx, int32 ToPoseIdx, int32 SchemaSampleRate) const` — calculates the delta time in seconds ToPoseIdx - FromPoseIdx
- L274 _private member_ `const int32 SourceAssetIdx = INDEX_NONE;` — Index of the source asset in search index's container (i.e. UPoseSearchDatabase)
- L276 _private member_ `const bool bMirrored : 1 = false;`
- L277 _private member_ `const bool bLooping : 1 = false;`
- L278 _private member_ `const bool bDisableReselection : 1 = false;`
- L279 _private member_ `const int32 PermutationIdx = INDEX_NONE;`
- L282 _private member_ `const float BlendParameterX = 0.f;` — fixed blend space patameters associated to this FSearchIndexAsset if SourceAssetIdx refers to a blend space
- L283 _private member_ `const float BlendParameterY = 0.f;`
- L285 _private member_ `const int32 FirstPoseIdx = INDEX_NONE;`
- L286 _private member_ `const int32 FirstSampleIdx = INDEX_NONE;`
- L287 _private member_ `const int32 LastSampleIdx = INDEX_NONE;`
- L290 _private member_ `const float ToRealTimeFactor = 1.f;` — if SourceAssetIdx refers to a blend space, the animation asset would be in a normalized time interval [0-1]. ToRealTimeFactor brings the normalized time to the real time for the fixed BlendParameterX/BlendParameterY

#### struct `UE::PoseSearch::FSearchStats`  
`struct FSearchStats`  
_L294-304_
- L296 _public member_ `float AverageSpeed = 0.f;`
- L297 _public member_ `float MaxSpeed = 0.f;`
- L298 _public member_ `float AverageAcceleration = 0.f;`
- L299 _public member_ `float MaxAcceleration = 0.f;`
- L301 _public prototype_ `void Reset();`
- L302 _public prototype_ `bool operator==(const FSearchStats& Other) const;`

#### struct `UE::PoseSearch::FSparsePoseMultiMap`  
`template <typename Type = int32> struct FSparsePoseMultiMap`  
_L309-458_
- desc: compact representation of an array of arrays
- L311 _public prototype_ `FSparsePoseMultiMap() = default;`
- L312 _public prototype_ `~FSparsePoseMultiMap() = default;`
- L313 _public prototype_ `FSparsePoseMultiMap(const FSparsePoseMultiMap& Other) = default;`
- L314 _public prototype_ `FSparsePoseMultiMap(FSparsePoseMultiMap&& Other) = default;`
- L315 _public prototype_ `FSparsePoseMultiMap& operator=(const FSparsePoseMultiMap& Other) = default;`
- L316 _public prototype_ `FSparsePoseMultiMap& operator=(FSparsePoseMultiMap&& Other) = default;`
- L318 _public function_ `FSparsePoseMultiMap(Type InMaxKey, Type InMaxValue)`
- L323 _public function_ `FSparsePoseMultiMap(TConstArrayView<TPair<Type, TArray<Type>>> Pairs, Type InMaxValue)`
- L328 _public function_ `void Init(Type InMaxKey, Type InMaxValue)`
- L343 _public function_ `void Init(TConstArrayView<TPair<Type, TArray<Type>>> Pairs, Type InMaxValue)`
- L353 _public function_ `void Insert(Type Key, TConstArrayView<Type> Values)`
- L398 _public function_ `TConstArrayView<Type> operator [](Type Key) const`
- L418 _public function_ `Type Num() const`
- L423 _public function_ `SIZE_T GetAllocatedSize() const`
- L428 _public function_ `bool operator==(const FSparsePoseMultiMap& Other) const`
- L446 _public function_ `void Reset()`
- L454 _public member_ `Type MaxKey = Type(0);`
- L455 _public member_ `Type MaxValue = Type(0);`
- L456 _public member_ `Type DeltaKeyValue = Type(0);`
- L457 _public member_ `TArray<Type> DataValues;`

#### struct `UE::PoseSearch::FEventDataCollector`  
`struct FEventDataCollector`  
_L462-474_
- desc: Experimental, this feature might be removed without warning, not for production use
- L464 _public typedef_ `typedef TSet<int32, DefaultKeyFuncs<int32>, TInlineSetAllocator<256>> FPoseIndexes;`
- L465 _public typedef_ `typedef TPair<FGameplayTag, FPoseIndexes> FTagToPoseIndexes;`
- L466 _public typedef_ `typedef TMap<FGameplayTag, FPoseIndexes, TInlineSetAllocator<16>> FData;`
- L468 _public prototype_ `void Emplace(const FGameplayTag& EventTag, int32 PoseIdx);`
- L469 _public prototype_ `void MergeWith(const FEventDataCollector& Other);`
- L470 _public function_ `const FData& GetData() const`
- L473 _private member_ `TMap<FGameplayTag, FPoseIndexes, TInlineSetAllocator<16>> Data;`

#### struct `UE::PoseSearch::FEventData`  
`struct FEventData`  
_L478-499_
- desc: Experimental, this feature might be removed without warning, not for production use
- L480 _public typedef_ `typedef TArray<int32> FPoseIndexes;`
- L481 _public typedef_ `typedef TPair<FGameplayTag, FPoseIndexes> FTagToPoseIndexes;`
- L482 _public typedef_ `typedef TArray<FTagToPoseIndexes> FData;`
- L485 _public prototype_ `bool operator==(const FEventData& Other) const;`
- L486 _public prototype_ `const TConstArrayView<int32> GetPosesWithEvent(const FGameplayTag& GameplayTag) const;`
- L487 _public prototype_ `bool IsPoseFromEventTag(int32 EventPoseIdx, const FGameplayTag& GameplayTag) const;`
- L488 _public function_ `const FData& GetData() const`
- L489 _public prototype_ `void Reset();`
- L492 _public prototype_ `void Initialize(const FEventDataCollector& EventDataCollector);`
- L493 _public prototype_ `SIZE_T GetAllocatedSize(void) const;`
- L494 _public prototype_ `void ValidateEventData() const;`
- L498 _private member_ `FData Data;`

#### struct `UE::PoseSearch::FSearchIndexBase`  
`struct FSearchIndexBase`  
_L504-569_
- desc: case class for FSearchIndex. building block used to gather data for data mining and calculate weights, pca, kdtree stuff
- L506 _public member_ `TAlignedArray<float> Values;`
- L507 _public member_ `FSparsePoseMultiMap<int32> ValuesVectorToPoseIndexes;`
- L508 _public member_ `TAlignedArray<FPoseMetadata> PoseMetadata;`
- L509 _public member_ `bool bAnyBlockTransition = false;`
- L510 _public member_ `TAlignedArray<FSearchIndexAsset> Assets;`
- L512 _public member_ `FEventData EventData;` — Experimental, this feature might be removed without warning, not for production use
- L515 _public member_ `float MinCostAddend = -MAX_FLT;` — minimum of the database metadata CostAddend: it represents the minimum cost of any search for the associated database (we'll skip the search in case the search result total cost is already less than MinCostAddend)
- L518 _public member_ `FSearchStats Stats;`
- L522 _public prototype_ `FSearchIndexBase();` — overriding ctor, copy, move to allow deprecations.
- L523 _public prototype_ `~FSearchIndexBase();`
- L524 _public prototype_ `FSearchIndexBase(const FSearchIndexBase& Other);`
- L525 _public prototype_ `FSearchIndexBase(FSearchIndexBase&& Other);`
- L526 _public prototype_ `FSearchIndexBase& operator=(const FSearchIndexBase& Other);`
- L527 _public prototype_ `FSearchIndexBase& operator=(FSearchIndexBase&& Other);`
- L529 _public function_ `int32 GetNumPoses() const`
- L530 _public function_ `int32 GetNumValuesVectors(int32 DataCardinality) const`
- L537 _public function_ `bool IsValidPoseIndex(int32 PoseIdx) const`
- L538 _public prototype_ `bool IsEmpty() const;`
- L539 _public function_ `bool IsValuesEmpty() const`
- L541 _public function_ `void ResetValues()`
- L542 _public prototype_ `void AllocateData(int32 DataCardinality, int32 NumPoses);`
- L544 _public prototype_ `const FSearchIndexAsset& GetAssetForPose(int32 PoseIdx) const;`
- L545 _public prototype_ `const FSearchIndexAsset* GetAssetForPoseSafe(int32 PoseIdx) const;`
- L547 _public prototype_ `void Reset();`
- L549 _public prototype_ `void PruneDuplicateValues(float SimilarityThreshold, int32 DataCardinality, bool bDoNotGenerateValuesVectorToPoseIndexes);`
- L551 _public function_ `TConstArrayView<float> GetPoseValuesBase(int32 PoseIdx, int32 DataCardinality) const`
- L559 _public function_ `TConstArrayView<float> GetValuesVector(int32 ValuesVectorIdx, int32 DataCardinality) const`
- L566 _public prototype_ `bool operator==(const FSearchIndexBase& Other) const;`

#### struct `UE::PoseSearch::FSearchIndex`  
`struct FSearchIndex : public FSearchIndexBase`  
_L575-640_
- inherits: `FSearchIndexBase`
- desc: A search index for animation poses. The structure of the search index is determined by its UPoseSearchSchema. May represent a single animation (see UPoseSearchSequenceMetaData) or a collection (see UPoseSearchDatabase).
- L582 _public member_ `TAlignedArray<float> WeightsSqrt;` — we store weights square roots to reduce numerical errors when CompareFeatureVectors ((VA - VB) * VW).square().sum() instead of ((VA - VB).square() * VW).sum() since (VA - VB).square() could lead to big numbers, and VW being multiplied by the variance of the dataset
- L588 _public member_ `TAlignedArray<float> PCAValues;` — array containing the data of FSearchIndexBase::Values encoded in PCA space. used to create the kdtree. Not all the poses have a related PCAValue(s) array since, for instance, poses marked as block transition don't have to be searchable via kdtree, but only via continuing pose search, so method like GetPCAValueIndex or GetPoseToPCAValuesVectorIndexes could not find the respective PCAValueIndex of a requested pose
- L589 _public member_ `FSparsePoseMultiMap<int32> PCAValuesVectorToPoseIndexes;`
- L590 _public member_ `TAlignedArray<float> PCAProjectionMatrix;`
- L591 _public member_ `TAlignedArray<float> Mean;`
- L593 _public member_ `FKDTree KDTree;`
- L594 _public member_ `FVPTree VPTree;`
- L597 _public member_ `TAlignedArray<float> DeviationEditorOnly;`
- L598 _public member_ `float PCAExplainedVarianceEditorOnly = 0.f;`
- L601 _public prototype_ `FSearchIndex() = default;`
- L602 _public prototype_ `~FSearchIndex() = default;`
- L603 _public prototype_ `FSearchIndex(const FSearchIndex& Other);` — custom copy constructor to deal with the KDTree DataSrc
- L604 _public prototype_ `FSearchIndex(FSearchIndex&& Other);`
- L605 _public prototype_ `FSearchIndex& operator=(const FSearchIndex& Other);` — custom equal operator to deal with the KDTree DataSrc
- L606 _public prototype_ `FSearchIndex& operator=(FSearchIndex&& Other);`
- L608 _public prototype_ `void Reset();`
- L609 _public prototype_ `TConstArrayView<float> GetPoseValues(int32 PoseIdx) const;`
- L610 _public prototype_ `TConstArrayView<float> GetReconstructedPoseValues(int32 PoseIdx, TArrayView<float> BufferUsedForReconstruction) const;`
- L611 _public prototype_ `int32 GetNumDimensions() const;`
- L612 _public prototype_ `int32 GetNumberOfPrincipalComponents() const;`
- L613 _public prototype_ `TConstArrayView<float> PCAProject(TConstArrayView<float> PoseValues, TArrayView<float> BufferUsedForProjection) const;`
- L615 _public prototype_ `TConstArrayView<float> GetPoseValuesSafe(int32 PoseIdx, TArray<float>& BufferUsedForReconstruction) const;`
- L620 _public prototype_ `TConstArrayView<float> GetPCAPoseValues(int32 PCAValuesVectorIdx) const;` — since PCAValues (as well as Values can be pruned out from duplicate data, we lose the 1:1 mapping between PoseIdx and PCAValuesVectorIdx that in the case of GetPoseValuesSafe it's stored in PoseMetadata[PoseIdx].GetValueOffset(), but missing for the PCAValues, so this API input is NOT a PoseIdx mapping between PoseIdx to PCAValuesVectorIdx can be reconstructed by inverting the PCAValuesVectorToPoseIndexes via GetPoseToPCAValuesVectorIndexes
- L622 _public function_ `int32 GetNumPCAValuesVectors(int32 DataCardinality) const`
- L629 _public prototype_ `void PruneDuplicatePCAValues(float SimilarityThreshold, int32 NumberOfPrincipalComponents);`
- L630 _public prototype_ `void PrunePCAValuesFromBlockTransitionPoses(int32 NumberOfPrincipalComponents);`
- L633 _public prototype_ `void GetPoseToPCAValuesVectorIndexes(TArray<uint32>& PoseToPCAValuesVectorIndexes) const;` — returns the inverse mapping of PCAValuesVectorToPoseIndexes
- L636 _public prototype_ `int32 GetPCAValueIndex(int32 PoseIdx) const;` — returns the PCAValueIndex from the pose index. the method is very slow. consider calling GetPoseToPCAValuesVectorIndexes to cache ALL the PCAValueIndex from the pose index mapping
- L638 _public prototype_ `bool operator==(const FSearchIndex& Other) const;`

#### struct `UE::PoseSearch::FVPTreeDataSource`  
`struct FVPTreeDataSource`  
_L642-665_
- L644 _public function_ `explicit FVPTreeDataSource(const FSearchIndex& InSearchIndex) : SearchIndex(InSearchIndex)`
- L649 _public function_ `const TConstArrayView<float> operator[](int32 Index) const`
- L655 _public function_ `int32 Num() const`
- L661 _public prototype_ `static float GetDistance(const TConstArrayView<float> A, const TConstArrayView<float> B);`
- L664 _private member_ `const FSearchIndex& SearchIndex;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PoseSearch` (scope `UE`)
- L14 _prototype_ `void CompareFeatureVectors(TConstArrayView<float> A, TConstArrayView<float> B, TConstArrayView<float> WeightsSqrt, TArrayView<float> Result);` (scope `UE::PoseSearch`)
- L15 _prototype_ `float CompareFeatureVectors(TConstArrayView<float> A, TConstArrayView<float> B);` (scope `UE::PoseSearch`)
- L23 _enumerator_ `enum { ValueOffsetNumBits = 27 }; enum { AssetIndexNumBits = 20 }; enum { BlockTransitionNumBits = 1 }; uint32 ValueOffset : ValueOffsetNumBits = 0; uint32 AssetIndex : AssetIndexNumBits = 0; bool bBlockTransition : BlockTransitionNumBits = 0; FFloat16 CostAddend = 0.f;` (scope `UE::PoseSearch::FPoseMetadata::__anon4b2af18a0103`)
- L24 _enumerator_ `enum { AssetIndexNumBits = 20 }; enum { BlockTransitionNumBits = 1 }; uint32 ValueOffset : ValueOffsetNumBits = 0; uint32 AssetIndex : AssetIndexNumBits = 0; bool bBlockTransition : BlockTransitionNumBits = 0; FFloat16 CostAddend = 0.f;` (scope `UE::PoseSearch::FPoseMetadata::__anon4b2af18a0203`)
- L25 _enumerator_ `enum { BlockTransitionNumBits = 1 }; uint32 ValueOffset : ValueOffsetNumBits = 0; uint32 AssetIndex : AssetIndexNumBits = 0; bool bBlockTransition : BlockTransitionNumBits = 0; FFloat16 CostAddend = 0.f; public:` (scope `UE::PoseSearch::FPoseMetadata::__anon4b2af18a0303`)
- L437 _function_ `friend FArchive& operator<<(FArchive& Ar, FSparsePoseMultiMap& SparsePoseMultiMap)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionAsset.h` (Public)


#### struct `FPoseSearchInteractionAssetItem`  
`struct FPoseSearchInteractionAssetItem`  
_L13-46_
- reflection: `USTRUCT(Experimental, BlueprintType)`
- L19 _public member_ `TObjectPtr<UAnimationAsset> Animation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — associated aniamtion for this FPoseSearchInteractionAssetItem
- L23 _public member_ `FName Role;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — associated role for this FPoseSearchInteractionAssetItem
- L29 _public member_ `float WarpingWeightRotation = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warping", meta = (ClampMin = "0", ClampMax = "1"))` — relative weight to the other FPoseSearchInteractionAssetItem::WarpingWeightRotation(s) defining which character will be rotated while warping 0 - the associated character to this item will move fully to compensate the warping errors > 0 && all the other FPoseSearchInteractionAssetItem::WarpingWeightTranslation as zero, and the associated character will not move
- L35 _public member_ `float WarpingWeightTranslation = 0.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Warping", meta = (ClampMin = "0", ClampMax = "1"))` — relative weight to the other FPoseSearchInteractionAssetItem::WarpingWeightTranslation(s) defining which character will be translated while warping 0 - the associated character to this item will move fully to compensate the warping errors > 0 && all the other FPoseSearchInteractionAssetItem::WarpingWeightTranslation as zero, and the associated character will not move
- L39 _public member_ `FTransform Origin = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — offset from the origin
- L44 _public member_ `TObjectPtr<USkeletalMesh> PreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (ExcludeFromHash))` — If null, the default preview mesh for the skeleton will be used. Otherwise, this will be used in preview scenes.

#### class `UPoseSearchInteractionAsset`  
`class UPoseSearchInteractionAsset : public UMultiAnimAsset`  
_L49-102_
- reflection: `UCLASS(MinimalAPI, Experimental, BlueprintType, Category = "Animation|Pose Search")`
- inherits: `UMultiAnimAsset`
- L55 _public member_ `TArray<FPoseSearchInteractionAssetItem> Items;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")`
- L58 _public member_ `float WarpingBankingWeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0", ClampMax = "1"))`
- L61 _public member_ `float MinimalTranslationWeight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (ClampMin = "0", ClampMax = "1"))`
- L66 _public member_ `TArray<FTransform> DebugWarpOffsets;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (EditCondition=bEnableDebugWarp, EditConditionHides))`
- L74 _public member_ `float DebugWarpAmount = 0.f;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (ClampMin = "0", ClampMax = "1", EditCondition=bEnableDebugWarp, EditConditionHides))` — used to test warping: 0 - no warping applied, 1 - full warping/alignment applied test warping actors will be offsetted by Items::DebugWarpOffset transforms from the original UMultiAnimAsset::GetOrigin() definition and warped accordingly with CalculateWarpTransforms following the rotation and translation weights defined in Items::WarpingWeightRotation and Items::WarpingWeightTranslation as relative weights between the Items (they'll be normalized at runtime)
- L78 _public member_ `float DebugTimeOffset = 0.f;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (ClampMin = "0", EditCondition=bEnableDebugWarp, EditConditionHides))` — useful to test TimeOffset
- L81 _public member_ `bool bEnableDebugWarp = false;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Debug")`
- L84 _public prototype_ `virtual bool IsLooping() const override;`
- L85 _public prototype_ `virtual bool HasRootMotion() const override;`
- L86 _public prototype_ `virtual float GetPlayLength(const FVector& BlendParameters) const override;`
- L88 _public function_ `virtual int32 GetNumRoles() const override`
- L89 _public function_ `virtual UE::PoseSearch::FRole GetRole(int32 RoleIndex) const override`
- L91 _public prototype_ `virtual UAnimationAsset* GetAnimationAsset(const UE::PoseSearch::FRole& Role) const override;`
- L93 _public prototype_ `virtual FTransform GetOrigin(const UE::PoseSearch::FRole& Role) const override;`
- L96 _public prototype_ `FTransform GetDebugWarpOrigin(const UE::PoseSearch::FRole& Role, bool bComposeWithDebugWarpOffset) const;`
- L97 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh(const UE::PoseSearch::FRole& Role) const override;`
- L100 _public prototype_ `virtual void CalculateWarpTransforms(float Time, float TimeOffset, const TConstArrayView<const FTransform> ActorRootBoneTransforms, TArrayView<FTransform> FullAlignedActorRootBoneTransforms, const TConstArrayView<const UMirrorDataTable*> MirrorDataTables = TConstArrayView<const UMirrorDataTable*>(), const TConstArrayView<TObjectPtr<const UObject>> DebugAnimContexts = TConstArrayView<TObjectPtr<const UObject>>()) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionAvailability.h` (Public)


#### struct `FPoseSearchInteractionAvailability`  
`struct FPoseSearchInteractionAvailability`  
_L17-60_
- reflection: `USTRUCT(Experimental, BlueprintType, Category = "Animation|Pose Search")`
- desc: input for MotionMatchInteraction_Pure: it declares that the associated character ("AnimContext" that could be an AnimInstance or an AnimNextCharacterComponent) is willing to partecipate in an interaction described by a UMultiAnimAsset (derived by UPoseSearchInteractionAsset) contained in the UPoseSearchDatabase Database with one of the roles in RolesFilter (if empty ANY of the Database roles can be taken) the MotionMatchInteraction_Pure will ultimately setup a motion matching query using looking for the pose history "PoseHistoryName" to gather bone and trajectory positions for this character for an interaction to be valid, the query needs to find all the other interacting characters within BroadPhaseRadius, and reach a maximum cost of MaxCost Experimental, this feature might be removed without warning, not for production use
- L23 _public member_ `TObjectPtr<UPoseSearchDatabase> Database;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — Database describing the interaction. It'll contains multi character UMultiAnimAsset and a schema with multiple skeletons with associated roles
- L32 _public member_ `FName Tag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — in case this availability Database is valid (not null), Tag (if IsTagValid()) is used to flag the Database with a specific name. Different availabilities can share the same Tag. in case this availability Database is NOT valid, we use the valid Tag to figure out all the possible databases that can be assigned to this availability from all the published availabilities. The reason behind Tag is, for example, to be able to have NPCs been able to interact with a main character (MC), without the MC having a direct dependency to the database used for the interaction allowing those NPCs to be contextually loaded/unloaded, streamed in/out, with the obvious advantages for the the memory managment of the "payload" database. Another reason for Tag, is to facilitate the setup of interactions, where the MC have to publish only one availability with its own assigned Role (in RolesFilter) automatically contextually resolved in multiple different types of possible databases: it could be MC-NPC, MC-Vehicle, MC-Whatever
- L36 _public member_ `TArray<FName> RolesFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — roles the character is willing to take to partecipate in this interaction. If empty ANY of the Database roles can be taken
- L40 _public member_ `float BroadPhaseRadius = 500.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — the associated character to this FPoseSearchInteractionAvailability will partecipate in an interaction only if all the necessary roles gest assigned to character within BroadPhaseRadius centimeters
- L45 _public member_ `float BroadPhaseRadiusIncrementOnInteraction = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — during interaction the BroadPhaseRadius will be incremented by BroadPhaseRadiusIncrementOnInteraction to create geometrical histeresys, where it's harder for actors to get into interaction rather than staying in interaction
- L49 _public member_ `bool bDisableCollisions = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — if true, the system will disable collsions between interacting characters
- L55 _public member_ `int32 TickPriority = UE::PoseSearch::DefaultTickPriority;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — the Actor with the higher TickPriority of any Availability request will be elected as the MainActor of the interaction island (containing all the actors that could interact with each other) the main Actor will tick first and all the other interacting actors will tick after in a concurrently from each other. TickPriority is useful if your setup is already enforcing tick dependency between actors, and the motion matching interaction system needs to play nicely with them.
- L57 _public function_ `bool IsTagValid() const`
- L59 _public prototype_ `bool operator==(const FPoseSearchInteractionAvailability& Other) const = default;`

#### struct `UE::PoseSearch::FInteractionAvailability`  
`struct FInteractionAvailability : public FPoseSearchInteractionAvailability`  
_L65-82_
- inherits: `FPoseSearchInteractionAvailability`
- desc: Experimental, this feature might be removed without warning, not for production use
- L67 _public function_ `void Init(const FPoseSearchInteractionAvailability& InAvailability, FName InPoseHistoryName, const IPoseHistory* InPoseHistory)`
- L76 _public prototype_ `FString GetPoseHistoryName() const;`
- L77 _public prototype_ `const IPoseHistory* GetPoseHistory(const UObject* AnimContext) const;`
- L80 _private member_ `FName PoseHistoryName;`
- L81 _private member_ `const IPoseHistory* PoseHistory = nullptr;`

#### struct `UE::PoseSearch::FInteractionAnimContextAvailabilities`  
`struct FInteractionAnimContextAvailabilities`  
_L85-89_
- desc: Experimental, this feature might be removed without warning, not for production use
- L87 _public member_ `TObjectPtr<const UObject> AnimContext;`
- L88 _public member_ `TArray<FInteractionAvailability> Availabilities;`

#### Free symbols / members of external scopes

- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionIsland.h` (Public)


#### struct `UE::PoseSearch::FInteractionSearchContextBase`  
`struct FInteractionSearchContextBase`  
_L29-69_
- desc: Experimental, this feature might be removed without warning, not for production use
- L31 _public function_ `int32 Num() const`
- L32 _public function_ `const UObject* GetAnimContext(int32 Index) const`
- L33 _public prototype_ `const IPoseHistory* GetPoseHistory(int32 Index) const;`
- L34 _public function_ `const FRole GetRole(int32 Index) const`
- L35 _public function_ `const UPoseSearchDatabase* GetDatabase() const`
- L36 _public function_ `const TConstArrayView<FRole> GetRoles() const`
- L37 _public function_ `const TConstArrayView<TObjectPtr<const UObject>> GetAnimContexts() const`
- L39 _public function_ `bool IsDisableCollisions() const`
- L41 _public prototype_ `uint32 GetHashForEquivalence() const;`
- L42 _public prototype_ `uint32 GetContextHashForEquivalence() const;`
- L43 _public prototype_ `void CacheHashesForEquivalence();`
- L45 _public function_ `void SetDatabase(const UPoseSearchDatabase* InDatabase)`
- L46 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L47 _public prototype_ `void Add(const UObject* AnimContext, const IPoseHistory* PoseHistory, const FRole Role, bool bWantsDisableCollisions);`
- L50 _public prototype_ `bool CheckForConsistency() const;`
- L54 _private prototype_ `void CalculateHashesForEquivalence(uint32& OutCachedHashForEquivalence, uint32& OutCachedContextHashForEquivalence) const;`
- L56 _private member_ `TArray<TObjectPtr<const UObject>, TInlineAllocator<PreallocatedRolesNum>> AnimContexts;`
- L60 _private member_ `TArray<TWeakPtr<const IPoseHistory, ESPMode::ThreadSafe>, TInlineAllocator<PreallocatedRolesNum>> PoseHistories;` — storing PoseHistories as TWeakPtr since they are from nodes or traits that can be invalidated within the same frame. for performance reasons are not used to determine equivalence IsEquivalent / GetHashForEquivalence
- L62 _private member_ `TArray<FRole, TInlineAllocator<PreallocatedRolesNum>> Roles;`
- L64 _private member_ `TObjectPtr<const UPoseSearchDatabase> Database;`
- L65 _private member_ `bool bDisableCollisions = false;`
- L67 _private member_ `uint32 CachedHashForEquivalence = InvalidCachedHashForEquivalence;`
- L68 _private member_ `uint32 CachedContextHashForEquivalence = InvalidCachedHashForEquivalence;`

#### enum `UE::PoseSearch::FInteractionSearchContextBase::(anonymous)`  
`enum`  
_L66-66_

#### struct `UE::PoseSearch::FInteractionSearchResult`  
`struct FInteractionSearchResult : public FSearchResult`  
_L72-89_
- inherits: `FSearchResult`
- desc: Experimental, this feature might be removed without warning, not for production use
- L74 _public member_ `int32 SearchIndex = INDEX_NONE;`
- L78 _public member_ `TArray<FTransform, TInlineAllocator<PreallocatedRolesNum>> ActorRootTransforms;` — cached actors root transforms for all the roles in SelectedAnimation (as UMultiAnimAsset), so we don't have to query the pose history to gather it when it's not thread safe to do so
- L82 _public member_ `TArray<FTransform, TInlineAllocator<PreallocatedRolesNum>> ActorRootBoneTransforms;` — cached actors root bone transforms for all the roles in SelectedAnimation (as UMultiAnimAsset), so we don't have to query the pose history to gather it when it's not thread safe to do so
- L86 _public member_ `TArray<FPoseSearchConstraint> Constraints;` — @todo: preallocate some... all the active constraints in this result
- L88 _public prototype_ `bool operator==(const FInteractionSearchResult& Other) const;`

#### struct `UE::PoseSearch::FValidInteractionSearch`  
`struct FValidInteractionSearch : public FInteractionSearchContextBase`  
_L92-113_
- inherits: `FInteractionSearchContextBase`
- desc: Experimental, this feature might be removed without warning, not for production use
- L94 _public prototype_ `FValidInteractionSearch& Init(const FInteractionSearchContextBase& SearchContextBase);`
- L95 _public prototype_ `void Update(const FInteractionSearchResult& InSearchResult);`
- L96 _public prototype_ `void DoDisableCollisions();`
- L97 _public prototype_ `void UndoDisableCollisions();`
- L100 _public prototype_ `void VLogContext(const FColor& Color) const;`
- L103 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L104 _public function_ `const FInteractionSearchResult& GetSearchResult() const`
- L107 _private member_ `FInteractionSearchResult SearchResult;`
- L108 _private member_ `FDisabledCollisions DisabledCollisions;`
- L111 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(ThreadSafeCounter);`

#### struct `UE::PoseSearch::FValidInteractionSearches`  
`struct FValidInteractionSearches`  
_L115-140_
- L117 _public prototype_ `void Update(const UPoseSearchInteractionSubsystem* InteractionSubsystem);`
- L118 _public prototype_ `const FValidInteractionSearch* Get(const FInteractionSearchContext& SearchContext) const;`
- L120 _public prototype_ `bool IsThereAnyValidSearchWithTheSameContexts(const FInteractionSearchContext& SearchContext) const;` — returns true if the tuple of AnimContexts (e.g. pair of AnimInstance(s) ~ Characters) from the SearchContext is used in any FValidInteractionSearch with any assigned roles
- L121 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L124 _private prototype_ `static void OnInteractionStart(FValidInteractionSearch& ValidInteractionSearch, const UPoseSearchInteractionSubsystem* InteractionSubsystem);`
- L125 _private prototype_ `static void OnInteractionContinuing(FValidInteractionSearch& ValidInteractionSearch, const UPoseSearchInteractionSubsystem* InteractionSubsystem);`
- L126 _private prototype_ `static void OnInteractionEnd(FValidInteractionSearch& ValidInteractionSearch, const UPoseSearchInteractionSubsystem* InteractionSubsystem);`
- L129 _private member_ `TMap<uint32, FValidInteractionSearch> Searches;` — mapping from FValidInteractionSearch::GetHashForEquivalence to FValidInteractionSearch
- L135 _private member_ `TMap<uint32, TArray<uint32>> ContextsToSearches;` — mapping from FValidInteractionSearch::GetContextHashForEquivalence to FValidInteractionSearch::GetHashForEquivalence(s) the map Key represents what AnimContexts (e.g. AnimInstance(s), that can be confused with Actors...) can be interacting. each map Value represents a possible interaction (associated to a FValidInteractionSearch), and only one will be a valid search, and all the others are searches that still has been performed (and are valid)
- L138 _private prototype_ `UE_MT_DECLARE_TS_RW_ACCESS_DETECTOR(ThreadSafeCounter);`

#### struct `UE::PoseSearch::FInteractionSearchContext`  
`struct FInteractionSearchContext : public FInteractionSearchContextBase`  
_L146-184_
- inherits: `FInteractionSearchContextBase`
- desc: Experimental, this feature might be removed without warning, not for production use stack allocated temporary struct used to generate interaction contexts, then the FInteractionSearchContextBase portion will be stored including DisabledCollisions as FValidInteractionSearch
- L148 _public prototype_ `void Add(const UObject* AnimContext, const IPoseHistory* PoseHistory , const FRole Role, bool bWantsDisableCollisions, int32 TickPriority #if ENABLE_ANIM_DEBUG , float InBroadPhaseRadius, float InBroadPhaseRadiusIncrementOnInteraction #endif`
- L155 _public function_ `int32 GetTickPriority(int32 Index) const`
- L157 _public prototype_ `FPoseSearchContinuingProperties GetContinuingProperties() const;`
- L159 _public function_ `bool IsContinuingInteraction() const`
- L160 _public function_ `bool IsContinuingContextInteraction() const`
- L162 _public prototype_ `float GetDebugBroadPhaseRadius(int32 Index) const;`
- L164 _public function_ `void SetContinuingInteraction(bool bInIsContinuingInteraction)`
- L165 _public function_ `void SetContinuingContextInteraction(bool bInIsContinuingContextInteraction)`
- L166 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L167 _public prototype_ `void SetContinuingProperties(float InPlayingAssetAccumulatedTime, const UObject* InPlayingAsset, bool bInIsPlayingAssetMirrored, const FVector& InPlayingAssetBlendParameters, EPoseSearchInterruptMode InInterruptMode);`
- L171 _private member_ `TObjectPtr<const UObject> PlayingAsset;`
- L172 _private member_ `float PlayingAssetAccumulatedTime = 0.f;`
- L173 _private member_ `bool bIsPlayingAssetMirrored = false;`
- L174 _private member_ `FVector PlayingAssetBlendParameters = FVector::ZeroVector;`
- L175 _private member_ `EPoseSearchInterruptMode InterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;`
- L176 _private member_ `bool bIsContinuingInteraction = false;`
- L177 _private member_ `bool bIsContinuingContextInteraction = false;`
- L178 _private member_ `TArray<int32, TInlineAllocator<PreallocatedRolesNum, TMemStackAllocator<>>> TickPriorities;`
- L181 _private member_ `TArray<float, TInlineAllocator<PreallocatedRolesNum, TMemStackAllocator<>>> DebugBroadPhaseRadius;`
- L182 _private member_ `TArray<float, TInlineAllocator<PreallocatedRolesNum, TMemStackAllocator<>>> BroadPhaseRadiusIncrementOnInteraction;`

#### struct `UE::PoseSearch::FInteractionIsland`  
`struct FInteractionIsland`  
_L194-295_
- desc: Experimental, this feature might be removed without warning, not for production use FInteractionIsland contains ticks functions injected between the interacting actors TickActorComponents (UCharacterMovementComponent, or UCharacterMoverComponent) and PostTickComponent (USkeletalMeshComponent, or UAnimNextComponent) to create a execution threading fence to be able to perform motion matching searches between the involved characters in a thread safe manner. Look at UPoseSearchInteractionSubsystem "Execution model and threading details" for additional information
- L198 _public prototype_ `FInteractionIsland(ULevel* Level, UPoseSearchInteractionSubsystem* Subsystem);`
- L199 _public prototype_ `~FInteractionIsland();`
- L201 _public prototype_ `bool DoSearch_AnyThread(const UObject* AnimContext, FPoseSearchBlueprintResult& Result);`
- L202 _public prototype_ `bool GetResult_AnyThread(const UObject* AnimContext, FPoseSearchBlueprintResult& Result, bool bCompareOwningActors = false);`
- L204 _public function_ `const TArray<UActorComponent*>& GetTickActorComponents() const`
- L205 _public function_ `const TArray<const UObject*>& GetIslandAnimContexts() const`
- L206 _public function_ `const TArray<FInteractionSearchContext>& GetSearchContexts() const`
- L207 _public function_ `const TArray<FInteractionSearchResult>& GetSearchResults() const`
- L209 _public prototype_ `bool IsInitialized() const;`
- L210 _public prototype_ `void AddSearchContext(const FInteractionSearchContext& SearchContext);`
- L211 _public prototype_ `void Uninitialize(bool bValidateTickDependencies);`
- L213 _public prototype_ `bool HasTickDependencies() const;`
- L214 _public prototype_ `void InjectToActor(const UObject* AnimContext, bool bAddTickDependencies);`
- L217 _public prototype_ `void LogTickDependencies() const;`
- L220 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L221 _public prototype_ `void UpdateConstraints(float DeltaTime);`
- L222 _public prototype_ `bool GetConstraint(const UObject* AnimContext, FName SocketName, float& OutDesiredReach, FTransform& OutTransform, bool bCompareOwningActors = false) const;`
- L226 _private prototype_ `static void LogTickDependencies(const TConstArrayView<UActorComponent*> TickActorComponents, int32 InteractionIslandIndex);`
- L227 _private prototype_ `void ValidateTickDependenciesLeaks() const;`
- L230 _private prototype_ `void AddTickDependencies(UActorComponent* TickActorComponent, bool bInIsMainActor);`
- L231 _private prototype_ `void RemoveTickDependencies(bool bValidateTickDependencies);`
- L232 _private prototype_ `static IInteractionIslandDependency* FindCustomDependency(UActorComponent* InTickComponent);`
- L234 _private prototype_ `const FInteractionSearchResult* GetInteractionSearchResult_AnyThread(const UObject* AnimContext, bool bCompareOwningActors, FRole& OutRole) const;`
- L236 _private prototype_ `const UObject* GetMainAnimContext() const;`
- L237 _private prototype_ `const AActor* GetMainActor() const;`
- L246 _private member_ `FPreTickFunction PreTickFunction;`
- L255 _private member_ `FPostTickFunction PostTickFunction;`
- L264 _private member_ `FClosingTickFunction ClosingTickFunction;`
- L266 _private member_ `bool bHasTickDependencies = false;`
- L268 _private member_ `TArray<TObjectPtr<UActorComponent>> TickActorComponents;`
- L270 _private member_ `TArray<TObjectPtr<UActorComponent>> PostClosingTickActorComponents;` — UActorComponent with an ijected tick dependency to the ClosingTickFunction
- L273 _private member_ `TArray<TObjectPtr<const UObject>> IslandAnimContexts;` — all the AnimContext in this island. Each SearchContexts will contain a subset of IslandAnimContexts
- L277 _private member_ `TArray<FInteractionSearchContext> SearchContexts;` — there's one FSearchContext for each search we need to perform (including all the possible roles combinations). Added by UPoseSearchInteractionSubsystem::Tick islands don't get deallocated, so this array once warmed up will not hit the allocator and waste cycles
- L281 _private member_ `TArray<FInteractionSearchResult> SearchResults;` — SearchResults contains only the best results, and it has not necessarly the same cardinality as SearchContexts. usually SearchResults.Num() < SearchContexts.Num() islands don't get deallocated, so this array once warmed up will not hit the allocator and waste cycles
- L282 _private member_ `bool bSearchPerfomed = false;`
- L284 _private member_ `UPoseSearchInteractionSubsystem* InteractionSubsystem = nullptr;`
- L289 _private member_ `FThreadSafeCounter InteractionIslandThreadSafeCounter = 0;`
- L290 _private member_ `FThreadSafeCounter TickFunctionsThreadSafeCounter = 0;`
- L291 _private member_ `bool bPreTickFunctionExecuted = false;`
- L292 _private member_ `bool bPostTickFunctionExecuted = false;`
- L293 _private member_ `bool bClosingTickFunctionExecuted = false;`

#### struct `UE::PoseSearch::FInteractionIsland::FPreTickFunction`  
`struct FPreTickFunction : public FTickFunction`  
_L240-245_
- inherits: `FTickFunction`
- desc: running before main actor animation evaluation
- L242 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L243 _public function_ `virtual FString DiagnosticMessage() override`
- L244 _public member_ `FInteractionIsland* Island = nullptr;`

#### struct `UE::PoseSearch::FInteractionIsland::FPostTickFunction`  
`struct FPostTickFunction : public FTickFunction`  
_L249-254_
- inherits: `FTickFunction`
- desc: running after main actor animation evaluation, and before any NON main actor animation evaluation
- L251 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L252 _public function_ `virtual FString DiagnosticMessage() override`
- L253 _public member_ `FInteractionIsland* Island = nullptr;`

#### struct `UE::PoseSearch::FInteractionIsland::FClosingTickFunction`  
`struct FClosingTickFunction : public FTickFunction`  
_L258-263_
- inherits: `FTickFunction`
- desc: running ALL actors animation evaluation
- L260 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L261 _public function_ `virtual FString DiagnosticMessage() override`
- L262 _public member_ `FInteractionIsland* Island = nullptr;`

#### struct `UE::PoseSearch::IInteractionIslandDependency`  
`struct IInteractionIslandDependency : public IModularFeature`  
_L299-312_
- inherits: `IModularFeature`
- desc: Experimental, this feature might be removed without warning, not for production use Allows systems other than regular actor components to hook into interaction island dependencies
- L301 _public member_ `static inline FName FeatureName = "II`
- L303 _public prototype_ `virtual ~IInteractionIslandDependency() = default;`
- L305 _public prototype_ `virtual bool CanMakeDependency(const UObject* InIslandObject, const UObject* InObject) const = 0;`
- L306 _public prototype_ `virtual const FTickFunction* FindTickFunction(UObject* InObject) const = 0;`
- L308 _public prototype_ `virtual void AddPrerequisite(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const = 0;`
- L309 _public prototype_ `virtual void AddSubsequent(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const = 0;`
- L310 _public prototype_ `virtual void RemovePrerequisite(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const = 0;`
- L311 _public prototype_ `virtual void RemoveSubsequent(UObject* InIslandObject, FTickFunction& InIslandTickFunction, UObject* InObject) const = 0;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PoseSearch` (scope `UE`)
- L24 _typedef_ `typedef TPair<TObjectPtr<AActor>, TObjectPtr<AActor>> FDisabledCollision;` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L26 _typedef_ `typedef TArray<FDisabledCollision> FDisabledCollisions;` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L66 _enumerator_ `enum { InvalidCachedHashForEquivalence = 0 }; uint32 CachedHashForEquivalence = InvalidCachedHashForEquivalence; uint32 CachedContextHashForEquivalence = InvalidCachedHashForEquivalence;` (scope `UE::PoseSearch::FInteractionSearchContextBase::__anondbc8fa0d0103`)
- L187 _typedef_ `typedef TArray<FInteractionSearchContext, TInlineAllocator<PreallocatedSearchesNum, TMemStackAllocator<>>> FInteractionSearchContexts;` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionLibrary.h` (Public)


#### struct `FPoseSearchAnimContextRoles`  
`struct FPoseSearchAnimContextRoles`  
_L13-24_
- reflection: `USTRUCT(Experimental, BlueprintType, Category = "Animation|Pose Search")`
- desc: roles an AnimContext (currently only AnimInstance(s) are supported) can take during a MotionMatchMulti search
- L20 _public member_ `TObjectPtr<UObject> AnimContext = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — @todo: add UAF support, since we currently allow AnimContext of type UAnimInstance @todo: add a UPROPERTY filter to select only UAnimInstance or UUAFComponent
- L23 _public member_ `TArray<FName> Roles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`

#### struct `FPoseSearchMotionMatchMultiQuery`  
`struct FPoseSearchMotionMatchMultiQuery`  
_L30-39_
- reflection: `USTRUCT(Experimental, BlueprintType, Category = "Animation|Pose Search")`
- desc: single query for a MotionMatchMulti search. Database should contain UMultiAnimAsset(s) (for example UPoseSearchInteractionAsset(s)) AnimContextsRoles lists all the AnimContext that could partecipate in interactions and the roles they're willing to take (possible roles are defined in Database->Schema->Skeletons[i].Role)
- L35 _public member_ `TObjectPtr<const UPoseSearchDatabase> Database = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`
- L38 _public member_ `TArray<FPoseSearchAnimContextRoles> AnimContextsRoles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)`

#### class `UPoseSearchInteractionLibrary`  
`class UPoseSearchInteractionLibrary : public UBlueprintFunctionLibrary`  
_L43-112_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Experimental, this feature might be removed without warning, not for production use
- L60 _public prototype_ `static FPoseSearchBlueprintResult MotionMatchInteraction_Pure(TArray<FPoseSearchInteractionAvailability> Availabilities, const UObject* AnimContext, FName PoseHistoryName, bool bValidateResultAgainstAvailabilities = true);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))` — function publishing this character (via its AnimInstance) FPoseSearchInteractionAvailability to the UPoseSearchInteractionSubsystem, FPoseSearchInteractionAvailability represents the character availability to partecipate in an interaction with other characters for the next frame. that means there will always be one frame delay between publiching availabilities and getting a result back from MotionMatchInteraction_Pure! if FPoseSearchBlueprintResult has a valid SelectedAnimation, this will be the animation assigned to this character to partecipate in this interaction. additional interaction properties, like assigned role, SelectedAnimation time, SearchCost, etc can be found within the result ContinuingProperties are used to figure out the continuing pose and bias it accordingly. ContinuingProperties can reference directly the UMultiAnimAsset or any of the roled UMultiAnimAsset::GetAnimationAsset, and the UPoseSearchInteractionSubsystem will figure out the related UMultiAnimAsset PoseHistoryName is the name of the pose history node used for the associated motion matching search if bValidateResultAgainstAvailabilities is true, the result will be invalidated if doesn't respect the new availabilities
- L64 _public prototype_ `static FPoseSearchBlueprintResult MotionMatchInteraction(TArray<FPoseSearchInteractionAvailability> Availabilities, const UObject* AnimContext, FName PoseHistoryName, bool bValidateResultAgainstAvailabilities = true);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))` — BlueprintCallable version of MotionMatchInteraction_Pure
- L71 _public prototype_ `static void CalculateFullAlignedTransforms(const FPoseSearchBlueprintResult& CurrentResult, float TimeOffset, bool bWarpUsingRootBone, TArray<FTransform>& OutFullAlignedTransforms);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))` — this function calculates the mesh space transforms (OutFullAlignedTransforms) the AnimContext(s) should reach within a time of TimeOffset to be consistently aligned to the selected UMultiAnimAsset (CurrentResult.SelectedAnim) at the selected time (CurrentResult.SelectedTime), given the interacting AnimContext(s) transforms (CurrentResult.ActorRootBoneTransforms, CurrentResult.ActorRootTransforms) if bWarpUsingRootBone is true the function will use the AnimContext root bone transforms, otherwise the mesh space transforms
- L75 _public prototype_ `static void CalculateFullAlignedTransform(const FPoseSearchBlueprintResult& CurrentResult, float TimeOffset, bool bWarpUsingRootBone, FTransform& OutFullAlignedTransform);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))` — this function calculates the mesh space transform for the AnimContext assigned the role CurrentResult.Role as CalculateFullAlignedTransforms does for all the AnimContext(s)
- L80 _public prototype_ `static void CalculateNoAlignedTransform(const FPoseSearchBlueprintResult& CurrentResult, float TimeOffset, bool bWarpUsingRootBone, FTransform& OutNoAlignedTransform);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))` — this function calculates the mesh space transform (OutNoAlignedTransform), or root bone transform if bWarpUsingRootBone is true, the AnimContext will reach within a time of TimeOffset, if it continues playing the CurrentResult.SelectedAnim from CurrentResult.SelectedTime forward
- L88 _public prototype_ `static FPoseSearchContinuingProperties GetMontageContinuingProperties(UAnimInstance* AnimInstance);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L91 _public prototype_ `static void GetMotionMatchInteractionConstraint(const UObject* AnimContext, FName SocketName, float& OutDesiredReach, FTransform& OutTransform, bool& IsValid, bool bCompareOwningActors = true);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L98 _public prototype_ `static void MotionMatchMulti( TArray<FPoseSearchMotionMatchMultiQuery> MotionMatchMultiQueries, const FName PoseHistoryName, const FPoseSearchContinuingProperties ContinuingProperties, TArray<FPoseSearchBlueprintResult>& Results);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (AdvancedDisplay = "ContinuingProperties, Future, EventToSearch"))` — function performing all the possible MotionMatching searches between the AnimContexts (eg AnimInstance(s)) defined in MotionMatchMultiQueries and compiled from the valid combination of the AnimContexts allowed Roles. Results will output the best mathing options for all those AnimContexts willing to partecipate in interactions. Users can iterate over Results, and assign the Results[i].SelectedAnim playback to the corresponding GetActor(Results[i])
- L108 _public prototype_ `static void UpdateConstraints(UPARAM(ref) TArray<FPoseSearchConstraint>& InOutConstraints, float DeltaTime, const UMultiAnimAsset* MultiAnimAsset, const TArray<UObject*> AnimContexts, float SelectedTime, bool bIsMirrored, FVector BlendParameters);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search")`
- L111 _public prototype_ `static void GetConstraint(const TArray<FPoseSearchConstraint>& Constraints, FName AnimContextRole, FName SocketName, float& OutDesiredReach, FTransform& OutTransform, bool& IsValid);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionSubsystem.h` (Public)


#### class `UPoseSearchInteractionSubsystem`  
`class UPoseSearchInteractionSubsystem : public UTickableWorldSubsystem`  
_L78-161_
- reflection: `UCLASS(MinimalAPI, Experimental, Category="Animation|Pose Search")`
- inherits: `UTickableWorldSubsystem`
- L83 _public prototype_ `static UPoseSearchInteractionSubsystem* GetSubsystem_AnyThread(const UObject* AnimInstance);`
- L84 _public prototype_ `static UPoseSearchInteractionSubsystem* GetSubsystem_AnyThread(const UWorld* World);`
- L86 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L87 _public prototype_ `virtual void Deinitialize() override;`
- L90 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — it processes FPoseSearchInteractionAvailability(s) and creates/updates FInteractionIsland
- L92 _public prototype_ `virtual TStatId GetStatId() const override;`
- L100 _public prototype_ `void Query_AnyThread(const TArrayView<const FPoseSearchInteractionAvailability> Availabilities, const UObject* AnimContext, FPoseSearchBlueprintResult& Result, FName PoseHistoryName, const UE::PoseSearch::IPoseHistory* PoseHistory, bool bValidateResultAgainstAvailabilities);` — publishing FPoseSearchInteractionAvailability(s) for the requesting character (via AnimContext as UAnimInstance or UAnimNextComponent) and getting the FPoseSearchBlueprintResult from the PREVIOUS Tick update containing the animation to play at what time, and the assigned role to partecipate in the selected interaction. Either a PoseHistoryName or a PoseHistory are required to perform the associated motion matching searches if bValidateResultAgainstAvailabilities is true, the result will be validated against the currently published availabilities, that could differ from the previous frame one for this AnimContext, and discarded if not valid within the context of the new availabilities
- L105 _public prototype_ `void GetResult_AnyThread(const UObject* AnimContext, FPoseSearchBlueprintResult& Result, bool bCompareOwningActors = false);` — use bCompareOwningActors = true in case you're querying the UPoseSearchInteractionSubsystem from a different AnimContext, for example when using this API from a different ABP from a different skeletal mesh component
- L107 _public function_ `TConstArrayView<UE::PoseSearch::FInteractionIsland*> GetInteractionIslands() const`
- L110 _public prototype_ `static void AddReferencedObjects(UObject* This, FReferenceCollector& Collector);` — garbage collection handling
- L112 _public prototype_ `const TConstArrayView<FPoseSearchConstraint> GetConstraints(const UE::PoseSearch::FInteractionSearchContext& SearchContext) const;`
- L116 _public prototype_ `bool GetConstraint(const UObject* AnimContext, FName SocketName, float& OutDesiredReach, FTransform& OutTransform, bool bCompareOwningActors = false);` — use bCompareOwningActors = true in case you're querying the UPoseSearchInteractionSubsystem from a different AnimContext, for example when using this API from a different ABP from a different skeletal mesh component
- L118 _public function_ `TConstArrayView<UE::PoseSearch::FInteractionIsland*> GetIslands() const`
- L120 _public member_ `FOnPoseSearchInteractionEvent OnInteractionStartedDelegate;`
- L121 _public member_ `FOnPoseSearchInteractionEvent OnInteractionContinuingDelegate;`
- L122 _public member_ `FOnPoseSearchInteractionEvent OnInteractionEndedDelegate;`
- L129 _private prototype_ `UE::PoseSearch::FInteractionIsland& CreateIsland();`
- L130 _private prototype_ `UE::PoseSearch::FInteractionIsland& GetAvailableIsland();`
- L132 _private prototype_ `void DestroyIsland(int32 Index);`
- L133 _private prototype_ `void DestroyAllIslands();`
- L134 _private prototype_ `void RegenerateAllIslands(float DeltaSeconds);`
- L135 _private prototype_ `bool ShouldRegenerateAllIslands();`
- L138 _private prototype_ `bool ValidateAllIslands() const;`
- L141 _private prototype_ `UE::PoseSearch::FInteractionIsland* FindIsland(const UObject* AnimContext, bool bCompareOwningActors = false);`
- L144 _private prototype_ `void DebugDrawIslands() const;`
- L145 _private prototype_ `void DebugLogTickDependencies() const;`
- L148 _private prototype_ `void AddAvailabilities(const TArrayView<const FPoseSearchInteractionAvailability> Availabilities, const UObject* AnimContext, FName PoseHistoryName, const UE::PoseSearch::IPoseHistory* PoseHistory);`
- L149 _private prototype_ `void GenerateAnimContextInfosAndTagToDatabases(UE::PoseSearch::FAnimContextInfos& AnimContextInfos, UE::PoseSearch::FTagToDatabases& TagToDatabases) const;`
- L150 _private prototype_ `void GenerateSearchContexts(float DeltaSeconds, UE::PoseSearch::FInteractionSearchContexts& SearchContexts) const;`
- L153 _private member_ `TArray<UE::PoseSearch::FInteractionAnimContextAvailabilities> AnimContextsAvailabilitiesBuffer;` — it could contain duplicated availabilities
- L154 _private member_ `FThreadSafeCounter AnimContextsAvailabilitiesIndex = 0;`
- L155 _private member_ `int32 AnimContextsAvailabilitiesNum = 0;`
- L158 _private member_ `TArray<UE::PoseSearch::FInteractionIsland*> Islands;` — array of groups of characters that needs to be anaylzed together for possible interactions
- L160 _private member_ `UE::PoseSearch::FValidInteractionSearches ValidInteractionSearches;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API POSESEARCH_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PoseSearch` (scope `UE`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPoseSearchInteractionEvent, const UE::PoseSearch::FValidInteractionSearch&);`
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPoseSearchInteractionEvent, const UE::PoseSearch::FValidInteractionSearch&);`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PoseSearch` (scope `UE`)
- L14 _prototype_ `int32 GetRoleIndex(const UMultiAnimAsset* MultiAnimAsset, const FRole& Role);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L17 _prototype_ `FRoleToIndex MakeRoleToIndex(const UMultiAnimAsset* MultiAnimAsset);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L20 _prototype_ `void CalculateFullAlignedTransforms(const FPoseSearchBlueprintResult& Result, float Time, float TimeOffset, bool bWarpUsingRootBone, TArrayView<FTransform> OutFullAlignedTransforms);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L23 _prototype_ `FTransform CalculateDeltaAlignment(const FTransform& MeshWithoutOffset, const FTransform& MeshWithOffset, const FTransform& FullAlignedTransform, float WarpingRotationRatio, float WarpingTranslationRatio);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L27 _function_ `template <typename EvaluateCombinationType> static void GenerateCombinationsRecursive(int32 DataCardinality, int32 DataIndex, TArray<int32, TInlineAllocator<PreallocatedRolesNum>>& Combination, int32 CombinationIndex, EvaluateCombinationType EvaluateCombination)` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L53 _function_ `template <typename EvaluateCombinationType> static void GenerateCombinations(int32 DataCardinality, int32 CombinationCardinality, EvaluateCombinationType EvaluateCombination)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchInteractionValidator.h` (Public)


#### struct `UE::PoseSearch::FInteractionValidator`  
`struct FInteractionValidator`  
_L15-23_
- desc: Experimental, this feature might be removed without warning, not for production use
- L17 _public prototype_ `explicit FInteractionValidator(const UObject* AnimContext);`
- L18 _public prototype_ `explicit FInteractionValidator(FInteractionIsland* InValidatingIsland);`
- L19 _public prototype_ `~FInteractionValidator();`
- L21 _public member_ `const UObject* ValidatingAnimContext = nullptr;`
- L22 _public member_ `FInteractionIsland* ValidatingIsland = nullptr;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API POSESEARCH_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace PoseSearch` (scope `UE`)
- L25 _macro_ `#define CheckInteractionThreadSafety(ValidationContext) const FInteractionValidator InteractionValidator(ValidationContext)`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchLibrary.h` (Public)


#### enum `EPoseSearchInterruptMode`  
`enum class EPoseSearchInterruptMode : uint8`  
_L35-53_
- reflection: `UENUM(BlueprintType)`
- L38 _public enumerator_ `DoNotInterrupt` — continuing pose search will be performed if valid
- L41 _public enumerator_ `InterruptOnDatabaseChange` — continuing pose search will be interrupted if its database is not listed in the searchable databases
- L45 _public enumerator_ `InterruptOnDatabaseChangeAndInvalidateContinuingPose` — continuing pose search will be interrupted if its database is not listed in the searchable databases, and continuing pose will be invalidated (forcing the schema to use pose history to build the query)
- L48 _public enumerator_ `ForceInterrupt` — continuing pose search will always be interrupted
- L52 _public enumerator_ `ForceInterruptAndInvalidateContinuingPose` — continuing pose search will always be interrupted and continuing pose will be invalidated (forcing the schema to use pose history to build the query)

#### struct `FMotionMatchingState`  
`struct FMotionMatchingState`  
_L56-82_
- reflection: `USTRUCT()`
- L61 _public prototype_ `FMotionMatchingState() = default;`
- L62 _public prototype_ `FMotionMatchingState(const FMotionMatchingState& Other) = default;`
- L63 _public prototype_ `FMotionMatchingState(FMotionMatchingState&& Other) = default;`
- L64 _public prototype_ `FMotionMatchingState& operator=(const FMotionMatchingState& Other) = default;`
- L65 _public prototype_ `FMotionMatchingState& operator=(FMotionMatchingState&& Other) = default;`
- L66 _public prototype_ `~FMotionMatchingState() = default;`
- L70 _public prototype_ `void Reset();` — Reset the state to a default state using the current Database
- L72 _public prototype_ `FVector GetEstimatedFutureRootMotionVelocity() const;`
- L75 _public member_ `FPoseSearchBlueprintResult SearchResult;` — `UPROPERTY(Transient)`
- L78 _public member_ `float ElapsedPoseSearchTime = 0.f;` — Time since the last pose jump (real time in seconds, not a normalized time)
- L81 _public member_ `UE::PoseSearch::FPoseIndicesHistory PoseIndicesHistory;` — `UE_DEPRECATED(5.7, "this property has been moved into the pose history. Use IPoseHistory::GetPoseIndicesHistory to access it")`

#### struct `FPoseSearchFutureProperties`  
`struct FPoseSearchFutureProperties`  
_L85-100_
- reflection: `USTRUCT(Experimental, BlueprintType, Category="Animation|Pose Search")`
- L91 _public member_ `TObjectPtr<const UObject> Animation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Animation to play (it'll start at AnimationTime seconds)
- L95 _public member_ `float AnimationTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Start time for Animation
- L99 _public member_ `float IntervalTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=State)` — Interval time before playing Animation

#### struct `FPoseSearchContinuingProperties`  
`struct FPoseSearchContinuingProperties`  
_L103-138_
- reflection: `USTRUCT(Experimental, BlueprintType, Category="Animation|Pose Search")`
- L109 _public member_ `TObjectPtr<const UObject> PlayingAsset = nullptr;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)` — Currently playing animation
- L113 _public member_ `float PlayingAssetAccumulatedTime = 0.f;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)` — Currently playing animation accumulated time
- L116 _public member_ `bool bIsPlayingAssetMirrored = false;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)`
- L120 _public member_ `FVector PlayingAssetBlendParameters = FVector::ZeroVector;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — PlayingAsset associated BlendParameters (if PlayingAsset is a UBlendSpace)
- L123 _public member_ `EPoseSearchInterruptMode InterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)`
- L126 _public member_ `bool bIsContinuingInteraction = false;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)`
- L129 _public member_ `bool bIsContinuingContextInteraction = false;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)`
- L134 _public member_ `TObjectPtr<const UPoseSearchDatabase> PlayingAssetDatabase = nullptr;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=State)` — database where the PlayingAsset was originally from (optional property, used to provide an additional database to search for the continuing pose associated to PlayingAsset)
- L137 _public prototype_ `void InitFrom(const FPoseSearchBlueprintResult& SearchResult, EPoseSearchInterruptMode InInterruptMode);` — Experimental, this feature might be removed without warning, not for production use

#### class `UPoseSearchLibrary`  
`class UPoseSearchLibrary : public UBlueprintFunctionLibrary`  
_L141-303_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L148 _private prototype_ `static void TraceMotionMatching( UE::PoseSearch::FSearchContext& SearchContext, const UE::PoseSearch::FSearchResult& SearchResult, float ElapsedPoseSearchTime, float DeltaTime, bool bSearch, float WantedPlayRate, EPoseSearchInterruptMode InterruptMode);` — deprecate in favor of TraceMotionMatching using FSearchResults once we settle on FSearchResults API signatures
- L158 _private prototype_ `static void TraceMotionMatching( UE::PoseSearch::FSearchContext& SearchContext, const UE::PoseSearch::FSearchResults& SearchResults, float ElapsedPoseSearchTime, float WantedPlayRate, EPoseSearchInterruptMode InterruptMode);` — Experimental, this feature might be removed without warning, not for production use
- L185 _public prototype_ `static void UpdateMotionMatchingState( FChooserEvaluationContext* AnimContext, const UE::PoseSearch::IPoseHistory* PoseHistory, const TConstArrayView<TObjectPtr<const UPoseSearchDatabase>> Databases, float DeltaTime, const FFloatInterval& PoseJumpThresholdTime, float PoseReselectHistory, float SearchThrottleTime, const FFloatInterval& PlayRate, FMotionMatchingState& InOutMotionMatchingState, EPoseSearchInterruptMode InterruptMode, bool bShouldUseCachedChannelData, bool bDebugDrawQuery = false, bool bDebugDrawCurResult = false, const FPoseSearchEvent& EventToSearch = FPoseSearchEvent());` — `UE_DEPRECATED(5.7, "Use MotionMatch API instead")` — Implementation of the core motion matching algorithm @param AnimContext					Input animation context, either UAnimInstance or UAnimNextComponent @param PoseHistory					Input IPoseHistory, used to gather historical information about trajectory and bone transforms @param Databases						Input array of databases to search @param DeltaTime						Input DeltaTime @param PoseJumpThresholdTime			Input don't jump to poses of the same segment that are within the interval this many seconds away from the continuing pose. @param PoseReselectHistory			Input prevent re-selection of poses that have been selected previously within this much time (in seconds) in the past. This is across all animation segments that have been selected within this time range. @param SearchThrottleTime				Input minimum amount of time to wait between searching for a new pose segment. It allows users to define how often the system searches, default for locomotion is searching every update, but you may only want to search once for other situations, like jump. @param PlayRate						Input effective range of play rate that can be applied to the animations to account for discrepancies in estimated velocity between the movement modeland the animation. @param InOutMotionMatchingState		Input/Output encapsulated motion matching algorithm and state @param InterruptMode					Input continuing pose search interrupt mode @param bShouldUseCachedChannelData	Input if true, motion matching will try to reuse the continuing pose channels fe
- L213 _public prototype_ `static void MotionMatch( UAnimInstance* AnimInstance, TArray<UObject*> AssetsToSearch, const FName PoseHistoryName, const FPoseSearchContinuingProperties ContinuingProperties, const FPoseSearchFutureProperties Future, FPoseSearchBlueprintResult& Result);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe, AdvancedDisplay = "ContinuingProperties, Future", Keywords = "PoseMatch"))` — Implementation of the core motion matching algorithm @param AnimInstance					Input animation instance @param AssetsToSearch					Input assets to search (UPoseSearchDatabase or any animation asset containing UAnimNotifyState_PoseSearchBranchIn) @param PoseHistoryName				Input tag of the associated PoseSearchHistoryCollector node in the anim graph @param ContinuingProperties			Input struct specyfying the currently playing animation to be able to bias the search in selecting the continuing pose @param Future							Input future properties to match (animation / start time / time offset) @param SelectedAnimation				Output selected animation from the Database asset @param Result							Output FPoseSearchBlueprintResult with the search result
- L222 _public prototype_ `static UE::PoseSearch::FSearchResult MotionMatch( const TArrayView<const UObject*> AnimContexts, const TArrayView<const UE::PoseSearch::FRole> Roles, const TArrayView<const UE::PoseSearch::IPoseHistory*> PoseHistories, const TArrayView<const UObject*> AssetsToSearch, const FPoseSearchContinuingProperties& ContinuingProperties, const FPoseSearchFutureProperties& Future, const FPoseSearchEvent& EventToSearch);` — deprecate in favor of MotionMatch with the FSearchResults parameter once we settle on FSearchResults API signatures
- L282 _public prototype_ `static const FAnimNode_PoseSearchHistoryCollector_Base* FindPoseHistoryNode( const FName PoseHistoryName, const UAnimInstance* AnimInstance);`
- L287 _public prototype_ `static void OverridePoseHistoryFromOwningMesh(UAnimInstance* AnimInstance, const FName PoseHistoryName);` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L290 _public prototype_ `static void IsAnimationAssetLooping(const UObject* Asset, bool& bIsAssetLooping);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L293 _public prototype_ `static void GetDatabaseTags(const UPoseSearchDatabase* Database, TArray<FName>& Tags);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L296 _public prototype_ `static void ClearPoseSearchDatabasesManagement();` — `UFUNCTION(Experimental, BlueprintCallable, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L299 _public prototype_ `static const AActor* GetActor(const FPoseSearchBlueprintResult& Result);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`
- L302 _public prototype_ `static const AActor* GetActorForRole(const FPoseSearchBlueprintResult& Result, const FName& Role);` — `UFUNCTION(Experimental, BlueprintPure, Category = "Animation|Pose Search", meta = (BlueprintThreadSafe))`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API POSESEARCH_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace PoseSearch` (scope `UE`)
- L28 _prototype_ `FRole GetCommonDefaultRole(const TConstArrayView<TObjectPtr<const UPoseSearchDatabase>> Databases);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use
- L30 _prototype_ `float CalculateWantedPlayRate(const FSearchResult& SearchResult, const FSearchContext& SearchContext, const FFloatInterval& PlayRate, float TrajectorySpeedMultiplier, const FPoseSearchEvent& EventToSearch);` (scope `UE::PoseSearch`) — Experimental, this feature might be removed without warning, not for production use

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchMirrorDataCache.h` (Public)


#### struct `UE::PoseSearch::FMirrorDataCache`  
`struct FMirrorDataCache`  
_L17-43_
- desc: @todo: make a memstack allocator version of FMirrorDataCache
- L19 _public prototype_ `FMirrorDataCache();`
- L21 _public prototype_ `FMirrorDataCache(const UMirrorDataTable* InMirrorDataTable);` — fast initialization to mirror only the root bone
- L22 _public prototype_ `FMirrorDataCache(const UMirrorDataTable* InMirrorDataTable, const FBoneContainer& BoneContainer);`
- L25 _public prototype_ `void Init(const UMirrorDataTable* InMirrorDataTable);` — fast initialization to mirror only the root bone
- L26 _public prototype_ `void Init(const UMirrorDataTable* InMirrorDataTable, const FBoneContainer& BoneContainer);`
- L27 _public prototype_ `void Reset();`
- L29 _public prototype_ `FTransform MirrorTransform(const FTransform& InTransform) const;`
- L30 _public prototype_ `void MirrorPose(FCompactPose& Pose) const;`
- L31 _public function_ `const UMirrorDataTable* GetMirrorDataTable() const`
- L35 _private member_ `TWeakObjectPtr<const UMirrorDataTable> MirrorDataTable;` — Mirror data table pointer copied from Schema for convenience
- L38 _private member_ `TCustomBoneIndexArray<FCompactPoseBoneIndex, FCompactPoseBoneIndex> CompactPoseMirrorBones;` — Compact pose format of Mirror Bone Map
- L42 _private member_ `TCustomBoneIndexArray<FQuat, FCompactPoseBoneIndex> ComponentSpaceRefRotations;` — Pre-calculated component space rotations of reference pose, which allows mirror to work with any joint orientation Only initialized and used when a mirroring table is specified

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API POSESEARCH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PoseSearch` (scope `UE`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchNormalizationSet.h` (Public)


#### class `UPoseSearchNormalizationSet`  
`class UPoseSearchNormalizationSet : public UDataAsset`  
_L17-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Animation|Pose Search", meta = (DisplayName = "Pose Search Normalization Set"))`
- inherits: `UDataAsset`
- desc: Data asset used to allow multiple Pose Search Databases to be normalized together.
- L23 _public member_ `TArray<TObjectPtr<const UPoseSearchDatabase>> Databases;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NormalizationSet")`
- L25 _public prototype_ `void AddUniqueDatabases(TArray<const UPoseSearchDatabase*>& UniqueDatabases) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchResult.h` (Public)


#### struct `UE::PoseSearch::FDatabasePoseIdx`  
`struct FDatabasePoseIdx`  
_L22-39_
- L25 _public member_ `int32 PoseIdx = INDEX_NONE;` — pose index from Database associated to this search result
- L28 _public member_ `TWeakObjectPtr<const UPoseSearchDatabase> Database;` — database associated to this search result. Poses are derived data stored in Database->GetSearchIndex()
- L30 _public prototype_ `FDatabasePoseIdx() = default;`
- L31 _public function_ `bool IsValid() const`
- L32 _public function_ `bool operator==(const FDatabasePoseIdx& Other) const`
- L34 _public prototype_ `const FSearchIndexAsset* GetSearchIndexAsset(bool bMandatory = false) const;`
- L36 _public prototype_ `const UAnimationAsset* GetCurrentResultAnimationAsset() const;` — Experimental, this feature might be removed without warning, not for production use
- L38 _public prototype_ `const UAnimationAsset* GetCurrentResultAnimationAsset(const FRole& Role) const;` — Experimental, this feature might be removed without warning, not for production use

#### struct `UE::PoseSearch::FSearchResult`  
`struct FSearchResult : FDatabasePoseIdx`  
_L41-119_
- inherits: `FDatabasePoseIdx`
- L44 _public member_ `FPoseSearchCost PoseCost;` — best cost of the currently selected PoseIdx (it could be equal to ContinuingPoseCost)
- L49 _public member_ `int32 EventPoseIdx = INDEX_NONE;` — Experimental, this feature might be removed without warning, not for production use if this search result is from an event search, EventPoseIdx is the pose index at event time from Database associated to this search result if it's not an event search result EventPoseIdx is INDEX_NONE
- L54 _public member_ `float AssetTime = MAX_flt;` — `UE_DEPRECATED(5.7, "AssetTime will be made private. Use GetAssetTime and SetAssetTime instead")` — time of the associated GetSearchIndexAsset from this search. During continuing pose searches, AssetTime is resynchronized via UpdateWithNormalizedTime or UpdateWithRealTime, so it's not precisely the quantized time associated to PoseIdx
- L57 _public member_ `bool bIsContinuingPoseSearch = false;` — true if the search result is from a continuing pose search
- L61 _public member_ `FPoseSearchCost BruteForcePoseCost;` — debug information related to the brute force search, to be able to compare it versus a kdtree/vptree search
- L62 _public member_ `int32 BestPosePos = 0;`
- L66 _public prototype_ `FSearchResult() = default;`
- L67 _public prototype_ `FSearchResult(const FSearchResult& Other) = default;`
- L68 _public prototype_ `FSearchResult(FSearchResult&& Other) = default;`
- L69 _public prototype_ `FSearchResult& operator=(const FSearchResult& Other) = default;`
- L70 _public prototype_ `FSearchResult& operator=(FSearchResult&& Other) = default;`
- L72 _public function_ `static bool IsAssetTimeValid(float AssetTime)`
- L73 _public function_ `bool IsAssetTimeValid() const`
- L74 _public function_ `float GetAssetTime() const`
- L75 _public function_ `void SetAssetTime(float InAssetTime)`
- L82 _public prototype_ `void UpdateWithNormalizedTime(float NormalizedTime);` — Experimental, this feature might be removed without warning, not for production use Attempts to set the internal state to match the provided asset time including updating the internal DbPoseIdx. If the provided asset time is out of bounds for the currently playing asset then this function will reset the state back to the default state.
- L85 _public prototype_ `void UpdateWithRealTime(float RealTime);` — Experimental, this feature might be removed without warning, not for production use
- L88 _public prototype_ `bool DebugValidate() const;` — Experimental, this feature might be removed without warning, not for production use
- L91 _public function_ `bool IsEventSearchResult() const` — Experimental, this feature might be removed without warning, not for production use
- L98 _public prototype_ `bool IsEventSearchFromTag(const FGameplayTag& EventTag) const;` — Experimental, this feature might be removed without warning, not for production use returns true if EventPoseIdx is from the input EventTag
- L101 _public prototype_ `float CalculateTimeToEvent() const;` — Experimental, this feature might be removed without warning, not for production use
- L103 _public function_ `void Reset()`
- L105 _public function_ `bool operator==(const FSearchResult& Other) const`
- L118 _public prototype_ `void InitFrom(const FPoseSearchBlueprintResult& BlueprintResult);` — Experimental, this feature might be removed without warning, not for production use

#### struct `UE::PoseSearch::FSearchResults`  
`struct FSearchResults`  
_L122-151_
- desc: Experimental, this feature might be removed without warning, not for production use
- L124 _public function_ `FSearchResults() : UpdateWith([](const FSearchResult& SearchResult) {}) , FinalizeResults([]() {}) , GetBestResult([]() { return FSearchResult(); }) , ShouldPerformSearch([](float) { return true; }) , IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L125 _public function_ `: UpdateWith([](const FSearchResult& SearchResult) {}) , FinalizeResults([]() {}) , GetBestResult([]() { return FSearchResult(); }) , ShouldPerformSearch([](float) { return true; }) , IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L126 _public function_ `, FinalizeResults([]() {}) , GetBestResult([]() { return FSearchResult(); }) , ShouldPerformSearch([](float) { return true; }) , IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L127 _public function_ `, GetBestResult([]() { return FSearchResult(); }) , ShouldPerformSearch([](float) { return true; }) , IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L128 _public function_ `, ShouldPerformSearch([](float) { return true; }) , IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L129 _public function_ `, IterateOverSearchResults([](const TFunctionRef<bool(FSearchResult& SearchResult)>) { return true; })`
- L133 _public prototype_ `virtual ~FSearchResults() = default;`
- L135 _public prototype_ `FSearchResults(const FSearchResults& Other) = delete;`
- L136 _public prototype_ `FSearchResults(FSearchResult&& Other) = delete;`
- L137 _public prototype_ `FSearchResults& operator=(const FSearchResults& Other) = delete;`
- L138 _public prototype_ `FSearchResults& operator=(FSearchResults&& Other) = delete;`
- L140 _public member_ `TFunction<void(const FSearchResult& SearchResult)> UpdateWith;`
- L141 _public member_ `TFunction<void()> FinalizeResults;`
- L142 _public member_ `TFunction<FSearchResult()> GetBestResult;`
- L146 _public member_ `TFunction<bool(float)> ShouldPerformSearch;` — every search will ask FSearchResults if it should perform the search, knowing that its minimum cost will be SearchMinimumCost: it's up to this method to perform early out optimizations if the holded results are already good enough fo skip the search
- L150 _public member_ `TFunction<bool(const TFunctionRef<bool(FSearchResult& SearchResult)>)> IterateOverSearchResults;` — calls IterateOverSearchResultsFunction for each FSearchResult this FSearchResults is holding is IterateOverSearchResultsFunction returns true, the iteration will stop and IterateOverSearchResults will return true otherwise will return false (useful to implement contains / find methods)

#### struct `UE::PoseSearch::FSearchResults_Single`  
`struct FSearchResults_Single : public FSearchResults`  
_L154-160_
- inherits: `FSearchResults`
- desc: Experimental, this feature might be removed without warning, not for production use
- L156 _public prototype_ `FSearchResults_Single();`
- L159 _private member_ `FSearchResult SingleSearchResult;`

#### struct `UE::PoseSearch::FSearchResults_Multi`  
`struct FSearchResults_Multi : public FSearchResults`  
_L163-172_
- inherits: `FSearchResults`
- desc: Experimental, this feature might be removed without warning, not for production use
- L165 _public prototype_ `explicit FSearchResults_Multi(int32 InMaxNumberOfWantedResults = 1);`
- L170 _private member_ `TArray<FSearchResult, TInlineAllocator<PreallocatedSearchesNum, TMemStackAllocator<>>> SearchResults;` — @todo: evaluate a max heap instead (using AlgoImpl::HeapSiftUp / AlgoImpl::HeapSiftDown) SearchResults[0] is the best result (lowest FSearchResult::PoseCost), SearchResults.Last() is the worst result (higher FSearchResult::PoseCost)
- L171 _private member_ `int32 MaxNumberOfWantedResults = 1;`

#### struct `UE::PoseSearch::FSearchResults_AssetBests`  
`struct FSearchResults_AssetBests : public FSearchResults`  
_L175-188_
- inherits: `FSearchResults`
- desc: Experimental, this feature might be removed without warning, not for production use
- L177 _public prototype_ `FSearchResults_AssetBests();`
- L178 _public prototype_ `const FSearchResult* FindSearchResultFor(const UPoseSearchDatabase* Database, int32 SourceAssetIdx) const;`
- L181 _public prototype_ `void Shrink(int32 MaxNumResults);` — shrinks FSearchResults_AssetBests down to MaxNumResults preserving the best results (the ones with less cost)
- L183 _public typedef_ `typedef TMap<int32, FSearchResult, TInlineSetAllocator<16, TMemStackSetAllocator<>>> FSourceAssetIdxToBestSearchResult;`
- L184 _public typedef_ `typedef TMap<const UPoseSearchDatabase*, FSourceAssetIdxToBestSearchResult, TInlineSetAllocator<4, TMemStackSetAllocator<>>> FPerDatabaseSourceAssetIdxToBestSearchResult;`
- L187 _private member_ `FPerDatabaseSourceAssetIdxToBestSearchResult PerDatabaseSourceAssetIdxToBestSearchResult;`

#### struct `FPoseSearchBlueprintResult`  
`struct FPoseSearchBlueprintResult`  
_L193-268_
- reflection: `USTRUCT(BlueprintType, Category="Animation|Pose Search")`
- L199 _public member_ `TObjectPtr<UObject> SelectedAnim = nullptr;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — selected animation selected by the motion matching alghoritm that matches the query (trajectory + historical pose) the best
- L203 _public member_ `float SelectedTime = 0.f;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim associated time (to have the best result out of the motion matchign selection, play the SelectedAnim at the SelectedTime)
- L207 _public member_ `bool bIsContinuingPoseSearch = false;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim at SelectedTime is from the motion matching continuing pose search
- L211 _public member_ `float WantedPlayRate = 1.f;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim suggested play rate (it's usually calculated by estimating the ratio between the trajectory speed in the query against the speed in the result)
- L215 _public member_ `bool bLoop = false;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim associated looping state
- L219 _public member_ `bool bIsMirrored = false;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim associated mirror state
- L223 _public member_ `FVector BlendParameters = FVector::ZeroVector;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — SelectedAnim associated BlendParameters (if SelectedAnim is a UBlendSpace)
- L227 _public member_ `TObjectPtr<const UPoseSearchDatabase> SelectedDatabase = nullptr;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — database containig the SelectedAnim
- L231 _public member_ `float SearchCost = MAX_flt;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category=State)` — associated motion matching search cost for this result (how bad the SelectedAnim at SelectedTime etc looks in comparison to the query. The bigger the number, the more different the two are)
- L235 _public member_ `bool bIsInteraction = false;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — bIsInteraction is true if this is a result from a motion matching interaction search
- L239 _public member_ `FName Role = UE::PoseSearch::DefaultRole;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — assigned role to this character. If this result is from a motion matched interaction, every interacting Actors will be assigned a different Role
- L244 _public member_ `int32 RoleIndex = INDEX_NONE;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — assigned role index to this character. If this result is from a motion matched interaction, every interacting Actors will be assigned a different Role index. It can be used to find this actor properies from ActorRootTransforms, ActorRootBoneTransforms, and AnimContexts
- L248 _public member_ `TArray<FTransform> ActorRootTransforms;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — cached actors root transforms for all the roles in SelectedAnim (as UMultiAnimAsset). For all the optional missing roles (where the associated AnimContexts[i] is null), the ActorRootTransform will be identity
- L252 _public member_ `TArray<FTransform> ActorRootBoneTransforms;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — cached actors root bone transforms for all the roles in SelectedAnim (as UMultiAnimAsset). For all the optional missing roles (where the associated AnimContexts[i] is null), the ActorRootBoneTransform will be identity
- L258 _public member_ `TArray<TObjectPtr<const UObject>> AnimContexts;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Experimental|Interaction", meta = (Experimental))` — Experimental, this feature might be removed without warning, not for production use AnimContexts involved in this interaction for all the roles in SelectedAnim (as UMultiAnimAsset). If the role is missing because optional the AnimContext will be null BE CAREFUL HOW YOU USE THEM! since accessing data from other actors without proper tick dependencies leads to threading problems!
- L261 _public prototype_ `bool InitFrom(const UE::PoseSearch::FSearchResult& SearchResult, float InWantedPlayRate);` — Experimental, this feature might be removed without warning, not for production use
- L264 _public prototype_ `UAnimationAsset* GetAnimationAssetForRole();` — Experimental, this feature might be removed without warning, not for production use
- L267 _public prototype_ `bool operator==(const FPoseSearchBlueprintResult& Other) const;` — Experimental, this feature might be removed without warning, not for production use

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPoseSearchBlueprintResult> : public TStructOpsTypeTraitsBase2<FPoseSearchBlueprintResult>`  
_L271-274_
- inherits: `TStructOpsTypeTraitsBase2<FPoseSearchBlueprintResult>`
- desc: Experimental, this feature might be removed without warning, not for production use

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L273-273_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace PoseSearch` (scope `UE`)
- L273 _enumerator_ `enum { WithIdenticalViaEquality = true };` (scope `TStructOpsTypeTraits::__anon6e26f3910603`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchRole.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PoseSearch` (scope `UE`)
- L9 _typedef_ `using FRole = FName;` (scope `UE::PoseSearch`)
- L10 _variable_ `static const FRole DefaultRole = FRole();` (scope `UE::PoseSearch`)
- L13 _typedef_ `using FRoleToIndex = TMap<FRole, int32, TInlineSetAllocator<PreallocatedRolesNum >>;` (scope `UE::PoseSearch`) — todo: enabling TMemStackSetAllocator?
- L14 _typedef_ `using FRoleToIndexPair = TPair<FRole, int32>;` (scope `UE::PoseSearch`)
- L16 _function_ `static bool IsValid(const FRoleToIndex& RoleToIndex)` (scope `UE::PoseSearch`)
- L37 _function_ `static FRoleToIndex MakeRoleToIndex(const TConstArrayView<FRole> Roles)` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchSchema.h` (Public)


#### enum `EPoseSearchDataPreprocessor`  
`enum class EPoseSearchDataPreprocessor : int32`  
_L16-31_
- reflection: `UENUM()`
- L19 _public enumerator_ `None` — The data will be left untouched.
- L22 _public enumerator_ `Normalize` — The data will be normalized against its deviation, and the user weights will be normalized to be a unitary vector.
- L26 _public enumerator_ `NormalizeOnlyByDeviation UMETA(DisplayName = "Normalize Only By Deviation (Experimental)")` — The data will be normalized against its deviation Experimental, this feature might be removed without warning, not for production use
- L30 _public enumerator_ `NormalizeWithCommonSchema UMETA(DisplayName = "Normalize With Common Schema (Experimental)")` — same behavior as Normalize, but it'll index all the databases in the normalization set with the same schema Experimental, this feature might be removed without warning, not for production use

#### struct `FPoseSearchRoledSkeleton`  
`struct FPoseSearchRoledSkeleton`  
_L35-60_
- reflection: `USTRUCT()`
- L40 _public prototype_ `FPoseSearchRoledSkeleton() = default;` — Declared to be able to disable deprecation warnings
- L41 _public prototype_ `FPoseSearchRoledSkeleton(const FPoseSearchRoledSkeleton&);`
- L42 _public prototype_ `FPoseSearchRoledSkeleton& operator=(const FPoseSearchRoledSkeleton&);`
- L46 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Category = "Schema")` — Skeleton Reference for Motion Matching Database assets. Must be set to a compatible skeleton to the animation data in the database.
- L50 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Category = "Schema")` — Setting up and assigning a mirror data table will allow all your assets in your database to access the mirrored version of the data. This is required for mirroring to work with Motion Matching.
- L53 _public member_ `FName Role;` — `UPROPERTY(EditAnywhere, Category = "Schema")`
- L56 _public member_ `TArray<FBoneReference> BoneReferences;` — `UPROPERTY(Transient)`
- L59 _public member_ `TArray<FName> RequiredCurves;` — `UPROPERTY(Transient)`

#### class `UPoseSearchSchema`  
`class UPoseSearchSchema : public UDataAsset`  
_L66-219_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "Animation|Pose Search", meta = (DisplayName = "Pose Search Schema"), CollapseCategories)`
- inherits: `UDataAsset`
- desc: Specifies the format of a pose search index. At runtime, queries are built according to the schema for searching.
- L73 _public member_ `int32 SampleRate = 30;` — `UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayPriority = 3, ClampMin = "1", ClampMax = "240"))` — The update rate at which we sample the animation data in the database. The higher the SampleRate the more refined your searches will be, but the more memory will be required
- L77 _private member_ `TArray<FPoseSearchRoledSkeleton> Skeletons;` — `UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayPriority = 0))`
- L81 _private member_ `TArray<TObjectPtr<UPoseSearchFeatureChannel>> Channels;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Schema")` — Channels itemize the cost breakdown of the Schema in simpler parts such as position or velocity of a bones, or phase of limbs. The total cost of a query against an indexed database pose will be the sum of the combined channel costs
- L85 _private member_ `TArray<TObjectPtr<UPoseSearchFeatureChannel>> FinalizedChannels;` — `UPROPERTY(Transient)` — FinalizedChannels gets populated with UPoseSearchFeatureChannel(s) from Channels and additional injected ones during the Finalize.
- L91 _public member_ `EPoseSearchDataPreprocessor DataPreprocessor = EPoseSearchDataPreprocessor::Normalize;` — `UPROPERTY(EditAnywhere, Category = "Schema", meta = (DisplayPriority = 2))` — Type of operation performed to the full pose features dataset
- L95 _public member_ `int32 SchemaCardinality = 0;` — `UPROPERTY(Transient)`
- L100 _public member_ `int32 NumberOfPermutations = 1;` — `UPROPERTY(EditAnywhere, Category = "Permutations", meta = (ClampMin = "1"))` — How many times the animation assets of the database using this schema will be indexed.
- L104 _public member_ `int32 PermutationsSampleRate = 30;` — `UPROPERTY(EditAnywhere, Category = "Permutations", meta = (ClampMin = "1", ClampMax = "240", EditCondition = "NumberOfPermutations > 1", EditConditionHides))` — Delta time between every permutation indexing.
- L109 _public member_ `float PermutationsTimeOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Permutations")` — Starting offset of the "PermutationTime" from the "SamplingTime" of the first permutation. subsequent permutations will have PermutationTime = SamplingTime + PermutationsTimeOffset + PermutationIndex / PermutationsSampleRate.
- L114 _public member_ `bool bAddDataPadding = false;` — `UPROPERTY(EditAnywhere, Category = "Performance")` — if true a padding channel will be added to make sure the data is 16 bytes (aligned) and padded, to facilitate performance improvements at cost of eventual additional memory
- L120 _public member_ `bool bInjectAdditionalDebugChannels = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — If bInjectAdditionalDebugChannels is true, channels will be asked to inject additional channels into this schema. the original intent is to add UPoseSearchFeatureChannel_Position(s) to help with the complexity of the debug drawing (the database will have all the necessary positions to draw lines at the right location and time).
- L126 _public member_ `bool bDrawInjectAdditionalDebugChannels = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — if bDrawInjectAdditionalDebugChannels is true, all the channels added for debug purposes with bInjectAdditionalDebugChannels (as well as all those channels with an associated zero weight) will be drawn
- L129 _public function_ `TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> GetChannels() const`
- L131 _public prototype_ `void AddChannel(UPoseSearchFeatureChannel* Channel);`
- L132 _public prototype_ `void AddTemporaryChannel(UPoseSearchFeatureChannel* DependentChannel);`
- L135 _public function_ `template <typename FindPredicateType> const UPoseSearchFeatureChannel* FindChannel(FindPredicateType FindPredicate) const`
- L141 _public function_ `template<typename ChannelType> const ChannelType* FindFirstChannelOfType() const`
- L147 _public function_ `template <typename IteratePredicateType> void IterateChannels(IteratePredicateType IteratePredicate) const`
- L153 _public prototype_ `virtual void PostLoad() override;` — UObject
- L156 _public prototype_ `int8 AddBoneReference(const FBoneReference& BoneReference, const UE::PoseSearch::FRole& Role, bool bDefaultWithRootBone);` — Experimental, this feature might be removed without warning, not for production use
- L157 _public prototype_ `int8 AddBoneReference(const FBoneReference& BoneReference, const UE::PoseSearch::FRole& Role);`
- L158 _public prototype_ `int8 AddCurveReference(const FName& CurveReference, const UE::PoseSearch::FRole& Role);`
- L161 _public prototype_ `int8 FindSchemaBoneIdx(const FName& BoneName, const UE::PoseSearch::FRole& Role, bool bDefaultWithRootBone) const;` — Experimental, this feature might be removed without warning, not for production use
- L164 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L166 _public prototype_ `const UE::PoseSearch::FRole GetDefaultRole() const;`
- L167 _public function_ `const TArray<FPoseSearchRoledSkeleton>& GetRoledSkeletons() const`
- L169 _public prototype_ `TConstArrayView<float> BuildQuery(UE::PoseSearch::FSearchContext& SearchContext) const;`
- L171 _public prototype_ `void AddSkeleton(USkeleton* Skeleton, UMirrorDataTable* MirrorDataTable = nullptr, const UE::PoseSearch::FRole& Role = UE::PoseSearch::DefaultRole);`
- L172 _public prototype_ `bool AreSkeletonsCompatible(const UPoseSearchSchema* Other) const;`
- L173 _public prototype_ `void AddDefaultChannels();`
- L175 _public prototype_ `const FPoseSearchRoledSkeleton* GetRoledSkeleton(const UE::PoseSearch::FRole& Role) const;`
- L176 _public prototype_ `FPoseSearchRoledSkeleton* GetRoledSkeleton(const UE::PoseSearch::FRole& Role);`
- L178 _public prototype_ `USkeleton* GetSkeleton(const UE::PoseSearch::FRole& Role) const;`
- L179 _public prototype_ `UMirrorDataTable* GetMirrorDataTable(const UE::PoseSearch::FRole& Role) const;`
- L180 _public prototype_ `TConstArrayView<FBoneReference> GetBoneReferences(const UE::PoseSearch::FRole& Role) const;`
- L184 _private function_ `template <typename FindPredicateType> static const UPoseSearchFeatureChannel* FindChannelRecursive(TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> Channels, FindPredicateType FindPredicate)`
- L205 _private function_ `template <typename IteratePredicateType> static void IterateChannelsRecursive(TConstArrayView<TObjectPtr<UPoseSearchFeatureChannel>> Channels, IteratePredicateType IteratePredicate)`
- L217 _private prototype_ `void Finalize();`
- L218 _private prototype_ `void ResetFinalize();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`
- L143 _function_ `return static_cast<const ChannelType*>(FindChannel([this](const UPoseSearchFeatureChannel* Channel) -> const UPoseSearchFeatureChannel* { return Cast<ChannelType>(Channel); }));` (scope `UPoseSearchSchema::FindFirstChannelOfType`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchSettings.h` (Public)


#### class `UPoseSearchSettings`  
`class UPoseSearchSettings : public UDeveloperSettings`  
_L10-27_
- reflection: `UCLASS(Config=Engine, defaultconfig, meta=(DisplayName="Pose Search"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Default PoseSearch settings.
- L14 _private prototype_ `UPoseSearchSettings();`
- L17 _public prototype_ `static const UPoseSearchSettings& Get();`
- L21 _public member_ `int32 AvailabilitiesBufferSize = 8;` — `UPROPERTY(EditAnywhere, config, Category = "Interaction", meta = (ClampMin = "0"))` — Initial size for the interaction availabilities buffer
- L26 _public member_ `int32 MaxDatabaseEditorPreviewActors = 50;` — `UPROPERTY(EditAnywhere, config, Category = "Editor", meta = (ClampMin = "1"))` — Maximum number of skeletal-mesh preview actors spawned in the Pose Search Database editor viewport. Lower this when previewing animations on complex meshes to keep the editor responsive.

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchTrajectoryLibrary.h` (Public)


#### struct `FPoseSearchTrajectoryData`  
`struct FPoseSearchTrajectoryData`  
_L21-91_
- reflection: `USTRUCT(BlueprintType)`
- L60 _public prototype_ `bool UpdateData(float DeltaTime, const FAnimInstanceProxy& AnimInstanceProxy, FDerived& TrajectoryDataDerived, FState& TrajectoryDataState) const;`
- L61 _public prototype_ `bool UpdateData(float DeltaTime, const UObject* Context, FDerived& TrajectoryDataDerived, FState& TrajectoryDataState) const;`
- L62 _public prototype_ `FVector StepCharacterMovementGroundPrediction(float DeltaTime, const FVector& InVelocity, const FVector& InAcceleration, const FDerived& TrajectoryDataDerived) const;`
- L68 _public member_ `float RotateTowardsMovementSpeed = 10.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings")` — If the character is forward facing (i.e. bOrientRotationToMovement is true), this controls how quickly the trajectory will rotate to face acceleration. It's common for this to differ from the rotation rate of the character, because animations are often authored with different rotation speeds than the character. This is especially true in cases where the character rotation snaps to movement.
- L73 _public member_ `float MaxControllerYawRate = 70.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings")` — Maximum controller yaw  rate in degrees per second used to clamp the character owner controller desired yaw to generate the prediction trajectory. Negative values disable the clamping behavior
- L78 _public member_ `float BendVelocityTowardsAcceleration = 0.f;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (ClampMin = "0", ClampMax = "1"))` — artificially bend character velocity towards acceleration direction to compute trajectory prediction, to get sharper turns 0: character velocity is used with no alteration, 1: the acceleration direction is used as velocity direction
- L81 _public member_ `bool bUseSpeedRemappingCurve = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (InlineEditConditionToggle))`
- L84 _public member_ `FRuntimeFloatCurve SpeedRemappingCurve;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (EditCondition = "bUseSpeedRemappingCurve"))`
- L87 _public member_ `bool bUseAccelerationRemappingCurve = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (InlineEditConditionToggle))`
- L90 _public member_ `FRuntimeFloatCurve AccelerationRemappingCurve;` — `UPROPERTY(EditDefaultsOnly, Category = "Trajectory Settings", meta = (EditCondition = "bUseAccelerationRemappingCurve"))`

#### struct `FPoseSearchTrajectoryData::FState`  
`struct FState`  
_L26-29_
- L28 _public member_ `float DesiredControllerYawLastUpdate = 0.f;`

#### struct `FPoseSearchTrajectoryData::FDerived`  
`struct FDerived`  
_L31-48_
- L33 _public member_ `float ControllerYawRate = 0.f;`
- L35 _public member_ `float MaxSpeed = 0.f;`
- L36 _public member_ `float BrakingDeceleration = 0.f;`
- L37 _public member_ `float BrakingSubStepTime = 0.f;`
- L38 _public member_ `float Friction = 0.f;`
- L40 _public member_ `FVector Velocity = FVector::ZeroVector;`
- L41 _public member_ `FVector Acceleration = FVector::ZeroVector;`
- L43 _public member_ `FVector Position = FVector::ZeroVector;`
- L44 _public member_ `FQuat Facing = FQuat::Identity;`
- L45 _public member_ `FQuat MeshCompRelativeRotation = FQuat::Identity;`
- L46 _public member_ `bool bOrientRotationToMovement = false;`
- L47 _public member_ `bool bStepGroundPrediction = true;`

#### struct `FPoseSearchTrajectoryData::FSampling`  
`struct FSampling`  
_L50-58_
- L52 _public member_ `int32 NumHistorySamples = 0;`
- L54 _public member_ `float SecondsPerHistorySample = 0.f;` — if SecondsPerHistorySample <= 0, then we collect every update
- L56 _public member_ `int32 NumPredictionSamples = 0;`
- L57 _public member_ `float SecondsPerPredictionSample = 0.f;`

#### struct `FPoseSearchTrajectory_WorldCollisionResults`  
`struct FPoseSearchTrajectory_WorldCollisionResults`  
_L94-103_
- reflection: `USTRUCT(BlueprintType)`
- L99 _public member_ `float TimeToLand = 0.0f;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trajectory Settings")`
- L102 _public member_ `float LandSpeed = 0.0f;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Trajectory Settings")`

#### class `UPoseSearchTrajectoryLibrary`  
`class UPoseSearchTrajectoryLibrary : public UBlueprintFunctionLibrary`  
_L109-265_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Set of functions to help populate a FTransformTrajectory for motion matching.
- L116 _public prototype_ `static void UpdateHistory_TransformHistory(FTransformTrajectory& Trajectory, FVector CurrentPosition, FVector CurrentVelocity, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float DeltaTime, float CurrentTime);` — `UE_DEPRECATED(5.7, "CurrentTime is no longer needed or used. Use UpdateHistory_TransformHistory with no CurrentTime")`
- L124 _public prototype_ `static void InitTrajectorySamples(FTransformTrajectory& Trajectory, FVector DefaultPosition, FQuat DefaultFacing, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float DeltaTime);` — Initialize history and predicted samples based on sampling settings and a default state
- L131 _public prototype_ `static void UpdateHistory_TransformHistory(FTransformTrajectory& Trajectory, FVector CurrentPosition, FVector CurrentVelocity, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float DeltaTime);` — Update history by tracking offsets that result from character intent (e.g. movement component velocity) and applying that to the current world transform. This works well on linearly-translating platforms as it only stores a history of movement that results from character intent, not movement from platforms. For rotating platforms use UpdateHistory_TransformHistoryWithRotation instead. Important: CurrentVelocity should be the velocity relative to the ground as reported by the character movement component or character mover etc
- L153 _public prototype_ `static void UpdatePrediction_SimulateCharacterMovement(FTransformTrajectory& Trajectory, const FPoseSearchTrajectoryData& TrajectoryData, const FPoseSearchTrajectoryData::FDerived& TrajectoryDataDerived, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float DeltaTime);` — Update prediction by simulating the movement math for ground locomotion from UCharacterMovementComponent.
- L176 _public prototype_ `static void PoseSearchGenerateTransformTrajectory(const UObject* InAnimInstance, UPARAM(ref) const FPoseSearchTrajectoryData& InTrajectoryData, float InDeltaTime, UPARAM(ref) FTransformTrajectory& InOutTrajectory, UPARAM(ref) float& InOutDesiredControllerYawLastUpdate, FTransformTrajectory& OutTrajectory, float InHistorySamplingInterval = 0.04f, int32 InTrajectoryHistoryCount = 10, float InPredictionSamplingInterval = 0.2f, int32 InTrajectoryPredictionCount = 8);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch", meta = (BlueprintThreadSafe, DisplayName = "Pose Search Generate Trajectory (for Character)"))` — Generates a prediction trajectory based of the current character intent. For use with Character actors.
- L191 _public prototype_ `static void PoseSearchGeneratePredictorTransformTrajectory(UObject* InPredictor, UPARAM(ref) const FPoseSearchTrajectoryData& InTrajectoryData, float InDeltaTime, UPARAM(ref) FTransformTrajectory& InOutTrajectory, UPARAM(ref) float& InOutDesiredControllerYawLastUpdate, FTransformTrajectory& OutTrajectory, float InHistorySamplingInterval = 0.04f, int32 InTrajectoryHistoryCount = 10, float InPredictionSamplingInterval = 0.2f, int32 InTrajectoryPredictionCount = 8);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental", meta = (BlueprintThreadSafe, DisplayName = "Pose Search Generate Trajectory (using Predictor)", DeprecatedFunction, DeprecationMessage="Use PoseSearchGeneratePredictorTrajectory that does not take FPoseSearchTrajectoryData."))` — Generates a prediction trajectory based of the current movement intent. For use with predictors. InPredictor must implement IPoseSearchTrajectoryPredictorInterface
- L198 _public prototype_ `static void PoseSearchGenerateTransformTrajectoryWithPredictor(TScriptInterface<IPoseSearchTrajectoryPredictorInterface> InPredictor, float InDeltaTime, UPARAM(ref) FTransformTrajectory& InOutTrajectory, UPARAM(ref) float& InOutDesiredControllerYawLastUpdate, FTransformTrajectory& OutTrajectory, float InHistorySamplingInterval = 0.04f, int32 InTrajectoryHistoryCount = 10, float InPredictionSamplingInterval = 0.2f, int32 InTrajectoryPredictionCount = 8);` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental", meta = (BlueprintThreadSafe, DisplayName = "Pose Search Generate Trajectory (using Predictor)"))` — Generates a prediction trajectory based of the current movement intent. For use with predictors. InPredictor must implement IPoseSearchTrajectoryPredictorInterface
- L221 _public prototype_ `static void GetTransformTrajectorySampleAtTime(UPARAM(ref) const FTransformTrajectory& InTrajectory, float Time, FTransformTrajectorySample& OutTrajectorySample, bool bExtrapolate = false);` — `UFUNCTION(BlueprintPure, Category="Animation|PoseSearch", meta = (BlueprintThreadSafe, DisplayName="GetTrajectorySampleAtTime"))`
- L224 _public prototype_ `static void GetTransformTrajectoryVelocity(UPARAM(ref) const FTransformTrajectory& InTrajectory, float Time1, float Time2, FVector& OutVelocity, bool bExtrapolate = false);` — `UFUNCTION(BlueprintPure, Category="Animation|PoseSearch", meta = (BlueprintThreadSafe, DisplayName="GetTrajectoryVelocity"))`
- L227 _public prototype_ `static void GetTransformTrajectoryAngularVelocity(UPARAM(ref) const FTransformTrajectory& InTrajectory, float Time1, float Time2, FVector& OutAngularVelocity, bool bExtrapolate = false);` — `UFUNCTION(BlueprintPure, Category="Animation|PoseSearch", meta = (BlueprintThreadSafe, DisplayName="GetTrajectoryAngularVelocity"))`
- L230 _public prototype_ `static FTransform GetTransformTrajectorySampleTransform(UPARAM(ref) const FTransformTrajectorySample& InTrajectorySample);` — `UFUNCTION(BlueprintPure, Category="Animation|PoseSearch", meta = (BlueprintThreadSafe, DisplayName="GetTrajectorySampleTransform"))`
- L233 _public prototype_ `static void DrawTransformTrajectory(const UObject* WorldContextObject, UPARAM(ref) const FTransformTrajectory& InTrajectory, const float DebugThickness, float HeightOffset);` — `UFUNCTION(BlueprintCallable, Category="Animation|PoseSearch|Experimental", meta=(DisplayName="DrawTrajectory", WorldContext="WorldContextObject"))`
- L237 _private prototype_ `static void UpdateHistory_TransformHistoryInternal(FTransformTrajectory& Trajectory, FVector CurrentPosition, FVector CurrentVelocity, FQuat CurrentFacing, FVector CurrentAngularVelocityDegrees, bool bApplyAngularCorrection, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float DeltaTime);`
- L246 _private prototype_ `static FVector RemapVectorMagnitudeWithCurve(const FVector& Vector, bool bUseCurve, const FRuntimeFloatCurve& Curve);`
- L248 _private prototype_ `static void UpdatePrediction_SimulateCharacterMovementInit(FTransformTrajectory& Trajectory, FVector& OutCurrentPositionWS, FVector& OutCurrentVelocityWS, FVector& OutCurrentAccelerationWS, FQuat& OutCurrentFacingWS, const FPoseSearchTrajectoryData& TrajectoryData, const FPoseSearchTrajectoryData::FDerived& TrajectoryDataDerived);`
- L256 _private prototype_ `static void UpdatePrediction_SimulateCharacterMovementStep(FTransformTrajectory& Trajectory, FVector& InOutCurrentPositionWS, FVector& InOutCurrentVelocityWS, FVector& InOutCurrentAccelerationWS, FQuat& InOutCurrentFacingWS, const FPoseSearchTrajectoryData& TrajectoryData, const FPoseSearchTrajectoryData::FDerived& TrajectoryDataDerived, const FPoseSearchTrajectoryData::FSampling& TrajectoryDataSampling, float& InOutAccumulatedSeconds);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API POSESEARCH_API`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchTrajectoryPredictor.h` (Public)


#### class `UPoseSearchTrajectoryPredictorInterface`  
`class UPoseSearchTrajectoryPredictorInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable, Experimental)`
- inherits: `UInterface`

#### class `IPoseSearchTrajectoryPredictorInterface`  
`class IPoseSearchTrajectoryPredictorInterface : public IInterface`  
_L20-41_
- inherits: `IInterface`
- desc: PoseSearchTrajectoryPredictor: API for an object to implement to act as a predictor of the future trajectory for motion matching animation purposes
- L27 _public prototype_ `virtual void Predict(FTransformTrajectory& InOutTrajectory, int32 NumPredictionSamples, float SecondsPerPredictionSample, int32 NumHistorySamples) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental")`
- L30 _public prototype_ `virtual void GetGravity(FVector& OutGravityAccel) = 0;` — `UFUNCTION(BlueprintCallable, Category="Animation|PoseSearch|Experimental")`
- L33 _public prototype_ `virtual void GetCurrentState(FVector& OutPosition, FQuat& OutFacing, FVector& OutVelocity) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental")`
- L36 _public prototype_ `virtual void GetVelocity(FVector& OutVelocity) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental")`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/PoseSearchTrajectoryTypes.h` (Public)


#### struct `FPoseSearchQueryTrajectorySample`  
`FPoseSearchQueryTrajectorySample`  
_L17-50_
- reflection: `USTRUCT(BlueprintType, Category="Pose Search Trajectory")`
- reflection: `UE_DEPRECATED(5.6, "FPoseSearchQueryTrajectorySample has been deprecated. Use FTransformTrajectorySample instead.")`
- L21 _public prototype_ `FPoseSearchQueryTrajectorySample(const FQuat& InFacing, const FVector& InPosition, float InAccumulatedSeconds);`
- L25 _public prototype_ `FPoseSearchQueryTrajectorySample() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L26 _public prototype_ `~FPoseSearchQueryTrajectorySample() = default;`
- L27 _public prototype_ `FPoseSearchQueryTrajectorySample(const FPoseSearchQueryTrajectorySample&) = default;`
- L28 _public prototype_ `FPoseSearchQueryTrajectorySample(FPoseSearchQueryTrajectorySample&&) = default;`
- L29 _public prototype_ `FPoseSearchQueryTrajectorySample& operator=(const FPoseSearchQueryTrajectorySample&) = default;`
- L30 _public prototype_ `FPoseSearchQueryTrajectorySample& operator=(FPoseSearchQueryTrajectorySample&&) = default;`
- L35 _public member_ `FQuat Facing = FQuat::Identity;` — `UE_DEPRECATED(5.6, "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::Facing.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::Facing."))`
- L39 _public member_ `FVector Position = FVector::ZeroVector;` — `UE_DEPRECATED(5.6, "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::Position.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::Position."))`
- L43 _public member_ `float AccumulatedSeconds = 0.f;` — `UE_DEPRECATED(5.6, "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::AccumulatedSeconds.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FTransfromTrajectorySample instead. See FTransfromTrajectorySample::AccumulatedSeconds."))`
- L46 _public prototype_ `FPoseSearchQueryTrajectorySample Lerp(const FPoseSearchQueryTrajectorySample& Other, float Alpha) const;`
- L47 _public prototype_ `void SetTransform(const FTransform& Transform);`
- L48 _public function_ `FTransform GetTransform() const`

#### struct `FPoseSearchQueryTrajectory`  
`FPoseSearchQueryTrajectory`  
_L58-92_
- reflection: `USTRUCT(BlueprintType, Category="Pose Search Trajectory")`
- reflection: `UE_DEPRECATED(5.6, "FPoseSearchQueryTrajectory has been deprecated. Use FTransformTrajectory instead.")`
- L64 _public prototype_ `FPoseSearchQueryTrajectory() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L65 _public prototype_ `~FPoseSearchQueryTrajectory() = default;`
- L66 _public prototype_ `FPoseSearchQueryTrajectory(const FPoseSearchQueryTrajectory&) = default;`
- L67 _public prototype_ `FPoseSearchQueryTrajectory(FPoseSearchQueryTrajectory&&) = default;`
- L68 _public prototype_ `FPoseSearchQueryTrajectory& operator=(const FPoseSearchQueryTrajectory&) = default;`
- L69 _public prototype_ `FPoseSearchQueryTrajectory& operator=(FPoseSearchQueryTrajectory&&) = default;`
- L73 _public prototype_ `FPoseSearchQueryTrajectory(const FTransformTrajectory& InTrajectory);` — Implicit conversion constructor in oreder to facilitate deprecations.
- L76 _public prototype_ `operator FTransformTrajectory() const;` — Implicit conversion operator in order to facilitate deprecations.
- L82 _public member_ `TArray<FPoseSearchQueryTrajectorySample> Samples;` — `UE_DEPRECATED(5.6, "Use FTransformTrajectory instead. See FTransfromTrajectory::Samples.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FTransfromTrajectory instead. See FTransfromTrajectory:Samples."))` — This contains zero or more history samples, a current sample, and zero or more future predicted samples.
- L84 _public prototype_ `FPoseSearchQueryTrajectorySample GetSampleAtTime(float Time, bool bExtrapolate = false) const;`
- L88 _public prototype_ `void DebugDrawTrajectory(const UWorld* World, const float DebugThickness = 0.f, float HeightOffset = 0.f) const;`
- L89 _public prototype_ `void DebugDrawTrajectory(FAnimInstanceProxy& AnimInstanceProxy, const float DebugThickness = 0.f, float HeightOffset = 0.f, int MaxHistorySamples = -1, int MaxPredictionSamples = -1) const;`
- L90 _public prototype_ `void DebugDrawTrajectory(const UObject* Owner, const FLogCategoryBase& Category, ELogVerbosity::Type Verbosity, const float DebugThickness = 0.f, float HeightOffset = 0.f) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API POSESEARCH_API`
- L53 _prototype_ `FArchive& operator<<(FArchive& Ar, FPoseSearchQueryTrajectorySample& TrajectorySample);`
- L95 _prototype_ `FArchive& operator<<(FArchive& Ar, FPoseSearchQueryTrajectory& Trajectory);`

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/Trace/PoseSearchTraceLogger.h` (Public)


#### struct `UE::PoseSearch::FTraceLogger`  
`struct UE_DEPRECATED(5.7, "FTraceLogger is no longer necessary and it'll be removed") FTraceLogger`  
_L20-24_
- L23 _public member_ `static const FName Name;` — Used for reading trace data

#### struct `UE::PoseSearch::FTraceMessage`  
`struct FTraceMessage`  
_L28-39_
- desc: Base message type for common data
- L30 _public member_ `uint64 Cycle = 0;`
- L33 _public member_ `uint64 AnimInstanceId = 0;` — @todo: rename it to AnimContextId
- L37 _public member_ `int32 NodeId = InvalidSearchId;` — motion matching Search Id associated with this message @todo: rename it to SearchId
- L38 _public function_ `int32 GetSearchId() const`

#### struct `UE::PoseSearch::FTraceMotionMatchingStatePoseEntry`  
`struct FTraceMotionMatchingStatePoseEntry`  
_L42-49_
- L44 _public member_ `int32 DbPoseIdx = INDEX_NONE;`
- L45 _public member_ `EPoseCandidateFlags PoseCandidateFlags = EPoseCandidateFlags::None;`
- L46 _public member_ `FPoseSearchCost Cost;`
- L48 _public function_ `bool operator==(const FTraceMotionMatchingStatePoseEntry& Other) const`

#### struct `UE::PoseSearch::FTraceMotionMatchingStateDatabaseEntry`  
`struct FTraceMotionMatchingStateDatabaseEntry`  
_L52-59_
- L54 _public member_ `uint64 DatabaseId = 0;`
- L55 _public member_ `TArray<float> QueryVector;`
- L56 _public member_ `TArray<FTraceMotionMatchingStatePoseEntry> PoseEntries;`
- L58 _public function_ `bool operator==(const FTraceMotionMatchingStateDatabaseEntry& Other) const`

#### struct `UE::PoseSearch::FTraceMotionMatchingStateMessage`  
`struct FTraceMotionMatchingStateMessage : public FTraceMessage`  
_L65-141_
- inherits: `FTraceMessage`
- desc: Used to trace motion matching state data via the logger, which is then placed into a timeline
- L68 _public prototype_ `FTraceMotionMatchingStateMessage() = default;`
- L69 _public prototype_ `FTraceMotionMatchingStateMessage(const FTraceMotionMatchingStateMessage& Other) = default;`
- L70 _public prototype_ `FTraceMotionMatchingStateMessage(FTraceMotionMatchingStateMessage&& Other) = default;`
- L71 _public prototype_ `FTraceMotionMatchingStateMessage& operator=(const FTraceMotionMatchingStateMessage& Other) = default;`
- L72 _public prototype_ `FTraceMotionMatchingStateMessage& operator=(FTraceMotionMatchingStateMessage&& Other) = default;`
- L76 _public member_ `float ElapsedPoseSearchTime = 0.f;` — Amount of time since the last pose switch
- L78 _public member_ `float AssetPlayerTime = 0.f;`
- L79 _public member_ `float DeltaTime = 0.f;`
- L80 _public member_ `float SimLinearVelocity = 0.f;`
- L81 _public member_ `float SimAngularVelocity = 0.f;`
- L82 _public member_ `float AnimLinearVelocity = 0.f;`
- L83 _public member_ `float AnimAngularVelocity = 0.f;`
- L84 _public member_ `float Playrate = 0.f;`
- L85 _public member_ `float AnimLinearVelocityNoTimescale = 0.f;`
- L86 _public member_ `float AnimAngularVelocityNoTimescale = 0.f;`
- L88 _public member_ `float RecordingTime = 0.f;`
- L89 _public member_ `float SearchBestCost = 0.f;`
- L90 _public member_ `float SearchBruteForceCost = 0.f;`
- L91 _public member_ `int32 SearchBestPosePos = 0;`
- L93 _public member_ `TArray<uint64> SkeletalMeshComponentIds;`
- L95 _public member_ `TArray<FRole> Roles;`
- L97 _public member_ `TArray<FTraceMotionMatchingStateDatabaseEntry> DatabaseEntries;`
- L99 _public member_ `TArray<UE::PoseSearch::FArchivedPoseHistory> PoseHistories;`
- L102 _public member_ `int32 CurrentDbEntryIdx = INDEX_NONE;` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for a FTraceMotionMatchingStateDatabaseEntry::PoseEntries with PoseCandidateFlags containg EPoseCandidateFlags::Valid_ContinuingPose for the 'current database and pose index' instead")`
- L105 _public member_ `int32 CurrentPoseEntryIdx = INDEX_NONE;` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for a FTraceMotionMatchingStateDatabaseEntry::PoseEntries with PoseCandidateFlags containg EPoseCandidateFlags::Valid_ContinuingPose for the 'current database and pose index' instead")`
- L107 _public member_ `EPoseSearchInterruptMode InterruptMode = EPoseSearchInterruptMode::DoNotInterrupt;`
- L110 _public prototype_ `void Input(FPoseSearchCustomVersion::Type CustomVersionType, TConstArrayView<uint8> Data);` — Input the current state from EventData
- L112 _public prototype_ `void Output();` — Output the current state info to the logger
- L115 _public prototype_ `const UPoseSearchDatabase* GetCurrentDatabase() const;` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for a FTraceMotionMatchingStateDatabaseEntry::PoseEntries with PoseCandidateFlags containg EPoseCandidateFlags::Valid_ContinuingPose for the 'current database and pose index' instead")`
- L117 _public prototype_ `int32 GetCurrentDatabasePoseIndex() const;` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for a FTraceMotionMatchingStateDatabaseEntry::PoseEntries with PoseCandidateFlags containg EPoseCandidateFlags::Valid_ContinuingPose for the 'current database and pose index' instead")`
- L119 _public prototype_ `const FTraceMotionMatchingStatePoseEntry* GetCurrentPoseEntry() const;` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for a FTraceMotionMatchingStateDatabaseEntry::PoseEntries with PoseCandidateFlags containg EPoseCandidateFlags::Valid_ContinuingPose for the 'current database and pose index' instead")`
- L123 _public function_ `static const T* GetObjectFromId(uint64 ObjectId)` — `UE_DEPRECATED(5.7, "This API will soon be removed. Look for ResolveDatabaseFromId to resolve databases from ids")`
- L140 _public member_ `static const FName Name;` — `UE_DEPRECATED(5.7, "FTraceMotionMatchingStateMessage::Name is no longer necessary and it'll be removed")`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API POSESEARCH_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PoseSearch` (scope `UE`)
- L40 _prototype_ `FArchive& operator<<(FArchive& Ar, FTraceMessage& State);` (scope `UE::PoseSearch`)
- L50 _prototype_ `FArchive& operator<<(FArchive& Ar, FTraceMotionMatchingStatePoseEntry& Entry);` (scope `UE::PoseSearch`)
- L60 _prototype_ `FArchive& operator<<(FArchive& Ar, FTraceMotionMatchingStateDatabaseEntry& Entry);` (scope `UE::PoseSearch`)
- L143 _prototype_ `FArchive& operator<<(FArchive& Ar, FTraceMotionMatchingStateMessage& State);` (scope `UE::PoseSearch`)

### `Plugins/Animation/PoseSearch/Source/Runtime/Public/PoseSearch/VPTree.h` (Public)


#### struct `UE::PoseSearch::FIndexDistance`  
`struct FIndexDistance`  
_L29-56_
- L31 _public function_ `FIndexDistance(int32 InIndex = INDEX_NONE, VPTreeScalar InDistance = VPTreeScalar(0)) : Index(InIndex) , Distance(InDistance)`
- L37 _public function_ `bool operator<(const FIndexDistance& Other) const`
- L42 _public function_ `bool operator==(const FIndexDistance& Other) const`
- L54 _public member_ `int32 Index;`
- L55 _public member_ `VPTreeScalar Distance;`

#### struct `UE::PoseSearch::FVPTreeNode`  
`struct FVPTreeNode : public FIndexDistance`  
_L58-75_
- inherits: `FIndexDistance`
- L60 _public member_ `int32 LeftIndex = INDEX_NONE;`
- L61 _public member_ `int32 RightIndex = INDEX_NONE;`
- L63 _public function_ `bool operator==(const FVPTreeNode& Other) const`

#### struct `UE::PoseSearch::FVPTreeResultSet`  
`struct FVPTreeResultSet`  
_L77-172_
- L79 _public function_ `FVPTreeResultSet(int32 InNumNeighbors) : NumNeighbors(InNumNeighbors)`
- L90 _public function_ `VPTreeScalar GetWorstDistance() const`
- L95 _public function_ `bool IsFull() const`
- L100 _public function_ `void AddPoint(float Distance, int32 Index #if VALIDATE_FINDNEIGHBORS , int32 BestIndex = INDEX_NONE #endif`
- L136 _public function_ `TArray<FIndexDistance> GetSortedResults()`
- L149 _public function_ `TConstArrayView<FIndexDistance> GetUnsortedResults() const`
- L154 _public function_ `bool operator==(const FVPTreeResultSet& Other) const`
- L169 _private member_ `const int32 NumNeighbors;`
- L171 _private member_ `TArray<FIndexDistance, TInlineAllocator<HeapDefaultMaxSize>> Heap;`

#### struct `UE::PoseSearch::FVPTreeResultSet::HeapCompare`  
`struct HeapCompare`  
_L160-167_
- L162 _public function_ `bool operator()(const FIndexDistance& A, const FIndexDistance& B) const`

#### enum `UE::PoseSearch::FVPTreeResultSet::(anonymous)`  
`enum`  
_L170-170_

#### struct `UE::PoseSearch::FVPTree`  
`struct FVPTree`  
_L174-489_
- L177 _public function_ `template<typename TDataSource> void Construct(const TDataSource& DataSource, FRandomStream& RandStream)`
- L193 _public function_ `template<typename TDataSource> bool TestConstruct(const TDataSource& DataSource, int32 NodeIndex = 0) const`
- L201 _public function_ `template<typename T, typename TDataSource, typename TVPTreeResultSet> void FindNeighbors(const T& Query, TVPTreeResultSet& ResultSet, const TDataSource& DataSource) const`
- L361 _public prototype_ `void Reset();`
- L363 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L365 _public prototype_ `bool operator==(const FVPTree& Other) const;`
- L370 _private function_ `void GetSubTreeNodeIndexes(int32 RootNodeIndex, TArray<int32>& NodeIndexes) const`
- L382 _private function_ `template<typename TDataSource> void ChooseVantagePointMappingIndex(const TDataSource& DataSource, TArrayView<FIndexDistance> DataSourceIndexMapping, FRandomStream& RandStream) const` — choose and swap vantage point into DataSourceIndexMapping[0]
- L396 _private function_ `template<typename TDataSource> void CacheDistancesFromVantagePoint(const TDataSource& DataSource, TArrayView<FIndexDistance> DataSourceIndexMapping) const`
- L409 _private function_ `template<typename TDataSource> int32 ConstructRecursive(const TDataSource& DataSource, TArrayView<FIndexDistance> DataSourceIndexMapping, FRandomStream& RandStream)`
- L446 _private function_ `template<typename TDataSource> bool TestConstructRecursive(const TDataSource& DataSource, int32 NodeIndex, TArray<int32>& SubTreeNodeIndexesTempBuffer) const`
- L488 _private member_ `TArray<FVPTreeNode> Nodes;`

#### enum `UE::PoseSearch::FVPTree::FindNeighbors::(anonymous)`  
`enum`  
_L236-236_

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace PoseSearch` (scope `UE`)
- L25 _macro_ `#define VALIDATE_FINDNEIGHBORS 0`
- L27 _typedef_ `typedef float VPTreeScalar;` (scope `UE::PoseSearch`)
- L47 _function_ `friend FArchive& operator<<(FArchive& Ar, FIndexDistance& IndexDistance)` (scope `UE::PoseSearch`)
- L68 _function_ `friend FArchive& operator<<(FArchive& Ar, FVPTreeNode& Node)` (scope `UE::PoseSearch`)
- L170 _enumerator_ `enum { HeapDefaultMaxSize = 256 }; TArray<FIndexDistance` (scope `UE::PoseSearch::FVPTreeResultSet::__anon8cc60f1b0103`)
- L236 _enumerator_ `enum { NodesToSearchDefaultMaxSize = 512 }; TArray<int32` (scope `UE::PoseSearch::FVPTree::FindNeighbors::__anon8cc60f1b0203`)
- L402 _function_ `` (scope `UE::PoseSearch::FVPTree::CacheDistancesFromVantagePoint`)
- L427 _function_ `` (scope `UE::PoseSearch::FVPTree::ConstructRecursive`)
