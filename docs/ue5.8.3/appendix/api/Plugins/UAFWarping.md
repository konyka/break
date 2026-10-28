# Plugins / UAFWarping

- module root: `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping`
- headers: 8; symbols: 252
- symbol kinds: delegate=1, enum=3, enumerator=7, function=4, macro=5, member=140, namespace=14, prototype=42, struct=31, typedef=5
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, RigVM, UAF, UAFAnimGraph, UAFAnimNode

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/AnimNextWarpingLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimNextWarping, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimNextWarping, Log, All);`

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/AnimNode/UAFStrafeWarpingNode.h` (Private)


#### struct `UE::UAF::FUAFStrafeWarpingPostAnimOp`  
`struct FUAFStrafeWarpingPostAnimOp : public FUAFAnimOp`  
_L21-77_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L26 _public prototype_ `FUAFStrafeWarpingPostAnimOp();`
- L28 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;`
- L47 _public prototype_ `void DoWarpRootMotion(FUAFAnimOpValueEvaluator& Evaluator, const FVector& RotationAxisVector, const FVector& TargetMoveDir, float& OutTargetOrientationAngleRad);`
- L48 _public prototype_ `void DoWarpPose(FUAFAnimOpValueEvaluator& Evaluator, const FVector& RotationAxisVector);`
- L49 _public prototype_ `void InitializeSpineData(TArrayView<FSpineBoneData> OutSpineBoneData, const TArray<FName>& SpineBoneNames, FAttributeTypedSetPtr BoneSet);`
- L51 _public member_ `TWeakObjectPtr<const UObject> HostObject;`
- L54 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — Target orientation per instance
- L57 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — Last root bone transform sampled
- L60 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L62 _public member_ `float Alpha = 1.0f;`
- L65 _public member_ `FVector RootMotionDeltaDirection = FVector::ZeroVector;` — Internal current frame root motion delta direction
- L68 _public member_ `FQuat RootMotionDeltaRotation = FQuat::Identity;` — Internal current frame root motion delta angle
- L71 _public member_ `float CounterCompensateTargetAngleRad = 0.0f;` — Target for counter compenstate, we keep the target so we can smoothly interp.
- L74 _public member_ `float OrientationAngleForPoseWarpRad = 0.f;` — Internal orientation warping angle
- L76 _public member_ `const FUAFStrafeWarpingData* SharedData = nullptr;`

#### struct `UE::UAF::FUAFStrafeWarpingPostAnimOp::FSpineBoneData`  
`struct FSpineBoneData`  
_L32-45_
- desc: Internal structure with some precomputed weight values and bone indices
- L34 _public member_ `FAttributeSetIndex BoneIndex;`
- L35 _public member_ `float Weight = 0.f;`

#### struct `UE::UAF::FUAFStrafeWarpingPostAnimOp::FSpineBoneData::FCompareBoneIndex`  
`struct FCompareBoneIndex`  
_L38-44_
- desc: Comparison Operator for Sorting
- L40 _public function_ `FORCEINLINE bool operator()(const FSpineBoneData& A, const FSpineBoneData& B) const`

#### struct `UE::UAF::FUAFStrafeWarpingData`  
`struct FUAFStrafeWarpingData : public FUAFModifierAnimNodeData`  
_L80-166_
- reflection: `USTRUCT(DisplayName = "Strafe Warping")`
- inherits: `FUAFModifierAnimNodeData`
- L86 _public member_ `FBindableFloat Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Alpha)` — Current strength of the skeletal control
- L90 _public member_ `FBindableQuat TargetOrientation;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — The Orientation to steer towards
- L95 _public member_ `FBindableTransform RootBoneTransform;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — @TODO Temp / try to remove this. Shouldn't have to feed as argument Last root bone transform sampled
- L99 _public member_ `TEnumAsByte<EAxis::Type> RotationAxis = EAxis::Z;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Rotation axis used when rotating the character body
- L103 _public member_ `float DistributedBoneOrientationAlpha = 0.5f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", ClampMax="1.0"))` — Specifies how much rotation is applied to the character body versus IK feet
- L108 _public member_ `float RotationInterpSpeed = 10.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0"))` — Specifies the interpolation speed (in Alpha per second) towards reaching the final warped rotation angle A value of 0 will cause instantaneous rotation, while a greater value will introduce smoothing
- L113 _public member_ `float CounterCompensateInterpSpeed = 45.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — Same as RotationInterpSpeed, but for CounterCompensate smoothing. A value of 0 sample raw root motion. Used to avoid stuttering from resampling root deltas. Root motion is already smooth, so a large value is our default (~75% of 60 fps).
- L118 _public member_ `float MaxCorrectionDegrees = 180.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Max correction we're allowed to do per-second when using interpolation. This minimizes pops when we have a large difference between current and target orientation.
- L122 _public member_ `float MaxRootMotionDeltaToCompensateDegrees = 45.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Don't compensate our interpolator when the instantaneous root motion delta is higher than this. This is likely a pivot.
- L128 _public member_ `bool bCounterCompenstateInterpolationByRootMotion = true;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(EditCondition="RotationInterpSpeed > 0.0f"))` — Whether to counter compensate interpolation by the animated root motion angle change over time. This helps to conserve the motion from our animation. Disable this if your root motion is expected to be jittery, and you want orientation warping to smooth it out.
- L134 _public member_ `float MinRootMotionSpeedThreshold = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (ClampMin = "0.0"))` — Minimum root motion speed required to apply orientation warping This is useful to prevent unnatural re-orientation when the animation has a portion with no root motion (i.e starts/stops/idles) When this value is greater than 0, it's recommended to enable interpolation with RotationInterpSpeed > 0
- L144 _public member_ `float LocomotionAngleDeltaThreshold = 90.f;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(ClampMin="0.0", ClampMax="180.0"))` — Specifies an angle threshold to prevent erroneous over-rotation of the character, disabled with a value of 0 When the effective orientation warping angle is detected to be greater than this value (default: 90 degrees) the locomotion direction will be inverted prior to warping This will be used in the following equation: [Orientation = RotationBetween(RootMotionDirection, -LocomotionDirection)] Example: Playing a forward running animation while the motion is going backward Rather than orientation warping by 180 degrees, the system will warp by 0 degrees
- L149 _public member_ `bool PreserveOriginalRootRotation = true;` — `UPROPERTY(EditAnywhere, Category=Evaluation)` — When true, propagates any modification on the root bone down to all of its children When false, will directly modify the root
- L156 _public member_ `TArray<FName> SpineBones;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Spine bone definitions Used to counter rotate the body in order to keep the character facing forward The amount of counter rotation applied is driven by DistributedBoneOrientationAlpha TODO: we ideally would use an equivlane to FBoneReference
- L159 _public member_ `TArray<FStrafeWarpFootData> FootData;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Bones"))`
- L162 _public member_ `EStrafeWarpingFootMode FootMode = EStrafeWarpingFootMode::DoBasicIK;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L165 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFAnimNodeData impl

#### struct `UE::UAF::FUAFStrafeWarpingNode`  
`struct FUAFStrafeWarpingNode : FUAFModifierAnimNode`  
_L169-181_
- inherits: `FUAFModifierAnimNode`
- desc: This node modifies an animation pose to orientate towards a desired move direction
- L171 _public prototype_ `FUAFStrafeWarpingNode(FUAFAnimGraphUpdateContext& Context, const FUAFStrafeWarpingData& InData);`
- L173 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& Context) override;`
- L176 _public prototype_ `virtual FString GetDebugName() const override;`
- L177 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L180 _private member_ `FUAFStrafeWarpingPostAnimOp PostAnimOp;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/AnimNode/UAFWarpToTargetNode.h` (Private)


