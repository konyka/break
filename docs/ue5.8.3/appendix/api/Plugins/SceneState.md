# Plugins / SceneState

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneState`
- headers: 49; symbols: 683
- symbol kinds: class=15, delegate=1, enum=10, enumerator=26, function=56, macro=20, member=163, namespace=65, prototype=276, struct=42, typedef=4, variable=5
- PrivateDependencyModuleNames: PropertyBindingUtils, StructUtilsEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneStateBinding, SceneStateEvent

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Internal/Debug/SceneStateDebugStateContext.h` (Internal)


#### struct `UE::SceneState::FDebugStateContext`  
`struct FDebugStateContext`  
_L19-36_
- desc: Context for a debugged state
- L21 _public prototype_ `explicit FDebugStateContext(uint16 InStateIndex, const FSceneStateInstance& InStateInstance);`
- L23 _public function_ `uint16 GetStateIndex() const`
- L28 _public prototype_ `bool Equals(const FDebugStateContext& InOther) const;`
- L32 _private member_ `uint16 StateIndex;` — Index of the state that is being debugged
- L35 _private member_ `uint16 StateInstanceId;` — Identifier for a single state instance

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATE_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Internal/Debug/SceneStateDebugStateInstance.h` (Internal)


#### class `UE::SceneState::FDebugStateInstance`  
`class FDebugStateInstance`  
_L18-60_
- desc: Holds debug information about the state to visualize as node info popups in the state machine graph
- L20 _private member_ `static constexpr double EnteringTime = 0.125;`
- L21 _private member_ `static constexpr double ExitingTime = 0.75;`
- L24 _public prototype_ `explicit FDebugStateInstance(const FDebugStateContext& InContext, EExecutionStatus InInitialStatus);`
- L26 _public prototype_ `uint16 GetStateIndex() const;`
- L29 _public prototype_ `bool operator==(const FDebugStateContext& InOther) const;` — Returns true if the debug instance matches the given state context information
- L32 _public prototype_ `float GetActivePercentage() const;` — Calculate how 'active' a state is. Returns a float value in the range [0, 1]
- L35 _public prototype_ `bool IsValid() const;` — Determines whether the state is in a current valid state
- L41 _public prototype_ `double GetStatusElapsedTime() const;` — Returns the elapsed time for the current execution status. The elapsed time resets every time the execution status changes.
- L43 _public function_ `EExecutionStatus GetExecutionStatus() const`
- L49 _public prototype_ `void SetExecutionStatus(EExecutionStatus InExecutionStatus);` — Sets the execution status of this state debug instance (to match with the actual executed state instance)
- L53 _private member_ `FDebugStateContext DebugStateContext;` — Context of the executed state
- L56 _private member_ `EExecutionStatus ExecutionStatus = EExecutionStatus::NotStarted;` — Current execution status of the state
- L59 _private member_ `double StatusChangeTime = 0.0;` — Last time the status was changed

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Internal/Debug/SceneStateDebugger.h` (Internal)


#### class `UE::SceneState::FDebugger`  
`class FDebugger : public TSharedFromThis<FDebugger>`  
_L25-57_
- inherits: `TSharedFromThis<FDebugger>`
- desc: Processes execution events like state status changes. Editor-only
- L28 _public prototype_ `~FDebugger();`
- L31 _public prototype_ `void AttachTo(USceneStateObject* InObject);` — Called to attach this debugger to the target scene state object
- L34 _public prototype_ `void Detach();` — Called to detach this debugger from any existing scene state object
- L37 _public prototype_ `bool IsAttachedTo(USceneStateObject* InObject) const;` — Returns whether this debugger is attached to the given object
- L40 _public prototype_ `void ForEachDebugInstanceOfState(uint16 InStateIndex, TFunctionRef<void(const FDebugStateInstance&)> InFunc);` — Calls the given functor for every state debug instance that matches the state index
- L43 _public prototype_ `void NotifyStateStatusChanged(const FDebugStateContext& InContext, UE::SceneState::EExecutionStatus InStatus);` — Called when a state instance has changed status
- L47 _private prototype_ `void Initialize();` — Populates debug state instances with currently active states
- L50 _private prototype_ `void CleanInvalidDebugInstances();` — Removes all state debug instances that are no longer valid
- L53 _private member_ `TArray<FDebugStateInstance> DebugStateInstances;` — All the relevant debug instances that are or were recently active.
- L56 _private member_ `TWeakObjectPtr<USceneStateObject> DebuggedObjectWeak;` — The object that this debugger is currently attached to

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENESTATE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Private/SceneStateExecutionContextRegistry.h` (Private)


#### class `UE::SceneState::FExecutionContextRegistry`  
`class FExecutionContextRegistry : public TSharedFromThis<FExecutionContextRegistry>`  
_L15-47_
- inherits: `TSharedFromThis<FExecutionContextRegistry>`
- desc: Holds all the contexts setup to the scene state object owning this registry
- L19 _public prototype_ `FExecutionContextHandle RegisterContext(const FSceneStateExecutionContext* InContext);` — Called on Context setup to add the given context to the registry
- L22 _public prototype_ `void UnregisterContext(const FSceneStateExecutionContext* InContext);` — Called on Context destructor to remove the given context from the registry
- L25 _public prototype_ `const FSceneStateExecutionContext* FindContext(FExecutionContextHandle InHandle) const;` — Retrieves the context mapped to a given handle
- L28 _public prototype_ `FExecutionContextHandle FindHandle(const FSceneStateExecutionContext& InContext) const;` — Retrieves the handle mapped to the given context
- L32 _public prototype_ `void ForEachExecutionContext(TFunctionRef<void(const FSceneStateExecutionContext&)> InFunctor);` — Iterates each registered execution context. Used only for editor debug visualization
- L37 _private member_ `TArray<FExecutionContextHandle> Handles;` — Unique handles where each handle is mapped to a context at the same index in the context array
- L40 _private member_ `TArray<const FSceneStateExecutionContext*> Contexts;` — Registered context where each context is mapped to a handle at the same index in the handles array
- L43 _private member_ `uint64 NextHandleId = 1;` — Id to the next handle to use for this registry
- L46 _private member_ `bool bIterating = false;` — Flag to detect when contexts are unexpectedly being added to/removed from the registry while iterating the contexts

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Private/SceneStateLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneState, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneState, Log, All);`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Conduit/SceneStateConduit.h` (Public)


#### struct `FSceneStateConduit`  
`struct FSceneStateConduit`  
_L26-68_
- reflection: `USTRUCT()`
- desc: Defines a conduit, a transition indirection
- L31 _public prototype_ `void Link(const FSceneStateConduitLink& InConduitLink, TNotNull<const UClass*> InOwnerClass);` — Called when the Owner Class is linking to cache the Event function and Result property
- L34 _public prototype_ `void Setup(const FSceneStateExecutionContext& InContext) const;` — Called when a state that could evaluate this conduit has entered. Allocates and initializes the conduit instance
- L37 _public prototype_ `bool Evaluate(const UE::SceneState::FTransitionEvaluationParams& InParams) const;` — Called to evaluate this conduit. Returns true if the conduit should take place
- L40 _public prototype_ `void Exit(const FSceneStateExecutionContext& InContext) const;` — Called when the State has exited. Cleans up the conduit instance
- L42 _public function_ `FSceneStateRange GetTransitionRange() const`
- L49 _private prototype_ `bool ProcessEvaluationEvent(const UE::SceneState::FTransitionEvaluationParams& InParams) const;` — Calls the evaluation event (can return early if optimized away via the evaluation flags)
- L53 _private member_ `FSceneStateRange TransitionRange;` — `UPROPERTY()` — Index and count of the exit transitions that go out of this conduit and into other targets (states, conduits, exit).
- L57 _private member_ `ESceneStateTransitionEvaluationFlags EvaluationFlags = ESceneStateTransitionEvaluationFlags::None;` — `UPROPERTY()` — Transition flags indicating how a transition should be evaluated
- L61 _private member_ `TObjectPtr<UFunction> EvaluationEvent;` — `UPROPERTY(Transient)` — Conduit evaluation event to execute
- L64 _private member_ `FStructProperty* ResultProperty = nullptr;` — Pointer to the result property of this conduit evaluation

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Conduit/SceneStateConduitInstance.h` (Public)


#### struct `FSceneStateConduitInstance`  
`struct FSceneStateConduitInstance`  
_L10-20_
- reflection: `USTRUCT()`
- desc: Instance data of a conduit
- L19 _public member_ `bool bInitialized = false;` — `UPROPERTY()` — Flag to determine if the conduit instance has already been initialized. Used as a way to avoid re-setting up all the exit transitions of a conduit.

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Conduit/SceneStateConduitLink.h` (Public)


#### struct `FSceneStateConduitLink`  
`struct FSceneStateConduitLink`  
_L13-24_
- reflection: `USTRUCT()`
- desc: Holds information about the conduit that is only used in conduit link time @see FSceneStateConduitLink::Link
- L19 _public member_ `FName EventName;` — `UPROPERTY()` — Name to lookup and set the Event Function
- L23 _public member_ `FName ResultPropertyName;` — `UPROPERTY()` — Name of the Result Property the Event function sets

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Functions/SceneStateFunction.h` (Public)


#### struct `FSceneStateFunction`  
`struct FSceneStateFunction`  
_L43-88_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base struct for all scene state functions. Binding Functions are a layer of logic that execute prior to evaluating owner's bindings. The function's instance data is expected to have its output properties with meta "Output", and these will be hidden in the UI. This property is used to find which bindings the function can be used for. Example: USTRUCT() struct FTextToStringFunctionInstance { GENERATED_BODY() UPROPERTY(EditAnywhere, Category="Test") FText Text; UPROPERTY(EditAnywhere, Category="Test", meta=(Output)) FString Result; };
- L52 _public prototype_ `const UScriptStruct* GetFunctionDataType() const;` — Called in-editor to get the function data type @return the function data struct type
- L56 _public prototype_ `void Setup(const FSceneStateExecutionContext& InContext) const;` — Called when binding owners are setting up and allocating instance data
- L63 _public prototype_ `void Execute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const;` — Called right before evaluating bindings for the owner. @param InContext reference to current execution context. @param InFunctionInstance data view of the function instance data
- L66 _public prototype_ `void Cleanup(const FSceneStateExecutionContext& InContext) const;` — Called when binding owners are cleaning up their allocated instance data
- L71 _protected prototype_ `virtual const UScriptStruct* OnGetFunctionDataType() const PURE_VIRTUAL(FSceneStateFunction::OnGetFunctionDataType, return nullptr;);` — Called to retrieve the data type that this function expects
- L75 _protected function_ `virtual void OnExecute(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const` — Called right before evaluating bindings for the owner.
- L81 _private prototype_ `bool ApplyBindings(const FSceneStateExecutionContext& InContext, FStructView InFunctionInstance) const;` — Applies the bindings batch to the function instance
- L85 _private member_ `FPropertyBindingIndex16 BindingsBatch;` — `UPROPERTY()` — Bindings Batch where this function is target

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSceneStateFunction> : TStructOpsTypeTraitsBase2<FSceneStateFunction>`  
_L93-99_
- inherits: `TStructOpsTypeTraitsBase2<FSceneStateFunction>`
- desc: The pure virtual functions in FSceneStateFunction are editor-only.

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L96-98_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L97 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon436a4a610103`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Functions/SceneStateFunctionInstanceBatch.h` (Public)


#### struct `FSceneStateFunctionInstanceBatch`  
`struct FSceneStateFunctionInstanceBatch`  
_L11-22_
- reflection: `USTRUCT()`
- desc: Holds all the function instances for a given batch
- L17 _public member_ `FSceneStateRange FunctionRange;` — `UPROPERTY()` — The function range (in absolute index) of the functions within the batch
- L21 _public member_ `FInstancedStructContainer FunctionInstances;` — `UPROPERTY()` — Container holding all the function instances for a batch in a contiguous block of memory

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Functions/SceneStateFunctionMetadata.h` (Public)


