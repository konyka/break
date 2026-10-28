# Plugins / NetworkPredictionExtras

- module root: `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras`
- headers: 20; symbols: 697
- symbol kinds: class=30, delegate=12, enum=10, enumerator=23, function=143, macro=2, member=189, prototype=243, struct=34, typedef=11
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Engine, NetCore, TraceLog, UnrealEd
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine, InputCore, NetworkPrediction, PhysicsCore, RenderCore

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/BaseMovementComponent.h` (Public)


#### class `UBaseMovementComponent`  
`class UBaseMovementComponent : public UNetworkPredictionComponent`  
_L15-56_
- reflection: `UCLASS(Abstract)`
- inherits: `UNetworkPredictionComponent`
- L21 _public prototype_ `UBaseMovementComponent();`
- L23 _public prototype_ `virtual void InitializeComponent() override;`
- L24 _public prototype_ `virtual void OnRegister() override;`
- L25 _public prototype_ `virtual void RegisterComponentTickFunctions(bool bRegister) override;`
- L29 _public function_ `virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)` — `UFUNCTION()` — Callbacks
- L32 _public function_ `UPrimitiveComponent* GetPhysicsPrimitiveComponent() const` — Used by NetworkPrediction driver for physics interpolation case
- L37 _protected prototype_ `virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent);` — Basic "Update Component/Ticking"
- L38 _protected prototype_ `virtual void UpdateTickRegistration();`
- L41 _protected prototype_ `virtual void PhysicsVolumeChanged(class APhysicsVolume* NewVolume);` — `UFUNCTION()`
- L44 _protected member_ `TObjectPtr<USceneComponent> UpdatedComponent = nullptr;` — `UPROPERTY()`
- L47 _protected member_ `TObjectPtr<UPrimitiveComponent> UpdatedPrimitive = nullptr;` — `UPROPERTY()`
- L52 _private member_ `bool bInOnRegister = false;` — Transient flag indicating whether we are executing OnRegister().
- L55 _private member_ `bool bInInitializeComponent = false;` — Transient flag indicating whether we are executing InitializeComponent().

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/BaseMovementSimulation.h` (Public)


#### class `FBaseMovementSimulation`  
`class FBaseMovementSimulation`  
_L21-47_
- desc: This provides a base for movement related simulations: moving an "UpdatedComponent" around the world. There is no actual Update function provided here, it will be implemented by subclasses.
- L24 _public prototype_ `bool SafeMoveUpdatedComponent(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult& OutHit, ETeleportType Teleport) const;`
- L25 _public prototype_ `bool MoveUpdatedComponent(const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport) const;`
- L26 _public prototype_ `FTransform GetUpdateComponentTransform() const;`
- L28 _public prototype_ `FVector GetPenetrationAdjustment(const FHitResult& Hit) const;`
- L30 _public prototype_ `bool OverlapTest(const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor) const;`
- L31 _public prototype_ `void InitCollisionParams(FCollisionQueryParams &OutParams, FCollisionResponseParams& OutResponseParam) const;`
- L32 _public prototype_ `bool ResolvePenetration(const FVector& ProposedAdjustment, const FHitResult& Hit, const FQuat& NewRotationQuat) const;`
- L35 _public member_ `mutable EMoveComponentFlags MoveComponentFlags = MOVECOMP_NoFlags;` — Flags that control the behavior of calls to MoveComponent() on our UpdatedComponent.
- L37 _public function_ `void SetComponents(USceneComponent* InUpdatedComponent, UPrimitiveComponent* InPrimitiveComponent)`
- L45 _protected member_ `USceneComponent* UpdatedComponent = nullptr;`
- L46 _protected member_ `UPrimitiveComponent* UpdatedPrimitive = nullptr;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/CharacterMotionComponent.h` (Public)


#### class `UCharacterMotionComponent`  
`class UCharacterMotionComponent : public UBaseMovementComponent`  
_L19-66_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UBaseMovementComponent`
- L25 _public prototype_ `UCharacterMotionComponent();`
- L27 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L30 _public prototype_ `DECLARE_DELEGATE_TwoParams(FProduceCharacterInput, const int32 , FCharacterMotionInputCmd& ) FProduceCharacterInput ProduceInputDelegate;` — Forward input producing event to someone else (probably the owning actor)
- L34 _public prototype_ `virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);` — BeginOverlap has to be bound to a ufunction, so we have no choice but to bind here and forward into simulation code. Not ideal.
- L41 _public prototype_ `void ProduceInput(const int32 DeltaTimeMS, FCharacterMotionInputCmd* Cmd);` — Get latest local input prior to simulation step
- L44 _public prototype_ `void RestoreFrame(const FCharacterMotionSyncState* SyncState, const FCharacterMotionAuxState* AuxState);` — Restore a previous frame prior to resimulating
- L47 _public prototype_ `void FinalizeFrame(const FCharacterMotionSyncState* SyncState, const FCharacterMotionAuxState* AuxState);` — Take output for simulation
- L50 _public prototype_ `void InitializeSimulationState(FCharacterMotionSyncState* Sync, FCharacterMotionAuxState* Aux);` — Seed initial values based on component's state
- L52 _public prototype_ `float GetMaxMoveSpeed() const;`
- L53 _public prototype_ `void SetMaxMoveSpeed(float NewMaxMoveSpeed);`
- L54 _public prototype_ `void AddMaxMoveSpeed(float AdditiveMaxMoveSpeed);`
- L59 _protected prototype_ `virtual void InitializeNetworkPredictionProxy() override;` — Network Prediction
- L60 _protected member_ `TPimplPtr<FCharacterMotionSimulation> OwnedMovementSimulation;` — If we instantiate the sim in InitializeNetworkPredictionProxy, its stored here
- L61 _protected member_ `FCharacterMotionSimulation* ActiveMovementSimulation = nullptr;` — The sim driving us, set in InitCharacterMotionSimulation. Could be child class that implements InitializeNetworkPredictionProxy.
- L63 _protected prototype_ `void InitCharacterMotionSimulation(FCharacterMotionSimulation* Simulation);`
- L65 _protected prototype_ `static float GetDefaultMaxSpeed();`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_TwoParams(FProduceCharacterInput, const int32 , FCharacterMotionInputCmd& ) FProduceCharacterInput ProduceInputDelegate;` — Forward input producing event to someone else (probably the owning actor)

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/CharacterMotionSimulation.h` (Public)


#### struct `FCharacterMotionInputCmd`  
`struct FCharacterMotionInputCmd`  
_L18-40_
- desc: State the client generates
- L21 _public member_ `FRotator RotationInput;` — Input: "pure" input for this frame. At this level, frame time has not been accounted for. (E.g., "move straight" would be (1,0,0) regardless of frame time)
- L22 _public member_ `FVector MovementInput;`
- L24 _public function_ `FCharacterMotionInputCmd() : RotationInput(ForceInitToZero) , MovementInput(ForceInitToZero)`
- L29 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L35 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### enum `ECharacterMovementMode`  
`enum class ECharacterMovementMode : uint8`  
_L43-48_
- desc: Movement mode
- L45 _public enumerator_ `None`
- L46 _public enumerator_ `Walking`
- L47 _public enumerator_ `Falling`

#### struct `FFloorTestResult`  
`struct FFloorTestResult`  
_L52-104_
- desc: Data about the floor for walking movement, used by CharacterMovementComponent.
- L59 _public member_ `uint32 bBlockingHit : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterFloor)` — True if there was a blocking hit in the floor test that was NOT in initial penetration. The HitResult can give more info about other circumstances.
- L63 _public member_ `uint32 bWalkableFloor : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterFloor)` — True if the hit found a valid walkable floor.
- L67 _public member_ `float FloorDist;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterFloor)` — The distance to the floor, computed from the swept capsule trace.
- L71 _public member_ `FHitResult HitResult;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterFloor)` — Hit result of the test that found a floor. Includes more specific data about the point of impact and surface normal at that point.
- L75 _public function_ `FFloorTestResult() : bBlockingHit(false) , bWalkableFloor(false) , FloorDist(0.f) , HitResult(1.f)`
- L84 _public function_ `bool IsWalkableFloor() const` — Returns true if the floor result hit a walkable surface.
- L89 _public function_ `void Clear()`
- L98 _public function_ `float GetDistanceToFloor() const` — Gets the distance to floor, either LineDist or FloorDist.
- L103 _public prototype_ `void SetFromSweep(const FHitResult& InHit, const float InSweepFloorDist, const bool bIsWalkableFloor);`

#### struct `FCharacterMotionSyncState`  
`struct FCharacterMotionSyncState`  
_L109-157_
- desc: State we are evolving frame to frame and keeping in sync
- L111 _public member_ `ECharacterMovementMode MovementMode;`
- L112 _public member_ `FVector Location;`
- L113 _public member_ `FVector Velocity;`
- L114 _public member_ `FRotator Rotation;`
- L116 _public function_ `FCharacterMotionSyncState() : MovementMode(ECharacterMovementMode::Walking) , Location(ForceInitToZero) , Velocity(ForceInitToZero) , Rotation(ForceInitToZero)`
- L123 _public prototype_ `bool ShouldReconcile(const FCharacterMotionSyncState& AuthorityState) const;`
- L125 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L133 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L141 _public function_ `void Interpolate(const FCharacterMotionSyncState* From, const FCharacterMotionSyncState* To, float PCT)`

#### struct `FCharacterMotionAuxState`  
`struct FCharacterMotionAuxState`  
_L160-202_
- desc: Auxiliary state that is input into the simulation.
- L162 _public member_ `float MaxSpeed = 1200.f;`
- L163 _public member_ `float TurningBoost = 8.f;`
- L164 _public member_ `float Deceleration = 8000.f;`
- L165 _public member_ `float Acceleration = 4000.f;`
- L166 _public member_ `float WalkableFloorZ = 0.71f;`
- L167 _public member_ `float FloorSweepDistance = 40.0f;`
- L169 _public prototype_ `bool ShouldReconcile(const FCharacterMotionAuxState& AuthorityState) const;`
- L171 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L181 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L191 _public function_ `void Interpolate(const FCharacterMotionAuxState* From, const FCharacterMotionAuxState* To, float PCT)`

#### class `FCharacterMotionSimulation`  
`class FCharacterMotionSimulation : public FBaseMovementSimulation`  
_L206-260_
- inherits: `FBaseMovementSimulation`
- L211 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output);` — Main update function
- L214 _public prototype_ `void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);` — Callbacks
- L217 _public member_ `static constexpr float ROTATOR_TOLERANCE = (1e-3f);` — general tolerance value for rotation checks
- L220 _public member_ `static bool ForceMispredict;` — Dev tool to force simple mispredict
- L225 _protected prototype_ `virtual void InvalidateCache();` — Called at start of simulation to avoid using old cached values.
- L227 _protected prototype_ `virtual bool IsExceedingMaxSpeed(const FVector& Velocity, float InMaxSpeed) const;`
- L229 _protected prototype_ `virtual FVector ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const;`
- L230 _protected prototype_ `virtual void TwoWallAdjust(FVector& OutDelta, const FHitResult& Hit, const FVector& OldHitNormal) const;`
- L231 _protected prototype_ `virtual float SlideAlongSurface(const FVector& Delta, float Time, const FQuat Rotation, const FVector& Normal, FHitResult& Hit, bool bHandleImpact);`
- L235 _protected prototype_ `virtual void PerformMovement(float DeltaSeconds, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& LocalSpaceMovementInput);`
- L237 _protected prototype_ `virtual void Movement_Walking(float DeltaSeconds, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& LocalSpaceMovementInput);`
- L238 _protected prototype_ `virtual void Movement_Falling(float DeltaSeconds, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& LocalSpaceMovementInput);`
- L240 _protected prototype_ `virtual void SetMovementMode(ECharacterMovementMode MovementMode, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output);`
- L242 _protected prototype_ `virtual FRotator ComputeLocalRotation(const FNetSimTimeStep& TimeStep, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output) const;`
- L243 _protected prototype_ `virtual FVector ComputeLocalInput(const FNetSimTimeStep& TimeStep, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output) const;`
- L246 _protected prototype_ `virtual FVector ComputeVelocity(float DeltaSeconds, const FVector& InitialVelocity, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& LocalSpaceMovementInput) const;` — Computes a velocity based on InputVelocity and current state
- L247 _protected prototype_ `virtual FVector ComputeGravity(float DeltaSeconds, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& Delta) const;`
- L249 _protected prototype_ `virtual void FindFloor(const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& Location, FFloorTestResult& OutFloorResult) const;`
- L250 _protected prototype_ `virtual void ComputeFloorDist(const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& Location, FFloorTestResult& OutFloorResult, float SweepDistance) const;`
- L251 _protected prototype_ `virtual bool FloorSweepTest(FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const struct FCollisionShape& CollisionShape, const struct FCollisionQueryParams& Params, const struct FCollisionResponseParams& ResponseParam) const;`
- L253 _protected prototype_ `virtual bool IsWalkable(const FHitResult& Hit, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output) const;`
- L254 _protected prototype_ `virtual bool IsValidLandingSpot(const FVector& Location, const FHitResult& Hit, const TNetSimInput<CharacterMotionStateTypes>& Input, const TNetSimOutput<CharacterMotionStateTypes>& Output, const FVector& Delta) const;`
- L259 _protected member_ `FFloorTestResult CachedFloor;`

