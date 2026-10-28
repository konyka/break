# Plugins / GameplayStateTreeModule

- module root: `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule`
- headers: 14; symbols: 201
- symbol kinds: class=8, delegate=2, enum=1, enumerator=3, function=12, macro=7, member=52, namespace=1, prototype=101, struct=11, typedef=3
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, GameplayTags, GameplayTasks, NavigationSystem, PropertyBindingUtils, StateTreeModule

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Private/PropertyFunctions/StateTreeActorPropertyFunctions.h` (Private)


#### struct `FStateTreeGetActorLocationPropertyFunctionInstanceData`  
`struct FStateTreeGetActorLocationPropertyFunctionInstanceData`  
_L10-19_
- reflection: `USTRUCT()`
- L15 _public member_ `TObjectPtr<AActor> Input = nullptr;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L18 _public member_ `FVector Output = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = Output)`

#### struct `FStateTreeGetActorLocationPropertyFunction`  
`struct FStateTreeGetActorLocationPropertyFunction : public FStateTreePropertyFunctionCommonBase`  
_L22-35_
- reflection: `USTRUCT(DisplayName = "Get Actor Location")`
- inherits: `FStateTreePropertyFunctionCommonBase`
- L26 _public typedef_ `using FInstanceDataType = FStateTreeGetActorLocationPropertyFunctionInstanceData;`
- L28 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L30 _public prototype_ `virtual void Execute(FStateTreeExecutionContext& Context) const override;`
- L33 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const;`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/BehaviorTree/GameplayStateTreeBTUtils.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GameplayStateTreeBTUtils`
- L11 _prototype_ `EBTNodeResult::Type StateTreeRunStatusToBTNodeResult(EStateTreeRunStatus Result);` (scope `GameplayStateTreeBTUtils`)

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/BehaviorTree/Tasks/BTTask_RunDynamicStateTree.h` (Public)


#### class `UBTTask_RunDynamicStateTree`  
`class UBTTask_RunDynamicStateTree : public UBTTaskNode`  
_L20-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode`
- desc: RunDynamicStateTree task allows the execution of a state tree chosen at runtime. UBTTask_RunDynamicStateTree::SetDynamicStateTree can be used to set the node's state tree.
- L24 _public prototype_ `DECLARE_DELEGATE_ThreeParams(FSetContextDataDelegate, FStateTreeExecutionContext&, UBehaviorTreeComponent&, FGameplayTag InjectionTag);`
- L26 _public prototype_ `static bool SetDynamicStateTree(UBehaviorTreeComponent& OwnerComp, FGameplayTag InInjectTag, const FStateTreeReference& InStateTree, const FSetContextDataDelegate& InSetContextDataDelegate, float InInterval, float InRandomDeviation, UBTCompositeNode* OptionalStartNode = nullptr);`
- L28 _public function_ `FGameplayTag GetInjectionTag() const`
- L31 _protected prototype_ `UBTTask_RunDynamicStateTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L33 _protected prototype_ `virtual FString GetStaticDescription() const override;`
- L34 _protected prototype_ `virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;`
- L36 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L37 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L38 _protected prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L40 _protected prototype_ `void SetStateTreeToRun(UBehaviorTreeComponent& OwnerComp, const FStateTreeReference& StateTreeToRun, const FSetContextDataDelegate& SetContextDelegate, float Interval, float RandomDeviation);`
- L43 _protected prototype_ `const UObject* GetAssociatedAsset(TOptional<FBehaviorTreeNodeDebugContext> DebugContext) const override;`
- L47 _protected member_ `FStateTreeReference StateTreeRef;` — `UPROPERTY(Transient)`
- L50 _protected member_ `FStateTreeInstanceData InstanceData;` — `UPROPERTY(Transient)`
- L54 _protected member_ `FGameplayTag InjectionTag;` — `UPROPERTY(EditAnywhere, Category = Node)` — Gameplay tag that will identify this task for state tree injection
- L56 _protected member_ `FSetContextDataDelegate SetContextDataDelegate;`
- L58 _protected member_ `float Interval = 1.f;`
- L59 _protected member_ `float RandomDeviation = 0.f;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE_ThreeParams(FSetContextDataDelegate, FStateTreeExecutionContext&, UBehaviorTreeComponent&, FGameplayTag InjectionTag);`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/BehaviorTree/Tasks/BTTask_RunStateTree.h` (Public)


