# Plugins / MotionWarping

- module root: `Plugins/Animation/MotionWarping/Source/MotionWarping`
- headers: 13; symbols: 513
- symbol kinds: class=22, delegate=5, enum=14, enumerator=44, function=45, macro=10, member=188, prototype=169, struct=16
- PrivateDependencyModuleNames: Slate, SlateCore
- PublicDependencyModuleNames: AnimGraph, Core, CoreUObject, Engine, NetCore, UnrealEd

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/AnimNotifyState_MotionWarping.h` (Public)


#### class `UAnimNotifyState_MotionWarping`  
`class UAnimNotifyState_MotionWarping : public UAnimNotifyState`  
_L16-60_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Motion Warping"))`
- inherits: `UAnimNotifyState`
- desc: AnimNotifyState used to define a motion warping window in the animation
- L25 _public member_ `TObjectPtr<URootMotionModifier> RootMotionModifier;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Config")`
- L27 _public prototype_ `UAnimNotifyState_MotionWarping(const FObjectInitializer& ObjectInitializer);`
- L30 _public prototype_ `void OnBecomeRelevant(UMotionWarpingComponent* MotionWarpingComp, const UAnimSequenceBase* Animation, float StartTime, float EndTime) const;` — Called from the MotionWarpingComp when this notify becomes relevant. See: UMotionWarpingComponent::Update
- L34 _public prototype_ `URootMotionModifier* AddRootMotionModifier(UMotionWarpingComponent* MotionWarpingComp, const UAnimSequenceBase* Animation, float StartTime, float EndTime) const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Motion Warping")` — Creates a root motion modifier from the config class defined in the notify
- L37 _public prototype_ `void OnRootMotionModifierActivate(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier);` — `UFUNCTION()`
- L40 _public prototype_ `void OnRootMotionModifierUpdate(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier);` — `UFUNCTION()`
- L43 _public prototype_ `void OnRootMotionModifierDeactivate(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier);` — `UFUNCTION()`
- L46 _public prototype_ `void OnWarpBegin(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Motion Warping")`
- L49 _public prototype_ `void OnWarpUpdate(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Motion Warping")`
- L52 _public prototype_ `void OnWarpEnd(UMotionWarpingComponent* MotionWarpingComp, URootMotionModifier* Modifier) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Motion Warping")`
- L55 _public prototype_ `virtual void ValidateAssociatedAssets() override;`
- L57 _public prototype_ `virtual void DrawInEditor(class FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;`
- L58 _public prototype_ `virtual void DrawCanvasInEditor(FCanvas& Canvas, FSceneView& View, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/AttributeBasedRootMotionComponent.h` (Public)


#### struct `FAttributeBasedRootMotionComponentPrePhysicsTickFunction`  
`struct FAttributeBasedRootMotionComponentPrePhysicsTickFunction : public FTickFunction`  
_L14-35_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- L19 _public member_ `class UAttributeBasedRootMotionComponent* Target;` — CharacterMovementComponent that is the target of this tick
- L28 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — Abstract function actually execute the tick. @param DeltaTime - frame time to advance, in seconds @param TickType - kind of tick for this frame @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completion of this task until certain child tasks are complete.
- L31 _public prototype_ `virtual FString DiagnosticMessage() override;` — Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph
- L34 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;` — Function used to describe this tick for active tick reporting.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FAttributeBasedRootMotionComponentPrePhysicsTickFunction> : public TStructOpsTypeTraitsBase2<FAttributeBasedRootMotionComponentPrePhysicsTickFunction>`  
_L37-43_
- inherits: `TStructOpsTypeTraitsBase2<FAttributeBasedRootMotionComponentPrePhysicsTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L40-42_

#### enum `EAttributeBasedRootMotionMode`  
`enum class EAttributeBasedRootMotionMode`  
_L47-51_
- reflection: `UENUM()`
- L49 _public enumerator_ `ApplyDelta`
- L50 _public enumerator_ `ApplyVelocity`

#### class `UAttributeBasedRootMotionComponent`  
`class UAttributeBasedRootMotionComponent : public UActorComponent`  
_L56-93_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Movement, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L61 _public prototype_ `UAttributeBasedRootMotionComponent(const FObjectInitializer& ObjectInitializer);`
- L63 _public prototype_ `virtual void InitializeComponent() override;`
- L64 _public prototype_ `virtual void RegisterComponentTickFunctions(bool bRegister) override;`
- L66 _public prototype_ `void PrePhysicsTickComponent(float DeltaTime);`
- L67 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L70 _public function_ `inline ACharacter* GetCharacterOwner() const` — Gets the character this component belongs to
- L73 _public member_ `bool bEnableRootMotion = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Runtime")`
- L77 _public member_ `EAttributeBasedRootMotionMode Mode = EAttributeBasedRootMotionMode::ApplyDelta;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L82 _protected member_ `FAttributeBasedRootMotionComponentPrePhysicsTickFunction PrePhysicsTickFunction;` — Pre-physics tick function for this character
- L86 _protected member_ `TWeakObjectPtr<ACharacter> CharacterOwner;` — `UPROPERTY(Transient)` — Character this component belongs to
- L88 _protected member_ `FTransform PrevTransform;`
- L89 _protected member_ `bool PrevTransformValid = false;`
- L91 _protected member_ `FVector TranslationVelocity {0, 0, 0};`
- L92 _protected member_ `FVector RotationVelocity {0, 0, 0};`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`
- L41 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon082317540103`)

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarping.h` (Public)


#### class `FMotionWarpingModule`  
`class FMotionWarpingModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingAdapter.h` (Public)


