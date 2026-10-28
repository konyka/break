# Plugins / AnimationLayering

- module root: `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayering`
- headers: 4; symbols: 170
- symbol kinds: class=1, enum=1, enumerator=4, function=11, macro=3, member=95, namespace=3, prototype=36, struct=14, typedef=2
- PrivateDependencyModuleNames: CoreUObject, Engine, PoseSearch
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayering/Public/AnimNode_BoneMask.h` (Public)


#### struct `UE::Anim::BoneMask::FPerBoneData`  
`struct FPerBoneData`  
_L16-27_
- L18 _public member_ `FCompactPoseBoneIndex BoneIndex;`
- L19 _public member_ `float Weight;`
- L21 _public function_ `FPerBoneData(const FCompactPoseBoneIndex InBoneIndex, const float InWeight) : BoneIndex(InBoneIndex) , Weight(InWeight)`

#### struct `UE::Anim::BoneMask::FBodyPartData`  
`struct FBodyPartData`  
_L29-41_
- L31 _public member_ `TArray<FPerBoneData> PerBoneData;`
- L32 _public member_ `TArray<FCompactPoseBoneIndex> ChildIndices;`
- L33 _public member_ `int32 PartIndex;`
- L34 _public member_ `int32 SourcePoseIndex;`
- L35 _public member_ `float MeshSpaceWeight;`
- L36 _public member_ `float LocalSpaceWeight;`
- L39 _public member_ `FName DebugPartName;`

#### struct `FBoneMaskBodyPartNameContainer`  
`struct FBoneMaskBodyPartNameContainer`  
_L45-51_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `TArray<FName> Names;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`

#### struct `FAnimNode_BoneMask`  
`struct FAnimNode_BoneMask : public FAnimNode_Base`  
_L59-194_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: This node is heavily based on AnimNode_LayeredBoneBlend but replacing both BranchFilter and BlendMask option with a single input param that represents different body parts. Each body parts has a list of BranchFilter that maps to actual bones. Blending is done in the order the body parts are created and in local space first and mesh space after. Unlike AnimNode_LayeredBoneBlend, with this node we can change the mask dynamically.
- L67 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)` — The source pose
- L71 _public member_ `TArray<FPoseLink> BlendPoses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category = Links, meta = (BlueprintCompilerGeneratedDefaults))` — Each layer's blended pose
- L75 _public member_ `TArray<float> BlendWeights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category = Runtime, meta = (BlueprintCompilerGeneratedDefaults, PinShownByDefault))` — The weights of each layer
- L79 _public member_ `FBoneMask BoneMask;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Runtime, meta = (BlueprintCompilerGeneratedDefaults, PinShownByDefault))` — Mask with all the body part dynamic values
- L83 _public member_ `TObjectPtr<UBoneMaskDefinitionDataAsset> BoneMaskDefinitionDataAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Runtime, meta = (PinShownByDefault))` — Mask with all the body part static values
- L91 _public member_ `TArray<FBoneMaskBodyPartNameContainer> BodyParts;` — `UPROPERTY(EditAnywhere, editfixedsize, Category = Runtime)` — List of BodyParts that want to use different Poses When adding a new input pose to the node (right click on the node Add Input Pose) an entry to this array is automatically added allowing the user to specify the body part(s) that should use that pose
- L99 _public member_ `bool bProcessMeshSpaceAsRootSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config, meta = (PinHiddenByDefault))` — Process mesh space rotations in root space, effectively ignoring any root rotation
- L101 _public member_ `bool bHasRelevantPoses;`
- L110 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreadhold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L117 _public member_ `bool bUpdateSkeletonDataOnDemand = false;` — `UPROPERTY(EditAnywhere, Category = Performance)` — Whether this node should update bone weights and child bone indices at runtime or use the data cached in the BoneMaskDefinitionDataAsset. Useful for cases where the skeleton can change at runtime and is not possible to have a BoneMaskDefinitionDataAsset for each skeleton.
- L121 _protected member_ `TArray<UE::Anim::BoneMask::FBodyPartData> BodyPartsData;`
- L124 _protected member_ `TArray<FPerBoneBlendWeight> CurrentBoneBlendWeightsForAttributes;` — @TODO: Temp, for now so we can pass it to BlendAttributesPerBoneFilter.
- L127 _protected member_ `TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElementIndexed> CurvePoseSourceIndices;` — Per-curve source pose index
- L130 _protected member_ `uint16 RequiredBonesSerialNumber;` — Serial number of the required bones container
- L139 _protected member_ `TArray<FBodyPartSkeletonData> BodyPartsSkeletonData;`
- L142 _public function_ `FAnimNode_BoneMask() : CurveBlendOption(ECurveBlendOption::Override) , bHasRelevantPoses(false) , LODThreshold(INDEX_NONE) , RequiredBonesSerialNumber(0)`
- L151 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L152 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L153 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L154 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L155 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L156 _public function_ `virtual int32 GetLODThreshold() const override`
- L159 _public function_ `void AddPose()`
- L171 _public function_ `void RemovePose(int32 PoseIndex)`
- L186 _public function_ `void InvalidateCachedBoneData()` — Invalidates the cached bone data so it is recalculated the next time this node is updated
- L191 _private prototype_ `void UpdateCachedBoneData(const FBoneContainer& RequiredBones, const USkeleton* Skeleton);` — Update cached data if required

