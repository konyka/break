# Plugins / TedsDebugger

- module root: `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger`
- headers: 15; symbols: 351
- symbol kinds: class=16, delegate=1, enum=3, enumerator=13, function=15, member=97, namespace=69, prototype=126, struct=7, typedef=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ApplicationCore, EditorWidgets, InputCore, SceneOutliner, Slate, SlateCore, TedsOutliner, TedsQueryStack, TedsTableViewer, ToolWidgets, TypedElementFramework, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/QueryEditor/TedsQueryEditor.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SQueryEditorWidget`  
`class SQueryEditorWidget : public SCompoundWidget`  
_L17-48_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SQueryEditorWidget)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FTedsQueryEditorModel& QueryEditorModel);`
- L35 _private prototype_ `TSharedRef<SWidget> CreateToolbar();`
- L36 _private prototype_ `TSharedRef<SWidget> GetViewModesMenuWidget();`
- L37 _private prototype_ `FText GetCurrentViewModeText() const;`
- L38 _private prototype_ `static FText GetViewModeAsText(ETableViewMode::Type InViewMode);`
- L39 _private prototype_ `FSlateIcon GetCurrentViewModeIcon() const;`
- L40 _private prototype_ `static FSlateIcon GetViewModeAsIcon(ETableViewMode::Type InViewMode);`
- L44 _private member_ `FTedsQueryEditorModel* Model = nullptr;`
- L45 _private member_ `TArray<TSharedPtr<ColumnComboItem>> ComboItems;`
- L46 _private member_ `TSharedPtr<SResultsView> ResultsView;`
- L47 _private member_ `TSharedPtr<SHierarchyComboWidget> HierarchyComboWidget;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L12 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/QueryEditor/TedsQueryEditorModel.h` (Private)


#### enum `UE::Editor::DataStorage::Debug::QueryEditor::EOperatorType`  
`enum class EOperatorType : uint32`  
_L17-25_
- L19 _public enumerator_ `Invalid` — Not initialized
- L20 _public enumerator_ `Select`
- L21 _public enumerator_ `All`
- L22 _public enumerator_ `Any`
- L23 _public enumerator_ `None`
- L24 _public enumerator_ `Unset` — Not associated with a set

#### enum `UE::Editor::DataStorage::Debug::QueryEditor::EErrorCode`  
`enum class EErrorCode`  
_L27-34_
- L29 _public enumerator_ `Success`
- L30 _public enumerator_ `AlreadyExists`
- L31 _public enumerator_ `DoesNotExist`
- L32 _public enumerator_ `InvalidParameter`
- L33 _public enumerator_ `ConstraintViolation`

#### struct `UE::Editor::DataStorage::Debug::QueryEditor::FConditionEntryHandle`  
`struct FConditionEntryHandle`  
_L36-48_
- L38 _public prototype_ `FConditionEntryHandle() = default;`
- L39 _public prototype_ `bool operator==(const FConditionEntryHandle& Rhs) const;`
- L40 _public prototype_ `bool IsValid() const;`
- L41 _public prototype_ `void Reset();`
- L47 _private member_ `FName Id = NAME_None;` — Unique ID for a condition Used to identify the entry by external code (ie. list views)

