# Editor / SceneOutliner

- module root: `Source/Editor/SceneOutliner`
- headers: 49; symbols: 1653
- symbol kinds: class=37, delegate=38, enum=9, enumerator=37, function=355, macro=24, member=336, namespace=12, prototype=734, struct=53, typedef=15, variable=3
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, Core, CoreUObject, EditorConfig, EditorFramework, EditorWidgets, Engine, InputCore, Slate, SlateCore, SourceControl, SourceControlWindows, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UncontrolledChangelists, UnrealEd, UnsavedAssetsTracker

### `Source/Editor/SceneOutliner/Private/ActorBrowsingModeCommands.h` (Private)


#### class `FActorBrowsingModeCommands`  
`class FActorBrowsingModeCommands : public TCommands<FActorBrowsingModeCommands>`  
_L15-35_
- inherits: `TCommands<FActorBrowsingModeCommands>`
- L20 _public function_ `FActorBrowsingModeCommands() : TCommands<FActorBrowsingModeCommands>( TEXT("ActorBrowsingModeCommands"), NSLOCTEXT("ActorBrowsingModeCommands", "ActorBrowsingModeCommands", "Actor Browsing Mode Commands"), NAME_None, FAppStyle::GetAppStyleSetName() )` — Default constructor.
- L25 _public prototype_ `virtual ~FActorBrowsingModeCommands() = default;`
- L31 _public prototype_ `virtual void RegisterCommands() override;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`

### `Source/Editor/SceneOutliner/Private/ActorBrowsingModeSettings.h` (Private)


#### enum `EActorBrowsingFolderDoubleClickMethod`  
`enum class EActorBrowsingFolderDoubleClickMethod : uint8`  
_L16-23_
- reflection: `UENUM()`
- L19 _public enumerator_ `ToggleExpansion` — Expands / Collapses the folder
- L22 _public enumerator_ `ToggleCurrentFolder` — Marks / unmarks the folder as the Current Folder

#### struct `FActorBrowsingModeConfig`  
`struct FActorBrowsingModeConfig`  
_L26-83_
- reflection: `USTRUCT()`
- L34 _public member_ `bool bHideTemporaryActors = false;` — `UPROPERTY()` — True when the Scene Outliner is hiding temporary/run-time Actors
- L38 _public member_ `bool bShowOnlyActorsInCurrentLevel = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current level
- L42 _public member_ `bool bShowOnlyActorsInCurrentDataLayers = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current data layers
- L46 _public member_ `bool bShowOnlyActorsInCurrentContentBundle = false;` — `UPROPERTY()` — True when the Scene Outliner is showing only Actors that exist in the current content bundle
- L50 _public member_ `bool bShowOnlySelectedActors = false;` — `UPROPERTY()` — True when the Scene Outliner is only displaying selected Actors
- L54 _public member_ `bool bHideActorComponents = true;` — `UPROPERTY()` — True when the Scene Outliner is not displaying Actor Components
- L58 _public member_ `bool bHideLevelInstanceHierarchy = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying LevelInstances
- L62 _public member_ `bool bHideUnloadedActors = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying unloaded actors
- L66 _public member_ `bool bHideEmptyFolders = false;` — `UPROPERTY()` — True when the Scene Outliner is not displaying empty folders
- L70 _public member_ `bool bAlwaysFrameSelection = true;` — `UPROPERTY()` — True when the Scene Outliner updates when an actor is selected in the viewport
- L74 _public member_ `EActorBrowsingFolderDoubleClickMethod FolderDoubleClickMethod = EActorBrowsingFolderDoubleClickMethod::ToggleExpansion;` — `UPROPERTY()` — Specifies the behavior of double click on a folder
- L78 _public member_ `bool bShouldUpdateContentWhileInPIEFocused = false;` — `UPROPERTY()` — True if we want to allow updating content when in PIE with the PIE viewport focused
- L82 _public member_ `bool bCollapseOutlinerTreeOnNewSelection = false;` — `UPROPERTY()` — True if we want to collapse Outliner tree on new selection, except for the item that was just selected

#### class `UActorBrowserConfig`  
`class UActorBrowserConfig : public UEditorConfigBase`  
_L86-101_
- reflection: `UCLASS(EditorConfig="ActorBrowsingMode")`
- inherits: `UEditorConfigBase`
- L92 _public prototype_ `static void Initialize();`
- L93 _public function_ `static UActorBrowserConfig* Get()`
- L96 _public member_ `TMap<FName, FActorBrowsingModeConfig> ActorBrowsers;` — `UPROPERTY(meta=(EditorConfig))`
- L100 _private member_ `static TObjectPtr<UActorBrowserConfig> Instance;`

### `Source/Editor/SceneOutliner/Private/SSourceControlWidget.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SSourceControlWidget>`  
_L10-13_
- L12 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SSourceControlWidget`  
`class SSourceControlWidget : public SLayeredImage`  
_L15-35_
- inherits: `SLayeredImage`
- L18 _public function_ `SLATE_BEGIN_ARGS(SSourceControlWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FSceneOutlinerTreeItemSCC> InItemSourceControl);`
- L26 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L28 _private prototype_ `void UpdateSourceControlState(FSourceControlStatePtr SourceControlState);`
- L29 _private prototype_ `void UpdateUncontrolledChangelistState(TSharedPtr<FUncontrolledChangelistState> UncontrolledChangelistState);`
- L31 _private prototype_ `void UpdateWidget(FSourceControlStatePtr SourceControlState, const TSharedPtr<FUncontrolledChangelistState>& UncontrolledChangelistState);`
- L34 _private member_ `TSharedPtr<FSceneOutlinerTreeItemSCC> ItemSourceControl;` — The object that keeps the source control state for the outliner

### `Source/Editor/SceneOutliner/Private/SceneOutlinerActorInfoColumn.h` (Private)


#### class `FTypeInfoColumn`  
`class FTypeInfoColumn : public ISceneOutlinerColumn`  
_L22-72_
- inherits: `ISceneOutlinerColumn`
- desc: A custom column for the SceneOutliner which is used to display the Class/Type of Actors Note: Used to have support for displaying a variety of details related to Actors, that functionality has been moved FTextInfoColumn (See SceneOutlinerModule::CreateActorInfoColumns)
- L30 _public prototype_ `FTypeInfoColumn( ISceneOutliner& Outliner);` — Constructor
- L32 _public prototype_ `virtual ~FTypeInfoColumn() = default;`
- L34 _public function_ `static FName GetID()`
- L39 _public prototype_ `virtual FName GetColumnID() override;`
- L41 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L43 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget( FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row ) override;`
- L45 _public prototype_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const override;`
- L47 _public prototype_ `virtual bool SupportsSorting() const override;`
- L49 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L54 _public prototype_ `FText GetTextForItem( const TWeakPtr<ISceneOutlinerTreeItem> TreeItem ) const;`
- L58 _private prototype_ `TSharedPtr<SWidget> ConstructClassHyperlink( ISceneOutlinerTreeItem& TreeItem );`
- L60 _private prototype_ `EVisibility GetColumnDataVisibility( bool bIsClassHyperlink ) const;`
- L62 _private prototype_ `FText MakeComboText( ) const;`
- L64 _private prototype_ `FText MakeComboToolTipText( ) const;`
- L66 _private prototype_ `FText GetSelectedMode() const;`
- L71 _private member_ `TWeakPtr< ISceneOutliner > SceneOutlinerWeak;` — Weak reference to the outliner widget that owns our list

### `Source/Editor/SceneOutliner/Private/SceneOutlinerConfig.h` (Private)


#### struct `FSceneOutlinerConfig`  
`struct FSceneOutlinerConfig`  
_L17-30_
- reflection: `USTRUCT()`
- L25 _public member_ `TMap<FName, bool> ColumnVisibilities;` — `UPROPERTY()` — Map to store the visibility of each column
- L29 _public member_ `bool bShouldStackHierarchyHeaders = true;` — `UPROPERTY()` — Whether the hierarchy is pinned at the top of the outliner

#### class `UOutlinerConfig`  
`class UOutlinerConfig : public UEditorConfigBase`  
_L34-49_
- reflection: `UCLASS(EditorConfig="Outliner")`
- inherits: `UEditorConfigBase`
- L40 _public prototype_ `static void Initialize();`
- L41 _public function_ `static UOutlinerConfig* Get()`
- L44 _public member_ `TMap<FName, FSceneOutlinerConfig> Outliners;` — `UPROPERTY(meta=(EditorConfig))`
- L48 _private member_ `static TObjectPtr<UOutlinerConfig> Instance;`

### `Source/Editor/SceneOutliner/Private/SceneOutlinerFilterBar.h` (Private)


#### class `SSceneOutlinerFilterBar`  
`class SSceneOutlinerFilterBar : public SFilterBar< SceneOutliner::FilterBarType >`  
_L8-156_
- inherits: `SFilterBar<SceneOutliner::FilterBarType>`
- L16 _public prototype_ `DECLARE_EVENT_OneParam(SSceneOutlinerFilterBar, FCustomTextFilterEvent, TSharedPtr<SWidget> );` — An event delegate that is executed when a custom text filter has been created/modified/deleted in any SSceneOutlinerFilterBar that is using shared settings.
- L18 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<SceneOutliner::FilterBarType>::FOnFilterChanged;`
- L19 _public typedef_ `using FCompareItemWithClassNames = typename FAssetFilter<SceneOutliner::FilterBarType>::FCompareItemWithClassNames;`
- L20 _public typedef_ `using FCreateTextFilter = typename SBasicFilterBar<SceneOutliner::FilterBarType>::FCreateTextFilter;`
- L22 _public function_ `SLATE_BEGIN_ARGS( SSceneOutlinerFilterBar ) : _FilterBarIdentifier(NAME_None) , _UseDefaultAssetFilters(true)`
- L30 _public prototype_ `SLATE_EVENT( FOnFilterChanged, OnFilterChanged ) SLATE_EVENT( FConvertItemToAssetData, OnConvertItemToAssetData ) SLATE_EVENT( FCompareItemWithClassNames, OnCompareItemWithClassNames ) SLATE_ARGUMENT( TArray<TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>>, CustomFilters) SLATE_ARGUMENT(FName, FilterBarIdentifier) SLATE_ARGUMENT( TArray<TSharedRef<FCustomClassFilterData>>, CustomClassFilters) SLATE_ARGUMENT(bool, UseDefaultAssetFilters) SLATE_ARGUMENT(FCreateTextFilter, CreateTextFilter) SLATE_ARGUMENT(TSharedPtr<SFilterSearchBox>, FilterSearchBox) SLATE_ARGUMENT(bool, UseSharedSettings) SLATE_ARGUMENT(TSharedPtr<FFilterCategory>, CategoryToExpand) SLATE_END_ARGS()` — Delegate for when filters have changed
- L79 _public prototype_ `void AddTypeFilter(const TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>& InFilter, TArrayView<const TSharedPtr<FFilterCategory>> InAdditionalCategories = {});` — Register a filter as a "type filter" so it appears as an entry in the "Type Filters" section of the Add Filter menu rather than under "Other Filters". The filter will appear under its primary category (set in the Filter) and each additional category in the "Add Filter" menu. Toggling from any category activates the same filter instance, providing a shared state.
- L83 _public prototype_ `virtual void PopulateAddFilterMenu(UToolMenu* Menu, TSharedPtr<FFilterCategory> MenuExpansion, FOnFilterAssetType OnFilterAssetType) override;` — Override from the AssetFilterBar to allow non-FCustomClassFilterData to populate the TypeFilter section
- L85 _public prototype_ `virtual void SaveSettings() override;`
- L86 _public prototype_ `virtual void LoadSettings() override;`
- L89 _public prototype_ `virtual void OnCreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool bApplyFilter) override;` — Handler for when a custom text filter is created
- L91 _public prototype_ `virtual void OnModifyCustomTextFilter(const FCustomTextFilterData& InFilterData, TSharedPtr<ICustomTextFilter<SceneOutliner::FilterBarType>> InFilter) override;` — Handler for when a custom text filter is modified
- L93 _public prototype_ `virtual void OnDeleteCustomTextFilter(const TSharedPtr<ICustomTextFilter<SceneOutliner::FilterBarType>> InFilter) override;` — Handler for when a custom text filter is deleted
- L96 _protected prototype_ `virtual UAssetFilterBarContext* CreateAssetFilterBarContext() override;`
- L117 _private prototype_ `void OnExternalCustomTextFilterCreated(TSharedPtr<SWidget> BroadcastingFilterBar);` — Handler for when another Filter Bar using shared settings creates a custom text filter
- L120 _private prototype_ `void LoadCustomTextFilters(const FFilterBarSettings* FilterBarConfig);` — Empty our list of custom text filters, and load from the given config
- L125 _private prototype_ `bool RestoreCustomTextFilterState(const FCustomTextFilterState& InFilterState);` — Find the custom text filter corresponding to the specified state, and restore it's state to what is specified @return True if the filter was restored successfully, false if not
- L127 _private prototype_ `void PopulateTypeFilterMap(const FOnFilterAssetType& OnFilterAssetType, TMap<TSharedPtr<FFilterCategory>, FTypeFilterCategoryEntry>& TypeFilterMap);`
- L130 _private prototype_ `void CreateTypeFiltersMenuSection(UToolMenu* InMenu, TArray<TSharedPtr<FFilterBase<SceneOutliner::FilterBarType>>> InFilters);` — Populate a submenu section from an explicit filter list, bypassing GetCategory() matching.
- L133 _private prototype_ `void TypeFilterCategoryClicked(TArray<TSharedPtr<FFilterBase<SceneOutliner::FilterBarType>>> InFilters);` — Toggle all filters in the explicit list on or off (analogous to FrontendFilterCategoryClicked).
- L136 _private prototype_ `ECheckBoxState IsTypeFilterCategoryChecked(TArray<TSharedPtr<FFilterBase<SceneOutliner::FilterBarType>>> InFilters) const;` — Return the tri-state check state for the category toggle button (analogous to IsFrontendFilterCategoryChecked).
- L140 _private member_ `static FCustomTextFilterEvent CustomTextFilterEvent;` — The event that executes when a custom text filter is created/modified/deleted in any filter list that is using Shared Settings
- L143 _private member_ `static const FName SharedIdentifier;` — An identifier shared by all SSceneOutlinerFilterBars, used to save and load settings common to every instance
- L146 _private member_ `bool bUseSharedSettings;` — Whether this Filter bar wants to load/save from the settings common to all instances
- L148 _private member_ `TSharedPtr<FFilterCategory> CategoryToExpand;`
- L155 _private member_ `TMap<TSharedPtr<FFilterBase<SceneOutliner::FilterBarType>>, TArray<TSharedPtr<FFilterCategory>>> TypeFilters;` — Filters registered via AddTypeFilter, used when building the 'Type Filters' menu section. Can be populated with extra categories registered for specific type filters. PopulateTypeFilterMap distributes each filter across its primary category plus any entries in the value array.

#### struct `SSceneOutlinerFilterBar::FTypeFilterCategoryEntry`  
`struct FTypeFilterCategoryEntry`  
_L103-114_
- desc: Unified representation of a single "Type Filters" menu category. A category may contain FCustomClassFilterData entries, FFilterBase entries, or both.
- L106 _public member_ `FName SectionExtensionHook;` — Extension hook and heading used when this category is rendered as a section or submenu
- L107 _public member_ `FText SectionHeading;`
- L110 _public member_ `TArray<TSharedPtr<FCustomClassFilterData>> Classes;` — Asset class filters managed by the asset filter bar infrastructure
- L113 _public member_ `TArray<TSharedPtr<FFilterBase<SceneOutliner::FilterBarType>>> Filters;` — Type filters managed via AllFrontendFilters

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_EVENT_OneParam(SSceneOutlinerFilterBar, FCustomTextFilterEvent, TSharedPtr<SWidget> );` — An event delegate that is executed when a custom text filter has been created/modified/deleted in any SSceneOutlinerFilterBar that is using shared settings.

### `Source/Editor/SceneOutliner/Private/SceneOutlinerItemLabelColumn.h` (Private)


#### class `FSceneOutlinerItemLabelColumn`  
`class FSceneOutlinerItemLabelColumn : public ISceneOutlinerColumn`  
_L15-46_
- inherits: `ISceneOutlinerColumn`
- desc: A column for the SceneOutliner that displays the item label
- L19 _public function_ `FSceneOutlinerItemLabelColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L21 _public prototype_ `virtual ~FSceneOutlinerItemLabelColumn() = default;`
- L23 _public function_ `static FName GetID()`
- L28 _public prototype_ `virtual FName GetColumnID() override;`
- L30 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L32 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget( FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row ) override;`
- L34 _public prototype_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const override;`
- L36 _public function_ `virtual bool SupportsSorting() const override`
- L38 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L44 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

### `Source/Editor/SceneOutliner/Private/SceneOutlinerPinnedColumn.h` (Private)


#### class `FSceneOutlinerPinnedColumn`  
`class FSceneOutlinerPinnedColumn : public ISceneOutlinerColumn`  
_L15-53_
- inherits: `ISceneOutlinerColumn`
- desc: A column for the SceneOutliner that displays the pin icon
- L32 _public function_ `FSceneOutlinerPinnedColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L34 _public prototype_ `virtual ~FSceneOutlinerPinnedColumn() = default;`
- L36 _public function_ `static FName GetID()`
- L39 _public prototype_ `virtual FName GetColumnID() override;`
- L40 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L41 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L42 _public prototype_ `virtual void Tick(double InCurrentTime, float InDeltaTime) override;`
- L43 _public function_ `virtual bool SupportsSorting() const override`
- L46 _public prototype_ `bool IsItemPinned(const ISceneOutlinerTreeItem& Item) const;`
- L48 _private prototype_ `const FSlateBrush* GetHeaderIcon() const;`
- L49 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`
- L52 _private member_ `FSceneOutlinerPinnedStateCache PinnedStateCache;` — Cached pinned state of items per-frame

#### struct `FSceneOutlinerPinnedColumn::FSceneOutlinerPinnedStateCache`  
`struct FSceneOutlinerPinnedStateCache`  
_L17-30_
- L21 _public prototype_ `bool CheckChildren(const ISceneOutlinerTreeItem& Item) const;` — Recursive over the children and check the pinned state
- L23 _public prototype_ `bool GetPinnedState(const ISceneOutlinerTreeItem& Item) const;` — Get or cache the pinned state of an item
- L26 _public prototype_ `void Empty();` — Clear the cache
- L29 _private member_ `mutable TMap<const ISceneOutlinerTreeItem*, bool> PinnedStateInfo;` — Map of tree item to pinned state

### `Source/Editor/SceneOutliner/Private/SceneOutlinerUnsavedColumn.h` (Private)


#### class `FSceneOutlinerActorUnsavedColumn`  
`class FSceneOutlinerActorUnsavedColumn : public ISceneOutlinerColumn`  
_L15-36_
- inherits: `ISceneOutlinerColumn`
- desc: A column for the SceneOutliner that displays if the actor is unsaved
- L18 _public function_ `FSceneOutlinerActorUnsavedColumn(ISceneOutliner& SceneOutliner) : WeakOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L19 _public prototype_ `virtual ~FSceneOutlinerActorUnsavedColumn() = default;`
- L21 _public function_ `static FName GetID()`
- L22 _public function_ `static FText GetDisplayName()`
- L26 _public prototype_ `virtual FName GetColumnID() override;`
- L27 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L28 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L29 _public function_ `virtual bool SupportsSorting() const override`
- L30 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L35 _private member_ `TWeakPtr<ISceneOutliner> WeakOutliner;`

### `Source/Editor/SceneOutliner/Public/ActorBaseTreeItem.h` (Public)


#### struct `IActorBaseTreeItem`  
`struct IActorBaseTreeItem : ISceneOutlinerTreeItem`  
_L14-23_
- inherits: `ISceneOutlinerTreeItem`
- desc: A tree item that represents an actor, loaded or unloaded
- L17 _public function_ `IActorBaseTreeItem(FSceneOutlinerTreeItemType InType) : ISceneOutlinerTreeItem(InType)`
- L20 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for the base class tree item
- L22 _public prototype_ `virtual const FGuid& GetGuid() const =0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/ActorBrowsingMode.h` (Public)


#### class `FActorBrowsingMode`  
`class FActorBrowsingMode : public FActorModeInteractive`  
_L12-197_
- inherits: `FActorModeInteractive`
- L15 _public prototype_ `FActorBrowsingMode(SSceneOutliner* InSceneOutliner, TWeakObjectPtr<UWorld> InSpecifiedWorldToDisplay = nullptr);`
- L16 _public prototype_ `virtual ~FActorBrowsingMode();`
- L19 _public prototype_ `virtual void Rebuild() override;` — Begin ISceneOutlinerMode Interface
- L20 _public prototype_ `virtual FCreateSceneOutlinerMode CreateFolderPickerMode(const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject()) const override;`
- L21 _public prototype_ `virtual void InitializeViewMenuExtender(TSharedPtr<FExtender> Extender) override;`
- L22 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L23 _public prototype_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item) override;`
- L24 _public prototype_ `virtual void OnItemRemoved(FSceneOutlinerTreeItemPtr Item) override;`
- L25 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L26 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L27 _public prototype_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType) override;`
- L28 _public prototype_ `virtual void OnItemPassesFilters(const ISceneOutlinerTreeItem& Item) override;`
- L29 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L30 _public prototype_ `virtual void OnDuplicateSelected() override;`
- L31 _public prototype_ `virtual bool HasCustomFolderDoubleClick() const override;`
- L32 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L33 _public prototype_ `virtual FText GetStatusText() const override;`
- L34 _public prototype_ `virtual FSlateColor GetStatusTextColor() const override;`
- L35 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L36 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L37 _public function_ `virtual bool ShouldShowFolders() const override`
- L38 _public function_ `virtual bool SupportsCreateNewFolder() const override`
- L39 _public function_ `virtual bool ShowStatusBar() const override`
- L40 _public function_ `virtual bool ShowViewButton() const override`
- L41 _public function_ `virtual bool ShowFilterOptions() const override`
- L42 _public prototype_ `virtual bool CanDelete() const override;`
- L43 _public prototype_ `virtual bool CanRename() const override;`
- L44 _public prototype_ `virtual bool CanCut() const override;`
- L45 _public prototype_ `virtual bool CanCopy() const override;`
- L46 _public prototype_ `virtual bool CanPaste() const override;`
- L47 _public function_ `virtual bool CanSupportDragAndDrop() const`
- L48 _public prototype_ `virtual bool HasErrors() const;`
- L49 _public prototype_ `virtual FText GetErrorsText() const;`
- L50 _public prototype_ `virtual void RepairErrors() const;`
- L51 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L52 _public prototype_ `virtual FFolder CreateNewFolder() override;`
- L53 _public prototype_ `virtual FFolder GetFolder(const FFolder& ParentPath, const FName& LeafName) override;`
- L54 _public prototype_ `virtual bool CreateFolder(const FFolder& NewFolder) override;`
- L55 _public prototype_ `virtual bool ReparentItemToFolder(const FFolder& FolderPath, const FSceneOutlinerTreeItemPtr& Item) override;`
- L56 _public prototype_ `virtual void SelectFoldersDescendants(const TArray<FFolderTreeItem*>& FolderItems, bool bSelectImmediateChildrenOnly) override;`
- L57 _public prototype_ `virtual void PinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;`
- L58 _public prototype_ `virtual void UnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;`
- L59 _public prototype_ `virtual bool CanPinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;`
- L60 _public prototype_ `virtual bool CanUnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;`
- L61 _public prototype_ `virtual void SynchronizeSelection() override;`
- L68 _public prototype_ `void OnComponentsUpdated();` — Called by the engine when a component is updated
- L70 _public prototype_ `void OnLevelActorDeleted(AActor* Actor);` — Called by the engine when an actor is deleted
- L73 _public prototype_ `void OnSelectUnloadedActors(const TArray<FGuid>& ActorGuids);` — Called by the editor to allow selection of unloaded actors
- L77 _public function_ `void OnActorDescRemoved(FWorldPartitionActorDesc* InActorDesc)` — `UE_DEPRECATED(5.4, "Use OnActorDescInstanceRemoved")` — Called when an actor desc is removed
- L80 _public prototype_ `void OnActorDescInstanceRemoved(FWorldPartitionActorDescInstance* InActorDescInstance);` — Called when an actor desc instance is removed
- L83 _public prototype_ `void OnEditCutActorsBegin();` — Called by engine when edit cut actors begins
- L86 _public prototype_ `void OnEditCutActorsEnd();` — Called by engine when edit cut actors ends
- L89 _public prototype_ `void OnEditCopyActorsBegin();` — Called by engine when edit copy actors begins
- L92 _public prototype_ `void OnEditCopyActorsEnd();` — Called by engine when edit copy actors ends
- L95 _public prototype_ `virtual void OnEditPasteActorsBegin();` — Called by engine when edit paste actors begins
- L98 _public prototype_ `virtual void OnEditPasteActorsEnd();` — Called by engine when edit paste actors ends
- L101 _public prototype_ `virtual void OnDuplicateActorsBegin();` — Called by engine when edit duplicate actors begins
- L104 _public prototype_ `virtual void OnDuplicateActorsEnd();` — Called by engine when edit duplicate actors ends
- L107 _public prototype_ `void OnDeleteActorsBegin();` — Called by engine when edit delete actors begins
- L110 _public prototype_ `void OnDeleteActorsEnd();` — Called by engine when edit delete actors ends
- L113 _public prototype_ `virtual bool CompareItemWithClassName(SceneOutliner::FilterBarType InItem, const TSet<FTopLevelAssetPath>&) const override;` — Function called by the Outliner Filter Bar to compare an item with Type Filters
- L116 _public prototype_ `virtual bool CanExecuteRename();` — Check whether the Rename can be executed
- L119 _private prototype_ `TSharedPtr<SWidget> BuildContextMenu();` — Build and up the context menu
- L121 _private prototype_ `static void RegisterContextMenu();` — Register the context menu with the engine
- L122 _private prototype_ `static void FillDefaultContextBaseMenu(UToolMenu* InMenu);`
- L123 _private prototype_ `bool CanPasteFoldersOnlyFromClipboard() const;`
- L126 _private prototype_ `void OnExecuteDelete();` — Delete the current selection
- L129 _private prototype_ `void OnExecuteRefresh();` — Refresh the Outliner
- L132 _private prototype_ `void OnExecuteRename();` — Rename the selected Item (Only work with 1 selected Item)
- L134 _private prototype_ `void SynchronizeSelectedActorDescs();`
- L136 _private prototype_ `void OnActorEditorContextSubsystemChanged();`
- L139 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateShowOnlySelectedActorsFilter();` — Filter factories
- L140 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentLevelFilter();`
- L141 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentDataLayersFilter();`
- L142 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideComponentsFilter();`
- L143 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideUnloadedActorsFilter();`
- L144 _private prototype_ `static TSharedRef<FSceneOutlinerFilter> CreateHideEmptyFoldersFilter();`
- L145 _private prototype_ `TSharedRef<FSceneOutlinerFilter> CreateIsInCurrentContentBundleFilter();`
- L148 _private prototype_ `void OnToggleAlwaysFrameSelection();` — Functions to expose selection framing to the UI
- L149 _private prototype_ `bool ShouldAlwaysFrameSelection() const;`
- L151 _private prototype_ `void OnToggleHideTemporaryActors();`
- L152 _private prototype_ `bool ShouldHideTemporaryActors() const;`
- L154 _private prototype_ `void OnToggleHideLevelInstanceHierarchy();`
- L155 _private prototype_ `bool ShouldHideLevelInstanceHierarchy() const;`
- L157 _private prototype_ `void OnToggleFolderDoubleClickMarkCurrentFolder();`
- L158 _private prototype_ `bool DoesFolderDoubleClickMarkCurrentFolder() const;`
- L160 _private prototype_ `void OnToggleShouldUpdateContentWhileInPIEFocused();`
- L161 _private prototype_ `bool ShouldUpdateContentWhileInPIEFocused() const;`
- L163 _private prototype_ `void OnToggleCollapseOutlinerTreeOnNewSelection();`
- L164 _private prototype_ `bool CollapseOutlinerTreeOnNewSelection() const;`
- L171 _private prototype_ `struct FActorBrowsingModeConfig* GetMutableConfig();` — Get a mutable version of the ActorBrowser config for setting values. @returns		The config for this ActorBrowser. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L178 _private prototype_ `const FActorBrowsingModeConfig* GetConstConfig() const;` — Get a const version of the ActorBrowser config for getting values. @returns		The config for this ActorBrowser. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L181 _private prototype_ `void SaveConfig();` — Save the config for this ActorBrowser
- L185 _private member_ `IWorldPartitionEditorModule* WorldPartitionEditorModule;`
- L187 _private member_ `uint32 FilteredActorCount = 0;` — Number of actors (including unloaded) which have passed through the filters
- L189 _private member_ `uint32 FilteredUnloadedActorCount = 0;` — Number of unloaded actors which have passed through all the filters
- L191 _private member_ `TSet<FWorldPartitionHandle> ApplicableUnloadedActors;` — List of unloaded actors which passed through the regular filters and may or may not have passed the search filter
- L193 _private member_ `TSet<TWeakObjectPtr<AActor>> ApplicableActors;` — List of actors which passed the regular filters and may or may not have passed the search filter
- L195 _private member_ `bool bRepresentingWorldGameWorld = false;`
- L196 _private member_ `bool bRepresentingWorldPartitionedWorld = false;`