#### class `UBTTask_RunStateTree`  
`class UBTTask_RunStateTree : public UBTTaskNode, public IStateTreeSchemaProvider`  
_L18-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBTTaskNode,IStateTreeSchemaProvider`
- desc: RunStateTree task allows the execution of state tree with the StateTreeAIComponentSchema inside a behavior tree.
- L22 _public prototype_ `UBTTask_RunStateTree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _protected prototype_ `virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;`
- L26 _protected prototype_ `virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;`
- L27 _protected prototype_ `virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;`
- L29 _protected prototype_ `virtual bool SetContextRequirements(UBehaviorTreeComponent& OwnerComp, FStateTreeExecutionContext& Context);`
- L30 _protected prototype_ `virtual bool CollectExternalData(const FStateTreeExecutionContext& Context, const UStateTree* StateTree, TArrayView<const FStateTreeExternalDataDesc> ExternalDataDescs, TArrayView<FStateTreeDataView> OutDataViews);`
- L32 _protected prototype_ `virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;`
- L35 _protected prototype_ `virtual const UObject* GetAssociatedAsset(TOptional<FBehaviorTreeNodeDebugContext> DebugContext) const override;`
- L40 _protected member_ `FStateTreeReference StateTreeRef;` — `UPROPERTY(EditAnywhere, Category = Task, DisplayName="State Tree", meta = (Schema = "/Script/GameplayStateTreeModule.StateTreeAIComponentSchema", SchemaCanBeOverriden))` — State tree that will be run when the task is selected.
- L43 _protected member_ `FStateTreeInstanceData InstanceData;` — `UPROPERTY(Transient)`
- L47 _protected member_ `float Interval = 0.01f;` — `UPROPERTY(EditAnywhere, Category = Task, meta = (ClampMin = "0.001"))` — Interval between state tree update.
- L51 _protected member_ `float RandomDeviation = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Task, meta = (ClampMin = "0.0"))` — Random deviation on the interval between each state tree update.
- L54 _protected member_ `TWeakObjectPtr<AActor> SchemaActor;` — Saved actor used by the schema requirement.

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Components/StateTreeAIComponent.h` (Public)


#### class `UStateTreeAIComponent`  
`class UStateTreeAIComponent : public UStateTreeComponent`  
_L16-23_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AI, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UStateTreeComponent`
- desc: State tree component designed to be run on an AIController. It uses the StateTreeAIComponentSchema that guarantees access to the AIController.
- L21 _public prototype_ `TSubclassOf<UStateTreeSchema> GetSchema() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Components/StateTreeAIComponentSchema.h` (Public)