#### class `UE::Editor::DataStorage::Debug::QueryEditor::FTedsQueryEditorModel`  
`class FTedsQueryEditorModel`  
_L52-145_
- L55 _public prototype_ `explicit FTedsQueryEditorModel(ICoreProvider& InDataStorageProvider);`
- L57 _public prototype_ `void Reset();`
- L58 _public prototype_ `ICoreProvider& GetTedsInterface();`
- L59 _public prototype_ `const ICoreProvider& GetTedsInterface() const;`
- L61 _public prototype_ `FQueryDescription GenerateQueryDescription();`
- L65 _public prototype_ `FQueryDescription GenerateNoSelectQueryDescription();` — Special function to generate a description that puts the Select elements as All Conditions This is helpful for using a Count query type or for the TableViewer which requires the row query to have no select items
- L67 _public prototype_ `int32 CountConditionsOfOperator(EOperatorType OperatorType) const;`
- L73 _public prototype_ `void ForEachCondition(TFunctionRef<void(const FTedsQueryEditorModel& Model, FConditionEntryHandle Handle)> Function) const;` — Runs given function over all conditions that match the condition type The order of the conditions is not guaranteeds to be the same each run.
- L75 _public prototype_ `void ForEachCondition(TFunctionRef<void(FTedsQueryEditorModel& Model, FConditionEntryHandle Handle)> Function);`
- L77 _public prototype_ `EErrorCode GenerateValidOperatorChoices(EOperatorType OperatorType, TFunctionRef<void(const FTedsQueryEditorModel& Model, const FConditionEntryHandle Handle)> Function);`
- L79 _public prototype_ `EOperatorType GetOperatorType(FConditionEntryHandle Handle) const;`
- L80 _public prototype_ `TPair<bool, EErrorCode> CanSetOperatorType(FConditionEntryHandle Handle, EOperatorType OperatorType);`
- L90 _public prototype_ `EErrorCode SetOperatorType(FConditionEntryHandle Handle, EOperatorType OperatorType);` — @param OperatorType @param ColumnType - Column or tag type @return Success - Column or tag added to collection DuplicateInSameCondition - Column or tag already present in condition collection ExistsInOtherCondition - Column or tag present in a different condition collection InvalidParameter - Column or tag cannot be added to condition collection
- L92 _public prototype_ `const UScriptStruct* GetColumnScriptStruct(FConditionEntryHandle Handle) const;`
- L94 _public function_ `FTedsQueryEditorModel_ModelChanged& GetModelChangedDelegate()`
- L97 _public function_ `FTedsQueryEditorModel_ModelChanged& OnTableViewerRefreshRequired()` — Fired when the table viewer widget needs to be rebuilt (hierarchy or row visibility settings changed)
- L99 _public prototype_ `void SetShowHiddenRows(bool bInShowHiddenRows);`
- L100 _public prototype_ `bool GetShowHiddenRows() const;`
- L102 _public prototype_ `void RegenerateColumnsList();`
- L104 _public prototype_ `void SetHierarchy(const FName& InHierarchy);`
- L105 _public prototype_ `FName GetHierarchyName() const;`
- L106 _public prototype_ `FHierarchyHandle GetHierarchy() const;`
- L109 _public prototype_ `void SetRelationType(RelationTypeHandle InRelationType);` — Relation-type hierarchy selection (mutually exclusive with SetHierarchy)
- L110 _public prototype_ `bool HasRelationType() const;`
- L111 _public prototype_ `RelationTypeHandle GetRelationType() const;`
- L126 _private prototype_ `FConditionEntryInternal* FindEntryByHandle(FConditionEntryHandle Handle);`
- L127 _private prototype_ `const FConditionEntryInternal* FindEntryByHandle(FConditionEntryHandle Handle) const;`
- L129 _private member_ `ICoreProvider& EditorDataStorageProvider;`
- L131 _private member_ `TArray<FConditionEntryInternal> Conditions;`
- L132 _private member_ `FTedsQueryEditorModel_ModelChanged ModelChangedDelegate;`
- L134 _private member_ `uint64 CurrentVersion = 0;`
- L135 _private member_ `uint64 GeneratedVersion = 0;`
- L136 _private member_ `QueryHandle QueryHandle;`
- L140 _private member_ `FName CurrentHierarchy;` — The current hierarchy being viewed (only applicable for hierarchy based widgets). CurrentHierarchy and CurrentRelationType are mutually exclusive — only one is active at a time.
- L141 _private member_ `TOptional<RelationTypeHandle> CurrentRelationType;`
- L142 _private member_ `FTedsQueryEditorModel_ModelChanged TableViewerRefreshRequiredDelegate;`
- L144 _private member_ `bool bShowHiddenRows = false;`