#### Free symbols / members of external scopes

- L204 _typedef_ `using CharacterMotionStateTypes = TNetworkPredictionStateTypes<FCharacterMotionInputCmd, FCharacterMotionSyncState, FCharacterMotionAuxState>;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/FlyingMovementComponent.h` (Public)


#### class `UFlyingMovementComponent`  
`class UFlyingMovementComponent : public UBaseMovementComponent`  
_L20-67_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UBaseMovementComponent`
- L26 _public prototype_ `UFlyingMovementComponent();`
- L28 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L31 _public prototype_ `DECLARE_DELEGATE_TwoParams(FProduceFlyingInput, const int32 , FFlyingMovementInputCmd& ) FProduceFlyingInput ProduceInputDelegate;` — Forward input producing event to someone else (probably the owning actor)
- L35 _public prototype_ `virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);` — BeginOverlap has to be bound to a ufunction, so we have no choice but to bind here and forward into simulation code. Not ideal.
- L42 _public prototype_ `void ProduceInput(const int32 DeltaTimeMS, FFlyingMovementInputCmd* Cmd);` — Get latest local input prior to simulation step
- L45 _public prototype_ `void RestoreFrame(const FFlyingMovementSyncState* SyncState, const FFlyingMovementAuxState* AuxState);` — Restore a previous frame prior to resimulating
- L48 _public prototype_ `void FinalizeFrame(const FFlyingMovementSyncState* SyncState, const FFlyingMovementAuxState* AuxState);` — Take output for simulation
- L51 _public prototype_ `void InitializeSimulationState(FFlyingMovementSyncState* Sync, FFlyingMovementAuxState* Aux);` — Seed initial values based on component's state
- L53 _public prototype_ `float GetMaxMoveSpeed() const;`
- L54 _public prototype_ `void SetMaxMoveSpeed(float NewMaxMoveSpeed);`
- L55 _public prototype_ `void AddMaxMoveSpeed(float AdditiveMaxMoveSpeed);`
- L60 _protected prototype_ `virtual void InitializeNetworkPredictionProxy() override;` — Network Prediction
- L61 _protected member_ `TPimplPtr<FFlyingMovementSimulation> OwnedMovementSimulation;` — If we instantiate the sim in InitializeNetworkPredictionProxy, its stored here
- L62 _protected member_ `FFlyingMovementSimulation* ActiveMovementSimulation = nullptr;` — The sim driving us, set in InitFlyingMovementSimulation. Could be child class that implements InitializeNetworkPredictionProxy.
- L64 _protected prototype_ `void InitFlyingMovementSimulation(FFlyingMovementSimulation* Simulation);`
- L66 _protected prototype_ `static float GetDefaultMaxSpeed();`

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_TwoParams(FProduceFlyingInput, const int32 , FFlyingMovementInputCmd& ) FProduceFlyingInput ProduceInputDelegate;` — Forward input producing event to someone else (probably the owning actor)

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/FlyingMovementSimulation.h` (Public)


#### struct `FFlyingMovementInputCmd`  
`struct FFlyingMovementInputCmd`  
_L17-39_
- desc: State the client generates
- L20 _public member_ `FRotator RotationInput;` — Input: "pure" input for this frame. At this level, frame time has not been accounted for. (E.g., "move straight" would be (1,0,0) regardless of frame time)
- L21 _public member_ `FVector MovementInput;`
- L23 _public function_ `FFlyingMovementInputCmd() : RotationInput(ForceInitToZero) , MovementInput(ForceInitToZero)`
- L28 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L34 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FFlyingMovementSyncState`  
`struct FFlyingMovementSyncState`  
_L42-84_
- desc: State we are evolving frame to frame and keeping in sync
- L44 _public member_ `FVector Location;`
- L45 _public member_ `FVector Velocity;`
- L46 _public member_ `FRotator Rotation;`
- L48 _public function_ `FFlyingMovementSyncState() : Location(ForceInitToZero) , Velocity(ForceInitToZero) , Rotation(ForceInitToZero)`
- L54 _public prototype_ `bool ShouldReconcile(const FFlyingMovementSyncState& AuthorityState) const;`
- L56 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L63 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L70 _public function_ `void Interpolate(const FFlyingMovementSyncState* From, const FFlyingMovementSyncState* To, float PCT)`

#### struct `FFlyingMovementAuxState`  
`struct FFlyingMovementAuxState`  
_L87-121_
- desc: Auxiliary state that is input into the simulation.
- L89 _public member_ `float MaxSpeed = 1200.f;`
- L90 _public member_ `float TurningBoost = 8.f;`
- L91 _public member_ `float Deceleration = 8000.f;`
- L92 _public member_ `float Acceleration = 4000.f;`
- L94 _public prototype_ `bool ShouldReconcile(const FFlyingMovementAuxState& AuthorityState) const;`
- L96 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L104 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L112 _public function_ `void Interpolate(const FFlyingMovementAuxState* From, const FFlyingMovementAuxState* To, float PCT)`

#### class `FFlyingMovementSimulation`  
`class FFlyingMovementSimulation : public FBaseMovementSimulation`  
_L125-144_
- inherits: `FBaseMovementSimulation`
- L130 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<FlyingMovementStateTypes>& Input, const TNetSimOutput<FlyingMovementStateTypes>& Output);` — Main update function
- L133 _public prototype_ `void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);` — Callbacks
- L136 _public member_ `static constexpr float ROTATOR_TOLERANCE = (1e-3f);` — general tolerance value for rotation checks
- L139 _public member_ `static bool ForceMispredict;` — Dev tool to force simple mispredict
- L143 _protected prototype_ `float SlideAlongSurface(const FVector& Delta, float Time, const FQuat Rotation, const FVector& Normal, FHitResult& Hit, bool bHandleImpact);`

#### Free symbols / members of external scopes

- L123 _typedef_ `using FlyingMovementStateTypes = TNetworkPredictionStateTypes<FFlyingMovementInputCmd, FFlyingMovementSyncState, FFlyingMovementAuxState>;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockAbilitySimulation.h` (Public)


#### struct `FMockAbilityInputCmd`  
`struct FMockAbilityInputCmd : public FFlyingMovementInputCmd`  
_L45-74_
- inherits: `FFlyingMovementInputCmd`
- L47 _public member_ `bool bSprintPressed = false;`
- L48 _public member_ `bool bDashPressed = false;`
- L49 _public member_ `bool bBlinkPressed = false;`
- L51 _public member_ `bool bPrimaryPressed = false;`
- L52 _public member_ `bool bSecondaryPressed = false;`
- L54 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L65 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FMockAbilitySyncState`  
`struct FMockAbilitySyncState : public FFlyingMovementSyncState`  
_L76-100_
- inherits: `FFlyingMovementSyncState`
- L78 _public member_ `float Stamina = 0.f;`
- L80 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L86 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L92 _public function_ `void Interpolate(const FMockAbilitySyncState* From, const FMockAbilitySyncState* To, float PCT)`
- L99 _public prototype_ `bool ShouldReconcile(const FMockAbilitySyncState& AuthorityState) const;`

