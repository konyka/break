# Plugins / TedsTableViewer

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer`
- headers: 25; symbols: 834
- symbol kinds: class=32, delegate=14, enum=4, enumerator=7, function=53, macro=11, member=208, namespace=119, prototype=345, struct=20, typedef=20, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorWidgets, Engine, InputCore, Slate, SlateCore, ToolMenus, ToolWidgets, WorkspaceMenuStructure
- PublicDependencyModuleNames: TedsOperations, TedsQueryStack, TypedElementFramework

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Private/QueryStack/AddParentHierarchyRowsNode.h` (Private)


#### class `UE::Editor::DataStorage::QueryStack::FAddParentHierarchyRowNode`  
`class FAddParentHierarchyRowNode : public IRowNode`  
_L19-43_
- inherits: `IRowNode`
- desc: A custom query stack node to add any missing parents of the given node rows in the hierarchy viewer Ex: Filter matches child row and moves that child row to the outer hierarchy level since it doesn't have a parent
- L23 _public prototype_ `FAddParentHierarchyRowNode(const ICoreProvider* InStorage, TSharedPtr<IHierarchyViewerDataInterface> InHierarchyData, TSharedPtr<IRowNode> InParent);`
- L25 _public prototype_ `virtual ~FAddParentHierarchyRowNode() override = default;`
- L28 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;` — Retrieve access to the rows used by this node.
- L29 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L30 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L31 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L34 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L35 _protected prototype_ `void UpdateRows();`
- L37 _protected member_ `RevisionId Revision = UninitializedRevisionId;`
- L38 _protected member_ `const ICoreProvider* Storage = nullptr;`
- L39 _protected member_ `TSharedPtr<IHierarchyViewerDataInterface> HierarchyData;`
- L40 _protected member_ `TSharedPtr<IRowNode> Parent;`
- L41 _protected member_ `FRowHandleArray Rows;`
- L42 _protected member_ `RevisionId CachedParentRevision = UninitializedRevisionId;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Private/QueryStack/TopLevelRowsNode.h` (Private)


#### class `UE::Editor::DataStorage::QueryStack::FTopLevelRowsNode`  
`class FTopLevelRowsNode : public IRowNode`  
_L18-41_
- inherits: `IRowNode`
- desc: A custom query stack node to get top level rows of the given rows to display in the hierarchy viewer
- L22 _public prototype_ `FTopLevelRowsNode(const ICoreProvider* InStorage, TSharedPtr<IHierarchyViewerDataInterface> InHierarchyData, TSharedPtr<IRowNode> InParent);`
- L23 _public prototype_ `virtual ~FTopLevelRowsNode() override = default;`
- L26 _public prototype_ `virtual FRowHandleArrayView GetRows() const override;` — Retrieve access to the rows used by this node.
- L27 _public prototype_ `virtual FRowHandleArray& GetMutableRows() override;`
- L28 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L29 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L32 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L33 _protected prototype_ `void UpdateRows();`
- L35 _protected member_ `RevisionId Revision = 0;`
- L36 _protected member_ `const ICoreProvider* Storage = nullptr;`
- L37 _protected member_ `TSharedPtr<IHierarchyViewerDataInterface> HierarchyData;`
- L38 _protected member_ `TSharedPtr<IRowNode> Parent;`
- L39 _protected member_ `FRowHandleArray Rows;`
- L40 _protected member_ `RevisionId CachedParentRevision = TNumericLimits<RevisionId>::Max();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Editor` (scope `UE`)
- L15 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Private/Widgets/STedsTreeView.h` (Private)


#### class `UE::Editor::DataStorage::STedsTreeView`  
`class STedsTreeView : public STreeView<TableViewerItemPtr>`  
_L13-78_
- inherits: `STreeView<TableViewerItemPtr>`
- desc: A tree view widget specialized for TableViewerItemPtr to support constructing the widget using a bottom up hierarchy (FOnGetParent)
- L18 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TableViewerItemPtr , FOnGetParent, TableViewerItemPtr ) SLATE_BEGIN_ARGS(STedsTreeView)` — Delegate that gets the parent row handle for a given row
- L23 _public prototype_ `SLATE_ARGUMENT( const TArray<TableViewerItemPtr>*, RowsSource ) SLATE_ARGUMENT( const TArray<TableViewerItemPtr>*, TopLevelRowsSource ) SLATE_EVENT( FOnGenerateRow, OnGenerateRow ) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnExpansionChanged, OnExpansionChanged ) SLATE_EVENT( FOnSetExpansionRecursive, OnSetExpansionRecursive ) SLATE_ATTRIBUTE( ESelectionMode::Type, SelectionMode ) SLATE_ARGUMENT( TSharedPtr<SHeaderRow>, HeaderRow ) SLATE_ARGUMENT(bool, AllowInvisibleItemSelection);` — All the rows that can be displayed by the widget
- L49 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const FOnGetParent& InOnGetParent, RowHandle InWidgetRow );`
- L53 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L54 _public prototype_ `virtual void RequestListRefresh() override;`
- L59 _protected prototype_ `void UpdateTreeMap();` — Update the internal tree map used to contain the hierarchy
- L62 _protected prototype_ `void GetChildren_Internal(TableViewerItemPtr InParent, TArray<TableViewerItemPtr>& OutChildren);` — For a given row, get all the children
- L66 _protected member_ `FOnGetParent OnGetParent;`
- L68 _protected member_ `RowHandle WidgetRow = InvalidRowHandle;`
- L71 _protected member_ `const TArray<TableViewerItemPtr>* RowsSource = nullptr;` — All rows that can be shown in this tree, including the full hieararchy regardless of whether it is currently expanded
- L74 _protected member_ `TMap<TableViewerItemPtr, TArray<TableViewerItemPtr>> TreeMap;` — The internal tree map used to contain the hierarchy
- L77 _protected member_ `bool bDirty = false;` — Whether the TreeMap needs to be re-calculated

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TableViewerItemPtr , FOnGetParent, TableViewerItemPtr ) SLATE_BEGIN_ARGS(STedsTreeView) {} SLATE_ARGUMENT( const TArray<TableViewerItemPtr>*, RowsSource ) SLATE_ARGUMENT( const TArray<TableViewerItemPtr>*, TopLevelRowsSource ) SLATE_EVENT( FOnGenerateRow, OnGenerateRow ) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnExpansionChanged, OnExpansionChanged ) SLATE_EVENT( FOnSetExpansionRecursive, OnSetExpansionRecursive ) SLATE_ATTRIBUTE( ESelectionMode::Type, SelectionMode ) SLATE_ARGUMENT( TSharedPtr<SHeaderRow>, HeaderRow ) SLATE_ARGUMENT(bool, AllowInvisibleItemSelection);` — Delegate that gets the parent row handle for a given row

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/HierarchyViewerIntefaces.h` (Public)


#### class `UE::Editor::DataStorage::IHierarchyViewerDataInterface`  
`class IHierarchyViewerDataInterface`  
_L15-34_
- desc: Data interface for the hierarchy viewer to extract hierarchy information from a row
- L20 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParentChanged, RowHandle);` — Delegate that is fired when the parent of a row on this hierarchy changes
- L22 _public prototype_ `virtual ~IHierarchyViewerDataInterface() = default;`
- L23 _public prototype_ `virtual RowHandle GetParent(const ICoreProvider& Storage, RowHandle InRow) const = 0;`
- L24 _public prototype_ `virtual void WalkDepthFirst(const ICoreProvider& Storage, RowHandle InRow, ICoreProvider::FHierarchyIterationCallback VisitFn, ICoreProvider::ETraversalOrder TraversalOrder = ICoreProvider::ETraversalOrder::PreOrder) const = 0;`
- L27 _public function_ `FOnParentChanged& OnHierarchyChangedEvent()`
- L33 _protected member_ `FOnParentChanged ParentChangedEvent;`

#### class `UE::Editor::DataStorage::FHierarchyViewerData`  
`class FHierarchyViewerData : public IHierarchyViewerDataInterface`  
_L37-55_
- inherits: `IHierarchyViewerDataInterface`
- desc: Data interface for the hierarchy viewer that operates on a single FHierarchyHandle
- L40 _public prototype_ `explicit FHierarchyViewerData(ICoreProvider& Storage, FHierarchyHandle InHierarchyHandle);`
- L42 _public prototype_ `virtual RowHandle GetParent(const ICoreProvider& Storage, RowHandle InRow) const override;`
- L43 _public prototype_ `virtual void WalkDepthFirst(const ICoreProvider& Storage, RowHandle InRow, ICoreProvider::FHierarchyIterationCallback VisitFn, ICoreProvider::ETraversalOrder TraversalOrder = ICoreProvider::ETraversalOrder::PreOrder) const override;`
- L45 _public prototype_ `FHierarchyHandle GetHierarchy() const;`
- L48 _protected prototype_ `void RegisterQueries(ICoreProvider& Storage);`
- L49 _protected prototype_ `void UnRegisterQueries(ICoreProvider& Storage);`
- L52 _protected member_ `FHierarchyHandle HierarchyHandle;`
- L53 _protected member_ `QueryHandle ParentAddedQuery = InvalidQueryHandle;`
- L54 _protected member_ `QueryHandle ParentRemovedQuery = InvalidQueryHandle;`

#### class `UE::Editor::DataStorage::FHierarchyViewerMultiData`  
`class FHierarchyViewerMultiData : public IHierarchyViewerDataInterface`  
_L58-73_
- inherits: `IHierarchyViewerDataInterface`
- desc: Accepts an ordered list of hierarchies to combine into one singular view.
- L61 _public prototype_ `FHierarchyViewerMultiData(ICoreProvider& Storage, TArray<FHierarchyHandle> OrderedHierarchyHandles);`
- L63 _public prototype_ `virtual RowHandle GetParent(const ICoreProvider& Storage, RowHandle InRow) const override;` — Returns the first parent it finds among the list of hierarchies
- L65 _public prototype_ `virtual void WalkDepthFirst(const ICoreProvider& Storage, RowHandle InRow, ICoreProvider::FHierarchyIterationCallback VisitFn, ICoreProvider::ETraversalOrder TraversalOrder = ICoreProvider::ETraversalOrder::PreOrder) const override;` — Does a DFS of each hierarchy one-by-one. If a child is encountered multiple times in different hierarchies, it is only reported in the first instance
- L69 _public prototype_ `void ForEachHierarchyData(TFunctionRef<bool(const TSharedRef<FHierarchyViewerData>&)> VisitFn) const;` — Iterate over each contained hierarchy data. The callback can return false to terminate iteration early
- L72 _protected member_ `TArray<TSharedPtr<FHierarchyViewerData>> Hierarchies;`

#### class `UE::Editor::DataStorage::FRelationTypeHierarchyViewerData`  
`class FRelationTypeHierarchyViewerData : public IHierarchyViewerDataInterface`  
_L78-88_
- inherits: `IHierarchyViewerDataInterface`
- desc: Data interface for a hierarchical relation registered directly via RegisterRelationType (HierarchyMode != Disabled). These relations are not registered in FTedsHierarchyRegistrar and have no FHierarchyHandle, but still support parent/child traversal via the RelationTypeHandle API on ICoreProvider.
- L81 _public prototype_ `explicit FRelationTypeHierarchyViewerData(RelationTypeHandle InRelationType);`
- L82 _public prototype_ `virtual RowHandle GetParent(const ICoreProvider& Storage, RowHandle InRow) const override;`
- L83 _public prototype_ `virtual void WalkDepthFirst(const ICoreProvider& Storage, RowHandle InRow, ICoreProvider::FHierarchyIterationCallback VisitFn, ICoreProvider::ETraversalOrder TraversalOrder = ICoreProvider::ETraversalOrder::PreOrder) const override;`
- L87 _private member_ `RelationTypeHandle RelationType;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnParentChanged, RowHandle);` — Delegate that is fired when the parent of a row on this hierarchy changes

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/ITedsTableViewer.h` (Public)


