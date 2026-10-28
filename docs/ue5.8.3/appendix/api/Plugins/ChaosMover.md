# Plugins / ChaosMover

- module root: `Plugins/Experimental/ChaosMover/Source/ChaosMover`
- headers: 51; symbols: 1505
- symbol kinds: class=52, delegate=8, enum=18, enumerator=35, externvar=15, function=120, macro=18, member=529, namespace=29, prototype=602, struct=75, typedef=3, variable=1
- PrivateDependencyModuleNames: CoreUObject, DeveloperSettings, Engine, MotionWarping
- PublicDependencyModuleNames: Core, GameplayTags, InputCore, Mover, NetCore, Water

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Private/Backends/ChaosMoverAsyncCallback.h` (Private)


#### struct `UE::ChaosMover::FAsyncCallbackInput`  
`struct FAsyncCallbackInput : public Chaos::FSimCallbackInput`  
_L13-27_
- inherits: `Chaos::FSimCallbackInput`
- L15 _public member_ `TArray<FSimulationInputData> InputData;`
- L16 _public member_ `TArray<TWeakObjectPtr<UChaosMoverBackendComponent>> Backends;`
- L17 _public member_ `Chaos::FPhysicsSolver* PhysicsSolver;`
- L18 _public member_ `int32 NetworkPhysicsTickOffset;`
- L20 _public function_ `void Reset()`

#### struct `UE::ChaosMover::FAsyncCallbackOutput`  
`struct FAsyncCallbackOutput : public Chaos::FSimCallbackOutput`  
_L29-43_
- inherits: `Chaos::FSimCallbackOutput`
- L31 _public member_ `TArray<FSimulationOutputData> OutputData;`
- L32 _public member_ `TArray<TWeakObjectPtr<UChaosMoverBackendComponent>> Backends;`
- L33 _public member_ `TArray<FMoverTimeStep> TimeStep;`
- L35 _public member_ `TArray<FMoverSyncState> RollbackNewSyncState;` — Sync state at the rollback destination frame (NewBaseTimeStep), populated only when bIsFirstResimFrame is true.
- L36 _public function_ `void Reset()`

#### class `UE::ChaosMover::FAsyncCallback`  
`class FAsyncCallback : public Chaos::TSimCallbackObject< FAsyncCallbackInput, FAsyncCallbackOutput, Chaos::ESimCallbackOptions::InjectInputsExternal | Chaos::ESimCallbackOptions::ProcessInputsInternal | Chaos::ESimCallbackOptions::Presimulate | Chaos::ESimCallbackOptions::ContactModification | Chaos::ESimCallbackOptions::PostSolve | Chaos::ESimCallbackOptions::Rewind>`  
_L45-79_
- inherits: `Chaos::TSimCallbackObject<FAsyncCallbackInput,FAsyncCallbackOutput,Chaos::ESimCallbackOptions::InjectInputsExternal|Chaos::ESimCallbackOptions::ProcessInputsInternal|Chaos::ESimCallbackOptions::Presimulate|Chaos::ESimCallbackOptions::ContactModification|Chaos::ESimCallbackOptions::PostSolve|Chaos::ESimCallbackOptions::Rewind>`
- L56 _public function_ `void SetSubsystem(UChaosMoverSubsystem* InSubsystem)`
- L62 _protected prototype_ `virtual void OnInjectInputs_External(int32 PhysicsStep, int32 NumSteps) override;`
- L63 _protected prototype_ `virtual void OnProcessInputs_Internal(int32 PhysicsStep) override;`
- L64 _protected prototype_ `virtual void OnPreSimulate_Internal() override;`
- L65 _protected prototype_ `virtual void OnContactModification_Internal(Chaos::FCollisionContactModifier& Modifier) override;`
- L66 _protected prototype_ `virtual void OnPostSolve_Internal() override;`
- L68 _protected prototype_ `void GetCurrentMoverTimeStep(const FAsyncCallbackInput* AsyncInput, FMoverTimeStep& OutMoverTimeStep) const;`
- L72 _protected prototype_ `const TArray<int32, TInlineAllocator<64>>* DetermineResimulatedBackendIndices(const TArray<TWeakObjectPtr<UChaosMoverBackendComponent>>& InBackends);` — With bubble resim enabled, determines which backends should resimulate and returns a pointer to ResimulatedBackendIndices Only call this function during resim frames
- L76 _protected member_ `TArray<int32, TInlineAllocator<64>> ResimulatedBackendIndices;` — Array of resimulated backend indices. This array is used only in the resim case. During a resim frame, it is reset and filled in OnProcessInputs_Internal and reused in subsequent callbacks on that same frame, such as OnPreSimulate_Internal
- L78 _protected member_ `UChaosMoverSubsystem* Subsystem = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ChaosMover` (scope `UE`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Private/Backends/ChaosMoverSubsystem.h` (Private)


#### class `UChaosMoverSubsystem`  
`class UChaosMoverSubsystem : public UWorldSubsystem`  
_L21-47_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L26 _public prototype_ `void Register(TWeakObjectPtr<UChaosMoverBackendComponent> Backend);`
- L27 _public prototype_ `void Unregister(TWeakObjectPtr<UChaosMoverBackendComponent> Backend);`
- L30 _public prototype_ `TArray<TWeakObjectPtr<UChaosMoverBackendComponent>>& ValidateAndGetBackends();` — Remove invalid backends before returning
- L32 _public prototype_ `FMoverTimeStep GetMoverTimeStep() const;`
- L33 _public prototype_ `int32 GetNetworkPhysicsTickOffset() const;`
- L36 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;`
- L37 _protected prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L38 _protected prototype_ `virtual void Deinitialize() override;`
- L40 _protected prototype_ `void OnPostPhysicsTick(FChaosScene* Scene);`
- L42 _protected member_ `TArray<TWeakObjectPtr<UChaosMoverBackendComponent>> Backends;`
- L44 _protected member_ `FDelegateHandle InjectInputsExternalCallbackHandle;`
- L45 _protected member_ `FDelegateHandle PhysScenePostTickCallbackHandle;`
- L46 _protected member_ `class UE::ChaosMover::FAsyncCallback* AsyncCallback = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ChaosMover` (scope `UE`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Private/Backends/NetworkChaosMoverData.h` (Private)


#### struct `FNetworkChaosMoverInputData`  
`struct FNetworkChaosMoverInputData : public FNetworkPhysicsData`  
_L11-43_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- L16 _public member_ `FMoverInputCmdContext InputCmdContext;` — `UPROPERTY()`
- L19 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L22 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L25 _public prototype_ `virtual void DecayData(float DecayAmount) override;` — Decay input during resimulation and forward prediction
- L28 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L31 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two inputs data
- L34 _public prototype_ `virtual void MergeData(const FNetworkPhysicsData& FromData) override;` — Merge data into this input
- L37 _public prototype_ `virtual void ValidateData(const UActorComponent* NetworkComponent) override;` — Check input data is valid - Input is send from client to server, no need to make sure it's reasonable
- L39 _public prototype_ `virtual bool CompareData(const FNetworkPhysicsData& PredictedData) override;`
- L42 _public prototype_ `virtual const FString DebugData() override;` — Return string with debug information

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkChaosMoverInputData> : public TStructOpsTypeTraitsBase2<FNetworkChaosMoverInputData>`  
_L46-52_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkChaosMoverInputData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L49-51_

#### struct `FNetworkChaosMoverStateData`  
`struct FNetworkChaosMoverStateData : public FNetworkPhysicsData`  
_L55-78_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsData`
- L60 _public member_ `FMoverSyncState SyncState;` — `UPROPERTY()`
- L63 _public prototype_ `virtual void ApplyData(UActorComponent* NetworkComponent) const override;` — Apply the data onto the network physics component
- L66 _public prototype_ `virtual void BuildData(const UActorComponent* NetworkComponent) override;` — Build the data from the network physics component
- L69 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize data function that will be used to transfer the struct across the network
- L72 _public prototype_ `virtual void InterpolateData(const FNetworkPhysicsData& MinData, const FNetworkPhysicsData& MaxData) override;` — Interpolate the data in between two inputs data
- L74 _public prototype_ `virtual bool CompareData(const FNetworkPhysicsData& PredictedData) override;`
- L77 _public prototype_ `virtual const FString DebugData() override;` — Return string with debug information

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNetworkChaosMoverStateData> : public TStructOpsTypeTraitsBase2<FNetworkChaosMoverStateData>`  
_L81-87_
- inherits: `TStructOpsTypeTraitsBase2<FNetworkChaosMoverStateData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L84-86_

#### struct `UE::ChaosMover::FNetworkDataTraits`  
`struct FNetworkDataTraits`  
_L91-95_
- L93 _public typedef_ `using InputsType = FNetworkChaosMoverInputData;`
- L94 _public typedef_ `using StatesType = FNetworkChaosMoverStateData;`

#### Free symbols / members of external scopes

