# Plugins / WidgetEditorToolPalette

- module root: `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette`
- headers: 8; symbols: 97
- symbol kinds: class=12, function=6, member=27, prototype=50, struct=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: ContentBrowser, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, Engine, GraphEditor, InputCore, InteractiveToolsFramework, LevelEditor, Projects, Slate, SlateCore, ToolMenus, UMG, UMGEditor, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/DefaultTools/CreateWidgetTool.h` (Public)


#### class `UCreateWidgetToolBuilder`  
`class UCreateWidgetToolBuilder : public UInteractiveToolBuilder`  
_L15-28_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for UCreateWidgetTool
- L19 _private prototype_ `UCreateWidgetToolBuilder();`
- L22 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override`
- L23 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L27 _public member_ `UClass* WidgetClass;` — Widget Class to be created by this tool

#### class `UCreateWidgetToolProperties`  
`class UCreateWidgetToolProperties : public UInteractiveToolPropertySet`  
_L35-40_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings UObject for UCreateWidgetTool. This UClass inherits from UInteractiveToolPropertySet, which provides an OnModified delegate that the Tool will listen to for changes in property values.
- L39 _public prototype_ `UCreateWidgetToolProperties();`

#### class `UCreateWidgetTool`  
`class UCreateWidgetTool : public USingleClickTool, public IWidgetBaseBehavior`  
_L48-79_
- reflection: `UCLASS()`
- inherits: `USingleClickTool,IWidgetBaseBehavior`
- desc: UCreateWidgetTool is a tool that allows for a specific widget to be created on click It allows for fast widget creation via hotkeys. The specific OnClick behavior can be customized by specifying a different create widget tool builder class in editor per project user settings.
- L53 _public prototype_ `UCreateWidgetTool();`
- L55 _public prototype_ `virtual void SetOwningToolkit(TSharedPtr<class IToolkit> InOwningToolkit);`
- L56 _public prototype_ `virtual void SetOwningWidget(TSharedPtr<class SWidget> InOwningWidget);`
- L59 _public prototype_ `virtual void Setup() override;`
- L63 _public prototype_ `virtual bool OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L68 _public member_ `UClass* WidgetClass;` — Widget Class to be created by this tool
- L72 _protected member_ `TObjectPtr<UCreateWidgetToolProperties> Properties;` — `UPROPERTY()`
- L77 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> OwningToolkit;` — @TODO: DarenC - Find a good parent class or interface for these (as base class)
- L78 _protected member_ `TWeakPtr<class SDesignerView> OwningWidget;`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/DefaultTools/RectangleSelectTool.h` (Public)


#### class `URectangleSelectToolBuilder`  
`class URectangleSelectToolBuilder : public UInteractiveToolBuilder`  
_L17-24_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Builder for URectangleSelectTool
- L22 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L23 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### class `URectangleSelectProperties`  
`class URectangleSelectProperties : public UInteractiveToolPropertySet`  
_L32-44_
- reflection: `UCLASS(Transient)`
- inherits: `UInteractiveToolPropertySet`
- desc: Property set for the URectangleSelectTool Note: Since we don't expose this for editing via details (yet), could instead be member variables on tool.
- L37 _public prototype_ `URectangleSelectProperties();`
- L40 _public member_ `bool bIsMarqueeActive;` — A pending marquee operation if it's active
- L43 _public member_ `FMarqueeOperation Marquee;` — A pending marquee operation if it's active

#### class `URectangleSelectTool`  
`class URectangleSelectTool : public UInteractiveTool, public IWidgetBaseBehavior`  
_L50-85_
- reflection: `UCLASS()`
- inherits: `UInteractiveTool,IWidgetBaseBehavior`
- desc: URectangleSelectTool is a simple marque widget select tool.
- L55 _public prototype_ `virtual void SetOwningToolkit(TSharedPtr<class IToolkit> InOwningToolkit);`
- L56 _public prototype_ `virtual void SetOwningWidget(TSharedPtr<class SWidget> InOwningWidget);`
- L59 _public prototype_ `virtual void Setup() override;`
- L63 _public prototype_ `virtual bool OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L64 _public prototype_ `virtual bool OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L65 _public prototype_ `virtual bool OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _public prototype_ `virtual bool OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L67 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L73 _protected member_ `TObjectPtr<URectangleSelectProperties> Properties;` — `UPROPERTY()` — Properties of the tool are stored here
- L76 _protected member_ `FVector2D PrevSelectionEndPoint;` — Cached last end point to optimize comparisons
- L81 _protected member_ `TWeakPtr<class FWidgetBlueprintEditor> OwningToolkit;` — @TODO: DarenC - Find a good parent class or interface for these (as base class)
- L82 _protected member_ `TWeakPtr<class SDesignerView> OwningWidget;`
- L84 _protected prototype_ `void SelectWidgetsAffectedByMarquee();`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/Settings/CreateWidgetToolSettings.h` (Public)