#### struct `FSceneStateFunctionMetadata`  
`struct FSceneStateFunctionMetadata`  
_L10-18_
- reflection: `USTRUCT()`
- desc: Metadata information about the function. Its data is meant to be available/accessible in editor-only builds
- L16 _public member_ `FGuid FunctionId;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/ISceneStateSchemaProvider.h` (Public)


#### class `USceneStateSchemaProvider`  
`class USceneStateSchemaProvider : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `ISceneStateSchemaProvider`  
`class ISceneStateSchemaProvider`  
_L16-23_
- L22 _public prototype_ `virtual TSubclassOf<USceneStateSchema> GetSceneStateSchemaClass() const = 0;` — Returns the schema used for the scene state

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneState.h` (Public)


#### struct `FSceneStateMetadata`  
`struct FSceneStateMetadata`  
_L30-38_
- reflection: `USTRUCT()`
- desc: Metadata information about the State. Available only in editor
- L36 _public member_ `FString StateName;` — `UPROPERTY()`

#### struct `FSceneState`  
`struct FSceneState`  
_L46-146_
- reflection: `USTRUCT()`
- desc: Runtime-immutable information of a state. Holds the range of tasks, state machines and transitions belonging to the state. These states are stored in the Scene State Generated Class.
- L51 _public prototype_ `void Enter(const FSceneStateExecutionContext& InContext) const;` — Called the state becomes the active state in its parent state machine
- L54 _public prototype_ `void Tick(const FSceneStateExecutionContext& InContext, float InDeltaSeconds) const;` — Called on every tick while the state is active
- L57 _public prototype_ `void Exit(const FSceneStateExecutionContext& InContext) const;` — Called when the state is no longer active in its parent state machine
- L60 _public prototype_ `const FInstancedPropertyBag& GetParameters() const;` — Get the template parameters of the state
- L63 _public prototype_ `const UStruct* GetParametersStruct() const;` — Get the template parameter struct
- L65 _public function_ `FSceneStateRange GetTaskRange() const`
- L70 _public function_ `FSceneStateRange GetStateMachineRange() const`
- L75 _public function_ `FSceneStateRange GetTransitionRange() const`
- L80 _public function_ `FSceneStateRange GetEventHandlerRange() const`
- L86 _public prototype_ `void UpdateActiveTasks(const FSceneStateExecutionContext& InContext, FSceneStateInstance& InStateInstance) const;` — Starts pending tasks whose prerequisites are satisfied
- L89 _public prototype_ `FStringView GetStateName(const FSceneStateExecutionContext& InContext) const;` — Returns the State Name used for logging. Returns an empty string view if metadata is not available
- L92 _public prototype_ `bool HasPendingTasks(const FSceneStateExecutionContext& InContext) const;` — Returns whether there's any Task pending to finish
- L95 _public prototype_ `UE_INTERNAL void AllocateTaskInstances(const FSceneStateExecutionContext& InContext, TConstArrayView<FConstStructView> InTemplateTaskInstances) const;` — Called on start to create the required task instances that will run for this state
- L99 _private prototype_ `bool ApplyBindings(const FSceneStateExecutionContext& InContext, FSceneStateInstance& InStateInstance) const;` — Applies Bindings to the given state instance
- L102 _private prototype_ `UE_INTERNAL void InstanceTaskObjects(UObject* InOuter , TConstArrayView<FStructView> InTargets , TConstArrayView<FConstStructView> InSources , TFunctionRef<UObject*(FObjectDuplicationParameters&)> InDuplicationFunc) const;` — Instances the instanced references in source data into the target data using the provided duplication functor
- L108 _private prototype_ `void CaptureEvents(const FSceneStateExecutionContext& InContext) const;` — Captures all the events of interest from the handlers this state owns
- L111 _private prototype_ `void ResetCapturedEvents(const FSceneStateExecutionContext& InContext) const;` — Removes all the event data that was captured by the handlers this state owns
- L115 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Template parameters to use for the state instances
- L119 _private member_ `FPropertyBindingIndex16 BindingsBatch;` — `UPROPERTY()` — Bindings batch where this state is the target
- L123 _private member_ `FSceneStateRange TaskRange;` — `UPROPERTY()` — Index and Count of the tasks that belong to this state.
- L127 _private member_ `FSceneStateRange StateMachineRange;` — `UPROPERTY()` — Index and Count of the sub state machines that belong to this state.
- L131 _private member_ `FSceneStateRange TransitionRange;` — `UPROPERTY()` — Index and count of the exit transitions that go out of this state and into other targets (states, conduits, exit).
- L135 _private member_ `FSceneStateRange EventHandlerRange;` — `UPROPERTY()` — Index and Count of the events that this state and its tasks and its sub state machines will be handling
- L141 _private member_ `UE::SceneState::FReentryHandle ReentryHandle;` — Handle to ensure reentry is not hit @see FSceneStateReentryGuard

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENESTATE_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SceneState` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateEnums.h` (Public)


#### enum `UE::SceneState::EIterationResult`  
`enum class EIterationResult : uint8`  
_L12-16_
- desc: Defines the next actions for the current iteration
- L14 _public enumerator_ `Continue`
- L15 _public enumerator_ `Break`

#### enum `UE::SceneState::EExecutionStatus`  
`enum class EExecutionStatus : uint8`  
_L19-24_
- desc: Defines the possible execution status of a State, Task and State Machine
- L21 _public enumerator_ `NotStarted`
- L22 _public enumerator_ `Running`
- L23 _public enumerator_ `Finished`

#### enum `UE::SceneState::ETaskObjectType`  
`enum class ETaskObjectType : uint8`  
_L27-34_
- desc: Describes the different components of a task
- L29 _public enumerator_ `None`
- L31 _public enumerator_ `Task` — Object deriving from FSceneStateTask that contains the logic to run
- L33 _public enumerator_ `TaskInstance` — Object deriving from FSceneStateTaskInstance containing the instance data to feed to the task

#### enum `ESceneStateTaskFlags`  
`enum class ESceneStateTaskFlags : uint8`  
_L40-49_
- reflection: `UENUM()`
- desc: Defines common task behaviors: whether it should tick, whether it handles custom bindings, etc.
- L42 _public enumerator_ `None = 0`
- L45 _public enumerator_ `Ticks = 1 << 0` — Task will always call OnTick when Active
- L48 _public enumerator_ `HasBindingExtension = 1 << 1` — Task has custom binding extension

#### enum `ESceneStateMachineRunMode`  
`enum class ESceneStateMachineRunMode : uint8`  
_L54-61_
- reflection: `UENUM()`
- desc: Defines the possible ways a state machine will run
- L57 _public enumerator_ `Auto` — The state machine will run automatically
- L60 _public enumerator_ `Manual` — The state machine will run through other means (e.g. State Machine Task)

#### enum `ESceneStateTaskStopReason`  
`enum class ESceneStateTaskStopReason : uint8`  
_L65-72_
- reflection: `UENUM(BlueprintType)`
- desc: Defines the reasons why a task has stopped
- L68 _public enumerator_ `State` — State ended (transitioning, or end play) so it's forcing all its Active States to stop
- L71 _public enumerator_ `Finished` — Task was marked as finished

