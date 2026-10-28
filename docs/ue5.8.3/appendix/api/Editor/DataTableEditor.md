# Editor / DataTableEditor

- module root: `Source/Editor/DataTableEditor`
- headers: 9; symbols: 246
- symbol kinds: class=11, delegate=3, function=9, macro=1, member=54, prototype=167, struct=1
- DynamicallyLoadedModuleNames: WorkspaceMenuStructure
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, InputCore, Json, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicIncludePathModuleNames: LevelEditor

### `Source/Editor/DataTableEditor/Private/CompositeDataTableEditor.h` (Private)


#### class `FCompositeDataTableEditor`  
`class FCompositeDataTableEditor : public FDataTableEditor`  
_L17-59_
- inherits: `FDataTableEditor`
- desc: Viewer/editor for a CompositeDataTable
- L22 _public prototype_ `FCompositeDataTableEditor();` — Constructor
- L25 _public prototype_ `virtual ~FCompositeDataTableEditor();` — Destructor
- L27 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L28 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L30 _public prototype_ `virtual void InitDataTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table) override;`
- L31 _public prototype_ `virtual bool CanEditRows() const override;`
- L34 _public prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the tab with the details view inside
- L37 _public prototype_ `TSharedRef<SDockTab> SpawnTab_Stack(const FSpawnTabArgs& Args);` — Spawns the tab with the stack of data tables inside
- L41 _protected prototype_ `virtual void CreateAndRegisterRowEditorTab(const TSharedRef<class FTabManager>& InTabManager) override;`
- L44 _protected prototype_ `virtual void CreateAndRegisterPropertiesTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the properties tab
- L47 _private prototype_ `TSharedRef<SWidget> CreateStackBox();`
- L49 _private prototype_ `virtual TSharedRef<SRowEditor> CreateRowEditor(UDataTable* Table);`
- L52 _private member_ `TSharedPtr< class IDetailsView > DetailsView;` — Details view
- L55 _private member_ `TSharedPtr<SWidget> StackTabWidget;` — UI for the "Stack" tab
- L57 _private member_ `static const FName PropertiesTabId;`
- L58 _private member_ `static const FName StackTabId;`

### `Source/Editor/DataTableEditor/Private/DataTableEditor.h` (Private)


#### class `FDataTableEditor`  
`class FDataTableEditor : public IDataTableEditor , public FEditorUndoClient , public FStructureEditorUtils::INotifyOnStructChanged , public FDataTableEditorUtils::INotifyOnDataTableChanged`  
_L47-299_
- inherits: `IDataTableEditor,FEditorUndoClient,FStructureEditorUtils::INotifyOnStructChanged,FDataTableEditorUtils::INotifyOnDataTableChanged`
- desc: Viewer/editor for a DataTable
- L56 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L57 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L66 _public prototype_ `virtual void InitDataTableEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table );` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Table					The table to edit
- L68 _public prototype_ `virtual bool CanEditRows() const;`
- L71 _public prototype_ `FDataTableEditor();` — Constructor
- L74 _public prototype_ `virtual ~FDataTableEditor();` — Destructor
- L77 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L78 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L79 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L80 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L83 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient
- L84 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L85 _public prototype_ `void HandleUndoRedo();`
- L88 _public prototype_ `virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;` — INotifyOnStructChanged
- L89 _public prototype_ `virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;`
- L92 _public prototype_ `virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;` — INotifyOnDataTableChanged
- L93 _public prototype_ `virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;`
- L94 _public prototype_ `virtual void SelectionChange(const UDataTable* Changed, FName RowName) override;`
- L97 _public prototype_ `const UDataTable* GetDataTable() const;` — Get the data table being edited
- L99 _public prototype_ `void HandlePostChange();`
- L101 _public prototype_ `void SetHighlightedRow(FName Name);`
- L103 _public prototype_ `FText GetFilterText() const;`
- L105 _public prototype_ `FSlateColor GetRowTextColor(FName RowName) const;`
- L109 _protected prototype_ `void RefreshCachedDataTable(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);`
- L111 _protected prototype_ `void UpdateVisibleRows(const FName InCachedSelection = NAME_None, const bool bUpdateEvenIfValid = false);`
- L113 _protected prototype_ `void RestoreCachedSelection(const FName InCachedSelection, const bool bUpdateEvenIfValid = false);`
- L115 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L116 _protected prototype_ `void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L118 _protected prototype_ `virtual void PostRegenerateMenusAndToolbars() override;`
- L120 _protected prototype_ `FReply OnFindRowInContentBrowserClicked();`
- L122 _protected prototype_ `FText GetCellText(FDataTableEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;`
- L123 _protected prototype_ `FText GetCellToolTipText(FDataTableEditorRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;`
- L125 _protected prototype_ `TSharedRef<SVerticalBox> CreateContentBox();`
- L127 _protected prototype_ `TSharedRef<SWidget> CreateRowEditorBox();`
- L128 _protected prototype_ `virtual TSharedRef<SRowEditor> CreateRowEditor(UDataTable* Table);`
- L131 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_DataTable( const FSpawnTabArgs& Args );` — Spawns the tab with the data table inside
- L134 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_DataTableDetails(const FSpawnTabArgs& Args);` — Spawns the tab with the data table inside
- L137 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_RowEditor(const FSpawnTabArgs& Args);` — Spawns the tab with the Row Editor inside
- L139 _protected prototype_ `float GetRowNameColumnWidth() const;`
- L140 _protected prototype_ `void RefreshRowNameColumnWidth();`
- L142 _protected prototype_ `float GetRowNumberColumnWidth() const;`
- L143 _protected prototype_ `void RefreshRowNumberColumnWidth();`
- L145 _protected prototype_ `float GetColumnWidth(const int32 ColumnIndex) const;`
- L147 _protected prototype_ `void OnColumnResized(const float NewWidth, const int32 ColumnIndex);`
- L149 _protected prototype_ `void OnRowNameColumnResized(const float NewWidth);`
- L151 _protected prototype_ `void OnRowNumberColumnResized(const float NewWidth);`
- L153 _protected prototype_ `void LoadLayoutData();`
- L155 _protected prototype_ `void SaveLayoutData();`
- L158 _protected prototype_ `TSharedRef<ITableRow> MakeRowWidget(FDataTableEditorRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);` — Make the widget for a row entry in the data table row list view
- L161 _protected prototype_ `TSharedRef<SWidget> MakeCellWidget(FDataTableEditorRowListViewDataPtr InRowDataPtr, const int32 InRowIndex, const FName& InColumnId);` — Make the widget for a cell entry in the data table row list view
- L163 _protected prototype_ `void OnRowSelectionChanged(FDataTableEditorRowListViewDataPtr InNewSelection, ESelectInfo::Type InSelectInfo);`
- L165 _protected prototype_ `void CopySelectedRow();`
- L166 _protected prototype_ `void PasteOnSelectedRow();`
- L167 _protected prototype_ `void DuplicateSelectedRow();`
- L168 _protected prototype_ `void RenameSelectedRowCommand();`
- L169 _protected prototype_ `void DeleteSelectedRow();`
- L172 _protected prototype_ `virtual void CreateAndRegisterDataTableTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the data table data
- L175 _protected prototype_ `virtual void CreateAndRegisterDataTableDetailsTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the data table details
- L178 _protected prototype_ `virtual void CreateAndRegisterRowEditorTab(const TSharedRef<class FTabManager>& InTabManager);` — Helper function for creating and registering the tab containing the row editor
- L180 _protected prototype_ `virtual FString GetDocumentationLink() const override;`
- L182 _protected prototype_ `void OnAddClicked();`
- L183 _protected prototype_ `void OnRemoveClicked();`
- L184 _protected prototype_ `FReply OnMoveRowClicked(FDataTableEditorUtils::ERowMoveDirection MoveDirection);`
- L185 _protected prototype_ `FReply OnMoveToExtentClicked(FDataTableEditorUtils::ERowMoveDirection MoveDirection);`
- L186 _protected prototype_ `void OnCopyClicked();`
- L187 _protected prototype_ `void OnPasteClicked();`
- L188 _protected prototype_ `void OnDuplicateClicked();`
- L189 _protected prototype_ `void OnCopySheetClicked();`
- L190 _protected prototype_ `void OnPasteSheetClicked();`
- L191 _protected prototype_ `bool CanEditTable() const;`
- L193 _protected prototype_ `void SetDefaultSort();`
- L194 _protected prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L195 _protected prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L196 _protected prototype_ `void OnColumnNumberSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L197 _protected prototype_ `void OnColumnNameSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L199 _protected prototype_ `void OnEditDataTableStructClicked();`
- L201 _protected prototype_ `void ExtendToolbar(TSharedPtr<FExtender> Extender);`
- L202 _protected prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder);`
- L205 _private prototype_ `UDataTable* GetEditableDataTable() const;`
- L225 _protected member_ `TSharedPtr<SWidget> DataTableTabWidget;` — UI for the "Data Table" tab
- L228 _protected member_ `TSharedPtr<class IDetailsView> PropertyView;` — Property viewing widget
- L231 _protected member_ `TSharedPtr<SSearchBox> SearchBoxWidget;` — UI for the "Row Editor" tab
- L234 _protected member_ `TSharedPtr<SWidget> RowEditorTabWidget;` — UI for the "Row Editor" tab
- L237 _protected member_ `TArray<FDataTableEditorColumnHeaderDataPtr> AvailableColumns;` — Array of the columns that are available for editing
- L240 _protected member_ `TArray<FDataTableEditorRowListViewDataPtr> AvailableRows;` — Array of the rows that are available for editing
- L243 _protected member_ `TArray<FDataTableEditorRowListViewDataPtr> VisibleRows;` — Array of the rows that match the active filter(s)
- L246 _protected member_ `TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;` — Header row containing entries for each column in AvailableColumns
- L249 _protected member_ `TSharedPtr<SListView<FDataTableEditorRowListViewDataPtr>> CellsListView;` — List view responsible for showing the rows in VisibleRows for each entry in AvailableColumns
- L252 _protected member_ `float RowNameColumnWidth;` — Width of the row name column
- L255 _protected member_ `float RowNumberColumnWidth;` — Width of the row number column
- L258 _protected member_ `TArray<FColumnWidth> ColumnWidths;` — Widths of data table cell columns
- L261 _protected member_ `TSharedPtr<FJsonObject> LayoutData;` — The layout data for the currently loaded data table
- L264 _protected member_ `FName HighlightedRowName;` — The name of the currently selected row
- L267 _protected member_ `int32 HighlightedVisibleRowIndex;` — The visible row index of the currently selected row
- L270 _protected member_ `FText ActiveFilterText;` — The current filter text applied to the data table
- L273 _protected member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L276 _protected member_ `FName SortByColumn;` — Specify which column to sort with
- L278 _protected member_ `FOnRowHighlighted CallbackOnRowHighlighted;`
- L280 _protected member_ `FSimpleDelegate CallbackOnDataTableUndoRedo;`
- L283 _protected member_ `static const FName DataTableTabId;` — The tab id for the data table tab
- L286 _protected member_ `static const FName DataTableDetailsTabId;` — The tab id for the data table details tab
- L289 _protected member_ `static const FName RowEditorTabId;` — The tab id for the row editor tab
- L292 _protected member_ `static const FName RowNameColumnId;` — The column id for the row name list view column
- L295 _protected member_ `static const FName RowNumberColumnId;` — The column id for the row number list view column
- L298 _protected member_ `static const FName RowDragDropColumnId;` — The column id for the drag drop column

