# Plugins / ContextualAnimation

- module root: `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation`
- headers: 10; symbols: 669
- symbol kinds: class=16, delegate=4, enum=12, enumerator=32, function=116, macro=7, member=205, namespace=2, prototype=240, struct=33, typedef=2
- PrivateDependencyModuleNames: Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags, IKRig, MotionWarping, NetCore

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/AnimNotifyState_EarlyOutContextualAnimWindow.h` (Public)


#### class `UAnimNotifyState_EarlyOutContextualAnimWindow`  
`class UAnimNotifyState_EarlyOutContextualAnimWindow : public UAnimNotifyState`  
_L12-26_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "Early Out Contextual Anim"))`
- inherits: `UAnimNotifyState`
- desc: Notify used to allow player to early out from a contextual anim. Usually used at the end of the animations to improve responsivess
- L20 _public member_ `bool bStopEveryone = false;` — `UPROPERTY(EditAnywhere, Category = Config)` — Whether to force all the actors in the interaction to exit the interaction or only us
- L22 _public prototype_ `UAnimNotifyState_EarlyOutContextualAnimWindow(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;`
- L25 _public prototype_ `virtual FString GetNotifyName_Implementation() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CONTEXTUALANIMATION_API`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/AnimNotifyState_IKWindow.h` (Public)


#### class `UAnimNotifyState_IKWindow`  
`class UAnimNotifyState_IKWindow : public UAnimNotifyState`  
_L13-38_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "IK Window"))`
- inherits: `UAnimNotifyState`
- desc: AnimNotifyState used to define areas in an animation where IK should be enable
- L19 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L22 _public member_ `FName GoalName;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L25 _public member_ `FAlphaBlend BlendIn;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L28 _public member_ `FAlphaBlend BlendOut;` — `UPROPERTY(EditAnywhere, Category = Config)`
- L31 _public member_ `bool bEnable = true;` — `UPROPERTY()`
- L33 _public prototype_ `UAnimNotifyState_IKWindow(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `virtual FString GetNotifyName_Implementation() const override;`
- L37 _public prototype_ `static float GetIKAlphaValue(const FName& GoalName, const struct FAnimMontageInstance* MontageInstance);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CONTEXTUALANIMATION_API`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimActorInterface.h` (Public)


#### class `UContextualAnimActorInterface`  
`class UContextualAnimActorInterface : public UInterface`  
_L9-12_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IContextualAnimActorInterface`  
`class IContextualAnimActorInterface : public IInterface`  
_L14-24_
- inherits: `IInterface`
- L19 _private prototype_ `class USkeletalMeshComponent* GetMesh() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Contextual Animation System")`
- L23 _private prototype_ `void RefreshEditorPreview();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Contextual Animation System")` — Called from CAS Editor on the preview actor after spawn. Useful to give that actor a chance to run game-specific logic needed to be usable as preview actor in the CAS Editor

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimOverrideInterface.h` (Public)


#### struct `FContextualAnimationOverrideData`  
`struct FContextualAnimationOverrideData`  
_L16-44_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public function_ `FContextualAnimationOverrideData()`
- L25 _public function_ `FContextualAnimationOverrideData(const FContextualAnimTrack& InAnimTrack)`
- L32 _public member_ `TObjectPtr<UAnimSequenceBase> AnimSequence = nullptr;` — `UPROPERTY(EditAnywhere, Category = Overrides)`
- L35 _public member_ `FTransform MeshToScene = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Overrides)`
- L39 _public member_ `FContextualAnimAlignmentTrackContainer AlignmentData;` — `UPROPERTY()` — Container for alignment tracks
- L43 _public member_ `FContextualAnimAlignmentTrackContainer IKTargetData;` — `UPROPERTY()` — Container for auto generate IK Target Tracks

#### class `UContextualAnimOverrideInterface`  
`class UContextualAnimOverrideInterface : public UInterface`  
_L47-50_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`

