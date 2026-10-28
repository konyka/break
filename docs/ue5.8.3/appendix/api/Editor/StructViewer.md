# Editor / StructViewer

- module root: `Source/Editor/StructViewer`
- headers: 5; symbols: 164
- symbol kinds: class=8, delegate=2, enum=4, enumerator=11, function=20, macro=1, member=45, prototype=73
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, EditorWidgets
- PrivateDependencyModuleNames: ApplicationCore, ContentBrowserData, Core, CoreUObject, EditorFramework, Engine, InputCore, Settings, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: AssetRegistry, EditorWidgets, WorkspaceMenuStructure

### `Source/Editor/StructViewer/Private/SStructViewer.h` (Private)


#### class `SStructViewer`  
`class SStructViewer : public SCompoundWidget`  
_L26-238_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SStructViewer)`
- L33 _public prototype_ `SLATE_ARGUMENT(FOnStructPicked, OnStructPickedDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FStructViewerInitializationOptions& InInitOptions);`
- L46 _public prototype_ `virtual TSharedRef<SWidget> GetContent();` — Gets the widget contents of the app
- L48 _public prototype_ `virtual ~SStructViewer();`
- L51 _public prototype_ `virtual void ClearSelection();` — Empty the selection set.
- L54 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L55 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L56 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L57 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L60 _public prototype_ `virtual bool IsStructAllowed(const UScriptStruct* InStruct) const;` — Test to see whether the given struct would be allowed by this struct viewer
- L63 _public prototype_ `static void DestroyStructHierarchy();` — Destroys the internal Struct Hierarchy database
- L71 _private prototype_ `void OnGetChildrenForStructViewerTree(TSharedPtr<FStructViewerNode> InParent, TArray<TSharedPtr<FStructViewerNode>>& OutChildren);` — Retrieves the children for the input node. @param InParent				The parent node to retrieve the children from. @param OutChildren			List of children for the parent node.
- L74 _private prototype_ `TSharedRef<ITableRow> OnGenerateRowForStructViewer(TSharedPtr<FStructViewerNode> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Creates the row widget when called by Slate when an item appears on the tree.
- L77 _private prototype_ `FReply OnDragDetected(const FGeometry& Geometry, const FPointerEvent& PointerEvent) override;` — Invoked when the user attempts to drag an item out of the struct browser
- L80 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called by Slate when the filter box changes text.
- L83 _private prototype_ `void OnFilterTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Called when enter is hit in search box
- L86 _private prototype_ `void OnStructViewerSelectionChanged(TSharedPtr<FStructViewerNode> Item, ESelectInfo::Type SelectInfo);` — Called by Slate when an item is selected from the tree/list.
- L89 _private prototype_ `void OnStructViewerExpansionChanged(TSharedPtr<FStructViewerNode> Item, bool bExpanded);` — Called by Slate when an item is expanded/collapsed from the tree/list.
- L96 _private prototype_ `void SetAllExpansionStates(bool bInExpansionState);` — Sets all expansion states in the tree. @param bInExpansionState			The expansion state to set the tree to.
- L104 _private prototype_ `void SetAllExpansionStates_Helper(TSharedPtr<FStructViewerNode> InNode, bool bInExpansionState);` — A helper function to recursively set the tree. @param	InNode						The current node in the tree. @param	bInExpansionState			The expansion state to set the tree to.
- L111 _private prototype_ `void ToggleExpansionState_Helper(TSharedPtr<FStructViewerNode> InNode);` — A helper function to toggle expansion state of a single node @param	InNode						The node to toggle expansion.
- L114 _private prototype_ `TSharedPtr<SWidget> BuildMenuWidget();` — Builds the right click menu widget for the selected node.
- L121 _private prototype_ `bool ExpandFilteredInNodes(TSharedPtr<FStructViewerNode> InNode);` — Recursive function to expand nodes not filtered out of the tree @param	InNode				The current node to inspect for expansion. @return bool				true if the child expanded, thus the parent should.
- L126 _private prototype_ `void MapExpansionStatesInTree(TSharedPtr<FStructViewerNode> InItem);` — Recursive function to map the expansion states of items in the tree. @param InItem		The current item to examine the expansion state of.
- L131 _private prototype_ `void SetExpansionStatesInTree(TSharedPtr<FStructViewerNode> InItem);` — Recursive function to set the expansion states of items in the tree. @param InItem		The current item to set the expansion state of.
- L134 _private prototype_ `void Refresh();` — Sends a requests to the Struct Viewer to refresh itself the next chance it gets
- L137 _private prototype_ `void Populate();` — Populates the tree with items based on the current filter.
- L140 _private prototype_ `const TArray<TSharedPtr<FStructViewerNode>> GetSelectedItems() const;` — Returns an array of the currently selected StructViewerNodes
- L143 _private prototype_ `virtual void ExpandRootNodes();` — Expands all of the root nodes
- L146 _private prototype_ `FSlateColor GetViewButtonForegroundColor() const;` — Returns the foreground color for the view button
- L149 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent();` — Handler for when the view combo button is clicked
- L152 _private prototype_ `FText GetStructCountText() const;` — Gets the text for the struct count label
- L155 _private prototype_ `void SetCurrentDeveloperViewType(EStructViewerDeveloperType NewType);` — Sets the view type and updates lists accordingly
- L158 _private prototype_ `EStructViewerDeveloperType GetCurrentDeveloperViewType() const;` — Gets the current view type (list or tile)
- L161 _private prototype_ `bool IsCurrentDeveloperViewType(EStructViewerDeveloperType ViewType) const;` — Returns true if ViewType is the current view type
- L164 _private prototype_ `void ToggleShowInternalStructs();` — Toggle whether internal use structs should be shown or not
- L167 _private prototype_ `bool IsShowingInternalStructs() const;` — Whether or not it's possible to show internal use structs
- L170 _private prototype_ `bool IsToggleShowInternalStructsAllowed() const;` — Whether or not it's possible to show internal use structs
- L173 _private prototype_ `const int GetNumItems() const;` — Get the total number of structs passing the current filters.
- L176 _private prototype_ `int32 CountTreeItems(FStructViewerNode* Node);` — Count the number of tree items in the specified hierarchy
- L179 _private prototype_ `void HandleSettingChanged(FName PropertyName);` — Handle the settings for StructViewer changing.
- L182 _private prototype_ `void GetInternalOnlyStructs(TArray<TSoftObjectPtr<const UScriptStruct>>& Structs);` — Accessor for the struct names that have been marked as internal only in settings
- L185 _private prototype_ `void GetInternalOnlyPaths(TArray<FDirectoryPath>& Paths);` — Accessor for the struct paths that have been marked as internal only in settings
- L189 _private member_ `FStructViewerInitializationOptions InitOptions;` — Init options, cached
- L192 _private member_ `TArray<TSharedPtr<FStructViewerNode>> RootTreeItems;` — The items to be displayed in the tree.
- L195 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilterPtr;` — Compiled filter search terms.
- L198 _private member_ `TSharedPtr<STreeView<TSharedPtr<FStructViewerNode>>> StructTree;` — Holds the Slate Tree widget which holds the structs for the Struct Viewer.
- L201 _private member_ `TSharedPtr<SListView<TSharedPtr<FStructViewerNode>>> StructList;` — Holds the Slate List widget which holds the structs for the Struct Viewer.
- L204 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The struct Search Box, used for filtering the structs visible.
- L207 _private member_ `bool bShowUnloadedStructs;` — true to filter for unloaded structs.
- L210 _private member_ `bool bEnableStructDynamicLoading;` — true to allow struct dynamic loading.
- L213 _private member_ `FOnStructPicked OnStructPicked;` — Callback that's fired when a struct is selected while in 'struct picking' mode
- L216 _private member_ `bool bSaveExpansionStates;` — true if expansions states should be saved when compiling.
- L219 _private member_ `TMap<FSoftObjectPath, bool> ExpansionStateMap;` — The map holding the expansion state map for the tree.
- L222 _private member_ `bool bNeedsRefresh;` — True if the Struct Viewer needs to be repopulated at the next appropriate opportunity, occurs whenever structs are added, removed, renamed, etc.
- L225 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L228 _private member_ `bool bPendingSetExpansionStates;` — True if we need to set the tree expansion states according to our local copy next tick
- L231 _private member_ `bool bCanShowInternalStructs;` — Indicates if the 'Show Internal Structs' option should be enabled or disabled
- L234 _private member_ `TSharedPtr<SComboButton> ViewOptionsComboButton;` — The button that displays view options
- L237 _private member_ `int32 NumStructs;` — Number of structs that passed the filter

### `Source/Editor/StructViewer/Private/StructViewerNode.h` (Private)


#### class `FStructViewerNodeData`  
`class FStructViewerNodeData : public TSharedFromThis<FStructViewerNodeData>`  
_L21-111_
- inherits: `TSharedFromThis<FStructViewerNodeData>`
- desc: Common data representing an unfiltered hierarchy of nodes
- L25 _public prototype_ `FStructViewerNodeData();` — Create a dummy node
- L28 _public prototype_ `explicit FStructViewerNodeData(const UScriptStruct* InStruct);` — Create a node representing the given struct
- L31 _public prototype_ `explicit FStructViewerNodeData(const FAssetData& InStructAsset);` — Create a node representing the given struct asset (may be unloaded)
- L34 _public function_ `const FString& GetStructName() const` — Get the unlocalized name of the struct we represent
- L40 _public function_ `FText GetStructDisplayName() const` — Get the localized name of the struct we represent
- L46 _public function_ `FSoftObjectPath GetStructPath() const` — Get the full object path to the struct we represent
- L52 _public function_ `FSoftObjectPath GetParentStructPath() const` — Get the full object path to the parent of the struct we represent
- L58 _public prototype_ `const UScriptStruct* GetStruct() const;` — Get the struct that we represent (for loaded struct assets, or native structs)
- L61 _public prototype_ `const UUserDefinedStruct* GetStructAsset() const;` — Get the struct asset that we represent (for loaded struct assets)
- L67 _public prototype_ `bool LoadStruct() const;` — Trigger a load of the struct we represent. @return True if the struct was loaded (or was already loaded), false otherwise.
- L70 _public function_ `TSharedPtr<FStructViewerNodeData> GetParentNode() const` — Get the pointer to the parent data node (if any)
- L76 _public function_ `const TArray<TSharedPtr<FStructViewerNodeData>>& GetChildNodes() const` — Get the list of child data nodes
- L82 _public prototype_ `void AddChild(const TSharedRef<FStructViewerNodeData>& InChild);` — Adds the specified child to this node
- L85 _public prototype_ `void AddUniqueChild(const TSharedRef<FStructViewerNodeData>& InChild);` — Adds the specified child to this node, only if a node representing the struct doesn't already exist as a child
- L88 _public prototype_ `bool RemoveChild(const FSoftObjectPath& InStructPath);` — Remove the child representing the given struct path (if present)
- L92 _private member_ `FString StructName;` — The unlocalized name of the struct we represent
- L95 _private member_ `mutable FText StructDisplayName;` — The localized name of the struct we represent
- L98 _private member_ `FSoftObjectPath StructPath;` — The full object path to the struct we represent
- L101 _private member_ `FSoftObjectPath ParentStructPath;` — The full object path to the parent of the struct we represent
- L104 _private member_ `mutable TWeakObjectPtr<const UScriptStruct> Struct;` — The struct that we represent (for loaded struct assets, or native structs)
- L107 _private member_ `TWeakPtr<FStructViewerNodeData> ParentNode;` — Pointer to the parent data node (if any)
- L110 _private member_ `TArray<TSharedPtr<FStructViewerNodeData>> ChildNodes;` — List of child data nodes

#### class `FStructViewerNode`  
`class FStructViewerNode : public TSharedFromThis<FStructViewerNode>`  
_L114-237_
- inherits: `TSharedFromThis<FStructViewerNode>`
- desc: Filtered data representing a filtered hierarchy of nodes
- L118 _public prototype_ `FStructViewerNode();` — Create a dummy node
- L121 _public prototype_ `FStructViewerNode(const TSharedRef<FStructViewerNodeData>& InData, const TSharedPtr<IPropertyHandle>& InPropertyHandle, const bool InPassedFilter);` — Create a node representing the given data
- L124 _public function_ `const FString& GetStructName() const` — Get the unlocalized name of the struct we represent
- L130 _public function_ `FText GetStructDisplayName() const` — Get the localized name of the struct we represent
- L136 _public prototype_ `FText GetStructDisplayName(const EStructViewerNameTypeToDisplay InNameType) const;` — Get the display name of the struct we represent, built based on the given option
- L139 _public function_ `FSoftObjectPath GetStructPath() const` — Get the full object path to the struct we represent
- L145 _public function_ `FSoftObjectPath GetParentStructPath() const` — Get the full object path to the parent of the struct we represent
- L151 _public function_ `const UScriptStruct* GetStruct() const` — Get the struct that we represent (for loaded struct assets, or native structs)
- L157 _public function_ `const UUserDefinedStruct* GetStructAsset() const` — Get the struct asset that we represent (for loaded struct assets)
- L166 _public function_ `bool LoadStruct() const` — Trigger a load of the struct we represent. @return True if the struct was loaded (or was already loaded), false otherwise.
- L172 _public function_ `TSharedPtr<FStructViewerNode> GetParentNode() const` — Get the pointer to the parent node (if any)
- L178 _public function_ `const TArray<TSharedPtr<FStructViewerNode>>& GetChildNodes() const` — Get the list of child nodes
- L184 _public prototype_ `void AddChild(const TSharedRef<FStructViewerNode>& InChild);` — Adds the specified child to this node
- L187 _public prototype_ `void AddUniqueChild(const TSharedRef<FStructViewerNode>& InChild);` — Adds the specified child to this node, only if a node representing the struct doesn't already exist as a child
- L190 _public prototype_ `void SortChildren();` — Sort the child nodes based on FStructViewerNode::SortPredicate
- L193 _public prototype_ `void SortChildrenRecursive();` — Sort the child nodes recursively based on FStructViewerNode::SortPredicate
- L196 _public prototype_ `static bool SortPredicate(const TSharedPtr<FStructViewerNode>& InA, const TSharedPtr<FStructViewerNode>& InB);` — Predicate function that can be used to sort instances by struct name
- L199 _public prototype_ `static void SortNodes(TArray<TSharedPtr<FStructViewerNode>>& Nodes, const TSharedPtr<IPropertyHandle>& PropertyHandle = { });` — Sorts the array of nodes either by a custom sort function, or by using the default one (::SortPredicate)
- L202 _public prototype_ `bool IsRestricted() const;` — Check whether this struct is restricted for the specific context
- L205 _public function_ `const TSharedPtr<IPropertyHandle>& GetPropertyHandle() const` — Get the property this filtered node will be working on
- L211 _public function_ `bool PassedFilter() const` — True if the struct passed the filter
- L217 _public function_ `void PassedFilter(const bool InPassedFilter)` — True if the struct passed the filter
- L224 _private member_ `TSharedRef<const FStructViewerNodeData> NodeData;` — Reference to the common data this filtered node represents
- L227 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property this filtered node will be working on
- L230 _private member_ `bool bPassedFilter;` — True if the struct passed the filter
- L233 _private member_ `TWeakPtr<FStructViewerNode> ParentNode;` — Pointer to the parent node (if any)
- L236 _private member_ `TArray<TSharedPtr<FStructViewerNode>> ChildNodes;` — List of child nodes

### `Source/Editor/StructViewer/Public/StructViewerFilter.h` (Public)


#### class `IStructViewerFilter`  
`class IStructViewerFilter`  
_L11-33_
- desc: Interface class for creating filters for the Struct Viewer.
- L14 _public prototype_ `virtual ~IStructViewerFilter() = default;`
- L23 _public prototype_ `virtual bool IsStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const UScriptStruct* InStruct, TSharedRef<class FStructViewerFilterFuncs> InFilterFuncs) = 0;` — Checks if a struct is allowed by this filter. @param InInitOptions				The Struct Viewer/Picker options. @param InStruct					The struct to be tested. @param InFilterFuncs				Useful functions for filtering.
- L32 _public prototype_ `virtual bool IsUnloadedStructAllowed(const FStructViewerInitializationOptions& InInitOptions, const FSoftObjectPath& InStructPath, TSharedRef<class FStructViewerFilterFuncs> InFilterFuncs) = 0;` — Checks if a struct is allowed by this filter. @param InInitOptions				The Struct Viewer/Picker options. @param InStructPath				The path of the unloaded struct to be tested. @param InFilterFuncs				Useful functions for filtering.

#### enum `EStructFilterReturn`  
`enum class EStructFilterReturn : uint8`  
_L35-40_
- L37 _public enumerator_ `Failed = 0`
- L38 _public enumerator_ `Passed`
- L39 _public enumerator_ `NoItems`

#### class `FStructViewerFilterFuncs`  
`class FStructViewerFilterFuncs`  
_L41-75_
- L44 _public prototype_ `virtual ~FStructViewerFilterFuncs() = default;`
- L54 _public prototype_ `virtual EStructFilterReturn IfInChildOfStructsSet(TSet<const UScriptStruct*>& InSet, const UScriptStruct* InStruct);` — Checks if the given struct is a child-of any of the structs in a set. @param InSet				The set to test against. @param InStruct			The struct to test against. @return					EFilterReturn::Passed if it is a child-of a struct in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L64 _public prototype_ `virtual EStructFilterReturn IfMatchesAllInChildOfStructsSet(TSet<const UScriptStruct*>& InSet, const UScriptStruct* InStruct);` — Checks if the given struct is a child-of ALL of the classes in a set. @param InSet				The set to test against. @param InStruct			The struct to test against. @return					EFilterReturn::Passed if it is a child-of ALL the structs in the set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.
- L74 _public prototype_ `virtual EStructFilterReturn IfInStructsSet(TSet<const UScriptStruct*>& InSet, const UScriptStruct* InStruct);` — Checks if the struct is in the structs set. @param InSet				The set to test against. @param InStruct			The struct to test against. @return					EFilterReturn::Passed if the struct is in the structs set, EFilterReturn::Failed if it is not, EFilterReturn::NoItems if the set is empty.

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API STRUCTVIEWER_API`

