# Plugins / UVEditor

- module root: `Plugins/Editor/UVEditor/Source/UVEditor`
- headers: 21; symbols: 468
- symbol kinds: class=28, delegate=2, enum=4, enumerator=12, function=19, macro=14, member=159, namespace=7, prototype=222, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AdvancedPreviewScene, ContentBrowser, CoreUObject, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorSubsystem, Engine, GeometryAlgorithms, GeometryCore, LevelEditor, ModelingComponents, ModelingComponentsEditorOnly, ModelingEditorUI, Slate, SlateCore, StatusBar, TextureUtilitiesCommon, ToolMenus, ToolWidgets, UVEditorTools, UVEditorToolsEditorOnly, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, GeometryProcessingInterfaces, InputCore, InteractiveToolsFramework, MeshModelingToolsExp, UnrealEd

### `Plugins/Editor/UVEditor/Source/UVEditor/Private/Actions/UnsetUVsAction.h` (Private)


#### class `UUnsetUVsAction`  
`class UUnsetUVsAction : public UUVToolAction`  
_L13-20_
- reflection: `UCLASS()`
- inherits: `UUVToolAction`
- L18 _public prototype_ `virtual bool CanExecuteAction() const override;`
- L19 _public prototype_ `virtual bool ExecuteAction() override;`

### `Plugins/Editor/UVEditor/Source/UVEditor/Private/UVEditor3DViewportMode.h` (Private)


#### class `UUVEditor3DViewportMode`  
`class UUVEditor3DViewportMode : public UEdMode`  
_L21-29_
- reflection: `UCLASS(Transient)`
- inherits: `UEdMode`
- desc: The UV editor live preview has its own world, mode manager, and input router. It doesn't really need a mode, and we can't hook it up to the UV editor mode because we don't want input to be routed directly to it from this other world (it is instead accessed through a context API in tools). However, we do want hotkey events to be routed to our tools from the live preview. This is done by registering our command objects to a command list that the live preview routes input to, and to have that command list be at the expected place in the input routing, we need a mode that has a toolkit object (See FEditorModeTools::InputKey. The hotkey handling passes through the ProcessCommandBindings on the mode toolkit there). The default mode (UEdModeDefault) does not have a toolkit object, hence this dummy mode.
- L26 _public member_ `const static FEditorModeID EM_ModeID;`
- L28 _public prototype_ `UUVEditor3DViewportMode();`

### `Plugins/Editor/UVEditor/Source/UVEditor/Private/UVEditorUXPropertySets.h` (Private)


#### class `UUVEditorUnwrappedUXProperties`  
`class UUVEditorUnwrappedUXProperties : public UInteractiveToolPropertySet`  
_L13-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the UUVEditorMode's Unwrapped Visualization
- L18 _public member_ `TArray<FColor> BoundaryLineColors;` — `UPROPERTY(EditAnywhere, Category="Unwrapped Visualization", meta = (DisplayName = "Boundary Line Color"))`
- L21 _public member_ `float BoundaryLineThickness;` — `UPROPERTY(EditAnywhere, Category="Unwrapped Visualization", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", DisplayName = "Boundary Line Thickness"))`
- L25 _public member_ `float WireframeThickness;` — `UPROPERTY(EditAnywhere, Category="Unwrapped Visualization", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", DisplayName = "Wireframe Thickness"))` — TODO: maybe opacity is the setting to change instead of/in addition to thickness? Could also have something to recognize line density and/or window size and adjust accordingly

#### class `UUVEditorLivePreviewUXProperties`  
`class UUVEditorLivePreviewUXProperties : public UInteractiveToolPropertySet`  
_L32-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the UUVEditorMode's properties in the Live Preview (3d) Viewport
- L37 _public member_ `FColor SelectionColor;` — `UPROPERTY(EditAnywhere, Category="Live Preview Visualization", meta = (DisplayName = "Selection Line Color"))`
- L40 _public member_ `float SelectionLineThickness;` — `UPROPERTY(EditAnywhere, Category="Live Preview Visualization", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", DisplayName = "Selection Line Thickness"))`
- L43 _public member_ `float SelectionPointSize;` — `UPROPERTY(EditAnywhere, Category="Live Preview Visualization", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", DisplayName = "Selection Point Size"))`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/SUVEditor2DViewport.h` (Public)


#### class `SUVEditor2DViewport`  
`class SUVEditor2DViewport : public SAssetEditorViewport`  
_L13-21_
- inherits: `SAssetEditorViewport`
- L18 _public prototype_ `virtual void BindCommands() override;` — SEditorViewport
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L20 _public prototype_ `bool IsWidgetModeActive(UE::Widget::EWidgetMode Mode) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/SUVEditor3DViewport.h` (Public)


#### class `SUVEditor3DViewport`  
`class SUVEditor3DViewport : public SAssetEditorViewport`  
_L14-22_
- inherits: `SAssetEditorViewport`
- desc: Viewport used for live preview in UV editor. Has a custom toolbar overlay at the top.
- L19 _public prototype_ `virtual void BindCommands() override;` — SAssetEditorViewport
- L20 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditor.h` (Public)