#### struct `UE::Editor::DataStorage::Debug::QueryEditor::FTedsQueryEditorModel::FConditionEntryInternal`  
`struct FConditionEntryInternal`  
_L115-124_
- L119 _public member_ `FName Id;` — Unique ID for a condition Used to identify the entry by external code (ie. list views)
- L120 _public member_ `const UScriptStruct* Struct;`
- L121 _public member_ `EOperatorType OperatorType;`
- L123 _public function_ `bool operator==(const FConditionEntryHandle& Rhs) const`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L13 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTedsQueryEditorModel_ModelChanged);`
- L50 _prototype_ `DECLARE_MULTICAST_DELEGATE(FTedsQueryEditorModel_ModelChanged);` (scope `UE::Editor::DataStorage::Debug::QueryEditor`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/STedsDebugger.h` (Private)


#### class `UE::Editor::DataStorage::Debug::STedsDebugger`  
`class STedsDebugger : public SCompoundWidget`  
_L17-60_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(STedsDebugger)`
- L27 _public prototype_ `STedsDebugger() = default;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SDockTab>& ConstructUnderMajorTab, const TSharedPtr<SWindow>& ConstructUnderWindow);` — Constructs the debugger. @param InArgs The Slate argument list. @param ConstructUnderMajorTab The major tab which will contain the session front-end. @param ConstructUnderWindow The window in which this widget is being constructed.
- L39 _private prototype_ `QueryEditor::FTedsQueryEditorModel* FindQueryEditorModel(const EQueryEditorTabs QueryTabIdentifier);`
- L40 _private prototype_ `static FName GetQueryTabName(const EQueryEditorTabs QueryTabIdentifier);`
- L41 _private prototype_ `TSharedRef<SDockTab> SpawnToolbar(const FSpawnTabArgs& Args);`
- L42 _private prototype_ `TSharedRef<SDockTab> SpawnQueryEditorTab(const FSpawnTabArgs& Args, const EQueryEditorTabs QueryTabIdentifier);`
- L43 _private prototype_ `TSharedRef<SDockTab> SpawnTableTab(const FSpawnTabArgs& Args);`
- L44 _private prototype_ `TSharedRef<SDockTab> SpawnDiscoverTab(const FSpawnTabArgs& Args);`
- L45 _private prototype_ `TSharedRef<SDockTab> SpawnContextHierarchyTab(const FSpawnTabArgs& Args);`
- L46 _private prototype_ `void FillWindowMenu( FMenuBuilder& MenuBuilder);`
- L48 _private prototype_ `void RegisterTabSpawners();`
- L53 _private member_ `TSharedPtr<FTabManager> TabManager;` — Holds the tab manager that manages the front-end's tabs.
- L56 _private member_ `QueryHandle TableViewerQuery;` — Table Viewer
- L58 _private member_ `static constexpr int32 MaxQueryEditorTabs = 4;`
- L59 _private member_ `TArray<TUniquePtr<QueryEditor::FTedsQueryEditorModel>, TInlineAllocator<MaxQueryEditorTabs>> Models;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L13 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/TedsDebuggerModule.h` (Private)


#### class `UE::Editor::DataStorage::Debug::FTedsDebuggerModule`  
`class FTedsDebuggerModule : public IModuleInterface`  
_L23-42_
- inherits: `IModuleInterface`
- desc: Implements the Teds Debugger module.
- L28 _public prototype_ `FTedsDebuggerModule() = default;`
- L31 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L32 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _private prototype_ `void RegisterTabSpawners();`
- L36 _private prototype_ `void UnregisterTabSpawners() const;`
- L38 _private prototype_ `TSharedRef<SDockTab> OpenTedsDebuggerTab(const FSpawnTabArgs& SpawnTabArgs);`
- L41 _private member_ `TWeakPtr<STedsDebugger> TedsDebuggerInstance;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L16 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/QueryEditor/TedsConditionCollectionViewWidget.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SConditionCollectionViewWidget`  
`class SConditionCollectionViewWidget : public SCompoundWidget`  
_L16-36_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS( SConditionCollectionViewWidget )`
- L22 _public prototype_ `~SConditionCollectionViewWidget() override;`
- L23 _public prototype_ `void Construct(const FArguments& InArgs, FTedsQueryEditorModel& InModel, EOperatorType InOperatorType);`
- L24 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L28 _private prototype_ `void OnModelChanged();`
- L30 _private member_ `FTedsQueryEditorModel* Model = nullptr;`
- L31 _private member_ `EOperatorType OperatorType = EOperatorType::Unset;`
- L32 _private member_ `FDelegateHandle OnModelChangedDelegate;`
- L34 _private member_ `TSharedPtr<SWrapBox> ColumnButtonWrap;`
- L35 _private member_ `FButtonStyle ButtonStyle;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L11 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L11 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/QueryEditor/TedsConditionSelectionCollectionWidget.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SConditionSelectionCollectionWidget`  
`class SConditionSelectionCollectionWidget : public SCompoundWidget`  
_L13-23_
- inherits: `SCompoundWidget`
- desc: Widget which shows and allows editing of columns/tabs within a given condition
- L16 _public function_ `SLATE_BEGIN_ARGS( SConditionSelectionCollectionWidget )`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FTedsQueryEditorModel& InModel);`
- L22 _private member_ `FTedsQueryEditorModel* Model = nullptr;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Editor` (scope `UE`)
- L6 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L6 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L6 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/QueryEditor/TedsConditionSelectionComboWidget.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SConditionComboWidget`  
`class SConditionComboWidget : public SComboButton`  
_L17-62_
- inherits: `SComboButton`
- L20 _public function_ `SLATE_BEGIN_ARGS( SConditionComboWidget )`
- L23 _public prototype_ `~SConditionComboWidget() override;`
- L24 _public prototype_ `void OnConditionCollectionChanged();`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, FTedsQueryEditorModel& InModel, QueryEditor::EOperatorType InConditionType);`
- L30 _private prototype_ `void PopulateComboItems();`
- L31 _private prototype_ `void FilterComboItems();`
- L33 _private prototype_ `void OnSelectionChanged(TSharedPtr<FComboItem> NewSelection, ESelectInfo::Type SelectInfo);`
- L34 _private prototype_ `FReply OnKeyDownHandler(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L35 _private prototype_ `TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FComboItem> Item);`
- L36 _private prototype_ `TSharedRef<ITableRow> GenerateMenuItemRow(TSharedPtr<FComboItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L38 _private prototype_ `void OnSearchBoxTextChanged(const FText& InSearchText);`
- L39 _private prototype_ `void OnSearchBoxTextCommitted(const FText& InSearchText, ETextCommit::Type InCommitType);`
- L41 _private prototype_ `void SelectItem(TSharedPtr<FComboItem> InItem);`
- L43 _private member_ `FTedsQueryEditorModel* Model = nullptr;`
- L44 _private member_ `QueryEditor::EOperatorType ConditionType = QueryEditor::EOperatorType::Invalid;`
- L46 _private member_ `FDelegateHandle ConditionCollectionChangedHandle;`
- L49 _private member_ `FText SearchText;` — Updated whenever search text is changed
- L51 _private member_ `TArray<TSharedPtr<FComboItem>> ComboItems;`
- L52 _private member_ `TArray<TSharedPtr<FComboItem>> FilteredComboItems;`
- L55 _private member_ `TSharedPtr<SWidget> ComboBoxMenuContent;` — Widget that gets passed as the combo box content containing the list and search bar
- L58 _private member_ `TSharedPtr<SListView<TSharedPtr<FComboItem>>> ComboListView;` — The ListView that pops up with the available columns and tags
- L59 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L61 _private member_ `TSharedPtr<SFilterBar<TSharedPtr<FComboItem>>> FilterThing;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L12 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L12 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/QueryEditor/TedsHierarchySelectionComboWidget.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SHierarchyComboWidget`  
`class SHierarchyComboWidget : public SCompoundWidget`  
_L10-28_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS( SHierarchyComboWidget )`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FTedsQueryEditorModel& InModel);`
- L19 _protected prototype_ `void GenerateHierarchyList();`
- L22 _protected member_ `TArray<TSharedPtr<FString>> Hierarchies;`
- L25 _protected member_ `TMap<FString, RelationTypeHandle> RelationHandleByDisplayName;` — Maps display name (e.g. "InheritsFrom (relation)") → RelationTypeHandle for entries added from ListRelationTypes. Entries not present in this map are named hierarchies resolved via FindHierarchyByName.
- L26 _protected member_ `FTedsQueryEditorModel* Model = nullptr;`
- L27 _protected member_ `TSharedPtr<SSearchableComboBox> SearchableComboBox;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Editor` (scope `UE`)
- L8 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L8 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L8 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/QueryEditor/TedsQueryEditorResultsView.h` (Private)


