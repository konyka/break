# Plugins / ScribbleEditor

- module root: `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor`
- headers: 7; symbols: 151
- symbol kinds: class=8, delegate=1, function=20, macro=3, member=31, prototype=88
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EditorFramework, EditorStyle, EditorWidgets, Engine, InputCore, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: AppFramework, GraphEditor, MainFrame, Scribble

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/SScribbleGraph.h` (Public)


#### class `SScribbleGraphPanel`  
`class SScribbleGraphPanel : public SGraphPanel, public FEditorUndoClient`  
_L15-100_
- inherits: `SGraphPanel,FEditorUndoClient`
- L19 _public function_ `SLATE_BEGIN_ARGS(SScribbleGraphPanel) : _ScribbleEnabled(true) , _ScribbleNodeType(EScribbleNodeType::Invalid) , _ScribbleColor() , _ScribbleThickness() , _ScribblePrecision() , _ShouldDrawBackground(false) , _ShouldDrawSurroundingShadow(false) , _AllowNavigation(true)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FScribbleGraphData>, GraphData) SLATE_ATTRIBUTE(bool, ScribbleEnabled) SLATE_ATTRIBUTE(EScribbleNodeType::Type, ScribbleNodeType) SLATE_EVENT(FScribbleSetNodeType, OnSetNodeType) SLATE_ATTRIBUTE(FLinearColor, ScribbleColor) SLATE_ATTRIBUTE(float, ScribbleThickness) SLATE_ATTRIBUTE(float, ScribblePrecision) SLATE_ATTRIBUTE(bool, ShouldDrawBackground) SLATE_ATTRIBUTE(bool, ShouldDrawSurroundingShadow) SLATE_ARGUMENT(bool, AllowNavigation) SLATE_ARGUMENT(TWeakPtr<SGraphPanel>, PanelToSync) SLATE_END_ARGS() SScribbleGraphPanel();`
- L47 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L49 _public prototype_ `bool IsScribbleEnabled() const;`
- L50 _public prototype_ `bool HasActiveNodeType() const;`
- L51 _public prototype_ `void ActivateSelectionMode();`
- L52 _public prototype_ `EScribbleNodeType::Type GetActiveNodeType() const;`
- L53 _public prototype_ `void SetActiveNodeType(EScribbleNodeType::Type InNodeType);`
- L55 _public prototype_ `UScribbleEdGraph* GetScribbleEdGraph();`
- L56 _public prototype_ `const UScribbleEdGraph* GetScribbleEdGraph() const;`
- L57 _public prototype_ `FScribbleGraphData* GetScribbleGraph();`
- L58 _public prototype_ `const FScribbleGraphData* GetScribbleGraph() const;`
- L60 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L61 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L62 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L63 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L64 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L65 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L66 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L67 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L70 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L71 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L75 _private prototype_ `void BindCommands();`
- L76 _private prototype_ `void UpdateScribbleVisibility();`
- L77 _private prototype_ `void HandleSelectionChanged(const FGraphPanelSelectionSet& SelectionSet);`
- L79 _private prototype_ `bool UpdateNewNode( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L80 _private prototype_ `bool CancelNewNode();`
- L81 _private prototype_ `bool CommitNewNode();`
- L83 _private member_ `UScribbleEdGraph* ScribbleGraphObj;`
- L84 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L86 _private member_ `TAttribute<bool> ScribbleEnabled;`
- L87 _private member_ `TAttribute<EScribbleNodeType::Type> ScribbleNodeType;`
- L88 _private member_ `TAttribute<float> ScribbleThickness;`
- L89 _private member_ `TAttribute<float> ScribblePrecision;`
- L90 _private member_ `TAttribute<FLinearColor> ScribbleColor;`
- L91 _private member_ `FScribbleSetNodeType OnSetNodeType;`
- L93 _private member_ `TOptional<bool> bIsScribbleDragging;`
- L94 _private member_ `TSharedPtr<FScribbleNode> NewNode;`
- L95 _private member_ `TSharedPtr<FScopedTransaction> Transaction;`
- L96 _private member_ `bool bAllowNavigation;`
- L97 _private member_ `TWeakPtr<SGraphPanel> WeakPanelToSync;`
- L99 _private member_ `const TUniquePtr<FSlateRoundedBoxBrush> RoundedFrameBrush;`

#### class `SScribbleGraph`  
`class SScribbleGraph : public SCompoundWidget`  
_L102-143_
- inherits: `SCompoundWidget`
- L106 _public function_ `SLATE_BEGIN_ARGS(SScribbleGraph) : _ShouldDrawBackground(true) , _ShouldDrawSurroundingShadow(false) , _AllowNavigation(true) , _ToolbarHAlignment(HAlign_Left) , _ToolbarVAlignment(VAlign_Top) , _ToolbarPadding(20)`
- L114 _public function_ `SLATE_ARGUMENT(TSharedPtr<FScribbleGraphData>, GraphData) SLATE_ATTRIBUTE(bool, ShouldDrawBackground) SLATE_ATTRIBUTE(bool, ShouldDrawSurroundingShadow) SLATE_ARGUMENT(bool, AllowNavigation) SLATE_ARGUMENT(EHorizontalAlignment, ToolbarHAlignment) SLATE_ARGUMENT(EVerticalAlignment, ToolbarVAlignment) SLATE_ARGUMENT(FMargin, ToolbarPadding) SLATE_ARGUMENT(TWeakPtr<SGraphPanel>, PanelToSync) SLATE_END_ARGS() SScribbleGraph() : bIsScribbleEnabled(true)`
- L132 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs this widget with InArgs
- L136 _protected prototype_ `FLinearColor GetScribbleColor() const;`
- L137 _protected prototype_ `float GetScribbleThickness() const;`
- L138 _protected prototype_ `float GetScribblePrecision() const;`
- L139 _protected function_ `bool IsScribbleEnabled() const`
- L141 _protected member_ `TSharedPtr<SScribbleGraphPanel> GraphPanel;`
- L142 _protected member_ `bool bIsScribbleEnabled;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCRIBBLEEDITOR_API`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FScribbleSetNodeType, EScribbleNodeType::Type);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FScribbleSetNodeType, EScribbleNodeType::Type);`

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/SScribbleGraphNode.h` (Public)


