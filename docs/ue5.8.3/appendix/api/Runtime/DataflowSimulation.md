# Runtime / DataflowSimulation

- module root: `Source/Runtime/Dataflow/Simulation`
- headers: 14; symbols: 251
- symbol kinds: class=17, function=62, macro=8, member=40, namespace=9, prototype=91, struct=22, typedef=2
- PrivateDependencyModuleNames: Chaos, DataflowCore, DataflowEngine, Engine, RHI, RenderCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DataflowCore, DataflowEngine, RigidPhysics

### `Source/Runtime/Dataflow/Simulation/Private/Dataflow/DataflowSimulationPlugin.h` (Private)


#### class `IDataflowSimulationPlugin`  
`class IDataflowSimulationPlugin : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L14 _public prototype_ `virtual void StartupModule();`
- L15 _public prototype_ `virtual void ShutdownModule();`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationContext.h` (Public)


#### class `UE::Dataflow::TSimulationContext`  
`template<typename Base = UE::Dataflow::FContextSingle> class TSimulationContext : public UE::Dataflow::TEngineContext<Base>`  
_L18-119_
- inherits: `UE::Dataflow::TEngineContext<Base>`
- desc: Simulation context that will be used by all the simulation nodes
- L21 _public prototype_ `DATAFLOW_CONTEXT_INTERNAL(UE::Dataflow::TEngineContext<Base>, TSimulationContext);`
- L23 _public function_ `explicit TSimulationContext(const TObjectPtr<UObject>& InOwner) : Super(InOwner)`
- L27 _public prototype_ `virtual ~TSimulationContext() override = default;`
- L30 _public function_ `void SetTimingInfos(const float DeltaSeconds, const float TimeSeconds)` — Set the timing infos
- L33 _public function_ `float GetDeltaTime() const` — Get the delta time in seconds
- L36 _public function_ `float GetSimulationTime() const` — Get the simulation time in seconds
- L40 _public prototype_ `template<typename ProxyType> void GetTypedProxies(TArray<ProxyType*>& FilteredProxies) const;` — Get the typed proxies
- L43 _public prototype_ `void GetSimulationProxies(const FString& ProxyType, const TArray<FString>& SimulationGroups, TArray<FDataflowSimulationProxy*>& FilteredProxies) const;` — Filter the physics solvers matching the groups
- L46 _public prototype_ `void AddSimulationProxy(const FString& ProxyType, FDataflowSimulationProxy* SimulationProxy);` — Add simulation proxy to the context
- L49 _public prototype_ `void RemoveSimulationProxy(const FString& ProxyType, const FDataflowSimulationProxy* SimulationProxy);` — Remove simulation proxy from the context
- L52 _public prototype_ `void ResetSimulationProxies();` — Reset all the simulation proxies
- L55 _public prototype_ `int32 NumSimulationProxies(const FString& ProxyType) const;` — Return the number of physics solvers
- L58 _public prototype_ `void RegisterProxyGroups();` — Register all the proxy groups used in the proxy
- L61 _public prototype_ `void BuildGroupBits(const TArray<FString>& SimulationGroups, TBitArray<>& GroupBits) const;` — Build group bits based on the string array
- L65 _public prototype_ `UE_INTERNAL FRigidPhysicsSceneDataflowState* GetRigidState();` — Return state associated with the rigids dataflow simulation
- L68 _public prototype_ `UE_INTERNAL void SetRigidSceneName(const FString& InSceneName);` — Set the name of scene created through the rigids dataflow
- L71 _public prototype_ `UE_INTERNAL const FString& GetRigidSceneName();` — Get the name of scene created through the rigids dataflow
- L75 _public function_ `void PushIterationIndex()` — Push another level of iteration indices
- L81 _public function_ `void PopIterationIndex()` — Pop the last level of iteration indices
- L87 _public function_ `void SetIterationIndex(const int32 IterationIndex)` — Set the last iteration index
- L93 _public function_ `int32 GetIterationIndex()` — Get the last iteration index
- L101 _private member_ `float SimulationTime = 0.0f;` — Simulation time
- L104 _private member_ `float DeltaTime = 0.0f;` — Delta time
- L107 _private member_ `TMap<FString, TSet<FDataflowSimulationProxy*>> SimulationProxies;` — List of all the simulation proxies within the context sorted by type
- L110 _private member_ `TMap<FString, uint32> GroupIndices;` — List of all the simulation groups indices
- L113 _private member_ `TArray<int32> IterationIndices;` — List of all the nested iteration indices
- L116 _private member_ `UE_INTERNAL TPimplPtr<FRigidPhysicsSceneDataflowState> RigidState;`
- L117 _private member_ `UE_INTERNAL FString SceneName = "";`
- L123 _function_ `template<typename Base> template<typename ProxyType> void TSimulationContext<Base>::GetTypedProxies(TArray<ProxyType*>& FilteredProxies) const`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Dataflow` (scope `UE`)
- L137 _typedef_ `using FDataflowSimulationContext = TSimulationContext<UE::Dataflow::FContextSingle>;` (scope `UE::Dataflow`)
- L138 _typedef_ `using FDataflowSimulationContextThreaded = TSimulationContext<UE::Dataflow::FContextThreaded>;` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationInterface.h` (Public)


