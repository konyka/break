# Editor / GraphEditor

- module root: `Source/Editor/GraphEditor`
- headers: 91; symbols: 2647
- symbol kinds: class=88, delegate=33, enum=17, enumerator=70, function=437, macro=52, member=807, namespace=2, prototype=1065, struct=62, typedef=14
- DynamicallyLoadedModuleNames: ClassViewer, ContentBrowser, StructViewer
- PrivateDependencyModuleNames: AppFramework, AssetRegistry, BlueprintGraph, Core, CoreUObject, Documentation, EditorFramework, EditorWidgets, Engine, InputCore, Kismet, KismetCompiler, KismetWidgets, Persona, PropertyEditor, RHI, RenderCore, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicIncludePathModuleNames: ClassViewer, MaterialEditor, StructViewer

### `Source/Editor/GraphEditor/Private/DragConnection.h` (Private)


#### class `FDragConnection`  
`class FDragConnection : public FGraphEditorDragDropAction`  
_L20-67_
- inherits: `FGraphEditorDragDropAction`
- L31 _public typedef_ `typedef TArray<FGraphPinHandle> FDraggedPinTable;`
- L32 _public prototype_ `static TSharedRef<FDragConnection> New(const TSharedRef<SGraphPanel>& InGraphPanel, const FDraggedPinTable& InStartingPins);`
- L35 _public prototype_ `virtual void OnDrop( bool bDropWasHandled, const FPointerEvent& MouseEvent ) override;` — FDragDropOperation interface
- L39 _public prototype_ `virtual void HoverTargetChanged() override;` — FGraphEditorDragDropAction interface
- L40 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L41 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L42 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L43 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L49 _public prototype_ `virtual void ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins);` — Function to check validity of graph pins in the StartPins list. This check helps to prevent processing graph pins which are outdated.
- L52 _protected typedef_ `typedef FGraphEditorDragDropAction Super;`
- L55 _protected prototype_ `FDragConnection(const TSharedRef<SGraphPanel>& GraphPanel, const FDraggedPinTable& DraggedPins);` — Constructor: Make sure to call Construct() after factorying one of these
- L58 _protected member_ `TSharedPtr<SGraphPanel> GraphPanel;`
- L59 _protected member_ `FDraggedPinTable DraggingPins;`
- L60 _protected member_ `EDragMode DragMode = EDragMode::CreateConnection;`
- L63 _protected member_ `FDeprecateSlateVector2D DecoratorAdjust;` — Offset information for the decorator widget
- L65 _protected member_ `FGraphPinHandle SourcePinHandle;`
- L66 _protected member_ `FGraphPinHandle TargetPinHandle;`

#### enum `FDragConnection::EDragMode`  
`enum EDragMode : uint8`  
_L25-29_
- L27 _public enumerator_ `CreateConnection = 0`
- L28 _public enumerator_ `RelinkConnection`

### `Source/Editor/GraphEditor/Private/DragNode.h` (Private)


#### class `FDragNode`  
`class FDragNode : public FGraphEditorDragDropAction`  
_L21-60_
- inherits: `FGraphEditorDragDropAction`
- L24 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDragNode, FGraphEditorDragDropAction) static TSharedRef<FDragNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TSharedRef<SGraphNode>& InDraggedNode);`
- L28 _public prototype_ `static TSharedRef<FDragNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphNode> >& InDraggedNodes);`
- L31 _public prototype_ `virtual void HoverTargetChanged() override;` — FGraphEditorDragDropAction interface
- L32 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L33 _public prototype_ `virtual FReply DroppedOnPanel( const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L35 _public prototype_ `virtual void OnDragged (const class FDragDropEvent& DragDropEvent ) override;` — virtual void OnDragBegin( const TSharedRef<class SGraphPin>& InPin) override;
- L38 _public prototype_ `const TArray< TSharedRef<SGraphNode> > & GetNodes() const;`
- L40 _public prototype_ `virtual bool IsValidOperation() const;`
- L43 _protected typedef_ `typedef FGraphEditorDragDropAction Super;`
- L45 _protected prototype_ `UEdGraphNode* GetGraphNodeForSGraphNode(TSharedRef<SGraphNode>& SNode);`
- L50 _protected member_ `TSharedPtr<SGraphPanel> GraphPanel;` — graph panel
- L53 _protected member_ `TArray< TSharedRef<SGraphNode> > DraggedNodes;` — our dragged nodes
- L56 _protected member_ `FVector2f DecoratorAdjust;` — Offset information for the decorator widget
- L59 _protected member_ `bool bValidOperation;` — if we can drop our node here

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Private/GraphEditorCommon.h` (Private)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Private/GraphEditorSnapping/NodeSnappingManager.h` (Private)


#### struct `FArrangedGraphNode`  
`struct FArrangedGraphNode`  
_L8-12_
- L10 _public member_ `FGeometry Geometry;`
- L11 _public member_ `TSharedPtr<SGraphNode> Widget;`

#### struct `FNodeSnappingManager`  
`struct FNodeSnappingManager`  
_L14-81_
- L16 _public prototype_ `FNodeSnappingManager(TWeakPtr<SGraphPanel> InOwningPanel);`
- L18 _public prototype_ `void RemoveNode(const UEdGraphNode* Node);`
- L19 _public prototype_ `bool IsDragging() const;`
- L20 _public prototype_ `bool BeginDragWithSnap(const FGeometry& MyGeometry, const FPointerEvent& PointerEvent);`
- L21 _public prototype_ `bool FinalizeNodeMovements();`
- L22 _public prototype_ `void UpdateDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L23 _public prototype_ `void HandleGraphChanged();`
- L24 _public prototype_ `void ForEachNode(TFunctionRef<void(const TSharedRef<SNodePanel::SNode>&)> Ftor) const;`
- L25 _public prototype_ `FArrangedGraphNode GetGraphNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L27 _public prototype_ `static bool IsNodeSnappingEnabled();`
- L37 _private prototype_ `void CommitDrag();`
- L38 _private prototype_ `void ResetDragManager();`
- L39 _private prototype_ `const UEdGraphSchema* GetSchema() const;`
- L40 _private prototype_ `bool TryToSnapDataflow(FPendingSnap& PendingSnap);`
- L41 _private prototype_ `bool TryToSnapControlflow(FPendingSnap& PendingSnap);`
- L42 _private prototype_ `bool TrySnapTo(UEdGraphPin* OtherPin, UEdGraphPin* PinOnMovingNode);`
- L43 _private prototype_ `void SnapControlFlowPeer(FPendingSnap& SnapState, TSharedRef<SGraphPin> PinToSnapTo, UEdGraphPin* PinOnMovingNode);`
- L45 _private prototype_ `void ClearAllSnaps(TSharedRef<SGraphNode> OnNode);`
- L46 _private prototype_ `void ClearControlFlowSnap(TSharedRef<SGraphNode> OnNode);`
- L47 _private prototype_ `void ClearDataSnap(TSharedRef<SGraphNode> OnNode);`
- L48 _private prototype_ `void UpdateSnapsFromModel(TSharedRef<SGraphNode> OnNode);`
- L49 _private prototype_ `static TArray<TSharedRef<SGraphNode>> GetControlFlowInputNodes(TSharedRef<SGraphNode> ForNode);`
- L50 _private prototype_ `static TArray<TSharedRef<SGraphNode>> GetControlFlowOutputNodes(TSharedRef<SGraphNode> ForNode);`
- L52 _private prototype_ `FArrangedGraphNode FindNodeForMouseInteraction( const FGeometry& MyGeometry, const FPointerEvent& PointerEvent, FVector2f& OutPositionInNode ) const;`
- L53 _private prototype_ `TSharedPtr<SGraphNode> FindNodeForSnap(TSharedPtr<SGraphNode> NodeBeingMoved);`
- L54 _private prototype_ `TSharedPtr<SGraphPin> FindBestControlFlowForSnap(TSharedPtr<SGraphNode> NodeBeingMoved, UEdGraphPin* Pin);`
- L55 _private prototype_ `TSharedPtr<SGraphPin> GetPreferredControlFlowSnapTarget(TSharedPtr<SGraphPin> A, TSharedPtr<SGraphPin> B) const;`
- L56 _private prototype_ `static TSharedRef<SGraphNode> GetSGraphNode(TSharedRef<SGraphPanel> FromPanel, const UEdGraphNode* Node);`
- L57 _private prototype_ `TSharedPtr<SGraphNode> TryGetGraphNode(const UEdGraphNode* Node);`
- L58 _private prototype_ `void ModifySafe(UEdGraphPin* Pin);`
- L60 _private member_ `TWeakPtr<SGraphPanel> OwningPanel;` — must be weak, otherwise we'll have a cycle, never meant to be null
- L62 _private member_ `TUniquePtr<FScopedTransaction> MoveNodeTransaction;`
- L64 _private member_ `TArray<FPendingSnap> PendingSnaps;` — @todo: rename
- L65 _private member_ `TSharedPtr<SGraphNode> RootDragNode;` — actual node that is being dragged, used to calculate deltas
- L66 _private member_ `TSet<UEdGraphNode*> MovingNodes;`
- L67 _private member_ `TSet<UEdGraphNode*> ModifiedNodes;` — track modification to make sure we don't modify after mutating
- L78 _private member_ `TArray<FPendingConnection> UncommittedConnections;`
- L80 _private member_ `bool bIsActivelyDragging;`

#### struct `FNodeSnappingManager::FPendingSnap`  
`struct FPendingSnap`  
_L29-35_
- L31 _public member_ `TSharedPtr<SGraphNode> NodeBeingDragged;`
- L32 _public member_ `TSharedPtr<SGraphPin> PinSnappedTo;`
- L34 _public prototype_ `bool operator==(const FPendingSnap& RHS) const = default;`

#### struct `FNodeSnappingManager::FPendingConnection`  
`struct FPendingConnection`  
_L73-77_
- desc: A list of uncommitted connections, which will be created only if the final state of the drag operation leaves them in connected positions. This is meant to facilitate connecting nodes by dragging them on top of eachother/compatible pins. We use FEdGraphPinReference for persistent references to visible pins across node refreshes:
- L75 _public member_ `FEdGraphPinReference DraggingPin;`
- L76 _public member_ `FEdGraphPinReference StablePin;`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeCallParameterCollectionFunction.h` (Private)


#### class `SGraphNodeCallParameterCollectionFunction`  
`class SGraphNodeCallParameterCollectionFunction : public SGraphNodeK2Default`  
_L11-18_
- inherits: `SGraphNodeK2Default`
- L16 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeFormatText.h` (Private)


#### class `SGraphNodeFormatText`  
`class SGraphNodeFormatText : public SGraphNodeK2Base`  
_L14-30_
- inherits: `SGraphNodeK2Base`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeFormatText)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_FormatText* InNode);`
- L23 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L26 _protected prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;`
- L27 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L28 _protected prototype_ `virtual FReply OnAddPin() override;`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeK2Copy.h` (Private)


#### class `SGraphNodeK2Copy`  
`class SGraphNodeK2Copy : public SGraphNodeK2Base`  
_L17-32_
- inherits: `SGraphNodeK2Base`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Copy)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node* InNode);`
- L26 _public prototype_ `virtual void UpdateGraphNode() override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea() override;`
- L28 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L29 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L30 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeK2CreateDelegate.h` (Private)


#### class `SGraphNodeK2CreateDelegate`  
`class SGraphNodeK2CreateDelegate : public SGraphNodeK2Base`  
_L24-65_
- inherits: `SGraphNodeK2Base`
- desc: @brief	The CreateDelegate node will allow users to bind to event dispatchers based off of appropriate function signatures, or create a matching one.
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2CreateDelegate)`
- L28 _public prototype_ `SLATE_END_ARGS() TSharedPtr<FString> CreateMatchingFunctionData;`
- L34 _public member_ `TSharedPtr<FString> CreateMatchingEventData;` — Data that can be used to create a matching event based on based on the parameters of a create event node
- L37 _public prototype_ `virtual ~SGraphNodeK2CreateDelegate();`
- L38 _public prototype_ `void Construct(const FArguments& InArgs, UK2Node* InNode);`
- L39 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L42 _protected prototype_ `static FText FunctionDescription(const UFunction* Function, const bool bOnlyDescribeSignature = false, const int32 CharacterLimit = 32);`
- L44 _protected prototype_ `FText GetCurrentFunctionDescription() const;`
- L49 _private member_ `TWeakPtr<SSearchableComboBox> FunctionOptionComboBox;`
- L50 _private member_ `TArray< TSharedPtr< FString > > FunctionOptionList;`
- L52 _private prototype_ `TSharedRef<SWidget> MakeFunctionOptionComboWidget(TSharedPtr<FString> InItem);`
- L55 _private prototype_ `void OnFunctionSelected(TSharedPtr<FString> FunctionItemData, ESelectInfo::Type SelectInfo);` — Callback for when the function selection has changed from the dropdown
- L64 _private prototype_ `TSharedPtr<FString> AddDefaultFunctionDataOption(const FText& DescriptionName);` — Adds a FunctionItemData with a given description to the array of FunctionDataItems. @param	DescriptionName		Description of the option to give the user @return	Shared pointer to the FunctionItemData

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeK2Sequence.h` (Private)


#### class `SGraphNodeK2Sequence`  
`class SGraphNodeK2Sequence : public SGraphNodeK2Base`  
_L14-28_
- inherits: `SGraphNodeK2Base`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Sequence)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UK2Node* InNode );`
- L24 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;` — SGraphNode interface
- L25 _protected prototype_ `virtual FReply OnAddPin() override;`
- L26 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeK2Terminator.h` (Private)


#### class `SGraphNodeK2Terminator`  
`class SGraphNodeK2Terminator : public SGraphNodeK2Base`  
_L11-23_
- inherits: `SGraphNodeK2Base`
- L14 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Terminator)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UK2Node* InNode );`
- L19 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L22 _protected prototype_ `virtual void UpdateGraphNode() override;`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeK2Timeline.h` (Private)


#### class `SGraphNodeK2Timeline`  
`class SGraphNodeK2Timeline : public SGraphNodeK2Default`  
_L13-24_
- inherits: `SGraphNodeK2Default`
- L16 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Timeline)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_Timeline* InNode);`
- L22 _public prototype_ `void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;` — SNodePanel::SNode interface

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeMakeStruct.h` (Private)


#### struct `FOptionalPinOverrideState`  
`struct FOptionalPinOverrideState`  
_L15-44_
- L18 _public member_ `FText DisplayText;` — Display text to display for this item in the selection widget
- L21 _public member_ `FText TooltipText;` — Tooltip to display for this item on both the node and in the selection widget
- L24 _public member_ `bool bIsOverrideEnabled;` — TRUE if this option will enable the override
- L27 _public member_ `bool bIsValuePinVisible;` — TRUE if this option will make the value visible/editable
- L30 _public member_ `bool bIsOverridePinVisible;` — TRUE if the override value can be edited
- L32 _public function_ `FOptionalPinOverrideState(FText InDisplayText, FText InTooltipText, bool bInIsOverridePinVisible, bool bInIsOverrideEnabled, bool bInIsValuePinVisible) : DisplayText(InDisplayText) , TooltipText(InTooltipText) , bIsOverrideEnabled(bInIsOverrideEnabled) , bIsValuePinVisible(bInIsValuePinVisible) , bIsOverridePinVisible(bInIsOverridePinVisible)`
- L40 _public function_ `bool operator== (const FOptionalPinOverrideState& InOther) const`

#### class `SGraphNodeMakeStruct`  
`class SGraphNodeMakeStruct : public SGraphNodeK2Base`  
_L46-61_
- inherits: `SGraphNodeK2Base`
- L49 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeMakeStruct)`
- L50 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_MakeStruct* InNode);`
- L55 _public prototype_ `bool IsPinEnabled(FOptionalPinFromProperty* InPropertyEntry) const;` — Callback for the pin for whether the pin should display as enabled
- L58 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;` — SGraphNode interface
- L59 _public prototype_ `virtual void CreatePinWidgets() override;`

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeSpawnActor.h` (Private)


#### class `SGraphNodeSpawnActor`  
`class SGraphNodeSpawnActor : public SGraphNodeK2Default`  
_L7-14_
- inherits: `SGraphNodeK2Default`
- L12 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeSpawnActorFromClass.h` (Private)


#### class `SGraphNodeSpawnActorFromClass`  
`class SGraphNodeSpawnActorFromClass : public SGraphNodeK2Default`  
_L7-14_
- inherits: `SGraphNodeK2Default`
- L12 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface

### `Source/Editor/GraphEditor/Private/KismetNodes/SGraphNodeSwitchStatement.h` (Private)


#### class `SGraphNodeSwitchStatement`  
`class SGraphNodeSwitchStatement : public SGraphNodeK2Base`  
_L14-30_
- inherits: `SGraphNodeK2Base`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeSwitchStatement)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_Switch* InNode);`
- L23 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L26 _protected prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;`
- L27 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L28 _protected prototype_ `virtual FReply OnAddPin() override;`

### `Source/Editor/GraphEditor/Private/KismetPins/SGraphPinCollisionProfile.h` (Private)


#### class `SGraphPinCollisionProfile`  
`class SGraphPinCollisionProfile : public SGraphPin`  
_L19-44_
- inherits: `SGraphPin`
- desc: Customizes a CollisionProfileName graph pin to use a dropdown
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphPinCollisionProfile)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L30 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L32 _protected prototype_ `void OnSelectionChanged(TSharedPtr<FName> NameItem, ESelectInfo::Type SelectInfo);`
- L33 _protected prototype_ `void OnComboBoxOpening();`
- L35 _protected prototype_ `TSharedPtr<FName> GetSelectedName() const;`
- L37 _protected prototype_ `void SetPropertyWithName(const FName& Name);`
- L38 _protected prototype_ `void GetPropertyAsName(FName& OutName) const;`
- L42 _protected member_ `TArray<TSharedPtr<FName>> NameList;`
- L43 _protected member_ `TSharedPtr<SNameComboBox> NameComboBox;`

### `Source/Editor/GraphEditor/Private/KismetPins/SGraphPinIndex.h` (Private)


#### class `SGraphPinIndex`  
`class SGraphPinIndex : public SGraphPin`  
_L12-27_
- inherits: `SGraphPin`
- L15 _public function_ `SLATE_BEGIN_ARGS(SGraphPinIndex)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L20 _public prototype_ `FEdGraphPinType OnGetPinType() const;`
- L21 _public prototype_ `void OnTypeChanged(const FEdGraphPinType& PinType);`
- L25 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

### `Source/Editor/GraphEditor/Private/KismetPins/SGraphPinKey.h` (Private)


#### class `SGraphPinKey`  
`class SGraphPinKey : public SGraphPin`  
_L14-40_
- inherits: `SGraphPin`
- L17 _public function_ `SLATE_BEGIN_ARGS(SGraphPinKey)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L29 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — Function to create class specific widget. @return Reference to the newly created widget object
- L34 _private prototype_ `TOptional<FKey> GetCurrentKey() const;` — Gets the current Key being edited.
- L37 _private prototype_ `void OnKeyChanged(TSharedPtr<FKey> SelectedKey);` — Updates the pin default when a new key is selected.
- L39 _private member_ `FKey SelectedKey;`

### `Source/Editor/GraphEditor/Private/KismetPins/SGraphPinStruct.h` (Private)


#### class `SGraphPinStruct`  
`class SGraphPinStruct : public SGraphPinObject`  
_L19-38_
- inherits: `SGraphPinObject`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGraphPinStruct)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L29 _protected prototype_ `void OnPickedNewStruct(const UScriptStruct* ChosenStruct);` — Called when a new struct was picked via the asset picker
- L32 _protected prototype_ `virtual FReply OnClickUse() override;`
- L33 _protected function_ `virtual bool AllowSelfPinWidget() const override`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAssetPicker() override;`
- L35 _protected prototype_ `virtual FText GetDefaultComboText() const override;`
- L36 _protected prototype_ `virtual FOnClicked GetOnUseButtonDelegate() override;`

### `Source/Editor/GraphEditor/Private/KismetPins/SGraphPinText.h` (Private)


#### class `SGraphPinText`  
`class SGraphPinText : public SGraphPin`  
_L12-24_
- inherits: `SGraphPin`
- L15 _public function_ `SLATE_BEGIN_ARGS(SGraphPinText)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L22 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

### `Source/Editor/GraphEditor/Private/SGraphEditorImpl.h` (Private)


#### struct `FAlignmentData`  
`struct FAlignmentData`  
_L55-73_
- desc: Struct used for generically aligning nodes
- L57 _public function_ `FAlignmentData(UEdGraphNode* InNode, int32& InTargetProperty, float InTargetOffset) : Node(InNode), TargetProperty(InTargetProperty), TargetOffset(InTargetOffset)`
- L62 _public member_ `UEdGraphNode* Node;` — The node to position
- L64 _public member_ `int32& TargetProperty;` — The property within the node to read/write
- L66 _public member_ `float TargetOffset;` — The offset from the property to consider for alignment
- L69 _public function_ `float GetTarget() const` — Get the destination target from this alignment data (property + offset)

#### enum `EAlignType`  
`enum class EAlignType : uint8`  
_L75-78_
- L77 _public enumerator_ `Minimum`
- L77 _public enumerator_ `Minimum`
- L77 _public enumerator_ `Minimum`

#### struct `FAlignmentHelper`  
`struct FAlignmentHelper`  
_L81-197_
- desc: Helper class for aligning nodes
- L84 _public function_ `FAlignmentHelper(TSharedRef<SGraphEditor> InGraphEditor, EOrientation InOrientation, EAlignType InAlignType) : GraphEditor(MoveTemp(InGraphEditor))` — Construct from a graph editor, an orientation, and an alignment type
- L109 _public function_ `void Align()` — Align all the nodes
- L147 _private prototype_ `FAlignmentData GetAlignmentDataForNode(UEdGraphNode* Node);` — Collect alignment data for a given node, based on our settings
- L150 _private function_ `float DetermineAlignmentTarget()` — Determine the horizontal/vertical position that all nodes should align to
- L188 _private member_ `TSharedRef<SGraphEditor> GraphEditor;` — The graph editor
- L190 _private member_ `EOrientation Orientation;` — Whether we are aligning horizontally/vertically
- L192 _private member_ `EAlignType AlignType;` — Whether we are aligning to the minimum/middle/maximum bounds
- L194 _private member_ `UEdGraphNode* CardinalNode;` — The cardinal node that all other nodes should align to (possibly null)
- L196 _private member_ `TArray<FAlignmentData> AlignmentData;` — Generated alignment data

#### class `SGraphEditorImpl`  
`class SGraphEditorImpl : public SGraphEditor`  
_L204-433_
- inherits: `SGraphEditor`
- L207 _public function_ `SLATE_BEGIN_ARGS( SGraphEditorImpl ) : _AdditionalCommands( TSharedPtr<FUICommandList>() ) , _IsEditable(true) , _DisplayAsReadOnly(false) , _AllowConnectionSlicing(true) , _GraphSupportsInvalidation(false)`
- L216 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, AdditionalCommands) SLATE_ATTRIBUTE( bool, IsEditable ) SLATE_ATTRIBUTE( bool, DisplayAsReadOnly ) SLATE_ARGUMENT( TSharedPtr<SWidget>, TitleBar ) SLATE_ATTRIBUTE( FGraphAppearanceInfo, Appearance ) SLATE_ARGUMENT( UEdGraph*, GraphToEdit ) SLATE_ARGUMENT(TSharedPtr<TArray<FDiffSingleResult>>, DiffResults ) SLATE_ATTRIBUTE(int32, FocusedDiffResult ) SLATE_ARGUMENT(SGraphEditor::FGraphEditorEvents, GraphEvents) SLATE_ARGUMENT(bool, AutoExpandActionMenu) SLATE_EVENT(FSimpleDelegate, OnNavigateHistoryBack) SLATE_EVENT(FSimpleDelegate, OnNavigateHistoryForward) SLATE_EVENT(FOnGraphEditorTickDelegate, OnTick);`
- L231 _public prototype_ `SLATE_ATTRIBUTE(bool, ShowGraphStateOverlay) SLATE_ATTRIBUTE(bool, AllowConnectionSlicing) SLATE_ARGUMENT(bool, GraphSupportsInvalidation) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Show overlay elements for the graph state such as the PIE and read-only borders and text
- L241 _private member_ `TSharedPtr< FUICommandList > Commands;`
- L242 _private member_ `mutable TSet<UEdGraphNode*> SelectedNodeCache;`
- L245 _private member_ `SOverlay::FOverlaySlot* GraphPanelSlot;` — The panel contains the GraphNode widgets, draws the connections, etc
- L246 _private member_ `TSharedPtr<SGraphPanel> GraphPanel;`
- L247 _private member_ `TSharedPtr<SWidget> TitleBar;`
- L249 _private member_ `FEdGraphPinReference GraphPinForMenu;`
- L250 _private member_ `TWeakObjectPtr<UEdGraphNode> GraphNodeForMenu;`
- L251 _private member_ `bool bResetMenuContext;`
- L254 _private member_ `TAttribute<FGraphAppearanceInfo> Appearance;` — Info on the appearance
- L256 _private member_ `SGraphEditor::FOnFocused OnFocused;`
- L257 _private member_ `SGraphEditor::FOnCreateActionMenuAtLocation OnCreateActionMenuAtLocation;`
- L258 _private member_ `SGraphEditor::FOnCreateNodeOrPinMenu OnCreateNodeOrPinMenu;`
- L260 _private member_ `TAttribute<bool> IsEditable;`
- L263 _private member_ `TAttribute<bool> DisplayAsReadOnly;` — Attribute for displaying the graph as read-only, which is a visual state only where IsEditable is a functional state
- L265 _private member_ `bool bAutoExpandActionMenu;`
- L268 _private member_ `TAttribute<bool> ShowGraphStateOverlay;` — Whether to show the state (read only / PIE etc) Overlay on the panel
- L271 _private member_ `TArray< TWeakPtr<SGraphEditor> > LockedGraphs;` — FOnViewChanged	OnViewChanged;
- L274 _private prototype_ `EVisibility PIENotification( ) const;` — Function to check whether PIE is active to display "Simulating" text in graph panel
- L277 _private prototype_ `EVisibility ReadOnlyVisibility() const;` — Function to check whether we should show read-only text in the panel
- L280 _private prototype_ `FText GetInstructionText() const;` — Returns dynamic text, meant to passively instruct the user on what to do in the graph
- L282 _private prototype_ `EVisibility InstructionTextVisibility() const;` — Function to check whether we should show instruction text to the user
- L284 _private prototype_ `float GetInstructionTextFade() const;` — Returns a 0.0 to 1.0 value, denoting the instruction text's fade percent
- L286 _private prototype_ `FLinearColor InstructionTextTint() const;` — A dynamic tint for the instruction text (allows us to nicely fade it in/out)
- L288 _private prototype_ `FSlateColor InstructionBorderColor() const;` — Determines the color of the box containing the instruction text
- L291 _private member_ `TSharedPtr<SNotificationList> NotificationListPtr;` — Notification list to pass messages to editor users
- L294 _private member_ `FSimpleDelegate OnNavigateHistoryBack;` — Callback to navigate backward in the history
- L296 _private member_ `FSimpleDelegate OnNavigateHistoryForward;` — Callback to navigate forward in the history
- L299 _private member_ `FOnNodeSpawnedByKeymap OnNodeSpawnedByKeymap;` — Invoked when a node is created by a keymap
- L305 _private member_ `FOnGraphEditorTickDelegate OnTickDelegate;` — Invoked during the tick of the graph editor. Can be used for custom layout code / node UI relevant code
- L308 _public prototype_ `virtual ~SGraphEditorImpl();`
- L310 _public prototype_ `void OnClosedActionMenu();`
- L312 _public prototype_ `FActionMenuContent GraphEd_OnGetContextMenuFor(const FGraphContextMenuArguments& SpawnInfo);`
- L317 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L319 _public prototype_ `void FocusLockedEditorHere();`
- L321 _public prototype_ `virtual FReply OnFocusReceived( const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent ) override;`
- L322 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L323 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L324 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L325 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L329 _public prototype_ `virtual const TSet<class UObject*>& GetSelectedNodes() const override;` — SGraphEditor interface
- L330 _public prototype_ `virtual void ClearSelectionSet() override;`
- L331 _public prototype_ `virtual void SetNodeSelection(UEdGraphNode* Node, bool bSelect) override;`
- L332 _public prototype_ `virtual void SelectAllNodes() override;`
- L334 _public prototype_ `virtual UE::Slate::FDeprecateVector2DResult GetPasteLocation2f() const override;`
- L335 _public prototype_ `virtual bool IsNodeTitleVisible( const UEdGraphNode* Node, bool bRequestRename ) override;`
- L336 _public prototype_ `virtual void JumpToNode( const UEdGraphNode* JumpToMe, bool bRequestRename = false, bool bSelectNode = true ) override;`
- L337 _public prototype_ `virtual void JumpToPin( const UEdGraphPin* JumpToMe ) override;`
- L338 _public prototype_ `virtual UEdGraphPin* GetGraphPinForMenu() override;`
- L339 _public prototype_ `virtual UEdGraphNode* GetGraphNodeForMenu() override;`
- L340 _public prototype_ `virtual void ZoomToFit(bool bOnlySelection) override;`
- L341 _public prototype_ `virtual bool GetBoundsForSelectedNodes( class FSlateRect& Rect, float Padding) override;`
- L342 _public prototype_ `virtual bool GetBoundsForNode( const UEdGraphNode* InNode, class FSlateRect& Rect, float Padding) const override;`
- L343 _public prototype_ `virtual void NotifyGraphChanged() override;`
- L344 _public prototype_ `virtual TSharedPtr<SWidget> GetTitleBar() const override;`
- L345 _public prototype_ `virtual void SetViewLocation(const FVector2f& Location, float ZoomAmount, const FGuid& BookmarkId = FGuid()) override;`
- L346 _public prototype_ `virtual void GetViewLocation(FVector2f& Location, float& ZoomAmount) override;`
- L347 _public prototype_ `virtual void GetViewBookmark(FGuid& BookmarkId) override;`
- L348 _public prototype_ `virtual void LockToGraphEditor(TWeakPtr<SGraphEditor> Other) override;`
- L349 _public prototype_ `virtual void UnlockFromGraphEditor(TWeakPtr<SGraphEditor> Other) override;`
- L350 _public prototype_ `virtual void AddNotification ( FNotificationInfo& Info, bool bSuccess ) override;`
- L351 _public prototype_ `virtual TSharedPtr<SNotificationItem> AddNotification(FNotificationInfo& Info) override;`
- L352 _public prototype_ `virtual void SetPinVisibility(SGraphEditor::EPinVisibility Visibility) override;`
- L353 _public prototype_ `virtual TSharedRef<FActiveTimerHandle> RegisterActiveTimer(float TickPeriod, FWidgetActiveTimerDelegate TickFunction) override;`
- L354 _public prototype_ `virtual void StraightenConnections() override;`
- L355 _public prototype_ `virtual void StraightenConnections(UEdGraphPin* SourcePin, UEdGraphPin* PinToAlign) const override;`
- L356 _public prototype_ `virtual void RefreshNode(UEdGraphNode& Node) override;`
- L357 _public prototype_ `virtual void CaptureKeyboard() override;`
- L358 _public prototype_ `virtual void SetNodeFactory(const TSharedRef<class FGraphNodeFactory>& NewNodeFactory) override;`
- L359 _public prototype_ `virtual void OnAlignTop() override;`
- L360 _public prototype_ `virtual void OnAlignMiddle() override;`
- L361 _public prototype_ `virtual void OnAlignBottom() override;`
- L362 _public prototype_ `virtual void OnAlignLeft() override;`
- L363 _public prototype_ `virtual void OnAlignCenter() override;`
- L364 _public prototype_ `virtual void OnAlignRight() override;`
- L366 _public prototype_ `virtual void OnStraightenConnections() override;`
- L368 _public prototype_ `virtual void OnDistributeNodesH() override;`
- L369 _public prototype_ `virtual void OnDistributeNodesV() override;`
- L371 _public prototype_ `virtual void OnStackNodesH() override;`
- L372 _public prototype_ `virtual void OnStackNodesV() override;`
- L374 _public prototype_ `virtual int32 GetNumberOfSelectedNodes() const override;`
- L376 _public prototype_ `virtual UEdGraphNode* GetSingleSelectedNode() const override;`
- L378 _public prototype_ `virtual SGraphPanel* GetGraphPanel() const override;`
- L380 _public prototype_ `virtual void SetOnTick(FOnGraphEditorTickDelegate InOnTickDelegate) override;`
- L387 _protected prototype_ `bool CanReconstructNodes() const;` — COMMAND HANDLING
- L388 _protected prototype_ `bool CanBreakNodeLinks() const;`
- L389 _protected prototype_ `bool CanSummonCreateNodeMenu() const;`
- L391 _protected prototype_ `void ReconstructNodes();`
- L392 _protected prototype_ `void BreakNodeLinks();`
- L394 _protected prototype_ `void SummonCreateNodeMenu();`
- L397 _protected prototype_ `virtual void OnGraphChanged( const FEdGraphEditAction& InAction ) override;` — SGraphEditor interface
- L401 _private prototype_ `FText GetZoomText() const;`
- L403 _private prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L405 _private prototype_ `bool IsGraphEditable() const;`
- L408 _private prototype_ `bool DisplayGraphAsReadOnly() const;` — Helper function to decide whether to display the graph in a read-only state
- L410 _private prototype_ `bool IsLocked() const;`
- L412 _private prototype_ `void RegisterContextMenu(const class UEdGraphSchema* Schema, struct FToolMenuContext& MenuContext) const;`
- L413 _private prototype_ `class UToolMenu* GenerateContextMenu(const class UEdGraphSchema* Schema, struct FToolMenuContext& MenuContext) const;`
- L415 _private prototype_ `static FName GetNodeParentContextMenuName(UClass* InClass);`
- L416 _private prototype_ `static FName GetNodeContextMenuName(UClass* InClass);`
- L417 _private prototype_ `static void AddContextMenuCommentSection(UToolMenu* InMenu);`
- L419 _private prototype_ `void GetPinContextMenuActionsForSchema(UToolMenu* InMenu) const;`
- L420 _private prototype_ `void ExecuteBreakPinLinks(const FToolMenuContext& InContext) const;`
- L421 _private prototype_ `bool IsBreakPinLinksVisible(const FToolMenuContext& InContext) const;`
- L422 _private prototype_ `bool IsBreakThisLinkVisible(const FToolMenuContext& InContext) const;`
- L423 _private prototype_ `bool HasAnyLinkedPins(const FToolMenuContext& InContext) const;`
- L425 _private prototype_ `void ExecuteSelectConnectedNodesFromPin(const FToolMenuContext& InContext) const;`
- L426 _private prototype_ `void SelectAllNodesInDirection(const UEdGraphPin* InGraphPin) const;`
- L427 _private prototype_ `bool IsSelectConnectedNodesFromPinVisible(const FToolMenuContext& InContext, EEdGraphPinDirection DirectionToSelect) const;`
- L429 _private prototype_ `EActiveTimerReturnType HandleFocusEditorDeferred(double InCurrentTime, float InDeltaTime);`
- L431 _private member_ `TWeakPtr<FActiveTimerHandle> FocusEditorTimer;`
- L432 _private member_ `uint32 NumNodesAddedSinceLastPointerPosition;`

#### Free symbols / members of external scopes

- L103 _function_ `AlignmentData.Sort([](const FAlignmentData& A, const FAlignmentData& B) { return A.GetTarget() < B.GetTarget(); });` (scope `FAlignmentHelper::FAlignmentHelper`) — Sort the data based on target - important for future algorithms

### `Source/Editor/GraphEditor/Public/BlueprintConnectionDrawingPolicy.h` (Public)


#### class `FKismetConnectionDrawingPolicy`  
`class FKismetConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L35-146_
- inherits: `FConnectionDrawingPolicy`
- desc: This class draws the connections for an UEdGraph using a K2-based schema
- L55 _protected typedef_ `typedef TMap<UEdGraphPin*, FTimePair> FExecPairingMap;` — Map of exec-pins to a pair of execution times (holds timing info for the owning-node, paired with a time of execution for the linked node)... only one timing-pair per pin because exec outputs can only connect to one node
- L58 _protected member_ `TMap<UEdGraphNode*, FExecPairingMap> PredecessorPins;` — Map of executed nodes, and the execution pins that lead to them being ran
- L60 _protected member_ `UEdGraph* GraphObj;`
- L61 _protected member_ `double CurrentTime;`
- L62 _protected member_ `double LatestTimeDiscovered;`
- L64 _protected member_ `FLinearColor AttackColor;`
- L65 _protected member_ `FLinearColor SustainColor;`
- L66 _protected member_ `FLinearColor ReleaseColor;`
- L68 _protected member_ `float AttackWireThickness;`
- L69 _protected member_ `float SustainWireThickness;`
- L70 _protected member_ `float ReleaseWireThickness;`
- L71 _protected member_ `float DefaultDataWireThickness;`
- L72 _protected member_ `float DefaultExecutionWireThickness;`
- L74 _protected member_ `float TracePositionBonusPeriod;`
- L75 _protected member_ `float TracePositionExponent;`
- L76 _protected member_ `float AttackHoldPeriod;`
- L77 _protected member_ `float DecayPeriod;`
- L78 _protected member_ `float DecayExponent;`
- L79 _protected member_ `float SustainHoldPeriod;`
- L80 _protected member_ `float ReleasePeriod;`
- L81 _protected member_ `float ReleaseExponent;`
- L84 _protected member_ `TMap<class UK2Node_Knot*, bool> KnotToReversedDirectionMap;` — Each time a knot is encountered, input geometry is compared to output geometry to see if the pins on the knot need to be reversed
- L88 _protected prototype_ `virtual bool TreatWireAsExecutionPin(UEdGraphPin* InputPin, UEdGraphPin* OutputPin) const;` — Should this wire be treated as an execution pin, querying the execution trace for connected nodes to draw it differently?
- L91 _protected prototype_ `UBlueprint* GetTargetBlueprint() const;` — Determines the target Blueprint for querying the active debugging context.
- L94 _protected prototype_ `bool CanBuildRoadmap(UBlueprint* TargetBP) const;` — Determines if the given Blueprint context has a valid object for debugging.
- L97 _public prototype_ `FKismetConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);`
- L99 _public prototype_ `virtual void BuildExecutionRoadmap();`
- L101 _public prototype_ `virtual bool CanBuildRoadmap() const;`
- L103 _public prototype_ `void CalculateEnvelopeAlphas(double ExecutionTime, float& AttackAlpha, float& SustainAlpha) const;`
- L106 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;` — FConnectionDrawingPolicy interface
- L107 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& PinGeometries, FArrangedChildren& ArrangedNodes) override;`
- L110 _public prototype_ `virtual void DetermineStyleOfExecWire(float& Thickness, FLinearColor& WireColor, bool& bDrawBubbles, const FTimePair& Times);`
- L112 _public prototype_ `virtual void SetIncompatiblePinDrawState(const TSharedPtr<SGraphPin>& StartPin, const TSet< TSharedRef<SWidget> >& VisiblePins) override;`
- L113 _public prototype_ `virtual void ResetIncompatiblePinDrawState(const TSet< TSharedRef<SWidget> >& VisiblePins) override;`
- L124 _protected prototype_ `bool AreNodesGraphicallySequential(UEdGraphNode* InputNode, UEdGraphNode* OutputNode) const;` — Checks that the specified nodes are connected in the graph directly by an exec pin. @param  InputNode	The node whose exec output(s) should be connected to OutputNode. @param  OutputNode	The node whose exec input should be coming from the InputNode. @return True if the two nodes are connected in the graph, otherwise false.
- L140 _protected prototype_ `FTimePair const* BackTraceExecPath(UEdGraphPin const* const OutputPin, FExecPairingMap const* const NodeExecutionList);` — With the introduction of "reroute" (UK2Node_Knot) nodes, we have to backtrace to find a node that was actually executed before the one in question (knot nodes are removed at compile time, and therefore never executed). This function recursively searches for any pins feeding the OutputPin (or the OutputPin itself); it looks for a pin on a non-reroute node (one that is listed in NodeExecutionList). @param  OutputPin			An exec pin, leading into the node in question (an output pin on some other node). @param  NodeExecutionList	A list of pins that feed the execution of a specific node. @return Null if OutputPin did not cause the invocation of the node in question, otherwise a valid time pair denoting when the node was executed.
- L142 _protected prototype_ `bool ShouldChangeTangentForKnot(class UK2Node_Knot* Knot);`
- L143 _protected prototype_ `bool GetAverageConnectedPosition(class UK2Node_Knot* Knot, EEdGraphPinDirection Direction, FVector2f& OutPos) const;`
- L144 _protected prototype_ `bool FindPinCenter(UEdGraphPin* Pin, FVector2f& OutCenter) const;`
- L145 _protected prototype_ `static UObject* GetObjectBeingDebugged(UBlueprint* TargetBP);`

