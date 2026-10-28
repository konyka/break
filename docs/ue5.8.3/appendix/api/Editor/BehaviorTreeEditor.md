# Editor / BehaviorTreeEditor

- module root: `Source/Editor/BehaviorTreeEditor`
- headers: 46; symbols: 1143
- symbol kinds: class=53, delegate=14, enum=4, enumerator=12, externvar=1, function=38, macro=13, member=274, namespace=15, prototype=665, struct=15, typedef=4, variable=35
- PrivateDependencyModuleNames: AIGraph, AIModule, ApplicationCore, AssetDefinition, Core, CoreUObject, EditorWidgets, Engine, GameplayTags, GraphEditor, InputCore, KismetWidgets, PropertyEditor, RewindDebuggerInterface, Slate, SlateCore, ToolMenus, TraceServices, UnrealEd

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeDecoratorGraph.h` (Public)


#### class `UBehaviorTreeDecoratorGraph`  
`class UBehaviorTreeDecoratorGraph : public UEdGraph`  
_L22-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraph`
- L26 _private prototype_ `void CollectDecoratorData(TArray<class UBTDecorator*>& DecoratorInstances, TArray<struct FBTDecoratorLogic>& DecoratorOperations) const;`
- L27 _private prototype_ `int32 SpawnMissingNodes(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32 StartIndex);`
- L31 _protected prototype_ `const class UBehaviorTreeDecoratorGraphNode* FindRootNode() const;`
- L32 _protected prototype_ `void CollectDecoratorDataWorker(const class UBehaviorTreeDecoratorGraphNode* Node, TArray<class UBTDecorator*>& DecoratorInstances, TArray<struct FBTDecoratorLogic>& DecoratorOperations) const;`
- L34 _protected prototype_ `UEdGraphPin* FindFreePin(UEdGraphNode* Node, EEdGraphPinDirection Direction);`
- L35 _protected prototype_ `UBehaviorTreeDecoratorGraphNode* SpawnMissingNodeWorker(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32& Index, UEdGraphNode* ParentGraphNode, int32 ChildIdx);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeDecoratorGraphNode.h` (Public)


#### class `UBehaviorTreeDecoratorGraphNode`  
`class UBehaviorTreeDecoratorGraphNode : public UEdGraphNode`  
_L19-43_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L24 _private prototype_ `virtual class UBehaviorTreeDecoratorGraph* GetDecoratorGraph();` — Get the BT graph that owns this node
- L26 _private prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L29 _private prototype_ `virtual UEdGraphPin* GetInputPin(int32 InputIndex=0) const;` — @return the input pin for this state
- L31 _private prototype_ `virtual UEdGraphPin* GetOutputPin(int32 InputIndex=0) const;` — @return the output pin for this state
- L33 _private prototype_ `virtual EBTDecoratorLogic::Type GetOperationType() const;`
- L36 _private member_ `uint32 bAllowModifingInputs : 1;` — allow creating / removing inputs
- L38 _private prototype_ `virtual void NodeConnectionListChanged() override;`
- L40 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L42 _private prototype_ `virtual bool CanUserDeleteNode() const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeDecoratorGraphNode_Decorator.h` (Public)


