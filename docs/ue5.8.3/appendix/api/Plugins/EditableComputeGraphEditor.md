# Plugins / EditableComputeGraphEditor

- module root: `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor`
- headers: 10; symbols: 218
- symbol kinds: class=10, delegate=10, enum=2, enumerator=7, function=4, member=73, prototype=107, struct=4, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, ComputeDataInterface, ComputeFramework, Core, CoreUObject, EditableComputeGraph, Engine, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/ComputeGraphHlslEditor.h` (Private)


#### class `SComputeGraphHlslEditor`  
`class SComputeGraphHlslEditor : public SCompoundWidget`  
_L21-72_
- inherits: `SCompoundWidget`
- desc: HLSL editor for the EditableComputeGraph asset editor. Displays the source text of the currently selected kernel in a monospace multi-line text box. User commits the text by changing focus or F8 to compile.
- L24 _public function_ `SLATE_BEGIN_ARGS(SComputeGraphHlslEditor)`
- L25 _public prototype_ `SLATE_ARGUMENT(UEditableComputeGraph*, Asset) SLATE_EVENT(FOnComputeGraphHlslTextCommitted, OnTextCommitted_WithKernel) SLATE_EVENT(FOnComputeGraphHlslTextChanged, OnTextChanged) SLATE_EVENT(FOnComputeGraphHlslCompileRequested, OnCompileRequested) SLATE_END_ARGS() void Construct(FArguments const& InArgs);`
- L34 _public prototype_ `void SetActiveKernel(FName KernelName);` — Switch the editor to display a different kernel's source text.
- L37 _public prototype_ `void SetBoundFunctions(TArray<FString> const& Names);` — Highlight the given DI_ function names with the bound-function colour.
- L40 _public prototype_ `void CommitCurrentText();` — Flush any in-progress edit.
- L44 _private prototype_ `FReply OnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent) override;` — Override key down handler to intercept F8 for triggering a compile request.
- L46 _private prototype_ `FReply OnTextBoxKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent);` — First chance key handler wired to the text box to intercept Tab before Slate focus traversal.
- L49 _private prototype_ `void OnTextCommitted(FText const& NewText, ETextCommit::Type CommitType);` — Fires the commit delegate when the user finishes editing.
- L51 _private prototype_ `void OnTextChangedInternal(FText const& NewText);` — Notifies the toolkit that the text has changed so it can mark the asset dirty.
- L54 _private member_ `TWeakObjectPtr<UEditableComputeGraph> Asset;` — The asset being edited.
- L57 _private member_ `FOnComputeGraphHlslTextCommitted OnTextCommitted_WithKernel;` — Fires with the kernel name and new source text when the user commits an edit.
- L59 _private member_ `FOnComputeGraphHlslTextChanged OnTextChanged;` — Fires whenever the text box content changes.
- L61 _private member_ `FOnComputeGraphHlslCompileRequested OnCompileRequested;` — Fires when the user requests a compile (F8).
- L64 _private member_ `FName ActiveKernelName;` — Name of the kernel whose source text is currently displayed.
- L66 _private member_ `TSharedPtr<SMultiLineEditableTextBox> TextBox;` — The multi-line text box used for HLSL input.
- L68 _private member_ `TSharedPtr<STextBlock> PlaceholderText;` — Shown in place of the text box when no kernel is selected.
- L71 _private member_ `TSharedPtr<FComputeGraphHlslSyntaxHighlighter> SyntaxHighlighter;` — Syntax highlighter that colours keywords, DI_ calls, and bound functions.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphHlslTextCommitted, FName , FString const& );`
- L12 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphHlslTextCommitted, FName , FString const& );`
- L13 _delegate_ `DECLARE_DELEGATE(FOnComputeGraphHlslTextChanged);`
- L13 _prototype_ `DECLARE_DELEGATE(FOnComputeGraphHlslTextChanged);`
- L14 _delegate_ `DECLARE_DELEGATE(FOnComputeGraphHlslCompileRequested);`
- L14 _prototype_ `DECLARE_DELEGATE(FOnComputeGraphHlslCompileRequested);`

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/ComputeGraphHlslSyntaxHighlighter.h` (Private)


