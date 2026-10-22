# Plugins / SceneStateMachineGraph

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph`
- headers: 19; symbols: 332
- symbol kinds: class=11, enum=1, enumerator=7, function=31, macro=9, member=50, namespace=29, prototype=183, struct=8, typedef=3
- PrivateDependencyModuleNames: BlueprintGraph, GraphEditor, SceneStateEditor, Slate, SlateCore, StructUtilsEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneState, SceneStateBinding, SceneStateEvent, SceneStateTransitionGraph

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/Actions/SceneStateMachineAction_NewBlueprintTask.h` (Private)


#### struct `UE::SceneState::Graph::FStateMachineAction_NewBlueprintTask`  
`struct FStateMachineAction_NewBlueprintTask : public FEdGraphSchemaAction`  
_L14-28_
- inherits: `FEdGraphSchemaAction`
- desc: Adds a new task node with a set blueprint class to the State Machine Graph
- L16 _public prototype_ `FStateMachineAction_NewBlueprintTask() = default;`
- L18 _public prototype_ `explicit FStateMachineAction_NewBlueprintTask(const FAssetData& InBlueprintTaskAsset, int32 InSectionId);`
- L21 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* InParentGraph, UEdGraphPin* InSourcePin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;`
- L24 _public prototype_ `TSubclassOf<USceneStateBlueprintableTask> ResolveBlueprintTaskClass() const;`
- L27 _private member_ `FAssetData BlueprintTaskAsset;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/Actions/SceneStateMachineAction_NewComment.h` (Private)


#### struct `UE::SceneState::Graph::FStateMachineAction_NewComment`  
`struct FStateMachineAction_NewComment : public FEdGraphSchemaAction`  
_L11-20_
- inherits: `FEdGraphSchemaAction`
- desc: Adds a new comment to the State Machine Graph
- L13 _public prototype_ `FStateMachineAction_NewComment() = default;`
- L15 _public prototype_ `explicit FStateMachineAction_NewComment(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, int32 InGrouping);`
- L18 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* InParentGraph, UEdGraphPin* InSourcePin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/Actions/SceneStateMachineAction_NewNode.h` (Private)


#### struct `UE::SceneState::Graph::FStateMachineAction_NewNode`  
`struct FStateMachineAction_NewNode : public FEdGraphSchemaAction`  
_L11-32_
- inherits: `FEdGraphSchemaAction`
- desc: Adds a new node to the State Machine Graph
- L13 _public prototype_ `FStateMachineAction_NewNode() = default;`
- L15 _public prototype_ `explicit FStateMachineAction_NewNode(UEdGraphNode* InTemplateNode);`
- L17 _public prototype_ `explicit FStateMachineAction_NewNode(UEdGraphNode* InTemplateNode, const FText& InNodeCategory, const FText& InMenuDesc, const FText& InTooltip, int32 InGrouping);`
- L20 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* InParentGraph, UEdGraphPin* InSourcePin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;`
- L21 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L25 _public function_ `template <typename InNodeType> static InNodeType* SpawnNode(UEdGraph* InParentGraph, InNodeType* InNewNode, UEdGraphPin* InSourcePin, const UE::Slate::FDeprecateVector2DParameter& InLocation = FVector2f::ZeroVector, bool bInSelectNewNode = true)`
- L31 _private member_ `TObjectPtr<UEdGraphNode> TemplateNode;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/Actions/SceneStateMachineAction_NewTask.h` (Private)


#### struct `UE::SceneState::Graph::FStateMachineAction_NewTask`  
`struct FStateMachineAction_NewTask : public FEdGraphSchemaAction`  
_L11-24_
- inherits: `FEdGraphSchemaAction`
- desc: Adds a new task node to the State Machine Graph
- L13 _public prototype_ `FStateMachineAction_NewTask() = default;`
- L15 _public prototype_ `explicit FStateMachineAction_NewTask(const UScriptStruct* InTaskStruct, int32 InSectionId);`
- L18 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* InParentGraph, UEdGraphPin* InSourcePin, const FVector2f& InLocation, bool bInSelectNewNode = true) override;`
- L19 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L23 _private member_ `TObjectPtr<const UScriptStruct> TaskStruct;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/Nodes/SceneStateMachineNodeNameValidator.h` (Private)