### `Source/Editor/SceneOutliner/Public/ActorDescTreeItem.h` (Public)


#### struct `FActorDescTreeItem`  
`struct FActorDescTreeItem : IActorBaseTreeItem`  
_L19-92_
- inherits: `IActorBaseTreeItem`
- desc: A tree item that represents an actor in the world
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FWorldPartitionActorDescInstance*);`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FWorldPartitionActorDescInstance*);`
- L25 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L30 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L36 _public member_ `FWorldPartitionHandle ActorDescHandle;` — The actor desc this tree item is associated with.
- L39 _public member_ `FSceneOutlinerTreeItemID ID;` — Constant identifier for this tree item
- L41 _public prototype_ `static FSceneOutlinerTreeItemID ComputeTreeItemID(FGuid InActorGuid, UActorDescContainerInstance* InContainer);`
- L43 _public prototype_ `static bool ShouldDisplayInOutliner(const FWorldPartitionActorDescInstance* InActorDescInstance);`
- L46 _public function_ `static bool ShouldDisplayInOutliner(const FWorldPartitionActorDesc* ActorDesc)` — `UE_DEPRECATED(5.4, "Use FWorldPartitionActorDescInstance version instead")`
- L49 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L52 _public prototype_ `FActorDescTreeItem(const FGuid& InActorGuid, UActorDescContainerInstance* InContainerInstance);` — Construct this item from an actor desc
- L55 _public prototype_ `FActorDescTreeItem(const FWorldPartitionActorDescInstance* InActorDescInstance);` — Construct this item from an actor desc instance
- L58 _public function_ `FActorDescTreeItem(const FGuid& InActorGuid, class UActorDescContainer* InContainer) : IActorBaseTreeItem(Type)` — `UE_DEPRECATED(5.4, "Use FWorldPartitionActorDescInstance version instead")`
- L61 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L62 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L63 _public prototype_ `virtual FString GetDisplayString() const override;`
- L64 _public prototype_ `virtual bool CanInteract() const override;`
- L65 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L66 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner) override;`
- L67 _public function_ `virtual bool HasVisibilityInfo() const override`
- L68 _public prototype_ `virtual bool GetVisibility() const override;`
- L69 _public prototype_ `virtual bool ShouldShowPinnedState() const override;`
- L70 _public function_ `virtual bool ShouldShowVisibilityState() const override`
- L71 _public function_ `virtual bool HasPinnedStateInfo() const override`
- L72 _public prototype_ `virtual bool GetPinnedState() const override;`
- L73 _public prototype_ `virtual FString GetPackageName() const override;`
- L77 _public function_ `virtual const FGuid& GetGuid() const override` — Begin IActorBaseTreeItem Implementation
- L80 _public prototype_ `UExternalDataLayerAsset* GetExternalDataLayerAsset() const;`
- L82 _public prototype_ `void FocusActorBounds() const;`
- L85 _protected member_ `FString DisplayString;`
- L88 _private member_ `mutable TSoftObjectPtr<UExternalDataLayerAsset> CachedExternalDataLayerAsset;`
- L90 _private prototype_ `void CopyActorFilePathtoClipboard() const;`
- L91 _private member_ `FGuid ActorGuid;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENEOUTLINER_API`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FWorldPartitionActorDescInstance*);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FWorldPartitionActorDescInstance*);`

### `Source/Editor/SceneOutliner/Public/ActorFolderHierarchy.h` (Public)


#### class `FActorFolderHierarchy`  
`class FActorFolderHierarchy : public ISceneOutlinerHierarchy`  
_L8-28_
- inherits: `ISceneOutlinerHierarchy`
- L11 _public prototype_ `FActorFolderHierarchy(ISceneOutlinerMode* InMode, const TWeakObjectPtr<UWorld>& World, const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject());`
- L12 _public prototype_ `virtual ~FActorFolderHierarchy() = default;`
- L16 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;` — Begin ISceneOutlinerHierarchy Implementation
- L17 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override;`
- L18 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;`
- L22 _private prototype_ `void CreateWorldChildren(UWorld* World, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Adds all the direct and indirect children of a world to OutItems
- L25 _private member_ `TWeakObjectPtr<UWorld> RepresentingWorld;` — The world which this hierarchy is representing
- L27 _private member_ `FFolder::FRootObject RootObject;`

### `Source/Editor/SceneOutliner/Public/ActorFolderPickingMode.h` (Public)


#### class `FActorFolderPickingMode`  
`class FActorFolderPickingMode : public FActorMode`  
_L9-29_
- inherits: `FActorMode`
- L12 _public prototype_ `FActorFolderPickingMode(SSceneOutliner* InSceneOutliner, FOnSceneOutlinerItemPicked InOnItemPicked, TWeakObjectPtr<UWorld> InSpecifiedWorldToDisplay = nullptr, const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject());`
- L13 _public prototype_ `virtual ~FActorFolderPickingMode() = default;`
- L16 _public prototype_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType) override;` — Begin ISceneOutlinerMode Implementation
- L17 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L18 _public prototype_ `virtual void CreateViewContent(FMenuBuilder& MenuBuilder) override;`
- L19 _public function_ `virtual bool ShowViewButton() const override`
- L20 _public function_ `virtual bool ShouldShowFolders() const`
- L22 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L26 _protected member_ `FOnSceneOutlinerItemPicked OnItemPicked;` — Delegate to call when an item is picked
- L28 _protected member_ `FFolder::FRootObject RootObject;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/ActorFolderTreeItem.h` (Public)


#### struct `FActorFolderTreeItem`  
`struct FActorFolderTreeItem : public FFolderTreeItem`  
_L10-46_
- inherits: `FFolderTreeItem`
- L14 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L16 _public prototype_ `FActorFolderTreeItem(const FFolder& InFolder, const TWeakObjectPtr<UWorld>& InWorld);`
- L19 _public member_ `TWeakObjectPtr<UWorld> World;` — The world which this folder belongs to
- L22 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L23 _public prototype_ `virtual void OnExpansionChanged() override;`
- L24 _public prototype_ `virtual void Delete(const FFolder& InNewParentFolder) override;`
- L25 _public prototype_ `virtual bool CanInteract() const override;`
- L26 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L27 _public function_ `virtual bool ShouldShowPinnedState() const override`
- L28 _public prototype_ `virtual bool ShouldShowVisibilityState() const override;`
- L29 _public prototype_ `virtual bool ShouldRemoveOnceLastChildRemoved() const override;`
- L30 _public prototype_ `virtual FFolder GetFolder() const override;`
- L31 _public prototype_ `virtual FString GetPackageName() const override;`
- L35 _public prototype_ `virtual void MoveTo(const FFolder& InNewParentFolder) override;` — Begin FFolderTreeItem Implementation
- L36 _public prototype_ `virtual void SetPath(const FName& InNewPath) override;`
- L38 _public prototype_ `bool CanChangeChildrenPinnedState() const;`
- L39 _public function_ `const UActorFolder* GetActorFolder() const`
- L41 _private prototype_ `virtual void CreateSubFolder(TWeakPtr<SSceneOutliner> WeakOutliner) override;`
- L45 _private member_ `TWeakObjectPtr<UActorFolder> ActorFolder;` — The actor folder object (can be invalid)

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/ActorHierarchy.h` (Public)


#### class `FActorHierarchy`  
`class FActorHierarchy : public ISceneOutlinerHierarchy`  
_L14-139_
- inherits: `ISceneOutlinerHierarchy`
- L17 _public prototype_ `virtual ~FActorHierarchy();`
- L19 _public prototype_ `static TUniquePtr<FActorHierarchy> Create(ISceneOutlinerMode* Mode, const TWeakObjectPtr<UWorld>& World);`
- L22 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;` — Create a linearization of all applicable items in the hierarchy
- L24 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override;` — Create a linearization of all direct and indirect children of a given item in the hierarchy
- L26 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;` — Forcibly create a parent item for a given tree item
- L28 _public function_ `void SetShowingComponents(bool bInShowingComponents)`
- L29 _public function_ `void SetShowingOnlyActorWithValidComponents(bool bInShowingOnlyActorWithValidComponents)`
- L30 _public function_ `void SetShowingLevelInstances(bool bInShowingLevelInstances)`
- L31 _public function_ `void SetShowingUnloadedActors(bool bInShowingUnloadedActors)`
- L32 _public function_ `void SetShowingEmptyFolders(bool bInShowingEmptyFolders)`
- L33 _public function_ `void SetSearchComponentsByActorName(bool bInSearchComponentsByActorName)`
- L36 _private prototype_ `bool IsShowingUnloadedActors() const;`
- L38 _private prototype_ `void CreateWorldChildren(UWorld* World, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Adds all the direct and indirect children of a world to OutItems
- L42 _protected prototype_ `void OnWorldPartitionCreated(UWorld* InWorld);` — Update the hierarchy when actor or world changing events occur
- L45 _protected prototype_ `void CreateComponentItems(const AActor* Actor, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create all component items for an actor if we are showing components and place them in OutItems
- L47 _protected prototype_ `virtual void OnLevelActorAdded(AActor* InActor);`
- L48 _protected prototype_ `virtual void OnLevelActorDeleted(AActor* InActor);`
- L50 _protected prototype_ `virtual void OnLevelActorAttached(AActor* InActor, const AActor* InParent);`
- L51 _protected prototype_ `virtual void OnLevelActorDetached(AActor* InActor, const AActor* InParent);`
- L53 _protected prototype_ `virtual void OnLevelActorFolderChanged(const AActor* InActor, FName OldPath);`
- L55 _protected prototype_ `virtual void OnLoadedActorAdded(AActor& InActor);`
- L56 _protected prototype_ `virtual void OnLoadedActorRemoved(AActor& InActor);`
- L58 _protected prototype_ `virtual void OnActorDescInstanceAdded(FWorldPartitionActorDescInstance* InActorDescInstance);`
- L59 _protected prototype_ `virtual void OnActorDescInstanceRemoved(FWorldPartitionActorDescInstance* InActorDescInstance);`
- L62 _protected function_ `virtual void OnActorDescAdded(FWorldPartitionActorDesc* ActorDesc)` — `UE_DEPRECATED(5.4, "Use OnActorDescInstanceAdded instead")`
- L65 _protected function_ `virtual void OnActorDescRemoved(FWorldPartitionActorDesc* ActorDesc)` — `UE_DEPRECATED(5.4, "Use OnActorDescInstanceRemoved instead")`
- L67 _protected prototype_ `void OnComponentsUpdated();`
- L69 _protected prototype_ `void OnLevelActorListChanged();`
- L71 _protected prototype_ `virtual void OnActorFolderAdded(UActorFolder* InActorFolder);`
- L72 _protected prototype_ `void OnActorFoldersUpdatedEvent(ULevel* InLevel);`
- L74 _protected prototype_ `virtual void OnLevelAdded(ULevel* InLevel, UWorld* InWorld);`
- L75 _protected prototype_ `virtual void OnLevelRemoved(ULevel* InLevel, UWorld* InWorld);`
- L77 _protected prototype_ `void OnWorldPartitionInitialized(UWorldPartition* InWorldPartition);`
- L78 _protected prototype_ `void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);`
- L81 _protected prototype_ `virtual void OnBroadcastFolderCreate(UWorld& InWorld, const FFolder& InNewFolder);` — Called when a folder is to be created
- L84 _protected prototype_ `virtual void OnBroadcastFolderMove(UWorld& InWorld, const FFolder& InOldFolder, const FFolder& InNewFolder);` — Called when a folder is to be moved
- L87 _protected prototype_ `virtual void OnBroadcastFolderDelete(UWorld& InWorld, const FFolder& InFolder);` — Called when a folder is to be deleted
- L90 _protected prototype_ `void RemoveActorDesc(AActor& InActor);` — Remove the unloaded actor item for the given actor
- L93 _protected prototype_ `void AddActorDesc(AActor& InActor);` — Add the unloaded actor item for the given actor
- L96 _protected prototype_ `void RemoveLevelActorFolders(ULevel* InLevel, UWorld* InWorld);` — Remove all Actor Folders belonging to this level
- L99 _protected prototype_ `void CreateFolderItems(UWorld* InWorld, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create items for Actor Folders
- L102 _protected prototype_ `void CreateUnloadedItems(UWorld* World, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Create items for unloaded actors
- L105 _protected prototype_ `void InsertActorItemAndCreateComponents(AActor* InActor, FSceneOutlinerTreeItemPtr ActorItem, TArray<FSceneOutlinerTreeItemPtr>& OutItems) const;` — Insert the given item at the right position in the tree, and optionally create and insert components if needed
- L108 _protected prototype_ `bool CheckLevelInstanceEditing(UWorld* World, AActor* Actor) const;` — Check if the actor we are creating an item for is in the current level instance, if we are currently editing one
- L111 _protected prototype_ `virtual FSceneOutlinerTreeItemPtr CreateItemForActor(AActor* InActor, bool bForce = false) const;` — Create a SceneOutlinerTreeItem for the given actor
- L114 _protected prototype_ `virtual FSceneOutlinerTreeItemPtr CreateItemForActorDescInstance(const FWorldPartitionActorDescInstance* InActorDescInstance, bool bForce = false) const;` — Create a SceneOutlinerTreeItem for the given actor descriptor instance
- L116 _protected prototype_ `virtual FSceneOutlinerTreeItemPtr CreateItemForFolder(const FFolder& InFolder, const TWeakObjectPtr<UWorld>& InWorld, bool bForce = false) const;`
- L120 _protected prototype_ `void FullRefreshEvent();` — Send a an event indicating a full refresh of the hierarchy is required
- L122 _protected member_ `TWeakObjectPtr<UWorld> RepresentingWorld;`
- L124 _protected member_ `bool bShowingComponents = false;`
- L125 _protected member_ `bool bShowingOnlyActorWithValidComponents = false;`
- L126 _protected member_ `bool bShowingLevelInstances = false;`
- L127 _protected member_ `bool bShowingUnloadedActors = false;`
- L128 _protected member_ `bool bShowingEmptyFolders = false;`
- L129 _protected member_ `bool bSearchComponentsByActorName = false;`
- L133 _protected prototype_ `static void Create_Internal(FActorHierarchy* Hierarchy, const TWeakObjectPtr<UWorld>& World);`
- L135 _protected prototype_ `FActorHierarchy(ISceneOutlinerMode* Mode, const TWeakObjectPtr<UWorld>& Worlds);`
- L137 _protected prototype_ `FActorHierarchy(const FActorHierarchy&) = delete;`
- L138 _protected prototype_ `FActorHierarchy& operator=(const FActorHierarchy&) = delete;`

### `Source/Editor/SceneOutliner/Public/ActorMode.h` (Public)


#### struct `SceneOutliner::FWeakActorSelector`  
`struct FWeakActorSelector`  
_L13-16_
- desc: Functor which can be used to get weak actor pointers from a selection
- L15 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, TWeakObjectPtr<AActor>& DataOut) const;`

#### struct `SceneOutliner::FActorSelector`  
`struct FActorSelector`  
_L19-22_
- desc: Functor which can be used to get actors from a selection including component parents
- L21 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, AActor*& ActorPtrOut) const;`

#### struct `SceneOutliner::FActorDescSelector`  
`struct UE_DEPRECATED(5.4, "Use FActorHandleSelector instead") FActorDescSelector`  
_L24-27_
- L26 _public function_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>&Item, FWorldPartitionActorDesc * &ActorDescPtrOut) const`

#### struct `SceneOutliner::FActorHandleSelector`  
`struct FActorHandleSelector`  
_L30-33_
- desc: Functor which can be used to get actor descriptors from a selection
- L32 _public prototype_ `bool operator()(const TWeakPtr<ISceneOutlinerTreeItem>& Item, FWorldPartitionHandle& ActorHandleOut) const;`

#### struct `FActorModeParams`  
`struct FActorModeParams`  
_L36-63_
- L38 _public function_ `FActorModeParams()`
- L40 _public function_ `FActorModeParams(SSceneOutliner* InSceneOutliner, const TWeakObjectPtr<UWorld>& InSpecifiedWorldToDisplay = nullptr, bool bInHideComponents = true, bool bInHideLevelInstanceHierarchy = true, bool bInHideUnloadedActors = true, bool bInHideEmptyFolders = true, bool bInCanInteractWithSelectableActorsOnly = true, bool binSearchComponentsByActorName = false) : SpecifiedWorldToDisplay(InSpecifiedWorldToDisplay) , SceneOutliner(InSceneOutliner) , bHideComponents(bInHideComponents) , bHideLevelInstanceHierarchy(bInHideLevelInstanceHierarchy) , bHideUnloadedActors(bInHideUnloadedActors) , bHideEmptyFolders(bInHideEmptyFolders) , bCanInteractWithSelectableActorsOnly(bInCanInteractWithSelectableActorsOnly) , bSearchComponentsByActorName(binSearchComponentsByActorName)`
- L53 _public member_ `TWeakObjectPtr<UWorld> SpecifiedWorldToDisplay = nullptr;`
- L54 _public member_ `SSceneOutliner* SceneOutliner = nullptr;`
- L55 _public member_ `bool bHideComponents = true;`
- L56 _public member_ `bool bHideActorWithNoComponent = false;`
- L57 _public member_ `bool bHideLevelInstanceHierarchy = true;`
- L58 _public member_ `bool bHideUnloadedActors = true;`
- L59 _public member_ `bool bHideEmptyFolders = true;`
- L60 _public member_ `bool bCanInteractWithSelectableActorsOnly = true;`
- L61 _public member_ `bool bShouldUpdateContentWhileInPIEFocused = false;`
- L62 _public member_ `bool bSearchComponentsByActorName = false;`

#### class `FActorMode`  
`class FActorMode : public ISceneOutlinerMode`  
_L65-155_
- inherits: `ISceneOutlinerMode`
- L73 _public prototype_ `FActorMode(const FActorModeParams& Params);`
- L74 _public prototype_ `virtual ~FActorMode();`
- L76 _public prototype_ `virtual void Rebuild() override;`
- L78 _public prototype_ `void BuildWorldPickerMenu(FMenuBuilder& MenuBuilder);`
- L80 _public function_ `virtual void SynchronizeSelection() override`
- L82 _public prototype_ `virtual void OnFilterTextChanged(const FText& InFilterText) override;`
- L84 _public prototype_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L86 _public prototype_ `static bool IsActorDisplayable(const SSceneOutliner* SceneOutliner, const AActor* Actor, bool bShowLevelInstanceContent = false);`
- L87 _public prototype_ `static bool IsActorLevelDisplayable(ULevel* InLevel);`
- L89 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L90 _public prototype_ `virtual FFolder::FRootObject GetPasteTargetRootObject() const override;`
- L92 _public prototype_ `virtual bool CanInteract(const ISceneOutlinerTreeItem& Item) const override;`
- L93 _public prototype_ `virtual bool CanPopulate() const override;`
- L95 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L96 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L97 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L98 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L103 _private prototype_ `void OnSelectWorld(TWeakObjectPtr<UWorld> World);` — Called when the user selects a world in the world picker menu
- L107 _private prototype_ `void ChooseRepresentingWorld();`
- L108 _private prototype_ `bool IsWorldChecked(TWeakObjectPtr<UWorld> World) const;`
- L109 _private prototype_ `bool GetFolderNamesFromPayload(const FSceneOutlinerDragDropPayload& InPayload, TArray<FName>& OutFolders, FFolder::FRootObject& OutCommonRootObject) const;`
- L112 _protected prototype_ `void SynchronizeActorSelection();`
- L113 _protected prototype_ `virtual bool IsActorDisplayable(const AActor* InActor) const;`
- L116 _protected prototype_ `void SetAsMostRecentOutliner() const;` — Set the Scene Outliner attached to this mode as the most recently used outliner in the Level Editor
- L118 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L121 _protected function_ `virtual void OnActorsAttached(AActor* ParentActor, TArray<TWeakObjectPtr<AActor>> ChildActors) const` — Called when actors are attached to a parent actor via drag and drop
- L123 _protected prototype_ `FFolder GetWorldDefaultRootFolder() const;`
- L126 _protected member_ `TWeakObjectPtr<UWorld> RepresentingWorld;` — The world which we are currently representing
- L128 _protected member_ `TWeakObjectPtr<UWorld> UserChosenWorld;` — The world which the user manually selected
- L131 _protected member_ `const TWeakObjectPtr<UWorld> SpecifiedWorldToDisplay;` — If this mode was created to display a specific world, don't allow it to be reassigned
- L134 _protected member_ `bool bHideComponents;` — Should components be hidden
- L136 _protected member_ `bool bHideActorWithNoComponent;` — Should actor with no component be hidden.
- L138 _protected member_ `bool bHideLevelInstanceHierarchy;` — Should the level instance hierarchy be hidden
- L140 _protected member_ `bool bHideUnloadedActors;` — Should unloaded actors be hidden
- L142 _protected member_ `bool bHideEmptyFolders;` — Should empty folders be hidden
- L144 _protected member_ `bool bAlwaysFrameSelection;` — Should the outliner scroll to the item on selection
- L146 _protected member_ `bool bCanInteractWithSelectableActorsOnly;` — If True, CanInteract will be restricted to selectable actors only.
- L148 _protected member_ `bool bShouldUpdateContentWhileInPIEFocused;` — Should we update content when in PIE and the PIE viewport has focus.
- L152 _protected member_ `bool bSearchComponentsByActorName;` — If true and bHideComponents is false, components will be shown if the owning actor is searched for even if the search text does not match the components
- L154 _protected member_ `bool bCollapseOutlinerTreeOnNewSelection;` — Should Outliner Tree get collapsed on selection, except for the item that was just selected

