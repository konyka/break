# Plugins / PerformanceCaptureWorkflowRuntime

- module root: `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime`
- headers: 6; symbols: 90
- symbol kinds: class=5, delegate=1, function=9, member=30, prototype=43, struct=2
- PrivateDependencyModuleNames: CoreUObject, Engine, IKRig, LiveLink, LiveLinkAnimationCore, LiveLinkInterface, PerformanceCaptureCore, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Private/AnimNode_LiveLinkProp.h` (Private)


#### struct `FAnimNode_LiveLinkProp`  
`struct FAnimNode_LiveLinkProp : public FAnimNode_Base`  
_L22-76_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FAnimNode_Base`
- L29 _public member_ `FPoseLink InputPose;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture|Prop")` — Input pose
- L33 _public member_ `FLiveLinkSubjectName LiveLinkSubjectName;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture|Prop")` — The Live Link subject to use.
- L37 _public member_ `bool bDoLiveLinkEvaluation = true;` — `UPROPERTY(EditAnywhere, Transient, Category = "Performance Capture|Prop")` — Bool to control evaluation of animation.
- L41 _public member_ `FTransform OffsetTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture|Prop")` — Transform to apply local space to offset to the incoming Live Link data.
- L45 _public member_ `float GlobalScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture|Prop")` — Global scale to the location
- L49 _public member_ `FVector DynamicConstraintOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture|Prop")` — Location to apply in parent bone space to offset the incoming Live Link data.
- L51 _public prototype_ `FAnimNode_LiveLinkProp();`
- L54 _public prototype_ `virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;`
- L55 _public prototype_ `virtual void PreUpdate(const UAnimInstance* InAnimInstance) override;`
- L56 _public prototype_ `virtual void Update_AnyThread(const FAnimationUpdateContext & Context) override;`
- L57 _public prototype_ `virtual void Evaluate_AnyThread(FPoseContext& Output) override;`
- L58 _public prototype_ `virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext & Context) override;`
- L59 _public prototype_ `virtual void GatherDebugData(FNodeDebugData& DebugData) override;`
- L60 _public function_ `virtual bool HasPreUpdate() const override`
- L65 _protected prototype_ `void BuildPoseFromAnimData(const FLiveLinkSubjectFrameData& LiveLinkData, FPoseContext& Output);`
- L69 _private member_ `ILiveLinkClient* LiveLinkClient_AnyThread;`
- L71 _private member_ `float CachedDeltaTime;`
- L73 _private member_ `TSharedPtr<FLiveLinkSubjectFrameData> CachedLiveLinkFrameData;`
- L75 _private member_ `TSubclassOf<class ULiveLinkRole> CachedEvaluatedRole;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Private/PCapPropLiveLinkAnimInstance.h` (Private)


#### struct `FPCapPropLiveLinkAnimInstanceProxy`  
`struct FPCapPropLiveLinkAnimInstanceProxy : public FAnimInstanceProxy`  
_L12-35_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- L19 _public function_ `FPCapPropLiveLinkAnimInstanceProxy()`
- L23 _public function_ `FPCapPropLiveLinkAnimInstanceProxy(UAnimInstance* InAnimInstance) : FAnimInstanceProxy(InAnimInstance)`
- L28 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L29 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;`
- L30 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L31 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L34 _public member_ `FAnimNode_LiveLinkProp PoseNode;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### class `UPCapPropLiveLinkAnimInstance`  
`class UPCapPropLiveLinkAnimInstance : public UAnimInstance`  
_L40-88_
- reflection: `UCLASS(transient, NotBlueprintable)`
- inherits: `UAnimInstance`
- L47 _public function_ `void SetSubject(FLiveLinkSubjectName SubjectName)` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")`
- L53 _public function_ `void EnableLiveLinkEvaluation(bool bDoEnable)` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")`
- L59 _public function_ `void SetOffsetTransform(FTransform Offset)` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")`
- L65 _public function_ `void SetDynamicConstraintVector(FVector DynamicOffset)` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")`
- L71 _public function_ `void SetGlobalScale(float GlobalScale)` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")`
- L77 _public function_ `bool GetEnableLiveLinkEvaluation()` — Not exposed to Blueprint
- L83 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L84 _protected prototype_ `virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Private/PCapWorkflowRuntimeFunctionLibrary.h` (Private)


