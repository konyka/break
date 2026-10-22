# Plugins / FullBodyIK

- module root: `Plugins/Experimental/FullBodyIK/Source/FullBodyIK`
- headers: 10; symbols: 280
- symbol kinds: class=11, delegate=4, enum=5, enumerator=13, function=49, macro=4, member=116, namespace=4, prototype=57, struct=16, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: ControlRig, Core, Eigen, RigVM

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Private/RigUnit_FullbodyIK.h` (Private)


#### struct `FFBIKEndEffector`  
`struct FFBIKEndEffector`  
_L19-77_
- reflection: `USTRUCT()`
- L26 _public member_ `FRigElementKey Item;` — `UPROPERTY(meta = (Constant, CustomWidget = "BoneName"))` — The last item in the chain to solve - the effector
- L29 _public member_ `FVector Position;` — `UPROPERTY()`
- L32 _public member_ `float PositionAlpha = 1.f;` — `UPROPERTY()`
- L35 _public member_ `int32 PositionDepth = 1000;` — `UPROPERTY()`
- L38 _public member_ `FQuat Rotation;` — `UPROPERTY()`
- L41 _public member_ `float RotationAlpha = 1.f;` — `UPROPERTY()`
- L44 _public member_ `int32 RotationDepth = 1000;` — `UPROPERTY()`
- L51 _public member_ `float Pull = 0.f;` — `UPROPERTY()` — Clamps the total length to target by this scale for each iteration This helps to stabilize solver to reduce singularity by avoiding to try to reach target too far.
- L53 _public function_ `FFBIKEndEffector() : Item(NAME_None, ERigElementType::Bone) , Position(FVector::ZeroVector) , Rotation(FQuat::Identity)`
- L60 _public function_ `FFBIKEndEffector(const FFBIKEndEffector& Other)`
- L65 _public function_ `FFBIKEndEffector& operator = (const FFBIKEndEffector& Other)`

#### struct `FRigUnit_FullbodyIK_WorkData`  
`struct FRigUnit_FullbodyIK_WorkData`  
_L80-104_
- reflection: `USTRUCT()`
- L84 _public function_ `FRigUnit_FullbodyIK_WorkData()`
- L89 _public member_ `TArray<FFBIKLinkData> LinkData;` — list of Link Data for solvers - joints
- L91 _public member_ `TMap<int32, FFBIKEffectorTarget> EffectorTargets;` — Effector Targets - search key is LinkData Index
- L93 _public member_ `TArray<int32> EffectorLinkIndices;` — End Effector Link Indices - EndEffector index to LinkData index
- L95 _public member_ `TMap<int32, FRigElementKey> LinkDataToHierarchyIndices;` — Map from LinkData index to Rig Hierarchy Index
- L97 _public member_ `TMap<FRigElementKey, int32> HierarchyToLinkDataMap;` — Map from Rig Hierarchy Index to LinkData index
- L99 _public member_ `TArray<ConstraintType> InternalConstraints;` — Constraints data
- L101 _public member_ `FJacobianSolver_FullbodyIK IKSolver;` — Current Solver
- L103 _public member_ `TArray<FJacobianDebugData> DebugData;` — Debug Data

#### struct `FRigUnit_FullbodyIK`  
`struct FRigUnit_FullbodyIK : public FRigUnit_HighlevelBaseMutable`  
_L110-157_
- reflection: `USTRUCT(meta=(DisplayName="Fullbody IK", Category="Hierarchy", Keywords="Multi, Effector, N-Chain, FB, IK", Deprecated = "5.0"))`
- inherits: `FRigUnit_HighlevelBaseMutable`
- desc: Based on Jacobian solver at core, this can solve multi chains within a root using multi effectors
- L114 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L117 _public function_ `FRigUnit_FullbodyIK() : Root(NAME_None, ERigElementType::Bone)`
- L127 _public member_ `FRigElementKey Root;` — `UPROPERTY(meta = (Input, Constant, CustomWidget = "BoneName"))` — The first bone in the chain to solve
- L130 _public member_ `TArray<FFBIKEndEffector> Effectors;` — `UPROPERTY(meta = (Input))`
- L133 _public member_ `TArray<FFBIKConstraintOption> Constraints;` — `UPROPERTY(EditAnywhere, Category = FRigUnit_Jacobian, meta = (Input))`
- L136 _public member_ `FSolverInput SolverProperty;` — `UPROPERTY(meta = (Input, Constant))`
- L139 _public member_ `FMotionProcessInput MotionProperty;` — `UPROPERTY(meta = (Input, Constant))`
- L147 _public member_ `bool bPropagateToChildren = true;` — `UPROPERTY(meta = (Input))` — If set to true all of the global transforms of the children of this bone will be recalculated based on their local transforms. Note: This is computationally more expensive than turning it off.
- L150 _public member_ `FFBIKDebugOption DebugOption;` — `UPROPERTY(meta = (Input))`
- L153 _public member_ `FRigUnit_FullbodyIK_WorkData WorkData;` — `UPROPERTY(transient)`
- L155 _public prototype_ `RIGVM_METHOD() virtual FRigVMStructUpgradeInfo GetUpgradeInfo() const override;`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKConstraint.h` (Public)