#### class `IContextualAnimOverrideInterface`  
`class IContextualAnimOverrideInterface : public IInterface`  
_L52-72_
- inherits: `IInterface`
- L57 _public prototype_ `virtual bool GetCASAnimationDataOverride(const FContextualAnimSceneBinding& InBinding, const FContextualAnimSceneBindings& InBindings, const FContextualAnimTrack& InAnimTrack, FContextualAnimationOverrideData& OutData) = 0;`
- L64 _public function_ `virtual bool GetCASAnimActorPreviewDataOverrideForRole(const FName& InRole, FContextualAnimActorPreviewData& OutPreviewData)` — Called during SpawnPreviewActor to allow the provider to override the preview data for a given role. Return true and populate OutPreviewData to replace whatever is set in the scene asset's OverridePreviewData.
- L69 _public function_ `virtual void OnCASPreviewActorSpawned(const FName& InRole, AActor* InSpawnedActor)` — Called after a preview actor has been spawned, allowing post-spawn setup (e.g. applying cosmetics).

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimSceneActorComponent.h` (Public)


#### struct `FContextualAnimWarpTarget`  
`struct FContextualAnimWarpTarget`  
_L25-49_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public prototype_ `FContextualAnimWarpTarget() = default;`
- L30 _public function_ `FContextualAnimWarpTarget(const FName InRole, const FName InWarpTargetName, const FTransform& InTargetTransform) : Role(InRole) , TargetName(InWarpTargetName) , TargetLocation(InTargetTransform.GetLocation()) , TargetRotation(InTargetTransform.GetRotation())`
- L39 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L42 _public member_ `FName TargetName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L45 _public member_ `FVector TargetLocation = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L48 _public member_ `FQuat TargetRotation = FQuat::Identity;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FContextualAnimRepData`  
`struct FContextualAnimRepData`  
_L53-63_
- reflection: `USTRUCT()`
- desc: Base struct for replicated data with a rep counter
- L59 _public member_ `uint8 RepCounter = 0;` — `UPROPERTY()` — Auto increment counter to ensure replication even if the data is the same
- L61 _public prototype_ `void IncrementRepCounter();`
- L62 _public function_ `bool IsValid() const`

#### struct `FContextualAnimRepBindingsData`  
`struct FContextualAnimRepBindingsData : public FContextualAnimRepData`  
_L67-91_
- reflection: `USTRUCT()`
- inherits: `FContextualAnimRepData`
- desc: Used to replicate start/stop contextual anim events
- L72 _public member_ `FContextualAnimSceneBindings Bindings;` — `UPROPERTY()`
- L75 _public member_ `TArray<FContextualAnimWarpPoint> WarpPoints;` — `UPROPERTY()`
- L78 _public member_ `TArray<FContextualAnimWarpTarget> ExternalWarpTargets;` — `UPROPERTY()`
- L81 _public member_ `float StartTime = 0.f;` — `UPROPERTY()`
- L83 _public function_ `void Reset()`

#### struct `FContextualAnimRepLateJoinData`  
`struct FContextualAnimRepLateJoinData : public FContextualAnimRepData`  
_L95-121_
- reflection: `USTRUCT()`
- inherits: `FContextualAnimRepData`
- desc: Used to replicate a late join event
- L101 _public member_ `TWeakObjectPtr<AActor> Actor = nullptr;` — `UPROPERTY()` — Actor that is joining the interaction
- L105 _public member_ `FName Role = NAME_None;` — `UPROPERTY()` — Role in the interaction the actor is gonna play
- L108 _public member_ `TArray<FContextualAnimWarpPoint> WarpPoints;` — `UPROPERTY()`
- L111 _public member_ `TArray<FContextualAnimWarpTarget> ExternalWarpTargets;` — `UPROPERTY()`
- L113 _public function_ `void Reset()`

#### struct `FContextualAnimRepTransitionData`  
`struct FContextualAnimRepTransitionData : public FContextualAnimRepData`  
_L125-157_
- reflection: `USTRUCT()`
- inherits: `FContextualAnimRepData`
- desc: Used to transition events
- L130 _public member_ `uint8 Id = 0;` — `UPROPERTY()`
- L133 _public member_ `uint8 SectionIdx = 0;` — `UPROPERTY()`
- L136 _public member_ `uint8 AnimSetIdx = 0;` — `UPROPERTY()`
- L139 _public member_ `bool bStopEveryone = false;` — `UPROPERTY()`
- L142 _public member_ `TArray<FContextualAnimWarpPoint> WarpPoints;` — `UPROPERTY()`
- L145 _public member_ `TArray<FContextualAnimWarpTarget> ExternalWarpTargets;` — `UPROPERTY()`
- L147 _public function_ `void Reset()`

#### class `UContextualAnimSceneActorComponent`  
`class UContextualAnimSceneActorComponent : public UActorComponent, public IIKGoalCreatorInterface`  
_L160-396_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IIKGoalCreatorInterface`
- L168 _public member_ `FContextualAnimSceneActorCompDelegate OnJoinedSceneDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Events")` — Event that happens when the actor owner of this component joins an scene
- L172 _public member_ `FContextualAnimSceneActorCompDelegate OnLeftSceneDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Events")` — Event that happens when the actor owner of this component leave an scene
- L175 _public member_ `FContextualAnimPlayMontageNotifyBeginDelegate OnPlayMontageNotifyBeginDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L178 _public member_ `FContextualAnimOnMontageBlendingOutDelegate OnMontageBlendingOutDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Events")`
- L182 _public member_ `FContextualAnimOnMontageReachedEndDelegate OnMontageReachedEndDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Events")` — Delegate called when the currently playing montage reaches the end but does not blends out
- L185 _public member_ `TObjectPtr<class UContextualAnimSceneAsset> SceneAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")`
- L189 _public member_ `FTransform AlignmentOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")` — Optional offset from the actor transform. Can be used to modify the final world space transform used for alignment.
- L191 _public prototype_ `UContextualAnimSceneActorComponent(const FObjectInitializer& ObjectInitializer);`
- L193 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L194 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;`
- L195 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L197 _public prototype_ `virtual void AddIKGoals_Implementation(TMap<FName, FIKRigGoal>& OutGoals) override;`
- L200 _public function_ `const FContextualAnimSceneBindings& GetBindings() const` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Actor Component")`
- L203 _public prototype_ `bool IsInActiveScene() const;` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Actor Component")`
- L207 _public prototype_ `void OnJoinedScene(const FContextualAnimSceneBindings& InBindings);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")` — Called when the actor owner of this component joins an scene
- L211 _public prototype_ `void OnLeftScene();` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")` — Called from the scene instance when the actor owner of this component leave an scene
- L214 _public function_ `const TArray<FContextualAnimIKTarget>& GetIKTargets() const` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Actor Component")`
- L217 _public prototype_ `const FContextualAnimIKTarget& GetIKTargetByGoalName(FName GoalName) const;` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Actor Component")`
- L220 _public prototype_ `bool StartContextualAnimScene(const FContextualAnimSceneBindings& InBindings);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L223 _public prototype_ `bool LateJoinContextualAnimScene(AActor* Actor, FName Role);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L226 _public prototype_ `bool TransitionContextualAnimScene(FName SectionName);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L229 _public prototype_ `bool TransitionContextualAnimSceneToSpecificSet(FName SectionName, int32 AnimSetIdx);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L232 _public prototype_ `bool TransitionSingleActor(int32 SectionIdx, int32 AnimSetIdx);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L234 _public prototype_ `bool StartContextualAnimScene(const FContextualAnimSceneBindings& InBindings, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L235 _public prototype_ `bool LateJoinContextualAnimScene(AActor* Actor, FName Role, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L236 _public prototype_ `bool TransitionContextualAnimScene(FName SectionName, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L237 _public prototype_ `bool TransitionContextualAnimScene(FName SectionName, int32 AnimSetIdx, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L238 _public prototype_ `bool TransitionSingleActor(int32 SectionIdx, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L239 _public prototype_ `bool TransitionSingleActor(int32 SectionIdx, int32 AnimSetIdx, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L242 _public prototype_ `void EarlyOutContextualAnimScene(bool bStopEveryone = false);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Actor Component")`
- L244 _public prototype_ `bool IsOwnerLocallyControlled() const;`
- L247 _public prototype_ `void OnIgnoredActorEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L253 _protected member_ `TWeakObjectPtr<UAnimInstance> OwnerAnimInstance = nullptr;` — `UPROPERTY(Transient)` — Cache of the owner's AnimInstance for easy access. Only valid while an interaction is active
- L260 _protected member_ `FContextualAnimRepBindingsData RepBindings;` — `UPROPERTY(Transient, ReplicatedUsing = OnRep_Bindings)` — Replicated copy of the bindings so we can start the action on simulated proxies This gets replicated only from the initiator of the action and then set on all the other members of the interaction
- L263 _protected member_ `FContextualAnimRepLateJoinData RepLateJoinData;` — `UPROPERTY(Transient, ReplicatedUsing = OnRep_LateJoinData)`
- L266 _protected member_ `FContextualAnimRepTransitionData RepTransitionData;` — `UPROPERTY(Transient, ReplicatedUsing = OnRep_TransitionData)`
- L269 _protected member_ `FContextualAnimRepTransitionData RepTransitionSingleActorData;` — `UPROPERTY(Transient, ReplicatedUsing = OnRep_RepTransitionSingleActor)`
- L276 _protected member_ `FContextualAnimSceneBindings Bindings;` — `UPROPERTY(Transient)` — Bindings for the interaction we are currently playing. Used to update IK, keep montage in sync, disable/enable collision between actors etc
- L280 _protected member_ `TArray<FContextualAnimIKTarget> IKTargets;` — `UPROPERTY(Transient)` — List of IKTarget for this frame
- L287 _protected member_ `TArray<FName> WarpTargetNamesCache;` — `UPROPERTY(Transient)` — Motion warping doesn't remove warp targets when a warping window ends, so we keep track of the warp targets added during the interaction and remove them at the end of it to prevent issues caused by dangling warp targets after an interaction.
- L307 _protected member_ `FCharacterProperties CharacterPropertiesBackup;`
- L309 _protected prototype_ `void UpdateIKTargets();`
- L316 _protected prototype_ `virtual void OnTickPose(class USkinnedMeshComponent* SkinnedMeshComponent, float DeltaTime, bool bNeedsValidRootMotion);` — `UFUNCTION()` — Event called right before owner's mesh ticks the pose when we are in a scene instance and IK Targets are required. Used to update IK Targets before animation need them
- L319 _protected prototype_ `virtual void OnRep_Bindings();` — `UFUNCTION()`
- L322 _protected prototype_ `void OnRep_LateJoinData();` — `UFUNCTION()`
- L325 _protected prototype_ `void OnRep_RepTransitionSingleActor();` — `UFUNCTION()`
- L328 _protected prototype_ `void OnRep_TransitionData();` — `UFUNCTION()`
- L330 _protected prototype_ `void SetIgnoreCollisionWithActor(AActor& Actor, bool bValue) const;`
- L331 _protected prototype_ `void SetIgnoreCollisionWithOtherActors(bool bValue) const;`
- L333 _protected prototype_ `virtual void SetCollisionState(const FContextualAnimSceneBinding& Binding);`
- L334 _protected prototype_ `virtual void RestoreCollisionState(const FContextualAnimSceneBinding& Binding);`
- L336 _protected prototype_ `void SetMovementState(const FContextualAnimSceneBinding& Binding, const FContextualAnimTrack& AnimTrack);`
- L337 _protected prototype_ `void RestoreMovementState(const FContextualAnimSceneBinding& Binding);`
- L340 _protected prototype_ `void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L343 _protected prototype_ `void OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);` — `UFUNCTION()`
- L348 _protected prototype_ `void JoinScene(const FContextualAnimSceneBindings& InBindings, const TArray<FContextualAnimWarpPoint> WarpPoints, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets, float StartTime = 0.f);`
- L350 _protected prototype_ `virtual void OnJoinScene(const FContextualAnimSceneBinding& Binding);`
- L352 _protected prototype_ `void LeaveScene();`
- L354 _protected prototype_ `virtual bool CanLeaveScene(const FContextualAnimSceneBinding& Binding);`
- L357 _protected prototype_ `virtual void OnPreLeaveScene(const FContextualAnimSceneBinding& Binding);` — Called just before the scene leaving happens (which calls OnLeaveScene)
- L359 _protected prototype_ `virtual void OnLeaveScene(const FContextualAnimSceneBinding& Binding);`
- L361 _protected prototype_ `void LateJoinScene(const FContextualAnimSceneBindings& InBindings, int32 SectionIdx, int32 AnimSetIdx, const TArray<FContextualAnimWarpPoint>& WarpPoints, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L363 _protected prototype_ `virtual void OnLateJoinScene(const FContextualAnimSceneBinding& Binding, int32 SectionIdx, int32 AnimSetIdx);`
- L366 _protected prototype_ `void ServerStartContextualAnimScene(const FContextualAnimSceneBindings& InBindings);` — `UFUNCTION(Server, Reliable, WithValidation)`
- L369 _protected prototype_ `void ServerEarlyOutContextualAnimScene(bool bStopEveryone);` — `UFUNCTION(Server, Reliable, WithValidation)`
- L371 _protected prototype_ `virtual void PlayAnimation_Internal(UAnimSequenceBase* Animation, float StartTime, bool bSyncPlaybackTime);`
- L373 _protected prototype_ `virtual void AddOrUpdateWarpTargets(int32 SectionIdx, int32 AnimSetIdx, const TArray<FContextualAnimWarpPoint>& WarpPoints, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L375 _protected prototype_ `void HandleTransitionSelf(int32 NewSectionIdx, int32 NewAnimSetIdx, const TArray<FContextualAnimWarpPoint>& WarpPoints, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L377 _protected prototype_ `void HandleTransitionEveryone(int32 NewSectionIdx, int32 NewAnimSetIdx, const TArray<FContextualAnimWarpPoint>& WarpPoints, const TArray<FContextualAnimWarpTarget>& ExternalWarpTargets);`
- L379 _protected prototype_ `virtual void OnTransitionScene(const FContextualAnimSceneBinding& Binding, int32 SectionIdx, int32 AnimSetIdx);`
- L381 _protected prototype_ `virtual void OnTransitionSingleActor(const FContextualAnimSceneBinding& Binding, int32 SectionIdx, int32 AnimSetIdx);`
- L383 _protected prototype_ `virtual void OtherActorLeftScene(AActor& Actor);`
- L390 _protected prototype_ `float FindIdealStartTime(const FContextualAnimSceneBindings& InBindings, const FContextualAnimSceneBinding& Binding, const TArray<FContextualAnimWarpPoint>& WarpPoints) const;` — Finds ideal start time for the interaction based on the distance from the actor to the warp target in the animation and the actual distance in game. Effectively skipping the portion of the 'approach-motion' the actor doesn't need. Returns 0 if the actor is far enough to play the full animation from the beginning.
- L394 _private member_ `TArray<TWeakObjectPtr<const UAnimMontage>, TInlineAllocator<5>> AnimsPlayed;`
- L395 _private member_ `int32 LoopCounter = 0;`

#### struct `UContextualAnimSceneActorComponent::FCharacterRotationProperties`  
`struct FCharacterRotationProperties`  
_L289-294_
- L291 _public member_ `bool bAllowPhysicsRotationDuringAnimRootMotion = false;`
- L292 _public member_ `bool bUseControllerDesiredRotation = false;`
- L293 _public member_ `bool bOrientRotationToMovement = false;`

#### struct `UContextualAnimSceneActorComponent::FCharacterProperties`  
`struct FCharacterProperties`  
_L296-306_
- L298 _public member_ `bool bIgnoreClientMovementErrorChecksAndCorrection = false;`
- L299 _public member_ `bool bReplicatingMovement = false;`
- L300 _public member_ `bool bSimulatePhysics = false;`
- L301 _public member_ `TOptional<FCharacterRotationProperties> RotationProperties;`
- L302 _public member_ `TOptional<EMovementMode> MovementMode;`
- L303 _public member_ `uint8 CustomMovementMode = 0;`
- L304 _public member_ `TArray<TTuple<ECollisionChannel, ECollisionResponse>> CollisionResponses;`
- L305 _public member_ `TOptional<struct FCollisionResponseContainer> CollisionProfileResponses;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTEXTUALANIMATION_API`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContextualAnimSceneActorCompDelegate, class UContextualAnimSceneActorComponent*, SceneActorComponent);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContextualAnimSceneActorCompDelegate, class UContextualAnimSceneActorComponent*, SceneActorComponent);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FContextualAnimPlayMontageNotifyBeginDelegate, class UContextualAnimSceneActorComponent*, SceneActorComponent, FName, NotifyName);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FContextualAnimPlayMontageNotifyBeginDelegate, class UContextualAnimSceneActorComponent*, SceneActorComponent, FName, NotifyName);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FContextualAnimOnMontageBlendingOutDelegate, class UContextualAnimSceneActorComponent*, SceneComponent, UAnimMontage* const, BlendingOutMontage, bool, bInterrupted);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FContextualAnimOnMontageBlendingOutDelegate, class UContextualAnimSceneActorComponent*, SceneComponent, UAnimMontage* const, BlendingOutMontage, bool, bInterrupted);`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FContextualAnimOnMontageReachedEndDelegate, class UContextualAnimSceneActorComponent*, SceneComponent, UAnimMontage* const, Montage, int32, LoopCounter);`
- L22 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FContextualAnimOnMontageReachedEndDelegate, class UContextualAnimSceneActorComponent*, SceneComponent, UAnimMontage* const, Montage, int32, LoopCounter);`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimSceneAsset.h` (Public)


#### enum `EContextualAnimCollisionBehavior`  
`enum class EContextualAnimCollisionBehavior : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `None`
- L20 _public enumerator_ `IgnoreActorWhenMoving`
- L21 _public enumerator_ `IgnoreChannels`
- L22 _public enumerator_ `CollisionProfile`

#### struct `FContextualAnimIgnoreChannelsParam`  
`struct FContextualAnimIgnoreChannelsParam`  
_L26-35_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L34 _public member_ `TArray<TEnumAsByte<ECollisionChannel>> Channels;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`

#### struct `FContextualAnimCollisionProfileParam`  
`struct FContextualAnimCollisionProfileParam`  
_L38-47_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L46 _public member_ `FCollisionProfileName Profile;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`

#### struct `FContextualAnimCollisionBehaviorParams`  
`struct FContextualAnimCollisionBehaviorParams`  
_L50-90_
- reflection: `USTRUCT(BlueprintType)`
- L55 _public member_ `EContextualAnimCollisionBehavior CollisionBehavior = EContextualAnimCollisionBehavior::None;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L58 _public member_ `TArray<FContextualAnimIgnoreChannelsParam> CollisionChannelsToIgnoreParams;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "CollisionBehavior==EContextualAnimCollisionBehavior::IgnoreChannels", EditConditionHides))`
- L61 _public member_ `TArray<FContextualAnimCollisionProfileParam> CollisionProfileParams;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "CollisionBehavior==EContextualAnimCollisionBehavior::CollisionProfile", EditConditionHides))`
- L63 _public function_ `const TArray<TEnumAsByte<ECollisionChannel>>& GetCollisionChannelsToIgnoreForRole(FName Role) const`
- L77 _public function_ `FCollisionProfileName GetCollisionProfileNameForRole(FName Role) const`

#### struct `FContextualAnimAttachmentParams`  
`struct FContextualAnimAttachmentParams`  
_L93-105_
- reflection: `USTRUCT()`
- L98 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L101 _public member_ `FName SocketName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`
- L104 _public member_ `FTransform RelativeTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`

#### class `UContextualAnimRolesAsset`  
`class UContextualAnimRolesAsset : public UDataAsset`  
_L108-125_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UDataAsset`
- L115 _public member_ `TArray<FContextualAnimRoleDefinition> Roles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L117 _public function_ `UContextualAnimRolesAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L119 _public function_ `const FContextualAnimRoleDefinition* FindRoleDefinitionByName(const FName& Name) const`
- L124 _public function_ `inline int32 GetNumRoles() const`

