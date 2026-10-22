# Plugins / BaseCharacterFXEditor

- module root: `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor`
- headers: 8; symbols: 100
- symbol kinds: class=9, delegate=1, function=9, macro=8, member=20, prototype=53
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, ContentBrowser, Core, CoreUObject, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, LevelEditor, ModelingComponents, Projects, Slate, SlateCore, StatusBar, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditor.h` (Public)


#### class `UBaseCharacterFXEditor`  
`class UBaseCharacterFXEditor : public UAssetEditor`  
_L25-50_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAssetEditor`
- L32 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& OutObjects) override;` — Retrieve stored objects to edit
- L35 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() PURE_VIRTUAL(UBaseCharacterFXEditor::CreateToolkit, return TSharedPtr<FBaseAssetToolkit>(););` — Inherited from UAssetEditor and called in UAssetEditor::Initialize. Override this to create a subclass of FBaseCharacterFXEditorToolkit
- L38 _public prototype_ `virtual void Initialize(const TArray<TObjectPtr<UObject>>& InObjects, const TSubclassOf<AActor>& InPreviewClass = {});` — Store objects to edit and call UAssetEditor::Initialize
- L41 _public prototype_ `virtual IAssetEditorInstance* GetInstanceInterface();` — Returns the asset editor instance interface, so that its window can be focused, for example.
- L49 _protected member_ `TArray<TObjectPtr<UObject>> OriginalObjectsToEdit;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorCommands.h` (Public)


#### class `TBaseCharacterFXEditorCommands`  
`template<typename CommandContextType> class TBaseCharacterFXEditorCommands : public TInteractiveToolCommands<CommandContextType>`  
_L12-40_
- inherits: `TInteractiveToolCommands<CommandContextType>`
- L19 _public function_ `virtual void RegisterCommands() override` — TInteractiveToolCommands<> interface If you override this function, call this base version to set up Accept/Cancel buttons
- L30 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L36 _protected function_ `TBaseCharacterFXEditorCommands(const FName InContextName, const FText& InContextDesc, const FName InContextParent, const FName InStyleSetName) : TInteractiveToolCommands<CommandContextType>(InContextName, InContextDesc, InContextParent, InStyleSetName)` — Call this from subclass default constructor

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "TBaseCharacterFXEditorCommands"`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorMode.h` (Public)


#### class `UBaseCharacterFXEditorMode`  
`class UBaseCharacterFXEditorMode : public UEdMode`  
_L21-65_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UEdMode`
- L28 _public prototype_ `virtual void Enter() override;` — UEdMode overrides
- L29 _public prototype_ `virtual void Exit() override;`
- L33 _public prototype_ `virtual void InitializeTargets(const TArray<TObjectPtr<UObject>>& AssetsIn);` — Called by the corresponding EditorToolkit. Creates ToolTargets from OriginalObjectsToEdit. Override to add custom per-target setup.
- L35 _public function_ `virtual FBox SceneBoundingBox() const`
- L43 _protected prototype_ `virtual void AddToolTargetFactories() PURE_VIRTUAL(UBaseCharacterFXEditorMode::AddToolTargetFactories, );` — Override these to specify supported ToolTargets and tools
- L44 _protected prototype_ `virtual void RegisterTools() PURE_VIRTUAL(UBaseCharacterFXEditorMode::RegisterTools, );`
- L48 _protected prototype_ `virtual void CreateToolTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) PURE_VIRTUAL(UBaseCharacterFXEditorMode::CreateToolTargets, );` — Called by InitializeTargets; override to populate tool targets for given assets
- L51 _protected prototype_ `void AcceptActiveToolActionOrTool();` — Handles nested tools and notifies InteractiveToolsContext
- L52 _protected prototype_ `void CancelActiveToolActionOrTool();`
- L58 _protected member_ `TArray<TObjectPtr<UObject>> OriginalObjectsToEdit;` — `UPROPERTY()` — Stores original input objects
- L64 _protected member_ `TArray<TObjectPtr<UToolTarget>> ToolTargets;` — `UPROPERTY()` — Tool targets created from OriginalObjectsToEdit (and 1:1 with that array) that provide us with dynamic meshes

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorModeToolkit.h` (Public)