#### struct `UE::UAF::FUAFWarpToTargetPostAnimOp`  
`struct FUAFWarpToTargetPostAnimOp : public FUAFAnimOp`  
_L17-30_
- reflection: `USTRUCT()`
- inherits: `FUAFAnimOp`
- L22 _public prototype_ `FUAFWarpToTargetPostAnimOp();`
- L24 _public prototype_ `virtual void EvaluateValues(FUAFAnimOpValueEvaluator& Evaluator) override;`
- L26 _public member_ `TWeakObjectPtr<const UObject> HostObject;`
- L28 _public member_ `FTransform RootBoneTransform = FTransform::Identity;`
- L29 _public member_ `FTransform TargetRootBoneTransform = FTransform::Identity;`

#### struct `UE::UAF::FUAFWarpToTargetData`  
`struct FUAFWarpToTargetData : public FUAFModifierAnimNodeData`  
_L33-47_
- reflection: `USTRUCT(DisplayName = "Warp To Target")`
- inherits: `FUAFModifierAnimNodeData`
- L40 _public member_ `FBindableTransform RootBoneTransform;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — @TODO Temp / try to remove this. Shouldn't have to feed as argument Last root bone transform sampled
- L43 _public member_ `FBindableTransform TargetRootBoneTransform;` — `UPROPERTY(EditAnywhere, Category = Evaluation)`
- L46 _public prototype_ `virtual FUAFAnimNodePtr CreateInstance(FUAFAnimGraphUpdateContext& Context) const override;` — FUAFAnimNodeData impl

#### struct `UE::UAF::FUAFWarpToTargetNode`  
`struct FUAFWarpToTargetNode : FUAFModifierAnimNode`  
_L49-62_
- inherits: `FUAFModifierAnimNode`
- L51 _public prototype_ `FUAFWarpToTargetNode(FUAFAnimGraphUpdateContext& Context, const FUAFWarpToTargetData& InData);`
- L53 _public prototype_ `virtual void PreUpdate(FUAFAnimGraphUpdateContext& Context) override;`
- L56 _public prototype_ `virtual FString GetDebugName() const override;`
- L57 _public prototype_ `virtual UStruct* GetDebugStruct() const override;`
- L60 _private member_ `FUAFWarpToTargetPostAnimOp PostAnimOp;`
- L61 _private member_ `const FUAFWarpToTargetData* Data = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/OffsetRootBoneTrait.h` (Private)


#### enum `EUAFOffsetRootBoneMode`  
`enum class EUAFOffsetRootBoneMode : uint8`  
_L16-29_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Accumulate` — Accumulate the mesh component's movement into the offset. In this mode, if the mesh component moves the offset will counter the motion, and the root will stay in place
- L25 _public enumerator_ `Interpolate` — Continuously interpolate the offset out In this mode, if the mesh component moves The root will stay behind, but will attempt to catch up
- L28 _public enumerator_ `Release` — Release the offset and stop accumulating the mesh component's movement delta. In this mode we will "blend out" the offset