#### class `UMotionWarpingBaseAdapter`  
`class UMotionWarpingBaseAdapter : public UObject`  
_L16-54_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: MotionWarpingBaseAdapter: base class to adapt/apply motion warping to a target. Concrete subclasses should override
- L21 _public prototype_ `virtual ~UMotionWarpingBaseAdapter() = default;`
- L23 _public function_ `virtual AActor* GetActor() const`
- L24 _public function_ `virtual USkeletalMeshComponent* GetMesh() const`
- L27 _public function_ `virtual FTransform GetCurrentTransform() const` — Current Transform. Warping should use this as child adapters may not have an actor.
- L38 _public function_ `virtual FVector GetVisualRootLocation() const` — Current visual root (IE: Bottom of actor capsule).
- L44 _public function_ `FQuat GetCurrentRotation() const` — Current Transform Rotation. Utility method to make API consistent.
- L49 _public function_ `virtual FVector GetBaseVisualTranslationOffset() const`
- L50 _public function_ `virtual FQuat GetBaseVisualRotationOffset() const`
- L53 _public member_ `FOnWarpLocalspaceRootMotionWithContext WarpLocalRootMotionDelegate;` — A MotionWarpingComponent will bind to this delegate to perform warping when it is triggered

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnWarpLocalspaceRootMotionWithContext, const FTransform&, float, const FMotionWarpingUpdateContext*) DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnWarpWorldspaceRootMotionWithContext, const FTransform&, float, const FMotionWarpingUpdateContext*) UCLASS(MinimalAPI, Abstract) class UMotionWarpingBaseAdapter : public UObject { GENERATED_BODY() public: virtual ~UMotionWarpingBaseAdapter() = default; virtual AActor* GetActor() const { return nullptr; } virtual USkeletalMeshComponent* GetMesh() const { return nullptr; }`
- L10 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FTransform, FOnWarpWorldspaceRootMotionWithContext, const FTransform&, float, const FMotionWarpingUpdateContext*) UCLASS(MinimalAPI, Abstract) class UMotionWarpingBaseAdapter : public UObject { GENERATED_BODY() public: virtual ~UMotionWarpingBaseAdapter() = default; virtual AActor* GetActor() const { return nullptr; } virtual USkeletalMeshComponent* GetMesh() const { return nullptr; }`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingCharacterAdapter.h` (Public)


#### class `UMotionWarpingCharacterAdapter`  
`class UMotionWarpingCharacterAdapter : public UMotionWarpingBaseAdapter`  
_L13-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMotionWarpingBaseAdapter`
- desc: Adapter for Character / ChararacterMovementComponent actors to participate in motion warping
- L18 _public prototype_ `virtual void BeginDestroy() override;`
- L20 _public prototype_ `void SetCharacter(ACharacter* InCharacter);`
- L22 _public prototype_ `virtual AActor* GetActor() const override;`
- L23 _public prototype_ `virtual USkeletalMeshComponent* GetMesh() const override;`
- L24 _public prototype_ `virtual FVector GetVisualRootLocation() const override;`
- L25 _public prototype_ `virtual FVector GetBaseVisualTranslationOffset() const override;`
- L26 _public prototype_ `virtual FQuat GetBaseVisualRotationOffset() const override;`
- L30 _private prototype_ `FTransform WarpLocalRootMotionOnCharacter(const FTransform& LocalRootMotionTransform, UCharacterMovementComponent* TargetMoveComp, float DeltaSeconds);` — Triggered when the character says it's time to pre-process local root motion. This adapter catches the request and passes along to the Warping component
- L33 _private member_ `TWeakObjectPtr<ACharacter> TargetCharacter;` — The associated character

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingComponent.h` (Public)


#### struct `FMotionWarpingCVars`  
`struct FMotionWarpingCVars`  
_L29-36_
- L31 _public member_ `static TAutoConsoleVariable<int32> CVarMotionWarpingDisable;`
- L32 _public member_ `static TAutoConsoleVariable<int32> CVarMotionWarpingDebug;`
- L33 _public member_ `static TAutoConsoleVariable<float> CVarMotionWarpingDrawDebugDuration;`
- L34 _public member_ `static TAutoConsoleVariable<int32> CVarWarpedTargetDebug;`
- L35 _public member_ `static TAutoConsoleVariable<int32> CVarWarpedSwitchOffConditionDebug;`

#### struct `FMotionWarpingWindowData`  
`struct FMotionWarpingWindowData`  
_L40-52_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public member_ `TObjectPtr<UAnimNotifyState_MotionWarping> AnimNotify = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L48 _public member_ `float StartTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L51 _public member_ `float EndTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`

#### class `UMotionWarpingUtilities`  
`class UMotionWarpingUtilities : public UBlueprintFunctionLibrary`  
_L56-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L63 _public prototype_ `static void ExtractLocalSpacePose(const UAnimSequenceBase* Animation, const FBoneContainer& BoneContainer, float Time, bool bExtractRootMotion, FCompactPose& OutPose);` — Extract bone pose in local space for all bones in BoneContainer. If Animation is a Montage the pose is extracted from the first track
- L66 _public prototype_ `static void ExtractComponentSpacePose(const UAnimSequenceBase* Animation, const FBoneContainer& BoneContainer, float Time, bool bExtractRootMotion, FCSPose<FCompactPose>& OutPose);` — Extract bone pose in component space for all bones in BoneContainer. If Animation is a Montage the pose is extracted from the first track
- L70 _public prototype_ `static FTransform ExtractRootMotionFromAnimation(const UAnimSequenceBase* Animation, float StartTime, float EndTime);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Extract Root Motion transform from a contiguous position range
- L73 _public prototype_ `static FTransform ExtractRootTransformFromAnimation(const UAnimSequenceBase* Animation, float Time);` — Extract root bone transform at a given time
- L77 _public prototype_ `static void GetMotionWarpingWindowsFromAnimation(const UAnimSequenceBase* Animation, TArray<FMotionWarpingWindowData>& OutWindows);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — @return All the MotionWarping windows within the supplied animation
- L81 _public prototype_ `static void GetMotionWarpingWindowsForWarpTargetFromAnimation(const UAnimSequenceBase* Animation, FName WarpTargetName, TArray<FMotionWarpingWindowData>& OutWindows);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — @return All the MotionWarping windows within the supplied animation for a given Warp Target
- L84 _public prototype_ `static FTransform CalculateRootTransformRelativeToWarpPointAtTime(const ACharacter& Character, const UAnimSequenceBase* Animation, float Time, const FName& WarpPointBoneName);` — @return root transform relative to the warp point bone at the supplied time
- L85 _public prototype_ `static FTransform CalculateRootTransformRelativeToWarpPointAtTime(const UMotionWarpingBaseAdapter& WarpingAdapter, const UAnimSequenceBase* Animation, float Time, const FName& WarpPointBoneName);`
- L88 _public prototype_ `static FTransform CalculateRootTransformRelativeToWarpPointAtTime(const ACharacter& Character, const UAnimSequenceBase* Animation, float Time, const FTransform& WarpPointTransform);` — @return root transform relative to the warp point transform at the supplied time
- L89 _public prototype_ `static FTransform CalculateRootTransformRelativeToWarpPointAtTime(const UMotionWarpingBaseAdapter& WarpingAdapter, const UAnimSequenceBase* Animation, float Time, const FTransform& WarpPointTransform);`
- L93 _public prototype_ `static void ExtractBoneTransformFromAnimationAtTime(const UAnimInstance* AnimInstance, const UAnimSequenceBase* Animation, float Time, bool bExtractRootMotion, FName BoneName, bool bLocalSpace, FTransform& OutTransform);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Extract bone transform from animation at a given time

#### class `UMotionWarpingComponent`  
`class UMotionWarpingComponent : public UActorComponent`  
_L100-298_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Movement, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L112 _public member_ `bool bSearchForWindowsInAnimsWithinMontages;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Whether to look inside animations within montage when looking for warping windows
- L116 _public member_ `FMotionWarpingPreUpdate OnPreUpdate;` — `UPROPERTY(BlueprintAssignable, Category = "Motion Warping")` — Event called before Root Motion Modifiers are updated
- L118 _public prototype_ `UMotionWarpingComponent(const FObjectInitializer& ObjectInitializer);`
- L120 _public prototype_ `virtual void InitializeComponent() override;`
- L121 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;`
- L124 _public prototype_ `UMotionWarpingBaseAdapter* CreateOwnerAdapter(TSubclassOf<UMotionWarpingBaseAdapter> AdapterClass);` — Set a new adapter of a particular type
- L127 _public function_ `template <class T> T* CreateOwnerAdapter()`
- L134 _public function_ `UMotionWarpingBaseAdapter* GetOwnerAdapter() const` — Get the current adapter to the owner
- L137 _public function_ `inline const TArray<URootMotionModifier*>& GetModifiers() const` — Returns the list of root motion modifiers
- L140 _public prototype_ `bool ContainsModifier(const UAnimSequenceBase* Animation, float StartTime, float EndTime) const;` — Check if we contain a RootMotionModifier for the supplied animation and time range
- L143 _public prototype_ `int32 AddModifier(URootMotionModifier* Modifier);` — Add a new modifier
- L147 _public prototype_ `void DisableAllRootMotionModifiers();` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Mark all the modifiers as Disable
- L149 _public prototype_ `URootMotionModifier* AddModifierFromTemplate(URootMotionModifier* Template, const UAnimSequenceBase* Animation, float StartTime, float EndTime);`
- L152 _public function_ `inline const FMotionWarpingTarget* FindWarpTarget(const FName& WarpTargetName) const` — Find the target associated with a specified name
- L159 _public function_ `void FindWarpTarget(FName WarpTargetName, FMotionWarpingTarget& MotionWarpingTarget, bool& bFound)` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")`
- L174 _public function_ `inline TConstArrayView<FMotionWarpingTarget> GetWarpTargets() const` — Returns the full list of warp targets
- L178 _public prototype_ `void AddOrUpdateWarpTarget(const FMotionWarpingTarget& WarpTarget);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Adds or update a warp target
- L186 _public prototype_ `void AddOrUpdateWarpTargetFromTransform(FName WarpTargetName, FTransform TargetTransform);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Create and adds or update a target associated with a specified name @param WarpTargetName Warp target identifier @param TargetTransform Transform used to set the location and rotation for the warp target
- L200 _public prototype_ `void AddOrUpdateWarpTargetFromComponent(FName WarpTargetName, const USceneComponent* Component, FName BoneName, bool bFollowComponent, EWarpTargetLocationOffsetDirection LocationOffsetDirection = EWarpTargetLocationOffsetDirection::TargetsForwardVector, FVector LocationOffset = FVector::ZeroVector, FRotator RotationOffset = FRotator::ZeroRotator);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Create and adds or update a target associated with a specified name @param WarpTargetName Warp target identifier @param Component Scene Component used to get the target transform @param BoneName Optional bone or socket in the component used to get the target transform. @param bFollowComponent Whether the target transform should update while the warping is active. Useful for tracking moving targets. Note that this will be one frame off if our owner ticks before the target actor. Add tick pre-requisites to avoid this. @param LocationOffsetDirection Direction of LocationOffset @param LocationOffset Optional translation offset to apply to the transform we get from the component @param RotationOffset Optional rotation offset to apply to the transform we get from the component
- L203 _public prototype_ `void AddOrUpdateWarpTargetFromComponent(FName WarpTargetName, const USceneComponent* Component, FName BoneName, bool bFollowComponent, FVector LocationOffset = FVector::ZeroVector, FRotator RotationOffset = FRotator::ZeroRotator);` — @TODO: Deprecate this.
- L211 _public function_ `void AddOrUpdateWarpTargetFromLocation(FName WarpTargetName, FVector TargetLocation)` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Create and adds or update a target associated with a specified name @param WarpTargetName Warp target identifier @param TargetLocation Location for the warp target
- L222 _public function_ `void AddOrUpdateWarpTargetFromLocationAndRotation(FName WarpTargetName, FVector TargetLocation, FRotator TargetRotation)` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Create and adds or update a target associated with a specified name @param WarpTargetName Warp target identifier @param TargetLocation Location for the warp target
- L229 _public prototype_ `int32 RemoveWarpTarget(FName WarpTargetName);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Removes the warp target associated with the specified key
- L233 _public prototype_ `int32 RemoveAllWarpTargets();` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Removes all warp targets
- L237 _public prototype_ `int32 RemoveWarpTargets(const TArray<FName>& WarpTargetNames);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")` — Removes multiple warp targets
- L240 _public prototype_ `void AddSwitchOffCondition(FName WarpTargetName, UMotionWarpingSwitchOffCondition* Condition);` — `UFUNCTION(BlueprintCallable, Category="Motion Warping|Experimental")`
- L242 _public prototype_ `void RemoveSwitchOffConditions(FName WarpTargetName);`
- L244 _public prototype_ `FSwitchOffConditionData* FindSwitchOffConditionData(FName WarpTargetName);`
- L247 _public prototype_ `void BeginTrajectoryPredictions(const FAnimMontageInstance* MontageInstance);` — Creates Prediction adapter if needed and swaps state to prediction state
- L250 _public prototype_ `void EndTrajectoryPredictions();` — Reverts state back to before any predictions
- L253 _public prototype_ `bool IsPredictingTrajectory() const;` — True if we are currentl prediciting a trajectory
- L259 _protected member_ `TObjectPtr<UMotionWarpingBaseAdapter> OwnerAdapter;` — `UPROPERTY(Transient, VisibleInstanceOnly, Category = "Warp State")` — Adapter that connects motion warping to an owner
- L273 _protected member_ `TArray<TObjectPtr<URootMotionModifier>> Modifiers;` — `UPROPERTY(Transient, VisibleInstanceOnly, Category = "Warp State")` — List of root motion modifiers
- L276 _protected member_ `TArray<FMotionWarpingTarget> WarpTargets;` — `UPROPERTY(Transient, Replicated, VisibleInstanceOnly, Category = "Warp State")`
- L279 _protected member_ `TArray<FSwitchOffConditionData> SwitchOffConditions;` — `UPROPERTY(Transient, Experimental, VisibleInstanceOnly, Category = "Warp State")`
- L287 _protected member_ `TOptional<FVector> OriginalRootMotionAccum;`
- L288 _protected member_ `TOptional<FVector> WarpedRootMotionAccum;`
- L291 _protected prototype_ `void UpdateSwitchOffConditions();`
- L293 _protected prototype_ `void UpdateWithContext(const FMotionWarpingUpdateContext& Context, float DeltaSeconds);`
- L295 _protected prototype_ `bool FindAndUpdateWarpTarget(const FMotionWarpingTarget& WarpTarget);`
- L297 _protected prototype_ `FTransform ProcessRootMotionPreConvertToWorld(const FTransform& InRootMotion, float DeltaSeconds, const FMotionWarpingUpdateContext* InContext=nullptr);` — callback with optional context

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`
- L26 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotionWarping, Log, All);`
- L26 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMotionWarping, Log, All);`
- L97 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMotionWarpingPreUpdate, class UMotionWarpingComponent*, MotionWarpingComp);`
- L97 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMotionWarpingPreUpdate, class UMotionWarpingComponent*, MotionWarpingComp);`
- L154 _function_ `return WarpTargets.FindByPredicate([&WarpTargetName](const FMotionWarpingTarget& WarpTarget){ return WarpTarget.Name == WarpTargetName; });` (scope `UMotionWarpingComponent::FindWarpTarget`)

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingFunctionLibrary.h` (Public)


