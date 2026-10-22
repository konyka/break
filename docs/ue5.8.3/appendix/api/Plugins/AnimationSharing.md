# Plugins / AnimationSharing

- module root: `Plugins/Developer/AnimationSharing/Source/AnimationSharing`
- headers: 7; symbols: 324
- symbol kinds: class=8, delegate=5, enum=1, enumerator=1, function=27, macro=7, member=159, prototype=99, struct=15, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, SignificanceManager, TargetPlatform

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AdditiveAnimationInstance.h` (Public)


#### struct `FAdditiveAnimationInstance`  
`struct FAdditiveAnimationInstance`  
_L14-34_
- L17 _public prototype_ `FAdditiveAnimationInstance();`
- L19 _public prototype_ `void Initialise(USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InAnimationBP);`
- L20 _public prototype_ `void Setup(USkeletalMeshComponent* InBaseComponent, UAnimSequence* InAnimSequence);`
- L21 _public prototype_ `void UpdateBaseComponent(USkeletalMeshComponent* InBaseComponent);`
- L22 _public prototype_ `void Stop();`
- L23 _public prototype_ `void Start();`
- L25 _public prototype_ `USkeletalMeshComponent* GetComponent() const;`
- L26 _public prototype_ `USkeletalMeshComponent* GetBaseComponent() const;`
- L29 _protected member_ `USkeletalMeshComponent * SkeletalMeshComponent;`
- L30 _protected member_ `UAnimSharingAdditiveInstance* AdditiveInstance;`
- L31 _protected member_ `UAnimSequence* AdditiveAnimationSequence;`
- L32 _protected member_ `USkeletalMeshComponent* BaseComponent;`
- L33 _protected member_ `bool bLoopingState;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API ANIMATIONSHARING_API`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingInstances.h` (Public)


#### class `UAnimSharingStateInstance`  
`class UAnimSharingStateInstance : public UAnimInstance`  
_L13-41_
- reflection: `UCLASS(MinimalAPI, transient, Blueprintable)`
- inherits: `UAnimInstance`
- L21 _protected member_ `TObjectPtr<UAnimSequence> AnimationToPlay;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = AnimationSharing)`
- L24 _protected member_ `float PermutationTimeOffset;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = AnimationSharing)`
- L27 _protected member_ `float PlayRate;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = AnimationSharing)`
- L30 _protected member_ `bool bStateBool;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = AnimationSharing)`
- L33 _protected prototype_ `void GetInstancedActors(TArray<class AActor*>& Actors);` — `UFUNCTION(BlueprintCallable, Category = AnimationSharing)`
- L36 _private member_ `uint8 StateIndex;`
- L37 _private member_ `uint8 ComponentIndex;`
- L40 _private member_ `TObjectPtr<class UAnimSharingInstance> Instance;` — `UPROPERTY(Transient)`

#### class `UAnimSharingTransitionInstance`  
`class UAnimSharingTransitionInstance : public UAnimInstance`  
_L44-61_
- reflection: `UCLASS(transient, Blueprintable)`
- inherits: `UAnimInstance`
- L51 _protected member_ `TWeakObjectPtr<USkeletalMeshComponent> FromComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Transition)`
- L54 _protected member_ `TWeakObjectPtr<USkeletalMeshComponent> ToComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Transition)`
- L57 _protected member_ `float BlendTime;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Transition)`
- L60 _protected member_ `bool bBlendBool;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Transition)`