#### struct `FOffsetRootBoneTraitSharedData`  
`struct FOffsetRootBoneTraitSharedData : public FAnimNextTraitSharedData`  
_L33-129_
- reflection: `USTRUCT(meta = (DisplayName = "Offset Root Bone"))`
- inherits: `FAnimNextTraitSharedData`
- L39 _public member_ `FAnimNextTraitHandle Input;` — `UPROPERTY()` — Input pose to be processed
- L43 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Alpha, meta = (PinShownByDefault))` — Current strength of the skeletal control
- L47 _public member_ `EUAFOffsetRootBoneMode TranslationMode = EUAFOffsetRootBoneMode::Interpolate;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The translation offset behavior mode
- L51 _public member_ `EUAFOffsetRootBoneMode RotationMode = EUAFOffsetRootBoneMode::Interpolate;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The rotation offset behavior mode
- L56 _public member_ `float TranslationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls how fast the translation offset is blended out Values closer to 0 make it faster
- L61 _public member_ `float RotationSmoothingTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Controls how fast the rotation offset is blended out Values closer to 0 make it faster
- L66 _public member_ `float MaxTranslationError = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — How much the offset can deviate from the mesh component's translation in units Values lower than 0 disable this limit
- L71 _public member_ `float MaxRotationErrorDegrees = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — How much the offset can deviate from the mesh component's rotation in degrees Values lower than 0 disable this limit
- L76 _public member_ `bool bClampToTranslationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(Inline))` — Whether to limit the offset's translation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no translation speed
- L81 _public member_ `bool bClampToRotationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(Inline))` — Whether to limit the offset's rotation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no rotation speed
- L86 _public member_ `float TranslationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToTranslationVelocity, Inline))` — How much the offset can blend out, relative to the incoming translation speed i.e. If root motion is moving at 400cm/s, at 0.5, the offset can blend out at 200cm/s
- L91 _public member_ `float RotationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToRotationVelocity, Inline))` — How much the offset can blend out, relative to the incoming rotation speed i.e. If root motion is rotating at 90 degrees/s, at 0.5, the offset can blend out at 45 degree/s
- L96 _public member_ `FTransform MeshComponentTransformWorld = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — @TODO Temp / try to remove this. Shouldn't have to feed as argument This has to be the mesh component transform in world space
- L100 _public member_ `bool bOnGround = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Signals whether the offset root bone translation should be projected onto a projected ground plane
- L104 _public member_ `FVector AnimatedGroundNormal = { 0, 0, 1 };` — `UPROPERTY(EditAnywhere, Category = Settings)` — Surface normal that the current animation was authored for. Used with the bOnGround flag.
- L108 _public member_ `float TeleportDistanceThreshold = 300.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — Distance threshold used to detect teleports
- L112 _public member_ `bool bResetOnTeleport = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline))` — If to reset the root bone offset on teleport