#### class `SScribbleGraphNode`  
`class SScribbleGraphNode : public SGraphNode`  
_L19-61_
- inherits: `SGraphNode`
- L22 _public function_ `SLATE_BEGIN_ARGS(SScribbleGraphNode)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UScribbleEdGraphNode* InNode);`
- L32 _protected function_ `virtual void CreatePinWidgets() override` — SGraphNode interface
- L33 _protected function_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override`
- L35 _protected function_ `virtual FText GetNodeTooltip() const override`
- L36 _protected function_ `virtual FSlateColor GetNodeBodyColor() const override`
- L37 _protected function_ `virtual const FSlateBrush* GetNodeBodyBrush() const override`
- L38 _protected prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L39 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L40 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L41 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L42 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L43 _protected prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;`
- L44 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L45 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L46 _protected function_ `virtual FVector2f GetDesiredSizeForMarquee2f() const override`
- L47 _protected prototype_ `virtual bool CanBeSelected(const FVector2f& MousePositionInNode) const override;`
- L51 _protected prototype_ `const UScribbleEdGraphNode* GetScribbleEdGraphNode() const;`
- L52 _protected prototype_ `UScribbleEdGraphNode* GetScribbleEdGraphNode();`
- L53 _protected prototype_ `const FScribbleNode* GetScribbleNode() const;`
- L54 _protected prototype_ `FScribbleNode* GetScribbleNode();`
- L55 _protected prototype_ `const FScribbleGraphData* GetScribbleGraphData() const;`
- L56 _protected prototype_ `FScribbleGraphData* GetScribbleGraphData();`
- L58 _protected prototype_ `FVector2f GetSizeFromScribbleNode() const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCRIBBLEEDITOR_API`

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/ScribbleEdGraph.h` (Public)


#### class `UScribbleEdGraph`  
`class UScribbleEdGraph : public UEdGraph`  
_L18-96_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- desc: The UEdGraph implementation of a scribble graph. This is used for the ed graph side of things only and corresponds with the FScribbleGraphData as well as the SScribbleGraph.
- L23 _public prototype_ `void Initialize(const TSharedPtr<FScribbleGraphData>& InScribbleGraphData);`
- L25 _public prototype_ `FScribbleGraphData* GetGraphData();`
- L26 _public prototype_ `const FScribbleGraphData* GetGraphData() const;`
- L29 _public prototype_ `void RebuildGraph();` — Rebuilds graph from selection
- L32 _public prototype_ `void SelectNodes(const TArray<FGuid>& InNodeIds);` — Select the nodes
- L35 _public function_ `const TArray<TObjectPtr<UEdGraphNode>>& GetNodes() const` — Get the scribble graph nodes we are displaying
- L38 _public prototype_ `const UScribbleEdGraphNode* FindNode(const FGuid& InNodeId) const;` — Returns the node given a Node Id
- L39 _public prototype_ `UScribbleEdGraphNode* FindNode(const FGuid& InNodeId);`
- L41 _public prototype_ `FGuid AddScribbleNode(const TSharedPtr<FScribbleNode>& InNode);`
- L42 _public prototype_ `bool RemoveScribbleNode(const TSharedPtr<FScribbleNode>& InNode);`
- L43 _public prototype_ `bool RemoveScribbleNode(const FGuid& InGuid);`
- L46 _public prototype_ `bool Contains(const FGuid& InNodeId) const;` — Returns true if the node given a Node Id exists
- L48 _public prototype_ `void SelectAllNodes();`
- L49 _public prototype_ `void ClearSelection();`
- L50 _public prototype_ `void RemoveAllNodes();`
- L51 _public prototype_ `TArray<FGuid> GetAllNodeIds() const;`
- L52 _public function_ `const TArray<FGuid>& GetSelectedNodeIds() const`
- L53 _public prototype_ `void RemoveSelectedNodes();`
- L54 _public prototype_ `bool IsNodeSelected(const FGuid& InNodeId) const;`
- L55 _public prototype_ `bool IsNodeSelected(const TSharedPtr<FScribbleNode>& InNode) const;`
- L56 _public prototype_ `bool IsNodeSelected(const UScribbleEdGraphNode* InNode) const;`
- L58 _public prototype_ `void GroupSelectedNodes();`
- L59 _public prototype_ `void UngroupSelectedNodes();`
- L61 _public prototype_ `virtual void NotifyGraphChanged() override;`
- L64 _private prototype_ `FBox2D GetAllNodesBounds() const;`
- L65 _private prototype_ `FBox2D GetSelectedNodesBounds() const;`
- L68 _private function_ `template<typename RangeType> FBox2D GetNodesBounds(const RangeType& InNodeIds) const`
- L85 _private member_ `TArray<FGuid> SelectedNodes;`
- L86 _private member_ `bool bIsSelecting;`
- L88 _private member_ `TMap<FGuid, UScribbleEdGraphNode*> NodeIdLookup;`
- L90 _private member_ `TSharedPtr<FScribbleGraphData> GraphData;`
- L91 _private member_ `TAttribute<bool> IsAnchorEnabled;`

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/ScribbleEdGraphCommands.h` (Public)


