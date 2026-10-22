# Plugins / Mover

- module root: `Plugins/Experimental/Mover/Source/Mover`
- headers: 80; symbols: 2854
- symbol kinds: class=68, delegate=17, enum=55, enumerator=103, externvar=23, function=365, macro=70, member=829, namespace=18, prototype=1147, struct=155, typedef=4
- PrivateDependencyModuleNames: Chaos, CoreUObject, DeveloperSettings, Engine, PhysicsCore, PoseSearch
- PublicDependencyModuleNames: AnimGraphRuntime, Core, GameplayTags, InputCore, MotionWarping, MoverCVDData, NavigationSystem, NetCore, NetworkPrediction, Water

### `Plugins/Experimental/Mover/Source/Mover/Private/Debug/GameplayDebuggerCategory_Mover.h` (Private)


#### class `FGameplayDebuggerCategory_Mover`  
`class FGameplayDebuggerCategory_Mover : public FGameplayDebuggerCategory`  
_L11-53_
- inherits: `FGameplayDebuggerCategory`
- desc: System for adding Mover-related debugging info and visualization to the Gameplay Debugger tool
- L14 _public prototype_ `FGameplayDebuggerCategory_Mover();`
- L16 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L17 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L19 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L22 _protected prototype_ `void DrawOverheadInfo(AActor& DebugActor, FGameplayDebuggerCanvasContext& CanvasContext);`
- L23 _protected prototype_ `void DrawInWorldInfo(AActor& DebugActor, FGameplayDebuggerCanvasContext& CanvasContext);`
- L52 _protected member_ `FRepData DataPack;`

#### struct `FGameplayDebuggerCategory_Mover::FRepData`  
`struct FRepData`  
_L26-51_
- L28 _public member_ `FString PawnName;`
- L29 _public member_ `FString LocalRole;`
- L32 _public member_ `FString MovementModeName;` — State
- L33 _public member_ `FString MovementBaseInfo;`
- L34 _public member_ `FVector Velocity;`
- L35 _public member_ `FVector MoveIntent;`
- L36 _public member_ `TArray<FString> ActiveLayeredMoves;`
- L37 _public member_ `TArray<FString> ModeMap;`
- L38 _public member_ `TArray<FString> ActiveTransitions;`
- L39 _public member_ `TArray<FString> ActiveModifiers;`
- L40 _public member_ `TArray<FString> SyncStateDataTypes;`
- L43 _public member_ `int8 MoveInputType;` — Last input
- L44 _public member_ `FVector MoveInput;`
- L45 _public member_ `FVector OrientIntentDir;`
- L46 _public member_ `FString SuggestedModeName;`
- L48 _public function_ `FRepData()`
- L50 _public prototype_ `void Serialize(FArchive& Ar);`

### `Plugins/Experimental/Mover/Source/Mover/Private/DefaultMovementSet/Modes/SimpleSpringState.h` (Private)


#### struct `FSimpleSpringState`  
`struct FSimpleSpringState : public FMoverDataStructBase`  
_L14-28_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Internal state data for the SimpleSpringWalkingMode
- L18 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L19 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L20 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L21 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L22 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L23 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L27 _public member_ `FVector CurrentAccel = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Acceleration of internal spring model

### `Plugins/Experimental/Mover/Source/Mover/Private/DefaultMovementSet/Modes/SmoothWalkingState.h` (Private)


#### struct `FSmoothWalkingState`  
`struct FSmoothWalkingState : public FMoverDataStructBase`  
_L14-44_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Internal state data for the SmoothWalkingMode
- L18 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L19 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L20 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L21 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L22 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L23 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L27 _public member_ `FVector SpringVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Velocity of internal velocity spring
- L31 _public member_ `FVector SpringAcceleration = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Acceleration of internal velocity spring
- L35 _public member_ `FVector IntermediateVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Intermediate velocity which the velocity spring tracks as a target
- L39 _public member_ `FQuat IntermediateFacing = FQuat::Identity;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Intermediate facing direction when using a double spring
- L43 _public member_ `FVector IntermediateAngularVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Mover|Experimental")` — Angular velocity of the intermediate spring when using a double spring

### `Plugins/Experimental/Mover/Source/Mover/Private/MoveLibrary/NavMovementUtils.h` (Private)


#### class `NavMovementUtils`  
`class NavMovementUtils`  
_L11-16_
- L15 _public prototype_ `static bool CalculateNavMeshNormal(const FNavLocation& Location, FVector& OutNormal, const INavigationDataInterface* NavData, UObject* LogOwner = nullptr);`

### `Plugins/Experimental/Mover/Source/Mover/Public/Backends/MoverBackendLiaison.h` (Public)


#### class `UMoverBackendLiaisonInterface`  
`class UMoverBackendLiaisonInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: MoverBackendLiaisonInterface: any object or system wanting to be the driver of Mover actors must implement this. The intent is to act as a middleman between the Mover actor and the system that drives it, such as the Network Prediction plugin. In practice, objects implementing this interface should be some kind of UActorComponent. The Mover actor instantiates its backend liaison when initialized, then relies on the liaison to call various functions as the simulation progresses. See @MoverComponent.

#### class `IMoverBackendLiaisonInterface`  
`class IMoverBackendLiaisonInterface`  
_L24-71_
- L29 _public prototype_ `virtual double GetCurrentSimTimeMs() = 0;`
- L30 _public prototype_ `virtual int32 GetCurrentSimFrame() = 0;`
- L33 _public function_ `virtual bool IsAsync() const` — Whether this backend will simulate movement asynchronously
- L35 _public function_ `virtual bool IsFixedDt() const` — Whether the underlying simulation advances time in fixed increments
- L37 _public function_ `virtual bool ShouldResim() const` — During a resim, whether this particular mover should resimulate
- L40 _public function_ `virtual float GetEventSchedulingMinDelaySeconds() const` — How much delay to apply to scheduled events. This is important for networked events, and should be greater than the RTT to ensure the event will be executed on all end points at the same frame.
- L42 _public function_ `virtual FMoverTime GetScheduledNetworkTime(const FMoverTime& Time) const` — Util function that returns a time in the future far enough for all end points to receive a networked message before that time elapses. This is only useful in the context of networked events.
- L49 _public function_ `virtual bool ReadPendingSyncState(OUT FMoverSyncState& OutSyncState)` — Pending State: the simulation state currently being authored
- L50 _public function_ `virtual bool WritePendingSyncState(const FMoverSyncState& SyncStateToWrite)`
- L53 _public function_ `virtual bool ReadPresentationSyncState(OUT FMoverSyncState& OutSyncState)` — Presentation State: the most recent presentation state, possibly the result of interpolation or smoothing. Writing to it does not affect the official simulation record.
- L54 _public function_ `virtual bool WritePresentationSyncState(const FMoverSyncState& SyncStateToWrite)`
- L57 _public function_ `virtual bool ReadPrevPresentationSyncState(OUT FMoverSyncState& OutSyncState)` — Previous Presentation State: the state that our optional smoothing process is moving away from, towards a more recent state. Writing to it does not affect the official simulation record.
- L58 _public function_ `virtual bool WritePrevPresentationSyncState(const FMoverSyncState& SyncStateToWrite)`
- L65 _public function_ `virtual void OnSimulationRollback(const FMoverSyncState& NewSyncState, const FMoverTimeStep& NewBaseTimeStep, const FMoverTimeStep& PreRollbackTimeStep)` — Called on the game thread when a rollback occurs, after simulation state has been restored. NewBaseTimeStep is the frame we are about to re-simulate from. PreRollbackTimeStep is the last forward-simulated frame before the rollback -- together they define the window of time that was invalidated (mirrors the FMover_OnPostSimRollback delegate). NewSyncState is the sync state at NewBaseTimeStep, i.e., the state the simulation has been restored to.
- L68 _public function_ `virtual EDataValidationResult ValidateData(FDataValidationContext& Context, const UMoverComponent& ValidationMoverComp) const`

### `Plugins/Experimental/Mover/Source/Mover/Public/Backends/MoverNetworkPredictionLiaison.h` (Public)


#### class `UMoverNetworkPredictionLiaisonComponent`  
`class UMoverNetworkPredictionLiaisonComponent : public UNetworkPredictionComponent, public IMoverBackendLiaisonInterface`  
_L29-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UNetworkPredictionComponent,IMoverBackendLiaisonInterface`
- desc: MoverNetworkPredictionLiaisonComponent: this component acts as a middleman between an actor's Mover component and the Network Prediction plugin. This class is set on a Mover component as the "back end".
- L36 _public prototype_ `void ProduceInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd);` — Get latest local input prior to simulation step. Called by Network Prediction system on owner's instance (autonomous or authority).
- L39 _public prototype_ `bool ShouldReconcile(const FMoverSyncState* PredictedSyncState, const FMoverSyncState* AuthoritySyncState) const;` — Query whether a rollback / resim should occur based on how different the predicted and authority sync states were. Called by Network Prediction system.
- L42 _public prototype_ `bool ShouldReconcile(const FMoverAuxStateContext* PredictedAuxState, const FMoverAuxStateContext* AuthorityAuxState) const;` — Query whether a rollback / resim should occur based on how different the predicted and authority aux states were. Called by Network Prediction system.
- L45 _public prototype_ `void RestoreFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Restore a previous frame prior to resimulating. Called by Network Prediction system.
- L48 _public prototype_ `void FinalizeFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Take output for simulation. Called by Network Prediction system.
- L51 _public prototype_ `void FinalizeSmoothingFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Take output for smoothing. Called by Network Prediction system.
- L54 _public prototype_ `void InitializeSimulationState(FMoverSyncState* OutSync, FMoverAuxStateContext* OutAux);` — Seed initial values based on component's state. Called by Network Prediction system.
- L57 _public prototype_ `void SimulationTick(const FNetSimTimeStep& TimeStep, const TNetSimInput<KinematicMoverStateTypes>& SimInput, const TNetSimOutput<KinematicMoverStateTypes>& SimOutput);` — Primary movement simulation update. Given an starting state and timestep, produce a new state. Called by Network Prediction system.
- L61 _public prototype_ `virtual double GetCurrentSimTimeMs() override;` — IMoverBackendLiaisonInterface
- L62 _public prototype_ `virtual int32 GetCurrentSimFrame() override;`
- L63 _public prototype_ `virtual bool ReadPendingSyncState(OUT FMoverSyncState& OutSyncState) override;`
- L64 _public prototype_ `virtual bool WritePendingSyncState(const FMoverSyncState& SyncStateToWrite) override;`
- L65 _public prototype_ `virtual bool ReadPresentationSyncState(OUT FMoverSyncState& OutSyncState) override;`
- L66 _public prototype_ `virtual bool WritePresentationSyncState(const FMoverSyncState& SyncStateToWrite) override;`
- L67 _public prototype_ `virtual bool ReadPrevPresentationSyncState(FMoverSyncState& OutSyncState) override;`
- L68 _public prototype_ `virtual bool WritePrevPresentationSyncState(const FMoverSyncState& SyncStateToWrite) override;`
- L70 _public prototype_ `virtual EDataValidationResult ValidateData(FDataValidationContext& Context, const UMoverComponent& ValidationMoverComp) const override;`
- L74 _public prototype_ `virtual void BeginPlay() override;`
- L75 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason) override;`
- L78 _public prototype_ `void InitializeComponent() override;` — UObject interface
- L79 _public prototype_ `void UninitializeComponent() override;`
- L80 _public prototype_ `void OnRegister() override;`
- L81 _public prototype_ `void RegisterComponentTickFunctions(bool bRegister) override;`
- L85 _public prototype_ `virtual void InitializeNetworkPredictionProxy() override;` — UNetworkPredictionComponent interface
- L90 _public prototype_ `UMoverNetworkPredictionLiaisonComponent();`
- L96 _protected prototype_ `void ResetSimulation();`
- L97 _protected prototype_ `void SetupSimulation();`
- L99 _protected member_ `TObjectPtr<UMoverComponent> MoverComp;` — the component that we're in charge of driving
- L100 _protected member_ `FMoverSyncState* StartingOutSync;`
- L101 _protected member_ `FMoverAuxStateContext* StartingOutAux;`
- L104 _protected member_ `TSubclassOf<UKinematicActorSimulation> SimulationClass;` — Type of simulation to instantiate as the system spins up
- L107 _protected member_ `TObjectPtr<UKinematicActorSimulation> Simulation;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVER_API`
- L22 _typedef_ `using KinematicMoverStateTypes = TNetworkPredictionStateTypes<FMoverInputCmdContext, FMoverSyncState, FMoverAuxStateContext>;`

### `Plugins/Experimental/Mover/Source/Mover/Public/Backends/MoverStandaloneLiaison.h` (Public)


#### struct `FMoverStandaloneProduceInputTickFunction`  
`struct FMoverStandaloneProduceInputTickFunction : public FTickFunction`  
_L23-33_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: Tick task for producing input before the next movement simulation step
- L28 _public member_ `TWeakObjectPtr<UMoverStandaloneLiaisonComponent> Target;` — Standalone liaison that is the target of this tick
- L30 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L31 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L32 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverStandaloneProduceInputTickFunction> : public TStructOpsTypeTraitsBase2<FMoverStandaloneProduceInputTickFunction>`  
_L36-42_
- inherits: `TStructOpsTypeTraitsBase2<FMoverStandaloneProduceInputTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L39-41_

#### struct `FMoverStandaloneSimulateMovementTickFunction`  
`struct FMoverStandaloneSimulateMovementTickFunction : public FTickFunction`  
_L47-57_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: Tick task for advancing the movement simulation step, after input has been produced
- L52 _public member_ `TWeakObjectPtr<UMoverStandaloneLiaisonComponent> Target;` — Standalone liaison that is the target of this tick
- L54 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L55 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L56 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverStandaloneSimulateMovementTickFunction> : public TStructOpsTypeTraitsBase2<FMoverStandaloneSimulateMovementTickFunction>`  
_L60-66_
- inherits: `TStructOpsTypeTraitsBase2<FMoverStandaloneSimulateMovementTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L63-65_

#### struct `FMoverStandaloneApplyStateTickFunction`  
`struct FMoverStandaloneApplyStateTickFunction : public FTickFunction`  
_L71-81_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: Tick task for applying the new simulation state to the actor/components, after movement has been simulated
- L76 _public member_ `TWeakObjectPtr<UMoverStandaloneLiaisonComponent> Target;` — Standalone liaison that is the target of this tick
- L78 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;`
- L79 _public prototype_ `virtual FString DiagnosticMessage() override;`
- L80 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverStandaloneApplyStateTickFunction> : public TStructOpsTypeTraitsBase2<FMoverStandaloneApplyStateTickFunction>`  
_L84-90_
- inherits: `TStructOpsTypeTraitsBase2<FMoverStandaloneApplyStateTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L87-89_

#### class `UMoverStandaloneLiaisonComponent`  
`class UMoverStandaloneLiaisonComponent : public UActorComponent, public IMoverBackendLiaisonInterface`  
_L100-214_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UActorComponent,IMoverBackendLiaisonInterface`
- desc: MoverStandaloneLiaison: this component acts as a backend driver for an actor's Mover component, for use in Standalone (non-networked) games. This class is set on a Mover component as the "back end".
- L105 _public prototype_ `UMoverStandaloneLiaisonComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L108 _public prototype_ `virtual double GetCurrentSimTimeMs() override;` — IMoverBackendLiaisonInterface
- L109 _public prototype_ `virtual int32 GetCurrentSimFrame() override;`
- L110 _public prototype_ `virtual bool ReadPendingSyncState(OUT FMoverSyncState& OutSyncState) override;`
- L111 _public prototype_ `virtual bool WritePendingSyncState(const FMoverSyncState& SyncStateToWrite) override;`
- L115 _public prototype_ `virtual void RegisterComponentTickFunctions(bool bRegister) override;`
- L116 _public prototype_ `virtual void InitializeComponent() override;`
- L117 _public prototype_ `virtual void UninitializeComponent() override;`
- L118 _public prototype_ `virtual void BeginPlay() override;`
- L119 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason) override;`
- L122 _public prototype_ `FTickFunction* FindTickFunction(EMoverTickPhase MoverTickPhase);`
- L131 _public prototype_ `void AddTickDependency(UActorComponent* OtherComponent, EMoverTickDependencyOrder TickOrder, EMoverTickPhase TickPhase);` — `UFUNCTION(BlueprintCallable, Category = "Ticking", meta = (Keywords = "Tick Dependency"))` — Adds a tick dependency between another component and one of mover's tick functions. @param OtherComponent		The component to add a dependency with. @param TickOrder				What order OtherComponent's should have relative to TickPhase i.e. OtherComponent Before SimulateMovement. @param TickPhase				The mover tick phase we want to a dependency with.
- L135 _public prototype_ `void SetUseAsyncProduceInput(bool bUseAsyncInputProduction);` — `UFUNCTION(BlueprintCallable, Category = "Ticking")` — Sets whether this instance's produce input can run on worker threads or not. See @bUseAsyncProduceInput and @SetEnableProduceInput
- L138 _public prototype_ `bool GetUseAsyncProduceInput() const;` — `UFUNCTION(BlueprintCallable, Category = "Ticking")`
- L142 _public prototype_ `void SetEnableProduceInput(bool bEnableInputProduction);` — `UFUNCTION(BlueprintCallable, Category = "Ticking")` — Sets whether this instance's produce-input tick will run at all. It may be useful to disable on actors that don't rely on Mover input to move.
- L146 _public prototype_ `bool GetEnableProduceInput() const;` — `UFUNCTION(BlueprintCallable, Category = "Ticking")` — Whether this instance will have its produce-input tick called.
- L150 _public prototype_ `void SetUseAsyncMovementSimulationTick(bool bUseAsyncMovementSim);` — `UFUNCTION(BlueprintCallable, Category = "Ticking")` — Sets whether this instance's movement simulation tick can run on worker threads or not. See @bUseAsyncMovementSimulationTick
- L153 _public prototype_ `bool GetUseAsyncMovementSimulationTick() const;` — `UFUNCTION(BlueprintCallable, Category = "Ticking")`
- L156 _protected prototype_ `void TickInputProduction(float DeltaSeconds);`
- L157 _protected prototype_ `void TickMovementSimulation(float DeltaSeconds);`
- L158 _protected prototype_ `void TickApplySimulationState(float DeltaSeconds);`
- L160 _protected prototype_ `void UpdateSimulationTime();`
- L164 _protected prototype_ `virtual void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);` — `UFUNCTION()` — Called when controller changes, used to manage ticking dependencies
- L172 _protected member_ `bool bUseAsyncProduceInput = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Async Movement")` — Sets whether produce input can run on worker threads or not, also gated by global option. Changes at runtime will take affect next frame. Has no effect on simulation ticking or applying results.
- L179 _protected member_ `bool bUseAsyncMovementSimulationTick = false;` — `UPROPERTY(EditDefaultsOnly, Category = "Async Movement")` — Sets whether the movement simulation tick can run on worker threads or not, also gated by global option. Changes at runtime will take affect next frame. Has no effect on input production or applying results.
- L182 _protected member_ `TSubclassOf<UKinematicActorSimulation> SimulationClass;` — Type of simulation to instantiate as the system spins up
- L185 _protected member_ `TObjectPtr<UKinematicActorSimulation> Simulation;` — `UPROPERTY(Transient)`
- L187 _protected member_ `TObjectPtr<UMoverComponent> MoverComp;` — the component that we're in charge of driving
- L189 _protected member_ `double CurrentSimTimeMs;`
- L190 _protected member_ `int32 CurrentSimFrame;`
- L192 _protected member_ `FMoverInputCmdContext LastProducedInputCmd;`
- L194 _protected member_ `FMoverSyncState CachedLastSyncState;`
- L195 _protected member_ `FMoverAuxStateContext CachedLastAuxState;`
- L196 _protected member_ `bool bIsCachedStateDirty = false;` — If true, we need to propagate the state to our MoverComponent during ApplyState
- L198 _protected member_ `FRWLock StateDataLock;` — used when reading/writing to our cached state (sync/aux) data
- L200 _protected member_ `bool bIsInApplySimulationState = false;` — transient flag indicating ApplySimulationState is active
- L202 _protected member_ `FMoverStandaloneProduceInputTickFunction ProduceInputTickFunction;`
- L203 _protected member_ `FMoverStandaloneSimulateMovementTickFunction SimulateMovementTickFunction;`
- L204 _protected member_ `FMoverStandaloneApplyStateTickFunction ApplyStateTickFunction;`
- L209 _private member_ `FMoverTickStartData WorkingStartData;` — Internal-use-only tick data structs, for efficiency since they typically have the same contents from frame to frame
- L210 _private member_ `FMoverTickEndData WorkingEndData;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L40 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon53d615630103`)
- L64 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon53d615630203`)
- L88 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon53d615630303`)

### `Plugins/Experimental/Mover/Source/Mover/Public/BlueprintDataExt.h` (Public)


#### struct `FMoverDictionaryData`  
`struct FMoverDictionaryData : public FMoverDataStructBase`  
_L18-59_
- reflection: `USTRUCT(BlueprintType, Experimental)`
- inherits: `FMoverDataStructBase`
- desc: Data block containing mappings between names and commonly-used types, so that Blueprint-only devs can include custom data in their project's sync state or input cmds without needing native code changes. EXPERIMENTAL: this will be removed in favor of generic user-defined struct support. If this is for Blueprint usage, consider using FMoverUserDefinedDataStruct instead. If native, consider deriving your own FMoverDataStructBase type.
- L25 _public member_ `TMap<FName, bool> BoolValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L28 _public member_ `TMap<FName, int32> IntValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L31 _public member_ `TMap<FName, double> FloatValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L34 _public member_ `TMap<FName, FVector> VectorValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L37 _public member_ `TMap<FName, FRotator> RotatorValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L40 _public member_ `TMap<FName, FName> NameValues;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L43 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L48 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L53 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L54 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L55 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Alpha) override;`
- L56 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L57 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/ChaosVisualDebugger/MoverCVDRuntimeTrace.h` (Public)


#### class `UE::MoverUtils::FMoverCVDRuntimeTrace`  
`class FMoverCVDRuntimeTrace`  
_L26-37_
- desc: Utility functions used to trace Mover data into the Chaos Visual Debugger
- L29 _public prototype_ `static void TraceMoverData(UMoverComponent* MoverComponent, const FMoverInputCmdContext* InputCmd, const FMoverSyncState* SyncState, const NamedDataCollections* LocalSimDataCollections = nullptr);`
- L30 _public prototype_ `static void TraceMoverData(uint32 SolverID, uint32 ParticleID, const FMoverInputCmdContext* InputCmd, const FMoverSyncState* SyncState, const NamedDataCollections* LocalSimDataCollections = nullptr);`
- L32 _public prototype_ `static void UnwrapSimData(const FMoverCVDSimDataWrapper& InSimDataWrapper, TSharedPtr<FMoverInputCmdContext>& OutInputCmd, TSharedPtr<FMoverSyncState>& OutSyncState, TArray<TPair<FName, TSharedPtr<FMoverDataCollection>>>& OutLocalSimDataSections);`
- L33 _public prototype_ `static void WrapSimData(uint32 SolverID, uint32 ParticleID, const FMoverInputCmdContext& InInputCmd, const FMoverSyncState& InSyncState, const NamedDataCollections* LocalSimDataCollections, FMoverCVDSimDataWrapper& OutSimDataWrapper);`
- L36 _private prototype_ `static void TraceMoverDataPrivate(uint32 SolverID, uint32 ParticleID, const FMoverInputCmdContext* InputCmd, const FMoverSyncState* SyncState, const NamedDataCollections* LocalSimDataCollections = nullptr);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace MoverUtils` (scope `UE`)
- L21 _typedef_ `typedef TArray<TPair<FName, const FMoverDataCollection*>> NamedDataCollections;` (scope `UE::MoverUtils`)

### `Plugins/Experimental/Mover/Source/Mover/Public/Debug/MoverDebugComponent.h` (Public)


#### class `UMoverDebugComponent`  
`class UMoverDebugComponent : public UActorComponent`  
_L21-134_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Component to help display debug information for actors using the Mover Component. Is expected to be attached to the actor that has the mover component. Currently supports trajectory functionality and trailing functionality. Is also used in the gameplay debugger under the mover category.
- L27 _public prototype_ `UMoverDebugComponent();`
- L29 _public prototype_ `virtual void InitializeComponent() override;`
- L31 _public prototype_ `virtual void BeginPlay() override;`
- L32 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L34 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L40 _public member_ `float LookaheadSeconds = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverDebug)` — Number of seconds to lookahead and show the current trajectory
- L44 _public member_ `int32 LookaheadSamplesPerSecond = 20;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverDebug)` — Number of times trajectory will be sampled each second
- L50 _public member_ `bool bShowTrajectory = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverDebug)` — Whether this component should show the trajectory of the movement component of the Actor it's attached too
- L54 _public member_ `bool bShowTrail = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverDebug)` — Whether this component should show the trail of the movement component of the Actor it's attached too
- L58 _public member_ `bool bShowCorrections = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MoverDebug)` — Whether this component should show the corrections and rollbacks applied to the Actor it's attached too
- L61 _public prototype_ `void DrawCorrections();` — Draw network corrections. Uses
- L64 _public prototype_ `void DrawTrail();` — Draw the trail behind the actor
- L67 _public prototype_ `void DrawTrajectory();` — Draw the current trajectory of the actor
- L73 _public prototype_ `void SetHistoryTracking(float SecondsToTrack, float SamplesPerSecond);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Change history tracking feature settings. Anything <= 0 for SecondsToTrack will disable the feature.
- L77 _public prototype_ `TArray<FTrajectorySampleInfo> GetPastTrajectory() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category=Mover)` — Get a read-only sampling of where the actor has recently been, ordered by ascending age. Will be empty unless history tracking is enabled. @see SetHistoryTracking
- L85 _protected member_ `float HistoryTrackingSeconds = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mover)` — Max age of tracked samples. Feature is disabled for values <= 0. @see SetHistoryTracking
- L89 _protected member_ `int32 HistorySamplesPerSecond = 15;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mover)` — Target sampling rate for history tracking. Note that sampling rate is variable and may be higher during times of rapid change. @see SetHistoryTracking
- L91 _protected prototype_ `void InitHistoryTracking();`
- L92 _protected prototype_ `void UpdateHistoryTrackingForFrame(const FMoverTimeStep& TimeStep, const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);`
- L95 _protected prototype_ `void OnHistoryTrackingRollback(const FMoverTimeStep& NewTimeStep, const FMoverTimeStep& InvalidatedTimeStep);` — `UFUNCTION()`
- L97 _protected member_ `bool bIsTrackingHistory = false;` — Master flag for whether trajectory history is being tracked
- L98 _protected member_ `TRingBuffer<FTrajectorySampleInfo> HistorySamples;` — Running buffer of most recent trajectory
- L104 _private prototype_ `void OnMovementSimTick(const FMoverTimeStep& TimeStep);` — `UFUNCTION()`
- L107 _private prototype_ `void OnMovementSimRollback(const FMoverTimeStep& NewTimeStep, const FMoverTimeStep& InvalidatedTimeStep);` — `UFUNCTION()`
- L117 _private member_ `TUniquePtr<TCircularBuffer<FTrailSample>> SimulatedSamples;`
- L118 _private member_ `TUniquePtr<TCircularBuffer<FTrailSample>> RolledBackSamples;`
- L120 _private member_ `int32 NumSimulatedSamplesToBuffer = 300;`
- L121 _private member_ `int32 NumRolledBackSamplesToBuffer = 100;`
- L123 _private member_ `float OldestSampleToRenderByGameSecs = 2.f;`
- L125 _private member_ `int32 FrameOfLastSample = -1;`
- L126 _private member_ `int32 HighestRolledBackFrame = -1;`
- L127 _private member_ `bool bHasValidRollbackSamples = false;`
- L131 _private member_ `TArray<FVector> ClientLocations;`
- L132 _private member_ `TArray<FVector> CorrectedLocations;`

#### struct `UMoverDebugComponent::FTrailSample`  
`struct FTrailSample`  
_L109-115_
- L111 _public member_ `FVector Location = FVector::ZeroVector;`
- L112 _public member_ `int32 SimTimeMS = -1;`
- L113 _public member_ `int32 SimFrame = -1;`
- L114 _public member_ `float GameTimeSecs = -1.f;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/CharacterMoverComponent.h` (Public)


#### class `UCharacterMoverComponent`  
`class UCharacterMoverComponent : public UMoverComponent`  
_L27-138_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UMoverComponent`
- desc: Character Mover Component: this is a specialization of the core Mover Component that is set up with a classic character in mind. Defaults and extended functionality, such as jumping and simple montage replication, are intended to support features similar to UE's ACharacter actor type.
- L32 _public prototype_ `UCharacterMoverComponent();`
- L34 _public prototype_ `virtual void BeginPlay() override;`
- L39 _public prototype_ `bool GetHandleJump() const;` — `UFUNCTION(BlueprintGetter)` — Returns whether this component is tasked with handling jump input or not
- L43 _public prototype_ `void SetHandleJump(bool bInHandleJump);` — `UFUNCTION(BlueprintSetter)` — If true, this component will handle default character inputs for jumping
- L47 _public prototype_ `bool GetHandleStanceChanges() const;` — `UFUNCTION(BlueprintGetter)` — Returns whether this component is tasked with handling character stance changes, including crouching
- L51 _public prototype_ `void SetHandleStanceChanges(bool bInHandleStanceChanges);` — `UFUNCTION(BlueprintSetter)` — If true, this component will process stancing changes and crouching inputs
- L55 _public prototype_ `virtual bool IsCrouching() const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns true if currently crouching
- L59 _public prototype_ `virtual bool IsFlying() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Returns true if currently flying (moving through a non-fluid volume without resting on the ground)
- L63 _public prototype_ `virtual bool IsFalling() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Is this actor in a falling state? Note that this includes upwards motion induced by jumping.
- L67 _public prototype_ `virtual bool IsAirborne() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Is this actor in a airborne state? (e.g. Flying, Falling)
- L71 _public prototype_ `virtual bool IsOnGround() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Is this actor in a grounded state? (e.g. Walking)
- L75 _public prototype_ `virtual bool IsSwimming() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Is this actor in a Swimming state? (e.g. Swimming)
- L79 _public prototype_ `virtual bool IsSlopeSliding() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Is this actor sliding on an unwalkable slope
- L83 _public prototype_ `virtual bool CanActorJump() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Can this Actor jump?
- L87 _public prototype_ `virtual bool Jump();` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Perform jump on actor
- L91 _public prototype_ `virtual bool CanCrouch();` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Whether this actor can currently crouch or not
- L95 _public prototype_ `virtual void Crouch();` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Perform crouch on actor
- L99 _public prototype_ `virtual void UnCrouch();` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Perform uncrouch on actor
- L103 _public function_ `bool GetCrouchIntent() const` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Get Crouch Intent
- L107 _public member_ `FMover_OnStanceChanged OnStanceChanged;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when this actor changes stances.
- L111 _protected prototype_ `virtual void OnMoverPreSimulationTick(const FMoverTimeStep& TimeStep, const FMoverInputCmdContext& InputCmd);` — `UFUNCTION()`
- L114 _protected prototype_ `virtual void OnMoverPostFinalize(const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — `UFUNCTION()`
- L116 _protected prototype_ `virtual void OnHandlerSettingChanged();`
- L118 _protected prototype_ `virtual void UpdateSyncedMontageState(const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);`
- L121 _protected member_ `FMovementModifierHandle StanceModifierHandle;` — ID used to keep track of the modifier responsible for crouching
- L125 _protected member_ `uint8 bWantsToCrouch : 1 = 0;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Mover|Crouch")` — If true, try to crouch (or keep crouching) on next update. If false, try to stop crouching on next update.
- L129 _protected member_ `uint8 bHandleJump : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetHandleJump, BlueprintSetter = SetHandleJump, Category = "Mover|Character")` — Whether this component should directly handle jumping or not
- L133 _protected member_ `uint8 bHandleStanceChanges : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetHandleStanceChanges, BlueprintSetter = SetHandleStanceChanges, Category = "Mover|Character")` — Whether this component should directly handle stance changes, including crouching input
- L137 _protected member_ `FMoverAnimMontageState SyncedMontageState;` — `UPROPERTY(Transient)` — Current state of replicated montage playback from an active movement mechanism (layered move, etc.)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnStanceChanged, EStanceMode, OldStance, EStanceMode, NewStance);` — Fires when a stance is changed, if stance handling is enabled (see @SetHandleStanceChanges) Note: If a stance was just Activated it will fire with an invalid OldStance If a stance was just Deactivated it will fire with an invalid NewStance
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnStanceChanged, EStanceMode, OldStance, EStanceMode, NewStance);` — Fires when a stance is changed, if stance handling is enabled (see @SetHandleStanceChanges) Note: If a stance was just Activated it will fire with an invalid OldStance If a stance was just Deactivated it will fire with an invalid NewStance

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/CharacterMoverSimulationTypes.h` (Public)


#### struct `FLandedEventData`  
`struct FLandedEventData : public FMoverSimulationEventData`  
_L11-30_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L15 _public function_ `FLandedEventData(const FMoverTimeStep& InEventTime, const FHitResult& InHitResult, const FName InNewModeName) : FMoverSimulationEventData(InEventTime) , HitResult(InHitResult) , NewModeName(InNewModeName)`
- L21 _public function_ `FLandedEventData()`
- L23 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L28 _public member_ `FHitResult HitResult;`
- L29 _public member_ `FName NewModeName = NAME_None;`

#### struct `FJumpedEventData`  
`struct FJumpedEventData : public FMoverSimulationEventData`  
_L33-50_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L37 _public function_ `FJumpedEventData(const FMoverTimeStep& InEventTime, float InJumpStartHeight) : FMoverSimulationEventData(InEventTime) , JumpStartHeight(InJumpStartHeight)`
- L42 _public function_ `FJumpedEventData()`
- L44 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L49 _public member_ `float JumpStartHeight = 0.0f;`

#### struct `FFloorResultData`  
`struct FFloorResultData : public FMoverDataStructBase`  
_L53-80_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- L59 _public member_ `FFloorCheckResult FloorResult;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L61 _public prototype_ `FFloorResultData() = default;`
- L62 _public prototype_ `virtual ~FFloorResultData() = default;`
- L64 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L69 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L74 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L75 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L76 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L77 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L78 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L79 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FFloorResultData > : public TStructOpsTypeTraitsBase2< FFloorResultData >`  
_L83-89_
- inherits: `TStructOpsTypeTraitsBase2<FFloorResultData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L86-88_

#### Free symbols / members of external scopes

- L87 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonf057e5d30103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/InstantMovementEffects/BasicInstantMovementEffects.h` (Public)


#### struct `FTeleportEffect`  
`struct FTeleportEffect : public FInstantMovementEffect`  
_L15-46_
- reflection: `USTRUCT(BlueprintType, Category = "Mover|Instant Movement Effect", DisplayName = "Teleport Instant Movement Effect")`
- inherits: `FInstantMovementEffect`
- desc: Teleport: instantly moves an actor to a new location and rotation For async-compatible teleportation, use AsyncTeleportEffect instead.
- L19 _public prototype_ `FTeleportEffect();`
- L20 _public prototype_ `virtual ~FTeleportEffect() = default;`
- L24 _public member_ `FVector TargetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Location to teleport to, in world space
- L28 _public member_ `bool bUseActorRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Whether this teleport effect should keep the actor's current rotation or use a specified one (TargetRotation)
- L32 _public member_ `FRotator TargetRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(EditCondition="bUseActorRotation==false", EditConditionHides))` — Actor rotation is set to this value on teleport if bUseActorRotation is false
- L34 _public prototype_ `virtual bool ApplyMovementEffect(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L35 _public prototype_ `virtual bool ApplyMovementEffect_Async(FApplyMovementEffectParams_Async& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L37 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L39 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L41 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L43 _public prototype_ `virtual FString ToSimpleString() const override;`
- L45 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `FAsyncTeleportEffect`  
`struct FAsyncTeleportEffect : public FTeleportEffect`  
_L50-61_
- reflection: `USTRUCT(BlueprintType, Category = "Mover|Instant Movement Effect", DisplayName = "Async Teleport Instant Movement Effect")`
- inherits: `FTeleportEffect`
- desc: Async Teleport: instantly moves an actor to a new location and rotation (compatible with async movement simulation)
- L54 _public prototype_ `virtual bool ApplyMovementEffect(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L56 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L58 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L60 _public prototype_ `virtual FString ToSimpleString() const override;`

#### struct `FJumpImpulseEffect`  
`struct FJumpImpulseEffect : public FInstantMovementEffect`  
_L67-90_
- reflection: `USTRUCT(BlueprintType, Category = "Mover|Instant Movement Effect", DisplayName = "Jump Impulse Instant Movement Effect")`
- inherits: `FInstantMovementEffect`
- desc: Jump Impulse: introduces an instantaneous upwards change in velocity. This overrides the existing 'up' component of the actor's current velocity Note: this only applies the impulse for one tick!
- L71 _public prototype_ `FJumpImpulseEffect();`
- L73 _public prototype_ `virtual ~FJumpImpulseEffect() = default;`
- L77 _public member_ `float UpwardsSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Units per second, in whatever direction the target actor considers 'up'
- L79 _public prototype_ `virtual bool ApplyMovementEffect(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L81 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L83 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L85 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L87 _public prototype_ `virtual FString ToSimpleString() const override;`
- L89 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `FApplyVelocityEffect`  
`struct FApplyVelocityEffect : public FInstantMovementEffect`  
_L96-126_
- reflection: `USTRUCT(BlueprintType, Category = "Mover|Instant Movement Effect", DisplayName = "Apply Velocity Instant Movement Effect")`
- inherits: `FInstantMovementEffect`
- desc: Apply Velocity: provides an impulse velocity to the actor after (optionally) forcing them into a particular movement mode Note: this only applies the impulse for one tick!
- L100 _public prototype_ `FApplyVelocityEffect();`
- L101 _public prototype_ `virtual ~FApplyVelocityEffect() = default;`
- L105 _public member_ `FVector VelocityToApply;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the actor.
- L109 _public member_ `bool bAdditiveVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true VelocityToApply will be added to current velocity on this actor. If false velocity will be set directly to VelocityToApply
- L113 _public member_ `FName ForceMovementMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.
- L115 _public prototype_ `virtual bool ApplyMovementEffect(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState) override;`
- L117 _public prototype_ `virtual FInstantMovementEffect* Clone() const override;`
- L119 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L121 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L123 _public prototype_ `virtual FString ToSimpleString() const override;`
- L125 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/AnimRootMotionLayeredMove.h` (Public)


#### struct `FLayeredMove_AnimRootMotion`  
`struct FLayeredMove_AnimRootMotion : public FLayeredMove_MontageStateProvider`  
_L32-59_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMove_MontageStateProvider`
- desc: Anim Root Motion Move: handles root motion from a montage played on the primary visual component (skeletal mesh). In this method, root motion is extracted independently from anim playback. The move will end itself if the animation is interrupted on the mesh. This variant runs on the game thread only. Use FLayeredMove_AnimRootMotion_SimDriven for simulation-driven (worker thread) root motion with motion warping support.
- L36 _public prototype_ `FLayeredMove_AnimRootMotion();`
- L37 _public prototype_ `virtual ~FLayeredMove_AnimRootMotion() = default;`
- L40 _public member_ `FMoverAnimMontageState MontageState;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L43 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L45 _public prototype_ `bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const override;`
- L47 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L49 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L51 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L53 _public prototype_ `virtual FString ToSimpleString() const override;`
- L55 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L58 _public prototype_ `virtual FMoverAnimMontageState GetMontageState() const override;` — FLayeredMove_MontageStateProvider

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_AnimRootMotion > : public TStructOpsTypeTraitsBase2< FLayeredMove_AnimRootMotion >`  
_L62-68_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_AnimRootMotion>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L65-67_

#### struct `FLayeredMove_AnimRootMotion_SimDriven`  
`struct FLayeredMove_AnimRootMotion_SimDriven : public FLayeredMove_AnimRootMotion`  
_L79-125_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMove_AnimRootMotion`
- desc: Async-capable variant of FLayeredMove_AnimRootMotion. Runs GenerateMove_Async on the simulation worker thread, computing root motion from montage data without touching game-thread objects. Supports motion warping via warp targets snapshotted to the blackboard each frame. Use this variant when the Mover component is running in async physics mode and you need the simulation to be authoritative over root motion position and blend-out timing.
- L83 _public prototype_ `virtual ~FLayeredMove_AnimRootMotion_SimDriven() = default;`
- L89 _public member_ `FMoverTime StartMoverTime;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category = Mover)` — Simulation time snapshot taken when this move starts on a worker thread. FrameCount is valid only when started from a fixed-timestep step (ServerFrame != INDEX_NONE); otherwise it remains INDEX_NONE and ElapsedSecondsTo falls back to ms arithmetic automatically.
- L94 _public member_ `bool bShouldBlendOut = false;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category = Mover)` — Set true in async the first time blend-out is triggered. Sticky: never cleared once set. Read on the game thread to call Montage_Stop exactly once.
- L99 _public member_ `bool bIsFinished = false;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category = Mover)` — Set true in async when the montage position has reached the end of a non-looping montage. Read on the game thread to finalize the montage instance cleanly.
- L103 _public member_ `int32 BlendOutServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category = Mover)` — Server frame at the end of the substep when blend-out was first triggered. INDEX_NONE if not yet.
- L107 _public member_ `int32 FinishServerFrame = INDEX_NONE;` — `UPROPERTY(VisibleInstanceOnly, Transient, Category = Mover)` — Server frame at the end of the substep when the montage was first detected as finished. INDEX_NONE if not yet.
- L109 _public function_ `virtual bool SupportsAsync() const override`
- L111 _public prototype_ `virtual void OnStart_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime) override;`
- L113 _public prototype_ `virtual bool GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;`
- L115 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L117 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L119 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L121 _public prototype_ `virtual FString ToSimpleString() const override;`
- L124 _public prototype_ `virtual void AppendMontageOutputEntry(TArray<FMoverSimDrivenMontageEntry>& OutEntries, const FMoverTimeStep& TimeStep) const override;` — FLayeredMove_MontageStateProvider

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_AnimRootMotion_SimDriven > : public TStructOpsTypeTraitsBase2< FLayeredMove_AnimRootMotion_SimDriven >`  
_L128-134_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_AnimRootMotion_SimDriven>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L131-133_

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVER_API`
- L18 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_AnimRootMotion_Montage);`
- L21 _externvar_ `extern FAutoConsoleVariable CVarLogAnimRootMotionSteps;`
- L66 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anond35e773e0103`)
- L132 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anond35e773e0203`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/AnimRootMotionWarpingTypes.h` (Public)


#### struct `FMoverResolvedWarpTarget`  
`struct FMoverResolvedWarpTarget`  
_L28-40_
- reflection: `USTRUCT()`
- desc: A GT-resolved motion warp target, safe to read on a worker thread. Populated from UMotionWarpingComponent::WarpTargets each frame by the ChaosMover backend.
- L33 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L36 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L39 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`

#### struct `FMoverMotionWarpingInputs`  
`struct FMoverMotionWarpingInputs : public FMoverDataStructBase`  
_L46-59_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Replicated motion warp targets, populated from UMotionWarpingComponent on the locally-controlled machine and forwarded to all participants via the input command collection so every endpoint uses consistent targets during root motion warping on the worker thread.
- L51 _public member_ `TArray<FMoverResolvedWarpTarget> WarpTargets;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L53 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L54 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L55 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L56 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L57 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L58 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace AnimRootMotionBlackboard`
- L16 _externvar_ `extern const FName LastPrimaryVisualComponentRelativeTransform;` (scope `AnimRootMotionBlackboard`) — Relative transform of the primary visual component with respect to the actor root. Written each substep so async layered moves can convert mesh-local root motion into world space without touching game-thread-only objects.
- L22 _externvar_ `extern const FName LastResolvedMotionWarpTargets;` (scope `AnimRootMotionBlackboard`) — GT-resolved motion warp targets snapshotted from UMotionWarpingComponent each frame. Written each substep so GenerateMove_Async can apply skew-warp math without accessing game-thread-only UObjects. Value type: TArray<FMoverResolvedWarpTarget>

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/BasicLayeredMoves.h` (Public)


#### enum `ELayeredMove_ConstantVelocitySettingsFlags`  
`enum class ELayeredMove_ConstantVelocitySettingsFlags : uint8`  
_L16-25_
- reflection: `UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))`
- L18 _public enumerator_ `NoFlags = 0`
- L21 _public enumerator_ `VelocityStartRelative = (1 << 0)` — Velocity direction is determined when this move starts, relative to the target actor. This flag is incompatible with other Velocity**** flags
- L23 _public enumerator_ `VelocityAlwaysRelative = (1 << 1)` — Velocity direction is always relative to the target actor, even if its orientation changes. This flag is incompatible with other Velocity**** flags

#### struct `FLayeredMove_LinearVelocity`  
`struct FLayeredMove_LinearVelocity : public FLayeredMoveBase`  
_L29-66_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Linear Velocity: A method of inducing a straight-line velocity on an actor over time
- L33 _public prototype_ `FLayeredMove_LinearVelocity();`
- L35 _public prototype_ `virtual ~FLayeredMove_LinearVelocity() = default;`
- L39 _public member_ `FVector Velocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Units per second, could be worldspace vs relative depending on Flags
- L44 _public member_ `TObjectPtr<UCurveFloat> MagnitudeOverTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional curve float for controlling the magnitude of the velocity applied to the actor over the duration of the move Warning: This should not be set in async mode as it is not thread safe
- L48 _public member_ `uint8 SettingsFlags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(Bitmask, BitmaskEnum="/Script/Mover.ELayeredMove_ConstantVelocitySettingsFlags"))` — @see ELayeredMove_ConstantVelocitySettingsFlags
- L50 _public function_ `virtual bool SupportsAsync() const override`
- L53 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L55 _public prototype_ `virtual bool GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Async safe version of movement generation (does not use MagnitudeOverTime)
- L57 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L59 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L61 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L63 _public prototype_ `virtual FString ToSimpleString() const override;`
- L65 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_LinearVelocity > : public TStructOpsTypeTraitsBase2< FLayeredMove_LinearVelocity >`  
_L69-76_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_LinearVelocity>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-75_

#### struct `FLinearVelocityMoveActivationParams`  
`struct FLinearVelocityMoveActivationParams : public FLayeredMoveActivationParams`  
_L80-91_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FLayeredMoveActivationParams`
- L86 _public member_ `FVector Velocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Units per second, world-space or relative to the actor depending on SettingsFlags.
- L90 _public member_ `uint8 SettingsFlags = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(Bitmask, BitmaskEnum="/Script/Mover.ELayeredMove_ConstantVelocitySettingsFlags"))` — @see ELayeredMove_ConstantVelocitySettingsFlags

#### struct `FLinearVelocityMoveData`  
`struct FLinearVelocityMoveData : public FLayeredMoveInstancedData`  
_L94-111_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FLayeredMoveInstancedData`
- L98 _public function_ `virtual FLayeredMoveInstancedData* Clone() const override`
- L99 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L103 _public member_ `FVector Velocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Units per second, world-space or relative to the actor depending on SettingsFlags.
- L107 _public member_ `uint8 SettingsFlags = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(Bitmask, BitmaskEnum="/Script/Mover.ELayeredMove_ConstantVelocitySettingsFlags"))` — @see ELayeredMove_ConstantVelocitySettingsFlags
- L109 _public prototype_ `virtual void ActivateFromContext(const FLayeredMoveActivationParams* ActivationParams) override;`
- L110 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLinearVelocityMoveData> : public TStructOpsTypeTraitsBase2<FLinearVelocityMoveData>`  
_L114-120_
- inherits: `TStructOpsTypeTraitsBase2<FLinearVelocityMoveData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L117-119_

#### class `ULinearVelocityMoveLogic`  
`class ULinearVelocityMoveLogic : public ULayeredMoveLogic`  
_L127-139_
- reflection: `UCLASS()`
- inherits: `ULayeredMoveLogic`
- desc: Linear Velocity (instanced): Induces a straight-line velocity on an actor over time. Async-compatible. Curve-based magnitude modulation is not supported; use FLayeredMove_LinearVelocity for that.
- L132 _public prototype_ `ULinearVelocityMoveLogic();`
- L134 _public function_ `virtual bool SupportsAsync() const override`
- L137 _protected prototype_ `virtual bool GenerateMove_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, const FMoverTickStartData& StartState, FProposedMove& OutProposedMove) override;`
- L138 _protected prototype_ `virtual bool GenerateMove_Async_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, const FMoverTickStartData& StartState, FProposedMove& OutProposedMove) override;`

#### struct `FLayeredMove_JumpImpulseOverDuration`  
`struct FLayeredMove_JumpImpulseOverDuration : public FLayeredMoveBase`  
_L147-171_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Jump Impulse Over Duration: introduces an instantaneous upwards change in velocity over a duration(ms). This overrides the existing 'up' component of the actor's current velocity Note: For a one time Jump Impulse consider using a FJumpImpulseEffect Instant Effect
- L151 _public prototype_ `FLayeredMove_JumpImpulseOverDuration();`
- L153 _public prototype_ `virtual ~FLayeredMove_JumpImpulseOverDuration() = default;`
- L157 _public member_ `float UpwardsSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Units per second, in whatever direction the target actor considers 'up'
- L160 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L162 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L164 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L166 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L168 _public prototype_ `virtual FString ToSimpleString() const override;`
- L170 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_JumpImpulseOverDuration > : public TStructOpsTypeTraitsBase2< FLayeredMove_JumpImpulseOverDuration >`  
_L174-181_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_JumpImpulseOverDuration>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L177-180_

#### struct `FLayeredMove_JumpTo`  
`struct FLayeredMove_JumpTo : public FLayeredMoveBase`  
_L187-239_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: JumpTo: Moves this actor in a more jump-like manner - specifying height and distance of jump rather than just upwards speed Note: this layered move is only intended for Mover actors using Z as it's up direction
- L191 _public prototype_ `FLayeredMove_JumpTo();`
- L192 _public prototype_ `virtual ~FLayeredMove_JumpTo() = default;`
- L196 _public member_ `float JumpDistance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Distance this jump impulse is supposed to reach
- L200 _public member_ `float JumpHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Height this jump impulse is supposed to reach
- L204 _public member_ `bool bUseActorRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true this jump will use the actor's rotation for jump direction instead of the Jump Rotation property.
- L208 _public member_ `FRotator JumpRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Direction to jump in. Only used if bUseActorRotation is false
- L212 _public member_ `TObjectPtr<UCurveVector> PathOffsetCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional CurveVector used to offset the actor from the path
- L216 _public member_ `TObjectPtr<UCurveFloat> TimeMappingCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional CurveFloat to modify jump impulse over the duration of the impulse
- L219 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L221 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L223 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L225 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L227 _public prototype_ `virtual FString ToSimpleString() const override;`
- L229 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L232 _protected prototype_ `FVector GetPathOffset(const float MoveFraction) const;` — helper function to apply movement vector offset from the PathOffsetCurve
- L235 _protected prototype_ `float EvaluateFloatCurveAtFraction(const UCurveFloat& Curve, const float Fraction) const;` — Helper function to apply TimeMappingCurve to the layered move
- L238 _protected prototype_ `FVector GetRelativeLocation(float MoveFraction, const FRotator& Rotator) const;` — Helper function for calculating position in jump given move fraction of total time for move

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_JumpTo > : public TStructOpsTypeTraitsBase2< FLayeredMove_JumpTo >`  
_L242-249_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_JumpTo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L245-248_

#### struct `FLayeredMove_MoveTo`  
`struct FLayeredMove_MoveTo : public FLayeredMoveBase`  
_L253-299_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: MoveTo: Move Actor from the starting location to the target location over a duration of time.
- L257 _public prototype_ `FLayeredMove_MoveTo();`
- L258 _public prototype_ `virtual ~FLayeredMove_MoveTo() = default;`
- L262 _public member_ `FVector StartLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Location to Start the MoveTo move from
- L266 _public member_ `FVector TargetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Location to move towards
- L270 _public member_ `bool bRestrictSpeedToExpected;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — if true, will restrict speed to where the actor is expected to be (in regard to start, end and duration)
- L274 _public member_ `TObjectPtr<UCurveVector> PathOffsetCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional CurveVector used to offset the actor from the path
- L278 _public member_ `TObjectPtr<UCurveFloat> TimeMappingCurve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional CurveFloat to apply to how fast the actor moves as they get closer to the target location
- L281 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L283 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L285 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L287 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L289 _public prototype_ `virtual FString ToSimpleString() const override;`
- L291 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L295 _protected prototype_ `FVector GetPathOffsetInWorldSpace(const float MoveFraction) const;` — helper function to apply movement vector offset from the PathOffsetCurve
- L298 _protected prototype_ `float EvaluateFloatCurveAtFraction(const UCurveFloat& Curve, const float Fraction) const;` — Helper function to apply TimeMappingCurve to the layered move

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_MoveTo > : public TStructOpsTypeTraitsBase2< FLayeredMove_MoveTo >`  
_L302-309_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_MoveTo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L305-308_

#### struct `FLayeredMove_MoveToDynamic`  
`struct FLayeredMove_MoveToDynamic : public FLayeredMove_MoveTo`  
_L316-339_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMove_MoveTo`
- desc: MoveToDynamic: Move Actor from the starting location to the target location over a duration of time with a moving target location You can either update TargetLocation manually to update the location this actor is moving towards or set an actor for this actor to move towards.
- L320 _public prototype_ `FLayeredMove_MoveToDynamic();`
- L321 _public prototype_ `virtual ~FLayeredMove_MoveToDynamic() = default;`
- L325 _public member_ `TObjectPtr<AActor> LocationActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional actor to move to. Note: this overrides the TargetLocation Property
- L328 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L330 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L332 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L334 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L336 _public prototype_ `virtual FString ToSimpleString() const override;`
- L338 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_MoveToDynamic > : public TStructOpsTypeTraitsBase2< FLayeredMove_MoveToDynamic >`  
_L342-349_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_MoveToDynamic>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L345-348_

#### struct `FLayeredMove_RadialImpulse`  
`struct FLayeredMove_RadialImpulse : public FLayeredMoveBase`  
_L353-412_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: RadialImpulse applies a velocity pulling or pushing away from a given world location to the target actor
- L357 _public prototype_ `FLayeredMove_RadialImpulse();`
- L358 _public prototype_ `virtual ~FLayeredMove_RadialImpulse() = default;`
- L362 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Location to pull or push actor from
- L366 _public member_ `TObjectPtr<AActor> LocationActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional Actor to pull or push this actor from. Note: this overrides the Location Property
- L370 _public member_ `float Radius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Radius from the location to apply radial velocity
- L374 _public member_ `float Magnitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Magnitude of velocity applied to actors in range
- L378 _public member_ `bool bIsPush;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true the velocity applied will push actor away from location, otherwise this layered move wil pull the actor towards it
- L382 _public member_ `bool bNoVerticalVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Whether to apply vertical velocity (based off mover components up direction) to the actor affected by this layered move
- L386 _public member_ `TObjectPtr<UCurveFloat> DistanceFalloff;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional Curvefloat to dictate falloff of velocity as you get further from the velocity location
- L390 _public member_ `TObjectPtr<UCurveFloat> MagnitudeOverTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional Curvefloat to dictate magnitude of velocity applied over time
- L394 _public member_ `bool bUseFixedWorldDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true velocity added to the actor will be in the direction of FixedWorldDirection, otherwise it will be calculated from the position of the actor and velocity location.
- L398 _public member_ `FRotator FixedWorldDirection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Direction to apply velocity from the radial impulse in. This is only taken into account if UseFixedWorldDirection is true.
- L401 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L403 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L405 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L407 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L409 _public prototype_ `virtual FString ToSimpleString() const override;`
- L411 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_RadialImpulse > : public TStructOpsTypeTraitsBase2< FLayeredMove_RadialImpulse >`  
_L415-422_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_RadialImpulse>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L418-421_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`
- L74 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40103`) — WithNetSerializer = true,
- L118 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40203`)
- L179 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40303`) — WithNetSerializer = true,
- L247 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40403`) — WithNetSerializer = true,
- L307 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40503`) — WithNetSerializer = true,
- L347 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40603`) — WithNetSerializer = true,
- L420 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon3db1aad40703`) — WithNetSerializer = true,

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/LaunchMove.h` (Public)


#### struct `FLaunchMoveActivationParams`  
`struct FLaunchMoveActivationParams : public FLayeredMoveActivationParams`  
_L12-24_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FLayeredMoveActivationParams`
- L18 _public member_ `FVector LaunchVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the updated component. Could be additive or overriding depending on MixMode setting.
- L22 _public member_ `FName ForceMovementMode = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.

#### struct `FLaunchMoveData`  
`struct FLaunchMoveData : public FLayeredMoveInstancedData`  
_L27-46_
- reflection: `USTRUCT(Blueprintable)`
- inherits: `FLayeredMoveInstancedData`
- L32 _public function_ `virtual FLayeredMoveInstancedData* Clone() const override` — @todo DanH: This is boilerplate begging for a macro
- L33 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L37 _public member_ `FVector LaunchVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the updated component. Could be additive or overriding depending on MixMode setting.
- L41 _public member_ `FName ForceMovementMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.
- L43 _public prototype_ `virtual void ActivateFromContext(const FLayeredMoveActivationParams* ActivationParams) override;`
- L45 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`

#### class `ULaunchMoveLogic`  
`class ULaunchMoveLogic : public ULayeredMoveLogic`  
_L50-71_
- reflection: `UCLASS()`
- inherits: `ULayeredMoveLogic`
- desc: TODO: Create data for this? Is it not needed?!
- L55 _public prototype_ `ULaunchMoveLogic();`
- L59 _public member_ `FVector LaunchVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the updated component. Could be additive or overriding depending on MixMode setting.
- L64 _public member_ `FName ForceMovementMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.
- L66 _public function_ `virtual bool SupportsAsync() const override`
- L69 _protected prototype_ `virtual bool GenerateMove_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, const FMoverTickStartData& StartState, FProposedMove& OutProposedMove) override;`
- L70 _protected prototype_ `virtual bool GenerateMove_Async_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, const FMoverTickStartData& StartState, FProposedMove& OutProposedMove) override;`

#### struct `FLayeredMove_Launch`  
`struct FLayeredMove_Launch : public FLayeredMoveBase`  
_L75-105_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Launch Move: provides an impulse velocity to the actor after (optionally) forcing them into a particular movement mode
- L79 _public prototype_ `FLayeredMove_Launch();`
- L80 _public prototype_ `virtual ~FLayeredMove_Launch() = default;`
- L84 _public member_ `FVector LaunchVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the actor. Could be additive or overriding depending on MixMode setting.
- L88 _public member_ `FName ForceMovementMode = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.
- L90 _public function_ `virtual bool SupportsAsync() const override`
- L93 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L94 _public prototype_ `virtual bool GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;`
- L96 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L98 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L100 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L102 _public prototype_ `virtual FString ToSimpleString() const override;`
- L104 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_Launch > : public TStructOpsTypeTraitsBase2< FLayeredMove_Launch >`  
_L109-115_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_Launch>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L112-114_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L113 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anond21300d40103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/MontageStateProvider.h` (Public)


#### struct `FMoverAnimMontageState`  
`struct FMoverAnimMontageState`  
_L17-57_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about montages that is replicated to simulated clients
- L22 _public member_ `TObjectPtr<UAnimMontage> Montage;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L29 _public member_ `FName Debug_MontageName;` — `UPROPERTY(VisibleAnywhere, Category = Mover, meta = (DisplayName = "MontageName"))` — Asset name of Montage, kept in sync with the Montage pointer for CVD display (UObject references cannot cross the CVD trace boundary). Not net serialized -- derived locally from the Montage pointer on each machine. Only populated in non-shipping builds.
- L33 _public member_ `float StartingMontagePosition = 0.0f;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — Montage position when started (in unscaled seconds).
- L37 _public member_ `float PlayRate = 1.0f;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — Rate at which this montage is intended to play
- L41 _public member_ `float CurrentPosition = 0.0f;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — Current position (during playback only)
- L46 _public member_ `float BlendOutTimeSeconds = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — Duration of the blend-out in seconds, copied from the montage asset's default blend-out at move-creation time. Used by the PT to compute the blend-out trigger position.
- L53 _public member_ `bool bEnableAutoBlendOut = true;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — True when the simulation should automatically trigger blend-out based on playback position approaching the end of the montage. Set to false for montages that require an external stop signal (e.g. internally looping montages whose terminal section is reached via JumpToSection on the GT); for those, blend-out falls back to DurationMs expiry.
- L55 _public prototype_ `void Reset();`
- L56 _public prototype_ `void NetSerialize(FArchive& Ar);`

#### struct `FLayeredMove_MontageStateProvider`  
`struct FLayeredMove_MontageStateProvider : public FLayeredMoveBase`  
_L63-78_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Note this will become obsolete once layered move logic is represented by a uobject, allowing use of interface classes.
- L71 _public function_ `virtual void AppendMontageOutputEntry(TArray<FMoverSimDrivenMontageEntry>& OutEntries, const FMoverTimeStep& TimeStep) const` — Push simulation-authoritative montage state into the simulation output so the game thread can drive FAnimMontageInstance. Derived classes append one FMoverSimDrivenMontageEntry per active montage they own. TimeStep is provided so implementations can populate timing fields (FrameSimTimeMs, etc.) for precise interpolation. Default implementation is a no-op: base class has no montage state to contribute.
- L73 _public function_ `virtual FMoverAnimMontageState GetMontageState() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/MultiJumpLayeredMove.h` (Public)


#### struct `FLayeredMove_MultiJump`  
`struct FLayeredMove_MultiJump : public FLayeredMoveBase`  
_L17-56_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: MultiJump: layered move for handling multiple jumps without touching the ground i.e. a double jump. Note: This layered move ends automatically when the actor hits a valid floor so duration is expected to be less than 0.
- L21 _public prototype_ `FLayeredMove_MultiJump();`
- L22 _public prototype_ `virtual ~FLayeredMove_MultiJump() = default;`
- L26 _public member_ `int32 MaximumInAirJumps;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Jumping", meta = (ClampMin = "1", UIMin = "1"))` — Maximum Jumps an actor could perform while in the air
- L30 _public member_ `float UpwardsSpeed;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jumping", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Units per second, in whatever direction the target actor considers 'up'
- L33 _public prototype_ `virtual bool WantsToJump(const FMoverInputCmdContext& InputCmd);` — returns true if input context has state that the actor wants to jump
- L36 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L38 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L40 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L42 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L44 _public prototype_ `virtual FString ToSimpleString() const override;`
- L46 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L50 _protected member_ `int32 JumpsInAirRemaining;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jumping")`
- L53 _protected member_ `double TimeOfLastJumpMS;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Jumping")`
- L55 _protected prototype_ `bool PerformJump(const FMoverDefaultSyncState* SyncState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, FProposedMove& OutProposedMove);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_MultiJump > : public TStructOpsTypeTraitsBase2< FLayeredMove_MultiJump >`  
_L59-66_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_MultiJump>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L62-65_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVER_API`
- L64 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone9a304e60103`) — WithNetSerializer = true,

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/LayeredMoves/RootMotionAttributeLayeredMove.h` (Public)


#### struct `FLayeredMove_RootMotionAttribute`  
`struct FLayeredMove_RootMotionAttribute : public FLayeredMoveBase`  
_L19-50_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Root Motion Attribute Move: handles root motion from a mesh's custom attribute, ignoring scaling. Currently only supports Independent ticking mode, and allows controlled movement while jumping/falling or when a SkipAnimRootMotion tag is active.
- L23 _public prototype_ `FLayeredMove_RootMotionAttribute();`
- L24 _public prototype_ `virtual ~FLayeredMove_RootMotionAttribute() = default;`
- L28 _public member_ `bool bConstrainWorldRotToMovementPlane = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true, any root motion rotations will be projected onto the movement plane (in worldspace), relative to the "up" direction. Otherwise, they'll be taken as-is.
- L32 _protected member_ `bool bDidAttrHaveRootMotionForResim = false;` — These member variables are NOT replicated. They are used if we rollback and resimulate when the root motion attribute is no longer in sync.
- L33 _protected member_ `FTransform LocalRootMotionForResim;`
- L34 _protected member_ `FMotionWarpingUpdateContext WarpingContextForResim;`
- L37 _protected prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L39 _protected prototype_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const override;`
- L41 _protected prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L43 _protected prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L45 _protected prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L47 _protected prototype_ `virtual FString ToSimpleString() const override;`
- L49 _protected prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMove_RootMotionAttribute > : public TStructOpsTypeTraitsBase2< FLayeredMove_RootMotionAttribute >`  
_L53-59_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMove_RootMotionAttribute>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L56-58_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`
- L12 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_AnimRootMotion_MeshAttribute);`
- L57 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon5ea5c90d0103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/AsyncFallingMode.h` (Public)


#### class `UAsyncFallingMode`  
`class UAsyncFallingMode : public UBaseMovementMode`  
_L19-97_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Experimental)`
- inherits: `UBaseMovementMode`
- desc: AsyncFallingMode: a default movement mode for moving through the air and jumping, typically influenced by gravity and air control This mode simulates movement without actually modifying any scene component(s).
- L25 _public prototype_ `UAsyncFallingMode(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L28 _public prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L29 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L30 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L34 _public member_ `FMover_OnLanded OnLanded;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when this actor lands on a valid surface.
- L41 _public member_ `bool bCancelVerticalSpeedOnLanding;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true, actor will land and lose all speed in the vertical direction upon landing. If false, actor's vertical speed will be redirected based on the surface normal it hit. Note: Actor's horizontal speed will not be affected if true. If false, horizontal speed may be increased on landing.
- L48 _public member_ `float AirControlPercentage;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ClampMax="1.0"))` — When falling, amount of movement control available to the actor. 0 = no control, 1 = full control
- L55 _public member_ `float FallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling slower than terminal velocity. Note: This is NOT applied to vertical velocity, only movement plane velocity
- L62 _public member_ `float OverTerminalSpeedFallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling faster than terminal velocity Note: This is NOT applied to vertical velocity, only movement plane velocity
- L70 _public member_ `float TerminalMovementPlaneSpeed;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s"))` — If the actor's movement plane velocity is greater than this speed falling will start applying OverTerminalSpeedFallingDeceleration instead of FallingDeceleration The expected behavior is to set OverTerminalSpeedFallingDeceleration higher than FallingDeceleration so the actor will slow down faster when going over TerminalMovementPlaneSpeed.
- L74 _public member_ `bool bShouldClampTerminalVerticalSpeed;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — When exceeding maximum vertical speed, should it be enforced via a hard clamp? If false, VerticalFallingDeceleration will be used for a smoother transition to the terminal speed limit.
- L78 _public member_ `float VerticalFallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!bShouldClampTerminalVerticalSpeed", ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to vertical velocity when it's greater than TerminalVerticalSpeed. Only used if bShouldClampTerminalVerticalSpeed is false.
- L84 _public member_ `float TerminalVerticalSpeed;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s"))` — If the actors vertical velocity is greater than this speed VerticalFallingDeceleration will be applied to vertical velocity
- L92 _protected prototype_ `virtual void ProcessLanded(const FFloorCheckResult& FloorResult, FVector Location, FVector& Velocity, FRelativeBaseInfo& BaseInfo, FMoverTickEndData& TickEndData) const;` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Is called at the end of the tick in falling mode. Handles checking any landings that should occur and switching to specific modes (i.e. landing on a walkable surface would switch to the walking movement mode)
- L94 _protected prototype_ `void CaptureFinalState(const FMoverDefaultSyncState* StartSyncState, const FVector FinalLocation, const FRotator FinalRotation, const FFloorCheckResult& FloorResult, float DeltaSeconds, float DeltaSecondsUsed, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState, FMoverTickEndData& TickEndData, FMovementRecord& Record) const;`
- L96 _protected member_ `TWeakObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/AsyncFlyingMode.h` (Public)


#### class `UAsyncFlyingMode`  
`class UAsyncFlyingMode : public UBaseMovementMode`  
_L20-40_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Experimental)`
- inherits: `UBaseMovementMode`
- desc: AsyncFlyingMode: a default movement mode for moving through the air freely, but still interacting with blocking geometry. The moving actor will remain upright vs the movement plane. This mode is threadsafe, and simulates movement without actually modifying any scene component(s).
- L31 _public member_ `bool bRespectDistanceOverWalkableSurfaces = false;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true, the actor will 'float' above any walkable surfaces to maintain the same height as ground-based modes. This can prevent pops when transitioning to ground-based movement, at the cost of performing floor checks while flying.
- L33 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L34 _public prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L35 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L36 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L39 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/AsyncNavWalkingMode.h` (Public)


#### class `UAsyncNavWalkingMode`  
`class UAsyncNavWalkingMode : public UBaseMovementMode`  
_L25-140_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Experimental)`
- inherits: `UBaseMovementMode`
- desc: AsyncNavWalkingMode: a default movement mode for traversing surfaces and movement bases by using an active navmesh when moving the actor rather than collision checks. Note: This movement mode requires a NavMoverComponent be on the actor to function properly. This mode also contains some randomization to avoid navmesh look ups happening at the same time (which is fine for AI characters running on the server) but may cause issues if used on autonomous proxies. This mode simulates movement without actually modifying any scene component(s).
- L30 _public prototype_ `UAsyncNavWalkingMode();`
- L32 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L33 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L34 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L40 _public member_ `bool bSweepWhileNavWalking;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — Whether or not the actor should sweep for collision geometry while walking.
- L44 _public member_ `bool bProjectNavMeshWalking;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — Whether to raycast to underlying geometry to better conform navmesh-walking actors
- L51 _public member_ `float NavMeshProjectionHeightScaleUp;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bProjectNavMeshWalking", ClampMin = "0", UIMin = "0"))` — Scale of the total capsule height to use for projection from navmesh to underlying geometry in the upward direction. In other words, start the trace at [CapsuleHeight * NavMeshProjectionHeightScaleUp] above nav mesh.
- L58 _public member_ `float NavMeshProjectionHeightScaleDown;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bProjectNavMeshWalking", ClampMin = "0", UIMin = "0"))` — Scale of the total capsule height to use for projection from navmesh to underlying geometry in the downward direction. In other words, trace down to [CapsuleHeight * NavMeshProjectionHeightScaleDown] below nav mesh.
- L62 _public member_ `float NavMeshProjectionInterval;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bProjectNavMeshWalking", ForceUnits = "s"))` — How often we should raycast to project from navmesh to underlying geometry
- L66 _public member_ `float NavMeshProjectionInterpSpeed;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta = (editcondition = "bProjectNavMeshWalking", ClampMin = "0", UIMin = "0"))` — Speed at which to interpolate agent navmesh offset between traces. 0: Instant (no interp) > 0: Interp speed")
- L70 _public member_ `EProjectNavMeshToGeometryBehavior ProjectNavMeshToGeometryBehavior = EProjectNavMeshToGeometryBehavior::UseTopGeometry;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking"))` — What to do when we are projecting nav movement onto geometry from the nav mesh
- L74 _public member_ `EOffNavMeshBehavior BehaviorOffNavMesh = EOffNavMeshBehavior::SwitchToWalking;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — What should we do if we stray off the nav mesh?
- L78 _public member_ `bool bSlideAlongNavMeshEdge = false;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — If attempting to stray off the nav mesh, should we slide along the edge instead? See @BehaviorOffNavMesh for cases where a sliding move can't be determined.
- L82 _public member_ `float NavMeshProjectionTimer;` — `UPROPERTY(Transient)`
- L85 _public member_ `FNavLocation CachedNavLocation;` — last known location projected on navmesh
- L94 _public prototype_ `virtual bool FindNavFloor(const FVector& TestLocation, FNavLocation& OutNavFloorLocation, const INavigationDataInterface* NavData) const;` — Project a location to navmesh to find adjusted height. @param TestLocation			Location to project @param OutNavFloorLocation	Location on navmesh @param NavData				NavigationDataInterface to search TestLocation for @return True if projection was performed (successfully or not)
- L98 _public prototype_ `UObject* GetTurnGenerator();` — `UFUNCTION(BlueprintPure, Category = Mover)` — Returns the active turn generator. Note: you will need to cast the return value to the generator you expect to get, it can also be none
- L102 _public prototype_ `void SetTurnGeneratorClass(UPARAM(meta = (MustImplement = "/Script/Mover.TurnGeneratorInterface", AllowAbstract = "false"))` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets the active turn generator to use the class provided. Note: To set it back to the default implementation pass in none
- L106 _protected member_ `TWeakObjectPtr<UNavMoverComponent> NavMoverComponent;` — Associated Movement component that will actually move the actor
- L109 _protected member_ `TWeakInterfacePtr<const INavigationDataInterface> NavDataInterface;` — Note: This isn't guaranteed to be valid at all times. It will be most of the time but re-entering this mode to call Activate() will search for NavData again and update it accordingly.
- L113 _protected member_ `uint8 bProjectNavMeshOnBothWorldChannels : 1;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadOnly, AdvancedDisplay)` — Use both WorldStatic and WorldDynamic channels for NavWalking geometry conforming
- L117 _protected member_ `TObjectPtr<UObject> TurnGenerator;` — `UPROPERTY(EditAnywhere, Instanced, Category = Mover, meta = (ObjectMustImplement = "/Script/Mover.TurnGeneratorInterface"))` — Optional modular object for generating rotation towards desired orientation. If not specified, linear interpolation will be used.
- L120 _protected prototype_ `const INavigationDataInterface* GetNavData() const;` — Get Navigation data for the actor. Returns null if there is no associated nav data.
- L123 _protected prototype_ `virtual void FindBestNavMeshLocation(const FVector& TraceStart, const FVector& TraceEnd, const FVector& CurrentFeetLocation, const FVector& TargetNavLocation, FHitResult& OutHitResult) const;` — Performs trace for ProjectLocationFromNavMesh
- L130 _protected prototype_ `virtual FVector ProjectLocationFromNavMesh(float DeltaSeconds, const FVector& CurrentFeetLocation, const FVector& TargetNavLocation, float UpOffset, float DownOffset);` — Attempts to better align navmesh walking actors with underlying geometry (sometimes navmesh can differ quite significantly from geometry). Updates CachedProjectedNavMeshHitResult, access this for more info about hits.
- L133 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L134 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L136 _protected prototype_ `void CaptureOutputState(const FMoverDefaultSyncState& StartSyncState, const FVector& FinalLocation, const FRotator& FinalRotation, const FMovementRecord& Record, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState, FMoverTickEndData& OutputState) const;`
- L138 _protected member_ `TWeakObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/AsyncWalkingMode.h` (Public)


#### class `UAsyncWalkingMode`  
`class UAsyncWalkingMode : public UBaseMovementMode`  
_L23-60_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, Experimental)`
- inherits: `UBaseMovementMode`
- desc: AsyncWalkingMode: a default movement mode for traversing surfaces and movement bases (walking, running, sneaking, etc.) This mode simulates movement without actually modifying any scene component(s).
- L28 _public prototype_ `UAsyncWalkingMode(const FObjectInitializer& ObjectInitializer);`
- L30 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L31 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L32 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L36 _public prototype_ `UObject* GetTurnGenerator();` — `UFUNCTION(BlueprintPure, Category=Mover)` — Returns the active turn generator. Note: you will need to cast the return value to the generator you expect to get, it can also be none
- L40 _public prototype_ `void SetTurnGeneratorClass(UPARAM(meta=(MustImplement="/Script/Mover.TurnGeneratorInterface", AllowAbstract="false"))` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Sets the active turn generator to use the class provided. Note: To set it back to the default implementation pass in none
- L46 _protected member_ `EStaticFloorCheckPolicy FloorCheckPolicy = EStaticFloorCheckPolicy::OnDynamicBaseOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Choice of behavior for floor checks while not moving.
- L50 _protected member_ `TObjectPtr<UObject> TurnGenerator;` — `UPROPERTY(EditAnywhere, Instanced, Category=Mover, meta=(ObjectMustImplement="/Script/Mover.TurnGeneratorInterface"))` — Optional modular object for generating rotation towards desired orientation. If not specified, linear interpolation will be used.
- L52 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L53 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L55 _protected prototype_ `void CaptureFinalState(const FMoverDefaultSyncState* StartingState, const FVector FinalLocation, const FRotator FinalRotation, bool bDidAttemptMovement, const FFloorCheckResult& FloorResult, const FMovementRecord& Record, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState) const;`
- L57 _protected prototype_ `FRelativeBaseInfo UpdateFloorAndBaseInfo(const FFloorCheckResult& FloorResult, FVector CurrentLocation) const;`
- L59 _protected member_ `TWeakObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/FallingMode.h` (Public)


#### class `UFallingMode`  
`class UFallingMode : public UBaseMovementMode`  
_L21-108_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: FallingMode: a default movement mode for moving through the air and jumping, typically influenced by gravity and air control
- L27 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L29 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L33 _public member_ `FMover_OnLanded OnLanded;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when this actor lands on a valid surface.
- L40 _public member_ `bool bCancelVerticalSpeedOnLanding;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true, actor will land and lose all speed in the vertical direction upon landing. If false, actor's vertical speed will be redirected based on the surface normal it hit. Note: Actor's horizontal speed will not be affected if true. If false, horizontal speed may be increased on landing.
- L47 _public member_ `float AirControlPercentage;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ClampMax="1.0"))` — When falling, amount of movement control available to the actor. 0 = no control, 1 = full control
- L54 _public member_ `float FallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling slower than terminal velocity. Note: This is NOT applied to vertical velocity, only movement plane velocity
- L63 _public member_ `float FallingLateralFriction;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))` — Friction to apply to air movement. Lateral velocity is scaled each tick by a factor (1-Friction * TimeStep) so friction values greater than 1/TimeStep will result in all lateral velocity being removed. Note: This is NOT applied to vertical velocity, only movement plane velocity
- L70 _public member_ `float OverTerminalSpeedFallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to air movement when falling faster than terminal velocity Note: This is NOT applied to vertical velocity, only movement plane velocity
- L78 _public member_ `float TerminalMovementPlaneSpeed;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s"))` — If the actor's movement plane velocity is greater than this speed falling will start applying OverTerminalSpeedFallingDeceleration instead of FallingDeceleration The expected behavior is to set OverTerminalSpeedFallingDeceleration higher than FallingDeceleration so the actor will slow down faster when going over TerminalMovementPlaneSpeed.
- L82 _public member_ `bool bShouldClampTerminalVerticalSpeed;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — When exceeding maximum vertical speed, should it be enforced via a hard clamp? If false, VerticalFallingDeceleration will be used for a smoother transition to the terminal speed limit.
- L86 _public member_ `float VerticalFallingDeceleration;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!bShouldClampTerminalVerticalSpeed", ClampMin="0", ForceUnits = "cm/s^2"))` — Deceleration to apply to vertical velocity when it's greater than TerminalVerticalSpeed. Only used if bShouldClampTerminalVerticalSpeed is false.
- L92 _public member_ `float TerminalVerticalSpeed;` — `UPROPERTY(Category=Mover, EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ForceUnits = "cm/s"))` — If the actors vertical velocity is greater than this speed VerticalFallingDeceleration will be applied to vertical velocity
- L100 _protected prototype_ `virtual void ProcessLanded(const FFloorCheckResult& FloorResult, FVector Location, FVector& Velocity, FRelativeBaseInfo& BaseInfo, FMoverTickEndData& TickEndData) const;` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Is called at the end of the tick in falling mode. Handles checking any landings that should occur and switching to specific modes (i.e. landing on a walkable surface would switch to the walking movement mode)
- L102 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L103 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L105 _protected prototype_ `void CaptureFinalState(USceneComponent* UpdatedComponent, const FMoverDefaultSyncState& StartSyncState, const FFloorCheckResult& FloorResult, float DeltaSeconds, float DeltaSecondsUsed, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState, FMoverTickEndData& TickEndData, FMovementRecord& Record) const;`
- L107 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnLanded, const FName&, NextMovementModeName, const FHitResult&, HitResult);` — Fired after the actor lands on a valid surface. First param is the name of the mode this actor is in after landing. Second param is the hit result from hitting the floor.
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnLanded, const FName&, NextMovementModeName, const FHitResult&, HitResult);` — Fired after the actor lands on a valid surface. First param is the name of the mode this actor is in after landing. Second param is the hit result from hitting the floor.

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/FlyingMode.h` (Public)


#### class `UFlyingMode`  
`class UFlyingMode : public UBaseMovementMode`  
_L19-43_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: FlyingMode: a default movement mode for moving through the air freely, but still interacting with blocking geometry. The moving actor will remain upright vs the movement plane.
- L30 _public member_ `bool bRespectDistanceOverWalkableSurfaces = false;` — `UPROPERTY(Category = Mover, EditAnywhere, BlueprintReadWrite)` — If true, the actor will 'float' above any walkable surfaces to maintain the same height as ground-based modes. This can prevent pops when transitioning to ground-based movement, at the cost of performing floor checks while flying.
- L32 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L34 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L37 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L38 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L40 _protected prototype_ `void CaptureFinalState(USceneComponent* UpdatedComponent, FMovementRecord& Record, const FMoverDefaultSyncState& StartSyncState, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState, const float DeltaSeconds) const;`
- L42 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/NavWalkingMode.h` (Public)


#### enum `EOffNavMeshBehavior`  
`enum class EOffNavMeshBehavior : uint8`  
_L22-35_
- reflection: `UENUM(BlueprintType)`
- desc: Options for what to do when we find ourselves off the nav mesh
- L25 _public enumerator_ `SwitchToWalking = 0 UMETA(DisplayName = "Switch to Walking Mode")` — We change to normal walking mode and re-attempt the move. Typically this is more expensive than nav walking, and we'll later need to switch back to nav walking.
- L28 _public enumerator_ `MoveWithoutNavMesh = 1 UMETA(DisplayName = "Move Without Nav Mesh")` — We proceed to move as directed, but height may diverge from the floor until we return to a valid nav mesh.
- L31 _public enumerator_ `DoNotMove = 2 UMETA(DisplayName = "Do Not Move or Rotate")` — We do not move. Movement will continue once instructed to move over nav mesh again.
- L34 _public enumerator_ `RotateOnly = 3 UMETA(DisplayName = "Rotate Only")` — We do not move, but will allow rotation in place. Movement will continue once instructed to move over nav mesh again.

#### enum `EProjectNavMeshToGeometryBehavior`  
`enum class EProjectNavMeshToGeometryBehavior : uint8`  
_L39-46_
- reflection: `UENUM(BlueprintType)`
- desc: Options for what to do when we are projecting nav movement onto geometry from the nav mesh
- L42 _public enumerator_ `UseClosestGeometry = 0 UMETA(DisplayName = "Use closest Geometry")` — Projects movement onto the closest geometry to the target location projected onto the navmesh.
- L45 _public enumerator_ `UseTopGeometry = 1 UMETA(DisplayName = "Use Top Geometry")` — Projects movement onto the top most geometry in projection range of the navmesh

#### class `UNavWalkingMode`  
`class UNavWalkingMode : public UBaseMovementMode`  
_L59-181_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: NavWalkingMode: a default movement mode for traversing surfaces and movement bases by using an active navmesh when moving the actor rather than collision checks. Note: This movement mode requires a NavMoverComponent be on the actor to function properly. This mode also contains some randomization to avoid navmesh look ups happening at the same time (which is fine for AI characters running on the server) but may cause issues if used on autonomous proxies.
- L64 _public prototype_ `UNavWalkingMode();`
- L66 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L67 _public prototype_ `virtual void Deactivate(const FMoverEventContext& Context, FName NextModeName, const FMoverSimContext& SimContext) override;`
- L68 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L69 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L75 _public member_ `bool bSweepWhileNavWalking;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — Whether or not the actor should sweep for collision geometry while walking.
- L79 _public member_ `bool bProjectNavMeshWalking;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadOnly)` — Whether to raycast to underlying geometry to better conform navmesh-walking actors
- L86 _public member_ `float NavMeshProjectionHeightScaleUp;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking", ClampMin="0", UIMin="0"))` — Scale of the total capsule height to use for projection from navmesh to underlying geometry in the upward direction. In other words, start the trace at [CapsuleHeight * NavMeshProjectionHeightScaleUp] above nav mesh.
- L93 _public member_ `float NavMeshProjectionHeightScaleDown;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking", ClampMin="0", UIMin="0"))` — Scale of the total capsule height to use for projection from navmesh to underlying geometry in the downward direction. In other words, trace down to [CapsuleHeight * NavMeshProjectionHeightScaleDown] below nav mesh.
- L97 _public member_ `float NavMeshProjectionInterval;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking", ForceUnits="s"))` — How often we should raycast to project from navmesh to underlying geometry
- L101 _public member_ `float NavMeshProjectionInterpSpeed;` — `UPROPERTY(Category="NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking", ClampMin="0", UIMin="0"))` — Speed at which to interpolate agent navmesh offset between traces. 0: Instant (no interp) > 0: Interp speed")
- L105 _public member_ `EProjectNavMeshToGeometryBehavior ProjectNavMeshToGeometryBehavior = EProjectNavMeshToGeometryBehavior::UseTopGeometry;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bProjectNavMeshWalking"))` — What to do when we are projecting nav movement onto geometry from the nav mesh
- L109 _public member_ `EOffNavMeshBehavior BehaviorOffNavMesh = EOffNavMeshBehavior::SwitchToWalking;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — What should we do if we stray off the nav mesh?
- L113 _public member_ `bool bSlideAlongNavMeshEdge = false;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadWrite)` — If attempting to stray off the nav mesh, should we attempt to slide along the edge instead? See @BehaviorOffNavMesh for cases where a sliding move can't be determined.
- L116 _public member_ `float NavMeshProjectionTimer;` — `UPROPERTY(Transient)`
- L119 _public member_ `FNavLocation CachedNavLocation;` — last known location projected on navmesh
- L128 _public prototype_ `virtual bool FindNavFloor(const FVector& TestLocation, FNavLocation& OutNavFloorLocation, const INavigationDataInterface* NavData) const;` — Project a location to navmesh to find adjusted height. @param TestLocation			Location to project @param OutNavFloorLocation	Location on navmesh @param NavData				NavigationDataInterface to search TestLocation for @return True if projection was performed (successfully or not)
- L132 _public prototype_ `UObject* GetTurnGenerator();` — `UFUNCTION(BlueprintPure, Category=Mover)` — Returns the active turn generator. Note: you will need to cast the return value to the generator you expect to get, it can also be none
- L136 _public prototype_ `void SetTurnGeneratorClass(UPARAM(meta=(MustImplement="/Script/Mover.TurnGeneratorInterface", AllowAbstract="false"))` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Sets the active turn generator to use the class provided. Note: To set it back to the default implementation pass in none
- L141 _protected member_ `TObjectPtr<UNavMoverComponent> NavMoverComponent;` — `UPROPERTY(BlueprintReadOnly, Category="Nav Movement")` — Associated Movement component that will actually move the actor
- L144 _protected member_ `TWeakInterfacePtr<const INavigationDataInterface> NavDataInterface;` — Note: This isn't guaranteed to be valid at all times. It will be most of the time but re-entering this mode to call Activate() will search for NavData again and update it accordingly.
- L148 _protected member_ `uint8 bProjectNavMeshOnBothWorldChannels : 1;` — `UPROPERTY(Category = "NavMesh Movement", EditAnywhere, BlueprintReadOnly, AdvancedDisplay)` — Use both WorldStatic and WorldDynamic channels for NavWalking geometry conforming
- L152 _protected member_ `TObjectPtr<UObject> TurnGenerator;` — `UPROPERTY(EditAnywhere, Instanced, Category=Mover, meta=(ObjectMustImplement="/Script/Mover.TurnGeneratorInterface"))` — Optional modular object for generating rotation towards desired orientation. If not specified, linear interpolation will be used.
- L155 _protected prototype_ `virtual void SetCollisionForNavWalking(bool bEnable);` — Switch collision settings for NavWalking mode (ignore world collisions)
- L158 _protected prototype_ `const INavigationDataInterface* GetNavData() const;` — Get Navigation data for the actor. Returns null if there is no associated nav data.
- L161 _protected prototype_ `virtual void FindBestNavMeshLocation(const FVector& TraceStart, const FVector& TraceEnd, const FVector& CurrentFeetLocation, const FVector& TargetNavLocation, FHitResult& OutHitResult) const;` — Performs trace for ProjectLocationFromNavMesh
- L168 _protected prototype_ `virtual FVector ProjectLocationFromNavMesh(float DeltaSeconds, const FVector& CurrentFeetLocation, const FVector& TargetNavLocation, float UpOffset, float DownOffset);` — Attempts to better align navmesh walking actors with underlying geometry (sometimes navmesh can differ quite significantly from geometry). Updates CachedProjectedNavMeshHitResult, access this for more info about hits.
- L171 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L172 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L174 _protected prototype_ `void CaptureFinalState(USceneComponent* UpdatedComponent, const FMovementRecord& Record, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState) const;`
- L176 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`
- L179 _protected member_ `ECollisionResponse CollideVsWorldStatic = ECollisionResponse::ECR_Block;` — Collision responses saved at the activation of this mode, to be restored as upon deactivation if the CDO can't be used
- L180 _protected member_ `ECollisionResponse CollideVsWorldDynamic = ECollisionResponse::ECR_Block;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`
- L48 _namespace_ `namespace NavWalkingUtils`
- L50 _prototype_ `void CheckClientSideNavigationSettings(const UMoverComponent* MoverComponent);` (scope `NavWalkingUtils`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/SimpleFlyingMode.h` (Public)


#### class `USimpleFlyingMode`  
`class USimpleFlyingMode : public UFlyingMode`  
_L15-31_
- reflection: `UCLASS(BlueprintType, Abstract)`
- inherits: `UFlyingMode`
- desc: Basic flying mode that will move exactly where inputs request. Easy to derive from to create custom behaviors
- L21 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L25 _public prototype_ `void GenerateFlyingMove(UPARAM(ref) FMoverTickStartData& StartState, float DeltaSeconds, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, UPARAM(ref) FVector& InOutAngularVelocityDegrees, UPARAM(ref) FVector& InOutVelocity);` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Generate Simple Flying Move"))` — Override this to make a simple flying mode
- L30 _public member_ `float MaxSpeedOverride = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Flying Settings", meta = (ForceUnits = "cm/s"))` — If this value is greater or equal to 0, this will override the max speed read from the CommonLegacyMovementSettings

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/SimpleSpringWalkingMode.h` (Public)


#### class `USimpleSpringWalkingMode`  
`class USimpleSpringWalkingMode : public USimpleWalkingMode`  
_L16-35_
- reflection: `UCLASS(BlueprintType)`
- inherits: `USimpleWalkingMode`
- desc: A walking mode that uses a critically damped spring for translation and rotation. The strength of the critically damped spring is set via smoothing times (separate for translation and rotation)
- L21 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L22 _public prototype_ `virtual void GenerateWalkMove_Implementation(FMoverTickStartData& StartState, float DeltaSeconds, const FMoverSimContext& SimContext, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, FVector& InOutAngularVelocityDegrees, FVector& InOutVelocity) override;`
- L27 _protected member_ `float VelocitySmoothingTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Spring Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L30 _protected member_ `float FacingSmoothingTime = 0.2f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Spring Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))`
- L34 _protected member_ `float VelocityDeadzoneThreshold = 0.1f;` — Below this speed we set velocity to 0

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/SimpleWalkingMode.h` (Public)


#### class `USimpleWalkingMode`  
`class USimpleWalkingMode : public UWalkingMode`  
_L15-34_
- reflection: `UCLASS(BlueprintType, Abstract)`
- inherits: `UWalkingMode`
- desc: Basic walking mode that implements the ground based walking
- L20 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L21 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L25 _public prototype_ `void GenerateWalkMove(UPARAM(ref) FMoverTickStartData& StartState, float DeltaSeconds, const FMoverSimContext& SimContext, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, UPARAM(ref) FVector& InOutAngularVelocityDegrees, UPARAM(ref) FVector& InOutVelocity);` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Generate Simple Walk Move"))` — Override this to make a simple walking mode
- L30 _public member_ `float MaxSpeedOverride = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Walking Settings", meta = (ForceUnits = "cm/s"))` — If this value is greater or equal to 0, this will override the max speed read from the common legacy shared walk settings
- L33 _protected member_ `static const FName DidGenerateMoveEntry;` — boolean blackboard entry name, set whenever GenerateWalkMove finishes - valid through next frame

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/SmoothWalkingMode.h` (Public)


#### class `USmoothWalkingMode`  
`class USmoothWalkingMode : public USimpleWalkingMode`  
_L16-107_
- reflection: `UCLASS(BlueprintType, Experimental)`
- inherits: `USimpleWalkingMode`
- desc: A walking mode that provides a simplified version of the default walking mode model with additional options for smoothing.
- L21 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L22 _public prototype_ `virtual void GenerateWalkMove_Implementation(FMoverTickStartData& StartState, float DeltaSeconds, const FMoverSimContext& SimContext, const FVector& DesiredVelocity, const FQuat& DesiredFacing, const FQuat& CurrentFacing, FVector& InOutAngularVelocityDegrees, FVector& InOutVelocity) override;`
- L30 _protected member_ `float Acceleration = 1500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Base acceleration to apply when the desired velocity magnitude is greater than the current velocity.
- L34 _protected member_ `float Deceleration = 1500.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Base deceleration to apply when the desired velocity magnitude is less than the current velocity
- L43 _protected member_ `float DirectionalAccelerationFactor = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — Value between 0 and 1 that controls how the acceleration is applied. When set to 1 this will effectively add the acceleration in the direction of the desired velocity on top of the current velocity then clip the result. This emulates the behavior of the default walking mode. When set to 0 it will apply an acceleration which changes the current velocity directly towards the desired velocity. This makes directional changes in velocity faster and more regular, always using a fixed acceleration, but can cause the overall velocity magnitude to dip during turning.
- L51 _protected member_ `float TurningStrength = 10.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0"))` — Applies an additional force that rotates the velocity to make it face the desired direction of travel. This allows quick turns which don't lose speed but adds additional acceleration to the system. Valid values range roughly between 0 and 100, where 10 would be considered already quite a strong turning force and 100 will produce near instant turns (before smoothing).
- L55 _protected member_ `float AccelerationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — Controls how much smoothing is applied to the velocity changes of the movement when accelerating. Set to zero to apply no smoothing.
- L59 _protected member_ `float DecelerationSmoothingTime = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — Controls how much smoothing is applied to the velocity changes of the movement when decelerating. Set to zero to apply no smoothing.
- L68 _protected member_ `float AccelerationSmoothingCompensation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — When the velocity is smoothed it will naturally lag behind the unsmoothed target. This factor controls how much this is compensated for by tracking a future target that is the appropriate amount of time in the future when accelerating. Setting this to 0 will produce smoother, more S-shaped velocity profiles but may reduce the feeling of responsiveness. Setting this to 1 increases the feeling of responsiveness but makes the initial change in velocity less smooth and reduces the effective "lead-in".
- L72 _protected member_ `float DecelerationSmoothingCompensation = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))` — This parameter acts the same as AccelerationSmoothingCompensation but is applied during deceleration instead
- L76 _protected member_ `float VelocityDeadzoneThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Controls the point at which the velocity will "snap" to the desired velocity once it is close enough
- L80 _protected member_ `float AccelerationDeadzoneThreshold = 0.001f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Controls the point at which the acceleration will "snap" to zero when the desired velocity is reached
- L87 _protected member_ `float OutsideInfluenceSmoothingTime = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — Controls how quickly the built-up internal velocity will be modified when the character's movement is influenced by the outside factors such as collisions. Setting this to a small value will mean that collisions and other outside influences on the character's velocity "reset" the built-up internal velocity quickly. Larger values will mean that the character loses less momentum and takes less time to re-accumulate internal velocity in situations such as glancing collisions and other short external impulses such as pushes.
- L93 _protected member_ `float FacingSmoothingTime = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "s"))` — Controls how much smoothing is applied to the facing direction. Set to zero to apply no smoothing.
- L97 _protected member_ `bool bSmoothFacingWithDoubleSpring = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings")` — Smooths facing using a double spring rather than a single spring. This produces a more S-shaped profile with a shorter "lead-out".
- L101 _protected member_ `float FacingDeadzoneThreshold = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "deg"))` — Controls the point at which the facing will "snap" to the desired facing once it is close enough
- L105 _protected member_ `float AngularVelocityDeadzoneThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover|Advanced Smooth Walking Settings", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "deg/s"))` — Controls the point at which the angular velocity will "snap" to zero when the desired facing is reached

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/SwimmingMode.h` (Public)


#### struct `FSwimmingControlSettings`  
`struct FSwimmingControlSettings`  
_L19-189_
- reflection: `USTRUCT(BlueprintType)`
- desc: Controls for the Swimming Movement
- L23 _public function_ `FSwimmingControlSettings()`
- L29 _public member_ `float CancelCrouchImmersionDepth = 28.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — At or below this depth, cancel and disallow crouching.
- L33 _public member_ `float DBNOSwimImmersionDepth = 50.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — At or below this depth, start swimming in DBNO
- L37 _public member_ `float MaxAcceleration = 350.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max acceleration.
- L41 _public member_ `float MaxAccelerationSprinting = 490.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max acceleration while sprinting.
- L45 _public member_ `float BrakingDeceleration = 400.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Braking deceleration (decel when letting go of input)
- L49 _public member_ `float MaxNormalSpeed = 0.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max speed when not sprinting and moving normally (before water velocity is applied)
- L53 _public member_ `float MaxSprintSpeed = 1.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max sprint speed (before water velocity is applied)
- L57 _public member_ `float MinSprintJumpSpeed = -0.03f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Min speed required (relative to water) to maintain sprint while jumping, otherwise will stop sprint (and change anims).
- L61 _public member_ `float SprintJumpAirAccelAngleLimit = 0.25f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — If accel deviates from velocity by this angle while sprint jumping in air, stop sprint (and change anims).
- L64 _public member_ `float SprintRetriggerDelay = 210.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)`
- L67 _public member_ `float SprintDelayAfterFiring = 385.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)`
- L71 _public member_ `float MaxTargetingSpeed = 300.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max speed when targeting (before water velocity is applied)
- L75 _public member_ `float BackwardsSpeedMultiplier = 50.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Directional multiplier when moving mostly backwards
- L79 _public member_ `float BackwardsSpeedCosAngle = 0.10f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Directional multiplier is applied when dot product of velocity and player facing direction is < this.
- L83 _public member_ `float AngledSpeedMultiplier = 0.70f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Speed multiplier when moving off angle (velocity and acceleration divergent)
- L87 _public member_ `float AngledSpeedCosAngle = 250.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Angled multiplier is applied when dot product of velocity and acceleration is < this.
- L91 _public member_ `float Friction = 0.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Friction, ie how floaty or snappy is changing direction.
- L95 _public member_ `float FrictionSprinting = -0.30f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Friction, ie how floaty or snappy is changing direction.
- L99 _public member_ `float FrictionDirectionChangeDot = 0.40f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — If Dot(Velocity, Acceleration) < this value, apply FrictionDirectionChangeMultiplier to friction value used. Allows lower friction when changing direction hard, which slows velocity change.
- L103 _public member_ `float FrictionDirectionChangeMultiplier = 0.75f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Friction multiplier (usually < 1) when changing direction.
- L106 _public member_ `float MaxSpeedUp = 500.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)`
- L109 _public member_ `float MaxSpeedDown = 1000.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)`
- L112 _public member_ `float MaxHorizontalEntrySpeed = 1200.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)`
- L116 _public member_ `float WaterForceMultiplier = 2.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Multiplier to water force acceleration in direction of current.
- L120 _public member_ `float WaterForceSecondMultiplier = 1.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Multiplier applied on the top of WaterForceMultiplier, to water force acceleration in direction of current. Used only for inherited objects.
- L124 _public member_ `float MaxWaterForce = 400.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max water force, after WaterVelocity * (WaterForceMultiplier * WaterForceSecondMultiplier).
- L128 _public member_ `float WaterVelocityDepthForMax = 175.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — At or above this depth, use max velocity. Interps down to WaterVelocityMinMultiplier at wading depth (where player can start swimming)
- L132 _public member_ `float WaterVelocityMinMultiplier = 0.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Min velocity multiplier applied when depth equals min swimming depth (where they transition from wading to swimming). Interps between this and 1.0 at WaterVelocityDepthForMax.
- L136 _public member_ `float WaterSimMaxTimeStep = 0.10f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Max time step allowed, to prevent huge forces on hitches.
- L140 _public member_ `float WaterSimSubStepTime = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Simulation sub-step time allowed for higher quality movement (local player and server).
- L144 _public member_ `float BobbingMaxForce = 3800.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing:
- L148 _public member_ `float BobbingIdealDepthTolerance = 7.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: Slow down strongly when within this tolerance of the ideal immersion depth. Normally we apply drag only when going away from the ideal depth, this allows some slowdown when approaching it.
- L152 _public member_ `float BobbingFrictionDown = 5.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, linear multiplier per second
- L156 _public member_ `float BobbingExpDragDown = 0.05f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L160 _public member_ `float BobbingFrictionDownSubmerged = 7.50f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to downward velocity, linear multiplier per second. Only used when fully submerged (replaces other value).
- L164 _public member_ `float BobbingExpDragDownSubmerged = 0.10f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L168 _public member_ `float BobbingFrictionUp = 7.00f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, linear multiplier per second
- L172 _public member_ `float BobbingExpDragUp = 0.20f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction/drag opposed to upward velocity, squared with velocity per second. Ramps up faster with higher speeds, less effect at low speeds.
- L176 _public member_ `float BobbingFrictionMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: friction multiplier, multiplies the fluid friction value.
- L180 _public member_ `float BobbingExpDragMultiplier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: multiplier for the exponential drag.
- L184 _public member_ `float BoostDragMultiplier = 1.85f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Bobbing: multiplier when in sprint boost to keep from popping up and out as much.
- L188 _public member_ `float JumpMultiplier = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwimmingControl)` — Multiplies ground's jump speed

#### class `USwimmingMode`  
`class USwimmingMode : public UBaseMovementMode`  
_L195-221_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: SwimmingMode: a default movement mode for traversing water volumes
- L201 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L203 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L206 _public member_ `FSwimmingControlSettings SurfaceSwimmingWaterControlSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Water Control")`
- L209 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L210 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L212 _protected prototype_ `virtual bool AttemptJump(const FSimulationTickParams& Params, float UpwardsSpeed, FMoverTickEndData& Output);`
- L214 _protected prototype_ `void CaptureFinalState(USceneComponent* UpdatedComponent, const FFloorCheckResult& FloorResult, const FMovementRecord& Record, FMoverDefaultSyncState& OutputSyncState) const;`
- L216 _protected prototype_ `FRelativeBaseInfo UpdateFloorAndBaseInfo(const FFloorCheckResult& FloorResult) const;`
- L218 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`
- L220 _protected member_ `float OriginalCapsuleHalfHeight = 75.f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Modes/WalkingMode.h` (Public)


#### enum `EStaticFloorCheckPolicy`  
`enum class EStaticFloorCheckPolicy : uint8`  
_L19-26_
- reflection: `UENUM(BlueprintType)`
- desc: Behavior policy for performing floor checks in walking mode when no movement is occurring.
- L22 _public enumerator_ `Always = 0 UMETA(DisplayName = "Always")` — Always perform floor checks, even when not moving. You may want this if static bases may disappear from underneath.
- L25 _public enumerator_ `OnDynamicBaseOnly = 1 UMETA(DisplayName = "OnDynamicBaseOnly")` — Only perform floor checks when not moving IF we're on a dynamic movement base

#### class `UWalkingMode`  
`class UWalkingMode : public UBaseMovementMode`  
_L34-70_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UBaseMovementMode`
- desc: WalkingMode: a default movement mode for traversing surfaces and movement bases (walking, running, sneaking, etc.)
- L40 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState) override;`
- L41 _public prototype_ `virtual void GenerateMove_Implementation(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const override;`
- L42 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L46 _public prototype_ `UObject* GetTurnGenerator();` — `UFUNCTION(BlueprintPure, Category=Mover)` — Returns the active turn generator. Note: you will need to cast the return value to the generator you expect to get, it can also be none
- L50 _public prototype_ `void SetTurnGeneratorClass(UPARAM(meta=(MustImplement="/Script/Mover.TurnGeneratorInterface", AllowAbstract="false"))` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Sets the active turn generator to use the class provided. Note: To set it back to the default implementation pass in none
- L56 _protected member_ `EStaticFloorCheckPolicy FloorCheckPolicy = EStaticFloorCheckPolicy::OnDynamicBaseOnly;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Choice of behavior for floor checks while not moving.
- L60 _protected member_ `TObjectPtr<UObject> TurnGenerator;` — `UPROPERTY(EditAnywhere, Instanced, Category=Mover, meta=(ObjectMustImplement="/Script/Mover.TurnGeneratorInterface"))` — Optional modular object for generating rotation towards desired orientation. If not specified, linear interpolation will be used.
- L62 _protected prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext) override;`
- L63 _protected prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext) override;`
- L65 _protected prototype_ `void CaptureFinalState(const FMoverDefaultSyncState* StartingState, USceneComponent* UpdatedComponent, bool bDidAttemptMovement, const FFloorCheckResult& FloorResult, const FMovementRecord& Record, const FMoverTimeStep& TimeStep, const FVector& AngularVelocityDegrees, FMoverDefaultSyncState& OutputSyncState) const;`
- L67 _protected prototype_ `FRelativeBaseInfo UpdateFloorAndBaseInfo(const FFloorCheckResult& FloorResult, FVector CurrentLocation) const;`
- L69 _protected member_ `TObjectPtr<const UCommonLegacyMovementSettings> CommonLegacySettings;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/MovementModifiers/StanceModifier.h` (Public)


#### enum `EStanceMode`  
`enum class EStanceMode : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `Invalid = 0` — Invalid default stance
- L19 _public enumerator_ `Crouch` — Actor goes into crouch
- L21 _public enumerator_ `Prone` — Actor goes into prone - not currently implemented

#### struct `FStanceModifier`  
`struct FStanceModifier : public FMovementModifierBase`  
_L30-80_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMovementModifierBase`
- desc: Stances: Applies settings to the actor to make them go into different stances like crouch or prone(not implemented), affects actor maxacceleration and capsule height Note: This modifier currently uses the CDO of the actor to reset values to "standing" values. This modifier also assumes the actor is using a capsule as it's updated component for now
- L35 _public prototype_ `FStanceModifier();`
- L36 _public prototype_ `virtual ~FStanceModifier() override = default;`
- L38 _public member_ `EStanceMode ActiveStance;`
- L40 _public prototype_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const override;`
- L41 _public prototype_ `virtual void GetGameplayTags(FGameplayTagContainer& InOutTags) const override;`
- L44 _public prototype_ `virtual void OnStart(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState) override;` — Fired when this modifier is activated.
- L47 _public prototype_ `virtual void OnEnd(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState) override;` — Fired when this modifier is deactivated.
- L50 _public prototype_ `virtual void OnPreMovement(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep) override;` — Fired just before a Substep
- L53 _public prototype_ `virtual void OnPostMovement(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState) override;` — Fired after a Substep
- L56 _public prototype_ `virtual FMovementModifierBase* Clone() const override;` — @return newly allocated copy of this FMovementModifier. Must be overridden by child classes
- L58 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L60 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L62 _public prototype_ `virtual FString ToSimpleString() const override;`
- L64 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
- L66 _public prototype_ `virtual bool CanExpand(const UCharacterMoverComponent* MoverComp) const;`
- L69 _public prototype_ `virtual bool ShouldExpandingMaintainBase(const UCharacterMoverComponent* MoverComp) const;` — Whether expanding should be from the base of the capsule or not
- L73 _protected prototype_ `virtual void AdjustCapsule(UMoverComponent* MoverComp, float OldHalfHeight, float NewHalfHeight, float NewEyeHeight);` — Modifies the updated component casted to a capsule component
- L76 _protected prototype_ `void ApplyMovementSettings(UMoverComponent* MoverComp);` — Applies any movement settings like acceleration or max speed changes
- L79 _protected prototype_ `void RevertMovementSettings(UMoverComponent* MoverComp);` — Reverts any movement settings like acceleration or max speed changes

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FStanceModifier > : public TStructOpsTypeTraitsBase2< FStanceModifier >`  
_L83-89_
- inherits: `TStructOpsTypeTraitsBase2<FStanceModifier>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L86-88_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVER_API`
- L87 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonb72235ec0103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/MoverMontageSimulationTypes.h` (Public)


#### struct `FMoverSimDrivenMontageEntry`  
`struct FMoverSimDrivenMontageEntry`  
_L17-68_
- reflection: `USTRUCT()`
- desc: Per-move montage state snapshot produced by the simulation each substep. Not serialized over the network: this is an in-process simulation->game thread scratch struct.
- L23 _public member_ `TObjectPtr<UAnimMontage> Montage = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Montage asset; key for game thread tracking.
- L28 _public member_ `FName Debug_MontageName;` — `UPROPERTY(VisibleAnywhere, Category = Mover, meta = (DisplayName = "MontageName"))` — Asset name of Montage, kept in sync with the Montage pointer for CVD display (UObject references cannot cross the CVD trace boundary). Debug-only: not net serialized.
- L32 _public member_ `float CurrentPosition = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation-authoritative position at the END of this substep (seconds, unscaled by PlayRate)
- L36 _public member_ `float PlayRate = 1.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — PlayRate at which the montage is playing
- L42 _public member_ `float FrameSimTimeMs = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation time (ms) at the end of the substep that produced this entry. FMoverSimDrivenMontageData::Interpolate uses this to reconstruct the display-time simulation time and deliver lifecycle events precisely rather than taking them blindly from the To frame.
- L46 _public member_ `float StartSimTimeMs = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation time (ms) when the montage move was first activated. Informational for CVD.
- L51 _public member_ `float BlendOutSimTimeMs = -1.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation time (ms) when blend-out was first triggered. -1 means not yet triggered. Interpolate fires bShouldBlendOut exactly when the interpolated display time crosses this threshold.
- L55 _public member_ `float FinishSimTimeMs = -1.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation time (ms) when the montage was first detected as finished. -1 means not yet.
- L59 _public member_ `bool bShouldBlendOut = false;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation has computed that blend-out should begin. Game thread calls Montage_Stop(BlendOutTimeSeconds) once.
- L63 _public member_ `float BlendOutTimeSeconds = 0.f;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Blend-out duration (seconds) to pass to Montage_Stop when bShouldBlendOut first becomes true
- L67 _public member_ `bool bIsFinished = false;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Simulation has finished the move entirely. Game thread calls Montage_Stop(0) or lets existing blend-out finish.

#### struct `FMoverSimDrivenMontageData`  
`struct FMoverSimDrivenMontageData : public FMoverDataStructBase`  
_L73-89_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Simulation output for montage-driving layered moves. Stored in AdditionalOutputData so it flows through the FSimulationOutputData interpolation path (CurrentPosition is lerped between simulation frames).
- L79 _public member_ `TArray<FMoverSimDrivenMontageEntry> MontageStates;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — One entry per active montage-driving layered move on the simulation this substep
- L81 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L82 _public function_ `virtual FMoverDataStructBase* Clone() const override`
- L88 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;` — Lerps CurrentPosition between simulation frames for smooth game thread animation. Lifecycle flags (bShouldBlendOut, bIsFinished) are recomputed from the interpolated simulation time crossing BlendOutSimTimeMs/FinishSimTimeMs, so they fire at the precise display moment rather than snapping to the To-frame value.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverSimDrivenMontageData> : public TStructOpsTypeTraitsBase2<FMoverSimDrivenMontageData>`  
_L92-95_
- inherits: `TStructOpsTypeTraitsBase2<FMoverSimDrivenMontageData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L94-94_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L94 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon33df4ed10103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/NavMoverComponent.h` (Public)


#### class `UNavMoverComponent`  
`class UNavMoverComponent : public UActorComponent, public INavMovementInterface, public IRVOAvoidanceInterface`  
_L27-207_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,INavMovementInterface,IRVOAvoidanceInterface`
- desc: NavMoverComponent: Responsible for implementing INavMoveInterface with UMoverComponent so pathfinding and other forms of navigation movement work. This component also caches the input given to it that is then consumed by the mover system. This component supports a basic version of the RVO avoidance interface to make it usable with Detour Crowd Avoidance. It does not support force based RVO avoidance, but this or child component would be a good place to update/evaluate Avoidance information and apply effects to the Mover Simulation. Note: This component relies on the parent actor having a MoverComponent as well. By default, this component only has a reference to MoverComponent meaning we use other ways (such as gameplay tags for the active movement mode) to check for state rather than calling specific functions on the active MoverComponent.
- L32 _public prototype_ `UNavMoverComponent();`
- L36 _public member_ `FNavAgentProperties NavAgentProps;` — `UPROPERTY(EditAnywhere, Category="Nav Movement", meta = (DisplayName = "Movement Capabilities", Keywords = "Nav Agent"))` — Properties that define how the component can move.
- L40 _public member_ `FMovementProperties MovementState;` — `UPROPERTY()` — Expresses runtime state of character's movement. Put all temporal changes to movement properties here
- L44 _public member_ `int32 AvoidanceUID;` — `UPROPERTY(Category="Avoidance", VisibleAnywhere, BlueprintReadOnly, AdvancedDisplay)` — No default value, for now it's assumed to be valid if GetAvoidanceManager() returns non-NULL.
- L48 _public member_ `FNavAvoidanceMask AvoidanceGroup;` — `UPROPERTY(Category="Avoidance", EditAnywhere, BlueprintReadOnly, AdvancedDisplay)` — Moving actor's group mask
- L51 _public prototype_ `void SetAvoidanceGroupMask(const FNavAvoidanceMask& GroupMask);` — `UFUNCTION(BlueprintCallable, Category = "Nav Movement|Avoidance")`
- L55 _public member_ `FNavAvoidanceMask GroupsToAvoid;` — `UPROPERTY(Category="Avoidance", EditAnywhere, BlueprintReadOnly, AdvancedDisplay)` — Will avoid other agents if they are in one of specified groups
- L58 _public prototype_ `void SetGroupsToAvoidMask(const FNavAvoidanceMask& GroupMask);` — `UFUNCTION(BlueprintCallable, Category = "Nav Movement|Avoidance")`
- L62 _public member_ `FNavAvoidanceMask GroupsToIgnore;` — `UPROPERTY(Category="Avoidance", EditAnywhere, BlueprintReadOnly, AdvancedDisplay)` — Will NOT avoid other agents if they are in one of specified groups, higher priority than GroupsToAvoid
- L65 _public prototype_ `void SetGroupsToIgnoreMask(const FNavAvoidanceMask& GroupMask);` — `UFUNCTION(BlueprintCallable, Category = "Nav Movement|Avoidance")`
- L69 _public member_ `float AvoidanceWeight;` — `UPROPERTY(Category="Avoidance", EditAnywhere, BlueprintReadOnly)` — De facto default value 0.5 (due to that being the default in the avoidance registration function), indicates RVO behavior.
- L72 _public member_ `float AvoidanceConsiderationRadius;` — `UPROPERTY(Category="Avoidance", EditAnywhere, BlueprintReadOnly, meta=(ForceUnits=cm))`
- L77 _protected member_ `FNavMovementProperties NavMovementProperties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Nav Movement")` — associated properties for nav movement
- L80 _protected member_ `uint64 GameFrameNavMovementConsumed = 0;` — Keeps track of the last game frame we consumed nav movement.
- L83 _protected member_ `uint64 GameFrameNavMovementRequested = 0;` — Keeps track of the last game frame we requested nav movement.
- L86 _protected member_ `FVector CachedNavMoveInputIntent = FVector::ZeroVector;` — Used to store movement input intent from requested moves
- L88 _protected member_ `FVector CachedNavMoveInputVelocity = FVector::ZeroVector;` — Used to store movement input velocity from requested moves
- L92 _protected member_ `TWeakInterfacePtr<IPathFollowingAgentInterface> PathFollowingComp;` — object implementing IPathFollowingAgentInterface. Is private to control access to it. @see SetPathFollowingAgent, GetPathFollowingAgent
- L96 _protected member_ `TWeakObjectPtr<UMoverComponent> MoverComponent;` — `UPROPERTY()` — Associated Movement component that will actually move the actor
- L99 _public prototype_ `virtual void InitializeComponent() override;`
- L100 _public prototype_ `virtual void BeginPlay() override;`
- L103 _public function_ `virtual UObject* GetOwnerAsObject() const override` — Get the owner of the object consuming nav movement
- L106 _public function_ `virtual TObjectPtr<UObject> GetUpdatedObject() const override` — Get the component this movement component is updating
- L109 _public prototype_ `virtual void GetSimpleCollisionCylinder(float& CollisionRadius, float& CollisionHalfHeight) const override;` — Get axis-aligned cylinder around this actor, used for simple collision checks in nav movement
- L112 _public prototype_ `virtual FVector GetSimpleCollisionCylinderExtent() const override;` — Returns collision extents vector for this object, based on GetSimpleCollisionCylinder.
- L115 _public prototype_ `virtual FVector GetForwardVector() const override;` — Get forward vector of the object being driven by nav movement
- L119 _public prototype_ `virtual FVector GetVelocityForNavMovement() const override;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|NavMovement")` — Get the current velocity of the movement component
- L123 _public prototype_ `virtual float GetMaxSpeedForNavMovement() const override;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|NavMovement")` — Get the max speed of the movement component
- L126 _public prototype_ `virtual void StopMovementImmediately() override;` — Overridden to also call StopActiveMovement().
- L130 _public prototype_ `bool ConsumeNavMovementData(FVector& OutMoveInputIntent, FVector& OutMoveInputVelocity);` — `UFUNCTION(BlueprintCallable, Category="AI|Components|NavMovement")` — Writes internal cached requested velocities to the MoveInput passed in. Returns true if it had move input to write.
- L133 _public prototype_ `virtual FVector GetLocation() const override;` — Returns location of controlled actor - meaning center of collision bounding box
- L135 _public prototype_ `virtual FVector GetFeetLocation() const override;` — Returns location of controlled actor's "feet": the center bottom of its collision bounding box at its current location
- L137 _public prototype_ `virtual FVector GetFeetLocationAt(FVector ComponentLocation) const;` — Returns location of controlled actor's "feet": the center bottom of its collision bounding box, as if it was at a specific location
- L139 _public prototype_ `virtual FBasedPosition GetFeetLocationBased() const override;` — Returns based location of controlled actor
- L142 _public prototype_ `virtual void UpdateNavAgent(const UObject& ObjectToUpdateFrom) override;` — Set nav agent properties from an object
- L145 _public prototype_ `virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;` — path following: request new velocity
- L148 _public prototype_ `virtual void RequestPathMove(const FVector& MoveInput) override;` — path following: request new move input (normal vector = full strength)
- L152 _public prototype_ `virtual bool CanStopPathFollowing() const override;` — check if current move target can be reached right now if positions are matching (e.g. performing scripted move and can't stop)
- L155 _public function_ `virtual FNavMovementProperties* GetNavMovementProperties() override` — Get Nav movement props struct this component uses
- L157 _public function_ `virtual const FNavMovementProperties& GetNavMovementProperties() const override` — Returns the NavMovementProps(const)
- L159 _public prototype_ `virtual void SetPathFollowingAgent(IPathFollowingAgentInterface* InPathFollowingAgent) override;`
- L160 _public prototype_ `virtual IPathFollowingAgentInterface* GetPathFollowingAgent() override;`
- L161 _public prototype_ `virtual const IPathFollowingAgentInterface* GetPathFollowingAgent() const override;`
- L164 _public prototype_ `virtual const FNavAgentProperties& GetNavAgentPropertiesRef() const override;` — Returns the NavAgentProps(const)
- L166 _public prototype_ `virtual FNavAgentProperties& GetNavAgentPropertiesRef() override;` — Returns the NavAgentProps
- L169 _public prototype_ `virtual void ResetMoveState() override;` — Resets runtime movement state to character's movement capabilities
- L172 _public prototype_ `virtual bool CanStartPathFollowing() const override;` — Returns true if path following can start
- L175 _public prototype_ `virtual bool IsCrouching() const override;` — Returns true if currently crouching
- L178 _public prototype_ `virtual bool IsFalling() const override;` — Returns true if currently falling (not flying, in a non-fluid volume, and not on the ground)
- L181 _public prototype_ `virtual bool IsMovingOnGround() const override;` — Returns true if currently moving on the ground (e.g. walking or driving)
- L185 _public prototype_ `virtual bool IsSwimming() const override;` — `UFUNCTION(BlueprintCallable, Category="AI|Components|NavMovement")` — Returns true if currently swimming (moving through a fluid volume)
- L188 _public prototype_ `virtual bool IsFlying() const override;` — Returns true if currently flying (moving through a non-fluid volume without resting on the ground)
- L191 _public prototype_ `virtual void SetRVOAvoidanceUID(int32 UID) override;` — BEGIN IRVOAvoidanceInterface
- L192 _public prototype_ `virtual int32 GetRVOAvoidanceUID() override;`
- L193 _public prototype_ `virtual void SetRVOAvoidanceWeight(float Weight) override;`
- L194 _public prototype_ `virtual float GetRVOAvoidanceWeight() override;`
- L195 _public prototype_ `virtual FVector GetRVOAvoidanceOrigin() override;`
- L196 _public prototype_ `virtual float GetRVOAvoidanceRadius() override;`
- L197 _public prototype_ `virtual float GetRVOAvoidanceHeight() override;`
- L198 _public prototype_ `virtual float GetRVOAvoidanceConsiderationRadius() override;`
- L199 _public prototype_ `virtual FVector GetVelocityForRVOConsideration() override;`
- L200 _public prototype_ `virtual void SetAvoidanceGroupMask(int32 GroupFlags) override;`
- L201 _public prototype_ `virtual int32 GetAvoidanceGroupMask() override;`
- L202 _public prototype_ `virtual void SetGroupsToAvoidMask(int32 GroupFlags) override;`
- L203 _public prototype_ `virtual int32 GetGroupsToAvoidMask() override;`
- L204 _public prototype_ `virtual void SetGroupsToIgnoreMask(int32 GroupFlags) override;`
- L205 _public prototype_ `virtual int32 GetGroupsToIgnoreMask() override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Settings/CommonLegacyMovementSettings.h` (Public)


#### class `UCommonLegacyMovementSettings`  
`class UCommonLegacyMovementSettings : public UObject, public IMovementSettingsInterface`  
_L13-147_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovementSettingsInterface`
- desc: CommonLegacyMovementSettings: collection of settings that are shared between several of the legacy movement modes
- L17 _private function_ `virtual FString GetDisplayName() const override`
- L24 _public member_ `bool bShouldRemainVertical = true;` — `UPROPERTY(Category="General", EditAnywhere, BlueprintReadWrite)` — If true, the actor will remain upright with gravity despite any rotation applied to the actor
- L28 _public member_ `FName GroundMovementModeName = DefaultModeNames::Walking;` — `UPROPERTY(Category="General", EditAnywhere, BlueprintReadWrite)` — What movement mode to use when on the ground.
- L32 _public member_ `FName AirMovementModeName = DefaultModeNames::Falling;` — `UPROPERTY(Category="General", EditAnywhere, BlueprintReadWrite)` — What movement mode to use when airborne.
- L36 _public member_ `FName SwimmingMovementModeName = DefaultModeNames::Swimming;` — `UPROPERTY(Category = "General", EditAnywhere, BlueprintReadWrite)` — What movement mode to use when airborne.
- L40 _public member_ `float MaxWalkSlopeCosine = 0.71f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ground Movement")` — Walkable slope angle, represented as cosine(max slope angle) for performance reasons. Ex: for max slope angle of 30 degrees, value is cosine(30 deg) = 0.866
- L44 _public member_ `float FloorSweepDistance = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ground Movement", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Max distance to scan for floor surfaces under a Mover actor
- L50 _public member_ `bool bUseFlatBaseForFloorChecks = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ground Movement")` — Performs floor checks as if the object is using a shape with a flat base. This avoids the situation where we slowly lower off the side of a ledge when using shapes with rounded bottoms, like a capsule.
- L55 _public member_ `float PerchRadiusThreshold = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ground Movement", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Distance from the capsule edge within which floor surface contact is rejected for perching purposes. A value of 0 means the character can stand right at the capsule edge (no perch restriction). Increasing values make a character fall from a ledge earlier as it is approached.
- L59 _public member_ `float MaxStepHeight = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ground Movement", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Mover actors will be able to step up onto or over obstacles shorter than this
- L63 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Maximum speed in the movement plane
- L71 _public member_ `bool bUseAccelerationForVelocityMove = true;` — `UPROPERTY(Category="General", EditAnywhere, BlueprintReadWrite, AdvancedDisplay)` — Should use acceleration for velocity based movement intent? If true, acceleration is applied when using velocity input to reach the target velocity. If false, velocity is set directly, disregarding acceleration.
- L78 _public member_ `float GroundFriction = 8.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General|Friction", meta = (ClampMin = "0", UIMin = "0"))` — Setting that affects movement control. Higher values allow faster changes in direction. This can be used to simulate slippery surfaces such as ice or oil by lowering the value (possibly based on the material the actor is standing on).
- L87 _public member_ `uint8 bUseSeparateBrakingFriction:1;` — `UPROPERTY(Category="General|Friction", EditDefaultsOnly, BlueprintReadWrite)` — If true, BrakingFriction will be used to slow the character to a stop (when there is no Acceleration). If false, braking uses the same friction passed to CalcVelocity() (ie GroundFriction when walking), multiplied by BrakingFrictionFactor. This setting applies to all movement modes; if only desired in certain modes, consider toggling it when movement modes change. @see BrakingFriction
- L98 _public member_ `float BrakingFriction = 8.0f;` — `UPROPERTY(Category="General|Friction", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0", EditCondition="bUseSeparateBrakingFriction"))` — Friction (drag) coefficient applied when braking (whenever Acceleration = 0, or if character is exceeding max speed); actual value used is this multiplied by BrakingFrictionFactor. When braking, this property allows you to control how much friction is applied when moving across the ground, applying an opposing force that scales with current velocity. Braking is composed of friction (velocity-dependent drag) and constant deceleration. This is the current value, used in all movement modes; if this is not desired, override it or bUseSeparateBrakingFriction when movement mode changes. @note Only used if bUseSeparateBrakingFriction setting is true, otherwise current friction such as GroundFriction is used. @see bUseSeparateBrakingFriction, BrakingFrictionFactor, GroundFriction, BrakingDecelerationWalking
- L106 _public member_ `float BrakingFrictionFactor = 2.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General|Friction", meta=(ClampMin="0", UIMin="0"))` — Factor used to multiply actual value of friction used when braking. This applies to any friction value that is currently used, which may depend on bUseSeparateBrakingFriction. @note This is 2 by default for historical reasons, a value of 1 gives the true drag equation.
- L110 _public member_ `float Deceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Default max linear rate of deceleration when there is no controlled input
- L114 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — Default max linear rate of acceleration for controlled input. May be scaled based on magnitude of input.
- L118 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General", meta = (ClampMin = "-1", UIMin = "0", ForceUnits = "degrees/s"))` — Maximum rate of turning rotation (degrees per second). Negative numbers indicate instant rotation and should cause rotation to snap instantly to desired direction.
- L122 _public member_ `float TurningBoost = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="General", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "Multiplier"))` — Speeds velocity direction changes while turning, to reduce sliding
- L129 _public member_ `bool bIgnoreBaseRotation = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "General")` — Whether the actor ignores changes in rotation of the base it is standing on when using based movement. If true, the actor maintains its current world rotation. If false, the actor rotates with the moving base.
- L133 _public member_ `float JumpUpwardsSpeed = 500.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Jumping", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — Instantaneous speed induced in an actor upon jumping
- L137 _public member_ `float SwimmingStartImmersionDepth = 64.5f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Swimming", meta = (Units = "cm"))` — Depth at which the pawn starts swimming
- L141 _public member_ `float SwimmingIdealImmersionDepth = 51.66f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Swimming", meta = (Units = "cm"))` — Depth at which the pawn will float when in water
- L145 _public member_ `float SwimmingStopImmersionDepth = 39.9f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Swimming", meta = (Units = "cm"))` — Depth at which the pawn stops swimming

### `Plugins/Experimental/Mover/Source/Mover/Public/DefaultMovementSet/Settings/StanceSettings.h` (Public)


#### class `UStanceSettings`  
`class UStanceSettings : public UObject, public IMovementSettingsInterface`  
_L12-34_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IMovementSettingsInterface`
- desc: StanceSettings: collection of settings that are shared through the mover component and contain stance related settings.
- L16 _private function_ `virtual FString GetDisplayName() const override`
- L21 _public member_ `float CrouchingMaxAcceleration = 2000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s^2"))` — New max acceleration while in crouching
- L25 _public member_ `float CrouchingMaxSpeed = 200;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))` — New max speed while in crouching
- L29 _public member_ `float CrouchHalfHeight = 55;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — New capsule half height while crouching
- L33 _public member_ `float CrouchedEyeHeight = 50;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crouch")` — New eye height while crouching

### `Plugins/Experimental/Mover/Source/Mover/Public/InputContainerStruct.h` (Public)


#### struct `FMoverInputContainerDataStruct`  
`struct FMoverInputContainerDataStruct : public FMoverDataStructBase`  
_L18-36_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- L24 _public member_ `FMoverDataCollection InputCollection;` — All input data in this struct
- L29 _public function_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override` — This struct never triggers reconciliation
- L30 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float LerpFactor) override;`
- L31 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L32 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L34 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/InstantMovementEffect.h` (Public)


#### struct `FApplyMovementEffectParams`  
`struct FApplyMovementEffectParams`  
_L18-31_
- L20 _public member_ `USceneComponent* UpdatedComponent;`
- L22 _public member_ `UPrimitiveComponent* UpdatedPrimitive;`
- L24 _public member_ `const UMoverComponent* MoverComp;`
- L26 _public member_ `const FMoverTickStartData* StartState;`
- L28 _public member_ `const FMoverTimeStep* TimeStep;`
- L30 _public member_ `TArray<TSharedPtr<FMoverSimulationEventData>> OutputEvents;`

#### struct `FApplyMovementEffectParams_Async`  
`struct FApplyMovementEffectParams_Async`  
_L37-42_
- desc: Async safe parameters passed to ApplyMovementEffect_Async. It is almost certainly missing the Physics Object handle and other things, this is just a first pass
- L39 _public member_ `UMoverSimulation* Simulation;`
- L40 _public member_ `const FMoverTickStartData* StartState;`
- L41 _public member_ `const FMoverTimeStep* TimeStep;`

#### struct `FInstantMovementEffect`  
`struct FInstantMovementEffect`  
_L51-86_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Instant Movement Effects are methods of affecting movement state directly on a Mover-based actor for one tick. Note: This is only applied one tick and then removed Common uses would be for Teleporting, Changing Movement Modes directly, one time force application, etc. Multiple Instant Movement Effects can be active at the time
- L55 _public function_ `FInstantMovementEffect()`
- L57 _public prototype_ `virtual ~FInstantMovementEffect() = default;`
- L60 _public prototype_ `virtual FInstantMovementEffect* Clone() const;` — @return newly allocated copy of this FInstantMovementEffect. Must be overridden by child classes
- L62 _public prototype_ `virtual void NetSerialize(FArchive& Ar);`
- L64 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;`
- L66 _public prototype_ `virtual FString ToSimpleString() const;`
- L68 _public function_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector)`
- L78 _public function_ `virtual bool IsNearlyEqualTo(const FInstantMovementEffect& Other) const` — Returns true if this effect is considered nearly equal to Other for comparison purposes. Other is guaranteed to be the same struct type. Override in subclasses to allow tolerance-based equality instead of exact field matching (e.g. for server-side proposal validation in ChaosMover's Proposed auth style). Default: uses UScriptStruct's strict Identical test. If the struct's TStructOpsTypeTraits declares WithIdenticalViaEquality, CompareScriptStruct calls operator== on the struct; otherwise it compares each UPROPERTY field individually via reflection. Check the struct's TStructOpsTypeTraits specialization to know which path applies to a given subtype.
- L84 _public function_ `virtual bool ApplyMovementEffect(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState)` — Return false is the effect didn't apply at all, true if anything was modified, especially the output state's movement mode
- L85 _public function_ `virtual bool ApplyMovementEffect_Async(FApplyMovementEffectParams_Async& ApplyEffectParams, FMoverSyncState& OutputState)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FInstantMovementEffect > : public TStructOpsTypeTraitsBase2< FInstantMovementEffect >`  
_L89-96_
- inherits: `TStructOpsTypeTraitsBase2<FInstantMovementEffect>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L92-95_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L94 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon04841d310103`) — WithNetSerializer = true,

### `Plugins/Experimental/Mover/Source/Mover/Public/KinematicActorSimulation.h` (Public)


#### class `UKinematicActorSimulation`  
`class UKinematicActorSimulation : public UMoverSimulation`  
_L28-130_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMoverSimulation`
- L35 _public prototype_ `UKinematicActorSimulation();`
- L36 _public prototype_ `virtual void BeginDestroy() override;`
- L38 _public prototype_ `void Init(const FInitParams& InInitParams);`
- L39 _public prototype_ `void Uninit();`
- L43 _public prototype_ `void InitializeSimulationState(FMoverSyncState& OutSync, FMoverAuxStateContext& OutAux);` — Simulation driver interface: backend will call these on this simulation
- L45 _public prototype_ `void DoSimulationTick(const FMoverTimeStep& InTimeStep, const FMoverTickStartData& StartData, OUT FMoverTickEndData& EndData);` — UE_API virtual void ProduceInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd);
- L46 _public prototype_ `void RollbackToPriorState(const FMoverTimeStep& NewBaseTimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);`
- L50 _public prototype_ `virtual void QueueNextMode(FModeChangeParams ModeChangeParams) override;` — UMoverSimulation overrides:  threadsafe functions for external systems or internal simulation mechanisms to influence the simulation
- L52 _public prototype_ `virtual FName GetNextModeName() const override;`
- L54 _public prototype_ `virtual bool HasFeaturesWithTag(FGameplayTag TagToMatch, bool bRequireExactMatch) const override;`
- L55 _public prototype_ `virtual void CancelFeaturesWithTag(FGameplayTag TagToCancel, bool bRequireExactMatch = false) override;`
- L57 _public prototype_ `virtual void RegisterMovementMode(FModeRegistrationParams ModeRegisterParams) override;`
- L58 _public prototype_ `virtual void UnregisterMovementMode(FModeRegistrationParams ModeRegisterParams) override;`
- L60 _public prototype_ `virtual const FMovementModifierBase* FindQueuedModifier(FMovementModifierHandle ModifierHandle) const override;`
- L61 _public prototype_ `virtual const FMovementModifierBase* FindQueuedModifierByType(const UScriptStruct* ModifierType) const override;`
- L62 _public prototype_ `virtual FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier) override;`
- L63 _public prototype_ `virtual void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle) override;`
- L69 _protected prototype_ `void RegisterMovementModes(const TMap<FName, TWeakObjectPtr<UBaseMovementMode>>& ModeMap, FName StartingModeName);` — Setup functions
- L70 _protected prototype_ `void RegisterGlobalTransitions(const TArray<TWeakObjectPtr<UBaseMovementModeTransition>>& Transitions);`
- L72 _protected prototype_ `virtual void CheckForExternalChanges(const FMoverTickStartData& SimStartingData);`
- L76 _protected prototype_ `virtual void PrepareStateDataForNewFrame(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartData, FMoverTickEndData& EndData);` — JAH NOTE: this is a good candidate for being in the base class
- L82 _protected prototype_ `virtual void OnPreSimulationAdvance(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartData, FMoverTickEndData& EndData);` — Customizable events called by this simulation UE_API virtual void OnInit(); UE_API virtual void OnDeinit();
- L83 _protected prototype_ `void AdvanceSimulation(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartData, FMoverTickEndData& EndData);`
- L84 _protected prototype_ `virtual void OnPostSimulationAdvance(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartData, FMoverTickEndData& EndData);`
- L90 _protected prototype_ `virtual void OnSimulationRolledBack(const FMoverTimeStep& NewBaseTimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — JAH TODO: Make a version of this that provides the PREVIOUS state as well UE_API virtual void OnSimulationRolledBack(const FMoverTimeStep& NewBaseTimeStep, const FMoverSyncState& PrevSyncState);
- L112 _protected member_ `FInitParams InitParams;`
- L115 _protected member_ `TObjectPtr<UMovementModeStateMachine> ModeFSM;` — `UPROPERTY()`
- L118 _protected member_ `TObjectPtr<UMoverComponent> MoverComp;` — `UPROPERTY()`
- L121 _protected member_ `FMoverSyncState LastSyncState;`
- L122 _protected member_ `FMoverAuxStateContext LastAuxState;`
- L124 _protected member_ `FMoverTimeStep LastSimTickTimeStep;` — Saved timestep info from our last simulation tick, used during rollback handling. This will rewind during corrections.
- L125 _protected member_ `FMoverTimeStep NewestSimTickTimeStep;` — Saved timestep info from the newest (farthest-advanced) simulation tick. This will not rewind during corrections.
- L126 _protected member_ `bool bJustStartedResim = false;`
- L129 _private prototype_ `FString GetContextNameSafe() const;` — internally used for logging actor owner name

#### struct `UKinematicActorSimulation::FInitParams`  
`struct FInitParams`  
_L95-108_
- L97 _public member_ `TMap<FName, TWeakObjectPtr<UBaseMovementMode>> ModesToRegister;`
- L98 _public member_ `TArray<TWeakObjectPtr<UBaseMovementModeTransition>> TransitionsToRegister;`
- L99 _public member_ `FName StartingMovementMode = NAME_None;`
- L102 _public member_ `TWeakObjectPtr<UMovementMixer> MovementMixer = nullptr;` — TWeakObjectPtr<UNullMovementMode> NullMovementMode = nullptr; TWeakObjectPtr<UImmediateMovementModeTransition> ImmediateModeTransition = nullptr;
- L104 _public member_ `UWorld* World = nullptr;` — FTransform TransformOnInit = FTransform::Identity;
- L105 _public member_ `TWeakObjectPtr<UMoverComponent> MoverComp = nullptr;`
- L106 _public member_ `TWeakObjectPtr<USceneComponent> UpdatedComp = nullptr;`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/LayeredMove.h` (Public)


#### enum `ELayeredMoveFinishVelocityMode`  
`enum class ELayeredMoveFinishVelocityMode : uint8`  
_L21-29_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `MaintainLastRootMotionVelocity = 0` — Maintain the last velocity root motion gave to the character
- L26 _public enumerator_ `SetVelocity` — Set Velocity to the specified value (for example, 0,0,0 to stop the character)
- L28 _public enumerator_ `ClampVelocity` — Clamp velocity magnitude to the specified value. Note that it will not clamp Z if negative (falling). it will clamp Z positive though.

#### struct `FLayeredMoveFinishVelocitySettings`  
`struct FLayeredMoveFinishVelocitySettings`  
_L35-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct for LayeredMove Finish Velocity options.
- L39 _public function_ `FLayeredMoveFinishVelocitySettings() : SetVelocity(FVector::ZeroVector) , ClampVelocity(0.f) , FinishVelocityMode(ELayeredMoveFinishVelocityMode::MaintainLastRootMotionVelocity)`
- L45 _public prototype_ `void NetSerialize(FArchive& Ar);`
- L49 _public member_ `FVector SetVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Velocity that the actor will use if Mode == SetVelocity
- L53 _public member_ `float ClampVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Actor's Velocity will be clamped to this value if Mode == ClampVelocity
- L57 _public member_ `ELayeredMoveFinishVelocityMode FinishVelocityMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — What mode we want to happen when a Layered Move ends, see @ELayeredMoveFinishVelocityMode

#### struct `FLayeredMoveBase`  
`struct FLayeredMoveBase`  
_L74-176_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Base class for all layered moves
- L78 _public prototype_ `FLayeredMoveBase();`
- L79 _public prototype_ `virtual ~FLayeredMoveBase() = default;`
- L83 _public member_ `EMoveMixMode MixMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Determines how this object's movement contribution should be mixed with others
- L87 _public member_ `uint8 Priority;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Determines if this layered move should take priority over other layered moves when different moves have conflicting overrides - higher numbers taking precedent.
- L94 _public member_ `float DurationMs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — This move will expire after a set amount of time if > 0. If 0, it will be ticked only once, regardless of time step. It will need to be manually ended if < 0. Note: If changed after starting to a value beneath the current lifetime of the move, it will immediately finish (so if your move finishes early, setting this to 0 is equivalent to returning true from IsFinished())
- L98 _public member_ `double StartSimTimeMs;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = Mover)` — The simulation time this move first ticked (< 0 means it hasn't started yet)
- L102 _public member_ `FLayeredMoveFinishVelocitySettings FinishVelocitySettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Settings related to velocity applied to the actor after a layered move has finished
- L112 _public function_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const` — Check Layered Move for a gameplay tag. @param TagToFind			Tag to check on the Mover systems @param bExactMatch		If true, the tag has to be exactly present, if false then TagToFind will include its parent tags while matching @return True if the TagToFind was found
- L118 _public function_ `virtual void GetGameplayTags(FGameplayTagContainer& InOutTags) const` — Adds all gameplay tags currently active on this layered move to InOutTags.
- L121 _public prototype_ `void StartMove(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs);` — Kicks off this move, allowing any initialization to occur.
- L123 _public prototype_ `void StartMove_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime);` — Async version of the above
- L126 _public function_ `virtual void OnStart(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard)` — Called when this layered move starts.
- L128 _public function_ `virtual void OnStart_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime)` — Async version of the above
- L132 _public function_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove)` — TODO: consider whether MoverComp should just be part of FMoverTickStartData Generate a movement that will be combined with other sources
- L134 _public prototype_ `virtual bool GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove);` — Async version of the above
- L138 _public function_ `virtual bool SupportsAsync() const` — Returns true if this move supports async (worker thread) execution via GenerateMove_Async. Moves that return false will only have GenerateMove called on them, never GenerateMove_Async.
- L141 _public prototype_ `virtual bool IsFinished(double CurrentSimTimeMs) const;` — Runtime query whether this move is finished and can be destroyed. The default implementation is based on DurationMs.
- L144 _public prototype_ `void EndMove(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs);` — Ends this move, allowing any cleanup to occur.
- L146 _public prototype_ `void EndMove_Async(UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs);` — Async version of the above
- L149 _public function_ `virtual void OnEnd(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs)` — Called when this layered move ends.
- L151 _public function_ `virtual void OnEnd_Async(UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs)` — Async version of the above
- L154 _public prototype_ `virtual FLayeredMoveBase* Clone() const;` — @return newly allocated copy of this FLayeredMoveBase. Must be overridden by child classes
- L156 _public prototype_ `virtual void NetSerialize(FArchive& Ar);`
- L158 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;`
- L160 _public prototype_ `virtual FString ToSimpleString() const;`
- L162 _public function_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector)`
- L172 _public function_ `virtual bool IsNearlyEqualTo(const FLayeredMoveBase& Other) const` — Returns true if this move is considered nearly equal to Other for comparison purposes. Other is guaranteed to be the same struct type. Override in subclasses to allow tolerance-based equality instead of exact field matching (e.g. for server-side proposal validation in ChaosMover's Proposed auth style). Default: uses UScriptStruct's strict Identical test. If the struct's TStructOpsTypeTraits declares WithIdenticalViaEquality, CompareScriptStruct calls operator== on the struct; otherwise it compares each UPROPERTY field individually via reflection. Check the struct's TStructOpsTypeTraits specialization to know which path applies to a given subtype.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FLayeredMoveBase > : public TStructOpsTypeTraitsBase2< FLayeredMoveBase >`  
_L179-186_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMoveBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L182-185_

#### struct `FLayeredMoveGroup`  
`struct FLayeredMoveGroup`  
_L191-340_
- reflection: `USTRUCT(BlueprintType)`
- desc: A collection of layered moves affecting a movable actor
- L195 _public prototype_ `FLayeredMoveGroup();`
- L202 _public member_ `FVector ResidualVelocity;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover)` — If bApplyResidualVelocity is true this actors velocity will be set to this. Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings
- L204 _public prototype_ `void QueueLayeredMove(TSharedPtr<FLayeredMoveBase> Move);`
- L207 _public prototype_ `void CancelMovesByTag(FGameplayTag Tag, bool bRequireExactMatch=false);` — Schedule matching layered moves to be cancelled ASAP
- L209 _public function_ `bool HasAnyMoves() const`
- L213 _public function_ `template <typename MoveType UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveType>)> bool HasMove() const` — @return True if there is at least one layered move of MoveType that's either active or queued
- L219 _public prototype_ `TArray<TSharedPtr<FLayeredMoveBase>> GenerateActiveMoves(const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard);` — Generates active layered move list (by calling FlushMoveArrays) and returns the an array of all currently active layered moves
- L220 _public prototype_ `TArray<TSharedPtr<FLayeredMoveBase>> GenerateActiveMoves_Async(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard);`
- L223 _public prototype_ `void NetSerialize(FArchive& Ar, uint8 MaxNumMovesToSerialize = MAX_uint8);` — Serialize all moves and their states for this group
- L226 _public prototype_ `FLayeredMoveGroup& operator=(const FLayeredMoveGroup& Other);` — Copy operator - deep copy so it can be used for archiving/saving off moves
- L229 _public prototype_ `bool operator==(const FLayeredMoveGroup& Other) const;` — Comparison operator - needs matching LayeredMoves along with identical states in those structs
- L232 _public prototype_ `bool operator!=(const FLayeredMoveGroup& Other) const;` — Comparison operator
- L235 _public prototype_ `bool HasSameContents(const FLayeredMoveGroup& Other) const;` — Checks only whether there are matching LayeredMoves, but NOT necessarily identical states of each move
- L238 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector) const;` — Exposes references to GC system
- L241 _public prototype_ `FString ToSimpleString() const;` — Get a simplified string representation of this group. Typically for debugging.
- L246 _public prototype_ `void PrepareCVDMirror() const;` — Populate Debug_ActiveMoves from ActiveLayeredMoves so CVD can display them via reflection. Call just before tracing.
- L249 _public function_ `const TArray<TSharedPtr<FLayeredMoveBase>>& GetActiveMoves() const`
- L250 _public function_ `const TArray<TSharedPtr<FLayeredMoveBase>>& GetQueuedMoves() const`
- L254 _public function_ `template <typename MoveType UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveType>)> const MoveType* FindActiveMove() const` — Returns the first active layered move of the specified type, if one exists
- L258 _public prototype_ `const FLayeredMoveBase* FindActiveMove(const UScriptStruct* LayeredMoveStructType) const;`
- L262 _public function_ `template <typename MoveType UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveType>)> void ForEachActiveMoveOfType(TFunctionRef<void(MoveType&)> Func)` — Calls Func for every active move whose struct type is or derives from MoveType.
- L275 _public function_ `template <typename MoveType UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveType>)> void ForEachActiveMoveOfType(TFunctionRef<void(const MoveType&)> Func) const` — Const overload: calls Func for every active move whose struct type is or derives from MoveType.
- L288 _public function_ `template <typename MoveType UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveType>)> const MoveType* FindQueuedMove() const` — Returns the first queued layered move of the specified type, if one exists
- L292 _public prototype_ `const FLayeredMoveBase* FindQueuedMove(const UScriptStruct* LayeredMoveStructType) const;`
- L295 _public prototype_ `void ResetResidualVelocity();` — Resets residual velocity related settings
- L298 _public prototype_ `void Reset();` — Resets residual velocity and clears active and queued moves
- L302 _protected prototype_ `void FlushMoveArrays(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime, bool bIsAsync);` — Clears out any finished or invalid active moves and adds any queued moves to the active moves
- L305 _protected prototype_ `void GatherResidualVelocitySettings(const TSharedPtr<FLayeredMoveBase>& Move, bool& bResidualVelocityOverriden, bool& bClampVelocityOverriden);` — Helper function for gathering any residual velocity settings from layered moves that just ended
- L308 _protected prototype_ `static void NetSerializeLayeredMovesArray(FArchive& Ar, TArray< TSharedPtr<FLayeredMoveBase> >& LayeredMovesArray, uint8 MaxNumLayeredMovesToSerialize = MAX_uint8);` — Helper function for serializing array of root motion sources
- L311 _protected member_ `TArray< TSharedPtr<FLayeredMoveBase> > ActiveLayeredMoves;` — Layered moves currently active in this group
- L314 _protected member_ `TArray< TSharedPtr<FLayeredMoveBase> > QueuedLayeredMoves;` — Moves that are queued to become active next sim frame
- L321 _protected member_ `mutable TArray<FInstancedStruct> Debug_ActiveMoves;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Mover, DisplayName = "ActiveMoves")` — Reflected snapshot of ActiveLayeredMoves, populated just before CVD tracing in UChaosMoverSimulation::TraceMoverData. TSharedPtr arrays cannot be UPROPERTY so this mirror is the only way for CVD's reflection-based display to see active moves. mutable so it can be filled from a const reference during tracing.
- L324 _protected member_ `TArray<TPair<FGameplayTag, bool>> TagCancellationRequests;` — Used during simulation to cancel any moves that match a tag
- L332 _public member_ `float ResidualClamping;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover)` — Clamps an actors velocity to this value when a layered move ends. This expects Value >= 0. Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings
- L339 _public member_ `bool bApplyResidualVelocity;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover)` — If true ResidualVelocity will be the next velocity used for this actor Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLayeredMoveGroup> : public TStructOpsTypeTraitsBase2<FLayeredMoveGroup>`  
_L343-352_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMoveGroup>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L346-351_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`
- L184 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon17d5a5d50103`) — WithNetSerializer = true,
- L347 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon17d5a5d50203`) — Necessary so that TSharedPtr<FLayeredMoveBase> Data is copied around
- L349 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon17d5a5d50203`) — WithNetSerializer = true,
- L350 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon17d5a5d50203`)

### `Plugins/Experimental/Mover/Source/Mover/Public/LayeredMoveBase.h` (Public)


#### struct `FLayeredMoveActivationParams`  
`struct FLayeredMoveActivationParams`  
_L35-45_
- reflection: `USTRUCT(Blueprintable)`
- desc: Packaged params struct for initializing a corresponding FLayeredMoveInstancedData Allows BP to do "templated" move data creation. Optional in C++, where params can be forwarded to the FLayeredMoveInstancedData ctor directly The base class can also be used on any activation to just use default values
- L44 _public member_ `double DurationMs = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — This move will expire after a set amount of time if > 0. If 0, it will be ticked only once, regardless of time step. It will need to be manually ended if < 0. Note: If changed after starting to a value beneath the current lifetime of the move, it will immediately finish (so if your move finishes early, setting this to 0 is equivalent to returning true from IsFinished())

#### struct `FLayeredMoveInstancedData`  
`struct FLayeredMoveInstancedData`  
_L49-108_
- reflection: `USTRUCT(Blueprintable)`
- desc: Instanced data created and replicated for each activation of a layered move
- L54 _public prototype_ `USING_PARAMS(FLayeredMoveActivationParams);` — @todo DanH: If we're already using a macro, might as well put the boilerplate virtuals in here
- L56 _public function_ `FLayeredMoveInstancedData()`
- L57 _public prototype_ `virtual ~FLayeredMoveInstancedData() = default;`
- L59 _public prototype_ `bool operator==(const FLayeredMoveInstancedData& Other) const;` — Checks if
- L60 _public function_ `bool operator!=(const FLayeredMoveInstancedData& Other) const`
- L63 _public function_ `virtual FLayeredMoveInstancedData* Clone() const` — @return A newly allocated copy of this FLayeredMoveInstancedData. Must be overridden by child classes
- L66 _public function_ `virtual UScriptStruct* GetScriptStruct() const` — @return The UScriptStruct describing this struct. Must be overridden by child classes
- L69 _public prototype_ `virtual bool Equals(const FLayeredMoveInstancedData& OtherData) const;` — @return True if this move data is identical to OtherData. OtherData is guaranteed to be safe to cast to the implementing type.
- L79 _public function_ `virtual bool IsNearlyEqualTo(const FLayeredMoveInstancedData& Other) const` — Returns true if this data is considered nearly equal to Other for comparison purposes. Other is guaranteed to be the same struct type. Override in subclasses to allow tolerance-based equality instead of exact field matching (e.g. for server-side proposal validation in ChaosMover's Proposed auth style). Default: uses UScriptStruct's strict Identical test. If the struct's TStructOpsTypeTraits declares WithIdenticalViaEquality, CompareScriptStruct calls operator== on the struct; otherwise it compares each UPROPERTY field individually via reflection. Check the struct's TStructOpsTypeTraits specialization to know which path applies to a given subtype.
- L85 _public prototype_ `virtual void ActivateFromContext(const FLayeredMoveActivationParams* ActivationParams);` — Called when a queued layered move is activated. Provides an opportunity to initialize Layered MoveData
- L87 _public prototype_ `virtual void NetSerialize(FArchive& Ar);`
- L89 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector)`
- L92 _public function_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const` — Is this move considered to "have" a given gameplay tag?
- L94 _public function_ `double GetStartSimTimeMs() const`
- L101 _public member_ `double DurationMs = -1.f;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — This move will expire after a set amount of time if > 0. If 0, it will be ticked only once, regardless of time step. It will need to be manually ended if < 0. Note: If changed after starting to a value beneath the current lifetime of the move, it will immediately finish (so if your move finishes early, setting this to 0 is equivalent to returning true from IsFinished())
- L105 _public member_ `double StartSimTimeMs = -UE_BIG_NUMBER;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — The simulation time this move first ticked (< 0 means it hasn't started yet)

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLayeredMoveInstancedData> : public TStructOpsTypeTraitsBase2<FLayeredMoveInstancedData>`  
_L111-118_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMoveInstancedData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L114-117_

#### class `ULayeredMoveLogic`  
`class ULayeredMoveLogic : public UObject`  
_L133-261_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: Base class for all layered move logic that operates in tandem with instanced FLayeredMoveInstancedData. The logic object itself is not meant to ever be replicated, and a maximum of one instance of each logic class need ever exist on a given MoverComponent. Repeated and/or simultaneous activations of the same move on a component are represented, tracked, and replicated through instances of the FLayeredMoveInstancedData struct type that the logic class indicates in the ActiveMoveDataStructType property. The virtual methods on this class are invoked in a special and strict pattern that guarantees AccessExecutionMoveData will return the valid data instance relevant to that function execution. Refer to [Examples when they exist] for implementation examples
- L140 _public prototype_ `ULayeredMoveLogic();`
- L142 _public function_ `UScriptStruct* GetInstancedDataType() const`
- L144 _public function_ `const FLayeredMoveFinishVelocitySettings& GetFinishVelocitySettings() const`
- L145 _public function_ `EMoveMixMode GetMixMode() const`
- L146 _public function_ `uint8 GetPriority() const`
- L149 _public prototype_ `static bool ValidateMoveDataGetSet(const UObject* ObjectValidatingData, const ULayeredMoveLogic* MoveLogic, const FStructProperty* MoveDataProperty, const uint8* MoveDataPtr, FFrame& StackFrame);` — Helper function for validating move data when passing data and logic to/from BP
- L153 _public function_ `virtual bool SupportsAsync() const` — Returns true if this logic class supports async (worker-thread) execution via GenerateMove_Async. Subclasses that override GenerateMove_Async must also return true here.
- L163 _protected prototype_ `void OnStart(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard);` — `UFUNCTION(BlueprintNativeEvent)` — Called when this move is initially activated
- L167 _protected prototype_ `void OnEnd(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard);` — `UFUNCTION(BlueprintNativeEvent)` — Called when this move has ended
- L171 _protected prototype_ `bool GenerateMove(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, UPARAM(ref) const FMoverTickStartData& StartState, UPARAM(ref) FProposedMove& OutProposedMove);` — `UFUNCTION(BlueprintNativeEvent)` — Generate a movement that will be combined with other sources
- L175 _protected prototype_ `bool IsFinished(const FMoverTimeStep& TimeStep, const UMoverBlackboard* SimBlackboard);` — `UFUNCTION(BlueprintNativeEvent)` — @todo: Will need to cache whether to treat the instance data as const (i.e. whether to disregard & complain if someone tries to set the data in BP during that window)
- L177 _protected function_ `virtual void OnStart_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard)`
- L178 _protected function_ `virtual void OnEnd_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard)`
- L179 _protected function_ `virtual bool GenerateMove_Implementation(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, const FMoverTickStartData& StartState, FProposedMove& OutProposedMove)`
- L180 _protected prototype_ `virtual bool IsFinished_Implementation(const FMoverTimeStep& TimeStep, const UMoverBlackboard* SimBlackboard);`
- L184 _protected prototype_ `void OnStart_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime);` — `UFUNCTION(BlueprintNativeEvent)` — Async version of OnStart, called on the simulation worker thread when SupportsAsync() returns true
- L188 _protected prototype_ `bool GenerateMove_Async(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, UPARAM(ref) const FMoverTickStartData& StartState, UPARAM(ref) FProposedMove& OutProposedMove);` — `UFUNCTION(BlueprintNativeEvent)` — Async version of GenerateMove, called on the simulation worker thread when SupportsAsync() returns true
- L192 _protected prototype_ `void OnEnd_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime);` — `UFUNCTION(BlueprintNativeEvent)` — Async version of OnEnd, called on the simulation worker thread when SupportsAsync() returns true
- L194 _protected function_ `virtual void OnStart_Async_Implementation(UMoverBlackboard*, const FMoverTime&)`
- L195 _protected function_ `virtual bool GenerateMove_Async_Implementation(const FMoverTimeStep&, UMoverBlackboard*, const FMoverTickStartData&, FProposedMove&)`
- L196 _protected function_ `virtual void OnEnd_Async_Implementation(UMoverBlackboard*, const FMoverTime&)`
- L200 _protected function_ `template <typename MoveDataT = FLayeredMoveInstancedData UE_REQUIRES(std::is_base_of_v<FLayeredMoveInstancedData, MoveDataT>)> MoveDataT& AccessExecutionMoveData() const` — Accessor to the FLayeredMoveInstancedData established for the execution of a virtual move logic function
- L220 _protected prototype_ `static bool K2_GetActiveMoveData(ULayeredMoveLogic* MoveLogic, FLayeredMoveInstancedData& OutMoveData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "Mover | Layered Move", DisplayName = "Get Active Move Data", meta = (BlueprintProtected, BlueprintInternalUseOnly, CustomStructureParam = "OutMoveData", DefaultToSelf = "MoveLogic"))` — Gets active move data that is tied to this active move. Use SetActiveMoveData to write active move data. Note: Make sure break node is the correct data type specified by the layered move logic.
- L228 _protected prototype_ `static void K2_SetActiveMoveData(ULayeredMoveLogic* MoveLogic, const FLayeredMoveInstancedData& OutMoveData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "Mover | Layered Move", DisplayName = "Set Active Move Data", meta = (BlueprintProtected, BlueprintInternalUseOnly, CustomStructureParam = "OutMoveData", DefaultToSelf = "MoveLogic"))` — Sets active move data that is tied to this active move. Use GetActiveMoveData to read current active move data. Note: Make sure make node is the correct data type specified by the layered move logic.
- L236 _protected member_ `double DefaultDurationMs = -1.f;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — This move will expire after a set amount of time if > 0. If 0, it will be ticked only once, regardless of time step. It will need to be manually ended if < 0. Note: If changed after starting to a value beneath the current lifetime of the move, it will immediately finish (so if your move finishes early, setting this to 0 is equivalent to returning true from IsFinished())
- L240 _protected member_ `EMoveMixMode MixMode = EMoveMixMode::AdditiveVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mover)` — Determines how this object's movement contribution should be mixed with others
- L244 _protected member_ `uint8 Priority = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mover)` — Determines if this layered move should take priority over other layered moves when different moves have conflicting overrides - higher numbers taking precedent.
- L249 _protected member_ `FLayeredMoveFinishVelocitySettings FinishVelocitySettings;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mover)` — Settings related to velocity applied to the actor after the move has finished
- L253 _protected member_ `TObjectPtr<UScriptStruct> InstancedDataStructType;` — `UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Mover, meta=(MetaStruct="/Script/Mover.LayeredMoveInstancedData"))` — @todo DanH: Fail validation if this isn't set or isn't an FLayeredMoveInstancedData
- L260 _private member_ `TSharedPtr<FLayeredMoveInstancedData> CurrentInstancedData;` — The FLayeredMoveInstancedData provided to each of the base virtual move functions, valid only for the duration a single virtual function execution. Direct access is only for internal plumbing - use AccessExecutionMoveData() in virtuals to obtain a typed reference to this.

#### struct `FLayeredMoveInstance`  
`struct FLayeredMoveInstance`  
_L268-332_
- reflection: `USTRUCT()`
- desc: Wrapper to encapsulate the split implementation of a move between a stateless ULayeredMoveLogic* object and an instance of FLayeredMoveInstancedData Those two pieces, in tandem, represent a "whole" functional Layered Move.
- L272 _public prototype_ `FLayeredMoveInstance();`
- L273 _public prototype_ `FLayeredMoveInstance(const FLayeredMoveInstance& OtherLayeredMoveInstance);`
- L274 _public prototype_ `FLayeredMoveInstance(const TSharedRef<FLayeredMoveInstancedData>& InMoveData, ULayeredMoveLogic* InMoveLogic = nullptr);`
- L277 _public function_ `bool operator==(const TSubclassOf<ULayeredMoveLogic>& LogicClass) const` — TArray::FindByKey() enablers
- L278 _public function_ `bool operator==(const UScriptStruct* MoveDataType) const`
- L280 _public function_ `bool HasLogic() const`
- L281 _public function_ `const UClass* GetLogicClass() const`
- L283 _public prototype_ `void StartMove(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard) const;`
- L284 _public prototype_ `bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) const;`
- L285 _public prototype_ `void EndMove(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard) const;`
- L286 _public prototype_ `bool IsFinished(const FMoverTimeStep& TimeStep, const UMoverBlackboard* SimBlackboard) const;`
- L289 _public prototype_ `void StartMove_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime) const;` — Async equivalents, safe to call from the simulation worker thread when the logic SupportsAsync()
- L290 _public prototype_ `bool GenerateMove_Async(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) const;`
- L291 _public prototype_ `void EndMove_Async(UMoverBlackboard* SimBlackboard, const FMoverTime& SimTime) const;`
- L294 _public function_ `ULayeredMoveLogic* GetLogic() const` — Returns the logic object; used by GenerateActiveMoves_Async to filter by SupportsAsync()
- L296 _public prototype_ `const FLayeredMoveFinishVelocitySettings& GetFinishVelocitySettings() const;`
- L297 _public prototype_ `EMoveMixMode GetMixMode() const;`
- L298 _public function_ `uint8 GetPriority() const`
- L299 _public function_ `double GetStartingTimeMs() const`
- L300 _public function_ `bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const`
- L302 _public prototype_ `FLayeredMoveInstance Clone() const;`
- L303 _public function_ `UScriptStruct* GetDataStructType() const`
- L304 _public function_ `const FLayeredMoveInstancedData* GetMoveData() const`
- L305 _public function_ `void AddReferencedObjects(FReferenceCollector& Collector) const`
- L307 _public prototype_ `void NetSerialize(FArchive& Ar);`
- L309 _public prototype_ `const UClass* GetSerializedMoveLogicClass() const;`
- L317 _public prototype_ `bool PopulateMissingActiveMoveLogic(const TArray<TObjectPtr<ULayeredMoveLogic>>& RegisteredMoves);` — This function populates the MoveLogic reference of ActiveMoves that don't have any logic classes. This is necessary as active move data received from NetSerialize doesn't necessarily have the Logic class it was activated with. Note: Currently we are NetSerializing the MoveLogic class so that we can then populate Logic from using the registered move array on the MoverComponent but eventually we should use a ID mapping or something better to avoid serializing the MoveLogic class.
- L320 _private member_ `TSharedPtr<FLayeredMoveInstancedData> InstanceMoveData;`
- L327 _private member_ `TSubclassOf<ULayeredMoveLogic> MoveLogicClassType;` — `UPROPERTY(Transient)` — Is used in PopulateMissingActiveMoveLogic to help populate logic classes in active moves that were NetSerialized since MoveLogic isn't NetSerialized TODO: Eventually replace this with some ID/Mapping system so we can NetSerialize that instead of a full UClass
- L331 _private member_ `TObjectPtr<ULayeredMoveLogic> MoveLogic;` — `UPROPERTY(Transient)` — @todo DanH: This exists on the PT for the chaos mover - can/should this still be a UProperty TObjectPtr?

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLayeredMoveInstance> : public TStructOpsTypeTraitsBase2<FLayeredMoveInstance>`  
_L335-342_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMoveInstance>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L338-341_

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MOVER_API`
- L19 _macro_ `#define USING_PARAMS(ActivationParamsClass) using ActivationParamsType = ActivationParamsClass;`
- L20 _macro_ `#define USING_MOVE_DATA(MoveDataClass) using MoveDataType = MoveDataClass;`
- L116 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone197ccf00103`) — WithNetSerializer = true,
- L340 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone197ccf00203`) — WithNetSerializer = true,

### `Plugins/Experimental/Mover/Source/Mover/Public/LayeredMoveGroup.h` (Public)


#### struct `FLayeredMoveInstanceGroup`  
`struct FLayeredMoveInstanceGroup`  
_L26-144_
- reflection: `USTRUCT(BlueprintType)`
- desc: The group of information about currently active and queued moves. This replicates info for FLayeredMoveInstancedData only - it is expected that the corresponding ULayeredMoveLogic is already registered with the mover component.
- L30 _public prototype_ `FLayeredMoveInstanceGroup();`
- L31 _public prototype_ `FLayeredMoveInstanceGroup& operator=(const FLayeredMoveInstanceGroup& Other);`
- L32 _public prototype_ `bool operator==(const FLayeredMoveInstanceGroup& Other) const;`
- L33 _public function_ `bool operator!=(const FLayeredMoveInstanceGroup& Other) const`
- L36 _public prototype_ `bool HasSameContents(const FLayeredMoveInstanceGroup& Other) const;` — Checks only whether there are matching LayeredMoves, but NOT necessarily identical states of each move
- L38 _public prototype_ `bool GenerateMixedMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UMovementMixer& MovementMixer, UMoverBlackboard* SimBlackboard, FProposedMove& OutMixedMove);`
- L39 _public prototype_ `void ApplyResidualVelocity(FProposedMove& InOutProposedMove);`
- L40 _public prototype_ `void NetSerialize(FArchive& Ar, uint8 MaxNumMovesToSerialize = MAX_uint8);`
- L41 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector) const;`
- L42 _public prototype_ `void ResetResidualVelocity();`
- L43 _public prototype_ `void Reset();`
- L49 _public prototype_ `void PopulateMissingActiveMoveLogic(const TArray<TObjectPtr<ULayeredMoveLogic>>& RegisteredMoves);` — Loops through all Queued and Active moves and populates any missing MoveLogic using FLayeredMoveInstance::PopulateMissingActiveMoveLogic. See FLayeredMoveInstance::PopulateMissingActiveMoveLogic function for more details.
- L52 _public prototype_ `void QueueLayeredMove(const TSharedPtr<FLayeredMoveInstance>& Move);` — Adds the active move to the queued array of the move group
- L55 _public function_ `bool HasAnyMoves() const` — @return True if there are any active or queued moves in this group
- L59 _public function_ `template <typename MoveElementT UE_REQUIRES(std::is_base_of_v<FLayeredMoveInstancedData, MoveElementT> || std::is_base_of_v<ULayeredMoveLogic, MoveElementT>)> bool HasMove() const` — @return True if there is at least one layered move that's either active or queued and is associated with the provided logic or data type
- L65 _public prototype_ `FString ToSimpleString() const;` — Get a simplified string representation of this group. Typically for debugging.
- L69 _public function_ `template <typename MoveLogicT = ULayeredMoveLogic UE_REQUIRES(std::is_base_of_v<ULayeredMoveLogic, MoveLogicT>)> const FLayeredMoveInstance* FindActiveMove(TSubclassOf<ULayeredMoveLogic> MoveLogicClass = MoveLogicT::StaticClass()) const` — Returns the first active layered move associated with logic of the specified type, if one exists
- L76 _public function_ `template <typename MoveDataT = FLayeredMoveInstancedData UE_REQUIRES(std::is_base_of_v<FLayeredMoveInstancedData, MoveDataT>)> const FLayeredMoveInstance* FindActiveMove(const UScriptStruct* MoveDataType = MoveDataT::StaticStruct()) const` — Returns the first active layered move using data of the specified type, if one exists
- L83 _public function_ `template <typename MoveLogicT = ULayeredMoveLogic UE_REQUIRES(std::is_base_of_v<ULayeredMoveLogic, MoveLogicT>)> const FLayeredMoveInstance* FindQueuedMove(TSubclassOf<ULayeredMoveLogic> MoveLogicClass = MoveLogicT::StaticClass()) const` — Returns the first queued layered move associated with logic of the specified type, if one exists
- L90 _public function_ `template <typename MoveDataT = FLayeredMoveInstancedData UE_REQUIRES(std::is_base_of_v<FLayeredMoveInstancedData, MoveDataT>)> const FLayeredMoveInstance* FindQueuedMove(const UScriptStruct* MoveDataType = MoveDataT::StaticStruct()) const` — Returns the first queued layered move using data of the specified type, if one exists
- L96 _public prototype_ `void CancelMovesByTag(FGameplayTag Tag, bool bRequireExactMatch);` — Cancel any active or queued moves with a matching tag
- L99 _public prototype_ `void FlushMoveArrays(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard, bool bIsAsync = false);` — Clears out any finished or invalid active moves and adds any queued moves to the active moves
- L102 _public prototype_ `TArray<TSharedPtr<FLayeredMoveInstance>> GenerateActiveMoves_Async(const FMoverTimeStep& TimeStep, UMoverBlackboard* SimBlackboard);` — Flushes move arrays using async start/end calls, then returns only moves whose logic SupportsAsync()
- L106 _protected prototype_ `void ProcessFinishedMove(const FLayeredMoveInstance& Move, bool& bResidualVelocityOverriden, bool& bClampVelocityOverriden);` — Helper function for gathering any residual velocity settings from layered moves that just ended
- L109 _protected member_ `TArray<TSharedPtr<FLayeredMoveInstance>> ActiveMoves;` — Moves that are currently active in this group
- L112 _protected member_ `TArray<TSharedPtr<FLayeredMoveInstance>> QueuedMoves;` — Moves that are queued to become active next sim frame
- L115 _private prototype_ `const FLayeredMoveInstance* PrivateFindActiveMove(const TSubclassOf<ULayeredMoveLogic>& MoveLogicClass) const;`
- L116 _private prototype_ `const FLayeredMoveInstance* PrivateFindActiveMove(const UScriptStruct* MoveDataType) const;`
- L117 _private prototype_ `const FLayeredMoveInstance* PrivateFindQueuedMove(const TSubclassOf<ULayeredMoveLogic>& MoveLogicClass) const;`
- L118 _private prototype_ `const FLayeredMoveInstance* PrivateFindQueuedMove(const UScriptStruct* MoveDataType) const;`
- L126 _private member_ `float ResidualClamping;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover, meta = (AllowPrivateAccess))` — Clamps an actors velocity to this value when a layered move ends. This expects Value >= 0. Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings
- L133 _private member_ `bool bApplyResidualVelocity;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover, meta = (AllowPrivateAccess))` — If true ResidualVelocity will be the next velocity used for this actor Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings
- L140 _private member_ `FVector ResidualVelocity;` — `UPROPERTY(NotReplicated, VisibleAnywhere, BlueprintReadOnly, Category = Mover, meta = (AllowPrivateAccess))` — If bApplyResidualVelocity is true this actors velocity will be set to this. Note: This is set automatically when a layered move has ended based off of end velocity settings - it is not meant to be set by the user see @FLayeredMoveFinishVelocitySettings
- L143 _private member_ `TArray<TPair<FGameplayTag, bool>> TagCancellationRequests;` — Used during simulation to cancel any moves that match a tag

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLayeredMoveInstanceGroup> : public TStructOpsTypeTraitsBase2<FLayeredMoveInstanceGroup>`  
_L147-156_
- inherits: `TStructOpsTypeTraitsBase2<FLayeredMoveInstanceGroup>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L150-155_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L151 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonbcddc3220103`)
- L153 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonbcddc3220103`) — WithNetSerializer = true,
- L154 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anonbcddc3220103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MotionWarpingMoverAdapter.h` (Public)


#### class `UMotionWarpingMoverAdapter`  
`class UMotionWarpingMoverAdapter : public UMotionWarpingBaseAdapter`  
_L14-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMotionWarpingBaseAdapter`
- L19 _public prototype_ `virtual void BeginDestroy() override;`
- L21 _public prototype_ `void SetMoverComp(UMoverComponent* InMoverComp);`
- L23 _public prototype_ `virtual AActor* GetActor() const override;`
- L24 _public prototype_ `virtual USkeletalMeshComponent* GetMesh() const override;`
- L25 _public prototype_ `virtual FVector GetVisualRootLocation() const override;`
- L26 _public prototype_ `virtual FVector GetBaseVisualTranslationOffset() const override;`
- L27 _public prototype_ `virtual FQuat GetBaseVisualRotationOffset() const override;`
- L31 _private prototype_ `FTransform WarpLocalRootMotionOnMoverComp(const FTransform& LocalRootMotionTransform, float DeltaSeconds, const FMotionWarpingUpdateContext* OptionalWarpingContext);` — This is called when our Mover actor wants to warp local motion, and passes the responsibility onto the warping component
- L34 _private member_ `TObjectPtr<UMoverComponent> TargetMoverComp;` — `UPROPERTY(Transient, DuplicateTransient)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/AirMovementUtils.h` (Public)


#### struct `FFreeMoveParams`  
`struct FFreeMoveParams`  
_L17-62_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for controlled free movement function
- L22 _public member_ `EMoveInputType MoveInputType = EMoveInputType::DirectionalIntent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L25 _public member_ `FVector MoveInput = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L28 _public member_ `FRotator OrientationIntent = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L31 _public member_ `FVector PriorVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L34 _public member_ `FRotator PriorOrientation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L37 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L40 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L43 _public member_ `float Deceleration = 8000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L46 _public member_ `float TurningBoost = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L49 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L52 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L55 _public member_ `float Friction = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L58 _public member_ `FQuat WorldToGravityQuat = FQuat::Identity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L61 _public member_ `bool bUseAccelerationForVelocityMove = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### class `UAirMovementUtils`  
`class UAirMovementUtils : public UBlueprintFunctionLibrary`  
_L68-106_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: AirMovementUtils: a collection of stateless static BP-accessible functions for a variety of air movement-related operations
- L75 _public prototype_ `static FProposedMove ComputeControlledFreeMove(const FFreeMoveParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Generate a new movement based on move/orientation intents and the prior state, unconstrained like when flying
- L79 _public prototype_ `static bool IsValidLandingSpot(const FMovingComponentSet& MovingComps, const FVector& Location, const FHitResult& Hit, const FFloorCheckSettings& FloorCheckSettings, UPARAM(Ref) FFloorCheckResult& OutFloorResult);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Checks if a hit result represents a walkable location that an actor can land on
- L82 _public prototype_ `static bool IsValidLandingSpot(const FMovingComponentSet& MovingComps, const FVector& Location, const FHitResult& Hit, float FloorSweepDistance, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, UPARAM(Ref) FFloorCheckResult& OutFloorResult, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`
- L86 _public prototype_ `static float TryMoveToFallAlongSurface(const FMovingComponentSet& MovingComps, const FVector& Delta, float PctOfDeltaToMove, const FQuat Rotation, const FVector& Normal, UPARAM(Ref) FHitResult& Hit, bool bHandleImpact, const FFloorCheckSettings& FloorCheckSettings, UPARAM(Ref) FFloorCheckResult& OutFloorResult, UPARAM(Ref) FMovementRecord& MoveRecord);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Attempts to move a component along a surface, while checking for landing on a walkable surface. Intended for use while falling. Returns the percent of time applied, with 0.0 meaning no movement occurred.
- L89 _public prototype_ `static float TryMoveToFallAlongSurface(const FMovingComponentSet& MovingComps, const FVector& Delta, float PctOfDeltaToMove, const FQuat Rotation, const FVector& Normal, UPARAM(Ref) FHitResult& Hit, bool bHandleImpact, float FloorSweepDistance, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, UPARAM(Ref) FFloorCheckResult& OutFloorResult, UPARAM(Ref) FMovementRecord& MoveRecord, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`
- L101 _public prototype_ `static float TestFallingMoveAlongHitSurface(const FMovingComponentSet& MovingComps, const FVector& OriginalMoveDelta, const FVector& LocationAtHit, const FQuat& TargetRotation, bool bHandleImpact, const FFloorCheckSettings& FloorCheckSettings, UPARAM(Ref) FHitResult& InOutHit, UPARAM(Ref) FFloorCheckResult& OutFloorResult, UPARAM(Ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests potential movement of a component falling/sliding along a surface, while checking for landing on a walkable surface. Intended for use while falling. Modifies InOutHit with final movement hit data Sets OutFloorResult with any found walkable surface info Appends to InOutMoveRecord with any movement substeps Returns the percent of time applied, with 0.0 meaning no movement would occur.
- L104 _public prototype_ `static float TestFallingMoveAlongHitSurface(const FMovingComponentSet& MovingComps, const FVector& OriginalMoveDelta, const FVector& LocationAtHit, const FQuat& TargetRotation, bool bHandleImpact, float FloorSweepDistance, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, UPARAM(Ref) FHitResult& InOutHit, UPARAM(Ref) FFloorCheckResult& OutFloorResult, UPARAM(Ref) FMovementRecord& InOutMoveRecord, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/AsyncMovementUtils.h` (Public)


#### class `UAsyncMovementUtils`  
`class UAsyncMovementUtils : public UBlueprintFunctionLibrary`  
_L24-74_
- reflection: `UCLASS(MinimalAPI, Experimental)`
- inherits: `UBlueprintFunctionLibrary`
- desc: AsyncMovementUtils: a collection of stateless static BP-accessible functions focused on testing potential movements in a threadsafe manner without actually causing immediate changes.
- L35 _public prototype_ `static bool TestDepenetratingMove(const FMovingComponentSet& MovingComps, const FVector& StartLocation, const FVector& TargetLocation, const FQuat& StartRotation, const FQuat& TargetRotation, bool bShouldSweep, FHitResult& OutHit, UPARAM(ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests potential movement of a component without actually moving it, taking penetration resolution issues into account first. Returns true if any movement was possible Modifies OutHit with final movement hit data Appends to InOutMoveRecord with any movement substeps
- L42 _public prototype_ `static bool TestDepenetratingMove(const FMovingComponentSet& MovingComps, const FVector& StartLocation, const FVector& TargetLocation, const FQuat& StartRotation, const FQuat& TargetRotation, bool bShouldSweep, FMoverCollisionParams& CollisionParams, FHitResult& OutHit, FMovementRecord& InOutMoveRecord);` — Tests potential movement of a component without actually moving it, taking penetration resolution issues into account first.  Relies on CollisionParams to describe the query. Returns true if any movement was possible Modifies OutHit with final movement hit data Appends to InOutMoveRecord with any movement substeps
- L50 _public prototype_ `static float TestSlidingMoveAlongHitSurface(const FMovingComponentSet& MovingComps, const FVector& OriginalMoveDelta, const FVector& LocationAtHit, const FQuat& TargetRotation, UPARAM(ref) FHitResult& InOutHit, UPARAM(ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests potential movement of a component sliding along a surface, without actually moving it. Returns the percent of time applied, with 0.0 meaning no movement would occur. Modifies InOutHit with final movement hit data Appends to InOutMoveRecord with any movement substeps
- L58 _public prototype_ `static float TestSlidingMoveAlongHitSurface(const FMovingComponentSet& MovingComps, const FVector& OriginalMoveDelta, const FVector& LocationAtHit, const FQuat& TargetRotation, FMoverCollisionParams& CollisionParams, FHitResult& InOutHit, FMovementRecord& InOutMoveRecord);` — Tests potential movement of a component sliding along a surface, without actually moving it. Relies on CollisionParams to describe the query. Returns the percent of time applied, with 0.0 meaning no movement would occur. Modifies InOutHit with final movement hit data Appends to InOutMoveRecord with any movement substeps
- L64 _public prototype_ `static bool FindMoveToResolveInitialPenetration_Internal(const FMovingComponentSet& MovingComps, const FVector& StartLocation, const FQuat& StartRotation, const FHitResult& PenetratingHit, FMoverCollisionParams& CollisionParams, FVector& OutAdjustmentDelta);` — Attempts to find a move that would resolve an initially penetrating blockage. Returns true if an adjustment was found. The adjustment will be in OutAdjustmentDelta.
- L71 _public prototype_ `static bool TestMoveComponent_Internal(const FMovingComponentSet& MovingComps, const FVector& StartLocation, const FVector& TargetLocation, const FQuat& StartRotation, const FQuat& TargetRotation, bool bShouldSweep, FMoverCollisionParams& CollisionParams, FHitResult& OutHit);` — Tests a move of a component without actually moving it. Returns true if any motion could occur. Detailed blocking hit results are written to OutHit. If not sweeping, full movement will always be allowed even if new blocking overlaps would occur.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/BasedMovementUtils.h` (Public)


#### struct `FRelativeBaseInfo`  
`struct FRelativeBaseInfo`  
_L18-60_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about the object a Mover actor is basing its movement on, such as when standing on a moving platform
- L24 _public member_ `TWeakObjectPtr<UPrimitiveComponent> MovementBase = nullptr;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Mover")` — Component we are moving relative to
- L28 _public member_ `FName BoneName = NAME_None;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mover")` — Bone name on component, for skeletal meshes. NAME_None if not a skeletal mesh or if bone is invalid.
- L32 _public member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mover")` — Last captured worldspace location of MovementBase / Bone
- L36 _public member_ `FQuat Rotation = FQuat::Identity;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mover")` — Last captured worldspace orientation of MovementBase / Bone
- L40 _public member_ `FVector ContactLocalPosition = FVector::ZeroVector;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mover")` — Last captured location of the tethering point where the Mover actor is "attached", relative to the base.
- L44 _public member_ `FVector WorldspaceOffsetFromContactPos = FVector::ZeroVector;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Mover")` — Last captured offset of the Mover actor from contact location, in world space.
- L49 _public prototype_ `void Clear();`
- L51 _public prototype_ `bool HasRelativeInfo() const;`
- L52 _public prototype_ `bool UsesSameBase(const FRelativeBaseInfo& Other) const;`
- L53 _public prototype_ `bool UsesSameBase(const UPrimitiveComponent* OtherComp, FName OtherBoneName=NAME_None) const;`
- L55 _public prototype_ `void SetFromFloorResult(const FFloorCheckResult& FloorTestResult, const FVector ObjectWorldLocation, const FVector UpDir);`
- L57 _public prototype_ `void UpdateToLatestBaseTransform();`
- L59 _public prototype_ `FString ToString() const;`

#### class `UBasedMovementUtils`  
`class UBasedMovementUtils : public UBlueprintFunctionLibrary`  
_L67-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: MovementBaseUtils: a collection of stateless static BP-accessible functions for based movement
- L74 _public prototype_ `static bool IsADynamicBase(const UPrimitiveComponent* MovementBase);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Determine whether MovementBase can possibly move.
- L78 _public prototype_ `static bool IsBaseSimulatingPhysics(const UPrimitiveComponent* MovementBase);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Determine whether MovementBase's movement is performed via physics.
- L82 _public prototype_ `static bool GetMovementBaseTransform(const UPrimitiveComponent* MovementBase, const FName BoneName, FVector& OutLocation, FQuat& OutQuat);` — `UFUNCTION(BlueprintCallable, Category="Mover/MovementBases")` — Get the transform (local-to-world) for the given MovementBase, optionally at the location of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone.
- L86 _public prototype_ `static bool GetMovementBaseVelocity(const UPrimitiveComponent* MovementBase, FVector& OutWorldVelocity);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases", meta=(ReturnDisplayName = "Did Get Velocity"))` — Get the velocity (world space) for the given MovementBase. Returns false and sets OutWorldVelocity to zero if MovementBase/Bone isn't valid.
- L90 _public prototype_ `static bool GetMovementBaseVelocityAtPoint(const UPrimitiveComponent* MovementBase, const FVector& WorldPoint, FVector& OutWorldVelocity);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases", meta=(ReturnDisplayName = "Did Get Velocity"))` — Get the velocity (world space) for the given MovementBase at a given point, taking its translation and angular velocity into account. Returns false and sets OutWorldVelocity to zero if MovementBase/Bone isn't valid.
- L94 _public prototype_ `static bool TransformBasedLocationToWorld(const UPrimitiveComponent* MovementBase, const FName BoneName, FVector LocalLocation, FVector& OutLocationWorldSpace);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local location to a world location for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L98 _public prototype_ `static bool TransformWorldLocationToBased(const UPrimitiveComponent* MovementBase, const FName BoneName, FVector WorldSpaceLocation, FVector& OutLocalLocation);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world location to a local location for a given MovementBase, optionally at the location of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L102 _public prototype_ `static bool TransformBasedDirectionToWorld(const UPrimitiveComponent* MovementBase, const FName BoneName, FVector LocalDirection, FVector& OutDirectionWorldSpace);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local direction to a world direction for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L106 _public prototype_ `static bool TransformWorldDirectionToBased(const UPrimitiveComponent* MovementBase, const FName BoneName, FVector WorldSpaceDirection, FVector& OutLocalDirection);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world direction to a local direction for a given MovementBase, optionally relative to the orientation of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L110 _public prototype_ `static bool TransformBasedRotatorToWorld(const UPrimitiveComponent* MovementBase, const FName BoneName, FRotator LocalRotator, FRotator& OutWorldSpaceRotator);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local rotator to world space for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L114 _public prototype_ `static bool TransformWorldRotatorToBased(const UPrimitiveComponent* MovementBase, const FName BoneName, FRotator WorldSpaceRotator, FRotator& OutLocalRotator);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world space rotator to a local rotator for a given MovementBase, optionally relative to the orientation of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L118 _public prototype_ `static void TransformLocationToWorld(FVector BasePos, FQuat BaseQuat, FVector LocalLocation, FVector& OutLocationWorldSpace);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local location to a world location for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L122 _public prototype_ `static void TransformLocationToLocal(FVector BasePos, FQuat BaseQuat, FVector WorldSpaceLocation, FVector& OutLocalLocation);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world location to a local location for a given MovementBase, optionally at the location of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L126 _public prototype_ `static void TransformDirectionToWorld(FQuat BaseQuat, FVector LocalDirection, FVector& OutDirectionWorldSpace);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local direction to a world direction for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L130 _public prototype_ `static void TransformDirectionToLocal(FQuat BaseQuat, FVector WorldSpaceDirection, FVector& OutLocalDirection);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world direction to a local direction for a given MovementBase, optionally relative to the orientation of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L134 _public prototype_ `static void TransformRotatorToWorld(FQuat BaseQuat, FRotator LocalRotator, FRotator& OutWorldSpaceRotator);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a local rotator to world space for a given MovementBase. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L138 _public prototype_ `static void TransformRotatorToLocal(FQuat BaseQuat, FRotator WorldSpaceRotator, FRotator& OutLocalRotator);` — `UFUNCTION(BlueprintCallable, Category = "Mover/MovementBases")` — Convert a world space rotator to a local rotator for a given MovementBase, optionally relative to the orientation of a bone. Returns false if MovementBase is nullptr, or if BoneName is not a valid bone. Scaling is ignored.
- L141 _public prototype_ `static FRelativeBaseInfo ApplyMovementBaseChange(UMoverComponent* TargetMoverComp, const FRelativeBaseInfo& RelativeBaseInfo, bool bIgnoreBaseRotation);` — Apply a sweeping movement to attempt to follow a movement base that we're moving relative to. This is typically called during movement simulation.
- L144 _public prototype_ `static void AddTickDependency(FTickFunction& BasedObjectTick, UPrimitiveComponent* NewBase);` — Makes it so BasedObjectTick ticks after NewBase's actor ticking
- L147 _public prototype_ `static void RemoveTickDependency(FTickFunction& BasedObjectTick, UPrimitiveComponent* OldBase);` — Removes ticking dependency of BasedObjectTick on OldBase
- L150 _public prototype_ `static void UpdateSimpleBasedMovement(UMoverComponent* TargetMoverComp);` — Attempts to move the actor to keep up with its base's movement using a simple sweep. This function is not intended to be called during a Mover actor's simulation tick.

#### struct `FMoverDynamicBasedMovementTickFunction`  
`struct FMoverDynamicBasedMovementTickFunction : public FTickFunction`  
_L158-180_
- reflection: `USTRUCT()`
- inherits: `FTickFunction`
- desc: Tick function used to perform based movement at dynamic times throughout the world update time, typically out-of-band with the movement simulation
- L163 _public member_ `UMoverComponent* TargetMoverComp;` — MoverComponent that is the target of this tick
- L166 _public member_ `bool bAutoDisableAfterTick = false;` — If true, this tick function will self-disable after running
- L175 _public prototype_ `virtual void ExecuteTick(float DeltaTime, enum ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent) override;` — Abstract function actually execute the tick. @param DeltaTime - frame time to advance, in seconds @param TickType - kind of tick for this frame @param CurrentThread - thread we are executing on, useful to pass along as new tasks are created @param MyCompletionGraphEvent - completion event for this task. Useful for holding the completion of this task until certain child tasks are complete.
- L177 _public prototype_ `virtual FString DiagnosticMessage() override;` — Abstract function to describe this tick. Used to print messages about illegal cycles in the dependency graph
- L179 _public prototype_ `virtual FName DiagnosticContext(bool bDetailed) override;` — Function used to describe this tick for active tick reporting.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverDynamicBasedMovementTickFunction> : public TStructOpsTypeTraitsBase2<FMoverDynamicBasedMovementTickFunction>`  
_L183-189_
- inherits: `TStructOpsTypeTraitsBase2<FMoverDynamicBasedMovementTickFunction>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L186-188_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`
- L187 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anona974abee0103`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/ConstrainedMoveUtils.h` (Public)


#### struct `FPlanarConstraint`  
`struct FPlanarConstraint`  
_L15-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates info about constraining movement to a plane, such as in a side-scroller
- L21 _public member_ `bool bConstrainToPlane = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanarMovement)` — If true, movement will be constrained to a plane.
- L29 _public member_ `FVector PlaneConstraintNormal = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanarMovement, meta = (editcondition = bConstrainToPlane))` — The normal or axis of the plane that constrains movement, if bConstrainToPlane is enabled. If for example you wanted to constrain movement to the X-Z plane (so that Y cannot change), the normal would be set to X=0 Y=1 Z=0. It is normalized once the component is registered with the game world.
- L33 _public member_ `FVector PlaneConstraintOrigin = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlanarMovement, meta = (editcondition = bConstrainToPlane))` — The origin of the plane that constrains movement, if plane constraint is enabled.

#### class `UPlanarConstraintUtils`  
`class UPlanarConstraintUtils : public UBlueprintFunctionLibrary`  
_L42-77_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: PlanarConstraintUtils: a collection of stateless static BP-accessible functions for working with planar constraints
- L49 _public prototype_ `static void SetPlanarConstraintEnabled(UPARAM(ref) FPlanarConstraint& Constraint, bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Sets whether or not the constraint is enabled
- L57 _public prototype_ `static void SetPlanarConstraintNormal(UPARAM(ref) FPlanarConstraint& Constraint, FVector PlaneNormal);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Sets the normal of the plane that constrains movement, enforced if the plane constraint is enabled. @param PlaneNormal	The normal of the plane. If non-zero in length, it will be normalized.
- L61 _public prototype_ `static void SetPlaneConstraintOrigin(UPARAM(ref) FPlanarConstraint& Constraint, FVector PlaneOrigin);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Sets the origin of the plane that constrains movement, enforced if the plane constraint is enabled.
- L67 _public prototype_ `static FVector ConstrainDirectionToPlane(const FPlanarConstraint& Constraint, FVector Direction, bool bMaintainMagnitude=false);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Constrains a direction to be on the plane, if enabled
- L71 _public prototype_ `static FVector ConstrainLocationToPlane(const FPlanarConstraint& Constraint, FVector Location);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Constrains a location to be on the plane, if enabled
- L75 _public prototype_ `static FVector ConstrainNormalToPlane(const FPlanarConstraint& Constraint, FVector Normal);` — `UFUNCTION(BlueprintCallable, Category = "Mover|PlanarConstraint")` — Constrains a normal to be on the plane, if enabled. Result will be re-normalized.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/FloorQueryUtils.h` (Public)


#### struct `FFloorCheckSettings`  
`struct FFloorCheckSettings`  
_L22-41_
- reflection: `USTRUCT(BlueprintType)`
- desc: Settings that control how floor checks are performed
- L28 _public member_ `float FloorSweepDistance = 40.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Floor", meta = (ForceUnits = "cm"))` — Max distance to scan for floor surfaces under a Mover actor
- L32 _public member_ `float MaxWalkSlopeCosine = 0.71f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Floor")` — Walkable slope angle, represented as cosine(max slope angle) for performance reasons
- L36 _public member_ `bool bUseFlatBaseForFloorChecks = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Floor")` — If true, use a flat base shape for floor checks instead of a rounded capsule bottom
- L40 _public member_ `float PerchRadiusThreshold = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Floor", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm"))` — Distance from the capsule edge within which floor surface contact is rejected for perching purposes

#### struct `FFloorCheckResult`  
`struct FFloorCheckResult`  
_L46-115_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about the floor for walking movement, used by Mover simulations
- L55 _public member_ `uint32 bBlockingHit : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — True if there was a blocking hit in the floor test that was NOT in initial penetration. The HitResult can give more info about other circumstances.
- L59 _public member_ `uint32 bWalkableFloor : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — True if the hit found a valid walkable floor.
- L63 _public member_ `uint32 bLineTrace : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — True if the hit found a valid walkable floor using a line trace (rather than a sweep test, which happens when the sweep test fails to yield a walkable surface).
- L67 _public member_ `float LineDist;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — The distance to the floor, computed from the trace. Only valid if bLineTrace is true.
- L71 _public member_ `float FloorDist;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — The distance to the floor, computed from the swept capsule trace.
- L75 _public member_ `FHitResult HitResult;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = CharacterFloor)` — Hit result of the test that found a floor. Includes more specific data about the point of impact and surface normal at that point.
- L79 _public function_ `FFloorCheckResult() : bBlockingHit(false) , bWalkableFloor(false) , bLineTrace(false) , LineDist(0.f) , FloorDist(0.f) , HitResult(1.f)`
- L90 _public function_ `bool IsWalkableFloor() const` — Returns true if the floor result hit a walkable surface.
- L95 _public function_ `void Clear()`
- L106 _public function_ `float GetDistanceToFloor() const` — Gets the distance to floor, either LineDist or FloorDist.
- L112 _public prototype_ `void SetFromSweep(const FHitResult& InHit, const float InSweepFloorDist, const bool bIsWalkableFloor);` — Sets the passed in hit result with data from the floor Sweep
- L114 _public prototype_ `void SetFromLineTrace(const FHitResult& InHit, const float InSweepFloorDist, const float InLineDist, const bool bIsWalkableFloor);` — Sets the passed in hit result with data from the line trace

#### struct `FOptionalFloorCheckResult`  
`struct FOptionalFloorCheckResult`  
_L118-127_
- desc: Used by some movement operations to conditionally return a floor check result, if one was performed
- L120 _public member_ `uint8 bHasFloorResult : 1;` — If true, the floor test result has been computed
- L121 _public member_ `FFloorCheckResult FloorTestResult;`
- L123 _public function_ `FOptionalFloorCheckResult()`

#### class `UFloorQueryUtils`  
`class UFloorQueryUtils : public UBlueprintFunctionLibrary`  
_L133-166_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: FloorQueryUtils: a collection of stateless static BP-accessible functions for a variety of operations involving floor checks
- L138 _public prototype_ `static void FindFloor(const FMovingComponentSet& MovingComps, const FFloorCheckSettings& FloorCheckSettings, const FVector& Location, FFloorCheckResult& OutFloorResult);`
- L141 _public prototype_ `static void FindFloor(const FMovingComponentSet& MovingComps, float FloorSweepDistance, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, const FVector& Location, FFloorCheckResult& OutFloorResult, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`
- L143 _public prototype_ `static void ComputeFloorDist(const FMovingComponentSet& MovingComps, const FFloorCheckSettings& FloorCheckSettings, float LineTraceDistance, const FVector& Location, FFloorCheckResult& OutFloorResult);`
- L146 _public prototype_ `static void ComputeFloorDist(const FMovingComponentSet& MovingComps, float LineTraceDistance, float FloorSweepDistance, float MaxWalkSlopeCosine, const FVector& Location, bool bUseFlatBaseForFloorChecks, FFloorCheckResult& OutFloorResult, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`
- L148 _public prototype_ `static bool FloorSweepTest(const FMovingComponentSet& MovingComps, FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const struct FCollisionQueryParams& Params, const struct FCollisionResponseParams& ResponseParam, bool bUseFlatBaseForFloorChecks, float PerchRadiusThreshold = 0.f);`
- L151 _public prototype_ `static bool IsHitSurfaceWalkable(const FHitResult& Hit, const FVector& UpDirection, float MaxWalkSlopeCosine);` — `UFUNCTION(BlueprintCallable, Category=Mover)`
- L157 _public prototype_ `static bool IsWithinEdgeTolerance(const FVector& CapsuleLocation, const FVector& TestImpactPoint, float CapsuleRadius, const FVector& UpDirection);` — Return true if the 2D distance to the impact point is inside the edge tolerance (CapsuleRadius minus a small rejection threshold). Useful for rejecting adjacent hits when finding a floor or landing spot.
- L164 _public prototype_ `static void TryFindFloor(UMoverComponent* MoverComp, bool& DidFindWalkableFloor, FFloorCheckResult& FloorResult);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Try to find a floor underneath a Mover actor. Requires use of UCommonLegacyMovementSettings.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVER_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace FloorQueryUtility` (scope `UE`)
- L15 _externvar_ `extern const float MIN_FLOOR_DIST;` (scope `UE::FloorQueryUtility`)
- L16 _externvar_ `extern const float MAX_FLOOR_DIST;` (scope `UE::FloorQueryUtility`)
- L17 _externvar_ `extern const float SWEEP_EDGE_REJECT_DISTANCE;` (scope `UE::FloorQueryUtility`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/GroundMovementUtils.h` (Public)


#### struct `FGroundMoveParams`  
`struct FGroundMoveParams`  
_L22-73_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for controlled ground movement function
- L27 _public member_ `EMoveInputType MoveInputType = EMoveInputType::DirectionalIntent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L30 _public member_ `FVector MoveInput = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L33 _public member_ `FRotator OrientationIntent = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L36 _public member_ `FVector PriorVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L39 _public member_ `FRotator PriorOrientation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L42 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L45 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L48 _public member_ `float Deceleration = 8000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L51 _public member_ `float Friction = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L54 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L57 _public member_ `float TurningBoost = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L60 _public member_ `FVector GroundNormal = FVector::UpVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L63 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L66 _public member_ `FVector UpDirection = FVector::UpVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L69 _public member_ `FQuat WorldToGravityQuat = FQuat::Identity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L72 _public member_ `bool bUseAccelerationForVelocityMove = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### class `UGroundMovementUtils`  
`class UGroundMovementUtils : public UBlueprintFunctionLibrary`  
_L79-152_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: GroundMovementUtils: a collection of stateless static BP-accessible functions for a variety of ground movement-related operations
- L86 _public prototype_ `static FProposedMove ComputeControlledGroundMove(const FGroundMoveParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Generate a new movement based on move/orientation intents and the prior state, constrained to the ground movement plane. Also applies deceleration friction as necessary.
- L89 _public prototype_ `static float TryMoveToStepUp(const FMovingComponentSet& MovingComps, const FVector& GravDir, float MaxStepHeight, const FFloorCheckSettings& FloorCheckSettings, const FVector& MoveDelta, const FHitResult& Hit, const FFloorCheckResult& CurrentFloor, bool bIsFalling, FOptionalFloorCheckResult* OutStepDownResult, FMovementRecord& MoveRecord);` — Move up steps or slope. Returns the percent of time applied, with 0.0 meaning no movement occurred and hit surface is invalid for step-up use.
- L92 _public prototype_ `static float TryMoveToStepUp(const FMovingComponentSet& MovingComps, const FVector& GravDir, float MaxStepHeight, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, float FloorSweepDistance, const FVector& MoveDelta, const FHitResult& Hit, const FFloorCheckResult& CurrentFloor, bool bIsFalling, FOptionalFloorCheckResult* OutStepDownResult, FMovementRecord& MoveRecord, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`
- L95 _public prototype_ `static bool TryMoveToAdjustHeightAboveFloor(const FMovingComponentSet& MovingComps, FFloorCheckResult& CurrentFloor, float MaxWalkSlopeCosine, FMovementRecord& MoveRecord);` — Moves vertically to stay within range of the walkable floor. Does nothing and returns false if floor is unwalkable or if already in range.
- L98 _public prototype_ `static bool TryMoveToKeepMinHeightAboveFloor(const FMovingComponentSet& MovingComps, FFloorCheckResult& CurrentFloor, float MaxWalkSlopeCosine, FMovementRecord& MoveRecord);` — Moves vertically to maintain the minimum distance above the walkable floor. Does nothing and returns false if floor is unwalkable or if already far enough away.
- L104 _public prototype_ `static float TryWalkToSlideAlongSurface(const FMovingComponentSet& MovingComps, const FVector& Delta, float PctOfDeltaToMove, const FQuat Rotation, const FVector& Normal, UPARAM(ref) FHitResult& Hit, bool bHandleImpact, UPARAM(ref) FMovementRecord& MoveRecord, float MaxWalkSlopeCosine, float MaxStepHeight);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Attempts to move a component along a surface in the walking mode. Returns the percent of time applied, with 0.0 meaning no movement occurred. Note: This modifies the normal and calls UMovementUtils::TryMoveToSlideAlongSurface
- L108 _public prototype_ `static FVector ComputeDeflectedMoveOntoRamp(const FVector& OrigMoveDelta, const FVector& UpDirection, const FHitResult& RampHitResult, float MaxWalkSlopeCosine, const bool bHitFromLineTrace);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Used to change a movement to be along a ramp's surface, typically to prevent slow movement when running up/down a ramp
- L111 _public prototype_ `static bool CanStepUpOnHitSurface(const FHitResult& Hit);` — `UFUNCTION(BlueprintCallable, Category = Mover)`
- L122 _public prototype_ `static float TestGroundedMoveAlongHitSurface(const FMovingComponentSet& MovingComps, const FVector& OriginalMoveDelta, const FVector& LocationAtHit, const FQuat& TargetRotation, bool bHandleImpact, float MaxStepHeight, float MaxWalkSlopeCosine, UPARAM(ref) FHitResult& InOutHit, UPARAM(ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests a potential movement along a walkable surface. Modifies InOutHit with final movement hit data Appends to InOutMoveRecord with any movement substeps Returns the percent of time applied, with 0.0 meaning no movement would occur.
- L130 _public prototype_ `static FVector TestMoveToAdjustToFloor(const FMovingComponentSet& MovingComps, const FVector& Location, const FQuat& Rotation, float MaxWalkSlopeCosine, UPARAM(ref) FFloorCheckResult& InOutCurrentFloor, UPARAM(ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests potential movement of a component up/down to adjust to a walkable floor. Intended for use while performing ground movement. Modifies InOutCurrentFloor to account for adjustments, if any was made Appends to InOutMoveRecord with any movement substeps Returns new location, including any adjustment if it was made
- L138 _public prototype_ `static FVector TestMoveToKeepMinHeightAboveFloor(const FMovingComponentSet& MovingComps, const FVector& Location, const FQuat& Rotation, float MaxWalkSlopeCosine, UPARAM(ref) FFloorCheckResult& InOutCurrentFloor, UPARAM(ref) FMovementRecord& InOutMoveRecord);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Tests potential vertical movement of a component to float a bit above a walkable floor. Intended for use while moving along ground surfaces. Modifies InOutCurrentFloor to account for adjustments, if any was made Appends to InOutMoveRecord with any movement substeps Returns new location, including any adjustment if it was made
- L146 _public prototype_ `static float TestMoveToStepOver(const FMovingComponentSet& MovingComps, const FVector& GravDir, float MaxStepHeight, const FFloorCheckSettings& FloorCheckSettings, const FVector& MoveDelta, const FQuat& Rotation, const FHitResult& MoveHitResult, const FFloorCheckResult& CurrentFloor, bool bIsFalling, FOptionalFloorCheckResult* OutFloorTestResult, FVector& OutFinalLocation, FMovementRecord& InOutMoveRecord);` — Tests potential up-and-over movement of a component to overcome a blocking obstacle hit, such as moving up steps or slope. Sets OutFloorTestResult with final floor info (optional) Sets OutFinalLocation with final component location Appends to InOutMoveRecord with any movement substeps Returns the percent of time applied, with 0.0 meaning no movement would occur.
- L149 _public prototype_ `static float TestMoveToStepOver(const FMovingComponentSet& MovingComps, const FVector& GravDir, float MaxStepHeight, float MaxWalkSlopeCosine, bool bUseFlatBaseForFloorChecks, float FloorSweepDistance, const FVector& MoveDelta, const FQuat& Rotation, const FHitResult& MoveHitResult, const FFloorCheckResult& CurrentFloor, bool bIsFalling, FOptionalFloorCheckResult* OutFloorTestResult, FVector& OutFinalLocation, FMovementRecord& InOutMoveRecord, float PerchRadiusThreshold = 0.f);` — `UE_DEPRECATED(5.8, "Use the overload taking FFloorCheckSettings instead.")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/ModularMovement.h` (Public)


#### class `UTurnGeneratorInterface`  
`class UTurnGeneratorInterface : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(BlueprintType, MinimalAPI)`
- inherits: `UInterface`

#### class `ITurnGeneratorInterface`  
`class ITurnGeneratorInterface : public IInterface`  
_L26-36_
- inherits: `IInterface`
- desc: TurnGeneratorInterface: API for generating an in-place orientation change, based on a starting state and a target orientation
- L35 _public prototype_ `FVector GetTurn(FRotator TargetOrientation, const FMoverTickStartData& FullStartState, const FMoverDefaultSyncState& MoverState, const FMoverTimeStep& TimeStep, const FProposedMove& ProposedMove, UMoverBlackboard* SimBlackboard);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=Mover)` — Returns an additive angular velocity (degrees/second) based on the starting state and timestep. The vector points in the direction of the rotation axis

#### class `ULinearTurnGenerator`  
`class ULinearTurnGenerator : public UObject, public ITurnGeneratorInterface`  
_L43-63_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UObject,ITurnGeneratorInterface`
- desc: Modular mechanism for turning a Mover actor in place using linear angular velocity.
- L51 _public member_ `float HeadingRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Linear Turning", meta = (ClampMin = "-1", UIMin = "0", ForceUnits = "deg/s"))` — Maximum angular velocity of heading changes (degrees per second). AKA Yaw, AKA Z. Negative numbers will cause rotation to snap instantly to desired orientation.
- L55 _public member_ `float PitchRate = -1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Linear Turning", meta = (ClampMin = "-1", UIMin = "0", ForceUnits = "deg/s"))` — Maximum angular velocity of pitch changes (degrees per second). Negative numbers will cause rotation to snap instantly to desired orientation.
- L59 _public member_ `float RollRate = -1.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Linear Turning", meta = (ClampMin = "-1", UIMin = "0", ForceUnits = "deg/s"))` — Maximum angular velocity of roll changes (degrees per second). Negative numbers will cause rotation to snap instantly to desired orientation.
- L62 _public prototype_ `virtual FVector GetTurn_Implementation(FRotator TargetOrientation, const FMoverTickStartData& FullStartState, const FMoverDefaultSyncState& MoverState, const FMoverTimeStep& TimeStep, const FProposedMove& ProposedMove, UMoverBlackboard* SimBlackboard) override;`

#### class `UExactDampedTurnGenerator`  
`class UExactDampedTurnGenerator : public UObject, public ITurnGeneratorInterface`  
_L70-81_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UObject,ITurnGeneratorInterface`
- desc: Modular mechanism for turning a Mover actor in place using an exact damped spring
- L78 _public member_ `float HalfLifeSeconds = 0.15f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exact Damped Turning", meta = (ClampMin = "0.01", UIMin = "0", ForceUnits = "seconds"))` — Time required to reach halfway to the target orientation (smaller = quicker)
- L80 _public prototype_ `virtual FVector GetTurn_Implementation(FRotator TargetOrientation, const FMoverTickStartData& FullStartState, const FMoverDefaultSyncState& MoverState, const FMoverTimeStep& TimeStep, const FProposedMove& ProposedMove, UMoverBlackboard* SimBlackboard) override;`

#### class `UBlueprintableTurnGenerator`  
`class UBlueprintableTurnGenerator : public UObject, public ITurnGeneratorInterface`  
_L89-92_
- reflection: `UCLASS(MinimalAPI, Blueprintable, EditInlineNew, Abstract)`
- inherits: `UObject,ITurnGeneratorInterface`
- desc: Base class for blueprint-implemented turn generators. This is necessary due to the lack of support for specifying EditInlineNew on a BP class, so it has to inherit the flag from a native parent.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MovementMixer.h` (Public)


#### class `UMovementMixer`  
`class UMovementMixer : public UObject`  
_L18-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Class in charge of Mixing various moves when evaluating/combining moves. The mixer used can be set on the MoverComponent itself.
- L23 _public prototype_ `UMovementMixer();`
- L26 _public prototype_ `virtual void MixLayeredMove(const FLayeredMoveBase& ActiveMove, const FProposedMove& MoveStep, FProposedMove& OutCumulativeMove);` — In charge of mixing Layered Move proposed moves into a cumulative proposed move based on mix mode and priority.
- L29 _public prototype_ `virtual void MixLayeredMove(const FLayeredMoveInstance& ActiveMove, const FProposedMove& MoveStep, FProposedMove& OutCumulativeMove);` — In charge of mixing Layered Move proposed moves into a cumulative proposed move based on mix mode and priority.
- L32 _public prototype_ `virtual void MixProposedMoves(const FProposedMove& MoveToMix, FVector UpDirection, FProposedMove& OutCumulativeMove);` — In charge of mixing proposed moves together. Is similar to MixLayeredMove but is only responsible for mixing proposed moves instead of layered moves.
- L35 _public prototype_ `virtual void ResetMixerState();` — Resets all state used for mixing. Should be called before or after finished mixing moves.
- L39 _protected member_ `uint8 CurrentHighestPriority;` — Stores the current highest priority we've hit during this round of mixing. Will get reset. Note: Currently only used for mixing layered moves
- L42 _protected member_ `double CurrentLayeredMoveStartTime;` — Earliest start time of the layered move with highest priority. Used to help break ties of moves with same priority. Note: Currently only used for mixing layered moves
- L48 _protected prototype_ `static bool CheckPriority(const FLayeredMoveBase* LayeredMove, uint8& InOutHighestPriority, double& InOutCurrentLayeredMoveStartTimeMs);` — Helper function for layered move mixing to check priority and start time if priority is the same. Returns true if this layered move should take priority given current HighestPriority and CurrentLayeredMoveStartTimeMs
- L49 _protected prototype_ `static bool CheckPriority(uint8 LayeredMovePriority, double LayeredMoveStartTimeMs, uint8& InOutHighestPriority, double& InOutCurrentLayeredMoveStartTimeMs);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MovementRecord.h` (Public)


#### struct `FMovementSubstep`  
`struct FMovementSubstep`  
_L11-23_
- reflection: `USTRUCT(BlueprintType)`
- desc: A part of movement accounting, representing a single piece of a move operation, such as a slide, floor adjustment, etc.
- L15 _public function_ `FMovementSubstep()`
- L16 _public function_ `FMovementSubstep(FName InMoveName, FVector InMoveDelta, bool InIsRelevant = true) : MoveName(InMoveName), MoveDelta(InMoveDelta), bIsRelevant(InIsRelevant)`
- L19 _public member_ `FName MoveName = NAME_None;`
- L20 _public member_ `FVector MoveDelta = FVector::ZeroVector;`
- L22 _public member_ `bool bIsRelevant = false;` — TODO: Replace this simple flag with a bit mask of different aspects of relevancy (i.e. the move delta is relevant BUT not to vertical velocity)

#### struct `FMovementRecord`  
`struct FMovementRecord`  
_L32-64_
- reflection: `USTRUCT(BlueprintType)`
- desc: Accounting record of a move as it is processed. Moves are composed of substeps, and these can be marked to indicate how they influence the final collapsed move. Relevancy means the substep (or part thereof) is contributing to the reflected movement state. Example: a character moves forward across a slightly irregular sidewalk, and then is adjusted downward to keep it sticking closely to the sidewalk. The forward move is a relevant substep, while the vertical heigh adjustment is not.
- L36 _public prototype_ `void Reset();`
- L38 _public prototype_ `void Append(FMovementSubstep Substep);`
- L42 _public function_ `void LockRelevancy(bool bLockValue)` — TODO: consider changing this to only allow locking as irrelevant TODO: this relevancy locking is hacky, could be replaced by a scoping-style mechanism to allow higher-level functions to override a lower-level function's default relevancy
- L43 _public function_ `void UnlockRelevancy()`
- L45 _public function_ `void SetDeltaSeconds(float DeltaSeconds)`
- L47 _public function_ `const TArray<FMovementSubstep>& GetSubsteps() const`
- L48 _public function_ `const FVector& GetTotalMoveDelta() const`
- L49 _public function_ `const FVector& GetRelevantMoveDelta() const`
- L50 _public function_ `FVector GetRelevantVelocity() const`
- L52 _public prototype_ `FString ToString() const;`
- L55 _private member_ `FVector TotalMoveDelta = FVector::ZeroVector;`
- L56 _private member_ `FVector RelevantMoveDelta = FVector::ZeroVector;` — This is the portion of movement that counts as relevant to actor velocity
- L57 _private member_ `float TotalDeltaSeconds = 0.f;`
- L59 _private member_ `bool bIsRelevancyLocked = false;`
- L60 _private member_ `bool bRelevancyLockValue = false;`
- L63 _private member_ `TArray<FMovementSubstep> Substeps;` — TODO: Perf, need to reserve a reasonable number or possibly refactor this to be some kind of pool

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MovementRecordUtils.h` (Public)


#### class `UMovementRecordUtils`  
`class UMovementRecordUtils : public UBlueprintFunctionLibrary`  
_L16-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: MovementRecordUtils: a collection of stateless static BP-accessible functions for movement record related operations
- L23 _public prototype_ `static void K2_SetDeltaSeconds(UPARAM(Ref) FMovementRecord& OutMovementRecord, float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = Mover, DisplayName="Set Delta Seconds")` — Sets the delta time these moves took place over
- L27 _public prototype_ `static const FVector& K2_GetTotalMoveDelta(const FMovementRecord& MovementRecord);` — `UFUNCTION(BlueprintPure, Category = Mover, DisplayName="Get Total Move Delta")` — Get all the move delta applied to the actor/record
- L31 _public prototype_ `static const FVector& K2_GetRelevantMoveDelta(const FMovementRecord& MovementRecord);` — `UFUNCTION(BlueprintPure, Category = Mover, DisplayName="Get Relevant Move Delta")` — Get relevant move delta applied to the actor/record
- L35 _public prototype_ `static FVector K2_GetRelevantVelocity(const FMovementRecord& MovementRecord);` — `UFUNCTION(BlueprintPure, Category = Mover, DisplayName="Get Relevant Velocity")` — Get relevant velocity applied to the actor/record

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MovementUtils.h` (Public)


#### struct `FTrajectorySampleInfo`  
`struct FTrajectorySampleInfo`  
_L28-51_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates detailed trajectory sample info, from a move that has already occurred or one projected into the future
- L34 _public member_ `FTransform Transform;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Position and orientation (world space)
- L38 _public member_ `FVector LinearVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Velocity at the time of this sample (world space, units/sec)
- L42 _public member_ `FVector InstantaneousAcceleration = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Acceleration at the time of this sample (world space, units/sec^2)
- L46 _public member_ `FRotator AngularVelocity = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Rotational velocity (world space, degrees/sec)
- L50 _public member_ `double SimTimeMs = 0.0f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Time stamp of this sample, in server simulation time

#### struct `FComputeVelocityParams`  
`struct FComputeVelocityParams`  
_L55-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for compute velocity function
- L60 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L63 _public member_ `FVector InitialVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L66 _public member_ `FVector MoveDirectionIntent = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L70 _public member_ `float MaxSpeed = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — AuxState variables
- L73 _public member_ `float TurningBoost = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L76 _public member_ `float Friction = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L79 _public member_ `float Deceleration = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L82 _public member_ `float Acceleration = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L85 _public member_ `FVector MoveInput = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L88 _public member_ `EMoveInputType MoveInputType = EMoveInputType::DirectionalIntent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L91 _public member_ `bool bUseAccelerationForVelocityMove = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### struct `FComputeCombinedVelocityParams`  
`struct FComputeCombinedVelocityParams`  
_L96-130_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for ComputeCombinedVelocity()
- L101 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L104 _public member_ `FVector InitialVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L107 _public member_ `FVector MoveDirectionIntent = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L111 _public member_ `float MaxSpeed = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — AuxState variables
- L114 _public member_ `float TurningBoost = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L117 _public member_ `float Friction = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L120 _public member_ `float Deceleration = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L123 _public member_ `float Acceleration = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L126 _public member_ `FVector ExternalAcceleration = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L129 _public member_ `float OverallMaxSpeed = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### class `UMovementUtils`  
`class UMovementUtils : public UBlueprintFunctionLibrary`  
_L136-348_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: MovementUtils: a collection of stateless static BP-accessible functions for a variety of movement-related operations
- L147 _public prototype_ `template <class ComponentType> static const ComponentType* GetOriginalComponentType(const AActor* MoverCompOwner);` — Gets CDO component type - useful for getting original values
- L151 _public prototype_ `static bool IsExceedingMaxSpeed(const FVector& Velocity, float InMaxSpeed);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Checks whether a given velocity is exceeding a maximum speed, with some leeway to account for numeric imprecision
- L155 _public prototype_ `static FVector ComputeVelocity(const FComputeVelocityParams& InParams);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Returns new ground-based velocity (worldspace) based on previous state, movement intent (worldspace), and movement settings
- L159 _public prototype_ `static FVector ComputeCombinedVelocity(const FComputeCombinedVelocityParams& InParams);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Returns new velocity based on previous state, movement intent, movement mode's influence and movement settings
- L163 _public function_ `static FVector ComputeVelocityFromGravity(const FVector& GravityAccel, float DeltaSeconds)` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Returns velocity (units per second) contributed by gravitational acceleration over a given time
- L167 _public prototype_ `static FVector DeduceUpDirectionFromGravity(const FVector& GravityAcceleration);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Returns the up direction deduced from gravity acceleration, but defaults to mover constants up direction if zero
- L171 _public prototype_ `static bool CanEscapeGravity(const FVector& PriorVelocity, const FVector& NewVelocity, const FVector& GravityAccel, float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Checks whether a given velocity is strong enough to lift off against gravity
- L177 _public prototype_ `static FVector ConstrainToPlane(const FVector& Vector, const FPlane& MovementPlane, bool bMaintainMagnitude=true);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Ensures input Vector (typically a velocity, acceleration, or move delta) is limited to a movement plane. @param bMaintainMagnitude - if true, vector will be scaled after projection in an attempt to keep magnitude the same
- L181 _public prototype_ `static FRotator ApplyGravityToOrientationIntent(const FRotator& IntendedOrientation, const FQuat& WorldToGravity, bool bStayVertical = true);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Converts intended orientation into orientation rotated by out current gravity
- L185 _public function_ `static FVector ProjectToGravityFloor(const FVector& Vector, const FVector& UpDirection)` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Project a vector onto the floor defined by the gravity direction.
- L189 _public function_ `static FVector GetGravityVerticalComponent(const FVector& Vector, const FVector& UpDirection)` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the component of the vector in the gravity-space vertical direction.
- L192 _public function_ `static void SetGravityVerticalComponent(FVector& Vector, const FVector::FReal VerticalValue, const FVector& UpDirection)` — Set the vertical component of the vector to the given value in the gravity-space vertical direction.
- L198 _public prototype_ `static FVector ComputeSlideDelta(const FMovingComponentSet& MovingComps, const FVector& Delta, const float PctOfDeltaToMove, const FVector& Normal, const FHitResult& Hit);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Returns an alternative move delta to slide along a surface, based on parameters describing a blocked attempted move
- L201 _public prototype_ `static FVector ComputeTwoWallAdjustedDelta(const FMovingComponentSet& MovingComps, const FVector& MoveDelta, const FHitResult& Hit, const FVector& OldHitNormal);` — Returns an alternative move delta when we are in contact with 2 surfaces
- L208 _public prototype_ `static float TryMoveToSlideAlongSurface(const FMovingComponentSet& MovingComps, const FVector& Delta, float PctOfDeltaToMove, const FQuat Rotation, const FVector& Normal, UPARAM(Ref) FHitResult& Hit, bool bHandleImpact, UPARAM(Ref) FMovementRecord& MoveRecord);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Move To Slide Along Surface (Movement Record)"))` — Attempts to move a component along a surface. Returns the percent of time applied, with 0.0 meaning no movement occurred. Note: This function takes a movement record that collects moves applied to the actor see @FMovementRecord
- L215 _public prototype_ `static float TryMoveToSlideAlongSurfaceNoMovementRecord(const FMovingComponentSet& MovingComps, const FVector& Delta, float PctOfDeltaToMove, const FQuat Rotation, const FVector& Normal, UPARAM(Ref) FHitResult& Hit, bool bHandleImpact);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Move To Slide Along Surface (No Movement Record)"))` — Attempts to move a component along a surface. Returns the percent of time applied, with 0.0 meaning no movement occurred. Note: This function doesn't update a movement record so velocity should be gathered/set using a different method
- L236 _public prototype_ `static float TrySafeMoveAndSlideUpdatedComponent(const FMovingComponentSet& MovingComps, const FVector& Delta, const FQuat& NewRotation, bool bSweep, UPARAM(Ref) FHitResult& OutHit, ETeleportType Teleport, UPARAM(Ref) FMovementRecord& MoveRecord, bool bSlideAlongSurface = true);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Safe Move And Slide (Movement Record)"))` — Attempts to move a component and resolve any penetration issues with the proposed move Delta. This function handles blocking moves and slides along the surface or stops on impact. It uses @TryMoveToSlideAlongSurface to slide along the surface on hit, so if other behavior is needed for sliding (like Falling based sliding) consider using @TrySafeMoveUpdatedComponent and a slide function or setting @bSlideAlongSurface to false and then using a separate sliding function. Note: This function takes a movement record that collects moves applied to the actor see @FMovementRecord. @param MovingComps Encapsulates components involved in movement @param Delta The desired location change in world space @param NewRotation The new desired rotation in world space @param bSweep Whether we sweep to the destination location @param OutHit Optional output describing the blocking hit that stopped the move, if any @param Teleport Whether we teleport the physics state (if physics collision is enabled for this object) @param MoveRecord Move record to add moves to @param bSlideAlongSurface If true the actor slides along a blocking surface. If false the actor will stop if the move was blocked @return Returns the percent of the move applied 0 to 1, where 1 represents the whole move being applied
- L254 _public prototype_ `static float TrySafeMoveAndSlideUpdatedComponentNoMovementRecord(const FMovingComponentSet& MovingComps, const FVector& Delta, const FQuat& NewRotation, bool bSweep, UPARAM(Ref) FHitResult& OutHit, ETeleportType Teleport, bool bSlideAlongSurface = true);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Safe Move And Slide (No Movement Record)"))` — Attempts to move a component and resolve any penetration issues with the proposed move Delta. This function handles blocking moves and slides along the surface or stops on impact. It uses @TryMoveToSlideAlongSurface to slide along the surface on hit, so if other behavior is needed for sliding (like Falling based sliding) consider using @TrySafeMoveUpdatedComponent and a slide function or setting @bSlideAlongSurface to false and then using a separate sliding function. Note: This function doesn't update a movement record so velocity should be gathered/set using a different method @param MovingComps Encapsulates components involved in movement @param Delta The desired location change in world space @param NewRotation The new desired rotation in world space @param bSweep Whether we sweep to the destination location @param OutHit Optional output describing the blocking hit that stopped the move, if any @param Teleport Whether we teleport the physics state (if physics collision is enabled for this object) @param bSlideAlongSurface If true the actor slides along a blocking surface. If false the actor will stop if the move was blocked @return Returns the percent of the move applied 0 to 1, where 1 represents the whole move being applied
- L261 _public prototype_ `static bool TrySafeMoveUpdatedComponent(const FMovingComponentSet& MovingComps, const FVector& Delta, const FQuat& NewRotation, bool bSweep, UPARAM(Ref) FHitResult& OutHit, ETeleportType Teleport, UPARAM(Ref) FMovementRecord& MoveRecord);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Safe Move Updated Component (Movement Record)"))` — Attempts to move a component and resolve any penetration issues with the proposed move Delta Note: This function takes a movement record that collects moves applied to the actor see @FMovementRecord
- L268 _public prototype_ `static bool TrySafeMoveUpdatedComponentNoMovementRecord(const FMovingComponentSet& MovingComps, const FVector& Delta, const FQuat& NewRotation, bool bSweep, UPARAM(Ref) FHitResult& OutHit, ETeleportType Teleport);` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Try Safe Move Updated Component (No Movement Record)"))` — Attempts to move a component and resolve any penetration issues with the proposed move Delta Note: This function doesn't update a movement record so velocity should be gathered/set using a different method
- L271 _public prototype_ `static FVector ComputePenetrationAdjustment(const FHitResult& Hit);` — Returns a movement step that should get the subject of the hit result out of an initial penetration condition
- L274 _public prototype_ `static bool TryMoveToResolvePenetration(const FMovingComponentSet& MovingComps, EMoveComponentFlags MoveComponentFlags, const FVector& ProposedAdjustment, const FHitResult& Hit, const FQuat& NewRotationQuat, FMovementRecord& MoveRecord);` — Attempts to move out of a situation where the component is stuck in geometry, using a suggested adjustment to start.
- L275 _public prototype_ `static void InitCollisionParams(const UPrimitiveComponent* UpdatedPrimitive, FCollisionQueryParams& OutParams, FCollisionResponseParams& OutResponseParam);`
- L276 _public prototype_ `static bool OverlapTest(const USceneComponent* UpdatedComponent, const UPrimitiveComponent* UpdatedPrimitive, const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor);`
- L280 _public prototype_ `static FVector ComputeVelocityFromPositions(const FVector& FromPos, const FVector& ToPos, float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Computes velocity based on start and end positions over time
- L285 _public prototype_ `static FRotator ComputeAngularVelocity(const FRotator& From, const FRotator& To, const FQuat& WorldToGravity, float DeltaSeconds, float TurningRateLimit=-1.f);` — `UE_DEPRECATED(5.7, "Rotator is no longer used for angular velocity")` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Computes the angular velocity needed to change from one orientation to another within a time frame. Use the optional TurningRateLimit to clamp to a maximum step (negative=unlimited).
- L289 _public prototype_ `static FVector ComputeAngularVelocityDegrees(const FRotator& From, const FRotator& To, float DeltaSeconds, float TurningRateLimit = -1.0f);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Computes the angular velocity needed to change from one orientation to another within a time frame. Use the optional TurningRateLimit to clamp to a maximum step in degrees per second (negative=unlimited).
- L293 _public prototype_ `static FVector ComputeDirectionIntent(const FVector& MoveInput, EMoveInputType MoveInputType, float MaxSpeed);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Computes the directional movement intent based on input vector and associated type
- L298 _public prototype_ `static bool IsAngularVelocityZero(const FRotator& AngularVelocity);` — `UE_DEPRECATED(5.7, "Rotator is no longer used for angular velocity")` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns whether this rotator representing angular velocity has any non-zero values. This function exists due to FRotator::IsZero queries performing undesired wrapping and clamping.
- L302 _public prototype_ `static FRotator ApplyAngularVelocityToRotator(const FRotator& StartingOrient, const FVector& AngularVelocityDegrees, float DeltaSeconds);` — `UFUNCTION(BlueprintPure, Category = Mover)` — Applies a desired angular velocity to a starting rotator over time. Returns the new orientation rotator.
- L306 _public prototype_ `static FQuat ApplyAngularVelocityToQuat(const FQuat& StartingOrient, const FVector& AngularVelocityDegrees, float DeltaSeconds);` — `UFUNCTION(BlueprintPure, Category = Mover)` — Applies a desired angular velocity to a starting quaternion over time. Returns the new orientation quaternion.
- L311 _public prototype_ `static FRotator ApplyAngularVelocity(const FRotator& StartingOrient, const FRotator& AngularVelocity, float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — `UE_DEPRECATED(5.7, "Rotator is no longer used for angular velocity")` — Applies a desired angular velocity to a starting rotator over time. Returns the new orientation rotator.
- L319 _public prototype_ `static bool FindTeleportSpot(const UMoverComponent* MoverComp, UPARAM(Ref) FVector& TestLocation, FRotator TestRotation);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Try to find an acceptable non-colliding location to place TestActor as close to possible to TestLocation. Expects TestLocation to be a valid location inside the level. Returns true if a location without blocking collision is found, in which case TestLocation is overwritten with the new clear location. Returns false if no suitable location could be found, in which case TestLocation is unmodified.
- L323 _public prototype_ `static bool TestEncroachment(const UMoverComponent* MoverComp, FVector TestLocation, FRotator TestRotation);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns whether MoverComp's Actor would encroach at TestLocation on something that blocks it.
- L331 _public prototype_ `static bool TestEncroachmentAndAdjust(const UMoverComponent* MoverComp, FVector TestLocation, FRotator TestRotation, FVector& OutProposedAdjustment);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns whether MoverComp's Actor would encroach at TestLocation on something that blocks it. If blocked, we'll attempt to find an adjustment and set OutProposedAdjustment accordingly. OutProposedAdjustment will be zero'd if there's no blockage or an adjustment could not be found.
- L339 _public prototype_ `static bool TryMoveUpdatedComponent_Internal(const FMovingComponentSet& MovingComps, const FVector& Delta, const FQuat& NewRotation, bool bSweep, EMoveComponentFlags MoveComponentFlags, FHitResult* OutHit, ETeleportType Teleport);` — Internal function that other move functions use to perform all actual component movement and retrieve results Note: This function moves the character directly and should only be used if needed. Consider using something like TrySafeMoveUpdatedComponent.
- L342 _public prototype_ `static bool TestEncroachment_Internal(const UWorld* World, const AActor* TestActor, const UPrimitiveComponent* PrimComp, const FTransform& TestWorldTransform, const TArray<AActor*>& IgnoreActors);` — Internal function for testing whether a Mover actor would encroach at a test location
- L346 _public prototype_ `static bool TestEncroachmentWithAdjustment_Internal(const UWorld* World, const AActor* TestActor, const UPrimitiveComponent* PrimComp, const FTransform& TestWorldTransform, const TArray<AActor*>& IgnoreActors, OUT FVector& OutProposedAdjustment);` — Internal function for testing whether a Mover actor would encroach at a test location, and computes a proposed adjustment where they won't encroach (if found).
- L351 _function_ `template <class ComponentType> const ComponentType* UMovementUtils::GetOriginalComponentType(const AActor* MoverCompOwner)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVER_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace MoverUtils` (scope `UE`)
- L22 _externvar_ `extern const double SMALL_MOVE_DISTANCE;` (scope `UE::MoverUtils`)
- L23 _externvar_ `extern const double VERTICAL_SLOPE_NORMAL_MAX_DOT;` (scope `UE::MoverUtils`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MovementUtilsTypes.h` (Public)


#### enum `EMoveMixMode`  
`enum class EMoveMixMode : uint8`  
_L17-29_
- reflection: `UENUM()`
- L20 _public enumerator_ `AdditiveVelocity = 0` — Velocity (linear and angular) is intended to be added with other sources
- L22 _public enumerator_ `OverrideVelocity = 1` — Velocity (linear and angular) should override others
- L24 _public enumerator_ `OverrideAll = 2` — All move parameters should override others
- L27 _public enumerator_ `OverrideAllExceptVerticalVelocity = 3` — All move parameters should override others except linear velocity along the up/down axis. Commonly used for falling.

#### struct `FProposedMove`  
`struct FProposedMove`  
_L34-68_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates info about an intended move that hasn't happened yet
- L38 _public function_ `FProposedMove() : bHasDirIntent(false)`
- L47 _public member_ `FName PreferredMode = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Indicates that we should switch to a particular movement mode before the next simulation step is performed. Note: If this is set from a layered move the preferred mode will only be set at the beginning of the layered move, not continuously.
- L51 _public member_ `FVector DirectionIntent = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Directional, per-axis magnitude [-1, 1] in world space (length of 1 indicates max speed intent). Only valid if bHasDirIntent is set.
- L55 _public member_ `FVector LinearVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Units per second, world space, possibly mapped onto walking surface
- L59 _public member_ `FVector AngularVelocityDegrees = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Angular velocity in degrees per second. Direction points along rotation axis.
- L63 _public member_ `uint8 bHasDirIntent : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Signals whether there was any directional intent specified
- L67 _public member_ `EMoveMixMode MixMode = EMoveMixMode::AdditiveVelocity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Determines how this move should resolve with other moves

#### struct `FMovingComponentSet`  
`struct FMovingComponentSet`  
_L77-96_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates components involved in movement. Used by many library functions. Only a scene component is required for movement, but this is typically a primitive component so we provide a pre-cast ptr for convenience.
- L81 _public function_ `FMovingComponentSet()`
- L82 _public function_ `FMovingComponentSet(USceneComponent* InUpdatedComponent)`
- L83 _public function_ `FMovingComponentSet(UMoverComponent* InMoverComponent)`
- L85 _public prototype_ `void SetFrom(USceneComponent* InUpdatedComponent);`
- L86 _public prototype_ `void SetFrom(UMoverComponent* InMoverComponent);`
- L89 _public member_ `TWeakObjectPtr<USceneComponent> UpdatedComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)`
- L92 _public member_ `TWeakObjectPtr<UPrimitiveComponent> UpdatedPrimitive;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)`
- L95 _public member_ `TWeakObjectPtr<UMoverComponent> MoverComponent;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)`

#### struct `FMoverCollisionParams`  
`struct FMoverCollisionParams`  
_L102-119_
- desc: Encapsulates a collision context involved in movement. Useful for altering queries without changing the component.
- L105 _public function_ `FMoverCollisionParams()`
- L106 _public prototype_ `FMoverCollisionParams(const USceneComponent* SceneComp);`
- L108 _public prototype_ `void SetFromPrimitiveComponent(const UPrimitiveComponent* PrimitiveComp);`
- L110 _public member_ `FCollisionShape Shape;`
- L112 _public member_ `ECollisionChannel Channel = ECollisionChannel::ECC_Pawn;`
- L114 _public member_ `FCollisionQueryParams QueryParams;`
- L116 _public member_ `FCollisionResponseParams ResponseParams;`
- L118 _public member_ `EMoveComponentFlags MoveComponentFlags = MOVECOMP_NoFlags;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/MoverBlackboard.h` (Public)


#### enum `EInvalidationReason`  
`enum class EInvalidationReason : uint8`  
_L15-19_
- L17 _public enumerator_ `FullReset` — All blackboard objects should be invalidated
- L18 _public enumerator_ `Rollback` — Invalidate any rollback-sensitive objects

#### class `UMoverBlackboard`  
`class UMoverBlackboard : public UObject`  
_L30-147_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: MoverBlackboard: this is a simple generic map that can store any type, used as a way for decoupled systems to store calculations or transient state data that isn't necessary to reconstitute the movement simulation. It has support for invalidation, which could occur, for example, when a rollback is triggered. Values submitted are copy-in, copy-out. Unlike a traditional blackboard pattern, there is no support for subscribing to changes. TODO: expand invalidation rules attached to BBObjs, for instance if we wanted some to invalidate upon rollback. Some might expire over time or after a number of simulation frames. Or an item could be tagged with a predicted sim frame #, and become cleared once that frame is finalized/confirmed.
- L82 _public function_ `template<typename T> bool TryGet(FName ObjName, T& OutFoundValue) const` — Attempt to retrieve an object from the blackboard. If found, OutFoundValue will be set. Returns true/false to indicate whether it was found.
- L117 _public function_ `bool Contains(FName ObjName) const` — Returns true/false to indicate if an object is stored with that name
- L125 _public function_ `template<typename T> void Set(FName ObjName, T Obj)` — Store object by a named key, overwriting any existing object
- L132 _public prototype_ `void Invalidate(FName ObjName);` — Invalidate an object by name
- L135 _public prototype_ `void Invalidate(EInvalidationReason Reason);` — Invalidate all objects that can be affected by a particular circumstance (such as a rollback)
- L138 _public function_ `void InvalidateAll()` — Invalidate all objects
- L141 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L145 _private member_ `mutable FTransactionallySafeRWLock ObjectsMapLock;` — used internally when reading/writing to ObjectsByName map
- L146 _private member_ `TMap<FName, TUniquePtr<BlackboardObject>> ObjectsByName;`

#### class `UMoverBlackboard::BlackboardObject`  
`class BlackboardObject`  
_L35-76_
- L58 _public function_ `template<typename T> BlackboardObject(const T& obj) : ContainerPtr(MakeShared<ObjectContainer<T>>(obj))`
- L61 _public function_ `template<typename T> const T& Get() const`
- L68 _public function_ `template<typename T> T& GetMutable() const`
- L75 _private member_ `TSharedPtr<ObjectContainerBase> ContainerPtr;`

#### struct `UMoverBlackboard::BlackboardObject::ObjectContainerBase`  
`struct ObjectContainerBase`  
_L38-40_
- desc: untyped base

#### struct `UMoverBlackboard::BlackboardObject::ObjectContainer`  
`template<typename T> struct ObjectContainer : ObjectContainerBase`  
_L44-53_
- inherits: `ObjectContainerBase`
- desc: typed container
- L46 _public function_ `ObjectContainer(const T& t) : Object(t)`
- L48 _public function_ `const T& Get()`
- L49 _public function_ `T& GetMutable()`
- L52 _private member_ `T Object;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/PlayMoverMontageCallbackProxy.h` (Public)


#### class `UPlayMoverMontageCallbackProxy`  
`class UPlayMoverMontageCallbackProxy : public UPlayMontageCallbackProxy`  
_L23-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPlayMontageCallbackProxy`
- desc: Runtime object used as a proxy to an async blueprint task node that runs animation montages on Mover actors. This leverages parent UPlayMontageCallbackProxy to perform animation, while adding an accompanying layered move to handle any root motion from the montage.
- L29 _private prototype_ `static UPlayMoverMontageCallbackProxy* CreateProxyObjectForPlayMoverMontage( UMoverComponent* InMoverComponent, UAnimMontage* MontageToPlay, float PlayRate = 1.f, float StartingPosition = 0.f, FName StartingSection = NAME_None, bool bShouldStopAllMontages = true, float BlendOutOverride = -1.f);` — `UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))` — Called to perform the query internally
- L40 _public prototype_ `virtual void BeginDestroy() override;`
- L44 _protected prototype_ `bool PlayMoverMontage( UMoverComponent* InMoverComponent, USkeletalMeshComponent* InSkeletalMeshComponent, UAnimMontage* MontageToPlay, float PlayRate = 1.f, float StartingPosition = 0.f, FName StartingSection = NAME_None, bool bShouldStopAllMontages = true, float BlendOutOverride = -1.f, EMoveMixMode MixMode = EMoveMixMode::OverrideAll);`
- L56 _protected prototype_ `void OnMoverMontageEnded(FName IgnoredNotifyName);` — `UFUNCTION()`
- L58 _protected prototype_ `void UnbindMontageDelegates();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/RollbackBlackboard.h` (Public)


#### enum `EBlackboardSizingPolicy`  
`enum class EBlackboardSizingPolicy : uint8`  
_L44-61_
- reflection: `UENUM()`
- desc: Determines how a blackboard's entry buffer is sized
- L47 _public enumerator_ `FixedDeclaredSize` — Buffer size is set at a given number and and never changes
- L53 _public enumerator_ `FixedBackendBufferSize UMETA(Hidden)` — Buffer size matches the backend simulation's history size, determined by ticking rate and history settings. A simulation running a fixed 30 fps with a 1 second history will need a buffer size of 30. For variable rate simulations, buffer size cam only be estimated. NOT YET IMPLEMENTED
- L60 _public enumerator_ `SingleEntry` — Buffer size is minimal, for a single value slot. Useful for cases where rolling back shouldn't change the value, or for short-lived values that are only set & read within the same simulation frame. Example: a statistic tracking the maximum time spent in a particular mode's simulation tick. Note this will still have 2 elements for asynchronous simulations, to prevent thread contention over the entry.

#### enum `EBlackboardPersistencePolicy`  
`enum class EBlackboardPersistencePolicy : uint8`  
_L67-83_
- reflection: `UENUM()`
- desc: Determines how long a blackboard entry can be read after its value is set. Time is in terms of simulation frames or simulation time.
- L70 _public enumerator_ `Forever = 0` — Any edits to the entry remain valid and readable indefinitely
- L73 _public enumerator_ `NextFrameOnly UE_DEPRECATED(5.8, "Deprecated in favor of ThroughNextFrame, which has identical behavior") = 1` — Any edits remain valid until the end of the next simulation frame. If an edit occurs during frame N, the entry will be readable for the remainder of frame N and frame N+1.
- L76 _public enumerator_ `ThroughNextFrame = 2` — Any edits remain valid until the end of the next simulation frame. If an edit occurs during frame N, the entry will be readable for the remainder of frame N and frame N+1.
- L79 _public enumerator_ `CurrentFrameOnly = 3` — Any edits remain valid until the end of the current simulation frame. If an edit occurs during frame N, the entry will be readable for the remainder of frame N, until frame N+1 begins.
- L82 _public enumerator_ `LimitedTime = 4 UMETA(Hidden)` — NOT YET IMPLEMENTED. Any edits remain valid until a specified amount of simulation time has passed.

#### enum `EBlackboardRollbackPolicy`  
`enum class EBlackboardRollbackPolicy : uint8`  
_L90-103_
- reflection: `UENUM()`
- desc: Determines how a blackboard's buffered entries are treated when a rollback occurs
- L93 _public enumerator_ `InvalidatedOnRollback` — Entry changes occurring after the rollback time are effectively erased and no longer retrievable. New entries may be written during resimulation.
- L96 _public enumerator_ `IgnoreRollback` — Current value does not change when a rollback occurs. Typically paired with the SingleEntry sizing policy.
- L99 _public enumerator_ `WritableDuringResimulation UMETA(Hidden)` — Entries are not invalidated during rollback, and may be read/written during resim. If left alone, they will persist. NOT YET IMPLEMENTED.
- L102 _public enumerator_ `LockedDuringResimulation UMETA(Hidden)` — Entries are not invalidated during rollback, and may be read during resim. But writes cannot be performed during resim. NOT YET IMPLEMENTED.

#### class `URollbackBlackboard`  
`class URollbackBlackboard : public UObject`  
_L113-547_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This is the core rollback blackboard, with API for external access and admin use. See @FRollbackBlackboardSimWrapper for in-simulation use.
- L347 _public function_ `template<typename EntryT> bool CreateEntry(FName EntryName, const EntrySettings& InSettings)`
- L360 _public function_ `bool HasEntry(FName EntryName) const`
- L368 _private function_ `template<typename EntryT> bool TrySet_External(FName ObjName, const EntryT& Obj)` — Store object by a named key, overwriting any existing object
- L384 _private function_ `template<typename EntryT> bool TryGet_External(FName ObjName, EntryT& OutFoundValue) const` — Attempt to retrieve an object from the blackboard. If found, OutFoundValue will be set. Returns true/false to indicate whether it was found.
- L398 _private function_ `template<typename EntryT> const EntryT* TryGetRef_External(FName ObjName) const` — Users may access the reference of the entry, which may be more efficient than copy - out, copy - in. Although you can get access to the reference, it is not safe to hold references over time.
- L411 _private function_ `template<typename EntryT> bool TrySet_Internal(FName ObjName, const EntryT& Obj)` — Store object of a named key, overwriting any existing object. Should only be called from within the simulation.
- L426 _private function_ `template<typename EntryT> bool TryGet_Internal(FName ObjName, EntryT& OutFoundValue) const`
- L440 _private function_ `template<typename EntryT> const EntryT* TryGetRef_Internal(FName ObjName) const`
- L456 _private function_ `template<typename EntryT> bool TrySet_Predictive(FName ObjName, const EntryT& Obj)` — Store object by a named key, overwriting any existing object. Should only be called from within the predicting simulation.
- L470 _private function_ `template<typename EntryT> bool TryGet_Predictive(FName ObjName, EntryT& OutFoundValue) const`
- L483 _private function_ `template<typename EntryT> const EntryT* TryGetRef_Predictive(FName ObjName) const`
- L497 _private function_ `BlackboardEntryBase* FindEntry(FName EntryName) const`
- L511 _public prototype_ `void BeginSimulationFrame(const FMoverTimeStep& PendingTimeStep);`
- L512 _public prototype_ `void EndSimulationFrame();`
- L515 _public prototype_ `void BeginRollback(const FMoverTimeStep& NewBaseTimeStep);` — NewBaseTimeStep represents the current time and the PENDING step that's next to be resimulated
- L516 _public prototype_ `void EndRollback();`
- L519 _public prototype_ `void BeginPredictionFrame(const FMoverTimeStep& PendingTimeStep);` — BeginPredictionFrame/EndPrediction: this is for predictive simulation that is temporary and can't rollback. Note there may be multiple calls to BeginPredictionFrame before a single call to EndPrediction.
- L520 _public prototype_ `void EndPrediction();` — Called at the end of ALL prediction frames
- L523 _private prototype_ `bool IsInSimulationThread() const;`
- L524 _private prototype_ `bool IsInPredictionThread() const;`
- L526 _private member_ `ERollbackBufferFlags BufferFlags = ERollbackBufferFlags::Prediction;`
- L528 _private member_ `TMap<FName, TUniquePtr<BlackboardEntryBase>> EntryMap;`
- L531 _private member_ `bool bIsSimulationInProgress = false;`
- L532 _private member_ `bool bIsResimulating = false;`
- L533 _private member_ `uint32 InProgressSimFrameThreadId = 0;`
- L535 _private member_ `bool bIsRollbackInProgress = false;`
- L536 _private member_ `uint32 InRollbackThreadId = 0;`
- L538 _private member_ `bool bIsPredictionInProgress = false;`
- L539 _private member_ `uint32 InPredictionThreadId = 0;`
- L541 _private member_ `EntryTimeStamp CurrentSimTimeStamp;` — this is the "committed" simulation time, and will lag behind InProgressSimTimeStamp while in the middle of a simulation frame
- L542 _private member_ `EntryTimeStamp InProgressSimTimeStamp;` — this is the sim time that's actively being used mid-simulation. It is only valid during a simulation step.

#### struct `URollbackBlackboard::EntrySettings`  
`struct EntrySettings`  
_L118-126_
- L120 _public member_ `EBlackboardSizingPolicy SizingPolicy = EBlackboardSizingPolicy::FixedDeclaredSize;`
- L121 _public member_ `EBlackboardPersistencePolicy PersistencePolicy = EBlackboardPersistencePolicy::Forever;`
- L122 _public member_ `EBlackboardRollbackPolicy RollbackPolicy = EBlackboardRollbackPolicy::InvalidatedOnRollback;`
- L124 _public member_ `uint32 FixedSize = 0;`
- L125 _public member_ `double MaxLifetimeSecs = -1.0;`

#### struct `URollbackBlackboard::EntryTimeStamp`  
`struct EntryTimeStamp`  
_L130-148_
- L132 _public function_ `EntryTimeStamp()`
- L133 _public function_ `EntryTimeStamp(double InTimeMs, uint32 InFrame) : TimeMs(InTimeMs), Frame(InFrame)`
- L135 _public member_ `double TimeMs = -1.0;`
- L136 _public member_ `uint32 Frame = 0;`
- L138 _public function_ `bool IsValid() const`
- L143 _public function_ `void Invalidate()`

#### enum `URollbackBlackboard::EEntryIndexType`  
`enum EEntryIndexType : uint8`  
_L150-155_
- L152 _public enumerator_ `External` — entry index for outside systems to read
- L153 _public enumerator_ `Internal` — entry index for in-simulation system to read/write
- L154 _public enumerator_ `Predictive` — entry index for a predicting system to read/write

#### struct `URollbackBlackboard::BlackboardEntryBase`  
`struct BlackboardEntryBase`  
_L158-194_
- desc: untyped base, so we can use entries of multiple types in a single-typed container
- L161 _public prototype_ `BlackboardEntryBase() = delete;`
- L162 _public prototype_ `BlackboardEntryBase(const EntrySettings& InSettings, uint32 BufferSize, ERollbackBufferFlags BufferFlags);`
- L164 _public function_ `virtual ~BlackboardEntryBase()`
- L168 _public function_ `void OnSimulationFrameEnd()`
- L175 _public prototype_ `void RollBack(uint32 NewPendingFrame);` — Note that NewPendingFrame means the frame that will now be re-simulated. So any existing entries with a Frame >= NewPendingFrame can be invalidated.
- L177 _public prototype_ `void InvalidatePredictiveState();`
- L180 _public prototype_ `static uint32 ComputeBufferSize(EBlackboardSizingPolicy InSizingPolicy, uint32 FixedBufferSize = -1);`
- L183 _protected prototype_ `bool CanReadEntryAtTime(const EntryTimeStamp& ReaderTimeStamp, EEntryIndexType IndexType) const;`
- L184 _protected prototype_ `bool CanReadEntryAtTime(const EntryTimeStamp& ReaderTimeStamp, const EntryTimeStamp& EntryTimeStamp) const;`
- L186 _protected function_ `virtual void ResetPredictiveElement()`
- L188 _protected member_ `EntrySettings Settings;`
- L190 _protected member_ `TRollbackCircularBuffer<EntryTimeStamp> Timestamps;`
- L192 _protected member_ `uint32 ExternalIdx;` — Indexes to the last entry on a committed frame
- L193 _protected member_ `uint32 InternalIdx;` — Indexes to where in-progress simulations should read/write (matches ExternalIdx when not mid-simulation, and advances if written during simulation)

#### struct `URollbackBlackboard::BlackboardEntry`  
`template<typename EntryT> struct BlackboardEntry : BlackboardEntryBase`  
_L197-341_
- inherits: `BlackboardEntryBase`
- L201 _private prototype_ `BlackboardEntry() = delete;` — disallow use of default constructor
- L206 _public function_ `BlackboardEntry(const EntrySettings& InSettings, uint32 InBufferSize, ERollbackBufferFlags InBufferFlags, const EntryT* OptionalInitialObj=nullptr) : BlackboardEntryBase(InSettings, InBufferSize, InBufferFlags) , EntryBuffer(InBufferSize, InBufferFlags), DefaultValue()` — TODO: consider what options need to be specified
- L222 _public function_ `void SetValueAtTime_External(const EntryT& Value, const EntryTimeStamp& TimeStamp)`
- L228 _public function_ `bool TryGetValueAtTime_External(const EntryTimeStamp& CurrentExternalTime, EntryT& ValueOut) const`
- L240 _public function_ `const EntryT* TryGetRefAtTime_External(const EntryTimeStamp& CurrentExternalTime) const` — TODO: Consider whether it's worthwhile to have this function... dangerous to let external folks hold onto references to internal storage, but may allow more efficient editing
- L250 _public function_ `bool TryGetValueAtTime_Internal(const EntryTimeStamp& InternalTime, EntryT& ValueOut) const`
- L261 _public function_ `const EntryT* TryGetRefAtTime_Internal(const EntryTimeStamp& InternalTime) const`
- L271 _public function_ `void SetValueAtTime_Internal(const EntryT& Value, const EntryTimeStamp& TimeStamp)`
- L279 _public function_ `bool TryGetValueAtTime_Predictive(const EntryTimeStamp& PredictiveReaderTime, EntryT& ValueOut) const`
- L302 _public function_ `const EntryT* TryGetRefAtTime_Predictive(const EntryTimeStamp& PredictiveReaderTime) const`
- L324 _public function_ `void SetValueAtTime_Predictive(const EntryT& Value, const EntryTimeStamp& TimeStamp)`
- L331 _public function_ `virtual void ResetPredictiveElement() override`
- L337 _public member_ `TRollbackCircularBuffer<EntryT> EntryBuffer;`
- L338 _public member_ `EntryT DefaultValue;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/RollbackBlackboardLibrary.h` (Public)


#### class `URollbackBlackboardLibrary`  
`class URollbackBlackboardLibrary : public UBlueprintFunctionLibrary`  
_L18-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: RollbackBlackboardLibrary: a collection of static functions to help working with a rollback blackboard
- L31 _public prototype_ `static URollbackBlackboard::EntrySettings MakeEventEntrySettings(int32 MaxHistoryCount);` — An 'event' entry is good for data that is rarely authored each frame and may be useful for some time into the future. These are commonly used to denote gameplay events that need to be referenced a short time later. Examples: - recording a jump apex's time & height, to be used upon landing to see how far a character fell - denoting a state like "was ducking" at the start of navigating under an obstacle, to be used later to restore the ducking behavior after clearing the obstacle For MaxHistoryCount, consider how many times this entry might change during your worst-case prediction window, which is typically 1000 milliseconds or less.
- L38 _public prototype_ `static URollbackBlackboard::EntrySettings MakeSingleFrameEntrySettings();` — Single-frame entries are good for data that only needs to be communicated between different parts of the movement sim during the current frame and has no use beyond that. Example: information about acceleration used in a mode's GenerateMove that you want to capture and include in the SyncState during SimulationTick
- L46 _public prototype_ `static URollbackBlackboard::EntrySettings MakeRollingEntrySettings();` — A 'rolling' entry is good for data that changes every frame. Examples: - a dynamic homing target location, or motion warping position, that is moving as we relate to it - information about animation state from an associated skeletal mesh

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/RollbackBlackboardWrappers.h` (Public)


#### struct `FRollbackBlackboardExternalWrapper`  
`struct FRollbackBlackboardExternalWrapper`  
_L17-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper class for external parties to access the blackboard. External parties = users outside of an active movement simulation such as animation and gameplay scripting
- L22 _public prototype_ `FRollbackBlackboardExternalWrapper(URollbackBlackboard& InBlackboard);`
- L23 _public prototype_ `FRollbackBlackboardExternalWrapper(const FRollbackBlackboardExternalWrapper& Other);`
- L25 _public prototype_ `FRollbackBlackboardExternalWrapper();` — Default constructor exists only for reflection / BP support.  Typically constructed with a blackboard or as a copy.
- L28 _public function_ `template<typename EntryT> bool CreateEntry(FName EntryName, const URollbackBlackboard::EntrySettings& InSettings)`
- L38 _public function_ `bool HasEntry(FName EntryName) const`
- L49 _public function_ `template<typename EntryT> bool TrySet(FName ObjName, const EntryT& Obj)`
- L60 _public function_ `template<typename EntryT> bool TryGet(FName ObjName, EntryT& OutFoundValue) const`
- L71 _public function_ `template<typename EntryT> const EntryT* TryGetRef(FName ObjName) const`
- L83 _private member_ `TObjectPtr<URollbackBlackboard> Blackboard = nullptr;` — `UPROPERTY()`

#### struct `FRollbackBlackboardSimWrapper`  
`struct FRollbackBlackboardSimWrapper`  
_L96-190_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper class for in-simulation access to the blackboard. This exposes otherwise private API, and redirects set/get operations to the in-simulation locations. This is what all movement mechanisms will interact with, including movement modes, layered moves, etc. This also supports a predictive mode, so the blackboard can be used and even temporarily written to, without affecting the true simulation's state or external parties. Users of this wrapper will not be aware whether it's part of a true movement sim or a predictive one.
- L101 _public prototype_ `FRollbackBlackboardSimWrapper(URollbackBlackboard& InBlackboard, bool bUsePredictiveMode = false);`
- L102 _public prototype_ `FRollbackBlackboardSimWrapper(const FRollbackBlackboardSimWrapper& Other);`
- L104 _public prototype_ `FRollbackBlackboardSimWrapper();` — Default constructor exists only for reflection / BP support. Typically constructed with a blackboard or as a copy.
- L107 _public function_ `template<typename EntryT> bool CreateEntry(FName EntryName, const URollbackBlackboard::EntrySettings& InSettings)`
- L117 _public function_ `bool HasEntry(FName EntryName) const`
- L128 _public function_ `template<typename EntryT> bool TrySet(FName ObjName, const EntryT& Obj)`
- L146 _public function_ `template<typename EntryT> bool TryGet(FName ObjName, EntryT& OutFoundValue) const`
- L164 _public function_ `template<typename EntryT> const EntryT* TryGetRef(FName ObjName) const`
- L186 _private member_ `TObjectPtr<URollbackBlackboard> Blackboard = nullptr;` — `UPROPERTY()`
- L189 _private member_ `bool bInPredictiveMode = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/RollbackCircularBuffer.h` (Public)


#### enum `ERollbackBufferFlags`  
`enum class ERollbackBufferFlags`  
_L8-12_
- L10 _public enumerator_ `None = 0`
- L11 _public enumerator_ `Prediction = (1 << 0)` — whether this buffer will allocate additional space for use with prediction

#### class `TRollbackCircularBuffer`  
`template<typename InElementType> class TRollbackCircularBuffer`  
_L25-171_
- desc: Circular buffer specialized for use with rollback simulations providing concurrent access between active simulation and external users, as well as extra space for predictive work that's temporary and to be discarded. This is based on TCircularBuffer's implementation. The size of the buffer is rounded up to the next power of two in order speed up indexing operations using a simple bit mask instead of the commonly used modulus operator that may be slow on some platforms.
- L28 _public typedef_ `using ElementType = InElementType;`
- L35 _public function_ `[[nodiscard]] explicit TRollbackCircularBuffer(uint32 Capacity, ERollbackBufferFlags Flags)` — Creates and initializes a new instance of the TRollbackCircularBuffer class. @param Capacity The number of elements that the buffer can store
- L63 _public function_ `[[nodiscard]] TRollbackCircularBuffer(uint32 Capacity, ERollbackBufferFlags Flags, const ElementType& InitialValue)` — Creates and initializes a new instance of the TRollbackCircularBuffer class. @param Capacity The number of elements that the buffer can store (will be rounded up to the next power of 2). @param InFlags @param InitialValue The initial value for the buffer's elements.
- L91 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT ElementType& operator[](uint32 Index)` — Returns the mutable element at the specified index. @param Index The index of the element to return.
- L99 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT ElementType& GetPredictiveElement()` — Returns the mutable predictive element. Only valid if the buffer was created with prediction supported.
- L111 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const ElementType& operator[](uint32 Index) const` — Returns the immutable element at the specified index. @param Index The index of the element to return.
- L120 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT const ElementType& GetPredictiveElement() const` — Returns the immutable predictive element. Only valid if the buffer was created with prediction supported.
- L134 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT uint32 Capacity() const` — Returns the number of elements that the buffer can naturally hold. @return Buffer capacity.
- L145 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT uint32 GetNextIndex(uint32 CurrentIndex) const` — Calculates the index that follows the given index. @param CurrentIndex The current index. @return The next index.
- L156 _public function_ `[[nodiscard]] UE_FORCEINLINE_HINT uint32 GetPreviousIndex(uint32 CurrentIndex) const` — Calculates the index previous to the given index. @param CurrentIndex The current index. @return The previous index.
- L164 _private member_ `uint32 IndexMask;` — Holds the mask for indexing the buffer's elements. This mask covers only the non-predicted elements. The predictive element in the array will not be accessible.
- L167 _private member_ `uint32 NonPredictedCapacity;` — This is the true number of usable element slots. If prediction is enabled, this will be smaller than Elements.Num()
- L170 _private member_ `TArray<ElementType> Elements;` — Holds the buffer's elements. If prediction is enabled, this will have 1 additional element at the end of the array.

### `Plugins/Experimental/Mover/Source/Mover/Public/MoveLibrary/WaterMovementUtils.h` (Public)


#### struct `FWaterMoveParams`  
`struct FWaterMoveParams`  
_L18-66_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for ComputeControlledWaterMove()
- L23 _public member_ `EMoveInputType MoveInputType = EMoveInputType::DirectionalIntent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L26 _public member_ `FVector MoveInput = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L29 _public member_ `FRotator OrientationIntent = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L32 _public member_ `FVector PriorVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L35 _public member_ `FRotator PriorOrientation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L38 _public member_ `float MaxSpeed = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L41 _public member_ `float Acceleration = 4000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L44 _public member_ `float Deceleration = 8000.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L47 _public member_ `float Friction = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L50 _public member_ `float TurningRate = 500.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L53 _public member_ `float TurningBoost = 8.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L56 _public member_ `float DeltaSeconds = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L59 _public member_ `FVector MoveAcceleration = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L62 _public member_ `float MoveSpeed = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L65 _public member_ `FQuat WorldToGravityQuat = FQuat::Identity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### struct `FWaterFlowSplineData`  
`struct FWaterFlowSplineData`  
_L70-117_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about the water volume and its interaction with the pawn used in calculating swimming movement
- L74 _public function_ `FWaterFlowSplineData()`
- L79 _public member_ `float SplineInputKey;`
- L80 _public member_ `float ImmersionDepth;`
- L81 _public member_ `float ImmersionPercent;`
- L82 _public member_ `float WaterDepth;`
- L83 _public member_ `float WaterVelocityDepthMultiplier;`
- L84 _public member_ `float WaveAttenuationFactor;`
- L85 _public member_ `float WaveReferenceTime;`
- L86 _public member_ `FVector RawWaterVelocity;`
- L87 _public member_ `FVector WaterVelocity;`
- L88 _public member_ `FVector PlayerRelativeVelocityToWater;`
- L89 _public member_ `FVector WaterSurfaceLocation;`
- L90 _public member_ `FVector WaterSurfaceNormal;`
- L91 _public member_ `FVector WaterSurfaceOffset;`
- L92 _public member_ `FVector WaterPlaneLocation;`
- L93 _public member_ `FVector WaterPlaneNormal;`
- L94 _public member_ `TWeakObjectPtr<class AWaterBody> WaterBody;`
- L96 _public function_ `bool IsValid() const`
- L98 _public function_ `void Reset()`

#### struct `FWaterCheckResult`  
`struct FWaterCheckResult`  
_L121-156_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about the overlapping volume typically used for swimming
- L127 _public member_ `uint32 bSwimmableVolume : 1;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterVolume)` — True if the hit found a valid swimmable volume.
- L131 _public member_ `FHitResult HitResult;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterVolume)` — Hit result of the test that found a volume. Includes more specific data about the point of impact and surface normal at that point.
- L135 _public member_ `FWaterFlowSplineData WaterSplineData;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = CharacterVolume)` — Water Spline data to be used in calculating swimming movement, FX, etc.
- L138 _public function_ `FWaterCheckResult() : bSwimmableVolume(false) , HitResult(-1.f) , WaterSplineData()`
- L146 _public function_ `bool IsSwimmableVolume() const` — Returns true if the volume result hit a walkable surface.
- L151 _public function_ `void Clear()`

#### struct `FUpdateWaterSplineDataParams`  
`struct FUpdateWaterSplineDataParams`  
_L160-181_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters for Updating WaterSplineData
- L165 _public member_ `float TargetImmersionDepth = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L168 _public member_ `float WaterVelocityDepthForMax = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L171 _public member_ `float WaterVelocityMinMultiplier = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L174 _public member_ `FVector PlayerVelocity = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L177 _public member_ `FVector PlayerLocation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`
- L180 _public member_ `float CapsuleHalfHeight = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)`

#### class `UWaterMovementUtils`  
`class UWaterMovementUtils : public UBlueprintFunctionLibrary`  
_L187-199_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: WaterMovementUtils: a collection of stateless static BP-accessible functions for a variety of water movement-related operations
- L194 _public prototype_ `static FProposedMove ComputeControlledWaterMove(const FWaterMoveParams& InParams);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Generate a new movement based on move/orientation intents and the prior state for the swimming move
- L198 _public prototype_ `static void UpdateWaterSplineData(const FUpdateWaterSplineDataParams& UpdateWaterSplineDataParams, UPARAM(ref) FWaterCheckResult& WaterCheckResult);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Updates the water spline data used in calculated swimming movement

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MovementMode.h` (Public)


#### class `UMovementSettingsInterface`  
`class UMovementSettingsInterface : public UInterface`  
_L23-26_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`
- desc: UMovementSettingsInterface: interface that must be implemented for any settings object to be shared between modes

#### class `IMovementSettingsInterface`  
`class IMovementSettingsInterface`  
_L28-34_
- L33 _public prototype_ `virtual FString GetDisplayName() const = 0;`

#### class `UBaseMovementMode`  
`class UBaseMovementMode : public UObject`  
_L40-144_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UObject`
- desc: Base class for all movement modes, exposing simulation update methods for both C++ and blueprint extension
- L45 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L47 _public prototype_ `virtual void OnRegistered(const FName ModeName, const FMoverSimContext& SimContext);`
- L48 _public prototype_ `virtual void OnUnregistered(const FMoverSimContext& SimContext);`
- L51 _public prototype_ `virtual void Activate(const FMoverEventContext& Context, FName PrevModeName, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, FMoverSyncState* OutSyncState, FMoverAuxStateContext* OutAuxState);` — These functions are called immediately within the simulation. If using async movement, it may be on a worker thread and unsafe to perform some operations on external objects.
- L52 _public prototype_ `virtual void Deactivate(const FMoverEventContext& Context, FName NextModeName, const FMoverSimContext& SimContext);`
- L56 _public prototype_ `virtual void Activate_External(const FMoverEventContext& Context);` — These functions are called when the sync state is changed on the game thread and a new mode is activated/deactivated
- L57 _public prototype_ `virtual void Deactivate_External(const FMoverEventContext& Context);`
- L60 _public prototype_ `void GenerateMove(const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, UPARAM(ref) FProposedMove& OutProposedMove) const;` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Generate Move", ForceAsFunction))`
- L63 _public prototype_ `void SimulationTick(const FSimulationTickParams& Params, UPARAM(ref) FMoverTickEndData& OutputState);` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Simulation Tick", ForceAsFunction))`
- L67 _public prototype_ `UMoverComponent* K2_GetMoverComponent() const;` — `UFUNCTION(BlueprintCallable, Category=Mover, meta=(DisplayName="Get Mover Component", ScriptName = GetMoverComponent))` — Gets the MoverComponent that owns this movement mode
- L73 _public function_ `template<typename MoverT = UMoverComponent UE_REQUIRES(std::is_base_of_v<UMoverComponent, MoverT>)> MoverT* GetMoverComponent() const` — Gets the outer mover component of the indicated type. Does not check on the type or the presence of the MoverComp outer. Safe to call on CDOs.
- L82 _public function_ `template<typename MoverT = UMoverComponent UE_REQUIRES(std::is_base_of_v<UMoverComponent, MoverT>)> MoverT& GetMoverComponentChecked() const` — Gets the outer mover component of the indicated type, checked for validity.
- L95 _public prototype_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const;` — Check Movement Mode for a gameplay tag. @param TagToFind			Tag to check on the Mover systems @param bExactMatch		If true, the tag has to be exactly present, if false then TagToFind will include it's parent tags while matching @return True if the TagToFind was found
- L98 _public prototype_ `virtual void GetGameplayTags(FGameplayTagContainer& InOutTags) const;` — Adds all gameplay tags currently active on this movement mode to InOutTags.
- L101 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L106 _public member_ `TArray<TSubclassOf<UObject>> SharedSettingsClasses;` — `UPROPERTY(EditDefaultsOnly, Category = Mover, meta = (MustImplement = "/Script/Mover.MovementSettingsInterface"))` — Settings object type that this mode depends on. May be shared with other movement modes. When the mode is added to a Mover Component, it will create a shared instance of this settings class.
- L110 _public member_ `TArray<TObjectPtr<UBaseMovementModeTransition>> Transitions;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = Mover, meta = (FullyExpand = true))` — Transition checks for the current mode. Evaluated in order, stopping at the first successful transition check
- L114 _public member_ `FGameplayTagContainer GameplayTags;` — `UPROPERTY(EditDefaultsOnly, Category = Mover)` — A list of gameplay tags associated with this movement mode
- L121 _public member_ `bool bSupportsAsync = false;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mover)` — Whether this movement mode supports being part of an asynchronous movement simulation (running concurrently with the gameplay thread) Specifically for the GenerateMove and SimulationTick functions
- L125 _protected prototype_ `void K2_OnActivated();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Activated", ScriptName = "OnActivated"))`
- L128 _protected prototype_ `void K2_OnDeactivated();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Deactivated", ScriptName = "OnDeactivated"))`
- L131 _protected prototype_ `void K2_OnRegistered(const FName ModeName);` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Registered", ScriptName = "OnRegistered"))`
- L134 _protected prototype_ `void K2_OnUnregistered();` — `UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Unregistered", ScriptName = "OnUnregistered"))`
- L137 _protected function_ `virtual void OnActivate() final` — `UE_DEPRECATED(5.6, "OnActivate() has been renamed to Activate().")`
- L139 _protected function_ `virtual void OnDeactivate() final` — `UE_DEPRECATED(5.6, "OnDeactivate() has been renamed to Deactivate().")`
- L141 _protected function_ `virtual void OnGenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FProposedMove& OutProposedMove) const final` — `UE_DEPRECATED(5.6, "OnGenerateMove() has been replaced with a GenerateMove() BlueprintNativeEvent. Rename your override to GenerateMove_Implementation().")`
- L143 _protected function_ `virtual void OnSimulationTick(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) final` — `UE_DEPRECATED(5.6, "OnSimulationTick() has been replaced with a SimulationTick() BlueprintNativeEvent. Rename your override to SimulationTick_Implementation().")`

#### class `UNullMovementMode`  
`class UNullMovementMode : public UBaseMovementMode`  
_L150-158_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UBaseMovementMode`
- desc: NullMovementMode: a default do-nothing mode used as a placeholder when no other mode is active
- L155 _public prototype_ `virtual void SimulationTick_Implementation(const FSimulationTickParams& Params, FMoverTickEndData& OutputState) override;`
- L157 _public member_ `const static FName NullModeName;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MovementModeStateMachine.h` (Public)


#### class `UMovementModeStateMachine`  
`class UMovementModeStateMachine : public UObject`  
_L27-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: - Any movement modes registered are co-owned by the state machine - There is always an active mode, falling back to a do-nothing 'null' mode - Queuing a mode that is already active will cause it to exit and re-enter - Modes only switch during simulation tick
- L32 _public prototype_ `virtual void BeginDestroy() override;`
- L34 _public prototype_ `void RegisterMovementMode(FName ModeName, TObjectPtr<UBaseMovementMode> Mode, bool bIsDefaultMode);`
- L35 _public prototype_ `void RegisterMovementMode(FName ModeName, TSubclassOf<UBaseMovementMode> ModeType, bool bIsDefaultMode);`
- L37 _public prototype_ `void UnregisterMovementMode(FName ModeName);`
- L38 _public prototype_ `void ClearAllMovementModes();`
- L40 _public prototype_ `void RegisterGlobalTransition(TObjectPtr<UBaseMovementModeTransition> Transition);`
- L41 _public prototype_ `void UnregisterGlobalTransition(TObjectPtr<UBaseMovementModeTransition> Transition);`
- L42 _public prototype_ `void ClearAllGlobalTransitions();`
- L45 _public prototype_ `void SetSimulation(UMoverSimulation& InSimulation);` — TODO: Warning: this function will be removed once the full simulation context (including blackboard) comes in as part of the Simulation**** function params
- L47 _public prototype_ `void SetDefaultMode(FName NewDefaultModeName);`
- L49 _public prototype_ `void QueueNextMode(FName DesiredNextModeName, bool bShouldReenter=false);`
- L50 _public prototype_ `void SetModeImmediately(FName DesiredModeName, bool bShouldReenter=false);`
- L51 _public prototype_ `void ClearQueuedMode();`
- L53 _public prototype_ `void OnSimulationTick(USceneComponent* UpdatedComponent, UPrimitiveComponent* UpdatedPrimitive, UMoverBlackboard* SimBlackboard, const FMoverSimContext& SimContext, const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, FMoverTickEndData& OutputState);`
- L54 _public prototype_ `void OnSimulationPreRollback(const FMoverSyncState* InvalidSyncState, const FMoverSyncState* SyncState, const FMoverAuxStateContext* InvalidAuxState, const FMoverAuxStateContext* AuxState, const FMoverTimeStep& NewBaseTimeStep);`
- L55 _public prototype_ `void OnSimulationRollback(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState, const FMoverTimeStep& NewBaseTimeStep);`
- L57 _public function_ `FName GetCurrentModeName() const`
- L58 _public prototype_ `FName GetQueuedModeName() const;`
- L60 _public prototype_ `const UBaseMovementMode* GetCurrentMode() const;`
- L62 _public prototype_ `const UBaseMovementMode* FindMovementMode(FName ModeName) const;`
- L64 _public prototype_ `void QueueActiveLayeredMove(const TSharedPtr<FLayeredMoveInstance>& LayeredMove);`
- L66 _public prototype_ `FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier);`
- L68 _public prototype_ `void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle);`
- L70 _public prototype_ `const FMovementModifierBase* FindQueuedModifier(FMovementModifierHandle ModifierHandle) const;`
- L71 _public prototype_ `const FMovementModifierBase* FindQueuedModifierByType(const UScriptStruct* ModifierType) const;`
- L73 _public prototype_ `void CancelFeaturesWithTag(FGameplayTag TagToCancel, bool bRequireExactMatch=false);`
- L74 _public prototype_ `bool HasFeaturesWithTag(FGameplayTag TagToMatch, bool bRequireExactMatch = false) const;`
- L77 _public prototype_ `void QueueInstantMovementEffect_Internal(const FScheduledInstantMovementEffect& ScheduledInstantMovementEffect);` — This function is meant to be used only in async mode on a worker thread, not on the game thread
- L80 _public prototype_ `void QueueLayeredMove_Internal(const FScheduledLayeredMove& ScheduledLayeredMove);` — This function is meant to be used only in async mode on a worker thread, not on the game thread
- L83 _protected prototype_ `void QueueInstantMovementEffect(const FScheduledInstantMovementEffect& ScheduledInstantMovementEffect);`
- L84 _protected prototype_ `void QueueInstantMovementEffects(const TArray<FScheduledInstantMovementEffect>& ScheduledInstantMovementEffects);`
- L86 _protected prototype_ `void QueueLayeredMove(const FScheduledLayeredMove& ScheduledLayeredMove);`
- L87 _protected prototype_ `void QueueLayeredMoves(const TArray<FScheduledLayeredMove>& ScheduledLayeredMoves);`
- L89 _protected prototype_ `void ProcessEvents(const TArray<TSharedPtr<FMoverSimulationEventData>>& InEvents);`
- L90 _protected prototype_ `virtual void ProcessSimulationEvent(const FMoverSimulationEventData& EventData);`
- L92 _protected prototype_ `void QueueNextModeInternal(FName DesiredNextModeName, bool bShouldReenter=false, bool bIsFromRollback=false);`
- L93 _protected prototype_ `void SetModeImmediatelyInternal(FName DesiredModeName, bool bShouldReenter=false, bool bIsFromRollback=false);`
- L95 _protected prototype_ `virtual void PostInitProperties() override;`
- L98 _protected member_ `TMap<FName, TObjectPtr<UBaseMovementMode>> Modes;` — `UPROPERTY()`
- L99 _protected member_ `TArray<TObjectPtr<UBaseMovementModeTransition>> GlobalTransitions;`
- L102 _protected member_ `TObjectPtr<UImmediateMovementModeTransition> QueuedModeTransition;` — `UPROPERTY(Transient)`
- L105 _protected member_ `TObjectPtr<UMoverSimulation> Simulation;` — `UPROPERTY(Transient)`
- L107 _protected member_ `FName DefaultModeName = NAME_None;`
- L108 _protected member_ `FName CurrentModeName = NAME_None;`
- L111 _protected member_ `FMoverTimeStep CurrentBaseTimeStep;` — Represents the current sim time that's passed, and the next frame number that's next to be simulated.
- L114 _protected member_ `TArray<FScheduledLayeredMove> QueuedLayeredMoves;` — Moves that are queued to be added to the simulation when their scheduled time has come (earliest is at the start of the next sim subtick). Access covered by lock.
- L117 _protected member_ `TArray<TSharedPtr<FLayeredMoveInstance>> QueuedLayeredMoveInstances;` — Moves that are queued to be added to the simulation at the start of the next sim subtick. Access covered by lock.
- L120 _protected member_ `TArray<FScheduledInstantMovementEffect> QueuedInstantEffects;` — Effects that are queued to be applied to the simulation when their scheduled time has come (earliest is at the start of the next sim subtick, or at the end of this tick).  Access covered by lock.
- L123 _protected member_ `TArray<TSharedPtr<FMovementModifierBase>> QueuedMovementModifiers;` — Modifiers that are queued to be added to the simulation at the start of the next sim subtick. Access covered by lock.
- L126 _protected member_ `TArray<FMovementModifierHandle> ModifiersToCancel;` — Modifiers that are to be canceled at the start of the next sim subtick.  Access covered by lock.
- L129 _protected member_ `TArray<TPair<FGameplayTag, bool>> TagCancellationRequests;` — Tags that are used to cancel any matching movement features (modifiers, layered moves, etc). Access covered by lock.
- L132 _protected member_ `FMoverTickStartData WorkingSubstepStartData;` — Internal-use-only tick data structs, for efficiency since they typically have the same contents from frame to frame
- L133 _protected member_ `FSimulationTickParams WorkingSimTickParams;`
- L134 _protected member_ `FMoverTickEndData* WorkingSimTickEndData = nullptr;` — Only valid during OnSimulationTick and null otherwise
- L138 _private member_ `mutable FTransactionallySafeRWLock LayeredMoveQueueLock;` — Locks for thread safety on queueing mechanisms
- L139 _private member_ `mutable FTransactionallySafeRWLock InstantEffectsQueueLock;`
- L140 _private member_ `mutable FTransactionallySafeRWLock ModifiersQueueLock;`
- L141 _private member_ `mutable FTransactionallySafeRWLock ModifierCancelQueueLock;`
- L142 _private member_ `mutable FTransactionallySafeRWLock TagCancellationRequestsLock;`
- L144 _private prototype_ `void ConstructDefaultModes();`
- L145 _private prototype_ `void AdvanceToNextMode();`
- L146 _private prototype_ `void FlushQueuedMovesToGroup(const FMoverTimeStep& TimeStep, FLayeredMoveGroup& Group);`
- L148 _private prototype_ `void ActivateQueuedMoves(FLayeredMoveInstanceGroup& Group);` — Flushes queued ActiveLayeredMoves to FLayeredMoveInstanceGroup for this frame
- L149 _private prototype_ `void FlushQueuedModifiersToGroup(FMovementModifierGroup& ModifierGroup);`
- L150 _private prototype_ `void FlushModifierCancellationsToGroup(FMovementModifierGroup& ActiveModifierGroup);`
- L151 _private prototype_ `void FlushTagCancellationsToSyncState(FMoverSyncState& SyncState);`
- L152 _private prototype_ `void RollbackModifiers(const FMoverSyncState* InvalidSyncState, const FMoverSyncState* SyncState, const FMoverAuxStateContext* InvalidAuxState, const FMoverAuxStateContext* AuxState);`
- L153 _private prototype_ `void RollBackQueuedInstantMovementEffects(const FMoverTimeStep& NewBaseTimeStep);`
- L154 _private prototype_ `void RollBackQueuedLayeredMoves(const FMoverTimeStep& NewBaseTimeStep);`
- L155 _private prototype_ `bool HasAnyInstantEffectsQueued() const;`
- L156 _private prototype_ `bool ApplyInstantEffects(FApplyMovementEffectParams& ApplyEffectParams, FMoverSyncState& OutputState);`
- L157 _private prototype_ `bool UpdateWorkingStateFromSyncState(FMoverSyncState& OutputState);`
- L158 _private prototype_ `FMoverSimContext GetSimContext() const;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MovementModeTransition.h` (Public)


#### struct `FTransitionEvalResult`  
`struct FTransitionEvalResult`  
_L18-31_
- reflection: `USTRUCT(BlueprintType)`
- desc: Results from a movement mode transition evaluation
- L22 _public function_ `FTransitionEvalResult()`
- L23 _public function_ `FTransitionEvalResult(FName InNextMode)`
- L27 _public member_ `FName NextMode = NAME_None;` — `UPROPERTY(BlueprintReadWrite, Category=Mover)` — Mode name that should be transitioned to. NAME_None indicates no transition.
- L30 _public member_ `static const FTransitionEvalResult NoTransition;`

#### class `UBaseMovementModeTransition`  
`class UBaseMovementModeTransition : public UObject`  
_L38-106_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)`
- inherits: `UObject`
- desc: Base class for all transitions
- L43 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L45 _public prototype_ `virtual void OnRegistered();`
- L46 _public prototype_ `virtual void OnUnregistered();`
- L50 _public prototype_ `UMoverComponent* K2_GetMoverComponent() const;` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (DisplayName = "Get Mover Component"))` — Gets the MoverComponent that ultimately owns this transition
- L53 _public function_ `template<typename MoverT = UMoverComponent UE_REQUIRES(std::is_base_of_v<UMoverComponent, MoverT>)> MoverT* GetMoverComponent() const`
- L59 _public function_ `template<typename MoverT = UMoverComponent UE_REQUIRES(std::is_base_of_v<UMoverComponent, MoverT>)> MoverT& GetMoverComponentChecked() const`
- L65 _public prototype_ `FTransitionEvalResult Evaluate(const FSimulationTickParams& Params) const;` — `UFUNCTION(BlueprintNativeEvent, Category = MovementModeTransition)`
- L68 _public prototype_ `void Trigger(const FSimulationTickParams& Params);` — `UFUNCTION(BlueprintNativeEvent, Category = MovementModeTransition)`
- L71 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L76 _public member_ `TArray<TSubclassOf<UObject>> SharedSettingsClasses;` — `UPROPERTY(EditDefaultsOnly, Category = Mover, meta = (MustImplement = "/Script/Mover.MovementSettingsInterface"))` — Settings object type that this mode depends on. May be shared with other transitions and movement modes. When the transition is added to a Mover Component, it will create a shared instance of this settings class.
- L80 _public member_ `uint8 bAllowModeReentry : 1 = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mover)` — Whether this transition should reenter a mode if it evaluates true and wants to transition into a mode the actor is already in
- L86 _public member_ `uint8 bFirstSubStepOnly : 1 = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mover)` — Whether this transition should only apply to the first step of the update. If true, modes reached after transitions or mode changes in the current update will not consider this transition
- L93 _public member_ `uint8 bSupportsAsync : 1 = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Mover)` — Whether this movement mode transition supports being part of an asynchronous movement simulation (running concurrently with the gameplay thread) Specifically for the Evaluate and Trigger functions
- L97 _protected prototype_ `void K2_OnRegistered();` — `UFUNCTION(BlueprintImplementableEvent, Category = MovementModeTransition, meta = (DisplayName = "On Registered", ScriptName = "OnRegistered"))`
- L100 _protected prototype_ `void K2_OnUnregistered();` — `UFUNCTION(BlueprintImplementableEvent, Category = MovementModeTransition, meta = (DisplayName = "On Unregistered", ScriptName = "OnUnregistered"))`
- L103 _protected function_ `virtual FTransitionEvalResult OnEvaluate(const FSimulationTickParams& Params) const final` — `UE_DEPRECATED(5.6, "OnEvaluate() has been replaced with an Evaluate() BlueprintNativeEvent. Rename your override to Evaluate_Implementation().")`
- L105 _protected function_ `virtual void OnTrigger(const FSimulationTickParams& Params) final` — `UE_DEPRECATED(5.6, "OnTrigger() has been replaced with a Trigger() BlueprintNativeEvent. Rename your override to Trigger_Implementation().")`

#### class `UImmediateMovementModeTransition`  
`class UImmediateMovementModeTransition : public UBaseMovementModeTransition`  
_L112-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseMovementModeTransition`
- desc: Simple transition that evaluates true if a "next mode" is set. Used internally only by the Mover plugin.
- L117 _public prototype_ `virtual FTransitionEvalResult Evaluate_Implementation(const FSimulationTickParams& Params) const override;`
- L118 _public prototype_ `virtual void Trigger_Implementation(const FSimulationTickParams& Params) override;`
- L120 _public function_ `bool IsSet() const`
- L121 _public prototype_ `void SetNextMode(FName DesiredModeName, bool bShouldReenter=false, bool bIsFromRollback=false);`
- L122 _public prototype_ `void Clear();`
- L124 _public function_ `FName GetNextModeName() const`
- L125 _public function_ `bool ShouldReenter() const`
- L126 _public function_ `bool IsCausedByRollback() const`
- L129 _private member_ `FName NextMode = NAME_None;`
- L130 _private member_ `uint8 bIsCausedByRollback : 1 = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MovementModifier.h` (Public)


#### struct `FMovementModifierHandle`  
`struct FMovementModifierHandle`  
_L26-70_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to identify movement modifiers.
- L30 _public function_ `FMovementModifierHandle() : Handle(0)`
- L35 _public function_ `FMovementModifierHandle(MODIFIER_HANDLE_TYPE InHandle) : Handle(InHandle)`
- L41 _public prototype_ `void GenerateHandle();` — Creates a new handle
- L43 _public function_ `bool operator==(const FMovementModifierHandle& Other) const`
- L48 _public function_ `bool operator!=(const FMovementModifierHandle& Other) const`
- L53 _public function_ `FString ToString() const`
- L58 _public function_ `bool IsValid() const`
- L63 _public function_ `void Invalidate()`
- L69 _private member_ `MODIFIER_HANDLE_TYPE Handle;`

#### struct `FMovementModifierParams_Async`  
`struct FMovementModifierParams_Async`  
_L72-91_
- L74 _public function_ `FMovementModifierParams_Async(UMoverSimulation* InSimulation, const FMoverSyncState* InSyncState, const FMoverTimeStep* InTimeStep) : Simulation(InSimulation) , SyncState(InSyncState) , TimeStep(InTimeStep)`
- L81 _public prototype_ `FMovementModifierParams_Async() = delete;`
- L83 _public function_ `bool IsValid() const`
- L88 _public member_ `UMoverSimulation* Simulation = nullptr;`
- L89 _public member_ `const FMoverSyncState* SyncState = nullptr;`
- L90 _public member_ `const FMoverTimeStep* TimeStep = nullptr;`

#### struct `FMovementModifierBase`  
`struct FMovementModifierBase`  
_L103-209_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: Movement Modifier: Used to apply changes that indirectly influence the movement simulation, without proposing or executing any movement, but still in sync with the sim. Example usages: changing groups of settings, movement mode re-mappings, etc. Note: Currently mover expects to only have one type of modifier active at a time. This can be fixed by extending the Matches function to check more than just type, but make sure anything used to compare is synced through the NetSerialize function.
- L107 _public prototype_ `FMovementModifierBase();`
- L108 _public prototype_ `virtual ~FMovementModifierBase() = default;`
- L112 _public member_ `float DurationMs;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — This modifier will expire after a set amount of time if > 0. If 0, it will be ticked only once, regardless of time step. It will need to be manually ended if < 0.
- L116 _public member_ `double StartSimTimeMs;` — `UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = Mover)` — The simulation time this move first ticked (< 0 means it hasn't started yet)
- L119 _public function_ `virtual void OnStart(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState)` — Fired when this modifier is activated.
- L122 _public function_ `virtual void OnEnd(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState)` — Fired when this modifier is deactivated.
- L127 _public function_ `virtual void OnPreMovement(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep)` — Fired just before a movement Substep
- L130 _public function_ `virtual void OnPostMovement(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState)` — Fired after a movement Substep
- L133 _public prototype_ `void StartModifier(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — Kicks off this modifier, allowing any initialization to occur.
- L136 _public prototype_ `void EndModifier(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — Ends this move, allowing any cleanup to occur.
- L139 _public prototype_ `virtual bool IsFinished(double CurrentSimTimeMs) const;` — Runtime query whether this modifier is finished and can be destroyed. The default implementation is based on DurationMs.
- L147 _public function_ `virtual void OnStart_Async(const FMovementModifierParams_Async& Params)` — The async API is used by the async friendly mover simulation class which is currently implemented in ChaosMover for async physics support. The standard Mover update does not currently require these async functions to be implemented
- L148 _public function_ `virtual void OnEnd_Async(const FMovementModifierParams_Async& Params)`
- L149 _public function_ `virtual void OnPreMovement_Async(const FMovementModifierParams_Async& Params)`
- L150 _public function_ `virtual void OnPostMovement_Async(const FMovementModifierParams_Async& Params)`
- L152 _public prototype_ `void StartModifier_Async(const FMovementModifierParams_Async& Params);`
- L153 _public prototype_ `void EndModifier_Async(const FMovementModifierParams_Async& Params);`
- L159 _public prototype_ `virtual FMovementModifierBase* Clone() const;` — @return newly allocated copy of this FMovementModifier. Must be overridden by child classes
- L161 _public prototype_ `virtual void NetSerialize(FArchive& Ar);`
- L163 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;`
- L165 _public prototype_ `virtual FString ToSimpleString() const;`
- L167 _public function_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector)`
- L174 _public prototype_ `virtual bool Matches(const FMovementModifierBase* Other) const;` — Used to compare modifiers and check if they are the same instance of modifiers. Doesn't need to be overridden but more specific data to match is best Note: Current default implementation only checks type and nothing else.
- L176 _public prototype_ `FMovementModifierHandle GetHandle() const;`
- L178 _public prototype_ `void GenerateHandle();`
- L185 _public prototype_ `void OverwriteHandleIfInvalid(const FMovementModifierHandle& ValidModifierHandle);` — Used to write to a valid handle to a invalid handle Currently used to write a local handle to modifiers that were added from a rollback so they don't have a handle yet This is done to avoid queueing a modifier again as a local client applies potential input
- L195 _public function_ `virtual bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const` — Check modifier for a gameplay tag. @param TagToFind			Tag to check on the Mover systems @param bExactMatch		If true, the tag has to be exactly present, if false then TagToFind will include it's parent tags while matching @return True if the TagToFind was found
- L201 _public function_ `virtual void GetGameplayTags(FGameplayTagContainer& InOutTags) const` — Adds all gameplay tags currently active on this modifier to InOutTags.
- L208 _protected member_ `FMovementModifierHandle LocalModifierHandle;` — `UPROPERTY()` — Modifier handle local to this client or server instance. Used to cancel or query for a active/queued modifier.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FMovementModifierBase > : public TStructOpsTypeTraitsBase2< FMovementModifierBase >`  
_L212-219_
- inherits: `TStructOpsTypeTraitsBase2<FMovementModifierBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L215-218_

#### struct `FMovementModifierGroup`  
`struct FMovementModifierGroup`  
_L224-291_
- reflection: `USTRUCT(BlueprintType)`
- desc: A collection of movement modifiers affecting a movable actor
- L228 _public function_ `FMovementModifierGroup()`
- L230 _public function_ `bool HasAnyMoves() const`
- L233 _public prototype_ `void NetSerialize(FArchive& Ar, uint8 MaxNumModifiersToSerialize = MAX_uint8);` — Serialize all modifiers and their states for this group
- L235 _public prototype_ `void QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier);`
- L237 _public prototype_ `void CancelModifierFromHandle(const FMovementModifierHandle& HandleToCancel);`
- L238 _public prototype_ `void CancelModifiersByTag(FGameplayTag Tag, bool bRequiresExactMatch=false);`
- L241 _public prototype_ `TArray<TSharedPtr<FMovementModifierBase>> GenerateActiveModifiers(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — Generates active modifier list (by calling FlushModifierArrays) and returns the an array of all currently active modifiers
- L243 _public prototype_ `TArray<TSharedPtr<FMovementModifierBase>> GenerateActiveModifiers_Async(const FMovementModifierParams_Async& Params);`
- L246 _public prototype_ `FMovementModifierGroup& operator=(const FMovementModifierGroup& Other);` — Copy operator - deep copy so it can be used for archiving/saving off moves
- L249 _public prototype_ `bool operator==(const FMovementModifierGroup& Other) const;` — Comparison operator - needs matching modifier along with identical states in those structs
- L252 _public prototype_ `bool operator!=(const FMovementModifierGroup& Other) const;` — Comparison operator
- L255 _public prototype_ `bool HasSameContents(const FMovementModifierGroup& Other) const;` — Checks only whether there are matching modifiers, but NOT necessarily identical states of each one
- L258 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector) const;` — Exposes references to GC system
- L261 _public prototype_ `FString ToSimpleString() const;` — Get a simplified string representation of this group. Typically for debugging.
- L264 _public prototype_ `TArray<TSharedPtr<FMovementModifierBase>>::TConstIterator GetActiveModifiersIterator() const;` — Const access to active moves
- L267 _public prototype_ `TArray<TSharedPtr<FMovementModifierBase>>::TConstIterator GetQueuedModifiersIterator() const;` — Const access to queued moves
- L270 _public prototype_ `void Reset();` — Clears active and queued modifiers
- L273 _public prototype_ `bool ShouldReconcile(const FMovementModifierGroup& Other) const;` — Whether this modifier should reconcile with the authority state
- L277 _protected member_ `TArray< TSharedPtr<FMovementModifierBase> > ActiveModifiers;` — Movement modifiers that are currently active in this group
- L280 _protected member_ `TArray< TSharedPtr<FMovementModifierBase> > QueuedModifiers;` — Movement modifiers that are queued to become active next sim frame
- L283 _protected prototype_ `void FlushModifierArrays(UMoverComponent* MoverComp, const FMoverTimeStep& TimeStep, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — Clears out any finished or invalid modifiers and adds any queued modifiers to the active modifiers
- L285 _protected prototype_ `void FlushModifierArrays_Async(const FMovementModifierParams_Async& Params);`
- L288 _protected prototype_ `static void NetSerializeMovementModifierArray(FArchive& Ar, TArray< TSharedPtr<FMovementModifierBase> >& ModifierArray, uint8 MaxNumModifiersToSerialize = MAX_uint8);` — Helper function for serializing array of movement modifiers

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovementModifierGroup> : public TStructOpsTypeTraitsBase2<FMovementModifierGroup>`  
_L295-304_
- inherits: `TStructOpsTypeTraitsBase2<FMovementModifierGroup>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L298-303_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L18 _macro_ `#define MODIFIER_HANDLE_TYPE uint16`
- L19 _macro_ `#define MODIFIER_HANDLE_MAX UINT16_MAX`
- L20 _macro_ `#define MODIFIER_INVALID_HANDLE 0`
- L217 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon185799720103`) — WithNetSerializer = true,
- L299 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon185799720203`) — Necessary so that TSharedPtr<FMovementModifierGroup> Data is copied around
- L301 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon185799720203`) — WithNetSerializer = true,
- L302 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon185799720203`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverComponent.h` (Public)


#### class `UMoverComponent`  
`class UMoverComponent : public UActorComponent, public IMovementInterface`  
_L93-1024_
- reflection: `UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IMovementInterface`
- L99 _public prototype_ `UMoverComponent();`
- L101 _public prototype_ `virtual void InitializeComponent() override;`
- L102 _public prototype_ `virtual void UninitializeComponent() override;`
- L103 _public prototype_ `virtual void OnRegister() override;`
- L104 _public prototype_ `virtual void RegisterComponentTickFunctions(bool bRegister) override;`
- L105 _public prototype_ `virtual void PostLoad() override;`
- L106 _public prototype_ `virtual void BeginPlay() override;`
- L107 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type Reason) override;`
- L112 _public member_ `FMover_OnPreSimTick OnPreSimulationTick;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast before each simulation tick. Note - Guaranteed to run on the game thread (even in async simulation).
- L116 _public member_ `FMover_OnPostMovement OnPostMovement;` — `UPROPERTY()` — Broadcast at the end of a simulation tick after movement has occurred, but allowing additions/modifications to the state. Not assignable as a BP event due to it having mutable parameters.
- L120 _public member_ `FMover_OnPostSimTick OnPostSimulationTick;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast after each simulation tick and the state is finalized
- L124 _public member_ `FMover_OnPostSimRollback OnPostSimulationRollback;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a rollback has occurred, just before the next simulation tick occurs
- L128 _public member_ `FMover_OnMovementModeChanged OnMovementModeChanged;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a MovementMode has changed. Happens during a simulation tick if the mode changed.
- L132 _public member_ `FMover_OnTeleportSucceeded OnTeleportSucceeded;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a teleport has succeeded
- L136 _public member_ `FMover_OnTeleportFailed OnTeleportFailed;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a teleport has failed
- L141 _public member_ `FMover_OnBasedMovementApplied OnBasedMovementApplied;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast after any based movement has been finished appling to the owner of this MoverComponent during a single movement simulation tick. This is always on the game thread, after the base has moved. (see @bSupportsKinematicBasedMovement)
- L145 _public member_ `FMover_OnGameplayTagAdded OnGameplayTagAdded;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a gameplay tag becomes active, whether driven by the simulation internally or applied externally via AddGameplayTag. Fired on the game thread.
- L149 _public member_ `FMover_OnGameplayTagRemoved OnGameplayTagRemoved;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a gameplay tag is no longer active, whether driven by the simulation internally or removed externally via RemoveGameplayTag. Fired on the game thread.
- L153 _public member_ `FMover_OnTransitionTriggered OnMovementTransitionTriggered;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast when a Transition has been triggered.
- L157 _public member_ `FMover_OnPostFinalize OnPostFinalize;` — `UPROPERTY(BlueprintAssignable, Category = Mover)` — Broadcast after each finalized simulation frame, after the state is finalized. (Game thread only)
- L162 _public member_ `FMover_OnPostSimEventReceived OnPostSimEventReceived;` — Fired when a new event has been received from the simulation This happens after the event had been processed at the mover component level, which may have caused a dedicated delegate, e.g. OnMovementModeChanged, to fire prior to this broadcast.
- L168 _public member_ `FMover_ProcessGeneratedMovement ProcessGeneratedMovement;` — Broadcast after proposed movement has been generated. After movement modes and layered moves have generated movement and mixed together. This allows for final modifications to proposed movement before it's executed.
- L172 _public prototype_ `void BindProcessGeneratedMovement(FMover_ProcessGeneratedMovement ProcessGeneratedMovementEvent);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Binds event for processing movement after it has been generated. Allows for final modifications to proposed movement before it's executed.
- L175 _public prototype_ `void UnbindProcessGeneratedMovement();` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Clears current bound event for processing movement after it has been generated.
- L179 _public function_ `virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)` — `UFUNCTION()` — Callbacks
- L186 _public prototype_ `virtual void ProduceInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd);` — Get latest local input prior to simulation step. Called by backend system on owner's instance (autonomous or authority).
- L189 _public prototype_ `void FinalizeFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Take output for simulation. Called by backend system.
- L192 _public prototype_ `void FinalizeUnchangedFrame();` — Take output for simulation when no simulation state changes have occurred. Called by backend system.
- L195 _public prototype_ `void FinalizeSmoothingFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Take smoothed simulation state. Called by backend system, if supported.
- L198 _public prototype_ `void TickInterpolatedSimProxy(const FMoverTimeStep& TimeStep, const FMoverInputCmdContext& InputCmd, UMoverComponent* MoverComp, const FMoverSyncState& CachedSyncState, const FMoverSyncState& SyncState, const FMoverAuxStateContext& AuxState);` — This is an opportunity to run code on the code on the simproxy in interpolated mode - currently used to help activate and deactivate modifiers on the simproxy in interpolated mode
- L201 _public prototype_ `void OnSimulationStateInitialized(const FMoverSyncState& InitialSyncState, const FMoverAuxStateContext& InitialAuxState);` — Seed initial values based on component's state. Called by backend system.
- L206 _public member_ `TSubclassOf<UActorComponent> BackendClass;` — `UPROPERTY(EditDefaultsOnly, Category = Mover, meta = (MustImplement = "/Script/Mover.MoverBackendLiaisonInterface"))` — Specifies which supporting back end class should drive this Mover actor
- L209 _public member_ `TMap<FName, TObjectPtr<UBaseMovementMode>> MovementModes;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = Mover, meta=(FullyExpand=true))`
- L213 _public member_ `FName StartingMovementMode = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mover, meta=(GetOptions=GetStartingMovementModeNames))` — Name of the first mode to start in when simulation begins. Must have a mapping in MovementModes. Only used during initialization.
- L217 _public member_ `TArray<TObjectPtr<UBaseMovementModeTransition>> Transitions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category=Mover)` — Broadcast after proposed movement has been generated. After movement modes and layered moves have generated movement and mixed together. This allows for final modifications to proposed movement before it's executed. FMover_ProcessGeneratedMovement ProcessGeneratedMovement; Binds event for processing movement after it has been generated. Allows for final modifications to proposed movement before it's executed. UFUNCTION(BlueprintCallable, Category = Mover) MOVER_API void BindProcessGeneratedMovement(FMover_ProcessGeneratedMovement ProcessGeneratedMovementEvent); Clears current bound event for processing movement after it has been generated. UFUNCTION(BlueprintCallable, Category = Mover) MOVER_API void UnbindProcessGeneratedMovement(); Callbacks UFUNCTION() virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { } NP Driver Get latest local input prior to simulation step. Called by backend system on owner's instance (autonomous or authority). MOVER_API virtual void ProduceInput(const int32 DeltaTimeMS, FMoverInputCmdContext* Cmd); Take output for simulation. Called by backend system. MOVER_API void FinalizeFrame(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState); Take output for simulation when no simulation state changes have occurred. Called by backend system. MOVER_API void FinalizeUnchangedFrame(); Take smoothed simulation sta
- L221 _public member_ `TArray<FMoverDataPersistence> PersistentSyncStateDataTypes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Mover)` — List of types that should always be present in this actor's sync state
- L228 _public member_ `TObjectPtr<UObject> InputProducer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover, meta = (ObjectMustImplement = "/Script/Mover.MoverInputProducerInterface"))` — Optional object for producing input cmds. Typically set at BeginPlay time. If not specified, defaulted input will be used. Note that any other actor component implementing MoverInputProducerInterface on this component's owner will also be able to produce input commands if bGatherInputFromAllInputProducerComponents is true. @see bGatherInputFromAllInputProducerComponents
- L232 _public member_ `bool bGatherInputFromAllInputProducerComponents = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mover)` — If true, any actor component implementing MoverInputProducerInterface on this component's owner will be able to produce input commands
- L242 _public member_ `TArray<TObjectPtr<UObject>> InputProducers;` — `UPROPERTY(Transient)` — All MoverInputProducerInterface objects producing input for this mover component. If bGatherInputFromAllInputProducerComponents is true, all components implementing MoverInputProducerInterface on this component's owner will be added to this array at BeginPlay time, and IMoverInputProducerInterface::ProduceInput will be called on each within UMoverComponent::ProduceInput. The order shouldn't matter, as this is for input commands independent of each other, driving different movement modes. If order is important, set bGatherInputFromAllInputProducerComponents to false and implement a dedicated input component instead, gathering input from different sources in a custom order and set it as the InputProducer.
- L246 _public member_ `TObjectPtr<UMovementMixer> MovementMixer;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Optional object for mixing proposed moves.Typically set at BeginPlay time. If not specified, UDefaultMovementMixer will be used.
- L248 _public prototype_ `const TArray<TObjectPtr<ULayeredMoveLogic>>* GetRegisteredMoves() const;`
- L253 _public prototype_ `void FlushPendingMoveRegistrations();` — Flushes MovesPendingRegistration and MovesPendingUnregistration into RegisteredMoves. Extracted so async backends (e.g. ChaosMover) can drive registration without calling the full PreSimulationTick, which is intended for the synchronous path only.
- L257 _public function_ `template <typename MoveT UE_REQUIRES(std::is_base_of_v<ULayeredMoveLogic, MoveT>)> void RegisterMove(TSubclassOf<MoveT> MoveClass = MoveT::StaticClass())` — Registers layered move logic
- L264 _public prototype_ `void K2_RegisterMove(TSubclassOf<ULayeredMoveLogic> MoveClass);` — `UFUNCTION(BlueprintCallable, Category = Mover, DisplayName = "Register Move")` — Registers layered move logic
- L268 _public prototype_ `void K2_RegisterMoves(TArray<TSubclassOf<ULayeredMoveLogic>> MoveClasses);` — `UFUNCTION(BlueprintCallable, Category = Mover, DisplayName = "Register Moves")` — Registers an array of layered move logic classes
- L272 _public function_ `template <typename MoveT UE_REQUIRES(std::is_base_of_v<ULayeredMoveLogic, MoveT>)> void UnregisterMove(TSubclassOf<MoveT> MoveClass = MoveT::StaticClass())` — Unregisters layered move logic
- L279 _public prototype_ `void K2_UnregisterMove(TSubclassOf<ULayeredMoveLogic> MoveClass);` — `UFUNCTION(BlueprintCallable, Category = Mover, DisplayName = "Unregister Move")` — Unregisters layered move logic
- L282 _public function_ `template <typename MoveT, typename ActivationParamsT UE_REQUIRES(std::is_base_of_v<ULayeredMoveLogic, MoveT> && std::is_base_of_v<typename MoveT::MoveDataType::ActivationParamsType, ActivationParamsT>)> bool QueueLayeredMoveActivationWithContext(const ActivationParamsT& ActivationParams, TSubclassOf<MoveT> MoveClass = MoveT::StaticClass())`
- L303 _public prototype_ `bool QueueLayeredMoveActivation(TSubclassOf<ULayeredMoveLogic> MoveLogicClass);` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (AllowAbstract = "false"))` — Queues a layered move for activation. Takes NO Activation Context meaning the layered move will be activated using default Move Data. Note: Changing Move Data is still possible in the layered move logic itself See QueueLayeredMoveActivationWithContext for activating a layered move with context
- L310 _public prototype_ `void K2_QueueLayeredMove(UPARAM(DisplayName="Layered Move") const int32& Mov` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "MoveAsRawData", AllowAbstract = "false", DisplayName = "Queue Layered Move"))` — Queue a layered move to start during the next simulation frame. This will clone whatever move you pass in, so you'll need to fully set it up before queuing. @param LayeredMove			The move to queue, which must be a LayeredMoveBase sub-type.
- L314 _public prototype_ `void QueueLayeredMove(TSharedPtr<FLayeredMoveBase> Move);` — Queue a layered move to start during the next simulation frame
- L334 _public prototype_ `void ScheduleLayeredMove(TSharedPtr<FLayeredMoveBase> Move);` — Advance Usage. This will only become relevant to Mover in general when Layered Moves are automatically networked (pending, only Chaos Mover networks them by default) Queue a scheduled move to take place after delay (tunable in the NetworkPhysicsSettingsComponent) ensuring it gets executed on the same frame on all networked end points. @see UNetworkPhysicsSettingsComponent, @see FNetworkPhysicsSettings Examples: 1. For an Autonomous Proxy Actor: An autonomous proxy might want to schedule a move that can be dodged by other players, for instance and air stomp, so that it starts executing on the same frame for sim proxies giving them a fair chance to dodge it. The server might also need to schedule 2. For an actor moved on the Server authoritatively. Since the server runs behind clients, if it wants to avoid corrections it needs to schedule execution of moves in the future so they get executed on the same frame on all end points. For instance, a platform changing direction as a result of some unpredictable event (such as colliding with a player character) should be scheduled if we want to guarantee correction-free physical interactions with that platform Pros: Everybody executes on the same frame (or at roughly the same time in variable dt), less correction, no surprises. Cons: Delay in execution, needs to be masked with anticipation anim. Significant lag (several frames). Default to using QueueLayeredMove instead, except for advanced use cases where it is important the move get 
- L338 _protected prototype_ `void QueueScheduledLayeredMove(const FScheduledLayeredMove& ScheduledLayeredMove);` — Queue a scheduled layered move. Thread safe, can be used outside the game thread.
- L348 _public prototype_ `FMovementModifierHandle K2_QueueMovementModifier(UPARAM(DisplayName="Movement Modifier") const int32` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "MoveAsRawData", AllowAbstract = "false", DisplayName = "Queue Movement Modifier"))` — Queue a Movement Modifier to start during the next simulation frame. This will clone whatever move you pass in, so you'll need to fully set it up before queuing. @param MovementModifier The modifier to queue, which must be a LayeredMoveBase sub-type. @return Returns a Modifier handle that can be used to query or cancel the movement modifier
- L352 _public prototype_ `FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier);` — Queue a Movement Modifier to start during the next simulation frame.
- L358 _public prototype_ `void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Cancel any active or queued Modifiers with the handle passed in.
- L364 _public prototype_ `void CancelFeaturesWithTag(FGameplayTag TagToCancel, bool bRequireExactMatch=false);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Cancel any active or queued movement features (layered moves, modifiers, etc.) that have a matching gameplay tag. Does not affect the active movement mode.
- L370 _public prototype_ `bool HasFeaturesWithTag(FGameplayTag TagToCancel, bool bRequireExactMatch = false) const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Check any active or queued movement features (layered moves, modifiers, etc.) for a matching gameplay tag.
- L377 _public prototype_ `void K2_QueueInstantMovementEffect(UPARAM(DisplayName="Instant Movement Effect") const i` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "EffectAsRawData", AllowAbstract = "false", DisplayName = "Queue Instant Movement Effect"))` — Queue an Instant Movement Effect to start at the end of this frame or start of the next subtick - whichever happens first. This will clone whatever move you pass in, so you'll need to fully set it up before queuing. @param InstantMovementEffect			The effect to queue, which must be a FInstantMovementEffect sub-type.
- L387 _public prototype_ `void K2_ScheduleInstantMovementEffect(UPARAM(DisplayName="Instant Movement Effect") const i` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = Mover, meta = (CustomStructureParam = "EffectAsRawData", AllowAbstract = "false", DisplayName = "Schedule Instant Movement Effect"))` — Schedule an Instant Movement Effect to be applied as early as possible while ensuring it gets executed on the same frame on all networked end points. This adds a delay to the application of the effect, tunable in the NetworkPhysicsSettingsComponent. @see UNetworkPhysicsSettingsComponent, @see FNetworkPhysicsSettings, @see EventSchedulingMinDelaySeconds This will clone whatever move you pass in, so you'll need to fully set it up before queuing. @param InstantMovementEffect			The effect to queue, which must be a FInstantMovementEffect sub-type.
- L394 _public prototype_ `void QueueInstantMovementEffect(TSharedPtr<FInstantMovementEffect> InstantMovementEffect);` — Queue a Instant Movement Effect to take place at the end of this frame or start of the next subtick - whichever happens first @param InstantMovementEffect			The effect to queue, which must be a FInstantMovementEffect sub - type.
- L402 _public prototype_ `void ScheduleInstantMovementEffect(TSharedPtr<FInstantMovementEffect> InstantMovementEffect);` — Advance Usage. This will only become relevant to Mover in general when Instant Movement Effects are automatically networked (pending, only Chaos Mover networks them by default) Queue a scheduled Instant Movement Effect to take place after delay (tunable in the NetworkPhysicsSettingsComponent) ensuring it gets executed on the same frame on all networked end points. @see UNetworkPhysicsSettingsComponent, @see FNetworkPhysicsSettings Default to using QueueInstantMovementEffect instead, except for advanced use cases where it is important the effect get executed on the same frame on all end points. @param InstantMovementEffect			The effect to queue, which must be a FInstantMovementEffect sub - type.
- L405 _public prototype_ `void QueueInstantMovementEffect_Internal(const FMoverTimeStep& TimeStep, TSharedPtr<FInstantMovementEffect> InstantMovementEffect);` — Queue an instant movement effect in async mode. Do not use on the game thread.
- L409 _protected prototype_ `void QueueScheduledInstantMovementEffect(const FScheduledInstantMovementEffect& ScheduledInstantMovementEffect);` — Queue a scheduled instant movement effect. Thread safe, can be used outside the game thread.
- L414 _public prototype_ `void QueueNextMode(FName DesiredModeName, bool bShouldReenter=false);` — `UFUNCTION(BlueprintCallable, Category = Mover, DisplayName="Queue Next Movement Mode")` — Queue a movement mode change to occur during the next simulation frame. If bShouldReenter is true, then a mode change will occur even if already in that mode.
- L418 _public prototype_ `UBaseMovementMode* AddMovementModeFromClass(FName ModeName, UPARAM(meta = (AllowAbstract = "false"))TSubclassOf<UBaseMovementMode> MovementM` — `UFUNCTION(BlueprintCallable, Category = Mover, meta=(DeterminesOutputType="MovementMode"))` — Add a movement mode to available movement modes. Returns true if the movement mode was added successfully. Returns the mode that was made.
- L422 _public prototype_ `bool AddMovementModeFromObject(FName ModeName, UBaseMovementMode* MovementMode);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Add a movement mode to available movement modes. Returns true if the movement mode was added successfully
- L426 _public prototype_ `bool RemoveMovementMode(FName ModeName);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Removes a movement mode from available movement modes. Returns number of modes removed from the available movement modes.
- L431 _public prototype_ `void SetGravityOverride(bool bOverrideGravity, FVector GravityAcceleration=FVector::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Set gravity override, as a directional acceleration in worldspace.  Gravity on Earth would be {x=0,y=0,z=-980}
- L435 _public prototype_ `FVector GetGravityAcceleration() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Mover)` — Get the current acceleration due to gravity (cm/s^2) in worldspace
- L438 _public function_ `FQuat GetWorldToGravityTransform() const` — Returns a quaternion transforming from world to gravity space.
- L441 _public function_ `FQuat GetGravityToWorldTransform() const` — Returns a quaternion transforming from gravity to world space.
- L445 _public prototype_ `void SetUpDirectionOverride(bool bOverrideUpDirection, FVector UpDirection=FVector::UpVector);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Set UpDirection override. This is a fixed direction that overrides the gravity-derived up direction.
- L449 _public prototype_ `FVector GetUpDirection() const;` — `UFUNCTION(BlueprintPure = false, Category = Mover)` — Get the normalized direction considered "up" in worldspace. Typically aligned with gravity, and typically determines the plane an actor tries to move along.
- L453 _public prototype_ `const FPlanarConstraint& GetPlanarConstraint() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Mover)` — Access the planar constraint that may be limiting movement direction
- L457 _public prototype_ `void SetPlanarConstraint(const FPlanarConstraint& InConstraint);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets planar constraint that can limit movement direction
- L461 _public prototype_ `void SetBaseVisualComponentTransform (const FTransform& ComponentTransform);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets BaseVisualComponentTransform used for cases where we want to move the visual component away from the root component. See @BaseVisualComponentTransform
- L465 _public prototype_ `FTransform GetBaseVisualComponentTransform() const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Gets BaseVisualComponentTransform used for cases where we want to move the visual component away from the root component. See @BaseVisualComponentTransform
- L469 _public prototype_ `void SetUseDeferredGroupMovement(bool bEnable);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets whether this mover component can use grouped movement updates, which improve performance but can cause attachments to update later than expected
- L473 _public prototype_ `bool IsUsingDeferredGroupMovement() const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns true if this component is actually using grouped movement updates, which checks the flag and any global settings
- L482 _public prototype_ `virtual FTransform ConvertLocalRootMotionToWorld(const FTransform& LocalRootMotionTransform, float DeltaSeconds, const FTransform* AlternateActorToWorld=nullptr, const FMotionWarpingUpdateContext* OptionalWarpingContext=nullptr) const;` — Converts a local root motion transform to worldspace. @param AlternateActorToWorld   allows specification of a different actor root transform, for cases when root motion isn't directly being applied to this actor (async simulations) @param OptionalWarpingContext   allows specification of a warping context, for use with root motion that is asynchronous from the actor (async simulations)
- L485 _public member_ `FOnWarpLocalspaceRootMotionWithContext ProcessLocalRootMotionDelegate;` — delegates used when converting local root motion to worldspace, allowing external systems to influence it (such as motion warping)
- L486 _public member_ `FOnWarpWorldspaceRootMotionWithContext ProcessWorldRootMotionDelegate;`
- L491 _public prototype_ `FTransform GetUpdatedComponentTransform() const;` — Get the transform of the root component that our Mover simulation is moving
- L495 _public prototype_ `void SetUpdatedComponent(USceneComponent* NewUpdatedComponent);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets which component we're using as the root of our movement
- L499 _public prototype_ `USceneComponent* GetUpdatedComponent() const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Access the root component of the actor that our Mover simulation is moving
- L503 _public function_ `template<class T> T* GetUpdatedComponent() const` — Typed accessor to root moving component
- L511 _public prototype_ `USceneComponent* GetPrimaryVisualComponent() const;` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Access the primary visual component of the actor
- L515 _public function_ `template<class T> T* GetPrimaryVisualComponent() const` — Typed accessor to primary visual component
- L522 _public prototype_ `void SetPrimaryVisualComponent(USceneComponent* SceneComponent);` — `UFUNCTION(BlueprintCallable, Category=Mover)` — Sets this Mover actor's primary visual component. Must be a descendant of the updated component that acts as our movement root.
- L526 _public prototype_ `virtual FVector GetVelocity() const override;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the current velocity (units per second, worldspace)
- L530 _public prototype_ `FVector GetMovementIntent() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the intended movement direction in worldspace with magnitude (range 0-1)
- L534 _public prototype_ `FRotator GetTargetOrientation() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the orientation that the actor is moving towards
- L539 _public prototype_ `TArray<FTrajectorySampleInfo> GetFutureTrajectory(float FutureSeconds, float SamplesPerSecond);` — `UE_DEPRECATED(5.5, "Use GetPredictedTrajectory instead.")` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Mover)` — Get a sampling of where the actor is projected to be in the future, based on a current state. Note that this is projecting ideal movement without doing full simulation and collision.
- L544 _public prototype_ `virtual TArray<FTrajectorySampleInfo> GetPredictedTrajectory(FMoverPredictTrajectoryParams PredictionParams);` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Mover)` — Get a sampling of where the actor is projected to be in the future, based on a current state. Note that this is projecting ideal movement without doing full simulation and collision. The first sample info of the returned array corresponds to the current state of the mover.
- L548 _public prototype_ `FName GetMovementModeName() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the current movement mode name
- L552 _public prototype_ `virtual FName GetNextMovementModeName() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Gets the name of the next movement mode, if a change is queued. Returns the current mode name otherwise.
- L556 _public prototype_ `const UBaseMovementMode* GetMovementMode() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the current movement mode
- L560 _public prototype_ `UPrimitiveComponent* GetMovementBase() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the current movement base. Null if there isn't one.
- L564 _public prototype_ `FName GetMovementBaseBoneName() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the current movement base bone, NAME_None if there isn't one.
- L569 _public prototype_ `bool HasValidCachedState() const;` — `UE_DEPRECATED(5.6, "HasValidCachedState has been deprecated, and is not needed since we no longer wait until movement simulation begins before providing a valid sync state.")` — `UFUNCTION(BlueprintPure, Category = Mover, meta=(DeprecatedFunction, DeprecationMessage="HasValidCachedState has been deprecated, and is not needed since we no longer wait until movement simulation begins before providing a valid sync state."))` — Signals whether we have a sync state saved yet. If not, most queries will not be meaningful.
- L573 _public prototype_ `const FMoverSyncState& GetSyncState() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Access the most recent captured sync state.
- L578 _public prototype_ `bool HasValidCachedInputCmd() const;` — `UE_DEPRECATED(5.6, "HasValidCachedInputCmd has been deprecated, and is not needed since we no longer wait until movement simulation begins before providing a valid input cmd.")` — `UFUNCTION(BlueprintPure, Category = Mover, meta = (DeprecatedFunction, DeprecationMessage = "HasValidCachedInputCmd has been deprecated, and is not needed since we no longer wait until movement simulation begins before providing a valid input cmd."))` — Signals whether we have input data saved yet. If not, input queries will not be meaningful.
- L582 _public prototype_ `const FMoverInputCmdContext& GetLastInputCmd() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Access the most recently-used inputs.
- L586 _public prototype_ `const FMoverTimeStep& GetLastTimeStep() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the most recent TimeStep
- L590 _public prototype_ `virtual bool TryGetFloorCheckHitResult(FHitResult& OutHitResult) const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Access the most recent floor check hit result.
- L594 _public prototype_ `const UMoverBlackboard* GetSimBlackboard() const;` — `UFUNCTION(BlueprintPure, Category=Mover)` — Access the read-only version of the Mover's Blackboard
- L596 _public prototype_ `UMoverBlackboard* GetSimBlackboard_Mutable() const;`
- L599 _public function_ `FRollbackBlackboardExternalWrapper GetRollbackBlackboardExternal() const` — Access the version of the movement blackboard for users outside of the movement simulation
- L602 _public function_ `const IMovementSettingsInterface* FindSharedSettings(const UClass* ByType) const` — Find settings object by type. Returns null if there is none of that type
- L604 _public function_ `template<typename SettingsT = IMovementSettingsInterface UE_REQUIRES(std::is_base_of_v<IMovementSettingsInterface, SettingsT>)> const SettingsT* FindSharedSettings() const`
- L607 _public prototype_ `IMovementSettingsInterface* FindSharedSettings_Mutable(const UClass* ByType) const;` — Find mutable settings object by type. Returns null if there is none of that type
- L609 _public function_ `template<typename SettingsT = IMovementSettingsInterface UE_REQUIRES(std::is_base_of_v<IMovementSettingsInterface, SettingsT>)> SettingsT* FindSharedSettings_Mutable() const`
- L613 _public prototype_ `UObject* FindSharedSettings_Mutable_BP(UPARAM(meta = (MustImplement = "MovementSettingsInterface")) TSubclassOf<UObje` — `UFUNCTION(BlueprintPure, Category = Mover, meta=(DeterminesOutputType="SharedSetting", DisplayName="Find Shared Settings Mutable"))` — Find mutable settings object by type. Returns null if there is none of that type
- L617 _public prototype_ `const UObject* FindSharedSettings_BP(UPARAM(meta = (MustImplement = "MovementSettingsInterface")) TSubclassOf<UObje` — `UFUNCTION(BlueprintPure, Category = Mover, meta=(DeterminesOutputType="SharedSetting", DisplayName="Find Shared Settings"))` — Find settings object by type. Returns null if there is none of that type
- L621 _public function_ `template<typename ModeT = UBaseMovementMode UE_REQUIRES(std::is_base_of_v<UBaseMovementMode, ModeT>)> const ModeT* GetActiveMode(bool bRequireExactClass = false) const` — Gets the currently active movement mode, provided it is of the given type. Returns nullptr if there is no active mode yet, or if it's of a different type.
- L625 _public function_ `template<typename ModeT = UBaseMovementMode UE_REQUIRES(std::is_base_of_v<UBaseMovementMode, ModeT>)> ModeT* GetActiveMode_Mutable(bool bRequireExactClass = false) const` — Gets the currently active movement mode, provided it is of the given type. Returns nullptr if there is no active mode yet, or if it's of a different type.
- L629 _public function_ `template<typename ModeT = UBaseMovementMode UE_REQUIRES(std::is_base_of_v<UBaseMovementMode, ModeT>)> ModeT* FindMode_Mutable(bool bRequireExactClass = false) const` — Find the first movement mode on this component with the given type, optionally of the given type exactly. Returns null if there is none of that type
- L630 _public prototype_ `UBaseMovementMode* FindMode_Mutable(TSubclassOf<UBaseMovementMode> ModeType, bool bRequireExactClass = false) const;`
- L634 _public function_ `template<typename ModeT = UBaseMovementMode UE_REQUIRES(std::is_base_of_v<UBaseMovementMode, ModeT>)> ModeT* FindMode_Mutable(FName MovementModeName, bool bRequireExactClass = false) const` — Find the movement mode on this component the given name and type, optionally of the given type exactly. Returns null if there is no mode by that name, or if it's of a different type.
- L635 _public prototype_ `UBaseMovementMode* FindMode_Mutable(TSubclassOf<UBaseMovementMode> ModeType, FName ModeName, bool bRequireExactClass = false) const;`
- L638 _public prototype_ `UBaseMovementMode* FindMovementMode(TSubclassOf<UBaseMovementMode> MovementMode) const;` — `UFUNCTION(BlueprintPure, Category = Mover, meta=(DeterminesOutputType="MovementMode"))`
- L641 _public prototype_ `UBaseMovementMode* FindMovementModeByName(FName MovementModeName) const;` — `UFUNCTION(BlueprintPure, Category = Mover)`
- L653 _public prototype_ `const FLayeredMoveBase* FindActiveLayeredMoveByType(const UScriptStruct* DataStructType) const;` — Find an active layered move by type. Returns null if one wasn't found
- L657 _public function_ `template <typename MoveT = FLayeredMoveBase UE_REQUIRES(std::is_base_of_v<FLayeredMoveBase, MoveT>)> const MoveT* FindActiveLayeredMoveByType() const` — Find a layered move of a specific type in this components active layered moves. If not found, null will be returned.
- L671 _public prototype_ `bool IsModifierActiveOrQueued(const FMovementModifierHandle& ModifierHandle) const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Checks if the modifier handle passed in is active or queued on this mover component
- L674 _public prototype_ `const FMovementModifierBase* FindMovementModifier(const FMovementModifierHandle& ModifierHandle) const;` — Find movement modifier by it's handle. Returns nullptr if the modifier couldn't be found
- L677 _public prototype_ `const FMovementModifierBase* FindMovementModifierByType(const UScriptStruct* DataStructType) const;` — Find movement modifier by type (returns the first modifier it finds). Returns nullptr if the modifier couldn't be found
- L681 _public function_ `template <typename ModifierT = FMovementModifierBase UE_REQUIRES(std::is_base_of_v<FMovementModifierBase, ModifierT>)> const ModifierT* FindMovementModifierByType() const` — Find a movement modifier of a specific type in this components movement modifiers. If not found, null will be returned.
- L687 _public function_ `bool IsBackendAsync() const` — `UFUNCTION(BlueprintPure, Category = Mover)` — Returns true if the current backend runs the simulation asynchronously on the worker thread. Use this to decide whether simulation output (e.g. montage position) is the sole authority or whether the game thread is also advancing state independently.
- L693 _public prototype_ `FGameplayTagContainer GetGameplayTags() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get the gameplay tags currently active, combining simulation-reported tags and externally-added tags. In the async backend (ChaosMover), or when mover.UseSnapshotGameplayTagsForSyncBackend is set, returns the cached AllGameplayTags snapshot. Otherwise performs a live walk of the current sync state.
- L704 _public prototype_ `bool HasGameplayTag(FGameplayTag TagToFind, bool bExactMatch) const;` — `UFUNCTION(BlueprintPure, Category = Mover, meta = (Keywords = "HasTag"))` — Check Mover systems for a gameplay tag. @param TagToFind			Tag to check on the Mover systems @param bExactMatch		If true, the tag has to be exactly present, if false then TagToFind will include it's parent tags while matching @return True if the TagToFind was found
- L715 _public prototype_ `bool HasGameplayTagInState(const FMoverSyncState& SyncState, FGameplayTag TagToFind, bool bExactMatch) const;` — `UFUNCTION(BlueprintPure, Category = Mover, meta = (Keywords = "HasTag"))` — Check Mover systems for a gameplay tag. Use the given state, as well as any loose tags on the MoverComponent. @param TagToFind			Tag to check on the MoverComponent or state @param bExactMatch		If true, the tag has to be exactly present, if false then TagToFind will include it's parent tags while matching @return True if the TagToFind was found
- L723 _public prototype_ `void AddGameplayTag(FGameplayTag TagToAdd);` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (Keywords = "Add Tag"))` — Adds a gameplay tag to this Mover Component. Note: Duplicate tags will not be added @param TagToAdd			Tag to add to the Mover Component
- L731 _public prototype_ `void AddGameplayTags(const FGameplayTagContainer& TagsToAdd);` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (Keywords = "Add Tag"))` — Adds a series of gameplay tags to this Mover Component Note: Duplicate tags will not be added @param TagsToAdd			Tags to add/append to the Mover Component
- L738 _public prototype_ `void RemoveGameplayTag(FGameplayTag TagToRemove);` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (Keywords = "Remove Tag"))` — Removes a gameplay tag from this Mover Component @param TagToRemove			Tag to remove from the Mover Component
- L745 _public prototype_ `void RemoveGameplayTags(const FGameplayTagContainer& TagsToRemove);` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (Keywords = "Remove Tag"))` — Removes gameplay tags from this Mover Component @param TagsToRemove			Tags to remove from the Mover Component
- L748 _public prototype_ `virtual UObject* GetMovementOwner() const override;` — IMovementInterface
- L749 _public prototype_ `virtual UObject* GetUpdatedObject() const override;`
- L750 _public prototype_ `virtual FTransform GetTransform() const override;`
- L751 _public prototype_ `virtual void RequestStopMovement() override;`
- L757 _public prototype_ `virtual void OnPreSimulate(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartingData);` — Called before each simulation tick. Broadcasts OnPreSimulationTick delegate.
- L760 _public prototype_ `virtual void OnPostSimulate(const FMoverTimeStep& TimeStep, const FMoverTickStartData& StartingData, OUT FMoverTickEndData& EndingData);` — Called after each simulation tick. Broadcasts OnPostMovement and OnPostSimulationTick delegates.
- L763 _public prototype_ `void OnSimulationRollback(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState, const FMoverTimeStep& NewBaseTimeStep);` — Called when a rollback occurs, with the simulation state that is being restored. NewBaseTimeStep represents the new time and frame we'll be resimulating next.
- L769 _protected prototype_ `void SetFrameStateFromContext(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState, bool bDueToRollback);` — Makes this component and owner actor reflect the state of a particular frame snapshot. This occurs after simulation ticking, as well as during a rollback before we resimulate forward. @param bDueToRollback	Signifies if this is a forward-advancing frame or rollback. Affects how transform changes are applied.
- L772 _protected prototype_ `void UpdateCachedFrameState(const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState);` — Update cached frame state if it has changed
- L776 _public prototype_ `virtual void GetDefaultInputAndState(FMoverInputCmdContext& OutInputCmd, FMoverSyncState& OutSyncState, FMoverAuxStateContext& OutAuxState) const;` — Author input and state based on the current location of the actor. Typically used at initialization time.
- L778 _public prototype_ `void SetSimulation(UMoverSimulation& Simulation);` — Temporary support function. Will be removed once simulations are used consistently.
- L782 _public prototype_ `void HandleImpact(FMoverOnImpactParams& ImpactParams);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Handle a blocking impact.
- L785 _protected prototype_ `void FindDefaultUpdatedComponent();`
- L786 _protected prototype_ `void FindAndRegisterDefaults();`
- L787 _protected prototype_ `void UpdateTickRegistration();`
- L789 _protected prototype_ `virtual void DoQueueNextMode(FName DesiredModeName, bool bShouldReenter=false);`
- L792 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L793 _protected prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;`
- L794 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L795 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L796 _protected prototype_ `bool ValidateSetup(class FDataValidationContext& ValidationErrors) const;`
- L797 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L800 _protected prototype_ `TArray<FString> GetStartingMovementModeNames();` — `UFUNCTION()`
- L804 _protected prototype_ `virtual void PhysicsVolumeChanged(class APhysicsVolume* NewVolume);` — `UFUNCTION()`
- L806 _protected prototype_ `virtual void OnHandleImpact(const FMoverOnImpactParams& ImpactParams);`
- L809 _protected prototype_ `void UpdateBasedMovementScheduling(const FMoverTickEndData& SimOutput);` — internal function to perform post-sim scheduling to optionally support simple based movement
- L811 _protected prototype_ `UBaseMovementMode* GetActiveModeInternal(TSubclassOf<UBaseMovementMode> ModeType, bool bRequireExactClass = false) const;`
- L813 _protected member_ `TObjectPtr<UPrimitiveComponent> MovementBaseDependency;` — used internally for based movement scheduling management
- L816 _protected prototype_ `void RefreshSharedSettings();` — internal function to ensure SharedSettings array matches what's needed by the list of Movement Modes
- L820 _protected member_ `TObjectPtr<USceneComponent> UpdatedComponent = nullptr;` — `UPROPERTY(Transient)` — This is the component that's actually being moved. Typically it is the Actor's root component and often a collidable primitive.
- L824 _protected member_ `TObjectPtr<UPrimitiveComponent> UpdatedCompAsPrimitive = nullptr;` — `UPROPERTY(Transient)` — UpdatedComponent, cast as a UPrimitiveComponent. May be invalid if UpdatedComponent was null or not a UPrimitiveComponent.
- L828 _protected member_ `TObjectPtr<USceneComponent> PrimaryVisualComponent;` — `UPROPERTY(Transient)` — The main visual component associated with this Mover actor, typically a mesh and typically parented to the UpdatedComponent.
- L832 _protected member_ `FTransform BaseVisualComponentTransform = FTransform::Identity;` — Cached original offset from the visual component, used for cases where we want to move the visual component away from the root component (for smoothing, corrections, etc.)
- L836 _protected member_ `FGameplayTagContainer InternalGameplayTags;` — Gameplay tags currently active on the simulation.
- L839 _protected member_ `FGameplayTagContainer ExternalGameplayTags;` — A list of gameplay tags associated with this Mover Component added from sources outside of Mover
- L842 _protected member_ `FGameplayTagContainer AllGameplayTags;` — Combined cache of InternalGameplayTags and ExternalGameplayTags. Used by GetGameplayTags() and HasGameplayTag() in the async backend path, and in the sync backend path when mover.UseSnapshotGameplayTagsForSyncBackend is set.
- L845 _protected prototype_ `void RebuildAllGameplayTags();` — Rebuilds AllGameplayTags from InternalGameplayTags and ExternalGameplayTags. Must be called after either source changes.
- L848 _protected prototype_ `void CollectGameplayTagsFromSyncState(const FMoverSyncState& SyncState, FGameplayTagContainer& OutTags) const;` — Collects all gameplay tags currently active on the given sync state (movement mode, modifiers, layered moves) into OutTags.
- L850 _protected member_ `FMoverInputCmdContext CachedLastProducedInputCmd;`
- L852 _protected member_ `FMoverInputCmdContext CachedLastUsedInputCmd;`
- L854 _protected member_ `FMoverDoubleBuffer<FMoverSyncState> MoverSyncStateDoubleBuffer;`
- L856 _protected member_ `const FMoverDefaultSyncState* LastMoverDefaultSyncState = nullptr;`
- L858 _protected member_ `FMoverTimeStep CachedLastSimTickTimeStep;` — Saved timestep info from our last simulation tick, used during rollback handling. This will rewind during corrections.
- L859 _protected member_ `FMoverTimeStep CachedNewestSimTickTimeStep;` — Saved timestep info from the newest (farthest-advanced) simulation tick. This will not rewind during corrections.
- L862 _protected member_ `TScriptInterface<IMoverBackendLiaisonInterface> BackendLiaisonComp;` — `UPROPERTY(Transient)`
- L865 _protected member_ `FMoverDynamicBasedMovementTickFunction BasedMovementTickFunction;` — Tick function that may be called anytime after this actor's movement step, useful as a way to support based movement on objects that are not
- L869 _protected member_ `TObjectPtr<UMoverBlackboard> SimBlackboard = nullptr;` — `UPROPERTY(Transient)` — Used to store cached data & computations between decoupled systems, that can be referenced by name
- L873 _protected member_ `TObjectPtr<UMoverSimulation> Simulation = nullptr;` — `UPROPERTY(Transient)` — This is what all movement mechanisms should be interacting with during simulation, rather than relying on actors/components. External parties should generally not see it.
- L877 _protected member_ `FRollbackBlackboardExternalWrapper RollbackBlackboardExternalWrapper;` — `UPROPERTY(Transient)` — Accessors used to interface with the simulation's rollback blackboard
- L885 _protected member_ `TArray<TObjectPtr<ULayeredMoveLogic>> RegisteredMoves;` — `UPROPERTY(Transient)` — Layered moves registered on this component that can be activated regardless of the current mode Changes to this array or its contents occur ONLY during PreSimulationTick to ensure threadsafe access during async simulations.
- L888 _protected member_ `TArray<TSubclassOf<ULayeredMoveLogic>> MovesPendingRegistration;` — `UPROPERTY(Transient)`
- L891 _protected member_ `TArray<TSubclassOf<ULayeredMoveLogic>> MovesPendingUnregistration;` — `UPROPERTY(Transient)`
- L894 _protected prototype_ `bool MakeAndQueueLayeredMove(const TSubclassOf<ULayeredMoveLogic>& MoveLogicClass, const FLayeredMoveActivationParams* ActivationParams);` — Helper function for making Queueing and making Layered Moves
- L902 _protected prototype_ `void DispatchGameplayTagTransitionEvents(const FGameplayTagContainer& PreviousTags, const FGameplayTagContainer& NewTags, const TArray<TSharedPtr<FMoverSimulationEventData>>& EventsToSkip, const FMoverTimeStep& TimeStep);` — Fires OnGameplayTagAdded/OnGameplayTagRemoved for every tag that is in NewTags but not PreviousTags (added), or in PreviousTags but not NewTags (removed). Tags already covered by an entry in EventsToSkip are suppressed to avoid double-firing alongside explicit simulation events. Tags also present in ExternalGameplayTags are suppressed with a log, as concurrent simulation and external ownership of the same tag is unexpected.
- L910 _protected prototype_ `void DispatchUnexpectedTagDriftEvents(const FGameplayTagContainer& PreviousTags, const FGameplayTagContainer& NewTags, const TArray<TSharedPtr<FMoverSimulationEventData>>& Events, const FMoverTimeStep& TimeStep);` — Called after applying a new tag snapshot from simulation output. In principle, every queued simulation tag event should account for every change between PreviousTags and NewTags. If that invariant is violated (i.e. a tag changed state without a corresponding event), this is a bug - we recover by emitting the missing events and logging a warning for each discrepancy. Delegates to DispatchGameplayTagTransitionEvents for the actual dispatch.
- L915 _private member_ `TArray<TObjectPtr<UObject>> SharedSettings;` — `UPROPERTY(EditDefaultsOnly, EditFixedSize, Instanced, Category = Mover, meta = (NoResetToDefault, ObjectMustImplement = "/Script/Mover.MovementSettingsInterface"))` — Collection of settings objects that are shared between movement modes. This list is automatically managed based on the @MovementModes contents.
- L919 _private member_ `FVector GravityAccelOverride;` — `UPROPERTY(EditDefaultsOnly, Category="Mover|Gravity", meta=(ForceUnits = "cm/s^2"))` — cm/s^2, only meaningful if @bHasGravityOverride is enabled.Set @SetGravityOverride
- L923 _private member_ `FPlanarConstraint PlanarConstraint;` — `UPROPERTY(EditDefaultsOnly, Category = "Mover|Constraints")` — Settings that can lock movement to a particular plane
- L929 _public member_ `EMoverSmoothingMode SmoothingMode = EMoverSmoothingMode::VisualComponentOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover")` — If enabled, the movement of the primary visual component will be smoothed via an offset from the root moving component. This is useful in fixed-tick simulations with variable rendering rates.
- L933 _public member_ `uint8 bWarnOnExternalMovement : 1 = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover", AdvancedDisplay)` — Whether to warn when we detect that an external system has moved our object, outside of movement simulation control
- L937 _public member_ `uint8 bAcceptExternalMovement : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover", AdvancedDisplay)` — If enabled, we'll accept any movements from an external system in the next simulation state update
- L941 _public member_ `uint8 bSyncInputsForSimProxy : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mover", AdvancedDisplay, Experimental)` — If enabled, we'll send inputs along with to sim proxy via the sync state, and they'll be available via GetLastInputCmd. This may be useful for cases where input is used to hint at object state, such as an anim graph. This option is intended to be temporary until all networking backends allow this.
- L943 _public prototype_ `void SetSimulationOutput(const FMoverTimeStep& TimeStep, const UE::Mover::FSimulationOutputData& OutputData);`
- L946 _public prototype_ `void DispatchSimulationEvent(const FMoverSimulationEventData& EventData);` — Dispatch a simulation event. It will be processed immediately.
- L949 _protected prototype_ `virtual void DispatchSimulationEvents(const UE::Mover::FSimulationOutputData& OutputData);`
- L950 _protected prototype_ `virtual void ProcessSimulationEvent(const FMoverSimulationEventData& EventData);`
- L951 _protected prototype_ `virtual void SetAdditionalSimulationOutput(const FMoverDataCollection& Data);`
- L955 _protected prototype_ `void FlushMontageStates(const FMoverSimDrivenMontageData& MontageData);` — Flush the simulation-authoritative montage state accumulated during SetAdditionalSimulationOutput calls for this frame. Drives GT montage lifecycle (position, blend-out, finish) from sim output.
- L958 _protected prototype_ `void ApplyMontageEntry(const FMoverSimDrivenMontageEntry& Entry, UAnimInstance* AnimInstance);` — Apply a single montage entry: start, position, blend-out, or finish the GT montage instance.
- L961 _protected prototype_ `void StopDrivenMontage(const FMoverSimDrivenMontageEntry& LastEntry, UAnimInstance* AnimInstance);` — Stop a GT montage instance that disappeared from simulation output without a normal finish signal.
- L966 _private member_ `bool bHasUpDirectionOverride = false;` — `UPROPERTY(EditDefaultsOnly, Category="Mover|UpDirection")` — Whether to override the up direction with a fixed value instead of using gravity to deduce it
- L970 _private member_ `FVector UpDirectionOverride = FVector::UpVector;` — `UPROPERTY(EditDefaultsOnly, Category="Mover|UpDirection", meta = (EditCondition = "bHasUpDirectionOverride"))` — A fixed up direction to use if bHasUpDirectionOverride is true
- L974 _private member_ `bool bHasGravityOverride = false;` — `UPROPERTY(EditDefaultsOnly, Category="Mover|Gravity")` — Whether or not gravity is overridden on this actor. Otherwise, fall back on world settings. See @SetGravityOverride
- L987 _private member_ `bool bUseDeferredGroupMovement = false;` — `UPROPERTY(EditDefaultsOnly, Category="Mover", meta = (EditCondition = "Engine.SceneComponent.IsGroupedComponentMovementEnabled"))` — If true, then the transform updates applied in UMoverComponent::SetFrameStateFromContext will use a "deferred group move" to improve performance. It is not recommended that you enable this when you need exact, high fidelity characters such as your player character. This is mainly a benefit for scenarios with large amounts of NPCs or lower fidelity characters where it is acceptable to not have immediately applied transforms. This only does something if the "s.GroupedComponentMovement.Enable" CVar is set to true.
- L990 _private member_ `bool bInOnRegister = false;` — Transient flag indicating whether we are executing OnRegister().
- L993 _private member_ `bool bInInitializeComponent = false;` — Transient flag indicating whether we are executing InitializeComponent().
- L999 _private member_ `FQuat WorldToGravityTransform;` — `UPROPERTY(Category="Mover|Gravity", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))` — A cached quaternion representing the rotation from world space to gravity relative space defined by GravityAccelOverride.
- L1005 _private member_ `FQuat GravityToWorldTransform;` — `UPROPERTY(Category="Mover|Gravity", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))` — A cached quaternion representing the inverse rotation from world space to gravity relative space defined by GravityAccelOverride.
- L1010 _private member_ `TMap<UAnimMontage*, FMoverSimDrivenMontageEntry> DrivenMontageStateMap;` — Simulation-authoritative montage driving state. Tracks each active move (keyed by montage asset) to detect blend-out edge transitions and abrupt cancellations across dispatch cycles.
- L1017 _protected member_ `bool bSupportsKinematicBasedMovement = true;` — `UPROPERTY(EditDefaultsOnly, Category = "Mover")` — If enabled, this actor will be moved to follow a base actor that it's standing on. Typically disabled for physics-based movement, which handles based movement internally.
- L1019 _protected member_ `FMoverAuxStateContext CachedLastAuxState;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace MoverComponentConstants`
- L35 _externvar_ `extern const FVector DefaultGravityAccel;` (scope `MoverComponentConstants`) — Fallback gravity if not determined by the component or world (cm/s^2)
- L36 _externvar_ `extern const FVector DefaultUpDir;` (scope `MoverComponentConstants`) — Fallback up direction if not determined by the component or world (normalized)
- L40 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPreSimTick, const FMoverTimeStep&, TimeStep, const FMoverInputCmdContext&, InputCmd);` — Fired just before a simulation tick, regardless of being a re-simulated frame or not.
- L40 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPreSimTick, const FMoverTimeStep&, TimeStep, const FMoverInputCmdContext&, InputCmd);` — Fired just before a simulation tick, regardless of being a re-simulated frame or not.
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FMover_OnPreMovement, const FMoverTimeStep&, TimeStep, const FMoverInputCmdContext&, InputCmd, const FMoverSyncState&, SyncState, const FMoverAuxStateContext&, AuxState);` — Fired during a simulation tick, after the input is processed but before the actual move calculation.
- L43 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FMover_OnPreMovement, const FMoverTimeStep&, TimeStep, const FMoverInputCmdContext&, InputCmd, const FMoverSyncState&, SyncState, const FMoverAuxStateContext&, AuxState);` — Fired during a simulation tick, after the input is processed but before the actual move calculation.
- L46 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnPostMovement, const FMoverTimeStep&, TimeStep, FMoverSyncState&, SyncState, FMoverAuxStateContext&, AuxState);` — Fired during a simulation tick, after movement has occurred but before the state is finalized, allowing changes to the output state.
- L46 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnPostMovement, const FMoverTimeStep&, TimeStep, FMoverSyncState&, SyncState, FMoverAuxStateContext&, AuxState);` — Fired during a simulation tick, after movement has occurred but before the state is finalized, allowing changes to the output state.
- L49 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMover_OnPostSimTick, const FMoverTimeStep&, TimeStep);` — Fired after a simulation tick, regardless of being a re-simulated frame or not.
- L49 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMover_OnPostSimTick, const FMoverTimeStep&, TimeStep);` — Fired after a simulation tick, regardless of being a re-simulated frame or not.
- L53 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPostSimRollback, const FMoverTimeStep&, CurrentTimeStep, const FMoverTimeStep&, ExpungedTimeStep);` — Fired after a rollback. First param is the time step we've rolled back to. Second param is when we rolled back from, and represents a later frame that is no longer valid. Note: ExpungedTimeStep is called PreRollbackTimeStep in C++ code
- L53 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPostSimRollback, const FMoverTimeStep&, CurrentTimeStep, const FMoverTimeStep&, ExpungedTimeStep);` — Fired after a rollback. First param is the time step we've rolled back to. Second param is when we rolled back from, and represents a later frame that is no longer valid. Note: ExpungedTimeStep is called PreRollbackTimeStep in C++ code
- L56 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnMovementModeChanged, const FName&, PreviousMovementModeName, const FName&, NewMovementModeName);` — Fired after changing movement modes. First param is the name of the previous movement mode. Second is the name of the new movement mode.
- L56 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnMovementModeChanged, const FName&, PreviousMovementModeName, const FName&, NewMovementModeName);` — Fired after changing movement modes. First param is the name of the previous movement mode. Second is the name of the new movement mode.
- L59 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FMover_OnTeleportSucceeded, const FVector&, FromLocation, const FQuat&, FromRotation, const FVector&, ToLocation, const FQuat&, ToRotation);` — Fired when a teleport has succeeded
- L59 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FMover_OnTeleportSucceeded, const FVector&, FromLocation, const FQuat&, FromRotation, const FVector&, ToLocation, const FQuat&, ToRotation);` — Fired when a teleport has succeeded
- L62 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FMover_OnTeleportFailed, const FVector&, FromLocation, const FQuat&, FromRotation, const FVector&, ToLocation, const FQuat&, ToRotation, ETeleportFailureReason, TeleportFailureReason);` — Fired when a teleport has failed
- L62 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FMover_OnTeleportFailed, const FVector&, FromLocation, const FQuat&, FromRotation, const FVector&, ToLocation, const FQuat&, ToRotation, ETeleportFailureReason, TeleportFailureReason);` — Fired when a teleport has failed
- L66 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnGameplayTagAdded, const FGameplayTag&, Tag, const FMoverEventContext&, EventContext, bool, bIsExternalTag);` — Fired when a gameplay tag is added to the simulation (e.g. Mover_IsCrouching becomes set). Context carries bIsCausedByRollback and bIsDuringResimulation. bIsExternalTag is true if the tag was applied via AddGameplayTag rather than from within the simulation.
- L66 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnGameplayTagAdded, const FGameplayTag&, Tag, const FMoverEventContext&, EventContext, bool, bIsExternalTag);` — Fired when a gameplay tag is added to the simulation (e.g. Mover_IsCrouching becomes set). Context carries bIsCausedByRollback and bIsDuringResimulation. bIsExternalTag is true if the tag was applied via AddGameplayTag rather than from within the simulation.
- L70 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnGameplayTagRemoved, const FGameplayTag&, Tag, const FMoverEventContext&, EventContext, bool, bIsExternalTag);` — Fired when a gameplay tag is removed from the simulation. Context carries bIsCausedByRollback and bIsDuringResimulation. bIsExternalTag is true if the tag was removed via RemoveGameplayTag rather than from within the simulation.
- L70 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMover_OnGameplayTagRemoved, const FGameplayTag&, Tag, const FMoverEventContext&, EventContext, bool, bIsExternalTag);` — Fired when a gameplay tag is removed from the simulation. Context carries bIsCausedByRollback and bIsDuringResimulation. bIsExternalTag is true if the tag was removed via RemoveGameplayTag rather than from within the simulation.
- L73 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMover_OnTransitionTriggered, const UBaseMovementModeTransition*, ModeTransition);` — Fired after a transition has been triggered.
- L73 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMover_OnTransitionTriggered, const UBaseMovementModeTransition*, ModeTransition);` — Fired after a transition has been triggered.
- L76 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPostFinalize, const FMoverSyncState&, SyncState, const FMoverAuxStateContext&, AuxState);` — Fired after a frame has been finalized. This may be a resimulation or not. No changes to state are possible. Guaranteed to be on the game thread.
- L76 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnPostFinalize, const FMoverSyncState&, SyncState, const FMoverAuxStateContext&, AuxState);` — Fired after a frame has been finalized. This may be a resimulation or not. No changes to state are possible. Guaranteed to be on the game thread.
- L79 _delegate_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FMover_ProcessGeneratedMovement, const FMoverTickStartData&, StartState, const FMoverTimeStep&, TimeStep, FProposedMove&, OutProposedMove);` — Fired after proposed movement has been generated (i.e. after movement modes and layered moves have generated movement and mixed together).
- L79 _prototype_ `DECLARE_DYNAMIC_DELEGATE_ThreeParams(FMover_ProcessGeneratedMovement, const FMoverTickStartData&, StartState, const FMoverTimeStep&, TimeStep, FProposedMove&, OutProposedMove);` — Fired after proposed movement has been generated (i.e. after movement modes and layered moves have generated movement and mixed together).
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMover_OnPostSimEventReceived, const FMoverSimulationEventData&);` — Fired when a new event has been received from the simulation. This is a C++ only dispatch of the generic event. To dispatch the event to BP, prefer exposing the concrete event via a dedicated dynamic delegate (like OnMovementModeChanged).
- L83 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FMover_OnPostSimEventReceived, const FMoverSimulationEventData&);` — Fired when a new event has been received from the simulation. This is a C++ only dispatch of the generic event. To dispatch the event to BP, prefer exposing the concrete event via a dedicated dynamic delegate (like OnMovementModeChanged).
- L86 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnBasedMovementApplied, const FTransform&, TransformDelta, const FMoverTimeStep&, TimeStep);` — Fired after based movement is applied to this MoverComponent. TransformDelta is this component's cumulative transform change in world space during the most recent movement simulation tick.  (See @bSupportsKinematicBasedMovement)
- L86 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMover_OnBasedMovementApplied, const FTransform&, TransformDelta, const FMoverTimeStep&, TimeStep);` — Fired after based movement is applied to this MoverComponent. TransformDelta is this component's cumulative transform change in world space during the most recent movement simulation tick.  (See @bSupportsKinematicBasedMovement)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverDataModelTypes.h` (Public)


#### enum `EMoveInputType`  
`enum class EMoveInputType : uint8`  
_L17-29_
- reflection: `UENUM(BlueprintType)`
- desc: Used to identify how to interpret a movement input vector's values
- L19 _public enumerator_ `Invalid`
- L22 _public enumerator_ `DirectionalIntent` — Move with intent, as a per-axis magnitude [-1,1] (E.g., "move straight forward as fast as possible" would be (1, 0, 0) and "move straight left at half speed" would be (0, -0.5, 0) regardless of frame time). Zero vector indicates intent to stop.
- L25 _public enumerator_ `Velocity` — Move with a given velocity (units per second)
- L28 _public enumerator_ `None` — No move input of any type

#### struct `FCharacterDefaultInputs`  
`struct FCharacterDefaultInputs : public FMoverDataStructBase`  
_L34-131_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Data block containing all inputs that need to be authored and consumed for the default Mover character simulation
- L39 _public prototype_ `void SetMoveInput(EMoveInputType InMoveInputType, const FVector& InMoveInput);` — Sets the directional move inputs for a simulation frame
- L41 _public function_ `const FVector& GetMoveInput() const`
- L42 _public function_ `EMoveInputType GetMoveInputType() const`
- L46 _protected member_ `EMoveInputType MoveInputType;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mover)`
- L53 _protected member_ `FVector MoveInput;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mover)` — Representing the directional move input for this frame. Must be interpreted according to MoveInputType. Relative to MovementBase if set, world space otherwise. Will be truncated to match network serialization precision. Note: Use SetDirectionalInput or SetVelocityInput to set MoveInput and MoveInputType
- L58 _public member_ `FVector OrientationIntent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)` — Facing direction intent, as a normalized forward-facing direction. A zero vector indicates no intent to change facing direction. Relative to MovementBase if set, world space otherwise.
- L62 _public member_ `FRotator ControlRotation;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)` — World space orientation that the controls were based on. This is commonly a player's camera rotation.
- L66 _public member_ `FName SuggestedMovementMode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)` — Used to force the Mover actor into a different movement mode
- L70 _public member_ `bool bUsingMovementBase;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)` — Specifies whether we are using a movement base, which will affect how move inputs are interpreted
- L74 _public member_ `TObjectPtr<UPrimitiveComponent> MovementBase;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — Optional: when moving on a base, input may be relative to this object
- L78 _public member_ `FName MovementBaseBoneName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)` — Optional: for movement bases that are skeletal meshes, this is the bone we're based on. Only valid if MovementBase is set.
- L81 _public member_ `bool bIsJumpJustPressed;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L83 _public member_ `bool bIsJumpPressed;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mover)`
- L85 _public prototype_ `FVector GetMoveInput_WorldSpace() const;`
- L86 _public prototype_ `FVector GetOrientationIntentDir_WorldSpace() const;`
- L89 _public function_ `FCharacterDefaultInputs() : MoveInputType(EMoveInputType::None) , MoveInput(ForceInitToZero) , OrientationIntent(ForceInitToZero) , ControlRotation(ForceInitToZero) , SuggestedMovementMode(NAME_None) , bUsingMovementBase(false) , MovementBase(nullptr) , MovementBaseBoneName(NAME_None) , bIsJumpJustPressed(false) , bIsJumpPressed(false)`
- L103 _public prototype_ `virtual ~FCharacterDefaultInputs() = default;`
- L105 _public function_ `bool operator==(const FCharacterDefaultInputs& Other) const`
- L119 _public function_ `bool operator!=(const FCharacterDefaultInputs& Other) const`
- L122 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;` — @return newly allocated copy of this FCharacterDefaultInputs. Must be overridden by child classes
- L123 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L124 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L125 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L126 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L127 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L128 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L129 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L130 _public prototype_ `virtual void Decay(float DecayAmount) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FCharacterDefaultInputs > : public TStructOpsTypeTraitsBase2< FCharacterDefaultInputs >`  
_L134-141_
- inherits: `TStructOpsTypeTraitsBase2<FCharacterDefaultInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L137-140_

#### struct `FMoverDefaultSyncState`  
`struct FMoverDefaultSyncState : public FMoverDataStructBase`  
_L148-254_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: Data block containing basic sync state information
- L154 _protected member_ `FVector Location;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Position relative to MovementBase if set, world space otherwise
- L158 _protected member_ `FRotator Orientation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Forward-facing rotation relative to MovementBase if set, world space otherwise.
- L162 _protected member_ `FVector Velocity;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Linear velocity, units per second, relative to MovementBase if set, world space otherwise.
- L166 _protected member_ `FVector AngularVelocityDegrees;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Angular velocity, degrees per second, relative to MovementBase if set, world space otherwise.
- L171 _public member_ `FVector MoveDirectionIntent;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Mover)` — Movement intent direction relative to MovementBase if set, world space otherwise. Magnitude of range (0-1)
- L176 _protected member_ `TWeakObjectPtr<UPrimitiveComponent> MovementBase;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — Optional: when moving on a base, input may be relative to this object
- L180 _protected member_ `FName MovementBaseBoneName;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — Optional: for movement bases that are skeletal meshes, this is the bone we're based on. Only valid if MovementBase is set.
- L183 _protected member_ `FVector MovementBasePos;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)`
- L186 _protected member_ `FQuat MovementBaseQuat;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)`
- L190 _public function_ `FMoverDefaultSyncState() : Location(ForceInitToZero) , Orientation(ForceInitToZero) , Velocity(ForceInitToZero) , AngularVelocityDegrees(ForceInitToZero) , MoveDirectionIntent(ForceInitToZero) , MovementBase(nullptr) , MovementBaseBoneName(NAME_None) , MovementBasePos(ForceInitToZero) , MovementBaseQuat(FQuat::Identity)`
- L203 _public prototype_ `virtual ~FMoverDefaultSyncState() = default;`
- L206 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;` — @return newly allocated copy of this FMoverDefaultSyncState. Must be overridden by child classes
- L208 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L210 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L212 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L214 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L216 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L219 _public prototype_ `void SetTransforms_WorldSpace(FVector WorldLocation, FRotator WorldOrient, FVector WorldVelocity, UPrimitiveComponent* Base=nullptr, FName BaseBone = NAME_None);` — `UE_DEPRECATED(5.7, "Use the SetTransforms_WorldSpace with an angular velocity")`
- L221 _public prototype_ `void SetTransforms_WorldSpace(FVector WorldLocation, FRotator WorldOrient, FVector WorldVelocity, FVector WorldAngularVelocityDegrees, UPrimitiveComponent* Base=nullptr, FName BaseBone = NAME_None);`
- L224 _public prototype_ `bool SetMovementBase(UPrimitiveComponent* Base, FName BaseBone=NAME_None);` — Returns whether the base setting succeeded
- L227 _public prototype_ `bool UpdateCurrentMovementBase();` — Refreshes captured movement base transform based on its current state, while maintaining the same base-relative transforms
- L230 _public prototype_ `bool IsNearlyEqual(const FMoverDefaultSyncState& Other) const;` — Queries
- L232 _public function_ `UPrimitiveComponent* GetMovementBase() const`
- L233 _public function_ `FName GetMovementBaseBoneName() const`
- L234 _public function_ `FVector GetCapturedMovementBasePos() const`
- L235 _public function_ `FQuat GetCapturedMovementBaseQuat() const`
- L237 _public prototype_ `FVector GetLocation_WorldSpace() const;`
- L238 _public prototype_ `FVector GetLocation_BaseSpace() const;` — If there is no movement base set, these will be the same as world space
- L240 _public prototype_ `FVector GetIntent_WorldSpace() const;`
- L241 _public prototype_ `FVector GetIntent_BaseSpace() const;`
- L243 _public prototype_ `FVector GetVelocity_WorldSpace() const;`
- L244 _public prototype_ `FVector GetVelocity_BaseSpace() const;`
- L246 _public prototype_ `FRotator GetOrientation_WorldSpace() const;`
- L247 _public prototype_ `FRotator GetOrientation_BaseSpace() const;`
- L249 _public prototype_ `FTransform GetTransform_WorldSpace() const;`
- L250 _public prototype_ `FTransform GetTransform_BaseSpace() const;`
- L252 _public prototype_ `FVector GetAngularVelocityDegrees_WorldSpace() const;`
- L253 _public prototype_ `FVector GetAngularVelocityDegrees_BaseSpace() const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FMoverDefaultSyncState > : public TStructOpsTypeTraitsBase2< FMoverDefaultSyncState >`  
_L257-264_
- inherits: `TStructOpsTypeTraitsBase2<FMoverDefaultSyncState>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L260-263_

#### class `UMoverDataModelBlueprintLibrary`  
`class UMoverDataModelBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L271-311_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library to make it easier to work with Mover data structs, since we can't add UFUNCTIONs to structs
- L279 _public prototype_ `static void SetDirectionalInput(UPARAM(Ref) FCharacterDefaultInputs& Inputs, const FVector& DirectionInput);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets move input from a unit length vector representing directional intent
- L283 _public prototype_ `static void SetVelocityInput(UPARAM(Ref) FCharacterDefaultInputs& Inputs, const FVector& VelocityInput = FVector::ZeroVector);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Sets move input from a vector representing desired velocity c/m^2
- L287 _public prototype_ `static FVector GetMoveDirectionIntentFromInputs(const FCharacterDefaultInputs& Inputs);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the move direction intent, if any, in world space
- L294 _public prototype_ `static FVector GetLocationFromSyncState(const FMoverDefaultSyncState& SyncState);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the location in world space
- L298 _public prototype_ `static FVector GetMoveDirectionIntentFromSyncState(const FMoverDefaultSyncState& SyncState);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the move direction intent, if any, in world space
- L302 _public prototype_ `static FVector GetVelocityFromSyncState(const FMoverDefaultSyncState& SyncState);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the velocity in world space
- L306 _public prototype_ `static FVector GetAngularVelocityDegreesFromSyncState(const FMoverDefaultSyncState& SyncState);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the angular velocity in world space, in degrees per second
- L310 _public prototype_ `static FRotator GetOrientationFromSyncState(const FMoverDefaultSyncState& SyncState);` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Returns the orientation in world space

#### struct `FMoverAIInputs`  
`struct FMoverAIInputs : public FMoverDataStructBase`  
_L316-340_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FMoverDataStructBase`
- desc: AI-related movement inputs (e.g., RVO avoidance)
- L323 _public member_ `FVector RVOVelocityDelta;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)` — RVO Velocity calculated on the Server
- L325 _public function_ `FMoverAIInputs() : RVOVelocityDelta(ForceInitToZero)`
- L330 _public prototype_ `virtual ~FMoverAIInputs() = default;`
- L332 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L333 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L334 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L335 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L336 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L337 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;`
- L338 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct) override;`
- L339 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverAIInputs> : public TStructOpsTypeTraitsBase2<FMoverAIInputs>`  
_L343-350_
- inherits: `TStructOpsTypeTraitsBase2<FMoverAIInputs>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L346-349_

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`
- L138 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anonc46d79a10103`)
- L139 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonc46d79a10103`)
- L261 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anonc46d79a10203`)
- L262 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonc46d79a10203`)
- L347 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anonc46d79a10303`)
- L348 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonc46d79a10303`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverDeveloperSettings.h` (Public)


#### class `UMoverDeveloperSettings`  
`class UMoverDeveloperSettings : public UDeveloperSettingsBackedByCVars`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "Mover Settings"))`
- inherits: `UDeveloperSettingsBackedByCVars`
- desc: Developer settings for the Mover plugin
- L17 _public prototype_ `UMoverDeveloperSettings();`
- L23 _public member_ `int32 MaxTimesToRefundSubstep;` — `UPROPERTY(config, EditAnywhere, Category = "Mover")` — This specifies the number of times a movement mode can refund all of the time in a substep before we back out to avoid freezing the game/editor

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverGameplayTagLog.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace MoverCVars`
- L11 _externvar_ `extern bool bEnableGameplayTagLog;` (scope `MoverCVars`)
- L16 _prototype_ `void LogGameplayTagDriftDetect( const FString& ActorName, const TCHAR* RoleStr, const FMoverTimeStep& TimeStep, const FGameplayTag& Tag, bool bWasAdded, const TArray<TSharedPtr<FMoverSimulationEventData>>& Events, const FGameplayTagContainer& PreviousTags, const FGameplayTagContainer& NewTags);` — Logs the [GT:DriftDetect] header line and a [GT:DriftDetect:Event] line per queued event. The CVar check is included; safe to call unconditionally.
- L33 _macro_ `#define MOVER_TAG_LOG(Category, Format, ...) do {} while (0)`
- L35 _macro_ `#define MOVER_TAG_LOG(Category, StepAndFormat, ...) \`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMover, Log, All);`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverModule.h` (Public)


#### class `FMoverModule`  
`class FMoverModule : public IModuleInterface`  
_L16-29_
- inherits: `IModuleInterface`
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `void ShowTrajectory(const TArray<FString>& Args, UWorld* World);`
- L24 _public prototype_ `void ShowTrail(const TArray<FString>& Args, UWorld* World);`
- L25 _public prototype_ `void ShowCorrections(const TArray<FString>& Args, UWorld* World);`
- L28 _private member_ `TArray<IConsoleCommand*> ConsoleCommands;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mover` (scope `UE`)
- L13 _externvar_ `extern int32 DisableDataCopyInPlace;` (scope `UE::Mover`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverPoseSearchTrajectoryPredictor.h` (Public)


#### class `UMoverTrajectoryPredictor`  
`class UMoverTrajectoryPredictor : public UObject, public IPoseSearchTrajectoryPredictorInterface`  
_L19-55_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UObject,IPoseSearchTrajectoryPredictorInterface`
- desc: Trajectory predictor that can query from a Mover-driven actor, for use with Pose Search
- L26 _public function_ `void Setup(UMoverComponent* InMoverComponent)` — `UFUNCTION(BlueprintCallable, Category = "Animation|PoseSearch|Experimental")`
- L28 _public prototype_ `virtual void Predict(FTransformTrajectory& InOutTrajectory, int32 NumPredictionSamples, float SecondsPerPredictionSample, int32 NumHistorySamples) override;`
- L30 _public prototype_ `virtual void GetGravity(FVector& OutGravityAccel) override;`
- L32 _public prototype_ `virtual void GetCurrentState(FVector& OutPosition, FQuat& OutFacing, FVector& OutVelocity) override;`
- L34 _public prototype_ `virtual void GetVelocity(FVector& OutVelocity) override;`
- L36 _public prototype_ `virtual void GetAngularVelocity(FVector& OutAngularVelocityDegrees) override;`
- L39 _public prototype_ `static void Predict(UMoverComponent& Mover, FTransformTrajectory& InOutTrajectory, int32 NumPredictionSamples, float SecondsPerPredictionSample, int32 NumHistorySamples, float MoverSamplingInterval, bool bDisableGravity = true);` — Share code in static helper functions so we can call it from AnimNext, which doesn't support interfaces
- L40 _public prototype_ `static void GetCurrentState(UMoverComponent& Mover, FVector& OutPosition, FQuat& OutFacing, FVector& OutVelocity);`
- L44 _protected member_ `TObjectPtr<UMoverComponent> MoverComponent;`
- L49 _protected member_ `bool bDisableGravity = false;` — `UPROPERTY(EditAnywhere, Category = "Animation|PoseSearch|Experimental", BlueprintReadWrite)` — If true, the prediction will not take gravity into account If false, mover prediction will account for gravity (e.g. in falling state)
- L54 _protected member_ `FFrameRate MoverSamplingFrameRate = FFrameRate(60, 1);` — `UPROPERTY(EditAnywhere, Category = "Animation|PoseSearch|Experimental", BlueprintReadWrite)` — Sampling frame rate to query the mover, doesn't necessarily match the SecondsPerPredictionSample which is used to write to the trajectory This allows sampling of mover at a high frequency for accuracy but then we can downsample the results to a more coarse grained trajectory

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverSchedulingUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mover` (scope `UE`)
- L18 _prototype_ `FScheduledInstantMovementEffect MakeScheduledEffect(const TScriptInterface<IMoverBackendLiaisonInterface>& Backend, const FMoverTimeStep& TimeStep, TSharedPtr<FInstantMovementEffect> InstantMovementEffect);` (scope `UE::Mover`) — Turns a FInstantMovementEffect into a scheduled one (FScheduledInstantMovementEffect) The effect can be scheduled to apply immediately, or scheduled to apply with a delay @param Backend the simulation backend which implements the details of whether the simulation advances in fixed dt and how long to schedule in the future for networked events @param TimeStep the time step of the current or upcoming tick @param InstantMovementEffect the effect to schedule
- L21 _prototype_ `FScheduledInstantMovementEffect MakeScheduledEffectForNextFrame(const TScriptInterface<IMoverBackendLiaisonInterface>& Backend, const FMoverTimeStep& TimeStep, TSharedPtr<FInstantMovementEffect> InstantMovementEffect);` (scope `UE::Mover`) — Same as above but schedules the effect to run on the next frame. This is best used for fixed tick mode, it will add a small SchedulingDelaySeconds in the variable tick case
- L29 _prototype_ `FScheduledLayeredMove MakeScheduledMove(const TScriptInterface<IMoverBackendLiaisonInterface>& Backend, const FMoverTimeStep& TimeStep, TSharedPtr<FLayeredMoveBase> LayeredMove);` (scope `UE::Mover`) — Turns a FLayeredMove into a scheduled one (FScheduledLayeredMove) The move can be scheduled to apply immediately, or scheduled to apply with a delay @param Backend the simulation backend which implements the details of whether the simulation advances in fixed dt and how long to schedule in the future for networked events @param TimeStep the time step of the current or upcoming tick @param LayeredMove the move to schedule
- L31 _prototype_ `FScheduledLayeredMove MakeScheduledMoveForNextFrame(const TScriptInterface<IMoverBackendLiaisonInterface>& Backend, const FMoverTimeStep& TimeStep, TSharedPtr<FLayeredMoveBase> LayeredMove);` (scope `UE::Mover`) — Same as above but schedules the effect to run on the next frame. This is best used for fixed tick mode, it will add a small SchedulingDelaySeconds in the variable tick case

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverSimulation.h` (Public)


#### class `UMoverSimulation`  
`class UMoverSimulation : public UObject`  
_L24-130_
- reflection: `UCLASS(Abstract, MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: WIP Base class for a Mover simulation. The simulation is intended to be the thing that updates the Mover state and should be safe to run on an async thread
- L29 _public prototype_ `UMoverSimulation();`
- L33 _public prototype_ `const UMoverBlackboard* GetBlackboard() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Warning: the regular blackboard will be fully replaced by the rollback blackboard in the future
- L37 _public prototype_ `UMoverBlackboard* GetBlackboard_Mutable();` — `UFUNCTION(BlueprintPure, Category = Mover)` — Warning: the regular blackboard will be fully replaced by the rollback blackboard in the future
- L40 _public prototype_ `FRollbackBlackboardSimWrapper GetRollbackBlackboardSimWrapper() const;` — `UFUNCTION(BlueprintPure, Category = Mover)`
- L44 _public prototype_ `FRollbackBlackboardSimWrapper GetRollbackBlackboardPredictionWrapper() const;` — `UFUNCTION(BlueprintPure, Category = Mover)` — Get accessor for the blackboard to be used predictively. You can read from it, but any writes will be temporary and thrown away once prediction is finished.
- L48 _public function_ `virtual void QueueNextMode(FModeChangeParams ModeChangeParams)` — `UFUNCTION(BlueprintCallable, Category = Mover, meta=(BlueprintThreadSafe))` — Queues a mode change for the next opportunity. This function is intended to be threadsafe and can be called from inside or outside of the simulation.
- L52 _public function_ `virtual FName GetNextModeName() const` — `UFUNCTION(BlueprintPure, Category = Mover, meta = (BlueprintThreadSafe))` — Gets the anticipated next mode, either the next queued one or the current mode.
- L54 _public function_ `virtual bool HasFeaturesWithTag(FGameplayTag TagToMatch, bool bRequireExactMatch) const`
- L55 _public function_ `virtual void CancelFeaturesWithTag(FGameplayTag TagToCancel, bool bRequireExactMatch = false)`
- L59 _public function_ `virtual void RegisterMovementMode(FModeRegistrationParams ModeRegisterParams)` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (BlueprintThreadSafe))` — Registers a new movement mode for use in the simulation.
- L63 _public function_ `virtual void UnregisterMovementMode(FModeRegistrationParams ModeRegisterParams)` — `UFUNCTION(BlueprintCallable, Category = Mover, meta = (BlueprintThreadSafe))` — Unregisters a movement mode from the simulation
- L66 _public function_ `virtual const FMovementModifierBase* FindQueuedModifier(FMovementModifierHandle ModifierHandle) const` — Modifier management functions
- L67 _public function_ `virtual const FMovementModifierBase* FindQueuedModifierByType(const UScriptStruct* ModifierType) const`
- L68 _public function_ `virtual FMovementModifierHandle QueueMovementModifier(TSharedPtr<FMovementModifierBase> Modifier)`
- L69 _public function_ `virtual void CancelModifierFromHandle(FMovementModifierHandle ModifierHandle)`
- L77 _public prototype_ `void QueueLayeredMove(const FScheduledLayeredMove& Move);` — Queue a struct-based layered move (GT staging, write-locked).
- L80 _public prototype_ `void QueueInstantMovementEffect(const FScheduledInstantMovementEffect& Effect);` — Queue a scheduled instant movement effect (GT staging, write-locked).
- L83 _public prototype_ `void QueueLayeredMoveInstance(TSharedPtr<FLayeredMoveInstance> MoveInstance);` — Queue an instanced layered move (GT staging, write-locked).
- L86 _public prototype_ `TArray<FScheduledLayeredMove> ConsumeQueuedLayeredMoves();` — Consume all queued struct-based layered moves. Empties the queue under a write lock.
- L89 _public prototype_ `TArray<FScheduledInstantMovementEffect> ConsumeQueuedInstantMovementEffects();` — Consume all queued instant movement effects. Empties the queue under a write lock.
- L92 _public prototype_ `TArray<TSharedPtr<FLayeredMoveInstance>> ConsumeQueuedLayeredMoveInstances();` — Consume all queued instanced layered moves. Empties the queue under a write lock.
- L103 _public function_ `virtual void AttemptTeleport(const FMoverTimeStep& TimeStep, const FTransform& TargetTransform, bool bUseActorRotation, FMoverSyncState& OutputState)` — `UFUNCTION(BlueprintCallable, Category = Mover)` — Attempt to teleport to TargetTransform. The teleport is not guaranteed to happen. This function is meant to be called by an instant movement effect as part of its effect application. If it succeeds a FTeleportSucceededEventData will be emitted, if it fails a FTeleportFailedEventData will be sent. @param TimeStep The time step of the current step or substep being simulated. This will come from the ApplyMovementEffect function. @param TargetTransform The transform to teleport to. In the case bUseActorRotation is true, the rotation of this transform will be ignored. @param bUseActorRotation If true, the rotation will not be modified upon teleportation. If false, the rotation in TargetTransform will be used to orient the teleported. @param OutputState This is the sync state that me modified as a result of the application of this effect. Like TimeStep, this should come from the ApplyMovementEffect function.
- L108 _protected member_ `TObjectPtr<UMoverBlackboard> Blackboard = nullptr;` — `UPROPERTY(Transient)`
- L111 _protected member_ `TObjectPtr<URollbackBlackboard> RollbackBlackboard = nullptr;` — `UPROPERTY(Transient)`
- L113 _protected member_ `FRollbackBlackboardSimWrapper RollbackBlackboardSimWrapper;`
- L120 _private member_ `mutable FTransactionallySafeRWLock SimQueueLock;` — Protects the three simulation-level staging queues below.
- L123 _private member_ `TArray<FScheduledLayeredMove> QueuedLayeredMoves;` — Struct-based layered moves staged by the GT, consumed by the FSM or ChaosMover backend each tick.
- L126 _private member_ `TArray<FScheduledInstantMovementEffect> QueuedInstantMovementEffects;` — Instant movement effects staged by the GT, consumed by the FSM or ChaosMover backend each tick.
- L129 _private member_ `TArray<TSharedPtr<FLayeredMoveInstance>> QueuedLayeredMoveInstances;` — Instanced layered moves staged by the GT (via MakeAndQueueLayeredMove), consumed each tick.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverSimulationTypes.h` (Public)


#### struct `FMovementModeTickEndState`  
`struct FMovementModeTickEndState`  
_L52-78_
- reflection: `USTRUCT(BlueprintType)`
- desc: Filled out by a MovementMode during simulation tick to indicate its ending state, allowing for a residual time step and switching modes mid-tick
- L56 _public function_ `FMovementModeTickEndState()`
- L61 _public function_ `void ResetToDefaults()`
- L70 _public member_ `float RemainingMs;` — `UPROPERTY(BlueprintReadWrite, Category=Mover)` — Any unused tick time
- L73 _public member_ `FName NextModeName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, Category=Mover)`
- L77 _public member_ `bool bEndedWithNoChanges = false;` — `UPROPERTY(BlueprintReadWrite, Category=Mover)` — Affirms that no state changes were made during this simulation tick. Can help optimizations if modes set this during sim tick.

#### struct `FMoverSchedulingInfo`  
`struct FMoverSchedulingInfo`  
_L81-152_
- reflection: `USTRUCT()`
- L85 _public function_ `bool ShouldExecuteAtTimeStep(const FMoverTimeStep& TimeStep) const`
- L90 _public function_ `bool ShouldExecuteAtTime(const FMoverTime& ServerTime) const`
- L95 _public function_ `bool ShouldExecuteAtFrame(int32 CurrentServerFrame) const`
- L101 _public function_ `bool ShouldExecuteAtTimeMs(double CurrentServerTimeMs) const`
- L107 _public function_ `bool ShouldRollBackAtTimeStep(const FMoverTimeStep& NewTimeStep) const`
- L112 _public function_ `bool ShouldRollBackAtFrame(int32 NewServerFrame) const`
- L118 _public function_ `bool ShouldRollBackAtTimeMs(double NewServerTimeMs) const`
- L124 _public function_ `FString ToString() const`
- L137 _public member_ `FMoverTime ServerIssuanceTime;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Server time at which this scheduled event was issued bIsFixedDt TRUE: - ServerIssuanceTime.FrameCount will be valid and set to the backend's GetCurrentSimFrame, i.e. that of the server frame count of the first async step that will be processing this. - ServerIssuanceTime.TimeMs MAY be set to ServerIssuanceTime.TimeMs * AsyncFixedDt * 1000, is only here for reference, and it NOT an interpolated time bIsFixedDt FALSE: - ServerIssuanceTime.FrameCount will be invalid, do not use - ServerIssuanceTime.TimeMs will be set to the backend's GetCurrentSimTimeMs
- L147 _public member_ `FMoverTime ServerExecutionTime;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Server time at which this scheduled event should take effect bIsFixedDt TRUE: - ServerExecutionTime.FrameCount will be valid and set relative to the backend's GetCurrentSimFrame, i.e. that of the server frame count of the first async step that will be processing this. - ServerExecutionTime.TimeMs MAY be set to ServerExecutionTime.FrameCount * AsyncFixedDt * 1000, is only here for reference, and it NOT an interpolated time bIsFixedDt FALSE: - ServerExecutionTime.FrameCount will be invalid, do not use - ServerExecutionTime.TimeMs will be set relative to the backend's GetCurrentSimTimeMs
- L151 _public member_ `bool bIsFixedDt = true;` — `UPROPERTY(VisibleAnywhere, Category = "Mover")` — Whether this time was set in the context of a fixed or variable time advance scheme. This should correspond to the backend's IsFixedDt()

#### struct `FScheduledInstantMovementEffect`  
`struct FScheduledInstantMovementEffect`  
_L155-167_
- reflection: `USTRUCT()`
- L159 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L164 _public member_ `FMoverSchedulingInfo SchedulingInfo;`
- L166 _public member_ `TSharedPtr<FInstantMovementEffect> Effect;`

#### struct `FScheduledLayeredMove`  
`struct FScheduledLayeredMove`  
_L170-182_
- reflection: `USTRUCT()`
- L174 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L179 _public member_ `FMoverSchedulingInfo SchedulingInfo;`
- L181 _public member_ `TSharedPtr<FLayeredMoveBase> Move;`

#### struct `FMoverInputCmdContext`  
`struct FMoverInputCmdContext`  
_L189-221_
- reflection: `USTRUCT(BlueprintType)`
- desc: The client generates this representation of "input" to the simulated actor for one simulation frame. This can be direct mapping of controls, or more abstract data. It is composed of a collection of typed structs that can be customized per project.
- L194 _public member_ `FMoverDataCollection InputCollection;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L196 _public function_ `UScriptStruct* GetStruct() const`
- L201 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L207 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L212 _public function_ `void Interpolate(const FMoverInputCmdContext* From, const FMoverInputCmdContext* To, float Pct)`
- L217 _public function_ `void Reset()`

#### struct `FMoverSyncState`  
`struct FMoverSyncState`  
_L228-317_
- reflection: `USTRUCT(BlueprintType)`
- desc: State we are evolving frame to frame and keeping in sync (frequently changing). It is composed of a collection of typed structs that can be customized per project. Mover actors are required to have FMoverDefaultSyncState as one of these structs.
- L236 _public member_ `FName MovementMode;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Mover)` — The mode we ended up in from the prior frame, and which we'll start in during the next frame
- L240 _public member_ `FLayeredMoveGroup LayeredMoves;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Mover)` — Additional moves influencing our proposed motion
- L244 _public member_ `FLayeredMoveInstanceGroup LayeredMoveInstances;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Mover)` — Additional moves influencing our proposed motion
- L248 _public member_ `FMovementModifierGroup MovementModifiers;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Mover)` — Additional modifiers influencing our simulation
- L251 _public member_ `FMoverDataCollection SyncStateCollection;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L253 _public function_ `FMoverSyncState()`
- L258 _public function_ `bool HasSameContents(const FMoverSyncState& Other) const`
- L267 _public function_ `UScriptStruct* GetStruct() const`
- L270 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L281 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L290 _public function_ `bool ShouldReconcile(const FMoverSyncState& AuthorityState) const`
- L297 _public function_ `void Interpolate(const FMoverSyncState* From, const FMoverSyncState* To, float Pct)`
- L309 _public function_ `void Reset()` — Resets the sync state to its default configuration and removes any active or queued layered modes and modifiers

#### struct `FMoverDoubleBuffer`  
`template<typename T> struct FMoverDoubleBuffer`  
_L323-353_
- desc: Double Buffer struct for various Mover data.
- L326 _public function_ `void SetBufferedData(const T& InDataToCopy)` — Sets all buffered data - usually used for initializing data
- L333 _public function_ `const T& GetReadable() const` — Gets data that is safe to read and is not being written to
- L339 _public function_ `T& GetWritable()` — Gets data that is being written to and is expected to change
- L345 _public function_ `void Flip()` — Flips which data in the buffer we return for reading and writing
- L351 _private member_ `uint32 ReadIndex = 0;`
- L352 _private member_ `T Buffer[2];`

#### struct `FMoverAuxStateContext`  
`struct FMoverAuxStateContext`  
_L357-387_
- reflection: `USTRUCT(BlueprintType)`
- desc: Auxiliary state that is input into the simulation (changes rarely)
- L362 _public function_ `UScriptStruct* GetStruct() const`
- L364 _public function_ `bool ShouldReconcile(const FMoverAuxStateContext& AuthorityState) const`
- L369 _public function_ `void NetSerialize(const FNetSerializeParams& P)`
- L375 _public function_ `void ToString(FAnsiStringBuilderBase& Out) const`
- L380 _public function_ `void Interpolate(const FMoverAuxStateContext* From, const FMoverAuxStateContext* To, float Pct)`
- L386 _public member_ `FMoverDataCollection AuxStateCollection;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`

#### struct `FMoverTickStartData`  
`struct FMoverTickStartData`  
_L394-413_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains all state data for the start of a simulation tick
- L398 _public function_ `FMoverTickStartData()`
- L399 _public function_ `FMoverTickStartData( const FMoverInputCmdContext& InInputCmd, const FMoverSyncState& InSyncState, const FMoverAuxStateContext& InAuxState) : InputCmd(InInputCmd), SyncState(InSyncState), AuxState(InAuxState)`
- L408 _public member_ `FMoverInputCmdContext InputCmd;` — `UPROPERTY(BlueprintReadOnly, Category=Mover)`
- L410 _public member_ `FMoverSyncState SyncState;` — `UPROPERTY(BlueprintReadOnly, Category=Mover)`
- L412 _public member_ `FMoverAuxStateContext AuxState;` — `UPROPERTY(BlueprintReadOnly, Category=Mover)`

#### struct `FMoverTickEndData`  
`struct FMoverTickEndData`  
_L419-446_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains all state data produced by a simulation tick, including new simulation state
- L423 _public function_ `FMoverTickEndData()`
- L424 _public function_ `FMoverTickEndData( const FMoverSyncState* SyncState, const FMoverAuxStateContext* AuxState)`
- L432 _public function_ `void InitForNewFrame()`
- L439 _public member_ `FMoverSyncState SyncState;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Mover)`
- L441 _public member_ `FMoverAuxStateContext AuxState;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Mover)`
- L443 _public member_ `FMovementModeTickEndState MovementEndState;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Mover)`
- L445 _public member_ `FMovementRecord MoveRecord;`

#### struct `FMoverSimContext`  
`struct FMoverSimContext`  
_L457-473_
- reflection: `USTRUCT(BlueprintType)`
- desc: FMoverSimContext: contains information about the systems supporting the active simulation. This is commonly passed in to in-simulation functions and events. All objects are guaranteed to exist for the lifetime of any function called with FMoverSimContext as an argument. Do not cache references to them, as their lifetime is not guaranteed outside of the simulation.
- L462 _public member_ `TObjectPtr<UMoverSimulation> Simulation = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)`
- L465 _public member_ `mutable FRollbackBlackboardSimWrapper Blackboard;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)`
- L472 _public member_ `TObjectPtr<UObject> SimulationOwner = nullptr;` — `UPROPERTY(BlueprintReadOnly, Category=Mover)` — Owner of the simulation. True type is dependent on the situation (Actor, MoverComp, SG entity, etc.) May be null when its lifetime can't be guaranteed

#### struct `FSimulationTickParams`  
`struct FSimulationTickParams`  
_L478-506_
- reflection: `USTRUCT(BlueprintType)`
- desc: Input parameters to provide context for SimulationTick functions
- L484 _public member_ `FMoverSimContext SimContext;` — `UPROPERTY(BlueprintReadOnly, Category = Mover)` — Information about the systems supporting the active simulation
- L489 _public member_ `FMovingComponentSet MovingComps;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mover)` — Components involved in movement by the simulation This will be empty when the simulation is ticked asynchronously
- L493 _public member_ `TObjectPtr<UMoverBlackboard> SimBlackboard;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mover)` — Blackboard (old style, soon to be removed)
- L497 _public member_ `FMoverTickStartData StartState;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mover)` — Simulation state data at the start of the tick, including Input Cmd
- L501 _public member_ `FMoverTimeStep TimeStep;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mover)` — Time and frame information for this tick
- L505 _public member_ `FProposedMove ProposedMove;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Mover)` — Proposed movement for this tick

#### class `UMoverInputProducerInterface`  
`class UMoverInputProducerInterface : public UInterface`  
_L509-512_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType)`
- inherits: `UInterface`

#### class `IMoverInputProducerInterface`  
`class IMoverInputProducerInterface : public IInterface`  
_L517-525_
- inherits: `IInterface`
- desc: MoverInputProducerInterface: API for any object that can produce input for a Mover simulation frame
- L524 _public prototype_ `void ProduceInput(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult);` — `UFUNCTION(BlueprintNativeEvent)` — Contributes additions to the input cmd for this simulation frame. Typically this is translating accumulated user input (or AI state) into parameters that affect movement.

#### struct `FMoverPredictTrajectoryParams`  
`struct FMoverPredictTrajectoryParams`  
_L533-573_
- reflection: `USTRUCT(BlueprintType)`
- desc: FMoverPredictTrajectoryParams: parameter block for querying future trajectory samples based on a starting state See UMoverComponent::GetPredictedTrajectory
- L540 _public member_ `int32 NumPredictionSamples = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta = (ClampMin = 1))` — How many samples to predict into the future, including the first sample, which is always a snapshot of the starting state with 0 accumulated time.
- L544 _public member_ `float SecondsPerSample = 0.333f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta = (ClampMin = 0.00001))` — How much time between predicted samples
- L550 _public member_ `bool bUseVisualComponentRoot = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true, samples are based on the visual component transform, rather than the 'updated' movement root. Typically, this is a mesh with its component location at the bottom of the collision primitive. If false, samples are from the movement root.
- L554 _public member_ `bool bDisableGravity = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true, gravity will not taken into account during prediction
- L558 _public member_ `TOptional<FMoverTime> OptionalStartTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional starting time. If not set, prediction will begin from the current sim time.
- L562 _public member_ `TOptional<FMoverSyncState> OptionalStartSyncState;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional starting sync state. If not set, prediction will begin from the current state.
- L566 _public member_ `TOptional<FMoverAuxStateContext> OptionalStartAuxState;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional starting aux state. If not set, prediction will begin from the current state.
- L571 _public member_ `TArray<FMoverInputCmdContext> OptionalInputCmds;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional input cmds to use, one per sample. If none are specified, prediction will begin with last-used inputs. If too few are specified for the number of samples, the final input in the array will be used repeatedly to cover remaining samples.

#### struct `FMoverSimEventGameThreadContext`  
`struct FMoverSimEventGameThreadContext`  
_L576-582_
- reflection: `USTRUCT()`
- L581 _public member_ `UMoverComponent* MoverComp = nullptr;`

#### struct `FMoverSimulationEventData`  
`struct FMoverSimulationEventData`  
_L585-650_
- reflection: `USTRUCT()`
- L589 _public typedef_ `using FEventProcessedCallbackPtr = std::function<void(const FMoverSimulationEventData& Data, const FMoverSimEventGameThreadContext& GameThreadContext)>;`
- L591 _public function_ `FMoverSimulationEventData(const FMoverTimeStep& InEventTime, FEventProcessedCallbackPtr InEventProcessedCallback = nullptr) : EventProcessedCallback(InEventProcessedCallback) , Context(InEventTime)`
- L597 _public function_ `FMoverSimulationEventData()`
- L598 _public prototype_ `virtual ~FMoverSimulationEventData() = default;`
- L601 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;` — User must override
- L604 _public function_ `template<typename T> T* CastTo_Mutable()`
- L610 _public function_ `template<typename T> const T* CastTo() const`
- L615 _public function_ `void OnEventProcessed(const FMoverSimEventGameThreadContext& GameThreadContext) const`
- L623 _public function_ `void SetEventProcessedCallback(FEventProcessedCallbackPtr Callback)`
- L628 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const`
- L638 _private member_ `FEventProcessedCallbackPtr EventProcessedCallback = nullptr;` — This callback is fired when the event is processed on the game thread This is called before and in addition to any type based handling
- L642 _public member_ `FMoverEventContext Context;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L649 _public member_ `bool bReEmitOnResim = false;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — If true, this event will always re-emit during resimulation and is never added to the ProcessedEvents dedup list. Set this on event types that represent state changes which must be faithfully replayed on resim (e.g. gameplay tag adds/removes). Leave false for punctual one-shot events that the Game Thread has already received and must not see again.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverSimulationEventData> : public TStructOpsTypeTraitsBase2<FMoverSimulationEventData>`  
_L656-659_
- inherits: `TStructOpsTypeTraitsBase2<FMoverSimulationEventData>`
- desc: WithCopy = true: EventProcessedCallback is a std::function. FInstancedStruct::InitializeAs falls back to FMemory::Memcpy when WithCopy is absent, which is UB for std::function (shallow copy of internal heap storage). operator= must be used instead so std::function copies correctly.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L658-658_

#### struct `FMovementModeChangedEventData`  
`struct FMovementModeChangedEventData : public FMoverSimulationEventData`  
_L662-697_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L666 _public function_ `FMovementModeChangedEventData(const FMoverTimeStep& InEventTime, const FName InPreviousModeName, const FName InNewModeName, FEventProcessedCallbackPtr InEventProcessedCallback = nullptr) : FMoverSimulationEventData(InEventTime, InEventProcessedCallback) , PreviousModeName(InPreviousModeName) , NewModeName(InNewModeName)`
- L672 _public function_ `FMovementModeChangedEventData()`
- L674 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L679 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const override`
- L693 _public member_ `FName PreviousModeName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L696 _public member_ `FName NewModeName = NAME_None;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovementModeChangedEventData> : public TStructOpsTypeTraitsBase2<FMovementModeChangedEventData>`  
_L701-704_
- inherits: `TStructOpsTypeTraitsBase2<FMovementModeChangedEventData>`
- desc: WithCopy = true: inherited std::function in FMoverSimulationEventData requires operator= for safe copying via FInstancedStruct.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L703-703_

#### struct `FTeleportSucceededEventData`  
`struct FTeleportSucceededEventData : public FMoverSimulationEventData`  
_L707-751_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L711 _public function_ `FTeleportSucceededEventData(const FMoverTimeStep& InEventTime, const FVector& InFromLocation, const FQuat& InFromRotation, const FVector& InToLocation, const FQuat& InToRotation) : FMoverSimulationEventData(InEventTime) , FromLocation(InFromLocation) , FromRotation(InFromRotation) , ToLocation(InToLocation) , ToRotation(InToRotation)`
- L719 _public function_ `FTeleportSucceededEventData()`
- L721 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L726 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const override`
- L741 _public member_ `FVector FromLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L744 _public member_ `FQuat FromRotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L747 _public member_ `FVector ToLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L750 _public member_ `FQuat ToRotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTeleportSucceededEventData> : public TStructOpsTypeTraitsBase2<FTeleportSucceededEventData>`  
_L755-758_
- inherits: `TStructOpsTypeTraitsBase2<FTeleportSucceededEventData>`
- desc: WithCopy = true: inherited std::function in FMoverSimulationEventData requires operator= for safe copying via FInstancedStruct.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L757-757_

#### enum `ETeleportFailureReason`  
`enum class ETeleportFailureReason : uint8`  
_L761-764_
- reflection: `UENUM(BlueprintType)`
- L763 _public enumerator_ `Reason_NotAvailable UMETA(DisplayName = "Reason Not Available", Tooltip = "A reason for the teleport failure was not indicated")`

#### struct `FTeleportFailedEventData`  
`struct FTeleportFailedEventData : public FMoverSimulationEventData`  
_L767-815_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L771 _public function_ `FTeleportFailedEventData(const FMoverTimeStep& InEventTime, const FVector& InFromLocation, const FQuat& InFromRotation, const FVector& InToLocation, const FQuat& InToRotation, ETeleportFailureReason InTeleportFailureReason) : FMoverSimulationEventData(InEventTime) , FromLocation(InFromLocation) , FromRotation(InFromRotation) , ToLocation(InToLocation) , ToRotation(InToRotation) , TeleportFailureReason(InTeleportFailureReason)`
- L780 _public function_ `FTeleportFailedEventData()`
- L782 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L787 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const override`
- L802 _public member_ `FVector FromLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L805 _public member_ `FQuat FromRotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L808 _public member_ `FVector ToLocation = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L811 _public member_ `FQuat ToRotation = FQuat::Identity;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L814 _public member_ `ETeleportFailureReason TeleportFailureReason = ETeleportFailureReason::Reason_NotAvailable;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FTeleportFailedEventData> : public TStructOpsTypeTraitsBase2<FTeleportFailedEventData>`  
_L819-822_
- inherits: `TStructOpsTypeTraitsBase2<FTeleportFailedEventData>`
- desc: WithCopy = true: inherited std::function in FMoverSimulationEventData requires operator= for safe copying via FInstancedStruct.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L821-821_

#### struct `FMoverGameplayTagChangeEventData`  
`struct FMoverGameplayTagChangeEventData : public FMoverSimulationEventData`  
_L825-865_
- reflection: `USTRUCT()`
- inherits: `FMoverSimulationEventData`
- L829 _public function_ `FMoverGameplayTagChangeEventData(const FMoverTimeStep& InEventTime, const FGameplayTag& InTag, bool bInWasAdded, FEventProcessedCallbackPtr InEventProcessedCallback = nullptr) : FMoverSimulationEventData(InEventTime, InEventProcessedCallback) , Tag(InTag) , bWasAdded(bInWasAdded)`
- L836 _public function_ `FMoverGameplayTagChangeEventData()`
- L841 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L846 _public function_ `virtual bool IsEqual(const FMoverSimulationEventData& Other, int32 ServerFrameDiffTolerance = 0) const override`
- L857 _public member_ `FGameplayTag Tag;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L860 _public member_ `bool bWasAdded = false;` — `UPROPERTY(VisibleAnywhere, Category = Mover)`
- L864 _public member_ `bool bIsExternalTag = false;` — `UPROPERTY(VisibleAnywhere, Category = Mover)` — Was this event triggered by an externally-added tag (via AddGameplayTag/RemoveGameplayTag), rather than from within the simulation?

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverGameplayTagChangeEventData> : public TStructOpsTypeTraitsBase2<FMoverGameplayTagChangeEventData>`  
_L869-872_
- inherits: `TStructOpsTypeTraitsBase2<FMoverGameplayTagChangeEventData>`
- desc: WithCopy = true: inherited std::function in FMoverSimulationEventData requires operator= for safe copying via FInstancedStruct.

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L871-871_

#### struct `UE::Mover::FSimulationOutputData`  
`struct FSimulationOutputData`  
_L876-892_
- L878 _public prototype_ `void Reset();`
- L879 _public prototype_ `void Interpolate(const FSimulationOutputData& From, const FSimulationOutputData& To, float Alpha, double SimTimeMs);`
- L880 _public function_ `bool IsValid() const`
- L885 _public member_ `FMoverSyncState SyncState;`
- L886 _public member_ `FMoverInputCmdContext LastUsedInputCmd;`
- L887 _public member_ `FMoverDataCollection AdditionalOutputData;`
- L888 _public member_ `TArray<TSharedPtr<FMoverSimulationEventData>> Events;`
- L890 _public member_ `FGameplayTagContainer InternalGameplayTags;` — Snapshot of all gameplay tags active on the simulation at the end of this tick, as collected from the simulation.
- L891 _public member_ `bool bIsValid = false;`

#### class `UE::Mover::FSimulationOutputRecord`  
`class FSimulationOutputRecord`  
_L894-938_
- L905 _public prototype_ `void Add(const FMoverTimeStep& InTimeStep, const FSimulationOutputData& InData);`
- L907 _public prototype_ `const FSimulationOutputData& GetLatest() const;`
- L910 _public prototype_ `void CreateInterpolatedResult(double AtBaseTimeMs, FMoverTimeStep& OutTimeStep, FSimulationOutputData& OutData);` — This will create an interpolated output and extract events from the stored data with time stamps up until the input time
- L912 _public prototype_ `void Clear();`
- L915 _public prototype_ `void PruneEventsFromFrame(int32 FromServerFrame);` — Remove all queued events whose ServerFrame is >= FromServerFrame. Call this on the first resim frame after a rollback to discard stale predicted events.
- L919 _public member_ `FString DebugOwnerName;` — Mover Gameplay Tag Logging
- L920 _public member_ `FString DebugOwnerRole;`
- L924 _private member_ `FData Data[2];`
- L925 _private member_ `TArray<TSharedPtr<FMoverSimulationEventData>> Events;`
- L926 _private member_ `uint8 CurrentIndex = 1;`
- L932 _private member_ `int32 NextInterpolatedGeneration = 0;` — Tracks accumulated post-event InternalGameplayTags across multiple calls to CreateInterpolatedResult for the same interpolation window. Incremented by Add() whenever new simulation data arrives; compared in CreateInterpolatedResult to detect whether the Prev..Curr window has changed since the last call.
- L933 _private member_ `int32 LastInterpolatedGeneration = INDEX_NONE;`
- L934 _private member_ `FGameplayTagContainer LastInterpolatedTags;`
- L937 _private prototype_ `void LogTagInterpolate(uint8 PrevIndex, double AtBaseTimeMs, bool bIsInterpolated) const;` — Mover Gameplay Tag Logging

#### struct `UE::Mover::FSimulationOutputRecord::FData`  
`struct FData`  
_L897-903_
- L899 _public prototype_ `void Reset();`
- L901 _public member_ `FMoverTimeStep TimeStep;`
- L902 _public member_ `FSimulationOutputData SimOutputData;`

#### struct `FModeChangeParams`  
`struct FModeChangeParams`  
_L945-954_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params used when initiating a change in movement mode
- L950 _public member_ `FName DesiredModeName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L953 _public member_ `bool bShouldReenter = false;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`

#### struct `FModeRegistrationParams`  
`struct FModeRegistrationParams`  
_L960-973_
- reflection: `USTRUCT(BlueprintType)`
- desc: Params used when initiating a change in movement mode registration
- L965 _public member_ `FName ModeName = NAME_None;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L968 _public member_ `TObjectPtr<UBaseMovementMode> ModeObject = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`
- L971 _public member_ `bool bIsTheDefaultMode = false;` — `UPROPERTY(BlueprintReadWrite, Category = Mover)`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace DefaultModeNames`
- L27 _externvar_ `extern const FName Walking;` (scope `DefaultModeNames`)
- L28 _externvar_ `extern const FName Falling;` (scope `DefaultModeNames`)
- L29 _externvar_ `extern const FName Flying;` (scope `DefaultModeNames`)
- L30 _externvar_ `extern const FName Swimming;` (scope `DefaultModeNames`)
- L34 _namespace_ `namespace CommonBlackboard`
- L36 _externvar_ `extern const FName LastFloorResult;` (scope `CommonBlackboard`)
- L37 _externvar_ `extern const FName LastWaterResult;` (scope `CommonBlackboard`)
- L39 _externvar_ `extern const FName LastFoundDynamicMovementBase;` (scope `CommonBlackboard`)
- L40 _externvar_ `extern const FName AccumulatedBasedTransformDelta;` (scope `CommonBlackboard`)
- L41 _externvar_ `extern const FName LastBasedMovementAppliedEventTime;` (scope `CommonBlackboard`)
- L43 _externvar_ `extern const FName TimeSinceSupported;` (scope `CommonBlackboard`)
- L45 _externvar_ `extern const FName LastModeChangeRecord;` (scope `CommonBlackboard`)
- L658 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon1f7c555b0103`)
- L703 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon1f7c555b0203`)
- L757 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon1f7c555b0303`)
- L821 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon1f7c555b0403`)
- L871 _enumerator_ `enum { WithCopy = true };` (scope `TStructOpsTypeTraits::__anon1f7c555b0503`)
- L874 _namespace_ `namespace UE`
- L874 _namespace_ `namespace Mover` (scope `UE`)

### `Plugins/Experimental/Mover/Source/Mover/Public/MoverTypes.h` (Public)


#### enum `EMoverTickPhase`  
`enum class EMoverTickPhase : uint8`  
_L29-41_
- reflection: `UENUM(BlueprintType)`
- desc: List of Mover tick phases where different parts of work are being performed
- L31 _public enumerator_ `Invalid = 0 UMETA(Hidden)`
- L34 _public enumerator_ `ProduceInput = 1 UMETA(DisplayName = "ProduceInput")` — This tick is where an input for the next movement step is authored
- L37 _public enumerator_ `SimulateMovement = 2 UMETA(DisplayName = "SimulateMovement")` — This tick is where movement based on {input, state} is simulated, to produce a new state
- L40 _public enumerator_ `ApplyState = 3 UMETA(DisplayName = "ApplyState")` — This tick is where the newest simulation state is applied to the actor and its components

#### enum `EMoverTickDependencyOrder`  
`enum class EMoverTickDependencyOrder : uint8`  
_L45-49_
- reflection: `UENUM(BlueprintType)`
- desc: List of tick dependency order of execution relative to the Mover tick function.
- L47 _public enumerator_ `Before = 0`
- L48 _public enumerator_ `After = 1`

#### enum `EMoverSmoothingMode`  
`enum class EMoverSmoothingMode : uint8`  
_L53-60_
- reflection: `UENUM(BlueprintType)`
- desc: Options for how to handle smoothing frame data from the backend. Typically this is for advancing the simulation at a lower or fixed rate versus the game thread/render rate.
- L56 _public enumerator_ `None` — Smoothed frames will be ignored
- L59 _public enumerator_ `VisualComponentOffset` — Use the smoothed state data to offset the visual root component only, without smoothing the root moving component or any other state data

#### struct `FMoverOnImpactParams`  
`struct FMoverOnImpactParams`  
_L65-84_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Impact Data"))`
- desc: Struct to hold params for when an impact happens. This contains all of the data for impacts including what gets passed to the FMover_OnImpact delegate
- L69 _public prototype_ `FMoverOnImpactParams();`
- L71 _public prototype_ `FMoverOnImpactParams(const FName& ModeName, const FHitResult& Hit, const FVector& Delta);`
- L75 _public member_ `FName MovementModeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Name of the movement mode this actor is currently in at the time of the impact
- L79 _public member_ `FHitResult HitResult;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — The hit result of the impact
- L83 _public member_ `FVector AttemptedMoveDelta;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — The original move that was being performed when the impact happened

#### struct `FMoverEventContext`  
`struct FMoverEventContext`  
_L88-110_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct containing additional context about an event occurrence, such as what led to it
- L92 _public prototype_ `FMoverEventContext();`
- L93 _public prototype_ `FMoverEventContext(const FMoverTimeStep& InEventTime);`
- L97 _public member_ `double EventTimeMs = -1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Simulation time that this event occurred (in server simulation timespace)
- L101 _public member_ `int32 ServerFrame = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Server frame that this event occurred
- L105 _public member_ `uint8 bIsDuringResimulation : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Did this event occur while resimulating a past sim frame?
- L109 _public member_ `uint8 bIsCausedByRollback : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Did this event occur during the instant that the simulation rolled back to an earlier state? Note this is different than during resim. See also @bIsDuringResimulation

#### struct `FMoverTime`  
`struct FMoverTime`  
_L117-145_
- reflection: `USTRUCT(BlueprintType)`
- desc: A time that can be a frame count or a floating point value. When time advances in fixed time steps a frame count will be provided to allow for exact time arithmetic A floating point time will also be provided in milliseconds When time advances in variable time steps, the frame count will be INDEX_NONE (-1) and only the floating point time will be valid
- L121 _public function_ `FString ToString() const`
- L130 _public function_ `double ElapsedSecondsTo(const FMoverTime& Other, double FixedFrameDtSeconds) const` — Returns elapsed time in seconds from this time to Other. In fixed time steps (FrameCount != INDEX_NONE), uses integer frame arithmetic for exactness. (but intra step time differences, smaller than FixedFrameDtSeconds, will have to use other functions) In variable time steps (FrameCount == INDEX_NONE), uses floating-point ms arithmetic.
- L140 _public member_ `int32 FrameCount=INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mover)` — Number of fixed time steps that have occurred since time 0. Only valid when time advances in fixed time steps.
- L144 _public member_ `double TimeMs=-1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mover)` — Time in milliseconds. In fixed time steps this should always be equal to FrameCount * Duration of a Fixed Time Step

#### struct `FMoverTimeStep`  
`struct FMoverTimeStep`  
_L149-196_
- reflection: `USTRUCT(BlueprintType)`
- L156 _public member_ `int32 ServerFrame=INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mover)` — The server simulation frame this timestep is associated with. This is the frame that's being worked on now.
- L160 _public member_ `double BaseSimTimeMs=-1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mover)` — Starting simulation time (in server simulation timespace)
- L164 _public member_ `float StepMs=1.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mover)` — The delta time step for this tick
- L168 _public member_ `uint8 bIsResimulating : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mover)` — Indicates whether this time step is re-simulating based on prior inputs, such as during a correction
- L172 _public member_ `uint8 bIsFirstResimFrame : 1 = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mover)` — If resimulating, is this the first frame after the rollback?
- L177 _public function_ `FMoverTime ToStartTime() const` — Returns an FMoverTime representing the start of this time step. Both FrameCount and TimeMs are always populated; ElapsedSecondsTo uses whichever is appropriate based on the reference FMoverTime's FrameCount (INDEX_NONE = variable dt, otherwise fixed dt).
- L189 _public function_ `FMoverTime ToNextTime() const` — Returns an FMoverTime representing the start of the next step. With regard to time difference calculation, it also represents the time at the end of the current step, but with a frame count incremented by one. Otherwise the distance between ToStartTime and ToNextTime in async mode would be 0, since it base time arithmetic on frame counts.

#### struct `FMoverDataStructBase`  
`struct FMoverDataStructBase`  
_L203-259_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base type for all data structs used to compose Mover simulation model definition dynamically (input cmd, sync state, aux state) NOTE: for simulation state data (sync/aux), derive from FMoverStateData instead
- L207 _public prototype_ `FMoverDataStructBase();`
- L208 _public prototype_ `virtual ~FMoverDataStructBase() = default;`
- L211 _public prototype_ `virtual FMoverDataStructBase* Clone() const;` — return newly allocated copy of this FMoverDataStructBase. MUST be overridden by derived types.
- L213 _public function_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)`
- L220 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const;` — Gets the type info of this FMoverDataStructBase. MUST be overridden by derived types.
- L223 _public function_ `virtual void ToString(FAnsiStringBuilderBase& Out) const` — Get string representation of this struct instance
- L226 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector)` — If derived classes hold any object references, override this function and add them to the collector.
- L233 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const;` — Checks if the contained data is equal, within reason. AuthorityState is guaranteed to be the same concrete type as 'this'. Override for: All types that compose STATE data (sync or aux) and types that compose INPUT data for physics-based movement
- L240 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float Pct);` — Interpolates contained data between a starting and ending block. From and To are guaranteed to be the same concrete type as 'this'. Override for: All types that compose STATE data (sync or aux) and types that compose INPUT data for physics-based movement
- L247 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From);` — Merges contained data from a previous frame with that of the current frame. For more information, see the comments on FNetworkPhysicsData::MergeData. From is guaranteed to be the same concrete type as 'this'. Override for: Types that compose INPUT data for physics-based movement
- L254 _public function_ `virtual void Decay(float DecayAmount)` — Decays contained data during resimulation if data is forward predicted. For more information, see the comments on FNetworkPhysicsData::DecayData. @param DecayAmount = Total amount of decay as a multiplier. 10% decay = 0.1. Override for: Types that compose INPUT data for physics-based movement
- L258 _public prototype_ `virtual const UScriptStruct* GetDataScriptStruct() const;` — Used to differentiate between this type, and a proxy data type. RARELY overridden by derived types.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FMoverDataStructBase > : public TStructOpsTypeTraitsBase2< FMoverDataStructBase >`  
_L262-269_
- inherits: `TStructOpsTypeTraitsBase2<FMoverDataStructBase>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L265-268_

#### struct `FMoverDataCollection`  
`struct FMoverDataCollection`  
_L278-425_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains a group of different FMoverDataStructBase-derived data, and supports net serialization of them. Note that each contained data must have a unique type.  This is to support dynamic composition of Mover simulation model definitions (input cmd, sync state, aux state).
- L282 _public prototype_ `FMoverDataCollection();`
- L284 _public function_ `void Empty()`
- L287 _public prototype_ `bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess);` — Serialize all data in this collection
- L292 _public prototype_ `bool SerializeDebugData(FArchive& Ar);` — Serializes data in this collection for debug purposes. This is currently only usable in the context of sending mover info to the Chaos Visual Debugger
- L295 _public prototype_ `FMoverDataCollection& operator=(const FMoverDataCollection& Other);` — Copy operator - deep copy so it can be used for archiving/saving off data
- L298 _public prototype_ `bool operator==(const FMoverDataCollection& Other) const;` — Comparison operator (deep) - needs matching struct types along with identical states in those structs. See also ShouldReconcile
- L301 _public prototype_ `bool operator!=(const FMoverDataCollection& Other) const;` — Comparison operator
- L304 _public prototype_ `bool ShouldReconcile(const FMoverDataCollection& Other) const;` — Checks if the collections are significantly different enough (piece-wise) to need reconciliation. NOT an equality check.
- L307 _public prototype_ `void Interpolate(const FMoverDataCollection& From, const FMoverDataCollection& To, float Pct);` — Make this collection a piece-wise interpolation between 2 collections
- L310 _public prototype_ `void Merge(const FMoverDataCollection& From);` — Merge a previous frame's collection with this collection
- L313 _public prototype_ `void Decay(float DecayAmount);` — Decay input based on DecayAmount for resimulation and forward prediction
- L316 _public prototype_ `bool HasSameContents(const FMoverDataCollection& Other) const;` — Checks only whether there are matching structs inside, but NOT necessarily identical states of each one
- L319 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector) const;` — Exposes references to GC system
- L322 _public prototype_ `void ToString(FAnsiStringBuilderBase& Out) const;` — Get string representation of all elements in this collection
- L325 _public prototype_ `TArray<TSharedPtr<FMoverDataStructBase>>::TConstIterator GetCollectionDataIterator() const;` — Const access to data array of collections
- L329 _public function_ `template <typename T> T* FindMutableDataByType() const` — Find data of a specific type in the collection (mutable version). If not found, null will be returned.
- L341 _public function_ `template <typename T> const T* FindDataByType() const` — Find data of a specific type in the collection. If not found, null will be returned.
- L353 _public function_ `template <typename T> const T& FindOrAddDataByType()` — Find data of a specific type in the collection. If not found, a new default instance will be added.
- L365 _public function_ `template <typename T> T& FindOrAddMutableDataByType()` — Find data of a specific type in the collection (mutable version). If not found, a new default instance will be added.
- L377 _public function_ `template <typename T> T& FindOrAddMutableDataByType(bool& bOutAdded)` — Find data of a specific type in the collection (mutable version). If not found, a new default instance will be added. Outputs if the state was added or not.
- L390 _public prototype_ `void AddOrOverwriteData(const TSharedPtr<FMoverDataStructBase> DataInstance);` — Adds this data instance to the collection, taking ownership of it. If an existing data struct of the same type is already there, it will be removed first.
- L395 _public prototype_ `void AddDataByCopy(const FMoverDataStructBase* DataInstanceToCopy);` — Adds data to the collection by copying over an existing struct or cloning the provided struct if no matching struct exists. This is different than AddOrOverwriteData because the instance isn't touched, avoiding memory allocation & array changing if a matching struct exists.
- L398 _public function_ `const TArray< TSharedPtr<FMoverDataStructBase> >& GetDataArray() const`
- L404 _public prototype_ `FMoverDataStructBase* FindDataByType(const UScriptStruct* DataStructType) const;` — Find data of a specific type in the collection.
- L407 _public prototype_ `FMoverDataStructBase* FindOrAddDataByType(const UScriptStruct* DataStructType);` — Find data of a specific type in the collection. If not found, a new default instance will be added.
- L410 _public prototype_ `bool RemoveDataByType(const UScriptStruct* DataStructType);` — Removes data of a specific type in the collection. Returns true if data was removed.
- L413 _protected prototype_ `FMoverDataStructBase* AddDataByType(const UScriptStruct* DataStructType);`
- L414 _protected prototype_ `static TSharedPtr<FMoverDataStructBase> CreateDataByType(const UScriptStruct* DataStructType);`
- L417 _protected prototype_ `static void NetSerializeDataArray(FArchive& Ar, UPackageMap* Map, TArray<TSharedPtr<FMoverDataStructBase>>& DataArray);` — Helper function for serializing array of data
- L420 _protected member_ `TArray< TSharedPtr<FMoverDataStructBase> > DataArray;` — All data in this collection

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMoverDataCollection> : public TStructOpsTypeTraitsBase2<FMoverDataCollection>`  
_L429-438_
- inherits: `TStructOpsTypeTraitsBase2<FMoverDataCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L432-437_

#### struct `FMoverDataPersistence`  
`struct FMoverDataPersistence`  
_L442-461_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Persistent Data Settings"))`
- desc: Info about data collection types that should always be present, and how they should propagate from one frame to the next
- L446 _public function_ `FMoverDataPersistence()`
- L448 _public function_ `FMoverDataPersistence(UScriptStruct* TypeToPersist, bool bShouldCopyBetweenFrames)`
- L456 _public member_ `TObjectPtr<UScriptStruct> RequiredType = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(MetaStruct="/Script/Mover.MoverDataStructBase"))` — The type that should propagate between frames
- L460 _public member_ `bool bCopyFromPriorFrame = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — If true, values will be copied from the prior frame. Otherwise, they will be default-initialized.

#### struct `FMovementModeChangeRecord`  
`struct FMovementModeChangeRecord`  
_L464-470_
- desc: Information about a change in movement mode
- L466 _public member_ `FName ModeName;`
- L467 _public member_ `FName PrevModeName;`
- L468 _public member_ `uint32 Frame;`
- L469 _public member_ `double SimTimeMs;`

#### class `UMoverDataCollectionLibrary`  
`class UMoverDataCollectionLibrary : public UBlueprintFunctionLibrary`  
_L476-505_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint helper functions for working with a Mover data collection
- L486 _public prototype_ `static void K2_AddDataToCollection(UPARAM(Ref) FMoverDataCollection& Collection, UPARAM(DisplayName="Struct To Add") const int32& Sourc` — `UFUNCTION(BlueprintCallable, CustomThunk, Category = "Mover|Data", meta = (CustomStructureParam = "SourceAsRawBytes", AllowAbstract = "false", DisplayName = "Add Data To Collection"))` — Add a data struct to the collection, overwriting an existing one with the same type @param SourceAsRawBytes		The data struct instance to add by copy, which must be a FMoverDataStructBase sub-type
- L500 _public prototype_ `static void ClearDataFromCollection(UPARAM(Ref) FMoverDataCollection& Collection);` — `UFUNCTION(BlueprintCallable, Category = "Mover|Data", meta=(DisplayName = "Clear Data From Collection"))` — Clears all data from a collection

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`
- L15 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsOnGround);` — Gameplay tags
- L16 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsInAir);`
- L17 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsFalling);`
- L18 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsFlying);`
- L19 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsSwimming);`
- L20 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsCrouching);`
- L21 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_IsNavWalking);`
- L22 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_AnimRootMotion);`
- L23 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_SkipAnimRootMotion);`
- L24 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_SkipVerticalAnimRootMotion);`
- L25 _prototype_ `UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mover_DisableLanding);`
- L266 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anone487d5f60103`)
- L267 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone487d5f60103`)
- L433 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anone487d5f60203`) — Necessary so that DataArray is copied around
- L434 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anone487d5f60203`)
- L435 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anone487d5f60203`)
- L436 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anone487d5f60203`)

### `Plugins/Experimental/Mover/Source/Mover/Public/UserDefinedStructSupport.h` (Public)


#### struct `FMoverUserDefinedDataStruct`  
`struct FMoverUserDefinedDataStruct : public FMoverDataStructBase`  
_L24-46_
- reflection: `USTRUCT()`
- inherits: `FMoverDataStructBase`
- desc: Wrapper class that's used to add User-Defined Struct instances to Mover Data Collections (input or state). This allows devs to add custom data to inputs and/or state without requiring native code. Note that these are typically less efficient than natively-defined structs, and the logic of operations like interpolation, merging, and serialization may be simplistic for a project's needs. At present: - any differences between any struct contents will trigger reconciliation, even small floating point number differences - only boolean values can be merged - interpolation will take the entire struct instance from the highest weight frame
- L30 _public member_ `FInstancedStruct StructInstance;` — `UPROPERTY()` — this always represents a User-Defined Struct from Blueprint
- L33 _public prototype_ `virtual bool ShouldReconcile(const FMoverDataStructBase& AuthorityState) const override;` — Implementation of FMoverDataStructBase
- L34 _public prototype_ `virtual void Interpolate(const FMoverDataStructBase& From, const FMoverDataStructBase& To, float LerpFactor) override;`
- L35 _public prototype_ `virtual void Merge(const FMoverDataStructBase& From) override;`
- L36 _public prototype_ `virtual FMoverDataStructBase* Clone() const override;`
- L37 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;`
- L38 _public prototype_ `virtual void ToString(FAnsiStringBuilderBase& Out) const override;`
- L41 _public function_ `virtual UScriptStruct* GetScriptStruct() const override` — Note: this is the FMoverUserDefinedDataStruct type, NOT the User-Defined Struct type
- L43 _public prototype_ `virtual const UScriptStruct* GetDataScriptStruct() const override;` — This returns the User-Defined Struct type
- L45 _public prototype_ `static bool NetSerializeUserDefinedStruct(FInstancedStruct& UDSStructInstance, FArchive& Ar, UPackageMap* Map);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVER_API`