#### class `UMotionWarpingFunctionLibrary`  
`class UMotionWarpingFunctionLibrary : public UBlueprintFunctionLibrary`  
_L15-23_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "MotionWarpingLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- desc: Motion Warping Function Library
- L21 _public prototype_ `static FMotionWarpingTarget MakeMotionWarpingTarget(const FName Name, const FVector Location, const FRotator Rotation, const USceneComponent* Component, FName BoneName, bool bFollowComponent, EWarpTargetLocationOffsetDirection LocationOffsetDirection, const AActor* AvatarActor, const FVector LocationOffset, const FRotator RotationOffset);` — `UFUNCTION(BlueprintPure, Category = "Motion Warping", meta = (NativeMakeFunc))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingMontageTrajectoryAdapter.h` (Public)


#### struct `FMotionWarpingSwapState`  
`struct FMotionWarpingSwapState`  
_L16-38_
- reflection: `USTRUCT(Experimental)`
- desc: Temp state to iterate on for properties normally owned by the warping component. Used so we can predict without mutating real actor state.
- L22 _public member_ `TArray<TObjectPtr<URootMotionModifier>> Modifiers;` — `UPROPERTY(Transient, VisibleInstanceOnly, Category = "Warp State")` — List of root motion modifiers, stored as modifiers can be removed during prediction
- L26 _public member_ `TArray<FMotionWarpingTarget> WarpTargets;` — `UPROPERTY(Transient, VisibleInstanceOnly, Category = "Warp State")` — List of warp targets
- L34 _public member_ `TArray<FSwitchOffConditionData> SwitchOffConditions;` — `UPROPERTY(Transient, Experimental, VisibleInstanceOnly, Category = "Warp State")` — List of switch off conditions @TODO: Currently unused. Switch off conditions aren't actorless yet & to be accurate we may want to also predict against target actor trajectories
- L37 _public member_ `TArray<TSharedPtr<FRootMotionModifierSwapState>> ModifierSwapStates;` — State of modifiers prior to prediction

#### class `UMotionWarpingMontageTrajectoryAdapter`  
`class UMotionWarpingMontageTrajectoryAdapter : public UMotionWarpingBaseAdapter`  
_L42-89_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UMotionWarpingBaseAdapter`
- desc: Adapter for montage trajectories to participate in motion warping
- L49 _public prototype_ `void InitializeFrom(const UMotionWarpingBaseAdapter* InAdapter, const FAnimMontageInstance* InMontageInstance);` — Initialize current transforms from some other adapter & swaps component state to prediction state.
- L52 _public prototype_ `void RestoreState();` — Restores component state to before any prediction has been done
- L54 _public prototype_ `virtual FTransform GetCurrentTransform() const override;`
- L55 _public prototype_ `virtual FVector GetVisualRootLocation() const override;`
- L57 _public prototype_ `void SetCurrentTransform(const FTransform InCurrentTransform);`
- L58 _public prototype_ `void SetVisualRootLocation(const FVector InVisualRootLocation);`
- L60 _public prototype_ `virtual FVector GetBaseVisualTranslationOffset() const override;`
- L61 _public prototype_ `virtual FQuat GetBaseVisualRotationOffset() const override;`
- L64 _public prototype_ `FTransform WarpLocalRootMotionOnMontageTrajectory(const FTransform& LocalRootMotionTransform, float DeltaSeconds, float InMontagePreviousPosition, float InMontageCurrentPosition);` — Triggered iteratively as we sample the trajectory
- L70 _public member_ `FMotionWarpingSwapState CachedWarpState;` — `UPROPERTY(Transient)` — Cached state before any prediction, we restore this after predicting.
- L74 _public member_ `TObjectPtr<const UAnimMontage> Montage;` — `UPROPERTY(Transient)` — Montage to warp trajectory for
- L79 _private member_ `FTransform CurrentTransform = FTransform::Identity;` — Warping properties captured in adapter initialization that update as we iterate
- L80 _private member_ `FVector VisualRootLocation = FVector::ZeroVector;`
- L83 _private member_ `FVector BaseVisualTranslationOffset = FVector::ZeroVector;` — Warping properties that do not change after adapter initialization
- L84 _private member_ `FQuat BaseVisualRotationOffset = FQuat::Identity;`
- L87 _private member_ `float MontageWeight = 0.0f;` — Properties for warp context state
- L88 _private member_ `float MontagePlayRate = 0.0f;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/MotionWarpingSwitchOffCondition.h` (Public)


#### struct `FSwitchOffConditionData`  
`struct FSwitchOffConditionData`  
_L14-39_
- reflection: `USTRUCT(BlueprintType, Experimental)`
- L18 _public function_ `FSwitchOffConditionData() : WarpTargetName(NAME_None), SwitchOffConditions(TArray<UMotionWarpingSwitchOffCondition*>())`
- L22 _public function_ `FSwitchOffConditionData(FName InWarpTargetName, UMotionWarpingSwitchOffCondition* InSwitchOffCondition) : WarpTargetName(InWarpTargetName)`
- L28 _public function_ `FSwitchOffConditionData(FName InWarpTargetName) : WarpTargetName(InWarpTargetName), SwitchOffConditions(TArray<UMotionWarpingSwitchOffCondition*>())`
- L33 _public member_ `FName WarpTargetName;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L36 _public member_ `TArray<TObjectPtr<UMotionWarpingSwitchOffCondition>> SwitchOffConditions;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L38 _public prototype_ `void SetMotionWarpingTarget(const FMotionWarpingTarget* MotionWarpingTarget);`

#### enum `ESwitchOffConditionEffect`  
`enum class ESwitchOffConditionEffect : uint8`  
_L43-57_
- reflection: `UENUM(BlueprintType, Category = "MotionWarping", meta = (Experimental))`
- desc: Result of switch off condition.
- L47 _public enumerator_ `CancelFollow UMETA(DisplayName = "Cancel Follow Component")` — Changes associated motion warping target from component to a location of this component in the frame in which this switch off condition appeared
- L50 _public enumerator_ `CancelWarping UMETA(DisplayName = "Cancel Warping")` — Removes associated motion warping target
- L53 _public enumerator_ `PauseWarping UMETA(DisplayName = "Pause Warping")` — During time slot in the animation, where switch off condition is true, only play root motion, without warping
- L56 _public enumerator_ `PauseRootMotion UMETA(DisplayName = "Pause Root Motion")` — During time slot in the animation, where switch off condition is true, play the animation in place

#### class `UMotionWarpingSwitchOffCondition`  
`class UMotionWarpingSwitchOffCondition : public UObject`  
_L60-119_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew, Experimental, ClassGroup = MotionWarping)`
- inherits: `UObject`
- L67 _public member_ `bool bUseWarpTargetAsTargetLocation = true;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")` — If set to false, switch off condition will use target actor location
- L70 _public member_ `ESwitchOffConditionEffect Effect = ESwitchOffConditionEffect::CancelWarping;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`
- L77 _public function_ `ESwitchOffConditionEffect GetEffect() const` — Initialize switch off condition @param InOwnerActor Actor with MotionWarpingComponent, owning corresponding WarpingTarget @param InTargetActor Target actor used for calculating switch off condition result
- L78 _public prototype_ `bool Check() const;`
- L84 _public prototype_ `FVector GetTargetLocation() const;` — If bUseWarpTargetAsTargetLocation is true, this will return target FMotionWarpingTarget location. If bUseWarpTargetAsTargetLocation is false, this will return target actor location.
- L90 _public prototype_ `FRotator GetTargetRotation() const;` — If bUseWarpTargetAsTargetLocation is true, this will return target FMotionWarpingTarget rotation. If bUseWarpTargetAsTargetLocation is false, this will return target actor rotation.
- L96 _public prototype_ `virtual void SetWarpTargetForDestination(const FMotionWarpingTarget* InMotionWarpingTarget);` — Set warp target as context for calculating switch off condition result if bUseWarpTargetAsTargetLocation is set to true
- L97 _public function_ `virtual bool OnCheck() const`
- L102 _public function_ `virtual FString ExtraDebugInfo() const` — Extra information used for debugging, if CVAR MotionWarping.Debug.SwitchOffCondition is true
- L103 _public prototype_ `virtual bool IsConditionValid() const;`
- L105 _public function_ `virtual void SetOwnerActor(const AActor* InOwnerActor)`
- L106 _public function_ `virtual void SetTargetActor(const AActor* InTargetActor)`
- L107 _public function_ `virtual void SetMotionWarpingTarget(const FMotionWarpingTarget* InMotionWarpingTarget)`
- L110 _protected member_ `bool bIsInitialized = false;`
- L113 _protected member_ `TObjectPtr<const AActor> OwnerActor;` — `UPROPERTY()`
- L116 _protected member_ `TObjectPtr<const AActor> TargetActor;` — `UPROPERTY()`
- L118 _protected member_ `const FMotionWarpingTarget* MotionWarpingTarget = nullptr;`

