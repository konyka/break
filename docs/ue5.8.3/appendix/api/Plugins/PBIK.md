# Plugins / PBIK

- module root: `Plugins/Experimental/FullBodyIK/Source/PBIK`
- headers: 7; symbols: 290
- symbol kinds: class=1, delegate=1, enum=3, enumerator=9, function=16, macro=1, member=159, namespace=8, prototype=72, struct=18, variable=2
- PrivateDependencyModuleNames: AssetTools, CoreUObject, Engine, RigVMDeveloper, RigVMEditor, UnrealEd
- PublicDependencyModuleNames: ControlRig, ControlRigDeveloper, ControlRigEditor, Core, RigVM

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/Core/PBIKBody.h` (Public)


#### struct `PBIK::FBone`  
`struct FBone`  
_L16-48_
- L18 _public member_ `FName Name;`
- L19 _public member_ `int32 ParentIndex = -2;` — -2 is unset, -1 for root, or 0...n otherwise
- L20 _public member_ `FVector Position;`
- L21 _public member_ `FQuat Rotation;`
- L22 _public member_ `FVector Scale;` — just passed through, not modified
- L23 _public member_ `FVector LocalPositionFromInput;`
- L24 _public member_ `FQuat LocalRotationFromInput;`
- L25 _public member_ `FRotator LocalRotationInitial;`
- L28 _public member_ `FRigidBody* Body = nullptr;` — initialized - these fields are null/empty until after Solver::Initialize()
- L29 _public member_ `FBone* Parent = nullptr;`
- L30 _public member_ `TArray<FBone*> Children;`
- L31 _public member_ `int32 EffectorIndex = INDEX_NONE;`
- L32 _public member_ `bool bIsSolverRoot = false;`
- L33 _public member_ `bool bIsSolved = false;`
- L34 _public member_ `bool bIsSubRoot = false;`
- L35 _public member_ `bool bIsPartOfSolvedBranch = false;`
- L36 _public member_ `float Length = 0.f;`
- L39 _public prototype_ `FBone( const FName InName, const int32& InParentIndex,`
- L46 _public prototype_ `bool HasChild(const FBone* Bone);`
- L47 _public prototype_ `void UpdateFromInputs();`

#### enum `PBIK::ELimitType`  
`enum class ELimitType : uint8`  
_L50-55_
- L52 _public enumerator_ `Free`
- L53 _public enumerator_ `Limited`
- L54 _public enumerator_ `Locked`

#### struct `PBIK::FBoneSettings`  
`struct FBoneSettings`  
_L57-76_
- L59 _public member_ `float RotationStiffness = 0.0f;` — range (0, 1)
- L60 _public member_ `float PositionStiffness = 0.0f;` — range (0, 1)
- L62 _public member_ `ELimitType X;`
- L63 _public member_ `float MinX = 0.0f;` — range (-180, 180)
- L64 _public member_ `float MaxX = 0.0f;`
- L66 _public member_ `ELimitType Y;`
- L67 _public member_ `float MinY = 0.0f;`
- L68 _public member_ `float MaxY = 0.0f;`
- L70 _public member_ `ELimitType Z;`
- L71 _public member_ `float MinZ = 0.0f;`
- L72 _public member_ `float MaxZ = 0.0f;`
- L74 _public member_ `bool bUsePreferredAngles = false;`
- L75 _public member_ `FRotator PreferredAngles = FRotator::ZeroRotator;`

#### struct `PBIK::FRigidBody`  
`struct FRigidBody`  
_L78-127_
- L80 _public member_ `FBone* Bone = nullptr;`
- L81 _public member_ `FBoneSettings J;`
- L82 _public member_ `FPinConstraint* Pin = nullptr;`
- L83 _public member_ `FEffector* Effector = nullptr;`
- L84 _public member_ `const FPBIKSolverSettings* SolverSettings;`
- L86 _public member_ `FVector Position;`
- L87 _public member_ `FQuat Rotation;`
- L88 _public member_ `FVector InputPosition;`
- L89 _public member_ `FQuat InitialRotation;`
- L90 _public member_ `FVector BoneLocalPosition;`
- L92 _public member_ `float InvMass = 0.f;`
- L93 _public member_ `float Mass = 0.f;`
- L95 _public member_ `float MaxAngle = 0.0f;`
- L97 _public member_ `bool bIsLockedBySubSolve = false;`
- L98 _public member_ `bool bIsPartOfSubChain = false;`
- L102 _private member_ `int32 NumBonesToRoot = 0;`
- L106 _public prototype_ `FRigidBody(FBone* InBone);`
- L108 _public prototype_ `void Initialize(const FBone* SolverRoot);`
- L110 _public prototype_ `void UpdateFromInputs(const FPBIKSolverSettings& Settings);`
- L112 _public prototype_ `void UpdateTransformAndMassFromBones();`
- L114 _public prototype_ `int GetNumBonesToRoot() const;`
- L116 _public prototype_ `FRigidBody* GetParentBody() const;`
- L118 _public prototype_ `bool IsPositionLocked() const;`
- L120 _public prototype_ `bool IsRotationLocked() const;`
- L122 _public prototype_ `void ApplyPushToRotateBody(const FVector& Push, const FVector& Offset);`
- L124 _public prototype_ `void ApplyPositionDelta(const FVector& InDeltaP);`
- L126 _public prototype_ `void ApplyRotationDelta(const FQuat& InDelta);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PBIK`
- L130 _function_ `inline bool operator<(const FRigidBody& Lhs, const FRigidBody& Rhs)` (scope `PBIK`) — for sorting Bodies hierarchically (root to leaf order)

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/Core/PBIKConstraint.h` (Public)


#### struct `PBIK::FConstraint`  
`struct FConstraint`  
_L14-22_
- L16 _public member_ `bool bEnabled = true;`
- L18 _public prototype_ `virtual void Solve(const FPBIKSolverSettings& Settings) = 0;`
- L19 _public function_ `virtual void RemoveStretch(const float Percent)`
- L20 _public function_ `virtual void FinalPass()`
- L21 _public function_ `virtual void UpdateFromInputs()`

#### struct `PBIK::FJointConstraint`  
`struct FJointConstraint : public FConstraint`  
_L24-96_
- inherits: `FConstraint`
- L29 _private member_ `FRigidBody* A;`
- L30 _private member_ `FRigidBody* B;`
- L32 _private member_ `FVector PinPointLocalToA;`
- L33 _private member_ `FVector PinPointLocalToB;`
- L35 _private member_ `FVector XOrig;`
- L36 _private member_ `FVector YOrig;`
- L37 _private member_ `FVector ZOrig;`
- L39 _private member_ `FVector XA;`
- L40 _private member_ `FVector YA;`
- L41 _private member_ `FVector ZA;`
- L42 _private member_ `FVector XB;`
- L43 _private member_ `FVector YB;`
- L44 _private member_ `FVector ZB;`
- L46 _private member_ `FVector ZBProjOnX;`
- L47 _private member_ `FVector ZBProjOnY;`
- L48 _private member_ `FVector YBProjOnZ;`
- L50 _private member_ `float AngleX;`
- L51 _private member_ `float AngleY;`
- L52 _private member_ `float AngleZ;`
- L54 _private member_ `bool bInFinalPass = false;`
- L58 _public prototype_ `FJointConstraint(FRigidBody* InA, FRigidBody* InB);`
- L60 _public prototype_ `virtual ~FJointConstraint() = default;`
- L62 _public prototype_ `virtual void Solve(const FPBIKSolverSettings& Settings) override;`
- L64 _public prototype_ `virtual void RemoveStretch(const float Percent) override;`
- L66 _public prototype_ `virtual void FinalPass() override;`
- L68 _public prototype_ `virtual void UpdateFromInputs() override;`
- L72 _private prototype_ `FVector GetPositionCorrection(FVector& OutBodyToA, FVector& OutBodyToB) const;`
- L74 _private prototype_ `void ApplyRotationCorrection(FQuat DeltaQ) const;`
- L76 _private prototype_ `void UpdateJointLimits();`
- L78 _private prototype_ `void RotateWithinLimits( float MinAngle, float MaxAngle, float CurrentAngle, FVector RotAxis, FVector CurVec, FVector RefVec) const;`
- L86 _private prototype_ `void RotateToAlignAxes(const FVector& AxisA, const FVector& AxisB) const;`
- L88 _private prototype_ `void UpdateLocalRotateAxes(bool bX, bool bY, bool bZ);`
- L90 _private prototype_ `void DecomposeRotationAngles();`
- L92 _private prototype_ `float SignedAngleBetweenNormals( const FVector& From, const FVector& To, const FVector& Axis) const;`

#### struct `PBIK::FPinConstraint`  
`struct FPinConstraint : public FConstraint`  
_L98-130_
- inherits: `FConstraint`
- L102 _private member_ `FVector GoalPosition;`
- L103 _private member_ `FQuat GoalRotation;`
- L104 _private member_ `float Alpha = 1.0;`
- L106 _private member_ `FRigidBody* Body;`
- L107 _private member_ `FBone* PinBone;`
- L108 _private member_ `FVector PinPointLocalToA;`
- L112 _public prototype_ `FPinConstraint(FRigidBody* InBody, FBone* InPinBone);`
- L114 _public prototype_ `virtual ~FPinConstraint() = default;`
- L116 _public prototype_ `virtual void Solve(const FPBIKSolverSettings& Settings) override;`
- L118 _public prototype_ `virtual void UpdateFromInputs() override;`
- L120 _public prototype_ `void SetGoal(const FVector& InGoalPosition, const FQuat& InGoalRotation, const float InAlpha);`
- L122 _public prototype_ `FVector GetCurrentPinPoint() const;`
- L126 _private prototype_ `FVector GetPositionCorrection(FVector& OutBodyToPinPoint) const;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PBIK`

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/Core/PBIKDebug.h` (Public)


#### struct `PBIK::FDebugLine`  
`struct FDebugLine`  
_L11-21_
- L13 _public member_ `FVector A;`
- L14 _public member_ `FVector B;`
- L16 _public function_ `FDebugLine(const FVector& InA, const FVector& InB)`

#### struct `PBIK::FDebugDraw`  
`struct FDebugDraw`  
_L23-28_
- L25 _public member_ `FPBIKSolver* Solver;`
- L27 _public prototype_ `void GetDebugLinesForBodies(TArray<FDebugLine>& OutLines);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PBIK`

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/Core/PBIKSolver.h` (Public)


#### struct `PBIK::FEffectorSettings`  
`struct FEffectorSettings`  
_L31-61_
- L34 _public member_ `float PositionAlpha = 1.0f;` — Range 0-1, default is 1. Blend between the input bone position (0.0) and the current effector position (1.0).
- L37 _public member_ `float RotationAlpha = 1.0f;` — Range 0-1, default is 1. Blend between the input bone rotation (0.0) and the current effector rotation (1.0).
- L43 _public member_ `float StrengthAlpha = 1.0f;` — Range 0-1 (default is 1.0). The strength of the effector when pulling the bone towards it's target location. At 0.0, the effector does not pull at all, but the bones between the effector and the root will still slightly resist motion from other effectors. This can thus act as a "stabilizer" of sorts for parts of the body that you do not want to behave in a pure FK fashion.
- L49 _public member_ `int32 ChainDepth = 0;` — Range 0-inf (default is 0). Explicitly set the number of bones up the hierarchy to consider part of this effector's 'chain'. The "chain" of bones is used to apply Preferred Angles, Pull Chain Alpha and Chain "Sub Solves". If left at 0, the solver will attempt to determine the root of the chain by searching up the hierarchy until it finds a branch or another effector, whichever it finds first.
- L56 _public member_ `float PullChainAlpha = 1.0f;` — Range 0-1 (default is 1.0). When enabled (greater than 0.0), the solver internally partitions the skeleton into 'chains' which extend from the effector to the nearest fork in the skeleton. These chains are pre-rotated and translated, as a whole, towards the effector targets. This can improve the results for sparse bone chains, and significantly improve convergence on dense bone chains. But it may cause undesirable results in highly constrained bone chains (like robot arms).
- L60 _public member_ `float PinRotation = 1.0f;` — Range 0-1 (default is 1.0). Blends the effector bone rotation between the rotation of the effector transform (1.0) and the rotation of the input bone (0.0).

#### struct `PBIK::FEffector`  
`struct FEffector`  
_L63-97_
- L65 _public member_ `FVector PositionFinal;`
- L66 _public member_ `FQuat RotationFinal;`
- L68 _public member_ `FVector PositionOrig;`
- L69 _public member_ `FQuat RotationOrig;`
- L71 _public member_ `FVector PositionGoal;`
- L72 _public member_ `FQuat RotationGoal;`
- L74 _public member_ `FEffectorSettings Settings;`
- L76 _public member_ `FBone* Bone;`
- L77 _public member_ `FPinConstraint* Pin;`
- L78 _public member_ `FRigidBody* ChainRootBody = nullptr;`
- L79 _public member_ `int32 ChainDepthInitializedWith = -1;`
- L80 _public member_ `float DistToChainRootInInputPose;`
- L82 _public member_ `TArray<float> DistancesFromEffector;`
- L83 _public member_ `float DistToChainRootAlongBones;`
- L85 _public prototype_ `FEffector(FBone* InBone);`
- L87 _public prototype_ `void SetGoal( const FVector& InPositionGoal, const FQuat& InRotationGoal, const FEffectorSettings& InSettings);`
- L92 _public prototype_ `void UpdateChainStates();`
- L93 _public prototype_ `void UpdateFromInputs(const FBone& InSolverRoot, const bool bAllowStretch);`
- L94 _public prototype_ `float CalculateDistanceToChainRoot() const;`
- L95 _public prototype_ `float CalculateDistanceToSolveRootAlongBones() const;`
- L96 _public prototype_ `void ApplyPreferredAngles() const;`

#### enum `EPBIKRootBehavior`  
`enum class EPBIKRootBehavior : uint8`  
_L102-107_
- reflection: `UENUM(BlueprintType)`
- L104 _public enumerator_ `PrePull`
- L105 _public enumerator_ `PinToInput`
- L106 _public enumerator_ `Free`

#### struct `FRootPrePullSettings`  
`struct FRootPrePullSettings`  
_L110-145_
- reflection: `USTRUCT(BlueprintType)`
- L116 _public member_ `float RotationAlpha = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootRotation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 0. Apply a large scale rotation offset to the entire body prior to constraint solving.
- L120 _public member_ `float RotationAlphaX = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootRotation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to rotation offset in the X axis in component space.
- L124 _public member_ `float RotationAlphaY = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootRotation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to rotation offset in the Y axis in component space.
- L128 _public member_ `float RotationAlphaZ = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootRotation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to rotation offset in the Z axis in component space.
- L132 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootPosition, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Apply a large scale position offset to the entire body prior to constraint solving.
- L136 _public member_ `float PositionAlphaX = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootPosition, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to position offset in the X axis in component space.
- L140 _public member_ `float PositionAlphaY = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootPosition, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to position offset in the Y axis in component space.
- L144 _public member_ `float PositionAlphaZ = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootPosition, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend contribution to position offset in the Z axis in component space.

#### struct `FPBIKSolverSettings`  
`struct FPBIKSolverSettings`  
_L148-196_
- reflection: `USTRUCT(BlueprintType)`
- L154 _public member_ `int32 Iterations = 20;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0.0", UIMax = "200.0"))` — High iteration counts can help solve complex joint configurations with competing constraints, but will increase runtime cost. Default is 20.
- L158 _public member_ `int32 SubIterations = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0.0", UIMax = "200.0"))` — Iterations used for sub-chains defined by the Chain Depth of the effectors. These are solved BEFORE the main iteration pass. Default is 0.
- L162 _public member_ `float MassMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", UIMin = "0.0", UIMax = "10.0"))` — A global mass multiplier; higher values will make the joints more stiff, but require more iterations. Typical range is 0.0 to 10.0.
- L166 _public member_ `bool bAllowStretch = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings)` — If true, joints will translate to reach the effectors; causing bones to lengthen if necessary. Good for cartoon effects. Default is false.
- L173 _public member_ `EPBIKRootBehavior RootBehavior = EPBIKRootBehavior::PrePull;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootBehavior)` — (Default is PrePull) Set the behavior of the solver root. Pre Pull: translates and rotates the root (and all children) by the average motion of the stretched effectors to help achieve faster convergence when reaching far. Pin to Input: locks the translation and rotation of the root bone to the input pose. Overrides any bone settings applied to the root. Good for partial-body solves. Free: treats the root bone like any other and allows it to move freely or according to any bone settings applied to it.
- L177 _public member_ `FRootPrePullSettings PrePullRootSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootBehavior)` — Settings only applicable when Root Behavior is set to "PrePull". Use these values to adjust the gross movement and orientation of the entire skeleton.
- L181 _public member_ `float GlobalPullChainAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — A global multiplier for all Pull Chain Alpha values on all effectors. Range is 0.0 to 1.0. Default is 1.0.
- L185 _public member_ `float MaxAngle = 30.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "0", ClampMax = "45", UIMin = "0.0", UIMax = "180.0"))` — Maximum angle that a joint can be rotated per constraint iteration. Lower this value if the solve is diverging. Range is 0.0 to 180.0. Default is 30.
- L189 _public member_ `float OverRelaxation = 1.3f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "1", UIMin = "1.0", UIMax = "2.0"))` — Pushes constraints beyond their normal amount to speed up convergence. Increasing this may speed up convergence, but at the cost of stability. Range is 1.0 - 2.0. Default is 1.3.
- L195 _public member_ `bool bStartSolveFromInputPose_DEPRECATED = true;` — `UPROPERTY()` — DEPRECATED: When true, the solver is reset each tick to start from the current input pose. Default is true. If false, incoming animated poses are ignored and the solver starts from the results of the previous solve. In very limited circumstances, it can be beneficial to use the pose from the previous frame.

#### struct `FPBIKSolver`  
`struct FPBIKSolver`  
_L199-303_
- reflection: `USTRUCT()`
- L205 _public function_ `FPBIKSolver& operator=(const FPBIKSolver&)`
- L211 _public prototype_ `PBIK::FDebugDraw* GetDebugDraw();`
- L217 _public prototype_ `bool Initialize();`
- L219 _public prototype_ `void Solve(const FPBIKSolverSettings& InSolverSettings);`
- L221 _public prototype_ `void Reset();`
- L223 _public prototype_ `bool IsReadyToSimulate() const;`
- L229 _public prototype_ `void SetBoneTransform(const int32 Index, const FTransform& InTransform);`
- L231 _public prototype_ `PBIK::FBoneSettings* GetBoneSettings(const int32 Index);`
- L233 _public prototype_ `void SetEffectorGoal( const int32 Index, const FVector& InGoalPosition, const FQuat& InGoalRotation, const PBIK::FEffectorSettings& Settings);`
- L239 _public prototype_ `void GetBoneGlobalTransform(const int32 Index, FTransform& OutTransform);`
- L241 _public function_ `int32 GetNumBones() const`
- L243 _public prototype_ `int32 GetBoneIndex(FName BoneName) const;`
- L249 _public prototype_ `int32 AddBone( const FName Name, const int32 ParentIndex, const FVector& InOrigPosition, const FQuat& InOrigRotation, bool bIsSolverRoot);`
- L256 _public prototype_ `int32 AddEffector(const FName BoneName);`
- L260 _private prototype_ `bool InitBones();`
- L262 _private prototype_ `bool InitBodies();`
- L264 _private prototype_ `bool InitConstraints();`
- L266 _private prototype_ `void UpdateEffectorDepths(bool bForceUpdate);`
- L268 _private prototype_ `void AddBodyForBone(PBIK::FBone* Bone);`
- L270 _private prototype_ `void UpdateBodies(const FPBIKSolverSettings& Settings);`
- L272 _private prototype_ `void UpdateBonesFromBodies();`
- L274 _private prototype_ `void SolveConstraints(const FPBIKSolverSettings& InSolverSettings);`
- L276 _private prototype_ `void ApplyRootPrePull(const EPBIKRootBehavior RootBehavior, const FRootPrePullSettings& PrePullSettings);`
- L278 _private prototype_ `void ApplyPullChainAlpha(const float GlobalPullChainAlpha);`
- L280 _private prototype_ `void ApplyPreferredAngles();`
- L287 _private prototype_ `static FQuat GetRotationFromDeformedPoints( const TArrayView<FVector>& InInitialPoints, const TArrayView<FVector>& InCurrentPoints, FVector& OutInitialCentroid, FVector& OutCurrentCentroid);` — given a set of points in an initial configuration and the same set of points in a deformed configuration, this function outputs a quaternion that represents the "best fit" rotation that rotates the initial points to the current points.
- L293 _private member_ `PBIK::FBone* SolverRoot = nullptr;`
- L294 _private member_ `TArray<PBIK::FBone> Bones;`
- L295 _private member_ `TArray<PBIK::FRigidBody> Bodies;`
- L296 _private member_ `TArray<TSharedPtr<PBIK::FConstraint>> Constraints;`
- L297 _private member_ `TArray<PBIK::FEffector> Effectors;`
- L298 _private member_ `bool bHasSubChains = false;`
- L299 _private member_ `bool bReadyToSimulate = false;`
- L301 _private member_ `PBIK::FDebugDraw DebugDraw;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PBIK`
- L10 _namespace_ `namespace PBIK`
- L11 _namespace_ `namespace PBIK`
- L12 _namespace_ `namespace PBIK`
- L16 _namespace_ `namespace PBIK`
- L19 _variable_ `static float GLOBAL_UNITS = 100.0f;` (scope `PBIK`) — (1.0f = meters), (100.0f = centimeters)
- L20 _variable_ `static float MIN_MASS = 0.5f;` (scope `PBIK`)
- L23 _function_ `inline static float QuarticEaseOut(const float& Input)` (scope `PBIK`) — A long tail ease out function. Input range, 0-1.
- L25 _function_ `inline static float CircularEaseOut(const float& Input)` (scope `PBIK`) — A C2 continuous ease out function. Input range, 0-1
- L27 _function_ `inline static float SquaredEaseOut(const float& Input)` (scope `PBIK`) — An ease out function. Input range, 0-1.

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/PBIK.h` (Public)