#### class `UBehaviorTreeDecoratorGraphNode_Decorator`  
`class UBehaviorTreeDecoratorGraphNode_Decorator : public UBehaviorTreeDecoratorGraphNode`  
_L21-47_
- reflection: `UCLASS()`
- inherits: `UBehaviorTreeDecoratorGraphNode`
- L26 _private member_ `TObjectPtr<UObject> NodeInstance;` — `UPROPERTY()`
- L29 _private member_ `FGraphNodeClassData ClassData;` — `UPROPERTY()`
- L31 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L32 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L33 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L35 _private prototype_ `virtual EBTDecoratorLogic::Type GetOperationType() const override;`
- L37 _private prototype_ `virtual void PostEditImport() override;`
- L38 _private prototype_ `virtual void PostEditUndo() override;`
- L39 _private prototype_ `virtual void PrepareForCopying() override;`
- L40 _private prototype_ `void PostCopyNode();`
- L41 _private prototype_ `bool RefreshNodeClass();`
- L42 _private prototype_ `void UpdateNodeClassData();`
- L46 _protected prototype_ `virtual void ResetNodeOwner();`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeDecoratorGraphNode_Logic.h` (Public)


#### enum `EDecoratorLogicMode::Type`  
`enum Type : int`  
_L22-28_
- L24 _public enumerator_ `Sink`
- L25 _public enumerator_ `And`
- L26 _public enumerator_ `Or`
- L27 _public enumerator_ `Not`

#### class `UBehaviorTreeDecoratorGraphNode_Logic`  
`class UBehaviorTreeDecoratorGraphNode_Logic : public UBehaviorTreeDecoratorGraphNode`  
_L32-53_
- reflection: `UCLASS()`
- inherits: `UBehaviorTreeDecoratorGraphNode`
- L37 _private member_ `TEnumAsByte<EDecoratorLogicMode::Type> LogicMode;` — `UPROPERTY()`
- L39 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L40 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L41 _private prototype_ `virtual bool CanUserDeleteNode() const override;`
- L42 _private prototype_ `virtual EBTDecoratorLogic::Type GetOperationType() const override;`
- L44 _private prototype_ `virtual void GetMenuEntries(struct FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L46 _private prototype_ `bool CanRemovePins() const;`
- L47 _private prototype_ `bool CanAddPins() const;`
- L49 _private prototype_ `UEdGraphPin* AddInputPin();`
- L50 _private prototype_ `void RemoveInputPin(class UEdGraphPin* Pin);`
- L52 _private prototype_ `EDecoratorLogicMode::Type GetLogicMode(EBTDecoratorLogic::Type Op) const;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace EDecoratorLogicMode`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeEditorTypes.h` (Public)


#### struct `FAbortDrawHelper`  
`struct FAbortDrawHelper`  
_L20-28_
- L22 _public member_ `uint16 AbortStart;`
- L23 _public member_ `uint16 AbortEnd;`
- L24 _public member_ `uint16 SearchStart;`
- L25 _public member_ `uint16 SearchEnd;`
- L27 _public function_ `FAbortDrawHelper() : AbortStart(MAX_uint16), AbortEnd(MAX_uint16), SearchStart(MAX_uint16), SearchEnd(MAX_uint16)`

#### struct `FCompareNodeXLocation`  
`struct FCompareNodeXLocation`  
_L30-44_
- L32 _public function_ `FORCEINLINE bool operator()(const UEdGraphPin& A, const UEdGraphPin& B) const`

#### enum `ESubNode::Type`  
`enum Type`  
_L48-51_
- L49 _public enumerator_ `Decorator`
- L50 _public enumerator_ `Service`

#### struct `FNodeBounds`  
`struct FNodeBounds`  
_L54-64_
- L56 _public member_ `FDeprecateSlateVector2D Position;`
- L57 _public member_ `FDeprecateSlateVector2D Size;`
- L59 _public function_ `FNodeBounds(UE::Slate::FDeprecateVector2DParameter InPos, UE::Slate::FDeprecateVector2DParameter InSize) : Position(InPos) , Size(InSize)`

#### class `UBehaviorTreeEditorTypes`  
`class UBehaviorTreeEditorTypes : public UObject`  
_L67-75_
- reflection: `UCLASS()`
- inherits: `UObject`
- L71 _private member_ `static const FName PinCategory_MultipleNodes;`
- L72 _private member_ `static const FName PinCategory_SingleComposite;`
- L73 _private member_ `static const FName PinCategory_SingleTask;`
- L74 _private member_ `static const FName PinCategory_SingleNode;`

#### Free symbols / members of external scopes

- L46 _namespace_ `namespace ESubNode`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeFactory.h` (Public)


#### class `UBehaviorTreeFactory`  
`class UBehaviorTreeFactory : public UFactory`  
_L20-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L25 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;` — UFactory interface
- L26 _private prototype_ `virtual bool CanCreateNew() const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraph.h` (Public)


#### class `UBehaviorTreeGraph`  
`class UBehaviorTreeGraph : public UAIGraph`  
_L21-81_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraph`
- L34 _private member_ `int32 ModCounter;` — `UPROPERTY()` — increased with every graph rebuild, used to refresh data from subtrees
- L37 _private member_ `bool bIsUsingModCounter;` — `UPROPERTY()`
- L40 _private member_ `TSubclassOf<UBehaviorTreeGraphNode_Root> RootNodeClass;` — `UPROPERTY()`
- L42 _private prototype_ `virtual void OnCreated() override;`
- L43 _private prototype_ `virtual void OnLoaded() override;`
- L44 _private prototype_ `virtual void Initialize() override;`
- L45 _private prototype_ `void OnSave();`
- L47 _private prototype_ `virtual void UpdateVersion() override;`
- L48 _private prototype_ `virtual void MarkVersion() override;`
- L49 _private prototype_ `virtual void UpdateAsset(int32 UpdateFlags = 0) override;`
- L50 _private prototype_ `virtual void OnSubNodeDropped() override;`
- L52 _private function_ `virtual bool DoesSupportServices() const`
- L54 _private prototype_ `void UpdateBlackboardChange();`
- L55 _private prototype_ `void UpdateAbortHighlight(struct FAbortDrawHelper& Mode0, struct FAbortDrawHelper& Mode1);`
- L56 _private prototype_ `void CreateBTFromGraph(class UBehaviorTreeGraphNode* RootEdNode);`
- L57 _private prototype_ `void SpawnMissingNodes();`
- L58 _private prototype_ `void UpdatePinConnectionTypes();`
- L59 _private prototype_ `bool UpdateInjectedNodes();`
- L60 _private prototype_ `void UpdateBrokenComposites();`
- L61 _private prototype_ `class UEdGraphNode* FindInjectedNode(int32 Index);`
- L62 _private prototype_ `void ReplaceNodeConnections(UEdGraphNode* OldNode, UEdGraphNode* NewNode);`
- L63 _private prototype_ `void RebuildExecutionOrder();`
- L64 _private prototype_ `void RebuildChildOrder(UEdGraphNode* ParentNode);`
- L65 _private prototype_ `void SpawnMissingNodesForParallel();`
- L66 _private prototype_ `void RemoveUnknownSubNodes();`
- L68 _private prototype_ `void AutoArrange();`
- L72 _protected prototype_ `void CollectAllNodeInstances(TSet<UObject*>& NodeInstances) override;`
- L75 _protected prototype_ `virtual void PostEditUndo() override;`
- L78 _protected prototype_ `void UpdateVersion_UnifiedSubNodes();`
- L79 _protected prototype_ `void UpdateVersion_InnerGraphWhitespace();`
- L80 _protected prototype_ `void UpdateVersion_RunBehaviorInSeparateGraph();`

#### enum `UBehaviorTreeGraph::EUpdateFlags`  
`enum EUpdateFlags`  
_L25-30_
- L27 _public enumerator_ `RebuildGraph = 0`
- L28 _public enumerator_ `ClearDebuggerFlags = 1`
- L29 _public enumerator_ `KeepRebuildCounter = 2`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode.h` (Public)


#### class `UBehaviorTreeGraphNode`  
`class UBehaviorTreeGraphNode : public UAIGraphNode`  
_L27-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraphNode`
- L33 _private member_ `TArray<TObjectPtr<UBehaviorTreeGraphNode>> Decorators;` — `UPROPERTY()` — only some of behavior tree nodes support decorators
- L37 _private member_ `TArray<TObjectPtr<UBehaviorTreeGraphNode>> Services;` — `UPROPERTY()` — only some of behavior tree nodes support services
- L40 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L41 _private prototype_ `virtual FText GetTooltipText() const override;`
- L42 _private prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L43 _private prototype_ `virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;`
- L44 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L48 _private prototype_ `virtual void PostEditUndo() override;`
- L51 _private prototype_ `virtual FText GetDescription() const override;`
- L52 _private prototype_ `virtual bool HasErrors() const override;`
- L53 _private prototype_ `virtual void InitializeInstance() override;`
- L54 _private prototype_ `virtual void OnSubNodeAdded(UAIGraphNode* SubNode) override;`
- L55 _private prototype_ `virtual void OnSubNodeRemoved(UAIGraphNode* SubNode) override;`
- L56 _private prototype_ `virtual void RemoveAllSubNodes() override;`
- L57 _private prototype_ `virtual int32 FindSubNodeDropIndex(UAIGraphNode* SubNode) const override;`
- L58 _private prototype_ `virtual void InsertSubNodeAt(UAIGraphNode* SubNode, int32 DropIndex) override;`
- L59 _private prototype_ `virtual void UpdateErrorMessage() override;`
- L62 _private prototype_ `virtual UBehaviorTreeGraph* GetBehaviorTreeGraph();` — `UE_DEPRECATED(5.4, "Use GetOwnerBehaviorTreeGraph instead.")`
- L63 _private prototype_ `virtual UBehaviorTreeGraph* GetOwnerBehaviorTreeGraph() const;`
- L65 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const;`
- L68 _private function_ `virtual bool CanPlaceBreakpoints() const` — check if node can accept breakpoints
- L70 _private prototype_ `void ClearDebuggerState();`
- L73 _private prototype_ `virtual const ISlateStyle& GetNameIconStyleSet() const;` — gets the style set from which GetNameIcon is queried
- L76 _private prototype_ `virtual FName GetNameIcon() const;` — gets icon resource name for title bar
- L80 _private member_ `uint32 bInjectedNode : 1;` — `UPROPERTY()` — if set, this node was injected from subtree and shouldn't be edited
- L83 _private member_ `uint32 bRootLevel : 1;` — if set, this node is root of tree or sub node of it
- L86 _private member_ `uint32 bHasObserverError : 1;` — if set, observer setting is invalid (injected nodes only)
- L89 _private member_ `uint32 bHighlightInAbortRange0 : 1;` — highlighting nodes in abort range for more clarity when setting up decorators
- L92 _private member_ `uint32 bHighlightInAbortRange1 : 1;` — highlighting nodes in abort range for more clarity when setting up decorators
- L95 _private member_ `uint32 bHighlightInSearchRange0 : 1;` — highlighting connections in search range for more clarity when setting up decorators
- L98 _private member_ `uint32 bHighlightInSearchRange1 : 1;` — highlighting connections in search range for more clarity when setting up decorators
- L101 _private member_ `uint32 bHighlightInSearchTree : 1;` — highlighting nodes during quick find
- L104 _private member_ `uint32 bHighlightChildNodeIndices : 1;` — highlight other child node indexes when hovering over a child
- L107 _private member_ `uint32 bHasBreakpoint : 1;` — debugger flag: breakpoint exists
- L110 _private member_ `uint32 bIsBreakpointEnabled : 1;` — debugger flag: breakpoint is enabled
- L113 _private member_ `uint32 bDebuggerMarkCurrentlyActive : 1;` — debugger flag: mark node as active (current state)
- L116 _private member_ `uint32 bDebuggerMarkPreviouslyActive : 1;` — debugger flag: mark node as active (browsing previous states)
- L119 _private member_ `uint32 bDebuggerMarkFlashActive : 1;` — debugger flag: briefly flash active node
- L122 _private member_ `uint32 bDebuggerMarkSearchSucceeded : 1;` — debugger flag: mark as succeeded search path
- L125 _private member_ `uint32 bDebuggerMarkSearchFailed : 1;` — debugger flag: mark as failed on search path
- L128 _private member_ `uint32 bDebuggerMarkSearchTrigger : 1;` — debugger flag: mark as trigger of search path
- L131 _private member_ `uint32 bDebuggerMarkSearchFailedTrigger : 1;` — debugger flag: mark as trigger of discarded search path
- L134 _private member_ `uint32 bDebuggerMarkSearchReverseConnection : 1;` — debugger flag: mark as going to parent
- L137 _private member_ `uint32 bDebuggerMarkBreakpointTrigger : 1;` — debugger flag: mark stopped on this breakpoint
- L140 _private member_ `int32 DebuggerSearchPathIndex;` — debugger variable: index on search path
- L143 _private member_ `int32 DebuggerSearchPathSize;` — debugger variable: number of nodes on search path
- L146 _private member_ `int32 DebuggerUpdateCounter;` — debugger variable: incremented on change of debugger flags for render updates
- L149 _private member_ `FString DebuggerRuntimeDescription;` — used to show node's runtime description rather than static one
- L154 _protected prototype_ `void CreateAddDecoratorSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;` — creates add decorator... submenu
- L157 _protected prototype_ `void CreateAddServiceSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;` — creates add service... submenu
- L160 _protected prototype_ `void AddContextMenuActionsDecorators(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const;` — add right click menu to create subnodes: Decorators
- L163 _protected prototype_ `void AddContextMenuActionsServices(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const;` — add right click menu to create subnodes: Services

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_Composite.h` (Public)


#### class `UBehaviorTreeGraphNode_Composite`  
`class UBehaviorTreeGraphNode_Composite : public UBehaviorTreeGraphNode`  
_L19-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- L23 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual FText GetDescription() const override;`
- L25 _private prototype_ `virtual FText GetTooltipText() const override;`
- L26 _private function_ `virtual bool RefreshNodeClass() override`
- L29 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — Gets a list of actions that can be done to this particular node
- L32 _private function_ `virtual bool CanPlaceBreakpoints() const override` — check if node can accept breakpoints
- L34 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`
- L38 _protected prototype_ `virtual void PostPasteNode() override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_CompositeDecorator.h` (Public)


#### class `UBehaviorTreeGraphNode_CompositeDecorator`  
`class UBehaviorTreeGraphNode_CompositeDecorator : public UBehaviorTreeGraphNode`  
_L26-96_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- L32 _private member_ `TObjectPtr<class UEdGraph> BoundGraph;` — `UPROPERTY()` — The logic graph for this decorator (returning a boolean)
- L35 _private member_ `FString CompositeName;` — `UPROPERTY(EditAnywhere, Category=Description)`
- L39 _private member_ `uint32 bShowOperations : 1;` — `UPROPERTY(EditAnywhere, Category=Description)` — if set, all logic operations will be shown in description
- L43 _private member_ `uint32 bCanAbortFlow : 1;` — `UPROPERTY()` — updated with internal graph changes, set when decorators inside can abort flow
- L45 _private member_ `uint32 bHasBrokenInstances : 1;`
- L47 _private member_ `TSubclassOf<UBehaviorTreeDecoratorGraph> GraphClass;`
- L49 _private prototype_ `FString GetNodeTypeDescription() const;`
- L50 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L51 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L52 _private prototype_ `virtual FText GetDescription() const override;`
- L53 _private prototype_ `virtual FText GetTooltipText() const override;`
- L54 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L55 _private prototype_ `virtual void PostLoad() override;`
- L56 _private function_ `virtual UEdGraph* GetBoundGraph() const override`
- L57 _private prototype_ `virtual bool IsSubNode() const override;`
- L58 _private prototype_ `virtual bool HasErrors() const override;`
- L59 _private prototype_ `virtual bool RefreshNodeClass() override;`
- L60 _private prototype_ `virtual void UpdateNodeClassData() override;`
- L62 _private prototype_ `virtual void PrepareForCopying() override;`
- L63 _private prototype_ `virtual void PostCopyNode() override;`
- L64 _private prototype_ `virtual void PostPasteNode() override;`
- L66 _private prototype_ `int32 SpawnMissingNodes(const TArray<class UBTDecorator*>& NodeInstances, const TArray<struct FBTDecoratorLogic>& Operations, int32 StartIndex);`
- L67 _private prototype_ `void CollectDecoratorData(TArray<class UBTDecorator*>& NodeInstances, TArray<struct FBTDecoratorLogic>& Operations) const;`
- L68 _private prototype_ `void SetDecoratorData(class UBTCompositeNode* InParentNode, uint8 InChildIndex);`
- L69 _private prototype_ `void InitializeDecorator(class UBTDecorator* InnerDecorator);`
- L70 _private prototype_ `void OnBlackboardUpdate();`
- L71 _private prototype_ `void OnInnerGraphChanged();`
- L72 _private prototype_ `void BuildDescription();`
- L73 _private prototype_ `void UpdateBrokenInstances();`
- L75 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L77 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`
- L79 _private prototype_ `void ResetExecutionRange();`
- L82 _private member_ `uint16 FirstExecutionIndex;` — Execution index range of internal nodes, used by debugger
- L83 _private member_ `uint16 LastExecutionIndex;`
- L86 _protected prototype_ `void CreateBoundGraph();`
- L87 _protected prototype_ `virtual void ResetNodeOwner() override;`
- L90 _protected member_ `TObjectPtr<class UBTCompositeNode> ParentNodeInstance;` — `UPROPERTY()`
- L92 _protected member_ `uint8 ChildIndex;`
- L95 _protected member_ `FString CachedDescription;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_Decorator.h` (Public)


#### class `UBehaviorTreeGraphNode_Decorator`  
`class UBehaviorTreeGraphNode_Decorator : public UBehaviorTreeGraphNode`  
_L18-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L23 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L24 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`
- L25 _private prototype_ `void CollectDecoratorData(TArray<class UBTDecorator*>& NodeInstances, TArray<struct FBTDecoratorLogic>& Operations) const;`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_Root.h` (Public)


#### class `UBehaviorTreeGraphNode_Root`  
`class UBehaviorTreeGraphNode_Root : public UBehaviorTreeGraphNode`  
_L22-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- desc: Root node of this behavior tree, holds Blackboard data
- L27 _private member_ `TObjectPtr<class UBlackboardData> BlackboardAsset;` — `UPROPERTY(EditAnywhere, Category="AI|BehaviorTree")`
- L29 _private prototype_ `virtual void PostPlacedNewNode() override;`
- L30 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L31 _private function_ `virtual bool CanDuplicateNode() const override`
- L32 _private function_ `virtual bool CanUserDeleteNode() const override`
- L33 _private function_ `virtual bool HasErrors() const override`
- L34 _private function_ `virtual bool RefreshNodeClass() override`
- L35 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L37 _private prototype_ `virtual FName GetNameIcon() const override;` — gets icon resource name for title bar
- L38 _private prototype_ `virtual FText GetTooltipText() const override;`
- L40 _private prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L41 _private prototype_ `virtual void PostEditUndo() override;`
- L42 _private prototype_ `virtual FText GetDescription() const override;`
- L44 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`
- L47 _private prototype_ `void UpdateBlackboard();` — notify behavior tree about blackboard change

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_Service.h` (Public)


#### class `UBehaviorTreeGraphNode_Service`  
`class UBehaviorTreeGraphNode_Service : public UBehaviorTreeGraphNode`  
_L17-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- L21 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L22 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L23 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_SimpleParallel.h` (Public)


#### class `UBehaviorTreeGraphNode_SimpleParallel`  
`class UBehaviorTreeGraphNode_SimpleParallel : public UBehaviorTreeGraphNode_Composite`  
_L17-23_
- reflection: `UCLASS()`
- inherits: `UBehaviorTreeGraphNode_Composite`
- L21 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L22 _private prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_SubtreeTask.h` (Public)


#### class `UBehaviorTreeGraphNode_SubtreeTask`  
`class UBehaviorTreeGraphNode_SubtreeTask : public UBehaviorTreeGraphNode_Task`  
_L17-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode_Task`
- L22 _private member_ `int32 SubtreeVersion;` — UBehaviorTreeGraph.UpdateCounter value of subtree graph
- L25 _private member_ `FString SubtreePath;` — path of behavior tree asset used to create injected nodes preview
- L28 _private prototype_ `bool UpdateInjectedNodes();` — updates nodes injected from subtree's root
- L30 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/BehaviorTreeGraphNode_Task.h` (Public)


#### class `UBehaviorTreeGraphNode_Task`  
`class UBehaviorTreeGraphNode_Task : public UBehaviorTreeGraphNode`  
_L17-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBehaviorTreeGraphNode`
- L21 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L22 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L24 _private prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — Gets a list of actions that can be done to this particular node
- L26 _private function_ `virtual bool CanPlaceBreakpoints() const override`
- L27 _private prototype_ `virtual FLinearColor GetBackgroundColor(bool bIsActiveForDebugger) const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/BlackboardDataFactory.h` (Public)


#### class `UBlackboardDataFactory`  
`class UBlackboardDataFactory : public UFactory`  
_L18-26_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L23 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;` — UFactory interface
- L24 _private prototype_ `virtual bool CanCreateNew() const override;`

### `Source/Editor/BehaviorTreeEditor/Classes/EdGraphSchema_BehaviorTree.h` (Public)


#### struct `FBehaviorTreeSchemaAction_AutoArrange`  
`struct FBehaviorTreeSchemaAction_AutoArrange : public FEdGraphSchemaAction`  
_L38-52_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to auto arrange the graph
- L42 _public function_ `FBehaviorTreeSchemaAction_AutoArrange() : FEdGraphSchemaAction()`
- L45 _public function_ `FBehaviorTreeSchemaAction_AutoArrange(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L50 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `UEdGraphSchema_BehaviorTree`  
`class UEdGraphSchema_BehaviorTree : public UAIGraphSchema`  
_L55-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraphSchema`
- L60 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L61 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L62 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L63 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L64 _private prototype_ `virtual const FPinConnectionResponse CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const override;`
- L65 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L66 _private prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L67 _private prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L68 _private prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L69 _private prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L72 _private prototype_ `virtual void GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, int32 SubNodeFlags) const override;`
- L73 _private prototype_ `virtual void GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const override;`
- L75 _private member_ `TSubclassOf<UBehaviorTreeGraphNode_CompositeDecorator> CompositeDecoratorClass;`
- L76 _private member_ `TSubclassOf<UBehaviorTreeGraphNode_Decorator> DecoratorClass;`
- L77 _private member_ `TSubclassOf<UBehaviorTreeGraphNode_Task> TaskClass;`
- L78 _private member_ `TSubclassOf<UBehaviorTreeGraphNode_Service> ServiceClass;`
- L81 _protected prototype_ `virtual FGraphNodeClassHelper& GetClassCache() const;`
- L82 _protected prototype_ `virtual bool IsNodeSubtreeTask(const FGraphNodeClassData& NodeClass) const;`
- L86 _private member_ `static int32 CurrentCacheRefreshID;` — ID for checking dirty status of node titles against, increases whenever

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/EdGraphSchema_BehaviorTreeDecorator.h` (Public)


#### struct `FDecoratorSchemaAction_NewNode`  
`struct FDecoratorSchemaAction_NewNode : public FEdGraphSchemaAction`  
_L34-66_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L40 _public member_ `TObjectPtr<class UBehaviorTreeDecoratorGraphNode> NodeTemplate;` — `UPROPERTY()` — Template of node we want to create
- L42 _public function_ `FDecoratorSchemaAction_NewNode() : FEdGraphSchemaAction() , NodeTemplate(nullptr)`
- L47 _public function_ `FDecoratorSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping) , NodeTemplate(nullptr)`
- L53 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L54 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, TArray<UEdGraphPin*>& FromPins, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L55 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L59 _public function_ `template <typename NodeType> static NodeType* SpawnNodeFromTemplate(class UEdGraph* ParentGraph, NodeType* InTemplateNode, const FVector2f& Location)`

#### class `UEdGraphSchema_BehaviorTreeDecorator`  
`class UEdGraphSchema_BehaviorTreeDecorator : public UEdGraphSchema`  
_L69-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L74 _private member_ `FString PC_Boolean;` — `UPROPERTY()`
- L76 _private prototype_ `void AddPin(class UEdGraphNode* InGraphNode);`
- L77 _private prototype_ `void RemovePin(class UEdGraphPin* InGraphPin);`
- L80 _private prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L81 _private prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L82 _private prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L83 _private function_ `virtual FName GetParentContextMenuName() const override`
- L84 _private prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L85 _private prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L86 _private prototype_ `virtual bool ShouldHidePinDefaultValue(UEdGraphPin* Pin) const override;`
- L87 _private prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L88 _private prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L89 _private prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L92 _private prototype_ `static TSharedPtr<FDecoratorSchemaAction_NewNode> AddNewDecoratorAction(FGraphContextMenuBuilder& ContextMenuBuilder, const FText& Category, const FText& MenuDesc, const FText& Tooltip);`
- L95 _protected prototype_ `virtual FGraphNodeClassHelper& GetClassCache() const;`
- L98 _private member_ `inline static int32 CurrentCacheRefreshID = 0;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Classes/ValueOrBBKeyDetails.h` (Public)


#### class `FValueOrBBKeyDetails`  
`class FValueOrBBKeyDetails : public IPropertyTypeCustomization`  
_L25-52_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L34 _public prototype_ `bool CanEditDefaultValue() const;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> KeyProperty;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> DefaultValueProperty;`
- L40 _protected member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`
- L41 _protected member_ `TArray<FName> MatchingKeys;`
- L43 _protected prototype_ `virtual void ValidateData();`
- L44 _protected prototype_ `virtual TSharedRef<SWidget> CreateDefaultValueWidget();`
- L46 _protected prototype_ `void GetMatchingKeys(TArray<FName>& OutNames);`
- L47 _protected prototype_ `bool HasAccessToBlackboard() const;`
- L48 _protected prototype_ `TSharedRef<SWidget> OnGetKeyNames();`
- L49 _protected prototype_ `void OnKeyChanged(int32 Index);`
- L50 _protected prototype_ `FText GetKeyDesc() const;`
- L51 _protected prototype_ `const FValueOrBlackboardKeyBase* GetDataPtr() const;`

#### class `FValueOrBBKeyDetails_Class`  
`class FValueOrBBKeyDetails_Class : public FValueOrBBKeyDetails`  
_L54-73_
- inherits: `FValueOrBBKeyDetails`
- L58 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L60 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L61 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L64 _protected member_ `TSharedPtr<IPropertyHandle> BaseClassProperty;`
- L66 _protected prototype_ `virtual void ValidateData() override;`
- L67 _protected prototype_ `virtual TSharedRef<SWidget> CreateDefaultValueWidget() override;`
- L69 _protected prototype_ `void OnBaseClassChanged();`
- L70 _protected prototype_ `void OnSetClass(const UClass* NewClass);`
- L71 _protected prototype_ `const UClass* OnGetSelectedClass() const;`
- L72 _protected prototype_ `void BrowseToClass() const;`

#### class `FValueOrBBKeyDetails_Enum`  
`class FValueOrBBKeyDetails_Enum : public FValueOrBBKeyDetails`  
_L75-96_
- inherits: `FValueOrBBKeyDetails`
- L79 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L81 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L82 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L85 _protected member_ `TSharedPtr<IPropertyHandle> EnumTypeProperty;`
- L86 _protected member_ `TSharedPtr<IPropertyHandle> NativeEnumTypeNameProperty;`
- L88 _protected prototype_ `virtual void ValidateData() override;`
- L89 _protected prototype_ `virtual TSharedRef<SWidget> CreateDefaultValueWidget() override;`
- L91 _protected prototype_ `void OnEnumSelectionChanged(int32 NewValue, ESelectInfo::Type);`
- L92 _protected prototype_ `void OnEnumTypeChanged();`
- L93 _protected prototype_ `void OnNativeEnumTypeNameChanged();`
- L94 _protected prototype_ `int32 GetEnumValue() const;`
- L95 _protected prototype_ `bool CanEditEnumType() const;`

#### class `FValueOrBBKeyDetails_Object`  
`class FValueOrBBKeyDetails_Object : public FValueOrBBKeyDetails`  
_L98-117_
- inherits: `FValueOrBBKeyDetails`
- L102 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L104 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L105 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L108 _protected member_ `TSharedPtr<IPropertyHandle> BaseClassProperty;`
- L110 _protected prototype_ `virtual void ValidateData() override;`
- L111 _protected prototype_ `virtual TSharedRef<SWidget> CreateDefaultValueWidget() override;`
- L113 _protected prototype_ `void OnBaseClassChanged();`
- L114 _protected prototype_ `void OnObjectChanged(const FAssetData& AssetData);`
- L115 _protected prototype_ `FString OnGetObjectPath() const;`
- L116 _protected prototype_ `void BrowseToObject() const;`

#### class `FValueOrBBKeyDetails_Struct`  
`class FValueOrBBKeyDetails_Struct : public FValueOrBBKeyDetails`  
_L119-130_
- inherits: `FValueOrBBKeyDetails`
- L123 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L125 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L126 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L129 _protected member_ `TSharedPtr<IPropertyHandle> EditDefaultsOnlyProperty;`

#### class `FValueOrBBKeyDetails_WithChild`  
`class FValueOrBBKeyDetails_WithChild : public FValueOrBBKeyDetails`  
_L132-138_
- inherits: `FValueOrBBKeyDetails`
- L136 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L137 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`
- L14 _namespace_ `namespace ESelectInfo`

### `Source/Editor/BehaviorTreeEditor/Private/AssetDefinition_Blackboard.h` (Private)


#### class `UAssetDefinition_Blackboard`  
`class UAssetDefinition_Blackboard : public UAssetDefinitionDefault`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeConnectionDrawingPolicy.h` (Private)


#### class `FBehaviorTreeConnectionDrawingPolicy`  
`class FBehaviorTreeConnectionDrawingPolicy : public FAIGraphConnectionDrawingPolicy`  
_L17-26_
- inherits: `FAIGraphConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph with a behavior tree schema
- L21 _public prototype_ `FBehaviorTreeConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L24 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeDebugger.h` (Private)


#### class `FBehaviorTreeDebugger`  
`class FBehaviorTreeDebugger : public FTickableGameObject`  
_L28-235_
- inherits: `FTickableGameObject`
- L31 _public prototype_ `FBehaviorTreeDebugger();`
- L32 _public prototype_ `~FBehaviorTreeDebugger();`
- L34 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L35 _public prototype_ `virtual bool IsTickable() const override;`
- L36 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L37 _public function_ `virtual bool IsTickableInEditor() const override`
- L38 _public function_ `virtual TStatId GetStatId() const override`
- L41 _public prototype_ `void Refresh();` — Refresh the debugging information we are displaying (only when paused, as Tick() updates when running)
- L43 _public prototype_ `void Setup(UBehaviorTree* InTreeAsset, TSharedRef<class FBehaviorTreeEditor> InEditorOwner);`
- L46 _public prototype_ `void CacheRootNode();` — Store the root node for easy access if we have not already
- L48 _public prototype_ `bool IsDebuggerReady() const;`
- L49 _public prototype_ `bool IsDebuggerRunning() const;`
- L50 _public prototype_ `bool IsShowingCurrentState() const;`
- L51 _public prototype_ `int32 GetShownStateIndex() const;`
- L52 _public prototype_ `bool IsBehaviorExecutionPaused() const;`
- L54 _public prototype_ `void OnObjectSelected(UObject* Object);`
- L55 _public prototype_ `void OnAIDebugSelected(const APawn* Pawn);`
- L56 _public prototype_ `void OnTreeStarted(const UBehaviorTreeComponent& OwnerComp, const UBehaviorTree& InTreeAsset);`
- L57 _public prototype_ `void OnBeginPIE(const bool bIsSimulating);`
- L58 _public prototype_ `void OnEndPIE(const bool bIsSimulating);`
- L59 _public prototype_ `void OnPausePIE(const bool bIsSimulating);`
- L61 _public prototype_ `void OnBreakpointAdded(UBehaviorTreeGraphNode* Node);`
- L62 _public prototype_ `void OnBreakpointRemoved(UBehaviorTreeGraphNode* Node);`
- L64 _public prototype_ `void StepBackInto();`
- L65 _public prototype_ `void StepBackOver();`
- L66 _public prototype_ `void StepForwardInto();`
- L67 _public prototype_ `void StepForwardOver();`
- L68 _public prototype_ `void StepOut();`
- L69 _public prototype_ `void OpenParentTree();`
- L70 _public prototype_ `void OpenSubtree();`
- L71 _public prototype_ `bool CanStepBackInto() const;`
- L72 _public prototype_ `bool CanStepBackOver() const;`
- L73 _public prototype_ `bool CanStepForwardInto() const;`
- L74 _public prototype_ `bool CanStepForwardOver() const;`
- L75 _public prototype_ `bool CanStepOut() const;`
- L76 _public prototype_ `bool CanOpenParentTree() const;`
- L77 _public prototype_ `bool CanOpenSubtree() const;`
- L79 _public prototype_ `static void StopPlaySession();`
- L80 _public prototype_ `static void PausePlaySession();`
- L81 _public prototype_ `static void ResumePlaySession();`
- L82 _public prototype_ `static bool IsPlaySessionPaused();`
- L83 _public prototype_ `static bool IsPlaySessionRunning();`
- L84 _public prototype_ `static bool IsPIESimulating();`
- L85 _public prototype_ `static bool IsPIENotSimulating();`
- L87 _public prototype_ `FString GetDebuggedInstanceDesc() const;`
- L88 _public prototype_ `FString DescribeInstance(UBehaviorTreeComponent& InstanceToDescribe) const;`
- L89 _public prototype_ `void OnInstanceSelectedInDropdown(UBehaviorTreeComponent* SelectedInstance);`
- L90 _public prototype_ `void GetMatchingInstances(TArray<UBehaviorTreeComponent*>& MatchingInstances);`
- L92 _public prototype_ `void InitializeFromParent(class FBehaviorTreeDebugger* ParentDebugger);`
- L93 _public prototype_ `bool HasContinuousNextStep() const;`
- L94 _public prototype_ `bool HasContinuousPrevStep() const;`
- L96 _public prototype_ `TOptional<FBehaviorTreeNodeDebugContext> GetDebugContextForNode(const UBTNode* Node) const;`
- L104 _public prototype_ `FText FindValueForKey(const FName& InKeyName, bool bUseCurrentState) const;` — Find a (display) value for a given key. @param	InKeyName			Key to find a value for @param	bUseCurrentState	Whether to use the current (present) state or the state at the active step index @return the value to display to the user.
- L107 _public prototype_ `double GetTimeStamp(bool bUseCurrentState) const;` — Gets the timestamp to be displayed, either current or saved
- L110 _public prototype_ `DECLARE_EVENT_OneParam(FBehaviorTreeDebugger, FOnDebuggedBlackboardChanged, UBlackboardData*);` — Delegate fired when the debugged blackboard is changed
- L111 _public function_ `FOnDebuggedBlackboardChanged& OnDebuggedBlackboardChanged()`
- L116 _private member_ `TWeakPtr<FBehaviorTreeEditor> EditorOwner;` — owning editor
- L119 _private member_ `UBehaviorTree* TreeAsset;` — asset for debugging
- L122 _private member_ `TWeakObjectPtr<class UBehaviorTreeGraphNode_Root> RootNode;` — root node in asset's graph
- L125 _private member_ `TWeakObjectPtr<class UBehaviorTreeComponent> TreeInstance;` — instance for debugging
- L128 _private member_ `int32 DebuggerInstanceIndex;` — matching debugger instance index from component's stack
- L131 _private member_ `int32 ActiveStepIndex;` — index of state from buffer to show
- L134 _private member_ `int32 DisplayedExecutionStepId;` — execution id of displayed step, used to detect changes
- L137 _private member_ `int32 LastValidExecutionStepId;` — execution id of last valid step
- L140 _private member_ `int32 StepForwardIntoIdx;` — indices of display steps for different step actions
- L141 _private member_ `int32 StepForwardOverIdx;`
- L142 _private member_ `int32 StepBackIntoIdx;`
- L143 _private member_ `int32 StepBackOverIdx;`
- L144 _private member_ `int32 StepOutIdx;`
- L147 _private member_ `TArray<uint16> ActiveBreakpoints;` — execution indices of currently active breakpoints
- L150 _private member_ `TArray<TWeakObjectPtr<class UBehaviorTreeComponent> > KnownInstances;` — all known BT instances, cached for dropdown list
- L153 _private member_ `uint32 bIsPIEActive : 1;` — cached PIE state
- L156 _private member_ `uint32 bIsCurrentSubtree : 1;` — set when debugger instance is currently active one
- L159 _private member_ `uint16 StoppedOnBreakpointExecutionIndex;` — execution index of node that caused activated the breakpoint
- L162 _private member_ `TMap<FName, FString> SavedValues;` — Lookup of currently debugged blackboard values
- L163 _private member_ `TMap<FName, FString> CurrentValues;`
- L166 _private member_ `double SavedTimestamp;` — Debugger timestamps
- L167 _private member_ `double CurrentTimestamp;`
- L168 _private member_ `double RewindDebuggerTimestamp;`
- L171 _private prototype_ `void UpdateDebuggerInstance();` — set value of DebuggerInstanceIndex variable
- L174 _private prototype_ `void ClearDebuggerState(bool bKeepSubtree = false);` — clear all runtime variables
- L177 _private prototype_ `void OnActiveNodeChanged(const TArray<uint16>& ActivePath, const TArray<uint16>& PrevStepPath);` — try using breakpoints on node change
- L181 _private prototype_ `void FindMatchingTreeInstance();` — scan all actors and try to find matching BT component used only when user starts PIE before opening editor
- L184 _private prototype_ `int32 FindMatchingDebuggerStack(UBehaviorTreeComponent& TestInstance) const;` — find index on execution instance stack of matching tree asset
- L187 _private prototype_ `int32 FindDebuggerStepForTimeStamp(double Timestamp) const;` — Return StepId of the step at that TimeStamp.
- L190 _private prototype_ `UBehaviorTreeComponent* FindInstanceInActor(AActor* TestActor);` — find BT component in given actor
- L193 _private prototype_ `void FindLockedDebugActor(class UWorld* World);` — try to find pawn currently locked by ai debug tool
- L196 _private prototype_ `void CollectBreakpointsFromAsset(class UBehaviorTreeGraphNode* Node);` — recursively collect all breakpoint indices from child nodes
- L199 _private prototype_ `void UpdateAssetFlags(const struct FBehaviorTreeDebuggerInstance& Data, class UBehaviorTreeGraphNode* Node, int32 StepIdx);` — recursively update node flags on all child nodes
- L202 _private prototype_ `void SetNodeFlags(const struct FBehaviorTreeDebuggerInstance& Data, class UBehaviorTreeGraphNode* Node, class UBTNode* NodeInstance);` — set debugger flags on GraphNode
- L205 _private prototype_ `void SetCompositeDecoratorFlags(const struct FBehaviorTreeDebuggerInstance& Data, class UBehaviorTreeGraphNode_CompositeDecorator* Node);` — set debugger flags on GraphNode for composite decorator
- L208 _private prototype_ `void UpdateAssetRuntimeDescription(const TArray<FString>& RuntimeDescriptions, class UBehaviorTreeGraphNode* Node);` — recursively update node flags on all child nodes
- L211 _private prototype_ `void SetNodeRuntimeDescription(const TArray<FString>& RuntimeDescriptions, class UBehaviorTreeGraphNode* Node, class UBTNode* NodeInstance);` — set debugger flags on GraphNode
- L214 _private prototype_ `void SetCompositeDecoratorRuntimeDescription(const TArray<FString>& RuntimeDescriptions, class UBehaviorTreeGraphNode_CompositeDecorator* Node);` — set debugger flags on GraphNode for composite decorator
- L217 _private prototype_ `void UpdateDebuggerViewOnInstanceChange();` — updates variables in debugger details view
- L218 _private prototype_ `void UpdateDebuggerViewOnStepChange();`
- L219 _private prototype_ `void UpdateDebuggerViewOnTick();`
- L222 _private prototype_ `int32 FindActiveInstanceIdx(int32 StepIdx) const;` — find valid instance for given debugger step
- L225 _private prototype_ `void UpdateCurrentSubtree();` — check if currently debugged instance is active subtree
- L228 _private prototype_ `void UpdateCurrentStep(int32 PrevStepIdx, int32 NewStepIdx, bool bSwitchAsset = true);` — updates currently displayed execution step
- L231 _private prototype_ `void UpdateAvailableActions();` — updates button states
- L234 _private member_ `FOnDebuggedBlackboardChanged OnDebuggedBlackboardChangedEvent;` — Delegate fired when the debugged blackboard is changed

#### Free symbols / members of external scopes

- L110 _delegate_ `DECLARE_EVENT_OneParam(FBehaviorTreeDebugger, FOnDebuggedBlackboardChanged, UBlackboardData*);` — Delegate fired when the debugged blackboard is changed

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorCommands.h` (Private)


#### class `FBTCommonCommands`  
`class FBTCommonCommands : public TCommands<FBTCommonCommands>`  
_L10-20_
- inherits: `TCommands<FBTCommonCommands>`
- L13 _public prototype_ `FBTCommonCommands();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> SearchBT;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> NewBlackboard;`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FBTDebuggerCommands`  
`class FBTDebuggerCommands : public TCommands<FBTDebuggerCommands>`  
_L22-44_
- inherits: `TCommands<FBTDebuggerCommands>`
- L25 _public prototype_ `FBTDebuggerCommands();`
- L27 _public member_ `TSharedPtr<FUICommandInfo> BackInto;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> BackOver;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ForwardInto;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ForwardOver;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> StepOut;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> OpenParentTree;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> OpenSubtree;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> PausePlaySession;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ResumePlaySession;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> StopPlaySession;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> CurrentValues;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SavedValues;`
- L43 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

#### class `FBTBlackboardCommands`  
`class FBTBlackboardCommands : public TCommands<FBTBlackboardCommands>`  
_L46-55_
- inherits: `TCommands<FBTBlackboardCommands>`
- L49 _public prototype_ `FBTBlackboardCommands();`
- L51 _public member_ `TSharedPtr<FUICommandInfo> DeleteEntry;`
- L54 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorDelegates.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace BehaviorTreeEditor` (scope `UE`)
- L10 _namespace_ `namespace Delegates` (scope `UE::BehaviorTreeEditor`)
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBlackboardKeyChanged, const UBlackboardData& , FBlackboardEntry* const );` — Delegate for when a blackboard key changes (added, removed, renamed)
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBlackboardKeyChanged, const UBlackboardData& , FBlackboardEntry* const );` (scope `UE::BehaviorTreeEditor::Delegates`) — Delegate for when a blackboard key changes (added, removed, renamed)
- L14 _externvar_ `extern FOnBlackboardKeyChanged OnBlackboardKeyChanged;` (scope `UE::BehaviorTreeEditor::Delegates`)

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorModes.h` (Private)


#### class `FBehaviorTreeEditorApplicationMode`  
`class FBehaviorTreeEditorApplicationMode : public FApplicationMode`  
_L10-24_
- inherits: `FApplicationMode`
- desc: Application mode for main behavior tree editing mode
- L13 _public prototype_ `FBehaviorTreeEditorApplicationMode(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditor);`
- L15 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;`
- L16 _public prototype_ `virtual void PreDeactivateMode() override;`
- L17 _public prototype_ `virtual void PostActivateMode() override;`
- L20 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditor;`
- L23 _protected member_ `FWorkflowAllowedTabSet BehaviorTreeEditorTabFactories;` — Set of spawnable tabs in behavior tree editing mode

#### class `FBlackboardEditorApplicationMode`  
`class FBlackboardEditorApplicationMode : public FApplicationMode`  
_L27-40_
- inherits: `FApplicationMode`
- desc: Application mode for blackboard editing mode
- L30 _public prototype_ `FBlackboardEditorApplicationMode(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditor);`
- L32 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;`
- L33 _public prototype_ `virtual void PostActivateMode() override;`
- L36 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditor;`
- L39 _protected member_ `FWorkflowAllowedTabSet BlackboardTabFactories;` — Set of spawnable tabs in blackboard mode

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorTabFactories.h` (Private)


#### struct `FBlackboardSummoner`  
`struct FBlackboardSummoner : public FWorkflowTabFactory`  
_L18-28_
- inherits: `FWorkflowTabFactory`
- L21 _public prototype_ `FBlackboardSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr);`
- L23 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L24 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L27 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`

#### struct `FBlackboardEditorSummoner`  
`struct FBlackboardEditorSummoner : public FWorkflowTabFactory`  
_L30-40_
- inherits: `FWorkflowTabFactory`
- L33 _public prototype_ `FBlackboardEditorSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr);`
- L35 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L36 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L39 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`

#### struct `FBlackboardDetailsSummoner`  
`struct FBlackboardDetailsSummoner : public FWorkflowTabFactory`  
_L42-52_
- inherits: `FWorkflowTabFactory`
- L45 _public prototype_ `FBlackboardDetailsSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr);`
- L47 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L48 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L51 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`