#### struct `FAnimNode_BoneMask::FBodyPartSkeletonData`  
`struct FBodyPartSkeletonData`  
_L134-138_
- L136 _public member_ `TArray<FBoneMaskPerBoneData> SkeletonPoseBoneWeights;`
- L137 _public member_ `TArray<int32> SkeletonPoseChildBoneIndices;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMATIONLAYERING_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Anim` (scope `UE`)
- L14 _namespace_ `namespace BoneMask` (scope `UE::Anim`)

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayering/Public/BoneControllers/AnimNode_CopyBoneAdvanced.h` (Public)


#### struct `FAnimNode_CopyBoneAdvanced`  
`struct FAnimNode_CopyBoneAdvanced : public FAnimNode_SkeletalControlBase`  
_L14-73_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Controller to copy a bone's transform to another one, with individual per-component alphas.
- L20 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Source Bone Name to get transform from
- L24 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category=Copy)` — Name of bone to control. This is the main bone chain to modify from.
- L28 _public member_ `FVector TranslationWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta = (AllowPreserveRatio, PinHiddenByDefault))` — Per-axis translation weight to copy from source to target.
- L32 _public member_ `float RotationWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta = (PinHiddenByDefault))` — Rotation angle weight to copy from source to target.
- L36 _public member_ `float ScaleWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta = (AllowPreserveRatio, PinHiddenByDefault))` — Scale weight to copy from source to target (not separated per-axis to avoid non-uniform scales)
- L40 _public member_ `TEnumAsByte<EBoneControlSpace> ControlSpace;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Space to convert transforms into prior to copying components
- L46 _public member_ `FBoneReference TranslationSpaceBone;` — `UPROPERTY(EditAnywhere, Category=Copy, meta = (EditCondition = "bTranslationInCustomBoneSpace"))` — Name of the bone Translation Weight is relative to. If left empty, the axes are in source bone space. If unchecked, the axes are in component space.
- L50 _public member_ `bool bTranslationInCustomBoneSpace;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))` — If disabled, the translation weight axes are in component-space
- L54 _public member_ `bool bPropagateToChildren;` — `UPROPERTY(EditAnywhere, Category = Advanced)` — If disabled, the translation weight axes are in component-space
- L56 _public prototype_ `FAnimNode_CopyBoneAdvanced();`
- L59 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L63 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L64 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L69 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L72 _private member_ `TArray<FCompactPoseBoneIndex> ChildBoneIndices;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONLAYERING_API`

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayering/Public/BoneControllers/AnimNode_CopyBoneMotion.h` (Public)


#### enum `ECopyBoneMotion_Component`  
`enum class ECopyBoneMotion_Component : uint8`  
_L16-23_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `TranslationX = 0`
- L19 _public enumerator_ `TranslationY = 1`
- L20 _public enumerator_ `TranslationZ = 2`
- L22 _public enumerator_ `RotationAngle = 3` — In Degrees