#### struct `FMockAbilityAuxState`  
`struct FMockAbilityAuxState : public FFlyingMovementAuxState`  
_L102-146_
- inherits: `FFlyingMovementAuxState`
- L104 _public member_ `float MaxStamina = 100.f;`
- L105 _public member_ `float StaminaRegenRate = 20.f;`
- L106 _public member_ `int16 DashTimeLeft = 0;`
- L107 _public member_ `int16 BlinkWarmupLeft = 0;`
- L108 _public member_ `int16 PrimaryCooldown = 0;`
- L109 _public member_ `bool bIsSprinting = false;`
- L111 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L122 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L133 _public function_ `void Interpolate(const FMockAbilityAuxState* From, const FMockAbilityAuxState* To, float PCT)`
- L145 _public prototype_ `bool ShouldReconcile(const FMockAbilityAuxState& AuthorityState) const;`

#### struct `FMockAbilityBlinkActivateCue`  
`struct FMockAbilityBlinkActivateCue`  
_L153-178_
- desc: Cue for blink activation (the moment the ability starts)
- L155 _public prototype_ `FMockAbilityBlinkActivateCue() = default;`
- L156 _public function_ `FMockAbilityBlinkActivateCue(const FVector& InDestination, uint8 InRandomType) : Destination(InDestination), RandomType(InRandomType)`
- L159 _public prototype_ `NETSIMCUE_BODY();`
- L161 _public member_ `FVector_NetQuantize10 Destination;`
- L162 _public member_ `uint8 RandomType;` — Random value used to color code the effect. This is the test/prove out mispredictions
- L164 _public typedef_ `using Traits = NetSimCueTraits::Strong;`
- L166 _public function_ `void NetSerialize(FArchive& Ar)`
- L173 _public function_ `bool NetIdentical(const FMockAbilityBlinkActivateCue& Other) const`

#### struct `FMockAbilityPhysicsGunFireCue`  
`struct FMockAbilityPhysicsGunFireCue`  
_L182-235_
- L184 _public prototype_ `FMockAbilityPhysicsGunFireCue() = default;`
- L185 _public function_ `FMockAbilityPhysicsGunFireCue(const FVector& InStart, const FVector& InEnd, bool bInHasCooldown, TArray<FVector_NetQuantize100>&& InHitLocations) : Start(InStart), End(InEnd), bHasCooldown(bInHasCooldown), HitLocations(InHitLocations)`
- L188 _public prototype_ `NETSIMCUE_BODY();`
- L190 _public member_ `FVector_NetQuantize100 Start;`
- L191 _public member_ `FVector_NetQuantize100 End;`
- L192 _public member_ `bool bHasCooldown;`
- L194 _public member_ `TArray<FVector_NetQuantize100> HitLocations;`
- L196 _public typedef_ `using Traits = NetSimCueTraits::ReplicatedXOrPredicted;`
- L198 _public function_ `void NetSerialize(FArchive& Ar)`
- L230 _public function_ `bool NetIdentical(const FMockAbilityPhysicsGunFireCue& Other) const`

#### struct `FMockAbilityBlinkCue`  
`struct FMockAbilityBlinkCue`  
_L243-297_
- desc: Cue for blink (the moment the teleport happens)
- L245 _public function_ `FMockAbilityBlinkCue()`
- L250 _public function_ `FMockAbilityBlinkCue(const FVector& Start, const FVector& Stop) : StartLocation(Start), StopLocation(Stop)`
- L255 _public function_ `~FMockAbilityBlinkCue()`
- L260 _public function_ `FMockAbilityBlinkCue(FMockAbilityBlinkCue&& Other) : StartLocation(MoveTemp(Other.StartLocation)), StopLocation(Other.StopLocation)`
- L266 _public function_ `FMockAbilityBlinkCue& operator=(FMockAbilityBlinkCue&& Other)`
- L274 _public prototype_ `FMockAbilityBlinkCue(const FMockAbilityBlinkCue& Other) = delete;`
- L275 _public prototype_ `FMockAbilityBlinkCue& operator=(const FMockAbilityBlinkCue& Other) = delete;`
- L277 _public prototype_ `NETSIMCUE_BODY();`
- L279 _public member_ `FVector_NetQuantize10 StartLocation;`
- L280 _public member_ `FVector_NetQuantize10 StopLocation;`
- L282 _public typedef_ `using Traits = NetSimCueTraits::Strong;`
- L284 _public function_ `void NetSerialize(FArchive& Ar)`
- L292 _public function_ `bool NetIdentical(const FMockAbilityBlinkCue& Other) const`

#### struct `FMockAbilityCueSet`  
`struct FMockAbilityCueSet`  
_L318-333_
- desc: The set of Cues the MockAbility simulation will invoke
- L321 _public function_ `template<typename TDispatchTable> static void RegisterNetSimCueTypes(TDispatchTable& DispatchTable)`

#### class `FMockAbilitySimulation`  
`class FMockAbilitySimulation : public FFlyingMovementSimulation`  
_L341-347_
- inherits: `FFlyingMovementSimulation`
- L346 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<TMockAbilityBufferTypes>& Input, const TNetSimOutput<TMockAbilityBufferTypes>& Output);` — Main update function

#### class `UMockFlyingAbilityComponent`  
`class UMockFlyingAbilityComponent : public UFlyingMovementComponent`  
_L354-451_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UFlyingMovementComponent`
- L360 _public prototype_ `UMockFlyingAbilityComponent();`
- L362 _public prototype_ `DECLARE_DELEGATE_TwoParams(FProduceMockAbilityInput, const int32 , FMockAbilityInputCmd& ) FProduceMockAbilityInput ProduceInputDelegate;`
- L365 _public prototype_ `virtual void ProduceInput(const int32 SimTimeMS, FMockAbilityInputCmd* Cmd);`
- L366 _public prototype_ `virtual void FinalizeFrame(const FMockAbilitySyncState* SyncState, const FMockAbilityAuxState* AuxState);`
- L367 _public prototype_ `virtual void InitializeSimulationState(FMockAbilitySyncState* SyncState, FMockAbilityAuxState* AuxState);`
- L370 _public prototype_ `void HandleCue(const FMockAbilityBlinkActivateCue& BlinkCue, const FNetSimCueSystemParamemters& SystemParameters);` — NetSimCues
- L371 _public prototype_ `void HandleCue(const FMockAbilityBlinkCue& BlinkCue, const FNetSimCueSystemParamemters& SystemParameters);`
- L372 _public prototype_ `void HandleCue(const FMockAbilityPhysicsGunFireCue& FireCue, const FNetSimCueSystemParamemters& SystemParameters);`
- L384 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMockAbilityNotifyStateChange, bool, bNewStateValue);`
- L388 _public member_ `FMockAbilityNotifyStateChange OnSprintStateChange;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")` — Notifies when Sprint state changes
- L392 _public member_ `FMockAbilityNotifyStateChange OnDashStateChange;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")` — Notifies when Dash state changes
- L396 _public member_ `FMockAbilityNotifyStateChange OnBlinkStateChange;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")` — Notifies when Blink Changes
- L400 _public function_ `bool IsSprinting() const` — `UFUNCTION(BlueprintCallable, Category="Mock AbilitySystem")` — Are we currently in the sprinting state
- L404 _public function_ `bool IsDashing() const` — `UFUNCTION(BlueprintCallable, Category="Mock AbilitySystem")` — Are we currently in the dashing state
- L408 _public function_ `bool IsBlinking() const` — `UFUNCTION(BlueprintCallable, Category="Mock AbilitySystem")` — Are we currently in the blinking (startup) state
- L411 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMockAbilityBlinkCueEvent, FVector, DestinationLocation, int32, RandomValue, float, ElapsedTimeSeconds);` — Blueprint assignable events for blinking. THis allows the user/blueprint to implement rollback-able events
- L413 _public member_ `FMockAbilityBlinkCueEvent OnBlinkActivateEvent;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")`
- L415 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMockAbilityBlinkCueRollback);`
- L417 _public member_ `FMockAbilityBlinkCueRollback OnBlinkActivateEventRollback;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")`
- L419 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FMockAbilityPhysicsGunFireEvent, FVector, Start, FVector, End, bool, bHasCooldown, const TArray<FVector_NetQuantize100>&, HitLocations, float, ElapsedTimeSeconds);`
- L421 _public member_ `FMockAbilityPhysicsGunFireEvent OnPhysicsGunFirEvent;` — `UPROPERTY(BlueprintAssignable, Category="Mock AbilitySystem")`
- L424 _public prototype_ `float GetBlinkWarmupTimeSeconds() const;` — `UFUNCTION(BlueprintCallable, Category="Mock AbilitySystem")`
- L427 _public prototype_ `float GetStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Mock Ability")`
- L430 _public prototype_ `float GetMaxStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Mock Ability")`
- L435 _protected prototype_ `virtual void InitializeNetworkPredictionProxy() override;` — Network Prediction
- L437 _protected member_ `TPimplPtr<FMockAbilitySimulation> OwnedAbilitySimulation;`
- L438 _protected member_ `FMockAbilitySimulation* ActiveAbilitySimulation = nullptr;`
- L440 _protected prototype_ `void InitMockAbilitySimulation(FMockAbilitySimulation* Simulation);`
- L448 _private member_ `bool bIsSprinting = false;` — Local cached values for detecting state changes from the sim in ::FinalizeFrame Its tempting to think ::FinalizeFrame could pass in the previous frames values but this could not be reliable if buffer sizes are small and network conditions etc - you may not always know what was the "last finalized frame" or even have it in the buffers anymore.
- L449 _private member_ `bool bIsDashing = false;`
- L450 _private member_ `bool bIsBlinking = false;`

#### Free symbols / members of external scopes