#### struct `FContextualAnimSet`  
`struct FContextualAnimSet`  
_L133-154_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains AnimTracks for each role in the interaction. Example: An specific set for a interaction with a car would have two tracks, one with the animation for the character and another one with the animation for the car. It is common to have variations of the same action with different animations. We could have one AnimSet with the animations for getting into the car from the driver side and another for getting into the car from the passenger side.
- L139 _public member_ `TArray<FContextualAnimTrack> Tracks;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — List of tracks with animation (and relevant data specific to that animation) for each role
- L143 _public member_ `TMap<FName, FTransform> WarpPoints;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Map of WarpTargetNames and Transforms for this set. Generated off line based on warp points defined in the asset
- L147 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Optional name to identify this set
- L151 _public member_ `float RandomWeight = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Used by the selection mechanism to 'break the tie' when multiple Sets can be selected
- L153 _public prototype_ `int32 GetNumMandatoryRoles() const;`

#### struct `FContextualAnimSceneSection`  
`struct FContextualAnimSceneSection`  
_L158-198_
- reflection: `USTRUCT(BlueprintType)`
- desc: Named container with one or more ContextualAnimSet
- L164 _public prototype_ `const FContextualAnimSet* GetAnimSet(int32 AnimSetIdx) const;`
- L166 _public prototype_ `const FContextualAnimTrack* GetAnimTrack(int32 AnimSetIdx, const FName& Role) const;`
- L168 _public prototype_ `const FContextualAnimTrack* GetAnimTrack(int32 AnimSetIdx, int32 AnimTrackIdx) const;`
- L170 _public prototype_ `FTransform GetIKTargetTransformForRoleAtTime(int32 AnimSetIdx, FName Role, FName TrackName, float Time) const;`
- L172 _public prototype_ `const FContextualAnimTrack* FindFirstAnimTrackForRoleThatPassesSelectionCriteria(const FName& Role, const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const;`
- L174 _public function_ `inline FName GetName() const`
- L175 _public function_ `inline const TArray<FContextualAnimWarpPointDefinition>& GetWarpPointDefinitions() const`
- L176 _public function_ `inline int32 GetNumAnimSets() const`
- L177 _public function_ `inline bool ShouldSyncAnimations() const`
- L182 _protected member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`
- L185 _protected member_ `TArray<FContextualAnimSet> AnimSets;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`
- L188 _protected member_ `TArray<FContextualAnimWarpPointDefinition> WarpPointDefinitions;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (TitleProperty = "WarpTargetName"))`
- L191 _protected member_ `bool bSyncAnimations = true;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`
- L193 _protected prototype_ `void GenerateAlignmentTracks(UContextualAnimSceneAsset& SceneAsset);`
- L194 _protected prototype_ `void GenerateIKTargetTracks(UContextualAnimSceneAsset& SceneAsset);`

#### struct `FContextualAnimPoint`  
`struct FContextualAnimPoint`  
_L201-227_
- reflection: `USTRUCT(BlueprintType)`
- L206 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L209 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L212 _public member_ `float Speed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L215 _public member_ `int32 SectionIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L218 _public member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L221 _public member_ `int32 AnimTrackIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L223 _public function_ `FContextualAnimPoint()`
- L224 _public function_ `FContextualAnimPoint(const FName& InRole, const FTransform& InTransform, float InSpeed, int32 InSectionIdx, int32 InAnimSetIdx, int32 InAnimTrackIdx) : Role(InRole), Transform(InTransform), Speed(InSpeed), SectionIdx(InSectionIdx), AnimSetIdx(InAnimSetIdx), AnimTrackIdx(InAnimTrackIdx)`

#### enum `EContextualAnimPointType`  
`enum class EContextualAnimPointType : uint8`  
_L230-235_
- reflection: `UENUM(BlueprintType)`
- L232 _public enumerator_ `FirstFrame`
- L233 _public enumerator_ `SyncFrame`
- L234 _public enumerator_ `LastFrame`

#### enum `EContextualAnimCriterionToConsider`  
`enum class EContextualAnimCriterionToConsider : uint8`  
_L238-243_
- reflection: `UENUM(BlueprintType)`
- L240 _public enumerator_ `All`
- L241 _public enumerator_ `Spatial`
- L242 _public enumerator_ `Other`

#### enum `EContextualAnimActorPreviewType`  
`enum class EContextualAnimActorPreviewType : uint8`  
_L248-254_
- reflection: `UENUM(BlueprintType)`
- L250 _public enumerator_ `SkeletalMesh`
- L251 _public enumerator_ `StaticMesh`
- L252 _public enumerator_ `Actor`
- L253 _public enumerator_ `None`

#### struct `FContextualAnimActorPreviewData`  
`struct FContextualAnimActorPreviewData`  
_L257-278_
- reflection: `USTRUCT(BlueprintType)`
- L262 _public member_ `FName Role;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L265 _public member_ `EContextualAnimActorPreviewType Type = EContextualAnimActorPreviewType::StaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L268 _public member_ `TSoftObjectPtr<class USkeletalMesh> PreviewSkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Type==EContextualAnimActorPreviewType::SkeletalMesh", EditConditionHides))`
- L271 _public member_ `TSoftClassPtr<class UAnimInstance> PreviewAnimInstance;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Type==EContextualAnimActorPreviewType::SkeletalMesh", EditConditionHides))`
- L274 _public member_ `TSoftObjectPtr<class UStaticMesh> PreviewStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Type==EContextualAnimActorPreviewType::StaticMesh", EditConditionHides))`
- L277 _public member_ `TSoftClassPtr<class AActor> PreviewActorClass;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Type==EContextualAnimActorPreviewType::Actor", EditConditionHides))`

#### struct `FContextualAnimPreviewSequenceEntry`  
`struct FContextualAnimPreviewSequenceEntry`  
_L282-297_
- reflection: `USTRUCT(BlueprintType)`
- desc: Entry in a preview sequence that defines which section to play and how many times
- L288 _public member_ `FName SectionName;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (GetOptions = "GetSectionNames"))` — Which section to play
- L292 _public member_ `int32 LoopCount = 1;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (ClampMin = "1", ClampMax = "100"))` — How many times to play this section (1 = play once, 2 = repeat twice, etc.)
- L296 _public member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Which anim set to use. INDEX_NONE = use the editor's active anim set for that section

#### class `UContextualAnimSceneAsset`  
`class UContextualAnimSceneAsset : public UDataAsset`  
_L302-506_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UDataAsset`
- L308 _public typedef_ `typedef TFunctionRef<UE::ContextualAnim::EForEachResult(const FContextualAnimTrack& AnimTrack)> FForEachAnimTrackFunction;`
- L310 _public prototype_ `UContextualAnimSceneAsset(const FObjectInitializer& ObjectInitializer);`
- L313 _public prototype_ `virtual void PostLoad() override;` — Migrate deprecated objects.
- L315 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L317 _public prototype_ `void PrecomputeData();`
- L319 _public prototype_ `void ForEachAnimTrack(FForEachAnimTrackFunction Function) const;`
- L321 _public function_ `inline const FGameplayTag& GetTag() const`
- L322 _public function_ `inline const FName& GetPrimaryRole() const`
- L324 _public function_ `inline EContextualAnimCollisionBehavior GetCollisionBehavior() const` — `UE_DEPRECATED(5.9, "Direct access has been deprecated, Please use CollisionBehaviors array version instead")`
- L326 _public function_ `inline const TArray<FContextualAnimCollisionBehaviorParams>& GetCollisionBehaviors() const`
- L327 _public function_ `inline int32 GetSampleRate() const`
- L328 _public function_ `inline float GetRadius() const`
- L329 _public function_ `inline bool ShouldPrecomputeAlignmentTracks() const`
- L330 _public function_ `inline bool ShouldIgnoreClientMovementErrorChecksAndCorrection() const`
- L331 _public function_ `inline bool ShouldDisableMovementReplicationForSimulatedProxy() const`
- L332 _public function_ `inline bool ShouldFindIdealAnimStartTime() const`
- L333 _public function_ `inline float GetFindIdealStartTimeMargin() const`
- L335 _public function_ `const TArray<FContextualAnimAttachmentParams>& GetAttachmentParams() const`
- L337 _public function_ `const FContextualAnimAttachmentParams* GetAttachmentParamsForRole(FName Role) const`
- L342 _public function_ `const FContextualAnimIKTargetParams& GetIKTargetParams() const`
- L344 _public function_ `bool HasValidData() const`
- L346 _public function_ `const UContextualAnimRolesAsset* GetRolesAsset() const`
- L349 _public prototype_ `TArray<FName> GetRoles() const;` — `UFUNCTION()`
- L351 _public function_ `int32 GetNumRoles() const`
- L353 _public prototype_ `int32 GetNumMandatoryRoles(int32 SectionIdx, int32 AnimSetIdx) const;`
- L355 _public prototype_ `const FTransform& GetMeshToComponentForRole(const FName& Role) const;`
- L358 _public prototype_ `TArray<FName> GetSectionNames() const;` — `UFUNCTION()`
- L360 _public prototype_ `int32 GetNumSections() const;`
- L362 _public prototype_ `int32 GetNumAnimSetsInSection(int32 SectionIdx) const;`
- L364 _public prototype_ `const FContextualAnimSceneSection* GetSection(int32 SectionIdx) const;`
- L366 _public prototype_ `const FContextualAnimSceneSection* GetSection(const FName& SectionName) const;`
- L368 _public prototype_ `const FContextualAnimSet* GetAnimSet(int32 SectionIdx, int32 AnimSetIdx) const;`
- L370 _public prototype_ `int32 GetSectionIndex(const FName& SectionName) const;`
- L372 _public prototype_ `const FContextualAnimTrack* GetAnimTrack(int32 SectionIdx, int32 AnimSetIdx, const FName& Role) const;`
- L374 _public prototype_ `const FContextualAnimTrack* GetAnimTrack(int32 SectionIdx, int32 AnimSetIdx, int32 AnimTrackIdx) const;`
- L376 _public prototype_ `FTransform GetIKTargetTransform(int32 SectionIdx, int32 AnimSetIdx, int32 AnimTrackIdx, const FName& TrackName, float Time) const;`
- L377 _public prototype_ `FTransform GetIKTargetTransform(const FContextualAnimSceneBinding& InBinding, const FName& TrackName, float Time) const;`
- L379 _public prototype_ `FTransform GetAlignmentTransform(int32 SectionIdx, int32 AnimSetIdx, int32 AnimTrackIdx, int32 WarpPointIdx, float Time) const;`
- L380 _public prototype_ `FTransform GetAlignmentTransform(int32 SectionIdx, int32 AnimSetIdx, int32 AnimTrackIdx, const FName& WarpPointName, float Time) const;`
- L381 _public prototype_ `FTransform GetAlignmentTransform(const FContextualAnimTrack& AnimTrack, int32 WarpPointIdx, float Time) const;`
- L382 _public prototype_ `FTransform GetAlignmentTransform(const FContextualAnimTrack& AnimTrack, const FName& WarpPointName, float Time) const;`
- L383 _public prototype_ `FTransform GetAlignmentTransform(const FContextualAnimSceneBinding& InBinding, const FContextualAnimSceneBindings& InBindings, FName WarpPointName, float Time) const;`
- L384 _public prototype_ `FTransform GetAlignmentTransformForRoleRelativeToOtherRole(int32 SectionIdx, int32 AnimSetIdx, FName Role, FName OtherRole, float Time) const;`
- L386 _public prototype_ `const FContextualAnimTrack* FindAnimTrackForRoleWithClosestEntryLocation(int32 SectionIdx, const FName& Role, const FContextualAnimSceneBindingContext& Primary, const FVector& TestLocation) const;`
- L388 _public prototype_ `const FContextualAnimTrack* FindAnimTrackByAnimation(const UAnimSequenceBase* Animation) const;`
- L390 _public prototype_ `const FContextualAnimIKTargetDefContainer& GetIKTargetDefsForRole(const FName& Role) const;`
- L393 _public prototype_ `void GetAlignmentPointsForSecondaryRole(EContextualAnimPointType Type, int32 SectionIdx, const FContextualAnimSceneBindingContext& Primary, TArray<FContextualAnimPoint>& OutResult) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset")`
- L396 _public prototype_ `void GetAlignmentPointsForSecondaryRoleConsideringSelectionCriteria(EContextualAnimPointType Type, int32 SectionIdx, const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier, EContextualAnimCriterionToConsider CriterionToConsider, TArray<FContextualAnimPoint>& OutResult) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset")`
- L404 _public prototype_ `UAnimSequenceBase* BP_FindAnimationForRole(int32 SectionIdx, int32 AnimSetIdx, FName Role) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Find Animation For Role"))`
- L407 _public prototype_ `int32 BP_FindAnimSetIndexByAnimation(int32 SectionIdx, const UAnimSequenceBase* Animation) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Find AnimSet Index By Animation"))`
- L410 _public prototype_ `FTransform BP_GetAlignmentTransformForRoleRelativeToWarpPoint(int32 SectionIdx, int32 AnimSetIdx, FName Role, float Time) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Get Alignment Transform For Role Relative To WarpPoint"))`
- L413 _public prototype_ `FTransform BP_GetIKTargetTransformForRoleAtTime(int32 SectionIdx, int32 AnimSetIdx, FName Role, FName TrackName, float Time) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Get IK Target Transform For Role At Time"))`
- L416 _public prototype_ `FTransform BP_GetIKTargetTransformForBindingAtTime(const FContextualAnimSceneBinding& InBinding, FName TrackName, float Time) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Get IK Target Transform For Binding At Time"))`
- L419 _public prototype_ `void BP_GetStartAndEndTimeForWarpSection(int32 SectionIdx, int32 AnimSetIdx, FName Role, FName WarpSectionName, float& OutStartTime, float& OutEndTime) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Get Start and End Time For Warp Section"))`
- L423 _public prototype_ `bool Query(FName Role, FContextualAnimQueryResult& OutResult, const FContextualAnimQueryParams& QueryParams, const FTransform& ToWorldTransform) const;` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset")` — @TODO: Kept around only to do not break existing content. It will go away in the future.
- L424 _public prototype_ `float FindBestAnimStartTime(const FContextualAnimTrack& AnimTrack, const FVector& LocalLocation) const;`
- L429 _protected member_ `TObjectPtr<UContextualAnimRolesAsset> RolesAsset;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L432 _protected member_ `FName PrimaryRole = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (GetOptions = "GetRoles"))`
- L436 _protected member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Optional GameplayTag that can be used to identify this particular scene asset
- L441 _protected member_ `TArray<FContextualAnimActorPreviewData> OverridePreviewData;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (TitleProperty = "Role"))`
- L444 _protected member_ `TSubclassOf<UObject> PreviewOverrideProvider = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (TitleProperty = "Role", MustImplement = "/Script/ContextualAnimation.ContextualAnimOverrideInterface"))`
- L448 _protected member_ `TArray<FContextualAnimPreviewSequenceEntry> MultiSectionPreviewSequence;` — `UPROPERTY(EditAnywhere, Category = "Preview", meta = (TitleProperty = "SectionName"))` — Defines a sequence of sections for multi-section preview (e.g. Intro -> Loop x3 -> Outro)
- L453 _protected member_ `TArray<FContextualAnimSceneSection> Sections;` — `UPROPERTY(EditAnywhere, Category = "Defaults")`
- L456 _protected member_ `float Radius = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L460 _protected member_ `EContextualAnimCollisionBehavior CollisionBehavior_DEPRECATED = EContextualAnimCollisionBehavior::None;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Direct access has been deprecated, Please use CollisionBehaviors array version instead"))`
- L463 _protected member_ `TArray<FContextualAnimIgnoreChannelsParam> CollisionChannelsToIgnoreParams_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Direct access has been deprecated, Please use CollisionBehaviors array version instead"))`
- L467 _protected member_ `TArray<FContextualAnimCollisionBehaviorParams> CollisionBehaviors;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L470 _protected member_ `TArray<FContextualAnimAttachmentParams> AttachmentParams;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L473 _protected member_ `FContextualAnimIKTargetParams IKTargetParams;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName = "IK Target Params"))`
- L480 _protected member_ `bool bFindIdealAnimStartTime = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Whether to find ideal start time for the interaction based on the distance from the actor to the warp target in the animation and the actual distance in game. Effectively skipping the portion of the 'approach-motion' the actor doesn't need.
- L487 _protected member_ `float FindIdealStartTimeMargin = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (EditCondition = "bFindIdealAnimStartTime", EditConditionHides))` — Time (in seconds) reserved at the end of the warp window to ensure motion warping has enough room to reach the target. The ideal start time search will not go beyond (WarpEndTime - FindIdealStartTimeMargin).
- L491 _protected member_ `bool bIgnoreClientMovementErrorChecksAndCorrection = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", AdvancedDisplay)` — Whether to ignore movement error checks and corrections during the interaction for player characters
- L495 _protected member_ `bool bDisableMovementReplicationForSimulatedProxy = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", AdvancedDisplay)` — Whether to disable movement replication during the interaction for simulated proxies (NPCs only).
- L499 _protected member_ `bool bPrecomputeAlignmentTracks = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", AdvancedDisplay)` — Whether we should extract and cache alignment tracks off line.
- L503 _protected member_ `int32 SampleRate = 15;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "1", ClampMax = "60"), AdvancedDisplay)` — Sample rate (frames per second) used when sampling the animations to generate alignment and IK tracks

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CONTEXTUALANIMATION_API`
- L67 _function_ `if (const FContextualAnimIgnoreChannelsParam* Param = CollisionChannelsToIgnoreParams.FindByPredicate([Role](const FContextualAnimIgnoreChannelsParam& Item) { return Item.Role == Role; }))` (scope `FContextualAnimCollisionBehaviorParams::GetCollisionChannelsToIgnoreForRole`)
- L81 _function_ `if (const FContextualAnimCollisionProfileParam* Param = CollisionProfileParams.FindByPredicate([Role](const FContextualAnimCollisionProfileParam& Item) { return Item.Role == Role; }))` (scope `FContextualAnimCollisionBehaviorParams::GetCollisionProfileNameForRole`)
- L121 _function_ `return Roles.FindByPredicate([Name](const FContextualAnimRoleDefinition& RoleDef) { return RoleDef.Name == Name; });` (scope `UContextualAnimRolesAsset::FindRoleDefinitionByName`)
- L339 _function_ `return AttachmentParams.FindByPredicate([Role](const FContextualAnimAttachmentParams& Item) { return Item.Role == Role; });` (scope `UContextualAnimSceneAsset::GetAttachmentParamsForRole`)

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimSelectionCriterion.h` (Public)