#### class `UE::Editor::DataStorage::ITableViewer`  
`class ITableViewer`  
_L15-57_
- desc: Interface for all types of TEDS table viewers
- L20 _public prototype_ `virtual void ForEachSelectedRow(TFunctionRef<void(RowHandle)> InCallback) const = 0;` — Execute the given callback for each row handle selected in the table viewer
- L23 _public prototype_ `virtual RowHandle GetWidgetRowHandle() const = 0;` — Get the row handle for the widget row that contains the contents of the table viewer itself
- L26 _public prototype_ `virtual void SetSelection(RowHandle Row, bool bSelected, const ESelectInfo::Type SelectInfo) const = 0;` — Set the currently selected row in the table viewer
- L29 _public prototype_ `virtual void ScrollIntoView(RowHandle Row) const = 0;` — Scroll the input row into view in the table viewer
- L32 _public prototype_ `virtual void ClearSelection() const = 0;` — Deselect all items in the table viewer
- L35 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() = 0;` — Get the table viewer as an SWidget
- L38 _public prototype_ `virtual bool IsSelected(RowHandle InRow) const = 0;` — Get if a specific row is selected
- L41 _public prototype_ `virtual bool IsSelectedExclusively(RowHandle InRow) const = 0;` — Get if a specific row is selected exclusively
- L45 _public prototype_ `virtual void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InRowWidgetFactory) = 0;` — Add a custom per-row widget to the table viewer (that doesn't necessarily map to a TEDS column) This usually means a new column for column-based views
- L48 _public prototype_ `virtual void SetQueryStack(TSharedPtr<QueryStack::IRowNode> InRowQueryStack) = 0;` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L51 _public prototype_ `virtual void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns) = 0;` — Clear the current list of columns being displayed and set it to the given list
- L54 _public prototype_ `virtual void SetTableViewerIdentifier(const FName& NewIdentifier) = 0;` — Sets the Table Identifier (Can be used in case data is dynamic and created post widget init)
- L56 _public prototype_ `virtual ~ITableViewer() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsFilter.h` (Public)


#### class `UE::Editor::DataStorage::FTedsFilter`  
`class FTedsFilter : public FTedsFilterBase<FTedsRowHandle&>`  
_L14-33_
- inherits: `FTedsFilterBase<FTedsRowHandle&>`
- L23 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;` — Notification that the filter became active or inactive
- L26 _public prototype_ `virtual bool PassesFilter(FTedsRowHandle& InItem ) const override;` — Returns whether the specified Item passes the Filter's restrictions
- L30 _protected prototype_ `void SetTedsFilterBar(const TSharedPtr<STedsFilterBar>& InTedsFilterBar);` — Sets a TedsFilterBar to be used by this Filter
- L32 _protected member_ `TWeakPtr<STedsFilterBar> TedsFilterBar;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsFilter.inl` (Public)


#### class `UE::Editor::DataStorage::FTedsFilterBase`  
`template<typename FilterType> class FTedsFilterBase : public FFilterBase<FilterType>`  
_L35-188_
- inherits: `FFilterBase<FilterType>`
- L48 _public prototype_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, const QueryHandle& InFilterQuery, const bool bActiveByDefault = false);` — Constructor for a TEDS Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterToolTip Tooltip to describe the function of the Filter @param InFilterIconName Name of an icon in the App Style Set to display in the Add Filter Menu @param InCategory Group to place the filter in the Add Filter Menu @param InFilterQuery QueryHandle of a registered query to filter for (must be the same syntax as any other Query used in the viewer) @param bActiveByDefault Whether this filter should be active by default and can be implemented per-inherited filter type
- L58 _public prototype_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const QueryHandle& InFilterQuery, const bool bActiveByDefault = false);` — Constructor for a TEDS Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterQuery QueryHandle of a registered query to filter for (must be the same syntax as any other Query used in the viewer) @param bActiveByDefault Whether this filter should be active by default and can be implemented per-inherited filter type
- L70 _public prototype_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, const Queries::TConstQueryFunction<bool>& InFilterQuery, const bool bActiveByDefault = false);` — Constructor for a TEDS Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterToolTip Tooltip to describe the function of the Filter @param InFilterIconName Name of an icon in the App Style Set to display in the Add Filter Menu @param InCategory Group to place the filter in the Add Filter Menu @param InFilterQuery QueryFunction to filter for, Batching should be used for improved performance if possible @param bActiveByDefault Whether this filter should be active by default and can be implemented per-inherited filter type
- L80 _public prototype_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const Queries::TConstQueryFunction<bool>& InFilterQuery, const bool bActiveByDefault = false);` — Constructor for a TEDS Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterQuery QueryFunction to filter for, Batching should be used for improved performance if possible @param bActiveByDefault Whether this filter should be active by default and can be implemented per-inherited filter type
- L98 _public function_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, FilterFunction&& InFilterQuery, const bool bActiveByDefault = false) : FTedsFilterBase( InFilterName, InFilterDisplayName, InFilterToolTip, InFilterIconName, InCategory, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(InFilterQuery)), bActiveByDefault)`
- L122 _public function_ `FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, FilterFunction&& InFilterQuery, const bool bActiveByDefault = false) : FTedsFilterBase( InFilterName, InFilterDisplayName, FText::FromString(InFilterName.ToString()), FName(), nullptr, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(InFilterQuery)), bActiveByDefault)`
- L139 _public prototype_ `FTedsFilterBase(const UClass* InClass, const TSharedPtr<FFilterCategory>& InCategory = nullptr, const bool bActiveByDefault = false);` — Constructor for a TEDS Class Filter @param InClass UClass to filter for on the TypeInfo Column @param InCategory Group to place the filter in the Add Filter Menu @param bActiveByDefault Whether this filter should be active by default and can be implemented per-inherited filter type
- L141 _public prototype_ `virtual ~FTedsFilterBase() override = default;`
- L143 _public prototype_ `void SetCategory(const TSharedPtr<FFilterCategory>& InCategory);`
- L145 _public function_ `bool IsClassFilter() const`
- L147 _public function_ `bool IsActiveByDefault() const`
- L149 _public function_ `FName GetIdentifier() const`
- L152 _public prototype_ `virtual FString GetName() const override;` — Returns the system name for this filter
- L155 _public prototype_ `virtual FText GetDisplayName() const override;` — Returns the human-readable name for this filter
- L158 _public prototype_ `virtual FText GetToolTipText() const override;` — Returns the tooltip for this filter, shown in the filters menu
- L161 _public prototype_ `virtual FLinearColor GetColor() const override;` — Returns the color this filter button will be when displayed as a button
- L164 _public prototype_ `virtual FName GetIconName() const override;` — Returns the name of the icon to use in menu entries
- L167 _public prototype_ `virtual bool IsInverseFilter() const override;` — If true, the filter will be active in the FilterBar when it is inactive in the UI (i.e the filter pill is grayed out)
- L170 _public prototype_ `virtual void ModifyContextMenu(FMenuBuilder& MenuBuilder) override;` — Called when the right-click context menu is being built for this filter
- L173 _public prototype_ `virtual void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const override;` — Can be overriden for custom FilterBar subclasses to save settings, currently not implemented in any generic Filter Bar
- L176 _public prototype_ `virtual void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) override;` — Can be overridden for custom FilterBar subclasses to load settings, currently not implemented in any generic Filter Bar
- L179 _protected member_ `FName FilterName;`
- L180 _protected member_ `FText FilterDisplayName;`
- L181 _protected member_ `FText FilterToolTip;`
- L182 _protected member_ `FName FilterIconName;`
- L184 _protected member_ `const bool bIsClassFilter;`
- L185 _protected member_ `const bool bActiveByDefault;`
- L187 _protected member_ `TVariant<QueryHandle, Queries::TConstQueryFunction<bool>> FilterQuery;`
- L191 _function_ `template<typename FilterType> FTedsFilterBase<FilterType>::FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, const QueryHandle& InFilterQuery, const bool bActiveByDefault) : FFilterBase<FilterType>(InCategory) , FilterName(InFilterName) , FilterDisplayName(InFilterDisplayName) , FilterToolTip(InFilterToolTip) , FilterIconName(InFilterIconName) , bIsClassFilter(false) , bActiveByDefault(bActiveByDefault)`
- L205 _function_ `template<typename FilterType> FTedsFilterBase<FilterType>::FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const QueryHandle& InFilterQuery, const bool bActiveByDefault) : FTedsFilterBase(InFilterName, InFilterDisplayName, FText::FromString(InFilterName.ToString()), FName(), nullptr, InFilterQuery, bActiveByDefault)`
- L226 _function_ `template<typename FilterType> FTedsFilterBase<FilterType>::FTedsFilterBase(const FName& InFilterName, const FText& InFilterDisplayName, const Queries::TConstQueryFunction<bool>& InFilterQuery, const bool bActiveByDefault) : FTedsFilterBase(InFilterName, InFilterDisplayName, FText::FromString(InFilterName.ToString()), FName(), nullptr, InFilterQuery, bActiveByDefault)`
- L233 _function_ `template<typename FilterType> FTedsFilterBase<FilterType>::FTedsFilterBase(const UClass* InClass, const TSharedPtr<FFilterCategory>& InCategory, const bool bActiveByDefault) : FFilterBase<FilterType>(InCategory) , FilterName(InClass->GetFName()) , FilterDisplayName(InClass->GetDisplayNameText()) , FilterToolTip(FText::Format(LOCTEXT("FilterClassTooltip", "Filter by {0}"), InClass->GetDisplayNameText())) , FilterIconName(FSlateIconFinder::FindIconForClass(InClass).GetStyleName()) , bIsClassFilter(true) , bActiveByDefault(bActiveByDefault)`
- L254 _function_ `template<typename FilterType> void FTedsFilterBase<FilterType>::SetCategory(const TSharedPtr<FFilterCategory>& InCategory)`
- L260 _function_ `template<typename FilterType> FString FTedsFilterBase<FilterType>::GetName() const`
- L266 _function_ `template<typename FilterType> FText FTedsFilterBase<FilterType>::GetDisplayName() const`
- L272 _function_ `template<typename FilterType> FText FTedsFilterBase<FilterType>::GetToolTipText() const`
- L278 _function_ `template<typename FilterType> FLinearColor FTedsFilterBase<FilterType>::GetColor() const`
- L284 _function_ `template<typename FilterType> FName FTedsFilterBase<FilterType>::GetIconName() const`
- L290 _function_ `template<typename FilterType> bool FTedsFilterBase<FilterType>::IsInverseFilter() const`
- L296 _function_ `template<typename FilterType> void FTedsFilterBase<FilterType>::ModifyContextMenu(FMenuBuilder& MenuBuilder)`
- L300 _function_ `template<typename FilterType> void FTedsFilterBase<FilterType>::SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const`
- L304 _function_ `template<typename FilterType> void FTedsFilterBase<FilterType>::LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "TEDSFilter"`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _function_ `inline bool CheckValidFilterQueryHandle(const QueryHandle& InQueryHandle)` (scope `UE::Editor::DataStorage`) — Helper function to check if the given QueryHandle is valid to be used in a filter (is not an observer).
- L245 _function_ `` (scope `UE::Editor::DataStorage::FTedsFilterBase::FTedsFilterBase`)
- L247 _function_ `` (scope `UE::Editor::DataStorage::FTedsFilterBase::FTedsFilterBase::__anon373875560102`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsTableViewerColumn.h` (Public)


