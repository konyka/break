# Editor / HierarchicalLODOutliner

- module root: `Source/Editor/HierarchicalLODOutliner`
- headers: 10; symbols: 316
- symbol kinds: class=3, enum=4, enumerator=21, function=37, member=57, namespace=9, prototype=165, struct=13, typedef=7
- PrivateDependencyModuleNames: EditorFramework, SlateCore, ToolMenus
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, HierarchicalLODUtilities, InputCore, PropertyEditor, RHI, RenderCore, Slate, UnrealEd

### `Source/Editor/HierarchicalLODOutliner/Private/HLODOutliner.h` (Private)


#### struct `HLODOutliner::FOutlinerAction`  
`struct FOutlinerAction`  
_L59-74_
- desc: Outliner action class used for making changing to the Outliner's treeview
- L68 _public function_ `FOutlinerAction(ActionType InType, FTreeItemPtr InItem) : Type(InType), Item(InItem)`
- L69 _public function_ `FOutlinerAction(ActionType InType, FTreeItemPtr InItem, FTreeItemPtr InParentItem) : Type(InType), Item(InItem), ParentItem( InParentItem)`
- L71 _public member_ `ActionType Type;`
- L72 _public member_ `FTreeItemPtr Item;`
- L73 _public member_ `FTreeItemPtr ParentItem;`

#### enum `HLODOutliner::FOutlinerAction::ActionType`  
`enum ActionType`  
_L61-66_
- L63 _public enumerator_ `AddItem`
- L64 _public enumerator_ `RemoveItem`
- L65 _public enumerator_ `MoveItem`

