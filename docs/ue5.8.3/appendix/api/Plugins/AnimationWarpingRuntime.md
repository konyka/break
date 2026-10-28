# Plugins / AnimationWarpingRuntime

- module root: `Plugins/Animation/AnimationWarping/Source/Runtime`
- headers: 11; symbols: 544
- symbol kinds: class=3, enum=7, enumerator=25, function=18, macro=11, member=327, namespace=5, prototype=110, struct=37, typedef=1
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core, CoreUObject, Engine

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/AnimationWarpingLibrary.h` (Public)


#### struct `FOffsetRootBoneAnimNodeReference`  
`struct FOffsetRootBoneAnimNodeReference : public FAnimNodeReference`  
_L17-22_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L21 _public typedef_ `typedef FAnimNode_OffsetRootBone FInternalNodeType;`

#### class `UAnimationWarpingLibrary`  
`class UAnimationWarpingLibrary : public UBlueprintFunctionLibrary`  
_L26-55_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations related to Animation Warping
- L33 _public prototype_ `static FTransform GetOffsetRootTransform(const FAnimNodeReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|BlendStack", meta = (BlueprintThreadSafe))` — Get the current world space transform from the offset root bone animgraph node
- L37 _public prototype_ `static bool GetCurveValueFromAnimation(const UAnimSequenceBase* Animation, FName CurveName, float Time, float& OutValue);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe))` — Helper function to extract the value of a curve in an animation at a given time
- L41 _public prototype_ `static bool GetFloatValueFromCurve(const UCurveFloat* InCurve, float Time, float& OutValue);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe))` — Helper function to extract the float value from a curve asset at a given time. To be used inside AnimationBlueprint and assumes AnimBP holds reference to CurveAsset for it to be valid.
- L45 _public prototype_ `static bool GetVectorValueFromCurve(const UCurveVector* InCurve, float Time, FVector& OutValue);` — `UFUNCTION(BlueprintPure, Category = "Animation", meta = (BlueprintThreadSafe))` — Helper function to extract the vector value from a curve asset at a given time. To be used inside AnimationBlueprint and assumes AnimBP holds reference to CurveAsset for it to be valid.
- L49 _public prototype_ `static void ConvertToOffsetRootBoneNodePure(const FAnimNodeReference& Node, FOffsetRootBoneAnimNodeReference& OffsetRootBoneNode, bool& Result);` — `UFUNCTION(BlueprintPure, Category = "Animation|Offset Root Bone", meta = (BlueprintThreadSafe, DisplayName = "Convert to Offset Root Bone node"))` — Get a root bone offset node context from an anim node context
- L54 _public prototype_ `static void ApplyDeltaToOffsetRootBone(const FOffsetRootBoneAnimNodeReference& OffsetRootBoneNode, FVector TranslationWorld, FQuat RotationWorld);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Offset Root Bone", meta = (BlueprintThreadSafe))` — Apply a delta translation and rotation to the simulated transform inside a offset root bone node. This is useful for moving the root bone offset, e.g. when standing on a moving platform

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/AnimationWarpingRuntimeModule.h` (Public)


#### class `IAnimationWarpingRuntimeModule`  
`class IAnimationWarpingRuntimeModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/AnimationWarpingTypes.h` (Public)


#### enum `EOffsetRootBoneMode`  
`enum class EOffsetRootBoneMode : uint8`  
_L9-31_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Accumulate` — Accumulate the mesh component's movement into the offset. In this mode, if the mesh component moves the offset will counter the motion, and the root will stay in place
- L18 _public enumerator_ `Interpolate` — Continuously interpolate the offset out In this mode, if the mesh component moves The root will stay behind, but will attempt to catch up
- L21 _public enumerator_ `LockOffsetAndConsumeAnimation` — Stops accumulating the mesh component's movement delta into the root offset In this mode, whatever offset we have will be locked but we will still consume animated root motion
- L24 _public enumerator_ `LockOffsetIncreaseAndConsumeAnimation` — Stops accumulating the mesh component's movement delta into the root offset In this mode, whatever offset we have will be locked but we will still consume animated root motion, as long as it's decreasing the offset.
- L27 _public enumerator_ `LockOffsetAndIgnoreAnimation` — Stops accumulating the mesh component's movement delta into the root offset In this mode, whatever offset we have will be locked and we will ignore animated root motion
- L30 _public enumerator_ `Release` — Release the offset and stop accumulating the mesh component's movement delta. In this mode we will "blend out" the offset

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_FootPlacement.h` (Public)


#### enum `UE::Anim::FootPlacement::EPlantType`  
`enum class EPlantType`  
_L27-32_
- L29 _public enumerator_ `Unplanted`
- L30 _public enumerator_ `Planted`
- L31 _public enumerator_ `Replanted`

#### struct `UE::Anim::FootPlacement::FLegRuntimeData`  
`struct FLegRuntimeData`  
_L34-122_
- L36 _public member_ `int32 Idx = -1;`
- L47 _public member_ `} Bones;`
- L49 _public member_ `FName SpeedCurveName = NAME_None;`
- L50 _public member_ `FName DisableLockCurveName = NAME_None;`
- L51 _public member_ `FName DisableLegCurveName = NAME_None;`
- L75 _public member_ `} InputPose;`
- L98 _public member_ `} Plant;`
- L101 _public member_ `FTransform AlignedFootTransformWS = FTransform::Identity;` — Ground-aligned, locked/unlocked bone transform pre-extension adjustments
- L102 _public member_ `FTransform AlignedFootTransformRS = FTransform::Identity;`
- L104 _public member_ `FTransform UnalignedFootTransformWS = FTransform::Identity;` — Foot locked/unlocked bone transform, before ground alignment
- L105 _public member_ `FTransform UnalignedFootTransformRS = FTransform::Identity;`
- L121 _public member_ `} Interpolation;`

#### struct `UE::Anim::FootPlacement::FLegRuntimeData::FBoneData`  
`struct FBoneData`  
_L39-47_
- desc: Bone information that can be cached once per-lod change.
- L41 _public member_ `FCompactPoseBoneIndex FKIndex = FCompactPoseBoneIndex(INDEX_NONE);`
- L42 _public member_ `FCompactPoseBoneIndex BallIndex = FCompactPoseBoneIndex(INDEX_NONE);`
- L43 _public member_ `FCompactPoseBoneIndex IKIndex = FCompactPoseBoneIndex(INDEX_NONE);`
- L44 _public member_ `FCompactPoseBoneIndex HipIndex = FCompactPoseBoneIndex(INDEX_NONE);`
- L45 _public member_ `float LimbLength = 0.0f;`
- L46 _public member_ `float FootLength = 0.0f;`

#### struct `UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData`  
`struct FInputPoseData`  
_L54-75_
- desc: Helper struct to store values coming directly, or trivial to calculate from just the input pose.
- L56 _public member_ `FTransform FootFKTransformCS = FTransform::Identity;`
- L57 _public member_ `FTransform FootTransformCS = FTransform::Identity;`
- L58 _public member_ `FTransform BallTransformCS = FTransform::Identity;`
- L59 _public member_ `FTransform HipTransformCS = FTransform::Identity;`
- L60 _public member_ `FTransform BallToFoot = FTransform::Identity;`
- L61 _public member_ `FTransform FootToBall = FTransform::Identity;`
- L65 _public member_ `FTransform FootToGround = FTransform::Identity;` — These are only used for debug draw at the moment @TODO: Use this info to more precisely figure out foot dimensions
- L66 _public member_ `FTransform BallToGround = FTransform::Identity;`
- L68 _public member_ `float Speed = 0.0f;`
- L69 _public member_ `float DisableLeg = 0.0f;`
- L70 _public member_ `float LockAlpha = 0.0f;`
- L71 _public member_ `float DistanceToPlant = 0.0f;`
- L74 _public member_ `float AlignmentAlpha = 0.0f;` — Calculated from a range of toe speeds to define when to blend in/out ground rotational alignment @TODO: When we have prediction/phase info, replac with roll-phase alpha

#### struct `UE::Anim::FootPlacement::FLegRuntimeData::FPlantData`  
`struct FPlantData`  
_L79-98_
- L81 _public member_ `UE::Anim::FootPlacement::EPlantType PlantType = UE::Anim::FootPlacement::EPlantType::Unplanted;`
- L82 _public member_ `UE::Anim::FootPlacement::EPlantType LastPlantType = UE::Anim::FootPlacement::EPlantType::Unplanted;`
- L83 _public member_ `FPlane PlantPlaneRS = FPlane(FVector::UpVector, 0.0f);`
- L84 _public member_ `FQuat TwistCorrection = FQuat::Identity;`
- L86 _public member_ `float TimeSinceFullyUnaligned = 0.0f;` — @TODO: When we have prediction/phase info, replace use-cases with post-plant roll-phase
- L88 _public member_ `bool bCanReachTarget = false;` — Whether the planted/locked target has ever been reachable this plant
- L90 _public member_ `bool bWantsToPlant = false;` — Whether we want to plant, independently from any dynamic pose adjustments we may do
- L92 _public function_ `FPlane GetPlantPlaneCS(const FTransform& RootToComponent) const`
- L93 _public function_ `FPlane GetPlantPlaneWS(const FTransform& RootToComponent, const FTransform& ComponentToWorld) const`

#### struct `UE::Anim::FootPlacement::FLegRuntimeData::FInterpolationData`  
`struct FInterpolationData`  
_L108-121_
- desc: Interpolation
- L111 _public member_ `FTransform UnalignedFootOffset = FTransform::Identity;` — Interpolated foot lock offset
- L113 _public member_ `FVectorSpringState SeparatingPlaneOffsetSpringState;` — Separating plane spring states
- L114 _public member_ `FVector SeparatingPlaneOffset = FVector::ZeroVector;`
- L116 _public member_ `FVectorSpringState PlantOffsetTranslationSpringState;` — Foot lock spring states
- L117 _public member_ `FQuaternionSpringState PlantOffsetRotationSpringState;`
- L119 _public member_ `FFloatSpringState GroundHeightSpringState;` — Ground alignment spring states
- L120 _public member_ `FQuaternionSpringState GroundRotationSpringState;`

#### struct `UE::Anim::FootPlacement::FPlantRuntimeSettings`  
`struct FPlantRuntimeSettings`  
_L124-130_
- L126 _public member_ `float UnplantRadiusSqrd = 0.0f;`
- L127 _public member_ `float ReplantRadiusSqrd = 0.0f;`
- L128 _public member_ `float CosHalfUnplantAngle = 0.0f;`
- L129 _public member_ `float CosHalfReplantAngle = 0.0f;`

#### struct `UE::Anim::FootPlacement::FPelvisRuntimeData`  
`struct FPelvisRuntimeData`  
_L132-163_
- L139 _public member_ `} Bones;`
- L142 _public member_ `float MaxOffsetSqrd = 0.0f;` — Settings-based properties
- L151 _public member_ `} InputPose;`
- L159 _public member_ `} Interpolation;`
- L162 _public member_ `float DisablePelvis = 0.0f;`

#### struct `UE::Anim::FootPlacement::FPelvisRuntimeData::FBones`  
`struct FBones`  
_L135-139_
- desc: Bone IDs
- L137 _public member_ `FCompactPoseBoneIndex FkBoneIndex = FCompactPoseBoneIndex(INDEX_NONE);`
- L138 _public member_ `FCompactPoseBoneIndex IkBoneIndex = FCompactPoseBoneIndex(INDEX_NONE);`

#### struct `UE::Anim::FootPlacement::FPelvisRuntimeData::FInputPoseData`  
`struct FInputPoseData`  
_L145-151_
- desc: Input pose properties
- L147 _public member_ `FTransform FKTransformCS = FTransform::Identity;`
- L148 _public member_ `FTransform IKRootTransformCS = FTransform::Identity;`
- L149 _public member_ `FTransform RootTransformCS = FTransform::Identity;`
- L150 _public member_ `FVector FootMidpointCS = FVector::ZeroVector;`

#### struct `UE::Anim::FootPlacement::FPelvisRuntimeData::FInterpolationData`  
`struct FInterpolationData`  
_L154-159_
- desc: Interpolation
- L157 _public member_ `FVector PelvisTranslationOffset = FVector::ZeroVector;` — Current pelvis offset and spring states. We use a 3d vector because this interpolates weight rebalancing too.
- L158 _public member_ `FVectorSpringState PelvisTranslationSpringState;`

#### struct `UE::Anim::FootPlacement::FCharacterData`  
`struct FCharacterData`  
_L165-173_
- L167 _public member_ `FTransform ComponentTransformWS = FTransform::Identity;`
- L168 _public member_ `FVector ComponentMoveDeltaWS = FVector::ZeroVector;`
- L169 _public member_ `FVector CharacterVelocityWS = FVector::ZeroVector;`
- L170 _public member_ `FVector SmoothCapsuleGroundNormalWS = FVector::ZeroVector;`
- L171 _public member_ `FQuaternionSpringState SmoothCapsuleGroundNormalSpringState;`
- L172 _public member_ `bool bIsOnGround = false;`

#### struct `UE::Anim::FootPlacement::FPlantResult`  
`struct FPlantResult`  
_L176-184_
- desc: Final result after post-adjustments (extension checks, heel lift, etc.)
- L179 _public member_ `FBoneTransform FootTranformCS;`

#### struct `UE::Anim::FootPlacement::FDebugData`  
`struct FDebugData`  
_L187-210_
- L189 _public member_ `FVector OutputPelvisLocationWS = FVector::ZeroVector;`
- L190 _public member_ `FVector InputPelvisLocationWS = FVector::ZeroVector;`
- L192 _public member_ `TArray<FVector> OutputFootLocationsWS;`
- L193 _public member_ `TArray<FVector> InputFootLocationsWS;`
- L202 _public member_ `TArray<FLegInfo> LegsInfo;`
- L204 _public function_ `void Init(const int32 InSize)`

#### struct `UE::Anim::FootPlacement::FDebugData::FLegInfo`  
`struct FLegInfo`  
_L195-201_
- L197 _public member_ `float HyperExtensionAmount;`
- L198 _public member_ `float RollAmount;`
- L199 _public member_ `float PullAmount;`
- L200 _public member_ `float DistanceToSeparatingPlane;`

#### enum `EFootPlacementLockType`  
`enum class EFootPlacementLockType : uint8`  
_L217-228_
- reflection: `UENUM(BlueprintType)`
- L220 _public enumerator_ `Unlocked` — Foot is unlocked but free to move
- L222 _public enumerator_ `PivotAroundBall` — Foot can lock, and will pivot around its ball/toes.
- L224 _public enumerator_ `PivotAroundAnkle` — Foot can lock, and will pivot around the ankle/foot bone.
- L226 _public enumerator_ `LockRotation` — Foot is fully locked. Useful for bigger/mechanical creatures

#### struct `FFootPlacementInterpolationSettings`  
`struct FFootPlacementInterpolationSettings`  
_L231-274_
- reflection: `USTRUCT(BlueprintType)`
- L237 _public member_ `float UnplantLinearStiffness = 250.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L240 _public member_ `float UnplantLinearDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L243 _public member_ `float UnplantAngularStiffness = 450.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L246 _public member_ `float UnplantAngularDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L249 _public member_ `float SeparationStiffness = 1000.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableSeparationInterpolation", DisplayAfter="bEnableSeparationInterpolation"))`
- L252 _public member_ `float SeparationDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableSeparationInterpolation", DisplayAfter="bEnableSeparationInterpolation"))`
- L255 _public member_ `float FloorLinearStiffness = 1000.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableFloorInterpolation", DisplayAfter="bEnableFloorInterpolation"))`
- L258 _public member_ `float FloorLinearDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableFloorInterpolation", DisplayAfter="bEnableFloorInterpolation"))`
- L261 _public member_ `float FloorAngularStiffness = 450.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableFloorInterpolation", DisplayAfter="bEnableFloorInterpolation"))`
- L264 _public member_ `float FloorAngularDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(EditCondition="bEnableFloorInterpolation", DisplayAfter="bEnableFloorInterpolation"))`
- L267 _public member_ `bool bEnableFloorInterpolation = true;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L270 _public member_ `bool bSmoothRootBone = false;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L273 _public member_ `bool bEnableSeparationInterpolation = true;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`

