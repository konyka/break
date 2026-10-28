# Plugins / SequenceNavigator

- module root: `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator`
- headers: 128; symbols: 2630
- symbol kinds: class=121, delegate=18, enum=18, enumerator=55, function=271, macro=54, member=361, namespace=249, prototype=1464, struct=12, typedef=7
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AppFramework, BlueprintGraph, CoreUObject, DeveloperSettings, Engine, InputCore, LevelSequence, MovieScene, MovieSceneTools, MovieSceneTracks, Projects, Sequencer, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, SequencerCore

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/DragDropOps/Handlers/NavigationToolSequenceDropHandler.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolSequenceDropHandler`  
`class FNavigationToolSequenceDropHandler : public FNavigationToolItemDropHandler`  
_L13-28_
- inherits: `FNavigationToolItemDropHandler`
- desc: Class that handles Dropping Sequence Items into a Target Item
- L22 _protected prototype_ `virtual bool IsDraggedItemSupported(const FNavigationToolViewModelPtr& InDraggedItem) const override;`
- L23 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) const override;`
- L24 _protected prototype_ `virtual bool Drop(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) override;`
- L27 _protected prototype_ `void MoveItems(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Filters/Filters/NavigationToolBuiltInFilter.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolBuiltInFilter`  
`class FNavigationToolBuiltInFilter : public FFilterBase<FNavigationToolViewModelPtr>`  
_L12-50_
- inherits: `FFilterBase<FNavigationToolViewModelPtr>`
- L15 _public prototype_ `FNavigationToolBuiltInFilter(const FNavigationToolBuiltInFilterParams& InFilterParams);`
- L18 _public prototype_ `virtual FText GetDisplayName() const override;`
- L19 _public prototype_ `virtual FText GetToolTipText() const override;`
- L20 _public prototype_ `virtual FLinearColor GetColor() const override;`
- L21 _public prototype_ `virtual FName GetIconName() const override;`
- L22 _public function_ `virtual bool IsInverseFilter() const override`
- L26 _public prototype_ `virtual FString GetName() const override;`
- L27 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIcon() const;`
- L32 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const;`
- L34 _public prototype_ `virtual bool IsActive() const;`
- L35 _public prototype_ `virtual void SetActive(const bool bInActive);`
- L37 _public prototype_ `const FNavigationToolBuiltInFilterParams& GetFilterParams() const;`
- L40 _protected function_ `virtual void ActiveStateChanged(const bool bInActive) override`
- L41 _protected function_ `virtual void ModifyContextMenu(FMenuBuilder& InMenuBuilder) override`
- L43 _protected function_ `virtual void SaveSettings(const FString& InIniFilename, const FString& InIniSection, const FString& InSettingsString) const override`
- L44 _protected function_ `virtual void LoadSettings(const FString& InIniFilename, const FString& InIniSection, const FString& InSettingsString) override`
- L47 _protected member_ `bool bIsActive = false;` — Active global filters are not checked in the menu and will hide the item if it does not pass the filter
- L49 _protected member_ `FNavigationToolBuiltInFilterParams FilterParams;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Filters/NavigationToolFilterCommands.h` (Private)


#### class `FNavigationToolFilterCommands`  
`class FNavigationToolFilterCommands : public TCommands<FNavigationToolFilterCommands>`  
_L10-50_
- inherits: `TCommands<FNavigationToolFilterCommands>`
- L14 _public function_ `FNavigationToolFilterCommands() : TCommands<FNavigationToolFilterCommands>(TEXT("SequenceNavigationToolFilters") , LOCTEXT("SequenceNavigatorFilters", "Sequence Navigator Filters") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L21 _public prototype_ `virtual void RegisterCommands() override;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilterBarVisibility;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> SetToVerticalLayout;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> SetToHorizontalLayout;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ResetFilters;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ToggleMuteFilters;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> DisableAllFilters;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ToggleActivateEnabledFilters;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ActivateAllFilters;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> DeactivateAllFilters;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Sequence;` — Global Filters
- L41 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Track;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Binding;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Marker;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Unbound;` — Normal Filters
- L47 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Marks;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Playhead;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> ToggleFilter_Dirty;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "NavigationToolFilterCommands"`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Filters/TextExpressions/NavigationToolFilterTextExpression_Name.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolFilterTextExpression_Name`  
`class FNavigationToolFilterTextExpression_Name : public FNavigationToolFilterTextExpressionContext`  
_L13-30_
- inherits: `FNavigationToolFilterTextExpressionContext`
- L16 _public prototype_ `FNavigationToolFilterTextExpression_Name(INavigationToolFilterBar& InFilterInterface);`
- L19 _public prototype_ `virtual TSet<FName> GetKeys() const override;`
- L20 _public prototype_ `virtual ESequencerTextFilterValueType GetValueType() const override;`
- L21 _public prototype_ `virtual FText GetDescription() const override;`
- L25 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey , const FTextFilterString& InValue , const ETextFilterComparisonOperation InComparisonOperation , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Filters/TextExpressions/NavigationToolFilterTextExpression_Unbound.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolFilterTextExpression_Unbound`  
`class FNavigationToolFilterTextExpression_Unbound : public FNavigationToolFilterTextExpressionContext`  
_L12-29_
- inherits: `FNavigationToolFilterTextExpressionContext`
- L15 _public prototype_ `FNavigationToolFilterTextExpression_Unbound(INavigationToolFilterBar& InFilterInterface);`
- L18 _public prototype_ `virtual TSet<FName> GetKeys() const override;`
- L19 _public prototype_ `virtual ESequencerTextFilterValueType GetValueType() const override;`
- L20 _public prototype_ `virtual FText GetDescription() const override;`
- L24 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey , const FTextFilterString& InValue , const ETextFilterComparisonOperation InComparisonOperation , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Items/NavigationToolTreeRoot.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolTreeRoot`  
`class FNavigationToolTreeRoot final : public FNavigationToolItem`  
_L19-45_
- inherits: `FNavigationToolItem`
- desc: The Item that ensures that every item (except self) has a parent in the hierarchy to make it easier to handle. This is not really a visual item, so it can't appear in the Navigation Tool view.
- L29 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L30 _public prototype_ `virtual bool CanAddChild(const FNavigationToolViewModelPtr& InChild) const override;`
- L31 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public prototype_ `virtual FText GetClassName() const override;`
- L34 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L35 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SNavigationToolTreeRow>& InRow) override;`
- L37 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) override;`
- L38 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) override;`
- L43 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Menus/NavigationToolFilterBarContextMenu.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolFilterBarContextMenu`  
`class FNavigationToolFilterBarContextMenu : public TSharedFromThis<FNavigationToolFilterBarContextMenu>`  
_L15-30_
- inherits: `TSharedFromThis<FNavigationToolFilterBarContextMenu>`
- L18 _public prototype_ `TSharedRef<SWidget> CreateMenu(const TSharedRef<INavigationToolFilterBar>& InFilterBar);`
- L21 _protected prototype_ `void PopulateMenu(UToolMenu* const InMenu);`
- L23 _protected prototype_ `void PopulateOptionsSection(UToolMenu& InMenu);`
- L24 _protected prototype_ `void PopulateFilterBulkOptionsSection(UToolMenu& InMenu);`
- L26 _protected prototype_ `void OnActivateAllFilters(const bool bInActivate);`
- L27 _protected prototype_ `void OnResetFilters();`
- L29 _protected member_ `TWeakPtr<INavigationToolFilterBar> WeakFilterBar;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Menus/NavigationToolFilterContextMenu.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolFilterContextMenu`  
`class FNavigationToolFilterContextMenu : public TSharedFromThis<FNavigationToolFilterContextMenu>`  
_L15-40_
- inherits: `TSharedFromThis<FNavigationToolFilterContextMenu>`
- L18 _public prototype_ `TSharedRef<SWidget> CreateMenuWidget(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L21 _protected prototype_ `void PopulateMenu(UToolMenu* const InMenu);`
- L23 _protected prototype_ `void PopulateFilterOptionsSection(UToolMenu& InMenu);`
- L24 _protected prototype_ `void PopulateCustomFilterOptionsSection(UToolMenu& InMenu);`
- L25 _protected prototype_ `void PopulateBulkOptionsSection(UToolMenu& InMenu);`
- L27 _protected prototype_ `void OnDisableFilter();`
- L28 _protected prototype_ `void OnResetFilters();`
- L30 _protected prototype_ `void OnActivateWithFilterException();`
- L32 _protected prototype_ `void OnActivateAllFilters(const bool bInActivate);`
- L34 _protected prototype_ `void OnEditFilter();`
- L35 _protected prototype_ `void OnDeleteFilter();`
- L37 _protected prototype_ `const TSharedPtr<FNavigationToolFilter> GetFilter() const;`
- L39 _protected member_ `TWeakPtr<FNavigationToolFilter> WeakFilter;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Menus/NavigationToolItemContextMenu.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolItemContextMenu`  
`class FNavigationToolItemContextMenu : public TSharedFromThis<FNavigationToolItemContextMenu>`  
_L18-31_
- inherits: `TSharedFromThis<FNavigationToolItemContextMenu>`
- L21 _public prototype_ `static FName GetMenuName();`
- L23 _public prototype_ `TSharedRef<SWidget> CreateMenu(const TSharedRef<FNavigationToolView>& InToolView , const TArray<FNavigationToolViewModelWeakPtr>& InWeakItemList);`
- L27 _protected prototype_ `static void PopulateMenu(UToolMenu* const InMenu);`
- L29 _protected prototype_ `static void CreateGenericSection(UToolMenu& InMenu);`
- L30 _protected prototype_ `static void CreateToolSection(UToolMenu& InMenu);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Menus/NavigationToolToolbarMenu.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolToolbarMenu`  
`class FNavigationToolToolbarMenu : public TSharedFromThis<FNavigationToolToolbarMenu>`  
_L19-39_
- inherits: `TSharedFromThis<FNavigationToolToolbarMenu>`
- L22 _public prototype_ `static FName GetMenuName();`
- L24 _public prototype_ `TSharedRef<SWidget> CreateToolbar(const TSharedRef<FNavigationToolView>& InToolView);`
- L27 _protected prototype_ `void PopulateToolBar(UToolMenu* const InMenu);`
- L29 _protected prototype_ `void CreateSettingsMenu(UToolMenu* const InMenu);`
- L30 _protected prototype_ `void CreateItemViewOptionsMenu(UToolMenu* const InMenu);`
- L31 _protected prototype_ `void CreateColumnViewOptionsMenu(UToolMenu* const InMenu);`
- L32 _protected prototype_ `void CreateFilterBarOptionsMenu(UToolMenu* const InMenu);`
- L34 _protected prototype_ `ECheckBoxState GetCustomColumnViewMenuItemCheckState(const FText InColumnViewName, const TSharedRef<FNavigationToolView> InToolView) const;`
- L35 _protected prototype_ `void OnDeleteCustomColumnViewMenuItemClick(const FText InColumnViewName);`
- L37 _protected prototype_ `bool IsGlobalFilterActive(const TSharedRef<FNavigationToolBuiltInFilter> InFilter) const;`
- L38 _protected prototype_ `void OnToggleGlobalFilter(const TSharedRef<FNavigationToolBuiltInFilter> InFilter, const TSharedRef<FNavigationTool> InTool);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Menus/NavigationToolViewMenuContext.h` (Private)


#### class `UNavigationToolViewMenuContext`  
`class UNavigationToolViewMenuContext : public UObject`  
_L15-45_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L22 _public function_ `void Init(const TWeakPtr<UE::SequenceNavigator::FNavigationToolView>& InToolView)`
- L27 _public function_ `TSharedPtr<UE::SequenceNavigator::FNavigationToolView> GetToolView() const`
- L32 _public function_ `TSharedPtr<UE::SequenceNavigator::FNavigationTool> GetTool() const`
- L41 _public member_ `FOnPopulateNavigationToolViewToolbarMenu OnPopulateMenu;`
- L44 _private member_ `TWeakPtr<UE::SequenceNavigator::FNavigationToolView> WeakToolView;`

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateNavigationToolViewToolbarMenu, UToolMenu*);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateNavigationToolViewToolbarMenu, UToolMenu*);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/NavigationTool.h` (Private)


#### class `UE::SequenceNavigator::FNavigationTool`  
`class FNavigationTool : public INavigationTool , public FTickableEditorObject , public FEditorUndoClient`  
_L36-255_
- inherits: `INavigationTool,FTickableEditorObject,FEditorUndoClient`
- L42 _public prototype_ `FNavigationTool(const TWeakPtr<ISequencer>& InWeakSequencer);`
- L44 _public prototype_ `void Init();`
- L45 _public prototype_ `void Shutdown();`
- L47 _public prototype_ `bool CanProcessSequenceSpawn(UMovieSceneSequence* const InSequence) const;`
- L49 _public member_ `FOnToolLoaded OnToolLoaded;`
- L52 _public prototype_ `void GetItemProxiesForItem(const FNavigationToolViewModelPtr& InItem, TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies);` — Gathers all previously existing and new Item Proxies for a given Item
- L55 _public prototype_ `INavigationToolItemProxyFactory* GetItemProxyFactory(const FName InItemProxyTypeName) const;` — Tries to find the Item Proxy Factory for the given Item Proxy Type Name
- L58 _public prototype_ `bool IsToolLocked() const;` — Returns whether the Navigation Tool is in Read-only mode
- L60 _public prototype_ `void HandleUndoRedoTransaction(const FTransaction* const InTransaction, const bool bInIsUndo);`
- L64 _public prototype_ `virtual void ForEachProvider(const TFunction<bool(const TSharedRef<FNavigationToolProvider>& InToolProvider)>& InPredicate) const override;`
- L66 _public prototype_ `virtual TSharedPtr<FUICommandList> GetBaseCommandList() const override;`
- L68 _public prototype_ `virtual bool IsToolTabVisible() const override;`
- L69 _public prototype_ `virtual void ShowHideToolTab(const bool bInVisible) override;`
- L70 _public prototype_ `virtual void ToggleToolTabVisible() override;`
- L72 _public function_ `virtual FOnToolLoaded& GetOnToolLoaded() override`
- L74 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const override;`
- L76 _public prototype_ `virtual TSharedPtr<INavigationToolView> RegisterToolView(const int32 InToolViewId) override;`
- L77 _public prototype_ `virtual TSharedPtr<INavigationToolView> GetToolView(const int32 InToolViewId) const override;`
- L78 _public prototype_ `virtual TSharedPtr<INavigationToolView> GetMostRecentToolView() const override;`
- L80 _public prototype_ `virtual bool IsObjectAllowedInTool(const UObject* const InObject) const override;`
- L82 _public prototype_ `virtual void RegisterItem(const FNavigationToolViewModelPtr& InItem) override;`
- L83 _public prototype_ `virtual void UnregisterItem(const FNavigationToolItemId& InItemId) override;`
- L85 _public prototype_ `virtual void RequestRefresh() override;`
- L86 _public prototype_ `virtual void Refresh() override;`
- L88 _public prototype_ `virtual FNavigationToolViewModelWeakPtr GetTreeRoot() const override;`
- L90 _public prototype_ `virtual FNavigationToolViewModelPtr FindItem(const FNavigationToolItemId& InItemId) const override;`
- L91 _public prototype_ `virtual TArray<FNavigationToolViewModelPtr> TryFindItems(const Sequencer::FViewModelPtr& InSequencerOutlinerViewModel) const override;`
- L93 _public prototype_ `virtual void SetIgnoreNotify(const ENavigationToolIgnoreNotifyFlags InFlag, const bool bInIgnore) override;`
- L95 _public prototype_ `virtual void OnSequencerSelectionChanged() override;`
- L96 _public prototype_ `virtual TArray<FNavigationToolViewModelWeakPtr> GetSelectedItems(const bool bInNormalizeToTopLevelSelections = false) const override;`
- L97 _public prototype_ `virtual void SelectItems(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const ENavigationToolItemSelectionFlags InFlags = ENavigationToolItemSelectionFlags::SignalSelectionChange) const override;`
- L99 _public prototype_ `virtual void ClearItemSelection(const bool bInSignalSelectionChange) const override;`
- L101 _public prototype_ `virtual const FNavigationToolItemProxyRegistry& GetItemProxyRegistry() const override;`
- L102 _public prototype_ `virtual TArray<FName> GetRegisteredItemProxyTypeNames() const override;`
- L104 _public prototype_ `virtual void SetItemColor(const FNavigationToolViewModelPtr& InItem, const FColor& InColor) override;`
- L105 _public prototype_ `virtual void RemoveItemColor(const FNavigationToolViewModelPtr& InItem) override;`
- L106 _public prototype_ `virtual TOptional<FColor> FindItemColor(const FNavigationToolViewModelPtr& InItem, bool bRecurseParent = true) const override;`
- L108 _public prototype_ `virtual void EnqueueItemActions(TArray<TSharedPtr<INavigationToolItemAction>>&& InItemActions) noexcept override;`
- L110 _public prototype_ `virtual void NotifyToolItemRenamed(const FNavigationToolViewModelPtr& InItem) override;`
- L111 _public prototype_ `virtual void NotifyToolItemDeleted(const FNavigationToolViewModelPtr& InItem) override;`
- L115 _public prototype_ `FNavigationToolItemProxyRegistry& GetItemProxyRegistry();`
- L118 _public prototype_ `virtual void PostUndo(const bool bInSuccess) override;`
- L119 _public prototype_ `virtual void PostRedo(const bool bInSuccess) override;`
- L123 _public prototype_ `virtual TStatId GetStatId() const override;`
- L124 _public prototype_ `virtual void Tick(const float InDeltaTime) override;`
- L128 _public prototype_ `void DeleteItems(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems);` — Delete a set of items in the outliner by calling their custom delete handler
- L131 _public prototype_ `void UnregisterToolView(const int32 InToolViewId);` — Unregisters the Navigation Tool View bound to the given id
- L134 _public prototype_ `void UpdateRecentToolViews(const int32 InToolViewId);` — Sets the given Navigation Tool View Id as the most recent Navigation Tool View
- L137 _public prototype_ `void ForEachToolView(const TFunction<void(const TSharedRef<FNavigationToolView>& InToolView)>& InPredicate) const;` — Executes the given predicate for each Navigation Tool View registered
- L140 _public prototype_ `int32 GetPendingItemActionCount() const;` — @return Number of actions that been added to the queue so far before triggering a refresh
- L143 _public prototype_ `bool NeedsRefresh() const;` — @return True if the Navigation Tool is currently in need of a refresh
- L149 _public prototype_ `void NotifyItemIdChanged(const FNavigationToolItemId& OldId, const FNavigationToolViewModelPtr& InItem);` — Replaces the Item's Id in the Item Map. This can be due to an object item changing it's object (e.g. a bp component getting destroyed and recreated, the item should be the same but the underlying component will not be)
- L152 _public prototype_ `static FNavigationToolViewModelPtr FindLowestCommonAncestor(const TArray<FNavigationToolViewModelPtr>& Items);` — Gets the closest item to all the given items while also being their common ancestor
- L158 _public prototype_ `static void SortItems(TArray<FNavigationToolViewModelWeakPtr>& WeakItems, const bool bInReverseOrder = false);` — Sort the given array of items based on their ordering in the Navigation Tool @see FNavigationTool::CompareToolItemOrder
- L161 _public prototype_ `static void NormalizeToTopLevelSelections(TArray<FNavigationToolViewModelWeakPtr>& WeakItems);` — Normalizes the given Items by removing selected items that have their parent item also in the selection
- L164 _public prototype_ `void SyncSequencerSelection(const TArray<FNavigationToolViewModelWeakPtr>& InWeakSelectedItems) const;` — Have the given Selected Items sync to the USelection Instances of Mode Tools
- L167 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap);` — Called when the engine replaces an object. A common example is when a BP Component is destroyed, and replaced
- L170 _public prototype_ `void OnActorReplaced(AActor* const InOldActor, AActor* const InNewActor);` — Called when the engine replaces an Actor
- L173 _public prototype_ `void SetToolModified();` — Marks the Navigation Tool dirty. This triggers INavigationToolProvider::OnToolModified on next tick
- L176 _public prototype_ `void RefreshColumnView();` — If ShouldApplyDefaultColumnView(), applies the active providers default column view
- L178 _public prototype_ `bool DoesGlobalFilterExist(const FName InFilterId);`
- L179 _public prototype_ `void RefreshGlobalFilters();`
- L185 _private prototype_ `void OnTabVisibilityChanged(const bool bInVisible);`
- L187 _private prototype_ `void BindEvents();`
- L188 _private prototype_ `void UnbindEvents();`
- L190 _private prototype_ `void AddItem(const FNavigationToolViewModelPtr& InItem);`
- L191 _private prototype_ `void RemoveItem(const FNavigationToolItemId& InItemId);`
- L192 _private prototype_ `void ForEachItem(TFunctionRef<void(const FNavigationToolViewModelPtr&)> InFunc);`
- L194 _private prototype_ `USequencerSettings* GetSequencerSettings() const;`
- L196 _private prototype_ `void OnTreeViewChanged();`
- L198 _private prototype_ `TArray<FNavigationToolViewModelPtr> FindItemsFromMovieSceneObject(UObject* const InObject) const;`
- L199 _private prototype_ `TArray<FNavigationToolViewModelPtr> FindItemsFromObjectGuid(const FGuid& InObjectGuid) const;`
- L201 _private prototype_ `bool AreAllViewsSyncingItemSelection() const;`
- L203 _private prototype_ `void OnProvidersChanged(const FName InToolId , const TSharedRef<FNavigationToolProvider>& InProvider , const ENavigationToolProvidersChangeType InChangeType);`
- L207 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L209 _private member_ `TSharedRef<FNavigationToolTab> ToolTab;`
- L212 _private member_ `Sequencer::TViewModelPtr<FNavigationToolTreeRoot> RootItem;` — The root of all the items in the outliner
- L214 _private member_ `TSharedPtr<FUICommandList> BaseCommandList;`
- L217 _private member_ `TMap<FNavigationToolItemId, FNavigationToolViewModelPtr> ItemMap;` — The map of the registered items
- L219 _private member_ `TMap<FNavigationToolItemId, FNavigationToolViewModelPtr> ItemsPendingAdd;`
- L221 _private member_ `TSet<FNavigationToolItemId> ItemsPendingRemove;`
- L224 _private member_ `FNavigationToolItemProxyRegistry ItemProxyRegistry;` — Navigation Tool's Item Proxy Factory Registry Instance. This takes precedence over the Module's Factory Registry
- L227 _private member_ `TArray<TSharedPtr<INavigationToolItemAction>> PendingActions;` — The current pending actions before refresh is called
- L230 _private member_ `TSharedPtr<TArray<FNavigationToolViewModelWeakPtr>> ItemsLastSelected;` — The list of items pending selection processing, filled in when the Sequencer selection changes
- L233 _private member_ `TMap<int32, TSharedPtr<FNavigationToolView>> ToolViews;` — The map of registered outliner views
- L236 _private member_ `TArray<int32> RecentToolViews;` — List of Navigation Tool View Ids in order from least recent to most recent (i.e. Index 0 is least recent)
- L239 _private member_ `ENavigationToolIgnoreNotifyFlags IgnoreNotifyFlags = ENavigationToolIgnoreNotifyFlags::None;` — The current events to ignore and not handle automatically
- L242 _private member_ `bool bToolDirty = false;` — Flag indicating whether the Navigation Tool has been changed this tick and should call INavigationToolProvider::OnToolModified next tick
- L245 _private member_ `bool bRefreshing = false;` — Flag indicating Refreshing is taking place
- L248 _private member_ `bool bRefreshRequested = false;` — Flag indicating that a refresh must take place next tick
- L251 _private member_ `bool bIteratingItemMap = false;` — Flag indicating that the Item Map is iterating
- L254 _private member_ `TArray<TSharedPtr<FNavigationToolBuiltInFilter>> GlobalFilters;` — Built in "global" item type filters for all views

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/NavigationToolCommands.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolCommands`  
`class FNavigationToolCommands : public TCommands<FNavigationToolCommands>`  
_L10-59_
- inherits: `TCommands<FNavigationToolCommands>`
- L14 _public prototype_ `FNavigationToolCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> OpenToolSettings;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ToggleToolTabVisible;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> SelectAllChildren;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> SelectImmediateChildren;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> SelectParent;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SelectFirstChild;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> SelectPreviousSibling;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SelectNextSibling;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ExpandAll;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> CollapseAll;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> ExpandSelection;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> CollapseSelection;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ScrollNextSelectionIntoView;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ToggleMutedHierarchy;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoExpandToSelection;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> ToggleShortNames;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> ResetVisibleColumnSizes;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> SaveCurrentColumnView;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> FocusSingleSelection;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> FocusInContentBrowser;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/NavigationToolTab.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolTab`  
`class FNavigationToolTab : public TSharedFromThis<FNavigationToolTab>`  
_L20-66_
- inherits: `TSharedFromThis<FNavigationToolTab>`
- desc: Manages a tool instance tab, including its visible state settings in USequencerSettings
- L23 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, const bool );`
- L27 _public prototype_ `static FName StaticToolTabId(const ISequencer& InSequencer);` — @return Returns the auto generated tool instance tab id using the passed in ISequencer. Tool tab ids are based on the sequencer instance settings name.
- L29 _public prototype_ `FNavigationToolTab(INavigationTool& InOwnerTool);`
- L31 _public prototype_ `void Init();`
- L32 _public prototype_ `void Shutdown();`
- L35 _public prototype_ `bool ShouldShowToolTab() const;` — @return True if the USequencerSettings setting for the tool instance is set to visible
- L38 _public prototype_ `bool IsToolTabVisible() const;` — @return True if the tool instance tab is visible
- L41 _public prototype_ `void ShowHideToolTab(const bool bInVisible);` — Shows or hides the tool instance tab and toggles the state in the saved settings
- L43 _public prototype_ `void ToggleToolTabVisible();`
- L45 _public function_ `FOnVisibilityChanged& OnVisibilityChanged()`
- L48 _protected prototype_ `TSharedPtr<IToolkitHost> GetToolkitHost() const;`
- L49 _protected prototype_ `TSharedPtr<FTabManager> GetTabManager() const;`
- L50 _protected prototype_ `USequencerSettings* GetSequencerSettings() const;`
- L52 _protected prototype_ `void RegisterToolTab();`
- L53 _protected prototype_ `void UnregisterToolTab();`
- L55 _protected prototype_ `TSharedRef<SDockTab> SpawnToolTab(const FSpawnTabArgs& InArgs);`
- L56 _protected prototype_ `void CloseToolTab();`
- L58 _protected member_ `INavigationTool& OwnerTool;`
- L60 _protected member_ `FName NavigationToolTabId;`
- L63 _protected member_ `bool bShuttingDown = false;` — State variable to help the dock tab know when it should save its visibility
- L65 _protected member_ `FOnVisibilityChanged VisibilityChangedDelegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, const bool );`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/NavigationToolView.h` (Private)


#### class `UE::SequenceNavigator::FNavigationToolView`  
`class FNavigationToolView : public INavigationToolView`  
_L35-451_
- inherits: `INavigationToolView`
- desc: A view instance of the Navigation Tool, that handles viewing a subset of the outliner items based on item filters, search text, hierarchy type, etc
- L44 _public prototype_ `explicit FNavigationToolView(FPrivateToken);`
- L48 _public prototype_ `void CreateColumns(const TSharedRef<FNavigationToolProvider>& InProvider);` — Creates columns from a specific provider
- L50 _public prototype_ `void CreateDefaultColumnViews(const TSharedRef<FNavigationToolProvider>& InProvider);`
- L58 _public prototype_ `static TSharedRef<FNavigationToolView> CreateInstance(const int32 InToolViewId , const TSharedRef<FNavigationTool>& InTool , const TSharedPtr<FUICommandList>& InBaseCommandList);` — Creates a Navigation Tool View Instance and register it to the Navigation Tool @param InToolViewId the Id assigned to the Instance created @param InTool the Navigation Tool this Instance View belongs to @param InBaseCommandList the base command list
- L62 _public prototype_ `void PostLoad();`
- L65 _public prototype_ `void OnToolSettingsChanged(UObject* const InObject, FPropertyChangedEvent& InPropertyChangedEvent);` — Called when the UNavigationToolSettings has a property change
- L67 _public prototype_ `void Tick(const float InDeltaTime);`
- L69 _public prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InBaseCommandList);`
- L71 _public prototype_ `TSharedPtr<FUICommandList> GetBaseCommandList() const;`
- L72 _public function_ `TSharedPtr<FUICommandList> GetViewCommandList() const`
- L75 _public prototype_ `void UpdateRecentViews();` — Notifies FNavigationTool so that this view instance becomes the most recent interacted outliner view
- L78 _public prototype_ `bool IsMostRecentToolView() const;` — Returns whether this view instance is the most recently interacted between the instances in FNavigationTool
- L80 _public function_ `int32 GetToolViewId() const`
- L83 _public prototype_ `virtual TSharedPtr<INavigationTool> GetOwnerTool() const override;`
- L84 _public prototype_ `virtual TSharedPtr<SWidget> GetToolWidget() const override;`
- L85 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const override;`
- L86 _public prototype_ `virtual void RequestRefresh() override;`
- L87 _public function_ `virtual FOnToolViewRefreshed& GetOnToolViewRefreshed() override`
- L88 _public prototype_ `virtual void SetKeyboardFocus() override;`
- L89 _public prototype_ `virtual ENavigationToolItemViewMode GetItemDefaultViewMode() const override;`
- L90 _public prototype_ `virtual ENavigationToolItemViewMode GetItemProxyViewMode() const override;`
- L91 _public prototype_ `virtual TSharedRef<SWidget> GetColumnMenuContent(const FName InColumnId) override;`
- L92 _public prototype_ `virtual void GetChildrenOfItem(const FNavigationToolViewModelWeakPtr InWeakItem , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren) const override;`
- L94 _public prototype_ `virtual void GetChildrenOfItem(const FNavigationToolViewModelWeakPtr InWeakItem , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const ENavigationToolItemViewMode InViewMode , const TSet<FNavigationToolViewModelWeakPtr>& InWeakRecursionDisallowedItems) const override;`
- L98 _public prototype_ `virtual bool IsItemReadOnly(const FNavigationToolViewModelWeakPtr& InWeakItem) const override;`
- L99 _public prototype_ `virtual bool CanSelectItem(const FNavigationToolViewModelWeakPtr& InWeakItem) const override;`
- L100 _public prototype_ `virtual void SelectItems(TArray<FNavigationToolViewModelWeakPtr> InWeakItems , const ENavigationToolItemSelectionFlags InFlags = ENavigationToolItemSelectionFlags::SignalSelectionChange) override;`
- L102 _public prototype_ `virtual void ClearItemSelection(const bool bInSignalSelectionChange = true) override;`
- L103 _public prototype_ `virtual bool IsItemSelected(const FNavigationToolViewModelWeakPtr& InWeakItem) const override;`
- L104 _public prototype_ `virtual TArray<FNavigationToolViewModelWeakPtr> GetSelectedItems() const override;`
- L114 _public prototype_ `virtual bool IsItemExpanded(const FNavigationToolViewModelWeakPtr& InWeakItem, const bool bInUseFilter = true) const override;` — virtual FReply OnDragDetected(const FGeometry& InGeometry , const FPointerEvent& InPointerEvent , const FNavigationToolViewModelWeakPtr InWeakTargetItem) override; virtual FReply OnDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem) override; virtual TOptional<EItemDropZone> OnCanDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem) const override;
- L115 _public prototype_ `virtual void SetItemExpansion(const FNavigationToolViewModelWeakPtr& InWeakItem , const bool bInExpand, const bool bInUseFilter = true) override;`
- L117 _public prototype_ `virtual void SetItemExpansionRecursive(const FNavigationToolViewModelWeakPtr InWeakItem, const bool bInExpand) override;`
- L118 _public prototype_ `virtual void SetParentItemExpansions(const FNavigationToolViewModelWeakPtr& InWeakItem, const bool bInExpand) override;`
- L119 _public prototype_ `virtual bool CanExpandAll() const override;`
- L120 _public prototype_ `virtual void ExpandAll() override;`
- L121 _public prototype_ `virtual void CollapseAll() override;`
- L122 _public prototype_ `virtual bool CanCollapseAll() const override;`
- L125 _public prototype_ `FReply OnDragDetected(const FGeometry& InGeometry , const FPointerEvent& InPointerEvent , const FNavigationToolViewModelWeakPtr InWeakTargetItem);`
- L128 _public prototype_ `FReply OnDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem);`
- L131 _public prototype_ `TOptional<EItemDropZone> OnCanDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem) const;`
- L135 _public prototype_ `TSharedPtr<SWidget> CreateItemContextMenu();`
- L138 _public function_ `const TMap<FName, TSharedPtr<INavigationToolColumn>>& GetColumns() const` — Get the columns currently allocated in this Navigation Tool instance
- L141 _public prototype_ `bool ShouldShowColumnByDefault(const TSharedPtr<INavigationToolColumn>& InColumn) const;` — Whether the given column should be shown by default. This is only used at the start when creating the columns
- L144 _public prototype_ `void Refresh();` — Refreshes the items visible in this view and refreshes the Navigation Tool widget if it was created
- L147 _public prototype_ `void UpdateRootVisibleItems();` — Refreshes the items that will be at the top level of the tree (e.g. Actors with no parent item)
- L150 _public prototype_ `void UpdateItemExpansions();` — Updates the item expansions in the tree widget based on whether the Items have the expanded flag or not
- L153 _public prototype_ `void NotifyObjectsReplaced();` — Called when object replacement has taken place. Used to invalidate the widget for painting
- L156 _public prototype_ `FNavigationToolViewModelPtr GetRootItem() const;` — The root item of the tree. Convenience function to get the RootItem from FNavigationTool
- L159 _public prototype_ `const TArray<FNavigationToolViewModelWeakPtr>& GetRootVisibleItems() const;` — Gets the top level items that should be visible in the tree. This can differ between views depending on filters and other factors
- L161 _public prototype_ `void SaveViewItemFlags(const FNavigationToolViewModelWeakPtr& InWeakItem , const ENavigationToolItemFlags InFlags);`
- L164 _public prototype_ `ENavigationToolItemFlags GetViewItemFlags(const FNavigationToolViewModelWeakPtr& InWeakItem) const;`
- L166 _public prototype_ `FLinearColor GetItemBrushColor(const FNavigationToolViewModelPtr InItem) const;`
- L169 _public prototype_ `int32 GetViewSelectedItemCount() const;` — Gets the Currently Selected Item Count in the Tree View
- L172 _public prototype_ `int32 CalculateVisibleItemCount() const;` — Calculates the amount of Items that are visible in this Navigation Tool View
- L175 _public function_ `bool IsSyncingItemSelection() const` — Whether Sync Selection is currently taking place
- L177 _public function_ `TSharedPtr<FNavigationToolFilterBar> GetFilterBar() const`
- L180 _public prototype_ `void NotifyItemSelectionChanged(const TArray<FNavigationToolViewModelWeakPtr>& InWeakSelectedItems , const FNavigationToolViewModelPtr& InItem , const bool bInUpdateModeTools);` — Called when Item selection has changed. This can be called by the Navigation Tool Widget or by the View itself if there's no ToolWidget
- L185 _public prototype_ `bool ShouldShowItem(const FNavigationToolViewModelWeakPtr& InWeakItem , const bool bInUseFilters, const ENavigationToolItemViewMode InViewMode) const;` — Return whether the given item should be visible in this Navigation Tool Instance
- L189 _public prototype_ `int32 GetVisibleChildIndex(const FNavigationToolViewModelPtr& InParentItem, const FNavigationToolViewModelPtr& InChildItem) const;` — Returns the Index of the Child from the Parent's Children Visible List (Visible List can vary between Tool Instances)
- L192 _public prototype_ `FNavigationToolViewModelPtr GetVisibleChildAt(const FNavigationToolViewModelPtr& InParentItem, const int32 InChildIndex) const;` — Returns the Child from the Parent's Children Visible List at the given Index (Visible List can vary between Tool Instances)
- L195 _public prototype_ `bool IsToolLocked() const;` — Returns whether the Tool is Locked. See FNavigationTool::IsToolLocked
- L201 _public prototype_ `void ShowColumn(const TSharedPtr<INavigationToolColumn>& InColumn);` — Activate an Item Column @param InColumn the column to activate
- L207 _public prototype_ `void ShowColumnById(const FName& InColumnId);` — Activate the Item Column with the given ID @param InColumnId the filter id associated with the Filter to activate
- L213 _public prototype_ `void HideColumn(const TSharedPtr<INavigationToolColumn>& InColumn);` — Deactivates the given Item Column @param InColumn the filter to remove from the active filter list
- L216 _public prototype_ `virtual bool IsColumnVisible(const TSharedPtr<INavigationToolColumn>& InColumn) const override;` — Whether the given Column is in the Active Column List
- L218 _public prototype_ `void ToggleViewModeSupport(ENavigationToolItemViewMode& InOutViewMode, ENavigationToolItemViewMode InFlags);`
- L219 _public prototype_ `void ToggleItemDefaultViewModeSupport(ENavigationToolItemViewMode InFlags);`
- L220 _public prototype_ `void ToggleItemProxyViewModeSupport(ENavigationToolItemViewMode InFlags);`
- L222 _public prototype_ `ECheckBoxState GetViewModeCheckState(ENavigationToolItemViewMode InViewMode, ENavigationToolItemViewMode InFlags) const;`
- L223 _public prototype_ `ECheckBoxState GetItemDefaultViewModeCheckState(ENavigationToolItemViewMode InFlags) const;`
- L224 _public prototype_ `ECheckBoxState GetItemProxyViewModeCheckState(ENavigationToolItemViewMode InFlags) const;`
- L230 _public prototype_ `void ToggleMutedHierarchy();` — Action to turn Muted Hierarchy on or off @see bUseMutedHierarchy
- L231 _public function_ `bool CanToggleMutedHierarchy() const`
- L232 _public prototype_ `bool IsMutedHierarchyActive() const;`
- L238 _public prototype_ `void ToggleAutoExpandToSelection();` — Action to turn Auto Expand to Selection on or off @see bAutoExpandToSelection
- L239 _public function_ `bool CanToggleAutoExpandToSelection() const`
- L240 _public prototype_ `bool ShouldAutoExpandToSelection() const;`
- L242 _public prototype_ `void ToggleUseShortNames();`
- L243 _public function_ `bool CanToggleUseShortNames() const`
- L244 _public prototype_ `bool ShouldUseShortNames() const;`
- L246 _public prototype_ `void ToggleShowItemFilters();`
- L247 _public function_ `bool CanToggleShowItemFilters() const`
- L248 _public function_ `bool ShouldShowItemFilters() const`
- L250 _public prototype_ `void ToggleShowItemColumns();`
- L251 _public function_ `bool CanToggleShowItemColumns() const`
- L252 _public function_ `bool ShouldShowItemColumns() const`
- L255 _public prototype_ `void SetItemTypeHidden(const FName InItemTypeName, const bool bInHidden);` — Sets whether the given item type should be hidden or not
- L258 _public prototype_ `void ToggleHideItemTypes(const FName InItemTypeName);` — Toggles the given Item Types to Hide/Show
- L259 _public prototype_ `ECheckBoxState GetToggleHideItemTypesState(const FName InItemTypeName) const;`
- L263 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, INavigationToolItem>::IsDerived>::Type> void HideItemType()` — Hides the given Outliner Item Type from showing in this Outliner View (e.g. Hide Components is used)
- L270 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, INavigationToolItem>::IsDerived>::Type> void ExposeItemType()` — Shows the given Outliner Item Type if it was hidden in this Outliner View (e.g. Showing Components again)
- L276 _public prototype_ `bool IsItemTypeHidden(const FName InItemTypeName) const;` — Whether the given Outliner Item Type is currently hidden in this Outliner View
- L277 _public prototype_ `bool IsItemTypeHidden(const FNavigationToolViewModelPtr& InItem) const;`
- L280 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, INavigationToolItem>::IsDerived>::Type> bool IsItemTypeHidden() const`
- L286 _public prototype_ `void OnDragEnter(const FDragDropEvent& InDragDropEvent , const FNavigationToolViewModelWeakPtr InWeakTargetItem);` — Called when a drag enters the Navigation Tool widgets for the given item (if null, treat as root)
- L290 _public prototype_ `void OnDragLeave(const FDragDropEvent& InDragDropEvent , const FNavigationToolViewModelWeakPtr InWeakTargetItem);` — Called when a drag leaves the Navigation Tool widgets for the given item (if null, treat as root)
- L294 _public prototype_ `void SetDragIntoTreeRoot(const bool bInIsDraggingIntoTreeRoot);` — Called when there's a drag being started/ended to the Navigation Tool widget as a whole (i.e. root) and not an individual item
- L296 _public prototype_ `void RenameSelected();`
- L297 _public prototype_ `void ResetRenaming();`
- L298 _public prototype_ `void OnItemRenameAction(const ENavigationToolRenameAction InRenameAction, const TSharedPtr<INavigationToolView>& InToolView);`
- L299 _public prototype_ `bool CanRenameSelected() const;`
- L301 _public prototype_ `void DeleteSelected();`
- L302 _public prototype_ `bool CanDeleteSelected() const;`
- L304 _public prototype_ `void DuplicateSelected();`
- L305 _public prototype_ `bool CanDuplicateSelected() const;`
- L307 _public prototype_ `void SelectChildren(const bool bInIsRecursive);`
- L308 _public prototype_ `bool CanSelectChildren() const;`
- L310 _public prototype_ `void SelectParent();`
- L311 _public prototype_ `bool CanSelectParent() const;`
- L313 _public prototype_ `void SelectFirstChild();`
- L314 _public prototype_ `bool CanSelectFirstChild() const;`
- L316 _public prototype_ `void SelectSibling(const int32 InDeltaIndex);`
- L317 _public prototype_ `bool CanSelectSibling() const;`
- L320 _public prototype_ `void OnItemExpansionChanged(const FNavigationToolViewModelWeakPtr InWeakItem, const bool bInIsExpanded);` — Called when the given item's expansion state (expanded/collapsed) has changed
- L322 _public prototype_ `void ScrollNextIntoView();`
- L323 _public prototype_ `void ScrollPrevIntoView();`
- L324 _public prototype_ `bool CanScrollNextIntoView() const;`
- L325 _public prototype_ `void ScrollDeltaIndexIntoView(const int32 InDeltaIndex);`
- L326 _public prototype_ `void ScrollItemIntoView(const FNavigationToolViewModelWeakPtr& InWeakItem);`
- L329 _public prototype_ `void SortAndSelectItems(TArray<FNavigationToolViewModelWeakPtr> InWeakItemsToSelect);` — Sorts the given Items in the user-defined order and selects them, and if the Widget is valid focusing to the item in the Widget
- L332 _public prototype_ `void SaveViewState(const TSharedRef<FNavigationToolProvider>& InProvider);` — Save the current state of the Navigation Tool
- L334 _public prototype_ `void LoadViewState(const TSharedRef<FNavigationToolProvider>& InProvider);` — Load the current state of the Navigation Tool
- L337 _public prototype_ `void SaveColumnState(const FName InColumnId = NAME_None);`
- L339 _public prototype_ `void ResetColumnSize(const FName InColumnId);`
- L340 _public prototype_ `bool CanResetColumnSize(const FName InColumnId) const;`
- L342 _public prototype_ `void ResetVisibleColumnSizes();`
- L343 _public prototype_ `bool CanResetAllColumnSizes() const;`
- L346 _public prototype_ `void SaveNewCustomColumnView();` — Display a modal dialog for saving a new custom column view
- L349 _public prototype_ `void ApplyCustomColumnView(const FText InColumnViewName);` — Apply a saved custom column view by name
- L353 _protected prototype_ `void Init(const TSharedRef<FNavigationTool>& InTool, const TSharedPtr<FUICommandList>& InBaseCommandList);` — Initializes the Navigation Tool Instance. Only executed once
- L356 _protected prototype_ `void SetItemSelectionImpl(TArray<FNavigationToolViewModelWeakPtr>&& InWeakItems, const bool bSignalSelectionChange);` — Sets the Selected Items to be the given Items in this List.
- L359 _protected prototype_ `void RefreshTool(const bool bInImmediateRefresh);` — Triggers a Refresh on the FNavigationTool
- L361 _protected prototype_ `void EnsureToolViewCount(const int32 InToolViewId) const;`
- L364 _protected prototype_ `void SaveFilterState(FNavigationToolViewSaveState& OutViewSaveState);`
- L366 _protected prototype_ `void LoadFilterState(const FNavigationToolViewSaveState& InViewSaveState , const bool bInDisableAllFilters = true , const bool bInRequestFilterUpdate = true);`
- L371 _protected prototype_ `void SaveToolViewItems(FNavigationToolViewSaveState& OutViewSaveState);` — Save the Item State in the Navigation Tool Widget (e.g. Item Scoped Flags)
- L373 _protected prototype_ `void LoadToolViewItems(FNavigationToolViewSaveState& InViewSaveState);` — Load the Item State in the Navigation Tool Widget (e.g. Item Scoped Flags)
- L375 _protected prototype_ `bool CanFocusSingleSelection() const;`
- L376 _protected prototype_ `void FocusSingleSelection();`
- L378 _protected prototype_ `bool CanFocusInContentBrowser() const;`
- L379 _protected prototype_ `void FocusInContentBrowser();`
- L381 _protected prototype_ `bool UpdateFilters();`
- L384 _protected member_ `int32 ToolViewId = -1;` — Local Identifier of this Instance
- L387 _protected member_ `TWeakPtr<FNavigationTool> WeakTool;` — Weak pointer to the outliner this is a view of
- L390 _protected member_ `TSharedPtr<SNavigationToolView> ToolViewWidget;` — Widget showing the View. Can be null if instanced for testing (i.e. bCreateToolWidget is false in Init)
- L393 _protected member_ `TSharedPtr<FUICommandList> ViewCommandList;` — Command List mapped to the View to handle things like Selected Items
- L396 _protected member_ `TWeakObjectPtr<UNavigationToolSettings> WeakToolSettings;` — Settings for the tool
- L399 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakRootVisibleItems;` — Root Items from Navigation Tool visible to this Instance. i.e. a Subset of all the Items in FNavigationTool
- L402 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakSelectedItems;` — A list of the Selected Items in this Navigation Tool View
- L405 _protected member_ `mutable TSet<FNavigationToolViewModelWeakPtr> WeakReadOnlyItems;` — Set of Items that are Currently Read Only in this Instance. Mutable as this changes on GetChildrenOfItem const func
- L408 _protected member_ `TSet<FName> HiddenItemTypes;` — A set of the Navigation Tool Item Type Names that should be hidden
- L410 _protected member_ `TSharedPtr<FNavigationToolFilterBar> FilterBar;`
- L413 _protected member_ `FOnToolViewRefreshed OnToolViewRefreshed;` — Delegate called at the end of the Navigation Tool View Refresh
- L416 _protected member_ `TMap<FName, TSharedPtr<INavigationToolColumn>> Columns;` — Map of the Column Ids and the Column with that Id. This is filled in FNavigationToolView::CreateColumns
- L419 _protected member_ `TSharedPtr<FNavigationToolItemContextMenu> ItemContextMenu;` — Right click context menu for items
- L422 _protected member_ `int32 NextSelectedItemIntoView = -1;` — The Index of the Item that will be scrolled into View
- L425 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakSortedSelectedItems;` — Selected Items Sorted from Top To Bottom
- L428 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakItemsRemainingRename;` — The list of items that need renaming and are waiting for their turn to be renamed
- L431 _protected member_ `FNavigationToolViewModelWeakPtr WeakCurrentItemRenaming;` — The current item in the process of renaming. Null if no renaming is taking place
- L434 _protected member_ `bool bRefreshRequested = false;` — Flag to call FNavigationToolView::Refresh next tick
- L437 _protected member_ `bool bRenamingItems = false;` — Whether Item renaming is taking place in this View
- L440 _protected member_ `bool bRequestedRename = false;` — Whether Renaming Items should be processed next tick
- L443 _protected member_ `bool bSyncingItemSelection = false;` — Whether Items are currently being synced to what the Widget or Interface sent. Used as a re-enter guard
- L446 _protected member_ `bool bShowItemFilters = false;` — Flag used for the Navigation Tool Widget to determine if the Item Filter Bar should open and show the Item Filters
- L448 _protected member_ `bool bShowItemColumns = false;`
- L450 _protected member_ `bool bFilterUpdateRequested = false;`