#### class `UPCapWorkflowRuntimeFunctionLibrary`  
`class UPCapWorkflowRuntimeFunctionLibrary : public UBlueprintFunctionLibrary`  
_L14-58_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function Library for Performance Capture Workflow, enabling read-only access to Retargeter properties. Intended for querying retargeters when calculating dynamic prop constraints.
- L21 _private prototype_ `static const UIKRigDefinition* GetSourceRig(const UIKRetargeter* InRetargetAsset);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Get the source IK rig from an IKRetargeter asset.
- L27 _private prototype_ `static const UIKRigDefinition* GetTargetRig(const UIKRetargeter* InRetargetAsset);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Get the target IK rig from an IKRetargeter asset.
- L33 _private prototype_ `static TArray<FBoneChain> GetRetargetChains(const UIKRigDefinition* InIKRig);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Get all the chains in the given IKRig Asset.
- L39 _private prototype_ `static FName GetChainStartBone(const UIKRigDefinition* InIKRig, const FName ChainName);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Returns the bone name at the start of a given chain.
- L45 _private prototype_ `static FName GetChainEndBone(const UIKRigDefinition* InIKRig, const FName ChainName);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Returns the bone name at the end of a given chain.
- L51 _private prototype_ `static FName GetChainFromBone(const UIKRigDefinition* InIKRig, const FName InBoneName);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Returns the first chain the given bone name is a member of.
- L57 _private prototype_ `static FName GetChainPair(UIKRetargeter* InRetargetAsset, const FName InChainName, const ERetargetSourceOrTarget SourceOrTarget);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Runtime")` — Get the corresponding source or target chain from a given chain name.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Public/PCapPropComponent.h` (Public)


#### class `UPCapPropComponent`  
`class UPCapPropComponent : public UActorComponent`  
_L17-196_
- reflection: `UCLASS(Blueprintable, ClassGroup=("Performance Capture"), meta=(BlueprintSpawnableComponent, DisplayName="Prop Component"))`
- inherits: `UActorComponent`
- desc: A component for use in Motion Capture props. Accepts data as either a LiveLink Transform Role or an Animation Role. If the Live Link data is in the Animation role, this component will take the root bone transform and apply that transform to the owning actor's root component. Can be applied to Static Meshes, Skeletal Meshes and Blueprint constructions. Transform data can be offset in the component's local space. If this component is driving a Skeletal Mesh component and is receiving Live Link Animation data the full bone hierarchy will be applied.
- L23 _public prototype_ `UPCapPropComponent();` — Constructor
- L25 _public prototype_ `~UPCapPropComponent();` — Destructor
- L31 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture")` — LiveLink Subject Name. Must have either Animation Role Type.
- L37 _public member_ `bool bEvaluateLiveLink = true;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture")` — Should LiveLink Subject data be evaluated.
- L43 _public member_ `bool bIsControlledBySequencer = false;` — `UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Interp, Category = "Performance Capture")` — Overrides all LiveLink data and the offset transform. Must be manually set on possessable bindings.
- L49 _public member_ `FName SpawningDataAsset;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Performance Capture")` — The package name of the spawning data asset, if there is one.
- L55 _public member_ `FTransform OffsetTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Offset the incoming LiveLink Transform data in the local space of the controlled component.
- L62 _public member_ `float GlobalScale = 1.0f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Scale the transform from the parent pivot (usually the motion capture stage origin point). Scale is only applied to the location, not the scale of the driven mesh.
- L68 _public member_ `FComponentReference ControlledComponent;` — `UPROPERTY(EditInstanceOnly, Category = "Performance Capture", meta=(UseComponentPicker, AllowedClasses = "/Script/Engine.SceneComponent"))` — Scene Component driven by the LiveLink data. Defaults to Root component of the owning actor.
- L74 _public prototype_ `USceneComponent* GetControlledComponent() const;` — `UFUNCTION(BlueprintPure, Category = "Performance Capture")` — Returns the component controlled by this component. Can return null.
- L80 _public prototype_ `void SetControlledComponent(USceneComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture")` — Sets the component controlled by this component. Component must be within the same actor as this Prop component.
- L87 _public prototype_ `void SetLiveLinkSubject(FLiveLinkSubjectName Subject);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Prop")` — Set the Live Link subject used by this prop component. @param Subject Live Link Subject Name
- L94 _public prototype_ `FLiveLinkSubjectName GetLiveLinkSubject() const;` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Prop")` — Get the LiveLink Subject Name. @return FLiveLinkSubjectName Current LiveLink Subject.
- L101 _public prototype_ `void SetEvaluateLiveLinkData(bool bEvaluateLinkLink);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Prop")` — Set the LiveLink data to update the Skeletal Mesh pose. @param bEvaluateLinkLink Drive or pause the Controlled Mesh from LiveLink Subject data.
- L108 _public prototype_ `bool GetEvaluateLiveLinkData();` — `UFUNCTION(BlueprintPure, Category ="Performance Capture|Prop")` — Get the LiveLink Evaluation State. Subject must have the Animation Role Type. @return bool Is LiveLink data being evaluated.
- L115 _public prototype_ `void SetOffsetTransform(FTransform NewOffset);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Prop")` — Update the local space offset to this prop's Live Link pose. @param NewOffset Offset Transform.
- L122 _public prototype_ `void SetGlobalScale(float NewGlobalScale);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Prop")` — Update the scale factor applied to the incoming Live Link poses @param NewGlobalScale Global Scale.
- L128 _public member_ `bool bUseDynamicConstraint = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="Performance Capture|Dynamic Constraint")` — Enable/Disable use of the Dynamic Constraint offset vector.
- L134 _public member_ `TArray<TSoftObjectPtr<ACaptureCharacter>> DynamicAttachmentCharacters;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Performance Capture|Dynamic Constraint", meta = (EditCondition="bUseDynamicConstraint", EditConditionHides))` — List of Capture Characters to consider in calculating a dynamic constraint.
- L141 _public member_ `bool bAllowOnlyIKBones = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Performance Capture|Dynamic Constraint", meta = (EditCondition="bUseDynamicConstraint", EditConditionHides))` — False = All bone chains' start and end bones will be considered for dynamic attachment . True  = Only bones in chains with an IK goal will be considered for dynamic attachment.
- L147 _public member_ `TArray<FName> DynamicConstraintAttachBones;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Performance Capture|Dynamic Constraint", meta = (GetOptions="GetAttachBones", EditCondition="bUseDynamicConstraint", EditConditionHides))` — A list of bones of to test against for dynamic constraint.
- L154 _public prototype_ `TArray<FName> GetAttachBones() const;` — `UFUNCTION()` — Return a list of bones from the given list of DynamicAttachmentCharacters. @return List of bones to use in DynamicConstraintAttachBones variable
- L162 _public prototype_ `FVector CalculateDynamicOffset();` — `UFUNCTION(BlueprintNativeEvent, Category = "Performance Capture|Dynamic Constraint")` — Blueprint implementable event to enable calculation of a location offset before applying it to the controlled component's transform. @return Parent-space location offset to apply to the prop's transform
- L167 _protected prototype_ `virtual void OnRegister() override;`
- L168 _protected prototype_ `virtual void DestroyComponent(bool bPromoteChildren) override;`
- L173 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L180 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L182 _public prototype_ `void InitiateAnimation();`
- L184 _public prototype_ `void ResetAnimInstance() const;`
- L187 _private member_ `FVector DynamicConstraintOffset = FVector::ZeroVector;`
- L189 _private member_ `FTransform CachedLiveLinkTransform = FTransform::Identity;`
- L191 _private member_ `FTransform FinalTransform = FTransform::Identity;`
- L193 _private member_ `bool bIsDirty;`
- L195 _private member_ `TOptional<bool> bIsSpawnableCache;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Public/PCapStageRoot.h` (Public)


#### class `APerformanceCaptureStageRoot`  
`class APerformanceCaptureStageRoot : public AActor`  
_L17-37_
- reflection: `UCLASS(Blueprintable, Abstract)`
- inherits: `AActor`
- L23 _public prototype_ `APerformanceCaptureStageRoot(const FObjectInitializer& ObjectInitializer);` — Sets default values for this actor's properties
- L27 _public member_ `TObjectPtr<USceneCaptureComponent2D> MapCaptureComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Peformance Capture|StageRoot")` — Scene capture component for capturing the overhead, orthographic map.
- L31 _public member_ `TObjectPtr<UDecalComponent> DecalComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Peformance Capture|StageRoot")` — Decal component for rendering a grid to the floor.
- L35 _public member_ `TObjectPtr<USceneComponent> StageMeshParent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Peformance Capture|StageRoot")` — Scene component, under which all stage ghost meshes should be parented.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflowRuntime/Public/PerformanceCaptureWorkflowRuntime.h` (Public)


#### class `FPerformanceCaptureWorkflowRuntimeModule`  
`class FPerformanceCaptureWorkflowRuntimeModule : public IModuleInterface`  
_L9-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCapRuntime, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCapRuntime, Log, All);`