#### enum `ESwitchOffConditionDistanceOp`  
`enum class ESwitchOffConditionDistanceOp : uint8`  
_L122-126_
- reflection: `UENUM(BlueprintType, Category = "MotionWarping", meta = (Experimental))`
- L124 _public enumerator_ `LessThan`
- L125 _public enumerator_ `GreaterThan`

#### enum `ESwitchOffConditionDistanceAxesType`  
`enum class ESwitchOffConditionDistanceAxesType : uint8`  
_L129-134_
- reflection: `UENUM(BlueprintType, Category = "MotionWarping", meta = (Experimental))`
- L131 _public enumerator_ `AllAxes`
- L132 _public enumerator_ `IgnoreZAxis`
- L133 _public enumerator_ `OnlyZAxis`

#### class `UMotionWarpingSwitchOffDistanceCondition`  
`class UMotionWarpingSwitchOffDistanceCondition : public UMotionWarpingSwitchOffCondition`  
_L137-182_
- reflection: `UCLASS(Experimental)`
- inherits: `UMotionWarpingSwitchOffCondition`
- L143 _public member_ `ESwitchOffConditionDistanceOp Operator;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`
- L146 _public member_ `ESwitchOffConditionDistanceAxesType AxesType;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`
- L149 _public member_ `float Distance;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`
- L167 _public prototype_ `UPARAM(DisplayName = "Owner Actor", ref) AActor* InOwnerActor, UPARAM(DisplayName = "Effect") ESwitchOffConditionEffect InEffect, UPARAM(DisplayName = "Operator") ESwitchOffConditionDistanceOp InOperator, UPARAM(DisplayName = "AxesType") ESwitchOffConditionDistanceAxesType InAxesType, UPARAM(DisplayName = "Distance") float InDistance, UPARAM(DisplayName = "UseWarpTargetAsLocation") bool InbUseWarpTargetAsTargetLocation = true, UPARAM(DisplayName = "TargetActor") AActor* InTargetActor`
- L176 _protected prototype_ `virtual bool OnCheck() const override;`
- L177 _protected prototype_ `virtual FString ExtraDebugInfo() const override;`
- L179 _protected prototype_ `float CalculateSqDistance() const;`
- L180 _protected prototype_ `float CalculateSqDistance2D() const;`
- L181 _protected prototype_ `float CalculateZDistance() const;`

#### enum `ESwitchOffConditionAngleOp`  
`enum class ESwitchOffConditionAngleOp : uint8`  
_L186-190_
- reflection: `UENUM(BlueprintType, Category = "MotionWarping", meta = (Experimental))`
- L188 _public enumerator_ `LessThan`
- L189 _public enumerator_ `GreaterThan`

#### class `UMotionWarpingSwitchOffAngleToTargetCondition`  
`class UMotionWarpingSwitchOffAngleToTargetCondition : public UMotionWarpingSwitchOffCondition`  
_L193-236_
- reflection: `UCLASS(Experimental)`
- inherits: `UMotionWarpingSwitchOffCondition`
- L214 _public prototype_ `UPARAM(DisplayName = "Owner Actor", ref) AActor* InOwnerActor, UPARAM(DisplayName = "Effect") ESwitchOffConditionEffect InEffect, UPARAM(DisplayName = "Operator") ESwitchOffConditionAngleOp InOperator, UPARAM(DisplayName = "Angle") float InAngle, UPARAM(DisplayName = "Ignore Z Axis") bool bInIgnoreZAxis, UPARAM(DisplayName = "TargetActor") bool bInUseWarpTargetAsTargetLocation = true, UPARAM(DisplayName = "TargetActor") AActor* InTargetActor`
- L223 _protected prototype_ `virtual bool OnCheck() const override;`
- L224 _protected prototype_ `virtual FString ExtraDebugInfo() const override;`
- L226 _protected prototype_ `float CalculateAngleToTarget() const;`
- L229 _protected member_ `ESwitchOffConditionAngleOp Operator;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`
- L232 _protected member_ `float Angle;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping", meta = (ForceUnits="degrees"))`
- L235 _protected member_ `bool bIgnoreZAxis;` — `UPROPERTY(EditAnywhere, Category = "MotionWarping")`

#### enum `ESwitchOffConditionCompositeOp`  
`enum class ESwitchOffConditionCompositeOp : uint8`  
_L239-243_
- reflection: `UENUM(BlueprintType, Category = "MotionWarping", meta = (Experimental))`
- L241 _public enumerator_ `Or UMETA(DisplayName = "OR")`
- L242 _public enumerator_ `And UMETA(DisplayName = "AND")`

#### class `UMotionWarpingSwitchOffCompositeCondition`  
`class UMotionWarpingSwitchOffCompositeCondition : public UMotionWarpingSwitchOffCondition`  
_L246-290_
- reflection: `UCLASS(Experimental)`
- inherits: `UMotionWarpingSwitchOffCondition`
- L250 _public prototype_ `virtual void SetOwnerActor(const AActor* InOwnerActor) override;`
- L251 _public prototype_ `virtual void SetTargetActor(const AActor* InTargetActor) override;`
- L252 _public prototype_ `virtual void SetMotionWarpingTarget(const FMotionWarpingTarget* InMotionWarpingTarget) override;`
- L268 _public prototype_ `UPARAM(DisplayName = "Owner Actor", ref) AActor* InOwnerActor, UPARAM(DisplayName = "Effect") ESwitchOffConditionEffect InEffect, UPARAM(DisplayName = "Switch Off Condition A", ref) UMotionWarpingSwitchOffCondition* InSwitchOffConditionA, UPARAM(DisplayName = "Logic Operator") ESwitchOffConditionCompositeOp InLogicOperator, UPARAM(DisplayName = "Switch Off Condition B", ref) UMotionWarpingSwitchOffCondition* InSwitchOffConditionB, UPARAM(DisplayName = "Use Warp Target As Location") bool bInUseWarpTargetAsTargetLocation = true, UPARAM(DisplayName = "TargetActor") AActor* InTargetActor`
- L277 _protected prototype_ `virtual void SetWarpTargetForDestination(const FMotionWarpingTarget* InMotionWarpingTarget) override;`
- L278 _protected prototype_ `virtual bool OnCheck() const override;`
- L279 _protected prototype_ `virtual FString ExtraDebugInfo() const override;`
- L280 _protected prototype_ `virtual bool IsConditionValid() const override;`
- L283 _protected member_ `TObjectPtr<UMotionWarpingSwitchOffCondition> SwitchOffConditionA;` — `UPROPERTY(EditAnywhere, Instanced, Category="MotionWarping")`
- L286 _protected member_ `ESwitchOffConditionCompositeOp LogicOperator;` — `UPROPERTY(EditAnywhere, Category="MotionWarping")`
- L289 _protected member_ `TObjectPtr<UMotionWarpingSwitchOffCondition> SwitchOffConditionB;` — `UPROPERTY(EditAnywhere, Instanced, Category="MotionWarping")`