#### enum `EContextualAnimCriterionType`  
`enum class EContextualAnimCriterionType : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Spatial`
- L16 _public enumerator_ `Other`

#### class `UContextualAnimSelectionCriterion`  
`class UContextualAnimSelectionCriterion : public UObject`  
_L23-37_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, EditInlineNew)`
- inherits: `UObject`
- L30 _public member_ `EContextualAnimCriterionType Type = EContextualAnimCriterionType::Spatial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")`
- L32 _public prototype_ `UContextualAnimSelectionCriterion(const FObjectInitializer& ObjectInitializer);`
- L34 _public prototype_ `class UContextualAnimSceneAsset* GetSceneAssetOwner() const;`
- L36 _public function_ `virtual bool DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const`

#### class `UContextualAnimSelectionCriterion_Blueprint`  
`class UContextualAnimSelectionCriterion_Blueprint : public UContextualAnimSelectionCriterion`  
_L43-58_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UContextualAnimSelectionCriterion`
- L49 _public prototype_ `UContextualAnimSelectionCriterion_Blueprint(const FObjectInitializer& ObjectInitializer);`
- L52 _public prototype_ `bool BP_DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Default", meta = (DisplayName = "Does Querier Pass Condition"))`
- L55 _public prototype_ `const UContextualAnimSceneAsset* GetSceneAsset() const;` — `UFUNCTION(BlueprintPure, Category = "Default")`
- L57 _public prototype_ `virtual bool DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const override;`

#### class `UContextualAnimSelectionCriterion_TriggerArea`  
`class UContextualAnimSelectionCriterion_TriggerArea : public UContextualAnimSelectionCriterion`  
_L64-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContextualAnimSelectionCriterion`
- L71 _public member_ `TArray<FVector> PolygonPoints;` — `UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite, Category = "Default", meta = (EditFixedOrder))`
- L74 _public member_ `float Height = 100.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0", UIMin = "0"))`
- L76 _public prototype_ `UContextualAnimSelectionCriterion_TriggerArea(const FObjectInitializer& ObjectInitializer);`
- L78 _public prototype_ `virtual bool DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const override;`

#### enum `EContextualAnimCriterionConeMode`  
`enum class EContextualAnimCriterionConeMode : uint8`  
_L85-92_
- reflection: `UENUM(BlueprintType)`
- L88 _public enumerator_ `ToPrimary` — Uses the angle between the vector from querier to primary and querier forward vector rotated by offset
- L91 _public enumerator_ `FromPrimary` — Uses the angle between the vector from primary to querier and primary forward vector rotated by offset