#### struct `UE::SequenceNavigator::FNavigationToolView::FPrivateToken`  
`struct FPrivateToken`  
_L41-41_
- L41 _public prototype_ `struct FPrivateToken`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/SequenceNavigatorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSequenceNavigator, Log, All);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/SequenceNavigatorModule.h` (Private)


#### class `FSequenceNavigatorModule`  
`class FSequenceNavigatorModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Utils/NavigationToolMiscUtils.h` (Private)


#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L30 _prototype_ `void RecordUsageAnalytics(const FString& InParamName, const FString& InParamValue);` (scope `UE::SequenceNavigator`) — Records usage analytics for the Sequence Navigator tool. @param InParamName Parameter name string @param InParamValue Parameter value string
- L37 _prototype_ `FSourceControlStatePtr FindSourceControlState(UPackage* const InPackage);` (scope `UE::SequenceNavigator`) — Find the source control state for a given package. @param InPackage The package for which the source control state is being queried. @return The source control state if available, otherwise nullptr.
- L44 _prototype_ `const FSlateBrush* FindSourceControlStatusBrush(UPackage* const InPackage);` (scope `UE::SequenceNavigator`) — Find the source control status brush associated with a given package. @param InPackage The package for which the source control status brush is being queried. @return A pointer to the slate brush representing the source control status, or nullptr if unavailable.
- L51 _prototype_ `FText FindSourceControlStatusText(UPackage* const InPackage);` (scope `UE::SequenceNavigator`) — Find the source control status text for the specified package. @param InPackage The package for which the source control status text is being requested. @return The tooltip text representing the source control status if available, otherwise an empty text.
- L58 _prototype_ `void FocusSequence(const INavigationTool& InTool, UMovieSceneSequence& InSequence);` (scope `UE::SequenceNavigator`) — Focuses a sub-movie scene (MovieScene within a MovieScene) in the sequencer. @param InTool The Navigation Tool that manages scene sequences. @param InSequence The movie scene sequence to focus on.
- L66 _prototype_ `void FocusSequence(const INavigationTool& InTool , UMovieSceneSequence& InSequence , const FNavigationToolSequence& InSequenceItem);` (scope `UE::SequenceNavigator`) — Focuses a sub-movie scene (MovieScene within a MovieScene) in the sequencer. @param InTool The Navigation Tool that manages scene sequences. @param InSequence The movie scene sequence to focus on. @param InSequenceItem Optional sequence item to select in the sequence.
- L76 _prototype_ `void FocusSequence(const INavigationTool& InTool , UMovieSceneSequence& InSequence , const FNavigationToolTrack& InTrackItem);` (scope `UE::SequenceNavigator`) — Focuses a sub-movie scene (MovieScene within a MovieScene) in the sequencer. @param InTool The Navigation Tool that manages scene sequences. @param InSequence The movie scene sequence to focus on. @param InTrackItem Optional track item to select in the sequence.
- L86 _prototype_ `void FocusSequence(const INavigationTool& InTool , UMovieSceneSequence& InSequence , const FNavigationToolBinding& InBindingItem);` (scope `UE::SequenceNavigator`) — Focuses a sub-movie scene (MovieScene within a MovieScene) in the sequencer. @param InTool The Navigation Tool that manages scene sequences. @param InSequence The movie scene sequence to focus on. @param InBindingItem Optional binding item to select in the sequence.
- L91 _prototype_ `void SelectSequencerBindingTrack(const ISequencer& InSequencer, const FGuid& InObjectId);` (scope `UE::SequenceNavigator`) — Selects an object binding track in a sequencer.
- L99 _prototype_ `void FocusSequence(const INavigationTool& InTool , UMovieSceneSequence& InSequence , const FMovieSceneMarkedFrame& InMarkedFrame);` (scope `UE::SequenceNavigator`) — Focuses a sub-movie scene (MovieScene within a MovieScene) in the sequencer. @param InTool The Navigation Tool that manages scene sequences. @param InSequence The movie scene sequence to focus on. @param InMarkedFrame Optional marked frame to select in the sequence.
- L103 _prototype_ `void FocusItemInSequencer(const INavigationTool& InTool , const FNavigationToolViewModelPtr& InItem);` (scope `UE::SequenceNavigator`)
- L112 _prototype_ `FMovieSceneSequenceID ResolveSequenceID(const ISequencer& InSequencer, UMovieSceneSequence* const InSequence);` (scope `UE::SequenceNavigator`) — Resolve the sequence ID for a given sequence within the provided sequencer. @param InSequencer The sequencer instance to retrieve the sequence ID from. @param InSequence The sequence whose ID is to be resolved. @return The resolved sequence ID if found, otherwise an empty sequence ID.
- L121 _prototype_ `TArrayView<TWeakObjectPtr<>> ResolveBoundObjects(const ISequencer& InSequencer , UMovieSceneSequence* const InSequence, const FGuid& InBindingId);` (scope `UE::SequenceNavigator`) — Resolves the objects bound to a specified binding ID within a sequence. @param InSequencer The sequencer instance used for evaluating bindings and sequences. @param InSequence The movie scene sequence to search for bindings. @param InBindingId The binding ID whose bound objects are being resolved. @return A view of the objects bound to the specified binding ID in the specified sequence.

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Utils/NavigationToolMovieSceneUtils.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L16 _prototype_ `FFrameTime ConvertToDisplayRateTime(const UMovieSceneSequence& InSequence, const FFrameTime& InTime);` (scope `UE::SequenceNavigator`)
- L17 _prototype_ `FFrameTime ConvertToTickResolutionTime(const UMovieSceneSequence& InSequence, const FFrameTime& InTime);` (scope `UE::SequenceNavigator`)
- L25 _prototype_ `UMovieSceneSubSection* FindSequenceSubSection(ISequencer& InSequencer, UMovieSceneSequence* const InSequence);` (scope `UE::SequenceNavigator`) — Finds the subsection corresponding to a given sequence within the specified sequencer. @param InSequencer The sequencer to search within. @param InSequence The movie scene sequence for which the subsection is to be found. @return The found movie scene subsection, or nullptr if no matching subsection is found.
- L32 _prototype_ `bool IsGloballyMarkedFramesForSequence(UMovieSceneSequence* const InSequence);` (scope `UE::SequenceNavigator`) — Checks if globally marked frames are enabled for the given movie scene sequence. @param InSequence The movie scene sequence to check. @return True if globally marked frames are enabled for the specified sequence, false otherwise.
- L40 _prototype_ `void ShowGloballyMarkedFramesForSequence(ISequencer& InSequencer , UMovieSceneSequence* const InSequence, const bool bInVisible);` (scope `UE::SequenceNavigator`) — Toggles the visibility of globally marked frames for the specified sequence within the provided sequencer. @param InSequencer The sequencer controlling the movie scene. @param InSequence The movie scene sequence for which the globally marked frame visibility is to be changed. @param bInVisible Indicates whether the globally marked frames should be visible (true) or hidden (false).
- L47 _prototype_ `void ModifySequenceAndMovieScene(UMovieSceneSequence* const InSequence);` (scope `UE::SequenceNavigator`) — Modifies the given sequence and its associated movie scene to ensure they are marked as modified. @param InSequence The movie scene sequence to modify, including its associated movie scene.
- L54 _prototype_ `void GetSequenceSubSections(UMovieSceneSequence* const InSequence, TArray<UMovieSceneSubSection*>& OutSubSections);` (scope `UE::SequenceNavigator`) — Retrieves all sections as subsections from the given movie scene sequence. @param InSequence The movie scene sequence to retrieve subsections from. @param OutSubSections The array to be populated with found movie scene subsections.

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolColor.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolColor`  
`class SNavigationToolColor : public SCompoundWidget`  
_L18-60_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolColor)`
- L24 _public prototype_ `virtual ~SNavigationToolColor() override = default;`
- L26 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L31 _public prototype_ `FLinearColor GetColorBlockColor() const;`
- L32 _public prototype_ `void RemoveItemColor() const;`
- L34 _public prototype_ `FSlateColor GetBorderColor() const;`
- L35 _public prototype_ `FLinearColor GetStateColorAndOpacity() const;`
- L37 _public prototype_ `FReply OnColorEntrySelected(const FColor& InColor) const;`
- L39 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L40 _public prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L43 _protected prototype_ `FReply OnColorMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InEvent);`
- L45 _protected prototype_ `void OpenColorPickerDialog();`
- L47 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L49 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L51 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L53 _protected member_ `TWeakPtr<INavigationTool> WeakTool;`
- L55 _protected member_ `TSharedPtr<SMenuAnchor> ColorOptions;`
- L57 _protected member_ `mutable FColor ItemColor = FColor();`
- L59 _protected member_ `bool bIsPressed = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolComment.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolComment`  
`class SNavigationToolComment : public SCompoundWidget`  
_L18-45_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolComment)`
- L24 _public prototype_ `virtual ~SNavigationToolComment() override;`
- L26 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L32 _protected prototype_ `FString GetMetaDataComment() const;`
- L34 _protected prototype_ `FText GetCommentText() const;`
- L35 _protected prototype_ `void OnCommentTextChanged(const FText& InNewText);`
- L36 _protected prototype_ `void OnCommentTextCommitted(const FText& InNewText, const ETextCommit::Type InCommitType);`
- L38 _protected prototype_ `FText GetTransactionText() const;`
- L40 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L42 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L44 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolDeactiveState.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolDeactiveState`  
`class SNavigationToolDeactiveState : public SImage`  
_L25-68_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L28 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolDeactiveState)`
- L29 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FNavigationToolDeactiveStateColumn>& InColumn , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L39 _protected function_ `virtual bool IsVisibilityWidgetEnabled() const` — Returns whether the widget is enabled or not
- L41 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;`
- L44 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L45 _protected prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L46 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InInGeometry, const FPointerEvent& InPointerEvent) override;`
- L47 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L48 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L49 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L52 _protected prototype_ `FReply HandleClick();`
- L54 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L56 _protected prototype_ `Sequencer::EDeactivatableState GetInactiveState() const;`
- L57 _protected prototype_ `void SetIsDeactivated(const bool bInIsDeactivated);`
- L59 _protected member_ `TWeakPtr<FNavigationToolDeactiveStateColumn> WeakColumn;`
- L61 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L63 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L65 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L67 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolEndFrameOffset.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolEndFrameOffset`  
`class SNavigationToolEndFrameOffset : public SNavigationToolTime`  
_L14-33_
- inherits: `SNavigationToolTime`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolEndFrameOffset)`
- L20 _public prototype_ `virtual ~SNavigationToolEndFrameOffset() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L29 _protected prototype_ `virtual double GetFrameTimeValue() const override;`
- L30 _protected prototype_ `virtual void OnFrameTimeValueCommitted(const double InNewValue, const ETextCommit::Type InCommitType) override;`
- L31 _protected prototype_ `virtual FText GetTransactionText() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolHBias.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolHBias`  
`class SNavigationToolHBias : public SCompoundWidget`  
_L17-46_
- inherits: `SCompoundWidget`
- L20 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolHBias)`
- L23 _public prototype_ `virtual ~SNavigationToolHBias() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L31 _protected prototype_ `int32 GetValue() const;`
- L32 _protected prototype_ `void OnValueChanged(const int32 InNewValue);`
- L33 _protected prototype_ `void OnValueCommitted(const int32 InNewValue, const ETextCommit::Type InCommitType);`
- L34 _protected prototype_ `void OnBeginSliderMovement();`
- L35 _protected prototype_ `void OnEndSliderMovement(const int32 InNewValue);`
- L37 _protected prototype_ `FText GetTransactionText() const;`
- L39 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L41 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L43 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L45 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolId.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolId`  
`class SNavigationToolId : public SCompoundWidget`  
_L14-32_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolId)`
- L20 _public prototype_ `virtual ~SNavigationToolId() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L29 _protected prototype_ `FText GetItemText() const;`
- L31 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolInTime.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolInTime`  
`class SNavigationToolInTime : public SNavigationToolTime`  
_L15-35_
- inherits: `SNavigationToolTime`
- L18 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolInTime)`
- L21 _public prototype_ `virtual ~SNavigationToolInTime() override = default;`
- L23 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L30 _protected prototype_ `virtual FName GetStyleName() const override;`
- L31 _protected prototype_ `virtual double GetFrameTimeValue() const override;`
- L32 _protected prototype_ `virtual void OnFrameTimeValueCommitted(const double InNewValue, const ETextCommit::Type InCommitType) override;`
- L33 _protected prototype_ `virtual FText GetTransactionText() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolItemChip.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolItemChip`  
`class SNavigationToolItemChip : public SBorder`  
_L25-81_
- inherits: `SBorder`
- desc: Chip Widgets that represent an Item in a compact way in the Items Column
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnItemChipClicked, const FNavigationToolViewModelPtr& InItem, const FPointerEvent& InPointerEvent);`
- L30 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolItemChip)`
- L31 _public prototype_ `SLATE_EVENT(FOnItemChipClicked, OnItemChipClicked) SLATE_EVENT(FOnDragOver, OnValidDragOver) SLATE_STYLE_ARGUMENT(FTableRowStyle, ChipStyle) SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedPtr<INavigationToolView>& InView);`
- L41 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements, int32 LayerId , const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L44 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L45 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L46 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& InCaptureLostEvent) override;`
- L53 _public prototype_ `bool IsSelected() const;`
- L54 _public prototype_ `const FSlateBrush* GetItemBackgroundBrush() const;`
- L55 _public prototype_ `const FSlateBrush* GetDropIndicatorBrush(EItemDropZone InItemDropZone) const;`
- L58 _protected function_ `bool IsPressed() const`
- L59 _protected prototype_ `void Press();`
- L60 _protected prototype_ `void Release();`
- L62 _protected prototype_ `static EItemDropZone GetHoverZone(const FVector2f& InLocalPosition, const FVector2f& InLocalSize);`
- L64 _protected prototype_ `FSlateColor GetIconColor() const;`
- L66 _protected prototype_ `FText GetTooltipText() const;`
- L68 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L70 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L72 _protected member_ `TOptional<EItemDropZone> ItemDropZone;`
- L74 _protected member_ `const FTableRowStyle* ChipStyle = nullptr;`
- L76 _protected member_ `FOnItemChipClicked OnItemChipClicked;`
- L78 _protected member_ `FOnDragOver OnValidDragOver;`
- L80 _protected member_ `bool bIsPressed = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FOnItemChipClicked, const FNavigationToolViewModelPtr& InItem, const FPointerEvent& InPointerEvent);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolItemList.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolItemList`  
`class SNavigationToolItemList : public SCompoundWidget`  
_L17-48_
- inherits: `SCompoundWidget`
- desc: Widget that visualizes the list of children an Item has when collapsed
- L20 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolItemList)`
- L23 _public prototype_ `virtual ~SNavigationToolItemList() override;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L30 _public prototype_ `void OnItemExpansionChanged(const TSharedPtr<INavigationToolView>& InToolView, bool bInIsExpanded);`
- L32 _public prototype_ `void Refresh();`
- L34 _public prototype_ `FReply OnItemChipSelected(const FNavigationToolViewModelPtr& InItem, const FPointerEvent& InPointerEvent);`
- L36 _public prototype_ `FReply OnItemChipValidDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L39 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L41 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L43 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L45 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakChildItems;`
- L47 _protected member_ `TSharedPtr<SScrollBox> ItemListBox;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolLabelComponent.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolLabelComponent`  
`class SNavigationToolLabelComponent : public SNavigationToolLabelItem`  
_L16-29_
- inherits: `SNavigationToolLabelItem`
- L19 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolLabelComponent)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L27 _public prototype_ `virtual const FInlineEditableTextBlockStyle* GetTextBlockStyle() const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolLabelItem.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolLabelItem`  
`class SNavigationToolLabelItem : public SCompoundWidget`  
_L20-56_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolLabelItem)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L30 _public prototype_ `bool IsReadOnly() const;`
- L32 _public prototype_ `bool IsItemEnabled() const;`
- L34 _public prototype_ `FText GetItemText() const;`
- L36 _public prototype_ `bool OnVerifyItemLabelChanged(const FText& InLabel, FText& OutErrorMessage);`
- L38 _public prototype_ `void OnLabelTextCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);`
- L39 _public prototype_ `void RenameItem(const FText& InLabel);`
- L41 _public prototype_ `void OnRenameAction(ENavigationToolRenameAction InRenameAction, const TSharedPtr<INavigationToolView>& InToolView) const;`
- L43 _public prototype_ `void OnEnterEditingMode();`
- L44 _public prototype_ `void OnExitEditingMode();`
- L46 _public prototype_ `virtual const FInlineEditableTextBlockStyle* GetTextBlockStyle() const;`
- L49 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L51 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L53 _protected member_ `TSharedPtr<SInlineEditableTextBlock> InlineTextBlock;`
- L55 _protected member_ `bool bInEditingMode = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolLength.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolLength`  
`class SNavigationToolLength : public SNavigationToolTime`  
_L14-33_
- inherits: `SNavigationToolTime`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolLength)`
- L20 _public prototype_ `virtual ~SNavigationToolLength() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L29 _protected prototype_ `virtual double GetFrameTimeValue() const override;`
- L30 _protected prototype_ `virtual FText GetTransactionText() const override;`
- L31 _protected prototype_ `virtual TSharedPtr<INumericTypeInterface<double>> GetNumericTypeInterface() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolLock.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolLock`  
`class SNavigationToolLock : public SImage`  
_L25-71_
- inherits: `SImage`
- L28 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolLock)`
- L31 _public prototype_ `virtual ~SNavigationToolLock() override = default;`
- L33 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L38 _public prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L40 _public prototype_ `Sequencer::ELockableLockState GetLockState() const;`
- L42 _public prototype_ `void SetIsLocked(const bool bInIsLocked);`
- L44 _public prototype_ `const FSlateBrush* GetBrush() const;`
- L46 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L49 _public prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;` — If a lock drag drop operation has entered this widget, set its item to the new lock state
- L51 _public prototype_ `FReply HandleClick();`
- L53 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InInGeometry, const FPointerEvent& InPointerEvent) override;`
- L55 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L57 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L59 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L64 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L66 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L68 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L70 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolMarkerVisibility.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolMarkerVisibility`  
`class SNavigationToolMarkerVisibility : public SImage`  
_L19-62_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L22 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolMarkerVisibility)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FNavigationToolMarkerVisibilityColumn>& InColumn , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L33 _protected function_ `virtual bool IsVisibilityWidgetEnabled() const` — Returns whether the widget is enabled or not
- L35 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;`
- L37 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L38 _protected prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L40 _protected prototype_ `FReply HandleClick();`
- L42 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InInGeometry, const FPointerEvent& InPointerEvent) override;`
- L43 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L44 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L45 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& InCaptureLostEvent) override;`
- L47 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L49 _protected prototype_ `EItemMarkerVisibility GetMarkerVisibility() const;`
- L51 _protected prototype_ `void SetMarkersVisible(const bool bInVisible);`
- L53 _protected member_ `TWeakPtr<FNavigationToolMarkerVisibilityColumn> WeakColumn;`
- L55 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L57 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L59 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L61 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolOutTime.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolOutTime`  
`class SNavigationToolOutTime : public SNavigationToolTime`  
_L16-36_
- inherits: `SNavigationToolTime`
- L19 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolOutTime)`
- L22 _public prototype_ `virtual ~SNavigationToolOutTime() override = default;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L31 _protected prototype_ `virtual FName GetStyleName() const override;`
- L32 _protected prototype_ `virtual double GetFrameTimeValue() const override;`
- L33 _protected prototype_ `virtual void OnFrameTimeValueCommitted(const double InNewValue, const ETextCommit::Type InCommitType) override;`
- L34 _protected prototype_ `virtual FText GetTransactionText() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolPlayhead.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolPlayhead`  
`class SNavigationToolPlayhead : public SImage`  
_L17-46_
- inherits: `SImage`
- desc: Widget responsible for showing whether an item's range contains the playhead
- L20 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolPlayhead)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FNavigationToolPlayheadColumn>& InColumn , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L31 _protected function_ `virtual bool IsVisibilityWidgetEnabled() const` — Returns whether the widget is enabled or not
- L33 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;`
- L35 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L37 _protected prototype_ `EItemContainsPlayhead GetContainsPlayhead() const;`
- L39 _protected member_ `TWeakPtr<FNavigationToolPlayheadColumn> WeakColumn;`
- L41 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L43 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L45 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolRevisionControl.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolRevisionControl`  
`class SNavigationToolRevisionControl : public SImage`  
_L16-41_
- inherits: `SImage`
- L19 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolRevisionControl)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FNavigationToolRevisionControlColumn>& InColumn , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L29 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L31 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;`
- L32 _protected prototype_ `virtual FText GetToolTipText() const;`
- L34 _protected member_ `TWeakPtr<FNavigationToolRevisionControlColumn> WeakColumn;`
- L36 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L38 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L40 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolStartFrameOffset.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolStartFrameOffset`  
`class SNavigationToolStartFrameOffset : public SNavigationToolTime`  
_L14-33_
- inherits: `SNavigationToolTime`
- L17 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolStartFrameOffset)`
- L20 _public prototype_ `virtual ~SNavigationToolStartFrameOffset() override = default;`
- L22 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L29 _protected prototype_ `virtual double GetFrameTimeValue() const override;`
- L30 _protected prototype_ `virtual void OnFrameTimeValueCommitted(const double InNewValue, const ETextCommit::Type InCommitType) override;`
- L31 _protected prototype_ `virtual FText GetTransactionText() const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolTake.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolTake`  
`class SNavigationToolTake : public SCompoundWidget`  
_L19-57_
- inherits: `SCompoundWidget`
- desc: Column widget that displays a combo box dropdown list of takes for a specific sequence
- L22 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolTake)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L30 _public prototype_ `void SetActiveTake(const TSharedPtr<FSequenceTakeEntry>& InTakeInfo);`
- L33 _protected prototype_ `FSlateColor GetBorderColor() const;`
- L35 _protected prototype_ `FReply OnTakeEntrySelected(const TSharedRef<FSequenceTakeEntry> InTakeInfo);`
- L37 _protected prototype_ `TSharedRef<SWidget> GenerateTakeWidget(const TSharedPtr<FSequenceTakeEntry> InTakeInfo , const bool bShowTakeIndex, const bool bShowNumberedOf);`
- L40 _protected prototype_ `void OnSelectionChanged(const TSharedPtr<FSequenceTakeEntry> InTakeInfo, const ESelectInfo::Type InSelectType);`
- L42 _protected prototype_ `void CacheTakes();`
- L44 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L46 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L48 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L50 _protected member_ `TWeakPtr<INavigationTool> WeakTool;`
- L52 _protected member_ `TArray<TSharedPtr<FSequenceTakeEntry>> CachedTakes;`
- L54 _protected member_ `TSharedPtr<FSequenceTakeEntry> ActiveTakeInfo;`
- L56 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolTakeEntry.h` (Private)


#### struct `UE::SequenceNavigator::FSequenceTakeEntry`  
`struct FSequenceTakeEntry`  
_L13-25_
- desc: Stores information about a sequence take
- L16 _public member_ `TWeakObjectPtr<UMovieSceneSequence> WeakSequence;` — Sequence that the take belongs to
- L19 _public member_ `uint32 TakeIndex = 0;` — Index that the take is serialized to that will change depending on added/removed entries
- L22 _public member_ `uint32 TakeNumber = 0;` — Take number that doesn't change after being serialized
- L24 _public member_ `FText DisplayName;`

#### class `UE::SequenceNavigator::SNavigationToolTakeEntry`  
`class SNavigationToolTakeEntry : public SCompoundWidget`  
_L28-76_
- inherits: `SCompoundWidget`
- desc: Widget that display information about a single sequence take
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnTakeEntrySelected, const TSharedRef<FSequenceTakeEntry> );`
- L33 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolTakeEntry)`
- L34 _public prototype_ `SLATE_ATTRIBUTE(int32, TotalTakeCount) SLATE_EVENT(FOnTakeEntrySelected, OnEntrySelected) SLATE_ARGUMENT(bool, ShowTakeIndex) SLATE_ARGUMENT(bool, ShowNumberedOf) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FSequenceTakeEntry>& InTakeEntry);`
- L47 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L48 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L49 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L51 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L52 _public prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L53 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L54 _public prototype_ `virtual FReply OnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L55 _public prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L60 _protected prototype_ `const FSlateBrush* GetBorderImage() const;`
- L62 _protected prototype_ `FText GetTakeNumberText() const;`
- L63 _protected prototype_ `FText GetTakeNameText() const;`
- L64 _protected prototype_ `FText GetTakeIndexText() const;`
- L66 _protected member_ `TSharedPtr<FSequenceTakeEntry> TakeEntry;`
- L68 _protected member_ `TAttribute<int32> TotalTakeCount;`
- L69 _protected member_ `FOnTakeEntrySelected OnTakeEntrySelected;`
- L71 _protected member_ `bool ShowTakeIndex = false;`
- L72 _protected member_ `bool ShowNumberedOf = false;`
- L75 _protected member_ `bool bHighlightForDragDrop = false;` — Highlight effect to display which entry is dragged over

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FReply, FOnTakeEntrySelected, const TSharedRef<FSequenceTakeEntry> );`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Columns/SNavigationToolTime.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolTime`  
`class SNavigationToolTime : public SCompoundWidget`  
_L27-73_
- inherits: `SCompoundWidget`
- desc: Base time column widget. Subclass this widget to implement a time-based property column widget.
- L30 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolTime)`
- L33 _public prototype_ `virtual ~SNavigationToolTime() override = default;`
- L35 _public prototype_ `void Construct(const FArguments& InArgs , const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRowWidget);`
- L40 _public prototype_ `virtual bool IsReadOnly() const;`
- L41 _public prototype_ `virtual void SetIsReadOnly(const bool bInIsReadOnly);`
- L44 _protected prototype_ `virtual FName GetStyleName() const;`
- L48 _protected prototype_ `virtual double GetFrameTimeValue() const = 0;`
- L50 _protected prototype_ `virtual void OnFrameTimeValueChanged(const double InNewValue);`
- L51 _protected prototype_ `virtual void OnFrameTimeValueCommitted(const double InNewValue, const ETextCommit::Type InCommitType);`
- L53 _protected prototype_ `virtual void OnBeginSliderMovement();`
- L54 _protected prototype_ `virtual void OnEndSliderMovement(const double InNewValue);`
- L56 _protected prototype_ `virtual TSharedPtr<INumericTypeInterface<double>> GetNumericTypeInterface() const;`
- L58 _protected prototype_ `virtual double GetDisplayRateDeltaFrameCount() const;`
- L60 _protected prototype_ `virtual FText GetTransactionText() const = 0;`
- L64 _protected prototype_ `TSharedPtr<ISequencer> GetSequencer() const;`
- L66 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L67 _protected member_ `TWeakPtr<INavigationToolView> WeakView;`
- L68 _protected member_ `TWeakPtr<SNavigationToolTreeRow> WeakRowWidget;`
- L70 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;`
- L72 _protected member_ `bool bIsReadOnly = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/ModalTextInputDialog.h` (Private)