#### class `UE::Editor::DataStorage::FTedsTableViewerColumn`  
`class FTedsTableViewerColumn`  
_L26-133_
- desc: Class representing a column in the UI of the table viewer. Can be constructed using a NameID and a WidgetConstructor to create the actual widgets for rows (optionally supplying a header widget constructor and widget metadata to use)
- L30 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsRowVisible, const RowHandle);` — Delegate to check if a row is currently visible in the owning table viewer's UI
- L32 _public prototype_ `FTedsTableViewerColumn( const FName& ColumnName,`
- L40 _public prototype_ `~FTedsTableViewerColumn();`
- L42 _public prototype_ `TSharedPtr<SWidget> ConstructRowWidget(RowHandle InRowHandle, TFunction<void(ICoreProvider&, const RowHandle&)> WidgetRowSetupDelegate = nullptr) const;`
- L45 _public prototype_ `SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn();`
- L47 _public prototype_ `void Tick();`
- L49 _public prototype_ `void SetIsRowVisibleDelegate(FIsRowVisible InIsRowVisibleDelegate);`
- L52 _public prototype_ `FName GetColumnName() const;`
- L54 _public prototype_ `TConstArrayView<TWeakObjectPtr<const UScriptStruct>> GetMatchedColumns() const;`
- L56 _public prototype_ `ICoreProvider* GetStorage() const;`
- L59 _public prototype_ `DECLARE_DELEGATE_FourParams(FOnSort, FName ColumnName, TSharedPtr<const FColumnSorterInterface> ColumnSorter, EColumnSortMode::Type Direction, EColumnSortPriority::Type Priority);` — Delegate triggered when a column is sorted.
- L62 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsSorting);` — Delegate triggered used to determine is sorting is in progress.
- L70 _public prototype_ `void OnGetSearchStringCallback(const RowHandle& InRowHandle, TArray< FString >& OutSearchStrings);`
- L71 _public prototype_ `void SetInitialSortMode(EColumnSortMode::Type InSortMode);`
- L72 _public prototype_ `void SetSortDelegates(FSortHandler InSortDelegates);`
- L73 _public prototype_ `bool HasSortInfo() const;`
- L74 _public prototype_ `void ClearSort();`
- L75 _public prototype_ `void OnSortCallback(EColumnSortPriority::Type InSortPriority, const FName& InColumnId, EColumnSortMode::Type InSortDirection);`
- L76 _public prototype_ `FComboMetaDataView<FGenericMetaDataView, FColumnsMetaDataView> GetMetaData() const;`
- L80 _protected prototype_ `void RegisterQueries();`
- L81 _protected prototype_ `void UnRegisterQueries();`
- L82 _protected prototype_ `bool IsRowVisible(const RowHandle InRowHandle) const;`
- L83 _protected prototype_ `void UpdateWidgets();`
- L87 _private prototype_ `EColumnSortMode::Type GetSortMode() const;`
- L88 _private prototype_ `EColumnSortPriority::Type GetSortPriority() const;`
- L89 _private prototype_ `bool IsSorting() const;`
- L90 _private prototype_ `EVisibility GetSortTextVisibility() const;`
- L91 _private prototype_ `FText GetSortText() const;`
- L94 _private member_ `FName ColumnName;` — The ID of the column
- L97 _private member_ `IUiProvider::FWidgetConstructorPtr CellWidgetConstructor;` — Widget Constructors
- L98 _private member_ `IUiProvider::FWidgetConstructorPtr HeaderWidgetConstructor;`
- L101 _private member_ `TArray<TWeakObjectPtr<const UScriptStruct>> MatchedColumns;` — Teds Columns this widget constructor matched with
- L104 _private member_ `Queries::FConditions MatchedColumnConditions;` — The matched columns stored as a query condition for quick access
- L107 _private member_ `const FMetaData WidgetMetaData;` — The Metadata used to create widgets
- L108 _private member_ `const TArray<TSharedPtr<FColumnMetaData>> ColumnMetaData;`
- L111 _private member_ `ICoreProvider* Storage;` — TEDS Constructs
- L112 _private member_ `IUiProvider* StorageUi;`
- L113 _private member_ `ICompatibilityProvider* StorageCompatibility;`
- L116 _private member_ `TArray<QueryHandle> InternalObserverQueries;` — Queries used to virtualize widgets when a column is added to/remove from a row
- L117 _private member_ `QueryHandle WidgetQuery;`
- L118 _private member_ `TMap<RowHandle, bool> RowsToUpdate;`
- L120 _private member_ `TArray<TSharedPtr<const FColumnSearcherInterface>> ColumnSearchers;`
- L123 _private member_ `TArray<TSharedPtr<const FColumnSorterInterface>> ColumnSorters;` — Sorting information
- L124 _private member_ `FSortHandler SortDelegates;`
- L125 _private member_ `FText SorterShortName;`
- L126 _private member_ `uint32 ColumnSorterIndex = 0;`
- L127 _private member_ `EColumnSortMode::Type InitialSortMode = EColumnSortMode::Ascending;`
- L128 _private member_ `EColumnSortPriority::Type SortPriority = EColumnSortPriority::None;`
- L129 _private member_ `bool bIsSorted = false;`
- L132 _private member_ `FIsRowVisible IsRowVisibleDelegate;` — Delegate to check if a row is visible in the owning table viewer

#### struct `UE::Editor::DataStorage::FTedsTableViewerColumn::FSortHandler`  
`struct FSortHandler`  
_L64-68_
- L66 _public member_ `FOnSort OnSortHandler;`
- L67 _public member_ `FIsSorting IsSortingHandler;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsRowVisible, const RowHandle);` — Delegate to check if a row is currently visible in the owning table viewer's UI
- L59 _delegate_ `DECLARE_DELEGATE_FourParams(FOnSort, FName ColumnName, TSharedPtr<const FColumnSorterInterface> ColumnSorter, EColumnSortMode::Type Direction, EColumnSortPriority::Type Priority);` — Delegate triggered when a column is sorted.
- L62 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsSorting);` — Delegate triggered used to determine is sorting is in progress.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsTableViewerModel.h` (Public)


