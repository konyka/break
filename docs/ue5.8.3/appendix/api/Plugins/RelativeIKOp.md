# Plugins / RelativeIKOp

- module root: `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeIKOp`
- headers: 3; symbols: 359
- symbol kinds: class=3, enum=2, enumerator=7, function=4, macro=4, member=195, prototype=128, struct=16
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, BodyIntersectIKOp, Core, CoreUObject, DynamicMesh, Eigen, Engine, GeometryCore, IKRig, MeshConversion, MeshDescription, RelativeBodyAnimInfo, Renderer, SkeletalMeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeIKOp/Public/RelativeIKOp.h` (Public)


#### enum `EDistanceWeightMode`  
`enum class EDistanceWeightMode : uint8`  
_L30-38_
- reflection: `UENUM(BlueprintType)`
- L33 _public enumerator_ `Linear UMETA(DisplayName = "Linear")` — Constant   UMETA(DisplayName = "Constant"),
- L34 _public enumerator_ `Quadratic UMETA(DisplayName = "Quadratic")`
- L35 _public enumerator_ `Cubic UMETA(DisplayName = "Cubic")`
- L36 _public enumerator_ `Quartic UMETA(DisplayName = "Quartic")`

#### struct `FDebugRelativeTargetPairSpace`  
`struct FDebugRelativeTargetPairSpace`  
_L41-48_
- desc: Debug info for individual body pair contributions
- L43 _public member_ `FVector PairRangeStart;`
- L44 _public member_ `FVector PairRangeEnd;`
- L46 _public member_ `double TargetAlpha;`
- L47 _public member_ `FDoubleInterval FeasibleRange;`

#### struct `FDebugDrawTargetGoal`  
`struct FDebugDrawTargetGoal`  
_L51-55_
- desc: Debug draw info for goal (with individual pair goal targets)
- L53 _public member_ `FVector Goal;`
- L54 _public member_ `TArray<FVector> PairTargets;`

#### struct `FDebugDrawBodyPair`  
`struct FDebugDrawBodyPair`  
_L58-68_
- desc: Debug draw info for source or target pair
- L60 _public member_ `FVector PosA_A;`
- L61 _public member_ `FVector PosB_B;`
- L63 _public member_ `bool bFullPos;`
- L64 _public member_ `FVector PosB_A;`
- L65 _public member_ `FVector PosA_B;`
- L67 _public member_ `double Weight;`

#### struct `FDebugDrawBodyInfo`  
`struct FDebugDrawBodyInfo`  
_L71-77_
- desc: Debug physics body info
- L73 _public member_ `FName BodyName;`
- L74 _public member_ `double Scale;`
- L75 _public member_ `FTransform BoneTfm;`
- L76 _public member_ `FTransform RetargetTfm = FTransform::Identity;`

#### struct `FDebugBodyTfmInfo`  
`struct FDebugBodyTfmInfo`  
_L79-85_
- L81 _public member_ `FVector Center;`
- L82 _public member_ `FVector TfmX;`
- L83 _public member_ `FVector TfmY;`
- L84 _public member_ `FVector TfmZ;`

#### struct `FDebugRelativeIKDrawInfo`  
`struct FDebugRelativeIKDrawInfo`  
_L88-108_
- desc: Used to hold all debug draw info for convenience
- L91 _public member_ `TArray<FDebugDrawBodyPair> SourcePairVerts;` — Source/target vert pair info
- L92 _public member_ `TArray<FDebugDrawBodyPair> TargetPairVerts;`
- L95 _public member_ `TArray<FDebugDrawBodyInfo> SourceBodyInfo;` — Body info
- L96 _public member_ `TArray<FDebugDrawBodyInfo> TargetBodyInfo;`
- L99 _public member_ `TArray<FDebugBodyTfmInfo> SourceTfmInfo;` — Body transform vecs
- L100 _public member_ `TArray<FDebugBodyTfmInfo> TargetTfmInfo;`
- L103 _public member_ `TArray<FDebugRelativeTargetPairSpace> PairRetargetInfo;` — Debug info for retarget pairs
- L105 _public member_ `TArray<FDebugDrawTargetGoal> TargetGoals;` — Final goal points with contributions
- L107 _public member_ `TArray<FName> TargetDomainBones;`

#### struct `FPinBoneSettings`  
`struct FPinBoneSettings`  
_L111-137_
- reflection: `USTRUCT(BlueprintType)`
- L116 _public member_ `FName SourceBoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pinning", meta=(ReinitializeOnEdit))`
- L120 _public member_ `EPinBoneTranslationMode TranslationMode = EPinBoneTranslationMode::CopyGlobalPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pinning", meta=(ReinitializeOnEdit))` — The method used to calculate the translation of the bone.
- L124 _public member_ `EPinBoneRotationMode RotationMode = EPinBoneRotationMode::CopyGlobalRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pinning", meta=(ReinitializeOnEdit))` — The method used to calculate the rotation of the bone.
- L128 _public member_ `double PropScalar = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pinning", meta=(ReinitializeOnEdit))` — Alpha between primary and secondary pair distance relationship
- L132 _public member_ `TObjectPtr<USkeletalMesh> PropSkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — Prop Skeletal Mesh
- L136 _public member_ `TObjectPtr<UAnimSequence> PropAnimSequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — Prop mesh to anim sequence