#### struct `FKismetConnectionDrawingPolicy::FTimePair`  
`struct FTimePair`  
_L39-49_
- desc: Times for one execution pair within the current graph
- L41 _public member_ `double PredExecTime;` — time that the node with the associated exec-out was executed
- L42 _public member_ `double ThisExecTime;` — time that the following node was executed
- L44 _public function_ `FTimePair() : PredExecTime(0.0) , ThisExecTime(0.0)`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/ConnectionDrawingPolicy.h` (Public)


#### class `FGeometryHelper`  
`class FGeometryHelper`  
_L43-58_
- L46 _public prototype_ `static UE::Slate::FDeprecateVector2DResult VerticalMiddleLeftOf(const FGeometry& SomeGeometry);`
- L47 _public prototype_ `static UE::Slate::FDeprecateVector2DResult VerticalMiddleRightOf(const FGeometry& SomeGeometry);`
- L49 _public prototype_ `static UE::Slate::FDeprecateVector2DResult CenterOf(const FGeometry& SomeGeometry);`
- L51 _public prototype_ `static void ConvertToPoints(const FGeometry& Geom, TArray<FVector2D>& Points);` — `UE_DEPRECATED(5.6, "Use Array of FVector2f instead of FVector2D for slate positions")`
- L52 _public prototype_ `static void ConvertToPoints(const FGeometry& Geom, TArray<FVector2f>& Points);`
- L55 _public prototype_ `static UE::Slate::FDeprecateVector2DResult FindClosestPointOnLine(const UE::Slate::FDeprecateVector2DParameter& LineStart, const UE::Slate::FDeprecateVector2DParameter& LineEnd, const UE::Slate::FDeprecateVector2DParameter& TestPoint);` — Find the point on line segment from LineStart to LineEnd which is closest to Point
- L57 _public prototype_ `static UE::Slate::FDeprecateVector2DResult FindClosestPointOnGeom(const FGeometry& Geom, const UE::Slate::FDeprecateVector2DParameter& TestPoint);`

#### struct `FConnectionParams`  
`struct FConnectionParams`  
_L63-94_
- L65 _public member_ `FLinearColor WireColor;`
- L66 _public member_ `UEdGraphPin* AssociatedPin1;`
- L67 _public member_ `UEdGraphPin* AssociatedPin2;`
- L69 _public member_ `float WireThickness;`
- L70 _public member_ `bool bDrawBubbles;`
- L71 _public member_ `bool bUserFlag1;`
- L72 _public member_ `bool bUserFlag2;`
- L74 _public member_ `EEdGraphPinDirection StartDirection;`
- L75 _public member_ `EEdGraphPinDirection EndDirection;`
- L77 _public member_ `FDeprecateSlateVector2D StartTangent;`
- L78 _public member_ `FDeprecateSlateVector2D EndTangent;`
- L80 _public function_ `FConnectionParams() : WireColor(FLinearColor::White) , AssociatedPin1(nullptr) , AssociatedPin2(nullptr) , WireThickness(1.5f) , bDrawBubbles(false) , bUserFlag1(false) , bUserFlag2(false) , StartDirection(EGPD_Output) , EndDirection(EGPD_Input) , StartTangent(FVector2f::ZeroVector) , EndTangent(FVector2f::ZeroVector)`

#### class `FConnectionDrawingPolicy`  
`class FConnectionDrawingPolicy`  
_L102-279_
- desc: This class draws the connections for an UEdGraph composed of pins and nodes
- L105 _protected member_ `int32 WireLayerID;`
- L106 _protected member_ `int32 ArrowLayerID;`
- L108 _protected member_ `const FSlateBrush* ArrowImage;`
- L109 _protected member_ `const FSlateBrush* MidpointImage;`
- L110 _protected member_ `const FSlateBrush* BubbleImage;`
- L112 _protected member_ `const UGraphEditorSettings* Settings;`
- L115 _public member_ `FDeprecateSlateVector2D ArrowRadius;`
- L116 _public member_ `FDeprecateSlateVector2D MidpointRadius;`
- L118 _public member_ `FGraphSplineOverlapResult SplineOverlapResult;`
- L119 _public member_ `TArray<TPair<FEdGraphPinReference, FEdGraphPinReference>> ConnectionsIntersectingSliceLine;`
- L129 _protected member_ `float ZoomFactor;`
- L130 _protected member_ `float HoverDeemphasisDarkFraction;`
- L131 _protected member_ `float SliceDeemphasisAlphaMultiplier;`
- L132 _protected member_ `const FSlateRect ClippingRect;`
- L133 _protected member_ `FSlateWindowElementList& DrawElementsList;`
- L134 _protected member_ `TMap< UEdGraphPin*, TSharedPtr<SGraphPin> > PinToPinWidgetMap;`
- L135 _protected member_ `TSet< FEdGraphPinReference > HoveredPins;`
- L136 _protected member_ `TMap<TSharedRef<SWidget>, FArrangedWidget>* PinGeometries;`
- L137 _protected member_ `double LastHoverTimeEvent;`
- L139 _protected member_ `FDeprecateSlateVector2D LocalMousePosition;` — `UE_DEPRECATED(5.8, "Use AbsoluteMousePosition instead, no other change of code needed. The name of this variable was wrong as SetMousePosition was passed the result of 'AllottedGeometry.LocalToAbsolute'.")`
- L140 _protected member_ `FVector2f AbsoluteMousePosition;`
- L143 _protected member_ `TArray<FRelinkConnection> RelinkConnections;` — List of currently relinked connections.
- L146 _protected member_ `TArray<UEdGraphNode*> SelectedGraphNodes;` — Selected nodes in the graph panel.
- L148 _protected member_ `FMarqueeRect SliceLine;`
- L150 _public prototype_ `virtual ~FConnectionDrawingPolicy() = default;`
- L152 _public prototype_ `FConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements);`
- L155 _public prototype_ `void SetHoveredPins(const TSet< FEdGraphPinReference >& InHoveredPins, const TArray< TSharedPtr<SGraphPin> >& OverridePins, double HoverTime);` — Update the drawing policy with the set of hovered pins (which can be empty)
- L158 _public prototype_ `void SetMousePosition(const UE::Slate::FDeprecateVector2DParameter& InMousePos);` — `UE_DEPRECATED(5.8, "Use SetAbsoluteMousePosition instead, no other change of code needed.")`
- L159 _public prototype_ `void SetAbsoluteMousePosition(FVector2f InAbsoluteMousePos);`
- L163 _public prototype_ `void SetSliceLine(const FMarqueeRect& InLine);` — If a (valid) slice line has been set, we'll intersect any drawn splines via DrawConnection() with that line, and add any intersecting pin pairs to the public ConnectionsIntersectingSliceLine array.
- L166 _public prototype_ `void SetMarkedPin(TWeakPtr<SGraphPin> InMarkedPin);` — Update the drawing policy with the marked pin (which may not be valid)
- L169 _public function_ `void SetSelectedNodes(const TArray<UEdGraphNode*>& InSelectedNodes)` — Set the selected nodes from the graph panel.
- L172 _public function_ `void SetRelinkConnections(const TArray<FRelinkConnection>& Connections)` — Set the list of currently relinked connections.
- L174 _public prototype_ `static float MakeSplineReparamTable(const UE::Slate::FDeprecateVector2DParameter& P0, const UE::Slate::FDeprecateVector2DParameter& P0Tangent, const UE::Slate::FDeprecateVector2DParameter& P1, const UE::Slate::FDeprecateVector2DParameter& P1Tangent, FInterpCurve<float>& OutReparamTable);`
- L177 _public prototype_ `virtual void DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L178 _public prototype_ `virtual void DrawSplineWithArrow(const FVector2f& StartPoint, const FVector2f& EndPoint, const FConnectionParams& Params);`
- L180 _public prototype_ `virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params);`
- L183 _public prototype_ `virtual FVector2D ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L184 _public prototype_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const;`
- L188 _public prototype_ `virtual void DrawConnection(int32 LayerId, const FVector2D& Start, const FVector2D& End, const FConnectionParams& Params) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L189 _public prototype_ `virtual void DrawConnection(int32 LayerId, const FVector2f& Start, const FVector2f& End, const FConnectionParams& Params);`
- L192 _public prototype_ `virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L193 _public prototype_ `virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2f& StartPoint, const FVector2f& EndPoint, UEdGraphPin* Pin);`
- L197 _public prototype_ `virtual bool DrawSliceLine();` — If a SliceLine has already been set, draw it. Subclasses may return false to indicate they don't support drawing a slice line or draw it in a different style.
- L200 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params);` — Give specific editor modes a chance to highlight this connection or darken non-interesting connections
- L202 _public prototype_ `virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes);`
- L204 _public prototype_ `virtual void DetermineLinkGeometry( FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry );`
- L214 _public function_ `virtual bool UseDrawStateCaching() const` — Choose whether we want to cache the pins draw state to avoid resetting it for every tick
- L216 _public prototype_ `virtual void SetIncompatiblePinDrawState(const TSharedPtr<SGraphPin>& StartPin, const TSet< TSharedRef<SWidget> >& VisiblePins);`
- L217 _public prototype_ `virtual void ResetIncompatiblePinDrawState(const TSet< TSharedRef<SWidget> >& VisiblePins);`
- L219 _public prototype_ `virtual void ApplyHoverDeemphasis(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, float& Thickness, FLinearColor& WireColor);`
- L221 _public prototype_ `virtual bool IsConnectionCulled( const FArrangedWidget& StartLink, const FArrangedWidget& EndLink ) const;`
- L223 _public prototype_ `virtual TSharedPtr<IToolTip> GetConnectionToolTip(const SGraphPanel& GraphPanel, const FGraphSplineOverlapResult& OverlapData) const;`
- L229 _public prototype_ `virtual bool HaveConnectionsGraphicallyChanged(const SGraphPanel& InGraphPanel, const FVector2f& AbsoluteCursorPosition) const;` — Used in MouseMove to check if the connections have graphically changed and need the GraphPanel to invalidate. The default implementation checks for a difference in HoveredPins, or in difference in connection WireColor or WireThickness.
- L235 _public prototype_ `virtual bool HaveConnectionsGraphicallyChanged(const SGraphPanel& InGraphPanel, const TSet<FEdGraphPinReference>& InNewlyHoveredPins) const;` — Used in MouseMove to check if the connections have graphically changed and need the GraphPanel to invalidate. The default implementation checks for a difference in HoveredPins, or in difference in connection WireColor or WireThickness.
- L239 _protected prototype_ `virtual void BuildPinToPinWidgetMap(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries);` — Helper function used by Draw(). Called before DrawPinGeometries to populate PinToPinWidgetMap
- L242 _protected prototype_ `virtual void DrawPinGeometries(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes);` — Helper function used by Draw(). Iterates over the pin geometries, drawing connections between them
- L253 _protected prototype_ `void CheckSplineConnectionOverlapWithCursor( const FVector2f& AbsoluteCursorPosition, const FVector2f& Start, const FVector2f& End, const FConnectionParams& Params, FGraphSplineOverlapResult& InOutOverlapResults, bool* bOutSliceLineIntersectsSpline = nullptr ) const;` — Checks if the given spline overlaps with the Cursor. @param AbsoluteCursorPosition Absolute position of the cursor @param Start Start point of the Spline @param End End point of the Spline @param Params Parameters of the Spline @param InOutOverlapResults Will hold the overlap result. Pass in previous results used to find the closest spline to the cursor @param bOutSliceLineIntersectsSpline If not null, will return true if the SliceLine intersects this spline
- L272 _protected member_ `TArray<FSimpleConnectionData> LastConnections;` — Keeps track of the last connections drawn to check if they would have changed on MouseMove
- L275 _private prototype_ `void DrawSplineWithArrow_DeprecationHelper(const UE::Slate::FDeprecateVector2DParameter& StartPoint, const UE::Slate::FDeprecateVector2DParameter& EndPoint, const FConnectionParams& Params);` — Note - these helpers are temporary, to be replaced entirely by the public API's 2f/float functions once the 2D/double deprecated functions can be removed
- L276 _private prototype_ `UE::Slate::FDeprecateVector2DResult ComputeSplineTangent_DeprecationHelper(const UE::Slate::FDeprecateVector2DParameter& Start, const UE::Slate::FDeprecateVector2DParameter& End) const;`
- L277 _private prototype_ `void DrawConnection_DeprecationHelper(int32 LayerId, const UE::Slate::FDeprecateVector2DParameter& Start, const UE::Slate::FDeprecateVector2DParameter& End, const FConnectionParams& Params);`
- L278 _private prototype_ `void DrawPreviewConnector_DeprecationHelper(const FGeometry& PinGeometry, const UE::Slate::FDeprecateVector2DParameter& StartPoint, const UE::Slate::FDeprecateVector2DParameter& EndPoint, UEdGraphPin* Pin);`

#### struct `FConnectionDrawingPolicy::FRelinkConnection`  
`struct FRelinkConnection`  
_L122-126_
- desc: Handle for a currently relinked connection.
- L124 _public member_ `UEdGraphPin* SourcePin;`
- L125 _public member_ `UEdGraphPin* TargetPin;`

#### struct `FConnectionDrawingPolicy::FSimpleConnectionData`  
`struct FSimpleConnectionData`  
_L262-270_
- L264 _public member_ `FGraphPinHandle StartPinHandle;`
- L265 _public member_ `FGraphPinHandle EndPinHandle;`
- L266 _public member_ `FVector2f StartPoint;`
- L267 _public member_ `FVector2f EndPoint;`
- L268 _public member_ `FConnectionParams Params;`
- L269 _public member_ `bool bAreConnectionsFaded = false;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API GRAPHEDITOR_API`
- L38 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogConnectionDrawingPolicy, Log, All);`
- L96 _macro_ `#define END_DEPRECATED_VIRTUAL_FN`

### `Source/Editor/GraphEditor/Public/DragAndDrop/GraphNodeDragDropOp.h` (Public)


#### class `FGraphNodeDragDropOp`  
`class FGraphNodeDragDropOp : public FDecoratedDragDropOp`  
_L9-29_
- inherits: `FDecoratedDragDropOp`
- L12 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGraphNodeDragDropOp, FDecoratedDragDropOp) UE_DEPRECATED(5.6, "Please use the delegate accepting FVector2f.") DECLARE_DELEGATE_FourParams( FOnPerformDropToGraph, TSharedPtr<FDragDropOperation>, UEdGraph*, const FVector2D&, const FVector2D&);`
- L16 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnPerformDropToGraphAtLocation, TSharedPtr<FDragDropOperation>, UEdGraph*, const FVector2f&, const FVector2f&);`
- L19 _public member_ `FOnPerformDropToGraph OnPerformDropToGraph;`
- L22 _public member_ `FOnPerformDropToGraphAtLocation OnPerformDropToGraphAtLocation = FOnPerformDropToGraphAtLocation::CreateLambda( [this](TSharedPtr<FDragDropOperation> InOperation, UEdGraph* InGraph, const FVector2f& InNodePos, const FVector2f& InScreenPos) { PRAGMA_DISABLE_DEPRECATION_WARNINGS OnPerformDropToGraph.ExecuteIfBound(InOperation, InGraph, FVector2D(InNodePos), FVector2D(InScreenPos)); PRAGMA_ENABLE_DEPRECATION_WARNINGS });`
- L24 _public function_ ``

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_FourParams( FOnPerformDropToGraph, TSharedPtr<FDragDropOperation>, UEdGraph*, const FVector2D&, const FVector2D&);`
- L16 _delegate_ `DECLARE_DELEGATE_FourParams(FOnPerformDropToGraphAtLocation, TSharedPtr<FDragDropOperation>, UEdGraph*, const FVector2f&, const FVector2f&);`

### `Source/Editor/GraphEditor/Public/EdGraphHandleTypes.h` (Public)


#### struct `FEdGraphNodeHandle`  
`struct FEdGraphNodeHandle`  
_L11-52_
- L15 _public function_ `FORCEINLINE FEdGraphNodeHandle(const UEdGraphNode* InNode) : Graph(InNode ? InNode->GetGraph() : nullptr) , NodeName(InNode ? InNode->GetFName() : NAME_None)`
- L25 _public function_ `FORCEINLINE bool operator ==(const FEdGraphNodeHandle& InOther) const`
- L31 _public function_ `FORCEINLINE const UEdGraph* GetGraph() const`
- L33 _public function_ `FORCEINLINE UEdGraphNode* GetNode() const`
- L50 _private member_ `TSoftObjectPtr<UEdGraph> Graph;`
- L51 _private member_ `FName NodeName;`

#### struct `FEdGraphPinHandle`  
`struct FEdGraphPinHandle : FEdGraphNodeHandle`  
_L54-143_
- inherits: `FEdGraphNodeHandle`
- L58 _public function_ `FORCEINLINE FEdGraphPinHandle(const UEdGraphPin* InPin) : FEdGraphNodeHandle(InPin ? InPin->GetOwningNode() : nullptr) , PinIndex(INDEX_NONE)`
- L94 _public function_ `FORCEINLINE bool operator ==(const FEdGraphPinHandle& InOther) const`
- L101 _public function_ `FORCEINLINE UEdGraphPin* GetPin() const`
- L139 _private member_ `FName PinName;`
- L140 _private member_ `EEdGraphPinDirection PinDirection;`
- L141 _private member_ `FGuid PersistentPinGuid;`
- L142 _private member_ `int32 PinIndex;`

#### Free symbols / members of external scopes

- L20 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FEdGraphNodeHandle& InHandle)`
- L38 _function_ `` (scope `FEdGraphNodeHandle::GetNode`)
- L79 _function_ `friend FORCEINLINE uint32 GetTypeHash(const FEdGraphPinHandle& InHandle)`
- L107 _function_ `` (scope `FEdGraphPinHandle::GetPin`)

### `Source/Editor/GraphEditor/Public/FindInGraph.h` (Public)


#### class `FFindInGraphResult`  
`class FFindInGraphResult`  
_L23-82_
- desc: Item that matched the search results
- L26 _public prototype_ `virtual ~FFindInGraphResult() = default;`
- L39 _public prototype_ `FFindInGraphResult(const FCreateParams& InCreateParams);` — Create a root (or only text) result
- L42 _public prototype_ `virtual void JumpToNode(TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit, const UEdGraphNode* InNode) const;` — By default NoOp, implement this to make your result jump to a node or node owning pin on click
- L45 _public prototype_ `virtual FReply OnClick(TWeakPtr<FAssetEditorToolkit> AssetEditorToolkit);` — Called when user clicks on the search item
- L48 _public prototype_ `virtual FText GetCategory() const;` — Get Category for this search result
- L51 _public prototype_ `virtual TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L54 _public prototype_ `virtual FString GetCommentText() const;` — Gets the comment on this node if any
- L57 _public prototype_ `virtual FString GetValueText() const;` — Gets the value of the pin if any
- L60 _public member_ `TArray<TSharedPtr<FFindInGraphResult>> Children;` — Any children listed under this category
- L63 _public member_ `TWeakPtr<FFindInGraphResult> Parent;` — Search result Parent
- L66 _public member_ `FString Value;` — The meta string that was stored in the asset registry for this item
- L69 _public member_ `int DuplicationIndex;` — The graph may have multiple instances of whatever we are looking for, this tells us which instance # we refer to
- L72 _public member_ `UClass* Class;` — The class this item refers to
- L75 _public member_ `FEdGraphPinReference Pin;` — The pin that this search result refers to
- L78 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to (if not by asset registry or UK2Node)
- L81 _public member_ `FString CommentText;` — Display text for comment information

#### struct `FFindInGraphResult::FCreateParams`  
`struct FCreateParams`  
_L28-36_
- L30 _public member_ `const FString& Value;`
- L31 _public member_ `TSharedPtr<FFindInGraphResult> Parent = nullptr;`
- L32 _public member_ `int DuplicationIndex = 0;`
- L33 _public member_ `UClass* Class = nullptr;`
- L34 _public member_ `UEdGraphPin* Pin = nullptr;`
- L35 _public member_ `UEdGraphNode* GraphNode = nullptr;`

#### class `SFindInGraph`  
`class SFindInGraph : public SCompoundWidget`  
_L86-164_
- inherits: `SCompoundWidget`
- desc: Widget for searching for items that are part of a UEdGraph
- L89 _public function_ `SLATE_BEGIN_ARGS(SFindInGraph)`
- L90 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FAssetEditorToolkit> InAssetEditorToolkit);`
- L95 _public prototype_ `virtual void FocusForUse();` — Focuses this widget's search box
- L98 _protected typedef_ `typedef TSharedPtr<FFindInGraphResult> FSearchResult;`
- L99 _protected typedef_ `typedef STreeView<FSearchResult> STreeViewType;`
- L102 _protected prototype_ `virtual TSharedPtr<FFindInGraphResult> MakeSearchResult(const FFindInGraphResult::FCreateParams& InParams);` — Override this to create the search result of your type
- L105 _protected prototype_ `virtual void OnSearchTextChanged(const FText& Text);` — Called when user changes the text they are searching for
- L108 _protected prototype_ `virtual void OnSearchTextCommitted(const FText& Text, ETextCommit::Type CommitType);` — Called when user changes commits text to the search box
- L111 _protected prototype_ `virtual void OnGetChildren(FSearchResult InItem, TArray<FSearchResult>& OutChildren);` — Get the children of a row
- L114 _protected prototype_ `virtual void OnTreeSelectionChanged(FSearchResult Item, ESelectInfo::Type SelectInfo);` — Called when user clicks on a new result
- L117 _protected prototype_ `virtual void OnTreeSelectionDoubleClick(FSearchResult Item);` — Called when user double clicks on a new result
- L120 _protected prototype_ `virtual TSharedRef<ITableRow> OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Called when a new row is being generated
- L123 _protected prototype_ `virtual void InitiateSearch();` — Begins the search based on the SearchValue
- L126 _protected prototype_ `virtual const UEdGraph* GetGraph();` — Get a graph corresponding to this editor, implement if you want to want to use the default graph node search
- L129 _protected prototype_ `virtual void MatchTokens(const TArray<FString>& Tokens);` — Find any results that contain all of the tokens
- L135 _protected prototype_ `virtual bool MatchTokensInNode(const UEdGraphNode* Node, const TArray<FString>& Tokens);` — Implement this if you have node-specific search behavior. IE: Casting into child types to compare tokens. @return true if all tokens are valid for this node, false otherwisee
- L138 _protected prototype_ `virtual void MatchTokensInGraph(const UEdGraph* Graph, const TArray<FString>& Tokens);` — Find any results that contain all of the tokens in provided graph and subgraphs
- L141 _protected prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& Tokens, const FString& ComparisonString);` — Determines if a string matches the search tokens
- L145 _protected member_ `TWeakPtr<FAssetEditorToolkit> AssetEditorToolkitPtr;` — Pointer back to the Material editor that owns us
- L148 _protected member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L151 _protected member_ `TSharedPtr<SSearchBox> SearchTextField;` — The search text box
- L154 _protected member_ `TArray<FSearchResult> ItemsFound;` — This buffer stores the currently displayed results
- L157 _protected member_ `FSearchResult RootSearchResult;` — we need to keep a handle on the root result, because it won't show up in the tree
- L160 _protected member_ `FText HighlightText;` — The string to highlight in the results
- L163 _protected member_ `FString SearchValue;` — The string to search for

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphActionNode.h` (Public)


#### struct `FGraphActionNode`  
`struct FGraphActionNode : TSharedFromThis<FGraphActionNode>`  
_L21-336_
- inherits: `TSharedFromThis<FGraphActionNode>`
- desc: Utility class for building menus of graph actions
- L28 _public prototype_ `FGraphActionNode(const FGraphActionNode& Node) = delete;` — We need to declare our copy constructors so that we can disable deprecation warnings around them for ClangEditor - when all of the deprecated members are deleted we can remove these:
- L29 _public prototype_ `FGraphActionNode& operator=(const FGraphActionNode& Node) = delete;`
- L30 _public prototype_ `FGraphActionNode(FGraphActionNode&& Node) = delete;`
- L31 _public prototype_ `FGraphActionNode& operator=(FGraphActionNode&& Node) = delete;`
- L32 _public prototype_ `~FGraphActionNode() = default;`
- L36 _public member_ `static const int32 INVALID_SECTION_ID = 0;`
- L39 _public member_ `int32 const SectionID;` — Identifies the named section that this node belongs to, if any (defaults to INVALID_SECTION_ID)
- L41 _public member_ `int32 const Grouping;` — Identifies the menu group that this node belongs to (defaults to zero)
- L43 _public member_ `TSharedPtr<FEdGraphSchemaAction> const Action;` — An action to execute when this node is picked from a menu
- L45 _public member_ `TArray< TSharedPtr<FEdGraphSchemaAction> > const Actions;` — `UE_DEPRECATED(5.5, "!! WARNING: This array is no longer populated!! FGraphActionNode::Actions array only functioned with a single Action (GetPrimaryAction), access via Action")`
- L48 _public member_ `TArray< TSharedPtr<FGraphActionNode> > Children;`
- L51 _public member_ `TMap< FString, TSharedPtr<FGraphActionNode> > CategoryNodes;` — Lookup table for category nodes, used to speed up menu construction
- L60 _public prototype_ `static TSharedPtr<FGraphActionNode> NewRootNode();` — Static allocator for a new root node (so external users have a starting point to build graph action trees from). @return A newly allocated root node (should not be displayed in the tree view).
- L72 _public prototype_ `TSharedPtr<FGraphActionNode> AddChild(const TSharedPtr<FEdGraphSchemaAction>& Action);` — Inserts a new action node (and any accompanying category nodes) based off the provided Action. NOTE: This does NOT insert the node in a sorted manner. Call SortChildren() separately or use AddChildAlphabetical @param  Action	An action that you want the node to execute when picked. @return The new action node.
- L75 _public prototype_ `TSharedPtr<FGraphActionNode> AddChild(FGraphActionListBuilderBase::ActionGroup const& ActionSet);` — `UE_DEPRECATED(5.5, "FGraphActionListBuilderBase::ActionGroup has been deprecated, use TSharedPtr<FEdGraphSchemaAction> directly")`
- L85 _public prototype_ `TSharedPtr<FGraphActionNode> AddChildAlphabetical(const TSharedPtr<FEdGraphSchemaAction>& Action);` — Inserts a new action node (and any required category nodes) based off the provided Action. Inserts in alphabetical order. @param  Action	An action that you want the node to execute when picked. @return The new action node.
- L88 _public prototype_ `TSharedPtr<FGraphActionNode> AddChildAlphabetical(FGraphActionListBuilderBase::ActionGroup const& ActionSet);` — `UE_DEPRECATED(5.5, "FGraphActionListBuilderBase::ActionGroup has been deprecated, use TSharedPtr<FEdGraphSchemaAction> directly")`
- L91 _public prototype_ `TSharedPtr<FGraphActionNode> AddSection(int32 Grouping, int32 InSectionID);`
- L100 _public prototype_ `void SortChildren(bool bAlphabetically = true, bool bRecursive = true);` — Sorts all child nodes by section, group, and type (additionally, can sort alphabetically if wanted). @param  bAlphabetically	Determines if we sort alphabetically on top of section/group/type. @param  bRecursive		Determines if we should sort all decendent nodes' children ass well.
- L105 _public function_ `TWeakPtr<FGraphActionNode> GetParentNode() const` — Returns a WeakPtr to the Parent Node
- L112 _public prototype_ `void GetAllNodes(TArray< TSharedPtr<FGraphActionNode> >& OutNodeArray) const;` — Recursively collects all child/grandchild/decendent nodes. @param  OutNodeArray	The array to fill out with decendent nodes.
- L119 _public prototype_ `void GetAllActionNodes(TArray<TSharedPtr<FGraphActionNode>>& OutNodeArray) const;` — Recursively collects all child/grandchild/decendent action nodes. @param  OutNodeArray	The array to fill out with decendent nodes.
- L127 _public prototype_ `void GetLeafNodes(TArray< TSharedPtr<FGraphActionNode> >& OutLeafArray) const;` — Recursively collects all decendent action/separator nodes (leaves out branching category-nodes). @param  OutLeafArray	The array to fill out with decendent leaf nodes.
- L130 _public prototype_ `int32 GetTotalLeafNodes() const;` — Returns the number of leaf nodes
- L138 _public prototype_ `void ExpandAllChildren(TSharedPtr< STreeView< TSharedPtr<FGraphActionNode> > > TreeView, bool bRecursive = true);` — Takes the tree view and expands its elements for each child. @param  TreeView		The tree responsible for visualizing this node hierarchy. @param  bRecursive	Determines if you want children/decendents to expand their children as well.
- L144 _public prototype_ `void ClearChildren();` — Clears all children (not recursively... the TSharedPtrs should clean up appropriately).
- L152 _public prototype_ `bool IsRootNode() const;` — Query to determine this node's type (there are five distinguishable node types: root, section heading, category, action, & group-divider). @return True if this is the type your queried about, otherwise false.
- L153 _public prototype_ `bool IsSectionHeadingNode() const;`
- L154 _public prototype_ `bool IsCategoryNode() const;`
- L155 _public prototype_ `bool IsActionNode() const;`
- L156 _public prototype_ `bool IsGroupDividerNode() const;`
- L164 _public prototype_ `bool IsSeparator() const;` — Determines if this node is a menu separator of some kind (either a "group-divider" or a "section heading"). @return True if this is a menu divider, otherwise false.
- L171 _public prototype_ `FText const& GetDisplayName() const;` — Retrieves this node's display name (for category and action nodes). The text string will be empty for separator and root nodes. @return The name to present this node with in the tree view (will be an empty text string if this is a separator node)
- L180 _public prototype_ `FText GetCategoryPath() const;` — Walks the node chain backwards, constructing a category path (delimited by '|' characters). This includes this node's category (if it is a category node). @return A category path string, denoting the category hierarchy up to this node.
- L187 _public prototype_ `bool HasValidAction() const;` — Checks to see if this node contains at least one valid action. @return True is the Actions array contains a valid entry, otherwise false.
- L195 _public prototype_ `TSharedPtr<FEdGraphSchemaAction> GetPrimaryAction() const;` — Looks through this node's Actions array, and returns the first valid action it finds. @return This node's first valid action (will be an empty pointer if this is not an action node).
- L204 _public function_ `FOnRenameRequestActionNode& OnRenameRequest()` — Accessor to the node's RenameRequestEvent (for binding purposes). Do not Execute() the delegate from this function, instead call BroadcastRenameRequest() on the node. @return The node's internal RenameRequestEvent.
- L212 _public prototype_ `bool BroadcastRenameRequest();` — Executes the node's RenameRequestEvent if it is bound. Otherwise, it will mark the node as having a pending rename request. @return True if the broadcast went through, false if the "pending rename request" flag was set.
- L222 _public prototype_ `bool IsRenameRequestPending() const;` — Sometimes a call to BroadcastRenameRequest() is made before the RenameRequestEvent has been bound. When that happens, this node is marked with a pending rename request. This method determines if that is the case for this node. @return True if a call to BroadcastRenameRequest() was made without a valid RenameRequestEvent.
- L225 _public prototype_ `int32 GetLinearizedIndex(TSharedPtr<FGraphActionNode> Node) const;` — Returns the 'linearized' index of the node, including category nodes, useful for getting displayed position
- L233 _private prototype_ `FGraphActionNode(int32 Grouping, int32 SectionID);` — @param  Grouping @param  SectionID
- L242 _private prototype_ `FGraphActionNode(const TSharedPtr<FEdGraphSchemaAction>& InAction, int32 InGrouping, int32 InSectionID);` — Constructor for action nodes. Private so that users go through AddChild(). @param  InAction @param  Grouping @param  SectionID
- L252 _private prototype_ `static TSharedPtr<FGraphActionNode> NewSectionHeadingNode(TWeakPtr<FGraphActionNode> Parent, int32 Grouping, int32 SectionID);` — @param  Parent @param  Grouping @param  SectionID @return
- L262 _private prototype_ `static TSharedPtr<FGraphActionNode> NewCategoryNode(FString const& Category, int32 Grouping, int32 SectionID);` — @param  Category @param  Grouping @param  SectionID @return
- L270 _private prototype_ `static TSharedPtr<FGraphActionNode> NewActionNode(TSharedPtr<FEdGraphSchemaAction> const& ActionNode);` — @param  ActionNode @return
- L279 _private prototype_ `static TSharedPtr<FGraphActionNode> NewGroupDividerNode(TWeakPtr<FGraphActionNode> Parent, int32 Grouping);` — @param  Parent @param  Grouping @return
- L289 _private prototype_ `void AddChildRecursively(const TArray<FString>& CategoryStack, int32 Idx, TSharedPtr<FGraphActionNode> NodeToAdd);` — Iterates the CategoryStack, adding category-nodes as needed. The last category is what the node will be inserted under. @param  CategoryStack	A list of categories denoting where to nest the new node (the first element is the highest category) @param  Idx				Current point in the category stack that we have iterated to @param  NodeToAdd		The node you want inserted.
- L299 _private prototype_ `TSharedPtr<FGraphActionNode> FindMatchingParent(FString const& ParentName, TSharedPtr<FGraphActionNode> NodeToAdd);` — Looks through this node's children to see if a there already exists a node matching one we'd have to spawn (to parent the supplied NodeToAdd). @param   ParentName	The name of the category NodeToAdd wants to nest under. @param   NodeToAdd	The node that we'll be adding to this child. @return  A child node matching the supplied parameters (will be empty if no match was found).
- L308 _private prototype_ `void InsertChild(TSharedPtr<FGraphActionNode> NodeToAdd);` — Adds the specified node directly to this node's Children array. Will create and insert separators if needed (if the node has a new group or section). @param  NodeToAdd The node you want inserted.
- L310 _private prototype_ `void AddChildGrouping(TSharedPtr<FGraphActionNode> ActionNode, TWeakPtr<FGraphActionNode> Parent, bool bInsertAlphabetically);`
- L311 _private prototype_ `void InsertChildAlphabetical(TSharedPtr<FGraphActionNode> NodeToAdd);`
- L314 _private prototype_ `int32 GetLinearizedIndex(TSharedPtr<FGraphActionNode> Node, int32& Iter) const;` — Recursive implementation helper for GetLinearizedIndex
- L317 _private member_ `FText DisplayText;` — The category or action name (depends on what type of node this is)
- L319 _private member_ `TWeakPtr<FGraphActionNode> ParentNode;` — The node that this is a direct child of (empty if this is a root node)
- L322 _private member_ `TSet<int32> ChildGroupings;` — Tracks what groups have already been added (so we can easily determine what group-dividers we need)
- L324 _private member_ `TSet<int32> ChildSections;` — Tracks what sections have already been added (so we can easily determine what heading we need)
- L327 _private member_ `bool bPendingRenameRequest;` — When the item is first created, a rename request may occur before everything is setup for it. This toggles to true in those cases
- L329 _private member_ `FOnRenameRequestActionNode RenameRequestEvent;` — Delegate to trigger when a rename was requested on this node
- L333 _private member_ `int32 InsertOrder;` — For sorting, when we don't alphabetically sort (so menu items don't jump around).
- L335 _private member_ `int32 TotalLeafs;` — Root entry only, counts the total leaf entries in this tree

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphDiffControl.h` (Public)


#### class `FGraphDiffControl`  
`class FGraphDiffControl`  
_L18-138_
- desc: Used to find differences between revisions of a graph.
- L114 _public prototype_ `static FNodeMatch FindNodeMatch(UEdGraph* OldGraph, UEdGraphNode* NewNode, TArray<FNodeMatch> const& PriorMatches);` — Looks through the supplied graph for a node that best matches the one specified. Sometimes (when diffing separate assets) there could be more than one possible match, so providing a list of already matched nodes helps us narrow it down (and prevents us from matching one node with multiple others). @param  OldGraph		The graph you want to search. @param  NewNode		The new node you want to match. @param  PriorMatches	Previous made matches to exclude from our search. @return A pair of nodes (including the supplied one) that best match each other (one may be nullptr if no match was found).
- L123 _public prototype_ `static bool IsNodeMatch(UEdGraphNode* Node1, UEdGraphNode* Node2, bool bExactOnly = false, TArray<FGraphDiffControl::FNodeMatch> const* Exclusions = nullptr);` — Returns true if the two Nodes are the same @param  Node1		First node to check @param  Node2		Second node @param  Exclusions	Previous made matches to exclude from our search.
- L134 _public prototype_ `static bool DiffGraphs(UEdGraph* const OldGraph, UEdGraph* const NewGraph, TArray<FDiffSingleResult>& DiffsOut);` — Looks for node differences between the two supplied graphs. Diffs will be returned in the context of "what has changed from OldGraph in NewGraph?" @param  OldGraph		The baseline graph to compare against. @param  NewGraph		The second graph to look for changes in. @param  DiffsOut		All the differences that were found between the two. @return True if any differences were found, false if both graphs are identical.
- L137 _public prototype_ `static FString GetGraphPath(UEdGraph* Graph);` — Computes an object path for a specific graph, relative to the blueprint/asset root