#### enum `EConstraintType`  
`enum class EConstraintType : uint8`  
_L10-15_
- L12 _public enumerator_ `Free`
- L13 _public enumerator_ `Limit` — currently hard limit
- L14 _public enumerator_ `Locked`

#### struct `FMotionBase`  
`struct FMotionBase`  
_L17-76_
- L19 _public function_ `FMotionBase(const FVector& InBaseAxis) : BaseAxis(InBaseAxis) , LinearStiffness(1.f) , AngularStiffness(0.f)`
- L25 _public function_ `void SetAngularStiffness(float InStiffness)`
- L30 _public function_ `void SetLinearStiffness(float InStiffness)`
- L35 _public function_ `float GetAngularMotionScale() const`
- L40 _public function_ `float GetLinearMotionScale() const`
- L45 _public function_ `float GetAngularStiffness() const`
- L50 _public function_ `float GetLinearStiffness() const`
- L55 _public function_ `bool IsLinearMotionAllowed() const`
- L61 _public function_ `bool IsAngularMotionAllowed() const`
- L68 _public member_ `FVector BaseAxis;` — rotation axis that this motion represents
- L74 _private member_ `float LinearStiffness;` — this is in range of [0, 1] to define how stiff this is for this rotaiton axis if 1, it doesn't move
- L75 _private member_ `float AngularStiffness;`

#### struct `FFBIKLinkData`  
`struct FFBIKLinkData`  
_L78-279_
- L80 _public function_ `FFBIKLinkData() : ParentLinkIndex(INDEX_NONE) , Length(0.f) , LinkTransform(FTransform::Identity) , LinearMotionStrength(-1.f) , AngularMotionStrength(-1.f) , LocalFrame(FQuat::Identity)`
- L90 _public prototype_ `~FFBIKLinkData() = default;`
- L92 _public function_ `int32 GetNumMotionBases() const`
- L95 _public function_ `bool IsLinearMotionAllowed() const` — return true if any of my motion bases allow linear motion
- L110 _public function_ `bool IsLinearMotionAllowed(int32 BaseIndex) const` — return true if any specific motion base by index allows linear motion
- L121 _public function_ `bool IsAngularMotionAllowed() const` — return true if any of my motion bases allow angular motion
- L136 _public function_ `bool IsAngularMotionAllowed(int32 BaseIndex) const` — return true if any specific motion base by index allows linear motion
- L147 _public function_ `void AddMotionStrength(float InLinearScale, float InAngularScale)` — this is with
- L158 _public function_ `void FinalizeForSolver()` — @todo: may refactor this to somewhere else currently I don't really have to save this anymore
- L184 _public function_ `float GetLinearMotionStrength() const` — @TODO:  stiff ness per rotation axis?
- L189 _public function_ `float GetAngularMotionStrength() const`
- L194 _public function_ `void ResetMotionBases()`
- L199 _public function_ `void AddMotionBase(const FMotionBase& InLinkAxis)`
- L207 _public function_ `const FMotionBase& GetMotionBase(int32 Index) const`
- L213 _public function_ `FMotionBase& GetMotionBase(int32 Index)`
- L219 _public function_ `const FVector& GetRotationAxis(int32 Index) const`
- L231 _public member_ `int32 ParentLinkIndex;`
- L232 _public member_ `float Length;` — reference link length
- L234 _public function_ `void SetTransform(const FTransform& InTransform)`
- L240 _public function_ `const FTransform& GetTransform() const`
- L245 _public function_ `void SavePreviousTransform()`
- L250 _public function_ `const FTransform& GetPreviousTransform() const`
- L257 _private member_ `FTransform LinkTransform;` — link position is based on root space
- L258 _private member_ `FTransform PreviousLinkTransform;` — before modified, we save this for debugging
- L263 _private member_ `float LinearMotionStrength;` — this motion strength is calculated by effector's strength but stiffness can control that range, where this joint lies stiffness is expected to be in range of [0, 1]
- L264 _private member_ `float AngularMotionStrength;`
- L266 _private member_ `TArray<float> LinearMotionStrengthArray;`
- L267 _private member_ `TArray<float> AngularMotionStrengthArray;`
- L273 _private member_ `TArray<FMotionBase> MotionBaseAxes;` — this is the number of axes, it wants to generate motion w.r.t. this is often rotation axis in the jacobian method, but it does contain more property on how it applies it Stiff is now moved Motion Base. Each axis allow different motion property
- L278 _public member_ `FQuat LocalFrame;` — local frame - ideally we can make this to be angular vs linear different, but for now we just have one frame