#### class `UContextualAnimSelectionCriterion_Cone`  
`class UContextualAnimSelectionCriterion_Cone : public UContextualAnimSelectionCriterion`  
_L95-116_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContextualAnimSelectionCriterion`
- L102 _public member_ `EContextualAnimCriterionConeMode Mode = EContextualAnimCriterionConeMode::ToPrimary;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L105 _public member_ `float Distance = 200.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0", UIMin = "0"))`
- L108 _public member_ `float HalfAngle = 45.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0", UIMin = "0", ClampMax = "180", UIMax = "180"))`
- L111 _public member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "-180", UIMin = "-180", ClampMax = "180", UIMax = "180"))`
- L113 _public function_ `UContextualAnimSelectionCriterion_Cone(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L115 _public prototype_ `virtual bool DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const override;`

#### enum `EContextualAnimCriterionDistanceMode`  
`enum class EContextualAnimCriterionDistanceMode : uint8`  
_L122-126_
- reflection: `UENUM(BlueprintType)`
- L124 _public enumerator_ `Distance_3D`
- L125 _public enumerator_ `Distance_2D`

#### class `UContextualAnimSelectionCriterion_Distance`  
`class UContextualAnimSelectionCriterion_Distance : public UContextualAnimSelectionCriterion`  
_L129-147_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UContextualAnimSelectionCriterion`
- L136 _public member_ `EContextualAnimCriterionDistanceMode Mode = EContextualAnimCriterionDistanceMode::Distance_2D;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")`
- L139 _public member_ `float MinDistance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0", UIMin = "0"))`
- L142 _public member_ `float MaxDistance = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ClampMin = "0", UIMin = "0"))`
- L144 _public function_ `UContextualAnimSelectionCriterion_Distance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L146 _public prototype_ `virtual bool DoesQuerierPassCondition(const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Querier) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CONTEXTUALANIMATION_API`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimTypes.h` (Public)


#### enum `UE::ContextualAnim::EForEachResult`  
`enum class EForEachResult : uint8`  
_L33-37_
- L35 _public enumerator_ `Break`
- L36 _public enumerator_ `Continue`

#### struct `FContextualAnimAlignmentTrackContainer`  
`struct FContextualAnimAlignmentTrackContainer`  
_L43-69_
- reflection: `USTRUCT()`
- desc: Container for alignment tracks
- L48 _public member_ `FAnimSequenceTrackContainer Tracks;` — `UPROPERTY()`
- L51 _public member_ `float SampleInterval = 0.f;` — `UPROPERTY()`
- L53 _public function_ `void Initialize(int32 InNumTracks, float InSampleInterval)`
- L60 _public function_ `void Empty()`
- L67 _public prototype_ `FTransform ExtractTransformAtTime(int32 TrackIndex, float Time) const;`
- L68 _public prototype_ `FTransform ExtractTransformAtTime(const FName& TrackName, float Time) const;`

#### struct `FContextualAnimTrack`  
`struct FContextualAnimTrack`  
_L72-140_
- reflection: `USTRUCT(BlueprintType)`
- L77 _public member_ `TObjectPtr<UAnimSequenceBase> Animation = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L80 _public member_ `float AnimMaxStartTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L84 _public member_ `bool bChangeMovementMode = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — If true, will set the movement mode of the character using CAS, to 'MovementMode', during the scope of this anim track.
- L92 _public member_ `uint8 CustomMovementMode = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (EditConditionHides, EditCondition = "MovementMode==EMovementMode::MOVE_Custom"))` — If 'bChangeMovementMode' is true, and the 'MovementMode' is Custom, it'll set this custom movement mode during the scope of this anim track.
- L96 _public member_ `bool bControlCharacterRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — If true: disable orientation of the character towards movement, controller's rotation and physics driven rotation during root motion.
- L100 _public member_ `bool bOptional = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Whether the actor that should play this animation is optional
- L104 _public member_ `FContextualAnimAlignmentTrackContainer AlignmentData;` — `UPROPERTY()` — Container for alignment tracks
- L108 _public member_ `FContextualAnimAlignmentTrackContainer IKTargetData;` — `UPROPERTY()` — Container for auto generate IK Target Tracks
- L111 _public member_ `TArray<TObjectPtr<UContextualAnimSelectionCriterion>> SelectionCriteria;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Defaults")`
- L114 _public member_ `FTransform MeshToScene;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L117 _public member_ `FName Role = NAME_None;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")`
- L120 _public member_ `int32 SectionIdx = INDEX_NONE;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")`
- L123 _public member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")`
- L126 _public member_ `int32 AnimTrackIdx = INDEX_NONE;` — `UPROPERTY(BlueprintReadOnly, Category = "Defaults")`
- L129 _public prototype_ `float GetSyncTimeForWarpSection(int32 WarpSectionIndex) const;` — DEPRECATED: Will go away soon
- L130 _public prototype_ `float GetSyncTimeForWarpSection(const FName& WarpSectionName) const;`
- L132 _public prototype_ `void GetStartAndEndTimeForWarpSection(int32 WarpSectionIndex, float& OutStartTime, float& OutEndTime) const;`
- L133 _public prototype_ `void GetStartAndEndTimeForWarpSection(const FName& WarpSectionName, float& OutStartTime, float& OutEndTime) const;`
- L135 _public prototype_ `bool DoesQuerierPassSelectionCriteria(const FContextualAnimSceneBindingContext& PrimaryActorData, const FContextualAnimSceneBindingContext& QuerierData) const;`
- L137 _public prototype_ `FTransform GetRootTransformAtTime(float Time) const;`
- L139 _public member_ `static const FContextualAnimTrack EmptyTrack;`

#### enum `EContextualAnimJoinRule`  
`enum class EContextualAnimJoinRule : uint8`  
_L144-148_
- reflection: `UENUM(BlueprintType)`
- desc: Defines when the actor should start playing the animation
- L146 _public enumerator_ `Default`
- L147 _public enumerator_ `Late`

#### enum `EContextualAnimIKTargetProvider`  
`enum class EContextualAnimIKTargetProvider : uint8`  
_L151-163_
- reflection: `UENUM(BlueprintType)`
- L157 _public enumerator_ `Autogenerated` — IK Targets are auto generated from the animations @see: UContextualAnimSceneAssetBase::GenerateIKTargetTracks
- L160 _public enumerator_ `Bone` — IK Target defined by a bone or a socket in the animation

#### struct `FContextualAnimIKTargetDefinition`  
`struct FContextualAnimIKTargetDefinition`  
_L166-193_
- reflection: `USTRUCT(BlueprintType)`
- L171 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L174 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L177 _public member_ `EContextualAnimIKTargetProvider Provider = EContextualAnimIKTargetProvider::Autogenerated;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L180 _public member_ `FName TargetRoleName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L183 _public member_ `FName TargetBoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L185 _public function_ `bool operator==(const FContextualAnimIKTargetDefinition& Other) const`

#### struct `FContextualAnimIKTarget`  
`struct FContextualAnimIKTarget`  
_L196-217_
- reflection: `USTRUCT(BlueprintType)`
- L201 _public member_ `FName GoalName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L204 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L207 _public member_ `float Alpha = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L210 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L212 _public function_ `FContextualAnimIKTarget()`
- L213 _public function_ `FContextualAnimIKTarget(const FName& InGoalName, const FName& InBoneName, float InAlpha, const FTransform& InTransform) : GoalName(InGoalName), BoneName(InBoneName), Alpha(InAlpha), Transform(InTransform)`
- L216 _public member_ `static const FContextualAnimIKTarget InvalidIKTarget;`

#### struct `FContextualAnimIKTargetDefContainer`  
`struct FContextualAnimIKTargetDefContainer`  
_L220-233_
- reflection: `USTRUCT(BlueprintType)`
- L226 _public member_ `FName Role = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (GetOptions = "GetRoles"))` — Role this IK Target definitions are for
- L230 _public member_ `TArray<FContextualAnimIKTargetDefinition> IKTargetDefs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (DisplayName = "Definitions"))` — List of IK Target definitions
- L232 _public member_ `static const FContextualAnimIKTargetDefContainer EmptyContainer;`

#### enum `EContextualAnimIKTargetAlphaProvider`  
`enum class EContextualAnimIKTargetAlphaProvider : uint8`  
_L236-252_
- reflection: `UENUM(BlueprintType)`
- L242 _public enumerator_ `AnimNotifyState` — Alpha value is determine by an IK Window in the animation. IK Target transform will only be calculated when alpha is bigger than 0
- L248 _public enumerator_ `Curve` — Alpha value is determined by a curve in the animation with the same name as the IK Target IK Target transform will only be calculated when alpha is bigger than 0
- L251 _public enumerator_ `None` — IK Target transform will be calculated during the entire interaction. Alpha value will be always 1

#### struct `FContextualAnimIKTargetParams`  
`struct FContextualAnimIKTargetParams`  
_L255-266_
- reflection: `USTRUCT()`
- L261 _public member_ `TArray<FContextualAnimIKTargetDefContainer> IKTargetDefsForEachRole;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (TitleProperty = "Role", DisplayName = "IK Target Defs For Each Role"))` — IK Target definitions for each role in the interaction
- L265 _public member_ `EContextualAnimIKTargetAlphaProvider AlphaProvider = EContextualAnimIKTargetAlphaProvider::AnimNotifyState;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Method used to determine the alpha of IK targets at runtime

#### struct `FContextualAnimRoleDefinition`  
`struct FContextualAnimRoleDefinition`  
_L272-292_
- reflection: `USTRUCT(BlueprintType)`
- L277 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L280 _public member_ `bool bIsCharacter = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L283 _public member_ `float PreviewCapsuleHalfHeight = 88.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (EditCondition = "bIsCharacter", EditConditionHides))`
- L286 _public member_ `float PreviewCapsuleRadius = 34.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (EditCondition = "bIsCharacter", EditConditionHides))`
- L289 _public member_ `FTransform MeshToComponent = FTransform(FRotator(0.f, 0.f, 0.f));` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L291 _public member_ `static const FContextualAnimRoleDefinition InvalidRoleDefinition;`

#### enum `EContextualAnimWarpPointDefinitionMode`  
`enum class EContextualAnimWarpPointDefinitionMode : uint8`  
_L299-318_
- reflection: `UENUM(BlueprintType)`
- desc: Different modes for defining warp points
- L305 _public enumerator_ `PrimaryActor` — Warp point will be at the location/rotation of the primary actor. Commonly used when interacting with static objects
- L311 _public enumerator_ `Socket` — Warp point will be at the location/rotation of a socket on the primary actor. Commonly used when re-using the same interaction animations to interact with objects with different proportions
- L317 _public enumerator_ `Custom` — Warp point will be calculated based on a set of rules. Commonly used when we want actors to align at some point between them

#### struct `FContextualAnimWarpPointCustomParams`  
`struct FContextualAnimWarpPointCustomParams`  
_L322-337_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters used to calculate a warp point when using 'Custom' mode
- L327 _public member_ `FName Origin = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (GetOptions = "GetRoles"))`
- L330 _public member_ `bool bAlongClosestDistance = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L333 _public member_ `FName OtherRole = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (GetOptions = "GetRoles", EditCondition = "bAlongClosestDistance"))`
- L336 _public member_ `float Weight = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0", EditCondition = "bAlongClosestDistance"))`

#### struct `FContextualAnimWarpPointDefinition`  
`struct FContextualAnimWarpPointDefinition`  
_L344-363_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contain the params necessary to calculate a warp point for the scene. A warp point is a transform in the scene that can be used as reference to calculate alignment between actors
- L350 _public member_ `FName WarpTargetName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Name of the warp target in the warping window this warp point is for
- L354 _public member_ `EContextualAnimWarpPointDefinitionMode Mode = EContextualAnimWarpPointDefinitionMode::PrimaryActor;` — `UPROPERTY(EditAnywhere, Category = "Defaults")` — Method used to calculate this warp point
- L358 _public member_ `FName SocketName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Mode==EContextualAnimWarpPointDefinitionMode::Socket", EditConditionHides))` — Name of the socket in the primary actor acting as warping point. Only relevant when Mode is Socket
- L362 _public member_ `FContextualAnimWarpPointCustomParams Params;` — `UPROPERTY(EditAnywhere, Category = "Defaults", meta = (EditCondition = "Mode==EContextualAnimWarpPointDefinitionMode::Custom", EditConditionHides, FullyExpand = "true"))` — Set of rules used to calculate the warp point. Only relevant when Mode is Custom

