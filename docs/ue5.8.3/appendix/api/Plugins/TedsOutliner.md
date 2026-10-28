# Plugins / TedsOutliner

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner`
- headers: 43; symbols: 1004
- symbol kinds: class=54, delegate=18, enum=2, enumerator=6, function=17, macro=20, member=189, namespace=130, prototype=515, struct=48, typedef=4, variable=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, InputCore, LevelEditor, LevelInstanceEditor, TedsActorCompatibility, TedsAlerts, TedsAssetData, TedsEditorCompatibility, TedsEverythingPicker, TedsOperations, TedsQueryStack, TedsTableViewer, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject, EditorConfig, EditorFramework, EditorWidgets, Engine, SceneOutliner, Slate, SlateCore, TedsTableViewer, TypedElementFramework, TypedElementRuntime

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/Compatibility/TedsSceneOutlinerItemLabelColumn.h` (Private)


#### class `FTedsSceneOutlinerItemLabelColumn`  
`class FTedsSceneOutlinerItemLabelColumn : public UE::Editor::Outliner::FTedsOutlinerUiColumn`  
_L15-25_
- inherits: `UE::Editor::Outliner::FTedsOutlinerUiColumn`
- desc: This is an override column for the TEDS Outliner/Table Viewer to display item labels for items. The label column requires that we populate additional search strings for components and construct the Label Column widget via the Tree Item so it can get the appropriate metadata (still constructs a TEDS UI Widget)
- L18 _public function_ `FTedsSceneOutlinerItemLabelColumn(UE::Editor::Outliner::FTedsOutlinerUiColumnInitParams& InitParams) : FTedsOutlinerUiColumn(InitParams)`
- L20 _public prototype_ `virtual ~FTedsSceneOutlinerItemLabelColumn() = default;`
- L22 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget( FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row ) override;`
- L24 _public prototype_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/RowMapNode.h` (Private)


#### class `UE::Editor::Outliner::FRowMapNode`  
`class FRowMapNode : public DataStorage::QueryStack::IRowNode`  
_L13-38_
- inherits: `DataStorage::QueryStack::IRowNode`
- desc: A specialized node for the Teds Outliner that stores a map from row handle to index in the parent node. This is currently required to integrate sorting with the Teds Outliner without a major refactor of the base Outliner code.
- L16 _public prototype_ `FRowMapNode(TSharedPtr<IRowNode> InParent);`
- L18 _public prototype_ `virtual ~FRowMapNode() override = default;`
- L19 _public prototype_ `virtual DataStorage::FRowHandleArrayView GetRows() const override;`
- L20 _public prototype_ `virtual DataStorage::FRowHandleArray& GetMutableRows() override;`
- L21 _public prototype_ `virtual RevisionId GetRevision() const override;`
- L22 _public prototype_ `virtual void VisitParents(ParentListCallback Callback) override;`
- L25 _public prototype_ `int32 GetRowIndex(DataStorage::RowHandle Row) const;` — Look up the index of the given row in the parent node. INDEX_NONE if not found
- L28 _protected prototype_ `virtual void Update(FTimespan AllottedTime) override;`
- L29 _protected prototype_ `void RefreshMap();`
- L34 _protected member_ `TMap<DataStorage::RowHandle, int32> RowMap;` — Map of row handle -> index in the parent array
- L35 _protected member_ `TSharedPtr<IRowNode> Parent;`
- L36 _protected member_ `RevisionId CachedParentRevision;`
- L37 _protected member_ `RevisionId Revision = 0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/TedsOutlinerColumn.h` (Private)


#### struct `UE::Editor::Outliner::FTedsOutlinerUiColumnInitParams`  
`struct FTedsOutlinerUiColumnInitParams`  
_L15-47_
- L17 _public prototype_ `FTedsOutlinerUiColumnInitParams(const DataStorage::FMetaData& InMetaData, DataStorage::ICoreProvider& InStorage, DataStorage::IUiProvider& InStorageUi, DataStorage::ICompatibilityProvider& InStorageCompatibility);`
- L21 _public member_ `DataStorage::FMetaData MetaData;` — The metadata used for this column
- L24 _public member_ `DataStorage::ICoreProvider& Storage;` — Data storage interfaces
- L25 _public member_ `DataStorage::IUiProvider& StorageUi;`
- L26 _public member_ `DataStorage::ICompatibilityProvider& StorageCompatibility;`
- L29 _public member_ `FName NameId;` — Unique ID
- L32 _public member_ `TArray<TWeakObjectPtr<const UScriptStruct>> ColumnTypes;` — TEDS UI info
- L33 _public member_ `DataStorage::IUiProvider::FWidgetConstructorPtr HeaderWidgetConstructor;`
- L34 _public member_ `DataStorage::IUiProvider::FWidgetConstructorPtr CellWidgetConstructor;`
- L37 _public member_ `TSharedPtr<ISceneOutlinerColumn> FallbackColumn;` — Fallbacks to work with legacy columns
- L38 _public member_ `FTreeItemIDDealiaser Dealiaser;`
- L39 _public member_ `bool bHybridMode = false;`
- L42 _public member_ `DataStorage::FTedsTableViewerColumn::FSortHandler SortDelegates;` — Sorting info
- L45 _public member_ `TWeakPtr<ISceneOutliner> OwningOutliner;` — Outliner refernces
- L46 _public member_ `TWeakPtr<FTedsOutlinerImpl> TedsOutlinerImpl;`

#### class `UE::Editor::Outliner::FTedsOutlinerUiColumn`  
`class FTedsOutlinerUiColumn : public ISceneOutlinerColumn`  
_L49-83_
- inherits: `ISceneOutlinerColumn`
- L53 _public prototype_ `FTedsOutlinerUiColumn(FTedsOutlinerUiColumnInitParams& InitParams);`
- L55 _public prototype_ `FName GetColumnID() override;`
- L57 _public prototype_ `virtual void Tick(double InCurrentTime, float InDeltaTime) override;`
- L58 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L59 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& RootItems, const EColumnSortMode::Type SortMode) const override;`
- L60 _public prototype_ `virtual bool SupportsSorting() const override;`
- L61 _public prototype_ `virtual void OnSortRequested(const EColumnSortPriority::Type SortPriority, const EColumnSortMode::Type InSortMode) override;`
- L62 _public prototype_ `virtual bool IsSortReady() override;`
- L63 _public prototype_ `const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L64 _public prototype_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const override;`
- L66 _public prototype_ `bool IsRowVisible(const DataStorage::RowHandle InRowHandle) const;`
- L71 _protected member_ `TUniquePtr<DataStorage::FTedsTableViewerColumn> TableViewerColumnImpl;` — The table viewer implementation that we internally use to create our widgets
- L73 _protected member_ `DataStorage::ICoreProvider& Storage;`
- L74 _protected member_ `DataStorage::IUiProvider& StorageUi;`
- L75 _protected member_ `DataStorage::ICompatibilityProvider& StorageCompatibility;`
- L76 _protected member_ `DataStorage::FMetaData MetaData;`
- L77 _protected member_ `FName NameId;`
- L78 _protected member_ `TSharedPtr<ISceneOutlinerColumn> FallbackColumn;`
- L79 _protected member_ `TWeakPtr<ISceneOutliner> OwningOutliner;`
- L80 _protected member_ `TWeakPtr<FTedsOutlinerImpl> TedsOutlinerImpl;`
- L81 _protected member_ `FTreeItemIDDealiaser Dealiaser;`
- L82 _protected member_ `bool bHybridMode;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/TedsOutlinerContextMenuHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L9 _namespace_ `namespace Helpers` (scope `UE::Editor::Outliner`)
- L13 _prototype_ `void BuildTedsOutlinerContextMenu(UToolMenu* InMenu, TWeakObjectPtr<UWorld> World);` (scope `UE::Editor::Outliner::Helpers`) — Snapshot the current outliner selection and dispatch to all registered section builders. Call this from ModifyContextMenu / AddDynamicSection in GetSceneOutlinerInitializationOptions.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/TedsOutlinerHierarchy.h` (Private)


#### class `UE::Editor::Outliner::FTedsOutlinerHierarchy`  
`class FTedsOutlinerHierarchy : public ISceneOutlinerHierarchy`  
_L19-40_
- inherits: `ISceneOutlinerHierarchy`
- desc: Class that keeps track of hierarchy data and creates items using the given TEDS queries. See CreateGenericTEDSOutliner() Inherits from ISceneOutlinerHierarchy, which is responsible for creating the items you want to populate the Outliner with and establishing hierarchical relationships between the items
- L22 _public prototype_ `FTedsOutlinerHierarchy(FTedsOutlinerMode* InMode, const TSharedRef<FTedsOutlinerImpl>& InTedsOutlinerImpl);`
- L23 _public prototype_ `virtual ~FTedsOutlinerHierarchy();`
- L26 _public prototype_ `virtual void CreateItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems) const override;` — Create a linearization of all applicable items in the hierarchy
- L28 _public prototype_ `virtual void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const override;` — Create a linearization of all direct and indirect children of a given item in the hierarchy
- L30 _public prototype_ `virtual FSceneOutlinerTreeItemPtr FindOrCreateParentItem(const ISceneOutlinerTreeItem& Item, const TMap<FSceneOutlinerTreeItemID, FSceneOutlinerTreeItemPtr>& Items, bool bCreate = false) override;` — Find or optionally create a parent item for a given tree item
- L36 _protected member_ `TSharedRef<FTedsOutlinerImpl> TedsOutlinerImpl;` — The actual model for the TEDS-Outliner
- L39 _protected member_ `FDelegateHandle HierarchyChangedHandle;` — Delegate called by TedsOutlinerImpl when the hierarchy changes

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/TedsOutlinerModeSettings.h` (Private)


#### struct `FTedsOutlinerModeConfig`  
`struct FTedsOutlinerModeConfig`  
_L16-36_
- reflection: `USTRUCT()`
- L23 _public member_ `TMap<FName, bool> ShowSettingsActive = {};` — `UPROPERTY()` — Map containing the state of the given show settings if changed from their default
- L27 _public member_ `TMap<FName, bool> OptionSettingsActive = {};` — `UPROPERTY()` — Map containing the state of the given option settings if changed from their default
- L31 _public member_ `bool bAlwaysFrameSelection = true;` — `UPROPERTY()` — True when the Scene Outliner updates when an actor is selected in the viewport
- L35 _public member_ `bool bCollapseOutlinerTreeOnNewSelection = false;` — `UPROPERTY()` — True if we want to collapse Outliner tree on new selection, except for the item that was just selected

#### class `UTedsOutlinerConfig`  
`class UTedsOutlinerConfig : public UEditorConfigBase`  
_L39-54_
- reflection: `UCLASS(EditorConfig="TedsOutlinerMode")`
- inherits: `UEditorConfigBase`
- L45 _public prototype_ `static void Initialize();`
- L46 _public function_ `static UTedsOutlinerConfig* Get()`
- L49 _public member_ `TMap<FName, FTedsOutlinerModeConfig> TedsOutliners;` — `UPROPERTY(meta=(EditorConfig))`
- L53 _private member_ `static TObjectPtr<UTedsOutlinerConfig> Instance;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/Widgets/OutlinerActorDescWidget.h` (Private)


#### class `UActorDescWidgetFactory`  
`class UActorDescWidgetFactory : public UEditorDataStorageFactory`  
_L18-27_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L23 _public prototype_ `~UActorDescWidgetFactory() override = default;`
- L25 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerActorDescIconWidgetConstructor`  
`struct FOutlinerActorDescIconWidgetConstructor : public FSimpleWidgetConstructor`  
_L31-45_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label widget for folders in the Outliner that shows an icon
- L36 _public prototype_ `FOutlinerActorDescIconWidgetConstructor();`
- L37 _public prototype_ `~FOutlinerActorDescIconWidgetConstructor() override = default;`
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerActorDescTextWidgetConstructor`  
`struct FOutlinerActorDescTextWidgetConstructor : public FSimpleWidgetConstructor`  
_L49-64_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label widget for folders in the Outliner that shows the text label
- L54 _public prototype_ `FOutlinerActorDescTextWidgetConstructor();`
- L55 _public prototype_ `~FOutlinerActorDescTextWidgetConstructor() override = default;`
- L57 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/Widgets/OutlinerFolderLabelWidget.h` (Private)


#### class `UOutlinerFolderLabelWidgetFactory`  
`class UOutlinerFolderLabelWidgetFactory : public UEditorDataStorageFactory`  
_L18-27_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L23 _public prototype_ `~UOutlinerFolderLabelWidgetFactory() override = default;`
- L25 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerFolderIconWidgetConstructor`  
`struct FOutlinerFolderIconWidgetConstructor : public FSimpleWidgetConstructor`  
_L31-45_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Icon component widget for folder rows.
- L36 _public prototype_ `FOutlinerFolderIconWidgetConstructor();`
- L37 _public prototype_ `~FOutlinerFolderIconWidgetConstructor() override = default;`
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerFolderTextWidgetConstructor`  
`struct FOutlinerFolderTextWidgetConstructor : public FSimpleWidgetConstructor`  
_L49-63_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Text component widget for folder rows. Registered to the "SceneOutliner/RowLabel/Text" sub-purpose.
- L54 _public prototype_ `FOutlinerFolderTextWidgetConstructor();`
- L55 _public prototype_ `~FOutlinerFolderTextWidgetConstructor() override = default;`
- L57 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Private/Widgets/OutlinerLabelWidget.h` (Private)


#### class `UE::Editor::DataStorage::FOutlinerLabelWidgetSorter`  
`class FOutlinerLabelWidgetSorter final : public FColumnSorterInterface`  
_L15-28_
- inherits: `FColumnSorterInterface`
- L18 _public prototype_ `virtual ESortType GetSortType() const override;`
- L20 _public prototype_ `virtual FText GetShortName() const override;`
- L22 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L24 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L27 _private prototype_ `int32 GetTypeInfoPriorityForRow(const ICoreProvider& Storage, RowHandle Row) const;`

#### class `UOutlinerLabelWidgetFactory`  
`class UOutlinerLabelWidgetFactory : public UEditorDataStorageFactory`  
_L32-43_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L37 _public prototype_ `~UOutlinerLabelWidgetFactory() override = default;`
- L39 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L42 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerLabelHeaderConstructor`  
`struct FOutlinerLabelHeaderConstructor : public FSimpleWidgetConstructor`  
_L47-66_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label header widget for the Scene Outliner
- L52 _public prototype_ `FOutlinerLabelHeaderConstructor();`
- L53 _public prototype_ `~FOutlinerLabelHeaderConstructor() override = default;`
- L55 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L62 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerLabelWidgetConstructor`  
`struct FOutlinerLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L70-87_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Label widget for the Scene Outliner that shows an icon (with optional override information) + a text label
- L75 _public prototype_ `FOutlinerLabelWidgetConstructor();`
- L76 _public prototype_ `~FOutlinerLabelWidgetConstructor() override = default;`
- L78 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L81 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Columns/TedsOutlinerColumns.h` (Public)


#### struct `FTedsOutlinerContextMenuColumn`  
`struct FTedsOutlinerContextMenuColumn final : public FEditorDataStorageColumn`  
_L46-51_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to allow context menu to be extended for an item in the outliner
- L50 _public member_ `TSharedPtr<FTedsOutlinerContextMenuDelegate> OnCreateContextMenu;`