#### class `UStateTreeAIComponentSchema`  
`class UStateTreeAIComponentSchema : public UStateTreeComponentSchema`  
_L18-38_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "StateTree AI Component", CommonSchema))`
- inherits: `UStateTreeComponentSchema`
- desc: State tree schema to be used with StateTreeAIComponent. It guarantees access to an AIController and the Actor context value can be used to access the controlled pawn.
- L22 _public prototype_ `UStateTreeAIComponentSchema(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public prototype_ `virtual void PostLoad() override;`
- L26 _public prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L28 _public prototype_ `virtual void SetContextData(FContextDataSetter& ContextDataSetter, bool bLogErrors) const override;`
- L31 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L37 _protected member_ `TSubclassOf<AAIController> AIControllerClass;` — `UPROPERTY(EditAnywhere, Category = "Defaults", NoClear)` — AIController class the StateTree is expected to run on. Allows to bind to specific Actor class' properties.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Components/StateTreeComponent.h` (Public)


#### struct `FStateTreeComponentExecutionExtension`  
`struct FStateTreeComponentExecutionExtension : public FStateTreeExecutionExtension`  
_L25-34_
- reflection: `USTRUCT()`
- inherits: `FStateTreeExecutionExtension`
- L30 _public prototype_ `virtual void ScheduleNextTick(const FContextParameters& Context, const FNextTickArguments& Args) override;`
- L33 _public member_ `TObjectPtr<UStateTreeComponent> Component;` — `UPROPERTY()`

#### class `UStateTreeComponent`  
`class UStateTreeComponent : public UBrainComponent, public IGameplayTaskOwnerInterface, public IStateTreeSchemaProvider`  
_L39-199_
- reflection: `UCLASS(MinimalAPI, Blueprintable, ClassGroup = AI, HideCategories = (Activation, Collision), meta = (BlueprintSpawnableComponent))`
- inherits: `UBrainComponent,IGameplayTaskOwnerInterface,IStateTreeSchemaProvider`
- L43 _public prototype_ `UStateTreeComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L46 _public prototype_ `virtual void InitializeComponent() override;`
- L47 _public prototype_ `virtual void UninitializeComponent() override;`
- L48 _public prototype_ `virtual void BeginPlay() override;`
- L49 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L50 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L54 _public prototype_ `virtual void StartLogic() override;`
- L55 _public prototype_ `virtual void RestartLogic() override;`
- L56 _public prototype_ `virtual void StopLogic(const FString& Reason) override;`
- L57 _public prototype_ `virtual void Cleanup() override;`
- L58 _public prototype_ `virtual void PauseLogic(const FString& Reason) override;`
- L59 _public prototype_ `virtual EAILogicResuming::Type ResumeLogic(const FString& Reason) override;`
- L60 _public prototype_ `virtual bool IsRunning() const override;`
- L61 _public prototype_ `virtual bool IsPaused() const override;`
- L65 _public prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;`
- L66 _public prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;`
- L67 _public prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;`
- L68 _public prototype_ `virtual uint8 GetGameplayTaskDefaultPriority() const override;`
- L69 _public prototype_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;`
- L73 _public prototype_ `virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;`
- L81 _public prototype_ `void SetStateTree(UStateTree* StateTree);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Sets a new state tree. The state tree won't be set if the logic is running.
- L88 _public prototype_ `void SetStateTreeReference(FStateTreeReference StateTreeReference);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Sets a new state tree reference. The state tree reference won't be set if the logic is running.
- L94 _public prototype_ `void SetLinkedStateTreeOverrides(FStateTreeReferenceOverrides Overrides);` — Set the linked state tree overrides. The overrides won't be set if they do not use the StateTreeComponentSchema schema.
- L101 _public prototype_ `void AddLinkedStateTreeOverrides(const FGameplayTag StateTag, FStateTreeReference StateTreeReference);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Add a linked state tree override. The override won't be set if it doesn't use the StateTreeComponentSchema schema.
- L105 _public prototype_ `void RemoveLinkedStateTreeOverrides(const FGameplayTag StateTag);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Remove a linked state tree override.
- L113 _public prototype_ `void SetStartLogicAutomatically(const bool bInStartLogicAutomatically);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Sets whether the State Tree is started automatically on begin play. This function sets the bStartLogicAutomatically property, and should be used mostly from constructions scripts. If you wish to start the logic manually, call StartLogic().
- L117 _public prototype_ `void SendStateTreeEvent(const FStateTreeEvent& Event);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay|StateTree")` — Sends event to the running StateTree.
- L120 _public prototype_ `void SendStateTreeEvent(const FGameplayTag Tag, const FConstStructView Payload = FConstStructView(), const FName Origin = FName());` — Sends event to the running StateTree.
- L124 _public prototype_ `EStateTreeRunStatus GetStateTreeRunStatus() const;` — `UFUNCTION(BlueprintPure, Category = "Gameplay|StateTree")` — Returns the current run status of the StateTree.
- L128 _public member_ `FStateTreeRunStatusChanged OnStateTreeRunStatusChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Gameplay|StateTree")` — Called when the run status of the StateTree has changed
- L131 _public prototype_ `virtual FString GetDebugInfoString() const override;`
- L138 _public prototype_ `TArray<FName> GetActiveStateNames() const;` — @return the list of active states. If the StateTree has linked asset StateTree, then more than one state can have the same name. Only used for debugging purposes.
- L144 _protected prototype_ `virtual void PostLoad() override;`
- L151 _protected prototype_ `virtual void ValidateStateTreeReference();` — Called during initialize, will validate the state tree reference and create a context from the state tree to check its validity Override this function for custom state tree validation. Note: Override without calling super if the state tree reference is dynamically set after initialization
- L154 _protected prototype_ `virtual TValueOrError<void, FString> HasValidStateTreeReference() const;` — @return a value if the state tree reference can be used by the component or the error why it's not a valid reference.
- L156 _protected prototype_ `virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false);`
- L158 _protected prototype_ `virtual bool CollectExternalData(const FStateTreeExecutionContext& Context, const UStateTree* StateTree, TArrayView<const FStateTreeExternalDataDesc> Descs, TArrayView<FStateTreeDataView> OutDataViews) const;`
- L160 _protected prototype_ `void StartTree();`
- L161 _protected prototype_ `void ScheduleTickFrame(const FStateTreeScheduledTick& NextTick);`
- L162 _protected prototype_ `void ConditionalEnableTick();`
- L163 _protected prototype_ `void DisableTick();`
- L168 _protected member_ `TObjectPtr<UStateTree> StateTree_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Use StateTreeReference instead.")` — `UPROPERTY()`
- L173 _protected member_ `FStateTreeReference StateTreeRef;` — `UPROPERTY(EditAnywhere, Category = AI, DisplayName = "State Tree", meta=(Schema="/Script/GameplayStateTreeModule.StateTreeComponentSchema", SchemaCanBeOverriden))` — State Tree asset to run on the component.
- L180 _protected member_ `FStateTreeReferenceOverrides LinkedStateTreeOverrides;` — `UPROPERTY(EditAnywhere, Category = AI, meta=(Schema="/Script/GameplayStateTreeModule.StateTreeComponentSchema"))` — Overrides for linked State Trees. This table is used to override State Tree references on linked states. If a linked state's tag is exact match of the tag specified on the table, the reference from the table is used instead.
- L183 _protected member_ `FStateTreeInstanceData InstanceData;` — `UPROPERTY(Transient)`
- L187 _protected member_ `bool bStartLogicAutomatically = true;` — `UPROPERTY(EditAnywhere, Category = AI)` — If true, the StateTree logic is started on begin play. Otherwise, StartLogic() needs to be called.
- L190 _protected member_ `uint8 bIsRunning : 1;` — if set, execution has started and has not stopped yet.
- L193 _protected member_ `uint8 bIsPaused : 1;` — if set, execution has been requested to stop ticking.
- L196 _private member_ `FStateTreeExecutionContext* CurrentlyRunningExecContext = nullptr;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`
- L36 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateTreeRunStatusChanged, EStateTreeRunStatus, StateTreeRunStatus);`
- L36 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateTreeRunStatusChanged, EStateTreeRunStatus, StateTreeRunStatus);`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Components/StateTreeComponentSchema.h` (Public)


#### enum `EStateTreeComponentSchemaScheduledTickPolicy`  
`enum class EStateTreeComponentSchemaScheduledTickPolicy : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `Default`
- L21 _public enumerator_ `Allowed`
- L22 _public enumerator_ `Denied`