#### struct `FFootPlacementTraceSettings`  
`struct FFootPlacementTraceSettings`  
_L277-316_
- reflection: `USTRUCT(BlueprintType)`
- L285 _public member_ `float StartOffset = -75.0f;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta=(EditCondition="bEnabled", DisplayAfter="bEnabled"))` — A negative value extends the trace length above the bone
- L289 _public member_ `float EndOffset = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta=(EditCondition="bEnabled", DisplayAfter="bEnabled"))` — A positive value extends the trace length below the bone
- L294 _public member_ `float SweepRadius = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta=(EditCondition="bEnabled", DisplayAfter="bEnabled"))` — The trace is a sphere sweep with this radius. It should be big enough to prevent the trace from going through small geometry gaps
- L297 _public member_ `bool bDisableComplexTrace = false;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta=(EditCondition="bEnabled", DisplayAfter="bEnabled"))`
- L301 _public member_ `TEnumAsByte<ETraceTypeQuery> ComplexTraceChannel = TraceTypeQuery1;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta=(EditCondition="!bDisableComplexTrace", DisplayAfter="bDisableComplexTrace"))` — The channel to use for our complex trace
- L306 _public member_ `float MaxGroundPenetration = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")` — How much the feet can penetrate the ground geometry. It's recommended to allow some to account for interpolation Negative values disable this effect
- L310 _public member_ `TEnumAsByte<ETraceTypeQuery> SimpleTraceChannel = TraceTypeQuery1;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings", meta = (EditCondition = "bEnabled", DisplayAfter = "bEnabled"))` — The channel to use for our simple trace
- L315 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")` — Enabling tracing for ground alignment @TODO: Use ground normal when not tracing