- L240 _macro_ `#define LOG_BLINK_CUE 0 // During development, its useful to sanity check that we aren't doing more construction or moves than we expect`
- L303 _macro_ `#define DECLARE_BLINKCUE_SUBTYPE(TYPE, TRAITS) \`
- L312 _prototype_ `DECLARE_BLINKCUE_SUBTYPE(FMockAbilityBlinkCue_Weak, NetSimCueTraits::Weak);`
- L313 _prototype_ `DECLARE_BLINKCUE_SUBTYPE(FMockAbilityBlinkCue_ReplicatedNonPredicted, NetSimCueTraits::ReplicatedNonPredicted);`
- L314 _prototype_ `DECLARE_BLINKCUE_SUBTYPE(FMockAbilityBlinkCue_ReplicatedXOrPredicted, NetSimCueTraits::ReplicatedXOrPredicted);`
- L315 _prototype_ `DECLARE_BLINKCUE_SUBTYPE(FMockAbilityBlinkCue_Strong, NetSimCueTraits::Strong);`
- L339 _typedef_ `using TMockAbilityBufferTypes = TNetworkPredictionStateTypes<FMockAbilityInputCmd, FMockAbilitySyncState, FMockAbilityAuxState>;`
- L362 _delegate_ `DECLARE_DELEGATE_TwoParams(FProduceMockAbilityInput, const int32 , FMockAbilityInputCmd& ) FProduceMockAbilityInput ProduceInputDelegate;`
- L384 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMockAbilityNotifyStateChange, bool, bNewStateValue);`
- L411 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMockAbilityBlinkCueEvent, FVector, DestinationLocation, int32, RandomValue, float, ElapsedTimeSeconds);` — Blueprint assignable events for blinking. THis allows the user/blueprint to implement rollback-able events
- L415 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMockAbilityBlinkCueRollback);`
- L419 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FMockAbilityPhysicsGunFireEvent, FVector, Start, FVector, End, bool, bHasCooldown, const TArray<FVector_NetQuantize100>&, HitLocations, float, ElapsedTimeSeconds);`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockCharacterAbilitySimulation.h` (Public)


#### struct `FMockCharacterAbilityInputCmd`  
`struct FMockCharacterAbilityInputCmd : public FCharacterMotionInputCmd`  
_L18-50_
- inherits: `FCharacterMotionInputCmd`
- L20 _public member_ `bool bSprintPressed = false;`
- L21 _public member_ `bool bDashPressed = false;`
- L22 _public member_ `bool bBlinkPressed = false;`
- L23 _public member_ `bool bJumpPressed = false;`
- L25 _public member_ `bool bPrimaryPressed = false;`
- L26 _public member_ `bool bSecondaryPressed = false;`
- L28 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L40 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FMockCharacterAbilitySyncState`  
`struct FMockCharacterAbilitySyncState : public FCharacterMotionSyncState`  
_L53-77_
- inherits: `FCharacterMotionSyncState`
- L55 _public member_ `float Stamina = 0.f;`
- L57 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L63 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L69 _public function_ `void Interpolate(const FMockCharacterAbilitySyncState* From, const FMockCharacterAbilitySyncState* To, float PCT)`
- L76 _public prototype_ `bool ShouldReconcile(const FMockCharacterAbilitySyncState& AuthorityState) const;`

#### struct `FMockCharacterAbilityAuxState`  
`struct FMockCharacterAbilityAuxState : public FCharacterMotionAuxState`  
_L79-127_
- inherits: `FCharacterMotionAuxState`
- L81 _public member_ `float MaxStamina = 100.f;`
- L82 _public member_ `float StaminaRegenRate = 20.f;`
- L83 _public member_ `int16 DashTimeLeft = 0;`
- L84 _public member_ `int16 BlinkWarmupLeft = 0;`
- L85 _public member_ `int16 PrimaryCooldown = 0;`
- L86 _public member_ `bool bIsSprinting = false;`
- L87 _public member_ `bool bIsJumping = false;`
- L89 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L101 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L113 _public function_ `void Interpolate(const FMockCharacterAbilityAuxState* From, const FMockCharacterAbilityAuxState* To, float PCT)`
- L126 _public prototype_ `bool ShouldReconcile(const FMockCharacterAbilityAuxState& AuthorityState) const;`

#### class `FMockCharacterAbilitySimulation`  
`class FMockCharacterAbilitySimulation : public FCharacterMotionSimulation`  
_L137-145_
- inherits: `FCharacterMotionSimulation`
- L139 _private typedef_ `typedef FCharacterMotionSimulation Super;`
- L144 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<TMockCharacterAbilityBufferTypes>& Input, const TNetSimOutput<TMockCharacterAbilityBufferTypes>& Output);` — Main update function

#### class `UMockCharacterAbilityComponent`  
`class UMockCharacterAbilityComponent : public UCharacterMotionComponent`  
_L155-259_
- reflection: `UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UCharacterMotionComponent`
- L161 _public prototype_ `UMockCharacterAbilityComponent();`
- L163 _public prototype_ `DECLARE_DELEGATE_TwoParams(FProduceMockCharacterAbilityInput, const int32 , FMockCharacterAbilityInputCmd& ) FProduceMockCharacterAbilityInput ProduceInputDelegate;`
- L166 _public prototype_ `virtual void ProduceInput(const int32 SimTimeMS, FMockCharacterAbilityInputCmd* Cmd);`
- L167 _public prototype_ `virtual void FinalizeFrame(const FMockCharacterAbilitySyncState* SyncState, const FMockCharacterAbilityAuxState* AuxState);`
- L168 _public prototype_ `virtual void InitializeSimulationState(FMockCharacterAbilitySyncState* SyncState, FMockCharacterAbilityAuxState* AuxState);`
- L187 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMockCharacterAbilityNotifyStateChange, bool, bNewStateValue);`
- L191 _public member_ `FMockCharacterAbilityNotifyStateChange OnSprintStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")` — Notifies when Sprint state changes
- L195 _public member_ `FMockCharacterAbilityNotifyStateChange OnDashStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")` — Notifies when Dash state changes
- L199 _public member_ `FMockCharacterAbilityNotifyStateChange OnBlinkStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")` — Notifies when Blink Changes
- L203 _public member_ `FMockCharacterAbilityNotifyStateChange OnJumpStateChange;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")` — Notifies when Jump Changes
- L207 _public function_ `bool IsSprinting() const` — `UFUNCTION(BlueprintCallable, Category = "Mock AbilitySystem")` — Are we currently in the sprinting state
- L211 _public function_ `bool IsDashing() const` — `UFUNCTION(BlueprintCallable, Category = "Mock AbilitySystem")` — Are we currently in the dashing state
- L215 _public function_ `bool IsBlinking() const` — `UFUNCTION(BlueprintCallable, Category = "Mock AbilitySystem")` — Are we currently in the blinking (startup) state
- L219 _public function_ `bool IsJumping() const` — `UFUNCTION(BlueprintCallable, Category = "Mock AbilitySystem")` — Are we currently in the jumping state
- L222 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMockCharacterAbilityBlinkCueEvent, FVector, DestinationLocation, int32, RandomValue, float, ElapsedTimeSeconds);` — Blueprint assignable events for blinking. This allows the user/blueprint to implement rollback-able events
- L224 _public member_ `FMockCharacterAbilityBlinkCueEvent OnBlinkActivateEvent;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")`
- L226 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMockCharacterAbilityBlinkCueRollback);`
- L228 _public member_ `FMockCharacterAbilityBlinkCueRollback OnBlinkActivateEventRollback;` — `UPROPERTY(BlueprintAssignable, Category = "Mock AbilitySystem")`
- L231 _public prototype_ `float GetBlinkWarmupTimeSeconds() const;` — `UFUNCTION(BlueprintCallable, Category = "Mock AbilitySystem")`
- L234 _public prototype_ `float GetStamina() const;` — `UFUNCTION(BlueprintCallable, Category = "Mock Ability")`
- L237 _public prototype_ `float GetMaxStamina() const;` — `UFUNCTION(BlueprintCallable, Category = "Mock Ability")`
- L242 _protected prototype_ `virtual void InitializeNetworkPredictionProxy() override;` — Network Prediction
- L244 _protected member_ `TPimplPtr<FMockCharacterAbilitySimulation> OwnedAbilitySimulation;`
- L245 _protected member_ `FMockCharacterAbilitySimulation* ActiveAbilitySimulation = nullptr;`
- L247 _protected prototype_ `void InitMockCharacterAbilitySimulation(FMockCharacterAbilitySimulation* Simulation);`
- L255 _private member_ `bool bIsSprinting = false;` — Local cached values for detecting state changes from the sim in ::FinalizeFrame Its tempting to think ::FinalizeFrame could pass in the previous frames values but this could not be reliable if buffer sizes are small and network conditions etc - you may not always know what was the "last finalized frame" or even have it in the buffers anymore.
- L256 _private member_ `bool bIsDashing = false;`
- L257 _private member_ `bool bIsBlinking = false;`
- L258 _private member_ `bool bIsJumping = false;`

#### Free symbols / members of external scopes

- L135 _typedef_ `using TMockCharacterAbilityBufferTypes = TNetworkPredictionStateTypes<FMockCharacterAbilityInputCmd, FMockCharacterAbilitySyncState, FMockCharacterAbilityAuxState>;`
- L163 _delegate_ `DECLARE_DELEGATE_TwoParams(FProduceMockCharacterAbilityInput, const int32 , FMockCharacterAbilityInputCmd& ) FProduceMockCharacterAbilityInput ProduceInputDelegate;`
- L187 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMockCharacterAbilityNotifyStateChange, bool, bNewStateValue);`
- L222 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMockCharacterAbilityBlinkCueEvent, FVector, DestinationLocation, int32, RandomValue, float, ElapsedTimeSeconds);` — Blueprint assignable events for blinking. This allows the user/blueprint to implement rollback-able events
- L226 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMockCharacterAbilityBlinkCueRollback);`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockNetworkSimulation.h` (Public)


#### struct `FMockInputCmd`  
`struct FMockInputCmd`  
_L65-78_
- desc: State the client generates
- L67 _public member_ `float InputValue=0;`
- L69 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L74 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FMockSyncState`  
`struct FMockSyncState`  
_L81-105_
- desc: State we are evolving frame to frame and keeping in sync
- L83 _public member_ `float Total=0;`
- L84 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L90 _public function_ `bool ShouldReconcile(const FMockSyncState& AuthorityState) const` — Compare this state with AuthorityState. return true if a reconcile (correction) should happen
- L96 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L101 _public function_ `void Interpolate(const FMockSyncState* From, const FMockSyncState* To, float PCT)`