- L50 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon2e77a8550103`)
- L85 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon2e77a8550203`)
- L89 _namespace_ `namespace UE`
- L89 _namespace_ `namespace ChaosMover` (scope `UE`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Private/Character/ChaosCharacterSimUtils.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace ChaosMover` (scope `UE`)
- L18 _prototype_ `void ProcessCharacterInputs(FChaosMoverPreSimContext& Context);` (scope `UE::ChaosMover`) — Processes character movement inputs for the current tick: coerces invalid input to a zero directional intent, consumes any pending mode-transition request by queuing it on the simulation, and applies or removes per-mode speed/acceleration overrides. No-ops if the Simulation pointer in Context cannot be cast to UChaosMoverSimulation.
- L25 _prototype_ `void UpdateCurrentFloor(FChaosMoverPreSimContext& Context, IChaosCharacterMovementModeInterface& CharacterInterface);` (scope `UE::ChaosMover`) — Conditionally runs the character floor sweep and stores the result in the blackboard. Runs unconditionally when bEnablePreSimGroundCheck is set, or on the first frame of resimulation (the blackboard is invalidated on rollback so the result must be refreshed).
- L33 _prototype_ `void ReconcileParticleVelocity(FChaosMoverPostSimContext& Context, IChaosCharacterMovementModeInterface* CharacterInterface);` (scope `UE::ChaosMover`) — Reconciles particle velocity with game-side sync state. Drives the particle from the sync state in normal simulation; reads back from the particle for non-resim sim proxies. CharacterInterface may be null -- null is treated as "no upright opinion": linear velocity is still applied, angular velocity is left to physics and reflected back into sync state.
- L40 _prototype_ `void ApplyGroundAndWaterResults(FChaosMoverPostSimContext& Context, IChaosCharacterMovementModeInterface* CharacterInterface);` (scope `UE::ChaosMover`) — Propagates floor and water sensing results into output data and assigns the movement base on the sync state when in a ground mode with a blocking floor hit. No-ops if CharacterInterface is null.
- L47 _prototype_ `void ConfigureCharacterGroundConstraint( FChaosMoverPostSimContext& Context, IChaosCharacterMovementModeInterface* CharacterInterface, IChaosCharacterConstraintMovementModeInterface* ConstraintInterface);` (scope `UE::ChaosMover`) — Configures the character ground constraint for the next physics tick, using the sync state and floor result to compute target position and facing deltas. No-ops if either interface pointer is null or ShouldEnableConstraint returns false.

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Private/Character/Modes/ChaosSmoothWalkingState.h` (Private)


#### struct `FChaosSmoothWalkingState`  
`struct FChaosSmoothWalkingState : public FMoverDataStructBase`  
_L18-48_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Internal state data for Chaos smooth walking. Stored in the SyncStateCollection to remain stable across rollback/resim and replication.
- L22 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L23 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L24 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L25 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L26 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L27 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L31 _public member_ `FVector SpringVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosMover|Experimental")` — Velocity of internal velocity spring
- L35 _public member_ `FVector SpringAcceleration = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosMover|Experimental")` — Acceleration of internal velocity spring
- L39 _public member_ `FVector IntermediateVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosMover|Experimental")` — Intermediate velocity which the velocity spring tracks as a target
- L43 _public member_ `FQuat IntermediateFacing = FQuat::Identity;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosMover|Experimental")` — Intermediate facing direction when using a double spring
- L47 _public member_ `FVector IntermediateAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "ChaosMover|Experimental")` — Angular velocity of the intermediate spring when using a double spring

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Backends/ChaosMoverBackend.h` (Public)


#### class `UChaosMoverBackendComponent`  
`class UChaosMoverBackendComponent : public UActorComponent, public IMoverBackendLiaisonInterface`  
_L28-185_
- reflection: `UCLASS(MinimalAPI, Within = MoverComponent)`
- inherits: `UActorComponent,IMoverBackendLiaisonInterface`
- L33 _public prototype_ `UChaosMoverBackendComponent();`
- L35 _public prototype_ `virtual void InitializeComponent() override;`
- L36 _public prototype_ `virtual void UninitializeComponent() override;`
- L37 _public prototype_ `virtual void BeginPlay() override;`
- L38 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L41 _public prototype_ `virtual bool IsAsync() const override;` — IMoverBackendLiaisonInterface
- L42 _public prototype_ `virtual bool IsFixedDt() const override;`
- L43 _public prototype_ `virtual bool ShouldResim() const override;`
- L44 _public prototype_ `virtual float GetEventSchedulingMinDelaySeconds() const override;`
- L45 _public prototype_ `virtual FMoverTime GetScheduledNetworkTime(const FMoverTime& Time) const override;`
- L46 _public prototype_ `virtual double GetCurrentSimTimeMs();`
- L47 _public prototype_ `virtual int32 GetCurrentSimFrame();`
- L49 _public prototype_ `virtual void ProduceInputData(int32 PhysicsStep, int32 NumSteps, const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationInputData& InputData);`
- L50 _public prototype_ `virtual void ConsumeOutputData(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationOutputData& OutputData);`
- L51 _public prototype_ `virtual void FinalizeFrame(double ResultsTimeInMs);`
- L52 _public prototype_ `virtual void OnSimulationRollback(const FMoverSyncState& NewSyncState, const FMoverTimeStep& NewBaseTimeStep, const FMoverTimeStep& InPreRollbackTimeStep) override;`
- L54 _public prototype_ `UChaosMoverSimulation* GetSimulation();`
- L55 _public prototype_ `const UChaosMoverSimulation* GetSimulation() const;`
- L57 _public function_ `const FMoverTimeStep& GetPreRollbackTimeStep() const`
- L60 _protected prototype_ `virtual void InitSimulation();`
- L61 _protected prototype_ `virtual void DeinitSimulation();`
- L62 _protected prototype_ `virtual void CreatePhysics();`
- L63 _protected prototype_ `virtual void DestroyPhysics();`
- L65 _protected prototype_ `void CreateCharacterGroundConstraint();`
- L66 _protected prototype_ `void DestroyCharacterGroundConstraint();`
- L68 _protected prototype_ `void CreateActuationConstraint();`
- L69 _protected prototype_ `void DestroyActuationConstraint();`
- L71 _protected prototype_ `virtual void GenerateInput(const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationInputData& InputData);`
- L72 _protected prototype_ `virtual void GenerateServerInput(const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationInputData& InputData);`
- L74 _protected prototype_ `UMoverComponent& GetMoverComponent() const;`
- L75 _protected prototype_ `Chaos::FPhysicsSolver* GetPhysicsSolver() const;`
- L76 _protected prototype_ `Chaos::FPhysicsObject* GetPhysicsObject() const;`
- L77 _protected prototype_ `Chaos::FPBDRigidParticle* GetControlledParticle() const;`
- L80 _protected prototype_ `virtual void HandleUpdatedComponentPhysicsStateChanged(UPrimitiveComponent* ChangedComponent, EComponentPhysicsStateChange StateChange);` — `UFUNCTION()`
- L83 _protected prototype_ `void HandleOwningPawnControllerChanged_Server(APawn* OwnerPawn, AController* OldController, AController* NewController);` — `UFUNCTION()`
- L85 _protected member_ `TSubclassOf<UChaosMoverSimulation> SimulationClass;`
- L88 _protected member_ `TObjectPtr<UNetworkPhysicsComponent> NetworkPhysicsComponent;` — `UPROPERTY(Transient)`
- L91 _protected member_ `TObjectPtr<UNullMovementMode> NullMovementMode;` — `UPROPERTY(Transient)`
- L94 _protected member_ `TObjectPtr<UImmediateMovementModeTransition> ImmediateModeTransition;` — `UPROPERTY(Transient)`
- L97 _protected member_ `TObjectPtr<UChaosMoverSimulation> Simulation;` — `UPROPERTY(Transient)`
- L99 _protected member_ `UE::Mover::FSimulationOutputRecord SimOutputRecord;`
- L102 _protected member_ `FMoverTimeStep PreRollbackTimeStep;` — Last forward-simulated (non-resim) timestep simulated before the latest rollback; passed as PreRollbackTimeStep in OnSimulationRollback.
- L105 _protected member_ `TUniquePtr<Chaos::FCharacterGroundConstraint> CharacterGroundConstraint;` — Character ground constraint, for moving on ground like characters
- L108 _protected member_ `FPhysicsConstraintHandle ActuationConstraintHandle;` — General purpose joint constraint, for moving the controlled component physically
- L109 _protected member_ `FConstraintInstance ActuationConstraintInstance;`
- L110 _protected member_ `FPhysicsUserData ActuationConstraintPhysicsUserData;`
- L112 _protected member_ `FTransform TransformOnInit;`
- L114 _protected member_ `bool bIsUsingAsyncPhysics = false;`
- L115 _protected member_ `bool bWantsDestroySim = false;`
- L116 _protected member_ `bool bWantsCreateSim = true;`
- L119 _protected prototype_ `void InjectInstantMovementEffectsIntoSim(UE::ChaosMover::FSimulationInputData& OutInputData);` — Transfers queued instant movement effects from the simulation to the simulation input (via networked input or local sim input).
- L123 _protected prototype_ `void InjectInstantMovementEffectsIntoInput(UE::ChaosMover::FSimulationInputData& OutInputData, const TArray<FScheduledInstantMovementEffect>& Effects);` — Transfers the given instant movement effects to the (networked) simulation input. This is used in the input producing case.
- L127 _protected prototype_ `void InjectInstantMovementEffectsIntoLocalSimInput(const TArray<FScheduledInstantMovementEffect>& Effects);` — Transfers the given instant movement effects to the simulation directly, bypassing the networked input. This is used in the non input producing case.
- L133 _protected prototype_ `void InjectInstantMovementEffectsAsActions(const TArray<FScheduledInstantMovementEffect>& Effects);` — Routes the given instant movement effects through the UNetworkPhysicsComponent sim action system using Proposed auth style. Called by InjectInstantMovementEffectsIntoSim when ChaosMover.Networking.NetworkInstantMovementEffectsWithSimActions is true. All roles independently enqueue the same action (having detected the condition from GetLastInputCmd() in PostSim).
- L136 _protected prototype_ `void InjectLayeredMovesIntoSim(UE::ChaosMover::FSimulationInputData& OutInputData);` — Transfers queued layered moves from the simulation to the simulation input (via networked input or local sim input).
- L140 _protected prototype_ `void InjectLayeredMovesIntoInput(UE::ChaosMover::FSimulationInputData& OutInputData, const TArray<FScheduledLayeredMove>& Moves);` — Transfers the given layered moves to the (networked) simulation input. This is used in the input producing case.
- L144 _protected prototype_ `void InjectLayeredMovesIntoLocalSimInput(const TArray<FScheduledLayeredMove>& Moves);` — Transfers the given layered moves to the simulation directly, bypassing the networked input. This is used in the non input producing case.
- L149 _protected prototype_ `void InjectLayeredMovesAsActions(const TArray<FScheduledLayeredMove>& Moves);` — Routes the given layered moves through the UNetworkPhysicsComponent sim action system using Proposed auth style. Called by InjectLayeredMovesIntoSim when ChaosMover.Networking.NetworkMovesWithSimActions is true. All roles independently enqueue the same action (having detected the condition from GetLastInputCmd() in PostSim).
- L152 _protected prototype_ `void QueueLayeredMoveInstance(TSharedPtr<FLayeredMoveInstance> Move);` — GT-callable: enqueue a FLayeredMoveInstance into the simulation-level queue for injection on the next tick.
- L155 _protected prototype_ `void InjectLayeredMoveInstancesIntoSim(UE::ChaosMover::FSimulationInputData& OutInputData);` — Transfers queued FLayeredMoveInstance moves from the simulation to the simulation input (via networked input or local sim input).
- L158 _protected prototype_ `void InjectLayeredMoveInstancesIntoInput(UE::ChaosMover::FSimulationInputData& OutInputData, const TArray<FChaosScheduledLayeredMoveInstance>& ScheduledInstances);` — Transfers the given scheduled FLayeredMoveInstance moves to the (networked) simulation input.
- L161 _protected prototype_ `void InjectLayeredMoveInstancesIntoLocalSimInput(const TArray<FChaosScheduledLayeredMoveInstance>& ScheduledInstances);` — Transfers the given scheduled FLayeredMoveInstance moves to the simulation directly, bypassing networked input.
- L167 _protected prototype_ `void InjectLayeredMoveInstancesAsActions(const TArray<FChaosScheduledLayeredMoveInstance>& ScheduledInstances);` — Routes the given scheduled FLayeredMoveInstance activations through the UNetworkPhysicsComponent sim action system using Proposed auth style. Called by InjectLayeredMoveInstancesIntoSim when ChaosMover.Networking.NetworkMovesWithSimActions is true. All roles independently enqueue the same action (having detected the condition from GetLastInputCmd() in PostSim).
- L171 _private prototype_ `void ConvertToSerializable(const TArray<FScheduledInstantMovementEffect>& ScheduledInstantMovementEffects, FChaosNetInstantMovementEffectsQueue& OutNetInstantMovementEffectsQueue);`
- L172 _private prototype_ `void ConvertToSerializable(const TArray<FScheduledLayeredMove>& ScheduledLayeredMoves, FChaosNetLayeredMovesQueue& OutNetLayeredMovesQueue);`
- L173 _private prototype_ `void ConvertToSerializable(const TArray<FChaosScheduledLayeredMoveInstance>& ScheduledMoveInstances, FChaosNetLayeredMoveInstancesQueue& OutNetQueue);`
- L177 _private prototype_ `void CullPastDueLocalSimInputMoves();` — Removes past-due layered move entries from LocalSimInput so they are not re-marshalled to the PT on every tick. Called once per ProduceInputData before the inject calls.
- L180 _private prototype_ `uint8 GetNextUniqueSimCommandID();` — Returns the next unique ID used to prevent multiple application of the same sim command
- L184 _private member_ `uint8 NextUniqueSimCommandID = 0xFF;` — Unique ID counter for sim commands. Unique IDs need to be generated because input can be repeated and we need to prevent multiple application of a given command only queued once.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosCompositeMovementMode.h` (Public)


#### class `UChaosCompositeMovementMode`  
`class UChaosCompositeMovementMode : public UChaosMovementMode`  
_L29-64_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementMode`
- desc: UChaosCompositeMovementMode: a ChaosMover movement mode that composes a UChaosMoverSourceBase (what velocity to produce) with a UChaosMoveExecutorBase (how to apply it to the physics simulation). This separates move generation from physics application so that both can be configured and swapped independently. All simulation methods are async-safe — no AActor or UActorComponent access. When MoveSource::IsFinished() returns true, the mode automatically transitions to NextModeName (if set). The Transitions array can be used for additional conditions. If the executor implements IChaosCharacterMovementModeInterface and/or IChaosCharacterConstraintMovementModeInterface, CollectSimulationInterfaces automatically exposes those to the simulation -- no subclassing required.
- L34 _public prototype_ `UChaosCompositeMovementMode(const FObjectInitializer& ObjectInitializer);`
- L38 _public member_ `TObjectPtr<UChaosMoverSourceBase> MoveSource;` — `UPROPERTY(EditAnywhere, Instanced, Category = Mover)` — The source that produces a FProposedMove each tick.
- L42 _public member_ `TObjectPtr<UChaosMoveExecutorBase> MoveExecutor;` — `UPROPERTY(EditAnywhere, Instanced, Category = Mover)` — Applies the proposed move to the Chaos physics simulation state each tick.
- L46 _public member_ `FName NextModeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Mode to transition to when MoveSource::IsFinished() returns true. NAME_None = no auto-transition.
- L48 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L49 _public prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L51 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L52 _public prototype_ `virtual void Deactivate(const FMoverEventContext& Context, FName InNextModeName, const FMoverSimContext& SimContext) override;`
- L54 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L55 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L57 _public prototype_ `virtual void CollectSimulationInterfaces(FChaosMoverSimulationInterfaceCache& OutCache) override;`
- L63 _private member_ `bool bMoveSourceEnded = false;` — Set when MoveSource->OnEnd_Async has been called, cleared on Activate. Prevents OnEnd_Async from being called more than once per activation when IsFinished() returns true but no mode transition is configured.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosLayeredMoveSource.h` (Public)


#### class `UChaosLayeredMoveSource`  
`class UChaosLayeredMoveSource : public UChaosMoverSourceBase`  
_L23-37_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMoverSourceBase`
- desc: UChaosLayeredMoveSource: a UChaosMoverSourceBase that drives move generation from a single FLayeredMoveBase instance stored as an instanced struct property. All four source lifecycle methods (OnStart_Async, GenerateMove_Async, IsFinished, OnEnd_Async) are fully delegated to the underlying FLayeredMoveBase async API, so subclasses of FLayeredMoveBase can be configured and swapped in the editor without subclassing this object.
- L30 _public member_ `TInstancedStruct<FLayeredMoveBase> LayeredMove;` — `UPROPERTY(EditAnywhere, Category = Mover)` — The layered move that drives velocity generation.
- L32 _public prototype_ `virtual void OnStart_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime) override;`
- L33 _public prototype_ `virtual void GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;`
- L34 _public prototype_ `virtual bool IsFinished(double CurrentSimTimeMs) const override;`
- L35 _public prototype_ `virtual void OnEnd_Async(UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs) override;`
- L36 _public prototype_ `virtual void AppendMontageOutputEntry(TArray<FMoverSimDrivenMontageEntry>& OutEntries, const FMoverTimeStep& TimeStep) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoveExecutorBase.h` (Public)


#### class `UChaosMoveExecutorBase`  
`class UChaosMoveExecutorBase : public UObject`  
_L33-71_
- reflection: `UCLASS(Abstract, MinimalAPI, EditInlineNew, DefaultToInstanced)`
- inherits: `UObject`
- desc: Abstract base class for move executors in ChaosMover. A move executor is responsible for applying a FProposedMove to the physics simulation state — computing target delta positions, updating the sync state, and handling any surface interaction. It decouples the "how to apply movement" concern from the mode hierarchy, allowing physics behaviors (walking, free-move, etc.) to be composed independently of move generation. All methods must be safe to call from the physics simulation thread — no access to AActor or UActorComponent is permitted. Concrete subclasses that support the Chaos character ground constraint should additionally implement IChaosCharacterMovementModeInterface and/or IChaosCharacterConstraintMovementModeInterface. UChaosCompositeMovementMode automatically exposes those interfaces to the simulation via CollectSimulationInterfaces.
- L43 _public function_ `virtual void OnModeRegistered(const FName ModeName)` — Called by the owning mode during its OnRegistered, on the game thread. Subclasses may override to perform initialization that requires game-thread access (e.g. reading character mesh offset, finding shared settings).
- L49 _public function_ `virtual void OnModeUnregistered()` — Called by the owning mode during its OnUnregistered, on the game thread. Subclasses may override to release any references acquired in OnModeRegistered.
- L55 _public function_ `virtual void ExecuteMove_Async( const FSimulationTickParams& Params, FMoverTickEndData& OutputState)` — Applies Params.ProposedMove to the simulation output state. Thread-safe — no AActor or UActorComponent access.
- L64 _public function_ `virtual void SetSimulation(UChaosMoverSimulation* InSimulation)` — Propagates the simulation reference so that the executor can perform physics queries (e.g. floor sweeps) when needed. Called by the owning mode during OnRegistered and cleared during OnUnregistered.
- L70 _protected member_ `TObjectPtr<UChaosMoverSimulation> Simulation;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMovementMode.h` (Public)


#### enum `EChaosMoverIgnoredCollisionMode`  
`enum class EChaosMoverIgnoredCollisionMode : uint8`  
_L17-21_
- reflection: `UENUM()`
- L19 _public enumerator_ `EnableCollisionsWithIgnored`
- L20 _public enumerator_ `DisableCollisionsWithIgnored`

#### class `UChaosMovementMode`  
`class UChaosMovementMode : public UBaseMovementMode`  
_L27-73_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UBaseMovementMode`
- desc: Base class for all Chaos movement modes
- L32 _public prototype_ `UChaosMovementMode(const FObjectInitializer& ObjectInitializer);`
- L35 _public function_ `const UChaosMoverSimulation* GetSimulation() const` — `UFUNCTION(BlueprintPure, Category = ChaosMover)`
- L40 _public prototype_ `void SetSimulation(UChaosMoverSimulation* InSimulation);`
- L43 _public function_ `virtual bool UsesMovementBasisTransform() const` — Whether this movement mode is relative to a basis transform
- L50 _public function_ `virtual bool CanTeleport(const FTransform& TargetTransform, const FMoverSyncState& CurrentSyncState) const` — Whether the mode allows teleportation to the target transform This is for mode specific teleportation tests, in addition to those already done prior to this check
- L55 _public function_ `virtual void ModifyContacts(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const UE::ChaosMover::FSimulationOutputData& OutputData, Chaos::FCollisionContactModifier& Modifier) const`
- L62 _public prototype_ `virtual void CollectSimulationInterfaces(FChaosMoverSimulationInterfaceCache& OutCache);` — Populate OutCache with simulation interface pointers (IChaosPreSimulationTickInterface, IChaosPostSimulationTickInterface) this mode can service. The base implementation casts 'this'; composite overrides also try the executor.
- L65 _public member_ `EChaosMoverIgnoredCollisionMode IgnoredCollisionMode = EChaosMoverIgnoredCollisionMode::DisableCollisionsWithIgnored;` — `UPROPERTY(EditAnywhere, Category = "Collision Settings")`
- L68 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L72 _protected member_ `UChaosMoverSimulation* Simulation;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMovementModeTransition.h` (Public)


#### class `UChaosMovementModeTransition`  
`class UChaosMovementModeTransition : public UBaseMovementModeTransition`  
_L15-45_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UBaseMovementModeTransition`
- desc: Base class for all Chaos movement mode transitions
- L20 _public prototype_ `UChaosMovementModeTransition(const FObjectInitializer& ObjectInitializer);`
- L23 _public function_ `const UChaosMoverSimulation* GetSimulation() const` — `UFUNCTION(BlueprintPure, Category = ChaosMover)`
- L29 _public function_ `UChaosMoverSimulation* GetSimulation_Mutable()` — `UFUNCTION(BlueprintPure, Category = ChaosMover)`
- L34 _public function_ `void SetSimulation(UChaosMoverSimulation* InSimulation)`
- L40 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L44 _protected member_ `UChaosMoverSimulation* Simulation;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverActionTypes.h` (Public)


#### struct `FChaosMoverLayeredMoveAction`  
`struct FChaosMoverLayeredMoveAction : public FNetworkPhysicsActionPayload`  
_L18-47_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsActionPayload`
- desc: Scheduled action that delivers any FLayeredMoveBase subtype to the ChaosMover simulation via UNetworkPhysicsComponent::EnqueueScheduledAction_External.
- L22 _public function_ `virtual const EActionAuthorStyle GetAuthorStyle() const override`
- L34 _public member_ `EActionAuthorStyle AuthorStyle = EActionAuthorStyle::ProposedAutonomousOnly;` — Controls who authors this action and whether client prediction is active. Predicted / PredictedAutonomousOnly: all eligible roles independently detect the condition (e.g. from GetLastInputCmd() in PostSim) and enqueue the same action. Server-authoritative. Authority: server-only; replicates down to clients without client-side prediction. Proposed / ProposedAutonomousOnly: the client proposes its locally-detected move parameters; the server compares them to its own via FLayeredMoveBase::IsNearlyEqualTo. If accepted, the client's data wins (no resim). If rejected, the server's data wins (client resims). With the default exact-field comparison, this is equivalent to Predicted (server wins on any divergence). Override IsNearlyEqualTo on the FLayeredMoveBase subtype to accept proposals within a tolerance -- a resim-minimizing strategy where the server forgives small client deviations.
- L38 _public member_ `TInstancedStruct<FLayeredMoveBase> Move;` — `UPROPERTY()` — The move to deliver. Supports any FLayeredMoveBase subtype.
- L40 _public function_ `virtual bool IsNearlyEqual(const FNetworkPhysicsActionPayload& Other) const override`

#### struct `FChaosMoverLayeredMoveInstanceAction`  
`struct FChaosMoverLayeredMoveInstanceAction : public FNetworkPhysicsActionPayload`  
_L54-89_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsActionPayload`
- desc: Scheduled action that activates a FLayeredMoveInstance (ULayeredMoveLogic + FLayeredMoveInstancedData) on the ChaosMover simulation via UNetworkPhysicsComponent::EnqueueScheduledAction_External.
- L58 _public function_ `virtual const EActionAuthorStyle GetAuthorStyle() const override`
- L71 _public member_ `EActionAuthorStyle AuthorStyle = EActionAuthorStyle::ProposedAutonomousOnly;` — Controls who authors this action and whether client prediction is active. Predicted / PredictedAutonomousOnly: all eligible roles independently detect the condition (e.g. from GetLastInputCmd() in PostSim) and enqueue the same action. Server-authoritative. Authority: server-only; replicates down to clients without client-side prediction. Proposed / ProposedAutonomousOnly: the client proposes its locally-detected move parameters; the server compares them to its own via FLayeredMoveInstancedData::IsNearlyEqualTo. If accepted, the client's data wins (no resim). If rejected, the server's data wins (client resims). With the default exact-field comparison, this is equivalent to Predicted (server wins on any divergence). Override IsNearlyEqualTo on the FLayeredMoveInstancedData subtype to accept proposals within a tolerance -- a resim-minimizing strategy where the server forgives small client deviations.
- L75 _public member_ `TSubclassOf<ULayeredMoveLogic> MoveLogicClass;` — `UPROPERTY()` — Logic class serialized for re-linking on the simulation thread.
- L79 _public member_ `TInstancedStruct<FLayeredMoveInstancedData> InstancedData;` — `UPROPERTY()` — Per-activation data. Supports any FLayeredMoveInstancedData subtype.
- L81 _public function_ `virtual bool IsNearlyEqual(const FNetworkPhysicsActionPayload& Other) const override`

#### struct `FChaosMoverInstantMovementEffectAction`  
`struct FChaosMoverInstantMovementEffectAction : public FNetworkPhysicsActionPayload`  
_L105-139_
- reflection: `USTRUCT()`
- inherits: `FNetworkPhysicsActionPayload`
- desc: Scheduled action that delivers any FInstantMovementEffect to the ChaosMover simulation via UNetworkPhysicsComponent::EnqueueScheduledAction_External. Callers populate Effect with any FInstantMovementEffect subtype, then call: FChaosMoverInstantMovementEffectAction Action; Action.Effect.InitializeAs<FMyEffect>(...); NetworkPhysicsComponent->EnqueueScheduledAction_External(Action, SourceObject, DelaySeconds, bReliable); The effect is applied on the simulation thread at the scheduled frame, using the same QueueInstantMovementEffect path as locally-triggered effects.
- L109 _public function_ `virtual const EActionAuthorStyle GetAuthorStyle() const override`
- L125 _public member_ `EActionAuthorStyle AuthorStyle = EActionAuthorStyle::ProposedAutonomousOnly;` — Controls who authors this action and whether client prediction is active. Predicted / PredictedAutonomousOnly: all eligible roles independently detect the condition (e.g. from GetLastInputCmd() in PostSim) and enqueue the same action. Server-authoritative. Authority: server-only; replicates down to clients without client-side prediction. Proposed / ProposedAutonomousOnly: the client proposes its locally-detected effect parameters; the server compares them to its own via FInstantMovementEffect::IsNearlyEqualTo. If accepted, the client's data wins (no resim). If rejected, the server's data wins (client resims). With the default exact-field comparison, this is equivalent to Predicted (server wins on any divergence). Override IsNearlyEqualTo on the FInstantMovementEffect subtype to accept proposals within a tolerance -- a resim-minimizing strategy where the server forgives small client deviations.
- L129 _public member_ `TInstancedStruct<FInstantMovementEffect> Effect;` — `UPROPERTY()` — The effect to deliver. Supports any FInstantMovementEffect subtype.
- L131 _public function_ `virtual bool IsNearlyEqual(const FNetworkPhysicsActionPayload& Other) const override`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverBlueprintLibrary.h` (Public)


#### class `UChaosMoverBlueprintLibrary`  
`class UChaosMoverBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-116_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `static bool IsNetworkingMovesWithSimActions();` — `UFUNCTION(BlueprintPure, Category = "ChaosMover|Networking")` — Returns true if layered moves and instanced move activations queued via QueueLayeredMove/QueueLayeredMoveInstance are networked via the sim action system (Proposed style: all roles independently detect from GetLastInputCmd() in PostSim; server-authoritative, cheat-resistant). Returns false if they are embedded in the input cmd (PreSim detection; client-authoritative, co-op path). IMPORTANT: when true, BP must detect conditions from GetLastInputCmd() in PostSim, NOT from the PreSim input.
- L33 _public prototype_ `static bool IsNetworkingInstantMovementEffectsWithSimActions();` — `UFUNCTION(BlueprintPure, Category = "ChaosMover|Networking")` — Returns true if instant movement effects queued via QueueInstantMovementEffect are networked via the sim action system (Proposed style: all roles independently detect from GetLastInputCmd() in PostSim; server-authoritative, cheat-resistant). Returns false if they are embedded in the input cmd (PreSim detection; client-authoritative, co-op path). IMPORTANT: when true, BP must detect conditions from GetLastInputCmd() in PostSim, NOT from the PreSim input.
- L56 _public prototype_ `static void QueueLayeredMoveInstance_Authority(UMoverComponent* MoverComponent, TSubclassOf<ULayeredMoveLogic> MoveLogicClass, UPARAM(ref) FLayeredMoveInstancedData& InstancedData);` — `UFUNCTION(BlueprintCallable, Category = "ChaosMover|Networking", meta = (DefaultToSelf = "MoverComponent"))` — Server-only. Enqueues an instanced layered move activation as an authoritative sim action, replicating it to clients without client-side prediction. Use for server-initiated activations. Requires a ChaosMover backend (UNetworkPhysicsComponent on the owner); asserts in non-shipping builds if that requirement is not met. No-ops silently if called without authority.
- L98 _public prototype_ `static void ScheduleLayeredMoveInstance_Authority(UMoverComponent* MoverComponent, TSubclassOf<ULayeredMoveLogic> MoveLogicClass, UPARAM(ref) FLayeredMoveInstancedData& InstancedData);` — `UFUNCTION(BlueprintCallable, Category = "ChaosMover|Networking", meta = (DefaultToSelf = "MoverComponent"))` — Server-only. Schedules an instanced layered move activation as an authoritative sim action, far enough in the future for all endpoints to apply it on the same physics frame (no correction). Prefer this over QueueLayeredMoveInstance_Authority when frame synchronization matters. Requires a ChaosMover backend (UNetworkPhysicsComponent on the owner); asserts in non-shipping builds if that requirement is not met. No-ops silently if called without authority.

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverConsoleVariables.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ChaosMover` (scope `UE`)
- L9 _namespace_ `namespace CVars` (scope `UE::ChaosMover`)
- L11 _externvar_ `extern bool bForceSingleThreadedGT;` (scope `UE::ChaosMover::CVars`)
- L12 _externvar_ `extern bool bForceSingleThreadedPT;` (scope `UE::ChaosMover::CVars`)
- L13 _externvar_ `extern bool bDrawGroundQueries;` (scope `UE::ChaosMover::CVars`)
- L14 _externvar_ `extern bool bDrawOverlapQueries;` (scope `UE::ChaosMover::CVars`)
- L15 _externvar_ `extern bool bSkipGenerateMoveIfOverridden;` (scope `UE::ChaosMover::CVars`)
- L16 _externvar_ `extern bool bDisableResimDuplicateEventChecking;` (scope `UE::ChaosMover::CVars`)
- L17 _externvar_ `extern int32 InstantMovementEffectIDHistorySize;` (scope `UE::ChaosMover::CVars`)
- L18 _externvar_ `extern int32 LayeredMoveIDHistorySize;` (scope `UE::ChaosMover::CVars`)
- L19 _externvar_ `extern int32 FrameDifferenceLeniencyForEventTimeComparison;` (scope `UE::ChaosMover::CVars`)
- L20 _externvar_ `extern float FallingCheckRelativeSpeedLimit;` (scope `UE::ChaosMover::CVars`)
- L33 _externvar_ `extern bool bNetworkInstantMovementEffectsWithSimActions;` (scope `UE::ChaosMover::CVars`) — When true, instant movement effects queued via QueueInstantMovementEffect are networked using the sim action system ("Proposed" style: each role independently detects from GetLastInputCmd() in PostSim and enqueues the same action; server-authoritative, cheat-resistant). When false, they are embedded in the input cmd (PreSim detection, client-authoritative). IMPORTANT: when true, BP must read GetLastInputCmd() in PostSim -- NOT the PreSim input. In sim actions mode the server must independently queue the same action for verification. Unlike input-generating roles, the server has no access to generated input during PreSim and can only read it from the simulation output via GetLastInputCmd() in PostSim, introducing 1 frame of lag relative to the PreSim path. To allow the client to deviate from the server within tolerance (avoiding resims for small differences), override IsNearlyEqualTo on the FInstantMovementEffect subtype (see InstantMovementEffect.h).
- L46 _externvar_ `extern bool bNetworkMovesWithSimActions;` (scope `UE::ChaosMover::CVars`) — When true, layered moves and instanced move activations queued via QueueLayeredMove/QueueLayeredMoveInstance are networked using the sim action system ("Proposed" style: each role independently detects from GetLastInputCmd() in PostSim and enqueues the same action; server-authoritative, cheat-resistant). When false, they are embedded in the input cmd (PreSim detection, client-authoritative). IMPORTANT: when true, BP must read GetLastInputCmd() in PostSim -- NOT the PreSim input. In sim actions mode the server must independently queue the same action for verification. Unlike input-generating roles, the server has no access to generated input during PreSim and can only read it from the simulation output via GetLastInputCmd() in PostSim, introducing 1 frame of lag relative to the PreSim path. To allow the client to deviate from the server within tolerance (avoiding resims for small differences), override IsNearlyEqualTo on the FLayeredMoveBase or FLayeredMoveInstancedData subtype (see LayeredMove.h / LayeredMoveBase.h).
- L49 _externvar_ `extern bool bEnablePreSimGroundCheck;` (scope `UE::ChaosMover::CVars`) — Temporary
- L50 _externvar_ `extern bool bEnableServerLaunchOverride;` (scope `UE::ChaosMover::CVars`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverDefines.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define CHAOSMOVER_DEBUG_DRAW (!(UE_BUILD_SHIPPING || UE_BUILD_TEST) || WITH_EDITOR)`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosMover, Log, All);`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverSimulation.h` (Public)


#### struct `FChaosMoverPredictionStateBackup`  
`struct FChaosMoverPredictionStateBackup`  
_L28-33_
- L30 _public member_ `TOptional<FFloorCheckResult> BlackboardLastFloorResult;`
- L31 _public member_ `TOptional<FWaterCheckResult> BlackboardLastWaterResult;`
- L32 _public member_ `TOptional<UE::ChaosMover::FGroundDynamicsInfo> BlackboardGroundDynamicsInfo;`