#### struct `FTedsOutlinerColumnRefreshEventColumn`  
`struct FTedsOutlinerColumnRefreshEventColumn final : public FEditorDataStorageColumn`  
_L55-61_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to refresh information about the columns being viewed in the Teds Outliner
- L60 _public member_ `TSharedPtr<UE::Editor::Outliner::FOnRefreshColumns> OnRefreshColumns;` — Call this delegate to refresh the columns in the Teds Outliner

#### struct `FTedsOutlinerDealiaserColumn`  
`struct FTedsOutlinerDealiaserColumn final : public FEditorDataStorageColumn`  
_L65-70_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column used to store a dealiaser from outliner item -> row handle
- L69 _public member_ `UE::Editor::Outliner::FTreeItemIDDealiaser Dealiaser;`

#### struct `FTedsOutlinerSelectionChangeColumn`  
`struct FTedsOutlinerSelectionChangeColumn final : public FEditorDataStorageColumn`  
_L74-79_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column with a delegate that is broadcast when the outliner's selection changes
- L78 _public member_ `TSharedPtr<UE::Editor::Outliner::FOnTedsOutlinerSelectionChanged> OnSelectionChanged;`

#### struct `FTedsOutlinerPendingItemActionsColumn`  
`struct FTedsOutlinerPendingItemActionsColumn final : public FEditorDataStorageColumn`  
_L83-88_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column with a delegate that is broadcast to register pending item actions (select/rename/scroll) for a row
- L87 _public member_ `TSharedPtr<UE::Editor::Outliner::FOnRegisterPendingItemActions> OnRegisterPendingItemActions;`