#### struct `FFootPlacementRootDefinition`  
`struct FFootPlacementRootDefinition`  
_L319-332_
- reflection: `USTRUCT()`
- L325 _public member_ `FBoneReference PelvisBone;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")`
- L328 _public member_ `FBoneReference IKRootBone;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")`
- L331 _public prototype_ `void Initialize(const FAnimationInitializeContext& Context);`

#### enum `EPelvisHeightMode`  
`enum class EPelvisHeightMode : uint8`  
_L335-348_
- reflection: `UENUM(BlueprintType)`
- L339 _public enumerator_ `AllLegs` — Consider all legs for pelvis height, whether they're planted or not Generally good for flat/not too steep ground
- L342 _public enumerator_ `AllPlantedFeet` — Consider only the planted feet when calculating pelvis height Generally good we pelvis height to be defined by the weight supporting leg
- L347 _public enumerator_ `FrontPlantedFeetUphill_FrontFeetDownhill` — When moving uphill, use the front foot, as long as it's planted. It's recommended to also enable pelvis interpolation to smooth out the swap between what's considered the "planted" leg When moving downhill, both feet will be considered relevant. The algorithm tends to prefer the lower foot, except when the higher foot would become over-compresseed.

#### enum `EActorMovementCompensationMode`  
`enum class EActorMovementCompensationMode : uint8`  
_L351-359_
- reflection: `UENUM(BlueprintType)`
- L354 _public enumerator_ `ComponentSpace` — Keep pelvis component-space and follow along all of the actor's vertical ground movement. Use when you have really smooth ground geometry, or if you have moving platforms.
- L356 _public enumerator_ `WorldSpace` — Hold pelvis world-space and ignore the actor's vertical ground movement. Let springs interpolate the difference
- L358 _public enumerator_ `SuddenMotionOnly` — Keep pelvis component-space, but hold world-space transform when the actor does sudden changes (i.e. a big step), and let springs interpolate the difference. Does not work on moving platforms.

#### struct `FFootPlacementPelvisSettings`  
`struct FFootPlacementPelvisSettings`  
_L362-412_
- reflection: `USTRUCT(BlueprintType)`
- L370 _public member_ `float MaxOffset = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")` — Max vertical offset from the input pose for the Pelvis. Reaching this limit means the feet may not reach their plant plane
- L373 _public member_ `float LinearStiffness = 350.0f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta=(EditCondition="bEnableInterpolation", DisplayAfter="bEnableInterpolation"))`
- L376 _public member_ `float LinearDamping = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta=(EditCondition="bEnableInterpolation", DisplayAfter="bEnableInterpolation"))`
- L382 _public member_ `float HorizontalRebalancingWeight = 0.3f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0", DisplayAfter="bEnableInterpolation"))` — How much we move the pelvis horizontally to re-balance the characters weight due to foot offsets. A value of 0 will disable this effect. Higher values may move the mesh outside of the character's capsule
- L388 _public member_ `float MaxOffsetHorizontal = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta=(DisplayAfter="bEnableInterpolation"))` — Max horizontal foot adjustment we consider to lower the hips This can be used to prevent the hips from dropping too low when the feet are locked Exceeding this value will first attempt to roll the planted feet, and then slide
- L394 _public member_ `float HeelLiftRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0", DisplayAfter="bEnableInterpolation"))` — How much we prefer lifting the heel before dropping the hips to achieve the desired pose. 1 fully favors heel lift first. 0 fully favors pelvis drop first.
- L397 _public member_ `EPelvisHeightMode PelvisHeightMode = EPelvisHeightMode::AllLegs;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta=(DisplayAfter="bEnableInterpolation"))`
- L402 _public member_ `EActorMovementCompensationMode ActorMovementCompensationMode = EActorMovementCompensationMode::SuddenMotionOnly;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings", meta=(DisplayAfter="bEnableInterpolation"))` — This is used to hold the Pelvis's interpolator in a fixed spot when the capsule moves up/down If your camera is directly attached to the character with little to no smoothing, you may want this on ComponentSpace
- L405 _public member_ `bool bEnableInterpolation = true;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")`
- L408 _public member_ `bool bDisablePelvisOffsetInAir = true;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")`
- L411 _public member_ `FName DisablePelvisCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Pelvis Settings")`

#### struct `FFootPlacemenLegDefinition`  
`struct FFootPlacemenLegDefinition`  
_L415-451_
- reflection: `USTRUCT()`
- L422 _public member_ `FBoneReference FKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Bone to be planted. For feet, use the heel/ankle joint.
- L426 _public member_ `FBoneReference IKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — TODO: can we optionally output as an attribute?
- L430 _public member_ `FBoneReference BallBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Secondary plant bone. For feet, use the ball joint.
- L433 _public member_ `int32 NumBonesInLimb = 2;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L437 _public member_ `FName SpeedCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the curve representing the foot/ball speed. Not required in Graph speed mode
- L442 _public member_ `FName DisableLockCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the curve representing the alpha of the locking alpha. This allows you to disable locking precisely, instead of relying on the procedural mechanism based on springs and foot analysis
- L446 _public member_ `FName DisableLegCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Curve to disable the effect of footplacement on this leg
- L450 _public prototype_ `void InitializeBoneReferences(const FBoneContainer& RequiredBones);`

#### struct `FFootPlacementPlantSettings`  
`struct FFootPlacementPlantSettings`  
_L454-519_
- reflection: `USTRUCT(BlueprintType)`
- L462 _public member_ `float SpeedThreshold = 60.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — Bone is considered planted below this speed. Value is obtained from FKSpeedCurveName
- L466 _public member_ `float DistanceToGround = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — At this distance from the planting plane the bone is considered planted and will be fully aligned.
- L469 _public member_ `EFootPlacementLockType LockType = EFootPlacementLockType::PivotAroundBall;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")`
- L473 _public member_ `float UnplantRadius = 35.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — How much linear deviation causes the constraint to be released
- L477 _public member_ `float ReplantRadiusRatio = 0.35f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Below this value, proportional to UnplantRadius, the bone will replant
- L481 _public member_ `float UnplantAngle = 45.0;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — How much angular deviation (in degrees) causes the constraint to be released for replant
- L485 _public member_ `float ReplantAngleRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Below this value, proportional to UnplantAngle, the bone will replant
- L489 _public member_ `float MaxExtensionRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Max extension ratio of the chain, calculated from the remaining length between current pose and full limb extension
- L493 _public member_ `float MinExtensionRatio = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — Min extension ratio of the chain, calculated from the total limb length, and adjusted along the approach direction
- L498 _public member_ `float SeparatingDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The minimum distance the feet can be from the plane that separates the feet. Value of 0 disables this
- L504 _public member_ `float UnalignmentSpeedThreshold = 200.0f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — Speed at which we transition to fully unplanted. The range between SpeedThreshold and UnalignmentSpeedThreshold should roughly represent the roll-phase of the foot TODO: This feels innaccurate most of the time, and varies depending on anim speed. Improve this
- L508 _public member_ `float AnkleTwistReduction = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))` — How much we reduce the procedural ankle twist adjustment used to align the foot to the ground slope.
- L512 _public member_ `bool bReconstructWorldPlantFromVelocity = false;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — Only consider world deltas caused by played velocity. This is useful when on a moving platform i.e. but won't consider slopes.
- L516 _public member_ `bool bAdjustHeelBeforePlanting = false;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings")` — Whether to allow adjusting the heel lift before we plant
- L518 _public prototype_ `void Initialize(const FAnimationInitializeContext& Context);`