#### struct `FDataTableEditor::FColumnWidth`  
`struct FColumnWidth`  
_L210-222_
- desc: Struct holding information about the current column widths
- L212 _public function_ `FColumnWidth() : bIsAutoSized(true) , CurrentWidth(0.0f)`
- L219 _public member_ `bool bIsAutoSized;` — True if this column is being auto-sized rather than sized by the user
- L221 _public member_ `float CurrentWidth;` — The width of the column, either sized by the user, or auto-sized

#### Free symbols / members of external scopes

- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRowHighlighted, FName );`
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRowHighlighted, FName );`

### `Source/Editor/DataTableEditor/Private/DataTableEditorSettings.h` (Private)


#### class `UDataTableEditorSettings`  
`class UDataTableEditorSettings : public UDeveloperSettings`  
_L15-23_
- reflection: `UCLASS(MinimalAPI, config = EditorSettings)`
- inherits: `UDeveloperSettings`
- L22 _public member_ `bool bCopyAsSpreadsheetCells = false;` — `UPROPERTY(EditAnywhere, config, Category = SpreadsheetInteraction)` — Set to true to format copied data for pasting into a spreadsheet

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATATABLEEDITOR_API`

### `Source/Editor/DataTableEditor/Private/SCompositeRowEditor.h` (Private)


#### class `SCompositeRowEditor`  
`class SCompositeRowEditor : public SRowEditor`  
_L14-34_
- inherits: `SRowEditor`
- L16 _private function_ `SLATE_BEGIN_ARGS(SRowEditor)`
- L19 _private prototype_ `SCompositeRowEditor();`
- L20 _private prototype_ `virtual ~SCompositeRowEditor();`
- L22 _private prototype_ `void Construct(const FArguments& InArgs, UDataTable* Changed);`
- L25 _protected prototype_ `virtual FReply OnAddClicked() override;`
- L26 _protected prototype_ `virtual FReply OnRemoveClicked() override;`
- L27 _protected prototype_ `virtual FReply OnMoveRowClicked(FDataTableEditorUtils::ERowMoveDirection MoveDirection) override;`
- L29 _protected prototype_ `virtual bool IsMoveRowUpEnabled() const override;`
- L30 _protected prototype_ `virtual bool IsMoveRowDownEnabled() const override;`
- L31 _protected prototype_ `virtual bool IsAddRowEnabled() const override;`
- L32 _protected prototype_ `virtual bool IsRemoveRowEnabled() const override;`
- L33 _protected prototype_ `virtual EVisibility GetRenameVisibility() const override;`

### `Source/Editor/DataTableEditor/Private/SDataTableListViewRow.h` (Private)


#### class `SDataTableRowHandle`  
`class SDataTableRowHandle: public SCompoundWidget`  
_L35-57_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS(SDataTableRowHandle)`
- L40 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<SDataTableListViewRow>, ParentRow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L52 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L53 _public prototype_ `TSharedPtr<class FDataTableRowDragDropOp> CreateDragDropOperation(TSharedPtr<SDataTableListViewRow> InRow);`
- L56 _private member_ `TWeakPtr<SDataTableListViewRow> ParentRow;`