#### struct `FDataflowSimulationAsset`  
`struct FDataflowSimulationAsset`  
_L19-30_
- reflection: `USTRUCT(BlueprintType)`
- desc: Dataflow simulation asset (should be in the interface children)
- L25 _public member_ `TObjectPtr<UDataflow> DataflowAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")` — Simulation dataflow asset used to advance in time on Pt
- L29 _public member_ `TSet<FString> SimulationGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")` — Simulation groups used to filter within the simulation nodes

#### class `UDataflowSimulationInterface`  
`class UDataflowSimulationInterface : public UInterface`  
_L33-36_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowSimulationInterface`  
`class IDataflowSimulationInterface`  
_L41-95_
- desc: Dataflow simulation interface to send/receive datas (GT <-> PT)
- L46 _public function_ `IDataflowSimulationInterface()`
- L49 _public prototype_ `virtual FDataflowSimulationAsset& GetSimulationAsset() = 0;` — Get the dataflow simulation asset
- L52 _public prototype_ `virtual const FDataflowSimulationAsset& GetSimulationAsset() const = 0;` — Get the const dataflow simulation asset
- L55 _public prototype_ `virtual void BuildSimulationProxy() = 0;` — Build the simulation proxy
- L58 _public prototype_ `virtual void ResetSimulationProxy() = 0;` — Reset the simulation proxy
- L61 _public prototype_ `virtual const FDataflowSimulationProxy* GetSimulationProxy() const = 0;` — Get the const simulation proxy
- L64 _public prototype_ `virtual FDataflowSimulationProxy* GetSimulationProxy() = 0;` — Get the simulation proxy
- L67 _public prototype_ `virtual FString GetSimulationName() const = 0;` — Get the simulation name
- L70 _public function_ `virtual void PreProcessSimulation(const float DeltaTime)` — Preprocess data before simulation
- L73 _public function_ `virtual void WriteToSimulation(const float DeltaTime, const bool bAsyncTask)` — Write data to be sent to the simulation proxy
- L76 _public function_ `virtual void ReadFromSimulation(const float DeltaTime, const bool bAsyncTask)` — Read data received from the simulation proxy
- L79 _public function_ `virtual void ReadRestartData()` — Read restart data (positions) from simulation proxy
- L82 _public function_ `virtual void PostProcessSimulation(const float DeltaTime)` — Postprocess data after simulation
- L85 _public function_ `virtual FString GetSimulationType() const` — Get the simulation type
- L88 _public prototype_ `void RegisterManagerInterface(const TObjectPtr<UWorld>& SimulationWorld);` — Register simulation interface solver to manager
- L91 _public prototype_ `void UnregisterManagerInterface(const TObjectPtr<UWorld>& SimulationWorld) const;` — Unregister simulation interface from the manager
- L94 _public prototype_ `bool IsInterfaceRegistered(const TObjectPtr<UWorld>& SimulationWorld) const;` — Check if the interface has been registered to the manager

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationManager.h` (Public)