#### struct `FContextualAnimWarpPoint`  
`struct FContextualAnimWarpPoint`  
_L369-381_
- reflection: `USTRUCT(BlueprintType)`
- L373 _public prototype_ `FContextualAnimWarpPoint() = default;`
- L374 _public function_ `FContextualAnimWarpPoint(const FName InName, const FTransform& InTransform) : Name(InName), Transform(InTransform)`
- L377 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L380 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`

#### struct `FContextualAnimSceneBindingContext`  
`struct FContextualAnimSceneBindingContext`  
_L387-455_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake = "/Script/ContextualAnimation.ContextualAnimUtilities:BP_SceneBindingContext_MakeFromActor"))`
- L391 _public function_ `FContextualAnimSceneBindingContext()`
- L393 _public function_ `FContextualAnimSceneBindingContext(AActor* InActor, const TOptional<FTransform>& InExternalTransform = TOptional<FTransform>(), const TOptional<FVector>& InExternalVelocity = TOptional<FVector>()) : Actor(InActor), ExternalTransform(InExternalTransform), ExternalVelocity(InExternalVelocity)`
- L396 _public function_ `FContextualAnimSceneBindingContext(const FTransform& InExternalTransform, const TOptional<FVector>& InExternalVelocity = TOptional<FVector>()) : ExternalTransform(InExternalTransform), ExternalVelocity(InExternalVelocity)`
- L399 _public function_ `FContextualAnimSceneBindingContext(AActor* InActor, const FGameplayTagContainer& InExternalTags) : Actor(InActor), ExternalGameplayTags(InExternalTags)`
- L402 _public function_ `AActor* GetActor() const`
- L404 _public prototype_ `UAnimInstance* GetAnimInstance() const;`
- L406 _public prototype_ `USkeletalMeshComponent* GetSkeletalMeshComponent() const;`
- L408 _public prototype_ `UContextualAnimSceneActorComponent* GetSceneActorComponent() const;`
- L410 _public prototype_ `UCharacterMovementComponent* GetCharacterMovementComponent() const;`
- L412 _public prototype_ `UMotionWarpingComponent* GetMotionWarpingComponent() const;`
- L414 _public prototype_ `void SetExternalTransform(const FTransform& InTransform);`
- L416 _public prototype_ `FTransform GetTransform() const;`
- L418 _public prototype_ `FVector GetVelocity() const;`
- L420 _public prototype_ `void AddGameplayTag(const FGameplayTag& Tag);`
- L422 _public function_ `const FGameplayTagContainer& GetGameplayTags() const`
- L424 _public prototype_ `bool HasMatchingGameplayTag(const FGameplayTag& TagToCheck) const;`
- L426 _public prototype_ `bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;`
- L428 _public prototype_ `bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const;`
- L433 _private member_ `TWeakObjectPtr<AActor> Actor = nullptr;` — `UPROPERTY()`
- L436 _private member_ `mutable TWeakObjectPtr<UContextualAnimSceneActorComponent> CachedSceneActorComp = nullptr;` — `UPROPERTY(NotReplicated)`
- L439 _private member_ `mutable TWeakObjectPtr<UAnimInstance> CachedAnimInstance = nullptr;` — `UPROPERTY(NotReplicated)`
- L442 _private member_ `mutable TWeakObjectPtr<USkeletalMeshComponent> CachedSkeletalMesh = nullptr;` — `UPROPERTY(NotReplicated)`
- L445 _private member_ `mutable TWeakObjectPtr<UCharacterMovementComponent> CachedMovementComp = nullptr;` — `UPROPERTY(NotReplicated)`
- L448 _private member_ `mutable TWeakObjectPtr<UMotionWarpingComponent> CachedMotionWarpingComp = nullptr;` — `UPROPERTY(NotReplicated)`
- L450 _private member_ `TOptional<FTransform> ExternalTransform;`
- L452 _private member_ `TOptional<FVector> ExternalVelocity;`
- L454 _private member_ `FGameplayTagContainer ExternalGameplayTags;`

#### struct `FContextualAnimSceneBinding`  
`struct FContextualAnimSceneBinding`  
_L459-542_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represent an actor bound to a role in the scene
- L463 _public function_ `FContextualAnimSceneBinding()`
- L464 _public prototype_ `FContextualAnimSceneBinding(const FContextualAnimSceneBindingContext& InContext, const FContextualAnimTrack& InAnimTrack);`
- L466 _public function_ `inline const FContextualAnimSceneBindingContext& GetContext() const`
- L467 _public function_ `inline FContextualAnimSceneBindingContext& GetContext()`
- L468 _public function_ `inline AActor* GetActor() const`
- L469 _public function_ `inline FTransform GetTransform() const`
- L470 _public function_ `inline FVector GetVelocity() const`
- L471 _public function_ `inline UAnimInstance* GetAnimInstance() const`
- L472 _public function_ `inline USkeletalMeshComponent* GetSkeletalMeshComponent() const`
- L473 _public function_ `inline UContextualAnimSceneActorComponent* GetSceneActorComponent() const`
- L474 _public function_ `inline UCharacterMovementComponent* GetCharacterMovementComponent() const`
- L475 _public function_ `inline UMotionWarpingComponent* GetMotionWarpingComponent() const`
- L476 _public function_ `inline int8 GetSectionIdx() const`
- L477 _public function_ `inline int8 GetAnimSetIdx() const`
- L478 _public function_ `inline int8 GetAnimTrackIdx() const`
- L480 _public prototype_ `FTransform GetIKTargetTransform(const FName& TrackName, float Time) const;`
- L481 _public prototype_ `FTransform GetAlignmentTransform(const FName& TrackName, float Time) const;`
- L483 _public prototype_ `void SetAnimTrack(const FContextualAnimTrack& InAnimTrack);`
- L486 _public prototype_ `float GetAnimMontageTime() const;` — Return the current playback time of the animation this actor is playing
- L488 _public prototype_ `FName GetCurrentSection() const;`
- L490 _public prototype_ `int32 GetCurrentSectionIndex() const;`
- L493 _public prototype_ `FAnimMontageInstance* GetAnimMontageInstance() const;` — Returns the ActiveMontageInstance or null in the case of static actors
- L495 _public member_ `static const FContextualAnimSceneBinding InvalidBinding;`
- L497 _public function_ `UAnimSequenceBase* GetAnimation() const`
- L499 _public function_ `FContextualAnimAlignmentTrackContainer& GetAlignmentData()`
- L500 _public function_ `const FContextualAnimAlignmentTrackContainer& GetAlignmentData() const`
- L502 _public function_ `FContextualAnimAlignmentTrackContainer& GetIKTargetData()`
- L503 _public function_ `const FContextualAnimAlignmentTrackContainer& GetIKTargetData() const`
- L505 _public function_ `const FTransform& GetMeshToScene() const`
- L506 _public function_ `FTransform& GetMeshToScene()`
- L508 _public prototype_ `void SetOverrideData(const FContextualAnimationOverrideData& InData);`
- L516 _private member_ `FContextualAnimSceneBindingContext Context;` — `UPROPERTY()`
- L519 _private member_ `int8 SectionIdx = INDEX_NONE;` — `UPROPERTY()`
- L522 _private member_ `int8 AnimSetIdx = INDEX_NONE;` — `UPROPERTY()`
- L525 _private member_ `int8 AnimTrackIdx = INDEX_NONE;` — `UPROPERTY()`
- L528 _private member_ `TObjectPtr<UAnimSequenceBase> Animation = nullptr;` — `UPROPERTY()`
- L532 _private member_ `FContextualAnimAlignmentTrackContainer AlignmentData;` — `UPROPERTY(NotReplicated)` — Container for alignment tracks
- L536 _private member_ `FContextualAnimAlignmentTrackContainer IKTargetData;` — `UPROPERTY(NotReplicated)` — Container for auto generate IK Target Tracks
- L539 _private member_ `FTransform MeshToScene;` — `UPROPERTY()`