#### class `FComputeGraphHlslSyntaxHighlighter`  
`class FComputeGraphHlslSyntaxHighlighter : public FHLSLSyntaxHighlighterMarshaller`  
_L12-40_
- inherits: `FHLSLSyntaxHighlighterMarshaller`
- desc: HLSL syntax highlighter for the EditableComputeGraph kernel editor. Extends the base HLSL highlighter with an extra colour for DI_ function names that are currently bound in the kernel's pin list.
- L16 _public prototype_ `static TSharedRef<FComputeGraphHlslSyntaxHighlighter> Create(FSyntaxTextStyle const& InSyntaxTextStyle, FTextBlockStyle const& InBoundFunctionStyle);` — Creates the highlighter.
- L19 _public prototype_ `void SetBoundFunctions(TArray<FString> const& Names);` — Update the set of bound DI_ function names and trigger a re-highlight.
- L23 _protected prototype_ `FTextLayout::FNewLineData ProcessTokenizedLine( ISyntaxTokenizer::FTokenizedLine const& TokenizedLine, int32 const& LineNumber, FString const& SourceString, EParseState& ParseState) override;` — Applies bound-function colouring on top of the base HLSL token styles.
- L31 _private prototype_ `FComputeGraphHlslSyntaxHighlighter( TSharedPtr<ISyntaxTokenizer> InTokenizer, FSyntaxTextStyle const& InSyntaxTextStyle, FTextBlockStyle const& InBoundFunctionStyle);` — Private constructor. Use Create().
- L37 _private member_ `FTextBlockStyle BoundFunctionStyle;` — Text style applied to tokens that match a name in BoundFunctionNames.
- L39 _private member_ `TSet<FString> BoundFunctionNames;` — DI_ function names currently wired to a kernel pin.

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/ComputeGraphNavigator.h` (Private)


#### enum `EComputeGraphItemKind`  
`enum class EComputeGraphItemKind : uint8`  
_L15-21_
- desc: The category of item shown in the compute graph toolkit navigator panel.
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Kernel`
- L19 _public enumerator_ `Interface`
- L20 _public enumerator_ `BindingObject`

#### struct `FComputeGraphEditorSelection`  
`struct FComputeGraphEditorSelection`  
_L24-30_
- desc: Shared selection state between the navigator and the toolkit detail customization.
- L27 _public member_ `EComputeGraphItemKind Kind = EComputeGraphItemKind::None;` — Item type.
- L29 _public member_ `int32 Index = INDEX_NONE;` — Index of the item within its kind array.