#### enum `FGraphDiffControl::EDiffMode`  
`enum class EDiffMode`  
_L22-28_
- desc: What kind of diff are we performing
- L25 _public enumerator_ `Additive` — An item present in 'RHS' but missing in 'LHS' has been added to the graph
- L27 _public enumerator_ `Subtractive` — An item present in 'RHS' but missing in 'LHS' has been removed from the graph

#### struct `FGraphDiffControl::EDiffFlags`  
`struct EDiffFlags`  
_L31-48_
- desc: Flags controlling while operations should be included in the diff

#### enum `FGraphDiffControl::EDiffFlags::Type`  
`enum Type`  
_L33-47_
- L36 _public enumerator_ `NodeExistance = (1<<0)` — Include node existence (adds and removes) in the diff
- L38 _public enumerator_ `NodeMovement = (1<<1)` — Include node movement in the diff
- L40 _public enumerator_ `NodeComment = (1<<2)` — Include the node comment in the diff
- L42 _public enumerator_ `NodePins = (1<<3)` — Include the node pin changes in the diff
- L44 _public enumerator_ `NodeSpecificDiffs = (1<<4)` — Include any node specific items in the diff
- L46 _public enumerator_ `All = NodeExistance | NodeMovement | NodeComment | NodePins | NodeSpecificDiffs` — Include all the things

#### struct `FGraphDiffControl::FNodeDiffContext`  
`struct FNodeDiffContext`  
_L51-72_
- desc: A struct holding the context data for a node diff
- L53 _public function_ `FNodeDiffContext() : DiffMode(EDiffMode::Additive) , DiffFlags(EDiffFlags::All) , NodeTypeDisplayName() , bIsRootNode(true)`
- L62 _public member_ `EDiffMode DiffMode;` — What kind of diff are we performing?
- L65 _public member_ `EDiffFlags::Type DiffFlags;` — What items should be included in the diff?
- L68 _public member_ `FText NodeTypeDisplayName;` — Display name used when showing the node type in messages
- L71 _public member_ `bool bIsRootNode;` — True if this node is a root node in the graph, false if this node is nested within another node

#### struct `FGraphDiffControl::FNodeMatch`  
`struct FNodeMatch`  
_L75-101_
- desc: A struct to represent a found pair of nodes that match each other (for comparisons sake)
- L77 _public function_ `FNodeMatch() : NewNode(nullptr) , OldNode(nullptr)`
- L82 _public member_ `UEdGraphNode* NewNode;`
- L83 _public member_ `UEdGraphNode* OldNode;`
- L93 _public prototype_ `bool Diff(const FNodeDiffContext& DiffContext, TArray<FDiffSingleResult>* DiffsResultsOut = nullptr) const;` — Looks at the two node members and compares them to see if there are any differences. If one of the nodes is nullptr, then this will return true with a EDiffType::NODE_ADDED result. @param  DiffsArrayOut	If supplied, this will be filled out with all the differences that were found. @return True if there were differences found, false if the two nodes are identical.
- L94 _public prototype_ `bool Diff(const FNodeDiffContext& DiffContext, FDiffResults& DiffsOut) const;`
- L100 _public prototype_ `bool IsValid() const;` — Checks to see if this is a valid match. @return False if NewNode or OldNode is nullptr, true if both are valid.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphEditorActions.h` (Public)


#### class `FGraphEditorCommandsImpl`  
`class FGraphEditorCommandsImpl : public TCommands<FGraphEditorCommandsImpl>`  
_L22-166_
- inherits: `TCommands<FGraphEditorCommandsImpl>`
- L26 _public function_ `FGraphEditorCommandsImpl() : TCommands<FGraphEditorCommandsImpl>( TEXT("GraphEditor"), NSLOCTEXT("Contexts", "GraphEditor", "Graph Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L31 _public prototype_ `virtual ~FGraphEditorCommandsImpl() = default;`
- L33 _public prototype_ `virtual void RegisterCommands() override;`
- L35 _public member_ `TSharedPtr< FUICommandInfo > ReconstructNodes;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > BreakNodeLinks;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > AddExecutionPin;` — Execution sequence specific commands
- L40 _public member_ `TSharedPtr< FUICommandInfo > InsertExecutionPinBefore;`
- L41 _public member_ `TSharedPtr< FUICommandInfo > InsertExecutionPinAfter;`
- L42 _public member_ `TSharedPtr< FUICommandInfo > RemoveExecutionPin;`
- L45 _public member_ `TSharedPtr< FUICommandInfo > RemoveThisStructVarPin;` — SetFieldsInStruct specific commands
- L46 _public member_ `TSharedPtr< FUICommandInfo > RemoveOtherStructVarPins;`
- L47 _public member_ `TSharedPtr< FUICommandInfo > RestoreAllStructVarPins;`
- L50 _public member_ `TSharedPtr< FUICommandInfo > AddOptionPin;` — Select node specific commands
- L51 _public member_ `TSharedPtr< FUICommandInfo > RemoveOptionPin;`
- L52 _public member_ `TSharedPtr< FUICommandInfo > ChangePinType;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > DeleteAndReconnectNodes;`
- L56 _public member_ `TSharedPtr< FUICommandInfo > ShowAllPins;` — Pin visibility modes
- L57 _public member_ `TSharedPtr< FUICommandInfo > HideNoConnectionPins;`
- L58 _public member_ `TSharedPtr< FUICommandInfo > HideNoConnectionNoDefaultPins;`
- L61 _public member_ `TSharedPtr< FUICommandInfo > AddParentNode;` — Event / Function Entry commands
- L64 _public member_ `TSharedPtr< FUICommandInfo > CreateMatchingFunction;` — CallFunction commands
- L67 _public member_ `TSharedPtr< FUICommandInfo > RemoveBreakpoint;` — Debugging commands
- L68 _public member_ `TSharedPtr< FUICommandInfo > AddBreakpoint;`
- L69 _public member_ `TSharedPtr< FUICommandInfo > EnableBreakpoint;`
- L70 _public member_ `TSharedPtr< FUICommandInfo > DisableBreakpoint;`
- L71 _public member_ `TSharedPtr< FUICommandInfo > ToggleBreakpoint;`
- L74 _public member_ `TSharedPtr< FUICommandInfo > CollapseNodes;` — Encapsulation commands
- L75 _public member_ `TSharedPtr< FUICommandInfo > PromoteSelectionToFunction;`
- L76 _public member_ `TSharedPtr< FUICommandInfo > PromoteSelectionToMacro;`
- L77 _public member_ `TSharedPtr< FUICommandInfo > ExpandNodes;`
- L78 _public member_ `TSharedPtr< FUICommandInfo > CollapseSelectionToFunction;`
- L79 _public member_ `TSharedPtr< FUICommandInfo > CollapseSelectionToMacro;`
- L80 _public member_ `TSharedPtr< FUICommandInfo > ConvertFunctionToEvent;`
- L81 _public member_ `TSharedPtr< FUICommandInfo > ConvertEventToFunction;`
- L84 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesTop;` — Alignment commands
- L85 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesMiddle;`
- L86 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesBottom;`
- L88 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesLeft;`
- L89 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesCenter;`
- L90 _public member_ `TSharedPtr< FUICommandInfo > AlignNodesRight;`
- L92 _public member_ `TSharedPtr< FUICommandInfo > StraightenConnections;`
- L94 _public member_ `TSharedPtr< FUICommandInfo > DistributeNodesHorizontally;`
- L95 _public member_ `TSharedPtr< FUICommandInfo > DistributeNodesVertically;`
- L97 _public member_ `TSharedPtr< FUICommandInfo > StackNodesHorizontally;`
- L98 _public member_ `TSharedPtr< FUICommandInfo > StackNodesVertically;`
- L101 _public member_ `TSharedPtr< FUICommandInfo > EnableNodes;` — Enable/disable commands
- L102 _public member_ `TSharedPtr< FUICommandInfo > DisableNodes;`
- L103 _public member_ `TSharedPtr< FUICommandInfo > EnableNodes_Always;`
- L104 _public member_ `TSharedPtr< FUICommandInfo > EnableNodes_DevelopmentOnly;`
- L107 _public member_ `TSharedPtr< FUICommandInfo > SelectReferenceInLevel;`
- L108 _public member_ `TSharedPtr< FUICommandInfo > AssignReferencedActor;`
- L111 _public member_ `TSharedPtr< FUICommandInfo > FindReferences;` — Find references
- L112 _public function_ `TSharedPtr< FUICommandInfo > GetFindReferences() const`
- L115 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByNameLocal;` — Find references options that appear by context like for functions and variables
- L116 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByNameGlobal;`
- L117 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByClassMemberLocal;`
- L118 _public member_ `TSharedPtr< FUICommandInfo > FindReferencesByClassMemberGlobal;`
- L120 _public member_ `TSharedPtr< FUICommandInfo > FindAndReplaceReferences;`
- L123 _public member_ `TSharedPtr< FUICommandInfo > GoToDefinition;` — Jumps to the definition of the selected node (or otherwise focuses something interesting about that node, e.g., the inner graph for a collapsed graph)
- L126 _public member_ `TSharedPtr< FUICommandInfo > OpenInNewTab;` — Opens collapsed graphs, functions or macros in a new tab
- L129 _public member_ `TSharedPtr< FUICommandInfo > BreakThisLink;` — Pin-specific actions
- L130 _public member_ `TSharedPtr< FUICommandInfo > BreakPinLinks;`
- L131 _public member_ `TSharedPtr< FUICommandInfo > PromoteToVariable;`
- L132 _public member_ `TSharedPtr< FUICommandInfo > PromoteToLocalVariable;`
- L133 _public member_ `TSharedPtr< FUICommandInfo > SplitStructPin;`
- L134 _public member_ `TSharedPtr< FUICommandInfo > RecombineStructPin;`
- L135 _public member_ `TSharedPtr< FUICommandInfo > StartWatchingPin;`
- L136 _public member_ `TSharedPtr< FUICommandInfo > StopWatchingPin;`
- L137 _public member_ `TSharedPtr< FUICommandInfo > ResetPinToDefaultValue;`
- L138 _public member_ `TSharedPtr< FUICommandInfo > SelectAllInputNodes;`
- L139 _public member_ `TSharedPtr< FUICommandInfo > SelectAllOutputNodes;`
- L142 _public member_ `TSharedPtr< FUICommandInfo > CreateComment;` — create a comment node
- L145 _public member_ `TSharedPtr< FUICommandInfo > CreateCustomEvent;` — Create a custom event node
- L148 _public member_ `TSharedPtr< FUICommandInfo > ZoomIn;` — Zoom in and out on the graph editor
- L149 _public member_ `TSharedPtr< FUICommandInfo > ZoomOut;`
- L152 _public member_ `TSharedPtr< FUICommandInfo > GoToDocumentation;` — Go to node documentation
- L155 _public member_ `TSharedPtr< FUICommandInfo > SummonCreateNodeMenu;` — Open the context menu at last known mouse position
- L164 _public member_ `TArray< FQuickJumpCommandInfo > QuickJumpCommands;`
- L165 _public member_ `TSharedPtr< FUICommandInfo > ClearAllQuickJumps;`

#### struct `FGraphEditorCommandsImpl::FQuickJumpCommandInfo`  
`struct FQuickJumpCommandInfo`  
_L158-163_
- desc: Quick jump commands
- L160 _public member_ `TSharedPtr< FUICommandInfo > QuickJump;`
- L161 _public member_ `TSharedPtr< FUICommandInfo > SetQuickJump;`
- L162 _public member_ `TSharedPtr< FUICommandInfo > ClearQuickJump;`

#### class `FGraphEditorCommands`  
`class FGraphEditorCommands`  
_L168-179_
- L171 _public prototype_ `static void Register();`
- L173 _public prototype_ `static const FGraphEditorCommandsImpl& Get();`
- L176 _public prototype_ `static void BuildFindReferencesMenu(FMenuBuilder& MenuBuilder);` — Build "Find References" submenu when a context allows for it
- L178 _public prototype_ `static void Unregister();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphEditorDragDropAction.h` (Public)


#### class `FGraphEditorDragDropAction`  
`class FGraphEditorDragDropAction : public FDragDropOperation`  
_L31-98_
- inherits: `FDragDropOperation`
- desc: Base class for drag-drop actions that pass into the graph editor and perform an action when dropped
- L34 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGraphEditorDragDropAction, FDragDropOperation) FGraphEditorDragDropAction();`
- L38 _public prototype_ `void SetHoveredPin(UEdGraphPin* InPin);`
- L39 _public prototype_ `void SetHoveredNode(const TSharedPtr<SGraphNode>& InNode);`
- L40 _public prototype_ `void SetHoveredNode(UEdGraphNode* InNode);`
- L41 _public prototype_ `void SetHoveredGraph(const TSharedPtr<SGraphPanel>& InGraph);`
- L42 _public prototype_ `void SetHoveredCategoryName(const FText& InHoverCategoryName);`
- L43 _public prototype_ `void SetHoveredAction(TSharedPtr<struct FEdGraphSchemaAction> Action);`
- L44 _public function_ `void SetDropTargetValid( bool bValid )`
- L47 _public function_ `virtual void HoverTargetChanged()` — Interface to override
- L49 _public prototype_ `virtual FReply DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L50 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition);`
- L52 _public prototype_ `virtual FReply DroppedOnNode(FVector2D ScreenPosition, FVector2D GraphPosition) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L53 _public prototype_ `virtual FReply DroppedOnNode(const FVector2f& ScreenPosition, const FVector2f& GraphPosition);`
- L55 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, FVector2D ScreenPosition, FVector2D GraphPosition, UEdGraph& Graph) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")`
- L56 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph);`
- L57 _public function_ `virtual FReply DroppedOnAction(TSharedRef<struct FEdGraphSchemaAction> Action)`
- L58 _public function_ `virtual FReply DroppedOnCategory(FText Category)`
- L61 _public function_ `virtual bool IsSupportedBySchema(const UEdGraphSchema* Schema) const`
- L63 _public prototype_ `bool HasFeedbackMessage();`
- L64 _public prototype_ `void SetFeedbackMessage(const TSharedPtr<SWidget>& Message);`
- L65 _public prototype_ `void SetSimpleFeedbackMessage(const FSlateBrush* Icon, const FSlateColor& IconColor, const FText& Message, const FSlateBrush* SecondaryIcon = nullptr, const FSlateColor SecondaryColor = FSlateColor());`
- L68 _protected prototype_ `UEdGraphPin* GetHoveredPin() const;`
- L69 _protected prototype_ `UEdGraphNode* GetHoveredNode() const;`
- L70 _protected prototype_ `UEdGraph* GetHoveredGraph() const;`
- L73 _protected prototype_ `virtual void Construct() override;` — Constructs the window and widget if applicable
- L75 _protected prototype_ `virtual EVisibility GetIconVisible() const;`
- L76 _protected prototype_ `virtual EVisibility GetErrorIconVisible() const;`
- L80 _private member_ `FEdGraphPinReference HoveredPin;` — The pin that the drag action is currently hovering over
- L83 _private member_ `TWeakObjectPtr<UEdGraphNode> HoveredNode;` — The node that the drag action is currently hovering over
- L86 _private member_ `TSharedPtr<SGraphPanel> HoveredGraph;` — The graph that the drag action is currently hovering over
- L91 _protected member_ `FText HoveredCategoryName;` — Name of category we are hovering over
- L94 _protected member_ `TWeakPtr<struct FEdGraphSchemaAction> HoveredAction;` — Action we are hovering over
- L97 _protected member_ `bool bDropTargetValid;` — drop target status

#### class `FGraphSchemaActionDragDropAction`  
`class FGraphSchemaActionDragDropAction : public FGraphEditorDragDropAction`  
_L101-126_
- inherits: `FGraphEditorDragDropAction`
- desc: Drag-drop action where an FEdGraphSchemaAction should be performed when dropped
- L105 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGraphSchemaActionDragDropAction, FGraphEditorDragDropAction)`
- L109 _public prototype_ `virtual FReply DroppedOnPanel(const TSharedRef< SWidget >& Panel, const FVector2f& ScreenPosition, const FVector2f& GraphPosition, UEdGraph& Graph) override;`
- L110 _public prototype_ `virtual FReply DroppedOnPin(const FVector2f& ScreenPosition, const FVector2f& GraphPosition) override;`
- L113 _public function_ `static TSharedRef<FGraphSchemaActionDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InActionNode )`
- L122 _protected prototype_ `virtual void GetDefaultStatusSymbol(const FSlateBrush*& PrimaryBrushOut, FSlateColor& IconColorOut, FSlateBrush const*& SecondaryBrushOut, FSlateColor& SecondaryColorOut) const;`
- L125 _protected member_ `TSharedPtr<FEdGraphSchemaAction> SourceAction;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphEditorModule.h` (Public)


#### class `FGraphEditorModule`  
`class FGraphEditorModule : public IModuleInterface`  
_L26-68_
- inherits: `IModuleInterface`
- desc: Graph editor public interface
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal_FiveParams( TSharedRef<FExtender>, FGraphEditorMenuExtender_SelectedNode, const TSharedRef<FUICommandList>, const UEdGraph*, const UEdGraphNode*, const UEdGraphPin*, bool);`
- L36 _public function_ `virtual TArray<FGraphEditorMenuExtender_SelectedNode>& GetAllGraphEditorContextMenuExtender()`
- L46 _private prototype_ `virtual TSharedRef<SGraphEditor> PRIVATE_MakeGraphEditor( const TSharedPtr<FUICommandList>& InAdditionalCommands, const TAttribute<bool>& InIsEditable, const TAttribute<bool>& InDisplayAsReadOnly, const TAttribute<bool>& InIsEmpty, TAttribute<FGraphAppearanceInfo> Appearance, TSharedPtr<SWidget> InTitleBar, UEdGraph* InGraphToEdit, SGraphEditor::FGraphEditorEvents GraphEvents, bool InAutoExpandActionMenu, TSharedPtr<TArray<FDiffSingleResult>> DiffResults, TAttribute<int32> FocusedDiffResult, FSimpleDelegate InOnNavigateHistoryBack, FSimpleDelegate InOnNavigateHistoryForward, TAttribute<bool> ShowGraphStateOverlay, TAttribute<bool> AllowConnectionSlicing, FOnGraphEditorTickDelegate InOnTickDelegate, bool bGraphSupportsInvalidation);` — DO NOT CALL THIS METHOD. Use SNew(SGraphEditor) to make instances of SGraphEditor. @return A GraphEditor implementation.
- L67 _private member_ `TArray<FGraphEditorMenuExtender_SelectedNode> GraphEditorContextMenuExtender;` — All extender delegates for the graph menus

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal_FiveParams( TSharedRef<FExtender>, FGraphEditorMenuExtender_SelectedNode, const TSharedRef<FUICommandList>, const UEdGraph*, const UEdGraphNode*, const UEdGraphPin*, bool);`

### `Source/Editor/GraphEditor/Public/GraphEditorSettings.h` (Public)


#### enum `EGraphPanningMouseButton`  
`enum class EGraphPanningMouseButton : uint8`  
_L22-27_
- reflection: `UENUM()`
- L24 _public enumerator_ `Right UMETA(DisplayName = "Right")`
- L25 _public enumerator_ `Middle UMETA(DisplayName = "Middle")`
- L26 _public enumerator_ `Both UMETA(DisplayName = "Right or Middle")`

#### class `UGraphEditorSettings`  
`class UGraphEditorSettings : public UObject`  
_L35-373_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Implements settings for the graph editor.
- L43 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L51 _public member_ `TEnumAsByte<EBlueprintPinStyleType> DataPinStyle;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle)` — The visual styling to use for graph editor pins (in Blueprints, materials, etc...)
- L55 _public member_ `EGraphPanningMouseButton PanningMouseButton;` — `UPROPERTY(config, EditAnywhere, Category = GeneralStyle)` — Switch between using the right and middle mouse button for panning (defaults to right)
- L59 _public member_ `bool bUseHighPrecisionMouseMovement;` — `UPROPERTY(config, EditAnywhere, Category = GeneralStyle)` — Whether to use high precision mouse movement for more accurate mouse movement without mouse ballistics (defaults to true)
- L63 _public member_ `bool bUseInterpolationWithManualPanning;` — `UPROPERTY(config, EditAnywhere, Category = GeneralStyle)` — Whether to interpolate movement when manually panning a graph for smoother movement (defaults to false)
- L67 _public member_ `float PaddingAbovePin;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle, AdvancedDisplay)` — The amount of padding above a pin (defaults to 4)
- L71 _public member_ `float PaddingBelowPin;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle, AdvancedDisplay)` — The amount of padding below a pin (defaults to 4)
- L75 _public member_ `float PaddingRightOfInput;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle, AdvancedDisplay)` — The amount of horizontal padding towards the center of a node on an input pin (defaults to 10)
- L79 _public member_ `float PaddingLeftOfOutput;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle, AdvancedDisplay)` — The amount of horizontal padding towards the center of a node on an output pin (defaults to 10)
- L83 _public member_ `float PaddingTowardsNodeEdge;` — `UPROPERTY(config, EditAnywhere, Category=GeneralStyle, AdvancedDisplay)` — The amount of padding towards the node edge (defaults to 10, can be negative to make pins overlap or stick out of a node
- L86 _public prototype_ `FMargin GetInputPinPadding() const;` — Returns the padding to use for an input pin on a graph node
- L89 _public prototype_ `FMargin GetOutputPinPadding() const;` — Returns the padding to use for an output pin on a graph node
- L92 _public prototype_ `FMargin GetNonPinNodeBodyPadding() const;` — Returns the padding to use for a node region that won't contain a pin
- L95 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetShadowDeltaSize() const;` — Returns the size adjustment from node render geometry to shadow render geometry
- L101 _public member_ `bool bTreatSplinesLikePins;` — `UPROPERTY(EditAnywhere, config, Category=Splines)` — If enabled, allows splines to be Alt+Clicked to break them or Ctrl+Dragged to move them as if these actions were taking place on the associated pin.
- L105 _public member_ `float SplineHoverTolerance;` — `UPROPERTY(EditAnywhere, config, Category=Splines, meta=(EditCondition=bTreatSplinesLikePins))` — The distance threshold controlling how close the mouse has to be to the spline in order to trigger a hover response
- L109 _public member_ `float SplineCloseTolerance;` — `UPROPERTY(EditAnywhere, config, Category = Splines, meta = (EditCondition = bTreatSplinesLikePins))` — The additional distance around the spline to count as close, preventing other actions if the user just misses the spline when clicking
- L113 _public member_ `float ForwardSplineHorizontalDeltaRange;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The maximum value to clamp the absolute value of the horizontal distance between endpoints when calculating tangents (when the wire is moving forward)
- L117 _public member_ `float ForwardSplineVerticalDeltaRange;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The maximum value to clamp the absolute value of the vertical distance between endpoints when calculating tangents (when the wire is moving forward)
- L121 _public member_ `FDeprecateSlateVector2D ForwardSplineTangentFromHorizontalDelta;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The amount that the horizontal delta affects the generated tangent handle of splines (when the wire is moving forward)
- L125 _public member_ `FDeprecateSlateVector2D ForwardSplineTangentFromVerticalDelta;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The amount that the vertical delta affects the generated tangent handle of splines (when the wire is moving forward)
- L129 _public member_ `float BackwardSplineHorizontalDeltaRange;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The maximum value to clamp the absolute value of the horizontal distance between endpoints when calculating tangents (when the wire is moving backwards)
- L133 _public member_ `float BackwardSplineVerticalDeltaRange;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The maximum value to clamp the absolute value of the vertical distance between endpoints when calculating tangents (when the wire is moving backwards)
- L137 _public member_ `FDeprecateSlateVector2D BackwardSplineTangentFromHorizontalDelta;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The amount that the horizontal delta affects the generated tangent handle of splines (when the wire is moving backwards)
- L141 _public member_ `FDeprecateSlateVector2D BackwardSplineTangentFromVerticalDelta;` — `UPROPERTY(config, EditAnywhere, Category=Splines, AdvancedDisplay)` — The amount that the vertical delta affects the generated tangent handle of splines (when the wire is moving backwards)
- L144 _public prototype_ `UE::Slate::FDeprecateVector2DResult ComputeSplineTangent(const UE::Slate::FDeprecateVector2DParameter& Start, const UE::Slate::FDeprecateVector2DParameter& End) const;` — Compute a tangent given the start and end points of the spline
- L150 _public member_ `FLinearColor DefaultPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — The default color is used only for types not specifically defined below.  Generally if it's seen, it means another type needs to be defined so that the wire in question can have an appropriate color.
- L154 _public member_ `FLinearColor ExecutionPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Execution pin type color
- L158 _public member_ `FLinearColor BooleanPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Boolean pin type color
- L162 _public member_ `FLinearColor BytePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Byte pin type color
- L166 _public member_ `FLinearColor ClassPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Class pin type color
- L170 _public member_ `FLinearColor IntPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Integer pin type color
- L174 _public member_ `FLinearColor Int64PinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Integer64 pin type color
- L178 _public member_ `FLinearColor FloatPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Floating-point pin type color
- L182 _public member_ `FLinearColor DoublePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Double pin type color
- L186 _public member_ `FLinearColor RealPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Real pin type color
- L190 _public member_ `FLinearColor NamePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Name pin type color
- L194 _public member_ `FLinearColor SoftObjectPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Asset pin type color
- L198 _public member_ `FLinearColor SoftClassPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Asset Class pin type color
- L202 _public member_ `FLinearColor DelegatePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Delegate pin type color
- L206 _public member_ `FLinearColor ObjectPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Object pin type color
- L210 _public member_ `FLinearColor InterfacePinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Interface pin type color
- L214 _public member_ `FLinearColor StringPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — String pin type color
- L218 _public member_ `FLinearColor TextPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Text pin type color
- L222 _public member_ `FLinearColor StructPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Struct pin type color
- L226 _public member_ `FLinearColor WildcardPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Wildcard pin type color
- L230 _public member_ `FLinearColor VectorPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Vector pin type color
- L234 _public member_ `FLinearColor RotatorPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Rotator pin type color
- L238 _public member_ `FLinearColor TransformPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Transform pin type color
- L242 _public member_ `FLinearColor IndexPinTypeColor;` — `UPROPERTY(EditAnywhere, config, Category=PinColors)` — Index pin type color
- L248 _public member_ `FLinearColor EventNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Event node title color
- L252 _public member_ `FLinearColor FunctionCallNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — CallFunction node title color
- L256 _public member_ `FLinearColor PureFunctionCallNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Pure function call node title color
- L260 _public member_ `FLinearColor ParentFunctionCallNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Parent class function call node title color
- L264 _public member_ `FLinearColor FunctionTerminatorNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Function Terminator node title color
- L268 _public member_ `FLinearColor ExecBranchNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Exec Branch node title color
- L272 _public member_ `FLinearColor ExecSequenceNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Exec Sequence node title color
- L276 _public member_ `FLinearColor ResultNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Result node title color
- L280 _public member_ `FLinearColor DefaultCommentNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category=NodeTitleColors)` — Default Comment node title color
- L284 _public member_ `FLinearColor PreviewNodeTitleColor;` — `UPROPERTY(EditAnywhere, config, Category = NodeTitleColors)` — Preview node title color
- L288 _public member_ `FLinearColor SliceLineColor;` — `UPROPERTY(EditAnywhere, config, Category=Slicing)` — The color of the line shown while slicing connections
- L292 _public member_ `float SliceLineDashLength;` — `UPROPERTY(EditAnywhere, config, Category=Slicing)` — The length of each dash in the slice line
- L296 _public member_ `float SliceLineThickness;` — `UPROPERTY(EditAnywhere, config, Category=Slicing)` — The visual thickness of the slice line, does not affect collision
- L301 _public member_ `float DefaultDataWireThickness;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)` — The thickness of a data wire
- L305 _public member_ `float DefaultExecutionWireThickness;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)` — The thickness of an execution wire when not debugging
- L309 _public member_ `FLinearColor TraceAttackColor;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)` — The color to display execution wires that were just executed
- L312 _public member_ `float TraceAttackWireThickness;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)`
- L316 _public member_ `float TraceAttackHoldPeriod;` — `UPROPERTY()` — How long is the attack color fully visible
- L320 _public member_ `float TraceDecayPeriod;` — `UPROPERTY()` — How long does it take to fade from the attack to the sustain color
- L323 _public member_ `float TraceDecayExponent;` — `UPROPERTY()`
- L326 _public member_ `FLinearColor TraceSustainColor;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)`
- L329 _public member_ `float TraceSustainWireThickness;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)`
- L333 _public member_ `float TraceSustainHoldPeriod;` — `UPROPERTY()` — How long is the sustain color fully visible
- L337 _public member_ `FLinearColor TraceReleaseColor;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)` — The color to fade to for execution wires on release
- L341 _public member_ `float TraceReleaseWireThickness;` — `UPROPERTY(EditAnywhere, config, Category=Tracing)` — The thickness to drop down to during release / for unexecuted wires when debugging
- L345 _public member_ `float TraceReleasePeriod;` — `UPROPERTY()` — How long does it take to fade from the sustain to the release color
- L348 _public member_ `float TraceReleaseExponent;` — `UPROPERTY()`
- L352 _public member_ `float TracePositionBonusPeriod;` — `UPROPERTY()` — How much of a bonus does an exec get for being near the top of the trace stack, and how does that fall off with position?
- L355 _public member_ `float TracePositionExponent;` — `UPROPERTY()`
- L360 _public member_ `float PaddingAutoCollateIncrement;` — `UPROPERTY(config, EditAnywhere, Category=ContextMenu)` — The amount of padding to add in order to auto collate multiple created nodes when using tab context menu (defaults to 20)
- L364 _public member_ `bool bOpenCreateMenuOnBlankGraphAreas;` — `UPROPERTY(config, EditAnywhere, Category=ContextMenu)` — If a key press (default Tab) should open the create node context menu when the mouse is on top of blank areas of the graph (defaults to true)
- L368 _public member_ `TEnumAsByte<ECommentBoxMode::Type> DefaultCommentNodeMoveMode;` — `UPROPERTY(EditAnywhere, config, Category = CommentNodes)` — Whether a comment node should move any fully enclosed nodes around when it is moved
- L372 _public member_ `bool bShowCommentBubbleWhenZoomedOut;` — `UPROPERTY(EditAnywhere, config, Category = CommentNodes)` — Whether to show a zoom-invariant comment bubble when zoomed out (making the comment node's text readable at any distance)

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/GraphSplineOverlapResult.h` (Public)


#### struct `FGraphSplineOverlapResult`  
`struct FGraphSplineOverlapResult`  
_L13-95_
- L16 _public function_ `FGraphSplineOverlapResult(bool InCloseToSpline = false) : Pin1Handle(nullptr) , Pin2Handle(nullptr) , BestPinHandle(nullptr) , Pin1(nullptr) , Pin2(nullptr) , DistanceSquared(FLT_MAX) , DistanceSquaredToPin1(FLT_MAX) , DistanceSquaredToPin2(FLT_MAX) , bCloseToSpline(InCloseToSpline)`
- L29 _public function_ `FGraphSplineOverlapResult(UEdGraphPin* InPin1, UEdGraphPin* InPin2, float InDistanceSquared, float InDistanceSquaredToPin1, float InDistanceSquaredToPin2, bool InCloseToSpline) : Pin1Handle(InPin1) , Pin2Handle(InPin2) , BestPinHandle(nullptr) , Pin1(InPin1) , Pin2(InPin2) , DistanceSquared(InDistanceSquared) , DistanceSquaredToPin1(InDistanceSquaredToPin1) , DistanceSquaredToPin2(InDistanceSquaredToPin2) , bCloseToSpline(InCloseToSpline)`
- L42 _public function_ `bool IsValid() const`
- L47 _public prototype_ `void ComputeBestPin();`
- L49 _public function_ `float GetDistanceSquared() const`
- L54 _public function_ `bool GetCloseToSpline() const`
- L59 _public function_ `void SetCloseToSpline(bool InCloseToSpline)`
- L64 _public function_ `TSharedPtr<class SGraphPin> GetBestPinWidget(const class SGraphPanel& InGraphPanel) const`
- L74 _public function_ `FGraphPinHandle GetBestPinHandle() const`
- L79 _public function_ `FGraphPinHandle GetPin1Handle() const`
- L80 _public function_ `FGraphPinHandle GetPin2Handle() const`
- L82 _public prototype_ `bool GetPins(const class SGraphPanel& InGraphPanel, UEdGraphPin*& OutPin1, UEdGraphPin*& OutPin2) const;`
- L83 _public prototype_ `void GetPinWidgets(const class SGraphPanel& InGraphPanel, TSharedPtr<class SGraphPin>& OutPin1, TSharedPtr<class SGraphPin>& OutPin2) const;`
- L86 _protected member_ `FGraphPinHandle Pin1Handle;`
- L87 _protected member_ `FGraphPinHandle Pin2Handle;`
- L88 _protected member_ `FGraphPinHandle BestPinHandle;`
- L89 _protected member_ `UEdGraphPin* Pin1;`
- L90 _protected member_ `UEdGraphPin* Pin2;`
- L91 _protected member_ `float DistanceSquared;`
- L92 _protected member_ `float DistanceSquaredToPin1;`
- L93 _protected member_ `float DistanceSquaredToPin2;`
- L94 _protected member_ `bool bCloseToSpline;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetNodes/KismetNodeInfoContext.h` (Public)


#### struct `FKismetNodeInfoContext`  
`struct FKismetNodeInfoContext : public FNodeInfoContext`  
_L21-61_
- inherits: `FNodeInfoContext`
- desc: Context used to aid debugging displays for nodes
- L45 _public member_ `TMap<class UEdGraphNode*, TArray<FObjectUUIDPair> > NodesWithActiveLatentActions;`
- L48 _public member_ `TSet<UEdGraphPin*> WatchedPinSet;` — Set of pins with watches
- L51 _public member_ `TSet<UEdGraphNode*> WatchedNodeSet;` — Set of nodes with a pin that is being watched
- L54 _public member_ `UBlueprint* SourceBlueprint;` — Source blueprint for the graph
- L57 _public member_ `UObject* ActiveObjectBeingDebugged;` — Object being debugged for the graph
- L60 _public prototype_ `FKismetNodeInfoContext(class UEdGraph* SourceGraph);`

#### struct `FKismetNodeInfoContext::FObjectUUIDPair`  
`struct FObjectUUIDPair`  
_L24-43_
- L27 _public member_ `class UObject* Object;`
- L28 _public member_ `int32 UUID;`
- L30 _public function_ `FObjectUUIDPair(class UObject* InObject, int32 InUUID) : Object(InObject), UUID(InUUID)`
- L32 _public function_ `FString GetDisplayName() const`

### `Source/Editor/GraphEditor/Public/KismetNodes/SGraphNodeK2Base.h` (Public)


#### class `SGraphNodeK2Base`  
`class SGraphNodeK2Base : public SGraphNode`  
_L24-70_
- inherits: `SGraphNode`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Base)`
- L28 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<ISlateStyle>, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `virtual void UpdateGraphNode() override;`
- L37 _public prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L38 _public prototype_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const override;`
- L39 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L40 _public prototype_ `virtual void GetDiffHighlightBrushes(const FSlateBrush*& BackgroundOut, const FSlateBrush*& ForegroundOut) const override;`
- L41 _public prototype_ `void PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup) const override;`
- L45 _protected prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L49 _protected prototype_ `void UpdateStandardNode();` — Set up node in 'standard' mode
- L51 _protected prototype_ `void UpdateCompactNode();` — Set up node in 'compact' mode
- L54 _protected prototype_ `FText GetNodeCompactTitle() const;` — Get title in compact mode
- L57 _protected prototype_ `FText GetToolTipHeading() const;` — Retrieves text to tack on to the top of the tooltip (above the standard text)
- L60 _protected prototype_ `const ISlateStyle& GetStyleSet() const;` — Returns the slate style to use for this node
- L63 _protected member_ `TSharedPtr<ISlateStyle> Style;` — The slate style to use. We'll fall back to App Style if it's unset.
- L66 _protected member_ `static const FLinearColor BreakpointHitColor;`
- L67 _protected member_ `static const FLinearColor LatentBubbleColor;`
- L68 _protected member_ `static const FLinearColor TimelineBubbleColor;`
- L69 _protected member_ `static const FLinearColor PinnedWatchColor;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetNodes/SGraphNodeK2Composite.h` (Public)


#### class `SGraphNodeK2Composite`  
`class SGraphNodeK2Composite : public SGraphNodeK2Base`  
_L19-38_
- inherits: `SGraphNodeK2Base`
- L22 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Composite)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_Composite* InNode);`
- L28 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L29 _public prototype_ `virtual TSharedPtr<SToolTip> GetComplexTooltip() override;`
- L32 _protected prototype_ `virtual UEdGraph* GetInnerGraph() const;`
- L34 _protected prototype_ `FText GetPreviewCornerText() const;`
- L35 _protected prototype_ `FText GetTooltipTextForNode() const;`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeBody();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetNodes/SGraphNodeK2Default.h` (Public)


#### class `SGraphNodeK2Default`  
`class SGraphNodeK2Default : public SGraphNodeK2Base`  
_L13-20_
- inherits: `SGraphNodeK2Base`
- L16 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Default)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node* InNode);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetNodes/SGraphNodeK2Event.h` (Public)


#### class `SGraphNodeK2Event`  
`class SGraphNodeK2Event : public SGraphNodeK2Default`  
_L20-46_
- inherits: `SGraphNodeK2Default`
- L23 _public function_ `SGraphNodeK2Event() : SGraphNodeK2Default(), bHasDelegateOutputPin(false)`
- L26 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle) override;`
- L27 _protected prototype_ `virtual bool UseLowDetailNodeTitles() const override;`
- L28 _protected prototype_ `virtual void AddPin( const TSharedRef<SGraphPin>& PinToAdd ) override;`
- L31 _protected function_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override`
- L37 _private function_ `bool ParentUseLowDetailNodeTitles() const`
- L42 _private prototype_ `EVisibility GetTitleVisibility() const;`
- L44 _private member_ `TSharedPtr<SOverlay> TitleAreaWidget;`
- L45 _private member_ `bool bHasDelegateOutputPin;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetNodes/SGraphNodeK2Var.h` (Public)


#### class `SGraphNodeK2Var`  
`class SGraphNodeK2Var : public SGraphNodeK2Base`  
_L20-41_
- inherits: `SGraphNodeK2Base`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeK2Var)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UK2Node* InNode );`
- L28 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L30 _public prototype_ `virtual void GetDiffHighlightBrushes(const FSlateBrush*& BackgroundOut, const FSlateBrush*& ForegroundOut) const override;`
- L33 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L37 _protected prototype_ `FSlateColor GetVariableColor() const;`
- L40 _protected prototype_ `virtual TSharedRef<SWidget> UpdateTitleWidget(FText InTitleText, TSharedPtr<SWidget> InTitleWidget, EHorizontalAlignment& InOutTitleHAlign, FMargin& InOutTitleMargin) const;` — Allow derived classes to override title widget

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinBool.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinBool>`  
_L18-21_
- L20 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinBool`  
`class SGraphPinBool : public SGraphPin`  
_L23-41_
- inherits: `SGraphPin`
- L26 _public function_ `SLATE_BEGIN_ARGS(SGraphPinBool)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L37 _protected prototype_ `ECheckBoxState IsDefaultValueChecked() const;` — Determine if the check box should be checked or not
- L40 _protected prototype_ `void OnDefaultValueCheckBoxChanged( ECheckBoxState InIsChecked );` — Called when check box is changed

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinClass.h` (Public)


