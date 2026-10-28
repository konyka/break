# Editor / StringTableEditor

- module root: `Source/Editor/StringTableEditor`
- headers: 4; symbols: 77
- symbol kinds: class=4, function=8, macro=1, member=21, namespace=2, prototype=39, struct=1, typedef=1
- DynamicallyLoadedModuleNames: WorkspaceMenuStructure
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, Core, CoreUObject, DesktopPlatform, EditorFramework, Engine, InputCore, Slate, SlateCore, UnrealEd

### `Source/Editor/StringTableEditor/Private/AssetDefinition_StringTable.h` (Private)


#### class `UAssetDefinition_StringTable`  
`class UAssetDefinition_StringTable : public UAssetDefinitionDefault`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L21 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L26 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Source/Editor/StringTableEditor/Private/StringTableEditor.h` (Private)


#### class `FStringTableEditor`  
`class FStringTableEditor : public IStringTableEditor, public FEditorUndoClient`  
_L16-174_
- inherits: `IStringTableEditor,FEditorUndoClient`
- desc: Viewer/editor for a String Table
- L21 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L22 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L31 _public prototype_ `void InitStringTableEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UStringTable* StringTable);` — Edits the specified string table @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	StringTable				The string table to edit
- L34 _public prototype_ `FStringTableEditor() = default;` — Constructor
- L37 _public prototype_ `virtual ~FStringTableEditor();` — Destructor
- L40 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L42 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L43 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L46 _public prototype_ `virtual void RefreshStringTableEditor(const FString& NewSelection = FString()) override;`
- L49 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L50 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L51 _public prototype_ `void HandleUndoRedo();`
- L54 _public prototype_ `const UStringTable* GetStringTable() const;` — Get the string table being edited
- L57 _public prototype_ `void HandlePostChange(const FString& NewSelection = FString());` — Called after the string table has been changed
- L76 _private prototype_ `TSharedRef<SDockTab> SpawnTab_StringTable(const FSpawnTabArgs& Args);` — Spawns the tab with the string table inside
- L79 _private prototype_ `TSharedRef<ITableRow> OnGenerateStringTableEntryRow(TSharedPtr<FCachedStringTableEntry> CachedStringTableEntry, const TSharedRef<STableViewBase>& Table);` — Create the row for the given cached string table entry
- L82 _private prototype_ `void RefreshCachedStringTable(const FString& InCachedSelection = FString());` — Refresh the cached string table editor UI
- L85 _private prototype_ `FText GetNamespace() const;` — Get the current namespace used by this table
- L88 _private prototype_ `void OnNamespaceChanged(const FText& InText);` — Handle for the namespace being changed. Verify that the namespace is valid.
- L91 _private prototype_ `void OnNamespaceCommitted(const FText& InText, ETextCommit::Type);` — Handler for the namespace being committed.
- L94 _private prototype_ `void SetEntry(const FString& InKey, const FString& InSourceString, const FString& InDevNotes);` — Set the value of an entry in the string table
- L97 _private prototype_ `void DeleteEntry(const FString& InKey);` — Delete the given entry from the string table
- L100 _private prototype_ `bool IsValidIdentity(const FText& InIdentity, FText* OutReason = nullptr, const FText* InErrorCtx = nullptr) const;` — Check the given text to see whether it's valid to be used as identity (namespace or key)
- L103 _private prototype_ `void OnKeyChanged(const FText& InText);` — Handle for the key being changed. Verify that the key is valid and unique.
- L106 _private prototype_ `void OnSourceStringCommitted(const FText& InText, ETextCommit::Type);` — Handler for the source string being committed. Treat as if "Add" were pressed.
- L109 _private prototype_ `void OnFilterTextChanged(const FText& InNewText);` — Handler for the search box string being changed.
- L112 _private prototype_ `bool CanExecuteDelete() const;` — Check function for context menu delete action.
- L115 _private prototype_ `void ExecuteDelete();` — Handler for context menu delete action.
- L118 _private prototype_ `TSharedPtr<SWidget> OnConstructContextMenu();` — Handler for when opening the context menu in the list view.
- L121 _private prototype_ `FReply OnAddClicked();` — Handler for the "Add" button
- L124 _private prototype_ `FReply OnImportFromCSVClicked();` — Handler for the "Import from CSV" button
- L127 _private prototype_ `FReply OnExportToCSVClicked();` — Handler for the "Export to CSV" button
- L130 _private member_ `TSharedPtr<SEditableTextBox> NamespaceEditableTextBox;` — Editable text for the namespace
- L133 _private member_ `TSharedPtr<class SSearchBox> SearchBox;` — Search box for the text entries
- L136 _private typedef_ `using FEntryTextFilter = TTextFilter< TSharedPtr<FCachedStringTableEntry> >;` — Text filter for text entries
- L137 _private member_ `TSharedPtr<FEntryTextFilter> EntryTextFilter;`
- L140 _private member_ `TSharedPtr<SEditableTextBox> KeyEditableTextBox;` — Editable text for the key
- L143 _private member_ `TSharedPtr<SMultiLineEditableTextBox> SourceStringEditableTextBox;` — Editable text for the source string
- L146 _private member_ `TSharedPtr<SMultiLineEditableTextBox> DevNotesEditableTextBox;` — Editable text for the developer translation context notes
- L149 _private member_ `TArray<TSharedPtr<FCachedStringTableEntry>> CachedStringTableEntries;` — Array of cached string table entries
- L152 _private member_ `TSharedPtr<SListView<TSharedPtr<FCachedStringTableEntry>>> StringTableEntriesListView;` — List view showing the cached string table entries
- L155 _private member_ `TSharedPtr<class FUICommandList> CommandList;` — List of UI commands
- L158 _private member_ `static const FName StringTableTabId;` — The tab ID for the string table tab
- L161 _private member_ `static const FName StringTableDummyColumnId;` — The column ID for the dummy column
- L164 _private member_ `static const FName StringTableKeyColumnId;` — The column ID for the key column
- L167 _private member_ `static const FName StringTableSourceStringColumnId;` — The column ID for the source string column
- L170 _private member_ `static const FName StringTableDevNotesColumnId;` — The column ID for the developer translation context notes column
- L173 _private member_ `static const FName StringTableDeleteColumnId;` — The column ID for the delete column

#### struct `FStringTableEditor::FCachedStringTableEntry`  
`struct FCachedStringTableEntry`  
_L61-73_
- desc: Cached string table entry
- L63 _public function_ `FCachedStringTableEntry(FString InKey, FString InSourceString, FString InDevNotes) : Key(MoveTemp(InKey)) , SourceString(MoveTemp(InSourceString)) , DevNotes(MoveTemp(InDevNotes))`
- L70 _public member_ `FString Key;`
- L71 _public member_ `FString SourceString;`
- L72 _public member_ `FString DevNotes;`

### `Source/Editor/StringTableEditor/Public/IStringTableEditor.h` (Public)


#### class `IStringTableEditor`  
`class IStringTableEditor : public FAssetEditorToolkit`  
_L9-16_
- inherits: `FAssetEditorToolkit`
- desc: String Table Editor public interface
- L15 _public prototype_ `virtual void RefreshStringTableEditor(const FString& NewSelection = FString()) = 0;` — Notify the String Table editor that it needs to refresh due to an external String Table change.

### `Source/Editor/StringTableEditor/Public/StringTableEditorModule.h` (Public)


#### class `FStringTableEditorModule`  
`class FStringTableEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L21-53_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: String Table Editor module
- L26 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L38 _public prototype_ `TSharedRef<IStringTableEditor> CreateStringTableEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UStringTable* StringTable);` — Creates an instance of string table editor object. @param	Mode					Mode that this editor should operate in @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	StringTable				The string table to start editing @return	Interface to the new string table editor
- L41 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L43 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L46 _public member_ `static const FName StringTableEditorAppIdentifier;` — StringTable Editor app identifier string
- L49 _private prototype_ `void OnPackageMigration(UE::AssetTools::FPackageMigrationContext& MigrationContext);`
- L51 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L52 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API STRINGTABLEEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AssetTools` (scope `UE`)