#### class `UUVEditor`  
`class UUVEditor : public UAssetEditor`  
_L37-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditor`
- desc: The actual asset editor class doesn't have that much in it, intentionally. Our current asset editor guidelines ask us to place as little business logic as possible into the class, instead putting as much of the non-UI code into the subsystem as possible, and the UI code into the toolkit (which this class owns). However, since we're using a mode and the Interactive Tools Framework, a lot of our business logic ends up inside the mode and the tools, not the subsystem. The front-facing code is mostly in the asset editor toolkit, though the mode toolkit has most of the things that deal with the toolbar on the left.
- L42 _public prototype_ `void Initialize(const TArray<TObjectPtr<UObject>>& InObjects);`
- L43 _public prototype_ `void Initialize(const TArray<TObjectPtr<UObject>>& InObjects, const TArray<FTransform3d>& InTransforms);`
- L45 _public prototype_ `void GetWorldspaceRelativeTransforms(TArray<FTransform3d>& OutTransforms);`
- L48 _public prototype_ `IAssetEditorInstance* GetInstanceInterface();` — Returns the asset editor instance interface, so that its window can be focused, for example.
- L51 _public prototype_ `void GetObjectsToEdit(TArray<UObject*>& OutObjects) override;` — UAssetEditor overrides
- L52 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L60 _protected member_ `TArray<TObjectPtr<UObject>> OriginalObjectsToEdit;` — `UPROPERTY()`
- L63 _protected member_ `TArray<FTransform3d> ObjectWorldspaceOffsets;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditor2DViewportClient.h` (Public)


#### class `FUVEditor2DViewportClient`  
`class FUVEditor2DViewportClient : public FEditorViewportClient, public IInputBehaviorSource`  
_L21-88_
- inherits: `FEditorViewportClient,IInputBehaviorSource`
- desc: Client used to display a 2D view of the UV's, implemented by using a perspective viewport with a locked camera.
- L24 _public prototype_ `FUVEditor2DViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget, UUVToolViewportButtonsAPI* ViewportButtonsAPI, UUVTool2DViewportAPI* UVTool2DViewportAPI);`
- L27 _public prototype_ `virtual ~FUVEditor2DViewportClient() = default;`
- L29 _public prototype_ `bool AreSelectionButtonsEnabled() const;`
- L30 _public prototype_ `void SetSelectionMode(UUVToolViewportButtonsAPI::ESelectionMode NewMode);`
- L31 _public prototype_ `UUVToolViewportButtonsAPI::ESelectionMode GetSelectionMode() const;`
- L32 _public prototype_ `bool AreWidgetButtonsEnabled() const;`
- L34 _public prototype_ `void SetSnappingActive(bool bActive);`
- L35 _public prototype_ `bool IsSnappingActive();`
- L36 _public prototype_ `void SetLocationGridSnapEnabled(bool bEnabled);`
- L37 _public prototype_ `bool GetLocationGridSnapEnabled();`
- L38 _public prototype_ `void SetLocationGridSnapValue(float SnapValue);`
- L39 _public prototype_ `float GetLocationGridSnapValue();`
- L40 _public prototype_ `void SetRotationGridSnapEnabled(bool bEnabled);`
- L41 _public prototype_ `bool GetRotationGridSnapEnabled();`
- L42 _public prototype_ `void SetRotationGridSnapValue(float SnapValue);`
- L43 _public prototype_ `float GetRotationGridSnapValue();`
- L44 _public prototype_ `void SetScaleGridSnapEnabled(bool bEnabled);`
- L45 _public prototype_ `bool GetScaleGridSnapEnabled();`
- L46 _public prototype_ `void SetScaleGridSnapValue(float SnapValue);`
- L47 _public prototype_ `float GetScaleGridSnapValue();`
- L50 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;` — FEditorViewportClient
- L52 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L53 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L54 _public prototype_ `bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;`
- L55 _public prototype_ `void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;`
- L56 _public prototype_ `UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L57 _public prototype_ `void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L64 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override;` — IInputBehaviorSource
- L67 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L70 _protected prototype_ `void DrawGrid(const FSceneView* View, FPrimitiveDrawInterface* PDI);`
- L71 _protected prototype_ `void DrawGridRulers(FViewport& InViewport, FSceneView& View, UCanvas& Canvas);`
- L72 _protected prototype_ `void DrawUDIMLabels(FViewport& InViewport, FSceneView& View, UCanvas& Canvas);`
- L75 _protected member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — These get added in AddReferencedObjects for memory management
- L76 _protected member_ `TObjectPtr<UUVToolViewportButtonsAPI> ViewportButtonsAPI;`
- L77 _protected member_ `TObjectPtr<UUVTool2DViewportAPI> UVTool2DViewportAPI;`
- L79 _protected member_ `bool bDrawGridRulers = true;`
- L80 _protected member_ `bool bDrawGrid = true;`
- L81 _protected member_ `TObjectPtr<UCanvas> CanvasObject;`
- L86 _protected member_ `TUniquePtr<FEditor2DScrollBehaviorTarget> ScrollBehaviorTarget;` — Note that it's generally less hassle if the unique ptr types are complete here, not forward declared, else we get compile errors if their destruction shows up anywhere in the header.
- L87 _protected member_ `TUniquePtr<FEditor2DMouseWheelZoomBehaviorTarget> ZoomBehaviorTarget;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditor2DViewportContext.h` (Public)


#### class `UUVEditor2DViewportContext`  
`class UUVEditor2DViewportContext : public UUnrealEdViewportToolbarContext`  
_L12-37_
- reflection: `UCLASS()`
- inherits: `UUnrealEdViewportToolbarContext`
- L18 _public prototype_ `UUVEditor2DViewportContext();`
- L20 _public prototype_ `virtual FText GetGridSnapLabel() const override;`
- L21 _public prototype_ `virtual TArray<float> GetGridSnapSizes() const override;`
- L22 _public prototype_ `virtual bool IsGridSnapSizeActive(int32 GridSizeIndex) const override;`
- L23 _public prototype_ `virtual void SetGridSnapSize(int32 GridSizeIndex) override;`
- L25 _public prototype_ `virtual FText GetRotationSnapLabel() const override;`
- L26 _public prototype_ `virtual bool IsRotationSnapActive(int32 RotationIndex, ERotationGridMode RotationMode) const override;`
- L27 _public prototype_ `virtual void SetRotationSnapSize(int32 RotationIndex, ERotationGridMode RotationMode) override;`
- L29 _public prototype_ `virtual FText GetScaleSnapLabel() const override;`
- L30 _public prototype_ `virtual bool IsScaleSnapActive(int32 ScaleIndex) const override;`
- L31 _public prototype_ `virtual void SetScaleSnapSize(int32 ScaleIndex) override;`
- L34 _protected prototype_ `TSharedPtr<FUVEditor2DViewportClient> GetViewportClient() const;`
- L36 _protected member_ `TArray<float> GridSnapSizes;`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditor3DViewportClient.h` (Public)


#### enum `EUVEditor3DViewportClientCameraMode`  
`enum EUVEditor3DViewportClientCameraMode`  
_L14-17_
- desc: Types of camera motion for the UV Editor 3D viewport
- L15 _public enumerator_ `Orbit`
- L16 _public enumerator_ `Fly`

#### class `FUVEditor3DViewportClient`  
`class FUVEditor3DViewportClient : public FEditorViewportClient`  
_L23-50_
- inherits: `FEditorViewportClient`
- desc: Viewport client for the 3d live preview in the UV editor. Currently same as editor viewport client but doesn't allow editor gizmos/widgets, and alters orbit camera control.
- L27 _public prototype_ `FUVEditor3DViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene = nullptr, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr, UUVToolViewportButtonsAPI* ViewportButtonsAPI = nullptr);`
- L30 _public prototype_ `virtual ~FUVEditor3DViewportClient() = default;`
- L33 _public prototype_ `virtual bool ShouldOrbitCamera() const override;` — FEditorViewportClient
- L34 _public function_ `bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override`
- L35 _public function_ `void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override`
- L36 _public function_ `UE::Widget::EWidgetMode GetWidgetMode() const override`
- L37 _public prototype_ `void FocusCameraOnSelection();`
- L40 _public function_ `void SetCameraMode(EUVEditor3DViewportClientCameraMode CameraModeIn)`
- L41 _public function_ `EUVEditor3DViewportClientCameraMode GetCameraMode() const`
- L47 _protected member_ `EUVEditor3DViewportClientCameraMode CameraMode = EUVEditor3DViewportClientCameraMode::Orbit;` — Enforce Orbit camera for UV editor live preview viewport. Use this instead of the base class orbit camera flag to allow for expected behaviors of the base class when in fly camera mode.
- L48 _protected member_ `UUVToolViewportButtonsAPI* ViewportButtonsAPI;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorBackgroundPreview.h` (Public)


#### enum `EUVEditorBackgroundSourceType`  
`enum class EUVEditorBackgroundSourceType`  
_L19-24_
- reflection: `UENUM()`
- desc: Enum to control the background visualiztion mode
- L21 _public enumerator_ `Checkerboard`
- L22 _public enumerator_ `Texture`
- L23 _public enumerator_ `Material`