#### class `SGraphPinClass`  
`class SGraphPinClass : public SGraphPinObject`  
_L24-51_
- inherits: `SGraphPinObject`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphPinClass)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L31 _public function_ `void SetAllowAbstractClasses(bool bAllow)`
- L35 _protected prototype_ `void OnPickedNewClass(UClass* ChosenClass);` — Called when a new class was picked via the asset picker
- L38 _protected prototype_ `virtual FReply OnClickUse() override;`
- L39 _protected function_ `virtual bool AllowSelfPinWidget() const override`
- L40 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAssetPicker() override;`
- L41 _protected prototype_ `virtual FText GetDefaultComboText() const override;`
- L42 _protected prototype_ `virtual FOnClicked GetOnUseButtonDelegate() override;`
- L43 _protected prototype_ `virtual const FAssetData& GetAssetData(bool bRuntimePath) const override;`
- L47 _protected member_ `mutable FAssetData CachedEditorAssetData;` — Cached AssetData without the _C
- L50 _protected member_ `bool bAllowAbstractClasses;` — Whether abstract classes should be filtered out in the class viewer

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinColor.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinColor>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinColor`  
`class SGraphPinColor : public SGraphPin`  
_L27-52_
- inherits: `SGraphPin`
- L30 _public function_ `SLATE_BEGIN_ARGS(SGraphPinColor)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L36 _public prototype_ `FLinearColor GetColor () const;` — Return the current color value stored in the pin
- L40 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L44 _protected prototype_ `FReply OnColorBoxClicked(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when clicking on the color button
- L47 _protected prototype_ `void OnColorCommitted(FLinearColor color);` — Called when the color picker commits a color value
- L51 _private member_ `TSharedPtr<SWidget> DefaultValueWidget;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinEnum.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinEnum>`  
_L20-23_
- L22 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinEnum`  
`class SGraphPinEnum : public SGraphPin`  
_L25-89_
- inherits: `SGraphPin`
- L28 _public function_ `SLATE_BEGIN_ARGS(SGraphPinEnum)`
- L31 _public prototype_ `SLATE_ARGUMENT(TArray<FString>, ValidEnumValues) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);` — The array of values to allow in the combobox. All values permitted if this array is empty.
- L44 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — Function to create class specific widget. @return Reference to the newly created widget object
- L53 _private prototype_ `FString OnGetText() const;` — Function to get current string associated with the combo box selection @return currently selected string
- L60 _private prototype_ `void GenerateComboBoxIndexes( TArray< TSharedPtr<int32> >& OutComboBoxIndexes );` — Function to generate the list of indexes from the enum object @param OutComboBoxIndexes - Int array reference to store the list of indexes
- L68 _private prototype_ `void ComboBoxSelectionChanged( TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo );` — Function to set the newly selected index @param NewSelection The newly selected item in the combo box @param SelectInfo Provides context on how the selection changed
- L75 _private prototype_ `FText OnGetFriendlyName(int32 EnumIndex);` — Returns the friendly name of the enum at index EnumIndex @param EnumIndex	- The index of the enum to return the friendly name for
- L82 _private prototype_ `FText OnGetTooltip(int32 EnumIndex);` — Returns the tooltip of the enum at index EnumIndex @param EnumIndex	- The index of the enum to return the tooltip for
- L85 _private member_ `TArray<FString> ValidEnumValues;` — The array of values to allow in the combobox. All values permitted if this array is empty.
- L88 _private member_ `TSharedPtr<class SPinComboBox> ComboBox;` — Shared pointer to the combobox widget.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinExec.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinExec>`  
_L19-22_
- L21 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinExec`  
`class SGraphPinExec : public SGraphPin`  
_L24-42_
- inherits: `SGraphPin`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphPinExec)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L35 _protected prototype_ `virtual const FSlateBrush* GetPinIcon() const override;`
- L38 _protected prototype_ `void CachePinIcons();`
- L40 _protected member_ `const FSlateBrush* CachedImg_Pin_ConnectedHovered;`
- L41 _protected member_ `const FSlateBrush* CachedImg_Pin_DisconnectedHovered;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinInteger.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinInteger>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinInteger`  
`class SGraphPinInteger : public SGraphPinNum<int32>`  
_L27-39_
- inherits: `SGraphPinNum<int32>`
- L30 _public function_ `SLATE_BEGIN_ARGS(SGraphPinInteger)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinIntegerSlider.h` (Public)


#### class `SGraphPinIntegerSlider`  
`class SGraphPinIntegerSlider : public SGraphPinNumSlider<int32>`  
_L21-33_
- inherits: `SGraphPinNumSlider<int32>`
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphPinIntegerSlider)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, FProperty* InProperty);`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinNum.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SGraphPinNum<NumericType>>`  
_L18-21_
- L20 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinNum`  
`template <typename NumericType> class SGraphPinNum : public SGraphPin`  
_L24-75_
- inherits: `SGraphPin`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphPinNum)`
- L28 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`
- L37 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — SGraphPin interface
- L53 _protected function_ `TOptional<NumericType> GetNumericValue() const`
- L60 _protected function_ `void SetNumericValue(NumericType InValue, ETextCommit::Type CommitType)`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinNumSlider.h` (Public)


#### class `SGraphPinNumSlider`  
`template <typename NumericType> class SGraphPinNumSlider : public SGraphPin`  
_L17-170_
- inherits: `SGraphPin`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGraphPinNumSlider) :_MinDesiredBoxWidth(18.0f) ,_ShouldShowDisabledWhenConnected(false)`
- L25 _public function_ `SLATE_ARGUMENT(float, MinDesiredBoxWidth) SLATE_ARGUMENT(bool, ShouldShowDisabledWhenConnected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, FProperty* InProperty)`
- L40 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — SGraphPin interface
- L81 _protected function_ `void OnValueChanged( NumericType NewValue )`
- L87 _protected function_ `void OnValueCommitted( NumericType NewValue, ETextCommit::Type CommitInfo )`
- L106 _protected function_ `void OnBeginSliderMovement()` — Called when the slider begins to move.
- L118 _protected function_ `void OnEndSliderMovement( NumericType NewValue )` — Called when the slider stops moving.
- L124 _protected function_ `TOptional<NumericType> GetNumericValue() const`
- L131 _protected function_ `virtual EVisibility GetDefaultValueVisibility() const override`
- L164 _private member_ `FProperty* PinProperty;`
- L165 _private member_ `NumericType LastSliderCommittedValue;`
- L166 _private member_ `NumericType SliderValue;`
- L167 _private member_ `float MinDesiredBoxWidth = 0.0f;`
- L168 _private member_ `bool bIsUsingSlider = false;`
- L169 _private member_ `bool bShouldShowDisabledWhenConnected = false;`

#### Free symbols / members of external scopes

- L43 _function_ `` (scope `SGraphPinNumSlider::GetDefaultValueWidget`)

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinObject.h` (Public)


#### class `SGraphPinObject`  
`class SGraphPinObject : public SGraphPin`  
_L25-91_
- inherits: `SGraphPin`
- L28 _public function_ `SLATE_BEGIN_ARGS(SGraphPinObject)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L35 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L36 _protected function_ `virtual bool DoesWidgetHandleSettingEditingEnabled() const override`
- L40 _protected prototype_ `virtual FOnClicked GetOnUseButtonDelegate();` — Delegate to be called when the use current selected item in asset browser button is clicked
- L42 _protected prototype_ `virtual FOnClicked GetOnBrowseButtonDelegate();` — Delegate to be called when the browse for item button is clicked
- L45 _protected prototype_ `virtual FReply OnClickUse();` — Clicked Use button
- L47 _protected prototype_ `virtual FReply OnClickBrowse();` — Clicked Browse button
- L49 _protected prototype_ `FText GetObjectToolTip() const;` — Get text tooltip for object
- L51 _protected prototype_ `FString GetObjectToolTipAsString() const;` — Get text tooltip for object
- L53 _protected prototype_ `FText GetValue() const;` — Get string value for object
- L55 _protected prototype_ `FText GetObjectName() const;` — Get name of the object
- L57 _protected prototype_ `virtual FText GetDefaultComboText() const;` — Get default text for the picker combo
- L59 _protected function_ `virtual bool AllowSelfPinWidget() const` — Allow self pin widget
- L61 _protected prototype_ `virtual bool ShouldDisplayAsSelfPin() const;` — True if this specific pin should be treated as a self pin
- L63 _protected prototype_ `virtual TSharedRef<SWidget> GenerateAssetPicker();` — Generate asset picker window
- L65 _protected prototype_ `virtual void OnAssetSelectedFromPicker(const struct FAssetData& AssetData);` — Called to validate selection from picker window
- L67 _protected prototype_ `void OnAssetEnterPressedInPicker(const TArray<FAssetData>& InSelectedAssets);` — Called when enter is pressed when items are selected in the picker window
- L70 _protected prototype_ `FText OnGetComboTextValue() const;` — Used to update the combo button text
- L72 _protected prototype_ `FSlateColor OnGetComboForeground() const;` — Combo Button Color and Opacity delegate
- L74 _protected prototype_ `FSlateColor OnGetWidgetForeground() const;` — Button Color and Opacity delegate
- L76 _protected prototype_ `FSlateColor OnGetWidgetBackground() const;` — Button Color and Opacity delegate
- L79 _protected prototype_ `virtual const FAssetData& GetAssetData(bool bRuntimePath) const;` — Returns asset data of currently selected object, if bRuntimePath is true this will include _C for blueprint classes, for false it will point to UBlueprint instead
- L83 _protected member_ `TSharedPtr<SButton> UseButton;` — Object manipulator buttons.
- L84 _protected member_ `TSharedPtr<SButton> BrowseButton;`
- L87 _protected member_ `TSharedPtr<class SMenuAnchor> AssetPickerAnchor;` — Menu anchor for opening and closing the asset picker
- L90 _protected member_ `mutable FAssetData CachedAssetData;` — Cached AssetData of object selected

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinString.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinString>`  
_L19-22_
- L21 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinString`  
`class SGraphPinString : public SGraphPin`  
_L24-49_
- inherits: `SGraphPin`
- L27 _public function_ `SLATE_BEGIN_ARGS(SGraphPinString)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L37 _protected prototype_ `FText GetTypeInValue() const;`
- L38 _protected prototype_ `virtual void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type CommitInfo);`
- L41 _protected prototype_ `bool GetDefaultValueIsReadOnly() const;` — @return True if the pin default value field is read-only
- L44 _private prototype_ `TSharedRef<SWidget> GenerateComboBoxEntry(TSharedPtr<FString> Value);`
- L45 _private prototype_ `void HandleComboBoxSelectionChanged(TSharedPtr<FString> Value, ESelectInfo::Type InSelectInfo);`
- L46 _private prototype_ `TSharedPtr<SWidget> TryBuildComboBoxWidget();`
- L48 _private member_ `TArray<TSharedPtr<FString>> ComboBoxOptions;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinStructInstance.h` (Public)


#### struct `FPinStructEditWrapper`  
`struct FPinStructEditWrapper`  
_L34-48_
- reflection: `USTRUCT()`
- desc: Base type for editing simple structs as pin default values, by displaying a nested version of a struct customization. To make this work, create an inherited USTRUCT that includes a copy of the struct to be edited and overrides the functions. Then, pass in StructName::StaticStruct() when creating SGraphPinStructInstance from a pin factory
- L38 _public prototype_ `virtual ~FPinStructEditWrapper() = default;`
- L41 _public function_ `virtual FText GetPreviewDescription() const` — Returns a text representation of the data
- L44 _public function_ `virtual const UScriptStruct* GetDataScriptStruct() const` — Returns what script struct to use to parse the nested data
- L47 _public function_ `virtual uint8* GetDataMemory()` — Returns address of nested data

#### class `SGraphPinStructInstance`  
`class SGraphPinStructInstance : public SGraphPin`  
_L74-127_
- inherits: `SGraphPin`
- desc: This is a pin for showing a details customization for a struct instance. It can be used directly by passing in a StructEditWrapper parameter when creating from a pin factory Or, it can be subclassed for other types of struct display
- L77 _public function_ `SLATE_BEGIN_ARGS(SGraphPinStructInstance) : _StructEditWrapper(nullptr)`
- L80 _public prototype_ `SLATE_ARGUMENT(const UScriptStruct*, StructEditWrapper) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L88 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L92 _protected prototype_ `virtual void ParseDefaultValueData();` — Parses the struct ata from the pin to fill in the struct instance
- L95 _protected prototype_ `virtual void SaveDefaultValueData();` — Call to push changes from edit instance to pin
- L98 _protected prototype_ `virtual void RefreshCachedData();` — Refreshes cached description and edit data after an edit change
- L101 _protected prototype_ `virtual TSharedRef<SWidget> GetEditContent();` — Creates widget used to edit the struct instance
- L104 _protected prototype_ `virtual TSharedRef<SWidget> GetDescriptionContent();` — Creates widget for displaying preview on the pin
- L107 _protected prototype_ `virtual FText GetCachedDescriptionText() const;` — Slate accessor to shows cached description value
- L110 _protected prototype_ `virtual FPinStructEditWrapper* GetEditWrapper() const;` — Returns the base instance inside EditStruct, if null this is assumed to be a subclass that overrides other functions
- L113 _protected prototype_ `virtual void PropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Called when struct is modified by the details view
- L117 _protected member_ `TSharedPtr<SComboButton> ComboButton;` — Combo Button widget used to show edit content
- L120 _protected member_ `TSharedPtr<FStructOnScope> EditWrapperInstance;` — Instance of FPinStructEditWrapper that wraps what we actually want to edit
- L123 _protected member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;` — Details view that points into EditWrapperInstance
- L126 _protected member_ `FText CachedDescription;` — Cached description text

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVector.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SGraphPinVector<NumericType>>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinVector`  
`template <typename NumericType> class SGraphPinVector : public SGraphPin`  
_L28-236_
- inherits: `SGraphPin`
- L31 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVector)`
- L32 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`
- L46 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L72 _private typedef_ `using FVectorType = UE::Math::TVector<NumericType>;`
- L81 _private function_ `FString GetCurrentValue_0() const` — Function to get current value in text box 0 @return current string value
- L92 _private function_ `FString GetCurrentValue_1() const` — Function to get current value in text box 1 @return current string value
- L103 _private function_ `FString GetCurrentValue_2() const` — Function to get current value in text box 2 @return current string value
- L115 _private function_ `TArray<FString> GetComponentArray() const` — Function to get a string array of the components composing the default string. @return The array filled with each component as string
- L135 _private function_ `FString GetValue(ETextBoxIndex Index) const` — Function to get current value based on text box index value @param: Text box index @return current string value
- L154 _private function_ `void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 0 value in modified @param 0: Updated numeric Value
- L165 _private function_ `void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 1 value in modified @param 0: Updated numeric Value
- L176 _private function_ `void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 2 value in modified @param 0: Updated numeric Value
- L182 _private function_ `void SetNewValueHelper(EAxis::Type Axis, NumericType NewValue)`
- L214 _private function_ `FVectorType ConvertDefaultValueStringToVector() const` — @brief Converts the default string value to a value of VectorType. Example: it converts the default string value "2.00,3.00,4.00" to the corresponding 3D vector.
- L235 _private member_ `bool bIsRotator;` — Flag is true if the widget is used to represent a rotator; false otherwise

#### enum `SGraphPinVector::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L65-70_
- desc: Enum values to identify text boxes.
- L67 _public enumerator_ `TextBox_0`
- L68 _public enumerator_ `TextBox_1`
- L69 _public enumerator_ `TextBox_2`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVector2D.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SGraphPinVector2D<NumericType>>`  
_L23-26_
- L25 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinVector2D`  
`template <typename NumericType> class SGraphPinVector2D : public SGraphPin`  
_L30-156_
- inherits: `SGraphPin`
- L33 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVector2D)`
- L34 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`
- L48 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L74 _private function_ `FString GetCurrentValue_X() const` — Function to get current value in text box 0 @return current string value
- L84 _private function_ `FString GetCurrentValue_Y() const` — Function to get current value in text box 1 @return current string value
- L96 _private function_ `FVector2D GetValue() const` — Function to getch current value based on text box index value @param: Text box index @return current value
- L106 _private function_ `static FString MakeVector2DString(NumericType X, NumericType Y)`
- L116 _private function_ `void OnChangedValueTextBox_X(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 0 value in modified @param 0: Updated numeric value
- L139 _private function_ `void OnChangedValueTextBox_Y(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 1 value in modified @param 0: Updated numeric value

#### enum `SGraphPinVector2D::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L63-67_
- desc: Enum values to identify text boxes.
- L65 _public enumerator_ `TextBox_X`
- L66 _public enumerator_ `TextBox_Y`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVector2DSlider.h` (Public)


#### class `SGraphPinVector2DSlider`  
`template <typename NumericType> class SGraphPinVector2DSlider : public SGraphPin`  
_L22-151_
- inherits: `SGraphPin`
- L24 _private member_ `FProperty* PinProperty;`
- L26 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVector2DSlider)`
- L28 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, FProperty* InProperty)`
- L43 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L69 _private function_ `FString GetCurrentValue_X() const` — Function to get current value in text box 0 @return current string value
- L79 _private function_ `FString GetCurrentValue_Y() const` — Function to get current value in text box 1 @return current string value
- L91 _private function_ `FVector2D GetValue() const` — Function to getch current value based on text box index value @param: Text box index @return current value
- L101 _private function_ `static FString MakeVector2DString(NumericType X, NumericType Y)`
- L111 _private function_ `void OnChangedValueTextBox_X(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 0 value in modified @param 0: Updated numeric value
- L134 _private function_ `void OnChangedValueTextBox_Y(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 1 value in modified @param 0: Updated numeric value

#### enum `SGraphPinVector2DSlider::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L58-62_
- desc: Enum values to identify text boxes.
- L60 _public enumerator_ `TextBox_X`
- L61 _public enumerator_ `TextBox_Y`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVector4.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SGraphPinVector4<NumericType>>`  
_L24-27_
- L26 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinVector4`  
`template <typename NumericType> class SGraphPinVector4 : public SGraphPin`  
_L31-209_
- inherits: `SGraphPin`
- L34 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVector4)`
- L35 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)`
- L49 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L79 _private function_ `FString GetCurrentValue_0() const`
- L85 _private function_ `FString GetCurrentValue_1() const`
- L91 _private function_ `FString GetCurrentValue_2() const`
- L97 _private function_ `FString GetCurrentValue_3() const`
- L110 _private function_ `FString GetValue(ETextBoxIndex Index) const` — Function to getch current value based on text box index value @param: Text box index @return current string value
- L134 _private function_ `void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box value in modified @param 0: Updated numeric value
- L152 _private function_ `void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L170 _private function_ `void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L188 _private function_ `void OnChangedValueTextBox_3(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L208 _private member_ `bool bIsRotator;` — Flag is true if the widget is used to represent a rotator; false otherwise

#### enum `SGraphPinVector4::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L69-75_
- desc: Enum values to identify text boxes.
- L71 _public enumerator_ `TextBox_0`
- L72 _public enumerator_ `TextBox_1`
- L73 _public enumerator_ `TextBox_2`
- L74 _public enumerator_ `TextBox_3`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVector4Slider.h` (Public)


#### class `SGraphPinVector4Slider`  
`template <typename NumericType> class SGraphPinVector4Slider : public SGraphPin`  
_L20-200_
- inherits: `SGraphPin`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVector4Slider)`
- L24 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, FProperty* InProperty)`
- L39 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L69 _private function_ `FString GetCurrentValue_0() const`
- L75 _private function_ `FString GetCurrentValue_1() const`
- L81 _private function_ `FString GetCurrentValue_2() const`
- L87 _private function_ `FString GetCurrentValue_3() const`
- L100 _private function_ `FString GetValue(ETextBoxIndex Index) const` — Function to getch current value based on text box index value @param: Text box index @return current string value
- L124 _private function_ `void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box value in modified @param 0: Updated numeric value
- L142 _private function_ `void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L160 _private function_ `void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L178 _private function_ `void OnChangedValueTextBox_3(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L199 _private member_ `FProperty* PinProperty;` — Property to get metadata values out of for the slider widget

#### enum `SGraphPinVector4Slider::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L59-65_
- desc: Enum values to identify text boxes.
- L61 _public enumerator_ `TextBox_0`
- L62 _public enumerator_ `TextBox_1`
- L63 _public enumerator_ `TextBox_2`
- L64 _public enumerator_ `TextBox_3`

### `Source/Editor/GraphEditor/Public/KismetPins/SGraphPinVectorSlider.h` (Public)


#### class `SGraphPinVectorSlider`  
`template <typename NumericType> class SGraphPinVectorSlider : public SGraphPin`  
_L21-236_
- inherits: `SGraphPin`
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphPinVectorSlider)`
- L26 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, FProperty* InProperty)`
- L41 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override` — Function to create class specific widget. @return Reference to the newly created widget object
- L68 _private typedef_ `using FVectorType = UE::Math::TVector<NumericType>;`
- L77 _private function_ `FString GetCurrentValue_0() const` — Function to get current value in text box 0 @return current string value
- L88 _private function_ `FString GetCurrentValue_1() const` — Function to get current value in text box 1 @return current string value
- L99 _private function_ `FString GetCurrentValue_2() const` — Function to get current value in text box 2 @return current string value
- L111 _private function_ `TArray<FString> GetComponentArray() const` — Function to get a string array of the components composing the default string. @return The array filled with each component as string
- L131 _private function_ `FString GetValue(ETextBoxIndex Index) const` — Function to get current value based on text box index value @param: Text box index @return current string value
- L150 _private function_ `void OnChangedValueTextBox_0(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 0 value in modified @param 0: Updated numeric Value
- L161 _private function_ `void OnChangedValueTextBox_1(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 1 value in modified @param 0: Updated numeric Value
- L172 _private function_ `void OnChangedValueTextBox_2(NumericType NewValue, ETextCommit::Type CommitInfo)` — Function to store value when text box 2 value in modified @param 0: Updated numeric Value
- L178 _private function_ `void SetNewValueHelper(EAxis::Type Axis, NumericType NewValue)`
- L210 _private function_ `FVectorType ConvertDefaultValueStringToVector() const` — @brief Converts the default string value to a value of VectorType. Example: it converts the default string value "2.00,3.00,4.00" to the corresponding 3D vector.
- L231 _private member_ `bool bIsRotator;` — Flag is true if the widget is used to represent a rotator; false otherwise
- L234 _private member_ `FProperty* PinProperty;` — Property to get metadata values out of for the slider widget

#### enum `SGraphPinVectorSlider::ETextBoxIndex`  
`enum ETextBoxIndex`  
_L61-66_
- desc: Enum values to identify text boxes.
- L63 _public enumerator_ `TextBox_0`
- L64 _public enumerator_ `TextBox_1`
- L65 _public enumerator_ `TextBox_2`

### `Source/Editor/GraphEditor/Public/KismetPins/SVector2DSlider.h` (Public)


#### class `SVector2DSlider`  
`template <typename NumericType> class SVector2DSlider : public SCompoundWidget`  
_L16-246_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 2 editable text boxes to represent vector2D graph pin
- L21 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L23 _public function_ `SLATE_BEGIN_ARGS( SVector2DSlider )`
- L24 _public function_ `SLATE_ATTRIBUTE( FString, VisibleText_X ) SLATE_ATTRIBUTE( FString, VisibleText_Y ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_X ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_Y ) SLATE_END_ARGS()`
- L141 _private function_ `void OnValueChanged_X(NumericType NewValue)` — Called when the slider value changes
- L149 _private function_ `void OnValueChanged_Y(NumericType NewValue)` — Called when the slider value changes
- L157 _private function_ `void OnBeginSliderMovement_X()` — Called when the slider begins to move.
- L166 _private function_ `void OnEndSliderMovement_X(NumericType NewValue)` — Called when the slider stops moving.
- L179 _private function_ `void OnBeginSliderMovement_Y()` — Called when the slider begins to move.
- L188 _private function_ `void OnEndSliderMovement_Y(NumericType NewValue)` — Called when the slider stops moving.
- L198 _private function_ `void SyncValues()`
- L204 _private function_ `NumericType GetValueType(const FString& InString) const`
- L223 _private function_ `TOptional<NumericType> GetTypeInValue_X() const` — Get value for X text box
- L229 _private function_ `TOptional<NumericType> GetTypeInValue_Y() const` — Get value for Y text box
- L234 _private member_ `TAttribute<FString> VisibleText_X;`
- L235 _private member_ `TAttribute<FString> VisibleText_Y;`
- L237 _private member_ `FProperty* PinProperty;`
- L238 _private member_ `FOnNumericValueCommitted OnNumericCommitted_X;`
- L239 _private member_ `FOnNumericValueCommitted OnNumericCommitted_Y;`
- L241 _private member_ `NumericType LastSliderCommittedValue_X;`
- L242 _private member_ `NumericType LastSliderCommittedValue_Y;`
- L243 _private member_ `NumericType SliderValue_X;`
- L244 _private member_ `NumericType SliderValue_Y;`
- L245 _private member_ `bool bIsUsingSlider = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "Vector2DTextBox"`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L42 _function_ `` (scope `SVector2DSlider::SLATE_ATTRIBUTE`)

### `Source/Editor/GraphEditor/Public/KismetPins/SVector2DTextBox.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SVector2DTextBox<NumericType>>`  
_L17-20_
- L19 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SVector2DTextBox`  
`template <typename NumericType> class SVector2DTextBox : public SCompoundWidget`  
_L24-135_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 2 editable text boxes to represent vector2D graph pin
- L29 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L31 _public function_ `SLATE_BEGIN_ARGS( SVector2DTextBox )`
- L32 _public function_ `SLATE_ATTRIBUTE( FString, VisibleText_X ) SLATE_ATTRIBUTE( FString, VisibleText_Y ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_X ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_Y ) SLATE_END_ARGS()`
- L103 _private function_ `NumericType GetValueType(const FString& InString) const`
- L122 _private function_ `TOptional<NumericType> GetTypeInValue_X() const` — Get value for X text box
- L128 _private function_ `TOptional<NumericType> GetTypeInValue_Y() const` — Get value for Y text box
- L133 _private member_ `TAttribute<FString> VisibleText_X;`
- L134 _private member_ `TAttribute<FString> VisibleText_Y;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "Vector2DTextBox"`
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed

### `Source/Editor/GraphEditor/Public/KismetPins/SVector4Slider.h` (Public)


#### class `SVector4Slider`  
`template <typename NumericType> class SVector4Slider : public SCompoundWidget`  
_L17-405_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 3 editable text boxes to represent vector/rotator graph pin
- L22 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L24 _public function_ `SLATE_BEGIN_ARGS(SVector4Slider)`
- L25 _public function_ `SLATE_ATTRIBUTE(FString, VisibleText_0) SLATE_ATTRIBUTE(FString, VisibleText_1) SLATE_ATTRIBUTE(FString, VisibleText_2) SLATE_ATTRIBUTE(FString, VisibleText_3) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_0) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_1) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_2) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_3) SLATE_END_ARGS()`
- L223 _private function_ `void OnBeginSliderMovement_0()` — Called when the slider begins to move.
- L232 _private function_ `void OnEndSliderMovement_0(NumericType NewValue)` — Called when the slider stops moving.
- L245 _private function_ `void OnBeginSliderMovement_1()` — Called when the slider begins to move.
- L254 _private function_ `void OnEndSliderMovement_1(NumericType NewValue)` — Called when the slider stops moving.
- L267 _private function_ `void OnBeginSliderMovement_2()` — Called when the slider begins to move.
- L276 _private function_ `void OnEndSliderMovement_2(NumericType NewValue)` — Called when the slider stops moving.
- L289 _private function_ `void OnBeginSliderMovement_3()` — Called when the slider begins to move.
- L298 _private function_ `void OnEndSliderMovement_3(NumericType NewValue)` — Called when the slider stops moving.
- L311 _private function_ `void OnValueChanged_0(NumericType NewValue)` — Called when the slider value changes
- L319 _private function_ `void OnValueChanged_1(NumericType NewValue)` — Called when the slider value changes
- L327 _private function_ `void OnValueChanged_2(NumericType NewValue)` — Called when the slider value changes
- L335 _private function_ `void OnValueChanged_3(NumericType NewValue)` — Called when the slider value changes
- L340 _private function_ `void SyncValues()`
- L347 _private function_ `NumericType GetValueType(const FString& InString) const`
- L365 _private function_ `TOptional<NumericType> GetTypeInValue_0() const`
- L370 _private function_ `TOptional<NumericType> GetTypeInValue_1() const`
- L375 _private function_ `TOptional<NumericType> GetTypeInValue_2() const`
- L380 _private function_ `TOptional<NumericType> GetTypeInValue_3() const`
- L385 _private member_ `TAttribute<FString> VisibleText_0;`
- L386 _private member_ `TAttribute<FString> VisibleText_1;`
- L387 _private member_ `TAttribute<FString> VisibleText_2;`
- L388 _private member_ `TAttribute<FString> VisibleText_3;`
- L389 _private member_ `FProperty* PinProperty;`
- L391 _private member_ `FOnNumericValueCommitted OnNumericCommitted_0;`
- L392 _private member_ `FOnNumericValueCommitted OnNumericCommitted_1;`
- L393 _private member_ `FOnNumericValueCommitted OnNumericCommitted_2;`
- L394 _private member_ `FOnNumericValueCommitted OnNumericCommitted_3;`
- L396 _private member_ `NumericType LastSliderCommittedValue_0;`
- L397 _private member_ `NumericType LastSliderCommittedValue_1;`
- L398 _private member_ `NumericType LastSliderCommittedValue_2;`
- L399 _private member_ `NumericType LastSliderCommittedValue_3;`
- L400 _private member_ `NumericType SliderValue_0;`
- L401 _private member_ `NumericType SliderValue_1;`
- L402 _private member_ `NumericType SliderValue_2;`
- L403 _private member_ `NumericType SliderValue_3;`
- L404 _private member_ `bool bIsUsingSlider = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "VectorTextBox"`
- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L51 _function_ `` (scope `SVector4Slider::SLATE_ATTRIBUTE`)

### `Source/Editor/GraphEditor/Public/KismetPins/SVector4TextBox.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SVector4TextBox<NumericType>>`  
_L17-20_
- L19 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SVector4TextBox`  
`template <typename NumericType> class SVector4TextBox : public SCompoundWidget`  
_L25-197_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 4 editable text boxes to represent vector/rotator graph pin
- L30 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L32 _public function_ `SLATE_BEGIN_ARGS(SVector4TextBox)`
- L33 _public function_ `SLATE_ATTRIBUTE(FString, VisibleText_0) SLATE_ATTRIBUTE(FString, VisibleText_1) SLATE_ATTRIBUTE(FString, VisibleText_2) SLATE_ATTRIBUTE(FString, VisibleText_3) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_0) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_1) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_2) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_3) SLATE_END_ARGS()`
- L155 _private function_ `NumericType GetValueType(const FString& InString) const`
- L173 _private function_ `TOptional<NumericType> GetTypeInValue_0() const`
- L178 _private function_ `TOptional<NumericType> GetTypeInValue_1() const`
- L183 _private function_ `TOptional<NumericType> GetTypeInValue_2() const`
- L188 _private function_ `TOptional<NumericType> GetTypeInValue_3() const`
- L193 _private member_ `TAttribute<FString> VisibleText_0;`
- L194 _private member_ `TAttribute<FString> VisibleText_1;`
- L195 _private member_ `TAttribute<FString> VisibleText_2;`
- L196 _private member_ `TAttribute<FString> VisibleText_3;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "VectorTextBox"`
- L30 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed

### `Source/Editor/GraphEditor/Public/KismetPins/SVectorSlider.h` (Public)


#### class `SVectorSlider`  
`template <typename NumericType> class SVectorSlider : public SCompoundWidget`  
_L16-334_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 2 editable text boxes to represent vector2D graph pin
- L21 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L23 _public function_ `SLATE_BEGIN_ARGS( SVectorSlider )`
- L24 _public function_ `SLATE_ATTRIBUTE( FString, VisibleText_0 ) SLATE_ATTRIBUTE( FString, VisibleText_1 ) SLATE_ATTRIBUTE( FString, VisibleText_2) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_0) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_1) SLATE_EVENT(FOnNumericValueCommitted, OnNumericCommitted_Box_2) SLATE_END_ARGS()`
- L187 _private function_ `void OnBeginSliderMovement_0()` — Called when the slider begins to move.
- L196 _private function_ `void OnEndSliderMovement_0(NumericType NewValue)` — Called when the slider stops moving.
- L209 _private function_ `void OnBeginSliderMovement_1()` — Called when the slider begins to move.
- L218 _private function_ `void OnEndSliderMovement_1(NumericType NewValue)` — Called when the slider stops moving.
- L231 _private function_ `void OnBeginSliderMovement_2()` — Called when the slider begins to move.
- L240 _private function_ `void OnEndSliderMovement_2(NumericType NewValue)` — Called when the slider stops moving.
- L253 _private function_ `void OnValueChanged_0(NumericType NewValue)` — Called when the slider value changes
- L261 _private function_ `void OnValueChanged_1(NumericType NewValue)` — Called when the slider value changes
- L269 _private function_ `void OnValueChanged_2(NumericType NewValue)` — Called when the slider value changes
- L274 _private function_ `void SyncValues()`
- L281 _private function_ `NumericType GetValueType(const FString& InString) const`
- L300 _private function_ `TOptional<NumericType> GetTypeInValue_0() const` — Get value for X text box
- L306 _private function_ `TOptional<NumericType> GetTypeInValue_1() const` — Get value for Y text box
- L311 _private function_ `TOptional<NumericType> GetTypeInValue_2() const` — Get value for Y text box
- L317 _private member_ `TAttribute<FString> VisibleText_0;`
- L318 _private member_ `TAttribute<FString> VisibleText_1;`
- L319 _private member_ `TAttribute<FString> VisibleText_2;`
- L321 _private member_ `FProperty* PinProperty;`
- L322 _private member_ `FOnNumericValueCommitted OnNumericCommitted_0;`
- L323 _private member_ `FOnNumericValueCommitted OnNumericCommitted_1;`
- L324 _private member_ `FOnNumericValueCommitted OnNumericCommitted_2;`
- L326 _private member_ `NumericType LastSliderCommittedValue_0;`
- L327 _private member_ `NumericType LastSliderCommittedValue_1;`
- L328 _private member_ `NumericType LastSliderCommittedValue_2;`
- L329 _private member_ `NumericType SliderValue_0;`
- L330 _private member_ `NumericType SliderValue_1;`
- L331 _private member_ `NumericType SliderValue_2;`
- L332 _private member_ `bool bIsUsingSlider = false;`
- L333 _private member_ `bool bIsRotator;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "Vector2DTextBox"`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L49 _function_ `` (scope `SVectorSlider::SLATE_ATTRIBUTE`)

### `Source/Editor/GraphEditor/Public/KismetPins/SVectorTextBox.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <typename NumericType> struct TWidgetTypeTraits<SVectorTextBox<NumericType>>`  
_L16-19_
- L18 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SVectorTextBox`  
`template <typename NumericType> class SVectorTextBox : public SCompoundWidget`  
_L23-171_
- inherits: `SCompoundWidget`
- desc: Class implementation to create 3 editable text boxes to represent vector/rotator graph pin
- L28 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed
- L30 _public function_ `SLATE_BEGIN_ARGS( SVectorTextBox )`
- L31 _public function_ `SLATE_ATTRIBUTE( FString, VisibleText_0 ) SLATE_ATTRIBUTE( FString, VisibleText_1 ) SLATE_ATTRIBUTE( FString, VisibleText_2 ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_0 ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_1 ) SLATE_EVENT( FOnNumericValueCommitted, OnNumericCommitted_Box_2 ) SLATE_END_ARGS()`
- L130 _private function_ `NumericType GetValueType(const FString& InString) const`
- L149 _private function_ `TOptional<NumericType> GetTypeInValue_0() const` — Get value for text box 0
- L155 _private function_ `TOptional<NumericType> GetTypeInValue_1() const` — Get value for text box 1
- L161 _private function_ `TOptional<NumericType> GetTypeInValue_2() const` — Get value for text box 2
- L166 _private member_ `TAttribute<FString> VisibleText_0;`
- L167 _private member_ `TAttribute<FString> VisibleText_1;`
- L168 _private member_ `TAttribute<FString> VisibleText_2;`
- L170 _private member_ `bool bIsRotator;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "VectorTextBox"`
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnNumericValueCommitted, NumericType, ETextCommit::Type);` — Notification for numeric value committed

### `Source/Editor/GraphEditor/Public/MarqueeOperation.h` (Public)


#### struct `FMarqueeOperation`  
`struct FMarqueeOperation`  
_L13-76_
- desc: Helper for managing marquee operations
- L15 _public function_ `FMarqueeOperation() : Operation(Add)`
- L30 _public member_ `Invert, } Operation;` — Holding down Ctrl toggles the selection state of all encompassed nodes
- L32 _public function_ `bool IsValid() const`
- L37 _public function_ `void Start(const UE::Slate::FDeprecateVector2DParameter& InStartLocation, FMarqueeOperation::Type InOperationType)`
- L43 _public function_ `void End()`
- L50 _public function_ `static FMarqueeOperation::Type OperationTypeFromMouseEvent(const FPointerEvent& MouseEvent)` — Given a mouse event, figure out what the marquee selection should do based on the state of Shift and Ctrl keys
- L72 _public member_ `FMarqueeRect Rect;` — The marquee rectangle being dragged by the user
- L75 _public member_ `FGraphPanelSelectionSet AffectedNodes;` — Nodes that will be selected or unselected by the current marquee operation

#### enum `FMarqueeOperation::Type`  
`enum Type`  
_L20-30_
- L23 _public enumerator_ `Remove` — Holding down Alt removes nodes
- L25 _public enumerator_ `Add` — Holding down Shift adds to the selection
- L27 _public enumerator_ `Replace` — When nothing is pressed, marquee replaces selection
- L29 _public enumerator_ `Invert` — Holding down Ctrl toggles the selection state of all encompassed nodes

### `Source/Editor/GraphEditor/Public/MaterialNodes/SGraphNodeMaterialBase.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/MaterialNodes/SGraphNodeMaterialComposite.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/MaterialNodes/SGraphNodeMaterialConvert.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/MaterialNodes/SGraphNodeMaterialCustom.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/MaterialNodes/SGraphNodeMaterialResult.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/MaterialPins/SGraphPinMaterialInput.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/NodeFactory.h` (Public)


#### class `FNodeFactory`  
`class FNodeFactory`  
_L22-36_
- desc: Class that decides which widget type to create for a given data object
- L26 _public prototype_ `static TSharedPtr<SGraphNode> CreateNodeWidget(UEdGraphNode* InNode);` — Create a widget for the supplied node
- L29 _public prototype_ `static TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin);` — Create a widget for the supplied pin
- L32 _public prototype_ `static TSharedPtr<SGraphPin> CreateK2PinWidget(UEdGraphPin* InPin);` — Create a K2 schema default widget for the supplied pin
- L35 _public prototype_ `static FConnectionDrawingPolicy* CreateConnectionPolicy(const UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);` — Create a pin connection factory for the supplied schema

#### class `FGraphNodeFactory`  
`class FGraphNodeFactory`  
_L39-50_
- L43 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNodeWidget(UEdGraphNode* InNode);` — Create a widget for the supplied node
- L46 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* InPin);` — Create a widget for the supplied pin
- L49 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionPolicy(const UEdGraphSchema* Schema, int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj);` — Create a pin connection factory for the supplied schema

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SCommentBubble.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SCommentBubble>`  
_L36-39_
- L38 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SCommentBubble`  
`class SCommentBubble : public SCompoundWidget`  
_L41-218_
- inherits: `SCompoundWidget`
- L43 _private function_ `SLATE_BEGIN_ARGS( SCommentBubble ) : _GraphNode( NULL ) , _ColorAndOpacity( FLinearColor::White ) , _AllowPinning( false ) , _EnableTitleBarBubble( false ) , _EnableBubbleCtrls( false ) , _InvertLODCulling( false ) , _GraphLOD( EGraphRenderingLOD::DefaultDetail )`
- L54 _private prototype_ `SLATE_ARGUMENT( UEdGraphNode*, GraphNode ) SLATE_ATTRIBUTE( ECheckBoxState, ToggleButtonCheck ) SLATE_ATTRIBUTE( FString, Text ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_EVENT( FOnCommentBubbleToggled, OnToggled ) SLATE_ATTRIBUTE( FText, HintText ) SLATE_ATTRIBUTE( FSlateColor, ColorAndOpacity ) SLATE_ARGUMENT( bool, AllowPinning ) SLATE_ARGUMENT( bool, EnableTitleBarBubble ) SLATE_ARGUMENT( bool, EnableBubbleCtrls ) SLATE_ARGUMENT( bool, InvertLODCulling ) SLATE_ATTRIBUTE( EGraphRenderingLOD::Type, GraphLOD ) SLATE_EVENT( FIsGraphNodeHovered, IsGraphNodeHovered ) SLATE_END_ARGS()` — the GraphNode this bubble should interact with
- L103 _private prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L104 _private prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L108 _private prototype_ `void TickVisibility(const double InCurrentTime, const float InDeltaTime);` — Updates the comment Visibility
- L112 _private prototype_ `FVector2D GetOffset() const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Returns the offset from the SNode center slot
- L113 _private prototype_ `FVector2f GetOffset2f() const;`
- L116 _private prototype_ `float GetArrowCenterOffset() const;` — Returns the offset to the arrow center accounting for zoom on either the comment bubble or the title bar button based on current state
- L120 _private prototype_ `FVector2D GetSize() const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Returns the bubble size
- L121 _private prototype_ `FVector2f GetSize2f() const;`
- L124 _private prototype_ `bool IsBubbleVisible() const;` — Returns if comment bubble is visible
- L127 _private prototype_ `bool IsScalingAllowed() const;` — Returns if graph scaling can be applied to this bubble
- L130 _private prototype_ `void OnCommentBubbleToggle( ECheckBoxState State );` — Called to display/hide the comment bubble
- L133 _private prototype_ `void SetCommentBubbleVisibility(bool bVisible);` — Directly sets the bubble's visibility, without assuming it was from a user action (no undo transaction, or OnToggled callback)
- L136 _private prototype_ `void OnPinStateToggle( ECheckBoxState State ) const;` — Called when a node's comment bubble pinned state is changed
- L139 _private prototype_ `void UpdateBubble();` — Called to update the bubble widget layout
- L142 _private prototype_ `bool TextBlockHasKeyboardFocus() const;` — Returns if the text block currently has keyboard focus
- L147 _protected prototype_ `FText GetScaleButtonTooltip() const;` — Returns the current scale button tooltip
- L150 _protected prototype_ `EVisibility GetBubbleVisibility() const;` — Called to determine if the comment bubble's current visibility
- L153 _protected prototype_ `EVisibility GetToggleButtonVisibility() const;` — Called to determine if the toggle button's current visibility
- L156 _protected prototype_ `FSlateColor GetToggleButtonColor() const;` — Returns the color for the toggle bubble including the opacity value
- L159 _protected prototype_ `FSlateColor GetBubbleColor() const;` — Returns the color of the main bubble
- L162 _protected prototype_ `void OnCommentTextCommitted( const FText& NewText, ETextCommit::Type CommitInfo );` — Called when the comment text is committed
- L164 _protected prototype_ `FSlateColor GetTextBackgroundColor() const;`
- L165 _protected prototype_ `FSlateColor GetTextForegroundColor() const;`
- L166 _protected prototype_ `FSlateColor GetReadOnlyTextForegroundColor() const;`
- L168 _protected prototype_ `ECheckBoxState GetToggleButtonCheck() const;` — Returns bubble toggle check state
- L171 _protected prototype_ `ECheckBoxState GetPinnedButtonCheck() const;` — Returns pinned check state
- L174 _protected prototype_ `bool IsReadOnly() const;` — Called to determine if the comment bubble is readonly
- L179 _protected member_ `UEdGraphNode* GraphNode;` — The GraphNode this widget interacts with
- L181 _protected member_ `TSharedPtr<SMultiLineEditableTextBox> TextBlock;` — Cached inline editable text box
- L184 _protected member_ `TAttribute<FSlateColor> ColorAndOpacity;` — The Comment Bubble color and opacity value
- L186 _protected member_ `TAttribute<FString> CommentAttribute;` — Attribute to query node comment
- L188 _protected member_ `TAttribute<EGraphRenderingLOD::Type> GraphLOD;` — Attribute to query current LOD
- L190 _protected member_ `TAttribute<FText> HintText;` — Hint Text
- L192 _protected member_ `TAttribute<ECheckBoxState> ToggleButtonCheck;` — Toggle button checked state
- L195 _protected member_ `FOnTextCommitted OnTextCommittedDelegate;` — Optional delegate to call when the comment text is committed
- L197 _protected member_ `FOnCommentBubbleToggled OnToggledDelegate;` — Optional delegate to call when the comment bubble is toggled
- L199 _protected member_ `FIsGraphNodeHovered IsGraphNodeHovered;` — Delegate to determine if the graph node is currently hovered
- L202 _protected member_ `float BubbleLuminance;` — The luminance (R + G + B) of the bubble's color, used to control text foreground color
- L204 _protected member_ `bool bAllowPinning;` — Allow pin behaviour
- L206 _protected member_ `bool bEnableBubbleCtrls;` — Allow in bubble controls
- L208 _protected member_ `bool bInvertLODCulling;` — Invert the LOD culling behavior, used by comment nodes
- L210 _protected member_ `bool bEnableTitleBarBubble;` — Enable the title bar bubble toggle
- L212 _protected member_ `float OpacityValue;` — Used to Control hover fade up/down for widgets
- L214 _protected member_ `FString CachedComment;` — Cached comment
- L216 _protected member_ `FText CachedCommentText;` — Cached FText comment

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API GRAPHEDITOR_API`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal( bool, FIsGraphNodeHovered );`
- L31 _prototype_ `DECLARE_DELEGATE_RetVal( bool, FIsGraphNodeHovered );`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCommentBubbleToggled, bool );`
- L32 _prototype_ `DECLARE_DELEGATE_OneParam( FOnCommentBubbleToggled, bool );`

### `Source/Editor/GraphEditor/Public/SGraphActionMenu.h` (Public)


#### class `SDefaultGraphActionWidget`  
`class SDefaultGraphActionWidget : public SCompoundWidget`  
_L61-74_
- inherits: `SCompoundWidget`
- desc: Default widget for GraphActionMenu
- L63 _private function_ `SLATE_BEGIN_ARGS( SDefaultGraphActionWidget )`
- L64 _private prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCreateWidgetForActionData* InCreateData);`
- L68 _private prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L71 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The item that we want to display with this widget
- L73 _private member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate executed when mouse button goes down