#### class `UE::SceneState::Graph::FStateMachineNodeNameValidator`  
`class FStateMachineNodeNameValidator : public INameValidatorInterface`  
_L14-26_
- inherits: `INameValidatorInterface`
- L17 _public prototype_ `explicit FStateMachineNodeNameValidator(const USceneStateMachineNode* InNodeToValidate);`
- L21 _private prototype_ `virtual EValidatorResult IsValid(const FName& InName, bool bInOriginal) override;`
- L22 _private prototype_ `virtual EValidatorResult IsValid(const FString& InName, bool bInOriginal) override;`
- L25 _private member_ `TSet<FName> Names;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L11 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Private/SceneStateMachineNodeConnectionType.h` (Private)


#### struct `UE::SceneState::Graph::FNodeConnectionType`  
`struct FNodeConnectionType`  
_L11-39_
- desc: Combines a source node type and a target type to a single keyable (type hashable) struct
- L13 _public prototype_ `FNodeConnectionType() = default;`
- L15 _public function_ `explicit FNodeConnectionType(EStateMachineNodeType InSourceType, EStateMachineNodeType InTargetType) : SourceType(InSourceType) , TargetType(InTargetType)`
- L26 _public function_ `bool operator==(const FNodeConnectionType& InOther) const`
- L31 _public function_ `uint16 AsNumber() const`
- L37 _private member_ `EStateMachineNodeType SourceType = EStateMachineNodeType::Unspecified;`
- L38 _private member_ `EStateMachineNodeType TargetType = EStateMachineNodeType::Unspecified;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L21 _function_ `friend uint32 GetTypeHash(const FNodeConnectionType& InNodeConnectionType)` (scope `UE::SceneState::Graph`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Actions/SceneStateMachineNodeAction.h` (Public)


#### struct `UE::SceneState::Graph::FStateMachineAction_Node`  
`struct UE_INTERNAL FStateMachineAction_Node : public FEdGraphSchemaAction`  
_L15-43_
- inherits: `FEdGraphSchemaAction`
- L17 _public prototype_ `FStateMachineAction_Node() = default;`
- L25 _public prototype_ `explicit FStateMachineAction_Node(const FArguments& InArgs);`
- L27 _public prototype_ `static FName StaticGetTypeId();`
- L29 _public function_ `USceneStateMachineNode* GetNode() const`
- L35 _public prototype_ `virtual bool IsParentable() const override;`
- L36 _public prototype_ `virtual bool CanBeRenamed() const override;`
- L37 _public prototype_ `virtual FName GetTypeId() const override;`
- L38 _public prototype_ `virtual FEdGraphSchemaActionDefiningObject GetPersistentItemDefiningObject() const override;`
- L42 _private member_ `TWeakObjectPtr<USceneStateMachineNode> NodeWeak;`

#### struct `UE::SceneState::Graph::FStateMachineAction_Node::FArguments`  
`struct FArguments`  
_L19-24_
- L21 _public member_ `USceneStateMachineNode* Node = nullptr;`
- L22 _public member_ `FText Category;`
- L23 _public member_ `int32 SectionID;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineConduitNode.h` (Public)


#### class `USceneStateMachineConduitNode`  
`class USceneStateMachineConduitNode : public USceneStateMachineNode, public ISceneStateTransitionGraphProvider`  
_L10-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateMachineNode,ISceneStateTransitionGraphProvider`
- L15 _public prototype_ `USceneStateMachineConduitNode();`
- L17 _public function_ `bool ShouldWaitForTasksToFinish() const`
- L23 _public prototype_ `virtual UEdGraph* CreateBoundGraphInternal() override;`
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L29 _public prototype_ `virtual void PostPasteNode() override;`
- L30 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L34 _public prototype_ `virtual FText GetTitle() const override;`
- L35 _public prototype_ `virtual bool IsBoundToGraphLifetime(UEdGraph& InGraph) const override;`
- L36 _public prototype_ `virtual UEdGraphNode* AsNode() override;`
- L41 _private member_ `bool bWaitForTasksToFinish = true;` — `UPROPERTY(EditAnywhere, Category = "Conduit")`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineEntryNode.h` (Public)