#### class `SComputeGraphNavigator`  
`class SComputeGraphNavigator : public SCompoundWidget`  
_L55-121_
- inherits: `SCompoundWidget`
- desc: Item navigator for the EditableComputeGraph asset editor. Supports management of Binding Objects, Data Interfaces and Kernels. Styled to match the Blueprint item panel.
- L58 _public function_ `SLATE_BEGIN_ARGS(SComputeGraphNavigator)`
- L59 _public prototype_ `SLATE_ARGUMENT(UEditableComputeGraph*, Asset) SLATE_EVENT(FOnComputeGraphItemSelected, OnItemSelected) SLATE_EVENT(FOnComputeGraphAddItem, OnAddItem) SLATE_EVENT(FOnComputeGraphDeleteItem, OnDeleteItem) SLATE_EVENT(FOnComputeGraphDuplicateItem, OnDuplicateItem) SLATE_EVENT(FOnComputeGraphRenameItem, OnRenameItem) SLATE_EVENT(FOnComputeGraphKernelSelected, OnKernelSelected) SLATE_END_ARGS() void Construct(FArguments const& InArgs);`
- L71 _public prototype_ `void Refresh();` — Rebuild the tree from the current asset description and reapply selection/expansion.
- L74 _public prototype_ `void SetSelectedItem(EComputeGraphItemKind Kind, int32 Index);` — Programmatically select an item (e.g. after Add or Duplicate). Pass INDEX_NONE to clear.
- L78 _private prototype_ `void RebuildItems();` — Rebuilds RootItems from the current asset description.
- L80 _private prototype_ `TSharedRef<ITableRow> GenerateRow(FNavigatorItemPtr Item, TSharedRef<STableViewBase> const& OwnerTable);` — Builds either a section header row or a leaf item row for the tree view.
- L82 _private prototype_ `void OnGetChildren(FNavigatorItemPtr Item, TArray<FNavigatorItemPtr>& OutChildren);` — Fills OutChildren from the item's Children array (header items only).
- L84 _private prototype_ `TSharedPtr<SWidget> BuildContextMenu();` — Builds the right-click context menu for a selected leaf item.
- L87 _private prototype_ `FReply OnKeyDown(FGeometry const& MyGeometry, FKeyEvent const& InKeyEvent) override;` — Override key down handler to intercept F2 for inline rename on the selected item.
- L90 _private prototype_ `void OnSelectionChanged(FNavigatorItemPtr Item, ESelectInfo::Type SelectInfo);` — Delegate functions.
- L91 _private prototype_ `void OnExpansionChanged(FNavigatorItemPtr Item, bool bExpanded);`
- L92 _private prototype_ `void OnAddItemClicked(EComputeGraphItemKind Kind);`
- L93 _private prototype_ `void OnRenameItemCommitted(EComputeGraphItemKind Kind, int32 Index, FName NewName);`
- L94 _private prototype_ `void OnDeleteSelected();`
- L95 _private prototype_ `void OnDuplicateSelected();`
- L96 _private prototype_ `void OnRenameSelected();`
- L99 _private prototype_ `bool VerifyRenameText(FText const& NewText, FText& OutError, EComputeGraphItemKind Kind, int32 Index) const;` — Returns false and sets OutError if the candidate name is empty or already in use.
- L102 _private member_ `TWeakObjectPtr<UEditableComputeGraph> Asset;` — The asset being navigated; held weakly since this widget is not a GC object.
- L105 _private member_ `TSharedPtr<STreeView<FNavigatorItemPtr>> TreeView;` — The tree view widget.
- L107 _private member_ `TArray<FNavigatorItemPtr> RootItems;` — Root items — one per section header; each carries its leaf children.
- L109 _private member_ `TSet<EComputeGraphItemKind> CollapsedSections;` — Sections that have been manually collapsed; all others are expanded.
- L112 _private member_ `FComputeGraphEditorSelection Selection;` — Current selection; mirrored here so the context menu can read it without a tree query.
- L115 _private member_ `FOnComputeGraphItemSelected OnItemSelected;` — Delegate objects.
- L116 _private member_ `FOnComputeGraphAddItem OnAddItem;`
- L117 _private member_ `FOnComputeGraphDeleteItem OnDeleteItem;`
- L118 _private member_ `FOnComputeGraphDuplicateItem OnDuplicateItem;`
- L119 _private member_ `FOnComputeGraphRenameItem OnRenameItem;`
- L120 _private member_ `FOnComputeGraphKernelSelected OnKernelSelected;`

#### Free symbols / members of external scopes