#### class `UAnimSharingAdditiveInstance`  
`class UAnimSharingAdditiveInstance : public UAnimInstance`  
_L65-82_
- reflection: `UCLASS(transient, Blueprintable)`
- inherits: `UAnimInstance`
- L72 _protected member_ `TWeakObjectPtr<USkeletalMeshComponent> BaseComponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Additive)`
- L75 _protected member_ `TWeakObjectPtr<UAnimSequence> AdditiveAnimation;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Additive)`
- L78 _protected member_ `float Alpha;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Additive)`
- L81 _protected member_ `bool bStateBool;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Transient, Category = Additive)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONSHARING_API`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingManager.h` (Public)


#### struct `FBlendInstance`  
`struct FBlendInstance`  
_L30-60_
- desc: Structure which holds data about a currently in progress blend between two states
- L33 _public member_ `bool bActive;` — Flag whether or not this instance is currently active
- L35 _public member_ `bool bBlendStarted;` — Flag whether or not the actor's part of this have been setup as a follower component to the blend actor, this is done so the blend actor atleast ticks once (otherwise it can pop from the previous blend end pose)
- L37 _public member_ `bool bOnDemand;` — Flag whether or not this instance is blending towards an on-demand state
- L39 _public member_ `float EndTime;` — World time in seconds at which the blend has finished (calculated at start of blend world time + blend duration)
- L41 _public member_ `float BlendTime;` — Duration of the blend
- L43 _public member_ `uint8 StateFrom;` — State value to blend from
- L45 _public member_ `uint8 StateTo;` — State value to blend to
- L48 _public member_ `uint32 FromPermutationIndex;` — Permutation indices from and to which we are blending, used to ensure we 'forward' the actor to the correct LeaderPoseComponent when finished blending
- L49 _public member_ `uint32 ToPermutationIndex;`
- L52 _public member_ `FTransitionBlendInstance* TransitionBlendInstance;` — Actor used for blending between the two states
- L54 _public member_ `TArray<uint32> ActorIndices;` — Indices of actors who are set up as followers to BlendActor's main skeletal mesh component
- L57 _public member_ `uint32 FromOnDemandInstanceIndex;` — Optional index into OnDemandInstances from which we are blending
- L59 _public member_ `uint32 ToOnDemandInstanceIndex;` — Optional index into OnDemandInstance to which we are blending

#### struct `FOnDemandInstance`  
`struct FOnDemandInstance`  
_L63-95_
- desc: Structure which holds data about a currently running on-demand state animation instance
- L66 _public member_ `bool bActive;` — Flag whether or not instance is active
- L67 _public member_ `bool bBlendActive;`
- L70 _public member_ `bool bReturnToPreviousState;` — Flag whether or not the component should be 'returned' to the state they were in before the on-demand animation
- L73 _public member_ `uint8 State;` — State value which is active
- L76 _public member_ `uint8 ForwardState;` — State value which the components should be set to when the on-demand animation has finished playing (used when !bReturnToPreviousState)
- L79 _public member_ `float StartTime;` — Time at which this instance was started
- L82 _public member_ `float StartBlendTime;` — Time at which this on demand instance should blend out into the 'next' state the actor is in
- L85 _public member_ `float EndTime;` — World time in seconds at which the animation has finished playing (calculated at start of blend world time + animation sequence length)
- L88 _public member_ `uint32 UsedPerStateComponentIndex;` — Index into Components array for the current state data which is used for playing the animation
- L91 _public member_ `uint32 BlendToPermutationIndex;` — Permutation index that we are blending to before the end of the animation
- L94 _public member_ `TArray<uint32> ActorIndices;` — Indices of actors who are set up as followers to the skeletal mesh component running the animation

#### struct `FAdditiveInstance`  
`struct FAdditiveInstance`  
_L97-119_
- L100 _public member_ `bool bActive;` — Flag whether or not instance is active
- L103 _public member_ `uint8 State;` — State index this instance is running
- L106 _public member_ `float EndTime;` — Time at which this instance finishes
- L109 _public member_ `uint32 ActorIndex;` — Current actor indices as part of this instance
- L112 _public member_ `USkeletalMeshComponent* BaseComponent;` — Skeletal mesh component on which the additive animation is applied
- L115 _public member_ `FAdditiveAnimationInstance* AdditiveAnimationInstance;` — Actor used for playing the additive animation
- L118 _public member_ `uint32 UsedPerStateComponentIndex;` — Index into Components array for the current state data which is used for playing the animation

#### struct `FInstanceStack`  
`template <typename InstanceType> struct FInstanceStack`  
_L122-174_
- L124 _public function_ `~FInstanceStack()`
- L141 _public function_ `bool InstanceAvailable() const` — Return whether instance are available
- L147 _public function_ `InstanceType* GetInstance()` — Get an available instance
- L160 _public function_ `void FreeInstance(InstanceType* Instance)` — Return instance back
- L167 _public function_ `void AddInstance(InstanceType* Instance)` — Add a new instance to the 'stack'
- L172 _public member_ `TArray<InstanceType*> AvailableInstances;`
- L173 _public member_ `TArray<InstanceType*> InUseInstances;`

#### struct `FPerStateData`  
`struct FPerStateData`  
_L177-232_
- desc: Structure which holds data about a unique state which is linked to an enumeration value defined by the user. The data is populated from the user exposed FAnimationStateEntry
- L179 _public function_ `FPerStateData() : bIsOnDemand(false), bIsAdditive(false), bShouldRandomizeOnDemandAnims(false), BlendTime(0.f), CurrentFrameOnDemandIndex(INDEX_NONE), StateEnumValue(INDEX_NONE), AdditiveAnimationSequence(nullptr)`
- L182 _public member_ `bool bIsOnDemand;` — Flag whether or not this state is an on-demand state, this means that we kick off a unique animation when needed
- L185 _public member_ `bool bIsAdditive;` — Flag whether or not this state is an additive state
- L188 _public member_ `bool bReturnToPreviousState;` — Flag whether or not we should return to the previous state, only used when this state is an on-demand one
- L191 _public member_ `bool bShouldForwardToState;` — Flag whether or not ForwardStateValue should be used hwen the animation has finished
- L194 _public member_ `bool bShouldRandomizeOnDemandAnims;` — Flag to allow random selection of OnDemand components so we don't always get only the first avaialable component.
- L197 _public member_ `float BlendTime;` — Duration of blending when blending to this state
- L200 _public member_ `uint32 CurrentFrameOnDemandIndex;` — This is (re-)set every frame, and allows for quickly finding an on-demand instance which was setup this frame
- L203 _public member_ `float WiggleTime;` — Number of 'wiggle' frames, this is used when we run out of available entries in Components, if one of the FOnDemandInstance has started NumWiggleFrames ago or earlier, it is used instead of a brand new one
- L206 _public member_ `uint8 ForwardStateValue;` — State value to which the actors part of an FOnDemandInstance should be set to when its animation has finished
- L208 _public member_ `uint8 StateEnumValue;` — Enum value linked to this state
- L211 _public member_ `UAnimSequence* AdditiveAnimationSequence;` — Animation Sequence that is used for Additive States
- L214 _public member_ `TArray<USkeletalMeshComponent*> Components;` — Components setup to play animations for this state
- L216 _public member_ `TBitArray<> InUseComponentFrameBits;` — Bits keeping track which of the components are in-use, in case of On Demand state this is managed by FOnDemandInstance, otherwise we clear and populate the flags each frame
- L217 _public member_ `TBitArray<> PreviousInUseComponentFrameBits;`
- L220 _public member_ `TBitArray<> FollowerTickRequiredFrameBits;` — Bits keeping track whether or not any of the follower components requires the leader component to tick
- L224 _public member_ `TBitArray<> SlaveTickRequiredFrameBits;` — `UE_DEPRECATED(5.1, "This member has been deprecated. Please use FollowerTickRequiredFrameBits")`
- L228 _public member_ `TArray<float> AnimationLengths;` — Length of the animations used for an on-demand state, array as it could contain different animation permutations
- L231 _public member_ `FInstanceStack<FAdditiveAnimationInstance> AdditiveInstanceStack;` — Additive actors data structure

#### struct `FPerComponentData`  
`struct FPerComponentData`  
_L234-240_
- L237 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakComponent;` — Skeletal mesh component registered for this component
- L239 _public member_ `int32 ActorIndex;` — Index to the owning actor (used to index PerActorData)