#### struct `FPositionLimitConstraint`  
`struct FPositionLimitConstraint`  
_L281-306_
- L283 _public function_ `FPositionLimitConstraint() : BaseIndex(INDEX_NONE) , ConstrainedIndex(INDEX_NONE) , bXLimitSet(false) , bYLimitSet(false) , bZLimitSet(false) , Limit(0.f)`
- L292 _public member_ `int32 BaseIndex;`
- L293 _public member_ `int32 ConstrainedIndex;`
- L296 _public member_ `FTransform RelativelRefPose;` — frame of reference for this
- L299 _public member_ `uint8 bXLimitSet : 1;` — xyz
- L300 _public member_ `uint8 bYLimitSet : 1;`
- L301 _public member_ `uint8 bZLimitSet : 1;`
- L303 _public member_ `FVector Limit;`
- L305 _public prototype_ `bool ApplyConstraint(TArray<FFBIKLinkData>& InOutLinkData, TArray<FTransform>& InOutLocalTransforms);`

#### struct `FRotationLimitConstraint`  
`struct FRotationLimitConstraint`  
_L308-334_
- L310 _public function_ `FRotationLimitConstraint() : BaseIndex(INDEX_NONE) , ConstrainedIndex(INDEX_NONE) , bXLimitSet(false) , bYLimitSet(false) , bZLimitSet(false) , Limit(0.f)`
- L319 _public member_ `int32 BaseIndex;`
- L320 _public member_ `int32 ConstrainedIndex;`
- L323 _public member_ `FQuat BaseFrameOffset;` — frame of reference for this
- L324 _public member_ `FTransform RelativelRefPose;`
- L327 _public member_ `uint8 bXLimitSet : 1;` — xyz - twist/swing1/swing2
- L328 _public member_ `uint8 bYLimitSet : 1;`
- L329 _public member_ `uint8 bZLimitSet : 1;`
- L331 _public member_ `FVector Limit;`
- L333 _public prototype_ `bool ApplyConstraint(TArray<FFBIKLinkData>& InOutLinkData, TArray<FTransform>& InOutLocalTransforms);`

#### struct `FPoleVectorConstraint`  
`struct FPoleVectorConstraint`  
_L336-349_
- L338 _public member_ `int32 BoneIndex;`
- L339 _public member_ `int32 ParentBoneIndex;`
- L340 _public member_ `int32 ChildBoneIndex;`
- L344 _public member_ `bool bUseLocalDir = true;` — if you use local dir, it will be local dir and will be calculated based on local frame every time if not, it will interpret PoleVector as a target location in the space (global space)
- L345 _public member_ `FVector PoleVector;`
- L347 _public prototype_ `bool ApplyConstraint(TArray<FFBIKLinkData>& InOutLinkData, TArray<FTransform>& InOutLocalTransforms);`
- L348 _public prototype_ `FVector CalculateCurrentPoleVectorDir(const FTransform& ParentTransform, const FTransform& BoneTransform, const FTransform& ChildTransform, const FQuat& LocalFrame) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API FULLBODYIK_API`
- L352 _typedef_ `using ConstraintType = TVariant<FRotationLimitConstraint, FPositionLimitConstraint, FPoleVectorConstraint>;`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKConstraintLib.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace FBIKConstraintLib`
- L14 _prototype_ `void ApplyConstraint(TArray<FFBIKLinkData>& InOutLinkData, TArray<ConstraintType>* Constraints);` (scope `FBIKConstraintLib`) — constraint related
- L15 _prototype_ `void BuildConstraints(const TArrayView<const FFBIKConstraintOption>& Constraints, TArray<ConstraintType>& OutConstraints, const URigHierarchy* Hierarchy, TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FRigElementKey>& LinkDataToHierarchyIndices, const TMap<FRigElementKey, int32>& HierarchyToLinkDataMap);` (scope `FBIKConstraintLib`)

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKConstraintOption.h` (Public)