#### class `UE::Editor::DataStorage::FTedsTableViewerModel`  
`class FTedsTableViewerModel`  
_L34-186_
- desc: Model class for the TEDS Table Viewer that can be plugged into any widget that is a UI representation of data in TEDS @see STedsTableViewer
- L38 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemVisible, TableViewerItemPtr);`
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnModelChanged);`
- L54 _public prototype_ `FTedsTableViewerModel(const FArguments& Args);`
- L56 _public prototype_ `~FTedsTableViewerModel();`
- L59 _public prototype_ `const TArray<TableViewerItemPtr>& GetItems() const;` — Get the items this table viewer is viewing
- L62 _public prototype_ `uint64 GetRowCount() const;` — Get the number of rows currently being observed
- L65 _public prototype_ `uint64 GetColumnCount() const;` — Get the number of columns being displayed
- L68 _public prototype_ `TSharedPtr<FTedsTableViewerColumn> GetColumn(const FName& ColumnName) const;` — Get a specific column that the table viewer is displaying by name
- L71 _public prototype_ `int32 GetColumnIndex(const FName& ColumnName) const;` — Get the index of a column by name (INDEX_NONE if column doesn't exist)
- L74 _public prototype_ `void ForEachColumn(const TFunctionRef<void(const TSharedRef<FTedsTableViewerColumn>&)>& Delegate) const;` — Execute a delegate for each column in the model
- L77 _public prototype_ `FOnModelChanged& GetOnModelChanged();` — Delegate when the item list changes
- L80 _public prototype_ `void SetQueryStack(const TSharedPtr<QueryStack::IRowNode>& InRowQueryStack, bool bUpdateExecutor = true);` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L83 _public prototype_ `void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns);` — Clear the current list of columns being displayed and set it to the given list
- L86 _public prototype_ `void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InColumn);` — Add a custom row widget to display in the table viewer, that doesn't necessarily map to a Teds column
- L88 _public prototype_ `ICoreProvider* GetDataStorageInterface() const;`
- L90 _public prototype_ `IUiProvider* GetDataStorageUiProvider() const;`
- L93 _public prototype_ `TSharedPtr<QueryStack::IRowNode> GetRowNode() const;` — Get the bottom-most row node used in the query stack for this model
- L96 _public prototype_ `FName GetPrimaryColumnName() const;` — The FName of the primary UI column (matches the column name in the underlying slate widgets)
- L101 _protected prototype_ `void GenerateColumns();` — Generate the actual columns to display in the UI using TEDS UI
- L104 _protected prototype_ `bool IsRowVisible(RowHandle InRowHandle) const;` — Check if the given row is currently visible in the UI
- L106 _protected prototype_ `void OnSort(FName ColumnName, TSharedPtr<const FColumnSorterInterface> ColumnSorter, EColumnSortMode::Type Direction, EColumnSortPriority::Type Priority);`
- L108 _protected prototype_ `bool IsSorting() const;`
- L110 _protected prototype_ `bool Tick(float DeltaTime);`
- L112 _protected prototype_ `void Refresh();`
- L114 _protected prototype_ `void ValidateRequestedColumns();`
- L119 _private member_ `TSharedPtr<QueryStack::IRowNode> RowQueryStack;` — The row query stack used to supply the rows to display
- L122 _private member_ `QueryStack::FExplicitUpdateExecutor QueryStackExecutor;` — The executor used to update the RowQueryStack.
- L125 _private member_ `TSharedPtr<QueryStack::FRowSortNode> RowPrimarySortingNode;` — Row node used to sort the rows in the query stack.
- L128 _private member_ `TSharedPtr<QueryStack::FRowSortNode> RowSecondarySortingNode;` — Row node used as a backup to sort the rows in the query stack. Users can hold down shift to setup a secondary sort. As a result any duplicates from the the primary sorting node will be sorted by the secondary sort.
- L131 _private member_ `TSharedPtr<QueryStack::FRowOrderInversionNode> RowPrimaryInversionNode;` — Inverts the rows from the query stack when needed by the primary sort.
- L133 _private member_ `TSharedPtr<QueryStack::FRowOrderInversionNode> RowSecondaryInversionNode;` — Inverts the rows from the query stack when needed by the primary sort.
- L136 _private member_ `FName PrimarySortColumnName;` — The name of the active primary sort column or none if not set.
- L138 _private member_ `FName SecondarySortColumnName;` — The name of the active secondary sort column or none if not set.
- L141 _private member_ `TArray<TableViewerItemPtr> Items;` — The cached list of rows we are currently displaying
- L144 _private member_ `TArray<TSharedRef<FTedsTableViewerColumn>> ColumnsView;` — List of columns the table viewer is currently displaying
- L147 _private member_ `TArray<TWeakObjectPtr<const UScriptStruct>> RequestedTedsColumns;` — The initial TEDS columns the widget was requested to display
- L150 _private member_ `TSharedPtr<FMetaData> GenericMetaData;` — Generic Metadata for all widgets
- L153 _private member_ `TArray<TSharedPtr<FColumnMetaData>> ColumnMetaData;` — Metadata for RequestedTedsColumns
- L156 _private member_ `IUiProvider::FPurposeID CellWidgetPurpose;` — The widget purposes used to create widgets in this table viewer
- L157 _private member_ `IUiProvider::FPurposeID HeaderWidgetPurpose;`
- L160 _private member_ `uint32 CachedRowQueryStackRevision = QueryStack::INode::UninitializedRevisionId;` — Cached revision ID for the query stack used to check when the table viewer needs a refresh
- L163 _private member_ `FIsItemVisible IsItemVisible;` — Delegate supplied by the widget to check if an item is visible in the UI currently
- L165 _private member_ `FTSTicker::FDelegateHandle TickerHandle;`
- L168 _private member_ `FOnModelChanged OnModelChanged;` — Delegate executed when the row list changes
- L171 _private member_ `ICoreProvider* Storage = nullptr;` — Teds Constructs
- L172 _private member_ `IUiProvider* StorageUi = nullptr;`
- L175 _private member_ `TWeakObjectPtr<const UScriptStruct> PrimaryColumn;` — The TEDS column that was requested as primary for this viewer
- L178 _private member_ `bool bShowHiddenRows = false;` — If true, rows tagged with FHideRowFromUITag will still be displayed
- L181 _private member_ `FName PrimaryUIColumnName;` — TEDS -> UI columns is not a 1:1 mapping, so we cache the name of the UI column so widgets can query it easily
- L184 _private member_ `inline static int InstanceCounter = 0;` — Store the Instance count and the created name for use by the executor (so it can avoid recreation)
- L185 _private member_ `FName ExecutorInstanceName;`

#### struct `UE::Editor::DataStorage::FTedsTableViewerModel::FArguments`  
`struct FArguments`  
_L41-52_
- L43 _public member_ `TSharedPtr<QueryStack::IRowNode> RowQueryStack;`
- L44 _public member_ `TArray<TWeakObjectPtr<const UScriptStruct>> RequestedColumns;`
- L45 _public member_ `TSharedPtr<FMetaData> GenericMetaData;`
- L46 _public member_ `TArray<TSharedPtr<FColumnMetaData>> ColumnMetaData;`
- L47 _public member_ `IUiProvider::FPurposeID CellWidgetPurpose;`
- L48 _public member_ `IUiProvider::FPurposeID HeaderWidgetPurpose;`
- L49 _public member_ `FIsItemVisible IsItemVisibleDelegate;`
- L50 _public member_ `TWeakObjectPtr<const UScriptStruct> PrimaryColumn;`
- L51 _public member_ `bool bShowHiddenRows = false;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L30 _typedef_ `using TableViewerItemPtr = FTedsRowHandle;` (scope `UE::Editor::DataStorage`) — Typedef for an item in the table viewer
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemVisible, TableViewerItemPtr);`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnModelChanged);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsTableViewerUtils.h` (Public)


#### class `UTedsTableViewerFactory`  
`class UTedsTableViewerFactory : public UEditorDataStorageFactory`  
_L75-85_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L80 _public prototype_ `~UTedsTableViewerFactory() override = default;`
- L82 _public prototype_ `void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L83 _public prototype_ `void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L84 _public prototype_ `void RegisterHierarchies(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Editor` (scope `UE`)
- L24 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _namespace_ `namespace TableViewerUtils` (scope `UE::Editor::DataStorage`)
- L27 _delegate_ `DECLARE_DELEGATE_ThreeParams(FGetTableViewerRowMapping, const FName&, const RowHandle, FMapKey&);` — Delegate fired to get a custom row mapping for the table viewer
- L27 _prototype_ `DECLARE_DELEGATE_ThreeParams(FGetTableViewerRowMapping, const FName&, const RowHandle, FMapKey&);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Delegate fired to get a custom row mapping for the table viewer
- L29 _prototype_ `FName GetWidgetTableName();` (scope `UE::Editor::DataStorage::TableViewerUtils`)
- L33 _prototype_ `FName GetWidgetHierarchyName();` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Get the name of the widget hierarchy for table viewer widgets This hierarchy currently contains the relationship between the row containing the table viewer itself and individual cell widgets in that table viewer
- L35 _prototype_ `FName GetRowWidgetTableName();` (scope `UE::Editor::DataStorage::TableViewerUtils`)
- L38 _prototype_ `FName FindLongestMatchingName(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes, int32 DefaultNameIndex);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Find the longest matching common column name given a list of columns
- L41 _prototype_ `IUiProvider::FWidgetConstructorPtr CreateHeaderWidgetConstructor(IUiProvider& StorageUi, const FMetaDataView& InMetaData, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes, RowHandle PurposeRow);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Create a header widget constructor for the given columns
- L45 _prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> CreateVerifiedColumnTypeArray(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ColumnTypes);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Create a copy of the provided column types array after discarding invalid entries
- L48 _prototype_ `const FSlateBrush* GetIconForRow(ICoreProvider* DataStorage, RowHandle Row);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Scans the row for columns and tries to find the best matching icon.
- L51 _prototype_ `void CreateRowMappingKey(const FName& InHierarchyIdentifier, const TableViewerItemPtr InItem, FMapKey& OutMapKey);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Creates the default Row Map Key for the Table Row UI Rows
- L54 _prototype_ `void CreateRowMappingKey(const FName& InHierarchyIdentifier, const RowHandle InItem, FMapKey& OutMapKey);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Creates the default Row Map Key for the Table Row UI Rows from the RowHandle directly
- L57 _prototype_ `RowHandle GetTableViewerRowUiRow(const ICoreProvider* DataStorage, const RowHandle ChildWidgetRow);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Walks up the UI Widget Hierarchy until finding the row with the FTableViewerRowTag
- L60 _prototype_ `RowHandle GetTableViewerUiRow(const ICoreProvider* DataStorage, const RowHandle ChildWidgetRow);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Walks up the UI Widget Hierarchy until finding the row with the FTableViewerTag
- L63 _prototype_ `void RemoveAllTableViewerUIRows(ICoreProvider* DataStorage, const RowHandle TableViewerRowHandle);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Finds all the UI Rows for the provided TableViewer and removes the rows
- L66 _prototype_ `void DeactivateAllTableViewerUIRows(ICoreProvider* DataStorage, const RowHandle TableViewerRowHandle);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Finds all the UI Rows for the provided TableViewer and deactivates them (adds the FTedsTableViewerInactiveRowTag)
- L69 _prototype_ `void InitializeAllTableViewerUIRows(ICoreProvider* DataStorage, const TArray<TableViewerItemPtr>& Items, const FGetTableViewerRowMapping& GetTableViewerRowMapping, const FName& TableViewerIdentifier, const RowHandle TableViewerRowHandle, const bool bAddHierarchyTags = false);` (scope `UE::Editor::DataStorage::TableViewerUtils`) — Initializes all rows on a TableViewer for a QueryStack

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TedsTableViewerWidgetColumns.h` (Public)


#### struct `FExternalWidgetExclusiveSelectionColumn`  
`struct FExternalWidgetExclusiveSelectionColumn : public FEditorDataStorageColumn`  
_L23-34_
- reflection: `USTRUCT(meta = (DisplayName = "Widget with externally managed exclusive selection"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column added to a widget row when an external widget manages exclusive selection for the widget referenced by the row, such as an owning SListView or STreeView
- L33 _public member_ `TSharedPtr<FIsSelected> IsSelectedExclusively;` — Delegate to execute to check the status of if the widget is the only selected between multiple widgets Only needs to be hooked up if an external widget is managing selection on multiple widgets, such as a SListView or STreeView. E.g usage: Enables renaming by clicking the label twice if the widget is editable. @see SInlineEditableTextBlock::IsSelected

#### struct `FTedsTableViewerTag`  
`struct FTedsTableViewerTag : public FEditorDataStorageTag`  
_L40-43_
- reflection: `USTRUCT(meta = (DisplayName = "Table Viewer Widget Tag"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag on a UI row representing a table viewer (or hierarchy viewer)

#### struct `FTedsTableViewerReferenceColumn`  
`struct FTedsTableViewerReferenceColumn : public FEditorDataStorageColumn`  
_L49-54_
- reflection: `USTRUCT(meta = (DisplayName = "Table Viewer reference"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on table viewer row that contains a reference to the ITableViewer
- L53 _public member_ `TWeakPtr<UE::Editor::DataStorage::ITableViewer> TableViewerWeak;`

#### struct `FTedsTableViewerSelectionChangedColumn`  
`struct FTedsTableViewerSelectionChangedColumn : public FEditorDataStorageColumn`  
_L60-65_
- reflection: `USTRUCT(meta = (DisplayName = "On Table Viewer selection changed"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on the table viewer row with the delegate that executes when selection is changed
- L64 _public member_ `TSharedPtr<FSimpleMulticastDelegate> OnSelectionChanged;`

#### struct `FTedsTableViewerRenameSelectionColumn`  
`struct FTedsTableViewerRenameSelectionColumn : public FEditorDataStorageColumn`  
_L72-77_
- reflection: `USTRUCT(meta = (DisplayName = "Table Viewer rename event"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on the table viewer row with the delegate that executes to rename the selected rows TEDS UI TODO: Can we use a generic column for actions/events instead of one hardcoded for rename?
- L76 _public member_ `TSharedPtr<FSimpleMulticastDelegate> OnRenameSelection;`

#### struct `FTedsTableViewerDropInfoColumn`  
`struct FTedsTableViewerDropInfoColumn : public FEditorDataStorageColumn`  
_L83-88_
- reflection: `USTRUCT(meta = (DisplayName = "Table Viewer drop info"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on the table viewer row that contains information about an ongoing drag and drop event
- L87 _public member_ `UE::Editor::DataStorage::RowHandle DropTarget;`

#### struct `FTedsHierarchyViewerDataColumn`  
`struct FTedsHierarchyViewerDataColumn : public FEditorDataStorageColumn`  
_L98-103_
- reflection: `USTRUCT(meta = (DisplayName = "Hierarchy viewer access interface"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on widget rows that contains a weak ptr to the hierarchy data used by the hierarchy viewer to display rows (if present). This is useful if your widget is meant to be displayed in a hierarchy view and needs access to data on the visual parent of the data row or do a ForEachChild. NOTE: This contains hierarchy data about the data/target row and not the widget row. Widget hierarchies can be accessed directly by using TableViewerUtils::GetWidgetHierarchyName() to get the widget row of the parent widget.
- L102 _public member_ `TWeakPtr<UE::Editor::DataStorage::IHierarchyViewerDataInterface> HierarchyData;`

#### struct `FTedsHierarchyViewerRootColumn`  
`struct FTedsHierarchyViewerRootColumn : public FEditorDataStorageColumn`  
_L110-115_
- reflection: `USTRUCT(meta = (DisplayName = "Hierarchy Viewer root item"))`
- inherits: `FEditorDataStorageColumn`
- desc: Column on the hierarchy viewer widget row that contains the root of the tree. If there are multiple top level items, the root is the first one (taking sorting into account)
- L114 _public member_ `UE::Editor::DataStorage::RowHandle Root;`

#### struct `FTedsTableViewerRowTag`  
`struct FTedsTableViewerRowTag : public FEditorDataStorageTag`  
_L121-124_
- reflection: `USTRUCT(meta = (DisplayName = "Table Viewer Row Widget Tag"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag on a UI row representing a row in a table viewer (or hierarchy viewer)

#### struct `FTedsTableViewerInactiveRowTag`  
`struct FTedsTableViewerInactiveRowTag : public FEditorDataStorageTag`  
_L131-134_
- reflection: `USTRUCT(meta = (DisplayName = "Inactive UI"))`
- inherits: `FEditorDataStorageTag`
- desc: Tag on to indicate that this UI row is currently kept around but is not currently being used as a widget

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _variable_ `inline static const FName TableViewerUIRowMappingDomain = TEXT("Tab` (scope `UE::Editor::DataStorage`)
- L136 _namespace_ `namespace UE`
- L136 _namespace_ `namespace Editor` (scope `UE`)
- L136 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L138 _typedef_ `using FTableViewerTag = FTedsTableViewerTag;` (scope `UE::Editor::DataStorage`)
- L139 _typedef_ `using FTableViewerReferenceColumn = FTedsTableViewerReferenceColumn;` (scope `UE::Editor::DataStorage`)
- L140 _typedef_ `using FTableViewerDropInfoColumn = FTedsTableViewerDropInfoColumn;` (scope `UE::Editor::DataStorage`)
- L141 _typedef_ `using FTableViewerSelectionChangedColumn = FTedsTableViewerSelectionChangedColumn;` (scope `UE::Editor::DataStorage`)
- L142 _typedef_ `using FTableViewerRenameSelectionColumn = FTedsTableViewerRenameSelectionColumn;` (scope `UE::Editor::DataStorage`)
- L143 _typedef_ `using FHierarchyViewerDataColumn = FTedsHierarchyViewerDataColumn;` (scope `UE::Editor::DataStorage`)
- L144 _typedef_ `using FHierarchyViewerRootColumn = FTedsHierarchyViewerRootColumn;` (scope `UE::Editor::DataStorage`)
- L145 _typedef_ `using FTableViewerRowTag = FTedsTableViewerRowTag;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/TypedElementUITypes.h` (Public)


#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<FTedsRowHandle>`  
_L15-58_
- desc: Template declaration to describe how a row handle behaves as a type for slate widgets like SListView, STreeView etc This allows you to use Row Handles with slate widgets that work on pointers by using the wrapper struct e.g SListView<FTedsRowHandle>
- L17 _public typedef_ `typedef FTedsRowHandle NullableType;`
- L19 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FTedsRowHandle, TSharedRef<ITableRow>, false>;`
- L20 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FTedsRowHandle, FSparseItemInfo, false>;`
- L21 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FTedsRowHandle>;`
- L24 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FTedsRowHandle>&, TSet<FTedsRowHandle>&, TMap<const U*, FTedsRowHandle>&)`
- L31 _public function_ `static bool IsPtrValid(const FTedsRowHandle& InPtr)`
- L36 _public function_ `static void ResetPtr(FTedsRowHandle& InPtr)`
- L41 _public function_ `static FTedsRowHandle MakeNullPtr()`
- L47 _public function_ `static FTedsRowHandle NullableItemTypeConvertToItemType(const FTedsRowHandle& InPtr)`
- L52 _public function_ `static FString DebugDump(FTedsRowHandle InPtr)`
- L77 _public typedef_ `typedef FTedsTableHandle NullableType;`
- L79 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FTedsTableHandle, TSharedRef<ITableRow>, false>;`
- L80 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FTedsTableHandle, FSparseItemInfo, false>;`
- L81 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FTedsTableHandle>;`
- L84 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FTedsTableHandle>&, TSet<FTedsTableHandle>&, TMap<const U*, FTedsTableHandle>&)`
- L91 _public function_ `static bool IsPtrValid(const FTedsTableHandle& InPtr)`
- L96 _public function_ `static void ResetPtr(FTedsTableHandle& InPtr)`
- L101 _public function_ `static FTedsTableHandle MakeNullPtr()`
- L107 _public function_ `static FTedsTableHandle NullableItemTypeConvertToItemType(const FTedsTableHandle& InPtr)`
- L112 _public function_ `static FString DebugDump(FTedsTableHandle InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L57-57_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<FTedsRowHandle>`  
_L62-68_
- desc: Template declaration to enable using row handles inside of slate widgets like SListView

#### enum `TIsValidListItem::(anonymous)`  
``  
_L65-67_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<FTedsTableHandle>`  
_L75-118_
- desc: Template declaration to describe how a table handle behaves as a type for slate widgets like SListView, STreeView etc This allows you to use Table Handles with slate widgets that would otherwise only work on pointers by using the wrapper struct e.g STreeView<FTedsTableHandle>
- L17 _public typedef_ `typedef FTedsRowHandle NullableType;`
- L19 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FTedsRowHandle, TSharedRef<ITableRow>, false>;`
- L20 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FTedsRowHandle, FSparseItemInfo, false>;`
- L21 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FTedsRowHandle>;`
- L24 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FTedsRowHandle>&, TSet<FTedsRowHandle>&, TMap<const U*, FTedsRowHandle>&)`
- L31 _public function_ `static bool IsPtrValid(const FTedsRowHandle& InPtr)`
- L36 _public function_ `static void ResetPtr(FTedsRowHandle& InPtr)`
- L41 _public function_ `static FTedsRowHandle MakeNullPtr()`
- L47 _public function_ `static FTedsRowHandle NullableItemTypeConvertToItemType(const FTedsRowHandle& InPtr)`
- L52 _public function_ `static FString DebugDump(FTedsRowHandle InPtr)`
- L77 _public typedef_ `typedef FTedsTableHandle NullableType;`
- L79 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FTedsTableHandle, TSharedRef<ITableRow>, false>;`
- L80 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FTedsTableHandle, FSparseItemInfo, false>;`
- L81 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FTedsTableHandle>;`
- L84 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector&, TArray<FTedsTableHandle>&, TSet<FTedsTableHandle>&, TMap<const U*, FTedsTableHandle>&)`
- L91 _public function_ `static bool IsPtrValid(const FTedsTableHandle& InPtr)`
- L96 _public function_ `static void ResetPtr(FTedsTableHandle& InPtr)`
- L101 _public function_ `static FTedsTableHandle MakeNullPtr()`
- L107 _public function_ `static FTedsTableHandle NullableItemTypeConvertToItemType(const FTedsTableHandle& InPtr)`
- L112 _public function_ `static FString DebugDump(FTedsTableHandle InPtr)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L117-117_

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<FTedsTableHandle>`  
_L122-128_
- desc: Template declaration to enable using table handles inside of slate widgets like STreeView

#### enum `TIsValidListItem::(anonymous)`  
``  
_L125-127_

#### Free symbols / members of external scopes

- L66 _enumerator_ `Value = true` (scope `TIsValidListItem::__anond399d2080103`)
- L126 _enumerator_ `Value = true` (scope `TIsValidListItem::__anond399d2080203`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/Composite/STedsCompositeHierarchyViewer.h` (Public)


#### class `UE::Editor::DataStorage::FTedsCompositeHierarchyViewerOption`  
`class FTedsCompositeHierarchyViewerOption : public TSharedFromThis<FTedsCompositeHierarchyViewerOption>`  
_L25-55_
- inherits: `TSharedFromThis<FTedsCompositeHierarchyViewerOption>`
- desc: A class corresponding to one boolean option (e.g. "Show Components"). An array of these objects can be passed into the STedsCompositeHierarchyViewer and it will auto-populate a menu containing toggle buttons for each object.
- L34 _public prototype_ `FTedsCompositeHierarchyViewerOption(const FText& InSettingTitle, const FText& InSettingTitleToolTip, EOptionCategories InOptionCategory, bool bInActive);`
- L36 _public prototype_ `bool IsActive() const;`
- L38 _public prototype_ `void ToggleIsActive();`
- L40 _public prototype_ `void AddMenu(FMenuBuilder& InMenuBuilder);`
- L42 _public prototype_ `EOptionCategories GetCategory() const;`
- L44 _public prototype_ `DECLARE_EVENT_OneParam(FTedsCompositeHierarchyViewerOption, FOnToggle, bool);`
- L45 _public function_ `FOnToggle& OnToggle()`
- L49 _private member_ `FText OptionTitle;`
- L50 _private member_ `FText OptionToolTip;`
- L51 _private member_ `EOptionCategories OptionCategory;`
- L52 _private member_ `bool bActive;`
- L54 _private member_ `FOnToggle OnToggleEvent;`

#### enum `UE::Editor::DataStorage::FTedsCompositeHierarchyViewerOption::EOptionCategories`  
`enum class EOptionCategories`  
_L28-32_
- L30 _public enumerator_ `Hierarchy`
- L31 _public enumerator_ `Show`

#### class `UE::Editor::DataStorage::STedsCompositeHierarchyViewer`  
`class STedsCompositeHierarchyViewer : public SCompoundWidget, public ITableViewer`  
_L71-215_
- inherits: `SCompoundWidget,ITableViewer`
- desc: A hierarchy viewer widget can be used to show a visual representation of data in TEDS. This composite widget adds features in a 'default' layout such as searching and filtering. The rows to display can be specified using a RowQueryStack, and the columns to display are directly input into the widget Example usage: SNew(STedsCompositeHierarchyViewer, HierarchyData) // Filtering and Searching enabled by default .HierarchyViewerArgs(SHierarchyViewer::FArguments() .AllNodeProvider(FilterNode) .Columns({ FTypedElementLabelColumn::StaticStruct(), FTypedElementClassTypeInfoColumn::StaticStruct() }) .CellWidgetPurpose(PurposeId) .Filters(MyCustomFilterArray);
- L75 _public function_ `SLATE_BEGIN_ARGS(STedsCompositeHierarchyViewer) : _HierarchyViewerArgs() , _EnableSearching(true) , _EnableFiltering(true) , _EnableSettings(true) , _UseSectionsForCategories(false) , _ShowFilteredParentHierarchy(true)`
- L116 _protected prototype_ `virtual void SetQueryStack(TSharedPtr<QueryStack::IRowNode> InRowQueryStack) override;` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L120 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<IHierarchyViewerDataInterface> InHierarchyInterface);`
- L123 _public prototype_ `virtual void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns) override;` — Clear the current list of columns being displayed and set it to the given list
- L126 _public prototype_ `void SetTableViewerIdentifier(const FName& NewIdentifier);` — Sets the TableViewer/Hierarchy Identifier (Can be used in case data is dynamic and created post widget init)
- L130 _public prototype_ `virtual void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InColumn) override;` — Add a custom per-row widget to the table viewer (that doesn't necessarily map to a TEDS column) This means a new column for the table viewer
- L133 _public prototype_ `virtual void ForEachSelectedRow(TFunctionRef<void(RowHandle)> InCallback) const override;` — Execute the given callback for each row that is selected in the table viewer
- L136 _public prototype_ `virtual RowHandle GetWidgetRowHandle() const override;` — Get the row handle for the widget row the table viewer's contents are stored in
- L139 _public prototype_ `virtual void SetSelection(RowHandle Row, bool bSelected, const ESelectInfo::Type SelectInfo) const override;` — Select the given row in the table viewer
- L142 _public prototype_ `virtual void ScrollIntoView(RowHandle Row) const override;` — Scroll the given row into view in the table viewer
- L144 _public prototype_ `virtual void ClearSelection() const override;`
- L146 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L148 _public prototype_ `virtual bool IsSelected(RowHandle InRow) const override;`
- L150 _public prototype_ `virtual bool IsSelectedExclusively(RowHandle InRow) const override;`
- L152 _public prototype_ `void AddFilter(const TSharedPtr<FTedsFilter> InFilter) const;`
- L154 _public prototype_ `void AddFilters(const TArray<TSharedPtr<FTedsFilter>>& InFilters) const;`
- L156 _public prototype_ `void DeleteFilter(const FName& InFilterName) const;`
- L158 _public prototype_ `void DeleteAllFilters() const;`
- L160 _public prototype_ `void SetCommonFilters(const TArray<FName>& InFilters) const;`
- L162 _public prototype_ `void ReplaceFilters(const TArray<TSharedPtr<FTedsFilter>>& InFilters, const bool bPersistFilterStates = true) const;`
- L165 _public prototype_ `void ExpandAll() const;` — Recursively Expand all rows currently present in the viewer
- L168 _public prototype_ `void CollapseAll() const;` — Recursively Collapse all rows currently present in the viewer
- L171 _public prototype_ `void ExpandWithParents(RowHandle Row);` — Expand this row, and all its parents
- L174 _public prototype_ `void OnToggleShowFilteredParentHierarchy();` — Menu actions
- L175 _public prototype_ `void OnToggleExpandNewRows();`
- L178 _public prototype_ `void SetDropHandler(TUniquePtr<FWidgetDropHandler> InDropHandler);` — Set a handler that this viewer will forward its drop operations to.
- L181 _private prototype_ `void AddFilteredParentRowsToQueryStack(TSharedPtr<QueryStack::IRowNode>* QueryStack, const TSharedPtr<IHierarchyViewerDataInterface>& HierarchyInterface);`
- L184 _private prototype_ `TSharedRef<SWidget> GetSettingsButtonContent();` — Build a menu of Toggle Buttons from the ShowOptions objects
- L187 _private member_ `TArray<TSharedPtr<FTedsCompositeHierarchyViewerOption>> Options;` — Option objects used to construct the settings menu
- L190 _private member_ `bool bShowFilteredOutParentHierarchy = true;` — Whether to add back the filtered out parent hierarchy (removed from searching or filtering)
- L193 _private member_ `TSharedPtr<QueryStack::IRowNode> QueryNode;` — Original Row Node given as the AllNodeProvider of the HierarchyViewer
- L196 _private member_ `TSharedPtr<QueryStack::IRowNode> CompositeQueryNode;` — Final Composite Row Node given to the Hierarchy Viewer
- L199 _private member_ `TSharedPtr<QueryStack::IRowNode> SearchNode;` — Row Node passed to the SearchBox that receives the searched result
- L202 _private member_ `TSharedPtr<QueryStack::IRowNode> FilterNode;` — Row Node passed to the FilterBar that receives the filtered result
- L205 _private member_ `TSharedPtr<STedsSearchBox> SearchBox;` — The search box widget
- L208 _private member_ `TSharedPtr<STedsFilterBar> FilterBar;` — The filter bar widget (uses MakeAddFilterButton to create the menu dropdown)
- L211 _private member_ `TSharedPtr<SComboButton> SettingsComboButton;` — Button used to bring up the settings menu
- L214 _private member_ `TSharedPtr<SHierarchyViewer> HierarchyViewer;` — The actual HierarchyViewer widget that displays the rows

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L44 _delegate_ `DECLARE_EVENT_OneParam(FTedsCompositeHierarchyViewerOption, FOnToggle, bool);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/RowForeignKeyWidget.h` (Public)


#### class `URowForeignKeyWidgetFactory`  
`class URowForeignKeyWidgetFactory : public UEditorDataStorageFactory`  
_L26-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `virtual ~URowForeignKeyWidgetFactory() override = default;`
- L33 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L36 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FRowForeignKeyWidgetConstructor`  
`struct FRowForeignKeyWidgetConstructor : public FTypedElementWidgetConstructor`  
_L41-59_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- desc: A custom widget to display the row ForeignKey of a row as text
- L46 _public prototype_ `FRowForeignKeyWidgetConstructor();`
- L47 _public prototype_ `virtual ~FRowForeignKeyWidgetConstructor() override = default;`
- L50 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L51 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`
- L57 _protected prototype_ `virtual FText CreateWidgetDisplayNameText(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace Ui` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/RowHandleWidget.h` (Public)


#### class `UE::Editor::DataStorage::FRowHandleSorter`  
`class FRowHandleSorter final : public FColumnSorterInterface`  
_L22-29_
- inherits: `FColumnSorterInterface`
- L25 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L26 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L27 _public prototype_ `virtual ESortType GetSortType() const override;`
- L28 _public prototype_ `virtual FText GetShortName() const override;`

#### class `URowHandleWidgetFactory`  
`class URowHandleWidgetFactory : public UEditorDataStorageFactory`  
_L33-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorDataStorageFactory`
- L38 _public prototype_ `virtual ~URowHandleWidgetFactory() override = default;`
- L40 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L43 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FRowHandleWidgetConstructor`  
`struct FRowHandleWidgetConstructor : public FTypedElementWidgetConstructor`  
_L48-71_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- desc: A custom widget to display the row handle of a row as text
- L53 _public prototype_ `FRowHandleWidgetConstructor();`
- L54 _public prototype_ `virtual ~FRowHandleWidgetConstructor() override = default;`
- L57 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L58 _protected prototype_ `virtual bool FinalizeWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`
- L64 _protected prototype_ `virtual FText CreateWidgetDisplayNameText(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L67 _protected prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/SRowDetails.h` (Public)


#### struct `UE::Editor::DataStorage::FRowDetailsItem`  
`struct FRowDetailsItem`  
_L22-47_
- desc: A row in the SRowDetails widget that represents either a column or a relation on the TEDS row we are viewing
- L25 _public member_ `FName Name;` — The logical name of this item (composited from the matched columns or grabbed from the widget constructor)
- L28 _public member_ `TArray<TWeakObjectPtr<const UScriptStruct>> ColumnTypes;` — The columns this row is displaying data for (empty for relation items)
- L31 _public member_ `IUiProvider::FWidgetConstructorPtr WidgetConstructor;` — Widget for the column (null for relation items)
- L33 _public member_ `RowHandle Row = InvalidRowHandle;`
- L34 _public member_ `RowHandle WidgetRow = InvalidRowHandle;`
- L37 _public member_ `RowHandle RelatedRow = InvalidRowHandle;` — For relation items: the related row to navigate to (InvalidRowHandle for column items)
- L39 _public function_ `bool IsRelationItem() const`
- L42 _public prototype_ `FRowDetailsItem(const FName& InItemName, const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumnTypes, IUiProvider::FWidgetConstructorPtr InWidgetConstructor, RowHandle InRow);` — Constructor for column items
- L46 _public prototype_ `FRowDetailsItem(const FName& InRelationName, RowHandle InRow, RowHandle InRelatedRow);` — Constructor for relation items

#### class `UE::Editor::DataStorage::SRowDetails`  
`class SRowDetails : public SCompoundWidget`  
_L52-133_
- inherits: `SCompoundWidget`
- desc: A widget to display all the columns/tags on a given row
- L55 _public member_ `static const FName NameColumn;`
- L56 _public member_ `static const FName DataColumn;`
- L58 _public prototype_ `~SRowDetails() override = default;`
- L60 _public function_ `SLATE_BEGIN_ARGS(SRowDetails) : _ShowUnpopulatedColumns(false) , _ShowAllDetails(true) , _SelectionMode(ESelectionMode::Multi)`
- L67 _public prototype_ `SLATE_ARGUMENT(TArray<TWeakObjectPtr<const UScriptStruct>>, Columns)` — List of Columns to show in order. Leave blank to automatically find all matching columns.
- L98 _public prototype_ `void SetRow(RowHandle Row);` — Set the row to view
- L101 _public prototype_ `void ClearRow();` — Clear the row to view
- L104 _public prototype_ `void NotifyRelatedRowSelected(RowHandle Row);` — Called by SRowDetailsRow to fire the OnRelatedRowSelected delegate
- L106 _public function_ `ICoreProvider* GetDataStorage() const`
- L107 _public function_ `IUiProvider* GetDataStorageUi() const`
- L108 _public function_ `const TSharedPtr<FMetaData>& GetNameMetaData() const`
- L109 _public function_ `const TSharedPtr<FMetaData>& GetDataMetaData() const`
- L110 _public function_ `const TArray<TSharedPtr<FColumnMetaData>>& GetColumnMetaData() const`
- L113 _private prototype_ `TSharedRef<ITableRow> CreateRow(RowDetailsItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L114 _private prototype_ `bool HasItem(const FName& ItemName) const;`
- L116 _private member_ `TArray<TWeakObjectPtr<const UScriptStruct>> RequestedTedsColumns;`
- L117 _private member_ `TSharedPtr<SListView<RowDetailsItemPtr>> ListView;`
- L118 _private member_ `TArray<RowDetailsItemPtr> Items;`
- L120 _private member_ `ICoreProvider* DataStorage = nullptr;`
- L121 _private member_ `IUiProvider* DataStorageUi = nullptr;`
- L123 _private member_ `IUiProvider::FPurposeID WidgetPurpose;`
- L125 _private member_ `TSharedPtr<FMetaData> NameMetaData;`
- L126 _private member_ `TSharedPtr<FMetaData> DataMetaData;`
- L127 _private member_ `TArray<TSharedPtr<FColumnMetaData>> ColumnMetaData;`
- L128 _private member_ `TAttribute<FMargin> RowPadding;`
- L129 _private member_ `bool bShowAllDetails = true;`
- L130 _private member_ `bool bShowUnpopulatedColumns = false;`
- L132 _private member_ `FOnRelatedRowSelected OnRelatedRowSelectedDelegate;`

#### class `UE::Editor::DataStorage::SRowDetailsRow`  
`class SRowDetailsRow : public SMultiColumnTableRow<RowDetailsItemPtr>`  
_L135-153_
- inherits: `SMultiColumnTableRow<RowDetailsItemPtr>`
- L139 _public function_ `SLATE_BEGIN_ARGS(SRowDetailsRow)`
- L141 _public prototype_ `SLATE_ARGUMENT(RowDetailsItemPtr, Item)`
- L148 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L151 _private member_ `RowDetailsItemPtr Item;`
- L152 _private member_ `TWeakPtr<SRowDetails> OwnerRowDetails;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRelatedRowSelected, RowHandle);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRelatedRowSelected, RowHandle);` (scope `UE::Editor::DataStorage`)
- L49 _typedef_ `using RowDetailsItemPtr = TSharedPtr<FRowDetailsItem>;` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/SRowDetailsNavigator.h` (Public)


#### class `UE::Editor::DataStorage::SRowDetailsNavigator`  
`class SRowDetailsNavigator : public SCompoundWidget`  
_L20-51_
- inherits: `SCompoundWidget`
- desc: Composite widget: breadcrumb trail + a stack of SRowDetails panels. Navigating to a related row pushes a new panel; clicking a breadcrumb pops back.
- L24 _public function_ `SLATE_BEGIN_ARGS(SRowDetailsNavigator)`
- L25 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `void SetRow(RowHandle Row);` — Reset the stack and show details for this row.
- L33 _public prototype_ `void ClearRow();` — Clear everything.
- L37 _private prototype_ `void NavigateTo(RowHandle Row);` — Push a new panel for the given row.
- L40 _private prototype_ `void OnBreadcrumbClicked(const RowHandle& Row);` — Called when a breadcrumb is clicked; pops panels beyond that point.
- L43 _private prototype_ `TSharedRef<SRowDetails> CreatePanel();` — Create a new SRowDetails wired to NavigateTo.
- L46 _private prototype_ `void TruncateStack(int32 KeepCount);` — Remove all panels from index onward.
- L48 _private member_ `TSharedPtr<SBreadcrumbTrail<RowHandle>> Breadcrumbs;`
- L49 _private member_ `TSharedPtr<SWidgetSwitcher> PanelSwitcher;`
- L50 _private member_ `TArray<TSharedPtr<SRowDetails>> PanelStack;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsFilterBar.h` (Public)


#### class `UE::Editor::DataStorage::STedsFilterBar`  
`class STedsFilterBar : public SBasicFilterBar<FTedsRowHandle&>`  
_L31-171_
- inherits: `SBasicFilterBar<FTedsRowHandle&>`
- desc: A Basic TEDS Filter Bar widget, which can be used to filter items of type FTedsRowHandle given a list of custom filters NOTE: The filter functions create copies, so you want to use a reference or pointer as the template type when possible Sample Usage: SAssignNew(MyFilterBar, STedsFilterBar) .InFilterableRowNode(QueryStack) .OutFilteredNode(&MyOutNode) .Filters(MyCustomFilters) // An array of filters available to this FilterBar Use MakeAddFilterButton() to make the button that summons the dropdown showing all the filters
- L33 _private typedef_ `using FOnFilterChanged = typename SBasicFilterBar<FTedsRowHandle&>::FOnFilterChanged;`
- L34 _private prototype_ `DECLARE_DELEGATE(FOnPostFiltersChanged);`
- L37 _public function_ `SLATE_BEGIN_ARGS(STedsFilterBar) : _FilterBarIdentifier(NAME_None) , _FilterBarLayout(EFilterBarLayout::Horizontal) , _FilterPillStyle(EFilterPillStyle::Basic) , _UseSectionsForCategories(false)`
- L45 _public prototype_ `SLATE_ARGUMENT(FName, FilterBarIdentifier) SLATE_ARGUMENT(TSharedPtr<QueryStack::IRowNode>, InFilterableRowNode) SLATE_ARGUMENT(TSharedPtr<QueryStack::IRowNode>*, OutFilteredNode) SLATE_ARGUMENT(TArray<TSharedPtr<FTedsFilter>>, Filters) SLATE_ARGUMENT(TArray<FName>, CommonSectionFilters) SLATE_EVENT(FOnFilterChanged, OnFilterChanged) SLATE_EVENT(FOnPostFiltersChanged, OnPostFiltersChanged) SLATE_ARGUMENT(EFilterBarLayout, FilterBarLayout) SLATE_ARGUMENT(EFilterPillStyle, FilterPillStyle) SLATE_ARGUMENT(bool, UseSectionsForCategories) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — A unique identifier for this filter bar needed to enable saving settings in the config file
- L80 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Override tick so that filters are only recompiled once if multiple were added at once
- L83 _public prototype_ `TSharedPtr<FTedsFilter> AddFilter(const TSharedPtr<FTedsFilter> InFilter);` — Add a new Filter to the menu post-initialization, will overwrite any filters with the same name
- L85 _public prototype_ `void AddFilters(const TArray<TSharedPtr<FTedsFilter>>& InFilters);` — Add an array of new Filters to the menu post-initialization, will overwrite any filters with the same name
- L87 _public prototype_ `void DeleteFilter(const FName& InFilterName);` — Remove a Filter from the menu and remove any place it may be referenced
- L89 _public prototype_ `void DeleteAllFilters();` — Remove all Filters from the menu and all references
- L91 _public prototype_ `void SetCommonFilters(const TArray<FName>& InFilters);` — Set a new array of Common filters to appear in that section
- L97 _public prototype_ `void ReplaceFilters(const TArray<TSharedPtr<FTedsFilter>>& InFilters, const bool bPersistFilterStates = true);` — Remove all filters and replace them with a new array of filters with an option to persist their state (is pinned & is active) for new filters with the same FName identifier
- L100 _public prototype_ `void AddExternalQuery(const FName& QueryName, const QueryHandle& InQueryHandle);` — Add an external query description to the FilterBar
- L101 _public prototype_ `void RemoveExternalQuery(const FName& QueryName);`
- L104 _public prototype_ `void AppendExternalQueries(DataStorage::FQueryDescription& OutQuery);` — Append all external queries into the given query description
- L107 _public prototype_ `void AddExternalQueryFunction(const FName& QueryName, const Queries::TConstQueryFunction<bool>& InQueryFunction);` — Add an external query function to the FilterBar
- L108 _public prototype_ `void RemoveExternalQueryFunction(const FName& QueryName);`
- L111 _public prototype_ `void AddClassQueryFunction(const FName& ClassName, const Queries::TConstQueryFunction<bool>& InClassQueryFunction);` — Add an external class query function to the FilterBar (uses OR)
- L112 _public prototype_ `void RemoveClassQueryFunction(const FName& ClassName);`
- L115 _protected prototype_ `void RecompileQueries();`
- L117 _protected prototype_ `virtual void PopulateAddFilterMenu(UToolMenu* InMenu);`
- L118 _protected prototype_ `virtual void PopulateCommonFilterSections(UToolMenu* InMenu);`
- L119 _protected prototype_ `virtual void PopulateCustomFilters(UToolMenu* InMenu);`
- L122 _private prototype_ `virtual TSharedRef<SWidget> MakeAddFilterMenu() override;`
- L124 _private member_ `ICoreProvider* Storage = nullptr;`
- L128 _private member_ `TArray<FName> CommonSectionFilters;` — Array of Filter FNames used to populate the 'common filters' section that filters can have a duplicate entry placed at the top of the add filter menu
- L131 _private member_ `TSharedPtr<QueryStack::IRowNode> InFilterableRowNode;` — The row node passed in as the data to filter on
- L134 _private member_ `TSharedPtr<QueryStack::IRowNode>* OutFilteredNode = nullptr;` — Pointer to the Node that is filtered and updated by the FilterBar
- L137 _private member_ `TSharedPtr<QueryStack::IRowNode> CompositeFilterNode;` — The Node responsible for compositing the final node to be given to the OutFilteredNode
- L140 _private member_ `TMap<FName, TSharedPtr<QueryStack::IQueryNode>> ExternalQueries;` — External query descriptions that are currently active (e.g Filters)
- L143 _private member_ `TMap<FName, Queries::TConstQueryFunction<bool>> ExternalQueryFunctions;` — External query functions that are currently active (e.g Filters)
- L146 _private member_ `TMap<FName, Queries::TConstQueryFunction<bool>> ClassFilters;` — External query functions used to filter by class, these are the only filters that use OR instead of AND
- L149 _private member_ `TArray<TSharedPtr<QueryStack::IRowNode>> FilterNodes;` — Array to store all filter nodes created from the active query functions
- L152 _private member_ `TArray<TSharedPtr<QueryStack::IRowNode>> ClassFilterNodes;` — Array to store all filter nodes created from the active class filters
- L155 _private member_ `TSharedPtr<QueryStack::IRowNode> CombinedRowCollectorNode;` — The query stack node responsible for collecting all rows that match the composite query on FullRefresh()
- L158 _private member_ `TSharedPtr<QueryStack::IRowNode> CombinedQueryFilterRowNode;` — The query stack node responsible for combining query filters - utilizes the repeated merge approach (AND)
- L161 _private member_ `TSharedPtr<QueryStack::IRowNode> CombinedClassFilterRowNode;` — The query stack node responsible for combining class filters - utilizes the unique merge approach (OR)
- L164 _private member_ `FOnPostFiltersChanged OnPostFiltersChanged;` — Delegate for additional functionality to perform after the filters have been updated, performed at the end of the RecompileQueries function
- L167 _private member_ `TSharedPtr<FFilterCategory> OtherFiltersCategory;` — Default Category if the category ptr on the Filter Data is a nullptr
- L170 _private member_ `bool bMarkDirty = false;` — Responsible for seeing if a filter was added or removed so multiple recompiles aren't performed every frame

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L34 _delegate_ `DECLARE_DELEGATE(FOnPostFiltersChanged);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsHierarchyViewer.h` (Public)


#### class `UE::Editor::DataStorage::SHierarchyViewer`  
`class SHierarchyViewer : public SCompoundWidget, public ITableViewer`  
_L50-286_
- inherits: `SCompoundWidget,ITableViewer`
- desc: A table viewer widget can be used to show a visual representation of data in TEDS. The rows to display can be specified using a RowQueryStack, and the columns to display are directly input into the widget Example usage: SNew(SHierarchyViewer) .QueryStack(MakeShared<UE::Editor::DataStorage::FQueryStackNode_RowView>(&Rows)) .Columns({FTypedElementLabelColumn::StaticStruct(), FTypedElementClassTypeInfoColumn::StaticStruct());
- L64 _public function_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type) SLATE_BEGIN_ARGS(SHierarchyViewer) : _CanSelectGeneratedColumn(true) , _ListSelectionMode(ESelectionMode::Type::Single) , _PersistUIRowsOnClose(false) , _ExpandNewRows(true) , _AllowInvisibleItemSelection(false) , _ShowWires(false) , _ShowHiddenRows(false)` — Delegate fired when the selection in the table viewer changes
- L78 _public prototype_ `SLATE_ARGUMENT(FName, TableViewerIdentifier)` — Unique Name of this TableViewer (Hierarchy)
- L112 _public prototype_ `SLATE_EVENT(TableViewerUtils::FGetTableViewerRowMapping, GetCustomTableViewerRowMapping)` — Delegate called to define a custom row mapping for the Table Viewer Row Widget Rows Used in cases where you need the UI Rows to persist across RowHandle changes
- L128 _public prototype_ `SLATE_ARGUMENT(bool, ShowWires);` — Whether to show hierarchy lines visually
- L136 _public prototype_ `SHierarchyViewer();`
- L139 _public prototype_ `void Construct( const FArguments& InArgs, TSharedPtr<IHierarchyViewerDataInterface> InHierarchyInterface);`
- L144 _public prototype_ `virtual void SetQueryStack(TSharedPtr<QueryStack::IRowNode> InRowQueryStack) override;` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L147 _public prototype_ `virtual void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns) override;` — Clear the current list of columns being displayed and set it to the given list
- L150 _public prototype_ `virtual void SetTableViewerIdentifier(const FName& NewIdentifier) override;` — Sets the Table Identifier (Can be used in case data is dynamic and created post widget init)
- L154 _public prototype_ `virtual void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InColumn) override;` — Add a custom per-row widget to the table viewer (that doesn't necessarily map to a TEDS column) This means a new column for the hierarchy viewer
- L157 _public prototype_ `virtual void ForEachSelectedRow(TFunctionRef<void(RowHandle)> InCallback) const override;` — Execute the given callback for each row that is selected in the table viewer
- L160 _public prototype_ `virtual RowHandle GetWidgetRowHandle() const override;` — Get the row handle for the widget row the table viewer's contents are stored in
- L163 _public prototype_ `virtual void SetSelection(RowHandle Row, bool bSelected, const ESelectInfo::Type SelectInfo) const override;` — Select the given row in the table viewer
- L166 _public prototype_ `virtual void ScrollIntoView(RowHandle Row) const override;` — Scroll the given row into view in the table viewer
- L168 _public prototype_ `virtual void ClearSelection() const override;`
- L170 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L173 _public prototype_ `virtual bool IsSelected(RowHandle InRow) const override;` — Get if a specific row is selected
- L176 _public prototype_ `virtual bool IsSelectedExclusively(RowHandle InRow) const override;` — Get if a specific row is selected exclusively
- L179 _public prototype_ `void ExpandAll() const;` — Recursively Expand all rows currently present in the viewer
- L182 _public prototype_ `void CollapseAll() const;` — Recursively Collapse all rows currently present in the viewer
- L185 _public prototype_ `void ExpandWithParents(RowHandle Row);` — Expand this row and all its parents
- L188 _public prototype_ `void SetDropHandler(TUniquePtr<FWidgetDropHandler> InDropHandler);` — Set a handler that this viewer will forward its drop operations to.
- L192 _protected prototype_ `void GetTableViewerRowMapping(const FName& InTableViewerIdentifier, const RowHandle InRow, FMapKey& OutMapKey) const;`
- L194 _protected prototype_ `RowHandle AddOrFindTableViewerUIRow(const TableViewerItemPtr InItem) const;`
- L196 _protected prototype_ `void InitializeAllTableViewerUIRows() const;`
- L198 _protected prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TableViewerItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L200 _protected prototype_ `bool IsItemVisible(TableViewerItemPtr InItem) const;`
- L202 _protected prototype_ `void CreateInternalWidget();`
- L204 _protected prototype_ `void RefreshColumnWidgets();`
- L206 _protected prototype_ `void OnExpansionChanged(TableViewerItemPtr Item, bool bExpanded) const;`
- L208 _protected prototype_ `void OnSetExpansionRecursive(TableViewerItemPtr Item, bool bExpanded) const;`
- L210 _protected prototype_ `void OnListSelectionChanged(TableViewerItemPtr Item, ESelectInfo::Type SelectInfo);`
- L212 _protected prototype_ `void AddWidgetColumns();`
- L214 _protected prototype_ `TableViewerItemPtr GetParentRow(TableViewerItemPtr InItem) const;`
- L216 _protected prototype_ `void OnModelChanged();`
- L218 _protected prototype_ `void SetExpansionState_Internal(FRowHandleArrayView Rows, bool bExpanded) const;`
- L221 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Drag and Drop handlers
- L222 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L223 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L224 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L229 _private member_ `FName TableViewerIdentifier;` — Unique identifier for this Hierarchy
- L232 _private member_ `TSharedPtr<STedsTreeView> TreeView;` — The actual ListView widget that displays the rows
- L235 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;` — The actual header widget
- L238 _private member_ `TSharedPtr<FTedsTableViewerModel> Model;` — Our model class
- L241 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate fired when the selection changes
- L245 _private member_ `bool bPersistUIRowsOnClose = false;` — If we want to persist all Table Viewer Rows and their mapping to this table ID when the viewer is destructed (keeping them around will persist its data while the editor is open)
- L248 _private member_ `TableViewerUtils::FGetTableViewerRowMapping GetCustomTableViewerRowMapping;` — Delegate fired when getting the row mapping, will use the default 'TableId.DataRowHandle' if nothing is bound
- L251 _private member_ `TSharedPtr<ITedsWidget> TedsWidget;` — Wrapper Teds Widget around our contents so we can use Teds columns to specify behavior
- L254 _private member_ `TAttribute<FText> EmptyRowsMessage;` — The message to show in place of the table viewer when there are no rows provided by the current query stack
- L257 _private member_ `TSharedPtr<QueryStack::IRowNode> TopLevelRowsNode;` — A specialized query stack node to only contain the top level rows present in the actual query stack we are using.
- L260 _private member_ `QueryStack::FExplicitUpdateExecutor QueryStackExecutor;` — The executor used to update the hierarchy stack.
- L263 _private member_ `inline static int InstanceCounter = 0;` — Store the Instance count and the created name for use by the executor and identifier (so it can avoid recreation)
- L264 _private member_ `FName ExecutorInstanceName;`
- L267 _private member_ `TArray<TableViewerItemPtr> TopLevelRows;` — The cached list of top level rows
- L270 _private member_ `TSharedPtr<IHierarchyViewerDataInterface> HierarchyInterface;` — Hierarchy data that is used to extract information about the parent of a row
- L273 _private member_ `mutable TOptional<bool> bExpansionStateChangeRequested;` — If we need to update the expansion state of all rows the next time the model changes
- L276 _private member_ `bool bModelInitialized = false;` — If the model hasn't been initialized yet, will check during OnModelChanged and let any PostModelInitialization functions run
- L279 _private member_ `bool bExpandNewRows = true;` — If any newly viewed rows (after initialization) should be expanded by default
- L282 _private member_ `TUniquePtr<FWidgetDropHandler> DropHandler;` — Drag and Drop Handler
- L285 _private member_ `bool bShowWires = false;` — Whether to show hierarchy lines visually

#### enum `UE::Editor::DataStorage::SHierarchyViewer::EExpansionState`  
`enum class EExpansionState : uint8`  
_L56-61_
- L58 _public enumerator_ `Collapsed`
- L59 _public enumerator_ `Expanded`
- L60 _public enumerator_ `Invalid`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L25 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L30 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace Editor` (scope `UE`)
- L37 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L64 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type) SLATE_BEGIN_ARGS(SHierarchyViewer) : _CanSelectGeneratedColumn(true) , _ListSelectionMode(ESelectionMode::Type::Single) , _PersistUIRowsOnClose(false) , _ExpandNewRows(true) , _AllowInvisibleItemSelection(false) , _ShowWires(false) , _ShowHiddenRows(false) { }` — Delegate fired when the selection in the table viewer changes

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsSearchBox.h` (Public)


#### class `UE::Editor::DataStorage::STedsSearchBox`  
`class STedsSearchBox : public SCompoundWidget`  
_L25-69_
- inherits: `SCompoundWidget`
- desc: A search bar widget that can be used to search across a TEDS table viewer widget using a QueryStack Search node. Example future usage: SNew(STedsSearchBox) .OutSearchNode(&OutSearchNode) // TSharedPtr<QueryStack::IRowNode> OutSearchNode .InSearchableRowNode(ReferenceQueryResultsNode)
- L28 _public typedef_ `using ESearchableQueryFlags = QueryStack::FQuerySearchNode::ESyncActions;`
- L30 _public function_ `SLATE_BEGIN_ARGS(STedsSearchBox)`
- L36 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<QueryStack::IRowNode>, InSearchableRowNode) SLATE_ARGUMENT(TSharedPtr<QueryStack::IQueryNode>, InSearchableQueryNode) SLATE_ARGUMENT(ESearchableQueryFlags, InSearchableQueryFlags) SLATE_ARGUMENT(TSharedPtr<QueryStack::IRowNode>*, OutSearchNode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The node provider to search through. If InSearchableQueryNode is also set, this node will be ignored.
- L62 _private prototype_ `void OnTextChanged(const FText& InSearchText);`
- L67 _private member_ `> SearchNode;`
- L68 _private member_ `FText SearchText;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsTableViewer.h` (Public)


#### class `UE::Editor::DataStorage::STedsTableViewer`  
`class STedsTableViewer : public SCompoundWidget, public ITableViewer`  
_L44-230_
- inherits: `SCompoundWidget,ITableViewer`
- desc: A table viewer widget can be used to show a visual representation of data in TEDS. The rows to display can be specified using a RowQueryStack, and the columns to display are directly input into the widget Example usage: SNew(STedsTableViewer) .QueryStack(MakeShared<UE::Editor::DataStorage::FQueryStackNode_RowView>(&Rows)) .Columns({FTypedElementLabelColumn::StaticStruct(), FTypedElementClassTypeInfoColumn::StaticStruct());
- L49 _public function_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type) SLATE_BEGIN_ARGS(STedsTableViewer) : _CanSelectGeneratedColumn(true) , _ListSelectionMode(ESelectionMode::Type::Single) , _PersistUIRowsOnClose(false) , _ItemHeight() , _ItemPadding(FMargin(0.f)) , _ShowHiddenRows(false)` — Delegate fired when the selection in the table viewer changes
- L63 _public prototype_ `SLATE_ARGUMENT(FName, TableViewerIdentifier)` — Unique Name of this Table
- L118 _public prototype_ `STedsTableViewer();`
- L121 _public prototype_ `void Construct(const FArguments& InArgs);`
- L124 _public prototype_ `virtual void SetTableViewerIdentifier(const FName& NewIdentifier) override;` — Sets the Table Identifier (Can be used in case data is dynamic and created post widget init)
- L127 _public prototype_ `virtual void SetQueryStack(TSharedPtr<QueryStack::IRowNode> InRowQueryStack) override;` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L130 _public prototype_ `virtual void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns) override;` — Clear the current list of columns being displayed and set it to the given list
- L134 _public prototype_ `virtual void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InColumn) override;` — Add a custom per-row widget to the table viewer (that doesn't necessarily map to a TEDS column) This means a new column for the table viewer
- L137 _public prototype_ `virtual void ForEachSelectedRow(TFunctionRef<void(RowHandle)> InCallback) const override;` — Execute the given callback for each row that is selected in the table viewer
- L140 _public prototype_ `virtual RowHandle GetWidgetRowHandle() const override;` — Get the row handle for the widget row the table viewer's contents are stored in
- L143 _public prototype_ `virtual void SetSelection(RowHandle Row, bool bSelected, const ESelectInfo::Type SelectInfo) const override;` — Select the given row in the table viewer
- L146 _public prototype_ `virtual void ScrollIntoView(RowHandle Row) const override;` — Scroll the given row into view in the table viewer
- L148 _public prototype_ `virtual void ClearSelection() const override;`
- L150 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L152 _public prototype_ `virtual bool IsSelected(RowHandle InRow) const override;`
- L154 _public prototype_ `virtual bool IsSelectedExclusively(RowHandle InRow) const override;`
- L157 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — Drag and Drop handlers
- L158 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L159 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L160 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L163 _public prototype_ `void SetDropHandler(TUniquePtr<FWidgetDropHandler> InDropHandler);` — Set a handler that this viewer will forward its drop operations to.
- L167 _protected prototype_ `void GetTableViewerRowMapping(const FName& InTableViewerIdentifier, const RowHandle InRow, FMapKey& OutMapKey) const;`
- L169 _protected prototype_ `RowHandle AddOrFindTableViewerUIRow(const TableViewerItemPtr InItem) const;`
- L171 _protected prototype_ `void InitializeAllTableViewerUIRows() const;`
- L173 _protected prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TableViewerItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L175 _protected prototype_ `bool IsItemVisible(TableViewerItemPtr InItem) const;`
- L177 _protected prototype_ `void CreateInternalWidget();`
- L179 _protected prototype_ `void RefreshColumnWidgets();`
- L181 _protected prototype_ `void OnListSelectionChanged(TableViewerItemPtr Item, ESelectInfo::Type SelectInfo);`
- L183 _protected prototype_ `void AddWidgetColumns();`
- L185 _protected prototype_ `void OnModelChanged();`
- L189 _private member_ `FName TableViewerIdentifier;` — Unique identifier for this TableViewer
- L192 _private member_ `TAttribute<float> ItemHeight;` — The actual height of each item
- L195 _private member_ `TAttribute<FMargin> ItemPadding;` — The actual padding between each item
- L198 _private member_ `TSharedPtr<SListView<TableViewerItemPtr>> ListView;` — The actual ListView widget that displays the rows
- L201 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;` — The actual header widget
- L204 _private member_ `TSharedPtr<FTedsTableViewerModel> Model;` — Our model class
- L207 _private member_ `inline static int InstanceCounter = 0;` — Store the Instance count and the created name for use by the identifier
- L210 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate fired when the selection changes
- L214 _private member_ `bool bPersistUIRowsOnClose = false;` — If we want to persist all Table Viewer Rows and their mapping to this table ID when the viewer is destructed (keeping them around will persist its data while the editor is open)
- L217 _private member_ `TableViewerUtils::FGetTableViewerRowMapping GetCustomTableViewerRowMapping;` — Delegate fired when getting the row mapping, will use the default 'TableId.DataRowHandle' if nothing is bound
- L220 _private member_ `TSharedPtr<ITedsWidget> TedsWidget;` — Wrapper Teds Widget around our contents so we can use Teds columns to specify behavior
- L223 _private member_ `TAttribute<FText> EmptyRowsMessage;` — The message to show in place of the table viewer when there are no rows provided by the current query stack
- L226 _private member_ `bool bModelInitialized = false;` — If the model hasn't been initialized yet, will check during OnModelChanged and let any PostModelInitialization functions run
- L229 _private member_ `TUniquePtr<FWidgetDropHandler> DropHandler;` — Drag and Drop Handler

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Editor` (scope `UE`)
- L31 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectionChanged, RowHandle, ESelectInfo::Type) SLATE_BEGIN_ARGS(STedsTableViewer) : _CanSelectGeneratedColumn(true) , _ListSelectionMode(ESelectionMode::Type::Single) , _PersistUIRowsOnClose(false) , _ItemHeight() , _ItemPadding(FMargin(0.f)) , _ShowHiddenRows(false) { }` — Delegate fired when the selection in the table viewer changes

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsTableViewerRow.h` (Public)


#### class `UE::Editor::DataStorage::STedsTableViewerRow`  
`class STedsTableViewerRow : public SMultiColumnTableRow< TableViewerItemPtr >`  
_L19-81_
- inherits: `SMultiColumnTableRow<TableViewerItemPtr>`
- desc: Widget that represents a row in the table viewer. Generates widgets for each column on demand.
- L25 _public function_ `SLATE_BEGIN_ARGS( STedsTableViewerRow ) : _WidgetRowHandle(InvalidRowHandle) , _TableViewerWidgetRowHandle(InvalidRowHandle) , _Padding(FMargin(0.f, 4.f)) , _ItemHeight() , _ShowWires(false)`
- L34 _public prototype_ `SLATE_ARGUMENT( TableViewerItemPtr, Item ) SLATE_ARGUMENT( RowHandle, WidgetRowHandle ) SLATE_ARGUMENT( RowHandle, TableViewerWidgetRowHandle ) SLATE_ATTRIBUTE( FMargin, Padding ) SLATE_ATTRIBUTE( float, ItemHeight ) SLATE_ARGUMENT( bool, ShowWires ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, TSharedRef<FTedsTableViewerModel> InTableViewerModel, TWeakPtr<const ITableViewer> InTableViewer);` — The list item for this row
- L57 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;` — Overridden from SMultiColumnTableRow. Generates a widget for this column of the tree row.
- L62 _protected prototype_ `void SetupWidgetColumns(ICoreProvider& InStorage, const RowHandle& InUIRowHandle);` — Add some common columns to the widget row for each cell widget created
- L66 _private prototype_ `FOptionalSize GetCurrentItemHeight() const;` — Get the current ItemHeight as an OptionalSize for the Box HeightOverride
- L69 _private prototype_ `void HandleOnDragEnter(const FDragDropEvent& DragDropEvent);` — Drag & Drop handlers
- L70 _private prototype_ `void HandleOnDragLeave(const FDragDropEvent& DragDropEvent);`
- L71 _private prototype_ `FReply HandleOnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L74 _protected member_ `TAttribute<float> ItemHeight;`
- L75 _protected member_ `RowHandle WidgetRowHandle = InvalidRowHandle;`
- L76 _protected member_ `RowHandle TableViewerWidgetRowHandle = InvalidRowHandle;`
- L77 _protected member_ `TSharedPtr<FTedsTableViewerModel> TableViewerModel;`
- L78 _protected member_ `TWeakPtr<const ITableViewer> WeakTableViewer;`
- L79 _protected member_ `TableViewerItemPtr Item;`
- L80 _protected member_ `bool bShowWires = false;`

#### class `UE::Editor::DataStorage::SHierarchyViewerRow`  
`class SHierarchyViewerRow : public STedsTableViewerRow`  
_L84-88_
- inherits: `STedsTableViewerRow`
- desc: Widget that represents a row in the hierarchy viewers. Generates widgets for each column and adds an expander arrow to the very first column.
- L87 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn( const FName& ColumnName ) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/STedsTileViewer.h` (Public)


#### class `UE::Editor::DataStorage::STedsTileViewer`  
`class STedsTileViewer : public SCompoundWidget, public ITableViewer`  
_L27-160_
- inherits: `SCompoundWidget,ITableViewer`
- desc: Table Viewer where each row is represented as a tile using STileView Unlike STedsTableViewer which takes a list of columns to display the tile viewer simply uses a single widget purpose to create tiles for each row.
- L32 _public function_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, RowHandle) SLATE_BEGIN_ARGS(STedsTileViewer) : _WidgetPurpose() , _SelectionMode(ESelectionMode::Type::Single) , _ItemHeight(128) , _ItemWidth(128) , _TileStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row")) , _TilePadding(FMargin(0.f)) , _ItemAlignment(EListItemAlignment::EvenlyDistributed) , _ShowHiddenRows(false)` — Delegate fired when the selection in the table viewer changes
- L84 _public prototype_ `void Construct(const FArguments& InArgs);`
- L87 _public prototype_ `virtual void ForEachSelectedRow(TFunctionRef<void(RowHandle)> InCallback) const override;` — Execute the given callback for each row that is selected in the table viewer
- L90 _public prototype_ `virtual RowHandle GetWidgetRowHandle() const override;` — Get the row handle for the widget row the table viewer's contents are stored in
- L93 _public prototype_ `virtual void SetSelection(RowHandle Row, bool bSelected, const ESelectInfo::Type SelectInfo) const override;` — Select the given row in the table viewer
- L96 _public prototype_ `virtual void ScrollIntoView(RowHandle Row) const override;` — Scroll the given row into view in the table viewer
- L99 _public prototype_ `virtual void ClearSelection() const override;` — Deselect all items in the table viewer
- L102 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;` — Get the table viewer as an SWidget
- L104 _public prototype_ `virtual bool IsSelected(RowHandle InRow) const override;`
- L106 _public prototype_ `virtual bool IsSelectedExclusively(RowHandle InRow) const override;`
- L109 _public prototype_ `virtual void SetTableViewerIdentifier(const FName& NewIdentifier) override;` — Sets the Table Identifier (Can be used in case data is dynamic and created post widget init)
- L112 _public prototype_ `virtual void SetQueryStack(TSharedPtr<QueryStack::IRowNode> InRowQueryStack) override;` — Clear the current QueryStack being displayed, set it to the given node, and recreate the sorting nodes
- L115 _public prototype_ `virtual void SetColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns) override;` — Clear the current list of columns being displayed and set it to the given list
- L118 _public prototype_ `virtual void AddCustomRowWidget(const TSharedRef<FTedsTableViewerColumn>& InColumn) override;` — Add a custom per-row widget to the table viewer (that doesn't necessarily map to a TEDS column)
- L122 _protected prototype_ `TSharedRef<ITableRow> MakeTileWidget(TableViewerItemPtr InItem, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L124 _protected prototype_ `bool IsItemVisible(TableViewerItemPtr InItem) const;`
- L126 _protected prototype_ `void OnListSelectionChanged(TableViewerItemPtr Item, ESelectInfo::Type SelectInfo);`
- L128 _protected prototype_ `void AddWidgetColumns();`
- L130 _protected prototype_ `void CreateTileWidgetConstructor();`
- L135 _private member_ `bool bAllowDragging = true;` — Whether dragging is allowed
- L138 _private member_ `TSharedPtr<STileView<TableViewerItemPtr>> TileView;` — The actual ListView widget that displays the rows
- L141 _private member_ `TSharedPtr<FTedsTableViewerModel> Model;` — Our model class
- L144 _private member_ `FOnSelectionChanged OnSelectionChanged;` — Delegate fired when the selection changes
- L147 _private member_ `TSharedPtr<ITedsWidget> TedsWidget;` — Wrapper Teds Widget around our contents so we can use Teds columns to specify behavior
- L150 _private member_ `IUiProvider::FPurposeID WidgetPurpose;` — The widget purpose used to generate tiles
- L153 _private member_ `TArray<TWeakObjectPtr<const UScriptStruct>> Columns;` — Optional columns to use when matching the tile widget
- L156 _private member_ `const FTableRowStyle* TableRowStyle = nullptr;` — Style name to use for the rows (tiles)
- L159 _private member_ `FMargin TilePadding;` — Padding between each tile

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, RowHandle) SLATE_BEGIN_ARGS(STedsTileViewer) : _WidgetPurpose() , _SelectionMode(ESelectionMode::Type::Single) , _ItemHeight(128) , _ItemWidth(128) , _TileStyle(&FAppStyle::Get().GetWidgetStyle<FTableRowStyle>("TableView.Row")) , _TilePadding(FMargin(0.f)) , _ItemAlignment(EListItemAlignment::EvenlyDistributed) , _ShowHiddenRows(false) { }` — Delegate fired when the selection in the table viewer changes

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/TableViewerWidgetDropHandler.h` (Public)


