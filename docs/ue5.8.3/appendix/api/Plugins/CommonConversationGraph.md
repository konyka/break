# Plugins / CommonConversationGraph

- module root: `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph`
- headers: 15; symbols: 220
- symbol kinds: class=14, enum=2, enumerator=5, function=14, macro=10, member=25, namespace=8, prototype=110, struct=4, variable=28
- PrivateDependencyModuleNames: AIGraph, AIModule, BlueprintGraph, CommonConversationRuntime, CoreUObject, Engine, GameplayTags, GraphEditor, KismetWidgets, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Private/SConversationGraphNode.h` (Private)


#### enum `ESubNodeWidgetLocation`  
`enum class ESubNodeWidgetLocation : uint8`  
_L20-24_
- L22 _public enumerator_ `Above`
- L23 _public enumerator_ `Below`

#### struct `FSubNodeWidgetStuff`  
`struct FSubNodeWidgetStuff`  
_L26-31_
- L28 _public member_ `TSharedPtr<SVerticalBox> ChildNodeBox;`
- L30 _public member_ `TArray< TSharedPtr<SGraphNode> > ChildNodeWidgets;`

#### class `SConversationGraphNode`  
`class SConversationGraphNode : public SGraphNodeAI, public FNotifyHook`  
_L35-137_
- inherits: `SGraphNodeAI,FNotifyHook`
- L38 _public function_ `SLATE_BEGIN_ARGS(SConversationGraphNode)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UConversationGraphNode* InNode);`
- L44 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L45 _public prototype_ `virtual void CreatePinWidgets() override;`
- L46 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L47 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L48 _public prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L49 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L50 _public prototype_ `virtual TSharedRef<SGraphNode> GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L51 _public prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L52 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L56 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;` — handle double click
- L65 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — Ticks this widget.  Override in derived classes, but always call the parent implementation. @param  AllottedGeometry The space allotted for this widget @param  InCurrentTime  Current absolute real time @param  InDeltaTime  Real time passed since last tick
- L68 _public prototype_ `void AddSubNodeWidget(TSharedPtr<SGraphNode> NewSubNodeWidget, ESubNodeWidgetLocation Location);` — adds a sub node widget inside current node
- L70 _public function_ `FVector2D GetCachedPosition() const`
- L73 _protected member_ `uint32 bSuppressDebuggerColor : 1;`
- L74 _protected member_ `uint32 bSuppressDebuggerTriggers : 1;`
- L77 _protected member_ `float DebuggerStateDuration;` — time spent in current state
- L80 _protected member_ `int32 DebuggerStateCounter;` — currently displayed state
- L83 _protected member_ `FLinearColor FlashColor;` — debugger colors
- L84 _protected member_ `float FlashAlpha;`
- L87 _protected member_ `TArray<FNodeBounds> TriggerOffsets;` — height offsets for search triggers
- L90 _protected member_ `FVector2D CachedPosition;` — cached draw position
- L92 _protected member_ `TMap<ESubNodeWidgetLocation, FSubNodeWidgetStuff> ChildNodeStuff;`
- L94 _protected member_ `TSharedPtr<SHorizontalBox> OutputPinBox;`
- L97 _protected member_ `TSharedPtr<SWidget> IndexOverlay;` — The widget we use to display the index of the node
- L100 _protected member_ `TSharedPtr<SBorder> NodeBody;` — The node body widget, cached here so we can determine its size when we want ot position our overlays
- L102 _protected prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L103 _protected prototype_ `FSlateColor GetBackgroundColor() const;`
- L105 _protected prototype_ `virtual const FSlateBrush* GetNameIcon() const override;`
- L106 _protected prototype_ `virtual EVisibility GetBlueprintIconVisibility() const;`
- L109 _protected prototype_ `EVisibility GetIndexVisibility() const;` — Get the visibility of the index overlay
- L112 _protected prototype_ `FText GetIndexText() const;` — Get the text to display in the index overlay
- L115 _protected prototype_ `FText GetIndexTooltipText() const;` — Get the tooltip for the index overlay
- L118 _protected prototype_ `FSlateColor GetIndexColor(bool bHovered) const;` — Get the color to display for the index overlay. This changes on hover state of sibling nodes
- L121 _protected prototype_ `void OnIndexHoverStateChanged(bool bHovered);` — Handle hover state changing for the index widget - we use this to highlight sibling nodes
- L123 _protected prototype_ `FText GetPinTooltip(UEdGraphPin* GraphPinObj) const;`
- L125 _protected prototype_ `bool IsNodeReachable() const;`
- L127 _protected prototype_ `EVisibility GetTaskRequirementsVisibility() const;`
- L128 _protected prototype_ `EVisibility GetTaskGeneratesChoicesVisibility() const;`
- L130 _protected prototype_ `void PropertyRowsRefreshed();`
- L132 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L134 _protected member_ `TSharedPtr<class IPropertyRowGenerator> PropertyRowGenerator;`
- L136 _protected member_ `class SVerticalBox::FSlot* PropertyDetailsSlot;`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/CommonConversationGraphModule.h` (Public)