#### struct `FTedsSceneOutlinerSettingsCacheColumn`  
`struct FTedsSceneOutlinerSettingsCacheColumn final : public FEditorDataStorageColumn`  
_L92-97_
- reflection: `USTRUCT()`
- inherits: `FEditorDataStorageColumn`
- desc: Column with a map containing boolean settings for a SceneOutliner
- L96 _public member_ `TMap<FName, bool> CachedSettings;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Editor` (scope `UE`)
- L22 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRefreshColumns, const UE::Editor::Outliner::FTedsOutlinerColumnDescription&)` — Delegate that refreshes columns on the Teds Outliner it is bound to when executed
- L25 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRefreshColumns, const UE::Editor::Outliner::FTedsOutlinerColumnDescription&)` (scope `UE::Editor::Outliner`) — Delegate that refreshes columns on the Teds Outliner it is bound to when executed
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTedsOutlinerSelectionChanged, ESelectInfo::Type)` — Delegate called when the selection in the Outliner changes. SelectInfo is Direct when the change originated outside the outliner/through code (ex: viewport), and OnMouseClick/OnKeyPress/etc when from the Outliner.
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRegisterPendingItemActions, DataStorage::RowHandle, uint8)` — Delegate broadcast to register Select/Rename/ScrollIntoView actions on a row's TreeItem the next time it is added to the tree. Item actions are a bitmask of SceneOutliner::ENewItemAction values.
- L36 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FSceneOutlinerTreeItemID, FTreeItemIDDealiaser, DataStorage::RowHandle);` — Delegate to get the TreeItemID for a row
- L39 _variable_ `inline static const FName MappingDomain = "Te` (scope `UE::Editor::Outliner`) — Mapping domain name for Outliners (kept for backward compatibility; OutlinerMappingDomain in SceneOutlinerColumns.h is the canonical source)
- L42 _delegate_ `DECLARE_DELEGATE_TwoParams(FTedsOutlinerContextMenuDelegate, UToolMenu* Menu, SSceneOutliner& SceneOutliner) USTRUCT() struct FTedsOutlinerContextMenuColumn final : public FEditorDataStorageColumn { GENERATED_BODY() TSharedPtr<FTedsOutlinerContextMenuDelegate> OnCreateContextMenu; };`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Compatibility/SceneOutlinerRowHandleColumn.h` (Public)


#### class `FSceneOutlinerRowHandleColumn`  
`class FSceneOutlinerRowHandleColumn : public ISceneOutlinerColumn`  
_L19-53_
- inherits: `ISceneOutlinerColumn`
- desc: This is a custom column for the TEDS Outliner/Table Viewer to display row handles for items. It is a special cased column instead of going through the TEDS UI layer because row handles are not information stored in a TEDS column
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UE::Editor::DataStorage::RowHandle, FGetRowHandle, const ISceneOutlinerTreeItem&);`
- L25 _public prototype_ `explicit FSceneOutlinerRowHandleColumn(ISceneOutliner& SceneOutliner);`
- L26 _public prototype_ `explicit FSceneOutlinerRowHandleColumn(ISceneOutliner& SceneOutliner, const FGetRowHandle& InGetRowHandle);`
- L28 _public prototype_ `virtual ~FSceneOutlinerRowHandleColumn() = default;`
- L30 _public prototype_ `static FName GetID();`
- L34 _public prototype_ `virtual FName GetColumnID() override;`
- L35 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L36 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row) override;`
- L37 _public prototype_ `virtual void PopulateSearchStrings( const ISceneOutlinerTreeItem& Item, TArray< FString >& OutSearchStrings ) const override;`
- L38 _public function_ `virtual bool SupportsSorting() const override`
- L39 _public prototype_ `virtual void SortItems(TArray<FSceneOutlinerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const override;`
- L45 _private prototype_ `void CreateWidgetConstructor();`
- L48 _private member_ `TWeakPtr<ISceneOutliner> WeakSceneOutliner;`
- L49 _private member_ `FGetRowHandle GetRowHandle;`
- L52 _private member_ `TSharedPtr<UE::Editor::DataStorage::FTedsTableViewerColumn> TableViewerColumn;` — The Table Viewer column we are going to use internally to create the widget

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UE::Editor::DataStorage::RowHandle, FGetRowHandle, const ISceneOutlinerTreeItem&);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Compatibility/SceneOutlinerTedsBridge.h` (Public)


#### class `USceneOutlinerTedsBridgeFactory`  
`class USceneOutlinerTedsBridgeFactory : public UEditorDataStorageFactory`  
_L25-42_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L30 _public prototype_ `~USceneOutlinerTedsBridgeFactory() override = default;`
- L32 _public prototype_ `virtual void PreRegister(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L33 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L34 _public prototype_ `virtual void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L36 _public prototype_ `FName FindOutlinerColumnFromTedsColumns(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> TEDSColumns) const;`
- L37 _public prototype_ `void RemoveTedsColumnMappingToOutlinerColumn(TWeakObjectPtr<const UScriptStruct> TEDSColumnToRemove);`
- L38 _public prototype_ `void AddTedsColumnMappingToOutlinerColumn(TWeakObjectPtr<const UScriptStruct> TEDSColumnToAdd, const FName& OutlinerColumnId);`
- L41 _protected member_ `TMap<TWeakObjectPtr<const UScriptStruct>, FName> TEDSToOutlinerDefaultColumnMapping;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Operations/DragAndDrop/ActorUtilities.h` (Public)


#### struct `UE::Editor::DataStorage::Operations::Utilities::FActorLevelPair`  
`struct FActorLevelPair`  
_L20-24_
- L22 _public member_ `AActor* Actor = nullptr;`
- L23 _public member_ `ULevel* Level = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _macro_ `#define UE_API TEDSOUTLINER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L17 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L17 _namespace_ `namespace Utilities` (scope `UE::Editor::DataStorage::Operations`)
- L27 _prototype_ `AActor* GetActorFromRow(const ICoreProvider& Storage, RowHandle Row);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the actor assigned to the given row.
- L32 _prototype_ `ULevel* GetTargetLevel(const ICoreProvider& Storage, RowHandle TargetRow);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Resolves the owning ULevel of an arbitrary drop target row.
- L35 _prototype_ `bool GetTargetActorOrLevel(FActorLevelPair& OutResult, const ICoreProvider& Storage, RowHandle InputRow, FText* OutError);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the actor and level assigned to the target column of the input row.
- L38 _prototype_ `bool GetTargetActorOrLevelWithAssetValidation(FActorLevelPair& OutResult, const ICoreProvider& Storage, RowHandle InputRow, const FAssetData& AssetData, FText* OutError);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the actor and level assigned to the target column of the input row.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Operations/DragAndDrop/AssetUtilities.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _macro_ `#define UE_API TEDSOUTLINER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L17 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L17 _namespace_ `namespace Utilities` (scope `UE::Editor::DataStorage::Operations`)
- L21 _prototype_ `UClass* GetSourceAssetClass(const ICoreProvider& Storage, RowHandle InputRow);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the asset class assigned to the source column's row of the given input row.
- L24 _prototype_ `const FAssetData* GetSourceAssetData(const ICoreProvider& Storage, RowHandle InputRow);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the asset data assigned to the source column's row of the given input row.
- L27 _prototype_ `bool AssetDataPassesFilter(TNotNull<const UObject*> TargetObject, const FAssetData& AssetData, FText* OutError);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Tests if the given asset data is allowed to be referenced by the target object.
- L30 _prototype_ `UObject* GetTargetObject(const ICoreProvider& Storage, RowHandle InputRow, FText* OutError);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the target object.
- L33 _prototype_ `UObject* GetTargetObjectWithAssetValidation(const ICoreProvider& Storage, RowHandle InputRow, const FAssetData& AssetData, FText* OutError);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Returns the target object and tests if it passes the asset filter.
- L36 _prototype_ `bool PrePlaceActorValidation(TNotNull<const UObject*> TargetObject, const FAssetData& AssetData);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Calls the LevelEditorDragDropHandler pre-place callback.
- L38 _prototype_ `void PostPlaceActorValidation(TNotNull<const UObject*> TargetObject, const FAssetData& AssetData);` (scope `UE::Editor::DataStorage::Operations::Utilities`) — Calls the LevelEditorDragDropHandler post-place callback.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Operations/DragAndDrop/RegisterDropOperations.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Operations` (scope `UE::Editor::DataStorage`)
- L16 _prototype_ `void RegisterReparentActor(ICoreProvider& Storage);` (scope `UE::Editor::DataStorage::Operations`)
- L17 _prototype_ `void RegisterReparentFolder(ICoreProvider& Storage);` (scope `UE::Editor::DataStorage::Operations`)
- L19 _function_ `inline void RegisterDropOperations(ICoreProvider& Storage)` (scope `UE::Editor::DataStorage::Operations`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Sorting/NaturalSortKey.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _prototype_ `FString BuildNaturalSortKey(FStringView Label);` (scope `UE::Editor::DataStorage`) — Builds a byte-sortable natural-order key from a label string. The returned FString has the property that byte-wise lexicographic comparison produces natural ordering (e.g. "Actor2" sorts before "Actor10"). This makes the key safe to use both as a HybridSort prefix (via TSortStringView) and in the Compare() tiebreaker, guaranteeing the two paths agree.
- L26 _prototype_ `int32 CompareNaturalSortKeys(FStringView A, FStringView B);` (scope `UE::Editor::DataStorage`) — Byte-wise compare of two BuildNaturalSortKey outputs. Unlike FString::Compare and FStringView::Compare (both null-terminated via Strcmp/Strncmp), this respects the full string length and correctly handles the embedded 0x0000 TCHARs emitted by BuildNaturalSortKey (hi-bytes of the length/zeros fields). Returns <0 if A sorts before B, >0 if after, 0 if equal. On prefix-equal inputs, the shorter key sorts first, matching UE::ComparisonUtility::CompareNaturalOrder.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerFilter.h` (Public)


#### class `UE::Editor::Outliner::FTedsOutlinerFilter`  
`class FTedsOutlinerFilter : public FTedsFilterBase<SceneOutliner::FilterBarType>`  
_L18-154_
- inherits: `FTedsFilterBase<SceneOutliner::FilterBarType>`
- L35 _public prototype_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, const QueryHandle& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false);` — Constructor for a TEDS Outliner Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterToolTip Tooltip to describe the function of the Filter @param InFilterIconName Name of an icon in the App Style Set to display in the Add Filter Menu @param InCategory Group to place the filter in the Add Filter Menu @param InFilterQuery QueryHandle of a registered query to filter for (must be the same syntax as the Outliner Query) @param bInteractiveFilter Whether this filter is visible in the Add Filter Menu and toggleable or is hidden and enabled by default @param bActiveByDefault Whether this filter should be active by default and turned on when the SceneOutliner is Init
- L46 _public prototype_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, const QueryHandle& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false);` — Constructor for a TEDS Outliner Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterQuery QueryHandle of a registered query to filter for (must be the same syntax as the Outliner Query) @param bInteractiveFilter Whether this filter is visible in the Add Filter Menu and toggleable or is hidden and enabled by default @param bActiveByDefault Whether this filter should be active by default and turned on when the SceneOutliner is Init
- L60 _public prototype_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, const TConstQueryFunction<bool>& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false);` — Constructor for a TEDS Outliner Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterToolTip Tooltip to describe the function of the Filter @param InFilterIconName Name of an icon in the App Style Set to display in the Add Filter Menu @param InCategory Group to place the filter in the Add Filter Menu @param InFilterQuery QueryFunction to filter for, Batching should be used for improved performance if possible @param bInteractiveFilter Whether this filter is visible in the Add Filter Menu and toggleable or is hidden and enabled by default @param bActiveByDefault Whether this filter should be active by default and turned on when the SceneOutliner is Init
- L71 _public prototype_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, const TConstQueryFunction<bool>& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false);` — Constructor for a TEDS Outliner Filter @param InFilterName FName Identifier of the Filter @param InFilterDisplayName Display Name to show on the Add Filter Menu and toggle button @param InFilterQuery QueryFunction to filter for, Batching should be used for improved performance if possible @param bInteractiveFilter Whether this filter is visible in the Add Filter Menu and toggleable or is hidden and enabled by default @param bActiveByDefault Whether this filter should be active by default and turned on when the SceneOutliner is Init
- L90 _public function_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, const FText& InFilterToolTip, const FName& InFilterIconName, const TSharedPtr<FFilterCategory>& InCategory, FilterFunction&& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false) : FTedsOutlinerFilter( InFilterName, InFilterDisplayName, InFilterToolTip, InFilterIconName, InCategory, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(InFilterQuery)), bInteractiveFilter, bActiveByDefault)`
- L116 _public function_ `FTedsOutlinerFilter(const FName& InFilterName, const FText& InFilterDisplayName, FilterFunction&& InFilterQuery, const bool bInteractiveFilter = true, const bool bActiveByDefault = false) : FTedsOutlinerFilter( InFilterName, InFilterDisplayName, FText::FromString(InFilterName.ToString()), FName(), nullptr, Queries::BuildConstQueryFunction<bool>(Forward<FilterFunction>(InFilterQuery)), bInteractiveFilter, bActiveByDefault)`
- L136 _public prototype_ `FTedsOutlinerFilter(const UClass* InClass, const TSharedPtr<FFilterCategory>& InCategory = nullptr, const bool bInteractiveFilter = true, const bool bActiveByDefault = false);` — Constructor for a TEDS Outliner Class Filter @param InClass UClass to filter for on the TypeInfo Column @param InCategory Group to place the filter in the Add Filter Menu @param bInteractiveFilter Whether this filter is visible in the Add Filter Menu and toggleable or is hidden and enabled by default @param bActiveByDefault Whether this filter should be active by default and turned on when the SceneOutliner is Init
- L139 _public function_ `bool IsInteractiveFilter() const`
- L142 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;` — Notification that the filter became active or inactive
- L145 _public prototype_ `virtual bool PassesFilter(SceneOutliner::FilterBarType InItem ) const override;` — Returns whether the specified Item passes the Filter's restrictions
- L149 _protected prototype_ `void SetSceneOutlinerImpl(const TSharedPtr<FTedsOutlinerImpl>& InTedsOutlinerImpl);` — Sets a SceneOutlinerImpl to be used by this Filter
- L151 _protected member_ `const bool bInteractiveFilter;`
- L153 _protected member_ `TWeakPtr<FTedsOutlinerImpl> TedsOutlinerImpl;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerFolderHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L18 _namespace_ `namespace Helpers` (scope `UE::Editor::Outliner`)
- L21 _prototype_ `void SelectDescendantActors(SSceneOutliner& Outliner, const TArray<FSceneOutlinerTreeItemPtr>& Roots, bool bSelectImmediateChildrenOnly);` (scope `UE::Editor::Outliner::Helpers`) — Selects descendant actors via a single batched GEditor selection operation.
- L24 _prototype_ `FFolder CreateFolder(DataStorage::ICoreProvider& Storage, const SSceneOutliner& Outliner, UWorld& World, const FSceneOutlinerTreeItemPtr& ParentFolder = nullptr);` (scope `UE::Editor::Outliner::Helpers`) — Creates a new folder
- L27 _prototype_ `FFolder CreateFolderForSelection(DataStorage::ICoreProvider& Storage, const SSceneOutliner& Outliner, UWorld& World, const TArray<FSceneOutlinerTreeItemPtr>& SelectedFolderItems);` (scope `UE::Editor::Outliner::Helpers`) — Creates a new folder for the current selection

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerHelpers.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L20 _namespace_ `namespace Helpers` (scope `UE::Editor::Outliner`)
- L23 _prototype_ `FSceneOutlinerTreeItemPtr GetTreeItemFromRowHandle(const DataStorage::ICoreProvider* Storage, TSharedRef<ISceneOutliner> InOutliner, DataStorage::RowHandle InRowHandle);` (scope `UE::Editor::Outliner::Helpers`) — Get the internal Outliner tree item from the row handle from the specific Outliner
- L27 _prototype_ `bool RegisterOutlinerDealiaser(DataStorage::ICoreProvider* Storage, TSharedRef<ISceneOutliner> InOutliner, const FTreeItemIDDealiaser& InDealiaser);` (scope `UE::Editor::Outliner::Helpers`) — Register a dealiaser for the given outliner, overriding any previously registered ones. Returns false if the registration failed, mostly commonly because the Outliner doesn't have a unique OutlinerIdentifier specificed
- L30 _prototype_ `FName GetTedsOutlinerTableName();` (scope `UE::Editor::Outliner::Helpers`) — Get the name of the Teds table that all Outliners are stored in
- L33 _prototype_ `void RefreshLevelEditorOutliners();` (scope `UE::Editor::Outliner::Helpers`) — Refresh all the Outliners currently open in the level editor
- L37 _prototype_ `bool OrderColumnGroup(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumnGroup, const FTedsOutlinerColumnDescription& InColumnDescription, const uint8 InDefaultStartingPriorityIndex, TMap<TWeakObjectPtr<const UScriptStruct>, uint8>& OutOrderedColumnMap);` (scope `UE::Editor::Outliner::Helpers`) — Orders a given array of Columns within the same priority group and relations defined by the ColumnDescription and returns evaluated priorities to the OutOrderedColumnMap. Returns true if the ordering was successful
- L43 _prototype_ `bool OrderColumns(const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns, const FTedsOutlinerColumnDescription& InColumnDescription, TMap<TWeakObjectPtr<const UScriptStruct>, uint8>& OutOrderedColumnMap);` (scope `UE::Editor::Outliner::Helpers`) — Orders a given array of Columns using priority groups and relations defined by the ColumnDescription and returns evaluated priorities to the OutOrderedColumnMap. Returns true if the ordering was successful
- L48 _prototype_ `TAttribute<FText> GetHighlightTextAttribute(DataStorage::ICoreProvider* DataStorage, DataStorage::RowHandle WidgetRow);` (scope `UE::Editor::Outliner::Helpers`) — Returns a TAttribute<FText> bound to FHighlightTextColumn on the parent table viewer row. Returns an empty FText attribute if the column is not present (safe no-op in non-outliner contexts).
- L51 _prototype_ `FName FindOutlinerColumnFromTedsColumns(const DataStorage::ICoreProvider* Storage, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> TEDSColumns);` (scope `UE::Editor::Outliner::Helpers`) — Get the name of the Outliner column corresponding to the given TEDS column (if any)
- L54 _prototype_ `void RemoveTedsColumnMappingToOutlinerColumn(DataStorage::ICoreProvider* Storage, TWeakObjectPtr<const UScriptStruct> TEDSColumnToRemove);` (scope `UE::Editor::Outliner::Helpers`) — Remove a Teds Column from the TEDSToOutlinerDefaultColumnMapping
- L56 _prototype_ `void AddTedsColumnMappingToOutlinerColumn(DataStorage::ICoreProvider* Storage, TWeakObjectPtr<const UScriptStruct> TEDSColumnToAdd, const FName& OutlinerColumnId);` (scope `UE::Editor::Outliner::Helpers`) — Add a Teds Column to the TEDSToOutlinerDefaultColumnMapping
- L59 _prototype_ `bool CheckValidFilterQueryHandle(const DataStorage::QueryHandle& InQueryHandle);` (scope `UE::Editor::Outliner::Helpers`) — Helper function to check if the given QueryHandle is valid to be used in a filter (is not an observer).
- L64 _prototype_ `void ConvertLegacyFiltersToTedsFilters(FSceneOutlinerFilterBarOptions& LegacyFilters, TArray<TSharedPtr<FTedsOutlinerFilter>>& TedsFilters, const TMap<FName, TVariant<DataStorage::QueryHandle, DataStorage::Queries::TConstQueryFunction<bool>>>& FilterConversionMap, TMap<FName, TArray<TSharedPtr<FFilterCategory>>>& OutTypeFilterCategoryMap);` (scope `UE::Editor::Outliner::Helpers`) — Helper function to convert legacy filters to Teds counterparts. All class filters will be automatically converted, any custom filters will need to have a mapped filter function counterpart to be converted successfully. OutFilterCategoryMap is populated with the additional categories for class filters that belonged to multiple categories in the legacy system.
- L69 _prototype_ `TAttribute<FSlateColor> GetLabelWidgetForegroundColor(TNotNull<DataStorage::ICoreProvider*> DataStorage, DataStorage::RowHandle DataRow, DataStorage::RowHandle WidgetRow);` (scope `UE::Editor::Outliner::Helpers`) — Helper function to get the Outliner Display color for a text/icon item label widget
- L73 _prototype_ `DataStorage::RowHandle GetRowHandleFromOutlinerItem(DataStorage::ICoreProvider& DataStorage, const DataStorage::ICompatibilityProvider& Compatibility, const DataStorage::RowHandle OutlinerRow, const ISceneOutlinerTreeItem& Item);` (scope `UE::Editor::Outliner::Helpers`) — Helper function to resolve the row handle from a SceneOutlinerTreeItem
- L76 _namespace_ `namespace LevelInstance` (scope `UE::Editor::Outliner::Helpers`)
- L81 _prototype_ `DataStorage::RowHandle FindContainingLevelInstanceRow(const DataStorage::ICoreProvider* DataStorage, DataStorage::RowHandle InRow);` (scope `UE::Editor::Outliner::Helpers::LevelInstance`) — Walk the EditorObjectHierarchy ancestors of InRow until a row carrying FLevelInstanceTag is found
- L86 _prototype_ `bool IsInEditingLevelInstanceHierarchy(const DataStorage::ICoreProvider* DataStorage, DataStorage::RowHandle InRow);` (scope `UE::Editor::Outliner::Helpers::LevelInstance`) — Returns true if any EditorObjectHierarchy ancestor of InRow carries FLevelInstanceEditingColumn

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerHierarchyInterfaces.h` (Public)


#### class `UE::Editor::Outliner::ITedsOutlinerHierarchyDataInterface`  
`class ITedsOutlinerHierarchyDataInterface : public DataStorage::IHierarchyViewerDataInterface`  
_L17-42_
- inherits: `DataStorage::IHierarchyViewerDataInterface`
- desc: Base class for all hierarchy data interfaces used by the Teds Outliner to display hierarchies in the UI. Teds Outliner hierarchies have the additional step of registering queries to detect changes to hierarchies when compared to the hierarchy viewer
- L20 _public prototype_ `virtual ~ITedsOutlinerHierarchyDataInterface() override = default;`
- L31 _public prototype_ `virtual void RegisterQueries(DataStorage::ICoreProvider& Storage, const DataStorage::FQueryDescription& OutlinerQueryDescription, TWeakPtr<ISceneOutliner> Outliner, bool bUsingQueryConditionsSyntax) = 0;` — Register any queries required by this data interface @param Storage Reference to the editor data storage interface @param OutlinerQueryDescription The query description used to gather rows in the outliner, can be merged with any local queries to filter down on the rows observed to only those in the outliner @param Outliner Ptr to the Scene Outliner owning this interface @param bUsingQueryConditionsSyntax Whether the owning outliner query description is using the new query condition syntax or not Useful for query merge which requires both input queries to be using the same syntax
- L35 _public prototype_ `virtual void UnregisterQueries(DataStorage::ICoreProvider& Storage) = 0;` — Unregister any queries required by this data interface
- L37 _public typedef_ `using FParentIterationCallback = TFunction<bool(const DataStorage::ICoreProvider& Context, DataStorage::RowHandle Parent)>;`
- L41 _public prototype_ `virtual void ForEachImmediateParent(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow, FParentIterationCallback Callback);` — Iterate over the immediate parents of InRow. In the simple case this is just one parent, but if this is a complex hierarchy combining multiple individual ones there could be multiple immediate parents

#### class `UE::Editor::Outliner::FTedsOutlinerMultiHierarchyInterface`  
`class FTedsOutlinerMultiHierarchyInterface : public ITedsOutlinerHierarchyDataInterface`  
_L45-67_
- inherits: `ITedsOutlinerHierarchyDataInterface`
- desc: Hierarchy Data interface that can be used to combine multiple hierarchies into one view
- L49 _public prototype_ `explicit FTedsOutlinerMultiHierarchyInterface(TSharedRef<DataStorage::FHierarchyViewerMultiData> InHierarchyData);` — @see FHierarchyViewerMultiData, which is used to specify the ordered list of hierarchies
- L51 _public prototype_ `virtual DataStorage::RowHandle GetParent(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow) const override;`
- L53 _public prototype_ `virtual void WalkDepthFirst(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow, DataStorage::ICoreProvider::FHierarchyIterationCallback VisitFn, DataStorage::ICoreProvider::ETraversalOrder TraversalOrder = DataStorage::ICoreProvider::ETraversalOrder::PreOrder) const override;`
- L57 _public prototype_ `virtual void RegisterQueries(DataStorage::ICoreProvider& Storage, const DataStorage::FQueryDescription& OutlinerQueryDescription, TWeakPtr<ISceneOutliner> Outliner, bool bUsingQueryConditionsSyntax) override;`
- L60 _public prototype_ `virtual void UnregisterQueries(DataStorage::ICoreProvider& Storage) override;`
- L62 _public prototype_ `virtual void ForEachImmediateParent(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow, FParentIterationCallback Callback) override;`
- L65 _protected member_ `TSharedRef<DataStorage::FHierarchyViewerMultiData> HierarchyData;`
- L66 _protected member_ `TArray<DataStorage::QueryHandle> HierarchyChangeQueries;`

#### struct `UE::Editor::Outliner::FTedsOutlinerHierarchyData`  
`struct FTedsOutlinerHierarchyData`  
_L77-111_
- desc: Legacy struct storing information on how hierarchies are handled in the TEDS Outliner
- L80 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(DataStorage::RowHandle, FGetParentRowHandle, const void* );` — A delegate used to get the parent row handle for a given row
- L83 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArrayView<DataStorage::RowHandle>, FGetChildrenRowsHandles, void* );` — A delegate used to get the children row handles for a given row
- L86 _public prototype_ `DECLARE_DELEGATE_TwoParams(FSetParentRowHandle, void* , DataStorage::RowHandle );` — A delegate used to set the parent row handle for a given row
- L88 _public function_ `FTedsOutlinerHierarchyData(const UScriptStruct* InHierarchyColumn, const FGetParentRowHandle& InGetParent, const FSetParentRowHandle& InSetParent, const FGetChildrenRowsHandles& InGetChildren) : HierarchyColumn(InHierarchyColumn) , GetParent(InGetParent) , GetChildren(InGetChildren) , SetParent(InSetParent)`
- L98 _public member_ `const UScriptStruct* HierarchyColumn;` — The column that contains the parent row handle for rows
- L101 _public member_ `FGetParentRowHandle GetParent;` — Function to get parent row handle
- L104 _public member_ `FGetChildrenRowsHandles GetChildren;` — Function to get the children row handle
- L107 _public member_ `FSetParentRowHandle SetParent;` — Function to set the parent row handle
- L110 _public prototype_ `static FTedsOutlinerHierarchyData GetDefaultHierarchyData();` — Get the default hierarchy data for the TEDS Outliner that uses FTableRowParentColumn to get the parent

#### class `UE::Editor::Outliner::FTedsOutlinerLegacyHierarchyInterface`  
`class FTedsOutlinerLegacyHierarchyInterface : public ITedsOutlinerHierarchyDataInterface`  
_L114-128_
- inherits: `ITedsOutlinerHierarchyDataInterface`
- desc: Legacy data interface for displaying custom hierarchies in the Teds Outliner
- L117 _public prototype_ `explicit FTedsOutlinerLegacyHierarchyInterface(FTedsOutlinerHierarchyData InHierarchyData);`
- L118 _public prototype_ `virtual DataStorage::RowHandle GetParent(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow) const override;`
- L119 _public prototype_ `virtual void WalkDepthFirst(const DataStorage::ICoreProvider& Storage, DataStorage::RowHandle InRow, DataStorage::ICoreProvider::FHierarchyIterationCallback VisitFn, DataStorage::ICoreProvider::ETraversalOrder TraversalOrder = DataStorage::ICoreProvider::ETraversalOrder::PreOrder) const override;`
- L121 _public prototype_ `virtual void RegisterQueries(DataStorage::ICoreProvider& Storage, const DataStorage::FQueryDescription& OutlinerQueryDescription, TWeakPtr<ISceneOutliner> Outliner, bool bUsingQueryConditionsSyntax) override;`
- L122 _public prototype_ `virtual void UnregisterQueries(DataStorage::ICoreProvider& Storage) override;`
- L125 _protected member_ `FTedsOutlinerHierarchyData HierarchyData;`
- L126 _protected member_ `DataStorage::QueryHandle HierarchyChangeQuery = DataStorage::InvalidQueryHandle;`
- L127 _protected member_ `DataStorage::QueryHandle GetChildrenQuery = DataStorage::InvalidQueryHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSOUTLINER_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L80 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(DataStorage::RowHandle, FGetParentRowHandle, const void* );` — A delegate used to get the parent row handle for a given row
- L83 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArrayView<DataStorage::RowHandle>, FGetChildrenRowsHandles, void* );` — A delegate used to get the children row handles for a given row
- L86 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetParentRowHandle, void* , DataStorage::RowHandle );` — A delegate used to set the parent row handle for a given row

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerImpl.h` (Public)