#### struct `UE::Dataflow::Private::FDataflowSimulationData`  
`struct FDataflowSimulationData`  
_L24-44_
- desc: Per dataflow graph simulation data type (data interfaces + simulation context)
- L27 _public member_ `TMap<FString, TSet<IDataflowSimulationInterface*>> SimulationInterfaces;` — List of all simulation interfaces used in this this dataflow graph
- L30 _public member_ `TSharedPtr<UE::Dataflow::FDataflowSimulationContext> SimulationContext;` — Simulation context used to evaluate the graph on PT
- L33 _public function_ `bool IsEmpty() const` — Check is there is any datas to process

#### class `UDataflowSimulationManager`  
`class UDataflowSimulationManager : public UTickableWorldSubsystem`  
_L51-157_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L56 _public prototype_ `UDataflowSimulationManager();`
- L57 _public prototype_ `virtual ~UDataflowSimulationManager() override = default;`
- L60 _public prototype_ `static void OnStartup();` — Static function to add world delegates
- L63 _public prototype_ `static void OnShutdown();` — Static function to remove world delegates
- L66 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L67 _public function_ `virtual bool IsTickableInEditor() const override`
- L68 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L69 _public prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;`
- L70 _public prototype_ `virtual TStatId GetStatId() const override;`
- L74 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L75 _public prototype_ `virtual void Deinitialize() override;`
- L79 _public prototype_ `void AdvanceSimulationProxies(const float DeltaTime, const float SimulationTime);` — Advance in time the registered simulation data (PT)
- L82 _public prototype_ `bool HasSimulationInterface(const IDataflowSimulationInterface* SimulationInterface) const;` — Check if the manager has a simulation interface
- L85 _public prototype_ `void AddSimulationInterface(IDataflowSimulationInterface* SimulationInterface);` — Add a dataflow simulation interface to the manager
- L88 _public prototype_ `void RemoveSimulationInterface(const IDataflowSimulationInterface* SimulationInterface);` — Remove a dataflow simulation interface from the manager
- L91 _public prototype_ `void ReadSimulationInterfaces(const float DeltaTime, const bool bAsyncTask);` — Read the simulation interfaces and Write all the data to the simulation proxies (to be send from GT->PT)
- L94 _public prototype_ `void WriteSimulationInterfaces(const float DeltaTime, const bool bAsyncTask);` — Read all the data from the simulation proxies and write the result onto the interfaces (received from PT->GT)
- L97 _public prototype_ `void ReadRestartData();` — Read the restart data and Write it to the simulation proxies (to be send from GT->PT)
- L100 _public prototype_ `void InitSimulationInterfaces();` — Init all the simulation interfaces
- L103 _public prototype_ `void ResetSimulationInterfaces();` — Reset all the simulation interfaces
- L106 _public prototype_ `void CompleteSimulationTasks();` — Complete all the simulation tasks
- L109 _public prototype_ `void StartSimulationTasks(const float DeltaTime, const float SimulationTime);` — Start the simulation tasks given a delta time
- L112 _public function_ `bool GetSimulationEnabled() const` — Gets whether the simulation is enabled or disabled
- L115 _public prototype_ `void SetSimulationEnabled(const bool bSimulationEnabled);` — Set the simulation flag to enable/disable the simulation
- L118 _public prototype_ `void NotifyActorOfCurrentSimulationEnabled(class AActor* PreviewActor) const;` — Forward the current simulation enabled state to a freshly spawned preview actor
- L121 _public function_ `void SetSimulationStepping(const bool bSimulationStepping)` — Set the simulation scene stepping bool
- L124 _public prototype_ `TSharedPtr<UE::Dataflow::FDataflowSimulationContext> GetSimulationContext(const TObjectPtr<UDataflow>& DataflowAsset) const;` — Get the simulation context for a given asset
- L129 _private prototype_ `void PreProcessSimulation(const float DeltaTime);` — Pre process before the simulation step
- L132 _private prototype_ `void PostProcessSimulation(const float DeltaTime);` — Post process after the simulation step
- L135 _private member_ `static FDelegateHandle OnObjectPropertyChangedHandle;` — static delegate for object property changed
- L138 _private member_ `static FDelegateHandle OnWorldPostActorTick;` — static delegate for post actor tick
- L141 _private member_ `static FDelegateHandle OnCreatePhysicsStateHandle;` — static delegate for physics state creation
- L144 _private member_ `static FDelegateHandle OnDestroyPhysicsStateHandle;` — static delegate for physics state destruction
- L147 _private member_ `TMap<TObjectPtr<UDataflow>, UE::Dataflow::Private::FDataflowSimulationData> SimulationData;` — Dataflow simulation data registered to the manager
- L150 _private member_ `TArray<FGraphEventRef> SimulationTasks;` — Simulation tasks in which the graph will be evaluated
- L153 _private member_ `bool bIsSimulationEnabled = true;` — Boolean to control if the simulation should be disabled or not
- L156 _private member_ `bool bStepSimulationScene = false;` — Boolean to check if we are stepping the simulation scene

#### class `UDataflowSimulationActor`  
`class UDataflowSimulationActor : public UInterface`  
_L161-164_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`
- desc: Dataflow simulation actor interface to be able to call BP events before/after the manager ticking in case we need it

