# Plugins / SceneStateMachineEditor

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor`
- headers: 18; symbols: 278
- symbol kinds: class=17, enum=1, enumerator=4, function=12, macro=1, member=69, namespace=64, prototype=94, struct=10, typedef=6
- PrivateDependencyModuleNames: GraphEditor, Projects, PropertyEditor, SceneState, SceneStateTransitionGraph, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneStateMachineGraph

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/SceneStateMachineConnectionDrawingPolicy.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineConnectionDrawingPolicy`  
`class FStateMachineConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L10-35_
- inherits: `FConnectionDrawingPolicy`
- L13 _public prototype_ `explicit FStateMachineConnectionDrawingPolicy(int32 InBackLayerID , int32 InFrontLayerID , float InZoomFactor , const FSlateRect& InClippingRect , FSlateWindowElementList& InDrawElements);`
- L21 _private prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* InOutputPin, UEdGraphPin* InInputPin, FConnectionParams& InOutParams) override;`
- L22 _private prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& InArrangedNodes) override;`
- L23 _private prototype_ `virtual void DetermineLinkGeometry(FArrangedChildren& InArrangedNodes, TSharedRef<SWidget>& InOutputPinWidget, UEdGraphPin* InOutputPin, UEdGraphPin* InInputPin, FArrangedWidget*& OutStartWidgetGeometry, FArrangedWidget*& OutEndWidgetGeometry) override;`
- L24 _private prototype_ `virtual void DrawSplineWithArrow(const FGeometry& InStartGeometry, const FGeometry& InEndGeometry, const FConnectionParams& InParams) override;`
- L25 _private prototype_ `virtual void DrawSplineWithArrow(const FVector2f& InStartPoint, const FVector2f& InEndPoint, const FConnectionParams& InParams) override;`
- L26 _private prototype_ `virtual void DrawPreviewConnector(const FGeometry& InPinGeometry, const FVector2f& InStartPoint, const FVector2f& InEndPoint, UEdGraphPin* InPin) override;`
- L27 _private prototype_ `virtual FVector2f ComputeSplineTangent(const FVector2f& InStart, const FVector2f& InEnd) const override;`
- L30 _private prototype_ `void DrawArrowLine(const FVector2f& InStartPoint, const FVector2f& InEndPoint, const FConnectionParams& InParams);`
- L32 _private prototype_ `void DrawCircle(const FVector2f& InCenter, float InRadius, const FLinearColor& InColor, int32 InSegments);`
- L34 _private member_ `TMap<FObjectKey, int32> NodeWidgetMap;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/SceneStateMachineEdGraphFactory.h` (Private)


#### struct `UE::SceneState::Editor::FStateMachineEdGraphNodeFactory`  
`struct FStateMachineEdGraphNodeFactory : FGraphPanelNodeFactory`  
_L11-29_
- inherits: `FGraphPanelNodeFactory`
- L14 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override;`
- L18 _public function_ `template<typename InNodeType, typename InGraphNodeType> void RegisterDefaultNodeFactory()`
- L28 _private member_ `TMap<UClass*, TFunction<TSharedPtr<SGraphNode>(UEdGraphNode*)>> NodeFactories;`

#### struct `UE::SceneState::Editor::FStateMachineEdGraphPinFactory`  
`struct FStateMachineEdGraphPinFactory : FGraphPanelPinFactory`  
_L31-36_
- inherits: `FGraphPanelPinFactory`
- L34 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* InPin) const override;`

#### struct `UE::SceneState::Editor::FStateMachineEdGraphPinConnectionFactory`  
`struct FStateMachineEdGraphPinConnectionFactory : FGraphPanelPinConnectionFactory`  
_L38-43_
- inherits: `FGraphPanelPinConnectionFactory`
- L41 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionPolicy(const UEdGraphSchema* InSchema, int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraph) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L22 _function_ `` (scope `UE::SceneState::Editor::FStateMachineEdGraphNodeFactory::RegisterDefaultNodeFactory`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/SceneStateMachineEditorModule.h` (Private)