#### class `UUVEditorBackgroundPreviewProperties`  
`class UUVEditorBackgroundPreviewProperties : public UInteractiveToolPropertySet`  
_L30-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the UUVEditorBackgroundPreview
- L36 _public member_ `bool bVisible = false;` — `UPROPERTY(EditAnywhere, Category = Background, meta = (DisplayName = "Display Background"))` — Should the background be shown (Alt+B)
- L40 _public member_ `EUVEditorBackgroundSourceType SourceType = EUVEditorBackgroundSourceType::Checkerboard;` — `UPROPERTY(EditAnywhere, Category = Background, meta = (EditCondition = "bVisible", DisplayName = "Background Source"))` — Source of background visuals
- L44 _public member_ `TObjectPtr<UTexture2D> SourceTexture;` — `UPROPERTY(EditAnywhere, Category = Background, meta = (EditCondition = "SourceType==EUVEditorBackgroundSourceType::Texture && bVisible", EditConditionHides = true))` — Display a background based on the selected texture
- L48 _public member_ `TObjectPtr<UMaterial> SourceMaterial;` — `UPROPERTY(EditAnywhere, Category = Background, meta = (EditCondition = "SourceType==EUVEditorBackgroundSourceType::Material && bVisible", EditConditionHides = true))` — Display a background based on the selected material
- L51 _public member_ `TArray<int32> UDIMBlocks;` — `UPROPERTY()`
- L54 _public member_ `bool bUDIMsEnabled = false;` — `UPROPERTY()`

#### class `UUVEditorBackgroundPreview`  
`class UUVEditorBackgroundPreview : public UPreviewGeometry`  
_L62-96_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPreviewGeometry`
- desc: Serves as a container for the background texture/material display in the UVEditor. This class is responsible for managing the quad drawn behind the grid, as well as maintaining the texture and material choices from the user to display.
- L71 _public prototype_ `void OnTick(float DeltaTime);` — Client must call this every frame for changes to .Settings to be reflected in rendered result.
- L76 _public member_ `TObjectPtr<UUVEditorBackgroundPreviewProperties> Settings;` — `UPROPERTY()` — Visualization settings
- L80 _public member_ `TObjectPtr<UTriangleSetComponent> BackgroundComponent;` — `UPROPERTY()` — The component containing the quad visualization
- L84 _public member_ `TObjectPtr<UMaterialInstanceDynamic> BackgroundMaterial;` — `UPROPERTY()` — The active material being displayed for the background
- L86 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBackgroundMaterialChange, TObjectPtr<UMaterialInstanceDynamic> MaterialInstance);`
- L87 _public member_ `FOnBackgroundMaterialChange OnBackgroundMaterialChange;`
- L90 _protected prototype_ `virtual void OnCreated() override;`
- L92 _protected member_ `bool bSettingsModified = false;`
- L94 _protected prototype_ `void UpdateVisibility();`
- L95 _protected prototype_ `void UpdateBackground();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITOR_API`
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBackgroundMaterialChange, TObjectPtr<UMaterialInstanceDynamic> MaterialInstance);`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorCommands.h` (Public)


#### class `FUVEditorCommands`  
`class FUVEditorCommands : public TCommands<FUVEditorCommands>`  
_L9-54_
- inherits: `TCommands<FUVEditorCommands>`
- L13 _public prototype_ `FUVEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L19 _public member_ `TSharedPtr<FUICommandInfo> OpenUVEditor;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ApplyChanges;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> BeginLayoutTool;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> BeginTransformTool;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> BeginAlignTool;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> BeginDistributeTool;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> BeginTexelDensityTool;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> BeginParameterizeMeshTool;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> BeginChannelEditTool;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> BeginSeamTool;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> BeginRecomputeUVsTool;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> BeginBrushSelectTool;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> BeginUVSnapshotTool;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SewAction;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SplitAction;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> MakeIslandAction;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> UnsetUVsAction;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> AcceptOrCompleteActiveTool;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> CancelOrCompleteActiveTool;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> VertexSelection;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> EdgeSelection;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> TriangleSelection;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> IslandSelection;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> FullMeshSelection;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> SelectAll;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> EnableOrbitCamera;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> EnableFlyCamera;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> SetFocusCamera;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> ToggleBackground;`

#### class `UE::Geometry::FUVEditorToolActionCommands`  
`class FUVEditorToolActionCommands : public TInteractiveToolCommands<FUVEditorToolActionCommands>`  
_L59-74_
- inherits: `TInteractiveToolCommands<FUVEditorToolActionCommands>`
- L62 _public prototype_ `FUVEditorToolActionCommands();`
- L64 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;`
- L65 _public prototype_ `static void RegisterAllToolActions();`
- L66 _public prototype_ `static void UnregisterAllToolActions();`
- L73 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added

#### Free symbols / members of external scopes

- L56 _namespace_ `namespace UE`
- L56 _namespace_ `namespace Geometry` (scope `UE`)
- L78 _macro_ `#define DECLARE_TOOL_ACTION_COMMANDS(CommandsClassName) \`
- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace Geometry` (scope `UE`)
- L88 _prototype_ `DECLARE_TOOL_ACTION_COMMANDS(FUVEditorBrushSelectToolCommands);` (scope `UE::Geometry`)

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorDistortionVisualization.h` (Public)


#### enum `EDistortionMetric`  
`enum class EDistortionMetric : uint8`  
_L17-27_
- reflection: `UENUM()`
- L20 _public enumerator_ `ReedBeta UMETA(DisplayName = "Elliptical Eccentricity")` — Represents the shape deviation from the worldspace triangle element, sans scaling.
- L22 _public enumerator_ `Sander_L2 UMETA(DisplayName = "L2 Norm")` — Represents the root-mean-square strech over all directions vs the worldspace triangle element
- L24 _public enumerator_ `Sander_LInf UMETA(DisplayName = "L Infinity Norm")` — Represents the worst-case, or greatest stretch in any particular direction, vs the worldspace triangle element
- L26 _public enumerator_ `TexelDensity UMETA(DisplayName = "Texel Density")` — Shows the current texile density ratio, compared against the average baseline of the entire mesh.

#### class `UUVEditorDistortionVisualizationProperties`  
`class UUVEditorDistortionVisualizationProperties : public UInteractiveToolPropertySet`  
_L33-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the UUVEditorDistortionVisualization
- L39 _public member_ `bool bVisible = false;` — `UPROPERTY(EditAnywhere, Category = "Distortion Visualization", meta = (DisplayName = "Display UV Distortion Visualization"))` — Should the visualization be shown.
- L43 _public member_ `EDistortionMetric Metric = EDistortionMetric::ReedBeta;` — `UPROPERTY(EditAnywhere, Category = "Distortion Visualization", meta = (DisplayName = "Metric"))` — The specific metric used to classify and visualize distortion.
- L50 _public member_ `bool bCompareToAverageDensity = true;` — `UPROPERTY()`
- L54 _public member_ `bool bRespectUDIMTextureResolutions = false;` — `UPROPERTY(EditAnywhere, Category = "Distortion Visualization|Texel Density", meta = (DisplayName = "Use UDIM Resolutions", EditCondition = "Metric == EDistortionMetric::TexelDensity"))` — When computing average texel density, take into account specific UDIM tile resolutions for a more accurate representation
- L60 _public member_ `int32 MapSize;` — `UPROPERTY()`
- L66 _public member_ `float TargetTexelDensity;` — `UPROPERTY()`
- L69 _public member_ `TMap<int32, int32> PerUDIMTextureResolution;` — `UPROPERTY()`

#### class `UUVEditorDistortionVisualization`  
`class UUVEditorDistortionVisualization : public UObject`  
_L77-119_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: This class contains the logic for handling distortion visualization within the UV Editor. It manages the setting of triangle color and computing the potential metrics used to describe the amount of distortion present in the UVs.
- L86 _public prototype_ `void Initialize();` — Client must call this after construction and parameter configuration to complete setup.
- L91 _public prototype_ `void Shutdown();` — Client must call this before destruction to clean up state.
- L96 _public prototype_ `void OnTick(float DeltaTime);` — Client must call this every frame for changes to .Settings to be reflected in rendered result.
- L103 _public member_ `TObjectPtr<UUVEditorDistortionVisualizationProperties> Settings;` — `UPROPERTY()`
- L106 _public member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L109 _protected member_ `bool bSettingsModified = false;`
- L111 _protected member_ `TArray<double> PerTargetAverageTexelDensity;`
- L112 _protected member_ `int32 MaximumTileTextureResolution;`
- L114 _protected prototype_ `void UpdateVisibility();`
- L115 _protected prototype_ `void ConfigureMeshColorsForTarget(int32 TargetIndex);`
- L116 _protected prototype_ `FColor GetDistortionColorForTriangle(const UE::Geometry::FDynamicMesh3& Mesh, int UVChannel, int Tid, double TargetAverageTexelDensity);`
- L117 _protected prototype_ `void ComputeInitialMeshSurfaceAreas();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITOR_API`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorInitializationContext.h` (Public)