### `Source/Editor/StructViewer/Public/StructViewerModule.h` (Public)


#### enum `EStructViewerMode`  
`enum class EStructViewerMode : uint8`  
_L22-29_
- L25 _public enumerator_ `StructBrowsing` — Allows all structs to be browsed and selected; syncs selection with the editor; drag and drop attachment, etc.
- L28 _public enumerator_ `StructPicker` — Sets the struct viewer to operate as a struct 'picker'.

#### enum `EStructViewerDisplayMode`  
`enum class EStructViewerDisplayMode : uint8`  
_L31-41_
- L34 _public enumerator_ `DefaultView` — Default will choose what view mode based on if in Viewer or Picker mode.
- L37 _public enumerator_ `TreeView` — Displays all classes as a tree.
- L40 _public enumerator_ `ListView` — Displays all classes as a list.

#### enum `EStructViewerNameTypeToDisplay`  
`enum class EStructViewerNameTypeToDisplay : uint8`  
_L43-53_
- L46 _public enumerator_ `Dynamic` — Display both the display name and struct name if they're available and different.
- L49 _public enumerator_ `DisplayName` — Always use the display name
- L52 _public enumerator_ `StructName` — Always use the struct name

#### class `FStructViewerInitializationOptions`  
`class FStructViewerInitializationOptions`  
_L59-119_
- desc: Settings for the Struct Viewer set by the programmer before spawning an instance of the widget.  This is used to modify the struct viewer's behavior in various ways, such as filtering in or out specific structs.
- L63 _public member_ `TSharedPtr<class IStructViewerFilter> StructFilter;` — The filter to use on structs in this instance.
- L66 _public member_ `EStructViewerMode Mode;` — Mode to operate in
- L69 _public member_ `EStructViewerDisplayMode DisplayMode;` — Mode to display the structs using.
- L72 _public member_ `bool bShowUnloadedStructs;` — Shows unloaded structs. Will not be filtered out based on non-bool filter options.
- L75 _public member_ `bool bShowNoneOption;` — Shows a "None" option, only available in Picker mode.
- L78 _public member_ `bool bExpandRootNodes;` — If true, root nodes will be expanded by default.
- L81 _public member_ `bool bEnableStructDynamicLoading;` — true allows struct dynamic loading on selection
- L84 _public member_ `EStructViewerNameTypeToDisplay NameTypeToDisplay;` — Controls what name is shown for structs
- L87 _public member_ `FText ViewerTitleString;` — the title string of the struct viewer if required.
- L90 _public member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — The property this struct viewer be working on.
- L93 _public member_ `bool bAllowViewOptions;` — true (the default) shows the view options at the bottom of the struct picker.
- L96 _public member_ `bool bShowBackgroundBorder;` — true (the default) shows a background border behind the struct viewer widget.
- L99 _public member_ `const UScriptStruct* SelectedStruct;` — Defined currently selected struct to scroll to to when struct picker is opened.
- L102 _public member_ `TArray<const UScriptStruct*> ExtraPickerCommonStructs;` — Defines additional structs you want listed in the "Common Structs" section for the picker.
- L106 _public function_ `FStructViewerInitializationOptions() : Mode(EStructViewerMode::StructPicker) , DisplayMode(EStructViewerDisplayMode::DefaultView) , bShowUnloadedStructs(true) , bShowNoneOption(false) , bExpandRootNodes(true) , bEnableStructDynamicLoading(true) , NameTypeToDisplay(EStructViewerNameTypeToDisplay::StructName) , bAllowViewOptions(true) , bShowBackgroundBorder(true) , SelectedStruct(nullptr)` — Constructor