#### class `UE::SequenceNavigator::FModalTextInputDialog`  
`class FModalTextInputDialog`  
_L13-30_
- L16 _public prototype_ `FModalTextInputDialog();`
- L19 _public prototype_ `bool Open(const FText& InDefaultText, FText& OutText, const TSharedPtr<SWindow>& InParentWindow = nullptr);` — @return True if the text input was accepted. False if cancel was clicked.
- L21 _public prototype_ `bool IsOpen();`
- L23 _public prototype_ `void Close();`
- L25 _public member_ `FText DialogTitle;`
- L26 _public member_ `FText InputLabel;`
- L29 _protected member_ `TSharedPtr<SWindow> WindowWidget;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolCustomTextFilterDialog.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolCustomTextFilterDialog`  
`class SNavigationToolCustomTextFilterDialog : public SWindow`  
_L21-70_
- inherits: `SWindow`
- L26 _public prototype_ `static bool IsOpen();`
- L27 _public prototype_ `static void CloseWindow();`
- L29 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolCustomTextFilterDialog)`
- L31 _public prototype_ `SLATE_ARGUMENT(FCustomTextFilterData, CustomTextFilterData) SLATE_EVENT(FOnNavigationToolTryCreateFilter, OnTryCreateFilter) SLATE_EVENT(FOnNavigationToolTryModifyFilter, OnTryModifyFilter) SLATE_EVENT(FOnNavigationToolTryDeleteFilter, OnTryDeleteFilter) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _protected prototype_ `static void ShowWindow(const TSharedRef<SWindow>& InWindowToShow, const bool bInModal, const TSharedPtr<SWindow>& InParentWindow = nullptr);`
- L43 _protected member_ `static TSharedPtr<SNavigationToolCustomTextFilterDialog> DialogInstance;` — Only allow one instance of this dialog at a time. This class is private so we will store the instance here.
- L45 _protected prototype_ `TSharedRef<SWidget> ConstructFilterLabelRow();`
- L46 _protected prototype_ `TSharedRef<SWidget> ConstructFilterColorRow();`
- L47 _protected prototype_ `TSharedRef<SWidget> ConstructFilterStringRow();`
- L48 _protected prototype_ `TSharedRef<SWidget> ConstructContentRow(const FText& InLabel, const TSharedRef<SWidget>& InContentWidget);`
- L49 _protected prototype_ `TSharedRef<SWidget> ConstructButtonRow();`
- L51 _protected prototype_ `FReply OnColorBlockMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);`
- L53 _protected prototype_ `bool IsEdit() const;`
- L55 _protected prototype_ `FReply OnCreateButtonClick(const bool bInApply);`
- L56 _protected prototype_ `FReply OnSaveButtonClick();`
- L57 _protected prototype_ `FReply OnDeleteButtonClick();`
- L58 _protected prototype_ `FReply OnCancelButtonClick();`
- L60 _protected prototype_ `void HandleWindowClosed(const TSharedRef<SWindow>& InWindow);`
- L62 _protected member_ `FOnNavigationToolTryCreateFilter OnTryCreateFilter;`
- L63 _protected member_ `FOnNavigationToolTryModifyFilter OnTryModifyFilter;`
- L64 _protected member_ `FOnNavigationToolTryDeleteFilter OnTryDeleteFilter;`
- L66 _protected member_ `TSharedPtr<SEditableTextBox> FilterLabelTextBox;`
- L68 _protected member_ `FCustomTextFilterData InitialCustomTextFilterData;`
- L69 _protected member_ `FCustomTextFilterData CustomTextFilterData;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L12 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnNavigationToolTryCreateFilter , const FCustomTextFilterData& , const FString& , const bool , FText& );`
- L12 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnNavigationToolTryCreateFilter , const FCustomTextFilterData& , const FString& , const bool , FText& );` (scope `UE::SequenceNavigator`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnNavigationToolTryModifyFilter , const FCustomTextFilterData& , const FString& , FText& );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnNavigationToolTryModifyFilter , const FCustomTextFilterData& , const FString& , FText& );` (scope `UE::SequenceNavigator`)
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnNavigationToolTryDeleteFilter , const FString& , FText& );`
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnNavigationToolTryDeleteFilter , const FString& , FText& );` (scope `UE::SequenceNavigator`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolExpanderArrow.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolExpanderArrow`  
`class SNavigationToolExpanderArrow : public SExpanderArrow`  
_L12-34_
- inherits: `SExpanderArrow`
- L15 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolExpanderArrow)`
- L16 _public prototype_ `SLATE_ARGUMENT(SExpanderArrow::FArguments, ExpanderArrowArgs) SLATE_ATTRIBUTE(FLinearColor, WireTint) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<ITableRow>& InTableRow);`
- L24 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs , const FGeometry& InAllottedGeometry , const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const FWidgetStyle& InWidgetStyle , const bool bInParentEnabled) const override;`
- L33 _protected member_ `TAttribute<FLinearColor> WireTint;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolFilterBar.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolFilterBar`  
`class SNavigationToolFilterBar : public SCompoundWidget`  
_L24-136_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolFilterBar) : _FilterBarLayout(EFilterBarLayout::Vertical) , _FiltersMuted(false) , _CanChangeOrientation(true) , _FilterPillStyle(EFilterPillStyle::Default) , _UseSectionsForCategories(true)`
- L37 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SSequencerSearchBox>, FilterSearchBox) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(bool, FiltersMuted) SLATE_ARGUMENT(bool, CanChangeOrientation) SLATE_ARGUMENT(EFilterPillStyle, FilterPillStyle) SLATE_ARGUMENT(bool, UseSectionsForCategories) SLATE_END_ARGS() virtual ~SNavigationToolFilterBar() override;` — An SFilterSearchBox that can be attached to this filter bar. When provided along with a CreateTextFilter delegate, allows the user to save searches from the Search Box as text filters for the filter bar. NOTE: Will bind a delegate to SFilterSearchBox::OnClickedAddSearchHistoryButton
- L58 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<FNavigationToolFilterBar>& InWeakFilterBar);`
- L61 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L64 _public prototype_ `TSharedPtr<FNavigationToolFilterBar> GetFilterBar() const;`
- L66 _public prototype_ `void SetTextFilterString(const FString& InFilterString);`
- L68 _public prototype_ `FText GetFilterErrorText() const;`
- L70 _public prototype_ `EFilterBarLayout GetLayout() const;`
- L71 _public prototype_ `void SetLayout(const EFilterBarLayout InFilterBarLayout);`
- L73 _public prototype_ `void AttachFilterSearchBox(const TSharedPtr<SSequencerSearchBox>& InFilterSearchBox);`
- L75 _public prototype_ `bool HasAnyFilterWidgets() const;`
- L77 _public prototype_ `void CreateAddCustomTextFilterWindowFromSearch(const FText& InSearchText);`
- L79 _public prototype_ `TWeakPtr<SSequencerSearchBox> GetSearchBox() const;`
- L82 _public prototype_ `void SetMuted(bool bInMuted);` — Set the state of the filter bar. Muted means that the filters are muted, but the context menu is still enabled and accessible.
- L85 _protected prototype_ `void AddWidgetToLayout(const TSharedRef<SWidget>& InWidget);`
- L86 _protected prototype_ `void RemoveWidgetFromLayout(const TSharedRef<SWidget>& InWidget);`
- L88 _protected prototype_ `void CreateAndAddFilterWidget(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L89 _protected prototype_ `void AddFilterWidget(const TSharedRef<FNavigationToolFilter>& InFilter, const TSharedRef<SSequencerFilter>& InFilterWidget);`
- L90 _protected prototype_ `void RemoveFilterWidget(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L91 _protected prototype_ `void RemoveAllFilterWidgets();`
- L92 _protected prototype_ `void RemoveAllFilterWidgetsButThis(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L94 _protected prototype_ `UWorld* GetWorld() const;`
- L96 _protected prototype_ `void OnEnableAllGroupFilters(bool bEnableAll);`
- L97 _protected prototype_ `void OnNodeGroupFilterClicked(UMovieSceneNodeGroup* NodeGroup);`
- L99 _protected prototype_ `void CreateFilterWidgetsFromConfig();`
- L101 _protected prototype_ `TSharedRef<SWidget> OnWrapButtonClicked();`
- L103 _protected prototype_ `FText GetFilterDisplayName(const TSharedRef<FNavigationToolFilter> InFilter) const;`
- L104 _protected prototype_ `FSlateColor GetFilterBlockColor(const TSharedRef<FNavigationToolFilter> InFilter) const;`
- L106 _protected prototype_ `void OnFilterToggle(const ECheckBoxState InNewState, const TSharedRef<FNavigationToolFilter> InFilter);`
- L107 _protected prototype_ `void OnFilterCtrlClick(const TSharedRef<FNavigationToolFilter> InFilter);`
- L108 _protected prototype_ `void OnFilterAltClick(const TSharedRef<FNavigationToolFilter> InFilter);`
- L109 _protected prototype_ `void OnFilterMiddleClick(const TSharedRef<FNavigationToolFilter> InFilter);`
- L110 _protected prototype_ `void OnFilterDoubleClick(const TSharedRef<FNavigationToolFilter> InFilter);`
- L112 _protected prototype_ `TSharedRef<SWidget> OnGetMenuContent(const TSharedRef<FNavigationToolFilter> InFilter);`
- L114 _protected prototype_ `void ActivateAllButThis(const bool bInActive, const TSharedRef<FNavigationToolFilter> InFilter);`
- L116 _protected prototype_ `void OnFiltersChanged(const ENavigationToolFilterChange InChangeType, const TSharedRef<FNavigationToolFilter>& InFilter);`
- L118 _protected member_ `TWeakPtr<FNavigationToolFilterBar> WeakFilterBar;`
- L120 _protected member_ `TWeakPtr<SSequencerSearchBox> WeakSearchBox;`
- L122 _protected member_ `TSharedPtr<SWidgetSwitcher> FilterBoxWidget;`
- L123 _protected member_ `TSharedPtr<SFilterBarClippingHorizontalBox> HorizontalContainerWidget;`
- L124 _protected member_ `TSharedPtr<SScrollBox> VerticalContainerWidget;`
- L126 _protected member_ `EFilterBarLayout FilterBarLayout = EFilterBarLayout::Vertical;`
- L127 _protected member_ `bool bCanChangeOrientation = true;`
- L128 _protected member_ `EFilterPillStyle FilterPillStyle = EFilterPillStyle::Default;`
- L130 _protected member_ `TMap<TSharedRef<FNavigationToolFilter>, TSharedRef<SSequencerFilter>> FilterWidgets;`
- L132 _protected member_ `TSharedPtr<SFilterExpressionHelpDialog> TextExpressionHelpDialog;`
- L134 _protected member_ `TSharedPtr<FNavigationToolFilterBarContextMenu> ContextMenu;`
- L135 _protected member_ `TSharedPtr<FNavigationToolFilterContextMenu> FilterContextMenu;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolItemColumns.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolItemColumns`  
`class SNavigationToolItemColumns : public SCompoundWidget`  
_L18-67_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolItemColumns)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FNavigationToolView>& InToolView);`
- L28 _public prototype_ `void AddItemSlot(const TSharedPtr<INavigationToolColumn>& InColumn);`
- L30 _public prototype_ `void OnToolLoaded();`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L33 _public prototype_ `FSlateColor GetItemStateColor(TSharedPtr<INavigationToolColumn> InColumn) const;`
- L35 _public prototype_ `ECheckBoxState IsChecked(TSharedPtr<INavigationToolColumn> InColumn) const;`
- L36 _public prototype_ `void OnCheckBoxStateChanged(const ECheckBoxState InNewCheckState, const TSharedPtr<INavigationToolColumn> InColumn) const;`
- L38 _public prototype_ `float GetExpandItemsLerp() const;`
- L39 _public prototype_ `void OnExpandItemsChanged(const FNavigationToolView& InToolView);`
- L41 _public prototype_ `FReply ToggleShowItemColumns();`
- L43 _public prototype_ `FReply ShowAll();`
- L44 _public prototype_ `FReply HideAll();`
- L47 _protected prototype_ `FText GetItemMenuButtonToolTip() const;`
- L49 _protected member_ `TWeakPtr<FNavigationToolView> WeakToolView;`
- L51 _protected member_ `TSharedPtr<SBox> ItemBox;`
- L53 _protected member_ `TSharedPtr<SScrollBox> ItemScrollBox;`
- L55 _protected member_ `TMap<FName, TSharedPtr<SWidget>> ItemSlots;`
- L57 _protected member_ `FCurveSequence ExpandCurveSequence;`
- L60 _protected member_ `float ItemBoxTargetHeight = 0.f;` — Target Height of the Item Filter Box when playing the sequence
- L63 _protected member_ `bool bItemsExpanded = false;` — Whether to expand and show the Item Filter List
- L66 _protected member_ `bool bPlayedSequenceLastTick = true;` — The cached state of Expand Filters Sequence, to know when states have changed. Default to true so that we run it at the start

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolTreeView.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolTreeView`  
`class SNavigationToolTreeView : public STreeView<FNavigationToolViewModelWeakPtr>`  
_L14-52_
- inherits: `STreeView<FNavigationToolViewModelWeakPtr>`
- L18 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolTreeView)`
- L19 _public prototype_ `SLATE_ARGUMENT(STreeView<FNavigationToolViewModelWeakPtr>::FArguments, TreeViewArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FNavigationToolView>& InToolView);`
- L24 _public prototype_ `int32 GetItemIndex(const FNavigationToolViewModelWeakPtr& InWeakItem) const;`
- L26 _public prototype_ `void FocusOnItem(const FNavigationToolViewModelWeakPtr& InWeakItem);`
- L28 _public prototype_ `void UpdateItemExpansions(const FNavigationToolViewModelWeakPtr& InWeakItem);`
- L31 _public prototype_ `virtual void Private_UpdateParentHighlights() override;`
- L35 _public prototype_ `virtual void Private_SetItemSelection(const FNavigationToolViewModelWeakPtr InWeakItem , const bool bInShouldBeSelected, const bool bInWasUserDirected = false) override;`
- L37 _public prototype_ `virtual void Private_SignalSelectionChanged(const ESelectInfo::Type InSelectInfo) override;`
- L38 _public prototype_ `virtual void Private_ClearSelection() override;`
- L42 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) const override;`
- L43 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L44 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L45 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L49 _protected member_ `TWeakPtr<FNavigationToolView> WeakToolView;`
- L51 _protected member_ `TItemSet PreviousSelectedItems;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/SNavigationToolView.h` (Private)


#### class `UE::SequenceNavigator::SNavigationToolView`  
`class SNavigationToolView : public SCompoundWidget`  
_L27-112_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolView)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FNavigationToolView>& InToolView);`
- L35 _public function_ `TSharedPtr<SNavigationToolTreeView> GetTreeView() const`
- L38 _public prototype_ `void RebuildWidget(const bool bInReconstructColumns = false);` — Rebuilds the entire widget. Needs to be called when the filter bar layout changes.
- L40 _public prototype_ `void ReconstructColumns();`
- L42 _public prototype_ `bool IsColumnVisible(const FName InColumnId) const;`
- L43 _public prototype_ `void ShowHideColumn(const FName InColumnId, const bool bInVisible);`
- L45 _public prototype_ `void SetColumnWidth(const FName InColumnId, const float InWidth);`
- L47 _public prototype_ `void RequestTreeRefresh();`
- L49 _public prototype_ `void SetItemSelection(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const bool bInSignalSelectionChange);`
- L52 _public prototype_ `void OnItemSelectionChanged(const FNavigationToolViewModelWeakPtr InWeakItem , const ESelectInfo::Type InSelectionType);`
- L55 _public prototype_ `void ScrollItemIntoView(const FNavigationToolViewModelWeakPtr& InWeakItem) const;`
- L57 _public prototype_ `bool IsItemExpanded(const FNavigationToolViewModelWeakPtr& InWeakItem) const;`
- L58 _public prototype_ `void SetItemExpansion(const FNavigationToolViewModelWeakPtr& InWeakItem, const bool bInExpand) const;`
- L60 _public prototype_ `void UpdateItemExpansions(const FNavigationToolViewModelWeakPtr& InWeakItem) const;`
- L62 _public prototype_ `TSharedRef<ITableRow> OnItemGenerateRow(const FNavigationToolViewModelWeakPtr InWeakItem , const TSharedRef<STableViewBase>& InOwnerTable);`
- L65 _public prototype_ `void SetKeyboardFocus() const;`
- L68 _public prototype_ `virtual void OnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L69 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L70 _public prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L71 _public prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L72 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L75 _public prototype_ `void SetTreeBorderVisibility(const bool bInVisible);`
- L77 _public prototype_ `void GenerateColumnState(const FName InColumnId, FNavigationToolViewColumnSaveState& OutColumnState);`
- L78 _public prototype_ `void GenerateColumnStateMap(TMap<FName, FNavigationToolViewColumnSaveState>& OutStateMap);`
- L80 _public prototype_ `EFilterBarLayout GetFilterBarLayout() const;`
- L81 _public prototype_ `void SetFilterBarLayout(const EFilterBarLayout InLayout);`
- L84 _protected prototype_ `TSharedRef<SWidget> ConstructSplitterContent();`
- L85 _protected prototype_ `TSharedRef<SWidget> ConstructMainContent();`
- L87 _protected prototype_ `void RebuildSearchAndFilterRow();`
- L89 _protected prototype_ `void OnFilterActivationChanged();`
- L90 _protected prototype_ `void OnFilterVisibilityChanged(bool bInIsVisible);`
- L91 _protected prototype_ `void OnFilterLayoutChanged(EFilterBarLayout InLayout);`
- L92 _protected prototype_ `void OnFiltersChanged(const ENavigationToolFilterChange InChangeType, const TSharedRef<FNavigationToolFilter>& InFilter);`
- L94 _protected prototype_ `TSharedPtr<FNavigationToolFilterBar> GetFilterBar() const;`
- L96 _protected member_ `TWeakPtr<FNavigationToolView> WeakToolView;`
- L98 _protected member_ `TSharedPtr<FNavigationToolToolbarMenu> ToolbarMenu;`
- L100 _protected member_ `TSharedPtr<SVerticalBox> SearchAndFilterRow;`
- L101 _protected member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L102 _protected member_ `TSharedPtr<SBorder> TreeBorder;`
- L103 _protected member_ `TSharedPtr<SNavigationToolTreeView> TreeView;`
- L104 _protected member_ `TSharedPtr<SNavigationToolFilterBar> FilterBarWidget;`
- L107 _protected member_ `bool bIsEnterLastKeyPressed = false;` — If true the SuggestionList shouldn't appear since we selected what we wanted
- L109 _protected member_ `bool bSelectingItems = false;`
- L111 _protected member_ `TSet<TWeakPtr<FNavigationToolItemDragDropOp>> ItemDragDropOps;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Private/Widgets/Styling/NavigationToolStyleUtils.h` (Private)


#### enum `UE::SequenceNavigator::EStyleType`  
`enum class EStyleType`  
_L15-20_
- L17 _public enumerator_ `Normal`
- L18 _public enumerator_ `Hovered`
- L19 _public enumerator_ `Pressed`

#### struct `UE::SequenceNavigator::FStyleUtils`  
`struct FStyleUtils`  
_L22-31_
- L24 _public prototype_ `static const FToolBarStyle& GetSlimToolBarStyle();`
- L26 _public prototype_ `static const FSlateBrush& GetBrush(EStyleType InStyleType, bool bIsSelected);`
- L28 _public prototype_ `static FSlateColor GetColor(EStyleType InStyleType, bool bIsSelected);`
- L30 _public prototype_ `static FSlateColorBrush GetColorBrush(EStyleType InStyleType, bool bIsSelected);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L33 _prototype_ `const FButtonStyle& GetFilterItemMenuButtonStyle();` (scope `UE::SequenceNavigator`)
- L34 _prototype_ `const FCheckBoxStyle& GetFilterItemCheckboxStyle();` (scope `UE::SequenceNavigator`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/INavigationToolColumn.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolColumn`  
`class INavigationToolColumn`  
_L16-46_
- L23 _public prototype_ `virtual FName GetColumnId() const = 0;`
- L25 _public prototype_ `virtual FText GetColumnDisplayNameText() const = 0;`
- L27 _public function_ `virtual const FSlateBrush* GetIconBrush() const`
- L29 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InToolView, const float InFillSize) = 0;`
- L31 _public function_ `virtual float GetFillWidth() const`
- L37 _public function_ `virtual bool ShouldShowColumnByDefault() const` — Determines whether the Column should be Showing by Default while still be able to toggle it on/off. Used when calling SHeaderRow::SetShowGeneratedColumn (requires ShouldGenerateWidget to not be set).
- L39 _public function_ `virtual bool CanHideColumn(const FName InColumnId) const`
- L41 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) = 0;`
- L45 _public function_ `virtual void Tick(const float InDeltaTime)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolColorColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolColorColumn`  
`class FNavigationToolColorColumn : public FNavigationToolColumn`  
_L16-35_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView, const float InFillSize) override;`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolColumn`  
`class FNavigationToolColumn : public Sequencer::FViewModel , public INavigationToolColumn`  
_L14-21_
- inherits: `Sequencer::FViewModel,INavigationToolColumn`
- desc: Base Navigation Tool Column to extend from

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolColumnExtender.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolColumnExtender`  
`class FNavigationToolColumnExtender`  
_L26-59_
- desc: Extension Class to add Navigation Tool Columns Example #1: This would create a Tag Column at the end of the current column list (order matters!) ColumnExtender.AddColumn<FNavigationToolTagColumn>(); Example #2: This would create a Tag Column before the Label Column (if it doesn't exist, it's the same behavior as the above example) ColumnExtender.AddColumn<FNavigationToolTagColumn, ENavigationToolExtensionPosition::Before, FNavigationToolLabelColumn>();
- L31 _public function_ `void AddColumn()`
- L43 _public function_ `void AddColumn(const TSharedPtr<FNavigationToolColumn>& InNewColumn , const ENavigationToolExtensionPosition InPosition = ENavigationToolExtensionPosition::After)`
- L49 _public function_ `const TArray<TSharedPtr<FNavigationToolColumn>>& GetColumns() const`
- L52 _private prototype_ `void AddColumn(const TSharedPtr<FNavigationToolColumn>& InColumn , const ENavigationToolExtensionPosition InExtensionPosition , const FName InReferenceColumnId);`
- L56 _private prototype_ `int32 FindColumnIndex(const FName InColumnId) const;`
- L58 _private member_ `TArray<TSharedPtr<FNavigationToolColumn>> Columns;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolCommentColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolCommentColumn`  
`class FNavigationToolCommentColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolDeactiveStateColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolDeactiveStateColumn`  
`class FNavigationToolDeactiveStateColumn : public FNavigationToolColumn`  
_L16-37_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L32 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolHBiasColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolHBiasColumn`  
`class FNavigationToolHBiasColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolIdColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolIdColumn`  
`class FNavigationToolIdColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolInTimeColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolInTimeColumn`  
`class FNavigationToolInTimeColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolItemsColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItemsColumn`  
`class FNavigationToolItemsColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolLabelColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolLabelColumn`  
`class FNavigationToolLabelColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L32 _protected function_ `virtual float GetFillWidth() const override`
- L33 _protected function_ `virtual bool CanHideColumn(const FName InColumnId) const override`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolLengthColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolLengthColumn`  
`class FNavigationToolLengthColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolLockColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolLockColumn`  
`class FNavigationToolLockColumn : public FNavigationToolColumn`  
_L16-37_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolMarkerVisibilityColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolMarkerVisibilityColumn`  
`class FNavigationToolMarkerVisibilityColumn : public FNavigationToolColumn`  
_L16-37_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L32 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolOutTimeColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolOutTimeColumn`  
`class FNavigationToolOutTimeColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolPlayheadColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolPlayheadColumn`  
`class FNavigationToolPlayheadColumn : public FNavigationToolColumn`  
_L16-37_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L32 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolRevisionControlColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolRevisionControlColumn`  
`class FNavigationToolRevisionControlColumn : public FNavigationToolColumn`  
_L16-37_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L32 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L33 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolStartFrameOffsetColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolStartFrameOffsetColumn`  
`class FNavigationToolStartFrameOffsetColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Columns/NavigationToolTakeColumn.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolTakeColumn`  
`class FNavigationToolTakeColumn : public FNavigationToolColumn`  
_L16-38_
- inherits: `FNavigationToolColumn`
- L23 _public function_ `static FName StaticColumnId()`
- L27 _protected function_ `virtual FName GetColumnId() const override`
- L28 _protected prototype_ `virtual FText GetColumnDisplayNameText() const override;`
- L29 _protected prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L30 _protected function_ `virtual bool ShouldShowColumnByDefault() const override`
- L31 _protected function_ `virtual float GetFillWidth() const override`
- L32 _protected prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn(const TSharedRef<INavigationToolView>& InView , const float InFillSize) override;`
- L34 _protected prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(const FNavigationToolViewModelPtr& InItem , const TSharedRef<INavigationToolView>& InView , const TSharedRef<SNavigationToolTreeRow>& InRow) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Customization/INavigationToolIconCustomization.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolIconCustomization`  
`class INavigationToolIconCustomization`  
_L16-26_
- L19 _public prototype_ `virtual ~INavigationToolIconCustomization() = default;`
- L21 _public prototype_ `virtual FName GetToolItemIdentifier() const = 0;`
- L23 _public prototype_ `virtual bool HasOverrideIcon(const FNavigationToolViewModelPtr& InItem) const = 0;`
- L25 _public prototype_ `virtual FSlateIcon GetOverrideIcon(const FNavigationToolViewModelPtr& InItem) const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/DragDropOps/Handlers/NavigationToolItemDropHandler.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItemDropHandler`  
`class FNavigationToolItemDropHandler : public Sequencer::FViewModel`  
_L25-84_
- inherits: `Sequencer::FViewModel`
- desc: Base Class to Handle Dropping Navigation Tool Items into a Target Navigation Tool Item @see built-in example FNavigationToolActorDropHandler
- L33 _public function_ `TConstArrayView<FNavigationToolViewModelWeakPtr> GetItems() const`
- L41 _protected prototype_ `void Initialize(const FNavigationToolItemDragDropOp& InDragDropOp);`
- L43 _protected prototype_ `virtual bool IsDraggedItemSupported(const FNavigationToolViewModelPtr& InDraggedItem) const = 0;`
- L45 _protected prototype_ `virtual TOptional<EItemDropZone> CanDrop(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) const = 0;`
- L47 _protected prototype_ `virtual bool Drop(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) = 0;`
- L55 _protected function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, INavigationToolItem>::Value>::Type> void ForEachItem(const TFunctionRef<EIterationResult(InItemType&)>& InFunc) const`
- L81 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakItems;`
- L83 _protected member_ `ENavigationToolDragDropActionType ActionType = ENavigationToolDragDropActionType::Move;`

#### enum `UE::SequenceNavigator::FNavigationToolItemDropHandler::EIterationResult`  
`enum class EIterationResult`  
_L49-53_
- L51 _public enumerator_ `Continue`
- L52 _public enumerator_ `Break`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/DragDropOps/NavigationToolItemDragDropOp.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItemDragDropOp`  
`class FNavigationToolItemDragDropOp : public FDecoratedDragDropOp`  
_L18-68_
- inherits: `FDecoratedDragDropOp`
- desc: Drag Drop Operation for Navigation Tool Items. Customized behavior can be added in via the AddDropHandler function
- L21 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FNavigationToolItemDragDropOp, FDecoratedDragDropOp) static TSharedRef<FNavigationToolItemDragDropOp> New(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const TSharedPtr<FNavigationToolView>& InToolView , const ENavigationToolDragDropActionType InActionType);`
- L27 _public function_ `TSharedPtr<INavigationToolView> GetToolView() const`
- L32 _public function_ `TConstArrayView<FNavigationToolViewModelWeakPtr> GetItems() const`
- L37 _public function_ `ENavigationToolDragDropActionType GetActionType() const`
- L45 _public function_ `void AddDropHandler(InArgTypes&&... InArgs)`
- L52 _public prototype_ `FReply Drop(EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem);`
- L54 _public prototype_ `TOptional<EItemDropZone> CanDrop(const EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) const;`
- L57 _protected prototype_ `void Init(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const TSharedPtr<FNavigationToolView>& InToolView , const ENavigationToolDragDropActionType InActionType);`
- L61 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakItems;`
- L63 _protected member_ `TArray<TSharedRef<FNavigationToolItemDropHandler>> DropHandlers;`
- L65 _protected member_ `TWeakPtr<INavigationToolView> WeakToolView;`
- L67 _protected member_ `ENavigationToolDragDropActionType ActionType = ENavigationToolDragDropActionType::Move;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IColorExtension.h` (Public)