#### enum `ERelativeIKFrameBoneConstraintType`  
`enum class ERelativeIKFrameBoneConstraintType : uint8`  
_L140-145_
- reflection: `UENUM()`
- L142 _public enumerator_ `XYZ = 0`
- L143 _public enumerator_ `Z = 1`
- L144 _public enumerator_ `Default = XYZ`

#### struct `FRelativeIKFrameBoneConstraint`  
`struct FRelativeIKFrameBoneConstraint`  
_L147-173_
- L149 _public member_ `ERelativeIKFrameBoneConstraintType ConstraintType;`
- L151 _public member_ `double Weight;`
- L152 _public member_ `double FeasibilityWeight;`
- L153 _public member_ `FVector ContactOffset;`
- L154 _public member_ `FVector Offset;`
- L155 _public member_ `bool bAmplifyCloseWeight;`
- L156 _public member_ `double SourceDist;`
- L158 _public function_ `FRelativeIKFrameBoneConstraint()`
- L163 _public function_ `void Reset()`

#### struct `FIKRetargetRelativeIKOpSettings`  
`struct FIKRetargetRelativeIKOpSettings : public FIKRetargetOpSettingsBase`  
_L176-357_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Relative IK Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L180 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L182 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L186 _public member_ `TObjectPtr<UPhysicsAsset> TargetPhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta=(ReinitializeOnEdit))` — Target mesh physics asset for retargeting relative body pair vertices
- L190 _public member_ `TMap<FName,FName> BodyMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source Target Mapping", meta=(ReinitializeOnEdit))` — Physics body source -> target name mapping
- L194 _public member_ `double FloorThreshold = 5.00;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.1"))` — Maximum distance for which prop-floor info is baked
- L198 _public member_ `double FloorConstraintScalar = 10.00;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.0"))` — Maximum distance for which prop-floor info is baked
- L202 _public member_ `TArray<FPinBoneSettings> PinPropBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Settings", meta=(ReinitializeOnEdit))` — List of bones to pin. Should include all attach bones that may be affected by relative ik bake data
- L206 _public member_ `double DistanceThreshold = 70.00;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.1"))` — Maximum distance for which body pair info is baked
- L210 _public member_ `double DistHalfPointLambda = 0.15;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.01", ClampMax = "0.99"))` — DistHalfPointLambda*DistanceThreshold is the place where distance weight value be 0.5
- L214 _public member_ `EDistanceWeightMode DistanceWeightMode = EDistanceWeightMode::Quadratic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")` — DistHalfPointLambda*DistanceThreshold is the place where distance weight value be 0.5
- L218 _public member_ `double FeasibilityLengthBias = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")` — Bias feasibility distance weighting relative to distance threshold (+ increase target feasibility/- reduced target feasibility)
- L222 _public member_ `double ContributionSumWeight = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0", ClampMax = "1"))` — IK Goal normalization (internally multiplied by total of contribution weights)
- L226 _public member_ `int32 TemporalSmoothingRadius = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0", ClampMax = "60"))` — Frames of temporal smoothing of body pair verts (0 is no smoothing)
- L230 _public member_ `bool bIgnoreSourceScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")` — Ignore source scaling when computing relative distance relationships
- L234 _public member_ `double RetargetContactAlpha = 0.5;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Alpha from contact-body to secondary body representation in contribution pairs
- L238 _public member_ `double RetargetSpringAlpha = 0.5;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Alpha between primary and secondary pair distance relationship
- L241 _public member_ `bool bApplyImportanceWeighting = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Importance Weight")`
- L250 _public member_ `double AmplifyCloseThreshold = 15.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Importance Weight", meta=(ClampMin = "1.0"))` — Start amplifying weight at this distance (close-ish to prop)
- L254 _public member_ `double AmplifyCloseDistance = 3.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Importance Weight", meta=(ClampMin = "0.1"))` — Max weight increase cap distance (very close to prop)
- L258 _public member_ `double AmplifyScale = 6.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Importance Weight", meta=(ClampMin = "1.0", ClampMax = "20.0"))` — Bias feasibility distance weighting relative to distance threshold (+ increase target feasibility/- reduced target feasibility)
- L262 _public member_ `bool bDebugDrawBodyPairs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw source and target body pair relationships for current animation
- L266 _public member_ `TArray<FName> DebugFullRetargetPairBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta=(NotOverrideable))` — Draw full retarget space (quad) pair relationships
- L270 _public member_ `bool bDebugDrawGoalContributions = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw each pair's goal contribution (white) and show weighted final goal location (yellow)
- L274 _public member_ `bool bDebugDrawRetargetVertAverages = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw retarget pair-line for each pair contribution
- L278 _public member_ `bool bDebugDrawPhysicsBodies = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Display source and target physics bodies for baked data
- L282 _public member_ `bool bDebugDrawBodyTransforms = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Show body-local transform setup (like baked verts)
- L286 _public member_ `bool bDryRun = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Run op and display debug info but DON'T update IK Goals
- L298 _public member_ `bool bMultiBoneSolve = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Features")` — Solve for output positions using multiple interacting contact bodies
- L302 _public member_ `double MultiBoneRegularization = 0.001;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Features", meta=(ClampMin = "0.001"))` — Regularization additive constant for stabilizing multibone solve, the higher the body bones will stay at original position
- L307 _public member_ `bool bSolveWithPropScale = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Scaling")` — Add Props scale as a parameter for optimization
- L311 _public member_ `double PropScalarLearningRate = 0.001;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Scaling", meta=(ClampMin = "0.0001", ClampMax = "10"))` — Props scalar change ratio which allow to change per frame
- L315 _public member_ `double PropScalarRange = 0.25;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Scaling", meta=(ClampMin = "0", ClampMax = "10"))` — Test Parameter for prop scalar range allow to change, it will clamp prop scalar between [PinPropBone.Propscalar-PropScalarRange, PinPropBone.Propscalar+PropScalarRange]
- L319 _public member_ `double PropScalarBoneRegularization = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Scaling", meta=(ClampMin = "0.001"))` — Regularization additive constant for stabilizing prop bone position, the higher the prop bones will stay at original position
- L323 _public member_ `double PropScalarDamping = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Scaling", meta=(ClampMin = "0.001"))` — Regularization additive constant for stabilizing prop bone scalar, the higher the prop bones will stay at original Propscalar set in PinPropBone Settings
- L327 _public member_ `bool bEnableIntersectPushOut = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection")` — Enable Collison push out for Ikgoals and Props
- L331 _public member_ `TObjectPtr<UPhysicsAsset> TargetIntersectOpPhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — Target mesh physics asset for Intersect push out
- L335 _public member_ `double GlueThreshold = 5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ClampMin = "0.01"))` — Max distance to glue bodies (very close to a body)
- L339 _public member_ `double IntersectOffsetScale = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ClampMin = "0.01"))` — Max distance to glue bodies (very close to a body)
- L344 _public member_ `TArray<FName> IntersectBodies;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(NotOverrideable))` — Bone names with attached physics bodies to do trivial intersection against **NOTE: Only Sphere, Capsule and Box bodies currently supported**
- L348 _public member_ `bool bBidirectionalDistanceContactBlend = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Features")` — Distance blend body pairs towards each contact position if both can move
- L352 _public member_ `bool bApplyPostSolvePinning = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Features")` — Apply prop pin post-solve
- L356 _public member_ `double BlendPinsToSource = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test Features", meta=(ClampMin = "0", ClampMax = "1"))` — Blend from relative ik pin bone to source location