#### class `UE::Editor::DataStorage::Debug::QueryEditor::SResultsView`  
`class SResultsView : public SCompoundWidget`  
_L35-90_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS( SResultsView )`
- L41 _public prototype_ `~SResultsView() override;`
- L42 _public prototype_ `void Construct(const FArguments& InArgs, FTedsQueryEditorModel& InModel);`
- L43 _public prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L45 _public prototype_ `ETableViewMode::Type GetViewMode() const;`
- L46 _public prototype_ `void SetViewMode(ETableViewMode::Type InViewMode);`
- L50 _private prototype_ `void OnModelChanged();`
- L51 _private prototype_ `void OnTableViewerRefreshRequired();`
- L52 _private prototype_ `void CreateRowHandleColumn();`
- L53 _private prototype_ `TSharedRef<SWidget> CreateTableViewer();`
- L54 _private prototype_ `TSharedRef<SWidget> CreateSearchBox();`
- L56 _private member_ `FTedsQueryEditorModel* Model = nullptr;`
- L57 _private member_ `FDelegateHandle ModelChangedDelegateHandle;`
- L58 _private member_ `FDelegateHandle TableViewerRefreshRequiredDelegateHandle;`
- L59 _private member_ `bool bModelDirty = true;`
- L62 _private member_ `QueryHandle CountQueryHandle = InvalidQueryHandle;`
- L64 _private member_ `TArray<RowHandle> TableViewerRows;`
- L65 _private member_ `TSharedPtr<ITableViewer> TableViewer;`
- L66 _private member_ `TSharedPtr<QueryStack::FQueryNode> QueryNode;`
- L67 _private member_ `TSharedPtr<QueryStack::IRowNode> RowQueryStack;`
- L71 _private member_ `TSharedPtr<IHierarchyViewerDataInterface> HierarchyData;` — Hierarchy Data used by SHierarchyView to resolve parenting. May be FHierarchyViewerData (named hierarchy) or FRelationTypeHierarchyViewerData (raw hierarchical relation).
- L73 _private member_ `FHierarchyHandle HierarchyHandle;` — The current named hierarchy the widget is viewing (only valid when a named hierarchy is selected)
- L76 _private member_ `TSharedPtr<FTedsTableViewerColumn> RowHandleColumn;` — Custom column for the table viewer to display row handles
- L79 _private member_ `TSharedPtr<SRowDetailsNavigator> RowDetailsNavigator;` — Breadcrumb-navigable stack of row detail panels
- L81 _private member_ `IUiProvider* UiProvider = nullptr;`
- L84 _private member_ `TSharedPtr<SBorder> TableViewerSlot;` — Border inside which the table viewer is stored so we can re-create it when needed
- L87 _private member_ `TSharedPtr<SBorder> SearchBoxSlot;` — Border inside which the search box is stored so we can re-create it when needed
- L89 _private member_ `ETableViewMode::Type ResultsViewMode = ETableViewMode::List;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L24 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L31 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L31 _namespace_ `namespace QueryEditor` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/RowReferenceWidget.h` (Private)


#### class `URowReferenceWidgetFactory`  
`class URowReferenceWidgetFactory : public UEditorDataStorageFactory`  
_L16-25_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Widget for the TEDS Debugger that visualizes a reference to another row
- L23 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FRowReferenceWidgetConstructor`  
`struct FRowReferenceWidgetConstructor : public FTypedElementWidgetConstructor`  
_L28-42_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L33 _public prototype_ `FRowReferenceWidgetConstructor();`
- L34 _public prototype_ `~FRowReferenceWidgetConstructor() override = default;`
- L36 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/SScopeHierarchyTab.h` (Private)


#### struct `UE::Editor::DataStorage::Debug::FScopeColumnItem`  
`struct FScopeColumnItem`  
_L24-32_
- desc: Item for the visible-columns list view on the details side.
- L26 _public member_ `FString TypeName;`
- L27 _public member_ `RowHandle OwnerRow = InvalidRowHandle;`
- L28 _public member_ `bool bInherited = false;`
- L29 _public member_ `TWeakObjectPtr<const UScriptStruct> ColumnType;`
- L30 _public member_ `IUiProvider::FWidgetConstructorPtr WidgetConstructor;`
- L31 _public member_ `RowHandle WidgetRow = InvalidRowHandle;`

#### class `UE::Editor::DataStorage::Debug::SScopeHierarchyTab`  
`class SScopeHierarchyTab final : public SCompoundWidget`  
_L40-72_
- inherits: `SCompoundWidget`
- desc: Debugger tab showing the Editor Scope Tree row hierarchy. Left: SHierarchyViewer tree of all scope rows. Right: On selection, resolved creation callstack + visible columns list.
- L43 _public function_ `SLATE_BEGIN_ARGS(SScopeHierarchyTab)`
- L44 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L49 _private prototype_ `TSharedRef<SWidget> CreateHierarchyViewer();`
- L50 _private prototype_ `TSharedRef<SWidget> CreateDetailsPanel();`
- L51 _private prototype_ `void OnHierarchySelectionChanged(RowHandle Row, ESelectInfo::Type SelectInfo);`
- L52 _private prototype_ `void RebuildDetailsForRow(RowHandle Row);`
- L53 _private prototype_ `FReply CopyCallstackToClipboard();`
- L55 _private prototype_ `TSharedRef<ITableRow> MakeColumnListRow( FScopeColumnItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L58 _private member_ `ICoreProvider* Storage = nullptr;`
- L59 _private member_ `IUiProvider* DataStorageUi = nullptr;`
- L62 _private member_ `TSharedPtr<SHierarchyViewer> HierarchyViewer;` — Hierarchy viewer
- L63 _private member_ `TSharedPtr<FHierarchyViewerData> HierarchyData;`
- L64 _private member_ `TSharedPtr<QueryStack::FQueryNode> ContextQueryNode;`
- L65 _private member_ `TSharedPtr<QueryStack::FRowQueryResultsNode> ScopeRowsNode;`
- L68 _private member_ `TSharedPtr<SMultiLineEditableTextBox> CallstackTextBox;` — Details panel
- L69 _private member_ `FString CachedCallstackString;`
- L70 _private member_ `TSharedPtr<SListView<FScopeColumnItemPtr>> ColumnListView;`
- L71 _private member_ `TArray<FScopeColumnItemPtr> ColumnItems;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L21 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)
- L33 _typedef_ `using FScopeColumnItemPtr = TSharedPtr<FScopeColumnItem>;` (scope `UE::Editor::DataStorage::Debug`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/STedsDiscoveryDebugger.h` (Private)


#### enum `UE::Editor::DataStorage::Debug::ESearchMode`  
`enum class ESearchMode : uint8`  
_L18-24_
- L21 _public enumerator_ `RowHandle` — Search for a specific RowHandle for specific debugging
- L23 _public enumerator_ `Column` — Search on all rows on columns with Searchable properties

#### class `UE::Editor::DataStorage::Debug::SDiscoveryDebuggerTab`  
`class SDiscoveryDebuggerTab final : public SCompoundWidget`  
_L26-64_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SDiscoveryDebuggerTab)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _private prototype_ `TSharedRef<SWidget> CreateToolbar();`
- L39 _private prototype_ `TSharedRef<SWidget> GetSearchModesMenuWidget();`
- L40 _private prototype_ `FText GetCurrentSearchModeAsText() const;`
- L41 _private prototype_ `static FText GetSearchModeAsText(const ESearchMode InSearchMode);`
- L43 _private prototype_ `void SetRowQueryStack();`
- L44 _private prototype_ `void InitColumnSearch();`
- L45 _private prototype_ `TSharedRef<SWidget> CreateTableViewer();`
- L46 _private prototype_ `void CreateRowHandleColumn();`
- L47 _private prototype_ `TSharedRef<SWidget> CreateSearchBox();`
- L49 _private member_ `TSharedPtr<STedsTableViewer> TableViewer;`
- L50 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L52 _private member_ `TSharedPtr<SRowDetails> RowDetailsWidget;` — Widget that displays details of a row
- L54 _private member_ `TSharedPtr<FTedsTableViewerColumn> RowHandleColumn;` — Custom column for the table viewer to display row handles
- L56 _private member_ `TSharedPtr<QueryStack::IRowNode> RowQueryStack;`
- L58 _private member_ `TSharedPtr<QueryStack::FColumnsSearchNode> ColumnSearchNode;` — Hold onto the ColumnSearchNode so it doesn't need to be re-initialized when switching back to column search
- L60 _private member_ `ICoreProvider* Storage = nullptr;`
- L61 _private member_ `IUiProvider* UiProvider = nullptr;`
- L62 _private member_ `FText SearchText;`
- L63 _private member_ `ESearchMode SearchMode = ESearchMode::RowHandle;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Editor` (scope `UE`)
- L14 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L14 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/STedsTableDebugger.h` (Private)


#### class `UE::Editor::DataStorage::Debug::STableDebuggerTab`  
`class STableDebuggerTab final : public SCompoundWidget`  
_L27-92_
- inherits: `SCompoundWidget`
- L31 _public function_ `SLATE_BEGIN_ARGS(STableDebuggerTab)`
- L33 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L38 _private typedef_ `using TreeViewItem = FTedsTableHandle;`
- L57 _private typedef_ `using InfoItem = TSharedPtr<FTableInfoEntry>;`
- L73 _private prototype_ `void RefreshRootTables();`
- L74 _private prototype_ `void OnTableSelection(TreeViewItem Item, ESelectInfo::Type SelectInfo);`
- L76 _private prototype_ `TSharedRef<SWidget> CreateTreeView();`
- L77 _private prototype_ `TSharedRef<SWidget> CreateInfoView();`
- L78 _private prototype_ `TSharedRef<SWidget> CreateRowView();`
- L79 _private prototype_ `void CreateRowForeignKeyColumn();`
- L80 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TreeViewItem Item, const TSharedRef<STableViewBase>& Tree);`
- L81 _private prototype_ `TSharedRef<ITableRow> MakeInfoRowWidget(InfoItem Item, const TSharedRef<STableViewBase>& Tree);`
- L82 _private prototype_ `void HandleGetChildrenForTree(TreeViewItem Item, TArray<TreeViewItem>& Children);`
- L84 _private member_ `TArray<TreeViewItem> RootTables;`
- L85 _private member_ `TArray<InfoItem> InfoLines;`
- L86 _private member_ `TSharedPtr<SListView<InfoItem>> InfoView;`
- L87 _private member_ `TSharedPtr<STedsTableViewer> RowView;`
- L88 _private member_ `TSharedPtr<QueryStack::FRowArrayNode> QueryStack;`
- L89 _private member_ `TSharedPtr<FTedsTableViewerColumn> RowForeignKeyColumn;`
- L90 _private member_ `ICoreProvider* Storage = nullptr;`
- L91 _private member_ `IUiProvider* UiProvider = nullptr;`