#### struct `FAnimNode_CopyBoneMotion`  
`struct FAnimNode_CopyBoneMotion : public FAnimNode_SkeletalControlBase`  
_L27-199_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Highly experimental plugin. There's a strong chance that this gets replaced with Control Rig functionality after initial exploration.
- L33 _public prototype_ `FAnimNode_CopyBoneMotion();`
- L36 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L37 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L41 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L42 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L43 _public prototype_ `virtual void UpdateComponentPose_AnyThread(const FAnimationUpdateContext& Context) override;`
- L44 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context);`
- L45 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L50 _public member_ `FComponentSpacePoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — Input pose to copy the motion from.
- L54 _public member_ `FComponentSpacePoseLink BasePoseReference;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — Reference pose used to calculate a motion delta from the base pose.
- L58 _public member_ `bool bUseBasePose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy)` — Whether to use the input Base Pose. Curves will be used when this is disabled.
- L63 _public member_ `FName PoseHistoryTag = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy)` — Tag of the pose history node to use to reference past bone transforms. Your Pose History must include the desired bones used as Source and Copy.
- L68 _public member_ `float Delay = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (ClampMin="0", PinHiddenByDefault))` — How much to delay the motion we're copying. Your Pose History time horizon/duration must be at least this long.
- L72 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Copy, meta = (EditCondition = "bUseBasePose"))` — Bone to copy the motion from.
- L76 _public member_ `FBoneReference BoneToModify;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Name of bone to control. This is the main bone chain to modify from.
- L81 _public member_ `FBoneReference CopySpace;` — `UPROPERTY(EditAnywhere, Category = Copy, meta = (EditCondition = "bUseBasePose"))` — Bone to use as the reference frame/space for our copied transform delta. If no reference frame is used, the source bone motion will be copied in component space.
- L85 _public member_ `bool bUseRootSpace = false;` — `UPROPERTY(EditAnywhere, Category = Copy, meta = (PinHiddenByDefault, EditCondition = "bUseBasePose"))` — Process CopySpace in root space, ignoring root bone rotation when computing the motion delta (Apply space is not impacted by root rotations)
- L90 _public member_ `FBoneReference ApplySpace;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Bone to use as the reference frame/space for our applied transform delta. If no reference frame is used, the source bone motion will be applied in component space.
- L95 _public member_ `FRotator TranslationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Translation, meta=(PinHiddenByDefault))` — Offset to use before applying the translation deltas (in degrees). This is useful for changing the direction of motion, relative to our reference frame/bone
- L100 _public member_ `FRotator RotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta=(PinHiddenByDefault))` — Rotation offset (in degrees) to apply before the rotation deltas. This is useful for changing the direction of motion, relative to our reference frame/bone
- L105 _public member_ `FVector RotationPivot = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta=(PinHiddenByDefault))` — Pivot offset (in local space) to use when applying the rotation. Any non-zero value will cause the target bone to rotate around the pivot, effectively introducing additional translation.
- L109 _public member_ `FName CurvePrefix = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (EditCondition = "!bUseBasePose"))` — Curve prefix used for the animation curves. Format matches those generated by the LayeringMotionExtractorModifier
- L113 _public member_ `FName TargetCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curve)` — Name of the curve we're outputting motion to.
- L117 _public member_ `float TargetCurveScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curve, meta=(PinHiddenByDefault))` — Which component of motion we're outputting to the curve.
- L121 _public member_ `ECopyBoneMotion_Component TargetCurveComponent = ECopyBoneMotion_Component::RotationAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curve)` — Which component of motion we're outputting to the curve.
- L125 _public member_ `TEnumAsByte<EAxis::Type> TargetCurveRotationAxis = EAxis::X;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Curve, meta = (EditCondition = "TargetCurveComponent == ECopyBoneMotion_Component::RotationAngle"))` — Axis around which to consider the rotation angle for the curve output.
- L128 _public member_ `FName TranslationX_CurveName = NAME_None;` — `UPROPERTY()`
- L131 _public member_ `FName TranslationY_CurveName = NAME_None;` — `UPROPERTY()`
- L134 _public member_ `FName TranslationZ_CurveName = NAME_None;` — `UPROPERTY()`
- L137 _public member_ `FName RotationRoll_CurveName = NAME_None;` — `UPROPERTY()`
- L140 _public member_ `FName RotationPitch_CurveName = NAME_None;` — `UPROPERTY()`
- L143 _public member_ `FName RotationYaw_CurveName = NAME_None;` — `UPROPERTY()`
- L146 _public member_ `FVector TranslationScale = FVector::One();` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Translation, meta = (AllowPreserveRatio, PinHiddenByDefault))`
- L149 _public member_ `float TranslationSmoothingTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Translation, meta = (PinHiddenByDefault))`
- L152 _public member_ `TObjectPtr<const UCurveVector> TranslationRemapCurve = nullptr;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Translation, meta = (PinHiddenByDefault))`
- L155 _public member_ `float RotationScale = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Rotation, meta = (PinHiddenByDefault))`
- L158 _public member_ `float RotationSmoothingTime = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (PinHiddenByDefault))`
- L161 _public member_ `TObjectPtr<const UCurveFloat> RotationRemapCurve = nullptr;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Rotation, meta = (PinHiddenByDefault))`
- L165 _public member_ `bool bDeltaSmoothing = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Advanced)` — Do the smoothing as a delta between input and output poses, instead of a global component space smoothing.
- L169 _protected prototype_ `void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;`
- L170 _protected prototype_ `float GetTargetCurveValue(const FTransformNoScale& InTransformDelta, ECopyBoneMotion_Component MotionComponent);`
- L171 _protected prototype_ `bool HasTargetBone(const FBoneContainer& BoneContainer) const;`
- L172 _protected prototype_ `bool HasTargetCurve() const;`
- L173 _protected prototype_ `void Reset();`
- L174 _protected member_ `bool bIsFirstUpdate = true;`
- L179 _private member_ `FVector LastLocDebug = FVector::Zero();`
- L180 _private member_ `FVector LastRotDebug = FVector::Zero();`
- L181 _private member_ `FTransform ApplySpaceDebugTransform = FTransform::Identity;`
- L182 _private member_ `bool bIsDrawHistoryEnabled = false;`
- L185 _private prototype_ `void UpdateApplySpace(FComponentSpacePoseContext& Output, const FBoneContainer& BoneContainer, FCompactPoseBoneIndex CompactPoseBoneToModify, FTransformNoScale& InOutTransformOffset, FTransform& InOutNewBoneTM);`
- L186 _private prototype_ `void UpdateCopySpace(const FTransform& SourceToTransform, const FTransform& SourceFromTransform, const FTransform& BoneSpaceToTransform, const FTransform& BoneSpaceFromPoseTransform, FTransformNoScale& OutTransformOffset);`
- L193 _private member_ `} SpringState;`
- L195 _private member_ `FGraphTraversalCounter UpdateCounter;`
- L197 _private prototype_ `void LogRequestError(const FComponentSpacePoseContext& Context, const FSkeletonPoseBoneIndex BoneIdx);`

#### struct `FAnimNode_CopyBoneMotion::FSpringData`  
`struct FSpringData`  
_L188-193_
- L190 _public member_ `FTransformNoScale CurrentTransform;`
- L191 _public member_ `FVector Velocity;`
- L192 _public member_ `FVector AngularVelocity;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONLAYERING_API`

### `Plugins/Experimental/Animation/AnimationLayering/Source/AnimationLayering/Public/BoneMaskTypes.h` (Public)


#### struct `FBoneMaskPerBoneData`  
`struct FBoneMaskPerBoneData`  
_L14-23_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `int32 SkeletonPoseBoneIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoneMask)`
- L22 _public member_ `float BlendWeight = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoneMask)`

#### struct `FBoneMaskBodyPartDefinition`  
`struct FBoneMaskBodyPartDefinition`  
_L26-41_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoneMask)`
- L34 _public member_ `TArray<FBranchFilter> BranchFilters;` — `UPROPERTY(EditAnywhere, Category = BoneMask)`
- L37 _public member_ `TArray<FBoneMaskPerBoneData> SkeletonPoseBoneWeights;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BoneMask)`
- L40 _public member_ `TArray<int32> SkeletonPoseChildBoneIndices;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BoneMask)`