#### struct `UE::Editor::Outliner::FTedsOutlinerColumnParams`  
`struct FTedsOutlinerColumnParams`  
_L60-105_
- L89 _public prototype_ `explicit FTedsOutlinerColumnParams( const ESceneOutlinerColumnVisibility InInitialVisibility = ESceneOutlinerColumnVisibility::Visible, const EColumnPriorityGroup InPriorityGroup = EColumnPriorityGroup::Middle, const FColumnPriorityRelation& InPriorityRelation = FColumnPriorityRelation());`
- L94 _public prototype_ `explicit FTedsOutlinerColumnParams( const EColumnPriorityGroup InPriorityGroup, const FColumnPriorityRelation& InPriorityRelation = FColumnPriorityRelation());`
- L99 _public member_ `ESceneOutlinerColumnVisibility InitialVisibility;` — Visibility State of this column when the Outliner is Initialized (can change the visibility via the Header right-click menu)
- L101 _public member_ `EColumnPriorityGroup PriorityGroup;` — Priority Group this column belongs to, it will sort by relations in this group and have an adjusted priority value based on its group
- L104 _public member_ `FColumnPriorityRelation PriorityRelation;` — Specifies if this column should appear before or after another column (must be in the same priority group). Without this, order is defined by what Column is passed the Column Array first

#### enum `UE::Editor::Outliner::FTedsOutlinerColumnParams::EColumnPriorityGroup`  
`enum class EColumnPriorityGroup`  
_L64-69_
- desc: Defines the priority groups, where Left priority is ordered first and Right priority is ordered last ||  Left  |  Middle  |  Right  ||
- L66 _public enumerator_ `Middle = 0` — Initial Priority value of 80
- L67 _public enumerator_ `Left = 1 << 0` — Initial Priority value of 0
- L68 _public enumerator_ `Right = 1 << 1` — Initial Priority value of 160

#### struct `UE::Editor::Outliner::FTedsOutlinerColumnParams::FColumnPriorityRelation`  
`struct FColumnPriorityRelation`  
_L72-87_
- desc: Defines possible relations between columns so they can specify the desired ordering
- L81 _public prototype_ `explicit FColumnPriorityRelation(const EColumnPriorityRelation InPriorityRelation = EColumnPriorityRelation::None, const TWeakObjectPtr<const UScriptStruct>& InRelatedColumn = nullptr);`
- L85 _public member_ `EColumnPriorityRelation PriorityRelation;` — When determining priority, all columns with Before relations are sorted before columns with After Columns
- L86 _public member_ `TWeakObjectPtr<const UScriptStruct> RelatedColumn;`

#### enum `UE::Editor::Outliner::FTedsOutlinerColumnParams::FColumnPriorityRelation::EColumnPriorityRelation`  
`enum class EColumnPriorityRelation`  
_L74-79_
- L76 _public enumerator_ `None = 0`
- L77 _public enumerator_ `Before = 1 << 0` — This column comes before the specified RelatedColumn
- L78 _public enumerator_ `After = 1 << 1` — This column comes after the specified RelatedColumn

#### struct `UE::Editor::Outliner::FTedsOutlinerColumnDescription`  
`struct FTedsOutlinerColumnDescription`  
_L107-148_
- L109 _public prototype_ `FTedsOutlinerColumnDescription( const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns = {}, const TMap<TWeakObjectPtr<const UScriptStruct>, FTedsOutlinerColumnParams>& InColumnParams = {}, const TArray<TSharedPtr<FColumnMetaData>>& InColumnMetaData = {}, const FMetaData& InGenericMetaData = FMetaData());`
- L115 _public prototype_ `FTedsOutlinerColumnDescription( const TArray<TWeakObjectPtr<const UScriptStruct>>& InColumns, const FMetaData& InGenericMetaData);`
- L118 _public prototype_ `const TArray<TWeakObjectPtr<const UScriptStruct>>& GetColumns() const;`
- L121 _public prototype_ `TArray<TWeakObjectPtr<const UScriptStruct>> GetEffectiveColumns() const;` — Returns GetColumns() with ExcludedColumns filtered out.
- L123 _public prototype_ `const FTedsOutlinerColumnParams* FindColumnParams(const TWeakObjectPtr<const UScriptStruct>& InColumn) const;`
- L124 _public prototype_ `FTedsOutlinerColumnParams& FindOrAddColumnParams(const TWeakObjectPtr<const UScriptStruct>& InColumn);`
- L125 _public prototype_ `const TArray<TSharedPtr<FColumnMetaData>>& GetColumnMetaData() const;`
- L126 _public prototype_ `FMetaData GetGenericMetaData() const;`
- L129 _public prototype_ `bool ExcludeColumns(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> InColumns);` — Mark columns as excluded.
- L132 _public prototype_ `bool IncludeColumns(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> InColumns);` — Re-include columns that were previously excluded.
- L134 _public prototype_ `const TSet<TWeakObjectPtr<const UScriptStruct>>& GetExcludedColumns() const;`
- L138 _protected member_ `TArray<TWeakObjectPtr<const UScriptStruct>> Columns;` — Columns to display in the Outliner
- L140 _protected member_ `TMap<TWeakObjectPtr<const UScriptStruct>, FTedsOutlinerColumnParams> ColumnParams;` — Customization Parameters for a given column
- L142 _protected member_ `TArray<TSharedPtr<FColumnMetaData>> ColumnMetaData;` — Metadata for Columns (ReadOnly/ReadWrite), by default the constructor will populate this with ReadOnly Metadata for all columns
- L144 _protected member_ `FMetaData GenericMetaData;` — Generic meta data for the TEDS (i.e. GenericMetaData.AddOrSetMutableData("bAllowSorting", false))
- L147 _protected member_ `TSet<TWeakObjectPtr<const UScriptStruct>> ExcludedColumns;` — Columns currently suppressed. Honored by FTedsOutlinerImpl::RegenerateColumns; the Columns array and ColumnParams map are never mutated when a column is excluded.

#### struct `UE::Editor::Outliner::FTedsOutlinerExpansionStateBridge`  
`struct FTedsOutlinerExpansionStateBridge`  
_L151-155_
- L153 _public member_ `TFunction<bool(RowHandle)> GetExpansionState;`
- L154 _public member_ `TFunction<void(RowHandle, bool)> SetExpansionState;`

#### struct `UE::Editor::Outliner::FTedsOutlinerParams`  
`struct FTedsOutlinerParams`  
_L157-232_
- L159 _public prototype_ `FTedsOutlinerParams(SSceneOutliner* InSceneOutliner);`
- L161 _public member_ `SSceneOutliner* SceneOutliner = nullptr;`
- L164 _public member_ `DataStorage::FQueryDescription QueryDescription;` — The query description that will be used to populate rows in the TEDS Outliner
- L167 _public member_ `FTedsOutlinerColumnDescription ColumnDescription;` — The columns to display in the TEDS Outliner and any additional metadata
- L170 _public member_ `TArray<TSharedPtr<FTedsOutlinerFilter>> Filters;` — TEDS Filters that utilize QueryDescriptions or QueryFunctions in this TEDS Outliner
- L174 _public member_ `TMap<FName, TArray<TSharedPtr<FFilterCategory>>> FilterCategoryMap;` — Additional categories for type filters. The same filter instance will appear under all categories in the "Add Filter" menu, sharing its active state.
- L177 _public member_ `TArray<TSharedPtr<FTedsOutlinerFilter>> ShowOptionsFilters;` — TEDS Filters that populate the Show section of the settings menu: "Hide Components", etc.
- L180 _public member_ `FOnExtendViewMenu OnInitializeViewMenuExtender;` — Delegate for extending the View Menu with additional options
- L183 _public member_ `FOnExtendOptionsMenu OnExtendOptionsMenu;` — Delegate for adding entries into the "Options" section of the View Menu
- L186 _public member_ `FOnOutlinerItemDoubleClick OnItemDoubleClick;` — Delegate called before the default double-click behavior. Return true if handled.
- L189 _public member_ `FTedsOutlinerExpansionStateBridge ExpansionStateBridge;` — Expansion state bridge (temporary)
- L192 _public member_ `FOnCanPopulate OnCanPopulate;` — Delegate used by the SSceneOutliner to decide whether to populate
- L195 _public member_ `FOnCustomAddToToolbar OnCustomAddToToolbar;` — Delegate fired by the mode's CustomAddToToolbar - extender adds widgets to the outliner toolbar.
- L198 _public member_ `FOnRegisterInteractiveFilters OnRegisterInteractiveFilters;` — Delegate invoked once after the outliner is constructed so callers can register interactive filters via SSceneOutliner::AddInteractiveFilter.
- L201 _public member_ `bool bShowRowHandleColumn;` — If true, this Outliner will include a column for row handle
- L204 _public member_ `bool bForceShowParents;` — If true, parent nodes will remain visible if a child passes all filters even if the parent fails a filter
- L207 _public member_ `bool bUseDefaultObservers;` — If true, the Teds Outliner will create observers to track addition/removal of rows and update the Outliner
- L210 _public member_ `bool bShowViewButton = false;` — If true, the Teds Outliner will create a view button (settings cog) pre-populated with hierarchy actions
- L214 _public member_ `TSharedPtr<ITedsOutlinerHierarchyDataInterface> HierarchyData;` — If specified, this is how the TEDS Outliner will handle hierarchies. If not specified - there will be no hierarchies shown as a parent-child relation in the tree view
- L217 _public member_ `UTypedElementSelectionSet* SelectionSet;` — The selection set to use for this Outliner, nullptr = don't propagate tree selection through TypedElementSelectionInterface
- L220 _public member_ `DataStorage::IUiProvider::FPurposeID CellWidgetPurpose;` — The purpose to use when generating widgets for row/column pairs through TEDS UI
- L223 _public member_ `DataStorage::IUiProvider::FPurposeID HeaderWidgetPurpose;` — The purpose to use when generating widgets for column headers through TEDS UI
- L226 _public member_ `DataStorage::IUiProvider::FPurposeID LabelWidgetPurpose;` — The purpose to use when generating widgets for the "Item Label" column through TEDS UI
- L230 _public member_ `TOptional<FQueryDescription> AddObserverQuery;` — Additional queries that the TEDS Outliner will use to add or remove certain rows when the query is run. NOTE: The callback function for these queries will be overriden by the Outliner.
- L231 _public member_ `TOptional<FQueryDescription> RemoveObserverQuery;`