#### class `UE::Editor::DataStorage::Debug::STableDebuggerTab::STableTreeViewRow`  
`class STableTreeViewRow final : public STableRow<TreeViewItem>`  
_L39-49_
- inherits: `STableRow<TreeViewItem>`
- L42 _public typedef_ `using Super = STableRow<TreeViewItem>;`
- L44 _public function_ `SLATE_BEGIN_ARGS(STableTreeViewRow)`
- L45 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const ICoreProvider& InStorage, const TreeViewItem& InItem, const TSharedRef<STableViewBase>& InOwner);`

#### struct `UE::Editor::DataStorage::Debug::STableDebuggerTab::FTableInfoEntry`  
`struct FTableInfoEntry final`  
_L51-55_
- L53 _public member_ `FString Key;`
- L54 _public member_ `FString Value;`

#### class `UE::Editor::DataStorage::Debug::STableDebuggerTab::SInfoRow`  
`class SInfoRow final : public SMultiColumnTableRow<InfoItem>`  
_L58-71_
- inherits: `SMultiColumnTableRow<InfoItem>`
- L61 _public function_ `SLATE_BEGIN_ARGS(SInfoRow)`
- L62 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const InfoItem& InItem, const TSharedRef<STableViewBase>& InOwner);`
- L67 _protected prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L70 _private member_ `InfoItem Item;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L15 _namespace_ `namespace QueryStack` (scope `UE::Editor::DataStorage`)
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Editor` (scope `UE`)
- L25 _namespace_ `namespace DataStorage` (scope `UE::Editor`)
- L25 _namespace_ `namespace Debug` (scope `UE::Editor::DataStorage`)

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/ScopeRowLabelWidget.h` (Private)


#### struct `FScopeRowLabelWidgetConstructor`  
`struct FScopeRowLabelWidgetConstructor : public FSimpleWidgetConstructor`  
_L15-29_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- desc: Widget constructor for scope hierarchy rows that shows the FTypedElementLabelColumn text when available, falling back to the stringified RowHandle. When a label is shown, the tooltip displays the RowHandle for debugging.
- L20 _public prototype_ `FScopeRowLabelWidgetConstructor();`
- L21 _public prototype_ `~FScopeRowLabelWidgetConstructor() override = default;`
- L23 _public prototype_ `TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

### `Plugins/Experimental/EditorDataStorageFeatures/Source/TedsDebugger/Private/Widgets/SlateVisualizationWidget.h` (Private)


#### class `USlateVisualizationWidgetFactory`  
`class USlateVisualizationWidgetFactory : public UEditorDataStorageFactory`  
_L16-25_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Widget for the TEDS Debugger that shows a slate widget reference
- L21 _public prototype_ `~USlateVisualizationWidgetFactory() override = default;`
- L23 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FSlateVisualizationWidgetConstructor`  
`struct FSlateVisualizationWidgetConstructor : public FTypedElementWidgetConstructor`  
_L28-41_
- reflection: `USTRUCT()`
- inherits: `FTypedElementWidgetConstructor`
- L33 _public prototype_ `FSlateVisualizationWidgetConstructor();`
- L34 _public prototype_ `~FSlateVisualizationWidgetConstructor() override = default;`
- L37 _protected prototype_ `TSharedPtr<SWidget> CreateWidget(const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`
- L38 _protected prototype_ `bool FinalizeWidget(UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle Row, const TSharedPtr<SWidget>& Widget) override;`