#### struct `FBehaviorTreeDetailsSummoner`  
`struct FBehaviorTreeDetailsSummoner : public FWorkflowTabFactory`  
_L54-64_
- inherits: `FWorkflowTabFactory`
- L57 _public prototype_ `FBehaviorTreeDetailsSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr);`
- L59 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L60 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L63 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`

#### struct `FBehaviorTreeSearchSummoner`  
`struct FBehaviorTreeSearchSummoner : public FWorkflowTabFactory`  
_L66-76_
- inherits: `FWorkflowTabFactory`
- L69 _public prototype_ `FBehaviorTreeSearchSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr);`
- L71 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L72 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L75 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`

#### struct `FBTGraphEditorSummoner`  
`struct FBTGraphEditorSummoner : public FDocumentTabFactoryForObjects<UEdGraph>`  
_L78-97_
- inherits: `FDocumentTabFactoryForObjects<UEdGraph>`
- L81 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);`
- L83 _public prototype_ `FBTGraphEditorSummoner(TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L85 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L86 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L89 _protected prototype_ `virtual TAttribute<FText> ConstructTabNameForObject(UEdGraph* DocumentID) const override;`
- L90 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L91 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const override;`
- L92 _protected prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L95 _protected member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;`
- L96 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### Free symbols / members of external scopes

- L81 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, UEdGraph*);`

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorTabs.h` (Private)


