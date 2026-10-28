# Runtime / AnimGraphRuntime

- module root: `Source/Runtime/AnimGraphRuntime`
- headers: 90; symbols: 2383
- symbol kinds: class=26, delegate=5, enum=44, enumerator=151, externvar=9, function=220, macro=7, member=965, namespace=5, prototype=808, struct=129, typedef=14
- PrivateDependencyModuleNames: TraceLog
- PublicDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, GeometryCollectionEngine

### `Source/Runtime/AnimGraphRuntime/Public/AnimCustomInstanceHelper.h` (Public)


#### class `FAnimCustomInstanceHelper`  
`class FAnimCustomInstanceHelper`  
_L36-292_
- L44 _public function_ `template<typename InstanceClassType> static InstanceClassType* BindToSkeletalMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent, bool& bOutWasCreated)` — Called to bind a typed UAnimCustomInstance to an existing skeletal mesh component @return the current (or newly created) UAnimCustomInstance
- L191 _public function_ `template<typename InstanceClassType> static void UnbindFromSkeletalMeshComponent(USkeletalMeshComponent* InSkeletalMeshComponent)` — Called to unbind a UAnimCustomInstance to an existing skeletal mesh component
- L291 _private prototype_ `static bool ShouldCreateCustomInstancePlayer(const USkeletalMeshComponent* SkeletalMeshComponent);` — Helper function for BindToSkeletalMeshComponent

### `Source/Runtime/AnimGraphRuntime/Public/AnimExecutionContextLibrary.h` (Public)


#### class `UAnimExecutionContextLibrary`  
`class UAnimExecutionContextLibrary : public UBlueprintFunctionLibrary`  
_L15-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on anim node contexts
- L23 _public function_ `void Prototype_ThreadSafeAnimNodeCall(const FAnimExecutionContext& Context, const FAnimNodeReference& Node)` — `UFUNCTION(BlueprintInternalUseOnly, meta=(BlueprintThreadSafe))` — Prototype function for thread-safe anim node calls
- L27 _public function_ `void Prototype_ThreadSafeAnimUpdateCall(const FAnimUpdateContext& Context, const FAnimNodeReference& Node)` — `UFUNCTION(BlueprintInternalUseOnly, meta=(BlueprintThreadSafe))` — Prototype function for thread-safe anim update calls
- L32 _public prototype_ `static UAnimInstance* GetAnimInstance(const FAnimExecutionContext& Context);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta=(BlueprintThreadSafe))` — Get the anim instance that hosts this context
- L36 _public prototype_ `static FAnimNodeReference GetAnimNodeReference(UAnimInstance* Instance, int32 Index);` — `UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(BlueprintThreadSafe, DefaultToSelf = "Instance"))` — Internal compiler use only - Get a reference to an anim node by index
- L40 _public prototype_ `static FAnimInitializationContext ConvertToInitializationContext(const FAnimExecutionContext& Context, EAnimExecutionContextConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Convert to an initialization context
- L44 _public prototype_ `static FAnimUpdateContext ConvertToUpdateContext(const FAnimExecutionContext& Context, EAnimExecutionContextConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Convert to an update context
- L48 _public prototype_ `static float GetDeltaTime(const FAnimUpdateContext& Context);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta=(BlueprintThreadSafe))` — Get the current delta time in seconds
- L52 _public prototype_ `static float GetCurrentWeight(const FAnimUpdateContext& Context);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta=(BlueprintThreadSafe))` — Get the current weight of this branch of the graph
- L56 _public prototype_ `static bool IsActive(const FAnimExecutionContext& Context);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta=(BlueprintThreadSafe))` — Get whether this branch of the graph is active (i.e. NOT blending out).
- L60 _public prototype_ `static FAnimPoseContext ConvertToPoseContext(const FAnimExecutionContext& Context, EAnimExecutionContextConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Convert to a pose context
- L64 _public prototype_ `static FAnimComponentSpacePoseContext ConvertToComponentSpacePoseContext(const FAnimExecutionContext& Context, EAnimExecutionContextConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Convert to a component space pose context

### `Source/Runtime/AnimGraphRuntime/Public/AnimGraphRuntimeTrace.h` (Public)


#### struct `FAnimGraphRuntimeTrace`  
`struct FAnimGraphRuntimeTrace`  
_L16-36_
- L19 _public prototype_ `static void OutputBlendSpacePlayer(const FAnimationBaseContext& InContext, const FAnimNode_BlendSpacePlayerBase& InNode);` — Helper function to output debug info for blendspace player nodes
- L22 _public prototype_ `static void OutputBlendSpace(const FAnimationBaseContext& InContext, const FAnimNode_BlendSpaceGraphBase& InNode);` — Helper function to output debug info for blendspace nodes
- L30 _public prototype_ `static void OutputBlendSpacePlayerValues( const FAnimationBaseContext& InContext, int32 InNodeId, const UBlendSpace* InBlendSpace, FVector InPosition, FVector InFilteredPosition);` — Helper function to output blend space player debug info from a custom node that does not inherit from FAnimNode_BlendSpacePlayerBase or FAnimNode_BlendSpaceGraphBase. Uses a caller-supplied node ID so it works correctly when called from Evaluate_AnyThread where the context's current node ID may not be set.

#### Free symbols / members of external scopes

- L38 _macro_ `#define TRACE_BLENDSPACE_PLAYER(Context, Node) \`
- L41 _macro_ `#define TRACE_BLENDSPACE(Context, Node) \`
- L46 _macro_ `#define TRACE_BLENDSPACE_PLAYER(Context, Node)`
- L47 _macro_ `#define TRACE_BLENDSPACE(Context, Node)`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_AimOffsetLookAt.h` (Public)


#### struct `FAnimNode_AimOffsetLookAt`  
`struct FAnimNode_AimOffsetLookAt : public FAnimNode_BlendSpacePlayer`  
_L16-92_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpacePlayer`
- desc: This node uses a source transform of a socket on the skeletal mesh to automatically calculate Yaw and Pitch directions for a referenced aim offset given a point in the world to look at.
- L21 _public member_ `FTransform SocketLocalTransform;` — Cached local transform of the source socket
- L24 _public member_ `FTransform PivotSocketLocalTransform;` — Cached local transform of the pivot socket
- L27 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L36 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L40 _public member_ `FName SourceSocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))` — Socket or bone to treat as the look at source. This will then be pointed at LookAtLocation
- L48 _public member_ `FName PivotSocketName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))` — Socket or bone to treat as the look at pivot (optional). This will overwrite the translation of the source socket transform improve the lookat direction, especially when the target is close to the character
- L52 _public member_ `FVector LookAtLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))` — Location, in world space to look at
- L56 _public member_ `FVector SocketAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinHiddenByDefault))` — Direction in the socket transform to consider the 'forward' or look at axis
- L60 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LookAt, meta = (PinShownByDefault))` — Amount of this node to blend into the output pose
- L63 _public member_ `FVector CurrentBlendInput;` — Cached calculated blend input
- L66 _public member_ `FBoneReference SocketBoneReference;` — Cached reference to the source socket's bone
- L69 _public member_ `FBoneReference PivotSocketBoneReference;` — Cached reference to the pivot socket's bone
- L72 _public member_ `bool bIsLODEnabled;` — Cached flag to indicate whether LOD threshold is enabled
- L75 _public prototype_ `FAnimNode_AimOffsetLookAt();`
- L78 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;` — FAnimNode_Base interface
- L79 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L80 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L81 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L82 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L83 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L84 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L85 _public function_ `virtual int32 GetLODThreshold() const override`
- L89 _public prototype_ `virtual FVector GetPosition() const override;` — FAnimNode_BlendSpacePlayer interface
- L91 _public prototype_ `void UpdateFromLookAtTarget(FPoseContext& LocalPoseContext);`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_ApplyAdditive.h` (Public)


#### struct `FAnimNode_ApplyAdditive`  
`struct FAnimNode_ApplyAdditive : public FAnimNode_Base`  
_L12-66_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L17 _public member_ `FPoseLink Base;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L20 _public member_ `FPoseLink Additive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L23 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Alpha, meta=(PinShownByDefault))`
- L26 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Alpha)`
- L35 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta=(DisplayName="LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L38 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayName = "Blend Settings", DisplayAfter = "bAlphaBoolEnabled"))`
- L41 _public member_ `FName AlphaCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))`
- L44 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L46 _public member_ `float ActualAlpha;`
- L49 _public member_ `EAnimAlphaInputType AlphaInputType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayAfter = "AlphaScaleBias"))`
- L52 _public member_ `bool bAlphaBoolEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, DisplayName = "bEnabled", DisplayAfter = "AlphaInputType"))`
- L55 _public prototype_ `FAnimNode_ApplyAdditive();`
- L58 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L59 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L60 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L61 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L62 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L63 _public function_ `virtual int32 GetLODThreshold() const override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendBoneByChannel.h` (Public)


#### struct `FBlendBoneByChannelEntry`  
`struct FBlendBoneByChannelEntry`  
_L13-43_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L19 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Bone to take Transform from
- L23 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Bone to apply Transform to
- L27 _public member_ `bool bBlendTranslation;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Copy Translation from Source to Target
- L31 _public member_ `bool bBlendRotation;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Copy Rotation from Source to Target
- L35 _public member_ `bool bBlendScale;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Copy Scale from Source to Target
- L37 _public function_ `FBlendBoneByChannelEntry() : bBlendTranslation(true) , bBlendRotation(true) , bBlendScale(true)`

#### struct `FAnimNode_BlendBoneByChannel`  
`struct FAnimNode_BlendBoneByChannel : public FAnimNode_Base`  
_L46-100_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L53 _public member_ `FPoseLink A;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L56 _public member_ `FPoseLink B;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L59 _public member_ `TArray<FBlendBoneByChannelEntry> BoneDefinitions;` — `UPROPERTY(EditAnywhere, Category = Blend, meta = (DisplayAfter = "AlphaScaleBias"))`
- L64 _private member_ `TArray<FBlendBoneByChannelEntry> ValidBoneEntries;` — Array of bone entries, that has been validated to be correct at runtime. So we don't have to perform validation checks per frame.
- L68 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault, DisplayAfter = "B"))`
- L71 _private member_ `float InternalBlendAlpha;`
- L75 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L79 _public member_ `TEnumAsByte<EBoneControlSpace> TransformsSpace;` — `UPROPERTY(EditAnywhere, Category = Blend)` — Space to convert transforms into prior to copying channels
- L82 _private member_ `bool bBIsRelevant;`
- L85 _public function_ `FAnimNode_BlendBoneByChannel() : Alpha(0.0f) , InternalBlendAlpha(0.0f) , TransformsSpace(EBoneControlSpace::BCS_BoneSpace) , bBIsRelevant(false)`
- L94 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L95 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L96 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L97 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L98 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendListBase.h` (Public)


#### enum `EBlendListTransitionType`  
`enum class EBlendListTransitionType : uint8`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `StandardBlend`
- L19 _public enumerator_ `Inertialization`

#### enum `EBlendListChildUpdateMode`  
`enum class EBlendListChildUpdateMode : uint8`  
_L23-33_
- reflection: `UENUM()`
- L26 _public enumerator_ `Default` — Do not tick inactive children, do not reset on activate
- L29 _public enumerator_ `ResetChildOnActivate` — This reinitializes the re-activated child
- L32 _public enumerator_ `AlwaysTickChildren` — Always tick children even if they are not active

#### struct `FAnimNode_BlendListBase`  
`struct FAnimNode_BlendListBase : public FAnimNode_Base`  
_L37-157_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Blend list node; has many children
- L43 _protected member_ `TArray<FPoseLink> BlendPose;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=Links)`
- L48 _private member_ `TArray<float> BlendTime;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=Config, meta=(PinShownByDefault, FoldProperty))`
- L51 _private member_ `EBlendListTransitionType TransitionType = EBlendListTransitionType::StandardBlend;` — `UPROPERTY(EditAnywhere, Category=Config, meta=(FoldProperty))`
- L54 _private member_ `EAlphaBlendOption BlendType = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, Category=BlendType, meta=(FoldProperty))`
- L59 _protected member_ `bool bResetChildOnActivation_DEPRECATED = false;` — `UE_DEPRECATED(5.6, "Use ChildUpateMode instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use the ChildUpateMode instead"))`
- L62 _protected member_ `EBlendListChildUpdateMode ChildUpateMode = EBlendListChildUpdateMode::Default;` — `UPROPERTY(EditAnywhere, Category = Option, meta=(FoldProperty))`
- L66 _private member_ `TObjectPtr<UCurveFloat> CustomBlendCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category=BlendType, meta=(FoldProperty))`
- L69 _private member_ `TObjectPtr<UBlendProfile> BlendProfile = nullptr;` — `UPROPERTY(EditAnywhere, Category=BlendType, meta=(UseAsBlendProfile=true, FoldProperty))`
- L82 _protected member_ `TArray<FBlendData> PerBlendData;`
- L85 _protected member_ `TArray<FBlendSampleData> PerBoneSampleData;` — Per-bone blending data, allocated when using blend profiles
- L87 _protected member_ `int32 LastActiveChildIndex = 0;`
- L91 _protected member_ `UBlendProfile* CurrentBlendProfile = nullptr;` — The blend profile used for the current blend Note its possible that the blend profile changes based on the active child
- L97 _public prototype_ `FAnimNode_BlendListBase() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables this is a requirement for clang to compile without warnings.
- L98 _public prototype_ `~FAnimNode_BlendListBase() = default;`
- L99 _public prototype_ `FAnimNode_BlendListBase(const FAnimNode_BlendListBase&) = default;`
- L100 _public prototype_ `FAnimNode_BlendListBase(FAnimNode_BlendListBase&&) = default;`
- L101 _public prototype_ `FAnimNode_BlendListBase& operator=(const FAnimNode_BlendListBase&) = default;`
- L102 _public prototype_ `FAnimNode_BlendListBase& operator=(FAnimNode_BlendListBase&&) = default;`
- L107 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L108 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L109 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L110 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L111 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L115 _public function_ `virtual void AddPose()`
- L121 _public function_ `virtual void RemovePose(int32 PoseIndex)`
- L130 _public prototype_ `const TArray<float>& GetBlendTimes() const;` — Get the array of blend times to apply to our input poses
- L133 _public prototype_ `EBlendListTransitionType GetTransitionType() const;` — Get the type of transition that this blend list will make
- L136 _public prototype_ `EAlphaBlendOption GetBlendType() const;` — Get the blend type we will use when blending
- L139 _public prototype_ `EBlendListChildUpdateMode GetChildUpdateMode() const;` — Get the child update mode.
- L142 _public prototype_ `UCurveFloat* GetCustomBlendCurve() const;` — Get the custom blend curve to apply when blending, if any
- L146 _public prototype_ `virtual UBlendProfile* GetBlendProfile() const;` — Get the blend profile to use when blending, if any Note that its possible for the blend profile to change based on the active child
- L149 _protected function_ `virtual int32 GetActiveChildIndex()`
- L150 _protected function_ `virtual FString GetNodeName(FNodeDebugData& DebugData)`
- L152 _protected prototype_ `void Initialize();`
- L153 _protected prototype_ `void InitializePerBoneData();`
- L154 _protected prototype_ `void SetCurrentBlendProfile(UBlendProfile* NewBlendProfile);`

#### struct `FAnimNode_BlendListBase::FBlendData`  
`struct FBlendData`  
_L74-80_
- desc: Struct for tracking blends for each pose
- L76 _public member_ `FAlphaBlend Blend;`
- L77 _public member_ `float Weight;`
- L78 _public member_ `float RemainingTime;`
- L79 _public member_ `float StartAlpha;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendListByBool.h` (Public)


#### struct `FAnimNode_BlendListByBool`  
`struct FAnimNode_BlendListByBool : public FAnimNode_BlendListBase`  
_L12-49_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendListBase`
- desc: This node is effectively a 'branch', picking one of two input poses based on an input Boolean value
- L19 _private member_ `TObjectPtr<UBlendProfile> BlendProfileForFalse = nullptr;` — `UPROPERTY(EditAnywhere, Category = BlendType, meta = (UseAsBlendProfile = true, FoldProperty, EditCondition="bUseSeperateBlendProfileForFalse", DisplayAfter="bUseSeperateBlendProfileForFalse"))` — Used in conjunction with bUseSeperateBlendProfileForFalse
- L27 _private member_ `bool bUseSeperateBlendProfileForFalse = false;` — `UPROPERTY(EditAnywhere, Category = BlendType, meta = (FoldProperty, DisplayAfter="BlendProfile"))` — Specify whether to use a different blend profile for the 'false' branch than the true branch. If bUseSeperateBlendProfileForFalse is false (default), then the 'BlendProfile' is used when ActiveValue is both true or false If bUseSeperateBlendProfileForFalse is true, then the 'BlendProfileForFalse' value is used when the ActiveValue is false, but 'BlendProfile' is used when ActiveValue is true
- L31 _private member_ `bool bActiveValue = false;` — `UPROPERTY(EditAnywhere, Category=Runtime, meta=(PinShownByDefault, FoldProperty))` — Which input should be connected to the output?
- L35 _public prototype_ `FAnimNode_BlendListByBool() = default;`
- L38 _public prototype_ `bool GetActiveValue() const;` — Get which input should be connected to the output
- L40 _public prototype_ `bool GetUseSeperateBlendProfiles() const;`
- L42 _public prototype_ `UBlendProfile* GetBlendProfileForFalse() const;`
- L45 _protected prototype_ `virtual int32 GetActiveChildIndex() override;`
- L46 _protected function_ `virtual FString GetNodeName(FNodeDebugData& DebugData) override`
- L48 _protected prototype_ `virtual UBlendProfile* GetBlendProfile() const override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendListByEnum.h` (Public)


#### struct `FAnimNode_BlendListByEnum`  
`struct FAnimNode_BlendListByEnum : public FAnimNode_BlendListBase`  
_L12-44_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendListBase`
- desc: Blend List by Enum, it changes based on enum input that enters
- L20 _private member_ `TArray<int32> EnumToPoseIndex;` — `UPROPERTY(meta=(FoldProperty))` — Mapping from enum value to BlendPose index; there will be one entry per entry in the enum; entries out of range always map to pose index 0
- L24 _private member_ `mutable uint8 ActiveEnumValue = 0;` — `UPROPERTY(EditAnywhere, Category=Runtime, meta=(PinShownByDefault, FoldProperty))` — The currently selected pose (as an enum value)
- L28 _public prototype_ `FAnimNode_BlendListByEnum() = default;`
- L32 _public prototype_ `void SetEnumToPoseIndex(const TArray<int32>& InEnumToPoseIndex);` — Set the mapping from enum value to BlendPose index. Called during compilation.
- L36 _public prototype_ `const TArray<int32>& GetEnumToPoseIndex() const;` — Get the mapping from enum value to BlendPose index; there will be one entry per entry in the enum; entries out of range always map to pose index 0
- L39 _public prototype_ `uint8 GetActiveEnumValue() const;` — Get the currently selected pose (as an enum value)
- L42 _protected prototype_ `virtual int32 GetActiveChildIndex() override;`
- L43 _protected function_ `virtual FString GetNodeName(FNodeDebugData& DebugData) override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendListByInt.h` (Public)


#### struct `FAnimNode_BlendListByInt`  
`struct FAnimNode_BlendListByInt : public FAnimNode_BlendListBase`  
_L12-29_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendListBase`
- desc: Blend list node; has many children
- L18 _private member_ `int32 ActiveChildIndex = 0;` — `UPROPERTY(EditAnywhere, Category=Runtime, meta=(PinShownByDefault, FoldProperty))`
- L22 _public prototype_ `FAnimNode_BlendListByInt() = default;`
- L25 _public prototype_ `virtual int32 GetActiveChildIndex() override;` — Get the currently active child index
- L28 _protected function_ `virtual FString GetNodeName(FNodeDebugData& DebugData) override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendSpaceEvaluator.h` (Public)


#### struct `FAnimNode_BlendSpaceEvaluator`  
`struct FAnimNode_BlendSpaceEvaluator : public FAnimNode_BlendSpacePlayer`  
_L16-53_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpacePlayer`
- desc: Evaluates a BlendSpace at a specific using a specific time input rather than advancing time internally. Typically the playback position of the animation for this node will represent something other than time, like jump height. Note that events output from the sequences playing and being blended together should not be used. In addition, synchronization of animations will potentially be discontinuous if the blend weights are updated, as the leader/follower changes.
- L29 _public member_ `float NormalizedTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))` — Normalized time between [0,1]. The actual length of a blendspace is dynamic based on the coordinate, so it is exposed as a normalized value. Note that treating this as a "time" value that increases (and wraps) will not result in the same output as you would get from using a BlendSpace player. The output events may not be as expected, and synchronization will sometimes be discontinuous if the leader/follower animations change as a result of changing the blend weights (even if that is done smoothly).
- L37 _public member_ `bool bTeleportToNormalizedTime = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If true, teleport to normalized time, does NOT advance time (does not trigger notifies, does not extract Root Motion, etc.). If false, will advance time (will trigger notifies, extract root motion if applicable, etc).
- L40 _public prototype_ `FAnimNode_BlendSpaceEvaluator();`
- L43 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;` — FAnimNode_Base interface
- L44 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L48 _public prototype_ `virtual float GetPlayRate() const override;` — FAnimNode_BlendSpacePlayer interface
- L49 _public function_ `virtual bool ShouldTeleportToTime() const override`
- L50 _public function_ `virtual bool IsEvaluator() const override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendSpaceGraph.h` (Public)


#### struct `FAnimNode_BlendSpaceGraph`  
`struct FAnimNode_BlendSpaceGraph : public FAnimNode_BlendSpaceGraphBase`  
_L11-17_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpaceGraphBase`
- desc: Allows multiple animations to be blended between based on input parameters
- L16 _public function_ `FName GetGroupName() const` — @return the sync group that this blendspace uses

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendSpaceGraphBase.h` (Public)


#### struct `FAnimNode_BlendSpaceGraphBase`  
`struct FAnimNode_BlendSpaceGraphBase : public FAnimNode_Base`  
_L15-96_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Allows multiple animations to be blended between based on input parameters
- L22 _public function_ `const UBlendSpace* GetBlendSpace() const` — @return the blendspace that this node uses
- L25 _public function_ `FVector GetPosition() const` — @return the current sample coordinates that this node is using to sample the blendspace
- L28 _public function_ `FVector GetFilteredPosition() const` — @return the current sample coordinates after going through the filtering
- L32 _public prototype_ `void SetPreviewPosition(FVector InVector);` — Set the node to preview a supplied sample value
- L36 _public prototype_ `void SnapToPosition(const FVector& NewPosition);` — Forces the Position to the specified value
- L41 _protected member_ `float X = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Coordinates, meta = (PinShownByDefault, AllowPrivateAccess))` — The X coordinate to sample in the blendspace
- L45 _protected member_ `float Y = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Coordinates, meta = (PinShownByDefault, AllowPrivateAccess))` — The Y coordinate to sample in the blendspace
- L52 _protected member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sync, meta = (NeverAsPin, AllowPrivateAccess))` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it. Animations inside this Blend Space have their own options for syncing.
- L57 _protected member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sync, meta = (NeverAsPin, AllowPrivateAccess))` — The role this Blend Space can assume within the group (ignored if GroupName is not set). Note that this is the role of the output of this node, not of animations contained by it.
- L61 _protected member_ `TObjectPtr<const UBlendSpace> BlendSpace = nullptr;` — `UPROPERTY()` — The internal blendspace asset to play
- L65 _protected member_ `TArray<FPoseLink> SamplePoseLinks;` — `UPROPERTY()` — Pose links for each sample in the blendspace
- L69 _protected member_ `FBlendFilter BlendFilter;` — FIR filter applied to inputs
- L72 _protected member_ `TArray<FBlendSampleData> BlendSampleDataCache;` — Cache of sampled data, updated each frame
- L75 _protected member_ `int32 CachedTriangulationIndex = -1;` — Previous position in the triangulation/segmentation
- L79 _protected member_ `FVector PreviewPosition = FVector::ZeroVector;` — Preview blend params - set in editor only
- L82 _protected member_ `bool bUsePreviewPosition = false;` — Whether to use the preview blend params
- L86 _protected prototype_ `void UpdateInternal(const FAnimationUpdateContext& Context);` — Internal update handler, skipping evaluation of exposed inputs
- L90 _protected prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L91 _protected prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L92 _protected prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L93 _protected prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L94 _protected prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendSpacePlayer.h` (Public)


#### struct `FAnimNode_BlendSpacePlayerBase`  
`struct FAnimNode_BlendSpacePlayerBase : public FAnimNode_AssetPlayerBase`  
_L15-103_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_AssetPlayerBase`
- desc: @TODO: Comment
- L21 _protected member_ `FBlendFilter BlendFilter;` — Filter used to dampen coordinate changes
- L24 _protected member_ `TArray<FBlendSampleData> BlendSampleDataCache;` — Cache of samples used to determine blend weights
- L27 _protected member_ `int32 CachedTriangulationIndex = -1;` — Previous position in the triangulation/segmentation
- L30 _protected member_ `TObjectPtr<UBlendSpace> PreviousBlendSpace = nullptr;` — `UPROPERTY(Transient)`
- L35 _public prototype_ `virtual float GetCurrentAssetTime() const override;` — FAnimNode_AssetPlayerBase interface
- L36 _public prototype_ `virtual float GetCurrentAssetTimePlayRateAdjusted() const override;`
- L37 _public prototype_ `virtual float GetCurrentAssetLength() const override;`
- L38 _public prototype_ `virtual UAnimationAsset* GetAnimAsset() const override;`
- L42 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L43 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L44 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L45 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L46 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L50 _public prototype_ `float GetTimeFromEnd(float CurrentTime) const;` — Get the amount of time from the end
- L53 _public function_ `FVector GetFilteredPosition() const` — @return the current sample coordinates after going through the filtering
- L56 _public prototype_ `void SnapToPosition(const FVector& NewPosition);` — Forces the Position to the specified value
- L61 _public prototype_ `virtual UBlendSpace* GetBlendSpace() const PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::GetBlendSpace, return nullptr;);` — Get the blendspace asset to play
- L64 _public prototype_ `virtual FVector GetPosition() const PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::GetPosition, return FVector::Zero(););` — Get the coordinates that are currently being sampled by the blendspace
- L67 _public prototype_ `virtual float GetStartPosition() const PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::GetStartPosition, return 0.0f;);` — The start position in [0, 1] to use when initializing. When looping, play will still jump back to the beginning when reaching the end.
- L70 _public prototype_ `virtual float GetPlayRate() const PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::GetPlayRate, return 1.0f;);` — Get the play rate multiplier. Can be negative, which will cause the animation to play in reverse.
- L73 _public prototype_ `virtual bool ShouldResetPlayTimeWhenBlendSpaceChanges() const PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::ShouldResetPlayTimeWhenBlendSpaceChanges, return true;);` — Get whether we should reset the current play time when the blend space changes
- L76 _public prototype_ `virtual bool SetResetPlayTimeWhenBlendSpaceChanges(bool bReset) PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::SetResetPlayTimeWhenBlendSpaceChanges, return false;);` — Set whether we should reset the current play time when the blend space changes
- L79 _public function_ `virtual bool ShouldTeleportToTime() const` — An evaluator will be setting the play rate to zero and setting the time explicitly. ShouldTeleportToTime indicates whether we should jump to that time, or move to it playing out root motion and events etc.
- L82 _public function_ `virtual bool IsEvaluator() const` — Indicates if we are an evaluator - i.e. will be setting the time explicitly rather than letting it play out
- L85 _public prototype_ `virtual bool SetBlendSpace(UBlendSpace* InBlendSpace) PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::SetBlendSpace, return false;);` — Set the blendspace asset to play
- L88 _public prototype_ `virtual bool SetPosition(FVector InPosition) PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::SetPosition, return false;);` — Set the coordinates that are currently being sampled by the blendspace
- L91 _public prototype_ `virtual bool SetPlayRate(float InPlayRate) PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::SetPlayRate, return false;);` — Set the play rate multiplier. Can be negative, which will cause the animation to play in reverse.
- L94 _public prototype_ `virtual bool SetLoop(bool bInLoop) PURE_VIRTUAL(FAnimNode_BlendSpacePlayerBase::SetLoop, return false;);` — Set if the animation should loop back to the start when it reaches the end?
- L97 _protected prototype_ `void UpdateInternal(const FAnimationUpdateContext& Context);`
- L100 _private prototype_ `void Reinitialize(bool bResetTime = true);`
- L102 _private prototype_ `const FBlendSampleData* GetHighestWeightedSample() const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_BlendSpacePlayerBase> : public TStructOpsTypeTraitsBase2<FAnimNode_BlendSpacePlayerBase>`  
_L106-112_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_BlendSpacePlayerBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L109-111_

#### struct `FAnimNode_BlendSpacePlayer`  
`struct FAnimNode_BlendSpacePlayer : public FAnimNode_BlendSpacePlayerBase`  
_L117-211_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpacePlayerBase`
- desc: @TODO: Comment
- L134 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it.
- L139 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — The role this node can assume within the group (ignored if GroupName is not set). Note that this is the role of the output of this node, not of animations contained by it.
- L143 _private member_ `bool bOverridePositionWhenJoiningSyncGroupAsLeader = false;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty, EditCondition = "GroupRole != EAnimGroupRole::TransitionFollower && GroupRole != EAnimGroupRole::AlwaysFollower", EditConditionHides))` — When enabled, acting as the leader, and using marker-based sync, this asset player will not sync to the previous leader's sync position when joining a sync group and before becoming the leader but instead force everyone else to match its position.
- L148 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (FoldProperty))` — How this node will synchronize with other animations. Note that this determines how the output of this node is used for synchronization, not of animations contained by it.
- L152 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L156 _private member_ `float X = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Coordinates, meta = (PinShownByDefault, FoldProperty))` — The X coordinate to sample in the blendspace
- L160 _private member_ `float Y = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Coordinates, meta = (PinShownByDefault, FoldProperty))` — The Y coordinate to sample in the blendspace
- L164 _private member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "1.0", PinHiddenByDefault, FoldProperty))` — The play rate multiplier. Can be negative, which will cause the animation to play in reverse.
- L168 _private member_ `bool bLoop = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "true", PinHiddenByDefault, FoldProperty))` — Should the animation loop back to the start when it reaches the end?
- L172 _private member_ `bool bResetPlayTimeWhenBlendSpaceChanges = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, FoldProperty))` — Whether we should reset the current play time when the blend space changes
- L176 _private member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "0.f", PinHiddenByDefault, FoldProperty))` — The start position in [0, 1] to use when initializing. When looping, play will still jump back to the beginning when reaching the end.
- L181 _private member_ `TObjectPtr<UBlendSpace> BlendSpace = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — The blendspace asset to play
- L186 _public prototype_ `virtual FName GetGroupName() const override;` — FAnimNode_AssetPlayerBase interface
- L187 _public prototype_ `virtual EAnimGroupRole::Type GetGroupRole() const override;`
- L188 _public prototype_ `virtual bool GetOverridePositionWhenJoiningSyncGroupAsLeader() const override;`
- L189 _public prototype_ `virtual EAnimSyncMethod GetGroupMethod() const override;`
- L190 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L191 _public prototype_ `virtual bool IsLooping() const override;`
- L192 _public prototype_ `virtual bool SetGroupName(FName InGroupName) override;`
- L193 _public prototype_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override;`
- L194 _public prototype_ `virtual bool SetOverridePositionWhenJoiningSyncGroupAsLeader(bool InOverridePositionWhenJoiningSyncGroupAsLeader) override;`
- L195 _public prototype_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override;`
- L196 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L200 _public prototype_ `virtual UBlendSpace* GetBlendSpace() const override;` — FAnimNode_BlendSpacePlayerBase interface
- L201 _public prototype_ `virtual FVector GetPosition() const override;`
- L202 _public prototype_ `virtual float GetStartPosition() const override;`
- L203 _public prototype_ `virtual float GetPlayRate() const override;`
- L204 _public prototype_ `virtual bool ShouldResetPlayTimeWhenBlendSpaceChanges() const override;`
- L205 _public prototype_ `virtual bool SetResetPlayTimeWhenBlendSpaceChanges(bool bReset) override;`
- L206 _public prototype_ `virtual bool SetBlendSpace(UBlendSpace* InBlendSpace) override;`
- L207 _public prototype_ `virtual bool SetPosition(FVector InPosition) override;`
- L208 _public prototype_ `virtual bool SetPlayRate(float InPlayRate) override;`
- L209 _public prototype_ `virtual bool SetLoop(bool bInLoop) override;`

#### struct `FAnimNode_BlendSpacePlayer_Standalone`  
`struct FAnimNode_BlendSpacePlayer_Standalone : public FAnimNode_BlendSpacePlayerBase`  
_L215-302_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpacePlayerBase`
- desc: @TODO: Comment
- L226 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = Sync)` — The group name that we synchronize with (NAME_None if it is not part of any group). Note that this is the name of the group used to sync the output of this node - it will not force syncing of animations contained by it. Animations inside this Blend Space have their own options for syncing.
- L231 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Sync)` — The role this Blend Space can assume within the group (ignored if GroupName is not set). Note that this is the role of the output of this node, not of animations contained by it.
- L235 _private member_ `bool bOverridePositionWhenJoiningSyncGroupAsLeader = false;` — `UPROPERTY(EditAnywhere, Category = Sync, meta = (EditCondition = "GroupRole != EAnimGroupRole::TransitionFollower && GroupRole != EAnimGroupRole::AlwaysFollower", EditConditionHides))` — When enabled, acting as the leader, and using marker-based sync, this asset player will not sync to the previous leader's sync position when joining a sync group and before becoming the leader but instead force everyone else to match its position.
- L240 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category = Sync)` — How this asset will synchronize with other assets. Note that this determines how the output of this node is used for synchronization, not of animations contained by it.
- L244 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L248 _private member_ `float X = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Coordinates, meta = (PinShownByDefault))` — The X coordinate to sample in the blendspace
- L252 _private member_ `float Y = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Coordinates, meta = (PinShownByDefault))` — The Y coordinate to sample in the blendspace
- L256 _private member_ `float PlayRate = 1.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "1.0", PinHiddenByDefault))` — The play rate multiplier. Can be negative, which will cause the animation to play in reverse.
- L260 _private member_ `bool bLoop = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "true", PinHiddenByDefault))` — Should the animation loop back to the start when it reaches the end?
- L264 _private member_ `bool bResetPlayTimeWhenBlendSpaceChanges = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Whether we should reset the current play time when the blend space changes
- L268 _private member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (DefaultValue = "0.f", PinHiddenByDefault))` — The start position in [0, 1] to use when initializing. When looping, play will still jump back to the beginning when reaching the end.
- L272 _private member_ `TObjectPtr<UBlendSpace> BlendSpace = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — The blendspace asset to play
- L277 _public function_ `virtual FName GetGroupName() const override` — FAnimNode_AssetPlayerBase interface
- L278 _public function_ `virtual EAnimGroupRole::Type GetGroupRole() const override`
- L279 _public function_ `virtual EAnimSyncMethod GetGroupMethod() const override`
- L280 _public function_ `virtual bool GetOverridePositionWhenJoiningSyncGroupAsLeader() const override`
- L281 _public function_ `virtual bool GetIgnoreForRelevancyTest() const override`
- L282 _public function_ `virtual bool IsLooping() const override`
- L283 _public function_ `virtual bool SetGroupName(FName InGroupName) override`
- L284 _public function_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override`
- L285 _public function_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override`
- L286 _public function_ `virtual bool SetOverridePositionWhenJoiningSyncGroupAsLeader(bool InOverridePositionWhenJoiningSyncGroupAsLeader) override`
- L287 _public function_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override`
- L291 _public function_ `virtual UBlendSpace* GetBlendSpace() const override` — FAnimNode_BlendSpacePlayerBase interface
- L292 _public function_ `virtual FVector GetPosition() const override`
- L293 _public function_ `virtual float GetStartPosition() const override`
- L294 _public function_ `virtual float GetPlayRate() const override`
- L295 _public function_ `virtual bool ShouldResetPlayTimeWhenBlendSpaceChanges() const override`
- L296 _public function_ `virtual bool SetResetPlayTimeWhenBlendSpaceChanges(bool bReset) override`
- L297 _public function_ `virtual bool SetBlendSpace(UBlendSpace* InBlendSpace) override`
- L298 _public function_ `virtual bool SetPosition(FVector InPosition) override`
- L299 _public function_ `virtual bool SetPlayRate(float InPlayRate) override`
- L300 _public function_ `virtual bool SetLoop(bool bInLoop) override`

#### Free symbols / members of external scopes

- L110 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anonb9826c0c0103`)

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_BlendSpaceSampleResult.h` (Public)


#### struct `FAnimNode_BlendSpaceSampleResult`  
`struct FAnimNode_BlendSpaceSampleResult : public FAnimNode_Root`  
_L13-16_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Root`
- desc: Root node of a blend space sample (sink node). We dont use AnimNode_Root to let us distinguish these nodes in the property list at link time.

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_CallFunction.h` (Public)


#### enum `EAnimFunctionCallSite`  
`enum class EAnimFunctionCallSite`  
_L11-52_
- reflection: `UENUM()`
- desc: When to call the function during the execution of the animation graph
- L14 _public enumerator_ `OnInitialize` — Called when the node is initialized - i.e. it becomes weighted/relevant in the graph (before child nodes are initialized)
- L17 _public enumerator_ `OnUpdate` — Called when the node is updated (before child nodes are updated)
- L20 _public enumerator_ `OnBecomeRelevant` — Called when the node is updated for the first time with a valid weight
- L23 _public enumerator_ `OnEvaluate` — Called when the node is evaluated (before child nodes are evaluated)
- L26 _public enumerator_ `OnInitializePostRecursion UMETA(DisplayName = "On Initialize (Post Recursion)")` — Called when the node is initialized - i.e. it becomes weighted/relevant in the graph (after child nodes are initialized)
- L29 _public enumerator_ `OnUpdatePostRecursion UMETA(DisplayName = "On Update (Post Recursion)")` — Called when the node is updated (after child nodes are updated)
- L32 _public enumerator_ `OnBecomeRelevantPostRecursion UMETA(DisplayName = "On Become Relevant (Post Recursion)")` — Called when the node is updated for the first time with a valid weight (after child nodes are updated)
- L35 _public enumerator_ `OnEvaluatePostRecursion UMETA(DisplayName = "On Evaluate (Post Recursion)")` — Called when the node is evaluated (after child nodes are evaluated)
- L39 _public enumerator_ `OnStartedBlendingOut` — Called when the node is updated, was at full weight and beings to blend out. Called before child nodes are updated
- L42 _public enumerator_ `OnStartedBlendingIn` — Called when the node is updated, was at zero weight and beings to blend in. Called before child nodes are updated
- L47 _public enumerator_ `OnFinishedBlendingOut UMETA(Hidden)` — Called when the node is updated, was at non-zero weight and finishes blending out. Called before child nodes are updated (note that this is necessarily not called within the graph update but from outside) @TODO: Not currently supported, needs subsystem support!
- L51 _public enumerator_ `OnFinishedBlendingIn` — Called when the node is updated, was at non-zero weight and becomes full weight. Called before child nodes are updated

#### struct `FAnimNode_CallFunction`  
`struct FAnimNode_CallFunction : public FAnimNode_Base`  
_L56-94_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Calls specified user-defined events/functions during anim graph execution
- L61 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, Category = Links)`
- L66 _public member_ `FAnimNodeFunctionRef Function;` — `UPROPERTY(meta=(FoldProperty))` — Function to call
- L70 _public member_ `FGraphTraversalCounter Counter;` — Counter used to determine relevancy
- L73 _public member_ `float CurrentWeight = 0.0f;` — Weight to determine blend-related call sites
- L77 _public member_ `EAnimFunctionCallSite CallSite = EAnimFunctionCallSite::OnUpdate;` — `UPROPERTY(EditAnywhere, Category="Function")` — When to call the function during the execution of the animation graph
- L80 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;` — FAnimNode_Base interface
- L81 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L82 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L83 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L84 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Context) override;`
- L85 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L86 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L90 _public prototype_ `void CallFunctionFromCallSite(EAnimFunctionCallSite InCallSite, const FAnimationBaseContext& InContext) const;` — Calls the function we hold if the callsite matches the one we have set
- L93 _public prototype_ `const FAnimNodeFunctionRef& GetFunction() const;` — Get the function held on this node

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_CopyPoseFromMesh.h` (Public)


#### struct `FAnimNode_CopyPoseFromMesh`  
`struct FAnimNode_CopyPoseFromMesh : public FAnimNode_Base`  
_L18-85_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L24 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SourceMeshComponent;` — `UPROPERTY(BlueprintReadWrite, transient, Category=Copy, meta=(PinShownByDefault))` — This is used by default if it's valid
- L28 _public member_ `uint8 bUseAttachedParent : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (NeverAsPin))` — If SourceMeshComponent is not valid, and if this is true, it will look for attahced parent as a source
- L32 _public member_ `uint8 bCopyCurves : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (NeverAsPin))` — Copy curves also from SouceMeshComponent. This will copy the curves if this instance also contains curve attributes
- L36 _public member_ `bool bCopyCustomAttributes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Copy Custom Attributes(Animation Attributes)",Category = Copy, meta = (NeverAsPin))` — Copy custom attributes (animation attributes) from SourceMeshComponent
- L40 _public member_ `uint8 bUseMeshPose : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (NeverAsPin))` — Use root space transform to copy to the target pose. By default, it copies their relative transform (bone space)
- L44 _public member_ `FName RootBoneToCopy;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Copy, meta = (NeverAsPin))` — If you want to specify copy root, use this - this will ensure copy only below of this joint (inclusively)
- L46 _public prototype_ `FAnimNode_CopyPoseFromMesh();`
- L49 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L50 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L51 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L52 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L53 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L54 _public function_ `virtual bool HasPreUpdate() const override`
- L55 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L60 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> CurrentlyUsedSourceMeshComponent;` — this is source mesh references, so that we could compare and see if it has changed
- L61 _private member_ `TWeakObjectPtr<USkeletalMesh> CurrentlyUsedSourceMesh;`
- L62 _private member_ `TWeakObjectPtr<USkeletalMesh> CurrentlyUsedMesh;`
- L65 _private member_ `TWeakObjectPtr<USkeletalMesh> CurrentlyUsedTargetMesh;` — target mesh
- L67 _private member_ `TMap<int32, int32> BoneMapToSource;` — cache of target space bases to source space bases
- L68 _private member_ `TMap<int32, int32> SourceBoneToTarget;`
- L71 _private member_ `TArray<FTransform> SourceMeshTransformArray;` — Cached transforms, copied on the game thread
- L74 _private member_ `TBitArray<> SourceMeshValidMeshPoseTransforms;` — Cached transforms, copied on the game thread
- L77 _private member_ `FBlendedHeapCurve SourceCurves;` — Cached curves, copied on the game thread
- L80 _private member_ `UE::Anim::FMeshAttributeContainer SourceCustomAttributes;` — Cached attributes, copied on the game thread
- L83 _private prototype_ `void ReinitializeMeshComponent(USkeletalMeshComponent* NewSkeletalMeshComponent, USkeletalMeshComponent* TargetMeshComponent);` — reinitialize mesh component
- L84 _private prototype_ `void RefreshMeshComponent(USkeletalMeshComponent* TargetMeshComponent);`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_CurveSource.h` (Public)