#### struct `UE::UAF::FOffsetRootBoneTrait`  
`struct FOffsetRootBoneTrait : FBaseTrait, IUpdate, IEvaluate, IHierarchy`  
_L141-194_
- inherits: `FBaseTrait,IUpdate,IEvaluate,IHierarchy`
- L145 _public typedef_ `using FSharedData = FOffsetRootBoneTraitSharedData;`
- L186 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L189 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L192 _public prototype_ `virtual uint32 GetNumChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding) const override;` — IHierarchy impl
- L193 _public prototype_ `virtual void GetChildren(const FExecutionContext& Context, const TTraitBinding<IHierarchy>& Binding, FChildrenArray& Children) const override;`

#### struct `UE::UAF::FOffsetRootBoneTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L147-183_
- inherits: `FTrait::FInstanceData`
- L149 _public member_ `FTraitPtr Input;`
- L152 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L154 _public member_ `float Alpha = 1.0f;`
- L156 _public member_ `bool bIsFirstUpdate = true;`
- L158 _public member_ `FTransform LastMeshComponentTransformWorld = FTransform::Identity;`
- L159 _public member_ `FTransform MeshComponentTransformWorld = FTransform::Identity;`
- L161 _public member_ `EUAFOffsetRootBoneMode TranslationMode = EUAFOffsetRootBoneMode::Interpolate;`
- L162 _public member_ `EUAFOffsetRootBoneMode RotationMode = EUAFOffsetRootBoneMode::Interpolate;`
- L164 _public member_ `float TranslationSmoothingTime = 0.0f;`
- L165 _public member_ `float RotationSmoothingTime = 0.0f;`
- L166 _public member_ `float MaxTranslationError = -1.0f;`
- L167 _public member_ `float MaxRotationErrorDegrees = -1.0f;`
- L171 _public member_ `FVector SimulatedTranslation = FVector::ZeroVector;` — The simulated world-space transforms for the root bone with offset Offset = ComponentTransform - SimulatedTransform
- L172 _public member_ `FQuat SimulatedRotation = FQuat::Identity;`
- L174 _public member_ `FVector LastNonZeroRootMotionDirection = FVector::ZeroVector;`
- L176 _public member_ `bool bOnGround = true;`
- L177 _public member_ `FVector AnimatedGroundNormal = FVector::ZeroVector;`
- L181 _public member_ `TObjectPtr<const UObject> HostObject = nullptr;` — Debug Object for VisualLogger

#### struct `FAnimNextOffsetRootBoneTask`  
`struct FAnimNextOffsetRootBoneTask : public FAnimNextEvaluationTask`  
_L200-215_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task to run Offset Root Bone on VM
- L204 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextOffsetRootBoneTask) static FAnimNextOffsetRootBoneTask Make(UE::UAF::FOffsetRootBoneTrait::FInstanceData* InstanceData, const UE::UAF::FOffsetRootBoneTrait::FSharedData* SharedData);`
- L209 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L213 _private member_ `UE::UAF::FOffsetRootBoneTrait::FInstanceData* InstanceData = nullptr;`
- L214 _private member_ `const UE::UAF::FOffsetRootBoneTrait::FSharedData* SharedData = nullptr;`

#### Free symbols / members of external scopes

- L115 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L138 _namespace_ `namespace UE`
- L138 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/OverrideRootMotionTrait.h` (Private)


#### enum `EUAFOverrideRootMotionMode`  
`enum class EUAFOverrideRootMotionMode : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Replace`
- L18 _public enumerator_ `Additive`