#### class `UE::Editor::Outliner::FTedsOutlinerImpl`  
`class FTedsOutlinerImpl : public TSharedFromThis<FTedsOutlinerImpl>`  
_L238-495_
- inherits: `TSharedFromThis<FTedsOutlinerImpl>`
- desc: This class is meant to be a model to hold functionality to create a "table viewer" in TEDS that can be attached to any view/UI. TEDS-Outliner TODO: This class still has a few outliner implementation details leaking in that should be removed
- L243 _public prototype_ `static TSharedRef<SWidget> CreateLabelWidget( DataStorage::ICoreProvider& Storage, DataStorage::IUiProvider& StorageUi, const DataStorage::IUiProvider::FPurposeID& Purpose, DataStorage::RowHandle TargetRow, const DataStorage::RowHandle OutlinerWidgetRow, ISceneOutlinerTreeItem& TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& RowItem, bool bInteractable = true);` — Helper function to create a label widget for a given row
- L253 _public prototype_ `FTedsOutlinerImpl(const FTedsOutlinerParams& InParams, ISceneOutlinerMode* InMode, bool bInHybridMode);`
- L254 _public prototype_ `virtual ~FTedsOutlinerImpl();`
- L256 _public prototype_ `void Init();`
- L257 _public prototype_ `void FullRefresh() const;`
- L258 _public prototype_ `void OnMonitoredRowsAdded(DataStorage::FRowHandleArrayView InRows);`
- L259 _public prototype_ `void OnMonitoredRowsRemoved(DataStorage::FRowHandleArrayView InRows);`
- L262 _public prototype_ `DataStorage::ICoreProvider* GetStorage() const;` — TEDS construct getters
- L263 _public prototype_ `DataStorage::IUiProvider* GetStorageUI() const;`
- L264 _public prototype_ `DataStorage::ICompatibilityProvider* GetStorageCompatibility() const;`
- L266 _public prototype_ `UTypedElementSelectionSet* GetSelectionSet() const;`
- L269 _public prototype_ `FOnTedsOutlinerSelectionChanged& OnSelectionChanged();` — Delegate fired when the selection changes, only if SelectionSet is set
- L272 _public prototype_ `void SetPendingSelectionType(ESelectInfo::Type InSelectionType);` — Set the selection type to broadcast with the next OnSelectionChanged event
- L275 _public prototype_ `ISceneOutlinerHierarchy::FHierarchyChangedEvent& OnHierarchyChanged();` — Delegate fired when the hierarchy changes due to item addition/removal/move
- L278 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemCompatible, const ISceneOutlinerTreeItem&) FIsItemCompatible& IsItemCompatible();` — Delegate to check if a certain outliner item is compatible with this TEDS Outliner Impl - set by the system using FTedsOutlinerImpl
- L283 _public prototype_ `void SetSelection(const TArray<DataStorage::RowHandle>& InSelectedRows);` — Update the selection to the input rows, only if SelectionSet is set This will use the TypedElementSelectionInterface to select/deselect elements
- L286 _public prototype_ `TSharedRef<SWidget> CreateLabelWidgetForItem(DataStorage::RowHandle TargetRow, ISceneOutlinerTreeItem& TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& RowItem, bool bIsInteractable = true) const;` — Helper function to create a label widget for a given row
- L289 _public prototype_ `void AddExternalQuery(const FName& QueryName, const QueryHandle& InQueryHandle);` — Add an external query description to the Outliner
- L290 _public prototype_ `void RemoveExternalQuery(const FName& QueryName);`
- L293 _public prototype_ `void AppendExternalQueries(DataStorage::FQueryDescription& OutQuery);` — Append all external queries into the given query description
- L296 _public prototype_ `void AddExternalQueryFunction(const FName& QueryName, const TConstQueryFunction<bool>& InQueryFunction);` — Add an external query function to the Outliner
- L297 _public prototype_ `void RemoveExternalQueryFunction(const FName& QueryName);`
- L300 _public prototype_ `void AddClassQueryFunction(const FName& ClassName, const TConstQueryFunction<bool>& InClassQueryFunction);` — Add an external class query function to the Outliner (uses OR)
- L301 _public prototype_ `void RemoveClassQueryFunction(const FName& ClassName);`
- L304 _public prototype_ `void CreateItemsFromQuery(TArray<FSceneOutlinerTreeItemPtr>& OutItems, ISceneOutlinerMode* InMode);` — Outliner specific functionality
- L305 _public prototype_ `void CreateChildren(const FSceneOutlinerTreeItemPtr& Item, TArray<FSceneOutlinerTreeItemPtr>& OutChildren) const;`
- L308 _public prototype_ `DataStorage::RowHandle GetParentRow(DataStorage::RowHandle InRowHandle);` — Get the parent row for a given row
- L310 _public prototype_ `bool ShouldForceShowParentRows() const;`
- L313 _public prototype_ `void RefreshQueries() const;` — Refresh the primary query node and its filters; use instead of RecompileQueries if the queries have not changed
- L316 _public prototype_ `void RecompileQueries();` — Recompile all queries used by this table viewer
- L319 _public prototype_ `void UnregisterQueries();` — Unregister all queries used by this table viewer
- L321 _public prototype_ `void Tick();`
- L324 _public prototype_ `bool IsSorting() const;` — Sorting delegates
- L325 _public prototype_ `void OnSort(FName ColumnName, TSharedPtr<const DataStorage::FColumnSorterInterface> ColumnSorter, EColumnSortMode::Type Direction, EColumnSortPriority::Type Priority);`
- L327 _public prototype_ `void SortItems(TArray<FSceneOutlinerTreeItemPtr>& Items, EColumnSortMode::Type Direction) const;`
- L329 _public prototype_ `DataStorage::RowHandle GetOutlinerRowHandle() const;`
- L332 _public prototype_ `void IncludeExcludeColumns(TConstArrayView<TWeakObjectPtr<const UScriptStruct>> IncludedColumns, TConstArrayView<TWeakObjectPtr<const UScriptStruct>> ExcludedColumns);` — Exclude and include one or more columns from this outliner.
- L334 _public prototype_ `int32 GetTotalRowCount() const;`
- L336 _public prototype_ `const FTedsOutlinerExpansionStateBridge& GetExpansionStateBridge() const;`
- L340 _protected prototype_ `void ClearSelection() const;`
- L341 _protected prototype_ `void PostDataStorageUpdate();`
- L343 _protected prototype_ `void CreateFilterQueries();`
- L346 _protected prototype_ `bool CanDisplayRow(DataStorage::RowHandle ItemRowHandle) const;` — Check if this row can be displayed in this table viewer
- L349 _protected prototype_ `void RegisterTedsOutliner();` — Register this Teds Outliner with TEDS
- L351 _protected prototype_ `void ClearColumns() const;`
- L352 _protected prototype_ `void RegenerateColumns(const FTedsOutlinerColumnDescription& ColumnDescription);`
- L355 _private prototype_ `void OnSelectionChangedHandler(const UTypedElementSelectionSet* InSelectionSet);`
- L356 _private prototype_ `RowHandle GetRowHandleFromOutlinerItem(const ISceneOutlinerTreeItem& Item) const;`
- L360 _protected member_ `DataStorage::ICoreProvider* Storage{ nullptr };` — TEDS Storage Constructs
- L361 _protected member_ `DataStorage::IUiProvider* StorageUi{ nullptr };`
- L362 _protected member_ `DataStorage::ICompatibilityProvider* StorageCompatibility{ nullptr };`
- L364 _protected member_ `FTedsOutlinerParams CreationParams;`
- L367 _protected member_ `DataStorage::IUiProvider::FPurposeID CellWidgetPurpose;` — The purpose to use when generating widgets for row/column pairs through TEDS UI
- L370 _protected member_ `DataStorage::IUiProvider::FPurposeID HeaderWidgetPurpose;` — The purpose to use when generating widgets for headers pairs through TEDS UI
- L373 _protected member_ `DataStorage::IUiProvider::FPurposeID LabelWidgetPurpose;` — The purpose to use when generating widgets for the "Item Label" column through TEDS UI
- L376 _protected member_ `DataStorage::FQueryDescription InitialQueryDescription;` — Initial query provided by user
- L379 _protected member_ `TMap<FName, TSharedPtr<DataStorage::QueryStack::IQueryNode>> ExternalQueries;` — External query descriptions that are currently active (e.g Filters)
- L382 _protected member_ `TMap<FName, DataStorage::Queries::TConstQueryFunction<bool>> ExternalQueryFunctions;` — External query functions that are currently active (e.g Filters)
- L385 _protected member_ `TMap<FName, DataStorage::Queries::TConstQueryFunction<bool>> ClassFilters;` — External query functions used to filter by class, these are the only filters that use OR instead of AND
- L388 _protected member_ `TArray<TSharedPtr<DataStorage::QueryStack::FRowFilterNode>> FilterNodes;` — Array to store all filter nodes created from the active query functions
- L391 _protected member_ `TArray<TSharedPtr<DataStorage::QueryStack::FRowFilterNode>> ClassFilterNodes;` — Array to store all filter nodes created from the active class filters
- L394 _protected member_ `TSharedPtr<ITedsOutlinerHierarchyDataInterface> HierarchyData;` — Optional Hierarchy Data
- L396 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowQueryResultsNode> InitialRowCollectorNode;` — The query stack node responsible for collecting all rows that match the initial query on FullRefresh()
- L398 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowQueryResultsNode> CombinedRowCollectorNode;` — The query stack node responsible for collecting all rows that match the composite query on FullRefresh()
- L401 _protected member_ `TSharedPtr<DataStorage::QueryStack::IRowNode> CombinedClassFilterRowNode;` — The query stack node responsible for combining class filters - utilizes the unique merge approach (OR)
- L405 _protected member_ `TSharedPtr<DataStorage::QueryStack::IRowNode> FinalCombinedRowNode;` — The query stack node responsible for combining all filters and queries as the 'final' node responsible for getting all desired rows - utilizes the repeating merge approach (AND)
- L408 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowMonitorNode> RowMonitorNode;` — The query stack node responsible for tracking and row addition/removals that happen in between refreshes
- L411 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowHandleSortNode> RowHandleSortNode;` — A query stack node that keeps a copy of our rows sorted by row handle for faster search/lookup
- L414 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowSortNode> RowPrimarySortingNode;` — A query stack node that keeps a copy of our rows sorted by the actual column the user wants to sort by
- L417 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowOrderInversionNode> RowPrimaryInversionNode;` — Inverts the rows from the query stack when needed by the primary sort.
- L420 _protected member_ `TSharedPtr<FRowMapNode> RowSortMapNode;` — A map of the row handle -> index in the sort node for lookup
- L423 _protected member_ `TUniquePtr<DataStorage::QueryStack::FExplicitUpdateExecutor> QueryStackExecutor;` — The executor used to update the query stack stack.
- L426 _protected member_ `TSharedPtr<DataStorage::QueryStack::FRowHandleSortNode> InitialQueryResultsSortedNode;` — A query stack node that keeps a sorted copy of the initial query results (i.e without any filters or search) for fast lookup
- L429 _protected member_ `TUniquePtr<DataStorage::QueryStack::FExplicitUpdateExecutor> InitialQueryResultsSortedNodeExecutor;` — The executor used to update the node storing a copy of the initial query results. This is updated on demand and not every tick
- L432 _protected member_ `DataStorage::QueryHandle SelectedRowsQuery = DataStorage::InvalidQueryHandle;` — Query to get all selected rows, track selection added, track selection removed
- L433 _protected member_ `DataStorage::QueryHandle SelectionAddedQuery = DataStorage::InvalidQueryHandle;`
- L434 _protected member_ `DataStorage::QueryHandle SelectionRemovedQuery = DataStorage::InvalidQueryHandle;`
- L437 _protected member_ `DataStorage::QueryHandle LabelUpdateQuery = DataStorage::InvalidQueryHandle;` — Query to track when a row's label gets changed
- L440 _protected member_ `DataStorage::QueryHandle AdditionalAddObserverQuery = DataStorage::InvalidQueryHandle;` — Additional observer queries
- L441 _protected member_ `DataStorage::QueryHandle AdditionalRemoveObserverQuery = DataStorage::InvalidQueryHandle;`
- L445 _protected member_ `FDelegateHandle SelectionSetChangedDelegateHandle;` — Handle to keep track of the lifetime of the OnChanged delegate handler for the SelectionSet This handler is responsible for setting bSelectionDirty
- L448 _protected member_ `TObjectPtr<UTypedElementSelectionSet> SelectionSet;` — The UTypedElementSelectionSet to use for propagating selection via TypedElementSelectionInterface
- L450 _protected member_ `bool bSelectionDirty = false;`
- L451 _protected member_ `ESelectInfo::Type PendingSelectionType = ESelectInfo::Direct;`
- L454 _protected member_ `bool bForceShowParents = true;` — If true, parent nodes will remain visible if a child passes all filters even if the parent fails a filter
- L457 _protected member_ `FRowHandleArray ForceShownParentRows;` — Rows that are force-shown as parents in the tree because bForceShowParents=true, but do not themselves match the active filter (not in FinalCombinedRowNode).
- L460 _protected member_ `FTSTicker::FDelegateHandle TickerHandle;` — Ticker for selection updates so we don't fire the delegate multiple times in one frame for multi select
- L463 _protected member_ `FDelegateHandle OnTextFilteredChangedHandle;` — Handle for OnTextFilteredChanged delegate, so we can remove it upon destruction
- L465 _protected member_ `FOnTedsOutlinerSelectionChanged OnTedsOutlinerSelectionChanged;`
- L468 _protected member_ `ISceneOutlinerMode* SceneOutlinerMode;` — Scene Outliner specific constructors
- L469 _protected member_ `SSceneOutliner* SceneOutliner;`
- L472 _protected member_ `ISceneOutlinerHierarchy::FHierarchyChangedEvent HierarchyChangedEvent;` — Event fired when the hierarchy changes (addition/removal/move)
- L475 _protected member_ `FIsItemCompatible IsItemCompatibleWithTeds;` — Delegate to check if an item is compatible with this table viewer
- L478 _protected member_ `bool bUsingQueryConditionsSyntax = false;` — Whether the row query is using the FConditions syntax (TColumn<FMyColumn>()) or the old syntax (.All().Any().None())
- L482 _protected member_ `TSet<DataStorage::RowHandle> RowsPendingLabelUpdate;` — Addition and Label Updates are deferred because they access data storage implicitly Deletion is currently not deferred to work nicely with object lifecycles in some cases - but can be once everything goes through the query stack
- L485 _protected member_ `DataStorage::RowHandle OutlinerRowHandle = DataStorage::InvalidRowHandle;` — The Row Handle associated with this outliner
- L488 _protected member_ `TArray<FName> AddedColumns;` — The columns currently being displayed by the Teds Outliner
- L491 _protected member_ `bool bHybridMode;` — Whether this is a hybrid outliner, i.e it is displaying TEDS rows and some non-TEDS items
- L494 _protected member_ `FTedsOutlinerExpansionStateBridge ExpansionStateBridge;` — Expansion state bridge (temporary)

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API TEDSOUTLINER_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Editor` (scope `UE`)
- L22 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L42 _namespace_ `namespace UE`
- L42 _namespace_ `namespace Editor` (scope `UE`)
- L42 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L51 _namespace_ `namespace UE`
- L51 _namespace_ `namespace Editor` (scope `UE`)
- L51 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExtendViewMenu, TSharedPtr<FExtender>);`
- L53 _prototype_ `DECLARE_DELEGATE_OneParam(FOnExtendViewMenu, TSharedPtr<FExtender>);` (scope `UE::Editor::Outliner`)
- L54 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnOutlinerItemDoubleClick, ICoreProvider*, DataStorage::RowHandle , DataStorage::RowHandle );`
- L54 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnOutlinerItemDoubleClick, ICoreProvider*, DataStorage::RowHandle , DataStorage::RowHandle );` (scope `UE::Editor::Outliner`)
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FOnExtendOptionsMenu, FMenuBuilder&);`
- L55 _prototype_ `DECLARE_DELEGATE_OneParam(FOnExtendOptionsMenu, FMenuBuilder&);` (scope `UE::Editor::Outliner`)
- L56 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCanPopulate, ICoreProvider*, DataStorage::RowHandle );`
- L56 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnCanPopulate, ICoreProvider*, DataStorage::RowHandle );` (scope `UE::Editor::Outliner`)
- L57 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCustomAddToToolbar, TSharedPtr<SHorizontalBox> , DataStorage::RowHandle );`
- L57 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnCustomAddToToolbar, TSharedPtr<SHorizontalBox> , DataStorage::RowHandle );` (scope `UE::Editor::Outliner`)
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRegisterInteractiveFilters, SSceneOutliner&);`
- L58 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRegisterInteractiveFilters, SSceneOutliner&);` (scope `UE::Editor::Outliner`)
- L278 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsItemCompatible, const ISceneOutlinerTreeItem&) FIsItemCompatible& IsItemCompatible();` — Delegate to check if a certain outliner item is compatible with this TEDS Outliner Impl - set by the system using FTedsOutlinerImpl

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerItem.h` (Public)


#### struct `UE::Editor::Outliner::FTedsOutlinerTreeItem`  
`struct FTedsOutlinerTreeItem : ISceneOutlinerTreeItem`  
_L18-56_
- inherits: `ISceneOutlinerTreeItem`
- desc: A generic item in the TEDS driven Outliner, that uses a DataStorage::RowHandle to uniquely identify the object it is looking at. Functionality should be added through TEDS queries instead of having a different TreeItem type for each type of object you are looking at (i.e. Actor vs Folder) Inherits from ISceneOutlinerItem - which determines what type of item you are looking at. E.G FActorTreeItem for actors
- L22 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const DataStorage::RowHandle);`
- L23 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const DataStorage::RowHandle);`
- L25 _public function_ `bool Filter(FFilterPredicate Pred) const`
- L30 _public function_ `bool GetInteractiveState(FInteractivePredicate Pred) const`
- L35 _public prototype_ `FTedsOutlinerTreeItem(const DataStorage::RowHandle& InRowHandle, const TWeakPtr<const FTedsOutlinerImpl>& InTedsOutlinerImpl);`
- L38 _public prototype_ `virtual bool IsValid() const override;` — Begin ISceneOutlinerTreeItem Implementation
- L39 _public prototype_ `virtual FSceneOutlinerTreeItemID GetID() const override;`
- L40 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L41 _public prototype_ `virtual FString GetDisplayString() const override;`
- L42 _public prototype_ `virtual bool CanInteract() const override;`
- L43 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(ISceneOutliner& Outliner, const STableRow<FSceneOutlinerTreeItemPtr>& InRow) override;`
- L45 _public prototype_ `virtual void GenerateContextMenu(UToolMenu* Menu, SSceneOutliner& Outliner);` — Generate a context menu for this item. Only called if *only* this item is selected.
- L46 _public prototype_ `virtual void OnExpansionChanged() override;`
- L49 _public member_ `static const FSceneOutlinerTreeItemType Type;`
- L51 _public prototype_ `DataStorage::RowHandle GetRowHandle() const;`
- L54 _private member_ `const DataStorage::RowHandle RowHandle;`
- L55 _private member_ `const TWeakPtr<const FTedsOutlinerImpl> TedsOutlinerImpl;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFilterPredicate, const DataStorage::RowHandle);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FInteractivePredicate, const DataStorage::RowHandle);`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerMode.h` (Public)