#### class `SDataTableListViewRow`  
`class SDataTableListViewRow : public SMultiColumnTableRow<FDataTableEditorRowListViewDataPtr>`  
_L63-125_
- inherits: `SMultiColumnTableRow<FDataTableEditorRowListViewDataPtr>`
- desc: A widget to represent a row in a Data Table Editor widget. This widget allows us to do things like right-click and take actions on a particular row of a Data Table.
- L67 _public function_ `SLATE_BEGIN_ARGS(SDataTableListViewRow) : _IsEditable(true)`
- L72 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDataTableEditor>, DataTableEditor) SLATE_ARGUMENT(FDataTableEditorRowListViewDataPtr, RowDataPtr) SLATE_ARGUMENT(bool, IsEditable) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — The owning object. This allows us access to the actual data table being edited as well as some other API functions.
- L80 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L82 _public prototype_ `void OnRowRenamed(const FText& Text, ETextCommit::Type CommitType);`
- L84 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L86 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L88 _public prototype_ `FText GetCurrentNameAsText() const;`
- L89 _public prototype_ `FName GetCurrentName() const;`
- L90 _public prototype_ `uint32 GetCurrentIndex() const;`
- L92 _public prototype_ `const TArray<FText>& GetCellValues() const;`
- L94 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L96 _public prototype_ `void SetRowForRename();`
- L98 _public prototype_ `void SetIsDragDrop(bool bInIsDragDrop);`
- L100 _public prototype_ `const FDataTableEditorRowListViewDataPtr& GetRowDataPtr() const;`
- L104 _private prototype_ `FReply OnRowDrop(const FDragDropEvent& DragDropEvent);`
- L106 _private prototype_ `TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);`
- L108 _private prototype_ `void OnRowDragEnter(const FDragDropEvent& DragDropEvent);`
- L109 _private prototype_ `void OnRowDragLeave(const FDragDropEvent& DragDropEvent);`
- L111 _private prototype_ `virtual const FSlateBrush* GetBorder() const;`
- L113 _private prototype_ `TSharedRef<SWidget> MakeRowActionsMenu();`
- L115 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableText;`
- L117 _private member_ `TSharedPtr<FName> CurrentName;`
- L119 _private member_ `FDataTableEditorRowListViewDataPtr RowDataPtr;`
- L120 _private member_ `TWeakPtr<FDataTableEditor> DataTableEditor;`
- L122 _private member_ `bool IsEditable;`
- L123 _private member_ `bool bIsDragDropObject;`
- L124 _private member_ `bool bIsHoveredDragTarget;`

#### class `FDataTableRowDragDropOp`  
`class FDataTableRowDragDropOp : public FDecoratedDragDropOp`  
_L127-145_
- inherits: `FDecoratedDragDropOp`
- L130 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FDataTableRowDragDropOp, FDecoratedDragDropOp) FDataTableRowDragDropOp(TSharedPtr<SDataTableListViewRow> InRow);`
- L134 _public prototype_ `void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent);`
- L136 _public member_ `TSharedPtr<SWidget> DecoratorWidget;`
- L138 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L143 _public member_ `TWeakPtr<class SDataTableListViewRow> Row;`