#### struct `FBoneMaskEntry`  
`struct FBoneMaskEntry`  
_L44-61_
- reflection: `USTRUCT(BlueprintType)`
- L49 _public member_ `float LocalSpaceWeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneMask, meta = (UIMin = "0", UIMax = "1"))`
- L52 _public member_ `float MeshSpaceWeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneMask, meta = (UIMin = "0", UIMax = "1"))`
- L54 _public prototype_ `FBoneMaskEntry() = default;`
- L55 _public function_ `FBoneMaskEntry(const float InLocalSpaceWeight, const float InMeshSpaceWeight) : LocalSpaceWeight(InLocalSpaceWeight) , MeshSpaceWeight(InMeshSpaceWeight)`

#### struct `FBoneMask`  
`struct FBoneMask`  
_L64-72_
- reflection: `USTRUCT(BlueprintType)`
- L71 _public member_ `TMap<FName, FBoneMaskEntry> BoneMaskMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoneMask)`

#### struct `FBoneMaskDefinition`  
`struct FBoneMaskDefinition`  
_L75-102_
- reflection: `USTRUCT(BlueprintType)`
- L80 _public member_ `TArray<FBoneMaskBodyPartDefinition> BodyPartDefinitions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoneMask)`
- L82 _public function_ `inline const FBoneMaskBodyPartDefinition* FindBodyPart(const FName& Name) const`
- L90 _public function_ `inline FBoneMaskBodyPartDefinition* FindBodyPart(const FName& Name)`
- L96 _public function_ `void AddBodyPartDefinition(const FName& Name, const TArray<FBranchFilter>& BranchFilters)`