#### struct `FOverrideRootMotionTraitSharedData`  
`struct FOverrideRootMotionTraitSharedData : public FAnimNextTraitSharedData`  
_L23-45_
- reflection: `USTRUCT(meta = (DisplayName = "Override Root Motion"))`
- inherits: `FAnimNextTraitSharedData`
- L29 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Current strength of the override
- L32 _public member_ `FTransform OverrideRootMotionDelta = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L35 _public member_ `EUAFOverrideRootMotionMode OverrideRootMotionMode = EUAFOverrideRootMotionMode::Replace;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `UE::UAF::FOverrideRootMotionTrait`  
`struct FOverrideRootMotionTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L55-70_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- desc: Override the root motion attributes with custom values. Ex: allows code driven motion to be injected into the animation system as root motion.
- L59 _public typedef_ `using FSharedData = FOverrideRootMotionTraitSharedData;`
- L66 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L69 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FOverrideRootMotionTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L61-63_
- inherits: `FTrait::FInstanceData`

#### struct `FAnimNextOverrideRootMotionTask`  
`struct FAnimNextOverrideRootMotionTask : public FAnimNextEvaluationTask`  
_L76-92_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task to run override root motion on VM
- L80 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextOverrideRootMotionTask) static FAnimNextOverrideRootMotionTask Make(float Alpha, FTransform OverrideRootMotionDelta, EUAFOverrideRootMotionMode OverrideRootMotionMode);`
- L85 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L89 _private member_ `float Alpha = 1.0f;`
- L90 _private member_ `FTransform OverrideRootMotionDelta = FTransform::Identity;`
- L91 _private member_ `EUAFOverrideRootMotionMode OverrideRootMotionMode = EUAFOverrideRootMotionMode::Replace;`

#### Free symbols / members of external scopes

- L38 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L47 _namespace_ `namespace UE`
- L47 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/SteeringTrait.h` (Private)


#### struct `FSteeringTraitSharedData`  
`struct FSteeringTraitSharedData : public FAnimNextTraitSharedData`  
_L27-82_
- reflection: `USTRUCT(meta = (DisplayName = "Steering"))`
- inherits: `FAnimNextTraitSharedData`
- desc: Data needed to execute steering Some steering data such as current anim asset / playback time is acquired via trait stack interfaces Add procedural delta to the root motion attribute This is done via 2 techniques: 1) Scaling the root motion on an animation 2) Adding additional correction to root motion after accounting for the anticipated (potentially scaled) root motion The effects of 1) and 2) combine
- L34 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Alpha, meta = (PinShownByDefault))` — @TODO: This should belong in a parent class possibly? Discuss review, make JIRA Current strength of the skeletal control
- L38 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(PinShownByDefault))` — The Orientation to steer towards
- L43 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — @TODO Temp / try to remove this. Shouldn't have to feed as argument Last root bone transform sampled
- L47 _public member_ `float ProceduralTargetTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(Inline))` — The number of seconds in the future before we should reach the TargetOrientation when play animations with no root motion rotation
- L51 _public member_ `float AnimatedTargetTime = 0.2f;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(Inline))` — The number of seconds in the future before we should reach the TargetOrientation when playing animations with root motion rotation
- L56 _public member_ `float RootMotionThreshold = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName=RootMotionAngleThreshold, Category=Evaluation, meta=(Inline))` — The minimum amount of root motion required to enable root motion scaling. The root motion is measured from current time to AnimatedTargetTime
- L60 _public member_ `float DisableSteeringBelowSpeed = 1.0f;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(Inline))` — below this movement speed (based on the root motion in the animation) disable steering completely (both scaling and additive)
- L64 _public member_ `float DisableAdditiveBelowSpeed = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, Meta=(Inline))` — below this movement speed (based on the root motion in the animation) disable steering coming from the additive spring based correction
- L68 _public member_ `float MinScaleRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, Meta = (Inline))` — Will clamp the scaling ratio applied to above this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L72 _public member_ `float MaxScaleRatio = 1.5f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, Meta = (Inline))` — Will clamp the scaling ratio applied to below this threashold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)

#### struct `UE::UAF::FSteeringTrait`  
`struct FSteeringTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L92-132_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- L96 _public typedef_ `using FSharedData = FSteeringTraitSharedData;`
- L128 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L131 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FSteeringTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L98-125_
- inherits: `FTrait::FInstanceData`
- L101 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — Target orientation per instance
- L104 _public member_ `FOnExtractRootMotionAttribute OnExtractRootMotionAttribute = FOnExtractRootMotionAttribute();` — Callback provided by attribute trait on stack to evaluate root motion at a later time
- L108 _public member_ `FVector AngularVelocity = FVector::ZeroVector;` — Angular velocity of additive correction spring
- L111 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — Last root bone transform sampled
- L114 _public member_ `float CurrentAnimAssetTime = 0.f;` — Current Anim Asset time, used with ProceduralTargetTime to get future root motion, populated during PostEvaluate
- L117 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L119 _public member_ `float Alpha = 1.0f;`
- L123 _public member_ `TObjectPtr<const UObject> HostObject = nullptr;` — Debug Object for VisualLogger

