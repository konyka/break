# Plugins / EvaluationNotifiesRuntime

- module root: `Plugins/Experimental/EvaluationNotifies/Source/Runtime`
- headers: 6; symbols: 186
- symbol kinds: class=5, enum=2, enumerator=10, function=12, macro=1, member=112, namespace=2, prototype=26, struct=15, typedef=1
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, AnimationWarpingRuntime, Core, CoreUObject, Engine, RigVM, UAF, UAFAnimGraph

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Private/AnimNext/AnimNextAlignment.h` (Private)


#### struct `AlignmentAnimTrajectoryData`  
`struct AlignmentAnimTrajectoryData`  
_L10-16_
- L12 _public member_ `FTransform TargetTransform;`
- L13 _public member_ `TArray<FTransform> Trajectory;`
- L14 _public member_ `TArray<float> TranslationCurve;`
- L15 _public member_ `TArray<float> RotationCurve;`

#### struct `FEvaluationNotify_AlignmentInstance`  
`struct FEvaluationNotify_AlignmentInstance : public FEvaluationNotify_BaseInstance`  
_L20-44_
- reflection: `USTRUCT()`
- inherits: `FEvaluationNotify_BaseInstance`
- L23 _public prototype_ `virtual void Start() override;`
- L24 _public prototype_ `virtual bool GetTargetTransform(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& TraitInstanceData, FTransform& TargetTranform);`
- L25 _public prototype_ `virtual void Update(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& InstanceData, UE::UAF::FEvaluationVM& VM) override;`
- L27 _public prototype_ `float GetWeight(float Time, const FAlignmentWarpCurve& WarpCurve) const;`
- L29 _public member_ `FBoneReference AlignBone;`
- L30 _public member_ `bool bDisabled = false;`
- L31 _public member_ `bool bFirstFrame = true;`
- L32 _public member_ `float ActualStartTime = 0;`
- L33 _public member_ `float RoundedEndTime = 0;`
- L34 _public member_ `float PreviousFrame = 0;`
- L36 _public member_ `FTransform StartingRootTransform;`
- L37 _public member_ `FTransform TargetTransform;`
- L39 _public member_ `FQuat FilteredSteeringTarget = FQuat::Identity;`
- L40 _public member_ `FQuaternionSpringState TargetSmoothingState;`
- L42 _public member_ `TArray<FTransform> WarpedTrajectory;`
- L43 _public member_ `AlignmentAnimTrajectoryData AnimTrajectoryData;`

#### struct `FEvaluationNotify_AlignToGroundInstance`  
`struct FEvaluationNotify_AlignToGroundInstance : public FEvaluationNotify_AlignmentInstance`  
_L47-52_
- reflection: `USTRUCT()`
- inherits: `FEvaluationNotify_AlignmentInstance`
- L50 _public prototype_ `virtual void End(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& TraitInstanceData) override;`
- L51 _public prototype_ `virtual bool GetTargetTransform(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& TraitInstanceData, FTransform& TargetTranform);`

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Public/AnimNext/EvaluationNotifiesTrait.h` (Public)


#### struct `FEvaluationNotifiesTraitSharedData`  
`struct FEvaluationNotifiesTraitSharedData : public FAnimNextTraitSharedData`  
_L24-33_
- reflection: `USTRUCT(meta = (DisplayName = "EvaluationNotifies"))`
- inherits: `FAnimNextTraitSharedData`
- desc: Data needed to execute steering Some steering data such as current anim asset / playback time is acquired via trait stack interfaces

#### struct `UE::UAF::FEvaluationNotifiesTrait`  
`struct FEvaluationNotifiesTrait : FAdditiveTrait, ITimelinePlayer, IUpdate, IEvaluate`  
_L40-79_
- inherits: `FAdditiveTrait,ITimelinePlayer,IUpdate,IEvaluate`
- desc: this trait will run evaluation time code for notifies which have a registered handler
- L44 _public typedef_ `using FSharedData = FEvaluationNotifiesTraitSharedData;`
- L69 _public prototype_ `virtual void AdvanceBy(FExecutionContext& Context, const TTraitBinding<ITimelinePlayer>& Binding, float DeltaTime, bool bDispatchEvents) const override;` — ITimelinePlayer impl
- L72 _public prototype_ `virtual void PostEvaluate(FEvaluateTraversalContext& Context, const TTraitBinding<IEvaluate>& Binding) const override;` — IEvaluate impl
- L74 _public prototype_ `static void RegisterEvaluationHandler(UClass* NotifyType, UScriptStruct* Handler);`
- L75 _public prototype_ `static void UnregisterEvaluationHandler(UClass* NotifyType);`
- L78 _private member_ `static TMap<UClass*, UScriptStruct*> NotifyEvaluationHandlerMap;`