#### class `UStateTreeComponentSchema`  
`class UStateTreeComponentSchema : public UStateTreeSchema`  
_L29-99_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew, CollapseCategories, meta = (DisplayName = "StateTree Component", CommonSchema))`
- inherits: `UStateTreeSchema`
- desc: StateTree for Actors with StateTree component.
- L34 _public prototype_ `UStateTreeComponentSchema();`
- L36 _public function_ `UClass* GetContextActorClass() const`
- L38 _public prototype_ `static bool SetContextRequirements(UBrainComponent& BrainComponent, FStateTreeExecutionContext& Context, bool bLogErrors = false);`
- L39 _public prototype_ `static bool CollectExternalData(const FStateTreeExecutionContext& Context, const UStateTree* StateTree, TArrayView<const FStateTreeExternalDataDesc> Descs, TArrayView<FStateTreeDataView> OutDataViews);`
- L42 _protected prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InScriptStruct) const override;`
- L43 _protected prototype_ `virtual bool IsClassAllowed(const UClass* InScriptStruct) const override;`
- L44 _protected prototype_ `virtual bool IsExternalItemAllowed(const UStruct& InStruct) const override;`
- L45 _protected prototype_ `virtual bool IsScheduledTickAllowed() const override;`
- L66 _protected prototype_ `virtual void SetContextData(FContextDataSetter& ContextDataSetter, bool bLogErrors) const;`
- L68 _protected prototype_ `virtual TConstArrayView<FStateTreeExternalDataDesc> GetContextDataDescs() const override;`
- L71 _protected prototype_ `virtual void PostLoad() override;`
- L74 _protected prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L77 _protected function_ `const FStateTreeExternalDataDesc& GetContextActorDataDesc() const`
- L78 _protected function_ `FStateTreeExternalDataDesc& GetContextActorDataDesc()`
- L82 _protected member_ `TSubclassOf<AActor> ContextActorClass;` — `UPROPERTY(EditAnywhere, Category="Defaults", NoClear)` — Actor class the StateTree is expected to run on. Allows to bind to specific Actor class' properties.
- L89 _protected member_ `EStateTreeComponentSchemaScheduledTickPolicy ScheduledTickPolicy = EStateTreeComponentSchemaScheduledTickPolicy::Default;` — `UPROPERTY(EditAnywhere, Category="Defaults")` — Indicates if the execution can sleep and the tick delayed. The default value set by the cvar StateTree.Component.DefaultScheduledTickAllowed
- L94 _protected member_ `FStateTreeExternalDataDesc ContextActorDataDesc_DEPRECATED;` — `UE_DEPRECATED(5.4, "ContextActorDataDesc is being replaced with ContextDataDescs. Call GetContextActorDataDesc to access the equivalent.")` — `UPROPERTY()`
- L98 _protected member_ `TArray<FStateTreeExternalDataDesc> ContextDataDescs;` — `UPROPERTY()`