#### struct `FPerActorData`  
`struct FPerActorData`  
_L242-277_
- L245 _public member_ `uint8 CurrentState;` — Current state value (used to index PerStateData)
- L247 _public member_ `uint8 PreviousState;` — Previous state value (used to index PerStateData)
- L249 _public member_ `uint8 PermutationIndex;` — Permutation index (used to index Components array inside of PerStateData)
- L252 _public member_ `bool bBlending;` — Flag whether or not we are currently blending
- L254 _public member_ `bool bRunningOnDemand;` — Flag whether or not we are currently part of an on-demand animation state
- L257 _public member_ `bool bRunningAdditive;` — Flag whether or not we are currently part of an additive animation state
- L260 _public member_ `float SignificanceValue;` — Cached significance value
- L263 _public member_ `bool bRequiresTick;` — Flag whether or not this actor requires the leader component to tick
- L266 _public member_ `uint32 BlendInstanceIndex;` — Index to blend instance which is currently driving this actor's animation
- L268 _public member_ `uint32 OnDemandInstanceIndex;` — Index to on demand instance which is running accord to our current state (or previous state)
- L270 _public member_ `uint32 AdditiveInstanceIndex;` — Index to additive instance which is running on top of our state
- L273 _public member_ `TArray<uint32> ComponentIndices;` — Indices of the Components owned by this actor (used to index into PerComponentData)
- L276 _public member_ `FUpdateActorHandle UpdateActorHandleDelegate;` — Register delegate called when actor is swapped and the handle should be updated