#### struct `FAnimNextSteeringTask`  
`struct FAnimNextSteeringTask : public FAnimNextEvaluationTask`  
_L138-151_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task to run Steering on VM
- L142 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextSteeringTask) static FAnimNextSteeringTask Make(UE::UAF::FSteeringTrait::FInstanceData* InstanceData, const UE::UAF::FSteeringTrait::FSharedData* SharedData);`
- L147 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L149 _public member_ `UE::UAF::FSteeringTrait::FInstanceData* InstanceData = nullptr;`
- L150 _public member_ `const UE::UAF::FSteeringTrait::FSharedData* SharedData = nullptr;`

#### Free symbols / members of external scopes

- L75 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L89 _namespace_ `namespace UE`
- L89 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/StrafeWarpingTrait.h` (Private)


#### enum `EStrafeWarpingFootMode`  
`enum class EStrafeWarpingFootMode : uint8`  
_L15-19_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `DoBasicIK`
- L18 _public enumerator_ `SetIKBoneOnly`

#### struct `FStrafeWarpFootData`  
`struct FStrafeWarpFootData`  
_L23-52_
- reflection: `USTRUCT()`
- desc: Small structure to define a simple IK setup for legs
- L31 _public member_ `FName LegRoot;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Used for basic IK performed on the node itself Only required if EStrafeWarpingFootMode is set to `DoBasicIK` e.g. the thigh bone
- L37 _public member_ `FName LegMid;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Used for basic IK performed on the node itself Only required if EStrafeWarpingFootMode is set to `DoBasicIK` e.g. the knee bone
- L42 _public member_ `FName LegTip;` — `UPROPERTY(EditAnywhere, Category=Settings)` — This bone is required in all modes e.g. the foot bone
- L47 _public member_ `FName IKTargetBone;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Set this bone to the IK target (in character space) Can be invalid
- L51 _public member_ `FVector JointSideVector = FVector::ZAxisVector;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Used for pole vector calculation. Should be the side of the knee in its local space