#### struct `UStateTreeComponentSchema::FContextDataSetter`  
`struct FContextDataSetter`  
_L48-65_
- desc: Helper class to set the context data on the ExecutionContext
- L51 _public prototype_ `FContextDataSetter(TNotNull<const UBrainComponent*> BrainComponent, FStateTreeExecutionContext& Context);`
- L53 _public function_ `TNotNull<const UBrainComponent*> GetComponent() const`
- L57 _public prototype_ `TNotNull<const UStateTree*> GetStateTree() const;`
- L58 _public prototype_ `TNotNull<const UStateTreeComponentSchema*> GetSchema() const;`
- L60 _public prototype_ `bool SetContextDataByName(FName Name, FStateTreeDataView DataView);`
- L63 _private member_ `TNotNull<const UBrainComponent*> BrainComponent;`
- L64 _private member_ `FStateTreeExecutionContext& ExecutionContext;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Conditions/StateTreeAIConditionBase.h` (Public)


#### struct `FStateTreeAIConditionBase`  
`struct FStateTreeAIConditionBase : public FStateTreeConditionBase`  
_L11-14_
- reflection: `USTRUCT(meta = (Hidden, Category = "AI"))`
- inherits: `FStateTreeConditionBase`
- desc: Base class of all AI condition that expect to be run on an AIController or derived class

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/GameplayStateTreeBlueprintFunctionLibrary.h` (Public)


#### class `UGameplayStateTreeBlueprintFunctionLibrary`  
`class UGameplayStateTreeBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L14-28_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "GameplayStateTreeLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L27 _public prototype_ `static bool RunStateTree(AActor* Actor, UStateTree* StateTreeAsset);` — `UFUNCTION(BlueprintCallable, Category = "AI", meta=(ReturnDisplayName="bSuccess"))` — Starts executing an instance of the provided state tree asset on the specified actor. This will use the existing required component if present or add it if missing. @param Actor The actor on which the StateTree must be executed. @param StateTreeAsset The state tree asset to execute @return Whether a state tree instance was successfully started

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/GameplayStateTreeModule.h` (Public)


#### class `IGameplayStateTreeModule`  
`class IGameplayStateTreeModule : public IModuleInterface`  
_L10-29_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `static IGameplayStateTreeModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Tasks/StateTreeAITask.h` (Public)


#### struct `FStateTreeAITaskBase`  
`struct FStateTreeAITaskBase : public FStateTreeTaskBase`  
_L11-14_
- reflection: `USTRUCT(meta= (Hidden, Category = "AI"))`
- inherits: `FStateTreeTaskBase`
- desc: Base class of all AI task that expect to be run on an AIController or derived class

#### struct `FStateTreeAIActionTaskBase`  
`struct FStateTreeAIActionTaskBase : public FStateTreeAITaskBase`  
_L18-21_
- reflection: `USTRUCT(meta = (Hidden, Category="AI|Action"))`
- inherits: `FStateTreeAITaskBase`
- desc: Base class of all AI task that do a physical action

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Tasks/StateTreeMoveToTask.h` (Public)