#### enum `EFBIKBoneLimitType`  
`enum class EFBIKBoneLimitType : uint8`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `Free`
- L12 _public enumerator_ `Limit` — currently hard limit
- L13 _public enumerator_ `Locked`

#### struct `FFBIKBoneLimit`  
`struct FFBIKBoneLimit`  
_L17-40_
- reflection: `USTRUCT()`
- L21 _public function_ `FFBIKBoneLimit() : LimitType_X(EFBIKBoneLimitType::Locked) , LimitType_Y(EFBIKBoneLimitType::Locked) , LimitType_Z(EFBIKBoneLimitType::Locked) , Limit(EForceInit::ForceInitToZero)`
- L29 _public member_ `EFBIKBoneLimitType LimitType_X;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L32 _public member_ `EFBIKBoneLimitType LimitType_Y;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L35 _public member_ `EFBIKBoneLimitType LimitType_Z;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L39 _public member_ `FVector Limit;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — currently no negative limit, for position we may need min/max

#### enum `EPoleVectorOption`  
`enum class EPoleVectorOption : uint8`  
_L43-47_
- reflection: `UENUM()`
- L45 _public enumerator_ `Direction`
- L46 _public enumerator_ `Location` — Direction,   The polevector will indicate a direction vector in their local bone space

#### struct `FFBIKConstraintOption`  
`struct FFBIKConstraintOption`  
_L50-120_
- reflection: `USTRUCT()`
- L54 _public function_ `FFBIKConstraintOption() : Item(NAME_None, ERigElementType::Bone) , LinearStiffness(FVector(1.f)) , AngularStiffness(FVector::ZeroVector) , PoleVector(FVector::RightVector) , OffsetRotation(FRotator::ZeroRotator)`
- L69 _public member_ `FRigElementKey Item;` — `UPROPERTY(EditAnywhere, meta = (Constant), Category=FFBIKConstraintOption)` — Bone Name
- L72 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L75 _public member_ `bool bUseStiffness = true;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L79 _public member_ `FVector LinearStiffness;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — Scale of [0, 1] and applied to linear motion strength - linear stiffness works on their local frame
- L83 _public member_ `FVector AngularStiffness;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — Scale of [0, 1] and applied to angular motion strength, xyz is applied to twist, swing1, swing2
- L86 _public member_ `bool bUseAngularLimit = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L90 _public member_ `FFBIKBoneLimit AngularLimit;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — Angular delta limit of this joints local transform. [-Limit, Limit]
- L93 _public member_ `bool bUsePoleVector = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L96 _public member_ `EPoleVectorOption PoleVectorOption = EPoleVectorOption::Direction;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)`
- L100 _public member_ `FVector PoleVector;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — Pole Vector in their local space
- L104 _public member_ `FRotator OffsetRotation;` — `UPROPERTY(EditAnywhere, Category = FFBIKConstraintOption)` — this is offset rotation applied when constructing the local frame
- L106 _public function_ `bool IsLinearlyLimited() const`
- L111 _public function_ `bool IsAngularlyLimited() const`

#### struct `FMotionProcessInput`  
`struct FMotionProcessInput`  
_L123-132_
- reflection: `USTRUCT(BlueprintType)`
- L128 _public member_ `bool bForceEffectorRotationTarget = false;` — `UPROPERTY(EditAnywhere, Category = FMotionProcessInput)`
- L131 _public member_ `bool bOnlyApplyWhenReachedToTarget = false;` — `UPROPERTY(EditAnywhere, Category = FMotionProcessInput)`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKDebugOption.h` (Public)


#### struct `FFBIKDebugOption`  
`struct FFBIKDebugOption`  
_L8-42_
- reflection: `USTRUCT(BlueprintType)`
- L13 _public member_ `bool bDrawDebugHierarchy = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L17 _public member_ `bool bColorAngularMotionStrength = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)` — use red channel
- L21 _public member_ `bool bColorLinearMotionStrength = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)` — use green channel
- L24 _public member_ `bool bDrawDebugAxes = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L27 _public member_ `bool bDrawDebugEffector = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L30 _public member_ `bool bDrawDebugConstraints = false;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L33 _public member_ `FTransform DrawWorldOffset;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L36 _public member_ `float DrawSize = 5.f;` — `UPROPERTY(EditAnywhere, Category = FFBIKDebugOption)`
- L38 _public function_ `FFBIKDebugOption()`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKShared.h` (Public)