#### enum `ESceneStateTransitionEvaluationFlags`  
`enum class ESceneStateTransitionEvaluationFlags : uint8`  
_L76-89_
- reflection: `UENUM()`
- desc: Defines how a transition evaluation should take place
- L78 _public enumerator_ `None = 0`
- L81 _public enumerator_ `WaitForTasksToFinish = 1 << 0` — Transition will not evaluate until all the current tasks have finished
- L88 _public enumerator_ `EvaluationEventAlwaysTrue = 1 << 1` — Transition Evaluation Event will not be processed and will always evaluate to true. This is set when the transition graph compiler finds that the transition evaluation event will always return true, so no event is created and this flag is set.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L50 _prototype_ `ENUM_CLASS_FLAGS(ESceneStateTaskFlags);`
- L90 _prototype_ `ENUM_CLASS_FLAGS(ESceneStateTransitionEvaluationFlags);`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateExecutionContext.h` (Public)


#### struct `FSceneStateExecutionContext`  
`struct FSceneStateExecutionContext`  
_L62-368_
- reflection: `USTRUCT()`
- desc: Struct representing an execution. It is used mainly to run a Scene State Object, but is also used in to run the same state machines, state, etc. multiple times. @see USceneStateObject @see FSceneStateMachineTask This struct is the place holding the mutable data during execution, as the data residing in the Scene State Generated Class is immutable during execution. This struct also offers functionality to both get class (immutable) objects (states, state machines, etc) and their instance (mutable) data (state instances, state machine instances, etc). Prior to execution, ensure that the template data is in a valid state, as it is assumed to be valid during execution to avoid re-checking validity. See USceneStateObject as an example.
- L66 _public member_ `static const FSceneStateExecutionContext InvalidContext;`
- L68 _public prototype_ `~FSceneStateExecutionContext();`
- L71 _public prototype_ `TWeakPtr<const UE::SceneState::FExecutionContextRegistry> GetContextRegistry() const;` — Gets the registry that this context is registered to
- L74 _public prototype_ `UE::SceneState::FExecutionContextHandle GetContextHandle() const;` — Gets the context handle for this execution context, if any
- L76 _public function_ `const USceneStateTemplateData* GetTemplateData() const`
- L82 _public prototype_ `const FSceneStateBindingCollection& GetBindingCollection() const;` — Gets the binding collection owned by the template data
- L85 _public prototype_ `const FString& GetExecutionContextName() const;` — Returns the Player Debug Name for logging purposes
- L88 _public prototype_ `USceneStateObject* GetRootObject() const;` — Retrieves the Root Object of this Execution
- L91 _public prototype_ `UObject* GetContextObject() const;` — Retrieves the Context Object for this Execution
- L94 _public prototype_ `USceneStateEventStream* GetEventStream() const;` — Gets the Event Stream from the Root State if available
- L100 _public prototype_ `void Setup(const FSceneStateExecutionContext& InParentContext);` — Initialization for a context with a parent context. @param InParentContext the parent of this execution context
- L107 _public prototype_ `void Setup(TNotNull<USceneStateObject*> InRootState);` — Initialization for the Context. Through the given root state it pre-allocates the instance data that will be used @param InRootState the parameters containing the template data and context for this execution
- L129 _public prototype_ `void Setup(const FSetupParams& InParams);` — Initialization for the Context. Through the given root state it pre-allocates the instance data that will be used @param InParams the parameters containing the template data and context for this execution
- L132 _public prototype_ `void Reset();` — Called when cleaning up the instances of this execution
- L135 _public prototype_ `FPropertyBindingDataView FindDataView(const FSceneStateBindingDataHandle& InDataHandle) const;` — Finds the data view that matches the given data handle
- L139 _public function_ `template<typename T = void> T* ResolveProperty(const FSceneStatePropertyReference& InPropertyReference) const` — Returns the pointer to the property value address the given reference is mapped to
- L145 _public prototype_ `void ForEachTask(const FSceneState& InState, TFunctionRef<UE::SceneState::EIterationResult(const FSceneStateTask&, uint16 )> InCallable) const;` — Invokes a given callable for each task in the given state
- L148 _public prototype_ `TArray<FConstStructView> GetTemplateTaskInstances(const FSceneState& InState) const;` — Returns an array of const views of the Template Task Instances of the given State
- L151 _public prototype_ `TConstArrayView<uint16> GetTaskPrerequisites(const FSceneStateTask& InTask) const;` — Returns a sliced view of the prerequisite task indices for a given task, in relative index based on the owning state's task range
- L154 _public prototype_ `TConstArrayView<FSceneStateTransition> GetTransitions(const FSceneState& InState) const;` — Returns a sliced view of all the Exit Transitions going out of the given State
- L157 _public prototype_ `TConstArrayView<FSceneStateTransition> GetTransitions(const FSceneStateConduit& InConduit) const;` — Returns a sliced view of all the Exit Transitions going out of the given Conduit
- L160 _public prototype_ `FInstancedPropertyBag GetTemplateTransitionParameter(const FSceneStateTransition& InTransition) const;` — Gets the template transition parameter for the given transition
- L163 _public prototype_ `TConstArrayView<FSceneStateMachine> GetStateMachines(const FSceneState& InState) const;` — Returns a sliced view of all the Sub State Machines belonging to the given State
- L166 _public prototype_ `TConstArrayView<FSceneStateEventHandler> GetEventHandlers(const FSceneState& InState) const;` — Returns a sliced view of all the Event Handlers in the given State
- L170 _public prototype_ `const FSceneStateMetadata* GetStateMetadata(const FSceneState& InState) const;` — Returns the State Metadata of a given state
- L174 _public prototype_ `const FSceneStateMachine* GetStateMachine(const FGuid& InStateMachineId) const;` — Returns the State Machine linked to the given id
- L177 _public prototype_ `const FSceneStateMachine* GetStateMachine(uint16 InAbsoluteIndex) const;` — Returns the State Machine at the given absolute index
- L180 _public prototype_ `const FSceneStateMachine* GetContextStateMachine() const;` — Returns the most relevant State Machine in the current scope, if any
- L183 _public prototype_ `const FSceneState* GetActiveState(const FSceneStateMachine& InStateMachine) const;` — Returns the currently Active State within this context for the given State Machine
- L186 _public prototype_ `const FSceneState* GetState(uint16 InAbsoluteIndex) const;` — Returns the State at the given absolute index
- L189 _public prototype_ `const FSceneStateEventHandler* GetEventHandler(uint16 InAbsoluteIndex) const;` — Returns the Event Handler at the given absolute Index
- L192 _public prototype_ `const FSceneState* GetState(const FSceneStateMachine& InStateMachine, uint16 InRelativeIndex) const;` — Returns the State at the given relative index for the given State Machine
- L195 _public prototype_ `const FSceneStateConduit* GetConduit(const FSceneStateMachine& InStateMachine, uint16 InRelativeIndex) const;` — Returns the Conduit at the given relative index for the given State Machine
- L198 _public prototype_ `FSceneStateInstance& FindOrAddStateInstance(const FSceneState& InState) const;` — Returns the State Instance of this context for the given state, adding a new one if it's not found
- L201 _public prototype_ `FSceneStateInstance* FindStateInstance(uint16 InAbsoluteIndex) const;` — Returns the existing State Instance of this context for the given state absolute index. Null if not found
- L204 _public prototype_ `FSceneStateInstance* FindStateInstance(const FSceneState& InState) const;` — Returns the existing State Instance of this context for the given state. Null if not found
- L207 _public prototype_ `void RemoveStateInstance(const FSceneState& InState) const;` — Removes the State Instance of this context for the given state
- L210 _public prototype_ `void ForEachStateInstance(TFunctionRef<void(uint16, const FSceneStateInstance&)> InFunc) const;` — Iterates the active state instances of this context
- L213 _public prototype_ `FConstStructView FindTask(uint16 InAbsoluteIndex) const;` — Returns the Task of this context for the given task absolute index. Returns an invalid view if not found
- L216 _public prototype_ `uint16 FindTaskRelativeIndex(const FSceneStateTask& InTask) const;` — Gets the task index relative to the other tasks in the state
- L219 _public prototype_ `UE_INTERNAL FStructView FindTaskInstance(const FSceneStateTask& InTask) const;` — Returns the Task Instance of this context for the given task. Returns an invalid view if not found
- L222 _public prototype_ `FStructView FindTaskInstance(uint16 InTaskAbsoluteIndex) const;` — Returns the Task Instance of this context for the given task absolute index. Returns an invalid view if not found
- L225 _public prototype_ `UE_INTERNAL TOptional<UE::SceneState::EExecutionStatus> GetTaskStatus(const FSceneStateTask& InTask) const;` — Returns the given task's execution status, or unset if task was not found
- L228 _public prototype_ `void SetTaskStatus(const FSceneStateTask& InTask, UE::SceneState::EExecutionStatus InStatus) const;` — Set the task status of this context for the given task
- L231 _public prototype_ `FSceneStateMachineInstance* FindOrAddStateMachineInstance(const FSceneStateMachine& InStateMachine) const;` — Returns the State Machine Instance of this context for the given state machine, adding a new one if it's not found
- L234 _public prototype_ `FSceneStateMachineInstance* FindStateMachineInstance(uint16 InAbsoluteIndex) const;` — Returns the existing State Machine Instance of this context for the given state machine absolute index. Null if not found
- L237 _public prototype_ `FSceneStateMachineInstance* FindStateMachineInstance(const FSceneStateMachine& InStateMachine) const;` — Returns the existing State Machine Instance of this context for the given state machine. Null if not found
- L240 _public prototype_ `void RemoveStateMachineInstance(const FSceneStateMachine& InStateMachine) const;` — Removes the State Machine Instance of this context for the given state machine
- L243 _public prototype_ `FSceneStateTransitionInstance* FindOrAddTransitionInstance(const FSceneStateTransition& InTransition) const;` — Returns the transition instance of this context for the given transition, adding a new one if it's not found
- L246 _public prototype_ `FSceneStateTransitionInstance* FindTransitionInstance(uint16 InAbsoluteIndex) const;` — Returns the transition instance of this context for the given transition absolute index, or null if not found
- L249 _public prototype_ `FSceneStateTransitionInstance* FindTransitionInstance(const FSceneStateTransition& InTransition) const;` — Returns the transition instance of this context for the given transition, or null if not found
- L252 _public prototype_ `void RemoveTransitionInstance(const FSceneStateTransition& InTransition) const;` — Removes the transition instance of this context for the given transition
- L255 _public prototype_ `FSceneStateConduitInstance* FindOrAddConduitInstance(const FSceneStateConduit& InConduit) const;` — Returns the conduit instance of this context for the given conduit, adding a new one if it's not found
- L258 _public prototype_ `void RemoveConduitInstance(const FSceneStateConduit& InConduit) const;` — Removes the conduit instance of this context for the given conduit
- L264 _public prototype_ `bool SetupFunctionInstances(FPropertyBindingIndex16 InBindingsBatch) const;` — Allocates the function instance data for a given binding batch @return true if there were valid functions within the batch, false otherwise
- L267 _public prototype_ `void RemoveFunctionInstances(FPropertyBindingIndex16 InBindingsBatch) const;` — Removes the function instance data for a given binding batch
- L270 _public prototype_ `FConstStructView FindFunction(uint16 InAbsoluteIndex) const;` — Returns the function of this context for the given function absolute index. Returns an invalid view if not found
- L273 _public prototype_ `FStructView FindFunctionInstance(uint16 InAbsoluteIndex) const;` — Returns the function instance of this context for the given function absolute index. Returns an invalid view if not found
- L276 _public prototype_ `void SetStateStatus(const FSceneState& InState, FSceneStateInstance& InStateInstance, UE::SceneState::EExecutionStatus InStatus) const;` — Called to set the status of the given state
- L279 _public prototype_ `const FSceneStateExecutionContext* FindParentContext() const;` — Retrieves the parent execution context if existing. Can be null
- L282 _public prototype_ `uint16 GetStateIndex(const FSceneState& InState) const;` — Retrieves the Absolute Index of a State in the State array
- L285 _public prototype_ `uint16 GetStateMachineIndex(const FSceneStateMachine& InStateMachine) const;` — Retrieves the Absolute Index of a State Machine in the State Machine array
- L288 _public prototype_ `uint16 GetTransitionIndex(const FSceneStateTransition& InTransition) const;` — Retrieves the Absolute Index of a Transition in the Transitions array
- L291 _public prototype_ `uint16 GetConduitIndex(const FSceneStateConduit& InConduit) const;` — Retrieves the Absolute Index of a Conduit in the Conduits array
- L296 _private member_ `TWeakObjectPtr<UObject> ContextObjectWeak;` — `UPROPERTY()` — Weak ptr to the context holding this execution
- L300 _private member_ `TWeakObjectPtr<USceneStateEventStream> EventStreamWeak;` — `UPROPERTY()` — Weak ptr to the event stream for this execution
- L304 _private member_ `TObjectPtr<USceneStateObject> RootObject;` — `UPROPERTY()` — Pointer to the root object owning this execution
- L308 _private member_ `FString ContextName;` — `UPROPERTY()` — Description of the context
- L312 _private member_ `TObjectPtr<const USceneStateTemplateData> TemplateData;` — `UPROPERTY()` — Object owning the scene state template data
- L319 _private member_ `mutable TMap<uint16, FSceneStateInstance> StateInstances;` — `UPROPERTY()` — Map of State Index to its Instance Data It's allocated when the state starts and removed on exit.
- L326 _private member_ `mutable TMap<uint16, FSceneStateMachineInstance> StateMachineInstances;` — `UPROPERTY()` — Map of State Machine Index to its Instance Data It's allocated when the State Machine starts and removed on exit.
- L329 _private member_ `mutable TArray<uint16, TInlineAllocator<4>> StateMachineExecutionStack;` — Array of state machine absolute indices from outermost to innermost for this execution context
- L336 _private member_ `mutable TMap<uint16, FSceneStateTransitionInstance> TransitionInstances;` — `UPROPERTY()` — Map of the transition absolute index to its instance data It's allocated when the state starts (along with the other exit transitions) and removed on state exit
- L343 _private member_ `mutable TMap<uint16, FSceneStateConduitInstance> ConduitInstances;` — `UPROPERTY()` — Map of the conduit absolute index to its instance data It's allocated when a state that could evaluate the conduit starts and removed on state exit
- L350 _private member_ `mutable TMap<FPropertyBindingIndex16, FSceneStateFunctionInstanceBatch> FunctionInstanceBatches;` — `UPROPERTY()` — Map of the batch index to the function instances within the batch It's allocated when its owner is setup, and removed on the owners exit
- L356 _private member_ `mutable TMap<uint16, FStructView> FunctionInstanceViews;` — Map of the function absolute index to the view of the function instance It's allocated when its owner is setup, and removed on the owners exit
- L359 _private member_ `UE::SceneState::FExecutionContextHandle ContextHandle;` — Context handle to this execution.
- L362 _private member_ `UE::SceneState::FExecutionContextHandle ParentHandle;` — Context handle to the parent execution context. Can be invalid.
- L365 _private member_ `TWeakPtr<UE::SceneState::FExecutionContextRegistry> ContextRegistryWeak;` — Weak reference to the registry containing this context

#### struct `FSceneStateExecutionContext::FSetupParams`  
`struct FSetupParams`  
_L109-123_
- L112 _public member_ `const USceneStateTemplateData* TemplateData = nullptr;` — Template data object holding all the state machines, states, etc.
- L114 _public member_ `USceneStateObject* RootObject = nullptr;` — Root object instance
- L116 _public member_ `UObject* ContextObject = nullptr;` — Context object for utility purposes (e.g. to get world from context, etc)
- L118 _public member_ `USceneStateEventStream* EventStream = nullptr;` — Event stream to use for execution
- L120 _public member_ `TSharedPtr<UE::SceneState::FExecutionContextRegistry> ContextRegistry;` — Context registry to use
- L122 _public member_ `FString ContextName;` — Debug name describing the context

#### struct `TIsTriviallyRelocatable`  
`template<UE::CDerivedFrom<FSceneStateExecutionContext> T> struct TIsTriviallyRelocatable<T>`  
_L374-377_
- desc: FSceneStateExecutionContext is not trivially relocatable
- L376 _public member_ `static inline constexpr bool Value = false;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API SCENESTATE_API`
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateExecutionContextHandle.h` (Public)