#### struct `FActorMode::EItemSortOrder`  
`struct EItemSortOrder`  
_L68-71_

#### enum `FActorMode::EItemSortOrder::Type`  
`enum Type`  
_L70-70_
- L70 _public enumerator_ `enum Type { World = 0, Level = 10, Folder = 20, Actor = 30 };`
- L70 _public enumerator_ `enum Type { World = 0, Level = 10, Folder = 20, Actor = 30 };`
- L70 _public enumerator_ `enum Type { World = 0, Level = 10, Folder = 20, Actor = 30 };`
- L70 _public enumerator_ `enum Type { World = 0, Level = 10, Folder = 20, Actor = 30 };`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENEOUTLINER_API`
- L10 _namespace_ `namespace SceneOutliner`

### `Source/Editor/SceneOutliner/Public/ActorModeInteractive.h` (Public)


#### class `FActorModeInteractive`  
`class FActorModeInteractive : public FActorMode`  
_L7-26_
- inherits: `FActorMode`
- L10 _public prototype_ `FActorModeInteractive(const FActorModeParams& Params);`
- L11 _public prototype_ `virtual ~FActorModeInteractive();`
- L13 _public function_ `virtual bool IsInteractive() const override`
- L17 _protected prototype_ `void OnMapChange(uint32 MapFlags);`
- L18 _protected prototype_ `void OnNewCurrentLevel();`
- L20 _protected prototype_ `virtual void OnActorLabelChanged(AActor* ChangedActor);`
- L22 _protected prototype_ `void OnLevelSelectionChanged(UObject* Obj);`
- L23 _protected prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L24 _protected prototype_ `void OnLevelActorRequestsRename(const AActor* Actor);`
- L25 _protected prototype_ `void OnPostLoadMapWithWorld(UWorld* World);`

### `Source/Editor/SceneOutliner/Public/ActorPickingMode.h` (Public)


#### class `FActorPickingMode`  
`class FActorPickingMode : public FActorMode`  
_L9-29_
- inherits: `FActorMode`
- L12 _public prototype_ `FActorPickingMode(const FActorModeParams& Params, FOnSceneOutlinerItemPicked OnItemPickedDelegate);`
- L14 _public prototype_ `virtual ~FActorPickingMode() = default;`
- L16 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L19 _public prototype_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType) override;` — Allow the user to commit their selection by pressing enter if it is valid
- L21 _public prototype_ `virtual void CreateViewContent(FMenuBuilder& MenuBuilder) override;`
- L24 _public function_ `virtual void SynchronizeSelection() override` — Don't synchronize world selection
- L26 _public function_ `virtual bool ShowViewButton() const override`
- L28 _private member_ `FOnSceneOutlinerItemPicked OnItemPicked;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/ActorTreeItem.h` (Public)


#### struct `FActorTreeItem`  
`struct FActorTreeItem : IActorBaseTreeItem`  
_L13-78_
- inherits: `IActorBaseTreeItem`
- desc: A tree item that represents an actor in the world
- L16 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const AActor*);`
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const AActor*);`
- L19 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L24 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L30 _public member_ `mutable TWeakObjectPtr<AActor> Actor;` — The actor this tree item is associated with.
- L33 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L36 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L39 _public prototype_ `FActorTreeItem(AActor* InActor);` — Construct this item from an actor
- L42 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L43 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L44 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L45 _public prototype_ `virtual FString GetDisplayString() const override;`
- L46 _public prototype_ `virtual bool CanInteract() const override;`
- L47 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L48 _public prototype_ `virtual void OnVisibilityChanged(const bool bNewVisibility) override;`
- L49 _public function_ `virtual bool HasVisibilityInfo() const override`
- L50 _public prototype_ `virtual bool GetVisibility() const override;`
- L51 _public prototype_ `virtual bool ShouldShowPinnedState() const override;`
- L52 _public prototype_ `virtual bool ShouldShowVisibilityState() const override;`
- L53 _public function_ `virtual bool HasPinnedStateInfo() const override`
- L54 _public prototype_ `virtual bool GetPinnedState() const override;`
- L55 _public prototype_ `virtual void OnLabelChanged() override;`
- L56 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner) override;`
- L57 _public prototype_ `virtual FString GetPackageName() const override;`
- L61 _public prototype_ `virtual const FGuid& GetGuid() const override;` — Begin IActorBaseTreeItem Implementation
- L65 _public member_ `bool bExistsInCurrentWorldAndPIE;` — true if this item exists in both the current world and PIE.
- L69 _protected prototype_ `FActorTreeItem(FSceneOutlinerTreeItemType TypeIn, AActor* InActor);` — For use by derived classes, as it allows for passing down their own type.
- L71 _protected prototype_ `virtual void UpdateDisplayString();`
- L74 _protected member_ `FString DisplayString;` — Cached display string
- L77 _private prototype_ `void UpdateDisplayStringInternal();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENEOUTLINER_API`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const AActor*);`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const AActor*);`

### `Source/Editor/SceneOutliner/Public/Columns/SceneOutlinerColumns.h` (Public)


#### struct `FSceneOutlinerColumn`  
`struct FSceneOutlinerColumn final : public FEditorDataStorageColumn`  
_L16-21_
- reflection: `USTRUCT(meta = (DisplayName = "Outliner"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store a reference to the Scene Outliner owning or on a specific row
- L20 _public member_ `TWeakPtr<ISceneOutliner> Outliner;`

#### struct `FTedsOutlinerRowHandleDealiaserColumn`  
`struct FTedsOutlinerRowHandleDealiaserColumn final : public FEditorDataStorageColumn`  
_L42-47_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column on the outliner row providing a pre-bound delegate to resolve a RowHandle from a legacy ISceneOutlinerTreeItem. Custom outliner columns can query this from the outliner row to map tree items to TEDS rows without directly depending on TedsOutliner internals.
- L46 _public member_ `UE::Editor::Outliner::FGetRowHandleFromOutlinerItem GetRowHandle;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L26 _variable_ `inline const FName OutlinerMappingDomain = TEXT("Ted` (scope `UE::Editor::Outliner`) — The mapping domain used when registering outliner rows in TEDS.
- L33 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UE::Editor::DataStorage::RowHandle, FGetRowHandleFromOutlinerItem, const ISceneOutlinerTreeItem&);` — Delegate to resolve a TEDS RowHandle from a SceneOutliner tree item. Bound on the outliner row. Custom outliner columns can query FTedsOutlinerRowHandleDealiaserColumn from the outliner row to map tree items to TEDS rows without depending on TedsOutliner internals.
- L33 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UE::Editor::DataStorage::RowHandle, FGetRowHandleFromOutlinerItem, const ISceneOutlinerTreeItem&);` (scope `UE::Editor::Outliner`) — Delegate to resolve a TEDS RowHandle from a SceneOutliner tree item. Bound on the outliner row. Custom outliner columns can query FTedsOutlinerRowHandleDealiaserColumn from the outliner row to map tree items to TEDS rows without depending on TedsOutliner internals.

### `Source/Editor/SceneOutliner/Public/ComponentTreeItem.h` (Public)


#### struct `FComponentTreeItem`  
`struct FComponentTreeItem : ISceneOutlinerTreeItem`  
_L14-63_
- inherits: `ISceneOutlinerTreeItem`
- desc: A tree item that represents an Component in the world
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UActorComponent*);`
- L18 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UActorComponent*);`
- L20 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L25 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L31 _public member_ `mutable TWeakObjectPtr<UActorComponent> Component;` — The Component this tree item is associated with.
- L34 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L37 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L40 _public prototype_ `FComponentTreeItem(UActorComponent* InComponent, bool bInSearchComponentsByActorName = false);` — Construct this item from an Component
- L42 _public prototype_ `bool GetSearchComponentByActorName() const;`
- L45 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L46 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L47 _public prototype_ `virtual FString GetDisplayString() const override;`
- L48 _public prototype_ `virtual bool CanInteract() const override;`
- L49 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L50 _public function_ `virtual bool ShouldShowVisibilityState() const`
- L51 _public function_ `virtual bool HasVisibilityInfo() const`
- L52 _public function_ `virtual bool GetVisibility() const`
- L56 _public member_ `bool bExistsInCurrentWorldAndPIE;` — true if this item exists in both the current world and PIE.
- L59 _public member_ `bool bSearchComponentsByActorName;` — If true components will be shown if the owning actor is searched for even if the search text does not match the component
- L62 _public member_ `FString CachedDisplayString;` — Cache the string displayed

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SCENEOUTLINER_API`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UActorComponent*);`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UActorComponent*);`

### `Source/Editor/SceneOutliner/Public/FolderTreeItem.h` (Public)


#### struct `SceneOutliner::FFolderPathSelector`  
`struct FFolderPathSelector`  
_L15-18_
- L17 _public prototype_ `bool operator()(TWeakPtr<ISceneOutlinerTreeItem> Item, FFolder& DataOut) const;`

#### struct `FFolderTreeItem`  
`struct FFolderTreeItem : ISceneOutlinerTreeItem`  
_L23-84_
- inherits: `ISceneOutlinerTreeItem`
- desc: A tree item that represents a folder in the world
- L27 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L29 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FFolder&);`
- L30 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FFolder&);`
- L32 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L37 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L43 _public member_ `FName Path;` — The path of this folder. / separated.
- L46 _public member_ `FName LeafName;` — The leaf name of this folder
- L48 _public prototype_ `FFolderTreeItem(const FFolder& InFolder, FSceneOutlinerTreeItemType InType);`
- L49 _public prototype_ `FFolderTreeItem(const FFolder& InFolder);`
- L51 _public prototype_ `FFolderTreeItem(FName InPath);` — Constructor that takes a path to this folder (including leaf-name)
- L53 _public prototype_ `FFolderTreeItem(FName InPath, FSceneOutlinerTreeItemType Type);` — Constructor that takes a path to this folder and a subclass tree item type (used for subclassing FFolderTreeItem)
- L56 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L57 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L58 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L59 _public prototype_ `virtual FString GetDisplayString() const override;`
- L60 _public prototype_ `virtual bool CanInteract() const override;`
- L61 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner) override;`
- L63 _public function_ `virtual void Delete(const FFolder& InNewParentFolder)` — Delete this folder, children will be reparented to provided new parent path
- L65 _public prototype_ `virtual void SetPath(const FName& InNewPath);`
- L66 _public function_ `const FName& GetPath() const`
- L67 _public function_ `const FName& GetLeafName() const`
- L68 _public function_ `virtual FFolder GetFolder() const`
- L70 _public function_ `virtual bool ShouldShowPinnedState() const override`
- L71 _public function_ `virtual bool HasPinnedStateInfo() const override`
- L75 _public function_ `virtual void MoveTo(const FFolder& InNewParentFolder)` — Move this folder to a new parent
- L78 _private function_ `virtual void CreateSubFolder(TWeakPtr<SSceneOutliner> WeakOutliner)` — Create a new folder as a child of this one
- L80 _private prototype_ `void DuplicateHierarchy(TWeakPtr<SSceneOutliner> WeakOutliner);` — Duplicate folder hierarchy
- L83 _private member_ `FFolder::FRootObject RootObject;` — Folder's root object (can be null)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENEOUTLINER_API`
- L13 _namespace_ `namespace SceneOutliner`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const FFolder&);`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const FFolder&);`

### `Source/Editor/SceneOutliner/Public/ISceneOutliner.h` (Public)


#### class `ISceneOutliner`  
`class ISceneOutliner : public SCompoundWidget`  
_L20-203_
- inherits: `SCompoundWidget`
- desc: The public interface for the Scene Outliner widget
- L25 _public prototype_ `virtual void Refresh() = 0;` — Sends a requests to the Scene Outliner to refresh itself the next chance it gets
- L28 _public prototype_ `virtual void FullRefresh() = 0;` — Tells the scene outliner that it should do a full refresh, which will clear the entire tree and rebuild it from scratch.
- L31 _public prototype_ `virtual TAttribute<FText> GetFilterHighlightText() const = 0;` — @return Returns a string to use for highlighting results in the outliner list
- L34 _public prototype_ `virtual const FSharedSceneOutlinerData& GetSharedData() const = 0;` — @return Returns the common data for this outliner
- L37 _public prototype_ `virtual const STreeView<FSceneOutlinerTreeItemPtr>& GetTree() const = 0;` — Get a const reference to the actual tree hierarchy
- L40 _public prototype_ `virtual void SetKeyboardFocus() = 0;` — Set the keyboard focus to the outliner
- L43 _public prototype_ `virtual const FSlateBrush* GetCachedIconForClass(FName InClassName) const = 0;` — Gets the cached icon for this class name
- L46 _public prototype_ `virtual void CacheIconForClass(FName InClassName, const FSlateBrush* InSlateBrush) = 0;` — Sets the cached icon for this class name
- L49 _public prototype_ `virtual bool CanExecuteRenameRequest(const ISceneOutlinerTreeItem& ItemPtr) const = 0;` — Should the scene outliner accept a request to rename a item of the tree
- L56 _public prototype_ `virtual int32 AddFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) = 0;` — Add a filter to the scene outliner @param Filter The filter to apply to the scene outliner @return The index of the filter.
- L62 _public prototype_ `virtual void AddFilterToFilterBar(const TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>& InFilter) = 0;` — Add a filter to the scene outliner's filter bar @param Filter The filter to add
- L68 _public prototype_ `virtual void DisableAllFilterBarFilters(bool bRemove) = 0;` — Disable all filters currently active in the filter bar @param bRemove if true, the filter will also be unpinned and removed from the filter bar
- L75 _public prototype_ `virtual bool RemoveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) = 0;` — Remove a filter from the scene outliner @param Filter The Filter to remove @return True if the filter was removed.
- L82 _public prototype_ `virtual int32 AddInteractiveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) = 0;` — Add an interactive filter to the scene outliner @param Filter The filter used to determine if scene outliner items are interactive. @return The index of the filter.
- L89 _public prototype_ `virtual bool RemoveInteractiveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) = 0;` — Remove an interactive  filter from the scene outliner @param Filter The Filter to remove @return True if the filter was removed.
- L96 _public prototype_ `virtual TSharedPtr<FSceneOutlinerFilter> GetFilterAtIndex(int32 Index) = 0;` — Retrieve the filter at the specified index @param Index The index of the filter to retrive @return A valid poiter to a filter if the index was valid
- L99 _public prototype_ `virtual int32 GetFilterCount() const = 0;` — Get number of filters applied to the scene outliner
- L107 _public prototype_ `virtual void AddColumn(FName ColumnId, const FSceneOutlinerColumnInfo& ColumnInfo) = 0;` — Add or replace a column of the scene outliner Note: The column id must match the id of the column returned by the factory @param ColumnId The id of the column to add @param ColumInfo The struct that contains the information on how to present and retrieve the column
- L113 _public prototype_ `virtual void RemoveColumn(FName ColumnId) = 0;` — Remove a column of the scene outliner @param ColumnId The name of the column to remove
- L116 _public prototype_ `virtual TArray<FName> GetColumnIds() const = 0;` — Return the name/Id of the columns of the scene outliner
- L119 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode( const FName ColumnId ) const = 0;` — Return the sorting mode for the specified ColumnId
- L121 _public prototype_ `virtual uint32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const = 0;`
- L124 _public prototype_ `virtual void RequestSort() = 0;` — Request that the tree be sorted at a convenient time
- L127 _public prototype_ `virtual bool Delete_CanExecute() = 0;` — Returns true if edit delete can be executed
- L130 _public prototype_ `virtual bool Rename_CanExecute() = 0;` — Returns true if edit rename can be executed
- L133 _public prototype_ `virtual void Rename_Execute() = 0;` — Executes rename.
- L136 _public prototype_ `virtual bool Cut_CanExecute() = 0;` — Returns true if edit cut can be executed
- L139 _public prototype_ `virtual bool Copy_CanExecute() = 0;` — Returns true if edit copy can be executed
- L142 _public prototype_ `virtual bool Paste_CanExecute() = 0;` — Returns true if edit paste can be executed
- L145 _public prototype_ `virtual bool CanSupportDragAndDrop() const = 0;` — Can the scene outliner rows generated on drag event
- L148 _public prototype_ `virtual void SetSelection(const TFunctionRef<bool(ISceneOutlinerTreeItem&)> Selector) = 0;` — Set the item selection of the outliner based on a selector function. Any items which return true will be added
- L151 _public prototype_ `virtual void PinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) = 0;` — Pins an item list in the outliner.
- L154 _public prototype_ `virtual void UnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) = 0;` — Unpins an item list in the outliner.
- L157 _public prototype_ `virtual bool CanPinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const = 0;` — Returns true if any of the items can be pinned.
- L160 _public prototype_ `virtual bool CanUnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const = 0;` — Returns true if any of the items can be unpinned.
- L163 _public prototype_ `virtual void PinSelectedItems() = 0;` — Pin selected items
- L166 _public prototype_ `virtual void UnpinSelectedItems() = 0;` — Unpins selected items
- L169 _public prototype_ `virtual bool CanPinSelectedItems() const = 0;` — Returns true if any of the selected items can be pinned
- L172 _public prototype_ `virtual bool CanUnpinSelectedItems() const = 0;` — Returns true if any of the selected items can be unpinned
- L175 _public prototype_ `virtual void FrameSelectedItems() = 0;` — Scrolls the outliner to the selected item(s). If more are selected, the chosen item is undeterministic.
- L178 _public prototype_ `virtual void FrameItem(const FSceneOutlinerTreeItemID& Item) = 0;` — Scrolls the outliner to the specified item if it's found. No action is done otherwise.
- L181 _public function_ `virtual void SetItemExpansion(const FSceneOutlinerTreeItemPtr& Item, bool bIsExpanded)` — Set whether a particular item in the outliner is expanded or not.
- L184 _public function_ `const ISceneOutlinerMode* GetMode() const` — Get the active SceneOutlinerMode
- L187 _public prototype_ `virtual TSharedPtr<FSceneOutlinerTreeItemSCC> GetItemSourceControl(const FSceneOutlinerTreeItemPtr& InItem) = 0;` — Get the associated source control object for the specified item.
- L190 _public prototype_ `virtual bool IsFilterActive(const FString& FilterName) const = 0;` — Check if a filter with the given name exists and is active in the filter bar for this Outliner (if this Outliner has a filter bar).
- L193 _public prototype_ `virtual FSceneOutlinerTreeItemPtr GetTreeItem(FSceneOutlinerTreeItemID, bool bIncludePending = false) = 0;` — Retrieve an ISceneOutlinerTreeItem by its ID if it exists in the tree
- L197 _public prototype_ `virtual void SetNextUIRefreshDelay(float InDelay) = 0;` — Set a delay (in seconds) before the the next requested UI refresh executes. Note: This only applies until the next refresh that executes and any subsequent ones will be immediate.
- L200 _public prototype_ `virtual FName GetOutlinerIdentifier() const = 0;` — Get the unqiue identifier of this Outliner (if specified, NAME_None otherwise)
- L202 _protected member_ `ISceneOutlinerMode* Mode;`

### `Source/Editor/SceneOutliner/Public/ISceneOutlinerColumn.h` (Public)


#### class `ISceneOutlinerColumn`  
`class ISceneOutlinerColumn : public TSharedFromThis< ISceneOutlinerColumn >`  
_L15-41_
- inherits: `TSharedFromThis<ISceneOutlinerColumn>`
- desc: Interface for a scene outliner column
- L18 _public prototype_ `virtual ~ISceneOutlinerColumn() = default;`
- L20 _public prototype_ `virtual FName GetColumnID() = 0;`
- L22 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L24 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) = 0;`
- L26 _public function_ `virtual void Tick(double InCurrentTime, float InDeltaTime)`
- L30 _public function_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const` — Optionally overridden interface methods
- L32 _public function_ `virtual bool SupportsSorting() const`
- L34 _public function_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const`
- L37 _public function_ `virtual void OnSortRequested(const EColumnSortPriority::Type SortPriority, const EColumnSortMode::Type InSortMode)` — Called when a sort is first requested in the Outliner
- L40 _public function_ `virtual bool IsSortReady()` — Checks whether the column is still processing the sort or if it is ready to start sorting items

### `Source/Editor/SceneOutliner/Public/ISceneOutlinerHierarchy.h` (Public)


#### class `ISceneOutlinerHierarchy`  
`class ISceneOutlinerHierarchy : public TSharedFromThis<ISceneOutlinerHierarchy>`  
_L11-30_
- inherits: `TSharedFromThis<ISceneOutlinerHierarchy>`
- L14 _public function_ `ISceneOutlinerHierarchy(ISceneOutlinerMode* InMode) : Mode(InMode)`
- L15 _public function_ `virtual ~ISceneOutlinerHierarchy()`
- L18 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const = 0;` — Create a linearization of all applicable items in the hierarchy
- L20 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const = 0;` — Create a linearization of all direct and indirect children of a given item in the hierarchy
- L22 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) = 0;` — Find or optionally create a parent item for a given tree item
- L24 _public function_ `DECLARE_EVENT_OneParam(ISceneOutlinerHierarchy, FHierarchyChangedEvent, FSceneOutlinerHierarchyChangedData) FHierarchyChangedEvent& OnHierarchyChanged()`
- L28 _protected member_ `ISceneOutlinerMode* Mode;`
- L29 _protected member_ `FHierarchyChangedEvent HierarchyChangedEvent;`

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_EVENT_OneParam(ISceneOutlinerHierarchy, FHierarchyChangedEvent, FSceneOutlinerHierarchyChangedData) FHierarchyChangedEvent& OnHierarchyChanged() { return HierarchyChangedEvent; } protected: ISceneOutlinerMode* Mode;`

### `Source/Editor/SceneOutliner/Public/ISceneOutlinerMode.h` (Public)