#### class `FJacobianSolver_FullbodyIK`  
`class FJacobianSolver_FullbodyIK : public FJacobianSolverBase`  
_L12-20_
- inherits: `FJacobianSolverBase`
- L15 _public function_ `FJacobianSolver_FullbodyIK() : FJacobianSolverBase()`
- L18 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`
- L19 _private prototype_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const override;`

#### struct `FSolverInput`  
`struct FSolverInput`  
_L23-77_
- reflection: `USTRUCT(BlueprintType)`
- L34 _public member_ `float LinearMotionStrength = 3.f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — This value is applied to the target information for effectors, which influence back to Joint's motion that are affected by the end effector The reason min/max is used when we apply the depth through the chain that are affected
- L37 _public member_ `float MinLinearMotionStrength = 2.f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)`
- L45 _public member_ `float AngularMotionStrength = 3.f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — This value is applied to the target information for effectors, which influence back to Joint's motion that are affected by the end effector The reason min/max is used when we apply the depth through the chain that are affected
- L48 _public member_ `float MinAngularMotionStrength = 2.f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)`
- L52 _public member_ `float DefaultTargetClamp = 0.2f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — This is a scale value (range from 0-0.7) that is used to stablize the target vector. If less, it's more stable, but it can reduce speed of converge.
- L58 _public member_ `float Precision = 0.1f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — The precision to use for the solver
- L64 _public member_ `float Damping = 30.f;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — The precision to use for the fabrik solver
- L70 _public member_ `int32 MaxIterations = 30;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — The maximum number of iterations. Values between 4 and 16 are common.
- L76 _public member_ `bool bUseJacobianTranspose = false;` — `UPROPERTY(EditAnywhere, Category = FSolverInput)` — Cheaper solution than default Jacobian Pseudo Inverse Damped Least Square

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API FULLBODYIK_API`
- L10 _namespace_ `namespace JacobianIK`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FBIKUtil.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace FBIKUtil`
- L13 _prototype_ `FVector GetScaledRotationAxis(const FQuat& InQuat);` (scope `FBIKUtil`) — Utility functions
- L14 _prototype_ `bool CanCrossProduct(const FVector& Vector1, const FVector& Vector2);` (scope `FBIKUtil`)
- L15 _prototype_ `bool GetBoneChain(URigHierarchy* Hierarchy, const FRigElementKey& Root, const FRigElementKey& Current, TArray<FRigElementKey>& ChainIndices);` (scope `FBIKUtil`)

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/FullBodyIK.h` (Public)


#### class `FFullBodyIKModule`  
`class FFullBodyIKModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKSolver, Warning, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKSolver, Warning, All);`

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/JacobianIK.h` (Public)


#### struct `JacobianIK::FFBIKEffectorTarget`  
`struct FFBIKEffectorTarget`  
_L29-88_
- L32 _public member_ `bool bPositionEnabled;` — Position Target
- L33 _public member_ `FVector Position;`
- L36 _public member_ `bool bRotationEnabled;` — Rotation Target
- L37 _public member_ `FQuat Rotation;`
- L43 _public member_ `float LinearMotionStrength;` — This strength is applied to how strong this effector target is If you want the position to be more effective, you can increase this to be more precise and lower if you want less.
- L44 _public member_ `float AngularMotionStrength;`
- L50 _public member_ `float ConvergeScale;` — This is applied when testing converge to see if the effector is reached to target or not This allows to look of pull or reach based on this value
- L53 _public member_ `float ChainLength;` — Total chain length of this effector from root. Used when clamping
- L56 _public member_ `float TargetClampScale;` — ClampScale to target. Helps to stablize the target
- L60 _public member_ `float AdjustedLength;` — This is to support UpdateClamp for each iteration we recalculate the adjusted value and apply
- L63 _public member_ `float InitialPositionDistance;` — Initial distance prior to solver iteration from effetor to target
- L66 _public member_ `float InitialRotationDistance;` — Initial distance prior to solver iteration from effetor to target - currently not used to avoid having another precision value for input that is difficult to estimate
- L69 _public member_ `TArray<int32> LinkChain;` — Save list of chain it affects
- L71 _public function_ `FFBIKEffectorTarget() : Position(EForceInit::ForceInitToZero) , Rotation(EForceInit::ForceInitToZero) , LinearMotionStrength(0.5f) , AngularMotionStrength(0.5f) , ConvergeScale(0.5f) , ChainLength(0.f) , TargetClampScale(1.f) , AdjustedLength(0.f) , InitialPositionDistance(0.f) , InitialRotationDistance(0.f)`
- L84 _public function_ `float GetCurrentLength() const`

