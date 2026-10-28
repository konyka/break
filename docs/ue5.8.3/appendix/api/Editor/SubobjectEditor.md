# Editor / SubobjectEditor

- module root: `Source/Editor/SubobjectEditor`
- headers: 7; symbols: 306
- symbol kinds: class=10, delegate=4, enum=1, enumerator=5, function=29, macro=5, member=40, prototype=209, struct=1, typedef=2
- PrivateDependencyModuleNames: BlueprintGraph, EditorFramework, EditorWidgets, Engine, GameProjectGeneration, GraphEditor, InputCore, KismetWidgets, Slate, SlateCore, ToolMenus, ToolWidgets, TypedElementFramework, UnrealEd
- PrivateIncludePathModuleNames: LiveCoding
- PublicDependencyModuleNames: Core, CoreUObject, Kismet, SubobjectDataInterface

### `Source/Editor/SubobjectEditor/Public/Elements/Component/ComponentElementSubobjectEditorCommonActionsCustomization.h` (Public)


#### class `FComponentElementSubobjectEditorCommonActionsCustomization`  
`class FComponentElementSubobjectEditorCommonActionsCustomization : public FTypedElementCommonActionsCustomization, public FTypedElementSubobjectEditorMixin`  
_L10-16_
- inherits: `FTypedElementCommonActionsCustomization,FTypedElementSubobjectEditorMixin`
- L12 _private typedef_ `using Super = FTypedElementCommonActionsCustomization;`
- L15 _public prototype_ `virtual void DuplicateElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, const FVector& InLocationOffset, TArray<FTypedElementHandle>& OutNewElements) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SUBOBJECTEDITOR_API`

### `Source/Editor/SubobjectEditor/Public/Elements/Framework/TypedElementSubobjectEditorMixin.h` (Public)


#### class `FTypedElementSubobjectEditorMixin`  
`class FTypedElementSubobjectEditorMixin`  
_L12-34_
- desc: Mixin for subobject editor customizations that provides access to the subobject editor widget.
- L18 _public function_ `TSharedPtr<SSubobjectEditor> GetSubobjectEditor() const` — Get the subobject editor associated with this customization.
- L26 _public function_ `void SetSubobjectEditor(const TSharedPtr<SSubobjectEditor>& InSubobjectEditor)` — Set the subobject editor associated with this customization.
- L33 _private member_ `TWeakPtr<SSubobjectEditor> SubobjectEditorWeak;` — The subobject editor associated with this customization.

### `Source/Editor/SubobjectEditor/Public/SSubobjectBlueprintEditor.h` (Public)