#### class `UAnimSharingInstance`  
`class UAnimSharingInstance : public UObject`  
_L280-481_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L286 _public prototype_ `virtual void BeginDestroy() override;`
- L290 _public prototype_ `void UnregisterAllActors();` — unregister all actors associated with this sharing instance
- L293 _public prototype_ `uint8 DetermineStateForActor(uint32 ActorIndex, bool& bShouldProcess);` — This uses the StateProcessor to determine the state index the actor is currently in
- L296 _public prototype_ `bool Setup(UAnimationSharingManager* AnimationSharingManager, const FPerSkeletonAnimationSharingSetup& SkeletonSetup, const FAnimationSharingScalability* InScalabilitySettings, uint32 InSkeletonID);` — Initial set up of all animation sharing data and states
- L299 _public prototype_ `void SetupState(FPerStateData& StateData, const FAnimationStateEntry& StateEntry, USkeletalMesh* SkeletalMesh, const FPerSkeletonAnimationSharingSetup& SkeletonSetup, uint32 InSkeletonID);` — Populates data for a state setup
- L303 _public prototype_ `uint32 SetupBlend(uint8 FromState, uint8 ToState, uint32 ActorIndex);` — Retrieves a blend instance, this could either mean reusing an already in progress one or a brand new one (if available according to scalability settings) returns whether or not the setup was successful
- L306 _public prototype_ `uint32 SetupBlendFromOnDemand(uint8 ToState, uint32 OnDemandInstanceIndex, uint32 ActorIndex);` — Retrieves a blend instance, and sets up a blend from a currently running On-Demand instance to ToState
- L309 _public prototype_ `uint32 SetupBlendBetweenOnDemands(uint8 FromOnDemandInstanceIndex, uint32 ToOnDemandInstanceIndex, uint32 ActorIndex);` — Retrieves a blend instance, and sets up a blend between a currently running On-Demand instance and another one which was started this frame
- L312 _public prototype_ `uint32 SetupBlendToOnDemand(uint8 FromState, uint32 ToOnDemandInstanceIndex, uint32 ActorIndex);` — Retrieves a blend instance, and setups up a blend to an On-Demand instance from a regular animation state
- L315 _public prototype_ `void SwitchBetweenOnDemands(uint32 FromOnDemandInstanceIndex, uint32 ToOnDemandInstanceIndex, uint32 ActorIndex);` — Switches between on-demand instances directly, without blending
- L319 _public prototype_ `uint32 SetupOnDemandInstance(uint8 StateIndex);` — Retrieves a blend instance, this could either mean reusing an already in progress one or a brand new one (if available according to scalability settings) returns an index into OnDemandInstances array or INDEX_NONE if unable to setup an instance
- L323 _public function_ `uint32 SetupAdditiveInstance(uint8 StateIndex, uint8 FromState, uint8 StateComponentIndex)` — `UE_DEPRECATED(5.8, "SetupAdditiveInstance with state and component index has been deprecated as it causes invalid behaviour, use new signature instead")` — Retrieves an additive instance, these are unique and cannot be reused
- L324 _public prototype_ `uint32 SetupAdditiveInstance(uint8 StateIndex, USkeletalMeshComponent* InBaseComponent);`
- L327 _public prototype_ `float CalculateBlendTime(uint8 StateIndex) const;` — Retrieves the blend-time for this specific state
- L330 _public prototype_ `void KickoffInstances();` — Kicks off the blend and on-demand instances at the end of the current frame tick, this sets up the blend instance with the correct components to blend between
- L333 _public prototype_ `void TickBlendInstances();` — Ticks all currently running blend instances, checks whether or not the blend is finished and forwards the actor/components to the correct animation state
- L336 _public prototype_ `void TickOnDemandInstances();` — Ticks all currently running on-demand instances, this checks whether or not the animation has finished or if we have to start blending out of the state already
- L339 _public function_ `template <typename InstanceType> bool DoAnyActorsRequireTicking(const InstanceType& Instance)`
- L355 _public prototype_ `void TickAdditiveInstances();` — Ticks all currently running additive animation instances, this checks whether or not it has finished yet and sets the base-component as the leader component when it has
- L358 _public prototype_ `void TickActorStates();` — Ticks all Actor Data entries and determines their current state, if changed since last tick it will alter their animation accordingly
- L361 _public prototype_ `void TickDebugInformation();` — Ticks various types of debugging data / drawing (not active in shipping build)
- L364 _public prototype_ `void TickAnimationStates();` — Ticks all unique animation states, this checks which components are currently used and turns of those which currently don't have any followerss
- L367 _public prototype_ `void RemoveBlendInstance(int32 InstanceIndex);` — Removal functions which also make sure that indices of other data-structres are correctly remapped
- L368 _public prototype_ `void RemoveOnDemandInstance(int32 InstanceIndex);`
- L369 _public prototype_ `void RemoveAdditiveInstance(int32 InstanceIndex);`
- L370 _public prototype_ `void RemoveComponent(int32 ComponentIndex);`
- L373 _public prototype_ `void RemoveFromCurrentBlend(int32 ActorIndex);` — Removal functions which also make sure the actor is set to the correct leader pose component
- L374 _public prototype_ `void RemoveFromCurrentOnDemand(int32 ActorIndex);`
- L377 _public prototype_ `void FreeBlendInstance(FTransitionBlendInstance* Instance);` — Frees up a Blend instance and resets its state
- L380 _public prototype_ `void FreeAdditiveInstance(uint8 StateIndex, FAdditiveAnimationInstance* Instance);` — Frees up an Additive Animation instance and resets it state
- L383 _public prototype_ `void SetLeaderComponentForActor(uint32 ActorIndex, USkeletalMeshComponent* Component);` — Sets up all components of an actor to be followers of Component
- L386 _public function_ `void SetMasterComponentForActor(uint32 ActorIndex, USkeletalMeshComponent* Component)` — `UE_DEPRECATED(5.1, "This function has been deprecated. Please use SetLeaderComponentForActor instead.")`
- L389 _public prototype_ `void SetupFollowerComponent(uint8 CurrentState, uint32 ActorIndex);` — Sets up the correct LeaderPoseComponent for the passed in Component and State indices
- L392 _public function_ `void SetupSlaveComponent(uint8 CurrentState, uint32 ActorIndex)` — `UE_DEPRECATED(5.1, "This function has been deprecated. Please use SetupFollowerComponent instead.")`
- L395 _public prototype_ `void SetPermutationFollowerComponent(uint8 StateIndex, uint32 ActorIndex, uint32 PermutationIndex);` — Sets up the correct LeaderPoseComponent according to the state and permutation indices
- L398 _public function_ `void SetPermutationSlaveComponent(uint8 StateIndex, uint32 ActorIndex, uint32 PermutationIndex)` — `UE_DEPRECATED(5.1, "This function has been deprecated. Please use SetPermutationFollowerComponent instead.")`
- L401 _public prototype_ `virtual uint32 DeterminePermutationIndex(uint32 ActorIndex, uint8 State) const;` — Determines a permutation index for the given actor and state
- L404 _public prototype_ `void SetComponentUsage(bool bUsage, uint8 StateIndex, uint32 ComponentIndex);` — Marks the component as either used/not-used, this is used to disable ticking of components which are not in use
- L407 _public prototype_ `void SetComponentTick(uint8 StateIndex, uint32 ComponentIndex);` — Sets the whether or not any of the follower components are visible
- L410 _public prototype_ `USkeletalMeshComponent* GetComponent(const FPerComponentData& ComponentData);` — Retrieves USkeletalMeshComponent with validation of reachability
- L414 _public member_ `TArray<TObjectPtr<AActor>> RegisteredActors;` — `UPROPERTY(VisibleAnywhere, Transient, Category = AnimationSharing)` — Actors currently registered to be animation driven by the AnimManager using this setup
- L417 _public member_ `TArray<FPerActorData> PerActorData;` — Per actor data, matches RegisteredActors
- L419 _public member_ `TArray<FPerComponentData> PerComponentData;` — Per component state data indexed from FPerActorData.ComponentIndices
- L422 _public member_ `TArray<FPerStateData> PerStateData;` — Array of unique state data
- L425 _public member_ `FInstanceStack<FTransitionBlendInstance> BlendInstanceStack;` — Blend actors data structure
- L429 _public member_ `TObjectPtr<UAnimationSharingStateProcessor> StateProcessor;` — `UPROPERTY(EditAnywhere, Transient, Category = AnimationSharing)` — (Blueprint)class instance used for determining the state enum value for each registered actor
- L430 _public member_ `bool bNativeStateProcessor;`
- L433 _public member_ `TWeakObjectPtr<const UAnimationSharingSetup> OwnerSetup;` — weak ptr back to the setup that owns this instance
- L436 _public member_ `uint32 SkeletonID;` — id for skeleton associated with this instance that remains even when setups are removed and added.
- L439 _public member_ `TArray<FBlendInstance> BlendInstances;` — Currently running blend instances
- L441 _public member_ `TArray<FOnDemandInstance> OnDemandInstances;` — Currently running on-demand instance
- L443 _public member_ `TArray<FAdditiveInstance> AdditiveInstances;` — Currently running additive instances
- L446 _public member_ `TArray<TObjectPtr<UAnimSequence>> UsedAnimationSequences;` — `UPROPERTY(VisibleAnywhere, Transient, Category = AnimationSharing)`
- L449 _public member_ `USignificanceManager* SignificanceManager;` — Significance manager used to retrieve AI actor significance values
- L452 _public member_ `UAnimationSharingManager* AnimSharingManager;` — Animation sharing manager for the current world
- L456 _public member_ `TObjectPtr<UEnum> StateEnum;` — `UPROPERTY(VisibleAnywhere, Transient, Category = AnimationSharing)` — Enum class set up by the user to 'describe' the animation states
- L460 _public member_ `TObjectPtr<AActor> SharingActor;` — `UPROPERTY(VisibleAnywhere, Transient, Category = AnimationSharing)` — Actor to which all the running SkeletalMeshComponents used for the sharing are attached to
- L463 _public member_ `FAnimationSharingScalability ScalabilitySettings;` — Platform specific scalability settings for this instance
- L466 _public member_ `FVector SkeletalMeshBounds;` — Bounds for the currently used skeletal mesh
- L469 _public member_ `uint32 NumSetups;` — Number of animation setups
- L472 _public member_ `float WorldTime;` — Holds the current frame world time
- L477 _private prototype_ `void GetAnimAssetNameAndData(const uint32 StateIdx, const uint32 CompIdx, FString& AnimAssetName, float& AnimTime, float& AnimLength) const;`
- L478 _private prototype_ `FString GetDebugStateString(uint8 State, const uint32 CompIdx, uint32 OnDemandInstanceIndex) const;`