#### class `FPBIKModule`  
`class FPBIKModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPBIKSolver, Warning, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPBIKSolver, Warning, All);`

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/PBIK_Shared.h` (Public)


#### enum `EPBIKLimitType`  
`enum class EPBIKLimitType : uint8`  
_L11-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Free`
- L14 _public enumerator_ `Limited`
- L15 _public enumerator_ `Locked`

#### struct `FPBIKBoneSetting`  
`struct FPBIKBoneSetting`  
_L19-110_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public function_ `FPBIKBoneSetting() : Bone(NAME_None), X(EPBIKLimitType::Free), Y(EPBIKLimitType::Free), Z(EPBIKLimitType::Free), PreferredAngles(FVector::ZeroVector)`
- L32 _public member_ `FName Bone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Bone, meta = (CustomWidget = "BoneName"))` — The Bone that these settings will be applied to.
- L36 _public member_ `float RotationStiffness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Stiffness, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range is 0 to 1 (Default is 0). At higher values, the bone will resist rotating (forcing other bones to compensate).
- L40 _public member_ `float PositionStiffness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Stiffness, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range is 0 to 1 (Default is 0). At higher values, the bone will resist translational motion (forcing other bones to compensate).
- L47 _public member_ `EPBIKLimitType X;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the X axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at reference pose angle).
- L50 _public member_ `float MinX = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative X direction to allow when joint is in "Limited" mode.
- L53 _public member_ `float MaxX = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive X direction to allow when joint is in "Limited" mode.
- L60 _public member_ `EPBIKLimitType Y;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the Y axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at input pose angle).
- L63 _public member_ `float MinY = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative Y direction to allow when joint is in "Limited" mode.
- L66 _public member_ `float MaxY = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive Y direction to allow when joint is in "Limited" mode.
- L73 _public member_ `EPBIKLimitType Z;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the Z axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at input pose angle).
- L76 _public member_ `float MinZ = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative Z direction to allow when joint is in "Limited" mode.
- L79 _public member_ `float MaxZ = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive Z direction to allow when joint is in "Limited" mode.
- L85 _public member_ `bool bUsePreferredAngles = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PreferredAngles)` — When true, this bone will "prefer" to rotate in the direction specified by the Preferred Angles when the chain it belongs to is compressed. Preferred Angles should be the first method used to fix bones that bend in the wrong direction (rather than limits). The resulting angles can be visualized on their own by temporarily setting the Solver iterations to 0 and moving the effectors.
- L90 _public member_ `FVector PreferredAngles;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PreferredAngles)` — The local Euler angles (in degrees) used to rotate this bone when the chain it belongs to is squashed. This happens by moving the effector at the tip of the chain towards the root of the chain. This can be used to coerce knees and elbows to bend in the anatomically "correct" direction without resorting to limits (which may require more iterations to converge).
- L92 _public function_ `void CopyToCoreStruct(PBIK::FBoneSettings& Settings) const`

### `Plugins/Experimental/FullBodyIK/Source/PBIK/Public/RigUnit_PBIK.h` (Public)


#### struct `FPBIKDebug`  
`struct FPBIKDebug`  
_L23-45_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `float DrawScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Debug)` — The scale of the debug drawing.
- L33 _public member_ `bool bDrawDebug = false;` — `UPROPERTY(EditAnywhere, Category = Debug)` — If true, turns on debug drawing for the node.
- L35 _public function_ `void Draw(FRigVMDrawInterface* DrawInterface, FPBIKSolver* Solver) const`

#### struct `FPBIKEffector`  
`struct FPBIKEffector`  
_L48-103_
- reflection: `USTRUCT(BlueprintType)`
- L52 _public function_ `FPBIKEffector() : Bone(NAME_None), PositionAlpha(1.0f), RotationAlpha(1.0f), StrengthAlpha(1.0f), ChainDepth(0), PullChainAlpha(1.0f), PinRotation(1.0f)`
- L63 _public member_ `FName Bone;` — `UPROPERTY(EditAnywhere, Category="Effector", meta = (CustomWidget = "BoneName"))` — The bone that this effector will pull on.
- L67 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category="Effector")` — The target location and rotation for this effector. The solver will try to get the specified bone to reach this location.
- L71 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Goal Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend between the input bone position (0.0) and the current effector position (1.0).
- L75 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Goal Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend between the input bone rotation (0.0) and the current effector rotation (1.0).
- L82 _public member_ `float StrengthAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). The strength of the effector when pulling the bone towards it's target location. At 0.0, the effector does not pull at all, but the bones between the effector and the root will still slightly resist motion from other effectors. This can thus act as a "stabilizer" of sorts for parts of the body that you do not want to behave in a pure FK fashion.
- L89 _public member_ `int32 ChainDepth = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Full Body IK Effector", meta = (ClampMin = "0", UIMin = "0"))` — Range 0-inf (default is 0). Explicitly set the number of bones up the hierarchy to consider part of this effector's 'chain'. The "chain" of bones is used to apply Preferred Angles, Pull Chain Alpha and "Sub Solve" iterations. If left at 0, the solver will attempt to determine the root of the chain by searching up the hierarchy until it finds a branch or another effector, whichever it finds first.
- L97 _public member_ `float PullChainAlpha = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). When enabled (greater than 0.0), the solver internally partitions the skeleton into 'chains' which extend from the effector to the nearest fork in the skeleton. These chains are pre-rotated and translated, as a whole, towards the effector targets. This can improve the results for sparse bone chains, and significantly improve convergence on dense bone chains. But it may cause undesirable results in highly constrained bone chains (like robot arms).
- L102 _public member_ `float PinRotation = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). Blends the effector bone rotation between the rotation of the effector transform (1.0) and the rotation of the input bone (0.0).