#### struct `FAnimNode_FootPlacement`  
`struct FAnimNode_FootPlacement : public FAnimNode_SkeletalControlBase`  
_L523-719_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_SkeletalControlBase`
- L533 _public member_ `EWarpingEvaluationMode PlantSpeedMode = EWarpingEvaluationMode::Manual;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Foot/Ball speed evaluation mode (Graph or Manual) used to decide when the feet are locked Graph mode uses the root motion attribute from the animations to calculate the joint's speed Manual mode uses a per-foot curve name representing the joint's speed
- L536 _public member_ `FBoneReference IKFootRootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L539 _public member_ `FBoneReference PelvisBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L542 _public member_ `FFootPlacementPelvisSettings PelvisSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinHiddenByDefault))`
- L545 _public member_ `TArray<FFootPlacemenLegDefinition> LegDefinitions;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L548 _public member_ `FFootPlacementPlantSettings PlantSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinHiddenByDefault))`
- L551 _public member_ `FFootPlacementInterpolationSettings InterpolationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinHiddenByDefault))`
- L554 _public member_ `FFootPlacementTraceSettings TraceSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (PinHiddenByDefault))`
- L557 _public member_ `FVector BaseTranslationDelta = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))`
- L560 _public prototype_ `FAnimNode_FootPlacement();`
- L563 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L567 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L568 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L569 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread( FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L572 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L577 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L581 _private prototype_ `void GatherPelvisDataFromInputs(const UE::Anim::FootPlacement::FEvaluationContext& Context);` — Gather raw or trivially calculated values from input pose
- L582 _private prototype_ `void GatherLegDataFromInputs( const UE::Anim::FootPlacement::FEvaluationContext& Context, UE::Anim::FootPlacement::FLegRuntimeData& LegData, const FFootPlacemenLegDefinition& LegDef);`
- L587 _private prototype_ `void CalculateFootMidpoint( const UE::Anim::FootPlacement::FEvaluationContext& Context, TConstArrayView<UE::Anim::FootPlacement::FLegRuntimeData> LegData, FVector& OutMidpoint) const;`
- L593 _private prototype_ `void ProcessCharacterState(const UE::Anim::FootPlacement::FEvaluationContext& Context);` — Calculate procedural adjustments before solving the desired pelvis position
- L594 _private prototype_ `void ProcessFootAlignment( const UE::Anim::FootPlacement::FEvaluationContext& Context, UE::Anim::FootPlacement::FLegRuntimeData& LegData);`
- L599 _private prototype_ `FTransform SolvePelvis(const UE::Anim::FootPlacement::FEvaluationContext& Context);` — Calculate the desired pelvis offset, based on procedural character/foot adjustments
- L601 _private prototype_ `FTransform UpdatePelvisInterpolationRootSpace( const UE::Anim::FootPlacement::FEvaluationContext& Context, const FTransform& TargetPelvisTransform);`
- L606 _private prototype_ `UE::Anim::FootPlacement::FPlantResult FinalizeFootAlignment( const UE::Anim::FootPlacement::FEvaluationContext& Context, UE::Anim::FootPlacement::FLegRuntimeData& LegData, const FFootPlacemenLegDefinition& LegDef, const FTransform& PelvisTransformCS);` — Post-processing adjustments + fix hyper-extension/compression
- L612 _private prototype_ `FVector GetApproachDirWS(const FAnimationBaseContext& Context) const;`
- L614 _private prototype_ `const FTransform& GetRootToComponent() const;`
- L617 _private member_ `float CachedDeltaTime = 0.0f;`
- L618 _private member_ `FVector LastComponentLocation = FVector::ZeroVector;`
- L620 _private member_ `TArray<UE::Anim::FootPlacement::FLegRuntimeData> LegsData;`
- L621 _private member_ `UE::Anim::FootPlacement::FPlantRuntimeSettings PlantRuntimeSettings;`
- L622 _private member_ `UE::Anim::FootPlacement::FPelvisRuntimeData PelvisData;`
- L623 _private member_ `UE::Anim::FootPlacement::FCharacterData CharacterData;`
- L626 _private prototype_ `bool WantsToPlant( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose) const;` — Whether we want to plant, independently from any dynamic pose adjustments we may do
- L633 _private prototype_ `float GetAlignmentAlpha( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose) const;` — Get Alignment Alpha based on current foot speed 0.0 is fully unaligned and the foot is in flight. 1.0 is fully aligned and the foot is planted.
- L639 _private prototype_ `float CalcTargetPlantPlaneDistance( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose) const;` — This function looks at both the foot bone and the ball bone, returning the smallest distance to the planting plane. Note this distance can be negative, meaning it's penetrating.
- L651 _private prototype_ `void FindPelvisOffsetRangeForLimb( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData& LegData, const FVector& PlantTargetLocationCS, const FTransform& PelvisTransformCS, FPelvisOffsetRangeForLimb& OutPelvisOffsetRangeCS) const;` — Find the horizontal pelvis offset range for the foot to reach:
- L659 _private prototype_ `FTransform GetFootPivotAroundBallWS( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose, const FTransform& LastPlantTransformWS) const;` — Adjust LastPlantTransformWS to current, to have the foot pivot around the ball instead of the ankle
- L666 _private prototype_ `void AlignPlantToGround( const UE::Anim::FootPlacement::FEvaluationContext& Context, const FPlane& PlantPlaneWS, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose, FTransform& InOutFootTransformWS, FQuat& OutTwistCorrection) const;` — Align the transform the provided world space ground plant plane. Also outputs the twist along the ground plane needed to get there
- L674 _private prototype_ `FTransform UpdatePlantOffsetInterpolation( const UE::Anim::FootPlacement::FEvaluationContext& Context, UE::Anim::FootPlacement::FLegRuntimeData::FInterpolationData& InOutInterpData) const;` — Handles horizontal interpolation when unlocking the plant
- L680 _private prototype_ `void UpdatePlantingPlaneInterpolation( const UE::Anim::FootPlacement::FEvaluationContext& Context, const FTransform& FootTransformWS, const FTransform& LastAlignedFootTransform, const float AlignmentAlpha, FPlane& InOutPlantPlane, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose, UE::Anim::FootPlacement::FLegRuntimeData::FInterpolationData& InOutInterpData) const;` — Handles the interpolation of the planting plane. Because the plant transform is specified with respect to the planting plane, it cannot change abruptly without causing an animation pop. It must be interpolated instead.
- L690 _private prototype_ `void DeterminePlantType( const UE::Anim::FootPlacement::FEvaluationContext& Context, const FTransform& FKTransformWS, const FTransform& CurrentBoneTransformWS, UE::Anim::FootPlacement::FLegRuntimeData::FPlantData& InOutPlantData, const UE::Anim::FootPlacement::FLegRuntimeData::FInputPoseData& LegInputPose) const;` — Checks unplanting and replanting conditions to determine if the foot is planted
- L697 _private prototype_ `float GetMaxLimbExtension(const float DesiredExtension, const float LimbLength) const;`
- L698 _private prototype_ `float GetMinLimbExtension(const float DesiredExtension, const float LimbLength) const;`
- L700 _private prototype_ `void ResetRuntimeData();`
- L704 _private member_ `UE::Anim::FootPlacement::FDebugData DebugData;`
- L706 _private prototype_ `void DrawDebug( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData& LegData, const UE::Anim::FootPlacement::FPlantResult& PlantResult) const;`
- L711 _private prototype_ `void DrawVLog( const UE::Anim::FootPlacement::FEvaluationContext& Context, const UE::Anim::FootPlacement::FLegRuntimeData& LegData, const UE::Anim::FootPlacement::FPlantResult& PlantResult) const;`
- L717 _private member_ `bool bIsFirstUpdate = false;`
- L718 _private member_ `FGraphTraversalCounter UpdateCounter;`

#### struct `FAnimNode_FootPlacement::FPelvisOffsetRangeForLimb`  
`struct FPelvisOffsetRangeForLimb`  
_L643-648_
- L645 _public member_ `float MaxExtension;`
- L646 _public member_ `float MinExtension;`
- L647 _public member_ `float DesiredExtension;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`
- L20 _macro_ `#define ENABLE_FOOTPLACEMENT_DEBUG 1`
- L22 _macro_ `#define ENABLE_FOOTPLACEMENT_DEBUG 0`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Anim` (scope `UE`)
- L25 _namespace_ `namespace FootPlacement` (scope `UE::Anim`)

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_OffsetRootBone.h` (Public)


#### class `UE::AnimationWarping::FRootOffsetProvider`  
`class FRootOffsetProvider : public UE::Anim::IGraphMessage`  
_L18-33_
- inherits: `UE::Anim::IGraphMessage`
- L24 _public function_ `FRootOffsetProvider(const FTransform& InRootTransform) : RootTransform(InRootTransform)`
- L29 _public function_ `const FTransform& GetRootTransform() const`
- L32 _private member_ `FTransform RootTransform;`

#### enum `EOffsetRootBone_CollisionTestingMode`  
`enum class EOffsetRootBone_CollisionTestingMode : uint8`  
_L37-45_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `Disabled` — No Collision testing
- L42 _public enumerator_ `ShrinkMaxTranslation` — Reduce effective Max Translation offset to prevent penetration with nearby obstacles
- L44 _public enumerator_ `PlanarCollision` — Slide along a plane based on shape cast contact point