#### class `FCommonConversationGraphModule`  
`class FCommonConversationGraphModule : public IModuleInterface`  
_L14-25_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void HandlePreSavePackage(UPackage* Package, FObjectPreSaveContext ObjectSaveContext);`
- L24 _private prototype_ `void HandleBeginPIE(bool bIsSimulating);`

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonConversationGraph, Display, All);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationCompiler.h` (Public)


#### class `FConversationCompiler`  
`class FConversationCompiler`  
_L18-55_
- L21 _public prototype_ `static int32 GetNumGraphs(UConversationDatabase* ConversationAsset);`
- L22 _public prototype_ `static UConversationGraph* GetGraphFromBank(UConversationDatabase* ConversationAsset, int32 Index);`
- L23 _public prototype_ `static void RebuildBank(UConversationDatabase* ConversationAsset);`
- L24 _public prototype_ `static UConversationGraph* AddNewGraph(UConversationDatabase* ConversationAsset, const FString& DesiredName);`
- L26 _public prototype_ `static int32 GetCompilerVersion();`
- L28 _public prototype_ `static void ScanAndRecompileOutOfDateCompiledConversations();`
- L31 _private function_ `FConversationCompiler()`
- L34 _private prototype_ `static UConversationGraph* CreateNewGraph(UConversationDatabase* ConversationAsset, FName GraphName);` — Creates a new graph but does not add it
- L37 _private prototype_ `static void ForeachConnectedOutgoingConversationNode(UEdGraphPin* Pin, TFunctionRef<void(UConversationGraphNode*)> Predicate);` — Skips over knots.
- L54 _private prototype_ `static void ForeachConnectedOutgoingConversationNodeSorted(UEdGraphPin* Pin, TFunctionRef<void(UConversationGraphNode*)> Predicate);` — Functions similarly to ForeachConnectedOutgoingConversationNode but visits nodes based on their left to right order Knots are visited in depth-first order such that a graph like the following results in the order A B C D * /|\ / | \ *  C  D / \ /   \ /     \ /       \ A         B

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationEditorColors.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ConversationEditorColors`
- L9 _namespace_ `namespace NodeBody` (scope `ConversationEditorColors`)
- L11 _variable_ `const FLinearColor Task(0.24f, 0.055f, 0.715f);` (scope `ConversationEditorColors::NodeBody`)
- L13 _variable_ `const FLinearColor RequirementColor(0.0f, 0.07f, 0.4f);` (scope `ConversationEditorColors::NodeBody`)
- L14 _variable_ `const FLinearColor SideEffectColor(0.0f, 0.27f, 0.4f);` (scope `ConversationEditorColors::NodeBody`)
- L15 _variable_ `const FLinearColor ChoiceColor(0.35f, 0.23f, 0.15f);` (scope `ConversationEditorColors::NodeBody`)
- L17 _variable_ `const FLinearColor Default(0.15f, 0.15f, 0.15f);` (scope `ConversationEditorColors::NodeBody`)
- L18 _variable_ `const FLinearColor EntryPoint(0.5f, 0.5f, 0.5f, 0.1f);` (scope `ConversationEditorColors::NodeBody`)
- L19 _variable_ `const FLinearColor Error(1.0f, 0.0f, 0.0f);` (scope `ConversationEditorColors::NodeBody`)
- L22 _namespace_ `namespace NodeBorder` (scope `ConversationEditorColors`)
- L24 _variable_ `const FLinearColor Inactive(0.08f, 0.08f, 0.08f);` (scope `ConversationEditorColors::NodeBorder`)
- L25 _variable_ `const FLinearColor Root(0.2f, 0.2f, 0.2f, 0.2f);` (scope `ConversationEditorColors::NodeBorder`)
- L26 _variable_ `const FLinearColor Selected(1.00f, 0.58f, 0.08f);` (scope `ConversationEditorColors::NodeBorder`)
- L27 _variable_ `const FLinearColor ActiveDebugging(1.0f, 1.0f, 0.0f);` (scope `ConversationEditorColors::NodeBorder`)
- L28 _variable_ `const FLinearColor InactiveDebugging(0.4f, 0.4f, 0.0f);` (scope `ConversationEditorColors::NodeBorder`)
- L29 _variable_ `const FLinearColor HighlightAbortRange0(0.0f, 0.22f, 0.4f);` (scope `ConversationEditorColors::NodeBorder`)
- L30 _variable_ `const FLinearColor HighlightAbortRange1(0.0f, 0.4f, 0.22f);` (scope `ConversationEditorColors::NodeBorder`)
- L31 _variable_ `const FLinearColor Disconnected(0.f, 0.f, 0.f);` (scope `ConversationEditorColors::NodeBorder`)
- L32 _variable_ `const FLinearColor BrokenWithParent(1.f, 0.f, 1.f);` (scope `ConversationEditorColors::NodeBorder`)
- L33 _variable_ `const FLinearColor QuickFind(0.f, 0.8f, 0.f);` (scope `ConversationEditorColors::NodeBorder`)
- L36 _namespace_ `namespace Pin` (scope `ConversationEditorColors`)
- L38 _variable_ `const FLinearColor Diff(0.9f, 0.2f, 0.15f);` (scope `ConversationEditorColors::Pin`)
- L39 _variable_ `const FLinearColor Hover(1.0f, 0.7f, 0.0f);` (scope `ConversationEditorColors::Pin`)
- L40 _variable_ `const FLinearColor Default(0.02f, 0.02f, 0.02f);` (scope `ConversationEditorColors::Pin`)
- L41 _variable_ `const FLinearColor TaskOnly(0.13f, 0.03f, 0.4f);` (scope `ConversationEditorColors::Pin`)
- L42 _variable_ `const FLinearColor CompositeOnly(0.02f, 0.02f, 0.02f);` (scope `ConversationEditorColors::Pin`)
- L43 _variable_ `const FLinearColor SingleNode(0.02f, 0.02f, 0.02f);` (scope `ConversationEditorColors::Pin`)
- L46 _namespace_ `namespace Connection` (scope `ConversationEditorColors`)
- L48 _variable_ `const FLinearColor Default(1.0f, 1.0f, 1.0f);` (scope `ConversationEditorColors::Connection`)
- L51 _namespace_ `namespace Debugger` (scope `ConversationEditorColors`)
- L53 _variable_ `const FLinearColor TaskFlash(1.0f, 1.0f, 0.0f);` (scope `ConversationEditorColors::Debugger`)
- L55 _variable_ `const FLinearColor DescHeader(0.3f, 0.8f, 0.4f);` (scope `ConversationEditorColors::Debugger`)
- L56 _variable_ `const FLinearColor DescKeys(0.3f, 0.4f, 0.8f);` (scope `ConversationEditorColors::Debugger`)
- L59 _namespace_ `namespace Action` (scope `ConversationEditorColors`)
- L61 _variable_ `const FLinearColor DragMarker(1.0f, 1.0f, 0.2f);` (scope `ConversationEditorColors::Action`)

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraph.h` (Public)