#### struct `FCreateWidgetForActionData`  
`struct FCreateWidgetForActionData`  
_L76-99_
- L79 _public member_ `bool bHandleMouseButtonDown;` — True if we want to use the mouse delegate
- L81 _public member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate for mouse button going down
- L83 _public member_ `TSharedPtr< FEdGraphSchemaAction > Action;` — The action being used for the widget
- L85 _public member_ `FIsSelected IsRowSelectedDelegate;` — The delegate to determine if the current action is selected in the row
- L87 _public member_ `FOnRenameRequestActionNode* const OnRenameRequest;` — This will be returned, hooked up to request a rename
- L89 _public member_ `TAttribute<FText> HighlightText;` — The text to highlight
- L91 _public member_ `bool bIsReadOnly;` — True if the widget should be read only - no renaming allowed
- L93 _public function_ `FCreateWidgetForActionData(FOnRenameRequestActionNode* const InOnRenameRequest) : OnRenameRequest(InOnRenameRequest) , bIsReadOnly(false)`

#### struct `FCustomExpanderData`  
`struct FCustomExpanderData`  
_L101-111_
- L104 _public member_ `TSharedPtr<ITableRow> TableRow;` — The menu row associated with the widget being customized
- L107 _public member_ `TSharedPtr<FEdGraphSchemaAction> RowAction;` — The action associated with the menu row being customized
- L110 _public member_ `TSharedPtr<SPanel> WidgetContainer;` — The widget container that the custom expander will belong to

#### class `SGraphActionMenu`  
`class SGraphActionMenu : public SCompoundWidget, public FGCObject`  
_L114-412_
- inherits: `SCompoundWidget,FGCObject`
- desc: Class that displays a list of graph actions and them to be searched and selected
- L118 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SWidget>, FOnCreateWidgetForAction, FCreateWidgetForActionData* const );` — Delegate that can be used to create a widget for a particular action
- L120 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SExpanderArrow>, FOnCreateCustomRowExpander, FCustomExpanderData const& );` — Delegate that can be used to create a custom "expander" widget for a particular row
- L122 _public prototype_ `DECLARE_DELEGATE_TwoParams( FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type );` — Delegate executed when an action is selected
- L124 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnActionDoubleClicked, const TArray< TSharedPtr<FEdGraphSchemaAction> >& );` — Delegate executed when an action is double clicked
- L126 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( FReply, FOnActionDragged, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, const FPointerEvent& );` — Delegate executed when an action is dragged
- L128 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( FReply, FOnCategoryDragged, const FText&, const FPointerEvent& );` — Delegate executed when a category is dragged
- L130 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnCollectAllActions, FGraphActionListBuilderBase& );` — Delegate executed when the list of all actions needs to be refreshed
- L132 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnCollectStaticSections, TArray<int32>& ) DECLARE_DELEGATE_ThreeParams( FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when the list of all actions needs to be refreshed, should return any sections that should always be visible, even if they don't have children.
- L136 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FCanRenameSelectedAction, TWeakPtr< FGraphActionNode > );` — Delegate executed to check if the selected action is valid for renaming
- L138 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( FText, FGetSectionTitle, int32 );` — Delegate to get the name of a section if the widget is a section separator.
- L140 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedPtr<IToolTip>, FGetSectionToolTip, int32 );` — Delegate to get the tooltip of a section if the widget is a section separator.
- L142 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<SWidget>, FGetSectionWidget, TSharedRef<SWidget>, int32 );` — Delegate to get the widget that appears on the section bar in the section separator.
- L144 _public prototype_ `DECLARE_DELEGATE_RetVal( FText, FGetFilterText);` — Delegate to get the filter text
- L146 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnActionMatchesName, FEdGraphSchemaAction*, const FName& );` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L148 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<FGraphActionListBuilderBase>, FOnGetActionList);` — Delegate that can be used to create and/or get a custom action list.
- L150 _public function_ `SLATE_BEGIN_ARGS(SGraphActionMenu) : _AutoExpandActionMenu(false) , _AlphaSortItems(true) , _SortItemsRecursively(true) , _ShowFilterTextBox(true) , _UseSectionStyling(false) , _bAllowPreselectedItemActivation(false) , _DefaultRowExpanderBaseIndentLevel(0) , _GraphObj(nullptr) , _bAutomaticallySelectSingleAction(false)`
- L162 _public prototype_ `SLATE_EVENT( FOnActionSelected, OnActionSelected ) SLATE_EVENT( FOnActionDoubleClicked, OnActionDoubleClicked ) SLATE_EVENT( FOnActionDragged, OnActionDragged ) SLATE_EVENT( FOnCategoryDragged, OnCategoryDragged ) SLATE_EVENT( FOnContextMenuOpening, OnContextMenuOpening ) SLATE_EVENT( FOnCreateWidgetForAction, OnCreateWidgetForAction ) SLATE_EVENT( FOnCreateCustomRowExpander, OnCreateCustomRowExpander ) SLATE_EVENT( FOnGetActionList, OnGetActionList ) SLATE_EVENT( FOnCollectAllActions, OnCollectAllActions ) SLATE_EVENT( FOnCollectStaticSections, OnCollectStaticSections ) SLATE_EVENT( FOnCategoryTextCommitted, OnCategoryTextCommitted ) SLATE_EVENT( FCanRenameSelectedAction, OnCanRenameSelectedAction ) SLATE_EVENT( FGetSectionTitle, OnGetSectionTitle ) SLATE_EVENT( FGetSectionToolTip, OnGetSectionToolTip ) SLATE_EVENT( FGetSectionWidget, OnGetSectionWidget ) SLATE_EVENT( FGetFilterText, OnGetFilterText ) SLATE_EVENT( FOnActionMatchesName, OnActionMatchesName ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_ARGUMENT( bool, AlphaSortItems ) SLATE_ARGUMENT( bool, SortItemsRecursively ) SLATE_ARGUMENT( bool, ShowFilterTextBox ) SLATE_ARGUMENT( bool, UseSectionStyling ) SLATE_ARGUMENT( bool, bAllowPreselectedItemActivation ) SLATE_ARGUMENT( int32, DefaultRowExpanderBaseIndentLevel ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( bool, bAutomaticallySelectSingleAction ) SLATE_END_ARGS() void Construct( const FArgument ...`
- L195 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject override
- L196 _public prototype_ `virtual FString GetReferencerName() const override;`
- L203 _public prototype_ `void RefreshAllActions(bool bPreserveExpansion, bool bHandleOnSelectionEvent = true);` — Refreshes the actions that this widget should display @param bPreserveExpansion		TRUE if the expansion state of the tree should be preserved @param bHandleOnSelectionEvent		TRUE if the item should be selected and any actions that occur with selection will be handled. FALSE and only selection will occur
- L206 _public prototype_ `void GetSectionExpansion(TMap<int32, bool>& SectionExpansion) const;` — Returns a map of all top level sections and their current expansion state.
- L209 _public prototype_ `void SetSectionExpansion(const TMap<int32, bool>& SectionExpansion);` — Sets the sections to be expanded of all top level sections.
- L213 _protected member_ `TSharedPtr< STreeView< TSharedPtr<FGraphActionNode> > > TreeView;` — Tree view for showing actions
- L215 _protected member_ `TSharedPtr<SSearchBox> FilterTextBox;` — Text box used for searching for actions
- L218 _protected member_ `TSharedPtr<FGraphActionListBuilderBase> AllActions;` — List of all actions we can browser
- L221 _protected member_ `TArray< TSharedPtr<FGraphActionNode> > FilteredActionNodes;` — Flattened list of all actions passing the filter - access via GetFilteredActionNodes to ensure it's up to date
- L224 _protected member_ `TSharedPtr<FGraphActionNode> FilteredRootAction;` — Root of filtered actions tree
- L227 _protected member_ `float SelectedSuggestionScore;` — Stored score for our current selection, so that we can quickly maintain selection when building the list asynchronously
- L229 _protected member_ `int32 SelectedSuggestionSourceIndex;` — Stored index in the AllActions list builder that we think is the best fit
- L231 _protected member_ `TSharedPtr<FGraphActionNode> SelectedAction;` — The actual item selected - possibly redundant to selection information in the treeview, but the tree is rebuilt requently
- L234 _protected member_ `bool bIgnoreUIUpdate;` — Allows us to set selection (via keyboard) without triggering action
- L236 _protected member_ `bool bAutoExpandActionMenu;` — Should we auto-expand categories
- L238 _protected member_ `bool bShowFilterTextBox;` — Should we display the filter text box
- L240 _protected member_ `bool bAlphaSortItems;` — Don't sort items alphabetically
- L242 _protected member_ `bool bSortItemsRecursively;` — If only the top entries should be sorted or subentries as well
- L244 _protected member_ `bool bUseSectionStyling;` — Should the rows and sections be styled like the details panel?
- L246 _protected member_ `bool bIsKeyboardNavigating;` — True if the user is using the keyboard to navigatethe list, halting scoring of newly added entries so that selection is stable
- L248 _protected member_ `bool bAllowPreselectedItemActivation;` — Whether we allow pre-selected items to be activated with a left-click
- L250 _protected member_ `bool bAutomaticallySelectSingleAction;` — Whether to automatically proceed with an action if it's the only one in the list.
- L252 _protected member_ `int32 DefaultRowExpanderBaseIndentLevel;` — The BaseIndentLevel of the default-created row expander. Not used with OnCreateCustomRowExpander.
- L254 _protected member_ `int32 DisplayIndex;` — The slot that the selected item should be displayed at
- L257 _protected member_ `FOnActionSelected OnActionSelected;` — Delegate to call when action is selected
- L259 _protected member_ `FOnActionDoubleClicked OnActionDoubleClicked;` — Delegate to call when action is double clicked
- L261 _protected member_ `FOnActionDragged OnActionDragged;` — Delegate to call when an action is dragged.
- L263 _protected member_ `FOnCategoryDragged OnCategoryDragged;` — Delegate to call when a category is dragged.
- L265 _protected member_ `FOnCreateWidgetForAction OnCreateWidgetForAction;` — Delegate to call to create widget for an action
- L267 _protected member_ `FOnCreateCustomRowExpander OnCreateCustomRowExpander;` — Delegate to call for creating a custom "expander" widget for indenting a menu row with
- L269 _protected member_ `FOnGetActionList OnGetActionList;` — Delegate to call to get a custom action list
- L271 _protected member_ `FOnCollectAllActions OnCollectAllActions;` — Delegate to call to collect all actions
- L273 _protected member_ `FOnCollectStaticSections OnCollectStaticSections;` — Delegate to call to collect all always visible sections
- L275 _protected member_ `FOnCategoryTextCommitted OnCategoryTextCommitted;` — Delegate to call to handle any post-category rename events
- L277 _protected member_ `FCanRenameSelectedAction OnCanRenameSelectedAction;` — Delegate to call to check if a selected action is valid for renaming
- L279 _protected member_ `FGetSectionTitle OnGetSectionTitle;` — Delegate to get the name of a section separator.
- L281 _protected member_ `FGetSectionToolTip OnGetSectionToolTip;` — Delegate to get the tooltip of a section separator.
- L283 _protected member_ `FGetSectionWidget OnGetSectionWidget;` — Delegate to get the widgets of a section separator.
- L285 _protected member_ `FGetFilterText OnGetFilterText;` — Delegate to get the filter text if supplied from an external source
- L287 _protected member_ `FOnActionMatchesName OnActionMatchesName;` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L291 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& KeyEvent) override;` — SWidget interface
- L295 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();` — Get filter text box widget
- L298 _public prototype_ `void GetSelectedActions(TArray< TSharedPtr<FEdGraphSchemaAction> >& OutSelectedActions) const;` — Get action that is currently selected
- L301 _public prototype_ `void OnRequestRenameOnActionNode();` — Initiates a rename on the selected action node, if possible
- L304 _public prototype_ `bool CanRequestRenameOnActionNode() const;` — Queries if a rename on the selected action node is possible
- L307 _public prototype_ `FString GetSelectedCategoryName() const;` — Get category that is currently selected
- L310 _public prototype_ `void GetSelectedCategorySubActions(TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions) const;` — Get category child actions that is currently selected
- L313 _public prototype_ `void GetCategorySubActions(TWeakPtr<FGraphActionNode> InAction, TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions) const;` — Get category child actions for the passed in action
- L324 _public prototype_ `bool SelectItemByName(const FName& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct, int32 SectionId = INDEX_NONE, bool bIsCategory = false );` — Selects an non-creation item in the list, searching by FName, deselects if name is none @param	ItemName		The name of the item to select @param	SelectInfo		The selection type @param	SectionId		If known, the section Id to restrict the selection to, useful in the case of categories where they can exist multiple times @param	bIsCategory		TRUE if the selection is a category, categories obey different rules and it's hard to re-select properly without this knowledge @return					TRUE if the item was successfully selected or the tree cleared, FALSE if unsuccessful
- L327 _public prototype_ `void ExpandCategory(const FText& CategoryName);` — Expands any category with the associated name
- L330 _public prototype_ `bool OnMouseButtonDownEvent( TWeakPtr<FEdGraphSchemaAction> InAction );` — Handler for mouse button going down
- L333 _public prototype_ `void UpdateForNewActions(int32 IdxStart);` — Updates the displayed list starting from IdxStart, useful for async building the display list of actions
- L335 _public prototype_ `void GenerateFilteredItems(bool bPreserveExpansion);` — Regenerated filtered results (FilteredRootAction) based on filter text
- L338 _public member_ `static FString LastUsedFilterText;` — The last typed action within the graph action menu
- L342 _protected prototype_ `FText GetFilterText() const;` — Get current filter text
- L345 _protected prototype_ `void MarkActiveSuggestion();` — Change the selection to reflect the active suggestion
- L348 _protected prototype_ `bool TryToSpawnActiveSuggestion();` — Try to spawn the node reflected by the active suggestion
- L351 _protected prototype_ `bool ShouldExpandNodes() const;` — Returns true if the tree should be autoexpanded
- L354 _protected prototype_ `bool CanRenameNode(TWeakPtr<FGraphActionNode> InNode) const;` — Checks if the passed in node is safe for renaming
- L359 _protected prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called when filter text changes
- L361 _protected prototype_ `void OnFilterTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Called when enter is hit in search box
- L363 _protected prototype_ `void OnGetChildrenForCategory( TSharedPtr<FGraphActionNode> InItem, TArray< TSharedPtr<FGraphActionNode> >& OutChildren );` — Get children
- L365 _protected prototype_ `TSharedRef<ITableRow> MakeWidget( TSharedPtr<FGraphActionNode> InItem, const TSharedRef<STableViewBase>& OwnerTable, bool bIsReadOnly );` — Create widget for the supplied node
- L373 _protected prototype_ `void OnItemSelected( TSharedPtr< FGraphActionNode > InSelectedItem, ESelectInfo::Type SelectInfo );` — Called when tree item is selected @param	InSelectedItem	The action node that is being selected @param	SelectInfo		Selection type - Only OnMouseClick and OnKeyPress will trigger a call to HandleSelection
- L382 _protected prototype_ `bool HandleSelection( TSharedPtr< FGraphActionNode > &InSelectedItem, ESelectInfo::Type InSelectionType );` — Executes the selection delegate providing it has been bound, and the provided action node given is valid and is an action node @param InselectedItem	The graph action node selected @return true if item selection delegate was executed
- L385 _protected prototype_ `void OnItemDoubleClicked( TSharedPtr< FGraphActionNode > InClickedItem );` — Called when tree item is double clicked
- L387 _protected prototype_ `FReply OnItemDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );` — Called when tree item dragged
- L389 _protected prototype_ `void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit, TWeakPtr< FGraphActionNode > InAction);` — Callback when rename text is committed
- L391 _protected prototype_ `void OnItemScrolledIntoView( TSharedPtr<FGraphActionNode> InActionNode, const TSharedPtr<ITableRow>& InWidget );` — Handler for when an item has scrolled into view after having been requested to do so
- L393 _protected prototype_ `void OnSetExpansionRecursive(TSharedPtr<FGraphActionNode> InTreeNode, bool bInIsItemExpanded);` — Callback for expanding tree items recursively
- L395 _protected prototype_ `void ScoreAndAddActions(int32 StartingIndex = INDEX_NONE);` — Helper function for adding and scoring actions from our builder
- L398 _protected prototype_ `void SelectPreviousAction(int32 Num = 1);` — Helper functions for keyboard interaction
- L399 _protected prototype_ `void SelectNextAction(int32 Num = 1);`
- L400 _protected prototype_ `void SelectFirstAction();`
- L401 _protected prototype_ `void SelectLastAction();`
- L403 _protected prototype_ `TSharedPtr<FGraphActionNode> GetFirstAction();` — General helper functions for accessing the filtered tree
- L404 _protected prototype_ `const TArray< TSharedPtr<FGraphActionNode> >& GetFilteredActionNodes(int32* OutSelectedIndex = nullptr);`
- L405 _protected prototype_ `int32 GetTotalLeafNodes() const;`
- L408 _private member_ `TArray<UEdGraphPin*> DraggedFromPins;` — The pins that have been dragged off of to prompt the creation of this action menu.
- L411 _private member_ `UEdGraph* GraphObj;` — The graph that this menu is being constructed in

#### Free symbols / members of external scopes

- L36 _macro_ `#define UE_API GRAPHEDITOR_API`
- L56 _delegate_ `DECLARE_DELEGATE( FOnRenameRequestActionNode );` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L56 _prototype_ `DECLARE_DELEGATE( FOnRenameRequestActionNode );` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L58 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FCreateWidgetMouseButtonDown, TWeakPtr<FEdGraphSchemaAction> );` — Delegate executed when the mouse button goes down
- L58 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FCreateWidgetMouseButtonDown, TWeakPtr<FEdGraphSchemaAction> );` — Delegate executed when the mouse button goes down
- L118 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SWidget>, FOnCreateWidgetForAction, FCreateWidgetForActionData* const );` — Delegate that can be used to create a widget for a particular action
- L120 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<SExpanderArrow>, FOnCreateCustomRowExpander, FCustomExpanderData const& );` — Delegate that can be used to create a custom "expander" widget for a particular row
- L122 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type );` — Delegate executed when an action is selected
- L124 _delegate_ `DECLARE_DELEGATE_OneParam( FOnActionDoubleClicked, const TArray< TSharedPtr<FEdGraphSchemaAction> >& );` — Delegate executed when an action is double clicked
- L126 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( FReply, FOnActionDragged, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, const FPointerEvent& );` — Delegate executed when an action is dragged
- L128 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( FReply, FOnCategoryDragged, const FText&, const FPointerEvent& );` — Delegate executed when a category is dragged
- L130 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCollectAllActions, FGraphActionListBuilderBase& );` — Delegate executed when the list of all actions needs to be refreshed
- L132 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCollectStaticSections, TArray<int32>& ) DECLARE_DELEGATE_ThreeParams( FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when the list of all actions needs to be refreshed, should return any sections that should always be visible, even if they don't have children.
- L134 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnCategoryTextCommitted, const FText&, ETextCommit::Type, TWeakPtr< FGraphActionNode >);` — Delegate executed when a category is being renamed so any post-rename actions can be handled
- L136 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FCanRenameSelectedAction, TWeakPtr< FGraphActionNode > );` — Delegate executed to check if the selected action is valid for renaming
- L138 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( FText, FGetSectionTitle, int32 );` — Delegate to get the name of a section if the widget is a section separator.
- L140 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedPtr<IToolTip>, FGetSectionToolTip, int32 );` — Delegate to get the tooltip of a section if the widget is a section separator.
- L142 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<SWidget>, FGetSectionWidget, TSharedRef<SWidget>, int32 );` — Delegate to get the widget that appears on the section bar in the section separator.
- L144 _delegate_ `DECLARE_DELEGATE_RetVal( FText, FGetFilterText);` — Delegate to get the filter text
- L146 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnActionMatchesName, FEdGraphSchemaAction*, const FName& );` — Delegate to check if an action matches a specified name (used for renaming items etc.)
- L148 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<FGraphActionListBuilderBase>, FOnGetActionList);` — Delegate that can be used to create and/or get a custom action list.

### `Source/Editor/GraphEditor/Public/SGraphEditorActionMenu.h` (Public)


#### class `SGraphEditorActionMenu`  
`class SGraphEditorActionMenu : public SBorder`  
_L29-69_
- inherits: `SBorder`
- L32 _public function_ `SLATE_BEGIN_ARGS( SGraphEditorActionMenu ) : _GraphObj( static_cast<UEdGraph*>(NULL) ) , _NewNodePosition( FVector2f::ZeroVector ) , _AutoExpandActionMenu( false )`
- L38 _public prototype_ `SLATE_ARGUMENT( UEdGraph*, GraphObj ) SLATE_ARGUMENT( FDeprecateSlateVector2D, NewNodePosition ) SLATE_ARGUMENT( TArray<UEdGraphPin*>, DraggedFromPins ) SLATE_ARGUMENT( SGraphEditor::FActionMenuClosed, OnClosedCallback ) SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_EVENT( SGraphActionMenu::FOnCreateWidgetForAction, OnCreateWidgetForAction ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L48 _public prototype_ `~SGraphEditorActionMenu();`
- L50 _public prototype_ `void RefreshAllActions();`
- L52 _public prototype_ `TSharedRef<SEditableTextBox> GetFilterTextBox();`
- L55 _protected member_ `UEdGraph* GraphObj;`
- L56 _protected member_ `TArray<UEdGraphPin*> DraggedFromPins;`
- L57 _protected member_ `FDeprecateSlateVector2D NewNodePosition;`
- L58 _protected member_ `bool AutoExpandActionMenu;`
- L60 _protected member_ `SGraphEditor::FActionMenuClosed OnClosedCallback;`
- L61 _protected member_ `SGraphActionMenu::FOnCreateWidgetForAction OnCreateWidgetForAction;`
- L63 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`
- L65 _protected prototype_ `void OnActionSelected( const TArray< TSharedPtr<FEdGraphSchemaAction> >& SelectedAction, ESelectInfo::Type InSelectionType );`
- L68 _protected prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);` — Callback used to populate all actions list in SGraphActionMenu

### `Source/Editor/GraphEditor/Public/SGraphNode.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SNodeTitle>`  
_L64-67_
- L66 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SNodeTitle`  
`class SNodeTitle : public SCompoundWidget`  
_L69-126_
- inherits: `SCompoundWidget`
- L72 _public function_ `SLATE_BEGIN_ARGS(SNodeTitle) : _StyleSet(&FAppStyle::Get()) , _Style(TEXT("Graph.Node.NodeTitle")) , _ExtraLineStyle(TEXT("Graph.Node.NodeTitleExtraLines"))`
- L78 _public prototype_ `SLATE_ARGUMENT(const ISlateStyle*, StyleSet)`
- L93 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L97 _public prototype_ `FText GetHeadTitle() const;` — Returns the main title for the node
- L100 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetTitleSize() const;` — Get the size of this title the last time it was drawn
- L103 _public prototype_ `void MarkDirty();` — Mark the cached title dirty
- L106 _protected member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;`
- L107 _protected member_ `FNodeTextCache NodeTitleCache;`
- L108 _protected member_ `FName ExtraLineStyle;`
- L109 _protected member_ `const ISlateStyle* StyleSet;`
- L112 _protected member_ `FText CachedHeadTitle;` — The cached head title to return
- L115 _protected member_ `TAttribute< FText > TitleText;` — The title text to use, auto-binds to get the title if not set externally
- L118 _protected member_ `FVector2f CachedSize;` — The cached size of the title
- L122 _protected prototype_ `FText GetNodeTitle() const;` — Gets the expected node title
- L125 _protected prototype_ `void RebuildWidget();` — Rebuilds the widget if needed

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNode>`  
_L132-135_
- L66 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNode`  
`class SGraphNode : public SNodePanel::SNode`  
_L137-534_
- inherits: `SNodePanel::SNode`
- L141 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — SWidget interface
- L142 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L143 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L144 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L146 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L147 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L148 _public prototype_ `virtual FReply OnMouseButtonDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent ) override;`
- L150 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;`
- L151 _public prototype_ `virtual void OnToolTipClosing() override;`
- L153 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L157 _public prototype_ `virtual void MoveTo( const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true ) override;` — SNodePanel::SNode interface
- L158 _public prototype_ `virtual FVector2f GetPosition2f() const override;`
- L159 _public prototype_ `virtual FVector2f GetDesiredSizeForMarquee2f() const override;`
- L160 _public prototype_ `virtual FString GetNodeComment() const override;`
- L161 _public prototype_ `virtual UObject* GetObjectBeingDisplayed() const override;`
- L165 _public prototype_ `void SetIsEditable(TAttribute<bool> InIsEditable);` — Set attribute for determining if widget is editable
- L168 _public prototype_ `virtual bool IsNodeEditable() const;` — Returns if widget is editable, additionally considers if the owning graph is read only
- L171 _public prototype_ `void SetDoubleClickEvent(FSingleNodeEvent InDoubleClickEvent);` — Set event when node is double clicked
- L174 _public prototype_ `virtual void SetOwner( const TSharedRef<SGraphPanel>& OwnerPanel );` — @param OwnerPanel  The GraphPanel that this node belongs to
- L177 _public prototype_ `FString GetEditableNodeTitle() const;` — @return the editable title for a node
- L180 _public prototype_ `FText GetEditableNodeTitleAsText() const;` — @return the editable title for a node
- L183 _public prototype_ `virtual FSlateColor GetNodeTitleColor() const;` — @return the tint for the node's title image
- L186 _public prototype_ `FSlateColor GetNodeCommentColor() const;` — @return the tint for the node's comment
- L189 _public prototype_ `virtual FSlateColor GetNodeBodyColor() const;` — @return the tint for the node's main body
- L192 _public prototype_ `virtual const FSlateBrush * GetNodeBodyBrush() const;` — @return the image brush to use for the node
- L195 _public prototype_ `virtual FSlateColor GetNodeTitleIconColor() const;` — @return the tint for the node's title icon
- L198 _public prototype_ `virtual FLinearColor GetNodeTitleTextColor() const;` — @return the tint for the node's title text
- L201 _public prototype_ `virtual FText GetNodeTooltip() const;` — @return the tooltip to display when over the node
- L204 _public prototype_ `UEdGraphNode* GetNodeObj() const;` — @return the node being observed by this widget
- L207 _public prototype_ `virtual TSharedRef<SGraphNode> GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — @return the node under the mouse (either this node or one of its children)
- L209 _public prototype_ `TSharedPtr<SGraphPanel> GetOwnerPanel() const;`
- L214 _public prototype_ `virtual void UpdateGraphNode();` — Update this GraphNode to match the data that it is observing
- L217 _public prototype_ `virtual void CreatePinWidgets();` — Create the widgets for pins on the node
- L220 _public prototype_ `virtual void CreateStandardPinWidget(UEdGraphPin* Pin);` — Create a single pin widget
- L227 _public prototype_ `void GetPins( TSet< TSharedRef<SWidget> >& AllPins ) const;` — Get all the pins found on this node. @param AllPins  The set of pins found on this node.
- L228 _public prototype_ `void GetPins( TArray< TSharedRef<SWidget> >& AllPins ) const;`
- L238 _public prototype_ `virtual TSharedPtr<SGraphPin> GetHoveredPin( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) const;` — Find the pin that is hovered. @param MyGeometry  The geometry of the node @param MouseEvent  Information about the mouse @return A pointer to the pin widget hovered in this node, or invalid pointer if none.
- L240 _public prototype_ `TSharedPtr<SGraphPin> FindWidgetForPin( UEdGraphPin* ThePin ) const;`
- L242 _public prototype_ `void PlaySpawnEffect();`
- L245 _public prototype_ `UE::Slate::FDeprecateVector2DResult NodeCoordToGraphCoord( const UE::Slate::FDeprecateVector2DParameter& PanelSpaceCoordinate ) const;` — Given a coordinate in SGraphNode space, return the same coordinate in graph space while taking zoom and panning of the parent graph into account
- L247 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetContentScale() const;`
- L248 _public prototype_ `FLinearColor GetColorAndOpacity() const;`
- L249 _public prototype_ `FLinearColor GetPinLabelColorAndOpacity() const;`
- L252 _public prototype_ `void SetVerifyTextCommitEvent(FOnNodeVerifyTextCommit InOnVerifyTextCommit);` — Set event when text is committed on the node
- L254 _public prototype_ `void SetTextCommittedEvent(FOnNodeTextCommitted InDelegate);` — Set event when text is committed on the node
- L256 _public prototype_ `void SetDisallowedPinConnectionEvent(SGraphEditor::FOnDisallowedPinConnection InOnDisallowedPinConnection);` — Set event when the user generates a warning tooltip because a connection was invalid
- L258 _public prototype_ `virtual void OnCommentTextCommitted(const FText& NewComment, ETextCommit::Type CommitInfo);` — called to replace this nodes comment text
- L260 _public prototype_ `virtual void OnCommentBubbleToggled(bool bInCommentBubbleVisible);` — called when the node's comment bubble is toggled
- L262 _public function_ `bool IsRenamePending() const` — returns true if a rename is pending on this node
- L265 _public function_ `virtual void RequestRenameOnSpawn()` — Requests a rename when the node was initially spawned
- L271 _public prototype_ `void RequestRename();` — flags node as rename pending if supported
- L274 _public prototype_ `void ApplyRename();` — Sets node into rename state if supported
- L277 _public prototype_ `void CancelRename();` — Cancels the rename editing mode
- L280 _public prototype_ `virtual FSlateRect GetTitleRect() const;` — return rect of the title area
- L283 _public prototype_ `void NotifyDisallowedPinConnection(const class UEdGraphPin* PinA, const class UEdGraphPin* PinB) const;` — Called from drag drop code when a disallowed connection is hovered
- L286 _public function_ `UE::Slate::FDeprecateVector2DResult GetUnscaledPosition() const` — Gets the unscaled position of the node from the last tick
- L289 _public prototype_ `EGraphRenderingLOD::Type GetCurrentLOD() const;` — Returns the current Node LOD or Highest LOD if unable to query
- L292 _public prototype_ `virtual void RefreshErrorInfo();` — Called when GraphNode changes its error information, may be called when no change has actually occurred:
- L295 _public prototype_ `void InvalidateGraphData();` — Called when ed graph data is cleared, indicating this widget can no longer safely access GraphNode - forwards call to owned pins:
- L298 _public function_ `virtual bool IsHidingPinWidgets() const` — Returns true if the node is hiding its pins
- L301 _public function_ `virtual TOptional<const FSlateBrush*> GetPinBorder(const SGraphPin* InGraphPin) const` — Allows the node to override the pin border image
- L304 _public function_ `virtual TOptional<FSlateColor> GetHighlightColor(const SGraphPin* InGraphPin) const` — Allows the node to override the pin highlight color
- L307 _public function_ `virtual TOptional<FSlateColor> GetPinTextColor(const SGraphPin* InGraphPin) const` — Allows the node to override the pin text color
- L310 _public prototype_ `TArray<FArrangedWidget> GetArrangedSnappedChildNodes(const FGeometry& Geometry);` — snapping:
- L311 _public prototype_ `TSharedPtr<SGraphNode> GetSnappedChildForPosition(const FGeometry& Geometry, const FVector2f& Position, FVector2f& OutPositionInNode);`
- L312 _public prototype_ `FGeometry GetNodeGeometry(const FGeometry& Geometry) const;`
- L313 _public prototype_ `void DrawChildrenNodeShadow( const FGraphPanelSelectionSet& SelectionSet, FSlateWindowElementList& OutDrawElements, int32 NodeShadowsLayerId, const FGeometry& Geometry, FLinearColor Color);`
- L315 _public prototype_ `void GetPinsToDraw( TSet< TSharedRef<SWidget> >& AllPins ) const;` — Returns the set of pins that should have their connections drawn, including nested pins
- L317 _public prototype_ `void GetPinsIncludingSnappedChildren( TSet< TSharedRef<SWidget> >& AllPins ) const;` — Returns all of the pins, including those nested within this node
- L318 _public prototype_ `void ForEachNodeIncludingChildren(TFunctionRef<void(const TSharedRef<SGraphNode>&)> Ftor);`
- L319 _public prototype_ `void ForEachPinOnSnappedChild(TFunctionRef<void(const TSharedRef<SGraphPin>&)> Ftor) const;`
- L320 _public prototype_ `void ForEachNodeSnappedToControlFlowPin(TFunctionRef<void(const TSharedRef<SGraphNode>&)> Ftor) const;`
- L321 _public prototype_ `void ForEachNodeSnappedToDataPin(TFunctionRef<void(const TSharedRef<SGraphNode>&)> Ftor) const;`
- L323 _protected prototype_ `SGraphNode();`
- L325 _protected prototype_ `void PositionThisNodeBetweenOtherNodes(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup, UEdGraphNode* PreviousNode, UEdGraphNode* NextNode, float HeightAboveWire) const;`
- L326 _protected prototype_ `void PositionThisNodeBetweenOtherNodes(const TMap< UObject*, TSharedRef<SNode> >& NodeToWidgetLookup, TSet<UEdGraphNode*>& PreviousNodes, TSet<UEdGraphNode*>& NextNodes, float HeightAboveWire) const;`
- L327 _protected prototype_ `void PositionThisNodeBetweenOtherNodes(const FVector2f& PrevPos, const FVector2f& NextPos, float HeightAboveWire) const;`
- L332 _protected prototype_ `static bool CanAllowInteractionUsingDragDropOp( const UEdGraphNode* GraphNodePtr, const TSharedPtr<FActorDragDropOp>& DragDropOp );` — Check whether drag and drop functionality is permitted on the given node
- L339 _protected prototype_ `FText GetErrorMsgToolTip() const;` — Function to get error description string @return string to be displayed as tooltip.
- L346 _protected prototype_ `virtual void AddPin( const TSharedRef<SGraphPin>& PinToAdd );` — Add a new pin to this graph node. The pin must be newly created. @param PinToAdd   A new pin to add to this GraphNode.
- L349 _protected prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const;` — Hook that allows derived classes to supply their own SGraphPin derivatives for any pin.
- L354 _protected function_ `virtual TSharedPtr<SToolTip> GetComplexTooltip()` — Override this to provide support for an 'expensive' tooltip widget that is only built on demand
- L357 _protected function_ `virtual void CreateBelowWidgetControls(TSharedPtr<SVerticalBox> MainBox)` — Override this to add widgets below the node and pins
- L360 _protected function_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)` — Override this to add widgets below the pins but above advanced view arrow
- L363 _protected function_ `virtual TOptional<ETextOverflowPolicy> GetNameOverflowPolicy() const` — Determines how the node title overflow is handled
- L366 _protected prototype_ `virtual bool IsNameReadOnly () const;` — Helper function to check if node can be renamed
- L369 _protected prototype_ `bool OnVerifyNameTextChanged ( const FText& InText, FText& OutErrorMessage );` — Called when text is being committed to check for validity
- L372 _protected prototype_ `void OnNameTextCommited ( const FText& InText, ETextCommit::Type CommitInfo ) ;` — Called when text is committed on the node
- L375 _protected function_ `FSlateColor GetErrorColor() const` — Helper function to set the error color for the node
- L378 _protected prototype_ `EVisibility VisualWarningVisibility() const;` — Controls wether to show or not the visual warning message
- L381 _protected prototype_ `FText GetVisualWarningMsgToolTip() const;` — Function to get a visual warning description string(visual warnings does not break the build)
- L384 _protected prototype_ `FSlateColor GetVisualWarningColor() const;` — Helper function to set the error color for the node
- L387 _protected function_ `FString GetErrorMessage() const` — Helper function to get any error text for the node
- L390 _protected prototype_ `virtual void UpdateErrorInfo();` — Called to set error text on the node
- L393 _protected prototype_ `void SetupErrorReporting();` — Set-up the error reporting widget for the node
- L396 _protected prototype_ `virtual bool UseLowDetailNodeTitles() const;` — Should we use low-detail node titles?
- L401 _public function_ `virtual bool UseLowDetailPinNames() const` — Should we use low-detail pin names?
- L406 _protected function_ `virtual FSlateColor GetCommentColor() const` — Return the desired comment bubble color
- L411 _protected prototype_ `virtual void CreateAdvancedViewArrow(TSharedPtr<SVerticalBox> MainBox);` — Create button to show/hide advanced pins
- L414 _protected prototype_ `virtual EVisibility AdvancedViewArrowVisibility() const;` — Returns visibility of AdvancedViewButton
- L417 _protected prototype_ `virtual void OnAdvancedViewChanged( const ECheckBoxState NewCheckedState );` — Show/hide advanced view
- L420 _protected prototype_ `virtual ECheckBoxState IsAdvancedViewChecked() const;` — hidden == unchecked, shown == checked
- L423 _protected prototype_ `virtual const FSlateBrush* GetAdvancedViewArrow() const;` — Up when shown, down when hidden
- L426 _protected prototype_ `bool IsSelectedExclusively() const;` — Checks if the node is the only node selected
- L428 _protected function_ `virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget)`
- L429 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle);`
- L432 _protected prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget();` — Optionally create a widget to dock to the right in the title bar of the node.
- L435 _protected prototype_ `virtual TSharedRef<SWidget> CreateNodeContentArea();` — Create the inner node content area, including the left/right pin boxes
- L440 _protected function_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox)` — Override this to create a button to add pins on the input side of the node
- L443 _protected function_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox)` — Override this to create a button to add pins on the output side of the node
- L446 _protected prototype_ `TSharedRef<SWidget> AddPinButtonContent(FText PinText, FText PinTooltipText, bool bRightSide = true, FString DocumentationExcerpt = FString(), TSharedPtr<SToolTip> CustomTooltip = NULL);` — Creates widget for an Add pin button, which can then be added to the node
- L449 _protected prototype_ `virtual EVisibility IsAddPinButtonVisible() const;` — Checks whether Add pin button should currently be visible
- L452 _protected function_ `virtual FReply OnAddPin()` — Callback function executed when Add pin button is clicked
- L455 _protected prototype_ `virtual void PopulateMetaTag(class FGraphNodeMetaData* TagMeta) const;` — Populate a meta data tag with information about this graph node
- L458 _protected prototype_ `bool ShouldPinBeHidden(const UEdGraphPin* InPin) const;` — Returns TRUE if the input pin should be hidden from view
- L461 _protected prototype_ `virtual TSharedPtr<SWidget> GetEnabledStateWidget() const;` — Returns the widget to use for the enabled state of the node
- L464 _protected prototype_ `virtual TSharedRef<SWidget> CreateIconWidget();` — Returns the widget to use for the corner icon of the node
- L468 _protected member_ `TArray< TSharedRef<SGraphPin> > InputPins;` — Input pin widgets on this node
- L470 _protected member_ `TArray< TSharedRef<SGraphPin> > OutputPins;` — Output pin widgets on this node
- L472 _protected member_ `TWeakPtr<SGraphPanel> OwnerGraphPanelPtr;` — The GraphPanel within in which this node resides.
- L474 _protected member_ `UEdGraphNode* GraphNode;` — The GraphNode being observed by this widget
- L476 _protected member_ `TSharedPtr<SVerticalBox> LeftNodeBox;` — The area where input pins reside
- L478 _protected member_ `TSharedPtr<SVerticalBox> RightNodeBox;` — The area where output pins reside
- L480 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableText;` — Used to display the name of the node and allow renaming of the node
- L482 _protected member_ `TSharedPtr<class IErrorReportingWidget> ErrorReporting;` — Error handling widget
- L484 _protected member_ `TSharedPtr<class IErrorReportingWidget> VisualWarningReporting;` — Visual Warning handling widget
- L486 _protected member_ `FCurveSequence SpawnAnim;`
- L487 _protected member_ `FCurveHandle ZoomCurve;`
- L488 _protected member_ `FCurveHandle FadeCurve;`
- L492 _protected member_ `FMargin TitleBorderMargin = FMargin(10.f, 5.f, 30.f, 3.f);` — The margin used by the border containing the title. Can be changed by child classes if necessary. The extra padding on the right is for making the color spill stretch well past the node title
- L495 _protected member_ `TAttribute<bool> IsEditable;` — Is this node editable
- L497 _protected member_ `FSingleNodeEvent OnDoubleClick;`
- L500 _protected member_ `bool bProvidedComplexTooltip;` — Is the current tooltip a complex one that should be dropped when the tooltip is no longer displayed?
- L503 _protected member_ `bool bRenameIsPending;` — Is a rename operation pending
- L505 _protected member_ `FOnNodeVerifyTextCommit OnVerifyTextCommit;` — Called whenever the text on the node is being committed interactively by the user, validates the string for commit
- L507 _protected member_ `FOnNodeTextCommitted OnTextCommitted;` — Called whenever the text on the node is committed interactively by the user
- L509 _protected member_ `SGraphEditor::FOnDisallowedPinConnection OnDisallowedPinConnection;` — Called when the user generates a warning tooltip because a connection was invalid
- L511 _protected member_ `FString ErrorMsg;` — Used to report errors on the node
- L513 _protected member_ `FSlateColor ErrorColor;` — Used to set the error color
- L515 _protected member_ `FString VisualWarningMsg;` — Used to report visual warnings on the node (does not break build)
- L517 _protected member_ `FSlateColor VisualWarningColor;` — Used to set the soft error color
- L521 _protected member_ `FVector2f CachedUnscaledPosition;` — Caches true position of node
- L524 _protected member_ `FLinearColor IconColor;` — Cached icon color for the node
- L527 _protected member_ `const class UGraphEditorSettings* Settings;` — Cached pointer to graph editor settings
- L530 _private member_ `TSharedPtr<SLevelOfDetailBranchNode> TitleLODBranchNode;`
- L532 _private member_ `TSharedPtr<SVerticalBox> ControlFlowSequence;` — ref?
- L533 _private member_ `TWeakPtr<SGraphNode> SnapParent;` — dag so technically we can keep an owning reference.. but do we trust ourselves?

#### Free symbols / members of external scopes

- L40 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphNodeComment.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeComment>`  
_L32-35_
- L34 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeComment`  
`class SGraphNodeComment : public SGraphNodeResizable`  
_L37-149_
- inherits: `SGraphNodeResizable`
- L40 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeComment)`
- L41 _public prototype_ `SLATE_END_ARGS()`
- L45 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L46 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L47 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L48 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L52 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L53 _public prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L54 _public function_ `virtual bool ShouldAllowCulling() const override`
- L55 _public prototype_ `virtual int32 GetSortDepth() const override;`
- L56 _public prototype_ `virtual void EndUserInteraction() const override;`
- L57 _public prototype_ `virtual FString GetNodeComment() const override;`
- L61 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L65 _public prototype_ `virtual bool IsNameReadOnly() const override;`
- L66 _public function_ `virtual FSlateColor GetCommentColor() const override`
- L68 _public function_ `virtual void RequestRenameOnSpawn()` — Requests a rename when the node was initially spawned
- L75 _public prototype_ `void Construct( const FArguments& InArgs, UEdGraphNode_Comment* InNode );`
- L78 _public prototype_ `virtual bool CanBeSelected( const FVector2f& MousePositionInNode ) const override;` — return if the node can be selected, by pointing given location
- L81 _public prototype_ `virtual FVector2f GetDesiredSizeForMarquee2f() const override;` — return size of the title bar
- L84 _public prototype_ `virtual FSlateRect GetTitleRect() const override;` — return rect of the title bar
- L88 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L89 _protected prototype_ `virtual void PopulateMetaTag(class FGraphNodeMetaData* TagMeta) const override;`
- L96 _protected prototype_ `void HandleSelection(bool bIsSelected, bool bUpdateNodesUnderComment = false) const;` — Helper method to update selection state of comment and any nodes 'contained' within it @param bSelected	If true comment is being selected, false otherwise @param bUpdateNodesUnderComment If true then force the rebuild of the list of nodes under the comment
- L99 _protected prototype_ `virtual bool IsNodeUnderComment(UEdGraphNode_Comment* InCommentNode, const TSharedRef<SGraphNode> InNodeWidget) const;` — Helper function to determine if a node is under this comment widget or not
- L102 _protected prototype_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) override;` — called when user is moving the comment node
- L105 _protected prototype_ `virtual float GetTitleBarHeight() const override;`
- L106 _protected prototype_ `virtual FSlateRect GetHitTestingBorder() const override;`
- L107 _protected prototype_ `virtual FVector2f GetNodeMaximumSize2f() const override;`
- L111 _protected prototype_ `FSlateColor GetCommentBodyColor() const;` — @return the color to tint the comment body
- L114 _protected prototype_ `FSlateColor GetCommentTitleBarColor() const;` — @return the color to tint the title bar
- L117 _protected prototype_ `FSlateColor GetCommentBubbleColor() const;` — @return the color to tint the comment bubble
- L122 _private prototype_ `float GetWrapAt() const;` — Returns the width to wrap the text of the comment at
- L125 _private member_ `TSharedPtr<SCommentBubble> CommentBubble;` — The comment bubble widget (used when zoomed out)
- L128 _private member_ `mutable bool bIsSelected;` — The current selection state of the comment
- L131 _private member_ `TSharedPtr<SBorder> TitleBar;` — the title bar, needed to obtain it's height
- L135 _protected member_ `FString CachedCommentTitle;` — cached comment title
- L138 _protected member_ `int32 CachedFontSize;` — cached font size
- L141 _protected member_ `mutable bool bCachedBubbleVisibility;` — Was the bubble desired to be visible last frame?
- L145 _private member_ `int32 CachedWidth;` — cached comment title
- L148 _private member_ `FInlineEditableTextBlockStyle CommentStyle;` — Local copy of the comment style

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphNodeDefault.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeDefault>`  
_L16-19_
- L18 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeDefault`  
`class SGraphNodeDefault : public SGraphNode`  
_L21-33_
- inherits: `SGraphNode`
- L25 _public function_ `SLATE_BEGIN_ARGS( SGraphNodeDefault ) : _GraphNodeObj( static_cast<UEdGraphNode*>(NULL) )`
- L29 _public prototype_ `SLATE_ARGUMENT( UEdGraphNode*, GraphNodeObj ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphNodeDocumentation.h` (Public)


#### class `SGraphNodeDocumentation`  
`class SGraphNodeDocumentation : public SGraphNodeResizable`  
_L25-87_
- inherits: `SGraphNodeResizable`
- L28 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeDocumentation)`
- L29 _public prototype_ `SLATE_END_ARGS()`
- L36 _public prototype_ `void Construct( const FArguments& InArgs, UEdGraphNode* InNode );`
- L37 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L38 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L42 _public prototype_ `virtual FVector2f GetNodeMinimumSize2f() const override;`
- L43 _public prototype_ `virtual FVector2f GetNodeMaximumSize2f() const override;`
- L44 _public prototype_ `virtual float GetTitleBarHeight() const override;`
- L45 _public prototype_ `virtual FSlateRect GetHitTestingBorder() const override;`
- L51 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L52 _protected function_ `virtual bool IsNameReadOnly () const override`
- L56 _protected prototype_ `FText GetDocumentationTitle() const;` — Retrieves the current documentation title based on the chosen excerpt
- L58 _protected prototype_ `TSharedPtr<SWidget> CreateDocumentationPage();` — Create documentation page from link and excerpt
- L60 _protected prototype_ `FOptionalSize GetContentWidth() const;` — Returns the width the documentation content must adhere to, used as a delegate in child widgets
- L62 _protected prototype_ `FOptionalSize GetContentHeight() const;` — Returns the height the documentation content must adhere to, used as a delegate in child widgets
- L64 _protected prototype_ `float GetDocumentationWrapWidth() const;` — Returns the child widget text wrapat size, used as a delegate during creation of documentation page
- L66 _protected prototype_ `EVisibility GetWidgetVisibility() const;` — Returns the current child widgets visibility for hit testing
- L68 _protected prototype_ `FLinearColor GetPageGradientStartColor() const;` — Color of the page gradient start
- L70 _protected prototype_ `FLinearColor GetPageGradientEndColor() const;` — Color of the page gradient end
- L75 _private member_ `TSharedPtr<SWidget> TitleBar;` — Node Title Bar
- L77 _private member_ `FVector2f DocumentationSize;` — Documentation excerpt maximum page size
- L79 _private member_ `TSharedPtr<SWidget> ContentWidget;` — Content Widget with the desired size being managed
- L81 _private member_ `EVisibility ChildWidgetVisibility;` — Tracks if child widgets are availble to hit test against
- L83 _private member_ `FString CachedDocumentationLink;` — Cached Documentation Link
- L85 _private member_ `FString CachedDocumentationExcerpt;` — Cached Documentation Excerpt

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphNodeKnot.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeKnot>`  
_L23-26_
- L25 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeKnot`  
`class SGraphNodeKnot : public SGraphNodeDefault`  
_L31-66_
- inherits: `SGraphNodeDefault`
- desc: The visual representation of a control point meant to adjust how connections are routed, also known as a Reroute node. The input knot node should have properly implemented ShouldDrawNodeAsControlPointOnly to return true with valid indices for its pins.
- L34 _public function_ `SLATE_BEGIN_ARGS(SGraphNodeKnot)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UEdGraphNode* InKnot);`
- L40 _public prototype_ `virtual void UpdateGraphNode() override;` — SGraphNode interface
- L41 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L42 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L43 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L44 _public function_ `virtual void RequestRenameOnSpawn() override`
- L49 _protected prototype_ `FVector2f GetCommentOffset() const;` — Returns Offset to center comment on the node's only pin
- L53 _protected prototype_ `virtual void OnCommentBubbleToggled(bool bInCommentBubbleVisible) override;` — Toggles the hovered visibility state
- L56 _protected prototype_ `virtual void OnCommentTextCommitted(const FText& NewComment, ETextCommit::Type CommitInfo) override;` — If bHoveredCommentVisibility is true, hides the comment bubble after a change is committed
- L59 _protected member_ `bool bAlwaysShowCommentBubble;` — The hovered visibility state. If false, comment bubble will only appear on hover.
- L62 _protected member_ `TSharedPtr<SCommentBubble> CommentBubble;` — SharedPtr to comment bubble
- L64 _protected member_ `const FSlateBrush* ShadowBrush;`
- L65 _protected member_ `const FSlateBrush* ShadowBrushSelected;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPinKnot>`  
_L70-73_
- L25 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPinKnot`  
`class SGraphPinKnot : public SGraphPin`  
_L75-94_
- inherits: `SGraphPin`
- L78 _public function_ `SLATE_BEGIN_ARGS(SGraphPinKnot)`
- L79 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L84 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L89 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L90 _protected prototype_ `virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins) override;`
- L91 _protected prototype_ `virtual FReply OnPinMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _protected prototype_ `virtual FSlateColor GetPinColor() const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphNodePromotableOperator.h` (Public)