#### class `UChaosMoverSimulation`  
`class UChaosMoverSimulation : public UMoverSimulation, public INetworkPhysicsActionHandler_Internal`  
_L36-285_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoverSimulation,INetworkPhysicsActionHandler_Internal`
- L43 _public member_ `FString DebugOwnerName;` — Mover Gameplay Tag Logging
- L44 _public member_ `FString DebugOwnerRole;`
- L47 _public prototype_ `UChaosMoverSimulation();`
- L51 _public prototype_ `const FMoverDataCollection& GetLocalSimInput() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Returns the local simulation input MoverDataCollection, to read local non networked data passed to the simulation by the gameplay thread
- L56 _public prototype_ `FMoverDataCollection& GetLocalSimInput_Mutable();` — `UFUNCTION(BlueprintPure, Category = Mover)` — Returns the local simulation input MoverDataCollection, to pass local non networked data to the simulation Only available from the gameplay thread
- L58 _public prototype_ `TWeakObjectPtr<const UBaseMovementMode> GetCurrentMovementMode() const;`
- L59 _public prototype_ `TWeakObjectPtr<UBaseMovementMode> GetCurrentMovementMode_Mutable();`
- L60 _public prototype_ `TWeakObjectPtr<const UBaseMovementMode> FindMovementModeByName(const FName& Name) const;`
- L61 _public prototype_ `TWeakObjectPtr<UBaseMovementMode> FindMovementModeByName_Mutable(const FName& Name);`
- L62 _public prototype_ `bool HasMovementMode(const FName& Name) const;`
- L63 _public prototype_ `void QueueNextMovementMode(FName ModeName);`
- L66 _public prototype_ `void K2_QueueInstantMovementEffect(UPARAM(DisplayName = "Instant Movement Effect") const i` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "EffectAsRawData", AllowAbstract = "false", DisplayName = "Queue Instant Movement Effect"))`
- L70 _public prototype_ `void QueueInstantMovementEffect_Internal(TSharedPtr<FInstantMovementEffect> InstantMovementEffect, bool bShouldRollBack = true);` — Queue an Instant Movement Effect to take place at the end of this frame or start of the next subtick - whichever happens first
- L72 _public prototype_ `void QueueInstantMovementEffect_Internal(const FScheduledInstantMovementEffect& ScheduledInstantMovementEffect, bool bShouldRollBack = true);` — Queue a scheduled instant movement effect
- L75 _public prototype_ `void K2_QueueLayeredMove(UPARAM(DisplayName = "Layered Move") const int32& LayeredMov` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "LayeredMoveAsRawData", AllowAbstract = "false", DisplayName = "Queue Layered Move"))`
- L79 _public prototype_ `void QueueLayeredMove_Internal(TSharedPtr<FLayeredMoveBase> LayeredMove, bool bShouldRollBack = true);` — Queue a Layered Move to take place at the end of this frame or start of the next subtick - whichever happens first
- L81 _public prototype_ `void QueueLayeredMove_Internal(const FScheduledLayeredMove& ScheduledLayeredMove, bool bShouldRollBack = true);` — Queue a scheduled layered move
- L84 _public prototype_ `void QueueLayeredMoveInstance_Internal(TSubclassOf<ULayeredMoveLogic> MoveLogicClass, TSharedRef<FLayeredMoveInstancedData> Data, bool bShouldRollBack = true);` — Queue a FLayeredMoveInstance activation. Looks up the registered logic by class and constructs the instance.
- L88 _public prototype_ `void SetRegisteredMoves(const TArray<TObjectPtr<ULayeredMoveLogic>>& Moves);` — Updates the cached snapshot of registered ULayeredMoveLogic objects. Call from the game thread before each simulation tick to keep the cache current with any dynamic re-registration.
- L91 _public prototype_ `FMovementModifierHandle K2_QueueMovementModifier(UPARAM(DisplayName = "Movement Modifier") const int32` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "MoveAsRawData", AllowAbstract = "false", DisplayName = "Queue Movement Modifier"))`
- L95 _public prototype_ `FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier);` — Queue a Movement Modifier to start during the next simulation frame.
- L98 _public prototype_ `const FMovementModifierBase* FindMovementModifierByType(const UScriptStruct* DataStructType) const;` — Find movement modifier by type (returns the first modifier it finds). Returns nullptr if the modifier couldn't be found
- L102 _public function_ `template <typename ModifierT = FMovementModifierBase UE_REQUIRES(std::is_base_of_v<FMovementModifierBase, ModifierT>)> const ModifierT* FindMovementModifierByType() const` — Find a movement modifier of a specific type in this components movement modifiers. If not found, null will be returned.
- L106 _public prototype_ `void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle);` — `UFUNCTION(BlueprintCallable, Category = Mover)`
- L109 _public prototype_ `bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const;` — `UFUNCTION(BlueprintPure, Category = Mover, meta = (Keywords = "HasTag"))`
- L111 _public function_ `ENetRole GetLocalRole() const`
- L112 _public function_ `bool IsUsingAsyncPhysics() const`
- L114 _public prototype_ `bool ShouldResim() const;`
- L135 _public prototype_ `void Init(const FInitParams& InitParams);`
- L136 _public prototype_ `void SetOwner(const AActor* Owner);`
- L137 _public prototype_ `void Deinit();`
- L139 _public prototype_ `void ProcessInputs(int32 PhysicsStep, const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData);`
- L140 _public prototype_ `void SimulationTick(const FMoverSimContext& SimContext, const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, UE::ChaosMover::FSimulationOutputData& OutputData);`
- L141 _public prototype_ `void ModifyContacts(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const UE::ChaosMover::FSimulationOutputData& OutputData, Chaos::FCollisionContactModifier& Modifier);`
- L143 _public prototype_ `void AddEvent(TSharedPtr<FMoverSimulationEventData> Event);`
- L144 _public prototype_ `const TArray<TSharedPtr<FMoverSimulationEventData>>& GetEvents() const;`
- L148 _public prototype_ `virtual void ApplyAction_Internal(const TInstancedStruct<FNetworkPhysicsActionPayload>& ActionInstance) override;` — INetworkPhysicsActionHandler_Internal: receives scheduled actions enqueued via UNetworkPhysicsComponent::EnqueueScheduledAction_External. Dispatches to typed handlers based on the action payload type.
- L150 _public prototype_ `void ApplyNetInputData(const FMoverInputCmdContext& InNetInputCmd);`
- L151 _public prototype_ `void BuildNetInputData(FMoverInputCmdContext& OutNetInputCmd) const;`
- L152 _public prototype_ `void ApplyNetStateData(const FMoverSyncState& InNetSyncState);`
- L153 _public prototype_ `void BuildNetStateData(FMoverSyncState& OutNetSyncState) const;`
- L157 _public prototype_ `virtual const FTransform& GetMovementBasisTransform() const;` — Movement modes can be relative to a basis transform, which can change at runtime Returns the movement basis transform, for movement relative to it
- L159 _public prototype_ `virtual void SetMovementBasisTransform(const FTransform& InMovementBasisTransform);` — Sets the movement basis transform, for movement relative to it
- L164 _public prototype_ `FMoverDataCollection& GetDebugSimData();` — `UFUNCTION(BlueprintPure, Category = Mover)` — Collection for holding extra debug data, that will be sent to the Chaos Visual Debugger for debugging
- L168 _protected prototype_ `virtual void OnInit();`
- L169 _protected prototype_ `virtual void OnDeinit();`
- L170 _protected prototype_ `virtual void OnPreSimulationTick(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData);`
- L171 _protected prototype_ `virtual void OnSimulationTick(const FMoverSimContext& SimContext, const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, UE::ChaosMover::FSimulationOutputData& OutputData);`
- L172 _protected prototype_ `virtual void OnPostSimulationTick(const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationOutputData& OutputData);`
- L173 _protected prototype_ `virtual void OnModifyContacts(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const UE::ChaosMover::FSimulationOutputData& OutputData, Chaos::FCollisionContactModifier& Modifier);`
- L174 _protected prototype_ `virtual void OnSimulationRollback(const FMoverTimeStep& NewTimeStep, const FMoverSyncState& PrevSyncState);`
- L176 _protected prototype_ `virtual void ProcessSimulationEvent(const FMoverSimulationEventData& ModeChangedData);`
- L177 _protected prototype_ `virtual void OnMovementModeChanged(const FMovementModeChangedEventData& ModeChangedData);`
- L180 _protected prototype_ `void BackupState(FChaosMoverPredictionStateBackup& Out) const;` — Trajectory Prediction
- L181 _protected prototype_ `void RestoreState(const FChaosMoverPredictionStateBackup& In);`
- L182 _protected prototype_ `void PredictTrajectory(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const FChaosMoverTrajectoryPredictionInputs* PredInputs, const FMoverSyncState& StartSyncState, UE::ChaosMover::FSimulationOutputData& OutputData) const;`
- L187 _public prototype_ `virtual void AttemptTeleport(const FMoverTimeStep& TimeStep, const FTransform& TargetTransform, bool bUseActorRotation, FMoverSyncState& OutputState) override;` — Attempt to teleport. This will first check CanTeleport and broadcast simulation events to indicate success or failure.
- L190 _protected prototype_ `virtual bool CanTeleport(const FTransform& TargetTransform, bool bUseActorRotation, const FMoverSyncState& SyncState);` — Whether the teleport can happen (does the movement mode allow it? Do we fit at the target transform?)
- L192 _protected prototype_ `virtual void Teleport(const FTransform& TargetTransform, const FMoverTimeStep& TimeStep, FMoverSyncState& OutputState);` — Actually perform the teleport
- L196 _public prototype_ `void TraceMoverData(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationOutputData& OutputData);` — Trace mover data to Chaos Visual Debugger
- L198 _public function_ `const FMoverSyncState& GetCurrentSyncState() const`
- L201 _public prototype_ `Chaos::FPBDRigidParticleHandle* GetControlledParticle() const;` — Physics state accessors -- callable from IChaosPostSimulationTickInterface implementations.
- L202 _public prototype_ `Chaos::FCharacterGroundConstraintHandle* GetCharacterGroundConstraintHandle() const;`
- L203 _public prototype_ `Chaos::FPBDJointConstraintHandle* GetActuationConstraintHandle() const;`
- L204 _public prototype_ `bool IsNonResimSimProxy() const;`
- L208 _public prototype_ `void SetControlledParticleDynamic();` — Object state -- callable from IChaosPostSimulationTickInterface implementations (e.g. executor classes that need to switch the particle between dynamic and kinematic).
- L209 _public prototype_ `void SetControlledParticleKinematic();`
- L210 _public prototype_ `bool IsControlledParticleDynamic() const;`
- L211 _public prototype_ `bool IsControlledParticleKinematic() const;`
- L215 _public prototype_ `void EnableCharacterGroundConstraint();` — Constraint enable helpers -- called by IChaosPostSimulationTickInterface implementations to re-enable the constraint after the simulation disables it upfront each tick.
- L216 _public prototype_ `void EnableActuationConstraint();`
- L219 _public prototype_ `void SetActuationTargetTransform(const FTransform& TargetTransform);` — Target transform for the actuation joint -- callable from pathed movement mode.
- L223 _protected prototype_ `void DisableCharacterGroundConstraint();` — Character ground constraint
- L224 _protected prototype_ `bool IsCharacterGroundConstraintEnabled() const;`
- L227 _protected prototype_ `void DisableActuationConstraint();` — General purpose actuation joint constraint
- L228 _protected prototype_ `bool IsActuationConstraintEnabled() const;`
- L229 _protected prototype_ `void TeleportActuationTarget(const FTransform& TargetTransform, bool AlsoTeleportControlledParticle = false);`
- L232 _protected member_ `FMoverSyncState CurrentSyncState;` — State structs
- L234 _protected member_ `FMoverDataCollection InternalSimData;` — Data internal to the simulation
- L236 _protected member_ `FMoverDataCollection LocalSimInput;` — Local input data, usually sent by the gameplay side locally, that is not expected to differ from that on the server so doesn't warrant networking
- L238 _protected member_ `FMoverDataCollection DebugSimData;` — Debug Data collection, sent to Chaos Visual Debugger when Trace Extra Sim Debug Data is selected
- L241 _protected member_ `UE::ChaosMover::FMoverStateMachine StateMachine;` — Movement mode state machine
- L244 _protected member_ `TWeakObjectPtr<UMovementMixer> MovementMixerWeakPtr = nullptr;` — Optional movement mixer
- L247 _protected member_ `Chaos::FConstPhysicsObjectHandle PhysicsObject = nullptr;` — Controlled physics object
- L250 _protected member_ `Chaos::FCharacterGroundConstraintHandle* CharacterGroundConstraintHandle = nullptr;` — Character ground constraint, specifically for moving on ground like characters
- L253 _protected member_ `Chaos::FPBDJointConstraintHandle* ActuationConstraintHandle = nullptr;` — General purpose actuation joint constraint
- L254 _protected member_ `Chaos::FKinematicGeometryParticleHandle* ActuationConstraintEndPointParticleHandle= nullptr;`
- L257 _protected member_ `FTransform MovementBasisTransform = FTransform::Identity;` — Some movement modes are relative to a movement basis transform, stored here
- L259 _protected member_ `Chaos::FPhysicsSolver* Solver = nullptr;`
- L260 _protected member_ `UWorld* World = nullptr;`
- L263 _private prototype_ `void UpdateEvents(const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationOutputData& OutputData);`
- L264 _private prototype_ `FChaosMoverPostSimContext BuildPostSimContext(const FMoverTimeStep& TimeStep, UE::ChaosMover::FSimulationOutputData& OutputData);`
- L266 _private member_ `FMoverInputCmdContext NetInputCmd;`
- L267 _private member_ `FMoverSyncState NetSyncState;`
- L270 _private member_ `TArray<TSharedPtr<FMoverSimulationEventData>> Events;` — Events from this simulation update
- L275 _private member_ `TArray<TSharedPtr<FMoverSimulationEventData>> ProcessedEvents;` — Dedup record of events sent to the GT during the forward sim, used to suppress duplicate re-emission during resimulation. Only contains events with bReEmitOnResim=false; events that opt into re-emission are never added here and always pass through resim unchanged.
- L277 _private member_ `bool bInputCmdOverridden = false;`
- L278 _private member_ `bool bSyncStateOverridden = false;`
- L279 _private member_ `bool bIsUsingAsyncPhysics = true;`
- L281 _private member_ `int32 InternalServerFrame = 0;`
- L283 _private member_ `bool bInitialized = false;`
- L284 _private member_ `ENetRole OwnerLocalRole = ENetRole::ROLE_None;`

#### struct `UChaosMoverSimulation::FInitParams`  
`struct FInitParams`  
_L116-133_
- L118 _public member_ `TMap<FName, TWeakObjectPtr<UBaseMovementMode>> ModesToRegister;`
- L119 _public member_ `TArray<TWeakObjectPtr<UBaseMovementModeTransition>> TransitionsToRegister;`
- L120 _public member_ `FMoverSyncState InitialSyncState;`
- L121 _public member_ `FName StartingMovementMode = NAME_None;`
- L122 _public member_ `TWeakObjectPtr<UNullMovementMode> NullMovementMode = nullptr;`
- L123 _public member_ `TWeakObjectPtr<UImmediateMovementModeTransition> ImmediateModeTransition = nullptr;`
- L124 _public member_ `TWeakObjectPtr<UMovementMixer> MovementMixer = nullptr;`
- L125 _public member_ `FTransform TransformOnInit = FTransform::Identity;`
- L126 _public member_ `Chaos::FCharacterGroundConstraintHandle* CharacterGroundConstraintHandle = nullptr;`
- L127 _public member_ `Chaos::FPBDJointConstraintHandle* ActuationConstraintHandle = nullptr;`
- L128 _public member_ `Chaos::FKinematicGeometryParticleHandle* ActuationConstraintEndPointParticleHandle = nullptr;`
- L129 _public member_ `Chaos::FConstPhysicsObjectHandle PhysicsObject = nullptr;`
- L130 _public member_ `Chaos::FPhysicsSolver* Solver = nullptr;`
- L131 _public member_ `UWorld* World = nullptr;`
- L132 _public member_ `bool bIsUsingAsyncPhysics = true;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverSimulationTypes.h` (Public)


#### struct `UE::ChaosMover::FSimulationInputData`  
`struct FSimulationInputData`  
_L36-46_
- L38 _public function_ `void Reset()`
- L44 _public member_ `mutable FMoverInputCmdContext InputCmd;` — Can be overridden by network physics
- L45 _public member_ `FMoverAuxStateContext AuxInputState;` — Optional aux input state. Not networked

#### struct `UE::ChaosMover::FMovementModeChangeEvent`  
`struct FMovementModeChangeEvent`  
_L51-57_
- desc: Mode change event structure, used to postpone callbacks to gameplay code when a mode has changed
- L53 _public member_ `FName PreviousMovementModeName;`
- L54 _public member_ `TWeakObjectPtr<UBaseMovementMode> PreviousMovementMode;`
- L55 _public member_ `FName NextMovementModeName;`
- L56 _public member_ `TWeakObjectPtr<UBaseMovementMode> NextMovementMode;`

#### struct `UE::ChaosMover::FGroundDynamicsInfo`  
`struct FGroundDynamicsInfo`  
_L68-77_
- L70 _public prototype_ `FGroundDynamicsInfo();`
- L71 _public prototype_ `FGroundDynamicsInfo(const FFloorCheckResult& InFloorResult);`
- L72 _public member_ `FVector LinearVelocity;`
- L73 _public member_ `FVector AngularVelocityDegrees;`
- L74 _public member_ `uint32 bIsMoving : 1;`
- L75 _public member_ `uint32 bIsDynamic : 1;`
- L76 _public member_ `uint32 bIsGravityEnabled : 1;`

#### struct `FChaosMoverPredictedTrajectoryData`  
`struct FChaosMoverPredictedTrajectoryData : public FMoverDataStructBase`  
_L84-118_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Predicted trajectory deltas generated during simulation tick. Stored in FSimulationOutputData::AdditionalOutputData (not networked, local only).
- L89 _public member_ `FTransform BaseTransform = FTransform::Identity;` — `UPROPERTY(BlueprintReadWrite, Category = ChaosMover)`
- L94 _public member_ `TArray<FTrajectorySampleInfo> Deltas;` — `UPROPERTY(BlueprintReadWrite, Category = ChaosMover)` — Predicted trajectory as delta transforms relative to each preceding step. Element [0] is the starting transform (time offset 0, Identity), i.e., anchored at BaseTransform.
- L96 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L101 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L106 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override`
- L111 _public function_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override`
- L117 _public function_ `virtual void Merge(const FMoverDataStructBase& From) override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosMoverPredictedTrajectoryData> : public TStructOpsTypeTraitsBase2<FChaosMoverPredictedTrajectoryData>`  
_L121-127_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverPredictedTrajectoryData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L124-126_

#### struct `FChaosMoverTrajectoryPredictionInputs`  
`struct FChaosMoverTrajectoryPredictionInputs : public FMoverDataStructBase`  
_L131-162_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Local-only inputs that control how ChaosMover generates predicted trajectory samples.
- L136 _public member_ `int32 NumPredictionSteps = 15;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChaosMover, meta = (ClampMin = "1", UIMin = "1"))`
- L139 _public member_ `float SecondsPerStep = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChaosMover, meta = (ClampMin = "0.001", UIMin = "0.001"))`
- L141 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L146 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L151 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override`
- L156 _public function_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override`
- L161 _public function_ `virtual void Merge(const FMoverDataStructBase& From) override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosMoverTrajectoryPredictionInputs> : public TStructOpsTypeTraitsBase2<FChaosMoverTrajectoryPredictionInputs>`  
_L165-171_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverTrajectoryPredictionInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L168-170_

#### struct `FChaosMoverGroundSimState`  
`struct FChaosMoverGroundSimState : public FMoverDataStructBase`  
_L175-193_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Mover ground state, holds movement properties relative to the ground
- L180 _public function_ `virtual FMoverDataStructBase* Clone() const override` — return newly allocated copy of this FMoverDataStructBase. MUST be overridden by derived types.
- L186 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Gets the type info of this FMoverDataStructBase. MUST be overridden by derived types.
- L192 _public member_ `FVector LocalVelocity = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ChaosMover)`

#### struct `FChaosMovementBasis`  
`struct FChaosMovementBasis : public FMoverDataStructBase`  
_L197-215_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Movement basis state, for any movement that is relative to a basis transform given in world coordinates
- L202 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;` — Implementation of FMoverDataStructBase
- L203 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L204 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L205 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L206 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L207 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L208 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L211 _public member_ `FVector BasisLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ChaosMover)`
- L214 _public member_ `FQuat BasisRotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ChaosMover)`

#### struct `FChaosMoverSimulationDefaultInputs`  
`struct FChaosMoverSimulationDefaultInputs : public FMoverDataStructBase`  
_L219-282_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Data block containing all default inputs required by the Chaos Mover simulation
- L223 _public function_ `FChaosMoverSimulationDefaultInputs()`
- L228 _public prototype_ `void Reset();`
- L231 _public function_ `virtual FMoverDataStructBase* Clone() const override` — return newly allocated copy of this FMoverDataStructBase. MUST be overridden by derived types.
- L237 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Gets the type info of this FMoverDataStructBase. MUST be overridden by derived types.
- L242 _public member_ `FCollisionResponseParams CollisionResponseParams;`
- L243 _public member_ `FCollisionQueryParams CollisionQueryParams;`
- L246 _public member_ `FVector UpDir;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)`
- L249 _public member_ `FVector Gravity;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)`
- L253 _public member_ `bool bIsGeneratingInputsLocally = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)` — True if inputs are generated locally for this Actor
- L257 _public member_ `bool bIsRemotelyControlled = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)` — True if the Actor is a pawn, has a controller but that controller is not local
- L259 _public member_ `Chaos::FPhysicsObjectHandle PhysicsObject;`
- L260 _public member_ `AActor* OwningActor;`
- L261 _public member_ `UWorld* World;`
- L262 _public member_ `FAsyncNetworkPhysicsComponent* AsyncNetworkPhysicsComponent;`
- L265 _public member_ `float PhysicsObjectGravity;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)`
- L268 _public member_ `float PawnCollisionHalfHeight;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)`
- L271 _public member_ `float PawnCollisionRadius;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ChaosMover)`
- L278 _public member_ `FTransform PrimaryVisualComponentRelativeTransform = FTransform::Identity;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — Relative transform of the primary visual (skeletal mesh) component with respect to the actor root. Populated each physics frame by the backend from UMoverComponent::GetBaseVisualComponentTransform(). Used by async layered moves (e.g. AnimRootMotion) to convert mesh-local root motion into world space without touching game-thread-only objects.
- L281 _public member_ `TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`

#### struct `FChaosMoverTimeStepDebugData`  
`struct FChaosMoverTimeStepDebugData : public FMoverDataStructBase`  
_L286-305_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: This will be replaced eventually by the Chaos Visual Debugger supporting the display of this information
- L290 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L291 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L293 _public prototype_ `void SetTimeStep(const FMoverTimeStep& InTimeStep);`
- L297 _public member_ `bool bIsResimulating = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")` — This is so CVD can display TimeStep.bIsResimulating properly, which does not exist in FMoverTimeStep in a way that will show up by default (bitflag)
- L301 _public member_ `bool bIsFirstResimFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")` — This is so CVD can display TimeStep.bIsFirstResimFrame properly, which does not exist in FMoverTimeStep in a way that will show up by default (bitflag)
- L304 _public member_ `FMoverTimeStep TimeStep;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`

#### struct `FNetworkPhysicsDebugData`  
`struct FNetworkPhysicsDebugData : public FMoverDataStructBase`  
_L309-338_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Structure for tracing some network physics info to CVD
- L313 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L314 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L316 _public prototype_ `void Set(const FAsyncNetworkPhysicsComponent* NetworkPhysicsComponent);`
- L319 _public member_ `bool bIsLocallyControlled = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L322 _public member_ `EPhysicsReplicationMode PhysicsReplicationMode = EPhysicsReplicationMode::Default;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L325 _public member_ `int32 NetworkPhysicsTickOffset = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L328 _public member_ `int32 LatestReceivedStateFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L331 _public member_ `float ForwardPredictionTime = -1.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L334 _public member_ `float CurrentSimProxyInputDecayAtRuntime = -1.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L337 _public member_ `float CurrentInputDecay = -1.0f;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`

#### struct `FChaosMoverSimulationEventsDebugData`  
`struct FChaosMoverSimulationEventsDebugData : public FMoverDataStructBase`  
_L343-359_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: CVD-only debug wrapper for simulation events emitted during a substep. Stored in DebugSimData. Each element holds a full copy of the concrete event type with all UPROPERTY fields visible.
- L348 _public member_ `TArray<FInstancedStruct> Events;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L350 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L355 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FChaosMoverSimulationEventsDebugData> : public TStructOpsTypeTraitsBase2<FChaosMoverSimulationEventsDebugData>`  
_L362-365_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverSimulationEventsDebugData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L364-364_

#### struct `FChaosWaterResultData`  
`struct FChaosWaterResultData : public FMoverDataStructBase`  
_L368-394_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- L374 _public member_ `FWaterCheckResult WaterResult;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L376 _public prototype_ `FChaosWaterResultData() = default;`
- L377 _public prototype_ `virtual ~FChaosWaterResultData() = default;`
- L379 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L384 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L389 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L390 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L391 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L392 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L393 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### class `UChaosCharacterMovementModeInterface`  
`class UChaosCharacterMovementModeInterface : public UInterface`  
_L397-400_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IChaosCharacterMovementModeInterface`  
`class IChaosCharacterMovementModeInterface`  
_L402-439_
- L408 _public prototype_ `virtual float GetTargetHeight() const = 0;` — `UFUNCTION(BlueprintCallable, Category=ChaosMover)`
- L411 _public prototype_ `virtual float GetGroundQueryRadius() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L414 _public prototype_ `virtual float GetMaxWalkSlopeCosine() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L417 _public prototype_ `virtual bool ShouldCharacterRemainUpright() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L420 _public prototype_ `virtual float GetMaxSpeed() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L423 _public prototype_ `virtual void OverrideMaxSpeed(float Value) = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L426 _public prototype_ `virtual void ClearMaxSpeedOverride() = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L429 _public prototype_ `virtual float GetAcceleration() const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L432 _public prototype_ `virtual void OverrideAcceleration(float Value) = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L435 _public prototype_ `virtual void ClearAccelerationOverride() = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`
- L438 _public prototype_ `virtual void UpdateCurrentFloor(const FMoverTimeStep& TimeStep) const = 0;` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)`

#### class `UChaosCharacterConstraintMovementModeInterface`  
`class UChaosCharacterConstraintMovementModeInterface : public UInterface`  
_L443-446_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for mover modes moving on ground like characters, using a character ground constraint

#### class `IChaosCharacterConstraintMovementModeInterface`  
`class IChaosCharacterConstraintMovementModeInterface`  
_L448-456_
- L453 _public prototype_ `virtual float GetTargetHeight() const = 0;`
- L454 _public prototype_ `virtual bool ShouldEnableConstraint() const = 0;`
- L455 _public prototype_ `virtual void UpdateConstraintSettings(Chaos::FCharacterGroundConstraintSettings& ConstraintSettings) const = 0;`

#### struct `FChaosMoverPreSimContext`  
`struct FChaosMoverPreSimContext`  
_L464-469_
- desc: Context passed by mutable reference to all IChaosPreSimulationTickInterface implementations during OnPreSimulationTick. Filled once per tick by the simulation; implementations perform mode-specific pre-simulation setup (floor sweeps, input processing, etc.) via the Simulation pointer.
- L466 _public member_ `FMoverTimeStep TimeStep;`
- L467 _public member_ `const UE::ChaosMover::FSimulationInputData& InputData;`
- L468 _public member_ `UMoverSimulation* Simulation = nullptr;`

#### class `UChaosPreSimulationTickInterface`  
`class UChaosPreSimulationTickInterface : public UInterface`  
_L472-475_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IChaosPreSimulationTickInterface`  
`class IChaosPreSimulationTickInterface`  
_L489-494_
- desc: Interface for pre-simulation tick implementations. Attach this to any UChaosMovementMode or UChaosMoveExecutorBase to opt into the generic OnPreSimulationTick dispatch -- no simulation changes needed. CollectSimulationInterfaces on UChaosMovementMode / UChaosCompositeMovementMode discovers implementors via Cast<> and registers them in FChaosMoverSimulationInterfaceCache::PreSimInterfaces. The simulation calls PreSimulationTick_Async for every collected interface after updating the sync state from the physics particle each tick.
- L493 _public prototype_ `virtual void PreSimulationTick_Async(FChaosMoverPreSimContext& Context) = 0;`

#### struct `FChaosMoverPostSimContext`  
`struct FChaosMoverPostSimContext`  
_L506-515_
- desc: Context passed by mutable reference to all IChaosPostSimulationTickInterface implementations during OnPostSimulationTick. Filled once per tick by the simulation; implementations read physics state and write results back to OutputData via the Simulation pointer. The fallback velocity application is skipped whenever any interface was dispatched. Set bApplyFallbackVelocity = true if the implementation does not apply particle velocity itself and still wants the fallback to fire.
- L508 _public member_ `FMoverTimeStep TimeStep;`
- L509 _public member_ `UE::ChaosMover::FSimulationOutputData& OutputData;`
- L510 _public member_ `UMoverSimulation* Simulation = nullptr;`
- L514 _public member_ `bool bApplyFallbackVelocity = false;` — Set to true to request the simulation's fallback velocity application even when an IChaosPostSimulationTickInterface implementation was dispatched. Leave false (the default) if the implementation handles particle velocity itself.

#### class `UChaosPostSimulationTickInterface`  
`class UChaosPostSimulationTickInterface : public UInterface`  
_L518-521_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IChaosPostSimulationTickInterface`  
`class IChaosPostSimulationTickInterface`  
_L536-541_
- desc: Interface for post-simulation tick implementations. Attach this to any UChaosMovementMode or UChaosMoveExecutorBase to opt into the generic OnPostSimulationTick dispatch -- no simulation changes needed. CollectSimulationInterfaces on UChaosMovementMode / UChaosCompositeMovementMode discovers implementors via Cast<> and registers them in FChaosMoverSimulationInterfaceCache::PostSimInterfaces. The simulation calls PostSimulationTick_Async for every collected interface, then applies a fallback SetV unless at least one interface was dispatched (or an implementation sets Context.bApplyFallbackVelocity = true).
- L540 _public prototype_ `virtual void PostSimulationTick_Async(FChaosMoverPostSimContext& Context) = 0;`

#### struct `FChaosMoverSimulationInterfaceCache`  
`struct FChaosMoverSimulationInterfaceCache`  
_L547-551_
- desc: Holds pre- and post-simulation interface pointers for the active movement mode, populated by UChaosMovementMode::CollectSimulationInterfaces each tick.
- L549 _public member_ `TArray<IChaosPreSimulationTickInterface*, TInlineAllocator<2>> PreSimInterfaces;`
- L550 _public member_ `TArray<IChaosPostSimulationTickInterface*, TInlineAllocator<2>> PostSimInterfaces;`

#### enum `EChaosMoverVelocityEffectMode`  
`enum class EChaosMoverVelocityEffectMode : uint8`  
_L554-564_
- reflection: `UENUM(BlueprintType)`
- L557 _public enumerator_ `Impulse` — Apply as an additive impulse
- L560 _public enumerator_ `AdditiveVelocity` — Apply as an additive velocity
- L563 _public enumerator_ `OverrideVelocity` — Apply as an override velocity

#### struct `FStanceModifiedEventData`  
`struct FStanceModifiedEventData : public FMoverSimulationEventData`  
_L567-606_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L571 _public function_ `FStanceModifiedEventData(const FMoverTimeStep& InEventTime, EStanceMode InOldStance, EStanceMode InNewStance, FEventProcessedCallbackPtr InEventProcessedCallback = nullptr) : FMoverSimulationEventData(InEventTime, InEventProcessedCallback) , OldStance(InOldStance) , NewStance(InNewStance)`
- L578 _public function_ `FStanceModifiedEventData()`
- L583 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L588 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const override`
- L602 _public member_ `EStanceMode OldStance = EStanceMode::Invalid;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L605 _public member_ `EStanceMode NewStance = EStanceMode::Invalid;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FStanceModifiedEventData> : public TStructOpsTypeTraitsBase2<FStanceModifiedEventData>`  
_L610-613_
- inherits: `TStructOpsTypeTraitsBase2<FStanceModifiedEventData>`
- desc: WithCopy = true: inherited std::function in FMoverSimulationEventData requires operator= for safe copying via FInstancedStruct.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L612-612_

#### struct `FChaosScheduledInstantMovementEffect`  
`struct FChaosScheduledInstantMovementEffect`  
_L617-630_
- reflection: `USTRUCT()`
- desc: Version of a FScheduledInstantMovementEffect bShouldRollBack flag
- L626 _public member_ `bool bShouldRollBack = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Whether this effect should rollback or not We do not net serialize this value since any effect received from the network should always be rolled back Only effects that were issued locally by the game thread should NOT roll back since resimulation does not run game thread logic again and will fail to generate them again
- L629 _public member_ `FScheduledInstantMovementEffect ScheduledEffect;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`