#### class `UE::SceneState::FExecutionContextHandle`  
`class FExecutionContextHandle`  
_L12-34_
- desc: Holds a unique number mapping a context in a registry
- L15 _public function_ `bool IsValid() const`
- L20 _public function_ `bool operator==(FExecutionContextHandle InOtherHandle) const`
- L31 _private member_ `uint64 Id = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L25 _function_ `friend uint32 GetTypeHash(FExecutionContextHandle InHandle)` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateExecutionScope.h` (Public)


#### class `UE::SceneState::FExecutionScope`  
`class FExecutionScope`  
_L19-32_
- desc: Adds the given State Machine to the Execution Stack on scope enter / constructor and removes it on scope exit / destructor. Stores references and should be short-lived within a function's scope.
- L22 _public prototype_ `explicit FExecutionScope(const FSceneStateExecutionContext& InContext, const FSceneStateMachine& InStateMachine);`
- L24 _public prototype_ `~FExecutionScope();`
- L28 _private member_ `const FSceneStateExecutionContext& ExecutionContext;` — The execution context containing the execution stack
- L31 _private member_ `uint16 StateMachineIndex = std::numeric_limits<uint16>::max();` — Index to the state machine in the execution scope

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateGeneratedClass.h` (Public)


#### class `USceneStateGeneratedClass`  
`class USceneStateGeneratedClass : public UBlueprintGeneratedClass`  
_L28-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- desc: Object Class for the Scene State Object Holds the template data for scene state objects. @see USceneStateTemplateData @see FSceneStateExecutionContext
- L33 _public prototype_ `USceneStateGeneratedClass();`
- L35 _public function_ `const USceneStateTemplateData* GetTemplateData() const`
- L41 _public prototype_ `virtual void Link(FArchive& Ar, bool bInRelinkExistingProperties) override;`
- L42 _public prototype_ `virtual void PurgeClass(bool bInRecompilingOnLoad) override;`
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void BeginDestroy() override;`
- L52 _private prototype_ `void LinkData();` — Called to link the template data
- L55 _private prototype_ `UE_INTERNAL void ResolveBindings();` — Called to resolve the template data bindings
- L58 _private prototype_ `UE_INTERNAL bool IsFullClass() const;` — Returns true if this class is a 'full' class (i.e. not a SKEL_ or REINST_ class)
- L61 _private prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& InReplacementMap);`
- L62 _private prototype_ `void OnStructsReinstanced(const UUserDefinedStruct& InStruct);`
- L67 _private member_ `TObjectPtr<USceneStateTemplateData> TemplateData;` — `UPROPERTY()` — Scene State template data for this class.
- L70 _private member_ `FDelegateHandle OnObjectsReinstancedHandle;`
- L71 _private member_ `FDelegateHandle OnStructsReinstancedHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateInstance.h` (Public)


#### struct `FSceneStateInstance`  
`struct FSceneStateInstance`  
_L16-73_
- reflection: `USTRUCT()`
- desc: Instance data of a State
- L21 _public prototype_ `FSceneStateInstance();`
- L22 _public prototype_ `FSceneStateInstance(const FSceneStateInstance&) = default;`
- L23 _public prototype_ `FSceneStateInstance(FSceneStateInstance&&) = default;`
- L24 _public prototype_ `FSceneStateInstance& operator=(const FSceneStateInstance&) = default;`
- L25 _public prototype_ `FSceneStateInstance& operator=(FSceneStateInstance&&) = default;`
- L29 _public prototype_ `void Setup(const FSceneState& InState);` — Called to setup the state instance for use
- L32 _public member_ `float ElapsedTime = 0.f;` — `UE_DEPRECATED(5.8, "ElapsedTime is deprecated, it is no longer in use.")`
- L35 _public prototype_ `UE::SceneState::EExecutionStatus GetStatus() const;` — Gets the execution status of the state instance
- L38 _public prototype_ `void SetStatus(UE::SceneState::EExecutionStatus InStatus);` — Sets the execution status of the state instance
- L42 _public member_ `UE::SceneState::EExecutionStatus Status = UE::SceneState::EExecutionStatus::NotStarted;` — `UE_DEPRECATED(5.8, "Public access to Status is deprecated, and it will become private in a future release. Please update code to use the setter/getter instead.")` — Current status of this state instance
- L45 _public prototype_ `UE_INTERNAL uint16 GetInstanceId() const;` — Get an identifier for this instance
- L48 _public prototype_ `FInstancedPropertyBag& GetParameters();` — Returns the state parameters
- L51 _public prototype_ `FInstancedStructContainer& GetTaskInstances();` — Returns the instance data of the tasks owned by this state
- L54 _public prototype_ `UE::SceneState::EExecutionStatus GetTaskStatus(uint16 InTaskRelativeIndex) const;` — Returns the status of the task at the given index
- L57 _public prototype_ `void SetTaskStatus(uint16 InTaskRelativeIndex, UE::SceneState::EExecutionStatus InTaskStatus);` — Sets the status of the task at the given index
- L62 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Instanced state parameters
- L66 _private member_ `FInstancedStructContainer TaskInstances;` — `UPROPERTY()` — The task instances owned by this state
- L69 _private member_ `TArray<UE::SceneState::EExecutionStatus> TaskStatuses;` — Execution status of the tasks
- L72 _private member_ `uint16 InstanceId;` — The id for this instance. This is used to differentiate state instances for a same state and consequently task instances for a same task

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateMachine.h` (Public)


#### struct `FSceneStateMachine`  
`struct FSceneStateMachine`  
_L33-121_
- reflection: `USTRUCT()`
- desc: Runtime-immutable information of a state machine. Holds the range of states it will run, as well as the conduits found in the state machine, and other template data like template state machine parameters. These state machines are stored in the Scene State Generated Class.
- L37 _public function_ `bool IsValid() const`
- L42 _public prototype_ `void Setup(const FSceneStateExecutionContext& InContext) const;`
- L44 _public prototype_ `void Start(const FSceneStateExecutionContext& InContext) const;`
- L46 _public prototype_ `void Tick(const FSceneStateExecutionContext& InContext, float InDeltaSeconds) const;`
- L48 _public prototype_ `void Stop(const FSceneStateExecutionContext& InContext) const;`
- L50 _public function_ `FSceneStateRange GetStateRange() const`
- L55 _public function_ `FSceneStateRange GetConduitRange() const`
- L60 _public function_ `uint16 GetEntryIndex() const`
- L65 _public function_ `const UStruct* GetParametersStruct() const`
- L72 _private prototype_ `void EvaluateStateTransitions(const FSceneStateExecutionContext& InContext, FSceneStateMachineInstance& InInstance, const FSceneState& InActiveState) const;` — Called to evaluate the exit transitions from the active state
- L80 _private prototype_ `const FSceneStateTransition* EvaluateTransitions(TConstArrayView<FSceneStateTransition> InTransitions, const UE::SceneState::FTransitionEvaluationParams& InEvaluationParams) const;` — Evaluates whether the current context has any exit transitions satisfied. @param InTransitions the transitions to evaluate, already ordered from the highest priority to the lowest priority @param InEvaluationParams the parameters to use when evaluating a transition @return returns the highest priority transition satisfied, or null if no transitions were satisfied
- L88 _private prototype_ `const FSceneStateTransition* FollowTransition(const FSceneStateTransition& InTransition, const UE::SceneState::FTransitionEvaluationParams& InEvaluationParams) const;` — Follows the transition and returns a valid transition that would lead to a state or exit. @param InTransition the transition to follow @param InEvaluationParams the parameters to use when evaluating a transition @return returns the highest priority transition satisfied, or null if no transitions were satisfied
- L91 _private prototype_ `bool ApplyBindings(const FSceneStateExecutionContext& InContext, FSceneStateMachineInstance& InStateMachineInstance) const;` — Applies Bindings to the given State Machine Instance
- L94 _private prototype_ `void StopActiveState(const FSceneStateExecutionContext& InContext, FSceneStateMachineInstance& InInstance) const;` — Stops the current active state and resets the active time to 0
- L98 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Template Parameters to use to Instance the Scene State Machine Instance
- L102 _private member_ `FPropertyBindingIndex16 BindingsBatch;` — `UPROPERTY()` — Bindings Batch where this State Machine is target
- L106 _private member_ `FSceneStateRange StateRange;` — `UPROPERTY()` — Index and count of the states that belong to this state machine.
- L110 _private member_ `FSceneStateRange ConduitRange;` — `UPROPERTY()` — Index and count of the conduits that belong to this state machine.
- L117 _private member_ `uint16 EntryIndex = FSceneStateRange::InvalidIndex;` — `UPROPERTY()` — Relative Index of the entry state that the State Machine will start in AbsoluteEntryIndex = StateRange.Index (absolute) + EntryIndex (relative)

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateMachineInstance.h` (Public)


#### struct `FSceneStateMachineInstance`  
`struct FSceneStateMachineInstance`  
_L12-28_
- reflection: `USTRUCT()`
- desc: Instance data of a State Machine
- L18 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Instanced Parameters for the given State Machine
- L24 _public member_ `uint16 ActiveIndex = FSceneStateRange::InvalidIndex;` — Relative Index of the currently Active State AbsoluteActiveIndex = StateRange.Index (absolute) + ActiveIndex (relative)
- L27 _public member_ `UE::SceneState::EExecutionStatus Status = UE::SceneState::EExecutionStatus::NotStarted;` — Current status of the state machine instance

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateObject.h` (Public)


#### class `USceneStateObject`  
`class USceneStateObject : public UObject`  
_L35-124_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UObject`
- desc: Object instanced by USceneStateGeneratedClass. Holds the execution context (and instance data) that will be used to run the Scene State the USceneStateGeneratedClass holds. @see USceneStateGeneratedClass
- L40 _public prototype_ `USceneStateObject();`
- L43 _public prototype_ `FString GetContextName() const;` — Gets the context name of the scene state player
- L45 _public function_ `const USceneStateTemplateData* GetTemplateData() const`
- L52 _public prototype_ `UObject* GetContextObject() const;` — `UFUNCTION(BlueprintCallable, Category="State")` — Gets the context object of the scene state player
- L55 _public function_ `USceneStateEventStream* GetEventStream() const` — `UFUNCTION(BlueprintPure, Category="Events")`
- L62 _public prototype_ `bool IsActive() const;` — `UFUNCTION(BlueprintPure, Category="State")` — Returns true if the object has an active root state
- L65 _public prototype_ `void Setup();` — Called by the scene state player to setup this object and the root execution context
- L68 _public prototype_ `void Enter();` — Called by the scene state player to start execution of the root state
- L71 _public prototype_ `void Tick(float InDeltaSeconds);` — Called by the scene state player to start ticking the root state
- L74 _public prototype_ `void Exit();` — Called by the scene state player to stop the execution of the root state
- L77 _public prototype_ `void ReceiveEnter();` — `UFUNCTION(BlueprintImplementableEvent, DisplayName = "Enter", Category = "State Events")`
- L80 _public prototype_ `void ReceiveTick(float InDeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, DisplayName = "Tick", Category = "State Events")`
- L83 _public prototype_ `void ReceiveExit();` — `UFUNCTION(BlueprintImplementableEvent, DisplayName = "Exit", Category = "State Events")`
- L86 _public prototype_ `TSharedRef<UE::SceneState::FExecutionContextRegistry> GetContextRegistry() const;` — Gets the context registry owned by this object
- L90 _public prototype_ `UE_INTERNAL TSharedPtr<UE::SceneState::FDebugger> GetDebugger() const;` — Gets the currently attached debugger, if any
- L93 _public prototype_ `void SetDebugger(const TWeakPtr<UE::SceneState::FDebugger>& InDebuggerWeak);` — Attaches a new debugger, detaching the old one if any
- L97 _public prototype_ `virtual UWorld* GetWorld() const override final;`
- L98 _public prototype_ `virtual void BeginDestroy() override;`
- L103 _private prototype_ `const FSceneState* GetRootState() const;` — Resolves the root state from the template data, if any
- L107 _private member_ `TObjectPtr<const USceneStateTemplateData> TemplateData;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient, NonTransactional, meta=(NoBinding))` — Scene State template data to use for this object's execution.
- L111 _private member_ `TObjectPtr<USceneStateEventStream> EventStream;` — `UPROPERTY(Transient, Instanced, meta=(NoBinding))` — Runtime Event System keeping track of Active Events that have been added
- L115 _private member_ `FSceneStateExecutionContext RootExecutionContext;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient, NonTransactional, meta=(NoBinding))` — The top-level execution context of the Scene State
- L118 _private member_ `TSharedPtr<UE::SceneState::FExecutionContextRegistry> ContextRegistry;` — The registry containing all the execution contexts in this object
- L122 _private member_ `TWeakPtr<UE::SceneState::FDebugger> DebuggerWeak;` — Debugger attached to this object

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCENESTATE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStatePlayer.h` (Public)


