# Plugins / ExampleCharacterFXEditor

- module root: `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor`
- headers: 9; symbols: 57
- symbol kinds: class=9, function=2, member=8, prototype=38
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: BaseCharacterFXEditor, ContentBrowser, Core, CoreUObject, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, ModelingComponents, ModelingComponentsEditorOnly, Projects, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditor.h` (Public)


#### class `UExampleCharacterFXEditor`  
`class UExampleCharacterFXEditor : public UBaseCharacterFXEditor`  
_L9-15_
- reflection: `UCLASS()`
- inherits: `UBaseCharacterFXEditor`
- L14 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorCommands.h` (Public)


#### class `FExampleCharacterFXEditorCommands`  
`class FExampleCharacterFXEditorCommands : public TBaseCharacterFXEditorCommands<FExampleCharacterFXEditorCommands>`  
_L7-23_
- inherits: `TBaseCharacterFXEditorCommands<FExampleCharacterFXEditorCommands>`
- L11 _public prototype_ `FExampleCharacterFXEditorCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;` — TInteractiveToolCommands<> interface
- L15 _public function_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override`
- L19 _public member_ `TSharedPtr<FUICommandInfo> OpenCharacterFXEditor;`
- L21 _public member_ `const static FString BeginAttributeEditorToolIdentifier;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> BeginAttributeEditorTool;`

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorMode.h` (Public)


#### class `UExampleCharacterFXEditorMode`  
`class UExampleCharacterFXEditorMode : public UBaseCharacterFXEditorMode`  
_L9-44_
- reflection: `UCLASS()`
- inherits: `UBaseCharacterFXEditorMode`
- L15 _public member_ `const static FEditorModeID EM_ExampleCharacterFXEditorModeId;`
- L17 _public prototype_ `UExampleCharacterFXEditorMode();`
- L22 _public prototype_ `static const FToolTargetTypeRequirements& GetToolTargetRequirements();` — Gets the tool target requirements for the mode.
- L24 _public prototype_ `virtual FBox SceneBoundingBox() const override;`
- L29 _protected prototype_ `virtual void CreateToolkit() override;` — UEdMode overrides
- L30 _protected prototype_ `virtual void BindCommands() override;`
- L31 _protected prototype_ `virtual void Exit() override;`
- L34 _protected prototype_ `virtual void AddToolTargetFactories() override;` — UBaseCharacterFXEditorMode overrides
- L35 _protected prototype_ `virtual void RegisterTools() override;`
- L36 _protected prototype_ `virtual void CreateToolTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L38 _protected prototype_ `virtual void InitializeTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L43 _protected member_ `TArray<TObjectPtr<UDynamicMeshComponent>> DynamicMeshComponents;` — `UPROPERTY()` — NOTE: Since the Example CharacterFX Editor is not the "default" editor for a particular asset type and we still want to have something to render, we instead store a set of temporary DynamicMeshComponents here. This should not be necessary if your editor is the default for an asset type

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorModeToolkit.h` (Public)


#### class `FExampleCharacterFXEditorModeToolkit`  
`class FExampleCharacterFXEditorModeToolkit : public FBaseCharacterFXEditorModeToolkit`  
_L12-27_
- inherits: `FBaseCharacterFXEditorModeToolkit`
- L18 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;` — For a specific tool palette category, construct and fill ToolbarBuilder with the category's tools
- L21 _public prototype_ `virtual const FSlateBrush* GetActiveToolIcon(const FString& Identifier) const;` — FBaseCharacterFXEditorModeToolkit
- L24 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit
- L25 _public prototype_ `virtual FText GetBaseToolkitName() const override;`

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorModule.h` (Public)


#### class `FExampleCharacterFXEditorModule`  
`class FExampleCharacterFXEditorModule : public FBaseCharacterFXEditorModule`  
_L15-27_
- inherits: `FBaseCharacterFXEditorModule`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _protected prototype_ `void RegisterMenus();` — NOTE: Only necessary because we want to allow opening specific asset types from the content browser

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorStyle.h` (Public)