#### struct `FChaosNetInstantMovementEffect`  
`struct FChaosNetInstantMovementEffect`  
_L634-665_
- reflection: `USTRUCT()`
- desc: Version of a FScheduledInstantMovementEffect with networkable instanced struct instead
- L639 _public member_ `int32 IssuanceServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")`
- L642 _public member_ `int32 ExecutionServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L645 _public member_ `uint8 UniqueID = 0xFF;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L652 _public member_ `bool bShouldRollBack = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Whether this effect should rollback or not We do not net serialize this value since any effect received from the network should always be rolled back Only effects that were issued locally by the game thread should NOT roll back since resimulation does not run game thread logic again and will fail to generate them again
- L656 _public function_ `FScheduledInstantMovementEffect AsScheduledInstantMovementEffect() const`
- L664 _public member_ `TInstancedStruct<FInstantMovementEffect> Effect;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`

#### struct `FChaosNetInstantMovementEffectsQueue`  
`struct FChaosNetInstantMovementEffectsQueue : public FMoverDataStructBase`  
_L668-688_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- L673 _public member_ `TArray<FChaosNetInstantMovementEffect> Effects;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L675 _public prototype_ `void Add(const FScheduledInstantMovementEffect& Effect, bool bShouldRollBack, uint8 UniqueID);`
- L678 _public prototype_ `FChaosNetInstantMovementEffectsQueue& operator=(const TArray<FChaosScheduledInstantMovementEffect>& ScheduledInstantEffects);` — This function is used for debugging (sending to CVD)
- L680 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L681 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L682 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L683 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L684 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L685 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L686 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L687 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### struct `FChaosScheduledLayeredMove`  
`struct FChaosScheduledLayeredMove`  
_L692-705_
- reflection: `USTRUCT()`
- desc: Version of a FScheduledLayeredMove with bShouldRollBack flag
- L701 _public member_ `bool bShouldRollBack = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Whether this move should rollback or not We do not net serialize this value since any move received from the network should always be rolled back Only moves issued locally by the game thread should NOT roll back since resimulation does not run game thread logic again and will fail to generate them again
- L704 _public member_ `FScheduledLayeredMove ScheduledLayeredMove;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`

#### struct `FChaosNetLayeredMove`  
`struct FChaosNetLayeredMove`  
_L708-737_
- reflection: `USTRUCT()`
- L713 _public member_ `int32 IssuanceServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")`
- L716 _public member_ `int32 ExecutionServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L719 _public member_ `uint8 UniqueID = 0xFF;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L726 _public member_ `bool bShouldRollBack = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Whether this move should roll back or not We do not net serialize this value since any move received from the network should always be rolled back Only moves that were issued locally by the game thread should NOT roll back since resimulation does not run game thread logic again and will fail to generate them again
- L728 _public function_ `FScheduledLayeredMove AsScheduledLayeredMove() const`
- L736 _public member_ `TInstancedStruct<FLayeredMoveBase> Move;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`

#### struct `FChaosNetLayeredMovesQueue`  
`struct FChaosNetLayeredMovesQueue : public FMoverDataStructBase`  
_L740-760_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- L745 _public member_ `TArray<FChaosNetLayeredMove> Moves;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L747 _public prototype_ `void Add(const FScheduledLayeredMove& InScheduledLayeredMove, bool bShouldRollBack, uint8 UniqueID);`
- L750 _public prototype_ `FChaosNetLayeredMovesQueue& operator=(const TArray<FChaosScheduledLayeredMove>& LayeredMovesQueue);` — This function is used for debugging (sending to CVD)
- L752 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L753 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L754 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L755 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L756 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L757 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L758 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L759 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### struct `FChaosScheduledLayeredMoveInstance`  
`struct FChaosScheduledLayeredMoveInstance`  
_L764-773_
- desc: SM-internal queue entry for a GT-issued FLayeredMoveInstance move. Not a USTRUCT -- carries TSharedPtr which cannot be a UPROPERTY.
- L768 _public member_ `bool bShouldRollBack = true;` — Whether this move should roll back on resimulation. Game-thread-issued moves set this to false since the GT is not resimulated.
- L770 _public member_ `FMoverSchedulingInfo SchedulingInfo;`
- L772 _public member_ `TSharedPtr<FLayeredMoveInstance> Move;`

#### struct `FChaosNetLayeredMoveInstance`  
`struct FChaosNetLayeredMoveInstance`  
_L777-800_
- reflection: `USTRUCT()`
- desc: Per-move entry in the networked FLayeredMoveInstance queue.
- L782 _public member_ `int32 IssuanceServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")`
- L785 _public member_ `int32 ExecutionServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L788 _public member_ `uint8 UniqueID = 0xFF;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L792 _public member_ `bool bShouldRollBack = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Not net-serialized: networked moves always roll back; only GT-issued moves skip rollback.
- L796 _public member_ `TSubclassOf<ULayeredMoveLogic> MoveLogicClass;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — Logic class serialized to allow re-linking on load (non-UPROPERTY Move holds the actual data).
- L799 _public member_ `TSharedPtr<FLayeredMoveInstance> Move;` — Populated during NetSerialize; not a UPROPERTY.

#### struct `FChaosNetLayeredMoveInstancesQueue`  
`struct FChaosNetLayeredMoveInstancesQueue : public FMoverDataStructBase`  
_L805-825_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Networked queue of FLayeredMoveInstance moves, mirroring FChaosNetLayeredMovesQueue for the newer ULayeredMoveLogic / FLayeredMoveInstance layered move system.
- L810 _public member_ `TArray<FChaosNetLayeredMoveInstance> Moves;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L812 _public prototype_ `void Add(const FChaosScheduledLayeredMoveInstance& Scheduled, bool bShouldRollBack, uint8 UniqueID);`
- L815 _public prototype_ `FChaosNetLayeredMoveInstancesQueue& operator=(const TArray<FChaosScheduledLayeredMoveInstance>& ScheduledMoves);` — Used for debugging (sending to CVD): converts the SM-internal scheduled queue.
- L817 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L818 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L819 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L820 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L821 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L822 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L823 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L824 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### struct `FAsyncLocalOnlyInstantMovementEffect`  
`struct FAsyncLocalOnlyInstantMovementEffect : public FInstantMovementEffect`  
_L831-847_
- reflection: `USTRUCT()`
- inherits: `FInstantMovementEffect`
- desc: This instant movement effect is ChaosMover only and executes AsyncFunction on the issuing end point only Being local only, this instant movement effect does not serialize anything, doesn't override NetSerialize
- L835 _public function_ `FAsyncLocalOnlyInstantMovementEffect()`
- L836 _public prototype_ `virtual ~FAsyncLocalOnlyInstantMovementEffect() = default;`
- L838 _public member_ `FName OptionalName;`
- L840 _public member_ `TFunction<bool(FApplyMovementEffectParams_Async&, FMoverSyncState&)> AsyncFunction;` — Async Function executed in ApplyMovementEffect_Async (only locally)
- L842 _public prototype_ `virtual bool ApplyMovementEffect_Async(FApplyMovementEffectParams_Async& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L843 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L845 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;` — No NetSerialize override, this is a local only effect
- L846 _public prototype_ `virtual FString ToSimpleString() const override;`

#### struct `FDebugTeleportToInstantMovementEffect`  
`struct FDebugTeleportToInstantMovementEffect : public FInstantMovementEffect`  
_L851-867_
- reflection: `USTRUCT()`
- inherits: `FInstantMovementEffect`
- desc: This instant movement effect is ChaosMover only and teleport to a location without any checks whatsoever, this is meant for debugging only
- L855 _public function_ `FDebugTeleportToInstantMovementEffect()`
- L856 _public function_ `virtual ~FDebugTeleportToInstantMovementEffect()`
- L859 _public member_ `FVector TeleportLocation = FVector(MAX_FLT, MAX_FLT, MAX_FLT);` — A component can be set to MAX_FLT to signify "keep that current component unchanged"
- L860 _public member_ `FRotator TeleportRotation = FRotator(MAX_FLT, MAX_FLT, MAX_FLT);`
- L862 _public prototype_ `virtual bool ApplyMovementEffect_Async(FApplyMovementEffectParams_Async& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L863 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L864 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L865 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L866 _public prototype_ `virtual FString ToSimpleString() const override;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`
- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace ChaosMover` (scope `UE`)
- L48 _typedef_ `using FSimulationOutputData = ::UE::Mover::FSimulationOutputData;` (scope `UE::ChaosMover`)
- L61 _prototype_ `FMoverDataCollection& GetDebugSimData(UChaosMoverSimulation* Simulation);` (scope `UE::ChaosMover`) — Util function to be able to get the debug sim data collection from a UChaosMoverSimulation from another plugin, without including ChaosMoverSimulation.h
- L63 _namespace_ `namespace Blackboard` (scope `UE::ChaosMover`)
- L65 _externvar_ `extern const FName GroundDynamicsInfo;` (scope `UE::ChaosMover::Blackboard`)
- L125 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonae36486b0103`)
- L169 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonae36486b0203`)
- L364 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anonae36486b0303`)
- L612 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anonae36486b0403`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverSourceBase.h` (Public)


#### class `UChaosMoverSourceBase`  
`class UChaosMoverSourceBase : public UObject`  
_L28-59_
- reflection: `UCLASS(Abstract, MinimalAPI, EditInlineNew, DefaultToInstanced)`
- inherits: `UObject`
- desc: Abstract base class for move sources. A move source is responsible for producing a FProposedMove from simulation state. It decouples the "what velocity to generate" concern from the movement mode, allowing the same generation logic to be reused across different modes or physics backends. All methods must be safe to call from the physics simulation thread — no access to AActor or UActorComponent is permitted.
- L34 _public function_ `virtual void OnStart_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime)` — Called once when the owning mode is activated. Async-safe.
- L40 _public function_ `virtual void GenerateMove_Async( const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove)` — Produces a proposed move from the current simulation state. Called during the mode's GenerateMove phase. Async-safe — no AActor or UActorComponent access.
- L47 _public function_ `virtual bool IsFinished(double CurrentSimTimeMs) const` — Returns true when this source has naturally expired (e.g. a duration-limited move has elapsed).
- L50 _public function_ `virtual void OnEnd_Async(UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs)` — Called when the owning mode is deactivated or when IsFinished() returns true. Async-safe.
- L58 _public function_ `virtual void AppendMontageOutputEntry(TArray<FMoverSimDrivenMontageEntry>& OutEntries, const FMoverTimeStep& TimeStep) const` — Append simulation-authoritative montage state to OutEntries so the game thread can drive FAnimMontageInstance from this source's output. Called once per substep from UChaosMoverSimulation::SimulationTick alongside the equivalent call on FLayeredMoveGroup. Default implementation is a no-op: sources with no montage output need not override.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/ChaosMoverStateMachine.h` (Public)


#### class `UE::ChaosMover::FMoverStateMachine`  
`class FMoverStateMachine`  
_L17-195_
- L20 _public prototype_ `FMoverStateMachine();`
- L21 _public prototype_ `virtual ~FMoverStateMachine();`
- L29 _public prototype_ `void Init(const FInitParams& Params);`
- L31 _public prototype_ `void RegisterMovementMode(FName ModeName, TWeakObjectPtr<UBaseMovementMode> Mode, bool bIsDefaultMode = false);`
- L33 _public prototype_ `void UnregisterMovementMode(FName ModeName);`
- L34 _public prototype_ `void ClearAllMovementModes();`
- L36 _public prototype_ `void RegisterGlobalTransition(TWeakObjectPtr<UBaseMovementModeTransition> Transition);`
- L37 _public prototype_ `void UnregisterGlobalTransition(TWeakObjectPtr<UBaseMovementModeTransition> Transition);`
- L38 _public prototype_ `void ClearAllGlobalTransitions();`
- L40 _public prototype_ `FName GetDefaultModeName() const;`
- L41 _public prototype_ `void SetDefaultMode(FName NewDefaultModeName);`
- L43 _public prototype_ `void QueueNextMode(FName DesiredNextModeName, bool bShouldReenter = false);`
- L44 _public prototype_ `void SetModeImmediately(const FMoverTimeStep& TimeStep, FName DesiredModeName, bool bShouldReenter = false);`
- L45 _public prototype_ `void ClearQueuedMode();`
- L47 _public prototype_ `void OnSimulationTick(const FMoverSimContext& SimContext, const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartState, UMoverBlackboard* SimBlackboard, UMovementMixer* MovementMixer, FMoverTickEndData& OutputState);`
- L48 _public prototype_ `void OnSimulationRollback(const FMoverTimeStep& NewTimeStep, const FMoverSyncState& InvalidSyncState, const FMoverSyncState& NewSyncState);`
- L50 _public function_ `FName GetCurrentModeName() const`
- L55 _public function_ `const FGameplayTagContainer& GetLastKnownGameplayTags() const`
- L60 _public prototype_ `const TWeakObjectPtr<UBaseMovementMode> GetCurrentMode() const;`
- L61 _public prototype_ `const TWeakObjectPtr<UBaseMovementMode> FindMovementMode(FName ModeName) const;`
- L62 _public prototype_ `TWeakObjectPtr<UBaseMovementMode> FindMovementMode_Mutable(FName ModeName);`
- L64 _public prototype_ `void QueueLayeredMove(const FChaosScheduledLayeredMove& ScheduledMove);`
- L66 _public prototype_ `void QueueLayeredMoveInstance(const FChaosScheduledLayeredMoveInstance& ScheduledMove);`
- L68 _public prototype_ `void QueueInstantMovementEffect(const FChaosScheduledInstantMovementEffect& ScheduledEffect);`
- L72 _public prototype_ `void SetRegisteredMoves(const TArray<TObjectPtr<ULayeredMoveLogic>>& Moves);` — Updates the cached snapshot of registered ULayeredMoveLogic objects. Call from the game thread before each simulation tick to keep the cache current with any dynamic re-registration.
- L76 _public function_ `const TArray<TObjectPtr<ULayeredMoveLogic>>& GetRegisteredMoves() const` — Returns the cached registered move logic objects. Used by the simulation to re-link FLayeredMoveInstance logic pointers when constructing instances from sim action payloads.
- L78 _public prototype_ `FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier);`
- L79 _public prototype_ `void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle);`
- L80 _public prototype_ `const FMovementModifierBase* FindQueuedModifier(FMovementModifierHandle ModifierHandle) const;`
- L81 _public prototype_ `const FMovementModifierBase* FindQueuedModifierByType(const UScriptStruct* ModifierType) const;`
- L83 _public function_ `const TArray<FChaosScheduledInstantMovementEffect>& GetQueuedInstantEffects() const`
- L88 _public prototype_ `void SetOwnerActorName(const FString& InOwnerActorName);`
- L89 _public prototype_ `void SetOwnerActorLocalNetRole(ENetRole InOwnerActorLocalNetRole);`
- L93 _public prototype_ `void CaptureUnprocessedSimCommandsForCVD();` — Capture any simulation commands (instant movement effects, layered moves, etc.) that have not yet been processed to be sent to CVD
- L94 _public prototype_ `void OnEndTraceMoverData();`
- L99 _protected prototype_ `void QueueNextModeInternal(FName DesiredNextModeName, bool bShouldReenter = false, bool bIsFromRollback=false);`
- L102 _protected member_ `TMap<FName, TWeakObjectPtr<UBaseMovementMode>> Modes;`
- L103 _protected member_ `TArray<TWeakObjectPtr<UBaseMovementModeTransition>> GlobalTransitions;`
- L105 _protected member_ `TWeakObjectPtr<UImmediateMovementModeTransition> QueuedModeTransitionWeakPtr;`
- L107 _protected member_ `TWeakObjectPtr<UImmediateMovementModeTransition> ImmediateMovementModeTransitionWeakPtr;`
- L108 _protected member_ `TWeakObjectPtr<UNullMovementMode> NullMovementModeWeakPtr;`
- L110 _protected member_ `FString OwnerActorName;`
- L111 _protected member_ `ENetRole OwnerActorLocalNetRole;`
- L113 _protected member_ `FName DefaultModeName = NAME_None;`
- L114 _protected member_ `FName CurrentModeName = NAME_None;`
- L117 _protected member_ `TArray<FChaosScheduledLayeredMove> QueuedLayeredMoves;` — Moves that are queued to be executed when their scheduled time comes (earliest is at the start of the next sim subtick)
- L120 _protected member_ `TArray<FChaosScheduledLayeredMoveInstance> QueuedLayeredMoveInstances;` — FLayeredMoveInstance moves queued from the GT or network, flushed into LayeredMoveInstances at the appropriate sim frame
- L123 _protected member_ `TArray<FChaosScheduledInstantMovementEffect> QueuedInstantEffects;` — Effects that are queued to be applied when their schduled time comes (earliest at the start of the next sim subtick or at the end of the ongoing tick if queued mid tick)
- L126 _protected member_ `TArray<TSharedPtr<FMovementModifierBase>> QueuedMovementModifiers;` — Modifiers that are queued to be added to the simulation at the start of the next sim subtick.
- L129 _protected member_ `TArray<FMovementModifierHandle> ModifiersToCancel;` — Modifiers that are to be canceled at the start of the next sim subtick.
- L132 _protected member_ `FMoverTickStartData WorkingSubstepStartData;` — Internal-use-only tick data structs, for efficiency since they typically have the same contents from frame to frame
- L133 _protected member_ `FSimulationTickParams WorkingSimTickParams;`
- L134 _protected member_ `FMoverTickEndData* WorkingSimTickEndData = nullptr;` — Only valid during OnSimulationTick and null otherwise
- L136 _protected member_ `TWeakObjectPtr<UChaosMoverSimulation> Simulation;`
- L139 _protected member_ `FGameplayTagContainer LastKnownGameplayTags;` — Last set of simulation tags that were diffed and emitted. Used to detect tag changes between substeps and on rollback.
- L144 _private member_ `TArray<TObjectPtr<ULayeredMoveLogic>> CachedRegisteredMoves;` — Snapshot of UMoverComponent::RegisteredMoves, used on the simulation thread to re-link logic pointers on FLayeredMoveInstance moves that arrive via the replicated sync state.
- L146 _private prototype_ `void ConstructDefaultModes();`
- L149 _private prototype_ `void CollectGameplayTags(const FMoverSyncState& SyncState, FGameplayTagContainer& OutTags) const;` — Collect all gameplay tags contributed by the active mode, modifiers, and layered moves in SyncState.
- L152 _private prototype_ `void DiffAndEmitGameplayTagEvents(const FGameplayTagContainer& OldTags, const FGameplayTagContainer& NewTags, const FMoverTimeStep& TimeStep, bool bIsCausedByRollback);` — Diff OldTags vs NewTags and emit FMoverGameplayTagChangeEventData for each change (bWasAdded=true for additions, false for removals).
- L153 _private prototype_ `void AdvanceToNextMode(const FMoverTimeStep& TimeStep);`
- L154 _private prototype_ `void FlushQueuedMovesToGroup(const FMoverTimeStep& TimeStep, FLayeredMoveGroup& Group);`
- L155 _private prototype_ `void FlushQueuedModifiersToGroup(FMovementModifierGroup& ModifierGroup);`
- L156 _private prototype_ `void FlushModifierCancellationsToGroup(FMovementModifierGroup& ActiveModifierGroup);`
- L157 _private prototype_ `bool HasAnyInstantEffectsQueued(const FMoverTimeStep& TimeStep) const;`
- L158 _private prototype_ `bool ApplyInstantEffects(const FMoverTickStartData& SubstepStartData, const FMoverTimeStep& SubTimeStep, FMoverSyncState& OutputState);`
- L159 _private prototype_ `bool UpdateWorkingStateFromSyncState(const FMoverTimeStep& TimeStep, FMoverSyncState& OutputState);`
- L160 _private prototype_ `void ReceiveInstantMovementEffects(const FMoverTimeStep& TimeStep, const FChaosNetInstantMovementEffectsQueue* InstantMovementEffectsQueue);`
- L161 _private prototype_ `void ReceiveLayeredMoves(const FMoverTimeStep& TimeStep, const FChaosNetLayeredMovesQueue* LayeredMovesQueue);`
- L162 _private prototype_ `void ReceiveLayeredMoveInstances(const FMoverTimeStep& TimeStep, const FChaosNetLayeredMoveInstancesQueue* Queue);`
- L163 _private prototype_ `void RollBackQueuedInstantMovementEffects(int32 NewServerFrame);`
- L164 _private prototype_ `void RollBackQueuedLayeredMoves(int32 NewServerFrame);`
- L165 _private prototype_ `void RollBackQueuedLayeredMoveInstances(int32 NewServerFrame);`
- L166 _private prototype_ `void FlushQueuedMoveInstancesToGroup(const FMoverTimeStep& TimeStep, FLayeredMoveInstanceGroup& Group);`
- L167 _private prototype_ `FMoverSimContext GetSimContext() const;`
- L169 _private member_ `FMoverTimeStep InternalSimTime;`
- L181 _private member_ `FIDHistory InstantMovementEffectsIDHistory;`
- L182 _private member_ `FIDHistory LayeredMovesIDHistory;`
- L183 _private member_ `FIDHistory LayeredMoveInstancesIDHistory;`
- L190 _private member_ `bool bCaptureSimCommandsForCVD = false;` — If true, queued simulation commands (instant movement effects. layered moves, etc.) will be added to DebugSimData It is false from the last time we traced movement data to the time we call CaptureUnprocessedSimCommandsForCVD in FMoverStateMachine::OnSimulationTick which allows us to trace any unprocessed sim commands, including scheduled ones, that exist on that frame It is true after that point until we trace, so that we can capture the ones queued after that, for instance those queued by movement modes
- L191 _private prototype_ `void TraceInstantMovementEffect(const FChaosScheduledInstantMovementEffect& ScheduledEffect);`
- L192 _private prototype_ `void TraceLayeredMove(const FChaosScheduledLayeredMove& ScheduledMove);`
- L193 _private prototype_ `void TraceLayeredMoveInstance(const FChaosScheduledLayeredMoveInstance& ScheduledMove);`

#### struct `UE::ChaosMover::FMoverStateMachine::FInitParams`  
`struct FInitParams`  
_L23-28_
- L25 _public member_ `TWeakObjectPtr<UChaosMoverSimulation> Simulation;`
- L26 _public member_ `TWeakObjectPtr<UNullMovementMode> NullMovementMode;`
- L27 _public member_ `TWeakObjectPtr<UImmediateMovementModeTransition> ImmediateMovementModeTransition;`

#### struct `UE::ChaosMover::FMoverStateMachine::FIDHistory`  
`struct FIDHistory`  
_L171-179_
- L173 _public prototype_ `void AddID(int32 Frame, uint8 ID);`
- L174 _public prototype_ `void CullOldFrames(int32 CurrentFrame, int32 MaxAge = 30);`
- L175 _public prototype_ `void Rollback(int32 RollbackToFrameInclusive);`
- L176 _public prototype_ `bool WasIDAlreadySeen(uint8 ID) const;`
- L178 _public member_ `TMap<int32, TSet<uint8>> IDsByFrame;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace ChaosMover` (scope `UE`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/ChaosCharacterInputs.h` (Public)


#### struct `FChaosMoverLaunchInputs`  
`struct FChaosMoverLaunchInputs : public FMoverDataStructBase`  
_L12-37_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Add this struct to the character inputs to launch the character
- L19 _public member_ `FVector LaunchVelocityOrImpulse = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = "Chaos Mover")` — Launch velocity in cm/s or impulse in kg cm/s
- L22 _public member_ `EChaosMoverVelocityEffectMode Mode = EChaosMoverVelocityEffectMode::AdditiveVelocity;` — `UPROPERTY(BlueprintReadWrite, Category = "Chaos Mover")`
- L24 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L28 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L32 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L33 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L34 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L35 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L36 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosMoverLaunchInputs > : public TStructOpsTypeTraitsBase2< FChaosMoverLaunchInputs >`  
_L40-47_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverLaunchInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L43-46_