#### struct `FTickAnimationSharingFunction`  
`struct FTickAnimationSharingFunction : public FTickFunction`  
_L484-497_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- L488 _public function_ `FTickAnimationSharingFunction() : Manager(nullptr)`
- L491 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L492 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L493 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`
- L496 _public member_ `class UAnimationSharingManager* Manager;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTickAnimationSharingFunction> : public TStructOpsTypeTraitsBase2<FTickAnimationSharingFunction>`  
_L501-507_
- inherits: `TStructOpsTypeTraitsBase2<FTickAnimationSharingFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L504-506_

#### class `UAnimationSharingManager`  
`class UAnimationSharingManager : public UObject`  
_L510-641_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- L516 _public prototype_ `virtual void BeginDestroy() override;`
- L517 _public prototype_ `virtual UWorld* GetWorld()const override;`
- L522 _public prototype_ `static UAnimationSharingManager* GetAnimationSharingManager(UObject* WorldContextObject);` — `UFUNCTION(BlueprintCallable, Category = AnimationSharing, meta = (WorldContext = "WorldContextObject"))` — Returns the AnimationSharing Manager, nullptr if none was set up
- L526 _public prototype_ `static bool CreateAnimationSharingManager(UObject* WorldContextObject, const UAnimationSharingSetup* Setup);` — `UFUNCTION(BlueprintCallable, Category = AnimationSharing, meta = (WorldContext = "WorldContextObject"))` — Create an Animation Sharing Manager using the provided Setup
- L530 _public prototype_ `bool RegisterActorWithSkeletonBP(AActor* InActor, const USkeleton* SharingSkeleton);` — `UFUNCTION(BlueprintCallable, Category = AnimationSharing, meta = (DisplayName = "Register Actor"))` — Register an Actor with this Animation Sharing manager, according to the SharingSkeleton
- L534 _public prototype_ `static bool AnimationSharingEnabled();` — `UFUNCTION(BlueprintPure, Category = AnimationSharing)` — Returns whether or not the animation sharing is enabled
- L537 _public prototype_ `static UAnimationSharingManager* GetManagerForWorld(UWorld* InWorld);` — Returns the AnimationSharing Manager for a specific UWorld, nullptr if none was set up
- L540 _public prototype_ `bool RegisterActor(AActor* InActor, FUpdateActorHandle Delegate);` — Registers actor with the animation sharing system
- L543 _public prototype_ `bool RegisterActorWithSkeleton(AActor* InActor, const USkeleton* SharingSkeleton, FUpdateActorHandle Delegate);` — Registers actor with the animation sharing system according to the SharingSkeleton's sharing setup (if available)
- L546 _public prototype_ `bool UnregisterActor(AActor* InActor);` — Unregisters actor with the animation sharing system
- L549 _public prototype_ `void UpdateSignificanceForActorHandle(uint32 InHandle, float InValue);` — Update cached significance for registered actor
- L552 _public prototype_ `void ClearActorData();` — Ensures all actor data is cleared
- L555 _public prototype_ `void UnregisterAllActors();` — Ensures all currently registered actors are removed
- L558 _public prototype_ `void SetLeaderComponentsVisibility(bool bVisible);` — Sets the visibility of currently used Leader Pose Components
- L561 _public function_ `void SetMasterComponentsVisibility(bool bVisible)` — `UE_DEPRECATED(5.1, "This member has been deprecated. Please use SetLeaderComponentsVisibility")`
- L564 _public prototype_ `void Initialise(const UAnimationSharingSetup* InSetup);` — Initialize sharing data structures
- L567 _public prototype_ `void AddSetup(const UAnimationSharingSetup* InSetup);` — Add an animation sharing setup to the manager
- L570 _public prototype_ `void RemoveSetup(const UAnimationSharingSetup* InSetup);` — Remove an animation sharing setup from the manager
- L573 _public prototype_ `const FAnimationSharingScalability& GetScalabilitySettings(const UAnimationSharingSetup* InSetup = nullptr) const;` — Returns current scalability settings, with optional setup parameter to return scalability settings specific to an animation sharing setup
- L575 _public prototype_ `void Tick(float DeltaTime);`
- L576 _public prototype_ `FTickAnimationSharingFunction& GetTickFunction();`
- L579 _public prototype_ `bool CheckDataForActor(AActor* InActor) const;` — Checks whether the supplied actor is registered and all its data is valid
- L582 _public prototype_ `void LogData() const;` — Log out internal data
- L584 _public function_ `static uint32 GetInvalidActorHandle()`
- L590 _protected prototype_ `void SetupPerSkeletonData(const FPerSkeletonAnimationSharingSetup& SkeletonSetup);` — `UE_DEPRECATED(5.7, "Replaced by SetupPerSkeletonData version below with extra parameters.")` — Populates all data required for a Skeleton setup
- L591 _protected prototype_ `void SetupPerSkeletonData(const FPerSkeletonAnimationSharingSetup& SkeletonSetup, const UAnimationSharingSetup* SharingSetup, const FAnimationSharingScalability& ScalabilitySettingsForSkeleton);`
- L593 _protected prototype_ `virtual UAnimSharingInstance* CreateAnimSharingInstance();`
- L596 _protected prototype_ `uint32 CreateActorHandle(uint8 SkeletonID, uint32 ActorIndex) const;` — Dealing with Actor data and handles
- L597 _protected prototype_ `uint8 GetSkeletonIndexFromHandle(uint32 InHandle) const;`
- L598 _protected prototype_ `uint32 GetActorIndexFromHandle(uint32 InHandle) const;`
- L599 _protected prototype_ `FPerActorData* GetActorDataByHandle(uint32 InHandle);`
- L605 _protected member_ `TArray<TObjectPtr<const USkeleton>> Skeletons;` — `UPROPERTY(Transient)` — Array of unique skeletons, matches PerSkeletonData array entries
- L609 _protected member_ `TArray<TObjectPtr<UAnimSharingInstance>> PerSkeletonData;` — `UPROPERTY(VisibleAnywhere, Transient, Category = AnimationSharing)` — Sharing data required for the unique Skeleton setups
- L612 _protected member_ `TMap< uint8, uint8 > SkeletonIDToSkeletonIndexMap;` — map from skeleton id to skeleton index to speed up accesssing from actor handles
- L615 _protected member_ `static const uint32 MaxSkeletonID = 0xFF;` — Max skeleton id matches the range supported in actor handles
- L616 _protected member_ `static const uint32 MaxSkeletonIndex = 0xFF;`
- L617 _protected member_ `static const uint32 InvalidActorHandle = INDEX_NONE;`
- L620 _protected member_ `uint32 NextSkeletonID = 0;` — Skeleton ID for next added skeleton setup
- L623 _protected member_ `TArray< TWeakObjectPtr<const UAnimationSharingSetup> > AnimationSharingSetups;` — Pointers to animation sharing setups added to manager
- L626 _protected member_ `FAnimationSharingScalability ScalabilitySettings;` — Platform specific scalability settings (default version, setting from a setup will generally be used instead)
- L629 _protected member_ `FTickAnimationSharingFunction TickFunction;` — Tick function for this manager
- L633 _public member_ `static TArray<TObjectPtr<UMaterialInterface>> DebugMaterials;`
- L635 _public prototype_ `static void SetDebugMaterial(USkeletalMeshComponent* Component, uint8 State);`
- L636 _public prototype_ `static void SetDebugMaterialForActor(UAnimSharingInstance* Data, uint32 ActorIndex, uint8 State);`
- L639 _public prototype_ `static FName GetPlatformName();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMATIONSHARING_API`
- L19 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationSharing, Log, All);`
- L19 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationSharing, Log, All);`
- L20 _delegate_ `DECLARE_STATS_GROUP(TEXT("Animation Sharing Manager"), STATGROUP_AnimationSh`
- L22 _macro_ `#define DEBUG_MATERIALS (UE_EDITOR && !UE_BUILD_SHIPPING)`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FUpdateActorHandle, int32);`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FUpdateActorHandle, int32);`
- L27 _typedef_ `typedef uint32 AnimationSharingDataHandle;`
- L505 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon5eb7ac7d0103`)

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingModule.h` (Public)