#### struct `FStateTreeMoveToTaskInstanceData`  
`struct FStateTreeMoveToTaskInstanceData`  
_L22-81_
- reflection: `USTRUCT()`
- L27 _public member_ `TObjectPtr<AAIController> AIController = nullptr;` — `UPROPERTY(EditAnywhere, Category = Context)`
- L30 _public member_ `FVector Destination = FVector::Zero();` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L33 _public member_ `TObjectPtr<AActor> TargetActor;` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L37 _public member_ `float AcceptableRadius = GET_AI_CONFIG_VAR(AcceptanceRadius);` — `UPROPERTY(EditAnywhere, Category = Parameter, meta=(ClampMin = "0.0", UIMin="0.0"))` — fixed distance added to threshold between AI and goal location in destination reach test
- L43 _public member_ `float DestinationMoveTolerance = 0.f;` — `UPROPERTY(EditAnywhere, Category = Parameter, meta = (ClampMin = "0.0", UIMin = "0.0", EditCondition="bTrackMovingGoal"))` — if the task is expected to react to changes to location in input this property can be used to tweak sensitivity of the mechanism. Value is recommended to be less than AcceptableRadius
- L47 _public member_ `TSubclassOf<UNavigationQueryFilter> FilterClass;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — "None" will result in default filter being used
- L50 _public member_ `bool bAllowStrafe = GET_AI_CONFIG_VAR(bAllowStrafing);` — `UPROPERTY(EditAnywhere, Category = Parameter)`
- L54 _public member_ `bool bAllowPartialPath = GET_AI_CONFIG_VAR(bAcceptPartialPaths);` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, use incomplete path when goal can't be reached
- L58 _public member_ `bool bTrackMovingGoal = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, path to goal actor will update itself when actor moves
- L62 _public member_ `bool bRequireNavigableEndLocation = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, the goal location will need to be navigable
- L66 _public member_ `bool bProjectGoalLocation = true;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, goal location will be projected on navigation data (navmesh) before using
- L70 _public member_ `bool bReachTestIncludesAgentRadius = GET_AI_CONFIG_VAR(bFinishMoveOnGoalOverlap);` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, radius of AI's capsule will be added to threshold between AI and goal location in destination reach test
- L74 _public member_ `bool bReachTestIncludesGoalRadius = GET_AI_CONFIG_VAR(bFinishMoveOnGoalOverlap);` — `UPROPERTY(EditAnywhere, Category = Parameter)` — if set, radius of goal's capsule will be added to threshold between AI and goal location in destination reach test
- L77 _public member_ `TObjectPtr<UAITask_MoveTo> MoveToTask = nullptr;` — `UPROPERTY(Transient)`
- L80 _public member_ `TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner = nullptr;` — `UPROPERTY(Transient)`