#### struct `UE::UAF::FEvaluationNotifiesTrait::FInstanceData`  
`struct FInstanceData : FTrait::FInstanceData`  
_L46-66_
- inherits: `FTrait::FInstanceData`
- L48 _public prototype_ `void Destruct(const FExecutionContext& Context, const FTraitBinding& Binding);`
- L51 _public member_ `float DeltaTime = 0.f;` — Delta in seconds between updates, populated during PreUpdate
- L54 _public member_ `FOnExtractRootMotionAttribute OnExtractRootMotionAttribute = FOnExtractRootMotionAttribute();` — Callback provided by attribute trait on stack to evaluate root motion at a later time
- L57 _public member_ `FTransform RootBoneTransform = FTransform::Identity;` — Last root bone transform sampled
- L60 _public member_ `TArray<FInstancedStruct> EvaluationNotifies;` — the evaluation notifies extracted from the current anim sequence
- L62 _public member_ `FUAFAssetInstance* Instance = nullptr;`
- L65 _public member_ `const UObject* HostObject;` — Owner object the trait instance is associated to

#### struct `FAnimNextEvaluationNotifiesTask`  
`struct FAnimNextEvaluationNotifiesTask : public FAnimNextEvaluationTask`  
_L85-98_
- reflection: `USTRUCT()`
- inherits: `FAnimNextEvaluationTask`
- desc: Task to run EvaluationNotifies on VM
- L89 _public prototype_ `DECLARE_ANIM_EVALUATION_TASK(FAnimNextEvaluationNotifiesTask) static FAnimNextEvaluationNotifiesTask Make(UE::UAF::FEvaluationNotifiesTrait::FInstanceData* InstanceData, const UE::UAF::FEvaluationNotifiesTrait::FSharedData* SharedData);`
- L94 _public prototype_ `virtual void Execute(UE::UAF::FEvaluationVM& VM) const override;` — Task entry point
- L96 _public member_ `UE::UAF::FEvaluationNotifiesTrait::FInstanceData* InstanceData = nullptr;`
- L97 _public member_ `const UE::UAF::FEvaluationNotifiesTrait::FSharedData* SharedData = nullptr;`

#### struct `FEvaluationNotify_BaseInstance`  
`struct FEvaluationNotify_BaseInstance`  
_L101-117_
- reflection: `USTRUCT()`
- L104 _public function_ `virtual void Start()`
- L105 _public function_ `virtual void Update(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& InstanceData, UE::UAF::FEvaluationVM& VM)`
- L106 _public function_ `virtual void End(UE::UAF::FEvaluationNotifiesTrait::FInstanceData& InstanceData)`
- L108 _public function_ `virtual ~FEvaluationNotify_BaseInstance()`
- L110 _public member_ `const FAnimNotifyEvent* NotifyEvent;`
- L111 _public member_ `TObjectPtr<UAnimNotifyState> AnimNotify = nullptr;`
- L112 _public member_ `float StartTime = 0.f;`
- L113 _public member_ `float EndTime = 0.f;`
- L115 _public member_ `float CurrentTime = 0.f;`
- L116 _public member_ `bool bActive = false;`

#### Free symbols / members of external scopes

- L29 _macro_ `#define TRAIT_LATENT_PROPERTIES_ENUMERATOR(GeneratorMacro) \` — Latent pin support boilerplate
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Public/EvaluationNotifies/AnimNode_EvaluationNotifies.h` (Public)