#### enum `JacobianIK::ERotationAxis`  
`enum class ERotationAxis : uint8`  
_L90-95_
- L92 _public enumerator_ `Twist`
- L93 _public enumerator_ `Swing1`
- L94 _public enumerator_ `Swing2`

#### enum `JacobianIK::EJacobianSolver`  
`enum class EJacobianSolver : uint8`  
_L97-101_
- L99 _public enumerator_ `JacobianTranspose`
- L100 _public enumerator_ `JacobianPIDLS`

#### struct `JacobianIK::FSolverParameter`  
`struct FSolverParameter`  
_L103-132_
- L106 _public member_ `float DampingValue;` — Damping allows solver to reduce oscillation but it increase iteration time to converge
- L109 _public member_ `EJacobianSolver JacobianSolver;` — Which solver to use
- L112 _public member_ `bool bClampToTarget : 1;` — Enable clamping scale to target
- L114 _public member_ `bool bUpdateClampMagnitude : 1;` — update clamping length for each iteration based on how much it moved from previous iteration
- L116 _public function_ `FSolverParameter() : DampingValue(10.f) , JacobianSolver(EJacobianSolver::JacobianPIDLS) , bClampToTarget(true) , bUpdateClampMagnitude(true)`
- L123 _public function_ `FSolverParameter(float InDampingValue, bool bInClampToTarget, bool bInUpdateClampMagnitude, EJacobianSolver InJacobianSolver = EJacobianSolver::JacobianPIDLS) : DampingValue(InDampingValue) , JacobianSolver(InJacobianSolver) , bClampToTarget(bInClampToTarget) , bUpdateClampMagnitude(bInUpdateClampMagnitude)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define EIGEN_MPL2_ONLY`
- L27 _namespace_ `namespace JacobianIK`
- L136 _delegate_ `DECLARE_DELEGATE_RetVal_SixParams(FVector, FCalculatePartialDerivativesDelegate, const FFBIKLinkData& , bool , int32 , const FFBIKLinkData& , bool , const FSolverParameter& );` — Delegates for core library to use to calculate partial derivatives
- L136 _prototype_ `DECLARE_DELEGATE_RetVal_SixParams(FVector, FCalculatePartialDerivativesDelegate, const FFBIKLinkData& , bool , int32 , const FFBIKLinkData& , bool , const FSolverParameter& );` (scope `JacobianIK`) — Delegates for core library to use to calculate partial derivatives
- L145 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(FVector, FCalculateTargetVectorDelegate, const FFBIKLinkData& , const FFBIKEffectorTarget& , bool , const FSolverParameter& );` — Delegates for core library to use to calculate target vector for end effectors
- L145 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(FVector, FCalculateTargetVectorDelegate, const FFBIKLinkData& , const FFBIKEffectorTarget& , bool , const FSolverParameter& );` (scope `JacobianIK`) — Delegates for core library to use to calculate target vector for end effectors
- L151 _prototype_ `void AllocateMatrix(Eigen::MatrixXf& InOutMatrix, const TArray<FFBIKLinkData>& InLinkData, int32 NumLinkComponent , const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, int32 NumEffectorComponent );` (scope `JacobianIK`)
- L157 _prototype_ `FVector ComputePositionalPartialDerivative( const FFBIKLinkData& InLinkData, const FFBIKLinkData& InEffectorLinkData, const FVector& RotationAxis);` (scope `JacobianIK`)
- L163 _prototype_ `bool CreateJacobianMatrix(const TArray<FFBIKLinkData>& InLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, Eigen::MatrixXf& InOutMatrix, FCalculatePartialDerivativesDelegate OnCalculatePartialDerivatives, const FSolverParameter& SolverParam);` (scope `JacobianIK`) — Core jacobian solver functions
- L170 _prototype_ `bool CreateAnglePartialDerivativesUsingJPIDLS(const TArray<FFBIKLinkData>& InLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, const Eigen::MatrixXf& InJacobianMatrix, Eigen::MatrixXf& InOutAngleDerivativeMatrix, FCalculateTargetVectorDelegate OnCalculateTargetVector, const FSolverParameter& SolverParam);` (scope `JacobianIK`) — Create Angle PArtial Derivatives using Jacobian Psuedo Inverse Damped Least Square
- L178 _prototype_ `bool CreateAnglePartialDerivativesUsingJT(const TArray<FFBIKLinkData>& InLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, const Eigen::MatrixXf& InJacobianMatrix, Eigen::MatrixXf& InOutAngleDerivativeMatrix, FCalculateTargetVectorDelegate OnCalculateTargetVector, const FSolverParameter& SolverParam);` (scope `JacobianIK`) — Create Angle PArtial Derivatives using Jacobian Transpose