#### class `SSubobjectBlueprintEditor`  
`class SSubobjectBlueprintEditor final : public SSubobjectEditor`  
_L14-127_
- inherits: `SSubobjectEditor`
- desc: This is the editor for subobjects within the blueprint editor that
- L17 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnHighlightPropertyInDetailsView, const class FPropertyPath&);`
- L20 _private function_ `SLATE_BEGIN_ARGS(SSubobjectBlueprintEditor) : _ObjectContext(nullptr) , _PreviewActor(nullptr) , _AllowEditing(true) , _HideComponentClassCombo(false) , _OnSelectionUpdated() , _OnHighlightPropertyInDetailsView()`
- L29 _private prototype_ `SLATE_ATTRIBUTE(UObject*, ObjectContext) SLATE_ATTRIBUTE(AActor*, PreviewActor) SLATE_ATTRIBUTE(bool, AllowEditing) SLATE_ATTRIBUTE(bool, HideComponentClassCombo) SLATE_EVENT(FOnSelectionUpdated, OnSelectionUpdated) SLATE_EVENT(FOnItemDoubleClicked, OnItemDoubleClicked) SLATE_EVENT(FOnHighlightPropertyInDetailsView, OnHighlightPropertyInDetailsView) SLATE_ARGUMENT(TArray<TSharedRef<IClassViewerFilter>>, SubobjectClassListFilters) SLATE_ARGUMENT(TSharedPtr<ISCSEditorUICustomization>, SCSEditorUICustomization) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _protected member_ `TAttribute<AActor*> PreviewActor;` — Attribute that provides access to a "preview" Actor context (may not be same as the Actor context that's being edited.
- L49 _protected function_ `virtual bool ShouldModifyBPOnAssetDrop() const override` — SSubobjectEditor interface
- L50 _protected prototype_ `virtual void OnDeleteNodes() override;`
- L51 _protected prototype_ `virtual void CopySelectedNodes() override;`
- L52 _protected prototype_ `virtual void OnDuplicateComponent() override;`
- L53 _protected prototype_ `virtual bool CanPasteNodes() const override;`
- L54 _protected prototype_ `virtual void PasteNodes() override;`
- L55 _protected prototype_ `virtual void UpdateTree(bool bRegenerateTreeNodes = true) override;`
- L57 _protected prototype_ `virtual void OnAttachToDropAction(FSubobjectEditorTreeNodePtrType DroppedOn, const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs);`
- L58 _protected prototype_ `virtual void OnDetachFromDropAction(const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs);`
- L59 _protected prototype_ `virtual void OnMakeNewRootDropAction(FSubobjectEditorTreeNodePtrType DroppedNodePtr);`
- L60 _protected prototype_ `virtual void PostDragDropAction(bool bRegenerateTreeNodes);`
- L63 _protected prototype_ `virtual TSharedPtr<SWidget> BuildSceneRootDropActionMenu(FSubobjectEditorTreeNodePtrType DroppedOntoNodePtr, FSubobjectEditorTreeNodePtrType DroppedNodePtr);` — Builds a context menu pop up for dropping a child node onto the scene root node
- L64 _protected function_ `virtual bool ClearSelectionOnClick() const override`
- L65 _protected function_ `virtual bool ShowInlineSearchWithButtons() const override`
- L66 _protected prototype_ `virtual FSubobjectDataHandle AddNewSubobject(const FSubobjectDataHandle& ParentHandle, UClass* NewClass, UObject* AssetOverride, FText& OutFailReason, TUniquePtr<FScopedTransaction> InOngoingTransaction) override;`
- L67 _protected prototype_ `virtual void PopulateContextMenuImpl(UToolMenu* InMenu, TArray<FSubobjectEditorTreeNodePtrType>& InSelectedItems, bool bIsChildActorSubtreeNodeSelected) override;`
- L68 _protected prototype_ `virtual FSubobjectEditorTreeNodePtrType GetSceneRootNode() const override;`
- L70 _public prototype_ `virtual FSubobjectEditorTreeNodePtrType FindSlateNodeForObject(const UObject* InObject, bool bIncludeAttachmentComponents = true) const override;`
- L76 _public member_ `FOnHighlightPropertyInDetailsView OnHighlightPropertyInDetailsView;` — Delegate to invoke when the given property should be highlighted in the details view (e.g. diff).
- L86 _public prototype_ `static void BuildMenuEventsSection(FMenuBuilder& Menu, UBlueprint* Blueprint, UClass* SelectedClass, FCanExecuteAction CanExecuteActionDelegate, FGetSelectedObjectsDelegate GetSelectedObjectsDelegate);` — Fills out an events section in ui. @param Menu								the menu to add the events section into @param Blueprint							the active blueprint context being edited @param SelectedClass						the common component class to build the events list from @param CanExecuteActionDelegate			the delegate to query whether or not to execute the UI action @param GetSelectedObjectsDelegate		the delegate to fill the currently select variables / components
- L94 _public prototype_ `void HighlightTreeNode(FName TreeNodeName, const class FPropertyPath& Property);` — Highlight a tree node and, optionally, a property with in it @param TreeNodeName		Name of the treenode to be highlighted @param Property	The name of the property to be highlighted in the details view
- L105 _protected prototype_ `static void CreateEventsForSelection(UBlueprint* Blueprint, FName EventName, FGetSelectedObjectsDelegate GetSelectedObjectsDelegate);` — Function to create events for the current selection @param Blueprint						the active blueprint context @param EventName						the event to add @param GetSelectedObjectsDelegate	the delegate to gather information about current selection @param NodeIndex						an index to a specified node to add event for or < 0 for all selected nodes.
- L113 _protected prototype_ `static void ConstructEvent(UBlueprint* Blueprint, const FName EventName, const FComponentEventConstructionData EventData);` — Function to construct an event for a node @param Blueprint						the nodes blueprint @param EventName						the event to add @param EventData						the event data structure describing the node
- L121 _protected prototype_ `static void ViewEvent(UBlueprint* Blueprint, const FName EventName, const FComponentEventConstructionData EventData);` — Function to view an event for a node @param Blueprint						the nodes blueprint @param EventName						the event to view @param EventData						the event data structure describing the node
- L124 _protected function_ `AActor* GetActorPreview() const` — Get the current preview actor for this blueprint editor.
- L126 _protected member_ `TSharedPtr<class SBox> TreeViewOverlay;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SUBOBJECTEDITOR_API`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHighlightPropertyInDetailsView, const class FPropertyPath&);`

### `Source/Editor/SubobjectEditor/Public/SSubobjectEditor.h` (Public)


#### class `FSubobjectEditorTreeNode`  
`class FSubobjectEditorTreeNode : public TSharedFromThis<FSubobjectEditorTreeNode>`  
_L44-181_
- inherits: `TSharedFromThis<FSubobjectEditorTreeNode>`
- desc: Wrapper struct that represents access an singe subobject that is used by slate as a layout for columns/rows should look like
- L49 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L51 _public prototype_ `explicit FSubobjectEditorTreeNode(const FSubobjectDataHandle& DataSource, bool InbIsSeperator = false);`
- L53 _public prototype_ `~FSubobjectEditorTreeNode() = default;`
- L55 _public function_ `bool IsSeperator() const`
- L59 _public prototype_ `const UActorComponent* GetComponentTemplate() const;` — If this subobject is an actor component, then return its template. Otherwise it will return null
- L61 _public prototype_ `const UObject* GetObject(bool bEvenIfPendingKill = false) const;`
- L64 _public prototype_ `FSubobjectData* GetDataSource() const;` — Get a pointer to the subobject data that this slate node is representing
- L67 _public function_ `FSubobjectDataHandle GetDataHandle() const` — Get the subobject handle that this slate node is representing
- L70 _public function_ `FSubobjectEditorTreeNodePtrType GetParent() const` — Get the slate parent of this single tree node
- L73 _public prototype_ `FString GetDisplayString() const;` — Get the display name of this single tree node
- L75 _public prototype_ `bool IsComponentNode() const;`
- L78 _public prototype_ `bool IsRootActorNode() const;` — Returns true if this is the root actor node of the tree
- L80 _public prototype_ `bool CanReparent() const;`
- L82 _public prototype_ `FName GetVariableName() const;`
- L85 _public function_ `bool IsValid() const` — Returns true if this subobject data handle is valid
- L87 _public prototype_ `bool IsChildSubtreeNode() const;`
- L89 _public prototype_ `bool IsNativeComponent() const;`
- L92 _public prototype_ `bool IsAttachedTo(FSubobjectEditorTreeNodePtrType InNodePtr) const;` — Returns true if this node is attached to the given slate node
- L97 _public prototype_ `bool IsDirectlyAttachedTo(FSubobjectEditorTreeNodePtrType InNodePtr) const;` — @return Whether or not this node is a direct child of the given node.
- L99 _public prototype_ `bool CanDelete() const;`
- L101 _public prototype_ `bool CanRename() const;`
- L106 _public function_ `const TArray<FSubobjectEditorTreeNodePtrType>& GetChildren() const` — @return The set of nodes which are parented to this node (read-only).
- L111 _public prototype_ `void AddChild(FSubobjectEditorTreeNodePtrType AttachToPtr);` — Add the given slate node to our child array and set it's parent to us This had no effect on the actual structure of the subobjects this node represents it is purely visual
- L114 _public prototype_ `void RemoveChild(FSubobjectEditorTreeNodePtrType InChildNodePtr);` — Remove the given slate node from our children array
- L117 _public prototype_ `FSubobjectEditorTreeNodePtrType FindChild(const FSubobjectDataHandle& InHandle);` — Attempts to find the given subobject handle in the slate children on this node. Nullptr if none are found.
- L120 _public prototype_ `bool IsFlaggedForFiltration() const;` — Query that determines if this item should be filtered out or not
- L123 _public prototype_ `void SetCachedFilterState(bool bMatchesFilter, bool bUpdateParent);` — Sets this item's filtration state. Use bUpdateParent to make sure the parent's EFilteredState::ChildMatches flag is properly updated based off the new state
- L126 _public prototype_ `void ApplyFilteredStateToParent();` — Used to update the EFilteredState::ChildMatches flag for parent nodes, when this item's filtration state has changed
- L129 _public prototype_ `void RefreshCachedChildFilterState(bool bUpdateParent);` — Updates the EFilteredState::ChildMatches flag, based off of children's current state
- L132 _public prototype_ `bool RefreshFilteredState(const UClass* InFilterType, const TArray<FString>& InFilterTerms, bool bRecursive);` — Refreshes this item's filtration state. Set bRecursive to 'true' to refresh any child nodes as well
- L135 _public prototype_ `bool MatchesFilterType(const UClass* InFilterType) const;` — Returns whether the node will match the given type (for filtering)
- L137 _public prototype_ `void SetOngoingCreateTransaction(TUniquePtr<FScopedTransaction> InTransaction);`
- L138 _public prototype_ `void CloseOngoingCreateTransaction();`
- L139 _public function_ `void GetOngoingCreateTransaction(TUniquePtr<FScopedTransaction>& OutPtr)`
- L140 _public function_ `bool HasOngoingTransaction() const`
- L143 _public function_ `void SetRenameRequestedDelegate(FOnRenameRequested InRenameRequested)` — Sets up the delegate for a rename operation
- L144 _public function_ `FOnRenameRequested GetRenameRequestedDelegate()`
- L146 _public prototype_ `void ForEachNodeImpl(TFunctionRef<void(FSubobjectEditorTreeNode& Data)> Ftor);`
- L147 _public prototype_ `void DisposeUnsafe();`
- L151 _protected member_ `FSubobjectEditorTreeNodePtrType ParentNodePtr;` — Pointer to the parent of this subobject
- L154 _protected member_ `TUniquePtr<FScopedTransaction> OngoingCreateTransaction;` — Scope the creation of a node which ends when the initial 'name' is given/accepted by the user, which can be several frames after the node was actually created.
- L157 _protected member_ `FOnRenameRequested RenameRequestedDelegate;` — Handles rename requests
- L163 _protected member_ `TArray<FSubobjectEditorTreeNodePtrType> Children;` — Any children that this subobject has in the hierarchy, used to collapsed things within in the tree
- L166 _protected member_ `FSubobjectDataHandle DataHandle;` — The data source of this subobject
- L177 _protected member_ `uint8 FilterFlags;`
- L180 _protected member_ `uint8 bIsSeperator : 1;` — A flag that indicates that this is a separator slate node and has no valid data

#### enum `FSubobjectEditorTreeNode::EFilteredState`  
`enum EFilteredState`  
_L168-176_
- L170 _public enumerator_ `FilteredOut = 0x00`
- L171 _public enumerator_ `MatchesFilter = (1 << 0)`
- L172 _public enumerator_ `ChildMatches = (1 << 1)`
- L174 _public enumerator_ `FilteredInMask = (MatchesFilter | ChildMatches)`
- L175 _public enumerator_ `Unknown = 0xFC` — ~FilteredInMask

#### class `SSubobjectEditorDragDropTree`  
`class SSubobjectEditorDragDropTree : public STreeView<FSubobjectEditorTreeNodePtrType>`  
_L187-251_
- inherits: `STreeView<FSubobjectEditorTreeNodePtrType>`
- desc: Implements the specific node type and add drag/drop functionality
- L190 _public function_ `SLATE_BEGIN_ARGS(SSubobjectEditorDragDropTree) : _SubobjectEditor(nullptr) , _OnGenerateRow() , _OnGetChildren() , _OnSetExpansionRecursive() , _TreeItemsSource(static_cast<TArray<FSubobjectEditorTreeNodePtrType>*>(nullptr)) , _ItemHeight(16) , _OnContextMenuOpening() , _OnMouseButtonDoubleClick() , _OnSelectionChanged() , _SelectionMode(ESelectionMode::Multi) , _ClearSelectionOnClick(true) , _ExternalScrollbar() , _OnTableViewBadState()`
- L208 _public prototype_ `SLATE_ARGUMENT(SSubobjectEditor*, SubobjectEditor) SLATE_EVENT(FOnGenerateRow, OnGenerateRow) SLATE_EVENT(FOnItemScrolledIntoView, OnItemScrolledIntoView) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FOnSetExpansionRecursive, OnSetExpansionRecursive) SLATE_ARGUMENT(TArray<FSubobjectEditorTreeNodePtrType>*, TreeItemsSource) SLATE_ATTRIBUTE_DEPRECATED(float, ItemHeight, 5.5, "The ItemHeight is only used for Tile. See ShouldArrangeAsTiles") SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FOnMouseButtonDoubleClick, OnMouseButtonDoubleClick) SLATE_EVENT(FOnSelectionChanged, OnSelectionChanged) SLATE_ATTRIBUTE(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(TSharedPtr<SHeaderRow>, HeaderRow) SLATE_ARGUMENT(bool, ClearSelectionOnClick) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_EVENT(FOnTableViewBadState, OnTableViewBadState) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L244 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — SWidget interface
- L245 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L250 _private member_ `SSubobjectEditor* SubobjectEditor;`

#### class `SSubobject_RowWidget`  
`class SSubobject_RowWidget : public SMultiColumnTableRow<FSubobjectEditorTreeNodePtrType>`  
_L259-392_
- inherits: `SMultiColumnTableRow<FSubobjectEditorTreeNodePtrType>`
- desc: A row widget that represents a single subobject within the tree.
- L262 _public function_ `SLATE_BEGIN_ARGS(SSubobject_RowWidget)`
- L263 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<SSubobjectEditor> InEditor, FSubobjectEditorTreeNodePtrType InNodePtr, TSharedPtr<STableViewBase> InOwnerTableView);`
- L268 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow<T> interface
- L271 _protected prototype_ `virtual ESelectionMode::Type GetSelectionMode() const override;`
- L275 _protected prototype_ `void HandleOnDragEnter(const FDragDropEvent& DragDropEvent);` — Drag-drop handlers
- L276 _protected prototype_ `void HandleOnDragLeave(const FDragDropEvent& DragDropEvent);`
- L277 _protected prototype_ `FReply HandleOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L278 _protected prototype_ `TOptional<EItemDropZone> HandleOnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, FSubobjectEditorTreeNodePtrType TargetItem);`
- L279 _protected prototype_ `FReply HandleOnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, FSubobjectEditorTreeNodePtrType TargetItem);`
- L283 _public prototype_ `FText GetAssetName() const;` — Get the asset name of this subobject from the asset brokerage
- L286 _public prototype_ `FText GetAssetPath() const;` — Get the asset path of this subobject from the asset brokerage
- L288 _public prototype_ `FText GetNameLabel() const;`
- L291 _public prototype_ `EVisibility GetAssetVisibility() const;` — Check if this asset is visible from the asset brokerage
- L293 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const;`
- L295 _public prototype_ `FSlateColor GetColorTintForIcon() const;`
- L297 _public function_ `FSubobjectEditorTreeNodePtrType GetSubobjectPtr() const`
- L301 _private prototype_ `static void AddToToolTipInfoBox(const TSharedRef<SVerticalBox>& InfoBox, const FText& Key, TSharedRef<SWidget> ValueIcon, const TAttribute<FText>& Value, bool bImportant);`
- L304 _private prototype_ `TSharedRef<SToolTip> CreateToolTipWidget() const;` — Creates a tooltip for this row
- L307 _private prototype_ `TSharedRef<SToolTip> CreateComponentTooltipWidget(const FSubobjectEditorTreeNodePtrType& InNode) const;` — Create the tooltip for component subobjects
- L310 _private prototype_ `TSharedRef<SToolTip> CreateActorTooltipWidget(const FSubobjectEditorTreeNodePtrType& InNode) const;` — Create the tooltip for actor subobjects
- L312 _private prototype_ `FText GetToolTipText() const;`
- L314 _private prototype_ `FText GetActorClassNameText() const;`
- L315 _private prototype_ `FText GetActorSuperClassNameText() const;`
- L316 _private prototype_ `FText GetActorMobilityText() const;`
- L319 _private prototype_ `TSharedRef<SWidget> GetInheritedLinkWidget();` — Returns a widget that represents the inheritance of this subobject which includes a hyperlink to edit the property
- L322 _private prototype_ `FText GetObjectContextText() const;` — Gets the context of this subobject, such as "(Self)" or "(Instance)" for actors.
- L324 _private prototype_ `FString GetDocumentationLink() const;`
- L325 _private prototype_ `FString GetDocumentationExcerptName() const;`
- L328 _private prototype_ `void OnEditBlueprintClicked();` — Callback used when the user clicks on a blueprint inherited variable
- L330 _private prototype_ `EVisibility GetEditBlueprintVisibility() const;`
- L331 _private prototype_ `EVisibility GetEditNativeCppVisibility() const;`
- L334 _private prototype_ `void OnEditNativeCppClicked();` — Callback used when the user clicks on a native inherited variable
- L341 _private prototype_ `FText GetMobilityToolTipText() const;` — Retrieves tooltip text describing the specified component's mobility. @returns An FText object containing a description of the component's mobility
- L348 _private prototype_ `FSlateBrush const* GetMobilityIconImage() const;` — Retrieves an image brush signifying the specified component's mobility (could sometimes be NULL). @returns A pointer to the FSlateBrush to use (NULL for Static and Non-SceneComponents)
- L355 _private prototype_ `FText GetIntroducedInToolTipText() const;` — Retrieves tooltip text describing where the component was first introduced (for inherited components). @returns An FText object containing a description of when the component was first introduced
- L362 _private prototype_ `FText GetComponentAddSourceToolTipText() const;` — Retrieves tooltip text describing how the component was introduced @returns An FText object containing a description of when the component was first introduced
- L369 _private prototype_ `FText GetComponentEditorOnlyTooltipText() const;` — Retrieves a tooltip text describing if the component is marked Editor only or not @returns An FText object containing a description of if the component is marked Editor only or not
- L376 _private prototype_ `FText GetNativeComponentNameToolTipText() const;` — Retrieves tooltip text for the specified Native Component's underlying Name @returns An FText object containing the Component's Name
- L378 _private prototype_ `FText GetActorDisplayText() const;`
- L381 _private prototype_ `void OnNameTextCommit(const FText& InNewName, ETextCommit::Type InTextCommit);` — Commits the new name of the component
- L384 _private prototype_ `bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage);` — Verifies the name of the component when changing it
- L386 _private prototype_ `bool IsReadOnly() const;`
- L388 _private member_ `TWeakPtr<SSubobjectEditor> SubobjectEditor;`
- L389 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineWidget;`
- L391 _private member_ `FSubobjectEditorTreeNodePtrType SubobjectPtr;`