#### class `UMotionWarpingSwitchOffBlueprintableCondition`  
`class UMotionWarpingSwitchOffBlueprintableCondition : public UMotionWarpingSwitchOffCondition`  
_L293-334_
- reflection: `UCLASS(Blueprintable, Experimental)`
- inherits: `UMotionWarpingSwitchOffCondition`
- L297 _private prototype_ `virtual bool OnCheck() const override;`
- L298 _private prototype_ `virtual FString ExtraDebugInfo() const override;`
- L312 _private prototype_ `UPARAM(DisplayName = "Owner Actor", ref) AActor* InOwnerActor, UPARAM(DisplayName = "Effect") ESwitchOffConditionEffect InEffect, UPARAM(DisplayName = "Blueprintable Switch Off Condition") TSubclassOf<UMotionWarpingSwitchOffBlueprintableCondition> InBlueprintableCondition, UPARAM(DisplayName = "Use Warp Target As Location") bool bInUseWarpTargetAsTargetLocation = true, UPARAM(DisplayName = "TargetActor") AActor* InTargetActor`
- L319 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L323 _public prototype_ `UPARAM(DisplayName = "Owner Actor") const AActor* InOwnerActor, UPARAM(DisplayName = "Target Actor") const AActor* InTargetActor, UPARAM(DisplayName = "Target Location") FVector InTargetLocation, UPARAM(DisplayName = "Use warp target as target location") bool bInUse`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/RootMotionModifier.h` (Public)


#### struct `FMotionWarpingUpdateContext`  
`struct FMotionWarpingUpdateContext`  
_L25-46_
- reflection: `USTRUCT()`
- desc: Context passed to any active root motion modifier during the update phase. Contains relevant data from the animation that contributed to root motion this frame (or in the past when replaying saved moves)
- L30 _public member_ `TWeakObjectPtr<const UAnimSequenceBase> Animation = nullptr;` — `UPROPERTY()`
- L33 _public member_ `float PreviousPosition = 0.f;` — `UPROPERTY()`
- L36 _public member_ `float CurrentPosition = 0.f;` — `UPROPERTY()`
- L39 _public member_ `float Weight = 0.f;` — `UPROPERTY()`
- L42 _public member_ `float PlayRate = 1.f;` — `UPROPERTY()`
- L45 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY()`

#### enum `ERootMotionModifierState`  
`enum class ERootMotionModifierState : uint8`  
_L50-63_
- reflection: `UENUM(BlueprintType)`
- desc: The possible states of a Root Motion Modifier
- L53 _public enumerator_ `Waiting` — The modifier is waiting for the animation to hit the warping window
- L56 _public enumerator_ `Active` — The modifier is active and currently affecting the final root motion
- L59 _public enumerator_ `MarkedForRemoval` — The modifier has been marked for removal. Usually because the warping window is done
- L62 _public enumerator_ `Disabled` — The modifier will remain in the list (as long as the window is active) but will not modify the root motion

#### class `URootMotionModifier`  
`class URootMotionModifier : public UObject`  
_L71-175_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, EditInlineNew)`
- inherits: `UObject`
- L79 _public member_ `TWeakObjectPtr<const UAnimSequenceBase> Animation = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Source of the root motion we are warping
- L83 _public member_ `float StartTime = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Start time of the warping window
- L87 _public member_ `float EndTime = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — End time of the warping window
- L91 _public member_ `float PreviousPosition = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Previous playback time of the animation
- L95 _public member_ `float CurrentPosition = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Current playback time of the animation
- L99 _public member_ `float Weight = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Current blend weight of the animation
- L103 _public member_ `float PlayRate = 1.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")` — Current play rate of the animation
- L107 _public member_ `FTransform StartTransform;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Defaults")` — Character owner transform at the time this modifier becomes active
- L111 _public member_ `float ActualStartTime = 0.f;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Defaults")` — Actual playback time when the modifier becomes active
- L115 _public member_ `FTransform TotalRootMotionWithinWindow;` — `UPROPERTY(Transient, BlueprintReadOnly, Category = "Defaults")` — Total root motion within the warping window
- L119 _public member_ `FOnRootMotionModifierDelegate OnActivateDelegate;` — `UPROPERTY()` — Delegate called when this modifier is activated (starts affecting the root motion)
- L123 _public member_ `FOnRootMotionModifierDelegate OnUpdateDelegate;` — `UPROPERTY()` — Delegate called when this modifier updates while active (affecting the root motion)
- L127 _public member_ `FOnRootMotionModifierDelegate OnDeactivateDelegate;` — `UPROPERTY()` — Delegate called when this modifier is deactivated (stops affecting the root motion)
- L129 _public prototype_ `URootMotionModifier(const FObjectInitializer& ObjectInitializer);`
- L132 _public prototype_ `virtual void OnStateChanged(ERootMotionModifierState LastState);` — Called when the state of the modifier changes
- L135 _public prototype_ `void SetState(ERootMotionModifierState NewState);` — Sets the state of the modifier
- L138 _public function_ `inline ERootMotionModifierState GetState() const` — Returns the state of the modifier
- L141 _public prototype_ `UMotionWarpingComponent* GetOwnerComponent() const;` — Returns a pointer to the component that owns this modifier
- L144 _public prototype_ `UMotionWarpingBaseAdapter* GetOwnerAdapter() const;` — Returns a pointer to the adapter to the object being warped
- L147 _public prototype_ `AActor* GetActorOwner() const;` — Returns a pointer to the actor that owns the component that owns this modifier
- L150 _public prototype_ `virtual TSharedPtr<FRootMotionModifierSwapState> GetSwapState() const;` — Returns a snapshot of the current state of this modifier
- L153 _public prototype_ `virtual void RestoreFromSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState);` — Restores this modifer to some previous state snapshot
- L156 _public prototype_ `virtual void PopulateSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState) const;` — Populates given swap state
- L158 _public prototype_ `virtual void Update(const FMotionWarpingUpdateContext& Context);`
- L159 _public function_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds)`
- L161 _public function_ `inline const UAnimSequenceBase* GetAnimation() const`
- L164 _public function_ `virtual void DrawInEditor(class FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* InAnimation, const FAnimNotifyEvent& NotifyEvent) const`
- L165 _public function_ `virtual void DrawCanvasInEditor(class FCanvas& Canvas, class FSceneView& View, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* InAnimation, const FAnimNotifyEvent& NotifyEvent) const`
- L174 _private member_ `ERootMotionModifierState State = ERootMotionModifierState::Waiting;` — `UPROPERTY()` — Current state

#### struct `FRootMotionModifierSwapState`  
`struct FRootMotionModifierSwapState`  
_L178-192_
- desc: Stateful properties for URootMotionModifier
- L180 _public prototype_ `virtual ~FRootMotionModifierSwapState() = default;`
- L182 _public member_ `float StartTime = 0.f;`
- L183 _public member_ `float EndTime = 0.f;`
- L184 _public member_ `float PreviousPosition = 0.f;`
- L185 _public member_ `float CurrentPosition = 0.f;`
- L186 _public member_ `float Weight = 0.f;`
- L187 _public member_ `float PlayRate = 1.f;`
- L188 _public member_ `FTransform StartTransform;`
- L189 _public member_ `float ActualStartTime = 0.f;`
- L190 _public member_ `FTransform TotalRootMotionWithinWindow;`
- L191 _public member_ `ERootMotionModifierState State = ERootMotionModifierState::Waiting;`

#### enum `EWarpTargetLocationOffsetDirection`  
`enum class EWarpTargetLocationOffsetDirection : uint8`  
_L195-203_
- reflection: `UENUM(BlueprintType, meta=(Experimental))`
- L198 _public enumerator_ `TargetsForwardVector` — LocationOffset.X translates the target transform along the target component's forward vector.
- L200 _public enumerator_ `VectorFromTargetToOwner` — LocationOffset.X translates the target transform along the vector from the target to the owning actor.
- L202 _public enumerator_ `WorldSpace` — LocationOffset moves the target transform in world space

#### struct `FMotionWarpingTarget`  
`struct FMotionWarpingTarget`  
_L210-297_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake = "/Script/MotionWarping.MotionWarpingFunctionLibrary.MakeMotionWarpingTarget"))`
- desc: Represents a point of alignment in the world
- L216 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Unique name for this warp target
- L220 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — When the warp target is created from a component this stores the location of the component at the time of creation, otherwise its the location supplied by the user
- L224 _public member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — When the warp target is created from a component this stores the rotation of the component at the time of creation, otherwise its the rotation supplied by the user
- L228 _public member_ `TWeakObjectPtr<const USceneComponent> Component;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Optional component used to calculate the final target transform
- L232 _public member_ `FName BoneName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Optional bone name in the component used to calculate the final target transform
- L237 _public member_ `bool bFollowComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Whether the target transform calculated from a component and an optional bone should be updated during the warp Only relevant when the warp target is created from a component
- L242 _public member_ `EWarpTargetLocationOffsetDirection LocationOffsetDirection = EWarpTargetLocationOffsetDirection::TargetsForwardVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experimental)` — Determines how LocationOffset is applied by FMotionWarpingTarget when calculating a target transform Only relevant when the warp target is created from a component
- L246 _public member_ `FVector LocationOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Optional static location offset. Only relevant when the warp target is created from a component
- L250 _public member_ `FRotator RotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Optional static rotation offset. Only relevant when the warp target is created from a component
- L254 _public member_ `TWeakObjectPtr<const AActor> AvatarActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Optional Actor that uses this warping target. Used for offset calculation of target transform is provided via component
- L256 _public member_ `bool bCacheForwardOffset = false;`
- L257 _public member_ `FVector CachedForwardOffset = FVector::ZeroVector;`
- L258 _public member_ `FVector CachedRightOffset = FVector::ZeroVector;`
- L259 _public member_ `FVector CachedUpOffset = FVector::ZeroVector;`
- L261 _public member_ `bool bWarpingPaused = false;`
- L262 _public member_ `bool bRootMotionPaused = false;`
- L264 _public function_ `FMotionWarpingTarget() : Name(NAME_None), Location(FVector::ZeroVector), Rotation(FRotator::ZeroRotator), Component(nullptr), BoneName(NAME_None), bFollowComponent(false)`
- L267 _public function_ `FMotionWarpingTarget(const FName& InName, const FTransform& InTransform) : Name(InName), Location(InTransform.GetLocation()), Rotation(InTransform.Rotator()), Component(nullptr), BoneName(NAME_None), bFollowComponent(false)`
- L270 _public prototype_ `FMotionWarpingTarget(const FName& InName, const USceneComponent* InComp, FName InBoneName, bool bInbFollowComponent, EWarpTargetLocationOffsetDirection InLocationOffsetDirection = EWarpTargetLocationOffsetDirection::TargetsForwardVector, const AActor* InAvatarActor = nullptr, const FVector& InLocOffset = FVector::ZeroVector, const FRotator& InRotOffset = FRotator::ZeroRotator);`
- L273 _public prototype_ `FMotionWarpingTarget(const FName& InName, const USceneComponent* InComp, FName InBoneName, bool bInbFollowComponent, const FVector& InLocOffset = FVector::ZeroVector, const FRotator& InRotOffset = FRotator::ZeroRotator);` — @TODO: Deprecate this.
- L275 _public prototype_ `FTransform GetTargetTrasform() const;`
- L276 _public prototype_ `void CacheOffset(const FTransform& InTransform);`
- L277 _public prototype_ `void RecalculateOffset(FTransform& InTransform) const;`
- L279 _public function_ `inline FVector GetLocation() const`
- L280 _public function_ `inline FQuat GetRotation() const`
- L281 _public function_ `inline FRotator Rotator() const`
- L283 _public function_ `inline bool operator==(const FMotionWarpingTarget& Other) const`
- L289 _public function_ `inline bool operator!=(const FMotionWarpingTarget& Other) const`
- L295 _public prototype_ `static FTransform GetTargetTransformFromComponent(const USceneComponent* Comp, const FName& BoneName);`