#### struct `FIKRetargetRelativeIKOp`  
`struct FIKRetargetRelativeIKOp : public FIKRetargetOpBase`  
_L360-650_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Relative IK Goals"))`
- inherits: `FIKRetargetOpBase`
- L364 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L371 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L377 _public prototype_ `virtual void RunAfterParent(FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L382 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L384 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L386 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L388 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L390 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L392 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L394 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L397 _public member_ `FIKRetargetRelativeIKOpSettings Settings;` — `UPROPERTY()`
- L400 _private prototype_ `void UpdateAnimPlayhead(float FrameTime);`
- L401 _private prototype_ `void UpdateAnimSeqData(UAnimSequence* Sequence);`
- L402 _private prototype_ `void UpdateCacheBoneChains(const FIKRetargetProcessor& InProcessor, const FIKRetargetRunIKRigOp* ParentRigOp);`
- L403 _private prototype_ `void UpdateSourceBoneMap(FName SourceBoneName);`
- L404 _private prototype_ `void UpdateTargetBoneMap(FName TargetBoneName);`
- L405 _private prototype_ `void UpdateBoneMapTfm(FName SourceBoneName, FName TargetBoneName);`
- L406 _private prototype_ `void UpdateCacheSkelInfo(const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton);`
- L407 _private prototype_ `void PreUpdateMontagePlayhead();`
- L408 _private prototype_ `void SetupRelativeIKNotifyInfoMontage();`
- L409 _private prototype_ `void UpdateRelativeIKNotifyInfoAnimSeq(UAnimInstance* SourceAnimInstance);`
- L410 _private prototype_ `void ResetCacheNotifyInfo();`
- L411 _private prototype_ `void UpdateCacheNotifyInfo(URelativeBodyBakeAnimNotify* NotifyInfo);`
- L412 _private prototype_ `void UpdateCacheChainInfo(const TArray<FTransform>& TargetPose, FName BoneName);`
- L413 _private prototype_ `void UpdateCachePropNotifyInfo(URelativePropsBakeAnimNotify* NotifyInfo);`
- L431 _private prototype_ `void InitializePinData(const FIKRetargetProcessor& Processor);`
- L432 _private prototype_ `void InitializeIntersectionData(const FIKRetargetProcessor& Processor);`
- L434 _private prototype_ `void CachePinBoneTransforms( const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose);`
- L439 _private prototype_ `FTransform ComputePinBoneTransform( const FRelativeIKPinBoneData& PinData, const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& OutTargetGlobalPose);`
- L445 _private prototype_ `static const FTransform& GetParentTransform(const FRetargetSkeleton& Skeleton, const int32 BoneIndex, const TArray<FTransform>& InPose);`
- L447 _private prototype_ `void ComputeFramePairSpaces( double SourceScale, const TArray<FTransform>& SourcePose, const TArray<FTransform>& TargetPose, int32 PairOffset, TConstArrayView<FVector3f> FramePointView, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L456 _private prototype_ `void ComputeFramePropSpaces( double SourceScale, const TArray<FName>& AmplifyBones, const TArray<FTransform>& SourcePose, const TArray<FTransform>& TargetPose, int32 PairOffset, TConstArrayView<FVector3f> FramePointView, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L466 _private prototype_ `void AmplifyImportanceWeights();`
- L468 _private prototype_ `void ApplyAverageBodyPairTargets( TArray<FIKRigGoal>& OutIKGoals, const TArray<FTransform>& TargetPose, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L474 _private prototype_ `void ApplyMatrixBodyPairTargets( TArray<FIKRigGoal>& OutIKGoals, const TArray<FTransform>& TargetPose, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L480 _private prototype_ `void ApplyIntersectPushOut( TArray<FIKRigGoal>& OutIKGoals, const TArray<FTransform>& TargetPose, FDebugRelativeIKDrawInfo& DebugInfo);`
- L485 _private prototype_ `void ApplyMatrixBodyPairTargetsWithPropScale( TArray<FIKRigGoal>& OutIKGoals, const TArray<FTransform>& TargetPose, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L491 _private prototype_ `void UpdateTargetIKGoal( TArray<FIKRigGoal>& OutIKGoals, FName TargetBoneName, const FVector& TargetWeight, const FVector& TargetGoalOffset, const FTransform& InTargetBonePose);`
- L498 _private prototype_ `void UpdatePropPinTransform( FName SourceBoneName, const FVector& TargetWeight, const FVector& TargetPropOffset, const FTransform& InTargetBonePose);`
- L504 _private prototype_ `FVector ComputeTargetWeightedOffset( FVector& OutTargetOffset, const TArray<int32>& EffectIndices, const FVector& BoneLoc, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L511 _private prototype_ `void ComputeWeightMatrixRow( Eigen::MatrixXd& WeightMatrix, int32 RowIdx, const TArray<FName>& OutBones, const TArray<int32>& EffectIndices);`
- L517 _private prototype_ `FVector ComputeTargetWeightedOffsetRow( Eigen::MatrixXd& OffsetMatrix, int32 RowIdx, const TArray<FName>& OutBones, const TArray<int32>& EffectIndices, const FVector& BoneLoc, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L526 _private prototype_ `FName ApplyBodyMap(FName BodyName) const;`
- L527 _private prototype_ `bool HasBoneDelta(FName TargetBoneName) const;`
- L528 _private prototype_ `const FTransform& GetTargetBoneDelta(FName TargetBoneName) const;`
- L540 _private prototype_ `const FTransform& OffsetTransformsForSourceBones(FName SourceBoneName) const;`
- L541 _private prototype_ `void ComputeSourceBodyTransform(FBodyTransform& OutTransform, FName SourceBoneName, const FTransform& GlobalTfm, double SourceScale) const;`
- L542 _private prototype_ `void ComputeTargetBodyTransform(FBodyTransform& OutTransform, FName SourceBoneName, const FTransform& GlobalTfm) const;`
- L544 _private prototype_ `static FVector ApplyBodyTransform(const FBodyTransform& Transform, const FVector& LocalPos);`
- L545 _private prototype_ `static FVector InverseBodyTransform(const FBodyTransform& Transform, const FVector& GlobalPos);`
- L547 _private prototype_ `void ComputeFeasibilityRange(FDoubleInterval& OutFeasibleRange, FName BoneName, const FVector& BoneLoc, const FVector& TargetOffsetVec);`
- L548 _private prototype_ `TConstArrayView<FVector3f> ApplyTemporalSmoothing(float Time, float SampleRate, int32 NumSamples, int32 NumBodies, const TArray<FVector3f>& PairLocalVerts);`
- L550 _private prototype_ `FVector GoalLocBlendCompSpace(const FIKRigGoal* Goal, const FTransform& BoneTfm) const;`
- L552 _private prototype_ `static bool CalcLineSphereIntersect(FDoubleInterval& OutRange, const FVector& Center, double Radius, const FVector& StartPoint, const FVector& EndPoint);`
- L554 _private prototype_ `static FVector CalcReferenceShapeScale3D(FKShapeElem* ShapeElem);`
- L556 _private prototype_ `static FQuat GetBodyRotation(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get local body rotation relative to parent bone
- L558 _private prototype_ `static FVector GetBodyTranslation(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get body origin relative to parent bone
- L560 _private prototype_ `static FVector GetBodyOrientedScale(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get body oriented scale vector
- L561 _private prototype_ `static FKShapeElem* FindBodyShape(const UPhysicsAsset* PhysAsset, FName BoneName);`
- L563 _private prototype_ `static double GetDistanceWeight(EDistanceWeightMode DistanceWeightMode, double Distance, double DistThreshold, double DistHalfPointLambda = 0.5);`
- L564 _private prototype_ `void GetAnimSeqFramePose(const UAnimSequence* AnimSeq, double Time, TArray<FName>& OutBones, TArray<FTransform>& OutPose) const;`
- L568 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L575 _public function_ `virtual bool HasDebugDrawing() override`
- L577 _public prototype_ `virtual void UpdateFromAnimSequence(UAnimSequence* Sequence, float FrameTime) override;`
- L580 _private prototype_ `void DebugDrawBodyPairs(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugDrawBodyPair>& BodyPairs) const;`
- L581 _private prototype_ `void DebugDrawGoalContributions(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugDrawTargetGoal>& GoalInfoLis) const;`
- L582 _private prototype_ `void DebugDrawPairVertRetarget(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugRelativeTargetPairSpace>& RetargetPairList) const;`
- L583 _private prototype_ `void DebugDrawBodies(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, UPhysicsAsset* PhysAsset, const TArray<FDebugDrawBodyInfo>& PhysBodies, bool TargetPAForSource) const;`
- L584 _private prototype_ `void DebugDrawPhysBody(FPrimitiveDrawInterface* InPDI, const FTransform& ParentTransform, double Scale, const FKShapeElem* ShapeElem, const FLinearColor& Color) const;`
- L585 _private prototype_ `void DebugDrawBodyCoords(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugBodyTfmInfo>& BodyTfms) const;`
- L587 _private prototype_ `void UpdateDebugInfo(double SourceScale, const TArray<FTransform>& SourcePose, const TArray<FTransform>& TargetPose, const FDebugRelativeIKDrawInfo& LocalDebugInfo);`
- L588 _private prototype_ `void ResetDebugInfo();`
- L591 _private member_ `FDebugRelativeIKDrawInfo DebugDrawInfo;` — Collection of all debug structures
- L593 _private member_ `static FCriticalSection DebugDataMutex;`
- L598 _private member_ `TObjectPtr<const UPhysicsAsset> TargetRelativeIKPhysicsAsset;` — TObjectPtr<const UPhysicsAsset> SourcePhysicsAsset;
- L599 _private member_ `TObjectPtr<const UPhysicsAsset> TargetIntersectOpPhysicsAsset;`
- L601 _private member_ `TObjectPtr<const UIKRigDefinition> TargetIKRig;`
- L604 _private member_ `TArray<FVector3f> SmoothedPoints;` — For runtime smoothing
- L607 _private member_ `TObjectPtr<const UAnimSequence> CacheSourceAnimSequence;` — Cache notify-related data for faster weighted goal computations
- L608 _private member_ `TObjectPtr<const URelativeBodyBakeAnimNotify> CachedNotifyInfo;`
- L609 _private member_ `TObjectPtr<const URelativePropsBakeAnimNotify> CachedPropNotifyInfo;`
- L610 _private member_ `int32 CacheMeshPairOffset = 0;`
- L611 _private member_ `int32 CachePropPairOffset = 0;`
- L612 _private member_ `float AnimSeqPlayHead;`
- L613 _private member_ `float MeshSampleRate;`
- L614 _private member_ `float PropSampleRate;`
- L617 _private member_ `TArray<FName> SourceBoneNames;` — Cache source/target bone-names
- L618 _private member_ `TArray<FName> TargetBoneNames;`
- L621 _private member_ `TArray<TArray<int32>> CacheSourceBodyEffectVertIdx;` — Array of body-vert indices affecting each joint goal (for weighted averaging)
- L622 _private member_ `TArray<FName> CacheSourceEffectBones;`
- L623 _private member_ `TSet<FName> CacheBodyBones;`
- L624 _private member_ `TArray<FName> CachePairEffectBoneNames;`
- L626 _private member_ `TArray<FRelativeIKFrameBoneConstraint> FrameBoneConstraints;`
- L629 _private member_ `TArray<FTransform> CacheSourceBoneInitTfm;` — Cache skel and IK goal info
- L630 _private member_ `TArray<FTransform> CacheTargetBoneInitTfm;`
- L631 _private member_ `TMap<FName,FTransform> CacheMapBoneSourceTargetTfm;`
- L633 _private member_ `TMap<FName, const FResolvedBoneChain*> CacheBoneChains;` — TMap<FName,FName> CacheIKBoneGoalMap;
- L634 _private member_ `TMap<FName,int32> CacheSourceSkelIndices;`
- L635 _private member_ `TMap<FName,int32> CacheTargetSkelIndices;`
- L637 _private member_ `TMap<FName,double> CacheChainLengthMap;` — Additional per-frame ik cache maps for length lookup
- L638 _private member_ `TMap<FName,FVector> CacheChainStartMap;`
- L640 _private member_ `TArray<FName> CachePinSourcePropBones;` — Cache prop bones to pin/update
- L641 _private member_ `TArray<FRelativeIKPinBoneData> CachePinBoneData;`
- L642 _private member_ `TArray<FTransform> CachePinTargetPropTransforms;`
- L643 _private member_ `TArray<int32> CachePropId2PinTargetPropSettingId;`
- L644 _private member_ `TArray<int32> CachePropId2PinBoneDataId;`
- L647 _private member_ `const FAnimMontageInstance* MontageInstance;` — Cached montage instance/segment info for early-out matching in preupdate
- L648 _private member_ `float SegmentStartTime;`
- L649 _private member_ `float SegmentEndTime;`

#### struct `FIKRetargetRelativeIKOp::FRelativeIKPinBoneData`  
`struct FRelativeIKPinBoneData`  
_L415-429_
- L417 _public member_ `EPinBoneTranslationMode TranslationMode;`
- L418 _public member_ `EPinBoneRotationMode RotationMode;`
- L420 _public member_ `FName SourceBone;` — TODO: Switch to using bone indices where possible
- L421 _public member_ `FName TargetBone;`
- L423 _public member_ `FTransform SourceTargetOffsetTfm;`
- L424 _public member_ `FTransform SourceLocalRefTfm;`
- L425 _public member_ `FTransform TargetLocalRefTfm;`
- L426 _public member_ `FQuat RefRotDelta;`
- L428 _public member_ `double PropScalar;`

#### struct `FIKRetargetRelativeIKOp::FBodyTransform`  
`struct FBodyTransform`  
_L532-538_
- desc: Internal structure for holding necessary baked->component transform data Baked data is in Source Bone orientation but at body origin
- L535 _public member_ `FTransform BoneToBody;` — TODO: Test this with FMatrix computations and see what's better/faster
- L536 _public member_ `FVector BodyScale;`
- L537 _public member_ `FTransform BodyToGlobal;`

#### class `UIKRetargetRelativeIKController`  
`class UIKRetargetRelativeIKController : public UIKRetargetOpControllerBase`  
_L654-669_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Relative IK Op
- L663 _public prototype_ `FIKRetargetRelativeIKOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRelativeIKOpSettings struct with the current settings used by the op.
- L668 _public prototype_ `void SetSettings(FIKRetargetRelativeIKOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRetargetRelativeIKOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RELATIVEIKOP_API`
- L13 _macro_ `#define LOCTEXT_NAMESPACE "RelativeIKOp"`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeIKOp/Public/RelativeIKOpModule.h` (Public)


#### class `FRelativeIKOpModule`  
`class FRelativeIKOpModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/RelativeIKOp/Public/RelativePelvicMotionOp.h` (Public)


#### struct `FIKRetargetPelvicMotionOpSettings`  
`struct FIKRetargetPelvicMotionOpSettings : public FIKRetargetOpSettingsBase`  
_L28-116_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Relative Pelvic Motion Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L32 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L34 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L38 _public member_ `TObjectPtr<UPhysicsAsset> TargetPhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta=(ReinitializeOnEdit))` — Target mesh physics asset for retargeting relative body pair vertices
- L42 _public member_ `TMap<FName,FName> BodyMapping;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Source Target Mapping", meta=(ReinitializeOnEdit))` — Physics body source -> target name mapping
- L46 _public member_ `FName TargetPelvicBone = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target", meta=(ReinitializeOnEdit))` — Physics body source -> target name mapping
- L51 _public member_ `TArray<FPinBoneSettings> CheckPropBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Settings", meta=(ReinitializeOnEdit))` — List of attach (prop) bones that can contribute to pelvic motion relationships NOTE: unlike relative ik, these bones are not pinned by the op
- L55 _public member_ `double DistanceThreshold = 70.00;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.1"))` — Maximum distance for which body pair info is baked
- L59 _public member_ `double DistHalfPointLambda = 0.15;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0.01", ClampMax = "0.99"))` — DistHalfPointLambda*DistanceThreshold is the place where distance weight value be 0.5
- L63 _public member_ `EDistanceWeightMode DistanceWeightMode = EDistanceWeightMode::Quadratic;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")` — DistHalfPointLambda*DistanceThreshold is the place where distance weight value be 0.5
- L67 _public member_ `double ContributionSumWeight = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0", ClampMax = "1"))` — IK Goal normalization (internally multiplied by total of contribution weights)
- L71 _public member_ `int32 TemporalSmoothingRadius = 15;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0", ClampMax = "60"))` — Frames of temporal smoothing of body pair verts (0 is no smoothing)
- L75 _public member_ `bool bIgnoreSourceScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")` — Ignore source scaling when computing relative distance relationships
- L79 _public member_ `double RetargetContactAlpha = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta=(ClampMin = "0", ClampMax = "1"))` — Alpha from contact-body to secondary body representation in contribution pairs
- L83 _public member_ `double RetargetSpringAlpha = 0.5;` — `UPROPERTY(BlueprintReadWrite, Category = "Parameters")` — Alpha between primary and secondary pair distance relationship
- L87 _public member_ `bool bDebugDrawBodyPairs = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw source and target body pair relationships for current animation
- L91 _public member_ `TArray<FName> DebugFullRetargetPairBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta=(NotOverrideable))` — Draw full retarget space (quad) pair relationships
- L95 _public member_ `bool bDebugDrawGoalContributions = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw each pair's goal contribution (white) and show weighted final goal location (yellow)
- L99 _public member_ `bool bDebugDrawRetargetVertAverages = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Draw retarget pair-line for each pair contribution
- L103 _public member_ `bool bDebugDrawPhysicsBodies = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Display source and target physics bodies for baked data
- L107 _public member_ `bool bDebugDrawBodyTransforms = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Show body-local transform setup (like baked verts)
- L111 _public member_ `bool bDryRun = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Run op and display debug info but DON'T update IK Goals

#### struct `FIKRetargetPelvicMotionOp`  
`struct FIKRetargetPelvicMotionOp : public FIKRetargetOpBase`  
_L119-328_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Relative Pelvic Motion"))`
- inherits: `FIKRetargetOpBase`
- L123 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L130 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L136 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L138 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L140 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L142 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L145 _public member_ `FIKRetargetPelvicMotionOpSettings Settings;` — `UPROPERTY()`
- L148 _private prototype_ `void UpdateSourceBoneMap(FName SourceBoneName);`
- L149 _private prototype_ `void UpdateTargetBoneMap(FName TargetBoneName);`
- L150 _private prototype_ `void UpdateBoneMapTfm(FName SourceBoneName, FName TargetBoneName);`
- L151 _private prototype_ `void UpdateCacheSkelInfo(const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton);`
- L152 _private prototype_ `void PreUpdateMontagePlayhead();`
- L153 _private prototype_ `void SetupRelativeIKNotifyInfoMontage();`
- L154 _private prototype_ `void UpdateRelativeIKNotifyInfoAnimSeq(UAnimInstance* SourceAnimInstance);`
- L155 _private prototype_ `void ResetCacheNotifyInfo();`
- L157 _private prototype_ `void UpdateCachePropNotifyInfo(URelativePropsBakeAnimNotify* NotifyInfo);` — void UpdateCacheNotifyInfo(URelativeBodyBakeAnimNotify* NotifyInfo);
- L158 _private prototype_ `bool KeepPropPair(FName SourceBodyBone, FName SourcePropBone);`
- L174 _private prototype_ `void InitializePinData(const FIKRetargetProcessor& Processor);`
- L176 _private prototype_ `void CachePinBoneTransforms( const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose);`
- L181 _private prototype_ `FTransform ComputePinBoneTransform( const FRelativeIKPinBoneData& PinData, const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& OutTargetGlobalPose);`
- L187 _private prototype_ `static const FTransform& GetParentTransform(const FRetargetSkeleton& Skeleton, const int32 BoneIndex, const TArray<FTransform>& InPose);`
- L189 _private prototype_ `void ComputeFramePropSpaces( double SourceScale, const TArray<FTransform>& SourcePose, const TArray<FTransform>& TargetPose, int32 PairOffset, TConstArrayView<FVector3f> FramePointView, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L198 _private prototype_ `void ApplyAverageBodyPairTargets( TArray<FTransform>& OutTargetPose, FIKRetargetProcessor& InProcessor, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L204 _private prototype_ `void UpdateTargetPelvisBone( TArray<FTransform>& OutTargetPose, int32 TargetBoneIdx, FIKRetargetProcessor& InProcessor, const FVector& TargetWeight, const FVector& TargetGoalOffset);`
- L211 _private prototype_ `FVector ComputeTargetWeightedOffset( FVector& OutTargetOffset, const TArray<int32>& EffectIndices, const FVector& BoneLoc, FDebugRelativeIKDrawInfo& DebugInfo, TArray<FDebugRelativeTargetPairSpace>& DebugPairSpaces);`
- L218 _private prototype_ `FName ApplyBodyMap(FName BodyName) const;`
- L219 _private prototype_ `bool HasBoneDelta(FName TargetBoneName) const;`
- L220 _private prototype_ `const FTransform& GetTargetBoneDelta(FName TargetBoneName) const;`
- L232 _private prototype_ `const FTransform& OffsetTransformsForSourceBones(FName SourceBoneName) const;`
- L233 _private prototype_ `void ComputeSourceBodyTransform(FBodyTransform& OutTransform, FName SourceBoneName, const FTransform& GlobalTfm, double SourceScale) const;`
- L234 _private prototype_ `void ComputeTargetBodyTransform(FBodyTransform& OutTransform, FName SourceBoneName, const FTransform& GlobalTfm) const;`
- L236 _private prototype_ `static FVector ApplyBodyTransform(const FBodyTransform& Transform, const FVector& LocalPos);`
- L237 _private prototype_ `static FVector InverseBodyTransform(const FBodyTransform& Transform, const FVector& GlobalPos);`
- L239 _private prototype_ `TConstArrayView<FVector3f> ApplyTemporalSmoothing(float Time, float SampleRate, int32 NumSamples, int32 NumBodies, const TArray<FVector3f>& PairLocalVerts);`
- L241 _private prototype_ `static FVector CalcReferenceShapeScale3D(FKShapeElem* ShapeElem);`
- L243 _private prototype_ `static FQuat GetBodyRotation(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get local body rotation relative to parent bone
- L245 _private prototype_ `static FVector GetBodyTranslation(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get body origin relative to parent bone
- L247 _private prototype_ `static FVector GetBodyOrientedScale(const UPhysicsAsset* PhysAsset, FName BoneName);` — Get body oriented scale vector
- L248 _private prototype_ `static FKShapeElem* FindBodyShape(const UPhysicsAsset* PhysAsset, FName BoneName);`
- L250 _private prototype_ `static double GetDistanceWeight(EDistanceWeightMode DistanceWeightMode, double Distance, double DistThreshold, double DistHalfPointLambda = 0.5);`
- L254 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L261 _public function_ `virtual bool HasDebugDrawing() override`
- L264 _private prototype_ `void DebugDrawBodyPairs(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugDrawBodyPair>& BodyPairs) const;`
- L265 _private prototype_ `void DebugDrawGoalContributions(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugDrawTargetGoal>& GoalInfoLis) const;`
- L266 _private prototype_ `void DebugDrawPairVertRetarget(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugRelativeTargetPairSpace>& RetargetPairList) const;`
- L267 _private prototype_ `void DebugDrawBodies(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, UPhysicsAsset* PhysAsset, const TArray<FDebugDrawBodyInfo>& PhysBodies, bool TargetPAForSource) const;`
- L268 _private prototype_ `void DebugDrawPhysBody(FPrimitiveDrawInterface* InPDI, const FTransform& ParentTransform, double Scale, const FKShapeElem* ShapeElem, const FLinearColor& Color) const;`
- L269 _private prototype_ `void DebugDrawBodyCoords(FPrimitiveDrawInterface* InPDI, const FTransform& BaseTransform, double Scale, const TArray<FDebugBodyTfmInfo>& BodyTfms) const;`
- L271 _private prototype_ `void UpdateDebugInfo(double SourceScale, const TArray<FTransform>& SourcePose, const TArray<FTransform>& TargetPose, const FDebugRelativeIKDrawInfo& LocalDebugInfo);`
- L272 _private prototype_ `void ResetDebugInfo();`
- L275 _private member_ `FDebugRelativeIKDrawInfo DebugDrawInfo;` — Collection of all debug structures
- L277 _private member_ `static FCriticalSection DebugDataMutex;`
- L281 _private member_ `FName SourcePelvicBone;`
- L283 _private member_ `TObjectPtr<const UPhysicsAsset> TargetPhysicsAsset;` — TObjectPtr<const UPhysicsAsset> SourcePhysicsAsset;
- L286 _private member_ `TArray<FVector3f> SmoothedPoints;` — For runtime smoothing
- L289 _private member_ `TObjectPtr<const UAnimSequence> CacheSourceAnimSequence;` — Cache notify-related data for faster weighted goal computations
- L291 _private member_ `TObjectPtr<const URelativePropsBakeAnimNotify> CachedPropNotifyInfo;` — TObjectPtr<const URelativeBodyBakeAnimNotify> CachedNotifyInfo;
- L292 _private member_ `int32 CacheMeshPairOffset = 0;`
- L293 _private member_ `int32 CachePropPairOffset = 0;`
- L294 _private member_ `float AnimSeqPlayHead;`
- L295 _private member_ `float MeshSampleRate;`
- L296 _private member_ `float PropSampleRate;`
- L299 _private member_ `TArray<FName> SourceBoneNames;` — Cache source/target bone-names
- L300 _private member_ `TArray<FName> TargetBoneNames;`
- L303 _private member_ `TArray<TArray<int32>> CacheSourceBodyEffectVertIdx;` — Array of body-vert indices affecting each joint goal (for weighted averaging)
- L304 _private member_ `TArray<FName> CacheSourceEffectBones;`
- L305 _private member_ `TSet<FName> CacheBodyBones;`
- L306 _private member_ `TArray<FName> CachePairEffectBoneNames;`
- L308 _private member_ `TArray<FRelativeIKFrameBoneConstraint> FrameBoneConstraints;`
- L311 _private member_ `TArray<FTransform> CacheSourceBoneInitTfm;` — Cache skel and IK goal info
- L312 _private member_ `TArray<FTransform> CacheTargetBoneInitTfm;`
- L313 _private member_ `TMap<FName,FTransform> CacheMapBoneSourceTargetTfm;`
- L314 _private member_ `TMap<FName,int32> CacheSourceSkelIndices;`
- L315 _private member_ `TMap<FName,int32> CacheTargetSkelIndices;`
- L317 _private member_ `TMap<FName,double> CacheChainLengthMap;` — Additional per-frame ik cache maps for length lookup
- L318 _private member_ `TMap<FName,FVector> CacheChainStartMap;`
- L320 _private member_ `TArray<FName> CachePinSourcePropBones;` — Cache prop bones to pin/update
- L321 _private member_ `TArray<FRelativeIKPinBoneData> CachePinBoneData;`
- L322 _private member_ `TArray<FTransform> CachePrevPinTargetPropTransforms;`
- L325 _private member_ `const FAnimMontageInstance* MontageInstance;` — Cached montage instance/segment info for early-out matching in preupdate
- L326 _private member_ `float SegmentStartTime;`
- L327 _private member_ `float SegmentEndTime;`

#### struct `FIKRetargetPelvicMotionOp::FRelativeIKPinBoneData`  
`struct FRelativeIKPinBoneData`  
_L160-172_
- L162 _public member_ `EPinBoneTranslationMode TranslationMode;`
- L163 _public member_ `EPinBoneRotationMode RotationMode;`
- L165 _public member_ `FName SourceBone;` — TODO: Switch to using bone indices where possible
- L166 _public member_ `FName TargetBone;`
- L168 _public member_ `FTransform SourceTargetOffsetTfm;`
- L169 _public member_ `FTransform SourceLocalRefTfm;`
- L170 _public member_ `FTransform TargetLocalRefTfm;`
- L171 _public member_ `FQuat RefRotDelta;`

#### struct `FIKRetargetPelvicMotionOp::FBodyTransform`  
`struct FBodyTransform`  
_L224-230_
- desc: Internal structure for holding necessary baked->component transform data Baked data is in Source Bone orientation but at body origin
- L227 _public member_ `FTransform BoneToBody;` — TODO: Test this with FMatrix computations and see what's better/faster
- L228 _public member_ `FVector BodyScale;`
- L229 _public member_ `FTransform BodyToGlobal;`

#### class `UIKRetargetPelvicMotionController`  
`class UIKRetargetPelvicMotionController : public UIKRetargetOpControllerBase`  
_L332-347_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Relative Pelvic Motion Op
- L341 _public prototype_ `FIKRetargetPelvicMotionOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRelativeIKOpSettings struct with the current settings used by the op.
- L346 _public prototype_ `void SetSettings(FIKRetargetPelvicMotionOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRetargetRelativeIKOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API RELATIVEIKOP_API`
- L15 _macro_ `#define LOCTEXT_NAMESPACE "RelativePelvicMotionOp"`