#### class `UE::Editor::Outliner::FTedsOutlinerMode`  
`class FTedsOutlinerMode : public ISceneOutlinerMode`  
_L24-138_
- inherits: `ISceneOutlinerMode`
- desc: TEDS driven Outliner mode where the Outliner is populated using the results of the RowHandleQueries passed in. See CreateGenericTEDSOutliner() for example usage Inherits from ISceneOutlinerMode - which contains all actions that depend on the type of item you are viewing in the Outliner
- L27 _public prototype_ `explicit FTedsOutlinerMode(const FTedsOutlinerParams& InParams);`
- L31 _public prototype_ `virtual void Rebuild() override;` — ISceneOutlinerMode interface
- L32 _public prototype_ `virtual void SynchronizeSelection() override;`
- L33 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L34 _public prototype_ `virtual bool CanInteract(const ISceneOutlinerTreeItem& Item) const override;`
- L35 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L36 _public function_ `virtual bool CanSupportDragAndDrop() const override` — TODO: Can we check this from TEDS somehow (if the user requests a drag column?)
- L37 _public prototype_ `virtual TSharedPtr<FDragDropOperation> CreateDragDropOperation(const FPointerEvent& MouseEvent, const TArray<FSceneOutlinerTreeItemPtr>& InTreeItems) const override;`
- L38 _public prototype_ `virtual bool ParseDragDrop(FSceneOutlinerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const override;`
- L39 _public prototype_ `virtual FSceneOutlinerDragValidationInfo ValidateDrop(const ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload) const override;`
- L40 _public prototype_ `virtual void OnDrop(ISceneOutlinerTreeItem& DropTarget, const FSceneOutlinerDragDropPayload& Payload, const FSceneOutlinerDragValidationInfo& ValidationInfo) const override;`
- L41 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L42 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L43 _public prototype_ `virtual void Tick() override;`
- L44 _public prototype_ `virtual bool CanPopulate() const override;`
- L45 _public prototype_ `virtual bool ShowViewButton() const override;`
- L46 _public prototype_ `virtual void InitializeViewMenuExtender(TSharedPtr<FExtender> Extender) override;`
- L47 _public prototype_ `virtual bool ShowFilterOptions() const override;`
- L48 _public prototype_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item) override;`
- L49 _public prototype_ `virtual void OnItemRemoved(FSceneOutlinerTreeItemPtr Item) override;`
- L50 _public prototype_ `virtual FText GetStatusText() const override;`
- L51 _public prototype_ `virtual FSlateColor GetStatusTextColor() const override;`
- L52 _public prototype_ `virtual bool ShowStatusBar() const override;`
- L53 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& OutCommandList) override;`
- L54 _public prototype_ `virtual bool CanRenameItem(const ISceneOutlinerTreeItem& Item) const override;`
- L55 _public prototype_ `virtual bool CanDelete() const override;`
- L56 _public prototype_ `virtual bool CanCut() const override;`
- L57 _public prototype_ `virtual bool CanCopy() const override;`
- L58 _public prototype_ `virtual bool CanPaste() const override;`
- L59 _public prototype_ `virtual FFolder::FRootObject GetRootObject() const override;`
- L60 _public prototype_ `virtual bool CanCustomizeToolbar() const override;`
- L61 _public prototype_ `virtual void CustomAddToToolbar(TSharedPtr<class SHorizontalBox> Toolbar) override;`
- L64 _public prototype_ `int32 GetFilteredRowCount() const;`
- L68 _protected prototype_ `virtual TUniquePtr<ISceneOutlinerHierarchy> CreateHierarchy() override;`
- L70 _protected prototype_ `void OnSelectionChanged(ESelectInfo::Type SelectionType);` — Called by TedsOutlinerImpl when the selection in TEDS changes
- L73 _protected prototype_ `void OnToggleAlwaysFrameSelection();` — Functions to expose default SceneOutliner Options to the UI
- L74 _protected prototype_ `bool ShouldAlwaysFrameSelection() const;`
- L76 _protected prototype_ `void OnToggleCollapseOutlinerTreeOnNewSelection();`
- L77 _protected prototype_ `bool CollapseOutlinerTreeOnNewSelection() const;`
- L85 _private prototype_ `struct FTedsOutlinerModeConfig* GetMutableConfig();` — Get a mutable version of the TedsOutliner config for setting values. @returns		The config for this TedsOutliner. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L92 _private prototype_ `const FTedsOutlinerModeConfig* GetConstConfig() const;` — Get a const version of the TedsOutliner config for getting values. @returns		The config for this TedsOutliner. @note		If OutlinerIdentifier is not set for this outliner, it is not possible to store settings.
- L95 _private prototype_ `void SaveConfig();` — Save the config for this TedsOutliner
- L98 _private prototype_ `bool CanExecuteRename();` — Bound to the rename command.
- L99 _private prototype_ `void OnExecuteRename();`
- L107 _private prototype_ `void RegisterPendingItemActions(DataStorage::RowHandle Row, uint8 ItemActions);` — Register Select/Rename/ScrollIntoView actions to apply to a row's TreeItem the next time it is added to the tree. NewItemActions (what OnItemAdded writes to) gets cleared at SSceneOutliner::Populate whenever PendingOperations is empty. For TEDS, the new row surfaces via RowMonitor on the next TEDS tick so a Populate pass with empty PendingOperations can fire in between, wiping the entry before SSceneOutliner::AddItemToTree ever sees it. RegisterPendingItemActions bypasses that by storing the mask on the TEDS side and consuming it in FTedsOutlinerMode::OnItemAdded after the race window.
- L110 _protected member_ `bool bShowViewButton = false;`
- L113 _protected member_ `bool bAlwaysFrameSelection;` — Should the outliner scroll to the item on selection
- L115 _protected member_ `bool bCollapseOutlinerTreeOnNewSelection;` — Should Outliner Tree get collapsed on selection, except for the item that was just selected
- L118 _protected member_ `FOnExtendViewMenu OnInitializeViewMenuExtender;` — Delegate for extending the View Menu with options (World picker, frame on selection, etc.)
- L120 _protected member_ `FOnExtendOptionsMenu OnExtendOptionsMenu;` — Delegate for injecting entries into the "Options" section of the View Menu
- L122 _protected member_ `FOnOutlinerItemDoubleClick OnItemDoubleClickDelegate;` — Delegate called before the default double-click behavior. Return true if handled.
- L124 _protected member_ `FOnCanPopulate OnCanPopulateDelegate;` — Delegate called in CanPopulate if there is logic needed to disable populating (i.e during PIE)
- L126 _protected member_ `FOnCustomAddToToolbar OnCustomAddToToolbarDelegate;` — Delegate that adds widgets to the outliner toolbar.
- L128 _protected member_ `TSharedPtr<FTedsOutlinerImpl> TedsOutlinerImpl;` — The actual model for the TEDS Outliner
- L131 _protected member_ `FTypedElementSelectionOptions CanInteractSelectionOptions;` — TypedElement Selection Options use during CanInteract
- L134 _protected member_ `int32 TedsOutlinerItemCount = 0;` — Number of items currently visible in the tree (reduced by text filter)
- L137 _protected member_ `TMap<DataStorage::RowHandle, uint8> PendingItemActionsByRow;` — Per-row Select/Rename/ScrollIntoView actions to apply when the matching TreeItem first appears in the tree.

#### class `UTedsOutlinerMenuContext`  
`class UTedsOutlinerMenuContext : public UObject`  
_L144-149_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class to hold the owning scene outliner for a menu TEDS-Outliner TODO: Once menus go through TEDS UI this can be done using the FTableViewerColumn on the widget row instead
- L148 _public member_ `SSceneOutliner* OwningSceneOutliner = nullptr;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API TEDSOUTLINER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/TedsOutlinerModule.h` (Public)


#### class `UE::Editor::Outliner::FTedsOutlinerModule`  
`class FTedsOutlinerModule : public IModuleInterface`  
_L33-75_
- inherits: `IModuleInterface`
- desc: Implements the Scene Outliner module.
- L38 _public prototype_ `FTedsOutlinerModule();`
- L48 _public prototype_ `virtual TSharedRef<ISceneOutliner> CreateTedsOutliner( const FSceneOutlinerInitializationOptions& InInitOptions, const FTedsOutlinerParams& InInitTedsOptions) const;` — Creates a TEDS-Outliner widget @param	InInitOptions						Programmer-driven configuration for the scene outliner @param	InInitTedsOptions				Programmer-driven configuration for the TEDS queries that drive the outliner @return	New scene outliner widget
- L52 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L53 _public prototype_ `virtual void ShutdownModule() override;`
- L56 _public prototype_ `virtual FTedsOutlinerColumnDescription GetLevelEditorTedsOutlinerColumnDescription();` — Get the column description the default table viewer uses
- L59 _public prototype_ `FName GetTedsOutlinerTabName();` — The name of the tab the default table viewer is opened in
- L63 _private prototype_ `void RegisterLevelEditorTedsOutlinerTab();`
- L64 _private prototype_ `void UnregisterLevelEditorTedsOutlinerTab();`
- L65 _private prototype_ `TSharedRef<SDockTab> OpenLevelEditorTedsOutliner(const FSpawnTabArgs& SpawnTabArgs);`
- L66 _private prototype_ `TSharedRef<SWidget> CreateLevelEditorTedsOutliner();`
- L69 _private member_ `FName TedsOutlinerTabName;`
- L70 _private member_ `FDelegateHandle LevelEditorTabManagerChangedHandle;`
- L71 _private member_ `FDelegateHandle TedsInitializedHandle;`
- L72 _private member_ `FDelegateHandle EditorInitializedHandle;`
- L73 _private member_ `DataStorage::ICoreProvider* Storage = nullptr;`
- L74 _private member_ `DataStorage::IUiProvider* StorageUi = nullptr;`

#### class `UE::Editor::Outliner::FTedsSceneOutlinerWorldFilter`  
`class FTedsSceneOutlinerWorldFilter : public FTedsOutlinerFilter`  
_L77-103_
- inherits: `FTedsOutlinerFilter`
- L80 _public prototype_ `FTedsSceneOutlinerWorldFilter(const FName& InFilterName, const TWeakObjectPtr<UWorld>& InSpecifiedWorldToDisplay = nullptr);`
- L82 _public prototype_ `~FTedsSceneOutlinerWorldFilter();`
- L84 _public prototype_ `void BuildWorldFilter();`
- L86 _public prototype_ `void QueryFunction(TConstQueryContext<RowBatchInfo> Context, TResult<bool>& Result, TConstBatch<FTypedElementWorldColumn> WorldColumns);`
- L88 _public prototype_ `void SetUserChosenWorld(const TWeakObjectPtr<UWorld>& InWorld);`
- L90 _public prototype_ `TWeakObjectPtr<UWorld> GetRepresentingWorld() const;`
- L92 _public prototype_ `TWeakObjectPtr<UWorld> GetUserChosenWorld() const;`
- L96 _protected member_ `TWeakObjectPtr<UWorld> RepresentingWorld;` — The world which we are currently filtering for
- L99 _protected member_ `TWeakObjectPtr<UWorld> UserChosenWorld;` — The world that has been manually picked by the user
- L102 _protected member_ `const TWeakObjectPtr<UWorld> SpecifiedWorldToDisplay;` — If this mode was created to display a specific world, don't allow it to be reassigned

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Editor` (scope `UE`)
- L25 _namespace_ `namespace Outliner` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerActorLayersWidget.h` (Public)


#### class `UE::Editor::DataStorage::FOutlinerActorLayersWidgetSearcher`  
`class FOutlinerActorLayersWidgetSearcher final : public TColumnSearcherInterface<Layers::FActorLayersColumn>`  
_L16-20_
- inherits: `TColumnSearcherInterface<Layers::FActorLayersColumn>`
- L19 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const Layers::FActorLayersColumn& Column) const override;`

#### class `UOutlinerActorLayersWidgetFactory`  
`class UOutlinerActorLayersWidgetFactory : public UEditorDataStorageFactory`  
_L24-33_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L29 _public prototype_ `~UOutlinerActorLayersWidgetFactory() override = default;`
- L31 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerActorLayersWidgetConstructor`  
`struct FOutlinerActorLayersWidgetConstructor : public FSimpleWidgetConstructor`  
_L36-59_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L41 _public prototype_ `FOutlinerActorLayersWidgetConstructor();`
- L42 _public prototype_ `~FOutlinerActorLayersWidgetConstructor() override = default;`
- L44 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L48 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L55 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerCDOTextWidget.h` (Public)


#### class `UOutlinerCDOTextWidgetFactory`  
`class UOutlinerCDOTextWidgetFactory : public UEditorDataStorageFactory`  
_L17-26_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L22 _public prototype_ `virtual ~UOutlinerCDOTextWidgetFactory() override = default;`
- L24 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerCDOTextWidgetConstructor`  
`struct FOutlinerCDOTextWidgetConstructor : public FSimpleWidgetConstructor`  
_L29-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L34 _public prototype_ `FOutlinerCDOTextWidgetConstructor();`
- L35 _public prototype_ `FOutlinerCDOTextWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L36 _public prototype_ `virtual ~FOutlinerCDOTextWidgetConstructor() override = default;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerContentBundleWidget.h` (Public)


#### class `UOutlinerContentBundleWidgetFactory`  
`class UOutlinerContentBundleWidgetFactory : public UEditorDataStorageFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `~UOutlinerContentBundleWidgetFactory() override = default;`
- L21 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerContentBundleWidgetConstructor`  
`struct FOutlinerContentBundleWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FOutlinerContentBundleWidgetConstructor();`
- L32 _public prototype_ `~FOutlinerContentBundleWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerDataLayerWidget.h` (Public)


#### class `UOutlinerDataLayerWidgetFactory`  
`class UOutlinerDataLayerWidgetFactory : public UEditorDataStorageFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `~UOutlinerDataLayerWidgetFactory() override = default;`
- L21 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerDataLayerWidgetConstructor`  
`struct FOutlinerDataLayerWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FOutlinerDataLayerWidgetConstructor();`
- L32 _public prototype_ `~FOutlinerDataLayerWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L38 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerIconWidget.h` (Public)


#### class `UOutlinerIconWidgetFactory`  
`class UOutlinerIconWidgetFactory : public UEditorDataStorageFactory`  
_L15-22_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L20 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerIconWidgetLogic`  
`struct FOutlinerIconWidgetLogic`  
_L24-37_
- L26 _public prototype_ `virtual ~FOutlinerIconWidgetLogic() = default;`
- L28 _public prototype_ `virtual const FSlateBrush* GetOverrideBadgeFirstLayer(const UE::Editor::DataStorage::ICoreProvider& Storage, UE::Editor::DataStorage::RowHandle Row) const;`
- L30 _public prototype_ `virtual const FSlateBrush* GetOverrideBadgeSecondLayer(const UE::Editor::DataStorage::ICoreProvider& Storage, UE::Editor::DataStorage::RowHandle Row) const;`
- L32 _public prototype_ `virtual FText GetOverrideTooltip(const UE::Editor::DataStorage::ICoreProvider& Storage, UE::Editor::DataStorage::RowHandle Row) const;`
- L35 _public prototype_ `virtual EOverriddenState GetOverriddenState(const UE::Editor::DataStorage::ICoreProvider& Storage, UE::Editor::DataStorage::RowHandle Row) const;`