- L12 _typedef_ `using FNavigatorItemPtr = TSharedPtr<FNavigatorItem>;`
- L33 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnComputeGraphItemSelected, EComputeGraphItemKind, int32 , FName );` — Fired when the user clicks a leaf item. Index is the position in the relevant array.
- L33 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnComputeGraphItemSelected, EComputeGraphItemKind, int32 , FName );` — Fired when the user clicks a leaf item. Index is the position in the relevant array.
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComputeGraphAddItem, EComputeGraphItemKind);` — Fired when the user clicks a section [+] button.
- L36 _prototype_ `DECLARE_DELEGATE_OneParam(FOnComputeGraphAddItem, EComputeGraphItemKind);` — Fired when the user clicks a section [+] button.
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphDeleteItem, EComputeGraphItemKind, int32 );` — Fired when the user selects Delete from the context menu.
- L39 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphDeleteItem, EComputeGraphItemKind, int32 );` — Fired when the user selects Delete from the context menu.
- L42 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphDuplicateItem, EComputeGraphItemKind, int32 );` — Fired when the user selects Duplicate from the context menu.
- L42 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphDuplicateItem, EComputeGraphItemKind, int32 );` — Fired when the user selects Duplicate from the context menu.
- L45 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnComputeGraphRenameItem, EComputeGraphItemKind, int32 , FName );` — Fired when the user commits a rename (inline text or context menu → Rename).
- L45 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnComputeGraphRenameItem, EComputeGraphItemKind, int32 , FName );` — Fired when the user commits a rename (inline text or context menu → Rename).
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComputeGraphKernelSelected, FName );` — Kept for HLSL editor wiring: fires when a kernel is selected.
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnComputeGraphKernelSelected, FName );` — Kept for HLSL editor wiring: fires when a kernel is selected.

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/ComputeGraphView.h` (Private)


#### class `SComputeGraphView`  
`class SComputeGraphView : public SLeafWidget`  
_L17-90_
- inherits: `SLeafWidget`
- desc: Read only graph view for the EditableComputeGraph asset editor. Each connected pin pair is drawn as a spline. The selected kernels and data interfaces can be highlighted along with a dimmer highlight on their neighboring nodes. Clicking on nodes in the graph view will select them in the toolkit.
- L20 _public function_ `SLATE_BEGIN_ARGS(SComputeGraphView)`
- L21 _public prototype_ `SLATE_ARGUMENT(UEditableComputeGraph*, Asset) SLATE_EVENT(FOnComputeGraphNodeClicked, OnNodeClicked) SLATE_END_ARGS() void Construct(FArguments const& InArgs);`
- L28 _public prototype_ `void SetHighlightedKernel(FName KernelName);` — Highlight edges connected to a specific kernel.
- L31 _public prototype_ `void SetHighlightedInterface(FName InterfaceName);` — Highlight a specific data interface node.
- L34 _public prototype_ `void Refresh();` — Rebuild the visual layout from the current asset description.
- L38 _protected prototype_ `int32 OnPaint(FPaintArgs const& Args, FGeometry const& AllottedGeometry, FSlateRect const& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, FWidgetStyle const& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _protected prototype_ `FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L40 _protected prototype_ `FReply OnMouseButtonDown(FGeometry const& MyGeometry, FPointerEvent const& MouseEvent) override;`
- L45 _private prototype_ `void RebuildLayout();` — Rebuilds NodeLayouts, Edges, centre lookup maps, and cached size metrics from the current asset description.
- L68 _private member_ `TWeakObjectPtr<UEditableComputeGraph> Asset;` — The asset being visualised; held weakly since this widget is not a GC object.
- L71 _private member_ `TArray<FNodeLayout> NodeLayouts;` — Flat list of node positions, rebuilt by RebuildLayout().
- L73 _private member_ `TArray<FEdge> Edges;` — Flat list of edges (one per kernel pin), rebuilt by RebuildLayout().
- L75 _private member_ `TMap<FName, FVector2D> InterfaceCentreMap;` — Centre position lookup for interface nodes, keyed by name. Rebuilt by RebuildLayout().
- L77 _private member_ `TMap<FName, FVector2D> KernelCentreMap;` — Centre position lookup for kernel nodes, keyed by name. Rebuilt by RebuildLayout().
- L80 _private member_ `FName HighlightedKernel;` — Name of the kernel node to draw highlighted. NAME_None when nothing is selected.
- L82 _private member_ `FName HighlightedInterface;` — Name of the interface node to draw highlighted. NAME_None when nothing is selected.
- L84 _private member_ `int32 MaxRank = 0;` — Highest rank value present in NodeLayouts that drives the widget width.
- L86 _private member_ `int32 MaxNodesInAnyRank = 0;` — Largest number of nodes sharing a rank column that drives the widget height.
- L89 _private member_ `FOnComputeGraphNodeClicked OnNodeClicked;` — Fired when the user clicks a node.