#### struct `FBehaviorTreeEditorTabs`  
`struct FBehaviorTreeEditorTabs`  
_L7-18_
- L10 _public member_ `static const FName GraphDetailsID;` — Tab identifiers
- L11 _public member_ `static const FName SearchID;`
- L12 _public member_ `static const FName BlackboardID;`
- L13 _public member_ `static const FName BlackboardEditorID;`
- L14 _public member_ `static const FName BlackboardDetailsID;`
- L17 _public member_ `static const FName GraphEditorID;` — Document tab identifiers

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorToolbar.h` (Private)


#### class `FBehaviorTreeEditorToolbar`  
`class FBehaviorTreeEditorToolbar : public TSharedFromThis<FBehaviorTreeEditorToolbar>`  
_L11-34_
- inherits: `TSharedFromThis<FBehaviorTreeEditorToolbar>`
- L14 _public function_ `FBehaviorTreeEditorToolbar(TSharedPtr<FBehaviorTreeEditor> InBehaviorTreeEditor) : BehaviorTreeEditor(InBehaviorTreeEditor)`
- L17 _public prototype_ `void AddModesToolbar(TSharedPtr<FExtender> Extender);`
- L18 _public prototype_ `void AddDebuggerToolbar(TSharedPtr<FExtender> Extender);`
- L19 _public prototype_ `void AddBehaviorTreeToolbar(TSharedPtr<FExtender> Extender);`
- L21 _public prototype_ `void SetCreateActionsEnabled(bool bActionsEnabled);`
- L24 _private prototype_ `void FillModesToolbar(FToolBarBuilder& ToolbarBuilder);`
- L25 _private prototype_ `void FillDebuggerToolbar(FToolBarBuilder& ToolbarBuilder);`
- L26 _private prototype_ `void FillBehaviorTreeToolbar(FToolBarBuilder& ToolbarBuilder);`
- L30 _protected member_ `TWeakPtr<FBehaviorTreeEditor> BehaviorTreeEditor;` — Pointer back to the blueprint editor tool that owns us
- L33 _private member_ `bool bCreateActionsEnabled = true;`

### `Source/Editor/BehaviorTreeEditor/Private/BehaviorTreeEditorUtils.h` (Private)


#### struct `BehaviorTreeEditorUtils::FPropertySelectionInfo`  
`struct FPropertySelectionInfo`  
_L14-28_
- L16 _public function_ `FPropertySelectionInfo() : FoundGraphNode_CompDecorator(nullptr) , FoundDecorator(nullptr) , bInjectedNode(false) , bRootLevelNode(false)`
- L24 _public member_ `UBehaviorTreeGraphNode_CompositeDecorator* FoundGraphNode_CompDecorator;`
- L25 _public member_ `UBTDecorator* FoundDecorator;`
- L26 _public member_ `bool bInjectedNode;`
- L27 _public member_ `bool bRootLevelNode;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace BehaviorTreeEditorUtils`
- L31 _prototype_ `TArray<UObject*> GetSelectionForPropertyEditor(const TSet<UObject*>& InSelection, FPropertySelectionInfo& OutSelectionInfo);` (scope `BehaviorTreeEditorUtils`) — Given a selection of nodes, return the instances that should be selected be selected for editing in the property panel

### `Source/Editor/BehaviorTreeEditor/Private/DetailCustomizations/BehaviorDecoratorDetails.h` (Private)


#### class `FBehaviorDecoratorDetails`  
`class FBehaviorDecoratorDetails : public IDetailCustomization`  
_L17-57_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L26 _public prototype_ `bool IsEditingEnabled() const;`
- L30 _private prototype_ `void UpdateAllowedAbortModes();`
- L31 _private prototype_ `void InitPropertyValues();`
- L33 _private prototype_ `EVisibility GetModeVisibility() const;`
- L34 _private prototype_ `bool GetAbortModeEnabled() const;`
- L36 _private prototype_ `void OnAbortModeChange(int32 Index);`
- L37 _private prototype_ `TSharedRef<SWidget> OnGetAbortModeContent() const;`
- L38 _private prototype_ `FText GetCurrentAbortModeDesc() const;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> ModeProperty;`
- L49 _private member_ `TArray<FStringIntPair> ModeValues;`
- L51 _private member_ `uint32 bShowMode : 1;`
- L52 _private member_ `uint32 bIsModeEnabled : 1;`
- L54 _private member_ `class UObject* MyNode;`
- L56 _private member_ `class IPropertyUtilities* PropUtils;` — property utils

#### struct `FBehaviorDecoratorDetails::FStringIntPair`  
`struct FStringIntPair`  
_L43-47_
- desc: cached names of abort behaviors
- L45 _public member_ `FString Str;`
- L46 _public member_ `int32 Int;`

### `Source/Editor/BehaviorTreeEditor/Private/DetailCustomizations/BlackboardDataDetails.h` (Private)


#### class `FBlackboardDataDetails`  
`class FBlackboardDataDetails : public IDetailCustomization`  
_L32-61_
- inherits: `IDetailCustomization`
- L35 _public function_ `FBlackboardDataDetails(FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex, UBlackboardData* InBlackboardData) : OnGetSelectedBlackboardItemIndex(InOnGetSelectedBlackboardItemIndex) , BlackboardData(InBlackboardData)`
- L41 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FOnGetSelectedBlackboardItemIndex InOnGetSelectedBlackboardItemIndex, UBlackboardData* InBlackboardData);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L44 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L47 _private prototype_ `FText OnGetKeyCategoryText() const;`
- L48 _private prototype_ `void OnKeyCategoryTextCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L49 _private prototype_ `void OnKeyCategorySelectionChanged(TSharedPtr<FText> ProposedSelection, ESelectInfo::Type );`
- L50 _private prototype_ `TSharedRef<ITableRow> MakeKeyCategoryViewWidget(TSharedPtr<FText> Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L51 _private prototype_ `void PopulateKeyCategories();`
- L55 _private member_ `FOnGetSelectedBlackboardItemIndex OnGetSelectedBlackboardItemIndex;` — Delegate used to retrieve current blackboard selection
- L56 _private member_ `TSharedPtr<IPropertyHandle> KeyHandle;`
- L57 _private member_ `TSharedPtr<SListView<TSharedPtr<FText>>> KeyCategoryListView;`
- L58 _private member_ `TSharedPtr<SComboButton> KeyCategoryComboButton;`
- L59 _private member_ `TArray<TSharedPtr<FText>> KeyCategorySource;`
- L60 _private member_ `TWeakObjectPtr<UBlackboardData> BlackboardData;`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FOnGetSelectedBlackboardItemIndex, bool& );` — Delegate used to retrieve current blackboard selection
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FOnGetSelectedBlackboardItemIndex, bool& );` — Delegate used to retrieve current blackboard selection

### `Source/Editor/BehaviorTreeEditor/Private/DetailCustomizations/BlackboardDecoratorDetails.h` (Private)


#### class `FBlackboardDecoratorDetails`  
`class FBlackboardDecoratorDetails : public FBehaviorDecoratorDetails, public FEnumEditorUtils::INotifyOnEnumChanged`  
_L25-73_
- inherits: `FBehaviorDecoratorDetails,FEnumEditorUtils::INotifyOnEnumChanged`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L33 _protected prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L36 _protected prototype_ `virtual void PreChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override;` — INotifyOnEnumChanged interface
- L37 _protected prototype_ `virtual void PostChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override;`
- L41 _private prototype_ `void CacheBlackboardData(IDetailLayoutBuilder& DetailLayout);`
- L42 _private prototype_ `void RefreshEnumPropertyValues();`
- L44 _private prototype_ `EVisibility GetIntValueVisibility() const;`
- L45 _private prototype_ `EVisibility GetFloatValueVisibility() const;`
- L46 _private prototype_ `EVisibility GetStringValueVisibility() const;`
- L47 _private prototype_ `EVisibility GetEnumValueVisibility() const;`
- L48 _private prototype_ `EVisibility GetBasicOpVisibility() const;`
- L49 _private prototype_ `EVisibility GetArithmeticOpVisibility() const;`
- L50 _private prototype_ `EVisibility GetTextOpVisibility() const;`
- L52 _private prototype_ `void OnKeyIDChanged();`
- L54 _private prototype_ `void OnEnumValueComboChange(int32 Index);`
- L55 _private prototype_ `TSharedRef<SWidget> OnGetEnumValueContent() const;`
- L56 _private prototype_ `FText GetCurrentEnumValueDesc() const;`
- L58 _private member_ `TSharedPtr<IPropertyHandle> StringValueProperty;`
- L59 _private member_ `TSharedPtr<IPropertyHandle> KeyIDProperty;`
- L60 _private member_ `TSharedPtr<IPropertyHandle> NotifyObserverProperty;`
- L63 _private member_ `TSubclassOf<class UBlackboardKeyType> CachedKeyType;` — cached type of property selected by KeyName
- L65 _private member_ `UEnum* CachedCustomObjectType;` — cached custom object type of property selected by KeyName
- L67 _private member_ `uint8 CachedOperationType;` — cached operation for key type
- L70 _private member_ `TArray<FString> EnumPropValues;` — cached enum value if property selected by KeyName has enum type
- L72 _private member_ `TWeakObjectPtr<UBlackboardData> CachedBlackboardAsset;`

### `Source/Editor/BehaviorTreeEditor/Private/DetailCustomizations/BlackboardKeysDetails.h` (Private)


#### class `FBlackboardKeyDetails_Class`  
`class FBlackboardKeyDetails_Class : public IDetailCustomization`  
_L19-36_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L29 _protected member_ `TSharedPtr<IPropertyHandle> BaseClassProperty;`
- L30 _protected member_ `TSharedPtr<IPropertyHandle> DefaultValueProperty;`
- L31 _protected member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`
- L33 _protected prototype_ `void OnBaseClassChanged();`
- L34 _protected prototype_ `void OnSetClass(const UClass* NewClass);`
- L35 _protected prototype_ `const UClass* OnGetSelectedClass() const;`