#### class `SGraphNodePromotableOperator`  
`class SGraphNodePromotableOperator : public SGraphNodeK2Sequence`  
_L20-39_
- inherits: `SGraphNodeK2Sequence`
- desc: A custom slate node for the promotable operator (K2Node_PromotableOperator) These nodes include common math operations like Add, Subtract, Multiply, etc. This custom node will provide a neat little secondary icon to visually show that promotable operator pins can be converted to other types.
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphNodePromotableOperator)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UK2Node_PromotableOperator* InNode);`
- L30 _public prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L35 _protected prototype_ `void LoadCachedIcons();`
- L37 _protected member_ `const FSlateBrush* CachedOuterIcon;`
- L38 _protected member_ `const FSlateBrush* CachedInnerIcon;`

### `Source/Editor/GraphEditor/Public/SGraphNodeResizable.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphNodeResizable>`  
_L21-24_
- L23 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphNodeResizable`  
`class SGraphNodeResizable : public SGraphNode`  
_L26-115_
- inherits: `SGraphNode`
- L49 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L50 _public prototype_ `virtual void OnMouseEnter( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L51 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L52 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L53 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L54 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L61 _protected prototype_ `virtual SGraphNodeResizable::EResizableWindowZone FindMouseZone(const FVector2D& LocalMouseCoordinates) const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Find the current window zone the mouse is in
- L62 _protected prototype_ `virtual SGraphNodeResizable::EResizableWindowZone FindMouseZone(const FVector2f& LocalMouseCoordinates) const;`
- L65 _protected function_ `bool InSelectionArea() const` — @return true if the current window zone is considered a selection area
- L68 _protected prototype_ `bool InSelectionArea(EResizableWindowZone InZone) const;` — @return true if the passed zone is a selection area
- L71 _protected prototype_ `void InitNodeAnchorPoint();` — Function to store anchor point before resizing the node. The node will be anchored to this point when resizing happens
- L74 _protected prototype_ `UE::Slate::FDeprecateVector2DResult GetCorrectedNodePosition() const;` — Function to fetch the corrected node position based on anchor point
- L77 _protected prototype_ `virtual float GetTitleBarHeight() const;` — Get the current titlebar size
- L81 _protected prototype_ `virtual FVector2D GetNodeMinimumSize() const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Return smallest desired node size
- L82 _protected prototype_ `virtual FVector2f GetNodeMinimumSize2f() const;`
- L86 _protected prototype_ `virtual FVector2D GetNodeMaximumSize() const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Return largest desired node size
- L87 _protected prototype_ `virtual FVector2f GetNodeMaximumSize2f() const;`
- L90 _protected prototype_ `virtual FSlateRect GetHitTestingBorder() const;` — /  Return slate rect border for hit testing
- L95 _protected member_ `FDeprecateSlateVector2D DragSize;` — The non snapped size of the node for fluid resizing
- L98 _protected member_ `FDeprecateSlateVector2D UserSize;` — The desired size of the node set during a drag
- L101 _protected member_ `FDeprecateSlateVector2D StoredUserSize;` — The original size of the node while resizing
- L104 _protected member_ `TSharedPtr<FScopedTransaction> ResizeTransactionPtr;` — The resize transaction
- L107 _protected member_ `FDeprecateSlateVector2D NodeAnchorPoint;` — Anchor point used to correct node position on resizing the node
- L110 _protected member_ `EResizableWindowZone MouseZone;` — The current window zone the mouse is in
- L113 _protected member_ `bool bUserIsDragging;` — If true the user is actively dragging the node

#### enum `SGraphNodeResizable::EResizableWindowZone`  
`enum EResizableWindowZone`  
_L33-46_
- desc: The resizable window zone the user is interacting with
- L35 _public enumerator_ `CRWZ_NotInWindow = 0`
- L36 _public enumerator_ `CRWZ_InWindow = 1`
- L37 _public enumerator_ `CRWZ_RightBorder = 2`
- L38 _public enumerator_ `CRWZ_BottomBorder = 3`
- L39 _public enumerator_ `CRWZ_BottomRightBorder = 4`
- L40 _public enumerator_ `CRWZ_LeftBorder = 5`
- L41 _public enumerator_ `CRWZ_TopBorder = 6`
- L42 _public enumerator_ `CRWZ_TopLeftBorder = 7`
- L43 _public enumerator_ `CRWZ_TopRightBorder = 8`
- L44 _public enumerator_ `CRWZ_BottomLeftBorder = 9`
- L45 _public enumerator_ `CRWZ_TitleBar = 10`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphPalette.h` (Public)


#### class `SGraphPaletteItem`  
`class SGraphPaletteItem : public SCompoundWidget`  
_L36-85_
- inherits: `SCompoundWidget`
- desc: Widget for displaying a single item
- L40 _public member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate executed when mouse button goes down
- L42 _public member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The item that we want to display with this widget
- L44 _public member_ `TSharedPtr< SInlineEditableTextBlock > InlineRenameWidget;` — Holds the inline renaming widget if one was created
- L47 _public function_ `SLATE_BEGIN_ARGS( SGraphPaletteItem )`
- L48 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L53 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;` — SWidget interface
- L54 _public prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L55 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L56 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L61 _protected prototype_ `TSharedRef<SWidget> CreateIconWidget( const FText& IconToolTip, const FSlateBrush* IconBrush, const FSlateColor& IconColor, const FString& DocLink, const FString& DocExcerpt, const FSlateBrush* SecondaryIconBrush, const FSlateColor& SecondaryColor );` — Creates an icon type widget, including big tooltip link
- L63 _protected prototype_ `TSharedRef<SWidget> CreateIconWidget(const FText& IconToolTip, const FSlateBrush* IconBrush, const FSlateColor& IconColor);` — Create an icon type widget
- L66 _protected function_ `virtual TSharedRef<SWidget> CreateTextSlotWidget(const FSlateFontInfo& NameFont, FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly)` — `UE_DEPRECATED(5.0, "CreateTextSlotWidget that takes a font parameter is deprecated")`
- L72 _protected prototype_ `virtual TSharedRef<SWidget> CreateTextSlotWidget( FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly );` — Create the text widget
- L75 _protected prototype_ `virtual bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage);` — Callback when rename text is being verified on text changed
- L78 _protected prototype_ `virtual void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);` — Callback when rename text is committed
- L81 _protected prototype_ `virtual FText GetDisplayText() const;` — Callback to get the display text
- L84 _protected prototype_ `virtual FText GetItemTooltip() const;` — Callback to get the tooltip

#### class `SGraphPalette`  
`class SGraphPalette : public SCompoundWidget`  
_L89-114_
- inherits: `SCompoundWidget`
- L92 _public function_ `SLATE_BEGIN_ARGS( SGraphPalette )`
- L96 _public prototype_ `SLATE_ARGUMENT( bool, AutoExpandActionMenu ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L100 _public prototype_ `virtual ~SGraphPalette() = default;`
- L103 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);`
- L105 _protected prototype_ `virtual FReply OnActionDragged(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions, const FPointerEvent& MouseEvent);`
- L107 _protected prototype_ `virtual void RefreshActionsList(bool bPreserveExpansion);`
- L110 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) = 0;` — Callback used to populate all actions list in SGraphActionMenu
- L113 _protected member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphPanel.h` (Public)


#### struct `FGraphContextMenuArguments`  
`struct FGraphContextMenuArguments`  
_L61-74_
- desc: Arguments when the graph panel wants to open a context menu
- L64 _public member_ `FDeprecateSlateVector2D NodeAddPosition;` — The endpoint of the drag or the location of the right-click
- L67 _public member_ `UEdGraphNode* GraphNode;` — The source node if there are any
- L70 _public member_ `UEdGraphPin* GraphPin;` — The source pin if there is one
- L73 _public member_ `TArray<UEdGraphPin*> DragFromPins;`