#### class `IDataflowSimulationActor`  
`class IDataflowSimulationActor`  
_L166-182_
- L173 _public prototype_ `void PreDataflowSimulationTick(const float SimulationTime, const float DeltaTime);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Dataflow")` — Pre simulation callback function that can be implemented in C++ or Blueprint.
- L177 _public prototype_ `void PostDataflowSimulationTick(const float SimulationTime, const float DeltaTime);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Dataflow")` — Post simulation callback function that can be implemented in C++ or Blueprint.
- L181 _public prototype_ `void OnDataflowSimulationEnabledChanged(const bool bSimulationEnabled);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Dataflow")` — Called on the preview actor when the Dataflow Editor's simulation enabled state changes.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWSIMULATION_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L46 _prototype_ `void RegisterSimulationInterface(const TObjectPtr<UObject>& SimulationObject);` (scope `UE::Dataflow`)
- L47 _prototype_ `void UnregisterSimulationInterface(const TObjectPtr<UObject>& SimulationObject);` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationNodes.h` (Public)


#### struct `FDataflowSimulationProperty`  
`struct FDataflowSimulationProperty`  
_L18-24_
- reflection: `USTRUCT(BlueprintType)`
- desc: Dataflow simulation property
- L23 _public member_ `FDataflowSimulationProxy* SimulationProxy;` — Simulation proxy used to pass information in between nodes

#### struct `FDataflowSimulationNode`  
`struct FDataflowSimulationNode : public FDataflowNode`  
_L33-70_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: FDataflowSimulationNode Base class for simulation nodes within the Dataflow graph. Simulation nodes are used to simulate data from the calling client.
- L37 _public function_ `FDataflowSimulationNode() : Super()`
- L40 _public function_ `FDataflowSimulationNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid()) : Super(Param,InGuid)`
- L45 _public prototype_ `virtual ~FDataflowSimulationNode() = default;` — FDataflowNode interface
- L47 _public function_ `static FName StaticType()`
- L49 _public function_ `virtual bool IsA(FName InType) const override`
- L56 _public function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Output) const override` — Evaluate simulation dispatch
- L69 _protected function_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const` — Evaluate simulation node given a simulation context

#### struct `FDataflowInvalidNode`  
`struct FDataflowInvalidNode : public FDataflowSimulationNode`  
_L79-100_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationNode`
- desc: FDataflowInvalidNode Base class for invalid nodes within the Dataflow graph. Invalid nodes will be always invalidated while simulating
- L83 _public function_ `FDataflowInvalidNode() : Super()`
- L86 _public function_ `FDataflowInvalidNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid()) : Super(Param,InGuid)`
- L91 _public prototype_ `virtual ~FDataflowInvalidNode() = default;` — FDataflowNode interface
- L93 _public function_ `static FName StaticType()`
- L95 _public function_ `virtual bool IsA(FName InType) const override`