#### struct `FStateTreeMoveToTask`  
`struct FStateTreeMoveToTask : public FStateTreeAIActionTaskBase`  
_L88-121_
- reflection: `USTRUCT(meta = (DisplayName = "Move To", Category = "AI|Action"))`
- inherits: `FStateTreeAIActionTaskBase`
- desc: Task moving the given AIController's pawn using the AITask_MoveTo framework. Succeed when move ends at destinations, fails if move is impossible.
- L92 _public typedef_ `using FInstanceDataType = FStateTreeMoveToTaskInstanceData;`
- L94 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L96 _public prototype_ `FStateTreeMoveToTask();`
- L97 _public prototype_ `virtual bool Link(FStateTreeLinker& Linker) override;`
- L98 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L99 _public prototype_ `virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;`
- L100 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L102 _public prototype_ `virtual UAITask_MoveTo* PrepareMoveToTask(FStateTreeExecutionContext& Context, AAIController& Controller, UAITask_MoveTo* ExistingTask, FAIMoveRequest& MoveRequest) const;`
- L103 _public prototype_ `virtual EStateTreeRunStatus PerformMoveTask(FStateTreeExecutionContext& Context, AAIController& Controller) const;`
- L106 _public prototype_ `virtual EDataValidationResult Compile(UE::StateTree::ICompileNodeContext& Context) override;`
- L108 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L109 _public function_ `virtual FName GetIconName() const override`
- L113 _public function_ `virtual FColor GetIconColor() const override`
- L120 _public member_ `bool bSavedShouldCallTick = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`

### `Plugins/Runtime/GameplayStateTree/Source/GameplayStateTreeModule/Public/Tasks/StateTreeRunEnvQueryTask.h` (Public)


#### struct `FStateTreeRunEnvQueryInstanceData`  
`struct FStateTreeRunEnvQueryInstanceData`  
_L14-39_
- reflection: `USTRUCT()`
- L20 _public member_ `FStateTreePropertyRef Result;` — `UPROPERTY(EditAnywhere, Category = Out, meta = (RefType = "/Script/CoreUObject.Vector, /Script/Engine.Actor", CanRefToArray))` — Result of the query. If an array is binded, it will output all the created values otherwise it will output the best one.
- L24 _public member_ `TObjectPtr<AActor> QueryOwner = nullptr;` — `UPROPERTY(EditAnywhere, Category = Context)` — The query will be run with this actor has the owner object.
- L28 _public member_ `TObjectPtr<UEnvQuery> QueryTemplate;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — The query template to run
- L32 _public member_ `TArray<FAIDynamicParam> QueryConfig;` — `UPROPERTY(EditAnywhere, EditFixedSize, Category = Parameter)` — Query config associated with the query template.
- L36 _public member_ `TEnumAsByte<EEnvQueryRunMode::Type> RunMode = EEnvQueryRunMode::SingleResult;` — `UPROPERTY(EditAnywhere, Category = Parameter)` — determines which item will be stored (All = only first matching)
- L38 _public member_ `int32 RequestId = INDEX_NONE;`

#### struct `FStateTreeRunEnvQueryTask`  
`struct FStateTreeRunEnvQueryTask : public FStateTreeTaskCommonBase`  
_L49-74_
- reflection: `USTRUCT(meta = (DisplayName = "Run Env Query", Category = "Common"))`
- inherits: `FStateTreeTaskCommonBase`
- desc: Task that runs an async environment query and outputs the result to an outside parameter. Supports Actor and vector types EQS. The task is usually run in a sibling state to the result user will be with the data being stored in the parent state's parameters. - Parent (Has an EQS result parameter) - Run Env Query (If success go to Use Query Result) - Use Query Result
- L53 _public typedef_ `using FInstanceDataType = FStateTreeRunEnvQueryInstanceData;`
- L55 _public prototype_ `FStateTreeRunEnvQueryTask();`
- L57 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L59 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L60 _public prototype_ `virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;`
- L63 _public prototype_ `virtual void PostEditInstanceDataChangeChainProperty(const FPropertyChangedChainEvent& PropertyChangedEvent, FStateTreeDataView InstanceDataView) override;`
- L64 _public prototype_ `virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;`
- L65 _public function_ `virtual FName GetIconName() const override`
- L69 _public function_ `virtual FColor GetIconColor() const override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYSTATETREEMODULE_API`
