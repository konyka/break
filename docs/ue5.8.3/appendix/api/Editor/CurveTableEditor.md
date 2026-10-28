# Editor / CurveTableEditor

- module root: `Source/Editor/CurveTableEditor`
- headers: 8; symbols: 143
- symbol kinds: class=7, enum=1, enumerator=2, function=14, member=28, prototype=89, struct=1, typedef=1
- DynamicallyLoadedModuleNames: WorkspaceMenuStructure
- PrivateDependencyModuleNames: Core, CoreUObject, CurveEditor, EditorFramework, EditorWidgets, Engine, InputCore, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicIncludePathModuleNames: LevelEditor

### `Source/Editor/CurveTableEditor/Private/CompositeCurveTableEditor.h` (Private)


#### class `FCompositeCurveTableEditor`  
`class FCompositeCurveTableEditor : public FCurveTableEditor`  
_L17-49_
- inherits: `FCurveTableEditor`
- desc: Viewer/editor for a CurveTable
- L24 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L25 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L27 _public prototype_ `virtual void InitCurveTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveTable* Table) override;`
- L29 _public prototype_ `void CreateAndRegisterPropertiesTab(const TSharedRef<class FTabManager>& InTabManager);`
- L32 _public prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the tab with the details view inside
- L35 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L36 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L39 _protected prototype_ `virtual TSharedRef< FTabManager::FLayout > InitCurveTableLayout() override;`
- L41 _protected function_ `virtual bool ShouldCreateDefaultStandaloneMenu() const override`
- L42 _protected function_ `virtual bool ShouldCreateDefaultToolbar() const override`
- L46 _private member_ `TSharedPtr< class IDetailsView > DetailsView;` — Details view
- L48 _private member_ `static const FName PropertiesTabId;`

### `Source/Editor/CurveTableEditor/Private/CurveTableEditor.h` (Private)


#### enum `ECurveTableViewMode`  
`enum class ECurveTableViewMode : int32`  
_L43-50_
- desc: The manner in which curve tables are displayed
- L46 _public enumerator_ `Grid` — Displays values in a spreadsheet-like table
- L49 _public enumerator_ `CurveTable` — Displays values as curves