#### struct `FDataflowExecutionNode`  
`struct FDataflowExecutionNode : public FDataflowSimulationNode`  
_L109-135_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationNode`
- desc: FDataflowExecutionNode Base class for the execute the dataflow simulation graph. Execution nodes are used to pull the graph from the calling client.
- L113 _public function_ `FDataflowExecutionNode() : Super()`
- L116 _public function_ `FDataflowExecutionNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid()) : Super(Param,InGuid)`
- L121 _public prototype_ `virtual ~FDataflowExecutionNode() = default;` — FDataflowNode interface
- L123 _public function_ `static FName StaticType()`
- L125 _public function_ `virtual bool IsA(FName InType) const override`
- L131 _public function_ `virtual bool IsTerminal() const override`

#### struct `FDataflowSimulationTime`  
`struct FDataflowSimulationTime`  
_L139-161_
- reflection: `USTRUCT()`
- desc: Get the dataflow simulation time
- L144 _public function_ `FDataflowSimulationTime(): DeltaTime(0.0f), CurrentTime(0.0f)`
- L147 _public function_ `FDataflowSimulationTime(const float InDeltaTime, const float InCurrentTime) : DeltaTime(InDeltaTime), CurrentTime(InCurrentTime)`
- L152 _public member_ `float DeltaTime = 0.0f;` — `UPROPERTY(Transient, SkipSerialization)` — Delta time in seconds coming from the context
- L156 _public member_ `float CurrentTime = 0.0f;` — `UPROPERTY(Transient, SkipSerialization)` — Current time in seconds coming from the context
- L160 _public member_ `float TimeOffset = 0.0f;` — `UPROPERTY(Transient, SkipSerialization)` — Time offset that will need to be added to the current time to compute the sub-stepping

#### struct `FGetSimulationTimeDataflowNode`  
`struct FGetSimulationTimeDataflowNode : public FDataflowInvalidNode`  
_L165-184_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowInvalidNode`
- desc: Get the context simulation time
- L172 _public function_ `FGetSimulationTimeDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowInvalidNode(InParam, InGuid)`
- L180 _public member_ `FDataflowSimulationTime SimulationTime = FDataflowSimulationTime(0.0f, 0.0f);` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowOutput))` — Simulation time property coming from the context
- L183 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FGetPhysicsSolversDataflowNode`  
`struct FGetPhysicsSolversDataflowNode : public FDataflowInvalidNode`  
_L188-211_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowInvalidNode`
- desc: Get physics solvers from context
- L195 _public function_ `FGetPhysicsSolversDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowInvalidNode(InParam, InGuid)`
- L203 _public member_ `TArray<FDataflowSimulationProperty> PhysicsSolvers;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowOutput))` — Physics solvers coming from the context and filtered with the groups
- L207 _public member_ `TArray<FString> SimulationGroups;` — `UPROPERTY(EditAnywhere, Category="Simulation")` — Simulation groups to filter the output solvers properties
- L210 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FAdvancePhysicsSolversDataflowNode`  
`struct FAdvancePhysicsSolversDataflowNode : public FDataflowSimulationNode`  
_L215-240_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Advance the simulation physics solver in time
- L222 _public function_ `FAdvancePhysicsSolversDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowSimulationNode(InParam, InGuid)`
- L232 _public member_ `FDataflowSimulationTime SimulationTime = FDataflowSimulationTime(0.0f,0.0f);` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))` — Delta time to use to advance the solver
- L236 _public member_ `TArray<FDataflowSimulationProperty> PhysicsSolvers;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "PhysicsSolvers"))` — Physics solvers to advance in time
- L239 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FFilterSimulationProxiesDataflowNode`  
`struct FFilterSimulationProxiesDataflowNode : public FDataflowSimulationNode`  
_L244-272_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Filter simulation proxies from context
- L251 _public function_ `FFilterSimulationProxiesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowSimulationNode(InParam, InGuid)`
- L260 _public member_ `TArray<FDataflowSimulationProperty> SimulationProxies;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))` — Simulation proxies coming from the context and filtered with the groups
- L264 _public member_ `TArray<FDataflowSimulationProperty> FilteredProxies;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowOutput))` — Simulation proxies coming from the context and filtered with the groups
- L268 _public member_ `TArray<FString> SimulationGroups;` — `UPROPERTY(EditAnywhere, Category="Simulation")` — Simulation groups to filter the output solvers properties
- L271 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FSimulationProxiesTerminalDataflowNode`  
`struct FSimulationProxiesTerminalDataflowNode : public FDataflowExecutionNode`  
_L276-295_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowExecutionNode`
- desc: Main terminal node for simulation proxies
- L283 _public function_ `FSimulationProxiesTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowExecutionNode(InParam, InGuid)`
- L291 _public member_ `TArray<FDataflowSimulationProperty> SimulationProxies;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))` — Physics solvers to evaluate
- L294 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FAdvanceRigidPhysicsSolverDataflowNode`  
`struct FAdvanceRigidPhysicsSolverDataflowNode : public FDataflowSimulationNode`  
_L299-323_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Advance the rigid solver in time
- L306 _public function_ `FAdvanceRigidPhysicsSolverDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowSimulationNode(InParam, InGuid)`
- L316 _public member_ `FDataflowSimulationTime SimulationTime = FDataflowSimulationTime(0.0f,0.0f);` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))` — Delta time to use to advance the solver
- L319 _public member_ `FRigidPhysicsSceneDataflowState State;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "State"))`
- L322 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FSceneSimulationTerminalDataflowNode`  
`struct FSceneSimulationTerminalDataflowNode : public FDataflowSimulationNode`  
_L327-343_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Main terminal node for simulation
- L333 _public function_ `FSceneSimulationTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowSimulationNode(InParam, InGuid)`
- L339 _public member_ `FRigidPhysicsSceneDataflowState State;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))`
- L342 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### struct `FRigidSceneSetupTerminalDataflowNode`  
`struct FRigidSceneSetupTerminalDataflowNode : public FDataflowSimulationNode`  
_L347-363_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowSimulationNode`
- desc: Main terminal node for scene setup
- L353 _public function_ `FRigidSceneSetupTerminalDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid()) : FDataflowSimulationNode(InParam, InGuid)`
- L359 _public member_ `FRigidPhysicsSceneDataflowState State;` — `UPROPERTY(Transient, SkipSerialization, Meta = (DataflowInput))`
- L362 _public prototype_ `virtual void EvaluateSimulation(UE::Dataflow::FDataflowSimulationContext& SimulationContext, const FDataflowOutput* Output) const override;` — Evaluate simulation node given a simulation context

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATAFLOWSIMULATION_API`
- L365 _namespace_ `namespace UE`
- L365 _namespace_ `namespace Dataflow` (scope `UE`)
- L367 _prototype_ `void RegisterDataflowSimulationNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationProxy.h` (Public)


#### struct `FDataflowSimulationProxy`  
`struct FDataflowSimulationProxy`  
_L14-72_
- reflection: `USTRUCT()`
- desc: Dataflow simulation proxy used for simulation (PT)
- L18 _public prototype_ `FDataflowSimulationProxy() = default;`
- L19 _public prototype_ `virtual ~FDataflowSimulationProxy() = default;`
- L22 _public function_ `virtual bool IsValid() const` — Check if the proxy is valid
- L25 _public function_ `virtual const UScriptStruct* GetScriptStruct() const` — Get the proxy script struct
- L32 _public function_ `template<class T> const T* AsType() const` — Cast the proxy to child
- L44 _public function_ `template<class T> T* AsType()` — Cast the const proxy to child
- L55 _public function_ `const TSet<FString>& GetSimulationGroups() const` — Get the simulation groups from the proxy
- L58 _public prototype_ `void SetSimulationGroups(const TSet<FString>& InSimulationGroups);` — Set the simulation groups onto the proxy
- L61 _public prototype_ `bool HasSimulationGroup(const FString& SimulationGroup) const;` — Check if the given group is within the proxy simulation groups
- L64 _public prototype_ `bool HasGroupBit(const TBitArray<>& SimulationBits) const;` — Check if the proxy has at least one valid bit
- L67 _public member_ `TBitArray<> GroupBits;` — Bit array matching the simulation groups for fast access
- L71 _private member_ `TSet<FString> SimulationGroups;` — List of simulation groups this proxy belongs to

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/DataflowSimulationUtils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _prototype_ `void EvaluateSimulationGraph(const TObjectPtr<UDataflow>& SimulationGraph, const TSharedPtr<UE::Dataflow::FDataflowSimulationContext>& SimulationContext, const float DeltaTime, const float SimulationTime);` (scope `UE::Dataflow`) — Evaluate the simulation graph given a simulation context and a simulation flag

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/Interfaces/DataflowCollisionObject.h` (Public)