### `Plugins/Experimental/FullBodyIK/Source/FullBodyIK/Public/JacobianSolver.h` (Public)


#### struct `FJacobianDebugData`  
`struct FJacobianDebugData`  
_L21-28_
- desc: This is debug structure for editing time
- L23 _public member_ `TArray<FFBIKLinkData> LinkData;`
- L26 _public member_ `TArray<FTransform> TargetVectorSources;` — should match # of effectors
- L27 _public member_ `TArray<FVector> TargetVectors;`

#### class `FJacobianSolverBase`  
`class FJacobianSolverBase`  
_L39-87_
- desc: Jacobian Solver Base Class This does support two solvers 1. Jacobian Transpose 2. Jacobian Pseudo Inverse Damped Least Square (JPIDLS) By default, we use JPIDLS, but it is cheaper to use Jacobian Transpose at the cost of solver
- L42 _public prototype_ `FJacobianSolverBase();`
- L43 _public prototype_ `virtual ~FJacobianSolverBase() = default;`
- L45 _public function_ `void SetPostProcessDelegateForIteration(FPostProcessDelegateForIteration InDelegate)`
- L50 _public function_ `void ClearPostProcessDelegateForIteration()`
- L55 _public prototype_ `bool SolveJacobianIK(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, const FSolverParameter& InSolverParameter, int32 IterationCount = 30, float Tolerance = 1.f, TArray<FJacobianDebugData>* DebugData = nullptr);`
- L59 _private member_ `Eigen::MatrixXf JacobianMatrix;` — for reusing, and not reallocating memory
- L60 _private member_ `Eigen::MatrixXf AnglePartialDerivatives;`
- L63 _private prototype_ `bool RunJacobianIK(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, const FSolverParameter& InSolverParameter, float NormalizedIterationProgress);` — Solver generic APIs  - private APIs to be used internally
- L64 _private prototype_ `void UpdateClampMag(const TArray<FFBIKLinkData>& InLinkData, TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const;`
- L66 _private prototype_ `FVector ComputePartialDerivative(const FFBIKLinkData& InLinkData, bool bPositionChange, int32 LinkComponentIdx, const FFBIKLinkData& InEffectorLinkData, bool PositionTarget, const FSolverParameter& InSolverParameter);`
- L67 _private prototype_ `FVector ComputeTargetVector(const FFBIKLinkData& InEffectorLink, const FFBIKEffectorTarget& InEffectorData, bool bPositionTarget, const FSolverParameter& SolverParam);`
- L69 _private prototype_ `FQuat GetDeltaRotation(const FFBIKLinkData& LinkData, int32& OutPartialDerivativesIndex) const;`
- L70 _private prototype_ `FVector GetDeltaPosition(const FFBIKLinkData& LinkData, int32& OutPartialDerivativesIndex) const;`
- L72 _private prototype_ `FVector ClampMag(const FVector& ToTargetVector, float Length) const;`
- L73 _private prototype_ `void UpdateLinkData(TArray<FFBIKLinkData>& InOutLinkData, const Eigen::MatrixXf& InAnglePartialDerivatives) const;`
- L74 _private prototype_ `bool DidConverge(const TArray<FFBIKLinkData>& InLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors, float Tolerance, int32 Count) const;`
- L79 _protected function_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const` — Initialize Solver - allows users to modify data before running the base solver - Check Below
- L81 _protected function_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const` — Pre Solve - for each iteration, they run PreSolve. For each iteration, they may require to update info based on previous solved pose
- L84 _protected member_ `FCalculatePartialDerivativesDelegate OnCalculatePartialDerivativesDelegate;`
- L85 _protected member_ `FCalculateTargetVectorDelegate OnCalculateTargetVectorDelegate;`
- L86 _protected member_ `FPostProcessDelegateForIteration OnPostProcessDelegateForIteration;`