#### class `UE::SceneState::Editor::FStateStateMachineEditorModule`  
`class FStateStateMachineEditorModule : public IModuleInterface`  
_L18-33_
- inherits: `IModuleInterface`
- L21 _private prototype_ `virtual void StartupModule() override;`
- L22 _private prototype_ `virtual void ShutdownModule() override;`
- L25 _private prototype_ `void RegisterGraphFactories();`
- L26 _private prototype_ `void UnregisterGraphFactories();`
- L28 _private member_ `TSharedPtr<FStateMachineEdGraphNodeFactory> NodeFactory;`
- L30 _private member_ `TSharedPtr<FStateMachineEdGraphPinFactory> PinFactory;`
- L32 _private member_ `TSharedPtr<FStateMachineEdGraphPinConnectionFactory> PinConnectionFactory;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SceneState` (scope `UE`)
- L8 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L15 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/SceneStateMachineEditorStyle.h` (Private)


#### class `UE::SceneState::Editor::FStateMachineEditorStyle`  
`class FStateMachineEditorStyle : public FSlateStyleSet`  
_L10-32_
- inherits: `FSlateStyleSet`
- L13 _public function_ `static FStateMachineEditorStyle& Get()`
- L19 _public function_ `const FNumberFormattingOptions& GetDefaultNumberFormat() const`
- L25 _private prototype_ `FStateMachineEditorStyle();`
- L29 _private prototype_ `void RegisterGraphStyles();`
- L31 _private member_ `const FNumberFormattingOptions DefaultNumberFormat;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineConduitNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineConduitNode`  
`class SStateMachineConduitNode : public SStateMachineNode`  
_L12-29_
- inherits: `SStateMachineNode`
- L15 _public typedef_ `using Super = SStateMachineNode;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStateMachineConduitNode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineConduitNode* InNode);`
- L23 _private prototype_ `TSharedRef<SWidget> MakeNodeInnerWidget();`
- L26 _private prototype_ `virtual void UpdateGraphNode() override;`
- L27 _private prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineEntryNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineEntryNode`  
`class SStateMachineEntryNode : public SStateMachineNode`  
_L12-27_
- inherits: `SStateMachineNode`
- L15 _public typedef_ `using Super = SStateMachineNode;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStateMachineEntryNode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineEntryNode* InNode);`
- L24 _private prototype_ `virtual void UpdateGraphNode() override;`
- L25 _private prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bInSelected) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineEntryPin.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineEntryPin`  
`class SStateMachineEntryPin : public SGraphPin`  
_L10-20_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(SStateMachineEntryPin)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L19 _private prototype_ `const FSlateBrush* GetEntryPinBorder() const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineExitNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineExitNode`  
`class SStateMachineExitNode : public SStateMachineNode`  
_L12-27_
- inherits: `SStateMachineNode`
- L15 _public typedef_ `using Super = SStateMachineNode;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStateMachineExitNode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineExitNode* InNode);`
- L24 _private prototype_ `virtual void UpdateGraphNode() override;`
- L25 _private prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bInSelected) const override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineNode`  
`class SStateMachineNode : public SGraphNode`  
_L13-23_
- inherits: `SGraphNode`
- desc: Base class for State Machine Graph Nodes
- L16 _protected prototype_ `virtual void AddPinWidgetToSlot(const TSharedRef<SGraphPin>& InPinWidget);`
- L19 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L20 _protected prototype_ `virtual void CreateStandardPinWidget(UEdGraphPin* InPin) override;`
- L21 _protected prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& InPinWidget) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineOutputPin.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineOutputPin`  
`class SStateMachineOutputPin : public SGraphPin`  
_L10-24_
- inherits: `SGraphPin`
- L13 _public function_ `SLATE_BEGIN_ARGS(SStateMachineOutputPin)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L20 _private prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L23 _private prototype_ `const FSlateBrush* GetOutputPinBorder() const;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SceneState` (scope `UE`)
- L7 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineStateNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineStateNode`  
`class SStateMachineStateNode : public SStateMachineNode`  
_L13-58_
- inherits: `SStateMachineNode`
- L16 _public typedef_ `using Super = SStateMachineNode;`
- L18 _public function_ `SLATE_BEGIN_ARGS(SStateMachineStateNode)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineStateNode* InNode);`
- L24 _private prototype_ `TSharedRef<SWidget> MakeNodeInnerWidget();`
- L26 _private prototype_ `FSlateColor GetStateBackgroundColor() const;`
- L29 _private prototype_ `virtual void UpdateGraphNode() override;`
- L30 _private prototype_ `virtual void AddPinWidgetToSlot(const TSharedRef<SGraphPin>& InPinWidget);`
- L31 _private prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L35 _private prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* InContext, TArray<FGraphInformationPopupInfo>& OutPopups) const;`
- L39 _private prototype_ `virtual void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L40 _private prototype_ `virtual void OnMouseLeave(const FPointerEvent& InMouseEvent) override;`
- L43 _private member_ `TSharedPtr<SOverlay> OutputPinOverlay;`
- L45 _private member_ `FLinearColor ActiveColor = FLinearColor(ForceInit);`
- L46 _private member_ `FLinearColor FinishedColor = FLinearColor(ForceInit);`
- L47 _private member_ `FLinearColor InactiveColor = FLinearColor(ForceInit);`
- L54 _private member_ `mutable float ActivePercentage = 0.f;` — Represents how 'active' the state is 1 means fully active, 0 means fully inactive. When multiple instances are active, it will use the highest value.
- L57 _private member_ `mutable TOptional<EExecutionStatus> StateStatus;` — Whether the state should show the finish color instead of the active color

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SceneState` (scope `UE`)
- L10 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineTaskNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineTaskNode`  
`class SStateMachineTaskNode : public SStateMachineNode`  
_L17-55_
- inherits: `SStateMachineNode`
- L20 _public typedef_ `using Super = SStateMachineNode;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SStateMachineTaskNode)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineTaskNode* InNode);`
- L30 _private prototype_ `TSharedRef<SWidget> MakeNodeInnerWidget();`
- L32 _private prototype_ `FSlateColor GetTaskBackgroundColor() const;`
- L35 _private prototype_ `virtual void UpdateGraphNode() override;`
- L36 _private prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L40 _private prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* InContext, TArray<FGraphInformationPopupInfo>& OutPopups) const;`
- L44 _private prototype_ `void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L45 _private prototype_ `void OnMouseLeave(const FPointerEvent& InMouseEvent) override;`
- L48 _private member_ `TSharedPtr<SNodeTitle> NodeTitle;`
- L50 _private member_ `TWeakObjectPtr<USceneStateMachineTaskNode> TaskNodeWeak;`
- L52 _private member_ `TMap<EExecutionStatus, FLinearColor> StatusColors;`
- L54 _private member_ `mutable EExecutionStatus TaskStatus = EExecutionStatus::NotStarted;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SceneState` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Private/Widgets/SSceneStateMachineTransitionNode.h` (Private)