#### class `ISceneOutlinerMode`  
`class ISceneOutlinerMode`  
_L16-209_
- L19 _public function_ `ISceneOutlinerMode(SSceneOutliner* InSceneOutliner) : SceneOutliner(InSceneOutliner)`
- L21 _public prototype_ `virtual ~ISceneOutlinerMode() = default;`
- L24 _public prototype_ `virtual void Rebuild() = 0;` — Rebuild all mode data
- L33 _public function_ `template <typename TreeItemType, typename TreeItemData> FSceneOutlinerTreeItemPtr CreateItemFor(const TreeItemData& Data, bool bForce = false)` — Attempt to create a tree item for a given data type. @param bForce should the item be created regardless if it passes the filters or not @return returns a shared pointer to the new item if it was created may be invalid if the item was not created
- L40 _public function_ `virtual void CreateViewContent(FMenuBuilder& MenuBuilder)` — Fill the view button menu with content
- L43 _public function_ `virtual void InitializeViewMenuExtender(TSharedPtr<FExtender> Extender)` — Allows extending SceneOutliner View Button MenuBuilder (allows using ExtensionHooks which isn't possible with CreateViewContent override)
- L46 _public function_ `virtual FCreateSceneOutlinerMode CreateFolderPickerMode(const FFolder::FRootObject& InRootObject = FFolder::GetInvalidRootObject()) const` — Returns a factory to create a Folder Picker mode which matches this mode
- L49 _public function_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const` — Construct a new Drag and drop operation
- L56 _public function_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const` — Populates a drag/drop operation if the mode supports that type of operation. @param OutPayload:	The payload data will be stored here after parsing @return				Returns true if the operation is supported by the mode
- L59 _public function_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const` — Test whether the specified payload can be dropped onto this tree item
- L62 _public function_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const` — Called when a payload is dropped onto a target
- L65 _public function_ `virtual FReply OnDragOverItem(const FDragDropEvent& Event, const ISceneOutlinerTreeItem& Item) const` — Called when a payload is dragged over an item
- L68 _public function_ `virtual bool UpdateOperationDecorator(const FDragDropEvent& Event, const FSceneOutlinerDragValidationInfo* ValidationInfo) const` — Called when a drag-over/enter/leave warrants updating the DragDrop decorator, (ValidationInfo == nullptr, indicates resetting the decorator)
- L73 _public function_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item)` — Called by the outliner when a new item is added to the outliner tree
- L75 _public function_ `virtual void OnItemRemoved(FSceneOutlinerTreeItemPtr Item)` — Called by the outliner when an item is removed from the outliner tree
- L77 _public function_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection)` — Called by the outliner when an item is selected in the tree. Used to partially synchronize selection
- L79 _public function_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item)` — Called by the outliner when a tree item is double clicked
- L81 _public function_ `virtual void OnItemClicked(FSceneOutlinerTreeItemPtr Item)` — Called by the outliner when a tree item is single-clicked
- L83 _public function_ `virtual void OnFilterTextChanged(const FText& InFilterText)` — Called by the outliner when search box text is changed
- L85 _public function_ `virtual void OnFilterTextCommited(FSceneOutlinerItemSelection& Selection, ETextCommit::Type CommitType)` — Called by the outliner when search box text is committed (by pressing enter)
- L87 _public function_ `virtual void OnItemPassesFilters(const ISceneOutlinerTreeItem& Item)` — Called by the outliner when an item passes filters but isn't yet added to the tree
- L89 _public function_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent)` — Called by the outliner when a key is pressed
- L92 _public function_ `virtual TSharedPtr<SWidget> CreateContextMenu()` — Returns a context menu widget based on the current selection
- L94 _public function_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const` — Check if an item can be renamed
- L96 _public function_ `virtual bool CanCustomizeToolbar() const` — Whether the toolbar can be customized.
- L98 _public function_ `virtual void CustomAddToToolbar(TSharedPtr<SHorizontalBox> Toolbar)` — Add mode-specific controls to the toolbar. Called when CanCustomizeToolbar() returns true.
- L100 _public function_ `virtual bool CanInteract(const ISceneOutlinerTreeItem& Item) const` — Check if an item is interactive
- L102 _public function_ `virtual bool CanPopulate() const` — Check if we are allowed to repopulate
- L105 _public function_ `virtual void SynchronizeSelection()` — Synchronize the mode specific selection with the tree view
- L107 _public function_ `virtual void OnDuplicateSelected()` — Trigger a duplication of selected items
- L110 _public function_ `virtual FFolder::FRootObject GetRootObject() const` — Returns the root object of this outliner mode
- L112 _public function_ `virtual FFolder::FRootObject GetPasteTargetRootObject() const` — Returns the target root object for a paste operation
- L115 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const` — Get the current selection mode
- L117 _public function_ `virtual int32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const` — Get the sort priority of an item
- L119 _public function_ `virtual bool SupportsKeyboardFocus() const` — Does the mode support keyboard focus
- L121 _public function_ `virtual FText GetStatusText() const` — Get the current status text
- L123 _public function_ `virtual FSlateColor GetStatusTextColor() const` — Get the color of the status text
- L125 _public function_ `virtual bool ShouldShowFolders() const` — Should folders be shown in the outliner
- L127 _public function_ `virtual bool SupportsCreateNewFolder() const` — Should the new folder button be displayed by the outliner
- L129 _public function_ `virtual bool IsInteractive() const` — Is the mode interactive
- L131 _public function_ `virtual bool ShowStatusBar() const` — Does the mode want to display a status bar
- L133 _public function_ `virtual bool ShowViewButton() const` — Does the mode want to display a view button
- L135 _public function_ `virtual bool ShowFilterOptions() const` — Does the mode allow the user to enable and disable filters through a menu
- L138 _public function_ `virtual bool CanDelete() const` — Can the current selection be deleted
- L140 _public function_ `virtual bool CanRename() const` — Can the current selection be renamed
- L142 _public function_ `virtual bool CanCut() const` — Can the current selection be cut
- L144 _public function_ `virtual bool CanCopy() const` — Can the current selection be copied
- L146 _public function_ `virtual bool CanPaste() const` — Can the current selection be pasted
- L149 _public function_ `virtual bool CanSupportDragAndDrop() const` — Does the mode support drag and drop
- L152 _public function_ `virtual bool HasErrors() const` — Does the mode reports errors
- L155 _public function_ `virtual FText GetErrorsText() const` — Return the errors text
- L158 _public function_ `virtual void RepairErrors() const` — Repair errors
- L161 _public function_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList)` — Bind commands for this mode to the given CommandList
- L167 _public function_ `virtual FFolder CreateNewFolder()` — Creates a new folder item at the root with a valid name
- L169 _public function_ `virtual FFolder GetFolder(const FFolder& ParentPath, const FName& LeafName)` — Returns a unique folder path for a specific parent with a given leaf name (without creating it)
- L171 _public function_ `virtual bool CreateFolder(const FFolder& NewFolder)` — Create a folder under a specific parent with a given leaf name
- L173 _public function_ `virtual bool ReparentItemToFolder(const FFolder& FolderPath, const FSceneOutlinerTreeItemPtr& Item)` — Reparent an item to a given folder path. Returns true if the operation is sucessful
- L175 _public function_ `virtual void SelectFoldersDescendants(const TArray<FFolderTreeItem*>& FolderItems, bool bSelectImmediateChildrenOnly)` — Select all descendants of a folder. Optionally select only immediate descendants.
- L177 _public function_ `virtual bool HasCustomFolderDoubleClick() const` — Returns true if this mode overrides the default folder double click behavior (expanding the subtree)
- L180 _public function_ `virtual void PinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems)` — Pins an item list in the outliner
- L182 _public function_ `virtual void UnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems)` — Unpins an item list in the outliner
- L184 _public function_ `virtual bool CanPinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const` — Returns true if any of the items can be pinned.
- L186 _public function_ `virtual bool CanUnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const` — Returns true if any of the items can be unpinned.
- L189 _public function_ `virtual bool CompareItemWithClassName(SceneOutliner::FilterBarType InItem, const TSet<FTopLevelAssetPath>&) const` — Function called by the Outliner Filter Bar to compare an item with Type Filters
- L192 _public function_ `virtual void Tick()` — Function called at the start of the Outliner's tick to allow the mode to perform operations
- L196 _public function_ `ISceneOutlinerHierarchy* GetHierarchy()`
- L197 _public function_ `TMap<FName, FSceneOutlinerFilterInfo>& GetFilterInfos()`
- L199 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() = 0;`
- L201 _protected member_ `TMap<FName, FSceneOutlinerFilterInfo> FilterInfoMap;`
- L202 _protected member_ `TUniquePtr<ISceneOutlinerHierarchy> Hierarchy;`
- L204 _protected member_ `SSceneOutliner* SceneOutliner;`
- L206 _private prototype_ `ISceneOutlinerMode() = delete;`
- L207 _private prototype_ `ISceneOutlinerMode(const ISceneOutliner&) = delete;`
- L208 _private prototype_ `ISceneOutlinerMode& operator=(const ISceneOutliner&) = delete;`

#### Free symbols / members of external scopes

- L36 _function_ `return SceneOutliner->CreateItemFor<TreeItemType>(Data, [this](const ISceneOutlinerTreeItem& Item) { OnItemPassesFilters(Item); }, bForce);` (scope `ISceneOutlinerMode::CreateItemFor`)

### `Source/Editor/SceneOutliner/Public/ISceneOutlinerTreeItem.h` (Public)


#### struct `ISceneOutlinerTreeItem`  
`struct ISceneOutlinerTreeItem : TSharedFromThis<ISceneOutlinerTreeItem>`  
_L16-196_
- inherits: `TSharedFromThis<ISceneOutlinerTreeItem>`
- desc: Base tree item interface
- L43 _public member_ `FlagsType Flags;` — Flags for this item
- L46 _public member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;` — Weak Outliner pointer
- L49 _public prototype_ `DECLARE_DELEGATE( FOnRenameRequest );` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L52 _public member_ `FOnRenameRequest RenameRequestEvent;` — Broadcasts whenever a rename is requested
- L57 _protected function_ `ISceneOutlinerTreeItem(FSceneOutlinerTreeItemType InType) : Parent(nullptr), TreeType(InType)` — Default constructor
- L58 _protected prototype_ `virtual ~ISceneOutlinerTreeItem() = default;`
- L61 _protected member_ `mutable TWeakPtr<ISceneOutlinerTreeItem> Parent;` — This item's parent, if any.
- L64 _protected member_ `mutable TSet<TWeakPtr<ISceneOutlinerTreeItem>> Children;` — Array of children contained underneath this item
- L67 _protected member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for the base class tree item
- L70 _protected member_ `FSceneOutlinerTreeItemType TreeType;` — Tree item type identifier
- L74 _public function_ `FSceneOutlinerTreeItemPtr GetParent() const` — Get this item's parent. Can be nullptr.
- L80 _public function_ `void AddChild(FSceneOutlinerTreeItemRef Child)` — Add a child to this item
- L88 _public function_ `void RemoveChild(const FSceneOutlinerTreeItemRef& Child)` — Remove a child from this item
- L97 _public function_ `FORCEINLINE const TSet<TWeakPtr<ISceneOutlinerTreeItem>>& GetChildren() const` — Get this item's children, if any.
- L102 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const ISceneOutlinerTreeItem& Item);`
- L103 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const ISceneOutlinerTreeItem& Item);`
- L105 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L110 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L117 _public function_ `template <typename T> T* CastTo()` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L123 _public function_ `template <typename T> const T* CastTo() const` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L129 _public function_ `template <typename T> bool IsA() const` — Returns true if this item is of the specified type
- L134 _public function_ `bool IsA(const FSceneOutlinerTreeItemType& InType) const`
- L139 _public function_ `const FSceneOutlinerTreeItemType& GetType() const`
- L142 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the data the item references is valid
- L147 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const = 0;` — Get the ID that represents this tree item. Used to reference this item in a map
- L150 _public function_ `virtual FFolder::FRootObject GetRootObject() const` — Get the optional context object root of a tree item.
- L153 _public prototype_ `virtual FString GetDisplayString() const = 0;` — Get the raw string to display for this tree item - used for sorting
- L156 _public prototype_ `virtual bool CanInteract() const = 0;` — Check whether it should be possible to interact with this tree item
- L159 _public function_ `virtual void OnExpansionChanged()` — Called when this item is expanded or collapsed
- L162 _public function_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow)` — Generate the label widget for this item
- L165 _public function_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner)` — Generate a context menu for this item. Only called if *only* this item is selected.
- L168 _public function_ `virtual void OnVisibilityChanged(const bool bNewVisibility)` — Called when this items visibility changed
- L171 _public function_ `virtual bool ShouldShowVisibilityState() const` — Returns true if this item should show its visibility state
- L174 _public function_ `virtual bool HasVisibilityInfo() const` — Returns true if this item can set its own visibility
- L177 _public function_ `virtual bool GetVisibility() const` — Query this items visibility state. Only called if the item type has visibility info
- L180 _public function_ `virtual bool ShouldShowPinnedState() const` — Returns true if this item should show pinned state
- L183 _public function_ `virtual bool HasPinnedStateInfo() const` — Returns true if this item can set its own pinned state
- L186 _public function_ `virtual bool GetPinnedState() const` — Query the pinned staet of this item. Only called if the item has its own pinned state info
- L189 _public function_ `virtual void OnLabelChanged()` — Called when this item's label has changed
- L192 _public function_ `virtual bool ShouldRemoveOnceLastChildRemoved() const` — Whether the item should be removed when the last child has been removed.
- L195 _public function_ `virtual FString GetPackageName() const` — Returns (optionally) the name of the UPackage this item represents/is-part-of

#### struct `ISceneOutlinerTreeItem::FlagsType`  
`struct FlagsType`  
_L22-38_
- desc: Flags structure
- L25 _public member_ `bool bIsExpanded : 1;` — Whether this item is expanded or not
- L28 _public member_ `bool bIsFilteredOut : 1;` — true if this item is filtered out
- L31 _public member_ `bool bInteractive : 1;` — true if this item can be interacted with as per the current outliner filters
- L34 _public member_ `bool bChildrenRequireSort : 1;` — true if this item's children need to be sorted
- L37 _public function_ `FlagsType() : bIsExpanded(1), bIsFilteredOut(0), bInteractive(1), bChildrenRequireSort(1)` — Default constructor

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENEOUTLINER_API`
- L49 _delegate_ `DECLARE_DELEGATE( FOnRenameRequest );` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L102 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const ISceneOutlinerTreeItem& Item);`
- L103 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const ISceneOutlinerTreeItem& Item);`

### `Source/Editor/SceneOutliner/Public/LevelTreeItem.h` (Public)


#### struct `FLevelTreeItem`  
`struct FLevelTreeItem : ISceneOutlinerTreeItem`  
_L12-48_
- inherits: `ISceneOutlinerTreeItem`
- desc: A tree item that represents a level in the world
- L16 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L18 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const ULevel*);`
- L19 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const ULevel*);`
- L21 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L26 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L32 _public member_ `mutable TWeakObjectPtr<ULevel> Level;` — The level this tree item is associated with.
- L35 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L38 _public prototype_ `FLevelTreeItem(ULevel* InLevel);` — Construct this item from a level
- L41 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L42 _public function_ `virtual FSceneOutlinerTreeItemID GetID() const override`
- L43 _public prototype_ `virtual FString GetDisplayString() const override;`
- L44 _public prototype_ `virtual bool CanInteract() const override;`
- L45 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L46 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SCENEOUTLINER_API`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const ULevel*);`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const ULevel*);`

### `Source/Editor/SceneOutliner/Public/SOutlinerTreeView.h` (Public)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SSceneOutlinerTreeView>`  
_L14-17_
- L16 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SSceneOutlinerTreeView`  
`class SSceneOutlinerTreeView : public STreeView< FSceneOutlinerTreeItemPtr >`  
_L19-42_
- inherits: `STreeView<FSceneOutlinerTreeItemPtr>`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SSceneOutliner> Owner);` — Construct this widget
- L26 _public prototype_ `void FlashHighlightOnItem( FSceneOutlinerTreeItemPtr FlashHighlightOnItem );`
- L28 _public function_ `const TWeakPtr<SSceneOutliner>& GetOutlinerPtr()`
- L31 _protected prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L33 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L35 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L38 _private prototype_ `virtual void Private_UpdateParentHighlights() override;`
- L41 _private member_ `TWeakPtr<SSceneOutliner> SceneOutlinerWeak;` — Weak reference to the outliner widget that owns this list

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SSceneOutlinerTreeRow>`  
_L45-48_
- L16 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SSceneOutlinerTreeRow`  
`class SSceneOutlinerTreeRow : public SMultiColumnTableRow< FSceneOutlinerTreeItemPtr >`  
_L51-131_
- inherits: `SMultiColumnTableRow<FSceneOutlinerTreeItemPtr>`
- desc: Widget that represents a row in the outliner's tree control.  Generates widgets for each column on demand.
- L57 _public function_ `SLATE_BEGIN_ARGS( SSceneOutlinerTreeRow )`
- L60 _public prototype_ `SLATE_ARGUMENT( FSceneOutlinerTreeItemPtr, Item ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<SSceneOutlinerTreeView>& OutlinerTreeView, TSharedRef<SSceneOutliner> SceneOutliner );` — The list item for this row
- L69 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L71 _public prototype_ `void FlashHighlight();`
- L74 _protected prototype_ `virtual bool ComputeVolatility() const override;`
- L76 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L77 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L78 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L80 _protected prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L82 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L84 _protected prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L86 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L88 _protected prototype_ `bool IsRowEnabled() const;`
- L93 _private member_ `TWeakPtr< SSceneOutliner > SceneOutlinerWeak;` — Weak reference to the outliner widget that owns our list
- L96 _private member_ `TWeakPtr<ISceneOutlinerTreeItem> Item;` — The item associated with this row of data
- L100 _protected prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L102 _protected prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L106 _private member_ `static const float HighlightRectLeftOffset;` — How many pixels to extend the highlight rectangle's left side horizontally
- L109 _private member_ `static const float HighlightRectRightOffset;` — How many pixels to extend the highlight rectangle's right side horizontally
- L112 _private member_ `static const float HighlightTargetSpringConstant;` — How quickly the highlight 'targeting' rectangle will slide around.  Larger is faster.
- L115 _private member_ `static const float HighlightTargetEffectDuration;` — Duration of animation highlight target effects
- L118 _private member_ `static const float HighlightTargetOpacity;` — Opacity of the highlight target effect overlay
- L121 _private member_ `static const float LabelChangedAnimOffsetPercent;` — How large the highlight target effect will be when highlighting, as a scalar percentage of font height
- L124 _private member_ `FFloatSpring1D HighlightTargetLeftSpring;` — Highlight "targeting" visual effect left position
- L127 _private member_ `FFloatSpring1D HighlightTargetRightSpring;` — Highlight "targeting" visual effect right position
- L130 _private member_ `double LastHighlightInteractionTime;` — Last time that the user had a major interaction with the highlight

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SSceneOutlinerPinnedTreeRow>`  
_L134-137_
- L16 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SSceneOutlinerPinnedTreeRow`  
`class SSceneOutlinerPinnedTreeRow : public SMultiColumnTableRow< FSceneOutlinerTreeItemPtr >`  
_L140-189_
- inherits: `SMultiColumnTableRow<FSceneOutlinerTreeItemPtr>`
- desc: Widget that represents a pinned row in the outliner's tree control.
- L146 _public function_ `SLATE_BEGIN_ARGS(SSceneOutlinerPinnedTreeRow)`
- L149 _public prototype_ `SLATE_ARGUMENT(FSceneOutlinerTreeItemPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SSceneOutlinerTreeView>& OutlinerTreeView, TSharedRef<SSceneOutliner> SceneOutliner);` — The list item for this row
- L158 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L162 _protected function_ `virtual void ConstructChildren(ETableViewMode::Type InOwnerTableMode, const TAttribute<FMargin>& InPadding, const TSharedRef<SWidget>& InContent) override`
- L174 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L175 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L176 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L177 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L182 _private member_ `TWeakPtr< SSceneOutliner > SceneOutlinerWeak;` — Weak reference to the outliner widget that owns our list
- L185 _private member_ `TWeakPtr< SSceneOutlinerTreeView > OutlinerTreeViewWeak;` — Weak reference to the tree view that contains our list
- L188 _private member_ `TWeakPtr<ISceneOutlinerTreeItem> Item;` — The item associated with this row of data

### `Source/Editor/SceneOutliner/Public/SSceneOutliner.h` (Public)


#### struct `SceneOutliner::FPendingTreeOperation`  
`struct FPendingTreeOperation`  
_L65-75_
- desc: Structure that defines an operation that should be applied to the tree
- L68 _public function_ `FPendingTreeOperation(EType InType, TSharedRef<ISceneOutlinerTreeItem> InItem) : Type(InType), Item(InItem)`
- L71 _public member_ `EType Type;` — The type of operation that is to be applied
- L74 _public member_ `FSceneOutlinerTreeItemRef Item;` — The tree item to which this operation relates