#### struct `FConnectionSlice`  
`struct FConnectionSlice`  
_L77-88_
- desc: Data we need to store while the user is slicing through connections in the graph
- L80 _public member_ `FMarqueeRect Line;` — The start/end points of the slice line, in graph coords
- L84 _public member_ `TArray<TPair<FEdGraphPinReference, FEdGraphPinReference>> ConnectionsIntersectingSliceLine;` — The pin connections which were intersecting the line last frame when the connection policy was drawn, and which should be broken if this slice is executed
- L86 _public function_ `explicit FConnectionSlice(const FVector2f StartPosition) : Line(StartPosition)`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPanel>`  
_L92-95_
- L94 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPanel`  
`class SGraphPanel : public SNodePanel, public FGCObject`  
_L97-559_
- inherits: `SNodePanel,FGCObject`
- L101 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FActionMenuContent, FOnGetContextMenuFor, const FGraphContextMenuArguments& ) SLATE_BEGIN_ARGS( SGraphPanel ) : _OnGetContextMenuFor() , _OnSelectionChanged() , _OnNodeDoubleClicked() , _GraphObj( static_cast<UEdGraph*>(NULL) ) , _InitialZoomToFit( false ) , _IsEditable( true ) , _DisplayAsReadOnly( false ) , _ShowGraphStateOverlay(true) , _AllowConnectionSlicing(true) , _ShouldDrawBackground(true) , _ShouldDrawSurroundingShadow(true) , _OnUpdateGraphPanel() , _AllowZoom(true) , _AllowPanning(true)`
- L122 _public function_ `SLATE_EVENT( FOnGetContextMenuFor, OnGetContextMenuFor ) SLATE_EVENT( SGraphEditor::FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT(FSingleNodeEvent, OnNodeDoubleClicked) SLATE_EVENT(SGraphEditor::FOnDropActors, OnDropActors) PRAGMA_DISABLE_DEPRECATION_WARNINGS static SGraphEditor::FOnDropActors ConvertOnDropActorDelegate(const SGraphEditor::FOnDropActor& LegacyDelegate)`
- L143 _public function_ `static SGraphEditor::FOnDropStreamingLevels ConvertOnDropStreamingLevelDelegate(const SGraphEditor::FOnDropStreamingLevel& LegacyDelegate)`
- L160 _public function_ `SLATE_EVENT( SGraphEditor::FOnDropStreamingLevels, OnDropStreamingLevels ) SLATE_ARGUMENT( class UEdGraph*, GraphObj ) SLATE_ARGUMENT( TSharedPtr<TArray<FDiffSingleResult>>, DiffResults ) SLATE_ATTRIBUTE( int32, FocusedDiffResult ) SLATE_ARGUMENT( bool, InitialZoomToFit ) SLATE_ATTRIBUTE( bool, IsEditable ) SLATE_ATTRIBUTE( bool, DisplayAsReadOnly ) SLATE_ATTRIBUTE(bool, ShowGraphStateOverlay) SLATE_ATTRIBUTE(bool, AllowConnectionSlicing) SLATE_ATTRIBUTE(bool, ShouldDrawBackground) SLATE_ATTRIBUTE(bool, ShouldDrawSurroundingShadow) SLATE_EVENT( FOnNodeVerifyTextCommit, OnVerifyTextCommit ) SLATE_EVENT( FOnNodeTextCommitted, OnTextCommitted ) PRAGMA_DISABLE_DEPRECATION_WARNINGS static SGraphEditor::FOnSpawnNodeByShortcutAtLocation ConvertOnSpawnNodeByShortcutDelegate(const SGraphEditor::FOnSpawnNodeByShortcut& LegacyDelegate)`
- L192 _public prototype_ `SLATE_EVENT( SGraphEditor::FOnSpawnNodeByShortcutAtLocation, OnSpawnNodeByShortcutAtLocation ) SLATE_EVENT( FOnUpdateGraphPanel, OnUpdateGraphPanel ) SLATE_EVENT( SGraphEditor::FOnDisallowedPinConnection, OnDisallowedPinConnection ) SLATE_EVENT( SGraphEditor::FOnDoubleClicked, OnDoubleClicked ) SLATE_EVENT( SGraphEditor::FOnMouseButtonDown, OnMouseButtonDown ) SLATE_EVENT( SGraphEditor::FOnNodeSingleClicked, OnNodeSingleClicked )`
- L210 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct a widget @param InArgs    The declaration describing how the widgets should be constructed.
- L213 _public prototype_ `~SGraphPanel();` — Destructor
- L216 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L217 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L218 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L219 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L220 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L221 _public prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L222 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L223 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L224 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L225 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L226 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L227 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`
- L228 _public prototype_ `virtual bool CustomPrepass(float LayoutScaleMultiplier) override;`
- L232 _public prototype_ `virtual TSharedPtr<SWidget> OnSummonContextMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SNodePanel interface
- L233 _public prototype_ `virtual bool OnHandleLeftMouseRelease(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L234 _public prototype_ `virtual void AddGraphNode(const TSharedRef<SNode>& NodeToAdd) override;`
- L235 _public prototype_ `virtual void RemoveAllNodes() override;`
- L239 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface.
- L240 _public prototype_ `virtual FString GetReferencerName() const override;`
- L243 _public prototype_ `void ArrangeChildrenForContextMenuSummon(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const;`
- L244 _public prototype_ `TSharedPtr<SWidget> SummonContextMenu(const UE::Slate::FDeprecateVector2DParameter& WhereToSummon, const UE::Slate::FDeprecateVector2DParameter& WhereToAddNode, UEdGraphNode* ForNode, UEdGraphPin* ForPin, const TArray<UEdGraphPin*>& DragFromPins);`
- L245 _public prototype_ `void SummonCreateNodeMenuFromUICommand(uint32 NumNodesAdded);`
- L246 _public prototype_ `void DismissContextMenu();`
- L248 _public prototype_ `void OnBeginMakingConnection(UEdGraphPin* InOriginatingPin);`
- L249 _public prototype_ `void OnBeginMakingConnection(FGraphPinHandle PinHandle);`
- L250 _public prototype_ `void OnStopMakingConnection(bool bForceStop = false);`
- L251 _public prototype_ `void PreservePinPreviewUntilForced();`
- L254 _public prototype_ `void OnBeginRelinkConnection(const FGraphPinHandle& InSourcePinHandle, const FGraphPinHandle& InTargetPinHandle);` — Indicate that the connection from the given start to the given end pins is being relinked. A preview connection is being drawn for the relinked connection.
- L257 _public prototype_ `void OnEndRelinkConnection(bool bForceStop = false);` — The relink connection operation either got cancelled or has successfully been executed. Preview connection won't be drawn anymore.
- L260 _public prototype_ `bool IsRelinkingConnection() const;` — True in case a connection is currently being relinked, false if not.
- L263 _public prototype_ `void Update();` — Update this GraphPanel to match the data that it is observing. Expected to be called during ticking.
- L266 _public prototype_ `void PurgeVisualRepresentation();` — Purges the existing visual representation (typically followed by an Update call in the next tick)
- L269 _public prototype_ `bool IsNodeTitleVisible(const class UEdGraphNode* Node, bool bRequestRename);` — Use to determine if a comment title is currently visible
- L272 _public prototype_ `bool IsRectVisible(const UE::Slate::FDeprecateVector2DParameter &TopLeft, const UE::Slate::FDeprecateVector2DParameter &BottomRight);` — Use to determine if a rectangle is currently visible
- L275 _public prototype_ `bool JumpToRect(const UE::Slate::FDeprecateVector2DParameter &BottomLeft, const UE::Slate::FDeprecateVector2DParameter &TopRight);` — Focuses the view on rectangle, zooming if neccesary
- L277 _public prototype_ `void JumpToNode(const class UEdGraphNode* JumpToMe, bool bRequestRename, bool bSelectNode);`
- L279 _public prototype_ `void JumpToPin(const class UEdGraphPin* JumptToMe);`
- L281 _public prototype_ `void GetAllPins(TSet< TSharedRef<SWidget> >& AllPins);`
- L283 _public prototype_ `void AddPinToHoverSet(UEdGraphPin* HoveredPin);`
- L284 _public prototype_ `void RemovePinFromHoverSet(UEdGraphPin* UnhoveredPin);`
- L286 _public function_ `SGraphEditor::EPinVisibility GetPinVisibility() const`
- L287 _public function_ `void SetPinVisibility(SGraphEditor::EPinVisibility InVisibility)`
- L289 _public function_ `UEdGraph* GetGraphObj() const`
- L292 _public prototype_ `void AttachGraphEvents(TSharedPtr<SGraphNode> CreatedSubNode);` — helper to attach graph events to sub node, which won't be placed directly on the graph
- L295 _public function_ `bool IsGraphEditable() const` — Returns if this graph is editable
- L299 _public prototype_ `bool GetBoundsForNode(const UObject* InNode, FVector2D& MinCorner, FVector2D& MaxCorner, float Padding = 0.0f) const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Attempt to retrieve the bounds for the specified node
- L300 _public prototype_ `bool GetBoundsForNode(const UObject* InNode, FVector2f& MinCorner, FVector2f& MaxCorner, float Padding = 0.0f) const;`
- L303 _public prototype_ `void StraightenConnections();` — Straighten all connections between the selected nodes
- L306 _public prototype_ `void StraightenConnections(UEdGraphPin* SourcePin, UEdGraphPin* PinToAlign = nullptr);` — Straighten any connections attached to the specified pin, optionally limiting to the specified pin to align
- L309 _public prototype_ `void RefreshNode(UEdGraphNode& Node);` — Refresh the visual state of a single node
- L312 _public prototype_ `EActiveTimerReturnType InvalidatePerTick(double InCurrentTime, float InDeltaTime);` — When the graph panel needs to be dynamically refreshing for animations, this function is registered to tick and invalidate the UI.
- L315 _public prototype_ `void SetNodeFactory(const TSharedRef<class FGraphNodeFactory>& NewNodeFactory);` — Sets the current widget factory.
- L317 _public prototype_ `static bool IsSnappingEnabled();`
- L320 _protected prototype_ `void NotifyGraphChanged ( const struct FEdGraphEditAction& InAction);`
- L322 _protected prototype_ `const TSharedRef<SGraphNode> GetChild(int32 ChildIndex);`
- L333 _protected prototype_ `void AddNode(class UEdGraphNode* Node, AddNodeBehavior Behavior);` — Helper method to add a new node to the panel
- L336 _protected prototype_ `void RemoveNode(const UEdGraphNode* Node);` — Helper method to remove a node from the panel
- L339 _protected prototype_ `void RemoveAllNodesWithInvalidPointers();` — Helper method to remove all nodes from the panel holding garbage / invalid pointers
- L342 _protected prototype_ `virtual void OnSelectionChanged(const TSet<UObject*>& Objects) override;` — Called when the graph selection changed
- L346 _public member_ `TWeakPtr<SGraphPin> MarkedPin;` — Pin marked via shift-clicking
- L349 _public prototype_ `TSharedPtr<SGraphNode> GetNodeWidgetFromGuid(FGuid Guid) const;` — Get a graph node widget from the specified GUID, if it applies to any nodes in this graph
- L352 _public prototype_ `TArray<UEdGraphNode*> GetSelectedGraphNodes() const;` — Get a list of selected editor graph nodes from the selection manager.
- L354 _public function_ `const FGraphSplineOverlapResult& GetPreviousFrameSplineOverlap() const`
- L357 _protected function_ `void SetShowGraphStateOverlay(TAttribute<bool> InShowGraphStateOverlayAttribute)`
- L358 _protected function_ `bool GetShowGraphStateOverlay() const`
- L359 _protected function_ `TSlateAttributeRef<bool> GetShowGraphStateOverlayAttribute() const`
- L361 _protected function_ `void SetShouldDrawBackground(TAttribute<bool> InShouldDrawBackgroundAttribute)`
- L362 _protected function_ `bool GetShouldDrawBackground() const`
- L363 _protected function_ `TSlateAttributeRef<bool> GetShouldDrawBackgroundAttribute() const`
- L365 _protected function_ `void SetShouldDrawSurroundingShadow(TAttribute<bool> InShouldDrawSurroundingShadowAttribute)`
- L366 _protected function_ `bool GetShouldDrawSurroundingShadow() const`
- L367 _protected function_ `TSlateAttributeRef<bool> GetShouldDrawSurroundingShadowAttribute() const`
- L369 _protected function_ `void SetDisplayAsReadOnly(TAttribute<bool> InDisplayAsReadOnlyAttribute)`
- L370 _protected function_ `bool GetDisplayAsReadOnly() const`
- L371 _protected function_ `TSlateAttributeRef<bool> GetDisplayAsReadOnlyAttribute() const`
- L376 _private member_ `TMap<FGuid, TWeakPtr<SGraphNode>> NodeGuidMap;` — A map of guid -> graph nodes
- L379 _private member_ `TArray<FConnectionDrawingPolicy::FRelinkConnection> RelinkConnections;` — List of currently relinked connections.
- L382 _protected member_ `TObjectPtr<UEdGraph> GraphObj;`
- L386 _protected member_ `TSharedPtr<TArray<FDiffSingleResult>> DiffResults;` — if this graph is displaying the results of a diff, this will provide info on how to display the nodes
- L387 _protected member_ `TAttribute<int32> FocusedDiffResult;`
- L390 _protected member_ `bool bPreservePinPreviewConnection;` — Should we ignore the OnStopMakingConnection unless forced?
- L393 _protected member_ `SGraphEditor::EPinVisibility PinVisibility;` — Pin visibility mode
- L396 _protected member_ `TSet< FEdGraphPinReference > CurrentHoveredPins;` — List of pins currently being hovered over
- L399 _protected member_ `double TimeWhenMouseEnteredPin;` — Time since the last mouse enter/exit on a pin
- L400 _protected member_ `double TimeWhenMouseLeftPin;`
- L402 _protected member_ `bool bInSlicingMode = false;`
- L405 _protected member_ `TArray< FGraphPinHandle > PreviewConnectorFromPins;` — Sometimes the panel draws a preview connector; e.g. when the user is connecting pins
- L406 _protected member_ `FDeprecateSlateVector2D PreviewConnectorEndpoint;`
- L407 _protected member_ `mutable bool bIsDrawStateCached = false;`
- L410 _protected member_ `FDeprecateSlateVector2D SavedMousePosForOnPaintEventLocalSpace;` — Last mouse position seen, used for paint-centric highlighting
- L413 _protected member_ `FDeprecateSlateVector2D PreviousFrameSavedMousePosForSplineOverlap;` — The overlap results from the previous OnPaint call
- L414 _protected member_ `FGraphSplineOverlapResult PreviousFrameSplineOverlap;`
- L415 _protected member_ `FGraphSplineOverlapResult LastClickSplineOverlap;`
- L418 _protected member_ `FGeometry LastPointerGeometry;` — The mouse state from the last mouse move event, used to synthesize pin actions when hovering over a spline on the panel
- L419 _protected member_ `FPointerEvent LastPointerEvent;`
- L422 _protected member_ `FOnGetContextMenuFor OnGetContextMenuFor;` — Invoked when we need to summon a context menu
- L425 _protected member_ `SGraphEditor::FOnDropActors OnDropActors;` — Invoked when an actor is dropped onto the panel
- L428 _protected member_ `SGraphEditor::FOnDropStreamingLevels OnDropStreamingLevels;` — Invoked when a streaming level is dropped onto the panel
- L431 _protected member_ `FSingleNodeEvent OnNodeDoubleClicked;` — What to do when a node is double-clicked
- L434 _protected member_ `FCurveSequence BounceCurve;` — Bouncing curve
- L437 _protected member_ `mutable FDeprecateSlateVector2D CachedAllottedGeometryScaledSize;` — Geometry cache
- L440 _protected member_ `FOnNodeVerifyTextCommit OnVerifyTextCommit;` — Invoked when text is being committed on panel to verify it
- L443 _protected member_ `FOnNodeTextCommitted OnTextCommitted;` — Invoked when text is committed on panel
- L446 _protected member_ `FOnUpdateGraphPanel OnUpdateGraphPanel;` — Invoked when the panel is updated
- L449 _protected member_ `SGraphEditor::FOnDisallowedPinConnection OnDisallowedPinConnection;` — Called when the user generates a warning tooltip because a connection was invalid
- L452 _protected member_ `SGraphEditor::FOnDoubleClicked OnDoubleClicked;` — Called when the graph itself is double clicked
- L455 _protected member_ `SGraphEditor::FOnMouseButtonDown OnClicked;` — Called when the graph itself is clicked
- L458 _protected member_ `SGraphEditor::FOnSelectionChanged OnSelectionChangedDelegate;` — Called when the graph selection changed
- L461 _protected member_ `bool bShowPIENotification;` — Whether to draw the overlay indicating we're in PIE
- L465 _protected member_ `TSlateDeprecatedTAttribute<bool> ShowGraphStateOverlay;` — `UE_DEPRECATED(5.8, "Use SetShowGraphStateOverlay / GetShowGraphStateOverlay / GetShowGraphStateOverlayAttribute")` — Whether to draw decorations for graph state (PIE / ReadOnly etc.)
- L468 _protected member_ `TAttribute<bool> AllowConnectionSlicing;` — Whether to allow slicing of connections in this graph panel
- L472 _protected member_ `TSlateDeprecatedTAttribute<bool> ShouldDrawBackground;` — `UE_DEPRECATED(5.8, "Use SetShouldDrawBackground / GetShouldDrawBackground / GetShouldDrawBackgroundAttribute")` — Whether this panel should be drawing a background
- L476 _protected member_ `TSlateDeprecatedTAttribute<bool> ShouldDrawSurroundingShadow;` — `UE_DEPRECATED(5.8, "Use SetShouldDrawSurroundingShadow / GetShouldDrawSurroundingShadow / GetShouldDrawSurroundingShadowAttribute")` — Whether this panel should be drawing a sunken shadow on its borders
- L482 _protected member_ `mutable TUniquePtr<FConnectionDrawingPolicy> ConnectionDrawingPolicy;` — The last created policy which is cached to be used on MouseMove to invalidate when hovering connections. This must not be used for drawing outside of Paint
- L486 _private member_ `TSet<TWeakObjectPtr<class UEdGraphNode>> UserSelectedNodes;` — Set of nodes selected by the user, tracked while a visual update is pending
- L492 _private member_ `TSlateAttribute<bool> ShowGraphStateOverlayAttribute;` — Whether to draw decorations for graph state (PIE / ReadOnly etc.)
- L495 _private member_ `TSlateAttribute<bool> ShouldDrawBackgroundAttribute;` — Whether this panel should be drawing a background
- L498 _private member_ `TSlateAttribute<bool> ShouldDrawSurroundingShadowAttribute;` — Whether this panel should be drawing a sunken shadow on its borders
- L501 _private member_ `TSlateAttribute<bool> DisplayAsReadOnlyAttribute;` — Should the graph display all nodes in a read-only state (grayed)? This does not affect functionality of using them (IsEditable)
- L503 _private member_ `FOnGraphChanged::FDelegate MyRegisteredGraphChangedDelegate;`
- L504 _private member_ `FDelegateHandle MyRegisteredGraphChangedDelegateHandle;`
- L507 _private prototype_ `void OnBeginPIE( const bool bIsSimulating );` — Called when PIE begins
- L510 _private prototype_ `void OnEndPIE( const bool bIsSimulating );` — Called when PIE ends
- L513 _private prototype_ `void OnGraphChanged( const FEdGraphEditAction& InAction );` — Called when watched graph changes
- L516 _private prototype_ `void UpdateSelectedNodesPositions(const FVector2f& PositionIncrement);` — Update all selected nodes position by provided vector2d
- L519 _private prototype_ `bool OnSplineHoverStateChanged(const FGraphSplineOverlapResult& NewSplineHoverState);` — Handle updating the spline hover state
- L522 _private prototype_ `class SGraphPin* GetBestPinFromHoveredSpline() const;` — Returns the pin that we're considering as hovered if we are hovering over a spline; may be null
- L525 _private prototype_ `TSharedPtr<SGraphNode> GetGraphNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Returns the top most graph node under the mouse pointer. Returns nullptr if no node found
- L528 _private prototype_ `UEdGraphPin* GetPinUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TSharedPtr<SGraphNode> GraphNode) const;` — Returns a pin that is under the mouse, given a specified node. Returns nullptr if no valid node is given or no pin found
- L531 _private prototype_ `void AdjustNewlySpawnedNodePositions(TArrayView<UEdGraphNode* const> SpawnedNodes, TArrayView<UEdGraphPin*> DraggedFromPins, FVector2f SpawnGraphPosition);` — If the spawned nodes were auto-wired from any of the dragged pins, then this will try to make the newly connected pin end up at SpawnGraphPosition
- L534 _private prototype_ `void MoveNodesToAnchorPinAtGraphPosition(TArrayView<UEdGraphNode* const> NodesToMove, FGraphPinHandle PinToAnchor, FVector2f DesiredPinGraphPosition);` — Will move a group of nodes by the amount needed for an anchor pin to be at a certain position
- L537 _private prototype_ `FReply OnMouseDownDisconnectClosestPinFromWire(TSharedRef<class SGraphPin> ClosestPin, TSharedRef<class SGraphPin> ConnectedPin);` — Begins a drag operation that disconnects the pin at ClosestPin, but only from the ConnectedPin, rather than all connections
- L543 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandleInvalidatePerTick;` — Handle to timer callback that allows the UI to refresh it's arrangement each tick, allows animations to occur within the UI
- L546 _private member_ `float TimeLeftToInvalidatePerTick;` — Amount of time left to invalidate the UI per tick
- L549 _private member_ `TSharedPtr<class FGraphNodeFactory> NodeFactory;` — The current node factory to create nodes, pins and connections. Uses the static FNodeFactory if not set.
- L552 _private member_ `TWeakPtr<IMenu> ContextMenu;` — Weak pointer to the last summoned context menu, for dismissing it when requested.
- L555 _private member_ `bool bCheckNodeGraphObjValidity;` — A flag indicating that we need to check if we have any nodes which use invalid pointers
- L558 _private member_ `TOptional<FConnectionSlice> CurrentSlice;` — Exists while the user is making a slice, and tracks the line points and any connections intersecting the line

#### enum `SGraphPanel::AddNodeBehavior`  
`enum AddNodeBehavior`  
_L325-330_
- desc: Flag to control AddNode, more readable than a bool:
- L327 _public enumerator_ `CheckUserAddedNodesList`
- L328 _public enumerator_ `WasUserAdded`
- L329 _public enumerator_ `NotUserAdded`

#### Free symbols / members of external scopes

- L36 _macro_ `#define UE_API GRAPHEDITOR_API`
- L58 _delegate_ `DECLARE_DELEGATE( FOnUpdateGraphPanel )`
- L101 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FActionMenuContent, FOnGetContextMenuFor, const FGraphContextMenuArguments& ) SLATE_BEGIN_ARGS( SGraphPanel ) : _OnGetContextMenuFor() , _OnSelectionChanged() , _OnNodeDoubleClicked() , _GraphObj( static_cast<UEdGraph*>(NULL) ) , _InitialZoomToFit( false ) , _IsEditable( true ) , _DisplayAsReadOnly( false ) , _ShowGraphStateOverlay(true) , _AllowConnectionSlicing(true) , _ShouldDrawBackground(true) , _ShouldDrawSurroundingShadow(true) , _OnUpdateGraphPanel() , _AllowZoom(true) , _AllowPanning(true) { _Clipping = EWidgetClipping::ClipToBounds; } SLATE_EVENT( FOnGetContextMenuFor, OnGetContextMenuFor ) SLATE_EVENT( SGraphEditor::FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT(FSingleNodeEvent, OnNodeDoubleClicked) SLATE_EVENT(SGraphEditor::FOnDropActors, OnDropActors) PRAGMA_DISABLE_DEPRECATION_WARNINGS static SGraphEditor::FOnDropActors ConvertOnDropActorDelegate(const SGraphEditor::FOnDropActor& LegacyDelegate) { if (LegacyDelegate.IsBound()) { return SGraphEditor::FOnDropActors::CreateLambda([LegacyDelegate](const TArray< TWeakObjectPtr<AActor> >& Actors, UEdGraph* InGraph, const FVector2f& InDropLocation) { LegacyDelegate.Execute(Actors, InGraph, FVector2D(InDropLocation)); }); } return SGraphEditor::FOnDropActors(); } SLATE_EVENT_DEPRECATED(5.6, "Use SGraphEditor::FOnDropActors.",`
- L133 _function_ `` (scope `SGraphPanel::SLATE_EVENT`)
- L148 _function_ `` (scope `SGraphPanel::ConvertOnDropStreamingLevelDelegate`)

### `Source/Editor/GraphEditor/Public/SGraphPin.h` (Public)


#### struct `FGraphPinHandle`  
`struct FGraphPinHandle`  
_L57-97_
- desc: A handle to a pin, defined by its owning node's GUID, and the pin's name. Used to reference a pin without referring to its widget
- L60 _public member_ `FGuid NodeGuid;` — The GUID of the node to which this pin belongs
- L63 _public member_ `FGuid PinId;` — The GUID of the pin we are referencing
- L69 _public prototype_ `FGraphPinHandle() = default;` — Default constructor Will contain a invalid node and pin GUID and IsValid() will return false.
- L72 _public prototype_ `FGraphPinHandle(UEdGraphPin* InPin);` — Constructor
- L75 _public prototype_ `UEdGraphPin* GetPinObj(const SGraphPanel& InPanel) const;`
- L78 _public prototype_ `TSharedPtr<class SGraphPin> FindInGraphPanel(const class SGraphPanel& InPanel) const;` — Find a pin widget in the specified panel from this handle
- L81 _public function_ `bool IsValid() const`
- L87 _public function_ `bool operator==(const FGraphPinHandle& Other) const`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SGraphPin>`  
_L104-107_
- L106 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SGraphPin`  
`class SGraphPin : public SBorder`  
_L112-462_
- inherits: `SBorder`
- desc: Represents a pin on a node in the GraphEditor
- L116 _public function_ `SLATE_BEGIN_ARGS(SGraphPin) : _PinLabelStyle(NAME_DefaultPinLabelStyle) , _UsePinColorForText(false) , _SideToSideMargin(5.0f)`
- L121 _public prototype_ `SLATE_ARGUMENT(FName, PinLabelStyle) SLATE_ARGUMENT(bool, UsePinColorForText) SLATE_ARGUMENT(float, SideToSideMargin) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L134 _public prototype_ `SGraphPin();`
- L135 _public prototype_ `virtual ~SGraphPin();`
- L138 _public prototype_ `void SetIsEditable(TAttribute<bool> InIsEditable);` — Set attribute for determining if pin is editable
- L141 _public function_ `TWeakPtr<SHorizontalBox> GetFullPinHorizontalRowWidget()` — Retrieves the full horizontal box that contains the pin's row content
- L147 _public prototype_ `virtual FReply OnPinMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);` — Handle clicking on the pin
- L150 _public prototype_ `FReply OnPinNameMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);` — Handle clicking on the pin name
- L153 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L154 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L155 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L156 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L157 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L158 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L159 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L160 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L161 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L162 _public prototype_ `virtual TSharedPtr<IToolTip> GetToolTip() override;`
- L166 _public prototype_ `void RefreshLOD();` — Refresh the level of detail applied to the pin name
- L169 _public prototype_ `UEdGraphPin* GetPinObj() const;`
- L172 _public prototype_ `void SetOwner( const TSharedRef<SGraphNode> OwnerNode );` — @param OwnerNode  The SGraphNode that this pin belongs to
- L175 _public prototype_ `void SetPinObj(UEdGraphPin* PinObj);` — @param PinObj The UEdGraphPin object this pin widget represents
- L178 _public prototype_ `EEdGraphPinDirection GetDirection() const;` — @return whether this pin is incoming or outgoing
- L181 _public prototype_ `bool IsArray() const;` — @return whether this pin is an array value
- L184 _public prototype_ `bool IsSet() const;` — @return whether this pin is a set value
- L187 _public prototype_ `bool IsMap() const;` — @return whether this pin is a map value
- L190 _public prototype_ `bool IsByMutableRef() const;` — @return whether this pin is passed by mutable ref
- L193 _public prototype_ `bool IsDelegate() const;` — @return whether this pin is passed by mutable ref
- L196 _public prototype_ `bool IsConnected() const;` — @return whether this pin is connected to another pin
- L199 _public prototype_ `bool AreConnectionsFaded() const;` — @return whether to fade out the pin's connections
- L207 _public prototype_ `virtual bool TryHandlePinConnection(SGraphPin& OtherSPin);` — Tries to handle making a connection to another pin, depending on the schema and the pins it may do: - Nothing - Break existing links on either side while making the new one - Just make the new one @return Whether a connection was actually made or not
- L210 _public prototype_ `virtual EVisibility GetDefaultValueVisibility() const;` — @return Visibility based on whether or not we should show the inline editable text field for this pin
- L213 _public prototype_ `void SetShowLabel(bool bNewDrawLabel);` — Control whether we draw the label on this pin
- L216 _public function_ `void SetPinColorModifier(FLinearColor InColor)` — Allows the connection drawing policy to control the pin color
- L221 _public function_ `void SetDiffHighlighted(bool bHighlighted)`
- L227 _public function_ `void SetPinDiffColor(TOptional<FLinearColor> InColor)` — Allows Diff to highlight pins
- L233 _public function_ `void SetFadeConnections(bool bInFadeConnections)` — Makes Pin Connection Wires transparent
- L239 _public prototype_ `void SetOnlyShowDefaultValue(bool bNewOnlyShowDefaultValue);` — Set this pin to only be used to display default value
- L242 _public prototype_ `EVisibility IsPinVisibleAsAdvanced() const;` — If pin in node is visible at all
- L245 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetNodeOffset() const;` — Gets Node Offset
- L248 _public prototype_ `bool GetIsConnectable() const;` — Returns whether or not this pin is currently connectable
- L251 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget();` — Build the widget we should put into the 'default value' space, shown when nothing connected
- L254 _public function_ `TSharedRef<SWidget> GetValueWidget() const` — Get the widget created by GetDefaultValueWidget()
- L257 _public function_ `TSharedRef<SWrapBox> GetLabelAndValue() const` — Get the label/value part of the pin widget
- L260 _public prototype_ `bool IsEditingEnabled() const;` — True if pin can be edited
- L263 _public function_ `bool GetDefaultValueIsEditable() const` — True if the pin's default value can be edited, false if it is read only
- L272 _public function_ `void InvalidateGraphData()` — Called when ed graph data is cleared, indicating this widget can no longer safely access GraphPinObj Typically an SGraphPin is destroyed before the ed graph data is actually deleted but because SWidget is reference counted we have had problems in the past with the SGraphPin (or Node) living unexpectedly long. If such a situation occurs the code attempting to own the SWidget should be demoted to a WeakPtr, but for added safety we track graph data invalidation here:
- L275 _public prototype_ `void SetCustomPinIcon(const FSlateBrush* InConnectedBrush, const FSlateBrush* InDisconnectedBrush);` — Override the visual look of the pin by providing two custom brushes
- L278 _public prototype_ `bool HasInteractiveTooltip() const;` — @returns true if we have a valid PinValueInspector tooltip
- L281 _public function_ `void EnableDragAndDrop(bool bEnable)` — Enables or disables drag and drop on the pin
- L283 _public prototype_ `bool SnapSGraphNode(TSharedRef<SGraphNode> Node);`
- L284 _public prototype_ `void ClearSnappedSGraphNode();`
- L285 _public prototype_ `bool IsSnapped() const;`
- L286 _public prototype_ `TSharedPtr<SGraphNode> GetSnappedChildForPosition(const FGeometry& MyGeometry, const FVector2f& Position, FVector2f& OutPositionInNode) const;`
- L287 _public prototype_ `TOptional<FArrangedWidget> GetArrangedSnappedChildNode(const FGeometry& MyGeometry) const;`
- L288 _public prototype_ `TSharedPtr<SGraphNode> GetSnappedNode() const;`
- L292 _protected function_ `virtual bool DoesWidgetHandleSettingEditingEnabled() const` — If true the graph pin subclass is responsible for setting the IsEnabled delegates for the aspects it cares about. If false, the default value widget enabling is done by the base class
- L294 _protected prototype_ `FText GetPinLabel() const;`
- L297 _protected function_ `EVisibility GetPinLabelVisibility() const` — If we should show the label on this pin
- L303 _protected prototype_ `virtual TSharedRef<SWidget> GetLabelWidget(const FName& InPinLabelStyle);` — Get the widget we should put in the label space, which displays the name of the pin.
- L306 _protected prototype_ `virtual const FSlateBrush* GetPinIcon() const;` — @return The brush with which to paint this graph pin's incoming/outgoing bullet point
- L309 _protected prototype_ `const FSlateBrush* GetSecondaryPinIcon() const;` — @return the brush which is to paint the 'secondary icon' for this pin, (e.g. value type for Map pins
- L311 _protected prototype_ `const FSlateBrush* GetPinBorder() const;`
- L314 _protected prototype_ `virtual const FSlateBrush* GetPinStatusIcon() const;` — @return The status brush to show after/before the name (on an input/output)
- L317 _protected prototype_ `virtual EVisibility GetPinStatusIconVisibility() const;` — @return Should we show a status brush after/before the name (on an input/output)
- L320 _protected prototype_ `virtual FReply ClickedOnPinStatusIcon();` — Toggle the watch pinning
- L323 _protected prototype_ `virtual FSlateColor GetPinColor() const;` — @return The color that we should use to draw this pin
- L326 _protected prototype_ `virtual FSlateColor GetHighlightColor() const;` — @return The color that we should use to draw the highlight for this pin
- L328 _protected prototype_ `virtual FSlateColor GetPinDiffColor() const;`
- L331 _protected prototype_ `FSlateColor GetSecondaryPinColor() const;` — @return The secondary color that we should use to draw this pin (e.g. value color for Map pins)
- L334 _protected prototype_ `virtual FSlateColor GetPinTextColor() const;` — @return The color that we should use to draw this pin's text
- L337 _protected prototype_ `FText GetTooltipText() const;` — @return The tooltip to display for this pin
- L341 _protected prototype_ `void GetInteractiveTooltipLocation(FVector2D& InOutDesiredLocation) const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Gets the window location (in screen coords) for an interactive tooltip (e.g. pin value inspector)
- L342 _protected prototype_ `void GetInteractiveTooltipLocation(FVector2f& InOutDesiredLocation) const;`
- L344 _protected prototype_ `TOptional<EMouseCursor::Type> GetPinCursor() const;`
- L347 _protected prototype_ `virtual TSharedRef<FDragDropOperation> SpawnPinDragEvent(const TSharedRef<class SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphPin> >& InStartingPins);` — Spawns a FDragConnection or similar class for the pin drag event
- L350 _protected prototype_ `virtual bool UseLowDetailPinNames() const;` — Should we use low-detail pin names?
- L353 _protected prototype_ `virtual TSharedRef<SWidget> OnGetActiveDetailSlotContent(bool bChangedToHighDetail) const;` — What widget should we show when we change detail slot?
- L356 _protected prototype_ `EVisibility GetPinVisiblity() const;` — Determines the pin's visibility based on the LOD factor, when it is low LOD, no hit test will occur
- L361 _public prototype_ `TSharedPtr<SWidget> GetPinImageWidget() const;` — Returns the current pin image widget that is being used
- L364 _public prototype_ `void SetPinImageWidget(TSharedRef<SWidget> NewWidget);` — Sets the pin widget for this pin
- L369 _protected member_ `TWeakPtr<SGraphNode> OwnerNodePtr;` — The GraphNode that owns this pin
- L372 _protected member_ `TSharedPtr<SWidget> PinImage;` — Image of pin
- L373 _protected member_ `TSharedPtr<SBox> SnappedDataNodeContainer;`
- L374 _protected member_ `TWeakPtr<SGraphNode> SnappedNode;`
- L377 _protected member_ `TSharedPtr<SWrapBox> LabelAndValue;` — Label and value
- L380 _protected member_ `TWeakPtr<SHorizontalBox> FullPinHorizontalRowWidget;` — Horizontal box that holds the full detail pin widget, useful for outsiders to inject widgets into the pin
- L383 _protected member_ `SHorizontalBox::FSlot* PinImageHighDetailSlot;` — The slot in which PinImage will be attached when PinNameLODBranchNode switches to HighDetail. Might be stale or null.
- L386 _protected member_ `TSharedPtr<SWidget> ValueWidget;` — Value widget for the pin, created with GetDefaultValueWidget()
- L389 _protected member_ `TWeakPtr<FPinValueInspectorTooltip> ValueInspectorTooltip;` — Value inspector tooltip while debugging
- L392 _protected member_ `class UEdGraphPin* GraphPinObj;` — The GraphPin that this widget represents.
- L395 _protected member_ `TAttribute<bool> IsEditable;` — Is this pin editable
- L398 _protected member_ `FLinearColor PinColorModifier;` — Color modifier for use by the connection drawing policy
- L401 _protected member_ `FDeprecateSlateVector2D CachedNodeOffset;` — Cached offset from owning node to approximate position of culled pins
- L404 _protected member_ `TSet< FEdGraphPinReference > HoverPinSet;` — Set of pins that are currently being hovered
- L407 _protected member_ `TOptional<FLinearColor> PinDiffColor;` — If set, this will change the color of the pin's background highlight
- L410 _protected member_ `const FSlateBrush* CachedImg_ArrayPin_Connected;` — @TODO: Want to cache these once for all SGraphPins, but still handle slate style updates
- L411 _protected member_ `const FSlateBrush* CachedImg_ArrayPin_Disconnected;`
- L412 _protected member_ `const FSlateBrush* CachedImg_RefPin_Connected;`
- L413 _protected member_ `const FSlateBrush* CachedImg_RefPin_Disconnected;`
- L414 _protected member_ `const FSlateBrush* CachedImg_Pin_Connected;`
- L415 _protected member_ `const FSlateBrush* CachedImg_Pin_Disconnected;`
- L416 _protected member_ `const FSlateBrush* CachedImg_DelegatePin_Connected;`
- L417 _protected member_ `const FSlateBrush* CachedImg_DelegatePin_Disconnected;`
- L418 _protected member_ `const FSlateBrush* CachedImg_PosePin_Connected;`
- L419 _protected member_ `const FSlateBrush* CachedImg_PosePin_Disconnected;`
- L420 _protected member_ `const FSlateBrush* CachedImg_SetPin;`
- L421 _protected member_ `const FSlateBrush* CachedImg_MapPinKey;`
- L422 _protected member_ `const FSlateBrush* CachedImg_MapPinValue;`
- L424 _protected member_ `const FSlateBrush* CachedImg_Pin_Background;`
- L425 _protected member_ `const FSlateBrush* CachedImg_Pin_BackgroundHovered;`
- L427 _protected member_ `const FSlateBrush* CachedImg_Pin_DiffOutline;`
- L429 _protected member_ `const FSlateBrush* Custom_Brush_Connected;`
- L430 _protected member_ `const FSlateBrush* Custom_Brush_Disconnected;`
- L433 _protected member_ `bool bGraphDataInvalid;` — flag indicating that graph data has been deleted by the user
- L436 _protected member_ `bool bShowLabel;` — If we should draw the label on this pin
- L439 _protected member_ `bool bOnlyShowDefaultValue;` — If we should draw the label on this pin
- L442 _protected member_ `bool bIsMovingLinks;` — true when we're moving links between pins.
- L445 _protected member_ `bool bUsePinColorForText;` — TRUE if the pin should use the Pin's color for the text
- L448 _protected member_ `bool bDragAndDropEnabled;` — TRUE if the pin should allow any drag and drop
- L451 _protected member_ `bool bIsDiffHighlighted;` — True if this pin is being diffed and it's currently selected in the diff view. Highlights this pin
- L454 _protected member_ `bool bFadeConnections;` — TRUE if the connections from this pin should be drawn at a lower opacity
- L458 _private member_ `bool bIsSnappingEnabled;` — Cached value of snapping feature flag
- L460 _private member_ `TSharedPtr<SLevelOfDetailBranchNode> PinNameLODBranchNode;`

#### Free symbols / members of external scopes

- L33 _macro_ `#define UE_API GRAPHEDITOR_API`
- L51 _macro_ `#define NAME_DefaultPinLabelStyle TEXT("Graph.Node.PinName")`
- L93 _function_ `friend inline uint32 GetTypeHash(const FGraphPinHandle& Handle)`

### `Source/Editor/GraphEditor/Public/SGraphPinComboBox.h` (Public)


#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SPinComboBox>`  
_L22-25_
- L24 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SPinComboBox`  
`class SPinComboBox : public SCompoundWidget`  
_L28-95_
- inherits: `SCompoundWidget`
- desc: Class implementation to create combo box
- L31 _public typedef_ `typedef SListView< TSharedPtr<int32> > SComboList;`
- L32 _public typedef_ `typedef TSlateDelegates< TSharedPtr<int32> >::FOnSelectionChanged FOnSelectionChanged;`
- L34 _public function_ `SLATE_BEGIN_ARGS( SPinComboBox )`
- L35 _public prototype_ `SLATE_ATTRIBUTE( TArray< TSharedPtr<int32> >, ComboItemList ) SLATE_ATTRIBUTE( FString, VisibleText ) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FGetComboItemDisplayString, OnGetDisplayName ) SLATE_EVENT( FGetComboItemDisplayString, OnGetTooltip ) SLATE_END_ARGS()`
- L46 _public function_ `const TSharedPtr<int32> GetSelectedItem()` — Function to return currently selected string
- L51 _public prototype_ `void RemoveItemByIndex(int32 InIndexToRemove);`
- L56 _private prototype_ `void OnSelectionChangedInternal( TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo );` — Function to set the newly selected item
- L59 _private function_ `FText OnGetVisibleTextInternal() const` — Get string to display
- L65 _private prototype_ `TSharedRef<ITableRow> OnGenerateComboWidget( TSharedPtr<int32> InComboIndex, const TSharedRef<STableViewBase>& OwnerTable );` — Function to create each row of the combo widget
- L68 _private prototype_ `FOptionalSize GetMenuDesiredWidth() const;` — Returns the target width of the enum selection menu.
- L70 _private function_ `FText GetRowString(int32 RowIndex) const`
- L76 _private function_ `FText GetRowTooltip(int32 RowIndex) const` — Callback for Slate to retrieve the tooltip
- L83 _private member_ `TArray< TSharedPtr<int32> > ComboItemList;` — List of items in our combo box. Only generated once as combo items dont change at runtime
- L85 _private member_ `TAttribute< FString > VisibleText;`
- L86 _private member_ `TSharedPtr< SComboButton > ComboButton;`
- L87 _private member_ `TSharedPtr< SComboList > ComboList;`
- L88 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L89 _private member_ `TWeakPtr<int32> CurrentSelection;`
- L91 _private member_ `FGetComboItemDisplayString OnGetDisplayName;`
- L94 _private member_ `FGetComboItemDisplayString OnGetTooltip;` — Delegate for finding the tooltip

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetComboItemDisplayString, int32);` — A delegate type invoked when a selection changes somewhere.
- L19 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FGetComboItemDisplayString, int32);` — A delegate type invoked when a selection changes somewhere.

### `Source/Editor/GraphEditor/Public/SGraphPinDataTableRowName.h` (Public)


#### class `SGraphPinDataTableRowName`  
`class SGraphPinDataTableRowName : public SGraphPinNameList, public FDataTableEditorUtils::INotifyOnDataTableChanged`  
_L17-37_
- inherits: `SGraphPinNameList,FDataTableEditorUtils::INotifyOnDataTableChanged`
- L20 _public function_ `SLATE_BEGIN_ARGS(SGraphPinDataTableRowName)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, class UDataTable* InDataTable);`
- L25 _public prototype_ `SGraphPinDataTableRowName();`
- L26 _public prototype_ `virtual ~SGraphPinDataTableRowName();`
- L29 _public prototype_ `virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;` — FDataTableEditorUtils::INotifyOnDataTableChanged
- L30 _public prototype_ `virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;`
- L34 _protected prototype_ `void RefreshNameList();`
- L36 _protected member_ `TSoftObjectPtr<class UDataTable> DataTable;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphPinNameList.h` (Public)


#### class `SGraphPinNameList`  
`class SGraphPinNameList : public SGraphPin`  
_L20-49_
- inherits: `SGraphPin`
- L23 _public function_ `SLATE_BEGIN_ARGS(SGraphPinNameList)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj, const TArray<TSharedPtr<FName>>& InNameList);`
- L35 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — Function to create class specific widget. @return Reference to the newly created widget object
- L43 _protected prototype_ `void ComboBoxSelectionChanged(TSharedPtr<FName> StringItem, ESelectInfo::Type SelectInfo);` — Function to set the newly selected index @param NewSelection The newly selected item in the combo box @param SelectInfo Provides context on how the selection changed
- L45 _protected member_ `TSharedPtr<class SNameComboBox> ComboBox;`
- L48 _protected member_ `TArray<TSharedPtr<FName>> NameList;` — The actual list of FName values to choose from

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphPreviewer.h` (Public)