#### class `FBaseCharacterFXEditorModeToolkit`  
`class FBaseCharacterFXEditorModeToolkit : public FModeToolkit`  
_L21-86_
- inherits: `FModeToolkit`
- L25 _public prototype_ `FBaseCharacterFXEditorModeToolkit();`
- L26 _public prototype_ `~FBaseCharacterFXEditorModeToolkit();`
- L29 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit
- L32 _public function_ `virtual FText GetActiveToolDisplayName() const override` — Active tool name to display in the ViewportOverlay
- L35 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;` — Returns the Mode specific tabs in the mode toolbar
- L38 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;` — Returns human readable name for the specific palette tool category
- L41 _public function_ `virtual bool HasIntegratedToolPalettes() const override` — Informs the built-in FModeToolkit palette building routines about how we want the toolbars to be set up
- L42 _public function_ `virtual bool HasExclusiveToolPalettes() const override`
- L45 _public function_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override` — Returns the mode's toolbox
- L48 _public prototype_ `virtual void PostNotification(const FText& Message);` — Set/clear notification message area
- L49 _public prototype_ `virtual void ClearNotification();`
- L52 _public prototype_ `virtual void PostWarning(const FText& Message);` — Set/clear warning message area
- L53 _public prototype_ `virtual void ClearWarning();`
- L58 _protected prototype_ `virtual const FSlateBrush* GetActiveToolIcon(const FString& Identifier) const PURE_VIRTUAL(FBaseCharacterFXEditorModeToolkit::GetActiveToolIcon, return nullptr;);` — Should be implemented in the concrete subclass since it will likely have to know where to look for UI resources
- L63 _protected member_ `const static FName ToolsTabName;` — The editor can have multiple tabs in the mode toolbar. ToolsTabName is the "Tools" tab maintained by this base class. PaletteNames_Standard is the set of all tab names in the concrete editor. Set these in the concrete subclass when adding additional toolbar tabs
- L64 _protected member_ `const static TArray<FName> PaletteNames_Standard;`
- L67 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;` — FModeToolkit
- L68 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L71 _protected member_ `TSharedPtr<STextBlock> ToolWarningArea;` — A place for tools to write out any warnings
- L74 _protected member_ `TSharedPtr<SBorder> ToolDetailsContainer;` — A container for the tool settings that is populated by the DetailsView managed in FModeToolkit
- L77 _protected member_ `TSharedPtr<SWidget> ViewportOverlayWidget;` — Contains the widget container for the Accept/Cancel buttons, etc. for tools
- L80 _protected member_ `FText ActiveToolName;` — Tool name, icon and message to display in viewport
- L81 _protected member_ `const FSlateBrush* ActiveToolIcon;`
- L82 _protected member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L84 _protected prototype_ `void UpdateActiveToolProperties();`
- L85 _protected prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorModeUILayer.h` (Public)


#### class `FBaseCharacterFXEditorModeUILayer`  
`class FBaseCharacterFXEditorModeUILayer : public FAssetEditorModeUILayer`  
_L12-26_
- inherits: `FAssetEditorModeUILayer`
- L15 _public prototype_ `FBaseCharacterFXEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L16 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L17 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L19 _public prototype_ `void SetModeMenuCategory(TSharedPtr<FWorkspaceItem> MenuCategoryIn);`
- L20 _public prototype_ `TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L24 _protected member_ `TSharedPtr<FWorkspaceItem> CharacterFXEditorMenuCategory;`

#### class `UBaseCharacterFXEditorUISubsystem`  
`class UBaseCharacterFXEditorUISubsystem : public UAssetEditorUISubsystem`  
_L33-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditorUISubsystem`
- L39 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Adds RegisterLayoutExtensions as a callback to the module corresponding to GetModuleName()
- L42 _public prototype_ `virtual void Deinitialize() override;` — Removes RegisterLayoutExtensions callback from the module corresponding to GetModuleName()
- L45 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;` — Docks the editor Mode tab in the Editor side panel area of the layout
- L48 _public member_ `static const FName EditorSidePanelAreaName;` — Identifier for the Layout extension in BaseCharacterFXEditorToolkit's StandaloneDefaultLayout
- L53 _protected function_ `virtual FName GetModuleName() const` — OVERRIDE THIS

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorModule.h` (Public)