#### enum `SceneOutliner::FPendingTreeOperation::EType`  
`enum EType`  
_L67-67_
- L67 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<ISceneOutlinerTreeItem> InItem) : Type(InType)`
- L67 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<ISceneOutlinerTreeItem> InItem) : Type(InType)`
- L67 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<ISceneOutlinerTreeItem> InItem) : Type(InType)`

#### enum `SceneOutliner::ENewItemAction::Type`  
`enum Type : uint8`  
_L80-90_
- L83 _public enumerator_ `None = 0` — Do nothing when it is created
- L85 _public enumerator_ `Select = 1 << 0` — Select the item when it is created
- L87 _public enumerator_ `ScrollIntoView = 1 << 1` — Scroll the item into view when it is created
- L89 _public enumerator_ `Rename = 1 << 2` — Interactively rename the item when it is created (implies the above)

#### struct `FSceneOutlinerItemSelection`  
`struct FSceneOutlinerItemSelection`  
_L103-233_
- desc: Stores a set of selected items with parsing functions for the scene outliner
- L106 _public member_ `mutable TArray<TWeakPtr<ISceneOutlinerTreeItem>> SelectedItems;` — Set of selected items
- L108 _public function_ `FSceneOutlinerItemSelection()`
- L110 _public function_ `FSceneOutlinerItemSelection(const TArray<FSceneOutlinerTreeItemPtr>& InSelectedItems) : SelectedItems(InSelectedItems)`
- L113 _public function_ `FSceneOutlinerItemSelection(SSceneOutlinerTreeView& Tree) : FSceneOutlinerItemSelection(Tree.GetSelectedItems())`
- L118 _public function_ `template <typename TreeType> bool Has() const` — Returns true if the selection has an item of a specified type
- L134 _public function_ `uint32 Num() const` — Returns the total number of items in the selection
- L141 _public function_ `template <typename ...TreeTypes> uint32 Num() const` — Returns the number of items of the specified types in the selection
- L158 _public function_ `void Add(FSceneOutlinerTreeItemPtr NewItem)` — Add a new item to the selection
- L165 _public function_ `template <typename TreeType> void Get(TArray<TreeType*>& OutArray) const` — Get all items of a specified type
- L179 _public function_ `void Get(TArray<FSceneOutlinerTreeItemPtr>& OutArray) const`
- L192 _public function_ `template <typename TreeType> void ForEachItem(TFunctionRef<void(TreeType&)> Func) const` — Apply a function to each item of a specified type
- L207 _public function_ `void ForEachItem(TFunctionRef<void(FSceneOutlinerTreeItemPtr&)> Func) const` — Apply a function to every item in the selection regardless of type.
- L220 _public function_ `template <typename DataType> TArray<DataType> GetData(TFunctionRef<bool(const TWeakPtr<ISceneOutlinerTreeItem>&, DataType&)> Selector) const` — Use a selector to retrieve a specific data type from items in the selection. Will only add an item's data if the selector returns true for that item.

#### class `SSceneOutliner`  
`class SSceneOutliner : public ISceneOutliner, public FEditorUndoClient, public FGCObject`  
_L238-1107_
- inherits: `ISceneOutliner,FEditorUndoClient,FGCObject`
- desc: Scene Outliner widget
- L243 _public function_ `SLATE_BEGIN_ARGS(SSceneOutliner)`
- L245 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FSceneOutlinerInitializationOptions& InitOptions);`
- L256 _public function_ `SSceneOutliner() : SharedData(MakeShareable(new FSharedSceneOutlinerData)) , Filters(MakeShareable(new FSceneOutlinerFilters)) , InteractiveFilters(MakeShareable(new FSceneOutlinerFilters))` — Default constructor - initializes data that is shared between all tree items
- L263 _public prototype_ `virtual ~SSceneOutliner();` — SSceneOutliner destructor
- L266 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L267 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L268 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L271 _public prototype_ `virtual void Refresh() override;` — Sends a requests to the Scene Outliner to refresh itself the next chance it gets
- L273 _public prototype_ `void RefreshSelection();`
- L276 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L277 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L281 _public function_ `virtual const FSharedSceneOutlinerData& GetSharedData() const override` — @return Returns the common data for this outliner
- L287 _public function_ `virtual const STreeView<FSceneOutlinerTreeItemPtr>& GetTree() const override` — Get a const reference to the actual tree hierarchy
- L292 _public function_ `virtual const TSharedPtr< SSceneOutlinerTreeView>& GetTreeView() const`
- L298 _public prototype_ `virtual TAttribute<FText> GetFilterHighlightText() const override;` — @return Returns a string to use for highlighting results in the outliner list
- L301 _public prototype_ `SceneOutliner::TreeItemTextFilter::FChangedEvent& OnTextFilterChanged() const;` — @return Returns an Event to use for highlighting changes in the outliner list
- L304 _public prototype_ `virtual void SetKeyboardFocus() override;` — Set the keyboard focus to the outliner
- L307 _public prototype_ `virtual const FSlateBrush* GetCachedIconForClass(FName InClassName) const override;` — Gets the cached icon for this class name
- L310 _public prototype_ `virtual void CacheIconForClass(FName InClassName, const FSlateBrush* InSlateBrush) override;` — Sets the cached icon for this class name
- L313 _public prototype_ `virtual bool CanExecuteRenameRequest(const ISceneOutlinerTreeItem& ItemPtr) const override;` — Should the scene outliner accept a request to rename a object
- L320 _public prototype_ `virtual int32 AddFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) override;` — Add a filter to the scene outliner @param Filter The filter to apply to the scene outliner @return The index of the filter.
- L326 _public prototype_ `virtual void AddFilterToFilterBar(const TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>& InFilter) override;` — Add a filter to the scene outliner's filter bar @param Filter The filter to add
- L332 _public prototype_ `virtual void DisableAllFilterBarFilters(bool bRemove) override;` — Disable all filters currently active in the filter bar @param bRemove if true, the filter will also be unpinned and removed from the filter bar
- L340 _public prototype_ `virtual bool RemoveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) override;` — Remove a filter from the scene outliner @param Filter The Filter to remove @return True if the filter was removed.
- L347 _public prototype_ `virtual int32 AddInteractiveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) override;` — Add an interactive filter to the scene outliner @param Filter The filter used to determine if scene outliner items are interactive. @return The index of the filter.
- L354 _public prototype_ `virtual bool RemoveInteractiveFilter(const TSharedRef<FSceneOutlinerFilter>& Filter) override;` — Remove an interactive  filter from the scene outliner @param Filter The Filter to remove @return True if the filter was removed.
- L361 _public prototype_ `virtual TSharedPtr<FSceneOutlinerFilter> GetFilterAtIndex(int32 Index) override;` — Retrieve the filter at the specified index @param Index The index of the filter to retrive @return A valid poiter to a filter if the index was valid
- L364 _public prototype_ `virtual int32 GetFilterCount() const override;` — Get number of filters applied to the scene outliner
- L372 _public prototype_ `virtual void AddColumn(FName ColumnId, const FSceneOutlinerColumnInfo& ColumnInfo) override;` — Add or replace a column of the scene outliner Note: The column id must match the id of the column returned by the factory @param ColumnId The id of the column to add @param ColumnInfo The struct that contains the information on how to present and retrieve the column
- L378 _public prototype_ `virtual void RemoveColumn(FName ColumnId) override;` — Remove a column of the scene outliner @param ColumnId The name of the column to remove
- L380 _public prototype_ `void SetColumnVisibility(FName ColumnId, bool bIsVisible);`
- L383 _public prototype_ `virtual TArray<FName> GetColumnIds() const override;` — Return the name/Id of the columns of the scene outliner
- L386 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — @return Returns the current sort mode of the specified column
- L389 _public prototype_ `virtual void RequestSort();` — Request that the tree be sorted at a convenient time
- L392 _public prototype_ `virtual bool Delete_CanExecute();` — Returns true if edit delete can be executed
- L395 _public prototype_ `virtual bool Rename_CanExecute();` — Returns true if edit rename can be executed
- L398 _public prototype_ `virtual void Rename_Execute();` — Executes rename.
- L401 _public prototype_ `virtual bool Cut_CanExecute();` — Returns true if edit cut can be executed
- L404 _public prototype_ `virtual bool Copy_CanExecute();` — Returns true if edit copy can be executed
- L407 _public prototype_ `virtual bool Paste_CanExecute();` — Returns true if edit paste can be executed
- L410 _public prototype_ `virtual bool CanSupportDragAndDrop() const override;` — Can the scene outliner rows generated on drag event
- L413 _public prototype_ `virtual void FullRefresh() override;` — Tells the scene outliner that it should do a full refresh, which will clear the entire tree and rebuild it from scratch.
- L416 _public prototype_ `virtual void CustomAddToToolbar(TSharedPtr<class SHorizontalBox> Toolbar);` — Hook to add custom options to toolbar in a derived class. Defaults to delegating to the mode's CustomAddToToolbar.
- L419 _public prototype_ `virtual bool IsFilterActive(const FString& FilterName) const override;` — Check if a filter with the given name exists and is active in the filter bar for this Outliner (if this Outliner has a filter bar).
- L422 _public prototype_ `virtual FSceneOutlinerTreeItemPtr GetTreeItem(FSceneOutlinerTreeItemID, bool bIncludePending = false) override;` — Retrieve an ISceneOutlinerTreeItem by its ID if it exists in the tree
- L426 _public prototype_ `virtual void SetNextUIRefreshDelay(float InDelay) override;` — Set a delay (in seconds) before the the next requested UI refresh executes. Note: This only applies until the next refresh that executes and any subsequent ones will be immediate.
- L430 _public function_ `SceneOutliner::FTreeItemPtrEvent& GetDoubleClickEvent()` — Event to react to a user double click on a item
- L436 _public function_ `SceneOutliner::FOnItemSelectionChanged& GetOnItemSelectionChanged()` — Allow the system that use the scene outliner to react when it's selection is changed Note: This event will only be broadcast on a user input.
- L439 _public function_ `FSimpleMulticastDelegate& GetOnFullRefreshDone()` — Event that's broadcast after the scene outliner has been re-populated.
- L442 _public prototype_ `virtual void SetSelection(const TFunctionRef<bool(ISceneOutlinerTreeItem&)> Selector) override;` — Set the item selection of the outliner based on a selector function. Any items which return true will be added
- L445 _public prototype_ `void SetItemSelection(const TArray<FSceneOutlinerTreeItemPtr>& InItems, bool bSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Set the selection status of a set of items in the scene outliner
- L448 _public prototype_ `void SetItemSelection(const FSceneOutlinerTreeItemPtr& InItem, bool bSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Set the selection status of a single item in the scene outliner
- L451 _public prototype_ `void AddToSelection(const TArray<FSceneOutlinerTreeItemPtr>& InItems, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Adds a set of items to the current selection
- L454 _public prototype_ `void RemoveFromSelection(const TArray<FSceneOutlinerTreeItemPtr>& InItems, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Remove a set of items from the current selection
- L457 _public prototype_ `void RemoveFromSelection(const FSceneOutlinerTreeItemPtr& InItem, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Remove a single item from the current selection
- L460 _public prototype_ `void AddToSelection(const FSceneOutlinerTreeItemPtr& InItem, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Adds a single item to the current selection
- L465 _public function_ `virtual TArray<FSceneOutlinerTreeItemPtr> GetSelectedItems() const` — Returns the list of currently selected tree items
- L470 _public function_ `virtual FSceneOutlinerItemSelection GetSelection() const` — Returns the currently selected items.
- L475 _public prototype_ `virtual void PinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;` — Pins an item list in the outliner.
- L480 _public prototype_ `virtual void UnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) override;` — Unpins an item list in the outliner.
- L485 _public prototype_ `virtual bool CanPinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;` — Returns true if any of the items can be pinned.
- L490 _public prototype_ `virtual bool CanUnpinItems(const TArray<FSceneOutlinerTreeItemPtr>& InItems) const override;` — Returns true if any of the items can be unpinned.
- L495 _public prototype_ `virtual void PinSelectedItems() override;` — Pin selected items
- L500 _public prototype_ `virtual void UnpinSelectedItems() override;` — Unpins selected items
- L505 _public prototype_ `virtual bool CanPinSelectedItems() const override;` — Returns true if any of the selected items can be pinned
- L510 _public prototype_ `virtual bool CanUnpinSelectedItems() const override;` — Returns true if any of the selected items can be unpinned
- L516 _public prototype_ `virtual void FrameSelectedItems() override;` — Scrolls the outliner to the selected item(s). If more are selected, the chosen item is undeterministic.
- L522 _public prototype_ `virtual void FrameItem(const FSceneOutlinerTreeItemID& Item) override;` — Scrolls the outliner to the specified item if it's found. No action is done otherwise.
- L527 _public prototype_ `FSceneOutlinerTreeItemPtr FindParent(const ISceneOutlinerTreeItem& InItem) const;` — Returns the parent tree item for a given item if it exists, nullptr otherwise.
- L533 _public prototype_ `void AddFolderToSelection(const FName& FolderName);` — Add a folder to the selection of the scene outliner @param FolderName The name of the folder to add to selection
- L539 _public prototype_ `void RemoveFolderFromSelection(const FName& FolderName);` — Remove a folder from the selection of the scene outliner @param FolderName The name of the folder to remove from the selection
- L542 _public prototype_ `void ClearSelection();` — Deselect all selected items
- L545 _public function_ `void SetPendingRenameItem(const FSceneOutlinerTreeItemPtr& InItem)` — Sets the next item to rename
- L548 _public function_ `TSharedPtr<FSceneOutlinerFilters>& GetFilters()` — Get the outliner filter collection
- L551 _public prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const;` — Create a drag drop operation
- L554 _public prototype_ `bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const;` — Parse a drag drop operation into a payload
- L557 _public prototype_ `FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const;` — Validate a drag drop operation on a drop target
- L560 _public prototype_ `void OnDropPayload(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const;` — Called when a payload is dropped onto a target
- L563 _public prototype_ `FReply OnDragOverItem(const FDragDropEvent& Event, const ISceneOutlinerTreeItem& Item) const;` — Called when a payload is dragged over an item
- L566 _public prototype_ `bool UpdateOperationDecorator(const FDragDropEvent& Event, const FSceneOutlinerDragValidationInfo* ValidationInfo) const;` — Called when a drag-over/enter/leave warrants updating the DragDrop decorator
- L569 _public function_ `bool GetIsReentrant() const` — Used to test if Outliner related selection changes have already been handled
- L572 _public function_ `virtual FName GetOutlinerIdentifier() const override` — Get the unique identifier associated with this outliner
- L575 _public function_ `void SetShowTransient(bool bInShowTransient)` — Toggle if SceneOutliner should show Transient objects
- L581 _private prototype_ `void EmptyTreeItems();` — Empty all the tree item containers maintained by this outliner
- L584 _private prototype_ `void Populate();` — Apply incremental changes to, or a complete repopulation of the tree
- L587 _private prototype_ `void RepopulateEntireTree();` — Repopulates the entire tree
- L590 _private prototype_ `void AddPendingItem(FSceneOutlinerTreeItemPtr Item);` — Adds a single new item to the pending map and creates an add operation for it
- L593 _private prototype_ `void AddPendingItemAndChildren(FSceneOutlinerTreeItemPtr Item);` — Adds a new item and all of its children to the pending items.
- L596 _private prototype_ `bool AddItemToTree(FSceneOutlinerTreeItemRef InItem);` — Attempts to add a pending item to the current tree. Will add any parents if required.
- L599 _private prototype_ `void AddUnfilteredItemToTree(FSceneOutlinerTreeItemRef Item);` — Add an item to the tree, even if it doesn't match the filter terms. Used to add parent's that would otherwise be filtered out
- L602 _private prototype_ `FSceneOutlinerTreeItemPtr EnsureParentForItem(FSceneOutlinerTreeItemRef Item);` — Ensure that the specified item's parent is added to the tree, if applicable
- L605 _private prototype_ `void RemoveItemFromTree(FSceneOutlinerTreeItemRef InItem);` — Remove the specified item from the tree
- L608 _private prototype_ `void OnChildRemovedFromParent(ISceneOutlinerTreeItem& Parent);` — Called when a child has been removed from the specified parent. Will potentially remove the parent from the tree
- L611 _private prototype_ `void OnItemMoved(const FSceneOutlinerTreeItemRef& Item);` — Called when a child has been moved in the tree hierarchy
- L616 _public function_ `template <typename TreeItemType, typename TreeItemData> FSceneOutlinerTreeItemPtr CreateItemFor(const TreeItemData& Data, TFunctionRef<void(const TreeItemType&)> OnItemPassesFilters, bool bForce = false)` — Test the filters using stack-allocated data to prevent unnecessary heap allocations
- L649 _public prototype_ `void OnItemAdded(const FSceneOutlinerTreeItemID& ItemID, uint8 ActionMask);` — Instruct the outliner to perform an action on the specified item when it is created
- L652 _public function_ `const TMap<FName, TSharedPtr<ISceneOutlinerColumn>>& GetColumns() const` — Get the columns to be displayed in this outliner
- L657 _public prototype_ `void GetSortedColumnIDs(TArray<FName>& OutColumnIDs) const;`
- L659 _public function_ `bool PassesFilters(const ISceneOutlinerTreeItem& Item) const`
- L665 _public prototype_ `bool IsTextFilterActive() const;` — @return	Returns true if the text filter is currently active
- L667 _public function_ `bool PassesTextFilter(const FSceneOutlinerTreeItemPtr& Item) const`
- L672 _public function_ `bool PassesAllFilters(const FSceneOutlinerTreeItemPtr& Item) const`
- L690 _public function_ `bool HasSelectorFocus(FSceneOutlinerTreeItemPtr Item) const`
- L696 _public prototype_ `void OnItemLabelChanged(FSceneOutlinerTreeItemPtr ChangedItem, bool bFlashHighlight = true);` — Handler for when a property changes on any item. Called by the mode
- L700 _private prototype_ `void BindCommands(const TSharedPtr<FUICommandList>& InCommandListToAppend);` — BindCommands for this Outliner with additional commands to append
- L703 _private member_ `TMap<FName, TSharedPtr<ISceneOutlinerColumn>> Columns;` — Map of columns that are shown on this outliner.
- L706 _private prototype_ `void SetupColumns();` — Set up the columns required for this outliner
- L708 _private prototype_ `void HandleHiddenColumnsChanged();`
- L711 _private prototype_ `void RefreshColumns();` — Refresh the scene outliner columns
- L713 _private prototype_ `void AddColumn_Internal(const FName& ColumnId, const FSceneOutlinerColumnInfo& ColumnInfo, const TMap<FName, bool>& ColumnVisibilities, int32 InsertPosition = INDEX_NONE);`
- L714 _private prototype_ `void RemoveColumn_Internal(const FName& ColumnId);`
- L717 _private prototype_ `void PopulateSearchStrings( const ISceneOutlinerTreeItem& TreeItem, OUT TArray< FString >& OutSearchStrings ) const;` — Populates OutSearchStrings with the strings associated with TreeItem that should be used in searching
- L722 _private prototype_ `TSharedPtr< SceneOutliner::TreeItemTextFilter > CreateTextFilter() const;` — Creates a TextFilter for ISceneOutlinerTreeItem used to save searches as Text Filters
- L724 _private prototype_ `bool CompareItemWithClassName(SceneOutliner::FilterBarType InItem, const TSet<FTopLevelAssetPath>&) const;`
- L727 _private prototype_ `void OnFilterBarFilterChanged();` — Delegate for when a filter in the filter bar is changed
- L730 _private prototype_ `void CreateFilterBar(const FSceneOutlinerFilterBarOptions& FilterBarOptions);` — Create the filter bar for this outliner using the specified init options
- L736 _public prototype_ `void ScrollItemIntoView(const FSceneOutlinerTreeItemPtr& Item);` — Scroll the specified item into view
- L738 _public prototype_ `virtual void SetItemExpansion(const FSceneOutlinerTreeItemPtr& Item, bool bIsExpanded) override;`
- L740 _public prototype_ `bool IsItemExpanded(const FSceneOutlinerTreeItemPtr& Item) const;`
- L742 _public prototype_ `void ExpandAll();`
- L743 _public prototype_ `void CollapseAll();`
- L748 _private prototype_ `bool ShouldShowFolders() const;` — Check whether we should be showing folders or not in this scene outliner
- L751 _private prototype_ `void GetSelectedFolders(TArray<FFolderTreeItem*>& OutFolders) const;` — Get an array of selected folders
- L757 _private prototype_ `TSharedRef< ITableRow > OnGenerateRowForOutlinerTree( FSceneOutlinerTreeItemPtr Item, const TSharedRef< STableViewBase >& OwnerTable );` — Called by STreeView to generate a table row for the specified item
- L760 _private prototype_ `TSharedRef< ITableRow > OnGeneratePinnedRowForOutlinerTree(FSceneOutlinerTreeItemPtr Item, const TSharedRef< STableViewBase >& OwnerTable);` — Called by STreeView to generate a table row for the specified item is pinned
- L763 _private prototype_ `void OnGetChildrenForOutlinerTree( FSceneOutlinerTreeItemPtr InParent, TArray< FSceneOutlinerTreeItemPtr >& OutChildren );` — Called by STreeView to get child items for the specified parent item
- L766 _private prototype_ `void OnOutlinerTreeSelectionChanged( FSceneOutlinerTreeItemPtr TreeItem, ESelectInfo::Type SelectInfo );` — Called by STreeView when the tree's selection has changed
- L769 _private prototype_ `void OnOutlinerTreeDoubleClick( FSceneOutlinerTreeItemPtr TreeItem );` — Called by STreeView when the user double-clicks on an item in the tree
- L772 _private prototype_ `void OnOutlinerTreeSingleClick( FSceneOutlinerTreeItemPtr TreeItem ) const;` — Called by STreeView when the user single-clicks on an item in the tree
- L775 _private prototype_ `void OnOutlinerTreeItemScrolledIntoView( FSceneOutlinerTreeItemPtr TreeItem, const TSharedPtr<ITableRow>& Widget );` — Called by STreeView when an item is scrolled into view
- L778 _private prototype_ `void OnItemExpansionChanged(FSceneOutlinerTreeItemPtr TreeItem, bool bIsExpanded) const;` — Called when an item in the tree has been collapsed or expanded
- L783 _private prototype_ `void OnHierarchyChangedEvent(FSceneOutlinerHierarchyChangedData Event);`
- L786 _private prototype_ `void OnAssetReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Handler for when an asset is reloaded
- L790 _public prototype_ `void CopyFoldersToClipboard(const TArray<FName>& InFolders, const FString& InPrevClipboardContents);` — Copy specified folders to clipboard, keeping current clipboard contents if they differ from previous clipboard contents (meaning items were copied)
- L793 _public prototype_ `void CopyFoldersBegin();` — Called by copy and duplicate
- L796 _public prototype_ `void CopyFoldersEnd();` — Called by copy and duplicate
- L799 _public prototype_ `void PasteFoldersBegin(TArray<FName> InFolders);` — Called by paste and duplicate
- L802 _public prototype_ `void PasteFoldersEnd();` — Paste folders end logic
- L805 _public prototype_ `void DeleteFoldersBegin();` — Called by cut and delete
- L808 _public prototype_ `void DeleteFoldersEnd();` — Called by cut and delete
- L811 _public prototype_ `TArray<FName> GetClipboardPasteFolders() const;` — Get an array of folders to paste
- L814 _public prototype_ `FString ExportFolderList(TArray<FName> InFolders) const;` — Construct folders export string to be used in clipboard
- L817 _public prototype_ `TArray<FName> ImportFolderList(const FString& InStrBuffer) const;` — Construct array of folders to be created based on input clipboard string
- L821 _public prototype_ `void DuplicateFoldersHierarchy();` — Duplicates current folder and all descendants
- L823 _public prototype_ `FName GetPrimaryColumnName() const;`
- L827 _private member_ `TArray<FFolderTreeItem*> CacheFoldersDelete;` — Cache selected folders during edit delete
- L830 _private member_ `TArray<FName> CacheFoldersEdit;` — Cache folders for cut/copy/paste/duplicate
- L833 _private member_ `FFolder::FRootObject CacheFoldersEditRootObject;` — CacheFoldersEdit target root object
- L836 _private member_ `TMap<FName, FName> CacheFolderMap;` — Cache folders mapping (old to new) for cut/copy/paste/duplicate
- L839 _private member_ `FString CacheClipboardContents;` — Cache clipboard contents for cut/copy
- L842 _private member_ `TMap<FFolder, TArray<FSceneOutlinerTreeItemID>> CachePasteFolderExistingChildrenMap;` — Maps pre-existing children during paste or duplicate
- L845 _private member_ `TSet<FName> CacheHiddenColumns;` — Cache which columns are hidden to know what changed
- L848 _private prototype_ `bool GetCommonRootObjectFromSelection(FFolder::FRootObject& OutCommonRootObject) const;`
- L853 _private prototype_ `void OnFilterTextChanged( const FText& InFilterText );` — Called by the editable text control when the filter text is changed by the user
- L856 _private prototype_ `void OnFilterTextCommitted( const FText& InFilterText, ETextCommit::Type CommitInfo );` — Called by the editable text control when a user presses enter or commits their text change
- L859 _private prototype_ `const FSlateBrush* GetFilterButtonGlyph() const;` — Called by the filter button to get the image to display in the button
- L862 _private prototype_ `FString GetFilterButtonToolTip() const;` — @return	The filter button tool-tip text
- L865 _private prototype_ `EVisibility GetFilterStatusVisibility() const;` — @return	Returns whether the filter status line should be drawn
- L868 _private prototype_ `FText GetFilterStatusText() const;` — @return	Returns the filter status text
- L871 _private prototype_ `FSlateColor GetFilterStatusTextColor() const;` — @return Returns color for the filter status text message, based on success of search filter
- L874 _private prototype_ `EVisibility GetEmptyLabelVisibility() const;` — Returns the current visibility of the Empty label
- L877 _private prototype_ `ESelectionMode::Type GetSelectionMode() const;` — @return the selection mode; disabled entirely if in PIE/SIE mode
- L880 _private prototype_ `TSharedRef<SWidget> GetViewButtonContent(bool bShowFilters);` — @return the content for the view button
- L883 _private prototype_ `FSlateColor GetViewButtonForegroundColor() const;` — @return the foreground color for the view button
- L888 _public prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();` — Open a context menu for this scene outliner
- L890 _public prototype_ `void FillFoldersSubMenu(UToolMenu* Menu) const;`
- L891 _public prototype_ `void AddMoveToFolderOutliner(UToolMenu* Menu) const;`
- L892 _public prototype_ `void FillSelectionSubMenu(UToolMenu* Menun) const;`
- L893 _public prototype_ `TSharedRef<TSet<FFolder>> GatherInvalidMoveToDestinations() const;`
- L896 _public prototype_ `void SelectFoldersDescendants(bool bSelectImmediateChildrenOnly = false);` — Called to select descendants of the currently selected folders
- L899 _public prototype_ `void MoveSelectionTo(const FFolder& NewParent);` — Moves the current selection to the specified folder path
- L902 _public prototype_ `void CreateFolder();` — Create a new folder under the specified parent name (NAME_None for root)
- L906 _private prototype_ `FReply OnCreateFolderClicked();` — Called when the user has clicked the button to add a new folder
- L911 _private member_ `FOnContextMenuOpening OnContextMenuOpening;` — Context menu opening delegate provided by the client
- L913 _private member_ `TSharedPtr<FSharedSceneOutlinerData> SharedData;`
- L916 _private member_ `TArray<SceneOutliner::FPendingTreeOperation> PendingOperations;` — List of pending operations to be applied to the tree
- L919 _private member_ `TMap<FSceneOutlinerTreeItemID, uint8> NewItemActions;` — Map of actions to apply to new tree items
- L922 _private member_ `TSharedPtr< SSceneOutlinerTreeView > OutlinerTreeView;` — Our tree view
- L925 _private member_ `FSceneOutlinerTreeItemMap TreeItemMap;` — A map of all items we have in the tree
- L928 _private member_ `FSceneOutlinerTreeItemMap PendingTreeItemMap;` — Pending tree items that are yet to be added the tree
- L931 _private member_ `FSceneOutlinerTreeItemMap PendingTreeItemMap_Removal;` — Pending tree items that are yet to be removed from the tree
- L934 _private member_ `TArray<FFolder> PendingFoldersSelect;` — Folders pending selection
- L937 _private member_ `TArray<FSceneOutlinerTreeItemPtr> RootTreeItems;` — Root level tree items
- L940 _private member_ `TSharedPtr<SComboButton> ViewOptionsComboButton;` — The button that displays view options
- L943 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list to be processed during the OnKeyDown, extended by derived Mode through BindCommands
- L948 _private prototype_ `void OnColumnPermissionListChanged();` — Called when SceneOutlinerModule column permission list changes.
- L951 _private typedef_ `typedef TMap<FSceneOutlinerTreeItemID, bool> FParentsExpansionState;` — Structure containing information relating to the expansion state of parent items in the tree
- L954 _private member_ `mutable FParentsExpansionState CachedExpansionStateInfo;` — Cached expansion state info
- L960 _private member_ `uint8 bNeedsRefresh : 1;` — True if the outliner needs to be repopulated at the next appropriate opportunity, usually because our item set has changed in some way.
- L963 _private member_ `uint8 bProcessingFullRefresh : 1;` — Processing a full refresh until pending items are processed
- L966 _private member_ `uint8 bFullRefresh : 1;` — true if the Scene Outliner should do a full refresh.
- L969 _private member_ `uint8 bSelectionDirty : 1;` — true if the Scene Outliner should refresh selection
- L972 _private member_ `uint8 bDisableIntermediateSorting : 1;` — True if the Scene Outliner is currently responding to a level visibility change
- L974 _private member_ `uint8 bNeedsColumRefresh : 1;`
- L977 _private member_ `uint8 bShouldCacheColumnVisibility : 1;` — True if the outliner should cache changes to column visibility into the config
- L980 _private member_ `mutable uint8 bForceParentItemsExpanded : 1;` — True if we are forcing the underlying tree view to automatically expand all parents when searching
- L983 _private member_ `bool bIsReentrant;` — Reentrancy guard
- L986 _private member_ `float UIRefreshDelay = 0.0f;` — The delay (in seconds) before a UI sort and refresh is executed after being requested. 0 means the next refresh will be immediate
- L989 _private member_ `TSharedPtr< SFilterSearchBox > FilterTextBoxWidget;` — Widget containing the filtering text box
- L992 _private member_ `TSharedPtr< SHeaderRow > HeaderRowWidget;` — The header row of the scene outliner
- L995 _private member_ `TSharedPtr< FSceneOutlinerFilters > Filters;` — A collection of filters used to filter the displayed items and folders in the scene outliner
- L998 _private member_ `TSharedPtr< FSceneOutlinerFilters > InteractiveFilters;` — A collection of extra filters applied on top of existing Filters to determine if items are interactive or not in the scene outliner
- L1001 _private member_ `TSharedPtr< SceneOutliner::TreeItemTextFilter > SearchBoxFilter;` — The TextFilter attached to the SearchBox widget of the Scene Outliner
- L1004 _private member_ `TSharedPtr< SFilterBar< SceneOutliner::FilterBarType > > FilterBar;` — The FilterBar attached to this outliner to filter down assets further
- L1007 _private member_ `TSharedPtr< TFilterCollection< SceneOutliner::FilterBarType > > FilterCollection;` — The FilterCollection belonging to the Filter Bar
- L1010 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L1013 _private member_ `TWeakPtr<ISceneOutlinerTreeItem> PendingRenameItem;` — The tree item that is currently pending a rename
- L1015 _private member_ `TMap<FName, const FSlateBrush*> CachedIcons;`
- L1017 _private member_ `SceneOutliner::FTreeItemPtrEvent OnDoubleClickOnTreeEvent;`
- L1019 _private member_ `SceneOutliner::FOnItemSelectionChanged OnItemSelectionChanged;`
- L1021 _private member_ `FSimpleMulticastDelegate OnFullRefreshDone;`
- L1024 _private member_ `FName PrimaryColumnName;` — The primary column for this outliner, used to determine initial sorting and where the hierarchy arrows appear
- L1027 _private function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L1028 _private function_ `virtual FString GetReferencerName() const override`
- L1036 _private member_ `float SortOutlinerTimer;` — Timer for PIE/SIE mode to sort the outliner.
- L1039 _private member_ `bool bSortDirty;` — true if the outliner currently needs to be sorted
- L1042 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L1045 _private member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L1048 _private member_ `FName OutlinerIdentifier;` — Identifier for this outliner (Set through FSceneOutlinerInitializationOptions)
- L1051 _private member_ `bool bShouldStackHierarchyHeaders = true;` — true if the hierarchy of items is pinned at the top of the outliner
- L1053 _private prototype_ `void ToggleStackHierarchyHeaders();`
- L1055 _private prototype_ `bool ShouldStackHierarchyHeaders() const;`
- L1058 _private prototype_ `void OnColumnSortModeChanged( const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode );` — Handles column sorting mode change
- L1061 _private prototype_ `void SortItems(TArray<FSceneOutlinerTreeItemPtr>& Items) const;` — Sort the specified array of items based on the current sort column
- L1063 _private prototype_ `virtual uint32 GetTypeSortPriority(const ISceneOutlinerTreeItem& Item) const override;`
- L1066 _private prototype_ `void SetItemExpansionRecursive(FSceneOutlinerTreeItemPtr Model, bool bInExpansionState);` — Handler for recursively expanding/collapsing items
- L1073 _private prototype_ `struct FSceneOutlinerConfig* GetMutableConfig();` — Get a mutable version of the outliner config for setting values. @returns		The outliner config for this outliner. @note		If FSceneOutlinerInitializationOptions.OutlinerIdentifier is not set, it is not possible to store settings for this outliner.
- L1080 _private prototype_ `const FSceneOutlinerConfig* GetConstConfig() const;` — Get a const version of the outliner config for getting values. @returns		The outliner config for this outliner. @note		If FSceneOutlinerInitializationOptions.OutlinerIdentifier is not set, it is not possible to retrieve settings for this outliner.
- L1082 _private prototype_ `void SaveConfig();`
- L1084 _private member_ `TSharedPtr<FSceneOutlinerSCCHandler> SourceControlHandler;`
- L1087 _public prototype_ `virtual TSharedPtr<FSceneOutlinerTreeItemSCC> GetItemSourceControl(const FSceneOutlinerTreeItemPtr& InItem) override;`
- L1089 _public prototype_ `void AddSourceControlMenuOptions(UToolMenu* Menu);`
- L1091 _public prototype_ `void FilterByType(TSharedPtr<FCustomClassFilterData> CustomClassFilterData);`
- L1092 _public prototype_ `void FilterByTypeCategory(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomClassFilterData>> Classes);`
- L1093 _public prototype_ `bool NeedsRefresh() const;`
- L1101 _public prototype_ `void AddTypeFilterToFilterBar(const TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>& InFilter, TArrayView<const TSharedPtr<FFilterCategory>> InAdditionalCategories = {}) const;` — Add a type filter to the scene outliner's filter bar. Added separately so it can appear in the 'Type Filters' section of the Add Filter menu rather than "Other Filters". The filter will appear under its primary category (set in the Filter) and each additional category in the "Add Filter" menu. Toggling from any category activates the same filter instance, providing a shared state.
- L1104 _public prototype_ `void CreateCustomTextFilter(const FCustomTextFilterData& InFilterData, bool bApplyFilter);`
- L1105 _public prototype_ `void ModifyCustomTextFilter(const FCustomTextFilterData& InFilterData, const TSharedPtr<ICustomTextFilter<SceneOutliner::FilterBarType>>& InFilter);`
- L1106 _public prototype_ `void DeleteCustomTextFilter(const TSharedPtr<ICustomTextFilter<SceneOutliner::FilterBarType>>& InFilter);`

#### struct `FSceneOutlinerMenuHelper`  
`struct FSceneOutlinerMenuHelper`  
_L1109-1113_
- L1111 _public prototype_ `static void AddMenuEntryCreateFolder(FToolMenuSection& InSection, SSceneOutliner& InOutliner);`
- L1112 _public prototype_ `static void AddMenuEntryCleanupFolders(FToolMenuSection& InSection, ULevel* InLevel);`

#### Free symbols / members of external scopes

- L36 _macro_ `#define UE_API SCENEOUTLINER_API`
- L50 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSceneOutliner, Log, All);`
- L56 _namespace_ `namespace SceneOutliner`
- L58 _delegate_ `DECLARE_EVENT_OneParam(SSceneOutliner, FTreeItemPtrEvent, FSceneOutlinerTreeItemPtr);`
- L58 _prototype_ `DECLARE_EVENT_OneParam(SSceneOutliner, FTreeItemPtrEvent, FSceneOutlinerTreeItemPtr);` (scope `SceneOutliner`)
- L60 _delegate_ `DECLARE_EVENT_TwoParams(SSceneOutliner, FOnItemSelectionChanged, FSceneOutlinerTreeItemPtr, ESelectInfo::Type);`
- L60 _prototype_ `DECLARE_EVENT_TwoParams(SSceneOutliner, FOnItemSelectionChanged, FSceneOutlinerTreeItemPtr, ESelectInfo::Type);` (scope `SceneOutliner`)
- L62 _typedef_ `typedef TTextFilter< const ISceneOutlinerTreeItem& > TreeItemTextFilter;` (scope `SceneOutliner`)
- L78 _namespace_ `namespace ENewItemAction` (scope `SceneOutliner`)
- L93 _namespace_ `namespace ExtensionHooks` (scope `SceneOutliner`)
- L95 _variable_ `static FName Hierarchy(TEXT("Hier` (scope `SceneOutliner::ExtensionHooks`)
- L96 _variable_ `static FName Show(TEXT("Show` (scope `SceneOutliner::ExtensionHooks`)

### `Source/Editor/SceneOutliner/Public/SSocketChooser.h` (Public)


#### class `SSocketChooserPopup`  
`class SSocketChooserPopup : public SCompoundWidget`  
_L27-327_
- inherits: `SCompoundWidget`
- L30 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnSocketChosen, FName );`
- L54 _public member_ `TWeakObjectPtr<USceneComponent> SceneComponent;` — The Component that contains the sockets we are choosing from
- L57 _public member_ `TWeakObjectPtr<UStaticMesh> StaticMesh;` — StaticMesh that we want to pick a socket for. Will only be used if no SkeletalMesh
- L60 _public member_ `TArray< TSharedPtr<FSocketInfo> > Sockets;` — Array of shared pointers to socket infos
- L63 _public member_ `TArray< TSharedPtr<FSocketInfo> > FilteredSockets;` — Filtered list of sockets
- L66 _public member_ `FOnSocketChosen OnSocketChosen;` — Delegate to call when OK button is pressed
- L69 _public member_ `TSharedPtr< SListView< TSharedPtr<FSocketInfo> > > SocketListView;` — The combo box
- L72 _public member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilterPtr;` — Compiled filter search terms.
- L75 _public member_ `TSharedPtr<SWidget> SearchBox;` — Search box widget
- L77 _public function_ `SLATE_BEGIN_ARGS( SSocketChooserPopup ) : _SceneComponent(NULL) , _ProvideNoSocketOption(true)`
- L94 _private member_ `TWeakPtr<SWindow> WidgetWindow;` — Cache a weak pointer to my window
- L98 _public function_ `TSharedRef<ITableRow> MakeItemWidget( TSharedPtr<FSocketInfo> SocketInfo, const TSharedRef<STableViewBase>& OwnerTable )` — Called to create a widget for each socket
- L136 _public function_ `void SelectedSocket(TSharedPtr<FSocketInfo> SocketInfo, ESelectInfo::Type SelectType)` — Called when item is selected
- L145 _public function_ `void ChooseSocket(TSharedPtr<FSocketInfo> SocketInfo)` — Select an item
- L157 _public function_ `void Construct( const FArguments& InArgs )`
- L227 _public function_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override` — SWidget interface
- L256 _public function_ `void HandleSearchTextChanged(const FText& InText)`
- L280 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L295 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L300 _public function_ `virtual bool HasKeyboardFocus() const override`
- L306 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L314 _private function_ `TSharedPtr<SWindow> CheckAndGetWindowPtr()` — Check and get the cached window pointer so that we don't need to find it if we already have it

#### struct `SSocketChooserPopup::FSocketInfo`  
`struct FSocketInfo`  
_L33-50_
- desc: Info about one socket
- L35 _public member_ `FComponentSocketDescription Description;`
- L38 _public member_ `FBasicStringFilterExpressionContext FilterContext;` — Cached filter context for faster comparison
- L40 _public function_ `static TSharedRef<FSocketInfo> Make(FComponentSocketDescription Description)`
- L46 _protected function_ `FSocketInfo(FComponentSocketDescription InDescription) : Description(InDescription) , FilterContext(InDescription.Name.ToString())`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSocketChosen, FName );`
- L130 _function_ `.HighlightText_Lambda([this]() { return TextFilterPtr->GetFilterText(); }) ] ];` (scope `SSocketChooserPopup::MakeItemWidget`)

### `Source/Editor/SceneOutliner/Public/SceneOutliner.h` (Public)
_(no declarations extracted)_

### `Source/Editor/SceneOutliner/Public/SceneOutlinerDelegates.h` (Public)


#### class `FSceneOutlinerDelegates`  
`class FSceneOutlinerDelegates`  
_L7-28_
- L11 _public function_ `static FSceneOutlinerDelegates& Get()` — Return a single FSceneOutlinerDelegates object
- L19 _public member_ `FSimpleMulticastDelegate SelectionChanged;` — Broadcasts whenever the current selection changes
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComponentSelectionChanged, class UActorComponent*);` — Broadcasts whenever a Component Selection Changes
- L23 _public member_ `FOnComponentSelectionChanged OnComponentSelectionChanged;`
- L26 _public member_ `FSimpleMulticastDelegate OnComponentsUpdated;` — Broadcasts whenever a Component has been modified

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComponentSelectionChanged, class UActorComponent*);` — Broadcasts whenever a Component Selection Changes

### `Source/Editor/SceneOutliner/Public/SceneOutlinerDragDrop.h` (Public)


#### enum `ESceneOutlinerDropCompatibility`  
`enum class ESceneOutlinerDropCompatibility : uint8`  
_L26-38_
- desc: Enum to describe the compatibility of a drag drop operation
- L28 _public enumerator_ `Compatible`
- L29 _public enumerator_ `Incompatible`
- L30 _public enumerator_ `MultipleSelection_Incompatible`
- L31 _public enumerator_ `CompatibleAttach`
- L32 _public enumerator_ `IncompatibleGeneric`
- L33 _public enumerator_ `CompatibleGeneric`
- L34 _public enumerator_ `CompatibleMultipleAttach`
- L35 _public enumerator_ `IncompatibleMultipleAttach`
- L36 _public enumerator_ `CompatibleDetach`
- L37 _public enumerator_ `CompatibleMultipleDetach`

#### struct `FSceneOutlinerDragDropPayload`  
`struct FSceneOutlinerDragDropPayload`  
_L41-132_
- desc: Consolidated drag/drop with parsing functions for the scene outliner
- L44 _public function_ `FSceneOutlinerDragDropPayload(const FDragDropOperation& InOperation = FDragDropOperation()) : SourceOperation(InOperation)` — Default constructor, resulting in unset contents
- L51 _public function_ `template<typename TreeType> FSceneOutlinerDragDropPayload(const TArray<TreeType>& InDraggedItems, const FDragDropOperation& InOperation = FDragDropOperation()) : SourceOperation(InOperation)` — Populate this payload from an array of tree items
- L62 _public function_ `template <typename TreeType> bool Has() const` — Returns true if the payload has an item of a specified type
- L79 _public function_ `template <typename TreeType> TArray<TreeType*> Get() const` — Return an array of all tree items in the payload which are of a specified type
- L97 _public function_ `template <typename TreeType> void ForEachItem(TFunctionRef<void(TreeType&)> Func) const` — Apply a function to each item in the payload
- L113 _public function_ `template <typename DataType> TArray<DataType> GetData(TFunctionRef<bool(TWeakPtr<ISceneOutlinerTreeItem>, DataType&)> Selector) const` — Use a selector to retrieve an array of a specific data type from the items in the payload
- L128 _public member_ `mutable TArray<TWeakPtr<ISceneOutlinerTreeItem>> DraggedItems;` — List of all dragged items
- L131 _public member_ `const FDragDropOperation& SourceOperation;` — The source FDragDropOperation

#### struct `FSceneOutlinerDragValidationInfo`  
`struct FSceneOutlinerDragValidationInfo`  
_L135-171_
- desc: Struct used for validation of a drag/drop operation in the scene outliner
- L138 _public member_ `ESceneOutlinerDropCompatibility CompatibilityType;` — The tooltip type to display on the operation
- L141 _public member_ `FText ValidationText;` — The tooltip text to display on the operation
- L144 _public function_ `FSceneOutlinerDragValidationInfo(const ESceneOutlinerDropCompatibility InCompatibilityType, const FText InValidationText) : CompatibilityType(InCompatibilityType) , ValidationText(InValidationText)` — Construct this validation information out of a tootip type and some text
- L150 _public function_ `static FSceneOutlinerDragValidationInfo Invalid()` — Return a generic invalid result
- L156 _public function_ `bool IsValid() const` — @return true if this operation is valid, false otheriwse

#### struct `FSceneOutlinerDragDropOp`  
`struct FSceneOutlinerDragDropOp : public FCompositeDragDropOp`  
_L174-206_
- inherits: `FCompositeDragDropOp`
- desc: A drag/drop operation that was started from the scene outliner
- L176 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FSceneOutlinerDragDropOp, FCompositeDragDropOp);`
- L178 _public prototype_ `FSceneOutlinerDragDropOp();`
- L182 _public function_ `void ResetTooltip()`
- L188 _public function_ `void SetTooltip(FText InOverrideText, const FSlateBrush* InOverrideIcon)`
- L194 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L198 _private prototype_ `EVisibility GetOverrideVisibility() const;`
- L199 _private prototype_ `EVisibility GetDefaultVisibility() const;`
- L201 _private member_ `FText OverrideText;`
- L202 _private function_ `FText GetOverrideText() const`
- L204 _private member_ `const FSlateBrush* OverrideIcon;`
- L205 _private function_ `const FSlateBrush* GetOverrideIcon() const`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerFilters.h` (Public)


#### class `FSceneOutlinerFilterInfo`  
`class FSceneOutlinerFilterInfo`  
_L25-61_
- desc: Contains information used to create a filter which will be displayed as user toggleable filter
- L28 _public function_ `FSceneOutlinerFilterInfo(const FText& InFilterTitle, const FText& InFilterTooltip, bool bInActive, const FCreateSceneOutlinerFilter& InFactory = FCreateSceneOutlinerFilter()) : FilterTitle(InFilterTitle) , FilterTooltip(InFilterTooltip) , bActive(bInActive) , Factory(InFactory)`
- L36 _public prototype_ `void InitFilter(TSharedPtr<FSceneOutlinerFilters> InFilters);` — Initialize and apply a new filter
- L39 _public prototype_ `void AddMenu(FMenuBuilder& InMenuBuilder);` — Add menu for this filter
- L41 _public prototype_ `bool IsFilterActive() const;`
- L43 _public prototype_ `DECLARE_EVENT_OneParam(FSceneOutlinerFilterInfo, FOnToggle, bool);`
- L44 _public function_ `FOnToggle& OnToggle()`
- L47 _private prototype_ `void ApplyFilter(bool bActive);`
- L48 _private prototype_ `void ToggleFilterActive();`
- L50 _private member_ `TWeakPtr<FSceneOutlinerFilters> Filters;`
- L52 _private member_ `TSharedPtr<FSceneOutlinerFilter> Filter;`
- L54 _private member_ `FText FilterTitle;`
- L55 _private member_ `FText FilterTooltip;`
- L56 _private member_ `bool bActive;`
- L58 _private member_ `FOnToggle OnToggleEvent;`
- L60 _private member_ `FCreateSceneOutlinerFilter Factory;`

#### class `FSceneOutlinerFilter`  
`class FSceneOutlinerFilter : public IFilter<const ISceneOutlinerTreeItem&>`  
_L64-106_
- inherits: `IFilter<constISceneOutlinerTreeItem&>`
- desc: A filter that can be applied to any type in the tree
- L71 _public prototype_ `DECLARE_DERIVED_EVENT(FSceneOutlinerFilter, IFilter<const ISceneOutlinerTreeItem&>::FChangedEvent, FChangedEvent);` — Event that is fired if this filter changes
- L72 _public function_ `virtual FChangedEvent& OnChanged() override`
- L77 _protected member_ `FChangedEvent ChangedEvent;` — The event that broadcasts whenever a change occurs to the filter
- L80 _protected member_ `const EDefaultBehaviour DefaultBehaviour;` — Default result of the filter when not overridden in derived classes
- L83 _protected function_ `FSceneOutlinerFilter(EDefaultBehaviour InDefaultBehaviour) : DefaultBehaviour(InDefaultBehaviour)` — Constructor to specify the default result of a filter
- L89 _private member_ `mutable bool bTransientFilterResult;` — Transient result from the filter operation. Only valid until the next invocation of the filter.
- L92 _private function_ `virtual bool PassesFilter(const ISceneOutlinerTreeItem& InItem) const override` — Check whether the specified item passes our filter
- L102 _public function_ `virtual bool GetInteractiveState(const ISceneOutlinerTreeItem& InItem) const` — Check if an item should be interactive according to this filter. Default behavior just checks if it passes the filter or not.

#### enum `FSceneOutlinerFilter::EDefaultBehaviour`  
`enum class EDefaultBehaviour : uint8`  
_L68-68_
- desc: Enum to specify how items that are not explicitly handled by this filter should be managed
- L68 _public enumerator_ `enum class EDefaultBehaviour : uint8 { Pass, Fail }; DECLARE_DERIVED_EVENT(FSceneOutlinerFilter, IFilter<const ISceneOutlinerTreeItem&>::FChangedEvent, FChangedEvent); virtual FChangedEvent& OnChanged() override { return ChangedEvent; } protected:` — Enum to specify how items that are not explicitly handled by this filter should be managed
- L68 _public enumerator_ `enum class EDefaultBehaviour : uint8 { Pass, Fail }; DECLARE_DERIVED_EVENT(FSceneOutlinerFilter, IFilter<const ISceneOutlinerTreeItem&>::FChangedEvent, FChangedEvent); virtual FChangedEvent& OnChanged() override { return ChangedEvent; } protected:` — Enum to specify how items that are not explicitly handled by this filter should be managed

#### struct `TSceneOutlinerFilter`  
`template <class T> struct TSceneOutlinerFilter : public FSceneOutlinerFilter`  
_L110-144_
- inherits: `FSceneOutlinerFilter`
- desc: Outliner filter which will be applied on items which match the specified type
- L112 _public function_ `TSceneOutlinerFilter(EDefaultBehaviour InDefaultBehaviour) : FSceneOutlinerFilter(InDefaultBehaviour)`
- L116 _public function_ `virtual bool PassesFilter(const ISceneOutlinerTreeItem& InItem) const override`
- L125 _public function_ `virtual bool PassesFilterImpl(const T& InItem) const`
- L130 _public function_ `virtual bool GetInteractiveState(const ISceneOutlinerTreeItem& InItem) const`
- L140 _public function_ `virtual bool GetInteractiveStateImpl(const T& InItem) const` — If not overriden will just default to testing against PassesFilter

#### struct `TSceneOutlinerPredicateFilter`  
`template <class T> struct TSceneOutlinerPredicateFilter : public TSceneOutlinerFilter<T>`  
_L149-179_
- inherits: `TSceneOutlinerFilter<T>`
- desc: Predicate based filter for the outliner
- L151 _public typedef_ `using TFilterPredicate = typename T::FFilterPredicate;`
- L152 _public typedef_ `using TInteractivePredicate = typename T::FInteractivePredicate;`
- L155 _public member_ `mutable TFilterPredicate FilterPred;` — Predicate used to filter tree items
- L156 _public member_ `mutable TInteractivePredicate InteractivePred;`
- L158 _public function_ `TSceneOutlinerPredicateFilter(TFilterPredicate InFilterPred, FSceneOutlinerFilter::EDefaultBehaviour InDefaultBehaviour, TInteractivePredicate InInteractivePredicate = TInteractivePredicate()) : TSceneOutlinerFilter<T>(InDefaultBehaviour) , FilterPred(InFilterPred) , InteractivePred(InInteractivePredicate)`
- L164 _public function_ `virtual bool PassesFilterImpl(const T& InItem) const override`
- L169 _public function_ `virtual bool GetInteractiveStateImpl(const T& InItem) const override`

#### struct `FSceneOutlinerFilters`  
`struct FSceneOutlinerFilters : public TFilterCollection<const ISceneOutlinerTreeItem&>`  
_L182-210_
- inherits: `TFilterCollection<constISceneOutlinerTreeItem&>`
- desc: Scene outliner filters class. This class wraps a collection of filters and allows items of any type to be tested against the entire set.
- L185 _public function_ `int32 Add(const TSharedPtr<FSceneOutlinerFilter>& Filter)` — Overridden to ensure we only ever have FSceneOutlinerFilters added
- L191 _public function_ `bool GetInteractiveState(const ISceneOutlinerTreeItem& InItem) const` — Test whether this tree item passes all filters, and set its interactive state according to the filter it failed (if applicable)
- L206 _public function_ `template <typename T> void AddFilterPredicate(typename T::FFilterPredicate InFilterPred, FSceneOutlinerFilter::EDefaultBehaviour InDefaultBehaviour = FSceneOutlinerFilter::EDefaultBehaviour::Pass, typename T::FInteractivePredicate InInteractivePred = typename T::FInteractivePredicate())` — Add a filter predicate to this filter collection

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API SCENEOUTLINER_API`
- L43 _delegate_ `DECLARE_EVENT_OneParam(FSceneOutlinerFilterInfo, FOnToggle, bool);`
- L71 _delegate_ `DECLARE_DERIVED_EVENT(FSceneOutlinerFilter, IFilter<const ISceneOutlinerTreeItem&>::FChangedEvent, FChangedEvent);` — Event that is fired if this filter changes

### `Source/Editor/SceneOutliner/Public/SceneOutlinerFwd.h` (Public)


#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TSharedPtr<ISceneOutlinerTreeItem> FSceneOutlinerTreeItemPtr;`
- L23 _typedef_ `typedef TSharedRef<ISceneOutlinerTreeItem> FSceneOutlinerTreeItemRef;`
- L25 _typedef_ `typedef TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr> FSceneOutlinerTreeItemMap;`
- L38 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSceneOutlinerItemPicked, TSharedRef<ISceneOutlinerTreeItem> );`
- L38 _prototype_ `DECLARE_DELEGATE_OneParam( FOnSceneOutlinerItemPicked, TSharedRef<ISceneOutlinerTreeItem> );`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam( FCustomSceneOutlinerDeleteDelegate, const TArray<TWeakPtr<ISceneOutlinerTreeItem>>& ) DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<ISceneOutlinerColumn>, FCreateSceneOutlinerColumn, ISceneOutliner& );`
- L40 _prototype_ `DECLARE_DELEGATE_OneParam( FCustomSceneOutlinerDeleteDelegate, const TArray<TWeakPtr<ISceneOutlinerTreeItem>>& ) DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<ISceneOutlinerColumn>, FCreateSceneOutlinerColumn, ISceneOutliner& );`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<ISceneOutlinerColumn>, FCreateSceneOutlinerColumn, ISceneOutliner& );` — A delegate used to factory a new column type
- L46 _delegate_ `DECLARE_DELEGATE_RetVal( TSharedRef<FSceneOutlinerFilter>, FCreateSceneOutlinerFilter );` — A delegate used to factory a new filter type
- L46 _prototype_ `DECLARE_DELEGATE_RetVal( TSharedRef<FSceneOutlinerFilter>, FCreateSceneOutlinerFilter );` — A delegate used to factory a new filter type
- L49 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<ISceneOutliner>, FSceneOutlinerFactory, FSceneOutlinerInitializationOptions);` — A delegate used to factory a new scene outliner using the given init options
- L49 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<ISceneOutliner>, FSceneOutlinerFactory, FSceneOutlinerInitializationOptions);` — A delegate used to factory a new scene outliner using the given init options

### `Source/Editor/SceneOutliner/Public/SceneOutlinerGutter.h` (Public)


#### class `FSceneOutlinerGutter`  
`class FSceneOutlinerGutter : public ISceneOutlinerColumn`  
_L22-63_
- inherits: `ISceneOutlinerColumn`
- desc: A gutter for the SceneOutliner which handles setting and visualizing item visibility
- L27 _public prototype_ `FSceneOutlinerGutter(ISceneOutliner& Outliner);` — Constructor
- L29 _public prototype_ `virtual ~FSceneOutlinerGutter() = default;`
- L31 _public function_ `static FName GetID()`
- L33 _public function_ `static FText GetDisplayName()`
- L37 _public prototype_ `virtual FName GetColumnID() override;` — ISceneOutlinerColumn Implementation
- L39 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L41 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L43 _public prototype_ `virtual void Tick(double InCurrentTime, float InDeltaTime) override;`
- L45 _public function_ `virtual bool SupportsSorting() const override`
- L47 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L51 _public function_ `FORCEINLINE bool IsItemVisible(const ISceneOutlinerTreeItem& Item)` — Check whether the specified item is visible
- L59 _protected member_ `TWeakPtr<ISceneOutliner> WeakOutliner;` — Weak pointer back to the scene outliner - required for setting visibility on current selection.
- L62 _protected member_ `FSceneOutlinerVisibilityCache VisibilityCache;` — Get and cache visibility for items. Cached per-frame to avoid expensive recursion.

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SVisibilityWidget>`  
_L66-69_
- L68 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SVisibilityWidget`  
`class SVisibilityWidget : public SImage`  
_L72-145_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L75 _public function_ `SLATE_BEGIN_ARGS(SVisibilityWidget)`
- L76 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FSceneOutlinerGutter> InWeakColumn, TWeakPtr<ISceneOutliner> InWeakOutliner, TWeakPtr<ISceneOutlinerTreeItem> InWeakTreeItem, const STableRow<FSceneOutlinerTreeItemPtr>* InRow);`
- L84 _protected function_ `virtual bool IsEnabled() const` — Returns whether the widget is enabled or not
- L87 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;` — Get the brush for this widget
- L90 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Start a new drag/drop operation for this widget
- L93 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — If a visibility drag drop operation has entered this widget, set its item to the new visibility state
- L95 _protected prototype_ `FReply HandleClick();`
- L97 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L100 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when the mouse button is pressed down on this widget
- L103 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Process a mouse up message
- L106 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;` — Called when this widget had captured the mouse, but that capture has been revoked for some reason.
- L109 _protected prototype_ `virtual void OnSetItemVisibility(ISceneOutlinerTreeItem& Item, const bool bNewVisibility);` — Called when visibility change happens on an Item.
- L112 _protected function_ `virtual bool ShouldPropagateVisibilityChangeOnChildren() const` — Whether visibility change should propagate down to children.
- L114 _protected prototype_ `virtual FSlateColor GetForegroundColor() const;`
- L117 _protected prototype_ `static bool IsVisible(const FSceneOutlinerTreeItemPtr& Item, const TSharedPtr<FSceneOutlinerGutter>& Column);` — Check if the specified item is visible
- L120 _protected prototype_ `bool IsVisible() const;` — Check if our wrapped tree item is visible
- L123 _protected prototype_ `void SetIsVisible(const bool bVisible);` — Set the item this widget is responsible for to be hidden or shown
- L126 _protected member_ `TWeakPtr<ISceneOutlinerTreeItem> WeakTreeItem;` — The tree item we relate to
- L129 _protected member_ `TWeakPtr<ISceneOutliner> WeakOutliner;` — Reference back to the outliner so we can set visibility of a whole selection
- L132 _protected member_ `TWeakPtr<FSceneOutlinerGutter> WeakColumn;` — Weak pointer back to the column
- L135 _protected member_ `const STableRow<FSceneOutlinerTreeItemPtr>* Row;` — Weak pointer back to the row
- L138 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;` — Scoped undo transaction
- L141 _protected member_ `const FSlateBrush* VisibleHoveredBrush;` — Visibility brushes for the various states
- L142 _protected member_ `const FSlateBrush* VisibleNotHoveredBrush;`
- L143 _protected member_ `const FSlateBrush* NotVisibleHoveredBrush;`
- L144 _protected member_ `const FSlateBrush* NotVisibleNotHoveredBrush;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerHelpers.h` (Public)


#### class `SceneOutliner::FSceneOutlinerHelpers`  
`class FSceneOutlinerHelpers`  
_L13-37_
- desc: Class to hold common functionality needed by the Outliner and helpful to modules creating Outliner instances
- L17 _public prototype_ `static FString GetExternalPackageName(const ISceneOutlinerTreeItem& TreeItem);` — `UE_DEPRECATED(5.5, "FSceneOutlinerHelpers::GetExternalPackageName has been deprecated implement/use ISceneOutlinerTreeItem::GetPackageName instead")`
- L20 _public prototype_ `static UPackage* GetExternalPackage(const ISceneOutlinerTreeItem& TreeItem);` — `UE_DEPRECATED(5.5, "FSceneOutlinerHelpers::GetExternalPackage has been deprecated implement/use ISceneOutlinerTreeItem::GetPackageName instead")`
- L22 _public prototype_ `static void ChooseRepresentingWorld(TWeakObjectPtr<UWorld>& OutWorld, const TWeakObjectPtr<UWorld>& InSpecifiedWorldToDisplay = nullptr, const TWeakObjectPtr<UWorld>& InUserChosenWorld = nullptr);`
- L26 _public prototype_ `static TSharedPtr<SWidget> GetClassHyperlink(UObject* InObject);`
- L28 _public prototype_ `static void PopulateExtraSearchStrings(const ISceneOutlinerTreeItem& TreeItem, TArray< FString >& OutSearchStrings);`
- L30 _public prototype_ `static bool ValidateFolderName(const FFolder& InFolder, UWorld* World, const FText& InLabel, FText& OutErrorMessage);`
- L32 _public prototype_ `static void RenameFolder(const FFolder& InFolder, const FText& NewFolderName, UWorld* World);`
- L34 _public prototype_ `static bool IsFolderCurrent(const FFolder& InFolder, UWorld* World);`
- L36 _public prototype_ `static TWeakObjectPtr<AActor> GetActorFromOutlinerTreeItem(const ISceneOutlinerTreeItem& TreeItem, const TSharedPtr<ISceneOutliner>& Outliner);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENEOUTLINER_API`
- L10 _namespace_ `namespace SceneOutliner`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerMenuContext.h` (Public)