#### class `FCurveTableEditor`  
`class FCurveTableEditor : public ICurveTableEditor , public FCurveTableEditorUtils::INotifyOnCurveTableChanged , public FEditorUndoClient`  
_L57-237_
- inherits: `ICurveTableEditor,FCurveTableEditorUtils::INotifyOnCurveTableChanged,FEditorUndoClient`
- desc: Viewer/Editor for a CurveTable
- L64 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L65 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L74 _public prototype_ `virtual void InitCurveTableEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveTable* Table );` — Edits the specified table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Table					The table to edit
- L77 _public prototype_ `virtual ~FCurveTableEditor();` — Destructor
- L80 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L81 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L82 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L83 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L86 _public prototype_ `virtual void PreChange(const UCurveTable* Changed, FCurveTableEditorUtils::ECurveTableChangeInfo Info) override;` — INotifyOnDataTableChanged
- L87 _public prototype_ `virtual void PostChange(const UCurveTable* Changed, FCurveTableEditorUtils::ECurveTableChangeInfo Info) override;`
- L88 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L89 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L92 _public prototype_ `UCurveTable* GetCurveTable() const;` — Get the curve table being edited
- L95 _public prototype_ `bool IsReadOnly() const;` — Determine if the table being viewed, can be edited or is read-only
- L98 _public function_ `TSharedPtr<FCurveEditor> GetCurveEditor() const` — Get the curve editor used for the Curve View
- L100 _public prototype_ `void HandlePostChange();`
- L103 _public prototype_ `TSharedRef<SDockTab> SpawnTab_CurveTable( const FSpawnTabArgs& Args );` — Spawns the tab with the curve table inside
- L106 _public function_ `ECurveTableViewMode GetViewMode() const` — Get the mode that we are displaying data in
- L109 _public prototype_ `void HandleCurveRename(FCurveEditorTreeItemID& TreeID, FName& OldCurveName, FName& NewCurveName);` — Rename a specific curve
- L112 _public prototype_ `TSharedPtr<SWidget> OnOpenCurveMenu();` — Pop open context Menu
- L115 _public prototype_ `void OnDeleteCurves();` — Callback for R-Click Menu Delete Curves
- L118 _public prototype_ `void OnRenameCurve();` — Callback for R-Click Menu Rename Selected Curve
- L121 _public prototype_ `void OnDeleteKeyColumn(float KeyTime);` — Callback for R-Click Menu Delete Key Column
- L124 _public prototype_ `bool VerifyValidRetime(const FText& InText, FText& OutErrorMessage, float OriginalTime);` — Ensure that whatever time we are reetiming to is not redundant
- L127 _public prototype_ `void HandleRetimeCommitted(const FText& InText, ETextCommit::Type CommitInfo, float OriginalKeyTime);` — Process the retime from the header column text entry
- L132 _protected prototype_ `virtual TSharedRef< FTabManager::FLayout > InitCurveTableLayout();` — Handles setting up slate for the curve table editor
- L135 _protected prototype_ `void ExtendMenu();` — Add extra menu items
- L138 _protected prototype_ `void ExtendToolbar();` — Add extra menu items
- L141 _protected prototype_ `void BindCommands();` — Bind commands to delegates
- L144 _protected prototype_ `void RefreshCachedCurveTable();` — Update the cached state of this curve table, and then reflect that new state in the UI
- L147 _protected prototype_ `TSharedRef<SWidget> MakeToolbar(TSharedRef<SCurveEditorPanel>& CurveEditorPanel);` — Make the toolbar
- L150 _protected prototype_ `void OnCurveTreeViewScrolled(double InScrollOffset);` — Called when the CurveEditorTree view is scrolled - used to keep the two list views in sync
- L153 _protected prototype_ `void OnTableViewScrolled(double InScrollOffset);` — Called when the Table View is scrolled - used to keep the two list views in sync
- L156 _protected prototype_ `void OnTableViewSelectionChanged(FCurveEditorTreeItemID ItemID, ESelectInfo::Type);` — Called when someone selected a row directly in the TableView - used to keep selection in sync between CurveTree  and TableView
- L159 _protected prototype_ `void OnPostReimport(UObject* InObject, bool);` — Called when an asset has finished being imported
- L162 _protected prototype_ `EVisibility GetTableViewControlsVisibility() const;` — Control control visibility based on view mode
- L165 _protected prototype_ `EVisibility GetCurveViewControlsVisibility() const;` — Control control visibility based on view mode
- L168 _protected prototype_ `FReply OnAddCurveClicked();` — Add New Curve Callback
- L171 _protected prototype_ `void OnAddNewKeyColumn();` — Callback For SimpleCurves, add a new Key/Column
- L174 _protected prototype_ `void AddNewKeyColumn(float NewKeyTime);` — Adds new key for all (Simple) curves in the table at given time
- L177 _protected prototype_ `void ToggleViewMode();` — Toggle between curve & grid view
- L180 _protected prototype_ `bool IsCurveViewChecked() const;` — Get whether the curve view checkbox should be toggled on
- L183 _protected prototype_ `void OnRequestCurveRename(FCurveEditorTreeItemID TreeItemId);` — Invoke UI for Renaming a Curve
- L185 _protected function_ `virtual bool ShouldCreateDefaultStandaloneMenu() const`
- L186 _protected function_ `virtual bool ShouldCreateDefaultToolbar() const`
- L188 _protected prototype_ `SHeaderRow::FColumn::FArguments GenerateHeaderColumnForKey(FCurveTableEditorColumnHeaderDataPtr ColumnData);`
- L191 _protected member_ `TArray<FCurveTableEditorColumnHeaderDataPtr> AvailableColumns;` — Array of the columns that are available for editing
- L194 _protected member_ `TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;` — Header row containing entries for each column in AvailableColumns
- L197 _protected member_ `TSharedPtr<SListView<FCurveEditorTreeItemID>> TableView;` — List view responsible for showing the rows from AvailableColumns
- L200 _protected member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender
- L203 _protected member_ `TSharedPtr<FExtender> ToolbarExtender;` — Menu extender
- L206 _protected member_ `static const FName CurveTableTabId;` — The tab id for the curve table tab
- L209 _protected member_ `ECurveTableViewMode ViewMode;` — The manner in which curve tables are displayed
- L212 _protected member_ `TSharedPtr<FCurveEditor> CurveEditor;` — The Curve Editor
- L215 _protected member_ `TSharedPtr<class SCurveEditorTree> CurveEditorTree;` — The Data Model that holds the source items for Views (TreeView, TableView)
- L217 _protected member_ `bool bUpdatingTableViewSelection;`
- L220 _protected prototype_ `void RefreshTableRows();` — Sync Filtered from the CurveEditorTree model to the TableView
- L223 _protected prototype_ `void RefreshTableRowsSelection();` — Sync selected rows from the CurveEditorTree model to the TableView
- L226 _protected member_ `FSimpleMulticastDelegate OnColumnsChanged;` — A delegate to let item rows know when the number of columns have changed
- L229 _protected member_ `TArray<FCurveEditorTreeItemID> EmptyItems;` — An empty source list used to initialize or when rebuilding the TableView
- L232 _protected member_ `TMap< FCurveEditorTreeItemID, FName > RowIDMap;` — Associates the CurveEditor Ids with the FName Ids from the Curve Table
- L235 _protected member_ `ERichCurveInterpMode InterpMode;` — The default interpolation type of the curves within the table