#### struct `FMockAuxState`  
`struct FMockAuxState`  
_L109-132_
- desc: Auxiliary state that is input into the simulation. Doesn't change during the simulation tick. (It can change and even be predicted but doing so will trigger more bookeeping, etc. Changes will happen "next tick")
- L111 _public member_ `float Multiplier=1;`
- L112 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L117 _public function_ `bool ShouldReconcile(const FMockAuxState& Authority) const`
- L123 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L128 _public function_ `void Interpolate(const FMockAuxState* From, const FMockAuxState* To, float PCT)`

#### struct `FMockCue`  
`struct FMockCue`  
_L139-147_
- desc: A minimal Cue, emitted every 10 "totals" with a random integer as a payload
- L141 _public prototype_ `FMockCue() = default;`
- L142 _public function_ `FMockCue(int32 InRand) : RandomData(InRand)`
- L145 _public prototype_ `NETSIMCUE_BODY();`
- L146 _public member_ `int32 RandomData = 0;`

#### struct `FMockCueSet`  
`struct FMockCueSet`  
_L150-157_
- desc: Set of all cues the Mock simulation emits. Not strictly necessary and not that helpful when there is only one cue (but using since this is the example real simulations will want to use)
- L153 _public function_ `template<typename TDispatchTable> static void RegisterNetSimCueTypes(TDispatchTable& DispatchTable)`