#### class `USceneStateMachineEntryNode`  
`class USceneStateMachineEntryNode : public USceneStateMachineNode`  
_L13-32_
- reflection: `UCLASS(MinimalAPI, meta=(ToolTip="Entry point for state machine"))`
- inherits: `USceneStateMachineNode`
- L18 _public prototype_ `USceneStateMachineEntryNode();`
- L21 _public prototype_ `USceneStateMachineStateNode* GetStateNode() const;` — Retrieves the first State Node in the State Machine
- L24 _public prototype_ `virtual UEdGraphPin* GetInputPin() const override;`
- L25 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;`
- L26 _public prototype_ `virtual bool HasValidPins() const override;`
- L30 _public prototype_ `virtual void AllocateDefaultPins() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineExitNode.h` (Public)


#### class `USceneStateMachineExitNode`  
`class USceneStateMachineExitNode : public USceneStateMachineNode`  
_L9-25_
- reflection: `UCLASS(MinimalAPI, meta=(ToolTip="Exit point for a state machine"))`
- inherits: `USceneStateMachineNode`
- L14 _public prototype_ `USceneStateMachineExitNode();`
- L17 _public prototype_ `virtual UEdGraphPin* GetInputPin() const override;`
- L18 _public prototype_ `virtual UEdGraphPin* GetOutputPin() const override;`
- L19 _public prototype_ `virtual bool HasValidPins() const override;`
- L23 _public prototype_ `virtual void AllocateDefaultPins() override;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineNode.h` (Public)


#### class `USceneStateMachineNode`  
`class USceneStateMachineNode : public UEdGraphNode`  
_L14-100_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UEdGraphNode`
- L20 _public prototype_ `TArray<USceneStateMachineTransitionNode*> GatherTransitions(bool bInSortList = false) const;` — Gathers and returns all the transition nodes connected to this state (including bi-directional transitions)
- L22 _public function_ `FName GetNodeName() const`
- L27 _public function_ `UE::SceneState::Graph::EStateMachineNodeType GetNodeType() const`
- L32 _public prototype_ `UEdGraph* GetBoundGraph() const;`
- L34 _public function_ `TConstArrayView<UEdGraph*> GetBoundGraphs() const`
- L39 _public function_ `FVector2D GetNodePosition() const`
- L44 _public function_ `virtual UEdGraphPin* GetInputPin() const`
- L49 _public function_ `virtual UEdGraphPin* GetOutputPin() const`
- L54 _public function_ `virtual bool HasValidPins() const`
- L59 _public prototype_ `bool ConditionallyCreateBoundGraph();`
- L61 _public function_ `virtual UEdGraph* CreateBoundGraphInternal()`
- L67 _public prototype_ `void CleanInvalidBoundGraphs();` — Removes null graphs and graphs not outered to this node
- L70 _public prototype_ `virtual void DestroyNode() override;`
- L71 _public prototype_ `virtual void PostPasteNode() override;`
- L72 _public prototype_ `virtual void OnRenameNode(const FString& InNodeName);`
- L73 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* InSourcePin) override;`
- L74 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L75 _public prototype_ `virtual TArray<UEdGraph*> GetSubGraphs() const override;`
- L76 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L77 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L78 _public prototype_ `virtual void JumpToDefinition() const override;`
- L79 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* InSchema) const override;`
- L80 _public prototype_ `virtual TSharedPtr<INameValidatorInterface> MakeNameValidator() const override;`
- L84 _public prototype_ `virtual void PostLoad() override;`
- L89 _protected prototype_ `void HidePins(TConstArrayView<FName> InPinNames);` — Finds the given pin and sets bHidden true to it
- L91 _protected prototype_ `void GenerateNewNodeName();`
- L94 _protected member_ `FName NodeName;` — `UPROPERTY()`
- L96 _protected member_ `UE::SceneState::Graph::EStateMachineNodeType NodeType = UE::SceneState::Graph::EStateMachineNodeType::Unspecified;`
- L99 _protected member_ `TArray<TObjectPtr<UEdGraph>> BoundGraphs;` — `UPROPERTY(Instanced)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineStateNode.h` (Public)