#### struct `FAnimNode_CurveSource`  
`struct FAnimNode_CurveSource : public FAnimNode_Base`  
_L17-52_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Supply curves from some external source (e.g. audio)
- L22 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)`
- L31 _public member_ `FName SourceBinding;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurveSource, meta = (PinHiddenByDefault))` — The binding of the curve source we want to bind to. We will bind to an object that implements ICurveSourceInterface. First we check the actor that owns this (if any), then we check each of its components to see if we should bind to the source that matches this name.
- L35 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CurveSource, meta = (PinShownByDefault))` — How much we wan to blend the curve in by
- L39 _public member_ `TScriptInterface<ICurveSourceInterface> CurveSource;` — `UPROPERTY(Transient)` — Our bound source
- L41 _public prototype_ `FAnimNode_CurveSource();`
- L44 _public function_ `virtual bool HasPreUpdate() const override` — FAnimNode_Base interface
- L45 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L46 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L47 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L48 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L49 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L50 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_LayeredBoneBlend.h` (Public)


#### enum `ELayeredBoneBlendMode`  
`enum class ELayeredBoneBlendMode : uint8`  
_L13-17_
- reflection: `UENUM()`
- L15 _public enumerator_ `BranchFilter`
- L16 _public enumerator_ `BlendMask`

#### struct `FAnimNode_LayeredBoneBlend`  
`struct FAnimNode_LayeredBoneBlend : public FAnimNode_Base`  
_L21-199_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Layered blend (per bone); has dynamic number of blendposes that can blend per different bone sets
- L28 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — The source pose
- L32 _public member_ `TArray<FPoseLink> BlendPoses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Links, meta=(BlueprintCompilerGeneratedDefaults))` — Each layer's blended pose
- L36 _public member_ `ELayeredBoneBlendMode BlendMode;` — `UPROPERTY(EditAnywhere, Category = Config)` — Whether to use branch filters or a blend mask to specify an input pose per-bone influence
- L43 _public member_ `TArray<TObjectPtr<UBlendProfile>> BlendMasks;` — `UPROPERTY(EditAnywhere, editfixedsize, Category=Config, meta=(UseAsBlendMask=true))` — The blend masks to use for our layer inputs. Allows the use of per-bone alphas. Blend masks are used when BlendMode is BlendMask.
- L51 _public member_ `TArray<FInputBlendPose> LayerSetup;` — `UPROPERTY(EditAnywhere, editfixedsize, Category=Config)` — Configuration for the parts of the skeleton to blend for each layer. Allows certain parts of the tree to be blended out or omitted from the pose. LayerSetup is used when BlendMode is BranchFilter.
- L55 _public member_ `TArray<float> BlendWeights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category=Runtime, meta=(BlueprintCompilerGeneratedDefaults, PinShownByDefault))` — The weights of each layer
- L60 _protected member_ `TArray<FPerBoneBlendWeight> DesiredBoneBlendWeights;` — transient data to handle weight and target weight this array changes based on required bones
- L61 _protected member_ `TArray<FPerBoneBlendWeight> CurrentBoneBlendWeights;`
- L66 _protected member_ `TArray<FPerBoneBlendWeight> PerBoneBlendWeights;` — `UPROPERTY()` — Per-bone weights for the skeleton. Serialized as these are only relative to the skeleton, but can potentially be regenerated at runtime if the GUIDs dont match
- L69 _protected member_ `TBaseBlendedCurve<FDefaultAllocator, UE::Anim::FCurveElementIndexed> CurvePoseSourceIndices;` — Per-curve source pose index
- L73 _protected member_ `FGuid SkeletonGuid;` — `UPROPERTY()` — Guids for skeleton used to determine whether the PerBoneBlendWeights need rebuilding
- L77 _protected member_ `FGuid VirtualBoneGuid;` — `UPROPERTY()` — Guid for virtual bones used to determine whether the PerBoneBlendWeights need rebuilding
- L80 _protected member_ `uint16 RequiredBonesSerialNumber;` — Serial number of the required bones container
- L90 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L94 _public member_ `bool bMeshSpaceRotationBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)` — Whether to blend bone rotations in mesh space or in local space
- L98 _public member_ `bool bRootSpaceRotationBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config, Meta = (Editcondition = bMeshSpaceRotationBlend))` — Whether to blend bone rotations in root space or in mesh space
- L102 _public member_ `bool bMeshSpaceScaleBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)` — Whether to blend bone scales in mesh space or in local space
- L110 _public member_ `bool bBlendRootMotionBasedOnRootBone;` — `UPROPERTY(EditAnywhere, Category = Config)` — Whether to incorporate the per-bone blend weight of the root bone when lending root motion
- L114 _public member_ `bool bUpdateBasePoseFirst = false;` — `UPROPERTY(Experimental, EditAnywhere, BlueprintReadWrite, Category = Config, meta = (PinHiddenByDefault))` — Whether to update the base pose first or after all the blend poses
- L116 _public member_ `bool bHasRelevantPoses;`
- L118 _public function_ `FAnimNode_LayeredBoneBlend() : BlendMode(ELayeredBoneBlendMode::BranchFilter) , RequiredBonesSerialNumber(0) , LODThreshold(INDEX_NONE) , bMeshSpaceRotationBlend(false) , bRootSpaceRotationBlend(false) , bMeshSpaceScaleBlend(false) , CurveBlendOption(ECurveBlendOption::Override) , bBlendRootMotionBasedOnRootBone(true) , bHasRelevantPoses(false)`
- L132 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L133 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L134 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L135 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L136 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L137 _public function_ `virtual int32 GetLODThreshold() const override`
- L140 _public function_ `void AddPose()`
- L147 _public function_ `void RemovePose(int32 PoseIndex)`
- L166 _public prototype_ `void SetBlendMask(int32 InPoseIndex, UBlendProfile* InBlendMask);` — Set the blend mask for the specified input pose
- L169 _public function_ `void InvalidatePerBoneBlendWeights()` — Invalidate the cached per-bone blend weights from the skeleton
- L172 _public function_ `void InvalidateCachedBoneData()` — Invalidates the cached bone data so it is recalculated the next time this node is updated
- L177 _private function_ `void AddFirstPose()` — just for the graph constructor to call.
- L187 _private prototype_ `void SyncBlendMasksAndLayers();` — Synchronize the number of BlendMasks or Layers with the number of BlendPoses.
- L190 _private prototype_ `void RebuildPerBoneBlendWeights(const USkeleton* InSkeleton);` — Rebuild cache per bone blend weights from the skeleton
- L193 _private prototype_ `bool ArePerBoneBlendWeightsValid(const USkeleton* InSkeleton) const;` — Check whether per-bone blend weights are valid according to the skeleton (GUID check)
- L196 _private prototype_ `void UpdateCachedBoneData(const FBoneContainer& RequiredBones, const USkeleton* Skeleton);` — Update cached data if required

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_MakeDynamicAdditive.h` (Public)


#### struct `FAnimNode_MakeDynamicAdditive`  
`struct FAnimNode_MakeDynamicAdditive : public FAnimNode_Base`  
_L11-38_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L17 _public member_ `FPoseLink Base;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — Reference pose for additive delta calculation
- L21 _public member_ `FPoseLink Additive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — Pose to make additive
- L25 _public member_ `bool bMeshSpaceAdditive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)` — Do additive delta calculation in mesh space
- L28 _public prototype_ `FAnimNode_MakeDynamicAdditive();`
- L31 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L32 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L33 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L34 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L35 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_Mirror.h` (Public)


#### enum `EMirrorBlendType`  
`enum class EMirrorBlendType : uint8`  
_L13-19_
- reflection: `UENUM()`
- L16 _public enumerator_ `StandardBlend` — Use a standard crossfade blend. If Reset Child on Mirror State Change is enabled, this will result in a pop.
- L18 _public enumerator_ `Inertialization` — Use an inertial blend. This requires having a matching inertialization or dead blend node upstream in the graph.

#### struct `FAnimNode_MirrorBase`  
`struct FAnimNode_MirrorBase : public FAnimNode_Base`  
_L22-106_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L26 _public prototype_ `FAnimNode_MirrorBase();`
- L27 _public prototype_ `FAnimNode_MirrorBase(const FAnimNode_MirrorBase&);`
- L28 _public prototype_ `~FAnimNode_MirrorBase();`
- L30 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L31 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L32 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L33 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L34 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L37 _public prototype_ `virtual UMirrorDataTable* GetMirrorDataTable() const;` — Get the MirrorDataTable
- L39 _public prototype_ `virtual bool SetMirrorDataTable(UMirrorDataTable* MirrorTable);`
- L42 _public prototype_ `virtual EMirrorBlendType GetBlendType() const;` — Get mirror blend type. Default to inertialization for backwards compatibility.
- L45 _public prototype_ `virtual bool GetMirror() const;` — Get Mirror State
- L47 _public prototype_ `virtual float GetBlendTimeOnMirrorStateChange() const;` — How long to blend using inertialization when switching  mirrored state
- L50 _public prototype_ `virtual bool GetBoneMirroring() const;` — Should bones mirror
- L53 _public prototype_ `virtual bool GetCurveMirroring() const;` — Should the curves mirror
- L56 _public prototype_ `virtual bool GetAttributeMirroring() const;` — Should attributes mirror (based on the bone mirroring data in the mirror data table)
- L59 _public prototype_ `virtual bool GetResetChildOnMirrorStateChange() const;` — Whether to reset (reinitialize) the child (source) pose when the mirror state changes
- L62 _public prototype_ `virtual bool SetMirror(bool bInMirror);` — Set Mirror State
- L66 _public prototype_ `virtual bool SetBlendTimeOnMirrorStateChange(float InBlendTime);` — Set how long to blend using inertialization when switching  mirrored state @return true if the value was set (it is dynamic), or false if it could not (it is not dynamic or pin exposed)
- L70 _public prototype_ `virtual bool SetBoneMirroring(bool bInBoneMirroring);` — Set if bones mirror @return true if the value was set (it is dynamic), or false if it could not (it is not dynamic or pin exposed)
- L74 _public prototype_ `virtual bool SetCurveMirroring(bool bInCurveMirroring);` — Set if curves mirror @return true if the value was set (it is dynamic), or false if it could not (it is not dynamic or pin exposed)
- L78 _public prototype_ `virtual bool SetAttributeMirroring(bool bInAttributeMirroring);` — Set if attributes mirror @return true if the value was set (it is dynamic), or false if it could not (it is not dynamic or pin exposed)
- L82 _public prototype_ `virtual bool SetResetChildOnMirrorStateChange(bool bInResetChildOnMirrorStateChange);` — Set whether to reset (reinitialize) the child (source) pose when the mirror state changes @return true if the value was set (it is dynamic), or false if it could not (it is not dynamic or pin exposed)
- L85 _public prototype_ `virtual void SetSourceLinkNode(FAnimNode_Base* NewLinkNode);` — This only used by custom handlers, and it is advanced feature.
- L88 _public prototype_ `virtual FAnimNode_Base* GetSourceLinkNode();` — This only used by custom handlers, and it is advanced feature.
- L91 _protected member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, Category = Links)`
- L94 _private member_ `FAlphaBlend Blend;`
- L96 _private member_ `bool bMirrorState;`
- L97 _private member_ `bool bMirrorStateIsValid;`
- L99 _private prototype_ `void MirrorPoseInPlace(FPoseContext& InPose);`
- L100 _private prototype_ `void FillCompactPoseAndComponentRefRotations(const FBoneContainer& BoneContainer);`
- L102 _private member_ `TCustomBoneIndexArray<FCompactPoseBoneIndex, FCompactPoseBoneIndex> CompactPoseMirrorBones;` — Compact pose format of Mirror Bone Map
- L105 _private member_ `TCustomBoneIndexArray<FQuat, FCompactPoseBoneIndex> ComponentSpaceRefRotations;` — Pre-calculated component space of reference pose, which allows mirror to work with any joint orient

#### struct `FAnimNode_Mirror`  
`struct FAnimNode_Mirror : public FAnimNode_MirrorBase`  
_L110-167_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_MirrorBase`
- L117 _public prototype_ `FAnimNode_Mirror();`
- L118 _public prototype_ `~FAnimNode_Mirror();`
- L120 _public prototype_ `virtual UMirrorDataTable* GetMirrorDataTable() const override;`
- L121 _public prototype_ `virtual bool SetMirrorDataTable(UMirrorDataTable* MirrorTable) override;`
- L123 _public prototype_ `virtual EMirrorBlendType GetBlendType() const;`
- L124 _public prototype_ `virtual bool GetMirror() const override;`
- L125 _public prototype_ `virtual float GetBlendTimeOnMirrorStateChange() const override;`
- L126 _public prototype_ `virtual bool GetBoneMirroring() const override;`
- L127 _public prototype_ `virtual bool GetCurveMirroring() const override;`
- L128 _public prototype_ `virtual bool GetAttributeMirroring() const override;`
- L129 _public prototype_ `virtual bool GetResetChildOnMirrorStateChange() const override;`
- L131 _public prototype_ `virtual bool SetMirror(bool bInMirror) override;`
- L132 _public prototype_ `virtual bool SetBlendTimeOnMirrorStateChange(float InBlendTime) override;`
- L133 _public prototype_ `virtual bool SetBoneMirroring(bool bInBoneMirroring) override;`
- L134 _public prototype_ `virtual bool SetCurveMirroring(bool bInCurveMirroring) override;`
- L135 _public prototype_ `virtual bool SetAttributeMirroring(bool bInAttributeMirroring) override;`
- L136 _public prototype_ `virtual bool SetResetChildOnMirrorStateChange(bool bInResetChildOnMirrorStateChange) override;`
- L142 _protected member_ `bool bMirror = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault, FoldProperty))`
- L145 _protected member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (FoldProperty))`
- L149 _protected member_ `float BlendTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (PinHiddenByDefault, FoldProperty))` — Inertialization blend time to use when transitioning between mirrored and unmirrored states
- L152 _protected member_ `EMirrorBlendType BlendType = EMirrorBlendType::Inertialization;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (PinHiddenByDefault, FoldProperty))`
- L156 _protected member_ `bool bResetChild = false;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (FoldProperty))` — Whether to reset (reinitialize) the child (source) pose when the mirror state changes
- L159 _protected member_ `bool bBoneMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta=(DisplayName="Bone", FoldProperty))`
- L162 _protected member_ `bool bCurveMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta=(DisplayName = "Curve", FoldProperty))`
- L165 _protected member_ `bool bAttributeMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta=(DisplayName = "Attributes", FoldProperty))`

#### struct `FAnimNode_Mirror_Standalone`  
`struct FAnimNode_Mirror_Standalone : public FAnimNode_MirrorBase`  
_L171-227_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_MirrorBase`
- L178 _public prototype_ `FAnimNode_Mirror_Standalone();`
- L179 _public prototype_ `FAnimNode_Mirror_Standalone(const FAnimNode_Mirror_Standalone&);`
- L180 _public prototype_ `~FAnimNode_Mirror_Standalone();`
- L182 _public prototype_ `virtual UMirrorDataTable* GetMirrorDataTable() const override;`
- L183 _public prototype_ `virtual bool SetMirrorDataTable(UMirrorDataTable* MirrorTable) override;`
- L185 _public prototype_ `virtual EMirrorBlendType GetBlendType() const;`
- L186 _public prototype_ `virtual bool GetMirror() const override;`
- L187 _public prototype_ `virtual float GetBlendTimeOnMirrorStateChange() const override;`
- L188 _public prototype_ `virtual bool GetBoneMirroring() const override;`
- L189 _public prototype_ `virtual bool GetCurveMirroring() const override;`
- L190 _public prototype_ `virtual bool GetAttributeMirroring() const override;`
- L191 _public prototype_ `virtual bool GetResetChildOnMirrorStateChange() const override;`
- L193 _public prototype_ `virtual bool SetMirror(bool bInMirror) override;`
- L194 _public prototype_ `virtual bool SetBlendTimeOnMirrorStateChange(float InBlendTime) override;`
- L195 _public prototype_ `virtual bool SetBoneMirroring(bool bInBoneMirroring) override;`
- L196 _public prototype_ `virtual bool SetCurveMirroring(bool bInCurveMirroring) override;`
- L197 _public prototype_ `virtual bool SetAttributeMirroring(bool bInAttributeMirroring) override;`
- L198 _public prototype_ `virtual bool SetResetChildOnMirrorStateChange(bool bInResetChildOnMirrorStateChange) override;`
- L203 _protected member_ `bool bMirror = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))`
- L206 _protected member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L210 _protected member_ `float BlendTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (PinHiddenByDefault, FoldProperty))` — Inertialization blend time to use when transitioning between mirrored and unmirrored states
- L213 _protected member_ `EMirrorBlendType BlendType = EMirrorBlendType::Inertialization;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (PinHiddenByDefault, FoldProperty))`
- L217 _protected member_ `bool bResetChild = false;` — `UPROPERTY(EditAnywhere, Category = MirrorTransition, meta = (FoldProperty))` — Whether to reset (reinitialize) the child (source) pose when the mirror state changes
- L220 _protected member_ `bool bBoneMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta = (DisplayName = "Bone", FoldProperty))`
- L223 _protected member_ `bool bCurveMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta = (DisplayName = "Curve", FoldProperty))`
- L226 _protected member_ `bool bAttributeMirroring = true;` — `UPROPERTY(EditAnywhere, Category = MirroredChannels, meta = (DisplayName = "Attributes", FoldProperty))`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_ModifyCurve.h` (Public)


#### enum `EModifyCurveApplyMode`  
`enum class EModifyCurveApplyMode : uint8`  
_L11-27_
- reflection: `UENUM()`
- L14 _public enumerator_ `Add` — Add new value to input curve value
- L17 _public enumerator_ `Scale` — Scale input value by new value
- L20 _public enumerator_ `Blend` — Blend input with new curve value, using Alpha setting on the node
- L23 _public enumerator_ `WeightedMovingAverage` — Blend the new curve value with the last curve value using Alpha to determine the weighting (.5 is a moving average, higher values react to new values faster, lower slower)
- L26 _public enumerator_ `RemapCurve` — Remaps the new curve value between the CurveValues entry and 1.0 (.5 in CurveValues makes 0.51 map to 0.02)

#### struct `FAnimNode_ModifyCurve`  
`struct FAnimNode_ModifyCurve : public FAnimNode_Base`  
_L31-76_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Easy way to modify curve values on a pose
- L36 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Links)`
- L39 _public member_ `TMap<FName, float> CurveMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category = ModifyCurve, meta = (PinHiddenByDefault))`
- L42 _public member_ `TArray<float> CurveValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, editfixedsize, Category = ModifyCurve, meta = (BlueprintCompilerGeneratedDefaults, PinShownByDefault))`
- L45 _public member_ `TArray<FName> CurveNames;` — `UPROPERTY(meta = (BlueprintCompilerGeneratedDefaults))`
- L47 _public member_ `FBlendedHeapCurve LastCurve;`
- L50 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModifyCurve, meta = (PinShownByDefault))`
- L53 _public member_ `EModifyCurveApplyMode ApplyMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ModifyCurve)`
- L55 _public prototype_ `FAnimNode_ModifyCurve();`
- L58 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L59 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L60 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L62 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L63 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L68 _public prototype_ `void AddCurve(const FName& InName, float InValue);` — Add new curve being modified
- L70 _public prototype_ `void RemoveCurve(int32 PoseIndex);` — Remove a curve from being modified
- L74 _private prototype_ `float ProcessCurveOperation(float CurrentValue, float NewValue) const;`
- L75 _private prototype_ `float ProcessCurveWMAOperation(float CurrentValue, float LastValue) const;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_MultiWayBlend.h` (Public)


#### struct `FAnimNode_MultiWayBlend`  
`struct FAnimNode_MultiWayBlend : public FAnimNode_Base`  
_L11-91_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: This represents a baked transition
- L18 _public member_ `TArray<FPoseLink> Poses;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (BlueprintCompilerGeneratedDefaults))`
- L21 _public member_ `TArray<float> DesiredAlphas;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category=Settings, meta=(BlueprintCompilerGeneratedDefaults, PinShownByDefault))`
- L24 _private member_ `TArray<float> CachedAlphas;`
- L28 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)`
- L31 _public member_ `bool bAdditiveNode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L34 _public member_ `bool bNormalizeAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L37 _public function_ `FAnimNode_MultiWayBlend() : bAdditiveNode(false) , bNormalizeAlpha(true)`
- L44 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L45 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L46 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L47 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L48 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L51 _public function_ `int32 AddPose()`
- L60 _public function_ `void RemovePose(int32 PoseIndex)`
- L67 _public function_ `void ResetPoses()`
- L74 _public function_ `float GetTotalAlpha() const`
- L88 _private prototype_ `void UpdateCachedAlphas();` — process new weights and then return out

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_PoseBlendNode.h` (Public)


#### struct `FAnimNode_PoseBlendNode`  
`struct FAnimNode_PoseBlendNode : public FAnimNode_PoseHandler`  
_L16-51_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_PoseHandler`
- desc: Evaluates a point in an anim sequence, using a specific time input rather than advancing time internally. Typically the playback position of the animation for this node will represent something other than time, like jump height. This node will not trigger any notifies present in the associated sequence.
- L21 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = Links)`
- L25 _public member_ `EAlphaBlendOption BlendOption;` — `UPROPERTY(EditAnywhere, Category = "Blend")` — Type of blending used (Linear, Cubic, etc.)
- L29 _public member_ `TObjectPtr<UCurveFloat> CustomCurve;` — `UPROPERTY(EditAnywhere, Category = "Blend")` — If you're using Custom BlendOption, you can specify curve
- L32 _public member_ `bool bIgnorePoseAssetSourceAnimationCurves = false;` — `UPROPERTY(EditAnywhere, Category = "Blend", BlueprintReadWrite, meta = (PinHiddenByDefault))`
- L36 _private member_ `UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FNamedIndexElement> BulkCurves;` — Cached curves to extract
- L39 _public prototype_ `FAnimNode_PoseBlendNode();`
- L42 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L43 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L44 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L45 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L46 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L50 _public prototype_ `virtual void RebuildPoseList(const FBoneContainer& InBoneContainer, const UPoseAsset* InPoseAsset) override;` — FAnimNode_PoseHandler interface

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_PoseByName.h` (Public)


#### struct `FAnimNode_PoseByName`  
`struct FAnimNode_PoseByName : public FAnimNode_PoseHandler`  
_L14-43_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_PoseHandler`
- desc: Evaluates a point in an anim sequence, using a specific time input rather than advancing time internally. Typically the playback position of the animation for this node will represent something other than time, like jump height. This node will not trigger any notifies present in the associated sequence.
- L19 _public member_ `FName PoseName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L22 _public member_ `float PoseWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L26 _private member_ `FName CurrentPoseName;` — Cached current pose name used for invalidation
- L29 _public function_ `FAnimNode_PoseByName() : PoseWeight(1.f) , CurrentPoseName(NAME_None)`
- L36 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L37 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L38 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L39 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L42 _private prototype_ `virtual void RebuildPoseList(const FBoneContainer& InBoneContainer, const UPoseAsset* InPoseAsset) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_PoseDriver.h` (Public)


#### enum `EPoseDriverType`  
`enum class EPoseDriverType : uint8`  
_L15-20_
- reflection: `UENUM()`
- desc: Deprecated
- L17 _public enumerator_ `SwingAndTwist`
- L18 _public enumerator_ `SwingOnly`
- L19 _public enumerator_ `Translation`

#### enum `EPoseDriverSource`  
`enum class EPoseDriverSource : uint8`  
_L24-31_
- reflection: `UENUM(BlueprintType)`
- desc: Transform aspect used to drive interpolation
- L27 _public enumerator_ `Rotation` — Drive using rotation
- L30 _public enumerator_ `Translation` — Driver using translation

#### enum `EPoseDriverOutput`  
`enum class EPoseDriverOutput : uint8`  
_L35-42_
- reflection: `UENUM(BlueprintType)`
- desc: Options for what PoseDriver should be driving
- L38 _public enumerator_ `DrivePoses` — Use target's DrivenName to drive poses from the assigned PoseAsset
- L41 _public enumerator_ `DriveCurves` — Use the target's DrivenName to drive curves

#### struct `FPoseDriverTransform`  
`struct FPoseDriverTransform`  
_L46-62_
- reflection: `USTRUCT()`
- desc: Translation and rotation for a particular bone at a particular target
- L52 _public member_ `FVector TargetTranslation;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Translation of this target
- L56 _public member_ `FRotator TargetRotation;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Rotation of this target
- L58 _public function_ `FPoseDriverTransform() : TargetTranslation(FVector::ZeroVector) , TargetRotation(FRotator::ZeroRotator)`

#### struct `FPoseDriverTarget`  
`struct FPoseDriverTarget`  
_L66-129_
- reflection: `USTRUCT()`
- desc: Information about each target in the PoseDriver
- L72 _public member_ `TArray<FPoseDriverTransform> BoneTransforms;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Translation of this target
- L76 _public member_ `FRotator TargetRotation;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Rotation of this target
- L80 _public member_ `float TargetScale;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Scale applied to this target's function - a larger value will activate this target sooner
- L84 _public member_ `ERBFDistanceMethod DistanceMethod;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Override for the distance method to use for each target
- L88 _public member_ `ERBFFunctionType FunctionType;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Override for the function method to use for each target
- L92 _public member_ `bool bApplyCustomCurve;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — If we should apply a custom curve mapping to how this target activates
- L96 _public member_ `FRichCurve CustomCurve;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Custom curve mapping to apply if bApplyCustomCurve is true
- L104 _public member_ `FName DrivenName;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Name of item to drive - depends on DriveOutput setting. If DriveOutput is DrivePoses, this should be the name of a pose in the assigned PoseAsset If DriveOutput is DriveCurves, this is the name of the curve (morph target, material param etc) to drive
- L107 _public member_ `int32 PoseCurveIndex;` — Pose buffer index
- L111 _public member_ `bool bIsHidden;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — If we should hide this pose from the UI
- L115 _public prototype_ `FPoseDriverTarget(const FPoseDriverTarget&) = default;` — removing deprecation for default copy operator/constructor to avoid deprecation warnings
- L116 _public prototype_ `FPoseDriverTarget& operator=(const FPoseDriverTarget&) = default;`
- L119 _public function_ `FPoseDriverTarget() : TargetRotation(ForceInitToZero) , TargetScale(1.f) , DistanceMethod(ERBFDistanceMethod::DefaultMethod) , FunctionType(ERBFFunctionType::DefaultFunction) , bApplyCustomCurve(false) , DrivenName(NAME_None) , PoseCurveIndex(INDEX_NONE) , bIsHidden(false)`

#### struct `FAnimNode_PoseDriver`  
`struct FAnimNode_PoseDriver : public FAnimNode_PoseHandler`  
_L133-256_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_PoseHandler`
- desc: RBF based orientation driver
- L139 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = PoseDriver)` — Bones to use for driving parameters based on their transform
- L143 _public member_ `TArray<FBoneReference> SourceBones;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Bone to use for driving parameters based on its orientation
- L150 _public member_ `FBoneReference EvalSpaceBone;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Optional other bone space to use when reading SourceBone transform. If not specified, the local space of SourceBone will be used. (ie relative to parent bone)
- L160 _public member_ `bool bEvalFromRefPose = false;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Evaluate SourceBone transform relative from its Reference Pose. This is recommended when using Swing and Twist Angle as Distance Method, since the twist will be computed from RefPose. If not specified, the local space of SourceBone will be used. (ie relative to parent bone) This mode won't work in conjunction with EvalSpaceBone;
- L164 _public member_ `TArray<FBoneReference> OnlyDriveBones;` — `UPROPERTY(EditAnywhere, Category = PoseDriver, meta = (EditCondition = "DriveOutput == EPoseDriverOutput::DrivePoses"))` — List of bones that will modified by this node. If no list is provided, all bones bones with a track in the PoseAsset will be modified
- L168 _public member_ `TArray<FPoseDriverTarget> PoseTargets;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Targets used to compare with current pose and drive morphs/poses
- L172 _public member_ `FRBFParams RBFParams;` — `UPROPERTY(EditAnywhere, Category = PoseDriver, meta = (ShowOnlyInnerProperties))` — Parameters used by RBF solver
- L176 _public member_ `EPoseDriverSource DriveSource;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Which part of the transform is read
- L180 _public member_ `EPoseDriverOutput DriveOutput;` — `UPROPERTY(EditAnywhere, Category = PoseDriver)` — Whether we should drive poses or curves
- L183 _public member_ `TArray<FRBFOutputWeight> OutputWeights;` — Last set of output weights from RBF solve
- L186 _public member_ `TArray<FTransform> SourceBoneTMs;` — Input source bone TM, used for debug drawing
- L189 _public member_ `bool bHasOnlyDriveBones = false;` — Checks if there are valid bones in OnlyDriveBones, since some entries can be None
- L192 _public member_ `TArray<FCompactPoseBoneIndex> BonesToFilter;` — This array lists bones that we should filter out (ie have a track in the PoseAsset, but are not listed in OnlyDriveBones)
- L197 _public member_ `FBoneReference SourceBone_DEPRECATED;` — `UPROPERTY()` — Deprecated
- L199 _public member_ `TEnumAsByte<EBoneAxis> TwistAxis_DEPRECATED;` — `UPROPERTY()`
- L201 _public member_ `EPoseDriverType Type_DEPRECATED;` — `UPROPERTY()`
- L203 _public member_ `float RadialScaling_DEPRECATED;` — `UPROPERTY()`
- L208 _public member_ `uint8 bCachedDrivenIDsAreDirty : 1;` — If true, will recalculate DrivenUID values in PoseTargets array on next eval
- L213 _public member_ `int32 SoloTargetIndex;` — The target to solo on, or INDEX_NONE if to use the normal weight computation. Not a UPROPERTY to ensure it stays transient and doesn't affect PIE.
- L217 _public member_ `bool bSoloDrivenOnly;` — `UPROPERTY()` — Only solo the driven poses, and don't move the source joint(s) to match
- L227 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, Category = Performance, meta = (PinHiddenByDefault, DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L230 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L231 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L232 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L233 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L234 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L235 _public function_ `virtual int32 GetLODThreshold() const override`
- L238 _public prototype_ `FAnimNode_PoseDriver();`
- L241 _public prototype_ `float GetRadiusForTarget(const FRBFTarget& Target) const;` — Returns the radius for a given target
- L244 _public prototype_ `bool IsBoneDriven(FName BoneName) const;` — Util for seeing if BoneName is in the list of driven bones (and bFilterDrivenBones is true)
- L247 _public prototype_ `void GetRBFTargets(TArray<FRBFTarget>& OutTargets, const FBoneContainer* BoneContainer) const;` — Return array of FRBFTarget structs, derived from PoseTargets array and DriveSource setting
- L250 _public prototype_ `virtual void RebuildPoseList(const FBoneContainer& InBoneContainer, const UPoseAsset* InPoseAsset) override;` — Rebuild Pose List
- L253 _private member_ `TSharedPtr<const FRBFSolverData> SolverData;`
- L254 _private member_ `FRBFEntry RBFInput;`
- L255 _private member_ `TArray<FRBFTarget> RBFTargets;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_PoseHandler.h` (Public)


#### struct `FAnimNode_PoseHandler`  
`struct FAnimNode_PoseHandler : public FAnimNode_AssetPlayerBase`  
_L16-71_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_AssetPlayerBase`
- desc: Evaluates a point in an anim sequence, using a specific time input rather than advancing time internally. Typically the playback position of the animation for this node will represent something other than time, like jump height. This node will not trigger any notifies present in the associated sequence.
- L22 _public member_ `TObjectPtr<UPoseAsset> PoseAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — The animation sequence asset to evaluate
- L25 _public function_ `FAnimNode_PoseHandler() :PoseAsset(nullptr)`
- L31 _public function_ `virtual float GetCurrentAssetTime() const` — FAnimNode_AssetPlayerBase interface
- L32 _public function_ `virtual float GetCurrentAssetLength() const`
- L36 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L37 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L38 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L39 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L43 _public function_ `virtual float GetAccumulatedTime() const` — FAnimNode_AssetPlayerBase Interface
- L44 _public function_ `virtual void SetAccumulatedTime(float NewTime)`
- L45 _public function_ `virtual UAnimationAsset* GetAnimAsset() const`
- L50 _public prototype_ `void SetPoseAsset(UPoseAsset* InPoseAsset);` — Set the pose asset to use for this node
- L55 _protected function_ `virtual void OnPoseAssetChange()` — Called after CurrentPoseAsset is changed.
- L57 _protected member_ `TWeakObjectPtr<UPoseAsset> CurrentPoseAsset;`
- L58 _protected member_ `FAnimExtractContext PoseExtractContext;`
- L61 _protected member_ `TArray<float> BoneBlendWeights;` — weight to blend pose per joint - has to be cached whenever cache bones for LOD note this is for mesh bone
- L64 _protected prototype_ `virtual void RebuildPoseList(const FBoneContainer& InBoneContainer, const UPoseAsset* InPoseAsset);` — Rebuild pose list
- L67 _protected prototype_ `void CacheBoneBlendWeights(FAnimInstanceProxy* InstanceProxy);` — Cache bone blend weights - called when pose asset changes
- L70 _private prototype_ `void UpdatePoseAssetProperty(struct FAnimInstanceProxy* InstanceProxy);`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_PoseSnapshot.h` (Public)


#### enum `ESnapshotSourceMode`  
`enum class ESnapshotSourceMode : uint8`  
_L15-28_
- reflection: `UENUM()`
- desc: How to access the snapshot
- L21 _public enumerator_ `NamedSnapshot` — Refer to an internal snapshot by name (previously stored with SavePoseSnapshot). This can be more efficient than access via pin.
- L27 _public enumerator_ `SnapshotPin` — Use a snapshot variable (previously populated using SnapshotPose). This is more flexible and allows poses to be modified and managed externally to the animation blueprint.

#### struct `FAnimNode_PoseSnapshot`  
`struct FAnimNode_PoseSnapshot : public FAnimNode_Base`  
_L32-79_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Provide a snapshot pose, either from the internal named pose cache or via a supplied snapshot
- L38 _public prototype_ `FAnimNode_PoseSnapshot();`
- L41 _public function_ `virtual bool HasPreUpdate() const override` — FAnimNode_Base interface
- L42 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L43 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L44 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L45 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L49 _public member_ `FName SnapshotName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snapshot", meta = (PinShownByDefault))` — The name of the snapshot previously stored with SavePoseSnapshot
- L53 _public member_ `FPoseSnapshot Snapshot;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snapshot", meta = (PinHiddenByDefault))` — Snapshot to use. This should be populated at first by calling SnapshotPose
- L57 _public member_ `ESnapshotSourceMode Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Snapshot", meta = (PinHiddenByDefault))` — How to access the snapshot
- L61 _private member_ `TArray<int32> SourceBoneMapping;` — Cache of target space bases to source space bases
- L64 _private member_ `TArray<FName> TargetBoneNames;` — Cached array of bone names for target's ref skeleton
- L67 _private member_ `FName MappedSourceMeshName;` — Cached skeletal meshes we use to invalidate the bone mapping
- L68 _private member_ `FName MappedTargetMeshName;`
- L71 _private member_ `FName TargetBoneNameMesh;` — Cached skeletal mesh we used for updating the target bone name array
- L75 _private prototype_ `void ApplyPose(const FPoseSnapshot& PoseSnapshot, FCompactPose& OutPose);` — Evaluation helper function - apply a snapshot pose to a pose
- L78 _private prototype_ `void CacheBoneMapping(FName SourceMeshName, FName TargetMeshName, const TArray<FName>& InSourceBoneNames, const TArray<FName>& InTargetBoneNames);` — Evaluation helper function - cache the bone mapping between two skeletal meshes

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RandomPlayer.h` (Public)


#### enum `ERandomDataIndexType`  
`enum class ERandomDataIndexType`  
_L14-18_
- L16 _public enumerator_ `Current`
- L17 _public enumerator_ `Next`

#### struct `FRandomPlayerSequenceEntry`  
`struct FRandomPlayerSequenceEntry`  
_L24-65_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: The random player node holds a list of sequences and parameter ranges which will be played continuously In a random order. If shuffle mode is enabled then each entry will be played once before repeating any
- L28 _public function_ `FRandomPlayerSequenceEntry() : Sequence(nullptr) , ChanceToPlay(1.0f) , MinLoopCount(0) , MaxLoopCount(0) , MinPlayRate(1.0f) , MaxPlayRate(1.0f)`
- L40 _public member_ `TObjectPtr<UAnimSequenceBase> Sequence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisallowedClasses = "/Script/Engine.AnimMontage"))` — Sequence to play when this entry is picked
- L44 _public member_ `float ChanceToPlay;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — When not in shuffle mode, this is the chance this entry will play (normalized against all other sample chances)
- L48 _public member_ `int32 MinLoopCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Minimum number of times this entry will loop before ending
- L52 _public member_ `int32 MaxLoopCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Maximum number of times this entry will loop before ending
- L56 _public member_ `float MinPlayRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Minimum playrate for this entry
- L60 _public member_ `float MaxPlayRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (UIMin = "0", ClampMin = "0"))` — Maximum playrate for this entry
- L64 _public member_ `FAlphaBlend BlendIn;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Blending properties used when this entry is blending in ontop of another entry