#### struct `FOutlinerIconWidgetConstructor`  
`struct FOutlinerIconWidgetConstructor : public FSimpleWidgetConstructor`  
_L40-56_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L45 _public prototype_ `FOutlinerIconWidgetConstructor(const UScriptStruct* InTypeInfo = StaticStruct());`
- L47 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L55 _protected prototype_ `virtual const FOutlinerIconWidgetLogic& GetLogic() const;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerIdNameWidget.h` (Public)


#### class `UOutlinerIdNameWidgetFactory`  
`class UOutlinerIdNameWidgetFactory : public UEditorDataStorageFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `~UOutlinerIdNameWidgetFactory() override = default;`
- L21 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerIdNameWidgetConstructor`  
`struct FOutlinerIdNameWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-43_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FOutlinerIdNameWidgetConstructor();`
- L32 _public prototype_ `~FOutlinerIdNameWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L41 _public prototype_ `virtual FText CreateWidgetDisplayNameText(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerLevelWidget.h` (Public)


#### class `UE::Editor::DataStorage::FLevelWidgetSorter`  
`class FLevelWidgetSorter final : public FColumnSorterInterface`  
_L16-23_
- inherits: `FColumnSorterInterface`
- L19 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L20 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L21 _public prototype_ `virtual ESortType GetSortType() const override;`
- L22 _public prototype_ `virtual FText GetShortName() const override;`

#### class `UE::Editor::DataStorage::FLevelWidgetSearcher`  
`class FLevelWidgetSearcher final : public FColumnSearcherInterface`  
_L25-29_
- inherits: `FColumnSearcherInterface`
- L28 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const override;`

#### class `UOutlinerLevelWidgetFactory`  
`class UOutlinerLevelWidgetFactory : public UEditorDataStorageFactory`  
_L33-42_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L38 _public prototype_ `~UOutlinerLevelWidgetFactory() override = default;`
- L40 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerLevelHeaderWidgetConstructor`  
`struct FOutlinerLevelHeaderWidgetConstructor : public FSimpleWidgetConstructor`  
_L45-59_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L50 _public prototype_ `FOutlinerLevelHeaderWidgetConstructor();`
- L51 _public prototype_ `~FOutlinerLevelHeaderWidgetConstructor() override = default;`
- L53 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerLevelWidgetConstructor`  
`struct FOutlinerLevelWidgetConstructor : public FSimpleWidgetConstructor`  
_L62-90_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L67 _public prototype_ `FOutlinerLevelWidgetConstructor();`
- L68 _public prototype_ `~FOutlinerLevelWidgetConstructor() override = default;`
- L70 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L77 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L81 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L86 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerMobilityWidget.h` (Public)


#### class `UE::Editor::DataStorage::FMobilityWidgetSearcher`  
`class FMobilityWidgetSearcher final : public TColumnSearcherInterface<FTedsActorMobilityColumn>`  
_L18-22_
- inherits: `TColumnSearcherInterface<FTedsActorMobilityColumn>`
- L21 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, const FTedsActorMobilityColumn& Column) const override;`

#### class `UOutlinerMobilityWidgetFactory`  
`class UOutlinerMobilityWidgetFactory : public UEditorDataStorageFactory`  
_L26-35_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `~UOutlinerMobilityWidgetFactory() override = default;`
- L33 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerMobilityWidgetConstructor`  
`struct FOutlinerMobilityWidgetConstructor : public FSimpleWidgetConstructor`  
_L38-57_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L43 _public prototype_ `FOutlinerMobilityWidgetConstructor();`
- L44 _public prototype_ `~FOutlinerMobilityWidgetConstructor() override = default;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L53 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerPinnedWidget.h` (Public)


#### class `UOutlinerPinnedFactory`  
`class UOutlinerPinnedFactory : public UEditorDataStorageFactory`  
_L23-31_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L28 _public prototype_ `~UOutlinerPinnedFactory() override = default;`
- L30 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerPinnedWidgetConstructor`  
`struct FOutlinerPinnedWidgetConstructor : public FSimpleWidgetConstructor`  
_L34-52_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L39 _public prototype_ `FOutlinerPinnedWidgetConstructor();`
- L40 _public prototype_ `~FOutlinerPinnedWidgetConstructor() override = default;`
- L42 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerPinnedHeaderConstructor`  
`struct FOutlinerPinnedHeaderConstructor : public FSimpleWidgetConstructor`  
_L55-69_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L60 _public prototype_ `FOutlinerPinnedHeaderConstructor();`
- L61 _public prototype_ `~FOutlinerPinnedHeaderConstructor() override = default;`
- L63 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class STedsPinnedWidget>`  
_L72-75_
- L74 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `STedsPinnedWidget`  
`class STedsPinnedWidget : public SImage`  
_L78-109_
- inherits: `SImage`
- desc: Widget responsible for displaying and toggling the World Partition pinned state for a single item
- L80 _private typedef_ `using RowHandle = UE::Editor::DataStorage::RowHandle;`
- L83 _public function_ `SLATE_BEGIN_ARGS(STedsPinnedWidget)`
- L84 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow);`
- L89 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L90 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _protected prototype_ `FReply HandleClick();`
- L93 _protected prototype_ `virtual FSlateColor GetForegroundColor() const override;`
- L96 _protected prototype_ `void SetIsPinned(RowHandle InRow, bool bPinned);` — Toggle the pinned state of InRow in the data storage
- L98 _protected member_ `RowHandle TargetRow = UE::Editor::DataStorage::InvalidRowHandle;`
- L100 _protected member_ `TAttribute<bool> bIsPinnedAttr;`
- L101 _protected member_ `TAttribute<bool> bIsSelectedAttr;`
- L104 _private prototype_ `static void CommitPinnedState(UE::Editor::DataStorage::ICoreProvider& DataStorage, RowHandle Row, bool bPinned);`
- L106 _private prototype_ `void GetSelectedRows(TArray<RowHandle>& OutSelectedRows) const;`
- L108 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorage();`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEDSOUTLINER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerSubPackageWidget.h` (Public)


#### class `UOutlinerSubPackageWidgetFactory`  
`class UOutlinerSubPackageWidgetFactory : public UEditorDataStorageFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `~UOutlinerSubPackageWidgetFactory() override = default;`
- L21 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerSubPackageWidgetConstructor`  
`struct FOutlinerSubPackageWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-44_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FOutlinerSubPackageWidgetConstructor();`
- L32 _public prototype_ `~FOutlinerSubPackageWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L41 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerTextWidget.h` (Public)


#### class `UOutlinerTextWidgetFactory`  
`class UOutlinerTextWidgetFactory : public UEditorDataStorageFactory`  
_L18-27_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L23 _public prototype_ `virtual ~UOutlinerTextWidgetFactory() override = default;`
- L25 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerTextWidgetConstructor`  
`struct FOutlinerTextWidgetConstructor : public FSimpleWidgetConstructor`  
_L30-81_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L35 _public prototype_ `FOutlinerTextWidgetConstructor();`
- L36 _public prototype_ `FOutlinerTextWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L37 _public prototype_ `virtual ~FOutlinerTextWidgetConstructor() override = default;`
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L47 _public prototype_ `static void OnCommitText(const FText& NewText, ETextCommit::Type Type, UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle TargetRow);` — Updates the label columns with the given text.
- L48 _public prototype_ `static bool OnVerifyText(const FText& Label, FText& ErrorMessage);`
- L54 _protected prototype_ `virtual TSharedPtr<SWidget> CreateEditableWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Virtual relay function so that deriving Constructors may edit the editable widget without having to override the whole CreateWidget procedure.
- L63 _protected prototype_ `virtual TSharedPtr<SWidget> CreateNonEditableWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments);` — Virtual relay function so that deriving Constructors may edit the non-editable widget without having to override the whole CreateWidget procedure.
- L71 _protected prototype_ `TSharedPtr<SInlineEditableTextBlock> CreateEditableTextBlock( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow) const;` — The actual function that creates the editable widget.
- L77 _protected prototype_ `TSharedPtr<STextBlock> CreateNonEditableTextBlock( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow) const;` — The actual function that creates the non-editable widget.

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerUncachedLightsWidget.h` (Public)


#### class `UE::Editor::DataStorage::FUncachedLightsWidgetSearcher`  
`class FUncachedLightsWidgetSearcher final : public FColumnSearcherInterface`  
_L16-20_
- inherits: `FColumnSearcherInterface`
- L19 _protected prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const override;`

#### class `UE::Editor::DataStorage::FUncachedLightsWidgetSorter`  
`class FUncachedLightsWidgetSorter final : public FColumnSorterInterface`  
_L22-32_
- inherits: `FColumnSorterInterface`
- L25 _public prototype_ `virtual ESortType GetSortType() const override;`
- L27 _public prototype_ `virtual FText GetShortName() const override;`
- L29 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L31 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`

#### class `UOutlinerUncachedLightsWidgetFactory`  
`class UOutlinerUncachedLightsWidgetFactory : public UEditorDataStorageFactory`  
_L36-45_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L41 _public prototype_ `~UOutlinerUncachedLightsWidgetFactory() override = default;`
- L43 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerUncachedLightsWidgetConstructor`  
`struct FOutlinerUncachedLightsWidgetConstructor : public FSimpleWidgetConstructor`  
_L48-74_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L53 _public prototype_ `FOutlinerUncachedLightsWidgetConstructor();`
- L54 _public prototype_ `~FOutlinerUncachedLightsWidgetConstructor() override = default;`
- L56 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L63 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`
- L67 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L71 _public prototype_ `virtual TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerUnsavedWidget.h` (Public)


#### class `UE::Editor::DataStorage::FUnsavedWidgetSorter`  
`class FUnsavedWidgetSorter final : public FColumnSorterInterface`  
_L13-20_
- inherits: `FColumnSorterInterface`
- L16 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L17 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`
- L18 _public prototype_ `virtual ESortType GetSortType() const override;`
- L19 _public prototype_ `virtual FText GetShortName() const override;`

#### class `UOutlinerUnsavedWidgetFactory`  
`class UOutlinerUnsavedWidgetFactory : public UEditorDataStorageFactory`  
_L24-33_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L29 _public prototype_ `~UOutlinerUnsavedWidgetFactory() override = default;`
- L31 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerUnsavedWidgetConstructor`  
`struct FOutlinerUnsavedWidgetConstructor : public FSimpleWidgetConstructor`  
_L36-58_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L41 _public prototype_ `FOutlinerUnsavedWidgetConstructor();`
- L42 _public prototype_ `~FOutlinerUnsavedWidgetConstructor() override = default;`
- L44 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L51 _public prototype_ `TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L56 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### struct `FOutlinerUnsavedHeaderConstructor`  
`struct FOutlinerUnsavedHeaderConstructor : public FSimpleWidgetConstructor`  
_L61-75_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L66 _public prototype_ `FOutlinerUnsavedHeaderConstructor();`
- L67 _public prototype_ `~FOutlinerUnsavedHeaderConstructor() override = default;`
- L69 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerVisibilityWidget.h` (Public)


#### class `UOutlinerVisibilityWidgetFactory`  
`class UOutlinerVisibilityWidgetFactory : public UEditorDataStorageFactory`  
_L26-34_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L31 _public prototype_ `~UOutlinerVisibilityWidgetFactory() override = default;`
- L33 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### class `UOutlinerVisibilityHeaderFactory`  
`class UOutlinerVisibilityHeaderFactory : public UEditorDataStorageFactory`  
_L37-45_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L42 _public prototype_ `~UOutlinerVisibilityHeaderFactory() override = default;`
- L44 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerVisibilityWidgetConstructor`  
`struct FOutlinerVisibilityWidgetConstructor : public FSimpleWidgetConstructor`  
_L48-62_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L53 _public prototype_ `FOutlinerVisibilityWidgetConstructor();`
- L54 _public prototype_ `~FOutlinerVisibilityWidgetConstructor() override = default;`
- L56 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `FOutlinerVisibilityHeaderConstructor`  
`struct FOutlinerVisibilityHeaderConstructor : public FSimpleWidgetConstructor`  
_L65-79_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L70 _public prototype_ `FOutlinerVisibilityHeaderConstructor();`
- L71 _public prototype_ `~FOutlinerVisibilityHeaderConstructor() override = default;`
- L73 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class STedsOutlinerVisibilityWidget>`  
_L82-85_
- L84 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `STedsOutlinerVisibilityWidget`  
`class STedsOutlinerVisibilityWidget : public SImage`  
_L88-181_
- inherits: `SImage`
- desc: Widget responsible for managing the visibility for a single item
- L90 _private typedef_ `using RowHandle = UE::Editor::DataStorage::RowHandle;`
- L93 _public function_ `SLATE_BEGIN_ARGS(STedsOutlinerVisibilityWidget)`
- L94 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const RowHandle& InTargetRow, const RowHandle& InWidgetRow);`
- L102 _protected prototype_ `virtual bool IsEnabled() const;` — Returns whether the widget is enabled or not
- L105 _protected prototype_ `virtual bool CanCommitVisibility(UE::Editor::DataStorage::ICoreProvider& DataStorage, RowHandle Row) const;` — Returns whether the item on the given row can commit visibility
- L108 _protected prototype_ `virtual const FSlateBrush* GetBrush() const;` — Get the brush for this widget
- L111 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Start a new drag/drop operation for this widget
- L114 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;` — If a visibility drag drop operation has entered this widget, set its item to the new visibility state
- L116 _protected prototype_ `FReply HandleClick();`
- L118 _protected prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L121 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Called when the mouse button is pressed down on this widget
- L124 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — Process a mouse up message
- L127 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;` — Called when this widget had captured the mouse, but that capture has been revoked for some reason.
- L130 _protected function_ `virtual bool ShouldPropagateVisibilityChangeOnChildren() const` — Whether visibility change should propagate down to children.
- L132 _protected prototype_ `virtual FSlateColor GetForegroundColor() const;`
- L135 _protected prototype_ `bool IsVisible() const;` — Check if the TargetRow Object is Visible
- L138 _protected prototype_ `bool IsSelected() const;` — Check if the TargetRow Object is Selected
- L141 _protected prototype_ `void SetIsVisible(RowHandle InRow, const bool bVisible, UE::Editor::DataStorage::FRowHandleArray* ChangedRowsToAppendTo = nullptr);` — Set the item this widget is responsible for to be hidden or shown
- L144 _protected member_ `RowHandle TargetRow = UE::Editor::DataStorage::InvalidRowHandle;`
- L145 _protected member_ `RowHandle WidgetRow = UE::Editor::DataStorage::InvalidRowHandle;`
- L148 _protected member_ `TUniquePtr<FScopedTransaction> UndoTransaction;` — Scoped undo transaction
- L151 _protected member_ `const FSlateBrush* VisibleHoveredBrush = nullptr;` — Visibility brushes for the various states
- L152 _protected member_ `const FSlateBrush* VisibleNotHoveredBrush = nullptr;`
- L153 _protected member_ `const FSlateBrush* NotVisibleHoveredBrush = nullptr;`
- L154 _protected member_ `const FSlateBrush* NotVisibleNotHoveredBrush = nullptr;`
- L159 _private prototype_ `void CommitVisibility(UE::Editor::DataStorage::ICoreProvider& DataStorage, RowHandle Row, bool bVisible, UE::Editor::DataStorage::FRowHandleArray* ChangedRowsToAppendTo);` — Commit the visibility state into the Rows DataStorage. Will trigger a SyncBackToWorld manually but the object is never dirtied.
- L163 _private prototype_ `void SetVisibility_Recursive(UE::Editor::DataStorage::ICoreProvider& DataStorage, RowHandle Row, TSharedPtr<UE::Editor::DataStorage::IHierarchyViewerDataInterface> HierarchyData, bool bVisible, UE::Editor::DataStorage::FRowHandleArray* ChangedRowsToAppendTo);` — Recursive internal method to set visibility on a row and all its children.
- L168 _private prototype_ `void SetVisibility_Recursive(UE::Editor::DataStorage::ICoreProvider& DataStorage, FSceneOutlinerTreeItemPtr TreeItem, bool bVisible, UE::Editor::DataStorage::FRowHandleArray* ChangedRowsToAppendTo);` — Legacy method to work on Outliner tree items since they don't use the new hierarchy interface yet.
- L172 _private prototype_ `FSceneOutlinerTreeItemPtr GetTreeItem(RowHandle InRow) const;` — Returns the tree item associated with this widget.
- L174 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorage();`
- L175 _private prototype_ `static UE::Editor::DataStorage::ICoreProvider* GetDataStorageUI();`
- L176 _private prototype_ `static UE::Editor::DataStorage::ICompatibilityProvider* GetDataStorageCompatibility();`
- L178 _private prototype_ `void GetSelectedRows(TArray<RowHandle>& OutSelectedRows) const;`
- L180 _private member_ `TWeakObjectPtr<const UScriptStruct> EditorObjectHierarchyParentTag;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEDSOUTLINER_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Editor` (scope `UE`)
- L17 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/OutlinerWorldLevelLabelWidget.h` (Public)