#### struct `FChaosMoverCrouchInputs`  
`struct FChaosMoverCrouchInputs : public FMoverDataStructBase`  
_L51-73_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Add this struct to toggle crouch on the character
- L58 _public member_ `bool bWantsToCrouch = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chaos Mover")` — Launch velocity in cm/s or impulse in kg cm/s
- L60 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L64 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L68 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L69 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L70 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L71 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L72 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosMoverCrouchInputs > : public TStructOpsTypeTraitsBase2< FChaosMoverCrouchInputs >`  
_L76-83_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverCrouchInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L79-82_

#### struct `FChaosMovementSettingsOverrides`  
`struct FChaosMovementSettingsOverrides : public FMoverDataStructBase`  
_L87-117_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Add this struct to the character inputs to override the max speed and acceleration
- L94 _public member_ `FName ModeName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")` — The name of the mode to apply the overrides to. If this is set to none the override will apply to the currently active mode
- L98 _public member_ `float MaxSpeedOverride = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Override maximum speed in the movement plane
- L102 _public member_ `float AccelerationOverride = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Override max linear rate of acceleration for controlled input. May be scaled based on magnitude of input.
- L104 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L108 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L112 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L113 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L114 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L115 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L116 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosMovementSettingsOverrides > : public TStructOpsTypeTraitsBase2< FChaosMovementSettingsOverrides >`  
_L120-127_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMovementSettingsOverrides>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L123-126_

#### struct `FChaosMovementSettingsOverridesRemover`  
`struct FChaosMovementSettingsOverridesRemover : public FMoverDataStructBase`  
_L131-153_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Add this struct to the character inputs to cancel any max speed and acceleration for the input mode
- L138 _public member_ `FName ModeName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")` — The name of the mode to apply the overrides to. If this is set to none the override will apply to the currently active mode
- L140 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L144 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L148 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L149 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L150 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L151 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L152 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosMovementSettingsOverridesRemover > : public TStructOpsTypeTraitsBase2< FChaosMovementSettingsOverridesRemover >`  
_L156-163_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMovementSettingsOverridesRemover>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L159-162_

#### struct `FChaosMoverRequestedMoveInputs`  
`struct FChaosMoverRequestedMoveInputs : public FMoverDataStructBase`  
_L167-195_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Add this struct to the character inputs to apply a requested move the character
- L174 _public member_ `FVector RequestedVelocity = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chaos Mover")` — Requested velocity in cm/s
- L177 _public member_ `bool bForceMaxSpeed = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chaos Mover")`
- L180 _public member_ `bool bUseAcceleration = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Chaos Mover")`
- L182 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L186 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L190 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L191 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L192 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L193 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L194 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosMoverRequestedMoveInputs > : public TStructOpsTypeTraitsBase2< FChaosMoverRequestedMoveInputs >`  
_L198-205_
- inherits: `TStructOpsTypeTraitsBase2<FChaosMoverRequestedMoveInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L201-204_

#### Free symbols / members of external scopes

- L44 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon366478d40103`)
- L45 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon366478d40103`)
- L80 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon366478d40203`)
- L81 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon366478d40203`)
- L124 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon366478d40303`)
- L125 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon366478d40303`)
- L160 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon366478d40403`)
- L161 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon366478d40403`)
- L202 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon366478d40503`)
- L203 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon366478d40503`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/ChaosCharacterMoverComponent.h` (Public)


#### class `UChaosCharacterMoverComponent`  
`class UChaosCharacterMoverComponent : public UCharacterMoverComponent`  
_L21-118_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UCharacterMoverComponent`
- L26 _public prototype_ `UChaosCharacterMoverComponent();`
- L28 _public prototype_ `virtual bool TryGetFloorCheckHitResult(FHitResult& OutHitResult) const override;`
- L31 _public prototype_ `virtual bool TryGetLastWaterResult(FWaterCheckResult& OutWaterResult) const;` — `UFUNCTION(BlueprintPure, Category = "Chaos Mover")`
- L33 _public prototype_ `virtual void ProduceInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd) override;`
- L34 _public prototype_ `virtual void ProduceServerInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd);`
- L35 _public prototype_ `virtual void ProduceLocalInput(FMoverDataCollection& OutLocalSimInput) const;`
- L36 _public prototype_ `virtual void DoQueueNextMode(FName DesiredModeName, bool bShouldReenter=false) override;`
- L37 _public prototype_ `virtual FName GetNextMovementModeName() const override;`
- L41 _public member_ `FChaosMover_OnLanded OnLandedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Chaos Mover", DisplayName = "On Landed")` — Broadcast when this actor lands on a valid surface.
- L45 _public member_ `FChaosMover_OnJumped OnJumped;` — `UPROPERTY(BlueprintAssignable, Category = "Chaos Mover")` — Broadcast when this actor jumps.
- L50 _public prototype_ `void Launch(const FVector& VelocityOrImpulse, EChaosMoverVelocityEffectMode Mode = EChaosMoverVelocityEffectMode::AdditiveVelocity);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Mover")` — Launch the character using either impulse or velocity Note: This will only trigger a launch if a launch transition is implemented on the current movement mode
- L55 _public prototype_ `void OverrideMovementSettings(const FChaosMovementSettingsOverrides Overrides);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Mover")` — Override the movement mode settings on a mode If the name is not set it will apply to the current mode
- L60 _public prototype_ `void CancelMovementSettingsOverrides(FName ModeName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Mover")` — Cancel overrides of movement mode settings If the name is not set it will apply to the current mode
- L64 _public function_ `TConstArrayView<FTrajectorySampleInfo> GetCachedPredictedTrajectoryDeltas() const` — Get cached predicted trajectory deltas. The first element is Identity corresponding to the starting transform at time offset 0.
- L69 _public prototype_ `virtual TArray<FTrajectorySampleInfo> GetPredictedTrajectory(FMoverPredictTrajectoryParams PredictionParams) override;` — Returns predicted trajectory constructed from the cached deltas. The first element is the starting transform at time offset 0. Supported parameters: bUseVisualComponentRoot, NumPredictionSamples and SecondsPerSample.
- L71 _public prototype_ `void SetPredictedTrajectoryParams(int32 InSteps, float InStepSeconds, bool bInEnableTrajectoryPrediction);`
- L72 _public prototype_ `void GetPredictedTrajectoryParams(int32& OutSteps, float& OutStepSeconds, bool& bIsTrajectoryPredictionEnabled) const;`
- L75 _protected prototype_ `virtual void OnMoverPreSimulationTick(const FMoverTimeStep& TimeStep, const FMoverInputCmdContext& InputCmd) override;`
- L76 _protected prototype_ `virtual void DispatchSimulationEvents(const UE::Mover::FSimulationOutputData& OutputData) override;`
- L77 _protected prototype_ `virtual void ProcessSimulationEvent(const FMoverSimulationEventData& EventData) override;`
- L78 _protected prototype_ `virtual void SetAdditionalSimulationOutput(const FMoverDataCollection& Data) override;`
- L80 _protected prototype_ `void ClearQueuedMode();`
- L82 _protected prototype_ `void NotifyOnLanded(const FLandedEventData& LandedEvent);`
- L83 _protected prototype_ `virtual void OnLanded(const FLandedEventData& LandedEvent);`
- L85 _protected prototype_ `virtual void ProduceInputImpl(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd);`
- L87 _protected member_ `FName ModeToOverrideSettings = NAME_None;`
- L88 _protected member_ `float MaxSpeedOverride = 0.0f;`
- L89 _protected member_ `float AccelerationOverride = 0.0f;`
- L90 _protected member_ `bool bOverrideMovementSettings = false;`
- L91 _protected member_ `bool bCancelMovementOverrides = false;`
- L93 _protected member_ `bool bFloorResultSet = false;`
- L94 _protected member_ `FFloorCheckResult LatestFloorResult;`
- L96 _protected member_ `bool bWaterResultSet = false;`
- L97 _protected member_ `FWaterCheckResult LatestWaterResult;`
- L99 _protected member_ `bool bPredictedTrajectorySet = false;`
- L100 _protected member_ `FChaosMoverPredictedTrajectoryData LatestPredictedTrajectoryData;`
- L102 _protected member_ `int32 PredictedTrajectorySteps = 15;`
- L103 _protected member_ `float PredictedTrajectoryStepSeconds = 0.1f;`
- L104 _protected member_ `bool bEnableTrajectoryPrediction = false;`
- L106 _protected member_ `FVector LaunchVelocityOrImpulse = FVector::ZeroVector;`
- L107 _protected member_ `EChaosMoverVelocityEffectMode LaunchMode = EChaosMoverVelocityEffectMode::AdditiveVelocity;`
- L110 _protected member_ `FName QueuedModeTransitionName = NAME_None;` — Queued immediate mode transition, it will be transmitted to the simulation next time ProduceInput is called
- L116 _protected member_ `EStanceMode LastDispatchedStance = EStanceMode::Invalid;` — Batch accumulation for stance dispatch: avoids spurious visual transitions caused by rollback/resim transient transitions (e.g. forced uncrouch then recrouch). ProcessSimulationEvent accumulates the final stance seen in a batch, and SetAdditionalSimulationOutput fires OnStanceChanged only if the net result changed.
- L117 _protected member_ `TOptional<EStanceMode> PendingBatchFinalStance;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChaosMover_OnLanded, class UChaosCharacterMoverComponent*, ChaosMoverComponent, FLandedEventData, LandedEventData);` — Fired after the actor lands on a valid surface.
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChaosMover_OnLanded, class UChaosCharacterMoverComponent*, ChaosMoverComponent, FLandedEventData, LandedEventData);` — Fired after the actor lands on a valid surface.
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnJumped, float, StartingJumpHeight);` — Fired after the actor jumps. First param is the starting jump height.
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnJumped, float, StartingJumpHeight);` — Fired after the actor jumps. First param is the starting jump height.

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Effects/ChaosCharacterApplyVelocityEffect.h` (Public)


#### struct `FChaosCharacterApplyVelocityEffect`  
`struct FChaosCharacterApplyVelocityEffect : public FInstantMovementEffect`  
_L15-33_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FInstantMovementEffect`
- desc: Applies a velocity or impulse for a single tick
- L21 _public member_ `FVector VelocityOrImpulseToApply = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Velocity or impulse to apply to the actor.
- L25 _public member_ `EChaosMoverVelocityEffectMode Mode = EChaosMoverVelocityEffectMode::AdditiveVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Controls whether to apply velocity or impulse and if the velocity will be additive
- L27 _public prototype_ `virtual bool ApplyMovementEffect_Async(FApplyMovementEffectParams_Async& ApplyEffectParams, FMoverSyncState& OutputState);`
- L28 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L29 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L30 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L31 _public prototype_ `virtual FString ToSimpleString() const override;`
- L32 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Executors/ChaosCharacterAirExecutor.h` (Public)


#### class `UChaosCharacterAirExecutor`  
`class UChaosCharacterAirExecutor : public UChaosMoveExecutorBase , public IChaosCharacterMovementModeInterface , public IChaosCharacterConstraintMovementModeInterface , public IChaosPreSimulationTickInterface , public IChaosPostSimulationTickInterface`  
_L27-93_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMoveExecutorBase,IChaosCharacterMovementModeInterface,IChaosCharacterConstraintMovementModeInterface,IChaosPreSimulationTickInterface,IChaosPostSimulationTickInterface`
- desc: UChaosCharacterAirExecutor: a concrete UChaosMoveExecutorBase that applies air physics to the character's sync state each simulation tick. Implements IChaosCharacterMovementModeInterface and IChaosCharacterConstraintMovementModeInterface so that it works correctly when used inside a UChaosCompositeMovementMode (which delegates interface resolution to the executor via CollectSimulationInterfaces). The constraint is enabled with RadialForceLimit = 0 so it provides only upright swing torque, not positional driving force -- velocity-based movement is applied via SetV each post-simulation tick.
- L40 _public member_ `float SwingTorqueLimit = 3000.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "NewtonMeters"))` — Maximum torque the character can apply to remain upright
- L44 _public member_ `bool bShouldCharacterRemainUpright = true;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings")` — Controls whether the character capsule is forced to remain upright
- L51 _public member_ `TOptional<float> TargetHeightOverride;` — `UPROPERTY(EditAnywhere, Category = "Query Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Optional override for target height (desired distance from capsule center to floor). If unset, derived automatically from the owning character's skeletal mesh Z offset.
- L55 _public member_ `TOptional<float> QueryRadiusOverride;` — `UPROPERTY(EditAnywhere, Category = "Query Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Optional override for the ground query radius. If unset, derived from capsule radius.
- L58 _public prototype_ `virtual void OnModeRegistered(const FName ModeName) override;` — UChaosMoveExecutorBase overrides
- L59 _public prototype_ `virtual void OnModeUnregistered() override;`
- L60 _public prototype_ `virtual void ExecuteMove_Async(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L63 _public prototype_ `virtual void PreSimulationTick_Async(FChaosMoverPreSimContext& Context) override;` — IChaosPreSimulationTickInterface
- L66 _public prototype_ `virtual void PostSimulationTick_Async(FChaosMoverPostSimContext& Context) override;` — IChaosPostSimulationTickInterface
- L69 _public function_ `virtual float GetTargetHeight() const override` — IChaosCharacterMovementModeInterface
- L70 _public function_ `virtual float GetGroundQueryRadius() const override`
- L71 _public prototype_ `virtual float GetMaxWalkSlopeCosine() const override;`
- L72 _public function_ `virtual bool ShouldCharacterRemainUpright() const override`
- L73 _public prototype_ `virtual float GetMaxSpeed() const override;`
- L74 _public prototype_ `virtual void OverrideMaxSpeed(float Value) override;`
- L75 _public prototype_ `virtual void ClearMaxSpeedOverride() override;`
- L76 _public prototype_ `virtual float GetAcceleration() const override;`
- L77 _public prototype_ `virtual void OverrideAcceleration(float Value) override;`
- L78 _public prototype_ `virtual void ClearAccelerationOverride() override;`
- L79 _public prototype_ `virtual void UpdateCurrentFloor(const FMoverTimeStep& TimeStep) const override;`
- L82 _public function_ `virtual bool ShouldEnableConstraint() const override` — IChaosCharacterConstraintMovementModeInterface
- L83 _public prototype_ `virtual void UpdateConstraintSettings(Chaos::FCharacterGroundConstraintSettings& ConstraintSettings) const override;`
- L87 _private member_ `float TargetHeight = 95.0f;` — Resolved on the game thread in OnModeRegistered
- L88 _private member_ `float QueryRadius = 30.0f;`
- L89 _private member_ `TWeakObjectPtr<const USharedChaosCharacterMovementSettings> SharedSettingsWeakPtr;`
- L91 _private member_ `TOptional<float> MaxSpeedOverride;`
- L92 _private member_ `TOptional<float> AccelerationOverride;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Executors/ChaosCharacterWalkingExecutor.h` (Public)


#### class `UChaosCharacterWalkingExecutor`  
`class UChaosCharacterWalkingExecutor : public UChaosMoveExecutorBase , public IChaosCharacterMovementModeInterface , public IChaosCharacterConstraintMovementModeInterface , public IChaosPreSimulationTickInterface , public IChaosPostSimulationTickInterface`  
_L33-134_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMoveExecutorBase,IChaosCharacterMovementModeInterface,IChaosCharacterConstraintMovementModeInterface,IChaosPreSimulationTickInterface,IChaosPostSimulationTickInterface`
- desc: UChaosCharacterWalkingExecutor: a concrete UChaosMoveExecutorBase that applies walking physics to the Chaos character ground constraint simulation. This executor also implements IChaosCharacterMovementModeInterface and IChaosCharacterConstraintMovementModeInterface. When used inside a UChaosCompositeMovementMode, CollectSimulationInterfaces automatically exposes those interfaces to the simulation. The physics application logic (ExecuteMove_Async) is equivalent to UChaosWalkingMode::SimulationTick_Implementation. Move generation is intentionally left to the paired UChaosMoverSourceBase — use UChaosLayeredMoveSource or a custom subclass to drive the proposed velocity each tick. OnModeRegistered resolves TargetHeight and QueryRadius from the owning character and locates the shared movement settings — all on the game thread before simulation begins.
- L45 _public member_ `float RadialForceLimit = 2000.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Newtons"))` — Maximum force the character can apply to reach the motion target
- L49 _public member_ `float TwistTorqueLimit = 1500.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "NewtonMeters"))` — Maximum torque the character can apply to rotate in air about the vertical axis
- L53 _public member_ `float SwingTorqueLimit = 3000.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "NewtonMeters"))` — Maximum torque the character can apply to remain upright
- L58 _public member_ `float GroundDamping = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Damping factor to control the softness of the interaction between the character and the ground. Set to 0 for no damping and 1 for maximum damping.
- L62 _public member_ `float FrictionForceLimit = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Newtons"))` — Maximum force the character can apply to hold in place while standing on an unwalkable incline
- L67 _public member_ `float FractionalRadialForceLimitScaling = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Scaling applied to the radial force limit to raise the limit to always allow the character to reach the motion target. 1 = scale as needed, 0 = no scaling.
- L72 _public member_ `float FractionalGroundReaction = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Controls the reaction force applied to the ground in the ground plane when the character is moving. 1 = full reaction force, 0 = normal force only.
- L76 _public member_ `bool bShouldCharacterRemainUpright = true;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings")` — Controls whether the character capsule is forced to remain upright
- L83 _public member_ `TOptional<float> TargetHeightOverride;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Optional override for target height (desired distance from capsule center to floor). If unset, derived automatically from the owning character's skeletal mesh Z offset.
- L87 _public member_ `TOptional<float> QueryRadiusOverride;` — `UPROPERTY(EditAnywhere, Category = "Query Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Optional override for the ground query radius. If unset, derived from capsule radius.
- L92 _public member_ `float FractionalDownwardVelocityToTarget = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Movement Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Controls how much downward velocity is applied to keep the character rooted to the ground when within MaxStepHeight of the surface.
- L96 _public member_ `bool bShouldApplyAngularVelocityToTarget = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")` — Whether the character can apply angular velocity in response to stick input
- L99 _public prototype_ `virtual void OnModeRegistered(const FName ModeName) override;` — UChaosMoveExecutorBase overrides
- L100 _public prototype_ `virtual void OnModeUnregistered() override;`
- L101 _public prototype_ `virtual void ExecuteMove_Async(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L104 _public prototype_ `virtual void PreSimulationTick_Async(FChaosMoverPreSimContext& Context) override;` — IChaosPreSimulationTickInterface
- L107 _public prototype_ `virtual void PostSimulationTick_Async(FChaosMoverPostSimContext& Context) override;` — IChaosPostSimulationTickInterface
- L110 _public function_ `virtual float GetTargetHeight() const override` — IChaosCharacterMovementModeInterface — implemented directly on this executor
- L111 _public function_ `virtual float GetGroundQueryRadius() const override`
- L112 _public prototype_ `virtual float GetMaxWalkSlopeCosine() const override;`
- L113 _public function_ `virtual bool ShouldCharacterRemainUpright() const override`
- L114 _public prototype_ `virtual float GetMaxSpeed() const override;`
- L115 _public prototype_ `virtual void OverrideMaxSpeed(float Value) override;`
- L116 _public prototype_ `virtual void ClearMaxSpeedOverride() override;`
- L117 _public prototype_ `virtual float GetAcceleration() const override;`
- L118 _public prototype_ `virtual void OverrideAcceleration(float Value) override;`
- L119 _public prototype_ `virtual void ClearAccelerationOverride() override;`
- L120 _public prototype_ `virtual void UpdateCurrentFloor(const FMoverTimeStep& TimeStep) const override;`
- L123 _public function_ `virtual bool ShouldEnableConstraint() const override` — IChaosCharacterConstraintMovementModeInterface — implemented directly on this executor
- L124 _public prototype_ `virtual void UpdateConstraintSettings(Chaos::FCharacterGroundConstraintSettings& ConstraintSettings) const override;`
- L128 _private member_ `float TargetHeight = 95.0f;` — Resolved on the game thread in OnModeRegistered
- L129 _private member_ `float QueryRadius = 30.0f;`
- L130 _private member_ `TWeakObjectPtr<const USharedChaosCharacterMovementSettings> SharedSettingsWeakPtr;`
- L132 _private member_ `TOptional<float> MaxSpeedOverride;`
- L133 _private member_ `TOptional<float> AccelerationOverride;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosCharacterMovementMode.h` (Public)


#### enum `ECharacterMoverFrictionOverrideMode`  
`enum class ECharacterMoverFrictionOverrideMode : uint8`  
_L16-21_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `DoNotOverride`
- L19 _public enumerator_ `AlwaysOverrideToZero`
- L20 _public enumerator_ `OverrideToZeroWhenMoving`

#### class `UChaosCharacterMovementMode`  
`class UChaosCharacterMovementMode : public UChaosMovementMode, public IChaosCharacterMovementModeInterface, public IChaosCharacterConstraintMovementModeInterface, public IChaosPreSimulationTickInterface, public IChaosPostSimulationTickInterface`  
_L27-131_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementMode,IChaosCharacterMovementModeInterface,IChaosCharacterConstraintMovementModeInterface,IChaosPreSimulationTickInterface,IChaosPostSimulationTickInterface`
- desc: Base class for all Chaos character movement modes
- L36 _public prototype_ `UChaosCharacterMovementMode(const FObjectInitializer& ObjectInitializer);`
- L38 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L41 _public prototype_ `virtual void PreSimulationTick_Async(FChaosMoverPreSimContext& Context) override;` — IChaosPreSimulationTickInterface
- L44 _public prototype_ `virtual void PostSimulationTick_Async(FChaosMoverPostSimContext& Context) override;` — IChaosPostSimulationTickInterface
- L47 _public function_ `virtual bool ShouldEnableConstraint() const override` — IChaosCharacterConstraintMovementModeInterface
- L52 _public prototype_ `virtual void ModifyContacts(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const UE::ChaosMover::FSimulationOutputData& OutputData, Chaos::FCollisionContactModifier& Modifier) const override;`
- L54 _public prototype_ `virtual void UpdateConstraintSettings(Chaos::FCharacterGroundConstraintSettings& ConstraintSettings) const override;`
- L57 _public function_ `virtual float GetTargetHeight() const override` — IChaosCharacterMovementModeInterface
- L62 _public function_ `virtual float GetGroundQueryRadius() const override`
- L67 _public prototype_ `virtual float GetMaxWalkSlopeCosine() const override;`
- L69 _public function_ `virtual bool ShouldCharacterRemainUpright() const override`
- L74 _public prototype_ `virtual float GetMaxSpeed() const override;`
- L75 _public prototype_ `virtual void OverrideMaxSpeed(float Value) override;`
- L76 _public prototype_ `virtual void ClearMaxSpeedOverride() override;`
- L78 _public prototype_ `virtual float GetAcceleration() const override;`
- L79 _public prototype_ `virtual void OverrideAcceleration(float Value) override;`
- L80 _public prototype_ `virtual void ClearAccelerationOverride() override;`
- L83 _public prototype_ `virtual void UpdateCurrentFloor(const FMoverTimeStep& TimeStep) const override;` — Updates the floor result in the blackboard
- L86 _protected prototype_ `void SetTargetHeightOverride(float InTargetHeight);`
- L87 _protected prototype_ `void ClearTargetHeightOverride();`
- L89 _protected prototype_ `void SetQueryRadiusOverride(float InQueryRadius);`
- L90 _protected prototype_ `void ClearQueryRadiusOverride();`
- L96 _protected member_ `float RadialForceLimit = 1500.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Newtons"))` — Maximum force the character can apply to reach the motion target
- L100 _protected member_ `float TwistTorqueLimit = 1000.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "NewtonMeters"))` — Maximum torque the character can apply to rotate in air about the vertical axis
- L104 _protected member_ `float SwingTorqueLimit = 3000.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "NewtonMeters"))` — Maximum torque the character can apply to remain upright
- L108 _protected member_ `bool bShouldCharacterRemainUpright = true;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings")` — Controls whether the character capsule is forced to remain upright
- L115 _protected member_ `TOptional<float> TargetHeightOverride;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Optional override target height for the character (the desired distance from the center of the capsule to the floor). If left blank, the -Z offset of the owning character's skeletal mesh comp will be used automatically.
- L119 _protected member_ `TOptional<float> QueryRadiusOverride;` — `UPROPERTY(EditAnywhere, Category = "Query Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Radius used for ground queries
- L123 _protected member_ `ECharacterMoverFrictionOverrideMode FrictionOverrideMode = ECharacterMoverFrictionOverrideMode::OverrideToZeroWhenMoving;` — `UPROPERTY(EditAnywhere, Category = "Collision Settings")` — Allows the mode to override friction on collision with other physics bodies.
- L126 _private member_ `float TargetHeight = 95.0f;`
- L127 _private member_ `float QueryRadius = 30.0f;`
- L129 _private member_ `TOptional<float> MaxSpeedOverride;`
- L130 _private member_ `TOptional<float> AccelerationOverride;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosFallingMode.h` (Public)


#### class `UChaosFallingMode`  
`class UChaosFallingMode : public UChaosCharacterMovementMode`  
_L15-110_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosCharacterMovementMode`
- desc: Chaos character falling mode
- L20 _public prototype_ `UChaosFallingMode(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L23 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L30 _public member_ `bool bCancelVerticalSpeedOnLanding;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true, actor will land and lose all speed in the vertical direction upon landing. If false, actor's vertical speed will be redirected based on the surface normal it hit. Note: Actor's horizontal speed will not be affected if true. If false, horizontal speed may be increased on landing.
- L37 _public member_ `float AirControlPercentage;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1.0"))` — When falling, amount of movement control available to the actor. 0 = no control, 1 = full control
- L44 _public member_ `float FallingDeceleration;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling slower than terminal velocity. Note: This is NOT applied to vertical velocity, only movement plane velocity
- L53 _public member_ `float FallingLateralFriction;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))` — Friction to apply to air movement. Lateral velocity is scaled each tick by a factor (1-Friction * TimeStep) so friction values greater than 1/TimeStep will result in all lateral velocity being removed. Note: This is NOT applied to vertical velocity, only movement plane velocity
- L61 _public member_ `float FallingAngularFriction;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))` — Friction to apply to rotational air movement. Angular velocity is scaled each tick by a factor (1-Friction * TimeStep) so friction values greater than 1/TimeStep will result in all angular velocity being removed.
- L68 _public member_ `float OverTerminalSpeedFallingDeceleration;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling faster than terminal velocity Note: This is NOT applied to vertical velocity, only movement plane velocity
- L76 _public member_ `float TerminalMovementPlaneSpeed;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ForceUnits = "cm/s"))` — If the actor's movement plane velocity is greater than this speed falling will start applying OverTerminalSpeedFallingDeceleration instead of FallingDeceleration The expected behavior is to set OverTerminalSpeedFallingDeceleration higher than FallingDeceleration so the actor will slow down faster when going over TerminalMovementPlaneSpeed.
- L80 _public member_ `bool bShouldClampTerminalVerticalSpeed;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — When exceeding maximum vertical speed, should it be enforced via a hard clamp? If false, VerticalFallingDeceleration will be used for a smoother transition to the terminal speed limit.
- L84 _public member_ `float VerticalFallingDeceleration;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bShouldClampTerminalVerticalSpeed", ClampMin = "0", ForceUnits = "cm/s^2"))` — Deceleration to apply to vertical velocity when it's greater than TerminalVerticalSpeed. Only used if bShouldClampTerminalVerticalSpeed is false.
- L90 _public member_ `float TerminalVerticalSpeed;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ForceUnits = "cm/s"))` — If the actors vertical velocity is greater than this speed VerticalFallingDeceleration will be applied to vertical velocity
- L96 _public member_ `bool bAlwaysClampRequestedVelocityToMaxSpeed = false;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true and input requests a velocity, whether to always clamp that velocity to max speed, regardless of input's bForceMaxSpeed flag
- L102 _public member_ `bool bShouldApplyAngularVelocityToTarget = true;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — Whether the character can apply angular velocity to respond to stick input
- L109 _protected member_ `uint8 bIgnoreGravity = 0;` — To allow other modes disable gravity

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosFlyingMode.h` (Public)


#### class `UChaosFlyingMode`  
`class UChaosFlyingMode : public UChaosCharacterMovementMode`  
_L13-24_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosCharacterMovementMode`
- desc: Chaos character flying mode
- L18 _public prototype_ `UChaosFlyingMode(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L21 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L23 _public prototype_ `virtual void UpdateCurrentFloor(const FMoverTimeStep& TimeStep) const override;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosSimpleWalkingMode.h` (Public)


#### class `UChaosSimpleWalkingMode`  
`class UChaosSimpleWalkingMode : public UChaosWalkingMode`  
_L20-39_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Abstract, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosWalkingMode`
- desc: Chaos walking mode variant that mirrors Mover's USimpleWalkingMode pattern: - Compute DesiredVelocity + DesiredFacing from inputs - Call GenerateWalkMove hook to allow derived modes to shape/smooth motion Still reuses UChaosWalkingMode's floor checking, step filtering, and contact modification.
- L25 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L33 _public prototype_ `void GenerateWalkMove(UPARAM(ref) FMoverTickStartData& StartState, float DeltaSeconds, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, UPARAM(ref) FVector& InOutAngularVelocityDegrees, UPARAM(ref) FVector& InOutVelocity);` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Generate Simple Walk Move (Chaos)"))` — Override this to implement a Chaos "simple walking" variant. - DesiredVelocity is in world space, typically constrained to the movement plane. - DesiredFacing is the target world-space orientation.
- L37 _protected prototype_ `virtual void GenerateWalkMove_Implementation(FMoverTickStartData& StartState, float DeltaSeconds, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, FVector& InOutAngularVelocityDegrees, FVector& InOutVelocity);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosSmoothWalkingMode.h` (Public)