#### struct `FRandomAnimPlayData`  
`struct FRandomAnimPlayData`  
_L67-93_
- L70 _public member_ `FRandomPlayerSequenceEntry* Entry = nullptr;` — Index into the real sequence entry list, not the valid entry list.
- L74 _public member_ `float PlayStartTime = 0.0f;` — The time at which the animation started playing. Used to initialize the play for this animation and detect when a loop has occurred.
- L77 _public member_ `float CurrentPlayTime = 0.0f;` — The time at which the animation is currently playing.
- L80 _public member_ `FDeltaTimeRecord DeltaTimeRecord;` — Delta time record for this play through
- L83 _public member_ `float PlayRate = 0.0f;` — Calculated play rate
- L86 _public member_ `float BlendWeight = 0.0f;` — Current blend weight
- L89 _public member_ `int32 RemainingLoops = 0;` — Calculated loops remaining
- L92 _public member_ `FMarkerTickRecord MarkerTickRecord;` — Marker tick record for this play through

#### struct `FAnimNode_RandomPlayer`  
`struct FAnimNode_RandomPlayer : public FAnimNode_AssetPlayerRelevancyBase`  
_L96-184_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_AssetPlayerRelevancyBase`
- L100 _public prototype_ `FAnimNode_RandomPlayer();`
- L105 _public member_ `TArray<FRandomPlayerSequenceEntry> Entries;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — List of sequences to randomly step through
- L108 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L109 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L110 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L111 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L115 _public prototype_ `virtual UAnimationAsset* GetAnimAsset() const override;` — FAnimNode_RelevantAssetPlayerBase
- L116 _public prototype_ `virtual float GetAccumulatedTime() const override;`
- L117 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L118 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L119 _public prototype_ `virtual float GetCachedBlendWeight() const override;`
- L120 _public prototype_ `virtual void ClearCachedBlendWeight() override;`
- L121 _public prototype_ `virtual const FDeltaTimeRecord* GetDeltaTimeRecord() const override;`
- L127 _private prototype_ `int32 GetNextValidEntryIndex();` — Return the index of the next FRandomPlayerSequenceEntry to play, from the list of valid playable entries (ValidEntries).
- L131 _private prototype_ `FRandomAnimPlayData& GetPlayData(ERandomDataIndexType Type);` — Return the play data for either the currently playing animation or the next animation to blend into.
- L132 _private prototype_ `const FRandomAnimPlayData& GetPlayData(ERandomDataIndexType Type) const;`
- L136 _private prototype_ `void InitPlayData(FRandomAnimPlayData& Data, int32 InValidEntryIndex, float InBlendWeight);` — Initialize the play data with the given index into the ValidEntries array and a specific blend weight. All other member data will be reset to their default values.
- L140 _private prototype_ `void AdvanceToNextSequence();` — Advance to the next playable sequence. This is only called once a sequence is fully blended or there's a hard switch to the same playable entry.
- L146 _private prototype_ `void BuildShuffleList(int32 LastEntry);` — Build a new ShuffleList array, which is a shuffled index list of all the valid playable entries in ValidEntries. The LastEntry can be set to a valid entry index to ensure that the top/last item in the shuffle list will be a different value from it; pass in INDEX_NONE to disable the check.
- L149 _private member_ `TArray<FRandomPlayerSequenceEntry*> ValidEntries;` — List of valid sequence entries
- L152 _private member_ `TArray<float> NormalizedPlayChances;` — Normalized list of play chances when we aren't using shuffle mode
- L155 _private member_ `TArray<FRandomAnimPlayData> PlayData;` — Play data for the current and next sequence
- L158 _private member_ `int32 CurrentPlayDataIndex;` — Index of the 'current' data set in the PlayData array.
- L161 _private member_ `TArray<int32> ShuffleList;` — List to store transient shuffle stack in shuffle mode.
- L164 _private member_ `FRandomStream RandomStream;` — Random number source
- L169 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category = Relevancy, meta = (FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L175 _protected member_ `float BlendWeight = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = DoNotEdit)` — Last encountered blend weight for this node
- L183 _public member_ `bool bShuffleMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")` — When shuffle mode is active we will never loop a sequence beyond MaxLoopCount without visiting each sequence in turn (no repeats). Enabling this will ignore ChanceToPlay for each entry

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RefPose.h` (Public)


#### enum `ERefPoseType`  
`enum ERefPoseType : int`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `EIT_LocalSpace`
- L14 _public enumerator_ `EIT_Additive`

#### struct `FAnimNode_RefPose`  
`struct FAnimNode_RefPose : public FAnimNode_Base`  
_L19-42_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_Base`
- desc: RefPose pose nodes - ref pose or additive RefPose pose
- L26 _private member_ `TEnumAsByte<ERefPoseType> RefPoseType = EIT_LocalSpace;` — `UPROPERTY(meta=(FoldProperty))`
- L30 _public prototype_ `FAnimNode_RefPose() = default;`
- L34 _public function_ `void SetRefPoseType(ERefPoseType InType)` — Set the ref pose type of this node
- L38 _public prototype_ `ERefPoseType GetRefPoseType() const;` — Get the type of this ref pose
- L40 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L41 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

#### struct `FAnimNode_MeshSpaceRefPose`  
`struct FAnimNode_MeshSpaceRefPose : public FAnimNode_Base`  
_L45-52_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_Base`
- L49 _public prototype_ `FAnimNode_MeshSpaceRefPose() = default;`
- L51 _public prototype_ `virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output);`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RemoveCurve.h` (Public)


#### enum `ERemoveCurveMode`  
`enum class ERemoveCurveMode : uint8`  
_L12-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `RemoveSpecifiedCurves` — Removes animation curves which names are specified in the Curves variable from the Pose Input.
- L18 _public enumerator_ `KeepOnlySpecifiedCurves` — Removes ALL animation curves in the Pose Input, EXCEPT those specified in the Curves variable

#### struct `FAnimNode_RemoveCurve`  
`struct FAnimNode_RemoveCurve : public FAnimNode_Base`  
_L24-83_
- reflection: `USTRUCT(BlueprintInternalUseOnly, Experimental)`
- inherits: `FAnimNode_Base`
- desc: /  Removes animation curves on a pose
- L31 _public member_ `FPoseLink SourcePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Links")` — Input link (the upstream pose)
- L35 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alpha", meta = (PinShownByDefault))` — Is Enabled
- L41 _public member_ `ERemoveCurveMode RemoveMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remove Curves", meta = (BlueprintCompilerGeneratedDefaults, PinHiddenByDefault))` — Node mode selection. RemoveSpecifiedCurves -  will remove animation curves which names are specified in the Curves variable from the Pose Input KeepOnlySpecifiedCurves - will remove ALL animation curves in the Pose Input, EXCEPT those specified in the Curves variable
- L45 _public member_ `TSet<FName> Curves;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remove Curves", meta = (BlueprintCompilerGeneratedDefaults, PinHiddenByDefault))` — List of animation curves.
- L50 _public member_ `bool bAffectMorphTargetCurves;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remove Curves Filter by Type", meta = (NeverAsPin))` — Affect curves of a Morph Target type when True. Ignores them if False. I.e. curves of Morph Target type will be left completely unaffected by this node
- L55 _public member_ `bool bAffectMaterialCurves;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remove Curves Filter by Type", meta = (NeverAsPin))` — Affect curves of a Material type. Ignores them if False. I.e. curves of Material type will be left completely unaffected by this node
- L60 _public member_ `bool bAffectRegularCurves;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remove Curves Filter by Type", meta = (NeverAsPin))` — Affect normal animation curves (not Material or Morph Target type). Ignores them if False. I.e. regualar animation curves will be left completely unaffected by this node
- L64 _public member_ `TArray<FName> MorphTargetCurveNames;` — `UPROPERTY(transient)` — Internal vars.
- L67 _public member_ `TArray<FName> MaterialCurveNames;` — `UPROPERTY(transient)`
- L69 _public prototype_ `FAnimNode_RemoveCurve();`
- L72 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L73 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L74 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L76 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L77 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L82 _private member_ `UE::Anim::TNamedValueArray<FDefaultAllocator, UE::Anim::FCurveElement> CurvesForRemoval;` — Final list of curves to remove. Global, so it can be used in debug printouts anywhere.

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RotateRootBone.h` (Public)


#### struct `FAnimNode_RotateRootBone`  
`struct FAnimNode_RotateRootBone : public FAnimNode_Base`  
_L13-53_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: @TODO: Comment
- L18 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L21 _public member_ `float Pitch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))`
- L24 _public member_ `float Yaw;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))`
- L27 _public member_ `FInputScaleBiasClamp PitchScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L30 _public member_ `FInputScaleBiasClamp YawScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L33 _public member_ `FRotator MeshToComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))`
- L37 _public member_ `bool bRotateRootMotionAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Advanced)` — If enabled, rotating the root bone using this node will also rotate the direction of the root motion custom attribute
- L39 _public member_ `float ActualPitch;`
- L41 _public member_ `float ActualYaw;`
- L44 _public prototype_ `FAnimNode_RotateRootBone();`
- L47 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L48 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L49 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L50 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L51 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RotationOffsetBlendSpace.h` (Public)


#### struct `FAnimNode_RotationOffsetBlendSpace`  
`struct FAnimNode_RotationOffsetBlendSpace : public FAnimNode_BlendSpacePlayer`  
_L14-71_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpacePlayer`
- desc: @TODO: Comment
- L19 _public member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L23 _public member_ `bool bApplyAdditiveInRootSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))` — Apply the rotation additive in root space, effectively ignoring any root bone rotation.
- L32 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L36 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Current strength of the AimOffset
- L39 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L42 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayName = "Blend Settings"))`
- L45 _public member_ `FName AlphaCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))`
- L48 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L50 _public member_ `float ActualAlpha;`
- L53 _public member_ `EAnimAlphaInputType AlphaInputType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L56 _public member_ `bool bAlphaBoolEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, DisplayName = "bEnabled", DisplayAfter = "AlphaScaleBias"))`
- L58 _public member_ `bool bIsLODEnabled;`
- L61 _public prototype_ `FAnimNode_RotationOffsetBlendSpace();`
- L64 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L65 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L66 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L67 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L68 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L69 _public function_ `virtual int32 GetLODThreshold() const override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_RotationOffsetBlendSpaceGraph.h` (Public)


#### struct `FAnimNode_RotationOffsetBlendSpaceGraph`  
`struct FAnimNode_RotationOffsetBlendSpaceGraph : public FAnimNode_BlendSpaceGraphBase`  
_L12-75_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_BlendSpaceGraphBase`
- desc: Allows multiple animations to be blended between based on input parameters
- L21 _public function_ `FName GetGroupName() const` — @return the sync group that this blendspace uses
- L25 _private member_ `FPoseLink BasePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links, meta = (AllowPrivateAccess))`
- L29 _private member_ `bool bApplyAdditiveInRootSpace = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault, AllowPrivateAccess))` — Apply the rotation additive in root space, effectively ignoring any root bone rotation.
- L38 _private member_ `int32 LODThreshold = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (DisplayName = "LOD Threshold", AllowPrivateAccess))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L42 _private member_ `float Alpha = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, AllowPrivateAccess))` — Current strength of the AimOffset
- L45 _private member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (AllowPrivateAccess))`
- L48 _private member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayName = "Blend Settings", AllowPrivateAccess))`
- L51 _private member_ `FName AlphaCurveName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, AllowPrivateAccess))`
- L54 _private member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (AllowPrivateAccess))`
- L56 _private member_ `float ActualAlpha = 0.0f;`
- L59 _private member_ `EAnimAlphaInputType AlphaInputType = EAnimAlphaInputType::Float;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (AllowPrivateAccess))`
- L62 _private member_ `bool bAlphaBoolEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, DisplayName = "bEnabled", DisplayAfter = "AlphaScaleBias", AllowPrivateAccess))`
- L64 _private member_ `bool bIsLODEnabled = false;`
- L68 _private prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L69 _private prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L70 _private prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L71 _private prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L72 _private prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L73 _private function_ `virtual int32 GetLODThreshold() const override`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_SequenceEvaluator.h` (Public)


#### enum `ESequenceEvalReinit::Type`  
`enum Type : int`  
_L14-22_
- L17 _public enumerator_ `NoReset` — Do not reset InternalTimeAccumulator
- L19 _public enumerator_ `StartPosition` — Reset InternalTimeAccumulator to StartPosition
- L21 _public enumerator_ `ExplicitTime` — Reset InternalTimeAccumulator to ExplicitTime

#### struct `FAnimNode_SequenceEvaluatorBase`  
`struct FAnimNode_SequenceEvaluatorBase : public FAnimNode_AssetPlayerBase`  
_L29-96_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_AssetPlayerBase`
- desc: Abstract base class. Evaluates a point in an anim sequence, using a specific time input rather than advancing time internally. Typically the playback position of the animation for this node will represent something other than time, like jump height. This node will not trigger any notifies present in the associated sequence.
- L34 _private member_ `bool bReinitialized = false;`
- L38 _public prototype_ `virtual float GetCurrentAssetTime() const override;` — FAnimNode_AssetPlayerBase interface
- L39 _public prototype_ `virtual float GetCurrentAssetLength() const override;`
- L43 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L44 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L45 _public prototype_ `virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;`
- L46 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L47 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L51 _public function_ `virtual float GetAccumulatedTime() const override` — FAnimNode_AssetPlayerBase Interface
- L52 _public function_ `virtual void SetAccumulatedTime(float NewTime) override`
- L53 _public function_ `virtual UAnimationAsset* GetAnimAsset() const override`
- L56 _public function_ `void SetExplicitPreviousTime(float PreviousTime)`
- L59 _public prototype_ `virtual float GetEffectiveDeltaTime(float ExplicitTime, float PrevExplicitTime) const;` — Get the effective delta time between the previous and current frame internal time
- L62 _public function_ `virtual bool SetSequence(UAnimSequenceBase* InSequence)` — Set the animation sequence asset to evaluate
- L65 _public function_ `virtual bool SetExplicitTime(float InTime)` — Set the time at which to evaluate the associated sequence
- L68 _public function_ `virtual void SetTeleportToExplicitTime(bool bInTeleport)` — Set whether to teleport to explicit time when it is set
- L71 _public function_ `virtual void SetReinitializationBehavior(TEnumAsByte<ESequenceEvalReinit::Type> InBehavior)` — Set what to do when SequenceEvaluator is reinitialized
- L74 _public function_ `virtual UAnimSequenceBase* GetSequence() const` — The animation sequence asset to evaluate
- L77 _public function_ `virtual float GetExplicitTime() const` — The time at which to evaluate the associated sequence
- L80 _public function_ `virtual bool SetShouldLoop(bool bInShouldLoop)` — Set the animation to continue looping when it reaches the end
- L85 _public function_ `virtual bool GetTeleportToExplicitTime() const` — If true, teleport to explicit time, does NOT advance time (does not trigger notifies, does not extract Root Motion, etc.) If false, will advance time (will trigger notifies, extract root motion if applicable, etc.) Note: using a sync group forces advancing time regardless of what this option is set to.
- L88 _public function_ `virtual TEnumAsByte<ESequenceEvalReinit::Type> GetReinitializationBehavior() const` — What to do when SequenceEvaluator is reinitialized
- L91 _public function_ `virtual float GetStartPosition() const` — The start up position, it only applies when ReinitializationBehavior == StartPosition. Only used when bTeleportToExplicitTime is false.
- L94 _public prototype_ `void PostExposedInputsUpdateAssetPlayer(const FAnimationUpdateContext& Context);` — Called after executing the input pins, split for subclass convenience.

#### struct `FAnimNode_SequenceEvaluator`  
`struct FAnimNode_SequenceEvaluator : public FAnimNode_SequenceEvaluatorBase`  
_L100-185_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SequenceEvaluatorBase`
- desc: Sequence evaluator node that can be used with constant folding
- L110 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Sync, meta=(FoldProperty))` — The group name that we synchronize with (NAME_None if it is not part of any group).
- L114 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category=Sync, meta=(FoldProperty))` — The role this node can assume within the group (ignored if GroupName is not set)
- L118 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category=Sync, meta=(FoldProperty))` — How this node will synchronize with other animations.
- L122 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category=Relevancy, meta=(FoldProperty, PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L126 _private member_ `TObjectPtr<UAnimSequenceBase> Sequence = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, FoldProperty))` — The animation sequence asset to evaluate
- L130 _private member_ `float ExplicitTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(PinShownByDefault, FoldProperty, EditCondition="!bUseExplicitFrame"))` — The time at which to evaluate the associated sequence
- L134 _private member_ `bool bUseExplicitFrame = false;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(NeverAsPin, FoldProperty))` — Whether to use ExplicitFrame (true) or ExplicitTime (false) when evaluating the associated sequence
- L138 _private member_ `int32 ExplicitFrame = 0;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(PinHiddenByDefault, FoldProperty, EditCondition="bUseExplicitFrame"))` — The frame at which to evaluate the associated sequence
- L142 _private member_ `bool bShouldLoop = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, FoldProperty))` — This only works if bTeleportToExplicitTime is false OR this node is set to use SyncGroup
- L148 _private member_ `bool bTeleportToExplicitTime = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, FoldProperty))` — If true, teleport to explicit time, does NOT advance time (does not trigger notifies, does not extract Root Motion, etc.) If false, will advance time (will trigger notifies, extract root motion if applicable, etc.) Note: using a sync group forces advancing time regardless of what this option is set to.
- L152 _private member_ `TEnumAsByte<ESequenceEvalReinit::Type> ReinitializationBehavior = ESequenceEvalReinit::ExplicitTime;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(DisplayAfter="StartPosition", FoldProperty))` — What to do when SequenceEvaluator is reinitialized
- L156 _private member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, FoldProperty))` — The start up position, it only applies when ReinitializationBehavior == StartPosition. Only used when bTeleportToExplicitTime is false.
- L161 _public prototype_ `virtual bool SetSequence(UAnimSequenceBase* InSequence) override;` — FAnimNode_SequenceEvaluatorBase interface
- L162 _public prototype_ `virtual UAnimSequenceBase* GetSequence() const override;`
- L163 _public prototype_ `virtual float GetExplicitTime() const override;`
- L164 _public prototype_ `virtual bool SetExplicitTime(float InTime) override;`
- L165 _public prototype_ `virtual bool SetShouldLoop(bool bInShouldLoop) override;`
- L166 _public prototype_ `virtual bool GetTeleportToExplicitTime() const override;`
- L167 _public prototype_ `virtual TEnumAsByte<ESequenceEvalReinit::Type> GetReinitializationBehavior() const override;`
- L168 _public prototype_ `virtual float GetStartPosition() const override;`
- L171 _public prototype_ `virtual FName GetGroupName() const override;` — FAnimNode_AssetPlayerBase interface
- L172 _public prototype_ `virtual EAnimGroupRole::Type GetGroupRole() const override;`
- L173 _public prototype_ `virtual EAnimSyncMethod GetGroupMethod() const override;`
- L174 _public prototype_ `virtual bool GetIgnoreForRelevancyTest() const override;`
- L175 _public prototype_ `virtual bool IsLooping() const override;`
- L176 _public prototype_ `virtual bool SetGroupName(FName InGroupName) override;`
- L177 _public prototype_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override;`
- L178 _public prototype_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override;`
- L179 _public prototype_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override;`
- L181 _public prototype_ `bool ShouldUseExplicitFrame() const;`
- L182 _public prototype_ `bool SetShouldUseExplicitFrame(bool bFlag);`
- L183 _public prototype_ `bool SetExplicitFrame(int32 InFrame);`
- L184 _public prototype_ `int32 GetExplicitFrame() const;`

#### struct `FAnimNode_SequenceEvaluator_Standalone`  
`struct FAnimNode_SequenceEvaluator_Standalone : public FAnimNode_SequenceEvaluatorBase`  
_L189-281_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SequenceEvaluatorBase`
- desc: Sequence evaluator node that can be used standalone (without constant folding)
- L196 _private member_ `FName GroupName = NAME_None;` — `UPROPERTY(EditAnywhere, Category=Sync)` — The group name that we synchronize with (NAME_None if it is not part of any group).
- L200 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category=Sync)` — The role this node can assume within the group (ignored if GroupName is not set)
- L204 _private member_ `EAnimSyncMethod Method = EAnimSyncMethod::DoNotSync;` — `UPROPERTY(EditAnywhere, Category=Sync)` — How this node will synchronize with other animations.
- L208 _private member_ `bool bIgnoreForRelevancyTest = false;` — `UPROPERTY(EditAnywhere, Category=Relevancy, meta=(PinHiddenByDefault))` — If true, "Relevant anim" nodes that look for the highest weighted animation in a state will ignore this node
- L212 _private member_ `TObjectPtr<UAnimSequenceBase> Sequence = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — The animation sequence asset to evaluate
- L216 _private member_ `float ExplicitTime = 0.0f;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(PinShownByDefault, EditCondition="!bUseFrame"))` — The time at which to evaluate the associated sequence
- L219 _private member_ `bool bUseExplicitFrame = false;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(NeverAsPin))`
- L222 _private member_ `int32 ExplicitFrame = 0;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(PinHiddenByDefault, EditCondition="bUseFrame"))`
- L226 _private member_ `bool bShouldLoop = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — This only works if bTeleportToExplicitTime is false OR this node is set to use SyncGroup
- L232 _private member_ `bool bTeleportToExplicitTime = true;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — If true, teleport to explicit time, does NOT advance time (does not trigger notifies, does not extract Root Motion, etc.) If false, will advance time (will trigger notifies, extract root motion if applicable, etc.) Note: using a sync group forces advancing time regardless of what this option is set to.
- L236 _private member_ `TEnumAsByte<ESequenceEvalReinit::Type> ReinitializationBehavior = ESequenceEvalReinit::ExplicitTime;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(DisplayAfter="StartPosition"))` — What to do when SequenceEvaluator is reinitialized
- L240 _private member_ `float StartPosition = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — The start up position, it only applies when ReinitializationBehavior == StartPosition. Only used when bTeleportToExplicitTime is false.
- L244 _public function_ `virtual bool SetSequence(UAnimSequenceBase* InSequence) override` — FAnimNode_SequenceEvaluatorBase interface
- L245 _public function_ `virtual bool SetExplicitTime(float InTime) override`
- L246 _public function_ `virtual void SetTeleportToExplicitTime(bool bInTeleport) override`
- L247 _public function_ `virtual void SetReinitializationBehavior(TEnumAsByte<ESequenceEvalReinit::Type> InBehavior) override`
- L248 _public function_ `virtual UAnimSequenceBase* GetSequence() const override`
- L249 _public function_ `virtual float GetExplicitTime() const override`
- L262 _public function_ `virtual bool GetTeleportToExplicitTime() const override`
- L263 _public function_ `virtual TEnumAsByte<ESequenceEvalReinit::Type> GetReinitializationBehavior() const override`
- L264 _public function_ `virtual float GetStartPosition() const override`
- L267 _public function_ `virtual FName GetGroupName() const override` — FAnimNode_AssetPlayerBase interface
- L268 _public function_ `virtual EAnimGroupRole::Type GetGroupRole() const override`
- L269 _public function_ `virtual EAnimSyncMethod GetGroupMethod() const override`
- L270 _public function_ `virtual bool GetIgnoreForRelevancyTest() const override`
- L271 _public function_ `virtual bool IsLooping() const override`
- L272 _public function_ `virtual bool SetGroupName(FName InGroupName) override`
- L273 _public function_ `virtual bool SetGroupRole(EAnimGroupRole::Type InRole) override`
- L274 _public function_ `virtual bool SetGroupMethod(EAnimSyncMethod InMethod) override`
- L275 _public function_ `virtual bool SetIgnoreForRelevancyTest(bool bInIgnoreForRelevancyTest) override`
- L277 _public function_ `bool ShouldUseExplicitFrame() const`
- L278 _public function_ `void SetShouldUseExplicitFrame(bool bFlag)`
- L279 _public function_ `void SetExplicitFrame(int32 InFrame)`
- L280 _public function_ `int32 GetExplicitFrame() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ESequenceEvalReinit`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_Slot.h` (Public)


#### struct `FAnimNode_Slot`  
`struct FAnimNode_Slot : public FAnimNode_Base`  
_L15-47_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: An animation slot node normally acts as a passthru, but a montage or PlaySlotAnimation call from game code can cause an animation to blend in and be played on the slot temporarily, overriding the Source input.
- L21 _public member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — The source input, passed thru to the output unless a montage or slot animation is currently playing
- L25 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(CustomizeProperty))` — The name of this slot, exposed to gameplay code, etc...
- L29 _public member_ `bool bAlwaysUpdateSourcePose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Whether we should continue to update the source pose regardless of whether it would be used.
- L32 _protected function_ `virtual void PostEvaluateSourcePose(FPoseContext& SourceContext)`
- L34 _protected member_ `FSlotNodeWeightInfo WeightData;`
- L35 _protected member_ `FGraphTraversalCounter SlotNodeInitializationCounter;`
- L38 _public prototype_ `FAnimNode_Slot();`
- L41 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L42 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L43 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L44 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L45 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_StateResult.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_Sync.h` (Public)


#### struct `FAnimNode_Sync`  
`struct FAnimNode_Sync : public FAnimNode_Base`  
_L11-40_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L19 _public function_ `FName GetGroupName() const` — Get the group name that we synchronize with
- L23 _private member_ `FPoseLink Source;` — `UPROPERTY(EditAnywhere, Category = Links)`
- L27 _private member_ `FName GroupName;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The group name that we synchronize with (NAME_None if it is not part of any group).
- L31 _private member_ `TEnumAsByte<EAnimGroupRole::Type> GroupRole = EAnimGroupRole::CanBeLeader;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The role this animation can assume within the group (ignored if GroupName is not set)
- L35 _private prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base
- L36 _private prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L37 _private prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L38 _private prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L39 _private prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNodes/AnimNode_TwoWayBlend.h` (Public)


#### struct `FAnimNode_TwoWayBlend`  
`struct FAnimNode_TwoWayBlend : public FAnimNode_Base`  
_L13-89_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: This represents a baked transition
- L19 _public member_ `FPoseLink A;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L22 _public member_ `FPoseLink B;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)`
- L28 _public member_ `EAnimAlphaInputType AlphaInputType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — The data type used to control the alpha blending between the A and B poses. Note: Changing this value will disconnect alpha input pins.
- L32 _public member_ `uint8 bAlphaBoolEnabled:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault, DisplayName = "bEnabled", DisplayAfter="AlphaScaleBias"))` — The boolean value that controls the alpha blending when the alpha input type is set to 'Bool'
- L35 _protected member_ `uint8 bAIsRelevant:1;`
- L37 _protected member_ `uint8 bBIsRelevant:1;`
- L41 _protected member_ `uint8 bResetChildOnActivation:1;` — `UPROPERTY(EditAnywhere, Category = Option)` — This reinitializes child pose when re-activated. For example, when active child changes
- L45 _protected member_ `uint8 bAlwaysUpdateChildren:1;` — `UPROPERTY(EditAnywhere, Category = Option, meta=(PinHiddenByDefault))` — Always update children, regardless of whether or not that child has weight.
- L50 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))` — The float value that controls the alpha blending when the alpha input type is set to 'Float'
- L53 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings)`
- L56 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Blend Settings"))`
- L60 _public member_ `FName AlphaCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))` — The animation curve that controls the alpha blending when the alpha input type is set to 'Curve'
- L63 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`
- L66 _protected member_ `float InternalBlendAlpha;`
- L69 _public function_ `FAnimNode_TwoWayBlend() : AlphaInputType(EAnimAlphaInputType::Float) , bAlphaBoolEnabled(true) , bAIsRelevant(false) , bBIsRelevant(false) , bResetChildOnActivation(false) , bAlwaysUpdateChildren(false) , Alpha(0.0f) , AlphaCurveName(NAME_None) , InternalBlendAlpha(0.0f)`
- L83 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L84 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L85 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L86 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L87 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimNotifies/AnimNotify_PlayMontageNotify.h` (Public)


#### class `UAnimNotify_PlayMontageNotify`  
`class UAnimNotify_PlayMontageNotify : public UAnimNotify`  
_L13-31_
- reflection: `UCLASS(editinlinenew, const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Montage Notify"), MinimalAPI)`
- inherits: `UAnimNotify`
- L19 _public prototype_ `virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;`
- L21 _public prototype_ `virtual FString GetNotifyName_Implementation() const override;`
- L24 _public prototype_ `virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;`
- L30 _protected member_ `FName NotifyName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notify")` — Name of notify that is passed to the PlayMontage K2Node.

#### class `UAnimNotify_PlayMontageNotifyWindow`  
`class UAnimNotify_PlayMontageNotifyWindow : public UAnimNotifyState`  
_L39-57_
- reflection: `UCLASS(editinlinenew, const, hidecategories = Object, collapsecategories, meta = (DisplayName = "Montage Notify Window"), MinimalAPI)`
- inherits: `UAnimNotifyState`
- L44 _public prototype_ `virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;`
- L45 _public prototype_ `virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;`
- L47 _public prototype_ `virtual FString GetNotifyName_Implementation() const override;`
- L50 _public prototype_ `virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;`
- L56 _protected member_ `FName NotifyName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Notify")` — Name of notify that is passed to ability.

### `Source/Runtime/AnimGraphRuntime/Public/AnimSequencerInstance.h` (Public)


#### class `UAnimSequencerInstance`  
`class UAnimSequencerInstance : public UAnimInstance, public ISequencerAnimationSupport`  
_L18-55_
- reflection: `UCLASS(transient, NotBlueprintable, MinimalAPI)`
- inherits: `UAnimInstance,ISequencerAnimationSupport`
- L25 _public prototype_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InPosition, float Weight, bool bFireNotifies);` — Update an animation sequence player in this instance
- L26 _public prototype_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InFromPosition, float InToPosition, float Weight, bool bFireNotifies);`
- L28 _public prototype_ `void UpdateAnimTrackWithRootMotion(const FAnimSequencerData& InAnimSequencerData);`
- L31 _public prototype_ `virtual void ConstructNodes() override;` — Construct all nodes in this instance
- L34 _public prototype_ `virtual void ResetNodes() override;` — Reset all nodes in this instance
- L37 _public prototype_ `virtual void ResetPose() override;` — Reset the pose for this instance
- L40 _public prototype_ `virtual void SavePose() override;` — Saved the named pose to restore after
- L42 _public function_ `virtual UAnimInstance* GetSourceAnimInstance() override`
- L43 _public function_ `virtual void SetSourceAnimInstance(UAnimInstance* SourceAnimInstance)`
- L44 _public function_ `virtual bool DoesSupportDifferentSourceAnimInstance() const override`
- L48 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;` — UAnimInstance interface
- L53 _public member_ `static const FName SequencerPoseName;`

### `Source/Runtime/AnimGraphRuntime/Public/AnimSequencerInstanceProxy.h` (Public)


#### enum `ESwapRootBone`  
`enum class ESwapRootBone : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `SwapRootBone_Component` — Swap the root bone to the component
- L19 _public enumerator_ `SwapRootBone_Actor` — Swap root bone to the actor root component
- L21 _public enumerator_ `SwapRootBone_None` — Do not swap the root bone

#### struct `FSequencerPlayerBase`  
`struct FSequencerPlayerBase`  
_L25-58_
- desc: Base class for all 'players' that can attach to and be blended into a sequencer instance's output
- L28 _public function_ `FSequencerPlayerBase() : PoseIndex(INDEX_NONE) , bAdditive(false)`
- L34 _public function_ `template<class TType> bool IsOfType() const`
- L40 _public prototype_ `virtual ~FSequencerPlayerBase() = default;` — Virtual destructor.
- L44 _public member_ `int32 PoseIndex;` — Index of this players pose in the set of blend slots
- L47 _public member_ `bool bAdditive;` — Whether this pose is additive or not
- L53 _protected function_ `virtual bool IsOfTypeImpl(const FName& Type) const` — Checks whether this drag and drop operation can cast safely to the specified type.

#### struct `FRootMotionOverride`  
`struct FRootMotionOverride`  
_L62-71_
- desc: Optional Override To Specify RootMotion
- L64 _public function_ `FRootMotionOverride() :bBlendFirstChildOfRoot(false), ChildBoneIndex(INDEX_NONE), RootMotion(FTransform::Identity), PreviousTransform(FTransform::Identity)`
- L67 _public member_ `bool bBlendFirstChildOfRoot;` — If true we use the ChildBoneIndex otherwise we use the root
- L68 _public member_ `int32 ChildBoneIndex;`
- L69 _public member_ `FTransform RootMotion;`
- L70 _public member_ `FTransform PreviousTransform;`

#### struct `FAnimSequencerData`  
`struct FAnimSequencerData`  
_L73-99_
- L75 _public function_ `FAnimSequencerData(UAnimSequenceBase* InAnimSequence, int32 InSequenceId, const TOptional<FRootMotionOverride>& InRootMotion, float InFromPosition, float InToPosition, float InWeight, bool bInFireNotifies, ESwapRootBone InSwapRootBone, TOptional<FTransform> InInitialTransform, UMirrorDataTable* InMirrorDataTable) : AnimSequence(InAnimSequence) , SequenceId(InSequenceId) , RootMotion(InRootMotion) , FromPosition(InFromPosition) , ToPosition(InToPosition) , Weight(InWeight) , bFireNotifies(bInFireNotifies) , SwapRootBone(InSwapRootBone) , InitialTransform(InInitialTransform) , MirrorDataTable(InMirrorDataTable)`
- L89 _public member_ `UAnimSequenceBase* AnimSequence;`
- L90 _public member_ `int32 SequenceId;`
- L91 _public member_ `const TOptional<FRootMotionOverride>& RootMotion;`
- L92 _public member_ `float FromPosition;`
- L93 _public member_ `float ToPosition;`
- L94 _public member_ `float Weight;`
- L95 _public member_ `bool bFireNotifies;`
- L96 _public member_ `ESwapRootBone SwapRootBone;`
- L97 _public member_ `TOptional<FTransform> InitialTransform;`
- L98 _public member_ `UMirrorDataTable* MirrorDataTable;`

#### struct `FSequencerPlayerAnimSequence`  
`struct FSequencerPlayerAnimSequence : public FSequencerPlayerBase`  
_L107-112_
- inherits: `FSequencerPlayerBase`
- desc: Player type that evaluates a sequence-specified UAnimSequence
- L109 _public prototype_ `SEQUENCER_INSTANCE_PLAYER_TYPE(FSequencerPlayerAnimSequence, FSequencerPlayerBase) TOptional<FRootMotionOverride> RootMotion;`
- L111 _public member_ `FAnimNode_SequenceEvaluator_Standalone PlayerNode;`

#### struct `FAnimSequencerInstanceProxy`  
`struct FAnimSequencerInstanceProxy : public FAnimInstanceProxy`  
_L117-195_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L122 _public function_ `FAnimSequencerInstanceProxy()`
- L126 _public function_ `FAnimSequencerInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy(InAnimInstance)`
- L131 _public prototype_ `virtual ~FAnimSequencerInstanceProxy();`
- L134 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;` — FAnimInstanceProxy interface
- L135 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L136 _public prototype_ `virtual void PostEvaluate(UAnimInstance* InAnimInstance) override;`
- L137 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L140 _public prototype_ `void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, uint32 SequenceId, float InPosition, float Weight, bool bFireNotifies);` — Update an animation sequence player in this instance
- L141 _public prototype_ `void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, uint32 SequenceId, TOptional<float> InFromPosition, float InToPosition, float Weight, bool bFireNotifies);`
- L143 _public prototype_ `void UpdateAnimTrackWithRootMotion(const FAnimSequencerData& InAnimSequencerData);`
- L146 _public prototype_ `virtual void ResetNodes();` — Reset all nodes in this instance
- L149 _public prototype_ `virtual void ResetPose();` — Reset the pose in this instance
- L152 _public prototype_ `virtual void ConstructNodes();` — Construct and link the base part of the blend tree
- L154 _public prototype_ `virtual void AddReferencedObjects(UAnimInstance* InAnimInstance, FReferenceCollector& Collector) override;`
- L158 _protected prototype_ `void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, uint32 SequenceId, const TOptional<FRootMotionOverride>& RootMomtionOverride, TOptional<float> InFromPosition, float InToPosition, float Weight, bool bFireNotifies, UMirrorDataTable* InMirrorDataTable);`
- L162 _protected function_ `template<typename Type> Type* FindPlayer(uint32 SequenceId) const` — Find a player of a specified type
- L174 _protected member_ `struct FAnimNode_ApplyAdditive SequencerRootNode;` — custom root node for this sequencer player. Didn't want to use RootNode in AnimInstance because it's used with lots of AnimBP functionality
- L175 _protected member_ `struct FAnimNode_MultiWayBlend FullBodyBlendNode;`
- L176 _protected member_ `struct FAnimNode_MultiWayBlend AdditiveBlendNode;`
- L177 _protected member_ `struct FAnimNode_PoseSnapshot SnapshotNode;`
- L180 _protected member_ `TMap<uint32, FSequencerPlayerBase*> SequencerToPlayerMap;` — mapping from sequencer index to internal player index
- L183 _protected member_ `TMap<uint32, FAnimNode_Mirror_Standalone*> SequencerToMirrorMap;` — mapping from sequencer index to internal mirror node index
- L186 _protected member_ `TOptional<FRootMotionOverride> RootMotionOverride;` — custom root motion override sent in from sequencer
- L188 _protected prototype_ `void InitAnimTrack(UAnimSequenceBase* InAnimSequence, uint32 SequenceId);`
- L189 _protected prototype_ `void EnsureAnimTrack(UAnimSequenceBase* InAnimSequence, uint32 SequenceId);`
- L190 _protected prototype_ `void ClearSequencePlayerAndMirrorMaps();`
- L192 _protected member_ `ESwapRootBone SwapRootBone = ESwapRootBone::SwapRootBone_None;`
- L193 _protected member_ `TOptional<FTransform> InitialTransform;`
- L194 _protected member_ `TOptional<FTransform> RootBoneTransform;`

#### Free symbols / members of external scopes

- L102 _macro_ `#define SEQUENCER_INSTANCE_PLAYER_TYPE(TYPE, BASE) \` — Quick n dirty RTTI to allow for derived classes to insert nodes of different types