#### class `FMockNetworkSimulation`  
`class FMockNetworkSimulation`  
_L167-173_
- L172 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<TMockNetworkSimulationBufferTypes>& Input, const TNetSimOutput<TMockNetworkSimulationBufferTypes>& Output);` — Main update function

#### class `UMockNetworkSimulationComponent`  
`class UMockNetworkSimulationComponent : public UNetworkPredictionComponent`  
_L180-210_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UNetworkPredictionComponent`
- L186 _public prototype_ `UMockNetworkSimulationComponent();`
- L188 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L190 _public prototype_ `virtual void InitializeNetworkPredictionProxy() override;`
- L193 _public prototype_ `void InitializeSimulationState(FMockSyncState* Sync, FMockAuxState* Aux);` — Seed initial values based on component's state
- L196 _public prototype_ `void ProduceInput(const int32 DeltaTimeMS, FMockInputCmd* Cmd);` — Set latest input
- L199 _public prototype_ `void FinalizeFrame(const FMockSyncState* Sync, const FMockAuxState* Aux);` — Take output of Sim and push to component
- L203 _public prototype_ `void HandleCue(const FMockCue& MockCue, const FNetSimCueSystemParamemters& SystemParameters);`
- L206 _public member_ `float MockValue = 1000.f;` — Mock representation of "syncing' to the sync state in the network sim.
- L209 _public member_ `TUniquePtr<FMockNetworkSimulation> MockNetworkSimulation;` — Our own simulation object. This could just as easily be shared among all UMockNetworkSimulationComponent

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_STATS_GROUP(TEXT("NetworkPrediction"), STATGROUP_NetworkPrediction, S`
- L163 _typedef_ `using TMockNetworkSimulationBufferTypes = TNetworkPredictionStateTypes<FMockInputCmd, FMockSyncState, FMockAuxState>;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockRootMotionComponent.h` (Public)


#### struct `FRootMotionSourceCache`  
`struct FRootMotionSourceCache`  
_L16-24_
- reflection: `USTRUCT()`
- L21 _public member_ `TObjectPtr<UMockRootMotionSource> Instance = nullptr;` — `UPROPERTY()`
- L23 _public member_ `int32 ClassID = 0;`

#### class `UMockRootMotionComponent`  
`class UMockRootMotionComponent : public UBaseMovementComponent, public IRootMotionSourceStore`  
_L37-89_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UBaseMovementComponent,IRootMotionSourceStore`
- L43 _public prototype_ `virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;`
- L45 _public prototype_ `void InitializeSimulationState(FMockRootMotionSyncState* SyncState, FMockRootMotionAuxState* AuxState);`
- L46 _public prototype_ `void ProduceInput(const int32 SimTimeMS, FMockRootMotionInputCmd* Cmd);`
- L47 _public prototype_ `void RestoreFrame(const FMockRootMotionSyncState* SyncState, const FMockRootMotionAuxState* AuxState);`
- L48 _public prototype_ `void FinalizeFrame(const FMockRootMotionSyncState* SyncState, const FMockRootMotionAuxState* AuxState);`
- L53 _public prototype_ `UMockRootMotionSource* CreateRootMotionSource(TSubclassOf<UMockRootMotionSource> Source);` — `UFUNCTION(BlueprintCallable, Category=Input)`
- L56 _public prototype_ `void Input_PlayRootMotionSource(UMockRootMotionSource* Source);` — `UFUNCTION(BlueprintCallable, Category=Input)`
- L59 _public prototype_ `void Input_PlayRootMotionSourceByClass(TSubclassOf<UMockRootMotionSource> Source);` — `UFUNCTION(BlueprintCallable, Category=Input)`
- L64 _public prototype_ `void PlayRootMotionSource(UMockRootMotionSource* Source);` — `UFUNCTION(BlueprintCallable, Category=Animation)` — Callable by authority. Plays "out of band" animation: e.g, directly sets the RootMotionSourceID on the sync state, rather than the pending InputCmd. This is analogous to outside code teleporting the actor (outside of the core simulation function)
- L67 _public prototype_ `void PlayRootMotionSourceByClass(TSubclassOf<UMockRootMotionSource> Source);` — `UFUNCTION(BlueprintCallable, Category=Animation)`
- L70 _public prototype_ `UMockRootMotionSource* ResolveRootMotionSource(int32 ID, const TArrayView<const uint8>& Data) override;` — Root Motion Object store
- L71 _public prototype_ `void StoreRootMotionSource(int32 ID, UMockRootMotionSource* Source) override;`
- L75 _protected prototype_ `void FindAndCacheAnimInstance();`
- L78 _protected member_ `FMockRootMotionInputCmd PendingInputCmd;` — Next local InputCmd that will be submitted. This is a simple way of getting input to the system
- L80 _protected prototype_ `void InitializeNetworkPredictionProxy() override;`
- L81 _protected member_ `TUniquePtr<FMockRootMotionSimulation> OwnedMockRootMotionSimulation;`
- L83 _protected member_ `UAnimInstance* AnimInstance = nullptr;`
- L88 _private member_ `FRootMotionSourceCache RootMotionSourceCache;` — `UPROPERTY()`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockRootMotionSimulation.h` (Public)


#### struct `TMockRootMotionSourceProxy`  
`template<typename IdType=uint8, int32 InInlineSize=128, int32 InMaxSize=255> struct TMockRootMotionSourceProxy`  
_L18-109_
- desc: Thing that goes in the aux state
- L24 _public function_ `void Reset()`
- L31 _public function_ `bool IsValid() const`
- L37 _public function_ `void NetSerialize(const FNetSerializeParams& P)` — Writes the blob of parameters to the actual network stream
- L59 _public function_ `FBitReader GetParamBitReader()`
- L65 _public function_ `void WriteSource(IdType InID, int32 InStartMS)` — Writes a new source with no params
- L75 _public function_ `void WriteParams(TFunctionRef<void(FBitWriter&)> WriteFunc)` — Write a new source and encode the params into the generic param block
- L87 _public function_ `IdType GetID() const`
- L88 _public function_ `int32 GetStartMS() const`
- L89 _public function_ `TArrayView<const uint8> GetParamsDataView() const`
- L91 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L98 _public function_ `bool operator==(const TMockRootMotionSourceProxy<IdType, InlineSize, MaxSize> &Other) const`
- L103 _public function_ `bool operator!=(const TMockRootMotionSourceProxy<IdType, InlineSize, MaxSize> &Other) const`
- L106 _private member_ `IdType ID = InvalidValue;` — static mapping to the source (could be global or per sim/actor/anim instance)
- L107 _private member_ `int32 StartMS = 0;` — Sim time this source started
- L108 _private member_ `TArray<uint8, TInlineAllocator<InlineSize>> Params;` — quantized params

#### enum `TMockRootMotionSourceProxy::(anonymous)`  
`enum`  
_L20-20_

#### enum `TMockRootMotionSourceProxy::(anonymous)`  
`enum`  
_L21-21_

#### enum `TMockRootMotionSourceProxy::(anonymous)`  
`enum`  
_L22-22_

#### struct `FMockRootMotionInputCmd`  
`struct FMockRootMotionInputCmd`  
_L127-148_
- L137 _public member_ `TMockRootMotionSourceProxy<> PlaySource;` — What we are want to play
- L139 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L144 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FMockRootMotionSyncState`  
`struct FMockRootMotionSyncState`  
_L150-189_
- L155 _public member_ `FVector Location;` — Transform state. In the final version we may want to decouple this from the animation state, For example if a "movement simulation" was driving things, it may "own" the transform and feed it into the root motion system. But this is meant to be a stand alone mock example.
- L156 _public member_ `FRotator Rotation;`
- L158 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L163 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L169 _public function_ `void Interpolate(const FMockRootMotionSyncState* From, const FMockRootMotionSyncState* To, float PCT)`
- L183 _public function_ `bool ShouldReconcile(const FMockRootMotionSyncState& AuthorityState) const`

#### struct `FMockRootMotionAuxState`  
`struct FMockRootMotionAuxState`  
_L193-220_
- desc: The aux state should hold state that does not frequently change. It is otherwise the same as sync state. (note that optimizations for sparse aux storage are not complete yet)
- L195 _public member_ `TMockRootMotionSourceProxy<> Source;`
- L196 _public member_ `int32 EndTimeMS = 0;` — Time the Source finished. Used in the sim's input handling
- L198 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L204 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L210 _public function_ `bool ShouldReconcile(const FMockRootMotionAuxState& AuthorityState) const`
- L216 _public function_ `void Interpolate(const FMockRootMotionAuxState* From, const FMockRootMotionAuxState* To, float PCT)`

#### class `IMockRootMotionSourceMap`  
`class IMockRootMotionSourceMap`  
_L223-234_
- desc: This is the interface into "things that actually provide root motion"
- L228 _public prototype_ `virtual FTransform StepRootMotion(const FNetSimTimeStep& TimeStep, const FMockRootMotionSyncState* In, FMockRootMotionSyncState* Out, const FMockRootMotionAuxState* Aux) = 0;` — Advance the root motion state by the given TimeStep
- L233 _public prototype_ `virtual void FinalizePose(const FMockRootMotionSyncState* Sync, UAnimInstance* AnimInstance) = 0;` — Push the Sync state to the AnimInstance this is debatable - the simulation code doesn't need to call this, its really the concern of the driver (UMockRootMotionComponent) and not all potential root motion sources are going to want to set a pose.

#### class `FMockRootMotionSimulation`  
`class FMockRootMotionSimulation : public FBaseMovementSimulation`  
_L241-260_
- inherits: `FBaseMovementSimulation`
- desc: The actual NetworkPrediction simulation code that implements root motion movement (root motion evaluation itself is done via IMockRootMotionSourceMap but the actual 'how to move thing given a delta' is done here)
- L246 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<MockRootMotionStateTypes>& Input, const TNetSimOutput<MockRootMotionStateTypes>& Output);` — The main tick function
- L248 _public member_ `IRootMotionSourceStore* SourceStore = nullptr;`
- L251 _public function_ `template<typename ProxyType> UMockRootMotionSource* ResolveRootMotionSource(const ProxyType& Proxy)`
- L259 _public member_ `USceneComponent* RootMotionComponent = nullptr;` — The component the root motion is relative to. This was found to be needed since, in our examples, we author root motion anims where Y is forward and we rotate the mesh components at the actor level so that X is forward. We need to know which component to rotate the root motion animation relative to. If we continue with this, this means all non anim based root motions should expect to follow the same convention. Need clarity here from animation team.

#### Free symbols / members of external scopes

- L20 _enumerator_ `enum { InlineSize = InInlineSize }; enum { MaxSize = InMaxSize }; enum { InvalidValue = TNumericLimits<IdType>::Max() }; void Reset() { ID = InvalidValue; StartMS = 0;` (scope `TMockRootMotionSourceProxy::__anon0f51f6a90103`)
- L21 _enumerator_ `enum { MaxSize = InMaxSize }; enum { InvalidValue = TNumericLimits<IdType>::Max() }; void Reset() { ID = InvalidValue; StartMS = 0; Params.Reset();` (scope `TMockRootMotionSourceProxy::__anon0f51f6a90203`)
- L22 _enumerator_ `enum { InvalidValue = TNumericLimits<IdType>::Max() }; void Reset() { ID = InvalidValue; StartMS = 0; Params.Reset(); }` (scope `TMockRootMotionSourceProxy::__anon0f51f6a90303`)
- L237 _typedef_ `using MockRootMotionStateTypes = TNetworkPredictionStateTypes<FMockRootMotionInputCmd, FMockRootMotionSyncState, FMockRootMotionAuxState>;` — This just defines the state types that the simulation uses

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockRootMotionSourceObject.h` (Public)


#### struct `FMockRootMotionStepParameters`  
`struct FMockRootMotionStepParameters`  
_L20-26_
- L22 _public member_ `const FVector& Location;`
- L23 _public member_ `const FRotator& Rotation;`
- L24 _public member_ `int32 ElapsedMS;` — Time that has been stepped since this source was played
- L25 _public member_ `int32 DeltaMS;` — Delta time we are stepping with this call

#### struct `FMockRootMotionReturnValue`  
`struct FMockRootMotionReturnValue`  
_L28-48_
- L42 _public member_ `ESourceState State = ESourceState::Continue;`
- L43 _public member_ `ETransformType TransformType = ETransformType::Absolute;`
- L44 _public member_ `FTransform DeltaTransform = FTransform::Identity;`
- L46 _public function_ `void Stop()`
- L47 _public function_ `void Continue()`

#### enum `FMockRootMotionReturnValue::ESourceState`  
`enum class ESourceState : uint8`  
_L30-34_
- L32 _public enumerator_ `Continue`
- L33 _public enumerator_ `Stop`

#### enum `FMockRootMotionReturnValue::ETransformType`  
`enum class ETransformType : uint8`  
_L36-40_
- L38 _public enumerator_ `Absolute`
- L39 _public enumerator_ `AnimationRelative`

#### class `UMockRootMotionSource`  
`class UMockRootMotionSource : public UObject`  
_L51-82_
- reflection: `UCLASS(abstract)`
- inherits: `UObject`
- L57 _public prototype_ `UMockRootMotionSource() = default;`
- L58 _public function_ `virtual ~UMockRootMotionSource()`
- L60 _public function_ `virtual FMockRootMotionReturnValue Step(const FMockRootMotionStepParameters& Parameters)`
- L62 _public function_ `virtual void FinalizePose(int32 ElapsedMS, UAnimInstance* AnimInstance) const`
- L67 _public function_ `bool IsValidRootMotionSource() const` — Returns true if this instance is an acceptable runtime source for root motion. When called on a CDO, calls IsValidCDO() When called on a constructed instance, calls IsValidInstance();
- L75 _public function_ `virtual bool IsValidCDO() const` — Only called on CDOs - Is this class default object valid (or does it require subclassing to fill in required data) If true, this class gets a root motion source ID assigned and can be replicated If false, no ID and runtime error if this class is tried to be used
- L79 _public function_ `virtual bool IsValidInstance() const` — Runtime check if this source is well formed/valid for use By default this will just check IsValidCDO, but subclasses that require instancing + dynamic data will want to check that.
- L81 _public function_ `virtual void SerializePayloadParameters(FBitArchive& Ar)`

#### class `UMockRootMotionSourceClassMap`  
`class UMockRootMotionSourceClassMap : public UObject`  
_L86-122_
- reflection: `UCLASS()`
- inherits: `UObject`
- L92 _public prototype_ `virtual void BeginDestroy() override;`
- L95 _public prototype_ `static void InitSingleton();` — Creates singleton instance
- L98 _public prototype_ `static void BuildClassMap();` — Refreshes internal class structure: must be called when new classes are available/unloaded
- L101 _public function_ `static UMockRootMotionSourceClassMap* Get()` — Get Singleton instance
- L108 _public prototype_ `void CopyToReplicatedManager(ANetworkPredictionReplicatedManager* Manager);` — Copy singleton's data into replicated manager
- L112 _private prototype_ `void BuildClassMap_Internal();`
- L114 _private member_ `static UMockRootMotionSourceClassMap* Singleton;`
- L116 _private member_ `FDelegateHandle AuthoritySpawnCallbackHandle;`
- L119 _private member_ `TArray<TSoftClassPtr<UMockRootMotionSource>> SourceList;` — `UPROPERTY()`
- L121 _private member_ `TSortedMap<UClass*, int32> LookupMap;`

#### class `UMockRootMotionSource_Montage`  
`class UMockRootMotionSource_Montage : public UMockRootMotionSource`  
_L129-155_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMockRootMotionSource`
- L134 _private function_ `virtual bool IsValidCDO() const` — (BP) Subclasses must set montage asset for this to be valid
- L136 _private function_ `void SerializePayloadParameters(FBitArchive& Ar) override`
- L144 _protected member_ `TObjectPtr<UAnimMontage> Montage;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L147 _protected member_ `float PlayRate = 1.f;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L150 _protected member_ `FVector TranslationScale = FVector(1.f);` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L152 _protected prototype_ `virtual FMockRootMotionReturnValue Step(const FMockRootMotionStepParameters& Parameters) override;`
- L154 _protected prototype_ `void FinalizePose(int32 ElapsedMS, UAnimInstance* AnimInstance) const override;`

#### class `UMockRootMotionSource_Curve`  
`class UMockRootMotionSource_Curve : public UMockRootMotionSource`  
_L158-182_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMockRootMotionSource`
- L163 _private function_ `virtual bool IsValidCDO() const` — (BP) Subclasses must set curve  asset for this to be valid
- L165 _private function_ `void SerializePayloadParameters(FBitArchive& Ar) override`
- L173 _protected member_ `TObjectPtr<UCurveVector> Curve;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L176 _protected member_ `float PlayRate = 1.f;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L179 _protected member_ `FVector TranslationScale = FVector(1.f);` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L181 _protected prototype_ `virtual FMockRootMotionReturnValue Step(const FMockRootMotionStepParameters& Parameters);`

#### class `UMockRootMotionSource_MoveToLocation`  
`class UMockRootMotionSource_MoveToLocation : public UMockRootMotionSource`  
_L185-226_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMockRootMotionSource`
- L190 _private function_ `virtual bool IsValidCDO() const` — This is always a valid source class: Destination is only set at runtime (we have no static data that must be set)
- L193 _private function_ `virtual bool IsValidInstance() const` — Require Destination to be set for this instance to be valid
- L195 _private prototype_ `virtual FMockRootMotionReturnValue Step(const FMockRootMotionStepParameters& Parameters);`
- L197 _private function_ `void SerializePayloadParameters(FBitArchive& Ar) override`
- L212 _private function_ `void SetDestination(const FVector& InDestination)` — `UFUNCTION(BlueprintCallable, Category="Root Motion")`
- L217 _protected member_ `FVector Destination;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L220 _protected member_ `float Velocity = 100.f;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L223 _protected member_ `float SnapToTolerance = 1.f;` — `UPROPERTY(EditAnywhere, Category=RootMotion)`
- L225 _protected member_ `bool bDestinationSet = false;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/MockRootMotionSourceStore.h` (Public)


#### class `IRootMotionSourceStore`  
`class IRootMotionSourceStore`  
_L10-15_
- desc: Interface for managing instantiated root motion source objects
- L13 _public prototype_ `virtual UMockRootMotionSource* ResolveRootMotionSource(int32 ID, const TArrayView<const uint8>& Data) = 0;`
- L14 _public prototype_ `virtual void StoreRootMotionSource(int32 ID, UMockRootMotionSource* Source) = 0;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/NetworkPredictionExtrasCharacter.h` (Public)


#### enum `ENetworkPredictionExtrasCharacterInputPreset`  
`enum class ENetworkPredictionExtrasCharacterInputPreset: uint8`  
_L37-43_
- reflection: `UENUM()`
- L40 _public enumerator_ `None` — No input
- L42 _public enumerator_ `Forward` — Just moves forward

#### class `ANetworkPredictionExtrasCharacter`  
`class ANetworkPredictionExtrasCharacter : public APawn`  
_L47-103_
- reflection: `UCLASS()`
- inherits: `APawn`
- desc: Sample pawn that uses UCharacterMotionComponent. The main thing this provides is actually producing user input for the component/simulation to consume.
- L53 _public prototype_ `ANetworkPredictionExtrasCharacter(const FObjectInitializer& ObjectInitializer);`
- L55 _public prototype_ `virtual void BeginPlay() override;`
- L56 _public prototype_ `virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;`
- L57 _public prototype_ `virtual void Tick( float DeltaSeconds) override;`
- L58 _public prototype_ `virtual UNetConnection* GetNetConnection() const override;` — For bFakeAutonomousProxy only
- L62 _public member_ `ENetworkPredictionExtrasCharacterInputPreset InputPreset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Automation")`
- L66 _public member_ `bool bFakeAutonomousProxy = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Automation")` — Actor will behave like autonomous proxy even though not posessed by an APlayercontroller. To be used in conjuction with InputPreset.
- L69 _public prototype_ `void PrintDebug();` — `UFUNCTION(BlueprintCallable, Category="Debug")`
- L72 _public prototype_ `float GetMaxMoveSpeed() const;` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L75 _public prototype_ `void SetMaxMoveSpeed(float NewMaxMoveSpeed);` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L78 _public prototype_ `void AddMaxMoveSpeed(float AdditiveMaxMoveSpeed);` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L82 _protected prototype_ `void ProduceInput(const int32 DeltaMS, FCharacterMotionInputCmd& Cmd);`
- L85 _protected member_ `TObjectPtr<UCharacterMotionComponent> CharacterMotionComponent;` — `UPROPERTY(Category=Movement, VisibleAnywhere)`
- L89 _private member_ `FVector CachedMoveInput;`
- L90 _private member_ `FVector2D CachedLookInput;`
- L92 _private prototype_ `void InputAxis_MoveForward(float Value);`
- L93 _private prototype_ `void InputAxis_MoveRight(float Value);`
- L94 _private prototype_ `void InputAxis_LookYaw(float Value);`
- L95 _private prototype_ `void InputAxis_LookPitch(float Value);`
- L96 _private prototype_ `void InputAxis_MoveUp(float Value);`
- L97 _private prototype_ `void InputAxis_MoveDown(float Value);`
- L99 _private function_ `void Action_LeftShoulder_Pressed()`
- L100 _private function_ `void Action_LeftShoulder_Released()`
- L101 _private function_ `void Action_RightShoulder_Pressed()`
- L102 _private function_ `void Action_RightShoulder_Released()`

#### enum `ENetworkPredictionExtrasMockCharacterAbilityInputPreset`  
`enum class ENetworkPredictionExtrasMockCharacterAbilityInputPreset: uint8`  
_L106-114_
- reflection: `UENUM()`
- L109 _public enumerator_ `None` — No input
- L110 _public enumerator_ `Sprint`
- L111 _public enumerator_ `Dash`
- L112 _public enumerator_ `Blink`
- L113 _public enumerator_ `Jump`

#### class `ANetworkPredictionExtrasCharacter_MockAbility`  
`class ANetworkPredictionExtrasCharacter_MockAbility : public ANetworkPredictionExtrasCharacter`  
_L119-169_
- reflection: `UCLASS()`
- inherits: `ANetworkPredictionExtrasCharacter`
- desc: Example subclass of ANetworkPredictionExtrasCharacter that uses the MockAbility simulation
- L125 _public prototype_ `ANetworkPredictionExtrasCharacter_MockAbility(const FObjectInitializer& ObjectInitializer);`
- L126 _public prototype_ `virtual void BeginPlay() override;`
- L127 _public prototype_ `virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;`
- L131 _public prototype_ `UMockCharacterAbilityComponent* GetMockCharacterAbilityComponent();` — `UFUNCTION(BlueprintPure, Category="Ability")`
- L133 _public prototype_ `const UMockCharacterAbilityComponent* GetMockCharacterAbilityComponent() const;`
- L136 _public member_ `ENetworkPredictionExtrasMockCharacterAbilityInputPreset AbilityInputPreset = ENetworkPredictionExtrasMockCharacterAbilityInputPreset::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Automation")`
- L139 _public prototype_ `float GetStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Ability")`
- L142 _public prototype_ `float GetMaxStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Ability")`
- L146 _protected prototype_ `void ProduceInput(const int32 SimTimeMS, FMockCharacterAbilityInputCmd& Cmd);`
- L148 _protected prototype_ `void Action_Sprint_Pressed();`
- L149 _protected prototype_ `void Action_Sprint_Released();`
- L150 _protected prototype_ `void Action_Dash_Pressed();`
- L151 _protected prototype_ `void Action_Dash_Released();`
- L152 _protected prototype_ `void Action_Blink_Pressed();`
- L153 _protected prototype_ `void Action_Blink_Released();`
- L154 _protected prototype_ `void Action_Jump_Pressed();`
- L155 _protected prototype_ `void Action_Jump_Released();`
- L157 _protected prototype_ `void Action_Primary_Pressed();`
- L158 _protected prototype_ `void Action_Primary_Released();`
- L160 _protected prototype_ `void Action_Secondary_Pressed();`
- L161 _protected prototype_ `void Action_Secondary_Released();`
- L163 _protected member_ `bool bSprintPressed = false;`
- L164 _protected member_ `bool bDashPressed = false;`
- L165 _protected member_ `bool bBlinkPressed = false;`
- L166 _protected member_ `bool bJumpPressed = false;`
- L167 _protected member_ `bool bPrimaryPressed = false;`
- L168 _protected member_ `bool bSecondaryPressed = false;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/NetworkPredictionExtrasFlyingPawn.h` (Public)


#### enum `ENetworkPredictionExtrasFlyingInputPreset`  
`enum class ENetworkPredictionExtrasFlyingInputPreset: uint8`  
_L37-43_
- reflection: `UENUM()`
- L40 _public enumerator_ `None` — No input
- L42 _public enumerator_ `Forward` — Just moves forward

#### class `ANetworkPredictionExtrasFlyingPawn`  
`class ANetworkPredictionExtrasFlyingPawn : public APawn`  
_L47-103_
- reflection: `UCLASS()`
- inherits: `APawn`
- desc: Sample pawn that uses UFlyingMovementComponent. The main thing this provides is actually producing user input for the component/simulation to consume.
- L53 _public prototype_ `ANetworkPredictionExtrasFlyingPawn(const FObjectInitializer& ObjectInitializer);`
- L55 _public prototype_ `virtual void BeginPlay() override;`
- L56 _public prototype_ `virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;`
- L57 _public prototype_ `virtual void Tick( float DeltaSeconds) override;`
- L58 _public prototype_ `virtual UNetConnection* GetNetConnection() const override;` — For bFakeAutonomousProxy only
- L62 _public member_ `ENetworkPredictionExtrasFlyingInputPreset InputPreset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Automation")`
- L66 _public member_ `bool bFakeAutonomousProxy = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Automation")` — Actor will behave like autonomous proxy even though not posessed by an APlayercontroller. To be used in conjuction with InputPreset.
- L69 _public prototype_ `void PrintDebug();` — `UFUNCTION(BlueprintCallable, Category="Debug")`
- L72 _public prototype_ `float GetMaxMoveSpeed() const;` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L75 _public prototype_ `void SetMaxMoveSpeed(float NewMaxMoveSpeed);` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L78 _public prototype_ `void AddMaxMoveSpeed(float AdditiveMaxMoveSpeed);` — `UFUNCTION(BlueprintCallable, Category="Gameplay")`
- L82 _protected prototype_ `void ProduceInput(const int32 DeltaMS, FFlyingMovementInputCmd& Cmd);`
- L85 _protected member_ `TObjectPtr<UFlyingMovementComponent> FlyingMovementComponent;` — `UPROPERTY(Category=Movement, VisibleAnywhere)`
- L89 _private member_ `FVector3f CachedMoveInput;`
- L90 _private member_ `FVector2D CachedLookInput;`
- L92 _private prototype_ `void InputAxis_MoveForward(float Value);`
- L93 _private prototype_ `void InputAxis_MoveRight(float Value);`
- L94 _private prototype_ `void InputAxis_LookYaw(float Value);`
- L95 _private prototype_ `void InputAxis_LookPitch(float Value);`
- L96 _private prototype_ `void InputAxis_MoveUp(float Value);`
- L97 _private prototype_ `void InputAxis_MoveDown(float Value);`
- L99 _private function_ `void Action_LeftShoulder_Pressed()`
- L100 _private function_ `void Action_LeftShoulder_Released()`
- L101 _private function_ `void Action_RightShoulder_Pressed()`
- L102 _private function_ `void Action_RightShoulder_Released()`

#### enum `ENetworkPredictionExtrasMockAbilityInputPreset`  
`enum class ENetworkPredictionExtrasMockAbilityInputPreset: uint8`  
_L106-113_
- reflection: `UENUM()`
- L109 _public enumerator_ `None` — No input
- L110 _public enumerator_ `Sprint`
- L111 _public enumerator_ `Dash`
- L112 _public enumerator_ `Blink`

#### class `ANetworkPredictionExtrasFlyingPawn_MockAbility`  
`class ANetworkPredictionExtrasFlyingPawn_MockAbility : public ANetworkPredictionExtrasFlyingPawn`  
_L118-165_
- reflection: `UCLASS()`
- inherits: `ANetworkPredictionExtrasFlyingPawn`
- desc: Example subclass of ANetworkPredictionExtrasFlyingPawn that uses the MockAbility simulation
- L124 _public prototype_ `ANetworkPredictionExtrasFlyingPawn_MockAbility(const FObjectInitializer& ObjectInitializer);`
- L125 _public prototype_ `virtual void BeginPlay() override;`
- L126 _public prototype_ `virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;`
- L130 _public prototype_ `UMockFlyingAbilityComponent* GetMockFlyingAbilityComponent();` — `UFUNCTION(BlueprintPure, Category="Ability")`
- L132 _public prototype_ `const UMockFlyingAbilityComponent* GetMockFlyingAbilityComponent() const;`
- L135 _public member_ `ENetworkPredictionExtrasMockAbilityInputPreset AbilityInputPreset = ENetworkPredictionExtrasMockAbilityInputPreset::None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Automation")`
- L138 _public prototype_ `float GetStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Ability")`
- L141 _public prototype_ `float GetMaxStamina() const;` — `UFUNCTION(BlueprintCallable, Category="Ability")`
- L145 _protected prototype_ `void ProduceInput(const int32 SimTimeMS, FMockAbilityInputCmd& Cmd);`
- L147 _protected prototype_ `void Action_Sprint_Pressed();`
- L148 _protected prototype_ `void Action_Sprint_Released();`
- L149 _protected prototype_ `void Action_Dash_Pressed();`
- L150 _protected prototype_ `void Action_Dash_Released();`
- L151 _protected prototype_ `void Action_Blink_Pressed();`
- L152 _protected prototype_ `void Action_Blink_Released();`
- L154 _protected prototype_ `void Action_Primary_Pressed();`
- L155 _protected prototype_ `void Action_Primary_Released();`
- L157 _protected prototype_ `void Action_Secondary_Pressed();`
- L158 _protected prototype_ `void Action_Secondary_Released();`
- L160 _protected member_ `bool bSprintPressed = false;`
- L161 _protected member_ `bool bDashPressed = false;`
- L162 _protected member_ `bool bBlinkPressed = false;`
- L163 _protected member_ `bool bPrimaryPressed = false;`
- L164 _protected member_ `bool bSecondaryPressed = false;`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/NetworkPredictionExtrasGameMode.h` (Public)


#### class `ANetworkPredictionExtrasGameMode`  
`class ANetworkPredictionExtrasGameMode : public AGameMode`  
_L12-19_
- reflection: `UCLASS(BlueprintType)`
- inherits: `AGameMode`
- L16 _private prototype_ `ANetworkPredictionExtrasGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L18 _private function_ `virtual bool AllowCheats(APlayerController* P)`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/NetworkPredictionExtrasGameState.h` (Public)


#### class `ANetworkPredictionExtrasGameState`  
`class ANetworkPredictionExtrasGameState : public AGameState`  
_L12-24_
- reflection: `UCLASS(BlueprintType)`
- inherits: `AGameState`
- L16 _private prototype_ `ANetworkPredictionExtrasGameState() = default;`
- L18 _private function_ `virtual void BeginPlay() override`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/NetworkPredictionExtrasModule.h` (Public)


#### class `INetworkPredictionExtrasModule`  
`class INetworkPredictionExtrasModule : public IModuleInterface`  
_L9-23_
- inherits: `IModuleInterface`
- L14 _public function_ `static inline INetworkPredictionExtrasModule& Get()`
- L19 _public function_ `static inline bool IsAvailable()`

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/ParametricMovement.h` (Public)


#### struct `FSimpleParametricMotion`  
`struct FSimpleParametricMotion`  
_L19-39_
- reflection: `USTRUCT(BlueprintType)`
- desc: Extremely simple struct for defining parametric motion. This is editable in UParametricMovementComponent's defaults, and also used by the simulation code.
- L24 _public prototype_ `void MapTimeToTransform(const float InPosition, FTransform& OutTransform) const;` — Actually turn the given position into a transform. Again, should be static and not conditional on changing state outside of the network sim
- L27 _public prototype_ `void AdvanceParametricTime(const float InPosition, const float InPlayRate, float &OutPosition, float& OutPlayRate, const float DeltaTimeSeconds) const;` — Advance parametric time. This is meant to do simple things like looping/reversing etc.
- L30 _public member_ `FVector ParametricDelta = FVector(0.f, 0.f, 500.f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ParametricMovement)`
- L33 _public member_ `float MinTime = -1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ParametricMovement)`
- L36 _public member_ `float MaxTime = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ParametricMovement)`
- L38 _public member_ `FTransform CachedStartingTransform;`

#### struct `FParametricInputCmd`  
`struct FParametricInputCmd`  
_L46-67_
- desc: State the client generates
- L49 _public member_ `TOptional<float> PlayRate;` — Input Playrate. This being set can be thought of "telling the simulation what its new playrate should be"
- L51 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L56 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`