#### class `FBlackboardKeyDetails_Object`  
`class FBlackboardKeyDetails_Object : public IDetailCustomization`  
_L38-56_
- inherits: `IDetailCustomization`
- L42 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L45 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L48 _protected member_ `TSharedPtr<IPropertyHandle> BaseClassProperty;`
- L49 _protected member_ `TSharedPtr<IPropertyHandle> DefaultValueProperty;`
- L50 _protected member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`
- L52 _protected prototype_ `void OnBaseClassChanged();`
- L53 _protected prototype_ `const UObject* OnGetSelectedObject() const;`
- L54 _protected prototype_ `void OnObjectChanged(const FAssetData& AssetData);`
- L55 _protected prototype_ `FString OnGetObjectPath() const;`

#### class `FBlackboardKeyDetails_Enum`  
`class FBlackboardKeyDetails_Enum : public IDetailCustomization`  
_L58-75_
- inherits: `IDetailCustomization`
- L62 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L65 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L68 _protected member_ `TSharedPtr<IPropertyHandle> EnumTypeProperty;`
- L69 _protected member_ `TSharedPtr<IPropertyHandle> DefaultValueProperty;`
- L70 _protected member_ `TSharedPtr<IPropertyUtilities> CachedUtils;`
- L72 _protected prototype_ `void OnEnumSelectionChanged(int32 NewValue, ESelectInfo::Type);`
- L73 _protected prototype_ `void OnEnumTypeChanged();`
- L74 _protected prototype_ `int32 GetEnumValue() const;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace ESelectInfo`

### `Source/Editor/BehaviorTreeEditor/Private/DetailCustomizations/BlackboardSelectorDetails.h` (Private)


#### class `FBlackboardSelectorDetails`  
`class FBlackboardSelectorDetails : public IPropertyTypeCustomization`  
_L20-63_
- inherits: `IPropertyTypeCustomization`
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L28 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L32 _private prototype_ `void CacheBlackboardData();`
- L33 _private prototype_ `void FindBlackboardAsset(const UObject* InObj, const UObject*& OutBlackboardOwner, UBlackboardData*& OutBlackboardAsset) const;`
- L35 _private prototype_ `void OnBlackboardDataChanged(UBlackboardData* Asset);`
- L36 _private prototype_ `void OnBlackboardOwnerChanged(UObject* Owner, UBlackboardData* Asset);`
- L38 _private prototype_ `void InitKeyFromProperty();`
- L39 _private prototype_ `void OnKeyComboChange(int32 Index);`
- L40 _private prototype_ `TSharedRef<SWidget> OnGetKeyContent() const;`
- L41 _private prototype_ `FText GetCurrentKeyDesc() const;`
- L42 _private prototype_ `bool IsEditingEnabled() const;`
- L44 _private member_ `FDelegateHandle OnBlackboardDataChangedHandle;`
- L45 _private member_ `FDelegateHandle OnBlackboardOwnerChangedHandle;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> MyStructProperty;`
- L48 _private member_ `TSharedPtr<IPropertyHandle> MyKeyNameProperty;`
- L49 _private member_ `TSharedPtr<IPropertyHandle> MyKeyIDProperty;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> MyKeyClassProperty;`
- L53 _private member_ `TArray<FName> KeyValues;` — cached names of keys
- L55 _private member_ `bool bNoneIsAllowedValue;`
- L58 _private member_ `TWeakObjectPtr<class UBlackboardData> CachedBlackboardAsset;` — cached blackboard asset
- L62 _private member_ `class IPropertyUtilities* PropUtils;` — property utils

### `Source/Editor/BehaviorTreeEditor/Private/FindInBT.h` (Private)


#### enum `EFindInBTSearchType`  
`enum class EFindInBTSearchType : uint8`  
_L32-42_
- desc: Indicates the kind of search we want to do
- L35 _public enumerator_ `Node` — Search for text on nodes
- L38 _public enumerator_ `BlackboardKey` — Search through properties with matching Blackboard Key
- L41 _public enumerator_ `GameplayTag` — Search through properties with matching GameplayTag

#### class `FFindInBTResult`  
`class FFindInBTResult`  
_L45-83_
- desc: Item that matched the search results
- L49 _public prototype_ `FFindInBTResult(const FString& InValue);` — Create a root (or only text) result
- L52 _public prototype_ `FFindInBTResult(const FString& InValue, TSharedPtr<FFindInBTResult>& InParent, UEdGraphNode* InNode);` — Create a BT node result
- L55 _public prototype_ `FReply OnClick(TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditor, TSharedPtr<FFindInBTResult> Root);` — Called when user clicks on the search item
- L58 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L61 _public prototype_ `FString GetCommentText() const;` — Gets the comment on this node if any
- L64 _public prototype_ `FString GetNodeTypeText() const;` — Gets the node type
- L67 _public prototype_ `void SetNodeHighlight(bool bHighlight);` — Highlights BT tree nodes
- L70 _public member_ `TArray< TSharedPtr<FFindInBTResult> > Children;` — Any children listed under this BT node (decorators and services)
- L73 _public member_ `FString Value;` — The string value for this result
- L76 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to
- L79 _public member_ `TWeakPtr<FFindInBTResult> Parent;` — Search result parent
- L82 _public member_ `FString ExactFieldValueFound;` — Show in search result row the exact field value found

#### class `SFindInBT`  
`class SFindInBT : public SCompoundWidget`  
_L86-164_
- inherits: `SCompoundWidget`
- desc: Widget for searching for (BT nodes) across focused BehaviorTree
- L89 _public function_ `SLATE_BEGIN_ARGS(SFindInBT)`
- L90 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<class FBehaviorTreeEditor> InBehaviorTreeEditor);`
- L95 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L98 _private typedef_ `typedef TSharedPtr<FFindInBTResult> FSearchResult;`
- L99 _private typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L102 _private prototype_ `void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L105 _private prototype_ `void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user commits text
- L108 _private prototype_ `void OnGetChildren(FSearchResult InItem, TArray<FSearchResult>& OutChildren);` — Get the children of a row
- L111 _private prototype_ `void OnTreeSelectionChanged(FSearchResult Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L114 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L117 _private prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L120 _private prototype_ `void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L123 _private prototype_ `void MatchTokensInChild(const TArray<FString>& Tokens, UBehaviorTreeGraphNode* Child, FSearchResult ParentNode);` — Find if child contains all of the tokens and add a result accordingly
- L126 _private prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L129 _private prototype_ `bool NodePropertyMatchesSearchTokens(const TArray<FString>& Tokens, UBehaviorTreeGraphNode* Node, FString& OutExactFieldValueFound) const;` — Determines if a string matches a node property according to the SearchType
- L132 _private prototype_ `bool FieldPropertyMatchesSearchTokens(const TArray<FString>& Tokens, const FProperty* Property, void* Data, FString& OutExactFieldValueFound) const;` — Determines if a string matches a field property according to the SearchType
- L135 _private prototype_ `void OnSearchTypeSelectedItemChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Initiates search when SearchType changes
- L139 _private member_ `TWeakPtr<class FBehaviorTreeEditor> BehaviorTreeEditorPtr;` — Pointer back to the behavior tree editor that owns us
- L142 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L145 _private member_ `TSharedPtr<class SSearchBox> SearchTextField;` — The search text box
- L148 _private member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L151 _private member_ `FSearchResult RootSearchResult;` — we need to keep a handle on the root result, because it won't show up in the tree
- L154 _private member_ `FText HighlightText;` — The string to highlight in the results
- L157 _private member_ `FString SearchValue;` — The string to search for
- L160 _private member_ `TArray<TSharedPtr<FString>> SearchTypeComboBoxItems;` — Shared strings based on the search types
- L163 _private member_ `EFindInBTSearchType SearchType = EFindInBTSearchType::Node;` — Current search type determines how search occurs

### `Source/Editor/BehaviorTreeEditor/Private/SBehaviorTreeBlackboardEditor.h` (Private)


#### class `SBehaviorTreeBlackboardEditor`  
`class SBehaviorTreeBlackboardEditor : public SBehaviorTreeBlackboardView`  
_L26-95_
- inherits: `SBehaviorTreeBlackboardView`
- desc: Displays and edits blackboard entries
- L29 _public function_ `SLATE_BEGIN_ARGS( SBehaviorTreeBlackboardEditor )`
- L31 _public prototype_ `SLATE_EVENT(FOnEntrySelected, OnEntrySelected) SLATE_EVENT(FOnGetDebugKeyValue, OnGetDebugKeyValue) SLATE_EVENT(FOnGetDisplayCurrentState, OnGetDisplayCurrentState) SLATE_EVENT(FOnIsDebuggerReady, OnIsDebuggerReady) SLATE_EVENT(FOnIsDebuggerPaused, OnIsDebuggerPaused) SLATE_EVENT(FOnGetDebugTimeStamp, OnGetDebugTimeStamp) SLATE_EVENT(FOnIsBlackboardModeActive, OnIsBlackboardModeActive) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FUICommandList> InCommandList, UBlackboardData* InBlackboardData);`
- L45 _private prototype_ `virtual void FillContextMenu(FMenuBuilder& MenuBuilder) const override;` — Fill the context menu with edit options
- L48 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder) const;` — Fill the toolbar with edit options
- L51 _private prototype_ `virtual TSharedPtr<FExtender> GetToolbarExtender(TSharedRef<FUICommandList> ToolkitCommands) const override;` — Extend the toolbar
- L54 _private prototype_ `void HandleDeleteEntry();` — Handle deleting the currently selected entry
- L57 _private prototype_ `void HandleCopyEntry();` — Handle copying the currently selected entry
- L60 _private prototype_ `void HandlePasteEntry();` — Handle pasting the currently copied entry
- L63 _private prototype_ `void HandleDuplicateEntry();` — Handle duplicating the currently selected entry
- L66 _private prototype_ `void HandleRenameEntry();` — Handle renaming the currently selected entry
- L69 _private prototype_ `TSharedRef<SWidget> HandleCreateNewEntryMenu() const;` — Create the menu used to create a new blackboard entry
- L72 _private prototype_ `void HandleKeyClassPicked(UClass* InClass);` — Create a new blackboard entry when a class is picked
- L75 _private prototype_ `bool CanCreateNewEntry() const;` — Delegate handler that disallows creating a new entry while the debugger is running
- L78 _private prototype_ `bool CanDeleteEntry() const;` — Check whether the 'Delete' operation can be performed on the selected item
- L81 _private prototype_ `bool CanCopyEntry() const;` — Check whether the 'Copy' operation can be performed on the selected item
- L84 _private prototype_ `bool CanPasteEntry() const;` — Check whether the 'Paste' operation can be performed on the copied item
- L87 _private prototype_ `bool CanDuplicateEntry() const;` — Check whether the 'Duplicate' operation can be performed on the selected item
- L90 _private prototype_ `bool CanRenameEntry() const;` — Check whether the 'Rename' operation can be performed on the selected item
- L94 _private member_ `FOnIsBlackboardModeActive OnIsBlackboardModeActive;` — Delegate used to determine whether the Blackboard mode is active

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackboardEditor, Warning, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBlackboardEditor, Warning, All);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsBlackboardModeActive);` — Delegate used to determine whether the Blackboard mode is active
- L23 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsBlackboardModeActive);` — Delegate used to determine whether the Blackboard mode is active