#### class `UConversationGraph`  
`class UConversationGraph : public UAIGraph`  
_L13-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraph`
- L19 _public prototype_ `virtual void UpdateAsset(int32 UpdateFlags) override;` — UAIGraph interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphConnectionDrawingPolicy.h` (Public)


#### class `FConversationGraphConnectionDrawingPolicy`  
`class FConversationGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L10-30_
- inherits: `FConnectionDrawingPolicy`
- L13 _protected member_ `UEdGraph* GraphObj;`
- L14 _protected member_ `TMap<UEdGraphNode*, int32> NodeWidgetMap;`
- L17 _public prototype_ `FConversationGraphConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L20 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L21 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L22 _public prototype_ `virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;`
- L23 _public prototype_ `virtual void DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint, const FConnectionParams& Params) override;`
- L24 _public prototype_ `virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2f& StartPoint, const FVector2f& EndPoint, UEdGraphPin* Pin) override;`
- L25 _public prototype_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override;`
- L29 _protected prototype_ `void Internal_DrawLineWithArrow(const FVector2f& StartAnchorPoint, const FVector2f& EndAnchorPoint, const FConnectionParams& Params);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode.h` (Public)


#### class `UConversationGraphNode`  
`class UConversationGraphNode : public UAIGraphNode`  
_L15-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraphNode`
- L22 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;`
- L23 _public prototype_ `virtual void FindDiffs(UEdGraphNode* OtherNode, FDiffResults& Results) override;`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L26 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L27 _public prototype_ `virtual bool CanJumpToDefinition() const override;`
- L28 _public prototype_ `virtual void JumpToDefinition() const override;`
- L29 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L32 _public prototype_ `virtual FText GetDescription() const override;`
- L35 _public function_ `virtual bool CanPlaceBreakpoints() const` — check if node can accept breakpoints
- L38 _public prototype_ `virtual FName GetNameIcon() const;` — gets icon resource name for title bar
- L40 _public prototype_ `bool IsOutBoundConnectionAllowed(const UConversationGraphNode* OtherNode, FText& OutErrorMessage) const;`
- L41 _public prototype_ `bool IsOutBoundConnectionAllowed(const UConversationGraphNode_Knot* KnotNode, FText& OutErrorMessage) const;`
- L44 _public function_ `template<class T> T* GetRuntimeNode() const`
- L50 _protected prototype_ `void RequestRebuildConversation();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`
- L10 _namespace_ `namespace ENodeTitleType`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_Choice.h` (Public)