#### class `USceneStatePlayer`  
`class USceneStatePlayer : public UObject`  
_L19-97_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Scene State Players is the layer between the Context Object and the rest of Scene State It instances a Scene State Object from a given class. These players exist to keep shared logic re-usable across multiple possible implementers
- L24 _public function_ `TSubclassOf<USceneStateObject> GetSceneStateClass() const`
- L30 _public prototype_ `void SetSceneStateClass(TSubclassOf<USceneStateObject> InSceneStateClass);` — Sets the class of the root state object. Destroying the existing one
- L32 _public function_ `USceneStateObject* GetSceneState() const`
- L38 _public prototype_ `FString GetContextName() const;` — Returns the context name for this player, for debugging purposes
- L41 _public prototype_ `UObject* GetContextObject() const;` — Returns the context object for this player
- L44 _public prototype_ `void Setup();` — Should be called prior to the start of the execution
- L47 _public prototype_ `void Begin();` — Should be called to start the execution of the scene state object
- L50 _public prototype_ `void Tick(float InDeltaTime);` — Should be called every tick during the execution of the scene state object
- L53 _public prototype_ `void End();` — Should be called to end the execution of the scene state object
- L57 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L61 _public function_ `static FName GetSceneStateClassName()`
- L66 _public function_ `static FName GetRootStateName()`
- L73 _protected function_ `virtual bool OnGetContextName(FString& OutContextName) const` — Returns the context name for this player
- L79 _protected function_ `virtual bool OnGetContextObject(UObject*& OutContextObject) const` — Returns the context object for this player
- L86 _protected member_ `TSubclassOf<USceneStateObject> SceneStateClass;` — `UPROPERTY(EditAnywhere, Category="Scene State", meta=(NoBinding, EditCondition="bEditableSceneStateClass", EditConditionHides, HideEditConditionToggle))` — Scene State class used to instantiate the Scene State
- L90 _protected member_ `TObjectPtr<USceneStateObject> RootState;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Scene State", meta=(AllowPrivateAccess="true", ShowInnerProperties))` — Root Scene State object that this Component will run
- L95 _protected member_ `bool bEditableSceneStateClass = true;` — `UPROPERTY()` — Whether the scene state class is editable in Details

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATE_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStatePropertyUtils.h` (Public)


#### struct `UE::SceneState::FResolvePropertyResult`  
`struct FResolvePropertyResult`  
_L15-21_
- L18 _public member_ `uint8* ValuePtr = nullptr;` — the resolved value address
- L20 _public member_ `const FSceneStateBindingResolvedReference* ResolvedReference = nullptr;` — the resolved property reference mapped to the value address (can differ from the resolved reference mapped to InPropertyReference in recursive scenarios)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L29 _prototype_ `bool ResolveProperty(const FSceneStateExecutionContext& InContext, const FSceneStatePropertyReference& InPropertyReference, FResolvePropertyResult& OutResult);` (scope `UE::SceneState`) — Resolves the given reference and execution context to the value address of the property, and keeps iterating if the source is a property reference too. @param InContext the execution context containing the binding collection and way to retrieve the data views @param InPropertyReference the property reference to resolve access for @param OutResult if successful, a result containing a valid resolved reference and a valid value address. @return whether the operation succeeded
- L32 _function_ `template<class T> T* ResolveProperty(const FSceneStateExecutionContext& InContext, const FSceneStatePropertyReference& InPropertyReference)` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateRange.h` (Public)


#### struct `FSceneStateRange`  
`struct FSceneStateRange`  
_L12-37_
- reflection: `USTRUCT()`
- L16 _public member_ `static constexpr uint16 InvalidIndex = std::numeric_limits<uint16>::max();`
- L19 _public prototype_ `static FSceneStateRange MakeBeginEndRange(uint16 InBegin, uint16 InEnd);` — Makes a range with the given begin and end range, where end is exclusive
- L21 _public function_ `uint16 GetLastIndex() const`
- L27 _public function_ `bool IsValid() const`
- L33 _public member_ `uint16 Index = FSceneStateRange::InvalidIndex;` — `UPROPERTY()`
- L36 _public member_ `uint16 Count = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATE_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateReentryGuard.h` (Public)


#### class `UE::SceneState::FReentryHandle`  
`class FReentryHandle`  
_L10-14_
- L13 _private member_ `mutable bool bValue = false;`

#### struct `UE::SceneState::FReentryGuard`  
`struct FReentryGuard`  
_L17-31_
- desc: Ensures no reentry in a given scope
- L19 _public prototype_ `explicit FReentryGuard(const FReentryHandle& InCurrent, const FSceneStateExecutionContext& InContext);`
- L21 _public prototype_ `~FReentryGuard();`
- L23 _public prototype_ `bool IsReentry() const;`
- L27 _private member_ `const FReentryHandle& Reference;` — Reference to the handle that is used to monitor reentry
- L30 _private member_ `FReentryHandle Original;` — Original value prior to this guard's construction. Used to restore the reference when this object destroys

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateSchema.h` (Public)


#### class `USceneStateSchema`  
`class USceneStateSchema : public UObject`  
_L17-57_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Determines the rules (e.g. allowed tasks) and provides context for a Scene State object type.
- L24 _public prototype_ `bool IsTaskStructAllowed(TSubScriptStructOf<FSceneStateTask> InTaskStruct) const;` — Determines whether the given task struct is allowed
- L27 _public prototype_ `bool IsTaskAssetAllowed(const FAssetData& InTaskAsset) const;` — Determines whether the given task asset (task blueprint) is allowed
- L31 _public prototype_ `TSubclassOf<UObject> GetContextObjectClass() const;` — Return the context object class supported
- L36 _protected function_ `virtual bool OnIsTaskStructAllowed(TSubScriptStructOf<FSceneStateTask> InTaskStruct) const` — Determines whether a given task struct is allowed
- L42 _protected function_ `virtual bool OnIsTaskAssetAllowed(const FAssetData& InTaskAsset) const` — Determines whether the given task asset (task blueprint) is allowed
- L49 _protected function_ `virtual TSubclassOf<UObject> OnGetContextObjectClass() const` — Return the context object class supported. Called only once to keep the context object class constant throughout the schema.
- L56 _private member_ `mutable TSubclassOf<UObject> ContextObjectClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateTemplateData.h` (Public)


#### class `USceneStateTemplateData`  
`class USceneStateTemplateData : public UObject`  
_L45-201_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Holds all the data about States, State Machines, Tasks, etc. All this data is immutable in execution, and as such, it is not instanced to the Scene State Object instances. @see FSceneStateExecutionContext
- L51 _public prototype_ `const FSceneState* GetRootState() const;` — Gets the state that contains all top-level state machines
- L54 _public prototype_ `const FSceneStateMachine* FindStateMachine(const FGuid& InStateMachineId) const;` — Finds the state machine for a given state machine guid
- L57 _public prototype_ `const UStruct* FindDataStruct(const UClass* InOwnerClass, const FSceneStateBindingDataHandle& InDataHandle);` — Finds the struct type for the given data handle
- L60 _public prototype_ `void ResolveBindings(const UClass* InOwnerClass);` — Patches bindings and resolves the binding paths for the owning binding collection
- L63 _public prototype_ `void Link(const UClass* InOwnerClass);` — Called at link time to cache the properties and functions to use (e.g. in transitions or conduits)
- L66 _public prototype_ `void Reset();` — Resets all the elements that get compiled for this generated class (e.g. Tasks, State Machines, etc)
- L70 _public prototype_ `const FSceneState* FindStateFromNode(FObjectKey InStateNode) const;` — Finds the mapped compiled state for a given state node
- L73 _public prototype_ `const FSceneStateTask* FindTaskFromNode(FObjectKey InTaskNode) const;` — Finds the mapped compiled task for a given task node
- L76 _public prototype_ `void ForEachStateInstance(const TSharedRef<UE::SceneState::FExecutionContextRegistry>& InContextRegistry , FObjectKey InStateNode , TFunctionRef<void(const FSceneStateInstance&)> InFunctor) const;` — `UE_DEPRECATED(5.8, "ForEachStateInstance deprecated. No longer supported.")`
- L86 _public prototype_ `UE_INTERNAL void ForEachTaskStatus(const TSharedRef<UE::SceneState::FExecutionContextRegistry>& InContextRegistry , uint16 InTaskIndex , TFunctionRef<void(UE::SceneState::EExecutionStatus)> InFunctor) const;` — For a given root state and task index retrieves the mapped task status @param InContextRegistry the registry containing all the execution contexts @param InTaskIndex the task index to look for @param InFunctor the functor to run for each task status
- L91 _public prototype_ `void ForEachTaskInstance(const TSharedRef<UE::SceneState::FExecutionContextRegistry>& InContextRegistry , FObjectKey InTaskNode , TFunctionRef<void(const FSceneStateTaskInstance&)> InFunctor) const;` — `UE_DEPRECATED(5.8, "ForEachTaskInstance deprecated. No longer supported.")`
- L95 _public prototype_ `void OnObjectsReinstanced(const UClass* InOwnerClass, const TMap<UObject*, UObject*>& InReplacementMap);`
- L96 _public prototype_ `void OnStructsReinstanced(const UClass* InOwnerClass, const UUserDefinedStruct& InStruct);`
- L101 _public member_ `FSceneStateBindingCollection BindingCollection;` — `UPROPERTY()` — Container for all the bindings
- L105 _public member_ `uint16 RootStateIndex = FSceneStateRange::InvalidIndex;` — `UPROPERTY()` — Index to the state that contains all top-level state machines
- L109 _public member_ `TArray<FSceneState> States;` — `UPROPERTY()` — Holds all the compiled states including nested states
- L113 _public member_ `FInstancedStructContainer Tasks;` — `UPROPERTY()` — Holds all the compiled tasks (including tasks from nested states) in a contiguous block of memory
- L117 _public member_ `TArray<uint16> TaskPrerequisites;` — `UPROPERTY()` — Array of the task prerequisites in their relative index. Each task has a unique range indicating their pre-requisites
- L121 _public member_ `FInstancedStructContainer TaskInstances;` — `UPROPERTY()` — Templates used to instantiate the Task Instances
- L125 _public member_ `FInstancedStructContainer Functions;` — `UPROPERTY()` — Holds all the compiled functions (including from nested sources) in a contiguous block of memory
- L129 _public member_ `FInstancedStructContainer FunctionInstances;` — `UPROPERTY()` — Templates used to instantiate the function data
- L133 _public member_ `TArray<FSceneStateEventHandler> EventHandlers;` — `UPROPERTY()` — Holds all the compiled event handlers (including from nested sources) contiguously
- L137 _public member_ `TArray<FSceneStateTransition> Transitions;` — `UPROPERTY()` — Holds all the exit transitions (including nested sources) contiguously
- L141 _public member_ `TArray<FSceneStateTransitionLink> TransitionLinks;` — `UPROPERTY()` — Compiled transition information only used in Link time
- L145 _public member_ `TMap<uint16, FInstancedPropertyBag> TransitionParameters;` — `UPROPERTY()` — Map of the Transition Index (absolute) to the template transition parameters map for evaluation function call.
- L149 _public member_ `TArray<FSceneStateConduit> Conduits;` — `UPROPERTY()` — All the compiled conduits
- L153 _public member_ `TArray<FSceneStateConduitLink> ConduitLinks;` — `UPROPERTY()` — Compiled conduit information used only in Link time
- L156 _public member_ `TArray<FSceneStateMachine> StateMachines;` — `UPROPERTY()`
- L160 _public member_ `TMap<FGuid, uint16> StateMachineIdToIndex;` — `UPROPERTY()` — Map of the state machine parameters id to the index in the state machine array
- L164 _public member_ `TMap<FGuid, uint16> StateParameterIdToIndex;` — `UPROPERTY()` — Map of the state parameters id to the index in the state array
- L169 _public member_ `TArray<FSceneStateMetadata> StateMetadata;` — `UPROPERTY()` — Holds all the state editor-only metadata. This array matches in index with the states array.
- L173 _public member_ `TArray<FSceneStateTaskMetadata> TaskMetadata;` — `UPROPERTY()` — Holds all the task editor-only metadata. This array matches in index with the tasks array.
- L177 _public member_ `TArray<FSceneStateFunctionMetadata> FunctionMetadata;` — `UPROPERTY()` — Holds all the function editor-only metadata. This array matches in index with the functions.
- L181 _public member_ `TArray<FSceneStateTransitionMetadata> TransitionMetadata;` — `UPROPERTY()` — Holds all the transition editor-only metadata. This array matches in index with the transitions array.
- L187 _public member_ `TMap<FObjectKey, uint16> StateNodeToIndex;` — Map of a State Node to its State Index. Set after a compilation occurs.
- L193 _public member_ `TMap<FObjectKey, uint16> StateMachineGraphToIndex;` — Map of a State Machine Graph to its State Machine Index. Set after a compilation occurs.
- L199 _public member_ `TMap<FObjectKey, uint16> TaskNodeToIndex;` — Map of a Task Node to its Task Index. Set after a compilation occurs.

#### Free symbols / members of external scopes

- L28 _macro_ `#define UE_API SCENESTATE_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateUtils.h` (Public)