#### class `USceneStateMachineStateNode`  
`class USceneStateMachineStateNode : public USceneStateMachineNode, public ISceneStateEventHandlerProvider`  
_L14-90_
- reflection: `UCLASS(MinimalAPI, meta=(ToolTip="State node in a State Machine"))`
- inherits: `USceneStateMachineNode,ISceneStateEventHandlerProvider`
- L19 _public typedef_ `using FOnParametersChanged = TMulticastDelegate<void(USceneStateMachineStateNode*)>;`
- L21 _public prototype_ `USceneStateMachineStateNode();`
- L23 _public prototype_ `UE_INTERNAL static FOnParametersChanged::RegistrationType& OnParametersChanged();`
- L25 _public prototype_ `UE_INTERNAL void NotifyParametersChanged();`
- L27 _public function_ `UEdGraphPin* GetTaskPin() const`
- L32 _public function_ `TConstArrayView<FSceneStateEventHandler> GetEventHandlers() const`
- L38 _public prototype_ `UE_INTERNAL TOptional<uint16> GetCompiledIndex() const;` — Gets the index to the state this node compiled to last
- L41 _public prototype_ `UE_INTERNAL void SetCompiledIndex(uint16 InCompiledIndex);` — Sets the index to the state this node compiled to last
- L44 _public prototype_ `virtual bool FindEventHandlerId(const FSceneStateEventSchemaHandle& InEventSchemaHandle, FGuid& OutHandlerId) const override;`
- L48 _public prototype_ `virtual bool HasValidPins() const override;`
- L49 _public prototype_ `virtual UEdGraph* CreateBoundGraphInternal() override;`
- L53 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L54 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L55 _public prototype_ `virtual void PostPasteNode() override;`
- L56 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L60 _public prototype_ `virtual void PostInitProperties() override;`
- L61 _public prototype_ `virtual void PostLoad() override;`
- L62 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L63 _public prototype_ `virtual void PostEditImport() override;`
- L67 _public prototype_ `void GenerateNewParametersId();` — Called to set a new unique id for parameters (e.g. after duplicating)
- L71 _public member_ `FGuid ParametersId;` — `UPROPERTY(VisibleAnywhere, Category="Parameters")` — Identifier for the Parameters Struct Id
- L75 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category="Parameters")` — State parameters
- L79 _public member_ `TObjectPtr<UEdGraph> MainGraph;` — `UPROPERTY()` — Deprecated: Graphs are now managed in the Node Base class
- L82 _public member_ `TArray<FSceneStateEventHandler> EventHandlers;` — `UPROPERTY(EditAnywhere, Category="Events", meta=(NoBinding))`
- L87 _private member_ `TOptional<uint16> CompiledIndex;` — `UPROPERTY()` — Index to the state this state node compiled to last.
- L89 _private member_ `static FOnParametersChanged OnParametersChangedDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineTaskNode.h` (Public)


#### class `USceneStateMachineTaskNode`  
`class USceneStateMachineTaskNode : public USceneStateMachineNode`  
_L24-133_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateMachineNode`
- L29 _public prototype_ `USceneStateMachineTaskNode();`
- L31 _public function_ `TConstStructView<FSceneStateTask> GetTask() const`
- L36 _public function_ `TStructView<FSceneStateTaskInstance> GetTaskInstance()`
- L41 _public function_ `TMulticastDelegateRegistration<void()>& OnPostEditTask() const`
- L46 _public prototype_ `bool SetTaskStruct(const UScriptStruct* InTaskStruct);`
- L48 _public prototype_ `void SetTaskBlueprintClass(TSubclassOf<USceneStateBlueprintableTask> InTaskClass);`
- L50 _public prototype_ `bool FindDataViewById(const FGuid& InStructId, FStructView& OutDataView);`
- L52 _public function_ `const FGuid& GetTaskId() const`
- L58 _public prototype_ `UE_INTERNAL TOptional<uint16> GetCompiledIndex() const;` — Gets the index to the task this node compiled to last
- L61 _public prototype_ `UE_INTERNAL void SetCompiledIndex(uint16 InCompiledIndex);` — Sets the index to the task this node compiled to last
- L64 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L65 _public prototype_ `virtual void OnRenameNode(const FString& InNodeName);`
- L66 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L67 _public prototype_ `virtual FText GetTooltipText() const override;`
- L68 _public prototype_ `virtual bool CanDuplicateNode() const override;`
- L69 _public prototype_ `virtual void PostPasteNode() override;`
- L70 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L71 _public prototype_ `virtual TSharedPtr<INameValidatorInterface> MakeNameValidator() const override;`
- L75 _public prototype_ `virtual void PostLoad() override;`
- L76 _public prototype_ `virtual void BeginDestroy() override;`
- L77 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L78 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L79 _public prototype_ `virtual void PostEditImport() override;`
- L82 _public function_ `static FName GetTaskPropertyName()`
- L87 _public function_ `static FName GetTaskInstancePropertyName()`
- L94 _private prototype_ `static UE::SceneState::ETaskObjectType GetChangedObject(FPropertyChangedChainEvent& InPropertyChangedEvent);` — Determines whether the changed property comes from the task or task instance object, or none of them
- L97 _private prototype_ `void PostEditChangeTask(FPropertyChangedChainEvent& InPropertyChangedEvent, UE::SceneState::ETaskObjectType InChangedObject);` — Called on PostEditChangeChainProperty when the property that changed came from a Task or task instance object
- L100 _private prototype_ `FSceneStateTaskDescContext MakeContext() const;` — Create context for this task node
- L103 _private prototype_ `FSceneStateTaskDescMutableContext MakeMutableContext();` — Creates a mutable context for this task node
- L106 _private prototype_ `void RebuildTaskInstance();` — Rebuilds the task instance by recreating any instanced objects / or re-initializing any 'instance' guid property
- L109 _private prototype_ `void OnTaskChanged();` — Called when the task has changed its type, or a property related to the task / task instance has changed.
- L112 _private prototype_ `void OnStructIdChanged(const UE::SceneState::FStructIdChange& InChange);` — Called when a struct id has changed
- L115 _private prototype_ `void GenerateNewTaskId();` — Generates a new task id for this task node, notifying the binding owner of a struct id change
- L118 _private member_ `TInstancedStruct<FSceneStateTask> Task;` — `UPROPERTY(EditAnywhere, Category = "Task", meta=(StructTypeConst))`
- L121 _private member_ `TInstancedStruct<FSceneStateTaskInstance> TaskInstance;` — `UPROPERTY(EditAnywhere, Category="Task", meta=(StructTypeConst))`
- L125 _private member_ `TOptional<uint16> CompiledIndex;` — `UPROPERTY()` — Index to the task this task node compiled to last.
- L128 _private member_ `FGuid TaskId;` — `UPROPERTY()`
- L130 _private member_ `mutable TMulticastDelegate<void()> OnPostEditTaskDelegate;`
- L132 _private member_ `mutable FText CachedTaskDisplayName;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SceneState` (scope `UE`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Nodes/SceneStateMachineTransitionNode.h` (Public)


#### class `USceneStateMachineTransitionNode`  
`class USceneStateMachineTransitionNode : public USceneStateMachineNode, public ISceneStateTransitionGraphProvider`  
_L13-132_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateMachineNode,ISceneStateTransitionGraphProvider`
- L18 _public prototype_ `USceneStateMachineTransitionNode();`
- L20 _public typedef_ `using FOnParametersChanged = TMulticastDelegate<void(USceneStateMachineTransitionNode&)>;`
- L22 _public prototype_ `static FOnParametersChanged::RegistrationType& OnParametersChanged();`
- L24 _public prototype_ `void NotifyParametersChanged();`
- L26 _public prototype_ `static TArray<USceneStateMachineTransitionNode*> GetTransitionsToRelink(UEdGraphPin* InSourcePin , UEdGraphPin* InOldTargetPin , TConstArrayView<UEdGraphNode*> InSelectedGraphNodes);`
- L30 _public prototype_ `USceneStateMachineNode* GetSourceNode() const;`
- L32 _public prototype_ `USceneStateMachineNode* GetTargetNode() const;`
- L34 _public function_ `int32 GetPriority() const`
- L39 _public function_ `bool ShouldWaitForTasksToFinish() const`
- L44 _public function_ `const FGuid& GetParametersId() const`
- L49 _public function_ `const FInstancedPropertyBag& GetParameters() const`
- L54 _public function_ `FInstancedPropertyBag& GetParametersMutable()`
- L59 _public prototype_ `void CreateConnections(USceneStateMachineNode* InSourceState, USceneStateMachineNode* InTargetState);`
- L65 _public prototype_ `void RelinkHead(USceneStateMachineNode* InNewTargetState);` — Relink transition head (where the arrow is of a state transition) to a new state. @param InNewTargetState The new transition target
- L68 _public prototype_ `virtual UEdGraph* CreateBoundGraphInternal() override;`
- L72 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L73 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L74 _public prototype_ `virtual FText GetTooltipText() const override;`
- L75 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* InPin) override;`
- L76 _public function_ `virtual bool CanDuplicateNode() const override`
- L77 _public prototype_ `virtual void PostPasteNode() override;`
- L78 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L82 _public prototype_ `virtual FText GetTitle() const override;`
- L83 _public prototype_ `virtual bool IsBoundToGraphLifetime(UEdGraph& InGraph) const override;`
- L84 _public prototype_ `virtual UEdGraphNode* AsNode() override;`
- L88 _public prototype_ `virtual void PostInitProperties() override;`
- L89 _public prototype_ `virtual void PostLoad() override;`
- L90 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L91 _public prototype_ `virtual void PostEditImport() override;`
- L92 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L95 _public function_ `static FName GetParametersIdName()`
- L100 _public function_ `static FName GetParametersName()`
- L107 _private prototype_ `void GenerateNewParametersId();` — Called to set a new unique id for parameters (e.g. after duplicating)
- L109 _private member_ `static FOnParametersChanged OnParametersChangedDelegate;`
- L113 _private member_ `TObjectPtr<UEdGraph> TransitionGraph;` — `UPROPERTY()` — Deprecated: Graphs are now managed in the Node Base class
- L120 _private member_ `int32 Priority = 0;` — `UPROPERTY(EditAnywhere, Category = "Transitions")` — Priority of Transition @note the lower the number, the higher the priority
- L123 _private member_ `bool bWaitForTasksToFinish = true;` — `UPROPERTY(EditAnywhere, Category = "Transitions")`
- L127 _private member_ `FGuid ParametersId;` — `UPROPERTY(VisibleAnywhere, Category = "Parameters")` — Identifier for the Parameters Struct Id
- L131 _private member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category = "Parameters")` — Parameters to feed into the Transition via the "Transition Parameters" node

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/SceneStateMachineGraph.h` (Public)


#### class `USceneStateMachineGraph`  
`class USceneStateMachineGraph : public UEdGraph`  
_L16-79_
- reflection: `UCLASS(MinimalAPI, HideCategories=(Graph))`
- inherits: `UEdGraph`
- L21 _public typedef_ `using FOnParametersChanged = TMulticastDelegate<void(USceneStateMachineGraph*)>;`
- L23 _public prototype_ `USceneStateMachineGraph();`
- L25 _public prototype_ `static FOnParametersChanged::RegistrationType& OnParametersChanged();`
- L27 _public prototype_ `void NotifyParametersChanged();`
- L29 _public prototype_ `USceneStateMachineEntryNode* GetEntryNode() const;`
- L32 _public prototype_ `USceneStateMachineStateNode* GetParentStateNode() const;` — Returns the parent node if it's a state machine nested in a state node
- L35 _public prototype_ `bool IsRootStateMachine() const;` — Returns whether the state machine is at the root level (i.e. directly under the blueprint and not nested under a state node)
- L38 _public prototype_ `UE_INTERNAL TOptional<uint16> GetCompiledIndex() const;` — Get the index to the state machine this node compiled to last
- L41 _public prototype_ `UE_INTERNAL void SetCompiledIndex(uint16 InCompiledIndex);` — Sets the index to the state machine this node compiled to last
- L44 _public prototype_ `virtual void AddNode(UEdGraphNode* InNodeToAdd, bool bInUserAction, bool bInSelectNewNode) override;`
- L48 _public prototype_ `virtual void PostInitProperties() override;`
- L49 _public prototype_ `virtual void PostLoad() override;`
- L50 _public prototype_ `virtual void PostDuplicate(bool bInDuplicateForPIE) override;`
- L51 _public prototype_ `virtual void PostEditImport() override;`
- L52 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L56 _public prototype_ `void GenerateNewParametersId();` — Called to set a new unique id for parameters (e.g. after duplicating)
- L60 _public member_ `FText Category;` — `UPROPERTY(EditAnywhere, Category="State Machine")` — Category of the State Machine
- L64 _public member_ `FGuid ParametersId;` — `UPROPERTY(VisibleAnywhere, Category="State Machine")` — Identifier for the Parameters Struct Id
- L67 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY(EditAnywhere, Category="State Machine")`
- L71 _public member_ `ESceneStateMachineRunMode RunMode = ESceneStateMachineRunMode::Auto;` — `UPROPERTY(EditAnywhere, Category="State Machine")` — The run-mode for the State Machine. Currently only applies to Top-Level State Machines
- L76 _private member_ `TOptional<uint16> CompiledIndex;` — `UPROPERTY()` — Index to the state machine this graph compiled to last.
- L78 _private member_ `static FOnParametersChanged OnParametersChangedDelegate;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/SceneStateMachineGraphEnums.h` (Public)