#### class `FScribbleEdGraphCommands`  
`class FScribbleEdGraphCommands : public TCommands<FScribbleEdGraphCommands>`  
_L9-46_
- inherits: `TCommands<FScribbleEdGraphCommands>`
- L12 _public function_ `FScribbleEdGraphCommands() : TCommands<FScribbleEdGraphCommands> ( "ScribbleEdGraph", NSLOCTEXT("Contexts", "ScribbleEdGraph", "Scribble"), NAME_None,`
- L22 _public member_ `TSharedPtr<FUICommandInfo> FrameSelection;` — frames the selection in the graph
- L25 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelection;` — delete the selected nodes in the graph
- L28 _public member_ `TSharedPtr<FUICommandInfo> SelectAll;` — select all scribble elements
- L31 _public member_ `TSharedPtr<FUICommandInfo> GroupSelection;` — groups the selection in the graph
- L34 _public member_ `TSharedPtr<FUICommandInfo> UngroupSelection;` — ungroups the selection in the graph
- L37 _public member_ `TSharedPtr<FUICommandInfo> SelectionTool;` — enables / disables the select tool
- L40 _public member_ `TSharedPtr<FUICommandInfo> BrushTool;` — enables / disables the brush tool
- L45 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/ScribbleEdGraphNode.h` (Public)