#### class `FAnimSharingModule`  
`class FAnimSharingModule : public FDefaultModuleImpl, public FGCObject`  
_L16-60_
- inherits: `FDefaultModuleImpl,FGCObject`
- L20 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L25 _public function_ `virtual FString GetReferencerName() const override`
- L31 _public function_ `FORCEINLINE static UAnimationSharingManager* Get(const UWorld* World)`
- L36 _public function_ `FORCEINLINE static FOnAnimationSharingManagerCreated& GetOnAnimationSharingManagerCreated()`
- L41 _public function_ `FORCEINLINE static FOnAnimationSharingManagerSetupAdded& GetOnAnimationSharingManagerSetupAdded()`
- L47 _public prototype_ `static bool CreateAnimationSharingManager(UWorld* InWorld, const UAnimationSharingSetup* Setup);` — Creates an animation sharing manager for the given UWorld (must be a Game World)
- L51 _public typedef_ `using FCreateAnimationSharingManagerFunc = TFunction<UAnimationSharingManager*(UWorld* InWorld)>;` — Creates an animation sharing manager for the given UWorld (must be a Game World) - with custom func that is responsible for creation and initialisation
- L52 _public prototype_ `static bool CreateAnimationSharingManager(UWorld* InWorld, FCreateAnimationSharingManagerFunc CreateAnimationSharingManagerFunc);`
- L55 _private prototype_ `static void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L56 _private member_ `static TMap<const UWorld*, TObjectPtr<UAnimationSharingManager>> WorldAnimSharingManagers;`
- L58 _private member_ `static FOnAnimationSharingManagerCreated OnAnimationSharingManagerCreated;`
- L59 _private member_ `static FOnAnimationSharingManagerSetupAdded OnAnimationSharingManagerSetupAdded;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ANIMATIONSHARING_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimationSharingManagerCreated, UAnimationSharingManager*, const UWorld*);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimationSharingManagerCreated, UAnimationSharingManager*, const UWorld*);`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimationSharingManagerSetupAdded, UAnimationSharingManager*, const UWorld*);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAnimationSharingManagerSetupAdded, UAnimationSharingManager*, const UWorld*);`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingSetup.h` (Public)


#### class `UAnimationSharingSetup`  
`class UAnimationSharingSetup : public UObject`  
_L13-23_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object, Blueprintable, config = Engine)`
- inherits: `UObject`
- desc: The Animation Sharing Setup asset contains all the information that will be shared across the specified Actors
- L19 _public member_ `TArray<FPerSkeletonAnimationSharingSetup> SkeletonSetups;` — `UPROPERTY(EditAnywhere, config, Category = AnimationSharing)`
- L22 _public member_ `FAnimationSharingScalability ScalabilitySettings;` — `UPROPERTY(EditAnywhere, config, Category = AnimationSharing)`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/AnimationSharingTypes.h` (Public)


#### struct `FAnimationSetup`  
`struct FAnimationSetup`  
_L20-41_
- reflection: `USTRUCT()`
- L24 _public function_ `FAnimationSetup() : AnimSequence(nullptr), AnimBlueprint(nullptr), NumRandomizedInstances(1), Enabled(true)`
- L28 _public member_ `TObjectPtr<UAnimSequence> AnimSequence;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Animation Sequence to play for this particular setup
- L32 _public member_ `TSubclassOf<UAnimSharingStateInstance> AnimBlueprint;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = AnimationSharing)` — Animation blueprint to use for playing back the Animation Sequence
- L36 _public member_ `FPerPlatformInt NumRandomizedInstances;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (ClampMin = "1", UIMin = "1"))` — The number of randomized instances created from this setup, it will create instance with different start time offsets (Length / Number of Instance) * InstanceIndex
- L40 _public member_ `FPerPlatformBool Enabled;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Whether or not this setup is enabled for specific platforms

#### struct `FAnimationStateEntry`  
`struct FAnimationStateEntry`  
_L44-97_
- reflection: `USTRUCT()`
- L48 _public function_ `FAnimationStateEntry() : State(0), bOnDemand(false), bRandomizeOnDemandAnims(false), bAdditive(false), BlendTime(0.f), bReturnToPreviousState(false), bSetNextState(false), NextState(0), MaximumNumberOfConcurrentInstances(1), WiggleTimePercentage(0.1f), bRequiresCurves(false)`
- L52 _public member_ `uint8 State;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Enum value linked to this state
- L56 _public member_ `TArray<FAnimationSetup> AnimationSetups;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Per state animation setup
- L60 _public member_ `bool bOnDemand;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Flag whether or not this state is an on-demand state, this means that we kick off a unique animation when needed
- L64 _public member_ `bool bRandomizeOnDemandAnims;` — `UPROPERTY(EditAnywhere, Category = AnimSharing, meta = (EditCondition = "bOnDemand"))` — Flag that determines whether or not we attempt to randomize the selection of OnDemand animations, if the total number of components for the OnDemand state is more than 1.
- L68 _public member_ `bool bAdditive;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "bOnDemand"))` — Whether or not this state is an additive state
- L72 _public member_ `float BlendTime;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "!bAdditive", UIMin = "0.0", ClampMin = "0.0"))` — Duration of blending when blending to this state
- L76 _public member_ `bool bReturnToPreviousState;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "bOnDemand"))` — Flag whether or not we should return to the previous state, only used when this state is an on-demand one
- L79 _public member_ `bool bSetNextState;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "bOnDemand"))`
- L83 _public member_ `uint8 NextState;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "bSetNextState"))` — State value to which the actors part of an on demand state should be set to when its animation has finished
- L87 _public member_ `FPerPlatformInt MaximumNumberOfConcurrentInstances;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta=(EditCondition="bOnDemand", ClampMin = "0", UIMin = "0"))` — Number of instances that will be created for this state (platform-specific)
- L92 _public member_ `float WiggleTimePercentage;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (EditCondition = "bOnDemand", UIMin="0.0", UIMax="1.0", ClampMin = "0.0", ClampMax = "1.0"))` — Percentage of 'wiggle' frames, this is used when we run out of available entries in Components, if one of the on-demand animations has started SequenceLength * WiggleFramePercentage ago or earlier, it is used instead of a brand new one
- L96 _public member_ `bool bRequiresCurves;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = AnimationSharing)` — Whether or not this animation requires curves or morphtargets to function correctly for follower components