#### class `SGraphPreviewer`  
`class SGraphPreviewer : public SCompoundWidget`  
_L21-52_
- inherits: `SCompoundWidget`
- desc: This widget provides a fully-zoomed-out preview of a specified graph
- L24 _public function_ `SLATE_BEGIN_ARGS(SGraphPreviewer) : _ShowGraphStateOverlay(true)`
- L27 _public prototype_ `SLATE_ATTRIBUTE( FText, CornerOverlayText ) SLATE_ATTRIBUTE(bool, ShowGraphStateOverlay) SLATE_ARGUMENT( TSharedPtr<SWidget>, TitleBar ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraph* InGraphObj);`
- L37 _protected prototype_ `void OnUpdateGraphPanel();` — Delegate handler for graph panel updates
- L41 _private prototype_ `EActiveTimerReturnType RefreshGraphTimer(const double InCurrentTime, const float InDeltaTime);` — Helper function used to refresh the graph
- L45 _protected member_ `UEdGraph* EdGraphObj;` — The Graph we are currently viewing
- L48 _protected member_ `int32 NeedsRefreshCounter;` — As node's bounds dont get updated immediately, to truly zoom out to fit we need to tick a few times
- L51 _protected member_ `TSharedPtr<SGraphPanel> GraphPanel;` — The underlying graph panel

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GRAPHEDITOR_API`

### `Source/Editor/GraphEditor/Public/SGraphSubstrateMaterial.h` (Public)
_(no declarations extracted)_

### `Source/Editor/GraphEditor/Public/SNameComboBox.h` (Public)


#### class `SNameComboBox`  
`class SNameComboBox : public SCompoundWidget`  
_L43-133_
- inherits: `SCompoundWidget`
- desc: A combo box that shows FName content.
- L47 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetNameComboLabel, TSharedPtr<FName>);`
- L48 _public typedef_ `typedef TSlateDelegates< TSharedPtr<FName> >::FOnSelectionChanged FOnNameSelectionChanged;`
- L50 _public function_ `SLATE_BEGIN_ARGS( SNameComboBox ) : _ComboBoxStyle(&FCoreStyle::Get().GetWidgetStyle< FComboBoxStyle >("ComboBox")) , _ColorAndOpacity( FSlateColor::UseForeground() ) , _ContentPadding(FMargin(4.0, 2.0)) , _OnGetNameLabelForItem()`
- L57 _public prototype_ `SLATE_STYLE_ARGUMENT(FComboBoxStyle, ComboBoxStyle) SLATE_ARGUMENT( TArray< TSharedPtr<FName> >*, OptionsSource ) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_ATTRIBUTE( FSlateColor, ColorAndOpacity ) SLATE_ATTRIBUTE( FMargin, ContentPadding ) SLATE_EVENT( FOnNameSelectionChanged, OnSelectionChanged) SLATE_EVENT( FOnComboBoxOpening, OnComboBoxOpening ) SLATE_ARGUMENT( TSharedPtr<FName>, InitiallySelectedItem ) SLATE_EVENT( FGetNameComboLabel, OnGetNameLabelForItem ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L87 _public prototype_ `TSharedRef<SWidget> MakeItemWidget( TSharedPtr<FName> StringItem );` — Called to create a widget for each FName
- L89 _public prototype_ `void SetSelectedItem (TSharedPtr<FName> NewSelection);`
- L92 _public function_ `TSharedPtr<FName> GetSelectedItem()` — Returns the currently selected FName
- L98 _public prototype_ `void RefreshOptions();` — Request to reload the name options in the combobox from the OptionsSource attribute
- L101 _public prototype_ `void ClearSelection();` — Clears the selected item in the name combo
- L104 _private function_ `TSharedPtr<FName> OnGetSelection() const`
- L107 _private prototype_ `void OnSelectionChanged(TSharedPtr<FName> Selection, ESelectInfo::Type SelectInfo);` — Called when selection changes in the combo pop-up
- L110 _private prototype_ `FText GetSelectedNameLabel() const;` — Helper method to get the text for a given item in the combo box
- L112 _private prototype_ `FText GetItemNameLabel(TSharedPtr<FName> StringItem) const;`
- L117 _private member_ `FGetNameComboLabel GetTextLabelForItem;` — Called to get the text label for an item
- L120 _private member_ `TSharedPtr<FName> SelectedItem;` — The FName item selected
- L123 _private member_ `TArray< TSharedPtr<FName> > Names;` — Array of shared pointers to FNames so combo widget can work on them
- L126 _private member_ `TSharedPtr< SComboBox< TSharedPtr<FName> > > NameCombo;` — The combo box
- L129 _private member_ `FOnNameSelectionChanged SelectionChanged;` — Forwarding Delegate
- L132 _private member_ `TAttribute< FSlateFontInfo > Font;` — Sets the font used to draw the text

#### Free symbols / members of external scopes

- L34 _macro_ `#define UE_API GRAPHEDITOR_API`
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetNameComboLabel, TSharedPtr<FName>);`

### `Source/Editor/GraphEditor/Public/SNodePanel.h` (Public)


#### enum `EGraphRenderingLOD::Type`  
`enum Type`  
_L75-91_
- L78 _public enumerator_ `LowestDetail` — Detail level when zoomed all the way out (all performance optimizations enabled)
- L81 _public enumerator_ `LowDetail` — Detail level that text starts being disabled because it is unreadable
- L84 _public enumerator_ `MediumDetail` — Detail level at which text starts to get hard to read but is still drawn
- L87 _public enumerator_ `DefaultDetail` — Detail level when zoomed in at 1:1
- L90 _public enumerator_ `FullyZoomedIn` — Detail level when fully zoomed in (past 1:1)

#### enum `EGraphZoomLimitHandling`  
`enum class EGraphZoomLimitHandling : uint8`  
_L95-103_
- reflection: `UENUM()`
- L98 _public enumerator_ `Default` — By default, hold down Ctrl to break past the zoom limit.
- L100 _public enumerator_ `AllowLimitBreak` — Always allow breaking through the zoom limit.
- L102 _public enumerator_ `DisallowLimitBreak` — Never allow breaking through the zoom limit.

#### struct `FNodeInfoContext`  
`struct FNodeInfoContext`  
_L106-110_
- desc: Context passed in when getting popup info
- L109 _public member_ `bool bSelected;`

#### struct `FOverlayBrushInfo`  
`struct FOverlayBrushInfo`  
_L113-144_
- desc: Entry for an overlay brush in the node panel
- L117 _public member_ `const FSlateBrush* Brush;` — Brush to draw
- L119 _public member_ `FDeprecateSlateVector2D AnimationEnvelope;` — Scale of animation to apply
- L121 _public member_ `FDeprecateSlateVector2D OverlayOffset;` — Offset origin of the overlay from the widget
- L124 _public function_ `FOverlayBrushInfo() : Brush(NULL) , AnimationEnvelope(0.0f, 0.0f) , OverlayOffset(0.f, 0.f)`
- L131 _public function_ `FOverlayBrushInfo(const FSlateBrush* InBrush) : Brush(InBrush) , AnimationEnvelope(0.0f, 0.0f) , OverlayOffset(0.f, 0.f)`
- L138 _public function_ `FOverlayBrushInfo(const FSlateBrush* InBrush, float HorizontalBounce) : Brush(InBrush) , AnimationEnvelope(HorizontalBounce, 0.0f) , OverlayOffset(0.f, 0.f)`

#### struct `FOverlayWidgetInfo`  
`struct FOverlayWidgetInfo`  
_L147-168_
- desc: Entry for an overlay widget in the node panel
- L151 _public member_ `TSharedPtr<SWidget> Widget;` — Widget to use
- L154 _public member_ `FDeprecateSlateVector2D OverlayOffset;` — Offset origin of the overlay from the widget
- L157 _public function_ `FOverlayWidgetInfo() : Widget(nullptr) , OverlayOffset(0.f, 0.f)`
- L163 _public function_ `FOverlayWidgetInfo(TSharedPtr<SWidget> InWidget) : Widget(InWidget) , OverlayOffset(0.f, 0.f)`

#### struct `FGraphInformationPopupInfo`  
`struct FGraphInformationPopupInfo`  
_L171-184_
- desc: Entry for an information popup in the node panel
- L174 _public member_ `const FSlateBrush* Icon;`
- L175 _public member_ `FLinearColor BackgroundColor;`
- L176 _public member_ `FString Message;`
- L178 _public function_ `FGraphInformationPopupInfo(const FSlateBrush* InIcon, FLinearColor InBackgroundColor, const FString& InMessage) : Icon(InIcon) , BackgroundColor(InBackgroundColor) , Message(InMessage)`

#### struct `FZoomLevelsContainer`  
`struct FZoomLevelsContainer`  
_L190-234_
- desc: Interface for ZoomLevel values Provides mapping for a range of virtual ZoomLevel values to actual node scaling values
- L197 _public prototype_ `virtual float GetZoomAmount(int32 InZoomLevel) const = 0;` — @param InZoomLevel virtual zoom level value @return associated scaling value
- L204 _public prototype_ `virtual int32 GetNearestZoomLevel(float InZoomAmount) const = 0;` — @param InZoomAmount scaling value @return nearest ZoomLevel mapping for provided scale value
- L211 _public prototype_ `virtual FText GetZoomText(int32 InZoomLevel) const = 0;` — @param InZoomLevel virtual zoom level value @return associated friendly name
- L216 _public prototype_ `virtual int32 GetNumZoomLevels() const = 0;` — @return count of supported zoom levels
- L221 _public prototype_ `virtual int32 GetDefaultZoomLevel() const = 0;` — @return the optimal(1:1) zoom level value, default zoom level for the graph
- L228 _public prototype_ `virtual EGraphRenderingLOD::Type GetLOD(int32 InZoomLevel) const = 0;` — @param InZoomLevel virtual zoom level value @return associated LOD value
- L230 _public function_ `virtual EGraphZoomLimitHandling GetZoomLimitHandling() const`
- L233 _public prototype_ `virtual ~FZoomLevelsContainer( void ) = default;` — Necessary for Mac OS X to compile 'delete <pointer_to_this_object>;'

#### struct `FGraphSelectionManager`  
`struct FGraphSelectionManager : public FGCObject`  
_L236-283_
- inherits: `FGCObject`
- L238 _public member_ `TSet<TObjectPtr<class UObject>> SelectedNodes;`
- L241 _public member_ `SGraphEditor::FOnSelectionChanged OnSelectionChanged;` — Invoked when the selected graph nodes have changed.
- L244 _public prototype_ `const FGraphPanelSelectionSet& GetSelectedNodes() const;` — @return the set of selected nodes
- L247 _public prototype_ `void SelectSingleNode(SelectedItemType Node);` — Select just the specified node
- L250 _public prototype_ `void ClearSelectionSet();` — Reset the selection state of all nodes
- L253 _public function_ `bool AreAnyNodesSelected() const` — Returns true if any nodes are selected
- L259 _public prototype_ `void SetSelectionSet(FGraphPanelSelectionSet& NewSet);` — Changes the selection set to contain exactly all of the passed in nodes
- L267 _public prototype_ `void SetNodeSelection(SelectedItemType Node, bool bSelect);` — Add or remove a node from the selection set @param Node      Node the affect. @param bSelect   true to select the node; false to unselect.
- L270 _public prototype_ `bool IsNodeSelected(SelectedItemType Node) const;` — @return true if Node is selected; false otherwise
- L273 _public prototype_ `void StartDraggingNode(SelectedItemType NodeBeingDragged, const FPointerEvent& MouseEvent);` — Handle the selection mechanics of starting to drag a node
- L276 _public prototype_ `void ClickedOnNode(SelectedItemType Node, const FPointerEvent& MouseEvent);` — Handle the selection mechanics when a node is clicked on
- L278 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L279 _public function_ `virtual FString GetReferencerName() const override`

#### enum `ENodeZone::Type`  
`enum Type`  
_L296-311_
- L298 _public enumerator_ `TopLeft`
- L299 _public enumerator_ `TopCenter`
- L300 _public enumerator_ `TopRight`
- L302 _public enumerator_ `Left`
- L303 _public enumerator_ `Center`
- L304 _public enumerator_ `Right`
- L306 _public enumerator_ `BottomLeft`
- L307 _public enumerator_ `BottomCenter`
- L308 _public enumerator_ `BottomRight`
- L310 _public enumerator_ `Count`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<class SNodePanel>`  
_L315-318_
- L317 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SNodePanel`  
`class SNodePanel : public SPanel`  
_L320-1290_
- inherits: `SPanel`
- L828 _public prototype_ `SNodePanel();`
- L831 _public prototype_ `virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override;` — SPanel interface
- L832 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L835 _public prototype_ `virtual FChildren* GetChildren() override;` — `UE_DEPRECATED(5.8, "Use GetVisibleChildren for visible children, or GetManagedChildren to get all the nodes of this panel.")`
- L839 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L840 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L841 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L842 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L843 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L844 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L845 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L846 _public prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L847 _public prototype_ `virtual FReply OnKeyUp( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;`
- L848 _public prototype_ `virtual void OnFocusLost( const FFocusEvent& InFocusEvent ) override;`
- L849 _public prototype_ `virtual FReply OnTouchGesture( const FGeometry& MyGeometry, const FPointerEvent& GestureEvent ) override;`
- L850 _public prototype_ `virtual FReply OnTouchEnded( const FGeometry& MyGeometry, const FPointerEvent& InTouchEvent ) override;`
- L851 _public prototype_ `virtual float GetRelativeLayoutScale(int32 ChildIndex, float LayoutScaleMultiplier) const override;`
- L861 _public prototype_ `bool Contains(UObject* Node) const;` — Is the given node being observed by a widget in this panel? @param Node   The node to look for. @return True if the node is being observed by some widget in this panel; false otherwise.
- L864 _public prototype_ `float GetZoomAmount() const;` — @retun the zoom amount; e.g. a value of 0.25f results in quarter-sized nodes
- L866 _public prototype_ `FText GetZoomText() const;` — @return Zoom level as a pretty string
- L867 _public prototype_ `FSlateColor GetZoomTextColorAndOpacity() const;`
- L870 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetViewOffset() const;` — @return the view offset in graph space
- L873 _public function_ `void SetViewOffset(const UE::Slate::FDeprecateVector2DResult& InViewOffset)` — Sets the current view offset
- L882 _public prototype_ `bool GetZoomTargetRect(FVector2D& TopLeft, FVector2D& BottomRight) const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — when a panel is scrolling/zooming to a target, this can be called to get it's destination @param TopLeft top left corner of the destination @param BottomRight bottom right corner of the destination @return true if there's a scrolling/zooming target and false if there is no destination
- L883 _public prototype_ `bool GetZoomTargetRect(FVector2f& TopLeft, FVector2f& BottomRight) const;`
- L886 _public function_ `int32 GetZoomLevel() const` — @return the current zoom level
- L889 _public prototype_ `void SetZoomLevel(int32 InZoomLevel);` — Sets the current zoom level
- L892 _public function_ `const FGuid& GetViewBookmarkId() const` — @return the current view bookmark ID
- L895 _public prototype_ `UE::Slate::FDeprecateVector2DResult PanelCoordToGraphCoord(const UE::Slate::FDeprecateVector2DParameter& PanelSpaceCoordinate) const;` — Given a coordinate in panel space (i.e. panel widget space), return the same coordinate in graph space while taking zoom and panning into account
- L898 _public prototype_ `void RestoreViewSettings(const UE::Slate::FDeprecateVector2DParameter& InViewOffset, float InZoomAmount, const FGuid& InBookmarkGuid = FGuid());` — Restore the graph panel to the supplied view offset/zoom. Also, optionally set the current bookmark ID.
- L901 _public prototype_ `static uint32 GetSnapGridSize();` — Get the grid snap size
- L907 _public prototype_ `void ZoomToFit(bool bOnlySelection);` — Zooms out to fit either all nodes or only the selected ones. @param bOnlySelection Whether to zoom to fit around only the current selection (if false, will zoom to the extents of all nodes)
- L911 _public prototype_ `bool GetBoundsForSelectedNodes( class FSlateRect& Rect, float Padding = 0.0f);` — Get the bounding area for the currently selected nodes @return false if nothing is selected
- L914 _public prototype_ `UE::Slate::FDeprecateVector2DResult GetPastePosition() const;` — @return the position where where nodes should be pasted (i.e. from the clipboard)
- L917 _public prototype_ `void RequestDeferredPan(const UE::Slate::FDeprecateVector2DParameter& TargetPosition);` — Ask panel to scroll to location
- L920 _public prototype_ `bool HasDeferredObjectFocus() const;` — If it is focusing on a particular object
- L923 _public prototype_ `bool HasDeferredZoomDestination() const;` — Query whether this graph is about to start panning/zooming towards a destination
- L926 _public prototype_ `void FinalizeNodeMovements();` — Commit transactions for any node movements
- L929 _public function_ `EGraphRenderingLOD::Type GetCurrentLOD() const` — Returns the current LOD level of this panel, based on the zoom factor
- L932 _public prototype_ `bool HasMoved() const;` — Returns if the panel has been panned or zoomed since the last update
- L936 _public prototype_ `virtual FChildren* GetAllChildren() override;` — `UE_DEPRECATED(5.8, "Use GetVisibleChildren for visible children, or GetManagedChildren to get all the nodes of this panel. GetAllChildren needs to return only the VisibleChildren to work with invalidation.")` — Returns only the visible children as this is the function called by the invalidation system
- L939 _public prototype_ `FChildren* GetVisibleChildren();` — Returns all the visible panel children
- L940 _public prototype_ `FChildren* GetManagedChildren();`
- L944 _protected prototype_ `void Construct();` — Initialize members
- L951 _protected prototype_ `void ZoomToTarget(const FVector2f& TopLeft, const FVector2f& BottomRight);` — Zooms to the specified target rect @param TopLeft The top left corner of the target rect @param BottomRight The bottom right corner of the target rect
- L954 _protected prototype_ `void UpdateViewOffset(const FGeometry& MyGeometry, const FVector2f& TargetPosition);` — Update the new view offset location
- L957 _protected prototype_ `static FVector2f ComputeEdgePanAmount(const FGeometry& MyGeometry, const FVector2f& MouseEvent);` — Compute much panel needs to change to pan to location
- L960 _protected prototype_ `FVector2f GraphCoordToPanelCoord(const UE::Slate::FDeprecateVector2DParameter& GraphSpaceCoordinate) const;` — Given a coordinate in graph space (e.g. a node's position), return the same coordinate in widget space while taking zoom and panning into account
- L963 _protected prototype_ `FSlateRect PanelRectToGraphRect(const FSlateRect& PanelSpaceRect) const;` — Given a rectangle in panel space, return a rectangle in graph space.
- L971 _protected prototype_ `virtual void OnBeginNodeInteraction(const TSharedRef<SNode>& InNodeToDrag, const FVector2D& GrabOffset) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION;` — Lets the CanvasPanel know that the user is interacting with a node. @param InNodeToDrag   The node that the user wants to drag @param GrabOffset     Where within the node the user grabbed relative to split between inputs and outputs.
- L972 _protected prototype_ `virtual void OnBeginNodeInteraction(const TSharedRef<SNode>& InNodeToDrag, const FVector2f& GrabOffset);`
- L979 _protected prototype_ `virtual void OnEndNodeInteraction(const TSharedRef<SNode>& InNodeToDrag);` — Lets the CanvasPanel know that the user has ended interacting with a node. @param InNodeToDrag   The node that the user was to dragging
- L982 _protected prototype_ `void FindNodesAffectedByMarquee(FGraphPanelSelectionSet& OutAffectedNodes) const;` — Figure out which nodes intersect the marquee rectangle
- L991 _protected prototype_ `static void ApplyMarqueeSelection(const FMarqueeOperation& InMarquee, const FGraphPanelSelectionSet& CurrentSelection, TSet<TObjectPtr<UObject>>& OutNewSelection);` — Apply the marquee operation to the current selection @param InMarquee            The marquee operation to apply. @param CurrentSelection     The selection before the marquee operation. @param OutNewSelection      The selection resulting from Marquee being applied to CurrentSelection.
- L999 _protected prototype_ `void SelectAndCenterObject(const UObject* ObjectToSelect, bool bCenter);` — On the next tick, centers and selects the widget associated with the object if it exists @param ObjectToSelect	The object to select, and potentially center on @param bCenter			Whether or not to center the graph node
- L1006 _protected prototype_ `void CenterObject(const UObject* ObjectToCenter);` — On the next tick, centers the widget associated with the object if it exists @param ObjectToCenter	The object to center
- L1009 _protected prototype_ `virtual void AddGraphNode(const TSharedRef<SNode>& NodeToAdd);` — Add a slot to the CanvasPanel dynamically
- L1012 _protected prototype_ `virtual void RemoveAllNodes();` — Remove all nodes from the panel
- L1015 _protected prototype_ `virtual void PopulateVisibleChildren(const FGeometry& AllottedGeometry);` — Populate visibile children array
- L1018 _protected prototype_ `virtual void ArrangeChildNodes(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const;` — Arrange child nodes - allows derived classes to supply non-node children in OnArrangeChildren
- L1021 _protected prototype_ `void PaintBackgroundAsLines(const FSlateBrush* BackgroundImage, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;` — Paint the background as lines
- L1024 _protected prototype_ `void PaintSurroundSunkenShadow(const FSlateBrush* ShadowImage, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 DrawLayerId) const;` — Paint the well shadow (around the perimeter)
- L1027 _protected prototype_ `void PaintMarquee(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 DrawLayerId) const;` — Paint the marquee selection rectangle
- L1030 _protected prototype_ `void PaintSoftwareCursor(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 DrawLayerId) const;` — Paint the software mouse if necessary
- L1033 _protected prototype_ `void PaintComment(const FString& CommentText, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 DrawLayerId, const FLinearColor& CommentTinting, float& HeightAboveNode, const FWidgetStyle& InWidgetStyle ) const;` — Paint a comment bubble
- L1036 _protected prototype_ `bool IsNodeCulled(const TSharedRef<SNode>& Node, const FGeometry& AllottedGeometry) const;` — Determines if a specified node is not visually relevant.
- L1043 _protected function_ `virtual TSharedPtr<SWidget> OnSummonContextMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)` — @return the widget in the summoned context menu that should be focused.
- L1044 _protected function_ `virtual bool OnHandleLeftMouseRelease(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)`
- L1051 _protected prototype_ `bool GetBoundsForNode(const UObject* InNode, FVector2D& MinCorner, FVector2D& MaxCorner, float Padding = 0.0f) const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Get the bounds of the given node @return True if successful
- L1052 _protected prototype_ `bool GetBoundsForNode(const UObject* InNode, FVector2f& MinCorner, FVector2f& MaxCorner, float Padding = 0.0f) const;`
- L1060 _protected prototype_ `bool GetBoundsForNodes(bool bSelectionSetOnly, FVector2D& MinCorner, FVector2D& MaxCorner, float Padding = 0.0f) const;` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Get the bounds of the selected nodes @param bSelectionSetOnly If true, limits the query to just the selected nodes.  Otherwise it does all nodes. @return True if successful
- L1061 _protected prototype_ `bool GetBoundsForNodes(bool bSelectionSetOnly, FVector2f& MinCorner, FVector2f& MaxCorner, float Padding = 0.0f) const;`
- L1067 _protected prototype_ `bool ScrollToLocation(const FGeometry& MyGeometry, FVector2f DesiredCenterPosition, const float InDeltaTime);` — Scroll the view to the desired location @return true when the desired location is reached
- L1073 _protected prototype_ `bool ZoomToLocation(const FVector2f& CurrentSizeWithoutZoom, const FVector2f& DesiredSize, bool bDoneScrolling);` — Zoom to fit the desired size @return true when zoom fade has completed & fits the desired size
- L1078 _protected prototype_ `void ChangeZoomLevel(int32 ZoomLevelDelta, const FVector2f& WidgetSpaceZoomOrigin, bool bOverrideZoomLimiting);` — Change zoom level by the specified zoom level delta, about the specified origin.
- L1081 _protected prototype_ `void PostChangedZoom();` — Should be called whenever the zoom level has changed
- L1084 _protected prototype_ `void RequestZoomToFit();` — Fires up a per-tick function to zoom the graph to fit
- L1087 _protected prototype_ `void CancelZoomToFit();` — Cancels any active zoom-to-fit action
- L1090 _protected prototype_ `virtual void OnSelectionChanged(const TSet<UObject*>& Objects);` — Called when the graph selection changed
- L1096 _public function_ `template<typename T> void SetZoomLevelsContainer()` — Sets the zoom levels container
- L1101 _public function_ `void SetZoomLevelsContainer(const TSharedPtr<FZoomLevelsContainer>& InZoomLevels)`
- L1109 _public function_ `const TSharedPtr<FZoomLevelsContainer>& GetZoomLevels() const`
- L1111 _public function_ `void SetCurrentHoveredNode(UObject* InNode)`
- L1112 _public function_ `UObject* GetCurrentHoveredNode()`
- L1115 _protected function_ `void SetIsEditable(TAttribute<bool> InIsEditableAttribute)`
- L1116 _protected function_ `bool GetIsEditable() const`
- L1117 _protected function_ `TSlateAttributeRef<bool> GetIsEditableAttribute() const`
- L1122 _protected function_ `TSlateAttributeRef<FVector2f> GetViewOffsetAttribute() const`
- L1130 _protected member_ `TSharedPtr<FZoomLevelsContainer> ZoomLevels;` — The interface for mapping ZoomLevel values to actual node scaling values
- L1134 _protected member_ `FDeprecateSlateVector2D ViewOffset;` — `UE_DEPRECATED(5.8, "Use SetViewOffset / GetViewOffset / GetViewOffsetAttribute")` — The position within the graph at which the user is looking
- L1137 _protected member_ `FDeprecateSlateVector2D OldViewOffset;` — The position within the graph at which the user was looking last tick
- L1140 _protected member_ `int32 ZoomLevel;` — How zoomed in/out we are. e.g. 0.25f results in quarter-sized nodes.
- L1143 _protected member_ `int32 PreviousZoomLevel;` — Previous Zoom Level
- L1146 _protected member_ `float OldZoomAmount;` — The actual scalar zoom amount last tick
- L1149 _protected member_ `bool bIsPanning;` — Are we panning the view at the moment?
- L1152 _protected member_ `bool bIsZoomingWithTrackpad;` — Are we zooming the view with trackpad at the moment?
- L1155 _protected member_ `TUnmanagedSlotlessChildren<SNode> Children;` — The graph node widgets owned by this panel
- L1156 _protected member_ `TSlotlessChildren<SNode> VisibleChildren;`
- L1159 _protected member_ `TWeakPtr<SNode> NodeUnderMousePtr;` — The node that the user is dragging. Null when they are not dragging a node.
- L1162 _protected member_ `FDeprecateSlateVector2D NodeGrabOffset;` — Where in the title the user grabbed to initiate the drag
- L1165 _protected member_ `float TotalMouseDelta;` — The total distance that the mouse has been dragged while down
- L1168 _protected member_ `float TotalMouseDeltaXY;` — The additive X and Y components of mouse drag (used when zooming)
- L1171 _protected member_ `FDeprecateSlateVector2D ZoomStartOffset;` — Offset in the panel the user started the LMB+RMB zoom from
- L1174 _protected member_ `float TotalGestureMagnify;` — Cumulative magnify delta from trackpad gesture
- L1177 _public member_ `FGraphSelectionManager SelectionManager;` — Nodes selected in this instance of the editor; the selection is per-instance of the GraphEditor
- L1181 _protected member_ `TObjectPtr<class UObject> CurrentHoveredNode;` — The currently hovered SNode's UObject
- L1184 _protected member_ `FMarqueeOperation Marquee;` — A pending marquee operation if it's active
- L1188 _protected member_ `TSlateDeprecatedTAttribute<bool> IsEditable;` — `UE_DEPRECATED(5.8, "Use SetIsEditable / GetIsEditable / GetIsEditableAttribute")` — Is the graph editable (can nodes be moved, etc...)?
- L1191 _protected member_ `TMap< UObject*, TSharedRef<SNode> > NodeToWidgetLookup;` — Given a node, find the corresponding widget
- L1194 _protected member_ `TSet<const UObject*> DeferredSelectionTargetObjects;` — If not empty and a part of this panel, this node will be selected and brought into view on the next Tick
- L1196 _protected member_ `const UObject* DeferredMovementTargetObject;` — If non-null and a part of this panel, this node will be brought into view on the next Tick
- L1199 _protected member_ `bool bDeferredZoomToSelection;` — Deferred zoom to selected node extents
- L1202 _protected member_ `bool bDeferredZoomToNodeExtents;` — Deferred zoom to node extents
- L1205 _protected member_ `float ZoomPadding;` — Zoom selection padding
- L1208 _protected member_ `bool bAllowZoom;` — Allow Zoom overall
- L1211 _protected member_ `bool bAllowPanning;` — Allow Panning overall
- L1214 _protected member_ `bool bAllowContinousZoomInterpolation;` — Allow continous zoom interpolation?
- L1217 _protected member_ `bool bTeleportInsteadOfScrollingWhenZoomingToFit;` — Teleport immediately, or smoothly scroll when doing a deferred zoom
- L1220 _protected member_ `FCurveSequence ZoomLevelGraphFade;` — Fade on zoom for graph
- L1223 _protected member_ `FCurveSequence ZoomLevelFade;` — Curve that handles fading the 'Zoom +X' text
- L1226 _protected member_ `FDeprecateSlateVector2D PastePosition;` — The position where we should paste when a user executes the paste command.
- L1229 _protected member_ `FDeprecateSlateVector2D DeferredPanPosition;` — Position to pan to
- L1232 _protected member_ `bool bRequestDeferredPan;` — true if pending request for deferred panning
- L1235 _protected member_ `FDeprecateSlateVector2D SoftwareCursorPosition;` — The current position of the software cursor
- L1238 _protected member_ `bool bShowSoftwareCursor;` — Whether the software cursor should be drawn
- L1241 _protected member_ `EGraphRenderingLOD::Type CurrentLOD;` — Current LOD level for nodes/pins
- L1244 _protected member_ `SGraphEditor::FOnSpawnNodeByShortcutAtLocation OnSpawnNodeByShortcutAtLocation;` — Invoked when the user may be attempting to spawn a node using a shortcut
- L1247 _protected member_ `FInputChord LastKeyChordDetected;` — The last key chord detected in this graph panel
- L1250 _protected member_ `TSharedPtr<FScopedTransaction> ScopedTransactionPtr;` — The current transaction for undo/redo
- L1253 _protected member_ `FGeometry CachedGeometry;` — Cached geometry for use within the active timer
- L1257 _protected member_ `bool bVisualUpdatePending;` — A flag to detect when a visual update is pending to prevent deferred commands like zoom to fit from running when there are no widgets
- L1260 _protected member_ `TMap<TWeakPtr<SNode>, FVector2f> OriginalNodePositions;` — Node positions pre-drag, used to limit transaction creation on drag
- L1263 _protected member_ `SGraphEditor::FOnNodeSingleClicked OnNodeSingleClicked;` — Called when the user left clicks on a node without dragging
- L1266 _protected member_ `TPimplPtr<struct FNodeSnappingManager> NodeSnappingManager;` — Implementation detail for node snapping, experimental and not user extensible
- L1267 _protected prototype_ `struct FNodeSnappingManager* GetSnappingManager();`
- L1268 _protected prototype_ `const struct FNodeSnappingManager* GetSnappingManager() const;`
- L1272 _private prototype_ `EActiveTimerReturnType HandleZoomToFit(double InCurrentTime, float InDeltaTime);` — Active timer that handles deferred zooming until the target zoom is reached
- L1276 _private member_ `TSlateAttribute<bool> IsEditableAttribute;` — Is the graph editable (can nodes be moved, etc...)?
- L1279 _private member_ `TSlateAttribute<FVector2f> ViewOffsetAttribute;` — The position within the graph at which the user is looking
- L1282 _private member_ `TWeakPtr<FActiveTimerHandle> ActiveTimerHandle;` — The handle to the active timer
- L1285 _private member_ `FVector2f ZoomTargetTopLeft;` — Zoom target rectangle
- L1286 _private member_ `FVector2f ZoomTargetBottomRight;`
- L1289 _private member_ `FGuid CurrentBookmarkGuid;` — Current view bookmark info

#### class `SNodePanel::SNode`  
`class SNode : public SPanel`  
_L325-826_
- inherits: `SPanel`
- L433 _public typedef_ `typedef TSet<TWeakPtr<SNodePanel::SNode>> FNodeSet;`
- L436 _public function_ `virtual void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override`
- L446 _public function_ `virtual void OnMouseLeave(const FPointerEvent& InMouseEvent) override`
- L464 _public function_ `virtual FChildren* GetChildren() override` — SPanel Interface
- L469 _public function_ `virtual FVector2D ComputeDesiredSize(float) const override`
- L486 _public function_ `virtual float GetRelativeLayoutScale(int32 ChildIndex, float LayoutScaleMultiplier) const override`
- L502 _public function_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override`
- L536 _public function_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override`
- L564 _public typedef_ `using FScopedWidgetSlotArguments = TPanelChildren<FNodeSlot>::FScopedWidgetSlotArguments;`
- L565 _public function_ `FScopedWidgetSlotArguments GetOrAddSlot( const ENodeZone::Type SlotId )`
- L582 _public function_ `FNodeSlot* GetSlot( const ENodeZone::Type SlotId )`
- L597 _public function_ `void RemoveSlot( const ENodeZone::Type SlotId )`
- L615 _public function_ `virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true) UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — @param NewPosition	The Node should be relocated to this position in the graph panel @param NodeFilter		Set of nodes to prevent movement on, after moving successfully a node is added to this set. @param bMarkDirty		If we should mark nodes as dirty on move
- L619 _public function_ `virtual void MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty = true)`
- L625 _public function_ `virtual FVector2D GetPosition() const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — @return the Node's position within the graph
- L629 _public function_ `virtual FVector2f GetPosition2f() const`
- L635 _public function_ `virtual FString GetNodeComment() const` — @return a user-specified comment on this node; the comment gets drawn in a bubble above the node
- L641 _public function_ `virtual UObject* GetObjectBeingDisplayed() const` — @return The backing object, used as a unique identifier in the selection set, etc...
- L647 _public function_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const` — @return The brush to use for drawing the shadow for this node
- L659 _public prototype_ `TArray<SNodePanel::SNode::DiffHighlightInfo> GetDiffHighlights(const FDiffSingleResult& DiffResult) const;` — @return Collection of brushes layered to outline node with the DiffResult color
- L662 _public function_ `virtual void GetDiffHighlightBrushes(const FSlateBrush*& BackgroundOut, const FSlateBrush*& ForegroundOut) const` — used by GetDiffHighlights to generate outlines for diffed nodes
- L670 _public function_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Populate the brushes array with any overlay brushes to render
- L674 _public function_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const`
- L680 _public function_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — Populate the widgets array with any overlay widgets to render
- L684 _public function_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const`
- L690 _public function_ `virtual void GetNodeInfoPopups(FNodeInfoContext* Context, TArray<FGraphInformationPopupInfo>& Popups) const` — Populate the popups array with any popups to render
- L695 _public function_ `virtual bool RequiresSecondPassLayout() const` — Returns true if this node is dependent on the location of other nodes (it can only depend on the location of first-pass only nodes)
- L701 _public function_ `virtual void PerformSecondPassLayout(const TMap< UObject*, TSharedRef<SNode> >& InNodeToWidgetLookup) const` — Performs second pass layout; only called if RequiresSecondPassLayout returned true
- L706 _public function_ `virtual bool ShouldAllowCulling() const` — Return false if this node should not be culled. Useful for potentially large nodes that may be improperly culled.
- L713 _public function_ `virtual bool CanBeSelected(const FVector2D& MousePositionInNode) const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — return if the node can be selected, by pointing given location
- L717 _public function_ `virtual bool CanBeSelected(const FVector2f& MousePositionInNode) const`
- L723 _public function_ `virtual void EndUserInteraction() const` — Called when user interaction has completed
- L731 _public function_ `virtual FVector2D GetDesiredSizeForMarquee() const UE_SLATE_DEPRECATED_VECTOR_VIRTUAL_FUNCTION` — `UE_DEPRECATED(5.6, "Use the version of the function accepting FVector2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.")` — override, when area used to select node, should be different, than it's size e.g. comment node - only title bar is selectable return size of node used for Marquee selecting
- L735 _public function_ `virtual FVector2f GetDesiredSizeForMarquee2f() const`
- L741 _public function_ `virtual int32 GetSortDepth() const` — Returns node sort depth, defaults to and is generally 0 for most nodes
- L744 _public function_ `bool operator < ( const SNodePanel::SNode& NodeIn ) const` — Node Sort Operator
- L749 _public function_ `void SetParentPanel(const TSharedPtr<SNodePanel>& InParent)`
- L755 _protected function_ `SNode() : DesiredSizeScaleAttribute(*this, FVector2f::UnitVector) , Children(this)`
- L763 _protected function_ `void SetDesiredSizeScale(TAttribute<FDeprecateSlateVector2D> InDesiredSizeScale)`
- L767 _protected function_ `TSlateAttributeRef<FDeprecateSlateVector2D> GetDesiredSizeScaleAttribute() const`
- L771 _protected function_ `FDeprecateSlateVector2D GetDesiredSizeScale() const`
- L779 _protected member_ `TSlateDeprecatedTAttribute<FDeprecateSlateVector2D> DesiredSizeScale;` — `UE_DEPRECATED(5.8, "Use SetDesiredSizeScale / GetDesiredSizeScale / GetDesiredSizeScaleAttribute")`
- L783 _protected member_ `TSlateDeprecatedTAttribute<const FSlateBrush*> BorderImage;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")` — SBorder Begin
- L785 _protected member_ `TSlateDeprecatedTAttribute<FSlateColor> BorderBackgroundColor;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")`
- L789 _protected member_ `TSlateDeprecatedTAttribute<bool> ShowDisabledEffect;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")` — Whether or not to show the disabled effect when this border is disabled
- L792 _protected member_ `FPointerEventHandler MouseButtonDownHandler;` — `UE_DEPRECATED(5.8, "The EventHandler was unused and can be removed.")` — Mouse event handlers
- L794 _protected member_ `FPointerEventHandler MouseButtonUpHandler;` — `UE_DEPRECATED(5.8, "The EventHandler was unused and can be removed.")`
- L796 _protected member_ `FPointerEventHandler MouseMoveHandler;` — `UE_DEPRECATED(5.8, "The EventHandler was unused and can be removed.")`
- L798 _protected member_ `FPointerEventHandler MouseDoubleClickHandler;` — `UE_DEPRECATED(5.8, "The EventHandler was unused and can be removed.")`
- L804 _protected member_ `TSlateDeprecatedTAttribute<FDeprecateSlateVector2D> ContentScale;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")` — The layout scale to apply to this widget's contents; useful for animation.
- L807 _protected member_ `TSlateDeprecatedTAttribute<FLinearColor> ColorAndOpacity;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")` — The color and opacity to apply to this widget and all its descendants.
- L810 _protected member_ `TSlateDeprecatedTAttribute<FSlateColor> ForegroundColor;` — `UE_DEPRECATED(5.8, "The attribute was unused and can be removed.")` — Optional foreground color that will be inherited by all of this widget's contents
- L814 _private member_ `TSlateAttribute<FDeprecateSlateVector2D> DesiredSizeScaleAttribute;`
- L818 _private function_ `TSharedPtr<SNodePanel> GetParentPanel() const`
- L823 _private member_ `TPanelChildren<FNodeSlot> Children;`
- L824 _private member_ `TWeakPtr<SNodePanel> ParentPanelPtr;`

#### class `SNodePanel::SNode::FNodeSlot`  
`class FNodeSlot : public TBasicLayoutWidgetSlot<FNodeSlot>`  
_L331-431_
- inherits: `TBasicLayoutWidgetSlot<FNodeSlot>`
- desc: A slot that support alignment of content and padding and z-order
- L336 _public function_ `FNodeSlot() : FNodeSlot(ENodeZone::TopLeft)`
- L340 _public function_ `FNodeSlot(ENodeZone::Type InZone) : TBasicLayoutWidgetSlot<FNodeSlot>() , Zone(InZone) , Offset(*this, FVector2f::ZeroVector) , Size(*this, FVector2f::ZeroVector) , AllowScale(*this, true) , bSizeAttrIsSet(false)`
- L350 _public prototype_ `SLATE_SLOT_BEGIN_ARGS(FNodeSlot, TBasicLayoutWidgetSlot<FNodeSlot>) SLATE_ATTRIBUTE_DEPRECATED(FVector2D, SlotOffset, 5.6, "Use SlotOffset2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.") SLATE_ATTRIBUTE(FVector2f, SlotOffset2f) SLATE_ATTRIBUTE_DEPRECATED(FVector2D, SlotSize, 5.6, "UseSlotSize2f; this Slate API no longer interfaces directly with double-precision scalars and vectors.") SLATE_ATTRIBUTE(FVector2f, SlotSize2f) SLATE_ATTRIBUTE(bool, AllowScaling) SLATE_SLOT_END_ARGS() void Construct(const FChildren& SlotOwner, FSlotArguments&& InArgs);`
- L359 _public prototype_ `static void RegisterAttributes(FSlateWidgetSlotAttributeInitializer& AttributeInitializer);`
- L362 _public function_ `ENodeZone::Type GetZoneType() const`
- L368 _public function_ `void SetSlotOffset(TAttribute<FVector2D> InOffset)` — `UE_DEPRECATED(5.6, "This exists as a temporary bridge for deprecation of SlotSize Attribute. Please use the FVector2f version.")`
- L378 _public function_ `void SetSlotOffset(TAttribute<FVector2f> InOffset)`
- L383 _public function_ `UE::Slate::FDeprecateVector2DResult GetSlotOffset() const`
- L389 _public function_ `void SetSlotSize(TAttribute<FVector2D> InSize)` — `UE_DEPRECATED(5.6, "This exists as a temporary bridge for deprecation of SlotSize Attribute. Please use the FVector2f version.")`
- L399 _public function_ `void SetSlotSize(TAttribute<FVector2f> InSize)`
- L405 _public function_ `UE::Slate::FDeprecateVector2DResult GetSlotSize() const`
- L410 _public function_ `void SetAllowScaling(TAttribute<bool> InAllowScaling)`
- L415 _public function_ `bool GetAllowScaling() const`
- L422 _private member_ `ENodeZone::Type Zone;` — The child widget contained in this slot.
- L423 _private member_ `TSlateSlotAttribute<FVector2f> Offset;`
- L424 _private member_ `TSlateSlotAttribute<FVector2f> Size;`
- L426 _private member_ `TAttribute<FVector2D> Size_Deprecated;` — `UE_DEPRECATED(5.6, "This exists as a temporary bridge for deprecation of SlotSize Attribute.")`
- L428 _private member_ `TAttribute<FVector2D> Offset_Deprecated;` — `UE_DEPRECATED(5.6, "This exists as a temporary bridge for deprecation of SlotSize Attribute.")`
- L429 _private member_ `TSlateSlotAttribute<bool> AllowScale;`
- L430 _private member_ `bool bSizeAttrIsSet;`

#### struct `SNodePanel::SNode::DiffHighlightInfo`  
`struct DiffHighlightInfo`  
_L652-656_
- L654 _public member_ `const FSlateBrush* Brush;`
- L655 _public member_ `const FLinearColor Tint;`

#### struct `TWidgetTypeTraits`  
`template <> struct TWidgetTypeTraits<SNodePanel::SNode>`  
_L1293-1296_
- L317 _public function_ `static constexpr bool SupportsInvalidation()`

#### Free symbols / members of external scopes

- L52 _macro_ `#define UE_API GRAPHEDITOR_API`
- L70 _typedef_ `typedef class UObject* SelectedItemType;` — @TODO: Too generic of a name to expose at this scope
- L73 _namespace_ `namespace EGraphRenderingLOD`
- L294 _namespace_ `namespace ENodeZone`
- L373 _function_ `` (scope `SNodePanel::SNode::FNodeSlot::SetSlotOffset`)
- L394 _function_ `` (scope `SNodePanel::SNode::FNodeSlot::SetSlotSize`)