#### class `UE::SceneState::Editor::SStateMachineTransitionNode`  
`class SStateMachineTransitionNode : public SStateMachineNode`  
_L12-53_
- inherits: `SStateMachineNode`
- L15 _public typedef_ `using Super = SStateMachineNode;`
- L17 _public function_ `SLATE_BEGIN_ARGS(SStateMachineTransitionNode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USceneStateMachineTransitionNode* InNode);`
- L24 _private prototype_ `virtual void MoveTo(const FVector2f& InNewPosition, FNodeSet& InNodeFilter, bool bInMarkDirty) override;`
- L25 _private prototype_ `virtual bool RequiresSecondPassLayout() const override;`
- L26 _private prototype_ `virtual void PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& InNodeToWidgetLookup) const override;`
- L30 _private prototype_ `virtual void UpdateGraphNode() override;`
- L31 _private prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L35 _private prototype_ `void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L36 _private prototype_ `void OnMouseLeave(const FPointerEvent& InMouseEvent) override;`
- L40 _private prototype_ `void PositionBetweenTwoNodesWithOffset(const FGeometry& InStartGeometry, const FGeometry& InEndGeometry, int32 InNodeIndex, int32 InMaxNodes) const;` — Calculate position for multiple nodes to be placed between a start and end point, by providing this nodes index and max expected nodes
- L42 _private prototype_ `TSharedRef<SWidget> GenerateTooltip();`
- L44 _private prototype_ `FText GetPreviewCornerText() const;`
- L46 _private member_ `TSharedPtr<STextEntryPopup> TextEntryWidget;`
- L49 _private member_ `mutable TWeakPtr<SNode> SourceNodeWidgetWeak;` — Cache of the widget representing the source state node
- L51 _private member_ `static const FLinearColor ActiveColor;`
- L52 _private member_ `static const FLinearColor HoverColor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SceneState` (scope `UE`)
- L9 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Public/ISceneStateMachineCompilerContext.h` (Public)


