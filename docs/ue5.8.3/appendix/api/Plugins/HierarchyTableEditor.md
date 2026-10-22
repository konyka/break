# Plugins / HierarchyTableEditor

- module root: `Plugins/Experimental/Animation/HierarchyTable/Source/Editor`
- headers: 11; symbols: 123
- symbol kinds: class=9, delegate=3, function=16, macro=2, member=25, prototype=64, struct=4

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Private/DefaultHierarchyTableTypeHandler.h` (Private)


#### class `UHierarchyTable_TableTypeHandler_Default`  
`class UHierarchyTable_TableTypeHandler_Default final : public UHierarchyTable_TableTypeHandler`  
_L10-18_
- reflection: `UCLASS()`
- inherits: `UHierarchyTable_TableTypeHandler`
- L15 _public prototype_ `virtual void ConstructHierarchy() override;`
- L17 _public prototype_ `virtual bool FactoryConfigureProperties(FInstancedStruct& TableType) const override;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Private/FloatColumn.h` (Private)


#### struct `FHierarchyTableColumn_Float`  
`struct FHierarchyTableColumn_Float : public IHierarchyTableColumn`  
_L9-18_
- inherits: `IHierarchyTableColumn`
- L12 _public function_ `virtual FName GetColumnId() const override`
- L13 _public function_ `virtual FText GetColumnLabel() const override`
- L14 _public function_ `virtual float GetColumnSize() const override`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateEntryWidget(TObjectPtr<UHierarchyTable> HierarchyTable, int32 EntryIndex);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateHeaderWidget();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "HierarchyTableColumn_Float"`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Private/SHierarchyTable.h` (Private)


#### class `SHierarchyTable`  
`class SHierarchyTable : public IHierarchyTable, public FSelfRegisteringEditorUndoClient, public FGCObject`  
_L17-84_
- inherits: `IHierarchyTable,FSelfRegisteringEditorUndoClient,FGCObject`
- L22 _public function_ `SLATE_BEGIN_ARGS(SHierarchyTable)`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, TObjectPtr<UHierarchyTable> InHierarchyTable);`
- L42 _public prototype_ `~SHierarchyTable();`
- L45 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SCompoundWidget
- L48 _public prototype_ `int32 GetSelectedEntryIndex() const override;` — IHierarchyTable
- L51 _public prototype_ `void PostUndo(bool bSuccess) override;` — FSelfRegisteringEditorUndoClient
- L52 _public prototype_ `void PostRedo(bool bSuccess) override;`
- L55 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L56 _public prototype_ `virtual FString GetReferencerName() const override;`
- L59 _private prototype_ `void TreeView_HandleGetChildren(TSharedPtr<FTreeItem> InItem, TArray<TSharedPtr<FTreeItem>>& OutChildren) const;`
- L61 _private prototype_ `void TreeView_OnItemScrolledIntoView(TSharedPtr<FTreeItem> InItem, const TSharedPtr<ITableRow>& InWidget);`
- L63 _private prototype_ `TSharedRef<ITableRow> TreeView_GenerateItemRow(TSharedPtr<FTreeItem> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L65 _private prototype_ `TSharedPtr<SWidget> TreeView_HandleContextMenuOpening();`
- L68 _private prototype_ `TArray<TSharedPtr<FTreeItem>> GetAllTreeItems();`
- L70 _private prototype_ `void RegenerateTreeViewItems();`
- L73 _private member_ `TSharedPtr<STreeView<TSharedPtr<FTreeItem>>> TreeView;`
- L75 _private member_ `TArray<TSharedPtr<FTreeItem>> RootItems;`
- L77 _private member_ `TSharedPtr<FTreeItem> DeferredRenameRequest;`
- L79 _private member_ `TObjectPtr<UHierarchyTable> HierarchyTable;`
- L81 _private member_ `TObjectPtr<UHierarchyTable_TableTypeHandler> TableHandler;`
- L83 _private member_ `FGuid TableHierarchyGuid;`

#### struct `SHierarchyTable::FColumns`  
`struct FColumns`  
_L25-29_
- L27 _public member_ `static const FName IdentifierId;`
- L28 _public member_ `static const FName OverrideId;`

#### struct `SHierarchyTable::FTreeItem`  
`struct FTreeItem`  
_L31-39_
- L33 _public member_ `int32 Index;`
- L34 _public member_ `FName Name;`
- L35 _public member_ `TArray<TSharedPtr<FTreeItem>> Children;`
- L37 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);`
- L38 _public member_ `FOnRenameRequested OnRenameRequested;`

