# Plugins / ProxyTableEditor

- module root: `Plugins/Chooser/Source/ProxyTableEditor`
- headers: 9; symbols: 121
- symbol kinds: class=10, delegate=1, function=21, macro=1, member=22, namespace=8, prototype=57, struct=1
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, BlendStack, BlueprintGraph, Chooser, ChooserEditor, Core, CoreUObject, EditorStyle, EditorWidgets, Engine, GameplayTags, GameplayTagsEditor, GraphEditor, InputCore, PropertyEditor, ProxyTable, Slate, SlateCore, StructUtilsEditor, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Chooser/Source/ProxyTableEditor/Private/AssetDefinition_ProxyAsset.h` (Private)


#### class `UAssetDefinition_ProxyAsset`  
`class UAssetDefinition_ProxyAsset : public UAssetDefinitionDefault`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L27 _public prototype_ `const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L28 _public prototype_ `const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/Chooser/Source/ProxyTableEditor/Private/AssetDefinition_ProxyTable.h` (Private)


#### class `UAssetDefinition_ProxyTable`  
`class UAssetDefinition_ProxyTable : public UAssetDefinitionDefault`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L18 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L19 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L20 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L25 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L27 _public prototype_ `const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L28 _public prototype_ `const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyAssetFactory.h` (Private)


#### class `UProxyAssetFactory`  
`class UProxyAssetFactory : public UFactory`  
_L10-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UProxyAssetFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L23 _private function_ `virtual FName GetNewAssetThumbnailOverride() const override`

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyTableEditor.h` (Private)


#### class `UProxyRowDetails`  
`class UProxyRowDetails : public UObject`  
_L23-30_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Class used for chooser editor details customization
- L28 _public member_ `TObjectPtr<UProxyTable> ProxyTable;` — `UPROPERTY(EditAnywhere, Instanced, Category="Hidden")`
- L29 _public member_ `int Row;`