#### enum `UE::SceneState::Editor::ETransitionGraphCompileReturnCode`  
`enum class ETransitionGraphCompileReturnCode : uint8`  
_L14-27_
- L17 _public enumerator_ `Success` — Succeeded compiling transition graph
- L20 _public enumerator_ `Failed` — Failed to compile transition graph due to errors
- L23 _public enumerator_ `SkippedAlwaysFalse` — Transition graph not compiled because it's always going to evaluate to false
- L26 _public enumerator_ `SkippedAlwaysTrue` — Transition graph not compiled because it's always going to evaluate to true

#### struct `UE::SceneState::Editor::FTransitionGraphCompileResult`  
`struct FTransitionGraphCompileResult`  
_L29-37_
- L32 _public member_ `ETransitionGraphCompileReturnCode ReturnCode;` — Return code of the graph compilation, whether it succeeded, failed, etc.
- L34 _public member_ `FName EventName;` — Compiled event name to call (if any)
- L36 _public member_ `FName ResultPropertyName;` — Name of the result property that the event name will write to when called

#### class `UE::SceneState::Editor::IStateMachineCompilerContext`  
`class IStateMachineCompilerContext`  
_L40-48_
- desc: Interface to get data or execute functionality out of the scope of the compiler
- L44 _public prototype_ `virtual USceneStateTemplateData* GetTemplateData() = 0;` — Gets the template data to compile the objects to
- L47 _public prototype_ `virtual FTransitionGraphCompileResult CompileTransitionGraph(USceneStateTransitionGraph* InTransitionGraph) = 0;` — Requests compilation of the given transition graph

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SceneState` (scope `UE`)
- L11 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Public/SceneStateMachineCompiler.h` (Public)