#### Free symbols / members of external scopes

- L54 _typedef_ `typedef TSharedPtr<FCurveTableEditorColumnHeaderData> FCurveTableEditorColumnHeaderDataPtr;`

### `Source/Editor/CurveTableEditor/Private/CurveTableEditorCommands.h` (Private)


#### class `FCurveTableEditorCommands`  
`class FCurveTableEditorCommands : public TCommands<FCurveTableEditorCommands>`  
_L15-32_
- inherits: `TCommands<FCurveTableEditorCommands>`
- L18 _public function_ `FCurveTableEditorCommands() : TCommands<FCurveTableEditorCommands>(TEXT("CurveTableEditor"), NSLOCTEXT("Contexts", "CurveTableEditor", "Curve Table Editor"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> CurveViewToggle;` — Command to allow users to toggle the view mode
- L29 _public member_ `TSharedPtr<FUICommandInfo> AppendKeyColumn;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> RenameSelectedCurve;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelectedCurves;`

### `Source/Editor/CurveTableEditor/Private/CurveTableEditorHandle.h` (Private)


#### struct `FCurveTableEditorHandle`  
`struct FCurveTableEditorHandle : public FCurveOwnerInterface`  
_L20-70_
- inherits: `FCurveOwnerInterface`
- desc: Handle to a particular row in a table, used for editing individual curves
- L22 _public function_ `FCurveTableEditorHandle() : CurveTable(nullptr) , RowName(NAME_None)`
- L27 _public function_ `FCurveTableEditorHandle(UCurveTable* InCurveTable, FName InRowName) : CurveTable(InCurveTable) , RowName(InRowName)`
- L33 _public member_ `TWeakObjectPtr<UCurveTable> CurveTable;` — Pointer to table we want a row from
- L36 _public member_ `FName RowName;` — Name of row in the table that we want
- L40 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")`
- L41 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L42 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L43 _public prototype_ `virtual void ModifyOwner() override;`
- L44 _public prototype_ `virtual void MakeTransactional() override;`
- L45 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L46 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L47 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L53 _public function_ `bool IsValid() const` — Returns true if the curve is valid
- L59 _public function_ `bool IsNull() const` — Returns true if this handle is specifically pointing to nothing
- L65 _public prototype_ `FRealCurve* GetCurve() const;` — Get the curve straight from the row handle
- L66 _public prototype_ `FRichCurve* GetRichCurve() const;`
- L69 _public prototype_ `bool HasRichCurves() const;` — Returns true if the owning table uses RichCurves instead of Real Curves