### `Source/Runtime/AnimGraphRuntime/Public/AnimationCustomVersion.h` (Public)


#### struct `FAnimationCustomVersion`  
`struct FAnimationCustomVersion`  
_L11-44_
- desc: Custom serialization version for assets/classes in the AnimGraphRuntime and AnimGraph modules
- L40 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L43 _private function_ `FAnimationCustomVersion()`

#### enum `FAnimationCustomVersion::Type`  
`enum Type`  
_L13-37_
- L16 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L20 _public enumerator_ `BoneDrivenControllerMatchingMaya = 1` — Added support for one-to-many component mappings to FAnimNode_BoneDrivenController, changed the range to apply to the input, and added a configurable method for updating the components
- L23 _public enumerator_ `BoneDrivenControllerRemapping = 2` — Converted the range clamp into a remap function, rather than just clamping
- L26 _public enumerator_ `AnimDynamicsAddAngularOffsets = 3` — Added ability to offset angular ranges for constraints
- L29 _public enumerator_ `RenamedStretchLimits = 4` — Renamed Stretch Limits to better names
- L32 _public enumerator_ `ConvertIKToSupportBoneSocketTarget = 5` — Convert IK to support FBoneSocketTarget
- L35 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L36 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMGRAPHRUNTIME_API`

### `Source/Runtime/AnimGraphRuntime/Public/AnimationStateMachineLibrary.h` (Public)


#### struct `FAnimationStateResultReference`  
`struct FAnimationStateResultReference : public FAnimNodeReference`  
_L17-22_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Animation State Reference")`
- inherits: `FAnimNodeReference`
- L21 _public typedef_ `typedef FAnimNode_StateResult FInternalNodeType;`

#### struct `FAnimationStateMachineReference`  
`struct FAnimationStateMachineReference : public FAnimNodeReference`  
_L25-30_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Animation State Machine")`
- inherits: `FAnimNodeReference`
- L29 _public typedef_ `typedef FAnimNode_StateMachine FInternalNodeType;`

#### class `UAnimationStateMachineLibrary`  
`class UAnimationStateMachineLibrary : public UBlueprintFunctionLibrary`  
_L34-91_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on anim state machine node contexts
- L41 _public prototype_ `static void ConvertToAnimationStateResult(const FAnimNodeReference& Node, FAnimationStateResultReference& AnimationState, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "State Machine", meta=(BlueprintThreadSafe, DisplayName = "Convert to Animation State", ExpandEnumAsExecs = "Result"))` — Get an anim state reference from an anim node reference
- L45 _public function_ `static void ConvertToAnimationStateResultPure(const FAnimNodeReference& Node, FAnimationStateResultReference& AnimationState, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta=(BlueprintThreadSafe, DisplayName = "Convert to Animation State"))` — Get an anim state reference from an anim node reference (pure)
- L54 _public prototype_ `static void ConvertToAnimationStateMachine(const FAnimNodeReference& Node, FAnimationStateMachineReference& AnimationState, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "State Machine", meta=(BlueprintThreadSafe, DisplayName = "Convert to Animation State Machine", ExpandEnumAsExecs = "Result"))` — Get an anim state machine from an anim node reference
- L59 _public function_ `static void ConvertToAnimationStateMachinePure(const FAnimNodeReference& Node, FAnimationStateMachineReference& AnimationState, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta = (BlueprintThreadSafe, DisplayName = "Convert to Animation State Machine"))` — Get an anim state machine from an anim node reference (pure)
- L68 _public prototype_ `static bool IsStateBlendingIn(const FAnimUpdateContext& UpdateContext, const FAnimationStateResultReference& Node);` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta=(BlueprintThreadSafe))` — Returns whether the state the node belongs to is blending in
- L72 _public prototype_ `static bool IsStateBlendingOut(const FAnimUpdateContext& UpdateContext, const FAnimationStateResultReference& Node);` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta=(BlueprintThreadSafe))` — Returns whether the state the node belongs to is blending out
- L77 _public prototype_ `static void SetState(const FAnimUpdateContext& UpdateContext, const FAnimationStateMachineReference& Node, FName TargetState, float Duration , TEnumAsByte<ETransitionLogicType::Type> BlendType, UBlendProfile* BlendProfile, EAlphaBlendOption AlphaBlendOption, UCurveFloat* CustomBlendCurve);` — `UFUNCTION(BlueprintCallable, Category = "State Machine", meta=(BlueprintThreadSafe, AdvancedDisplay = "4"))` — Manually set the current state of the state machine NOTE: Custom blend type is not supported
- L82 _public prototype_ `static FName GetState(const FAnimUpdateContext& UpdateContext, const FAnimationStateMachineReference& Node);` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta=(BlueprintThreadSafe))` — Returns the name of the current state of this state machine
- L86 _public prototype_ `static float GetRelevantAnimTimeRemaining(const FAnimUpdateContext& UpdateContext, const FAnimationStateResultReference& Node);` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta = (BlueprintThreadSafe))` — Returns the remaining animation time of the state's most relevant asset player
- L90 _public prototype_ `static float GetRelevantAnimTimeRemainingFraction(const FAnimUpdateContext& UpdateContext, const FAnimationStateResultReference& Node);` — `UFUNCTION(BlueprintPure, Category = "State Machine", meta = (BlueprintThreadSafe))` — Returns the remaining animation time as a fraction of the duration for the state's most relevant asset player

### `Source/Runtime/AnimGraphRuntime/Public/BlendListBaseLibrary.h` (Public)


#### struct `FBlendListBaseReference`  
`struct FBlendListBaseReference : public FAnimNodeReference`  
_L14-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L17 _public typedef_ `typedef FAnimNode_BlendListBase FInternalNodeType;`

#### class `UBlendListBaseLibrary`  
`class UBlendListBaseLibrary : public UBlueprintFunctionLibrary`  
_L22-37_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on anim state machine node contexts
- L30 _public prototype_ `static FBlendListBaseReference ConvertToBlendListBase(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Blend List Base", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a blend list base context from an anim node context.
- L34 _public prototype_ `static void ResetNode(const FBlendListBaseReference& BlendListBase);` — `UFUNCTION(BlueprintCallable, Category = "Blend List Base", meta = (BlueprintThreadSafe))` — Reset target blend list node to that the next blend is executed from a blank state

### `Source/Runtime/AnimGraphRuntime/Public/BlendSpaceLibrary.h` (Public)


#### struct `FBlendSpaceReference`  
`struct FBlendSpaceReference : public FAnimNodeReference`  
_L14-19_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L18 _public typedef_ `typedef FAnimNode_BlendSpaceGraph FInternalNodeType;`

#### class `UBlendSpaceLibrary`  
`class UBlendSpaceLibrary : public UBlueprintFunctionLibrary`  
_L25-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a blend space anim node.
- L32 _public prototype_ `static FBlendSpaceReference ConvertToBlendSpace(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a blend space context from an anim node context.
- L36 _public function_ `static void ConvertToBlendSpacePure(const FAnimNodeReference& Node, FBlendSpaceReference& BlendSpace, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Blend Space", meta = (BlueprintThreadSafe, DisplayName = "Convert to Blend Space (Pure)"))` — Get a blend space context from an anim node context (pure).
- L45 _public prototype_ `static FVector GetPosition(const FBlendSpaceReference& BlendSpace);` — `UFUNCTION(BlueprintPure, Category = "Blend Space", meta = (BlueprintThreadSafe))` — Get the current position of the blend space.
- L49 _public prototype_ `static FVector GetFilteredPosition(const FBlendSpaceReference& BlendSpace);` — `UFUNCTION(BlueprintPure, Category = "Blend Space", meta = (BlueprintThreadSafe))` — Get the current sample coordinates after going through the filtering.
- L53 _public prototype_ `static void SnapToPosition(const FBlendSpaceReference& BlendSpace, FVector NewPosition);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space", meta = (BlueprintThreadSafe))` — Forces the Position to the specified value

### `Source/Runtime/AnimGraphRuntime/Public/BlendSpacePlayerLibrary.h` (Public)


#### struct `FBlendSpacePlayerReference`  
`struct FBlendSpacePlayerReference : public FAnimNodeReference`  
_L14-19_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L18 _public typedef_ `typedef FAnimNode_BlendSpacePlayer FInternalNodeType;`

#### class `UBlendSpacePlayerLibrary`  
`class UBlendSpacePlayerLibrary : public UBlueprintFunctionLibrary`  
_L25-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a blend space player anim node.
- L32 _public prototype_ `static FBlendSpacePlayerReference ConvertToBlendSpacePlayer(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a blend space player context from an anim node context.
- L36 _public function_ `static void ConvertToBlendSpacePlayerPure(const FAnimNodeReference& Node, FBlendSpacePlayerReference& BlendSpacePlayer, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe, DisplayName = "Convert to Blend Space Player"))` — Get a blend space player context from an anim node context (pure).
- L45 _public prototype_ `static FBlendSpacePlayerReference SetBlendSpace(const FBlendSpacePlayerReference& BlendSpacePlayer, UBlendSpace* BlendSpace);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set the current BlendSpace of the blend space player.
- L49 _public prototype_ `static FBlendSpacePlayerReference SetBlendSpaceWithInertialBlending(const FAnimUpdateContext& UpdateContext, const FBlendSpacePlayerReference& BlendSpacePlayer, UBlendSpace* BlendSpace, float BlendTime = 0.2f);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set the current BlendSpace of the blend space player with an interial blend time.
- L53 _public prototype_ `static FBlendSpacePlayerReference SetResetPlayTimeWhenBlendSpaceChanges(const FBlendSpacePlayerReference& BlendSpacePlayer, bool bReset);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set whether the current play time should reset when BlendSpace changes of the blend space player.
- L57 _public prototype_ `static FBlendSpacePlayerReference SetPlayRate(const FBlendSpacePlayerReference& BlendSpacePlayer, float PlayRate);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set the play rate of the blend space player.
- L61 _public prototype_ `static FBlendSpacePlayerReference SetLoop(const FBlendSpacePlayerReference& BlendSpacePlayer, bool bLoop);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set the loop of the blend space player.
- L65 _public prototype_ `static UBlendSpace* GetBlendSpace(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current BlendSpace of the blend space player.
- L69 _public prototype_ `static FVector GetPosition(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current position of the blend space player.
- L73 _public prototype_ `static float GetStartPosition(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current start position of the blend space player.
- L77 _public prototype_ `static float GetPlayRate(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current play rate of the blend space player.
- L81 _public prototype_ `static bool GetLoop(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current loop of the blend space player.
- L85 _public prototype_ `static bool ShouldResetPlayTimeWhenBlendSpaceChanges(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Get the current value of whether the current play time should reset when BlendSpace changes of the blend space player.
- L89 _public prototype_ `static void SnapToPosition(const FBlendSpacePlayerReference& BlendSpacePlayer, FVector NewPosition);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Forces the Position to the specified value
- L93 _public prototype_ `static FBlendSpacePlayerReference SetAccumulatedTime(const FBlendSpacePlayerReference& BlendSpacePlayer, float Time);` — `UFUNCTION(BlueprintCallable, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Set the current accumulated time of the blend space player. For blend spaces, this is normalized (0 - 1)
- L97 _public prototype_ `static float GetAccumulatedTime(const FBlendSpacePlayerReference& BlendSpacePlayer);` — `UFUNCTION(BlueprintPure, Category = "Blend Space Player", meta = (BlueprintThreadSafe))` — Gets the current accumulated time of the blend space player. For blend spaces, this is normalized (0 - 1)

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_AnimDynamics.h` (Public)


#### enum `AnimPhysAngularConstraintType`  
`enum class AnimPhysAngularConstraintType : uint8`  
_L38-42_
- reflection: `UENUM()`
- desc: Supported angular constraint types
- L40 _public enumerator_ `Angular`
- L41 _public enumerator_ `Cone`

#### enum `AnimPhysLinearConstraintType`  
`enum class AnimPhysLinearConstraintType : uint8`  
_L46-50_
- reflection: `UENUM()`
- desc: Supported linear axis constraints
- L48 _public enumerator_ `Free`
- L49 _public enumerator_ `Limited`

#### enum `AnimPhysSimSpaceType`  
`enum class AnimPhysSimSpaceType : uint8`  
_L53-60_
- reflection: `UENUM(BlueprintType)`
- L55 _public enumerator_ `Component UMETA(ToolTip = "Sim origin is the location/orientation of the skeletal mesh component.")`
- L56 _public enumerator_ `Actor UMETA(ToolTip = "Sim origin is the location/orientation of the actor containing the skeletal mesh component.")`
- L57 _public enumerator_ `World UMETA(ToolTip = "Sim origin is the world origin. Teleporting characters is not recommended in this mode.")`
- L58 _public enumerator_ `RootRelative UMETA(ToolTip = "Sim origin is the location/orientation of the root bone.")`
- L59 _public enumerator_ `BoneRelative UMETA(ToolTip = "Sim origin is the location/orientation of the bone specified in RelativeSpaceBone")`

#### struct `FAnimPhysBoneRigidBody`  
`struct FAnimPhysBoneRigidBody`  
_L63-72_
- desc: Helper mapping a rigid body to a bone reference
- L65 _public function_ `FAnimPhysBoneRigidBody(TArray<FAnimPhysShape>& Shapes, const FVector& Position, const FBoneReference& LinkedBone) : PhysBody(Shapes, Position) , BoundBone(LinkedBone)`
- L70 _public member_ `FAnimPhysRigidBody PhysBody;`
- L71 _public member_ `FBoneReference BoundBone;`

#### struct `FAnimPhysLinkedBody`  
`struct FAnimPhysLinkedBody`  
_L75-84_
- desc: Helper describing a body linked to an optional parent (can be nullptr)
- L77 _public function_ `FAnimPhysLinkedBody(TArray<FAnimPhysShape>& Shapes, const FVector& Position, const FBoneReference& LinkedBone) : RigidBody(Shapes, Position, LinkedBone) , ParentBody(nullptr)`
- L82 _public member_ `FAnimPhysBoneRigidBody RigidBody;`
- L83 _public member_ `FAnimPhysBoneRigidBody* ParentBody;`

#### struct `FAnimPhysConstraintSetup`  
`struct FAnimPhysConstraintSetup`  
_L88-184_
- reflection: `USTRUCT()`
- desc: Constraint setup struct, holds data required to build a physics constraint
- L92 _public function_ `FAnimPhysConstraintSetup() : LinearXLimitType(AnimPhysLinearConstraintType::Limited) , LinearYLimitType(AnimPhysLinearConstraintType::Limited) , LinearZLimitType(AnimPhysLinearConstraintType::Limited) , bLinearFullyLocked(false) , LinearAxesMin(ForceInitToZero) , LinearAxesMax(ForceInitToZero) , AngularConstraintType(AnimPhysAngularConstraintType::Angular) , TwistAxis(AnimPhysTwistAxis::AxisX) , AngularTargetAxis(AnimPhysTwistAxis::AxisX) , ConeAngle(0.0f) #if WITH_EDITORONLY_DATA , AngularXAngle_DEPRECATED(0.0f) , AngularYAngle_DEPRECATED(0.0f) , AngularZAngle_DEPRECATED(0.0f) #endif , AngularLimitsMin(ForceInitToZero) , AngularLimitsMax(ForceInitToZero) , AngularTarget(ForceInitToZero)`
- L115 _public member_ `AnimPhysLinearConstraintType LinearXLimitType;` — `UPROPERTY(EditAnywhere, Category = Linear)` — Whether to limit the linear X axis
- L119 _public member_ `AnimPhysLinearConstraintType LinearYLimitType;` — `UPROPERTY(EditAnywhere, Category = Linear)` — Whether to limit the linear Y axis
- L123 _public member_ `AnimPhysLinearConstraintType LinearZLimitType;` — `UPROPERTY(EditAnywhere, Category = Linear)` — Whether to limit the linear Z axis
- L126 _public member_ `bool bLinearFullyLocked;` — If all axes are locked we can use 3 linear limits instead of the 6 needed for limited axes
- L130 _public member_ `FVector LinearAxesMin;` — `UPROPERTY(EditAnywhere, Category = Linear, meta = (UIMax = "0", ClampMax = "0"))` — Minimum linear movement per-axis (Set zero here and in the max limit to lock)
- L134 _public member_ `FVector LinearAxesMax;` — `UPROPERTY(EditAnywhere, Category = Linear, meta = (UIMin = "0", ClampMin = "0"))` — Maximum linear movement per-axis (Set zero here and in the min limit to lock)
- L138 _public member_ `AnimPhysAngularConstraintType AngularConstraintType;` — `UPROPERTY(EditAnywhere, Category = Angular)` — Method to use when constraining angular motion
- L142 _public member_ `AnimPhysTwistAxis TwistAxis;` — `UPROPERTY(EditAnywhere, Category = Angular)` — Axis to consider for twist when constraining angular motion (forward axis)
- L150 _public member_ `AnimPhysTwistAxis AngularTargetAxis;` — `UPROPERTY(EditAnywhere, Category = Angular, meta=(DisplayAfter=AngularLimitsMax))` — The axis in the simulation pose to align to the Angular Target. This is typically the axis pointing along the bone. Note: This is affected by the Angular Spring Constant.
- L154 _public member_ `float ConeAngle;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "0", UIMax = "90", ClampMin = "0", ClampMax = "90"))` — Angle to use when constraining using a cone
- L159 _public member_ `float AngularXAngle_DEPRECATED;` — `UPROPERTY()` — X-axis limit for angular motion when using the "Angular" constraint type (Set to 0 to lock, or 180 to remain free)
- L163 _public member_ `float AngularYAngle_DEPRECATED;` — `UPROPERTY()` — Y-axis limit for angular motion when using the "Angular" constraint type (Set to 0 to lock, or 180 to remain free)
- L167 _public member_ `float AngularZAngle_DEPRECATED;` — `UPROPERTY()` — Z-axis limit for angular motion when using the "Angular" constraint type (Set to 0 to lock, or 180 to remain free)
- L171 _public member_ `FVector AngularLimitsMin;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`
- L174 _public member_ `FVector AngularLimitsMax;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`
- L183 _public member_ `FVector AngularTarget;` — `UPROPERTY(EditAnywhere, Category = Angular)` — The axis to align the angular spring constraint to in the animation pose. This typically points down the bone - so values of (1.0, 0.0, 0.0) are common, but you can pick other values to align the spring to a different direction. Note: This is affected by the Angular Spring Constant.

#### struct `FAnimPhysPlanarLimit`  
`struct FAnimPhysPlanarLimit`  
_L187-200_
- reflection: `USTRUCT()`
- L193 _public member_ `FBoneReference DrivingBone;` — `UPROPERTY(EditAnywhere, Category=PlanarLimit)` — When using a driving bone, the plane transform will be relative to the bone transform
- L199 _public member_ `FTransform PlaneTransform;` — `UPROPERTY(EditAnywhere, Category=PlanarLimit)` — Transform of the plane, this is either in component-space if no DrivinBone is specified or in bone-space if a driving bone is present.

#### enum `ESphericalLimitType`  
`enum class ESphericalLimitType : uint8`  
_L204-208_
- reflection: `UENUM()`
- desc: Whether spheres keep bodies inside, or outside of their shape
- L206 _public enumerator_ `Inner`
- L207 _public enumerator_ `Outer`

#### struct `FAnimPhysSphericalLimit`  
`struct FAnimPhysSphericalLimit`  
_L211-236_
- reflection: `USTRUCT()`
- L215 _public function_ `FAnimPhysSphericalLimit() : SphereLocalOffset(FVector::ZeroVector) , LimitRadius(0.0f) , LimitType(ESphericalLimitType::Outer)`
- L223 _public member_ `FBoneReference DrivingBone;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit)` — Bone to attach the sphere to
- L227 _public member_ `FVector SphereLocalOffset;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit)` — Local offset for the sphere, if no driving bone is set this is in node space, otherwise bone space
- L231 _public member_ `float LimitRadius;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit)` — Radius of the sphere
- L235 _public member_ `ESphericalLimitType LimitType;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit)` — Whether to lock bodies inside or outside of the sphere

#### struct `FAnimPhysBodyDefinition`  
`struct FAnimPhysBodyDefinition`  
_L239-284_
- reflection: `USTRUCT()`
- L243 _public function_ `FAnimPhysBodyDefinition() : BoxExtents(10.0f, 10.0f, 10.0f) , LocalJointOffset(FVector::ZeroVector) , CollisionType(AnimPhysCollisionType::CoM) , SphereCollisionRadius(10.0f)`
- L250 _public function_ `FAnimPhysBodyDefinition& operator=(const FAnimPhysBodyDefinition& Other)`
- L263 _public member_ `FBoneReference BoundBone;` — `UPROPERTY(VisibleAnywhere, Category = PhysicsBodyDefinition, meta = (EditCondition = "false"))`
- L267 _public member_ `FVector BoxExtents;` — `UPROPERTY(EditAnywhere, Category = PhysicsBodyDefinition, meta = (UIMin = "1", ClampMin = "1"))` — Extents of the box to use for simulation
- L271 _public member_ `FVector LocalJointOffset;` — `UPROPERTY(EditAnywhere, Category = PhysicsBodyDefinition)` — Vector relative to the body being simulated to attach the constraint to
- L275 _public member_ `FAnimPhysConstraintSetup ConstraintSetup;` — `UPROPERTY(EditAnywhere, Category = Constraint)` — Data describing the constraints we will apply to the body
- L279 _public member_ `AnimPhysCollisionType CollisionType;` — `UPROPERTY(EditAnywhere, Category = Collision)` — Resolution method for planar limits
- L283 _public member_ `float SphereCollisionRadius;` — `UPROPERTY(EditAnywhere, Category = PhysicsBodyDefinition, meta = (UIMin = "1", ClampMin = "1", EditCondition = "CollisionType == AnimPhysCollisionType::CustomSphere"))` — Radius to use if CollisionType is set to CustomSphere

#### struct `FAnimConstraintOffsetPair`  
`struct FAnimConstraintOffsetPair`  
_L286-295_
- L288 _public function_ `FAnimConstraintOffsetPair(const FVector& InBody0Offset, const FVector InBody1Offset) : Body0Offset(InBody0Offset) , Body1Offset(InBody1Offset)`
- L293 _public member_ `FVector Body0Offset;`
- L294 _public member_ `FVector Body1Offset;`

#### enum `TIsPODType::(anonymous)`  
`template <> struct TIsPODType<FAnimPhysSimSpaceSettings>`  
_L302-302_
- desc: Settings for the system which passes rotational motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.

#### struct `TIsPODType`  
`template <> struct TIsPODType<FAnimPhysSimSpaceSettings>`  
_L302-302_
- desc: Settings for the system which passes rotational motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.

#### struct `FAnimPhysSimSpaceSettings`  
`struct FAnimPhysSimSpaceSettings`  
_L305-346_
- reflection: `USTRUCT(BlueprintType)`
- L309 _public prototype_ `FAnimPhysSimSpaceSettings();`
- L311 _public prototype_ `~FAnimPhysSimSpaceSettings() = default;`
- L312 _public prototype_ `FAnimPhysSimSpaceSettings(FAnimPhysSimSpaceSettings const&) = default;`
- L313 _public prototype_ `FAnimPhysSimSpaceSettings& operator=(const FAnimPhysSimSpaceSettings&) = default;`
- L320 _public member_ `float SimSpaceAngularAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Global multipler on the effects of simulation space rotational movement. Must be in range[0, 1].If SimSpaceAngularAlpha = 0.0, the system is disabled and the simulation will be fully local (i.e., world-space actor movement and rotation does not affect the simulation).
- L328 _public member_ `float MaxAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space angular velocity that is passed to the simulation. Units are radian/s, so a value of about 6.0 is one rotation per second. The default value effectively means "unlimited". You would reduce this (and MaxAngularAcceleration) to limit how much bodies "fly out" when the actor spins on the spot. This is especially useful if you have characters than can rotate very quickly and you would probably want values around or less than 10 in this case.
- L336 _public member_ `float MaxAngularAcceleration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space angular accleration that is passed to the simulation. Units are radian/s/s. The default value effectively means "unlimited". This has a similar effect to MaxAngularVelocity, except that it is related to the flying out of bodies when the rotation speed suddenly changes. Typical limits for a character might be around 100.
- L344 _public member_ `FVector ExternalAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Additional angular velocity that is added to the component angular velocity. This can be used to make the simulation act as if the actor is rotating even when it is not. E.g., to apply physics to a character on a podium as the camera rotates around it, to emulate the podium itself rotating. Vector is in world space. Units are rad/s.

#### struct `FAnimNode_AnimDynamics`  
`struct FAnimNode_AnimDynamics : public FAnimNode_SkeletalControlBase`  
_L350-701_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L354 _public prototype_ `FAnimNode_AnimDynamics();`
- L360 _public member_ `float LinearDampingOverride;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "NumSolverIterationsPostUpdate", EditCondition = bOverrideLinearDamping))` — Overridden linear damping value. The default is 0.7. Values below 0.7 won't have an effect.
- L366 _public member_ `float AngularDampingOverride;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "LinearDampingOverride", EditCondition = bOverrideAngularDamping))` — Overridden angular damping value. The default is 0.7. Values below 0.7 won't have an effect.
- L369 _public member_ `FTransform PreviousCompWorldSpaceTM;` — Previous component & actor transforms, used to account for teleports
- L370 _public member_ `FTransform PreviousActorWorldSpaceTM;`
- L371 _public member_ `FTransform PreviousSimSpaceTM;`
- L375 _public member_ `FBoneReference RelativeSpaceBone;` — `UPROPERTY(EditAnywhere, Category = Setup, meta=(DisplayAfter="SimulationSpace", EditCondition = "SimulationSpace == AnimPhysSimSpaceType::BoneRelative"))` — When in BoneRelative sim space, the simulation will use this bone as the origin
- L379 _public member_ `FBoneReference BoundBone;` — `UPROPERTY(EditAnywhere, Category = Setup)` — The bone to attach the physics body to, if bChain is true this is the top of the chain
- L383 _public member_ `FBoneReference ChainEnd;` — `UPROPERTY(EditAnywhere, Category = Setup, meta = (EditCondition = bChain, DisplayAfter = "BoundBone"))` — If bChain is true this is the bottom of the chain, otherwise ignored
- L386 _public member_ `TArray< FAnimPhysBodyDefinition > PhysicsBodyDefinitions;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = PhysicsParameters, meta = (DisplayName = "Body Definitions", EditFixedOrder, DisplayAfter = "ChainEnd"))`
- L390 _public member_ `float GravityScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "bGravityOverrideInSimSpace", EditCondition = "!bUseGravityOverride"))` — Scale for gravity, higher values increase forces due to gravity
- L394 _public member_ `FVector GravityOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "bUseGravityOverride", EditCondition = "bUseGravityOverride"))` — Gravity Override Value
- L401 _public member_ `float LinearSpringConstant;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsParameters, meta = (EditCondition = bLinearSpring, PinHiddenByDefault, DisplayAfter = "AngularSpringConstant"))` — Spring constant to use when calculating linear springs, higher values mean a stronger spring. You need to enable the Linear Spring checkbox for this to have an effect.
- L409 _public member_ `float AngularSpringConstant;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsParameters, meta = (DisplayAfter = "PhysicsBodyDefinitions", EditCondition = bAngularSpring, PinHiddenByDefault))` — Spring constant to use when calculating angular springs, higher values mean a stronger spring. You need to enable the Angular Spring checkbox for this to have an effect. Note: Make sure to also set the Angular Target Axis and Angular Target in the Constraint Setup for this to have an effect.
- L415 _public member_ `float WorldSpaceMinimumScale;` — `UPROPERTY(EditAnywhere, Category = Settings)` — For world-space simulations, if the magnitude of the component's 3D scale is less than WorldSpaceMinimumScale, do not update the node.
- L419 _public member_ `float WindScale;` — `UPROPERTY(EditAnywhere, Category = Wind, meta=(DisplayAfter="bEnableWind"))` — Scale to apply to calculated wind velocities in the solver
- L423 _public member_ `FVector ComponentLinearAccScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this controls how much of the components world-space acceleration is passed on to the local-space simulation.
- L427 _public member_ `FVector ComponentLinearVelScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this applies a 'drag' to the bodies in the local space simulation, based on the components world-space velocity.
- L431 _public member_ `FVector ComponentAppliedLinearAccClamp;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When using non-world-space sim, this is an overall clamp on acceleration derived from ComponentLinearAccScale and ComponentLinearVelScale, to ensure it is not too large.
- L444 _public member_ `FAnimPhysSimSpaceSettings SimSpaceSettings;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way. This system is a superset of the functionality provided by ComponentLinearAccScale, ComponentLinearVelScale, and ComponentAppliedLinearAccClamp. In general you should not have both systems enabled.
- L452 _public member_ `float AngularBiasOverride;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "AngularDampingOverride", EditCondition = bOverrideAngularBias))` — Overridden angular bias value Angular bias is essentially a twist reduction for chain forces and defaults to a value to keep chains stability in check. When using single-body systems sometimes angular forces will look like they are "catching-up" with the mesh, if that's the case override this and push it towards 1.0f until it settles correctly
- L456 _public member_ `int32 NumSolverIterationsPreUpdate;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters)` — Number of update passes on the linear and angular limits before we solve the position of the bodies recommended to be four times the value of NumSolverIterationsPostUpdate
- L460 _public member_ `int32 NumSolverIterationsPostUpdate;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta = (PinHiddenByDefault, DisplayAfter = "NumSolverIterationsPreUpdate"))` — Number of update passes on the linear and angular limits after we solve the position of the bodies, recommended to be around a quarter of NumSolverIterationsPreUpdate
- L464 _public member_ `TArray<FAnimPhysSphericalLimit> SphericalLimits;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit, meta=(DisplayAfter="bUseSphericalLimits"))` — List of available spherical limits for this node
- L468 _public member_ `FVector ExternalForce;` — `UPROPERTY(EditAnywhere, Category = Forces, meta = (PinShownByDefault))` — An external force to apply to all bodies in the simulation when ticked, specified in world space
- L472 _public member_ `TArray<FAnimPhysPlanarLimit> PlanarLimits;` — `UPROPERTY(EditAnywhere, Category=PlanarLimit, meta=(DisplayAfter="bUsePlanarLimit"))` — List of available planar limits for this node
- L476 _public member_ `AnimPhysSimSpaceType SimulationSpace;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (PinHiddenByDefault, DisplayPriority=0))` — The space used to run the simulation
- L479 _public member_ `AnimPhysSimSpaceType LastSimSpace;` — Cached sim space that we last used
- L483 _public member_ `ETeleportType InitTeleportType;` — We can't get clean bone positions unless we are in the evaluate step. Requesting an init or reinit sets this flag for us to pick up during evaluate
- L487 _public member_ `uint8 bUseSphericalLimits:1;` — `UPROPERTY(EditAnywhere, Category = SphericalLimit)` — Whether to evaluate spherical limits
- L491 _public member_ `uint8 bUsePlanarLimit:1;` — `UPROPERTY(EditAnywhere, Category=PlanarLimit)` — Whether to evaluate planar limits
- L495 _public member_ `uint8 bDoUpdate : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta = (DisplayAfter = "bDoEval"))` — If true we will perform physics update, otherwise skip - allows visualization of the initial state of the bodies
- L499 _public member_ `uint8 bDoEval : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta = (DisplayAfter = "AngularBiasOverride"))` — If true we will perform bone transform evaluation, otherwise skip - allows visualization of the initial anim state compared to the physics sim
- L503 _public member_ `uint8 bOverrideLinearDamping:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta=(InlineEditConditionToggle, DisplayAfter="AngularSpringConstraint"))` — If true, the override value will be used for linear damping
- L511 _public member_ `uint8 bOverrideAngularBias:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta=(InlineEditConditionToggle, DisplayAfter="AngularDampingOverride"))` — If true, the override value will be used for the angular bias for bodies in this node. Angular bias is essentially a twist reduction for chain forces and defaults to a value to keep chains stability in check. When using single-body systems sometimes angular forces will look like they are "catching-up" with the mesh, if that's the case override this and push it towards 1.0f until it settles correctly
- L515 _public member_ `uint8 bOverrideAngularDamping:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = PhysicsParameters, meta=(InlineEditConditionToggle, DisplayAfter="LinearDampingOverride"))` — If true, the override value will be used for angular damping
- L519 _public member_ `uint8 bEnableWind:1;` — `UPROPERTY(EditAnywhere, Category = Wind)` — Whether or not wind is enabled for the bodies in this simulation
- L521 _public member_ `uint8 bWindWasEnabled:1;`
- L525 _public member_ `uint8 bUseGravityOverride:1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicsParameters, meta = (DisplayAfter = "LinearSpringConstant"))` — Use gravity override value vs gravity scale
- L529 _public member_ `uint8 bGravityOverrideInSimSpace : 1;` — `UPROPERTY(EditAnywhere, Category = PhysicsParameters, meta=(DisplayAfter = "GravityOverride", DisplayName = "Gravity Override In Sim Space", EditCondition = "bUseGravityOverride"))` — If true the gravity override value is defined in simulation space, by default it is in world space
- L533 _public member_ `uint8 bLinearSpring:1;` — `UPROPERTY(EditAnywhere, Category = PhysicsParameters, meta = (InlineEditConditionToggle))` — If true the body will attempt to spring back to its initial position
- L537 _public member_ `uint8 bAngularSpring:1;` — `UPROPERTY(EditAnywhere, Category = PhysicsParameters, meta = (InlineEditConditionToggle))` — If true the body will attempt to align itself with the specified angular target
- L541 _public member_ `uint8 bChain:1;` — `UPROPERTY(EditAnywhere, Category = Setup, meta=(InlineEditConditionToggle))` — Set to true to use the solver to simulate a connected chain
- L545 _public member_ `FRotationRetargetingInfo RetargetingSettings;` — `UPROPERTY(EditAnywhere, Category = Retargeting)` — The settings for rotation retargeting
- L549 _public member_ `FVector BoxExtents_DEPRECATED;` — `UPROPERTY()`
- L551 _public member_ `FVector LocalJointOffset_DEPRECATED;` — `UPROPERTY()`
- L553 _public member_ `FAnimPhysConstraintSetup ConstraintSetup_DEPRECATED;` — `UPROPERTY()`
- L555 _public member_ `AnimPhysCollisionType CollisionType_DEPRECATED;` — `UPROPERTY()`
- L557 _public member_ `float SphereCollisionRadius_DEPRECATED;` — `UPROPERTY()`
- L561 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L562 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L563 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L564 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L565 _public function_ `virtual bool HasPreUpdate() const override`
- L566 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L567 _public function_ `virtual bool NeedsDynamicReset() const override`
- L568 _public function_ `virtual void ResetDynamics(ETeleportType InTeleportType) override`
- L569 _public prototype_ `virtual int32 GetLODThreshold() const override;`
- L572 _public prototype_ `void RequestInitialise(ETeleportType InTeleportType);`
- L573 _public prototype_ `void InitPhysics(FComponentSpacePoseContext& Output);`
- L574 _public prototype_ `void TermPhysics();`
- L576 _public prototype_ `void UpdateChainPhysicsBodyDefinitions(const FReferenceSkeleton& ReferenceSkeleton);`
- L577 _public prototype_ `void ValidateChainPhysicsBodyDefinitions(const FReferenceSkeleton& ReferenceSkeleton);`
- L578 _public prototype_ `void FindChainBoneNames(const FReferenceSkeleton& ReferenceSkeleton, TArray<FName>& ChainBoneNames);`
- L579 _public prototype_ `void UpdateLimits(FComponentSpacePoseContext& Output);`
- L581 _public prototype_ `int32 GetNumBodies() const;`
- L582 _public prototype_ `const FAnimPhysRigidBody& GetPhysBody(int32 BodyIndex) const;`
- L584 _public prototype_ `FTransform GetBodyComponentSpaceTransform(const FAnimPhysRigidBody& Body, const USkeletalMeshComponent* const SkelComp) const;`
- L589 _public prototype_ `FVector GetBodyLocalJointOffset(const int32 BodyIndex) const;` — Accessors for editor code (mainly for visualization functions)
- L592 _public member_ `bool bDoPhysicsUpdateInEditor;` — True by default, if false physics simulation will not update this frame. Used to prevent the rig moving whilst interactively editing parameters with a widget in the viewport.
- L596 _public prototype_ `bool ShouldDoPhysicsUpdate() const;`
- L601 _protected prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase protected interface
- L602 _protected prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones);`
- L607 _private prototype_ `FTransform GetBoneTransformInSimSpace(FComponentSpacePoseContext& Output, const FCompactPoseBoneIndex& BoneIndex) const;` — Given a bone index, get it's transform in the currently selected simulation space
- L610 _private prototype_ `FTransform GetComponentSpaceTransformFromSimSpace(AnimPhysSimSpaceType SimSpace, FComponentSpacePoseContext& Output, const FTransform& InSimTransform) const;` — Given a transform in simulation space, convert it back to component space
- L611 _private prototype_ `FTransform GetComponentSpaceTransformFromSimSpace(AnimPhysSimSpaceType SimSpace, FComponentSpacePoseContext& Output, const FTransform& InSimTransform, const FTransform& InCompWorldSpaceTM, const FTransform& InActorWorldSpaceTM) const;`
- L612 _private prototype_ `FTransform GetComponentSpaceTransformFromSimSpace(AnimPhysSimSpaceType SimSpace, const USkeletalMeshComponent* const SkelComp, const FTransform& InSimTransform) const;`
- L614 _private prototype_ `FTransform GetSimToWorldSpaceTransform(AnimPhysSimSpaceType SimSpace, FComponentSpacePoseContext& Output) const;`
- L617 _private prototype_ `FTransform GetSimSpaceTransformFromComponentSpace(AnimPhysSimSpaceType SimSpace, FComponentSpacePoseContext& Output, const FTransform& InComponentTransform) const;` — Given a transform in component space, convert it to the current sim space
- L620 _private prototype_ `FVector TransformWorldVectorToSimSpace(FComponentSpacePoseContext& Output, const FVector& InVec) const;` — Given a world-space vector, convert it into the current simulation space
- L622 _private prototype_ `FVector TransformWorldVectorToSimSpaceScaled(FComponentSpacePoseContext& Output, const FVector& InVec) const;`
- L624 _private prototype_ `void ConvertSimulationSpace(FComponentSpacePoseContext& Output, AnimPhysSimSpaceType From, AnimPhysSimSpaceType To) const;`
- L626 _private prototype_ `void CalculateSimulationSpaceMotion(AnimPhysSimSpaceType Space, FAnimPhysSimSpaceSettings Settings, FComponentSpacePoseContext& Output, const float Dt, FVector& SpaceAngularVel, FVector& SpaceAngularAcc);`
- L629 _private prototype_ `void UpdateBodyScaling(const int32 BodyIndex, float Scale) const;`
- L632 _private member_ `static const float MaxTimeDebt;` — Maximum time to consider when accumulating time debt to avoid spiraling
- L635 _private member_ `float NextTimeStep;` — Cached timestep from the update phase (needed in evaluate phase)
- L638 _private member_ `float TimeDebt;` — Current amount of time debt
- L641 _private member_ `float AnimPhysicsMinDeltaTime;` — Cached physics settings. We cache these on initialise to avoid the cost of accessing UPhysicsSettings a lot each frame
- L642 _private member_ `float MaxPhysicsDeltaTime;`
- L643 _private member_ `float MaxSubstepDeltaTime;`
- L644 _private member_ `int32 MaxSubsteps;`
- L648 _private member_ `TArray<FAnimPhysLinkedBody> Bodies;` — Active body list
- L652 _private member_ `TArray<FAnimPhysLinkedBody*> BodiesToReset;` — Pointers to bodies that need to be reset to their bound bone. This happens on LOD change so we don't make the simulation unstable
- L655 _private member_ `TArray<FAnimPhysRigidBody*> BaseBodyPtrs;` — Pointers back to the base bodies to pass to the simulation
- L658 _private member_ `TArray<FAnimPhysLinearLimit> LinearLimits;` — List of current linear limits built for the current frame
- L661 _private member_ `TArray<FAnimPhysAngularLimit> AngularLimits;` — List of current angular limits built for the current frame
- L664 _private member_ `TArray<FAnimPhysSpring> Springs;` — List of spring force generators created for this frame
- L667 _private member_ `TArray<FVector> PhysicsBodyJointOffsets;` — Position of the physics object relative to the transform if its bound bone.
- L670 _private member_ `TArray<FAnimConstraintOffsetPair> ConstraintOffsets;` — A pair of positions (relative to their associated physics bodies) for each pair of bodies in a chain. These positions should be driven to match each other in sim space by the physics contstraints - See UpdateLimits() fns.
- L674 _private member_ `TArray<int32> ActiveBoneIndices;` — Depending on the LOD we might not be running all of the bound bodies (for chains) this tracks the active bodies.
- L677 _private member_ `FVector SimSpaceGravityDirection;` — Gravity direction in sim space
- L680 _private member_ `FVector PreviousComponentLinearVelocity;` — Previous linear velocity to resolve world accelerations when not using world space simulation
- L683 _private member_ `FVector PreviousSimSpaceAngularVelocity;` — Previous angular velocity to resolve world angular acceleration when not using world space simulation
- L686 _private member_ `uint8 bEnabled : 1;` — When true, physics simulation is enabled.
- L689 _private member_ `uint8 bShouldUpdateBodiesOnScaleChange : 1;` — When true, input bone transform scale has changed since the last physics evaluation. Will trigger an update of physics body scales in the next physics evaluation.
- L695 _private prototype_ `void DrawBodies(FComponentSpacePoseContext& InContext, const TArray<FAnimPhysRigidBody*>& InBodies);`
- L697 _private member_ `int32 FilteredBoneIndex;`
- L700 _public prototype_ `static bool IsAnimDynamicsSystemEnabledFor(int32 InLOD);`

#### Free symbols / members of external scopes

- L20 _externvar_ `extern TAutoConsoleVariable<int32> CVarEnableDynamics;`
- L21 _externvar_ `extern TAutoConsoleVariable<int32> CVarLODThreshold;`
- L22 _externvar_ `extern TAutoConsoleVariable<int32> CVarEnableWind;`
- L26 _externvar_ `extern TAutoConsoleVariable<int32> CVarShowDebug;`
- L27 _externvar_ `extern TAutoConsoleVariable<FString> CVarDebugBone;`
- L31 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Anim Dynamics Overall"), STAT_AnimDynamicsOverall, STATGROUP_Physics, A`
- L32 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Anim Dynamics Wind Data Update"), STAT_AnimDynamicsWindData, STATGROUP_P`
- L33 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Anim Dynamics Bone Evaluation"), STAT_AnimDynamicsBoneEval, STATGROUP_Ph`
- L34 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Anim Dynamics Sub-Steps"), STAT_AnimDynamicsSubSteps, STATGROUP_Physics,`
- L302 _enumerator_ `template <> struct TIsPODType<FAnimPhysSimSpaceSettings> { enum { Value = true }; }; USTRUCT(BlueprintType) struct FAnimPhysSimSpaceSettings { GENERATED_BODY() ANIMGRAPHRUNTIME_API FAnimPhysSimSpaceSettings();` (scope `TIsPODType::__anonbbd878480103`) — Settings for the system which passes rotational motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ApplyLimits.h` (Public)


#### struct `FAngularRangeLimit`  
`struct FAngularRangeLimit`  
_L15-32_
- reflection: `USTRUCT()`
- L19 _public function_ `FAngularRangeLimit() : LimitMin(-180, -180, -180) , LimitMax(+180, +180, +180)`
- L25 _public member_ `FVector LimitMin;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`
- L28 _public member_ `FVector LimitMax;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`
- L31 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = Angular)`

#### struct `FAnimNode_ApplyLimits`  
`struct FAnimNode_ApplyLimits : public FAnimNode_SkeletalControlBase`  
_L35-64_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L39 _public prototype_ `FAnimNode_ApplyLimits();`
- L42 _public member_ `TArray<FAngularRangeLimit> AngularRangeLimits;` — `UPROPERTY(EditAnywhere, Category = Angular)`
- L45 _public member_ `TArray<FVector> AngularOffsets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Angular", meta = (PinHiddenByDefault))`
- L47 _public prototype_ `void RecalcLimits();`
- L50 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L51 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L52 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L56 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L57 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L62 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_BoneDrivenController.h` (Public)


#### enum `EDrivenBoneModificationMode`  
`enum class EDrivenBoneModificationMode : uint8`  
_L21-31_
- reflection: `UENUM()`
- desc: The type of modification to make to the destination component(s)
- L24 _public enumerator_ `AddToInput` — Add the driven value to the input component value(s)
- L27 _public enumerator_ `ReplaceComponent` — Replace the input component value(s) with the driven value
- L30 _public enumerator_ `AddToRefPose` — Add the driven value to the reference pose value

#### enum `EDrivenDestinationMode`  
`enum class EDrivenDestinationMode : uint8`  
_L35-40_
- reflection: `UENUM()`
- desc: Type of destination value to drive
- L37 _public enumerator_ `Bone`
- L38 _public enumerator_ `MorphTarget`
- L39 _public enumerator_ `MaterialParameter`

#### struct `FAnimNode_BoneDrivenController`  
`struct FAnimNode_BoneDrivenController : public FAnimNode_SkeletalControlBase`  
_L46-175_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: This is the runtime version of a bone driven controller, which maps part of the state from one bone to another (e.g., 2 * source.x -> target.z)
- L52 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category="Source (driver)")` — Bone to use as controller input
- L56 _public member_ `TObjectPtr<UCurveFloat> DrivingCurve;` — `UPROPERTY(EditAnywhere, Category=Mapping)` — Curve used to map from the source attribute to the driven attributes if present (otherwise the Multiplier will be used)
- L60 _public member_ `float Multiplier;` — `UPROPERTY(EditAnywhere, Category=Mapping)` — Multiplier to apply to the input value (Note: Ignored when a curve is used)
- L65 _public member_ `double RangeMin;` — `UPROPERTY(EditAnywhere, Category=Mapping, meta=(EditCondition=bUseRange, DisplayName="Source Range Min"))` — Minimum limit of the input value (mapped to RemappedMin, only used when limiting the source range) If this is rotation, the unit is radian
- L70 _public member_ `double RangeMax;` — `UPROPERTY(EditAnywhere, Category=Mapping, meta=(EditCondition=bUseRange, DisplayName="Source Range Max"))` — Maximum limit of the input value (mapped to RemappedMax, only used when limiting the source range) If this is rotation, the unit is radian
- L75 _public member_ `double RemappedMin;` — `UPROPERTY(EditAnywhere, Category=Mapping, meta=(EditCondition=bUseRange, DisplayName="Mapped Range Min"))` — Minimum value to apply to the destination (remapped from the input range) If this is rotation, the unit is radian
- L80 _public member_ `double RemappedMax;` — `UPROPERTY(EditAnywhere, Category = Mapping, meta = (EditCondition = bUseRange, DisplayName="Mapped Range Max"))` — Maximum value to apply to the destination (remapped from the input range) If this is rotation, the unit is radian
- L84 _public member_ `FName ParameterName;` — `UPROPERTY(EditAnywhere, Category = "Destination (driven)")` — Name of Morph Target to drive using the source attribute
- L88 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)")` — Bone to drive using controller input
- L93 _private member_ `TEnumAsByte<EComponentType::Type> TargetComponent_DEPRECATED;` — `UPROPERTY()`
- L99 _public member_ `EDrivenDestinationMode DestinationMode;` — `UPROPERTY(EditAnywhere, Category = "Destination (driven)")` — Type of destination to drive, currently either bone or morph target
- L103 _public member_ `EDrivenBoneModificationMode ModificationMode;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)")` — The type of modification to make to the destination component(s)
- L107 _public member_ `TEnumAsByte<EComponentType::Type> SourceComponent;` — `UPROPERTY(EditAnywhere, Category="Source (driver)")` — Transform component to use as input
- L111 _public member_ `uint8 bUseRange : 1;` — `UPROPERTY(EditAnywhere, Category=Mapping, meta=(DisplayName="Remap Source"))` — Whether or not to clamp the driver value and remap it before scaling it
- L115 _public member_ `uint8 bAffectTargetTranslationX : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="X"))` — Affect the X component of translation on the target bone
- L119 _public member_ `uint8 bAffectTargetTranslationY : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="Y"))` — Affect the Y component of translation on the target bone
- L123 _public member_ `uint8 bAffectTargetTranslationZ : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="Z"))` — Affect the Z component of translation on the target bone
- L127 _public member_ `uint8 bAffectTargetRotationX : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="X"))` — Affect the X component of rotation on the target bone
- L131 _public member_ `uint8 bAffectTargetRotationY : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="Y"))` — Affect the Y component of rotation on the target bone
- L135 _public member_ `uint8 bAffectTargetRotationZ : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="Z"))` — Affect the Z component of rotation on the target bone
- L139 _public member_ `uint8 bAffectTargetScaleX : 1;` — `UPROPERTY(EditAnywhere, Category = "Destination (driven)", meta=(DisplayName="X"))` — Affect the X component of scale on the target bone
- L143 _public member_ `uint8 bAffectTargetScaleY : 1;` — `UPROPERTY(EditAnywhere, Category = "Destination (driven)", meta=(DisplayName="Y"))` — Affect the Y component of scale on the target bone
- L147 _public member_ `uint8 bAffectTargetScaleZ : 1;` — `UPROPERTY(EditAnywhere, Category="Destination (driven)", meta=(DisplayName="Z"))` — Affect the Z component of scale on the target bone
- L150 _public prototype_ `FAnimNode_BoneDrivenController();`
- L153 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L157 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L158 _public prototype_ `virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context);`
- L159 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L164 _public prototype_ `void ConvertTargetComponentToBits();` — Upgrade a node from the output enum to the output bits (change made in FAnimationCustomVersion::BoneDrivenControllerMatchingMaya)
- L170 _protected prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase protected interface
- L173 _protected prototype_ `const double ExtractSourceValue(const FTransform& InCurrentBoneTransform, const FTransform& InRefPoseBoneTransform);` — Extracts the value used to drive the target bone or parameter

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_CCDIK.h` (Public)


#### struct `FAnimNode_CCDIK`  
`struct FAnimNode_CCDIK : public FAnimNode_SkeletalControlBase`  
_L14-89_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Controller which implements the CCDIK IK approximation algorithm
- L20 _public member_ `FVector EffectorLocation;` — `UPROPERTY(EditAnywhere, Category = Effector, meta = (PinShownByDefault))` — Coordinates for target location of tip bone - if EffectorLocationSpace is bone, this is the offset from Target Bone to use as target location
- L28 _public member_ `FBoneSocketTarget EffectorTarget;` — `UPROPERTY(EditAnywhere, Category = Effector)` — If EffectorTransformSpace is a bone, this is the bone to use.
- L32 _public member_ `FBoneReference TipBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Name of tip bone
- L36 _public member_ `FBoneReference RootBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Name of the root bone
- L40 _public member_ `float Precision;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Tolerance for final tip location delta from EffectorLocation
- L44 _public member_ `int32 MaxIterations;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Maximum number of iterations allowed, to control performance.
- L48 _public member_ `bool bStartFromTail;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Toggle drawing of axes to debug joint rotation
- L52 _public member_ `bool bEnableRotationLimit;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Tolerance for final tip location delta from EffectorLocation
- L57 _private member_ `TArray<float> RotationLimitPerJoints;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = Solver)` — symmetry rotation limit per joint. Index 0 matches with root bone and last index matches with tip bone.
- L60 _public prototype_ `FAnimNode_CCDIK();`
- L63 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L67 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L68 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L73 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L77 _private prototype_ `FVector GetCurrentLocation(FCSPose<FCompactPose>& MeshBases, const FCompactPoseBoneIndex& BoneIndex);` — Convenience function to get current (pre-translation iteration) component space location of bone by bone index
- L79 _private prototype_ `static FTransform GetTargetTransform(const FTransform& InComponentTransform, FCSPose<FCompactPose>& MeshBases, FBoneSocketTarget& InTarget, EBoneControlSpace Space, const FVector& InOffset);`
- L84 _public member_ `TArray<FVector> DebugLines;`
- L87 _public prototype_ `void ResizeRotationLimitPerJoints(int32 NewSize);` — resize rotation limit array based on set up

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_Constraint.h` (Public)


#### enum `EConstraintOffsetOption`  
`enum class EConstraintOffsetOption : uint8`  
_L14-18_
- reflection: `UENUM()`
- desc: Enum value to describe how you'd like to maintain offset
- L16 _public enumerator_ `None` — no offset
- L17 _public enumerator_ `Offset_RefPose` — offset is based on reference pose

#### struct `FConstraint`  
`struct FConstraint`  
_L26-70_
- reflection: `USTRUCT()`
- desc: Constraint Set up
- L32 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category = FConstraint)` — Target Bone this is constraint to
- L42 _public member_ `EConstraintOffsetOption OffsetOption;` — `UPROPERTY(EditAnywhere, Category = FConstraint)` — Maintain offset based on refpose or not. None - no offset Offset_RefPose - offset is created based on reference pose In the future, we'd like to support custom offset, not just based on ref pose
- L46 _public member_ `ETransformConstraintType TransformType;` — `UPROPERTY(EditAnywhere, Category = FConstraint)` — What transform type is constraint to - Translation, Rotation, Scale OR Parent. Parent overrides all component
- L50 _public member_ `FFilterOptionPerAxis PerAxis;` — `UPROPERTY(EditAnywhere, Category = FConstraint)` — Per axis filter options - applied in their local space not in world space
- L53 _public member_ `int32 ConstraintDataIndex;` — transient constraint data index
- L55 _public function_ `void Initialize(const FBoneContainer& RequiredBones)`
- L60 _public function_ `bool IsValidToEvaluate(const FBoneContainer& RequiredBones) const`
- L65 _public function_ `FConstraint() : OffsetOption(EConstraintOffsetOption::Offset_RefPose) , TransformType(ETransformConstraintType::Translation) , ConstraintDataIndex(INDEX_NONE)`

#### struct `FAnimNode_Constraint`  
`struct FAnimNode_Constraint : public FAnimNode_SkeletalControlBase`  
_L75-119_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Constraint node to parent or world transform for rotation/translation
- L81 _public member_ `FBoneReference BoneToModify;` — `UPROPERTY(EditAnywhere, Category = SkeletalControl)` — Name of bone to control. This is the main bone chain to modify from.
- L85 _public member_ `TArray<FConstraint> ConstraintSetup;` — `UPROPERTY(EditAnywhere, Category = Constraints)` — List of constraints
- L89 _public member_ `TArray<float> ConstraintWeights;` — `UPROPERTY(EditAnywhere, editfixedsize, Category = Runtime, meta = (PinShownByDefault))` — Weight data - post edit syncs up to ConstraintSetups
- L91 _public prototype_ `FAnimNode_Constraint();`
- L94 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L98 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L99 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L103 _public prototype_ `void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp) const;`
- L108 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L111 _private member_ `TArray<FConstraintData> ConstraintData;`
- L115 _private member_ `FTransform CachedOriginalTransform;` — Debug draw cached data
- L116 _private member_ `FTransform CachedConstrainedTransform;`
- L117 _private member_ `TArray<FTransform> CachedTargetTransforms;`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_CopyBone.h` (Public)