#### class `UOutlinerWorldLevelLabelWidgetFactory`  
`class UOutlinerWorldLevelLabelWidgetFactory : public UEditorDataStorageFactory`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L15 _public prototype_ `virtual ~UOutlinerWorldLevelLabelWidgetFactory() override = default;`
- L17 _public prototype_ `virtual void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FOutlinerWorldLevelLabelWidgetConstructor`  
`struct FOutlinerWorldLevelLabelWidgetConstructor : public FOutlinerTextWidgetConstructor`  
_L22-38_
- reflection: `USTRUCT()`
- inherits: `FOutlinerTextWidgetConstructor`
- L27 _public prototype_ `FOutlinerWorldLevelLabelWidgetConstructor();`
- L28 _public prototype_ `FOutlinerWorldLevelLabelWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L29 _public prototype_ `virtual ~FOutlinerWorldLevelLabelWidgetConstructor() override = default;`
- L32 _protected prototype_ `virtual TSharedPtr<SWidget> CreateEditableWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/SceneOutlinerWidget.h` (Public)


#### class `UTedsOutlinerWidgetFactory`  
`class UTedsOutlinerWidgetFactory : public UEditorDataStorageFactory`  
_L40-60_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L45 _public prototype_ `~UTedsOutlinerWidgetFactory() override = default;`
- L47 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L49 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L53 _public typedef_ `using FExternalFilterProvider = TFunction<void(TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>&, UE::Editor::DataStorage::ICoreProvider*)>;` — Allows external filters to be provided to the Outliner
- L54 _public prototype_ `void RegisterExternalFilterProvider(FName ProviderName, FExternalFilterProvider Provider);`
- L55 _public prototype_ `void UnregisterExternalFilterProvider(FName ProviderName);`
- L56 _public prototype_ `void CallExternalFilterProviders(TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters, UE::Editor::DataStorage::ICoreProvider* DataStorage) const;`
- L59 _private member_ `TMap<FName, FExternalFilterProvider> ExternalFilterProviders;`

#### struct `FTedsSceneOutlinerWidgetConstructor`  
`struct FTedsSceneOutlinerWidgetConstructor : public FSimpleWidgetConstructor`  
_L63-140_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L68 _public prototype_ `FTedsSceneOutlinerWidgetConstructor();`
- L69 _public prototype_ `~FTedsSceneOutlinerWidgetConstructor() override = default;`
- L75 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;` — Constructs the Outliner Widget. If overridden, ensure that the resulting SSceneOutliner is referenced in an added FSceneOutlinerColumn on the WidgetRow and the TabIdentifier is gotten via metadata
- L83 _public prototype_ `virtual void PostOutlinerCreated(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle OutlinerRow);` — Called after the Outliner and its row are created. Override to perform post-creation setup such as adding the settings cache column
- L85 _public prototype_ `virtual void GetSceneOutlinerInitializationOptions(FSceneOutlinerInitializationOptions& InitOptions);` — Adds parameters to the default (non-TEDS) SceneOutlinerInitializationOptions used to create the SSceneOutliner
- L87 _public prototype_ `virtual UE::Editor::DataStorage::FQueryDescription GetQueryDescription() const;` — Gets the query description that will be used to populate rows in this Teds Outliner
- L89 _public prototype_ `virtual UE::Editor::Outliner::FTedsOutlinerColumnDescription GetColumnDescription() const;` — Gets the columns to display in this Teds Outliner and any additional metadata
- L91 _public prototype_ `virtual void GetFilters(UE::Editor::DataStorage::ICoreProvider* DataStorage, TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters) const;` — Adds FTedsOutlinerFilters to an array used to populate the Outliner FilterBar
- L94 _public prototype_ `virtual void GetShowOptionsFilters(UE::Editor::DataStorage::ICoreProvider* DataStorage, TMap<FName, TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters) const;` — Adds FTedsOutlinerFilters to an array used to populate the Outliner Show Options
- L96 _public prototype_ `virtual void GetInitializeViewMenuExtender(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams);`
- L98 _public prototype_ `virtual void GetOnItemDoubleClick(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams);` — Binds the delegate called before default double-click behavior
- L100 _public prototype_ `virtual void GetOnCanPopulate(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams);` — Binds the delegate called during Tick for whether the Outliner should Populate
- L102 _public prototype_ `virtual void GetInitializeOptionsMenuExtender(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams, UE::Editor::DataStorage::ICoreProvider* DataStorage);` — Binds the delegate that injects entries into the "Options" section of the View Menu
- L104 _public prototype_ `virtual void GetExpansionStateBridge(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams);` — Binds the delegate called on item expansion state change
- L106 _public prototype_ `virtual void GetAdditionalObserverQueries(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams);` — Gets any additional observer queries
- L108 _public prototype_ `virtual void GetOnCustomAddToToolbar(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams, UE::Editor::DataStorage::ICoreProvider* DataStorage);` — Binds the delegate fired by the mode's CustomAddToToolbar so the widget can extend the outliner toolbar
- L110 _public prototype_ `virtual void GetOnRegisterInteractiveFilters(UE::Editor::Outliner::FTedsOutlinerParams& OutlinerParams, UE::Editor::DataStorage::ICoreProvider* DataStorage);` — Registers interactive filters
- L112 _public prototype_ `virtual bool ShowRowHandleColumn() const;` — Whether we should add the Row Handle column to the Outliner, by default this is controlled by a CVar
- L114 _public prototype_ `virtual bool ForceShowParents() const;` — Whether Parent rows should be force added back when filtered or searched out
- L116 _public prototype_ `virtual bool UseDefaultObservers() const;` — Whether the Teds Outliner will create observers to track addition/removal of rows and update
- L118 _public prototype_ `virtual bool ShowViewButton() const;` — Whether the Teds Outliner will create a view button (settings cog) pre-populated with hierarchy actions
- L120 _public prototype_ `virtual TSharedPtr<UE::Editor::Outliner::ITedsOutlinerHierarchyDataInterface> GetHierarchyData(UE::Editor::DataStorage::ICoreProvider* DataStorage) const;` — Gets the defined hierarchy to show, if nullptr, a flat list will be presented
- L122 _public prototype_ `virtual UTypedElementSelectionSet* GetSelectionSet() const;` — Gets the selection set to use for this Outliner, if nullptr it doesn't propagate tree selection through TypedElementSelectionInterface
- L125 _public prototype_ `GetLegacyFilterConversionMap(UE::Editor::DataStorage::ICoreProvider* DataStorage) const;`
- L129 _protected prototype_ `void GetLevelEditorSceneOutlinerInitOptions(FSceneOutlinerInitializationOptions& OutInitOptions) const;` — Gets the FSceneOutlinerInitializationOptions defined in the Level Editor for the Scene Outliner to be used as the default
- L131 _protected member_ `FName TabIdentifier;` — Tab Id that can be used by the parameter creation function
- L134 _private prototype_ `void AddFavoriteFilters(UE::Editor::DataStorage::ICoreProvider* DataStorage, TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters) const;`
- L135 _private prototype_ `void AddAlertFilters(UE::Editor::DataStorage::ICoreProvider* DataStorage, TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters) const;`
- L136 _private prototype_ `void AddSCCFilters(UE::Editor::DataStorage::ICoreProvider* DataStorage, TArray<TSharedPtr<UE::Editor::Outliner::FTedsOutlinerFilter>>& Filters) const;`
- L139 _private member_ `TSharedPtr<UE::Editor::Outliner::FTedsSceneOutlinerWorldFilter> WorldFilter;` — Store the World filter so it can be referenced by the World Picker post-creation

#### class `FTedsSceneOutlinerActorEditorContextSubsystemFilter`  
`class FTedsSceneOutlinerActorEditorContextSubsystemFilter : public UE::Editor::Outliner::FTedsOutlinerFilter`  
_L142-159_
- inherits: `UE::Editor::Outliner::FTedsOutlinerFilter`
- L145 _public prototype_ `FTedsSceneOutlinerActorEditorContextSubsystemFilter(const FName& InFilterName, const FText InFilterDisplayName, const FText InFilterTooltip, const UE::Editor::DataStorage::Queries::TConstQueryFunction<bool>& InFilterQuery);`
- L148 _public prototype_ `~FTedsSceneOutlinerActorEditorContextSubsystemFilter();`
- L150 _public prototype_ `virtual void ActiveStateChanged(bool bActive) override;`
- L151 _public prototype_ `void OnActorEditorContextSubsystemChanged() const;`
- L154 _protected member_ `IWorldPartitionEditorModule* WorldPartitionModule = nullptr;`
- L155 _protected member_ `UE::Editor::DataStorage::ICoreProvider* DataStorage = nullptr;`
- L158 _private member_ `FDelegateHandle OnActorEditorContextSubsystemChangedDelegate;`

#### class `FTedsSceneOutlinerCurrentDataLayerFilter`  
`class FTedsSceneOutlinerCurrentDataLayerFilter : public FTedsSceneOutlinerActorEditorContextSubsystemFilter`  
_L161-165_
- inherits: `FTedsSceneOutlinerActorEditorContextSubsystemFilter`
- L164 _public prototype_ `FTedsSceneOutlinerCurrentDataLayerFilter(const FName& InFilterName);`

#### class `FTedsSceneOutlinerCurrentContentBundleFilter`  
`class FTedsSceneOutlinerCurrentContentBundleFilter : public FTedsSceneOutlinerActorEditorContextSubsystemFilter`  
_L167-171_
- inherits: `FTedsSceneOutlinerActorEditorContextSubsystemFilter`
- L170 _public prototype_ `FTedsSceneOutlinerCurrentContentBundleFilter(const FName& InFilterName);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API TEDSOUTLINER_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Editor` (scope `UE`)
- L23 _namespace_ `namespace Outliner` (scope `UE::Editor`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Editor` (scope `UE`)
- L32 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/SocketWidget.h` (Public)


#### class `USocketWidgetFactory`  
`class USocketWidgetFactory : public UEditorDataStorageFactory`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L19 _public prototype_ `~USocketWidgetFactory() override = default;`
- L21 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FSocketWidgetConstructor`  
`struct FSocketWidgetConstructor : public FSimpleWidgetConstructor`  
_L26-43_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L31 _public prototype_ `FSocketWidgetConstructor();`
- L32 _public prototype_ `~FSocketWidgetConstructor() override = default;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L41 _public prototype_ `virtual FText CreateWidgetDisplayNameText( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle Row = UE::Editor::DataStorage::InvalidRowHandle) const override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/TypeInfoWidget.h` (Public)


#### class `UE::Editor::DataStorage::FTypeInfoWidgetSorter`  
`class FTypeInfoWidgetSorter final : public FColumnSorterInterface`  
_L16-23_
- inherits: `FColumnSorterInterface`
- L19 _public prototype_ `virtual FText GetShortName() const override;`
- L20 _public prototype_ `virtual ESortType GetSortType() const override;`
- L21 _public prototype_ `virtual int32 Compare(const ICoreProvider& Storage, RowHandle Left, RowHandle Right) const override;`
- L22 _public prototype_ `virtual FPrefixInfo CalculatePrefix(const ICoreProvider& Storage, RowHandle Row, uint32 ByteIndex) const override;`

#### class `UE::Editor::DataStorage::FTypeInfoWidgetSearcher`  
`class FTypeInfoWidgetSearcher final : public FColumnSearcherInterface`  
_L25-29_
- inherits: `FColumnSearcherInterface`
- L28 _public prototype_ `virtual void GetSearchableString(FString& SearchableString, const ICoreProvider& Storage, RowHandle Row) const override;`

#### class `UTypeInfoWidgetFactory`  
`class UTypeInfoWidgetFactory : public UEditorDataStorageFactory`  
_L33-42_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L38 _public prototype_ `~UTypeInfoWidgetFactory() override = default;`
- L40 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FTypeInfoWidgetConstructor`  
`struct FTypeInfoWidgetConstructor : public FSimpleWidgetConstructor`  
_L45-76_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L50 _public prototype_ `FTypeInfoWidgetConstructor();`
- L51 _public prototype_ `~FTypeInfoWidgetConstructor() override = default;`
- L54 _protected prototype_ `explicit FTypeInfoWidgetConstructor(const UScriptStruct* InTypeInfo);`
- L56 _protected prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L63 _protected prototype_ `TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSorterInterface>> ConstructColumnSorters( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L68 _protected prototype_ `TArray<TSharedPtr<const UE::Editor::DataStorage::FColumnSearcherInterface>> ConstructColumnSearchers( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L75 _protected prototype_ `static TSharedRef<SWidget> CreateTextWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TEDSOUTLINER_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsOutliner/Public/Widgets/VisibilityWidget.h` (Public)


#### class `UVisibilityWidgetFactory`  
`class UVisibilityWidgetFactory : public UEditorDataStorageFactory`  
_L18-26_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L23 _public prototype_ `~UVisibilityWidgetFactory() override = default;`
- L25 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FVisibilityWidgetConstructor`  
`struct FVisibilityWidgetConstructor : public FSimpleWidgetConstructor`  
_L29-43_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L34 _public prototype_ `FVisibilityWidgetConstructor();`
- L35 _public prototype_ `~FVisibilityWidgetConstructor() override = default;`
- L37 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API TEDSOUTLINER_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