#### struct `FContextualAnimSceneBindings`  
`struct FContextualAnimSceneBindings`  
_L545-671_
- reflection: `USTRUCT(BlueprintType)`
- L549 _public function_ `FContextualAnimSceneBindings()`
- L552 _public prototype_ `FContextualAnimSceneBindings(const UContextualAnimSceneAsset& InSceneAsset, int32 InSectionIdx, int32 InAnimSetIdx);` — `UE_DEPRECATED(5.7, "This constructor is deprecated. Please use the version with the other signature")`
- L554 _public prototype_ `FContextualAnimSceneBindings(const UContextualAnimSceneAsset& InSceneAsset);`
- L556 _public function_ `const FContextualAnimSceneBinding* FindBindingByActor(const AActor* Actor) const`
- L561 _public function_ `FContextualAnimSceneBinding* FindBindingByActor(const AActor* Actor)`
- L566 _public function_ `const FContextualAnimSceneBinding* FindBindingByRole(const FName& Role) const`
- L571 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L573 _public function_ `inline uint8 GetID() const`
- L574 _public function_ `inline const UContextualAnimSceneAsset* GetSceneAsset() const`
- L577 _public function_ `inline int32 GetSectionIdx() const` — `UE_DEPRECATED(5.7, "This getter and its corresponding property is deprecated. SectionIdx is now stored per Binding")`
- L580 _public function_ `inline int32 GetAnimSetIdx() const` — `UE_DEPRECATED(5.7, "This getter and its corresponding property is deprecated. AnimSetIdx is now stored per Binding")`
- L582 _public function_ `inline int32 Num() const`
- L583 _public function_ `inline int32 Add(const FContextualAnimSceneBinding& NewData)`
- L584 _public function_ `inline const TArray<FContextualAnimSceneBinding>& GetBindings() const`
- L586 _public function_ `inline TArray<FContextualAnimSceneBinding>::RangedForIteratorType begin()`
- L587 _public function_ `inline TArray<FContextualAnimSceneBinding>::RangedForConstIteratorType begin() const`
- L588 _public function_ `inline TArray<FContextualAnimSceneBinding>::RangedForIteratorType end()`
- L589 _public function_ `inline TArray<FContextualAnimSceneBinding>::RangedForConstIteratorType end() const`
- L591 _public prototype_ `static bool CheckConditions(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, int32 AnimSetIdx, const TMap<FName, FContextualAnimSceneBindingContext>& Params);`
- L592 _public prototype_ `static bool TryCreateBindings(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, int32 AnimSetIdx, const TMap<FName, FContextualAnimSceneBindingContext>& Params, FContextualAnimSceneBindings& OutBindings);`
- L593 _public prototype_ `static bool TryCreateBindings(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, const TMap<FName, FContextualAnimSceneBindingContext>& Params, FContextualAnimSceneBindings& OutBindings);`
- L594 _public prototype_ `static bool TryCreateBindings(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, int32 AnimSetIdx, const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Secondary, FContextualAnimSceneBindings& OutBindings);`
- L595 _public prototype_ `static bool TryCreateBindings(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Secondary, FContextualAnimSceneBindings& OutBindings);`
- L596 _public prototype_ `static int32 FindAnimSet(const UContextualAnimSceneAsset& SceneAsset, int32 SectionIdx, const TMap<FName, FContextualAnimSceneBindingContext>& Params);`
- L598 _public prototype_ `bool BindActorToRole(AActor& ActorRef, FName Role, int32 SectionIdx, int32 AnimSetIdx);`
- L600 _public prototype_ `bool SetRoleWarpTarget(const FName Role, const FName WarpTargetName, const FTransform& Transform);`
- L603 _public prototype_ `void CalculateWarpPoints(TArray<FContextualAnimWarpPoint>& OutWarpPoints) const;` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use the version that takes a Section Index")`
- L605 _public prototype_ `void CalculateWarpPoints(TArray<FContextualAnimWarpPoint>& OutWarpPoints, int32 SectionIdx) const;`
- L607 _public prototype_ `bool CalculateWarpPoint(const FContextualAnimWarpPointDefinition& WarpPointDef, FContextualAnimWarpPoint& OutWarpPoint) const;`
- L609 _public prototype_ `const FContextualAnimTrack& GetAnimTrackFromBinding(const FContextualAnimSceneBinding& Binding) const;`
- L610 _public prototype_ `const FName& GetRoleFromBinding(const FContextualAnimSceneBinding& Binding) const;`
- L611 _public prototype_ `FTransform GetAlignmentTransformFromBinding(const FContextualAnimSceneBinding& Binding, const FName& TrackName, float Time) const;`
- L612 _public prototype_ `const FContextualAnimIKTargetDefContainer& GetIKTargetDefContainerFromBinding(const FContextualAnimSceneBinding& Binding) const;`
- L613 _public prototype_ `FTransform GetIKTargetTransformFromBinding(const FContextualAnimSceneBinding& Binding, const FName& TrackName, float Time) const;`
- L616 _public prototype_ `bool ShouldSyncAnimation() const;` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use ShouldBindingSyncAnimation instead")`
- L618 _public prototype_ `bool ShouldBindingSyncAnimation(const FContextualAnimSceneBinding& Binding) const;`
- L619 _public prototype_ `const FContextualAnimSceneBinding* GetSyncLeader() const;`
- L620 _public prototype_ `const FContextualAnimSceneBinding* GetPrimaryBinding() const;`
- L622 _public prototype_ `bool IsValid() const;`
- L624 _public prototype_ `void Reset();`
- L626 _public prototype_ `void Clear();`
- L628 _public prototype_ `void GenerateUniqueId();`
- L630 _public prototype_ `int32 FindAnimSetForTransitionTo(int32 NewSectionIdx) const;`
- L631 _public prototype_ `void TransitionTo(int32 NewSectionIdx, int32 NewAnimSetIdx);`
- L633 _public prototype_ `bool RemoveActor(AActor& ActorRef);`
- L635 _public prototype_ `bool AreAllBindingsInTheSameSection() const;`
- L637 _public prototype_ `void SetOverrideProvider(const TScriptInterface <IContextualAnimOverrideInterface>& Provider);`
- L639 _public function_ `const TScriptInterface <IContextualAnimOverrideInterface>& GetOverrideProvider() const`
- L645 _public prototype_ `bool UpdateBindingOverridesIfNeeded();` — Updates Each Bindings Overrides, Including Animation, Alignment IK, ETC Returns True is there is a valid Scene and Override Provider
- L652 _private member_ `uint8 Id = 0;` — `UPROPERTY()`
- L655 _private member_ `TObjectPtr<const UContextualAnimSceneAsset> SceneAsset = nullptr;` — `UPROPERTY()`
- L659 _private member_ `int8 SectionIdx_DEPRECATED = INDEX_NONE;` — `UPROPERTY()` — This property is deprecated and will be removed soon. AnimSetIdx is now stored per Binding
- L663 _private member_ `int8 AnimSetIdx_DEPRECATED = INDEX_NONE;` — `UPROPERTY()` — This property is deprecated and will be removed soon. AnimSetIdx is now stored per Binding
- L667 _private member_ `TArray<FContextualAnimSceneBinding> Data;` — `UPROPERTY()` — List of actors bound to each role in the SceneAsset
- L670 _private member_ `TScriptInterface<IContextualAnimOverrideInterface> OverrideProviderInterface = nullptr;` — `UPROPERTY()`

#### struct `FContextualAnimStartSceneParams`  
`struct FContextualAnimStartSceneParams`  
_L676-706_
- reflection: `USTRUCT(BlueprintType)`
- L682 _public member_ `TMap<FName, FContextualAnimSceneBindingContext> RoleToActorMap;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Map with actors to bind to each role in the scene
- L686 _public member_ `int32 SectionIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Desired section. If INDEX_NONE the Manager will use or find best set in the first section.
- L692 _public member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")` — Desired set. If INDEX_NONE the Manager will attempt to find the best set to use by running the selection criteria. The selection will be performed in the section specified by SectionIdx or in the first section if SectionIdx == INDEX_NONE.
- L697 _public member_ `TArray<FContextualAnimWarpPoint> WarpPoints;` — Precomputed warp points that could be provided when starting a scene. When not provided, the warp points will be automatically computed using local context information.
- L699 _public function_ `void Reset()`

#### struct `FContextualAnimQueryResult`  
`struct FContextualAnimQueryResult`  
_L715-743_
- reflection: `USTRUCT(BlueprintType)`
- desc: Stores the result of a query function @TODO: Only used by UContextualAnimSceneAsset::Query. Kept around only to do not break existing content. It will go away in the future.
- L720 _public member_ `TWeakObjectPtr<UAnimMontage> Animation;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L723 _public member_ `FTransform EntryTransform;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L726 _public member_ `FTransform SyncTransform;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L729 _public member_ `float AnimStartTime = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L732 _public member_ `int32 AnimSetIdx = INDEX_NONE;` — `UPROPERTY(BlueprintReadWrite, Category = "Defaults")`
- L734 _public function_ `void Reset()`
- L742 _public function_ `inline bool IsValid() const`

#### struct `FContextualAnimQueryParams`  
`struct FContextualAnimQueryParams`  
_L750-773_
- reflection: `USTRUCT(BlueprintType)`
- desc: Stores the parameters passed into query function @TODO: Only used by UContextualAnimSceneAsset::Query. Kept around only to do not break existing content. It will go away in the future.
- L755 _public member_ `TWeakObjectPtr<const AActor> Querier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L758 _public member_ `FTransform QueryTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L761 _public member_ `bool bComplexQuery = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L764 _public member_ `bool bFindAnimStartTime = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")`
- L766 _public function_ `FContextualAnimQueryParams()`
- L768 _public function_ `FContextualAnimQueryParams(const AActor* InQuerier, bool bInComplexQuery, bool bInFindAnimStartTime) : Querier(InQuerier), bComplexQuery(bInComplexQuery), bFindAnimStartTime(bInFindAnimStartTime)`
- L771 _public function_ `FContextualAnimQueryParams(const FTransform& InQueryTransform, bool bInComplexQuery, bool bInFindAnimStartTime) : QueryTransform(InQueryTransform), bComplexQuery(bInComplexQuery), bFindAnimStartTime(bInFindAnimStartTime)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTEXTUALANIMATION_API`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogContextualAnim, Log, All);`
- L29 _namespace_ `namespace UE`
- L31 _namespace_ `namespace ContextualAnim` (scope `UE`)
- L558 _function_ `return Actor ? Data.FindByPredicate([Actor](const FContextualAnimSceneBinding& Item) { return Item.GetActor() == Actor; }) : nullptr;` (scope `FContextualAnimSceneBindings::FindBindingByActor`)
- L568 _function_ `return Role != NAME_None ? Data.FindByPredicate([this, &Role](const FContextualAnimSceneBinding& Item) { return GetAnimTrackFromBinding(Item).Role == Role; }) : nullptr;` (scope `FContextualAnimSceneBindings::FindBindingByRole`)

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimUtilities.h` (Public)