#### struct `FAnimNode_OffsetRootBone`  
`struct FAnimNode_OffsetRootBone : public FAnimNode_Base`  
_L48-207_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_Base`
- L53 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (DisplayPriority = 0))`
- L57 _public member_ `EWarpingEvaluationMode EvaluationMode = EWarpingEvaluationMode::Graph;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta=(FoldProperty))`
- L60 _public member_ `bool bResetEveryFrame = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))`
- L64 _public member_ `EOffsetRootBoneMode TranslationMode = EOffsetRootBoneMode::Interpolate;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — The translation offset behavior mode
- L68 _public member_ `EOffsetRootBoneMode RotationMode = EOffsetRootBoneMode::Interpolate;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — The rotation offset behavior mode
- L73 _public member_ `float TranslationHalflife = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — Controls how fast the translation offset is blended out Values closer to 0 make it faster
- L78 _public member_ `float RotationHalfLife = 0.2f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — Controls how fast the rotation offset is blended out Values closer to 0 make it faster
- L83 _public member_ `float MaxTranslationError = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — How much the offset can deviate from the mesh component's translation in units Values lower than 0 disable this limit
- L88 _public member_ `float MaxRotationError = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — How much the offset can deviate from the mesh component's rotation in degrees Values lower than 0 disable this limit
- L93 _public member_ `bool bClampToTranslationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — Whether to limit the offset's translation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no translation speed
- L98 _public member_ `bool bClampToRotationVelocity = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — Whether to limit the offset's rotation interpolation speed to the velocity on the incoming motion Enabling this prevents the offset sliding when there's little to no rotation speed
- L103 _public member_ `float TranslationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToTranslationVelocity, FoldProperty, PinHiddenByDefault))` — How much the offset can blend out, relative to the incoming translation speed i.e. If root motion is moving at 400cm/s, at 0.5, the offset can blend out at 200cm/s
- L108 _public member_ `float RotationSpeedRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = bClampToRotationVelocity, FoldProperty, PinHiddenByDefault))` — How much the offset can blend out, relative to the incoming rotation speed i.e. If root motion is rotating at 90 degrees/s, at 0.5, the offset can blend out at 45 degree/s
- L112 _public member_ `bool bOnGround = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — When OnGround is true, root motion velocities will be projected onto the ground surface
- L116 _public member_ `FVector GroundNormal = { 0, 0, 1 };` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — Surface normal of the ground
- L121 _public member_ `FVector TranslationDelta = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (FoldProperty, PinHiddenByDefault))` — Delta applied to the translation offset this frame. For procedural values, consider adjusting the input by delta time.
- L126 _public member_ `FRotator RotationDelta = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (FoldProperty, PinHiddenByDefault))` — Delta applied to the rotation offset this frame. For procedural values, consider adjusting the input by delta time.
- L130 _public member_ `bool bResetOnTeleport = false;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty, PinHiddenByDefault))` — If to reset the root bone offset on teleport
- L133 _public member_ `EOffsetRootBone_CollisionTestingMode CollisionTestingMode = EOffsetRootBone_CollisionTestingMode::Disabled;` — `UPROPERTY(EditAnywhere, Category = CollisionTesting, meta = (FoldProperty, PinHiddenByDefault))`
- L135 _public member_ `float CollisionTestShapeRadius = 30;` — `UPROPERTY(EditAnywhere, Category = CollisionTesting, meta = (EditCondition = "CollisionTestingMode != ECollisionTestingMode::Disabled", DisplayAfter="CollisionTestingMode", FoldProperty, PinHiddenByDefault))`
- L137 _public member_ `FVector CollisionTestShapeOffset = {0,0,60};` — `UPROPERTY(EditAnywhere, Category = CollisionTesting, meta = (EditCondition = "CollisionTestingMode != ECollisionTestingMode::Disabled", DisplayAfter="CollisionTestingMode", FoldProperty, PinHiddenByDefault))`
- L143 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L144 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L145 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L146 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L147 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L151 _public prototype_ `EWarpingEvaluationMode GetEvaluationMode() const;` — Folded property accesors
- L152 _public prototype_ `bool GetResetEveryFrame() const;`
- L153 _public prototype_ `bool GetOnGround() const;`
- L154 _public prototype_ `const FVector& GetGroundNormal() const;`
- L155 _public prototype_ `const FVector& GetTranslationDelta() const;`
- L156 _public prototype_ `const FRotator& GetRotationDelta() const;`
- L157 _public prototype_ `EOffsetRootBoneMode GetTranslationMode() const;`
- L158 _public prototype_ `EOffsetRootBoneMode GetRotationMode() const;`
- L159 _public prototype_ `float GetTranslationHalflife() const;`
- L160 _public prototype_ `float GetRotationHalfLife() const;`
- L161 _public prototype_ `float GetMaxTranslationError() const;`
- L162 _public prototype_ `float GetMaxRotationError() const;`
- L163 _public prototype_ `bool GetClampToTranslationVelocity() const;`
- L164 _public prototype_ `bool GetClampToRotationVelocity() const;`
- L165 _public prototype_ `float GetTranslationSpeedRatio() const;`
- L166 _public prototype_ `float GetRotationSpeedRatio() const;`
- L167 _public prototype_ `EOffsetRootBone_CollisionTestingMode GetCollisionTestingMode() const;`
- L168 _public prototype_ `float GetCollisionTestShapeRadius() const;`
- L169 _public prototype_ `const FVector& GetCollisionTestShapeOffset() const;`
- L170 _public prototype_ `bool GetResetOnTeleport() const;`
- L173 _public function_ `void GetOffsetRootTransform(FTransform& OutTransform)` — get the current simulated root transform
- L179 _public function_ `const FVector& GetOffsetRootTranslation() const`
- L180 _public function_ `void SetOffsetRootTranslation(const FVector& InTranslation)`
- L182 _public function_ `const FQuat& GetOffsetRootRotation() const`
- L183 _public function_ `void SetOffsetRootRotation(const FQuat& InRotation)`
- L187 _private prototype_ `void Reset(const FAnimationBaseContext& Context);`
- L190 _private member_ `FAnimInstanceProxy* AnimInstanceProxy = nullptr;` — Internal cached anim instance proxy
- L193 _private member_ `float CachedDeltaTime = 0.f;` — Internal cached delta time used for interpolators
- L195 _private member_ `bool bIsFirstUpdate = true;`
- L197 _private member_ `FTransform ComponentTransform = FTransform::Identity;`
- L201 _private member_ `FVector SimulatedTranslation = FVector::ZeroVector;` — The simulated world-space transforms for the root bone with offset Offset = ComponentTransform - SimulatedTransform
- L202 _private member_ `FQuat SimulatedRotation = FQuat::Identity;`
- L204 _private member_ `FVector LastNonZeroRootMotionDirection = FVector::ZeroVector;`
- L206 _private member_ `FGraphTraversalCounter UpdateCounter;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace AnimationWarping` (scope `UE`)

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_OrientationWarping.h` (Public)


#### enum `EOrientationWarpingSpace`  
`enum class EOrientationWarpingSpace : uint8`  
_L19-27_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `ComponentTransform` — apply warping relative to current component transform
- L24 _public enumerator_ `RootBoneTransform` — Apply warping relative to previous frame's root bone transform. Use this mode when using an OffsetRootBone node which allows the root bone and component transforms to differ.
- L26 _public enumerator_ `CustomTransform` — Provide a custom transform pin