#### struct `FDataflowCollisionObjectProxy`  
`struct FDataflowCollisionObjectProxy : public FDataflowSimulationProxy`  
_L14-26_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationProxy`
- desc: Dataflow collision object proxy (PT)
- L18 _public prototype_ `FDataflowCollisionObjectProxy();`
- L19 _public prototype_ `virtual ~FDataflowCollisionObjectProxy() override = default;`
- L22 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override` — Get the proxy script struct

#### class `UDataflowCollisionObjectInterface`  
`class UDataflowCollisionObjectInterface : public UDataflowSimulationInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UDataflowSimulationInterface`

#### class `IDataflowCollisionObjectInterface`  
`class IDataflowCollisionObjectInterface : public IDataflowSimulationInterface`  
_L37-48_
- inherits: `IDataflowSimulationInterface`
- desc: Dataflow collision object interface to send/receive datas (GT <-> PT)
- L41 _public prototype_ `IDataflowCollisionObjectInterface();`
- L44 _public function_ `virtual FString GetSimulationType() const override` — Get the simulation type

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/Interfaces/DataflowConstraintObject.h` (Public)


#### struct `FDataflowConstraintObjectProxy`  
`struct FDataflowConstraintObjectProxy : public FDataflowSimulationProxy`  
_L14-26_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationProxy`
- desc: Dataflow collision object proxy (PT)
- L18 _public prototype_ `FDataflowConstraintObjectProxy();`
- L19 _public prototype_ `virtual ~FDataflowConstraintObjectProxy() override = default;`
- L22 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override` — Get the proxy script struct

#### class `UDataflowConstraintObjectInterface`  
`class UDataflowConstraintObjectInterface : public UDataflowSimulationInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UDataflowSimulationInterface`

#### class `IDataflowConstraintObjectInterface`  
`class IDataflowConstraintObjectInterface : public IDataflowSimulationInterface`  
_L37-49_
- inherits: `IDataflowSimulationInterface`
- desc: Dataflow collision object interface to send/receive datas (GT <-> PT)
- L42 _public prototype_ `IDataflowConstraintObjectInterface();`
- L45 _public function_ `virtual FString GetSimulationType() const override` — Get the simulation type

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/Interfaces/DataflowInterfaceGeometryCachable.h` (Public)