#### class `UE::SequenceNavigator::IColorExtension`  
`class IColorExtension`  
_L13-23_
- L20 _public prototype_ `virtual TOptional<FColor> GetColor() const = 0;`
- L22 _public prototype_ `virtual void SetColor(const TOptional<FColor>& InColor) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IIdExtension.h` (Public)


#### class `UE::SequenceNavigator::IIdExtension`  
`class IIdExtension`  
_L13-21_
- L20 _public prototype_ `virtual FText GetId() const = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IInTimeExtension.h` (Public)


#### class `UE::SequenceNavigator::IInTimeExtension`  
`class IInTimeExtension`  
_L13-23_
- L20 _public prototype_ `virtual FFrameNumber GetInTime() const = 0;`
- L22 _public prototype_ `virtual void SetInTime(const FFrameNumber& InTime) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IMarkerVisibilityExtension.h` (Public)


#### enum `UE::SequenceNavigator::EItemMarkerVisibility`  
`enum class EItemMarkerVisibility`  
_L12-17_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Visible = 1 << 0`
- L16 _public enumerator_ `PartiallyVisible = 1 << 1`

#### class `UE::SequenceNavigator::IMarkerVisibilityExtension`  
`class IMarkerVisibilityExtension`  
_L20-30_
- L27 _public prototype_ `virtual EItemMarkerVisibility GetMarkerVisibility() const = 0;`
- L29 _public prototype_ `virtual void SetMarkerVisibility(const bool bInVisible) = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IOutTimeExtension.h` (Public)


#### class `UE::SequenceNavigator::IOutTimeExtension`  
`class IOutTimeExtension`  
_L13-23_
- L20 _public prototype_ `virtual FFrameNumber GetOutTime() const = 0;`
- L22 _public prototype_ `virtual void SetOutTime(const FFrameNumber& InTime) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IPlayheadExtension.h` (Public)


#### enum `UE::SequenceNavigator::EItemContainsPlayhead`  
`enum class EItemContainsPlayhead`  
_L12-17_
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `ContainsPlayhead = 1 << 0`
- L16 _public enumerator_ `PartiallyContainsPlayhead = 1 << 1`

#### class `UE::SequenceNavigator::IPlayheadExtension`  
`class IPlayheadExtension`  
_L20-28_
- L27 _public prototype_ `virtual EItemContainsPlayhead ContainsPlayhead() const = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Extensions/IRevisionControlExtension.h` (Public)


#### enum `UE::SequenceNavigator::EItemRevisionControlState`  
`enum class EItemRevisionControlState`  
_L17-22_
- L19 _public enumerator_ `None = 0`
- L20 _public enumerator_ `SourceControlled = 1 << 0`
- L21 _public enumerator_ `PartiallySourceControlled = 1 << 1`

#### class `UE::SequenceNavigator::IRevisionControlExtension`  
`class IRevisionControlExtension`  
_L25-59_
- L30 _public function_ `IRevisionControlExtension(const UObject* const InObject)`
- L34 _public prototype_ `virtual ~IRevisionControlExtension() = default;`
- L36 _public prototype_ `virtual EItemRevisionControlState GetRevisionControlState() const = 0;`
- L38 _public prototype_ `virtual const FSlateBrush* GetRevisionControlStatusIcon() const = 0;`
- L40 _public prototype_ `virtual FText GetRevisionControlStatusText() const = 0;`
- L42 _public function_ `static void QueueRevisionControlStatusUpdate(const UObject* const InObject)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolBuiltInFilterParams.h` (Public)


#### struct `FNavigationToolBuiltInFilterParams`  
`struct FNavigationToolBuiltInFilterParams`  
_L15-99_
- reflection: `USTRUCT()`
- L19 _public prototype_ `static FNavigationToolBuiltInFilterParams CreateSequenceFilter();`
- L20 _public prototype_ `static FNavigationToolBuiltInFilterParams CreateTrackFilter();`
- L21 _public prototype_ `static FNavigationToolBuiltInFilterParams CreateBindingFilter();`
- L22 _public prototype_ `static FNavigationToolBuiltInFilterParams CreateMarkerFilter();`
- L24 _public prototype_ `FNavigationToolBuiltInFilterParams() = default;`
- L26 _public prototype_ `FNavigationToolBuiltInFilterParams(const FName InFilterId , const TSet<UE::Sequencer::FViewModelTypeID>& InItemClasses , const TArray<TSubclassOf<UObject>>& InFilterClasses , const ENavigationToolFilterMode InMode = ENavigationToolFilterMode::MatchesType , const FSlateBrush* const InIconBrush = nullptr , const FText& InDisplayName = FText::GetEmpty() , const FText& InTooltipText = FText::GetEmpty() , const TSharedPtr<FUICommandInfo>& InToggleCommand = nullptr , const bool InEnabledByDefault = true , const EClassFlags InRequiredClassFlags = CLASS_None , const EClassFlags InRestrictedClassFlags = CLASS_None);`
- L38 _public prototype_ `bool HasValidFilterData() const;`
- L40 _public prototype_ `FName GetFilterId() const;`
- L42 _public prototype_ `FText GetDisplayName() const;`
- L44 _public prototype_ `FText GetTooltipText() const;`
- L46 _public prototype_ `const FSlateBrush* GetIconBrush() const;`
- L48 _public prototype_ `ENavigationToolFilterMode GetFilterMode() const;`
- L50 _public prototype_ `bool IsEnabledByDefault() const;`
- L52 _public prototype_ `TSharedPtr<FUICommandInfo> GetToggleCommand() const;`
- L54 _public prototype_ `void SetOverrideIconColor(const FSlateColor& InNewIconColor);`
- L56 _public prototype_ `bool IsValidItemClass(const UE::Sequencer::FViewModelTypeID& InClassTypeId) const;`
- L57 _public prototype_ `bool IsValidObjectClass(const UClass* const InClass) const;`
- L59 _public prototype_ `void SetFilterText(const FText& InText);`
- L61 _public prototype_ `bool PassesFilterText(const UE::SequenceNavigator::FNavigationToolViewModelPtr& InItem) const;`
- L65 _private member_ `FName FilterId = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L67 _private member_ `TSet<UE::Sequencer::FViewModelTypeID> ItemClasses;`
- L70 _private member_ `TArray<TSubclassOf<UObject>> ObjectClasses;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L73 _private member_ `ENavigationToolFilterMode FilterMode = ENavigationToolFilterMode::MatchesType;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L76 _private member_ `FText FilterText;` — `UPROPERTY(EditAnywhere, Category = "Filter|Advanced")`
- L79 _private member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L82 _private member_ `FText TooltipText;` — `UPROPERTY(EditAnywhere, Category = "Filter")`
- L85 _private member_ `FSlateBrush OverrideIcon;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta=(EditCondition="bUseOverrideIcon"))`
- L88 _private member_ `bool bUseOverrideIcon = true;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta=(InlineEditConditionToggle))`
- L91 _private member_ `bool bEnabledByDefault = true;` — `UPROPERTY(EditAnywhere, Category = "Filter", meta=(InlineEditConditionToggle))`
- L93 _private member_ `TSharedPtr<FUICommandInfo> ToggleCommand;`
- L95 _private member_ `const FSlateBrush* IconBrush = nullptr;`
- L97 _private member_ `EClassFlags RequiredClassFlags = CLASS_None;`
- L98 _private member_ `EClassFlags RestrictedClassFlags = CLASS_None;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilterBase.h` (Public)


#### enum `ENavigationToolFilterMode`  
`enum class ENavigationToolFilterMode : uint8`  
_L17-26_
- reflection: `UENUM()`
- L19 _public enumerator_ `None = 0`
- L22 _public enumerator_ `MatchesType = 1 << 0` — Navigation Tool Item type matches the Filter Type
- L25 _public enumerator_ `ContainerOfType = 1 << 1` — Navigation Tool Item contains an item (as a descendant/child) of that type

#### class `UE::SequenceNavigator::FNavigationToolFilter`  
`class FNavigationToolFilter : public FSequencerFilterBase<FNavigationToolViewModelPtr>`  
_L32-44_
- inherits: `FSequencerFilterBase<FNavigationToolViewModelPtr>`
- L35 _public prototype_ `FNavigationToolFilter(INavigationToolFilterBar& InOutFilterInterface, TSharedPtr<FFilterCategory>&& InCategory = nullptr);`
- L38 _public function_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override`
- L42 _public prototype_ `virtual INavigationToolFilterBar& GetFilterInterface() const override;`

#### class `UE::SequenceNavigator::FNavigationToolFilter_ItemType`  
`template<typename InItemType> class FNavigationToolFilter_ItemType : public FNavigationToolFilter`  
_L51-64_
- inherits: `FNavigationToolFilter`
- desc: Base filter for filtering items based on their item class
- L54 _public function_ `FNavigationToolFilter_ItemType(INavigationToolFilterBar& InOutFilterInterface, TSharedPtr<FFilterCategory> InCategory) : FNavigationToolFilter(InOutFilterInterface, MoveTemp(InCategory))`
- L59 _public function_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L27 _prototype_ `ENUM_CLASS_FLAGS(ENavigationToolFilterMode);`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilterCollection.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilterCollection`  
`class FNavigationToolFilterCollection : public TFilterCollection<FNavigationToolViewModelPtr>`  
_L18-95_
- inherits: `TFilterCollection<FNavigationToolViewModelPtr>`
- desc: Some of this classes functionality could be moved to the TFilterCollection base class so other places could take advantage
- L21 _public prototype_ `FNavigationToolFilterCollection(ISequencerFilterBar& InFilterInterface);`
- L24 _public prototype_ `bool ContainsFilter(const TSharedRef<FNavigationToolFilter>& InItem) const;` — @todo Maybe this should get moved in to TFilterCollection
- L27 _public prototype_ `void RemoveAll();` — @todo Maybe this should get moved in to TFilterCollection
- L36 _public prototype_ `int32 Add(const TSharedRef<FNavigationToolFilter>& InFilter);` — Adds the specified Filter to the collection @param InFilter The filter object to add to the collection @return The index in the collection at which the filter was added
- L45 _public prototype_ `int32 Remove(const TSharedRef<FNavigationToolFilter>& InFilter);` — Removes as many instances of the specified Filter as there are in the collection @param InFilter The filter object to remove from the collection @return The number of Filters removed from the collection
- L54 _public prototype_ `TSharedRef<FNavigationToolFilter> GetFilterAtIndex(const int32 InIndex);` — Gets the filter at the specified index @param InIndex The index of the requested filter in the ChildFilters array @return Filter at the specified index
- L57 _public prototype_ `int32 Num() const;` — Returns the number of Filters in the collection
- L59 _public prototype_ `bool IsEmpty() const;`
- L62 _public prototype_ `void Sort();` — Sorts the filters by display string
- L65 _public prototype_ `TArray<FText> GetFilterDisplayNames() const;` — Gets all the available track filter names
- L67 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter>> GetAllFilters(const TArray<TSharedRef<FFilterCategory>>& InCategories = {}) const;`
- L69 _public prototype_ `TSet<TSharedRef<FFilterCategory>> GetCategories(const TSet<TSharedRef<FNavigationToolFilter>>* InFilters = nullptr) const;`
- L72 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter>> GetCategoryFilters(const TSharedRef<FFilterCategory>& InCategory) const;` — @return List of filters that match the specified category
- L74 _public prototype_ `void ForEachFilter(const TFunctionRef<bool(const TSharedRef<FNavigationToolFilter>&)>& InFunction , const TArray<TSharedRef<FFilterCategory>>& InCategories = {}) const;`
- L82 _protected prototype_ `void OnChildFilterChanged();` — Called when a child filter restrictions change and broadcasts the FilterChanged delegate for the collection
- L84 _protected member_ `ISequencerFilterBar& FilterInterface;`
- L91 _public function_ `inline TArray<TSharedPtr<IFilter<FNavigationToolViewModelPtr>>>::RangedForIteratorType begin()` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L92 _public function_ `inline TArray<TSharedPtr<IFilter<FNavigationToolViewModelPtr>>>::RangedForConstIteratorType begin() const`
- L93 _public function_ `inline TArray<TSharedPtr<IFilter<FNavigationToolViewModelPtr>>>::RangedForIteratorType end()`
- L94 _public function_ `inline TArray<TSharedPtr<IFilter<FNavigationToolViewModelPtr>>>::RangedForConstIteratorType end() const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilterExtension.h` (Public)