#### class `UBoneMaskDefinitionDataAsset`  
`class UBoneMaskDefinitionDataAsset : public UDataAsset`  
_L105-146_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L112 _private member_ `TObjectPtr<USkeleton> Skeleton = nullptr;` — `UPROPERTY(EditAnywhere, Category = BoneMask)`
- L115 _private member_ `mutable FGuid SkeletonGuid;` — `UPROPERTY()`
- L118 _private member_ `mutable FGuid VirtualBoneGuid;` — `UPROPERTY()`
- L120 _private prototype_ `void ConditionallyUpdateBoneMaskCachedData() const;`
- L122 _private prototype_ `void UpdateBoneMaskCachedData_Internal() const;`
- L125 _private prototype_ `bool NeedsBoneMaskUpdate(const USkeleton& InSkeleton) const;` — Check whether per-bone blend weights are valid according to the skeleton (GUID check)
- L131 _protected member_ `mutable FBoneMaskDefinition BoneMaskDefinition;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoneMask)`
- L135 _public prototype_ `void Serialize(FArchive& Ar);`
- L136 _public prototype_ `const FBoneMaskDefinition& GetBoneMaskDefinition() const;`
- L137 _public prototype_ `virtual void PostLoad() override;`
- L139 _public typedef_ `typedef TFunctionRef<TArray<FBoneMaskPerBoneData>& (int32 BodyPartIdx)> FGetBoneWeightsForBodyPartsCallback;`
- L140 _public typedef_ `typedef TFunctionRef<TArray<int32>& (int32 BodyPartIdx)> FGetChildBoneIndicesForBodyPartCallback;`
- L141 _public prototype_ `static void UpdateBoneMaskCachedData(const USkeleton& Skeleton, const FBoneMaskDefinition& BoneMaskDefinition, FGetBoneWeightsForBodyPartsCallback GetBoneWeightsForBodyPartsCallback, FGetChildBoneIndicesForBodyPartCallback GetChildBoneIndicesForBodyPartCallback);`
- L144 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### struct `FBoneMaskUpdateMultiParam`  
`struct FBoneMaskUpdateMultiParam`  
_L149-161_
- reflection: `USTRUCT(BlueprintType)`
- L154 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L157 _public member_ `float LocalSpaceWeight = -1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L160 _public member_ `float MeshSpaceWeight = -1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`

#### Free symbols / members of external scopes

- L87 _function_ `return BodyPartDefinitions.FindByPredicate([&Name](const FBoneMaskBodyPartDefinition& Item) { return Item.Name == Name; });` (scope `FBoneMaskDefinition::FindBodyPart`) — @TODO: This array is fairly small, but if this ended up being 'heavy' we may consider change to a map