#### class `HLODOutliner::SHLODOutliner`  
`class SHLODOutliner : public SCompoundWidget, public FNotifyHook, public FEditorUndoClient`  
_L79-518_
- inherits: `SCompoundWidget,FNotifyHook,FEditorUndoClient`
- desc: Implements the profiler window.
- L81 _private typedef_ `typedef STreeView<FTreeItemPtr> SHLODTree;`
- L90 _public prototype_ `SHLODOutliner();` — Default constructor.
- L93 _public prototype_ `virtual ~SHLODOutliner();` — Virtual destructor.
- L95 _public function_ `SLATE_BEGIN_ARGS(SHLODOutliner)`
- L96 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L104 _public prototype_ `TSharedRef<SWidget> CreateForcedViewWidget();` — Create the panel's forced HLOD level viewer
- L107 _public prototype_ `TSharedRef<SWidget> CreateMainButtonWidgets();` — Creates the panel's main button widget rows
- L110 _public prototype_ `TSharedRef<SWidget> CreateClusterButtonWidgets();` — Creates the panel's button widgets for cluster operations
- L113 _public prototype_ `TSharedRef<SHLODTree> CreateTreeviewWidget();` — Creates the panel's Tree view widget
- L116 _public prototype_ `void CreateSettingsView();` — Initializes and creates the settings view
- L119 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L120 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L121 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L122 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L123 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L124 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L128 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L129 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L133 _public prototype_ `FText GetForceBuildText() const;` — Button handlers
- L134 _public prototype_ `FText GetForceBuildToolTip() const;`
- L135 _public prototype_ `FText GetBuildText() const;`
- L136 _public prototype_ `FReply HandleDeleteHLODs();`
- L137 _public prototype_ `bool CanDeleteHLODs() const;`
- L138 _public prototype_ `FReply HandlePreviewHLODs();`
- L139 _public prototype_ `FReply RetrieveActors();`
- L140 _public prototype_ `FReply HandleBuildLODActors();`
- L141 _public prototype_ `bool CanBuildLODActors() const;`
- L142 _public prototype_ `FText GetBuildLODActorsTooltipText() const;`
- L143 _public prototype_ `FReply HandleForceBuildLODActors();`
- L144 _public prototype_ `FReply HandleForceRefresh();`
- L145 _public prototype_ `FReply HandleSaveAll();`
- L146 _public prototype_ `FText GetGenerateClustersText() const;`
- L147 _public prototype_ `FText GetGenerateClustersTooltip() const;`
- L148 _public prototype_ `FText GetRegenerateClustersText() const;`
- L149 _public prototype_ `FText GetRegenerateClustersTooltip() const;`
- L154 _private prototype_ `void RegisterDelegates();` — Registers all the callback delegates required for keeping the treeview sync
- L157 _private prototype_ `void DeregisterDelegates();` — De-registers all the callback delegates required for keeping the treeview sync
- L160 _private prototype_ `TSharedRef<SWidget> MakeToolBar();` — Builds the toolbar
- L163 _private prototype_ `FReply GenerateClustersFromUI();` — Callbacks to make interaction from UI uniform vs. UI updates
- L164 _private prototype_ `FReply GenerateProxyMeshesFromUI();`
- L165 _private prototype_ `FReply BuildClustersAndMeshesFromUI();`
- L168 _private prototype_ `bool HasHLODActors() const;` — Helper function used to determine whether there are any LOD actors present
- L172 _protected prototype_ `void ForceViewLODActor();` — Forces viewing the mesh of a Cluster (LODActor)
- L179 _protected prototype_ `bool AreHLODsBuild() const;` — Returns whether or not all HLODs in the level are build @return bool
- L186 _protected prototype_ `FText HandleForceLevelText() const;` — Returns FText with information about current forced HLOD level "None", "1" etc. @return FText
- L189 _protected prototype_ `TSharedRef<SWidget> GetForceLevelMenuContent() const;` — Build the forced level widget
- L196 _protected prototype_ `void RestoreForcedLODLevel(int32 LODLevel);` — Restores the forced viewing state for the given LOD levle @param LODLevel - LOD level to force
- L203 _protected prototype_ `void SetForcedLODLevel(int32 LODLevel);` — Forces LODActors within the given LODLevel to show their meshes (other levels hide theirs) @param LODLevel - LOD level to force
- L206 _protected prototype_ `void ResetLODLevelForcing();` — Resets the forced LOD level
- L209 _protected prototype_ `void CreateHierarchicalVolumeForActor();` — Creates a Hierarchical LOD Volume for the given LODActorItem, volume bounds correspond to those of the LODActor's SubActors
- L212 _protected prototype_ `void BuildLODActor();` — Builds the HLOD mesh for the given ALODActor (cluster)
- L215 _protected prototype_ `void RebuildLODActor();` — Rebuilds the HLOD mesh for the given ALODActor (cluster)
- L218 _protected prototype_ `void SelectLODActor();` — Select the LODActor in the Editor Viewport
- L221 _protected prototype_ `void DeleteCluster();` — Deletes a cluster (LODActor)
- L224 _protected prototype_ `void SelectContainedActors();` — Selects the contained actors (SubActors) for a specific LODActor
- L227 _protected prototype_ `void RemoveStaticMeshActorFromCluster();` — Removes the given StaticMeshActor from its parent's (ALODActor) sub-actors array
- L230 _protected prototype_ `void ExcludeFromClusterGeneration();` — Removes the given StaticMeshActor from its parent's (ALODActor) sub-actors array and excludes it from cluster generation
- L233 _protected prototype_ `void RemoveLODActorFromCluster();` — Removes the given LODActor from its parent's (ALODActor) sub-actors array
- L236 _protected prototype_ `void CreateClusterFromActors(const TArray<AActor*>& Actors, uint32 LODLevelIndex);` — Creates a cluster from a set of actors for the given lod level index
- L243 _protected prototype_ `void UpdateDrawDistancesForLODLevel(const uint32 LODLevelIndex);` — Updates the DrawDistance value for all the LODActors with the given LODLevelIndex @param LODLevelIndex -
- L250 _protected prototype_ `void RemoveLODLevelActors(const int32 HLODLevelIndex);` — Removes LODActors within the given HLODLevel @param LODLevelIndex -
- L253 _protected prototype_ `int32 GetSpitterWidgetIndex() const;` — Handle splitting horizontally or vertically based on dimensions
- L264 _protected prototype_ `TSharedRef<ITableRow> OnOutlinerGenerateRow(FTreeItemPtr InReflectorNode, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a Tree view row for the given Tree view Node @param InReflectorNode - Node to generate a row for @param OwnerTable - Owning table of the InReflectorNode @return TSharedRef<ITableRow>
- L272 _protected prototype_ `void OnOutlinerGetChildren(FTreeItemPtr InParent, TArray<FTreeItemPtr>& OutChildren);` — Treeview callback for retrieving the children of a specific TreeItem @param InParent - Parent item to return the children from @param OutChildren - InOut array for the children
- L280 _protected prototype_ `void OnOutlinerSelectionChanged(FTreeItemPtr TreeItem, ESelectInfo::Type );` — Handles the event fired when selection with the HLOD Tree view changes @param TreeItem - Selected node(s) @param SelectionInfo - Type of selection change
- L287 _protected prototype_ `void OnOutlinerDoubleClick(FTreeItemPtr TreeItem);` — Handles double click events from the HLOD Tree view @param TreeItem - Node which was double-clicked
- L290 _protected prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();` — Open a context menu for this scene outliner
- L298 _protected prototype_ `void OnItemExpansionChanged(FTreeItemPtr TreeItem, bool bIsExpanded);` — Handles item expansion events from the HLOD tree view @param TreeItem - Item which expansion state was changed @param bIsExpanded - New expansion state
- L304 _private prototype_ `void StartSelection();` — Starts the Editor selection batch
- L307 _private prototype_ `void EmptySelection();` — Empties the current Editor selection
- L310 _private prototype_ `void DestroySelectionActors();` — Destroys the created selection actors
- L318 _private prototype_ `void SelectActorInViewport(AActor* Actor, const uint32 SelectionDepth = 0);` — Selects an Actor in the Editor viewport @param Actor - AActor to select inside the viewport @param SelectionDepth - (recursive)
- L326 _private prototype_ `void SelectLODActorAndContainedActorsInViewport(ALODActor* LODActor, const uint32 SelectionDepth = 0);` — Selects actors and sub-actors and the given LODActor @param LODActor - Actor to select + subactors @param SelectionDepth - (recursive)
- L334 _private prototype_ `void SelectContainedActorsInViewport(ALODActor* LODActor, const uint32 SelectionDepth = 0);` — Selects actors and sub-actors for the given LODActor @param LODActor - Actor to select + subactors @param SelectionDepth - (recursive)
- L342 _private prototype_ `void AddLODActorForBoundsDrawing(AActor* Actor);` — Creates a ASelectionActor for the given actor, "procedurally" drawing its bounds @param Actor - Actor to create the SelectionActor for @return UDrawSphereComponent*
- L345 _private prototype_ `void EndSelection(const bool bChange);` — Ends the Editor selection batch, bChange determines whether or not there was an actual change and call NoteSelectionChange
- L351 _protected prototype_ `void OnLevelSelectionChanged(UObject* Obj);` — Called by USelection::SelectionChangedEvent delegate when the level's selection changes
- L354 _protected prototype_ `void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);` — Called by the engine when a level is added to the world.
- L357 _protected prototype_ `void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);` — Called by the engine when a level is removed from the world.
- L360 _protected prototype_ `void OnLevelActorsAdded(AActor* InActor);` — Called by the engine when an actor is added to the world.
- L363 _protected prototype_ `void OnLevelActorsRemoved(AActor* InActor);` — Called by the engine when an actor is remove from the world.
- L366 _protected prototype_ `void OnMapChange(uint32 MapFlags);` — Called when the map has changed
- L369 _protected prototype_ `void OnNewCurrentLevel();` — Called when the current level has changed
- L372 _protected prototype_ `void OnMapLoaded(const FString& Filename, bool bAsTemplate);` — Called when a new map is being loaded
- L375 _protected prototype_ `void OnHLODActorMovedEvent(const AActor* InActor, const AActor* ParentActor);` — Called when a HLODActor is moved between clusters
- L378 _protected prototype_ `void OnActorMovedEvent(AActor* InActor);` — Called when an Actor is moved inside of the level
- L381 _protected prototype_ `void OnHLODActorAddedEvent(const AActor* InActor, const AActor* ParentActor);` — Called when and HLODActor is added to the level
- L384 _protected prototype_ `void OnHLODTransitionScreenSizeChangedEvent();` — Called when a DrawDistance value within WorldSettings changed
- L387 _protected prototype_ `void OnHLODLevelsArrayChangedEvent();` — Called when the HLOD Levels array within WorldSettings changed
- L390 _protected prototype_ `void OnHLODActorRemovedFromClusterEvent(const AActor* InActor, const AActor* ParentActor);` — Called when an Actor is removed from a cluster
- L395 _protected prototype_ `bool OutlinerEnabled() const;` — Callback function used to check if Hierarchical LOD functionality is enabled in the current world settings
- L398 _protected prototype_ `void OnBeginPieEvent(bool bIsSimulating);` — Called when a PIE session is beginning
- L401 _protected prototype_ `void OnEndPieEvent(bool bIsSimulating);` — Called when a PIE session is ending
- L405 _private prototype_ `void FullRefresh();` — Tells the scene outliner that it should do a full refresh, which will clear the entire tree and rebuild it from scratch.
- L408 _private prototype_ `const bool UpdateCurrentWorldAndSettings();` — Retrieves and updates the current world and world settings pointers (returns whether or not a world was found)
- L411 _private prototype_ `void Populate();` — Populates the HLODTreeRoot array and consequently the Treeview
- L414 _private prototype_ `void ResetCachedData();` — Clears and resets all arrays and maps containing cached/temporary data
- L417 _private typedef_ `typedef TMap<FTreeItemID, bool> FParentsExpansionState;` — Structure containing information relating to the expansion state of parent items in the tree
- L420 _private prototype_ `TMap<FTreeItemID, bool> GetParentsExpansionState() const;` — Gets the current expansion state of parent items
- L423 _private prototype_ `void SetParentsExpansionState(const FParentsExpansionState& ExpansionStateInfo) const;` — Updates the expansion state of parent items after a repopulate, according to the previous state
- L432 _private prototype_ `const bool AddItemToTree(FTreeItemPtr InItem, FTreeItemPtr InParentItem);` — Adds a new Treeview item @param InItem - Item to add @param InParentItem - Optional parent item to add it to @return const bool
- L440 _private prototype_ `void MoveItemInTree(FTreeItemPtr InItem, FTreeItemPtr InParentItem);` — Moves a TreeView item around @param InItem - Item to move @param InParentItem - New parent for InItem to move to
- L447 _private prototype_ `void RemoveItemFromTree(FTreeItemPtr InItem);` — Removes a TreeView item @param InItem - Item to remove
- L454 _private prototype_ `void SelectItemInTree(FTreeItemPtr InItem);` — Selects a Treeview item @param InItem - Item to select
- L457 _private prototype_ `EActiveTimerReturnType UpdateNeedsBuildFlagTimer(double InCurrentTime, float InDeltaTime);` — Timer to update cached 'needs build' flag
- L460 _private prototype_ `void CloseOpenAssetEditors();` — Closes asset editors showing HLOD data
- L464 _private member_ `bool bNeedsRefresh;` — Whether or not we need to do a refresh of the Tree view
- L467 _private member_ `TWeakObjectPtr<UWorld> CurrentWorld;` — World instance we are currently representing/mirroring in the panel
- L470 _private member_ `AWorldSettings* CurrentWorldSettings;` — World settings found in CurrentWorld
- L473 _private member_ `TArray<FTreeItemPtr> HLODTreeRoot;` — Tree view nodes
- L475 _private member_ `TArray<FTreeItemPtr> SelectedNodes;` — Currently selected Tree view nodes
- L477 _private member_ `TSharedPtr<SHLODTree> TreeView;` — HLOD Treeview widget
- L479 _private member_ `TSharedPtr<IDetailsView> SettingsView;` — Property viewing widget
- L481 _private member_ `TSharedPtr<SVerticalBox> MainContentPanel;` — Content panel widget
- L483 _private member_ `TAttribute<bool> EnabledAttribute;` — Attribute determining if the outliner UI is enabled
- L486 _private member_ `TMultiMap<FTreeItemID, FTreeItemPtr> TreeItemsMap;` — Map containing all the nodes with their corresponding keys
- L489 _private member_ `TArray<FOutlinerAction> PendingActions;` — Array of pending OutlinerActions
- L492 _private member_ `TArray<FTreeItemPtr> AllNodes;` — Array containing all the nodes
- L495 _private member_ `TArray<AActor*> SelectedLODActors;` — Array of currently selected LODActors
- L498 _private member_ `int32 ForcedLODLevel;` — Currently forced LOD level
- L501 _private member_ `TArray<bool> LODLevelBuildFlags;` — Array with flags for each LOD level (whether or not all their Clusters/LODActors have their meshes built)
- L503 _private member_ `TArray<TArray<TWeakObjectPtr<ALODActor>>> LODLevelActors;` — Array of LODActors/Cluster per LOD level
- L505 _private member_ `TArray<float> LODLevelTransitionScreenSizes;` — Array of TransitionScreenSizes for each LOD Level
- L508 _private member_ `IHierarchicalLODUtilities* HierarchicalLODUtilities;` — Cached pointer to HLOD utilities
- L511 _private member_ `TSharedPtr<FActiveTimerHandle> ActiveTimerHandle;` — Update active timer handle
- L514 _private member_ `bool bCachedNeedsBuild;` — Cached flag to see if we need to generate meshes (any actors are dirty)
- L517 _private member_ `bool bArrangeHorizontally;` — Whether to arrange the main UI horizontally or vertically

