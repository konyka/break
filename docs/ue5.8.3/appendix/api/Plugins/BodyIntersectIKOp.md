# Plugins / BodyIntersectIKOp

- module root: `Plugins/Experimental/Animation/RelativeIKOp/Source/BodyIntersectIKOp`
- headers: 3; symbols: 111
- symbol kinds: class=4, enum=1, enumerator=7, function=1, macro=2, member=46, prototype=42, struct=8
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, IKRig, MeshDescription, Renderer, SkeletalMeshDescription, StaticMeshDescription
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RelativeIKOp/Source/BodyIntersectIKOp/Public/BodyIntersectIKOp.h` (Public)


#### struct `FDebugBodyIntersectDrawInfo`  
`struct FDebugBodyIntersectDrawInfo`  
_L24-34_
- desc: Used to hold all debug draw info for convenience
- L27 _public member_ `TArray<bool> TargetIntersectDetected;` — Intersect info
- L28 _public member_ `TArray<TTuple<FName,FTransform>> TargetIntersectTfms;`
- L29 _public member_ `TArray<TTuple<FName,FTransform>> GoalIntersectTfms;`
- L31 _public member_ `TArray<TTuple<float,float,FTransform>> PropIntersectTfms;`
- L33 _public member_ `TArray<TTuple<float,FTransform>> PoleIntersectTfms;`

#### struct `FIKPropIntersectSettings`  
`struct FIKPropIntersectSettings`  
_L37-65_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Prop Intersect Settings"))`
- L43 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings")` — The name of the attach bone or IK bone this intersection references
- L48 _public member_ `bool bPinBone = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings")` — Optionally also move this bone TODO: Need to figure out how to interact with blend and relative ik pin bones (RunAfterParent+offset?)
- L52 _public member_ `float CapsuleRadius = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings", meta=(ClampMin="0.0"))` — Capsule radius for prop intersector
- L56 _public member_ `float CapsuleLength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings", meta=(ClampMin="0.0"))` — Capsule length for prop intersector
- L60 _public member_ `FRotator CapsuleRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings")` — Capsule orientation relative to bone
- L64 _public member_ `FVector CapsuleTranslation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prop Intersect Settings")` — Capsule translation relative to bone

#### struct `FIKGoalIntersectShapeSettings`  
`struct FIKGoalIntersectShapeSettings`  
_L68-87_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Goal Intersect Settings"))`
- L74 _public member_ `FName Goal = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal Intersect Settings")` — The IK Goal Name (See Run IK Rig Op) to intersect
- L77 _public member_ `FVector GoalShapeScale = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal Intersect Settings", meta = (ClampMin="0.0"))` — Shape scale , Todo: need to be updated with shape property
- L80 _public member_ `FVector GoalShapeOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal Intersect Settings")` — Local offset of shape from goal bone
- L83 _public member_ `FName PropIntersectBone = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal Intersect Settings")` — Prop bone/IK bone to move together with (must be in prop intersect list!)
- L86 _public member_ `double BlendMultiMaxOffset = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Goal Intersect Settings", meta=(ClampMin="0.0", ClampMax="1.0"))` — Alpha blend on bone motion relative to prop bone

#### struct `FIKPoleVectorIntersectSettings`  
`struct FIKPoleVectorIntersectSettings`  
_L90-105_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pole Vector Settings"))`
- L96 _public member_ `FName BodyName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pole Vector Intersect Settings", meta=(ReinitializeOnEdit))` — The body along ik chain to check intersections and apply pole vector rotation
- L100 _public member_ `double SphereScale = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pole Vector Intersect Settings", meta = (ClampMin="0.0"))` — Sphere size scale (base radius is body min radius or 1.0) for intersection checks
- L104 _public member_ `FVector SphereOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pole Vector Intersect Settings")` — Local sphere offset from body bone

#### struct `FIKRetargetBodyIntersectIKOpSettings`  
`struct FIKRetargetBodyIntersectIKOpSettings : public FIKRetargetOpSettingsBase`  
_L108-144_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Body Intersect IK Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L112 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L114 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L118 _public member_ `TObjectPtr<UPhysicsAsset> TargetPhysicsAssetOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta=(ReinitializeOnEdit))` — Target physics asset for checking intersections against
- L122 _public member_ `bool bEnableGoalIntersect = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — Apply intersection delta to goals
- L126 _public member_ `TArray<FIKGoalIntersectShapeSettings> IntersectGoalSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — IK Goals Shape intersect against physics asset bodies
- L130 _public member_ `TArray<FIKPropIntersectSettings> PropIntersectSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit))` — Prop intersection shape and bone info (must match goal intersect names if moving together)
- L135 _public member_ `TArray<FName> IntersectBodies;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intersection", meta=(ReinitializeOnEdit, NotOverrideable))` — Bone names with attached physics bodies to do trivial intersection against **NOTE: Only Sphere, Capsule and Box bodies currently supported**
- L139 _public member_ `bool bEnablePoleVectorIntersect = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pole Vector", meta=(ReinitializeOnEdit))` — Check bodies in Pole Vector Intersect Settings for intersection and try to fixup using pole vector rotation
- L143 _public member_ `TArray<FIKPoleVectorIntersectSettings> PoleVectorIntersectSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pole Vector", meta=(ReinitializeOnEdit))` — Body settings for pole vector intersection fixup