#### class `UAnimationSharingStateProcessor`  
`class UAnimationSharingStateProcessor : public UObject`  
_L100-131_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- L105 _public prototype_ `void ProcessActorState(int32& OutState, AActor* InActor, uint8 CurrentState, uint8 OnDemandState, bool& bShouldProcess);` — `UFUNCTION(BlueprintNativeEvent, Category = AnimationSharing)`
- L106 _public function_ `virtual void ProcessActorState_Implementation(int32& OutState, AActor* InActor, uint8 CurrentState, uint8 OnDemandState, bool& bShouldProcess)`
- L112 _public prototype_ `UEnum* GetAnimationStateEnum();` — `UFUNCTION(BlueprintNativeEvent, Category = AnimationSharing)`
- L113 _public function_ `virtual UEnum* GetAnimationStateEnum_Implementation()`
- L118 _public function_ `virtual void ProcessActorStates(TArray<int32>& OutStates, const TArray<AActor*>& InActors, const TArray<uint8>& CurrentStates, const TArray<uint8>& OnDemandStates, TArray<bool>& ShouldProcessFlags)`
- L127 _public member_ `TSoftObjectPtr<UEnum> AnimationStateEnum;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)`
- L129 _protected function_ `virtual UEnum* GetAnimationStateEnum_Internal()`
- L130 _protected function_ `virtual void ProcessActorState_Internal(int32& OutState, AActor* InActor, uint8 CurrentState, uint8 OnDemandState, bool& bShouldProcess)`