#### Free symbols / members of external scopes

- L48 _namespace_ `namespace HLODOutliner`
- L53 _typedef_ `typedef TSharedPtr<ITreeItem> FTreeItemPtr;` (scope `HLODOutliner`)
- L54 _typedef_ `typedef TSharedRef<ITreeItem> FTreeItemRef;` (scope `HLODOutliner`)

### `Source/Editor/HierarchicalLODOutliner/Private/HLODOutlinerDragDrop.h` (Private)


#### struct `HLODOutliner::FDragDropPayload`  
`struct FDragDropPayload`  
_L31-63_
- desc: Consilidated drag/drop information parsed for the HLOD outliner
- L34 _public prototype_ `FDragDropPayload();` — Default constructor, resulting in unset contents
- L38 _public function_ `template<typename TItem> FDragDropPayload(const TArray<TItem>& InDraggedItems)` — Populate this payload from an array of tree items
- L47 _public member_ `TOptional<TArray<TWeakObjectPtr<AActor>>> LODActors;` — Optional array of dragged LOD actors
- L50 _public member_ `TOptional<TArray<TWeakObjectPtr<AActor>>> StaticMeshActors;` — OPtional array of dragged static mesh actors
- L53 _public member_ `bool bSceneOutliner;` — Flag whether or not this is a drop coming from the SceneOutliner or within the HLOD Outliner
- L56 _public member_ `UWorld* OutlinerWorld;` — World instance that is being used for the HLOD Outliner
- L62 _public prototype_ `EClusterGenerationError ParseDrag(const FDragDropOperation& Operation);` — Parse a drag operation into our list of actors and folders @return Error type None if the operation is viable for the HLOD outliner to process, Error type X otherwise