#### class `UUVEditorInitializationContext`  
`class UUVEditorInitializationContext : public UUVToolContextObject`  
_L23-29_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: An editor-only context used specifically to pass data from the asset editor to the mode when that data is not meant to be used by the tools. This allows a mode to be prepped before its first Enter() call even when it doesn't exist yet. Data/api's that are meant to be used by the tools would usually be placed into other, non-editor-only context objects (UUVToolLivePreviewAPI, etc).
- L27 _public member_ `TWeakObjectPtr<UEditorInteractiveToolsContext> LivePreviewITC;`
- L28 _public member_ `TWeakPtr<FUICommandList> LivePreviewToolkitCommands;`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorMode.h` (Public)


#### class `UUVEditorGridProperties`  
`class UUVEditorGridProperties : public UInteractiveToolPropertySet`  
_L47-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the UUVEditorMode's Grid
- L53 _public member_ `bool bDrawGrid = true;` — `UPROPERTY(EditAnywhere, Category = "Grid & Guides", meta = (DisplayName = "Display Grid"))` — Should the grid be shown?
- L57 _public member_ `bool bDrawRulers = true;` — `UPROPERTY(EditAnywhere, Category = "Grid & Guides", meta = (DisplayName = "Display Rulers"))` — Should the grid rulers be shown?

#### struct `FUDIMSpecifier`  
`struct FUDIMSpecifier`  
_L61-88_
- reflection: `USTRUCT()`
- L66 _public member_ `int32 UDIM = 1001;` — `UPROPERTY(EditAnywhere, Transient, Category = UDIM, meta = (ClampMin = "1001", UIMin = "1001"))`
- L69 _public member_ `int32 UCoord = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = UDIM, meta = (DisplayName = "Block U Offset"))`
- L72 _public member_ `int32 VCoord = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = UDIM, meta = (DisplayName = "Block V Offset"))`
- L75 _public member_ `int32 TextureResolution = 512;` — `UPROPERTY(EditAnywhere, Transient, Category = UDIM, meta = (DisplayName = "Block Texture Resolution"))`

#### enum `EUVEditorModeActions`  
`enum class EUVEditorModeActions`  
_L91-97_
- reflection: `UENUM()`
- L93 _public enumerator_ `NoAction`
- L95 _public enumerator_ `ConfigureUDIMsFromAsset`
- L96 _public enumerator_ `ConfigureUDIMsFromTexture`

#### class `UUVEditorUDIMProperties`  
`class UUVEditorUDIMProperties : public UInteractiveToolPropertySet`  
_L103-144_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for UDIMs in the UVEditor
- L107 _public function_ `void Initialize(UUVEditorMode* ParentModeIn)`
- L108 _public prototype_ `void PostAction(EUVEditorModeActions Action);`
- L111 _public member_ `FString UDIMSourceAsset;` — `UPROPERTY(EditAnywhere, Transient, Category = "UDIM", meta = (DisplayName = "UDIM Source Mesh", GetOptions = GetAssetNames))`
- L114 _public prototype_ `const TArray<FString>& GetAssetNames();` — `UFUNCTION()`
- L117 _public prototype_ `int32 AssetByIndex() const;` — `UFUNCTION()`
- L121 _public function_ `void SetUDIMsFromAsset()` — `UFUNCTION(CallInEditor, Category = UDIM)` — Set UDIM Layout from selected asset's UVs
- L125 _public member_ `TObjectPtr<UTexture2D> UDIMSourceTexture;` — `UPROPERTY(EditAnywhere, Transient, Category = UDIM)` — Texture asset to source UDIM information from
- L129 _public function_ `void SetUDIMsFromTexture()` — `UFUNCTION(CallInEditor, Category = UDIM)` — Set UDIM Layout from selected texture asset
- L133 _public member_ `TArray<FUDIMSpecifier> ActiveUDIMs;` — `UPROPERTY(EditAnywhere, Transient, Category = UDIM, meta = (TitleProperty = "UDIM"))` — Currently active UDIM set
- L136 _public prototype_ `void InitializeAssets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn);`
- L139 _private prototype_ `void UpdateActiveUDIMsFromTexture();`
- L140 _private prototype_ `void UpdateActiveUDIMsFromAsset();`
- L142 _private member_ `TWeakObjectPtr<UUVEditorMode> ParentMode;`
- L143 _private member_ `TArray<FString> UVAssetNames;`

#### class `UUVEditorMode`  
`class UUVEditorMode : public UEdMode`  
_L157-419_
- reflection: `UCLASS(Transient)`
- inherits: `UEdMode`
- desc: The UV editor mode is the mode used in the UV asset editor. It holds most of the inter-tool state. We put things in a mode instead of directly into the asset editor in case we want to someday use the mode in multiple asset editors.
- L163 _public member_ `const static FEditorModeID EM_UVEditorModeId;`
- L165 _public prototype_ `UUVEditorMode();`
- L171 _public prototype_ `static const FToolTargetTypeRequirements& GetToolTargetRequirements();` — Gets the tool target requirements for the mode. The resulting targets undergo further processing to turn them into the input objects that tools get (since these need preview meshes, etc).
- L176 _public prototype_ `static double GetUVMeshScalingFactor();` — Gets the factor by which UV layer unwraps get scaled (scaling makes certain things easier, like zooming in, etc).
- L181 _public prototype_ `static void InitializeAssetEditorContexts(UContextObjectStore& ContextStore, const TArray<TObjectPtr<UObject>>& AssetsIn, const TArray<FTransform>& TransformsIn, FEditorViewportClient& LivePreviewViewportClient, FAssetEditorModeManager& LivePreviewModeManager, UUVToolViewportButtonsAPI& ViewportButtonsAPI, UUVTool2DViewportAPI& UVTool2DViewportAPI);` — Called by an asset editor so that a created instance of the mode has all the data it needs on Enter() to initialize itself.
- L187 _public prototype_ `void ChangeInputObjectLayer(int32 AssetID, int32 NewLayerIndex);` — Public for use by undo/redo. Otherwise should use RequestUVChannelChange
- L193 _public prototype_ `void RequestUVChannelChange(int32 AssetID, int32 Channel);` — Request a change of the displayed UV channel/layer. It will happen on the next tick, and create an undo/redo event.
- L195 _public function_ `bool IsActive()`
- L206 _public prototype_ `void EmitToolIndependentObjectChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description);` — Unlike UInteractiveToolManager::EmitObjectChange, emitting an object change using this function does not cause it to expire when the active tool doesn't match the emitting tool. It is important that the emitted change deals properly with expiration itself, for instance expiring itself when a tool input is invalid or a contained preview is disconnected. TODO: Should this sort of option exist in UInteractiveToolManager?
- L209 _public prototype_ `bool HaveUnappliedChanges() const;` — Asset management
- L210 _public prototype_ `bool CanApplyChanges() const;`
- L211 _public prototype_ `void GetAssetsWithUnappliedChanges(TArray<TObjectPtr<UObject>> UnappliedAssetsOut);`
- L212 _public prototype_ `void ApplyChanges();`
- L215 _public function_ `const TArray<FString>& GetAssetNames() const` — @return List of asset names, indexed by AssetID
- L218 _public prototype_ `int32 GetNumUVChannels(int32 AssetID) const;` — @return Number of UV channels in the given asset, or IndexConstants::InvalidID if AssetID was invalid.
- L221 _public prototype_ `int32 GetDisplayedChannel(int32 AssetID) const;` — @return The index of the channel currently displayed for the given AssetID.
- L224 _public prototype_ `UObject* GetBackgroundSettingsObject();` — @return A settings object suitable for display in a details panel to control the background visualization.
- L227 _public prototype_ `UObject* GetGridSettingsObject();` — @return A settings object suitable for display in a details panel to control the grid.
- L230 _public prototype_ `UObject* GetUnwrappedUXSettingsObject() const;` — @return A settings object suitable for display in a details panel to control the unwrapped viewport visualization.
- L233 _public prototype_ `UObject* GetLivePreviewUXSettingsObject() const;` — @return A settings object suitable for display in a details panel to control the visualization in the live preview (3d) viewport.
- L236 _public prototype_ `UObject* GetUDIMSettingsObject();` — @return A settings object suitable for display in a details panel to control UDIM configuration.
- L239 _public prototype_ `UObject* GetToolDisplaySettingsObject();` — @return A settings object suitable for display in a details panel to control the active tool's visualization settings.
- L242 _public prototype_ `UObject* GetDistortionVisualsSettingsObject();` — @return A settings object suitable for display in a details panel to control the UV distortion visualization settings.
- L244 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) ;`
- L245 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L248 _public prototype_ `virtual void Enter() override;` — UEdMode overrides
- L249 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L250 _public prototype_ `virtual void Exit() override;`
- L251 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L256 _public prototype_ `virtual void ActivateDefaultTool() override;` — We're changing visibility of this one to public here so that we can call it from the toolkit when clicking accept/cancel buttons. We don't want to friend the toolkit because we don't want it to later get (accidentally) more entangled with mode internals. At the same time, we're not sure whether we want to make the UEdMode one public. So this is the minimal-impact tweak.
- L259 _public prototype_ `virtual bool IsDefaultToolActive();` — This is currently not part of the base class at all... Should it be?
- L265 _public member_ `TObjectPtr<UUVEditorBackgroundPreview> BackgroundVisualization;` — `UPROPERTY()`
- L268 _public member_ `TObjectPtr<UUVEditorDistortionVisualization> DistortionVisualization;` — `UPROPERTY()`
- L272 _public member_ `TObjectPtr<UUVEditorGridProperties> UVEditorGridProperties = nullptr;` — `UPROPERTY()` — Hold a settings object to configure the grid
- L276 _public member_ `TObjectPtr<UUVEditorUDIMProperties> UVEditorUDIMProperties = nullptr;` — `UPROPERTY()` — Hold a settings object to configure the UDIMs
- L278 _public prototype_ `void PopulateUDIMsByAsset(int32 AssetId, TArray<FUDIMSpecifier>& UDIMsOut) const;`
- L280 _public prototype_ `void FocusLivePreviewCameraOnSelection();`
- L284 _protected member_ `TArray<TObjectPtr<UUVToolAction>> RegisteredActions;` — `UPROPERTY()`
- L286 _protected prototype_ `void InitializeModeContexts();`
- L287 _protected prototype_ `void InitializeTargets();`
- L288 _protected prototype_ `void RegisterTools();`
- L289 _protected prototype_ `void RegisterActions();`
- L290 _protected prototype_ `void SetSimulationWarning(bool bEnabled);`
- L293 _protected prototype_ `virtual void CreateToolkit() override;` — UEdMode overrides
- L295 _protected prototype_ `virtual void BindCommands() override;` — Not sure whether we need these yet
- L296 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L297 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L300 _protected prototype_ `void UpdateTriangleMaterialBasedOnBackground(bool IsBackgroundVisible);` — `UE_DEPRECATED(5.3, "UpdateTriangleMaterialBasedOnBackground is deprecated, replaced by the more generic UpdateTriangleMaterialBasedOnDisplaySettings.")`
- L301 _protected prototype_ `void UpdatePreviewMaterialBasedOnBackground();`
- L302 _protected prototype_ `void UpdateTriangleMaterialBasedOnDisplaySettings();`
- L304 _protected prototype_ `void UpdateActiveUDIMs();`
- L305 _protected member_ `int32 UDIMsChangedWatcherId;`
- L312 _protected member_ `TArray<TObjectPtr<UObject>> OriginalObjectsToEdit;` — `UPROPERTY()` — Stores original input objects, for instance UStaticMesh pointers. AssetIDs on tool input objects are indices into this array (and ones that are 1:1 with it)
- L319 _protected member_ `TArray<TObjectPtr<UToolTarget>> ToolTargets;` — `UPROPERTY()` — Tool targets created from OriginalObjectsToEdit (and 1:1 with that array) that provide us with dynamic meshes whose UV layers we unwrap.
- L325 _protected member_ `TArray<FTransform> Transforms;` — Transforms that should be used for the 3d previews, 1:1 with OriginalObjectsToEdit and ToolTargets.
- L331 _protected member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMesh3>> AppliedCanonicalMeshes;` — 1:1 with the asset arrays. Hold dynamic mesh representations of the targets. These are authoritative versions of the combined UV layers that get baked back on apply.
- L340 _protected member_ `TArray<TObjectPtr<UMeshOpPreviewWithBackgroundCompute>> AppliedPreviews;` — 1:1 with AppliedCanonicalMeshes, the actual displayed 3d meshes that can be used by tools for background computations. However if doing so, keep in mind that while we currently do not display more than one layer at a time for each asset, if we someday do, tools would have to take care to disallow cases where the two layers of the same asset might try to use the same preview for a background compute.
- L349 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> ToolInputObjects;` — `UPROPERTY()` — Input objects we give to the tools, one per displayed UV layer. This includes pointers to the applied meshes, but also contains the unwrapped mesh and preview. These should not be assumed to be the same length as the asset arrays in case we someday do not display exactly a single layer per asset.
- L355 _protected member_ `TArray<TWeakObjectPtr<UMeshElementsVisualizer>> WireframesToTick;` — Wireframes have to get ticked to be able to respond to setting changes. This is 1:1 with ToolInputObjects.
- L359 _protected member_ `TSet<int32> ModifiedAssetIDs;` — Authoritative list of targets that have changes that have not been baked back yet.
- L362 _protected member_ `TArray<FString> AssetNames;` — 1:1 with ToolTargets, indexed by AssetID
- L365 _protected prototype_ `void SetDisplayedUVChannels(const TArray<int32>& LayerPerAsset, bool bEmitUndoTransaction);` — Used with the ToolAssetAndLayerAPI to process tool layer change requests
- L367 _protected member_ `TArray<int32> PendingUVLayerIndex;`
- L371 _protected member_ `TObjectPtr<UWorld> LivePreviewWorld = nullptr;` — `UPROPERTY()` — Here largely for convenience to avoid having to pass it around functions.
- L374 _protected member_ `TWeakObjectPtr<UEditorInteractiveToolsContext> LivePreviewITC;` — Used to forward Render/DrawHUD calls in the live preview to the api object.
- L380 _private member_ `TWeakPtr<FUICommandList> LivePreviewToolkitCommands;` — Used to make mode hotkeys be triggered properly from the live preview
- L384 _protected member_ `TObjectPtr<UUVToolSelectionAPI> SelectionAPI = nullptr;` — `UPROPERTY()`
- L390 _protected member_ `TArray<TObjectPtr<UInteractiveToolPropertySet>> PropertyObjectsToTick;` — `UPROPERTY()` — Mode-level property objects (visible or not) that get ticked.
- L392 _protected member_ `TArray<TWeakObjectPtr<UUVToolContextObject>> ContextsToUpdateOnToolEnd;`
- L393 _protected member_ `TArray<TWeakObjectPtr<UUVToolContextObject>> ContextsToShutdown;`
- L395 _protected member_ `bool bIsActive = false;`
- L396 _protected member_ `FString DefaultToolIdentifier;`
- L398 _protected member_ `static FDateTime AnalyticsLastStartTimestamp;`
- L401 _protected member_ `bool bPIEModeActive;` — Holds references to PIE callbacks to handle logic when the PIE session starts & shuts down
- L402 _protected member_ `FDelegateHandle BeginPIEDelegateHandle;`
- L403 _protected member_ `FDelegateHandle EndPIEDelegateHandle;`
- L404 _protected member_ `FDelegateHandle CancelPIEDelegateHandle;`
- L408 _protected member_ `FDelegateHandle PostSaveWorldDelegateHandle;` — Holds references to Save callbacks to handle logic when the autosave triggers and shuts down active tools. We need to recover from this, so we restart the select tool after the save is over.
- L412 _private member_ `TObjectPtr<UUVEditorUnwrappedUXProperties> UVEditorUnwrappedUXProperties = nullptr;` — `UPROPERTY()` — Hold a settings object to configure the unwrapped visualization
- L416 _private member_ `TObjectPtr<UUVEditorLivePreviewUXProperties> UVEditorLivePreviewUXProperties = nullptr;` — `UPROPERTY()` — Hold a settings object to configure the visualization in the live preview (3d) viewport
- L418 _private member_ `TArray<FString> ToolsThatAllowActions;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UVEDITOR_API`
- L17 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L77 _function_ `friend bool operator==(const FUDIMSpecifier& A, const FUDIMSpecifier& B )`
- L82 _function_ `friend uint32 GetTypeHash(const FUDIMSpecifier& UDIMSpecifier)`
- L146 _namespace_ `namespace UVEditorModeChange`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorModeChannelProperties.h` (Public)


#### class `UUVEditorUVChannelProperties`  
`class UUVEditorUVChannelProperties : public UInteractiveToolPropertySet`  
_L24-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: UV Layer Settings for the UVEditorMode
- L30 _public member_ `FString Asset;` — `UPROPERTY(EditAnywhere, Category = UVChannel, meta = (DisplayName = "Asset", GetOptions = GetAssetNames))`
- L33 _public prototype_ `const TArray<FString>& GetAssetNames();` — `UFUNCTION()`
- L36 _public member_ `FString UVChannel;` — `UPROPERTY(EditAnywhere, Category = UVChannel, meta = (DisplayName = "UV Channel", GetOptions = GetUVChannelNames))`
- L39 _public prototype_ `const TArray<FString>& GetUVChannelNames();` — `UFUNCTION()`
- L41 _public member_ `TArray<FString> UVChannelNames;`
- L42 _public member_ `TArray<FString> UVAssetNames;`
- L45 _public member_ `TArray<int32> NumUVLayersPerAsset;` — 1:1 with UVAssetNames
- L49 _public prototype_ `void Initialize( TArray<TObjectPtr<UToolTarget>>& TargetObjects, TArray<TSharedPtr<UE::Geometry::FDynamicMesh3>> AppliedCanonicalMeshes, bool bInitializeSelection);`
- L59 _public prototype_ `bool ValidateUVAssetSelection(bool bUpdateIfInvalid);` — Verify that the UV asset selection is valid @param bUpdateIfInvalid if selection is not valid, reset UVAsset to Asset0 or empty if no assets exist @return true if selection in UVAsset is an entry in UVAssetNames.
- L66 _public prototype_ `bool ValidateUVChannelSelection(bool bUpdateIfInvalid);` — Verify that the UV channel selection is valid @param bUpdateIfInvalid if selection is not valid, UVChannel to UV0 or empty if no UV channels exist @return true if selection in UVChannel is an entry in UVChannelNamesList.
- L72 _public prototype_ `int32 GetSelectedAssetID();` — @return selected UV asset ID, or -1 if invalid selection
- L78 _public prototype_ `int32 GetSelectedChannelIndex(bool bForceToZeroOnFailure = false);` — @param bForceToZeroOnFailure if true, then instead of returning -1 we return 0 so calling code can fallback to default UV paths @return selected UV channel index, or -1 if invalid selection, or 0 if invalid selection and bool bForceToZeroOnFailure = true

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITOR_API`
- L14 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorModeToolkit.h` (Public)


#### class `FUVEditorModeToolkit`  
`class FUVEditorModeToolkit : public FModeToolkit`  
_L21-133_
- inherits: `FModeToolkit`
- desc: The UV editor mode toolkit is responsible for the panel on the side in the UV editor that shows mode and tool properties. Tool buttons would go in Init().
- L24 _public prototype_ `FUVEditorModeToolkit();`
- L25 _public prototype_ `~FUVEditorModeToolkit();`
- L27 _public prototype_ `virtual void InitializeAfterModeSetup();`
- L30 _public prototype_ `virtual TSharedRef<SWidget> CreateChannelMenu();` — Creates a menu where the displayed UV Channel can be changed for each asset
- L33 _public prototype_ `virtual TSharedRef<SWidget> CreateBackgroundSettingsWidget();` — Creates a widget where the background visualization can be changed.
- L36 _public prototype_ `virtual TSharedRef<SWidget> CreateGridSettingsWidget();` — Creates a widget where the grid display can be changed.
- L39 _public prototype_ `virtual TSharedRef<SWidget> CreateUnwrappedUXSettingsWidget();` — Creates a widget where the visualization in the 2d/unwrapped view can be changed.
- L42 _public prototype_ `virtual TSharedRef<SWidget> CreateLivePreviewUXSettingsWidget();` — Creates a widget where the visualization properties in the 3d viewport can be changed.
- L45 _public prototype_ `virtual TSharedRef<SWidget> CreateUDIMSettingsWidget();` — Creates a widget where the visible UDIMs can be changed.
- L48 _public prototype_ `virtual TSharedRef<SWidget> GetToolDisplaySettingsWidget();` — Creates a widget where the active tool's display settings can be changed.
- L51 _public prototype_ `virtual void MakeGizmoNumericalUISubMenu(FMenuBuilder& MenuBuilder);` — Creates submenu for manipulating the gizmo numerical UI
- L54 _public prototype_ `virtual TSharedRef<SWidget> CreateDistortionVisualsSettingsWidget();` — Creates a widget where the distortion visualization settings can be changed.
- L57 _public prototype_ `virtual void EnableShowPIEWarning(bool bEnable);` — Enables or diables the Play in Editor mode warning for the editor
- L60 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — FModeToolkit
- L61 _public function_ `virtual FText GetActiveToolDisplayName() const override`
- L63 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;` — Returns the Mode specific tabs in the mode toolbar
- L65 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;` — Returns human readable name for the specific palette tool category
- L67 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder) override;` — For a specific tool palette category, construct and fill ToolbarBuilder with the category's tools
- L69 _public function_ `virtual bool HasIntegratedToolPalettes() const override` — Informs the built in FModeToolkit palette building routines about how we want the toolbars to be setup
- L70 _public function_ `virtual bool HasExclusiveToolPalettes() const override`
- L73 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit
- L74 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L75 _public function_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override`
- L78 _public prototype_ `virtual void PostNotification(const FText& Message);` — set/clear notification message area
- L79 _public prototype_ `virtual void ClearNotification();`
- L82 _public prototype_ `virtual void PostWarning(const FText& Message);` — set/clear warning message area
- L83 _public prototype_ `virtual void ClearWarning();`
- L86 _public prototype_ `virtual void PostModeWarning(const FText& Message);` — set/clear mode-level warning message area. These messages don't get cleared on tool shutdown.
- L87 _public prototype_ `virtual void ClearModeWarning();`
- L90 _protected member_ `const static TArray<FName> PaletteNames_Standard;`
- L92 _protected prototype_ `TSharedRef<SWidget> CreateDisplaySettingsWidget(UObject* SettingsObject) const;`
- L93 _protected prototype_ `void UpdatePIEWarnings();`
- L96 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;` — FModeToolkit
- L97 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L101 _protected member_ `TSharedPtr<SWidget> ToolkitWidget;` — The mode's entire toolbox, which gets returned by GetInlineContent()
- L104 _protected member_ `TSharedPtr<SBorder> ToolButtonsContainer;` — The portion of the toolbox composed of buttons that activate tools
- L107 _protected member_ `TSharedPtr<STextBlock> ToolWarningArea;` — A place for tools to write out any warnings
- L110 _protected member_ `TSharedPtr<STextBlock> ModeWarningArea;` — A place for the mode to write out any warnings
- L114 _protected member_ `TSharedPtr<SBorder> ToolDetailsContainer;` — A container for the tool settings that is populated by the DetailsView managed in FModeToolkit
- L117 _protected member_ `TSharedPtr<SBorder> EditorDetailsContainer;` — A container for the editor settings
- L120 _protected member_ `TSharedPtr<SWidget> ViewportOverlayWidget;` — Contains the widget container for the Accept/Cancel buttons for tools.
- L122 _protected member_ `TSharedPtr<STransformGizmoNumericalUIOverlay> GizmoNumericalUIOverlayWidget;`
- L124 _protected member_ `FText ActiveToolName;`
- L125 _protected member_ `const FSlateBrush* ActiveToolIcon;`
- L126 _protected member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L127 _protected member_ `bool bShowPIEWarning;`
- L129 _protected prototype_ `void UpdateActiveToolProperties();`
- L130 _protected prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);`
- L132 _protected member_ `bool bFirstInitializeAfterModeSetup = true;`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorModeUILayer.h` (Public)