#### struct `FAnimNode_CopyBone`  
`struct FAnimNode_CopyBone : public FAnimNode_SkeletalControlBase`  
_L19-62_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L25 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Source Bone Name to get transform from
- L29 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category=Copy)` — Name of bone to control. This is the main bone chain to modify from.
- L33 _public member_ `bool bCopyTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta=(PinShownByDefault))` — If Translation should be copied
- L37 _public member_ `bool bCopyRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta=(PinShownByDefault))` — If Rotation should be copied
- L41 _public member_ `bool bCopyScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Copy, meta=(PinShownByDefault))` — If Scale should be copied
- L45 _public member_ `TEnumAsByte<EBoneControlSpace> ControlSpace;` — `UPROPERTY(EditAnywhere, Category = Copy)` — Space to convert transforms into prior to copying components
- L47 _public prototype_ `FAnimNode_CopyBone();`
- L50 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L54 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L55 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L60 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_CopyBoneDelta.h` (Public)


#### enum `CopyBoneDeltaMode`  
`enum class CopyBoneDeltaMode : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `Accumulate`
- L18 _public enumerator_ `Copy`

#### struct `FAnimNode_CopyBoneDelta`  
`struct FAnimNode_CopyBoneDelta : public FAnimNode_SkeletalControlBase`  
_L27-73_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L32 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L35 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L38 _public member_ `bool bCopyTranslation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))`
- L41 _public member_ `bool bCopyRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))`
- L44 _public member_ `bool bCopyScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))`
- L47 _public member_ `CopyBoneDeltaMode CopyMode;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L50 _public member_ `float TranslationMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L53 _public member_ `float RotationMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L56 _public member_ `float ScaleMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinHiddenByDefault))`
- L58 _public prototype_ `FAnimNode_CopyBoneDelta();`
- L61 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L65 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L66 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L71 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_Fabrik.h` (Public)


#### struct `FAnimNode_Fabrik`  
`struct FAnimNode_Fabrik : public FAnimNode_SkeletalControlBase`  
_L21-93_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L27 _public member_ `FTransform EffectorTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EndEffector, meta = (PinShownByDefault))` — Coordinates for target location of tip bone - if EffectorLocationSpace is bone, this is the offset from Target Bone to use as target location
- L31 _public member_ `FBoneSocketTarget EffectorTarget;` — `UPROPERTY(EditAnywhere, Category = EndEffector)` — If EffectorTransformSpace is a bone, this is the bone to use.
- L35 _public member_ `FBoneReference TipBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Name of tip bone
- L39 _public member_ `FBoneReference RootBone;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Name of the root bone
- L43 _public member_ `float Precision;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Tolerance for final tip location delta from EffectorLocation
- L47 _public member_ `int32 MaxIterations;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Maximum number of iterations allowed, to control performance.
- L59 _public member_ `bool bEnableDebugDraw;` — `UPROPERTY(EditAnywhere, Category = Solver)` — Toggle drawing of axes to debug joint rotation
- L63 _public member_ `FBoneReference EffectorTransformBone_DEPRECATED;` — `UPROPERTY()` — If EffectorTransformSpace is a bone, this is the bone to use.
- L67 _public prototype_ `FAnimNode_Fabrik();`
- L70 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L71 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L75 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L76 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L79 _public prototype_ `virtual void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* PreviewSkelMeshComp) const;`
- L83 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L87 _private prototype_ `FVector GetCurrentLocation(FCSPose<FCompactPose>& MeshBases, const FCompactPoseBoneIndex& BoneIndex);` — Convenience function to get current (pre-translation iteration) component space location of bone by bone index
- L88 _private prototype_ `static FTransform GetTargetTransform(const FTransform& InComponentTransform, FCSPose<FCompactPose>& MeshBases, FBoneSocketTarget& InTarget, EBoneControlSpace Space, const FTransform& InOffset);`
- L91 _private member_ `FTransform CachedEffectorCSTransform;` — Cached CS location when in editor for debug drawing

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_HandIKRetargeting.h` (Public)


#### struct `FAnimNode_HandIKRetargeting`  
`struct FAnimNode_HandIKRetargeting : public FAnimNode_SkeletalControlBase`  
_L22-69_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L28 _public member_ `FBoneReference RightHandFK;` — `UPROPERTY(EditAnywhere, Category = "HandIKRetargeting")` — Bone for Right Hand FK
- L32 _public member_ `FBoneReference LeftHandFK;` — `UPROPERTY(EditAnywhere, Category = "HandIKRetargeting")` — Bone for Left Hand FK
- L36 _public member_ `FBoneReference RightHandIK;` — `UPROPERTY(EditAnywhere, Category = "HandIKRetargeting")` — Bone for Right Hand IK
- L40 _public member_ `FBoneReference LeftHandIK;` — `UPROPERTY(EditAnywhere, Category = "HandIKRetargeting")` — Bone for Left Hand IK
- L44 _public member_ `TArray<FBoneReference> IKBonesToMove;` — `UPROPERTY(EditAnywhere, Category = "HandIKRetargeting")` — IK Bones to move.
- L48 _public member_ `FVector PerAxisAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandIKRetargeting", meta = (PinHiddenByDefault))` — Alpha values per axis to apply on the resulting retargeting translation
- L52 _public member_ `float HandFKWeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HandIKRetargeting", meta = (PinShownByDefault))` — Which hand to favor. 0.5 is equal weight for both, 1 = right hand, 0 = left hand.
- L54 _public prototype_ `FAnimNode_HandIKRetargeting();`
- L57 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L61 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L62 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L67 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_LegIK.h` (Public)


#### struct `FIKChainLink`  
`struct FIKChainLink`  
_L17-46_
- reflection: `USTRUCT()`
- L22 _public member_ `FVector Location;`
- L23 _public member_ `double Length;`
- L24 _public member_ `FVector LinkAxisZ;`
- L25 _public member_ `FVector RealBendDir;`
- L26 _public member_ `FVector BaseBendDir;`
- L27 _public member_ `FName BoneName;`
- L29 _public function_ `FIKChainLink() : Location(FVector::ZeroVector) , Length(0.0) , LinkAxisZ(FVector::ZeroVector) , RealBendDir(FVector::ZeroVector) , BaseBendDir(FVector::ZeroVector) , BoneName(NAME_None)`
- L38 _public function_ `FIKChainLink(FVector InLocation, double InLength) : Location(InLocation) , Length(InLength) , LinkAxisZ(FVector::ZeroVector) , RealBendDir(FVector::ZeroVector) , BaseBendDir(FVector::ZeroVector) , BoneName(NAME_None)`

#### struct `FIKChain`  
`struct FIKChain`  
_L49-100_
- reflection: `USTRUCT()`
- L54 _public member_ `TArray<FIKChainLink> Links;`
- L55 _public member_ `float MinRotationAngleRadians;`
- L58 _private member_ `FAnimInstanceProxy* MyAnimInstanceProxy;`
- L59 _private member_ `double TotalChainLength;`
- L60 _private member_ `int32 NumLinks;`
- L61 _private member_ `FVector HingeRotationAxis;`
- L62 _private member_ `bool bEnableRotationLimit;`
- L63 _private member_ `bool bInitialized;`
- L66 _public function_ `FIKChain() : MyAnimInstanceProxy(nullptr) , TotalChainLength(0.0) , NumLinks(INDEX_NONE) , HingeRotationAxis(FVector::ZeroVector) , bEnableRotationLimit(false) , bInitialized(false)`
- L75 _public prototype_ `void InitializeFromLegData(FAnimLegIKData& InLegData, FAnimInstanceProxy* InAnimInstanceProxy);`
- L76 _public prototype_ `void ReachTarget( const FVector& InTargetLocation, double InReachPrecision, int32 InMaxIterations, float SoftPercentLength, float SoftAlpha);`
- L82 _public prototype_ `void ApplyTwistOffset(const float InTwistOffsetDegrees);`
- L84 _public function_ `double GetMaximumReach() const`
- L90 _private prototype_ `void OrientAllLinksToDirection(const FVector& InDirection);`
- L91 _private prototype_ `void SolveTwoBoneIK(const FVector& InTargetLocation);`
- L92 _private prototype_ `void SolveFABRIK(const FVector& InTargetLocation, double InReachPrecision, int32 InMaxIterations);`
- L94 _private prototype_ `static void FABRIK_ForwardReach(const FVector& InTargetLocation, FIKChain& IKChain);`
- L95 _private prototype_ `static void FABRIK_BackwardReach(const FVector& InRootTargetLocation, FIKChain& IKChain);`
- L96 _private prototype_ `static void FABRIK_ApplyLinkConstraints_Forward(FIKChain& IKChain, int32 LinkIndex);`
- L97 _private prototype_ `static void FABRIK_ApplyLinkConstraints_Backward(FIKChain& IKChain, int32 LinkIndex);`
- L99 _private prototype_ `static void DrawDebugIKChain(const FIKChain& IKChain, const FColor& InColor);`

#### struct `FAnimLegIKDefinition`  
`struct FAnimLegIKDefinition`  
_L104-153_
- reflection: `USTRUCT()`
- desc: Per foot definitions
- L109 _public member_ `FBoneReference IKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L112 _public member_ `FBoneReference FKFootBone;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L115 _public member_ `int32 NumBonesInLimb;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L120 _public member_ `float MinRotationAngle;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Only used if bEnableRotationLimit is enabled. Prevents the leg from folding onto itself, and forces at least this angle between Parent and Child bone.
- L124 _public member_ `TEnumAsByte<EAxis::Type> FootBoneForwardAxis;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Forward Axis for Foot bone.
- L128 _public member_ `TEnumAsByte<EAxis::Type> HingeRotationAxis;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Hinge Bones Rotation Axis. This is essentially the plane normal for (hip - knee - foot).
- L132 _public member_ `bool bEnableRotationLimit;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — If enabled, we prevent the leg from bending backwards and enforce a min compression angle
- L136 _public member_ `bool bEnableKneeTwistCorrection;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Enable Knee Twist correction, by comparing Foot FK with Foot IK orientation.
- L142 _public member_ `FName TwistOffsetCurveName;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Name of the curve to use as the twist offset angle(in degrees). This is useful for injecting knee motion, while keeping the IK chain's goal/hand and root/hip locked in place. Reasonable values are usually between -+15 degrees, although this is depends on how far in/out the knee is in the original pose.
- L144 _public function_ `FAnimLegIKDefinition() : NumBonesInLimb(2) , MinRotationAngle(15.f) , FootBoneForwardAxis(EAxis::Y) , HingeRotationAxis(EAxis::None) , bEnableRotationLimit(false) , bEnableKneeTwistCorrection(true) , TwistOffsetCurveName(NAME_None)`

#### struct `FAnimLegIKData`  
`struct FAnimLegIKData`  
_L157-182_
- reflection: `USTRUCT()`
- desc: Runtime foot data after validation, we guarantee these bones to exist
- L162 _public member_ `FTransform IKFootTransform;`
- L163 _public member_ `FAnimLegIKDefinition* LegDefPtr;`
- L164 _public member_ `FCompactPoseBoneIndex IKFootBoneIndex;`
- L165 _public member_ `float TwistOffsetDegrees;`
- L166 _public member_ `int32 NumBones;`
- L167 _public member_ `TArray<FCompactPoseBoneIndex> FKLegBoneIndices;`
- L168 _public member_ `TArray<FTransform> FKLegBoneTransforms;`
- L170 _public member_ `FIKChain IKChain;`
- L173 _public prototype_ `void InitializeTransforms(FAnimInstanceProxy* MyAnimInstanceProxy, FCSPose<FCompactPose>& MeshBases);`
- L175 _public function_ `FAnimLegIKData() : IKFootTransform(FTransform::Identity) , LegDefPtr(nullptr) , IKFootBoneIndex(INDEX_NONE) , TwistOffsetDegrees(0.0f) , NumBones(INDEX_NONE)`

#### struct `FAnimNode_LegIK`  
`struct FAnimNode_LegIK : public FAnimNode_SkeletalControlBase`  
_L185-235_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- L189 _public prototype_ `FAnimNode_LegIK();`
- L193 _public member_ `float ReachPrecision;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Tolerance for reaching IK Target, in unreal units.
- L197 _public member_ `int32 MaxIterations;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Max Number of Iterations.
- L203 _public member_ `float SoftPercentLength;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault, UIMin = "0.01", UIMax = "1", ClampMin = "0.01", ClampMax = "1"))` — Default is 1.0 (off). Range is 0.1 to 1.0. When set to a value less than 1, will "softly" approach full extension starting when the effector distance from the root of the chain is greater than this percent length of the bone chain. Typical values are around 0.97. This is useful for preventing the knee from "popping" when approaching full extension.
- L207 _public member_ `float SoftAlpha;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (PinHiddenByDefault, UIMin = "0.0", UIMax = "1", ClampMin = "0.0", ClampMax = "1"))` — Default is 1.0 (full). Range is 0 to 1. Blends the effect of the "softness" on/off.
- L210 _public member_ `TArray<FAnimLegIKDefinition> LegsDefinition;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L212 _public member_ `TArray<FAnimLegIKData> LegsData;`
- L214 _public member_ `FAnimInstanceProxy* MyAnimInstanceProxy;`
- L218 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L222 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L223 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L224 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L227 _public prototype_ `bool OrientLegTowardsIK(FAnimLegIKData& InLegData);`
- L228 _public prototype_ `bool DoLegReachIK(FAnimLegIKData& InLegData);`
- L229 _public prototype_ `bool AdjustKneeTwist(FAnimLegIKData& InLegData);`
- L233 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_LookAt.h` (Public)


#### enum `EInterpolationBlend::Type`  
`enum Type : int`  
_L22-32_
- L24 _public enumerator_ `Linear`
- L25 _public enumerator_ `Cubic`
- L26 _public enumerator_ `Sinusoidal`
- L27 _public enumerator_ `EaseInOutExponent2`
- L28 _public enumerator_ `EaseInOutExponent3`
- L29 _public enumerator_ `EaseInOutExponent4`
- L30 _public enumerator_ `EaseInOutExponent5`
- L31 _public enumerator_ `MAX`

#### struct `FAnimNode_LookAt`  
`struct FAnimNode_LookAt : public FAnimNode_SkeletalControlBase`  
_L39-155_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Simple controller that make a bone to look at the point or another bone
- L45 _public member_ `FBoneReference BoneToModify;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Name of bone to control. This is the main bone chain to modify from.
- L49 _public member_ `FBoneSocketTarget LookAtTarget;` — `UPROPERTY(EditAnywhere, Category = Target)` — Target socket to look at. Used if LookAtBone is empty. - You can use  LookAtLocation if you need offset from this point. That location will be used in their local space.
- L53 _public member_ `FVector LookAtLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target, meta = (PinHiddenByDefault))` — Target Offset. It's in world space if LookAtBone is empty or it is based on LookAtBone or LookAtSocket in their local space
- L56 _public member_ `FAxis LookAt_Axis;` — `UPROPERTY(EditAnywhere, Category = SkeletalControl)`
- L60 _public member_ `bool bUseLookUpAxis;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Whether or not to use Look up axis
- L63 _public member_ `TEnumAsByte<EInterpolationBlend::Type> InterpolationType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalControl, meta=(PinHiddenByDefault))`
- L66 _public member_ `FAxis LookUp_Axis;` — `UPROPERTY(EditAnywhere, Category = SkeletalControl)`
- L70 _public member_ `float LookAtClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalControl, meta=(PinHiddenByDefault))` — Look at Clamp value in degrees - if your look at axis is Z, only X, Y degree of clamp will be used
- L73 _public member_ `float InterpolationTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalControl, meta=(PinHiddenByDefault))`
- L76 _public member_ `float InterpolationTriggerThreashold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SkeletalControl, meta=(PinHiddenByDefault))`
- L81 _public member_ `FBoneReference LookAtBone_DEPRECATED;` — `UPROPERTY()` — Target Bone to look at - You can use  LookAtLocation if you need offset from this point. That location will be used in their local space.
- L84 _public member_ `FName LookAtSocket_DEPRECATED;` — `UPROPERTY()`
- L88 _public member_ `TEnumAsByte<EAxisOption::Type> LookAtAxis_DEPRECATED;` — `UPROPERTY()` — Look at axis, which axis to align to look at point
- L92 _public member_ `FVector CustomLookAtAxis_DEPRECATED;` — `UPROPERTY()` — Custom look up axis in local space. Only used if LookAtAxis==EAxisOption::Custom
- L96 _public member_ `TEnumAsByte<EAxisOption::Type> LookUpAxis_DEPRECATED;` — `UPROPERTY()` — Look up axis in local space
- L100 _public member_ `FVector CustomLookUpAxis_DEPRECATED;` — `UPROPERTY()` — Custom look up axis in local space. Only used if LookUpAxis==EAxisOption::Custom
- L104 _public prototype_ `FAnimNode_LookAt();` — in the future, it would be nice to have more options, -i.e. lag, interpolation speed
- L107 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L108 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L109 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L113 _public prototype_ `virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L114 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L115 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L118 _public function_ `FVector GetCachedTargetLocation() const`
- L121 _public prototype_ `void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp) const;`
- L126 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L130 _private prototype_ `static float AlphaToBlendType(float InAlpha, EInterpolationBlend::Type BlendType);` — Turn a linear interpolated alpha into the corresponding AlphaBlendType
- L133 _private member_ `FVector CurrentLookAtLocation;` — Debug transient data
- L136 _private member_ `FVector CurrentTargetLocation;` — Current Target Location
- L137 _private member_ `FVector PreviousTargetLocation;`
- L140 _private member_ `float AccumulatedInterpoolationTime;` — Current Alpha
- L145 _private member_ `FTransform CachedOriginalTransform;` — Debug draw cached data
- L146 _private member_ `FTransform CachedLookAtTransform;`
- L147 _private member_ `FTransform CachedTargetCoordinate;`
- L148 _private member_ `FVector CachedPreviousTargetLocation;`
- L149 _private member_ `FVector CachedCurrentLookAtLocation;`
- L151 _private member_ `FVector CachedCurrentTargetLocation;`
- L154 _protected prototype_ `virtual void ModifyPoseFromDeltaRotation(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms, FTransform& InOutBoneToModifyTransform, const FQuat& DeltaRotation);`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace EInterpolationBlend`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ModifyBone.h` (Public)


#### enum `EBoneModificationMode`  
`enum EBoneModificationMode : int`  
_L15-25_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `BMM_Ignore UMETA(DisplayName = "Ignore")` — The modifier ignores this channel (keeps the existing bone translation, rotation, or scale).
- L21 _public enumerator_ `BMM_Replace UMETA(DisplayName = "Replace Existing")` — The modifier replaces the existing translation, rotation, or scale.
- L24 _public enumerator_ `BMM_Additive UMETA(DisplayName = "Add to Existing")` — The modifier adds to the existing translation, rotation, or scale.

#### struct `FAnimNode_ModifyBone`  
`struct FAnimNode_ModifyBone : public FAnimNode_SkeletalControlBase`  
_L31-90_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Simple controller that replaces or adds to the translation/rotation of a single bone.
- L37 _public member_ `FBoneReference BoneToModify;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Name of bone to control. This is the main bone chain to modify from.
- L41 _public member_ `FVector Translation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Translation, meta=(PinShownByDefault))` — New translation of bone to apply.
- L45 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Rotation, meta=(PinShownByDefault))` — New rotation of bone to apply.
- L49 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Scale, meta=(PinShownByDefault))` — New Scale of bone to apply. This is only worldspace.
- L53 _public member_ `TEnumAsByte<EBoneModificationMode> TranslationMode;` — `UPROPERTY(EditAnywhere, Category=Translation)` — Whether and how to modify the translation of this bone.
- L57 _public member_ `TEnumAsByte<EBoneModificationMode> RotationMode;` — `UPROPERTY(EditAnywhere, Category=Rotation)` — Whether and how to modify the translation of this bone.
- L61 _public member_ `TEnumAsByte<EBoneModificationMode> ScaleMode;` — `UPROPERTY(EditAnywhere, Category=Scale)` — Whether and how to modify the translation of this bone.
- L75 _public prototype_ `FAnimNode_ModifyBone();`
- L78 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L82 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L83 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L88 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ObserveBone.h` (Public)


#### struct `FAnimNode_ObserveBone`  
`struct FAnimNode_ObserveBone : public FAnimNode_SkeletalControlBase`  
_L18-62_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Debugging node that displays the current value of a bone in a specific space.
- L24 _public member_ `FBoneReference BoneToObserve;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Name of bone to observe.
- L28 _public member_ `TEnumAsByte<EBoneControlSpace> DisplaySpace;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Reference frame to display the bone transform in.
- L32 _public member_ `bool bRelativeToRefPose;` — `UPROPERTY(EditAnywhere, Category=SkeletalControl)` — Show the difference from the reference pose?
- L36 _public member_ `FVector Translation;` — `UPROPERTY()` — Translation of the bone being observed.
- L40 _public member_ `FRotator Rotation;` — `UPROPERTY()` — Rotation of the bone being observed.
- L44 _public member_ `FVector Scale;` — `UPROPERTY()` — Scale of the bone being observed.
- L47 _public prototype_ `FAnimNode_ObserveBone();`
- L50 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L54 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L55 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L60 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ResetRoot.h` (Public)