#### struct `UE::SceneState::FApplyBatchParams`  
`struct FApplyBatchParams`  
_L50-56_
- L53 _public member_ `uint16 BindingsBatch;` — Batch of the bindings to apply
- L55 _public member_ `FPropertyBindingDataView TargetDataView;` — Target Data to copy the source data to

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SceneState` (scope `UE`)
- L31 _function_ `template<typename InKeyType, typename InIndexType = uint16> void ToAbsoluteIndexMap(TMap<InKeyType, InIndexType>& InOutMap, InIndexType InIndexOffset)` (scope `UE::SceneState`) — Converts a map of keys to relative indices to a map of keys to absolute indices @param InOutMap the map to convert @param InIndexOffset the index to add to these relative indices to transform them to absolute
- L39 _prototype_ `TArray<FStructView> GetStructViews(FInstancedStructContainer& InStructContainer, FSceneStateRange InRange);` (scope `UE::SceneState`)
- L41 _prototype_ `TArray<FStructView> GetStructViews(FInstancedStructContainer& InStructContainer);` (scope `UE::SceneState`)
- L43 _prototype_ `TArray<FConstStructView> GetConstStructViews(const FInstancedStructContainer& InStructContainer, FSceneStateRange InRange);` (scope `UE::SceneState`)
- L45 _prototype_ `TArray<FConstStructView> GetConstStructViews(const FInstancedStructContainer& InStructContainer);` (scope `UE::SceneState`)
- L48 _prototype_ `bool IsValidRange(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd);` (scope `UE::SceneState`) — Determines whether the given begin and end forms a valid range
- L58 _prototype_ `bool ApplyBatch(const FSceneStateExecutionContext& InContext, const FApplyBatchParams& InParams);` (scope `UE::SceneState`) — Applies a given binding batch to a target view within an execution context
- L61 _prototype_ `void* ResolveVisitedPath(const UScriptStruct* InRootObject, void* InRootData, const FPropertyVisitorPath& InPath);` (scope `UE::SceneState`) — `UE_DEPRECATED(5.8, "Use PropertyVisitorHelpers::ResolveVisitedPath instead")`
- L67 _prototype_ `void DiscardObject(UObject* InObjectToDiscard);` (scope `UE::SceneState`) — Discards a given object by changing its outer to transient package and adding a prefix to it while also ensuring uniqueness @param InObjectToDiscard the object to discard
- L77 _prototype_ `UObject* DiscardObject(UObject* InOuter , const TCHAR* InObjectName , TFunctionRef<void(UObject*)> InOnPreDiscardOldObject = [](UObject*){});` (scope `UE::SceneState`) — Discards an object with a given name in the given outer, by renaming the outer to the transient package and adding a prefix to it while also ensuring uniqueness @param InOuter outer of the object. Must be valid. @param InObjectName name to use. Must match InOutObject's name if not null @param InOnPreDiscardOldObject callback for when the old object is about to be trashed @return the object that was discarded, or null if none was found
- L79 _function_ `, TFunctionRef<void(UObject*)> InOnPreDiscardOldObject = [](UObject*)` (scope `UE::SceneState`)
- L91 _prototype_ `bool ReplaceObject(UObject*& InOutObject , UObject* InOuter , UClass* InClass , const TCHAR* InObjectName , const TCHAR* InContextName = nullptr , TFunctionRef<void(UObject*)> InOnPreDiscardOldObject = [](UObject*){});` (scope `UE::SceneState`) — Replaces a given Object with a new object with the same name but different class @param InOutObject object to replace. Can come in as null @param InOuter outer of the object. Must be valid. @param InClass new class of the new object that will replace the older one @param InObjectName name to use. Must match InOutObject's name if not null @param InContextName context for debugging purposes @param InOnPreDiscardOldObject callback for when the old object is about to be trashed @return true if the operation took place, false otherwise
- L99 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L102 _prototype_ `bool StructHasMetaData(const UStruct* InStruct, FName InMetaData, bool bInIncludeSuperStructs);` (scope `UE::SceneState::Editor`) — Returns true if the struct or its super structs contains the given metadata.
- L105 _prototype_ `bool StructHasAnyMetaData(const UStruct* InStruct, TConstArrayView<FName> InMetaData, bool bInIncludeSuperStructs);` (scope `UE::SceneState::Editor`) — Returns true if the struct or its super structs contains any of the given metadata.

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/SceneStateVersion.h` (Public)


#### struct `UE::SceneState::FVersion`  
`struct FVersion`  
_L13-32_
- desc: Describes the versions of scene state
- L16 _private prototype_ `FVersion() = delete;`
- L31 _public member_ `const static FGuid Guid;`

#### enum `UE::SceneState::FVersion::Type`  
`enum Type : uint8`  
_L19-29_
- L21 _public enumerator_ `PreVersioning = 0`
- L24 _public enumerator_ `Schema` — Added schemas to set rules for scene state blueprints
- L27 _public enumerator_ `VersionPlusOne`
- L28 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENESTATE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateBlueprintableTask.h` (Public)


#### class `USceneStateBlueprintableTask`  
`class USceneStateBlueprintableTask : public UObject, public ISceneStateEventHandlerProvider`  
_L25-78_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType, AutoExpandCategories=("Task Settings"), EditInlineNew)`
- inherits: `UObject,ISceneStateEventHandlerProvider`
- desc: Base class for Blueprint Tasks. Following the design of blueprints, unlike C++ Tasks that have Logic and Instance Data separated, Blueprint Tasks holds the logic and mutable instance data together and so get allocated when the task starts. @see FSceneStateBlueprintableTaskWrapper
- L34 _public prototype_ `void ReceiveStart();` — `UFUNCTION(BlueprintImplementableEvent, Category="Task")` — Called once when the Task starts
- L42 _public prototype_ `void ReceiveTick(float InDeltaSeconds);` — `UFUNCTION(BlueprintImplementableEvent, Category="Task")` — Called every frame after the Task has started Must have bCanTick set to true @see USceneStateTask::CanTick
- L46 _public prototype_ `void ReceiveStop(ESceneStateTaskStopReason InStopReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Task")` — Called once when the Task ends
- L50 _public prototype_ `USceneStateObject* GetRootState() const;` — `UFUNCTION(BlueprintCallable, Category="Task")` — Gets the scene state object that owns this blueprint task
- L53 _public prototype_ `const FSceneStateExecutionContext& GetExecutionContext() const;` — Gets the execution context of the task
- L57 _public prototype_ `UObject* GetContextObject() const;` — `UFUNCTION(BlueprintCallable, Category="Task")` — Gets the context object of the scene state object
- L61 _public prototype_ `USceneStateEventStream* GetEventStream() const;` — `UFUNCTION(BlueprintCallable, Category="Task")` — Gets the scene state object's event stream
- L65 _public prototype_ `void FinishTask();` — `UFUNCTION(BlueprintCallable, Category="Task")` — Called to indicate the task has completed
- L68 _public prototype_ `virtual bool FindEventHandlerId(const FSceneStateEventSchemaHandle& InEventSchemaHandle, FGuid& OutHandlerId) const;`
- L72 _public prototype_ `virtual UWorld* GetWorld() const override final;`
- L77 _private member_ `UE::SceneState::FTaskExecutionContext TaskExecutionContext;` — Context to retrieve the underlying Task/Task Instance for this blueprint task

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateBlueprintableTaskWrapper.h` (Public)


#### struct `FSceneStateBlueprintableTaskInstance`  
`struct FSceneStateBlueprintableTaskInstance : public FSceneStateTaskInstance`  
_L15-22_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L21 _public member_ `TObjectPtr<USceneStateBlueprintableTask> Task;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Scene State")` — Task Blueprint Instance allocated everytime the Blueprintable Task Wrapper task starts

#### struct `FSceneStateBlueprintableTaskWrapper`  
`struct FSceneStateBlueprintableTaskWrapper : public FSceneStateTask`  
_L31-61_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FSceneStateTask`
- desc: Task Wrapper for Blueprint Tasks. Forwards the task start, tick and stop to the Blueprint Task held in its Task Instance struct @see FSceneStateBlueprintableTaskInstance @see USceneStateBlueprintableTask
- L35 _public typedef_ `using FInstanceDataType = FSceneStateBlueprintableTaskInstance;`
- L37 _public prototype_ `FSceneStateBlueprintableTaskWrapper();`
- L39 _public prototype_ `bool SetTaskClass(TSubclassOf<USceneStateBlueprintableTask> InTaskClass);`
- L41 _public function_ `TSubclassOf<USceneStateBlueprintableTask> GetTaskClass() const`
- L49 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L50 _protected prototype_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const override;`
- L52 _protected prototype_ `virtual void OnSetup(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L53 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L54 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const override;`
- L55 _protected prototype_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const override;`
- L60 _private member_ `TSubclassOf<USceneStateBlueprintableTask> TaskClass;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateMachineTask.h` (Public)


#### struct `FSceneStateMachineTaskInstance`  
`struct FSceneStateMachineTaskInstance : public FSceneStateTaskInstance`  
_L15-36_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L21 _public member_ `FSceneStateExecutionContext ExecutionContext;` — `UPROPERTY(Transient, meta=(NoBinding))` — Execution context created and owned by this Task / Task Instance
- L25 _public member_ `FGuid TargetId;` — `UPROPERTY(EditAnywhere, Category="State Machine", meta=(NoBinding))` — Id of the Target State Machine Parameters to copy our Parameters to
- L30 _public member_ `FGuid ParametersId;` — `UPROPERTY(VisibleAnywhere, Category="State Machine", meta=(NoBinding))` — Identifier for the Parameters this Instance owns
- L35 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category="State Machine", meta=(FixedLayout))` — Parameters mirroring the Target State Machine