#### class `SSubobjectEditor`  
`class SSubobjectEditor : public SCompoundWidget`  
_L402-819_
- inherits: `SCompoundWidget`
- desc: The base class viewer for subobject editing in Slate. This displays all subobjects of a given actor or blueprint. A subobject can be a native component on an actor or inherited components from a native or blueprint parent.
- L406 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnSelectionUpdated, const TArray<FSubobjectEditorTreeNodePtrType>&);`
- L407 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnItemDoubleClicked, const FSubobjectEditorTreeNodePtrType);`
- L412 _protected prototype_ `SSubobjectEditor() = default;` — Do not allow public construction of this widget!
- L414 _protected prototype_ `virtual ~SSubobjectEditor();`
- L417 _protected member_ `FOnSelectionUpdated OnSelectionUpdated;` — Delegate to invoke on selection update.
- L420 _protected member_ `FOnItemDoubleClicked OnItemDoubleClicked;` — Delegate to invoke when an item in the tree is double clicked.
- L423 _protected prototype_ `void InitScopeRow(FStringView Label);` — Create and parent the Editor Scope Tree row.  Call once from derived Construct().
- L428 _protected member_ `UE::Editor::DataStorage::RowHandle ScopeRow = UE::Editor::DataStorage::InvalidRowHandle;` — Context row owned by this subobject editor for Editor Scope Tree. Created by InitScopeRow(), parented to the current context at that time. Pushed onto TLS in event handlers so property visibility checks see the correct editing scope.
- L431 _protected member_ `TAttribute<UObject*> ObjectContext;` — Attribute that provides access to the Object context for which we are viewing/editing.
- L434 _protected member_ `TAttribute<bool> AllowEditing;` — Attribute to indicate whether or not editing is allowed.
- L437 _protected member_ `TAttribute<bool> HideComponentClassCombo;` — Attribute to indicate whether or not the "Add Component" button is visible. If true, new components cannot be added to the Blueprint.
- L440 _protected member_ `TAttribute<TSubclassOf<UActorComponent>> ComponentTypeFilter;` — Attribute to limit visible nodes to a particular component type when filtering the tree view.
- L446 _protected prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(FSubobjectEditorTreeNodePtrType InNodePtr, const TSharedRef<STableViewBase>& OwnerTable);`
- L449 _protected prototype_ `EVisibility GetComponentsTreeVisibility() const;` — @return The visibility of the components tree
- L452 _protected prototype_ `void OnGetChildrenForTree(FSubobjectEditorTreeNodePtrType InNodePtr, TArray<FSubobjectEditorTreeNodePtrType>& OutChildren);` — Used by tree control - get children for a specified subobject node
- L455 _protected prototype_ `void UpdateSelectionFromNodes(const TArray<FSubobjectEditorTreeNodePtrType>& SelectedNodes);` — Update any associated selection (e.g. details view) from the passed in nodes
- L458 _protected prototype_ `void OnTreeSelectionChanged(FSubobjectEditorTreeNodePtrType InSelectedNodePtr, ESelectInfo::Type SelectInfo);` — Called when selection in the tree changes
- L461 _protected prototype_ `void HandleItemDoubleClicked(FSubobjectEditorTreeNodePtrType InItem);` — Callback when a component item is double clicked.
- L463 _protected prototype_ `void OnFindReferences(bool bSearchAllBlueprints, const EGetFindReferenceSearchStringFlags Flags);`
- L466 _protected prototype_ `EVisibility GetComponentsFilterBoxVisibility() const;` — @return The visibility of the components filter box
- L469 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Recursively updates the filtered state for each component item
- L472 _protected prototype_ `void OnItemScrolledIntoView(FSubobjectEditorTreeNodePtrType InItem, const TSharedPtr<ITableRow>& InWidget);` — Callback when a component item is scrolled into view
- L475 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L478 _public prototype_ `void SetSelectionSet(UTypedElementSelectionSet* InSelectionSet);`
- L480 _public prototype_ `UTypedElementSelectionSet* GetSelectionSet() const;`
- L483 _public prototype_ `void SelectNode(FSubobjectEditorTreeNodePtrType InNodeToSelect, bool bIsCntrlDown);` — Select the given tree node
- L486 _public prototype_ `void SelectNodeFromHandle(const FSubobjectDataHandle& InHandle, bool bIsCntrlDown);` — Select the given tree node if there is on that matches the given handle
- L489 _public prototype_ `virtual void UpdateTree(bool bRegenerateTreeNodes = true);` — Update the contents of the Subobject Tree based on the current context
- L492 _public prototype_ `void DumpTree();` — Dumps out the tree view contents to the log (used to assist with debugging widget hierarchy issues)
- L495 _public prototype_ `void RefreshSelectionDetails();` — Forces the details panel to refresh on the same objects
- L498 _public prototype_ `void ClearSelection();` — Clears the current selection
- L512 _public prototype_ `void SelectRoot();` — Select the root of the tree
- L515 _public prototype_ `virtual FSlateColor GetColorTintForIcon(FSubobjectEditorTreeNodePtrType Node) const;` — Get the tint color that any subobject editor icons should use. The default is the foreground color.
- L518 _public prototype_ `TArray<FSubobjectEditorTreeNodePtrType> GetSelectedNodes() const;` — Get the currently selected nodes from the tree sorted in order from parent to child
- L521 _public function_ `int32 GetNumSelectedNodes() const` — Returns the number of currently selected nodes in the tree
- L524 _public prototype_ `TArray<FSubobjectDataHandle> GetSelectedHandles() const;` — Get the currently selected handles from the tree sorted in order from parent to child
- L526 _public prototype_ `virtual FSubobjectEditorTreeNodePtrType GetSceneRootNode() const;`
- L534 _public prototype_ `EVisibility GetDesiredVisibility() const;` — Returns whether the editor wants to be visible, which can be optionally used by the containing widget. If not overriden by a customization, this will be Collapsed or Visible depending on whether ObjectContext was null or not, respectively, but a customization can drive this by some other state.
- L537 _public prototype_ `FReply TryHandleAssetDragDropOperation(const FDragDropEvent& DragDropEvent);` — Try to handle a drag-drop operation
- L540 _public prototype_ `FReply TryHandleAssetDragDropOperation(const FDragDropEvent& InDragDropEvent, FSubobjectEditorTreeNodePtrType InTargetItem);` — Handle drag-drop operation on a tree item
- L543 _public prototype_ `void SetUICustomization(TSharedPtr<ISCSEditorUICustomization> InUICustomization);` — Sets UI customizations of this SCSEditor.
- L546 _public prototype_ `const ISCSEditorUICustomization* GetUICustomization() const;` — Internally linked function to allow the tree widgets to access customization functions
- L548 _public prototype_ `virtual bool IsEditingAllowed() const;`
- L551 _public prototype_ `TSharedPtr<SWidget> GetToolButtonsBox() const;` — Return the button widgets that can add components or create/edit blueprints
- L553 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L555 _public function_ `TSharedPtr<SSubobjectEditorDragDropTree> GetDragDropTree() const`
- L559 _public function_ `void OnAttachToDropAction(FSubobjectEditorTreeNodePtrType DroppedOn, FSubobjectEditorTreeNodePtrType DroppedNodePtr)` — Handler for attaching a single node to this node
- L566 _public prototype_ `virtual void OnAttachToDropAction(FSubobjectEditorTreeNodePtrType DroppedOn, const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs) = 0;`
- L567 _public prototype_ `virtual void OnDetachFromDropAction(const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs) = 0;`
- L568 _public prototype_ `virtual void OnMakeNewRootDropAction(FSubobjectEditorTreeNodePtrType DroppedNodePtr) = 0;`
- L569 _public prototype_ `virtual void PostDragDropAction(bool bRegenerateTreeNodes) = 0;`
- L572 _public prototype_ `virtual TSharedPtr<SWidget> BuildSceneRootDropActionMenu(FSubobjectEditorTreeNodePtrType DroppedOntoNodePtr, FSubobjectEditorTreeNodePtrType DroppedNodePtr) = 0;` — Builds a context menu popup for dropping a child node onto the scene root node
- L574 _public function_ `virtual bool CanMakeNewRootOnDrag(UBlueprint* DraggedFromBlueprint) const`
- L577 _public prototype_ `UBlueprint* GetBlueprint() const;` — Provides access to the Blueprint context that's being edited
- L580 _public prototype_ `virtual FSubobjectEditorTreeNodePtrType FindSlateNodeForObject(const UObject* InObject, bool bIncludeAttachmentComponents = true) const;` — Attempt to find an existing slate node that matches the given handle
- L583 _public prototype_ `bool IsComponentSelected(const UPrimitiveComponent* PrimComponent) const;` — Returns true if the specified component is currently selected
- L586 _public prototype_ `void SetSelectionOverride(UPrimitiveComponent* PrimComponent) const;` — Assigns a selection override delegate to the specified component
- L592 _public prototype_ `void GetSelectedItemsForContextMenu(TArray<FComponentEventConstructionData>& OutSelectedItems) const;` — Fills the supplied array with the currently selected objects @param OutSelectedItems The array to fill.
- L595 _public function_ `const TArray<FSubobjectEditorTreeNodePtrType>& GetRootNodes() const` — Return an array of the current slate node hierarchy in the tree
- L598 _public prototype_ `FSubobjectEditorTreeNodePtrType FindSlateNodeForHandle(const FSubobjectDataHandle& Handle, FSubobjectEditorTreeNodePtrType InStartNodePtr = FSubobjectEditorTreeNodePtrType()) const;` — Attempt to find an existing slate node that matches the given handle
- L601 _public prototype_ `FSubobjectEditorTreeNodePtrType FindSlateNodeForVariableName(FName InVariableName) const;` — Attempt to find an existing slate node that has a given variable name
- L604 _public prototype_ `UObject* GetObjectContext() const;` — Pointer to the current object that is represented by the subobject editor
- L607 _public prototype_ `FSubobjectDataHandle GetObjectContextHandle() const;` — SubobjectHandle of the current object that is represented by the subobject editor
- L618 _public prototype_ `void RefreshComponentTypesList();` — Refresh the type list presented by the add component button when clicked
- L623 _protected prototype_ `virtual void RestoreSelectionState(TArray<FSubobjectEditorTreeNodePtrType>& SelectedTreeNodes, bool bFallBackToVariableName = true);` — Restore the previous selection state when updating the tree
- L626 _protected function_ `virtual bool ShouldModifyBPOnAssetDrop() const` — If true, then the blueprint should be modified on TryHandleAssetDragDropOperation
- L628 _protected prototype_ `bool CanCutNodes() const;`
- L629 _protected prototype_ `void CutSelectedNodes();`
- L631 _protected prototype_ `bool CanCopyNodes() const;`
- L632 _protected prototype_ `virtual void CopySelectedNodes() = 0;`
- L635 _protected prototype_ `virtual bool CanPasteNodes() const;` — Pastes previously copied node(s)
- L636 _protected prototype_ `virtual void PasteNodes() = 0;`
- L639 _protected prototype_ `static bool ShouldClearFocusOnDuplicate(TSharedPtr<SWidget> InCurrentlyFocusedWidget);` — Returns true if keyboard focus should be cleared in OnDuplicateComponent if the widget is currently focused
- L643 _public prototype_ `virtual bool CanDeleteNodes() const;` — Removes existing selected component nodes from the SCS
- L644 _public prototype_ `virtual void OnDeleteNodes() = 0;`
- L649 _protected prototype_ `bool CanDuplicateComponent() const;`
- L650 _protected prototype_ `virtual void OnDuplicateComponent() = 0;`
- L653 _protected prototype_ `bool CanRenameComponent() const;` — Checks to see if renaming is allowed on the selected component
- L654 _protected prototype_ `void OnRenameComponent();`
- L655 _protected prototype_ `void OnRenameComponent(TUniquePtr<FScopedTransaction> InComponentCreateTransaction);`
- L658 _protected prototype_ `void OnPostTick(float);` — Called at the end of each frame.
- L664 _protected member_ `TArray<FSubobjectEditorTreeNodePtrType> RootNodes;` — Root set of tree that represents all subobjects for the current context
- L667 _protected member_ `TSharedPtr<SSubobjectEditorDragDropTree> TreeWidget;` — Tree widget
- L670 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Command list for handling actions in the editor.
- L673 _protected member_ `TSharedPtr<SSearchBox> FilterBox;` — The filter box that handles filtering for the tree.
- L676 _protected member_ `TSharedPtr<SHorizontalBox> ButtonBox;` — The tools buttons box
- L679 _protected member_ `TSharedPtr<SComponentClassCombo> ComponentClassCombo;` — The add component button / type selector
- L682 _protected member_ `bool bUpdatingSelection;` — Gate to prevent changing the selection while selection change is being broadcast.
- L685 _protected member_ `bool bAllowTreeUpdates;` — Controls whether or not to allow calls to UpdateTree()
- L688 _protected member_ `TSharedPtr<ISCSEditorUICustomization> UICustomization;` — SCSEditor UI customizations
- L691 _protected member_ `TSharedPtr<SExtensionPanel> ExtensionPanel;` — SCSEditor UI extension
- L694 _protected member_ `TUniquePtr<FScopedTransaction> DeferredOngoingCreateTransaction;` — Scope the creation of a component which ends when the initial component 'name' is given/accepted by the user, which can be several frames after the component was actually created.
- L697 _protected member_ `FDelegateHandle PostTickHandle;` — Used to unregister from the post tick event.
- L700 _protected member_ `FSubobjectDataHandle DeferredRenameRequest;` — Name of a node that has been requested to be renamed
- L707 _protected member_ `FSubobjectDataHandle CachedRootHandle;` — The handle to the current root context. If this is different in between UpdateTree calls, then we know the context has changed and we should clean up the subobject memory layout.
- L709 _protected prototype_ `virtual FMenuBuilder CreateMenuBuilder();`
- L712 _protected prototype_ `virtual void ConstructTreeWidget();` — Constructs the slate drag/drop tree for this subobject editor
- L715 _protected prototype_ `virtual void CreateCommandList();` — Creates a list of commands
- L718 _protected prototype_ `void DepthFirstTraversal(const FSubobjectEditorTreeNodePtrType& InNodePtr, TSet<FSubobjectEditorTreeNodePtrType>& OutVisitedNodes, const TFunctionRef<void(const FSubobjectEditorTreeNodePtrType&)> InFunction) const;` — Recursively visits the given node + its children and invokes the given function for each.
- L721 _protected prototype_ `void GetCollapsedNodes(const FSubobjectEditorTreeNodePtrType& InNodePtr, TSet<FSubobjectEditorTreeNodePtrType>& OutCollapsedNodes) const;` — Returns the set of expandable nodes that are currently collapsed in the UI
- L724 _protected prototype_ `static FSubobjectEditorTreeNodePtrType FindOrCreateSlateNodeForHandle(const FSubobjectDataHandle& Handle, TMap<FSubobjectDataHandle, FSubobjectEditorTreeNodePtrType>& ExistingNodes);` — Attempt to find an existing slate node that matches the given handle
- L732 _protected prototype_ `void SetNodeExpansionState(FSubobjectEditorTreeNodePtrType InNodeToChange, const bool bIsExpanded);` — Set the expansion state of a node @param InNodeToChange	The node to be expanded/collapsed @param bIsExpanded		True to expand the node, false to collapse it
- L735 _protected prototype_ `void SetItemExpansionRecursive(FSubobjectEditorTreeNodePtrType Model, bool bInExpansionState);` — Handler for recursively expanding/collapsing items
- L738 _protected prototype_ `void RegisterContextMenu();` — Registers context menu by name for later access
- L741 _protected prototype_ `TSharedPtr<SWidget> CreateContextMenu();` — Called to display context menu when right clicking on the widget
- L744 _protected prototype_ `void PopulateContextMenu(UToolMenu* InMenu);` — Populate context menu on the fly
- L747 _protected prototype_ `virtual void PopulateContextMenuImpl(UToolMenu* InMenu, TArray<FSubobjectEditorTreeNodePtrType>& InSelectedItems, bool bIsChildActorSubtreeNodeSelected) = 0;` — Populate the context menu with implementation specific details
- L750 _protected prototype_ `TSubclassOf<UActorComponent> GetComponentTypeFilterToApply() const;` — @return Type of component to filter the tree view with or nullptr if there's no filter.
- L757 _protected prototype_ `bool RefreshFilteredState(FSubobjectEditorTreeNodePtrType TreeNode, bool bRecursive);` — Compares the filter bar's text with the item's component name. Use bRecursive to refresh the state of child nodes as well. Returns true if the node is set to be filtered out
- L760 _protected prototype_ `FText GetFilterText() const;` — Callback for the action trees to get the filter text
- L763 _protected prototype_ `void PromoteToBlueprint() const;` — Converts the current actor instance to a blueprint
- L766 _protected prototype_ `FReply OnPromoteToBlueprintClicked();` — Called when the promote to blueprint button is clicked
- L769 _protected prototype_ `void OnOpenBlueprintEditor(bool bForceCodeEditing) const;` — Opens the blueprint editor for the blueprint being viewed by the scseditor
- L777 _protected prototype_ `UClass* SpawnCreateNewCppComponentWindow(TSubclassOf<UActorComponent> ComponentClass);` — Spawns a new SWindow giving the user options for creating a new C++ component class. The user will be prompted to pick a new subclass name and code will be recompiled @return The new class that was created
- L785 _protected prototype_ `UClass* SpawnCreateNewBPComponentWindow(TSubclassOf<UActorComponent> ComponentClass);` — Spawns a new SWindow giving the user options for creating a new blueprint component class. The user will be prompted to pick a new subclass name and a blueprint asset will be created @return The new class that was created
- L788 _protected prototype_ `FSubobjectDataHandle PerformComboAddClass(TSubclassOf<UActorComponent> ComponentClass, EComponentCreateAction::Type ComponentCreateAction, UObject* AssetOverride);` — Add a component from the selection in the combo box
- L791 _protected prototype_ `virtual EVisibility GetPromoteToBlueprintButtonVisibility() const;` — @return The visibility of the promote to blueprint button (only visible with an actor instance that is not created from a blueprint)
- L794 _protected prototype_ `virtual EVisibility GetEditBlueprintButtonVisibility() const;` — @return The visibility of the Edit Blueprint button (only visible with an actor instance that is created from a blueprint)
- L797 _protected prototype_ `virtual EVisibility GetComponentClassComboButtonVisibility() const;` — @return The visibility of the Add Component combo button
- L800 _protected function_ `virtual bool ClearSelectionOnClick() const` — If true, then the tree widget will clear selection on click.
- L803 _protected function_ `virtual bool ShowInlineSearchWithButtons() const` — Indicates whether or not the search bar and inline buttons are visible.
- L806 _protected prototype_ `virtual FSubobjectDataHandle AddNewSubobject(const FSubobjectDataHandle& ParentHandle, UClass* NewClass, UObject* AssetOverride, FText& OutFailReason, TUniquePtr<FScopedTransaction> InOngoingTransaction) = 0;` — Add a new subobject to the given parent via the subobject data subsystem
- L816 _protected prototype_ `void ForEachNode(TFunctionRef<void(FSubobjectEditorTreeNode& Data)> Ftor);`
- L818 _private member_ `TWeakObjectPtr<UTypedElementSelectionSet> SelectionSet;`

#### struct `SSubobjectEditor::Utils`  
`struct Utils`  
_L810-814_
- desc: Utils
- L813 _public prototype_ `static void PopulateHandlesArray(const TArray<FSubobjectEditorTreeNodePtrType>& SlateNodePtrs, TArray<FSubobjectDataHandle>& OutHandles);` — Populate an array of subobject handles based on an array of the slate node ptr

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API SUBOBJECTEDITOR_API`
- L35 _typedef_ `using FSubobjectEditorTreeNodePtrType = TSharedPtr<class FSubobjectEditorTreeNode>;` — Tree node pointer types
- L49 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L406 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionUpdated, const TArray<FSubobjectEditorTreeNodePtrType>&);`
- L407 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemDoubleClicked, const FSubobjectEditorTreeNodePtrType);`