#### struct `SComputeGraphView::FNodeLayout`  
`struct FNodeLayout`  
_L48-54_
- desc: Position and rank of one node in the graph view.
- L50 _public member_ `FName Name;`
- L51 _public member_ `FVector2D Centre;` — Local widget space (pixels, pre-DPI-scale).
- L52 _public member_ `int32 Rank = 0;` — Column index: 0 = leftmost interfaces, increasing toward outputs.
- L53 _public member_ `bool bKernel = false;`

#### struct `SComputeGraphView::FEdge`  
`struct FEdge`  
_L57-65_
- desc: One directed connection between a kernel pin and a data interface.
- L59 _public member_ `FName KernelName;`
- L60 _public member_ `FName InterfaceName;`
- L61 _public member_ `FString KernelFn;`
- L62 _public member_ `FString InterfaceFn;`
- L63 _public member_ `bool bOrphaned = false;` — True when the pin has no valid binding; drawn red.
- L64 _public member_ `bool bIsOutput = false;` — True for kernel output pins (kernel → interface direction).

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphNodeClicked, FName , bool );`
- L9 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnComputeGraphNodeClicked, FName , bool );`

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/EditableComputeGraphAssetDefinition.h` (Private)


#### class `UAssetDefinition_EditableComputeGraph`  
`class UAssetDefinition_EditableComputeGraph : public UAssetDefinitionDefault`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/EditableComputeGraphDetailCustomization.h` (Private)