#### class `UConversationGraphNode_Choice`  
`class UConversationGraphNode_Choice : public UConversationGraphNode`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationGraphNode`
- L15 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L16 _private prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L17 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_EntryPoint.h` (Public)


#### class `UConversationGraphNode_EntryPoint`  
`class UConversationGraphNode_EntryPoint : public UConversationGraphNode`  
_L12-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationGraphNode`
- desc: Root node of this conversation block
- L16 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L17 _private prototype_ `virtual FName GetNameIcon() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_Knot.h` (Public)


#### class `UConversationGraphNode_Knot`  
`class UConversationGraphNode_Knot : public UEdGraphNode`  
_L12-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphNode`
- L18 _public prototype_ `virtual void AllocateDefaultPins() override;` — UEdGraphNode interface
- L19 _public prototype_ `virtual FText GetTooltipText() const override;`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L21 _public prototype_ `virtual bool ShouldOverridePinNames() const override;`
- L22 _public prototype_ `virtual FText GetPinNameOverride(const UEdGraphPin& Pin) const override;`
- L23 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L24 _public prototype_ `virtual TSharedPtr<class INameValidatorInterface> MakeNameValidator() const override;`
- L25 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L26 _public function_ `virtual bool IsCompilerRelevant() const override`
- L27 _public prototype_ `virtual UEdGraphPin* GetPassThroughPin(const UEdGraphPin* FromPin) const override;`
- L28 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L29 _public function_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override`
- L32 _public function_ `UEdGraphPin* GetInputPin() const`
- L37 _public function_ `UEdGraphPin* GetOutputPin() const`
- L42 _public prototype_ `void GatherAllInBoundGraphNodes(TArray<UConversationGraphNode*>& OutGraphNodes) const;`
- L43 _public prototype_ `void GatherAllOutBoundGraphNodes(TArray<UConversationGraphNode*>& OutGraphNodes) const;`
- L45 _public prototype_ `bool IsOutBoundConnectionAllowed(const UConversationGraphNode* OtherNode, FText& OutErrorMessage) const;`
- L46 _public prototype_ `bool IsOutBoundConnectionAllowed(const UConversationGraphNode_Knot* OtherKnotNode, FText& OutErrorMessage) const;`
- L49 _private prototype_ `void GatherAllInBoundGraphNodes_Internal(TArray<UConversationGraphNode*>& OutGraphNodes, TArray<const UConversationGraphNode_Knot*>& VisitedKnots) const;`
- L50 _private prototype_ `void GatherAllOutBoundGraphNodes_Internal(TArray<UConversationGraphNode*>& OutGraphNodes, TArray<const UConversationGraphNode_Knot*>& VisitedKnots) const;`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_Requirement.h` (Public)