#### class `FStructViewerModule`  
`class FStructViewerModule : public IModuleInterface`  
_L124-146_
- inherits: `IModuleInterface`
- desc: Struct Viewer module
- L130 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L135 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L145 _public prototype_ `virtual TSharedRef<class SWidget> CreateStructViewer(const FStructViewerInitializationOptions& InitOptions, const FOnStructPicked& OnStructPickedDelegate);` — Creates a struct viewer widget @param	InitOptions						Programmer-driven configuration for this widget instance @param	OnStructPickedDelegate			Optional callback when a struct is selected in 'struct picking' mode @return	New struct viewer widget

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStructPicked, const UScriptStruct*);` — Delegate used with the Struct Viewer in 'struct picking' mode.  You'll bind a delegate when the struct viewer widget is created, which will be fired off when a struct is selected in the list
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStructPicked, const UScriptStruct*);` — Delegate used with the Struct Viewer in 'struct picking' mode.  You'll bind a delegate when the struct viewer widget is created, which will be fired off when a struct is selected in the list
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStructPickerOpened, const UScriptStruct*);` — Delegate used with the Struct Viewer in 'struct picking' mode.  You'll bind a delegate when the struct viewer widget is created, which will be fired off when a list of structs is opened for selection
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnStructPickerOpened, const UScriptStruct*);` — Delegate used with the Struct Viewer in 'struct picking' mode.  You'll bind a delegate when the struct viewer widget is created, which will be fired off when a list of structs is opened for selection

### `Source/Editor/StructViewer/Public/StructViewerProjectSettings.h` (Public)


#### class `UStructViewerProjectSettings`  
`class UStructViewerProjectSettings : public UObject`  
_L23-36_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements the settings for the Struct Viewer Project Settings
- L30 _private member_ `TArray<FDirectoryPath> InternalOnlyPaths;` — `UPROPERTY(EditAnywhere, config, Category = StructVisibilityManagement, meta = (DisplayName = "List of directories to consider Internal Only.", ContentDir, LongPackageName))` — The base directories to be considered Internal Only for the struct picker.
- L34 _private member_ `TArray<TSoftObjectPtr<const UScriptStruct>> InternalOnlyStructs;` — `UPROPERTY(EditAnywhere, config, Category = StructVisibilityManagement, meta = (DisplayName = "List of base structs to consider Internal Only.", ShowTreeView, HideViewOptions))` — The base classes to be considered Internal Only for the struct picker.
