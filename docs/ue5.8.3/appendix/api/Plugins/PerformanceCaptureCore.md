# Plugins / PerformanceCaptureCore

- module root: `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore`
- headers: 7; symbols: 95
- symbol kinds: class=6, function=1, macro=4, member=23, prototype=60, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, IKRig, LiveLinkAnimationCore, LiveLinkInterface, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Private/RetargetInstanceProxy.h` (Private)


#### struct `FRetargetAnimInstanceProxy`  
`struct FRetargetAnimInstanceProxy : public FAnimInstanceProxy`  
_L17-43_
- reflection: `USTRUCT()`
- inherits: `FAnimInstanceProxy`
- L23 _public prototype_ `FRetargetAnimInstanceProxy() = default;` — Constructor
- L25 _public prototype_ `FRetargetAnimInstanceProxy(UAnimInstance* InAnimInstance, FAnimNode_RetargetPoseFromMesh* InRetargetNode);`
- L29 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;` — FAnimInstanceProxy Instance
- L30 _public prototype_ `virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;`
- L31 _public prototype_ `virtual void CacheBones() override;`
- L32 _public prototype_ `virtual bool Evaluate(FPoseContext& Output) override;`
- L33 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L36 _public prototype_ `void ConfigureAnimInstanceProxy(UIKRetargeter* InIKRetargetAsset, TWeakObjectPtr<USkeletalMeshComponent> InSourceMeshComponent,FRetargetProfile &InRetargetProfile);`
- L38 _public member_ `FAnimNode_RetargetPoseFromMesh* RetargetNode = nullptr;`
- L41 _private member_ `FRetargetProfile* RetargetProfile = nullptr;`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/CaptureCharacter.h` (Public)


#### class `ACaptureCharacter`  
`class ACaptureCharacter : public ASkeletalMeshActor`  
_L17-98_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup ="Performance Capture", Category = "Performance Capture", HideCategories = ("Mesh", "Rendering", "Animation", "LOD", "Misc", "Physics", "Streaming"))`
- inherits: `ASkeletalMeshActor`
- L23 _public prototype_ `ACaptureCharacter();` — Sets default values for this actor's properties
- L31 _public member_ `TSoftObjectPtr<ACapturePerformer> SourcePerformer_DEPRECATED;` — `UE_DEPRECATED(5.7, "Use URetargetComponent::SourcePerformer instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use URetargetComponent::SourcePerformer instead."))` — CapturePerformer Actor that will be the source for retargeting.
- L38 _public member_ `TObjectPtr<UIKRetargeter> RetargetAsset_DEPRECATED;` — `UE_DEPRECATED(5.7, "Use URetargetComponent::RetargetAsset instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use URetargetComponent::RetargetAsset instead."))` — The IKRetarget Asset to use for retargeting between the SourcePerformer and this Character.
- L45 _public member_ `bool bForceAllSkeletalMeshesToFollowLeader_DEPRECATED = true;` — `UE_DEPRECATED(5.7, "Use URetargetComponent::bForceOtherMeshesToFollowControlledMesh instead.")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use URetargetComponent::bForceOtherMeshesToFollowControlledMesh instead."))` — Force all skeletal meshes to use the root SkeletalMesh as their Leader. Default = True.
- L53 _public prototype_ `void SetCustomRetargetProfile(FRetargetProfile InProfile);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Set a Custom Retarget Profile. @param InProfile New Retarget Profile.
- L60 _public prototype_ `FRetargetProfile GetCustomRetargetProfile();` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Get a Custom Retarget Profile. @return Current Custom Retarget Profile.
- L67 _public prototype_ `void SetSourcePerformer(ACapturePerformer* InPerformer);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Set the Source CapturePerformer Actor. @param InPerformer New Performer.
- L74 _public prototype_ `void SetRetargetAsset(UIKRetargeter* InRetargetAsset);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Set the Retarget Asset. @param InRetargetAsset New IKRetarget Asset.
- L81 _public prototype_ `void SetForceAllSkeletalMeshesToFollowLeader (bool InFollowLeader);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Force all Skeletal Meshes to follow the Controlled Skeletal mesh. @param InFollowLeader New Bool.
- L87 _public prototype_ `URetargetComponent* GetRetargetComponent() const;` — `UFUNCTION(BlueprintPure, Category = "Performance Capture|Character")` — Return the retarget component
- L91 _protected prototype_ `virtual void PostLoad() override;` — UObject interface
- L97 _private member_ `TObjectPtr<URetargetComponent> RetargetComponent;` — `UPROPERTY()` — retarget component is private and hidden from the editor UI

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PERFORMANCECAPTURECORE_API`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/CapturePerformer.h` (Public)