#### class `UNavigationToolFilterExtension`  
`class UNavigationToolFilterExtension : public UObject`  
_L19-34_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Derive from this class to make additional filters available in the Navigation Tool.
- L30 _public function_ `virtual void AddFilterExtensions(UE::SequenceNavigator::INavigationToolFilterBar& InOutFilterInterface , const TSharedRef<FFilterCategory>& InPreferredCategory , TArray<TSharedRef<UE::SequenceNavigator::FNavigationToolFilter>>& InOutFilterList) const` — Override to add additional Navigation Tool filters. @param InOutFilterInterface The filter interface to extend @param InPreferredCategory  The preferred filter bar category to place any newly added filters to, but can be any category @param InOutFilterList      Filter list to add additional filters to

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_CustomText.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_CustomText`  
`class FNavigationToolFilter_CustomText : public ICustomTextFilter<FNavigationToolViewModelPtr>, public FNavigationToolFilter_Text`  
_L14-47_
- inherits: `ICustomTextFilter<FNavigationToolViewModelPtr>,FNavigationToolFilter_Text`
- L19 _public prototype_ `FNavigationToolFilter_CustomText(INavigationToolFilterBar& InFilterInterface);`
- L22 _public prototype_ `virtual void SetFromCustomTextFilterData(const FCustomTextFilterData& InFilterData) override;`
- L23 _public prototype_ `virtual FCustomTextFilterData CreateCustomTextFilterData() const override;`
- L24 _public prototype_ `virtual TSharedPtr<FFilterBase<FNavigationToolViewModelPtr>> GetFilter() override;`
- L28 _public prototype_ `virtual bool IsCustomTextFilter() const override;`
- L29 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L30 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L34 _public prototype_ `virtual FText GetDisplayName() const override;`
- L35 _public prototype_ `virtual FText GetToolTipText() const override;`
- L36 _public prototype_ `virtual FLinearColor GetColor() const override;`
- L40 _public prototype_ `virtual FString GetName() const override;`
- L44 _protected member_ `FText DisplayName = FText::GetEmpty();`
- L46 _protected member_ `FLinearColor Color = FLinearColor::White;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_Dirty.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Dirty`  
`class FNavigationToolFilter_Dirty : public FNavigationToolFilter`  
_L11-35_
- inherits: `FNavigationToolFilter`
- L14 _public function_ `static FString StaticName()`
- L16 _public prototype_ `FNavigationToolFilter_Dirty(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L19 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L20 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L29 _public prototype_ `virtual FString GetName() const override;`
- L30 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`
- L34 _protected prototype_ `static bool IsObjectPackageDirty(const UObject* const InObject);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_Marks.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Marks`  
`class FNavigationToolFilter_Marks : public FNavigationToolFilter`  
_L11-32_
- inherits: `FNavigationToolFilter`
- L14 _public function_ `static FString StaticName()`
- L16 _public prototype_ `FNavigationToolFilter_Marks(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L19 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L20 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L29 _public prototype_ `virtual FString GetName() const override;`
- L30 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_Playhead.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Playhead`  
`class FNavigationToolFilter_Playhead : public FNavigationToolFilter`  
_L11-53_
- inherits: `FNavigationToolFilter`
- L14 _public function_ `static FString StaticName()`
- L16 _public prototype_ `FNavigationToolFilter_Playhead(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L20 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L21 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L22 _public prototype_ `virtual void ActiveStateChanged(const bool bInActive) override;`
- L26 _public prototype_ `virtual FText GetDisplayName() const override;`
- L27 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L31 _public prototype_ `virtual FString GetName() const override;`
- L32 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`
- L36 _protected prototype_ `void BindEvents();`
- L37 _protected prototype_ `void UnbindEvents();`
- L39 _protected prototype_ `void OnPlayEvent();`
- L40 _protected prototype_ `void OnStopEvent();`
- L42 _protected prototype_ `void OnBeginScrubbingEvent();`
- L43 _protected prototype_ `void OnEndScrubbingEvent();`
- L45 _protected prototype_ `FTimerManager* GetTimerManager() const;`
- L47 _protected prototype_ `void StartRefreshTimer();`
- L48 _protected prototype_ `void StopRefreshTimer();`
- L50 _protected member_ `FTimerHandle TimerHandle;`
- L52 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_Text.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Text`  
`class FNavigationToolFilter_Text : public FNavigationToolFilter`  
_L17-54_
- inherits: `FNavigationToolFilter`
- L20 _public prototype_ `FNavigationToolFilter_Text(INavigationToolFilterBar& InFilterInterface);`
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`
- L24 _public prototype_ `virtual FText GetToolTipText() const override;`
- L28 _public prototype_ `virtual FString GetName() const override;`
- L29 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`
- L32 _public prototype_ `bool IsActive() const;`
- L34 _public prototype_ `FText GetRawFilterText() const;`
- L35 _public prototype_ `void SetRawFilterText(const FText& InFilterText);`
- L37 _public prototype_ `FText GetFilterErrorText() const;`
- L39 _public prototype_ `const FTextFilterExpressionEvaluator& GetTextFilterExpressionEvaluator() const;`
- L40 _public prototype_ `TArray<TSharedRef<ISequencerTextFilterExpressionContext>> GetTextFilterExpressionContexts() const;`
- L42 _public prototype_ `bool DoesTextFilterStringContainExpressionPair(const ISequencerTextFilterExpressionContext& InExpression) const;`
- L45 _protected prototype_ `static bool IsTokenKey(const FExpressionToken& InToken, const TSet<FName>& InKeys);`
- L46 _protected prototype_ `static bool IsTokenOperator(const FExpressionToken& InToken, const ESequencerTextFilterValueType InValueType);`
- L47 _protected prototype_ `static bool IsTokenValueValid(const FExpressionToken& InToken, const ESequencerTextFilterValueType InValueType);`
- L50 _protected member_ `FTextFilterExpressionEvaluator TextFilterExpressionEvaluator;` — Expression evaluator that can be used to perform complex text filter queries
- L53 _protected member_ `TArray<TSharedRef<FNavigationToolFilterTextExpressionContext>> TextFilterExpressionContexts;` — Transient context data, used when calling PassesFilter. Kept around to minimize re-allocations between multiple calls to PassesFilter

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilter_Unbound.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Unbound`  
`class FNavigationToolFilter_Unbound : public FNavigationToolFilter`  
_L11-32_
- inherits: `FNavigationToolFilter`
- L14 _public function_ `static FString StaticName()`
- L16 _public prototype_ `FNavigationToolFilter_Unbound(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L19 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L20 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L29 _public prototype_ `virtual FString GetName() const override;`
- L30 _public prototype_ `virtual bool PassesFilter(const FNavigationToolViewModelPtr InItem) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/Filters/NavigationToolFilters.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilter_Sequence`  
`class FNavigationToolFilter_Sequence : public FNavigationToolFilter_ItemType<FNavigationToolSequence>`  
_L17-38_
- inherits: `FNavigationToolFilter_ItemType<FNavigationToolSequence>`
- L20 _public function_ `static FString StaticName()`
- L22 _public prototype_ `FNavigationToolFilter_Sequence(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L25 _public function_ `virtual FString GetName() const override`
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L34 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L35 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L36 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* const InSequence) const override;`

#### class `UE::SequenceNavigator::FNavigationToolFilter_Track`  
`class FNavigationToolFilter_Track : public FNavigationToolFilter_ItemType<FNavigationToolTrack>`  
_L43-64_
- inherits: `FNavigationToolFilter_ItemType<FNavigationToolTrack>`
- L46 _public function_ `static FString StaticName()`
- L48 _public prototype_ `FNavigationToolFilter_Track(INavigationToolFilterBar& InFilterInterface, TSharedPtr<FFilterCategory> InCategory = nullptr);`
- L51 _public function_ `virtual FString GetName() const override`
- L55 _public prototype_ `virtual FText GetDisplayName() const override;`
- L56 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L60 _public prototype_ `virtual FText GetDefaultToolTipText() const override;`
- L61 _public prototype_ `virtual TSharedPtr<FUICommandInfo> GetToggleCommand() const override;`
- L62 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* const InSequence) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/INavigationToolFilterBar.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolFilterBar`  
`class INavigationToolFilterBar : public ISequencerFilterBar`  
_L17-44_
- inherits: `ISequencerFilterBar`
- L20 _public prototype_ `virtual ~INavigationToolFilterBar() override = default;`
- L22 _public prototype_ `virtual TSet<TSharedRef<FFilterCategory>> GetFilterCategories(const TSet<TSharedRef<FNavigationToolFilter>>* InFilters = nullptr) const = 0;`
- L24 _public prototype_ `virtual TArray<TSharedRef<FNavigationToolFilter>> GetCommonFilters(const TArray<TSharedRef<FFilterCategory>>& InCategories = {}) const = 0;`
- L26 _public prototype_ `virtual bool IsFilterEnabled(TSharedRef<FNavigationToolFilter> InFilter) const = 0;`
- L27 _public prototype_ `virtual bool SetFilterEnabled(const TSharedRef<FNavigationToolFilter> InFilter, const bool bInEnabled, const bool bInRequestFilterUpdate = true) = 0;`
- L29 _public prototype_ `virtual bool IsFilterActive(const TSharedRef<FNavigationToolFilter> InFilter) const = 0;`
- L30 _public prototype_ `virtual bool SetFilterActive(const TSharedRef<FNavigationToolFilter>& InFilter, const bool bInActive, const bool bInRequestFilterUpdate = true) = 0;`
- L32 _public prototype_ `virtual bool AddCustomTextFilter(const TSharedRef<FNavigationToolFilter_CustomText>& InFilter, const bool bInAddToConfig) = 0;`
- L33 _public prototype_ `virtual bool RemoveCustomTextFilter(const TSharedRef<FNavigationToolFilter_CustomText>& InFilter, const bool bInAddToConfig) = 0;`
- L35 _public prototype_ `virtual TSharedPtr<FNavigationToolFilter> FindFilterByDisplayName(const FString& InFilterName) const = 0;`
- L36 _public prototype_ `virtual TSharedPtr<FNavigationToolFilter_CustomText> FindCustomTextFilterByDisplayName(const FString& InFilterName) const = 0;`
- L38 _public prototype_ `virtual FNavigationToolFilterData& GetFilterData() = 0;`
- L40 _public prototype_ `virtual void EnableCustomTextFilters(const bool bInEnable, const TArray<TSharedRef<FNavigationToolFilter_CustomText>> InExceptions = {}) = 0;`
- L42 _public prototype_ `virtual void CreateWindow_AddCustomTextFilter(const FCustomTextFilterData& InCustomTextFilterData = FCustomTextFilterData()) = 0;`
- L43 _public prototype_ `virtual void CreateWindow_EditCustomTextFilter(const TSharedPtr<FNavigationToolFilter_CustomText>& InCustomTextFilter) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/NavigationToolFilterBar.h` (Public)


#### enum `UE::SequenceNavigator::ENavigationToolFilterChange`  
`enum class ENavigationToolFilterChange : uint8`  
_L30-36_
- L32 _public enumerator_ `Enable`
- L33 _public enumerator_ `Disable`
- L34 _public enumerator_ `Activate`
- L35 _public enumerator_ `Deactivate`

#### class `UE::SequenceNavigator::FNavigationToolFilterBar`  
`class FNavigationToolFilterBar : public INavigationToolFilterBar`  
_L39-290_
- inherits: `INavigationToolFilterBar`
- desc: Holds the Sequencer track filter collection, the current text filter, and hidden/isolated lists.
- L43 _public member_ `static const FName SharedIdentifier;` — An identifier shared by all filter bars, used to save and load settings common to every instance
- L45 _public prototype_ `DECLARE_EVENT_TwoParams(ISequencerFilterBar, FNavigationToolFiltersChanged, const ENavigationToolFilterChange , const TSharedRef<FNavigationToolFilter>& );`
- L46 _public prototype_ `DECLARE_EVENT_OneParam(ISequencerFilterBar, FOnLayoutChanged, EFilterBarLayout );`
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, bool ) static FCustomTextFilterData DefaultNewCustomTextFilterData(const FText& InFilterString);`
- L51 _public prototype_ `FNavigationToolFilterBar(FNavigationTool& InTool);`
- L54 _public prototype_ `void Init();`
- L56 _public prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InBaseCommandList);`
- L58 _public prototype_ `TSharedPtr<ICustomTextFilter<FNavigationToolViewModelPtr>> CreateTextFilter();`
- L60 _public prototype_ `TSharedRef<SSequencerSearchBox> GetOrCreateSearchBoxWidget();`
- L62 _public prototype_ `TSharedRef<SNavigationToolFilterBar> GenerateWidget();`
- L64 _public prototype_ `virtual bool AreFiltersMuted() const override;`
- L65 _public prototype_ `virtual void MuteFilters(const bool bInMute) override;`
- L66 _public prototype_ `void ToggleMuteFilters();`
- L68 _public prototype_ `virtual bool CanResetFilters() const override;`
- L69 _public prototype_ `virtual void ResetFilters() override;`
- L71 _public function_ `FNavigationToolFiltersChanged& OnFiltersChanged()`
- L72 _public function_ `FOnLayoutChanged& OnLayoutChanged()`
- L73 _public function_ `FSimpleMulticastDelegate& OnActivationStateChanged()`
- L74 _public function_ `FOnVisibilityChanged& OnVisibilityChanged()`
- L75 _public function_ `virtual FSimpleMulticastDelegate& OnRequestUpdate() override`
- L76 _public function_ `virtual FSimpleMulticastDelegate& OnTextFilterTextChanged() override`
- L77 _public function_ `virtual FMuteStateChangedDelegate& OnMuteFiltersChanged() override`
- L79 _public prototype_ `TSharedRef<FNavigationToolFilter_Text> GetTextFilter() const;`
- L80 _public prototype_ `FText GetFilterErrorText() const;`
- L82 _public prototype_ `virtual TSharedPtr<FNavigationToolFilter> FindFilterByDisplayName(const FString& InFilterName) const override;`
- L83 _public prototype_ `virtual TSharedPtr<FNavigationToolFilter_CustomText> FindCustomTextFilterByDisplayName(const FString& InFilterName) const override;`
- L85 _public prototype_ `bool HasAnyFiltersEnabled() const;`
- L89 _public prototype_ `virtual FName GetIdentifier() const override;`
- L91 _public prototype_ `virtual ISequencer& GetSequencer() const override;`
- L93 _public prototype_ `virtual TSharedPtr<FUICommandList> GetCommandList() const override;`
- L95 _public prototype_ `virtual FText GetTextFilterText() const;`
- L96 _public prototype_ `virtual FString GetTextFilterString() const override;`
- L97 _public prototype_ `virtual void SetTextFilterString(const FString& InText) override;`
- L99 _public prototype_ `virtual bool DoesTextFilterStringContainExpressionPair(const ISequencerTextFilterExpressionContext& InExpression) const override;`
- L101 _public prototype_ `virtual void RequestFilterUpdate() override;`
- L103 _public prototype_ `virtual void EnableAllFilters(const bool bInEnable, const TArray<FString>& InExceptionFilterNames) override;`
- L105 _public prototype_ `virtual void ActivateCommonFilters(const bool bInActivate, const TArray<FString>& InExceptionFilterNames) override;`
- L107 _public prototype_ `virtual bool AreAllEnabledFiltersActive(const bool bInActive, const TArray<FString> InExceptionFilterNames) const override;`
- L108 _public prototype_ `virtual void ActivateAllEnabledFilters(const bool bInActivate, const TArray<FString> InExceptionFilterNames) override;`
- L109 _public prototype_ `virtual void ToggleActivateAllEnabledFilters();`
- L111 _public prototype_ `virtual bool IsFilterActiveByDisplayName(const FString& InFilterName) const override;`
- L112 _public prototype_ `virtual bool IsFilterEnabledByDisplayName(const FString& InFilterName) const override;`
- L113 _public prototype_ `virtual bool SetFilterActiveByDisplayName(const FString& InFilterName, const bool bInActive, const bool bInRequestFilterUpdate = true) override;`
- L114 _public prototype_ `virtual bool SetFilterEnabledByDisplayName(const FString& InFilterName, const bool bInEnabled, const bool bInRequestFilterUpdate = true) override;`
- L116 _public prototype_ `virtual TArray<FText> GetFilterDisplayNames() const override;`
- L117 _public prototype_ `virtual TArray<FText> GetCustomTextFilterNames() const override;`
- L119 _public prototype_ `virtual int32 GetTotalDisplayNodeCount() const override;`
- L120 _public prototype_ `virtual int32 GetFilteredDisplayNodeCount() const override;`
- L122 _public prototype_ `virtual const FTextFilterExpressionEvaluator& GetTextFilterExpressionEvaluator() const override;`
- L123 _public prototype_ `virtual TArray<TSharedRef<ISequencerTextFilterExpressionContext>> GetTextFilterExpressionContexts() const override;`
- L124 _public prototype_ `virtual FString GenerateTextFilterStringFromEnabledFilters() const override;`
- L129 _public prototype_ `virtual FNavigationToolFilterData& GetFilterData() override;`
- L134 _public prototype_ `bool AnyCommonFilterActive() const;`
- L135 _public prototype_ `virtual bool HasAnyFilterActive(const bool bCheckTextFilter = true , const bool bInCheckHideIsolateFilter = true , const bool bInCheckCommonFilters = true , const bool bInCheckInternalFilters = true , const bool bInCheckCustomTextFilters = true) const override;`
- L140 _public prototype_ `virtual bool IsFilterActive(const TSharedRef<FNavigationToolFilter> InFilter) const override;`
- L141 _public prototype_ `virtual bool SetFilterActive(const TSharedRef<FNavigationToolFilter>& InFilter, const bool bInActive, const bool bInRequestFilterUpdate = true) override;`
- L142 _public prototype_ `void ActivateCommonFilters(const bool bInActivate , const TArray<TSharedRef<FFilterCategory>>& InMatchCategories , const TArray<TSharedRef<FNavigationToolFilter>>& InExceptions);`
- L145 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter>> GetActiveFilters() const;`
- L149 _public prototype_ `bool HasEnabledCommonFilters() const;`
- L150 _public prototype_ `bool HasEnabledFilter(const TArray<TSharedRef<FNavigationToolFilter>>& InFilters = {}) const;`
- L151 _public prototype_ `virtual bool HasAnyFilterEnabled() const override;`
- L152 _public prototype_ `virtual bool IsFilterEnabled(const TSharedRef<FNavigationToolFilter> InFilter) const override;`
- L153 _public prototype_ `virtual bool SetFilterEnabled(const TSharedRef<FNavigationToolFilter> InFilter, const bool bInEnabled, const bool bInRequestFilterUpdate = true) override;`
- L154 _public prototype_ `void EnableFilters(const bool bInEnable , const TArray<TSharedRef<FFilterCategory>> InMatchCategories = {} , const TArray<TSharedRef<FNavigationToolFilter>> InExceptions = {});`
- L157 _public prototype_ `void ToggleFilterEnabled(const TSharedRef<FNavigationToolFilter> InFilter);`
- L158 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter>> GetEnabledFilters() const;`
- L162 _public prototype_ `bool HasAnyCommonFilters() const;`
- L163 _public prototype_ `bool AddFilter(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L164 _public prototype_ `bool RemoveFilter(const TSharedRef<FNavigationToolFilter>& InFilter);`
- L166 _public prototype_ `virtual TArray<TSharedRef<FNavigationToolFilter>> GetCommonFilters(const TArray<TSharedRef<FFilterCategory>>& InCategories = {}) const override;`
- L170 _public prototype_ `bool AnyCustomTextFilterActive() const;`
- L171 _public prototype_ `bool HasEnabledCustomTextFilters() const;`
- L172 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter_CustomText>> GetAllCustomTextFilters() const;`
- L173 _public prototype_ `virtual bool AddCustomTextFilter(const TSharedRef<FNavigationToolFilter_CustomText>& InFilter, const bool bInAddToConfig) override;`
- L174 _public prototype_ `virtual bool RemoveCustomTextFilter(const TSharedRef<FNavigationToolFilter_CustomText>& InFilter, const bool bInRemoveFromConfig) override;`
- L175 _public prototype_ `void ActivateCustomTextFilters(const bool bInActivate, const TArray<TSharedRef<FNavigationToolFilter_CustomText>> InExceptions = {});`
- L176 _public prototype_ `virtual void EnableCustomTextFilters(const bool bInEnable, const TArray<TSharedRef<FNavigationToolFilter_CustomText>> InExceptions = {}) override;`
- L177 _public prototype_ `TArray<TSharedRef<FNavigationToolFilter_CustomText>> GetEnabledCustomTextFilters() const;`
- L181 _public prototype_ `virtual TSet<TSharedRef<FFilterCategory>> GetFilterCategories(const TSet<TSharedRef<FNavigationToolFilter>>* InFilters = nullptr) const override;`
- L182 _public prototype_ `TSet<TSharedRef<FFilterCategory>> GetConfigCategories() const;`
- L183 _public prototype_ `TSharedRef<FFilterCategory> GetClassTypeCategory() const;`
- L184 _public prototype_ `TSharedRef<FFilterCategory> GetComponentTypeCategory() const;`
- L185 _public prototype_ `TSharedRef<FFilterCategory> GetMiscCategory() const;`
- L189 _public prototype_ `const FNavigationToolFilterData& FilterNodes();`
- L191 _public prototype_ `bool ShouldUpdateOnTrackValueChanged() const;`
- L193 _public prototype_ `TSharedRef<SComboButton> MakeAddFilterButton();`
- L195 _public prototype_ `bool ShouldShowFilterBarWidget() const;`
- L196 _public prototype_ `bool IsFilterBarVisible() const;`
- L197 _public prototype_ `void ToggleFilterBarVisibility();`
- L199 _public prototype_ `bool IsFilterBarLayout(const EFilterBarLayout InLayout) const;`
- L200 _public prototype_ `void SetToVerticalLayout();`
- L201 _public prototype_ `void SetToHorizontalLayout();`
- L202 _public prototype_ `void ToggleFilterBarLayout();`
- L204 _public prototype_ `virtual void CreateWindow_AddCustomTextFilter(const FCustomTextFilterData& InCustomTextFilterData = FCustomTextFilterData()) override;`
- L205 _public prototype_ `virtual void CreateWindow_EditCustomTextFilter(const TSharedPtr<FNavigationToolFilter_CustomText>& InCustomTextFilter) override;`
- L207 _public prototype_ `bool IsFilterSupported(const TSharedRef<FNavigationToolFilter>& InFilter) const;`
- L208 _public prototype_ `bool IsFilterSupported(const FString& InFilterName) const;`
- L210 _public prototype_ `virtual void OpenTextExpressionHelp() override;`
- L211 _public prototype_ `virtual void SaveCurrentFilterSetAsCustomTextFilter() override;`
- L212 _public prototype_ `virtual void CreateNewTextFilter() override;`
- L214 _public prototype_ `virtual bool DoesCommonFilterPass(const Sequencer::TViewModelPtr<Sequencer::FViewModel>& InViewModel, const FString& InFilterName) const override;`
- L216 _public prototype_ `virtual void GetCommonFilterKeySuggestions(TArray<FSequencerFilterSuggestion>& OutSuggestions) const override;`
- L217 _public prototype_ `virtual void GetCommonFilterValueSuggestions(const FString& InKey, TArray<FSequencerFilterSuggestion>& OutSuggestions) const override;`
- L219 _public prototype_ `virtual bool IsCommonFilterName(const FString& InFilterName) const override;`
- L222 _protected prototype_ `virtual void GetCommonFiltersImpl(TArray<TSharedPtr<void>>& OutTypeErasedFilters) const override;`
- L224 _protected prototype_ `void CreateDefaultFilters();`
- L225 _protected prototype_ `void CreateCustomTextFiltersFromConfig();`
- L227 _protected prototype_ `bool PassesAnyCommonFilter(const FNavigationToolViewModelPtr& InNode);`
- L228 _protected prototype_ `bool PassesAllCustomTextFilters(const FNavigationToolViewModelPtr& InNode);`
- L230 _protected prototype_ `TArray<TSharedRef<FNavigationToolFilter>> GetFilterList(const bool bInIncludeCustomTextFilters = false) const;`
- L232 _protected prototype_ `void OnSearchTextChanged(const FText& InFilterText);`
- L233 _protected prototype_ `void OnSearchTextCommitted(const FText& InFilterText, const ETextCommit::Type InCommitType);`
- L234 _protected prototype_ `void OnSearchTextSaved(const FText& InFilterText);`
- L236 _protected prototype_ `void BroadcastFiltersChanged(const TSharedRef<FNavigationToolFilter>& InFilter, const ENavigationToolFilterChange InChangeType);`
- L239 _protected member_ `FNavigationTool& Tool;` — The Navigation Tool this filter bar is interacting with
- L241 _protected member_ `TSharedRef<FUICommandList> CommandList;`
- L244 _protected member_ `bool bFiltersMuted = false;` — Global override to enable/disable all filters
- L246 _protected member_ `TSharedRef<FFilterCategory> ClassTypeCategory;`
- L247 _protected member_ `TSharedRef<FFilterCategory> ComponentTypeCategory;`
- L248 _protected member_ `TSharedRef<FFilterCategory> MiscCategory;`
- L249 _protected member_ `TSharedRef<FFilterCategory> TransientCategory;`
- L251 _protected member_ `TSharedRef<FNavigationToolFilterCollection> CommonFilters;`
- L253 _protected member_ `TSharedRef<FNavigationToolFilter_Text> TextFilter;`
- L256 _protected member_ `TArray<TSharedRef<FNavigationToolFilter_CustomText>> CustomTextFilters;`
- L258 _protected member_ `TSharedPtr<FNavigationToolFilterMenu> FilterMenu;`
- L260 _protected member_ `FNavigationToolFilterData FilterData;`
- L262 _protected member_ `TWeakPtr<SSequencerSearchBox> WeakSearchBoxWidget;`
- L264 _protected member_ `TSharedPtr<SNavigationToolFilterBar> FilterBarWidget;`
- L266 _protected member_ `FNavigationToolFiltersChanged FiltersChangedEvent;`
- L267 _protected member_ `FOnLayoutChanged LayoutChangedEvent;`
- L268 _protected member_ `FSimpleMulticastDelegate ActivationStateChangedEvent;`
- L269 _protected member_ `FOnVisibilityChanged VisibilityChangedEvent;`
- L270 _protected member_ `FSimpleMulticastDelegate RequestUpdateEvent;`
- L271 _protected member_ `FSimpleMulticastDelegate TextFilterTextChangedEvent;`
- L272 _protected member_ `FMuteStateChangedDelegate MuteFiltersChangedEvent;`
- L275 _private member_ `static int32 InstanceCount;`
- L278 _private prototype_ `bool FilterNodesRecursive(INavigationToolView& InToolView , const UNavigationToolSettings& InSettings , const bool bInHasActiveFilter , const FNavigationToolViewModelWeakPtr& InWeakStartNode);` — Do not call directly! Should only be called by FilterNodes().
- L283 _private prototype_ `bool CheckFilterNameValidity(const FString& InNewFilterName, const FString& InOldFilterName, const bool bInIsEdit, FText& OutErrorText) const;`
- L285 _private prototype_ `bool TryCreateCustomTextFilter(const FCustomTextFilterData& InNewFilterData, const FString& InOldFilterName, const bool bInApply, FText& OutErrorText);`
- L286 _private prototype_ `bool TryModifyCustomTextFilter(const FCustomTextFilterData& InNewFilterData, const FString& InOldFilterName, FText& OutErrorText);`
- L287 _private prototype_ `bool TryDeleteCustomTextFilter(const FString& InFilterName, FText& OutErrorText);`
- L289 _private prototype_ `void HandleTextFilterChanged();`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L45 _delegate_ `DECLARE_EVENT_TwoParams(ISequencerFilterBar, FNavigationToolFiltersChanged, const ENavigationToolFilterChange , const TSharedRef<FNavigationToolFilter>& );`
- L46 _delegate_ `DECLARE_EVENT_OneParam(ISequencerFilterBar, FOnLayoutChanged, EFilterBarLayout );`
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, bool ) static FCustomTextFilterData DefaultNewCustomTextFilterData(const FText& InFilterString);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/NavigationToolFilterData.h` (Public)


#### struct `UE::SequenceNavigator::FNavigationToolFilterData`  
`struct FNavigationToolFilterData`  
_L15-54_
- desc: Represents a cache between nodes for a filter operation.
- L17 _public prototype_ `FNavigationToolFilterData(const FString& InRawFilterText);`
- L19 _public prototype_ `bool operator==(const FNavigationToolFilterData& InRhs) const;`
- L20 _public prototype_ `bool operator!=(const FNavigationToolFilterData& InRhs) const;`
- L22 _public prototype_ `void Reset();`
- L24 _public prototype_ `FString GetRawFilterText() const;`
- L26 _public prototype_ `uint32 GetDisplayNodeCount() const;`
- L27 _public prototype_ `uint32 GetTotalNodeCount() const;`
- L29 _public prototype_ `uint32 GetFilterInCount() const;`
- L30 _public prototype_ `uint32 GetFilterOutCount() const;`
- L32 _public prototype_ `void IncrementTotalNodeCount();`
- L34 _public prototype_ `void FilterInNode(const FNavigationToolViewModelWeakPtr& InWeakNode);`
- L35 _public prototype_ `void FilterOutNode(const FNavigationToolViewModelWeakPtr& InWeakNode);`
- L37 _public prototype_ `void FilterInParentChildNodes(const FNavigationToolViewModelWeakPtr& InWeakNode , const bool bInIncludeSelf, const bool bInIncludeParents, const bool bInIncludeChildren = false);`
- L40 _public prototype_ `void FilterInNodeWithAncestors(const FNavigationToolViewModelWeakPtr& InWeakNode);`
- L42 _public prototype_ `bool ContainsFilterInNodes(const FNavigationToolFilterData& InOtherData) const;`
- L44 _public prototype_ `bool IsFilteredIn(const FNavigationToolViewModelWeakPtr& InWeakNode) const;`
- L45 _public prototype_ `bool IsFilteredOut(const FNavigationToolViewModelWeakPtr& InWeakNode) const;`
- L48 _protected member_ `FString RawFilterText;`
- L50 _protected member_ `uint32 TotalNodeCount = 0;`
- L53 _protected member_ `TSet<FNavigationToolViewModelWeakPtr> FilterInNodes;` — Nodes to be displayed in the UI

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/TextExpressions/NavigationToolFilterTextExpressionContext.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilterTextExpressionContext`  
`class FNavigationToolFilterTextExpressionContext : public ISequencerTextFilterExpressionContext`  
_L18-44_
- inherits: `ISequencerTextFilterExpressionContext`
- L21 _public prototype_ `FNavigationToolFilterTextExpressionContext(INavigationToolFilterBar& InFilterInterface);`
- L23 _public prototype_ `void SetFilterItem(const FNavigationToolViewModelPtr& InFilterItem);`
- L27 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L30 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey , const FTextFilterString& InValue , const ETextFilterComparisonOperation InComparisonOperation , const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L38 _protected prototype_ `UMovieSceneSequence* GetFocusedMovieSceneSequence() const;`
- L39 _protected prototype_ `UMovieScene* GetFocusedGetMovieScene() const;`
- L41 _protected member_ `INavigationToolFilterBar& FilterInterface;`
- L43 _protected member_ `FNavigationToolViewModelWeakPtr WeakFilterItem;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Filters/TextExpressions/NavigationToolFilterTextExpressionExtension.h` (Public)


#### class `UNavigationToolFilterTextExpressionExtension`  
`class UNavigationToolFilterTextExpressionExtension : public UObject`  
_L21-34_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Derive from this class to make additional track filter text expressions available in Sequencer.
- L31 _public function_ `virtual void AddFilterTextExpressionExtensions(UE::SequenceNavigator::INavigationToolFilterBar& InOutFilterInterface , TArray<TSharedRef<UE::SequenceNavigator::FNavigationToolFilterTextExpressionContext>>& InOutExpressionList) const` — Override to add additional Sequencer track filter text expressions. @param InOutFilterInterface The filter interface to extend @param InOutExpressionList  Expression list to add additional text expressions to

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/INavigationTool.h` (Public)


#### class `UE::SequenceNavigator::INavigationTool`  
`class INavigationTool : public TSharedFromThis<INavigationTool>`  
_L39-253_
- inherits: `TSharedFromThis<INavigationTool>`
- desc: The Navigation Tool Object that is commonly instanced once per Sequencer (unless for advanced use where there are different Navigation Tool instances with different item ordering and behaviors). This is the object that dictates core Navigation Tool behavior like how items are sorted, which items are allowed, etc. Views are the objects that take this core behavior and show a part of it (e.g. through filters).
- L42 _public prototype_ `virtual ~INavigationTool() = default;`
- L44 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnToolLoaded);`
- L45 _public prototype_ `virtual FOnToolLoaded& GetOnToolLoaded() = 0;`
- L47 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const = 0;`
- L49 _public prototype_ `virtual bool IsToolTabVisible() const = 0;`
- L50 _public prototype_ `virtual void ShowHideToolTab(const bool bInVisible) = 0;`
- L51 _public prototype_ `virtual void ToggleToolTabVisible() = 0;`
- L53 _public prototype_ `virtual void ForEachProvider(const TFunction<bool(const TSharedRef<FNavigationToolProvider>& InToolProvider)>& InPredicate) const = 0;`
- L56 _public prototype_ `virtual TSharedPtr<FUICommandList> GetBaseCommandList() const = 0;` — Gets the Command List that the Navigation Tool Views will use to append their Command Lists to
- L59 _public prototype_ `virtual TSharedPtr<INavigationToolView> RegisterToolView(const int32 InToolViewId) = 0;` — Register a new Navigation Tool View to the Navigation Tool to the given id, replacing the old view that was bound to the given id
- L62 _public prototype_ `virtual TSharedPtr<INavigationToolView> GetToolView(const int32 InToolViewId) const = 0;` — Gets the Navigation Tool View bound to the given id
- L65 _public prototype_ `virtual TSharedPtr<INavigationToolView> GetMostRecentToolView() const = 0;` — Gets the outliner view that was most recently used (i.e. called FNavigationTool::UpdateRecentToolViews)
- L69 _public function_ `template<typename InItemType, typename = typename TEnableIf<TIsDerivedFrom<InItemType, INavigationToolItem>::IsDerived>::Type, typename ...InArgTypes> FNavigationToolViewModelPtr FindOrAdd(const TSharedRef<FNavigationToolProvider>& InProvider, InArgTypes&&... InArgs)` — Instantiates a new Item and automatically registers it to the Navigation Tool
- L92 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FNavigationToolItemProxy>::IsDerived>::Type> INavigationToolItemProxyFactory* GetItemProxyFactory() const` — Tries to find the Item Proxy Factory for the given Item Proxy Type Name
- L110 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FNavigationToolItemProxy>::IsDerived>::Type, typename ...InArgTypes> TSharedPtr<FNavigationToolItemProxy> GetOrCreateItemProxy(const FNavigationToolViewModelPtr& InParentItem, InArgTypes&&... InArgs)` — Tries to get the Item Proxy Factory for the given Item Proxy type, first trying the Navigation Tool Registry then the Module's then returns an existing item proxy created via the factory, or creates one if there's no existing item proxy @returns the Item Proxy created by the Factory. Can be null if no factory was found or if the factory intentionally returns null
- L139 _public prototype_ `virtual TArray<FName> GetRegisteredItemProxyTypeNames() const = 0;` — Gathers the Type Names of all the Item Proxies that are registered both in the outliner proxy registry and the module's
- L145 _public prototype_ `virtual bool IsObjectAllowedInTool(const UObject* const InObject) const = 0;` — Determines whether the given actor can be presented in the Navigation Tool, at all. This is a permanent check unlike filters that are temporary.
- L148 _public prototype_ `virtual void RegisterItem(const FNavigationToolViewModelPtr& InItem) = 0;` — Registers the given Item, replacing the old one.
- L151 _public prototype_ `virtual void UnregisterItem(const FNavigationToolItemId& InItemId) = 0;` — Unregisters the Item having the given ItemId
- L154 _public prototype_ `virtual void RequestRefresh() = 0;` — Ensures that the next time Refresh is called in tick, Refresh will be called
- L161 _public prototype_ `virtual void Refresh() = 0;` — Flushes the Pending Actions from the Queue while also updating the state of the Navigation Tool. Calling it directly is forcing it to happen. If a refresh is needed it will be called on the next tick automatically.
- L164 _public prototype_ `virtual FNavigationToolViewModelWeakPtr GetTreeRoot() const = 0;` — Gets the tree root item of the Navigation Tool
- L170 _public prototype_ `virtual FNavigationToolViewModelPtr FindItem(const FNavigationToolItemId& InItemId) const = 0;` — Finds the registered item that has the given Id @returns The item with the given Id, or null if the item does not exist or was not registered to the Navigation Tool
- L177 _public prototype_ `virtual TArray<FNavigationToolViewModelPtr> TryFindItems(const Sequencer::FViewModelPtr& InSequencerOutlinerViewModel) const = 0;` — Attempts to find all items associated with a Sequencer outliner view model @param InSequencerOutlinerViewModel The Sequencer view model to find the items for @return The list of Navigation Tool items found
- L184 _public prototype_ `virtual void SetIgnoreNotify(const ENavigationToolIgnoreNotifyFlags InFlag, const bool bInIgnore) = 0;` — Adds or Removes the Ignore Notify Flags to prevent certain actions from automatically happening when they're triggered @param InFlag the ignore flag to add or remove @param bInIgnore whether to add (true) or remove (false) the flag
- L187 _public prototype_ `virtual void OnSequencerSelectionChanged() = 0;` — Called when the Sequencer selection has changed
- L190 _public prototype_ `virtual TArray<FNavigationToolViewModelWeakPtr> GetSelectedItems(const bool bInNormalizeToTopLevelSelections = false) const = 0;` — Returns the currently selected items in the most recent outliner view (since this list can vary between outliner views)
- L197 _public prototype_ `virtual void SelectItems(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , const ENavigationToolItemSelectionFlags InFlags = ENavigationToolItemSelectionFlags::SignalSelectionChange) const = 0;` — Selects the given Items on all Navigation Tool Views @param InWeakItems the items to select @param InFlags how the items should be selected (appended, notify of selections, etc)
- L204 _public prototype_ `virtual void ClearItemSelection(const bool bInSignalSelectionChange) const = 0;` — Clears the Item Selection from all Navigation Tool Views @param bInSignalSelectionChange whether to notify the change in selection
- L207 _public prototype_ `virtual void SetItemColor(const FNavigationToolViewModelPtr& InItem, const FColor& InColor) = 0;` — Pairs the Item with the given color name, overriding the inherited color if different
- L210 _public prototype_ `virtual void RemoveItemColor(const FNavigationToolViewModelPtr& InItem) = 0;` — Removes the Color pairing of the given Item (can still have an inherited color though)
- L218 _public prototype_ `virtual TOptional<FColor> FindItemColor(const FNavigationToolViewModelPtr& InItem, bool bRecurseParent = true) const = 0;` — Gets the color related to the Item @param InItem the item to query @param bRecurseParent whether to get the color of the parent (recursively) if the given item does not have a color by itself @returns the matching color pair or unset if item is invalid or no color could be found.
- L226 _public function_ `template<typename InItemActionType, typename = typename TEnableIf<TIsDerivedFrom<InItemActionType, INavigationToolItemAction>::IsDerived>::Type, typename ...InArgTypes> TSharedRef<InItemActionType> NewItemAction(InArgTypes&&... InArgs)` — Instantiates a new item action without adding it to the Pending Actions Queue. This should only be used directly when planning to enqueue multiple actions. @see FNavigationTool::EnqueueItemActions
- L237 _public function_ `template<typename InItemActionType, typename = typename TEnableIf<TIsDerivedFrom<InItemActionType, INavigationToolItemAction>::IsDerived>::Type, typename ...InArgTypes> void EnqueueItemAction(InArgTypes&&... InArgs)` — Instantiates a single new item action and immediately adds it to the Pending Actions Queue. Ideal for when dealing with a single action. For multiple actions use FNavigationTool::EnqueueItemActions.
- L243 _public prototype_ `virtual void EnqueueItemActions(TArray<TSharedPtr<INavigationToolItemAction>>&& InItemActions) noexcept = 0;` — Adds the given actions to the Pending Action Queue
- L246 _public prototype_ `virtual void NotifyToolItemRenamed(const FNavigationToolViewModelPtr& InItem) = 0;` — Called when an Item has been Renamed
- L249 _public prototype_ `virtual void NotifyToolItemDeleted(const FNavigationToolViewModelPtr& InItem) = 0;` — Called when an Item has been deleted
- L252 _protected prototype_ `virtual const FNavigationToolItemProxyRegistry& GetItemProxyRegistry() const = 0;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnToolLoaded);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/INavigationToolView.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolView`  
`class INavigationToolView : public TSharedFromThis<INavigationToolView>`  
_L24-131_
- inherits: `TSharedFromThis<INavigationToolView>`
- L27 _public prototype_ `virtual ~INavigationToolView() = default;`
- L29 _public prototype_ `virtual TSharedPtr<INavigationTool> GetOwnerTool() const = 0;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> GetToolWidget() const = 0;` — Returns the Navigation Tool Widget. Can be null widget
- L34 _public prototype_ `virtual TSharedPtr<ISequencer> GetSequencer() const = 0;`
- L37 _public prototype_ `virtual void RequestRefresh() = 0;` — Marks the Navigation Tool View to be refreshed on Next Tick
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnToolViewRefreshed);`
- L40 _public prototype_ `virtual FOnToolViewRefreshed& GetOnToolViewRefreshed() = 0;`
- L42 _public prototype_ `virtual void SetKeyboardFocus() = 0;`
- L44 _public prototype_ `virtual ENavigationToolItemViewMode GetItemDefaultViewMode() const = 0;`
- L46 _public prototype_ `virtual ENavigationToolItemViewMode GetItemProxyViewMode() const = 0;`
- L48 _public prototype_ `virtual bool IsColumnVisible(const TSharedPtr<INavigationToolColumn>& InColumn) const = 0;`
- L50 _public prototype_ `virtual TSharedRef<SWidget> GetColumnMenuContent(const FName InColumnId) = 0;`
- L52 _public prototype_ `virtual void GetChildrenOfItem(const FNavigationToolViewModelWeakPtr InWeakItem , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren) const = 0;`
- L62 _public prototype_ `virtual void GetChildrenOfItem(const FNavigationToolViewModelWeakPtr InWeakItem , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const ENavigationToolItemViewMode InViewMode , const TSet<FNavigationToolViewModelWeakPtr>& InWeakRecursionDisallowedItems) const = 0;` — Gets the children of a given item. Can recurse if the immediate child is hidden (the children of these hidden items should still be given the opportunity to show up) @param InWeakItem The item to get the children of @param OutWeakChildren The visible children in the give view mode @param InViewMode The view mode(s) that the children should support to be added to OutChildren @param InWeakRecursionDisallowedItems The items where recursion should not be performed
- L68 _public prototype_ `virtual bool IsItemReadOnly(const FNavigationToolViewModelWeakPtr& InWeakItem) const = 0;` — Whether the given item is explicitly marked as Read-only in the Navigation Tool
- L73 _public prototype_ `virtual bool CanSelectItem(const FNavigationToolViewModelWeakPtr& InWeakItem) const = 0;` — Whether the given item can be selected in this Navigation Tool View / Widget
- L76 _public prototype_ `virtual void SelectItems(TArray<FNavigationToolViewModelWeakPtr> InWeakItems , const ENavigationToolItemSelectionFlags InFlags = ENavigationToolItemSelectionFlags::SignalSelectionChange) = 0;` — Selects the item in this Navigation Tool View
- L80 _public prototype_ `virtual void ClearItemSelection(const bool bInSignalSelectionChange = true) = 0;` — Clears the currently selected items in the Navigation Tool View
- L83 _public prototype_ `virtual bool IsItemSelected(const FNavigationToolViewModelWeakPtr& InWeakItem) const = 0;` — Whether the current item is selected in this Navigation Tool View
- L86 _public prototype_ `virtual TArray<FNavigationToolViewModelWeakPtr> GetSelectedItems() const = 0;` — Gets the currently selected items in the Tree View
- L91 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry , const FPointerEvent& InPointerEvent , const FNavigationToolViewModelWeakPtr InWeakTargetItem) = 0;` — Called a drag is attempted for the selected items in view
- L96 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem) = 0;` — Processes the drag and drop for the given item if valid, else it will process it for the root item
- L101 _public prototype_ `virtual TOptional<EItemDropZone> OnCanDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelWeakPtr InWeakTargetItem) const = 0;` — Determines whether the drag and drop can be processed by the given item
- L107 _public prototype_ `virtual bool IsItemExpanded(const FNavigationToolViewModelWeakPtr& InWeakItem , const bool bInUseFilter = true) const = 0;`
- L111 _public prototype_ `virtual void SetItemExpansion(const FNavigationToolViewModelWeakPtr& InWeakItem , const bool bInExpand, const bool bInUseFilter = true) = 0;` — Expands / Collapses the given item
- L115 _public prototype_ `virtual void SetItemExpansionRecursive(const FNavigationToolViewModelWeakPtr InWeakItem, const bool bInExpand) = 0;` — Expands / Collapses the given item and its children recursively
- L118 _public prototype_ `virtual void SetParentItemExpansions(const FNavigationToolViewModelWeakPtr& InWeakItem, const bool bInExpand) = 0;` — Change the expansion state of the parents (recursively) of the given item
- L121 _public prototype_ `virtual bool CanExpandAll() const = 0;` — @return True if all items in the tool tree view can be expanded
- L124 _public prototype_ `virtual void ExpandAll() = 0;` — Expands all items in the tool tree view
- L127 _public prototype_ `virtual bool CanCollapseAll() const = 0;` — @return True if all items in the tool tree view can be collapsed
- L130 _public prototype_ `virtual void CollapseAll() = 0;` — Collapses all items in the tool tree view

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnToolViewRefreshed);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemActions/INavigationToolItemAction.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolItemAction`  
`class INavigationToolItemAction : public Sequencer::FViewModel`  
_L20-35_
- inherits: `Sequencer::FViewModel`
- desc: Interface class for an action in the Navigation Tool (e.g. Add/Delete/Move tree item)
- L28 _public function_ `virtual bool ShouldTransact() const` — Determines whether the given action modifies its objects and should transact
- L31 _public prototype_ `virtual void Execute(FNavigationTool& InTool) = 0;` — The action to execute on the given Navigation Tool
- L34 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, const bool bInRecursive) = 0;` — Replace any objects that might be held in this action that has been killed and replaced by a new object (e.g. BP Components)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemActions/NavigationToolAddItem.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolAddItem`  
`class FNavigationToolAddItem : public INavigationToolItemAction`  
_L19-37_
- inherits: `INavigationToolItemAction`
- desc: Item action responsible for adding an item to the tree under a given optional parent. If Parent is null, it is added as a Top Level Item.
- L27 _public prototype_ `virtual ~FNavigationToolAddItem() = default;`
- L30 _public prototype_ `virtual bool ShouldTransact() const override;`
- L31 _public prototype_ `virtual void Execute(FNavigationTool& InTool) override;`
- L32 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bRecursive) override;`
- L36 _protected member_ `FNavigationToolAddItemParams AddParams;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemActions/NavigationToolRemoveItem.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolRemoveItem`  
`class FNavigationToolRemoveItem : public INavigationToolItemAction`  
_L18-35_
- inherits: `INavigationToolItemAction`
- desc: Item Action responsible for removing/unregistering items from the tree
- L26 _public prototype_ `virtual ~FNavigationToolRemoveItem() = default;`
- L29 _public prototype_ `virtual void Execute(FNavigationTool& InTool) override;`
- L30 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, const bool bInRecursive) override;`
- L34 _protected member_ `FNavigationToolRemoveItemParams RemoveParams;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemProxies/Factories/NavigationToolItemProxyDefaultFactory.h` (Public)