#### struct `FStrafeWarpingTraitSharedData`  
`struct FStrafeWarpingTraitSharedData : public FAnimNextTraitSharedData`  
_L55-147_
- reflection: `USTRUCT(meta = (DisplayName = "Strafe Warping"))`
- inherits: `FAnimNextTraitSharedData`
- L61 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Alpha, meta = (PinShownByDefault))` — Current strength of the skeletal control
- L65 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(PinShownByDefault))` — The Orientation to steer towards
- L70 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — @TODO Temp / try to remove this. Shouldn't have to feed as argument Last root bone transform sampled
- L74 _public member_ `TEnumAsByte<EAxis::Type> RotationAxis = EAxis::Z;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline))` — Rotation axis used when rotating the character body
- L78 _public member_ `float DistributedBoneOrientationAlpha = 0.5f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline, ClampMin="0.0", ClampMax="1.0", PinHiddenByDefault))` — Specifies how much rotation is applied to the character body versus IK feet
- L83 _public member_ `float RotationInterpSpeed = 10.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline, ClampMin="0.0"))` — Specifies the interpolation speed (in Alpha per second) towards reaching the final warped rotation angle A value of 0 will cause instantaneous rotation, while a greater value will introduce smoothing
- L88 _public member_ `float CounterCompensateInterpSpeed = 45.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (Inline, ClampMin = "0.0"))` — Same as RotationInterpSpeed, but for CounterCompensate smoothing. A value of 0 sample raw root motion. Used to avoid stuttering from resampling root deltas. Root motion is already smooth, so a large value is our default (~75% of 60 fps).
- L93 _public member_ `float MaxCorrectionDegrees = 180.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline, ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Max correction we're allowed to do per-second when using interpolation. This minimizes pops when we have a large difference between current and target orientation.
- L97 _public member_ `float MaxRootMotionDeltaToCompensateDegrees = 45.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline, ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Don't compensate our interpolator when the instantaneous root motion delta is higher than this. This is likely a pivot.
- L103 _public member_ `bool bCounterCompenstateInterpolationByRootMotion = true;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline, EditCondition="RotationInterpSpeed > 0.0f"))` — Whether to counter compensate interpolation by the animated root motion angle change over time. This helps to conserve the motion from our animation. Disable this if your root motion is expected to be jittery, and you want orientation warping to smooth it out.
- L109 _public member_ `float MinRootMotionSpeedThreshold = 10.0f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (ClampMin = "0.0", Inline))` — Minimum root motion speed required to apply orientation warping This is useful to prevent unnatural re-orientation when the animation has a portion with no root motion (i.e starts/stops/idles) When this value is greater than 0, it's recommended to enable interpolation with RotationInterpSpeed > 0
- L119 _public member_ `float LocomotionAngleDeltaThreshold = 90.f;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(Inline), meta=(ClampMin="0.0", ClampMax="180.0"))` — Specifies an angle threshold to prevent erroneous over-rotation of the character, disabled with a value of 0 When the effective orientation warping angle is detected to be greater than this value (default: 90 degrees) the locomotion direction will be inverted prior to warping This will be used in the following equation: [Orientation = RotationBetween(RootMotionDirection, -LocomotionDirection)] Example: Playing a forward running animation while the motion is going backward Rather than orientation warping by 180 degrees, the system will warp by 0 degrees
- L124 _public member_ `bool PreserveOriginalRootRotation = true;` — `UPROPERTY(EditAnywhere, Category=Evaluation, meta=(Inline))` — When true, propagates any modification on the root bone down to all of its children When false, will directly modify the root
- L131 _public member_ `TArray<FName> SpineBones;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline))` — Spine bone definitions Used to counter rotate the body in order to keep the character facing forward The amount of counter rotation applied is driven by DistributedBoneOrientationAlpha TODO: we ideally would use an equivlane to FBoneReference
- L134 _public member_ `TArray<FStrafeWarpFootData> FootData;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Bones"), meta=(Inline, Hidden))`
- L137 _public member_ `EStrafeWarpingFootMode FootMode = EStrafeWarpingFootMode::DoBasicIK;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Inline))`

#### struct `UE::UAF::FStrafeWarpingTrait`  
`struct FStrafeWarpingTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L155-229_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- L159 _public typedef_ `using FSharedData = FStrafeWarpingTraitSharedData;`
- L221 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L224 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L228 _public prototype_ `static void InitializeSpineData(TArrayView<FSpineBoneData> OutSpineBoneData, const TArray<FName>& SpineBoneNames, const FLODPoseStack& Pose);` — Helper for initialization of spine data Ideally this would be called once on trait become relevent, but we don't know the reference pose until Execute right now so must call it every frame

#### struct `UE::UAF::FStrafeWarpingTrait::FSpineBoneData`  
`struct FSpineBoneData`  
_L162-187_
- desc: Internal structure with some precomputed weight values and bone indices
- L164 _public member_ `FBoneIndexType LODBoneIndex;`
- L165 _public member_ `float Weight;`
- L167 _public function_ `FSpineBoneData() : LODBoneIndex(INDEX_NONE) , Weight(0.f)`
- L173 _public function_ `FSpineBoneData(FBoneIndexType InBoneIndex) : LODBoneIndex(InBoneIndex) , Weight(0.f)`

#### struct `UE::UAF::FStrafeWarpingTrait::FSpineBoneData::FCompareBoneIndex`  
`struct FCompareBoneIndex`  
_L180-186_
- desc: Comparison Operator for Sorting
- L182 _public function_ `FORCEINLINE bool operator()(const FSpineBoneData& A, const FSpineBoneData& B) const`

#### struct `UE::UAF::FStrafeWarpingTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L189-218_
- inherits: `FTrait::FInstanceData`
- L192 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — Target orientation per instance
- L195 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — Last root bone transform sampled
- L198 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L200 _public member_ `float Alpha = 1.0f;`
- L203 _public member_ `FVector RootMotionDeltaDirection = FVector::ZeroVector;` — Internal current frame root motion delta direction
- L206 _public member_ `FQuat RootMotionDeltaRotation = FQuat::Identity;` — Internal current frame root motion delta angle
- L209 _public member_ `float CounterCompensateTargetAngleRad = 0.0f;` — Target for counter compenstate, we keep the target so we can smoothly interp.
- L212 _public member_ `float OrientationAngleForPoseWarpRad = 0.f;` — Internal orientation warping angle
- L216 _public member_ `TObjectPtr<const UObject> HostObject = nullptr;` — Debug Object for VisualLogger