#### struct `FPBIKWorkData`  
`struct FPBIKWorkData`  
_L106-130_
- reflection: `USTRUCT()`
- L110 _public function_ `FPBIKWorkData() : bNeedsInit(true), HashInitializedWith(-1)`
- L117 _public member_ `bool bNeedsInit;` — `UPROPERTY(transient)`
- L120 _public member_ `uint32 HashInitializedWith;` — `UPROPERTY(transient)`
- L123 _public member_ `TArray<int32> BoneSettingToSolverBoneIndex;` — `UPROPERTY(transient)`
- L126 _public member_ `TArray<int32> SolverBoneToElementIndex;` — `UPROPERTY(transient)`
- L129 _public member_ `FPBIKSolver Solver;` — `UPROPERTY(transient)`

#### struct `FRigUnit_PBIK`  
`struct FRigUnit_PBIK : public FRigUnit_HighlevelBaseMutable`  
_L136-178_
- reflection: `USTRUCT(meta=(DisplayName="Full Body IK", NodeColor="0 1 1"))`
- inherits: `FRigUnit_HighlevelBaseMutable`
- desc: Based on a Position Based solver at core, this node can solve multi chains within a root using multi effectors
- L140 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L143 _public function_ `FRigUnit_PBIK() : Root(NAME_None)`
- L149 _public member_ `FName Root;` — `UPROPERTY(meta = (Input, CustomWidget = "BoneName"))` — This is usually the top-most skinned bone; often the "Pelvis" or "Hips", but can be set to any bone. Bones above the root will be ignored by the solver. Bones that are located *between* the Root and the effectors will be included in the solve.
- L153 _public member_ `TArray<FPBIKEffector> Effectors;` — `UPROPERTY(meta = (Input))` — An array of effectors. These specify target transforms for different parts of the skeleton.
- L156 _public member_ `TArray<int32> EffectorSolverIndices;` — `UPROPERTY(transient)`
- L160 _public member_ `TArray<FPBIKBoneSetting> BoneSettings;` — `UPROPERTY(meta = (Input))` — Per-bone settings to control the resulting pose. Includes limits and preferred angles.
- L165 _public member_ `TArray<FName> ExcludedBones;` — `UPROPERTY(meta = (Input, CustomWidget = "BoneName"))` — These bones will be excluded from the solver. They will not bend and will not contribute to the constraint set. Use the ExcludedBones array instead of setting Rotation Stiffness to very high values or Rotation Limits with zero range.
- L169 _public member_ `FPBIKSolverSettings Settings;` — `UPROPERTY(meta = (Input))` — Global solver settings.
- L173 _public member_ `FPBIKDebug Debug;` — `UPROPERTY(meta = (Input))` — Debug drawing options.
- L177 _public member_ `FPBIKWorkData WorkData;` — `UPROPERTY(transient)` — Runtime-only data

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PBIK_API`