#### class `FEditableComputeGraphDetailCustomization`  
`class FEditableComputeGraphDetailCustomization : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- desc: Detail Customization for UEditableComputeGraph. Hides the full "Graph" category and instead exposes only the current array element that the user has selected in the navigator, using property handle navigation.
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<FComputeGraphEditorSelection> InSelection);`
- L20 _protected prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _protected member_ `TSharedPtr<FComputeGraphEditorSelection> Selection;` — Current selection.

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/EditableComputeGraphEditorToolkit.h` (Private)


#### class `FEditableComputeGraphEditorToolkit`  
`class FEditableComputeGraphEditorToolkit : public FAssetEditorToolkit, public FGCObject`  
_L20-132_
- inherits: `FAssetEditorToolkit,FGCObject`
- desc: Custom asset editor for UEditableComputeGraph.
- L23 _public prototype_ `static TSharedRef<FEditableComputeGraphEditorToolkit> Create(UEditableComputeGraph* InAsset, EToolkitMode::Type InMode, TSharedPtr<IToolkitHost> InToolkitHost);`
- L26 _public function_ `UEditableComputeGraph* GetAsset() const` — Returns the asset being edited.
- L29 _public prototype_ `void CompileGraph();` — Flushes any uncommitted HLSL text then triggers a full graph rebuild and shader compile.
- L33 _public prototype_ `ECompileState GetCompileState() const;` — Inspects the graph description to determine the current compile state without recompiling.
- L35 _public prototype_ `FSlateIcon GetCompileStatusIcon() const;` — Returns the toolbar icon matching the current compile state.
- L39 _protected prototype_ `FName GetToolkitFName() const override;`
- L40 _protected prototype_ `FText GetBaseToolkitName() const override;`
- L41 _protected prototype_ `FString GetWorldCentricTabPrefix() const override;`
- L42 _protected prototype_ `FLinearColor GetWorldCentricTabColorScale() const override;`
- L43 _protected prototype_ `void RegisterTabSpawners(TSharedRef<FTabManager> const& InTabManager) override;`
- L44 _protected prototype_ `void UnregisterTabSpawners(TSharedRef<FTabManager> const& InTabManager) override;`
- L48 _protected prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L49 _protected prototype_ `FString GetReferencerName() const override;`
- L53 _protected prototype_ `void OnItemSelected(EComputeGraphItemKind Kind, int32 Index, FName Name);` — Updates the details panel and HLSL editor to reflect the newly selected item.
- L55 _protected prototype_ `void OnAddItem(EComputeGraphItemKind Kind);` — Appends a new kernel, interface, or binding object with a generated unique name.
- L57 _protected prototype_ `void OnDeleteItem(EComputeGraphItemKind Kind, int32 Index);` — Removes the item at Index and clears any dangling pin references to it.
- L59 _protected prototype_ `void OnDuplicateItem(EComputeGraphItemKind Kind, int32 Index);` — Appends a deep copy of the item at Index with a "_Copy" suffix on its name.
- L61 _protected prototype_ `void OnRenameItem(EComputeGraphItemKind Kind, int32 Index, FName NewName);` — Renames the item at Index and propagates the new name to any referencing pins.
- L63 _protected prototype_ `void OnKernelSelected(FName KernelName);` — Loads the selected kernel's source into the HLSL editor.
- L65 _protected prototype_ `void OnHlslTextCommitted(FName KernelName, FString const& NewText);` — Syncs pin lists from the new HLSL text and marks the graph dirty.
- L67 _protected prototype_ `void OnGraphNodeClicked(FName NodeName, bool bIsKernel);` — Selects the corresponding kernel or interface in the navigator when a graph node is clicked.
- L69 _protected prototype_ `void OnCompileOutputChanged(TArray<FComputeKernelCompileMessage> const& NewMessages);` — Appends newly arrived compile messages to the output list view.
- L71 _protected prototype_ `void OnOutputSelectionChanged(TSharedPtr<FComputeKernelCompileMessage> Selected, ESelectInfo::Type SelectInfo);` — Navigates the navigator to the kernel associated with the clicked output message.
- L75 _private prototype_ `void Init(UEditableComputeGraph* InAsset, EToolkitMode::Type InMode, TSharedPtr<IToolkitHost> InToolkitHost);` — Initialises the toolkit: creates the layout, registers tab spawners, and binds all callbacks.
- L78 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Navigator(FSpawnTabArgs const& Args);` — Tab spawn functions.
- L79 _private prototype_ `TSharedRef<SDockTab> SpawnTab_HlslEditor(FSpawnTabArgs const& Args);`
- L80 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphView(FSpawnTabArgs const& Args);`
- L81 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Details(FSpawnTabArgs const& Args);`
- L82 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Output(FSpawnTabArgs const& Args);`
- L85 _private prototype_ `TSharedRef<ITableRow> GenerateOutputRow(TSharedPtr<FComputeKernelCompileMessage> Message, TSharedRef<STableViewBase> const& OwnerTable);` — Builds one row in the compile output list view.
- L88 _private prototype_ `void ExtendToolbar();` — Adds the compile button and status icon to the asset editor toolbar.
- L90 _private prototype_ `void RefreshHlslBoundFunctions(FName KernelName);` — Pushes the current kernel's bound pin names into the HLSL editor for syntax highlighting.
- L92 _private prototype_ `void RefreshNavigatorAndDetails();` — Marks the graph dirty, refreshes the navigator, graph view, and details panel.
- L95 _private prototype_ `static FName GenerateUniqueName(TArray<FName> const& Existing, FStringView Base);` — Unique name helper. Returns "Base", "Base1", "Base2" etc while avoiding names in Existing.
- L99 _private member_ `TObjectPtr<UEditableComputeGraph> Asset;` — The asset being edited.
- L102 _private member_ `TSharedPtr<SComputeGraphNavigator> NavigatorWidget;` — Tree-view panel listing kernels, interfaces, and binding objects.
- L104 _private member_ `TSharedPtr<SComputeGraphHlslEditor> HlslEditorWidget;` — Multi-line HLSL editor panel.
- L106 _private member_ `TSharedPtr<SComputeGraphView> GraphViewWidget;` — Bipartite graph visualisation panel.
- L108 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details panel showing per-item properties.
- L111 _private member_ `TSharedPtr<SListView<TSharedPtr<FComputeKernelCompileMessage>>> OutputListView;` — The list view widget in the Output tab.
- L113 _private member_ `TArray<TSharedPtr<FComputeKernelCompileMessage>> OutputMessages;` — Messages currently displayed in the Output tab; repopulated on each compile.
- L115 _private member_ `FDelegateHandle CompileOutputHandle;` — Bound to UEditableComputeGraph::OnCompileOutputChanged to refresh the output tab.
- L118 _private member_ `TSharedPtr<FComputeGraphEditorSelection> EditorSelection;` — Shared with FEditableComputeGraphDetailCustomization; updated on every selection change.
- L121 _private member_ `bool bDirty = true;` — True whenever graph data has been mutated since the last successful compile.
- L124 _private member_ `FName CachedSelectedItemName = NAME_None;` — Name of the currently selected Interface or BindingObject, captured at selection time so OnFinishedChangingProperties can detect in-panel renames and apply cross-reference fixups.
- L127 _private member_ `static FName const TabId_Navigator;` — Tab Id FNames.
- L128 _private member_ `static FName const TabId_HlslEditor;`
- L129 _private member_ `static FName const TabId_GraphView;`
- L130 _private member_ `static FName const TabId_Details;`
- L131 _private member_ `static FName const TabId_Output;`

#### enum `FEditableComputeGraphEditorToolkit::ECompileState`  
`enum class ECompileState`  
_L31-31_
- desc: Whether the graph is compiled and up to date, needs recompile, or has errors.
- L31 _public enumerator_ `enum class ECompileState { UpToDate, NeedsCompile, Broken }; ECompileState GetCompileState() const; FSlateIcon GetCompileStatusIcon() const; protected:` — Whether the graph is compiled and up to date, needs recompile, or has errors.
- L31 _public enumerator_ `enum class ECompileState { UpToDate, NeedsCompile, Broken }; ECompileState GetCompileState() const; FSlateIcon GetCompileStatusIcon() const; protected:` — Whether the graph is compiled and up to date, needs recompile, or has errors.
- L31 _public enumerator_ `enum class ECompileState { UpToDate, NeedsCompile, Broken }; ECompileState GetCompileState() const; FSlateIcon GetCompileStatusIcon() const; protected:` — Whether the graph is compiled and up to date, needs recompile, or has errors.

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/EditableComputeGraphFactory.h` (Private)