#### class `UE::SequenceNavigator::TNavigationToolItemProxyDefaultFactoryBase`  
`class TNavigationToolItemProxyDefaultFactoryBase : public INavigationToolItemProxyFactory`  
_L17-33_
- inherits: `INavigationToolItemProxyFactory`
- L20 _public function_ `virtual FName GetItemProxyTypeName() const override`
- L27 _protected function_ `template<typename... InArgTypes> TSharedRef<FNavigationToolItemProxy> DefaultCreateItemProxy(InArgTypes&&... InArgs)`

#### class `UE::SequenceNavigator::TNavigationToolItemProxyDefaultFactory`  
`class TNavigationToolItemProxyDefaultFactory : public TNavigationToolItemProxyDefaultFactoryBase<InItemProxyType, InItemProxyPriority>`  
_L37-44_
- inherits: `TNavigationToolItemProxyDefaultFactoryBase<InItemProxyType,InItemProxyPriority>`
- L40 _public function_ `virtual TSharedPtr<FNavigationToolItemProxy> CreateItemProxy(INavigationTool& InTool, const FNavigationToolViewModelPtr& InParentItem) override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemProxies/INavigationToolItemProxyFactory.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolItemProxyFactory`  
`class INavigationToolItemProxyFactory`  
_L21-32_
- desc: Item Proxy Factories are the classes that instance or get the existing Navigation Tool Item Proxies for a given Item @see INavigationToolItemProxy
- L24 _public prototype_ `virtual ~INavigationToolItemProxyFactory() = default;`
- L27 _public prototype_ `virtual FName GetItemProxyTypeName() const = 0;` — Gets the Type Name of the Item Proxy the Factory creates
- L30 _public prototype_ `virtual TSharedPtr<FNavigationToolItemProxy> CreateItemProxy(INavigationTool& InTool , const FNavigationToolViewModelPtr& InParentItem) = 0;` — Returns a newly created instance of the Relevant Item Proxy if successful

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemProxies/NavigationToolComponentProxy.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolComponentProxy`  
`class FNavigationToolComponentProxy : public FNavigationToolItemProxy`  
_L12-32_
- inherits: `FNavigationToolItemProxy`
- L22 _public prototype_ `virtual FText GetDisplayName() const override;`
- L23 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L24 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L25 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L29 _public prototype_ `virtual void GetProxiedItems(const FNavigationToolViewModelPtr& InParent , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/ItemProxies/NavigationToolItemProxyRegistry.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItemProxyRegistry`  
`class FNavigationToolItemProxyRegistry`  
_L19-86_
- desc: Handles registering a Navigation Tool item type with a Navigation Tool item proxy factory that creates the respective INavigationToolItemProxy @see INavigationToolItemProxy
- L25 _public function_ `void RegisterItemProxyFactory(InArgTypes&&... InArgs)`
- L37 _public function_ `void RegisterItemProxyWithDefaultFactory()`
- L44 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FNavigationToolItemProxy>::IsDerived>::Type> void UnregisterItemProxyFactory()` — Unregisters the given Item Type from having an Item Proxy Factory
- L49 _public function_ `void UnregisterItemProxyFactory(FName InItemProxyTypeName)`
- L55 _public function_ `void UnregisterAllItemProxyFactories()` — Unregisters all the Item Proxy Factories for this Instance
- L61 _public function_ `INavigationToolItemProxyFactory* GetItemProxyFactory(const FName InItemProxyTypeName) const` — Gets the Item Proxy Factory for the given Item Proxy Type Name. Returns nullptr if not found
- L72 _public function_ `template<typename InItemProxyType, typename = typename TEnableIf<TIsDerivedFrom<InItemProxyType, FNavigationToolItemProxy>::IsDerived>::Type> INavigationToolItemProxyFactory* GetItemProxyFactory() const` — Gets the Item Proxy Factory if it was registered with the Item Proxy Type Name. Returns nullptr if not found
- L78 _public function_ `void GetRegisteredItemProxyTypeNames(TSet<FName>& OutItemProxyTypeNames) const` — Gets all the Item Proxy Type Names that exist in this registry
- L85 _private member_ `TMap<FName, TSharedRef<INavigationToolItemProxyFactory>> ItemProxyFactories;` — Map of the item proxy type name and its item proxy factory

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/INavigationToolItem.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolItem`  
`class INavigationToolItem`  
_L40-306_
- desc: An Navigation Tool Item is the class that represents a single element (i.e. node) in the Navigation Tool tree. This can be an item that represents an object (e.g. actor, component) or a folder, or something else.
- L42 _private typedef_ `using IndexType = TArray<INavigationToolItem>::SizeType;`
- L48 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRenameAction, ENavigationToolRenameAction, const TSharedPtr<INavigationToolView>&);`
- L50 _public prototype_ `virtual ~INavigationToolItem() = default;`
- L53 _public prototype_ `virtual bool IsItemValid() const = 0;` — Determines whether the Item properties are in a valid state
- L56 _public function_ `virtual UObject* GetItemObject() const` — Gets the UObject that this item represents. May be null due if no item association or multiple.
- L59 _public prototype_ `virtual TSharedPtr<FNavigationToolProvider> GetProvider() const = 0;` — Gets the module provider responsible for the creation of this item
- L62 _public prototype_ `virtual FNavigationToolSaveState* GetProviderSaveState() const = 0;` — Gets the providers saved state
- L65 _public function_ `virtual void Select(FNavigationToolScopedSelection& InSelection) const` — Used to signal the Scoped Selection that this Item should be Selected
- L68 _public function_ `virtual bool IsSelected(const FNavigationToolScopedSelection& InSelection) const` — Determines whether the given Item is selected in the given Scoped Selection
- L71 _public function_ `virtual bool IsSelectable() const` — Whether the Item can be selected in Navigation Tool at all
- L74 _public function_ `virtual void OnSelect()` — Called when an Item is selected
- L77 _public function_ `virtual void OnDoubleClick()` — Called when an Item is double-clicked with the mouse
- L80 _public prototype_ `virtual INavigationTool& GetOwnerTool() const = 0;` — Gets the Navigation Tool that owns this item
- L83 _public function_ `virtual void OnItemRegistered()` — Called when the Item has been registered into the Navigation Tool
- L86 _public function_ `virtual void OnItemUnregistered()` — Called when the Item has been unregistered from the Navigation Tool
- L89 _public function_ `virtual void OnItemSelectionChanged(const bool bInIsSelected)` — Called when the Item been selected/deselected from the Tree View
- L92 _public prototype_ `virtual void RefreshChildren() = 0;` — Refreshes what the Parent and Children are of this Item. (not recursive!)
- L95 _public prototype_ `virtual void ResetChildren() = 0;` — Resets both the cached visible children and children (before doing so, sets all child's parents to null)
- L102 _public prototype_ `virtual bool ShouldSort() const = 0;` — Determines whether this item can be sorted by the Navigation Tool or not. Unsorted Items usually mean that they have their own way of sorting that Navigation Tool's Item Sorting Data should not interfere with. Note: Unsorted Children go before Sorted Items (e.g. Item Proxies go first before Actors below a Parent)
- L105 _public prototype_ `virtual bool CanAddChild(const FNavigationToolViewModelPtr& InChild) const = 0;` — Determines whether the given Child is supported and can be added under this Item
- L111 _public prototype_ `virtual bool AddChild(const FNavigationToolAddItemParams& InAddItemParams) = 0;` — Adds another Child under this Item if such Item is supported. Returns true if it did, false if it could not add it (e.g. item not supported).
- L117 _public prototype_ `virtual bool RemoveChild(const FNavigationToolRemoveItemParams& InRemoveItemParams) = 0;` — Removes the given child from this Item if it was ever indeed a child. Returns true if the removal did happen.
- L120 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) = 0;` — Finds this items children. This is only relevant for items that do have that functionality (e.g. components or actors)
- L122 _public prototype_ `virtual void FindValidChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) = 0;`
- L125 _public function_ `virtual void GetItemProxies(TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies)` — Gets the Item Proxies for this Item (e.g. Component Item that represent Primitives add in a Material Proxy to display)
- L132 _public prototype_ `virtual TArray<FNavigationToolViewModelPtr> FindPath(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems) const = 0;` — Tries to find the first path of descendants (not including self) that lead to a given item in the set. The last item is the item in the set that was found, so the path might be "A/B/C/.../ItemInSet", where A is the child of This. Returns The empty array if failed.
- L135 _public prototype_ `virtual FString GetFullPath() const = 0;` — Returns the path to this item in the tree. Ex. "RootId,ChildId,ChildId"
- L138 _public prototype_ `virtual const TArray<FNavigationToolViewModelWeakPtr>& GetChildren() const = 0;` — Gets the current Child Items of this item
- L141 _public prototype_ `virtual TArray<FNavigationToolViewModelWeakPtr>& GetChildrenMutable() = 0;` — Gets the current Child Items of this Item
- L148 _public prototype_ `virtual IndexType GetChildIndex(const FNavigationToolViewModelWeakPtr& InWeakChildItem) const = 0;` — Gets the Index that the given Child Item is at. NOTE: This includes HIDDEN items as Item Visibility is relative to each Navigation Tool View. To consider only Visible Items, use FNavigationToolView::GetVisibleChildAt.
- L155 _public prototype_ `virtual FNavigationToolViewModelWeakPtr GetChildAt(const IndexType InIndex) const = 0;` — Gets the Child Item at the given Index. NOTE: This includes HIDDEN items as Item Visibility is relative to each Navigation Tool View. To consider only Visible Items, use FNavigationToolView::GetVisibleChildAt.
- L161 _public prototype_ `virtual FNavigationToolViewModelPtr GetParent() const = 0;` — Gets the Parent of this item. Should only be null prior to registering it in Navigation Tool or if its root item.
- L164 _public prototype_ `virtual TSet<FNavigationToolViewModelPtr> GetParents(const bool bInIncludeRoot = false) const = 0;` — Gets the list of all parents up the tree from this Item
- L167 _public prototype_ `virtual void SetParent(FNavigationToolViewModelPtr InParent) = 0;` — Sets the parent. Note that the parent must've already had this instance as a child (check is done)
- L170 _public prototype_ `virtual FNavigationToolItemId GetItemId() const = 0;` — Gets the Id of this item
- L176 _public prototype_ `virtual bool CanBeTopLevel() const = 0;` — Whether this item can be at the Top Level just beneath the Root, or it needs to always be under some other item E.g. Actors can be Top Level, but Components or Materials can't
- L179 _public prototype_ `virtual bool IsAllowedInTool() const = 0;` — Returns whether this item (and what it represents) should be allowed to be registered in Navigation Tool
- L182 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Gets the display name text of the item
- L185 _public prototype_ `virtual FText GetClassName() const = 0;` — Gets the Class/Type of this Item (e.g. for Items that represent UObjects, it will be the UObject class)
- L188 _public prototype_ `virtual FSlateColor GetItemLabelColor() const = 0;` — Gets the color to use for the item label
- L191 _public prototype_ `virtual FLinearColor GetItemTintColor() const = 0;` — Gets the color to use to tint the entire item row (all column content)
- L194 _public prototype_ `virtual FSlateIcon GetIcon() const = 0;` — Gets the slate icon for the item
- L196 _public function_ `virtual const FSlateBrush* GetDefaultIconBrush() const`
- L198 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const = 0;`
- L201 _public prototype_ `virtual FSlateColor GetIconColor() const = 0;` — Gets the color for the item icon
- L204 _public prototype_ `virtual FText GetIconTooltipText() const = 0;` — Gets the tooltip text for the item icon
- L207 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const = 0;` — Gets the View Modes that this Item Supports
- L210 _public prototype_ `virtual bool IsViewModeSupported(const ENavigationToolItemViewMode InViewMode, const INavigationToolView& InToolView) const = 0;` — Whether this Item should be visualized in the given View Mode, for the given Navigation Tool View
- L217 _public function_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, const bool bInRecursive)` — Called when objects have been replaced on the Engine side. Used to replace any UObjects used by this item @param InReplacementMap the map of old object that is garbage to the new object that replaced it @param bInRecursive     whether to recurse this same function to children items
- L220 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SNavigationToolTreeRow>& InRow) = 0;` — Function responsible of Generating the Label Widget for this Item (i.e. the column containing the Icon and the Name)
- L223 _public prototype_ `virtual bool ShowVisibility() const = 0;` — Whether this Item supports Visibility for the Given Type
- L226 _public prototype_ `virtual bool CanReceiveParentVisibilityPropagation() const = 0;` — Whether a change in Parent Visibility should also affect this Item's Visibility
- L229 _public prototype_ `virtual bool GetVisibility() const = 0;` — Whether this Item is currently visible or not for the Given Type
- L232 _public function_ `virtual void OnVisibilityChanged(const bool bInNewVisibility)` — Called when the Visibility on Item has been changed on the Navigation Tool side
- L245 _public prototype_ `virtual bool CanAutoExpand() const = 0;` — Whether the Item is able to expand when AutoExpand functionality is enabled
- L248 _public prototype_ `virtual bool CanDelete() const = 0;` — Whether this Item can be deleted or not
- L251 _public prototype_ `virtual bool Delete() = 0;` — The implementation to delete the item
- L253 _public prototype_ `virtual void AddFlags(const ENavigationToolItemFlags InFlag) = 0;`
- L254 _public prototype_ `virtual void RemoveFlags(const ENavigationToolItemFlags InFlag) = 0;`
- L256 _public prototype_ `virtual bool HasAnyFlags(const ENavigationToolItemFlags InFlag) const = 0;`
- L257 _public prototype_ `virtual bool HasAllFlags(const ENavigationToolItemFlags InFlag) const = 0;`
- L259 _public prototype_ `virtual void SetFlags(const ENavigationToolItemFlags InFlags) = 0;`
- L260 _public prototype_ `virtual ENavigationToolItemFlags GetFlags() const = 0;`
- L263 _public function_ `virtual TArray<FName> GetTags() const` — Gets the Tags found for this item (e.g. for Actors, actor tags and for Components, component tags)
- L279 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) = 0;` — Determines if and where the incoming Drag Drop Event can be processed by this item
- L282 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) = 0;` — Processes the Drag and Drop Event for this Item
- L285 _public prototype_ `virtual bool IsIgnoringPendingKill() const = 0;` — Whether Ignoring Pending Kill. Useful to get underlying UObjects that are pending kill and get the pointer to it and not a null value
- L288 _public prototype_ `virtual bool IsExpanded() const = 0;` — Gets whether this item is expanded
- L291 _public prototype_ `virtual void SetExpansion(const bool bInIsExpanded) = 0;` — Sets the expansion state of this item
- L294 _public prototype_ `virtual FNavigationToolSerializedItem MakeSerializedItem() = 0;` — Converts this Navigation Tool item to a serialized item that can be saved in the sequence
- L296 _public function_ `FOnRenameAction& OnRenameAction()`
- L298 _public function_ `FOnExpansionChanged& OnExpansionChanged()`
- L302 _protected member_ `FOnExpansionChanged OnExpansionChangedDelegate;` — Delegate for when expansion changes in the item
- L305 _protected member_ `FOnRenameAction OnRenameActionDelegate;` — The delegate for renaming

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExpansionChanged, const TSharedPtr<INavigationToolView>&, bool);`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRenameAction, ENavigationToolRenameAction, const TSharedPtr<INavigationToolView>&);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolActor.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolActor`  
`class FNavigationToolActor : public FNavigationToolBinding`  
_L21-55_
- inherits: `FNavigationToolBinding`
- desc: Navigation Tool Item representing an AActor binding
- L25 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FNavigationToolActor , FNavigationToolBinding) FNavigationToolActor(INavigationTool& InTool , const FNavigationToolViewModelPtr& InParentItem , const TSharedPtr<FNavigationToolSequence>& InParentSequenceItem , const FMovieSceneBinding& InBinding);`
- L35 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L37 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L38 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L39 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L41 _public prototype_ `virtual TArray<FName> GetTags() const override;`
- L43 _public function_ `virtual bool ShowVisibility() const override`
- L44 _public prototype_ `virtual bool GetVisibility() const override;`
- L45 _public prototype_ `virtual void OnVisibilityChanged(const bool bInNewVisibility) override;`
- L50 _public prototype_ `virtual bool CanRename() const override;`
- L51 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L54 _public prototype_ `AActor* GetActor() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolBinding.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolBinding`  
`class FNavigationToolBinding : public FNavigationToolItem , public Sequencer::IRenameableExtension`  
_L30-123_
- inherits: `FNavigationToolItem,Sequencer::IRenameableExtension,IPlayheadExtension,IIdExtension`
- desc: Navigation Tool Item representing a Sequence binding
- L45 _public prototype_ `FNavigationToolBinding(INavigationTool& InTool , const FNavigationToolViewModelPtr& InParentItem , const TSharedPtr<FNavigationToolSequence>& InParentSequenceItem , const FMovieSceneBinding& InBinding);`
- L52 _public prototype_ `virtual bool IsItemValid() const override;`
- L53 _public prototype_ `virtual UObject* GetItemObject() const override;`
- L54 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L56 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L58 _public function_ `virtual bool CanBeTopLevel() const override`
- L59 _public function_ `virtual bool ShouldSort() const override`
- L61 _public prototype_ `virtual FText GetDisplayName() const override;`
- L62 _public prototype_ `virtual FText GetClassName() const override;`
- L63 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L64 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L65 _public prototype_ `virtual FSlateColor GetIconColor() const override;`
- L67 _public prototype_ `virtual bool IsSelected(const FNavigationToolScopedSelection& InSelection) const override;`
- L68 _public prototype_ `virtual void Select(FNavigationToolScopedSelection& InSelection) const override;`
- L69 _public prototype_ `virtual void OnSelect() override;`
- L70 _public prototype_ `virtual void OnDoubleClick() override;`
- L72 _public prototype_ `virtual bool CanDelete() const override;`
- L73 _public prototype_ `virtual bool Delete() override;`
- L75 _public prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`
- L80 _public prototype_ `virtual bool CanRename() const override;`
- L81 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L90 _public prototype_ `virtual FText GetId() const override;`
- L94 _public prototype_ `virtual EItemContainsPlayhead ContainsPlayhead() const override;`
- L97 _public prototype_ `const FMovieSceneBinding& GetBinding() const;`
- L100 _public prototype_ `UMovieSceneSequence* GetSequence() const;` — @return The Sequence this binding belongs to
- L103 _public prototype_ `UMovieScene* GetMovieScene() const;` — @return The Movie Scene this binding belongs to
- L106 _public prototype_ `UObject* GetCachedBoundObject() const;` — @return The cached object that is bound in sequencer.
- L109 _public prototype_ `UObject* CacheBoundObject();` — Caches the object if it's not already been cached and returns the result.
- L111 _public prototype_ `UE::Sequencer::TViewModelPtr<UE::Sequencer::FObjectBindingModel> GetViewModel() const;`
- L114 _protected member_ `Sequencer::TWeakViewModelPtr<FNavigationToolSequence> WeakParentSequenceItem;`
- L116 _protected member_ `FMovieSceneBinding Binding;`
- L118 _protected member_ `TWeakObjectPtr<const UClass> WeakBoundObjectClass;`
- L119 _protected member_ `TWeakObjectPtr<> WeakBoundObject;`
- L121 _protected member_ `FSlateIcon Icon;`
- L122 _protected member_ `FSlateColor IconColor;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolComponent.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolComponent`  
`class FNavigationToolComponent : public FNavigationToolBinding`  
_L18-55_
- inherits: `FNavigationToolBinding`
- desc: Navigation Tool Item representing an Actor Component binding
- L32 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L33 _public prototype_ `virtual void GetItemProxies(TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies) override;`
- L35 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L36 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L37 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L38 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SNavigationToolTreeRow>& InRow) override;`
- L40 _public prototype_ `virtual FLinearColor GetItemTintColor() const override;`
- L41 _public prototype_ `virtual TArray<FName> GetTags() const override;`
- L43 _public function_ `virtual bool ShowVisibility() const override`
- L44 _public prototype_ `virtual bool GetVisibility() const override;`
- L45 _public prototype_ `virtual void OnVisibilityChanged(const bool bInNewVisibility) override;`
- L50 _public prototype_ `virtual bool CanRename() const override;`
- L51 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L54 _public prototype_ `UActorComponent* GetComponent() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolItem.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItem`  
`class FNavigationToolItem : public Sequencer::TOutlinerModelMixin<Sequencer::FViewModel> , public INavigationToolItem , public IColorExtension`  
_L30-187_
- inherits: `Sequencer::TOutlinerModelMixin<Sequencer::FViewModel>,INavigationToolItem,IColorExtension`
- desc: Base implementation of INavigationToolItem
- L38 _public typedef_ `using IndexType = TArray<INavigationToolItem>::SizeType;`
- L48 _public prototype_ `FNavigationToolItem(INavigationTool& InTool, const FNavigationToolViewModelPtr& InParentItem);`
- L52 _public prototype_ `virtual INavigationTool& GetOwnerTool() const final override;`
- L53 _public prototype_ `virtual TSharedPtr<FNavigationToolProvider> GetProvider() const final override;`
- L54 _public prototype_ `virtual FNavigationToolSaveState* GetProviderSaveState() const override;`
- L55 _public prototype_ `virtual bool IsItemValid() const override;`
- L57 _public prototype_ `virtual void RefreshChildren() override;`
- L58 _public prototype_ `virtual void ResetChildren() override;`
- L60 _public function_ `virtual const TArray<FNavigationToolViewModelWeakPtr>& GetChildren() const override`
- L61 _public function_ `virtual TArray<FNavigationToolViewModelWeakPtr>& GetChildrenMutable() override`
- L63 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override;`
- L65 _public prototype_ `virtual void FindValidChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override;`
- L68 _public prototype_ `virtual TArray<FNavigationToolViewModelPtr> FindPath(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems) const override final;`
- L69 _public prototype_ `virtual FString GetFullPath() const override final;`
- L71 _public prototype_ `virtual IndexType GetChildIndex(const FNavigationToolViewModelWeakPtr& InWeakChildItem) const override;`
- L72 _public prototype_ `virtual FNavigationToolViewModelWeakPtr GetChildAt(const IndexType InIndex) const override;`
- L74 _public prototype_ `virtual FNavigationToolViewModelPtr GetParent() const override;`
- L75 _public prototype_ `virtual TSet<FNavigationToolViewModelPtr> GetParents(const bool bInIncludeRoot = false) const override;`
- L76 _public prototype_ `virtual void SetParent(FNavigationToolViewModelPtr InParent) override;`
- L78 _public function_ `virtual bool ShouldSort() const override`
- L80 _public prototype_ `virtual bool CanAddChild(const FNavigationToolViewModelPtr& InChild) const override;`
- L81 _public prototype_ `virtual bool AddChild(const FNavigationToolAddItemParams& InAddItemParams) override;`
- L82 _public prototype_ `virtual bool RemoveChild(const FNavigationToolRemoveItemParams& InRemoveItemParams) override;`
- L84 _public prototype_ `virtual FNavigationToolItemId GetItemId() const override final;`
- L85 _public function_ `virtual bool CanBeTopLevel() const override`
- L86 _public function_ `virtual bool IsAllowedInTool() const override`
- L87 _public function_ `virtual FText GetDisplayName() const override`
- L88 _public function_ `virtual FText GetClassName() const override`
- L90 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L91 _public prototype_ `virtual bool IsViewModeSupported(const ENavigationToolItemViewMode InViewMode, const INavigationToolView& InToolView) const override;`
- L93 _public prototype_ `virtual FSlateColor GetItemLabelColor() const override;`
- L94 _public prototype_ `virtual FLinearColor GetItemTintColor() const override;`
- L95 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L96 _public prototype_ `virtual FSlateColor GetIconColor() const override;`
- L98 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(const TSharedRef<SNavigationToolTreeRow>& InRow) override;`
- L100 _public function_ `virtual bool ShowVisibility() const override`
- L101 _public function_ `virtual bool CanReceiveParentVisibilityPropagation() const override`
- L102 _public function_ `virtual bool GetVisibility() const override`
- L103 _public function_ `virtual bool CanAutoExpand() const override`
- L104 _public function_ `virtual bool CanDelete() const override`
- L105 _public prototype_ `virtual bool Delete() override;`
- L107 _public prototype_ `virtual void AddFlags(ENavigationToolItemFlags Flags) override;`
- L108 _public prototype_ `virtual void RemoveFlags(ENavigationToolItemFlags Flags) override;`
- L109 _public prototype_ `virtual bool HasAnyFlags(ENavigationToolItemFlags Flags) const override;`
- L110 _public prototype_ `virtual bool HasAllFlags(ENavigationToolItemFlags Flags) const override;`
- L111 _public function_ `virtual void SetFlags(ENavigationToolItemFlags InFlags) override`
- L112 _public function_ `virtual ENavigationToolItemFlags GetFlags() const override`
- L114 _public function_ `virtual TArray<FName> GetTags() const override`
- L116 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) override;`
- L117 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, const EItemDropZone InDropZone) override;`
- L119 _public prototype_ `virtual bool IsIgnoringPendingKill() const override final;`
- L121 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, const bool bInRecursive) override;`
- L123 _public prototype_ `virtual bool IsExpanded() const override;`
- L124 _public prototype_ `virtual void SetExpansion(const bool bInExpand) override;`
- L126 _public prototype_ `virtual FNavigationToolSerializedItem MakeSerializedItem() override final;`
- L131 _public prototype_ `virtual TOptional<FColor> GetColor() const override;`
- L132 _public prototype_ `virtual void SetColor(const TOptional<FColor>& InColor) override;`
- L136 _public prototype_ `virtual Sequencer::FOutlinerSizing GetOutlinerSizing() const override;`
- L139 _public function_ `Sequencer::TViewModelPtr<FNavigationToolItem> AsItemViewModel()`
- L145 _public function_ `Sequencer::TViewModelPtr<FNavigationToolItem> AsItemViewModelConst() const`
- L154 _protected prototype_ `void SetProvider(const TWeakPtr<FNavigationToolProvider>& InWeakProvider);`
- L157 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const = 0;` — Gets the Item Id with the latest information (e.g. parent, object, etc)
- L160 _protected prototype_ `void RecalculateItemId();` — Sets the ItemId member var to what CalculateItemId returns
- L163 _protected prototype_ `void AddChildChecked(const FNavigationToolAddItemParams& InAddItemParams);` — The actual implementation of putting the given item under the children array
- L166 _protected prototype_ `bool RemoveChildChecked(const FNavigationToolRemoveItemParams& InRemoveItemParams);` — The actual implementation of removing the given item from the Children array
- L169 _protected prototype_ `void HandleNewSortableChildren(TArray<FNavigationToolViewModelWeakPtr> InWeakSortableChildren);` — Careful handling of multiple children being detected and added to this item children array
- L172 _protected member_ `INavigationTool& Tool;` — Reference to the Owning Navigation Tool
- L175 _protected member_ `TWeakPtr<FNavigationToolProvider> WeakProvider;` — Tool provider that is responsible for the creation of this item
- L178 _protected member_ `FNavigationToolViewModelWeakPtr WeakParent;` — Weak pointer to the Parent Item. Can be null, but if valid, the Parent should have this item in the Children Array
- L181 _protected member_ `TArray<FNavigationToolViewModelWeakPtr> WeakChildren;` — Array of Shared pointers to the Child Items. These Items should have their ParentWeak pointing to this item
- L184 _protected member_ `ENavigationToolItemFlags ItemFlags;` — The current flags set for this item
- L186 _protected member_ `FNavigationToolItemId ItemId;`

