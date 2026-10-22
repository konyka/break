# Plugins / IKRig

- module root: `Plugins/Animation/IKRig/Source/IKRig`
- headers: 55; symbols: 2941
- symbol kinds: class=59, delegate=3, enum=41, enumerator=144, function=352, macro=63, member=1091, namespace=4, prototype=1000, struct=177, typedef=3, variable=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AnimationCore, ApplicationCore, CoreUObject, Engine, MessageLog
- PublicDependencyModuleNames: ControlRig, Core, PBIK, RigVM
- PublicIncludePathModuleNames: AnimationWidgets

### `Plugins/Animation/IKRig/Source/IKRig/Public/ActorComponents/IKRigComponent.h` (Public)


#### class `UIKRigComponent`  
`class UIKRigComponent : public UActorComponent, public IIKGoalCreatorInterface`  
_L14-90_
- reflection: `UCLASS(MinimalAPI, ClassGroup = IKRig, BlueprintType, Blueprintable, EditInlineNew, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IIKGoalCreatorInterface`
- L22 _public function_ `void SetIKRigGoalPositionAndRotation( const FName GoalName, const FVector Position, const FQuat Rotation, const float PositionAlpha, const float RotationAlpha)` — `UFUNCTION(BlueprintCallable, Category=IKRigGoals)` — Set an IK Rig Goal position and rotation (assumed in Component Space of Skeletal Mesh) with separate alpha values.
- L44 _public function_ `void SetIKRigGoalTransform( const FName GoalName, const FTransform Transform, const float PositionAlpha, const float RotationAlpha)` — `UFUNCTION(BlueprintCallable, Category=IKRigGoals)` — Set an IK Rig Goal transform (assumed in Component Space of Skeletal Mesh) with separate alpha values.
- L67 _public function_ `void SetIKRigGoal(const FIKRigGoal& Goal)` — `UFUNCTION(BlueprintCallable, Category=IKRigGoals)` — Apply a IKRigGoal and store it on this rig. Goal transform assumed in Component Space of Skeletal Mesh.
- L74 _public function_ `void ClearAllGoals()` — `UFUNCTION(BlueprintCallable, Category=IKRigGoals)` — Remove all stored goals in this component.
- L78 _public function_ `virtual void AddIKGoals_Implementation(TMap<FName, FIKRigGoal>& OutGoals) override` — Called from the IK Rig Anim node to obtain all the goals that have been set on this actor.
- L89 _private member_ `FIKRigGoalContainer GoalContainer;`

### `Plugins/Animation/IKRig/Source/IKRig/Public/ActorComponents/IKRigInterface.h` (Public)


#### class `UIKGoalCreatorInterface`  
`class UIKGoalCreatorInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IIKGoalCreatorInterface`  
`class IIKGoalCreatorInterface`  
_L16-25_
- L24 _public prototype_ `void AddIKGoals(TMap<FName, FIKRigGoal>& OutGoals);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=IKRigGoals)` — Add your own goals to the OutGoals map (careful not to remove existing goals in the map!)

### `Plugins/Animation/IKRig/Source/IKRig/Public/AnimNodes/AnimNode_IKRig.h` (Public)


#### struct `FAnimNode_IKRig`  
`struct FAnimNode_IKRig : public FAnimNode_CustomProperty`  
_L22-136_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_CustomProperty`
- L26 _public prototype_ `FAnimNode_IKRig();`
- L30 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, Category = Links)` — The input pose to start the IK solve relative to.
- L34 _public member_ `TObjectPtr<UIKRigDefinition> RigDefinitionAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = RigDefinition, meta = (NeverAsPin))` — The IK rig to use to modify the incoming source pose.
- L38 _public member_ `TArray<FIKRigGoal> Goals;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal, meta=(NeverAsPin))` — The input goal transforms used by the IK Rig solvers.
- L42 _public member_ `bool bStartFromRefPose = false;` — `UPROPERTY(EditAnywhere, Category = Solver)` — optionally ignore the input pose and start from the reference pose each solve
- L47 _public member_ `bool bDriveWithSourceAsset = false;` — when true, goals will use the current transforms stored in the IK Rig Definition asset itself
- L51 _public member_ `bool bEnableDebugDraw = false;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Toggle debug drawing of goals when node is selected.
- L55 _public member_ `float DebugScale = 5.0f;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Adjust size of debug drawing.
- L61 _public member_ `EAnimAlphaInputType AlphaInputType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)` — alpha value handler
- L64 _public member_ `bool bAlphaBoolEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, DisplayName = "bEnabled"))`
- L68 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Current strength of the skeletal control
- L71 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L74 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayName = "Blend Settings"))`
- L77 _public member_ `FName AlphaCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))`
- L80 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L85 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L86 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L87 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L88 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L89 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L90 _public function_ `virtual bool HasPreUpdate() const override`
- L91 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L92 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L93 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L97 _public prototype_ `void SetProcessorNeedsInitialized();` — force reinitialization
- L99 _public prototype_ `FIKRigProcessor* GetIKRigProcessor();`
- L104 _private member_ `FIKRigProcessor IKRigProcessor;` — IK Rig runtime processor
- L108 _private member_ `TArray<TObjectPtr<UActorComponent>> GoalCreators;` — `UPROPERTY(transient)` — a cached list of components on the owning actor that implement the goal creator interface
- L109 _private member_ `TMap<FName, FIKRigGoal> GoalsFromGoalCreators;`
- L110 _private member_ `bool bSearchedForGoalCreators = false;`
- L112 _private member_ `TMap<FCompactPoseBoneIndex, int32, FDefaultSetAllocator, TCompactPoseBoneIndexMapKeyFuncs<int32>> CompactPoseToRigIndices;`
- L115 _private typedef_ `using PropertyUpdateFunction = TFunction<void(const UObject*)>;` — Cached functions used to update goals using custom properties to avoid looking for then when evaluating
- L116 _private member_ `TArray<PropertyUpdateFunction> UpdateFunctions;`
- L118 _private member_ `float ActualAlpha;`
- L120 _private prototype_ `void CopyInputPoseToSolver(FCompactPose& InputPose);`
- L121 _private prototype_ `void AssignGoalTargets();`
- L122 _private prototype_ `void CopyOutputPoseToAnimGraph(FCompactPose& OutputPose);`
- L124 _private prototype_ `virtual void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const;`
- L130 _protected function_ `virtual UClass* GetTargetClass() const override` — FAnimNode_CustomProperty interface
- L131 _protected prototype_ `virtual void InitializeProperties(const UObject* InSourceInstance, UClass* InTargetClass) override;`
- L132 _protected prototype_ `virtual void PropagateInputProperties(const UObject* InSourceInstance) override;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/AnimNodes/AnimNode_RetargetPoseFromMesh.h` (Public)


#### enum `ERetargetSourceMode`  
`enum class ERetargetSourceMode : uint8`  
_L20-25_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `ParentSkeletalMeshComponent`
- L23 _public enumerator_ `CustomSkeletalMeshComponent`
- L24 _public enumerator_ `SourcePosePin`

#### struct `FAnimNode_RetargetPoseFromMesh`  
`struct FAnimNode_RetargetPoseFromMesh : public FAnimNode_CustomProperty`  
_L28-149_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_CustomProperty`
- L34 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, Category = Links)` — Input pose to be modified by the retargeter when using "Source Pose Pin" mode as the Input Pose Mode.
- L38 _public member_ `ERetargetSourceMode RetargetFrom = ERetargetSourceMode::ParentSkeletalMeshComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(NeverAsPin))` — Specify where to get the source pose to retarget from. Can be from the anim graph, or a different skeletal mesh component.
- L42 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SourceMeshComponent = nullptr;` — `UPROPERTY(BlueprintReadWrite, transient, Category = Settings, meta=(PinShownByDefault))` — The Skeletal Mesh Component to retarget animation from. Assumed to be animated and tick BEFORE this anim instance.
- L46 _public member_ `TObjectPtr<UIKRetargeter> IKRetargeterAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinHiddenByDefault))` — Retarget asset to use. Must define a Source and Target IK Rig compatible with the SourceMeshComponent and current anim instance.
- L50 _public member_ `FRetargetProfile CustomRetargetProfile;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinHiddenByDefault))` — Connect a custom retarget profile to modify the retargeter's settings at runtime.
- L54 _public member_ `bool bUseCustomOverrideSets = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(PinHiddenByDefault))` — If true, will use the custom list of named override sets to apply. These are stored in the retarget asset.
- L58 _public member_ `TArray<FName> OverrideSetsToApply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(EditCondition="bUseCustomOverrideSets", PinHiddenByDefault))` — Apply one or more override sets stored in the retarget asset.
- L64 _public member_ `int32 LODThreshold = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run. For example if you have LODThreshold at 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate A value of -1 forces the node to execute at all LOD levels.
- L71 _public member_ `int32 LODThresholdForIK = -1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "IK LOD Threshold"))` — Max LOD that IK is allowed to run. For example if you have LODThresholdForIK at 2, it will skip the IK pass on LODs 3 and greater. This only disables IK and does not affect the Root or FK passes. A value of -1 forces the node to execute at all LOD levels.
- L75 _public member_ `bool bSuppressWarnings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug, meta = (NeverAsPin))` — Toggle whether to print warnings about missing or incorrectly configured retarget configurations.
- L78 _public member_ `bool bUseAttachedParent_DEPRECATED = true;` — `UPROPERTY()`
- L81 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L82 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L83 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L84 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L85 _public function_ `virtual bool HasPreUpdate() const override`
- L86 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L87 _public function_ `virtual int32 GetLODThreshold() const override`
- L91 _public function_ `virtual UClass* GetTargetClass() const override` — FAnimNode_CustomProperty interface
- L95 _public prototype_ `FIKRetargetProcessor* GetRetargetProcessor();` — access to the runtime processor
- L98 _public prototype_ `bool EnsureProcessorIsInitialized(const USkeletalMeshComponent* TargetMeshComponent);` — returns true if processor is setup and ready to go, false otherwise
- L101 _public prototype_ `bool Serialize(FArchive& Ar);` — load deprecated properties
- L102 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L105 _public prototype_ `double GetAverageExecutionTime() const;`
- L112 _private member_ `FInstancedPropertyBag RuntimeVariables;` — `UPROPERTY(Transient)` — the runtime storage for variable values
- L116 _private member_ `TMap<FName, float> BoundCurveValues;` — `UPROPERTY(Transient)` — a map of curves bound to property overrides (Name, float)
- L117 _private member_ `int32 CachedOverrideVersion = INDEX_NONE;`
- L120 _private prototype_ `void CopyInputPropertiesToVariables(const UObject* InSourceInstance);` — pulls runtime values of variables out of anim instance and stores in RuntimeVariables
- L123 _private prototype_ `void CopyBoundCurveValues(const UObject* InSourceInstance);` — fills BoundCurves from the anim instance
- L126 _private prototype_ `FRetargetProfile GetMergedRetargetProfile(bool bEnableIK) const;` — get a retarget profile that includes settings from the asset, plus any custom profile overrides
- L129 _private member_ `FIKRetargetProcessor Processor;` — the runtime processor used to run the retarget and generate new poses
- L132 _private member_ `TArray<FTransform> PoseToRetargetFromComponentSpace;` — cached transforms, copied on the game thread
- L135 _private member_ `TArray<FTransform> InputLocalTransforms;` — reusable buffer when retargeting a pose from the anim graph pose pin
- L138 _private member_ `TArray< TPair<int32, int32> > CompactToTargetBoneIndexMap;` — mapping from required compact bone indices to target mesh bones expected by the retargeter
- L141 _private member_ `float DeltaTime;` — the delta time this tick
- L144 _private member_ `bool bSearchedForParentComponent = false;` — used to determine when to look for a parent component (prevents constantly searching component hierarchy)
- L147 _private member_ `double AverageExecutionTime;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_RetargetPoseFromMesh> : public TStructOpsTypeTraitsBase2<FAnimNode_RetargetPoseFromMesh>`  
_L152-159_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_RetargetPoseFromMesh>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L155-158_

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API IKRIG_API`
- L156 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonad646f310103`)
- L157 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonad646f310103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/AnimNodes/RigUnit_IKRig.h` (Public)


#### struct `FIKRigWorkData`  
`struct FIKRigWorkData`  
_L15-24_
- reflection: `USTRUCT()`
- L19 _public function_ `FIKRigWorkData()`
- L21 _public member_ `TArray<FCachedRigElement> CachedRigElements;`
- L23 _public member_ `FIKRigProcessor IKRigProcessor;`

#### struct `FIKRigGoalInput`  
`struct FIKRigGoalInput`  
_L27-54_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public function_ `FIKRigGoalInput() : GoalName(NAME_None), Transform(FTransform::Identity), PositionAlpha(1.0), RotationAlpha(1.0)`
- L41 _public member_ `FName GoalName;` — `UPROPERTY(EditAnywhere, Category=GoalSettings)` — The name of the goal to affect. Must match the name in the IK Rig.
- L45 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category=GoalSettings)` — The position and rotation target for the IK Goal.
- L49 _public member_ `double PositionAlpha;` — `UPROPERTY(EditAnywhere, Category=GoalSettings)` — Range 0-1, default 1. Blends the Goal position from the input pose position to the Goal position.
- L53 _public member_ `double RotationAlpha;` — `UPROPERTY(EditAnywhere, Category=GoalSettings)` — Range 0-1, default 1. Blends the Goal rotation from the input pose rotation to the Goal rotation.

#### struct `FRigUnit_IKRig`  
`struct FRigUnit_IKRig : public FRigUnit_HighlevelBaseMutable`  
_L58-81_
- reflection: `USTRUCT(meta=(DisplayName="IK Rig", Category="Hierarchy", Keywords="IK Rig, IK", NodeColor="0 1 1"))`
- inherits: `FRigUnit_HighlevelBaseMutable`
- desc: Supply an IK Rig asset and provide goal transforms to run IK on the skeleton.
- L62 _public function_ `FRigUnit_IKRig()`
- L64 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L69 _public member_ `TObjectPtr<UIKRigDefinition> IKRigAsset;` — `UPROPERTY(meta = (Input))` — An IK Rig asset to be evaluated.
- L73 _public member_ `TArray<FIKRigGoalInput> Goals;` — `UPROPERTY(meta = (Input))` — A list of Goals to solve. These must match what is in the IK Rig, any missing Goals will have their alphas set to zero.
- L76 _public member_ `FIKRigWorkData WorkData;` — `UPROPERTY(transient)`
- L80 _private prototype_ `static void CacheRigElements(TArray<FCachedRigElement>& OutMap, const TArray<FName>& InBoneNames, URigHierarchy* InHierarchy);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/IKRig.h` (Public)


#### class `FIKRigModule`  
`class FIKRigModule : public IModuleInterface`  
_L13-20_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _variable_ `static const TCHAR* IKRigReinitOnEditMetaLabel = TEXT("Rei` — a UProperty metadata tag used to indicate that a property should trigger reinitialization when edited
- L11 _variable_ `static const TCHAR* IKRigNonOverrideableMetaLabel = TEXT("Not` — a UProperty metadata tag used to indicate that a property can not be overridden by a profile

### `Plugins/Animation/IKRig/Source/IKRig/Public/IKRigDebugRendering.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace IKRigDebugRendering`
- L10 _variable_ `static TArray CubeVertices = { FVector(-0.5f, 0.5f, -0.5f), FVector(0.5f, 0.5f, -0.5f), FVector(0.5f, 0.5f, 0.5f), FVector(-0.5f, 0.5f, 0.5f), FVector(-0.5f, -0.5f, -0.5f), FVector(0.5f, -0.5f, -0.5f), FVector(0.5f, -0.5f, 0.5f), FVector(-0.5f, -0.5f, 0.5f), };` (scope `IKRigDebugRendering`) — 8 vertices of cube
- L24 _variable_ `static TArray CubeEdges = {` (scope `IKRigDebugRendering`) — 12 edges of cube
- L45 _function_ `static void DrawWireCube( FPrimitiveDrawInterface* PDI, const FTransform& Transform, FLinearColor Color, float Size, float Thickness)` (scope `IKRigDebugRendering`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/IKRigLogger.h` (Public)


#### struct `FIKRigLogger`  
`struct FIKRigLogger`  
_L12-43_
- L15 _public prototype_ `void SetLogTarget(const UObject* InAsset);` — Assign an asset for this log to store messages for.
- L17 _public prototype_ `FName GetLogTarget() const;` — Get the name this log is currently outputting to
- L19 _public prototype_ `void LogError(const FText& Message) const;` — Log a warning message to display to user.
- L21 _public prototype_ `void LogWarning(const FText& Message) const;` — Log a warning message to display to user.
- L23 _public prototype_ `void LogInfo(const FText& Message) const;` — Log a message to display to editor output log.
- L25 _public prototype_ `void Clear() const;` — clear all the stored messages
- L27 _public function_ `const TArray<FText>& GetErrors() const` — get a list of messages that have been logged since last Clear()
- L28 _public function_ `const TArray<FText>& GetWarnings() const`
- L29 _public function_ `const TArray<FText>& GetMessages() const`
- L37 _private member_ `FName LogName;` — the name of the output log this logger will send messages to For the IK Rig and Retargeting editors, we desire to filter the messages that originate only from the asset that is being edited. Therefore we name the log using the unique ID of the UObject itself (valid for lifetime of UObject between loads)
- L40 _private member_ `mutable TArray<FText> Errors;` — store messages here so we can show them during anim graph compilation
- L41 _private member_ `mutable TArray<FText> Warnings;`
- L42 _private member_ `mutable TArray<FText> Messages;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKRig, Warning, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIKRig, Warning, All);`

### `Plugins/Animation/IKRig/Source/IKRig/Public/IKRigObjectVersion.h` (Public)


#### struct `FIKRigObjectVersion`  
`struct FIKRigObjectVersion`  
_L10-69_
- desc: Custom serialization version for backwards compatibility during de-serialization
- L12 _public prototype_ `FIKRigObjectVersion() = delete;`
- L68 _public member_ `const static FGuid GUID;` — The GUID for this custom version number

#### enum `FIKRigObjectVersion::Type`  
`enum Type`  
_L14-65_
- L17 _public enumerator_ `BeforeCustomVersionWasAdded` — Before any version changes were made
- L20 _public enumerator_ `RetargetPoseQuatPostMultiplied` — Retarget pose quaternions changed from pre to post multiplied
- L23 _public enumerator_ `ChainSettingsConvertedToStruct` — Chain settings moved to struct to be used in profiles
- L27 _public enumerator_ `PinBoneTypeAndOffsetsUpgraded` — Pin Bone "Pin Type" converted into separate trans/rot/scale toggles Pin Bone "Maintain Offset" converted from bool to enum
- L30 _public enumerator_ `UseAttachedParentDeprecated` — we switched "Use Attach Parent" from a bool to an enum on retarget pose from mesh node
- L33 _public enumerator_ `ModularRetargeterOps` — modularized retargeting internals (converted phases to ops)
- L36 _public enumerator_ `OpsOwnChainMapping` — ops control their own chain mapping (no more global chain map on retarget asset)
- L39 _public enumerator_ `CopyBasePoseConvertedToBoneReference` — copy base pose op converted to use FBoneReference
- L42 _public enumerator_ `RemovedPelvisMotionFromSourceGoals` — changed default behavior of BlendToSource on IK Goals to not be affected by Pelvis motion
- L45 _public enumerator_ `MovedChainMappingToFKChainOpSettings` — moved chain mapping in FKChainsOp from Op to Op-settings for read-only API access
- L48 _public enumerator_ `AddedDebugDrawTogglePerOp` — added "bEnableDebugDraw" to base op settings
- L51 _public enumerator_ `AddedLocalGlobalOffsetsToPelvisOp` — added local/global offsets to pelvis motion op
- L54 _public enumerator_ `IKChainsOpSplitIntoSeparateOps` — the "Retarget IK Goals" op is deprecated and features are split into separate ops
- L57 _public enumerator_ `AddedRootBoneToRetargetDefinition` — IK Rig retarget definition now stores separate root bone and pelvis bone
- L60 _public enumerator_ `EnabledStateMovedFromOpToOpSettings` — the op settings now contain bEnabled instead of the ops themselves
- L63 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L64 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetChainMapping.h` (Public)


#### enum `EAutoMapChainType`  
`enum class EAutoMapChainType : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Exact` — map chains that have exactly the same name (case insensitive)
- L16 _public enumerator_ `Fuzzy` — map chains to the chain with the closest name (levenshtein distance)
- L17 _public enumerator_ `Clear` — clear all mappings, set them to None

#### struct `FRetargetChainPair`  
`struct FRetargetChainPair`  
_L21-34_
- reflection: `USTRUCT()`
- L25 _public prototype_ `FRetargetChainPair() = default;`
- L26 _public function_ `FRetargetChainPair(const FName InTargetChainName, const FName InSourceChainName) : TargetChainName(InTargetChainName), SourceChainName(InSourceChainName)`
- L30 _public member_ `FName TargetChainName = NAME_None;` — `UPROPERTY()`
- L33 _public member_ `FName SourceChainName = NAME_None;` — `UPROPERTY()`

#### struct `FRetargetChainMapping`  
`struct FRetargetChainMapping`  
_L37-108_
- reflection: `USTRUCT()`
- L45 _public prototype_ `void ReinitializeWithIKRigs(const UIKRigDefinition* InSourceIKRig, const UIKRigDefinition* InTargetIKRig);` — cleans the chain mapping to reflect the chains in the provided source/target IK Rigs NOTE: this will maintain existing mappings while removing unused ones and adding missing ones
- L48 _public prototype_ `bool IsReady() const;` — returns true if both a source and target IK Rig have been loaded
- L51 _public prototype_ `bool HasAnyChains() const;` — returns true if any chains have been loaded, regardless of if they are mapped
- L54 _public prototype_ `const UIKRigDefinition* GetIKRig(ERetargetSourceOrTarget SourceOrTarget);` — get one of the IK Rigs used in this mapping
- L60 _public prototype_ `bool HasChain(const FName& InChainName, ERetargetSourceOrTarget InSourceOrTarget) const;` — Check if the chain exists. @param InChainName the name of either a source or target chain @param InSourceOrTarget the side that InChainName belongs to (either source or target) @return true if the chain is present in the mapping
- L66 _public prototype_ `FName GetChainMappedTo(const FName InChainName, ERetargetSourceOrTarget InSourceOrTarget) const;` — Get the name of the bone chain mapped to this chain. @param InChainName the name of either a source or target chain @param InSourceOrTarget the side that InChainName belongs to (either source or target) @return the name of the chain that InChainName is mapped to (possibly NAME_None)
- L71 _public prototype_ `FRetargetChainPair* FindChainPair(const FName& InChainName, ERetargetSourceOrTarget InSourceOrTarget) const;` — returns the chain pair belonging to the supplied chain or nullptr if not found @param InChainName the name of either a source or target chain @param InSourceOrTarget the side that InChainName belongs to (either source or target)
- L72 _public prototype_ `const FRetargetChainPair* FindChainPairConst(const FName& InChainName, ERetargetSourceOrTarget InSourceOrTarget) const;`
- L75 _public prototype_ `TArray<FRetargetChainPair>& GetChainPairs();` — Get read-write access to the mapping from target to source chains (by name)
- L76 _public prototype_ `const TArray<FRetargetChainPair>& GetChainPairs() const;`
- L79 _public prototype_ `TArray<FName> GetChainNames(ERetargetSourceOrTarget InSourceOrTarget) const;` — Get the names of all the chains in either the source or target IK Rig
- L84 _public prototype_ `void SetChainMapping(const FName InTargetChainName, const FName InSourceChainName);` — Map target chain to a source chain. @param InTargetChainName the name of a target chain @param InSourceChainName the name of a source chain
- L87 _public prototype_ `void SortMapping();` — sort mapping hierarchically (root to leaf based on Target IK Rig hierarchy)
- L90 _public prototype_ `void AutoMapChains(const EAutoMapChainType AutoMapType, const bool bForceRemap);` — automatically map the source and target chains together
- L93 _public prototype_ `void LoadFromDeprecatedChainSettings(const TArray<URetargetChainSettings*>& InChainSettings);`
- L101 _private member_ `TArray<FRetargetChainPair> ChainMap;` — `UPROPERTY()` — mapping of target to source bone chains by name NOTE: this is an array instead of a TMap because it needs to be sorted by hierarchy
- L104 _private member_ `TObjectPtr<const UIKRigDefinition> SourceIKRig = nullptr;` — `UPROPERTY()`
- L107 _private member_ `TObjectPtr<const UIKRigDefinition> TargetIKRig = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetDeprecated.h` (Public)


#### struct `FTargetChainSpeedPlantSettings`  
`struct FTargetChainSpeedPlantSettings`  
_L20-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced by Speed Planting Op
- L25 _public member_ `bool EnableSpeedPlanting = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L27 _public member_ `FName SpeedCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L29 _public member_ `float SpeedThreshold = 15.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L31 _public member_ `float UnplantStiffness = 250.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L33 _public member_ `float UnplantCriticalDamping = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### enum `ERetargetTranslationMode`  
`enum class ERetargetTranslationMode : uint8`  
_L38-45_
- reflection: `UENUM(BlueprintType)`
- desc: NOTE: Replaced by FK Chain Op
- L40 _public enumerator_ `None UMETA(DisplayName = "None")`
- L41 _public enumerator_ `GloballyScaled UMETA(DisplayName = "Globally Scaled")`
- L42 _public enumerator_ `Absolute UMETA(DisplayName = "Absolute")`
- L43 _public enumerator_ `StretchBoneLengthUniformly UMETA(DisplayName = "Stretch Bone Length Uniformly")`
- L44 _public enumerator_ `StretchBoneLengthNonUniformly UMETA(DisplayName = "Stretch Bone Length Non-Uniformly")`

#### enum `ERetargetRotationMode`  
`enum class ERetargetRotationMode : uint8`  
_L49-57_
- reflection: `UENUM(BlueprintType)`
- desc: NOTE: Replaced by FK Chain Op
- L51 _public enumerator_ `Interpolated UMETA(DisplayName = "Interpolated")`
- L52 _public enumerator_ `OneToOne UMETA(DisplayName = "One to One")`
- L53 _public enumerator_ `OneToOneReversed UMETA(DisplayName = "One to One Reversed")`
- L54 _public enumerator_ `MatchChain UMETA(DisplayName = "Match Chain")`
- L55 _public enumerator_ `MatchScaledChain UMETA(DisplayName = "Match Scaled Chain")`
- L56 _public enumerator_ `None UMETA(DisplayName = "None")`

#### struct `FTargetChainFKSettings`  
`struct FTargetChainFKSettings`  
_L61-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced by FK Chain Op
- L66 _public member_ `bool EnableFK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L68 _public member_ `ERetargetRotationMode RotationMode = ERetargetRotationMode::Interpolated;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L70 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L72 _public member_ `ERetargetTranslationMode TranslationMode = ERetargetTranslationMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L74 _public member_ `float TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L76 _public member_ `float PoleVectorMatching = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L78 _public member_ `bool PoleVectorMaintainOffset = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L80 _public member_ `float PoleVectorOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### struct `FTargetChainIKSettings`  
`struct FTargetChainIKSettings`  
_L85-111_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced by IK Chain Op
- L90 _public member_ `bool EnableIK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L92 _public member_ `float BlendToSource = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L94 _public member_ `float BlendToSourceTranslation = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L96 _public member_ `float BlendToSourceRotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L98 _public member_ `FVector BlendToSourceWeights = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L100 _public member_ `FVector StaticOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L102 _public member_ `FVector StaticLocalOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L104 _public member_ `FRotator StaticRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L106 _public member_ `float ScaleVertical = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L108 _public member_ `float Extension = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L110 _public member_ `bool bAffectedByIKWarping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### struct `FTargetChainSettings`  
`struct FTargetChainSettings`  
_L115-124_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced by FK/IK Chain Ops and Speed Planting Op
- L119 _public member_ `FTargetChainFKSettings FK;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L121 _public member_ `FTargetChainIKSettings IK;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L123 _public member_ `FTargetChainSpeedPlantSettings SpeedPlanting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### struct `FTargetRootSettings`  
`struct FTargetRootSettings`  
_L128-152_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced by Pelvis Motion Op
- L133 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L135 _public member_ `float TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L137 _public member_ `float BlendToSource = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L139 _public member_ `FVector BlendToSourceWeights = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L141 _public member_ `float ScaleHorizontal = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L143 _public member_ `float ScaleVertical = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L145 _public member_ `FVector TranslationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L147 _public member_ `FRotator RotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L149 _public member_ `float AffectIKHorizontal = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L151 _public member_ `float AffectIKVertical = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### struct `FRetargetGlobalSettings`  
`struct FRetargetGlobalSettings`  
_L156-188_
- reflection: `USTRUCT(BlueprintType)`
- desc: NOTE: Replaced IK/FK/Post toggle flags with Op-enabled flags. Warping settings now in Stride Warp Op.
- L161 _public member_ `bool bEnableRoot = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L163 _public member_ `bool bEnableFK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L165 _public member_ `bool bEnableIK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L167 _public member_ `bool bEnablePost = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L169 _public member_ `bool bCopyBasePose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L171 _public member_ `FName CopyBasePoseRoot = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L173 _public member_ `float SourceScaleFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L175 _public member_ `bool bWarping = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L177 _public member_ `EWarpingDirectionSource DirectionSource = EWarpingDirectionSource::Goals;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L179 _public member_ `EBasicAxis ForwardDirection = EBasicAxis::Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L181 _public member_ `FName DirectionChain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L183 _public member_ `float WarpForwards = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L185 _public member_ `float SidewaysOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`
- L187 _public member_ `float WarpSplay = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DeprecatedSettings, meta=(DeprecatedProperty))`

#### class `URetargetChainSettings`  
`class URetargetChainSettings : public UObject`  
_L192-252_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: NOTE: Replaced with IK/FK Chains Op and new mapping data.
- L199 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject
- L207 _public member_ `FName SourceChain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(DeprecatedProperty))`
- L209 _public member_ `FName TargetChain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(DeprecatedProperty))`
- L211 _public member_ `FTargetChainSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(DeprecatedProperty))`
- L218 _public member_ `bool CopyPoseUsingFK_DEPRECATED = true;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L220 _public member_ `ERetargetRotationMode RotationMode_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L222 _public member_ `float RotationAlpha_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L224 _public member_ `ERetargetTranslationMode TranslationMode_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L226 _public member_ `float TranslationAlpha_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L228 _public member_ `bool DriveIKGoal_DEPRECATED = true;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L230 _public member_ `float BlendToSource_DEPRECATED = 0.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L232 _public member_ `FVector BlendToSourceWeights_DEPRECATED = FVector::OneVector;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L234 _public member_ `FVector StaticOffset_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L236 _public member_ `FVector StaticLocalOffset_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L238 _public member_ `FRotator StaticRotationOffset_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L240 _public member_ `float Extension_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L242 _public member_ `bool UseSpeedCurveToPlantIK_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L244 _public member_ `FName SpeedCurveName_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L246 _public member_ `float VelocityThreshold_DEPRECATED = 15.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L248 _public member_ `float UnplantStiffness_DEPRECATED = 250.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L250 _public member_ `float UnplantCriticalDamping_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`

#### class `URetargetRootSettings`  
`class URetargetRootSettings: public UObject`  
_L256-281_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: NOTE: Replaced by Pelvis Op and it's settings.
- L262 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L266 _public member_ `FTargetRootSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(DeprecatedProperty))` — deprecated in 5.6 op refactor
- L269 _public member_ `bool RetargetRootTranslation_DEPRECATED = true;` — `UPROPERTY(meta=(DeprecatedProperty))` — Deprecated properties from before FTargetRootSettings / profile refactor
- L271 _public member_ `float GlobalScaleHorizontal_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L273 _public member_ `float GlobalScaleVertical_DEPRECATED = 1.0f;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L275 _public member_ `FVector BlendToSource_DEPRECATED = FVector::ZeroVector;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L277 _public member_ `FVector StaticOffset_DEPRECATED = FVector::ZeroVector;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L279 _public member_ `FRotator StaticRotationOffset_DEPRECATED = FRotator::ZeroRotator;` — `UPROPERTY(meta=(DeprecatedProperty))`

#### class `UIKRetargetGlobalSettings`  
`class UIKRetargetGlobalSettings: public UObject`  
_L285-293_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: NOTE: Phase toggles replaced by op enabled flags. Stride warp settings replaced by Stride Warp op.
- L292 _public member_ `FRetargetGlobalSettings Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(DeprecatedProperty))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetOpUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace IKRetargetOpUtils`
- L38 _function_ `template<typename T> void SynchronizeChainSettingsWithIKRig( TArray<T>& InOutChainSettings, const FIKRetargetOpBase* InRetargetOp, const bool bSkipUnmappedChains, const bool bSkipNonIKChains)` (scope `IKRetargetOpUtils`) — Synchronizes a custom chain settings array with the chains in an IK Rig asset. Convenience function for retarget ops that need to keep an array of custom chain settings in sync with the chains defined in an IK Rig asset. @tparam T  Custom struct type representing chain settings. @param InOutChainSettings   Array of chain settings to synchronize. @param InRetargetOp         Retarget operation providing access to the IK Rig. @param bSkipUnmappedChains  If true, unmapped chains are ignored. @param bSkipNonIKChains     If true, chains without IK goals are ignored. @note  To use this function, your type T must: 1. Implement: - FName GetName() - void SetName(FName InChainName) 2. Provide a constructor that accepts the chain name. @note  This function will early-return if no valid chains are found. It does NOT clear the array, allowing users to reassign a different rig and preserve compatible settings.
- L98 _function_ `` (scope `IKRetargetOpUtils::SynchronizeChainSettingsWithIKRig`)
- L137 _function_ `template<typename T> void OnRetargetChainRenamed(TArray<T>& InOutChainSettings, const FName InOldChainName, const FName InNewChainName)` (scope `IKRetargetOpUtils`) — Responds to an IK Rig chain being renamed by updating the corresponding entry in a settings array. Convenience function for retarget ops that maintain custom per-chain settings. @tparam T  Custom struct type representing chain settings. @param InOutChainSettings  Array of chain settings to update. @param InOldChainName      Previous name of the chain. @param InNewChainName      New name of the chain. @note  Type T must implement: - FName GetName() - void SetName(FName InChainName)
- L165 _function_ `template<typename T> void CopyChainSettingsAtRuntime(const TArray<T>& InSettingsToCopyFrom, TArray<T>& InSettingsToCopyTo)` (scope `IKRetargetOpUtils`) — Copies matching chain settings from one array to another at runtime. Convenience function for retarget ops that need to copy per-chain settings between runtime instances of the same operation. @tparam T  Custom struct type representing chain settings. @param InSettingsToCopyFrom  Source array of chain settings. @param InSettingsToCopyTo    Destination array to update. @note  Only copies settings for chains that exist in both arrays. @note  Type T must implement: - FName GetName() - void SetName(FName InChainName)
- L198 _function_ `template<typename T> void ResetChainSettingsToDefault(TArray<T>& InChainSettingsArray, const FName& InChainName)` (scope `IKRetargetOpUtils`) — Resets the settings for a specific IK chain to its default values. Convenience function for retarget ops that manage per-chain settings arrays. Finds the matching chain by name and replaces its settings with a new default-constructed instance. @tparam T  Custom struct type representing chain settings. @param InChainSettingsArray  Array of chain settings to search and modify. @param InChainName           Name of the chain to reset. @note  Type T must: - Implement FName GetName() - Provide a constructor that accepts a chain name (FName) @note  If no matching chain is found, this function does nothing.
- L230 _function_ `template<typename T> bool AreChainSettingsAtDefault(const TArray<T>& InChainSettingsArray, const FName& InChainName)` (scope `IKRetargetOpUtils`) — Checks whether the settings for a specific chain are at their default values. Generic utility function for retarget ops that manage per-chain settings arrays. Compares the specified chain’s current settings to a default-constructed instance. @tparam T  Custom struct type representing chain settings. @param InChainSettingsArray  Array of chain settings to search. @param InChainName           Name of the chain to compare. @return True if the chain’s settings match the default values, or if the chain is not found. @note  Type T must: - Implement FName GetName() - Provide a constructor that accepts a chain name (FName) - Implement operator== for equality comparison
- L261 _function_ `template<typename T> uint8* GetChainSettingsMemory(TArray<T>& InChainSettingsArray, const FName& InChainName)` (scope `IKRetargetOpUtils`) — Returns a raw pointer to the memory of a specific chain’s settings instance. @tparam T  Custom struct type representing chain settings. @param InChainSettingsArray  Array of chain settings to search. @param InChainName           Name of the chain whose settings memory address should be returned. @return Pointer to the chain’s settings in memory, or nullptr if the chain is not found. @note  Type T must implement: - FName GetName() @warning  The returned pointer refers to memory owned by the array. It becomes invalid if the array is modified or reallocated. Use with caution.

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetOps.h` (Public)


#### struct `FIKRetargetOpSkeletonProvider`  
`struct FIKRetargetOpSkeletonProvider`  
_L37-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Because the settings structs in the retarget op stack are not UObjects, we cannot use the IBoneReferenceSkeletonProvider interface Instead, if Op settings require a FBoneReference with a bone selector widget then the settings must inherit either directly from this (in the case of sub structs), or indirectly from the FIKRetargetOpSettingBase for the op's main settings struct.
- L41 _public function_ `virtual ~FIKRetargetOpSkeletonProvider()`
- L46 _public member_ `mutable const USkeleton* SourceSkeletonAsset;` — a reference to the skeletons for bone selector widgets (can return these from GetSkeleton)
- L47 _public member_ `mutable const USkeleton* TargetSkeletonAsset;`
- L49 _public function_ `virtual USkeleton* GetSkeleton(const FName InPropertyName)` — allow settings to provide a skeleton for any given FBoneReference widget. Defaults to the target skeleton.
- L52 _public function_ `virtual USkeleton* GetSkeleton(const IPropertyHandle* InPropertyHandle)` — optional alternative to GetSkeleton that provides the full PropertyHandle. This is used if GetSkeleton(const FName) returns null NOTE: the property handle is necessary to help differentiate properties in copies of the same struct type

#### struct `FIKRetargetOpSettingsBase`  
`struct FIKRetargetOpSettingsBase : public FIKRetargetOpSkeletonProvider`  
_L70-157_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRetargetOpSkeletonProvider`
- desc: This is the base class for defining editable settings for a custom retargeting operation. All user-configurable properties for an "op" should be stored within a single instance of a subclass of this type. These settings will automatically be: 1. Displayed in the details panel when the op is selected 2. Saved/loaded with the op in the retarget asset 3. Applied to the op at runtime as part of a profile NOTE: the derived type must be returned by the op's GetSettingsType() and GetSettings() NOTE: UProperties that require reinitialization when modified must be marked meta=(ReinitializeOnEdit) When modified, in the editor, these properties will trigger a reinitialization at which point the runtime Op will get the latest values automatically.
- L74 _public prototype_ `virtual ~FIKRetargetOpSettingsBase() = default;`
- L78 _public member_ `bool bEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enable Op")` — Enable/disable the entire operation. Disabled ops are skipped entirely and do not run at all.
- L84 _public member_ `int32 LODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level of Detail")` — The maximum LOD that this Op is allowed to run at. For example if you have LODThreshold of 2, the Op will run until LOD 2 (based on 0 index). When the component LOD becomes 3, it will stop running. A value of -1 forces the Op to execute at all LOD levels. Default is -1.
- L88 _public member_ `bool bDebugDraw = true;` — `UPROPERTY()` — toggle on/off all debug drawing on the op.
- L91 _public function_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom)` — (required) override to specify how settings should be applied in a way that will not require reinitialization (ie runtime compatible)
- L112 _public function_ `template <typename T> static bool SerializeOpWithVersion(FArchive& Ar, T& Self)` — NOTE ON RETARGET OP POSTLOAD() / SERIALIZE() BEHAVIOR: If custom op settings require load-patching for backwards compatibility, it is NOT enough to rely on the archive being tagged with custom versioning from the UIKRetargeter itself. This is because these settings structs can be stored OUTSIDE of the retargeter (ie, in BP classes), which means they must take full control of their own back compatibility. BUT, because the settings are also stored as FInstancedStruct inside the retarget asset, and because these instanced structs do not run custom serialization, the patch must ALSO be applied explicitly from within FIKRetargetOpBase::PostLoad(). This leads us to this recommended pattern for op settings that need serialization patches: 1. Override virtual FIKRetargetOpSettingsBase::PostLoad() in your custom settings struct. This will be called by the retargeter to apply patching for any op settings stored in the asset. 2. Add the type trait WithSerializer and implement bool MyOp::Serialize(). 3. Call SerializeOpWithVersion() within the custom MyOp::Serialize() This will ensure the settings are saved with a custom version and it will call OpSettings::PostLoad() after loading Following this pattern ensures that op settings are properly patched both when they are stored in a retarget asset as an instanced struct AND if they are stored alone as a BP variable.
- L128 _public function_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion)` — (optional) called during the PostLoad of the owning asset. Can be used to apply patches to the data for backwards compatibility. NOTE: see description above on correct setup for retarget op settings serialization patches
- L132 _public prototype_ `virtual const UClass* GetControllerType() const;` — (optional, but recommended) provide a custom controller type (deriving from UIKRetargetOpControllerBase) as an API for editing the op NOTE: this type will automatically be lazy instantiated when/if the user calls GetController() on the op.
- L136 _public prototype_ `UIKRetargetOpControllerBase* GetController(UObject* Outer);` — provide a scripting object to edit your custom settings type in the editor via BP/Python NOTE: this returns an instance of whatever type is returned by GetControllerType(). This can be custom per op.
- L141 _private prototype_ `UIKRetargetOpControllerBase* CreateControllerIfNeeded(UObject* Outer);` — helper function for settings structs to instantiate their own controller
- L144 _private member_ `TStrongObjectPtr<UIKRetargetOpControllerBase> Controller = nullptr;` — the controller used to edit this op by script/blueprint (lazy instantiated when needed)
- L150 _public member_ `FName OwningOpName;` — `UPROPERTY(transient)` — the op these settings belong to
- L152 _public member_ `mutable FIKRetargetOpSettingsBase* EditorInstance;` — the instance of this op currently running in the editor viewport
- L155 _public prototype_ `virtual void AssignSkeletonAssets(const USkeleton* InSourceSkeleton, const USkeleton* InTargetSkeleton);` — assigned by the processor when an editor instance is initialized, used for UI reflection for bone selectors NOTE: if your op has sub-settings structs that inherit from FIKRetargetOpSkeletonProvider, override this to give them pointers to the skeletons

#### struct `FOpExecutionTimer`  
`struct FOpExecutionTimer`  
_L160-180_
- L163 _public prototype_ `void Reset();` — reset the running average execution time
- L166 _public prototype_ `void StartNewFrame();` — reset the per-frame time and update the running average
- L170 _public prototype_ `void AddTimeThisFrame(const double InSeconds);` — call this to add some execution time for this frame NOTE: this may be called multiple times per frame
- L173 _public prototype_ `double GetRunningAverage() const;` — returns the current running average execution time using a 30 frame exponential moving average
- L177 _private member_ `double RunningAverageTime = 0.0f;` — running average of past n frames
- L179 _private member_ `double TimeThisFrame = 0.0f;` — profiling data; time in seconds of last execution

#### struct `FIKRetargetOpBase`  
`struct FIKRetargetOpBase`  
_L191-452_
- reflection: `USTRUCT(BlueprintType)`
- desc: This is the base class for defining operations that live in the retargeter "op" stack. These operations are executed in order by calling the virtual Run() function on each one in order. The Run() function takes an input pose on the source skeletal mesh and affects the output pose on the target mesh. NOTE: any user defined settings associated with a retarget op must be aggregated into a custom UStruct derived from FIKRetargetOpSettingsBase This ensures that the settings are user editable in the details panel with full undo/redo support and serialization.
- L197 _public prototype_ `virtual ~FIKRetargetOpBase() = default;`
- L201 _public function_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log)` — (optional) override to cache internal data when initializing the processor NOTE: you must set bIsInitialized to true to inform the retargeter that this op is ok to execute.
- L209 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose)` — (optional) override to evaluate this operation and modify the output pose
- L216 _public function_ `virtual void PostInitialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, FIKRigLogger& InLog)` — (optional) a second pass of initialization that ops can use after Op::Initialize() is called on all ops.
- L223 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion);` — (optional) called during the PostLoad of the owning asset. Can be used to apply patches to the data for backwards compatibility.
- L226 _public function_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp)` — (optional) override to automate initial setup after being added to the stack
- L232 _public function_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp)` — (optional) override to react after user assigns a new IK Rig to all ops @param SourceOrTarget: whether the source or target IK Rig was changed @param InIKRig: the IK rig asset to assign to this op (will be NULL if user cleared an IK Rig) @param InParentOp: the parent for this op (may be null if unparented)
- L235 _public function_ `bool IsEnabled() const` — get if this op is enabled
- L238 _public function_ `void SetEnabled(const bool bEnabled)` — turn this operation on/off (will be skipped during execution if disabled)
- L241 _public function_ `bool IsInitialized() const` — return true if this op is initialized and ready to run
- L245 _public function_ `virtual FIKRetargetOpSettingsBase* GetSettings()` — (required) override and return a pointer to the settings struct used by this operation NOTE: it is not permitted to modify the settings from inside this getter. Treat as a const function.
- L248 _public function_ `const FIKRetargetOpSettingsBase* GetSettingsConst() const` — const access to the settings
- L253 _public prototype_ `virtual void SetSettings(const FIKRetargetOpSettingsBase* InSettings);` — `UE_DEPRECATED(5.7, "SetSettings(const FIKRetargetOpSettingsBase*) is deprecated. " "Use GetSettings()->CopySettingsAtRuntime(const FIKRetargetOpSettingsBase*) instead")` — Old API (deprecated):
- L256 _public function_ `virtual const UScriptStruct* GetSettingsType() const` — (required) override and return the type used to house the settings for this operation
- L259 _public function_ `virtual const UScriptStruct* GetType() const` — (required) override and return the type of this op (the derived subclass)
- L262 _public function_ `virtual void OnPlaybackReset()` — (optional) override to reset any internal state when animation playback is reset or stopped (ie, springs / dampers etc)
- L266 _public function_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent)` — (optional) override to get any data from the source or target skeletal mesh component NOTE: this is called during AnimGraph::PreUpdate() which runs on the main thread, use caution.
- L270 _public function_ `virtual void AnimGraphEvaluateAnyThread(FPoseContext& Output)` — (optional) override to get any data from the anim graph as it's evaluating. NOTE: this is called during AnimGraph::Evaluate_AnyThread() BEFORE the retargeting Ops are executed.
- L274 _public function_ `virtual void CollectRetargetedBones(TSet<int32>& OutRetargetedBones) const` — (optional) override and add any bones that your op modifies to the output TSet of bone indices Add indices of any bone that this op modifies. Any bone not registered here will be FK parented by other operations
- L277 _public function_ `virtual bool CanHaveChildOps() const` — (optional) ops can optionally behave as a 'parent' where child ops must be executed first.
- L280 _public function_ `virtual const UScriptStruct* GetParentOpType() const` — (optional) ops can optionally behave as a 'child' where they can be parented to ops of the type returned by this function.
- L285 _public function_ `virtual void InitializeBeforeChildren( FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, FIKRigLogger& Log)` — (optional) override to give this op a chance to initialize before it's children are initialized This is executed right after the previous op in the stack and right before the first child op Initialize() is called NOTE: unless this is a parent op, this will have no effect
- L294 _public function_ `virtual void RunBeforeChildren( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose)` — (optional) override to give this op a chance to do work before it's children are run This is executed right after the previous op in the stack and right before the first child op Run() is called NOTE: unless this is a parent op, this will have no effect
- L303 _public function_ `virtual void RunAfterParent( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose)` — (optional) override to give this op a chance to do work after it's parent is run This is executed right after the parent op in the stack and right before the next op after parent NOTE: unless this is a child op, this will have no effect
- L310 _public function_ `virtual bool IsSingleton() const` — (optional) return true to disallow multiple copies of this op in the stack
- L313 _public function_ `virtual bool IsAbstract() const` — (optional) return true to disallow adding this op to the stack
- L317 _public function_ `virtual const UIKRigDefinition* GetCustomTargetIKRig() const` — (optional) override and supply the target IK Rig this op references NOTE: The retarget processor will resolve the bone chains in the rig so that they can be queried by the op.
- L321 _public function_ `virtual FRetargetChainMapping* GetChainMapping()` — (optional) ops can optionally store their own chain mapping, this allows outside systems to query/edit it. NOTE: this is conceptually const and should not alter the op state, but only return the chain mapping!
- L324 _public function_ `const FRetargetChainMapping* GetChainMapping() const` — wraps the non-const GetChainMapping() to provide const access
- L329 _public function_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName)` — (optional) implement this if the op stores chain settings by name to allow the settings to be maintained after a chain is renamed NOTE: this is only called when the target IK Rig this op references has a chain that is renamed. NOTE: ops do not have to update chain mappings in this function, that is managed for them if GetChainMapping() is implemented
- L334 _public function_ `virtual void OnReinitPropertyEdited(const FPropertyChangedEvent* InPropertyChangedEvent)` — (optional) override to allow ops to react when a property marked "ReinitializeOnEdit" is modified NOTE: this is called before Initialize() is called again to give op a chance to auto-configure itself based on its new state NOTE: this is called in several places where InPropertyChangedEvent may be null
- L339 _public function_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent)` — (optional) override to allow ops to react when a property marked "ReinitializeOnEdit" on the parent op is modified NOTE: InPropertyChangedEvent will be null at load time giving op a chance to clean based on parent state. NOTE: this is called in several places where InPropertyChangedEvent may be null
- L344 _public prototype_ `FName GetDefaultName() const;` — get the nice name to display in the viewport (defaults to "DisplayName" UStruct metadata)
- L347 _public prototype_ `virtual FText GetWarningMessage() const;` — (optional) override to display a warning message in the op stack
- L350 _public function_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InTargetTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const` — (optional) override to draw debug info into the editor viewport when the Op is selected
- L358 _public function_ `virtual bool HasDebugDrawing()` — (required if using DebugDraw()) return true to display the debug draw toggle in the UI
- L361 _public function_ `virtual void ResetChainSettingsToDefault(const FName& InChainName)` — (optional) override to support resetting all settings for a given chain
- L364 _public function_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName)` — (optional) override to support "Reset to Default" UI for chains
- L368 _public function_ `virtual uint8* GetChainSettingsMemory(const FName InChainName)` — (required for any op that stores settings per-chain) return the memory for the settings struct associated with a particular chain NOTE: implementing this can automate some boilerplate UI setup, allows systems to display chain settings and get/set them.
- L372 _public function_ `virtual void UpdateFromAnimSequence(UAnimSequence* Sequence, float FrameTime)` — (optional) override to update op with anim sequence information when batch retargeting anim sequences NOTE: this should only be called for batch (offline) retargeting where there is no anim-instance running
- L376 _public prototype_ `virtual void GetOverrideableProperties(TSharedPtr<FRetargetPropertyOverrideNode>& OutRootNode) const;` — (optional) override this to customize which properties are available to be overridden in a profile. NOTE: the default implementation returns all overrideable properties
- L379 _public member_ `mutable FIKRetargetOpBase* EditorInstance;` — the instance of this op currently running in the editor viewport
- L382 _public member_ `FOpExecutionTimer Timer;` — a timer for the op profiler
- L390 _public function_ `virtual bool PostLoadSplitOp(TArray<FInstancedStruct>& OutNewOps)` — Called during PostLoad to allow ops to be split into multiple ops during version upgrade. Return an array of new op instances that replace this op. If empty, no splitting occurred and the original op is preserved. @param OutNewOps - Out array which will hold new op instances (if splitting occurred) @return true if this op is being replaced by OutNewOps, false to keep original op
- L397 _public prototype_ `FName GetName() const;` — Get the name of this op (may be customized by user)
- L401 _public prototype_ `void SetName(const FName InName);` — Set the name of this op NOTE: InName is assumed to be unique in the stack (this constraint is enforced when setting the name from the controller)
- L406 _public prototype_ `void SetParentOpName(const FName InName);` — Set the name of the op this op is "parented" to. This enforces execution order. NOTE: InName is assumed to refer to an op that exists. NOTE: Renaming the parent op through the controller will auto-update this.
- L409 _public prototype_ `FName GetParentOpName() const;` — Get the name of the op this op is parented to (None for root level ops)
- L414 _public prototype_ `void CopySettingsRaw(const FIKRetargetOpSettingsBase* InSettings, const TArray<FName>& InPropertiesToIgnore);` — wholesale copy all settings from the input settings into this op. NOTE: InSettings is assumed to be castable to the type returned by GetSettingsType() NOTE: be careful calling this on an initialized op as it may invalidate it's runtime state (use SetSettings instead)
- L417 _public prototype_ `static void CopyStructProperties( const UStruct* InStructType, const void* InSrcStruct, void* InOutDestStruct, const TArray<FName>& InPropertiesToIgnore);` — a convenience function to copy all properties from one struct to another while ignoring some
- L423 _public typedef_ `using FFrameValues = TArray<TArray<TOptional<float>>>;`
- L432 _public function_ `bool GetDeprecatedEnabledState() const`
- L438 _private member_ `FName Name;` — `UPROPERTY()` — the text label given to the op, used to refer to it from script
- L442 _private member_ `FName ParentOpName;` — `UPROPERTY()` — (optional) some ops are considered as a group, this is the name of the group parent
- L446 _private member_ `bool bIsEnabled_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "bIsEnabled is deprecated. Please use FIKRetargetOpSettingsBase::bEnabled instead."))` — DEPRECATED enabled flag, moved to base op settings
- L451 _protected member_ `bool bIsInitialized = false;` — set to true when the op is ready to run

#### struct `FIKRetargetOpBase::FCurveData`  
`struct FCurveData`  
_L425-430_
- L427 _public member_ `TArray<FName> Names;`
- L428 _public member_ `TArray<int32> Flags;`
- L429 _public member_ `TArray<FLinearColor> Colors;`

#### class `UIKRetargetOpControllerBase`  
`class UIKRetargetOpControllerBase : public UObject`  
_L466-474_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: This is the base class for defining a custom controller for a given retarget op type. Controllers provide an API for editing ops from blueprint or python. To use a controller: 1. Get a controller by calling UIKRetargeterController::GetOpController(int InOpIndex) 2. Cast the returned UIKRetargetOpControllerBase* to the type of controller used by the op you want to modify. 3. Call the public getter/setters to modify the op as desired NOTE: these controllers are necessary because the op UStructs do not support UFunctions
- L473 _public member_ `FIKRetargetOpSettingsBase* OpSettingsToControl = nullptr;` — the op settings this controller controls

#### class `URetargetOpBase`  
`class URetargetOpBase : public UObject`  
_L483-513_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced by FRetargetOpBase. URetargetOpBase-based ops no longer work, please refactor into the new FRetargetOpBase struct.
- L491 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct)` — this is the deprecation upgrade path for solvers that inherit from UIKRigSolver to convert them to FIKRigSolverBase override this and supply a struct into OutInstancedStruct that derives from FIKRigSolverBase that implements your custom solver.
- L493 _public function_ `virtual bool Initialize( const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, FIKRigLogger& Log)`
- L498 _public function_ `virtual void Run( const FIKRetargetProcessor& Processor, const TArray<FTransform>& InOutSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose)`
- L504 _public member_ `bool bIsEnabled = true;` — `UPROPERTY()`
- L506 _public member_ `bool bIsInitialized = false;`
- L509 _public function_ `virtual void OnAddedToStack(const UIKRetargeter* Asset)`
- L510 _public function_ `virtual FText GetNiceName() const`
- L511 _public function_ `virtual FText WarningMessage() const`

#### class `URetargetOpStack`  
`class URetargetOpStack : public UObject`  
_L517-525_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type is no longer in use except to load old stacks of UObject-based ops.
- L524 _public member_ `TArray<TObjectPtr<URetargetOpBase>> RetargetOps_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetOverrideManager.h` (Public)


#### struct `FIKRetargetRuntimeOverrideManager`  
`struct FIKRetargetRuntimeOverrideManager`  
_L10-99_
- L25 _public function_ `friend uint32 GetTypeHash(const FOpOverridesKey& Key)`
- L71 _public prototype_ `void ApplyPropertyOverridesToOps( FIKRetargetProcessor& Processor, const TArrayView<const FName> InOverrideSetsToApply, FInstancedPropertyBag* InVariables, TMap<FName, float>* InBoundCurveValues);`
- L77 _public function_ `void DirtyProfileCache()`
- L81 _private prototype_ `static void DebugPrintVariables(FInstancedPropertyBag* InVariables);`
- L83 _private prototype_ `void UpdateCachedValues(FIKRetargetProcessor& Processor);`
- L85 _private prototype_ `void UpdateFullListOfOverrideSets(FIKRetargetProcessor& Processor, const TArrayView<const FName> InOverrideSetsToApply);`
- L87 _private prototype_ `void RebuildCache(FIKRetargetProcessor& Processor, FInstancedPropertyBag* InVariables);`
- L89 _private prototype_ `static uint32 GetOverrideSetArrayHash(const TArray<FName>& InProfileNames);`
- L91 _private member_ `TArray<FName> OverrideSetsToApply;`
- L92 _private member_ `TArray<uint8> CachedValuePool;`
- L93 _private member_ `TArray<FCompiledPropertyOverride> CompiledOverrides;`
- L94 _private member_ `TMap<FOpOverridesKey, int32> CachedVersionPerOp;`
- L96 _private member_ `int32 CachedAssetVersion;`
- L97 _private member_ `uint32 OverrideSetHash;`
- L98 _private member_ `bool bIsCacheDirty = true;`

#### struct `FIKRetargetRuntimeOverrideManager::FOpOverridesKey`  
`struct FOpOverridesKey`  
_L12-30_
- L14 _public member_ `FName OverrideSetName;`
- L15 _public member_ `FName OpName;`
- L17 _public prototype_ `FOpOverridesKey() = default;`
- L18 _public function_ `FOpOverridesKey(FName ProfileName, FName OpName) : OverrideSetName(ProfileName), OpName(OpName)`
- L20 _public function_ `bool operator==(const FOpOverridesKey& Other) const`

#### enum `FIKRetargetRuntimeOverrideManager::ECurveCoercionType`  
`enum class ECurveCoercionType : uint8`  
_L33-42_
- desc: fast cache for safe numeric casting in the hot path
- L35 _public enumerator_ `None`
- L36 _public enumerator_ `Bool`
- L37 _public enumerator_ `Float`
- L38 _public enumerator_ `Double`
- L39 _public enumerator_ `Int32`
- L40 _public enumerator_ `Int64`
- L41 _public enumerator_ `Byte`

#### enum `FIKRetargetRuntimeOverrideManager::EVariableCoercionType`  
`enum class EVariableCoercionType : uint8`  
_L45-51_
- desc: coercion type for variable bindings when PropertyBag type differs from op settings type
- L47 _public enumerator_ `None` — no variable bound
- L48 _public enumerator_ `Direct` — same size, raw memcpy
- L49 _public enumerator_ `FloatToDouble` — PropertyBag float (4 bytes) -> op settings double (8 bytes)
- L50 _public enumerator_ `DoubleToFloat` — PropertyBag double (8 bytes) -> op settings float (4 bytes)

#### struct `FIKRetargetRuntimeOverrideManager::FCompiledPropertyOverride`  
`struct FCompiledPropertyOverride`  
_L53-69_
- L55 _public member_ `int32 SourcePoolOffset = INDEX_NONE;` — offset into CachedValuePool (if hardcoded)
- L56 _public member_ `int32 BagMemoryOffset = INDEX_NONE;` — offset into FInstancedPropertyBag memory (if bound to var)
- L58 _public member_ `FName BoundCurveName = NAME_None;` — name of the curve (if bound to curve)
- L59 _public member_ `ECurveCoercionType CurveCoercionType = ECurveCoercionType::None;` — the target type for curve casting
- L60 _public member_ `EVariableCoercionType VarCoercionType = EVariableCoercionType::None;` — coercion for variable binding
- L62 _public member_ `void* DestPtr = nullptr;` — pointer to processor op settings memory
- L63 _public member_ `int32 Size = 0;` — size of the property data
- L66 _public member_ `FOpOverridesKey OpOverrideKey;` — value cache invalidate/update stuff
- L67 _public member_ `FProperty* Property = nullptr;`
- L68 _public member_ `uint32 PropertyPathHash = 0;`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetOverrides.h` (Public)


#### class `FPropertyPathParser`  
`class FPropertyPathParser`  
_L17-30_
- desc: A centralized utility for parsing a property path string Intended for property path strings with properties separated by "->" with support for array syntax like "[0]"
- L29 _public prototype_ `static TArray<FPropertyPathStep> ParsePath(const FString& InPath);`

#### struct `FPropertyPathParser::FPropertyPathStep`  
`struct FPropertyPathStep`  
_L21-27_
- L23 _public member_ `FString PropertyName;`
- L24 _public member_ `int32 ArrayIndex = INDEX_NONE;`
- L26 _public function_ `bool IsArray() const`

#### struct `FRetargetPropertyOverrideNode`  
`struct FRetargetPropertyOverrideNode: public TSharedFromThis<FRetargetPropertyOverrideNode>`  
_L42-64_
- inherits: `TSharedFromThis<FRetargetPropertyOverrideNode>`
- desc: What is this for? This type is used to store a customized property tree that ops can supply to tell outside systems which of the op's settings can be overridden. For example, virtual FIKRetargetOpBase::GetOverrideableProperties() takes a root node and allows the op to add a hierarchy of nodes underneath it with customized labels. This allows ops to tell UI code how to group and organize setting overrides. Why not FPropertyNode? 1. FPropertyNode is an editor-only type and we do not want to link Slate 2. This type adds support for custom group labels
- L45 _public member_ `FName NodeName;` — the name of this submenu (e.g., "Settings" or "IKGoal")
- L48 _public member_ `TMap<FName, TSharedPtr<FRetargetPropertyOverrideNode>> SubNodes;` — sub-menus under this one
- L56 _public member_ `TArray<FRetargetPropertyOverrideEntry> LeafProperties;`
- L63 _public prototype_ `void AddPropertiesFromStruct(const UScriptStruct* InStruct, const uint8* InStructData, FString PathPrefix);` — helper to populate this node with properties from a specific struct. @param InStruct The struct type to reflect. @param InStructData pointer to the struct instance (needed for dynamic content like array elements) @param PathPrefix The string path leading to this struct (e.g., "Chains[0]")

#### struct `FRetargetPropertyOverrideNode::FRetargetPropertyOverrideEntry`  
`struct FRetargetPropertyOverrideEntry`  
_L51-55_
- desc: the actual leaf properties in this specific section
- L53 _public member_ `FText DisplayName;`
- L54 _public member_ `FString PropertyPath;`

#### struct `FRetargetOpPropertyOverride`  
`struct FRetargetOpPropertyOverride`  
_L69-154_
- reflection: `USTRUCT()`
- desc: Single property override for a retarget op
- L73 _public prototype_ `FRetargetOpPropertyOverride() = default;`
- L74 _public function_ `FRetargetOpPropertyOverride(const FString& InPropertyPath) : PropertyPath(InPropertyPath)`
- L80 _public function_ `const FString& GetPropertyPath() const` — get access to the path to this property
- L82 _public function_ `const FString& GetValueString() const` — get read-only access to the value of this override as a string
- L84 _public function_ `FString& GetValueStringEditable()` — get read/write access to the value of this override as a string
- L86 _public function_ `uint32 GetPropertyPathHash() const` — get the hash of the property path (cached at construction)
- L90 _public function_ `void SetBoundVariableName(const FName InVariableName)` — set the name of the variable to bind to this property NOTE: this must go through the retargeter controller
- L91 _public function_ `FName GetBoundVariableName() const`
- L95 _public function_ `void SetBoundCurveName(const FName InCurveName)` — set the name of the curve to bind to this property NOTE: this must go through the retargeter controller
- L96 _public function_ `FName GetBoundCurveName() const`
- L99 _public prototype_ `bool IsValid(const UScriptStruct* InSettingsStruct) const;` — validate that this property exists and is accessible
- L102 _public prototype_ `static bool IsStructPropertyAtDefault(const UScriptStruct* InStruct, uint8* InStructData, const FString& InPropertyPath);` — return true if the given property path is at the default value
- L111 _public prototype_ `static bool GetSegmentsFromProperyPath( const FString& InPath, const UScriptStruct* InOwnerStruct, TArray<FPropertySegment>& OutSegments);` — parse a property path string into segments
- L117 _public prototype_ `static uint8* GetDataPointerFromPathSegments( uint8* InStructPtr, const TArray<FPropertySegment>& InSegments, bool bResizeArrays = false);` — navigate from a struct pointer to the final property pointer
- L123 _public prototype_ `static FProperty* GetLeafProperty(const TArray<FPropertySegment>& InSegments);` — get the leaf property from the segment chain
- L126 _public prototype_ `static FProperty* FindProperty( const UStruct* InStruct, const FString& InNameOrDisplayName);` — find a property by name with redirect support
- L131 _public function_ `static FName GetPropertyPathName()` — reflection indirection because these are private
- L132 _public function_ `static FName GetValeAsStringName()`
- L139 _private member_ `FString PropertyPath;` — `UPROPERTY(EditAnywhere, Category=Override)` — property path using "->" separator like, "IKGoalSettings->BlendAlpha" and array syntax like, "Chains[0]->Weight" NOTE: this allows generic serialization of property overrides
- L141 _private member_ `uint32 PropertyPathHash = 0;` — `UPROPERTY()`
- L145 _private member_ `FString ValueAsString;` — `UPROPERTY(EditAnywhere, Category=Override)` — Value serialized as string
- L149 _private member_ `FName BoundVariableName = NAME_None;` — `UPROPERTY()` — The name of the variable this override is bound to, if any.
- L153 _private member_ `FName BoundCurveName = NAME_None;` — `UPROPERTY()` — The name of the curve this override is bound to, if any.

#### struct `FRetargetOpPropertyOverride::FPropertySegment`  
`struct FPropertySegment`  
_L104-108_
- L106 _public member_ `TWeakFieldPtr<FProperty> Property;`
- L107 _public member_ `int32 ArrayIndex = INDEX_NONE;`

#### struct `FRetargetOpOverrides`  
`struct FRetargetOpOverrides`  
_L158-217_
- reflection: `USTRUCT()`
- desc: A collection of property overrides to assign to a single op.
- L164 _public member_ `FName OpName = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Override)` — the retarget op to apply these overrides to
- L168 _public member_ `TArray<FRetargetOpPropertyOverride> PropertyOverrides;` — `UPROPERTY(EditAnywhere, Category=Override)` — the individual property-level overrides for this op
- L172 _public member_ `TObjectPtr<UScriptStruct> ScriptStruct;` — `UPROPERTY(EditAnywhere, Category=Override)` — the reflection data for the struct
- L181 _public prototype_ `bool AddPropertyOverride(const FString& InPropertyPath, const uint8* InSettingsPtr, const UScriptStruct* InSettingsStruct, bool bRequiresReinit);` — registers a new property override for this operation. @param InPropertyPath    The string path to the property (e.g., "Settings->Alpha"). @param InSettingsPtr     Pointer to the memory block containing the source value. @param InSettingsStruct  The reflection data (UScriptStruct) for the settings type. @param bRequiresReinit   True if applying this property at runtime requires a full op re-initialization. @return True if the override was successfully added.
- L187 _public prototype_ `bool RemovePropertyOverride(const FString& InPropertyPath);` — Removes an existing property override based on its path. @param InPropertyPath    The string path of the override to remove. @return True if a matching override was found and removed.
- L195 _public prototype_ `bool UpdateOverrideValue(FRetargetOpPropertyOverride& InPropertyOverride, const uint8* InStructData, const UScriptStruct* InScriptStruct);` — updates the serialized value of an existing property override. @param InPropertyOverride	The override to update. @param InStructData			Pointer to the memory block containing the new value. @param InScriptStruct		The reflection data (UScriptStruct) for the settings type. @return True if the value was updated, false if no matching override exists.
- L198 _public prototype_ `bool HasPropertyOverride(const FString& InPropertyPath) const;` — @return True if an overrides with the given property path exists in this op profile
- L204 _public prototype_ `FRetargetOpPropertyOverride* FindPropertyOverride(const FString& InPropertyPath);` — attempts to locate a specific property override by its path. @param InPropertyPath    The string path to search for. @return A pointer to the override data if found, otherwise nullptr.
- L208 _public prototype_ `int32 GetNumPropertyOverrides() const;` — returns the total count of properties currently overridden for this operation.
- L211 _public function_ `int32 GetValueVersion() const` — Get the version of the values stored for this op (incremented on edit)
- L216 _private member_ `uint32 Version = 0;` — incremented whenever override values change, used to update the runtime cache value

#### struct `FRetargetOverrideSet`  
`struct FRetargetOverrideSet`  
_L220-246_
- reflection: `USTRUCT()`
- L226 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category=Override)` — the label for this set of overrides.
- L230 _public member_ `FName ParentName;` — `UPROPERTY(EditAnywhere, Category=Override)` — used to organize override sets hierarchically
- L234 _public member_ `TArray<FRetargetOpOverrides> OpOverrides;` — `UPROPERTY(EditAnywhere, Category=Override)` — a collection of sparse property value overrides for ops in the stack.
- L238 _public member_ `bool bActiveByDefault = false;` — `UPROPERTY(EditAnywhere, Category=Override)` — allow an override set to be active by default
- L242 _public member_ `int32 DisplayOrder = 0;` — `UPROPERTY()` — Display order for sorting among sibling override sets in the editor tree view
- L245 _public prototype_ `FRetargetOpOverrides* FindOpOverrideByOpName(const FName InOpName);` — get an op override by the op name

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetProcessor.h` (Public)


#### struct `FRetargetPoseScaleWithPivot`  
`struct FRetargetPoseScaleWithPivot`  
_L37-51_
- L39 _public prototype_ `FRetargetPoseScaleWithPivot() = default;`
- L40 _public function_ `FRetargetPoseScaleWithPivot(const double InFactor, const FVector& InPivot) : Factor(InFactor), Pivot(InPivot)`
- L42 _public function_ `bool operator==(const FRetargetPoseScaleWithPivot& Other) const`
- L47 _public prototype_ `bool ScalePose(TArray<FTransform>& InOutGlobalPose) const;`
- L49 _public member_ `double Factor = 1.0;`
- L50 _public member_ `FVector Pivot = FVector::ZeroVector;`

#### struct `FResolvedRetargetPose`  
`struct FResolvedRetargetPose`  
_L54-64_
- desc: cached retarget pose transforms (both local and global) after it has been applied/resolved on a specific skeletal mesh
- L56 _public function_ `FResolvedRetargetPose(const FName InName) : Name(InName)`
- L58 _public member_ `FName Name;` — the name of the retarget pose this was initialized with
- L59 _public member_ `int32 Version;` — the version of the retarget pose this was initialized with (transient)
- L60 _public member_ `FRetargetPoseScaleWithPivot PoseScale;` — the scale of the retarget pose this was initialized with (transient)
- L62 _public member_ `TArray<FTransform> LocalPose;` — local space retarget pose
- L63 _public member_ `TArray<FTransform> GlobalPose;` — global space retarget pose

#### struct `FResolvedRetargetPoseSet`  
`struct FResolvedRetargetPoseSet`  
_L67-93_
- desc: the set of all resolved/cached retarget poses in use for a source or target skeleton
- L69 _public member_ `FName CurrentRetargetPoseName;`
- L70 _public member_ `TArray<FResolvedRetargetPose> RetargetPoses;` — all the retarget poses resolved on the target skeleton
- L72 _public prototype_ `FResolvedRetargetPose& AddOrUpdateRetargetPose( const FRetargetSkeleton& InSkeleton, const FName InRetargetPoseName, const FIKRetargetPose* InRetargetPose, const FName PelvisBoneName, const FRetargetPoseScaleWithPivot& InSourceScale);`
- L79 _public prototype_ `const FResolvedRetargetPose* FindRetargetPoseByName(const FName InRetargetPoseName) const;`
- L81 _public prototype_ `FResolvedRetargetPose& FindOrAddRetargetPose(const FName InRetargetPoseName);`
- L83 _public prototype_ `const TArray<FTransform>& GetLocalRetargetPose() const;`
- L85 _public prototype_ `const TArray<FTransform>& GetGlobalRetargetPose() const;`
- L87 _public prototype_ `FTransform GetGlobalRetargetPoseOfSingleBone( const FRetargetSkeleton& InSkeleton, const int32 BoneIndex, const TArray<FTransform>& InGlobalPose) const;`
- L92 _public prototype_ `void Reset();`

#### struct `FRetargetSkeleton`  
`struct FRetargetSkeleton`  
_L103-176_
- desc: A retarget skeleton contains: 1. hierarchy data (bones, parents) 2. a retarget pose 3. functions for converting Local/Global poses A retarget skeleton is created for both the source and target skeleton. The target skeleton uses a specialized skeleton subclass for managing a bone mask of retargeted bones
- L105 _public member_ `TArray<FName> BoneNames;` — list of all bone names in ref skeleton order
- L106 _public member_ `TArray<int32> ParentIndices;` — per-bone indices of parent bones (the hierarchy)
- L107 _public member_ `FResolvedRetargetPoseSet RetargetPoses;` — the set of cached retarget poses
- L108 _public member_ `const USkeletalMesh* SkeletalMesh;` — the skeletal mesh this was initialized with
- L110 _public prototype_ `void Initialize( const USkeletalMesh* InSkeletalMesh, const ERetargetSourceOrTarget InSourceOrTarget, const UIKRetargeter* InRetargetAsset, const FName PelvisBoneName, const FRetargetPoseScaleWithPivot& InPoseScale);`
- L117 _public prototype_ `void Reset();`
- L119 _public prototype_ `int32 FindBoneIndexByName(const FName InName) const;`
- L121 _public prototype_ `int32 GetParentIndex(const int32 BoneIndex) const;`
- L123 _public prototype_ `const FTransform& GetParentTransform(const int32 BoneIndex, const TArray<FTransform>& InPose) const;`
- L125 _public prototype_ `void UpdateGlobalTransformsBelowBone( const int32 StartBoneIndex, const TArray<FTransform>& InLocalPose, TArray<FTransform>& OutGlobalPose) const;`
- L130 _public prototype_ `void SetGlobalTransformAndUpdateChildren( const int32 InBoneToSetIndex, const FTransform& NewTransform, TArray<FTransform>& InOutGlobalPose) const;`
- L135 _public prototype_ `void UpdateLocalTransformsBelowBone( const int32 StartBoneIndex, TArray<FTransform>& OutLocalPose, const TArray<FTransform>& InGlobalPose) const;`
- L140 _public prototype_ `void UpdateGlobalTransformOfSingleBone( const int32 BoneIndex, const FTransform& InLocalTransform, TArray<FTransform>& OutGlobalPose) const;`
- L145 _public prototype_ `void UpdateLocalTransformOfSingleBone( const int32 BoneIndex, TArray<FTransform>& OutLocalPose, const TArray<FTransform>& InGlobalPose) const;`
- L150 _public prototype_ `FTransform GetLocalTransformOfSingleBone( const int32 BoneIndex, const TArray<FTransform>& InGlobalPose) const;`
- L154 _public prototype_ `TArray<FTransform> GetLocalTransformsOfMultipleBones( const TArray<int32>& InBoneIndices, const TArray<FTransform>& InGlobalPose) const;`
- L158 _public prototype_ `void UpdateGlobalTransformsOfMultipleBones( const TArray<int32>& InBoneIndices, const TArray<FTransform>& InLocalTransforms, TArray<FTransform>& OutGlobalPose) const;`
- L163 _public prototype_ `int32 GetCachedEndOfBranchIndex(const int32 InBoneIndex) const;`
- L165 _public prototype_ `void GetChildrenIndices(const int32 BoneIndex, TArray<int32>& OutChildren) const;`
- L167 _public prototype_ `void GetChildrenIndicesRecursive(const int32 BoneIndex, TArray<int32>& OutChildren) const;`
- L169 _public prototype_ `bool IsParentOf(const int32 PotentialParentIndex, const int32 ChildBoneIndex) const;`
- L175 _private member_ `mutable TArray<int32> CachedEndOfBranchIndices;` — One index per-bone. Lazy-filled on request. Stores the last element of the branch below the bone. You can iterate between in the indices stored here and the bone in question to iterate over all children recursively

#### struct `FTargetSkeleton`  
`struct FTargetSkeleton : public FRetargetSkeleton`  
_L182-209_
- inherits: `FRetargetSkeleton`
- desc: A retarget skeleton for the target skeleton. Contains the output pose buffer for the target skeleton Provides a per-bone mask specifying which bones are retargeted.
- L184 _public member_ `TArray<FTransform> OutputGlobalPose;`
- L185 _public member_ `TArray<FTransform> InputLocalPose;`
- L187 _public prototype_ `void Initialize( const USkeletalMesh* InSkeletalMesh, const ERetargetSourceOrTarget InSourceOrTarget, const UIKRetargeter* InRetargetAsset, const FName RetargetRootBone, const FRetargetPoseScaleWithPivot& InPoseScale);`
- L194 _public prototype_ `void Reset();`
- L196 _public prototype_ `void SetRetargetedBones(const TSet<int32>& InRetargetedBones);`
- L198 _public prototype_ `bool GetIsBoneRetargeted(int32 InBoneIndex) const;`
- L200 _public prototype_ `const TArray<bool>& GetRetargetedBonesMask() const;`
- L207 _private member_ `bool bIsMaskInitialized = false;` — a boolean mask with size NumBones, with value of "true" for any bone that is retargeted ie, bones that are actually posed based on a mapped source chain NOTE: this mask is only available in Op::PostInitialize()... it is built AFTER Op::Initialize()
- L208 _private member_ `TArray<bool> IsBoneRetargeted;`

#### struct `FResolvedBoneChain`  
`struct FResolvedBoneChain`  
_L219-286_
- desc: A "resolved" bone chain serves a few purposes: 1. takes the Start/End bone names from the IK Rig and converts them into a list of bone indices on the skeletal mesh 2. stores Local/Global ref pose of the chain 3. provides facilities to generate local/global poses of the chain 4. parameterizes the chain allowing you to GetTransformAtChainParam() The intention with this data structure is to provide read-only chain data for ops to work with as they need.
- L221 _public prototype_ `FResolvedBoneChain( const FBoneChain& InBoneChain, const FRetargetSkeleton& InSkeleton, FIKRigLogger& InLog);`
- L226 _public prototype_ `bool IsValid() const;`
- L228 _public prototype_ `void UpdatePoseFromSkeleton(const FRetargetSkeleton& InSkeleton);`
- L230 _public prototype_ `void GetWarnings( const FRetargetSkeleton& Skeleton, FIKRigLogger& Log) const;`
- L232 _public prototype_ `FTransform GetTransformAtChainParam( const TArray<FTransform>& Transforms, const double& Param) const;`
- L236 _public prototype_ `double GetStretchAtParam( const TArray<FTransform>& InitialTransforms, const TArray<FTransform>& CurrentTransforms, const double& Param) const;`
- L241 _public prototype_ `int32 GetBoneClosestToParam(const double& Param) const;`
- L243 _public prototype_ `int32 GetBoneAtParam(const double& Param) const;`
- L245 _public prototype_ `int32 GetEquivalentBoneInOtherChain(const int32 InChainIndex, const FResolvedBoneChain& InOtherBoneChain) const;`
- L247 _public prototype_ `static double GetChainLength(const TArray<FTransform>& Transforms);`
- L249 _public prototype_ `static void FillTransformsWithLocalSpaceOfChain( const FRetargetSkeleton& Skeleton, const TArray<FTransform>& InGlobalPose, const TArray<int32>& BoneIndices, TArray<FTransform>& OutLocalTransforms);`
- L255 _public prototype_ `static void FillTransformsWithGlobalRetargetPoseOfChain( const FRetargetSkeleton& Skeleton, const TArray<FTransform>& InGlobalPose, const TArray<int32>& BoneIndices, TArray<FTransform>& OutGlobalTransforms);`
- L261 _public prototype_ `TArray<FTransform> GetChainTransformsFromPose(const TArray<FTransform>& InPose) const;`
- L263 _public member_ `FName ChainName;`
- L264 _public member_ `FName StartBone;`
- L265 _public member_ `FName EndBone;`
- L266 _public member_ `FName IKGoalName;`
- L268 _public member_ `TArray<FTransform> RefPoseGlobalTransforms;`
- L269 _public member_ `TArray<FTransform> RefPoseLocalTransforms;`
- L270 _public member_ `mutable TArray<FTransform> CurrentLocalTransforms;` — reusable scratch space when op needs it
- L272 _public member_ `TArray<float> Params;`
- L273 _public member_ `TArray<int32> BoneIndices;`
- L274 _public member_ `float InitialChainLength;`
- L276 _public member_ `int32 ChainParentBoneIndex;`
- L277 _public member_ `FTransform ChainParentInitialGlobalTransform;`
- L281 _private member_ `bool bFoundStartBone = false;`
- L282 _private member_ `bool bFoundEndBone = false;`
- L283 _private member_ `bool bEndIsStartOrChildOfStart = false;`
- L285 _private prototype_ `void CalculateBoneParameters(FIKRigLogger& Log);`

#### struct `FRetargeterBoneChains`  
`struct FRetargeterBoneChains`  
_L290-339_
- desc: a container for ALL the fully resolved bone chains on both the source and target skeletons, as well as the mapping between them
- L293 _public prototype_ `bool Initialize( const UIKRetargeter* InRetargetAsset, const TArray<const UIKRigDefinition*>& InTargetIKRigs, const FRetargetSkeleton& InSourceSkeleton, const FRetargetSkeleton& InTargetSkeleton, FIKRigLogger& InLog);` — Load all chains from the IK Rigs and resolved them on the current skeletal meshes
- L302 _public prototype_ `const TArray<FResolvedBoneChain>* GetResolvedBoneChains( ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* TargetIKRig = nullptr) const;` — Get read only access to the resolved bone chains on either the source or the target If asking for a target chain, must supply the IK Rig it belongs to
- L307 _public prototype_ `const TMap<const UIKRigDefinition*, TArray<FResolvedBoneChain>>& GetAllResolvedTargetBoneChains() const;` — Get read only access to all resolved bone chains, for all IK Rigs used on the target
- L311 _public prototype_ `const FResolvedBoneChain* GetResolvedBoneChainByName( const FName InChainName, const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* TargetIKRig = nullptr) const;` — Get a fully resolved bone chain by name If asking for a target chain, must supply the IK Rig it belongs to.
- L317 _public prototype_ `void UpdatePoseFromSkeleton( const FRetargetSkeleton& InSkeleton, const ERetargetSourceOrTarget SourceOrTarget);` — Update all transforms stored in the chains. This is needed whenever the retarget pose is modified
- L322 _public prototype_ `TSet<FName> GetChainsThatContainBone(int32 InBoneIndex, ERetargetSourceOrTarget SourceOrTarget) const;` — Get a list of all chains that contain the bone with the given index
- L325 _public prototype_ `void Reset();` — Reset everything (between initializations)
- L330 _private member_ `TArray<FResolvedBoneChain> SourceBoneChains;` — All resolved chains on the source mesh
- L333 _private member_ `TMap<const UIKRigDefinition*, TArray<FResolvedBoneChain>> TargetBoneChains;` — All resolved chains on the target mesh for each IK Rig used by the ops
- L336 _private member_ `const UIKRigDefinition* DefaultTargetIKRig;` — the default IK Rig
- L338 _private member_ `bool bIsInitialized = false;`

#### enum `ERetargetBoneSpace`  
`enum class ERetargetBoneSpace : uint8`  
_L341-345_
- L343 _public enumerator_ `Global`
- L344 _public enumerator_ `Local`

#### enum `ERetargetOpsToSearch`  
`enum class ERetargetOpsToSearch : uint8`  
_L347-351_
- L349 _public enumerator_ `ProcessorOps`
- L350 _public enumerator_ `AssetOps`

#### struct `FRetargetInitParameters`  
`struct FRetargetInitParameters`  
_L357-369_
- desc: Parameters for initializing the IK Retargeter. Initialization does a lot of validation and can fail for many reasons. Check IsInitialized() afterwards.
- L360 _public member_ `const USkeletalMesh* SourceSkeletalMesh = nullptr;` — The skeletal mesh to pose FROM
- L362 _public member_ `const USkeletalMesh* TargetSkeletalMesh = nullptr;` — The skeletal mesh to pose TO
- L364 _public member_ `const UIKRetargeter* RetargeterAsset = nullptr;` — The source asset to use for retargeting settings
- L366 _public member_ `const FRetargetProfile* CustomProfile = nullptr;` — The collection of settings used to initialize with
- L368 _public member_ `bool bSuppressWarnings = false;` — If true, will not output warnings during initialization

#### struct `FRetargetRunParameters`  
`struct FRetargetRunParameters`  
_L372-388_
- desc: Parameters for running the retargeter to generate a new pose.
- L375 _public member_ `TArray<FTransform>* SourceGlobalPose = nullptr;` — The source mesh input pose in Component/Global space
- L377 _public member_ `const FRetargetProfile* Profile = nullptr;` — The retarget profile to use for this update
- L379 _public member_ `TArrayView<const FName> OverrideSetsToApply;` — An array of override set names stored on the asset to apply
- L381 _public member_ `FInstancedPropertyBag* Variables = nullptr;` — A property bag housing variable values that may be bound to overrides
- L383 _public member_ `TMap<FName, float>* BoundCurveValues = nullptr;` — A map of curve names to float values for any curves bound to an override
- L385 _public member_ `float DeltaTime = 0.0f;` — Time since last tick in seconds (passed to ops)
- L387 _public member_ `int32 LOD = INDEX_NONE;` — The current LOD level for the skeletal mesh

#### struct `FIKRetargetProcessor`  
`struct FIKRetargetProcessor`  
_L397-682_
- desc: The runtime processor that converts an input pose from a source skeleton into an output pose on a target skeleton. To use: 1. Initialize a processor with a Source/Target skeletal mesh and a UIKRetargeter asset. 2. Call ScaleSourcePose() and pass in the global space source pose (see func comments why this is necessary) 3. Call RunRetargeter and pass in a source pose as an array of global-space transforms 3. RunRetargeter() returns an array of global space transforms for the target skeleton.
- L406 _public prototype_ `void Initialize(const FRetargetInitParameters& Params);` — Initialize the retargeter to enable running it. @param Params - The initialization settings and source/target skeletons.
- L413 _public prototype_ `TArray<FTransform>& RunRetargeter(const FRetargetRunParameters& Params);` — Run the retarget to generate a new pose. @param Params - The input pose and runtime configuration. @return The retargeted Component/Global space pose for the target skeleton
- L416 _public prototype_ `bool IsInitialized() const;` — Get whether this processor is ready to call RunRetargeter() and generate new poses.
- L419 _public prototype_ `void SetNeedsInitialized();` — Set that this processor needs to be reinitialized.
- L422 _public prototype_ `bool WasInitializedWithTheseAssets( const USkeletalMesh* InSourceMesh, const USkeletalMesh* InTargetMesh, const UIKRetargeter* InRetargetAsset) const;` — Get whether this processor was initialized with these skeletal meshes and retarget asset
- L429 _public prototype_ `void UpdateRetargetPoseAtRuntime(const FName RetargetPoseToUseName, ERetargetSourceOrTarget SourceOrTarget);` — Does a partial reinitialization (at runtime) whenever the retarget pose is swapped to a different or if the pose has been modified. Does nothing if the pose has not changed.
- L432 _public prototype_ `const FRetargetSkeleton& GetSkeleton(ERetargetSourceOrTarget SourceOrTarget) const;` — Get read-only access to either source or target skeleton.
- L436 _public prototype_ `FTargetSkeleton& GetTargetSkeleton();` — Get read/write access to the target skeleton. NOTE: this skeleton contains the output pose of the target skeleton
- L437 _public prototype_ `const FTargetSkeleton& GetTargetSkeleton() const;`
- L440 _public function_ `const FRetargeterBoneChains& GetBoneChains() const` — Get read-only access to all the fully resolved bone chains for both source and target skeletons
- L445 _public function_ `FIKRigGoalContainer& GetIKRigGoalContainer()` — Get read-write access so that ops can modify the IK Rig goals NOTE: pointers to goals in the container are not stable between updates, do not store them. NOTE: any op that sets a goal position must also specify the space of the goal (they are all additive by default)
- L446 _public function_ `const FIKRigGoalContainer& GetIKRigGoalContainer() const`
- L449 _public function_ `const TArray<FInstancedStruct>& GetRetargetOps() const` — Get read only access to the retarget ops currently running in processor
- L452 _public prototype_ `TArray<const FIKRetargetOpBase*> GetRetargetOpsByType(const UScriptStruct* OpType) const;` — Get list of ops of a given type
- L455 _public prototype_ `FIKRetargetOpBase* GetRetargetOpByName(const FName InOpName);` — Get an op with the given name
- L459 _public function_ `template <typename T> const T* GetFirstRetargetOpOfType(ERetargetOpsToSearch SourceOfOps = ERetargetOpsToSearch::ProcessorOps) const` — Get the first op in the stack of the given type
- L489 _public function_ `bool IsIKForcedOff() const` — Returns true if the IK has not been forced off
- L492 _public function_ `const UIKRetargeter* GetRetargetAsset() const` — Get read only access to the retarget asset
- L495 _public prototype_ `void OnPlaybackReset();` — Calls OnPlaybackReset() for all ops in the stack
- L498 _public prototype_ `void OnAnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent);` — Calls AnimGraphPreUpdateMainThread() for all ops in the stack
- L501 _public prototype_ `void OnAnimGraphEvaluateAnyThread(FPoseContext& Output);` — Calls AnimGraphEvaluateAnyThread() for all ops in the stack
- L504 _public prototype_ `FName GetPelvisBone(ERetargetSourceOrTarget SourceOrTarget, ERetargetOpsToSearch InOpsToSearch) const;` — Get name of the pelvis bone for either the source or target skeleton.
- L513 _public prototype_ `void ApplySourceScaleToPose(TArray<FTransform>& InOutSourceGlobalPose) const;` — This scales the input source pose according to the source scale factor This must be called outside of the retargeter itself because otherwise the pose may be scaled multiple times. This is because we don't copy the source pose and we don't control when it's updated. By explicitly scaling outside of RunRetargeter(), outside systems can scale it whenever they update it. @param InOutSourceGlobalPose: an array of global space transforms for each bone in the source input pose
- L516 _public prototype_ `double GetSourceScaleFactor() const;` — Get the scale factor for the source pose (comes from presence of SourceScaleOp)
- L519 _public prototype_ `const FRetargetPoseScaleWithPivot& GetPoseScale(const ERetargetSourceOrTarget SourceOrTarget) const;` — Get the scale factor and pivot for the retarget pose (comes from presence of SourceScaleOp)
- L522 _public member_ `FIKRigLogger Log;` — The logging system
- L527 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnRetargeterInitialized);`
- L528 _private member_ `FOnRetargeterInitialized RetargeterInitialized;`
- L531 _public prototype_ `bool IsBoneMapped(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const;` — Returns true if the bone is part of a retarget chain or root bone, false otherwise.
- L533 _public prototype_ `int32 GetBoneIndexFromName(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const;` — Returns index of the bone with the given name in either Source or Target skeleton.
- L535 _public prototype_ `const FRetargeterBoneChains& GetBoneChains();` — Get access to all the fully resolved bone chain data
- L537 _public prototype_ `FName GetFirstChainForBone(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const;` — Returns name of the chain associated with this bone. Returns NAME_None if bone is not in a chain.
- L539 _public prototype_ `TSet<FName> GetAllChainNamesForBone(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const;` — Returns names of all the chains associated with this bone. Returns empty set if bone is not in a chain.
- L541 _public prototype_ `bool GetFirstChainMappingForBone(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget, FName& OutChainContainingBone, FName& OutMappedChain) const;` — get the first mapping that contains the given bone, returns false if no mapping exists
- L543 _public prototype_ `FTransform GetGlobalRetargetPoseAtParam(const FName InChainName, const float Param, const ERetargetSourceOrTarget SourceOrTarget) const;` — Get a transform at a given param in a chain
- L545 _public prototype_ `FTransform GetRetargetPoseBoneTransform(const FName InBoneName, const ERetargetSourceOrTarget SourceOrTarget, ERetargetBoneSpace BoneSpace) const;` — Get a transform of a bone in the retarget pose
- L548 _public prototype_ `float GetParamOfBoneInChain(const FName InBoneName, const ERetargetSourceOrTarget SourceOrTarget, const FName InChain = NAME_None) const;` — Get the param of the bone in it's retarget chain. Ranges from 0 to NumBonesInChain.
- L550 _public prototype_ `FName GetClosestBoneToParam(const FName InChainName, const float InParam, const ERetargetSourceOrTarget SourceOrTarget) const;` — Get the bone in the chain at the given param.
- L552 _public prototype_ `FName GetFirstChainMappedToChain(const FName InChainName, const ERetargetSourceOrTarget InSourceOrTarget) const;` — Get the chain mapped to this one.
- L554 _public function_ `FOnRetargeterInitialized& OnRetargeterInitialized()` — Attach a delegate to be notified whenever this processor is initialized.
- L556 _public prototype_ `void DebugDrawAllOps(FPrimitiveDrawInterface* InPDI, const FIKRetargetDebugDrawState& EditorState) const;` — Run debug drawing on all ops in the stack
- L559 _public prototype_ `void UpdateOpsFromAnimSequence(UAnimSequence* Sequence, float FrameTime);` — Run UpdateFromAnimSequence on all ops
- L565 _public prototype_ `void Initialize( const USkeletalMesh* SourceSkeleton, const USkeletalMesh* TargetSkeleton, const UIKRetargeter* InRetargeterAsset, const FRetargetProfile& InCustomProfile, const bool bSuppressWarnings = false);` — `UE_DEPRECATED(5.8, "Please use the Initialize overload that takes FRetargetInitParameters.")` — BEGIN DEPRECATED API
- L572 _public prototype_ `TArray<FTransform>& RunRetargeter( TArray<FTransform>& InSourceGlobalPose, const FRetargetProfile& InProfile, const float InDeltaTime, const int32 InLOD = -1);` — `UE_DEPRECATED(5.8, "Please use the RunRetargeter overload that takes FRetargetRunParameters.")`
- L583 _private member_ `bool bIKForcedOff = false;` — If true, all IK operations are skipped NOTE: this is used both for debugging and LOD'ing IK off
- L586 _private member_ `bool bIsInitialized = false;` — Only true once Initialize() has successfully completed.
- L587 _private member_ `int32 AssetVersionInitializedWith = -2;`
- L590 _private member_ `const UIKRetargeter* RetargeterAsset = nullptr;` — The source asset this processor was initialized with.
- L593 _private member_ `FRetargetSkeleton SourceSkeleton;` — The internal data structures used to represent the SOURCE skeleton / pose during retargeter.
- L596 _private member_ `FTargetSkeleton TargetSkeleton;` — The internal data structures used to represent the TARGET skeleton / pose during retargeter.
- L599 _private member_ `FIKRigGoalContainer GoalContainer;` — the named transforms that solvers use as end effectors
- L602 _private member_ `FRetargeterBoneChains AllBoneChains;` — Storage for all bone chain data used by Ops and editor tools
- L605 _private member_ `TArray<FInstancedStruct> OpStack;` — The collection of operations to run to transfer animation from source to target.
- L608 _private member_ `FIKRetargetRuntimeOverrideManager OverrideManager;` — Manages the application of stored property overrides at runtime.
- L611 _private member_ `mutable FRetargetPoseScaleWithPivot CurrentSourceScale;` — cached source scaling
- L614 _private prototype_ `void UpdateSettingsAtRuntime( const FRetargetProfile* InProfile, const TArrayView<const FName> InOverrideSetsToApply, FInstancedPropertyBag* InVariables, TMap<FName, float>* InBoundCurveValues);` — Apply the settings stored in a retarget profile. As well as any stored property overrides.
- L621 _private prototype_ `void GenerateBasePoses(TArray<FTransform>& InSourceGlobalPose);` — Internal retarget phase that does simple bone-to-bone copying from source
- L624 _private prototype_ `void InitialOpStackSetup( const TArray<FInstancedStruct>& OpsFromAsset, const FRetargetProfile* InRetargetProfile);` — Initial setup of the retarget op stack (copies op stack from asset into processor)
- L629 _private prototype_ `void InitializeRetargetOps();` — Run Initialize() on all ops then collects retargeted bones and call PostInitialize() on each Op
- L632 _private prototype_ `void RunRetargetOps( const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose, const double InDeltaTime, const int32 InLOD);` — Run all post process operations on the retargeted result.
- L639 _private prototype_ `static bool ShouldExecuteOp(const FIKRetargetOpBase& InOp, int32 InLOD);` — Helper function to determine if an op should run this frame
- L676 _private prototype_ `void BuildExecutionStack(int32 InLOD, TArray<FRetargetOpCall>& OutStack);`
- L678 _private prototype_ `void BuildInitializationStack(TArray<FRetargetOpCall>& OutStack);`
- L680 _private prototype_ `void InitializeOpEntries();`
- L681 _private member_ `TArray<FOpEntry> OpEntries;`

#### struct `FIKRetargetProcessor::FOpEntry`  
`struct FOpEntry`  
_L641-649_
- L643 _public member_ `FIKRetargetOpBase* Op = nullptr;`
- L644 _public member_ `FOpEntry* Parent = nullptr;`
- L645 _public member_ `TArray<FOpEntry*> Children;`
- L647 _public member_ `int32 StackIndex = INDEX_NONE;`
- L648 _public member_ `bool bExecute = false;`

#### enum `FIKRetargetProcessor::ERetargetOpPhase`  
`enum class ERetargetOpPhase : uint8`  
_L651-663_
- L654 _public enumerator_ `InitializeBeforeChildren` — initialization
- L655 _public enumerator_ `Initialize`
- L656 _public enumerator_ `PostInitializeProcessor`
- L657 _public enumerator_ `PostInitializeOp`
- L660 _public enumerator_ `RunBeforeChildren` — runtime
- L661 _public enumerator_ `Run`
- L662 _public enumerator_ `RunAfterParent`

#### struct `FIKRetargetProcessor::FRetargetOpCall`  
`struct FRetargetOpCall`  
_L665-674_
- L667 _public function_ `FRetargetOpCall(const ERetargetOpPhase InPhase, FOpEntry* InOpEntry) : Phase(InPhase), OpEntry(InOpEntry)`
- L668 _public prototype_ `FIKRetargetOpBase* GetOp();`
- L669 _public prototype_ `FIKRetargetOpBase* GetParentOp();`
- L671 _public member_ `ERetargetOpPhase Phase;`
- L673 _private member_ `FOpEntry* OpEntry;`

#### class `UIKRetargetProcessor`  
`UIKRetargetProcessor : public UObject`  
_L694-804_
- reflection: `UCLASS()`
- reflection: `UE_DEPRECATED(5.6, "UIKRetargetProcessor has been replaced by FIKRetargetProcessor. UIKRetargetProcessor is now a thin wrapper around FIKRetargetProcessor and will be removed in a future version.")`
- inherits: `UObject`
- desc: BEGIN DEPRECATED UOBJECT-BASED PROCESSOR NOTE: As of 5.6, IK Retarget processor is no longer a UObject. The UObject based processor is here for backwards compatibility. If you have a system built off this processor, please convert it to the FIKRetargetProcessor as this will be removed in a future update.
- L700 _public function_ `void Initialize( const USkeletalMesh *SourceSkeleton, const USkeletalMesh *TargetSkeleton, const UIKRetargeter* InRetargeterAsset, const FRetargetProfile& Settings, const bool bSuppressWarnings=false)`
- L710 _public function_ `TArray<FTransform>& RunRetargeter( TArray<FTransform>& InSourceGlobalPose, const TMap<FName,float>& SpeedValuesFromCurves, const float DeltaTime, const FRetargetProfile& Profile)`
- L719 _public function_ `void UpdateRetargetPoseAtRuntime( const FName NewRetargetPoseName, ERetargetSourceOrTarget SourceOrTarget)`
- L726 _public function_ `const FRetargetSkeleton& GetSkeleton(ERetargetSourceOrTarget SourceOrTarget) const`
- L730 _public function_ `FName GetRetargetRoot(ERetargetSourceOrTarget SourceOrTarget) const`
- L734 _public function_ `bool IsInitialized() const`
- L738 _public function_ `bool WasInitializedWithTheseAssets( const USkeletalMesh* InSourceMesh, const USkeletalMesh* InTargetMesh, const UIKRetargeter* InRetargetAsset) const`
- L745 _public function_ `const TArray<TObjectPtr<URetargetOpBase>>& GetRetargetOps() const`
- L749 _public function_ `const FRetargetGlobalSettings& GetGlobalSettings() const`
- L753 _public function_ `void ResetPlanting()`
- L757 _public function_ `void SetNeedsInitialized()`
- L762 _public member_ `FIKRigLogger Log;`
- L765 _public function_ `bool IsBoneRetargeted(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const`
- L769 _public function_ `int32 GetBoneIndexFromName(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const`
- L773 _public function_ `FName GetChainNameForBone(const FName BoneName, const ERetargetSourceOrTarget SourceOrTarget) const`
- L777 _public function_ `FTransform GetGlobalRetargetPoseAtParam(const FName InChainName, const float Param, const ERetargetSourceOrTarget SourceOrTarget) const`
- L781 _public function_ `FTransform GetRetargetPoseBoneTransform(const FName InBoneName, const ERetargetSourceOrTarget SourceOrTarget, ERetargetBoneSpace BoneSpace) const`
- L785 _public function_ `float GetParamOfBoneInChain(const FName InBoneName, const ERetargetSourceOrTarget SourceOrTarget) const`
- L789 _public function_ `FName GetClosestBoneToParam(const FName InChainName, const float InParam, const ERetargetSourceOrTarget SourceOrTarget) const`
- L793 _public function_ `FName GetMappedChainName(const FName InChainName, const ERetargetSourceOrTarget SourceOrTarget)`
- L801 _private member_ `FRetargetGlobalSettings DummyGlobalSettings;`
- L802 _private member_ `TArray<TObjectPtr<URetargetOpBase>> DummyStack;`
- L803 _private member_ `FIKRetargetProcessor Processor;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API IKRIG_API`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("IK Retarget Processor Run"), STAT_Anim_RetargetProcessorRun,`
- L527 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnRetargeterInitialized);`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetProfile.h` (Public)


#### enum `ECopyOpSettingsContext`  
`enum class ECopyOpSettingsContext : uint8`  
_L20-24_
- reflection: `UENUM()`
- L22 _public enumerator_ `PreInitialize` — copies ALL settings (used in editor during setup)
- L23 _public enumerator_ `Runtime` — copy only settings that don't require reinitialization

#### struct `FRetargetOpProfile`  
`struct FRetargetOpProfile`  
_L28-75_
- reflection: `USTRUCT(BlueprintType)`
- desc: A wholesale copy of the settings in a retarget op.
- L32 _public prototype_ `FRetargetOpProfile() = default;`
- L34 _public prototype_ `FRetargetOpProfile( const FName InOpName, const UScriptStruct* InSettingsType, const FIKRetargetOpSettingsBase* InOpSettings);`
- L45 _public prototype_ `bool CopySettingsToOp(FInstancedStruct& InOutOpStruct, ECopyOpSettingsContext InApplyContext) const;` — Applies the stored settings from this profile into the provided operation's instance data. @param InOutOpStruct     The destination operation struct to receive these settings. @param InApplyContext    The execution context (e.g., Runtime vs Editor). In Runtime mode, overrides that require reinitialization will be skipped. @return True if the settings were compatible and successfully applied, false otherwise.
- L51 _public prototype_ `void CopyFromOtherOpProfile(const FRetargetOpProfile& OtherOpProfile);` — Duplicates all settings from another op profile. @param OtherOpProfile    The source profile to copy settings data from.
- L57 _public prototype_ `UIKRetargetOpControllerBase* CreateControllerIfNeeded(UObject* Outer);` — Helper utility for operations to instantiate and retrieve their associated controller. @param Outer             The UObject that will own the newly created controller. @return A pointer to the existing or newly created controller base.
- L63 _public member_ `FName OpToApplySettingsTo = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Retarget Op Profile")` — The specific name of the operation in the stack these settings should target. If NAME_None, settings are applied to all operations matching the 'SettingsToApply' type.
- L70 _public member_ `FInstancedStruct SettingsToApply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Retarget Op Profile", meta = (ExcludeBaseStruct, BaseStruct = "/Script/IKRig.IKRetargetOpSettingsBase"))` — The collection of settings to override for a specific operation. Note: While all settings here are applied in the editor, operations independently filter which settings are safe to apply at runtime without re-initializing.
- L74 _private member_ `TStrongObjectPtr<UIKRetargetOpControllerBase> Controller = nullptr;` — the controller used to edit these op settings by script/blueprint (lazy instantiated when needed)

#### struct `FRetargetProfile`  
`struct FRetargetProfile`  
_L79-189_
- reflection: `USTRUCT(BlueprintType)`
- desc: A collection of FRetargetOpProfiles that can be applied at runtime to override settings for one or more ops.
- L87 _public prototype_ `FRetargetProfile() = default;` — implicit copy assignment operator raises deprecation warnings (remove this once the deprecated properties are gone)
- L88 _public prototype_ `FRetargetProfile(const FRetargetProfile&) = default;`
- L89 _public prototype_ `FRetargetProfile(FRetargetProfile&&) = default;`
- L90 _public prototype_ `FRetargetProfile& operator=(const FRetargetProfile&) = default;`
- L91 _public prototype_ `FRetargetProfile& operator=(FRetargetProfile&&) = default;`
- L96 _public member_ `TArray<FRetargetOpProfile> RetargetOpProfiles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — A polymorphic list of override settings to apply to retargeting operations in the stack
- L100 _public member_ `bool bApplyTargetRetargetPose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Retarget Poses", meta = (DisplayName = "Override Target Retarget Pose"))` — If true, the TARGET Retarget Pose specified in this profile will be applied to the Retargeter (when plugged into the Retargeter).
- L105 _public member_ `FName TargetRetargetPoseName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Retarget Poses", meta=(EditCondition="bApplyTargetRetargetPose"))` — Override the TARGET Retarget Pose to use when this profile is active. The pose must be present in the Retarget Asset and is not applied unless bApplyTargetRetargetPose is true.
- L109 _public member_ `bool bApplySourceRetargetPose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Retarget Poses", meta = (DisplayName = "Override Source Retarget Pose"))` — If true, the Source Retarget Pose specified in this profile will be applied to the Retargeter (when plugged into the Retargeter).
- L114 _public member_ `FName SourceRetargetPoseName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Retarget Poses", meta=(EditCondition="bApplySourceRetargetPose"))` — Override the SOURCE Retarget Pose to use when this profile is active. The pose must be present in the Retarget Asset and is not applied unless bApplySourceRetargetPose is true.
- L118 _public member_ `bool bForceAllIKOff = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Retarget Settings", DisplayName="Force All IK Off")` — Globally forces all IK solving off
- L120 _public prototype_ `void FillProfileWithAssetSettings(const UIKRetargeter* InAsset);`
- L122 _public prototype_ `void MergeWithOtherProfile(const FRetargetProfile& OtherProfile);`
- L124 _public prototype_ `FRetargetOpProfile* FindMatchingOpProfile(const FRetargetOpProfile& OtherOpProfile);`
- L126 _public prototype_ `bool ApplyOpProfilesToOpStruct(FInstancedStruct& InOutOpStruct, const ECopyOpSettingsContext InCopyContext) const;`
- L128 _public prototype_ `FRetargetOpProfile* GetOpProfileByName(const FName InOpName);`
- L132 _public function_ `template <typename T> void GetOpSettingsByTypeInProfile(TArray<T*>& OutMatchingOpSettings)` — search all the op profiles and get an array of all the settings of a particular type
- L154 _public prototype_ `void MergeDeprecatedProperties(const FRetargetProfile& OtherProfile);` — consolidating/isolating deprecation code
- L159 _public member_ `bool bApplyChainSettings = false;` — `UE_DEPRECATED(5.6, "Modifying chain settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Apply Chain Settings (Deprecated)"))` — (Deprecated) If true, the Chain Settings stored in this profile will be applied to the Retargeter (when plugged into the Retargeter).
- L164 _public member_ `TMap<FName, FTargetChainSettings> ChainSettings;` — `UE_DEPRECATED(5.6, "Modifying chain settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Chain Settings (Deprecated)"))` — (Deprecated) A (potentially sparse) set of setting overrides for the target chains (only applied when bApplyChainSettings is true).
- L169 _public member_ `bool bApplyRootSettings = false;` — `UE_DEPRECATED(5.6, "Modifying root settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Apply Root Settings (Deprecated)"))` — (Deprecated) If true, the root settings stored in this profile will be applied to the Retargeter (when plugged into the Retargeter).
- L174 _public member_ `FTargetRootSettings RootSettings;` — `UE_DEPRECATED(5.6, "Modifying root settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Root Settings (Deprecated)"))` — (Deprecated) Retarget settings to control behavior of the retarget root motion (not applied unless bApplyRootSettings is true)
- L179 _public member_ `bool bApplyGlobalSettings = false;` — `UE_DEPRECATED(5.6, "Modifying global settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Apply Global Settings (Deprecated)"))` — (Deprecated) If true, the global settings stored in this profile will be applied to the Retargeter (when plugged into the Retargeter).
- L184 _public member_ `FRetargetGlobalSettings GlobalSettings;` — `UE_DEPRECATED(5.6, "Modifying global settings must go through a retarget op profile.")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Deprecated", meta=(DisplayName="Global Settings (Deprecated)"))` — (Deprecated) Retarget settings to control global behavior, like Stride Warping (not applied unless bApplyGlobalSettings is true)

#### class `URetargetProfileLibrary`  
`class URetargetProfileLibrary : public UBlueprintFunctionLibrary`  
_L192-203_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L199 _public prototype_ `static FRetargetProfile CopyRetargetProfileFromRetargetAsset(const UIKRetargeter* InRetargetAsset);` — `UFUNCTION(BlueprintCallable, Category = "Retarget Profile")`
- L202 _public prototype_ `static UIKRetargetOpControllerBase* GetOpControllerFromRetargetProfile(UPARAM(ref) FRetargetProfile& InRetargetProfile, const FName InRetargetOpName);` — `UFUNCTION(BlueprintPure, Category = "Retarget Profile")`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargetSettings.h` (Public)


#### enum `ERetargetSourceOrTarget`  
`enum class ERetargetSourceOrTarget : uint8`  
_L11-17_
- reflection: `UENUM(BlueprintType)`
- desc: which skeleton are we referring to?
- L14 _public enumerator_ `Source` — the SOURCE skeleton (to copy FROM)
- L16 _public enumerator_ `Target` — the TARGET skeleton (to copy TO)

#### enum `EBasicAxis`  
`enum class EBasicAxis`  
_L20-28_
- reflection: `UENUM()`
- L22 _public enumerator_ `X`
- L23 _public enumerator_ `Y`
- L24 _public enumerator_ `Z`
- L25 _public enumerator_ `NegX`
- L26 _public enumerator_ `NegY`
- L27 _public enumerator_ `NegZ`

#### enum `ERetargetSelectionType`  
`enum class ERetargetSelectionType : uint8`  
_L31-39_
- L33 _public enumerator_ `NONE`
- L34 _public enumerator_ `BONE`
- L35 _public enumerator_ `CHAIN`
- L36 _public enumerator_ `MESH`
- L37 _public enumerator_ `ROOT`
- L38 _public enumerator_ `OP`

#### struct `FIKRetargetDebugDrawState`  
`struct FIKRetargetDebugDrawState`  
_L41-65_
- L46 _public member_ `ERetargetSelectionType LastSelectedType = ERetargetSelectionType::NONE;` — what type of objects was last selected?
- L48 _public member_ `bool bIsRootSelected = false;` — BONE
- L49 _public member_ `TMap<ERetargetSourceOrTarget, TArray<FName>> SelectedBoneNames;`
- L51 _public member_ `TArray<FName> SelectedChains;` — CHAINS
- L53 _public member_ `UPrimitiveComponent* SelectedMesh = nullptr;` — MESH
- L55 _public member_ `TArray<FName> SelectedGoals;` — GOALS
- L57 _public member_ `FName LastSelectedOpName;` — OPS
- L60 _public member_ `static FLinearColor Muted;` — common viewport drawing color palette for selected things
- L61 _public member_ `static FLinearColor SourceColor;`
- L62 _public member_ `static FLinearColor GoalColor;`
- L63 _public member_ `static FLinearColor MainColor;`
- L64 _public member_ `static FLinearColor NonSelected;`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/IKRetargeter.h` (Public)


#### struct `FRetargetVariableContainer`  
`struct FRetargetVariableContainer`  
_L23-29_
- reflection: `USTRUCT()`
- L28 _public member_ `FInstancedPropertyBag Bag;` — `UPROPERTY()`

#### struct `FIKRetargetPose`  
`struct FIKRetargetPose`  
_L32-67_
- reflection: `USTRUCT(BlueprintType)`
- L38 _public prototype_ `FIKRetargetPose() = default;`
- L40 _public prototype_ `FQuat GetDeltaRotationForBone(const FName BoneName) const;`
- L41 _public prototype_ `void SetDeltaRotationForBone(FName BoneName, const FQuat& RotationDelta);`
- L42 _public function_ `const TMap<FName, FQuat>& GetAllDeltaRotations() const`
- L44 _public prototype_ `FVector GetRootTranslationDelta() const;`
- L45 _public prototype_ `void SetRootTranslationDelta(const FVector& TranslationDelta);`
- L46 _public prototype_ `void AddToRootTranslationDelta(const FVector& TranslationDelta);`
- L48 _public prototype_ `void SortHierarchically(const FIKRigSkeleton& Skeleton);`
- L50 _public function_ `int32 GetVersion() const`
- L51 _public function_ `void IncrementVersion()`
- L56 _private member_ `FVector RootTranslationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = RetargetPose)` — a translational delta in GLOBAL space, applied only to the pelvis bone
- L60 _private member_ `TMap<FName, FQuat> BoneRotationOffsets;` — `UPROPERTY(EditAnywhere, Category = RetargetPose)` — these are LOCAL-space rotation deltas to be applied to a bone to modify it's retarget pose
- L64 _private member_ `int32 Version = INDEX_NONE;` — incremented by any edits to the retarget pose, indicating to any running instance that it should reinitialize this is not made "editor only" to leave open the possibility of programmatically modifying a retarget pose in cooked builds

#### class `UIKRetargeter`  
`class UIKRetargeter : public UObject`  
_L70-535_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L76 _public prototype_ `UIKRetargeter(const FObjectInitializer& ObjectInitializer);`
- L79 _public prototype_ `const UIKRigDefinition* GetIKRig(ERetargetSourceOrTarget SourceOrTarget) const;` — Get read-only access to the source or target IK Rig asset
- L82 _public prototype_ `UIKRigDefinition* GetIKRigWriteable(ERetargetSourceOrTarget SourceOrTarget) const;` — Get read-write access to the source IK Rig asset. WARNING: do not use for editing the data model. Use Controller class instead.
- L85 _public prototype_ `USkeletalMesh* GetPreviewMesh(ERetargetSourceOrTarget SourceOrTarget) const;` — Get read-only access to preview meshes
- L89 _public function_ `const TArray<FInstancedStruct>& GetRetargetOps() const` — Get access to the stack of retargeting operations
- L92 _public function_ `template <typename T> T* GetFirstRetargetOpOfType()` — Get the first op in the stack of the given type
- L106 _public function_ `template <typename T> TArray<T*> GetAllRetargetOpsOfType()` — Get all ops in the stack of the given type
- L124 _public prototype_ `const FIKRetargetOpBase* GetRetargetOpByName(const FName& InOpName) const;` — Get a retarget op by name
- L127 _public prototype_ `FIKRetargetOpBase* GetRetargetOpByNameNonConst(const FName& InOpName);` — Get a retarget op by name non-const NOTE: be careful with this, general op-editing should be done through a controller
- L129 _public prototype_ `int32 GetIndexOfRetargetOp(const FIKRetargetOpBase* InOp) const;` — Get index of a retarget op
- L131 _public prototype_ `const FIKRetargetPose* GetCurrentRetargetPose(const ERetargetSourceOrTarget& SourceOrTarget) const;` — Get read-only access to a retarget pose
- L133 _public prototype_ `FName GetCurrentRetargetPoseName(const ERetargetSourceOrTarget& SourceOrTarget) const;` — Get name of the current retarget pose
- L135 _public prototype_ `const FIKRetargetPose* GetRetargetPoseByName(const ERetargetSourceOrTarget& SourceOrTarget, const FName PoseName) const;` — Get read-only access to a retarget pose
- L137 _public prototype_ `static const FName GetDefaultPoseName();` — Get name of default pose
- L140 _public prototype_ `const FRetargetProfile* GetCurrentProfile() const;` — Get the current retarget profile (may be null)
- L142 _public prototype_ `const FRetargetProfile* GetProfileByName(const FName& ProfileName) const;` — Get the retarget profile by name (may be null)
- L145 _public function_ `const TMap<FName, FRetargetOverrideSet>& GetOverrideSets() const` — Get read-only access to all the override sets
- L147 _public function_ `TMap<FName, FRetargetOverrideSet>& GetOverrideSetsWriteable()` — Get read-write access to all override sets (caution, all modifications should go through the controller)
- L149 _public prototype_ `const TArray<FName>& GetOverrideSetsToApply() const;` — Get all the override sets that are enabled
- L151 _public prototype_ `const FRetargetOverrideSet* GetOverrideSetByName(const FName& OverrideName) const;` — Get a set of overrides by name (may be null)
- L153 _public function_ `int32 GetOverrideVersion() const` — get current version of the property overrides data (to compare against running processor instances)
- L156 _public function_ `FRetargetVariableContainer& GetVariables()` — get read-write access to the variable bag (caution here, all editing should go through controller)
- L159 _public function_ `int32 GetVersion() const` — get current version of the data (to compare against running processor instances)
- L161 _public function_ `void IncrementVersion() const` — do this after any edit that would require running instance to reinitialize
- L165 _public function_ `bool HasSourceIKRig() const` — `UFUNCTION(BlueprintPure, Category=RetargetProfile)` — Returns true if the source IK Rig has been assigned
- L169 _public function_ `bool HasTargetIKRig() const` — `UFUNCTION(BlueprintPure, Category=RetargetProfile)` — Returns true if the target IK Rig has been assigned
- L172 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;` — UObject
- L173 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L174 _public prototype_ `virtual void PostLoad() override;`
- L177 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L182 _public prototype_ `static const FName GetSourceIKRigPropertyName();` — Get name of Source IK Rig property
- L184 _public prototype_ `static const FName GetTargetIKRigPropertyName();` — Get name of Target IK Rig property
- L186 _public prototype_ `static const FName GetSourcePreviewMeshPropertyName();` — Get name of Source Preview Mesh property
- L188 _public prototype_ `static const FName GetTargetPreviewMeshPropertyName();` — Get name of Target Preview Mesh property
- L204 _public function_ `FRetargetChainMapping& GetChainMapping()` — `UE_DEPRECATED(5.6, "Chain mappings are managed by individual ops now. Use the asset or op controllers to edit them.")` — Get read/write access to the chain mapping
- L208 _public function_ `const FRetargetChainMapping& GetChainMapping() const` — `UE_DEPRECATED(5.6, "Chain mappings are managed by individual ops now. Use Op controllers to edit them.")` — Get read-only access to the chain mapping
- L212 _public function_ `const TArray<TObjectPtr<URetargetChainSettings>>& GetAllChainSettings() const` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op controller.")` — Get read-only access to the per-chain settings
- L216 _public prototype_ `const TObjectPtr<URetargetChainSettings> GetChainMapByName(const FName& TargetChainName) const;` — `UE_DEPRECATED(5.6, "Chain mappings are now accessed from GetChainMapping().")` — Get read-only access to the chain map for a given chain (null if chain not in retargeter)
- L220 _public prototype_ `const FTargetChainSettings* GetChainSettingsByName(const FName& TargetChainName) const;` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op controller.")` — Get read-only access to the chain settings for a given chain (null if chain not in retargeter)
- L224 _public function_ `URetargetRootSettings* GetRootSettingsUObject() const` — `UE_DEPRECATED(5.6, "Root settings are now accessed through a Pelvis Motion Op.")` — Get access to the root settings
- L228 _public function_ `UIKRetargetGlobalSettings* GetGlobalSettingsUObject() const` — `UE_DEPRECATED(5.6, "Global settings are now accessed through various Ops depending on the feature.")` — Get access to the global settings uobject
- L232 _public function_ `const FRetargetGlobalSettings& GetGlobalSettings() const` — `UE_DEPRECATED(5.6, "Global settings are now accessed through various Ops depending on the feature.")` — Get access to the global settings itself
- L237 _public prototype_ `static FTargetChainSettings GetChainUsingGoalFromRetargetAsset( const UIKRetargeter* RetargetAsset, const FName IKGoalName);` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=RetargetAsset, meta = (DeprecatedFunction, DeprecationMessage = "Use IK Chain Op controller to get chains with goals."))` — Returns the chain settings associated with a given Goal in an IK Retargeter Asset using the given profile name (optional)
- L244 _public prototype_ `static FTargetChainSettings GetChainSettingsFromRetargetAsset( const UIKRetargeter* RetargetAsset, const FName TargetChainName, const FName OptionalProfileName);` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=RetargetAsset, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set chain settings."))` — Returns the chain settings associated with a given target chain in an IK Retargeter Asset using the given profile name (optional)
- L252 _public prototype_ `static FTargetChainSettings GetChainSettingsFromRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FName TargetChainName);` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set chain settings."))` — Returns the chain settings associated with a given target chain in the supplied Retarget Profile.
- L267 _public prototype_ `static FTargetRootSettings GetRootSettingsFromRetargetProfile(UPARAM(ref) FRetargetProfile& RetargetProfile);` — `UE_DEPRECATED(5.6, "Root settings are now accessed through a Pelvis Motion Op.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set pelvis settings."))` — Returns the root settings in the supplied Retarget Profile.
- L280 _public prototype_ `static FRetargetGlobalSettings GetGlobalSettingsFromRetargetProfile(UPARAM(ref) FRetargetProfile& RetargetProfile);` — `UE_DEPRECATED(5.6, "Global settings are now accessed through various Op.")` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set settings that previously used global settings."))` — Returns the global settings in the supplied Retarget Profile.
- L285 _public prototype_ `static void SetGlobalSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FRetargetGlobalSettings& GlobalSettings);` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set settings that previously used global settings."))` — `UE_DEPRECATED(5.6, "Global settings are now accessed through various Op.")` — Set the global settings in a retarget profile (will set bApplyGlobalSettings to true).
- L292 _public prototype_ `static void SetRootSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FTargetRootSettings& RootSettings);` — `UE_DEPRECATED(5.6, "Root settings are now accessed through a Pelvis Motion Op.")` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set settings that previously used root settings."))` — Set the root settings in a retarget profile (will set bApplyRootSettings to true).
- L299 _public prototype_ `static void SetChainSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FTargetChainSettings& ChainSettings, const FName TargetChainName);` — `UE_DEPRECATED(5.6, "Chain settings are now accessed through an Op controller.")` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use op profiles to get/set chain settings."))` — Set the chain settings in a retarget profile (will set bApplyChainSettings to true).
- L307 _public prototype_ `static void SetChainFKSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FTargetChainFKSettings& FKSettings, const FName TargetChainName);` — `UE_DEPRECATED(5.6, "FK Chain settings are now accessed through an FK Chain Op.")` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use FK Chain Op profiles to get/set FK chain settings."))` — Set the chain FK settings in a retarget profile (will set bApplyChainSettings to true).
- L315 _public prototype_ `static void SetChainIKSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FTargetChainIKSettings& IKSettings, const FName TargetChainName);` — `UE_DEPRECATED(5.6, "IK Chain settings are now accessed through an IK Chain Op.")` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use IK Chain Op profiles to get/set IK chain settings."))` — Set the chain IK settings in a retarget profile (will set bApplyChainSettings to true).
- L323 _public prototype_ `static void SetChainSpeedPlantSettingsInRetargetProfile( UPARAM(ref) FRetargetProfile& RetargetProfile, const FTargetChainSpeedPlantSettings& SpeedPlantSettings, const FName TargetChainName);` — `UE_DEPRECATED(5.6, "Speed Plant settings are now accessed through a Speed Plant Op.")` — `UFUNCTION(BlueprintCallable, Category=RetargetProfile, meta = (DeprecatedFunction, DeprecationMessage = "Use Speed Plant Op profiles to get/set speed plant settings."))` — Set the chain Speed Plant settings in a retarget profile (will set bApplyChainSettings to true).
- L336 _private prototype_ `void PostLoadOldSettingsToNew();` — upgrade old assets to new data formats
- L337 _private prototype_ `void PostLoadOldOpsToNewStructOps();`
- L338 _private prototype_ `void PostLoadConvertEverythingToOps();`
- L339 _private prototype_ `void PostLoadPutChainMappingInOps();`
- L340 _private prototype_ `void PostLoadSplitIKChainsOp();`
- L341 _private prototype_ `void PostLoadSplitOps();`
- L343 _private prototype_ `void CleanRetargetPoses();`
- L344 _private prototype_ `void CleanOpStack();`
- L345 _private prototype_ `void PostLoadOpStack();`
- L349 _private prototype_ `FName GetCleanAndUniqueOpName(const FName& InOpName, const int32 InIndexOfOp);` — make the provided op name valid and unique NOTE: if InIndexOfOp is INDEX_None, then it assumes this is a new op
- L353 _private member_ `mutable int32 Version = INDEX_NONE;` — `UPROPERTY(Transient)` — incremented by any edits that require re-initialization
- L357 _private member_ `TObjectPtr<UIKRigDefinition> SourceIKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Source)` — The rig to copy animation FROM.
- L362 _private member_ `TSoftObjectPtr<USkeletalMesh> SourcePreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = Source)` — Optional. Override the Skeletal Mesh to copy animation from. Uses the preview mesh from the Source IK Rig asset by default.
- L367 _private member_ `TObjectPtr<UIKRigDefinition> TargetIKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = Target, DisplayName="Default Target IK Rig")` — The rig to copy animation TO. Note that this is only the default target IK Rig and ops can be setup to use other IK Rigs as desired.
- L372 _private member_ `TSoftObjectPtr<USkeletalMesh> TargetPreviewMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = Target)` — Optional. Override the Skeletal Mesh to preview the retarget on. Uses the preview mesh from the Target IK Rig asset by default.
- L381 _public member_ `FVector TargetMeshOffset;` — `UPROPERTY(EditAnywhere, Category = PreviewOffset)` — The offset applied to the target mesh in the editor viewport.
- L385 _public member_ `float TargetMeshScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = PreviewOffset, meta = (UIMin = "0.01", UIMax = "10.0"))` — Scale the target mesh in the viewport for easier visualization next to the source.
- L389 _public member_ `FVector SourceMeshOffset;` — `UPROPERTY(EditAnywhere, Category = PreviewOffset)` — The offset applied to the source mesh in the editor viewport.
- L393 _public member_ `bool bShowSourceMesh = true;` — `UPROPERTY(EditAnywhere, Category = PreviewVisibility)` — Show/hide the source skeletal mesh in the editor viewport.
- L397 _public member_ `bool bShowTargetMesh = true;` — `UPROPERTY(EditAnywhere, Category = PreviewVisibility)` — Show/hide the target skeletal mesh in the editor viewport.
- L401 _public member_ `bool bShowSourceSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = PreviewVisibility)` — Show/hide the source skeleton in the editor viewport. Note: the viewport must be showing bones to see the skeleton.
- L405 _public member_ `bool bShowTargetSkeleton = true;` — `UPROPERTY(EditAnywhere, Category = PreviewVisibility)` — Show/hide the target skeleton in the editor viewport. Note: the viewport must be showing bones to see the skeleton.
- L409 _public member_ `bool bOverrideSourceSkeletonColor = false;` — `UPROPERTY(EditAnywhere, Category = SkeletonColorOverride)` — Override the source skeleton color in the editor viewport.
- L413 _public member_ `FLinearColor SourceOverideColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = SkeletonColorOverride)` — Override the source skeleton color in the editor viewport.
- L417 _public member_ `bool bOverrideTargetSkeletonColor = false;` — `UPROPERTY(EditAnywhere, Category = SkeletonColorOverride)` — Override the target skeleton color in the editor viewport.
- L421 _public member_ `FLinearColor TargetOverideColor = FLinearColor::Red;` — `UPROPERTY(EditAnywhere, Category = SkeletonColorOverride)` — Override the target skeleton color in the editor viewport.
- L427 _public member_ `bool bIgnoreRootLockInPreview = true;` — `UPROPERTY(EditAnywhere, Category = RootLockSettings)` — When true, animation sequences with "Force Root Lock" turned On will act as though it is Off. This affects only the preview in the retarget editor. Use ExportRootLockMode to control exported animation behavior. This setting has no effect on runtime retargeting where root motion is copied from the source component.
- L431 _public member_ `bool bDebugDraw = true;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)` — Toggle debug drawing for retargeting in the viewport.
- L435 _public member_ `bool bProfileOps = false;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)` — Toggle performance profiling of the op stack.
- L439 _public member_ `float BoneDrawSize = 1.0f;` — `UPROPERTY()` — The visual size of the bones in the viewport (saved between sessions). This is set from the viewport Character>Bones menu
- L443 _public member_ `TObjectPtr<UObject> Controller;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — The controller responsible for managing this asset's data (all editor mutation goes through this)
- L448 _private member_ `TSet<TObjectPtr<USkeletalMesh>> MeshesAskedToFixRootHeightFor;` — only ask to fix the root height once, then warn thereafter (don't nag)
- L456 _private member_ `TArray<FInstancedStruct> RetargetOps;` — `UPROPERTY(meta = (ExcludeBaseStruct, BaseStruct = "/Script/IKRig.RetargetOpBase"))` — polymorphic stack of retargeting operations executed in serial fashion where output of prior operation is input to the next
- L460 _private member_ `TMap<FName, FRetargetProfile> Profiles;` — `UPROPERTY()` — whole setting struct profiles stored in this asset
- L462 _private member_ `FName CurrentProfile = NAME_None;` — `UPROPERTY()`
- L466 _private member_ `TMap<FName, FRetargetOverrideSet> OverrideSets;` — `UPROPERTY()` — sparse property overrides to apply at runtime
- L468 _private member_ `mutable TArray<FName> OverridesToApply;` — the default set of override sets to be applied at runtime
- L470 _private member_ `mutable int32 OverridesVersion = 0;` — updated anytime overrides are modified
- L474 _private member_ `FRetargetVariableContainer Variables;` — `UPROPERTY()` — storage for all variables (used to dynamically adjust property overrides)
- L478 _private member_ `TMap<FName, FIKRetargetPose> SourceRetargetPoses;` — `UPROPERTY()` — The set of retarget poses for the SOURCE skeleton.
- L481 _private member_ `TMap<FName, FIKRetargetPose> TargetRetargetPoses;` — `UPROPERTY()` — The set of retarget poses for the TARGET skeleton.
- L485 _private member_ `FName CurrentSourceRetargetPose;` — `UPROPERTY()` — The current retarget pose to use for the SOURCE.
- L488 _private member_ `FName CurrentTargetRetargetPose;` — `UPROPERTY()` — The current retarget pose to use for the TARGET.
- L495 _private member_ `bool bRetargetRoot_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty))` — BEGIN DEPRECATED DATA
- L497 _private member_ `bool bRetargetFK_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L499 _private member_ `bool bRetargetIK_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L501 _private member_ `float TargetActorOffset_DEPRECATED = 0.0f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L503 _private member_ `float TargetActorScale_DEPRECATED = 0.0f;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L506 _private member_ `TMap<FName, FIKRetargetPose> RetargetPoses;` — `UPROPERTY(meta = (DeprecatedProperty))` — (OLD VERSION) Before retarget poses were stored for target AND source.
- L508 _private member_ `FName CurrentRetargetPose;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L513 _private member_ `FRetargetChainMapping ChainMap_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))` — BEGIN deprecated data from 5.6 refactor
- L516 _private member_ `TArray<TObjectPtr<URetargetChainSettings>> ChainSettings_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FK Chain and IK Chain Op settings instead to affect chain settings."))` — Settings for how to map source chains to target chains.
- L519 _private member_ `TObjectPtr<URetargetRootSettings> RootSettings_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use Pelvis Op settings to affect the pelvis motion instead."))` — the retarget root settings
- L522 _private member_ `TObjectPtr<UIKRetargetGlobalSettings> GlobalSettings_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Toggled 'phases' is now done by enable/disabling ops. Warping now in Stride Warp Op."))` — the retarget global settings
- L525 _private member_ `TObjectPtr<URetargetOpStack> OpStack_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "The pre 5.6 stack of UObject based solvers. Use RetargetOps instead."))` — the stack of UObject-based ops

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/AdditivePoseOp.h` (Public)


#### struct `FIKRetargetAdditivePoseOpSettings`  
`struct FIKRetargetAdditivePoseOpSettings : public FIKRetargetOpSettingsBase`  
_L14-29_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Additive Pose Op Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L20 _public member_ `FName PoseToApply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pose")` — a retarget pose that is applied additively to the output pose of the target skeleton
- L24 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pose", meta=(ClampMin=0, ClampMax=1))` — blend the amount of the pose to apply
- L26 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L28 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetAdditivePoseOp`  
`struct FIKRetargetAdditivePoseOp : public FIKRetargetOpBase`  
_L32-64_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Additive Pose"))`
- inherits: `FIKRetargetOpBase`
- L36 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L43 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L49 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L51 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L53 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L57 _private prototype_ `void ApplyAdditivePose(FIKRetargetProcessor& InProcessor, TArray<FTransform>& OutTargetGlobalPose);`
- L60 _private member_ `FName PelvisBoneName;` — cached in Initialize()
- L63 _private member_ `FIKRetargetAdditivePoseOpSettings Settings;` — `UPROPERTY()`

#### class `UIKRetargetAdditivePoseController`  
`class UIKRetargetAdditivePoseController : public UIKRetargetOpControllerBase`  
_L68-82_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Retarget Pose Op
- L76 _public prototype_ `FIKRetargetAdditivePoseOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetPoseOpSettings struct with the current settings used by the op.
- L81 _public prototype_ `void SetSettings(FIKRetargetAdditivePoseOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetPoseOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "RetargetPoseOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/AlignPoleVectorOp.h` (Public)


#### struct `FPoleVectorMatcher`  
`struct FPoleVectorMatcher`  
_L17-57_
- L19 _public member_ `EAxis::Type SourcePoleAxis;`
- L20 _public member_ `EAxis::Type TargetPoleAxis;`
- L21 _public member_ `float TargetToSourceAngularOffsetAtRefPose;`
- L22 _public member_ `TArray<int32> AllChildrenWithinChain;`
- L23 _public member_ `const FRetargetPoleVectorSettings* Settings;`
- L24 _public member_ `const FResolvedBoneChain* SourceBoneChain;`
- L25 _public member_ `const FResolvedBoneChain* TargetBoneChain;`
- L27 _public prototype_ `bool Initialize( const FRetargetPoleVectorSettings* InSettings, const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FRetargetSkeleton& InSourceSkeleton, const FRetargetSkeleton& InTargetSkeleton);`
- L34 _public prototype_ `void MatchPoleVector( const TArray<FTransform> &SourceGlobalPose, const FRetargetSkeleton& TargetSkeleton, TArray<FTransform> &OutTargetGlobalPose);`
- L41 _private prototype_ `EAxis::Type CalculateBestPoleAxisForChain( const TArray<int32>& BoneIndices, const TArray<FTransform>& GlobalPose);`
- L45 _private prototype_ `static FVector CalculatePoleVector( const EAxis::Type& PoleAxis, const TArray<int32>& BoneIndices, const TArray<FTransform>& GlobalPose);`
- L50 _private prototype_ `static EAxis::Type GetMostDifferentAxis( const FTransform& Transform, const FVector& InNormal);`
- L54 _private prototype_ `static FVector GetChainAxisNormalized( const TArray<int32>& BoneIndices, const TArray<FTransform>& GlobalPose);`

#### struct `FRetargetPoleVectorSettings`  
`struct FRetargetPoleVectorSettings`  
_L60-92_
- reflection: `USTRUCT(BlueprintType)`
- L64 _public prototype_ `FRetargetPoleVectorSettings() = default;`
- L65 _public function_ `FRetargetPoleVectorSettings(FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L69 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the target chain to align pole vectors on.
- L73 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Align Pole Vector", meta=(ReinitializeOnEdit))` — Enable pole vector alignment on this chain.
- L79 _public member_ `double AlignAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Align Pole Vector", meta = (EditCondition = "bEnabled", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Matches the twist angle of this chain (along the Pole direction) to the source chain. At 0, the chain's pole vector direction will be left alone At 1, the root bone of the chain will be twist-rotated in the pole direction to match the orientation of the source chain.
- L83 _public member_ `double StaticAngularOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Align Pole Vector", meta = (EditCondition = "bEnabled", UIMin = "-180.0", UIMax = "180.0", ClampMin = "-180.0", ClampMax = "180.0"))` — Range +/- 180. Default 0. An angular offset, in degrees, for the pole direction of the chain.
- L87 _public member_ `bool MaintainOffset = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Align Pole Vector", meta = (EditCondition = "bEnabled"))` — Default is False. When true, the original angular offset between the source/target pole vectors will be maintained when aligning pole vectors.
- L89 _public prototype_ `bool operator==(const FRetargetPoleVectorSettings& Other) const;`
- L90 _public function_ `FName GetName() const`
- L91 _public function_ `void SetName(const FName InName)`

#### struct `FIKRetargetAlignPoleVectorOpSettings`  
`struct FIKRetargetAlignPoleVectorOpSettings : public FIKRetargetOpSettingsBase`  
_L95-115_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pole Vector Alignment Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L101 _public member_ `TObjectPtr<const UIKRigDefinition> IKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Rig Asset", meta=(ReinitializeOnEdit))` — The target IK Rig asset that contains the bones chains to retarget in this op.
- L104 _public member_ `TArray<FRetargetPoleVectorSettings> ChainsToAlign;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chains", meta=(TitleProperty="TargetChainName"))`
- L108 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the entire op.
- L110 _public prototype_ `void MergePoleVectorSettings(const FRetargetPoleVectorSettings& InSettingsToMerge);`
- L112 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L114 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetAlignPoleVectorOp`  
`struct FIKRetargetAlignPoleVectorOp : public FIKRetargetOpBase`  
_L118-171_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pole Vector Alignment"))`
- inherits: `FIKRetargetOpBase`
- L122 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L129 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L135 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L137 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L139 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L141 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L143 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L145 _public prototype_ `virtual const UIKRigDefinition* GetCustomTargetIKRig() const override;`
- L147 _public prototype_ `virtual FRetargetChainMapping* GetChainMapping() override;`
- L149 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L151 _public prototype_ `virtual void OnReinitPropertyEdited(const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L154 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L155 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L156 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L157 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L160 _public member_ `FIKRetargetAlignPoleVectorOpSettings Settings;` — `UPROPERTY()`
- L164 _public member_ `FRetargetChainMapping ChainMapping;` — `UPROPERTY()` — This op maintains its own chain mapping table to allow per-op mapping
- L168 _private prototype_ `void ApplyIKRigs(const UIKRigDefinition* InSourceIKRig, const UIKRigDefinition* InTargetIKRig);`
- L170 _private member_ `TArray<FPoleVectorMatcher> PoleVectorMatchers;`

#### class `UIKRetargetAlignPoleVectorController`  
`class UIKRetargetAlignPoleVectorController : public UIKRetargetOpControllerBase`  
_L175-189_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing an Align Pole Vector Op
- L183 _public prototype_ `FIKRetargetAlignPoleVectorOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetAlignPoleVectorOpSettings struct with the current settings used by the op.
- L188 _public prototype_ `void SetSettings(FIKRetargetAlignPoleVectorOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetAlignPoleVectorOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "AlignPoleVectorOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/BlendToSourceOp.h` (Public)


#### struct `FIKRetargetBlendToSourceChainSettings`  
`struct FIKRetargetBlendToSourceChainSettings`  
_L17-57_
- reflection: `USTRUCT(BlueprintType)`
- L21 _public prototype_ `FIKRetargetBlendToSourceChainSettings() = default;`
- L22 _public function_ `FIKRetargetBlendToSourceChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L23 _public prototype_ `bool operator==(const FIKRetargetBlendToSourceChainSettings& Other) const;`
- L24 _public function_ `FName GetName() const`
- L25 _public function_ `void SetName(const FName InName)`
- L29 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain to blend to source on.
- L33 _public member_ `double BlendToSource = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta=(ReinitializeOnEdit, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blend the goal on this chain to the location of the equivalent goal on the source chain.
- L39 _public member_ `double TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the translational component of BlendToSource on/off. At 0 the goal is placed at the input location. At 1 the goal is placed at the location of the source chain's end bone.
- L45 _public member_ `double RotationAlpha = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blends the rotational component of BlendToSource on/off. At 0 the goal is oriented to the input rotation. At 1 the goal is oriented to the source chain's end bone rotation.
- L51 _public member_ `FVector TranslationPerAxisAlpha = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Weight each axis separately when using Blend To Source. At 0 the goal is placed at the input location. At 1 the goal is placed at the location of the source chain's end bone.
- L56 _public member_ `double ApplyPelvisOffset = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. At 1, the source goal locations are fully affected by any offsets applied to the pelvis from a Pelvis Motion Op. NOTE: If no Pelvis Motion Op is present, or if the "Affect IK" weights in the Pelvis Motion Op are zero, then this setting has no effect.

#### struct `FIKRetargetBlendToSourceOpSettings`  
`struct FIKRetargetBlendToSourceOpSettings : public FIKRetargetOpSettingsBase`  
_L60-80_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Blend to Source Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L65 _public member_ `TArray<FIKRetargetBlendToSourceChainSettings> Chains;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L71 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends IK goal transform from retargeted transform (0) to source bone transform (1). At 0 the goal is placed at the input location and rotation. At 1 the goal is placed at the location and rotation of the source chain's end bone.
- L75 _public member_ `double DebugDrawSize = 5.0;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Adjust size of goal debug drawing in viewport
- L77 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L79 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKChainToBlend`  
`struct FIKChainToBlend`  
_L82-114_
- L84 _public prototype_ `FIKChainToBlend() = delete;`
- L85 _public function_ `FIKChainToBlend( const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FIKRetargetBlendToSourceChainSettings& InSettings) : SourceBoneChain(&InSourceBoneChain), TargetBoneChain(&InTargetBoneChain), Settings(&InSettings)`
- L91 _public prototype_ `void Run( FIKRigGoalContainer& InGoalContainer, const TArray<FTransform>& InSourceGlobalPose, const FIKRetargetBlendToSourceOpSettings& InOpSettings, const FIKRetargetPelvisMotionOp* InPelvisMotionOp) const;`
- L98 _public prototype_ `void DebugDraw(FPrimitiveDrawInterface* InPDI, const FTransform& InComponentTransform, const double InDrawSize) const;`
- L105 _private member_ `const FResolvedBoneChain* SourceBoneChain;` — cached data
- L106 _private member_ `const FResolvedBoneChain* TargetBoneChain;`
- L107 _private member_ `const FIKRetargetBlendToSourceChainSettings* Settings;`
- L110 _private member_ `static FCriticalSection DebugDataMutex;`
- L111 _private member_ `mutable FTransform DebugOutputGoal = FTransform::Identity;`
- L112 _private member_ `mutable FTransform DebugSourceGoal = FTransform::Identity;`

#### struct `FIKRetargetBlendToSourceOp`  
`struct FIKRetargetBlendToSourceOp : public FIKRetargetOpBase`  
_L117-173_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Blend to Source"))`
- inherits: `FIKRetargetOpBase`
- L121 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L128 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L134 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L136 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L138 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L140 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L142 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L144 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L146 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L148 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L151 _public member_ `FIKRetargetBlendToSourceOpSettings Settings;` — `UPROPERTY()`
- L155 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L161 _public function_ `virtual bool HasDebugDrawing() override`
- L162 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L163 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L164 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L167 _public prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L171 _private member_ `TArray<FIKChainToBlend> ChainsToBlend;`
- L172 _private member_ `const FIKRetargetPelvisMotionOp* PelvisMotionOp;`

#### class `UIKRetargetBlendToSourceController`  
`class UIKRetargetBlendToSourceController : public UIKRetargetOpControllerBase`  
_L177-191_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Blend to Source Op
- L185 _public prototype_ `FIKRetargetBlendToSourceOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKBlendToSourceChainSettings struct with the current settings used by the op.
- L190 _public prototype_ `void SetSettings(FIKRetargetBlendToSourceOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKBlendToSourceChainSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`
- L10 _macro_ `#define LOCTEXT_NAMESPACE "BlendToSourceOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/CopyBasePoseOp.h` (Public)


#### struct `FIKRetargetCopyBasePoseOpSettings`  
`struct FIKRetargetCopyBasePoseOpSettings : public FIKRetargetOpSettingsBase`  
_L14-42_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scale Source Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L21 _public member_ `bool bCopyBasePose = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RetargetPhases)` — When true, will copy all the source bone transforms with matching names to use as a base pose. This can be useful for partial retargeting. NOTE: no retargeting is applied to the bone transforms, they are assumed to be fully compatible between source/target skeletons.
- L25 _public member_ `FBoneReference CopyFromStart;` — `UPROPERTY(EditAnywhere, Category = RetargetPhases, meta = (ReinitializeOnEdit, NotOverrideable, EditCondition = "bCopyBasePose"))` — Filters the bones to copy when using "Copy Base Pose". If specified, will only copy all children of the specified bone (inclusive).
- L29 _public member_ `TArray<FBoneReference> BonesToExclude;` — `UPROPERTY(EditAnywhere, Category = RetargetPhases, meta = (ReinitializeOnEdit, NotOverrideable, EditCondition = "bCopyBasePose"))` — Bones added to this list (and their children) will not have their pose copied. They will be left at the reference pose.
- L33 _public member_ `FName CopyBasePoseRoot_DEPRECATED = NAME_None;` — `UPROPERTY(meta = (DeprecatedProperty))` — converted on PostLoad
- L35 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L37 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L40 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;` — Custom serialization to handle conversion from deprecated CopyBasePoseRoot to CopyFromStart
- L41 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetCopyBasePoseOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetCopyBasePoseOpSettings>`  
_L45-51_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetCopyBasePoseOpSettings>`
- desc: Custom serialization to load deprecated settings

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L48-50_

#### struct `FIKRetargetCopyBasePoseOp`  
`struct FIKRetargetCopyBasePoseOp : public FIKRetargetOpBase`  
_L54-92_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Copy Base Pose"))`
- inherits: `FIKRetargetOpBase`
- L61 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L68 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L74 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L76 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L78 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L80 _public function_ `virtual bool IsSingleton() const override`
- L83 _public member_ `FIKRetargetCopyBasePoseOpSettings Settings;` — `UPROPERTY()`
- L88 _private member_ `TMap<int32, int32> SourceToTargetBoneIndexMap;` — mapping from source bones to target bone indices NOTE: this map will only contain bones with the same name in both skeletons that are below the CopyFromStart (if specified)
- L91 _private member_ `TArray<int32> ChildrenToUpdate;` — children of bones that are copied that need manually updated

#### class `UIKRetargetCopyBasePoseController`  
`class UIKRetargetCopyBasePoseController : public UIKRetargetOpControllerBase`  
_L96-130_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Copy Base Pose Op
- L104 _public prototype_ `FIKRetargetCopyBasePoseOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetCopyBasePoseOpSettings struct with the current settings used by the op.
- L109 _public prototype_ `void SetSettings(FIKRetargetCopyBasePoseOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetCopyBasePoseOpSettings struct containing all the settings to apply to this op
- L113 _public prototype_ `void SetCopyFromStart(const FName InBoneName) const;` — `UFUNCTION(BlueprintCallable, Category = CopyFromStart)` — Set the name of the bone to use as the "Copy From Start" in the op
- L117 _public prototype_ `FName GetCopyFromStart() const;` — `UFUNCTION(BlueprintCallable, Category = CopyFromStart)` — Get the name of the bone to use as the "Copy From Start" in the op
- L121 _public prototype_ `void AddBoneToExclude(const FName InBoneName) const;` — `UFUNCTION(BlueprintCallable, Category = ExcludedBones)` — Add a bone to the "BonesToExclude" array
- L125 _public prototype_ `TArray<FName> GetBonesToExclude() const;` — `UFUNCTION(BlueprintCallable, Category = ExcludedBones)` — Get an array of all the excluded bones.
- L129 _public prototype_ `void ResetBonesToExclude() const;` — `UFUNCTION(BlueprintCallable, Category = ExcludedBones)` — Reset the array of Bones to Exclude

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "CopyBasePoseOp"`
- L49 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon4367f2330103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/CurveRemapOp.h` (Public)


#### struct `FCurveRemapPair`  
`struct FCurveRemapPair`  
_L16-27_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FName SourceCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — The curve name on the SOURCE skeletal mesh to copy animation data from.
- L26 _public member_ `FName TargetCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — The curve name on the TARGET skeletal mesh to receive animation data.

#### struct `FIKRetargetCurveRemapOpSettings`  
`struct FIKRetargetCurveRemapOpSettings : public FIKRetargetOpSettingsBase`  
_L30-55_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Remap Curve Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L39 _public member_ `bool bCopyAllSourceCurves = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Copy Curves")` — Whether to copy all curves over to the target animation instance NOTE: This setting also applies when exporting retargeted animations. True: all source curves are copied to the target animation instance/asset False: only remapped curves are copied on the target animation instance/asset
- L43 _public member_ `bool bRemapCurves = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Remap Curves")` — Toggle curve remapping on/off
- L50 _public member_ `TArray<FCurveRemapPair> CurvesToRemap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Remap Curves")` — Add pairs of Source/Target curve names to remap. While retargeting, the animation from the source curves will be redirected to the curves on the target skeletal meshes. Can be used to drive, blendshapes or other downstream systems. NOTE: By default the IK Retargeter will automatically copy all equivalently named curves from the source to the target. Remapping is only necessary when the target curve name(s) are different.
- L52 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L54 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetCurveRemapOp`  
`struct FIKRetargetCurveRemapOp : public FIKRetargetCurvesOpBase`  
_L58-127_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Remap Curves"))`
- inherits: `FIKRetargetCurvesOpBase`
- L67 _public function_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override`
- L78 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override`
- L84 _public function_ `virtual FIKRetargetOpSettingsBase* GetSettings() override`
- L89 _public function_ `virtual void SetSettings(const FIKRetargetOpSettingsBase* InSettings) override`
- L94 _public function_ `virtual const UScriptStruct* GetSettingsType() const override`
- L99 _public function_ `virtual const UScriptStruct* GetType() const override`
- L104 _public function_ `bool CanHaveChildOps() const override`
- L109 _public function_ `virtual bool IsAbstract() const override`
- L111 _public function_ `virtual bool IsSingleton() const override`
- L113 _public function_ `virtual bool HasCurveProcessing() const override`
- L118 _public prototype_ `virtual void ProcessAnimSequenceCurves(FIKRetargetCurvesOpBase::FCurveData InCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues InCurveFrameValues, FIKRetargetCurvesOpBase::FCurveData& OutCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues& OutCurveFrameValues)const override;`
- L121 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L123 _public prototype_ `virtual void AnimGraphEvaluateAnyThread(FPoseContext& Output) override;`
- L126 _public member_ `FIKRetargetCurveRemapOpSettings Settings;` — `UPROPERTY()`

#### class `UIKRetargetCurveRemapController`  
`class UIKRetargetCurveRemapController : public UIKRetargetOpControllerBase`  
_L131-145_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Curve Remap Op
- L139 _public prototype_ `FIKRetargetCurveRemapOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetCurveRemapOpSettings struct with the current settings used by the op.
- L144 _public prototype_ `void SetSettings(FIKRetargetCurveRemapOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetCurveRemapOpSettings struct containing all the settings to apply to this op

#### class `UCurveRemapOp`  
`class UCurveRemapOp : public URetargetOpBase`  
_L153-170_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URetargetOpBase`
- desc: NOTE: This type has been replaced with FIKRetargetCurveRemapOp.
- L157 _private function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override`
- L167 _private member_ `TArray<FCurveRemapPair> CurvesToRemap;` — `UPROPERTY()`
- L169 _private member_ `bool bCopyAllSourceCurves = true;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API IKRIG_API`
- L13 _macro_ `#define LOCTEXT_NAMESPACE "CurveRemapOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/FKChainsOp.h` (Public)


#### struct `FChainEncoderFK`  
`struct FChainEncoderFK`  
_L16-30_
- L18 _public prototype_ `void Initialize(const FResolvedBoneChain* InBoneChain);`
- L20 _public prototype_ `void EncodePose( const FRetargetSkeleton& SourceSkeleton, const TArray<int32>& SourceBoneIndices, const TArray<FTransform> &InSourceGlobalPose);`
- L25 _public prototype_ `void TransformCurrentChainTransforms(const FTransform& NewParentTransform);`
- L27 _public member_ `TArray<FTransform> CurrentGlobalTransforms;`
- L28 _public member_ `FTransform ChainParentCurrentGlobalTransform;`
- L29 _public member_ `const FResolvedBoneChain* BoneChain;`

#### struct `FChainDecoderCachedData`  
`struct FChainDecoderCachedData`  
_L32-44_
- L34 _public member_ `TArray<int32> SourceBoneIndices;`
- L35 _public member_ `TArray<FQuat> FromToGlobalRotationDeltas;`
- L36 _public member_ `TArray<double> SourceRefPoseLengths;`
- L37 _public member_ `TArray<double> TargetRefPoseLengths;`
- L39 _public prototype_ `void Initialize( const FResolvedBoneChain* InSourceBoneChain, const FResolvedBoneChain* InTargetBoneChain, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton);`

#### struct `FChainDecoderFK`  
`struct FChainDecoderFK`  
_L46-134_
- L48 _public prototype_ `void Initialize( const FResolvedBoneChain* InSourceBoneChain, const FResolvedBoneChain* InTargetBoneChain, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton);`
- L54 _public prototype_ `void InitializeIntermediateParentIndices( const int32 InRetargetRootBoneIndex, const int32 InChainRootBoneIndex, const FTargetSkeleton& InTargetSkeleton);`
- L59 _public prototype_ `void UpdateIntermediateLocalTransforms( const FTargetSkeleton& TargetSkeleton, const TArray<FTransform> &InOutGlobalPose);`
- L63 _public prototype_ `void DecodePose( const FIKRetargetPelvisMotionOp* PelvisMotionOp, const FRetargetFKChainSettings& Settings, const TArray<int32>& TargetBoneIndices, FChainEncoderFK& SourceChain, const TArray<FTransform>& InSourceGlobalPose, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, TArray<FTransform>& InOutGlobalPose);`
- L75 _private prototype_ `FQuat RetargetRotation( const int32 InChainIndex, const FRetargetFKChainSettings& Settings, const TArray<int32>& TargetBoneIndices, const FTargetSkeleton& TargetSkeleton, const TArray<FTransform>& InOutGlobalPose, FChainEncoderFK& SourceChain, FTransform& OutSourceCurrentTransform, FTransform& OutSourceInitialTransform) const;`
- L85 _private prototype_ `FVector RetargetPosition( const int32 InChainIndex, const FQuat& NewRotation, const FIKRetargetPelvisMotionOp* PelvisMotionOp, const FRetargetFKChainSettings& Settings, const TArray<int32>& TargetBoneIndices, FChainEncoderFK& SourceChain, const TArray<FTransform>& InSourceGlobalPose, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, TArray<FTransform>& InOutGlobalPose, const FTransform& InCurrentSourceGlobal);`
- L98 _private prototype_ `FVector RetargetScale( const int32 InChainIndex, const FTransform& OutSourceCurrentTransform, const FTransform& OutSourceInitialTransform) const;`
- L103 _private prototype_ `void MatchChain( const bool bScaleSourceChain, const FChainEncoderFK& SourceChain, const TArray<int32>& TargetBoneIndices, const FVector& TargetChainOrigin, TArray<FTransform>& InOutGlobalPose);`
- L110 _private prototype_ `void BlendByAlpha( const FRetargetFKChainSettings& Settings, const TArray<int32>& TargetBoneIndices, const FTargetSkeleton& TargetSkeleton, TArray<FTransform>& InOutGlobalPose);`
- L116 _private prototype_ `static FVector GetPointOnSplineFromIndexAndAlpha(const TArray<FVector>& InSplinePoints, const int32 InPointIndex, const double InSegmentAlpha);`
- L118 _private prototype_ `static void GetPointOnSplineDistanceFromPoint( const TArray<FVector>& InSplinePoints, const int32 InOriginPointIndex, const double InOriginPointAlpha, const double InTargetDistanceFromOrigin, int32& OutPointIndex, double& OutPointAlpha);`
- L126 _private prototype_ `void UpdateIntermediateParents( const FTargetSkeleton& TargetSkeleton, TArray<FTransform> &InOutGlobalPose);`
- L130 _private member_ `FChainDecoderCachedData CachedData;`
- L131 _private member_ `TArray<int32> IntermediateParentIndices;`
- L132 _private member_ `TArray<FTransform> IntermediateLocalTransforms;`
- L133 _private member_ `const FResolvedBoneChain* BoneChain;`

#### struct `FChainPairFK`  
`struct FChainPairFK`  
_L136-151_
- L138 _public prototype_ `bool Initialize( const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FRetargetFKChainSettings& InSettings, const FIKRigLogger& InLog);`
- L146 _public member_ `FChainEncoderFK FKEncoder;`
- L147 _public member_ `FChainDecoderFK FKDecoder;`
- L148 _public member_ `const FResolvedBoneChain* SourceBoneChain;`
- L149 _public member_ `const FResolvedBoneChain* TargetBoneChain;`
- L150 _public member_ `const FRetargetFKChainSettings* Settings;`

#### enum `EFKChainTranslationMode`  
`enum class EFKChainTranslationMode : uint8`  
_L154-162_
- reflection: `UENUM(BlueprintType)`
- L156 _public enumerator_ `None UMETA(DisplayName = "None")`
- L157 _public enumerator_ `GloballyScaled UMETA(DisplayName = "Globally Scaled")`
- L158 _public enumerator_ `Absolute UMETA(DisplayName = "Absolute")`
- L159 _public enumerator_ `StretchBoneLengthUniformly UMETA(DisplayName = "Stretch Bone Length Uniformly")`
- L160 _public enumerator_ `StretchBoneLengthNonUniformly UMETA(DisplayName = "Stretch Bone Length Non-Uniformly")`
- L161 _public enumerator_ `OrientAndScale UMETA(DisplayName = "Orient and Scale")`

#### enum `EFKChainRotationMode`  
`enum class EFKChainRotationMode : uint8`  
_L165-174_
- reflection: `UENUM(BlueprintType)`
- L167 _public enumerator_ `None = 5 UMETA(DisplayName = "None")`
- L168 _public enumerator_ `Interpolated = 0 UMETA(DisplayName = "Interpolated")`
- L169 _public enumerator_ `OneToOne = 1 UMETA(DisplayName = "One to One")`
- L170 _public enumerator_ `OneToOneReversed = 2 UMETA(DisplayName = "One to One Reversed")`
- L171 _public enumerator_ `MatchChain = 3 UMETA(DisplayName = "Match Chain")`
- L172 _public enumerator_ `MatchScaledChain = 4 UMETA(DisplayName = "Match Scaled Chain")`
- L173 _public enumerator_ `CopyLocal = 6 UMETA(DisplayName = "Copy Local")`

#### struct `FRetargetFKChainSettings`  
`struct FRetargetFKChainSettings`  
_L177-230_
- reflection: `USTRUCT(BlueprintType)`
- L181 _public prototype_ `FRetargetFKChainSettings() = default;`
- L182 _public function_ `FRetargetFKChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L186 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain to transfer animation onto.
- L191 _public member_ `bool EnableFK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FK Chain Retarget")` — Whether to copy the shape of the chain from the source skeleton using the Rotation and Translation modes. Default is true. NOTE: All FK operations run before the IK pass to copy the shape of the FK chain from the source skeleton.
- L203 _public member_ `EFKChainRotationMode RotationMode = EFKChainRotationMode::Interpolated;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FK Chain Retarget")` — Determines how rotation is copied from the source chain to the target chain. Default is Interpolated. None: The rotation of each target bone in the chain is left at the reference pose. Interpolated: Source and target chains are normalized by their length, then each target bone rotation is generated by finding the rotation at the same normalized distance on the source chain and interpolating between the neighboring bones. One to One: Each target bone rotation is copied from the equivalent bone in the source chain, based on the order in the chain, starting at the root of the chain. If the target chain has more bones than the source, the extra bones will remain at their reference pose. One to One Reversed: Same as One-to-One, but starting from the tip of the chain. Match Chain: Uses a Spline-IK type method to orient the target joint chain to exactly match the shape of the source chain. Match Scaled Chain: Same as Match Chain, but scales the source chain to the same length as the target chain before running the match procedure. Copy Local: The local space rotation of the closest source bone is copied to the target. No retargeting is applied. Retarget pose is ignored.
- L209 _public member_ `double RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FK Chain Retarget", meta = (UIMin = "0.0", UIMax = "1.0"))` — Range +/- infinity. Default 1. Scales the amount of rotation that is applied. If Rotation Mode is None this parameter has no effect. Otherwise, this parameter blends the rotation of each bone in the chain from the base retarget pose (0) to the retargeted pose (1).
- L219 _public member_ `EFKChainTranslationMode TranslationMode = EFKChainTranslationMode::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FK Chain Retarget")` — Determines how translation is copied from the source chain to the target chain. Default is None. None: Translation of target bones are left unmodified from the retarget pose. Globally Scaled: Translation of target bone is set to the source bone offset multiplied by the global scale of the skeleton (determined by the relative height difference between pelvis bones). Absolute: Translation of target bone is set to the absolute position of the source bone. Stretch Bone Length Uniformly: squashes or stretches the local translation of each bone so that the length of the target chain matches the relative length of the source chain. Accounts for differences in initial chain lengths. Stretch Bone Length Non-Uniformly: same as "Stretch Bone Length Uniformly" but treats each bone independently to allow for chains that stretch non-uniformly along their length (ie the base may stretch more than the tip or vice versa).
- L225 _public member_ `double TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FK Chain Retarget", meta = (UIMin = "0.0", UIMax = "1.0"))` — Range +/- infinity. Default 1. Scales the amount of translation that is applied. Exact behavior depends on the Translation Mode. In None Mode, this parameter has no effect. In Globally Scaled and Absolute modes, the translation offset is scaled by this parameter.
- L227 _public prototype_ `bool operator==(const FRetargetFKChainSettings& Other) const;`
- L228 _public function_ `FName GetName() const`
- L229 _public function_ `void SetName(const FName InName)`

#### struct `FIKRetargetFKChainsOpSettings`  
`struct FIKRetargetFKChainsOpSettings : public FIKRetargetOpSettingsBase`  
_L233-271_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Retarget Chains Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L239 _public member_ `TObjectPtr<const UIKRigDefinition> IKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Rig Asset", meta=(ReinitializeOnEdit))` — The target IK Rig asset that contains the bones chains to retarget in this op.
- L243 _public member_ `TArray<FRetargetFKChainSettings> ChainsToRetarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))` — The setting for each chain to retarget
- L247 _public member_ `bool bDrawChainLines = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug draw lines on each chain in the viewport
- L251 _public member_ `bool bDrawSingleBoneChains = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug draw spheres on single-bone chains in the viewport
- L255 _public member_ `double ChainDrawThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug draw chain line thickness.
- L259 _public member_ `double ChainDrawSize = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug draw size used for single-bone chains.
- L264 _public member_ `FRetargetChainMapping ChainMapping;` — `UPROPERTY()` — This op maintains its own chain mapping table to allow per-op mapping. NOTE: this is only editable through a custom UI in the details panel or the C++ API.
- L266 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L268 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FFKChainDebugData`  
`struct FFKChainDebugData`  
_L274-280_
- L276 _public member_ `FName TargetChainName;`
- L277 _public member_ `FTransform StartTransform;`
- L278 _public member_ `FTransform EndTransform;`
- L279 _public member_ `bool bIsSingleBoneChain = false;`

#### struct `FIKRetargetFKChainsOp`  
`struct FIKRetargetFKChainsOp : public FIKRetargetOpBase`  
_L284-366_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "FK Chains"))`
- inherits: `FIKRetargetOpBase`
- L288 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L295 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L301 _public prototype_ `virtual void PostInitialize(const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, FIKRigLogger& Log) override;`
- L306 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L308 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L310 _public prototype_ `virtual void CollectRetargetedBones(TSet<int32>& OutRetargetedBones) const override;`
- L312 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L314 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L316 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L318 _public prototype_ `virtual const UIKRigDefinition* GetCustomTargetIKRig() const override;`
- L320 _public prototype_ `virtual FRetargetChainMapping* GetChainMapping() override;`
- L322 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L324 _public prototype_ `virtual void OnReinitPropertyEdited(const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L326 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L329 _public member_ `FIKRetargetFKChainsOpSettings Settings;` — `UPROPERTY()`
- L334 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L341 _public function_ `virtual bool HasDebugDrawing() override`
- L343 _public prototype_ `void SaveDebugData(const TArray<FTransform>& OutTargetGlobalPose);`
- L344 _public member_ `TArray<FFKChainDebugData> AllChainsDebugData;`
- L345 _public member_ `static FCriticalSection DebugDataMutex;`
- L347 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L348 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L349 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L354 _private prototype_ `void ApplyIKRigs(const UIKRigDefinition* InSourceIKRig, const UIKRigDefinition* InTargetIKRig);`
- L357 _private member_ `TArray<FChainPairFK> ChainPairsFK;` — The Source/Target pairs of Bone Chains retargeted using the FK algorithm
- L360 _private member_ `TArray<int32> NonRetargetedChildrenToUpdate;` — Children of the FK chains that need updated after the chains are retargeted
- L361 _private member_ `TArray<FTransform> ChildrenToUpdateLocalTransforms;`
- L365 _private member_ `FRetargetChainMapping ChainMapping_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))` — Deprecated storage for chain mapping (now on settings for API access)

#### class `UIKRetargetFKChainsController`  
`class UIKRetargetFKChainsController : public UIKRetargetOpControllerBase`  
_L370-384_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a FK Chains Op
- L378 _public prototype_ `FIKRetargetFKChainsOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetFKChainsOpSettings struct with the current settings used by the op.
- L383 _public prototype_ `void SetSettings(FIKRetargetFKChainsOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetFKChainsOpSettings struct containing all the settings to apply to this op

#### struct `HIKRetargetEditorChainProxy`  
`struct HIKRetargetEditorChainProxy : public HHitProxy`  
_L388-407_
- inherits: `HHitProxy`
- desc: select chains/goals to edit chain settings
- L390 _public prototype_ `DECLARE_HIT_PROXY( );`
- L392 _public member_ `FName TargetChainName;`
- L394 _public function_ `HIKRetargetEditorChainProxy(const FName& InTargetChainName) : HHitProxy(HPP_World) , TargetChainName(InTargetChainName)`
- L398 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L403 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define LOCTEXT_NAMESPACE "FKChainOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/FilterBoneOp.h` (Public)


#### struct `FFilterBoneData`  
`struct FFilterBoneData`  
_L19-29_
- reflection: `USTRUCT(BlueprintType)`
- L25 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ReinitializeOnEdit))` — The target bone to filter.
- L27 _public member_ `bool bIsReady = false;`
- L28 _public member_ `FOneEuroQuatFilter Filter;`

#### struct `FIKRetargetFilterBoneOpSettings`  
`struct FIKRetargetFilterBoneOpSettings : public FIKRetargetOpSettingsBase`  
_L32-55_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Filter Bone Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L38 _public member_ `TArray<FFilterBoneData> BonesToFilter;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup, meta=(ReinitializeOnEdit))` — A list of bone-pairs to copy transforms between
- L42 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the entire op.
- L46 _public member_ `FOneEuroFilterSettings FilterSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Op Settings")` — The settings to control the One-Euro filter behavior
- L50 _public member_ `bool bResetPlayback = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Op Settings")` — If true, filter is reset when playback loops.
- L52 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L54 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetFilterBoneOp`  
`struct FIKRetargetFilterBoneOp : public FIKRetargetOpBase`  
_L58-90_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Filter Bones"))`
- inherits: `FIKRetargetOpBase`
- L62 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L69 _public prototype_ `virtual void Run( FIKRetargetProcessor& Processor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L75 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L77 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L79 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L81 _public prototype_ `virtual void OnPlaybackReset();`
- L84 _public member_ `FIKRetargetFilterBoneOpSettings Settings;` — `UPROPERTY()`
- L87 _private prototype_ `void ResetFilters(TArray<FTransform>& OutTargetGlobalPose);`
- L89 _private member_ `bool bResetPlayback = true;`

#### class `UIKRetargetFilterBoneController`  
`class UIKRetargetFilterBoneController : public UIKRetargetOpControllerBase`  
_L94-121_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Filter Bone Op
- L102 _public prototype_ `FIKRetargetFilterBoneOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetPinBoneOpSettings struct with the current settings used by the op.
- L107 _public prototype_ `void SetSettings(FIKRetargetFilterBoneOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetPinBoneOpSettings struct containing all the settings to apply to this op
- L111 _public prototype_ `void ClearBonesToFilter();` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Clear all the bones
- L115 _public prototype_ `void AddBoneToFilter(const FName InTargetBone);` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Add a target bone to filter.
- L120 _public prototype_ `TArray<FName> GetAllBonesToFilter();` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Get all the bones currently stored in the op. @return an array of target bone names

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`
- L14 _macro_ `#define LOCTEXT_NAMESPACE "FilterBoneOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/FloorConstraintOp.h` (Public)


#### struct `FFloorConstraintToeDefinition`  
`struct FFloorConstraintToeDefinition`  
_L22-41_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `FBoneReference ToeBone;` — `UPROPERTY(EditAnywhere, Category=Setup, meta=(ReinitializeOnEdit, NotOverrideable))` — The bone located at the base of the toe (the first knuckle).
- L32 _public member_ `double Length = 4.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Dimensions", meta = (ReinitializeOnEdit, ClampMin = "0.0", UIMin = "0.0", UIMax = "50.0"))` — The length of the toe from the ToeBone to the tip of the toe mesh.
- L36 _public member_ `double YawOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Dimensions", meta = (ReinitializeOnEdit, ClampMin = "-179.0", ClampMax = "179.0", UIMin = "-179.0", UIMax = "179.0"))` — Rotate the end of the toe side-to-side. Adjust this to align the length of the toe with the model.
- L40 _public member_ `double VerticalOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Dimensions", meta = (ReinitializeOnEdit, UIMin = "-10.0", UIMax = "10.0"))` — Push the tip of the toes up/down. Adjust this to place the tip of the toe on the bottom of the toe mesh.

#### struct `FFloorConstraintToesDefinition`  
`struct FFloorConstraintToesDefinition`  
_L44-67_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `double Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Settings", meta = (ReinitializeOnEdit, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Default 1.0. Range 0 to 1. Blend the effect of the toe solver on/off.
- L54 _public member_ `float Responsiveness = 0.02f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Filter", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "5.0"))` — Speed coefficient; increases cutoff when signal changes quickly (reactivity).
- L58 _public member_ `float CutoffFrequency = 8.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Filter", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))` — Minimum cutoff frequency for the One Euro Filter (higher = less smoothing).
- L62 _public member_ `float VelocityCutoffFrequency = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toe Filter", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))` — Cutoff frequency for the derivative smoothing step.
- L66 _public member_ `TArray<FFloorConstraintToeDefinition> AllToes;` — `UPROPERTY(EditAnywhere, Category="Toe Definitions", meta=(ReinitializeOnEdit))` — An array of toes to bend when contacting the floor

#### struct `FFloorConstraintFootDefinition`  
`struct FFloorConstraintFootDefinition`  
_L70-96_
- reflection: `USTRUCT(BlueprintType)`
- L76 _public member_ `double MedialOffset = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Dimensions", meta = (ReinitializeOnEdit, ClampMin = "0.0", UIMin = "0.0", UIMax = "50.0"))` — Default 10. The offset in cm towards the interior (middle) of the body.
- L80 _public member_ `double LateralOffset = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Dimensions", meta = (ReinitializeOnEdit, ClampMin = "0.0", UIMin = "0.0", UIMax = "50.0"))` — Default 10. The offset in cm towards the exterior (outside) of the body.
- L84 _public member_ `double HeelOffset = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Dimensions", meta = (ReinitializeOnEdit, ClampMin = "0.0", UIMin = "0.0", UIMax = "50.0"))` — Default 10. The offset in the direction of the heel (rear) of the foot.
- L90 _public member_ `double ToeOffset = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Dimensions", meta = (ReinitializeOnEdit, ClampMin = "0.0", UIMin = "0.0", UIMax = "50.0"))` — Default 10. The offset towards the toes (front) of the foot. NOTE: if you are using toe constraints, this offset should extend to the ball of the foot. Otherwise the toes will never be below the floor and thus never bend.
- L95 _public member_ `double VerticalOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Dimensions", meta = (ReinitializeOnEdit, UIMin = "-10.0", UIMax = "10.0"))` — Default 0. The vertical offset used to define the "bottom" of the foot mesh. NOTE: adjust this up/down if the floor constraint puts the foot mesh below/above the ground level.

#### struct `FFloorConstraintChainSettings`  
`struct FFloorConstraintChainSettings : public FIKRetargetOpSkeletonProvider`  
_L99-148_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRetargetOpSkeletonProvider`
- L103 _public prototype_ `FFloorConstraintChainSettings() = default;`
- L104 _public function_ `FFloorConstraintChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L108 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain to transfer animation onto.
- L118 _public member_ `bool EnableFloorConstraint = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint Chain Settings", meta=(ReinitializeOnEdit))` — Whether to apply the floor constraint to the location of the IK goal on this chain. Default is false. When ON, the floor constraint will adjust the vertical position of the IK Goal according to the following rules. 1. When the source goal bone is LOWER than FloorHeightFalloffStart, the height of the goal is smoothly blended to the height of the source bone. 2. When the source goal bone is HIGHER than FloorHeightFalloffStart, the height of the goal is left at its normal retargeted location. NOTE: the floor is assumed to be the XY plane where Z = 0. NOTE: This only has an effect if the chain has an IK Goal assigned to it in the Target IK Rig asset.
- L122 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default is 0. Blend the effect of the constraint on this goal on/off.
- L126 _public member_ `double MaintainHeightOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default is 0. Maintain the height different between the source and target from the retarget pose.
- L130 _public member_ `bool bUseFoot = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Settings", meta=(ReinitializeOnEdit))` — If true, will use the foot definition for more accurate foot/ground retargeting. If false, treats the foot as a point.
- L134 _public member_ `bool bUseToes = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Foot Settings", meta=(ReinitializeOnEdit))` — If true, will use the toes definition for more accurate toe/ground collision.
- L138 _public member_ `FFloorConstraintFootDefinition Foot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Foot Settings", meta=(ReinitializeOnEdit, EditCondition="bUseFoot"))` — Define the proportions of the target foot.
- L142 _public member_ `FFloorConstraintToesDefinition Toes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Foot Settings", meta=(ReinitializeOnEdit, EditCondition="bUseToes"))` — Define the proportions of the target foot.
- L144 _public prototype_ `bool operator==(const FFloorConstraintChainSettings& Other) const;`
- L146 _public function_ `FName GetName() const`
- L147 _public function_ `void SetName(const FName InName)`

#### struct `FIKRetargetFloorConstraintOpSettings`  
`struct FIKRetargetFloorConstraintOpSettings : public FIKRetargetOpSettingsBase`  
_L151-181_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Floor Goal Op Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L157 _public member_ `TArray<FFloorConstraintChainSettings> ChainsToAffect;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))` — The per-chain settings (exposed indirectly to the UI through a detail customization)
- L161 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default is 1. Blend the effect of the entire op on/off.
- L167 _public member_ `double HeightFalloffOffset = 8.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.1", UIMin = "0.1", UIMax = "100.0"))` — Range 0 to inf. Default is 8. The height in cm from the floor below which the goal is snapped directly to the source bone height. NOTE: if the source bone height is greater than this value, but lower than FloorHeightFalloffEnd, then the height will smoothly blend from the source bone height, to the height of the goal in its normal retargeted position.
- L172 _public member_ `double HeightFalloffDistance = 20.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.1", UIMin = "0.1", UIMax = "100.0"))` — Range 0 to inf. Default is 20. The height in cm from the floor below which the goal is gradually blended towards the source bone height. NOTE: if the source bone is higher than this value, the height of the goal is left at its normal retargeted height.
- L174 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L176 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L179 _public prototype_ `virtual void AssignSkeletonAssets(const USkeleton* InSourceSkeleton, const USkeleton* InTargetSkeleton) override;`

#### struct `FToeConstraint`  
`struct FToeConstraint`  
_L183-222_
- L186 _public member_ `int32 ToeBoneIndex = INDEX_NONE;` — constant
- L187 _public member_ `int32 AnkleBoneIndex = INDEX_NONE;`
- L188 _public member_ `bool bToeReady = false;`
- L189 _public member_ `FTransform InitialToeGlobal;`
- L190 _public member_ `FVector EndRelativeToToe;`
- L191 _public member_ `FVector PitchAxisRelativeToToe;`
- L192 _public member_ `const FFloorConstraintToeDefinition* Settings;`
- L193 _public member_ `const FFloorConstraintToesDefinition* AllToeSettings;`
- L196 _public member_ `FTransform CurrentToeGlobal;` — updated every frame
- L197 _public member_ `FVector Start;`
- L198 _public member_ `FVector End;`
- L199 _public member_ `FVector PitchAxis;`
- L200 _public member_ `FOneEuroScalarFilter AngleFilter;`
- L202 _public prototype_ `void Initialize( const FTargetSkeleton& InTargetSkeleton, const FFloorConstraintToesDefinition& InAllToeSettings, const FFloorConstraintToeDefinition& InToeSettings, const int32 InAnkleBoneIndex, FIKRigLogger& InLog);`
- L209 _public prototype_ `void RunAfterParent( const FTargetSkeleton& InTargetSkeleton, TArray<FTransform>& OutGlobalPose, const FFloorConstraintChainSettings* InChainSettings, FIKRetargetFloorConstraintOpSettings& InOpSettings, const double InDeltaTime);`
- L216 _public prototype_ `void UpdateFramePoints( const TArray<FTransform>& InGlobalPose, const FIKRigGoal* InGoal, bool bUpdateLocalOffset);`
- L221 _public prototype_ `double CalcToeCorrectionAngle();`

#### struct `FFootConstraint`  
`struct FFootConstraint`  
_L224-257_
- L227 _public member_ `static constexpr int32 FrontMedial = 0;` — the foot frame is made of a 4-point quad representing the base of the foot from the heel to the start of the toes
- L228 _public member_ `static constexpr int32 RearMedial = 1;`
- L229 _public member_ `static constexpr int32 FrontLateral = 2;`
- L230 _public member_ `static constexpr int32 RearLateral = 3;`
- L231 _public member_ `static constexpr int32 Count = 4;`
- L234 _public member_ `bool bReadyToRun = false;` — constants
- L235 _public member_ `int32 AnkleBoneIndex = INDEX_NONE;`
- L236 _public member_ `TStaticArray<FVector, Count> PointsOrig;`
- L239 _public member_ `TStaticArray<FVector, Count> Points;` — updated every frame
- L240 _public member_ `FTransform CurrentAnkleGlobal;`
- L242 _public prototype_ `void Initialize( const FTargetSkeleton& InTargetSkeleton, const FFloorConstraintFootDefinition& InFootSettings, const int32 InAnkleBoneIndex, FIKRigLogger& InLog);`
- L248 _public prototype_ `void Run( FIKRigGoal& InOutGoal, const TArray<FTransform>& OutTargetGlobalPose, const FFloorConstraintChainSettings& InChainSettings, const FIKRetargetFloorConstraintOpSettings& InOpSettings);`
- L254 _public prototype_ `void UpdateBasePoints(const TArray<FTransform>& InGlobalPose, const FIKRigGoal* InGoal);`
- L256 _public prototype_ `int32 GetIndexOfLowestPoint();`

#### struct `FFloorConstraint`  
`struct FFloorConstraint`  
_L259-281_
- L261 _public member_ `FName IKGoalName = NAME_None;`
- L262 _public member_ `int32 SourceEndBoneIndex = INDEX_NONE;`
- L263 _public member_ `int32 TargetEndBoneIndex = INDEX_NONE;`
- L264 _public member_ `double HeightOffsetInRefPose = 0.0;`
- L265 _public member_ `const FFloorConstraintChainSettings* Settings = nullptr;`
- L267 _public member_ `FFootConstraint FootConstraint;`
- L268 _public member_ `TArray<FToeConstraint> ToeConstraints;`
- L270 _public prototype_ `void Initialize( const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FFloorConstraintChainSettings& InSettings);`
- L275 _public prototype_ `void Run( const FTargetSkeleton& InTargetSkeleton, FIKRigGoalContainer& InGoalContainer, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose, const FIKRetargetFloorConstraintOpSettings& InOpSettings);`

#### struct `FIKRetargetFloorConstraintOp`  
`struct FIKRetargetFloorConstraintOp : public FIKRetargetOpBase`  
_L284-343_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Floor Constraint"))`
- inherits: `FIKRetargetOpBase`
- L288 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L295 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L301 _public prototype_ `virtual void RunAfterParent( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L307 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L309 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L311 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L313 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L315 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L317 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L319 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L321 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L324 _public member_ `FIKRetargetFloorConstraintOpSettings Settings;` — `UPROPERTY()`
- L327 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L328 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L329 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L331 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InTargetTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L337 _public function_ `virtual bool HasDebugDrawing() override`
- L342 _private member_ `TArray<FFloorConstraint> FloorConstraints;`

#### class `UIKRetargetFloorConstraintController`  
`class UIKRetargetFloorConstraintController : public UIKRetargetOpControllerBase`  
_L347-361_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Floor Constraint Op
- L355 _public prototype_ `FIKRetargetFloorConstraintOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetFloorConstraintOpSettings struct with the current settings used by the op.
- L360 _public prototype_ `void SetSettings(FIKRetargetFloorConstraintOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetFloorConstraintOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API IKRIG_API`
- L13 _macro_ `#define LOCTEXT_NAMESPACE "FloorConstraintOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/IKChainsOp.h` (Public)


#### struct `FIKChainRetargeter`  
`struct FIKChainRetargeter`  
_L19-62_
- L21 _public prototype_ `bool Initialize( const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FRetargetIKChainSettings& InSettings, FIKRigLogger& InLog);`
- L27 _public prototype_ `const FTransform& GenerateGoalTransform( const FIKRetargetPelvisMotionOp* InPelvisMotionOp, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& InTargetGlobalPose, const FRetargetSkeleton& InSourceSkeleton, const FRetargetSkeleton& InTargetSkeleton);`
- L34 _public function_ `const FResolvedBoneChain& GetSourceChain() const`
- L36 _public function_ `const FResolvedBoneChain& GetTargetChain() const`
- L38 _public function_ `const FRetargetIKChainSettings* GetSettings() const`
- L40 _public function_ `const FTransform& GetGoalTransform() const`
- L44 _private prototype_ `FQuat CalculateGoalRotation(const TArray<FTransform>& InSourceGlobalPose) const;`
- L46 _private prototype_ `FVector CalculateGoalPosition( const FIKRetargetPelvisMotionOp* InPelvisMotionOp, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& InTargetGlobalPose, const FRetargetSkeleton& InSourceSkeleton, const FRetargetSkeleton& InTargetSkeleton) const;`
- L54 _private member_ `FTransform GoalOutput;` — cached data
- L55 _private member_ `const FResolvedBoneChain* SourceBoneChain;`
- L56 _private member_ `const FResolvedBoneChain* TargetBoneChain;`
- L57 _private member_ `const FRetargetIKChainSettings* Settings;`
- L58 _private member_ `double InvInitialLengthSource = 1.0f;`
- L59 _private member_ `double InitialTargetChainLength = 1.0f;`
- L61 _private member_ `FTransform InitialTargetEndRelativeToSourceEnd;`

#### struct `FRetargetIKChainSettings`  
`struct FRetargetIKChainSettings`  
_L65-142_
- reflection: `USTRUCT(BlueprintType)`
- L69 _public prototype_ `FRetargetIKChainSettings() = default;`
- L70 _public function_ `FRetargetIKChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L74 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain to transfer animation onto.
- L80 _public member_ `bool EnableIK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit))` — Whether to modify the location of the IK goal on this chain. Default is true. NOTE: This only has an effect if the chain has an IK Goal assigned to it in the Target IK Rig asset. NOTE: If off, and this chain has an IK Goal, the IK will still be evaluated, but the Goal is set to the input bone location (from the FK pass).
- L86 _public member_ `double BlendToSource = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend to Source", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blends IK goal transform from retargeted transform (0) to source bone transform (1). At 0 the goal is placed at the retargeted location and rotation. At 1 the goal is placed at the location and rotation of the source chain's end bone.
- L92 _public member_ `double BlendToSourceTranslation = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend to Source", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the translational component of BlendToSource on/off. At 0 the goal is placed at the retargeted location. At 1 the goal is placed at the location of the source chain's end bone.
- L98 _public member_ `double BlendToSourceRotation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend to Source", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blends the rotational component of BlendToSource on/off. At 0 the goal is oriented to the retargeted rotation. At 1 the goal is oriented to the source chain's end bone rotation.
- L104 _public member_ `FVector BlendToSourceWeights = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend to Source", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Weight each axis separately when using Blend To Source. At 0 the goal is placed at the retargeted location. At 1 the goal is placed at the location of the source chain's end bone.
- L110 _public member_ `bool ApplyPelvisOffsetToSourceGoals = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend to Source")` — Default false. When true, the source goal locations are affected by the target pelvis motion. NOTE: this setting applies all offsets generated in the Pelvis Motion Op. If no Pelvis Motion Op is present, or if the "Affect IK" weights in the Pelvis Motion Op are zero, then this setting has no effect.
- L114 _public member_ `FVector StaticOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Offset")` — Default 0, 0, 0. Apply a static global-space offset to IK goal position.
- L118 _public member_ `FVector StaticLocalOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Offset")` — Default 0, 0, 0. Apply a static local-space offset to IK goal position.
- L122 _public member_ `FRotator StaticRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Offset")` — Default 0, 0, 0. Apply a static local-space offset to IK goal rotation.
- L126 _public member_ `double ScaleVertical = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Translation", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "5.0"))` — Range 0 to infinity. Default 1. Scales the vertical component of the IK goal's position.
- L134 _public member_ `double Extension = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Length", meta = (ClampMin = "0.0", ClampMax = "5.0", UIMin = "0.1", UIMax = "2.0"))` — Range 0 to 5. Default 1. Brings IK goal closer (0) or further (1+) from origin of chain. At 0 the effector is placed at the origin of the chain (ie Shoulder, Hip etc). At 1 the effector is left at the end of the chain (ie Wrist, Foot etc) Values in-between 0-1 will slide the effector along the vector from the start to the end of the chain. Values greater than 1 will stretch the chain beyond the retargeted length.
- L136 _public prototype_ `bool operator==(const FRetargetIKChainSettings& Other) const;`
- L137 _public function_ `FName GetName() const`
- L138 _public function_ `void SetName(const FName InName)`
- L141 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serialization to handle loading old assets

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRetargetIKChainSettings> : public TStructOpsTypeTraitsBase2<FRetargetIKChainSettings>`  
_L145-148_
- inherits: `TStructOpsTypeTraitsBase2<FRetargetIKChainSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L147-147_

#### struct `FIKRetargetIKChainsOpSettings`  
`struct FIKRetargetIKChainsOpSettings : public FIKRetargetOpSettingsBase`  
_L151-180_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Retarget IK Goals Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L156 _public member_ `TArray<FRetargetIKChainSettings> ChainsToRetarget;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L160 _public member_ `bool bDrawFinalGoals = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Draw final IK goal locations.
- L164 _public member_ `bool bDrawSourceLocations = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Draw goal locations from source skeleton.
- L168 _public member_ `double GoalDrawSize = 5.0;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Adjust size of goal debug drawing in viewport
- L172 _public member_ `double GoalDrawThickness = 1.0;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Adjust thickness of goal debug drawing in viewport
- L174 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L176 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L178 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L179 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetIKChainsOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetIKChainsOpSettings>`  
_L183-186_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetIKChainsOpSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L185-185_

#### struct `FChainDebugData`  
`struct FChainDebugData`  
_L189-196_
- L191 _public member_ `FName TargetChainName;`
- L192 _public member_ `FTransform InputTransformStart = FTransform::Identity;`
- L193 _public member_ `FTransform InputTransformEnd = FTransform::Identity;`
- L194 _public member_ `FTransform OutputTransformEnd = FTransform::Identity;`
- L195 _public member_ `FTransform SourceTransformEnd = FTransform::Identity;`

#### struct `FIKRetargetIKChainsOp`  
`struct FIKRetargetIKChainsOp : public FIKRetargetOpBase`  
_L200-266_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Retarget IK Goals", Deprecated))`
- inherits: `FIKRetargetOpBase`
- L204 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L211 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L217 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L219 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L221 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L223 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L225 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L227 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L229 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L231 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L234 _public member_ `FIKRetargetIKChainsOpSettings Settings;` — `UPROPERTY()`
- L238 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L245 _public function_ `virtual bool HasDebugDrawing() override`
- L247 _public prototype_ `void SaveDebugData( const FIKRetargetProcessor& InProcessor, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& OutTargetGlobalPose);`
- L252 _public member_ `TArray<FChainDebugData> AllChainsDebugData;`
- L253 _public member_ `FVector DebugRootModification;`
- L254 _public member_ `static FCriticalSection DebugDataMutex;`
- L256 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L257 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L258 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L263 _private prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L265 _private member_ `TArray<FIKChainRetargeter> IKChainRetargeters;`

#### class `UIKRetargetIKChainsController`  
`class UIKRetargetIKChainsController : public UIKRetargetOpControllerBase`  
_L270-284_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a IK Chains Op
- L278 _public prototype_ `FIKRetargetIKChainsOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetIKChainsOpSettings struct with the current settings used by the op.
- L283 _public prototype_ `void SetSettings(FIKRetargetIKChainsOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetIKChainsOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "IKChainOp"`
- L147 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anonbbd505f00103`)
- L185 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anonbbd505f00203`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/OffsetGoalsOp.h` (Public)


#### struct `FIKRetargetOffsetGoalsChainSettings`  
`struct FIKRetargetOffsetGoalsChainSettings`  
_L16-49_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FIKRetargetOffsetGoalsChainSettings() = default;`
- L21 _public function_ `FIKRetargetOffsetGoalsChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L22 _public prototype_ `bool operator==(const FIKRetargetOffsetGoalsChainSettings& Other) const;`
- L23 _public function_ `FName GetName() const`
- L24 _public function_ `void SetName(const FName InName)`
- L28 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain for these settings.
- L32 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blend the offsets on this chain on/off.
- L36 _public member_ `FVector GlobalTranslationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chain Settings")` — Default 0,0,0. Apply a global-space offset to the IK goal position.
- L40 _public member_ `FVector LocalTranslationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chain Settings")` — Default 0,0,0. Apply a local-space offset to the IK goal position.
- L44 _public member_ `FRotator GlobalRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chain Settings")` — Default 0,0,0. Apply a global-space offset to the IK goal rotation.
- L48 _public member_ `FRotator LocalRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chain Settings")` — Default 0,0,0. Apply a local-space offset to the IK goal rotation.

#### struct `FIKRetargetOffsetGoalsOpSettings`  
`struct FIKRetargetOffsetGoalsOpSettings : public FIKRetargetOpSettingsBase`  
_L52-74_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Blend to Source Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L57 _public member_ `TArray<FIKRetargetOffsetGoalsChainSettings> Chains;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L61 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blend all the offsets on/off.
- L65 _public member_ `double TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blend the translation offsets on/off.
- L69 _public member_ `double RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blend the rotation offsets on/off.
- L71 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L73 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKChainToOffset`  
`struct FIKChainToOffset`  
_L76-94_
- L78 _public prototype_ `FIKChainToOffset() = delete;`
- L79 _public function_ `FIKChainToOffset( const FResolvedBoneChain& InTargetBoneChain, const FIKRetargetOffsetGoalsChainSettings& InSettings) : TargetBoneChain(&InTargetBoneChain) , Settings(&InSettings)`
- L85 _public prototype_ `void Run( FIKRigGoalContainer& InGoalContainer, const FIKRetargetOffsetGoalsOpSettings& InOpSettings) const;`
- L92 _private member_ `const FResolvedBoneChain* TargetBoneChain;` — cached data
- L93 _private member_ `const FIKRetargetOffsetGoalsChainSettings* Settings;`

#### struct `FIKRetargetOffsetGoalsOp`  
`struct FIKRetargetOffsetGoalsOp : public FIKRetargetOpBase`  
_L97-145_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Offset Goals"))`
- inherits: `FIKRetargetOpBase`
- L101 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L108 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L114 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L116 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L118 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L120 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L122 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L124 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L126 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L128 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L131 _public member_ `FIKRetargetOffsetGoalsOpSettings Settings;` — `UPROPERTY()`
- L135 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L136 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L137 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L140 _public prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L144 _private member_ `TArray<FIKChainToOffset> ChainsToOffset;`

#### class `UIKRetargetOffsetGoalsController`  
`class UIKRetargetOffsetGoalsController : public UIKRetargetOpControllerBase`  
_L149-163_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Offset IK Goals Op
- L157 _public prototype_ `FIKRetargetOffsetGoalsOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetOffsetGoalsOpSettings struct with the current settings used by the op.
- L162 _public prototype_ `void SetSettings(FIKRetargetOffsetGoalsOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetOffsetGoalsOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`
- L10 _macro_ `#define LOCTEXT_NAMESPACE "BlendToSourceOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/PelvisMotionOp.h` (Public)


#### struct `FIKRetargetPelvisMotionOpSettings`  
`struct FIKRetargetPelvisMotionOpSettings : public FIKRetargetOpSettingsBase`  
_L16-147_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pelvis Motion Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L22 _public member_ `FBoneReference SourcePelvisBone;` — `UPROPERTY(EditAnywhere, Category=Setup, meta=(ReinitializeOnEdit, NotOverrideable))` — The Pelvis bone on the source skeleton to copy motion FROM.
- L26 _public member_ `FBoneReference TargetPelvisBone;` — `UPROPERTY(EditAnywhere, Category=Setup, meta=(ReinitializeOnEdit, NotOverrideable))` — The Pelvis bone on the target skeleton to copy motion TO.
- L31 _public member_ `FVector BlendToAbsoluteOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scaled or Absolute", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Blend from motion scaled by the size of the character, to the absolute delta motion from the source. NOTE: Typically, this is only applied to vertical motion (Z) to prevent dampening the pelvis bob on short characters.
- L38 _public member_ `double FloorConstraintWeight = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Floor Constraint", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default is 0. Set to a value of 1 to turn the pelvis floor constraint ON. When ON, the floor constraint will adjust the vertical Pelvis motion separately according to the following rules: 1. When the source pelvis is LOWER than the ref pose, the target pelvis will be lowered proportional to their relative crotch heights. 2. When the source pelvis is HIGHER than the ref pose, the target pelvis will be raised an identical amount while maintaining any vertical offset in the ref pose.
- L43 _public member_ `double SourceCrotchOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint")` — A negative vertical offset in cm relative to the Pelvis bone of the SOURCE. NOTE: Adjust this until the green dot is located roughly at the crotch of the character.
- L48 _public member_ `double TargetCrotchOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint")` — A negative vertical offset in cm relative to the Pelvis bone of the TARGET. NOTE: Adjust this until the green dot is located roughly at the crotch of the character.
- L53 _public member_ `bool bUseGroundFalloff = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint")` — When true, the effect of the floor constraint decays as the pelvis gets further from the floor. NOTE: This can help avoid over dampening vertical motion on the pelvis when retargeting to characters that are shorter than the source.
- L59 _public member_ `double GroundFalloffHeightPercent = 0.9f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Constraint", meta = (ClampMin = "0.1", ClampMax = "1.0", UIMin = "0.1", UIMax = "1.0"))` — Controls the height at which the floor constraint will begin blending in as a percentage of the pelvis height in the retarget pose. NOTE: Use this to prevent the floor constraint from dampening vertical pelvis motion at normal standing heights. At 1, the constraint is active at normal standing height. At 0.1, the constraint will only activate when within 10% of the height off the floor.
- L65 _public member_ `double RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Rotation", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the amount of retargeted pelvis rotation to apply. At 0 the pelvis is left at the rotation from the retarget pose. At 1 the pelvis is rotated fully to match the source pelvis rotation.
- L69 _public member_ `FRotator RotationOffsetLocal = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Rotation", meta = (ClampMin = "-180.0", ClampMax = "180.0", UIMin = "-180.0", UIMax = "180.0"))` — Applies a static local-space rotation offset to the pelvis.
- L73 _public member_ `FRotator RotationOffsetGlobal = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Rotation", meta = (ClampMin = "-180.0", ClampMax = "180.0", UIMin = "-180.0", UIMax = "180.0"))` — Applies a static global-space rotation offset to the pelvis.
- L79 _public member_ `double TranslationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Translation", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blends the amount of retargeted pelvis translation to apply. At 0 the pelvis is left at the position from the retarget pose. At 1 the pelvis will follow the source motion according to the behavior defined in the subsequent settings.
- L83 _public member_ `FVector TranslationOffsetLocal = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Translation")` — Applies a static local-space translation offset to the pelvis.
- L87 _public member_ `FVector TranslationOffsetGlobal = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Translation")` — Applies a static global-space translation offset to the pelvis.
- L93 _public member_ `double BlendToSourceTranslation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Translation", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 0. Blends the retarget pelvis' translation to the exact source location. At 0 the pelvis is placed at the retargeted location. At 1 the pelvis is placed at the location of the source's pelvis bone.
- L97 _public member_ `FVector BlendToSourceTranslationWeights = FVector::OneVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pelvis Translation", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Per-axis weights for the Blend to Source.
- L101 _public member_ `double ScaleHorizontal = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Pelvis Translation", meta = (UIMin = "0.0", UIMax = "3.0"))` — Default 1. Scales the translation of the pelvis in the horizontal plane (X,Y).
- L105 _public member_ `double ScaleVertical = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale Pelvis Translation", meta = (UIMin = "0.0", UIMax = "3.0"))` — Default 1. Scales the translation of the pelvis in the vertical direction (Z).
- L111 _public member_ `double AffectIKHorizontal = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affect IK Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "Affect IK Horizontal"))` — Range 0 to 1. Default 1. Control whether modifications made to the pelvis will affect the horizontal component of IK positions. At 0 the IK positions are independent of the pelvis modifications. At 1 the IK positions are calculated relative to the modified pelvis location.
- L117 _public member_ `double AffectIKVertical = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affect IK Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", DisplayName = "Affect IK Vertical"))` — Range 0 to 1. Default 0. Control whether modifications made to the pelvis will affect the vertical component of IK positions. At 0 the IK positions are independent of the pelvis modifications. At 1 the IK positions are calculated relative to the modified pelvis location.
- L121 _public member_ `double DebugDrawSize = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")` — Adjust size of the debug drawing
- L125 _public member_ `double DebugDrawThickness = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")` — Adjust thickness of the debug drawing
- L127 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L129 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L133 _public prototype_ `virtual USkeleton* GetSkeleton(const FName InPropertyName) override;`
- L137 _public member_ `FVector TranslationOffset_DEPRECATED = FVector::ZeroVector;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L140 _public member_ `FRotator RotationOffset_DEPRECATED = FRotator::ZeroRotator;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L143 _public member_ `bool bEnableDebugDraw_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L145 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L146 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetPelvisMotionOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetPelvisMotionOpSettings>`  
_L150-153_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetPelvisMotionOpSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L152-152_

#### struct `FPelvisSource`  
`struct FPelvisSource`  
_L155-164_
- L157 _public member_ `FName BoneName;`
- L158 _public member_ `int32 BoneIndex;`
- L159 _public member_ `FQuat InitialRotation;`
- L160 _public member_ `float InitialHeightInverse;`
- L161 _public member_ `FVector InitialPosition;`
- L162 _public member_ `FVector CurrentPosition;`
- L163 _public member_ `FQuat CurrentRotation;`

#### struct `FPelvisTarget`  
`struct FPelvisTarget`  
_L166-176_
- L168 _public member_ `FName BoneName;`
- L169 _public member_ `int32 BoneIndex;`
- L170 _public member_ `FVector InitialPosition;`
- L171 _public member_ `FQuat InitialRotation;`
- L172 _public member_ `float InitialHeight;`
- L174 _public member_ `FVector PelvisTranslationDelta;`
- L175 _public member_ `FQuat PelvisRotationDelta;`

#### struct `FIKRetargetPelvisMotionOp`  
`struct FIKRetargetPelvisMotionOp : public FIKRetargetOpBase`  
_L179-259_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pelvis Motion"))`
- inherits: `FIKRetargetOpBase`
- L183 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L190 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L196 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L198 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L200 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L202 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L204 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L206 _public prototype_ `virtual void CollectRetargetedBones(TSet<int32>& OutRetargetedBones) const override;`
- L208 _public prototype_ `FName GetPelvisBoneName(ERetargetSourceOrTarget SourceOrTarget) const;`
- L210 _public prototype_ `FVector GetGlobalScaleVector() const;`
- L212 _public prototype_ `FVector GetAffectIKWeightAsVector() const;`
- L214 _public prototype_ `FVector GetPelvisTranslationOffset() const;`
- L216 _public prototype_ `int32 GetPelvisBoneIndex(ERetargetSourceOrTarget SourceOrTarget) const;`
- L219 _public member_ `FIKRetargetPelvisMotionOpSettings Settings;` — `UPROPERTY()`
- L223 _private prototype_ `void Reset();`
- L225 _private prototype_ `bool InitializeSource( const FName SourcePelvisBoneName, const FRetargetSkeleton& SourceSkeleton, FIKRigLogger& Log);`
- L230 _private prototype_ `bool InitializeTarget( const FName TargetPelvisBoneName, const FTargetSkeleton& TargetSkeleton, FIKRigLogger& Log);`
- L235 _private prototype_ `void RetargetPelvisTransform(const TArray<FTransform>& SourceGlobalPose, FTransform& OutPelvisGlobalPose);`
- L238 _private member_ `FPelvisSource Source;` — transient work data
- L239 _private member_ `FPelvisTarget Target;`
- L240 _private member_ `FVector GlobalScaleFactor;`
- L245 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L247 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L254 _public function_ `virtual bool HasDebugDrawing() override`
- L256 _public member_ `FTransform CurrentPelvisTransform;`
- L257 _public member_ `static FCriticalSection DebugDataMutex;`

#### class `UIKRetargetPelvisMotionController`  
`class UIKRetargetPelvisMotionController : public UIKRetargetOpControllerBase`  
_L263-301_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Pelvis Motion Op
- L271 _public prototype_ `FIKRetargetPelvisMotionOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetPelvisMotionOpSettings struct with the current settings used by the op.
- L276 _public prototype_ `void SetSettings(FIKRetargetPelvisMotionOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetPelvisMotionOpSettings struct containing all the settings to apply to this op
- L281 _public prototype_ `void SetSourcePelvisBone(const FName InSourcePelvisBone);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the pelvis bone for the source. @param InSourcePelvisBone the name of the pelvis bone on the source skeleton.
- L286 _public prototype_ `FName GetSourcePelvisBone();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the pelvis bone for the source. @return the name of the pelvis bone on the source skeleton.
- L291 _public prototype_ `void SetTargetPelvisBone(const FName InTargetPelvisBone);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the pelvis bone for the target. @param InTargetPelvisBone the name of the pelvis bone on the target skeleton.
- L296 _public prototype_ `FName GetTargetPelvisBone();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the pelvis bone for the target. @return the name of the pelvis bone on the target skeleton.
- L300 _private prototype_ `FIKRetargetPelvisMotionOpSettings& GetPelvisOpSettings() const;`

#### struct `HIKRetargetEditorRootProxy`  
`struct HIKRetargetEditorRootProxy : public HHitProxy`  
_L305-321_
- inherits: `HHitProxy`
- desc: select root control to edit root settings
- L307 _public prototype_ `DECLARE_HIT_PROXY( );`
- L309 _public function_ `HIKRetargetEditorRootProxy() : HHitProxy(HPP_World)`
- L312 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L317 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "PelvisMotionOp"`
- L152 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anond1c826af0103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/PinBoneOp.h` (Public)


#### enum `EPinBoneType`  
`enum class EPinBoneType : uint8`  
_L16-22_
- reflection: `UENUM()`
- L18 _public enumerator_ `FullTransform`
- L19 _public enumerator_ `TranslateOnly`
- L20 _public enumerator_ `RotateOnly`
- L21 _public enumerator_ `ScaleOnly`

#### struct `FPinBoneData`  
`struct FPinBoneData`  
_L25-54_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public prototype_ `void CachePinData(ERetargetSourceOrTarget InSkeletonToCopyFrom, const FIKRetargetProcessor& Processor);`
- L33 _public member_ `FBoneReference BoneToCopyFrom;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ReinitializeOnEdit, NotOverrideable))` — The bone to copy FROM.
- L36 _public member_ `FBoneReference BoneToCopyTo;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ReinitializeOnEdit, NotOverrideable))` — The bone to copy TO. Will have its transform pinned to BoneToCopyFrom
- L39 _public member_ `FRetargetPoseScaleWithPivot LastUsedSourceScale;` — the scale factor used to calculate all the cached offset (lazy evaluated when scale factor is modified)
- L41 _public member_ `FTransform LocalRefPoseBoneToCopyTo;` — the local transform of the BoneToCopyTo in the ref pose
- L43 _public member_ `FTransform LocalRefPoseBoneToCopyFrom;` — the local transform of the BoneToCopyFrom in the ref pose
- L45 _public member_ `FTransform OffsetFromBoneToCopyFromInRefPose;` — the relative transform between the BoneToCopyFrom and BoneToCopyTo in the reference pose
- L49 _public member_ `FName BoneToPin_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — deprecated properties
- L51 _public member_ `FName BoneToPinTo_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L53 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPinBoneData> : public TStructOpsTypeTraitsBase2<FPinBoneData>`  
_L57-63_
- inherits: `TStructOpsTypeTraitsBase2<FPinBoneData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L60-62_

#### enum `EPinBoneTranslationMode`  
`enum class EPinBoneTranslationMode : uint8`  
_L66-78_
- reflection: `UENUM()`
- L69 _public enumerator_ `CopyGlobalPosition` — Copy the global position of BoneToCopyFrom
- L71 _public enumerator_ `CopyLocalPosition` — Copy the local translation (relative to parent), in global space, from BoneToCopyFrom to BoneToCopyTo
- L73 _public enumerator_ `CopyLocalPositionRelativeOffset` — Copy the local translation, in global space, from BoneToCopyFrom to BoneToCopyTo and add the difference in lengths in the reference pose
- L75 _public enumerator_ `CopyLocalPositionRelativeScaled` — Copy the local translation, in global space, from BoneToCopyFrom to BoneToCopyTo and scale by the relative lengths in the reference pose
- L77 _public enumerator_ `CopyGlobalPositionAndMaintainOffset` — Copy the global position of BoneToCopyFrom, and add the local offset between BoneToCopyFrom and BoneToCopyTo in the reference pose

#### enum `EPinBoneRotationMode`  
`enum class EPinBoneRotationMode : uint8`  
_L81-87_
- reflection: `UENUM()`
- L84 _public enumerator_ `CopyGlobalRotation` — no offset is maintained
- L86 _public enumerator_ `MaintainOffsetFromBoneToCopyFrom` — maintains rotation offset between BoneToCopyTo and BoneToCopyFrom in the reference pose

#### struct `FIKRetargetPinBoneOpSettings`  
`struct FIKRetargetPinBoneOpSettings : public FIKRetargetOpSettingsBase`  
_L90-144_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pin Bone Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L96 _public member_ `TArray<FPinBoneData> BonesToPin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup, meta=(ReinitializeOnEdit, NotOverrideable))` — A list of bone-pairs to copy transforms between
- L100 _public member_ `ERetargetSourceOrTarget SkeletonToCopyFrom = ERetargetSourceOrTarget::Target;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Setup, meta=(ReinitializeOnEdit))` — Which skeleton to copy animation from.
- L104 _public member_ `bool bCopyTranslation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Translation)` — Copy the translation of the bone.
- L108 _public member_ `EPinBoneTranslationMode TranslationMode = EPinBoneTranslationMode::CopyGlobalPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Translation)` — The method used to calculate the translation of the bone.
- L112 _public member_ `bool bCopyRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — Copy the rotation of the bone.
- L116 _public member_ `EPinBoneRotationMode RotationMode = EPinBoneRotationMode::CopyGlobalRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation)` — The method used to calculate the rotation of the bone.
- L120 _public member_ `bool bCopyScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Scale)` — Copy the scale of the bone.
- L124 _public member_ `bool bPropagateToChildren = false;` — `UPROPERTY(EditAnywhere, Category=PropagateTransform)` — Update children bone transforms (recursively).
- L128 _public member_ `FTransform GlobalOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Offset)` — A manual offset to apply in global space
- L132 _public member_ `FTransform LocalOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Offset)` — A manual offset to apply in local space
- L134 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L136 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L139 _public prototype_ `virtual USkeleton* GetSkeleton(const FName InPropertyName) override;`
- L142 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L143 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetPinBoneOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetPinBoneOpSettings>`  
_L147-150_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetPinBoneOpSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L149-149_

#### struct `FIKRetargetPinBoneOp`  
`struct FIKRetargetPinBoneOp : public FIKRetargetOpBase`  
_L153-192_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Pin Bones"))`
- inherits: `FIKRetargetOpBase`
- L157 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L164 _public prototype_ `virtual void Run( FIKRetargetProcessor& Processor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L170 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L172 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L174 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L177 _public member_ `FIKRetargetPinBoneOpSettings Settings;` — `UPROPERTY()`
- L180 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L185 _private member_ `bool bFoundAllBonesToPin = false;`
- L187 _private prototype_ `FTransform GetNewBoneTransform( const FPinBoneData& PinData, const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) const;`

#### class `UIKRetargetPinBoneController`  
`class UIKRetargetPinBoneController : public UIKRetargetOpControllerBase`  
_L196-226_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Pin Bone Op
- L204 _public prototype_ `FIKRetargetPinBoneOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetPinBoneOpSettings struct with the current settings used by the op.
- L209 _public prototype_ `void SetSettings(FIKRetargetPinBoneOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetPinBoneOpSettings struct containing all the settings to apply to this op
- L213 _public prototype_ `void ClearAllBonePairs();` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Clear all the bone pairs
- L220 _public prototype_ `void SetBonePair(const FName InBoneToCopyFrom, const FName InBoneToCopyTo);` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Add a pair of bones to copy animation between. @param InBoneToCopyFrom the name of the bone to copy animation from @param InBoneToCopyTo the name of the bone to apply animation to NOTE: if the bone to copy to is already present in the op, it will be updated with the new bone to copy from.
- L225 _public prototype_ `TMap<FName,FName> GetAllBonePairs();` — `UFUNCTION(BlueprintCallable, Category = BonePairs)` — Get all the bone pairs currently stored in the op. @return a map with target bones as keys and source bones as values.

#### class `UPinBoneOp`  
`class UPinBoneOp : public URetargetOpBase`  
_L234-288_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URetargetOpBase`
- desc: NOTE: This type has been replaced with FIKRetargetPinBoneOp.
- L240 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override`
- L257 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L261 _public member_ `TArray<FPinBoneData> BonesToPin;` — `UPROPERTY()`
- L263 _public member_ `ERetargetSourceOrTarget PinTo = ERetargetSourceOrTarget::Target;` — `UPROPERTY()`
- L265 _public member_ `bool bCopyTranslation = true;` — `UPROPERTY()`
- L267 _public member_ `bool bCopyRotation = true;` — `UPROPERTY()`
- L269 _public member_ `bool bCopyScale = true;` — `UPROPERTY()`
- L271 _public member_ `EPinBoneTranslationMode TranslationMode;` — `UPROPERTY()`
- L273 _public member_ `EPinBoneRotationMode RotationMode;` — `UPROPERTY()`
- L275 _public member_ `FTransform GlobalOffset;` — `UPROPERTY()`
- L277 _public member_ `FTransform LocalOffset;` — `UPROPERTY()`
- L283 _private member_ `bool bMaintainOffset_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Uses separate translation/rotation offset modes")` — `UPROPERTY()`
- L287 _private member_ `EPinBoneType PinType_DEPRECATED;` — `UE_DEPRECATED(5.6, "Uses separate translate/rotate/scale checkboxes")` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API IKRIG_API`
- L13 _macro_ `#define LOCTEXT_NAMESPACE "PinBoneOp"`
- L61 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon3990d4910103`)
- L149 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anon3990d4910203`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/RetargetCurvesOp.h` (Public)


#### struct `FIKRetargetCurvesOpBase`  
`struct FIKRetargetCurvesOpBase : public FIKRetargetOpBase`  
_L18-91_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRetargetOpBase`
- desc: This is the base class for defining all animation curves operations including curve remapping and rig mapping.
- L25 _public function_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override` — NOTE: this op does not do anything in Initialize() or Run(). In the future we may remove this coupling and make the op itself do the work via callbacks
- L36 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override`
- L43 _public function_ `virtual const UScriptStruct* GetType() const override`
- L45 _public function_ `bool CanHaveChildOps() const override`
- L47 _public function_ `virtual bool IsSingleton() const override`
- L50 _public function_ `virtual bool IsAbstract() const override` — Designator of an "abstract" base struct, in this case used to classify curve related ops
- L53 _public function_ `virtual bool HasCurveProcessing() const` — (optional) a function which returns true if the operation performs curve processing, false otherwise (default is true)
- L55 _public typedef_ `using FFrameValues = TArray<TArray<TOptional<float>>>;`
- L65 _public function_ `virtual void ProcessAnimSequenceCurves(FIKRetargetCurvesOpBase::FCurveData InCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues InCurveFrameValues, FIKRetargetCurvesOpBase::FCurveData& OutCurveMetaData, FIKRetargetCurvesOpBase::FFrameValues& OutCurveFrameValues) const` — (optional) a function which can be used during batch processing to apply any operations to curve data for each frame of an anim sequence. By default, this just moves the input data to the output data
- L73 _public function_ `void SetTakeInputCurvesFromSourceAnimInstance(bool bInTakeInputCurvesFromSourceAnimInstance)` — a function which allows the user to manually indicate whether to take source curves from the source anim instance, or from the current pose context, since only the first enabled curve processing node must take inputs from the source anim instance
- L79 _public function_ `bool GetTakeInputCurvesFromSourceAnimInstance() const` — a function which allows the user to manually indicate whether to take source curves from the source anim instance, or from the current pose context, since only the first enabled curve processing node must take inputs from the source anim instance
- L85 _public member_ `FBlendedHeapCurve SourceCurves;` — cached curves, copied on the game thread in PreUpdate()
- L90 _protected member_ `bool bTakeInputCurvesFromSourceAnimInstance = true;` — `UPROPERTY(Transient)` — (optional) determines whether input curves are taken from the source anim instance or from the current pose context (for example when we have multiple nodes which process curves). Can be set on the fly

#### struct `FIKRetargetCurvesOpBase::FCurveData`  
`struct FCurveData`  
_L57-62_
- L59 _public member_ `TArray<FName> Names;`
- L60 _public member_ `TArray<int32> Flags;`
- L61 _public member_ `TArray<FLinearColor> Colors;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "RetargetCurvesOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/RetargetOpUtils.h` (Public)


#### struct `FOneEuroFilterSettings`  
`struct FOneEuroFilterSettings`  
_L9-32_
- reflection: `USTRUCT(BlueprintType)`
- desc: These are settings for an adaptive first-order low-pass filter based on the "One-Euro" 2012 paper: https://gery.casiez.net/1euro/
- L18 _public member_ `double Responsiveness = 0.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="One Euro Filter")` — Raises the cutoff as speed grows. Larger values are snappier on fast turns. Smaller values are smoother but laggier during quick motion. Typical sweet spot: 0.3 – 0.8
- L24 _public member_ `double CutoffFrequency = 1.5;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="One Euro Filter")` — Hz. Sets the low-pass cutoff when motion is near zero. Higher = less smoothing at rest (more responsive but more jitter). Lower = more smoothing at rest (less jitter but more “stickiness”).
- L31 _public member_ `double VelocityCutoffFrequency = 20.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="One Euro Filter")` — Hz. Low-passes the raw velocity before we use it to adapt the derivative cutoff. If you see breathing/pumping of the smoothing during motion onsets or reversals, lower this value (e.g., 30 → 20 Hz). If responsiveness to fast changes is sluggish, raise this a bit. Good starting range: 15–30 Hz. Keep under Nyquist frequency (frame_rate/2).

#### struct `FOneEuroScalarFilter`  
`struct FOneEuroScalarFilter`  
_L35-54_
- desc: filter a double over time using the "One Euro" method
- L37 _public prototype_ `double Update(const double InValue, const double InDeltaTime, const FOneEuroFilterSettings& InSettings);`
- L39 _public prototype_ `void Reset(const double InValue);`
- L40 _public function_ `void Reset()`
- L42 _public prototype_ `static double AlphaFromHz(const double InDeltaTime, const double InFreqCutoffHz);`
- L44 _public prototype_ `static double ClampDeltaTime(const double InDeltaTime);`
- L46 _public prototype_ `static double ClampFreqToFramerate(const double InHz, const double InDeltaTime);`
- L50 _private member_ `double PrevValue = 0.0;`
- L51 _private member_ `double PrevRawValue = 0.0;`
- L52 _private member_ `double PrevValueDerivative = 0.0;`
- L53 _private member_ `bool bIsFirstRun = true;`

#### struct `FOneEuroVectorFilter`  
`struct FOneEuroVectorFilter`  
_L57-69_
- desc: filter a 3d vector over time using the "One Euro" method
- L59 _public prototype_ `FVector Update(const FVector& InValue, const double InDeltaTime, const FOneEuroFilterSettings& InSettings);`
- L61 _public prototype_ `void Reset(const FVector& StartingValue);`
- L62 _public prototype_ `void Reset();`
- L66 _private member_ `FOneEuroScalarFilter X;`
- L67 _private member_ `FOneEuroScalarFilter Y;`
- L68 _private member_ `FOneEuroScalarFilter Z;`

#### struct `FOneEuroQuatFilter`  
`struct FOneEuroQuatFilter`  
_L72-85_
- desc: filter a quaternion over time using the "One Euro" method
- L74 _public prototype_ `FQuat Update(const FQuat& InTargetRotation, double InDeltaTime, const FOneEuroFilterSettings& InSettings);`
- L76 _public function_ `void Reset()`
- L80 _private member_ `FQuat PrevFilteredRot = FQuat::Identity;`
- L81 _private member_ `FQuat PrevRawTarget = FQuat::Identity;`
- L82 _private member_ `FVector PrevHalfAngVel = FVector::ZeroVector;`
- L83 _private member_ `FVector PrevPhiFilt = FVector::ZeroVector;`
- L84 _private member_ `bool bIsFirstRun = true;`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/RetargetPoseOp.h` (Public)


#### struct `FIKRetargetPoseOpSettings`  
`struct FIKRetargetPoseOpSettings : public FIKRetargetOpSettingsBase`  
_L13-36_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Retarget Pose Op Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L19 _public member_ `bool bOverrideSourcePose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Source Pose")` — When true, overrides the default retarget pose for the source skeleton.
- L23 _public member_ `FName SourcePoseToUse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Source Pose")` — A retarget pose that is applied to the source skeleton. Must match the name of a retarget pose stored in this asset.
- L27 _public member_ `bool bOverrideTargetPose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target Pose")` — When true, overrides the default retarget pose for the target skeleton.
- L31 _public member_ `FName TargetPoseToUse;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target Pose")` — A retarget pose that is applied to the target skeleton. Must match the name of a retarget pose stored in this asset.
- L33 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L35 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetPoseOp`  
`struct FIKRetargetPoseOp : public FIKRetargetOpBase`  
_L39-68_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Retarget Pose"))`
- inherits: `FIKRetargetOpBase`
- L43 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L50 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L56 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L58 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L60 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L62 _public function_ `virtual bool IsSingleton() const override`
- L67 _private member_ `FIKRetargetPoseOpSettings Settings;` — `UPROPERTY()`

#### class `UIKRetargetPoseController`  
`class UIKRetargetPoseController : public UIKRetargetOpControllerBase`  
_L72-86_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Retarget Pose Op
- L80 _public prototype_ `FIKRetargetPoseOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetPoseOpSettings struct with the current settings used by the op.
- L85 _public prototype_ `void SetSettings(FIKRetargetPoseOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetPoseOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`
- L10 _macro_ `#define LOCTEXT_NAMESPACE "RetargetPoseOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/RootMotionGeneratorOp.h` (Public)


#### enum `ERootMotionSource`  
`enum class ERootMotionSource : uint8`  
_L15-19_
- reflection: `UENUM()`
- desc: where to copy the motion of the root from
- L17 _public enumerator_ `CopyFromSourceRoot`
- L18 _public enumerator_ `GenerateFromTargetPelvis`

#### enum `ERootMotionHeightSource`  
`enum class ERootMotionHeightSource : uint8`  
_L23-27_
- reflection: `UENUM()`
- desc: where to copy the height of the root from
- L25 _public enumerator_ `CopyHeightFromSource`
- L26 _public enumerator_ `SnapToGround`

#### struct `FIKRetargetRootMotionOpSettings`  
`struct FIKRetargetRootMotionOpSettings : public FIKRetargetOpSettingsBase`  
_L30-98_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Root Motion Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L36 _public member_ `FBoneReference SourceRoot;` — `UPROPERTY(EditAnywhere, Category="Bones", meta=(ReinitializeOnEdit, NotOverrideable))` — The root of the source skeleton.
- L40 _public member_ `FBoneReference TargetRoot;` — `UPROPERTY(EditAnywhere, Category="Bones", meta=(ReinitializeOnEdit, NotOverrideable))` — The root of the target skeleton.
- L47 _public member_ `ERootMotionSource RootMotionSource = ERootMotionSource::CopyFromSourceRoot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion Source")` — Where to copy the root motion from. Copy From Source Root: copies the motion from the source root bone, but scales it according to relative height difference. Generate From Target Pelvis: uses the retargeted Pelvis motion to generate root motion. NOTE: Generating root motion from the Pelvis
- L51 _public member_ `FBoneReference TargetPelvis;` — `UPROPERTY(EditAnywhere, Category="Motion Source", meta=(ReinitializeOnEdit, NotOverrideable))` — The pelvis of the target skeleton. Only used when "Root Motion Source" is set to target pelvis.
- L57 _public member_ `bool bRotateWithPelvis = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion Source")` — Applies only when generating root motion from the Pelvis. When true, the applied offset will be rotated by the Pelvis. (NOTE: This may cause unwanted rotations, for example if Pelvis Yaw is animated.)
- L63 _public member_ `ERootMotionHeightSource RootHeightSource = ERootMotionHeightSource::CopyHeightFromSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Height Source")` — How to set the height of the root bone. Copy Height From Source: copies the height of the root bone on the source skeleton's root bone. Snap To Ground: sets the root bone height to the ground plane (Z=0).
- L67 _public member_ `FTransform GlobalOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset")` — A manual offset to apply in global space to the root bone.
- L73 _public member_ `bool bMaintainOffsetFromPelvis = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Offset")` — Applies only when generating root motion from the Pelvis. Maintains the offset between the root and pelvis as recorded in the target retarget pose. If false, the root bone is placed directly under the Pelvis bone.
- L77 _public member_ `bool bPropagateToNonRetargetedChildren = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Update Children")` — Will transform all children of the target root that are not themselves part of a retarget chain.
- L79 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L81 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L85 _public prototype_ `virtual USkeleton* GetSkeleton(const FName InPropertyName) override;`
- L90 _public member_ `FName SourceRootBone_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))` — Changed to FBoneReference to support bone selector UI
- L92 _public member_ `FName TargetRootBone_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L94 _public member_ `FName TargetPelvisBone_DEPRECATED;` — `UPROPERTY(meta=(DeprecatedProperty))`
- L96 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L97 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetRootMotionOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetRootMotionOpSettings>`  
_L101-104_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetRootMotionOpSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L103-103_

#### struct `FIKRetargetRootMotionOp`  
`struct FIKRetargetRootMotionOp : public FIKRetargetOpBase`  
_L107-169_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Root Motion"))`
- inherits: `FIKRetargetOpBase`
- L111 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L118 _public prototype_ `virtual void Run( FIKRetargetProcessor& Processor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L124 _public prototype_ `virtual void PostInitialize( const FIKRetargetProcessor& Processor, const FRetargetSkeleton& SourceSkeleton, const FTargetSkeleton& TargetSkeleton, FIKRigLogger& Log) override;`
- L130 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L132 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L134 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L136 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L139 _public member_ `FIKRetargetRootMotionOpSettings Settings;` — `UPROPERTY()`
- L142 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L147 _private prototype_ `void Reset();`
- L149 _private prototype_ `void GenerateRootMotionFromTargetPelvis( FTransform& OutRootTransform, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& InTargetGlobalPose) const;`
- L154 _private prototype_ `void CopyRootMotionFromSourceRoot( FTransform& OutRootTransform, const FIKRetargetProcessor& Processor, const TArray<FTransform>& InSourceGlobalPose) const;`
- L159 _private member_ `int32 SourceRootIndex = INDEX_NONE;`
- L160 _private member_ `int32 TargetRootIndex = INDEX_NONE;`
- L161 _private member_ `int32 TargetPelvisIndex = INDEX_NONE;`
- L163 _private member_ `FTransform TargetPelvisRelativeToTargetRootRefPose;`
- L164 _private member_ `FTransform TargetPelvisInRefPose;`
- L165 _private member_ `FTransform SourceRootInRefPose;`
- L166 _private member_ `FTransform TargetRootInRefPose;`
- L168 _private member_ `TArray<int32> NonRetargetedChildrenOfRoot;`

#### class `UIKRetargetRootMotionController`  
`class UIKRetargetRootMotionController : public UIKRetargetOpControllerBase`  
_L173-221_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Root Motion Op
- L181 _public prototype_ `FIKRetargetRootMotionOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRootMotionOpSettings struct with the current settings used by the op.
- L186 _public prototype_ `void SetSettings(FIKRetargetRootMotionOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetRootMotionOpSettings struct containing all the settings to apply to this op
- L191 _public prototype_ `void SetSourceRootBone(const FName InSourceRootBone);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the root bone for the source. @param InSourceRootBone the name of the root bone on the source skeleton.
- L196 _public prototype_ `FName GetSourceRootBone();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the root bone for the source. @return the name of the root bone on the source skeleton.
- L201 _public prototype_ `void SetTargetRootBone(const FName InTargetRootBone);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the root bone for the target. @param InTargetRootBone the name of the root bone on the target skeleton.
- L206 _public prototype_ `FName GetTargetRootBone();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the root bone for the target. @return the name of the root bone on the target skeleton.
- L211 _public prototype_ `void SetTargetPelvisBone(const FName InTargetPelvisBone);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the pelvis bone for the target. @param InTargetPelvisBone the name of the pelvis bone on the target skeleton.
- L216 _public prototype_ `FName GetTargetPelvisBone();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the pelvis bone for the target. @return the name of the pelvis bone on the target skeleton.
- L220 _private prototype_ `FIKRetargetRootMotionOpSettings* GetSettingsPtr() const;`

#### class `URootMotionGeneratorOp`  
`class URootMotionGeneratorOp : public URetargetOpBase`  
_L229-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URetargetOpBase`
- desc: NOTE: This type has been replaced with FIKRetargetRootMotionOp.
- L235 _public prototype_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override;`
- L238 _public member_ `FName SourceRootBone;` — `UPROPERTY()`
- L240 _public member_ `FName TargetRootBone;` — `UPROPERTY()`
- L242 _public member_ `FName TargetPelvisBone;` — `UPROPERTY()`
- L244 _public member_ `ERootMotionSource RootMotionSource;` — `UPROPERTY()`
- L246 _public member_ `ERootMotionHeightSource RootHeightSource;` — `UPROPERTY()`
- L248 _public member_ `bool bPropagateToNonRetargetedChildren = true;` — `UPROPERTY()`
- L250 _public member_ `bool bMaintainOffsetFromPelvis = true;` — `UPROPERTY()`
- L252 _public member_ `bool bRotateWithPelvis = false;` — `UPROPERTY()`
- L254 _public member_ `FTransform GlobalOffset;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "URootMotionGeneratorOp"`
- L103 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anoned1edc670103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/RunIKRigOp.h` (Public)


#### struct `FIKRetargetRunIKRigChainSettings`  
`struct FIKRetargetRunIKRigChainSettings`  
_L19-71_
- reflection: `USTRUCT(BlueprintType)`
- L23 _public prototype_ `FIKRetargetRunIKRigChainSettings() = default;`
- L24 _public function_ `FIKRetargetRunIKRigChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L25 _public prototype_ `bool operator==(const FIKRetargetRunIKRigChainSettings& Other) const;`
- L26 _public function_ `FName GetName() const`
- L27 _public function_ `void SetName(const FName InName)`
- L31 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain to run IK on.
- L36 _public member_ `bool bEnableIK = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta=(ReinitializeOnEdit))` — Enable/disable IK on this chain. NOTE: This actually removes the goal from the internal IK Rig solve and triggers a reinitialization of the solver stack when toggled.
- L43 _public member_ `double ChainPositionAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bEnableIK"))` — Range 0 to 1. Default 1. Retargets the goal position based on the source chain length and direction. At 0, the goal is left at the input pose bone location. At 1, the goal is translated in the direction of the source chain, at a distance from the base of the chain proportional to how much it is compressed or stretched.
- L52 _public member_ `double ChainRotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bEnableIK"))` — Range 0 to 1. Default 1. Retargets the goal rotation based on the source chain end bone rotation. At 0, the goal is left at the input pose bone rotation. At 1, the goal is rotated by the same world space rotation applied to the source chain end bone. NOTE: if the target end bone rotation was already retargeted before this op, this setting may have no effect. It will not double-rotate the goal. This setting is useful if no FK retargeting is being performed on this chain before the IK op.
- L56 _public member_ `bool bOverrideGoalAlpha = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta=(ReinitializeOnEdit, EditCondition = "bEnableIK"))` — Default false. If true, the alpha values here will override the goal alpha settings from the IK Rig asset.
- L63 _public member_ `double FinalPositionAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bEnableIK && bOverrideGoalAlpha"))` — Range 0 to 1. Default 1. Blends all goal translation offsets on/off. At 0, the goal is left at the input pose bone location. At 1, the goal is moved to the location generated by the IK goal ops.
- L70 _public member_ `double FinalRotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bEnableIK && bOverrideGoalAlpha"))` — Range 0 to 1. Default 1. Blends all goal rotation offsets on/off. At 0, the goal is left at the input pose bone rotation. At 1, the goal is rotated to the orientation generated by the IK goal ops.

#### struct `FIKRetargetRunIKRigOpSettings`  
`struct FIKRetargetRunIKRigOpSettings : public FIKRetargetOpSettingsBase`  
_L74-104_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Solve IK Goal Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L79 _public member_ `TArray<FIKRetargetRunIKRigChainSettings> Chains;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L83 _public member_ `TObjectPtr<const UIKRigDefinition> IKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Rig Asset", meta=(ReinitializeOnEdit))` — The IK Rig asset to run when this op is executed.
- L87 _public member_ `bool bDrawGoals = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Draw IK goal locations.
- L91 _public member_ `bool bDrawGoalBoneLocations = true;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Draw locations of the source bone (pre-solve)
- L95 _public member_ `double GoalDrawSize = 5.0;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Adjust size of goal debug drawing in viewport
- L99 _public member_ `double GoalDrawThickness = 1.0;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Adjust thickness of goal debug drawing in viewport
- L101 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L103 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FRunIKRigChain`  
`struct FRunIKRigChain`  
_L106-130_
- L108 _public prototype_ `FRunIKRigChain( const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain, const FIKRetargetRunIKRigChainSettings& InSettings, FIKRigLogger& InLog);`
- L114 _public prototype_ `void Run( FIKRigGoalContainer& InGoalContainer, const TArray<FTransform>& InSourceGlobalPose, const TArray<FTransform>& InTargetGlobalPose, const FIKRetargetRunIKRigOpSettings& InOpSettings, const FIKRetargetPelvisMotionOp* InPelvisMotionOp) const;`
- L121 _public prototype_ `void SetGoalAlpha(FIKRigGoalContainer& InGoalContainer);`
- L124 _public member_ `bool bIsReady = false;` — cached data
- L125 _public member_ `const FResolvedBoneChain* SourceBoneChain = nullptr;`
- L126 _public member_ `const FResolvedBoneChain* TargetBoneChain = nullptr;`
- L127 _public member_ `const FIKRetargetRunIKRigChainSettings* Settings = nullptr;`
- L128 _public member_ `double InvInitialLengthSource = 1.0f;`
- L129 _public member_ `double InitialTargetChainLength = 1.0f;`

#### struct `FRunIKRigOpGoalDebugData`  
`struct FRunIKRigOpGoalDebugData`  
_L133-138_
- L135 _public member_ `FName GoalName;`
- L136 _public member_ `FTransform InitialGoal;`
- L137 _public member_ `FTransform CurrentGoal;`

#### struct `FIKRetargetRunIKRigOp`  
`struct FIKRetargetRunIKRigOp : public FIKRetargetOpBase`  
_L142-243_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Run IK Rig"))`
- inherits: `FIKRetargetOpBase`
- L146 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L153 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L159 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L161 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L163 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L165 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L167 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L169 _public function_ `virtual bool CanHaveChildOps() const override`
- L171 _public prototype_ `virtual void InitializeBeforeChildren( FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, FIKRigLogger& Log) override;`
- L177 _public prototype_ `virtual void RunBeforeChildren( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L183 _public prototype_ `virtual const UIKRigDefinition* GetCustomTargetIKRig() const override;`
- L185 _public prototype_ `virtual FRetargetChainMapping* GetChainMapping() override;`
- L187 _public prototype_ `virtual void OnReinitPropertyEdited(const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L190 _public prototype_ `static bool ValidateIKChain( const FName& InChainToValidate, const FIKRigGoalContainer& InGoalContainer, const FRetargeterBoneChains& InBoneChains, const FIKRetargetOpBase* InOp, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog, const FResolvedBoneChain*& OutSourceBoneChain, const FResolvedBoneChain*& OutTargetBoneChain);` — a helper function that sub-ops can use to validate IK chains before use
- L201 _public member_ `FIKRetargetRunIKRigOpSettings Settings;` — `UPROPERTY()`
- L205 _public member_ `FRetargetChainMapping ChainMapping;` — `UPROPERTY()` — This op maintains its own chain mapping table to allow per-op mapping
- L209 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L216 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L217 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L218 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L220 _public function_ `virtual bool HasDebugDrawing() override`
- L222 _public prototype_ `void SaveInitialGoalTransformsIntoDebugData(const FIKRetargetProcessor& InProcessor, const TArray<FTransform>& InTargetGlobalPose);`
- L224 _public prototype_ `void SaveCurrentGoalTransformsIntoDebugData();`
- L226 _public member_ `TArray<FRunIKRigOpGoalDebugData> GoalDebugData;`
- L227 _public member_ `static FCriticalSection DebugDataMutex;`
- L230 _public prototype_ `TArray<FName> GetRequiredTargetChains() const;`
- L231 _public prototype_ `void RegenerateChainSettings();`
- L235 _private prototype_ `void ResetGoalContainer(const TArray<FTransform> &InTargetGlobalPose, FIKRigGoalContainer& InOutGoalContainer);`
- L237 _private member_ `TArray<FRunIKRigChain> Chains;`
- L240 _private member_ `FIKRigProcessor IKRigProcessor;` — The IK Rig processor for running IK on the target
- L242 _private member_ `TMap<FName, int32> GoalBoneIndicesMap;`

#### class `UIKRetargetRunIKRigController`  
`class UIKRetargetRunIKRigController : public UIKRetargetOpControllerBase`  
_L247-261_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Run IK Rig Op
- L255 _public prototype_ `FIKRetargetRunIKRigOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetRunIKRigOpSettings struct with the current settings used by the op.
- L260 _public prototype_ `void SetSettings(FIKRetargetRunIKRigOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetRunIKRigOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "RunIKRigOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/ScaleGoalsOp.h` (Public)


#### struct `FIKRetargetScaleGoalsChainSettings`  
`struct FIKRetargetScaleGoalsChainSettings`  
_L15-44_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public prototype_ `FIKRetargetScaleGoalsChainSettings() = default;`
- L20 _public function_ `FIKRetargetScaleGoalsChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L21 _public prototype_ `bool operator==(const FIKRetargetScaleGoalsChainSettings& Other) const;`
- L22 _public function_ `FName GetName() const`
- L23 _public function_ `void SetName(const FName InName)`
- L27 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain for these settings.
- L31 _public member_ `double ScaleVertical = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "2.0"))` — Range 0 to infinity. Default 1. Scales the vertical component of the IK goal's position.
- L35 _public member_ `double ScaleHorizontal = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "2.0"))` — Range 0 to infinity. Default 1. Scales the horizontal component of the IK goal's position.
- L43 _public member_ `double ScaleAlongChain = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "2.0"))` — Range 0 to infinity. Default 1. Brings IK goal closer (0) or further (1+) from origin of chain. At 0 the effector is placed at the origin of the chain (ie Shoulder, Hip etc). At 1 the effector is left at the end of the chain (ie Wrist, Foot etc) Values in-between 0-1 will slide the effector along the vector from the start to the end of the chain. Values greater than 1 will stretch the chain beyond the retargeted length.

#### struct `FIKRetargetScaleGoalsOpSettings`  
`struct FIKRetargetScaleGoalsOpSettings : public FIKRetargetOpSettingsBase`  
_L47-61_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scale Goals Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L52 _public member_ `TArray<FIKRetargetScaleGoalsChainSettings> Chains;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L56 _public member_ `double Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0 to 1. Default 1. Blend the effect on all chains on/off.
- L58 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L60 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKChainToScale`  
`struct FIKChainToScale`  
_L63-82_
- L65 _public prototype_ `FIKChainToScale() = delete;`
- L66 _public function_ `FIKChainToScale( const FResolvedBoneChain& InTargetBoneChain, const FIKRetargetScaleGoalsChainSettings& InSettings) : TargetBoneChain(&InTargetBoneChain) , Settings(&InSettings)`
- L72 _public prototype_ `void Run( FIKRigGoalContainer& InGoalContainer, const TArray<FTransform>& InTargetGlobalPose, const FIKRetargetScaleGoalsOpSettings& InOpSettings) const;`
- L80 _private member_ `const FResolvedBoneChain* TargetBoneChain;` — cached data
- L81 _private member_ `const FIKRetargetScaleGoalsChainSettings* Settings;`

#### struct `FIKRetargetScaleGoalsOp`  
`struct FIKRetargetScaleGoalsOp : public FIKRetargetOpBase`  
_L85-139_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scale Goals"))`
- inherits: `FIKRetargetOpBase`
- L89 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L96 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L102 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L104 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L106 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L108 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L110 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L112 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L114 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L116 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L119 _public member_ `FIKRetargetScaleGoalsOpSettings Settings;` — `UPROPERTY()`
- L123 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L129 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L130 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L131 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L134 _public prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L138 _private member_ `TArray<FIKChainToScale> ChainsToScale;`

#### class `UIKRetargetScaleGoalsController`  
`class UIKRetargetScaleGoalsController : public UIKRetargetOpControllerBase`  
_L143-157_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Scale Goals Op
- L151 _public prototype_ `FIKRetargetScaleGoalsOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetScaleGoalsOpSettings struct with the current settings used by the op.
- L156 _public prototype_ `void SetSettings(FIKRetargetScaleGoalsOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetScaleGoalsOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API IKRIG_API`
- L9 _macro_ `#define LOCTEXT_NAMESPACE "ScaleGoalsOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/ScaleSourceOp.h` (Public)


#### enum `EScaleSourcePivot`  
`enum class EScaleSourcePivot : uint8`  
_L14-18_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `ComponentOrigin UMETA(DisplayName = "Component Origin")`
- L17 _public enumerator_ `Bone UMETA(DisplayName = "Bone")`

#### struct `FIKRetargetScaleSourceOpSettings`  
`struct FIKRetargetScaleSourceOpSettings : public FIKRetargetOpSettingsBase`  
_L21-45_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scale Source Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L27 _public member_ `double SourceScaleFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ReinitializeOnEdit, ClampMin = "0.01", UIMin = "0.01", UIMax = "10.0"))` — Range 0.01 to +inf. Default 1. Scales the incoming source pose. Affects entire skeleton and all IK goals.
- L30 _public member_ `EScaleSourcePivot ScalePivot = EScaleSourcePivot::ComponentOrigin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")`
- L33 _public member_ `FBoneReference ScalePivotBone;` — `UPROPERTY(EditAnywhere, Category = "Op Settings", meta=(NotOverrideable))`
- L36 _public member_ `bool bProjectScalePivotToFloor = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")`
- L38 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L40 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L43 _public prototype_ `virtual USkeleton* GetSkeleton(const FName InPropertyName) override;`

#### struct `FIKRetargetScaleSourceOp`  
`struct FIKRetargetScaleSourceOp : public FIKRetargetOpBase`  
_L48-86_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Scale Source"))`
- inherits: `FIKRetargetOpBase`
- L55 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& Log) override;`
- L62 _public function_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override`
- L68 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L70 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L72 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L74 _public function_ `virtual bool IsSingleton() const override`
- L76 _public prototype_ `int32 GetScalePivotBoneIndex(const FRetargetSkeleton& InSourceSkeleton) const;`
- L79 _public member_ `FIKRetargetScaleSourceOpSettings Settings;` — `UPROPERTY()`
- L84 _private member_ `mutable int32 CachedScalePivotBoneIndex = INDEX_NONE;` — caching the bone index to scale the source from
- L85 _private member_ `mutable FName CachedScalePivotBoneName = NAME_None;`

#### class `UIKRetargetScaleSourceController`  
`class UIKRetargetScaleSourceController : public UIKRetargetOpControllerBase`  
_L90-104_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Scale Source Op
- L98 _public prototype_ `FIKRetargetScaleSourceOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetScaleSourceOpSettings struct with the current settings used by the op.
- L103 _public prototype_ `void SetSettings(FIKRetargetScaleSourceOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetScaleSourceOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "ScaleSourceOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/SpeedPlantingOp.h` (Public)


#### struct `FRetargetSpeedPlantingSettings`  
`struct FRetargetSpeedPlantingSettings`  
_L16-39_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FRetargetSpeedPlantingSettings() = default;`
- L21 _public function_ `FRetargetSpeedPlantingSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L26 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Planting", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the target chain to plant the IK on. NOTE: this chain must have an IK Goal assigned to it!
- L30 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the speed planting on this chain only. At 0, there is no effect.
- L34 _public member_ `FName SpeedCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintReadWrite, Category = "Chain Settings", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0"))` — The name of the curve on the source animation that contains the speed of the end effector bone.
- L36 _public prototype_ `bool operator==(const FRetargetSpeedPlantingSettings& Other) const;`
- L37 _public function_ `FName GetName() const`
- L38 _public function_ `void SetName(const FName InName)`

#### enum `ESpeedPlantBlendMethod`  
`enum class ESpeedPlantBlendMethod : uint8`  
_L42-46_
- reflection: `UENUM(BlueprintType)`
- L44 _public enumerator_ `Spring`
- L45 _public enumerator_ `MoveTowards`

#### struct `FIKRetargetSpeedPlantingOpSettings`  
`struct FIKRetargetSpeedPlantingOpSettings : public FIKRetargetOpSettingsBase`  
_L49-110_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Speed Plant Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L54 _public member_ `TArray<FRetargetSpeedPlantingSettings> ChainsToSpeedPlant;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))`
- L58 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the speed planting. At 0, there is no effect.
- L63 _public member_ `double SpeedThreshold = 15.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "100.0"))` — Range 0 to 100. Default 15. The maximum speed a source bone can be moving while being considered 'planted'. The target IK goal will not be allowed to move whenever the source bone speed drops below this threshold speed.
- L69 _public member_ `ESpeedPlantBlendMethod BlendMethod = ESpeedPlantBlendMethod::Spring;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — The method to use when blending the IK goal in/out of a planted position. The Spring method uses a critically damped spring equation to blend into and out of the planted states. The Move Towards method can more accurately track fast motion without looking mushy. It only blends out of planted states.
- L75 _public member_ `double MaxBlendSpeed = 900.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "2000.0", EditCondition = "BlendMethod == ESpeedPlantBlendMethod::MoveTowards", EditConditionHides))` — The maximum speed in cm/s that the goal will move to catch up to the animation after unplanting. This blended towards the animated velocity as the goal catches up to animated location after unplanting.
- L80 _public member_ `double TimeToMaxSpeed = 0.2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.001", UIMin = "0.01", UIMax = "1.0", EditCondition = "BlendMethod == ESpeedPlantBlendMethod::MoveTowards", EditConditionHides))` — Seconds to reach MaxBlendSpeed. Determines how rapidly the goal accelerates after unplanting.
- L88 _public member_ `double ArrivalSpeedGain = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.001", UIMin = "0.01", UIMax = "20.0", EditCondition = "BlendMethod == ESpeedPlantBlendMethod::MoveTowards", EditConditionHides))` — Controls how aggressively the goal velocity matches the animated velocity as it arrives at the animated location after unplanting. This allows the goal speed to gradually blend towards the target speed as the goal location approaches the animated location. Reduce this to remove velocity discontinuities when catching up to the animation. 1.0 is very soft, 20.0 is very sharp. Default is 10.0.
- L95 _public member_ `double SpringStrength = 3.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta=(Input, ClampMin = "0.0", UIMin = "0.0", UIMax = "30.0", EditCondition = "BlendMethod == ESpeedPlantBlendMethod::Spring", EditConditionHides))` — The spring strength determines how hard it will pull towards the target when planting and unplanting. The value is the frequency (hz) at which it will oscillate when there is no damping.
- L98 _public member_ `double Stiffness = 250.0f;` — `UPROPERTY(meta=(DeprecatedProperty))` — Deprecated in 5.8, replaced with higher-level "Strength" param
- L102 _public member_ `double DebugDrawSize = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "10.0"))` — Adjust size of goal debug drawing in viewport. Red is planted, green is unplanted.
- L104 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L106 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L109 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;` — Custom override to load old "Stiffness" as new "Strength"

#### struct `FSpeedPlantingGoalState`  
`struct FSpeedPlantingGoalState`  
_L112-144_
- L114 _public function_ `FSpeedPlantingGoalState( const FName InGoalName, const FRetargetSpeedPlantingSettings* InSettings) : GoalName(InGoalName), Settings(InSettings)`
- L120 _public prototype_ `void Update( FIKRigGoal* IKRigGoal, const double InDeltaTime, const FIKRetargetSpeedPlantingOpSettings& InSettings);`
- L125 _public prototype_ `void Reset();`
- L127 _public member_ `FName GoalName;`
- L128 _public member_ `const FRetargetSpeedPlantingSettings* Settings;`
- L129 _public member_ `FVectorSpringState PositionSpringState;`
- L130 _public member_ `FVector CurrentPosition;`
- L131 _public member_ `FVector TargetPosition;`
- L132 _public member_ `FVector LastTargetPosition;`
- L133 _public member_ `double CurrentSpeedValue = -1.0f;`
- L134 _public member_ `bool bIsPlanted = false;`
- L135 _public member_ `bool bWasReset = true;`
- L136 _public member_ `FVector PlantLocation;`
- L137 _public member_ `double AccelerationTimer = 0.0;`
- L138 _public member_ `bool bIsTrackingTarget = true;`
- L141 _public member_ `bool bFoundCurveInSourceComponent = false;`
- L142 _public member_ `bool bFoundCurveInTargetComponent = false;`

#### struct `FIKRetargetSpeedPlantingOp`  
`struct FIKRetargetSpeedPlantingOp : public FIKRetargetOpBase`  
_L147-212_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Speed Plant IK Goals"))`
- inherits: `FIKRetargetOpBase`
- L151 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L158 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L164 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L166 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L168 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L170 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L172 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L174 _public prototype_ `virtual void OnPlaybackReset() override;`
- L176 _public prototype_ `virtual void AnimGraphPreUpdateMainThread(USkeletalMeshComponent& SourceMeshComponent, USkeletalMeshComponent& TargetMeshComponent) override;`
- L178 _public prototype_ `virtual void AnimGraphEvaluateAnyThread(FPoseContext& Output) override;`
- L180 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L182 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L184 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L187 _public prototype_ `TArray<FName> GetRequiredSpeedCurves() const;` — return array of names of all the speed curves referenced by this op.
- L190 _public member_ `FIKRetargetSpeedPlantingOpSettings Settings;` — `UPROPERTY()`
- L194 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L200 _public function_ `virtual bool HasDebugDrawing() override`
- L201 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L202 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L203 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L204 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L209 _private prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L211 _private member_ `TArray<FSpeedPlantingGoalState> GoalsToPlant;`

#### class `UIKRetargetSpeedPlantingController`  
`class UIKRetargetSpeedPlantingController : public UIKRetargetOpControllerBase`  
_L216-230_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Speed Planting Op
- L224 _public prototype_ `FIKRetargetSpeedPlantingOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetSpeedPlantingOpSettings struct with the current settings used by the op.
- L229 _public prototype_ `void SetSettings(FIKRetargetSpeedPlantingOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetSpeedPlantingOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "SpeedPlantingOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/StretchChainOp.h` (Public)


#### struct `FChainStretcher`  
`struct FChainStretcher`  
_L16-37_
- L18 _public prototype_ `FChainStretcher( const FRetargetStretchChainSettings* InSettings, const FResolvedBoneChain& InSourceBoneChain, const FResolvedBoneChain& InTargetBoneChain);`
- L23 _public prototype_ `void Initialize(const FRetargetSkeleton& InTargetSkeleton);`
- L25 _public prototype_ `void StretchChain( const TArray<FTransform> &InSourceGlobalPose, const FRetargetSkeleton& InTargetSkeleton, TArray<FTransform> &OutTargetGlobalPose);`
- L32 _private member_ `bool bIsInitialized = false;`
- L33 _private member_ `TArray<int32> AllChildrenOfChain;`
- L34 _private member_ `const FRetargetStretchChainSettings* Settings;`
- L35 _private member_ `const FResolvedBoneChain* SourceBoneChain;`
- L36 _private member_ `const FResolvedBoneChain* TargetBoneChain;`

#### struct `FRetargetStretchChainSettings`  
`struct FRetargetStretchChainSettings`  
_L40-68_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public prototype_ `FRetargetStretchChainSettings() = default;`
- L45 _public function_ `FRetargetStretchChainSettings(FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L49 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the target chain to stretch.
- L53 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings")` — Enable/disable stretching.
- L59 _public member_ `double MatchSourceLength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (EditCondition = "bEnabled", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 0. Matches the total length of this chain with the mapped source chain. At 0, the chain's length will be left alone At 1, the chain will be stretched to match the length of the source.
- L63 _public member_ `double ScaleChainLength = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (EditCondition = "bEnabled", UIMin = "0.0", UIMax = "5.0", ClampMin = "0.0"))` — Range 0 to inf. Default 1. A multiplier on the length of the chain, applied after matching the source length.
- L65 _public prototype_ `bool operator==(const FRetargetStretchChainSettings& Other) const;`
- L66 _public function_ `FName GetName() const`
- L67 _public function_ `void SetName(const FName InName)`

#### struct `FIKRetargetStretchChainOpSettings`  
`struct FIKRetargetStretchChainOpSettings : public FIKRetargetOpSettingsBase`  
_L71-85_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Stretch Chain Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L77 _public member_ `TObjectPtr<const UIKRigDefinition> IKRigAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK Rig Asset", meta=(ReinitializeOnEdit))` — The target IK Rig asset that contains the bones chains this op will modify.
- L80 _public member_ `TArray<FRetargetStretchChainSettings> ChainsToStretch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(TitleProperty="TargetChainName"))`
- L82 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L84 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### struct `FIKRetargetStretchChainOp`  
`struct FIKRetargetStretchChainOp : public FIKRetargetOpBase`  
_L88-142_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Stretch Chains"))`
- inherits: `FIKRetargetOpBase`
- L92 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L99 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L105 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L107 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L109 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L111 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L113 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L115 _public prototype_ `virtual const UIKRigDefinition* GetCustomTargetIKRig() const override;`
- L117 _public prototype_ `virtual FRetargetChainMapping* GetChainMapping() override;`
- L119 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L121 _public prototype_ `virtual void OnReinitPropertyEdited(const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L124 _public prototype_ `virtual FText GetWarningMessage() const override;`
- L125 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L126 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L127 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L131 _public member_ `FIKRetargetStretchChainOpSettings Settings;` — `UPROPERTY()`
- L135 _public member_ `FRetargetChainMapping ChainMapping;` — `UPROPERTY()` — This op maintains its own chain mapping table to allow per-op mapping
- L139 _private prototype_ `void ApplyIKRigs(const UIKRigDefinition* InSourceIKRig, const UIKRigDefinition* InTargetIKRig);`
- L141 _private member_ `TArray<FChainStretcher> ChainStretchers;`

#### class `UIKRetargetStretchChainController`  
`class UIKRetargetStretchChainController : public UIKRetargetOpControllerBase`  
_L146-160_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing an Align Pole Vector Op
- L154 _public prototype_ `FIKRetargetStretchChainOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetStretchChainOpSettings struct with the current settings used by the op.
- L159 _public prototype_ `void SetSettings(FIKRetargetStretchChainOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetStretchChainOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`
- L11 _macro_ `#define LOCTEXT_NAMESPACE "StretchChainOp"`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/StrideWarpingOp.h` (Public)


#### enum `EWarpingDirectionSource`  
`enum class EWarpingDirectionSource`  
_L15-20_
- reflection: `UENUM()`
- L17 _public enumerator_ `Goals`
- L18 _public enumerator_ `Chain`
- L19 _public enumerator_ `RootBone`

#### struct `FRetargetStrideWarpChainSettings`  
`struct FRetargetStrideWarpChainSettings`  
_L23-45_
- reflection: `USTRUCT(BlueprintType)`
- L27 _public prototype_ `FRetargetStrideWarpChainSettings() = default;`
- L28 _public function_ `FRetargetStrideWarpChainSettings(const FName InTargetChainName) : TargetChainName(InTargetChainName)`
- L32 _public member_ `FName TargetChainName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta=(ReinitializeOnEdit, NotOverrideable))` — The name of the TARGET chain with an IK goal to warp.
- L36 _public member_ `bool EnableStrideWarping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta=(ReinitializeOnEdit))` — Whether to warp the location of the IK goal on this chain. Default is true.
- L40 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chain Settings", meta = (EditCondition = "EnableStrideWarping", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the stride warping on this chain only. At 0, there is no effect.
- L42 _public prototype_ `bool operator==(const FRetargetStrideWarpChainSettings& Other) const;`
- L43 _public function_ `FName GetName() const`
- L44 _public function_ `void SetName(const FName InName)`

#### struct `FIKRetargetStrideWarpingOpSettings`  
`struct FIKRetargetStrideWarpingOpSettings : public FIKRetargetOpSettingsBase`  
_L48-117_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Stride Warp Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L54 _public member_ `TArray<FRetargetStrideWarpChainSettings> ChainSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chains, meta=(ReinitializeOnEdit, TitleProperty="TargetChainName"))` — The chains to apply stride warping to
- L58 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of all stride warping on/off. At 0, there is no effect.
- L69 _public member_ `EWarpingDirectionSource DirectionSource = EWarpingDirectionSource::Goals;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — Defines the source used to determine the forward direction as the character animates in world space. Default is "Goals". This method uses various positions on the character to create a "best fit" global rotation that approximates the facing direction of the character over time. This global rotation is used to define the forward and sideways directions used when warping goals along those axes. The options are: Goals: uses the positions of the IK goals to approximate the facing direction. This is best used on characters with a vertical spine, like bipeds. Chain: uses the positions of the bones in a retarget chain to approximate the facing direction. This is best when used with the spine chain for characters with a horizontal spine, like quadrupeds. Root Bone: uses the rotation of the root bone of the skeleton. This is most robust, but character must have correct root motion with yaw rotation in movement direction.
- L73 _public member_ `EBasicAxis ForwardDirection = EBasicAxis::Y;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — The world space axis that represents the forward facing direction for your character. By default, in Unreal, this is +Y.
- L78 _public member_ `FName DirectionChain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta=(EditCondition="DirectionSource == EWarpingDirectionSource::Chain"))` — When using the "Chain" option as a Direction Source, this defines the chain to use to determine the facing direction of the character. Typically this would be the chain that contains the Spine bones.
- L83 _public member_ `double WarpForwards = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "0.0", UIMax = "5.0", ClampMin = "0.0"))` — Range 0 to Inf. Default 1. Warps IK goal positions in the forward direction. Useful for stride warping. Values below 1 will create smaller, squashed strides. Values greater than 1 will create stretched, longer strides.
- L88 _public member_ `double SidewaysOffset = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "-10.0", UIMax = "100.0"))` — Range -+Inf. Default is 0. A static offset in world units to move the IK goals perpendicular to the forward direction. Values less than zero will move the goals towards the center-line of the character. Values greater than zero push the goals outwards.
- L94 _public member_ `double WarpSplay = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "0.0", UIMax = "2.0", ClampMin = "0.0"))` — Range 0 to +Inf. Default is 1.0f. Values below 1 pull all the goals towards the average of all the goals (towards each other). Values greater than 1 push the goals apart.
- L98 _public member_ `double DebugDrawSize = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Adjust the size of the debug drawing
- L102 _public member_ `double DebugDrawThickness = 5.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")` — Adjust the thickness of the debug drawing
- L104 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L106 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`
- L108 _public prototype_ `static FVector GetAxisVector(const EBasicAxis& Axis);`
- L110 _public prototype_ `bool operator==(const FIKRetargetStrideWarpingOpSettings& Other) const;`
- L113 _public member_ `bool bEnableDebugDraw_DEPRECATED = true;` — `UPROPERTY(meta = (DeprecatedProperty))`
- L115 _public prototype_ `virtual void PostLoad(const FIKRigObjectVersion::Type InVersion) override;`
- L116 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FIKRetargetStrideWarpingOpSettings> : public TStructOpsTypeTraitsBase2<FIKRetargetStrideWarpingOpSettings>`  
_L120-123_
- inherits: `TStructOpsTypeTraitsBase2<FIKRetargetStrideWarpingOpSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L122-122_

#### struct `FStrideWarpGoalData`  
`struct FStrideWarpGoalData`  
_L125-138_
- L127 _public function_ `FStrideWarpGoalData( const FName InGoalName, const FTransform& InGlobalRefPoseOfGoalBone, const FRetargetStrideWarpChainSettings& InChainSettings) : IKRigGoalName(InGoalName), GlobalRefPoseOfGoalBone(InGlobalRefPoseOfGoalBone), Settings(&InChainSettings)`
- L135 _public member_ `FName IKRigGoalName;`
- L136 _public member_ `FTransform GlobalRefPoseOfGoalBone;`
- L137 _public member_ `const FRetargetStrideWarpChainSettings* Settings;`

#### struct `FIKRetargetStrideWarpingOp`  
`struct FIKRetargetStrideWarpingOp : public FIKRetargetOpBase`  
_L141-200_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Stride Warp IK Goals"))`
- inherits: `FIKRetargetOpBase`
- L145 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L152 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L158 _public prototype_ `virtual void OnAddedToStack(const UIKRetargeter* InRetargetAsset, const FIKRetargetOpBase* InParentOp) override;`
- L160 _public prototype_ `virtual void OnAssignIKRig(const ERetargetSourceOrTarget SourceOrTarget, const UIKRigDefinition* InIKRig, const FIKRetargetOpBase* InParentOp) override;`
- L162 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L164 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L166 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L168 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L170 _public prototype_ `virtual void OnTargetChainRenamed(const FName InOldChainName, const FName InNewChainName) override;`
- L172 _public prototype_ `virtual void OnParentReinitPropertyEdited(const FIKRetargetOpBase& InParentOp, const FPropertyChangedEvent* InPropertyChangedEvent) override;`
- L175 _public member_ `FIKRetargetStrideWarpingOpSettings Settings;` — `UPROPERTY()`
- L179 _public prototype_ `virtual void DebugDraw( FPrimitiveDrawInterface* InPDI, const FTransform& InSourceTransform, const FTransform& InComponentTransform, const double InComponentScale, const FIKRetargetDebugDrawState& InEditorState) const override;`
- L186 _public function_ `virtual bool HasDebugDrawing() override`
- L188 _public member_ `FTransform DebugStrideWarpingFrame;`
- L189 _public member_ `static FCriticalSection DebugDataMutex;`
- L191 _public prototype_ `virtual void ResetChainSettingsToDefault(const FName& InChainName) override;`
- L192 _public prototype_ `virtual bool AreChainSettingsAtDefault(const FName& InChainName) override;`
- L193 _public prototype_ `virtual uint8* GetChainSettingsMemory(const FName InChainName) override;`
- L196 _public prototype_ `void RegenerateChainSettings(const FIKRetargetOpBase* InParentOp);`
- L198 _public member_ `TArray<FStrideWarpGoalData> GoalsToWarp;`
- L199 _public member_ `TObjectPtr<const UIKRigDefinition> TargetIKRig;`

#### class `UIKRetargetStrideWarpingController`  
`class UIKRetargetStrideWarpingController : public UIKRetargetOpControllerBase`  
_L204-219_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Stride Warping Op
- L213 _public prototype_ `FIKRetargetStrideWarpingOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetStrideWarpingOpSettings struct with the current settings used by the op.
- L218 _public prototype_ `void SetSettings(FIKRetargetStrideWarpingOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRetargetStrideWarpingOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`
- L10 _macro_ `#define LOCTEXT_NAMESPACE "StrideWarpingOp"`
- L122 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anoncf5a22e90103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Retargeter/RetargetOps/WeaponGoalsOp.h` (Public)


#### struct `FIKRetargetWeaponGoalsOpSettings`  
`struct FIKRetargetWeaponGoalsOpSettings : public FIKRetargetOpSettingsBase`  
_L14-101_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Weapon Op Settings"))`
- inherits: `FIKRetargetOpSettingsBase`
- L18 _public prototype_ `FIKRetargetWeaponGoalsOpSettings();`
- L23 _public member_ `FBoneReference LeftWeaponBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — An ancillary weapon bone for the left hand. This will be scaled with Weapon Scale. Defaults to "weapon_l".
- L28 _public member_ `FBoneReference RightWeaponBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — An ancillary weapon bone for the right hand. This will be scaled with Weapon Scale. Defaults to "weapon_r".
- L33 _public member_ `FBoneReference LeftHandAttachBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — An optional bone used to attach props to the left hand. This will be scaled with Weapon Scale. Defaults to "hand_attach_l".
- L38 _public member_ `FBoneReference RightHandAttachBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — An optional bone used to attach props to the right hand. This will be scaled with Weapon Scale. Defaults to "hand_attach_r".
- L43 _public member_ `FBoneReference LeftHandBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — The bone skinned to the left hand at wrist location. This bone must have an associated IK Goal. Defaults to "hand_l".
- L48 _public member_ `FBoneReference RightHandBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — The bone skinned to the right hand at wrist location. This bone must have an associated IK Goal. Defaults to "hand_r".
- L53 _public member_ `FBoneReference IKHandLeftBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", DisplayName="IK Hand Left Bone", meta=(NotOverrideable))` — A bone representing the location of the left hand IK position while holding a two-handed prop. Typically, a child of the IKHandGun. Defaults to "ik_hand_l".
- L58 _public member_ `FBoneReference IKHandRightBone;` — `UPROPERTY(EditAnywhere, Category = "Bones", DisplayName="IK Hand Right Bone", meta=(NotOverrideable))` — A bone representing the location of the right hand IK position while holding a two-handed prop. Typically, a child of the IKHandGun. Defaults to "ik_hand_r".
- L63 _public member_ `FBoneReference IKHandGun;` — `UPROPERTY(EditAnywhere, Category = "Bones", meta=(NotOverrideable))` — A bone located at the right hand, and parent of IKHandLeftBone and IKHandRightBone. This will be scaled with Weapon Scale. Defaults to "ik_hand_gun".
- L67 _public member_ `float Alpha = 1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Range 0 to 1. Default 1. Blends the effect of the op off. At 0, there is no effect.
- L71 _public member_ `bool bEnableWeaponScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — When false, all weapon scaling is skipped and WeaponScale has no effect.
- L75 _public member_ `double WeaponScale = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", meta = (ClampMin = "0.01", UIMin = "0.01", UIMax = "10.0"))` — Range 0 to inf. Default 1. Scales the IKHandGun bones, Left/Right Weapon bones and hand attach bones.
- L79 _public member_ `bool bSnapIKHandGun = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", DisplayName="Snap IK Hand Gun")` — When true, enables RetargetHandIKAlpha to blend the IK Gun hierarchy between left/right hands.
- L84 _public member_ `double LeftRightHandIKAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", DisplayName="Retarget Hand IK Alpha", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blends the entire Hand Gun bone hierarchy location from the left hand (at 0.0) to the right hand (at 1.0). Default is 1.0 (right hand). NOTE: this propagates the translational offset to the children bones (IKHandLeftBone/IKHandRightBone).
- L88 _public member_ `double LeftHandIKAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", DisplayName="Left Hand IK Alpha", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the effect of the left hand IK Goal from it's input location (0.0) to the IKHandLeftBone location (1.0). Default is 1.0.
- L92 _public member_ `double RightHandIKAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings", DisplayName="Right Hand IK Alpha", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the effect of the right hand IK Goal from it's input location (0.0) to the IKHandRightBone location (1.0). Default is 1.0.
- L96 _public member_ `bool bSuppressMissingBoneWarnings = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Op Settings")` — When true, will suppress warnings in the retarget editor output log about missing bones from this op.
- L98 _public prototype_ `virtual const UClass* GetControllerType() const override;`
- L100 _public prototype_ `virtual void CopySettingsAtRuntime(const FIKRetargetOpSettingsBase* InSettingsToCopyFrom) override;`

#### enum `ERetargetWeaponBone`  
`enum class ERetargetWeaponBone : uint8`  
_L105-117_
- reflection: `UENUM()`
- L107 _public enumerator_ `LeftWeapon UMETA(DisplayName = "Left Weapon")` — labels here used for warnings only, not exposed to UI
- L108 _public enumerator_ `RightWeapon UMETA(DisplayName = "Right Weapon")`
- L109 _public enumerator_ `LeftHandAttach UMETA(DisplayName = "Left Hand Attach")`
- L110 _public enumerator_ `RightHandAttach UMETA(DisplayName = "Right Hand Attach")`
- L111 _public enumerator_ `LeftHand UMETA(DisplayName = "Left Hand")`
- L112 _public enumerator_ `RightHand UMETA(DisplayName = "Right Hand")`
- L113 _public enumerator_ `IKHandLeft UMETA(DisplayName = "IK Hand Left")`
- L114 _public enumerator_ `IKHandRight UMETA(DisplayName = "IK Hand Right")`
- L115 _public enumerator_ `HandGun UMETA(DisplayName = "Hand Gun")`
- L116 _public enumerator_ `Count UMETA(Hidden)`

#### struct `FIKRetargetWeaponGoalOp`  
`struct FIKRetargetWeaponGoalOp : public FIKRetargetOpBase`  
_L120-152_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Weapon Goals"))`
- inherits: `FIKRetargetOpBase`
- L124 _public prototype_ `virtual bool Initialize( const FIKRetargetProcessor& InProcessor, const FRetargetSkeleton& InSourceSkeleton, const FTargetSkeleton& InTargetSkeleton, const FIKRetargetOpBase* InParentOp, FIKRigLogger& InLog) override;`
- L131 _public prototype_ `virtual void Run( FIKRetargetProcessor& InProcessor, const double InDeltaTime, const TArray<FTransform>& InSourceGlobalPose, TArray<FTransform>& OutTargetGlobalPose) override;`
- L137 _public prototype_ `virtual FIKRetargetOpSettingsBase* GetSettings() override;`
- L139 _public prototype_ `virtual const UScriptStruct* GetSettingsType() const override;`
- L141 _public prototype_ `virtual const UScriptStruct* GetType() const override;`
- L143 _public prototype_ `virtual const UScriptStruct* GetParentOpType() const override;`
- L146 _public member_ `FIKRetargetWeaponGoalsOpSettings Settings;` — `UPROPERTY()`
- L149 _private member_ `int32 BoneIndices[(int32)ERetargetWeaponBone::Count];`
- L150 _private member_ `FName LeftHandGoalName = NAME_None;`
- L151 _private member_ `FName RightHandGoalName = NAME_None;`

#### class `UIKRetargetWeaponGoalsOpController`  
`class UIKRetargetWeaponGoalsOpController : public UIKRetargetOpControllerBase`  
_L156-170_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRetargetOpControllerBase`
- desc: The blueprint/python API for editing a Weapon Goals Op
- L164 _public prototype_ `FIKRetargetWeaponGoalsOpSettings GetSettings();` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Get the current op settings as a struct. @return FIKRetargetWeaponGoalsOpSettings struct with the current settings used by the op.
- L169 _public prototype_ `void SetSettings(FIKRetargetWeaponGoalsOpSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = Settings)` — Set the op settings. Input is a custom struct type for this op. @param InSettings a FIKRetargetWeaponGoalsOpSettings struct containing all the settings to apply to this op

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/IKRigDataTypes.h` (Public)


#### enum `EIKRigGoalSpace`  
`enum class EIKRigGoalSpace : uint8`  
_L15-20_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Component UMETA(DisplayName = "Component Space")`
- L18 _public enumerator_ `Additive UMETA(DisplayName = "Additive")`
- L19 _public enumerator_ `World UMETA(DisplayName = "World Space")`

#### enum `EIKRigGoalTransformSource`  
`enum class EIKRigGoalTransformSource : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `Manual UMETA(DisplayName = "Manual Input")`
- L26 _public enumerator_ `Bone UMETA(DisplayName = "Bone")`
- L27 _public enumerator_ `ActorComponent UMETA(DisplayName = "Actor Component")`

#### struct `FIKRigGoal`  
`struct FIKRigGoal`  
_L31-143_
- reflection: `USTRUCT(Blueprintable)`
- L37 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)` — Name of the IK Goal. Must correspond to the name of a Goal in the target IKRig asset.
- L41 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)` — Name of the bone associate with this goal.
- L48 _public member_ `EIKRigGoalTransformSource TransformSource = EIKRigGoalTransformSource::Manual;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)` — Set the source of the transform data for the Goal. "Manual Input" uses the values provided by the blueprint node pin. "Bone" uses the transform of the bone provided by OptionalSourceBone. "Actor Component" uses the transform supplied by any Actor Components that implements the IIKGoalCreatorInterface
- L54 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Goal)` — When TransformSource is set to "Bone" mode, the Position and Rotation will be driven by this Bone's input transform. When using a Bone as the transform source, the Position and Rotation Alpha values can still be set as desired. But the PositionSpace and RotationSpace are no longer relevant and will not be used.
- L61 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position, meta=(EditCondition="Source == EIKRigGoalSource::Manual"))` — Position of the IK goal in Component Space of target actor component.
- L65 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta=(EditCondition="Source == EIKRigGoalSource::Manual"))` — Rotation of the IK goal in Component Space of target actor component.
- L69 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1.0. Smoothly blends the Goal position from the input pose (0.0) to the Goal position (1.0).
- L73 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1.0. Smoothly blends the Goal rotation from the input pose (0.0) to the Goal rotation (1.0).
- L80 _public member_ `EIKRigGoalSpace PositionSpace = EIKRigGoalSpace::Additive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position)` — The space that the goal position is in. "Additive" treats the goal transform as an additive offset relative to the Bone at the effector. "Component" treats the goal transform as being in the space of the Skeletal Mesh Actor Component. "World" treats the goal transform as being in the space of the World.
- L87 _public member_ `EIKRigGoalSpace RotationSpace = EIKRigGoalSpace::Additive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)` — The space that the goal rotation is in. "Additive" treats the goal transform as an additive offset relative to the Bone at the effector. "Component" treats the goal transform as being in the space of the Skeletal Mesh Actor Component. "World" treats the goal transform as being in the space of the World.
- L90 _public member_ `FVector FinalBlendedPosition = FVector::ZeroVector;` — `UPROPERTY(Transient)`
- L93 _public member_ `FQuat FinalBlendedRotation = FQuat::Identity;` — `UPROPERTY(Transient)`
- L98 _public member_ `bool bEnabled = true;` — `UPROPERTY(Transient)` — If true, the goal is active and can be used by solvers in the rig. NOTE: Toggling this on or off at runtime will trigger a re-initialization. Prefer Alpha if possible.
- L100 _public prototype_ `FIKRigGoal() = default;`
- L102 _public function_ `FIKRigGoal(const FName& InGoalName, const FName& InBoneName) : Name(InGoalName), BoneName(InBoneName)`
- L104 _public function_ `FIKRigGoal( const FName& InName, const FName& InBoneName, const FVector& InPosition, const FQuat& InRotation, const float InPositionAlpha, const float InRotationAlpha, EIKRigGoalSpace InPositionSpace, EIKRigGoalSpace InRotationSpace, bool bInEnabled) : Name(InName), BoneName(InBoneName), Position(InPosition), Rotation(InRotation.Rotator()), PositionAlpha(InPositionAlpha), RotationAlpha(InRotationAlpha), PositionSpace(InPositionSpace), RotationSpace(InRotationSpace), FinalBlendedPosition(InPosition), FinalBlendedRotation(InRotation), bEnabled(bInEnabled)`
- L126 _public function_ `FIKRigGoal(const UIKRigEffectorGoal* InGoal) : Name(InGoal->GoalName), BoneName(InGoal->BoneName), Position(InGoal->CurrentTransform.GetTranslation()), Rotation(InGoal->CurrentTransform.Rotator()), PositionAlpha(InGoal->PositionAlpha), RotationAlpha(InGoal->RotationAlpha), PositionSpace(EIKRigGoalSpace::Component), RotationSpace(EIKRigGoalSpace::Component), FinalBlendedPosition(ForceInitToZero), FinalBlendedRotation(FQuat::Identity)`
- L138 _public function_ `FString ToString() const`

#### struct `FIKRigGoalContainer`  
`struct FIKRigGoalContainer`  
_L148-197_
- reflection: `USTRUCT()`
- L156 _public prototype_ `void SetIKGoal(const FIKRigGoal& InGoal);` — Set an IK goal to go to a specific location and rotation (in the specified space) blended by alpha. Will ADD the goal if none exist with the input name.
- L160 _public prototype_ `void SetIKGoal(const UIKRigEffectorGoal* InEffectorGoal);` — Set an IK goal to go to a specific location and rotation (in the specified space) blended by alpha. Will ADD the goal if none exist with the input name.
- L163 _public prototype_ `const FIKRigGoal* FindGoalByName(const FName& GoalName) const;` — Get an IK goal with the given name. Returns nullptr if no Goal is found in the container with the name.
- L166 _public prototype_ `FIKRigGoal* FindGoalByName(const FName& GoalName);` — Get an IK goal with the given name. Returns nullptr if no Goal is found in the container with the name.
- L169 _public function_ `void Empty()` — Clear out all Goals in container.
- L172 _public function_ `bool IsEmpty() const` — Returns true if there are no goals in the container
- L175 _public function_ `bool NeedsInitialized() const` — Returns true if the container has a goal in it that triggered a reinitialization
- L178 _public function_ `const TArray<FIKRigGoal>& GetGoalArray() const` — Get read-only access to array of Goals.
- L179 _public function_ `TArray<FIKRigGoal>& GetGoalArray()`
- L182 _public prototype_ `const void FillWithGoalArray(const TArray<UIKRigEffectorGoal*>& InGoals);` — Fill this contain with all the goals in the input array
- L189 _private member_ `bool bRigNeedsInitialized = true;` — Set to true when: 1. a new goal is added 2. a goal has it's enabled flag toggled
- L191 _private prototype_ `FIKRigGoal* FindGoalWriteable(const FName& GoalName) const;`
- L194 _private member_ `TArray<FIKRigGoal> Goals;` — Array of Goals. Cannot contain duplicates (name is key).

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`
- L145 _function_ `inline uint32 GetTypeHash(FIKRigGoal ObjectRef)`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/IKRigDefinition.h` (Public)


#### enum `EIKRigGoalPreviewMode`  
`enum class EIKRigGoalPreviewMode : uint8`  
_L22-26_
- reflection: `UENUM()`
- L24 _public enumerator_ `Additive UMETA(DisplayName = "Additive")`
- L25 _public enumerator_ `Absolute UMETA(DisplayName = "Absolute")`

#### enum `EIKRigTransformType::Type`  
`enum Type : int8`  
_L30-34_
- L32 _public enumerator_ `Current`
- L33 _public enumerator_ `Reference`

#### class `UIKRigEffectorGoal`  
`class UIKRigEffectorGoal : public UObject`  
_L39-131_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L48 _public member_ `FName GoalName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Goal Settings")` — The name used to refer to this goal from outside systems. This is the name to use when referring to this Goal from Blueprint, Anim Graph, Control Rig or IK Retargeter.
- L52 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Goal Settings")` — The name of the bone that this Goal is located at.
- L56 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Goal Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend between the input bone position (0.0) and the current goal position (1.0).
- L60 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Goal Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1, default is 1. Blend between the input bone rotation (0.0) and the current goal rotation (1.0).
- L64 _public member_ `FTransform CurrentTransform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Goal Settings")` — The current transform of this Goal, in the Global Space of the character.
- L68 _public member_ `FTransform InitialTransform;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Goal Settings")` — The initial transform of this Goal, as defined by the initial transform of the Goal's bone in the retarget pose.
- L70 _public function_ `bool operator==(const UIKRigEffectorGoal& Other) const`
- L79 _public member_ `EIKRigGoalPreviewMode PreviewMode = EIKRigGoalPreviewMode::Additive;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Goal Settings")` — Effects how this Goal transform is previewed in the IK Rig editor. "Additive" interprets the Goal transform as being relative to the input pose. Useful for previewing animations. "Absolute" pins the Goal transform to the Gizmo in the viewport.
- L83 _public member_ `float SizeMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewport Goal Settings", meta = (ClampMin = "0.1", ClampMax = "1000.0", UIMin = "0.1", UIMax = "100.0"))` — The size of the Goal gizmo drawing in the editor viewport.
- L87 _public member_ `float ThicknessMultiplier = 0.7f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Viewport Goal Settings", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "5.0"))` — The thickness of the Goal gizmo drawing in the editor viewport.
- L91 _public member_ `bool bExposePosition = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exposure")` — Should position data be exposed in Blueprint
- L95 _public member_ `bool bExposeRotation = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exposure")` — Should rotation data be exposed in Blueprint
- L97 _public function_ `virtual void PostLoad() override`
- L107 _public prototype_ `TOptional<FTransform::FReal> GetNumericValue( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, EIKRigTransformType::Type TransformType ) const;`
- L114 _public prototype_ `TTuple<FTransform, FTransform> PrepareNumericValueChanged( ESlateTransformComponent::Type Component, ESlateRotationRepresentation::Type Representation, ESlateTransformSubComponent::Type SubComponent, FTransform::FReal Value, EIKRigTransformType::Type TransformType ) const;`
- L122 _public prototype_ `void SetTransform( const FTransform& InTransform, EIKRigTransformType::Type InTransformType);`
- L124 _public prototype_ `void OnCopyToClipboard(ESlateTransformComponent::Type Component, EIKRigTransformType::Type TransformType) const;`
- L125 _public prototype_ `void OnPasteFromClipboard(ESlateTransformComponent::Type Component, EIKRigTransformType::Type TransformType);`
- L127 _public prototype_ `bool TransformDiffersFromDefault(ESlateTransformComponent::Type Component, TSharedPtr<IPropertyHandle> PropertyHandle) const;`
- L128 _public prototype_ `void ResetTransformToDefault(ESlateTransformComponent::Type Component, TSharedPtr<IPropertyHandle> PropertyHandle);`

#### struct `FBoneChain`  
`struct FBoneChain`  
_L134-162_
- reflection: `USTRUCT(BlueprintType)`
- L138 _public prototype_ `FBoneChain() = default;`
- L140 _public function_ `FBoneChain( FName InName, const FName InStartBone, const FName InEndBone, const FName InGoalName = NAME_None) : ChainName(InName) , StartBone(InStartBone) , EndBone(InEndBone) , IKGoalName(InGoalName)`
- L152 _public member_ `FName ChainName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BoneChain)`
- L155 _public member_ `FBoneReference StartBone;` — `UPROPERTY(VisibleAnywhere, Category = BoneChain)`
- L158 _public member_ `FBoneReference EndBone;` — `UPROPERTY(VisibleAnywhere, Category = BoneChain)`
- L161 _public member_ `FName IKGoalName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = BoneChain)`

#### struct `FRetargetDefinition`  
`struct FRetargetDefinition`  
_L165-192_
- reflection: `USTRUCT(BlueprintType)`
- L171 _public member_ `FName RootBone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=RetargetRoot)` — The bone that contains root motion, located at the origin
- L175 _public member_ `FName PelvisBone;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=RetargetPelvis)` — The bone located at the hips or pelvis area, that translates the whole character
- L178 _public member_ `TArray<FBoneChain> BoneChains;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Chains)`
- L181 _public prototype_ `void AddBoneChain( const FName& ChainName, const FName& StartBone, const FName& EndBone, const FName& GoalName = NAME_None);` — add a bone chain from start bone to end bone and store it in this retarget definition
- L187 _public prototype_ `FBoneChain* GetEditableBoneChainByName(FName ChainName);`
- L190 _public prototype_ `bool Serialize(FArchive& Ar);` — post load patch old data
- L191 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FRetargetDefinition> : public TStructOpsTypeTraitsBase2<FRetargetDefinition>`  
_L196-203_
- inherits: `TStructOpsTypeTraitsBase2<FRetargetDefinition>`
- desc: load-patch FRetargetDefinition

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L199-202_

#### class `UIKRigDefinition`  
`class UIKRigDefinition : public UObject, public IInterface_PreviewMeshProvider`  
_L206-304_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IInterface_PreviewMeshProvider`
- L216 _public member_ `TSoftObjectPtr<USkeletalMesh> PreviewSkeletalMesh;` — `UPROPERTY(AssetRegistrySearchable, EditAnywhere, Category = PreviewMesh)` — The skeletal mesh to run the IK solve on (loaded into viewport). NOTE: you can assign ANY Skeletal Mesh to apply the IK Rig to. Compatibility is determined when a new mesh is assigned by comparing it's hierarchy with the goals, solvers and bone settings required by the rig. See output log for details.
- L219 _public function_ `const FIKRigSkeleton& GetSkeleton() const` — runtime, read-only access to skeleton data
- L222 _public function_ `const TArray<UIKRigEffectorGoal*>& GetGoalArray() const` — runtime, read-only access to array of Goals, all modifications must go through UIKRigController
- L225 _public prototype_ `const TArray<FInstancedStruct>& GetSolverStructs() const;` — runtime, read-only access to array of Solvers structs, all modifications must go through UIKRigController
- L228 _public function_ `const TArray<FBoneChain>& GetRetargetChains() const` — runtime, read-only access to Retarget Definition, all modifications must go through UIKRigController
- L231 _public function_ `const FName& GetPelvis() const` — runtime, read-only access to Pelvis, all modifications must go through UIKRigController
- L234 _public function_ `const FName& GetRoot() const` — runtime, read-only access to Root bone, all modifications must go through UIKRigController
- L237 _public prototype_ `const FBoneChain* GetRetargetChainByName(FName ChainName) const;` — runtime, read-only access to read a bone chain, all modifications must go through UIKRigController
- L240 _public prototype_ `TArray<FName> GetRetargetChainNames() const;` — get a list of the retarget chains contained in this IK Rig
- L243 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;` — UObject
- L244 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L245 _public prototype_ `virtual void PostLoad() override;`
- L249 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty = true) override;` — IInterface_PreviewMeshProvider interface
- L250 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const override;`
- L255 _public prototype_ `static const FName GetPreviewMeshPropertyName();` — Get name of Preview Mesh property
- L261 _public member_ `float BoneSize = 2.0f;` — `UPROPERTY()` — The size of the Bones in the editor viewport. This is set by callbacks from the viewport Character>Bones menu
- L265 _public member_ `bool DrawGoals = true;` — `UPROPERTY(EditAnywhere, Category = "Viewport Goal Settings")` — Draw bones in the viewport.
- L269 _public member_ `float GoalSize = 7.0f;` — `UPROPERTY(EditAnywhere, Category = "Viewport Goal Settings", meta = (ClampMin = "0.01", UIMin = "0.1", UIMax = "100.0"))` — The size of the Goals in the editor viewport.
- L273 _public member_ `float GoalThickness = 0.7f;` — `UPROPERTY(EditAnywhere, Category = "Viewport Goal Settings", meta = (ClampMin = "0.01", UIMin = "0.0", UIMax = "10.0"))` — The thickness of the Goals in the editor viewport.
- L277 _public member_ `TObjectPtr<UObject> Controller;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — The controller responsible for managing this asset's data (all editor mutation goes through this)
- L284 _private member_ `FIKRigSkeleton Skeleton;` — `UPROPERTY()` — hierarchy and bone-pose transforms
- L288 _private member_ `TArray<TObjectPtr<UIKRigEffectorGoal>> Goals;` — `UPROPERTY()` — goals, used as effectors by solvers that support them
- L292 _private member_ `TArray<FInstancedStruct> SolverStack;` — `UPROPERTY(meta = (ExcludeBaseStruct, BaseStruct = "/Script/IKRig.IKRigSolverBase"))` — polymorphic stack of solvers, executed in serial fashion where output of prior solve is input to the next
- L296 _private member_ `FRetargetDefinition RetargetDefinition;` — `UPROPERTY()` — bone chains for IK Retargeter
- L302 _private member_ `TArray<TObjectPtr<UIKRigSolver>> Solvers_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "The pre 5.6 stack of UObject based solvers. Use SolverStack instead."))`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace EIKRigTransformType`
- L200 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon755451540103`)
- L201 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon755451540103`)

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/IKRigProcessor.h` (Public)


#### struct `FGoalBone`  
`struct FGoalBone`  
_L18-25_
- reflection: `USTRUCT()`
- L22 _public member_ `FName BoneName;`
- L23 _public member_ `int32 BoneIndex;`
- L24 _public member_ `int32 OptSourceIndex = INDEX_NONE;`

#### struct `FIKRigProcessor`  
`struct FIKRigProcessor`  
_L37-148_
- desc: the runtime for an IKRig to convert an input pose into a solved output pose given a set of IK Rig Goals: 1. Create an FIKRigProcessor in your animation system (ie anim node) 2. Initialize() with an IKRigDefinition asset 3. each tick, call SetIKGoal() and SetInputPoseGlobal() 4. Call Solve() 5. Copy output transforms with GetOutputPoseGlobal()
- L48 _public prototype_ `void Initialize( const UIKRigDefinition* InRigAsset, const USkeletalMesh* InSkeletalMesh, const FIKRigGoalContainer& InOptionalGoals);` — setup a new processor to run the given IKRig asset NOTE!! this function creates new UObjects and consequently MUST be called from the main thread!! @param InRigAsset - the IK Rig defining the collection of solvers to execute and all the rig settings @param SkeletalMesh - the skeletal mesh you want to solve the IK on @param GoalContainer - an optional list of goals to initialize with, if empty it will use the goals from the IK Rig asset
- L60 _public prototype_ `void SetInputPoseGlobal(const TArray<FTransform>& InGlobalBoneTransforms);` — Set all bone transforms in global space. This is the pose the IK solve will start from
- L63 _public prototype_ `void SetInputBoneGlobal(const int32& InBoneIndex, const FTransform& InGlobalBoneTransform);` — Set input pose bone transforms individually
- L66 _public prototype_ `void SetInputPoseToRefPose();` — Optionally can be called before Solve() to use the reference pose as start pose
- L69 _public prototype_ `void ApplyGoalsFromOtherContainer(const FIKRigGoalContainer& InGoalContainer);` — Assign an entire container of goals to the rig.
- L72 _public prototype_ `void SetIKGoal(const FIKRigGoal& Goal);` — Set a named IK goal to go to a specific location, rotation and space, blended by separate position/rotation alpha (0-1)
- L75 _public prototype_ `void SetIKGoal(const UIKRigEffectorGoal* Goal);` — Set a named IK goal to go to a specific location, rotation and space, blended by separate position/rotation alpha (0-1)
- L79 _public prototype_ `void Solve(const FTransform& WorldToComponent = FTransform::Identity);` — Run entire stack of solvers. If any Goals were supplied in World Space, a valid WorldToComponent transform must be provided.
- L82 _public prototype_ `void GetOutputPoseGlobal(TArray<FTransform>& OutputPoseGlobal) const;` — Get the results after calling Solve()
- L85 _public prototype_ `void Reset();` — Reset all internal data structures. Will require re-initialization before solving again.
- L92 _public prototype_ `const FIKRigGoalContainer& GetGoalContainer() const;` — Get access to the internal goal data (read only)
- L93 _public prototype_ `FIKRigGoalContainer& GetGoalContainer();`
- L95 _public prototype_ `const FGoalBone* GetGoalBone(const FName& GoalName) const;` — Get the bone associated with a goal
- L98 _public prototype_ `FIKRigSkeleton& GetSkeletonWriteable();` — Get read/write access to the internal skeleton data
- L100 _public prototype_ `const FIKRigSkeleton& GetSkeleton() const;` — Get read-only access to the internal skeleton data
- L103 _public prototype_ `static bool IsIKRigCompatibleWithSkeleton( const UIKRigDefinition* InRigAsset, const FIKRigInputSkeleton& InputSkeleton, const FIKRigLogger* Log);` — Used to determine if the IK Rig asset is compatible with a given skeleton.
- L109 _public function_ `bool IsInitialized() const` — return true if the processor is initialized with a rig and ready to run
- L112 _public prototype_ `void SetNeedsInitialized();` — force the processor to reinitialize
- L115 _public prototype_ `const FIKRigSolverBase* GetSolver(const int32 InSolverIndex) const;` — Get read-only access to a currently running solver
- L119 _public prototype_ `void CopyAllSettingsFromAsset(const UIKRigDefinition* SourceAsset);` — Used to propagate setting values from the source asset at runtime (settings that do not require re-initialization) This allows the user to edit their IK Rig asset and see the effects in PIE.
- L122 _public member_ `FIKRigLogger Log;` — logging system
- L127 _private prototype_ `void ResolveFinalGoalTransforms(const FTransform& WorldToComponent);` — Update the final pos/rot of all the goals based on their alpha values and their space settings.
- L130 _private member_ `TArray<FInstancedStruct> Solvers;` — the stack of solvers to run in order
- L133 _private member_ `FIKRigGoalContainer GoalContainer;` — the named transforms that solvers use as end effectors
- L136 _private member_ `TMap<FName, FGoalBone> GoalBones;` — map of goal names to bone names/indices
- L139 _private member_ `FIKRigSkeleton Skeleton;` — storage for hierarchy and bone transforms
- L142 _private member_ `TObjectPtr<const UIKRigDefinition> AssetInitializedWith;` — store asset for dynamic reinitialization
- L145 _private member_ `bool bInitialized = false;` — true if processor is currently initialized and ready to run
- L147 _private member_ `bool bTriedToInitialize = false;` — true if processor attempted an initialization but failed (prevents infinite reinit)

#### class `UIKRigProcessor`  
`UIKRigProcessor : public UObject`  
_L160-236_
- reflection: `UCLASS()`
- reflection: `UE_DEPRECATED(5.6, "UIKRigProcessor has been replaced by FIKRigProcessor. UIKRigProcessor is now a thin wrapper around FIKRigProcessor and will be removed in a future version.")`
- inherits: `UObject`
- L166 _public function_ `void Initialize(const UIKRigDefinition* InRigAsset, const USkeletalMesh* SkeletalMesh, const TArray<FName>& ExcludedGoals = TArray<FName>())`
- L170 _public function_ `void SetInputPoseGlobal(const TArray<FTransform>& InGlobalBoneTransforms)`
- L174 _public function_ `void SetInputPoseToRefPose()`
- L178 _public function_ `void SetIKGoal(const FIKRigGoal& Goal)`
- L182 _public function_ `void SetIKGoal(const UIKRigEffectorGoal* Goal)`
- L186 _public function_ `void Solve(const FTransform& WorldToComponent = FTransform::Identity)`
- L190 _public function_ `void GetOutputPoseGlobal(TArray<FTransform>& OutputPoseGlobal) const`
- L194 _public function_ `void Reset()`
- L198 _public function_ `const FIKRigGoalContainer& GetGoalContainer() const`
- L202 _public function_ `const FGoalBone* GetGoalBone(const FName& GoalName) const`
- L206 _public function_ `FIKRigSkeleton& GetSkeletonWriteable()`
- L210 _public function_ `const FIKRigSkeleton& GetSkeleton() const`
- L214 _public function_ `static bool IsIKRigCompatibleWithSkeleton(const UIKRigDefinition* InRigAsset, const FIKRigInputSkeleton& InputSkeleton, const FIKRigLogger* Log)`
- L218 _public function_ `bool IsInitialized() const`
- L222 _public function_ `void SetNeedsInitialized()`
- L226 _public function_ `void CopyAllSettingsFromAsset(const UIKRigDefinition* SourceAsset)`
- L232 _public member_ `FIKRigLogger Log;` — NOTE: the deprecated logging system will no longer function. It's here to avoid compilation issues.
- L235 _private member_ `FIKRigProcessor Processor;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/IKRigSkeleton.h` (Public)


#### struct `FIKRigInputSkeleton`  
`struct FIKRigInputSkeleton`  
_L27-43_
- reflection: `USTRUCT()`
- desc: Data used just to initialize an IKRigSkeleton from outside systems The input skeleton may be different than the skeleton that the IK Rig asset was created for, within some limits. 1. It must have all the Bones that the IK Rig asset referenced (must be a sub-set) 2. All the bones must have the same parents (no change in hierarchy) You can however add additional bones, change the reference pose (including proportions) and the bone indices. This allows you to run the same IK Rig asset on somewhat different skeletal meshes. To validate compatibility use UIKRigProcess::IsIKRigCompatibleWithSkeleton()
- L31 _public member_ `TArray<FName> BoneNames;`
- L32 _public member_ `TArray<int32> ParentIndices;`
- L33 _public member_ `TArray<FTransform> LocalRefPose;`
- L34 _public member_ `const USkeletalMesh* SkeletalMesh;`
- L36 _public prototype_ `FIKRigInputSkeleton() = default;`
- L38 _public prototype_ `FIKRigInputSkeleton(const USkeletalMesh* InSkeletalMesh);`
- L40 _public prototype_ `void Initialize(const USkeletalMesh* InSkeletalMesh);`
- L42 _public prototype_ `void Reset();`

#### struct `FIKRigSkeleton`  
`struct FIKRigSkeleton`  
_L46-132_
- reflection: `USTRUCT()`
- L52 _public member_ `TObjectPtr<const USkeletalMesh> SkeletalMesh;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — The skeletal mesh this was initialized with.
- L56 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — Names of bones. Used to match hierarchy with runtime skeleton.
- L60 _public member_ `TArray<int32> ParentIndices;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — Same length as BoneNames, stores index of parent for each bone.
- L64 _public member_ `TArray<FName> ExcludedBones;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — Sparse array of bones that are to be excluded from any solvers (parented around, treated as FK children).
- L68 _public member_ `TArray<FTransform> CurrentPoseGlobal;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — The current GLOBAL space pose of each bone.
- L72 _public member_ `TArray<FTransform> CurrentPoseLocal;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — The current LOCAL space pose of each bone.
- L76 _public member_ `TArray<FTransform> RefPoseGlobal;` — `UPROPERTY(VisibleAnywhere, Category = Skeleton)` — The initial/reference GLOBAL space pose of each bone.
- L78 _public prototype_ `void SetInputSkeleton(const USkeletalMesh* InSkeletalMesh, const TArray<FName>& InExcludedBones);`
- L80 _public prototype_ `void SetInputSkeleton(const FIKRigInputSkeleton& InputSkeleton, const TArray<FName>& InExcludedBones);`
- L82 _public prototype_ `void Reset();`
- L84 _public prototype_ `int32 GetBoneIndexFromName(const FName InName) const;`
- L86 _public prototype_ `const FName& GetBoneNameFromIndex(const int32 BoneIndex) const;`
- L88 _public prototype_ `int32 GetParentIndex(const int32 BoneIndex) const;`
- L90 _public prototype_ `int32 GetParentIndexThatIsNotExcluded(const int32 BoneIndex) const;`
- L92 _public prototype_ `int32 GetChildIndices(const int32 ParentBoneIndex, TArray<int32>& Children) const;`
- L94 _public prototype_ `void GetChildrenIndicesRecursive(const int32 BoneIndex, TArray<int32>& OutChildren) const;`
- L96 _public prototype_ `int32 GetCachedEndOfBranchIndex(const int32 InBoneIndex) const;`
- L98 _public prototype_ `static void ConvertLocalPoseToGlobal( const TArray<int32>& InParentIndices, const TArray<FTransform>& InLocalPose, TArray<FTransform>& OutGlobalPose);`
- L103 _public prototype_ `void UpdateAllGlobalTransformFromLocal();`
- L105 _public prototype_ `void UpdateAllLocalTransformFromGlobal();`
- L107 _public prototype_ `void UpdateGlobalTransformFromLocal(const int32 BoneIndex);`
- L109 _public prototype_ `void UpdateLocalTransformFromGlobal(const int32 BoneIndex);`
- L111 _public prototype_ `void PropagateGlobalPoseBelowBone(const int32 BoneIndex);`
- L113 _public prototype_ `bool IsBoneInDirectLineage(const FName& Child, const FName& PotentialParent) const;`
- L115 _public prototype_ `bool IsBoneExcluded(const int32 BoneIndex) const;`
- L117 _public prototype_ `static void NormalizeRotations(TArray<FTransform>& Transforms);`
- L119 _public prototype_ `void GetChainsInList(const TArray<int32>& SelectedBones, TArray<FBoneChain>& OutChains) const;`
- L122 _public prototype_ `bool ValidateChainAndGetBones(const FBoneChain& Chain, TArray<int32>& OutBoneIndices) const;` — get indices of bones in this chain, ordered from tip to root. returns false if chain is invalid.
- L126 _public prototype_ `bool GetMirroredBoneIndices(const TArray<int32>& BoneIndices, TArray<int32>& OutMirroredIndices) const;` — given a set of bones, returns a set of indices of bones that are mirrored across X axis (YZ plane) return false if any of the bones do not have a mirrored pair within the MaxDistanceThreshold
- L131 _private member_ `mutable TArray<int32> CachedEndOfBranchIndices;` — The branch bellow a specific bone. It stores the last element of the branch instead of the indices

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigBodyMoverSolver.h` (Public)


#### struct `FIKRigBodyMoverGoalSettings`  
`struct FIKRigBodyMoverGoalSettings : public FIKRigGoalSettingsBase`  
_L13-24_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.BodyMoverGoalSettingsWrapper"))`
- inherits: `FIKRigGoalSettingsBase`
- L19 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Goal Settings")` — The bone associated with this goal.
- L23 _public member_ `float InfluenceMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Goal Settings", meta = (ClampMin = "0", ClampMax = "10", UIMin = "0.0", UIMax = "10.0"))` — Scale the influence this goal has on the body. Range is 0-10. Default is 1.0.

#### struct `FIKRigBodyMoverSettings`  
`struct FIKRigBodyMoverSettings : public FIKRigSolverSettingsBase`  
_L27-78_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.BodyMoverSettingsWrapper"))`
- inherits: `FIKRigSolverSettingsBase`
- L33 _public member_ `FName StartBone;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Body Mover Settings")` — The target bone to move with the effectors.
- L37 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Blend the translational effect of this solver on/off. Range is 0-1. Default is 1.0.
- L41 _public member_ `float PositionPositiveX = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Multiply the POSITIVE X translation. Range is 0-1. Default is 1.0.
- L45 _public member_ `float PositionNegativeX = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Multiply the NEGATIVE X translation. Range is 0-1. Default is 1.0.
- L49 _public member_ `float PositionPositiveY = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Multiply the POSITIVE Y translation. Range is 0-1. Default is 1.0.
- L53 _public member_ `float PositionNegativeY = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Multiply the NEGATIVE Y translation. Range is 0-1. Default is 1.0.
- L57 _public member_ `float PositionPositiveZ = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Multiply the POSITIVE Z translation. Range is 0-1. Default is 1.0.
- L61 _public member_ `float PositionNegativeZ = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — /  Multiply the NEGATIVE Z translation. Range is 0-1. Default is 1.0.
- L65 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Blend the total rotational effect on/off. Range is 0-1. Default is 1.0.
- L69 _public member_ `float RotateXAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Blend the X-axis rotational effect on/off. Range is 0-1. Default is 1.0.
- L73 _public member_ `float RotateYAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Blend the Y-axis rotational effect on/off. Range is 0-1. Default is 1.0.
- L77 _public member_ `float RotateZAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Body Mover Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Blend the Z-axis rotational effect on/off. Range is 0-1. Default is 1.0.

#### struct `FIKRigBodyMoverSolver`  
`struct FIKRigBodyMoverSolver : public FIKRigSolverBase`  
_L81-132_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L86 _public member_ `FIKRigBodyMoverSettings Settings;` — `UPROPERTY()`
- L89 _public member_ `TArray<FIKRigBodyMoverGoalSettings> AllGoalSettings;` — `UPROPERTY()`
- L92 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton) override;` — FIKRigSolverBase interface
- L93 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L94 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L95 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L98 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — solver settings
- L99 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L102 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal) override;` — goals
- L103 _public prototype_ `virtual void OnGoalRemoved(const FName& InGoalName) override;`
- L104 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L105 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L108 _public function_ `virtual bool UsesCustomGoalSettings() const override` — goal settings
- L109 _public prototype_ `virtual FIKRigGoalSettingsBase* GetGoalSettings(const FName& InGoalName) override;`
- L110 _public prototype_ `virtual const UScriptStruct* GetGoalSettingsType() const override;`
- L111 _public prototype_ `virtual void GetGoalsWithSettings(TSet<FName>& OutGoalsWithSettings) const override;`
- L114 _public function_ `virtual bool UsesStartBone() const override` — start bone can be set on this solver
- L115 _public function_ `virtual FName GetStartBone() const override`
- L116 _public prototype_ `virtual void SetStartBone(const FName& InRootBoneName) override;`
- L120 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L122 _public prototype_ `virtual FText GetNiceName() const override;` — UI stuff
- L123 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L124 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L129 _private prototype_ `int32 GetIndexOfGoal(const FName& InGoalName) const;`
- L131 _private member_ `int32 BodyBoneIndex;`

#### class `UIKRigBodyMoverController`  
`class UIKRigBodyMoverController : public UIKRigSolverControllerBase`  
_L137-164_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRigSolverControllerBase`
- desc: The blueprint/python API for modifying a Body Mover solver's settings in an IK Rig. Can adjust Solver and Goal settings.
- L146 _public prototype_ `FIKRigBodyMoverSettings GetSolverSettings();` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the current solver settings as a struct. @return FIKRigBodyMoverSettings struct with the current settings used by the solver.
- L151 _public prototype_ `void SetSolverSettings(FIKRigBodyMoverSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRigBodyMoverSettings struct containing all the settings to apply to this solver
- L157 _public prototype_ `FIKRigBodyMoverGoalSettings GetGoalSettings(const FName InGoalName);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the settings for the specified goal. @param InGoalName the name of the goal to get settings for @return FIKRigBodyMoverGoalSettings struct (empty if the specified goal does not belong to this solver)
- L163 _public prototype_ `void SetGoalSettings(const FName InGoalName, FIKRigBodyMoverGoalSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the settings for the specified goal. @param InGoalName: the name of the goal to assign the settings to. @param InSettings: a custom struct type with all the settings for a goal

#### class `UIKRig_BodyMoverEffector`  
`class UIKRig_BodyMoverEffector : public UObject`  
_L172-184_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced with FBodyMoverGoalSettings.
- L179 _public member_ `FName GoalName;` — `UPROPERTY()`
- L181 _public member_ `FName BoneName;` — `UPROPERTY()`
- L183 _public member_ `float InfluenceMultiplier = 1.0f;` — `UPROPERTY()`

#### class `UIKRig_BodyMover`  
`class UIKRig_BodyMover : public UIKRigSolver`  
_L188-255_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UIKRigSolver`
- desc: NOTE: This type has been replaced with FBodyMoverSolver.
- L195 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override` — upgrade patch to new UStruct-based solver
- L228 _public member_ `FName RootBone;` — `UPROPERTY()`
- L230 _public member_ `float PositionAlpha = 1.0f;` — `UPROPERTY()`
- L232 _public member_ `float PositionPositiveX = 1.0f;` — `UPROPERTY()`
- L234 _public member_ `float PositionNegativeX = 1.0f;` — `UPROPERTY()`
- L236 _public member_ `float PositionPositiveY = 1.0f;` — `UPROPERTY()`
- L238 _public member_ `float PositionNegativeY = 1.0f;` — `UPROPERTY()`
- L240 _public member_ `float PositionPositiveZ = 1.0f;` — `UPROPERTY()`
- L242 _public member_ `float PositionNegativeZ = 1.0f;` — `UPROPERTY()`
- L244 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY()`
- L246 _public member_ `float RotateXAlpha = 1.0f;` — `UPROPERTY()`
- L248 _public member_ `float RotateYAlpha = 1.0f;` — `UPROPERTY()`
- L250 _public member_ `float RotateZAlpha = 1.0f;` — `UPROPERTY()`
- L254 _public member_ `TArray<TObjectPtr<UIKRig_BodyMoverEffector>> Effectors_DEPRECATED;` — `UE_DEPRECATED(5.6, "IK Rig refactored to not use UObjects")` — `UPROPERTY(meta = (DeprecatedProperty))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigFullBodyIK.h` (Public)


#### struct `FIKRigFBIKGoalSettings`  
`struct FIKRigFBIKGoalSettings : public FIKRigGoalSettingsBase`  
_L15-56_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.FBIKGoalSettingsWrapper"))`
- inherits: `FIKRigGoalSettingsBase`
- L19 _public prototype_ `FIKRigFBIKGoalSettings() = default;`
- L20 _public function_ `FIKRigFBIKGoalSettings(FName InGoalName, FName InBoneName) : BoneName(InBoneName)`
- L24 _public member_ `FName BoneName;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Full Body IK Effector")` — The bone that this effector will pull on.
- L31 _public member_ `int32 ChainDepth = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Full Body IK Effector", meta = (ClampMin = "0", UIMin = "0"))` — Range 0-inf (default is 0). Explicitly set the number of bones up the hierarchy to consider part of this effector's 'chain'. The "chain" of bones is used to apply Preferred Angles, Pull Chain Alpha and Chain "Sub Solves". If left at 0, the solver will attempt to determine the root of the chain by searching up the hierarchy until it finds a branch or another effector, whichever it finds first.
- L38 _public member_ `float StrengthAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Full Body IK Effector", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). The strength of the effector when pulling the bone towards it's target location. At 0.0, the effector does not pull at all, but the bones between the effector and the root will still slightly resist motion from other effectors. This can thus act as a "stabilizer" for parts of the body that you do not want to behave in a pure FK fashion.
- L47 _public member_ `float PullChainAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Full Body IK Effector", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). When enabled (greater than 0.0), the solver internally partitions the skeleton into 'chains' which extend from the effector up the hierarchy by "Chain Depth". If Chain Depth is 0, the chain root is set to the nearest fork in the skeleton. These chains are pre-rotated and translated, as a whole, towards the effector targets. This can improve the results for sparse bone chains, and significantly improve convergence on dense bone chains. But it may cause undesirable results in highly constrained bone chains (like robot arms).
- L52 _public member_ `float PinRotation = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Full Body IK Effector", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range 0-1 (default is 1.0). Blends the effector bone rotation between the rotation of the effector transform (1.0) and the rotation of the input bone (0.0).
- L55 _public member_ `int32 IndexInSolver = -1;` — `UPROPERTY(Transient)`

#### struct `FIKRigFBIKBoneSettings`  
`struct FIKRigFBIKBoneSettings : public FIKRigBoneSettingsBase`  
_L59-142_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.FBIKBoneSettingsWrapper"))`
- inherits: `FIKRigBoneSettingsBase`
- L63 _public prototype_ `FIKRigFBIKBoneSettings() = default;`
- L64 _public function_ `FIKRigFBIKBoneSettings(FName InBoneName)`
- L68 _public member_ `float RotationStiffness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Stiffness, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range is 0 to 1 (Default is 0). At higher values, the bone will resist rotating (forcing other bones to compensate).
- L72 _public member_ `float PositionStiffness = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Stiffness, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — Range is 0 to 1 (Default is 0). At higher values, the bone will resist translational motion (forcing other bones to compensate).
- L79 _public member_ `EPBIKLimitType X = EPBIKLimitType::Free;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the X axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at reference pose angle).
- L82 _public member_ `float MinX = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative X direction to allow when joint is in "Limited" mode.
- L85 _public member_ `float MaxX = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive X direction to allow when joint is in "Limited" mode.
- L92 _public member_ `EPBIKLimitType Y = EPBIKLimitType::Free;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the Y axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at input pose angle).
- L95 _public member_ `float MinY = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative Y direction to allow when joint is in "Limited" mode.
- L98 _public member_ `float MaxY = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive Y direction to allow when joint is in "Limited" mode.
- L105 _public member_ `EPBIKLimitType Z = EPBIKLimitType::Free;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits)` — Limit the rotation angle of the bone on the Z axis. Free: can rotate freely in this axis. Limited: rotation is clamped between the min/max angles relative to the Skeletal Mesh reference pose. Locked: no rotation is allowed in this axis (will remain at input pose angle).
- L108 _public member_ `float MinZ = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "-180", ClampMax = "0", UIMin = "-180.0", UIMax = "0.0"))` — Range is -180 to 0 (Default is 0). Degrees of rotation in the negative Z direction to allow when joint is in "Limited" mode.
- L111 _public member_ `float MaxZ = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Limits, meta = (ClampMin = "0", ClampMax = "180", UIMin = "0.0", UIMax = "180.0"))` — Range is 0 to 180 (Default is 0). Degrees of rotation in the positive Z direction to allow when joint is in "Limited" mode.
- L117 _public member_ `bool bUsePreferredAngles = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PreferredAngles)` — When true, this bone will "prefer" to rotate in the direction specified by the Preferred Angles when the chain it belongs to is compressed. Preferred Angles should be the first method used to fix bones that bend in the wrong direction (rather than limits). The resulting angles can be visualized on their own by temporarily setting the Solver iterations to 0 and moving the effectors.
- L122 _public member_ `FVector PreferredAngles = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = PreferredAngles)` — The local Euler angles (in degrees) used to rotate this bone when the chain it belongs to is squashed. This happens by moving the effector at the tip of the chain towards the root of the chain. This can be used to coerce knees and elbows to bend in the anatomically "correct" direction without resorting to limits (which may require more iterations to converge).
- L124 _public function_ `void CopyToCoreStruct(PBIK::FBoneSettings& Settings) const`

#### struct `FIKRigFBIKSettings`  
`struct FIKRigFBIKSettings : public FIKRigSolverSettingsBase`  
_L145-195_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.FBIKSettingsWrapper"))`
- inherits: `FIKRigSolverSettingsBase`
- L155 _public member_ `FName RootBone;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Full Body IK Settings")` — All bones above this bone in the hierarchy will be completely ignored by the solver. Typically, this is set to the top-most skinned bone in the Skeletal Mesh (ie Pelvis, Hips etc), NOT the actual root of the entire skeleton. If you want to use the solver on a single chain of bones, and NOT translate the chain, ensure that "PinRoot" is checked on to disable the root from translating to reach the effector goals.
- L159 _public member_ `int32 Iterations = 20;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0.0", UIMax = "200.0"))` — High iteration counts can help solve complex joint configurations with competing constraints, but will increase runtime cost. Default is 20.
- L163 _public member_ `int32 SubIterations = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", ClampMax = "1000", UIMin = "0.0", UIMax = "200.0"))` — Iterations used for sub-chains defined by the Chain Depth of the effectors. These are solved BEFORE the main iteration pass. Default is 0.
- L167 _public member_ `float MassMultiplier = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings, meta = (ClampMin = "0", UIMin = "0.0", UIMax = "10.0"))` — A global mass multiplier; higher values will make the joints more stiff, but require more iterations. Typical range is 0.0 to 10.0.
- L171 _public member_ `bool bAllowStretch = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = SolverSettings)` — If true, joints will translate to reach the effectors; causing bones to lengthen if necessary. Good for cartoon effects. Default is false.
- L178 _public member_ `EPBIKRootBehavior RootBehavior = EPBIKRootBehavior::PrePull;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootBehavior)` — (Default is PrePull) Set the behavior of the solver root. Pre Pull: translates and rotates the root (and all children) by the average motion of the stretched effectors to help achieve faster convergence when reaching far. Pin to Input: locks the translation and rotation of the root bone to the input pose. Overrides any bone settings applied to the root. Good for partial-body solves. Free: treats the root bone like any other and allows it to move freely or according to any bone settings applied to it.
- L182 _public member_ `FRootPrePullSettings PrePullRootSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RootBehavior)` — Settings only applicable when Root Behavior is set to "PrePull". Use these values to adjust the gross movement and orientation of the entire skeleton.
- L186 _public member_ `float GlobalPullChainAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "0", ClampMax = "1", UIMin = "0.0", UIMax = "1.0"))` — A global multiplier for all Pull Chain Alpha values on all effectors. Range is 0.0 to 1.0. Default is 1.0.
- L190 _public member_ `float MaxAngle = 30.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "0", ClampMax = "45", UIMin = "0.0", UIMax = "180.0"))` — Maximum angle that a joint can be rotated per constraint iteration. Lower this value if the solve is diverging. Range is 0.0 to 180.0. Default is 30.
- L194 _public member_ `float OverRelaxation = 1.3f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AdvancedSettings, meta = (ClampMin = "1", ClampMax = "2", UIMin = "1.0", UIMax = "2.0"))` — Pushes constraints beyond their normal amount to speed up convergence. Increasing this may speed up convergence, but at the cost of stability. Range is 1.0 - 2.0. Default is 1.3.

#### struct `FIKRigFullBodyIKSolver`  
`struct FIKRigFullBodyIKSolver : public FIKRigSolverBase`  
_L199-268_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L204 _public member_ `FIKRigFBIKSettings Settings;` — `UPROPERTY()`
- L207 _public member_ `TArray<FIKRigFBIKGoalSettings> AllGoalSettings;` — `UPROPERTY()`
- L210 _public member_ `TArray<FIKRigFBIKBoneSettings> AllBoneSettings;` — `UPROPERTY()`
- L213 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton) override;` — FIKRigSolverBase runtime interface
- L214 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L215 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L216 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L220 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — solver settings
- L221 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L225 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal) override;` — goals
- L226 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L227 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L228 _public prototype_ `virtual void OnGoalRemoved(const FName& InGoalName) override;`
- L232 _public prototype_ `virtual bool UsesCustomGoalSettings() const override;` — goal settings
- L233 _public prototype_ `virtual FIKRigGoalSettingsBase* GetGoalSettings(const FName& InGoalName) override;`
- L234 _public prototype_ `virtual const UScriptStruct* GetGoalSettingsType() const override;`
- L235 _public prototype_ `virtual void GetGoalsWithSettings(TSet<FName>& OutGoalsWithSettings) const override;`
- L239 _public prototype_ `virtual bool UsesStartBone() const override;` — start bone
- L240 _public prototype_ `virtual void SetStartBone(const FName& InStartBoneName) override;`
- L241 _public prototype_ `virtual FName GetStartBone() const override;`
- L245 _public prototype_ `virtual bool UsesCustomBoneSettings() const override;` — bone settings
- L246 _public prototype_ `virtual void AddSettingsToBone(const FName& InBoneName) override;`
- L247 _public prototype_ `virtual void RemoveSettingsOnBone(const FName& InBoneName) override;`
- L248 _public prototype_ `virtual FIKRigBoneSettingsBase* GetBoneSettings(const FName& InBoneName) override;`
- L249 _public prototype_ `virtual const UScriptStruct* GetBoneSettingsType() const override;`
- L250 _public prototype_ `virtual bool HasSettingsOnBone(const FName& InBoneName) const override;`
- L251 _public prototype_ `virtual void GetBonesWithSettings(TSet<FName>& OutBonesWithSettings) const override;`
- L256 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L258 _public prototype_ `virtual FText GetNiceName() const override;` — ui
- L259 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L260 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L265 _private member_ `FPBIKSolver Solver;`
- L267 _private prototype_ `int32 GetIndexOfGoal(const FName& InGoalName) const;`

#### class `UIKRigFBIKController`  
`class UIKRigFBIKController : public UIKRigSolverControllerBase`  
_L274-314_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRigSolverControllerBase`
- desc: The blueprint/python API for modifying an Full-Body IK solver's settings in an IK Rig. Can adjust Solver, Goal and Bone settings.
- L283 _public prototype_ `FIKRigFBIKSettings GetSolverSettings();` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the current solver settings as a struct. @return FIKRigFBIKSettings struct with the current settings used by the solver.
- L288 _public prototype_ `void SetSolverSettings(FIKRigFBIKSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRigFBIKSettings struct containing all the settings to apply to this solver
- L294 _public prototype_ `FIKRigFBIKGoalSettings GetGoalSettings(const FName InGoalName);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the settings for the specified goal. @param InGoalName the name of the goal to get settings for @return FIKRigFBIKGoalSettings struct (empty if the specified goal does not belong to this solver)
- L300 _public prototype_ `void SetGoalSettings(const FName InGoalName, FIKRigFBIKGoalSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the settings for the specified goal. @param InGoalName: the name of the goal to assign the settings to. @param InSettings: a custom struct type with all the settings for an FBIK goal
- L307 _public prototype_ `FIKRigFBIKBoneSettings GetBoneSettings(const FName InBoneName);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the settings associated with a particular bone. Note that you must AddBoneSettings() using the IK Rig controller before a bone will have settings on it. @param InBoneName the name of the bone to get settings for @return FIKRigFBIKBoneSettings struct holding all the settings for the specified bone (or empty if the bone did not have settings)
- L313 _public prototype_ `void SetBoneSettings(const FName InBoneName, FIKRigFBIKBoneSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Apply settings to a given bone @param InBoneName the name of the bone to apply the settings to @param InSettings a FIKRigFBIKBoneSettings struct containing the settings

#### class `UIKRig_FBIKEffector`  
`class UIKRig_FBIKEffector : public UObject`  
_L322-340_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced with FFBIKGoalSettings.
- L329 _public member_ `FName GoalName;` — `UPROPERTY()`
- L331 _public member_ `FName BoneName;` — `UPROPERTY()`
- L333 _public member_ `int32 ChainDepth = 0;` — `UPROPERTY()`
- L335 _public member_ `float StrengthAlpha = 1.0f;` — `UPROPERTY()`
- L337 _public member_ `float PullChainAlpha = 1.0f;` — `UPROPERTY()`
- L339 _public member_ `float PinRotation = 1.0f;` — `UPROPERTY()`

#### class `UIKRig_FBIKBoneSettings`  
`class UIKRig_FBIKBoneSettings : public UObject`  
_L344-378_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced with FFBIKBoneSettings.
- L351 _public member_ `FName Bone;` — `UPROPERTY()`
- L353 _public member_ `float RotationStiffness = 0.0f;` — `UPROPERTY()`
- L355 _public member_ `float PositionStiffness = 0.0f;` — `UPROPERTY()`
- L357 _public member_ `EPBIKLimitType X;` — `UPROPERTY()`
- L359 _public member_ `float MinX = 0.0f;` — `UPROPERTY()`
- L361 _public member_ `float MaxX = 0.0f;` — `UPROPERTY()`
- L363 _public member_ `EPBIKLimitType Y;` — `UPROPERTY()`
- L365 _public member_ `float MinY = 0.0f;` — `UPROPERTY()`
- L367 _public member_ `float MaxY = 0.0f;` — `UPROPERTY()`
- L369 _public member_ `EPBIKLimitType Z;` — `UPROPERTY()`
- L371 _public member_ `float MinZ = 0.0f;` — `UPROPERTY()`
- L373 _public member_ `float MaxZ = 0.0f;` — `UPROPERTY()`
- L375 _public member_ `bool bUsePreferredAngles = false;` — `UPROPERTY()`
- L377 _public member_ `FVector PreferredAngles;` — `UPROPERTY()`

#### class `UIKRigFBIKSolver`  
`class UIKRigFBIKSolver : public UIKRigSolver`  
_L382-498_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UIKRigSolver`
- desc: NOTE: This type has been replaced with FFBIKSolver.
- L389 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override` — upgrade patch to new UStruct-based solver
- L453 _public member_ `FName RootBone;` — `UPROPERTY()`
- L455 _public member_ `int32 Iterations = 20;` — `UPROPERTY()`
- L457 _public member_ `int32 SubIterations = 0;` — `UPROPERTY()`
- L459 _public member_ `float MassMultiplier = 1.0f;` — `UPROPERTY()`
- L461 _public member_ `bool bAllowStretch = false;` — `UPROPERTY()`
- L463 _public member_ `EPBIKRootBehavior RootBehavior = EPBIKRootBehavior::PrePull;` — `UPROPERTY()`
- L465 _public member_ `FRootPrePullSettings PrePullRootSettings;` — `UPROPERTY()`
- L467 _public member_ `float PullChainAlpha = 1.0f;` — `UPROPERTY()`
- L469 _public member_ `float MaxAngle = 30.f;` — `UPROPERTY()`
- L471 _public member_ `float OverRelaxation = 1.3f;` — `UPROPERTY()`
- L475 _public function_ `TArray<UIKRig_FBIKEffector*> GetEffectors()` — `UE_DEPRECATED(5.6, "Deprecated UObject based FBIK solver.")` — `UFUNCTION(meta = (DeprecatedFunction))`
- L484 _public function_ `TArray<UIKRig_FBIKBoneSettings*> GetBoneSettings()` — `UE_DEPRECATED(5.6, "Deprecated UObject based FBIK solver.")` — `UFUNCTION(meta = (DeprecatedFunction))`
- L493 _public member_ `TArray<TObjectPtr<UIKRig_FBIKEffector>> Effectors_DEPRECATED;` — `UE_DEPRECATED(5.6, "IK Rig refactored to not use UObjects")` — `UPROPERTY(meta = (DeprecatedProperty))`
- L497 _public member_ `TArray<TObjectPtr<UIKRig_FBIKBoneSettings>> BoneSettings_DEPRECATED;` — `UE_DEPRECATED(5.6, "IK Rig refactored to not use UObjects")` — `UPROPERTY(meta = (DeprecatedProperty))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigLimbSolver.h` (Public)


#### struct `FIKRigLimbSolverSettings`  
`struct FIKRigLimbSolverSettings : public FLimbSolverSettings`  
_L16-31_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.LimbSolverSettingsWrapper"))`
- inherits: `FLimbSolverSettings`
- L22 _public member_ `FName StartBone = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName = "Root Bone", Category = "Limb IK Settings")` — The first bone in the IK chain, for example the "hip" in a leg, or the "shoulder" in an arm
- L26 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Limb IK Effector")` — The name of the IK goal to drive the end bone towards
- L30 _public member_ `FName EndBone = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Limb IK Effector")` — The name of the last bone in the IK chain. This is the bone you want to reach the goal.

#### struct `FIKRigLimbSolver`  
`struct FIKRigLimbSolver : public FIKRigSolverBase`  
_L34-79_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L39 _public member_ `FIKRigLimbSolverSettings Settings;` — `UPROPERTY()`
- L42 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton) override;` — runtime
- L43 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L44 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L45 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L48 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — solver settings
- L49 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L52 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal) override;` — goals
- L53 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L54 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L55 _public prototype_ `virtual void OnGoalRemoved(const FName& InGoalName) override;`
- L58 _public prototype_ `virtual bool UsesStartBone() const override;` — start bone
- L59 _public prototype_ `virtual void SetStartBone(const FName& InStartBoneName) override;`
- L60 _public prototype_ `virtual FName GetStartBone() const override;`
- L64 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L67 _public prototype_ `virtual FText GetNiceName() const override;` — general UI
- L68 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L69 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L74 _private prototype_ `static void GatherChildren(const int32 BoneIndex, const FIKRigSkeleton& InSkeleton, TArray<int32>& OutChildren);`
- L76 _private member_ `FLimbSolver Solver;`
- L77 _private member_ `TArray<int32> ChildrenToUpdate;`

#### class `UIKRigLimbSolverController`  
`class UIKRigLimbSolverController : public UIKRigSolverControllerBase`  
_L84-99_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRigSolverControllerBase`
- desc: The blueprint/python API for modifying an Full-Body IK solver's settings in an IK Rig. Can adjust Solver, Goal and Bone settings.
- L93 _public prototype_ `FIKRigLimbSolverSettings GetSolverSettings();` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the current solver settings as a struct. @return FIKRigLimbSolverSettings struct with the current settings used by the solver.
- L98 _public prototype_ `void SetSolverSettings(FIKRigLimbSolverSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRigLimbSolverSettings struct containing all the settings to apply to this solver

#### class `UIKRig_LimbEffector`  
`class UIKRig_LimbEffector : public UObject`  
_L107-118_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced with FIKRigLimbSolver.
- L112 _public function_ `UIKRig_LimbEffector()`
- L115 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY()`
- L117 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY()`

#### class `UIKRig_LimbSolver`  
`class UIKRig_LimbSolver : public UIKRigSolver`  
_L122-178_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UIKRigSolver`
- desc: NOTE: This type has been replaced with FIKRigLimbSolver.
- L128 _public function_ `UIKRig_LimbSolver()`
- L134 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override` — upgrade patch to new UStruct-based solver
- L155 _public member_ `FName RootName = NAME_None;` — `UPROPERTY()`
- L157 _public member_ `float ReachPrecision = 0.01f;` — `UPROPERTY()`
- L159 _public member_ `TEnumAsByte<EAxis::Type> HingeRotationAxis = EAxis::None;` — `UPROPERTY()`
- L161 _public member_ `int32 MaxIterations = 12;` — `UPROPERTY()`
- L163 _public member_ `bool bEnableLimit = false;` — `UPROPERTY()`
- L165 _public member_ `float MinRotationAngle = 15.f;` — `UPROPERTY()`
- L167 _public member_ `bool bAveragePull = true;` — `UPROPERTY()`
- L169 _public member_ `float PullDistribution = 0.5f;` — `UPROPERTY()`
- L171 _public member_ `float ReachStepAlpha = 0.7f;` — `UPROPERTY()`
- L173 _public member_ `bool bEnableTwistCorrection = false;` — `UPROPERTY()`
- L175 _public member_ `TEnumAsByte<EAxis::Type> EndBoneForwardAxis = EAxis::Y;` — `UPROPERTY()`
- L177 _public member_ `TObjectPtr<UIKRig_LimbEffector> Effector_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigPoleSolver.h` (Public)


#### struct `FIKRigPoleSolverSettings`  
`struct FIKRigPoleSolverSettings : public FIKRigSolverSettingsBase`  
_L13-29_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.PoleSolverSettingsWrapper"))`
- inherits: `FIKRigSolverSettingsBase`
- L18 _public member_ `FName StartBone = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Pole Solver Settings")`
- L21 _public member_ `FName EndBone = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Pole Solver Settings")`
- L24 _public member_ `FName AimAtGoal = NAME_None;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Pole Solver Settings")`
- L28 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pole Solver Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the effect on/off. Range is 0-1. Default is 1.0.

#### struct `FIKRigPoleSolver`  
`struct FIKRigPoleSolver : public FIKRigSolverBase`  
_L32-81_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L37 _public member_ `FIKRigPoleSolverSettings Settings;` — `UPROPERTY()`
- L40 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton) override;` — runtime FIKRigSolverBase interface
- L41 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L42 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L43 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L46 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — solver settings
- L47 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L50 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& NewGoal) override;` — goals
- L51 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L52 _public prototype_ `virtual void OnGoalRemoved(const FName& InName) override;`
- L53 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L56 _public function_ `virtual bool UsesStartBone() const override` — start bone can be set on this solver
- L57 _public prototype_ `virtual void SetStartBone(const FName& InRootBoneName) override;`
- L58 _public prototype_ `virtual FName GetStartBone() const override;`
- L61 _public function_ `virtual bool UsesEndBone() const override` — end bone can be set on this solver
- L62 _public prototype_ `virtual void SetEndBone(const FName& InEndBoneName) override;`
- L63 _public prototype_ `virtual FName GetEndBone() const override;`
- L67 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L70 _public prototype_ `virtual FText GetNiceName() const override;` — UI
- L71 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L72 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L77 _private member_ `TArray<int32> Chain;`
- L78 _private member_ `TArray<int32> ChildrenToUpdate;`
- L80 _private prototype_ `static void GatherChildren(const int32 BoneIndex, const FIKRigSkeleton& InSkeleton, TArray<int32>& OutChildren);`

#### class `UIKRigPoleSolverController`  
`class UIKRigPoleSolverController : public UIKRigSolverControllerBase`  
_L85-100_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRigSolverControllerBase`
- desc: The blueprint/python API for modifying a Pole solver's settings in an IK Rig.
- L94 _public prototype_ `FIKRigPoleSolverSettings GetSolverSettings();` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the current solver settings as a struct. @return FIKRigPoleSolverSettings struct with the current settings used by the solver.
- L99 _public prototype_ `void SetSolverSettings(FIKRigPoleSolverSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRigPoleSolverSettings struct containing all the settings to apply to this solver

#### class `UIKRig_PoleSolverEffector`  
`class UIKRig_PoleSolverEffector : public UObject`  
_L108-120_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This type has been replaced with FPoleSolver.
- L115 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY()`
- L117 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY()`
- L119 _public member_ `float Alpha = 1.0f;` — `UPROPERTY()`

#### class `UIKRig_PoleSolver`  
`class UIKRig_PoleSolver : public UIKRigSolver`  
_L124-160_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UIKRigSolver`
- desc: NOTE: This type has been replaced with FPoleSolver.
- L130 _public function_ `UIKRig_PoleSolver()`
- L138 _public member_ `FName RootName = NAME_None;` — `UPROPERTY()`
- L140 _public member_ `FName EndName = NAME_None;` — `UPROPERTY()`
- L143 _public member_ `TObjectPtr<UIKRig_PoleSolverEffector> Effector_DEPRECATED;` — `UE_DEPRECATED(5.6, "IK Rig refactored to not use UObjects")` — `UPROPERTY(meta = (DeprecatedProperty))`
- L146 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override` — upgrade patch to new UStruct-based solver

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigSetTransform.h` (Public)


#### struct `FIKRigSetTransformSettings`  
`struct FIKRigSetTransformSettings : public FIKRigSolverSettingsBase`  
_L13-40_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.SetTransformSettingsWrapper"))`
- inherits: `FIKRigSolverSettingsBase`
- L19 _public member_ `FName Goal;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Set Transform Settings")` — The goal used to affect the bone transform
- L23 _public member_ `FName BoneToAffect;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Set Transform Settings")` — The bone to affect
- L27 _public member_ `float PositionAlpha = 1.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Set Transform Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the translation on/off. Range is 0-1. Default is 1.0.
- L31 _public member_ `float RotationAlpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Set Transform Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the rotation on/off. Range is 0-1. Default is 1.0.
- L35 _public member_ `float Alpha = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Set Transform Effector", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Blend the total effect on/off. Range is 0-1. Default is 1.0.
- L39 _public member_ `bool bPropagateToChildren = true;` — `UPROPERTY(EditAnywhere, Category = "Set Transform Settings")` — If true, the transform modification will propagate to the hierarchy below the target bone.

#### struct `FIKRigSetTransform`  
`struct FIKRigSetTransform : public FIKRigSolverBase`  
_L43-78_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L48 _public member_ `FIKRigSetTransformSettings Settings;` — `UPROPERTY()`
- L51 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& IKRigSkeleton) override;` — runtime
- L52 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L53 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L54 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L57 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — settings
- L58 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L61 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal) override;` — goals
- L62 _public prototype_ `virtual void OnGoalRemoved(const FName& InGoalName) override;`
- L63 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L64 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L68 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L70 _public prototype_ `virtual FText GetNiceName() const override;` — ui
- L71 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L72 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L77 _private member_ `int32 BoneIndex = INDEX_NONE;`

#### class `UIKRigSetTransformController`  
`class UIKRigSetTransformController : public UIKRigSolverControllerBase`  
_L82-97_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UIKRigSolverControllerBase`
- desc: The blueprint/python API for modifying Set Transform settings in an IK Rig.
- L91 _public prototype_ `FIKRigSetTransformSettings GetSolverSettings();` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get the current solver settings as a struct. @return FIKRigSetTransformSettings struct with the current settings used by the solver.
- L96 _public prototype_ `void SetSolverSettings(FIKRigSetTransformSettings InSettings);` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Set the solver settings. Input is a custom struct type for this solver. @param InSettings a FIKRigSetTransformSettings struct containing all the settings to apply to this solver

#### class `UIKRig_SetTransformEffector`  
`class UIKRig_SetTransformEffector : public UObject`  
_L105-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE: This is a legacy type that is converted into an FSetTransformGoalSettings on PostLoad()
- L112 _public member_ `bool bEnablePosition = true;` — `UPROPERTY()`
- L114 _public member_ `bool bEnableRotation = true;` — `UPROPERTY()`
- L116 _public member_ `float Alpha = 1.0f;` — `UPROPERTY()`

#### class `UIKRig_SetTransform`  
`class UIKRig_SetTransform : public UIKRigSolver`  
_L121-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UIKRigSolver`
- desc: NOTE: This is a legacy type that is converted into an FIKRigSetTransform on PostLoad()
- L127 _public function_ `UIKRig_SetTransform()`
- L133 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct) override` — upgrade patch to new UStruct-based solver
- L146 _public member_ `FName Goal;` — `UPROPERTY()`
- L148 _public member_ `FName RootBone;` — `UPROPERTY()`
- L150 _public member_ `TObjectPtr<UIKRig_SetTransformEffector> Effector_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigSolverBase.h` (Public)


#### struct `FIKRigSettingsBase`  
`struct FIKRigSettingsBase`  
_L20-25_
- reflection: `USTRUCT(BlueprintType)`
- desc: This is the base class for all types of settings used by IKRig
- L24 _public prototype_ `virtual ~FIKRigSettingsBase() = default;`

#### struct `FIKRigGoalSettingsBase`  
`struct FIKRigGoalSettingsBase : public FIKRigSettingsBase`  
_L31-40_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSettingsBase`
- desc: This is the base class for defining editable per-goal settings for your custom IKRig solver. For example, your solver could have a "Strength" value for goals, which can go here. NOTE: the derived type must be returned by the solver's GetGoalSettingsType() and GetGoalSettings()
- L37 _public member_ `FName Goal;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Goal Settings")` — The IKRig Goal that these settings are applied to.
- L39 _public prototype_ `virtual ~FIKRigGoalSettingsBase() = default;`

#### struct `FIKRigBoneSettingsBase`  
`struct FIKRigBoneSettingsBase : public FIKRigSettingsBase`  
_L46-55_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSettingsBase`
- desc: This is the base class for defining editable per-bone settings for your custom IKRig solver. For example, your solver may have rotation limits per-bone which can be stored here. NOTE: the derived type must be returned by the solver's GetBoneSettingsType() and GetBoneSettings()
- L52 _public member_ `FName Bone;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Bone Settings")` — The bone these settings are applied to.
- L54 _public prototype_ `virtual ~FIKRigBoneSettingsBase() = default;`

#### struct `FIKRigSolverSettingsBase`  
`struct FIKRigSolverSettingsBase : public FIKRigSettingsBase`  
_L61-66_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSettingsBase`
- desc: This is the base class for defining editable settings for your custom IKRig solver. All user-configurable properties for your solver should be stored in a subclass of this NOTE: the derived type must be returned by the solver's GetSolverSettingsType() and GetSolverSettings()
- L65 _public prototype_ `virtual ~FIKRigSolverSettingsBase() = default;`

#### struct `FIKRigSolverBase`  
`struct FIKRigSolverBase`  
_L70-214_
- reflection: `USTRUCT(BlueprintType)`
- desc: this is the base class for creating your own solver type that integrates into the IK Rig framework/editor.
- L74 _public prototype_ `virtual ~FIKRigSolverBase() = default;`
- L77 _public function_ `bool IsEnabled() const` — get if this solver is enabled
- L79 _public function_ `void SetEnabled(const bool bEnabled)` — turn solver on/off (will be skipped during execution if disabled)
- L83 _public function_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton)` — RUNTIME (required) override to setup internal data based on ref pose
- L85 _public function_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals)` — (required) override Solve() to evaluate new output pose (InOutGlobalTransform)
- L87 _public function_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const` — (required) override to add any bones which this solver requires (helps validate skeleton compatibility)
- L89 _public function_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const` — (required) override to add any goals that have been added to this solver
- L97 _public prototype_ `virtual void UpdateSettingsFromAsset(const FIKRigSolverBase& InAssetSolver);` — (optional) override to add custom logic when updating settings from the source asset at runtime NOTE: you can safely cast this to your own solver type and copy any relevant settings at runtime This is necessary because at runtime, the IKRigProcessor creates a copy of your solver struct and the copy must be notified of changes made to the editor instance so that users can see their edits update in PIE. NOTE: the default implementation will copy solver, goal and bone settings if your solver has them
- L101 _public function_ `virtual FIKRigSolverSettingsBase* GetSolverSettings()` — SOLVER SETTINGS (required) override this to support custom settings for your solver type
- L103 _public function_ `virtual const UScriptStruct* GetSolverSettingsType() const` — (required) override this and return the type your solver uses to store its settings
- L105 _public prototype_ `virtual void SetSolverSettings(const FIKRigSolverSettingsBase* InSettings);` — (optional) override to add custom logic if needed when outside systems set solver settings.
- L110 _public function_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal)` — GOALS (required) override to support ADDING a new goal to custom solver
- L112 _public function_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName)` — (required) override to support RENAMING an existing goal
- L114 _public function_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName)` — (required) override to support CHANGING BONE for an existing goal
- L116 _public function_ `virtual void OnGoalRemoved(const FName& InGoalName)` — (required) override to support REMOVING a goal from custom solver
- L121 _public function_ `virtual bool UsesCustomGoalSettings() const` — GOAL SETTINGS (optional) override and return true to tell systems if this solver supports custom per-goal settings
- L125 _public function_ `virtual FIKRigGoalSettingsBase* GetGoalSettings(const FName& InGoalName)` — (required if UsesCustomGoalSettings()) override to support supplying goals settings specific to this solver to outside systems for editing/UI returns a pointer to the settings stored for the given bone (null if bone does not have settings)
- L127 _public prototype_ `virtual void SetGoalSettings(const FName& InGoalName, FIKRigGoalSettingsBase* InSettings);` — (optional) override if you need custom logic when setting goal settings from outside systems.
- L129 _public function_ `virtual const UScriptStruct* GetGoalSettingsType() const` — (required if UsesCustomGoalSettings()) returns the type used for the goal settings in this solver
- L131 _public function_ `virtual void GetGoalsWithSettings(TSet<FName>& OutGoalsWithSettings) const` — (required if UsesCustomGoalSettings()) override to support telling outside systems which goals this solver has settings for.
- L137 _public function_ `virtual bool UsesStartBone() const` — START BONE (optional) determines if your solver requires a start bone to be specified (most do) override and return true if your solver requires the user to specify a start bone
- L139 _public function_ `virtual FName GetStartBone() const` — (required if UsesStartBone()) if solver requires a start bone, then override this to return it.
- L141 _public function_ `virtual void SetStartBone(const FName& InRootBoneName)` — (required if UsesStartBone()) override to support SETTING ROOT BONE for the solver
- L147 _public function_ `virtual bool UsesEndBone() const` — END BONE (optional) implement if your solver requires an end bone override and return true if this solver requires an end bone to be specified
- L149 _public function_ `virtual FName GetEndBone() const` — (required if UsesEndBone()) override to support getting end bone of the solver
- L151 _public function_ `virtual void SetEndBone(const FName& InEndBoneName)` — (required if UsesEndBone()) override to support setting end bone for the solver
- L157 _public function_ `virtual bool UsesCustomBoneSettings() const` — BONE SETTINGS (optional) implement if your solver supports per-bone settings override and return true to tell systems if this solver supports per-bone settings
- L159 _public function_ `virtual void AddSettingsToBone(const FName& InBoneName)` — (required if UsesCustomBoneSettings()) override to support ADDING settings to a particular bone
- L161 _public function_ `virtual void RemoveSettingsOnBone(const FName& InBoneName)` — (required if UsesCustomBoneSettings()) override to support REMOVING settings on a particular bone
- L164 _public function_ `virtual FIKRigBoneSettingsBase* GetBoneSettings(const FName& InBoneName)` — (required if UsesCustomBoneSettings()) override to support supplying per-bone settings to outside systems for editing/UI NOTE: This must be overriden on solvers that use bone setting and return nullptr if no settings for the given bone
- L166 _public prototype_ `virtual void SetBoneSettings(const FName& InBoneName, FIKRigBoneSettingsBase* InSettings);` — (optional) override if you need custom logic when per-bone settings are applied from outside systems
- L168 _public function_ `virtual const UScriptStruct* GetBoneSettingsType() const` — (required if UsesCustomBoneSettings()) returns the type used for the bone settings in this solver
- L170 _public function_ `virtual bool HasSettingsOnBone(const FName& InBoneName) const` — (required if UsesCustomBoneSettings()) override to inform outside systems if the given bone has custom settings on it
- L173 _public function_ `virtual void GetBonesWithSettings(TSet<FName>& OutBonesWithSettings) const` — (required if UsesCustomBoneSettings()) override to support telling outside systems which bones this solver has settings for. NOTE: Only ADD to the incoming set, do not remove from it.
- L180 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer);` — SCRIPTING API (optional, but recommended) provide a scripting object to edit your custom solver type in the editor via BP/Python
- L185 _public function_ `virtual FText GetNiceName() const` — GENERAL UI (required) override to give your solver a nice name to display in the UI
- L187 _public function_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const` — (optional, but recommended) override to provide warning to user during setup of any missing components. return false if no warnings.
- L189 _public function_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const` — (optional, but recommended) return true if the supplied Bone is affected by this solver - this provides UI feedback for user
- L194 _public function_ `virtual void DrawBoneSettings(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton, FPrimitiveDrawInterface* PDI) const` — TODO: This will be supported in a future version of Unreal (optional) override to do custom debug drawing in the editor viewport
- L199 _protected prototype_ `UIKRigSolverControllerBase* CreateControllerIfNeeded(UObject* Outer, const UClass* ClassType);` — helper function for solvers to instantiate their own controller
- L202 _protected member_ `TStrongObjectPtr<UIKRigSolverControllerBase> Controller = nullptr;` — an optional custom editor controller used to edit this solver by script/blueprint
- L209 _private prototype_ `static void CopyAllEditableProperties(const UScriptStruct* SettingsType, const FIKRigSettingsBase* CopyFrom, FIKRigSettingsBase* CopyTo);` — generic function to set all types of solver settings
- L213 _private member_ `bool bIsEnabled = true;` — `UPROPERTY()` — all solvers can be enabled/disabled in the UI or API

#### class `UIKRigSolverControllerBase`  
`class UIKRigSolverControllerBase : public UObject`  
_L217-235_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L226 _public function_ `void SetEnabled(bool bIsEnabled)` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Turn the solver on/off in the IK Rig solver stack. @param bIsEnabled if true, the solver will execute, false otherwise.
- L231 _public function_ `bool GetEnabled()` — `UFUNCTION(BlueprintCallable, Category = IKRig)` — Get if the solver is on or off in the IK Rig solver stack. @param bIsEnabled returns true if the solver is enabled, false otherwise.
- L234 _public member_ `FIKRigSolverBase* SolverToControl = nullptr;` — the solver this controller controls

#### class `UIKRigSolver`  
`class UIKRigSolver : public UObject`  
_L250-295_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: NOTE on UIKRigSolver upgrade path: In 5.6 the UObject's in IK Rig have been replaced with runtime-friendly UStruct based data structures As part of this change, solvers based on UIKRigSolver will no longer function and must be upgraded to the new base FIKRigSolverBase. Old assets using UIKRigSolver-based solvers can be loaded and patched using the ConvertToInstancedStruct() function (see below) All solvers that ship with the IKRig plugin have been ported to the new system and should work exactly as before.
- L258 _public function_ `virtual void ConvertToInstancedStruct(FInstancedStruct& OutInstancedStruct)` — this is the legacy upgrade path for solvers that inherit from UIKRigSolver to convert them to FIKRigSolverBase override this and supply a struct into OutInstancedStruct that derives from FIKRigSolverBase that implements your custom solver.
- L261 _public function_ `virtual void Initialize(const FIKRigSkeleton& IKRigSkeleton)` — LEGACY UObject-based solver interface
- L262 _public function_ `virtual void Solve(FIKRigSkeleton& IKRigSkeleton, const FIKRigGoalContainer& Goals)`
- L263 _public function_ `virtual FName GetRootBone() const`
- L264 _public function_ `virtual void GetBonesWithSettings(TSet<FName>& OutBonesWithSettings) const`
- L265 _public function_ `bool IsEnabled() const`
- L266 _public function_ `void SetEnabled(const bool bEnabled)`
- L267 _public function_ `virtual void UpdateSolverSettings(UIKRigSolver* InSettings)`
- L268 _public function_ `virtual void RemoveGoal(const FName& GoalName)`
- L269 _public function_ `virtual bool IsGoalConnected(const FName& GoalName) const`
- L271 _public function_ `virtual FText GetNiceName() const`
- L272 _public function_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const`
- L273 _public function_ `virtual void AddGoal(const UIKRigEffectorGoal& NewGoal)`
- L274 _public function_ `virtual void RenameGoal(const FName& OldName, const FName& NewName)`
- L275 _public function_ `virtual void SetGoalBone(const FName& GoalName, const FName& NewBoneName)`
- L276 _public function_ `virtual UObject* GetGoalSettings(const FName& GoalName) const`
- L277 _public function_ `virtual void SetRootBone(const FName& RootBoneName)`
- L278 _public function_ `virtual bool RequiresRootBone() const`
- L279 _public function_ `virtual void SetEndBone(const FName& EndBoneName)`
- L280 _public function_ `virtual FName GetEndBone() const`
- L281 _public function_ `virtual bool RequiresEndBone() const`
- L282 _public function_ `virtual void AddBoneSetting(const FName& BoneName)`
- L283 _public function_ `virtual void RemoveBoneSetting(const FName& BoneName)`
- L284 _public function_ `virtual UObject* GetBoneSetting(const FName& BoneName) const`
- L285 _public function_ `virtual bool UsesBoneSettings() const`
- L286 _public function_ `virtual void DrawBoneSettings(const FName& BoneName, const FIKRigSkeleton& IKRigSkeleton, FPrimitiveDrawInterface* PDI) const`
- L287 _public function_ `virtual bool IsBoneAffectedBySolver(const FName& BoneName, const FIKRigSkeleton& IKRigSkeleton) const`
- L294 _private member_ `bool bIsEnabled = true;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/IKRigStretchLimb.h` (Public)


#### struct `FIKRigStretchLimbBoneSettings`  
`struct FIKRigStretchLimbBoneSettings : public FIKRigBoneSettingsBase`  
_L15-31_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.StretchLimbBoneSettingsWrapper"))`
- inherits: `FIKRigBoneSettingsBase`
- L19 _public prototype_ `FIKRigStretchLimbBoneSettings() = default;`
- L20 _public function_ `FIKRigStretchLimbBoneSettings(FName InBoneName)`
- L28 _public member_ `FVector SquashDirection = FVector::ZAxisVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferred Squash Direction")` — The direction to push this bone when the limb is squashed. This is relative to the local bone axes. NOTE: This direction is used by the "Squash Strength" feature of the stretch limb solver. If no custom Squash direction is specified, the solver will push the bone in the direction away from its projection onto the pole vector. If the bone is lying directly on the pole vector, the default squash direction is undefined and the bone may mot squash in a deterministic manner.
- L30 _public member_ `int32 CachedChainIndex;`

#### enum `EStretchLimbSquashMode`  
`enum class EStretchLimbSquashMode : uint8`  
_L34-39_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `None`
- L37 _public enumerator_ `Uniform`
- L38 _public enumerator_ `Bulge`

#### enum `EStretchLimbRotationMode`  
`enum class EStretchLimbRotationMode : uint8`  
_L42-46_
- reflection: `UENUM(BlueprintType)`
- L44 _public enumerator_ `None`
- L45 _public enumerator_ `OrientToGoal`

#### struct `FIKRigStretchLimbSettings`  
`struct FIKRigStretchLimbSettings : public FIKRigSolverSettingsBase`  
_L49-99_
- reflection: `USTRUCT(BlueprintType, meta=(UIWrapper="/Script/IKRigEditor.StretchLimbSettingsWrapper"))`
- inherits: `FIKRigSolverSettingsBase`
- L55 _public member_ `FName StartBone;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Limb Setup")` — The start bone assigned to this solver (usually the thigh or shoulder).
- L59 _public member_ `FName EndBone;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Limb Setup")` — The end bone assigned to this solver (usually the foot or ball).
- L63 _public member_ `FName Goal;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Limb Setup")` — The end bone assigned to this solver (usually the foot or ball).
- L67 _public member_ `bool bEnableStretching = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stretch Settings")` — Determines whether to squash or stretch the bones to reach the goal.
- L71 _public member_ `double MaximumStretchDistance = -1.0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stretch Settings")` — The maximum distance the limb is allowed to stretch (beyond its rest length). Default is -1.0 (no limit).
- L76 _public member_ `double StretchStartPercent = 0.95;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stretch Settings", meta = (ClampMin = "0.1", ClampMax = "1.0", UIMin = "0.1", UIMax = "1.0"))` — The percentage of the bone chain length to straighten before stretching is applied (can prevent over extension). NOTE: At 1.0, the limb will not stretch until the goal is 100% of the length of the limb away from the root of the chain.
- L80 _public member_ `EStretchLimbRotationMode RotationMode = EStretchLimbRotationMode::OrientToGoal;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation Settings")` — Determines how to affect the orientation of the bones in the chain.
- L84 _public member_ `double RotateEndBoneWithGoal = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rotation Settings", meta = (UIMin = "0.0", UIMax = "1.0"))` — Allow the end bone to be reoriented (0) or match the orientation of the goal (1). Range is 0-1. Default is 1.0.
- L88 _public member_ `int32 Iterations = 8;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Constraint Solving", meta = (UIMin = "0", UIMax = "20.0"))` — Number of FABRIK iterations to correct bones lengths. Adjust until the end bone converges on the goal. Default is 8.
- L93 _public member_ `EStretchLimbSquashMode SquashMode = EStretchLimbSquashMode::Uniform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Constraint Solving")` — Control the falloff shape of the squash effect applied to the bones when the goal compresses the limb. Default is Uniform. NOTE: this has no effect if the Squash Strength is 0.
- L98 _public member_ `double SquashStrength = 50;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Constraint Solving", meta = (UIMin = "0", UIMax = "200.0"))` — The distance to squash the bones perpendicular to the pole vector when the limb is fully compressed. NOTE: tune this to help dense chains achieve a reasonable pose. Must be used with constraint iterations to fix bones lengths.

#### struct `FIKRigStretchLimbSolver`  
`struct FIKRigStretchLimbSolver : public FIKRigSolverBase`  
_L102-188_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverBase`
- L107 _public prototype_ `virtual void Initialize(const FIKRigSkeleton& InIKRigSkeleton) override;` — FIKRigSolverBase interface
- L108 _public prototype_ `virtual void Solve(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoalContainer& InGoals) override;`
- L109 _public prototype_ `virtual void GetRequiredBones(TSet<FName>& OutRequiredBones) const override;`
- L110 _public prototype_ `virtual void GetRequiredGoals(TSet<FName>& OutRequiredGoals) const override;`
- L113 _public prototype_ `virtual FIKRigSolverSettingsBase* GetSolverSettings() override;` — solver settings
- L114 _public prototype_ `virtual const UScriptStruct* GetSolverSettingsType() const override;`
- L117 _public prototype_ `virtual void AddGoal(const UIKRigEffectorGoal& InNewGoal) override;` — goals
- L118 _public prototype_ `virtual void OnGoalRemoved(const FName& InGoalName) override;`
- L119 _public prototype_ `virtual void OnGoalRenamed(const FName& InOldName, const FName& InNewName) override;`
- L120 _public prototype_ `virtual void OnGoalMovedToDifferentBone(const FName& InGoalName, const FName& InNewBoneName) override;`
- L123 _public function_ `virtual bool UsesCustomGoalSettings() const override` — goal settings
- L126 _public prototype_ `virtual bool UsesCustomBoneSettings() const override;` — bone settings
- L127 _public prototype_ `virtual void AddSettingsToBone(const FName& InBoneName) override;`
- L128 _public prototype_ `virtual void RemoveSettingsOnBone(const FName& InBoneName) override;`
- L129 _public prototype_ `virtual FIKRigBoneSettingsBase* GetBoneSettings(const FName& InBoneName) override;`
- L130 _public prototype_ `virtual const UScriptStruct* GetBoneSettingsType() const override;`
- L131 _public prototype_ `virtual bool HasSettingsOnBone(const FName& InBoneName) const override;`
- L132 _public prototype_ `virtual void GetBonesWithSettings(TSet<FName>& OutBonesWithSettings) const override;`
- L136 _public function_ `virtual bool UsesStartBone() const override` — start bone can be set on this solver
- L137 _public function_ `virtual FName GetStartBone() const override`
- L138 _public prototype_ `virtual void SetStartBone(const FName& InRootBoneName) override;`
- L142 _public prototype_ `virtual UIKRigSolverControllerBase* GetSolverController(UObject* Outer) override;` — return custom controller for scripting this solver
- L144 _public prototype_ `virtual FText GetNiceName() const override;` — UI stuff
- L145 _public prototype_ `virtual bool GetWarningMessage(FText& OutWarningMessage) const override;`
- L146 _public prototype_ `virtual bool IsBoneAffectedBySolver(const FName& InBoneName, const FIKRigSkeleton& InIKRigSkeleton) const override;`
- L150 _public member_ `FIKRigStretchLimbSettings Settings;` — `UPROPERTY()`
- L153 _public member_ `TArray<FIKRigStretchLimbBoneSettings> AllBoneSettings;` — `UPROPERTY()`
- L157 _private prototype_ `void AimChainAtGoal(FIKRigSkeleton& InIKRigSkeleton, const FVector& GoalLocation) const;`
- L159 _private prototype_ `void StoreBonePositions(FIKRigSkeleton& InIKRigSkeleton);`
- L160 _private prototype_ `void UpdateBoneOrientations(FIKRigSkeleton& InIKRigSkeleton);`
- L162 _private prototype_ `void SquashOrStretchChainParallel(FIKRigSkeleton& InIKRigSkeleton, const FVector& GoalLocation) const;`
- L163 _private prototype_ `void SquashChainPerpendicular(FIKRigSkeleton& InIKRigSkeleton);`
- L164 _private prototype_ `void StretchChainFinal(FIKRigSkeleton& InIKRigSkeleton, const FVector& GoalLocation) const;`
- L165 _private prototype_ `void ApplyParallelOffsetToChain(FIKRigSkeleton& InIKRigSkeleton, const FVector& ChainStart, const FVector& NewPoleVector, const FVector& CurrentPoleVector) const;`
- L167 _private prototype_ `void RunFABRIK(FIKRigSkeleton& InIKRigSkeleton, const FVector& GoalLocation);`
- L168 _private prototype_ `void RunFABRIKBackwardPass(const FVector& Goal, TArray<FVector>& BonePositions);`
- L169 _private prototype_ `void RunFABRIKForwardPass(const FVector& Start, TArray<FVector>& BonePositions);`
- L171 _private prototype_ `void UpdateFKChildren(FIKRigSkeleton& InIKRigSkeleton);`
- L173 _private prototype_ `void RotateEndBoneWithGoal(FIKRigSkeleton& InIKRigSkeleton, const FIKRigGoal* Goal);`
- L175 _private prototype_ `double CalculateCurrentChainLength(FIKRigSkeleton& InIKRigSkeleton) const;`
- L177 _private prototype_ `void UpdateRestLengths(FIKRigSkeleton& InIKRigSkeleton);`
- L179 _private member_ `bool bIsInitialized = false;`
- L180 _private member_ `TArray<int32> BoneIndices;`
- L181 _private member_ `TArray<int32> ChildrenToUpdate;`
- L183 _private member_ `TArray<FVector> BonePositionsPreOffset;`
- L184 _private member_ `TArray<double> RestLengths;`
- L185 _private member_ `double TotalRestLength;`
- L186 _private member_ `TArray<double> PoleVectorParams;`
- L187 _private member_ `double InitialPoleVectorLenSq;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API IKRIG_API`

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/LimbSolver.h` (Public)


#### struct `FLimbSolverSettings`  
`struct FLimbSolverSettings : public FIKRigSolverSettingsBase`  
_L10-63_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FIKRigSolverSettingsBase`
- L15 _public prototype_ `virtual ~FLimbSolverSettings() = default;` — make this polymorphic
- L19 _public member_ `float ReachPrecision = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings", meta = (ClampMin = "0.0"))` — Precision (distance to the target)
- L25 _public member_ `TEnumAsByte<EAxis::Type> HingeRotationAxis = EAxis::None;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|Two Bones")` — Hinge Bones Rotation Axis. This is essentially the plane normal for (hip - knee - foot).
- L31 _public member_ `int32 MaxIterations = 12;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK", meta = (ClampMin = "0", UIMin = "0", UIMax = "100"))` — Number of Max Iterations to reach the target
- L35 _public member_ `bool bEnableLimit = false;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK|Limits")` — Enable/Disable rotational limits
- L40 _public member_ `float MinRotationAngle = 15.f;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK|Limits", meta = (EditCondition="bEnableLimit", ClampMin = "0.0", ClampMax = "90.0", UIMin = "0.0", UIMax = "90.0"))` — Only used if bEnableRotationLimit is enabled. Prevents the leg from folding onto itself, and forces at least this angle between Parent and Child bone.
- L44 _public member_ `bool bAveragePull = true;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK|Pull Averaging")` — Pull averaging only has a visual impact when we have more than 2 bones (3 links).
- L48 _public member_ `float PullDistribution = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK|Pull Averaging", meta = (ClampMin = "0.0", ClampMax = "1.0",UIMin = "0.0", UIMax = "1.0"))` — Re-position limb to distribute pull: 0 = foot, 0.5 = balanced, 1.f = hip
- L52 _public member_ `float ReachStepAlpha = 0.7f;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|FABRIK|Pull Averaging", meta = (ClampMin = "0.0", ClampMax = "1.0",UIMin = "0.0", UIMax = "1.0"))` — Move end effector towards target. If we are compressing the chain, limit displacement.
- L58 _public member_ `bool bEnableTwistCorrection = false;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|Twist")` — Enable Knee Twist correction, by comparing Foot FK with Foot IK orientation.
- L62 _public member_ `TEnumAsByte<EAxis::Type> EndBoneForwardAxis = EAxis::Y;` — `UPROPERTY(EditAnywhere, Category = "Limb Solver Settings|Twist", meta = (EditCondition="bEnableTwistCorrection"))` — Forward Axis for Foot bone.

#### struct `FLimbLink`  
`struct FLimbLink`  
_L66-101_
- reflection: `USTRUCT()`
- L71 _public member_ `FVector Location;` — Location of bone in component space.
- L74 _public member_ `float Length;` — Distance to its parent
- L77 _public member_ `int32 BoneIndex;` — Bone Index in SkeletalMesh
- L80 _public member_ `FVector LinkAxisZ;` — Axis utilites
- L81 _public member_ `FVector RealBendDir;`
- L82 _public member_ `FVector BaseBendDir;`
- L84 _public function_ `FLimbLink() : Location(FVector::ZeroVector) , Length(0.f) , BoneIndex( INDEX_NONE ) , LinkAxisZ(FVector::ZeroVector) , RealBendDir(FVector::ZeroVector) , BaseBendDir(FVector::ZeroVector)`
- L93 _public function_ `FLimbLink(const FVector& InLocation, int32 InBoneIndex) : Location(InLocation) , Length(0.f) , BoneIndex(InBoneIndex) , LinkAxisZ(FVector::ZeroVector) , RealBendDir(FVector::ZeroVector) , BaseBendDir(FVector::ZeroVector)`

#### struct `FLimbSolver`  
`struct FLimbSolver`  
_L104-129_
- reflection: `USTRUCT()`
- L108 _public prototype_ `void Reset();`
- L109 _public prototype_ `bool Initialize();`
- L110 _public prototype_ `bool Solve( TArray<FTransform>& InOutTransforms, const FVector& InGoalLocation, const FQuat& InGoalRotation, const FLimbSolverSettings& InSettings);`
- L116 _public prototype_ `int32 AddLink(const FVector& InLocation, int32 InBoneIndex);`
- L117 _public prototype_ `int32 GetBoneIndex(const int32 Index) const;`
- L118 _public prototype_ `int32 NumLinks() const;`
- L122 _private prototype_ `void UpdateTransforms(TArray<FTransform>& InOutTransforms);`
- L123 _private prototype_ `bool OrientTransformsTowardsGoal(TArray<FTransform>& InOutTransforms, const FVector& InGoalLocation) const;`
- L124 _private prototype_ `bool AdjustKneeTwist(TArray<FTransform>& InOutTransforms, const FTransform& InGoalTransform, const EAxis::Type FootBoneForwardAxis );`
- L126 _private member_ `float Length = 0.f;`
- L128 _private member_ `TArray<FLimbLink> Links;`

#### Free symbols / members of external scopes

- L131 _namespace_ `namespace AnimationCore`
- L151 _prototype_ `bool SolveLimb( TArray<FLimbLink>& InOutLinks, float LimbLength, const FVector& GoalLocation, float Precision, int32 InMaxIterations, const FVector& HingeRotationAxis, bool bUseAngleLimit, float MinRotationAngle, float ReachStepAlpha, bool bAveragePull, float PullDistribution);` (scope `AnimationCore`) — Limb solver This solves a hybrid TwoBoneIK / FABRIK based on the number of links within the chain @param	InOutLinks			Array of chain links @param	LimbLength			The full length on the limb (sum of all links' length) @param	GoalLocation		The location of the IK target @param	Precision			Precision @param	InMaxIterations		Number of Max Iteration (used for FABRIK only) @param	HingeRotationAxis	Hinge Bones Rotation Axis. This is essentially the plane normal for (hip - knee - foot). (used for TwoBones only) @param	bUseAngleLimit		Enable/Disable rotational limits (used for FABRIK only) @param	MinRotationAngle	Prevents the leg from folding onto itself, and forces at least this angle between Parent and Child bone (used for FABRIK only) @param	ReachStepAlpha		Move end effector towards target. If we are compressing the chain, limit displacement. (used for FABRIK only) * @param	bAveragePull		Pull averaging only has a visual impact when we have more than 2 bones (3 links). (used for FABRIK only) @param	PullDistribution	Re-position limb to distribute pull: 0 = foot, 0.5 = balanced, 1.f = hip. (used for FABRIK only) @return  true if modified. False if not.

### `Plugins/Animation/IKRig/Source/IKRig/Public/Rig/Solvers/PointsToRotation.h` (Public)


#### Free symbols / members of external scopes

- L11 _function_ `static FQuat GetRotationFromDeformedPoints( const TArray<FVector>& InInitialPoints, const TArray<FVector>& InCurrentPoints, FVector& OutInitialCentroid, FVector& OutCurrentCentroid)` — given a set of points in an initial configuration and the same set of points in a deformed configuration, this function outputs a quaternion that represents the "best fit" rotation that rotates the initial points to the current points.