#### class `FExampleCharacterFXEditorStyle`  
`class FExampleCharacterFXEditorStyle : public FSlateStyleSet`  
_L12-25_
- inherits: `FSlateStyleSet`
- L15 _public member_ `const static FName StyleName;`
- L18 _public prototype_ `static FExampleCharacterFXEditorStyle& Get();` — Access the singleton instance for this style set
- L21 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L23 _private prototype_ `FExampleCharacterFXEditorStyle();`
- L24 _private prototype_ `~FExampleCharacterFXEditorStyle();`

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorSubsystem.h` (Public)


#### class `UExampleCharacterFXEditorSubsystem`  
`class UExampleCharacterFXEditorSubsystem : public UEditorSubsystem`  
_L27-80_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L33 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L34 _public prototype_ `virtual void Deinitialize() override;`
- L37 _public prototype_ `virtual void BuildTargets(const TArray<TObjectPtr<UObject>>& ObjectsIn, const FToolTargetTypeRequirements& TargetRequirements, TArray<TObjectPtr<UToolTarget>>& TargetsOut);` — Tries to build the core targets that provide meshes for tools to work on.
- L42 _public prototype_ `virtual bool AreObjectsValidTargets(const TArray<UObject*>& InObjects) const;` — Checks that all of the objects are valid targets for an editor session.
- L50 _public prototype_ `virtual bool AreAssetsValidTargets(const TArray<FAssetData>& InAssets) const;` — Checks that all of the assets are valid targets for an editor session. This is preferable over AreObjectsValidTargets when we have FAssetData because it allows us to avoid forcing a load of the underlying UObjects (for instance to avoid triggering a load when right clicking an asset in the content browser).
- L57 _public prototype_ `virtual void StartExampleCharacterFXEditor(TArray<TObjectPtr<UObject>> ObjectsToEdit);` — Either brings to the front an existing editor instance that is editing one of these objects, if one exists, or starts up a new instance editing all of these objects.
- L63 _public prototype_ `virtual void NotifyThatExampleCharacterFXEditorClosed(TArray<TObjectPtr<UObject>> ObjectsItWasEditing);` — Needs to be called when an editor instance is closed so that the subsystem knows to create a new one for these objects if they are opened again.
- L72 _protected member_ `TObjectPtr<UToolTargetManager> ToolTargetManager = nullptr;` — `UPROPERTY()` — Used to let the subsystem figure out whether targets are valid. New factories should be added here in Initialize()/GetToolTargetRequirements() as they are developed.
- L75 _protected member_ `TMap<TObjectPtr<UObject>, TObjectPtr<UExampleCharacterFXEditor>> OpenedEditorInstances;` — Manage instances of the editor
- L78 _protected prototype_ `virtual void CreateToolTargetFactories(TArray<TObjectPtr<UToolTargetFactory>>& Factories) const;` — Create tool target factories based on what type of tool targets are supported

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorToolkit.h` (Public)


#### class `FExampleCharacterFXEditorToolkit`  
`class FExampleCharacterFXEditorToolkit : public FBaseCharacterFXEditorToolkit`  
_L7-22_
- inherits: `FBaseCharacterFXEditorToolkit`
- L11 _public prototype_ `FExampleCharacterFXEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L12 _public prototype_ `virtual ~FExampleCharacterFXEditorToolkit();`
- L14 _public prototype_ `virtual FText GetToolkitName() const override;`
- L15 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L16 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L21 _protected prototype_ `virtual FEditorModeID GetEditorModeId() const override;` — FBaseCharacterFXEditorToolkit overrides

### `Plugins/Experimental/CharacterFXEditor/ExampleCharacterFXEditor/Source/ExampleCharacterFXEditor/Public/ExampleCharacterFXEditorUISubsystem.h` (Public)


#### class `UExampleCharacterFXEditorUISubsystem`  
`class UExampleCharacterFXEditorUISubsystem : public UBaseCharacterFXEditorUISubsystem`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UBaseCharacterFXEditorUISubsystem`
- L15 _protected function_ `virtual FName GetModuleName() const override`