#### class `UUVEditorUISubsystem`  
`class UUVEditorUISubsystem : public UAssetEditorUISubsystem`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- desc: Interchange layer to manage built in tab locations within the editor's layout.
- L14 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L15 _public prototype_ `virtual void Deinitialize() override;`
- L16 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

#### class `FUVEditorModeUILayer`  
`class FUVEditorModeUILayer : public FAssetEditorModeUILayer`  
_L20-33_
- inherits: `FAssetEditorModeUILayer`
- desc: Handles the hosting of additional toolkits, such as the mode toolkit, within the UVEditor's toolkit.
- L23 _public prototype_ `FUVEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L24 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L25 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L27 _public prototype_ `void SetModeMenuCategory(TSharedPtr<FWorkspaceItem> MenuCategoryIn);`
- L28 _public prototype_ `TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`
- L31 _protected member_ `TSharedPtr<FWorkspaceItem> UVEditorMenuCategory;`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorModularFeature.h` (Public)


#### class `UE::Geometry::FUVEditorModularFeature`  
`class FUVEditorModularFeature : public IUVEditorModularFeature`  
_L19-28_
- inherits: `IUVEditorModularFeature`
- desc: Connector class that allows other plugins to look for the UV Editor to see if the plugin is present, (via IModularFeatures::Get().GetModularFeature and related methods), and then launch it if so.
- L22 _public prototype_ `virtual void LaunchUVEditor(const TArray<TObjectPtr<UObject>>& Objects) override;`
- L23 _public prototype_ `virtual bool CanLaunchUVEditor(const TArray<TObjectPtr<UObject>>& Objects) override;`
- L26 _protected prototype_ `void ConvertInputArgsToValidTargets(const TArray<TObjectPtr<UObject>>& ObjectsIn, TArray<TObjectPtr<UObject>>& ObjectsOut) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UVEDITOR_API`
- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorModule.h` (Public)


#### class `FUVEditorModule`  
`class FUVEditorModule : public IModuleInterface`  
_L18-39_
- inherits: `IModuleInterface`
- desc: Besides the normal module things, the module class is also responsible for hooking the UV editor into existing menus.
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public prototype_ `DECLARE_EVENT_OneParam(FUVEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L27 _public function_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L30 _protected prototype_ `void RegisterMenus();`
- L33 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;`
- L36 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L38 _private member_ `TSharedPtr<UE::Geometry::FUVEditorModularFeature> UVEditorAssetEditor;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UVEDITOR_API`
- L26 _delegate_ `DECLARE_EVENT_OneParam(FUVEditorModule, FOnRegisterLayoutExtensions, FLayoutExtender&);`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorSubsystem.h` (Public)


#### class `UUVEditorSubsystem`  
`class UUVEditorSubsystem : public UEditorSubsystem`  
_L31-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: The subsystem is meant to hold any UV editor operations that are not UI related (those are handled by the toolkit); however, in our case, most of our operations are wrapped up inside tools and the UV mode. Instead, the subsystem deals with some global UV asset editor things- it manages existing instances (we can't rely on the asset editor subsystem for this because the UV editor is not the primary editor for meshes), and figures out what we can launch the editor on.
- L36 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L37 _public prototype_ `virtual void Deinitialize() override;`
- L40 _public prototype_ `bool IsObjectValidTarget(const TObjectPtr<UObject> InObject) const;` — Checks that the object is a valid target for a UV editor session.
- L43 _public prototype_ `virtual bool AreObjectsValidTargets(const TArray<UObject*>& InObjects) const;` — Checks that all of the objects are valid targets for a UV editor session.
- L46 _public prototype_ `bool IsAssetValidTarget(const FAssetData& InAsset) const;` — Checks that the asset is a valid target for a UV Editor session.
- L54 _public prototype_ `virtual bool AreAssetsValidTargets(const TArray<FAssetData>& InAssets) const;` — Checks that all of the assets are valid targets for an editor session. This is preferable over AreObjectsValidTargets when we have FAssetData because it allows us to avoid forcing a load of the underlying UObjects (for instance to avoid triggering a load when right clicking an asset in the content browser).
- L63 _public prototype_ `virtual void BuildTargets(const TArray<TObjectPtr<UObject>>& ObjectsIn, const FToolTargetTypeRequirements& TargetRequirements, TArray<TObjectPtr<UToolTarget>>& TargetsOut, TArray<int32>* ObjectToTargetMapOut = nullptr);` — Tries to build the core targets that provide meshes for UV tools to work on. ObjectToTargetMapOut provides a mapping from the input Object set to the output Target set, since these might not be 1:1 and we may need to know which objects are represented by a single source target
- L73 _public prototype_ `virtual void StartUVEditor(TArray<TObjectPtr<UObject>> ObjectsToEdit);` — Either brings to the front an existing UV editor instance that is editing one of these objects, if one exists, or starts up a new instance editing all of these objects.
- L79 _public prototype_ `virtual void NotifyThatUVEditorClosed(TArray<TObjectPtr<UObject>> ObjectsItWasEditing);` — Needs to be called when a UV editor instance is closed so that the subsystem knows to create a new one for these objects if they are opened again.
- L88 _protected member_ `TObjectPtr<UToolTargetManager> ToolTargetManager = nullptr;` — `UPROPERTY()` — Used to let the subsystem figure out whether targets are valid. New factories should be added here in Initialize() as they are developed.
- L90 _protected member_ `TMap<TObjectPtr<UObject>, TObjectPtr<UUVEditor>> OpenedEditorInstances;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITOR_API`
- L16 _prototype_ `PREDECLARE_GEOMETRY(class FAssetDynamicMeshTargetComboInterface);`

### `Plugins/Editor/UVEditor/Source/UVEditor/Public/UVEditorToolkit.h` (Public)


#### class `FUVEditorToolkit`  
`class FUVEditorToolkit : public FBaseAssetToolkit`  
_L31-103_
- inherits: `FBaseAssetToolkit`
- desc: The toolkit is supposed to act as the UI manager for the asset editor. It's responsible for setting up viewports and most toolbars, except for the internals of the mode panel. However, because the toolkit also sets up the mode manager, and much of the important state is held in the UUVEditorMode managed by the mode manager, the toolkit also ends up initializing the UV mode. Thus, the FUVEdiotrToolkit ends up being the central place for the UV Asset editor setup.
- L34 _public prototype_ `FUVEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L35 _public prototype_ `virtual ~FUVEditorToolkit();`
- L37 _public member_ `static const FName InteractiveToolsPanelTabID;`
- L38 _public member_ `static const FName LivePreviewTabID;`
- L40 _public function_ `FPreviewScene* GetPreviewScene()`
- L43 _public prototype_ `virtual void CreateWidgets() override;` — FBaseAssetToolkit
- L46 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override;` — FAssetEditorToolkit
- L47 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;`
- L48 _public prototype_ `virtual void CreateEditorModeManager() override;`
- L49 _public prototype_ `virtual FText GetToolkitName() const override;`
- L50 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L51 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L52 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L53 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L54 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L55 _public prototype_ `virtual void OnClose() override;`
- L56 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L57 _public prototype_ `virtual bool CanSaveAsset() const override;`
- L58 _public prototype_ `virtual bool CanSaveAssetAs() const override;`
- L59 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L60 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L65 _public function_ `virtual bool IsPrimaryEditor() const override` — IAssetEditorInstance This is important because if this returns true, attempting to edit a static mesh that is open in the UV editor may open the UV editor instead of opening the static mesh editor.
- L69 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_InteractiveToolsPanel(const FSpawnTabArgs& Args);`
- L70 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_LivePreview(const FSpawnTabArgs& Args);`
- L73 _protected prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;` — FBaseAssetToolkit
- L74 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L77 _protected prototype_ `virtual void PostInitAssetEditor() override;` — FAssetEditorToolkit
- L78 _protected prototype_ `virtual const FSlateBrush* GetDefaultTabIcon() const override;`
- L79 _protected prototype_ `virtual FLinearColor GetDefaultTabColor() const override;`
- L82 _protected member_ `TUniquePtr<FPreviewScene> UnwrapScene;` — Scene in which the 2D unwrapped uv meshes live.
- L85 _protected member_ `TUniquePtr<FAdvancedPreviewScene> LivePreviewScene;` — Scene in which the 3D preview meshes of the assets live.
- L89 _protected member_ `TSharedPtr<class FEditorViewportTabContent> LivePreviewTabContent;` — These are related to the 3D "live preview" viewport. The 2d unwrap viewport things are stored in FBaseAssetToolkit::ViewportTabContent, ViewportDelegate, ViewportClient
- L90 _protected member_ `AssetEditorViewportFactoryFunction LivePreviewViewportDelegate;`
- L91 _protected member_ `TSharedPtr<FEditorViewportClient> LivePreviewViewportClient;`
- L93 _protected member_ `TSharedPtr<FAssetEditorModeManager> LivePreviewEditorModeManager;`
- L94 _protected member_ `TObjectPtr<UInputRouter> LivePreviewInputRouter = nullptr;`
- L96 _protected member_ `TWeakPtr<SEditorViewport> UVEditor2DViewport;`
- L97 _protected member_ `UUVToolViewportButtonsAPI* ViewportButtonsAPI = nullptr;`
- L99 _protected member_ `UUVTool2DViewportAPI* UVTool2DViewportAPI = nullptr;`
- L101 _protected member_ `TSharedPtr<FUVEditorModeUILayer> ModeUILayer;`
- L102 _protected member_ `TSharedPtr<FWorkspaceItem> UVEditorMenuCategory;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITOR_API`