#### struct `FEvaluationNotifyInstance`  
`struct FEvaluationNotifyInstance`  
_L18-33_
- reflection: `USTRUCT()`
- L22 _public function_ `virtual void Start(const UAnimSequenceBase* AnimationAsset)`
- L23 _public function_ `virtual void Update(const UAnimSequenceBase* AnimationAsset, float CurrentTime, float DeltaTime, bool bIsMirrored, const UMirrorDataTable* MirrorDataTable, FTransform& RootBoneTransform, const TMap<FName, FTransform>& NamedTransforms, FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)`
- L25 _public function_ `virtual void End()`
- L27 _public function_ `virtual ~FEvaluationNotifyInstance()`
- L29 _public member_ `TObjectPtr<UAnimNotifyState> AnimNotify = nullptr;`
- L30 _public member_ `float StartTime = 0.f;`
- L31 _public member_ `float EndTime = 0.f;`
- L32 _public member_ `bool bActive = false;`

#### struct `FAnimNode_EvaluationNotifies`  
`struct FAnimNode_EvaluationNotifies : public FAnimNode_SkeletalControlBase`  
_L37-88_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_SkeletalControlBase`
- desc: add procedural delta to the root motion attribute
- L43 _public member_ `TObjectPtr<UAnimationAsset> CurrentAnimAsset;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Animation Asset for incorporating root motion data. If CurrentAnimAsset is set, and the animation has root motion rotation within the TargetTime, then those rotations will be scaled to reach the TargetOrientation
- L47 _public member_ `float CurrentAnimAssetTime = 0.f;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Current playback time in seconds of the CurrentAnimAsset
- L51 _public member_ `bool CurrentAnimAssetMirrored = false;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Is the current anim asset mirrored
- L55 _public member_ `TObjectPtr<UMirrorDataTable> MirrorDataTable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Evaluation, meta = (PinShownByDefault))` — If bMirrored is set, MirrorDataTable will be used for mirroring the CurrentAnimAsset during prediction
- L59 _public member_ `TMap<FName, FTransform> NamedTransforms;` — `UPROPERTY(EditAnywhere, Transient, BlueprintReadWrite, Category=Evaluation, meta=(PinShownByDefault))` — Current playback time in seconds of the CurrentAnimAsset
- L62 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;` — FAnimNodeBase interface
- L63 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L67 _public prototype_ `virtual void UpdateInternal(const FAnimationUpdateContext& Context) override;` — FAnimNode_SkeletalControlBase interface
- L68 _public prototype_ `virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L69 _public function_ `virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override`
- L72 _public prototype_ `static void RegisterEvaluationHandler(UClass* NotifyType, UScriptStruct* Handler);`
- L73 _public prototype_ `static void UnregisterEvaluationHandler(UClass* NotifyType);`
- L76 _private prototype_ `void GetEvaluationNotifiesFromAnimation(const UAnimSequenceBase* Animation, TArray<FInstancedStruct>& OutNotifyInstances);`
- L78 _private member_ `FTransform RootBoneTransform;`
- L79 _private member_ `TArray<FInstancedStruct> Tags;`
- L80 _private member_ `float PreviousAnimAssetTime = 0;`
- L82 _private member_ `TObjectPtr<const UAnimSequenceBase> CurrentSequence = nullptr;` — `UPROPERTY(Transient)`
- L84 _private member_ `static TMap<UClass*, UScriptStruct*> NotifyEvaluationHandlerMap;`
- L87 _private member_ `FGraphTraversalCounter UpdateCounter;` — Update Counter for detecting being relevant

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Public/EvaluationNotifies/AnimNotifyState_Alignment.h` (Public)


#### enum `EAlignmentWeightCurveType`  
`enum class EAlignmentWeightCurveType`  
_L10-20_
- reflection: `UENUM()`
- L12 _public enumerator_ `FromRootMotionTranslation`
- L13 _public enumerator_ `FromRootMotionRotation`
- L14 _public enumerator_ `Linear`
- L15 _public enumerator_ `EaseIn`
- L16 _public enumerator_ `EaseOut`
- L17 _public enumerator_ `EaseInOut`
- L18 _public enumerator_ `Instant`
- L19 _public enumerator_ `DoNotWarp`

#### struct `FAlignmentWarpCurve`  
`struct FAlignmentWarpCurve`  
_L23-38_
- reflection: `USTRUCT()`
- L29 _public member_ `EAlignmentWeightCurveType CurveType = EAlignmentWeightCurveType::FromRootMotionTranslation;` — `UPROPERTY(EditAnywhere, Category = Properties)` — Type of curve to interpolate using
- L33 _public member_ `float StartRatio = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Properties", meta = (UIMin = "0.0", UIMax = "1.0", SliderExponent = "1.0"))` — Time to start warping, as a ratio of the duration of the Notify
- L37 _public member_ `float EndRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Properties", meta = (UIMin = "0.0", UIMax = "1.0", SliderExponent = "1.0"))` — Time to complete warping, as a ratio of the duration of the Notify