#### class `UScribbleEdGraphNode`  
`class UScribbleEdGraphNode : public UEdGraphNode`  
_L19-50_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- desc: The UEdGraphNode implementation of a scribble graph node. This is used for the ed graph side of things only and corresponds with the FScribbleNode as well as the SScribbleGraphNode.
- L23 _private prototype_ `virtual ~UScribbleEdGraphNode();`
- L25 _private prototype_ `class UScribbleEdGraph* GetScribbleEdGraph() const;`
- L27 _private prototype_ `void Initialize(const TSharedPtr<FScribbleNode>& InScribbleNode);`
- L30 _private function_ `virtual void AllocateDefaultPins() override` — UEdGraphNode implementation
- L31 _private function_ `virtual bool ShowPaletteIconOnNode() const override`
- L32 _private function_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override`
- L34 _private prototype_ `const FScribbleNode* GetScribbleNode() const;`
- L35 _private prototype_ `FScribbleNode* GetScribbleNode();`
- L36 _private prototype_ `TSharedPtr<FScribbleNode> GetScribbleNodePtr() const;`
- L37 _private prototype_ `const FScribbleGraphData* GetScribbleGraphData() const;`
- L38 _private prototype_ `FScribbleGraphData* GetScribbleGraphData();`
- L40 _private prototype_ `const FGuid& GetNodeId() const;`
- L44 _protected member_ `TWeakPtr<FScribbleNode> WeakScribbleNode;`
- L45 _protected member_ `FDelegateHandle PositionChangedDelegateHandle;`
- L46 _protected member_ `FDelegateHandle SizeChangedDelegateHandle;`

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/ScribbleEdGraphPanelNodeFactory.h` (Public)


#### class `FScribbleEdGraphPanelNodeFactory`  
`class FScribbleEdGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L12-15_
- inherits: `FGraphPanelNodeFactory`
- L14 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCRIBBLEEDITOR_API`

### `Plugins/Experimental/Animation/Scribble/Source/ScribbleEditor/Public/ScribbleEdGraphSchema.h` (Public)


#### class `UScribbleEdGraphSchema`  
`class UScribbleEdGraphSchema : public UEdGraphSchema`  
_L14-28_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L20 _public function_ `virtual FName GetParentContextMenuName() const override` — UEdGraphSchema interface
- L21 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L22 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L23 _public prototype_ `virtual void SetNodePosition(UEdGraphNode* InNode, const FVector2f& InPosition) const override;`
- L24 _public prototype_ `virtual void SetNodeSize(UEdGraphNode* InNode, const FVector2f& InSize) const;`
- L27 _public prototype_ `virtual UScribbleEdGraphNode* CreateGraphNode(UScribbleEdGraph* InGraph, const FGuid& InNodeId) const;`