#### struct `FAnimNextStrafeWarpingTask`  
`struct FAnimNextStrafeWarpingTask : public FAnimNextEvaluationTask`  
_L235-252_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task to run Strafe Warping on VM
- L239 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextStrafeWarpingTask) static FAnimNextStrafeWarpingTask Make(UE::UAF::FStrafeWarpingTrait::FInstanceData* InstanceData, const UE::UAF::FStrafeWarpingTrait::FSharedData* SharedData);`
- L244 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L247 _private prototype_ `void DoWarpRootMotion(TUniquePtr<UE::UAF::FKeyframeState>& KeyframeState, const FVector& RotationAxisVector, const FVector& TargetMoveDir, float& OutTargetOrientationAngleRad) const;`
- L248 _private prototype_ `void DoWarpPose(TUniquePtr<UE::UAF::FKeyframeState>& KeyframeState, const FVector& RotationAxisVector) const;`
- L250 _private member_ `UE::UAF::FStrafeWarpingTrait::FInstanceData* InstanceData = nullptr;`
- L251 _private member_ `const UE::UAF::FStrafeWarpingTrait::FSharedData* SharedData = nullptr;`

#### Free symbols / members of external scopes

- L140 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L152 _namespace_ `namespace UE`
- L152 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/UAF/UAFWarping/Source/UAFWarping/Private/WarpTestTrait.h` (Private)


#### struct `FWarpTestTraitSharedData`  
`struct FWarpTestTraitSharedData : public FAnimNextTraitSharedData`  
_L13-31_
- reflection: `USTRUCT(Experimental, meta = (DisplayName = "WarpTest"))`
- inherits: `FAnimNextTraitSharedData`
- L19 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — the trait will warp the character looping between Transforms[i] choosing the next one every SecondsToWait
- L23 _public member_ `float SecondsToWait = 1.f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — every SecondsToWait we warp to the next Transforms[i]

#### struct `UE::UAF::FWarpTestTrait`  
`struct FWarpTestTrait : FAdditiveTrait, IUpdate, IEvaluate`  
_L36-53_
- inherits: `FAdditiveTrait,IUpdate,IEvaluate`
- L40 _public typedef_ `using FSharedData = FWarpTestTraitSharedData;`
- L49 _public prototype_ `virtual void PreUpdate(FUpdateTraversalContext& Context, const TTraitBinding<IUpdate>& Binding, const FTraitUpdateState& TraitState) const override;` — IUpdate impl
- L52 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl

#### struct `UE::UAF::FWarpTestTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L42-46_
- inherits: `FTrait::FInstanceData`
- L44 _public member_ `int32 CurrentTransformIndex = 0;`
- L45 _public member_ `float CurrentTime = 0.f;`

#### struct `FAnimNextWarpTestTask`  
`struct FAnimNextWarpTestTask : public FAnimNextEvaluationTask`  
_L58-73_
- reflection: `USTRUCT(Experimental)`
- inherits: `FAnimNextEvaluationTask`
- L62 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextWarpTestTask) virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;`
- L66 _public member_ `FTransform ComponentTransform = FTransform::Identity;`
- L67 _public member_ `FTransform WarpToTransform = FTransform::Identity;`
- L71 _public member_ `const UObject* HostObject = nullptr;` — Debug Object for VisualLogger

#### Free symbols / members of external scopes

- L25 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace UAF` (scope `UE`)