#### Free symbols / members of external scopes

- L37 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Private/SHierarchyTableRow.h` (Private)


#### class `SHierarchyTableRow`  
`class SHierarchyTableRow : public SMultiColumnTableRow<TSharedPtr<SHierarchyTable::FTreeItem>>`  
_L11-39_
- inherits: `SMultiColumnTableRow<TSharedPtr<SHierarchyTable::FTreeItem>>`
- L14 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool , FOnRenamed, FName );`
- L15 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnReparented, FName , FName );`
- L17 _public function_ `SLATE_BEGIN_ARGS(SHierarchyTableRow)`
- L18 _public prototype_ `SLATE_EVENT(FOnRenamed, OnRenamed);`
- L19 _public prototype_ `SLATE_EVENT(FOnReparented, OnReparented);`
- L20 _public prototype_ `SLATE_END_ARGS() FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L24 _public prototype_ `TOptional<EItemDropZone> OnCanAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<SHierarchyTable::FTreeItem> TargetItem);`
- L26 _public prototype_ `FReply OnAcceptDrop(const FDragDropEvent& DragDropEvent, EItemDropZone DropZone, TSharedPtr<SHierarchyTable::FTreeItem> TargetItem);`
- L28 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedPtr<SHierarchyTable> InHierarchyTableWidget, TSharedPtr<SHierarchyTable::FTreeItem> InTreeItem);`
- L30 _public prototype_ `void OnCommitRename(const FText& InText, ETextCommit::Type CommitInfo);`
- L32 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L35 _private member_ `TSharedPtr<SHierarchyTable> HierarchyTableWidget;`
- L36 _private member_ `TSharedPtr<SHierarchyTable::FTreeItem> TreeItem;`
- L37 _private member_ `FOnRenamed OnRenamed;`
- L38 _private member_ `FOnReparented OnReparented;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool , FOnRenamed, FName );`
- L15 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnReparented, FName , FName );`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/HierarchyTableAssetDefinition.h` (Public)


#### class `UAssetDefinition_HierarchyTable`  
`class UAssetDefinition_HierarchyTable : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/HierarchyTableEditorModule.h` (Public)


#### class `FHierarchyTableEditorModule`  
`class FHierarchyTableEditorModule : public IModuleInterface`  
_L14-45_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `TSharedRef<IHierarchyTable> CreateHierarchyTableWidget(const TObjectPtr<UHierarchyTable> HierarchyTable);`
- L23 _public prototype_ `void RegisterTableType(const UScriptStruct* TableType, const UClass* Handler);`
- L25 _public prototype_ `void UnregisterTableType(const UScriptStruct* TableType);`
- L27 _public prototype_ `const TObjectPtr<UHierarchyTable_TableTypeHandler> CreateTableHandler(const TObjectPtr<UHierarchyTable> HierarchyTable);`
- L29 _public prototype_ `const TObjectPtr<UHierarchyTable_TableTypeHandler> CreateTableHandler(const TObjectPtr<const UScriptStruct> TableType);`
- L31 _public prototype_ `void RegisterElementTypeEditorColumns(const UScriptStruct* ElementType, const TArray<TSharedPtr<IHierarchyTableColumn>> Columns);`
- L33 _public prototype_ `void UnregisterElementTypeEditorColumns(const UScriptStruct* ElementType);`
- L35 _public prototype_ `TArray<TSharedPtr<IHierarchyTableColumn>> GetElementTypeEditorColumns(const TObjectPtr<const UHierarchyTable> HierarchyTable);`
- L38 _private member_ `TArray<TWeakObjectPtr<UScriptStruct>> BuiltinTableTypes;`
- L40 _private member_ `TArray<TWeakObjectPtr<UScriptStruct>> BuiltinElementTypes;`
- L42 _private member_ `TMap<TObjectKey<UScriptStruct>, const UClass*> TableHandlers;`
- L44 _private member_ `TMap<TObjectKey<UScriptStruct>, TArray<TSharedPtr<IHierarchyTableColumn>>> EditorColumns;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/HierarchyTableEditorToolkit.h` (Public)


#### class `FHierarchyTableEditorToolkit`  
`class FHierarchyTableEditorToolkit : public FAssetEditorToolkit`  
_L11-33_
- inherits: `FAssetEditorToolkit`
- L14 _public prototype_ `void InitEditor(const TArray<UObject*>& InObjects);`
- L17 _public prototype_ `void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L18 _public prototype_ `void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L20 _public function_ `FName GetToolkitFName() const override`
- L21 _public function_ `FText GetBaseToolkitName() const override`
- L22 _public function_ `FString GetWorldCentricTabPrefix() const override`
- L23 _public function_ `FLinearColor GetWorldCentricTabColorScale() const override`
- L26 _public prototype_ `void ExtendToolbar();`
- L28 _private prototype_ `void HandleOnEntryAdded(const int32 EntryIndex);`
- L30 _private member_ `TObjectPtr<UHierarchyTable> HierarchyTable;`
- L32 _private member_ `TSharedPtr<SHierarchyTable> HierarchyTableWidget;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/HierarchyTableFactory.h` (Public)


#### class `UHierarchyTableFactory`  
`class UHierarchyTableFactory : public UFactory`  
_L15-34_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L20 _public prototype_ `UHierarchyTableFactory();`
- L23 _public prototype_ `UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L24 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _private prototype_ `bool ConfigureTableType();`
- L29 _private prototype_ `bool ConfigureElementType();`
- L31 _private member_ `FInstancedStruct TableMetadata;`
- L33 _private member_ `const UScriptStruct* ElementType;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/HierarchyTableTypeHandler.h` (Public)