#### struct `FSceneStateMachineTask`  
`struct FSceneStateMachineTask : public FSceneStateTask`  
_L40-64_
- reflection: `USTRUCT(DisplayName="Run State Machine", Category="Core", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Task that runs a local state machine
- L44 _public typedef_ `using FInstanceDataType = FSceneStateMachineTaskInstance;`
- L46 _public prototype_ `FSceneStateMachineTask();`
- L51 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L52 _protected prototype_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const override;`
- L54 _protected prototype_ `virtual const FSceneStateTaskBindingExtension* OnGetBindingExtension() const override;`
- L55 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L56 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const override;`
- L57 _protected prototype_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const override;`
- L60 _protected prototype_ `bool IsStateMachineFinished(const FSceneStateExecutionContext& InContext, const FSceneStateMachine& InStateMachine) const;`
- L63 _protected member_ `FSceneStateMachineTaskBinding Binding;` — `UPROPERTY()`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateMachineTaskBinding.h` (Public)


#### struct `FSceneStateMachineTaskBinding`  
`struct FSceneStateMachineTaskBinding : public FSceneStateTaskBindingExtension`  
_L15-39_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskBindingExtension`
- desc: Binding Extension for the State Machine Task. Allows the State Machine Parameters to be discoverable as a binding desc
- L19 _public typedef_ `using FInstanceDataType = FSceneStateMachineTaskInstance;`
- L22 _public member_ `static constexpr uint16 PARAMETERS_DATA_INDEX = 0;` — Data View Indices
- L27 _protected prototype_ `virtual void VisitBindingDescs(FStructView InTaskInstance, TFunctionRef<void(const UE::SceneState::FTaskBindingDesc&)> InFunctor) const override;`
- L28 _protected prototype_ `virtual void SetBindingBatch(uint16 InDataIndex, uint16 InBatchIndex) override;`
- L29 _protected prototype_ `virtual bool FindDataById(FStructView InTaskInstance, const FGuid& InStructId, FStructView& OutDataView, uint16& OutDataIndex) const override;`
- L31 _protected prototype_ `virtual bool FindDataByIndex(FStructView InTaskInstance, uint16 InDataIndex, FStructView& OutDataView) const override;`
- L32 _protected prototype_ `virtual void VisitBindingBatches(FStructView InTaskInstance, TFunctionRef<void(uint16, FStructView)> InFunctor) const override;`
- L38 _private member_ `uint16 ParametersBatchIndex = std::numeric_limits<uint16>::max();` — `UPROPERTY()` — Index to the binding batch for the parameters property bag

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStatePlayerTask.h` (Public)


#### struct `FSceneStatePlayerTaskInstance`  
`struct FSceneStatePlayerTaskInstance : public FSceneStateTaskInstance`  
_L13-19_
- reflection: `USTRUCT()`
- inherits: `FSceneStateTaskInstance`
- L18 _public member_ `TObjectPtr<USceneStatePlayer> Player;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Scene State")`