#### struct `FAnimNode_ResetRoot`  
`struct FAnimNode_ResetRoot : public FAnimNode_SkeletalControlBase`  
_L13-36_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L17 _public prototype_ `FAnimNode_ResetRoot();`
- L19 _public member_ `TArray<FCompactPoseBoneIndex> RootChildren;`
- L22 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L23 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L24 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L28 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L29 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L34 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_RigidBody.h` (Public)


#### enum `ESimulationSpace`  
`enum class ESimulationSpace : uint8`  
_L24-32_
- reflection: `UENUM()`
- desc: Determines in what space the simulation should run
- L27 _public enumerator_ `ComponentSpace` — Simulate in component space. Moving the entire skeletal mesh will have no affect on velocities
- L29 _public enumerator_ `WorldSpace` — Simulate in world space. Moving the skeletal mesh will generate velocity changes
- L31 _public enumerator_ `BaseBoneSpace` — Simulate in another bone space. Moving the entire skeletal mesh and individually modifying the base bone will have no affect on velocities

#### enum `ESimulationTiming`  
`enum class ESimulationTiming : uint8`  
_L36-44_
- reflection: `UENUM()`
- desc: Determines behaviour regarding deferral of simulation tasks.
- L39 _public enumerator_ `Default` — Use the default project setting as defined by p.RigidBodyNode.DeferredSimulationDefault.
- L41 _public enumerator_ `Synchronous` — Always run the simulation to completion during animation evaluation.
- L43 _public enumerator_ `Deferred` — Always run the simulation in the background and retrieve the result on the next animation evaluation.

#### enum `TIsPODType::(anonymous)`  
`template <> struct TIsPODType<FSimSpaceSettings>`  
_L51-51_
- desc: Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.

#### struct `TIsPODType`  
`template <> struct TIsPODType<FSimSpaceSettings>`  
_L51-51_
- desc: Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.

#### struct `FSimSpaceSettings`  
`struct FSimSpaceSettings`  
_L54-137_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public prototype_ `FSimSpaceSettings();`
- L62 _public prototype_ `~FSimSpaceSettings() = default;` — Disable deprecation errors by providing defaults wrapped with pragma disable
- L63 _public prototype_ `FSimSpaceSettings(FSimSpaceSettings const&) = default;`
- L64 _public prototype_ `FSimSpaceSettings& operator=(const FSimSpaceSettings &) = default;`
- L71 _public member_ `float WorldAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))` — Global multipler on the effects of simulation space movement. Must be in range [0, 1]. If WorldAlpha = 0.0, the system is disabled and the simulation will be fully local (i.e., world-space actor movement and rotation does not affect the simulation). When WorldAlpha = 1.0 the simulation effectively acts as a world-space sim, but with the ability to apply limits using the other parameters.
- L77 _public member_ `float VelocityScaleZ;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — Multiplier on the Z-component of velocity and acceleration that is passed to the simulation. Usually from 0.0 to 1.0 to reduce the effects of jumping and crouching on the simulation, but it can be higher than 1.0 if you need to exaggerate this motion for some reason. Should probably have been called "WorldAlphaScaleZ".
- L85 _public member_ `float DampingAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A muliplier to control how much of the simulation space movement is used to calculate the drag forces from Linear/Angular Damping in the Physics Asset. When DampingAlpha=1.0, Damping drag forces are equivalent to a world-space simulation. This is similar to air resistance. When DampingAlpha=0.0, Damping drag forces depend only on local-space body velocity and not on the simulation space velocity. It can be useful to set this to zero so that the Linear/Angular Damping settings on the BodyInstances do not contribute to air resistance. Air resistance can be re-added in a controlled way using the ExternalLinearDrag setting below.
- L91 _public member_ `float MaxLinearVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space velocity that is passed to the simulation. Units are cm/s. The default value effectively means "unlimited". It is not usually required to change this but you would reduce this to limit the effects of drag on the bodies in the simulation (if you have bodies that have LinearDrag set to non-zero in the physics asset). Expected values in this case would be somewhat less than the usual velocities of your object which is commonly a few hundred for a character.
- L97 _public member_ `float MaxAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space angular velocity that is passed to the simulation. Units are radian/s, so a value of about 6.0 is one rotation per second. The default value effectively means "unlimited". You would reduce this (and MaxAngularAcceleration) to limit how much bodies "fly out" when the actor spins on the spot. This is especially useful if you have characters than can rotate very quickly and you would probably want values around or less than 10 in this case.
- L103 _public member_ `float MaxLinearAcceleration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space acceleration that is passed to the simulation. Units are cm/s/s. The default value effectively means "unlimited". This property is used to stop the bodies of the simulation flying out when suddenly changing linear speed. It is useful when you have characters than can changes from stationary to running very quickly such as in an FPS. A common value for a character might be in the few hundreds.
- L109 _public member_ `float MaxAngularAcceleration;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (ClampMin = "0.0"))` — A clamp on the effective world-space angular accleration that is passed to the simulation. Units are radian/s/s. The default value effectively means "unlimited". This has a similar effect to MaxAngularVelocity, except that it is related to the flying out of bodies when the rotation speed suddenly changes. Typical limist for a character might be around 100.
- L113 _public member_ `float ExternalLinearDrag_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "ExternalLinearDrag is deprecated. Please use ExternalLinearDragV instead."))`
- L122 _public member_ `FVector ExternalLinearDragV;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Additional linear drag applied to each body based on total body velocity. This is in addition to per-body linear damping in the physics asset (but see DampingAlpha to control that). (NOTE: The "V" suffix is to differentiate from the deprecated float property of the same name. It means "Vector" and not "Velocity"). NOTE: ExternalLinearDragV is in simulation space, so if the RB AnimNode is set to Bone Space the ExternalLinearDragV.Z will be the drag in the Up direction of the selected bone.
- L128 _public member_ `FVector ExternalLinearVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Additional velocity that is added to the component velocity so the simulation acts as if the actor is moving at speed, even when stationary. Vector is in world space. Units are cm/s. Could be used for a wind effects etc. Typical values are similar to the velocity of the object or effect, and usually around or less than 1000 for characters/wind.
- L134 _public member_ `FVector ExternalAngularVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Additional angular velocity that is added to the component angular velocity. This can be used to make the simulation act as if the actor is rotating even when it is not. E.g., to apply physics to a character on a podium as the camera rotates around it, to emulate the podium itself rotating. Vector is in world space. Units are rad/s.
- L136 _public prototype_ `void PostSerialize(const FArchive& Ar);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSimSpaceSettings> : public TStructOpsTypeTraitsBase2<FSimSpaceSettings>`  
_L141-147_
- inherits: `TStructOpsTypeTraitsBase2<FSimSpaceSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L144-146_

#### struct `FAnimNode_RigidBody`  
`struct FAnimNode_RigidBody : public FAnimNode_SkeletalControlBase`  
_L155-586_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: Controller that simulates physics based on the physics asset of the skeletal mesh component
- L159 _public prototype_ `FAnimNode_RigidBody();`
- L160 _public prototype_ `~FAnimNode_RigidBody();`
- L163 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L164 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L168 _public prototype_ `virtual void UpdateComponentPose_AnyThread(const FAnimationUpdateContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L169 _public prototype_ `virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output) override;`
- L170 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L171 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L172 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L173 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L174 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L175 _public function_ `virtual bool HasPreUpdate() const override`
- L176 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L177 _public prototype_ `virtual bool NeedsDynamicReset() const override;`
- L178 _public prototype_ `virtual void ResetDynamics(ETeleportType InTeleportType) override;`
- L179 _public prototype_ `virtual int32 GetLODThreshold() const override;`
- L182 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None);`
- L185 _public function_ `virtual ImmediatePhysics::FSimulation* GetSimulation()` — TEMP: Exposed for use in PhAt as a quick way to get drag handles working with Chaos
- L191 _public prototype_ `void SetOverridePhysicsAsset(UPhysicsAsset* PhysicsAsset);` — Set the override physics asset. This will automatically trigger a physics re-init in case the override physics asset changes. Users can get access to this in the Animation Blueprint via the Animation Node Functions.
- L193 _public function_ `UPhysicsAsset* GetPhysicsAsset() const`
- L198 _public member_ `TObjectPtr<UPhysicsAsset> OverridePhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Physics asset to use. If empty use the skeletal mesh's default physics asset in case Default To Skeletal Mesh Physics Asset is set to True.
- L202 _public member_ `bool bDefaultToSkeletalMeshPhysicsAsset = true;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Use the skeletal mesh physics asset as default in case set to True. The Override Physics Asset will always have priority over this.
- L206 _public member_ `bool bUseDefaultAsSimulated = false;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Treat parts in the Physics Asset with PhysicsType Default as Simulated for RBAN.
- L210 _private prototype_ `UPhysicsAsset* GetPhysicsAssetToBeUsed(const UAnimInstance* InAnimInstance) const;` — Get the physics asset candidate to be used while respecting the bDefaultToSkeletalMeshPhysicsAsset and the priority to the override physics asset.
- L212 _private member_ `FTransform PreviousCompWorldSpaceTM;`
- L213 _private member_ `FTransform CurrentTransform;`
- L214 _private member_ `FTransform PreviousTransform;`
- L216 _private member_ `UPhysicsAsset* UsePhysicsAsset;`
- L221 _public member_ `bool bUseLocalLODThresholdOnly = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (PinHiddenByDefault))` — Enable if you want to ignore the p.RigidBodyLODThreshold CVAR and force the node to solely use the LOD threshold.
- L225 _public member_ `FVector OverrideWorldGravity;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault, editcondition = "bOverrideWorldGravity"))` — Override gravity
- L229 _public member_ `FVector ExternalForce;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))` — Applies a uniform external force in world space. This allows for easily faking inertia of movement while still simulating in component space for example
- L233 _public member_ `FVector ComponentLinearAccScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this controls how much of the components world-space acceleration is passed on to the local-space simulation.
- L237 _public member_ `FVector ComponentLinearVelScale;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — When using non-world-space sim, this applies a 'drag' to the bodies in the local space simulation, based on the components world-space velocity.
- L241 _public member_ `FVector ComponentAppliedLinearAccClamp;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When using non-world-space sim, this is an overall clamp on acceleration derived from ComponentLinearAccScale and ComponentLinearVelScale, to ensure it is not too large.
- L254 _public member_ `FSimSpaceSettings SimSpaceSettings;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (PinHiddenByDefault))` — Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way. This system is a superset of the functionality provided by ComponentLinearAccScale, ComponentLinearVelScale, and ComponentAppliedLinearAccClamp. In general you should not have both systems enabled.
- L263 _public member_ `float CachedBoundsScale;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin="1.0", ClampMax="2.0"))` — Scale of cached bounds (vs. actual bounds). Increasing this may improve performance, but overlaps may not work as well. (A value of 1.0 effectively disables cached bounds).
- L267 _public member_ `FBoneReference BaseBoneRef;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Matters if SimulationSpace is BaseBone
- L271 _public member_ `TEnumAsByte<ECollisionChannel> OverlapChannel;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (editcondition = "bEnableWorldGeometry"))` — The channel we use to find static geometry to collide with
- L275 _public member_ `ESimulationSpace SimulationSpace;` — `UPROPERTY(EditAnywhere, Category = Settings)` — What space to simulate the bodies in. This affects how velocities are generated
- L279 _public member_ `bool bForceDisableCollisionBetweenConstraintBodies;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — Whether to allow collisions between two bodies joined by a constraint
- L283 _public member_ `bool bUseExternalClothCollision;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — If true, kinematic objects will be added to the simulation at runtime to represent any cloth colliders defined for the parent object.
- L286 _private member_ `ETeleportType ResetSimulatedTeleportType;`
- L290 _public member_ `uint8 bEnableWorldGeometry : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L293 _public member_ `uint8 bOverrideWorldGravity : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (InlineEditConditionToggle))`
- L300 _public member_ `uint8 bTransferBoneVelocities : 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(PinHiddenByDefault))` — When simulation starts, transfer previous bone velocities (from animation) to make transition into simulation seamless.
- L308 _public member_ `uint8 bFreezeIncomingPoseOnStart : 1;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When simulation starts, freeze incoming pose. This is useful for ragdolls, when we want the simulation to take over. It prevents non simulated bones from animating.
- L315 _public member_ `uint8 bClampLinearTranslationLimitToRefPose : 1;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Correct for linear tearing on bodies with all axes Locked. This only works if all axes linear translation are locked
- L323 _public member_ `uint8 bAllowPoseScalePropagation : 1;` — `UPROPERTY(EditAnywhere, Category = Settings)` — Allow / Prevent bone transform scales denfined in the input pose from being passed to the output pose. This setting is true by default but will only have an effect if bone scale propagation is enabled project wide with the p.RigidBodyNode.EnablePoseScalePropagation console variable. The details pannel checkbox will be hidden if the feature is not enabled.
- L329 _public member_ `float WorldSpaceMinimumScale;` — `UPROPERTY(EditAnywhere, Category = Settings)` — For world-space simulations, if the magnitude of the component's 3D scale is less than WorldSpaceMinimumScale, do not update the node.
- L336 _public member_ `float EvaluationResetTime;` — `UPROPERTY(EditAnywhere, Category = Settings)` — If the node is not evaluated for this amount of time (seconds), either because a lower LOD was in use for a while or the component was not visible, reset the simulation to the default pose on the next evaluation. Set to 0 to disable time-based reset.
- L344 _public member_ `float BoundsVelocityMultiplier = 0.0f;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin = 0))` — Expands the shape bounds to detect potentially active contacts when moving. Increasing this (typically up to 1) will increase the number of inactive contacts, which will reduce the likelihood of penetration, but will also increase solver cost.
- L351 _public member_ `float MaxVelocityBoundsExpansion = 0.0f;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings, meta = (ClampMin = 0))` — The maximum margin added due to movement. Reducing this can prevent excessive numbers of inactive contacts being generated.
- L357 _public member_ `bool bAllowCCD = false;` — `UPROPERTY(EditAnywhere, Category = CollisionSettings)` — Allows the solver to use the EnableCCD setting on the bodies
- L360 _private member_ `uint8 bEnabled : 1;`
- L361 _private member_ `uint8 bSimulationStarted : 1;`
- L362 _private member_ `uint8 bCheckForBodyTransformInit : 1;`
- L365 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L371 _private member_ `bool bComponentSpaceSimulation_DEPRECATED;` — `UPROPERTY()` — use SimulationSpace
- L375 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L378 _private prototype_ `void InitPhysics(const UAnimInstance* InAnimInstance);`
- L379 _private prototype_ `void UpdateWorldGeometry(const UWorld& World, const USkeletalMeshComponent& SKC);`
- L380 _private prototype_ `void UpdateWorldForces(const FTransform& ComponentToWorld, const FTransform& RootBoneTM, const float DeltaSeconds);`
- L382 _private prototype_ `void InitializeNewBodyTransformsDuringSimulation(FComponentSpacePoseContext& Output, const FTransform& ComponentTransform, const FTransform& BaseBoneTM);`
- L384 _private prototype_ `void InitSimulationSpace( const FTransform& ComponentToWorld, const FTransform& BoneToComponent);`
- L389 _private prototype_ `void CalculateSimulationSpaceMotion( ESimulationSpace Space, const FTransform& SpaceTransform, const FTransform& ComponentToWorld, const float Dt, const FSimSpaceSettings& Settings, FVector& SpaceLinearVel, FVector& SpaceAngularVel, FVector& SpaceLinearAcc, FVector& SpaceAngularAcc);` — Calculate simulation space transform, velocity etc to pass into the solver
- L402 _private prototype_ `void CollectClothColliderObjects(const USkeletalMeshComponent* SkeletalMeshComp);` — Gather cloth collision sources from the supplied Skeletal Mesh and add a kinematic actor representing each one of them to the sim.
- L405 _private prototype_ `void RemoveClothColliderObjects();` — Remove all cloth collider objects from the sim.
- L408 _private prototype_ `void UpdateClothColliderObjects(const FTransform& SpaceTransform);` — Update the sim-space transforms of all cloth collider objects.
- L411 _private prototype_ `void CollectWorldObjects();` — Gather nearby world objects and add them to the sim
- L414 _private prototype_ `void ExpireWorldObjects();` — Flag invalid world objects to be removed from the sim
- L417 _private prototype_ `void PurgeExpiredWorldObjects();` — Remove simulation objects that are flagged as expired
- L420 _private prototype_ `void UpdateWorldObjects(const FTransform& SpaceTransform);` — Update sim-space transforms of world objects
- L423 _private prototype_ `void RunPhysicsSimulation(float DeltaSeconds, const FVector& SimSpaceGravity);` — Advances the simulation by a given timestep
- L426 _private prototype_ `void FlushDeferredSimulationTask();` — Waits for the deferred simulation task to complete if it's not already finished
- L429 _private prototype_ `void DestroyPhysicsSimulation();` — Destroy the simulation and free related structures
- L435 _public member_ `ESimulationTiming SimulationTiming;` — `UPROPERTY(EditAnywhere, Category=Settings, AdvancedDisplay)` — Whether the physics simulation runs synchronously with the node's evaluation or is run in the background until the next frame.
- L439 _private member_ `double WorldTimeSeconds;`
- L440 _private member_ `double LastEvalTimeSeconds;`
- L442 _private member_ `float AccumulatedDeltaTime;`
- L443 _private member_ `float AnimPhysicsMinDeltaTime;`
- L444 _private member_ `bool bSimulateAnimPhysicsAfterReset;`
- L446 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelMeshCompWeakPtr;` — This should only be used for removing the delegate during termination. Do NOT use this for any per frame work
- L448 _private member_ `ImmediatePhysics::FSimulation* PhysicsSimulation;`
- L449 _private member_ `FPhysicsAssetSolverSettings SolverSettings;`
- L450 _private member_ `FSolverIterations SolverIterations;` — to be deprecated
- L453 _private member_ `UE::Tasks::FTask SimulationTask;`
- L516 _private member_ `TArray<FOutputBoneData> OutputBoneData;`
- L517 _private member_ `TArray<ImmediatePhysics::FActorHandle*> Bodies;`
- L518 _private member_ `TArray<int32> SkeletonBoneIndexToBodyIndex;`
- L519 _private member_ `TArray<FBodyAnimData> BodyAnimData;`
- L521 _private member_ `TArray<FPhysicsConstraintHandle*> Constraints;`
- L522 _private member_ `TArray<USkeletalMeshComponent::FPendingRadialForces> PendingRadialForces;`
- L524 _private member_ `FPerSolverFieldSystem PerSolverField;`
- L541 _private member_ `TArray<FClothCollider> ClothColliders;` — List of actors in the sim that represent objects collected from other parts of this character.
- L547 _private member_ `TMap<const UPrimitiveComponent*, FWorldObject> ComponentsInSim;` — List of actors in the sim that represent objects collected from the world. Note that the key should never be dereferenced, as it is not a smart pointer, and might have been deleted. Instead it should just be used for comparisons, and the actual pointer to the component is stored in the WorldObject.
- L548 _private member_ `int32 ComponentsInSimTick;`
- L550 _private member_ `FVector WorldSpaceGravity;`
- L552 _private member_ `double TotalMass;`
- L555 _private member_ `FSphere CachedBounds;` — Bounds used to gather world objects copied into the simulation
- L557 _private member_ `FCollisionQueryParams QueryParams;`
- L559 _private member_ `FPhysScene* PhysScene;`
- L564 _private member_ `const UWorld* UnsafeWorld;` — Used by CollectWorldObjects and UpdateWorldGeometry in Task Thread Typically, World should never be accessed off the Game Thread. However, since we're just doing overlaps this should be OK.
- L568 _private member_ `const AActor* UnsafeOwner;` — Used by CollectWorldObjects and UpdateWorldGeometry in Task Thread Only used for a pointer comparison.
- L570 _private member_ `FBoneContainer CapturedBoneVelocityBoneContainer;`
- L571 _private member_ `FCSPose<FCompactHeapPose> CapturedBoneVelocityPose;`
- L572 _private member_ `FCSPose<FCompactHeapPose> CapturedFrozenPose;`
- L573 _private member_ `FBlendedHeapCurve CapturedFrozenCurves;`
- L575 _private member_ `FVector PreviousComponentLinearVelocity;`
- L578 _private member_ `FTransform PreviousSimulationSpaceTransform;` — Used by the world-space to simulation-space motion transfer system in Component- or Bone-Space sims
- L579 _private member_ `FTransform PreviousPreviousSimulationSpaceTransform;`
- L580 _private member_ `float PreviousDt;`
- L583 _private member_ `FName OwningAssetPackageName;`
- L584 _private member_ `FName OwningAssetName;`

#### struct `FAnimNode_RigidBody::FOutputBoneData`  
`struct FOutputBoneData`  
_L455-465_
- L457 _public function_ `FOutputBoneData() : CompactPoseBoneIndex(INDEX_NONE)`
- L461 _public member_ `TArray<FCompactPoseBoneIndex> BoneIndicesToParentBody;`
- L462 _public member_ `FCompactPoseBoneIndex CompactPoseBoneIndex;`
- L463 _public member_ `int32 BodyIndex;`
- L464 _public member_ `int32 ParentBodyIndex;`

#### struct `FAnimNode_RigidBody::FBodyAnimData`  
`struct FBodyAnimData`  
_L467-496_
- L469 _public function_ `FBodyAnimData() : TransferedBoneAngularVelocity(ForceInit) , TransferedBoneLinearVelocity(ForceInitToZero) , LinearXMotion(ELinearConstraintMotion::LCM_Locked) , LinearYMotion(ELinearConstraintMotion::LCM_Locked) , LinearZMotion(ELinearConstraintMotion::LCM_Locked) , LinearLimit(0.0f) , RefPoseLength (0.f) , bIsSimulated(false) , bBodyTransformInitialized(false)`
- L481 _public member_ `FQuat TransferedBoneAngularVelocity;`
- L482 _public member_ `FVector TransferedBoneLinearVelocity;`
- L484 _public member_ `ELinearConstraintMotion LinearXMotion;`
- L485 _public member_ `ELinearConstraintMotion LinearYMotion;`
- L486 _public member_ `ELinearConstraintMotion LinearZMotion;`
- L487 _public member_ `float LinearLimit;`
- L492 _public member_ `float RefPoseLength;` — we don't use linear limit but use default length to limit the bodies linear limits are defined per constraint - it can be any two joints that can limit this is just default length of the local space from parent, and we use that info to limit the translation
- L494 _public member_ `bool bIsSimulated : 1;`
- L495 _public member_ `bool bBodyTransformInitialized : 1;`

#### struct `FAnimNode_RigidBody::FWorldObject`  
`struct FWorldObject`  
_L498-514_
- L500 _public function_ `FWorldObject() : ActorHandle(nullptr), LastSeenTick(0), bExpired(false), bNew(true)`
- L501 _public function_ `FWorldObject( ImmediatePhysics::FActorHandle* InActorHandle, int32 InLastSeenTick, TWeakObjectPtr<UPrimitiveComponent> InComponent) : Component(InComponent), ActorHandle(InActorHandle), LastSeenTick(InLastSeenTick) , bExpired(false), bNew(true)`
- L509 _public member_ `TWeakObjectPtr<UPrimitiveComponent> Component;`
- L510 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;`
- L511 _public member_ `int32 LastSeenTick;`
- L512 _public member_ `uint8 bExpired : 1;`
- L513 _public member_ `uint8 bNew : 1;`

#### struct `FAnimNode_RigidBody::FClothCollider`  
`struct FClothCollider`  
_L527-538_
- desc: Information required to identify and update a kinematic object representing a cloth collision source in the sim.
- L529 _public function_ `FClothCollider(ImmediatePhysics::FActorHandle* const InActorHandle, const USkeletalMeshComponent* const InSkeletalMeshComponent, const uint32 InBoneIndex) : ActorHandle(InActorHandle) , SkeletalMeshComponent(InSkeletalMeshComponent) , BoneIndex(InBoneIndex)`
- L535 _public member_ `ImmediatePhysics::FActorHandle* ActorHandle;` — Identifies the physics actor in the sim.
- L536 _public member_ `const USkeletalMeshComponent* SkeletalMeshComponent;` — Parent skeleton.
- L537 _public member_ `uint32 BoneIndex;` — Bone within parent skeleton that drives physics actors transform.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_RigidBody> : public TStructOpsTypeTraitsBase2<FAnimNode_RigidBody>`  
_L590-596_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_RigidBody>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L593-595_

#### Free symbols / members of external scopes

- L17 _externvar_ `extern bool bEnableRigidBodyNode;`
- L18 _externvar_ `extern FAutoConsoleVariableRef CVarEnableRigidBodyNode;`
- L19 _externvar_ `extern TAutoConsoleVariable<int32> CVarEnableRigidBodyNodeSimulation;`
- L20 _externvar_ `extern TAutoConsoleVariable<int32> CVarRigidBodyLODThreshold;`
- L51 _enumerator_ `template <> struct TIsPODType<FSimSpaceSettings> { enum { Value = true }; }; USTRUCT(BlueprintType) struct FSimSpaceSettings { GENERATED_USTRUCT_BODY() ANIMGRAPHRUNTIME_API FSimSpaceSettings();` (scope `TIsPODType::__anone58cede80103`) — Settings for the system which passes motion of the simulation's space into the simulation. This allows the simulation to pass a fraction of the world space motion onto the bodies which allows Bone-Space and Component-Space simulations to react to world-space movement in a controllable way.
- L145 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anone58cede80203`)
- L594 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anone58cede80303`)
- L599 _function_ `inline FTransform SpaceToWorldTransform( ESimulationSpace Space, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L611 _function_ `inline FVector WorldVectorToSpaceNoScale( ESimulationSpace Space, const FVector& WorldDir, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L624 _function_ `inline FVector WorldPositionToSpace( ESimulationSpace Space, const FVector& WorldPoint, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L637 _function_ `inline FTransform ConvertCSTransformToSimSpace( ESimulationSpace SimSpace, const FTransform& InCSTransform, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L649 _function_ `inline FVector ConvertCSVectorToSimSpace( ESimulationSpace SimSpace, const FVector& InCSVector, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L661 _function_ `inline FVector ConvertCSPositionToSimSpace( ESimulationSpace SimSpace, const FVector& InCSPosition, const FTransform& ComponentToWorld, const FTransform& BaseBoneTM)`
- L673 _prototype_ `bool RigidBodyNodeIsPoseScalePropagationEnabledGlobally();`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_RigidBody_Library.h` (Public)


#### struct `FRigidBodyAnimNodeReference`  
`struct FRigidBodyAnimNodeReference : public FAnimNodeReference`  
_L13-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L17 _public typedef_ `typedef FAnimNode_RigidBody FInternalNodeType;`

#### class `UAnimNodeRigidBodyLibrary`  
`class UAnimNodeRigidBodyLibrary : public UBlueprintFunctionLibrary`  
_L22-38_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a rigid body anim node
- L29 _public prototype_ `static FRigidBodyAnimNodeReference ConvertToRigidBodyAnimNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Dynamics", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a rigid body anim node context from an anim node context
- L33 _public prototype_ `static void ConvertToRigidBodyAnimNodePure(const FAnimNodeReference& Node, FRigidBodyAnimNodeReference& RigidBodyAnimNode, bool& Result);` — `UFUNCTION(BlueprintPure, Category = "Animation|Dynamics", meta = (BlueprintThreadSafe, DisplayName = "Convert to rigid body"))` — Get a rigid body anim node context from an anim node context (pure)
- L37 _public prototype_ `static FRigidBodyAnimNodeReference SetOverridePhysicsAsset(const FRigidBodyAnimNodeReference& Node, UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Dynamics", meta = (BlueprintThreadSafe))` — Set the physics asset on the rigid body anim graph node (RBAN).

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_RotationMultiplier.h` (Public)


#### struct `FAnimNode_RotationMultiplier`  
`struct FAnimNode_RotationMultiplier : public FAnimNode_SkeletalControlBase`  
_L19-62_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L25 _public member_ `FBoneReference TargetBone;` — `UPROPERTY(EditAnywhere, Category=Multiplier)` — Name of bone to control. This is the main bone chain to modify from.
- L29 _public member_ `FBoneReference SourceBone;` — `UPROPERTY(EditAnywhere, Category=Multiplier)` — Source to get transform from
- L34 _public member_ `float Multiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Multiplier, meta=(PinShownByDefault))` — To make these to be easily pin-hookable, I'm not making it struct, but each variable 0.f is invalid, and default
- L37 _public member_ `TEnumAsByte<EBoneAxis> RotationAxisToRefer;` — `UPROPERTY(EditAnywhere, Category=Multiplier)`
- L40 _public member_ `bool bIsAdditive;` — `UPROPERTY(EditAnywhere, Category = Multiplier)`
- L42 _public prototype_ `FAnimNode_RotationMultiplier();`
- L45 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L49 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L50 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L55 _private prototype_ `FQuat ExtractAngle(const FTransform& RefPoseTransform, const FTransform& LocalBoneTransform, const EBoneAxis Axis);` — Extract Delta Quat of rotation around Axis of animation and reference pose for the SourceBoneIndex
- L57 _private prototype_ `FQuat MultiplyQuatBasedOnSourceIndex(const FTransform& RefPoseTransform, const FTransform& LocalBoneTransform, const EBoneAxis Axis, float InMultiplier, const FQuat& ReferenceQuat);` — Multiply scalar value Multiplier to the delta Quat of SourceBone Index's rotation
- L60 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_ScaleChainLength.h` (Public)


#### enum `EScaleChainInitialLength`  
`enum class EScaleChainInitialLength : uint8`  
_L16-24_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `FixedDefaultLengthValue` — Use the 'DefaultChainLength' input value.
- L21 _public enumerator_ `Distance` — Use distance between 'ChainStartBone' and 'ChainEndBone' (in Component Space)
- L23 _public enumerator_ `ChainLength` — Use animated chain length (length in local space of every bone from 'ChainStartBone' to 'ChainEndBone'

#### struct `FAnimNode_ScaleChainLength`  
`struct FAnimNode_ScaleChainLength : public FAnimNode_Base`  
_L30-78_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- desc: Scale the length of a chain of bones.
- L35 _public member_ `FPoseLink InputPose;` — `UPROPERTY(EditAnywhere, Category = Links)`
- L39 _public member_ `float DefaultChainLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScaleChainLength, meta = (PinHiddenByDefault))` — Default chain length, as animated.
- L42 _public member_ `FBoneReference ChainStartBone;` — `UPROPERTY(EditAnywhere, Category = ScaleChainLength)`
- L45 _public member_ `FBoneReference ChainEndBone;` — `UPROPERTY(EditAnywhere, Category = ScaleChainLength)`
- L48 _public member_ `FVector TargetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScaleChainLength, meta = (PinShownByDefault))`
- L51 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (PinShownByDefault))`
- L53 _public member_ `float ActualAlpha;`
- L56 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L59 _public member_ `EScaleChainInitialLength ChainInitialLength;` — `UPROPERTY(EditAnywhere, Category = ScaleChainLength)`
- L61 _public member_ `bool bBoneIndicesCached;`
- L63 _public member_ `TArray<FCompactPoseBoneIndex> ChainBoneIndices;`
- L66 _public prototype_ `FAnimNode_ScaleChainLength();`
- L69 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L70 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;`
- L71 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L72 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L73 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L77 _protected prototype_ `double GetInitialChainLength(FCompactPose& InLSPose, FCSPose<FCompactPose>& InCSPose) const;`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_SkeletalControlBase.h` (Public)


#### struct `FAnimNode_SkeletalControlBase`  
`struct FAnimNode_SkeletalControlBase : public FAnimNode_Base`  
_L21-140_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L27 _public member_ `FComponentSpacePoseLink ComponentPose;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)` — Input link
- L36 _public member_ `int32 LODThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Performance, meta = (PinHiddenByDefault, DisplayName = "LOD Threshold"))` — Max LOD that this node is allowed to run For example if you have LODThreshold to be 2, it will run until LOD 2 (based on 0 index) when the component LOD becomes 3, it will stop update/evaluate currently transition would be issue and that has to be re-visited
- L39 _public member_ `float ActualAlpha;` — `UPROPERTY(Transient)`
- L42 _public member_ `EAnimAlphaInputType AlphaInputType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L45 _public member_ `bool bAlphaBoolEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault, DisplayName = "bEnabled"))`
- L49 _public member_ `float Alpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))` — Current strength of the skeletal control
- L52 _public member_ `FInputScaleBias AlphaScaleBias;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L55 _public member_ `FInputAlphaBoolBlend AlphaBoolBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (DisplayName = "Blend Settings"))`
- L58 _public member_ `FName AlphaCurveName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha, meta = (PinShownByDefault))`
- L61 _public member_ `FInputScaleBiasClamp AlphaScaleBiasClamp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alpha)`
- L65 _public function_ `FAnimNode_SkeletalControlBase() : LODThreshold(INDEX_NONE) , ActualAlpha(0.f) , AlphaInputType(EAnimAlphaInputType::Float) , bAlphaBoolEnabled(true) , Alpha(1.0f)`
- L74 _public prototype_ `virtual ~FAnimNode_SkeletalControlBase() = default;`
- L79 _public member_ `FCSPose<FCompactHeapPose> ForwardedPose;` — forwarded pose data from the wired node which current node's skeletal control is not applied yet
- L83 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L84 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L85 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext& Context) final;`
- L86 _public prototype_ `virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) final;`
- L87 _public function_ `virtual int32 GetLODThreshold() const override`
- L91 _public prototype_ `void SetAlpha(float InAlpha);` — Set the alpha of this node
- L94 _public prototype_ `float GetAlpha() const;` — Get the alpha of this node
- L96 _public prototype_ `void InitializeAndValidateBoneRef(FBoneReference& BoneRef, const FBoneContainer& RequiredBones);`
- L101 _public prototype_ `void AddBoneRefMissingVisualWarning(const FString& BoneName, const FString& SkeletalMeshName);`
- L102 _public prototype_ `void AddValidationVisualWarning(FText ValidationVisualWarning);`
- L103 _public prototype_ `bool HasValidationVisualWarnings() const;`
- L104 _public prototype_ `void ClearValidationVisualWarnings();`
- L105 _public prototype_ `FText GetValidationVisualWarningMessage() const;`
- L111 _protected prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context);` — Interface for derived skeletal controls to implement use this function to update for skeletal control base
- L114 _protected prototype_ `virtual void UpdateComponentPose_AnyThread(const FAnimationUpdateContext& Context);` — Update incoming component pose.
- L117 _protected prototype_ `virtual void EvaluateComponentPose_AnyThread(FComponentSpacePoseContext& Output);` — Evaluate incoming component pose.
- L120 _protected prototype_ `virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context);` — use this function to evaluate for skeletal control base
- L122 _protected prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms);` — Evaluate the new component-space transforms for the affected bones.
- L124 _protected function_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)` — return true if it is valid to Evaluate
- L126 _protected function_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones)` — initialize any bone references you have
- L129 _protected prototype_ `void AddDebugNodeData(FString& OutDebugData);` — Allow base to add info to the node debug output
- L133 _private member_ `TArray<FBoneTransform> BoneTransforms;` — Resused bone transform array to avoid reallocating in skeletal controls
- L137 _private member_ `FText ValidationVisualWarningMessage;` — `UPROPERTY(transient)`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_SplineIK.h` (Public)


#### enum `ESplineBoneAxis`  
`enum class ESplineBoneAxis : uint8`  
_L15-21_
- reflection: `UENUM()`
- desc: The different axes we can align our bones to. Note that the values are set to match up with EAxis (but without 'None')
- L17 _public enumerator_ `None = 0 UMETA(Hidden)`
- L18 _public enumerator_ `X = 1`
- L19 _public enumerator_ `Y = 2`
- L20 _public enumerator_ `Z = 3`

#### struct `FSplineIKCachedBoneData`  
`struct FSplineIKCachedBoneData`  
_L25-46_
- reflection: `USTRUCT()`
- desc: Data cached per bone in the chain
- L29 _public function_ `FSplineIKCachedBoneData() : Bone(NAME_None) , RefSkeletonIndex(INDEX_NONE)`
- L34 _public function_ `FSplineIKCachedBoneData(const FName& InBoneName, int32 InRefSkeletonIndex) : Bone(InBoneName) , RefSkeletonIndex(InRefSkeletonIndex)`
- L41 _public member_ `FBoneReference Bone;` — `UPROPERTY()` — The bone we refer to
- L45 _public member_ `int32 RefSkeletonIndex;` — `UPROPERTY()` — Index of the bone in the reference skeleton

#### struct `FAnimNode_SplineIK`  
`struct FAnimNode_SplineIK : public FAnimNode_SkeletalControlBase`  
_L49-186_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L55 _public member_ `FBoneReference StartBone;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — Name of root bone from which the spline extends
- L59 _public member_ `FBoneReference EndBone;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — Name of bone at the end of the spline chain. Bones after this will not be altered by the controller.
- L63 _public member_ `ESplineBoneAxis BoneAxis;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — Axis of the controlled bone (ie the direction of the spline) to use as the direction for the curve.
- L67 _public member_ `bool bAutoCalculateSpline;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — The number of points in the spline if we are specifying it directly
- L71 _public member_ `int32 PointCount;` — `UPROPERTY(EditAnywhere, Category = "Parameters", meta = (ClampMin = 2, UIMin = 2, EditCondition = "!bAutoCalculateSpline"))` — The number of points in the spline if we are not auto-calculating
- L75 _public member_ `TArray<FTransform> ControlPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Parameters", meta = (BlueprintCompilerGeneratedDefaults, PinHiddenByDefault))` — Transforms applied to spline points
- L79 _public member_ `float Roll;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (PinHiddenByDefault))` — Overall roll of the spline, applied on top of other rotations along the direction of the spline
- L83 _public member_ `float TwistStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (PinHiddenByDefault))` — The twist of the start bone. Twist is interpolated along the spline according to Twist Blend.
- L87 _public member_ `float TwistEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (PinHiddenByDefault))` — The twist of the end bone. Twist is interpolated along the spline according to Twist Blend.
- L91 _public member_ `FAlphaBlend TwistBlend;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — How to interpolate twist along the length of the spline
- L98 _public member_ `float Stretch;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (PinHiddenByDefault))` — The maximum stretch allowed when fitting bones to the spline. 0.0 means bones do not stretch their length, 1.0 means bones stretch to the length of the spline
- L102 _public member_ `float Offset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters", meta = (PinHiddenByDefault))` — The distance along the spline from the start from which bones are constrained
- L104 _public prototype_ `FAnimNode_SplineIK();`
- L107 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L108 _public prototype_ `virtual void OnInitializeAnimInstance(const FAnimInstanceProxy* InProxy, const UAnimInstance* InAnimInstance) override;`
- L109 _public function_ `virtual bool NeedsOnInitializeAnimInstance() const override`
- L113 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L114 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L118 _public function_ `const FSplineCurves& GetSplineCurves() const` — Read-only access to spline curves
- L121 _public function_ `const FSplineCurves& GetTransformedSplineCurves() const` — Read-only access to transformed curves
- L124 _public prototype_ `FTransform GetTransformedSplinePoint(int32 TransformIndex) const;` — Get transformed spline point (in component space) for the spline
- L127 _public prototype_ `FTransform GetControlPoint(int32 TransformIndex) const;` — Get specified handle transform (in component space) for the spline
- L130 _public prototype_ `void SetControlPoint(int32 TransformIndex, const FTransform& InTransform);` — Set specified handle transform (in component space) for the spline
- L133 _public prototype_ `void SetControlPointLocation(int32 TransformIndex, const FVector& InLocation);` — Set specified handle location (in component space) for the spline
- L136 _public prototype_ `void SetControlPointRotation(int32 TransformIndex, const FQuat& InRotation);` — Set specified handle rotation (in component space) for the spline
- L139 _public prototype_ `void SetControlPointScale(int32 TransformIndex, const FVector& InScale);` — Set specified handle scale (in component space) for the spline
- L142 _public function_ `int32 GetNumControlPoints() const` — Get the number of spline transforms we are using
- L145 _public prototype_ `void GatherBoneReferences(const FReferenceSkeleton& RefSkeleton);` — Build bone references & reallocate transforms from the supplied ref skeleton
- L149 _protected prototype_ `void BuildBoneSpline(const FReferenceSkeleton& RefSkeleton);` — Build spline from reference pose
- L153 _protected prototype_ `void TransformSpline();` — Transform the spline using our control points
- L156 _protected prototype_ `float FindParamAtFirstSphereIntersection(const FVector& InOrigin, float InRadius, int32& StartingLinearIndex);` — Use our linear approximation to determine the earliest intersection with a sphere
- L160 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L164 _private prototype_ `float GetTwist(float InAlpha, float TotalSplineAlpha);` — Get the current twist value at the specified spline alpha
- L167 _private member_ `FSplineCurves TransformedSpline;` — Transformed spline
- L170 _private member_ `TArray<FSplinePositionLinearApproximation> LinearApproximation;` — Piecewise linear approximation of the spline, recalculated on creation and deformation
- L173 _private member_ `FSplineCurves BoneSpline;` — Spline we maintain internally
- L176 _private member_ `float OriginalSplineLength;` — Cached spline length from when the spline was originally applied to the skeleton
- L179 _private member_ `TArray<FSplineIKCachedBoneData> CachedBoneReferences;` — Cached data for bones in the IK chain, from start to end
- L182 _private member_ `TArray<float> CachedBoneLengths;` — Cached bone lengths. Same size as CachedBoneReferences
- L185 _private member_ `TArray<FQuat> CachedOffsetRotations;` — Cached bone offset rotations. Same size as CachedBoneReferences

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_SpringBone.h` (Public)


#### struct `FAnimNode_SpringBone`  
`struct FAnimNode_SpringBone : public FAnimNode_SkeletalControlBase`  
_L20-131_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L26 _public member_ `FBoneReference SpringBone;` — `UPROPERTY(EditAnywhere, Category=Spring)` — Name of bone to control. This is the main bone chain to modify from.
- L30 _public member_ `double MaxDisplacement;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spring, meta=(EditCondition="bLimitDisplacement"))` — If bLimitDisplacement is true, this indicates how long a bone can stretch beyond its length in the ref-pose.
- L34 _public member_ `double SpringStiffness;` — `UPROPERTY(EditAnywhere, Category=Spring, meta = (PinHiddenByDefault))` — Stiffness of spring
- L38 _public member_ `double SpringDamping;` — `UPROPERTY(EditAnywhere, Category=Spring, meta = (PinHiddenByDefault))` — Damping of spring
- L42 _public member_ `double ErrorResetThresh;` — `UPROPERTY(EditAnywhere, Category=Spring)` — If spring stretches more than this, reset it. Useful for catching teleports etc
- L45 _public member_ `FVector BoneLocation;` — World-space location of the bone.
- L48 _public member_ `FVector BoneVelocity;` — World-space velocity of the bone.
- L51 _public member_ `FVector OwnerVelocity;` — Velocity of the owning actor
- L55 _public member_ `FVector LocalBoneTransform;` — Cache of previous frames local bone transform so that when we cannot simulate (timestep == 0) we can still update bone location
- L58 _public member_ `float RemainingTime;` — Internal use - Amount of time we need to simulate.
- L61 _public member_ `float FixedTimeStep;` — Internal use - Current timestep
- L64 _public member_ `float TimeDilation;` — Internal use - Current time dilation
- L69 _public member_ `bool bNoZSpring_DEPRECATED;` — `UPROPERTY()` — If true, Z position is always correct, no spring applied
- L74 _public member_ `uint8 bLimitDisplacement : 1;` — `UPROPERTY(EditAnywhere, Category=Spring)` — Limit the amount that a bone can stretch from its ref-pose length.
- L78 _public member_ `uint8 bTranslateX : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for translation in X
- L82 _public member_ `uint8 bTranslateY : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for translation in Y
- L86 _public member_ `uint8 bTranslateZ : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for translation in Z
- L90 _public member_ `uint8 bRotateX : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for rotation in X
- L94 _public member_ `uint8 bRotateY : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for rotation in Y
- L98 _public member_ `uint8 bRotateZ : 1;` — `UPROPERTY(EditAnywhere, Category=FilterChannels)` — If true take the spring calculation for rotation in Z
- L101 _public member_ `uint8 bHadValidStrength : 1;` — Did we have a non-zero ControlStrength last frame.
- L105 _public member_ `uint8 bOverrideOwnerVelocity : 1;` — `UPROPERTY(EditAnywhere, Category = OwnerVelocity, Meta = (PinHiddenByDefault))` — Option to override owner velocity used by spring controller.
- L108 _public member_ `FVector OwnerVelocityOverride;` — `UPROPERTY(EditAnywhere, Category = OwnerVelocity, Meta = (EditCondition = "bOverrideOwnerVelocity", PinHiddenByDefault))`
- L111 _public prototype_ `FAnimNode_SpringBone();`
- L114 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L115 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L116 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L117 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L118 _public function_ `virtual bool HasPreUpdate() const override`
- L119 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L123 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L124 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L129 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_Trail.h` (Public)


#### struct `FPerJointTrailSetup`  
`struct FPerJointTrailSetup`  
_L18-22_
- desc: in the future, we might use this for stretch set up as well for now this is unserializable, and transient only
- L21 _public member_ `float TrailRelaxationSpeedPerSecond;` — How quickly we 'relax' the bones to their animated positions.

#### struct `FRotationLimit`  
`struct FRotationLimit`  
_L25-39_
- reflection: `USTRUCT()`
- L29 _public function_ `FRotationLimit() : LimitMin(-180, -180, -180) , LimitMax(+180, +180, +180)`
- L35 _public member_ `FVector LimitMin;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`
- L38 _public member_ `FVector LimitMax;` — `UPROPERTY(EditAnywhere, Category = Angular, meta = (UIMin = "-180", UIMax = "180", ClampMin = "-180", ClampMax = "180"))`

#### struct `FAnimNode_Trail`  
`struct FAnimNode_Trail : public FAnimNode_SkeletalControlBase`  
_L46-209_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L51 _public member_ `FTransform OldBaseTransform;` — LocalToWorld used last frame, used for building transform between frames.
- L55 _public member_ `FBoneReference TrailBone;` — `UPROPERTY(EditAnywhere, Category=Trail)` — Reference to the active bone in the hierarchy to modify.
- L59 _public member_ `int32 ChainLength;` — `UPROPERTY(EditAnywhere, Category = Trail, meta = (ClampMin = "2", UIMin = "2"))` — Number of bones above the active one in the hierarchy to modify. ChainLength should be at least 2.
- L63 _public member_ `TEnumAsByte<EAxis::Type> ChainBoneAxis;` — `UPROPERTY(EditAnywhere, Category=Trail)` — Axis of the bones to point along trail.
- L67 _public member_ `uint8 bInvertChainBoneAxis:1;` — `UPROPERTY(EditAnywhere, Category=Trail)` — Invert the direction specified in ChainBoneAxis.
- L71 _public member_ `uint8 bLimitStretch:1;` — `UPROPERTY(EditAnywhere, Category=Limit)` — Limit the amount that a bone can stretch from its ref-pose length.
- L75 _public member_ `uint8 bLimitRotation:1;` — `UPROPERTY(EditAnywhere, Category = Limit)` — Limit the amount that a bone can stretch from its ref-pose length.
- L79 _public member_ `uint8 bUsePlanarLimit:1;` — `UPROPERTY(EditAnywhere, Category=Limit)` — Whether to evaluate planar limits
- L83 _public member_ `uint8 bActorSpaceFakeVel:1;` — `UPROPERTY(EditAnywhere, Category=Velocity)` — Whether 'fake' velocity should be applied in actor or world space.
- L87 _public member_ `uint8 bReorientParentToChild:1;` — `UPROPERTY(EditAnywhere, Category = Rotation)` — Fix up rotation to face child for the parent
- L90 _public member_ `uint8 bHadValidStrength:1;` — Did we have a non-zero ControlStrength last frame.
- L95 _public member_ `uint8 bEnableDebug:1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Enable Debug in the PIE. This doesn't work in game
- L99 _public member_ `uint8 bShowBaseMotion:1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Show Base Motion
- L103 _public member_ `uint8 bShowTrailLocation:1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Show Trail Location
- L107 _public member_ `uint8 bShowLimit:1;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Show Planar Limits
- L110 _public member_ `uint8 bEditorDebugEnabled:1;` — This is used by selection node. Use this transient flag.
- L114 _public member_ `float DebugLifeTime;` — `UPROPERTY(EditAnywhere, Category = Debug)` — Debug Life Time
- L118 _public member_ `float TrailRelaxation_DEPRECATED;` — `UPROPERTY()` — How quickly we 'relax' the bones to their animated positions. Deprecated. Replaced to TrailRelaxationCurve
- L123 _public member_ `float MaxDeltaTime;` — `UPROPERTY(EditAnywhere, Category = Limit)` — To avoid hitches causing stretch of trail, you can use MaxDeltaTime to clamp the long delta time. If you want 30 fps to set it to 0.03333f ( = 1/30 ).
- L126 _public member_ `float RelaxationSpeedScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trail, meta = (PinHiddenByDefault))`
- L130 _public member_ `FRuntimeFloatCurve TrailRelaxationSpeed;` — `UPROPERTY(EditAnywhere, Category=Trail, meta=(CustomizeProperty))` — How quickly we 'relax' the bones to their animated positions. Time 0 will map to top root joint, time 1 will map to the bottom joint.
- L133 _public member_ `FInputScaleBiasClamp RelaxationSpeedScaleInputProcessor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trail)`
- L136 _public member_ `TArray<FRotationLimit> RotationLimits;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = Limit, meta = (EditCondition =bLimitRotation))`
- L139 _public member_ `TArray<FVector> RotationOffsets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = Limit, meta = (PinHiddenByDefault, EditCondition = bLimitRotation))`
- L143 _public member_ `TArray<FAnimPhysPlanarLimit> PlanarLimits;` — `UPROPERTY(EditAnywhere, Category=Limit, meta = (EditCondition = bUsePlanarLimit))` — List of available planar limits for this node
- L147 _public member_ `float StretchLimit;` — `UPROPERTY(EditAnywhere, Category=Limit)` — If bLimitStretch is true, this indicates how long a bone can stretch beyond its length in the ref-pose.
- L151 _public member_ `FVector FakeVelocity;` — `UPROPERTY(EditAnywhere, Category=Velocity, meta = (PinHiddenByDefault))` — 'Fake' velocity applied to bones.
- L155 _public member_ `FBoneReference BaseJoint;` — `UPROPERTY(EditAnywhere, Category=Velocity)` — Base Joint to calculate velocity from. If none, it will use Component's World Transform. .
- L159 _public member_ `float TrailBoneRotationBlendAlpha_DEPRECATED;` — `UPROPERTY()`
- L165 _public member_ `float LastBoneRotationAnimAlphaBlend;` — `UPROPERTY(EditAnywhere, Category = Rotation, meta = (EditCondition = bReorientParentToChild))` — How to set last bone rotation. It copies from previous joint if alpha is 0.f, or 1.f will use animated pose This alpha dictates the blend between parent joint and animated pose, and how much you'd like to use animated pose for
- L168 _public member_ `float ThisTimstep;` — Internal use - we need the timestep to do the relaxation in CalculateNewBoneTransforms.
- L171 _public member_ `TArray<FVector> TrailBoneLocations;` — Component-space locations of the bones from last frame. Each frame these are moved towards their 'animated' locations.
- L174 _public member_ `TArray<FPerJointTrailSetup> PerJointTrailData;` — Per Joint Trail Set up
- L178 _public member_ `TArray<FColor> TrailDebugColors;` — debug transient data to draw debug better
- L179 _public member_ `TArray<FColor> PlaneDebugColors;`
- L182 _public prototype_ `FAnimNode_Trail();`
- L185 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNode_Base interface
- L186 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;`
- L187 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L191 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L192 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L195 _public prototype_ `void PostLoad();`
- L198 _public prototype_ `void EnsureChainSize();`
- L202 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L205 _private prototype_ `FVector GetAlignVector(EAxis::Type AxisOption, bool bInvert);`
- L208 _private member_ `TArray<int32> ChainBoneIndices;` — skeleton index

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_TwistCorrectiveNode.h` (Public)


#### struct `FReferenceBoneFrame`  
`struct FReferenceBoneFrame`  
_L16-27_
- reflection: `USTRUCT()`
- desc: Reference Bone Frame
- L21 _public member_ `FBoneReference Bone;` — `UPROPERTY(EditAnywhere, Category = "FReferenceBoneFrame")`
- L24 _public member_ `FAxis Axis;` — `UPROPERTY(EditAnywhere, Category = "FReferenceBoneFrame")`
- L26 _public function_ `FReferenceBoneFrame()`

#### struct `FAnimNode_TwistCorrectiveNode`  
`struct FAnimNode_TwistCorrectiveNode : public FAnimNode_SkeletalControlBase`  
_L36-111_
- reflection: `USTRUCT()`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: This is the node that apply corrective morphtarget for twist Good example is that if you twist your neck too far right or left, you're going to see odd stretch shape of neck, This node can detect the angle and apply morphtarget curve This isn't the twist control node for bone twist
- L42 _public member_ `FReferenceBoneFrame BaseFrame;` — `UPROPERTY(EditAnywhere, Category="Reference Frame")` — Base Frame of the reference for the twist node
- L46 _public member_ `FReferenceBoneFrame TwistFrame;` — `UPROPERTY(EditAnywhere, Category="Reference Frame")` — Transform component to use as input
- L50 _public member_ `FAxis TwistPlaneNormalAxis;` — `UPROPERTY(EditAnywhere, Category = "Reference Frame")` — Normal of the Plane that we'd like to calculate angle calculation from in BaseFrame. Please note we're looking for Normal Axis
- L60 _public member_ `float RangeMax;` — `UPROPERTY(EditAnywhere, Category = "Mapping", meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 90.f, ClampMax = 90.f, DisplayName = "Max Angle In Degree"))` — Maximum limit of the input value (mapped to RemappedMax, only used when limiting the source range) We can't go more than 180 right now because this is dot product driver
- L64 _public member_ `float RemappedMin;` — `UPROPERTY(EditAnywhere, Category = "Mapping", meta = (EditCondition = bUseRange, DisplayName = "Mapped Range Min"))` — Minimum value to apply to the destination (remapped from the input range)
- L68 _public member_ `float RemappedMax;` — `UPROPERTY(EditAnywhere, Category = "Mapping", meta = (EditCondition = bUseRange, DisplayName = "Mapped Range Max"))` — Maximum value to apply to the destination (remapped from the input range)
- L72 _public member_ `FAnimCurveParam Curve_DEPRECATED;` — `UPROPERTY()`
- L76 _public member_ `FName CurveName;` — `UPROPERTY(EditAnywhere, Category = "Output Curve")`
- L79 _public prototype_ `FAnimNode_TwistCorrectiveNode();`
- L82 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L83 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;`
- L84 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L88 _public prototype_ `virtual void EvaluateComponentSpaceInternal(FComponentSpacePoseContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L89 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L93 _public prototype_ `bool Serialize(FArchive& Ar);` — Type traits support
- L94 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L99 _protected prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase protected interface
- L103 _private member_ `float ReferenceAngle;` — Reference Pose Angle
- L105 _private member_ `float RangeMaxInRadian;` — Ranged Max in Radian, so that we don't keep having to convert
- L108 _private prototype_ `FVector GetReferenceAxis(FCSPose<FCompactPose>& MeshBases, const FReferenceBoneFrame& Reference) const;` — Get Reference Axis from the MeshBases
- L110 _private prototype_ `float GetAngle(const FVector& Base, const FVector& Twist, const FTransform& ReferencetBoneTransform) const;` — Get Angle of Base, and Twist from Reference Bone Transform

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAnimNode_TwistCorrectiveNode> : public TStructOpsTypeTraitsBase2<FAnimNode_TwistCorrectiveNode>`  
_L114-121_
- inherits: `TStructOpsTypeTraitsBase2<FAnimNode_TwistCorrectiveNode>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L117-120_

#### Free symbols / members of external scopes

- L118 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon434e7ee20103`)
- L119 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon434e7ee20103`)

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/AnimNode_TwoBoneIK.h` (Public)