#### class `UChaosSmoothWalkingMode`  
`class UChaosSmoothWalkingMode : public UChaosSimpleWalkingMode`  
_L17-75_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Experimental, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosSimpleWalkingMode`
- desc: A Chaos walking mode that ports Mover's USmoothWalkingMode spring/smoothing model. Uses FChaosSmoothWalkingState in SyncStateCollection to persist spring intermediates.
- L22 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L24 _public prototype_ `virtual void GenerateWalkMove_Implementation(FMoverTickStartData& StartState, float DeltaSeconds, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, FVector& InOutAngularVelocityDegrees, FVector& InOutVelocity) override;`
- L30 _protected member_ `float Acceleration = 1500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))`
- L33 _protected member_ `float Deceleration = 1500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))`
- L36 _protected member_ `float DirectionalAccelerationFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))`
- L39 _protected member_ `float TurningStrength = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0"))`
- L42 _protected member_ `float AccelerationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L45 _protected member_ `float DecelerationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L48 _protected member_ `float AccelerationSmoothingCompensation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))`
- L51 _protected member_ `float DecelerationSmoothingCompensation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))`
- L54 _protected member_ `float VelocityDeadzoneThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))`
- L57 _protected member_ `float AccelerationDeadzoneThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))`
- L60 _protected member_ `float OutsideInfluenceSmoothingTime = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L65 _protected member_ `float FacingSmoothingTime = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L68 _protected member_ `bool bSmoothFacingWithDoubleSpring = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings")`
- L71 _protected member_ `float FacingDeadzoneThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "deg"))`
- L74 _protected member_ `float AngularVelocityDeadzoneThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChaosMover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "deg/s"))`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosSwimmingMode.h` (Public)


#### struct `FSwimmingSettings`  
`struct FSwimmingSettings`  
_L13-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: Controls for the Swimming Movement
- L19 _public member_ `float MaxSpeedUp = 500.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max speed when moving up in water
- L23 _public member_ `float MaxSpeedDown = 1000.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max speed when moving down in water
- L27 _public member_ `float WaterVelocityDepthForMax = 175.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — At or above this depth, use max velocity. Interps down to WaterVelocityMinMultiplier at wading depth (where player can start swimming)
- L31 _public member_ `float WaterVelocityMinMultiplier = 0.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Min velocity multiplier applied when depth equals min swimming depth (where they transition from wading to swimming). Interps between this and 1.0 at WaterVelocityDepthForMax.
- L35 _public member_ `float MaxWaterForce = 400.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max water force, after WaterVelocity * (WaterForceMultiplier * WaterForceSecondMultiplier).
- L39 _public member_ `float WaterForceMultiplier = 2.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Multiplier to water force acceleration in direction of current.
- L43 _public member_ `float WaterForceSecondMultiplier = 1.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Multiplier applied on the top of WaterForceMultiplier, to water force acceleration in direction of current. Used only for inherited objects.
- L47 _public member_ `float BobbingMaxForce = 3800.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: Max force
- L51 _public member_ `float BobbingIdealDepthTolerance = 7.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: Slow down strongly when within this tolerance of the ideal immersion depth. Normally we apply drag only when going away from the ideal depth, this allows some slowdown when approaching it.
- L55 _public member_ `float BobbingFrictionDown = 5.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, linear multiplier per second
- L59 _public member_ `float BobbingExpDragDown = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L63 _public member_ `float BobbingFrictionDownSubmerged = 7.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, linear multiplier per second. Only used when fully submerged (replaces other value).
- L67 _public member_ `float BobbingExpDragDownSubmerged = 0.10f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L71 _public member_ `float BobbingFrictionUp = 7.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, linear multiplier per second
- L75 _public member_ `float BobbingExpDragUp = 0.20f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L79 _public member_ `float BobbingFrictionMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction multiplier, multiplies the fluid friction value.
- L83 _public member_ `float BobbingExpDragMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: multiplier for the exponential drag.

#### class `UChaosSwimmingMode`  
`class UChaosSwimmingMode : public UChaosCharacterMovementMode`  
_L90-109_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosCharacterMovementMode`
- desc: Chaos character swimming mode
- L95 _public prototype_ `UChaosSwimmingMode(const FObjectInitializer& ObjectInitializer);`
- L99 _public member_ `float SwimmingIdealImmersionDepth = 43.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water Control")` — Ideal depth when in water. Measured from the center of the collision shape.
- L102 _public member_ `FSwimmingSettings SurfaceSwimmingWaterControlSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water Control")`
- L104 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L105 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L108 _protected member_ `float OriginalHalfHeight = 75.f;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modes/ChaosWalkingMode.h` (Public)


#### class `UChaosWalkingMode`  
`class UChaosWalkingMode : public UChaosCharacterMovementMode`  
_L18-76_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosCharacterMovementMode`
- desc: Chaos character walking mode
- L23 _public prototype_ `UChaosWalkingMode(const FObjectInitializer& ObjectInitializer);`
- L28 _public member_ `float GroundDamping = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Damping factor to control the softness of the interaction between the character and the ground Set to 0 for no damping and 1 for maximum damping
- L32 _public member_ `float FrictionForceLimit = 100.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Newtons"))` — Maximum force the character can apply to hold in place while standing on an unwalkable incline
- L40 _public member_ `float FractionalRadialForceLimitScaling = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Scaling applied to the radial force limit to raise the limit to always allow the character to reach the motion target/ A value of 1 means that the radial force limit will be increased as needed to match the force required to achieve the motion target. A value of 0 means no scaling will be applied.
- L46 _public member_ `float FractionalGroundReaction = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Constraint Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Controls the reaction force applied to the ground in the ground plane when the character is moving A value of 1 means that the full reaction force is applied A value of 0 means the character only applies a normal force to the ground and no tangential force
- L51 _public member_ `float FractionalDownwardVelocityToTarget = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Movement Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Controls how much downward velocity is applied to keep the character rooted to the ground when the character is within MaxStepHeight of the ground surface.
- L58 _public member_ `uint8 bMaintainHorizontalGroundVelocity : 1 = 0;` — `UPROPERTY(EditAnywhere, Category = "Movement Settings")` — If true, walking movement always maintains horizontal velocity when moving up ramps, which causes movement up ramps to be faster parallel to the ramp surface. If false, then walking movement maintains velocity magnitude parallel to the ramp surface.
- L64 _public member_ `bool bShouldApplyAngularVelocityToTarget = true;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — Whether the character can apply angular velocity to respond to stick input
- L66 _public prototype_ `virtual void UpdateConstraintSettings(Chaos::FCharacterGroundConstraintSettings& ConstraintSettings) const override;`
- L68 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L69 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L71 _public prototype_ `virtual void ModifyContacts(const FMoverTimeStep& TimeStep, const UE::ChaosMover::FSimulationInputData& InputData, const UE::ChaosMover::FSimulationOutputData& OutputData, Chaos::FCollisionContactModifier& Modifier) const override;`
- L74 _protected prototype_ `virtual bool CanStepUpOnHitSurface(const FFloorCheckResult& FloorResult, const FVector& CharacterVelocity) const;`
- L75 _protected prototype_ `virtual void GetFloorAndCheckMovement(const FMoverDefaultSyncState& SyncState, const FProposedMove& ProposedMove, const FChaosMoverSimulationDefaultInputs& DefaultSimInputs, float DeltaSeconds, FFloorCheckResult& FloorResult, FWaterCheckResult& WaterResult, FVector& OutDeltaPos) const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Modifiers/ChaosStanceModifier.h` (Public)


#### struct `FChaosStanceModifier`  
`struct FChaosStanceModifier : public FMovementModifierBase`  
_L14-80_
- reflection: `USTRUCT(MinimalAPI, BlueprintType)`
- inherits: `FMovementModifierBase`
- L19 _public prototype_ `FChaosStanceModifier();`
- L20 _public prototype_ `virtual ~FChaosStanceModifier() override = default;`
- L22 _public member_ `EStanceMode ActiveStance;`
- L26 _public member_ `bool bCancelOnModeChange = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Whether to cancel the modifier when the movement mode changes
- L30 _public member_ `float ModifiedCapsuleHalfHeight = 60.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Height of the modified capsule
- L34 _public member_ `float ModifiedCapsuleRadius = 30.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Radius of the modified capsule
- L38 _public member_ `float ModifiedCapsuleGroundClearance = 10.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Ground clearance of the modified capsule
- L42 _public member_ `float DefaultCapsuleHalfHeight = 80.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Height of the default unmodified capsule
- L46 _public member_ `float DefaultCapsuleRadius = 30.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Radius of the default unmodified capsule
- L50 _public member_ `float DefaultCapsuleGroundClearance = 10.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Ground clearance of the default unmodified capsule
- L54 _public member_ `TOptional<float> MaxSpeedOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Override Max Speed
- L58 _public member_ `TOptional<float> AccelerationOverride;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Override Acceleration
- L60 _public prototype_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const override;`
- L61 _public prototype_ `virtual void GetGameplayTags(FGameplayTagContainer& InOutTags) const override;`
- L63 _public prototype_ `virtual void OnStart_Async(const FMovementModifierParams_Async& Params) override;`
- L64 _public prototype_ `virtual void OnEnd_Async(const FMovementModifierParams_Async& Params) override;`
- L65 _public prototype_ `virtual void OnPostMovement_Async(const FMovementModifierParams_Async& Params) override;`
- L67 _public prototype_ `virtual FMovementModifierBase* Clone() const override;`
- L68 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L69 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L70 _public prototype_ `virtual FString ToSimpleString() const override;`
- L71 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L74 _protected prototype_ `virtual void UpdateStance(const FMovementModifierParams_Async& AsyncParams, EStanceMode NewStance);`
- L76 _protected prototype_ `void UpdateCapsule(Chaos::FPBDRigidParticleHandle* ParticleHandle, float NewRadius, float NewHalfHeight, float NewGroundClearance, float TargetHeight);`
- L77 _protected prototype_ `const Chaos::FCapsule* GetCapsule(Chaos::FPBDRigidParticleHandle* ParticleHandle) const;`
- L79 _protected member_ `FName CurrentModeName = NAME_None;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FChaosStanceModifier > : public TStructOpsTypeTraitsBase2< FChaosStanceModifier >`  
_L83-89_
- inherits: `TStructOpsTypeTraitsBase2<FChaosStanceModifier>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L86-88_

#### Free symbols / members of external scopes

- L87 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anond25c6ca20103`)

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Settings/SharedChaosCharacterMovementSettings.h` (Public)


#### class `USharedChaosCharacterMovementSettings`  
`class USharedChaosCharacterMovementSettings : public UObject, public IMovementSettingsInterface`  
_L13-102_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovementSettingsInterface`
- desc: SharedChaosCharacterMovementSettings: collection of settings that are shared between the chaos character movement modes
- L17 _private function_ `virtual FString GetDisplayName() const override`
- L23 _public function_ `float GetMaxWalkableSlopeCosine() const`
- L30 _public member_ `float Deceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Default max linear rate of deceleration when there is no controlled input
- L34 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Default max linear rate of acceleration for controlled input. May be scaled based on magnitude of input.
- L38 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "-1", UIMin = "0", ForceUnits = "degrees/s"))` — Maximum rate of turning rotation (degrees per second). Negative numbers indicate instant rotation and should cause rotation to snap instantly to desired direction.
- L42 _public member_ `float TurningBoost = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Multiplier"))` — Speeds velocity direction changes while turning, to reduce sliding
- L46 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Maximum speed in the movement plane
- L54 _public member_ `bool bUseAccelerationForVelocityMove = true;` — `UPROPERTY(Category = "General", EditAnywhere, BlueprintReadWrite, AdvancedDisplay)` — Should use acceleration for velocity based movement intent? If true, acceleration is applied when using velocity input to reach the target velocity. If false, velocity is set directly, disregarding acceleration.
- L61 _public member_ `float GroundFriction = 8.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General|Friction", meta = (ClampMin = "0", UIMin = "0"))` — Setting that affects movement control. Higher values allow faster changes in direction. This can be used to simulate slippery surfaces such as ice or oil by lowering the value (possibly based on the material the actor is standing on).
- L70 _public member_ `uint8 bUseSeparateBrakingFriction : 1;` — `UPROPERTY(Category = "General|Friction", EditDefaultsOnly, BlueprintReadWrite)` — If true, BrakingFriction will be used to slow the character to a stop (when there is no Acceleration). If false, braking uses the same friction passed to CalcVelocity() (ie GroundFriction when walking), multiplied by BrakingFrictionFactor. This setting applies to all movement modes; if only desired in certain modes, consider toggling it when movement modes change. @see BrakingFriction
- L81 _public member_ `float BrakingFriction = 8.0f;` — `UPROPERTY(Category = "General|Friction", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", EditCondition = "bUseSeparateBrakingFriction"))` — Friction (drag) coefficient applied when braking (whenever Acceleration = 0, or if character is exceeding max speed); actual value used is this multiplied by BrakingFrictionFactor. When braking, this property allows you to control how much friction is applied when moving across the ground, applying an opposing force that scales with current velocity. Braking is composed of friction (velocity-dependent drag) and constant deceleration. This is the current value, used in all movement modes; if this is not desired, override it or bUseSeparateBrakingFriction when movement mode changes. @note Only used if bUseSeparateBrakingFriction setting is true, otherwise current friction such as GroundFriction is used. @see bUseSeparateBrakingFriction, BrakingFrictionFactor, GroundFriction, BrakingDecelerationWalking
- L89 _public member_ `float BrakingFrictionFactor = 2.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General|Friction", meta = (ClampMin = "0", UIMin = "0"))` — Factor used to multiply actual value of friction used when braking. This applies to any friction value that is currently used, which may depend on bUseSeparateBrakingFriction. @note This is 2 by default for historical reasons, a value of 1 gives the true drag equation.
- L93 _public member_ `float MaxStepHeight = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ground Movement", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Mover actors will be able to step up onto or over obstacles shorter than this
- L97 _public member_ `FName DefaultFallingMode = DefaultModeNames::Falling;` — `UPROPERTY(Category = "General", EditAnywhere, BlueprintReadWrite)` — Default movement mode to use when falling.
- L101 _public member_ `float MaxWalkableSlopeAngle = 45.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ground Movement", meta = (ClampMin = "0", UIMin = "0", ClampMax = "90", UIMax = "90", ForceUnits = "degrees"))` — Maximum angle of slope that the character can walk on without sliding

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterCrouchCheck.h` (Public)


#### class `UChaosCharacterCrouchCheck`  
`class UChaosCharacterCrouchCheck : public UChaosMovementModeTransition`  
_L11-68_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- L16 _public prototype_ `UChaosCharacterCrouchCheck(const FObjectInitializer& ObjectInitializer);`
- L18 _public prototype_ `virtual void OnRegistered();`
- L19 _public prototype_ `virtual void OnUnregistered();`
- L21 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L22 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L26 _public member_ `bool bCancelOnModeChange = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Whether to cancel the modifier when the movement mode changes
- L30 _public member_ `TOptional<float> CapsuleHalfHeight;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Height of the modified capsule
- L34 _public member_ `TOptional<float> CapsuleRadius;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Radius of the modified capsule
- L38 _public member_ `TOptional<float> CapsuleGroundClearance;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Ground clearance of the modified capsule
- L42 _public member_ `TOptional<float> MaxSpeed;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Override Max Speed
- L46 _public member_ `TOptional<float> Acceleration;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Override Acceleration
- L50 _public member_ `TOptional<FName> TransitionToCrouchedMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when crouched
- L54 _public member_ `TOptional<FName> TransitionToUncrouchedMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when uncrouched
- L57 _protected prototype_ `virtual bool CanCrouch(const FSimulationTickParams& Params) const;`
- L58 _protected prototype_ `virtual bool CanUncrouch(const FSimulationTickParams& Params) const;`
- L60 _protected prototype_ `virtual void Crouch(const FSimulationTickParams& Params);`
- L61 _protected prototype_ `virtual void Uncrouch(const FSimulationTickParams& Params);`
- L63 _protected member_ `float OriginalCapsuleHalfHeight = 0.0f;`
- L64 _protected member_ `float OriginalCapsuleRadius = 0.0f;`
- L66 _protected member_ `mutable bool bTriggerCrouch = false;`
- L67 _protected member_ `mutable bool bTriggerUncrouch = false;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterFallingCheck.h` (Public)


#### class `UChaosCharacterFallingCheck`  
`class UChaosCharacterFallingCheck : public UChaosMovementModeTransition`  
_L13-37_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- L18 _public prototype_ `UChaosCharacterFallingCheck(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual void OnRegistered() override;`
- L22 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L23 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L27 _public member_ `FName TransitionToFallingMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when landing on ground
- L33 _public member_ `float MaxUnsupportedTimeBeforeFalling = 0.06f;` — `UPROPERTY(EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — Time limit for being unsupported before moving from a walking to a falling state. This provides some grace period when walking off of an edge during which locomotion and jumping are still possible even though the character has started falling under gravity

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterJumpCheck.h` (Public)


#### class `UChaosCharacterJumpCheck`  
`class UChaosCharacterJumpCheck : public UChaosMovementModeTransition`  
_L13-38_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- L18 _public prototype_ `UChaosCharacterJumpCheck(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L21 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L25 _public member_ `float JumpUpwardsSpeed = 700.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Instantaneous speed induced in an actor upon jumping
- L33 _public member_ `float FractionalGroundReactionImpulse = 1.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Controls how much of the jump impulse the character will apply to the ground. A value of 0 means no impulse will be applied to the ground. A value of 1 means that the full equal and opposite jump impulse will be applied.
- L37 _public member_ `FName TransitionToMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when jumping

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterLandingCheck.h` (Public)


#### class `UChaosCharacterLandingCheck`  
`class UChaosCharacterLandingCheck : public UChaosMovementModeTransition`  
_L14-38_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- L19 _public prototype_ `UChaosCharacterLandingCheck(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L22 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L26 _public member_ `float FloorDistanceTolerance = 0.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (Units = "cm"))` — Height at which we consider the character to be on the ground
- L30 _public member_ `FName TransitionToGroundMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when landing on ground
- L34 _protected prototype_ `virtual TSharedPtr<FLandedEventData> AllocLandedEventData();` — Create the event data we will use for the landed event
- L37 _protected prototype_ `virtual void PopulateLandedEventData(const FSimulationTickParams& Params, const FFloorCheckResult& FloorResult, FLandedEventData& OutLandedEvent);` — Used to fill the landed event data before adding the Landed Event into the simulation

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterLaunchCheck.h` (Public)


#### class `UChaosCharacterLaunchCheck`  
`class UChaosCharacterLaunchCheck : public UChaosMovementModeTransition`  
_L13-29_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UChaosMovementModeTransition`
- desc: Transition that handles launching based on input for a physics-based character
- L18 _public prototype_ `UChaosCharacterLaunchCheck(const class FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L21 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L28 _public member_ `FName TransitionToMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Optional: Name of movement mode to transition to when launch is activated. If set to None launching will not change the current mode

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Character/Transitions/ChaosCharacterWaterCheck.h` (Public)


#### class `UChaosCharacterWaterCheck`  
`class UChaosCharacterWaterCheck : public UChaosMovementModeTransition`  
_L13-42_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- L18 _public prototype_ `UChaosCharacterWaterCheck(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L21 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L25 _public member_ `float WaterModeStartImmersionDepth = 45.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (Units = "cm"))` — Depth at which the pawn starts water mode. Measured from the center of the collision shape.
- L29 _public member_ `float WaterModeStopImmersionDepth = 40.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters, meta = (Units = "cm"))` — Depth at which the pawn stops water mode. Measured from the center of the collision shape.
- L33 _public member_ `FName WaterModeName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when immersed in water.
- L37 _public member_ `FName GroundModeName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when ground is within reach.
- L41 _public member_ `FName AirModeName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when exiting water but ground is not in reach.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosEllipticalMovementPathPattern.h` (Public)


#### class `UChaosEllipticalMovementPathPattern`  
`class UChaosEllipticalMovementPathPattern : public UChaosPathedMovementPatternBase`  
_L11-39_
- reflection: `UCLASS()`
- inherits: `UChaosPathedMovementPatternBase`
- L16 _public prototype_ `virtual void InitializePattern(UChaosMoverSimulation* InSimulation) override;`
- L19 _protected prototype_ `virtual FTransform CalcUnmaskedTargetTransform(float OverallPathFraction, const FTransform& BasisTransform) const override;`
- L23 _protected member_ `float RadiusX = 100.f;` — `UPROPERTY(EditAnywhere, Category = EllipticalPathPattern)` — Radius of the ellipse along the x axis
- L26 _protected member_ `float RadiusY = 100.f;` — `UPROPERTY(EditAnywhere, Category = EllipticalPathPattern)`
- L30 _protected member_ `float OriginAngle = 0.f;` — `UPROPERTY(EditAnywhere, Category = EllipticalPathPattern, meta = (Units = Degrees, UIMin = 0, ClampMin = 0, UIMax = 360, ClampMax = 360))` — The angle between the path origin (i.e. the initial location of the component/particle) and the center of the ellipse
- L34 _protected member_ `float UsableArcAngle = 360.f;` — `UPROPERTY(EditAnywhere, Category = EllipticalPathPattern, meta = (Units = Degrees, UIMin = 0, ClampMin = 0, UIMax = 360, ClampMax = 360))` — The amount of the ellipsoid arc to actually use for the path (where 360 is the entire ellipse)
- L38 _protected member_ `FRotator EllipsePlaneRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = EllipticalPathPattern)` — The world rotation of the plane the ellipse is on

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPathedMovementControllerComponent.h` (Public)