#### struct `FSceneStatePlayerTask`  
`struct FSceneStatePlayerTask : public FSceneStateTask`  
_L23-42_
- reflection: `USTRUCT(DisplayName="Run Player", Category="Core", meta=(CoreTask))`
- inherits: `FSceneStateTask`
- desc: Task that runs a Scene State Object through a Player
- L27 _public typedef_ `using FInstanceDataType = FSceneStatePlayerTaskInstance;`
- L29 _public prototype_ `FSceneStatePlayerTask();`
- L34 _protected prototype_ `virtual const UScriptStruct* OnGetTaskInstanceType() const override;`
- L35 _protected prototype_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const override;`
- L37 _protected prototype_ `virtual void OnSetup(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L38 _protected prototype_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const override;`
- L39 _protected prototype_ `virtual void OnTick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const override;`
- L40 _protected prototype_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTask.h` (Public)


#### struct `FSceneStateTask`  
`struct FSceneStateTask`  
_L39-233_
- reflection: `USTRUCT(meta=(Hidden))`
- desc: Base class for Tasks. Tasks are immutable in execution time, and so are meant to only hold logic and template read-only data. Each Task has a Task Instance Type that is allocated and used for instance data that the task can then mutate. @see FSceneStateTaskInstance @see SceneStateTaskMetadata.h for information about metadata that can be used with Tasks
- L43 _public prototype_ `virtual ~FSceneStateTask() = default;`
- L50 _public prototype_ `const UScriptStruct* GetTaskInstanceType() const;` — Called in-editor to get the task instance type @return the task instance struct. Must derive from FSceneStateTaskInstance
- L56 _public prototype_ `bool SupportsSchema(const USceneStateSchema* InSchema) const;` — Determines whether the given schema is supported by this task This is called only when the task struct contains the 'WithSupportsSchema' metadata.
- L63 _public prototype_ `void BuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const;` — Called to init properties (e.g. Guids) or instances objects within the task instance @param InOuter the outer to use for instanced objects @param InTaskInstance the task instance to build
- L70 _public prototype_ `void PostEditChange(UE::SceneState::FTaskEditChange& InEditChange, FStructView InTaskInstance);` — Called when a property within a task or task instance has changed @param InEditChange the edit change information (property changed event, outer) @param InTaskInstance the task instance paired with the task
- L74 _public prototype_ `const FSceneStateTaskBindingExtension* GetBindingExtension() const;` — Called to get the optional Binding Extension for a Task
- L77 _public prototype_ `FStructView FindTaskInstance(const FSceneStateExecutionContext& InContext) const;` — `UE_DEPRECATED(5.8, "FindTaskInstance is deprecated. Use the task instance provided by the task's virtual method ")`
- L83 _public prototype_ `void Setup(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const;` — Called when the State holding the Task first starts. This is called for all tasks held by the state even if these tasks end up not running, or run at a later time.
- L89 _public prototype_ `void Start(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const;` — Called once the State processes that the Task has all its prerequisites met. Applies and property bindings to the task and calls OnStart().
- L95 _public prototype_ `void Tick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const;` — Called by the State each Tick. OnTick() gets called if the Task is running and set to Tickable (see TaskFlags)
- L101 _public prototype_ `void Stop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const;` — Called to Stop the Task, because it either finished or was forcibly stopped by the state @see ESceneStateTaskStopReason
- L104 _public prototype_ `void Finish(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const;` — Calls Stop with stop reason being that the task has finished
- L106 _public function_ `uint16 GetParentStateIndex() const`
- L111 _public function_ `uint16 GetTaskIndex() const`
- L116 _public function_ `FSceneStateRange GetPrerequisiteRange() const`
- L122 _protected prototype_ `void SetFlags(ESceneStateTaskFlags InFlags);`
- L124 _protected prototype_ `void ClearFlags(ESceneStateTaskFlags InFlags);`
- L132 _protected function_ `virtual const UScriptStruct* OnGetTaskInstanceType() const` — Called in-editor to get the task instance type @see GetTaskInstanceType @return the task instance struct. Must derive from FSceneStateTaskInstance
- L141 _protected function_ `virtual bool OnSupportsSchema(TNotNull<const USceneStateSchema*> InSchema) const` — Determines whether the given schema is supported by this task This is called only when the task struct contains the 'WithSupportsSchema' metadata.
- L150 _protected function_ `virtual void OnBuildTaskInstance(UObject* InOuter, FStructView InTaskInstance) const` — Called to init properties (e.g. Guids) or instances objects within the task instance @see BuildTaskInstance
- L158 _protected function_ `virtual void OnPostTaskEditChange(UE::SceneState::FTaskEditChange& InEditChange, FStructView InTaskInstance)` — Called when a property within a task has changed @see PostEditChange
- L163 _protected function_ `virtual void OnPostEditChange(UE::SceneState::FTaskEditChange& InEditChange, FStructView InTaskInstance) const final` — DEPRECATED 5.8, "Use OnPostTaskEditChange() that is non-const instead
- L172 _protected function_ `virtual const FSceneStateTaskBindingExtension* OnGetBindingExtension() const` — Called to get the optional Binding Extension for a Task @see GetBindingExtension
- L181 _protected function_ `virtual void OnSetup(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const` — Called when the State holding the Task first starts. This is called for all tasks held by the state even if these tasks end up not running, or run at a later time.
- L186 _protected function_ `virtual void OnStart(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const` — Called once the State processes that the Task has all its prerequisites met.
- L191 _protected function_ `virtual void OnTick(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, float InDeltaSeconds) const` — Called by the State each Tick if the Task is set to Tick via its TaskFlags
- L199 _protected function_ `virtual void OnStop(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance, ESceneStateTaskStopReason InStopReason) const` — Called when the Task has finished or forcibly stopped by the state @see ESceneStateTaskStopReason
- L205 _private prototype_ `bool IsTaskStatus(const FSceneStateExecutionContext& InContext, UE::SceneState::EExecutionStatus InExpectedStatus) const;` — Returns true if the current task status on the given context matches the expected status
- L208 _private prototype_ `bool ApplyBindings(const FSceneStateExecutionContext& InContext, FStructView InTaskInstance) const;` — Applies Bindings to the given Task Instance
- L212 _private member_ `FPropertyBindingIndex16 BindingsBatch;` — `UPROPERTY()` — Bindings Batch where this Task is target
- L216 _private member_ `uint16 ParentStateIndex = FSceneStateRange::InvalidIndex;` — `UPROPERTY()` — Absolute Index to the State owning this Task
- L220 _private member_ `uint16 TaskIndex = FSceneStateRange::InvalidIndex;` — `UPROPERTY()` — Absolute Index of this Task
- L224 _private member_ `FSceneStateRange PrerequisiteRange;` — `UPROPERTY()` — Absolute Range to the relative indices of the tasks that need to finish before this task can be executed
- L227 _private member_ `ESceneStateTaskFlags TaskFlags = ESceneStateTaskFlags::None;` — Additional information about this task (e.g. if it ticks, whether it extends bindings, etc.)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SceneState` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskBindingExtension.h` (Public)


#### struct `UE::SceneState::FTaskBindingDesc`  
`struct FTaskBindingDesc`  
_L18-31_
- L21 _public member_ `FGuid Id;` — Unique identifier of the struct at Editor Time
- L24 _public member_ `FName Name;` — Name of the struct (used for debugging, logging, cosmetic).
- L27 _public member_ `FPropertyBindingDataView DataView;` — Template data view to the struct or class data
- L30 _public member_ `uint16 DataIndex = FSceneStateRange::InvalidIndex;` — Unique Index for this Custom Desc to identify at Runtime

#### struct `FSceneStateTaskBindingExtension`  
`struct FSceneStateTaskBindingExtension`  
_L38-95_
- reflection: `USTRUCT()`
- desc: Extension to allow custom bindings for a task.
- L48 _public function_ `virtual void VisitBindingDescs(FStructView InTaskInstance, TFunctionRef<void(const UE::SceneState::FTaskBindingDesc&)> InFunctor) const` — Visits all binding descs available @param InTaskInstance the task instance with binding structs @param InFunctor the functor to execute for every available binding desc
- L57 _public function_ `virtual void SetBindingBatch(uint16 InDataIndex, uint16 InBindingsBatchIndex)` — Sets the binding batch for the given data index @param InDataIndex index to the data that the binding batch links to @param InBindingsBatchIndex index to the binding batch that compiled
- L69 _public function_ `virtual bool FindDataById(FStructView InTaskInstance, const FGuid& InStructId, FStructView& OutDataView, uint16& OutDataIndex) const` — Finds the data view that matches the struct id @param InTaskInstance the task instance to look into @param InStructId the struct id to look for @param OutDataView the returned data view, if found @param OutDataIndex index to the returned data view, if found @return true if the data was found
- L82 _public function_ `virtual bool FindDataByIndex(FStructView InTaskInstance, uint16 InDataIndex, FStructView& OutDataView) const` — Finds the data view that maps to the given data index @param InTaskInstance the task instance to look into @param InDataIndex the index mapped to the data view to look for @param OutDataView the returned data view, if found @return true if the data was found
- L92 _public function_ `virtual void VisitBindingBatches(FStructView InTaskInstance, TFunctionRef<void(uint16, FStructView)> InFunctor) const` — Visits all the data views and their paired binding batch index @param InTaskInstance the task instance to look into @param InFunctor the functor to execute for every data view binding batch index pair

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskEditChange.h` (Public)


#### struct `UE::SceneState::FTaskEditChange`  
`struct FTaskEditChange : FPropertyChangedEvent`  
_L16-30_
- inherits: `FPropertyChangedEvent`
- desc: Describes an Edit change for a task or task instance
- L18 _public prototype_ `FTaskEditChange();`
- L21 _public prototype_ `bool IsTaskChange() const;` — Returns true if the FSceneStateTask changed
- L24 _public prototype_ `bool IsTaskInstanceChange() const;` — Returns true if the FSceneStateTaskInstance changed
- L27 _public member_ `UObject* Outer = nullptr;` — Owning object of the task
- L29 _public member_ `ETaskObjectType ChangedObject = ETaskObjectType::None;` — The object that was changed: whether it was the task or the task instance

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskExecutionContext.h` (Public)


#### struct `UE::SceneState::FTaskExecutionContext`  
`struct FTaskExecutionContext`  
_L29-68_
- desc: Helper struct that can be passed over by copy in lambda captures, delegates while enabling functionality like safely accessing a Task, Task Instance, and Finishing a Task. It returns the Task and Task Instance only if the saved Instance Id matches the current Instance Id for the Task.
- L31 _public prototype_ `FTaskExecutionContext();`
- L33 _public prototype_ `explicit FTaskExecutionContext(const FSceneStateTask& InTask, const FSceneStateExecutionContext& InContext);`
- L36 _public prototype_ `const FSceneStateExecutionContext* GetExecutionContext() const;` — Resolves the execution context if it still exists
- L39 _public prototype_ `FConstStructView GetTask() const;` — Retrieves the FSceneStateTask view for this context, if the task instance this context got created for is still valid. An invalid view is returned otherwise
- L42 _public prototype_ `FStructView GetTaskInstance() const;` — Retrieves the FSceneStateTaskInstance view for this context, if the task instance this context got created for is still valid. An invalid view is returned otherwise
- L45 _public prototype_ `void FinishTask() const;` — Helper function to Finish the Task / Task Instance for this context if these are still valid
- L48 _private prototype_ `FString GetDebugString() const;`
- L51 _private member_ `FExecutionContextHandle ContextHandle;` — Handle to the context within the saved registry
- L54 _private member_ `TWeakPtr<const FExecutionContextRegistry> ContextRegistryWeak;` — Registry used to find the context
- L57 _private member_ `uint16 TaskIndex;` — Absolute index to the task
- L60 _private member_ `uint16 StateIndex;` — Absolute index to the task's parent state
- L67 _private member_ `uint16 StateInstanceId;` — Id assigned to the state instance to distinguish it from a different instance (within the same context) with the same state index. This can happen if this context is held past its task instance (e.g. captured from a deferred lambda) and there's an active new instance for the same state within the same context.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATE_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SceneState` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskGeneratedClass.h` (Public)


#### class `USceneStateTaskGeneratedClass`  
`class USceneStateTaskGeneratedClass : public UBlueprintGeneratedClass`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- desc: Generated class for Scene State Blueprintable Tasks

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskInstance.h` (Public)


#### struct `FSceneStateTaskInstance`  
`struct FSceneStateTaskInstance`  
_L10-19_
- reflection: `USTRUCT()`
- desc: Represents the Instance Data of a Task
- L15 _public function_ `UE::SceneState::EExecutionStatus GetStatus() const` — `UE_DEPRECATED(5.8, "Status has been moved outside of task instance and now managed by the execution context ")`

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Tasks/SceneStateTaskMetadata.h` (Public)


#### struct `FSceneStateTaskMetadata`  
`struct FSceneStateTaskMetadata`  
_L42-51_
- reflection: `USTRUCT()`
- desc: Metadata information about the Task. Available only in editor
- L49 _public member_ `FGuid TaskId;` — `UPROPERTY()` — Id used for the Property Binding System to identify a Task

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L11 _variable_ `const FLazyName MD_Hidden(TEXT("Hidd` (scope `UE::SceneState::Editor`) — The task should not appear in the list of available tasks (e.g. because it's a base task struct)
- L17 _variable_ `const FLazyName MD_CoreTask(TEXT("Core` (scope `UE::SceneState::Editor`) — The task is deemed as 'Core'. These are tasks that should be allowed in most schemas. Derived tasks will NOT be recognized as 'CoreTask' unless they also specify this metadata.
- L23 _variable_ `const FLazyName MD_UtilityTask(TEXT("Util` (scope `UE::SceneState::Editor`) — The task is utility that can be useful for most schemas. All the non-core tasks that come with the Scene State plugin will be marked with this metadata. Derived tasks will NOT be recognized as 'UtilityTask' unless they also specify this metadata.
- L30 _variable_ `const FLazyName MD_RequiresContextWorld(TEXT("Requ` (scope `UE::SceneState::Editor`) — The task requires the context object to implement GetWorld(). This is just a convenience metadata to avoid having to call SupportsSchema. Derived tasks will also be treated as requiring a context world.
- L36 _variable_ `const FLazyName MD_WithSupportsSchema(TEXT("With` (scope `UE::SceneState::Editor`) — The task implements OnSupportsSchema function. Only tasks with this metadata will have their 'SupportsSchema' function called. Derived tasks will also have this function called.

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransition.h` (Public)


#### struct `FSceneStateTransition`  
`struct FSceneStateTransition`  
_L40-98_
- reflection: `USTRUCT()`
- desc: Holds the exit transition conditions and information from its owner state to a target. @see FSceneStateTransitionTarget
- L45 _public prototype_ `void Link(const FSceneStateTransitionLink& InTransitionLink, TNotNull<const UClass*> InOwnerClass);` — Called when the Owner Class is linking to cache the Event function and Result property
- L48 _public prototype_ `void Setup(const FSceneStateExecutionContext& InContext) const;` — Called when the State has entered. Allocates and initializes the transition instance
- L51 _public prototype_ `bool Evaluate(const UE::SceneState::FTransitionEvaluationParams& InParams) const;` — Called to evaluate this transition. Returns true if the transition should take place
- L54 _public prototype_ `void Exit(const FSceneStateExecutionContext& InContext) const;` — Called when the State has exited. Cleans up the transition instance
- L56 _public function_ `FSceneStateTransitionTarget GetTarget() const`
- L63 _private prototype_ `bool ApplyBindings(const FSceneStateExecutionContext& InContext, FSceneStateTransitionInstance& InInstance) const;` — Called to apply the transition parameter bindings to be optionally used by the transition evaluation event
- L66 _private prototype_ `bool ContainsAllRequiredEvents(const UE::SceneState::FTransitionEvaluationParams& InParams) const;` — Evaluates whether all the target state's required events are present
- L69 _private prototype_ `bool ProcessEvaluationEvent(const UE::SceneState::FTransitionEvaluationParams& InParams) const;` — Calls the evaluation event (can return early if optimized away via the evaluation flags)
- L72 _private prototype_ `const FSceneStateConduit* FindConduitTarget(const FSceneStateExecutionContext& InContext) const;` — If the transition target is a conduit, returns the pointer to such conduit
- L76 _private member_ `FPropertyBindingIndex16 BindingsBatch;` — `UPROPERTY()` — Bindings Batch where this Transition is target
- L83 _private member_ `FSceneStateTransitionTarget Target;` — `UPROPERTY()` — Target to transition to if this transition evaluates to true This is used to set the Active State Index if the type is state (which is relative to the state machine states start index) in a State Machine
- L87 _private member_ `ESceneStateTransitionEvaluationFlags EvaluationFlags = ESceneStateTransitionEvaluationFlags::None;` — `UPROPERTY()` — Transition flags indicating how a transition should be evaluated
- L91 _private member_ `TObjectPtr<UFunction> EvaluationEvent;` — `UPROPERTY(Transient)` — Transition Evaluation Event to execute
- L94 _private member_ `FStructProperty* ResultProperty = nullptr;` — Pointer to the result property of this transition

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SceneState` (scope `UE`)
- L28 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionEvaluation.h` (Public)


#### struct `UE::SceneState::FTransitionEvaluationParams`  
`struct FTransitionEvaluationParams`  
_L16-26_
- desc: The parameters required for transition evaluation
- L19 _public member_ `const FSceneStateExecutionContext& ExecutionContext;` — The current execution context
- L21 _public member_ `const FSceneStateMachine& StateMachine;` — The state machine the transition resides in
- L23 _public member_ `const FSceneStateMachineInstance& StateMachineInstance;` — The state machine instance data corresponding to the above state machine
- L25 _public member_ `const FSceneState& SourceState;` — The state containing the transition as an exit transition

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionInstance.h` (Public)


#### struct `FSceneStateTransitionInstance`  
`struct FSceneStateTransitionInstance`  
_L10-17_
- reflection: `USTRUCT()`
- desc: Instance data of a transition
- L16 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — The parameters to pass to the evaluation event

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionLink.h` (Public)


#### struct `FSceneStateTransitionLink`  
`struct FSceneStateTransitionLink`  
_L13-24_
- reflection: `USTRUCT()`
- desc: Holds information about the transition that is only used in transition link time @see FSceneStateTransition::Link
- L19 _public member_ `FName EventName;` — `UPROPERTY()` — Name to lookup and set the Event Function
- L23 _public member_ `FName ResultPropertyName;` — `UPROPERTY()` — Name of the Result Property the Event function sets

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionMetadata.h` (Public)


#### struct `FSceneStateTransitionMetadata`  
`struct FSceneStateTransitionMetadata`  
_L10-19_
- reflection: `USTRUCT()`
- desc: Metadata information about the Transition. Available only in editor
- L17 _public member_ `FGuid ParametersId;` — `UPROPERTY()` — Parameter id of the Transition, if any

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionResult.h` (Public)


#### struct `FSceneStateTransitionResult`  
`struct FSceneStateTransitionResult`  
_L9-16_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: The result output of a transition graph evaluation
- L15 _public member_ `bool bCanTransition = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Scene State Transition")` — Indicator of whether the transition condition succeeded

### `Plugins/VirtualProduction/SceneState/Source/SceneState/Public/Transition/SceneStateTransitionTarget.h` (Public)


#### enum `ESceneStateTransitionTargetType`  
`enum class ESceneStateTransitionTargetType : uint8`  
_L10-20_
- reflection: `UENUM()`
- desc: Types of object a transition can lead to
- L13 _public enumerator_ `State` — The transition leads to another state
- L16 _public enumerator_ `Exit` — The transition leads to an exit point
- L19 _public enumerator_ `Conduit` — The transition leads to a conduit

#### struct `FSceneStateTransitionTarget`  
`struct FSceneStateTransitionTarget`  
_L24-35_
- reflection: `USTRUCT()`
- desc: Describes a transition's target via its type (e.g. State) and an index if required (e.g. the index of the State)
- L30 _public member_ `ESceneStateTransitionTargetType Type = ESceneStateTransitionTargetType::State;` — `UPROPERTY()` — Target type to transition to
- L34 _public member_ `uint16 Index = std::numeric_limits<uint16>::max();` — `UPROPERTY()` — Index of the target to transition to, conditionally required