#### class `FBaseCharacterFXEditorModule`  
`class FBaseCharacterFXEditorModule : public IModuleInterface`  
_L12-28_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `DECLARE_EVENT_OneParam(FExampleCharacterFXEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Used by the EditorUISubsystem
- L22 _public function_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L26 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`
- L21 _delegate_ `DECLARE_EVENT_OneParam(FExampleCharacterFXEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);` — Used by the EditorUISubsystem

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/BaseCharacterFXEditorToolkit.h` (Public)


#### class `FBaseCharacterFXEditorToolkit`  
`class FBaseCharacterFXEditorToolkit : public FBaseAssetToolkit`  
_L22-70_
- inherits: `FBaseAssetToolkit`
- L26 _public prototype_ `FBaseCharacterFXEditorToolkit(UAssetEditor* InOwningAssetEditor, const FName& ModuleName);`
- L28 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L29 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L30 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L31 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L33 _public prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L34 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override;`
- L35 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;`
- L40 _protected prototype_ `virtual FEditorModeID GetEditorModeId() const PURE_VIRTUAL(FBaseCharacterFXEditorToolkit::GetEditorModeId, return FEditorModeID("EM_ER` — Override this to get the Mode ID of the concrete CharacterFXEditorMode
- L45 _protected prototype_ `virtual void CreateEditorModeUILayer();` — Override this to create the concrete CharacterFXEditorModeUILayer
- L48 _protected prototype_ `virtual void InitializeEdMode(UBaseCharacterFXEditorMode* EdMode);` — Override this to provide the EdMode with any custom data it needs
- L50 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L53 _protected prototype_ `virtual void CreateEditorModeManager() override;` — Called from FBaseAssetToolkit::CreateWidgets.
- L57 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;` — Called from FBaseAssetToolkit::CreateWidgets to populate ViewportClient, but otherwise only used in our own viewport delegate
- L60 _protected member_ `TSharedPtr<FBaseCharacterFXEditorModeUILayer> ModeUILayer;` — Handles the hosting of additional toolkits, such as the mode toolkit
- L63 _protected member_ `TSharedPtr<FPreviewScene> ObjectScene;` — PreviewScene showing the objects being edited
- L66 _protected member_ `TSharedPtr<FWorkspaceItem> EditorMenuCategory;` — A default "CharacterFXEditor" category is created in RegisterTabSpawners. Override that function to set this to a concrete class type
- L69 _protected member_ `bool bForceViewportTab = true;` — Boolean to force the construction of the viewport tab even if the layout is not adding it

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`

### `Plugins/Experimental/CharacterFXEditor/BaseCharacterFXEditor/Source/BaseCharacterFXEditor/Public/SBaseCharacterFXEditorViewport.h` (Public)


#### class `SBaseCharacterFXEditorViewport`  
`class SBaseCharacterFXEditorViewport : public SAssetEditorViewport`  
_L10-18_
- inherits: `SAssetEditorViewport`
- L16 _public prototype_ `virtual void AddOverlayWidget(TSharedRef<SWidget> OverlaidWidget, int32 ZOrder = INDEX_NONE);` — These allow the toolkit to add an accept/cancel overlay when needed. PopulateViewportOverlays is not helpful here because that gets called just once.
- L17 _public prototype_ `virtual void RemoveOverlayWidget(TSharedRef<SWidget> OverlaidWidget);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BASECHARACTERFXEDITOR_API`