#### class `UEditableComputeGraphFactory`  
`class UEditableComputeGraphFactory : public UFactory`  
_L9-18_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L13 _private prototype_ `UEditableComputeGraphFactory();`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/HlslExternalPinParser.h` (Private)


#### class `FHlslExternalPinParser`  
`class FHlslExternalPinParser`  
_L8-40_
- desc: Helper functions for finding function bindings in HLSL source.
- L27 _public prototype_ `static TArray<FPinDeclaration> FindExternalPins(FStringView SourceText);` — Scan SourceText for DataInterface function calls. The convention used by UEditableComputeGraph kernel authoring is that DataInterface function calls have the "DI_" prefix in the kernel. These will be presented in the toolkit UI for binding. The input/output direction is inferred from call-site context. If DI_*() is a standalone statement (only whitespace precedes it on the same line) then the call discards its return value and we make the assumption it is an output pin.
- L34 _public prototype_ `static TArray<FString> FindFunctionDefinitions(FStringView SourceText);` — Scan SourceText for top level function definitions. These are signatures followed by a body. We returns the bare function names in declaration order. This is usful for finding potential kernel EntryPoints.
- L39 _public prototype_ `static bool FunctionExistsInText(FStringView SourceText, FString const& FunctionName);` — Returns true if FunctionName appears in SourceText as a whole-word identifier followed by '('.

#### struct `FHlslExternalPinParser::FPinDeclaration`  
`struct FPinDeclaration`  
_L12-18_
- desc: Result of one DI_ call site found by FindExternalPins().
- L15 _public member_ `FString FunctionName;` — Full function name including the DI_ prefix, e.g. "DI_ReadValue".
- L17 _public member_ `bool bIsOutput = false;` — True when the call is considered to be an output.

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraphEditor/Private/ComputeFramework/KernelPinCustomization.h` (Private)