#### class `USceneOutlinerMenuContext`  
`class USceneOutlinerMenuContext : public UObject`  
_L13-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L18 _public function_ `USceneOutlinerMenuContext(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L30 _public member_ `TWeakPtr<SSceneOutliner> SceneOutliner;`
- L32 _public member_ `bool bShowParentTree;`
- L33 _public member_ `bool bRepresentingGameWorld;`
- L34 _public member_ `bool bRepresentingPartitionedWorld;`
- L35 _public member_ `int32 NumSelectedItems;`
- L36 _public member_ `int32 NumSelectedFolders;`
- L37 _public member_ `int32 NumWorldsSelected;`
- L38 _public member_ `int32 NumPinnedItems;`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerModule.h` (Public)


#### class `FSceneOutlinerModule`  
`class FSceneOutlinerModule : public IModuleInterface`  
_L25-169_
- inherits: `IModuleInterface`
- desc: Implements the Scene Outliner module.
- L30 _public prototype_ `FSceneOutlinerModule();`
- L40 _public prototype_ `virtual TSharedRef<ISceneOutliner> CreateSceneOutliner( const FSceneOutlinerInitializationOptions& InitOptions) const;` — Creates a scene outliner widget @param	InitOptions						Programmer-driven configuration for this widget instance @param	OutlinerModeFactory				Factory delegate used to create the outliner mode @return	New scene outliner widget
- L46 _public prototype_ `virtual TSharedRef<ISceneOutliner> CreateActorPicker( const FSceneOutlinerInitializationOptions& InInitOptions, const FOnActorPicked& OnActorPickedDelegate, TWeakObjectPtr<UWorld> SpecifiedWorld = nullptr, bool bHideLevelInstanceHierarchy = true) const;` — Creates an actor picker widget. Calls the OnActorPickedDelegate when an item is selected.
- L52 _public prototype_ `virtual TSharedRef<ISceneOutliner> CreateComponentPicker( const FSceneOutlinerInitializationOptions& InInitOptions, const FOnComponentPicked& OnComponentPickedDelegate, TWeakObjectPtr<UWorld> SpecifiedWorld = nullptr) const;` — Creates a component picker widget. Calls the OnComponentPickedDelegate when an item is selected.
- L58 _public prototype_ `virtual TSharedRef<ISceneOutliner> CreateActorBrowser( const FSceneOutlinerInitializationOptions& InInitOptions, TWeakObjectPtr<UWorld> SpecifiedWorld = nullptr) const;` — Creates an actor browser widget (also known as a World Outliner).
- L64 _public prototype_ `UE_INTERNAL virtual void RegisterCustomSceneOutlinerFactory(FName ID, FSceneOutlinerFactory InOutlinerFactory) final;` — Register a factory to create a custom Scene Outliner
- L67 _public prototype_ `UE_INTERNAL virtual void UnregisterCustomSceneOutlinerFactory(FName ID) final;` — Unregister a factory to create a custom Scene Outliner
- L70 _public prototype_ `UE_INTERNAL virtual TSharedPtr<ISceneOutliner> CreateCustomRegisteredOutliner(FName ID, FSceneOutlinerInitializationOptions InInitOptions) final;` — Try to create a custom scene outliner using a registered factory (nullptr if ID was not registered)
- L73 _public prototype_ `UE_INTERNAL virtual bool IsCustomSceneOutlinerFactoryRegistered(FName ID) final;` — Check if a custom scene outliner factory is registered with the given ID
- L78 _public prototype_ `virtual void CreateActorBrowserColumns(FSceneOutlinerInitializationOptions& InInitOptions, UWorld* InWorld = nullptr) const;` — Add the columns present in the level editor's Outliner (Actor Browser) to the given init options @param InWorld The world the Outliner initialized by InInitOptions will look it, defaults to the level editor's world if nullptr
- L81 _public function_ `TSharedRef<FNamePermissionList>& GetColumnPermissionList()` — Column permission list
- L84 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnColumnPermissionListChanged);` — Delegate that broadcasts when column permission list changes.
- L85 _public function_ `FOnColumnPermissionListChanged& OnColumnPermissionListChanged()`
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateActorBrowserColumns, FSceneOutlinerInitializationOptions&, UWorld*);` — Delegate that broadcasts when creating actor browser columns.
- L89 _public function_ `FOnCreateActorBrowserColumns& OnCreateActorBrowserColumns()`
- L94 _public function_ `template< typename T > void RegisterColumnType()` — Register a new type of column available to all scene outliners
- L109 _public function_ `template< typename T > void RegisterDefaultColumnType(FSceneOutlinerColumnInfo InColumnInfo)` — Register a new type of default column available to all scene outliners
- L125 _public function_ `template< typename T > void UnRegisterColumnType()` — Unregister a previously registered column type
- L132 _public function_ `TSharedPtr< ISceneOutlinerColumn > FactoryColumn( FName ID, ISceneOutliner& Outliner ) const` — Factory a new column from the specified name. Returns null if no type has been registered under that name.
- L142 _public prototype_ `void CreateActorInfoColumns(FSceneOutlinerInitializationOptions& InInitOptions, UWorld* WorldPtr = nullptr) const;`
- L145 _public member_ `TMap< FName, FSceneOutlinerColumnInfo> DefaultColumnMap;` — Map of column type name -> default column info
- L150 _private member_ `TMap< FName, FCreateSceneOutlinerColumn > ColumnMap;` — Map of column type name -> factory delegate
- L153 _private member_ `TSharedRef<FNamePermissionList> ColumnPermissionList;` — Column permission list used to filter scene ouliner columns.
- L156 _private member_ `FOnColumnPermissionListChanged ColumnPermissionListChanged;` — Delegate that broadcasts when column permission list changes.
- L159 _private member_ `FOnCreateActorBrowserColumns CreateActorBrowserColumnsDelegate;` — Delegate that broadcasts when creating actor browser columns.
- L161 _private member_ `TMap< FName, FSceneOutlinerFactory> CustomOutlinerFactories;`
- L167 _public prototype_ `virtual void StartupModule() override;`
- L168 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnActorPicked, AActor*);` — Delegate used with the Scene Outliner in 'actor picking' mode.  You'll bind a delegate when the outliner widget is created, which will be fired off when an actor is selected in the list
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnActorPicked, AActor*);` — Delegate used with the Scene Outliner in 'actor picking' mode.  You'll bind a delegate when the outliner widget is created, which will be fired off when an actor is selected in the list
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnComponentPicked, UActorComponent*);` — Delegate used with the Scene Outliner in 'component picking' mode.  You'll bind a delegate when the outliner widget is created, which will be fired off when an actor is selected in the list
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnComponentPicked, UActorComponent*);` — Delegate used with the Scene Outliner in 'component picking' mode.  You'll bind a delegate when the outliner widget is created, which will be fired off when an actor is selected in the list
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnColumnPermissionListChanged);` — Delegate that broadcasts when column permission list changes.
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateActorBrowserColumns, FSceneOutlinerInitializationOptions&, UWorld*);` — Delegate that broadcasts when creating actor browser columns.
- L99 _function_ `auto CreateColumn = []( ISceneOutliner& Outliner )` (scope `FSceneOutlinerModule::RegisterColumnType`)
- L114 _function_ `auto CreateColumn = []( ISceneOutliner& Outliner )` (scope `FSceneOutlinerModule::RegisterDefaultColumnType`)