#### class `UContextualAnimUtilities`  
`class UContextualAnimUtilities : public UBlueprintFunctionLibrary`  
_L27-216_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L38 _public prototype_ `static void ExtractLocalSpacePose(const UAnimSequenceBase* Animation, const FBoneContainer& BoneContainer, float Time, bool bExtractRootMotion, FCompactPose& OutPose);` — Helper function to extract local space pose from an animation at a given time. If the supplied animation is a montage it will extract the pose from the first track IMPORTANT: This function expects you to add a MemMark (FMemMark Mark(FMemStack::Get());) at the correct scope if you are using it from outside world's tick
- L45 _public prototype_ `static void ExtractComponentSpacePose(const UAnimSequenceBase* Animation, const FBoneContainer& BoneContainer, float Time, bool bExtractRootMotion, FCSPose<FCompactPose>& OutPose);` — Helper function to extract component space pose from an animation at a given time If the supplied animation is a montage it will extract the pose from the first track IMPORTANT: This function expects you to add a MemMark (FMemMark Mark(FMemStack::Get());) at the correct scope if you are using it from outside world's tick
- L48 _public prototype_ `static FTransform ExtractRootMotionFromAnimation(const UAnimSequenceBase* Animation, float StartTime, float EndTime);` — Extract Root Motion transform from a contiguous position range
- L51 _public prototype_ `static FTransform ExtractRootTransformFromAnimation(const UAnimSequenceBase* Animation, float Time);` — Extract root bone transform at a given time
- L54 _public prototype_ `static void BP_DrawDebugPose(const UObject* WorldContextObject, const UAnimSequenceBase* Animation, float Time, FTransform LocalToWorldTransform, FLinearColor Color, float LifeTime, float Thickness);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Utilities", meta = (WorldContext = "WorldContextObject", DisplayName = "Draw Debug Pose"))`
- L56 _public typedef_ `typedef TFunctionRef<void(const FVector& LineStart, const FVector& LineEnd, const FColor& Color, float LifeTime, float Thickness)> FDrawLineFunction;`
- L57 _public prototype_ `static void DrawPose(const UWorld* World, const UAnimSequenceBase* Animation, float Time, FTransform LocalToWorldTransform, FLinearColor Color, float LifeTime, float Thickness);`
- L58 _public prototype_ `static void DrawPose(FPrimitiveDrawInterface* PDI, const UAnimSequenceBase* Animation, float Time, FTransform LocalToWorldTransform, FLinearColor Color, float Thickness);`
- L59 _public prototype_ `static void DrawPose(const UAnimSequenceBase* Animation, float Time, FTransform LocalToWorldTransform, FLinearColor Color, float LifeTime, float Thickness, FDrawLineFunction DrawFunction);`
- L61 _public prototype_ `static void DrawDebugAnimSet(const UWorld* World, const UContextualAnimSceneAsset& SceneAsset, const FContextualAnimSet& AnimSet, float Time, const FTransform& ToWorldTransform, const FColor& Color, float LifeTime, float Thickness);`
- L63 _public prototype_ `static const FAnimNotifyEvent* FindFirstWarpingWindowForWarpTarget(const UAnimSequenceBase* Animation, FName WarpTargetName);`
- L65 _public prototype_ `static UMeshComponent* TryGetMeshComponentWithSocket(const AActor* Actor, FName SocketName);`
- L67 _public prototype_ `static USkeletalMeshComponent* TryGetSkeletalMeshComponent(const AActor* Actor);`
- L69 _public prototype_ `static UAnimInstance* TryGetAnimInstance(const AActor* Actor);`
- L71 _public prototype_ `static FAnimMontageInstance* TryGetActiveAnimMontageInstance(const AActor* Actor);`
- L73 _public prototype_ `static float GetSyncTimeForWarpSection(const UAnimSequenceBase* Animation, const FName& WarpSectionName);`
- L75 _public prototype_ `static void GetStartAndEndTimeForWarpSection(const UAnimSequenceBase* Animation, const FName& WarpSectionName, float& OutStartTime, float& OutEndTime);`
- L78 _public prototype_ `static FName GetStartAndEndTimeForWarpSection(const UAnimSequenceBase* Animation, int32 DesiredWarpSectionOrdinal, float& OutStartTime, float& OutEndTime);` — Returns the start/end time and warp target name of the Nth distinct warp section found sequentially in the animation's motion warping notifies
- L80 _public prototype_ `static void GenerateAlignmentTrack(const UContextualAnimSceneAsset& SceneAsset, const FContextualAnimSceneBinding& InBinding, const FContextualAnimSceneBindings& InBindings, FContextualAnimAlignmentTrackContainer& Container);`
- L81 _public prototype_ `static void GenerateIKTargetTrack(const UContextualAnimSceneAsset& SceneAsset, const FContextualAnimSceneBinding& InBinding, const FContextualAnimSceneBindings& InBindings, FContextualAnimAlignmentTrackContainer& Container);`
- L84 _public prototype_ `static void DrawSector(FPrimitiveDrawInterface& PDI, const FVector& Origin, const FVector& Direction, float MinDistance, float MaxDistance, float MinAngle, float MaxAngle, const FLinearColor& Color, uint8 DepthPriority, float Thickness, bool bDashedLine);`
- L87 _public prototype_ `static bool BP_CreateContextualAnimSceneBindings(const UContextualAnimSceneAsset* SceneAsset, const TMap<FName, FContextualAnimSceneBindingContext>& Params, FContextualAnimSceneBindings& OutBindings);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Create Contextual Anim Scene Bindings"))`
- L90 _public prototype_ `static bool BP_CreateContextualAnimSceneBindingsForTwoActors(const UContextualAnimSceneAsset* SceneAsset, const FContextualAnimSceneBindingContext& Primary, const FContextualAnimSceneBindingContext& Secondary, FContextualAnimSceneBindings& OutBindings);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Create Contextual Anim Scene Bindings For Two Actors"))`
- L93 _public prototype_ `static void BP_AddContextualAnimationOverrideProvider(UPARAM(Ref)FContextualAnimSceneBindings& InBindings, UPARAM(Ref)TScriptInterface<IContextualAnimOverrideInterface>& OverrideProvider, FContextualAnimSceneBindings& OutBindings);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Asset", meta = (DisplayName = "Add Override Provider to Bindings"))`
- L99 _public prototype_ `static void BP_Montage_GetSectionStartAndEndTime(const UAnimMontage* Montage, int32 SectionIndex, float& OutStartTime, float& OutEndTime);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Utilities", meta = (DisplayName = "GetSectionStartAndEndTime"))`
- L102 _public prototype_ `static float BP_Montage_GetSectionTimeLeftFromPos(const UAnimMontage* Montage, float Position);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Utilities", meta = (DisplayName = "GetSectionTimeLeftFromPos"))`
- L105 _public prototype_ `static float BP_Montage_GetSectionLength(const UAnimMontage* Montage, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Utilities", meta = (DisplayName = "GetSectionLength"))`
- L112 _public prototype_ `static void BP_SceneBindings_CalculateWarpPoints(const FContextualAnimSceneBindings& Bindings, TArray<FContextualAnimWarpPoint>& OutWarpPoints);` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use the version that takes a Section Index")` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Calculate Warp Points For Bindings"))`
- L115 _public prototype_ `static void BP_SceneBindings_CalculateWarpPointsForSectionAtIndex(const FContextualAnimSceneBindings& Bindings, int32 SectionIdx, TArray<FContextualAnimWarpPoint>& OutWarpPoints);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Calculate Warp Points For Bindings"))`
- L119 _public prototype_ `static void BP_SceneBindings_AddOrUpdateWarpTargetsForBindings(const FContextualAnimSceneBindings& Bindings);` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use the version that takes a Section Index")` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Add Or Update Warp Targets For Bindings"))`
- L122 _public prototype_ `static void BP_SceneBindings_AddOrUpdateWarpTargetsForSectionAtIndex(const FContextualAnimSceneBindings& Bindings, int32 SectionIdx);` — `UFUNCTION(BlueprintCallable, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Add Or Update Warp Targets For Bindings"))`
- L125 _public function_ `static const TArray<FContextualAnimSceneBinding>& BP_SceneBindings_GetBindings(const FContextualAnimSceneBindings& Bindings)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Bindings"))`
- L128 _public prototype_ `static const FContextualAnimSceneBinding& BP_SceneBindings_GetBindingByRole(const FContextualAnimSceneBindings& Bindings, FName Role);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Binding By Role"))`
- L131 _public prototype_ `static const FContextualAnimSceneBinding& BP_SceneBindings_GetBindingByActor(const FContextualAnimSceneBindings& Bindings, const AActor* Actor);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Binding By Actor"))`
- L134 _public prototype_ `static const FContextualAnimSceneBinding& BP_SceneBindings_GetPrimaryBinding(const FContextualAnimSceneBindings& Bindings);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Primary Binding"))`
- L137 _public prototype_ `static const UAnimSequenceBase* BP_SceneBinding_GetAnimationFromBinding(const FContextualAnimSceneBindings& Bindings, const FContextualAnimSceneBinding& Binding);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Animation From Binding"))`
- L140 _public prototype_ `static FName BP_SceneBinding_GetRoleFromBinding(const FContextualAnimSceneBindings& Bindings, const FContextualAnimSceneBinding& Binding);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Role From Binding"))`
- L143 _public function_ `static const UContextualAnimSceneAsset* BP_SceneBindings_GetSceneAsset(const FContextualAnimSceneBindings& Bindings)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Scene Asset"))`
- L147 _public prototype_ `static void BP_SceneBindings_GetSectionAndAnimSetIndices(const FContextualAnimSceneBindings& Bindings, int32& SectionIdx, int32& AnimSetIdx);` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use BP_SceneBinding_GetSectionAndAnimSetIndices instead")` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Section And AnimSet Indices"))`
- L151 _public prototype_ `static void BP_SceneBindings_GetSectionAndAnimSetNames(const FContextualAnimSceneBindings& Bindings, FName& SectionName, FName& AnimSetName);` — `UE_DEPRECATED(5.7, "This function is deprecated. Please use BP_SceneBindings_GetSectionAndAnimSetNamesFromBinding instead")` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Section And AnimSet Names"))`
- L154 _public prototype_ `static void BP_SceneBindings_GetSectionAndAnimSetNamesFromBinding(const FContextualAnimSceneBindings& Bindings, const FContextualAnimSceneBinding& Binding, FName& SectionName, FName& AnimSetName);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Section And AnimSet Names From Binding"))`
- L157 _public prototype_ `static FTransform BP_SceneBindings_GetAlignmentTransformForRoleRelativeToOtherRole(const FContextualAnimSceneBindings& Bindings, FName Role, FName RelativeToRole, float Time);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Alignment Transform For Role Relative To Other Role"))`
- L160 _public prototype_ `static FTransform BP_SceneBindings_GetAlignmentTransformForRoleRelativeToWarpPoint(const FContextualAnimSceneBindings& Bindings, FName Role, const FContextualAnimWarpPoint& WarpPoint, float Time);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Alignment Transform For Role Relative To Warp Point"))`
- L163 _public prototype_ `static FTransform BP_SceneBindings_GetAlignmentTransformFromBinding(const FContextualAnimSceneBindings& Bindings, const FContextualAnimSceneBinding& Binding, const FContextualAnimWarpPoint& WarpPoint);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Bindings", meta = (DisplayName = "Get Alignment Transform From Binding"))`
- L169 _public function_ `static FContextualAnimSceneBindingContext BP_SceneBindingContext_MakeFromActor(AActor* Actor)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (NativeMakeFunc, DisplayName = "Make Contextual Anim Scene Binding Context"))`
- L172 _public function_ `static FContextualAnimSceneBindingContext BP_SceneBindingContext_MakeFromActorWithExternalTransform(AActor* Actor, FTransform ExternalTransform)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Make Contextual Anim Scene Binding Context With External Transform"))`
- L175 _public function_ `static AActor* BP_SceneBindingContext_GetActor(const FContextualAnimSceneBindingContext& BindingContext)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Get Actor"))`
- L178 _public function_ `static FTransform BP_SceneBindingContext_GetTransform(const FContextualAnimSceneBindingContext& BindingContext)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Get Transform"))`
- L181 _public function_ `static FVector BP_SceneBindingContext_GetVelocity(const FContextualAnimSceneBindingContext& BindingContext)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Get Velocity"))`
- L184 _public function_ `static const FGameplayTagContainer& BP_SceneBindingContext_GetGameplayTags(const FContextualAnimSceneBindingContext& BindingContext)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Get GameplayTags"))`
- L187 _public function_ `static bool BP_SceneBindingContext_HasMatchingGameplayTag(const FContextualAnimSceneBindingContext& BindingContext, const FGameplayTag& TagToCheck)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Has Matching GameplayTag"))`
- L190 _public function_ `static bool BP_SceneBindingContext_HasAllMatchingGameplayTags(const FContextualAnimSceneBindingContext& BindingContext, const FGameplayTagContainer& TagContainer)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Has All Matching GameplayTags"))`
- L193 _public function_ `static bool BP_SceneBindingContext_HasAnyMatchingGameplayTags(const FContextualAnimSceneBindingContext& BindingContext, const FGameplayTagContainer& TagContainer)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Has Any Matching GameplayTags"))`
- L196 _public prototype_ `static void BP_SceneBindingContext_GetCurrentSectionAndAnimSetNames(const FContextualAnimSceneBindingContext& BindingContext, FName& SectionName, FName& AnimSetName);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding Context", meta = (DisplayName = "Get Current Section and Anim Set"))`
- L203 _public function_ `static AActor* BP_SceneBinding_GetActor(const FContextualAnimSceneBinding& Binding)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding", meta = (DisplayName = "Get Actor"))`
- L206 _public function_ `static USkeletalMeshComponent* BP_SceneBinding_GetSkeletalMesh(const FContextualAnimSceneBinding& Binding)` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding", meta = (DisplayName = "Get Skeletal Mesh"))`
- L209 _public prototype_ `static void BP_SceneBinding_GetSectionAndAnimSetIndices(const FContextualAnimSceneBinding& Binding, int32& SectionIdx, int32& AnimSetIdx);` — `UFUNCTION(BlueprintPure, Category = "Contextual Anim|Scene Binding", meta = (DisplayName = "Get Section And AnimSet Indices"))`
- L211 _public prototype_ `static void ExtractPoseIgnoringForceRootLock(UAnimSequenceBase* AnimSequenceBase, const FBoneContainer& BoneContainer, float Time, bool bExtractRootMotion, FCSPose<FCompactPose>& OutPose);`
- L212 _public prototype_ `static FCompactPoseBoneIndex GetCompactPoseBoneIndexFromPose(const FCSPose<FCompactPose>& Pose, const FName& BoneName);`
- L214 _public prototype_ `static void GenerateAlignmentTracksForBindings(UContextualAnimSceneAsset& SceneAsset, FContextualAnimSceneBindings& InBindings);`
- L215 _public prototype_ `static void GenerateAlignmentTrackForBinding(UContextualAnimSceneAsset& SceneAsset, const FName& Role, FContextualAnimSceneBinding& Binding);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CONTEXTUALANIMATION_API`

### `Plugins/Experimental/Animation/ContextualAnimation/Source/ContextualAnimation/Public/ContextualAnimation.h` (Public)


#### class `FContextualAnimationModule`  
`class FContextualAnimationModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