#### class `UE::Editor::DataStorage::Widgets::FTableViewerWidgetDropHandler`  
`class FTableViewerWidgetDropHandler : public FWidgetDropHandler`  
_L16-31_
- inherits: `FWidgetDropHandler`
- L19 _public prototype_ `FTableViewerWidgetDropHandler(TWeakPtr<ITableViewer> InTableViewer, TWeakObjectPtr<UTypedElementSelectionSet> InSelectionSet);`
- L23 _protected prototype_ `virtual EUpdateParameters UpdateParameters(ICoreProvider& Storage, const FGeometry& Geometry, const FDragDropEvent& InputEvent) override;`
- L24 _protected prototype_ `virtual void SetRowsFromParameters(ICoreProvider& Storage, FRowHandleArrayView Rows) const override;`
- L25 _protected prototype_ `virtual void Stop(ICoreProvider& Storage, UDropOperationSystem& DropSystem) override;`
- L27 _protected prototype_ `RowHandle GetDropTarget(ICoreProvider& Storage) const;`
- L29 _private member_ `TWeakPtr<ITableViewer> TableViewer;`
- L30 _private member_ `RowHandle LastTargetRow = InvalidRowHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _macro_ `#define UE_API TEDSTABLEVIEWER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Widgets` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsTableViewer/Public/Widgets/UObjectLabelWidget.h` (Public)


#### class `UUObjectLabelWidgetFactory`  
`class UUObjectLabelWidgetFactory : public UEditorDataStorageFactory`  
_L20-29_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L25 _public prototype_ `~UUObjectLabelWidgetFactory() override = default;`
- L27 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FUObjectLabelWidgetConstructor`  
`struct FUObjectLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L33-50_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget to show labels for UObjects in TEDS
- L38 _public prototype_ `FUObjectLabelWidgetConstructor();`
- L39 _public prototype_ `explicit FUObjectLabelWidgetConstructor(const UScriptStruct* TypeInfo);`
- L40 _public prototype_ `~FUObjectLabelWidgetConstructor() override = default;`
- L42 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