### `Source/Editor/SceneOutliner/Public/SceneOutlinerPublicTypes.h` (Public)


#### struct `FSceneOutlinerBuiltInColumnTypes`  
`struct FSceneOutlinerBuiltInColumnTypes`  
_L33-63_
- desc: Container for built in column types. Function-static so they are available without linking

#### enum `ESceneOutlinerColumnVisibility`  
`enum class ESceneOutlinerColumnVisibility : uint8`  
_L66-73_
- desc: Visibility enum for scene outliner columns
- L69 _public enumerator_ `Visible` — This column defaults to being visible on the scene outliner
- L72 _public enumerator_ `Invisible` — This column defaults to being invisible, yet still available on the scene outliner

#### struct `FSceneOutlinerColumnInfo`  
`struct FSceneOutlinerColumnInfo`  
_L76-108_
- desc: Column information for the scene outliner
- L78 _public function_ `FSceneOutlinerColumnInfo( ESceneOutlinerColumnVisibility InVisibility, uint8 InPriorityIndex, const FCreateSceneOutlinerColumn& InFactory = FCreateSceneOutlinerColumn() , bool inCanBeHidden = true, TOptional<float> InFillSize = TOptional<float>(), TAttribute<FText> InColumnLabel = TAttribute<FText>() , EHeaderComboVisibility InHeaderComboVisibility = EHeaderComboVisibility::OnHover, FOnGetContent InOnGetMenuContent = FOnGetContent()) : Visibility(InVisibility), PriorityIndex(InPriorityIndex), bCanBeHidden(inCanBeHidden) , Factory(InFactory), FillSize(InFillSize), ColumnLabel(InColumnLabel) , HeaderComboVisibility(InHeaderComboVisibility), OnGetHeaderContextMenuContent(InOnGetMenuContent)`
- L88 _public function_ `FSceneOutlinerColumnInfo()`
- L90 _public function_ `FSceneOutlinerColumnInfo(const FSceneOutlinerColumnInfo& InColumnInfo) : Visibility(InColumnInfo.Visibility), PriorityIndex(InColumnInfo.PriorityIndex) , bCanBeHidden(InColumnInfo.bCanBeHidden), Factory(InColumnInfo.Factory) , FillSize(InColumnInfo.FillSize), ColumnLabel(InColumnInfo.ColumnLabel) , HeaderComboVisibility(InColumnInfo.HeaderComboVisibility) , OnGetHeaderContextMenuContent(InColumnInfo.OnGetHeaderContextMenuContent)`
- L98 _public member_ `ESceneOutlinerColumnVisibility Visibility;`
- L99 _public member_ `uint8 PriorityIndex;`
- L100 _public member_ `bool bCanBeHidden;`
- L101 _public member_ `FCreateSceneOutlinerColumn Factory;`
- L102 _public member_ `TOptional< float > FillSize;`
- L103 _public member_ `TAttribute<FText> ColumnLabel;` — Override for the column name used instead of ID if specified (use this if you want the column name to be localizable)
- L106 _public member_ `EHeaderComboVisibility HeaderComboVisibility;` — Hides the button on each header cell which normally shows up when OnGetHeaderContextMenuContent is bound
- L107 _public member_ `FOnGetContent OnGetHeaderContextMenuContent;`

#### struct `FSharedSceneOutlinerData`  
`struct FSharedSceneOutlinerData`  
_L111-142_
- desc: Settings for the scene outliner which can be quieried publicly
- L114 _public member_ `FCustomSceneOutlinerDeleteDelegate CustomDelete;` — Invoked whenever the user attempts to delete an actor from within a Scene Outliner in the actor browsing mode
- L117 _public member_ `FSceneOutlinerModifyContextMenu ModifyContextMenu;` — Modify context menu before display
- L120 _public member_ `TMap<FName, FSceneOutlinerColumnInfo> ColumnMap;` — Map of column types available to the scene outliner, along with default ordering
- L123 _public member_ `bool bShowParentTree : 1;` — Whether the Scene Outliner should display parent actors in a Tree
- L126 _public member_ `bool bOnlyShowFolders : 1;` — True to only show folders in this outliner
- L129 _public member_ `bool bShowTransient : 1;` — Show transient objects
- L134 _public function_ `FSharedSceneOutlinerData() : bShowParentTree( true ) , bOnlyShowFolders( false ) , bShowTransient( false )` — Constructor
- L141 _public prototype_ `void UseDefaultColumns();` — Set up a default array of columns for this outliner

#### struct `FSceneOutlinerFilterBarOptions`  
`struct FSceneOutlinerFilterBarOptions`  
_L145-167_
- desc: Settings for the Filter Bar attached to the Scene Outliner. Can be specified through FSceneOutlinerInitializationOptions
- L148 _public member_ `bool bHasFilterBar = false;` — If true, the Scene Outliner has a filter bar attached to it
- L154 _public member_ `TArray<TSharedRef<FFilterBase<SceneOutliner::FilterBarType>>> CustomFilters;` — These are the custom filters that the Scene Outliner will have. All active filters will be AND'd together to test against. @see FGenericFilter on how to create generic filters
- L160 _public member_ `TArray<TSharedRef<FCustomClassFilterData>> CustomClassFilters;` — These are the asset type filters that the Scene Outliner will have. All active filters will be OR'd together to test against. Can be created using IAssetTypeActions or UClass (@see constructor)
- L163 _public member_ `bool bUseSharedSettings = false;` — If true, share this Outliner filter bar's custom text filters with the level editor outliners
- L166 _public member_ `TSharedPtr<FFilterCategory> CategoryToExpand;` — The category to expand in the filter menu (There must be at least one filter attached to the category)

#### struct `FSceneOutlinerInitializationOptions`  
`struct FSceneOutlinerInitializationOptions : FSharedSceneOutlinerData`  
_L174-224_
- inherits: `FSharedSceneOutlinerData`
- desc: Settings for the Scene Outliner set by the programmer before spawning an instance of the widget.  This is used to modify the outliner's behavior in various ways, such as filtering in or out specific classes of actors.
- L177 _public member_ `bool bShowHeaderRow : 1;` — True if we should draw the header row above the tree view
- L184 _public member_ `bool bCanSelectGeneratedColumns : 1;` — Can select the columns generated by right clicking on the header menu. FColumn with ShouldGenerateWidget set can not be selected. FColumn with MenuContent will still be displayed.
- L187 _public member_ `bool bShowSearchBox : 1;` — Whether the Scene Outliner should expose its searchbox
- L190 _public member_ `bool bFocusSearchBoxWhenOpened : 1;` — If true, the search box will gain focus when the scene outliner is created
- L193 _public member_ `bool bShowCreateNewFolder : 1;` — If true, the Scene Outliner will expose a Create New Folder button
- L196 _public member_ `TSharedPtr<FSceneOutlinerFilters> Filters;` — Optional collection of filters to use when filtering in the Scene Outliner
- L198 _public member_ `FCreateSceneOutlinerMode ModeFactory;`
- L201 _public member_ `FName OutlinerIdentifier;` — Identifier for this outliner; NAME_None if this view is anonymous (Needs to be specified to save visibility of columns in EditorConfig)
- L204 _public member_ `FSceneOutlinerFilterBarOptions FilterBarOptions;` — Init options related to the filter bar
- L207 _public member_ `FName PrimaryColumnName;` — The primary column for this outliner, used to determine initial sorting and where the hierarchy arrows appear
- L210 _public member_ `TSharedPtr<FUICommandList> CommandList;` — Additional commands to append to the scene outliner command list
- L213 _public function_ `FSceneOutlinerInitializationOptions() : bShowHeaderRow( true ) , bCanSelectGeneratedColumns( true ) , bShowSearchBox( true ) , bFocusSearchBoxWhenOpened( false ) , bShowCreateNewFolder( true ) , Filters( new FSceneOutlinerFilters ) , ModeFactory() , OutlinerIdentifier(NAME_None) , PrimaryColumnName(FSceneOutlinerBuiltInColumnTypes::Label())` — Constructor

#### struct `FSceneOutlinerDefaultTreeItemMetrics`  
`struct FSceneOutlinerDefaultTreeItemMetrics`  
_L227-232_
- desc: Default metrics for outliner tree items
- L229 _public function_ `static int32 RowHeight()`
- L230 _public function_ `static int32 IconSize()`
- L231 _public function_ `static FMargin IconPadding()`

#### struct `FSceneOutlinerVisibilityCache`  
`struct FSceneOutlinerVisibilityCache`  
_L235-244_
- desc: A struct which gets, and caches the visibility of a tree item
- L238 _public member_ `mutable TMap<const ISceneOutlinerTreeItem*, bool> VisibilityInfo;` — Map of tree item to visibility
- L241 _public prototype_ `bool RecurseChildren(const ISceneOutlinerTreeItem& Item) const;` — Get an item's visibility based on its children
- L243 _public prototype_ `bool GetVisibility(const ISceneOutlinerTreeItem& Item) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENEOUTLINER_API`
- L12 _macro_ `#define LOCTEXT_NAMESPACE "SceneOutlinerPublicTypes"`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FSceneOutlinerModifyContextMenu, FName& , FToolMenuContext& );`
- L21 _prototype_ `DECLARE_DELEGATE_TwoParams(FSceneOutlinerModifyContextMenu, FName& , FToolMenuContext& );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(ISceneOutlinerMode*, FCreateSceneOutlinerMode, SSceneOutliner*);` — A delegate used as a factory to defer mode creation in the outliner
- L24 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(ISceneOutlinerMode*, FCreateSceneOutlinerMode, SSceneOutliner*);` — A delegate used as a factory to defer mode creation in the outliner
- L26 _namespace_ `namespace SceneOutliner`
- L29 _typedef_ `typedef const ISceneOutlinerTreeItem& FilterBarType;` (scope `SceneOutliner`) — The type of item that the Outliner's Filter Bar operates on
- L35 _macro_ `#define DEFINE_SCENEOUTLINER_BUILTIN_COLUMN_TYPE(ColumnID, ColumnName, ColumnKey, ColumnLocalizedTextLiteral) \`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerSCCHandler.h` (Public)