#### class `UDataflowGeometryCachable`  
`class UDataflowGeometryCachable : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(meta = (CannotImplementInterfaceInBlueprint), MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowGeometryCachable`  
`class IDataflowGeometryCachable`  
_L23-39_
- desc: An asset that can produces a geometry cache
- L29 _public prototype_ `virtual TArray<FVector3f> GetGeometryCachePositions(const USkeletalMesh* SkeletalMesh) const = 0;` — Computes skeletal mesh positions for geometry cache
- L32 _public prototype_ `virtual TArray<FVector3f> GetGeometryCachePositions(const UStaticMesh* StaticMesh) const = 0;` — Computes static mesh positions for geometry cache
- L35 _public prototype_ `virtual TOptional<TArray<int32>> GetMeshImportVertexMap(const USkinnedAsset& SkinnedMeshAsset) const = 0;` — Get mapping from final mesh vertex index to raw import vertex index
- L38 _public function_ `virtual bool IsSkeletalMeshAnimationCompatible(const USkeletalMeshComponent* SkeletalMeshComponent) const` — Returns true if the asset supports animation update from a skeletal mesh

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/Interfaces/DataflowPhysicsObject.h` (Public)


#### struct `FDataflowPhysicsObjectProxy`  
`struct FDataflowPhysicsObjectProxy : public FDataflowSimulationProxy`  
_L14-26_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationProxy`
- desc: Dataflow physics object proxy (PT)
- L18 _public prototype_ `FDataflowPhysicsObjectProxy();`
- L19 _public prototype_ `virtual ~FDataflowPhysicsObjectProxy() override = default;`
- L22 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override` — Get the proxy script struct

#### class `UDataflowPhysicsObjectInterface`  
`class UDataflowPhysicsObjectInterface : public UDataflowSimulationInterface`  
_L29-32_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UDataflowSimulationInterface`