#### struct `HLODOutliner::FHLODOutlinerDragDropOp`  
`struct FHLODOutlinerDragDropOp : public FDragDropOperation`  
_L69-115_
- inherits: `FDragDropOperation`
- desc: A drag/drop operation that was started from the scene outliner
- L81 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FHLODOutlinerDragDropOp, FDragDropOperation);`
- L83 _public prototype_ `FHLODOutlinerDragDropOp(const FDragDropPayload& DraggedObjects);`
- L88 _public member_ `TSharedPtr<FActorDragDropOp> StaticMeshActorOp;` — Actor drag operation
- L89 _public member_ `TSharedPtr<FActorDragDropOp> LODActorOp;`
- L91 _public function_ `void ResetTooltip()`
- L97 _public function_ `void SetTooltip(FText InOverrideText, const FSlateBrush* InOverrideIcon)`
- L103 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L107 _private prototype_ `EVisibility GetOverrideVisibility() const;`
- L108 _private prototype_ `EVisibility GetDefaultVisibility() const;`
- L110 _private member_ `FText OverrideText;`
- L111 _private function_ `FText GetOverrideText() const`
- L113 _private member_ `const FSlateBrush* OverrideIcon;`
- L114 _private function_ `const FSlateBrush* GetOverrideIcon() const`

#### enum `HLODOutliner::FHLODOutlinerDragDropOp::ToolTipIconType`  
`enum ToolTipIconType`  
_L71-79_
- L73 _public enumerator_ `ToolTip_Compatible`
- L74 _public enumerator_ `ToolTip_Incompatible`
- L75 _public enumerator_ `ToolTip_Warning`
- L76 _public enumerator_ `ToolTip_MultipleSelection_Compatible`
- L77 _public enumerator_ `ToolTip_MultipleSelection_Incompatible`
- L78 _public enumerator_ `ToolTip_MultiSelection_Warning`

#### struct `HLODOutliner::FDragValidationInfo`  
`struct FDragValidationInfo`  
_L118-154_
- desc: Struct used for validation of a drag/drop operation in the scene outliner
- L121 _public member_ `FHLODOutlinerDragDropOp::ToolTipIconType TooltipIconType;` — The tooltip type to display on the operation
- L124 _public member_ `FText ValidationText;` — The tooltip text to display on the operation
- L126 _public member_ `EHierarchicalLODActionType ActionType;`
- L129 _public function_ `FDragValidationInfo(const EHierarchicalLODActionType InActionType, const FHLODOutlinerDragDropOp::ToolTipIconType InTooltipIconType, const FText InValidationText) : TooltipIconType(InTooltipIconType) , ValidationText(InValidationText) , ActionType(InActionType)` — Construct this validation information out of a tooltip type and some text
- L137 _public function_ `static FDragValidationInfo Invalid()` — Return a generic invalid result
- L143 _public function_ `bool IsValid() const` — @return true if this operation is valid, false otherwise

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace HLODOutliner`
- L28 _typedef_ `typedef TSharedPtr<ITreeItem> FTreeItemPtr;` (scope `HLODOutliner`)
- L66 _prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation(const TArray<FTreeItemPtr>& InTreeItems);` (scope `HLODOutliner`) — Construct a new Drag and drop operation for a scene outliner

### `Source/Editor/HierarchicalLODOutliner/Private/HLODTreeWidgetItem.h` (Private)


#### class `HLODOutliner::SHLODWidgetItem`  
`class SHLODWidgetItem : public SMultiColumnTableRow < FTreeItemPtr >`  
_L33-94_
- inherits: `SMultiColumnTableRow<FTreeItemPtr>`
- desc: Widget that visualizes the contents of a FReflectorNode.
- L38 _public function_ `SLATE_BEGIN_ARGS(SHLODWidgetItem) : _TreeItemToVisualize(), _Outliner(), _World()`
- L55 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwner);` — Construct child widgets that comprise this widget. @param InArgs Declaration from which to construct this widget.
- L59 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow overrides
- L62 _public function_ `UWorld* GetWorld() const` — Returns World set through the HLODOutliner parent widget
- L65 _protected prototype_ `FText GetItemDisplayString() const;` — Returns the display string of the node
- L68 _protected prototype_ `FSlateColor GetTint() const;` — Returns the tint of the node
- L71 _protected prototype_ `virtual void OnDragEnter(FGeometry const& MyGeometry, FDragDropEvent const& DragDropEvent) override;`
- L72 _protected prototype_ `virtual void OnDragLeave(FDragDropEvent const& DragDropEvent) override;`
- L73 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L74 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L81 _private member_ `ITreeItem* TreeItem;` — The info about the widget that we are visualizing.
- L84 _private member_ `FText CachedItemName;` — Cached Display String as FText
- L87 _private member_ `TWeakPtr< STableViewBase > WeakTableViewBase;` — WeakPtr to the Treeview widget
- L90 _private member_ `SHLODOutliner* Outliner;` — Pointer to the owning SHLODOutliner
- L93 _private member_ `UWorld* World;` — Pointer to the currently represented world (unused atm)

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace HLODOutliner`
- L27 _typedef_ `typedef TSharedPtr<ITreeItem> FTreeItemPtr;` (scope `HLODOutliner`)

### `Source/Editor/HierarchicalLODOutliner/Private/HierarchicalLODType.h` (Private)


#### enum `EHierarchicalLODActionType`  
`enum class EHierarchicalLODActionType : uint8`  
_L11-22_
- reflection: `UENUM()`
- L13 _public enumerator_ `InvalidAction`
- L14 _public enumerator_ `CreateCluster`
- L15 _public enumerator_ `AddActorToCluster`
- L16 _public enumerator_ `MoveActorToCluster`
- L17 _public enumerator_ `RemoveActorFromCluster`
- L18 _public enumerator_ `MergeClusters`
- L19 _public enumerator_ `ChildCluster`
- L21 _public enumerator_ `MAX`

### `Source/Editor/HierarchicalLODOutliner/Private/ITreeItem.h` (Private)


#### struct `HLODOutliner::IDropTarget`  
`struct IDropTarget`  
_L17-24_
- desc: Interface used for validating movement (ie, drag/dropping) operations
- L20 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const = 0;` — Called to test whether the specified payload can be dropped onto this tree item
- L23 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) = 0;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### struct `HLODOutliner::ITreeItem`  
`struct ITreeItem : IDropTarget, TSharedFromThis < ITreeItem >`  
_L28-116_
- inherits: `IDropTarget,TSharedFromThis<ITreeItem>`
- L42 _protected function_ `ITreeItem() : Parent(nullptr), Type(Invalid), bIsExpanded(false)` — Default constructor
- L43 _protected prototype_ `virtual ~ITreeItem() = default;`
- L46 _protected member_ `mutable TWeakPtr<ITreeItem> Parent;` — This item's parent, if any.
- L49 _protected member_ `mutable TArray<TWeakPtr<ITreeItem>> Children;` — Array of children contained underneath this item
- L52 _protected member_ `mutable TreeItemType Type;` — Item type enum
- L56 _public function_ `FTreeItemPtr GetParent() const` — Get this item's parent. Can be nullptr.
- L62 _public function_ `void AddChild(FTreeItemRef Child)` — Add a child to this item
- L69 _public function_ `void RemoveChild(const FTreeItemRef& Child)` — Remove a child from this item
- L78 _public function_ `const TreeItemType GetTreeItemType()` — Returns the TreeItem's type
- L84 _public function_ `FORCEINLINE const TArray<TWeakPtr<ITreeItem>>& GetChildren() const` — Get this item's children, if any. Although we store as weak pointers, they are guaranteed to be valid.
- L90 _public member_ `bool bIsExpanded;` — Flag whether or not this item is expanded in the treeview
- L94 _public prototype_ `virtual FString GetDisplayString() const = 0;` — Get the raw string to display for this tree item - used for sorting
- L97 _public prototype_ `virtual bool CanInteract() const = 0;` — Check whether it should be possible to interact with this tree item
- L100 _public function_ `virtual void OnExpansionChanged()` — Called when this item is expanded or collapsed
- L103 _public function_ `virtual void GenerateContextMenu(UToolMenu* Menu, SHLODOutliner& Outliner)` — Generate a context menu for this item. Only called if *only* this item is selected.
- L106 _public prototype_ `virtual void PopulateDragDropPayload(FDragDropPayload& Payload) const = 0;` — Populate the specified drag/drop payload with any relevant information for this type
- L109 _public prototype_ `virtual FTreeItemID GetID() = 0;` — Returns this TreeItem's ID
- L112 _public function_ `virtual FSlateColor GetTint() const` — Returns the Tint used for displaying this item in the Treeview

