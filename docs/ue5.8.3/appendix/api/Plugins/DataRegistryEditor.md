# Plugins / DataRegistryEditor

- module root: `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor`
- headers: 9; symbols: 245
- symbol kinds: class=11, delegate=5, function=16, macro=1, member=71, prototype=138, struct=2, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, BlueprintGraph, ContentBrowser, Core, CoreUObject, DataRegistry, DataTableEditor, EditorWidgets, Engine, GameplayTags, GameplayTagsEditor, GraphEditor, InputCore, Kismet, KismetCompiler, PropertyEditor, Slate, SlateCore, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/AssetDefinition_DataRegistry.h` (Private)


#### class `UAssetDefinition_DataRegistry`  
`class UAssetDefinition_DataRegistry : public UAssetDefinitionDefault`  
_L9-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/DataRegistryEditorToolkit.h` (Private)


#### class `FDataRegistryEditorToolkit`  
`class FDataRegistryEditorToolkit : public FAssetEditorToolkit`  
_L22-214_
- inherits: `FAssetEditorToolkit`
- desc: Viewer/editor for a DataRegistry
- L26 _private typedef_ `using Super = FAssetEditorToolkit;`
- L30 _public prototype_ `FDataRegistryEditorToolkit();`
- L31 _public prototype_ `virtual ~FDataRegistryEditorToolkit();`
- L33 _public prototype_ `static TSharedRef<FDataRegistryEditorToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UDataRegistry* InDataRegistry);`
- L36 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L37 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L38 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L39 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L41 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L42 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L44 _public prototype_ `virtual void InitDataRegistryEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataRegistry* Registry);`
- L47 _public prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the tab with the details view inside
- L50 _public prototype_ `TSharedRef<SDockTab> SpawnTab_RowList(const FSpawnTabArgs& Args);` — Spawns the tab with the data table inside
- L54 _public prototype_ `const UDataRegistry* GetDataRegistry() const;` — Get the data table being edited
- L56 _public prototype_ `void HandlePostChange();`
- L58 _public prototype_ `void SetHighlightedRow(FName Name);`
- L60 _public prototype_ `FText GetFilterText() const;`
- L62 _public prototype_ `FSlateColor GetRowTextColor(FName RowName) const;`
- L64 _public prototype_ `const FDataRegistrySourceItemId* GetSourceItemForName(FName DebugName) const;`
- L69 _protected prototype_ `void RefreshCachedDataRegistry(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);`
- L71 _protected prototype_ `void UpdateVisibleRows(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);`
- L73 _protected prototype_ `void RestoreCachedSelection(const FName InCachedSelection, const bool bUpdateEvenIfValid = false);`
- L75 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L76 _protected prototype_ `void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L78 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L80 _protected prototype_ `FReply OnFindRowInContentBrowserClicked();`
- L81 _protected prototype_ `void OnEditDataTableStructClicked();`
- L83 _protected prototype_ `FText GetCellText(FDataTableEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;`
- L84 _protected prototype_ `FText GetCellToolTipText(FDataTableEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;`
- L86 _protected prototype_ `TSharedRef<SVerticalBox> CreateContentBox();`
- L88 _protected prototype_ `float GetRowNameColumnWidth() const;`
- L89 _protected prototype_ `void RefreshRowNameColumnWidth();`
- L91 _protected prototype_ `float GetRowNumberColumnWidth() const;`
- L92 _protected prototype_ `void RefreshRowNumberColumnWidth();`
- L94 _protected prototype_ `float GetColumnWidth(const int32 ColumnIndex) const;`
- L96 _protected prototype_ `void OnColumnResized(const float NewWidth, const int32 ColumnIndex);`
- L98 _protected prototype_ `void OnRowNameColumnResized(const float NewWidth);`
- L100 _protected prototype_ `void OnRowNumberColumnResized(const float NewWidth);`
- L103 _protected prototype_ `TSharedRef<ITableRow> MakeRowWidget(FDataTableEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);` — Make the widget for a row entry in the data table row list view
- L105 _protected prototype_ `void OnRowSelectionChanged(FDataTableEditorRowListViewDataPtr InNewSelection, ESelectInfo::Type InSelectInfo);`
- L107 _protected prototype_ `void CopySelectedRow();`
- L110 _protected prototype_ `virtual void CreateAndRegisterRowListTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the row list
- L113 _protected prototype_ `virtual void CreateAndRegisterPropertiesTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the properties tab
- L115 _protected prototype_ `void OnCopyClicked();`
- L116 _protected prototype_ `void OnRefreshClicked();`
- L118 _protected prototype_ `void OnDataAcquired(EDataRegistryAcquireStatus AcquireStatus);`
- L120 _protected prototype_ `void SetDefaultSort();`
- L121 _protected prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L122 _protected prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L123 _protected prototype_ `void OnColumnNumberSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L124 _protected prototype_ `void OnColumnNameSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L126 _protected prototype_ `void ExtendToolbar(TSharedPtr<FExtender> Extender);`
- L127 _protected prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L130 _private prototype_ `UDataRegistry* GetEditableDataRegistry() const;`
- L149 _protected member_ `TSharedPtr<SWidget> RowListTabWidget;`
- L150 _protected member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L153 _protected member_ `TArray<FDataTableEditorColumnHeaderDataPtr> AvailableColumns;` — Array of the columns that are available for editing
- L156 _protected member_ `TArray<FDataTableEditorRowListViewDataPtr> AvailableRows;` — Array of the rows that are available for editing
- L159 _protected member_ `TMap<FName, FDataRegistrySourceItemId> SourceItemMap;` — Map of debug names to source details
- L162 _protected member_ `TArray<FDataTableEditorRowListViewDataPtr> VisibleRows;` — Array of the rows that match the active filter(s)
- L165 _protected member_ `TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;` — Header row containing entries for each column in AvailableColumns
- L168 _protected member_ `TSharedPtr<SListView<FDataTableEditorRowListViewDataPtr>> CellsListView;` — List view responsible for showing the rows in VisibleRows for each entry in AvailableColumns
- L171 _protected member_ `float RowNameColumnWidth;` — Width of the row name column
- L174 _protected member_ `float RowNumberColumnWidth;` — Width of the row number column
- L177 _protected member_ `TArray<FDataRegistrySourceItemId> PendingSourceData;` — If this is set, we asked the registry for info on some ids
- L180 _protected member_ `TArray<FColumnWidth> ColumnWidths;` — Widths of data table cell columns
- L183 _protected member_ `FName HighlightedRowName;` — The name of the currently selected row
- L186 _protected member_ `int32 HighlightedVisibleRowIndex;` — The visible row index of the currently selected row
- L189 _protected member_ `FText ActiveFilterText;` — The current filter text applied to the data table
- L192 _protected member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L195 _protected member_ `FName SortByColumn;` — Specify which column to sort with
- L198 _protected member_ `TSharedPtr< class IDetailsView > DetailsView;` — Details view
- L201 _protected member_ `TSharedPtr<SWidget> StackTabWidget;` — UI for the "Stack" tab
- L203 _protected member_ `static const FName AppIdentifier;`
- L204 _protected member_ `static const FName RowListTabId;`
- L205 _protected member_ `static const FName PropertiesTabId;`
- L206 _protected member_ `static const FName StackTabId;`
- L207 _protected member_ `static const FName RowNumberColumnId;`
- L208 _protected member_ `static const FName RowNameColumnId;`
- L209 _protected member_ `static const FName RowSourceColumnId;`
- L210 _protected member_ `static const FName RowResolvedColumnId;`

#### struct `FDataRegistryEditorToolkit::FColumnWidth`  
`struct FColumnWidth`  
_L135-147_
- desc: Struct holding information about the current column widths
- L137 _public function_ `FColumnWidth() : bIsAutoSized(true) , CurrentWidth(0.0f)`
- L144 _public member_ `bool bIsAutoSized;` — True if this column is being auto-sized rather than sized by the user
- L146 _public member_ `float CurrentWidth;` — The width of the column, either sized by the user, or auto-sized

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/DataRegistryFactory.h` (Private)


#### class `UDataRegistryFactory`  
`class UDataRegistryFactory : public UFactory`  
_L11-22_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L16 _private member_ `TSubclassOf<UDataRegistry> DataRegistryClass;` — `UPROPERTY(EditAnywhere, Category = DataRegistry)`
- L19 _private prototype_ `virtual bool ConfigureProperties() override;`
- L20 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/DataRegistryIdCustomization.h` (Private)


#### struct `FDataRegistryIdEditWrapper`  
`struct FDataRegistryIdEditWrapper : public FPinStructEditWrapper`  
_L15-31_
- reflection: `USTRUCT()`
- inherits: `FPinStructEditWrapper`
- desc: This allows using this customization with blueprint pins
- L21 _public member_ `FDataRegistryId RegistryId;` — `UPROPERTY(EditAnywhere, Category = Registry, Meta = (ShowOnlyInnerProperties))` — Actual id to edit
- L24 _public prototype_ `virtual FText GetPreviewDescription() const override;` — Returns a text representation of the data
- L27 _public function_ `virtual const UScriptStruct* GetDataScriptStruct() const override` — Returns what script struct to use to parse the nested data
- L30 _public function_ `virtual uint8* GetDataMemory() override` — Returns address of nested data

#### class `SDataRegistryItemNameWidget`  
`class SDataRegistryItemNameWidget : public SCompoundWidget`  
_L34-100_
- inherits: `SCompoundWidget`
- desc: Raw widget, used by both customization and external callers
- L37 _public function_ `SLATE_BEGIN_ARGS(SDataRegistryItemNameWidget) : _bAllowClear(true)`
- L49 _public prototype_ `void Construct(const FArguments& InArgs);`
- L53 _private prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Updates cached values
- L56 _private prototype_ `void OnTypeChanged(bool bClearInvalid);` — Delegate to refresh the drop down when the selected type changes
- L59 _private prototype_ `void OnNameSelected(const FString& NameString);` — Change value and forward to delegates
- L62 _private prototype_ `TSharedRef<SWidget> GetTagContent();` — Display tag UI
- L63 _private prototype_ `void OnTagUIOpened(bool bIsOpened);`
- L66 _private prototype_ `void OnTagChanged(const FGameplayTag& NewTag);` — Delegate when tag changes
- L69 _private prototype_ `void OnGetNameStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;` — Get list of all name
- L72 _private prototype_ `FString OnGetNameValueString() const;` — Slate accessors
- L73 _private prototype_ `FText OnGetNameValueText() const;`
- L74 _private prototype_ `EVisibility GetWarningVisibility() const;`
- L77 _private member_ `class UDataRegistrySubsystem* Subsystem = nullptr;` — This will never be bad while engine is running
- L80 _private member_ `FDataRegistryId CachedIdValue;` — Cached Id, if this changes then refresh items
- L83 _private member_ `TArray<FDataRegistryId> CachedIds;` — Cached list of ids for current type
- L86 _private member_ `TSharedPtr<FGameplayTag> CachedTag;` — Tag representation of name
- L89 _private member_ `FString CachedBaseGameplayTag;` — Root gameplay tag to show
- L92 _private member_ `TSharedPtr<class SWidgetSwitcher> ValueSwitcher;` — Widget switcher for value editor
- L95 _private member_ `FOnGetDataRegistryDisplayText OnGetDisplayText;` — Creation arguments
- L96 _private member_ `FOnGetDataRegistryId OnGetId;`
- L97 _private member_ `FOnSetDataRegistryId OnSetId;`
- L98 _private member_ `FOnGetCustomDataRegistryItemNames OnGetCustomItemNames;`
- L99 _private member_ `bool bAllowClear;`

#### class `FDataRegistryIdCustomization`  
`class FDataRegistryIdCustomization : public IPropertyTypeCustomization`  
_L106-144_
- inherits: `IPropertyTypeCustomization`
- L110 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L113 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L114 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L119 _private prototype_ `void OnSearchForReferences();` — Open reference viewer
- L122 _private prototype_ `FString OnGetTypeValueString() const;` — Slate accessors
- L123 _private prototype_ `FText OnGetNameValueText() const;`
- L124 _private prototype_ `FDataRegistryId GetCurrentValue() const;`
- L125 _private prototype_ `void SetCurrentValue(FDataRegistryId NewId);`
- L128 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct properties being customized
- L129 _private member_ `TSharedPtr<IPropertyHandle> TypePropertyHandle;`
- L130 _private member_ `TSharedPtr<IPropertyHandle> NamePropertyHandle;`
- L133 _private member_ `class UDataRegistrySubsystem* Subsystem = nullptr;` — This will never be bad while engine is running
- L136 _private member_ `TArray<FDataRegistryId> CachedIds;` — Cached list of ids for current type
- L139 _private member_ `TSharedPtr<FGameplayTag> CachedTag;` — Tag representation of name
- L142 _private member_ `TSharedPtr<class SWidgetSwitcher> ValueSwitcher;` — Widget switcher for value editor

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/DataRegistryTypeCustomization.h` (Private)


#### class `FDataRegistryTypeCustomization`  
`class FDataRegistryTypeCustomization : public IPropertyTypeCustomization`  
_L13-44_
- inherits: `IPropertyTypeCustomization`
- desc: Data Registry type, reads list from subsystem
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L28 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property being customized
- L31 _private prototype_ `const FDataRegistryType* GetPropertyValue() const;` — Returns the data of the underlying property
- L34 _private prototype_ `UDataRegistry* GetDataRegistry() const;` — Returns the data registry associated with this registry type, if there is one
- L37 _private prototype_ `void GenerateComboBoxStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<class SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems);` — Creates the string list
- L40 _private prototype_ `FReply OnClickOpenAsset();` — Functionality for the "open asset" button
- L41 _private prototype_ `EVisibility GetOpenAssetVisibility() const;`
- L42 _private prototype_ `FText GetOpenAssetTooltip() const;`

#### class `SDataRegistryTypeGraphPin`  
`class SDataRegistryTypeGraphPin : public SGraphPin`  
_L47-65_
- inherits: `SGraphPin`
- desc: Graph pin version of UI
- L50 _public function_ `SLATE_BEGIN_ARGS(SDataRegistryTypeGraphPin)`
- L51 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L56 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L61 _private prototype_ `void OnTypeSelected(FDataRegistryType AssetType);`
- L62 _private prototype_ `FText GetDisplayText() const;`
- L64 _private member_ `FDataRegistryType CurrentType;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/DataTableOrRegistryRowCustomization.h` (Private)


#### class `FDataRegistryOrTableRowCustomization`  
`class FDataRegistryOrTableRowCustomization : public IPropertyTypeCustomization`  
_L12-52_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a FDataRegistryOrTableRow to support filtering by item struct, and compacting it to one row
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _private prototype_ `void GetDataSourceComboStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;`
- L24 _private prototype_ `FString GetDataSourceTypeValueString() const;`
- L25 _private prototype_ `void OnDataSourceSelected(const FString& String);`
- L27 _private prototype_ `FString OnGetDataRegistryTypeValueString() const;`
- L28 _private prototype_ `bool ShouldFilterDataTableAsset(const struct FAssetData& AssetData);`
- L30 _private prototype_ `void OnGetDataTableRowStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;`
- L31 _private prototype_ `FString OnGetDataTableRowValueString() const;`
- L33 _private prototype_ `FDataRegistryOrTableRow GetCurrentValue() const;`
- L34 _private prototype_ `EVisibility GetOpenDataRegistryAssetVisibility() const;`
- L35 _private prototype_ `FReply OnClickOpenDataRegistryAsset();`
- L37 _private prototype_ `FText GetOpenDataRegistryAssetTooltip() const;`
- L38 _private prototype_ `FText OnGetDataRegistryNameValueText() const;`
- L39 _private prototype_ `FDataRegistryId GetCurrentDataRegistryValue() const;`
- L40 _private prototype_ `void SetCurrentDataRegistryValue(FDataRegistryId NewValue);`
- L42 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L44 _private member_ `FName FilterStructName;`
- L45 _private member_ `FName RegistryFilterStructName;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> UseRegistryPropertyHandle;`
- L48 _private member_ `TSharedPtr<IPropertyHandle> RegistryTypeNamePropertyHandle;`
- L49 _private member_ `TSharedPtr<IPropertyHandle> RegistryItemNamePropertyHandle;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> TablePropertyHandle;`
- L51 _private member_ `TSharedPtr<IPropertyHandle> TableRowNamePropertyHandle;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/SDataRegistryListViewRow.h` (Private)


#### class `SDataRegistryListViewRow`  
`class SDataRegistryListViewRow : public SMultiColumnTableRow<FDataTableEditorRowListViewDataPtr>`  
_L20-62_
- inherits: `SMultiColumnTableRow<FDataTableEditorRowListViewDataPtr>`
- desc: A widget to represent a row in a Data Table Editor widget. This widget allows us to do things like right-click and take actions on a particular row of a Data Table.
- L24 _public function_ `SLATE_BEGIN_ARGS(SDataRegistryListViewRow)`
- L26 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDataRegistryEditorToolkit>, DataRegistryEditor) SLATE_ARGUMENT(FDataTableEditorRowListViewDataPtr, RowDataPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — The owning object. This allows us access to the actual data table being edited as well as some other API functions.
- L33 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L38 _public prototype_ `FText GetCurrentNameAsText() const;`
- L39 _public prototype_ `FName GetCurrentName() const;`
- L40 _public prototype_ `uint32 GetCurrentIndex() const;`
- L42 _public prototype_ `const FDataTableEditorRowListViewDataPtr& GetRowDataPtr() const;`
- L46 _private prototype_ `const FDataRegistrySourceItemId* FindSource() const;`
- L47 _private prototype_ `void OnSearchForReferences();`
- L48 _private prototype_ `void OnOpenSourceAsset();`
- L50 _private prototype_ `TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);`
- L52 _private prototype_ `virtual const FSlateBrush* GetBorder() const;`
- L54 _private prototype_ `TSharedRef<SWidget> MakeRowActionsMenu();`
- L57 _private member_ `TSharedPtr<FName> CurrentName;`
- L59 _private member_ `FDataTableEditorRowListViewDataPtr RowDataPtr;`
- L60 _private member_ `TWeakPtr<FDataRegistryEditorToolkit> DataRegistryEditor;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Private/SoftDataRegistryOrTableCustomization.h` (Private)


#### class `FSoftDataRegistryOrTableCustomization`  
`class FSoftDataRegistryOrTableCustomization : public IPropertyTypeCustomization`  
_L12-42_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a FSoftDataRegistryOrTable to support filtering by item struct, and compacting it to one row
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _private prototype_ `void GetDataSourceComboStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;`
- L24 _private prototype_ `FString GetDataSourceTypeValueString() const;`
- L25 _private prototype_ `void OnDataSourceSelected(const FString& String);`
- L26 _private prototype_ `FString OnGetDataRegistryTypeValueString() const;`
- L27 _private prototype_ `bool ShouldFilterDataTableAsset(const struct FAssetData& AssetData);`
- L29 _private prototype_ `EVisibility GetOpenDataRegistryAssetVisibility() const;`
- L30 _private prototype_ `FReply OnClickOpenDataRegistryAsset();`
- L31 _private prototype_ `FText GetOpenDataRegistryAssetTooltip() const;`
- L33 _private prototype_ `FSoftDataRegistryOrTable GetCurrentValue() const;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L36 _private member_ `TSharedPtr<IPropertyHandle> UseRegistryPropertyHandle;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> RegistryTypeNamePropertyHandle;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> TablePropertyHandle;`
- L40 _private member_ `FName FilterStructName;`
- L41 _private member_ `FName RegistryFilterStructName;`

### `Plugins/Runtime/DataRegistry/Source/DataRegistryEditor/Public/DataRegistryEditorModule.h` (Public)


#### class `FDataRegistryEditorModule`  
`class FDataRegistryEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L23-85_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: The public interface to this module
- L33 _public function_ `static inline FDataRegistryEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L43 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L56 _public prototype_ `static TSharedRef<SWidget> MakeDataRegistryTypeSelector(FOnGetDataRegistryDisplayText OnGetDisplayText, FOnSetDataRegistryType OnSetType, bool bAllowClear = true, FName FilterStructName = NAME_None);` — Creates a simple version of a Data Registry Type selector, not bound to a PropertyHandle @param OnGetDisplayText Delegate that returns the text to display in body of combo box @param OnSetType Delegate called when type is changed @param bAllowClear If true, add None option to top @param FilterStructName If not empty, restrict to types that use a struct that inherts from something named this
- L59 _public prototype_ `static void GenerateDataRegistryTypeComboBoxStrings(TArray< TSharedPtr<FString> >& OutComboBoxStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems, bool bAllowClear, FName FilterStructName);` — Called to get list of valid data registry types, used by MakeDataRegistryTypeSelector or can be used for a property handle version
- L71 _public prototype_ `static TSharedRef<SWidget> MakeDataRegistryItemNameSelector(FOnGetDataRegistryDisplayText OnGetDisplayText, FOnGetDataRegistryId OnGetId, FOnSetDataRegistryId OnSetId, FOnGetCustomDataRegistryItemNames OnGetCustomItemNames = FOnGetCustomDataRegistryItemNames(), bool bAllowClear = true);` — Creates a simple version of a Data Registry Item Name selector, not bound to a PropertyHandle. This will spawn the appropriate tag/combo box UI on click depending on the type @param OnGetDisplayText Delegate that returns the text to display in body of combo box @param OnGetId Delegate that should return the current id, used to populate the comobo box on click. Type must be set but name can be none @param OnSetId Delegate called when item is selected @param OnGetCustomItemNames Optional delegate to call to get custom names if OnGetId returns CustomContextType @param bAllowClear If true, add None option to top
- L74 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend data registry editor's menus and toolbars
- L75 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L79 _private prototype_ `virtual void StartupModule() override;`
- L80 _private prototype_ `virtual void ShutdownModule() override;`
- L82 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L83 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L84 _private member_ `TSharedPtr<class FDataRegistryGraphPanelPinFactory> DataRegistryGraphPanelPinFactory;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAREGISTRYEDITOR_API`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnGetDataRegistryDisplayText);`
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(FText, FOnGetDataRegistryDisplayText);`
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetDataRegistryType, FDataRegistryType);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetDataRegistryType, FDataRegistryType);`
- L16 _delegate_ `DECLARE_DELEGATE_RetVal(FDataRegistryId, FOnGetDataRegistryId) DECLARE_DELEGATE_OneParam(FOnSetDataRegistryId, FDataRegistryId);`
- L16 _prototype_ `DECLARE_DELEGATE_RetVal(FDataRegistryId, FOnGetDataRegistryId) DECLARE_DELEGATE_OneParam(FOnSetDataRegistryId, FDataRegistryId);`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetDataRegistryId, FDataRegistryId);`
- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetCustomDataRegistryItemNames, TArray<FName>&);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetCustomDataRegistryItemNames, TArray<FName>&);`