#### enum `EChaosPathedMovementExecutionType`  
`enum class EChaosPathedMovementExecutionType : uint8`  
_L35-47_
- reflection: `UENUM(BlueprintType)`
- desc: Execution type for pathed movement modifications, i.e. whether the modification is executed on the authority only or predicted on the client
- L40 _public enumerator_ `AuthorityOnly UMETA(DisplayName = "Authority Only")` — Only executed if attempted on the authority. If attempted on non authoritative client, this action will be ignored. This will execute on an authoritative client (client only actors)
- L46 _public enumerator_ `ClientPredicted_AutonomousOnly UMETA(DisplayName = "Client Predicted - Autonomous Only")` — If the actor is autonomous proxy, this action will execute predictively. This will also result in an input that will cause the action to execute on the server and replicate to sim proxies. If the actor is simulated proxy, this will be ignored. On the server, this will be ignored, relying on input replication instead. This will execute on an authoritative client (client only actors)

#### class `UChaosPathedMovementControllerComponent`  
`class UChaosPathedMovementControllerComponent : public UActorComponent , public IMoverInputProducerInterface , public IChaosPathedMovementDebugDrawInterface`  
_L56-205_
- reflection: `UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IMoverInputProducerInterface,IChaosPathedMovementDebugDrawInterface`
- desc: This controller component gives control over pathed movement of an actor with a mover component and an active pathed movement mode. You can start/stop, play forward or in reverse, play once or loop and play one way (0 to 1) or round trip (0 to 1 to 0). In async mode, control requests are sent as scheduled to take effect at a future frame, to give enough time for all end points to receive the request and react at the same exact scheduled frame.
- L63 _public prototype_ `UChaosPathedMovementControllerComponent();`
- L66 _public prototype_ `virtual void BeginPlay() override;` — UActorComponent
- L67 _public prototype_ `virtual void OnRegister() override;`
- L68 _public prototype_ `virtual void OnUnregister() override;`
- L71 _public prototype_ `virtual void ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult) override;` — IMoverInputProducerInterface
- L80 _public prototype_ `void RequestStartPlayingPath(EChaosPathedMovementExecutionType ExecutionType = EChaosPathedMovementExecutionType::AuthorityOnly, bool bIsScheduled = true);` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Request to start or resume moving along the path. If a previous non looping playback reached the end naturally, this will restart playback. @param ExecutionType The execution type of this action @see EChaosPathedMovementExecutionType @param bIsScheduled If true, the execution will be delayed to leave enough time for all end points to receive request and start at the same frame to avoid a correction. @see UChaosMoverSettings::PathedMovementSchedulingDelaySeconds
- L83 _public prototype_ `void RequestStopPlayingPath(EChaosPathedMovementExecutionType ExecutionType = EChaosPathedMovementExecutionType::AuthorityOnly, bool bIsScheduled = true);` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Request to stop playback.
- L86 _public prototype_ `bool WantsPlayingPath() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Do we want to be starting or resuming playback?
- L89 _public prototype_ `bool IsPlayingPath() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Is a playback under way (not just requested) or stopped?
- L92 _public member_ `FChaosMover_OnPathedMovementStarted OnPathedMovementStarted;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when the pathed movement has started
- L95 _public member_ `FChaosMover_OnPathedMovementStopped OnPathedMovementStopped;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when the pathed movement has stopped
- L98 _public member_ `FChaosMover_OnPathedMovementBounced OnPathedMovementBounced;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when the pathed movement has bounced (reached the end of one leg in a round trip)
- L102 _public prototype_ `void RequestReversePlayback(bool bWantsReversePlayback, EChaosPathedMovementExecutionType ExecutionType = EChaosPathedMovementExecutionType::AuthorityOnly, bool bIsScheduled = true);` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Request to set playback in reverse (bWantsReversePlayback = True) or forward (False)
- L105 _public prototype_ `bool WantsReversePlayback() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Do we want the playback to be in reverse?
- L108 _public prototype_ `bool IsReversePlayback() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Is the playback in reverse
- L111 _public member_ `FChaosMover_OnPathedMovementReversePlaybackChanged OnPathedMovementReversePlaybackChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when reverse has changed
- L116 _public prototype_ `void RequestLoopingPlayback(bool bWantsLoopingPlayback, EChaosPathedMovementExecutionType ExecutionType = EChaosPathedMovementExecutionType::AuthorityOnly, bool bIsScheduled = true);` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Request the playback to be looping (True) or not (False)
- L119 _public prototype_ `bool WantsLoopingPlayback() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Do we want the playback to be looping or forward?
- L122 _public prototype_ `bool IsLoopingPlayback() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Is the playback looping
- L125 _public member_ `FChaosMover_OnPathedMovementLoopingPlaybackChanged OnPathedMovementLoopingPlaybackChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when looping has changed
- L129 _public prototype_ `void RequestOneWayPlayback(bool bWantsOneWayPlayback, EChaosPathedMovementExecutionType ExecutionType = EChaosPathedMovementExecutionType::AuthorityOnly, bool bIsScheduled = true);` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Request the playback be one way (0->1), or round trip (there and back, 0->1->0)
- L132 _public prototype_ `bool WantsOneWayPlayback() const;` — Do we want the playback to be one way or round trip?
- L135 _public prototype_ `bool IsOneWayPlayback() const;` — `UFUNCTION(BlueprintCallable, Category = "Pathed Movement")` — Is the playback one way or round trip
- L138 _public member_ `FChaosMover_OnPathedMovementOneWayPlaybackChanged OnPathedMovementOneWayPlaybackChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Pathed Movement")` — Broadcast when one way has changed
- L141 _public member_ `FChaosMutablePathedMovementProperties InitialProperties;` — `UPROPERTY(EditAnywhere, Category="Pathed Movement")`
- L146 _protected prototype_ `virtual void OnPostSimEventReceived(const FMoverSimulationEventData& EventData);` — `UFUNCTION()` — Processes output events coming from the simulation and broadcasts delegates accordingly
- L149 _protected prototype_ `virtual void OnPostFinalize(const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — `UFUNCTION()`
- L153 _protected prototype_ `virtual bool ShouldDisplayProgressPreviewMesh_Implementation() const override;` — IChaosPathedMovementDebugDrawInterface implementation
- L154 _protected prototype_ `virtual float GetPreviewMeshOverallPathProgress_Implementation() const override;`
- L155 _protected prototype_ `virtual UMaterialInterface* GetProgressPreviewMeshMaterial_Implementation() const override;`
- L159 _protected member_ `bool bDisplayProgressPreviewMesh = true;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement|Debug")` — When true and the root component of the actor is a mesh, a duplicate mesh will be shown at PreviewMeshProgress along the starting/default path
- L163 _protected member_ `float PreviewMeshOverallPathProgress = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement|Debug", meta = (EditCondition = bDisplayProgressPreviewMesh, EditConditionHides, UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — How far along the starting/default path to preview the controlled mesh
- L167 _protected member_ `TObjectPtr<UMaterialInterface> PreviewMeshMaterial;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement|Debug", meta = (EditCondition = bDisplayProgressPreviewMesh, EditConditionHides))` — The material to apply to the preview mesh displayed along the path at PreviewMeshProgress (leave empty for an exact duplicate)
- L170 _protected member_ `TObjectPtr<UChaosPathedMovementDebugDrawComponent> DebugDrawComp;` — `UPROPERTY(Transient)`
- L178 _private prototype_ `void ExecuteOrScheduleChange(const FChaosMutablePathedMovementProperties& NewProperties, bool bIsScheduled, bool bIsStart = false);` — Schedule NewProperties to take effect at the earliest possible time @param NewProperties The properties that should take effect @param bIsScheduled When true, a delay is added to ensure all end points execute the change on the same frame @param bIsStart If true, this indicates that a start is requested as part of the changes. This is to restart if bWantsToPlay was true but the pathed movement stopped by reaching the end of the path.
- L181 _private prototype_ `Chaos::FPhysicsSolver* GetPhysicsSolver() const;` — Util function to get the physics solver
- L184 _private member_ `FChaosMutablePathedMovementProperties PathedMovementMutableProperties;` — Mutable pathed movement properties to take effect when server frame reaches LastChangeFrame
- L189 _private member_ `int32 LastChangeFrame = INDEX_NONE;` — The (server) frame at which PathedMovementMutableProperties took effect Note that it can be greater than the current server frame to schedule that change (the changes are sent immediately but scheduled to take effect in the future)
- L192 _private member_ `int32 MovementStartFrame = INDEX_NONE;` — The frame at which movement last started (but this may be in the future for a scheduled start)
- L193 _private member_ `FTimerHandle PathedMovementDelayedStartTimerHandle;`
- L196 _private member_ `FChaosPathedMovementState PostSimState;` — The (possibly interpolated) post simulation state
- L201 _private member_ `TObjectPtr<UMoverComponent> MoverComponent = nullptr;` — `UPROPERTY(Transient)` — Cached mover component if found on owner actor We use the OnPostMovement delegate to reflect the current state to gameplay (interpolated state in async)
- L204 _private member_ `float EventSchedulingMinDelaySeconds = 0.3f;` — Delay added to changes, when they are scheduled @see ExecuteOrScheduleChange

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChaosMover_OnPathedMovementStarted);` — Fired on the game thread when it has received notification that the pathed movement has started
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChaosMover_OnPathedMovementStarted);` — Fired on the game thread when it has received notification that the pathed movement has started
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementStopped, bool, bReachedEndOfPlayback);` — Fired on the game thread when it has received notification that the pathed movement has stopped
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementStopped, bool, bReachedEndOfPlayback);` — Fired on the game thread when it has received notification that the pathed movement has stopped
- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChaosMover_OnPathedMovementBounced);` — Fired on the game thread when it has received notification that the pathed movement has bounced (reached the end of one leg in a round trip)
- L25 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChaosMover_OnPathedMovementBounced);` — Fired on the game thread when it has received notification that the pathed movement has bounced (reached the end of one leg in a round trip)
- L27 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementReversePlaybackChanged, bool, bIsReversePlayback);` — Fired on the game thread when reverse playback has changed
- L27 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementReversePlaybackChanged, bool, bIsReversePlayback);` — Fired on the game thread when reverse playback has changed
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementLoopingPlaybackChanged, bool, bIsLoopingPlayback);` — Fired on the game thread when looping playback has changed
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementLoopingPlaybackChanged, bool, bIsLoopingPlayback);` — Fired on the game thread when looping playback has changed
- L31 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementOneWayPlaybackChanged, bool, bIsOneWayPlayback);` — Fired on the game thread when one way playback has changed
- L31 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChaosMover_OnPathedMovementOneWayPlaybackChanged, bool, bIsOneWayPlayback);` — Fired on the game thread when one way playback has changed

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPathedMovementDebugDrawComponent.h` (Public)


#### class `UChaosPathedMovementDebugDrawInterface`  
`class UChaosPathedMovementDebugDrawInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IChaosPathedMovementDebugDrawInterface`  
`class IChaosPathedMovementDebugDrawInterface : public IInterface`  
_L21-37_
- inherits: `IInterface`
- desc: ChaosPathedMovementDebugDrawInterface: Controls the debug draws of pathed movement modes, showing a preview mesh at a given overall progression on the path
- L28 _public prototype_ `bool ShouldDisplayProgressPreviewMesh() const;` — `UFUNCTION(BlueprintNativeEvent)` — Whether pathed movement debug draws should display a preview mesh at a given overall progress of the aggregate path
- L32 _public prototype_ `float GetPreviewMeshOverallPathProgress() const;` — `UFUNCTION(BlueprintNativeEvent)` — How far along the path progression to preview the controlled mesh
- L36 _public prototype_ `UMaterialInterface* GetProgressPreviewMeshMaterial() const;` — `UFUNCTION(BlueprintNativeEvent)` — The material to apply to the preview mesh displayed along the path at PreviewMeshProgress (leave empty for an exact duplicate)

#### class `UChaosPathedMovementDebugDrawComponent`  
`class UChaosPathedMovementDebugDrawComponent : public UDebugDrawComponent`  
_L41-76_
- reflection: `UCLASS()`
- inherits: `UDebugDrawComponent`
- desc: @todo DanH: Ideally clicking anything drawn by this would select the mover comp in the editor. I think I need a whole FComponentVisualizer set up for that though?
- L46 _public prototype_ `UChaosPathedMovementDebugDrawComponent();`
- L48 _public prototype_ `virtual void OnRegister() override;`
- L49 _public prototype_ `virtual void OnUnregister() override;`
- L51 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L53 _public member_ `TArray<FDebugRenderSceneProxy::FDebugLine> DebugLines;`
- L54 _public member_ `TArray<FDebugRenderSceneProxy::FDashedLine> DebugDashedLines;`
- L55 _public member_ `TArray<FDebugRenderSceneProxy::FArrowLine> DebugArrowLines;`
- L56 _public member_ `TArray<FDebugRenderSceneProxy::FWireStar> DebugStars;`
- L57 _public member_ `TArray<FDebugRenderSceneProxy::FSphere> DebugSpheres;`
- L60 _protected prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L61 _protected prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L63 _protected prototype_ `void UpdatePreviewMeshComp(bool bForce = false);`
- L64 _protected prototype_ `void DestroyProgressPreviewMeshComp();`
- L65 _protected prototype_ `UMeshComponent* GetOwnerMeshRoot() const;`
- L66 _protected prototype_ `UMoverComponent* GetMoverComponent() const;`
- L69 _protected prototype_ `void HandleObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L73 _protected member_ `TObjectPtr<UMeshComponent> ProgressPreviewMeshComp = nullptr;` — `UPROPERTY(Transient)`
- L75 _protected member_ `TObjectPtr<UObject> DebugDrawInterfaceObject;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPathedMovementMode.h` (Public)


#### class `UChaosPathedMovementMode`  
`class UChaosPathedMovementMode : public UChaosMovementMode , public IChaosMovementActuationInterface , public IChaosPathedMovementModeInterface , public IChaosPostSimulationTickInterface`  
_L23-157_
- reflection: `UCLASS(Within = MoverComponent)`
- inherits: `UChaosMovementMode,IChaosMovementActuationInterface,IChaosPathedMovementModeInterface,IChaosPostSimulationTickInterface`
- desc: Base for any movement mode that proceeds along a defined path within a specified amount of time
- L32 _public prototype_ `UChaosPathedMovementMode(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;` — UBaseMovementMode
- L36 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L37 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L38 _public prototype_ `virtual bool UsesMovementBasisTransform() const override;`
- L41 _public prototype_ `virtual bool ShouldUseConstraint() const override;` — IChaosConstraintMovementModeInterface
- L42 _public prototype_ `virtual const Chaos::FPBDJointSettings& GetConstraintSettings() const override;`
- L45 _public prototype_ `virtual FTransform CalcTargetTransform(float OverallPathProgress, const FTransform& BasisTransform) const override;` — IChaosPathedMovementModeInterface
- L48 _public prototype_ `virtual void PostSimulationTick_Async(FChaosMoverPostSimContext& Context) override;` — IChaosPostSimulationTickInterface
- L53 _public prototype_ `EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;` — UBaseMovementMode Interface
- L57 _public prototype_ `virtual void InitializePath();` — Called when the owning UChaosPathedPhysicsMoverComponent is registered (i.e. at both edit and game time)
- L61 _public prototype_ `UChaosPathedMovementPatternBase* BP_FindPattern(TSubclassOf<UChaosPathedMovementPatternBase> PatternType) const;` — `UFUNCTION(BlueprintPure, Category = PathedMovementMode, DisplayName = "Find Pattern", meta=(DeterminesOutputType = PatternType))` — Finds the first path pattern on this mode of the given type, if there is one
- L69 _public prototype_ `void SetOneWayTripDuration_BeginPlayOnly(float NewDuration);` — `UFUNCTION(BlueprintCallable, Category = PathedMovementMode, DisplayName = "Set Path Duration (BeginPlay only)")` — Set the time it takes to travel one way along this path from start to end. Only valid to call in BeginPlay or the Construction Script, ignored otherwise. Once play has begun, the path duration can be modified indirectly via SetMovementTimeDilation on the owning PathedMoverComponent
- L70 _public function_ `float GetOneWayTripDuration() const`
- L73 _protected prototype_ `void OnPlaybackStarting(const FMoverTimeStep& SimTime);`
- L74 _protected prototype_ `void OnPlaybackStopping(const FMoverTimeStep& SimTime, bool bReachedEndOfPlayback);`
- L75 _protected prototype_ `void OnPlaybackBounced(const FMoverTimeStep& SimTime);`
- L76 _protected prototype_ `void OnInReverseChanging(const FMoverTimeStep& SimTime, bool bNewInReverse);`
- L77 _protected prototype_ `void OnLoopingChanging(const FMoverTimeStep& SimTime, bool bNewLooping);`
- L78 _protected prototype_ `void OnOneWayChanging(const FMoverTimeStep& SimTime, bool bNewOneWay);`
- L80 _protected prototype_ `void SetDefaultJointConstraintProperties();`
- L96 _private member_ `bool bUseJointConstraint = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathed Movement Mode", meta = (AllowPrivateAccess))` — True to have the updated component be able to respond to physics inputs by being "pulled" along the path using a joint constraint configured using JointConstraintProperties below. If false, no joint will be used, and the affected component will be moved kinematically (i.e. independent of other physics effects and treated as though it has infinite mass in the physics sim) and never deviate from the path. Note that the movement is calculated on the worker thread either way, so it will correctly interact with other bodies in the sim. Ex: Platform moving along a path in a straight line. If this is enabled, the platform could wobble, dip, shake, stall, etc. in response to physics forces/impulses (depending on the joint and physics properties of the platform). If this is disabled, the platform will rigidly move along the path and ignore all physics.
- L103 _private member_ `FConstraintProfileProperties JointConstraintProperties;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement Mode", meta = (EditCondition = bUseJointConstraint))` — Configuration of the joint constraint that (if enabled) pulls the updated component along the path The default settings are for a very stiff joint that allows just a little bit of "play"
- L107 _private member_ `float OneWayPlaybackDuration = 5.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathed Movement Mode", meta = (ClampMin=0, UIMin=0, Units=Seconds, AllowPrivateAccess))` — Total duration in seconds of a one-way trip from start to end.
- L120 _private member_ `TArray<TObjectPtr<UChaosPathedMovementPatternBase>> PathPatterns;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Pathed Movement Mode", meta = (AllowPrivateAccess))` — The set of patterns to follow that combine to form the path the component will follow NOTE: Order can matter here!! The patterns are evaluated each physics frame in order starting from the front. Each successive pattern is aware of the aggregate results from the previous patterns. In most cases, this doesn't matter, as the pattern calculates the target transform against the static path origin point. However, some patterns necessarily determine their target based on the calculated target to that point For example, the LookAtRotationPattern calculates the look-at rotation target based on the target location
- L124 _private member_ `EAlphaBlendOption Easing = EAlphaBlendOption::Linear;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathed Movement Mode", meta = (AllowPrivateAccess))` — The kind of easing to apply when traveling along the path
- L128 _private member_ `TObjectPtr<UCurveFloat> CustomEasingCurve = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathed Movement Mode", meta = (EditCondition = "Easing==EAlphaBlendOption::Custom", AllowPrivateAccess))` — If using a custom ease, this is the curve that will be used. If blank, will fall back to standard linear interpolation.
- L130 _private member_ `Chaos::FPBDJointSettings JointSettings;`
- L134 _private member_ `bool bIsUsingAsyncPhysics = true;` — Whether the physics simulation runs asynchronously with a fixed timestep. Cached from the simulation at registration time; used only when recording LastChangeTime reference points.
- L138 _private prototype_ `FMoverTime MakeChangeTime(const FMoverTimeStep& TimeStep) const;` — Builds the FMoverTime reference point to store when a change occurs (start of the current frame). Sets FrameCount in fixed-dt (async) mode, leaves it INDEX_NONE in variable-dt (non-async) mode.
- L142 _private member_ `bool bDebugDrawAggregatePath = true;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement Mode|Debug")` — True to draw debug lines for the aggregate path resulting from all the patterns in the path (i.e. the path that will actually be followed in game)
- L146 _private member_ `bool bAllowPatternDebugDrawing = true;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement Mode|Debug")` — True to allow individual patterns to draw debug representations. Can be toggled individually on each pattern as well, this is a master switch for convenience.
- L150 _private member_ `FColor PathDebugDrawColor = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Pathed Movement Mode|Debug", meta = (EditCondition = bDebugDrawAggregatePath))` — The color used when drawing the aggregate path
- L155 _private member_ `mutable FChaosPathedMovementModeDebugData DebugData;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPathedMovementPatternBase.h` (Public)


#### enum `EChaosPatternAxisMaskFlags`  
`enum class EChaosPatternAxisMaskFlags : uint8`  
_L18-27_
- reflection: `UENUM(Flags, meta = (Bitflags))`
- desc: @todo DanH: What's the Flags specifier for? Does that do everything now or do I still need the Bitflags meta?
- L20 _public enumerator_ `None = 0 UMETA(Hidden)`
- L22 _public enumerator_ `X = 1 UMETA(DisplayName = "X / Roll")`
- L23 _public enumerator_ `Y = 1 << 1 UMETA(DisplayName = "Y / Pitch")`
- L24 _public enumerator_ `Z = 1 << 2 UMETA(DisplayName = "Z / Yaw)"), All = X | Y | Z UMETA(Hidden) }; ENUM_CLASS_FLAGS(EChaosPatternAxisMaskFlags); UCLASS(Abstract, Within = ChaosPathedMovementMode, DefaultToInstanced, Blueprintable, BlueprintType, EditInlineNew) class UChaosPathedMovementPatternBase : public UObject`
- L26 _public enumerator_ `All = X | Y | Z UMETA(Hidden)`