#### enum `EMotionWarpRotationType`  
`enum class EMotionWarpRotationType : uint8`  
_L300-313_
- reflection: `UENUM(BlueprintType)`
- L303 _public enumerator_ `Default` — Character rotates to match the rotation of the sync point
- L306 _public enumerator_ `Facing` — Character rotates to face the sync point
- L309 _public enumerator_ `OppositeDefault UE_DEPRECATED(5.8, "Use AdditionalRotationOffset instead") UMETA(Hidden)` — Character rotates to match the rotation of the sync point, rotated by half of full angle around up axis (180 degrees yaw)
- L312 _public enumerator_ `OppositeFacing UE_DEPRECATED(5.8, "Use AdditionalRotationOffset instead") UMETA(Hidden)` — Character rotates to face the sync point with their back. Essentially facing + 180 degrees yaw.

#### enum `EMotionWarpRotationMethod`  
`enum class EMotionWarpRotationMethod : uint8`  
_L316-326_
- reflection: `UENUM(BlueprintType)`
- L319 _public enumerator_ `Slerp` — Rotate with spherical linear interpolation
- L321 _public enumerator_ `SlerpWithClampedRate` — Rotate with spherical linear interpolation, not exceeding a max rotation rate
- L323 _public enumerator_ `ConstantRate` — Rotate with a constant rotation rate
- L325 _public enumerator_ `Scale` — Scale rotation in a way that by the end of the anim notify state the owner's rotation matches the warp target's rotation

#### enum `EWarpPointAnimProvider`  
`enum class EWarpPointAnimProvider : uint8`  
_L330-340_
- reflection: `UENUM(BlueprintType)`
- desc: Method used to extract the warp point from the animation
- L333 _public enumerator_ `None` — No warp point is provided
- L336 _public enumerator_ `Static` — Warp point defined by a 'hard-coded' transform  user can enter through the warping notify
- L339 _public enumerator_ `Bone` — Warp point defined by a bone

#### class `URootMotionModifier_Warp`  
`class URootMotionModifier_Warp : public URootMotionModifier`  
_L343-461_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `URootMotionModifier`
- L350 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L355 _public member_ `FName WarpTargetName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ExposeOnSpawn))` — Name used to find the warp target for this modifier
- L358 _public member_ `EWarpPointAnimProvider WarpPointAnimProvider = EWarpPointAnimProvider::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")`
- L362 _public member_ `FTransform WarpPointAnimTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "WarpPointAnimProvider == EWarpPointAnimProvider::Static"))` — @TODO: Hide from the UI when Target != Static
- L366 _public member_ `FName WarpPointAnimBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "WarpPointAnimProvider == EWarpPointAnimProvider::Bone"))` — @TODO: Hide from the UI when Target != Bone
- L370 _public member_ `bool bWarpTranslation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Whether to warp the translation component of the root motion
- L374 _public member_ `bool bIgnoreZAxis = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bWarpTranslation"))` — Whether to ignore the Z component of the translation. Z motion will remain untouched
- L378 _public member_ `bool bWarpToFeetLocation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bWarpTranslation"))` — Whether we warp the actors location or their foot location to the warp target
- L382 _public member_ `EAlphaBlendOption AddTranslationEasingFunc = UE::Anim::DefaultBlendOption;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bWarpTranslation"))` — Easing function used when adding translation. Only relevant when there is no translation in the animation
- L386 _public member_ `TObjectPtr<class UCurveFloat> AddTranslationEasingCurve = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blend", meta = (EditCondition = "AddTranslationEasingFunc==EAlphaBlendOption::Custom", EditConditionHides))` — Custom curve used to add translation when there is none to warp. Only relevant when AddTranslationEasingFunc is set to Custom
- L390 _public member_ `bool bWarpRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Whether to warp the rotation component of the root motion
- L394 _public member_ `EMotionWarpRotationType RotationType = EMotionWarpRotationType::Default;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bWarpRotation"))` — Whether rotation should be warp to match the rotation of the sync point or to face the sync point
- L398 _public member_ `EMotionWarpRotationMethod RotationMethod = EMotionWarpRotationMethod::Slerp;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bWarpRotation"))` — The method of rotation to use
- L403 _public member_ `bool bSubtractRemainingRootMotion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Should root motion after this notify state be subtracted from warp target transform. This means actor will arrive at warp target transform when the animation finishes, not when the notify ends
- L407 _public member_ `FRotator AdditionalRotationOffset = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Applied as a final rotational offset on the warp target
- L414 _public member_ `float WarpRotationTimeMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "RotationMethod!=EMotionWarpRotationMethod::ConstantRate && RotationMethod!=EMotionWarpRotationMethod::Scale && bWarpRotation"))` — Allow to modify how fast the rotation is warped. e.g if the window duration is 2sec and this is 0.5, the target rotation will be reached in 1sec instead of 2sec
- L418 _public member_ `float WarpMaxRotationRate = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "RotationMethod!=EMotionWarpRotationMethod::Slerp && bWarpRotation"))` — Maximum rotation rate in degrees/sec. Will be the value used in constant rotation rate
- L420 _public prototype_ `URootMotionModifier_Warp(const FObjectInitializer& ObjectInitializer);`
- L423 _public prototype_ `virtual void Update(const FMotionWarpingUpdateContext& Context) override;`
- L427 _public prototype_ `virtual void OnTargetTransformChanged();` — Event called during update if the target transform changes while the warping is active
- L429 _public prototype_ `virtual void OnStateChanged(ERootMotionModifierState LastState) override;`
- L431 _public prototype_ `virtual TSharedPtr<FRootMotionModifierSwapState> GetSwapState() const override;`
- L432 _public prototype_ `virtual void PopulateSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState) const override;`
- L433 _public prototype_ `virtual void RestoreFromSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState) override;`
- L436 _public prototype_ `void PrintLog(const FString& Name, const FTransform& OriginalRootMotion, const FTransform& WarpedRootMotion) const;`
- L439 _public function_ `inline FVector GetTargetLocation() const`
- L440 _public function_ `inline FRotator GetTargetRotator() const`
- L441 _public prototype_ `FQuat GetTargetRotation() const;`
- L443 _public prototype_ `FQuat WarpRotation(const FTransform& RootMotionDelta, const FTransform& RootMotionTotal, float DeltaSeconds);`
- L448 _protected member_ `FTransform CachedTargetTransform = FTransform::Identity;` — `UPROPERTY()`
- L451 _protected member_ `FTransform RootMotionRemainingAfterNotify = FTransform::Identity;` — `UPROPERTY()`
- L454 _protected member_ `TOptional<FTransform> CachedOffsetFromWarpPoint;` — Cached of the offset from the warp target. Used to calculate the final target transform when a warp target is defined in the animation
- L457 _protected member_ `FQuat RotationOffset = FQuat::Identity;` — Rotation offset defined in warp target
- L459 _protected member_ `bool bWarpingPaused = false;`
- L460 _protected member_ `bool bRootMotionPaused = false;`

#### struct `FRootMotionModifier_WarpSwapState`  
`struct FRootMotionModifier_WarpSwapState : public FRootMotionModifierSwapState`  
_L463-472_
- inherits: `FRootMotionModifierSwapState`
- L465 _public member_ `FRotator AdditionalRotationOffset = FRotator::ZeroRotator;`
- L466 _public member_ `FTransform CachedTargetTransform = FTransform::Identity;`
- L467 _public member_ `FTransform RootMotionRemainingAfterNotify = FTransform::Identity;`
- L468 _public member_ `TOptional<FTransform> CachedOffsetFromWarpPoint;`
- L469 _public member_ `FQuat RotationOffset = FQuat::Identity;`
- L470 _public member_ `bool bWarpingPaused = false;`
- L471 _public member_ `bool bRootMotionPaused = false;`