#### class `UE::ProxyTableEditor::FProxyTableEditor`  
`class FProxyTableEditor : public FAssetEditorToolkit, public FSelfRegisteringEditorUndoClient, public FNotifyHook`  
_L34-159_
- inherits: `FAssetEditorToolkit,FSelfRegisteringEditorUndoClient,FNotifyHook`
- L38 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<UObject*>, FGetDetailsViewObjects, const TArray<UObject*>&);` — Delegate that, given an array of assets, returns an array of objects to use in the details view of an FSimpleAssetEditor
- L40 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L41 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L52 _public prototype_ `void InitEditor( const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit, FGetDetailsViewObjects GetDetailsViewObjects );` — Edits the specified asset object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectsToEdit			The object to edit @param	GetDetailsViewObjects	If bound, a delegate to get the array of objects to use in the details view; uses ObjectsToEdit if not bound
- L55 _public prototype_ `virtual ~FProxyTableEditor();` — Destructor
- L58 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L59 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L60 _public prototype_ `virtual FText GetToolkitName() const override;`
- L61 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L62 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L63 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L64 _public function_ `virtual bool IsPrimaryEditor() const override`
- L65 _public function_ `virtual bool IsSimpleAssetEditor() const override`
- L68 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L69 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L72 _public prototype_ `virtual void NotifyPreChange( FProperty* PropertyAboutToChange ) override;` — Begin FNotifyHook Interface
- L73 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L75 _public function_ `UProxyTable* GetProxyTable()`
- L78 _public prototype_ `void SetPropertyVisibilityDelegate(FIsPropertyVisible InVisibilityDelegate);` — Used to show or hide certain properties
- L80 _public prototype_ `void SetPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled InPropertyEditingDelegate);` — Can be used to disable the details view making it read-only
- L95 _public prototype_ `void UpdateTableColumns();`
- L96 _public prototype_ `void UpdateTableRows();`
- L97 _public prototype_ `int MoveRow(int SourceRowIndex, int TargetIndex);`
- L98 _public prototype_ `void InsertEntry(FProxyEntry& Entry, int RowIndex);`
- L99 _public prototype_ `void DeleteSelectedRows();`
- L100 _public prototype_ `void ClearSelectedRows();`
- L101 _public function_ `void SelectRow(int RowIndex)`
- L102 _public prototype_ `void SelectRow(TSharedPtr<FProxyTableRow> Row);`
- L104 _private prototype_ `void AddInheritedRows(UProxyTable* ProxyTable);`
- L105 _private prototype_ `void SelectRootProperties();`
- L106 _private prototype_ `void RegisterToolbar();`
- L107 _private prototype_ `void BindCommands();`
- L110 _private prototype_ `TSharedRef<SDockTab> SpawnPropertiesTab( const FSpawnTabArgs& Args );` — Create the properties tab and its content
- L112 _private prototype_ `TSharedRef<SDockTab> SpawnTableTab( const FSpawnTabArgs& Args );` — Create the table tab and its content
- L114 _private prototype_ `TSharedRef<ITableRow> GenerateTableRow(TSharedPtr<FProxyTableRow> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L115 _private prototype_ `void TreeViewExpansionChanged(TSharedPtr<FProxyTableEditor::FProxyTableRow> InItem, bool bShouldBeExpanded);`
- L118 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when objects need to be swapped out for new versions, like after a blueprint recompile.
- L119 _private prototype_ `void OnObjectTransacted(UObject* InObject, const FTransactionObjectEvent& InTransactionObjectEvent);`
- L122 _private member_ `TSharedPtr< class IDetailsView > DetailsView;` — Details view
- L125 _private member_ `static const FName ProxyEditorAppIdentifier;` — App Identifier.
- L128 _private member_ `static const FName PropertiesTabId;` — The tab ids for all the tabs used
- L129 _private member_ `static const FName TableTabId;`
- L132 _private member_ `TArray<UObject*> EditingObjects;` — The objects open within this editor
- L134 _private member_ `TArray<TObjectPtr<UProxyRowDetails>> SelectedRows;`
- L136 _private member_ `TArray<TSharedPtr<FProxyTableRow>> MainTableRows;`
- L137 _private member_ `TArray<TSharedPtr<FProxyTableRow>> TableRows;`
- L139 _private member_ `TSharedPtr<SComboButton> CreateRowComboButton;`
- L141 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L142 _private member_ `TSharedPtr<STreeView<TSharedPtr<FProxyTableRow>>> TableView;`
- L145 _public member_ `TMap<UProxyTable*, bool> ImportedTablesExpansionState;`
- L146 _public member_ `TSet<FProxyEntry> ReferencedProxyEntries;`
- L147 _public member_ `TSet<UProxyTable*> ReferencedProxyTables;`
- L149 _public function_ `TSharedPtr<SComboButton>& GetCreateRowComboButton()`
- L152 _public member_ `static const FName ToolkitFName;` — The name given to all instances of this type of editor
- L154 _public prototype_ `static TSharedRef<FProxyTableEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit, FGetDetailsViewObjects GetDetailsViewObjects = FGetDetailsViewObjects() );`
- L156 _public prototype_ `static TSharedRef<FProxyTableEditor> CreateEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UObject*>& ObjectsToEdit, FGetDetailsViewObjects GetDetailsViewObjects = FGetDetailsViewObjects() );`
- L158 _public prototype_ `static void RegisterWidgets();`

#### struct `UE::ProxyTableEditor::FProxyTableEditor::FProxyTableRow`  
`struct FProxyTableRow`  
_L82-93_
- L84 _public function_ `FProxyTableRow(int32 InIndex, UProxyTable* InProxyTable) : ProxyTable(InProxyTable), RowIndex(InIndex)`
- L90 _public member_ `UProxyTable* ProxyTable;`
- L91 _public member_ `int32 RowIndex;`
- L92 _public member_ `TArray<TSharedPtr<FProxyTableRow>> Children;`

#### Free symbols / members of external scopes

- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace ProxyTableEditor` (scope `UE`)
- L38 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<UObject*>, FGetDetailsViewObjects, const TArray<UObject*>&);` — Delegate that, given an array of assets, returns an array of objects to use in the details view of an FSimpleAssetEditor

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyTableEditorCommands.h` (Private)


#### class `FProxyTableEditorCommands`  
`class FProxyTableEditorCommands : public TCommands<FProxyTableEditorCommands>`  
_L11-27_
- inherits: `TCommands<FProxyTableEditorCommands>`
- L15 _public function_ `FProxyTableEditorCommands() : TCommands<FProxyTableEditorCommands>("ProxyTableEditor", NSLOCTEXT("Contexts", "ProxyTableEditor", "Proxy Table Editor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L20 _public member_ `TSharedPtr<FUICommandInfo> EditTableSettings;`
- L23 _public function_ `virtual void RegisterCommands() override` — Initialize commands

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "ProxyTableEditorCommands"`

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyTableEditorModule.h` (Private)


#### class `UE::ProxyTableEditor::FModule`  
`class FModule : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- L14 _private prototype_ `virtual void StartupModule() override;`
- L15 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ProxyTableEditor` (scope `UE`)

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyTableEditorStyle.h` (Private)


#### class `UE::ProxyTableEditor::FProxyTableEditorStyle`  
`class FProxyTableEditorStyle : FSlateStyleSet`  
_L10-22_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `FProxyTableEditorStyle();`
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static const ISlateStyle& Get();`
- L21 _private member_ `static TSharedPtr< FProxyTableEditorStyle > StyleInstance;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ProxyTableEditor` (scope `UE`)

### `Plugins/Chooser/Source/ProxyTableEditor/Private/ProxyTableFactory.h` (Private)


#### class `UProxyTableFactory`  
`class UProxyTableFactory : public UFactory`  
_L10-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L14 _private prototype_ `UProxyTableFactory();`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L18 _private function_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override`
- L22 _private function_ `virtual FName GetNewAssetThumbnailOverride() const override`

### `Plugins/Chooser/Source/ProxyTableEditor/Private/StructOutputDataCustomization.h` (Private)


#### class `UE::ProxyTableEditor::FStructOutputDataCustomization`  
`class FStructOutputDataCustomization : public IPropertyTypeCustomization`  
_L10-18_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `FStructOutputDataCustomization()`
- L16 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L17 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ProxyTableEditor` (scope `UE`)