### `Source/Editor/BehaviorTreeEditor/Private/SBehaviorTreeBlackboardView.h` (Private)


#### class `FEdGraphSchemaAction_BlackboardEntry`  
`class FEdGraphSchemaAction_BlackboardEntry : public FEdGraphSchemaAction_Dummy`  
_L49-75_
- inherits: `FEdGraphSchemaAction_Dummy`
- desc: Blackboard entry in the list
- L52 _public prototype_ `static FName StaticGetTypeId();`
- L53 _public prototype_ `virtual FName GetTypeId() const;`
- L55 _public prototype_ `FEdGraphSchemaAction_BlackboardEntry( TWeakObjectPtr<UBlackboardData> InBlackboardData, FBlackboardEntry& InKey, bool bInIsInherited );`
- L57 _public prototype_ `void Update();`
- L60 _public member_ `TWeakObjectPtr<UBlackboardData> BlackboardData;` — Blackboard we reference our key in
- L63 _public member_ `FBlackboardEntry& Key;` — Actual key
- L66 _public member_ `bool bIsInherited;` — Whether this entry came from a parent blackboard
- L69 _public member_ `bool bIsNew;` — Temp flag for new items
- L71 _public function_ `virtual bool CanBeRenamed() const override`

#### class `SBehaviorTreeBlackboardView`  
`class SBehaviorTreeBlackboardView : public SCompoundWidget`  
_L78-212_
- inherits: `SCompoundWidget`
- desc: Displays blackboard entries
- L81 _public function_ `SLATE_BEGIN_ARGS( SBehaviorTreeBlackboardView )`
- L86 _public prototype_ `SLATE_EVENT(FOnEntrySelected, OnEntrySelected) SLATE_EVENT(FOnGetDebugKeyValue, OnGetDebugKeyValue) SLATE_EVENT(FOnGetDisplayCurrentState, OnGetDisplayCurrentState) SLATE_EVENT(FOnIsDebuggerReady, OnIsDebuggerReady) SLATE_EVENT(FOnIsDebuggerPaused, OnIsDebuggerPaused) SLATE_EVENT(FOnGetDebugTimeStamp, OnGetDebugTimeStamp) SLATE_ARGUMENT(bool, IsReadOnly) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FUICommandList> InCommandList, UBlackboardData* InBlackboardData);`
- L97 _public prototype_ `~SBehaviorTreeBlackboardView();`
- L104 _public prototype_ `FBlackboardEntry* GetSelectedEntry(bool& bOutIsInherited) const;` — Retrieves the blackboard item currently selected by the user. @param	bOutIsInherited		Whether the item's index is in the key or parent key array @return A pointer to the currently selected entry (nullptr if a category is selected, or nothing at all)
- L111 _public prototype_ `bool SetSelectedEntry(FName EntryName) const;` — Selects a blackboard item @param	EntryName	The name of blackboard item to select @return true if the item was selected
- L119 _public prototype_ `int32 GetSelectedEntryIndex(bool& bOutIsInherited) const;` — Retrieves the blackboard item index currently selected by the user. @param	bOutIsInherited		Whether the item's index is in the key or parent key array @return The selected index (or INDEX_NONE if nothing is selected)
- L122 _public prototype_ `void SetObject(UBlackboardData* InBlackboardData);` — Set the object we are looking at
- L126 _protected prototype_ `void HandleBlackboardKeyChanged(const UBlackboardData& InBlackboardData, FBlackboardEntry* const InKey);` — Delegate handler for when a blackboard key changes (added, removed, renamed)
- L129 _protected prototype_ `TSharedRef<SWidget> HandleCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);` — Delegate handler used to generate a widget for an 'action' (key) in the list
- L132 _protected prototype_ `void HandleCollectAllActions( FGraphActionListBuilderBase& GraphActionListBuilder );` — Delegate handler used to collect all 'actions' (keys) for display
- L135 _protected prototype_ `FText HandleGetSectionTitle(int32 SectionID) const;` — Get the title of the specified section ID
- L138 _protected prototype_ `void HandleActionSelected(const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedActions, ESelectInfo::Type InSelectionType) const;` — Delegate handler used when an action is selected
- L141 _protected prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening(TSharedRef<FUICommandList> ToolkitCommands) const;` — Delegate handler used to generate an action's context menu
- L144 _protected prototype_ `virtual void FillContextMenu(FMenuBuilder& MenuBuilder) const;` — Add any context menu items
- L147 _protected prototype_ `virtual TSharedPtr<FExtender> GetToolbarExtender(TSharedRef<FUICommandList> ToolkitCommands) const;` — Extend the toolbar
- L150 _protected prototype_ `void HandleUseCurrentValues();` — Delegate handler invoked when we want to use current values
- L153 _protected prototype_ `void HandleUseSavedValues();` — Delegate handler invoked when we want to use saved values
- L156 _protected prototype_ `FText GetDebugTimeStampText() const;` — Delegate handler used by toolbar to get display text for timestamp
- L159 _protected prototype_ `EVisibility GetDebuggerToolbarVisibility() const;` — Get the visibility of the toolbar sections used when debugging
- L162 _protected prototype_ `bool IsUsingCurrentValues() const;` — Delegate handler used by toolbar to determine whether to display saved values
- L165 _protected prototype_ `bool IsUsingSavedValues() const;` — Delegate handler used by toolbar to determine whether to display current values
- L168 _protected prototype_ `bool HasSelectedItems() const;` — Check whether we have any items selected
- L171 _protected prototype_ `TSharedPtr<FEdGraphSchemaAction_BlackboardEntry> GetSelectedEntryInternal() const;` — Helper function for GetSelectedEntry()
- L174 _protected prototype_ `bool IsDebuggerActive() const;` — Delegate handler that shows various controls when the debugger is active
- L177 _protected prototype_ `bool IsDebuggerPaused() const;` — Delegate handler that enables various controls when the debugger is active and paused
- L180 _protected prototype_ `bool HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;` — Delegate handler used to match an FName to an action in the list, used for renaming keys
- L184 _protected member_ `TWeakObjectPtr<UBlackboardData> BlackboardData;` — The blackboard we are editing/viewing
- L187 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;` — The list of blackboard entries
- L190 _protected member_ `FOnEntrySelected OnEntrySelected;` — Delegate executed when an entry is selected
- L193 _protected member_ `FOnGetDebugKeyValue OnGetDebugKeyValue;` — Delegate used to retrieve debug data to display
- L196 _protected member_ `FOnGetDisplayCurrentState OnGetDisplayCurrentState;` — Delegate used to determine whether the BT debugger displaying the current state
- L199 _protected member_ `FOnIsDebuggerReady OnIsDebuggerReady;` — Delegate used to determine whether the BT debugger is active
- L202 _protected member_ `FOnIsDebuggerPaused OnIsDebuggerPaused;` — Delegate used to determine whether the BT debugger is paused
- L205 _protected member_ `FOnGetDebugTimeStamp OnGetDebugTimeStamp;` — Delegate used to get the debugger's current timestamp
- L208 _protected member_ `FDelegateHandle OnBlackboardKeyChangedDelegateHandle;` — Handle to the registered OnBlackboardKeyChanged delegate
- L211 _protected member_ `bool bShowCurrentState;` — Whether we want to show the current or saved state

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnEntrySelected, const FBlackboardEntry*, bool );` — Delegate executed when an entry is selected
- L30 _prototype_ `DECLARE_DELEGATE_TwoParams( FOnEntrySelected, const FBlackboardEntry*, bool );` — Delegate executed when an entry is selected
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnGetDebugKeyValue, const FName& , bool );` — Delegate used to retrieve debug data to display
- L33 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FText, FOnGetDebugKeyValue, const FName& , bool );` — Delegate used to retrieve debug data to display
- L36 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsDebuggerReady);` — Delegate used to determine whether the BT debugger is active
- L36 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsDebuggerReady);` — Delegate used to determine whether the BT debugger is active
- L39 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnIsDebuggerPaused);` — Delegate used to determine whether the BT debugger is paused
- L39 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnIsDebuggerPaused);` — Delegate used to determine whether the BT debugger is paused
- L42 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnGetDisplayCurrentState);` — Delegate used to determine whether the BT debugger displaying the current state
- L42 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnGetDisplayCurrentState);` — Delegate used to determine whether the BT debugger displaying the current state
- L45 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(double, FOnGetDebugTimeStamp, bool );` — Delegate used to get the debugger's current timestamp
- L45 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(double, FOnGetDebugTimeStamp, bool );` — Delegate used to get the debugger's current timestamp

### `Source/Editor/BehaviorTreeEditor/Private/SBehaviorTreeDiff.h` (Private)


#### class `SBehaviorTreeDiff`  
`class SBehaviorTreeDiff: public SCompoundWidget`  
_L27-207_
- inherits: `SCompoundWidget`
- L32 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, class UBehaviorTree* , class UBehaviorTree*);` — Delegate for default Diff tool
- L34 _public function_ `SLATE_BEGIN_ARGS(SBehaviorTreeDiff )`
- L35 _public prototype_ `SLATE_ARGUMENT(class UBehaviorTree*, BehaviorTreeOld) SLATE_ARGUMENT(class UBehaviorTree*, BehaviorTreeNew) SLATE_ARGUMENT(struct FRevisionInfo, OldRevision) SLATE_ARGUMENT(struct FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_EVENT(FOpenInDefaults, OpenInDefaults) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L116 _private typedef_ `typedef TSharedPtr<struct FTreeDiffResultItem> FSharedDiffOnGraph;` — Type def for our Table item
- L119 _private typedef_ `typedef SListView<FSharedDiffOnGraph > SListViewType;` — Type def of our Table Type
- L126 _private prototype_ `FReply OnOpenInDefaults();` — User clicks defaults view button to display defaults in remote diff tool @return If its been handled
- L132 _private prototype_ `TSharedRef<SWidget> GenerateDiffListWidget();` — Generate list of differences @return The widget containing the Difference list
- L137 _private prototype_ `void BuildDiffSourceArray();` — Build up the Diff Source Array
- L142 _private prototype_ `void NextDiff();` — Go to Next Difference
- L147 _private prototype_ `void PrevDiff();` — Go to Previous Difference
- L153 _private prototype_ `int32 GetCurrentDiffIndex();` — Get current Index into the diff array @return The Index
- L160 _private prototype_ `void OnSelectionChanged(FSharedDiffOnGraph Item, ESelectInfo::Type SelectionType);` — Called when difference selection is changed @param Item The item that was selected @param SelectionType The way it was selected
- L168 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSharedDiffOnGraph Item, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated @param Item The item being generated @param OwnerTable The table its going into @return The Row that was inserted
- L175 _private prototype_ `SGraphEditor* GetGraphEditorForGraph(UEdGraph* Graph) const;` — Get the Slate graph editor of the supplied Graph @param Graph The graph we want the Editor from @return The Graph Editor
- L180 _private prototype_ `void DisablePinDiffFocus();` — Removes focus of the pin in the graph viewer
- L185 _private member_ `FOpenInDefaults OpenInDefaults;` — Delegate to call when user wishes to view the defaults
- L188 _private member_ `FBehaviorTreeDiffPanel PanelOld, PanelNew;` — The 2 panels we will be comparing
- L188 _private member_ `FBehaviorTreeDiffPanel PanelOld, PanelNew;` — The 2 panels we will be comparing
- L191 _private member_ `TArray<FSharedDiffOnGraph> DiffListSource;` — Source for list view
- L194 _private member_ `TSharedPtr<TArray<FDiffSingleResult>> FoundDiffs;` — result from FGraphDiffControl::DiffGraphs
- L197 _private member_ `TSharedPtr<FUICommandList> KeyCommands;` — Key commands processed by this widget
- L200 _private member_ `TSharedPtr<SListViewType> DiffList;` — ListView of differences
- L203 _private member_ `UEdGraphPin* LastPinTarget;` — The last pin the user clicked on
- L206 _private member_ `UEdGraphPin* LastOtherPinTarget;` — The last other pin the user clicked on

#### struct `SBehaviorTreeDiff::FBehaviorTreeDiffPanel`  
`struct FBehaviorTreeDiffPanel`  
_L48-113_
- desc: Panel used to display the behavior tree
- L51 _public prototype_ `FBehaviorTreeDiffPanel();` — Constructor
- L58 _public prototype_ `void GeneratePanel(UEdGraph* Graph, TSharedPtr<TArray<FDiffSingleResult>> DiffResults);` — Generate a panel that displays the Graph and reflects the items in the DiffResults @param Graph        Graph Being Displayed @param DiffResults  Attribute for obtaining the list of differences
- L64 _public prototype_ `FText GetTitle() const;` — Returns title for this panel @return The Title
- L69 _public prototype_ `void CopySelectedNodes();` — Called when user hits keyboard shortcut to copy nodes
- L74 _public prototype_ `void OnSelectionChanged( const FGraphPanelSelectionSet& Selection );` — Called When graph node gains focus
- L79 _public prototype_ `bool IsPropertyEditable();` — Delegate to say if a node property should be editable
- L85 _public prototype_ `FGraphPanelSelectionSet GetSelectedNodes() const;` — Gets whatever nodes are selected in the Graph Editor @return Gets the selected nodes in the graph
- L91 _public prototype_ `bool CanCopyNodes() const;` — Can user copy any of the selected nodes? @return True if can copy
- L94 _public member_ `class UBehaviorTree* BehaviorTree;` — The behavior Tree that owns the graph we are showing
- L97 _public member_ `FRevisionInfo RevisionInfo;` — Revision information for this behavior tree
- L100 _public member_ `TSharedPtr<SBorder> GraphEditorBorder;` — The border around the graph editor, used to change the content when new graphs are set
- L103 _public member_ `TWeakPtr<class SGraphEditor> GraphEditor;` — The graph editor which does the work of displaying the graph
- L106 _public member_ `bool bShowAssetName;` — If we should show a name identifying which asset this panel is displaying
- L109 _public member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list for this diff panel
- L112 _public member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, class UBehaviorTree* , class UBehaviorTree*);` — Delegate for default Diff tool