#### class `UE::SceneState::Editor::FStateMachineCompiler`  
`class FStateMachineCompiler`  
_L34-115_
- L37 _public prototype_ `explicit FStateMachineCompiler(USceneStateMachineGraph* InGraph, IStateMachineCompilerContext& InCompilerContext);`
- L39 _public prototype_ `FSceneStateMachine Compile();`
- L43 _private prototype_ `void CompileState(const USceneStateMachineStateNode* InStateNode);` — Compiles a single state (compiles state's tasks, substate machines)
- L46 _private prototype_ `void FollowTransitions(TConstArrayView<USceneStateMachineTransitionNode*> InExitTransitions);` — Follows the given transitions to gather more states and conduits to process
- L49 _private prototype_ `void CompileSubStateMachines(FSceneState& InNewState, const USceneStateMachineStateNode* InStateNode);` — Compiles the substate machines for a given state
- L52 _private prototype_ `void AddConduitToCompile(const USceneStateMachineConduitNode* InConduitNode);` — Adds the given conduit for later compilation
- L55 _private prototype_ `void CompileTasks(FSceneState& InNewState, const USceneStateMachineStateNode* InStateNode);` — Compiles the tasks connected to the state node, and writes the result into the given new state
- L58 _private prototype_ `void CompileEventHandlers(FSceneState& InNewState, const USceneStateMachineStateNode* InStateNode);` — Compiles the events handlers in the state node, and writes the result into the given new state
- L61 _private prototype_ `void FinishTransitionCompilation(FSceneStateRange& OutTransitionRange, FStateMachineTransitionCompileResult&& InCompileResult);` — Adds the compile result's transitions to the generated class, and returns the transition range mapping these transitions
- L64 _private prototype_ `void CompileStateTransitions(FSceneState& InNewState, const USceneStateMachineStateNode* InStateNode);` — Compiles the transitions exiting the given state node, and writes the result into the given new state
- L67 _private prototype_ `void CompileConduit(const USceneStateMachineConduitNode* InConduitNode);` — Compiles the given conduit node, and writes the result into the given new conduit
- L69 _private prototype_ `UObject* DuplicateObject(FObjectDuplicationParameters& InDuplicationParams);`
- L72 _private member_ `TObjectPtr<USceneStateTemplateData> TemplateData;` — Template data where all the compiled objects will be allocated to
- L75 _private member_ `TObjectPtr<USceneStateMachineGraph> StateMachineGraph;` — Reference Graph that will build out the runtime State Machine object
- L78 _private member_ `TObjectPtr<UBlueprint> Blueprint;` — Blueprint owning the state machine graph, if any
- L81 _private member_ `IStateMachineCompilerContext& Context;` — Context used for compiling the State Machine Graph
- L87 _private member_ `TMap<FObjectKey, uint16> StateNodeIndexMap;` — Map of a State Node to the index of the States array below This is also used to avoid re-processing the same state
- L90 _private member_ `TMap<FGuid, uint16> StateParameterIdIndexMap;` — Map of a State's parameter id to the index of the states array below
- L93 _private member_ `TArray<FSceneState> States;` — Compiled States
- L96 _private member_ `TArray<FSceneStateMetadata> StateMetadata;` — Compiled State Metadata
- L99 _private member_ `TArray<const USceneStateMachineStateNode*> StateNodesToProcess;` — State nodes to process in an iteration (does not contain all the nodes)
- L102 _private member_ `TArray<const USceneStateMachineConduitNode*> ConduitNodesToCompile;` — Conduit nodes to process in an iteration. Should contain all conduit nodes to compile
- L108 _private member_ `TMap<FObjectKey, uint16> ConduitNodeIndexMap;` — Map of a Conduit Node to the index of the States array below This is also used to avoid re-processing the same state
- L111 _private member_ `TArray<FSceneStateConduit> Conduits;` — Compiled Conduits
- L114 _private member_ `TArray<FSceneStateConduitLink> ConduitLinks;` — Compiled Conduit Links

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCENESTATEMACHINEEDITOR_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace SceneState` (scope `UE`)
- L25 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace SceneState` (scope `UE`)
- L31 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Public/SceneStateMachineConduitCompiler.h` (Public)


#### struct `UE::SceneState::Editor::FStateMachineConduitCompileResult`  
`struct FStateMachineConduitCompileResult`  
_L16-24_
- L19 _public member_ `FSceneStateConduit Conduit;` — Compiled conduit. Without the missing Transition Range (to be generated by the finish compilation process)
- L21 _public member_ `FSceneStateConduitLink ConduitLink;` — Compiled conduit link
- L23 _public member_ `FStateMachineTransitionCompileResult TransitionCompileResult;` — Compiled conduit exit transitions

#### class `UE::SceneState::Editor::FStateMachineConduitCompiler`  
`class FStateMachineConduitCompiler`  
_L27-58_
- desc: Compiles the given conduit node into transitions, links, etc
- L41 _public prototype_ `explicit FStateMachineConduitCompiler(const FCompileParams& InParams);`
- L44 _public prototype_ `bool Compile(FStateMachineConduitCompileResult& OutResult);` — Compiles the conduit node
- L48 _private prototype_ `bool CompileConduitGraph();` — Compiles the transition graph within the conduit itself (not the exit transitions')
- L51 _private prototype_ `void CompileExitTransitions();` — Compiles the exit transitions of the conduit
- L54 _private member_ `const FCompileParams& Params;` — Parameters for compilation
- L57 _private member_ `FStateMachineConduitCompileResult Result;` — Result of the compilation

#### struct `UE::SceneState::Editor::FStateMachineConduitCompiler::FCompileParams`  
`struct FCompileParams`  
_L30-40_
- L33 _public member_ `IStateMachineCompilerContext& Context;` — Compiler context interface for compilation required outside the scope of this compiler
- L35 _public member_ `const USceneStateMachineConduitNode* ConduitNode;` — Conduit node to compile, along with its exit transitions
- L37 _public member_ `const TMap<FObjectKey, uint16>& StateNodeIndexMap;` — Used to look up the index, relative in state machine space, for a given state node
- L39 _public member_ `const TMap<FObjectKey, uint16>& ConduitNodeIndexMap;` — Used to look up the index, relative in state machine space, for a given conduit node

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SceneState` (scope `UE`)
- L13 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Public/SceneStateMachineTaskCompiler.h` (Public)


#### class `UE::SceneState::Editor::FStateMachineTaskCompiler`  
`class FStateMachineTaskCompiler`  
_L21-70_
- L39 _public prototype_ `explicit FStateMachineTaskCompiler(UEdGraphPin* InSourceOutputPin, UObject* InOuter);`
- L54 _public prototype_ `void Compile(FCompileResult& OutCompileResult);`
- L57 _private prototype_ `static FTaskInfo MakeTaskInfo(USceneStateMachineTaskNode* InNode);`
- L59 _private prototype_ `void GatherTasks(UEdGraphPin* InOutputPin);`
- L61 _private prototype_ `void CompileTasks(FCompileResult& OutCompilationResult);`
- L63 _private member_ `UEdGraphPin* SourceOutputPin;`
- L65 _private member_ `TObjectPtr<UObject> Outer;`
- L67 _private member_ `TArray<FTaskInfo> TaskInfos;`
- L69 _private member_ `TMap<FObjectKey, uint16> ProcessedNodes;`

#### struct `UE::SceneState::Editor::FStateMachineTaskCompiler::FTaskInfo`  
`struct FTaskInfo`  
_L24-36_
- desc: Information about a node to compile
- L27 _public member_ `TConstStructView<FSceneStateTask> Task;` — View of the task in the task node to compile
- L29 _public member_ `TConstStructView<FSceneStateTaskInstance> TaskInstance;` — View of the task instance in the task node to compile
- L31 _public member_ `FSceneStateTaskMetadata Metadata;` — Metadata compiled from the node for editor-only runtime
- L33 _public member_ `TObjectPtr<const USceneStateMachineTaskNode> Node;` — The task node to compile
- L35 _public member_ `TArray<const USceneStateMachineTaskNode*> Prerequisites;` — Prerequisite nodes that need to complete before this task executes

#### struct `UE::SceneState::Editor::FStateMachineTaskCompiler::FCompileResult`  
`struct FCompileResult`  
_L41-53_
- L44 _public member_ `TArray<FInstancedStruct> Tasks;` — Compiled FSceneStateTask instances
- L46 _public member_ `TArray<uint16> TaskPrerequisites;` — Compiled Task prerequisites
- L48 _public member_ `TArray<FConstStructView> TaskInstances;` — The nodes' task instance views
- L50 _public member_ `TArray<FSceneStateTaskMetadata> TaskMetadata;` — Additional editor-only metadata gotten from the node
- L52 _public member_ `TMap<FObjectKey, uint16> TaskToIndexMap;` — Map of the task node to the index in the task array

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SceneState` (scope `UE`)
- L18 _namespace_ `namespace Editor` (scope `UE::SceneState`)

### `Plugins/VirtualProduction/SceneState/Source/SceneStateMachineEditor/Public/SceneStateMachineTransitionCompiler.h` (Public)


#### struct `UE::SceneState::Editor::FStateMachineTransitionCompileResult`  
`struct FStateMachineTransitionCompileResult`  
_L32-38_
- L34 _public member_ `TArray<FSceneStateTransition> Transitions;`
- L35 _public member_ `TArray<FSceneStateTransitionLink> Links;`
- L36 _public member_ `TArray<FSceneStateTransitionMetadata> Metadata;`
- L37 _public member_ `TArray<FInstancedPropertyBag> Parameters;`

#### class `UE::SceneState::Editor::FStateMachineTransitionCompiler`  
`class FStateMachineTransitionCompiler`  
_L41-74_
- desc: Compiles the exit transitions of a given state node into a series of arrays
- L55 _public prototype_ `explicit FStateMachineTransitionCompiler(const FCompileParams& InParams);`
- L57 _public prototype_ `void Compile(FStateMachineTransitionCompileResult& OutResult);`
- L61 _private prototype_ `bool IsNodeValid(const USceneStateMachineTransitionNode* InTransitionNode) const;` — Determines whether the given node has a valid target
- L64 _private prototype_ `void CompileTransitionNode(const USceneStateMachineTransitionNode* InTransitionNode);` — Compiles a single transition node
- L67 _private prototype_ `FSceneStateTransition BuildTransition(const USceneStateMachineTransitionNode* InTransitionNode, const FTransitionGraphCompileResult& InGraphCompileResult);` — Builds the transition target based on the transition node's target node. Does not deal with the Transition Target yet
- L70 _private member_ `const FCompileParams& Params;` — Parameters for compilation
- L73 _private member_ `FStateMachineTransitionCompileResult Result;` — Result of the compilation

#### struct `UE::SceneState::Editor::FStateMachineTransitionCompiler::FCompileParams`  
`struct FCompileParams`  
_L44-54_
- L47 _public member_ `IStateMachineCompilerContext& Context;` — Compiler context interface for compilation required outside the scope of this compiler
- L49 _public member_ `const USceneStateMachineNode* Node;` — Node containing the exit transitions to compile
- L51 _public member_ `const TMap<FObjectKey, uint16>& StateNodeIndexMap;` — Used to look up the index, relative in state machine space, for a given state node
- L53 _public member_ `const TMap<FObjectKey, uint16>& ConduitNodeIndexMap;` — Used to look up the index, relative in state machine space, for a given conduit node

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SceneState` (scope `UE`)
- L17 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L23 _namespace_ `namespace Graph` (scope `UE::SceneState`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace SceneState` (scope `UE`)
- L29 _namespace_ `namespace Editor` (scope `UE::SceneState`)