#### class `ACapturePerformer`  
`class ACapturePerformer : public ASkeletalMeshActor`  
_L17-91_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Category="Performance Capture")`
- inherits: `ASkeletalMeshActor`
- L23 _public prototype_ `ACapturePerformer();` — Sets default values for this actor's properties
- L29 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — LiveLink Subject Name. Must have the Animation Role Type.
- L35 _public member_ `bool bForceAllMeshesToFollowLeader = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Force all skeletal meshes to follow the pose of the Controlled Skeletal Mesh.
- L41 _public member_ `bool bEvaluateAnimation = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Evaluate LiveLink animation. Set to false to pause animation.
- L48 _public prototype_ `void SetLiveLinkSubject(FLiveLinkSubjectName Subject);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Performer")` — Set the LiveLink Subject Name. Subject must have the Animation Role Type. @param Subject New LiveLink Subject.
- L55 _public prototype_ `FLiveLinkSubjectName GetLiveLinkSubject() const;` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Performer")` — Get the LiveLink Subject Name. @return FLiveLinkSubjectName Current LiveLink Subject.
- L62 _public prototype_ `void SetEvaluateLiveLinkData(bool bEvaluateLinkLink);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Performer")` — Set the LiveLink data to update the Skeletal Mesh pose. @param bEvaluateLinkLink Drive or pause the Skeletal Mesh from LiveLink Subject data.
- L69 _public prototype_ `bool GetEvaluateLiveLinkData();` — `UFUNCTION(BlueprintPure, Category ="Performance Capture|Performer")` — Get state of LiveLink data evaluation. True = animation is updated. @return bool Is LiveLink data being evaluated.
- L76 _public prototype_ `void SetMocapMesh(USkeletalMesh* MocapMesh);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Performer")` — Set the Skeletal Mesh Asset of the root Skeletal Mesh. @param MocapMesh New Skeletal Mesh Asset.
- L80 _protected prototype_ `virtual void BeginPlay() override;` — Called when the game starts or when spawned
- L81 _protected prototype_ `virtual void PostInitializeComponents() override;`
- L82 _protected prototype_ `virtual void PostRegisterAllComponents() override;`
- L83 _protected prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L86 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L90 _private member_ `TObjectPtr<UPerformerComponent> PerformerComponent;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PERFORMANCECAPTURECORE_API`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/PerformanceCaptureCore.h` (Public)


#### class `FPerformanceCaptureCoreModule`  
`class FPerformanceCaptureCoreModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/PerformerComponent.h` (Public)


#### class `UPerformerComponent`  
`class UPerformerComponent : public UActorComponent`  
_L16-108_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName="Performer Component", ClassGroup=("Performance Capture"), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L22 _public prototype_ `UPerformerComponent();` — Sets default values for this component's properties
- L28 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — LiveLink Subject Name. Must have the Animation Role Type.
- L34 _public member_ `FComponentReference ControlledSkeletalMesh;` — `UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Performance Capture", meta=(UseComponentPicker, AllowedClasses = "/Script/Engine.SkeletalMeshComponent"))` — The Skeletal Mesh driven by the LiveLink subject. Skeleton mush be compatible with the LiveLink subject's bone hierarchy.
- L40 _public member_ `bool bEvaluateAnimation = true;` — `UPROPERTY(EditAnywhere, Category = "Performance Capture")` — Evaluate LiveLink animation. Set to false to pause animation.
- L46 _public member_ `bool bForceOtherMeshesToFollowControlledMesh = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Force all other skeletal meshes in the Owner Actor to follow the pose of the Controlled Skeletal Mesh.
- L53 _public prototype_ `void SetLiveLinkSubject(FLiveLinkSubjectName Subject);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Performer")` — Set the LiveLink Subject Name. Subject must have the Animation Role Type. @param Subject New LiveLink Subject.
- L60 _public prototype_ `FLiveLinkSubjectName GetLiveLinkSubject() const;` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Performer")` — Get the LiveLink Subject Name. @return FLiveLinkSubjectName Current LiveLink Subject.
- L67 _public prototype_ `void SetEvaluateLiveLinkData(bool bEvaluateLinkLink);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Performer")` — Set the LiveLink data to update the Skeletal Mesh pose. @param bEvaluateLinkLink Drive or pause the Skeletal Mesh from LiveLink Subject data.
- L74 _public prototype_ `bool GetEvaluateLiveLinkData() const;` — `UFUNCTION(BlueprintPure, Category ="Performance Capture|Performer")` — Get the LiveLink Evaluation State. Subject must have the Animation Role Type. @return bool Is LiveLink data being evaluated.
- L82 _public prototype_ `bool SetControlledMesh(USkeletalMeshComponent* SkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Performer")` — Set the controlled skeletal mesh component. Must be a member of the owner actor of this component. @param SkeletalMesh New SkeletalMesh. @return bool Was the given skeletal mesh component successfully applied.
- L89 _public prototype_ `void SetForceMeshesFollowLeader(bool bInBool);` — `UFUNCTION(BlueprintCallable, Category ="Performance Capture|Performer")` — Set the bForceOtherMeshesToFollowControlledMesh variable. Changing will re-initialise animation. @param bInBool DForce all other skeletal meshes in the Owner Actor to follow the pose of the Controlled Skeletal Mesh.
- L92 _protected prototype_ `virtual void DestroyComponent(bool bPromoteChildren) override;`
- L94 _protected prototype_ `virtual void OnRegister() override;`
- L96 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L101 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L102 _public prototype_ `void InitiateAnimation();`
- L106 _private member_ `bool bIsDirty;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PERFORMANCECAPTURECORE_API`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/RetargetAnimInstance.h` (Public)


#### class `URetargetAnimInstance`  
`class URetargetAnimInstance : public UAnimInstance`  
_L21-56_
- reflection: `UCLASS(Transient, NotBlueprintable, BlueprintType, MinimalAPI)`
- inherits: `UAnimInstance`
- L34 _public prototype_ `void ConfigureAnimInstance(UIKRetargeter* InIKRetargetAsset,TWeakObjectPtr<USkeletalMeshComponent> InSourceMeshComponent, FRetargetProfile InRetargetProfile);` — Configure Retarget AnimInstance @param InIKRetargetAsset IKRetargeter Asset to use for retargeting. @param InSourceMeshComponent The mesh component that is the source of motion. @param InRetargetProfile Retarget Profile struct to use.
- L40 _public prototype_ `void UpdateCustomRetargetProfile(const FRetargetProfile &InRetargetProfile);` — Update the RetargetProfile. @param InRetargetProfile Retarget Profile struct to use.
- L46 _public prototype_ `FRetargetProfile GetRetargetProfile();` — Retrieve the current RetargetProfile struct. @return  Retarget Profile struct to use.
- L50 _protected prototype_ `virtual void NativeInitializeAnimation() override;` — UAnimInstance interface
- L51 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`
- L55 _protected member_ `FAnimNode_RetargetPoseFromMesh RetargetNode;` — `UPROPERTY()`