#### class `IDataflowPhysicsObjectInterface`  
`class IDataflowPhysicsObjectInterface : public IDataflowSimulationInterface`  
_L37-49_
- inherits: `IDataflowSimulationInterface`
- desc: Dataflow physics object interface to send/receive datas (GT <-> PT)
- L42 _public prototype_ `IDataflowPhysicsObjectInterface();`
- L45 _public function_ `virtual FString GetSimulationType() const override` — Get the simulation type

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/Interfaces/DataflowPhysicsSolver.h` (Public)


#### struct `FDataflowPhysicsSolverProxy`  
`struct FDataflowPhysicsSolverProxy : public FDataflowSimulationProxy`  
_L14-35_
- reflection: `USTRUCT()`
- inherits: `FDataflowSimulationProxy`
- desc: Dataflow simulation physics solver proxy (PT)
- L18 _public prototype_ `FDataflowPhysicsSolverProxy();`
- L19 _public prototype_ `virtual ~FDataflowPhysicsSolverProxy() override = default;`
- L22 _public function_ `virtual const UScriptStruct* GetScriptStruct() const override` — Get the proxy script struct
- L28 _public function_ `virtual void ReadRestartData()` — Advance the solver datas in time
- L31 _public function_ `virtual void AdvanceSolverDatas(const float DeltaTime)` — Advance the solver datas in time
- L34 _public function_ `virtual float GetTimeStep()` — Get the solver time step

#### class `UDataflowPhysicsSolverInterface`  
`class UDataflowPhysicsSolverInterface : public UDataflowSimulationInterface`  
_L38-41_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UDataflowSimulationInterface`

#### class `IDataflowPhysicsSolverInterface`  
`class IDataflowPhysicsSolverInterface : public IDataflowSimulationInterface`  
_L46-58_
- inherits: `IDataflowSimulationInterface`
- desc: Dataflow physics solver interface to send/receive (GT)
- L51 _public prototype_ `IDataflowPhysicsSolverInterface();`
- L54 _public function_ `virtual FString GetSimulationType() const override` — Get the simulation type

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWSIMULATION_API`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/RigidPhysicsDataflowNodes.h` (Public)


#### struct `FRigidSceneSetupDataflowNode`  
`struct FRigidSceneSetupDataflowNode : public FDataflowNode`  
_L13-29_
- reflection: `USTRUCT(meta = (DataflowSimulation))`
- inherits: `FDataflowNode`
- desc: Create a rigid scene
- L26 _public member_ `FRigidPhysicsSceneDataflowState State;` — `UPROPERTY(meta = (DataflowOutput))`
- L27 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Output) const override;`

#### Free symbols / members of external scopes

- L31 _prototype_ `void RegisterRigidPhysicsDataflowSimulationNodes();`

### `Source/Runtime/Dataflow/Simulation/Public/Dataflow/RigidPhysicsSceneState.h` (Public)


#### struct `FRigidPhysicsSceneDataflowState`  
`struct FRigidPhysicsSceneDataflowState`  
_L15-22_
- reflection: `USTRUCT()`
- L20 _public member_ `UE::Physics::FRigidSceneHandle Handle;`