#### class `UDEPRECATED_RootMotionModifier_SimpleWarp`  
`class UDEPRECATED_RootMotionModifier_SimpleWarp : public URootMotionModifier_Warp`  
_L479-487_
- reflection: `UCLASS(MinimalAPI, Deprecated, meta = (DisplayName = "Simple Warp"))`
- inherits: `URootMotionModifier_Warp`
- L485 _public prototype_ `UDEPRECATED_RootMotionModifier_SimpleWarp(const FObjectInitializer& ObjectInitializer);`
- L486 _public prototype_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override;`

#### class `URootMotionModifier_Scale`  
`class URootMotionModifier_Scale : public URootMotionModifier`  
_L493-519_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Scale"))`
- inherits: `URootMotionModifier`
- L501 _public member_ `FVector Scale = FVector(1.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Vector used to scale each component of the translation
- L503 _public function_ `URootMotionModifier_Scale(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L505 _public function_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override`
- L514 _public prototype_ `UPARAM(DisplayName = "Motion Warping Comp") UMotionWarpingComponent* InMotionWarpingComp, UPARAM(DisplayName = "Animation") const UAnimSequenceBase* InAnimation, UPARAM(DisplayName = "Start Time") float InStartTime, UPARAM(DisplayName = "End Time") float InEndTime, UPARAM(DisplayName = "Scale") FVector InScale = FVector(1`

#### class `URootMotionModifier_Blueprintable`  
`class URootMotionModifier_Blueprintable : public URootMotionModifier`  
_L525-537_
- reflection: `UCLASS(Experimental, MinimalAPI, Blueprintable, meta = (DisplayName = "Blueprintable"))`
- inherits: `URootMotionModifier`
- L531 _public function_ `URootMotionModifier_Blueprintable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L533 _public prototype_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override;`
- L536 _public prototype_ `FTransform BP_ProcessRootMotion(const AActor* Actor, const USkeletalMeshComponent* Mesh, const FTransform& InRootMotion, float DeltaSeconds) const;` — `UFUNCTION(BlueprintPure, BlueprintImplementableEvent, meta=(DisplayName = "Process Root Motion"), Category = "Settings")`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`
- L65 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRootMotionModifierDelegate, UMotionWarpingComponent*, MotionWarpingComp, URootMotionModifier*, RootMotionModifier);`
- L65 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRootMotionModifierDelegate, UMotionWarpingComponent*, MotionWarpingComp, URootMotionModifier*, RootMotionModifier);`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/RootMotionModifier_AdjustmentBlendWarp.h` (Public)


#### struct `FMotionDeltaTrack`  
`struct FMotionDeltaTrack`  
_L15-33_
- reflection: `USTRUCT()`
- L20 _public member_ `TArray<FTransform> BoneTransformTrack;` — `UPROPERTY()`
- L23 _public member_ `TArray<FVector> DeltaTranslationTrack;` — `UPROPERTY()`
- L26 _public member_ `TArray<FRotator> DeltaRotationTrack;` — `UPROPERTY()`
- L29 _public member_ `FVector TotalTranslation = FVector::ZeroVector;` — `UPROPERTY()`
- L32 _public member_ `FRotator TotalRotation = FRotator::ZeroRotator;` — `UPROPERTY()`

#### struct `FMotionDeltaTrackContainer`  
`struct FMotionDeltaTrackContainer`  
_L36-47_
- reflection: `USTRUCT()`
- L41 _public member_ `TArray<FMotionDeltaTrack> Tracks;` — `UPROPERTY()`
- L43 _public function_ `void Init(int32 InNumTracks)`

#### class `URootMotionModifier_AdjustmentBlendWarp`  
`class URootMotionModifier_AdjustmentBlendWarp : public URootMotionModifier_Warp`  
_L51-107_
- reflection: `UCLASS(MinimalAPI, hidedropdown, meta = (DisplayName = "Adjustment Blend Warp"))`
- inherits: `URootMotionModifier_Warp`
- desc: EXPERIMENTAL: Marked with 'hidedropdown' to prevent it from showing up in the UI since it is not ready for production.
- L58 _public member_ `bool bWarpIKBones = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")`
- L61 _public member_ `TArray<FName> IKBones;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")`
- L63 _public prototype_ `URootMotionModifier_AdjustmentBlendWarp(const FObjectInitializer& ObjectInitializer);`
- L65 _public prototype_ `virtual void OnTargetTransformChanged() override;`
- L66 _public prototype_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override;`
- L68 _public prototype_ `void GetIKBoneTransformAndAlpha(FName BoneName, FTransform& OutTransform, float& OutAlpha) const;`
- L71 _public prototype_ `static URootMotionModifier_AdjustmentBlendWarp* AddRootMotionModifierAdjustmentBlendWarp(UMotionWarpingComponent* InMotionWarpingComp, const UAnimSequenceBase* InAnimation, float InStartTime, float InEndTime, FName InWarpTargetName, EWarpPointAnimProvider InWarpPointAnimProvider, FTransform InWarpPointAnimTransform, FName InWarpPointAnimBoneName, bool bInWarpTranslation, bool bInIgnoreZAxis, bool bInWarpRotation, bool bInWarpIKBones, const TArray<FName>& InIKBones);` — `UFUNCTION(BlueprintCallable, Category = "Motion Warping")`
- L76 _public prototype_ `static void GetAdjustmentBlendIKBoneTransformAndAlpha(ACharacter* Character, FName BoneName, FTransform& OutTransform, float& OutAlpha);` — `UFUNCTION(BlueprintPure, Category = "Motion Warping")`
- L81 _protected member_ `FTransform CachedMeshTransform;` — `UPROPERTY()`
- L84 _protected member_ `FTransform CachedMeshRelativeTransform;` — `UPROPERTY()`
- L87 _protected member_ `FTransform CachedRootMotion;` — `UPROPERTY()`
- L90 _protected member_ `FAnimSequenceTrackContainer Result;` — `UPROPERTY()`
- L92 _protected prototype_ `void PrecomputeWarpedTracks();`
- L94 _protected prototype_ `FTransform ExtractWarpedRootMotion() const;`
- L96 _protected prototype_ `void ExtractBoneTransformAtTime(FTransform& OutTransform, const FName& BoneName, float Time) const;`
- L97 _protected prototype_ `void ExtractBoneTransformAtTime(FTransform& OutTransform, int32 TrackIndex, float Time) const;`
- L98 _protected prototype_ `void ExtractBoneTransformAtFrame(FTransform& OutTransform, int32 TrackIndex, int32 Frame) const;`
- L101 _protected prototype_ `void DrawDebugWarpedTracks(float DrawDuration) const;`
- L104 _protected prototype_ `static void ExtractMotionDeltaFromRange(const FBoneContainer& BoneContainer, const UAnimSequenceBase* Animation, float StartTime, float EndTime, float SampleRate, FMotionDeltaTrackContainer& OutMotionDeltaTracks);`
- L106 _protected prototype_ `static void AdjustmentBlendWarp(const FBoneContainer& BoneContainer, const FCSPose<FCompactPose>& AdditivePose, const FMotionDeltaTrackContainer& MotionDeltaTracks, FAnimSequenceTrackContainer& Output);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTIONWARPING_API`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/RootMotionModifier_PrecomputedWarp.h` (Public)


#### enum `EPrecomputedWarpWeightCurveType`  
`enum class EPrecomputedWarpWeightCurveType`  
_L10-20_
- reflection: `UENUM(Experimental)`
- L12 _public enumerator_ `FromRootMotionTranslation`
- L13 _public enumerator_ `FromRootMotionRotation`
- L14 _public enumerator_ `Linear`
- L15 _public enumerator_ `EaseIn`
- L16 _public enumerator_ `EaseOut`
- L17 _public enumerator_ `EaseInOut`
- L18 _public enumerator_ `Instant`
- L19 _public enumerator_ `DoNotWarp`

#### struct `FPrecomputedWarpCurve`  
`struct FPrecomputedWarpCurve`  
_L23-38_
- reflection: `USTRUCT(Experimental)`
- L29 _public member_ `EPrecomputedWarpWeightCurveType CurveType = EPrecomputedWarpWeightCurveType::FromRootMotionTranslation;` — `UPROPERTY(EditAnywhere, Category = Properties)` — Type of curve to interpolate using
- L33 _public member_ `float StartRatio = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Properties", meta = (UIMin = "0.0", UIMax = "1.0", SliderExponent = "1.0"))` — Time to start warping, as a ratio of the duration of the Notify
- L37 _public member_ `float EndRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Properties", meta = (UIMin = "0.0", UIMax = "1.0", SliderExponent = "1.0"))` — Time to complete warping, as a ratio of the duration of the Notify

#### struct `FPrecomputedWarpSteeringSettings`  
`struct FPrecomputedWarpSteeringSettings`  
_L41-60_
- reflection: `USTRUCT(Experimental)`
- L47 _public member_ `bool bEnableSmoothing = true;` — `UPROPERTY(EditAnywhere, Category=Properties)` — Enable smoothing of the steering target orientation, to avoid instant orientation changes
- L51 _public member_ `float SmoothStiffness = 300.f;` — `UPROPERTY(EditAnywhere, Category=Propeties, meta = (EditCondition=bEnableSmoothing))` — Sprint stiffness for smoothing
- L55 _public member_ `float SmoothDamping = 1.f;` — `UPROPERTY(EditAnywhere, Category=Properties, meta = (EditCondition=bEnableSmoothing))` — Spring damping factor for smoothing
- L59 _public member_ `float AngleThreshold = 135.f;` — `UPROPERTY(EditAnywhere, Category = Properties)` — When the warped movement direction differs from the animated movement direction by more than this threshold, steering will be disabled.

#### enum `EPrecomputedWarpUpdateMode`  
`enum class EPrecomputedWarpUpdateMode`  
_L63-69_
- reflection: `UENUM(Experimental)`
- L66 _public enumerator_ `World` — each frame, apply root motion to get to the expected part of the alignment path in wold space
- L68 _public enumerator_ `Relative` — each frame, apply the root motion from the alignment path relative to the previous frame

#### class `URootMotionModifier_PrecomputedWarp`  
`class URootMotionModifier_PrecomputedWarp : public URootMotionModifier_Warp`  
_L72-159_
- reflection: `UCLASS(Experimental, Blueprintable, MinimalAPI, meta = (DisplayName = "Precomputed Warp", Tooltip="(Experimental) Precomputed warp computes the full path to alignment on the first frame of execution and then on following frames just applies that root motion. Only Suitable for stationary targets."))`
- inherits: `URootMotionModifier_Warp`
- L85 _public prototype_ `URootMotionModifier_PrecomputedWarp(const FObjectInitializer& ObjectInitializer);`
- L87 _public prototype_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override;`
- L89 _public prototype_ `virtual TSharedPtr<FRootMotionModifierSwapState> GetSwapState() const override;`
- L90 _public prototype_ `virtual void PopulateSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState) const override;`
- L91 _public prototype_ `virtual void RestoreFromSwapState(TSharedPtr<FRootMotionModifierSwapState> InSwapState) override;`
- L94 _public member_ `FPrecomputedWarpCurve TranslationWarpingCurve;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="!bSeparateTranslationCurves"))`
- L98 _public member_ `bool bSeparateTranslationCurves = false;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L102 _public member_ `FPrecomputedWarpCurve TranslationWarpingCurve_InMovementDirection;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="bSeparateTranslationCurves"))` — curve for warping translation in direction of movement
- L104 _public member_ `FPrecomputedWarpCurve TranslationWarpingCurve_OutOfMovementDirection;` — `UPROPERTY(EditAnywhere, Category = Blending, Meta = (EditCondition="bSeparateTranslationCurves"))`
- L107 _public member_ `FPrecomputedWarpCurve RotationWarpingCurve;` — `UPROPERTY(EditAnywhere, Category = Blending)`
- L111 _public member_ `FTransform AlignOffset;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Offset from Root (or AlignBone) to Align to the target transform
- L115 _public member_ `bool bForceTargetTransformUpright = false;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — only allow Yaw in the target transform (remove other rotations before warping)
- L121 _public function_ `void SetAlignOffset(FTransform NewTransform)` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "TechAnimUtils")` — For automating setting the AlignOffset at the end of the NotifyState
- L128 _public member_ `EPrecomputedWarpUpdateMode UpdateMode;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)`
- L132 _public member_ `FName Disable;` — `UPROPERTY(EditAnywhere, Category = TargetTransform)` — Bool variable which will disable this notify
- L136 _public member_ `bool bEnableSteering = false;` — `UPROPERTY(EditAnywhere, Category = Steering)` — Steering will rotate the character based on the difference between the animated movement direction and the warped movement direction, to keep the character facing their direction of movement
- L139 _public member_ `FPrecomputedWarpSteeringSettings SteeringSettings;` — `UPROPERTY(EditAnywhere, Category = Steering, meta=(EditCondition=bEnableSteering))`
- L143 _public prototype_ `float GetWeight(float CurrentTime, const FPrecomputedWarpCurve& WarpCurve) const;`
- L145 _public member_ `bool bFirstFrame = true;`
- L146 _public member_ `float ActualStartTime = 0.f;`
- L147 _public member_ `float RoundedEndTime = 0.f;`
- L148 _public member_ `float PreviousFrame = 0.f;`
- L150 _public member_ `FTransform StartingRootTransform;`
- L151 _public member_ `FTransform TargetTransform;`
- L153 _public member_ `FQuat FilteredSteeringTarget = FQuat::Identity;`
- L154 _public member_ `FQuaternionSpringState TargetSmoothingState;`
- L156 _public member_ `TArray<FTransform> WarpedTrajectory;`
- L158 _public member_ `FAnimTrajectoryData AnimTrajectoryData;`

#### struct `URootMotionModifier_PrecomputedWarp::FAnimTrajectoryData`  
`struct FAnimTrajectoryData`  
_L77-83_
- L79 _public member_ `FTransform TargetTransform;`
- L80 _public member_ `TArray<FTransform> Trajectory;`
- L81 _public member_ `TArray<float> TranslationCurve;`
- L82 _public member_ `TArray<float> RotationCurve;`

#### struct `FRootMotionModifier_PrecomputedWarpSwapState`  
`struct FRootMotionModifier_PrecomputedWarpSwapState : public FRootMotionModifier_WarpSwapState`  
_L161-177_
- inherits: `FRootMotionModifier_WarpSwapState`
- L163 _public member_ `bool bFirstFrame = true;`
- L164 _public member_ `float ActualStartTime = 0.f;`
- L165 _public member_ `float RoundedEndTime = 0.f;`
- L166 _public member_ `float PreviousFrame = 0.f;`
- L168 _public member_ `FTransform StartingRootTransform;`
- L169 _public member_ `FTransform TargetTransform;`
- L171 _public member_ `FQuat FilteredSteeringTarget = FQuat::Identity;`
- L172 _public member_ `FQuaternionSpringState TargetSmoothingState;`
- L174 _public member_ `TArray<FTransform> WarpedTrajectory;`
- L176 _public member_ `URootMotionModifier_PrecomputedWarp::FAnimTrajectoryData AnimTrajectoryData;`

### `Plugins/Animation/MotionWarping/Source/MotionWarping/Public/RootMotionModifier_SkewWarp.h` (Public)


#### class `URootMotionModifier_SkewWarp`  
`class URootMotionModifier_SkewWarp : public URootMotionModifier_Warp`  
_L11-56_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Skew Warp"))`
- inherits: `URootMotionModifier_Warp`
- L17 _public prototype_ `URootMotionModifier_SkewWarp(const FObjectInitializer& ObjectInitializer);`
- L19 _public prototype_ `virtual FTransform ProcessRootMotion(const FTransform& InRootMotion, float DeltaSeconds) override;`
- L21 _public prototype_ `static FVector WarpTranslation(const FTransform& CurrentTransform, const FVector& DeltaTranslation, const FVector& TotalTranslation, const FVector& TargetLocation);`
- L24 _public prototype_ `virtual void DrawInEditor(FPrimitiveDrawInterface* PDI, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;`
- L25 _public prototype_ `virtual void DrawCanvasInEditor(FCanvas& Canvas, FSceneView& View, USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* Animation, const FAnimNotifyEvent& NotifyEvent) const override;`
- L26 _public prototype_ `FTransform GetDebugWarpPointTransform(USkeletalMeshComponent* MeshComp, const UAnimSequenceBase* InAnimation, const UMirrorDataTable* MirrorTable, const float NotifyEndTime) const;`
- L31 _public prototype_ `UPARAM(DisplayName = "Motion Warping Comp") UMotionWarpingComponent* InMotionWarpingComp, UPARAM(DisplayName = "Animation") const UAnimSequenceBase* InAnimation, UPARAM(DisplayName = "Start Time") float InStartTime, UPARAM(DisplayName = "End Time") float InEndTime, UPARAM(DisplayName = "Warp Target Name") FName InWarpTargetName, UPARAM(DisplayName = "Warp Point Anim Provider") EWarpPointAnimProvider InWarpPointAnimProvider, UPARAM(DisplayName = "Warp Point Anim Transform") FTransform InWarpPointAnimTransform, UPARAM(DisplayName = "Warp Point Anim Bone Name") FName InWarpPointAnimBoneName, UPARAM(DisplayName = "Warp Translation") bool bInWarpTranslation = true, UPARAM(DisplayName = "Ignore Z Axis") bool bInIgnoreZAxis = true, UPARAM(DisplayName = "Warp Rotation") bool bInWarpRotation = true, UPARAM(DisplayName = "Rotation Type") EMotionWarpRotationType InRotationType = EMotionWarpRotationType::Default, UPARAM(DisplayName = "Rotation Method") EMotionWarpRotationMethod InRotationMethod = EMotionWarpRotationMethod::Slerp, UPARAM(DisplayName = "Warp Rotation Time Multiplier") float InWarpRotationTimeMultiplier = 1.f, UPARAM(DisplayName = "Warp Max Rotation Rate") float InWarpM`
- L55 _protected member_ `float MaxSpeedClampRatio = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Allows to set maximum warp translation speed clamp ratio. Ratio is relative to the original animation translation speed. E.g. if the MaxSpeedClampRatio == 2.0f actor well be moving with maximum 2x speed of the animation. Applied only in cases when animation has root motion translation. Zero treated as no clamping.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOTIONWARPING_API`