### `Source/Editor/BehaviorTreeEditor/Private/SGraphNode_BehaviorTree.h` (Private)


#### class `SGraphNode_BehaviorTree`  
`class SGraphNode_BehaviorTree : public SGraphNodeAI, public FEnumEditorUtils::INotifyOnEnumChanged`  
_L35-138_
- inherits: `SGraphNodeAI,FEnumEditorUtils::INotifyOnEnumChanged`
- L38 _public function_ `SLATE_BEGIN_ARGS(SGraphNode_BehaviorTree)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UBehaviorTreeGraphNode* InNode);`
- L44 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L45 _public prototype_ `virtual void CreatePinWidgets() override;`
- L46 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L47 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L48 _public prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L49 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L50 _public prototype_ `virtual TSharedRef<SGraphNode> GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L55 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;` — handle double click
- L64 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  AllottedGeometry The space allotted for this widget @param  InCurrentTime  Current absolute real time @param  InDeltaTime  Real time passed since last tick
- L67 _public prototype_ `void AddDecorator(TSharedPtr<SGraphNode> DecoratorWidget);` — adds decorator widget inside current node
- L70 _public prototype_ `void AddService(TSharedPtr<SGraphNode> ServiceWidget);` — adds service widget inside current node
- L73 _public prototype_ `EVisibility GetDebuggerSearchFailedMarkerVisibility() const;` — shows red marker when search failed
- L75 _public function_ `FVector2f GetCachedPosition() const`
- L79 _protected prototype_ `virtual void PreChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override;` — INotifyOnEnumChanged interface
- L80 _protected prototype_ `virtual void PostChange(const UUserDefinedEnum* Changed, FEnumEditorUtils::EEnumEditorChangeInfo ChangedType) override;`
- L82 _protected member_ `uint32 bSuppressDebuggerColor : 1;`
- L83 _protected member_ `uint32 bSuppressDebuggerTriggers : 1;`
- L86 _protected member_ `float DebuggerStateDuration;` — time spent in current state
- L89 _protected member_ `int32 DebuggerStateCounter;` — currently displayed state
- L92 _protected member_ `FLinearColor FlashColor;` — debugger colors
- L93 _protected member_ `float FlashAlpha;`
- L96 _protected member_ `TArray<FNodeBounds> TriggerOffsets;` — height offsets for search triggers
- L99 _protected member_ `FVector2f CachedPosition;` — cached draw position
- L101 _protected member_ `TArray< TSharedPtr<SGraphNode> > DecoratorWidgets;`
- L102 _protected member_ `TArray< TSharedPtr<SGraphNode> > ServicesWidgets;`
- L103 _protected member_ `TSharedPtr<SVerticalBox> DecoratorsBox;`
- L104 _protected member_ `TSharedPtr<SVerticalBox> ServicesBox;`
- L105 _protected member_ `TSharedPtr<SHorizontalBox> OutputPinBox;`
- L108 _protected member_ `TSharedPtr<SWidget> IndexOverlay;` — The widget we use to display the index of the node
- L111 _protected member_ `TSharedPtr<SBorder> NodeBody;` — The node body widget, cached here so we can determine its size when we want ot position our overlays
- L113 _protected prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L114 _protected prototype_ `FSlateColor GetBackgroundColor() const;`
- L116 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const override;`
- L117 _protected prototype_ `virtual EVisibility GetBlueprintIconVisibility() const;`
- L119 _protected prototype_ `FText GetRuntimeDescription() const;`
- L120 _protected prototype_ `EVisibility GetRuntimeDescriptionVisibility() const;`
- L123 _protected prototype_ `EVisibility GetIndexVisibility() const;` — Get the visibility of the index overlay
- L126 _protected prototype_ `FText GetIndexText() const;` — Get the text to display in the index overlay
- L129 _protected prototype_ `FText GetIndexTooltipText() const;` — Get the tooltip for the index overlay
- L132 _protected prototype_ `FSlateColor GetIndexColor(bool bHovered) const;` — Get the color to display for the index overlay. This changes on hover state of sibling nodes
- L135 _protected prototype_ `void OnIndexHoverStateChanged(bool bHovered);` — Handle hover state changing for the index widget - we use this to highlight sibling nodes
- L137 _protected prototype_ `FText GetPinTooltip(UEdGraphPin* GraphPinObj) const;`

### `Source/Editor/BehaviorTreeEditor/Private/SGraphNode_Decorator.h` (Private)


#### class `SGraphNode_Decorator`  
`class SGraphNode_Decorator : public SGraphNode`  
_L11-20_
- inherits: `SGraphNode`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNode_Decorator)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UBehaviorTreeDecoratorGraphNode_Decorator* InNode);`
- L19 _public prototype_ `virtual FString GetNodeComment() const override;`

### `Source/Editor/BehaviorTreeEditor/Public/AssetDefinition_BehaviorTree.h` (Public)