#### struct `FAnimNode_TwoBoneIK`  
`struct FAnimNode_TwoBoneIK : public FAnimNode_SkeletalControlBase`  
_L20-126_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- L26 _public member_ `FBoneReference IKBone;` — `UPROPERTY(EditAnywhere, Category=IK)` — Name of bone to control. This is the main bone chain to modify from.
- L30 _public member_ `double StartStretchRatio;` — `UPROPERTY(EditAnywhere, Category=IK, meta = (editcondition = "bAllowStretching", ClampMin = "0.0", UIMin = "0.0"))` — Limits to use if stretching is allowed. This value determines when to start stretch. For example, 0.9 means once it reaches 90% of the whole length of the limb, it will start apply.
- L34 _public member_ `double MaxStretchScale;` — `UPROPERTY(EditAnywhere, Category= IK, meta = (editcondition = "bAllowStretching", ClampMin = "0.0", UIMin = "0.0"))` — Limits to use if stretching is allowed. This value determins what is the max stretch scale. For example, 1.5 means it will stretch until 150 % of the whole length of the limb.
- L39 _public member_ `FVector2D StretchLimits_DEPRECATED;` — `UPROPERTY()` — Limits to use if stretching is allowed - old property DEPRECATED
- L43 _public member_ `bool bNoTwist_DEPRECATED;` — `UPROPERTY()` — Whether or not to apply twist on the chain of joints. This clears the twist value along the TwistAxis
- L47 _public member_ `FName JointTargetSpaceBoneName_DEPRECATED;` — `UPROPERTY()` — If JointTargetSpaceBoneName is a bone, this is the bone to use.
- L51 _public member_ `FName EffectorSpaceBoneName_DEPRECATED;` — `UPROPERTY()` — If EffectorLocationSpace is a bone, this is the bone to use.
- L56 _public member_ `FVector EffectorLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector, meta = (PinShownByDefault))` — Effector Location. Target Location to reach.
- L59 _public member_ `FCompactPoseBoneIndex CachedUpperLimbIndex;` — cached limb index for upper
- L62 _public member_ `FBoneSocketTarget EffectorTarget;` — `UPROPERTY(EditAnywhere, Category=Effector)`
- L66 _public member_ `FVector JointTargetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=JointTarget, meta=(PinShownByDefault))` — Joint Target Location. Location used to orient Joint bone.
- L69 _public member_ `FCompactPoseBoneIndex CachedLowerLimbIndex;` — cached limb index for lower
- L72 _public member_ `FBoneSocketTarget JointTarget;` — `UPROPERTY(EditAnywhere, Category = JointTarget)`
- L76 _public member_ `FAxis TwistAxis;` — `UPROPERTY(EditAnywhere, Category = IK, meta = (editcondition = "!bAllowTwist"))` — Specify which axis it's aligned. Used when removing twist
- L88 _public member_ `uint8 bAllowStretching:1;` — `UPROPERTY(EditAnywhere, Category=IK)` — Should stretching be allowed, to be prevent over extension
- L92 _public member_ `uint8 bTakeRotationFromEffectorSpace : 1;` — `UPROPERTY(EditAnywhere, Category=IK)` — Set end bone to use End Effector rotation
- L96 _public member_ `uint8 bMaintainEffectorRelRot : 1;` — `UPROPERTY(EditAnywhere, Category = IK)` — Keep local rotation of end bone
- L100 _public member_ `uint8 bAllowTwist : 1;` — `UPROPERTY(EditAnywhere, Category = IK)` — Whether or not to apply twist on the chain of joints. This clears the twist value along the TwistAxis
- L102 _public prototype_ `FAnimNode_TwoBoneIK();`
- L105 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;` — FAnimNode_Base interface
- L106 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L110 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;` — FAnimNode_SkeletalControlBase interface
- L111 _public prototype_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;`
- L113 _public prototype_ `void ConditionalDebugDraw(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp) const;`
- L116 _public prototype_ `static FTransform GetTargetTransform(const FTransform& InComponentTransform, FCSPose<FCompactPose>& MeshBases, FBoneSocketTarget& InTarget, EBoneControlSpace Space, const FVector& InOffset);`
- L119 _private prototype_ `virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;` — FAnimNode_SkeletalControlBase interface
- L123 _private member_ `FVector CachedJoints[3];`
- L124 _private member_ `FVector CachedJointTargetPos;`

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/BoneControllerSolvers.h` (Public)


#### struct `FIKFootPelvisPullDownSolver`  
`struct FIKFootPelvisPullDownSolver`  
_L14-48_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L20 _public member_ `FVectorRK4SpringInterpolator PelvisAdjustmentInterp;` — `UPROPERTY(EditAnywhere, Category=Settings)` — Specifies the spring interpolation parameters applied during pelvis adjustment
- L25 _public member_ `double PelvisAdjustmentInterpAlpha = 0.5;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0", ClampMax="1.0"))` — Specifies an alpha between the original and final adjusted pelvis locations This is used to retain some degree of the original pelvis motion
- L29 _public member_ `double PelvisAdjustmentMaxDistance = 10.0;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(ClampMin="0.0"))` — Specifies the maximum displacement the pelvis can be adjusted relative to its original location
- L39 _public member_ `double PelvisAdjustmentErrorTolerance = 0.01;` — `UPROPERTY(EditAnywhere, Category=Advanced, meta=(ClampMin="0.001"))` — Specifies the pelvis adjustment distance error that is tolerated for each iteration of the solver When it is detected that the pelvis adjustment distance is incrementing at a value lower or equal to this value for each iteration, the solve will halt. Lower values will marginally increase visual quality at the cost of performance, but may require a higher PelvisAdjustmentMaxIter to be specified The default value of 0.01 specifies 1 centimeter of error
- L44 _public member_ `int32 PelvisAdjustmentMaxIter = 3;` — `UPROPERTY(EditAnywhere, Category=Advanced, meta=(ClampMin="0"))` — Specifies the maximum number of iterations to run for the pelvis adjustment solver Higher iterations will guarantee closer PelvisAdjustmentErrorTolerance convergence at the cost of performance
- L47 _public prototype_ `FTransform Solve(FTransform PelvisTransform, TArrayView<const float> FKFootDistancesToPelvis, TArrayView<const FVector> IKFootLocations, float DeltaTime);` — Iteratively pulls the character pelvis towards the ground based on the relationship of driven IK foot targets versus FK foot limits

### `Source/Runtime/AnimGraphRuntime/Public/BoneControllers/BoneControllerTypes.h` (Public)


#### enum `EWarpingEvaluationMode`  
`enum class EWarpingEvaluationMode : uint8`  
_L13-21_
- reflection: `UENUM(BlueprintInternalUseOnly)`
- desc: Specifies the evaluation mode of an animation warping node
- L16 _public enumerator_ `Manual` — Animation warping evaluation parameters are driven by user settings.
- L20 _public enumerator_ `Graph` — Animation warping evaluation parameters are graph-driven. This means some properties of the node are automatically computed using the accumulated root motion delta contribution of the animation graph leading into it.

#### enum `EWarpingVectorMode`  
`enum class EWarpingVectorMode : uint8`  
_L25-35_
- reflection: `UENUM(BlueprintInternalUseOnly)`
- desc: The supported spaces of a corresponding input vector value
- L28 _public enumerator_ `ComponentSpaceVector` — Component-space input vector
- L30 _public enumerator_ `ActorSpaceVector` — Actor-space input vector
- L32 _public enumerator_ `WorldSpaceVector` — World-space input vector
- L34 _public enumerator_ `IKFootRootLocalSpaceVector` — IK Foot Root relative local-space input vector

#### struct `FWarpingVectorValue`  
`struct FWarpingVectorValue`  
_L39-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: Vector values which may be specified in a configured space
- L45 _public member_ `EWarpingVectorMode Mode = EWarpingVectorMode::ComponentSpaceVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))` — Space of the corresponding Vector value
- L49 _public member_ `FVector Value = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Settings, meta=(PinShownByDefault))` — Specifies a vector relative to the space defined by Mode
- L52 _public prototype_ `FVector AsComponentSpaceDirection(const FAnimInstanceProxy* AnimInstanceProxy, const FTransform& IKFootRootTransform) const;` — Retrieves a normalized Component-space direction from the specified DirectionMode and Direction value

### `Source/Runtime/AnimGraphRuntime/Public/CommonAnimationLibrary.h` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace CommonAnimationLibrary`
- L28 _prototype_ `float ScalarEasing( float Value, const FRuntimeFloatCurve& CustomCurve, EEasingFuncType EasingType = EEasingFuncType::Linear, bool bFlip = false, float Weight = 1.f );` (scope `CommonAnimationLibrary`) — This function perform easing on a float value using a variety of easing types. @param Value The float value to ease @param EasingType The easing function to use @param CustomCurve The curve to use if the easing type is "Custom" @param bFlip If set to true the easing is flipping around @param Weight The amount of easing to use against linear (0.0 to 1.0)
- L52 _prototype_ `FVector RetargetSingleLocation( FVector Location, const FTransform& Source, const FTransform& Target, const FRuntimeFloatCurve& CustomCurve, EEasingFuncType EasingType = EEasingFuncType::Linear, bool bFlipEasing = false, float EasingWeight = 1.f, FVector Axis = FVector(1.f, 0.f, 0.f), float SourceMinimum = -1.f, float SourceMaximum = 1.f, float TargetMinimum = -1.f, float TargetMaximum = 1.f );` (scope `CommonAnimationLibrary`) — This function performs retargeting of translation using an easing function. For this a range of motion needs to be defined given a direction and the constraints. @param Location The input location to be retargeted @param Source The transform to be used as the frame of reference @param Target The transform to be used as the target space @param Axis The direction to use for the range measurement. Defaults to (1.0, 0.0, 0.0) @param SourceMinimum The minimum of the source range @param SourceMaximum The maximum of the source range @param TargetMinimum The minimum of the target range @param TargetMaximum The maximum of the target range @param EasingType The type of easing to apply @param CustomCurve The curve to use if the easing type is "Custom" @param bFlipEasing If set to true the easing is flipping around @param EasingWeight The amount of easing to use against linear (0.0 to 1.0)
- L85 _prototype_ `FQuat RetargetSingleRotation( const FQuat& Rotation, const FTransform& Source, const FTransform& Target, const FRuntimeFloatCurve& CustomCurve, EEasingFuncType EasingType = EEasingFuncType::Linear, bool bFlipEasing = false, float EasingWeight = 1.f, ERotationComponent RotationComponent = ERotationComponent::SwingAngle, FVector TwistAxis = FVector(1.f, 0.f, 0.f), bool bUseAbsoluteAngle = false, float SourceMinimum = 0.0f, float SourceMaximum = 45.f, float TargetMinimum = 0.f, float TargetMaximum = 45.f );` (scope `CommonAnimationLibrary`) — This function performs retargeting of rotation using an easing function. For this a range of motion needs to be defined as a euler angle, swing angle or twist @param Rotation The input rotation to be retargeted @param Source The transform to be used as the frame of reference @param Target The transform to be used as the target space @param CustomCurve The curve to use if the easing type is "Custom" @param bFlipEasing If set to true the easing is flipping around @param EasingWeight The amount of easing to use against linear (0.0 to 1.0) @param RotationComponent The component of the rotation to retarget @param TwistAxis The axis to use when extracting swing / twist rotations @param bUseAbsoluteAngle If set to true negative angles will be flipped to positive. This can be used to mirror the rotation. @param SourceMinimum The minimum of the source range in degrees @param SourceMaximum The maximum of the source range in degrees @param TargetMinimum The minimum of the target range in degrees @param TargetMaximum The maximum of the target range in degrees @param EasingType The type of easing to apply

### `Source/Runtime/AnimGraphRuntime/Public/CommonAnimationTypes.h` (Public)


#### enum `EEasingFuncType`  
`enum class EEasingFuncType : uint8`  
_L13-45_
- reflection: `UENUM()`
- desc: An easing type defining how to ease float values.
- L16 _public enumerator_ `Linear` — Linear easing (no change to the value)
- L18 _public enumerator_ `Sinusoidal` — Easing using a sinus function
- L20 _public enumerator_ `Cubic` — Cubic version of the value (only in)
- L22 _public enumerator_ `QuadraticInOut` — Quadratic version of the value (in and out)
- L24 _public enumerator_ `CubicInOut` — Cubic version of the value (in and out)
- L26 _public enumerator_ `HermiteCubic` — Easing using a cubic hermite function
- L28 _public enumerator_ `QuarticInOut` — Quartic version of the value (in and out)
- L30 _public enumerator_ `QuinticInOut` — Quintic version of the value (in and out)
- L32 _public enumerator_ `CircularIn` — Circular easing (only in)
- L34 _public enumerator_ `CircularOut` — Circular easing (only out)
- L36 _public enumerator_ `CircularInOut` — Circular easing (in and out)
- L38 _public enumerator_ `ExpIn` — Exponential easing (only in)
- L40 _public enumerator_ `ExpOut` — Exponential easing (only out)
- L42 _public enumerator_ `ExpInOut` — Exponential easing (in and out)
- L44 _public enumerator_ `CustomCurve` — Custom - based on an optional Curve

#### enum `ERotationComponent`  
`enum class ERotationComponent : uint8`  
_L49-63_
- reflection: `UENUM()`
- desc: A rotational component. This is used for retargeting, for example.
- L52 _public enumerator_ `EulerX` — Using the X component of the Euler rotation
- L54 _public enumerator_ `EulerY` — Using the Y component of the Euler rotation
- L56 _public enumerator_ `EulerZ` — Using the Z component of the Euler rotation
- L58 _public enumerator_ `QuaternionAngle` — Using the angle of the quaternion
- L60 _public enumerator_ `SwingAngle` — Using the angle of the swing quaternion
- L62 _public enumerator_ `TwistAngle` — Using the angle of the twist quaternion

#### struct `FRotationRetargetingInfo`  
`struct FRotationRetargetingInfo`  
_L71-156_
- reflection: `USTRUCT(BlueprintType)`
- desc: The FRotationRetargetingInfo is used to provide all of the settings required to perform rotational retargeting on a single transform.
- L78 _public function_ `FRotationRetargetingInfo(bool bInEnabled = true) : bEnabled(bInEnabled) , Source(FTransform::Identity) , Target(FTransform::Identity) , RotationComponent(ERotationComponent::SwingAngle) , TwistAxis(FVector(1.f, 0.f, 0.f)) , bUseAbsoluteAngle(false) , SourceMinimum(0.f) , SourceMaximum(45.f) , TargetMinimum(0.f) , TargetMaximum(45.f) , EasingType(EEasingFuncType::Linear) , CustomCurve(FRuntimeFloatCurve()) , bFlipEasing(false) , EasingWeight(1.f) , bClamp(false)` — Default constructor
- L99 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — Set to true this enables retargeting
- L103 _public member_ `FTransform Source;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — The source transform of the frame of reference. The rotation is made relative to this space
- L107 _public member_ `FTransform Target;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — The target transform to project the rotation. In most cases this is the same as Source
- L111 _public member_ `ERotationComponent RotationComponent;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — The rotation component to perform retargeting with
- L115 _public member_ `FVector TwistAxis;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — In case the rotation component is SwingAngle or TwistAngle this vector is used as the twist axis
- L119 _public member_ `bool bUseAbsoluteAngle;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — If set to true the angle will be always positive, thus resulting in mirrored rotation both ways
- L123 _public member_ `float SourceMinimum;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo", meta = (UIMin = "-90.0", UIMax = "90.0"))` — The minimum value of the source angle in degrees
- L127 _public member_ `float SourceMaximum;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo", meta = (UIMin = "-90.0", UIMax = "90.0"))` — The maximum value of the source angle in degrees
- L131 _public member_ `float TargetMinimum;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo", meta = (UIMin = "-90.0", UIMax = "90.0"))` — The minimum value of the target angle in degrees (can be the same as SourceMinimum)
- L135 _public member_ `float TargetMaximum;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo", meta = (UIMin = "-90.0", UIMax = "90.0"))` — The target value of the target angle in degrees (can be the same as SourceMaximum)
- L139 _public member_ `EEasingFuncType EasingType;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — The easing to use - pick linear if you don't want to apply any easing
- L143 _public member_ `FRuntimeFloatCurve CustomCurve;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — Custom curve mapping to apply if bApplyCustomCurve is true
- L147 _public member_ `bool bFlipEasing;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — If set to true the interpolation value for the easing will be flipped (1.0 - Value)
- L151 _public member_ `float EasingWeight;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo", meta = (UIMin = "0.0", UIMax = "1.0"))` — The amount of easing to apply (value should be 0.0 to 1.0)
- L155 _public member_ `bool bClamp;` — `UPROPERTY(EditAnywhere, Category = "FRotationRetargetingInfo")` — If set to true the value for the easing will be clamped between 0.0 and 1.0

### `Source/Runtime/AnimGraphRuntime/Public/IAnimGraphRuntime_SequencerMixerTargetConnector.h` (Public)


#### class `IAnimGraphRuntime_SequencerMixerTargetConnector`  
`class IAnimGraphRuntime_SequencerMixerTargetConnector : public IModularFeature`  
_L9-31_
- inherits: `IModularFeature`
- L13 _public function_ `static FName GetModularFeatureName()`
- L19 _public function_ `static const IAnimGraphRuntime_SequencerMixerTargetConnector* Get()`
- L28 _public prototype_ `virtual ~IAnimGraphRuntime_SequencerMixerTargetConnector() = default;`
- L30 _public prototype_ `virtual void ApplySequencerMixedPose(FPoseContext& Output, FName InTargetName) const = 0;`

### `Source/Runtime/AnimGraphRuntime/Public/KismetAnimationLibrary.h` (Public)


#### class `UKismetAnimationLibrary`  
`class UKismetAnimationLibrary : public UBlueprintFunctionLibrary`  
_L18-226_
- reflection: `UCLASS(meta=(ScriptName="AnimGraphLibrary", BlueprintThreadSafe, DocumentationPolicy="Strict"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: A library of the most common animation blueprint functions.
- L37 _private prototype_ `static void K2_TwoBoneIK( const FVector& RootPos, const FVector& JointPos, const FVector& EndPos, const FVector& JointTarget, const FVector& Effector, FVector& OutJointPos, FVector& OutEndPos, bool bAllowStretching, float StartStretchRatio, float MaxStretchScale );` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (DisplayName = "Two Bone IK Function", ScriptName = "TwoBoneIK", bAllowStretching = "false", StartStretchRatio = "1.0", MaxStretchScale = "1.2"))` — Computes the transform for two bones using inverse kinematics. @param RootPos The input root position of the two bone chain @param JointPos The input center (elbow) position of the two bone chain @param EndPos The input end (wrist) position of the two bone chain @param JointTarget The IK target for the write to reach @param Effector The position of the target effector for the IK Chain. @param OutJointPos The resulting position for the center (elbow) @param OutEndPos The resulting position for the end (wrist) @param bAllowStretching If set to true the bones are allowed to stretch @param StartStretchRatio The ratio at which the bones should start to stretch. The higher the value, the later the stretching wil start. @param MaxStretchScale The maximum multiplier for the stretch to reach.
- L61 _private prototype_ `static FTransform K2_LookAt( const FTransform& CurrentTransform, const FVector& TargetPosition, FVector LookAtVector, bool bUseUpVector, FVector UpVector, float ClampConeInDegree );` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (DisplayName = "Look At Function", ScriptName = "LookAt", bUseUpVector = "false"))` — Computes the transform which is "looking" at target position with a local axis. @param CurrentTransform The input transform to modify @param TargetPosition The position this transform should look at @param LookAtVector The local vector to align with the target @param bUseUpVector If set to true the lookat will also perform a twist rotation @param UpVector The position to use for the upvector target (only used is bUseUpVector is turned on) @param ClampConeInDegree A limit for only allowing the lookat to rotate as much as defined by the float value
- L85 _private prototype_ `static float K2_DistanceBetweenTwoSocketsAndMapRange( const USkeletalMeshComponent* Component, const FName SocketOrBoneNameA, ERelativeTransformSpace SocketSpaceA, const FName SocketOrBoneNameB, ERelativeTransformSpace SocketSpaceB, bool bRemapRange, float InRangeMin, float InRangeMax, float OutRangeMin, float OutRangeMax);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (NotBlueprintThreadSafe, DisplayName = "Get Distance Between Two Sockets", ScriptName = "DistanceBetweenSockets", bRemapRange= "false"))` — Computes the distance between two bones / sockets and can remap the range. @param Component The skeletal component to look for the sockets / bones within @param SocketOrBoneNameA The name of the first socket / bone @param SocketSpaceA The space for the first socket / bone @param SocketOrBoneNameB The name of the second socket / bone @param SocketSpaceB The space for the second socket / bone @param bRemapRange If set to true, the distance will be remapped using the range parameters @param InRangeMin The minimum for the input range (commonly == 0.0) @param InRangeMax The maximum for the input range (the max expected distance) @param OutRangeMin The minimum for the output range (commonly == 0.0) @param OutRangeMax The maximum for the output range (commonly == 1.0)
- L105 _private prototype_ `static FVector K2_DirectionBetweenSockets(const USkeletalMeshComponent* Component, const FName SocketOrBoneNameFrom, const FName SocketOrBoneNameTo);` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (NotBlueprintThreadSafe, DisplayName = "Get Direction Between Sockets", ScriptName = "DirectionBetweenSockets"))` — Computes the direction between two bones / sockets. @param Component The skeletal component to look for the sockets / bones within @param SocketOrBoneNameFrom The name of the first socket / bone @param SocketOrBoneNameTo The name of the second socket / bone
- L121 _private prototype_ `static FVector K2_MakePerlinNoiseVectorAndRemap( float X, float Y, float Z, float RangeOutMinX, float RangeOutMaxX, float RangeOutMinY, float RangeOutMaxY, float RangeOutMinZ, float RangeOutMaxZ );` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (DisplayName = "Make Perlin Noise Vector and Remap", ScriptName = "MakeVectorFromPerlinNoise", RangeOutMinX = "-1.f", RangeOutMaxX = "1.f", RangeOutMinY = "-1.f", RangeOutMaxY = "1.f", RangeOutMinZ = "-1.f", RangeOutMaxZ = "1.f"))` — This function creates perlin noise from input X, Y, Z, and then range map to RangeOut, and out put to OutX, OutY, OutZ @param X The x component for the input position of the noise @param Y The y component for the input position of the noise @param Z The z component for the input position of the noise @param RangeOutMinX The minimum for the output range for the x component @param RangeOutMaxX The maximum for the output range for the x component @param RangeOutMinY The minimum for the output range for the y component @param RangeOutMaxY The maximum for the output range for the y component @param RangeOutMinZ The minimum for the output range for the z component @param RangeOutMaxZ The maximum for the output range for the z component
- L141 _private prototype_ `static float K2_MakePerlinNoiseAndRemap( float Value, float RangeOutMin, float RangeOutMax );` — `UFUNCTION(BlueprintPure, Category = "Animation|Utilities", meta = (DisplayName = "Make Perlin Noise and Remap", ScriptName = "MakeFloatFromPerlinNoise", RangeOutMinX = "-1.f", RangeOutMaxX = "1.f", RangeOutMinY = "-1.f", RangeOutMaxY = "1.f", RangeOutMinZ = "-1.f", RangeOutMaxZ = "1.f"))` — This function creates perlin noise for a single float and then range map to RangeOut @param Value The input value for the noise function @param RangeOutMin The minimum for the output range @param RangeOutMax The maximum for the output range
- L159 _private prototype_ `static float K2_CalculateVelocityFromPositionHistory( float DeltaSeconds, FVector Position, UPARAM(ref) FPositionHistory& History, int32 NumberOfSamples, float VelocityMin, float VelocityMax );` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta = (DisplayName = "Calculate Velocity From Position History", ScriptName = "CalculateVelocityFromPositionHistory", NumberOfSamples = "16", VelocityMin = "0.f", VelocityMax = "128.f"))` — This function calculates the velocity of a position changing over time. You need to hook up a valid PositionHistory variable to this for storage. @param DeltaSeconds The time passed in seconds @param Position The position to track over time. @param History The history to use for storage. @param NumberOfSamples The number of samples to use for the history. The higher the number of samples - the smoother the velocity changes. @param VelocityMin The minimum velocity to use for normalization (if both min and max are set to 0, normalization is turned off) @param VelocityMax The maximum velocity to use for normalization (if both min and max are set to 0, normalization is turned off)
- L187 _private prototype_ `static float K2_CalculateVelocityFromSockets( float DeltaSeconds, USkeletalMeshComponent * Component, const FName SocketOrBoneName, const FName ReferenceSocketOrBone, ERelativeTransformSpace SocketSpace, FVector OffsetInBoneSpace, UPARAM(ref) FPositionHistory& History, int32 NumberOfSamples, float VelocityMin, float VelocityMax, EEasingFuncType EasingType, const FRuntimeFloatCurve& CustomCurve );` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta = (NotBlueprintThreadSafe, DisplayName = "Calculate Velocity From Sockets", ScriptName = "CalculateVelocityFromSockets", NumberOfSamples = "16", VelocityMin = "0.f", VelocityMax = "128.f"))` — This function calculates the velocity of an offset position on a bone / socket over time. The bone's / socket's motion can be expressed within a reference frame (another bone / socket). You need to hook up a valid PositionHistory variable to this for storage. @param DeltaSeconds The time passed in seconds @param Component The skeletal component to look for the bones / sockets @param SocketOrBoneName The name of the bone / socket to track. @param ReferenceSocketOrBone The name of the bone / socket to use as a frame of reference (or None if no frame of reference == world space). @param SocketSpace The space to use for the two sockets / bones @param OffsetInBoneSpace The relative position in the space of the bone / socket to track over time. @param History The history to use for storage. @param NumberOfSamples The number of samples to use for the history. The higher the number of samples - the smoother the velocity changes. @param VelocityMin The minimum velocity to use for normalization (if both min and max are set to 0, normalization is turned off) @param VelocityMax The maximum velocity to use for normalization (if both min and max are set to 0, normalization is turned off) @param EasingType The easing function to use @param CustomCurve The curve to use if the easing type is "Custom"
- L206 _private prototype_ `static void K2_StartProfilingTimer();` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta = (DisplayName = "Start Profiling Timer"))` — This function starts measuring the time for a profiling bracket
- L216 _private prototype_ `static float K2_EndProfilingTimer(bool bLog = true, const FString& LogPrefix = "");` — `UFUNCTION(BlueprintCallable, Category = "Animation|Utilities", meta = (DisplayName = "End Profiling Timer"))` — This function ends measuring a profiling bracket and optionally logs the result @param bLog If set to true the result is logged to the OutputLog @param LogPrefix A prefix to use for the log @result The time spent in milliseconds
- L225 _private prototype_ `static float CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation);` — `UFUNCTION(BlueprintPure, Category="Animation|Utilities")` — Returns degree of the angle between Velocity and Rotation forward vector The range of return will be from [-180, 180]. Useful for feeding directional blendspaces. @param	Velocity		The velocity to use as direction relative to BaseRotation @param	BaseRotation	The base rotation, e.g. of a pawn