#### class `UChaosPathedMovementPatternBase`  
`class UChaosPathedMovementPatternBase : public UObject`  
_L31-167_
- reflection: `UCLASS(Abstract, Within = ChaosPathedMovementMode, DefaultToInstanced, Blueprintable, BlueprintType, EditInlineNew)`
- inherits: `UObject`
- L36 _public prototype_ `virtual void InitializePattern(UChaosMoverSimulation* InSimulation);`
- L38 _public function_ `const UChaosMoverSimulation* GetSimulation() const`
- L43 _public prototype_ `UChaosPathedMovementMode& GetMovementMode() const;`
- L46 _public prototype_ `FTransform CalcTargetTransform(float OverallPathProgress, const FTransform& BasisTransform) const;` — Calculates the path target transform in world coordinates, at OverallPathProgress, given the path basis transform
- L48 _public function_ `virtual bool DebugDrawUsingStepSamples() const`
- L49 _public function_ `virtual void AppendDebugDrawElements(UChaosPathedMovementDebugDrawComponent& DebugDrawComp, FBoxSphereBounds::Builder& InOutDebugBoundsBuilder)`
- L64 _protected function_ `virtual FTransform CalcUnmaskedTargetTransform(float PatternProgress, const FTransform& BasisTransform) const` — Where patterns calculate their target transforms at the given path progress The transform returned is in world coordinates, given the path basis transform BasisTransform Axis masking is applied to this result before it's actually used.
- L69 _protected prototype_ `FTransform CalcMaskedTargetTransform(float PatternProgress, const FTransform& BasisTransform) const;` — Utility function that calls CalcUnmaskedTargetTransform and then applies masking. This is mostly for debug drawing, which wants to deal with PatternProgress and not OverallPathProgress but also get the masked transform
- L74 _protected prototype_ `float ConvertPathToPatternProgress(float OverallPathProgress) const;` — Converts an overall path progress to a progress on the pattern Returns -1 if it can't do it, say, e.g. if somehow StartAtPathProgress > EndAtPathProgress
- L80 _protected prototype_ `float ConvertPatternToPathProgress(float PatternProgress) const;` — Converts a pattern progress to one overall path possible progress If the pattern is looping, it will return the path progress corresponding to the first loop Note that ConvertPathToPatternProgress is not invertible, it is a surjective mapping (i.e. many-to-one mapping)
- L88 _protected member_ `uint8 TranslationMasks = (uint8)EChaosPatternAxisMaskFlags::None;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (Bitmask, BitmaskEnum = "/Script/ChaosMover.EChaosPatternAxisMaskFlags"))` — Along which axes is this pattern disallowed from modifying the translation/location of the updated component?
- L92 _protected member_ `uint8 RotationMasks = (uint8)EChaosPatternAxisMaskFlags::None;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (Bitmask, BitmaskEnum = "/Script/ChaosMover.EChaosPatternAxisMaskFlags"))` — Along which axes is this pattern disallowed from modifying the rotation of the updated component?
- L96 _protected member_ `uint8 ScaleMasks = (uint8)EChaosPatternAxisMaskFlags::None;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (Bitmask, BitmaskEnum = "/Script/ChaosMover.EChaosPatternAxisMaskFlags"))` — Along which axes is this pattern disallowed from modifying the scale of the updated component?
- L103 _protected member_ `bool bStartAfterPreviousPattern = false;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern")` — If true, this pattern will not begin to take effect until the previous pattern has completed. Note: If true and the previous pattern's EndAtPathProgress is 1, this pattern will never start.
- L107 _protected member_ `float StartAtPathProgress = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (EditCondition = "!bStartAfterPreviousPattern", UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — The overall path progress when this pattern should begin, where 0 is the start of the path and 1 is the end. Must be less than EndAtPathProgress.
- L111 _protected member_ `float EndAtPathProgress = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — The overall path progress when this pattern should complete, where 0 is the start of the path and 1 is the end. Must be greater than StartAtPathProgress.
- L118 _protected member_ `float LoopOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — This is an offset within a loop of the pattern, allowing to offset the start of the loop within the path. For example if this is set to 0.2, a loop will start at 20% of the path (instead of at the start), progress to the end, then wrap around to the start and continue progressing to 20%. If the path itself is not a loop (if start and end are not the same), then the position will jump abruptly when it wraps around.
- L126 _protected member_ `int32 NumLoopsPerPath = 1;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (UIMin = 0, ClampMin = 0))` — The number of loops to complete within the active span of this pattern (i.e. between StartAtPathProgress and EndAtPathProgress) on a single run along the full aggregate path. Setting to 0 effectively disables this pattern.
- L130 _protected member_ `bool IsOneWay = true;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern")` — If true, each loop plays forward only (0 → 1). If false, each loop plays there-and-back (0 → 1 → 0).
- L138 _protected member_ `bool bBounceAtEnds = false;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern")` — When true, progress bounces at 0 and 1 instead of crossing the seam (wrapping). Use this for non-looping paths to avoid teleports at the endpoints. When false (default), progress wraps at the seam — correct for geometrically looping paths.
- L145 _protected member_ `bool bOrientComponentToPath = false;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern")` — If true, the component will be rotated to face in the direction of this pattern's motion. To have the component face in the direction of the aggregate path, enable this on all movement patterns.
- L149 _protected member_ `EAlphaBlendOption Easing;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern")` — The kind of easing to apply when traveling along the path
- L153 _protected member_ `TObjectPtr<UCurveFloat> CustomEasingCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern", meta = (EditCondition = "Easing==EAlphaBlendOption::Custom"))` — If using a custom ease, this is the curve that will be used. If blank, will fall back to standard linear interpolation.
- L157 _protected member_ `bool bDebugDrawPattern = true;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern|Debug")` — True to draw debug lines for this specific pattern in editor views
- L162 _protected member_ `FColor PatternDebugDrawColor;` — `UPROPERTY(EditAnywhere, Category = "Path Pattern|Debug", meta = (EditCondition = bDrawDebug))` — The color used for debug draws of this pattern
- L164 _protected member_ `UChaosMoverSimulation* Simulation = nullptr;`

#### Free symbols / members of external scopes

- L28 _prototype_ `ENUM_CLASS_FLAGS(EChaosPatternAxisMaskFlags);`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPathedMovementTypes.h` (Public)


#### struct `FChaosMutablePathedMovementProperties`  
`struct FChaosMutablePathedMovementProperties`  
_L27-59_
- reflection: `USTRUCT()`
- desc: Properties that can change during game-time and affect path movement calculations. Split into its own struct because both the input and sync state structs want to hold onto these.
- L33 _public member_ `bool bWantsToPlay = false;` — `UPROPERTY(EditAnywhere, Category = ChaosMover)` — True = Wants to being playing the path, False = Wants to be stopped
- L37 _public member_ `bool bWantsReversePlayback = false;` — `UPROPERTY(EditAnywhere, Category = ChaosMover)` — True = Reverse, False = Forward
- L42 _public member_ `bool bWantsLoopingPlayback = false;` — `UPROPERTY(EditAnywhere, Category = ChaosMover)` — True = Looping, False = Will stop next time it reaches the end (that end could be 0 or 1 depending on bWantsOneWayPlayback and bWantsReversePlayback)
- L46 _public member_ `bool bWantsOneWayPlayback = false;` — `UPROPERTY(EditAnywhere, Category = ChaosMover)` — True = One way playback (0->1), False = Round trip, there and back (0->1->0)
- L54 _public prototype_ `void NetSerialize(FArchive& Ar);`
- L55 _public prototype_ `void ToString(FAnsiStringBuilderBase& Out) const;`
- L57 _public prototype_ `bool operator==(const FChaosMutablePathedMovementProperties& Other) const;`
- L58 _public function_ `bool operator!=(const FChaosMutablePathedMovementProperties& Other) const`

#### struct `FChaosPathedMovementInputs`  
`struct FChaosPathedMovementInputs : public FMoverDataStructBase`  
_L73-94_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Frame inputs for all pathed movement Any property that can change during game time must be delivered in this way, only immutable properties can be safely referenced directly on the object they come from (usually the movement mode) NOTE: MovementStartFrame and LastChangeFrame use integer frame numbers for scheduling and ordering. This is correct in async (fixed-dt) mode, where both server and client share the same synchronized frame counter. In non-async (variable-dt) mode, frame numbers are a local monotonic counter and are NOT synchronized across endpoints. The current implicit assumption is: networked => fixed-dt, variable-dt => standalone only. To support variable-dt networking properly, these fields would need to become FMoverTime.
- L78 _public member_ `int32 MovementStartFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L81 _public member_ `int32 LastChangeFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L84 _public member_ `FChaosMutablePathedMovementProperties Props;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)`
- L87 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;` — Implementation of FMoverDataStructBase
- L88 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L89 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L90 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L91 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L92 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L93 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `FChaosPathedMovementState`  
`struct FChaosPathedMovementState : public FMoverDataStructBase`  
_L98-142_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: State of a pathed movement that persists from frame to frame
- L110 _public member_ `float LastChangePathProgress = 0.0f;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — A path progress is a value between 0 and 1 that can be directly used along the path to calculate the position on it, 0.0 being a the start of the progression along the path, 1.0 being at the end of that progression. Note that this is not necessarily the start and end of that path as the start could be offset relative to the path primitive (say, a spline) LastChangePathProgress is the path progress we were at the last time an important change happened. We calculate the current progress based on that LastChangePathProgress, the number of frames elapsed since that change, and the progression rate, assuming all properties involved in updating that progress have not changed
- L116 _public member_ `FMoverTime LastChangeTime;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — The time at which the last change in movement properties occurred (set to the start of that frame). FrameCount is valid in fixed-dt (async) mode; TimeMs is valid in variable-dt (non-async) mode. @see LastChangePathProgress, FMoverTime::ElapsedSecondsTo
- L121 _public member_ `int32 LatestMovementStartFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — The frame at which we last started playing, or INDEX_NONE if we were never playing. Used to order start requests against MovementStartFrame from inputs. See note on FChaosPathedMovementInputs.
- L125 _public member_ `bool bIsPathProgressionIncreasing = true;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — Whether traveling from 0 to 1 (true) or 1 to 0 (false)
- L130 _public member_ `bool bHasFinished = false;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — Whether the previous playback finished by reaching the end of its overall progression (could be 0 or 1 depending on movement properties)
- L134 _public member_ `FChaosMutablePathedMovementProperties PropertiesInEffect;` — `UPROPERTY(VisibleAnywhere, Category = ChaosMover)` — The mutable properties in effect
- L136 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L137 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L138 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L139 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L140 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L141 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`

#### struct `FChaosPathedMovementModeDebugData`  
`struct FChaosPathedMovementModeDebugData : public FMoverDataStructBase`  
_L145-209_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- L149 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L150 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L152 _public function_ `void Advance()`
- L166 _public member_ `int32 PreviousServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")` — This is the server frame last time we ticked, it might not be ServerFrame-1 if we are resimming
- L169 _public member_ `int32 ServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L172 _public member_ `FChaosPathedMovementState PreSimMoveState;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L175 _public member_ `FChaosPathedMovementState PostSimMoveState;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L178 _public member_ `FVector PreviousWorldTranslation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L181 _public member_ `FRotator PreviousWorldRotation = FRotator::ZeroRotator;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L184 _public member_ `FVector NewWorldTranslation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L187 _public member_ `FRotator NewWorldRotation = FRotator::ZeroRotator;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L190 _public member_ `bool bPlaybackStartedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L193 _public member_ `bool bPlaybackStoppedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L196 _public member_ `bool bPlaybackBouncedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L199 _public member_ `bool bPlaybackReachedEndThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L202 _public member_ `bool bPlaybackReverseChangedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L205 _public member_ `bool bPlaybackLoopingChangedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`
- L208 _public member_ `bool bPlaybackOneWayChangedThisFrame = false;` — `UPROPERTY(VisibleAnywhere, Category = "Mover Info")`

#### struct `FPathedMovementStartedEventData`  
`struct FPathedMovementStartedEventData : public FMoverSimulationEventData`  
_L212-226_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L216 _public function_ `FPathedMovementStartedEventData(const FMoverTimeStep& InEventTime) : FMoverSimulationEventData(InEventTime)`
- L220 _public function_ `FPathedMovementStartedEventData()`
- L222 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`

#### struct `FPathedMovementStoppedEventData`  
`struct FPathedMovementStoppedEventData : public FMoverSimulationEventData`  
_L229-246_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L233 _public function_ `FPathedMovementStoppedEventData(const FMoverTimeStep& InEventTime, bool InbReachedEndOfPlayback) : FMoverSimulationEventData(InEventTime) , bReachedEndOfPlayback(InbReachedEndOfPlayback)`
- L238 _public function_ `FPathedMovementStoppedEventData()`
- L240 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L245 _public member_ `bool bReachedEndOfPlayback = false;`

#### struct `FPathedMovementBouncedEventData`  
`struct FPathedMovementBouncedEventData : public FMoverSimulationEventData`  
_L249-263_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L253 _public function_ `FPathedMovementBouncedEventData(const FMoverTimeStep& InEventTime) : FMoverSimulationEventData(InEventTime)`
- L257 _public function_ `FPathedMovementBouncedEventData()`
- L259 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`

#### struct `FPathedMovementInReverseChangedEventData`  
`struct FPathedMovementInReverseChangedEventData : public FMoverSimulationEventData`  
_L266-283_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L270 _public function_ `FPathedMovementInReverseChangedEventData(const FMoverTimeStep& InEventTime, bool InbNewInReverse) : FMoverSimulationEventData(InEventTime) , bNewInReverse(InbNewInReverse)`
- L275 _public function_ `FPathedMovementInReverseChangedEventData()`
- L277 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L282 _public member_ `bool bNewInReverse = false;`

#### struct `FPathedMovementLoopingChangedEventData`  
`struct FPathedMovementLoopingChangedEventData : public FMoverSimulationEventData`  
_L286-303_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L290 _public function_ `FPathedMovementLoopingChangedEventData(const FMoverTimeStep& InEventTime, bool InbNewLooping) : FMoverSimulationEventData(InEventTime) , bNewLooping(InbNewLooping)`
- L295 _public function_ `FPathedMovementLoopingChangedEventData()`
- L297 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L302 _public member_ `bool bNewLooping = false;`

#### struct `FPathedMovementOneWayChangedEventData`  
`struct FPathedMovementOneWayChangedEventData : public FMoverSimulationEventData`  
_L306-323_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L310 _public function_ `FPathedMovementOneWayChangedEventData(const FMoverTimeStep& InEventTime, bool InbNewOneWay) : FMoverSimulationEventData(InEventTime) , bNewOneWay(InbNewOneWay)`
- L315 _public function_ `FPathedMovementOneWayChangedEventData()`
- L317 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L322 _public member_ `bool bNewOneWay = false;`

#### class `UChaosMovementActuationInterface`  
`class UChaosMovementActuationInterface : public UInterface`  
_L328-331_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for mover modes which can move the controlled component with a physical constraint or kinematically

#### class `IChaosMovementActuationInterface`  
`class IChaosMovementActuationInterface`  
_L332-342_
- L338 _public prototype_ `virtual bool ShouldUseConstraint() const = 0;` — Whether the simulation should use a constraint to move the controlled particle, or moving it kinematically
- L341 _public prototype_ `virtual const Chaos::FPBDJointSettings& GetConstraintSettings() const = 0;` — Constraint settings of the joint constraint, only valid when ShouldUseConstraint() is true

#### class `UChaosPathedMovementModeInterface`  
`class UChaosPathedMovementModeInterface : public UInterface`  
_L351-354_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for mover modes which target transform is parameterized by an overall path progression, a value in [0, 1] 0 being at the beginning of the progression, 1 being at the end of that progression. A given progression should always result in the same resulting transform, but the spatial trajectory resulting from the progression varying from 0 to 1 may loop or revisit the same curves multiple times Implementing this interface implies the usage of a path basis (centralized in the simulation, not in modes) that the path is relative to

#### class `IChaosPathedMovementModeInterface`  
`class IChaosPathedMovementModeInterface`  
_L355-362_
- L361 _public prototype_ `virtual FTransform CalcTargetTransform(float Progression, const FTransform& BasisTransform) const = 0;` — Returns the transform on the path at Progression

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace ChaosMover` (scope `UE`)
- L12 _namespace_ `namespace PathBlackboard` (scope `UE::ChaosMover`)
- L14 _variable_ `const FName TargetRelativeTransform = TEXT("Tar` (scope `UE::ChaosMover::PathBlackboard`)
- L17 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosPointMovementPathPattern.h` (Public)


#### enum `EChaosPointMovementLocationBasis`  
`enum class EChaosPointMovementLocationBasis : uint8`  
_L13-21_
- reflection: `UENUM()`
- L16 _public enumerator_ `PreviousPoint` — The location is relative to the previous point in the path
- L18 _public enumerator_ `PathOrigin` — The location is relative to the origin of the path
- L20 _public enumerator_ `World` — The location is relative to the world origin

#### struct `FChaosPointMovementPathPoint`  
`struct FChaosPointMovementPathPoint`  
_L24-74_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public function_ `FChaosPointMovementPathPoint()`
- L35 _public member_ `EChaosPointMovementLocationBasis Basis = EChaosPointMovementLocationBasis::PreviousPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Location)` — Basis that the location of this point is relative to
- L39 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Location, meta = (MakeEditWidget = true))` — The location to move toward (i.e. root component location by default)
- L43 _public member_ `EChaosPointMovementLocationBasis RotationBasis = EChaosPointMovementLocationBasis::PreviousPoint;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Location)` — Basis that the rotation at this point is relative to
- L47 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Location, meta = (MakeEditWidget = true))` — The rotation to rotate toward
- L49 _public prototype_ `FTransform GetWorldTransform(const FTransform& BasisTransform) const;`
- L56 _public member_ `mutable float Progress = 0.f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = Location)` — The progress along the path that this point corresponds to. Read-only, calculated automatically based on number of points, distances between them, and movement rules for the point
- L60 _public member_ `mutable float PathDistanceFromStart = 0.f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = Location)` — Distance from the start of the path to this point. Read-only.
- L64 _public member_ `mutable FVector BasedLocation = FVector::ZeroVector;` — This location is precomputed as a function of Location and Basis. If Basis is World, then this is a world location. Otherwise this location is relative to the BasisTransform that will be provided (@see CalcUnmaskedTargetTransform)
- L67 _public member_ `mutable FQuat BasedRotation = FQuat::Identity;` — This rotation is precomputed as a function of Rotation and Basis. If RotationBasis is World, then this is a world rotation. Otherwise this rotation is relative to the BasisTransform that will be provided (@see CalcUnmaskedTargetTransform)
- L70 _public member_ `mutable EChaosPointMovementLocationBasis EffectiveBasis = EChaosPointMovementLocationBasis::PathOrigin;` — This basis indicates whether the BasedLocation is relative to the path basis or in world coordinates It is either PathOrigin or World, but cannot be PreviousPoint, since the purpose of BasedLocation is to precompute as much as possible beforehand
- L73 _public member_ `mutable EChaosPointMovementLocationBasis EffectiveRotationBasis = EChaosPointMovementLocationBasis::PathOrigin;` — This basis indicates whether the BasedRotation is relative to the path basis or in world coordinates It is either PathOrigin or World, but cannot be PreviousPoint, since the purpose of BasedRotation is to precompute as much as possible beforehand

#### class `UChaosPointMovementPathPattern`  
`class UChaosPointMovementPathPattern : public UChaosPathedMovementPatternBase`  
_L78-108_
- reflection: `UCLASS()`
- inherits: `UChaosPathedMovementPatternBase`
- desc: Movement pattern that moves between explicitly defined points
- L83 _public prototype_ `virtual void InitializePattern(UChaosMoverSimulation* InSimulation) override;`
- L86 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L89 _public prototype_ `virtual void AppendDebugDrawElements(UChaosPathedMovementDebugDrawComponent& DebugDrawComp, FBoxSphereBounds::Builder& InOutDebugBoundsBuilder) override;`
- L92 _protected prototype_ `virtual FTransform CalcUnmaskedTargetTransform(float PatternProgress, const FTransform& BasisTransform) const override;`
- L94 _protected prototype_ `void RefreshAssignedPointProgress(const FTransform& PathBasisTransform) const;`
- L95 _protected prototype_ `FTransform GetPathBasisTransform() const;`
- L99 _protected member_ `TArray<FChaosPointMovementPathPoint> PathPoints;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Movement Pattern")` — Relative point locations to move toward, in sequence from first to last
- L103 _protected member_ `mutable float TotalPathDistance = 0.f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "Point Movement Pattern")` — The sum total distance of this path. Read-only for reference only.
- L105 _protected member_ `mutable bool bHasAssignedPointProgress = false;`
- L107 _protected member_ `mutable FTransform CachedPathBasisTransform = FTransform::Identity;`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/ChaosSplineMovementPathPattern.h` (Public)


#### struct `FChaosSplinePathPatternPointData`  
`struct FChaosSplinePathPatternPointData`  
_L15-22_
- reflection: `USTRUCT()`
- desc: This isn't formal "spline metadata" because that requires a custom spline and component - we want to add info to vanilla splines
- L21 _public member_ `float SplinePointKey = 0.f;` — `UPROPERTY()` — Key of the spline point (or somewhere between two points) where this metadata applies

#### class `UChaosSplineMovementPathPattern`  
`class UChaosSplineMovementPathPattern : public UChaosPathedMovementPatternBase`  
_L25-68_
- reflection: `UCLASS()`
- inherits: `UChaosPathedMovementPatternBase`
- L30 _public prototype_ `virtual void InitializePattern(UChaosMoverSimulation* InSimulation) override;`
- L33 _public function_ `virtual bool DebugDrawUsingStepSamples() const override` — The spline is already drawn, no need to draw it again at lower rez
- L35 _public function_ `bool HasValidBounds() const`
- L38 _protected prototype_ `virtual FTransform CalcUnmaskedTargetTransform(float PatternProgress, const FTransform& BasisTransform) const override;`
- L42 _protected member_ `float LowerBound = 0.f;` — `UPROPERTY(EditAnywhere, Category = SplinePathPattern, meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — How far into the spline the movement path actually begins.
- L46 _protected member_ `float UpperBound = 1.f;` — `UPROPERTY(EditAnywhere, Category = SplinePathPattern, meta = (UIMin = 0.f, ClampMin = 0.f, UIMax = 1.f, ClampMax = 1.f))` — How far into the spline the movement path ends. Must be greater than the lower bound.
- L53 _protected member_ `bool bOffsetsModifyDuration = false;` — `UPROPERTY(EditAnywhere, Category = SplinePathPattern)` — If true, the path duration will be shortened according to how much of the spline is not being followed. If false (default), the path duration is unchanged, so the object will move slower when the usable spline range is reduced.
- L56 _protected member_ `bool bApplySplineScaling = false;` — `UPROPERTY(EditAnywhere, Category = SplinePathPattern)`
- L64 _protected member_ `FComponentReference SplineComponentRef;` — `UPROPERTY(EditAnywhere, DisplayName = "Spline Component", Category = SplinePathPattern, meta = (AllowAnyActor, UseComponentPicker, AllowedClasses = "/Script/Engine.SplineComponent"))` — Optional property to specify the spline component that defines the path to follow. If blank, we'll use the first spline component we find in this actor. This is only necessary to set if you have multiple spline components on the actor, or want to follow a spline on an external actor. Thread Safety Warning, this spline cannot be modified whilst in use
- L67 _protected member_ `TObjectPtr<const USplineComponent> SplineComp;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/PathedMovement/Transitions/ChaosPathedMovementReachedEndTransition.h` (Public)


#### class `UChaosPathedMovementReachedEndTransition`  
`class UChaosPathedMovementReachedEndTransition : public UChaosMovementModeTransition`  
_L13-26_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UChaosMovementModeTransition`
- desc: Transition checking if an ongiong pathed movement mode has reached the end of the path
- L18 _public prototype_ `UChaosPathedMovementReachedEndTransition(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L21 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L25 _public member_ `FName TransitionToMode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Parameters)` — Name of movement mode to transition to when the pathed movement has reached the end of the path

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSMOVER_API`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Utilities/ChaosGroundMovementUtils.h` (Public)


#### struct `FRequestedMoveParams`  
`struct FRequestedMoveParams`  
_L14-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for controlled ground movement function
- L19 _public member_ `FQuat WorldToGravityQuat = FQuat::Identity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L22 _public member_ `FRotator PriorOrientation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L25 _public member_ `FVector PriorVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L28 _public member_ `FVector RequestedVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L31 _public member_ `FVector GroundNormal = FVector::UpVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L34 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L37 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L40 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L43 _public member_ `float Deceleration = 8000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L46 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L49 _public member_ `bool bRequestedMoveWithMaxSpeed = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`
- L52 _public member_ `bool bShouldComputeAcceleration = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ChaosMover)`

#### class `UChaosGroundMovementUtils`  
`class UChaosGroundMovementUtils : public UBlueprintFunctionLibrary`  
_L56-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L63 _public prototype_ `static FVector ComputeLocalGroundVelocity_Internal(const FVector& Position, const FFloorCheckResult& FloorResult);` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)` — Computes the local velocity at the supplied position of the hit object in floor result
- L67 _public prototype_ `static FProposedMove ComputeRequestedMove(const FRequestedMoveParams& Params);` — `UFUNCTION(BlueprintCallable, Category = ChaosMover)` — Computes the local velocity at the supplied position of the hit object in floor result
- L69 _public prototype_ `static Chaos::FPBDRigidParticleHandle* GetRigidParticleHandleFromFloorResult_Internal(const FFloorCheckResult& FloorResult);`

### `Plugins/Experimental/ChaosMover/Source/ChaosMover/Public/ChaosMover/Utilities/ChaosMoverQueryUtils.h` (Public)


#### struct `UE::ChaosMover::Utils::FFloorSweepParams`  
`struct FFloorSweepParams`  
_L13-26_
- L15 _public member_ `FCollisionResponseParams ResponseParams;`
- L16 _public member_ `FCollisionQueryParams QueryParams;`
- L17 _public member_ `FVector Location;`
- L18 _public member_ `FVector DeltaPos;`
- L19 _public member_ `FVector UpDir;`
- L20 _public member_ `const UWorld* World;`
- L21 _public member_ `float QueryDistance;`
- L22 _public member_ `float QueryRadius;`
- L23 _public member_ `float MaxWalkSlopeCosine;`
- L24 _public member_ `float TargetHeight;`
- L25 _public member_ `ECollisionChannel CollisionChannel;`

#### struct `UE::ChaosMover::Utils::FCapsuleOverlapTestParams`  
`struct FCapsuleOverlapTestParams`  
_L30-41_
- L32 _public member_ `FCollisionResponseParams ResponseParams;`
- L33 _public member_ `FCollisionQueryParams QueryParams;`
- L34 _public member_ `FVector Location;`
- L35 _public member_ `FVector UpDir;`
- L36 _public member_ `const UWorld* World;`
- L37 _public member_ `float CapsuleHalfHeight;`
- L38 _public member_ `float CapsuleRadius;`
- L39 _public member_ `ECollisionChannel CollisionChannel;`
- L40 _public member_ `bool bBlockOnDynamic = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ChaosMover` (scope `UE`)
- L11 _namespace_ `namespace Utils` (scope `UE::ChaosMover`)
- L28 _prototype_ `extern void FloorSweep_Internal(const FFloorSweepParams& Params, FFloorCheckResult& OutFloorResult, FWaterCheckResult& OutWaterResult);` (scope `UE::ChaosMover::Utils`)
- L43 _prototype_ `extern bool CapsuleOverlapTest_Internal(const FCapsuleOverlapTestParams& Params);` (scope `UE::ChaosMover::Utils`)