#### struct `FPoleVectorChainIntersector`  
`struct FPoleVectorChainIntersector`  
_L147-185_
- desc: Per-chain pole vector intersection functionality
- L149 _public prototype_ `void Initialize( const FIKRetargetBodyIntersectIKOpSettings* InSettings, const TArray<int32>& InBodySettingsIdx, const FResolvedBoneChain* InTargetChain, const FTargetSkeleton& InTargetSkeleton);`
- L155 _public prototype_ `void ApplyIntersectRotation( const FRetargetSkeleton& TargetSkeleton, TArray<FTransform>& OutTargetGlobalPose, FDebugBodyIntersectDrawInfo& DebugInfo) const;`
- L160 _public prototype_ `FVector GetIntersectDelta( const FTransform& PoleTfm, FKSphereElem* PoleSphere, const TArray<FTransform>& TargetGlobalPose, FDebugBodyIntersectDrawInfo& DebugInfo) const;`
- L166 _public prototype_ `FVector CalculatePoleVector( const EAxis::Type& PoleAxis, const TArray<int32>& BoneIndices, const TArray<FTransform>& GlobalPose) const;`
- L171 _public prototype_ `FVector GetChainAxisNormalized( const TArray<int32>& BoneIndices, const TArray<FTransform>& GlobalPose) const;`
- L175 _public member_ `TObjectPtr<const UPhysicsAsset> PhysicsAsset;`
- L177 _public member_ `const FIKRetargetBodyIntersectIKOpSettings* Settings;`
- L178 _public member_ `const FResolvedBoneChain* TargetBoneChain;`
- L180 _public member_ `TArray<int32> PoleBodiesSettingsIdx;`
- L181 _public member_ `TArray<int32> PoleBonesIdx;`
- L182 _public member_ `TArray<int32> IntersectBonesIdx;`
- L184 _public member_ `TArray<int32> AllChildrenWithinChain;`