### `Source/Runtime/AnimGraphRuntime/Public/KismetAnimationTypes.h` (Public)


#### struct `FPositionHistory`  
`struct FPositionHistory`  
_L17-41_
- reflection: `USTRUCT(BlueprintType, meta = (DocumentationPolicy = "Strict"))`
- desc: An easing type defining how to ease float values. The FPositionHistory is a container to record position changes over time. This is used to calculate velocity of a bone, for example. The FPositionArray also tracks the last index used to allow for reuse of entries (instead of appending to the array all the time).
- L24 _public function_ `FPositionHistory() : Positions(TArray<FVector>()) , Range(0.f) , Velocities(TArray<float>()) , LastIndex(0)` — Default constructor
- L33 _public member_ `TArray<FVector> Positions;` — `UPROPERTY(EditAnywhere, Category = "FPositionHistory")` — The recorded positions
- L37 _public member_ `float Range;` — `UPROPERTY(EditAnywhere, Category = "FPositionHistory", meta = (UIMin = "0.0", UIMax = "1.0"))` — The range for this particular history
- L39 _public member_ `TArray<float> Velocities;`
- L40 _public member_ `uint32 LastIndex;` — The last index used to store a position

### `Source/Runtime/AnimGraphRuntime/Public/LayeredBoneBlendLibrary.h` (Public)


#### struct `FLayeredBoneBlendReference`  
`struct FLayeredBoneBlendReference : public FAnimNodeReference`  
_L14-19_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L18 _public typedef_ `typedef FAnimNode_LayeredBoneBlend FInternalNodeType;`

#### class `ULayeredBoneBlendLibrary`  
`class ULayeredBoneBlendLibrary : public UBlueprintFunctionLibrary`  
_L25-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a layered bone blend anim node.
- L32 _public prototype_ `static FLayeredBoneBlendReference ConvertToLayeredBoneBlend(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Layered Bone Blend", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a layered bone blend context from an anim node context.
- L36 _public function_ `static void ConvertToLayeredBlendPerBonePure(const FAnimNodeReference& Node, FLayeredBoneBlendReference& LayeredBoneBlend, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Layered Bone Blend", meta = (BlueprintThreadSafe, DisplayName = "Convert to Layered Bone Blend"))` — Get a layered bone blend context from an anim node context (pure).
- L45 _public prototype_ `static int32 GetNumPoses(const FLayeredBoneBlendReference& LayeredBoneBlend);` — `UFUNCTION(BlueprintPure, Category = "Layered Bone Blend", meta = (BlueprintThreadSafe))` — Get the number of poses that a layered bone blend node has (this does not include the base pose)
- L55 _public prototype_ `static FLayeredBoneBlendReference SetBlendMask(const FAnimUpdateContext& UpdateContext, const FLayeredBoneBlendReference& LayeredBoneBlend, int32 PoseIndex, FName BlendMaskName);` — `UFUNCTION(BlueprintCallable, Category = "Layered Bone Blend", meta = (BlueprintThreadSafe))` — Sets the currently-used blend mask for a blended input pose by name. @param	UpdateContext		The update context to use. This is used to extract the current skeleton to derive the blend mask from @param	LayeredBoneBlend	A reference to the node @param	PoseIndex			The pose index to set the blend mask for @param	BlendMaskName	The name of the blend mask to use

### `Source/Runtime/AnimGraphRuntime/Public/LinkedAnimGraphLibrary.h` (Public)


#### struct `FLinkedAnimGraphReference`  
`struct FLinkedAnimGraphReference : public FAnimNodeReference`  
_L13-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L17 _public typedef_ `typedef FAnimNode_LinkedAnimGraph FInternalNodeType;`

#### class `ULinkedAnimGraphLibrary`  
`class ULinkedAnimGraphLibrary : public UBlueprintFunctionLibrary`  
_L22-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on anim node contexts
- L29 _public prototype_ `static FLinkedAnimGraphReference ConvertToLinkedAnimGraph(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Linked Anim Graphs", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a linked anim graph reference from an anim node reference
- L33 _public function_ `static void ConvertToLinkedAnimGraphPure(const FAnimNodeReference& Node, FLinkedAnimGraphReference& LinkedAnimGraph, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|Linked Anim Graphs", meta=(BlueprintThreadSafe, DisplayName = "Convert to Linked Anim Graph"))` — Get a linked anim graph reference from an anim node reference (pure)
- L42 _public prototype_ `static bool HasLinkedAnimInstance(const FLinkedAnimGraphReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|Linked Anim Graphs", meta=(BlueprintThreadSafe))` — Returns whether the node hosts an instance (e.g. linked anim graph or layer)
- L46 _public prototype_ `static UAnimInstance* GetLinkedAnimInstance(const FLinkedAnimGraphReference& Node);` — `UFUNCTION(BlueprintPure, Category = "Animation|Linked Anim Graphs", meta=(BlueprintThreadSafe))` — Get the linked instance is hosted by this node. If the node does not host an instance then HasLinkedAnimInstance will return false

### `Source/Runtime/AnimGraphRuntime/Public/MirrorAnimLibrary.h` (Public)


#### struct `FMirrorAnimNodeReference`  
`struct FMirrorAnimNodeReference : public FAnimNodeReference`  
_L14-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L17 _public typedef_ `typedef FAnimNode_MirrorBase FInternalNodeType;`

#### class `UMirrorAnimLibrary`  
`class UMirrorAnimLibrary : public UBlueprintFunctionLibrary`  
_L22-59_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Mirror node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L29 _public prototype_ `static FMirrorAnimNodeReference ConvertToMirrorNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a mirror node context from an anim node context
- L33 _public function_ `static void ConvertToMirrorNodePure(const FAnimNodeReference& Node, FMirrorAnimNodeReference& MirrorNode, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe, DisplayName = "Convert to Mirror Node"))` — Get a mirror context from an anim node context (pure)
- L42 _public prototype_ `static FMirrorAnimNodeReference SetMirror(const FMirrorAnimNodeReference& MirrorNode, bool bInMirror);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe))` — Set the mirror state
- L46 _public prototype_ `static FMirrorAnimNodeReference SetMirrorTransitionBlendTime(const FMirrorAnimNodeReference& MirrorNode, float InBlendTime);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe))` — Set how long to blend using inertialization when switching mirrored state
- L50 _public prototype_ `static bool GetMirror(const FMirrorAnimNodeReference& MirrorNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe))` — Get the mirror state
- L54 _public prototype_ `static UMirrorDataTable* GetMirrorDataTable(const FMirrorAnimNodeReference& MirrorNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe))` — Get MirrorDataTable used to perform mirroring
- L58 _public prototype_ `static float GetMirrorTransitionBlendTime(const FMirrorAnimNodeReference& MirrorNode);` — `UFUNCTION(BlueprintPure, Category = "Animation|Mirroring", meta=(BlueprintThreadSafe))` — Get how long to blend using inertialization when switching mirrored state

### `Source/Runtime/AnimGraphRuntime/Public/ModifyCurveLibrary.h` (Public)


#### struct `FModifyCurveAnimNodeReference`  
`struct FModifyCurveAnimNodeReference : public FAnimNodeReference`  
_L14-18_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L17 _public typedef_ `typedef FAnimNode_ModifyCurve FInternalNodeType;`

#### class `UModifyCurveAnimLibrary`  
`class UModifyCurveAnimLibrary : public UBlueprintFunctionLibrary`  
_L22-54_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations that can be run on a Modify Curve Node via Anim Node Functions such as "On Become Relevant" and "On Update".
- L29 _public prototype_ `static FModifyCurveAnimNodeReference ConvertToModifyCurveNode(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a modify curve node context from an anim node context
- L33 _public function_ `static void ConvertToModifyCurveNodePure(const FAnimNodeReference& Node, FModifyCurveAnimNodeReference& ModifyCurveNode, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation", meta=(BlueprintThreadSafe, DisplayName = "Convert to Modify Curve node"))` — Get a modify curve context from an anim node context (pure)
- L41 _public prototype_ `static FModifyCurveAnimNodeReference SetCurveMap(const FModifyCurveAnimNodeReference& ModifyCurveNode, const TMap<FName, float> & InCurveMap);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))`
- L44 _public prototype_ `static EModifyCurveApplyMode GetApplyMode(const FModifyCurveAnimNodeReference& ModifyCurveNode);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))`
- L47 _public prototype_ `static FModifyCurveAnimNodeReference SetApplyMode(const FModifyCurveAnimNodeReference& ModifyCurveNode, EModifyCurveApplyMode InMode);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))`
- L50 _public prototype_ `static float GetAlpha(const FModifyCurveAnimNodeReference& ModifyCurveNode);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))`
- L53 _public prototype_ `static FModifyCurveAnimNodeReference SetAlpha(const FModifyCurveAnimNodeReference& ModifyCurveNode, float InAlpha);` — `UFUNCTION(BlueprintCallable, Category = "Animation", meta=(BlueprintThreadSafe))`

### `Source/Runtime/AnimGraphRuntime/Public/PlayMontageCallbackProxy.h` (Public)


#### class `UPlayMontageCallbackProxy`  
`class UPlayMontageCallbackProxy : public UObject`  
_L14-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L20 _private member_ `FOnMontagePlayDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable)` — Called when Montage finished playing and wasn't interrupted
- L24 _private member_ `FOnMontagePlayDelegate OnBlendOut;` — `UPROPERTY(BlueprintAssignable)` — Called when Montage starts blending out and is not interrupted
- L28 _private member_ `FOnMontagePlayDelegate OnInterrupted;` — `UPROPERTY(BlueprintAssignable)` — Called when Montage has been interrupted (or failed to play)
- L31 _private member_ `FOnMontagePlayDelegate OnNotifyBegin;` — `UPROPERTY(BlueprintAssignable)`
- L34 _private member_ `FOnMontagePlayDelegate OnNotifyEnd;` — `UPROPERTY(BlueprintAssignable)`
- L38 _private prototype_ `static UPlayMontageCallbackProxy* CreateProxyObjectForPlayMontage( class USkeletalMeshComponent* InSkeletalMeshComponent, class UAnimMontage* MontageToPlay, float PlayRate = 1.f, float StartingPosition = 0.f, FName StartingSection = NAME_None, bool bShouldStopAllMontages = true);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))` — Called to perform the query internally
- L48 _public prototype_ `virtual void BeginDestroy() override;`
- L53 _protected prototype_ `void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L56 _protected prototype_ `void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L59 _protected prototype_ `void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);` — `UFUNCTION()`
- L62 _protected prototype_ `void OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);` — `UFUNCTION()`
- L65 _private member_ `TWeakObjectPtr<UAnimInstance> AnimInstancePtr;`
- L66 _private member_ `int32 MontageInstanceID;`
- L67 _private member_ `uint32 bInterruptedCalledBeforeBlendingOut : 1;`
- L69 _private prototype_ `bool IsNotifyValid(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload) const;`
- L70 _private prototype_ `void UnbindDelegates();`
- L72 _private member_ `FOnMontageBlendingOutStarted BlendingOutDelegate;`
- L73 _private member_ `FOnMontageEnded MontageEndedDelegate;`
- L77 _protected prototype_ `bool PlayMontage( class USkeletalMeshComponent* InSkeletalMeshComponent, class UAnimMontage* MontageToPlay, float PlayRate = 1.f, float StartingPosition = 0.f, FName StartingSection = NAME_None, bool bShouldStopAllMontages = true);` — Attempts to play a montage with the specified settings. Returns whether it started or not.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontagePlayDelegate, FName, NotifyName);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontagePlayDelegate, FName, NotifyName);`

### `Source/Runtime/AnimGraphRuntime/Public/RBF/RBFInterpolator.h` (Public)


#### class `FRBFInterpolatorBase`  
`class FRBFInterpolatorBase`  
_L138-147_
- desc: An implementation detail for the RBF interpolator to hide the use of Eigen from components outside AnimGraphRuntime.
- L141 _protected prototype_ `bool SetUpperKernel(const TArrayView<float>& UpperKernel, int32 Size);`
- L145 _public member_ `TArray<float> Coeffs;`
- L146 _public member_ `bool bIsValid = false;`

#### class `TRBFInterpolator`  
`template<typename T> class TRBFInterpolator : public FRBFInterpolatorBase`  
_L151-345_
- inherits: `FRBFInterpolatorBase`
- L155 _public typedef_ `using WeightFuncT = TFunction<float(const T& A, const T& B)>;`
- L157 _public prototype_ `TRBFInterpolator() = default;`
- L163 _public function_ `TRBFInterpolator( const TArrayView<T>& InNodes, WeightFuncT InWeightFunc) : Nodes(InNodes) , WeightFunc(InWeightFunc)` — Construct an RBF interpolator, taking in a set of sparse nodes and a symmetric weighing function that computes the distance between two nodes, and, optionally, smooths the distance with a smoothing kernel.
- L172 _public prototype_ `TRBFInterpolator(const TRBFInterpolator<T>&) = default;`
- L173 _public prototype_ `TRBFInterpolator(TRBFInterpolator<T>&&) = default;`
- L174 _public prototype_ `TRBFInterpolator<T>& operator=(const TRBFInterpolator<T>&) = default;`
- L175 _public prototype_ `TRBFInterpolator<T>& operator=(TRBFInterpolator<T>&&) = default;`
- L181 _public function_ `template<typename U, typename InAllocator> void Interpolate( TArray<float, InAllocator>& OutWeights, const U& Value, bool bClip = true, bool bNormalize = false) const` — Given a value, compute the weight values to use to calculate each node's contribution to that value's location.
- L277 _public function_ `static bool GetIdenticalNodePairs( const TArrayView<T>& InNodes, WeightFuncT InWeightFunc, TArray<TTuple<int, int>>& OutInvalidPairs )` — Returns a list of integer pairs indicating which distinct pair of nodes have the same weight as a pair of the same node. These result in an ill-formed coefficient matrix which kills the interpolation. The user can then either simply remove one of the pairs and retry, or warn the user that they have an invalid setup.
- L313 _private function_ `void MakeUpperKernel()`
- L343 _private member_ `TArrayView<T> Nodes;`
- L344 _private member_ `WeightFuncT WeightFunc;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace RBFDistanceMetric`
- L19 _function_ `static inline double Euclidean(const FVector& A, const FVector& B)` (scope `RBFDistanceMetric`) — Returns the Euclidean (L2) distance between two coordinate vectors.
- L25 _function_ `static inline double Manhattan(const FVector& A, const FVector& B)` (scope `RBFDistanceMetric`) — Returns the Manhattan (L1), or Taxi-cab distance between two coordinate vectors.
- L33 _function_ `static inline double ArcLength(const FVector& A, const FVector B)` (scope `RBFDistanceMetric`) — Returns the arc length between two unit vectors (i.e. the distance between two points on a unit sphere, traveling along the surface of the sphere)
- L42 _function_ `static inline double Euclidean(const FRotator& A, const FRotator& B)` (scope `RBFDistanceMetric`) — Returns a straight-up Euclidean distance between two rotation values expressed in radians.
- L54 _function_ `static inline double ArcLength(const FRotator& A, const FRotator& B)` (scope `RBFDistanceMetric`) — Returns the arc-length distance, on a unit sphere, between two rotation vectors.
- L61 _function_ `static inline double Euclidean(const FQuat& A, const FQuat& B)` (scope `RBFDistanceMetric`) — Returns the Euclidean (L2) distance between two quaternion values expressed.
- L68 _function_ `static inline double ArcLength(const FQuat& A, const FQuat& B)` (scope `RBFDistanceMetric`) — Returns the arc-length distance, on a unit sphere, between two quaternions.
- L76 _function_ `static inline double SwingAngle(const FQuat& A, const FQuat& B, const FVector& TwistAxis)` (scope `RBFDistanceMetric`) — Returns the swing arc length distance between two quaternions, using a specific twist basis vector as reference.
- L87 _function_ `static inline double TwistAngle(const FQuat& A, const FQuat& B, const FVector& TwistAxis)` (scope `RBFDistanceMetric`) — Returns the twist arc length distance between two quaternions, using a specific twist basis vector as reference.
- L98 _namespace_ `namespace RBFKernel`
- L101 _function_ `static inline float Linear(float Value, float Sigma)` (scope `RBFKernel`) — A simple linear falloff, clamping at zero out when the norm of Value exceeds Sigma
- L107 _function_ `static inline float Gaussian(float Value, float Sigma)` (scope `RBFKernel`) — A gaussian falloff
- L113 _function_ `static inline float Exponential(float Value, float Sigma)` (scope `RBFKernel`) — An exponential falloff with a sharp peak
- L120 _function_ `static inline float Cubic(float Value, float Sigma)` (scope `RBFKernel`) — A cubic falloff, with identical clamping behavior to the linear falloff, but with a smooth peak
- L128 _function_ `static inline float Quintic(float Value, float Sigma)` (scope `RBFKernel`) — A quintic falloff, with identical clamping behavior to the linear falloff, but with a flatter peak than cubic

### `Source/Runtime/AnimGraphRuntime/Public/RBF/RBFSolver.h` (Public)


#### enum `ERBFSolverType`  
`enum class ERBFSolverType : uint8`  
_L22-38_
- reflection: `UENUM()`
- desc: The solver type to use. The two solvers have different requirements.
- L28 _public enumerator_ `Additive` — The additive solver sums up contributions from each target. It's faster but may require more targets for a good coverage, and requires the normalization step to be performed for smooth results.
- L37 _public enumerator_ `Interpolative` — The interpolative solver interpolates the values from each target based on distance. As long as the input values are within the area bounded by the targets, the interpolation is well-behaved and return weight values within the 0% - 100% limit with no normalization required. Interpolation also gives smoother results, with fewer targets, than additive but at a higher computational cost.

#### enum `ERBFFunctionType`  
`enum class ERBFFunctionType : uint8`  
_L42-56_
- reflection: `UENUM()`
- desc: Function to use for each target falloff
- L44 _public enumerator_ `Gaussian`
- L46 _public enumerator_ `Exponential`
- L48 _public enumerator_ `Linear`
- L50 _public enumerator_ `Cubic`
- L52 _public enumerator_ `Quintic`
- L55 _public enumerator_ `DefaultFunction` — Uses the setting of the parent container

#### enum `ERBFDistanceMethod`  
`enum class ERBFDistanceMethod : uint8`  
_L60-76_
- reflection: `UENUM()`
- desc: Method for determining distance from input to targets
- L63 _public enumerator_ `Euclidean` — Standard n-dimensional distance measure
- L66 _public enumerator_ `Quaternion` — Treat inputs as quaternion
- L69 _public enumerator_ `SwingAngle` — Treat inputs as quaternion, and find distance between rotated TwistAxis direction
- L72 _public enumerator_ `TwistAngle` — Treat inputs as quaternion, and find distance between rotations around the TwistAxis direction
- L75 _public enumerator_ `DefaultMethod` — Uses the setting of the parent container

#### enum `ERBFNormalizeMethod`  
`enum class ERBFNormalizeMethod : uint8`  
_L80-107_
- reflection: `UENUM()`
- desc: Method to normalize weights
- L83 _public enumerator_ `OnlyNormalizeAboveOne` — Only normalize above one
- L89 _public enumerator_ `AlwaysNormalize` — Always normalize. Zero distribution weights stay zero.
- L98 _public enumerator_ `NormalizeWithinMedian` — Normalize only within reference median. The median is a cone with a minimum and maximum angle within which the value will be interpolated between non-normalized and normalized. This helps to define the volume in which normalization is always required.
- L105 _public enumerator_ `NoNormalization` — Don't normalize at all. This should only be used with the interpolative method, if it is known that all input values will be within the area bounded by the targets.

#### struct `FRBFEntry`  
`struct FRBFEntry`  
_L111-138_
- reflection: `USTRUCT()`
- desc: Struct storing a particular entry within the RBF
- L117 _public member_ `TArray<float> Values;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Set of values for this target, size must be TargetDimensions
- L120 _public prototype_ `FRotator AsRotator(int32 Index) const;` — Return a target as an rotator, assuming Values is a sequence of Euler entries. Index is which Euler to convert.
- L123 _public prototype_ `FQuat AsQuat(int32 Index) const;` — Return a target as a quaternion, assuming Values is a sequence of Euler entries. Index is which Euler to convert.
- L125 _public prototype_ `FVector AsVector(int32 Index) const;`
- L129 _public prototype_ `void AddFromRotator(const FRotator& InRot);` — Set this entry to 3 floats from supplied rotator
- L131 _public prototype_ `void AddFromVector(const FVector& InVector);` — Set this entry to 3 floats from supplied vector
- L134 _public function_ `int32 GetDimensions() const` — Return dimensionality of this target

#### struct `FRBFTarget`  
`struct FRBFTarget : public FRBFEntry`  
_L142-177_
- reflection: `USTRUCT()`
- inherits: `FRBFEntry`
- desc: Data about a particular target in the RBF, including scaling factor
- L148 _public member_ `float ScaleFactor;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — How large the influence of this target.
- L154 _public member_ `bool bApplyCustomCurve;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Whether we want to apply an additional custom curve when activating this target. Ignored if the solver type is Interpolative.
- L159 _public member_ `FRichCurve CustomCurve;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Custom curve to apply to activation of this target, if bApplyCustomCurve is true. Ignored if the solver type is Interpolative.
- L164 _public member_ `ERBFDistanceMethod DistanceMethod;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Override the distance method used to calculate the distance from this target to the input. Ignored if the solver type is Interpolative.
- L169 _public member_ `ERBFFunctionType FunctionType;` — `UPROPERTY(EditAnywhere, Category = RBFData)` — Override the falloff function used to smooth the distance from this target to the input. Ignored if the solver type is Interpolative.
- L171 _public function_ `FRBFTarget() : ScaleFactor(1.f) , bApplyCustomCurve(false) , DistanceMethod(ERBFDistanceMethod::DefaultMethod) , FunctionType(ERBFFunctionType::DefaultFunction)`

#### struct `FRBFOutputWeight`  
`struct FRBFOutputWeight`  
_L180-196_
- desc: Struct for storing RBF results - target index and corresponding weight
- L183 _public member_ `int32 TargetIndex;` — Index of target
- L185 _public member_ `float TargetWeight;` — Weight of target
- L187 _public function_ `FRBFOutputWeight(int32 InTargetIndex, float InTargetWeight) : TargetIndex(InTargetIndex) , TargetWeight(InTargetWeight)`
- L192 _public function_ `FRBFOutputWeight() : TargetIndex(0) , TargetWeight(0.f)`

#### struct `FRBFParams`  
`struct FRBFParams`  
_L200-259_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters used by RBF solver
- L206 _public member_ `int32 TargetDimensions;` — `UPROPERTY()` — How many dimensions input data has
- L214 _public member_ `ERBFSolverType SolverType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)` — Specifies the type of solver to use. The additive solver requires normalization, for the most part, whereas the Interpolative solver is not as reliant on it. The interpolative solver also has smoother blending, whereas the additive solver requires more targets but has a more precise control over the influence of each target.
- L219 _public member_ `float Radius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData, meta = (EditCondition = "!bAutomaticRadius"))` — Default radius for each target.
- L223 _public member_ `bool bAutomaticRadius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)` — Automatically pick the radius based on the average distance between targets
- L226 _public member_ `ERBFFunctionType Function;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)`
- L229 _public member_ `ERBFDistanceMethod DistanceMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)`
- L233 _public member_ `TEnumAsByte<EBoneAxis> TwistAxis;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)` — Axis to use when DistanceMethod is SwingAngle
- L237 _public member_ `float WeightThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)` — Weight below which we shouldn't bother returning a contribution from a target
- L241 _public member_ `ERBFNormalizeMethod NormalizeMethod;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData)` — Method to use for normalizing the weight
- L245 _public member_ `FVector MedianReference;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData, meta = (EditCondition = "NormalizeMethod == ERBFNormalizeMethod::NormalizeWithinMedian"))` — Rotation or position of median (used for normalization)
- L249 _public member_ `float MedianMin;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData, meta = (UIMin = "0", UIMax = "90", EditCondition = "NormalizeMethod == ERBFNormalizeMethod::NormalizeWithinMedian"))` — Minimum distance used for median
- L253 _public member_ `float MedianMax;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RBFData, meta = (UIMin = "0", UIMax = "90", EditCondition = "NormalizeMethod == ERBFNormalizeMethod::NormalizeWithinMedian"))` — Maximum distance used for median
- L255 _public prototype_ `FRBFParams();`
- L258 _public prototype_ `FVector GetTwistAxisVector() const;` — Util for returning unit direction vector for swing axis

#### struct `FRBFSolver`  
`struct FRBFSolver`  
_L264-289_
- desc: Library of Radial Basis Function solver functions
- L268 _public prototype_ `static bool ValidateTargets(const FRBFParams& Params, const TArray<FRBFTarget>& Targets, TArray<int>& InvalidTargets);` — Given a list of targets, verify which ones are valid for solving the RBF setup. This is mostly about removing identical targets which invalidates the interpolative solver. Returns true if all targets are valid.
- L271 _public prototype_ `static TSharedPtr<const FRBFSolverData> InitSolver(const FRBFParams& Params, const TArray<FRBFTarget>& Targets);` — Given a set of targets and new input entry, give list of activated targets with weights
- L273 _public prototype_ `static bool IsSolverDataValid(const FRBFSolverData& SolverData, const FRBFParams& Params, const TArray<FRBFTarget>& Targets);`
- L276 _public prototype_ `static void Solve(const FRBFSolverData& SolverData, const FRBFParams& Params, const TArray<FRBFTarget>& Targets, const FRBFEntry& Input, TArray<FRBFOutputWeight>& OutputWeights);` — Given a set of targets and new input entry, give list of activated targets with weights
- L279 _public prototype_ `static bool FindTargetNeighbourDistances(const FRBFParams& Params, const TArray<FRBFTarget>& Targets, TArray<float>& NeighbourDists);` — Util to find distance to nearest neighbour target for each target
- L282 _public prototype_ `static float FindDistanceBetweenEntries(const FRBFEntry& A, const FRBFEntry& B, const FRBFParams& Params, ERBFDistanceMethod OverrideMethod = ERBFDistanceMethod::DefaultMethod);` — Util to find distance between two entries, using provided params
- L285 _public prototype_ `static float GetRadiusForTarget(const FRBFTarget& Target, const FRBFParams& Params);` — Returns the radius for a given target
- L288 _public prototype_ `static float GetOptimalRadiusForTargets(const FRBFParams& Params, const TArray<FRBFTarget>& Targets);` — Compute the optimal radius for the given targets. Returns the radius

### `Source/Runtime/AnimGraphRuntime/Public/SequenceEvaluatorLibrary.h` (Public)


#### struct `FSequenceEvaluatorReference`  
`struct FSequenceEvaluatorReference : public FAnimNodeReference`  
_L15-20_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L19 _public typedef_ `typedef FAnimNode_SequenceEvaluator FInternalNodeType;`

#### class `USequenceEvaluatorLibrary`  
`class USequenceEvaluatorLibrary : public UBlueprintFunctionLibrary`  
_L25-70_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a sequence evaluator anim node Note: Experimental and subject to change!
- L32 _public prototype_ `static FSequenceEvaluatorReference ConvertToSequenceEvaluator(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a sequence evaluator context from an anim node context
- L36 _public function_ `static void ConvertToSequenceEvaluatorPure(const FAnimNodeReference& Node, FSequenceEvaluatorReference& SequenceEvaluator, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta=(BlueprintThreadSafe, DisplayName = "Convert to Sequence Evaluator"))` — Get a sequence evaluator context from an anim node context (pure)
- L45 _public prototype_ `static FSequenceEvaluatorReference SetExplicitTime(const FSequenceEvaluatorReference& SequenceEvaluator, float Time);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta=(BlueprintThreadSafe))` — Set the current accumulated time of the sequence evaluator
- L49 _public prototype_ `static FSequenceEvaluatorReference SetExplicitFrame(const FSequenceEvaluatorReference& SequenceEvaluator, int32 Frame);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta=(BlueprintThreadSafe))` — Set the current accumulated time, using a frame number, of the sequence evaluator
- L53 _public prototype_ `static FSequenceEvaluatorReference AdvanceTime(const FAnimUpdateContext& UpdateContext, const FSequenceEvaluatorReference& SequenceEvaluator, float PlayRate = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Advance the current accumulated time of the sequence evaluator
- L57 _public prototype_ `static FSequenceEvaluatorReference SetSequence(const FSequenceEvaluatorReference& SequenceEvaluator, UAnimSequenceBase* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta=(BlueprintThreadSafe))` — Set the current sequence of the sequence evaluator
- L61 _public prototype_ `static FSequenceEvaluatorReference SetSequenceWithInertialBlending(const FAnimUpdateContext& UpdateContext, const FSequenceEvaluatorReference& SequenceEvaluator, UAnimSequenceBase* Sequence, float BlendTime = 0.2f);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta=(BlueprintThreadSafe))` — Set the current sequence of the sequence evaluator with an inertial blend time
- L65 _public prototype_ `static float GetAccumulatedTime(const FSequenceEvaluatorReference& SequenceEvaluator);` — `UFUNCTION(BlueprintPure, Category = "Sequence Evaluator", meta = (BlueprintThreadSafe))` — Gets the current accumulated time of the sequence evaluator
- L69 _public prototype_ `static UAnimSequenceBase* GetSequence(const FSequenceEvaluatorReference& SequenceEvaluator);` — `UFUNCTION(BlueprintPure, Category = "Sequence Evaluator", meta = (BlueprintThreadSafe))` — Gets the current sequence of the sequence evaluator

### `Source/Runtime/AnimGraphRuntime/Public/SequencePlayerLibrary.h` (Public)


#### struct `FSequencePlayerReference`  
`struct FSequencePlayerReference : public FAnimNodeReference`  
_L15-20_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L19 _public typedef_ `typedef FAnimNode_SequencePlayer FInternalNodeType;`

#### class `USequencePlayerLibrary`  
`class USequencePlayerLibrary : public UBlueprintFunctionLibrary`  
_L25-94_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a sequence player anim node Note: Experimental and subject to change!
- L32 _public prototype_ `static FSequencePlayerReference ConvertToSequencePlayer(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a sequence player context from an anim node context
- L36 _public function_ `static void ConvertToSequencePlayerPure(const FAnimNodeReference& Node, FSequencePlayerReference& SequencePlayer, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe, DisplayName = "Convert to Sequence Player"))` — Get a sequence player context from an anim node context (pure)
- L45 _public prototype_ `static FSequencePlayerReference SetAccumulatedTime(const FSequencePlayerReference& SequencePlayer, float Time);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Set the current accumulated time of the sequence player
- L53 _public prototype_ `static FSequencePlayerReference SetStartPosition(const FSequencePlayerReference& SequencePlayer, float StartPosition);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Set the start position of the sequence player. If this is called from On Become Relevant or On Initial Update then it should be accompanied by a call to SetAccumulatedTime to achieve the desired effect of resetting the play time of a sequence player.
- L57 _public prototype_ `static FSequencePlayerReference SetPlayRate(const FSequencePlayerReference& SequencePlayer, float PlayRate);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Set the play rate of the sequence player
- L61 _public prototype_ `static FSequencePlayerReference SetSequence(const FSequencePlayerReference& SequencePlayer, UAnimSequenceBase* Sequence);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Set the current sequence of the sequence player
- L65 _public prototype_ `static FSequencePlayerReference SetSequenceWithInertialBlending(const FAnimUpdateContext& UpdateContext, const FSequencePlayerReference& SequencePlayer, UAnimSequenceBase* Sequence, float BlendTime = 0.2f);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Set the current sequence of the sequence player with an inertial blend time
- L69 _public prototype_ `static FSequencePlayerReference GetSequence(const FSequencePlayerReference& SequencePlayer, UPARAM(Ref) UAnimSequenceBase*& SequenceBase);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Sequences", meta = (BlueprintThreadSafe, DeprecatedFunction))` — Get the current sequence of the sequence player - DEPRECATED, please use pure version
- L73 _public prototype_ `static UAnimSequenceBase* GetSequencePure(const FSequencePlayerReference& SequencePlayer);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe, DisplayName = "Get Sequence"))` — Get the current sequence of the sequence player
- L77 _public prototype_ `static float GetAccumulatedTime(const FSequencePlayerReference& SequencePlayer);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Gets the current accumulated time of the sequence player
- L81 _public prototype_ `static float GetStartPosition(const FSequencePlayerReference& SequencePlayer);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Get the start position of the sequence player
- L85 _public prototype_ `static float GetPlayRate(const FSequencePlayerReference& SequencePlayer);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Get the play rate of the sequence player
- L89 _public prototype_ `static bool GetLoopAnimation(const FSequencePlayerReference& SequencePlayer);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Get the looping state of the sequence player
- L93 _public prototype_ `static float ComputePlayRateFromDuration(const FSequencePlayerReference& SequencePlayer, float Duration = 1.f);` — `UFUNCTION(BlueprintPure, Category = "Animation|Sequences", meta = (BlueprintThreadSafe))` — Returns the Play Rate to provide when playing this animation if a specific animation duration is desired

### `Source/Runtime/AnimGraphRuntime/Public/SequencerAnimationOverride.h` (Public)


#### class `USequencerAnimationOverride`  
`class USequencerAnimationOverride : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`
- desc: Sequencer Animation Track Override interface. Anim blueprints can override this to provide Sequencer with instructions on how to override this blueprint during Sequencer takeover.

#### class `ISequencerAnimationOverride`  
`class ISequencerAnimationOverride`  
_L26-64_
- L34 _public prototype_ `bool AllowsCinematicOverride() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Sequencer", meta = (CallInEditor = "true"))` — Whether this animation blueprint allows Sequencer to override this anim instance and replace it during Sequencer playback.
- L36 _public function_ `virtual bool AllowsCinematicOverride_Implementation() const`
- L42 _public prototype_ `TArray<FName> GetSequencerAnimSlotNames() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Sequencer", meta = (CallInEditor = "true"))` — Should return a list of valid slot names for Sequencer to output to in the case that Sequencer is not permitted to override the anim instance. Will be chosen by the user in drop down on the skeletal animation section properties. Should be named descriptively, as in some contexts (UEFN), the user will not be able to view the animation blueprint itself to determine the mixing behavior of the slot.
- L44 _public function_ `virtual TArray<FName> GetSequencerAnimSlotName_Implementation() const`
- L46 _public function_ `static TScriptInterface<ISequencerAnimationOverride> GetSequencerAnimOverride(USkeletalMeshComponent* SkeletalMeshComponent)`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ANIMGRAPHRUNTIME_API`

### `Source/Runtime/AnimGraphRuntime/Public/SequencerAnimationSupport.h` (Public)


#### class `USequencerAnimationSupport`  
`class USequencerAnimationSupport : public UInterface`  
_L22-25_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint), MinimalAPI)`
- inherits: `UInterface`

#### class `ISequencerAnimationSupport`  
`class ISequencerAnimationSupport`  
_L27-50_
- L32 _private prototype_ `virtual UAnimInstance* GetSourceAnimInstance() = 0;` — Source Animation Getter for the support of the Sequencer Animation Track interface
- L33 _private prototype_ `virtual void SetSourceAnimInstance(UAnimInstance* SourceAnimInstance) = 0;`
- L34 _private prototype_ `virtual bool DoesSupportDifferentSourceAnimInstance() const = 0;`
- L36 _private prototype_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InPosition, float Weight, bool bFireNotifies) = 0;` — Update an animation sequence player in this instance
- L37 _private prototype_ `virtual void UpdateAnimTrack(UAnimSequenceBase* InAnimSequence, int32 SequenceId, float InFromPosition, float InToPosition, float Weight, bool bFireNotifies) = 0;`
- L40 _private prototype_ `virtual void ConstructNodes() = 0;` — Construct all nodes in this instance
- L43 _private prototype_ `virtual void ResetNodes() = 0;` — Reset all nodes in this instance
- L46 _private prototype_ `virtual void ResetPose() = 0;` — Reset the pose for this instance
- L49 _private prototype_ `virtual void SavePose() = 0;` — Saved the named pose to restore after

### `Source/Runtime/AnimGraphRuntime/Public/SkeletalControlLibrary.h` (Public)


#### struct `FSkeletalControlReference`  
`struct FSkeletalControlReference : public FAnimNodeReference`  
_L14-19_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FAnimNodeReference`
- L18 _public typedef_ `typedef FAnimNode_SkeletalControlBase FInternalNodeType;`

#### class `USkeletalControlLibrary`  
`class USkeletalControlLibrary : public UBlueprintFunctionLibrary`  
_L24-49_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Exposes operations to be performed on a skeletal control anim node Note: Experimental and subject to change!
- L31 _public prototype_ `static FSkeletalControlReference ConvertToSkeletalControl(const FAnimNodeReference& Node, EAnimNodeReferenceConversionResult& Result);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Skeletal Controls", meta=(BlueprintThreadSafe, ExpandEnumAsExecs = "Result"))` — Get a skeletal control from an anim node
- L35 _public function_ `static void ConvertToSkeletalControlPure(const FAnimNodeReference& Node, FSkeletalControlReference& SkeletalControl, bool& Result)` — `UFUNCTION(BlueprintPure, Category = "Animation|Skeletal Controls", meta=(BlueprintThreadSafe, DisplayName = "Convert to Skeletal Control"))` — Get a skeletal control from an anim node (pure)
- L44 _public prototype_ `static FSkeletalControlReference SetAlpha(const FSkeletalControlReference& SkeletalControl, float Alpha);` — `UFUNCTION(BlueprintCallable, Category = "Animation|Skeletal Controls", meta=(BlueprintThreadSafe))` — Set the alpha value of this skeletal control
- L48 _public prototype_ `static float GetAlpha(const FSkeletalControlReference& SkeletalControl);` — `UFUNCTION(BlueprintPure, Category = "Animation|Skeletal Controls", meta=(BlueprintThreadSafe))` — Get the alpha value of this skeletal control
