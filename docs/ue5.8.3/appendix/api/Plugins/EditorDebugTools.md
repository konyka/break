# Plugins / EditorDebugTools

- module root: `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools`
- headers: 6; symbols: 50
- symbol kinds: class=6, function=4, member=6, prototype=31, struct=1, typedef=2
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: AppFramework, CoreUObject, Engine, InputCore, Projects, Slate, SlateCore, SourceCodeAccess, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: SlateReflector
- PublicDependencyModuleNames: Core

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Private/GammaUIPanel.h` (Private)


#### class `SGammaUIPanel`  
`class SGammaUIPanel : public SCompoundWidget`  
_L7-19_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS( SGammaUIPanel )`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L17 _public prototype_ `float OnGetGamma() const;`
- L18 _public prototype_ `void OnGammaChanged( float NewValue );`

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Private/SDebugPanel.h` (Private)


#### class `SDebugPanel`  
`class SDebugPanel : public SCompoundWidget`  
_L7-22_
- inherits: `SCompoundWidget`
- L11 _public function_ `SLATE_BEGIN_ARGS(SDebugPanel)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L17 _private prototype_ `FReply OnReloadTexturesClicked();`
- L18 _private prototype_ `FReply OnDisplayTextureAtlases();`
- L19 _private prototype_ `FReply OnDisplayFontAtlases();`
- L20 _private prototype_ `FReply OnFlushFontCacheClicked();`
- L21 _private prototype_ `FReply OnTestSuiteClicked();`

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Private/SModuleUI.h` (Private)


#### class `SModuleUI`  
`class SModuleUI : public SCompoundWidget`  
_L13-107_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS( SModuleUI )`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `~SModuleUI();` — SModuleUI destructor
- L75 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForModuleListView(TSharedPtr< FModuleListItem > InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Given a data item, reutrns a widget to represent that item in the list view @param InItem      The list item to return a widget for @param OwnerTable  The TableView that this TableRow is being generated for @return	The widget to represent the specified list item
- L81 _private prototype_ `void OnModulesChanged( FName ModuleThatChanged, EModuleChangeReason ReasonForChange );` — Called by the engine's module manager when a module is loaded, unloaded, or the list of known modules has changed
- L86 _private prototype_ `void UpdateModuleListItems();` — Updates our module list items
- L91 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — module list item filter
- L97 _private typedef_ `typedef SListView< TSharedPtr< FModuleListItem > > SModuleListView;`
- L98 _private typedef_ `typedef TArray< TSharedPtr< FModuleListItem > > FModuleArray;`
- L101 _private member_ `TArray< TSharedPtr< FModuleListItem > > ModuleListItems;` — List items for the module list
- L104 _private member_ `TSharedPtr< SModuleListView > ModuleListView;` — List of all known modules
- L106 _private member_ `TSharedPtr< SSearchBox > ModuleNameSearchBox;`

#### struct `SModuleUI::FModuleListItem`  
`struct FModuleListItem`  
_L36-65_
- desc: An item in the module list
- L39 _public member_ `FName ModuleName;` — Name of this module
- L42 _public prototype_ `FReply OnLoadClicked();` — Called when 'Load' is clicked in the UI
- L45 _public prototype_ `FReply OnUnloadClicked();` — Called when 'Unload' is clicked in the UI
- L48 _public prototype_ `FReply OnReloadClicked();` — Called when 'Reload' is clicked in the UI
- L51 _public prototype_ `FReply OnRecompileClicked();` — Called when 'Recompile' is clicked in the UI
- L54 _public prototype_ `EVisibility GetVisibilityBasedOnLoadedAndShutdownableState() const;` — @return Returns Visible for modules that are currently loaded and shutdown-able, otherwise Collapsed
- L57 _public prototype_ `EVisibility GetVisibilityBasedOnReloadableState() const;` — @return Returns Visible for modules that are currently loaded and reload-able, otherwise Collapsed
- L60 _public prototype_ `EVisibility GetVisibilityBasedOnRecompilableState() const;` — @return Returns Visible for modules that are either not yet loaded or can be shutdown, otherwise Collapsed
- L63 _public prototype_ `EVisibility GetVisibilityBasedOnUnloadedState() const;` — @return Returns Collapsed for modules that are currently loaded, otherwise Visible

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Public/EditorDebugTools.h` (Public)


#### class `FEditorDebugToolsModule`  
`class FEditorDebugToolsModule : public IModuleInterface`  
_L10-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Public/EditorDebugToolsCommands.h` (Public)


#### class `FEditorDebugToolsCommands`  
`class FEditorDebugToolsCommands : public TCommands<FEditorDebugToolsCommands>`  
_L8-22_
- inherits: `TCommands<FEditorDebugToolsCommands>`
- L12 _public function_ `FEditorDebugToolsCommands() : TCommands<FEditorDebugToolsCommands>(TEXT("EditorDebugTools"), NSLOCTEXT("Contexts", "EditorDebugTools", "EditorDebugTools Plugin"), NAME_None, FEditorDebugToolsStyle::GetStyleSetName())`
- L18 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L21 _public member_ `TSharedPtr< FUICommandInfo > OpenPluginWindow;`

### `Plugins/Editor/EditorDebugTools/Source/EditorDebugTools/Public/EditorDebugToolsStyle.h` (Public)


#### class `FEditorDebugToolsStyle`  
`class FEditorDebugToolsStyle`  
_L10-31_
- L14 _public prototype_ `static void Initialize();`
- L16 _public prototype_ `static void Shutdown();`
- L20 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the Shooter game
- L22 _public prototype_ `static FName GetStyleSetName();`
- L26 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L30 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`