#### class `FKernelPinCustomization`  
`class FKernelPinCustomization : public IPropertyTypeCustomization`  
_L14-79_
- inherits: `IPropertyTypeCustomization`
- desc: Details panel customization for FKernelPin. Holds combo boxes for populating the DataInterface and function.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _protected prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L22 _protected prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _private prototype_ `void RefreshKernelFunctionNameOptions();` — Rebuilds the kernel function combo options from the owning kernel's HLSL source.
- L29 _private prototype_ `void RefreshInterfaceNameOptions();` — Rebuilds the data interface combo options from the graph's interface list.
- L31 _private prototype_ `void RefreshFunctionNameOptions();` — Rebuilds the DI function combo options from the currently selected interface's declared functions.
- L34 _private prototype_ `bool NeedsAttention() const;` — Returns true when the pin is orphaned or any required field is unset.
- L36 _private prototype_ `FText GetHeaderSummaryText() const;` — Text shown in the collapsed header row: "KernelFn → Interface::DIFn".
- L38 _private prototype_ `FSlateColor GetHeaderSummaryColor() const;` — Orange when NeedsAttention(), foreground colour otherwise.
- L40 _private prototype_ `FText GetOrphanedTooltipText() const;` — Tooltip explaining why the pin needs attention (orphaned or incomplete).
- L42 _private prototype_ `FText GetCurrentKernelFunctionNameText() const;` — Current value of KernelFunctionName as display text.
- L44 _private prototype_ `FText GetCurrentInterfaceNameText() const;` — Current value of DataInterfaceName as display text.
- L46 _private prototype_ `FText GetCurrentFunctionNameText() const;` — Current value of DataInterfaceFunctionName as display text.
- L49 _private prototype_ `void OnKernelFunctionSelected(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Writes the selected kernel function name back to the property.
- L51 _private prototype_ `void OnInterfaceSelected(TSharedPtr<FName> NewValue, ESelectInfo::Type SelectInfo);` — Writes the selected interface name back to the property and refreshes the function list.
- L53 _private prototype_ `void OnFunctionSelected(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Writes the selected DI function name back to the property.
- L56 _private member_ `bool bIsInput = true;` — True when customizing an input pin. False for an output pin.
- L59 _private member_ `TSharedPtr<IPropertyHandle> StructHandle;` — Handle for the FKernelPin struct itself.
- L61 _private member_ `TSharedPtr<IPropertyHandle> KernelFnHandle;` — Handle for FKernelPin::KernelFunctionName.
- L63 _private member_ `TSharedPtr<IPropertyHandle> InterfaceNameHandle;` — Handle for FKernelPin::DataInterfaceName.
- L65 _private member_ `TSharedPtr<IPropertyHandle> FunctionNameHandle;` — Handle for FKernelPin::DataInterfaceFunctionName.
- L67 _private member_ `TSharedPtr<IPropertyHandle> OrphanedHandle;` — Handle for FKernelPin::bOrphaned.
- L69 _private member_ `TSharedPtr<IPropertyHandle> KernelSourceHandle;` — Handle for the owning FComputeGraphKernelDesc::SourceText.
- L71 _private member_ `TSharedPtr<IPropertyHandle> KernelEntryPointHandle;` — Handle for the owning FComputeGraphKernelDesc::EntryPoint.
- L74 _private member_ `TArray<TSharedPtr<FString>> KernelFunctionNameOptions;` — Populated by RefreshKernelFunctionNameOptions(). Drives the kernel function combo box.
- L76 _private member_ `TArray<TSharedPtr<FName>> InterfaceNameOptions;` — Populated by RefreshInterfaceNameOptions(). Drives the data interface combo box.
- L78 _private member_ `TArray<TSharedPtr<FString>> FunctionNameOptions;` — Populated by RefreshFunctionNameOptions(). Drives the DI function combo box.