### `Source/Editor/SubobjectEditor/Public/SSubobjectEditorModule.h` (Public)


#### class `FSubobjectEditorModule`  
`class FSubobjectEditorModule : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`

### `Source/Editor/SubobjectEditor/Public/SSubobjectInstanceEditor.h` (Public)


#### class `SSubobjectInstanceEditor`  
`class SSubobjectInstanceEditor final : public SSubobjectEditor`  
_L13-71_
- inherits: `SSubobjectEditor`
- desc: This is the editor for subobjects within the level editor that works mainly with component and actor instances.
- L16 _private function_ `SLATE_BEGIN_ARGS(SSubobjectInstanceEditor) : _ObjectContext(nullptr) , _AllowEditing(true) , _OnSelectionUpdated()`
- L22 _private prototype_ `SLATE_ATTRIBUTE(UObject*, ObjectContext) SLATE_ATTRIBUTE(bool, AllowEditing) SLATE_EVENT(FOnSelectionUpdated, OnSelectionUpdated) SLATE_EVENT(FOnItemDoubleClicked, OnItemDoubleClicked) SLATE_ARGUMENT(TSharedPtr<ISCSEditorUICustomization>, SCSEditorUICustomization) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L35 _protected prototype_ `virtual void OnDeleteNodes() override;` — SSubobjectEditor interface
- L36 _protected prototype_ `virtual void CopySelectedNodes() override;`
- L37 _protected prototype_ `virtual void OnDuplicateComponent() override;`
- L38 _protected prototype_ `virtual void PasteNodes() override;`
- L40 _protected prototype_ `virtual void OnAttachToDropAction(FSubobjectEditorTreeNodePtrType DroppedOn, const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs) override;`
- L41 _protected prototype_ `virtual void OnDetachFromDropAction(const TArray<FSubobjectEditorTreeNodePtrType>& DroppedNodePtrs) override;`
- L42 _protected prototype_ `virtual void OnMakeNewRootDropAction(FSubobjectEditorTreeNodePtrType DroppedNodePtr) override;`
- L43 _protected prototype_ `virtual void PostDragDropAction(bool bRegenerateTreeNodes) override;`
- L45 _protected prototype_ `virtual void UpdateTree(bool bRegenerateTreeNodes = true) override;`
- L48 _protected prototype_ `virtual TSharedPtr<SWidget> BuildSceneRootDropActionMenu(FSubobjectEditorTreeNodePtrType DroppedOntoNodePtr, FSubobjectEditorTreeNodePtrType DroppedNodePtr) override;` — Builds a context menu popup for dropping a child node onto the scene root node
- L49 _protected prototype_ `virtual FSubobjectDataHandle AddNewSubobject(const FSubobjectDataHandle& ParentHandle, UClass* NewClass, UObject* AssetOverride, FText& OutFailReason, TUniquePtr<FScopedTransaction> InOngoingTransaction) override;`
- L50 _protected prototype_ `virtual void PopulateContextMenuImpl(UToolMenu* InMenu, TArray<FSubobjectEditorTreeNodePtrType>& InSelectedItems, bool bIsChildActorSubtreeNodeSelected) override;`
- L51 _protected prototype_ `virtual FMenuBuilder CreateMenuBuilder();`
- L58 _private prototype_ `FText OnGetApplyChangesToBlueprintTooltip() const;` — @return the tooltip describing how many properties will be applied to the blueprint
- L61 _private prototype_ `void OnApplyChangesToBlueprint() const;` — Propagates instance changes to the blueprint
- L64 _private prototype_ `void OnResetToBlueprintDefaults();` — Resets instance changes to the blueprint default
- L67 _private prototype_ `FText OnGetResetToBlueprintDefaultsTooltip() const;` — @return the tooltip describing how many properties will be reset to the blueprint default
- L69 _private member_ `TSharedPtr<class SBox> TreeViewOverlay;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SUBOBJECTEDITOR_API`

### `Source/Editor/SubobjectEditor/Public/SubobjectEditorMenuContext.h` (Public)


#### class `USubobjectEditorMenuContext`  
`class USubobjectEditorMenuContext : public UObject`  
_L20-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L26 _public prototype_ `TArray<UObject*> GetSelectedObjects() const;` — `UFUNCTION(BlueprintCallable, Category="Tool Menus")`
- L28 _public member_ `TWeakPtr<SSubobjectEditor> SubobjectEditor;`
- L30 _public member_ `bool bOnlyShowPasteOption;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SUBOBJECTEDITOR_API`
