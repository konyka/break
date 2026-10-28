# Plugins / StateTreeDeveloper

- module root: `Plugins/Runtime/StateTree/Source/StateTreeDeveloper`
- headers: 6; symbols: 135
- symbol kinds: class=6, delegate=2, function=8, macro=4, member=39, namespace=17, prototype=52, struct=7
- PrivateDependencyModuleNames: CoreUObject, InputCore, Slate, StateTreeModule
- PublicDependencyModuleNames: Core, SlateCore

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Internal/Debugger/SCompactTreeDebuggerView.h` (Internal)


#### struct `UE::StateTree::Editor::CompactTreeView::FStateItemDebuggerData`  
`struct FStateItemDebuggerData : public FStateItemCustomData`  
_L20-31_
- reflection: `USTRUCT()`
- inherits: `FStateItemCustomData`
- L24 _public prototype_ `FStateItemDebuggerData() = default;`
- L25 _public function_ `explicit FStateItemDebuggerData(const bool bIsActive) : bIsActive(bIsActive)`
- L30 _public member_ `bool bIsActive = false;`

#### class `UE::StateTree::Editor::SCompactTreeDebuggerView`  
`class SCompactTreeDebuggerView final : public SCompactTreeView`  
_L46-78_
- inherits: `SCompactTreeView`
- desc: Widget that displays a list of State Tree nodes which match base types and specified schema. Can be used e.g. in popup menus to select node types.
- L50 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`
- L52 _public function_ `SLATE_BEGIN_ARGS(SCompactTreeDebuggerView)`
- L54 _public prototype_ `SLATE_ATTRIBUTE(FStateTreeTraceActiveStates, ActiveStates) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TNotNull<const UStateTree*> StateTree);`
- L60 _private prototype_ `virtual TSharedRef<FStateItem> CreateStateItemInternal() const override;`
- L61 _private prototype_ `virtual void CacheStatesInternal() override;`
- L62 _private prototype_ `virtual TSharedRef<SWidget> CreateNameWidgetInternal(TSharedPtr<FStateItem> Item) const override;`
- L72 _private prototype_ `void CacheStateRecursive(TNotNull<const FStateTreeTraceActiveStates::FAssetActiveStates*> InAssetActiveStates , TSharedPtr<FStateItem> InParentItem , const uint16 InStateIdx , TArray<FProcessedState>& OutProcessedStates);`
- L77 _private member_ `TAttribute<FStateTreeTraceActiveStates> AllActiveStates;`

#### struct `UE::StateTree::Editor::SCompactTreeDebuggerView::FProcessedState`  
`struct FProcessedState`  
_L64-70_
- L66 _public prototype_ `bool operator==(const FProcessedState& Other) const = default;`
- L68 _public member_ `FObjectKey StateTree;`
- L69 _public member_ `uint16 StateIdx;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StateTree` (scope `UE`)
- L14 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L17 _namespace_ `namespace CompactTreeView` (scope `UE::StateTree::Editor`)
- L37 _macro_ `#define UE_API STATETREEDEVELOPER_API`
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace StateTree` (scope `UE`)
- L39 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Internal/Debugger/SStateTreeFrameEventsView.h` (Internal)