#### struct `FCreateWidgetToolInfo`  
`struct FCreateWidgetToolInfo`  
_L18-45_
- reflection: `USTRUCT()`
- desc: Info used to populate a single create widget tool
- L22 _public function_ `FCreateWidgetToolInfo() : WidgetClass(nullptr) , DisplayName("") , WidgetHotkey(FInputChord()) , CreateWidgetToolBuilder(UCreateWidgetToolBuilder::StaticClass())`
- L32 _public member_ `TSubclassOf<UWidget> WidgetClass;` — `UPROPERTY(EditAnywhere, config, Category = CreateWidgetInfo)` — The widget to create when this tool is activated
- L36 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, config, Category = CreateWidgetInfo)` — Display name for this tool, if empty will use the name of the widget
- L40 _public member_ `FInputChord WidgetHotkey;` — `UPROPERTY(EditAnywhere, config, Category = CreateWidgetInfo)` — The hotkey used to create this widget
- L44 _public member_ `TSubclassOf<UCreateWidgetToolBuilder> CreateWidgetToolBuilder;` — `UPROPERTY(EditAnywhere, config, AdvancedDisplay, Category = CreateWidgetInfo)` — Builder that handles creation of tool for this widget

#### struct `FCreateWidgetStackInfo`  
`struct FCreateWidgetStackInfo`  
_L49-60_
- reflection: `USTRUCT()`
- desc: Info used to populate a create widget tool stack
- L55 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, config, Category = CreateWidgetInfo)` — Display name for this tool stack
- L59 _public member_ `TArray<FCreateWidgetToolInfo> WidgetToolInfos;` — `UPROPERTY(EditAnywhere, config, Category = CreateWidgetInfo)` — Info for each widget that can be created by this stack

#### class `UCreateWidgetToolSettings`  
`class UCreateWidgetToolSettings : public UDeveloperSettings`  
_L66-82_
- reflection: `UCLASS(config=WidgetEditorToolPalette, autoexpandcategories=(Keybinds))`
- inherits: `UDeveloperSettings`
- desc: Allows for create widget tool layout to be defined via settings.
- L72 _public function_ `virtual FName GetContainerName() const`
- L73 _public function_ `virtual FName GetCategoryName() const`
- L74 _public function_ `virtual FName GetSectionName() const`
- L81 _public member_ `TArray<FCreateWidgetStackInfo> CreateWidgetStacks;` — `UPROPERTY(EditAnywhere, config, Category=Startup)` — List of tool stacks to create

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/WidgetEditorToolPaletteCommands.h` (Public)


#### class `FWidgetEditorToolPaletteCommands`  
`class FWidgetEditorToolPaletteCommands : public TCommands<FWidgetEditorToolPaletteCommands>`  
_L7-22_
- inherits: `TCommands<FWidgetEditorToolPaletteCommands>`
- L10 _public prototype_ `FWidgetEditorToolPaletteCommands();`
- L11 _public prototype_ `void RegisterCommands() override;`
- L12 _public prototype_ `static const FWidgetEditorToolPaletteCommands& Get();`
- L15 _public member_ `TSharedPtr<FUICommandInfo> ToggleWidgetEditorToolPalette;` — Command to toggle tool palette in widget editor
- L17 _public member_ `TSharedPtr<FUICommandInfo> DefaultSelectTool;`
- L18 _public member_ `TSharedPtr<FUICommandInfo> BeginRectangleSelectTool;`
- L20 _public member_ `TMap<FString, TSharedPtr<FUICommandInfo>> CreateWidgetToolStacks;`
- L21 _public member_ `TMap<FString, TSharedPtr<FUICommandInfo>> CreateWidgetTools;`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/WidgetEditorToolPaletteMode.h` (Public)


#### class `UWidgetEditorToolPaletteMode`  
`class UWidgetEditorToolPaletteMode : public UBaseLegacyWidgetEdMode`  
_L12-31_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseLegacyWidgetEdMode`
- L18 _public member_ `const static FEditorModeID Id;`
- L22 _protected prototype_ `UWidgetEditorToolPaletteMode();`
- L24 _protected prototype_ `void Enter() override;`
- L26 _protected prototype_ `bool UsesToolkits() const override;`
- L27 _protected prototype_ `void CreateToolkit() override;`
- L29 _protected function_ `virtual bool RequiresLegacyViewportInteractions() const override`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/WidgetEditorToolPaletteModule.h` (Public)


#### class `FWidgetEditorToolPaletteModule`  
`class FWidgetEditorToolPaletteModule : public IModuleInterface`  
_L11-24_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `bool IsWidgetEditorToolPaletteModeActive(TWeakPtr<FWidgetBlueprintEditor> InEditor) const;`
- L20 _public prototype_ `void OnToggleWidgetEditorToolPaletteMode(TWeakPtr<FWidgetBlueprintEditor> InEditor);`
- L22 _public prototype_ `void OnPostEngineInit();`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/WidgetEditorToolPaletteStyle.h` (Public)


#### class `FWidgetEditorToolPaletteStyle`  
`class FWidgetEditorToolPaletteStyle`  
_L9-28_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _public prototype_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);` — use to access icons defined by the style set by name, eg GetBrush("BrushFalloffIcons.Smooth")
- L24 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L27 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/WidgetEditorToolPalette/Source/WidgetEditorToolPalette/Public/WidgetEditorToolPaletteToolkit.h` (Public)


#### class `FWidgetEditorToolPaletteToolkit`  
`class FWidgetEditorToolPaletteToolkit : public FModeToolkit`  
_L9-41_
- inherits: `FModeToolkit`
- L13 _public prototype_ `void Init( const TSharedPtr<IToolkitHost>& InToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode ) override;`
- L16 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L17 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L21 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;`
- L22 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L23 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> CreatePaletteWidget(TSharedPtr<FUICommandList> InCommandList, FName InToolbarCustomizationName, FName InPaletteName);`
- L25 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L26 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L31 _private prototype_ `void UpdateActiveToolProperties(UInteractiveTool* Tool);`
- L34 _private prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L35 _private prototype_ `virtual FText GetActiveToolMessage() const override;`
- L38 _private member_ `FText ActiveToolName;`
- L39 _private member_ `FText ActiveToolMessage;`