#### struct `FAnimNode_OrientationWarping`  
`struct FAnimNode_OrientationWarping : public FAnimNode_SkeletalControlBase`  
_L34-254_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Maintains a look at direction for the upper body (orientation), while rotating the lower body to match capsule velocity direction Does nothing if the root motion velocity direction matches the desired / current capsule velocity direction
- L40 _public member_ `EWarpingEvaluationMode Mode = EWarpingEvaluationMode::Manual;` — `UPROPERTY(EditAnywhere, Category=Evaluation)` — Orientation warping evaluation mode (Graph or Manual)
- L46 _public member_ `float TargetTime = 0.8f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental, meta = (PinShownByDefault))` — Experimental. Orientation warping should do nothing if root motion velocity directions match capsule, however root motion can have multiple velocity directions. So we also check root motion direction 'TargetTime' in the future for matching direction to avoid temp orientation warps.
- L50 _public member_ `float OrientationAngle = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The desired orientation angle (in degrees) to warp by relative to the specified RotationAxis
- L56 _public member_ `float LocomotionAngle = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The character locomotion angle (in degrees) relative to the specified RotationAxis This will be used in the following equation for computing the orientation angle: [Orientation = RotationBetween(RootMotionDirection, LocomotionDirection)] In most cases, this is the difference between the Velocity of the Movement Component and the actor rotation (obtained via CalculateDirection)
- L62 _public member_ `FVector LocomotionDirection = { 0.f, 0.f, 0.f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The character movement direction vector in world space When set, this vector is used to compute LocomotionAngle automatically. When not set, the LocomotionAngle input should be used instead. In most cases, this vector is the same as the Velocity vector of the Movement Component
- L68 _public member_ `float MinRootMotionSpeedThreshold = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Evaluation, meta = (ClampMin = "0.0", PinHiddenByDefault))` — Minimum root motion speed required to apply orientation warping This is useful to prevent unnatural re-orientation when the animation has a portion with no root motion (i.e starts/stops/idles) When this value is greater than 0, it's recommended to enable interpolation with RotationInterpSpeed > 0
- L78 _public member_ `float LocomotionAngleDeltaThreshold = 90.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinHiddenByDefault), meta=(ClampMin="0.0", ClampMax="180.0"))` — Specifies an angle threshold to prevent erroneous over-rotation of the character, disabled with a value of 0 When the effective orientation warping angle is detected to be greater than this value (default: 90 degrees) the locomotion direction will be inverted prior to warping This will be used in the following equation: [Orientation = RotationBetween(RootMotionDirection, -LocomotionDirection)] Example: Playing a forward running animation while the motion is going backward Rather than orientation warping by 180 degrees, the system will warp by 0 degrees
- L84 _public member_ `TArray<FBoneReference> SpineBones;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Spine bone definitions Used to counter rotate the body in order to keep the character facing forward The amount of counter rotation applied is driven by DistributedBoneOrientationAlpha
- L88 _public member_ `FBoneReference IKFootRootBone;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Root Bone"))` — IK Foot Root Bone definition
- L92 _public member_ `TArray<FBoneReference> IKFootBones;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Bones"))` — IK Foot definitions
- L97 _public member_ `TObjectPtr<UAnimationAsset> CurrentAnimAsset;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category = Experimental, meta = (PinShownByDefault))` — Experimental. Animation Asset for incorporating root motion data. If 'TargetTime' is set, and the animation has root motion rotation within the TargetTime, then those rotations will be scaled to reach the TargetOrientation
- L101 _public member_ `float CurrentAnimAssetTime = 0.f;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category = Experimental, meta = (PinShownByDefault))` — Experimental. Current playback time in seconds of the CurrentAnimAsset
- L105 _public member_ `TEnumAsByte<EAxis::Type> RotationAxis = EAxis::Z;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Rotation axis used when rotating the character body
- L109 _public member_ `float DistributedBoneOrientationAlpha = 0.5f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", ClampMax="1.0", PinHiddenByDefault))` — Specifies how much rotation is applied to the character body versus IK feet
- L114 _public member_ `float RotationInterpSpeed = 10.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0"))` — Specifies the interpolation speed (in Alpha per second) towards reaching the final warped rotation angle A value of 0 will cause instantaneous rotation, while a greater value will introduce smoothing
- L119 _public member_ `float CounterCompensateInterpSpeed = 45.f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "0.0"))` — Same as RotationInterpSpeed, but for CounterCompensate smoothing. A value of 0 sample raw root motion. Used to avoid stuttering from resampling root deltas. Root motion is already smooth, so a large value is our default (~75% of 60 fps).
- L124 _public member_ `float MaxCorrectionDegrees = 180.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Max correction we're allowed to do per-second when using interpolation. This minimizes pops when we have a large difference between current and target orientation.
- L128 _public member_ `float MaxRootMotionDeltaToCompensateDegrees = 45.f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", EditCondition="RotationInterpSpeed > 0.0f"))` — Don't compensate our interpolator when the instantaneous root motion delta is higher than this. This is likely a pivot.
- L134 _public member_ `bool bCounterCompenstateInterpolationByRootMotion = true;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(EditCondition="RotationInterpSpeed > 0.0f"))` — Whether to counter compensate interpolation by the animated root motion angle change over time. This helps to conserve the motion from our animation. Disable this if your root motion is expected to be jittery, and you want orientation warping to smooth it out.
- L137 _public member_ `bool bScaleByGlobalBlendWeight = false;` — `UPROPERTY(EditAnywhere, Category=Experimental, meta=(PinHiddenByDefault))`
- L140 _public member_ `bool bUseManualRootMotionVelocity = false;` — `UPROPERTY(EditAnywhere, Category=Experimental, meta=(PinHiddenByDefault))`
- L143 _public member_ `FVector ManualRootMotionVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Experimental, meta=(PinHiddenByDefault))`
- L147 _public member_ `EOrientationWarpingSpace WarpingSpace = EOrientationWarpingSpace::ComponentTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinHiddenByDefault))`
- L150 _public member_ `FTransform WarpingSpaceTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinHiddenByDefault))`
- L155 _public member_ `float DebugDrawScale = 1.f;` — `UPROPERTY(EditAnywhere, Category=Debug, meta=(ClampMin="0.0"))` — Scale all debug drawing visualization by a factor
- L159 _public member_ `bool bEnableDebugDraw = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable orientation warping debug drawing
- L164 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L165 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L169 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L170 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L171 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L176 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L219 _private member_ `TArray<FOrientationWarpingSpineBoneData> SpineBoneDataArray;` — Computed spine bone indices and alpha weights for the specified spine definition
- L222 _private member_ `FOrientationWarpingFootData IKFootData;` — Computed IK bone indices for the specified foot definitions
- L225 _private member_ `FVector RootMotionDeltaDirection = FVector::ZeroVector;` — Internal current frame root motion delta direction
- L228 _private member_ `FQuat RootMotionDeltaRotation = FQuat::Identity;` — Internal current frame root motion delta angle
- L231 _private member_ `float CounterCompensateTargetAngleRad = 0.0f;` — Target for counter compenstate, we keep the target so we can smoothly interp.
- L235 _private member_ `FVector FutureRootMotionDeltaDirection = FVector::ZeroVector;` — Store prediction in debug only so that they can persist across pauses
- L236 _private member_ `bool bUsedFutureRootMotion = false;`
- L239 _private member_ `FColor DebugColor = FColor::Black;` — Stored from blend message, used to match with rewind debugger
- L243 _private member_ `float ActualOrientationAngleRad = 0.f;` — Internal orientation warping angle
- L244 _private member_ `float BlendWeight = 0.0f;`
- L246 _private member_ `FGraphTraversalCounter UpdateCounter;`
- L247 _private member_ `bool bIsFirstUpdate = false;`
- L248 _private prototype_ `void Reset(const FAnimationBaseContext& Context);`
- L252 _private member_ `bool bFoundRootMotionAttribute = false;` — Whether we found a root motion delta attribute in the attribute stream on graph driven mode

#### struct `FAnimNode_OrientationWarping::FOrientationWarpingSpineBoneData`  
`struct FOrientationWarpingSpineBoneData`  
_L179-204_
- L181 _public member_ `FCompactPoseBoneIndex BoneIndex;`
- L182 _public member_ `float Weight;`
- L184 _public function_ `FOrientationWarpingSpineBoneData() : BoneIndex(INDEX_NONE) , Weight(0.f)`
- L190 _public function_ `FOrientationWarpingSpineBoneData(FCompactPoseBoneIndex InBoneIndex) : BoneIndex(InBoneIndex) , Weight(0.f)`

#### struct `FAnimNode_OrientationWarping::FOrientationWarpingSpineBoneData::FCompareBoneIndex`  
`struct FCompareBoneIndex`  
_L197-203_
- desc: Comparison Operator for Sorting
- L199 _public function_ `inline bool operator()(const FOrientationWarpingSpineBoneData& A, const FOrientationWarpingSpineBoneData& B) const`

#### struct `FAnimNode_OrientationWarping::FOrientationWarpingFootData`  
`struct FOrientationWarpingFootData`  
_L206-216_
- L208 _public member_ `TArray<FCompactPoseBoneIndex> IKFootBoneIndexArray;`
- L209 _public member_ `FCompactPoseBoneIndex IKFootRootBoneIndex;`
- L211 _public function_ `FOrientationWarpingFootData() : IKFootBoneIndexArray() , IKFootRootBoneIndex(INDEX_NONE)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_OverrideRootMotion.h` (Public)


#### struct `FAnimNode_OverrideRootMotion`  
`struct FAnimNode_OverrideRootMotion : public FAnimNode_Base`  
_L16-52_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_Base`
- L21 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (DisplayPriority = 0))`
- L25 _public member_ `float Alpha = 1.f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (FoldProperty, PinShownByDefault))`
- L28 _public member_ `FVector OverrideVelocity = FVector(0,0,0);` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (FoldProperty, PinShownByDefault))`
- L35 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;` — FAnimNode_Base interface
- L36 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L37 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L38 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L39 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L43 _public prototype_ `float GetAlpha() const;` — Folded property accesors
- L44 _public prototype_ `const FVector& GetOverrideVelocity() const;`
- L49 _private member_ `FAnimInstanceProxy* AnimInstanceProxy = nullptr;` — Internal cached anim instance proxy
- L51 _private member_ `float DeltaTime = 0.f;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_SlopeWarping.h` (Public)


#### struct `FSlopeWarpingFootDefinition`  
`struct FSlopeWarpingFootDefinition`  
_L17-37_
- reflection: `USTRUCT()`
- desc: Per foot definitions
- L22 _public member_ `FBoneReference IKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L25 _public member_ `FBoneReference FKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L28 _public member_ `int32 NumBonesInLimb;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L31 _public member_ `float FootSize;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L33 _public function_ `FSlopeWarpingFootDefinition() : NumBonesInLimb(2) , FootSize(4.f)`

#### struct `FSlopeWarpingFootData`  
`struct FSlopeWarpingFootData`  
_L41-64_
- reflection: `USTRUCT()`
- desc: Runtime foot data after validation, we guarantee these bones to exist
- L46 _public member_ `FCompactPoseBoneIndex IKFootBoneIndex;`
- L47 _public member_ `FCompactPoseBoneIndex FKFootBoneIndex;`
- L48 _public member_ `FCompactPoseBoneIndex HipBoneIndex;`
- L50 _public member_ `FTransform IKFootTransform;`
- L52 _public member_ `FVector HitLocation;`
- L53 _public member_ `FVector HitNormal;`
- L55 _public member_ `FSlopeWarpingFootDefinition* FootDefinitionPtr;`
- L58 _public function_ `FSlopeWarpingFootData() : IKFootBoneIndex(INDEX_NONE) , FKFootBoneIndex(INDEX_NONE) , HipBoneIndex(INDEX_NONE) , FootDefinitionPtr(nullptr)`

#### struct `FAnimNode_SlopeWarping`  
`struct FAnimNode_SlopeWarping : public FAnimNode_SkeletalControlBase`  
_L70-168_
- reflection: `USTRUCT(Experimental)`
- inherits: `FAnimNode_SkeletalControlBase`
- L74 _public prototype_ `FAnimNode_SlopeWarping();`
- L76 _public member_ `USkeletalMeshComponent* MySkelMeshComponent;`
- L77 _public member_ `UCharacterMovementComponent* MyMovementComponent;`
- L78 _public member_ `FAnimInstanceProxy* MyAnimInstanceProxy;`
- L82 _public member_ `FBoneReference IKFootRootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — IKFoot Root Bone.
- L86 _public member_ `FBoneReference PelvisBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Pelvis Bone.
- L89 _public member_ `TArray<FSlopeWarpingFootDefinition> FeetDefinitions;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L92 _public member_ `TArray<FSlopeWarpingFootData> FeetData;` — `UPROPERTY(Transient)`
- L95 _public member_ `FVectorRK4SpringInterpolator PelvisOffsetInterpolator;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L98 _public member_ `FVector GravityDir;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault))`
- L101 _public member_ `FVector CustomFloorOffset;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault))`
- L104 _public member_ `float CachedDeltaTime;` — `UPROPERTY(Transient)`
- L107 _public member_ `FVector TargetFloorNormalWorldSpace;` — `UPROPERTY(Transient)`
- L110 _public member_ `FVectorRK4SpringInterpolator FloorNormalInterpolator;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L113 _public member_ `FVector TargetFloorOffsetLocalSpace;` — `UPROPERTY(Transient)`
- L116 _public member_ `FVectorRK4SpringInterpolator FloorOffsetInterpolator;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L119 _public member_ `float MaxStepHeight;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L122 _public member_ `uint32 bKeepMeshInsideOfCapsule : 1;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L125 _public member_ `uint32 bPullPelvisDown : 1;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L128 _public member_ `uint32 bUseCustomFloorOffset : 1;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault))`
- L131 _public member_ `uint32 bWasOnGround : 1;` — `UPROPERTY(Transient)`
- L134 _public member_ `uint32 bShowDebug : 1;` — `UPROPERTY(Transient)`
- L137 _public member_ `uint32 bFloorSmoothingInitialized : 1;` — `UPROPERTY(Transient)`
- L140 _public member_ `FVector ActorLocation;` — `UPROPERTY(Transient)`
- L144 _protected member_ `FVector GravityDirCompSpace;` — `UPROPERTY(Transient)`
- L148 _public prototype_ `FVector GetFloorNormalFromMovementComponent() const;`
- L149 _public prototype_ `void SetWorldSpaceTargetFloorInfoFromMovementComponent();`
- L151 _public prototype_ `void GetSmoothedFloorInfo(FCSPose<FCompactPose>& MeshBases, FVector& OutFloorNormal, FVector& OutFloorOffset);`
- L154 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L155 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L159 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L160 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L161 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L166 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_Steering.h` (Public)


#### struct `FAnimNode_Steering`  
`struct FAnimNode_Steering : public FAnimNode_SkeletalControlBase`  
_L23-107_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Add procedural delta to the root motion attribute This is done via 2 techniques: 1) Scaling the root motion on an animation 2) Adding additional correction to root motion after accounting for the anticipated (potentially scaled) root motion The effects of 1) and 2) combine
- L29 _public prototype_ `FAnimNode_Steering() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L30 _public prototype_ `~FAnimNode_Steering() = default;`
- L31 _public prototype_ `FAnimNode_Steering(const FAnimNode_Steering&) = default;`
- L32 _public prototype_ `FAnimNode_Steering(FAnimNode_Steering&&) = default;`
- L33 _public prototype_ `FAnimNode_Steering& operator=(const FAnimNode_Steering&) = default;`
- L34 _public prototype_ `FAnimNode_Steering& operator=(FAnimNode_Steering&&) = default;`
- L39 _public member_ `FQuat TargetOrientation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The Orientation to steer towards
- L43 _public member_ `bool bMirrored = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Filtering, meta = (PinShownByDefault))` — True if input animation is mirrored
- L47 _public member_ `float ProceduralTargetTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The number of seconds in the future before we should roughly attempt reach the TargetOrientation via additive correction
- L52 _public member_ `float TargetTime_DEPRECATED = 0.2f;` — `UE_DEPRECATED(5.6, "Use Procedural target time for the correction time scale and AnimatedTargetTime for the look ahead time on the animation")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use Procedural target time for the correction time scale and AnimatedTargetTime for the look ahead time on the animation"))` — Deprected old/unused parameter, to avoid breaking data
- L56 _public member_ `float AnimatedTargetTime = 2.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — The number of seconds in the future to sample the root motion to know how much this animation is expected to turn
- L61 _public member_ `float RootMotionThreshold = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName=RootMotionAngleThreshold, Category=Evaluation)` — The minimum amount of root motion required to enable root motion scaling. The root motion is measured from current time to AnimatedTargetTime
- L65 _public member_ `float DisableSteeringBelowSpeed = 1.0f;` — `UPROPERTY(EditAnywhere, Category=Evaluation)` — below this movement speed (based on the root motion in the animation) disable steering completely (both scaling and additive)
- L69 _public member_ `float DisableAdditiveBelowSpeed = -1.0f;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — below this movement speed (based on the root motion in the animation) disable steering coming from the additive spring based correction
- L73 _public member_ `float MinScaleRatio = 0.5f;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — Will clamp the scaling ratio applied to above this threshold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L77 _public member_ `float MaxScaleRatio = 1.5f;` — `UPROPERTY(EditAnywhere, Category = Evaluation)` — Will clamp the scaling ratio applied to below this threshold. Any error remaining will be compensated for linearly (using ProceduralTargetTime)
- L81 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category = Evaluation, meta = (PinShownByDefault))` — If bMirrored is set, MirrorDataTable will be used for mirroring the CurrentAnimAsset during prediction
- L85 _public member_ `TObjectPtr<UAnimationAsset> CurrentAnimAsset;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Animation Asset for incorporating root motion data. If CurrentAnimAsset is set, and the animation has root motion rotation within the TargetTime, then those rotations will be scaled to reach the TargetOrientation
- L89 _public member_ `float CurrentAnimAssetTime = 0.f;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Current playback time in seconds of the CurrentAnimAsset
- L92 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNodeBase interface
- L93 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L97 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L98 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L99 _public function_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override`
- L104 _private member_ `FVector AngularVelocity = FVector::ZeroVector;`
- L106 _private member_ `FTransform RootBoneTransform;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_StrideWarping.h` (Public)


#### struct `FStrideWarpingFootDefinition`  
`struct FStrideWarpingFootDefinition`  
_L18-33_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Foot definition specifying the IK/FK foot bones and Thigh bone
- L24 _public member_ `FBoneReference IKFootBone;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Bone"))` — IK driven foot bone
- L28 _public member_ `FBoneReference FKFootBone;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="FK Foot Bone"))` — FK driven foot bone
- L32 _public member_ `FBoneReference ThighBone;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Thigh bone, representing the end of the leg chain prior to reaching the Pelvis Bone

#### struct `FAnimNode_StrideWarping`  
`struct FAnimNode_StrideWarping : public FAnimNode_SkeletalControlBase`  
_L36-207_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L42 _public member_ `EWarpingEvaluationMode Mode = EWarpingEvaluationMode::Manual;` — `UPROPERTY(EditAnywhere, Category=Evaluation)` — Stride warping evaluation mode (Graph or Manual)
- L47 _public member_ `FVector StrideDirection = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Component-space stride direction Example: A value of <1,0,0> will warp the leg stride along the Forward Vector
- L52 _public member_ `float StrideScale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(ClampMin="0.0", PinShownByDefault))` — Stride scale, specifying the amount of warping applied to the foot definitions Example: A value of 0.5 will decrease the effective leg stride by half, while a value of 2.0 will double it
- L61 _public member_ `float LocomotionSpeed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(ClampMin="0.0", PinShownByDefault))` — Locomotion speed, specifying the current speed of the character This will be used in the following equation for computing the stride scale: [StrideScale = (LocomotionSpeed / RootMotionSpeed)] Note: This speed should be relative to the delta time of the animation graph Stride scale is a value specifying the amount of warping applied to the IK foot definitions Example: A value of 0.5 will decrease the effective leg stride by half, while a value of 2.0 will double it
- L67 _public member_ `float MinRootMotionSpeedThreshold = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Evaluation, meta=(ClampMin="0.0001", PinHiddenByDefault))` — Minimum root motion speed required to apply stride warping This is useful to prevent unnatural strides when the animation has a portion with no root motion (i.e starts/stops) When this value is greater than 0, it's recommended to enable interpolation in StrideScaleModifier
- L71 _public member_ `FBoneReference PelvisBone;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Pevlis Bone definition
- L75 _public member_ `FBoneReference IKFootRootBone;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(DisplayName="IK Foot Root Bone"))` — IK Foot Root Bone definition
- L79 _public member_ `TArray<FStrideWarpingFootDefinition> FootDefinitions;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Foot definitions specifying the IK, FK, and Thigh bone
- L83 _public member_ `FInputClampConstants StrideScaleModifier;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(PinHiddenByDefault))` — Modifies the final stride scale value by optionally clamping and/or interpolating
- L88 _public member_ `FWarpingVectorValue FloorNormalDirection = { EWarpingVectorMode::WorldSpaceVector, FVector::UpVector };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Advanced, meta=(PinHiddenByDefault))` — Floor normal direction, this value will internally convert into a corresponding Component-space representation prior to warping Default: World Space, Up Vector: <0,0,1>
- L93 _public member_ `FWarpingVectorValue GravityDirection = { EWarpingVectorMode::WorldSpaceVector, FVector::DownVector };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Advanced, meta=(PinHiddenByDefault))` — Gravity direction, this value will internally convert into a corresponding Component-space representation prior to warping Default: World Space, Down Vector: <0,0,-1>
- L97 _public member_ `FIKFootPelvisPullDownSolver PelvisIKFootSolver;` — `UPROPERTY(EditAnywhere, Category=Advanced, meta=(DisplayName="Pelvis IK Foot Solver"))` — Solver for controlling how much the pelvis is "pulled down" towards the IK/FK foot definitions during leg limb extension
- L101 _public member_ `bool bOrientStrideDirectionUsingFloorNormal = true;` — `UPROPERTY(EditAnywhere, Category=Advanced)` — Orients the specified (Manual) or computed (Graph) stride direction by the floor normal
- L106 _public member_ `bool bCompensateIKUsingFKThighRotation = true;` — `UPROPERTY(EditAnywhere, Category=Advanced, meta=(DisplayName="Compensate IK Using FK Thigh Rotation"))` — Include warping adjustment to the FK thigh bones alongside the IK/FK foot definitions This is used to help preserve the original overall leg shape
- L110 _public member_ `bool bClampIKUsingFKLimits = true;` — `UPROPERTY(EditAnywhere, Category=Advanced, meta=(DisplayName="Clamp IK Using FK Limits", EditCondition="bCompensateIKUsingFKThighRotation"))` — Clamps the IK foot warping to prevent over-extension relative to the overall FK leg
- L114 _public member_ `bool bDisableIfMissingRootMotion = true;` — `UPROPERTY(EditAnywhere, Category=Advanced)` — Do not execute stride warping if animation data has no root motion
- L119 _public member_ `float DebugDrawScale = 1.f;` — `UPROPERTY(EditAnywhere, Category=Debug, meta=(ClampMin="0.0"))` — Scale all debug drawing visualization by a factor
- L123 _public member_ `bool bEnableDebugDraw = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable stride warping debug drawing
- L127 _public member_ `bool bDebugDrawIKFootOrigin = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable IK foot location debug drawing prior to warping
- L131 _public member_ `bool bDebugDrawIKFootAdjustment = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable IK foot location debug drawing following initial foot adjustment
- L135 _public member_ `bool bDebugDrawPelvisAdjustment = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable pelvis debug drawing following adjustment
- L139 _public member_ `bool bDebugDrawThighAdjustment = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable thigh debug drawing following adjustment
- L143 _public member_ `bool bDebugDrawIKFootFinal = false;` — `UPROPERTY(EditAnywhere, Category=Debug)` — Enable/Disable IK foot location debug drawing following all adsjustments (Final warped result)
- L148 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L149 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L153 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L154 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L155 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L160 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L180 _private member_ `FAnimInstanceProxy* AnimInstanceProxy = nullptr;` — Internal cached anim instance proxy
- L183 _private member_ `TArray<FStrideWarpingFootData> FootData;` — Computed IK, FK, Thigh bone indices for the specified foot definitions
- L186 _private member_ `FInputClampState StrideScaleModifierState;` — Internal cached stride scale modifier state
- L189 _private member_ `FVector ActualStrideDirection = FVector::ForwardVector;` — Internal stride direction
- L192 _private member_ `float ActualStrideScale = 1.f;` — Internal stride scale
- L195 _private member_ `float CachedDeltaTime = 0.f;` — Internal cached delta time used for interpolators
- L199 _private member_ `FVector CachedRootMotionDeltaTranslation = FVector::ZeroVector;` — Internal cached debug root motion delta translation
- L202 _private member_ `float CachedRootMotionDeltaSpeed = 0.f;` — Internal cached debug root motion speed
- L205 _private member_ `bool bFoundRootMotionAttribute = false;` — Whether we found a root motion delta attribute in the attribute stream on graph driven mode

#### struct `FAnimNode_StrideWarping::FStrideWarpingFootData`  
`struct FStrideWarpingFootData`  
_L163-177_
- L165 _public member_ `FCompactPoseBoneIndex IKFootBoneIndex;`
- L166 _public member_ `FCompactPoseBoneIndex FKFootBoneIndex;`
- L167 _public member_ `FCompactPoseBoneIndex ThighBoneIndex;`
- L168 _public member_ `FTransform IKFootBoneTransform;`
- L170 _public function_ `FStrideWarpingFootData() : IKFootBoneIndex(INDEX_NONE) , FKFootBoneIndex(INDEX_NONE) , ThighBoneIndex(INDEX_NONE) , IKFootBoneTransform(FTransform::Identity)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`

### `Plugins/Animation/AnimationWarping/Source/Runtime/Public/BoneControllers/AnimNode_WarpTest.h` (Public)


#### struct `FAnimNode_WarpTest`  
`struct FAnimNode_WarpTest : public FAnimNode_Base`  
_L11-38_
- reflection: `USTRUCT(Experimental, BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L16 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (DisplayPriority = 0))`
- L20 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — the node will warp the character looping between Transforms[i] choosing the next one every SecondsToWait
- L24 _public member_ `float SecondsToWait = 1.f;` — `UPROPERTY(EditAnywhere, Category = Evaluation, meta = (PinShownByDefault))` — every SecondsToWait we warp to the next Transforms[i]
- L28 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;` — FAnimNode_Base interface
- L29 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L30 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L31 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L35 _public member_ `FTransform ComponentTransform = FTransform::Identity;` — ComponentTransform represents the previous frame component transform
- L36 _public member_ `float CurrentTime = 0.f;`
- L37 _public member_ `int32 CurrentTransformIndex = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONWARPINGRUNTIME_API`