#### class `UE::StateTreeDebugger::SFrameEventsView`  
`class SFrameEventsView : public SCompoundWidget`  
_L25-52_
- inherits: `SCompoundWidget`
- desc: TreeView representing all traced events on a StateTree instance at a given frame
- L28 _public function_ `SLATE_BEGIN_ARGS(SFrameEventsView)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TNotNull<const UStateTree*> InStateTree);`
- L34 _public prototype_ `void SelectByPredicate(TFunctionRef<bool(const FStateTreeTraceEventVariantType& Event)> InPredicate);` — Selects an element in the list based on a predicate applied on the currently displayed events
- L37 _public prototype_ `void RequestRefresh(const FScrubState& InScrubState);` — Rebuilds the view from events for a given frame
- L41 _private prototype_ `void ExpandAll(const TArray<TSharedPtr<FFrameEventTreeElement>>& Items);` — Recursively sets tree items as expanded.
- L43 _private prototype_ `static void GenerateElementsForProperties(const FStateTreeTraceEventVariantType& Event, const TSharedRef<FFrameEventTreeElement>& ParentElement);`
- L45 _private member_ `TWeakObjectPtr<const UStateTree> WeakStateTree;`
- L48 _private member_ `TArray<TSharedPtr<FFrameEventTreeElement>> EventsTreeElements;` — All trace events received for a given instance.
- L51 _private member_ `TSharedPtr<STreeView<TSharedPtr<FFrameEventTreeElement>>> EventsTreeView;` — Tree view displaying the frame events of the instance associated to the selected track.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STATETREEDEVELOPER_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Internal/Widgets/SCompactTreeView.h` (Internal)


#### struct `UE::StateTree::Editor::CompactTreeView::FStateItemCustomData`  
`struct FStateItemCustomData`  
_L31-34_
- reflection: `USTRUCT()`
- desc: Base type that SCompactTreeView derived classes can inherit from to store additional data through the instanced struct inside SCompactTreeView::FStateItem. USTRUCT is required to be compatible with instanced struct but properties inside the struct are not exposed to the garbage collector.

#### class `UE::StateTree::Editor::SCompactTreeView`  
`class SCompactTreeView : public SCompoundWidget`  
_L41-167_
- inherits: `SCompoundWidget`
- desc: Widget that displays a list of State Tree states.
- L45 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`
- L47 _public function_ `SLATE_BEGIN_ARGS(SCompactTreeView) : _TextStyle(nullptr) , _SelectionMode(ESelectionMode::Single)`
- L51 _public prototype_ `SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle) SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TNotNull<const UStateTree*> StateTree);`
- L60 _public prototype_ `TSharedPtr<SWidget> GetWidgetToFocusOnOpen();` — @returns widget to focus (search box) when the picker is opened.
- L62 _public prototype_ `void SetSelection(TConstArrayView<FGuid> Selection);`
- L63 _public prototype_ `TArray<FGuid> GetSelection() const;`
- L65 _public prototype_ `void Refresh();`
- L94 _protected prototype_ `virtual TSharedRef<FStateItem> CreateStateItemInternal() const;` — Creates the item to represent the State in the tree view. Can be overridden to create with some specific type of custom data. Default implementation returns an item without a custom data struct.
- L100 _protected prototype_ `virtual TSharedRef<STableRow<TSharedPtr<FStateItem>>> GenerateStateItemRowInternal( TSharedPtr<FStateItem> Item , const TSharedRef<STableViewBase>& OwnerTable , TSharedRef<SHorizontalBox> Box);` — Called by GenerateStateItemRow to create the table row for a given item using the provided box. Derived classes can override to add extra slots to the box and to customize the row.
- L106 _protected prototype_ `virtual void OnSelectionChangedInternal(TConstArrayView<TSharedPtr<FStateItem>> SelectedStates);` — Callback to allow derived classes to perform additional operations when selection changed.
- L109 _protected prototype_ `virtual void OnUpdatingFilteredRootInternal();` — Callback to allow derived classes to perform additional operations when filtered root is about to get updated and the tree refreshed.
- L112 _protected prototype_ `virtual void CacheStatesInternal() = 0;` — Callback that derived classes need to implement to build their tree hierarchy.
- L119 _protected prototype_ `virtual TSharedRef<SWidget> CreateNameWidgetInternal(TSharedPtr<FStateItem> Item) const;` — Create widget to represent the state name. Base implementation creates a text block with search highlighting and enabled status. Derived classes can override to add extra layer (e.g., borders)
- L121 _protected prototype_ `static void FindStatesByIDRecursive(const TSharedPtr<FStateItem>& Item, TConstArrayView<FGuid> StateIDs, TArray<TSharedPtr<FStateItem>>& OutStates);`
- L123 _protected member_ `TWeakObjectPtr<const UStateTree> WeakStateTree = nullptr;`
- L124 _protected member_ `TSharedPtr<FStateItem> RootItem;`
- L125 _protected member_ `TSharedPtr<FStateItem> FilteredRootItem;`
- L135 _private prototype_ `void CacheStates();`
- L136 _private prototype_ `void GetStateItemChildren(TSharedPtr<FStateItem> Item, TArray<TSharedPtr<FStateItem>>& OutItems) const;`
- L137 _private prototype_ `TSharedRef<ITableRow> GenerateStateItemRow(TSharedPtr<FStateItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L139 _private prototype_ `void OnStateItemSelected(TSharedPtr<FStateItem> SelectedItem, ESelectInfo::Type);`
- L140 _private prototype_ `void OnStateItemExpansionChanged(TSharedPtr<FStateItem> ExpandedItem, bool bInExpanded) const;`
- L141 _private prototype_ `void OnSearchBoxTextChanged(const FText& NewText);`
- L143 _private prototype_ `void UpdateFilteredRoot(bool bRestoreSelection = true);`
- L145 _private prototype_ `static int32 FilterStateItemChildren(const TArray<FString>& FilterStrings, const bool bParentMatches, const TArray<TSharedPtr<FStateItem>>& SourceArray, TArray<TSharedPtr<FStateItem>>& OutDestArray);`
- L146 _private prototype_ `static bool FindStateByIDRecursive(const TSharedPtr<FStateItem>& Item, const FGuid StateID, TArray<TSharedPtr<FStateItem>>& OutPath);`
- L148 _private prototype_ `void ExpandAll(const TArray<TSharedPtr<FStateItem>>& Items);`
- L149 _private prototype_ `void RestoreExpansionState();`
- L151 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L152 _private member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L154 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L155 _private member_ `TSharedPtr<STreeView<TSharedPtr<FStateItem>>> StateItemTree;`
- L158 _private member_ `const FTextBlockStyle* TextStyle = nullptr;` — Style used for the State name
- L160 _private member_ `TArray<FString> FilterStrings;`
- L162 _private member_ `bool bIsSettingSelection = false;`
- L163 _private member_ `bool bIsRestoringExpansion = false;`
- L166 _private member_ `static TMap<FObjectKey, FStateExpansionState> StateExpansionStates;` — Save expansion state for each base node type.

#### struct `UE::StateTree::Editor::SCompactTreeView::FStateItem`  
`struct FStateItem : TSharedFromThis<FStateItem>`  
_L69-87_
- inherits: `TSharedFromThis<FStateItem>`
- desc: Stores info about state
- L71 _public prototype_ `FStateItem() = default;`
- L72 _public function_ `FStateItem(const FText& InDesc, const FText& InTooltipText, const FSlateBrush* InIcon) : Desc(InDesc) , TooltipText(InTooltipText) , Icon(InIcon)`
- L79 _public member_ `FText Desc;`
- L80 _public member_ `FText TooltipText;`
- L81 _public member_ `FGuid StateID = {};`
- L82 _public member_ `const FSlateBrush* Icon = nullptr;`
- L83 _public member_ `TInstancedStruct<CompactTreeView::FStateItemCustomData> CustomData;`
- L84 _public member_ `TArray<TSharedPtr<FStateItem>> Children;`
- L85 _public member_ `FSlateColor Color = FSlateColor(FLinearColor::White);`
- L86 _public member_ `bool bIsEnabled = true;`

#### struct `UE::StateTree::Editor::SCompactTreeView::FStateExpansionState`  
`struct FStateExpansionState`  
_L130-133_
- desc: Stores per session node expansion state for a node type.
- L132 _public member_ `TSet<FGuid> CollapsedStates;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API STATETREEDEVELOPER_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StateTree` (scope `UE`)
- L20 _namespace_ `namespace Editor` (scope `UE::StateTree`)
- L22 _namespace_ `namespace CompactTreeView` (scope `UE::StateTree::Editor`)
- L45 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, TConstArrayView<FGuid> );`

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Private/Debugger/SStateTreeDebuggerViewRow.h` (Private)


#### struct `UE::StateTreeDebugger::FFrameEventTreeElement`  
`struct FFrameEventTreeElement : TSharedFromThis<FFrameEventTreeElement>`  
_L20-32_
- inherits: `TSharedFromThis<FFrameEventTreeElement>`
- desc: An item in the StateTreeDebugger trace event tree
- L22 _public function_ `explicit FFrameEventTreeElement(const TraceServices::FFrame& Frame, const FStateTreeTraceEventVariantType& Event, const UStateTree* StateTree) : Frame(Frame), Event(Event), WeakStateTree(StateTree)`
- L27 _public member_ `TraceServices::FFrame Frame;`
- L28 _public member_ `FStateTreeTraceEventVariantType Event;`
- L29 _public member_ `TArray<TSharedPtr<FFrameEventTreeElement>> Children;`
- L30 _public member_ `FString Description;`
- L31 _public member_ `TWeakObjectPtr<const UStateTree> WeakStateTree;`

#### class `UE::StateTreeDebugger::SFrameEventViewRow`  
`class SFrameEventViewRow : public STableRow<TSharedPtr<FFrameEventTreeElement>>`  
_L38-52_
- inherits: `STableRow<TSharedPtr<FFrameEventTreeElement>>`
- desc: Widget for row inside the StateTreeDebugger TreeView.
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView, const TSharedPtr<FFrameEventTreeElement>& InElement);`
- L46 _private prototype_ `TSharedPtr<SWidget> CreateImageForEvent() const;`
- L47 _private prototype_ `const FTextBlockStyle& GetEventTextStyle() const;`
- L48 _private prototype_ `FText GetEventDescription() const;`
- L49 _private prototype_ `FText GetEventTooltip() const;`
- L51 _private member_ `TSharedPtr<FFrameEventTreeElement> Item;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Private/StateTreeRewindDebuggerRecordingExtension.h` (Private)