### `Source/Editor/CurveTableEditor/Private/RealCurveModel.h` (Private)


#### class `FRealCurveModel`  
`class FRealCurveModel : public FCurveModel`  
_L29-73_
- inherits: `FCurveModel`
- L32 _public member_ `static ECurveEditorViewID EventView;`
- L34 _public prototype_ `explicit FRealCurveModel(FCurveTableEditorHandle InRealCurveHandle, UObject* InOwner);`
- L37 _public prototype_ `virtual const void* GetCurve() const override;` — FCurveModel interface
- L39 _public prototype_ `virtual void Modify() override;`
- L41 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L42 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L43 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L44 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKey, double InCurrentTime) override;`
- L46 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L47 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L48 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L50 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L52 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L53 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L55 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L56 _public prototype_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override;`
- L58 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L60 _public function_ `virtual bool IsValid() const`
- L64 _private member_ `const TWeakObjectPtr<> WeakOwner;`
- L65 _private member_ `const FCurveTableEditorHandle RealCurveHandle;`
- L67 _private function_ `FRealCurve* ResolveCurve(bool bEnsure = true) const`

### `Source/Editor/CurveTableEditor/Private/RichCurveEditorModelByHandle.h` (Private)


#### class `FRichCurveEditorModelByHandle`  
`class FRichCurveEditorModelByHandle : public FRichCurveEditorModel`  
_L19-35_
- inherits: `FRichCurveEditorModel`
- desc: Rich curve model that resolves its curve through an attribute on every access instead of caching a raw pointer. UCurveTable stores its rows as individual heap allocations which are deleted and reallocated wholesale whenever the table is re-serialized, as happens during an undo. A model holding a raw FRichCurve* is left pointing at freed memory until the owning editor rebuilds it, so anything reading the model in the meantime - selection cleansing, key proxies, drawing - reads that freed memory.
- L23 _public prototype_ `FRichCurveEditorModelByHandle(FCurveTableEditorHandle InCurveHandle, UObject* InOwner);`
- L26 _public prototype_ `virtual bool IsValid() const override;`
- L27 _public prototype_ `virtual FRichCurve& GetRichCurve() override;`
- L28 _public prototype_ `virtual const FRichCurve& GetReadOnlyRichCurve() const override;`
- L34 _private member_ `const FCurveTableEditorHandle CurveHandle;` — Re-resolved on every access.

### `Source/Editor/CurveTableEditor/Public/CurveTableEditorModule.h` (Public)


#### class `FCurveTableEditorModule`  
`class FCurveTableEditorModule : public IModuleInterface, public IHasMenuExtensibility`  
_L17-52_
- inherits: `IModuleInterface,IHasMenuExtensibility`
- desc: CurveTable Editor module
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public prototype_ `virtual TSharedRef<ICurveTableEditor> CreateCurveTableEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveTable* Table );` — Creates an instance of table editor object.  Only virtual so that it can be called across the DLL boundary. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	Table					The table to start editing @return	Interface to the new table editor
- L38 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L41 _public member_ `static const FName CurveTableEditorAppIdentifier;` — CurveTable Editor app identifier string
- L46 _private prototype_ `TSharedRef<ICurveTableEditor> CreateStandardCurveTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveTable* Table);` — Helper function to create the curve table editor for standard curve tables
- L49 _private prototype_ `TSharedRef<ICurveTableEditor> CreateCompositeCurveTableEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UCurveTable* Table);` — Helper function to create the curve table editor for composite curve tables
- L51 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`

### `Source/Editor/CurveTableEditor/Public/ICurveTableEditor.h` (Public)


#### class `ICurveTableEditor`  
`class ICurveTableEditor : public FAssetEditorToolkit`  
_L10-17_
- inherits: `FAssetEditorToolkit`
- desc: CurveTable Editor public interface