#### class `FSceneOutlinerSCCHandler`  
`class FSceneOutlinerSCCHandler : public TSharedFromThis<class FSceneOutlinerSCCHandler>`  
_L11-61_
- inherits: `TSharedFromThis<classFSceneOutlinerSCCHandler>`
- L14 _public prototype_ `FSceneOutlinerSCCHandler();`
- L15 _public prototype_ `~FSceneOutlinerSCCHandler();`
- L17 _public prototype_ `bool AddSourceControlMenuOptions(UToolMenu* Menu, TArray<FSceneOutlinerTreeItemPtr> InSelectedItems);`
- L19 _public prototype_ `TSharedPtr<FSceneOutlinerTreeItemSCC> GetItemSourceControl(const FSceneOutlinerTreeItemPtr& InItem) const;`
- L23 _private prototype_ `bool AllowExecuteSourceControlRevert() const;`
- L24 _private prototype_ `bool AllowExecuteSourceControlRevertUnsaved() const;`
- L25 _private prototype_ `bool CanExecuteSourceControlActions() const;`
- L26 _private prototype_ `void CacheCanExecuteVars();`
- L27 _private prototype_ `bool CanExecuteSCC() const;`
- L28 _private prototype_ `bool CanExecuteSCCCheckOut() const;`
- L29 _private prototype_ `bool CanExecuteSCCCheckIn() const;`
- L30 _private prototype_ `bool CanExecuteSCCRevert() const;`
- L31 _private prototype_ `bool CanExecuteSCCHistory() const;`
- L32 _private prototype_ `bool CanExecuteSCCRefresh() const;`
- L33 _private prototype_ `bool CanExecuteSCCShowInChangelist() const;`
- L34 _private prototype_ `void FillSourceControlSubMenu(UToolMenu* Menu);`
- L35 _private prototype_ `void GetSelectedPackageNames(TArray<FString>& OutPackageNames) const;`
- L36 _private prototype_ `void GetSelectedPackages(TArray<UPackage*>& OutPackages) const;`
- L37 _private prototype_ `void ExecuteSCCRefresh();`
- L38 _private prototype_ `void ExecuteSCCCheckOut();`
- L39 _private prototype_ `void ExecuteSCCCheckIn();`
- L40 _private prototype_ `void ExecuteSCCRevert();`
- L41 _private prototype_ `void ExecuteSCCHistory();`
- L42 _private prototype_ `void ExecuteSCCShowInChangelist();`
- L44 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType MapChangedType);`
- L46 _private member_ `TArray<FSceneOutlinerTreeItemPtr> SelectedItems;`
- L52 _private member_ `bool bCanExecuteSCC = false;` — todo: Sync and Revert functionality is not enabled currently due to needing to unload/reload the actor and having to deal with any potential dependencies. You can read more about this decision here: https://github.com/EpicGames/UnrealEngine/pull/9310#issuecomment-1171505628
- L53 _private member_ `bool bCanExecuteSCCCheckOut = false;`
- L54 _private member_ `bool bCanExecuteSCCCheckIn = false;`
- L55 _private member_ `bool bCanExecuteSCCHistory = false;`
- L56 _private member_ `bool bCanExecuteSCCRevert = false;`
- L57 _private member_ `bool bUsesSnapshots = false;`
- L58 _private member_ `bool bUsesChangelists = false;`
- L60 _private member_ `mutable TMap<FSceneOutlinerTreeItemPtr, TSharedPtr<FSceneOutlinerTreeItemSCC>> ItemSourceControls;`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerSourceControlColumn.h` (Public)


#### class `FSceneOutlinerSourceControlColumn`  
`class FSceneOutlinerSourceControlColumn : public ISceneOutlinerColumn`  
_L17-46_
- inherits: `ISceneOutlinerColumn`
- desc: A column for the SceneOutliner that displays the SCC Information
- L21 _public function_ `FSceneOutlinerSourceControlColumn(ISceneOutliner& SceneOutliner) : WeakSceneOutliner(StaticCastSharedRef<ISceneOutliner>(SceneOutliner.AsShared()))`
- L23 _public prototype_ `virtual ~FSceneOutlinerSourceControlColumn() = default;`
- L25 _public function_ `static FName GetID()`
- L27 _public function_ `static FText GetDisplayName()`
- L32 _public prototype_ `virtual FName GetColumnID() override;`
- L34 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L36 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L38 _public function_ `virtual bool SupportsSorting() const override`
- L43 _private prototype_ `const FSlateBrush* GetHeaderIconBadge() const;`
- L45 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENEOUTLINER_API`

### `Source/Editor/SceneOutliner/Public/SceneOutlinerStandaloneTypes.h` (Public)


#### struct `FFolderKey`  
`struct FFolderKey`  
_L14-28_
- L16 _public function_ `FFolderKey(const FName& InPath, const FFolder::FRootObject& InRootObject) : Path(InPath) , RootObjectKey(InRootObject)`
- L21 _public function_ `FORCEINLINE bool operator == (const FFolderKey& InOther) const`
- L26 _public member_ `FName Path;`
- L27 _public member_ `FFolder::FRootObject RootObjectKey;`

#### struct `FSceneOutlinerTreeItemID`  
`struct FSceneOutlinerTreeItemID`  
_L36-182_
- desc: Variant type that defines an identifier for a tree item. Assumes 'trivial relocatability' as with many unreal containers.
- L39 _public typedef_ `using FUniqueID = uint64;`
- L44 _public function_ `FSceneOutlinerTreeItemID() : Type(EType::Null), CachedHash(0)` — Default constructed null item ID
- L47 _public function_ `FSceneOutlinerTreeItemID(const UObject* InObject) : Type(EType::Object)` — ID representing a UObject
- L53 _public function_ `FSceneOutlinerTreeItemID(const FObjectKey& InKey) : Type(EType::Object)`
- L60 _public function_ `FSceneOutlinerTreeItemID(const FFolderKey& InKey) : Type(EType::Folder)` — ID representing a folder
- L66 _public function_ `FSceneOutlinerTreeItemID(const FFolder& InFolder) : FSceneOutlinerTreeItemID(FFolderKey(InFolder.GetPath(), InFolder.GetRootObject()))`
- L71 _public function_ `FSceneOutlinerTreeItemID(const FUniqueID& CustomID) : Type(EType::UniqueID)` — ID representing a generic tree item
- L77 _public function_ `explicit FSceneOutlinerTreeItemID(const FGuid& InGuid) : Type(EType::Guid)`
- L84 _public function_ `FSceneOutlinerTreeItemID(const FSceneOutlinerTreeItemID& Other)` — Copy construction / assignment
- L88 _public function_ `FSceneOutlinerTreeItemID& operator=(const FSceneOutlinerTreeItemID& Other)`
- L105 _public function_ `FSceneOutlinerTreeItemID(FSceneOutlinerTreeItemID&& Other)` — Move construction / assignment
- L109 _public function_ `FSceneOutlinerTreeItemID& operator=(FSceneOutlinerTreeItemID&& Other)`
- L115 _public function_ `~FSceneOutlinerTreeItemID()`
- L127 _public function_ `bool operator==(const FSceneOutlinerTreeItemID& Other) const`
- L131 _public function_ `bool operator!=(const FSceneOutlinerTreeItemID& Other) const`
- L136 _public function_ `uint32 CalculateTypeHash() const`
- L158 _private function_ `FObjectKey& GetAsObjectKey() const`
- L159 _private function_ `FFolderKey& GetAsFolderRef() const`
- L160 _private function_ `FGuid& GetAsGuid() const`
- L161 _private function_ `FUniqueID& GetAsHash() const`
- L164 _private function_ `bool Compare(const FSceneOutlinerTreeItemID& Other) const` — Compares the specified ID with this one - assumes matching types
- L177 _private member_ `EType Type;`
- L179 _private member_ `uint32 CachedHash;`
- L180 _private member_ `static const uint32 MaxSize = TMaxSizeof<FObjectKey, FFolderKey, FGuid, FUniqueID>::Value;`
- L181 _private member_ `alignas(8) mutable uint8 Data[MaxSize];`

#### enum `FSceneOutlinerTreeItemID::EType`  
`enum class EType : uint8`  
_L41-41_
- L41 _public enumerator_ `enum class EType : uint8 { Object, Folder, UniqueID, Guid, Null }; FSceneOutlinerTreeItemID() : Type(EType::Null)`
- L41 _public enumerator_ `enum class EType : uint8 { Object, Folder, UniqueID, Guid, Null }; FSceneOutlinerTreeItemID() : Type(EType::Null)`
- L41 _public enumerator_ `enum class EType : uint8 { Object, Folder, UniqueID, Guid, Null }; FSceneOutlinerTreeItemID() : Type(EType::Null)`
- L41 _public enumerator_ `enum class EType : uint8 { Object, Folder, UniqueID, Guid, Null }; FSceneOutlinerTreeItemID() : Type(EType::Null)`
- L41 _public enumerator_ `enum class EType : uint8 { Object, Folder, UniqueID, Guid, Null }; FSceneOutlinerTreeItemID() : Type(EType::Null)`

#### struct `FSceneOutlinerTreeItemType`  
`struct FSceneOutlinerTreeItemType`  
_L184-208_
- L187 _public function_ `explicit FSceneOutlinerTreeItemType(const FSceneOutlinerTreeItemType* Parent = nullptr) : ID(++NextUniqueID), ParentType(Parent)`
- L189 _public function_ `bool operator==(const FSceneOutlinerTreeItemType& Other) const`
- L194 _public function_ `bool IsA(const FSceneOutlinerTreeItemType& Other) const`
- L205 _private member_ `static uint32 NextUniqueID;`
- L206 _private member_ `uint32 ID;`
- L207 _private member_ `const FSceneOutlinerTreeItemType* ParentType;`

#### struct `FSceneOutlinerCommonLabelData`  
`struct FSceneOutlinerCommonLabelData`  
_L210-220_
- L212 _public member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`
- L213 _public member_ `static const FLinearColor DarkColor;`
- L215 _public prototype_ `static TOptional<FLinearColor> GetForegroundColor(TWeakPtr<ISceneOutliner> WeakSceneOutliner, const ISceneOutlinerTreeItem& TreeItem);`
- L217 _public prototype_ `TOptional<FLinearColor> GetForegroundColor(const ISceneOutlinerTreeItem& TreeItem) const;`
- L219 _public prototype_ `bool CanExecuteRenameRequest(const ISceneOutlinerTreeItem& Item) const;`

#### struct `FSceneOutlinerHierarchyChangedData`  
`struct FSceneOutlinerHierarchyChangedData`  
_L228-247_
- desc: Contains hierarchy change data. When an item is added, it will contain a pointer to the new item itself. When an item is removed or moved, it will contain the unique ItemID to that item. In the case that a folder is being moved, it will also contain the new path to that folder.
- L237 _public member_ `} Type;`
- L240 _public member_ `TArray<FSceneOutlinerTreeItemPtr> Items;` — This event may pass one of two kinds of data, depending on the type of event
- L242 _public member_ `TArray<FSceneOutlinerTreeItemID> ItemIDs;`
- L244 _public member_ `TArray<FFolder> NewPaths;` — Used for FolderMoved events
- L246 _public member_ `uint8 ItemActions = 0;` — Actions to apply to items

#### enum `FSceneOutlinerHierarchyChangedData::(anonymous)`  
``  
_L231-237_

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SCENEOUTLINER_API`
- L30 _function_ `FORCEINLINE uint32 GetTypeHash(FFolderKey Key)`
- L151 _function_ `friend uint32 GetTypeHash(const FSceneOutlinerTreeItemID& ItemID)`
- L199 _function_ `friend uint32 GetTypeHash(const FSceneOutlinerTreeItemType& Type)`
- L232 _enumerator_ `Added` (scope `FSceneOutlinerHierarchyChangedData::__anonb4aa1f1d0103`)
- L233 _enumerator_ `Removed` (scope `FSceneOutlinerHierarchyChangedData::__anonb4aa1f1d0103`)
- L234 _enumerator_ `Moved` (scope `FSceneOutlinerHierarchyChangedData::__anonb4aa1f1d0103`)
- L235 _enumerator_ `FolderMoved` (scope `FSceneOutlinerHierarchyChangedData::__anonb4aa1f1d0103`)
- L236 _enumerator_ `FullRefresh` (scope `FSceneOutlinerHierarchyChangedData::__anonb4aa1f1d0103`)

### `Source/Editor/SceneOutliner/Public/SceneOutlinerTextInfoColumn.h` (Public)


#### class `FTextInfoColumn`  
`class FTextInfoColumn : public ISceneOutlinerColumn`  
_L27-73_
- inherits: `ISceneOutlinerColumn`
- desc: A custom column for the SceneOutliner which is capable of displaying any text based information related to items Note: Only has support for text, any other requirements should have a custom column made
- L35 _public prototype_ `FTextInfoColumn(ISceneOutliner& Outliner, const FName InColumnName, const FGetTextForItem& InGetTextForItem, const FText InColumnToolTip);` — Constructor
- L37 _public prototype_ `virtual ~FTextInfoColumn() = default;`
- L40 _public prototype_ `static TSharedRef<ISceneOutlinerColumn> CreateTextInfoColumn(ISceneOutliner& Outliner, const FName InColumnName, const FGetTextForItem InGetTextForItem, const FText InColumnToolTip);` — Factory function to create a TextInfoColumn (This column is not registered by default because of it's requirements and therefore requires a factory!)
- L45 _public prototype_ `virtual FName GetColumnID() override;`
- L47 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L49 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L51 _public prototype_ `virtual void PopulateSearchStrings(const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings) const override;`
- L53 _public prototype_ `virtual bool SupportsSorting() const override;`
- L55 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L62 _private prototype_ `FText GetInfoForItem(TWeakPtr<ISceneOutlinerTreeItem> TreeItem) const;`
- L64 _private member_ `FName ColumnName;`
- L66 _private member_ `FText ColumnToolTip;`
- L69 _private member_ `TWeakPtr< ISceneOutliner > SceneOutlinerWeak;` — Weak reference to the outliner widget that owns our list
- L72 _private member_ `FGetTextForItem GetTextForItem;` — Delegate Called to Get Display Text for an item in the column

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SCENEOUTLINER_API`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetTextForItem, const ISceneOutlinerTreeItem&);` — A delegate used to factory a new TextInfo Column
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FGetTextForItem, const ISceneOutlinerTreeItem&);` — A delegate used to factory a new TextInfo Column

### `Source/Editor/SceneOutliner/Public/SceneOutlinerTreeItemSCC.h` (Public)


#### class `FSceneOutlinerTreeItemSCC`  
`class FSceneOutlinerTreeItemSCC : public TSharedFromThis<FSceneOutlinerTreeItemSCC>`  
_L16-66_
- inherits: `TSharedFromThis<FSceneOutlinerTreeItemSCC>`
- L19 _public prototype_ `FSceneOutlinerTreeItemSCC(FSceneOutlinerTreeItemPtr InTreeItemPtr);`
- L20 _public prototype_ `~FSceneOutlinerTreeItemSCC();`
- L23 _public prototype_ `void Initialize();` — Actually attempt to connect to Revision Control and get the item's status
- L25 _public prototype_ `FSourceControlStatePtr GetSourceControlState();`
- L26 _public prototype_ `FSourceControlStatePtr RefreshSourceControlState();`
- L27 _public function_ `TWeakPtr<FUncontrolledChangelistState> GetUncontrolledChangelistState()`
- L29 _public function_ `bool HasValidPackage() const`
- L30 _public function_ `FString GetPackageName() const`
- L31 _public function_ `FString GetPackageFileName() const`
- L32 _public prototype_ `UPackage* GetPackage() const;`
- L33 _public prototype_ `UPackage* LoadPackage() const;`
- L35 _public member_ `FSourceControlStateChangedDelegate OnSourceControlStateChanged;`
- L36 _public member_ `FUncontrolledStateChangedDelegate OnUncontrolledChangelistsStateChanged;`
- L38 _private prototype_ `void ConnectSourceControl();`
- L39 _private prototype_ `void DisconnectSourceControl();`
- L40 _private prototype_ `void HandleSourceControlStateChanged(EStateCacheUsage::Type CacheUsage);`
- L41 _private prototype_ `void HandleSourceControlProviderChanged(ISourceControlProvider& OldProvider, ISourceControlProvider& NewProvider);`
- L42 _private prototype_ `void BroadcastNewState(FSourceControlStatePtr SourceControlState);`
- L43 _private prototype_ `void HandleUncontrolledChangelistsStateChanged();`
- L46 _private member_ `FSceneOutlinerTreeItemPtr TreeItemPtr;` — The tree item we relate to
- L49 _private member_ `FString ExternalPackageName;` — Cache the items external package name and filename
- L50 _private member_ `FString ExternalPackageFileName;`
- L53 _private member_ `FDelegateHandle SourceControlStateChangedDelegateHandle;` — Source control state changed delegate handle
- L56 _private member_ `FDelegateHandle SourceControlProviderChangedDelegateHandle;` — Source control provider changed delegate handle
- L59 _private member_ `FDelegateHandle ActorPackingModeChangedDelegateHandle;` — Actor packaging mode changed delegate handle
- L62 _private member_ `FDelegateHandle UncontrolledChangelistChangedHandle;` — Uncontrolled Changelist Changed changed delegate handle
- L65 _private member_ `TSharedPtr<FUncontrolledChangelistState> UncontrolledChangelistState;` — The uncontrolled changelist this file belongs to, empty if this item is not uncontrolled

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "SceneOutlinerTreeItemSCC"`
- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FSourceControlStateChangedDelegate, FSourceControlStatePtr);`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FSourceControlStateChangedDelegate, FSourceControlStatePtr);`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FUncontrolledStateChangedDelegate, TSharedPtr<FUncontrolledChangelistState>);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FUncontrolledStateChangedDelegate, TSharedPtr<FUncontrolledChangelistState>);`

### `Source/Editor/SceneOutliner/Public/SortHelper.h` (Public)


#### struct `SceneOutliner::FNumericStringWrapper`  
`struct FNumericStringWrapper`  
_L13-45_
- desc: Wrapper type that will sort FString's using a more natural comparison (correctly sorts numbers and ignores underscores)
- L15 _public member_ `FString String;`
- L17 _public function_ `FNumericStringWrapper()`
- L19 _public function_ `FNumericStringWrapper(FString&& InString) : String(InString)`
- L22 _public function_ `FNumericStringWrapper(FNumericStringWrapper&& Other) : String(MoveTemp(Other.String))`
- L25 _public function_ `FNumericStringWrapper& operator=(FNumericStringWrapper&& Other)`
- L30 _public function_ `FORCEINLINE bool operator<(const FNumericStringWrapper& Other) const`
- L34 _public function_ `FORCEINLINE bool operator>(const FNumericStringWrapper& Other) const`
- L38 _public function_ `FORCEINLINE bool operator==(const FNumericStringWrapper& Other) const`
- L43 _private prototype_ `FNumericStringWrapper(const FNumericStringWrapper&);`
- L44 _private prototype_ `FNumericStringWrapper& operator=(const FNumericStringWrapper&);`

#### struct `FSceneOutlinerSortHelper`  
`template<typename PrimaryKeyType, typename SecondaryKeyType = int32> struct FSceneOutlinerSortHelper`  
_L61-171_
- desc: Templated helper to alleviate performance problems with sorting based on complex predicates. Example Usage: FSceneOutlinerSortHelper<FString>().Primary([](const ISceneOutlinerTreeItem& Item){ return Item->GetString(); }).SortItems(Array); Or: FSceneOutlinerSortHelper<FString, FString>() .Primary(FGetPrimaryString()) .Secondary(FGetSecondaryString()) .SortItems(Array);
- L63 _public typedef_ `typedef TFunction<PrimaryKeyType(const ISceneOutlinerTreeItem&)> FPrimaryFunction;`
- L64 _public typedef_ `typedef TFunction<SecondaryKeyType(const ISceneOutlinerTreeItem&)> FSecondaryFunction;`
- L66 _public function_ `FSceneOutlinerSortHelper() : PrimarySortMode(EColumnSortMode::None), SecondarySortMode(EColumnSortMode::None)`
- L71 _public function_ `FSceneOutlinerSortHelper& Primary(FPrimaryFunction&& Function, EColumnSortMode::Type SortMode)` — Sort primarily by the specified function and mode. Beware the function is a reference, so must be valid for the lifetime of this instance.
- L79 _public function_ `FSceneOutlinerSortHelper& Secondary(FSecondaryFunction&& Function, EColumnSortMode::Type SortMode)` — Sort secondarily by the specified function and mode. Beware the function is a reference, so must be valid for the lifetime of this instance.
- L87 _public function_ `void Sort(TArray<FSceneOutlinerTreeItemPtr>& Array)` — Sort the specified array using the current sort settings
- L134 _private member_ `EColumnSortMode::Type PrimarySortMode;`
- L135 _private member_ `EColumnSortMode::Type SecondarySortMode;`
- L137 _private member_ `FPrimaryFunction PrimaryFunction;`
- L138 _private member_ `FSecondaryFunction SecondaryFunction;`

#### struct `FSceneOutlinerSortHelper::FSortPayload`  
`struct FSortPayload`  
_L141-170_
- desc: Aggregated data from the sort methods. We extract the sort data from all elements first, then sort based on the extracted data.
- L143 _public member_ `int32 OriginalIndex;`
- L145 _public member_ `PrimaryKeyType PrimaryKey;`
- L146 _public member_ `SecondaryKeyType SecondaryKey;`
- L148 _public member_ `int32 DefaultSortID;`
- L150 _public function_ `FSortPayload(int32 InOriginalIndex, PrimaryKeyType&& InPrimaryKey, SecondaryKeyType&& InSecondaryKey, int32 InDefaultSortID) : OriginalIndex(InOriginalIndex), PrimaryKey(MoveTemp(InPrimaryKey)), SecondaryKey(MoveTemp(InSecondaryKey)), DefaultSortID(InDefaultSortID)`
- L154 _public function_ `FSortPayload(FSortPayload&& Other)`
- L158 _public function_ `FSortPayload& operator=(FSortPayload&& rhs)`
- L168 _private prototype_ `FSortPayload(const FSortPayload&);`
- L169 _private prototype_ `FSortPayload& operator=(const FSortPayload&);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace SceneOutliner`
- L108 _function_ `SortData.Sort([&](const FSortPayload& One, const FSortPayload& Two){ if (PrimarySortMode == EColumnSortMode::Ascending && One.PrimaryKey != Two.PrimaryKey) return One.PrimaryKey < Two.PrimaryKey; else if (PrimarySortMode == EColumnSortMode::Descending && One.PrimaryKey != Two.PrimaryKey) return One.PrimaryKey > Two.PrimaryKey; if (SecondarySortMode == EColumnSortMode::Ascending && One.SecondaryKey != Two.SecondaryKey) return One.SecondaryKey < Two.SecondaryKey; else if (SecondarySortMode == EColumnSortMode::Descending && One.SecondaryKey != Two.SecondaryKey) return One.SecondaryKey > Two.SecondaryKey; return One.DefaultSortID < Two.DefaultSortID; });` (scope `FSceneOutlinerSortHelper::Sort`)

### `Source/Editor/SceneOutliner/Public/WorldTreeItem.h` (Public)


#### struct `FWorldTreeItem`  
`struct FWorldTreeItem : ISceneOutlinerTreeItem`  
_L21-75_
- inherits: `ISceneOutlinerTreeItem`
- desc: A tree item that represents an entire world
- L24 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UWorld*);`
- L25 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UWorld*);`
- L27 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L32 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L38 _public member_ `mutable TWeakObjectPtr<UWorld> World;` — The world this tree item is associated with.
- L41 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L44 _public member_ `static const FSceneOutlinerTreeItemType Type;` — Static type identifier for this tree item class
- L47 _public prototype_ `FWorldTreeItem(UWorld* InWorld);` — Construct this item from a world
- L48 _public prototype_ `FWorldTreeItem(TWeakObjectPtr<UWorld> InWorld);`
- L51 _public function_ `virtual bool IsValid() const override` — Begin ISceneOutlinerTreeItem Implementation
- L52 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L53 _public prototype_ `virtual FString GetDisplayString() const override;`
- L54 _public prototype_ `virtual bool CanInteract() const override;`
- L55 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner) override;`
- L56 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L60 _public prototype_ `void OpenWorldSettings() const;` — Open the world settings for the contained world
- L62 _public prototype_ `void BrowseToAsset() const;` — Browse to world asset in content browser
- L63 _public prototype_ `bool CanBrowseToAsset() const;`
- L66 _public prototype_ `FString GetWorldName() const;` — Get just the name of the world, for tooltip use
- L68 _public typedef_ `using FContextMenuProviderFunc = TFunction<void(const UWorld*, UToolMenu*)>;`
- L69 _public prototype_ `static void RegisterContextMenuProvider(FName InProviderName, const FContextMenuProviderFunc& InProviderFunc);`
- L70 _public prototype_ `static void UnregisterContextMenuProvider(FName InProviderName);`
- L74 _private member_ `static TMap<FName, FContextMenuProviderFunc> ContextMenuProviders;` — Static map that registers all context menu providers

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SCENEOUTLINER_API`
- L14 _namespace_ `namespace SceneOutliner`
- L17 _prototype_ `FText GetWorldDescription(UWorld* World);` (scope `SceneOutliner`) — Get a description of a world to display in the scene outliner
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const UWorld*);`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const UWorld*);`