#### struct `FParametricSyncState`  
`struct FParametricSyncState`  
_L70-94_
- desc: State we are evolving frame to frame and keeping in sync
- L72 _public member_ `float Position=0.f;`
- L73 _public member_ `float PlayRate=1.f;`
- L75 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L81 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L87 _public function_ `void Interpolate(const FParametricSyncState* From, const FParametricSyncState* To, float PCT)`
- L93 _public prototype_ `bool ShouldReconcile(const FParametricSyncState& AuthorityState) const;`

#### struct `FParametricAuxState`  
`struct FParametricAuxState`  
_L98-117_
- desc: Auxiliary state that is input into the simulation. Doesn't change during the simulation tick. (It can change and even be predicted but doing so will trigger more bookeeping, etc. Changes will happen "next tick")
- L100 _public member_ `float Multiplier=1;`
- L101 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L106 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L111 _public function_ `void Interpolate(const FParametricAuxState* From, const FParametricAuxState* To, float PCT)`
- L116 _public prototype_ `bool ShouldReconcile(const FParametricAuxState& AuthorityState) const;`

#### class `FParametricMovementSimulation`  
`class FParametricMovementSimulation : public FBaseMovementSimulation`  
_L123-131_
- inherits: `FBaseMovementSimulation`
- desc: The actual movement simulation
- L127 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<ParametricMovementBufferTypes>& Input, const TNetSimOutput<ParametricMovementBufferTypes>& Output);`
- L130 _public member_ `const FSimpleParametricMotion* Motion = nullptr;` — Pointer to our static mapping of time->position

#### class `UParametricMovementComponent`  
`class UParametricMovementComponent : public UBaseMovementComponent`  
_L143-197_
- reflection: `UCLASS(BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UBaseMovementComponent`
- L149 _public prototype_ `UParametricMovementComponent();`
- L151 _public prototype_ `virtual void BeginPlay() override;`
- L152 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L154 _public prototype_ `void InitializeSimulationState(FParametricSyncState* SyncState, FParametricAuxState* AuxState);`
- L155 _public prototype_ `void ProduceInput(const int32 SimTimeMS, FParametricInputCmd* Cmd);`
- L156 _public prototype_ `void RestoreFrame(const FParametricSyncState* SyncState, const FParametricAuxState* AuxState);`
- L157 _public prototype_ `void FinalizeFrame(const FParametricSyncState* SyncState, const FParametricAuxState* AuxState);`
- L160 _public prototype_ `void EnableInterpolationMode(bool bValue);` — `UFUNCTION(BlueprintCallable, Category="Networking")`
- L164 _protected prototype_ `void InitializeNetworkPredictionProxy() override;`
- L165 _protected member_ `TPimplPtr<FParametricMovementSimulation> OwnedParametricMovementSimulation;`
- L177 _protected member_ `bool bDisableParametricMovementSimulation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ParametricMovement)` — Disables starting the simulation. For development/testing ease of use
- L180 _protected member_ `FSimpleParametricMotion ParametricMotion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ParametricMovement, meta=(ExposeOnSpawn=true))`
- L183 _protected member_ `bool bEnableDependentSimulation = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ParametricMovementNetworking)`
- L186 _protected member_ `bool bEnableInterpolation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ParametricMovementNetworking)`
- L190 _protected member_ `bool bEnableForceNetUpdate = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ParametricMovementNetworking)` — Calls ForceNetUpdate every frame. Has slightly different behavior than a very high NetUpdateFrequency
- L194 _protected member_ `float ParentNetUpdateFrequency = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ParametricMovementNetworking)` — Sets NetUpdateFrequency on parent. This is editable on the component and really just meant for use during development/test maps
- L196 _protected member_ `TOptional<float> PendingPlayRate = 1.f;`

#### Free symbols / members of external scopes

- L120 _typedef_ `using ParametricMovementBufferTypes = TNetworkPredictionStateTypes<FParametricInputCmd, FParametricSyncState, FParametricAuxState>;` — BufferTypes for ParametricMovement

### `Plugins/Runtime/NetworkPredictionExtras/Source/NetworkPredictionExtras/Public/Springs.h` (Public)


#### struct `FSpring`  
`struct FSpring`  
_L12-75_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public function_ `FSpring() : LocalPosition(ForceInitToZero) , LocalDirection(ForceInitToZero) , TraceChannel(ECC_Visibility) , Stiffness(0.0f) , DampingStrength(0.0f) , RaycastLength(0.0f) , NaturalLength(0.0f) , PreviousLength(0.0f)`
- L29 _public function_ `bool operator==(const FSpring& Spring) const`
- L43 _public member_ `FVector LocalPosition;` — `UPROPERTY(BlueprintReadWrite, Category="Spring")` — Position of spring relative to actor, raycast starts here and force is applied at this position.
- L47 _public member_ `FVector LocalDirection;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Direction of spring force applied to body.
- L51 _public member_ `TEnumAsByte<ECollisionChannel> TraceChannel;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Trace channel of raycast
- L55 _public member_ `float Stiffness;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Strength of spring force.
- L59 _public member_ `float DampingStrength;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Strength of damping term.
- L63 _public member_ `float RaycastLength;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Lenght of raycast.
- L67 _public member_ `float NaturalLength;` — `UPROPERTY(BlueprintReadWrite, Category = "Spring")` — Natural length of spring when it is not stretched/compressed.
- L69 _public function_ `float GetPreviousLength() const`
- L70 _public function_ `void SetPreviousLength(float InLength)`
- L71 _public function_ `void ResetState()`
- L74 _private member_ `float PreviousLength;` — Length of spring from last step.

#### Free symbols / members of external scopes

- L9 _prototype_ `static FArchive& operator<<(FArchive& Ar, FSpring& Spring);`
- L77 _function_ `static FArchive& operator<<(FArchive& Ar, FSpring& Spring)`
