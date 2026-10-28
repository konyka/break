# Plugins / StaticMeshEditorModeling

- module root: `Plugins/Editor/StaticMeshEditorModeling/Source/StaticMeshEditorModeling`
- headers: 4; symbols: 45
- symbol kinds: class=4, function=1, member=11, prototype=29
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, InputCore, InteractiveToolsFramework, MeshLODToolset, MeshModelingToolsExp, ModelingComponentsEditorOnly, ModelingToolsEditorMode, Slate, SlateCore, StaticMeshEditor, ToolMenus, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Editor/StaticMeshEditorModeling/Source/StaticMeshEditorModeling/Private/StaticMeshEditorModelingCommands.h` (Private)


#### class `FStaticMeshEditorModelingCommands`  
`class FStaticMeshEditorModelingCommands : public TCommands<FStaticMeshEditorModelingCommands>`  
_L7-15_
- inherits: `TCommands<FStaticMeshEditorModelingCommands>`
- L10 _public prototype_ `FStaticMeshEditorModelingCommands();`
- L11 _public prototype_ `void RegisterCommands() override;`
- L12 _public prototype_ `static const FStaticMeshEditorModelingCommands& Get();`
- L14 _public member_ `TSharedPtr<FUICommandInfo> ToggleStaticMeshEditorModelingMode;`

### `Plugins/Editor/StaticMeshEditorModeling/Source/StaticMeshEditorModeling/Public/StaticMeshEditorModelingMode.h` (Public)


#### class `UStaticMeshEditorModelingMode`  
`class UStaticMeshEditorModelingMode : public UBaseLegacyWidgetEdMode`  
_L12-31_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode`
- L18 _public member_ `const static FEditorModeID Id;`
- L22 _protected prototype_ `UStaticMeshEditorModelingMode();`
- L24 _protected prototype_ `virtual void Enter() override;`
- L25 _protected prototype_ `virtual bool OnRequestClose() override;`
- L27 _protected prototype_ `virtual bool UsesToolkits() const override;`
- L28 _protected prototype_ `virtual void CreateToolkit() override;`
- L30 _protected function_ `virtual bool RequiresLegacyViewportInteractions() const override`

### `Plugins/Editor/StaticMeshEditorModeling/Source/StaticMeshEditorModeling/Public/StaticMeshEditorModelingModule.h` (Public)


#### class `FStaticMeshEditorModelingModule`  
`class FStaticMeshEditorModelingModule : public IModuleInterface`  
_L11-28_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `bool IsStaticMeshEditorModelingModeActive(TWeakPtr<IStaticMeshEditor> InEditor) const;`
- L20 _public prototype_ `void OnToggleStaticMeshEditorModelingMode(TWeakPtr<IStaticMeshEditor> InEditor);`
- L22 _public prototype_ `void RegisterMenusAndToolbars();`
- L26 _private member_ `TWeakPtr<SDockTab> MeshLODDockTab;`

### `Plugins/Editor/StaticMeshEditorModeling/Source/StaticMeshEditorModeling/Public/StaticMeshEditorModelingToolkit.h` (Public)


#### class `FStaticMeshEditorModelingToolkit`  
`class FStaticMeshEditorModelingToolkit : public FModeToolkit`  
_L9-49_
- inherits: `FModeToolkit`
- L13 _public prototype_ `void Init( const TSharedPtr<IToolkitHost>& InToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode ) override;`
- L15 _public prototype_ `FName GetToolkitFName() const override;`
- L16 _public prototype_ `FText GetBaseToolkitName() const override;`
- L17 _public prototype_ `TSharedPtr<SWidget> GetInlineContent() const override;`
- L19 _public prototype_ `void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;`
- L20 _public prototype_ `FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L21 _public prototype_ `void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;`
- L23 _public prototype_ `void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L24 _public prototype_ `void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L28 _private prototype_ `void PostNotification(const FText& Message);`
- L29 _private prototype_ `void ClearNotification();`
- L30 _private prototype_ `void PostWarning(const FText& Message);`
- L31 _private prototype_ `void ClearWarning();`
- L33 _private prototype_ `void UpdateActiveToolProperties(UInteractiveTool* Tool);`
- L35 _private prototype_ `FText GetActiveToolDisplayName() const override;`
- L36 _private prototype_ `FText GetActiveToolMessage() const override;`
- L38 _private member_ `TSharedPtr<SBorder> ToolDetailsContainer;`
- L40 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`
- L41 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L42 _private member_ `FText ActiveToolName;`
- L43 _private member_ `FText ActiveToolMessage;`
- L45 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L46 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L47 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`