#### struct `UE::SequenceNavigator::FNavigationToolItemFlagGuard`  
`struct FNavigationToolItemFlagGuard`  
_L190-214_
- desc: Adds scoped item flags and removes them when out of scope. Useful for temp checks like IgnorePendingKill
- L192 _public function_ `FNavigationToolItemFlagGuard(const FNavigationToolViewModelPtr& InItem, const ENavigationToolItemFlags InItemFlags)`
- L202 _public function_ `~FNavigationToolItemFlagGuard()`
- L211 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L213 _protected member_ `ENavigationToolItemFlags OldItemFlags;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L45 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FNavigationToolSaveState*, FNavigationToolGetToolState , const FNavigationToolViewModelPtr );`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolItemId.h` (Public)


#### struct `UE::SequenceNavigator::FNavigationToolItemId`  
`struct FNavigationToolItemId`  
_L22-133_
- desc: Struct to identify an item in the Navigation Tool
- L24 _public prototype_ `static FString GetObjectPath(const UObject* const InObject);`
- L26 _public prototype_ `static void AddSeparatedSegment(FString& OutString, const FString& InSegment);`
- L28 _public member_ `static FNavigationToolItemId RootId;`
- L30 _public member_ `static constexpr const TCHAR* Separator = TEXT(",")`
- L33 _public prototype_ `FNavigationToolItemId() = default;` — Default Ctor. Does not run any CalculateTypeHash so this instance remains invalid
- L36 _public prototype_ `FNavigationToolItemId(const FString& InUniqueId);` — More flexible option to just specify the string directly. Could be used for folders (e.g. for a nested folder C could be "A/B/C"
- L53 _public prototype_ `FNavigationToolItemId(const UObject* InObject , const FNavigationToolViewModelPtr& InReferencingItem , const FString& InReferencingId);` — Ctor used for Objects that are expected to appear multiple times in the Navigation Tool (e.g. a Material Ref) Example Id #1: [Component Path], [Full Path of Material Asset], [Slot Index] "/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent,/Game/Materials/M_TestMaterial.M_TestMaterial,[Slot 0]" Example Id #2: [Component Path], [Material Instance Dynamic Path], [Slot Index] "/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent,/Game/World.World:PersistentLevel.StaticMeshActor_0.StaticMeshComponent.MaterialInstanceDynamic_0,[Slot 0]" @param InObject The Object being referenced multiple times (e.g. a Material) @param InReferencingItem The Item holding a reference to the object (e.g. a Primitive Comp referencing a Material) @param InReferencingId The Id to differentiate this reference from other references within the same object (e.g. can be slot or property name)
- L63 _public prototype_ `FNavigationToolItemId(const FNavigationToolViewModelPtr& InParentItem , const INavigationToolItemProxyFactory& InItemProxyFactory);` — Ctor used for making the Item Id for an item proxy that will be under the given Parent Item. Used when the actual Item Proxy is not created yet, but know it's factory and want to know whether the item proxy already exists @param InParentItem The parent item holding the item proxy @param InItemProxyFactory The factory responsible for creating the item proxy
- L71 _public prototype_ `FNavigationToolItemId(const FNavigationToolViewModelPtr& InParentItem , const FNavigationToolViewModelPtr& InItemProxy);` — Ctor used for making the Item Id for an Item Proxy under the given Parent Item. @param InParentItem The parent item holding the item proxy @param InItemProxy The item proxy under the parent item
- L82 _public prototype_ `FNavigationToolItemId(const FNavigationToolViewModelPtr& InParentItem , const UMovieSceneSequence* const InSequence , const UMovieSceneSection* const InSection = nullptr , const int32 InSectionIndex = 0 , const FString& InReferenceId = FString());` — Ctor used for making the Item Id for most sequence items @param InParentItem The parent item holding the item proxy @param InSequence The parent sequence object @param InSection The parent section this sequence belongs to, if any @param InSectionIndex The parent section index, if any. Should be specified if InSection is used. @param InReferenceId The optional additional reference string
- L92 _public prototype_ `FNavigationToolItemId(const UE::Sequencer::FViewModelPtr& InViewModel);` — Ctor used for making the Item Id from a Sequencer view model @param InViewModel The view model to construct the Id from
- L94 _public prototype_ `FNavigationToolItemId(const FNavigationToolItemId& Other);`
- L95 _public prototype_ `FNavigationToolItemId(FNavigationToolItemId&& Other) noexcept;`
- L97 _public prototype_ `FNavigationToolItemId& operator=(const FNavigationToolItemId& Other);`
- L98 _public prototype_ `FNavigationToolItemId& operator=(FNavigationToolItemId&& Other) noexcept;`
- L100 _public prototype_ `bool operator==(const FNavigationToolItemId& Other) const;`
- L108 _public prototype_ `bool IsValidId() const;` — Returns whether this Id has a cached hash (i.e. ran any ctor except the default one)
- L110 _public prototype_ `FString GetStringId() const;`
- L121 _private prototype_ `void ConstructId(const FNavigationToolViewModelPtr& InParentItem , const UMovieSceneSequence* const InSequence , const UMovieSceneSection* const InSection = nullptr , const int32 InSectionIndex = 0 , const FString& InReferenceId = FString());` — Constructs an Item Id for most sequence items @param InParentItem The parent item holding the item proxy @param InSequence The parent sequence object @param InSection The parent section this sequence belongs to, if any @param InSectionIndex The parent section index, if any. Should be specified if InSection is used. @param InReferenceId The optional additional reference string
- L127 _private prototype_ `void CalculateTypeHash();`
- L129 _private member_ `FString Id;`
- L131 _private member_ `uint32 CachedHash = 0;`
- L132 _private member_ `bool bHasCachedHash = false;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L102 _function_ `friend uint32 GetTypeHash(const FNavigationToolItemId& InItemId)` (scope `UE::SequenceNavigator`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolItemParameters.h` (Public)


#### enum `UE::SequenceNavigator::ENavigationToolAddItemFlags`  
`enum class ENavigationToolAddItemFlags : uint8`  
_L15-24_
- L17 _public enumerator_ `None = 0`
- L19 _public enumerator_ `AddChildren = 1 << 0` — Also add the children of the given item even if they were not made into their own Add Item Action
- L21 _public enumerator_ `Select = 1 << 1` — Select this Item on Add
- L23 _public enumerator_ `Transact = 1 << 2` — Make a Transaction for this Action

#### struct `UE::SequenceNavigator::FNavigationToolAddItemParams`  
`struct FNavigationToolAddItemParams`  
_L27-54_
- L29 _public function_ `FNavigationToolAddItemParams(const FNavigationToolViewModelPtr& InItem = nullptr , const ENavigationToolAddItemFlags InFlags = ENavigationToolAddItemFlags::None , const FNavigationToolViewModelPtr& InRelativeItem = nullptr , const TOptional<EItemDropZone>& InRelativeDropZone = TOptional<EItemDropZone>()) : WeakItem(InItem) , WeakRelativeItem(InRelativeItem) , RelativeDropZone(InRelativeDropZone) , Flags(InFlags) , SelectionFlags(ENavigationToolItemSelectionFlags::None)`
- L41 _public member_ `FNavigationToolViewModelWeakPtr WeakItem;` — The Item to Add
- L44 _public member_ `FNavigationToolViewModelWeakPtr WeakRelativeItem;` — The Item to use as base in where to place the Item
- L47 _public member_ `TOptional<EItemDropZone> RelativeDropZone;` — The Placement Order from the Relative Item (Onto/Inside, Above, Below)
- L50 _public member_ `ENavigationToolAddItemFlags Flags;` — Some Extra Flags for what to do when Adding or After Adding the Items
- L53 _public member_ `ENavigationToolItemSelectionFlags SelectionFlags;` — Flags to Indicate how we should Select the Item. This only applies if bool bSelectItem is true

#### struct `UE::SequenceNavigator::FNavigationToolRemoveItemParams`  
`struct FNavigationToolRemoveItemParams`  
_L56-63_
- L58 _public function_ `FNavigationToolRemoveItemParams(const FNavigationToolViewModelPtr& InItem = nullptr) : WeakItem(InItem)`
- L62 _public member_ `FNavigationToolViewModelWeakPtr WeakItem;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L25 _prototype_ `ENUM_CLASS_FLAGS(ENavigationToolAddItemFlags);` (scope `UE::SequenceNavigator`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolItemProxy.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolItemProxy`  
`class FNavigationToolItemProxy : public FNavigationToolItem`  
_L25-60_
- inherits: `FNavigationToolItem`
- desc: Item Proxies are Navigation Tool Items that with the sole purpose to group and hold common items together. The description or name of such commonality between these items should be the name of the Proxy that holds them. NOTE: Although Item proxies by default require a parent to be visible in Navigation Tool, they can be created without a parent as a means to override behavior (e.g. DisplayName, Icon, etc)
- L35 _public prototype_ `virtual bool IsItemValid() const override;`
- L36 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive) override final;`
- L38 _public prototype_ `virtual void SetParent(FNavigationToolViewModelPtr InParent) override;`
- L39 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L40 _public prototype_ `virtual bool CanAutoExpand() const override;`
- L41 _public function_ `virtual FText GetClassName() const override`
- L44 _public function_ `uint32 GetPriority() const`
- L45 _public function_ `void SetPriority(const uint32 InPriority)`
- L48 _public prototype_ `virtual void GetProxiedItems(const FNavigationToolViewModelPtr& InParent , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) = 0;` — Gets the items that this item proxy is representing / holding (ie. children)
- L53 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`
- L59 _private member_ `uint32 Priority = 0;` — This item proxy's order priority (ie. Highest priority is placed topmost or leftmost (depending on Orientation). Priority 0 is the lowest priority.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolItemUtils.h` (Public)


#### enum `UE::SequenceNavigator::ItemUtils::ENavigationToolCompareState`  
`enum class ENavigationToolCompareState`  
_L61-66_
- desc: The result of an item comparison
- L63 _public enumerator_ `NoneTrue = 0`
- L64 _public enumerator_ `AllTrue = 1 << 0`
- L65 _public enumerator_ `PartialTrue = 1 << 1`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L24 _namespace_ `namespace ItemUtils` (scope `UE::SequenceNavigator`)
- L31 _prototype_ `bool CompareToolItemOrder(const FNavigationToolViewModelPtr& InA, const FNavigationToolViewModelPtr& InB);` (scope `UE::SequenceNavigator::ItemUtils`) — Compares the absolute order of the items in the Navigation Tool and returns true if A comes before B in the Navigation Tool. Useful to use when sorting items.
- L34 _prototype_ `void SplitSortableAndUnsortableItems(const TArray<FNavigationToolViewModelWeakPtr>& InWeakItems , TArray<FNavigationToolViewModelWeakPtr>& OutWeakSortable , TArray<FNavigationToolViewModelWeakPtr>& OutWeakUnsortable);` (scope `UE::SequenceNavigator::ItemUtils`) — Returns two subset arrays of Items: one is containing only Sortable Items and the other Non Sortable Items
- L39 _prototype_ `UMovieSceneSubSection* GetSequenceItemSubSection(const FNavigationToolViewModelPtr& InItem);` (scope `UE::SequenceNavigator::ItemUtils`)
- L42 _prototype_ `UMovieSceneMetaData* GetSequenceItemMetaData(const FNavigationToolViewModelPtr& InItem);` (scope `UE::SequenceNavigator::ItemUtils`)
- L49 _prototype_ `void RemoveSequenceDisplayNameParentPrefix(FText& InOutDisplayName , const Sequencer::TViewModelPtr<FNavigationToolSequence>& InSequenceItem);` (scope `UE::SequenceNavigator::ItemUtils`) — Removes the parent sequence prefix from the display name of a child sequence item. @param InOutDisplayName The display name to modify, which will have the parent prefix removed if found. @param InSequenceItem The child sequence item whose display name is being adjusted.
- L58 _prototype_ `void AppendSequenceDisplayNameDirtyStatus(FText& InOutDisplayName, const UMovieSceneSequence& InSequence);` (scope `UE::SequenceNavigator::ItemUtils`) — Appends the dirty symbol to the given display name. If the associated package is dirty, a "*" tag is appended to the display name. @param InOutDisplayName The display name to be appended with the status. @param InSequence The sequence whose package is checked for a dirty status.
- L67 _function_ `ENUM_CLASS_FLAGS(ENavigationToolCompareState) template<typename InItemType> ENavigationToolCompareState CompareChildrenItemState(const FNavigationToolViewModelPtr& InItem , const TFunctionRef<bool(const Sequencer::TViewModelPtr<InItemType>)>& InTrueFunction , const TFunctionRef<bool(const Sequencer::TViewModelPtr<InItemType>)>& InFalseFunction , const ENavigationToolCompareState InDefaultState = ENavigationToolCompareState::NoneTrue)` (scope `UE::SequenceNavigator::ItemUtils`)
- L102 _function_ `` (scope `UE::SequenceNavigator::ItemUtils::ENUM_CLASS_FLAGS`)
- L133 _function_ `template<typename InItemType> ENavigationToolCompareState CompareChildrenItemStateSimple(const FNavigationToolViewModelPtr& InItem , const TFunctionRef<bool(const InItemType* const)>& InTrueFunction)` (scope `UE::SequenceNavigator::ItemUtils`) — Evaluates an items children based on a predicate function and determines whether all, none, or some of the children match the condition. @param InItem The item which to evaluate the children of. @param InTrueFunction A function that defines the true condition. @return ENavigationToolCompareState::AllTrue if all items satisfy the condition ENavigationToolCompareState::NoneTrue if no items satisfy the condition ENavigationToolCompareState::PartialTrue if some items satisfy the condition
- L153 _function_ `` (scope `UE::SequenceNavigator::ItemUtils::CompareChildrenItemStateSimple`)
- L185 _function_ `template<typename InItemType> ENavigationToolCompareState CompareArrayState(const TArray<InItemType*>& InArray , const TFunctionRef<bool(const InItemType* const)>& InTrueFunction , const TFunctionRef<bool(const InItemType* const)>& InFalseFunction)` (scope `UE::SequenceNavigator::ItemUtils`) — Evaluates the state of items in an array based on a predicate function and determines whether all, none, or some of the items match the condition. @param InArray The array of items to evaluate. @param InTrueFunction A function that defines the true condition. @param InFalseFunction A function that defines the false condition. @return ENavigationToolCompareState::AllTrue if all items satisfy the condition ENavigationToolCompareState::NoneTrue if no items satisfy the condition ENavigationToolCompareState::PartialTrue if some items satisfy the condition
- L196 _function_ `` (scope `UE::SequenceNavigator::ItemUtils::CompareArrayState`)
- L227 _function_ `template<typename InItemType> ENavigationToolCompareState CompareArrayStateSimple(const TArray<InItemType*>& InArray , const TFunctionRef<bool(const InItemType* const)>& InTrueFunction)` (scope `UE::SequenceNavigator::ItemUtils`) — Evaluates the state of items in an array based on a predicate function and determines whether all, none, or some of the items match the condition. @param InArray The array of items to evaluate. @param InTrueFunction A function that defines the true condition. @return ENavigationToolCompareState::AllTrue if all items satisfy the condition ENavigationToolCompareState::NoneTrue if no items satisfy the condition ENavigationToolCompareState::PartialTrue if some items satisfy the condition
- L237 _function_ `` (scope `UE::SequenceNavigator::ItemUtils::CompareArrayStateSimple`)
- L258 _prototype_ `FSlateColor GetItemBindingColor(const ISequencer& InSequencer , UMovieSceneSequence& InSequence , const FGuid& InObjectGuid , const FSlateColor& DefaultColor = FSlateColor::UseForeground());` (scope `UE::SequenceNavigator::ItemUtils`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolMarker.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolMarker`  
`class FNavigationToolMarker : public FNavigationToolItem , public Sequencer::IRenameableExtension , public IInTimeExtension`  
_L23-88_
- inherits: `FNavigationToolItem,Sequencer::IRenameableExtension,IInTimeExtension`
- desc: Navigation Tool Item representing a sequence marker
- L41 _public prototype_ `virtual bool IsItemValid() const override;`
- L42 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L44 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L46 _public prototype_ `virtual FText GetDisplayName() const override;`
- L47 _public prototype_ `virtual FText GetClassName() const override;`
- L48 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L49 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L50 _public prototype_ `virtual FSlateColor GetIconColor() const override;`
- L51 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L53 _public prototype_ `virtual bool IsSelected(const FNavigationToolScopedSelection& InSelection) const override;`
- L54 _public prototype_ `virtual void Select(FNavigationToolScopedSelection& InSelection) const override;`
- L55 _public prototype_ `virtual void OnSelect() override;`
- L56 _public prototype_ `virtual void OnDoubleClick() override;`
- L58 _public prototype_ `virtual bool CanDelete() const override;`
- L59 _public prototype_ `virtual bool Delete() override;`
- L64 _public prototype_ `virtual bool CanRename() const override;`
- L65 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L69 _public prototype_ `virtual FFrameNumber GetInTime() const override;`
- L70 _public prototype_ `virtual void SetInTime(const FFrameNumber& InTime) override;`
- L73 _public prototype_ `int32 GetMarkedFrameIndex() const;`
- L75 _public prototype_ `FMovieSceneMarkedFrame* GetMarkedFrame() const;`
- L79 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`
- L82 _protected prototype_ `UMovieSceneSequence* GetParentSequence() const;`
- L83 _protected prototype_ `UMovieScene* GetParentMovieScene() const;`
- L85 _protected member_ `Sequencer::TWeakViewModelPtr<FNavigationToolSequence> WeakParentSequenceItem;`
- L87 _protected member_ `int32 MarkedFrameIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolSequence.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolSequence`  
`class FNavigationToolSequence : public FNavigationToolItem , public Sequencer::IRenameableExtension , public Sequencer::IDeactivatableExtension , public Sequencer::ILockableExtension , public IMarkerVisibilityExtension , public IRevisionControlExtension , public IPlayheadExtension , public IIdExtension , public IInTimeExtension , public IOutTimeExtension`  
_L35-164_
- inherits: `FNavigationToolItem,Sequencer::IRenameableExtension,Sequencer::IDeactivatableExtension,Sequencer::ILockableExtension,IMarkerVisibilityExtension,IRevisionControlExtension,IPlayheadExtension,IIdExtension,IInTimeExtension,IOutTimeExtension`
- desc: Item in Navigation Tool representing a Sequence.
- L68 _public prototype_ `virtual bool IsItemValid() const override;`
- L69 _public prototype_ `virtual UObject* GetItemObject() const override;`
- L70 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L72 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L73 _public prototype_ `virtual void GetItemProxies(TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies) override;`
- L75 _public prototype_ `virtual bool AddChild(const FNavigationToolAddItemParams& InAddItemParams) override;`
- L76 _public prototype_ `virtual bool RemoveChild(const FNavigationToolRemoveItemParams& InRemoveItemParams) override;`
- L78 _public prototype_ `virtual ENavigationToolItemViewMode GetSupportedViewModes(const INavigationToolView& InToolView) const override;`
- L79 _public function_ `virtual bool CanBeTopLevel() const override`
- L81 _public prototype_ `virtual FText GetDisplayName() const override;`
- L82 _public prototype_ `virtual FText GetClassName() const override;`
- L83 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L84 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L86 _public prototype_ `virtual bool IsSelected(const FNavigationToolScopedSelection& InSelection) const override;`
- L87 _public prototype_ `virtual void Select(FNavigationToolScopedSelection& InSelection) const override;`
- L89 _public prototype_ `virtual void OnSelect() override;`
- L90 _public prototype_ `virtual void OnDoubleClick() override;`
- L92 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bInRecursive) override;`
- L97 _public prototype_ `virtual bool CanRename() const override;`
- L98 _public prototype_ `virtual void Rename(const FText& InNewName) override;`
- L102 _public prototype_ `virtual bool IsDeactivated() const override;`
- L103 _public prototype_ `virtual void SetIsDeactivated(const bool bInIsDeactivated) override;`
- L107 _public prototype_ `virtual Sequencer::ELockableLockState GetLockState() const override;`
- L108 _public prototype_ `virtual void SetIsLocked(const bool bInIsLocked) override;`
- L112 _public prototype_ `virtual EItemMarkerVisibility GetMarkerVisibility() const override;`
- L113 _public prototype_ `virtual void SetMarkerVisibility(const bool bInVisible) override;`
- L117 _public prototype_ `virtual TOptional<FColor> GetColor() const override;`
- L118 _public prototype_ `virtual void SetColor(const TOptional<FColor>& InColor) override;`
- L122 _public prototype_ `virtual FText GetId() const override;`
- L126 _public prototype_ `virtual EItemRevisionControlState GetRevisionControlState() const override;`
- L127 _public prototype_ `virtual const FSlateBrush* GetRevisionControlStatusIcon() const override;`
- L128 _public prototype_ `virtual FText GetRevisionControlStatusText() const override;`
- L132 _public prototype_ `virtual EItemContainsPlayhead ContainsPlayhead() const override;`
- L136 _public prototype_ `virtual FFrameNumber GetInTime() const override;`
- L137 _public prototype_ `virtual void SetInTime(const FFrameNumber& InTime) override;`
- L141 _public prototype_ `virtual FFrameNumber GetOutTime() const override;`
- L142 _public prototype_ `virtual void SetOutTime(const FFrameNumber& InTime) override;`
- L145 _public prototype_ `UMovieSceneSequence* GetSequence() const;`
- L147 _public prototype_ `UMovieSceneSubSection* GetSubSection() const;`
- L148 _public prototype_ `int32 GetSubSectionIndex() const;`
- L150 _public prototype_ `UMovieScene* GetSequenceMovieScene() const;`
- L152 _public prototype_ `TArray<FMovieSceneBinding> GetSortedBindings() const;`
- L154 _public prototype_ `Sequencer::TViewModelPtr<Sequencer::FSectionModel> GetViewModel() const;`
- L158 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`
- L161 _protected member_ `TWeakObjectPtr<UMovieSceneSubSection> WeakSubSection;`
- L162 _protected member_ `int32 SubSectionIndex = 0;`
- L163 _protected member_ `TWeakObjectPtr<UMovieSceneSequence> WeakSequence;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Sequencer` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolSubTrack.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolSubTrack`  
`class FNavigationToolSubTrack : public FNavigationToolTrack , public Sequencer::IDeactivatableExtension , public IMarkerVisibilityExtension`  
_L19-54_
- inherits: `FNavigationToolTrack,Sequencer::IDeactivatableExtension,IMarkerVisibilityExtension`
- L38 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L39 _public prototype_ `virtual TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L40 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone) override;`
- L43 _public prototype_ `UMovieSceneSubTrack* GetSubTrack() const;`
- L46 _public prototype_ `virtual bool IsDeactivated() const override;`
- L47 _public prototype_ `virtual void SetIsDeactivated(const bool bInIsDeactivated) override;`
- L51 _public prototype_ `virtual EItemMarkerVisibility GetMarkerVisibility() const override;`
- L52 _public prototype_ `virtual void SetMarkerVisibility(const bool bInVisible) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Items/NavigationToolTrack.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolTrack`  
`class FNavigationToolTrack : public FNavigationToolItem , public Sequencer::ILockableExtension , public IPlayheadExtension`  
_L26-100_
- inherits: `FNavigationToolItem,Sequencer::ILockableExtension,IPlayheadExtension`
- L46 _public prototype_ `virtual bool IsItemValid() const override;`
- L47 _public prototype_ `virtual UObject* GetItemObject() const override;`
- L48 _public prototype_ `virtual bool IsAllowedInTool() const override;`
- L50 _public prototype_ `virtual void FindChildren(TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren, const bool bInRecursive) override;`
- L52 _public function_ `virtual bool CanBeTopLevel() const override`
- L54 _public prototype_ `virtual FText GetDisplayName() const override;`
- L55 _public prototype_ `virtual FText GetClassName() const override;`
- L56 _public prototype_ `virtual const FSlateBrush* GetDefaultIconBrush() const override;`
- L57 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L58 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L60 _public prototype_ `virtual bool IsSelected(const FNavigationToolScopedSelection& InSelection) const override;`
- L61 _public prototype_ `virtual void Select(FNavigationToolScopedSelection& InSelection) const override;`
- L63 _public prototype_ `virtual void OnSelect() override;`
- L64 _public prototype_ `virtual void OnDoubleClick() override;`
- L66 _public prototype_ `virtual void OnObjectsReplaced(const TMap<UObject*, UObject*>& InReplacementMap, bool bInRecursive) override;`
- L71 _public prototype_ `virtual Sequencer::ELockableLockState GetLockState() const override;`
- L72 _public prototype_ `virtual void SetIsLocked(const bool bInIsLocked) override;`
- L76 _public prototype_ `virtual EItemContainsPlayhead ContainsPlayhead() const override;`
- L79 _public prototype_ `UMovieSceneTrack* GetTrack() const;`
- L81 _public prototype_ `UMovieSceneSequence* GetSequence() const;`
- L82 _public prototype_ `UMovieSceneSection* GetSection() const;`
- L83 _public prototype_ `int32 GetSectionIndex() const;`
- L85 _public prototype_ `UE::Sequencer::TViewModelPtr<UE::Sequencer::FTrackModel> GetViewModel() const;`
- L89 _protected prototype_ `virtual FNavigationToolItemId CalculateItemId() const override;`
- L92 _protected prototype_ `void OnTrackObjectChanged();`
- L94 _protected member_ `TWeakObjectPtr<UMovieSceneSequence> WeakSequence;`
- L95 _protected member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L96 _protected member_ `int32 SectionIndex = 0;`
- L97 _protected member_ `TWeakObjectPtr<UMovieSceneTrack> WeakTrack;`
- L99 _protected member_ `FSlateIcon Icon;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Menus/NavigationToolFilterBarContext.h` (Public)


#### class `UNavigationToolFilterBarContext`  
`class UNavigationToolFilterBarContext : public UObject`  
_L14-33_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public function_ `void Init(const TWeakPtr<UE::SequenceNavigator::INavigationToolFilterBar>& InFilterBarWeak)`
- L24 _public function_ `TSharedPtr<UE::SequenceNavigator::INavigationToolFilterBar> GetFilterBar() const`
- L29 _public member_ `FOnPopulateFilterBarMenu OnPopulateMenu;`
- L32 _protected member_ `TWeakPtr<UE::SequenceNavigator::INavigationToolFilterBar> WeakFilterBar;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateFilterBarMenu, UToolMenu*);`
- L11 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateFilterBarMenu, UToolMenu*);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Menus/NavigationToolFilterMenu.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolFilterMenu`  
`class FNavigationToolFilterMenu : public TSharedFromThis<FNavigationToolFilterMenu>`  
_L19-57_
- inherits: `TSharedFromThis<FNavigationToolFilterMenu>`
- L22 _public prototype_ `static TSharedRef<SWidget> ConstructCustomMenuItemWidget(const TAttribute<FText>& InItemText , const FSimpleDelegate& InOnItemClicked , const TAttribute<ECheckBoxState>& InIsChecked , const FSlateBrush* const InButtonImage , const FSimpleDelegate& InOnButtonClicked , const bool bInRadioButton = false);`
- L29 _public prototype_ `TSharedRef<SWidget> CreateMenu(const TSharedRef<INavigationToolFilterBar>& InFilterBar);`
- L32 _protected prototype_ `void PopulateMenu(UToolMenu* const InMenu);`
- L34 _protected prototype_ `void PopulateCustomsSection(UToolMenu& InMenu);`
- L35 _protected prototype_ `void PopulateFilterOptionsSection(UToolMenu& InMenu);`
- L36 _protected prototype_ `void PopulateCommonFilterSections(UToolMenu& InMenu);`
- L38 _protected prototype_ `void FillCustomTextFiltersMenu(UToolMenu* const InMenu);`
- L40 _protected prototype_ `void FillFiltersMenuCategory(FToolMenuSection& InOutSection, const TSharedRef<FFilterCategory> InMenuCategory);`
- L41 _protected prototype_ `void FillFiltersMenuCategory(UToolMenu* const InMenu, const TSharedRef<FFilterCategory> InMenuCategory);`
- L43 _protected prototype_ `void OnFilterCategoryClicked(const TSharedRef<FFilterCategory> InMenuCategory);`
- L44 _protected prototype_ `ECheckBoxState GetFilterCategoryCheckedState(const TSharedRef<FFilterCategory> InMenuCategory) const;`
- L46 _protected prototype_ `void OnFilterClicked(const TSharedRef<FNavigationToolFilter> InFilter);`
- L48 _protected prototype_ `void OnCustomTextFilterClicked(const FText InFilterLabel);`
- L49 _protected prototype_ `ECheckBoxState GetCustomTextFilerCheckState(const FText InFilterLabel) const;`
- L50 _protected prototype_ `void OnEditCustomTextFilterClicked(const FText InFilterLabel);`
- L52 _protected prototype_ `bool CanResetFilters() const;`
- L53 _protected prototype_ `void ResetFilters();`
- L56 _private member_ `TWeakPtr<INavigationToolFilterBar> WeakFilterBar;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Menus/NavigationToolFilterMenuContext.h` (Public)


#### class `UNavigationToolFilterMenuContext`  
`class UNavigationToolFilterMenuContext : public UObject`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public function_ `void Init(const TWeakPtr<UE::SequenceNavigator::FNavigationToolFilter>& InFilter)`
- L21 _public function_ `TSharedPtr<UE::SequenceNavigator::FNavigationToolFilter> GetFilter() const`
- L26 _public member_ `FOnPopulateFilterBarMenu OnPopulateMenu;`
- L29 _protected member_ `TWeakPtr<UE::SequenceNavigator::FNavigationToolFilter> WeakFilter;`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Menus/NavigationToolItemMenuContext.h` (Public)


#### class `UNavigationToolItemMenuContext`  
`class UNavigationToolItemMenuContext : public UObject`  
_L18-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L25 _public function_ `void Init(const TWeakPtr<UE::SequenceNavigator::INavigationTool>& InTool , const TArray<UE::Sequencer::TWeakViewModelPtr<UE::SequenceNavigator::INavigationToolItem>>& InWeakItemList)`
- L32 _public function_ `TSharedPtr<UE::SequenceNavigator::INavigationTool> GetTool() const`
- L37 _public function_ `TConstArrayView<UE::Sequencer::TWeakViewModelPtr<UE::SequenceNavigator::INavigationToolItem>> GetItems() const`
- L43 _private member_ `TWeakPtr<UE::SequenceNavigator::INavigationTool> WeakTool;`
- L45 _private member_ `TArray<UE::Sequencer::TWeakViewModelPtr<UE::SequenceNavigator::INavigationToolItem>> WeakItemList;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolDefines.h` (Public)


#### enum `ENavigationToolItemSelectionFlags`  
`enum class ENavigationToolItemSelectionFlags : uint8`  
_L29-40_
- desc: Flags specifying how an Item should be Selected
- L31 _public enumerator_ `None = 0`
- L33 _public enumerator_ `AppendToCurrentSelection = 1 << 0` — Append to the current selection
- L35 _public enumerator_ `SignalSelectionChange = 1 << 1` — Signal selection change (e.g. trigger on selection change delegate)
- L37 _public enumerator_ `IncludeChildren = 1 << 2` — Auto-include the items' children in the selection
- L39 _public enumerator_ `ScrollIntoView = 1 << 3` — Whether to scroll first item into view

#### enum `ENavigationToolIgnoreNotifyFlags`  
`enum class ENavigationToolIgnoreNotifyFlags : uint8`  
_L43-51_
- L45 _public enumerator_ `None = 0`
- L47 _public enumerator_ `Spawn = 1 << 0` — Ignores automatically handling actor spawns, usually so that it is manually handled
- L49 _public enumerator_ `Duplication = 1 << 1` — Ignores automatically handling actor duplications, usually so that it is manually handled
- L50 _public enumerator_ `All = 0xFF`

#### enum `ENavigationToolRenameAction`  
`enum class ENavigationToolRenameAction : uint8`  
_L54-60_
- L56 _public enumerator_ `None`
- L57 _public enumerator_ `Requested`
- L58 _public enumerator_ `Completed`
- L59 _public enumerator_ `Cancelled`

#### enum `ENavigationToolExtensionPosition`  
`enum class ENavigationToolExtensionPosition`  
_L62-66_
- L64 _public enumerator_ `Before`
- L65 _public enumerator_ `After`

#### enum `ENavigationToolDragDropActionType`  
`enum class ENavigationToolDragDropActionType : uint8`  
_L68-72_
- L70 _public enumerator_ `Move`
- L71 _public enumerator_ `Copy`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L17 _typedef_ `using FNavigationToolViewModelPtr = Sequencer::TViewModelPtr<INavigationToolItem>;` (scope `UE::SequenceNavigator`)
- L18 _typedef_ `using FNavigationToolViewModelWeakPtr = Sequencer::TWeakViewModelPtr<INavigationToolItem>;` (scope `UE::SequenceNavigator`)
- L20 _typedef_ `using FNavigationToolSharedPtr = TSharedPtr<Sequencer::TViewModelPtr<INavigationToolItem>::ViewModelType>;` (scope `UE::SequenceNavigator`)
- L21 _typedef_ `using FNavigationToolSharedRef = TSharedRef<Sequencer::TViewModelPtr<INavigationToolItem>::ViewModelType>;` (scope `UE::SequenceNavigator`)
- L23 _prototype_ `FName GetToolBarMenuName();` (scope `UE::SequenceNavigator`)
- L24 _prototype_ `FName GetItemContextMenuName();` (scope `UE::SequenceNavigator`)
- L41 _prototype_ `ENUM_CLASS_FLAGS(ENavigationToolItemSelectionFlags);`
- L52 _prototype_ `ENUM_CLASS_FLAGS(ENavigationToolIgnoreNotifyFlags);`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolEditorSelection.h` (Public)