#### enum `UE::SceneState::Graph::EStateMachineNodeType`  
`enum class EStateMachineNodeType : uint8`  
_L11-20_
- desc: Type of state machine node
- L13 _public enumerator_ `Unspecified`
- L14 _public enumerator_ `Entry`
- L15 _public enumerator_ `Exit`
- L16 _public enumerator_ `State`
- L17 _public enumerator_ `Transition`
- L18 _public enumerator_ `Task`
- L19 _public enumerator_ `Conduit`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Graph` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/SceneStateMachineGraphSchema.h` (Public)


#### class `USceneStateMachineGraphSchema`  
`class USceneStateMachineGraphSchema : public UEdGraphSchema`  
_L14-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L20 _public member_ `static const FName PN_In;` — Pin Names
- L21 _public member_ `static const FName PN_Out;`
- L22 _public member_ `static const FName PN_Task;`
- L25 _public member_ `static const FName PC_Transition;` — Pin Categories
- L26 _public member_ `static const FName PC_Task;`
- L29 _public member_ `static const FLinearColor PCC_Transition;` — Pin Category Colors
- L30 _public member_ `static const FLinearColor PCC_Task;`
- L33 _public prototype_ `static USceneStateMachineStateNode* FindConnectedStateNode(const UEdGraphNode* InTaskNode);` — Attempts to find the State Node connected to the given Task Node
- L36 _public prototype_ `virtual EGraphType GetGraphType(const UEdGraph* InGraph) const override;`
- L37 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& InGraph) const override;`
- L38 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& InContextMenuBuilder) const override;`
- L39 _public prototype_ `virtual void GetContextMenuActions(UToolMenu* InMenu, UGraphNodeContextMenuContext* InContext) const override;`
- L40 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* InSourcePin, const UEdGraphPin* InTargetPin) const override;`
- L41 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* InSourcePin, UEdGraphPin* InTargetPin) const override;`
- L42 _public prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* InSourcePin, UEdGraphPin* InTargetPin) const override;`
- L43 _public prototype_ `virtual bool TryRelinkConnectionTarget(UEdGraphPin* InSourcePin, UEdGraphPin* InOldTargetPin, UEdGraphPin* InNewTargetPin, const TArray<UEdGraphNode*>& InSelectedGraphNodes) const override;`
- L44 _public prototype_ `virtual bool IsConnectionRelinkingAllowed(UEdGraphPin* InPin) const override;`
- L45 _public prototype_ `virtual const FPinConnectionResponse CanRelinkConnectionToPin(const UEdGraphPin* InOldSourcePin, const UEdGraphPin* InTargetPin) const override;`
- L46 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& InPinType) const override;`
- L47 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& InGraph, FGraphDisplayInfo& OutDisplayInfo) const override;`
- L48 _public prototype_ `virtual void BreakNodeLinks(UEdGraphNode& InTargetNode) const override;`
- L49 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& InTargetPin, bool bInSendsNodeNotification) const override;`
- L50 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* InSourcePin, UEdGraphPin* InTargetPin) const override;`
- L60 _public prototype_ `void CreateConnectionWithTransition(const FTransitionConnectionParams& InParams) const;`
- L64 _private prototype_ `void GetGraphContextCoreActions(FGraphContextMenuBuilder& InContextMenuBuilder) const;` — Gathers the core actions for the context menu
- L67 _private prototype_ `void GetGraphContextTaskActions(FGraphContextMenuBuilder& InContextMenuBuilder) const;` — Gathers the task actions for the context menu

#### struct `USceneStateMachineGraphSchema::FTransitionConnectionParams`  
`struct FTransitionConnectionParams`  
_L53-59_
- L55 _public member_ `USceneStateMachineNode* SourceNode;`
- L56 _public member_ `USceneStateMachineNode* TargetNode;`
- L57 _public member_ `UEdGraphPin* SourcePin;`
- L58 _public member_ `UEdGraphPin* TargetPin;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/SceneStateMachineGraphUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENESTATEMACHINEGRAPH_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L15 _prototype_ `bool CanDirectlyRemoveGraph(UEdGraph* InGraph);` (scope `UE::SceneState::Graph`)
- L17 _prototype_ `void RemoveGraph(UEdGraph* InGraph);` (scope `UE::SceneState::Graph`)
- L20 _prototype_ `FEdGraphPinType GetPropertyDescAsPin(const FPropertyBagPropertyDesc& InPropertyDesc);` (scope `UE::SceneState::Graph`) — Gets the given property desc as a pin compatible for blueprints

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineGraph/Public/Transition/SceneStateTransitionParametersNode.h` (Public)


#### class `USceneStateTransitionParametersNode`  
`class USceneStateTransitionParametersNode : public UK2Node_EditablePinBase`  
_L12-53_
- reflection: `UCLASS(MinimalAPI, DisplayName="Transition Parameters")`
- inherits: `UK2Node_EditablePinBase`
- L17 _public prototype_ `USceneStateTransitionParametersNode();`
- L19 _public prototype_ `void OnTransitionParametersChanged(USceneStateMachineTransitionNode& InTransitionNode);`
- L23 _protected prototype_ `void BuildParameterPins();` — Builds the pins matching the outer state machine graph's parameters
- L26 _protected prototype_ `bool IsStructurallyEqual(TConstArrayView<FPropertyBagPropertyDesc> InPropertyDescs) const;` — Returns whether the Pin structure is equal with the property desc structure (i.e. same count, same names and same types)
- L29 _protected prototype_ `void ClearPins();` — Removes all the user pin definitions and pins from this node
- L32 _protected prototype_ `virtual UEdGraphPin* CreatePinFromUserDefinition(const TSharedPtr<FUserPinInfo> InNewPinInfo) override;`
- L33 _protected prototype_ `virtual bool CanCreateUserDefinedPin(const FEdGraphPinType& InPinType, EEdGraphPinDirection InDesiredDirection, FText& OutErrorMessage) override;`
- L34 _protected prototype_ `virtual bool ModifyUserDefinedPinDefaultValue(TSharedPtr<FUserPinInfo> InPinInfo, const FString& InNewDefaultValue) override;`
- L38 _protected prototype_ `virtual bool IsNodePure() const override;`
- L39 _protected prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& InActionRegistrar) const override;`
- L43 _protected prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type InTitleType) const override;`
- L44 _protected prototype_ `virtual void AllocateDefaultPins() override;`
- L48 _protected prototype_ `virtual void BeginDestroy() override;`
- L52 _private member_ `FDelegateHandle OnParametersChangedHandle;`