#### class `UConversationGraphNode_Requirement`  
`class UConversationGraphNode_Requirement : public UConversationGraphNode`  
_L11-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationGraphNode`
- L15 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L16 _private prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_SideEffect.h` (Public)


#### class `UConversationGraphNode_SideEffect`  
`class UConversationGraphNode_SideEffect : public UConversationGraphNode`  
_L11-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationGraphNode`
- L15 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L16 _private prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphNode_Task.h` (Public)


#### class `UConversationGraphNode_Task`  
`class UConversationGraphNode_Task : public UConversationGraphNode`  
_L19-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationGraphNode`
- L23 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L24 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _private prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L28 _private prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;` — Gets a list of actions that can be done to this particular node
- L29 _private prototype_ `virtual void ApplyAddRequirementMenu(FMenuBuilder& MenuBuilder, UEdGraph* Graph);`
- L31 _private function_ `virtual bool CanPlaceBreakpoints() const override`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphSchema.h` (Public)


#### struct `FConversationGraphSchemaAction_AutoArrange`  
`struct FConversationGraphSchemaAction_AutoArrange : public FEdGraphSchemaAction`  
_L25-40_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to auto arrange the graph
- L29 _public function_ `FConversationGraphSchemaAction_AutoArrange() : FEdGraphSchemaAction()`
- L32 _public function_ `FConversationGraphSchemaAction_AutoArrange(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) : FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)`
- L38 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### class `UConversationGraphSchema`  
`class UConversationGraphSchema : public UAIGraphSchema`  
_L46-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAIGraphSchema`
- L52 _public prototype_ `virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;`
- L53 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L54 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L55 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L56 _public prototype_ `virtual const FPinConnectionResponse CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const override;`
- L57 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L58 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L59 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L60 _public prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L61 _public prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L62 _public prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L65 _public prototype_ `virtual void GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, int32 SubNodeFlags) const override;`
- L66 _public prototype_ `bool HasSubNodeClasses(int32 SubNodeFlags) const;`
- L67 _public prototype_ `virtual void GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const override;`
- L70 _protected prototype_ `void AddConversationNodeOptions(const FString& CategoryName, FGraphContextMenuBuilder& ContextMenuBuilder, TSubclassOf<UConversationNode> RuntimeNodeType, TSubclassOf<UConversationGraphNode> EditorNodeType) const;`
- L74 _private member_ `static int32 CurrentCacheRefreshID;` — ID for checking dirty status of node titles against, increases whenever

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationGraph/Public/ConversationGraphTypes.h` (Public)


#### struct `FCompareNodeXLocation`  
`struct FCompareNodeXLocation`  
_L10-24_
- L12 _public function_ `inline bool operator()(const UEdGraphPin& A, const UEdGraphPin& B) const`

#### enum `EConversationGraphSubNodeType`  
`enum class EConversationGraphSubNodeType : uint8`  
_L26-31_
- L28 _public enumerator_ `Requirement`
- L29 _public enumerator_ `SideEffect`
- L30 _public enumerator_ `Choice`

#### struct `FNodeBounds`  
`struct FNodeBounds`  
_L33-43_
- L35 _public member_ `FVector2D Position;`
- L36 _public member_ `FVector2D Size;`
- L38 _public function_ `FNodeBounds(FVector2D InPos, FVector2D InSize)`

#### class `UConversationGraphTypes`  
`class UConversationGraphTypes : public UObject`  
_L46-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L50 _private member_ `static const FName PinCategory_MultipleNodes;`
- L51 _private member_ `static const FName PinCategory_SingleComposite;`
- L52 _private member_ `static const FName PinCategory_SingleTask;`
- L53 _private member_ `static const FName PinCategory_SingleNode;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONGRAPH_API`