#### struct `FAlignmentSteeringSettings`  
`struct FAlignmentSteeringSettings`  
_L41-60_
- reflection: `USTRUCT()`
- L47 _public member_ `bool bEnableSmoothing = true;` — `UPROPERTY(EditAnywhere, Category=Properties)` — Enable smoothing of the steering target orientation, to avoid instant orientation changes
- L51 _public member_ `float SmoothStiffness = 300;` — `UPROPERTY(EditAnywhere, Category=Propeties, meta = (EditCondition=bEnableSmoothing))` — Sprint stiffness for smoothing
- L55 _public member_ `float SmoothDamping = 1;` — `UPROPERTY(EditAnywhere, Category=Properties, meta = (EditCondition=bEnableSmoothing))` — Spring damping factor for smoothing
- L59 _public member_ `float AngleThreshold = 135;` — `UPROPERTY(EditAnywhere, Category = Properties)` — When the warped movement direction differs from the animated movement direction by more than this threshold, steering will be disabled.

#### struct `AnimTrajectoryData`  
`struct AnimTrajectoryData`  
_L62-68_
- L64 _public member_ `FTransform TargetTransform;`
- L65 _public member_ `TArray<FTransform> Trajectory;`
- L66 _public member_ `TArray<float> TranslationCurve;`
- L67 _public member_ `TArray<float> RotationCurve;`

#### enum `EAlignmentUpdateMode`  
`enum class EAlignmentUpdateMode`  
_L71-77_
- reflection: `UENUM()`
- L74 _public enumerator_ `World` — each frame, apply root motion to get to the expected part of the alignment path in wold space
- L76 _public enumerator_ `Relative` — each frame, apply the root motion from the alignment path relative to the previous frame

#### class `UNotifyState_AlignmentBase`  
`class UNotifyState_AlignmentBase : public UAnimNotifyState`  
_L80-137_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnimNotifyState`
- L87 _public member_ `FAlignmentWarpCurve TranslationWarpingCurve;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L91 _public member_ `bool bSeparateTranslationCurves;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="!bUseSeparateTranslationCurves"))`
- L95 _public member_ `FAlignmentWarpCurve TranslationWarpingCurve_InMovementDirection;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="bUseSeparateTranslationCurves"))` — curve for warping translation in direction of movement
- L97 _public member_ `FAlignmentWarpCurve TranslationWarpingCurve_OutOfMovementDirection;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="bUseSeparateTranslationCurves"))`
- L100 _public member_ `FAlignmentWarpCurve RotationWarpingCurve = { };` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L104 _public member_ `FTransform AlignOffset;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Offset from Root (or AlignBone) to Align to the target transform
- L108 _public member_ `bool bForceTargetTransformUpright;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — only allow Yaw in the target transform (remove other rotations before warping)
- L114 _public function_ `void SetAlignOffset(FTransform NewTransform)` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "TechAnimUtils")` — For automating setting the AlignOffset at the end of the NotifyState
- L122 _public member_ `FBoneReference AlignBone;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Optional bone to Align to target transform
- L125 _public member_ `EAlignmentUpdateMode UpdateMode;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)`
- L129 _public member_ `FName Disable;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Bool variable which will disable this notify
- L133 _public member_ `bool bEnableSteering = false;` — `UPROPERTY(EditAnywhere, Category = Steering)` — Steering will rotate the character based on the difference between the animated movement direction and the warped movement direction, to keep the character facing their direction of movement
- L136 _public member_ `FAlignmentSteeringSettings SteeringSettings;` — `UPROPERTY(EditAnywhere, Category = Steering, meta=(EditCondition=bEnableSteering))`

#### class `UNotifyState_Alignment`  
`class UNotifyState_Alignment : public UNotifyState_AlignmentBase`  
_L140-156_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName="Alignment")`
- inherits: `UNotifyState_AlignmentBase`
- L147 _public member_ `FName TransformName;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Named transform to align to
- L151 _public function_ `void SetTransformName(FName NewName)` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "TechAnimUtils")`