#### class `UHierarchyTable_TableTypeHandler`  
`class UHierarchyTable_TableTypeHandler : public UObject`  
_L22-55_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L27 _public function_ `void SetHierarchyTable(TObjectPtr<UHierarchyTable> InHierarchyTable)`
- L30 _public function_ `virtual bool FactoryConfigureProperties(FInstancedStruct& TableType) const` — Override to provide additional configurable properties when creating a new hierarchy table of this table type
- L33 _public function_ `virtual void ExtendToolbar(UToolMenu* ToolMenu, IHierarchyTable& HierarchyTableView) const` — Override to add additional buttons to the editor toolbar
- L36 _public function_ `virtual void ExtendContextMenu(FMenuBuilder& MenuBuilder, IHierarchyTable& HierarchyTableView) const` — Override to customize the context menu constructed for a particular entry in the table
- L39 _public prototype_ `virtual FSlateIcon GetEntryIcon(const int32 EntryIndex) const;` — Override to provide an icon for a particular entry in the table
- L42 _public prototype_ `virtual FSlateColor GetEntryIconColor(const int32 EntryIndex) const;` — Override to provide an icon color for a particular entry in the table
- L45 _public function_ `virtual void ConstructHierarchy()` — Resets and builds the hierarchy table data according to the current table metadata
- L47 _public function_ `virtual bool CanRenameEntry(const int32 EntryIndex) const`
- L48 _public prototype_ `virtual bool RenameEntry(const int32 EntryIndex, const FName NewName);`
- L50 _public function_ `virtual bool CanRemoveEntry(const int32 EntryIndex) const`
- L51 _public prototype_ `virtual bool RemoveEntry(const int32 EntryIndex);`
- L54 _protected member_ `TObjectPtr<UHierarchyTable> HierarchyTable;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HIERARCHYTABLEEDITOR_API`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/IHierarchyTable.h` (Public)


#### class `IHierarchyTable`  
`class IHierarchyTable : public SCompoundWidget`  
_L8-12_
- inherits: `SCompoundWidget`
- L11 _public prototype_ `virtual int32 GetSelectedEntryIndex() const = 0;`

### `Plugins/Experimental/Animation/HierarchyTable/Source/Editor/Public/IHierarchyTableColumn.h` (Public)


#### struct `IHierarchyTableColumn`  
`struct IHierarchyTableColumn`  
_L10-20_
- L13 _public prototype_ `virtual FName GetColumnId() const = 0;`
- L14 _public prototype_ `virtual FText GetColumnLabel() const = 0;`
- L15 _public prototype_ `virtual float GetColumnSize() const = 0;`
- L17 _public prototype_ `virtual TSharedRef<SWidget> CreateEntryWidget(TObjectPtr<UHierarchyTable> HierarchyTable, int32 EntryIndex) = 0;`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateHeaderWidget() = 0;`