#### enum `HLODOutliner::ITreeItem::TreeItemType`  
`enum TreeItemType`  
_L30-36_
- L32 _public enumerator_ `Invalid`
- L33 _public enumerator_ `HierarchicalLODLevel`
- L34 _public enumerator_ `HierarchicalLODActor`
- L35 _public enumerator_ `StaticMeshActor`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HLODOutliner`
- L26 _typedef_ `typedef TSharedRef<ITreeItem> FTreeItemRef;` (scope `HLODOutliner`)

### `Source/Editor/HierarchicalLODOutliner/Private/LODActorItem.h` (Private)


#### struct `HLODOutliner::FLODActorDropTarget`  
`struct FLODActorDropTarget : IDropTarget`  
_L23-37_
- inherits: `IDropTarget`
- desc: Helper class to manage moving arbitrary data onto an actor
- L26 _public member_ `TWeakObjectPtr<ALODActor> LODActor;` — The actor this tree item is associated with.
- L29 _public function_ `FLODActorDropTarget(ALODActor* InLODActor) : LODActor(InLODActor)` — Construct this object out of an Actor
- L33 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L36 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### struct `HLODOutliner::FLODActorItem`  
`struct FLODActorItem : ITreeItem`  
_L39-76_
- inherits: `ITreeItem`
- L41 _public member_ `mutable TWeakObjectPtr<ALODActor> LODActor;`
- L42 _public member_ `mutable FTreeItemID ID;`
- L44 _public prototype_ `explicit FLODActorItem(ALODActor* InLODActor);`
- L47 _public prototype_ `virtual bool CanInteract() const override;`
- L48 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SHLODOutliner& Outliner) override;`
- L49 _public prototype_ `virtual FString GetDisplayString() const override;`
- L50 _public prototype_ `virtual FSlateColor GetTint() const override;`
- L51 _public prototype_ `virtual FTreeItemID GetID() override;`
- L55 _public prototype_ `FText GetRawNumTrianglesAsText() const;` — Returns the number of triangles for the represented LODActor in FText form
- L58 _public prototype_ `FText GetReducedNumTrianglesAsText() const;` — Returns the reduced number of triangles for the represented LODActor in FText form
- L61 _public prototype_ `FText GetReductionPercentageAsText() const;` — Returns the reduction percentage for the represented LODActor in FText form
- L64 _public prototype_ `FText GetLevelAsText() const;` — Returns the level the meshes are in Ftext form
- L69 _public prototype_ `virtual void PopulateDragDropPayload(FDragDropPayload& Payload) const override;` — Populate the specified drag/drop payload with any relevant information for this type
- L72 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L75 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace HLODOutliner`

### `Source/Editor/HierarchicalLODOutliner/Private/LODLevelItem.h` (Private)


#### struct `HLODOutliner::FLODLevelDropTarget`  
`struct FLODLevelDropTarget : IDropTarget`  
_L19-37_
- inherits: `IDropTarget`
- desc: Helper class to manage moving abritrary data onto an actor
- L22 _public member_ `uint32 LODLevelIndex;` — The actor this tree item is associated with.
- L25 _public function_ `FLODLevelDropTarget(uint32 InLODIndex) : LODLevelIndex(InLODIndex)` — Construct this object out of an Actor
- L30 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L33 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.
- L36 _public prototype_ `void CreateNewCluster(FDragDropPayload &DraggedObjects);` — Creating a new cluster (LODActor) with given objects/actors

#### struct `HLODOutliner::FLODLevelItem`  
`struct FLODLevelItem : ITreeItem`  
_L39-64_
- inherits: `ITreeItem`
- L41 _public prototype_ `FLODLevelItem(const uint32 InLODIndex);`
- L44 _public prototype_ `virtual bool CanInteract() const override;`
- L45 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SHLODOutliner& Outliner) override;`
- L46 _public prototype_ `virtual FString GetDisplayString() const override;`
- L47 _public prototype_ `virtual FTreeItemID GetID() override;`
- L51 _public prototype_ `virtual void PopulateDragDropPayload(FDragDropPayload& Payload) const override;` — Populate the specified drag/drop payload with any relevant information for this type
- L54 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L57 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.
- L60 _public member_ `uint32 LODLevelIndex;` — LOD index of this level
- L63 _public member_ `FTreeItemID ID;` — TreeItem ID

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace HLODOutliner`

### `Source/Editor/HierarchicalLODOutliner/Private/StaticMeshActorItem.h` (Private)


#### struct `HLODOutliner::FStaticMeshActorDropTarget`  
`struct FStaticMeshActorDropTarget : IDropTarget`  
_L21-34_
- inherits: `IDropTarget`
- desc: Helper class to manage moving abritrary data onto an actor
- L24 _public member_ `TWeakObjectPtr<AActor> Actor;` — The actor this tree item is associated with.
- L27 _public function_ `FStaticMeshActorDropTarget(AActor* InActor) : Actor(InActor)` — Construct this object out of an Actor
- L30 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L33 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### struct `HLODOutliner::FStaticMeshActorItem`  
`struct FStaticMeshActorItem : ITreeItem`  
_L36-60_
- inherits: `ITreeItem`
- L39 _public member_ `mutable TWeakObjectPtr<AActor> StaticMeshActor;` — Represented StaticMeshActor
- L41 _public member_ `mutable FTreeItemID ID;` — TreeItem's ID
- L43 _public prototype_ `explicit FStaticMeshActorItem(AActor* InStaticMeshActor);`
- L46 _public prototype_ `virtual bool CanInteract() const override;`
- L47 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SHLODOutliner& Outliner) override;`
- L48 _public prototype_ `virtual FString GetDisplayString() const override;`
- L49 _public prototype_ `virtual FTreeItemID GetID() override;`
- L53 _public prototype_ `virtual void PopulateDragDropPayload(FDragDropPayload& Payload) const override;` — Populate the specified drag/drop payload with any relevant information for this type
- L56 _public prototype_ `virtual FDragValidationInfo ValidateDrop(FDragDropPayload& DraggedObjects) const override;` — Called to test whether the specified payload can be dropped onto this tree item
- L59 _public prototype_ `virtual void OnDrop(FDragDropPayload& DraggedObjects, const FDragValidationInfo& ValidationInfo, TSharedRef<SWidget> DroppedOnWidget) override;` — Called to drop the specified objects on this item. Only called if ValidateDrop() allows.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace HLODOutliner`

### `Source/Editor/HierarchicalLODOutliner/Private/TreeItemID.h` (Private)


#### struct `HLODOutliner::FTreeItemID`  
`struct FTreeItemID`  
_L9-71_
- L12 _public function_ `FTreeItemID() : CachedHash(0)`
- L14 _public function_ `FTreeItemID(const UObject* InObject)`
- L21 _public function_ `FTreeItemID(const FTreeItemID& Other)` — Copy construction / assignment
- L26 _public function_ `FTreeItemID& operator=(const FTreeItemID& Other)`
- L34 _public function_ `FTreeItemID(FTreeItemID&& Other)` — Move construction / assignment
- L39 _public function_ `FTreeItemID& operator=(FTreeItemID&& Other)`
- L45 _public function_ `~FTreeItemID()`
- L64 _public function_ `void SetCachedHash(const uint32 InHash)`
- L69 _private member_ `FObjectKey ObjectKey;`
- L70 _private member_ `uint32 CachedHash;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace HLODOutliner`
- L50 _function_ `friend bool operator==(const FTreeItemID& One, const FTreeItemID& Other)` (scope `HLODOutliner`)
- L54 _function_ `friend bool operator!=(const FTreeItemID& One, const FTreeItemID& Other)` (scope `HLODOutliner`)
- L59 _function_ `friend uint32 GetTypeHash(const FTreeItemID& ItemID)` (scope `HLODOutliner`)

### `Source/Editor/HierarchicalLODOutliner/Public/HierarchicalLODOutlinerModule.h` (Public)


#### class `FHierarchicalLODOutlinerModule`  
`class FHierarchicalLODOutlinerModule : public IModuleInterface`  
_L16-37_
- inherits: `IModuleInterface`
- desc: The module holding all of the UI related pieces for HLOD Outliner
- L22 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L27 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L29 _public prototype_ `void OnHLODLevelsArrayChangedEvent();`
- L32 _public prototype_ `virtual TSharedRef<SWidget> CreateHLODOutlinerWidget();` — Creates the HLOD Outliner widget
- L35 _private member_ `FDelegateHandle ArrayChangedDelegate;`
- L36 _private member_ `TSharedPtr<HLODOutliner::SHLODOutliner> HLODWindow;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace HLODOutliner`