#### class `UAssetDefinition_BehaviorTree`  
`class UAssetDefinition_BehaviorTree : public UAssetDefinitionDefault`  
_L13-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetDefinitionDefault`
- L19 _protected prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L20 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L24 _protected prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`
- L30 _private prototype_ `void OpenInDefaults(class UBehaviorTree* OldBehaviorTree, class UBehaviorTree* NewBehaviorTree) const;` — Called to open the Behavior Tree defaults view, this opens whatever text diff tool the user has

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Public/BehaviorTreeColors.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace BehaviorTreeColors`
- L11 _namespace_ `namespace NodeBody` (scope `BehaviorTreeColors`)
- L13 _variable_ `const FLinearColor Task(0.24f, 0.055f, 0.715f);` (scope `BehaviorTreeColors::NodeBody`)
- L14 _variable_ `const FLinearColor TaskSpecial(0.1f, 0.05f, 0.2f);` (scope `BehaviorTreeColors::NodeBody`)
- L15 _variable_ `const FLinearColor Decorator(0.0f, 0.07f, 0.4f);` (scope `BehaviorTreeColors::NodeBody`)
- L16 _variable_ `const FLinearColor InjectedSubNode(0.0f, 0.02f, 0.1f);` (scope `BehaviorTreeColors::NodeBody`)
- L17 _variable_ `const FLinearColor Composite(0.1f, 0.1f, 0.1f);` (scope `BehaviorTreeColors::NodeBody`)
- L18 _variable_ `const FLinearColor CompositeScoped(0.05f, 0.05f, 0.05f);` (scope `BehaviorTreeColors::NodeBody`)
- L19 _variable_ `const FLinearColor Service(0.0f, 0.4f, 0.22f);` (scope `BehaviorTreeColors::NodeBody`)
- L20 _variable_ `const FLinearColor Default(0.15f, 0.15f, 0.15f);` (scope `BehaviorTreeColors::NodeBody`)
- L21 _variable_ `const FLinearColor Root(0.5f, 0.5f, 0.5f, 0.1f);` (scope `BehaviorTreeColors::NodeBody`)
- L22 _variable_ `const FLinearColor Error(1.0f, 0.0f, 0.0f);` (scope `BehaviorTreeColors::NodeBody`)
- L25 _namespace_ `namespace NodeBorder` (scope `BehaviorTreeColors`)
- L27 _variable_ `const FLinearColor Inactive(0.08f, 0.08f, 0.08f);` (scope `BehaviorTreeColors::NodeBorder`)
- L28 _variable_ `const FLinearColor Root(0.2f, 0.2f, 0.2f, 0.2f);` (scope `BehaviorTreeColors::NodeBorder`)
- L29 _variable_ `const FLinearColor Selected(1.00f, 0.08f, 0.08f);` (scope `BehaviorTreeColors::NodeBorder`)
- L30 _variable_ `const FLinearColor ActiveDebugging(1.0f, 1.0f, 0.0f);` (scope `BehaviorTreeColors::NodeBorder`)
- L31 _variable_ `const FLinearColor InactiveDebugging(0.4f, 0.4f, 0.0f);` (scope `BehaviorTreeColors::NodeBorder`)
- L32 _variable_ `const FLinearColor HighlightAbortRange0(0.0f, 0.22f, 0.4f);` (scope `BehaviorTreeColors::NodeBorder`)
- L33 _variable_ `const FLinearColor HighlightAbortRange1(0.0f, 0.4f, 0.22f);` (scope `BehaviorTreeColors::NodeBorder`)
- L34 _variable_ `const FLinearColor Disconnected(0.f, 0.f, 0.f);` (scope `BehaviorTreeColors::NodeBorder`)
- L35 _variable_ `const FLinearColor BrokenWithParent(1.f, 0.f, 1.f);` (scope `BehaviorTreeColors::NodeBorder`)
- L36 _variable_ `const FLinearColor QuickFind(0.f, 0.8f, 0.f);` (scope `BehaviorTreeColors::NodeBorder`)
- L39 _namespace_ `namespace Pin` (scope `BehaviorTreeColors`)
- L41 _variable_ `const FLinearColor Diff(0.9f, 0.2f, 0.15f);` (scope `BehaviorTreeColors::Pin`)
- L42 _variable_ `const FLinearColor Hover(1.0f, 0.7f, 0.0f);` (scope `BehaviorTreeColors::Pin`)
- L43 _variable_ `const FLinearColor Default(0.02f, 0.02f, 0.02f);` (scope `BehaviorTreeColors::Pin`)
- L44 _variable_ `const FLinearColor TaskOnly(0.13f, 0.03f, 0.4f);` (scope `BehaviorTreeColors::Pin`)
- L45 _variable_ `const FLinearColor CompositeOnly(0.02f, 0.02f, 0.02f);` (scope `BehaviorTreeColors::Pin`)
- L46 _variable_ `const FLinearColor SingleNode(0.02f, 0.02f, 0.02f);` (scope `BehaviorTreeColors::Pin`)
- L49 _namespace_ `namespace Connection` (scope `BehaviorTreeColors`)
- L51 _variable_ `const FLinearColor Default(1.0f, 1.0f, 1.0f);` (scope `BehaviorTreeColors::Connection`)
- L54 _namespace_ `namespace Debugger` (scope `BehaviorTreeColors`)
- L56 _variable_ `const FLinearColor ActiveDecorator(0.05f, 0.27f, 0.7f);` (scope `BehaviorTreeColors::Debugger`)
- L57 _variable_ `const FLinearColor ActiveService(0.3f, 0.8f, 0.4f);` (scope `BehaviorTreeColors::Debugger`)
- L58 _variable_ `const FLinearColor TaskFlash(1.0f, 1.0f, 0.0f);` (scope `BehaviorTreeColors::Debugger`)
- L59 _variable_ `const FLinearColor SearchSucceeded(0.0f, 1.0f, 0.0f);` (scope `BehaviorTreeColors::Debugger`)
- L60 _variable_ `const FLinearColor SearchFailed(1.0f, 0.0f, 0.0f);` (scope `BehaviorTreeColors::Debugger`)
- L62 _variable_ `const FLinearColor DescHeader(0.3f, 0.8f, 0.4f);` (scope `BehaviorTreeColors::Debugger`)
- L63 _variable_ `const FLinearColor DescKeys(0.3f, 0.4f, 0.8f);` (scope `BehaviorTreeColors::Debugger`)
- L66 _namespace_ `namespace Action` (scope `BehaviorTreeColors`)
- L68 _variable_ `const FLinearColor DragMarker(1.0f, 1.0f, 0.2f);` (scope `BehaviorTreeColors::Action`)

### `Source/Editor/BehaviorTreeEditor/Public/BehaviorTreeEditor.h` (Public)


#### class `FBehaviorTreeEditor`  
`class FBehaviorTreeEditor : public IBehaviorTreeEditor, public FAIGraphEditor, public FNotifyHook`  
_L42-363_
- inherits: `IBehaviorTreeEditor,FAIGraphEditor,FNotifyHook`
- L45 _public prototype_ `FBehaviorTreeEditor();`
- L47 _public prototype_ `virtual ~FBehaviorTreeEditor();` — Destructor
- L49 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L51 _public prototype_ `virtual void InitBehaviorTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);`
- L54 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L55 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L56 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L57 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L58 _public prototype_ `virtual FText GetToolkitName() const override;`
- L59 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L63 _public prototype_ `virtual void InitializeDebuggerState(class FBehaviorTreeDebugger* ParentDebugger) const override;`
- L64 _public prototype_ `virtual UEdGraphNode* FindInjectedNode(int32 Index) const override;`
- L65 _public prototype_ `virtual void DoubleClickNode(class UEdGraphNode* Node) override;`
- L66 _public prototype_ `virtual void FocusAttentionOnNode(UEdGraphNode* Node) override;`
- L67 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn = NULL) override;`
- L71 _public prototype_ `virtual bool IncludeAssetInRestoreOpenAssetsPrompt(UObject* Asset) const override;`
- L75 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L76 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L80 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;`
- L84 _public prototype_ `void OnNodeDoubleClicked(class UEdGraphNode* Node);` — Delegates
- L85 _public prototype_ `void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);`
- L86 _public prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);`
- L88 _public prototype_ `void OnAddInputPin();`
- L89 _public prototype_ `bool CanAddInputPin() const;`
- L90 _public prototype_ `void OnRemoveInputPin();`
- L91 _public prototype_ `bool CanRemoveInputPin() const;`
- L93 _public prototype_ `void OnEnableBreakpoint();`
- L94 _public prototype_ `bool CanEnableBreakpoint() const;`
- L95 _public prototype_ `void OnToggleBreakpoint();`
- L96 _public prototype_ `bool CanToggleBreakpoint() const;`
- L97 _public prototype_ `void OnDisableBreakpoint();`
- L98 _public prototype_ `bool CanDisableBreakpoint() const;`
- L99 _public prototype_ `void OnAddBreakpoint();`
- L100 _public prototype_ `bool CanAddBreakpoint() const;`
- L101 _public prototype_ `void OnRemoveBreakpoint();`
- L102 _public prototype_ `bool CanRemoveBreakpoint() const;`
- L104 _public prototype_ `void SearchTree();`
- L105 _public prototype_ `bool CanSearchTree() const;`
- L107 _public prototype_ `void JumpToNode(const UEdGraphNode* Node);`
- L109 _public prototype_ `bool IsPropertyEditable() const;`
- L110 _public prototype_ `void OnPackageSaved(const FString& PackageFileName, UPackage* Package, FObjectPostSaveContext ObjectSaveContext);`
- L111 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L112 _public prototype_ `virtual void OnClassListUpdated() override;`
- L114 _public prototype_ `void UpdateToolbar();`
- L115 _public prototype_ `bool IsDebuggerReady() const;`
- L118 _public prototype_ `bool IsDebuggerPaused() const;` — Get whether the debugger is currently running and the PIE session is paused
- L121 _public prototype_ `bool CanEditWithDebuggerActive() const;` — Get whether we can edit the tree/blackboard with the debugger active
- L123 _public prototype_ `TSharedRef<class SWidget> OnGetDebuggerActorsMenu();`
- L124 _public prototype_ `void OnDebuggerActorSelected(TWeakObjectPtr<UBehaviorTreeComponent> InstanceToDebug);`
- L125 _public prototype_ `FText GetDebuggerActorDesc() const;`
- L126 _public prototype_ `FGraphAppearanceInfo GetGraphAppearance() const;`
- L127 _public prototype_ `bool InEditingMode(bool bGraphIsEditable) const;`
- L129 _public prototype_ `void DebuggerSwitchAsset(UBehaviorTree* NewAsset);`
- L130 _public prototype_ `void DebuggerUpdateGraph();`
- L132 _public prototype_ `EVisibility GetDebuggerDetailsVisibility() const;`
- L133 _public prototype_ `EVisibility GetRangeLowerVisibility() const;`
- L134 _public prototype_ `EVisibility GetRangeSelfVisibility() const;`
- L135 _public prototype_ `EVisibility GetInjectedNodeVisibility() const;`
- L136 _public prototype_ `EVisibility GetRootLevelNodeVisibility() const;`
- L138 _public prototype_ `TWeakPtr<SGraphEditor> GetFocusedGraphPtr() const;`
- L141 _public prototype_ `bool CanAccessBehaviorTreeMode() const;` — Check whether the behavior tree mode can be accessed (i.e whether we have a valid tree to edit)
- L144 _public prototype_ `bool CanAccessBlackboardMode() const;` — Check whether the blackboard mode can be accessed (i.e whether we have a valid blackboard to edit)
- L151 _public prototype_ `static FText GetLocalizedMode(FName InMode);` — Get the localized text to display for the specified mode @param	InMode	The mode to display @return the localized text representation of the mode
- L154 _public function_ `TSharedPtr<class FBehaviorTreeEditorToolbar> GetToolbarBuilder()` — Access the toolbar builder for this editor
- L157 _public prototype_ `UBehaviorTree* GetBehaviorTree() const;` — Get the behavior tree we are editing (if any)
- L160 _public prototype_ `UBlackboardData* GetBlackboardData() const;` — Get the blackboard we are editing (if any)
- L163 _public prototype_ `TSharedRef<SWidget> SpawnProperties();` — Spawns the tab with the update graph inside
- L166 _public prototype_ `TSharedRef<SWidget> SpawnSearch();` — Spawns the search tab
- L169 _public prototype_ `TSharedRef<SWidget> SpawnBlackboardDetails();` — Spawn blackboard details tab
- L172 _public prototype_ `TSharedRef<SWidget> SpawnBlackboardView();` — Spawn blackboard view tab
- L175 _public prototype_ `TSharedRef<SWidget> SpawnBlackboardEditor();` — Spawn blackboard editor tab
- L178 _public prototype_ `void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);` — @todo This is a hack for now until we reconcile the default toolbar with application modes [duplicated from counterpart in Blueprint Editor]
- L181 _public prototype_ `void RestoreBehaviorTree();` — Restores the behavior tree graph we were editing or creates a new one if none is available
- L184 _public prototype_ `void SaveEditedObjectState();` — Save the graph state for later editing
- L187 _public prototype_ `void HandleBlackboardEntrySelected(const FBlackboardEntry* BlackboardEntry, bool bIsInherited);` — Delegate handler for selection in the blackboard entry list
- L190 _public prototype_ `int32 HandleGetSelectedBlackboardItemIndex(bool& bOutIsInherited);` — Delegate handler used to retrieve current blackboard selection
- L193 _public prototype_ `FText HandleGetDebugKeyValue(const FName& InKeyName, bool bUseCurrentState) const;` — Delegate handler for displaying debugger values
- L196 _public prototype_ `double HandleGetDebugTimeStamp(bool bUseCurrentState) const;` — Delegate handler for retrieving timestamp to display
- L199 _public prototype_ `void HandleDebuggedBlackboardChanged(UBlackboardData* InObject);` — Delegate handler for when the debugged blackboard changes
- L202 _public prototype_ `bool HandleGetDisplayCurrentState() const;` — Delegate handler for determining whether to display the current state
- L205 _public prototype_ `bool HandleIsBlackboardModeActive() const;` — Check whether blackboard mode is current
- L208 _public prototype_ `void GetBlackboardSelectionInfo(int32& OutSelectionIndex, bool& bOutIsInherited) const;` — Get the currently selected blackboard entry
- L211 _public prototype_ `bool CanCreateNewTask() const;` — Check to see if we can create a new task node
- L214 _public prototype_ `bool CanCreateNewDecorator() const;` — Check to see if we can create a new decorator node
- L217 _public prototype_ `bool CanCreateNewService() const;` — Check to see if we can create a new service node
- L220 _public prototype_ `TSharedRef<SWidget> HandleCreateNewTaskMenu() const;` — Create the menu used to make a new task node
- L223 _public prototype_ `TSharedRef<SWidget> HandleCreateNewDecoratorMenu() const;` — Create the menu used to make a new decorator
- L226 _public prototype_ `TSharedRef<SWidget> HandleCreateNewServiceMenu() const;` — Create the menu used to make a new service
- L229 _public prototype_ `void HandleNewNodeClassPicked(UClass* InClass) const;` — Handler for when a node class is picked
- L232 _public prototype_ `void CreateNewTask() const;` — Create a new task from UBTTask_BlueprintBase
- L235 _public prototype_ `bool IsNewTaskButtonVisible() const;` — Whether the single button to create a new Blueprint-based task is visible
- L238 _public prototype_ `bool IsNewTaskComboVisible() const;` — Whether the combo button to create a new Blueprint-based task from all available base classes is visible
- L241 _public prototype_ `void CreateNewDecorator() const;` — Create a new decorator from UBTDecorator_BlueprintBase
- L244 _public prototype_ `bool IsNewDecoratorButtonVisible() const;` — Whether the single button to create a new Blueprint-based decorator is visible
- L247 _public prototype_ `bool IsNewDecoratorComboVisible() const;` — Whether the combo button to create a new Blueprint-based decorator from all available base classes is visible
- L250 _public prototype_ `void CreateNewService() const;` — Create a new service from UBTService_BlueprintBase
- L253 _public prototype_ `bool IsNewServiceButtonVisible() const;` — Whether the single button to create a new Blueprint-based service is visible
- L256 _public prototype_ `bool IsNewServiceComboVisible() const;` — Whether the combo button to create a new Blueprint-based service from all available base classes is visible
- L259 _public prototype_ `void CreateNewBlackboard();` — Create a new Blackboard alongside the currently-edited behavior tree
- L262 _public prototype_ `bool CanCreateNewBlackboard() const;` — Whether we can currently create a new Blackboard
- L266 _protected prototype_ `virtual void SaveAsset_Execute() override;` — Called when "Save" is clicked for this asset
- L268 _protected prototype_ `void SetToolbarCreateActionsEnabled(bool bActionsEnabled);`
- L270 _protected member_ `TSubclassOf<UBehaviorTreeGraph> GraphClass;`
- L271 _protected member_ `FName GraphName;`
- L272 _protected member_ `FText CornerText;`
- L273 _protected member_ `FText TitleText;`
- L274 _protected member_ `FText RootNodeNoteText;`
- L278 _private prototype_ `TSharedRef<class SGraphEditor> CreateGraphEditorWidget(UEdGraph* InGraph);` — Create widget for graph editing
- L281 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L284 _private prototype_ `void ExtendMenu();` — Add custom menu options
- L287 _private prototype_ `void BindCommonCommands();` — Setup common commands
- L290 _private prototype_ `void BindDebuggerToolbarCommands();` — Setup commands
- L293 _private prototype_ `virtual void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection) override;` — Called when the selection changes in the GraphEditor
- L296 _private prototype_ `void GetAbortModePreview(const class UBehaviorTreeGraphNode_CompositeDecorator* Node, struct FAbortDrawHelper& Mode0, struct FAbortDrawHelper& Mode1);` — prepare range of nodes that can be aborted by this decorator
- L299 _private prototype_ `void GetAbortModePreview(const class UBTDecorator* DecoratorOb, struct FAbortDrawHelper& Mode0, struct FAbortDrawHelper& Mode1);` — prepare range of nodes that can be aborted by this decorator
- L302 _private prototype_ `void RefreshDebugger();` — Refresh the debugger's display
- L305 _private prototype_ `void RefreshBlackboardViewsAssociatedObject();` — Push new associated Blackboard data to Blackboard views
- L307 _private member_ `TSharedPtr<FDocumentTracker> DocumentManager;`
- L308 _private member_ `TWeakPtr<FDocumentTabFactory> GraphEditorTabFactoryPtr;`
- L311 _private member_ `UBehaviorTree* BehaviorTree;` — The Behavior Tree being edited
- L314 _private member_ `UBlackboardData* BlackboardData;` — The Blackboard Data being edited
- L316 _private member_ `TWeakObjectPtr<class UBehaviorTreeGraphNode_CompositeDecorator> FocusedGraphOwner;`
- L319 _private member_ `TSharedPtr<class IDetailsView> DetailsView;` — Property View
- L321 _private member_ `TSharedPtr<class FBehaviorTreeDebugger> Debugger;`
- L324 _private member_ `TSharedPtr<class SFindInBT> FindResults;` — Find results log as well as the search filter
- L326 _private member_ `uint32 bShowDecoratorRangeLower : 1;`
- L327 _private member_ `uint32 bShowDecoratorRangeSelf : 1;`
- L328 _private member_ `uint32 bForceDisablePropertyEdit : 1;`
- L329 _private member_ `uint32 bSelectedNodeIsInjected : 1;`
- L330 _private member_ `uint32 bSelectedNodeIsRootLevel : 1;`
- L332 _private member_ `uint32 bHasMultipleTaskBP : 1;`
- L333 _private member_ `uint32 bHasMultipleDecoratorBP : 1;`
- L334 _private member_ `uint32 bHasMultipleServiceBP : 1;`
- L336 _private member_ `TSharedPtr<class FBehaviorTreeEditorToolbar> ToolbarBuilder;`
- L339 _private member_ `TSharedPtr<IDetailsView> BlackboardDetailsView;` — The details view we use to display the blackboard
- L342 _private member_ `TSharedPtr<class SBehaviorTreeBlackboardView> BlackboardView;` — The blackboard view widget
- L345 _private member_ `TSharedPtr<class SBehaviorTreeBlackboardEditor> BlackboardEditor;` — The blackboard editor widget
- L348 _private member_ `int32 CurrentBlackboardEntryIndex;` — The current blackboard selection index, stored here so it can be accessed by our details customization
- L351 _private member_ `bool bIsCurrentBlackboardEntryInherited;` — Whether the current selection is inherited, stored here so it can be accessed by our details customization
- L354 _private member_ `FDelegateHandle OnPackageSavedDelegateHandle;` — Handle to the registered OnPackageSave delegate
- L358 _public member_ `static const FName BehaviorTreeMode;` — Modes in mode switcher
- L359 _public member_ `static const FName BlackboardMode;`
- L361 _public member_ `static FText BehaviorTreeModeText;`
- L362 _public member_ `static FText BlackboardModeText;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API BEHAVIORTREEEDITOR_API`

### `Source/Editor/BehaviorTreeEditor/Public/BehaviorTreeEditorModule.h` (Public)


#### class `FBehaviorTreeEditorModule`  
`class FBehaviorTreeEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L17-41_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Behavior Tree Editor module
- L21 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public prototype_ `virtual TSharedRef<IBehaviorTreeEditor> CreateBehaviorTreeEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* Object);` — Creates an instance of Behavior Tree editor.  Only virtual so that it can be called across the DLL boundary.
- L28 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L29 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L31 _public function_ `TSharedPtr<FGraphNodeClassHelper> GetClassCache() const`
- L34 _public member_ `static const FName BehaviorTreeEditorAppIdentifier;` — Behavior Tree app identifier string
- L37 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L38 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L40 _private member_ `TSharedPtr<FGraphNodeClassHelper> ClassCache;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBehaviorTreeEditor, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBehaviorTreeEditor, Log, All);`

### `Source/Editor/BehaviorTreeEditor/Public/IBehaviorTreeEditor.h` (Public)


#### class `IBehaviorTreeEditor`  
`class IBehaviorTreeEditor : public FWorkflowCentricApplication`  
_L12-20_
- inherits: `FWorkflowCentricApplication`
- desc: BT Editor public interface
- L16 _public prototype_ `virtual void InitializeDebuggerState(class FBehaviorTreeDebugger* ParentDebugger) const = 0;`
- L17 _public prototype_ `virtual UEdGraphNode* FindInjectedNode(int32 Index) const = 0;`
- L18 _public prototype_ `virtual void DoubleClickNode(class UEdGraphNode* Node) = 0;`
- L19 _public prototype_ `virtual void FocusAttentionOnNode(UEdGraphNode* Node) = 0;`