#### struct `FAlignmentNotifyInstance`  
`struct FAlignmentNotifyInstance : public FEvaluationNotifyInstance`  
_L159-182_
- reflection: `USTRUCT()`
- inherits: `FEvaluationNotifyInstance`
- L163 _public prototype_ `virtual void Start(const UAnimSequenceBase* AnimationAsset) override;`
- L164 _public prototype_ `virtual void Update(const UAnimSequenceBase* AnimationAsset, float CurrentTime, float DeltaTime, bool bIsMirrored, const UMirrorDataTable* MirrorDataTable, FTransform& RootBoneTransform, const TMap<FName, FTransform>& NamedTransforms, FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L167 _public prototype_ `float GetWeight(float CurrentTime, const FAlignmentWarpCurve& WarpCurve) const;`
- L169 _public member_ `FBoneReference AlignBone;`
- L170 _public member_ `bool bFirstFrame = true;`
- L171 _public member_ `float ActualStartTime = 0;`
- L172 _public member_ `float PreviousFrame = 0;`
- L174 _public member_ `FTransform StartingRootTransform;`
- L175 _public member_ `FTransform TargetTransform;`
- L177 _public member_ `FQuat FilteredSteeringTarget = FQuat::Identity;`
- L178 _public member_ `FQuaternionSpringState TargetSmoothingState;`
- L180 _public member_ `TArray<FTransform> WarpedTrajectory;`
- L181 _public member_ `AnimTrajectoryData AnimTrajectoryData;`

#### class `UNotifyState_AlignToGround`  
`class UNotifyState_AlignToGround : public UNotifyState_AlignmentBase`  
_L185-228_
- reflection: `UCLASS(BlueprintType, DisplayName="AlignToGround")`
- inherits: `UNotifyState_AlignmentBase`
- L190 _private prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L195 _public member_ `float TraceRadius = 10;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")`
- L198 _public member_ `float TraceStartOffset = -100;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")`
- L201 _public member_ `float TraceEndOffset = 100;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")`
- L205 _public member_ `float GroundHeightOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")` — vertical offset added to the raycast hit result height
- L208 _public member_ `TEnumAsByte<ETraceTypeQuery> TraceChannel = TraceTypeQuery1;` — `UPROPERTY(EditAnywhere, Category = "Trace Settings")`
- L213 _public member_ `FName PlaybackRateOutputVariable_DEPRECATED;` — `UPROPERTY()` — Variable to output playback rate modifier to
- L218 _public member_ `FAnimNextVariableReference PlaybackRateOutputVariableReference;` — `UPROPERTY(EditAnywhere, DisplayName = "Playback Rate Output Variable", Category = PlaybackRate)` — Variable to output playback rate modifier to
- L221 _public member_ `float MinPlaybackRateModifier = 0.5;` — `UPROPERTY(EditAnywhere, Category = PlaybackRate)`
- L223 _public member_ `float MaxPlaybackRateModifier = 1.0;` — `UPROPERTY(EditAnywhere, Category = PlaybackRate)`
- L227 _public member_ `bool bForceStartTransformUpright;` — `UPROPERTY(EditAnywhere, Category = TraceSettings)` — only allow Yaw in the starting root transform when computing the future root motion

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Public/EvaluationNotifies/AnimNotifyState_TwoBoneIK.h` (Public)


#### class `UNotifyState_TwoBoneIK`  
`class UNotifyState_TwoBoneIK : public UAnimNotifyState`  
_L10-82_
- reflection: `UCLASS(BlueprintType, DisplayName="Two Bone IK")`
- inherits: `UAnimNotifyState`
- L18 _public member_ `FBoneReference IKBone;` — `UPROPERTY(EditAnywhere, Category=IK)` — Name of bone to control. This is the main bone chain to modify from.
- L22 _public member_ `FBoneReference RelativeToBone;` — `UPROPERTY(EditAnywhere, Category=IK)` — Name of bone to IK Relative to - IK will target a position that has the same offset from the EffectorLocation, as the IKBone has from this Bone in the source pose.
- L26 _public member_ `double StartStretchRatio = 1.0;` — `UPROPERTY(EditAnywhere, Category=IK, meta = (editcondition = "bAllowStretching", ClampMin = "0.0", UIMin = "0.0"))` — Limits to use if stretching is allowed. This value determines when to start stretch. For example, 0.9 means once it reaches 90% of the whole length of the limb, it will start apply.
- L30 _public member_ `double MaxStretchScale = 1.2;` — `UPROPERTY(EditAnywhere, Category= IK, meta = (editcondition = "bAllowStretching", ClampMin = "0.0", UIMin = "0.0"))` — Limits to use if stretching is allowed. This value determins what is the max stretch scale. For example, 1.5 means it will stretch until 150 % of the whole length of the limb.
- L34 _public member_ `float BlendInTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category= IK)` — Limits to use if stretching is allowed. This value determins what is the max stretch scale. For example, 1.5 means it will stretch until 150 % of the whole length of the limb.
- L36 _public member_ `float BlendOutTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category= IK)`
- L40 _public member_ `FVector EffectorLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector, meta = (PinShownByDefault))` — Effector Location. Target Location to reach.
- L43 _public member_ `FName EffectorLocationTransformName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effector, meta = (PinShownByDefault))`
- L46 _public member_ `FBoneSocketTarget EffectorTarget;` — `UPROPERTY(EditAnywhere, Category=Effector)`
- L50 _public member_ `FVector JointTargetLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=JointTarget, meta=(PinShownByDefault))` — Joint Target Location. Location used to orient Joint bone.
- L53 _public member_ `FBoneSocketTarget JointTarget;` — `UPROPERTY(EditAnywhere, Category = JointTarget)`
- L57 _public member_ `FAxis TwistAxis;` — `UPROPERTY(EditAnywhere, Category = IK, meta = (editcondition = "!bAllowTwist"))` — Specify which axis it's aligned. Used when removing twist
- L69 _public member_ `uint8 bAllowStretching:1 = false;` — `UPROPERTY(EditAnywhere, Category=IK)` — Should stretching be allowed, to be prevent over extension
- L73 _public member_ `uint8 bTakeRotationFromEffectorSpace : 1 = false;` — `UPROPERTY(EditAnywhere, Category=IK)` — Set end bone to use End Effector rotation
- L77 _public member_ `uint8 bMaintainEffectorRelRot : 1 = false;` — `UPROPERTY(EditAnywhere, Category = IK)` — Keep local rotation of end bone
- L81 _public member_ `uint8 bAllowTwist : 1 = true;` — `UPROPERTY(EditAnywhere, Category = IK)` — Whether or not to apply twist on the chain of joints. This clears the twist value along the TwistAxis

#### struct `FTwoBoneIKNotifyInstance`  
`struct FTwoBoneIKNotifyInstance : public FEvaluationNotifyInstance`  
_L85-112_
- reflection: `USTRUCT()`
- inherits: `FEvaluationNotifyInstance`
- L87 _public function_ `FTwoBoneIKNotifyInstance() : CachedUpperLimbIndex(INDEX_NONE) , CachedLowerLimbIndex(INDEX_NONE)`
- L96 _public prototype_ `virtual void Start(const UAnimSequenceBase* AnimationAsset) override;`
- L97 _public prototype_ `virtual void Update(const UAnimSequenceBase* AnimationAsset, float CurrentTime, float DeltaTime, bool bIsMirrored, const UMirrorDataTable* MirrorDataTable, FTransform& RootBoneTransform, const TMap<FName, FTransform>& NamedTransforms, FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;`
- L100 _public member_ `FBoneReference IKBone;`
- L101 _public member_ `FBoneReference RelativeToBone;`
- L102 _public member_ `FBoneSocketTarget EffectorTarget;`
- L105 _public member_ `FBoneSocketTarget JointTarget;` — `UPROPERTY(EditAnywhere, Category = JointTarget)`
- L108 _public member_ `FCompactPoseBoneIndex CachedUpperLimbIndex;` — cached limb index for upper
- L111 _public member_ `FCompactPoseBoneIndex CachedLowerLimbIndex;` — cached limb index for lower

### `Plugins/Experimental/EvaluationNotifies/Source/Runtime/Public/EvaluationNotifiesRuntimeModule.h` (Public)


#### class `IEvaluationNotifiesRuntimeModule`  
`class IEvaluationNotifiesRuntimeModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