#### enum `UE::SequenceNavigator::ENavigationToolSelectionSource`  
`enum class ENavigationToolSelectionSource`  
_L18-24_
- L21 _public enumerator_ `Single` — Only consider one USelection Object, closest to the Object Type. E.g. AActor will use SelectedActors
- L23 _public enumerator_ `All` — Consider all USelection Objects in Editor Mode Tools (i.e. SelectedActors, SelectedComponents and SelectedObjects)

#### class `UE::SequenceNavigator::FNavigationToolEditorSelection`  
`class FNavigationToolEditorSelection`  
_L26-109_
- L29 _private typedef_ `template<typename InObjectType, typename InParentObjectType = UObject> using TDerivesFromUObject = typename TEnableIf<TIsDerivedFrom<InObjectType, InParentObjectType>::Value>::Type;`
- L32 _public function_ `FNavigationToolEditorSelection(FEditorModeTools& InModeTools, UObject* InChangedSelection = nullptr) : ModeTools(InModeTools) , ChangedSelectionWeak(InChangedSelection)`
- L41 _public function_ `bool IsValid() const` — Determines this Selection valid either if there's either no Changed Selection (i.e. just handling Mode Tools) or the given Selection Object is one of the 3 in the given Editor Mode Tools
- L49 _public function_ `UObject* GetChangedSelection() const`
- L53 _public function_ `template<typename InObjectType = UObject, typename = TDerivesFromUObject<InObjectType>> USelection* GetSelection() const` — Retrieves the USelection object closest to Object Type
- L73 _public function_ `TArray<InObjectReturnType*> GetSelectedObjects() const`
- L93 _private function_ `template<typename InElementType> TArray<InElementType> GetSelectedObjects(USelection* InSelection) const`
- L105 _private member_ `FEditorModeTools& ModeTools;` — The Mode Tools used to get the USelection instances
- L108 _private member_ `TWeakObjectPtr<UObject> ChangedSelectionWeak;` — The Selection that changed that triggered this FNavigationToolEditorSelection to be instanced. Can be null if nothing changed.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolExtender.h` (Public)


#### enum `UE::SequenceNavigator::ENavigationToolProvidersChangeType`  
`enum class ENavigationToolProvidersChangeType`  
_L18-22_
- L20 _public enumerator_ `Add`
- L21 _public enumerator_ `Remove`

#### class `UE::SequenceNavigator::FNavigationToolExtender`  
`class FNavigationToolExtender : IModularFeature`  
_L38-212_
- inherits: `IModularFeature`
- desc: Singleton class for extending the Sequencer Navigation Tool. This class will watch for Sequencers being created and if a Navigation Tool has been registered for that specific sequencer, it will create a Navigation Tool instance for that Sequencer instance.
- L41 _public prototype_ `static FNavigationToolExtender& Get();`
- L43 _public prototype_ `FNavigationToolExtender();`
- L44 _public prototype_ `virtual ~FNavigationToolExtender();`
- L46 _public prototype_ `static FName GetModularFeatureName();`
- L55 _public prototype_ `static FName GetToolInstanceId(const ISequencer& InSequencer);` — Retrieves the unique name for the provided Sequencer instance. The Navigation Tool instance name is based on its associated sequencer settings object name. This provides a unique instance name for each Sequencer type. @param InSequencer The Sequencer instance for which the name is being retrieved. @return The name of the Navigation Tool instance if available; otherwise, NAME_None.
- L56 _public prototype_ `static FName GetToolInstanceId(const INavigationTool& InTool);`
- L59 _public prototype_ `static TSharedPtr<INavigationTool> FindNavigationTool(const TSharedRef<ISequencer>& InSequencer);` — Find the Navigation Tool instance associated with the given Sequencer instance
- L69 _public prototype_ `static bool RegisterToolProvider(const TSharedRef<ISequencer>& InSequencer , const TSharedRef<FNavigationToolProvider>& InProvider);` — Registers a Navigation Tool provider for a specified Navigation Tool instance. This method ensures that the provider is associated with the given tool and replaces any existing provider with the same identifier, if one exists. @param InSequencer The Sequencer instance to create the Navigation Tool instance for. @param InProvider The Navigation Tool provider being registered. @return True if the provider was successfully registered, false otherwise.
- L78 _public prototype_ `static bool UnregisterToolProvider(const FName InToolId, const FName InProviderId);` — Unregisters a Navigation Tool provider associated with a specific instance and identifier. @param InToolId The Id of the Navigation Tool from which the provider needs to be unregistered. @param InProviderId The identifier of the provider to be unregistered. @return True if the provider was successfully unregistered; false otherwise.
- L81 _public prototype_ `static TSharedPtr<FNavigationToolProvider> FindToolProvider(const FName InToolId, const FName InProviderId);`
- L89 _public prototype_ `static bool FindToolProviders(const FName InToolId , TSet<TSharedRef<FNavigationToolProvider>>& OutProviders);` — Finds the tool providers associated with the given Navigation Tool instance. @param InToolId The Navigation Tool Id for which to find associated providers. @param OutProviders A set that will be populated with the found tool providers as weak pointers. @return True if tool providers were found and populated into OutProviders; otherwise, false.
- L98 _public prototype_ `static void ForEachProvider(const TFunction<bool(const FName InToolId , const TSharedRef<FNavigationToolProvider>& InProvider)>& InPredicate);` — Iterates over each Navigation Tool provider and executes the predicate function. The provided predicate function determines whether the iteration continues or stops. @param InPredicate A function that accepts a reference to an INavigationTool and a shared reference to FNavigationToolProvider. Should return true to continue iteration or false to stop.
- L109 _public prototype_ `static void ForEachToolProvider(const FName InToolId , const TFunction<bool(const TSharedRef<FNavigationToolProvider>& InProvider)>& InPredicate);` — Iterates over each Navigation Tool provider and executes the predicate function associated with the given Navigation Tool instance. The iteration is controlled by the provided predicate function, which determines whether it continues or stops. @param InToolId The Navigation Tool Id whose providers are to be iterated over. @param InPredicate A predicate function that takes a shared reference to a Navigation Tool provider as input. The function should return true to continue iteration or false to stop it.
- L113 _public function_ `static FOnNavigationToolProvidersChanged& OnProvidersChanged()` — Event called when a provider has been added or removed from a tool instance.
- L119 _public function_ `static FOnItemDragDropOpInitialized& OnItemDragDropOpInitialized()` — Event called when the FNavigationToolItemDragDropOp has been created and initialized in FNavigationToolItemDragDropOp::Init.
- L124 _public function_ `static FNavigationToolItemProxyRegistry& GetItemProxyRegistry()`
- L134 _public prototype_ `static FSlateIcon FindOverrideIcon(const FNavigationToolViewModelPtr& InItem);` — Get the custom icon for the item if a customization for it exists. @param InItem The item to find the icon of @return The custom icon for the item if a customization is found, FSlateIcon() otherwise
- L136 _public prototype_ `static bool AnyProviderSupportsSequencer(const FName InToolId, const ISequencer& InSequencer);`
- L156 _protected prototype_ `static TSet<TSharedRef<FNavigationToolProvider>>* FindToolProviders(const FName InToolId);`
- L158 _protected prototype_ `FNavigationToolInstance* FindOrAddToolInstance_Internal(const TSharedRef<ISequencer>& InSequencer);`
- L160 _protected prototype_ `void OnSequencerCreated(const TSharedRef<ISequencer> InSequencer);`
- L161 _protected prototype_ `void OnSequencerActivated(const FName InToolId, FMovieSceneSequenceIDRef InSequenceId);`
- L162 _protected prototype_ `void OnSequencerClosed(const FName InToolId, const TSharedRef<ISequencer> InSequencer);`
- L164 _protected prototype_ `void RegisterOverridenIcon_Internal(const Sequencer::FViewModelTypeID& InItemTypeId, const TSharedRef<INavigationToolIconCustomization>& InIconCustomization);`
- L165 _protected prototype_ `void UnregisterOverriddenIcon_Internal(const Sequencer::FViewModelTypeID& InItemTypeId, const FName& InSpecializationIdentifier);`
- L172 _protected prototype_ `TSharedPtr<INavigationToolIconCustomization> GetCustomizationForItem(const FNavigationToolViewModelPtr& InItem) const;` — Get the customization for the given item if any. @param InItem Item to search the customization for. @return The customization for the item if any; nullptr otherwise.
- L174 _protected member_ `FDelegateHandle SequencerCreatedHandle;`
- L176 _protected prototype_ `static void AddSequencerToolBarExtension(const FNavigationToolInstance& InToolInstance);`
- L177 _protected prototype_ `static void RemoveSequencerToolBarExtension(const FNavigationToolInstance& InToolInstance);`
- L180 _protected member_ `TMap<FName, FNavigationToolInstance> ToolInstances;` — Registered Sequencer types to Navigation Tool instances
- L182 _protected member_ `FOnNavigationToolProvidersChanged ProvidersChangedDelegate;`
- L184 _protected member_ `FOnItemDragDropOpInitialized ItemDragDropOpInitializedDelegate;`
- L186 _protected member_ `FNavigationToolItemProxyRegistry ItemProxyRegistry;`
- L204 _protected function_ `friend uint32 GetTypeHash(const FIconCustomizationKey& InCustomizationKey)`
- L211 _protected member_ `TMap<FIconCustomizationKey, TSharedPtr<INavigationToolIconCustomization>> IconRegistry;`

#### struct `UE::SequenceNavigator::FNavigationToolExtender::FNavigationToolInstance`  
`struct FNavigationToolInstance`  
_L139-154_
- L142 _public member_ `FName ToolId;` — The Sequencer type name to register the provider for
- L144 _public member_ `TSharedPtr<FNavigationTool> Instance;`
- L147 _public member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer instance for this Navigation Tool instance. May be null if the Sequencer is not currently open
- L149 _public member_ `FDelegateHandle ActivateSequenceHandle;`
- L150 _public member_ `FDelegateHandle SequencerClosedHandle;`
- L153 _public member_ `TSet<TSharedRef<FNavigationToolProvider>> Providers;` — List of providers registered to this tool instance

#### struct `UE::SequenceNavigator::FNavigationToolExtender::FIconCustomizationKey`  
`struct FIconCustomizationKey`  
_L189-209_
- desc: Hold the key of the map containing the IconCustomizations
- L193 _public member_ `uint32 ItemTypeId = 0;` — FNavigationToolItemTypeId ItemTypeId = FNavigationToolItemTypeId::Invalid();
- L196 _public member_ `FName CustomizationSpecializationIdentifier;` — Specialization identifier (ex. AvaShapeActor class FName for ActorIcon customization)
- L198 _public function_ `bool operator==(const FIconCustomizationKey& InOther) const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SequenceNavigator` (scope `UE`)
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNavigationToolProvidersChanged , const FName , const TSharedRef<FNavigationToolProvider>& , const ENavigationToolProvidersChangeType );`
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNavigationToolProvidersChanged , const FName , const TSharedRef<FNavigationToolProvider>& , const ENavigationToolProvidersChangeType );` (scope `UE::SequenceNavigator`)
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragDropOpInitialized, FNavigationToolItemDragDropOp&);` — Called when the FNavigationToolItemDragDropOp has been created and Initialized in FNavigationToolItemDragDropOp::Init
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemDragDropOpInitialized, FNavigationToolItemDragDropOp&);` (scope `UE::SequenceNavigator`) — Called when the FNavigationToolItemDragDropOp has been created and Initialized in FNavigationToolItemDragDropOp::Init

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolScopedSelection.h` (Public)


#### enum `UE::SequenceNavigator::ENavigationToolScopedSelectionPurpose`  
`enum class ENavigationToolScopedSelectionPurpose`  
_L19-25_
- L22 _public enumerator_ `Sync` — At the end of the Scope, it will set whatever has been added to the Selected List to be the new Selection
- L24 _public enumerator_ `Read` — Used only to check for whether an Object is Selected or not. Cannot execute "Select"

#### class `UE::SequenceNavigator::FNavigationToolScopedSelection`  
`class FNavigationToolScopedSelection`  
_L28-65_
- desc: Handler to Sync Selection from Navigation Tool to the Sequencer
- L31 _public prototype_ `explicit FNavigationToolScopedSelection(ISequencer& InSequencer , ENavigationToolScopedSelectionPurpose InPurpose = ENavigationToolScopedSelectionPurpose::Read);`
- L34 _public prototype_ `~FNavigationToolScopedSelection();`
- L36 _public prototype_ `void Select(const FGuid& InObjectGuid);`
- L37 _public prototype_ `void Select(UMovieSceneSection* const InSection);`
- L38 _public prototype_ `void Select(UMovieSceneTrack* const InTrack);`
- L39 _public prototype_ `void Select(UMovieSceneSequence* const InSequence , const int32 InMarkedFrameIndex);`
- L42 _public prototype_ `bool IsSelected(const UObject* const InObject) const;`
- L43 _public prototype_ `bool IsSelected(const FGuid& InObjectGuid) const;`
- L44 _public prototype_ `bool IsSelected(UMovieSceneSection* const InSection) const;`
- L45 _public prototype_ `bool IsSelected(UMovieSceneTrack* const InTrack) const;`
- L46 _public prototype_ `bool IsSelected(UMovieSceneSequence* const InSequence , const int32 InMarkedFrameIndex) const;`
- L49 _public prototype_ `ISequencer& GetSequencer() const;`
- L52 _private prototype_ `void SyncSelections();`
- L54 _private member_ `ISequencer& Sequencer;`
- L57 _private member_ `TSet<const UObject*> ObjectsSet;` — All Objects Selected (Sections, Tracks, Objects)
- L59 _private member_ `TArray<FGuid> SelectedObjectGuids;`
- L60 _private member_ `TArray<UMovieSceneSection*> SelectedSections;`
- L61 _private member_ `TArray<UMovieSceneTrack*> SelectedTracks;`
- L62 _private member_ `TMap<UMovieSceneSequence*, TSet<int32>> SelectedMarkedFrames;`
- L64 _private member_ `ENavigationToolScopedSelectionPurpose Purpose;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolSettings.h` (Public)


#### enum `ENavigationToolItemViewMode`  
`enum class ENavigationToolItemViewMode : uint8`  
_L11-22_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: The type of visualization being done to the item
- L13 _public enumerator_ `None = 0 UMETA(Hidden)`
- L16 _public enumerator_ `ItemTree = 1 << 0` — Navigation Tool Tree Hierarchy View of the Items
- L18 _public enumerator_ `HorizontalItemList = 1 << 1` — Flattened Horizontal List of Nested Items shown in the "Items" column
- L21 _public enumerator_ `All = ItemTree | HorizontalItemList` — All the Views

#### struct `FNavigationToolColumnView`  
`struct FNavigationToolColumnView`  
_L26-50_
- reflection: `USTRUCT()`
- L30 _public prototype_ `FNavigationToolColumnView() = default;`
- L31 _public function_ `FNavigationToolColumnView(const FText& InViewName) : ViewName(InViewName)`
- L36 _public member_ `FText ViewName;` — `UPROPERTY()`
- L39 _public member_ `TSet<FName> VisibleColumns;` — `UPROPERTY()`
- L41 _public function_ `bool operator==(const FNavigationToolColumnView& InOtherView) const`

#### class `UNavigationToolSettings`  
`class UNavigationToolSettings : public UDeveloperSettings`  
_L53-181_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta=(DisplayName="Sequence Navigation"))`
- inherits: `UDeveloperSettings`
- L58 _public prototype_ `static void OpenEditorSettings();`
- L60 _public prototype_ `UNavigationToolSettings();`
- L62 _public prototype_ `bool ShouldApplyDefaultColumnView() const;`
- L63 _public prototype_ `void SetApplyDefaultColumnView(const bool bInApplyDefaultColumnView);`
- L65 _public prototype_ `bool ShouldUseShortNames() const;`
- L66 _public prototype_ `void SetUseShortNames(const bool bInUseShortNames);`
- L68 _public prototype_ `bool ShouldUseMutedHierarchy() const;`
- L69 _public prototype_ `void SetUseMutedHierarchy(const bool bInUseMutedHierarchy);`
- L71 _public prototype_ `bool ShouldAutoExpandToSelection() const;`
- L72 _public prototype_ `void SetAutoExpandToSelection(const bool bInAutoExpandToSelection);`
- L74 _public prototype_ `bool ShouldAlwaysShowLockState() const;`
- L75 _public prototype_ `void SetAlwaysShowLockState(const bool bInAlwaysShowLockState);`
- L77 _public prototype_ `ENavigationToolItemViewMode GetItemDefaultViewMode() const;`
- L78 _public prototype_ `ENavigationToolItemViewMode GetItemProxyViewMode() const;`
- L80 _public prototype_ `void ToggleViewModeSupport(ENavigationToolItemViewMode& InOutViewMode, const ENavigationToolItemViewMode InFlags);`
- L81 _public prototype_ `void ToggleItemDefaultViewModeSupport(const ENavigationToolItemViewMode InFlags);`
- L82 _public prototype_ `void ToggleItemProxyViewModeSupport(const ENavigationToolItemViewMode InFlags);`
- L84 _public function_ `TSet<FNavigationToolColumnView>& GetCustomColumnViews()`
- L85 _public prototype_ `FNavigationToolColumnView* FindCustomColumnView(const FText& InColumnViewName);`
- L87 _public function_ `const TSet<FName>& GetEnabledBuiltInFilters() const`
- L88 _public prototype_ `void SetBuiltInFilterEnabled(const FName InFilterName, const bool bInEnabled);`
- L90 _public prototype_ `FSequencerFilterBarConfig& FindOrAddFilterBar(const FName InIdentifier, const bool bInSaveConfig);`
- L91 _public prototype_ `FSequencerFilterBarConfig* FindFilterBar(const FName InIdentifier);`
- L92 _public prototype_ `bool RemoveFilterBar(const FName InIdentifier);`
- L94 _public prototype_ `bool ShouldAutoExpandNodesOnFilterPass() const;`
- L95 _public prototype_ `void SetAutoExpandNodesOnFilterPass(const bool bInAutoExpand);`
- L97 _public prototype_ `bool ShouldUseFilterSubmenusForCategories() const;`
- L98 _public prototype_ `void SetUseFilterSubmenusForCategories(const bool bInUseFilterSubmenusForCategories);`
- L100 _public prototype_ `bool IsFilterBarVisible() const;`
- L101 _public prototype_ `void SetFilterBarVisible(const bool bInVisible);`
- L103 _public prototype_ `EFilterBarLayout GetFilterBarLayout() const;`
- L104 _public prototype_ `void SetFilterBarLayout(const EFilterBarLayout InLayout);`
- L106 _public prototype_ `float GetLastFilterBarSizeCoefficient() const;`
- L107 _public prototype_ `void SetLastFilterBarSizeCoefficient(const float bInSizeCoefficient, const bool bInSaveConfig);`
- L109 _public prototype_ `bool ShouldSyncSelectionToNavigationTool() const;`
- L110 _public prototype_ `void SetSyncSelectionToNavigationTool(const bool bInSync, const bool bInSaveConfig = true);`
- L112 _public prototype_ `bool ShouldSyncSelectionToSequencer() const;`
- L113 _public prototype_ `void SetSyncSelectionToSequencer(const bool bInSync, const bool bInSaveConfig = true);`
- L118 _private member_ `bool bApplyDefaultColumnView = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Applies the default column view set by the provider when a view is loaded
- L122 _private member_ `bool bUseShortNames = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Shortens child item names that contain their parents name as a prefix by excluding it from the displayed child name
- L126 _private member_ `bool bUseMutedHierarchy = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Whether to show the parent of the shown items, even if the parents are filtered out
- L130 _private member_ `bool bAutoExpandToSelection = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Whether to auto expand the hierarchy to show the item when selected
- L134 _private member_ `bool bAlwaysShowLockState = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — Whether to show the lock state always, rather than only showing when the item is locked or hovered
- L138 _private member_ `ENavigationToolItemViewMode ItemDefaultViewMode = ENavigationToolItemViewMode::None;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX", meta=(Bitmask, BitmaskEnum="/Script/Sequencer.ENavigationToolItemViewMode"))` — The View Mode a Non-Actor / Non-Component Item supports by default
- L142 _private member_ `ENavigationToolItemViewMode ItemProxyViewMode = ENavigationToolItemViewMode::None;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX", meta=(Bitmask, BitmaskEnum="/Script/Sequencer.ENavigationToolItemViewMode"))` — The View Mode a Proxy Item supports by default
- L145 _private member_ `TSet<FNavigationToolColumnView> CustomColumnViews;` — `UPROPERTY(Config)`
- L148 _private member_ `TSet<FName> EnabledBuiltInFilters;` — `UPROPERTY(Config)`
- L152 _private member_ `TMap<FName, FSequencerFilterBarConfig> FilterBars;` — `UPROPERTY(Config)` — Saved settings for each unique filter bar instance mapped by instance identifier
- L156 _private member_ `bool bAutoExpandNodesOnFilterPass = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Filtering")` — Automatically expand tracks that pass filters
- L160 _private member_ `bool bUseFilterSubmenusForCategories = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Filtering")` — Display the filter menu categories as submenus instead of sections
- L164 _private member_ `bool bFilterBarVisible = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Filtering")` — Last saved visibility of the filter bar to restore after closed
- L168 _private member_ `EFilterBarLayout LastFilterBarLayout = EFilterBarLayout::Horizontal;` — `UPROPERTY(Config, EditAnywhere, Category = "Filtering")` — Last saved layout orientation of the filter bar to restore after closed
- L172 _private member_ `float LastFilterBarSizeCoefficient = 0.05f;` — `UPROPERTY(Config)` — Last saved size of the filter bar to restore after closed
- L176 _private member_ `bool bSyncSelectionToNavigationTool = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — If true, syncs selections in Sequencer to Navigation Tool
- L180 _private member_ `bool bSyncSelectionToSequencer = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Editor UX")` — If true, syncs selections in Navigation Tool to Sequencer

#### Free symbols / members of external scopes

- L23 _prototype_ `ENUM_CLASS_FLAGS(ENavigationToolItemViewMode);`
- L46 _function_ `friend uint32 GetTypeHash(const FNavigationToolColumnView& InOtherView)`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/NavigationToolStyle.h` (Public)


#### class `FNavigationToolStyle`  
`class FNavigationToolStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FNavigationToolStyle& Get()`
- L16 _public prototype_ `FNavigationToolStyle();`

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Providers/INavigationToolProvider.h` (Public)


#### class `UE::SequenceNavigator::INavigationToolProvider`  
`class INavigationToolProvider : public TSharedFromThis<INavigationToolProvider>`  
_L29-125_
- inherits: `TSharedFromThis<INavigationToolProvider>`
- desc: Provides the Navigation Tool with functionality it is not responsible for.
- L32 _public prototype_ `virtual ~INavigationToolProvider() = default;`
- L35 _public prototype_ `virtual FName GetIdentifier() const = 0;` — @return Unique identifier name used to distinguish this provider from others
- L38 _public prototype_ `virtual TSet<TSubclassOf<UMovieSceneSequence>> GetSupportedSequenceClasses() const = 0;` — Gets the sequence classes that this provider is designed to support
- L41 _public prototype_ `virtual FNavigationToolSaveState* GetSaveState(const INavigationTool& InTool) const = 0;` — @return Saved editor only state data to be restored
- L44 _public prototype_ `virtual void SetSaveState(const INavigationTool& InTool, const FNavigationToolSaveState& InSaveState) const = 0;` — Saves the editor only state data to be restored
- L47 _public function_ `virtual void OnActivate()` — Event called when this provider is activated. A provider is activated when a Sequencer opens a sequence.
- L50 _public function_ `virtual void OnDeactivate()` — Event called when this provider is deactivated. A provider is deactivated when a Sequencer closes.
- L52 _public function_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList)`
- L59 _public function_ `virtual void OnExtendColumns(FNavigationToolColumnExtender& OutExtender)` — Extends the available list of columns that can be displayed in the Navigation Tool instance. Users can override this method to add or modify columns in the Navigation Tool interface. @param OutExtender A reference to the column extender used to register additional custom columns.
- L66 _public function_ `virtual void OnExtendColumnViews(TSet<FNavigationToolColumnView>& OutColumnViews)` — Extends the available list of column views that can be displayed in the Navigation Tool instance. Users can override this method to add or modify column views in the Navigation Tool interface. @param OutColumnViews A set of column views that can be customized by the user.
- L76 _public function_ `virtual void OnExtendItemChildren(INavigationTool& InTool , const FNavigationToolViewModelPtr& InParentItem , TArray<FNavigationToolViewModelWeakPtr>& OutWeakChildren , const bool bInRecursive)` — Extends the children of a specified item in the Navigation Tool instance. Users can override this method to add or manipulate the child items of a given parent item. @param InTool The Navigation Tool instance where the item resides. @param InParentItem The item whose children are to be extended. @param OutWeakChildren The array to which additional child items will be added. @param bInRecursive Indicates whether to recursively find children for the provided item.
- L88 _public function_ `virtual void OnExtendItemProxiesForItem(INavigationTool& InTool , const FNavigationToolViewModelPtr& InItem , TArray<TSharedPtr<FNavigationToolItemProxy>>& OutItemProxies)` — Extends the list of item proxies for a specific item in a Navigation Tool instance. Users can override this method to add or manipulate item proxies associated with a given item. @param InTool The Navigation Tool instance where the item resides. @param InItem The item for which proxies are being extended. @param OutItemProxies The array to which additional item proxies will be added.
- L97 _public function_ `virtual void OnExtendBuiltInFilters(TArray<FNavigationToolBuiltInFilterParams>& OutFilterParams)` — Extends the built-in filters available in the Navigation Tool instance. Users can override this method to add or customize filters in the tool's filtering system. @param OutFilterParams An array to which additional built-in filter parameters will be added.
- L100 _public prototype_ `virtual bool ShouldLockTool() const = 0;` — Determines whether the Navigation Tool should be read-only
- L103 _public prototype_ `virtual bool ShouldHideItem(const FNavigationToolViewModelPtr& InItem) const = 0;` — An extended check to determine whether Item should be hidden in the Navigation Tool
- L106 _public function_ `virtual FText GetDefaultColumnView() const` — @return The name of the default column view to load when this provider is registered
- L109 _public prototype_ `virtual TOptional<EItemDropZone> OnToolItemCanAcceptDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelPtr& InTargetItem) const = 0;` — Determines whether an external Drag Drop event (i.e. not an Navigation Tool one) can be accepted by the Navigation Tool for a given Target Item
- L114 _public prototype_ `virtual FReply OnToolItemAcceptDrop(const FDragDropEvent& InDragDropEvent , const EItemDropZone InDropZone , const FNavigationToolViewModelPtr& InTargetItem) = 0;` — Processes an external Drag Drop event (i.e. not an Navigation Tool one) for a given Target item
- L118 _public prototype_ `virtual void UpdateItemIdContexts(const INavigationTool& InTool) = 0;`
- L121 _public function_ `virtual void NotifyToolItemRenamed(const FNavigationToolViewModelPtr& InItem)` — Event called when an Item has been renamed
- L124 _public function_ `virtual void NotifyToolItemDeleted(const FNavigationToolViewModelPtr& InItem)` — Event called when an Item has been deleted

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Providers/NavigationToolProvider.h` (Public)


#### class `UE::SequenceNavigator::FNavigationToolProvider`  
`class FNavigationToolProvider : public INavigationToolProvider`  
_L22-70_
- inherits: `INavigationToolProvider`
- desc: Base Navigation Tool Provider to extend from
- L27 _public prototype_ `virtual void OnExtendColumnViews(TSet<FNavigationToolColumnView>& OutColumnViews) override;`
- L28 _public prototype_ `virtual void OnExtendBuiltInFilters(TArray<FNavigationToolBuiltInFilterParams>& OutFilterParams) override;`
- L30 _public function_ `virtual bool ShouldLockTool() const override`
- L31 _public function_ `virtual bool ShouldHideItem(const FNavigationToolViewModelPtr& InItem) const override`
- L33 _public prototype_ `virtual void UpdateItemIdContexts(const INavigationTool& InTool) final override;`
- L35 _public prototype_ `virtual TOptional<EItemDropZone> OnToolItemCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) const override;`
- L36 _public prototype_ `virtual FReply OnToolItemAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, const FNavigationToolViewModelPtr& InTargetItem) override;`
- L41 _public prototype_ `FNavigationToolViewSaveState* GetViewSaveState(const INavigationTool& InTool, const int32 InToolViewId) const;` — @return Editor only saved data for a specific view
- L44 _public prototype_ `void EnsureToolViewCount(const INavigationTool& InTool, const int32 InToolViewId);` — Ensure saved editor only data contains an entry for a specific view, creating it if necessary
- L46 _public prototype_ `bool IsSequenceSupported(UMovieSceneSequence* const InSequence) const;`
- L52 _private prototype_ `void Activate(FNavigationTool& InTool);`
- L53 _private prototype_ `void Deactivate(FNavigationTool& InTool);`
- L55 _private prototype_ `void SaveState(FNavigationTool& InTool);`
- L56 _private prototype_ `void LoadState(FNavigationTool& InTool);`
- L58 _private prototype_ `void SaveSerializedTree(FNavigationTool& InTool, const bool bInResetTree);`
- L60 _private prototype_ `void SaveSerializedTreeRecursive(const FNavigationToolViewModelPtr& InParentItem , FNavigationToolSerializedTree& InSerializedTree);`
- L63 _private prototype_ `void LoadSerializedTree(const FNavigationToolViewModelPtr& InParentItem , FNavigationToolSerializedTree* const InSerializedTree);`
- L66 _private prototype_ `void CleanupExtendedColumnViews();`
- L68 _private member_ `TArray<FText> ExtendedColumnViewNames;`
- L69 _private member_ `TArray<FName> ExtendedBuiltInFilterNames;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SEQUENCENAVIGATOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace SequenceNavigator` (scope `UE`)

### `Plugins/Experimental/SequenceNavigator/Source/SequenceNavigator/Public/Widgets/SNavigationToolTreeRow.h` (Public)


#### class `UE::SequenceNavigator::SNavigationToolTreeRow`  
`class SNavigationToolTreeRow : public SMultiColumnTableRow<FNavigationToolViewModelWeakPtr>`  
_L17-54_
- inherits: `SMultiColumnTableRow<FNavigationToolViewModelWeakPtr>`
- L21 _public function_ `SLATE_BEGIN_ARGS(SNavigationToolTreeRow)`
- L22 _public prototype_ `SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FNavigationToolView>& InToolView , const TSharedPtr<SNavigationToolTreeView>& InTreeView , const FNavigationToolViewModelPtr& InItem);`
- L31 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L34 _public function_ `TAttribute<FText> GetHighlightText() const`
- L36 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L37 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent) override;`
- L39 _public prototype_ `TSharedPtr<FNavigationToolView> GetToolView() const;`
- L41 _public function_ `const FTableRowStyle* GetStyle() const`
- L44 _public prototype_ `FReply OnDefaultDrop(const FDragDropEvent& InDragDropEvent) const;` — The default reply if a row did not handle AcceptDrop
- L47 _protected member_ `FNavigationToolViewModelWeakPtr WeakItem;`
- L49 _protected member_ `TWeakPtr<SNavigationToolTreeView> WeakTreeView;`
- L51 _protected member_ `TWeakPtr<FNavigationToolView> WeakToolView;`
- L53 _protected member_ `TAttribute<FText> HighlightText;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SequenceNavigator` (scope `UE`)