### `Plugins/Animation/PerformanceCaptureCore/Source/PerformanceCaptureCore/Public/RetargetComponent.h` (Public)


#### class `URetargetComponent`  
`class URetargetComponent : public UActorComponent`  
_L17-131_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup=("Performance Capture"), meta=(BlueprintSpawnableComponent), DisplayName = "Retarget Component")`
- inherits: `UActorComponent`
- L23 _public prototype_ `URetargetComponent();` — Sets default values for this component's properties
- L30 _public member_ `FComponentReference SourceSkeletalMeshComponent ;` — `UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Performance Capture", meta = (UseComponentPicker, AllowAnyActor, AllowedClasses = "/Script/Engine.SkeletalMeshComponent", EditCondition = "IsSourcePerformerNull()", EditConditionHides))` — Skeletal Mesh component that will be the source for retargeting. Can be on the Owner Actor or another Actor in the same level.
- L36 _public member_ `FComponentReference ControlledSkeletalMeshComponent;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere,Category = "Performance Capture", meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.SkeletalMeshComponent"))` — Skeletal Mesh that will be driven by the IKRetargeter. Limited to skeletal meshes on this component's Owner Actor.
- L42 _public member_ `bool bForceOtherMeshesToFollowControlledMesh = true;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — Force all skeletal meshes to use the ControlledSkeletalMeshComponent as their Leader. Default = True.
- L48 _public member_ `TObjectPtr<UIKRetargeter> RetargetAsset;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture")` — The IKRetarget Asset to use for retargeting between the source and controlled skeletal meshes.
- L54 _public member_ `FRetargetProfile CustomRetargetProfile;` — `UPROPERTY(BlueprintReadOnly, Interp, EditAnywhere, Category = "Performance Capture")` — Custom Retarget Profile. Should be used to override Retarget settings on the RetargetAsset.
- L60 _public member_ `TSoftObjectPtr<ACapturePerformer> SourcePerformer;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Performance Capture|Character")` — CapturePerformer Actor that will be the source for retargeting.
- L67 _public prototype_ `void SetSourcePerformerMesh(USkeletalMeshComponent* InPerformerMesh);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Set the Source Performer Mesh. @param InPerformerMesh New Source Skeletal Mesh.
- L74 _public prototype_ `void SetControlledMesh(USkeletalMeshComponent* InControlledMesh);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Set the Controlled Skeletal Mesh. @param InControlledMesh New Controlled Skeletal Mesh Component.
- L81 _public prototype_ `void SetRetargetAsset(UIKRetargeter* InRetargetAsset);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Set the Retarget Asset. @param InRetargetAsset New IKRetarget Asset.
- L88 _public prototype_ `void SetCustomRetargetProfile(FRetargetProfile InProfile);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Set a Custom Retarget Profile. @param InProfile New Retarget Profile.
- L95 _public prototype_ `FRetargetProfile GetCustomRetargetProfile();` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Get Retarget Profile. @return Current Custom Retarget Profile.
- L102 _public prototype_ `void SetForceMeshesFollowLeader(bool bInBool);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Retarget")` — Set the bForceOtherMeshesToFollowControlledMesh variable. Changing will re-initialise animation. @param bInBool Force all other skeletal meshes in the Owner Actor to follow the pose of the Controlled Skeletal Mesh.
- L109 _public prototype_ `void SetSourcePerformer(ACapturePerformer* InPerformer);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Character")` — Set the Source CapturePerformer Actor. @param InPerformer New Performer.
- L113 _protected prototype_ `virtual void OnRegister() override;` — Called when the game starts
- L114 _protected prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L115 _protected prototype_ `virtual void DestroyComponent(bool bPromoteChildren) override;`
- L118 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L122 _protected function_ `inline bool IsSourcePerformerNull() const` — `UFUNCTION()`
- L125 _private member_ `bool bIsDirty = true;`
- L128 _public prototype_ `void InitiateAnimation();`
- L130 _public prototype_ `void SetForceOtherMeshesToFollowControlledMesh(bool bInBool);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PERFORMANCECAPTURECORE_API`