#### class `FJacobianSolver_PositionTarget_3DOF`  
`class FJacobianSolver_PositionTarget_3DOF : public FJacobianSolverBase`  
_L101-108_
- inherits: `FJacobianSolverBase`
- desc: This support positional target using 3 different axis (default coordinate in world space - xyz axis)
- L104 _public prototype_ `FJacobianSolver_PositionTarget_3DOF();`
- L107 _protected prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`

#### class `FJacobianSolver_PositionTarget_Quat`  
`class FJacobianSolver_PositionTarget_Quat : public FJacobianSolverBase`  
_L115-123_
- inherits: `FJacobianSolverBase`
- desc: This support positional target using quaternion instead of 3 world axis This creates rotation axis using effector target of known (https://cseweb.ucsd.edu/classes/sp16/cse169-a/slides/CSE169_09.pdf)
- L118 _public prototype_ `FJacobianSolver_PositionTarget_Quat();`
- L121 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`
- L122 _private prototype_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const override;`

#### class `FJacobianSolver_RotationTarget_Quat`  
`class FJacobianSolver_RotationTarget_Quat : public FJacobianSolverBase`  
_L129-137_
- inherits: `FJacobianSolverBase`
- desc: This support rotation target using quaternion instead of 3 world axis This creates rotation axis using effector target of known (https://cseweb.ucsd.edu/classes/sp16/cse169-a/slides/CSE169_09.pdf)
- L132 _public prototype_ `FJacobianSolver_RotationTarget_Quat();`
- L135 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`
- L136 _private prototype_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const override;`

#### class `FJacobianSolver_RotationTarget_3DOF`  
`class FJacobianSolver_RotationTarget_3DOF : public FJacobianSolver_PositionTarget_3DOF`  
_L142-149_
- inherits: `FJacobianSolver_PositionTarget_3DOF`
- desc: This support rotational target using 3 different axis (default coordinate in world space - xyz axis)
- L145 _public prototype_ `FJacobianSolver_RotationTarget_3DOF();`
- L148 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`

#### class `FJacobianSolver_PositionRotationTarget_3DOF`  
`class FJacobianSolver_PositionRotationTarget_3DOF : public FJacobianSolver_PositionTarget_3DOF`  
_L154-161_
- inherits: `FJacobianSolver_PositionTarget_3DOF`
- desc: This support positional and rotational target using 3 different axis (default coordinate in world space - xyz axis)
- L157 _public prototype_ `FJacobianSolver_PositionRotationTarget_3DOF();`
- L160 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`

#### class `FJacobianSolver_PositionRotationTarget_Quat`  
`class FJacobianSolver_PositionRotationTarget_Quat : public FJacobianSolver_PositionTarget_Quat`  
_L167-175_
- inherits: `FJacobianSolver_PositionTarget_Quat`
- desc: This support position/rotation target using quaternion instead of 3 world axis This creates rotation axis using effector target of known (https://cseweb.ucsd.edu/classes/sp16/cse169-a/slides/CSE169_09.pdf)
- L170 _public prototype_ `FJacobianSolver_PositionRotationTarget_Quat();`
- L173 _private prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`
- L174 _private prototype_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const override;`

#### class `FJacobianSolver_PositionTarget_3DOF_Translation`  
`class FJacobianSolver_PositionTarget_3DOF_Translation : public FJacobianSolver_PositionTarget_3DOF`  
_L180-187_
- inherits: `FJacobianSolver_PositionTarget_3DOF`
- desc: This support positional target using 3 different axis by translating joint (default coordinate in world space - xyz axis)
- L183 _public prototype_ `FJacobianSolver_PositionTarget_3DOF_Translation();`
- L186 _protected prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`

#### class `FJacobianSolver_PositionRotationTarget_LocalFrame`  
`class FJacobianSolver_PositionRotationTarget_LocalFrame : public FJacobianSolverBase`  
_L192-200_
- inherits: `FJacobianSolverBase`
- desc: This support positional/rotational target using custom frame provided by user. If you want to create custom frame for stiffness.
- L195 _public prototype_ `FJacobianSolver_PositionRotationTarget_LocalFrame();`
- L198 _protected prototype_ `virtual void InitializeSolver(TArray<FFBIKLinkData>& InOutLinkData, TMap<int32, FFBIKEffectorTarget>& InOutEndEffectors) const override;`
- L199 _protected prototype_ `virtual void PreSolve(TArray<FFBIKLinkData>& InOutLinkData, const TMap<int32, FFBIKEffectorTarget>& InEndEffectors) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API FULLBODYIK_API`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FPostProcessDelegateForIteration, TArray<FFBIKLinkData>& );` — Post processor for each iteration after resolving the pose This will be used for Applying Constraints, but if you have more you want to do, you can customize this
- L16 _prototype_ `DECLARE_DELEGATE_OneParam(FPostProcessDelegateForIteration, TArray<FFBIKLinkData>& );` — Post processor for each iteration after resolving the pose This will be used for Applying Constraints, but if you have more you want to do, you can customize this