#### class `UE::StateTreeDebugger::FRewindDebuggerRecordingExtension`  
`class FRewindDebuggerRecordingExtension final : public IRewindDebuggerRuntimeExtension`  
_L10-15_
- inherits: `IRewindDebuggerRuntimeExtension`
- L12 _private prototype_ `virtual void RecordingStarted() override;`
- L13 _private prototype_ `virtual void RecordingStopped() override;`
- L14 _private prototype_ `virtual void Clear() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StateTreeDebugger` (scope `UE`)

### `Plugins/Runtime/StateTree/Source/StateTreeDeveloper/Public/StateTreeStyle.h` (Public)


#### class `FStateTreeStyle`  
`class FStateTreeStyle : public FSlateStyleSet`  
_L14-52_
- inherits: `FSlateStyleSet`
- L17 _public prototype_ `static FStateTreeStyle& Get();`
- L19 _public prototype_ `static const FSlateBrush* GetBrushForSelectionBehaviorType(EStateTreeStateSelectionBehavior InSelectionBehavior, bool bInHasChildren, EStateTreeStateType InStateType);`
- L42 _protected prototype_ `explicit FStateTreeStyle(const FName& InStyleSetName);`
- L44 _protected prototype_ `static void Register();`
- L45 _protected prototype_ `static void Unregister();`
- L47 _protected member_ `static const FString EngineSlateContentDir;`
- L48 _protected member_ `static const FString StateTreePluginContentDir;`
- L49 _protected member_ `static const FLazyName StateTitleTextStyleName;`
- L51 _private prototype_ `FStateTreeStyle();`

#### struct `FStateTreeStyle::FContentRootScope`  
`struct FContentRootScope`  
_L22-38_
- L24 _public function_ `FContentRootScope(FSlateStyleSet* InStyle, const FString& NewContentRoot) : Style(InStyle) , PreviousContentRoot(InStyle->GetContentRootDir())`
- L31 _public function_ `~FContentRootScope()`
- L36 _private member_ `FSlateStyleSet* Style;`
- L37 _private member_ `FString PreviousContentRoot;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API STATETREEDEVELOPER_API`