#### struct `FIKRetargetBodyIntersectIKOp`  
`struct FIKRetargetBodyIntersectIKOp : public FIKRetargetOpBase`  
_L188-289_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Body Intersect Goals"))`
- inherits: `FIKRetargetOpBase`
- L192 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L199 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L205 _public prototype_ `virtual void RunAfterParent( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L211 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L213 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L215 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L217 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L219 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L222 _public member_ `FIKRetargetBodyIntersectIKOpSettings Settings;` — `UPROPERTY()`
- L233 _private prototype_ `void InitPoleVectorIntersectors(const TArray<FResolvedBoneChain>& TargetChains, const FTargetSkeleton& InTargetSkeleton);`
- L235 _private prototype_ `FVector GetTotalIntersectDelta( int32 CollisionProxyIndex, const FKShapeElem* IntersectShape, const FTransform& IntersectTfm, const TArray<FTransform>& TargetGlobalPose, const FTargetSkeleton& TargetSkeleton, FDebugBodyIntersectDrawInfo& DebugInfo);`
- L243 _private prototype_ `void UpdatePropMoves(FName PropLinkBone, int32 IntersectIndex);`
- L245 _private prototype_ `FVector GoalLocBlendCompSpace(const FIKRigGoal* Goal, const FTransform& BoneTfm) const;`
- L246 _private prototype_ `void SetGoalPosFromCompSpace(FIKRigGoal* Goal, const FTransform& BoneTfm, const FVector& CompSpaceLoc) const;`
- L250 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L257 _public function_ `virtual bool HasDebugDrawing() override`
- L260 _private prototype_ `void DebugDrawPhysBody(FPrimitiveDrawInterface* InPDI, const FTransform& ParentTransform, const FVector& Scale, const FKShapeElem* ShapeElem, const FLinearColor& Color) const;`
- L262 _private prototype_ `void ResetDebugInfo();`
- L264 _private prototype_ `FKShapeElem* CopyShape(FKShapeElem* InShape);`
- L267 _private member_ `FDebugBodyIntersectDrawInfo DebugDrawInfo;` — Collection of all debug structures
- L269 _private member_ `static FCriticalSection DebugDataMutex;`
- L272 _private member_ `TObjectPtr<const UPhysicsAsset> PhysicsAsset;`
- L275 _private member_ `TArray<const FIKRigGoal*> IntersectIKGoals;` — Cache ik goals to check
- L278 _private member_ `TArray<FPoleVectorChainIntersector> PoleVectorChainIntersectors;` — Array (per-chain w/ pv bodies) of intersectors
- L282 _private member_ `TArray<TPair<int32,FVector>> UpdatePropDeltas;` — Attach bone updates to pin TODO: Decide if these should be deltas or absolute locs
- L285 _private member_ `TArray<FIntersectFrameDeltaInfo> FrameDeltaInfo;` — Per-frame goal deltas
- L288 _private member_ `TArray<TArray<int32>> MoveWithPropGroups;` — Move with prop groups

#### struct `FIKRetargetBodyIntersectIKOp::FIntersectFrameDeltaInfo`  
`struct FIntersectFrameDeltaInfo`  
_L225-231_
- L227 _public member_ `FIKRigGoal* GoalPtr = nullptr;`
- L228 _public member_ `FTransform StartBodyTfm = FTransform::Identity;`
- L229 _public member_ `FVector StartGoalLoc = FVector::ZeroVector;`
- L230 _public member_ `FVector IntersectDelta = FVector::ZeroVector;`

#### class `UIKRetargetBodyIntersectController`  
`class UIKRetargetBodyIntersectController : public UIKRetargetOpControllerBase`  
_L293-308_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing BodyIntersectIK Op
- L302 _public prototype_ `FIKRetargetBodyIntersectIKOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetBodyIntersectIKOp struct with the current settings used by the op.
- L307 _public prototype_ `void SetSettings(FIKRetargetBodyIntersectIKOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRetargetBodyIntersectIKOp struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BODYINTERSECTIKOP_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "BodyIntersectIKOp"`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/BodyIntersectIKOp/Public/BodyIntersectIKOpModule.h` (Public)


#### class `FBodyIntersectIKOpModule`  
`class FBodyIntersectIKOpModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Animation/RelativeIKOp/Source/BodyIntersectIKOp/Public/PhysicsBodyHelpers.h` (Public)


#### enum `EBodyIntersectPairType`  
`enum class EBodyIntersectPairType : uint8`  
_L19-29_
- L21 _public enumerator_ `SphereSphere`
- L22 _public enumerator_ `SphereBox`
- L23 _public enumerator_ `BoxBox`
- L24 _public enumerator_ `SphereCapsule`
- L25 _public enumerator_ `BoxCapsule`
- L26 _public enumerator_ `CapsuleCapsule`
- L28 _public enumerator_ `Unknown`

#### class `FBodyIntersectUtils`  
`class FBodyIntersectUtils`  
_L34-50_
- desc: Helper static class providing physics body intersection delta functions
- L37 _public prototype_ `static double CalcIntersectionPairDelta(const FTransform& GoalShapeTfm, const FKShapeElem* GoalShapeElem, const FTransform& TargetShapeTfm, const FKShapeElem* TargetShapeElem, FVector& OutDeltaDir);`
- L38 _public prototype_ `static double CalcIntersectionPairDelta(const FTransform& GoalShapeTfm, const FKAggregateGeom* GoalAggGeom, const FTransform& TargetShapeTfm, const FKAggregateGeom* TargetAggGeom, FVector& OutDeltaDir);`
- L40 _private prototype_ `static EBodyIntersectPairType CalcBodyIntersectPairType(const FKShapeElem* ShapeElem1, const FKShapeElem* ShapeElem2, bool &NeedInverse);`
- L42 _private prototype_ `static double CalcSphereSphereShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKSphereElem* ShapeElem1, const FTransform& ShapeTfm2, const FKSphereElem* ShapeElem2);`
- L43 _private prototype_ `static double CalcSphereBoxShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKSphereElem* ShapeElem1, const FTransform& ShapeTfm2, const FKBoxElem* ShapeElem2);`
- L44 _private prototype_ `static double CalcSphereCapsuleShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKSphereElem* ShapeElem1, const FTransform& ShapeTfm2, const FKSphylElem* ShapeElem2);`
- L45 _private prototype_ `static double CalcBoxBoxShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKBoxElem* ShapeElem1, const FTransform& ShapeTfm2, const FKBoxElem* ShapeElem2);`
- L46 _private prototype_ `static double CalcBoxCapsuleShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKBoxElem* ShapeElem1, const FTransform& ShapeTfm2, const FKSphylElem* ShapeElem2);`
- L47 _private prototype_ `static double CalcCapsuleCapsuleShapeDelta(FVector& OutDeltaDir, const FTransform& ShapeTfm1, const FKSphylElem* ShapeElem1, const FTransform& ShapeTfm2, const FKSphylElem* ShapeElem2);`
- L49 _private prototype_ `static double SegmentDistToAABB(const FVector& A, const FVector& B, const FVector& BoxMin, const FVector& BoxMax, FVector& OutSeg, FVector& OutBox);`

#### class `FPhysShapeUtils`  
`class FPhysShapeUtils`  
_L52-60_
- L55 _public prototype_ `static double CalcShapeSmallRadius(const FKShapeElem* ShapeElem);`
- L56 _public prototype_ `static double CalcShapeAvgRadius(const FKShapeElem* ShapeElem);`
- L58 _public prototype_ `static const FKShapeElem* FindBodyShape(const UPhysicsAsset* PhysAsset, FName BoneName);`
- L59 _public prototype_ `static const FKAggregateGeom* FindBodyAggGeom(const UPhysicsAsset* PhysAsset, FName BoneName);`