#### struct `FPerSkeletonAnimationSharingSetup`  
`struct FPerSkeletonAnimationSharingSetup`  
_L134-167_
- reflection: `USTRUCT()`
- L138 _public function_ `FPerSkeletonAnimationSharingSetup() : Skeleton(nullptr), SkeletalMesh(nullptr), BlendAnimBlueprint(nullptr), AdditiveAnimBlueprint(nullptr), StateProcessorClass(nullptr), bEnableMaterialParameterCaching(false)`
- L142 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Skeleton compatible with the animation sharing setup
- L146 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (DisallowedClasses = "/Script/ApexDestruction.DestructibleMesh"))` — Skeletal mesh used to setup skeletal mesh components
- L150 _public member_ `TSubclassOf<UAnimSharingTransitionInstance> BlendAnimBlueprint;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (DisplayName="Animation Blueprint for Blending"))` — Animation blueprint used to perform the blending between states
- L154 _public member_ `TSubclassOf<UAnimSharingAdditiveInstance> AdditiveAnimBlueprint;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (DisplayName = "Animation Blueprint for Additive Animation"))` — Animation blueprint used to apply additive animation on top of other states
- L158 _public member_ `TSubclassOf<UAnimationSharingStateProcessor> StateProcessorClass;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Interface class used when determining which state an actor is in
- L162 _public member_ `bool bEnableMaterialParameterCaching;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Whether or not to enable material parameter caching on the skeletal mesh components created for each state
- L166 _public member_ `TArray<FAnimationStateEntry> AnimationStates;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Definition of different animation states

#### struct `FAnimationSharingScalability`  
`struct FAnimationSharingScalability`  
_L170-195_
- reflection: `USTRUCT()`
- L174 _public function_ `FAnimationSharingScalability() : UseBlendTransitions(true), BlendSignificanceValue(0.0f), MaximumNumberConcurrentBlends(1)`
- L178 _public member_ `FPerPlatformBool UseBlendTransitions;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Flag whether or not to use blend transitions between states
- L182 _public member_ `FPerPlatformFloat BlendSignificanceValue;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (ClampMin="0.0", UIMin="0.0"))` — Significance value tied to whether or not a transition should be blended
- L186 _public member_ `FPerPlatformInt MaximumNumberConcurrentBlends;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (ClampMin = "1", UIMin = "1"))` — Maximum number of blends which can be running concurrently
- L190 _public member_ `FPerPlatformFloat TickSignificanceValue;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing, meta = (ClampMin = "0.0", UIMin = "0.0"))` — Significance value tied to whether or not the leader pose components should be ticking
- L194 _public member_ `FPerPlatformBool RequireCurvesDuringBlends;` — `UPROPERTY(EditAnywhere, Category = AnimationSharing)` — Whether or not curves are required during blends

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONSHARING_API`

### `Plugins/Developer/AnimationSharing/Source/AnimationSharing/Public/TransitionBlendInstance.h` (Public)


#### struct `FTransitionBlendInstance`  
`struct FTransitionBlendInstance`  
_L13-32_
- L16 _public prototype_ `FTransitionBlendInstance();`
- L17 _public prototype_ `void Initialise(USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InAnimationBP);`
- L18 _public prototype_ `void Setup(USkeletalMeshComponent* InFromComponent, USkeletalMeshComponent* InToComponent, float InBlendTime);`
- L19 _public prototype_ `void Stop();`
- L21 _public prototype_ `USkeletalMeshComponent* GetComponent() const;`
- L22 _public prototype_ `USkeletalMeshComponent* GetToComponent() const;`
- L23 _public prototype_ `USkeletalMeshComponent* GetFromComponent() const;`
- L26 _protected member_ `USkeletalMeshComponent * SkeletalMeshComponent;`
- L27 _protected member_ `UAnimSharingTransitionInstance* TransitionInstance;`
- L28 _protected member_ `USkeletalMeshComponent* FromComponent;`
- L29 _protected member_ `USkeletalMeshComponent* ToComponent;`
- L30 _protected member_ `float BlendTime;`
- L31 _protected member_ `bool bBlendState;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API ANIMATIONSHARING_API`