### `Source/Editor/DataTableEditor/Private/SRowEditor.h` (Private)


#### class `SRowEditor`  
`class SRowEditor : public SCompoundWidget , public FNotifyHook , public FStructureEditorUtils::INotifyOnStructChanged , public FDataTableEditorUtils::INotifyOnDataTableChanged`  
_L40-112_
- inherits: `SCompoundWidget,FNotifyHook,FStructureEditorUtils::INotifyOnStructChanged,FDataTableEditorUtils::INotifyOnDataTableChanged`
- L46 _public function_ `SLATE_BEGIN_ARGS(SRowEditor)`
- L49 _public prototype_ `SRowEditor();`
- L50 _public prototype_ `virtual ~SRowEditor();`
- L53 _public prototype_ `virtual void NotifyPreChange( FProperty* PropertyAboutToChange ) override;` — FNotifyHook
- L54 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;`
- L57 _public prototype_ `virtual void PreChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;` — INotifyOnStructChanged
- L58 _public prototype_ `virtual void PostChange(const class UUserDefinedStruct* Struct, FStructureEditorUtils::EStructureEditorChangeInfo Info) override;`
- L61 _public prototype_ `virtual void PreChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;` — INotifyOnDataTableChanged
- L62 _public prototype_ `virtual void PostChange(const UDataTable* Changed, FDataTableEditorUtils::EDataTableChangeInfo Info) override;`
- L64 _public member_ `FOnRowSelected RowSelectedCallback;`
- L68 _protected member_ `TArray<TSharedPtr<FName>> CachedRowNames;`
- L69 _protected member_ `TSharedPtr<FStructOnScope> CurrentRow;`
- L70 _protected member_ `TSoftObjectPtr<UDataTable> DataTable;` — weak obj ptr couldn't handle reimporting
- L71 _protected member_ `TSharedPtr<class IStructureDetailsView> StructureDetailsView;`
- L72 _protected member_ `TSharedPtr<FName> SelectedName;`
- L73 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> RowComboBox;`
- L75 _protected prototype_ `void RefreshNameList();`
- L76 _protected prototype_ `void CleanBeforeChange();`
- L77 _protected prototype_ `void Restore();`
- L80 _protected prototype_ `virtual bool IsMoveRowUpEnabled() const;` — Functions for enabling, disabling, and hiding portions of the row editor
- L81 _protected prototype_ `virtual bool IsMoveRowDownEnabled() const;`
- L82 _protected prototype_ `virtual bool IsAddRowEnabled() const;`
- L83 _protected prototype_ `virtual bool IsRemoveRowEnabled() const;`
- L84 _protected prototype_ `virtual EVisibility GetRenameVisibility() const;`
- L86 _protected prototype_ `UScriptStruct* GetScriptStruct() const;`
- L88 _protected prototype_ `FName GetCurrentName() const;`
- L89 _protected prototype_ `FText GetCurrentNameAsText() const;`
- L90 _protected prototype_ `FString GetStructureDisplayName() const;`
- L91 _protected prototype_ `TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FName> InItem);`
- L92 _protected prototype_ `virtual void OnSelectionChanged(TSharedPtr<FName> InItem, ESelectInfo::Type InSeletionInfo);`
- L94 _protected prototype_ `virtual FReply OnAddClicked();`
- L95 _protected prototype_ `virtual FReply OnRemoveClicked();`
- L96 _protected prototype_ `virtual FReply OnMoveRowClicked(FDataTableEditorUtils::ERowMoveDirection MoveDirection);`
- L97 _protected prototype_ `FReply OnMoveToExtentClicked(FDataTableEditorUtils::ERowMoveDirection MoveDirection);`
- L98 _protected prototype_ `void OnRowRenamed(const FText& Text, ETextCommit::Type CommitType);`
- L99 _protected prototype_ `FReply OnResetToDefaultClicked();`
- L100 _protected prototype_ `EVisibility GetResetToDefaultVisibility() const ;`
- L102 _protected prototype_ `void ConstructInternal(UDataTable* Changed);`
- L106 _public prototype_ `void Construct(const FArguments& InArgs, UDataTable* Changed);`
- L108 _public prototype_ `void SelectRow(FName Name);`
- L110 _public prototype_ `void HandleUndoRedo();`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRowModified, FName );`
- L37 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRowModified, FName );`
- L38 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRowSelected, FName );`
- L38 _prototype_ `DECLARE_DELEGATE_OneParam(FOnRowSelected, FName );`

### `Source/Editor/DataTableEditor/Public/DataTableEditorModule.h` (Public)


#### class `FDataTableEditorModule`  
`class FDataTableEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L17-54_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: DataTable Editor module
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public prototype_ `virtual TSharedRef<IDataTableEditor> CreateDataTableEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table );` — Creates an instance of table editor object.  Only virtual so that it can be called across the DLL boundary. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Table					The table to start editing @return	Interface to the new table editor
- L38 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L40 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L43 _public member_ `static const FName DataTableEditorAppIdentifier;` — DataTable Editor app identifier string
- L46 _private prototype_ `TSharedRef<IDataTableEditor> CreateStandardDataTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table);`
- L48 _private prototype_ `TSharedRef<IDataTableEditor> CreateCompositeDataTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UDataTable* Table);`
- L50 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L51 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`

### `Source/Editor/DataTableEditor/Public/DataTableRowMenuContext.h` (Public)


#### class `UDataTableRowMenuContext`  
`class UDataTableRowMenuContext : public UAssetEditorToolkitMenuContext`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UAssetEditorToolkitMenuContext`
- L18 _public member_ `FDataTableEditorRowListViewDataPtr RowDataPtr;`

### `Source/Editor/DataTableEditor/Public/IDataTableEditor.h` (Public)


#### class `IDataTableEditor`  
`class IDataTableEditor : public FAssetEditorToolkit`  
_L10-16_
- inherits: `FAssetEditorToolkit`
- desc: DataTable Editor public interface
