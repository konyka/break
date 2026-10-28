# Plugins / ChaosClothAssetEditor

- module root: `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor`
- headers: 26; symbols: 738
- symbol kinds: class=29, delegate=3, enum=2, enumerator=6, function=46, macro=13, member=215, namespace=66, prototype=352, struct=6
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, ApplicationCore, AssetDefinition, BaseCharacterFXEditor, Chaos, ChaosCloth, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEditorTools, ChaosClothAssetEngine, ChaosClothAssetTools, ClothingSystemEditor, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, ContentBrowser, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DataflowEnginePlugin, DeveloperSettings, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, GeometryCore, GeometryFramework, InputCore, InteractiveToolsFramework, KismetWidgets, LevelEditor, MeshConversion, MeshDescription, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, Projects, RenderCore, Slate, SlateCore, StatusBar, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Internal/ChaosClothAsset/ChaosClothAssetThumbnailRenderer.h` (Internal)


#### class `AChaosClothPreviewActor`  
`class UE_DEPRECATED(5.8, "This class will be moved to the internal section of the ChaosClothAsset module.") AChaosClothPreviewActor : public AActor`  
_L17-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: Minimal actor with a cloth component used to render cloth assets previews
- L21 _public prototype_ `AChaosClothPreviewActor();`
- L23 _public function_ `UChaosClothComponent* GetClothComponent()`
- L30 _protected member_ `TObjectPtr<UChaosClothComponent> ClothComponent;` — `UPROPERTY()`

#### class `UE::Chaos::ClothAsset::FThumbnailScene`  
`class UE_DEPRECATED(5.8, "This class will be moved to the internal section of the ChaosClothAsset module.") FThumbnailScene : public FThumbnailPreviewScene`  
_L38-51_
- inherits: `FThumbnailPreviewScene`
- desc: Preview scene for a Cloth asset thumbnail
- L41 _public prototype_ `FThumbnailScene();`
- L43 _public prototype_ `void SetClothAsset(UChaosClothAssetBase* InClothAsset);`
- L45 _public prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;`
- L49 _private member_ `AChaosClothPreviewActor* PreviewActor;` — `UE_DEPRECATED(5.8, "This class will be moved to the internal section of the ChaosClothAsset module.")`

#### class `UChaosClothAssetThumbnailRenderer`  
`class UE_DEPRECATED(5.8, "This class will be moved to the internal section of the ChaosClothAsset module.") UChaosClothAssetThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L59-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- desc: Renders a preview scene to be used as a thumbnail for a supported cloth asset
- L63 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget* Viewport, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L64 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L65 _private prototype_ `virtual EThumbnailRenderFrequency GetThumbnailRenderFrequency(UObject* Object) const override;`
- L67 _private prototype_ `virtual void BeginDestroy() override;`
- L71 _protected member_ `TObjectInstanceThumbnailScene<UE::Chaos::ClothAsset::FThumbnailScene, 128> ClothThumbnailSceneCache;` — `UE_DEPRECATED(5.8, "This class will be moved to the internal section of the ChaosClothAsset module.")`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace Chaos` (scope `UE`)
- L33 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/AssetDefinition_ClothAsset.h` (Private)


#### class `UAssetDefinition_ClothAsset`  
`class UAssetDefinition_ClothAsset : public UAssetDefinitionDefault`  
_L11-35_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `static bool LaunchClothDataflowAssetEditor(UChaosClothAsset* ClothAsset);`
- L19 _public prototype_ `static bool LaunchClothPanelAssetEditor(UChaosClothAsset* ClothAsset);` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")`
- L22 _public prototype_ `static bool UseClothPanelEditorByDefault();` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")`
- L25 _public prototype_ `static bool AllowClothPanelEditor();` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")`
- L28 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L29 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L30 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L31 _private prototype_ `virtual bool CanImport() const override;`
- L32 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L33 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L34 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ChaosClothAssetEditorModule.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditorModule`  
`class FChaosClothAssetEditorModule final : public FBaseCharacterFXEditorModule`  
_L12-29_
- inherits: `FBaseCharacterFXEditorModule`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _private member_ `FDelegateHandle StartupCallbackDelegateHandle;`
- L22 _private member_ `FDelegateHandle OnCVarChangedDelegateHandle;`
- L23 _private member_ `FDelegateHandle DataflowMenusHandle;`
- L25 _private prototype_ `void RegisterMenus();`
- L27 _private member_ `TSharedPtr<FClothAssetComponentBroker> ClothAssetComponentBroker;`
- L28 _private member_ `TUniquePtr<FLegacyClothingConverterProvider> LegacyClothingConverterProvider;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothDataflowConstructionVisualization.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothDataflowConstructionVisualization`  
`class FClothDataflowConstructionVisualization : public UE::Dataflow::IDataflowConstructionVisualization`  
_L9-25_
- inherits: `UE::Dataflow::IDataflowConstructionVisualization`
- L12 _public member_ `static const FName Name;`
- L13 _public prototype_ `virtual ~FClothDataflowConstructionVisualization() = default;`
- L18 _private prototype_ `virtual FName GetName() const override;` — IDataflowConstructionVisualization
- L19 _private prototype_ `virtual void ExtendViewportShowMenu(const TSharedPtr<FDataflowConstructionViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder) override;`
- L20 _private prototype_ `virtual void Draw(const FDataflowConstructionScene* ConstructionScene, FPrimitiveDrawInterface* PDI, const FSceneView* View = nullptr) override;`
- L22 _private member_ `bool bSeamVisualizationEnabled = false;`
- L23 _private member_ `bool bCollapseSeams = false;`
- L24 _private member_ `bool bPatternColorVisualizationEnabled = false;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothDataflowSimulationVisualization.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothDataflowSimulationVisualization`  
`class FClothDataflowSimulationVisualization : public Dataflow::IDataflowSimulationVisualization`  
_L10-28_
- inherits: `Dataflow::IDataflowSimulationVisualization`
- L13 _public member_ `static const FName Name;`
- L14 _public prototype_ `virtual ~FClothDataflowSimulationVisualization() = default;`
- L19 _private prototype_ `virtual FName GetName() const override;` — IDataflowSimulationVisualization
- L20 _private prototype_ `virtual void ExtendSimulationVisualizationMenu(const TSharedPtr<FDataflowSimulationViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder) override;`
- L21 _private prototype_ `virtual void Draw(const FDataflowSimulationScene* SimulationScene, FPrimitiveDrawInterface* PDI) override;`
- L22 _private prototype_ `virtual void DrawCanvas(const FDataflowSimulationScene* SimulationScene, FCanvas* Canvas, const FSceneView* SceneView) override;`
- L23 _private prototype_ `virtual FText GetDisplayString(const FDataflowSimulationScene* SimulationScene) const override;`
- L25 _private prototype_ `const UChaosClothComponent* GetClothComponent(const FDataflowSimulationScene* SimulationScene) const;`
- L27 _private member_ `FClothEditorSimulationVisualization ClothEditorSimulationVisualization;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Chaos` (scope `UE`)
- L8 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditor.h` (Private)


#### class `UChaosClothAssetEditor`  
`class UChaosClothAssetEditor : public UBaseCharacterFXEditor`  
_L24-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCharacterFXEditor`
- L30 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L33 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothAssetEditor, Log, All);`
- L33 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogChaosClothAssetEditor, Log, All);`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditor3DViewportClient.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditor3DViewportClient`  
`class FChaosClothAssetEditor3DViewportClient : public FEditorViewportClient, public TSharedFromThis<FChaosClothAssetEditor3DViewportClient>, public IClickBehaviorTarget, public IClickDragBehaviorTarget, public IInputBehaviorSource, public IPreviewLODController`  
_L31-144_
- inherits: `FEditorViewportClient,TSharedFromThis<FChaosClothAssetEditor3DViewportClient>,IClickBehaviorTarget,IClickDragBehaviorTarget,IInputBehaviorSource,IPreviewLODController`
- desc: Viewport client for the 3d sim preview in the cloth editor. Currently same as editor viewport client but doesn't allow editor gizmos/widgets.
- L40 _public prototype_ `FChaosClothAssetEditor3DViewportClient(FEditorModeTools* InModeTools, TSharedPtr<FChaosClothPreviewScene> InPreviewScene, TSharedPtr<FClothEditorSimulationVisualization> InVisualization, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L45 _public prototype_ `void RegisterDelegates();` — Call this after construction to initialize callbacks when settings change
- L47 _public prototype_ `virtual ~FChaosClothAssetEditor3DViewportClient();`
- L50 _public prototype_ `void DeleteViewportGizmo();` — Delete the viewport gizmo and transform proxy
- L52 _public prototype_ `void ClearSelectedComponents();`
- L54 _public function_ `void EnableSimMeshWireframe(bool bEnable)`
- L55 _public function_ `bool SimMeshWireframeEnabled() const`
- L57 _public prototype_ `void EnableRenderMeshWireframe(bool bEnable);`
- L58 _public function_ `bool RenderMeshWireframeEnabled() const`
- L60 _public prototype_ `void SetClothEdMode(TObjectPtr<UChaosClothAssetEditorMode> ClothEdMode);`
- L61 _public prototype_ `void SetClothEditorToolkit(TWeakPtr<const FChaosClothAssetEditorToolkit> ClothToolkit);`
- L63 _public prototype_ `void SoftResetSimulation();`
- L64 _public prototype_ `void HardResetSimulation();`
- L65 _public prototype_ `void SuspendSimulation();`
- L66 _public prototype_ `void ResumeSimulation();`
- L67 _public prototype_ `bool IsSimulationSuspended() const;`
- L68 _public prototype_ `void SetEnableSimulation(bool bEnable);`
- L69 _public prototype_ `bool IsSimulationEnabled() const;`
- L73 _public prototype_ `virtual void SetLODLevel(int32 LODIndex) override;` — IPreviewLODController interface LODIndex == INDEX_NONE is LOD Auto
- L74 _public prototype_ `virtual int32 GetLODCount() const override;`
- L75 _public prototype_ `virtual int32 GetCurrentLOD() const override;`
- L76 _public prototype_ `virtual bool IsLODSelected(int32 LODIndex) const override;`
- L77 _public function_ `virtual int32 GetAutoLODStartingIndex() const override`
- L78 _public prototype_ `virtual void FillLODCommands(TArray<TSharedPtr<FUICommandInfo>>& Commands) override;`
- L81 _public prototype_ `FBox PreviewBoundingBox() const;`
- L83 _public prototype_ `TWeakPtr<FChaosClothPreviewScene> GetClothPreviewScene();`
- L84 _public prototype_ `TWeakPtr<const FChaosClothPreviewScene> GetClothPreviewScene() const;`
- L85 _public prototype_ `UChaosClothComponent* GetPreviewClothComponent();`
- L86 _public prototype_ `const UChaosClothComponent* GetPreviewClothComponent() const;`
- L87 _public function_ `TWeakPtr<FClothEditorSimulationVisualization> GetSimulationVisualization()`
- L90 _public function_ `TWeakPtr<const FChaosClothAssetEditorToolkit> GetClothToolKit() const`
- L95 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject override
- L98 _private function_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override` — FEditorViewportClient overrides
- L99 _private function_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override`
- L100 _private function_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override`
- L101 _private prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L102 _private prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L103 _private prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L106 _private prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;` — IClickBehaviorTarget
- L107 _private prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L110 _private prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget
- L111 _private function_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override`
- L112 _private function_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override`
- L113 _private function_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override`
- L114 _private function_ `virtual void OnTerminateDragSequence() override`
- L117 _private prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override;` — IInputBehaviorSource
- L119 _private prototype_ `void ComponentSelectionChanged(UObject* NewSelection);`
- L122 _private prototype_ `void UpdateSelection(HHitProxy* HitProxy);` — Update the selected components based on hitproxy
- L124 _private member_ `TWeakPtr<FChaosClothPreviewScene> ClothPreviewScene;`
- L126 _private member_ `TObjectPtr<UChaosClothAssetEditorMode> ClothEdMode;`
- L128 _private member_ `TWeakPtr<const FChaosClothAssetEditorToolkit> ClothToolkit;`
- L130 _private member_ `TWeakPtr<FClothEditorSimulationVisualization> ClothEditorSimulationVisualization;`
- L132 _private member_ `bool bSimMeshWireframe = true;`
- L133 _private member_ `bool bRenderMeshWireframe = false;`
- L136 _private member_ `UE::Dataflow::FTimestamp LastModifiedTimestamp = UE::Dataflow::FTimestamp::Invalid;` — Dataflow render support
- L139 _private member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — Gizmo support
- L140 _private member_ `TObjectPtr<UCombinedTransformGizmo> Gizmo = nullptr;`
- L141 _private member_ `TSharedPtr<FTransformGizmoDataBinder> DataBinder = nullptr;`
- L143 _private member_ `TObjectPtr<UInputBehaviorSet> InputBehaviorSet;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Chaos` (scope `UE`)
- L20 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorCommands.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditorCommands`  
`class FChaosClothAssetEditorCommands : public TBaseCharacterFXEditorCommands<FChaosClothAssetEditorCommands>`  
_L9-102_
- inherits: `TBaseCharacterFXEditorCommands<FChaosClothAssetEditorCommands>`
- L13 _public prototype_ `FChaosClothAssetEditorCommands();`
- L14 _public prototype_ `~FChaosClothAssetEditorCommands();`
- L17 _public prototype_ `FChaosClothAssetEditorCommands(const FChaosClothAssetEditorCommands&) = default;`
- L18 _public prototype_ `FChaosClothAssetEditorCommands(FChaosClothAssetEditorCommands&&) = default;`
- L19 _public prototype_ `FChaosClothAssetEditorCommands& operator=(const FChaosClothAssetEditorCommands&) = default;`
- L20 _public prototype_ `FChaosClothAssetEditorCommands& operator=(FChaosClothAssetEditorCommands&&) = default;`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — TBaseCharacterFXEditorCommands<> interface
- L27 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;` — TInteractiveToolCommands<>
- L34 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added
- L40 _public member_ `TSharedPtr<FUICommandInfo> OpenClothEditor;` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")`
- L42 _public member_ `TSharedPtr<FUICommandInfo> OpenClothAssetInClothPanelEditor;` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")`
- L44 _public member_ `TSharedPtr<FUICommandInfo> OpenClothAssetInDataflowEditor;` — `UE_DEPRECATED(5.8, "The Cloth Panel Editor is now deprecated, use the Dataflow Editor instead.")` — The Dataflow Editor command is no longer needed once the deprecation is completed
- L46 _public member_ `const static FString BeginRemeshToolIdentifier;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> BeginRemeshTool;`
- L49 _public member_ `const static FString BeginWeightMapPaintToolIdentifier;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> BeginWeightMapPaintTool;`
- L51 _public member_ `const static FString AddWeightMapNodeIdentifier;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> AddWeightMapNode;`
- L54 _public member_ `const static FString BeginAttributeEditorToolIdentifier;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> BeginAttributeEditorTool;`
- L57 _public member_ `const static FString BeginTransferSkinWeightsToolIdentifier;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> BeginTransferSkinWeightsTool;`
- L59 _public member_ `const static FString AddTransferSkinWeightsNodeIdentifier;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> AddTransferSkinWeightsNode;`
- L62 _public member_ `const static FString BeginMeshSelectionToolIdentifier;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> BeginMeshSelectionTool;`
- L64 _public member_ `const static FString AddMeshSelectionNodeIdentifier;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> AddMeshSelectionNode;`
- L68 _public member_ `const static FString ToggleConstructionViewWireframeIdentifier;` — Construction viewport commands
- L69 _public member_ `TSharedPtr<FUICommandInfo> ToggleConstructionViewWireframe;`
- L71 _public member_ `const static FString ToggleConstructionViewSeamsIdentifier;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> ToggleConstructionViewSeams;`
- L74 _public member_ `const static FString ToggleConstructionViewSeamsCollapseIdentifier;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> ToggleConstructionViewSeamsCollapse;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> TogglePatternColor;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ToggleMeshStats;`
- L80 _public member_ `const static FString ToggleConstructionViewSurfaceNormalsIdentifier;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> ToggleConstructionViewSurfaceNormals;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> SetConstructionMode2D;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> SetConstructionMode3D;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> SetConstructionModeRender;`
- L88 _public member_ `const static FString TogglePreviewWireframeIdentifier;` — Preview viewport commands
- L89 _public member_ `TSharedPtr<FUICommandInfo> TogglePreviewWireframe;`
- L91 _public member_ `const static FString SoftResetSimulationIdentifier;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> SoftResetSimulation;`
- L94 _public member_ `const static FString HardResetSimulationIdentifier;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> HardResetSimulation;`
- L97 _public member_ `const static FString ToggleSimulationSuspendedIdentifier;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> ToggleSimulationSuspended;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> LODAuto;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> LOD0;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorMode.h` (Private)


#### class `UChaosClothAssetEditorMode`  
`class UChaosClothAssetEditorMode final : public UBaseCharacterFXEditorMode`  
_L52-331_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseCharacterFXEditorMode`
- desc: The cloth editor mode is the mode used in the cloth asset editor. It holds most of the inter-tool state. We put things in a mode instead of directly into the asset editor in case we want to someday use the mode in multiple asset editors.
- L58 _public member_ `const static FEditorModeID EM_ChaosClothAssetEditorModeId;`
- L60 _public prototype_ `UChaosClothAssetEditorMode();`
- L63 _public prototype_ `FBox SelectionBoundingBox() const;` — Bounding box for selected rest space mesh components
- L66 _public prototype_ `FBox PreviewBoundingBox() const;` — Bounding box for sim space meshes
- L68 _public prototype_ `void SetConstructionViewMode(UE::Chaos::ClothAsset::EClothPatternVertexType InMode);`
- L69 _public prototype_ `UE::Chaos::ClothAsset::EClothPatternVertexType GetConstructionViewMode() const;`
- L70 _public prototype_ `bool CanChangeConstructionViewModeTo(UE::Chaos::ClothAsset::EClothPatternVertexType NewViewMode) const;`
- L72 _public prototype_ `void ToggleConstructionViewWireframe();`
- L73 _public prototype_ `bool CanSetConstructionViewWireframeActive() const;`
- L74 _public function_ `bool IsConstructionViewWireframeActive() const`
- L79 _public prototype_ `void ToggleConstructionViewSeams();`
- L80 _public prototype_ `bool CanSetConstructionViewSeamsActive() const;`
- L81 _public function_ `bool IsConstructionViewSeamsActive() const`
- L86 _public prototype_ `void ToggleConstructionViewSeamsCollapse();`
- L87 _public prototype_ `bool CanSetConstructionViewSeamsCollapse() const;`
- L88 _public function_ `bool IsConstructionViewSeamsCollapseActive() const`
- L93 _public prototype_ `void TogglePatternColor();`
- L94 _public prototype_ `bool CanSetPatternColor() const;`
- L95 _public function_ `bool IsPatternColorActive() const`
- L100 _public prototype_ `void ToggleConstructionViewSurfaceNormals();`
- L101 _public prototype_ `bool CanSetConstructionViewSurfaceNormalsActive() const;`
- L102 _public function_ `bool IsConstructionViewSurfaceNormalsActive() const`
- L107 _public prototype_ `void ToggleMeshStats();`
- L108 _public prototype_ `bool CanSetMeshStats() const;`
- L109 _public function_ `bool IsMeshStatsActive() const`
- L115 _public prototype_ `void SoftResetSimulation();` — Simulation controls
- L116 _public prototype_ `void HardResetSimulation();`
- L117 _public prototype_ `void SuspendSimulation();`
- L118 _public prototype_ `void ResumeSimulation();`
- L119 _public prototype_ `bool IsSimulationSuspended() const;`
- L120 _public prototype_ `void SetEnableSimulation(bool bEnabled);`
- L121 _public prototype_ `bool IsSimulationEnabled() const;`
- L123 _public prototype_ `int32 GetConstructionViewTriangleCount() const;`
- L124 _public prototype_ `int32 GetConstructionViewVertexCount() const;`
- L127 _public prototype_ `void SetLODModel(int32 LODIndex);` — LODIndex == INDEX_NONE is LOD Auto
- L128 _public prototype_ `bool IsLODModelSelected(int32 LODIndex) const;`
- L129 _public prototype_ `int32 GetLODModel() const;`
- L130 _public prototype_ `int32 GetNumLODs() const;`
- L132 _public function_ `TObjectPtr<UEditorInteractiveToolsContext> GetActiveToolsContext()`
- L143 _private prototype_ `virtual void Enter() final;` — UEdMode
- L144 _private prototype_ `virtual void Exit() override;`
- L145 _private prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L146 _private prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L147 _private prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L148 _private prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L149 _private prototype_ `virtual void CreateToolkit() override;`
- L150 _private prototype_ `virtual void BindCommands() override;`
- L156 _private prototype_ `virtual void AddToolTargetFactories() override;` — UBaseCharacterFXEditorMode
- L157 _private prototype_ `virtual void RegisterTools() override;`
- L158 _private prototype_ `virtual void CreateToolTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L159 _private prototype_ `virtual void InitializeTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L163 _private prototype_ `static const FToolTargetTypeRequirements& GetToolTargetRequirements();` — Gets the tool target requirements for the mode. The resulting targets undergo further processing to turn them into the input objects that tools get (since these need preview meshes, etc).
- L166 _private prototype_ `void RegisterClothTool(TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder, const IChaosClothAssetEditorToolBuilder* ClothToolBuilder, UEditorInteractiveToolsContext* UseToolsContext, EToolsContextScope ToolScope = EToolsContextScope::Default);` — Use this function to register tools rather than UEdMode::RegisterTool() because we need to specify the ToolsContext
- L173 _private prototype_ `void RegisterAddNodeCommand(TSharedPtr<FUICommandInfo> AddNodeCommand, const FName& NewNodeType, TSharedPtr<FUICommandInfo> StartToolCommand);`
- L175 _private prototype_ `void SetPreviewScene(UE::Chaos::ClothAsset::FChaosClothPreviewScene* PreviewScene);`
- L178 _private prototype_ `virtual FBox SceneBoundingBox() const override;` — Bounding box for rest space meshes
- L180 _private prototype_ `void SetRestSpaceViewportClient(TWeakPtr<UE::Chaos::ClothAsset::FChaosClothEditorRestSpaceViewportClient, ESPMode::ThreadSafe> ViewportClient);`
- L181 _private prototype_ `void RefocusRestSpaceViewportClient();`
- L182 _private prototype_ `void FirstTimeFocusRestSpaceViewport();`
- L185 _private prototype_ `void SetSelectedClothCollection(TSharedPtr<FManagedArrayCollection> Collection, TSharedPtr<FManagedArrayCollection> InputCollection = nullptr, bool bDeferDynamicMeshInitForTool = false);` — intended to be called by the toolkit when selected node in the Dataflow graph changes
- L188 _private prototype_ `TSharedPtr<FManagedArrayCollection> GetClothCollection();` — gets the currently selected cloth collection, as specified by the toolkit
- L189 _private prototype_ `TSharedPtr<FManagedArrayCollection> GetInputClothCollection();`
- L191 _private prototype_ `void SetDataflowContext(TWeakPtr<UE::Dataflow::FEngineContext> InDataflowContext);`
- L192 _private prototype_ `void SetDataflowGraphEditor(TSharedPtr<SDataflowGraphEditor> InGraphEditor);`
- L194 _private prototype_ `void StartToolForSelectedNode(const UObject* SelectedNode);`
- L195 _private prototype_ `void OnDataflowNodeDeleted(const TSet<UObject*>& DeletedNodes);`
- L201 _private prototype_ `UEdGraphNode* GetSingleSelectedNodeWithOutputType(const FName& SelectedNodeOutputTypeName) const;` — Return the single selected node in the Dataflow Graph Editor only if it has an output of the specified type If there is not a single node selected, or if it does not have the specified output, return null
- L206 _private prototype_ `UEdGraphNode* CreateNewNode(const FName& NewNodeTypeName);` — Create a node with the specified type in the graph
- L226 _private prototype_ `UEdGraphNode* CreateAndConnectNewNode(const FName& NewNodeTypeName, UEdGraphNode& UpstreamNode, const FName& ConnectionTypeName, const FName& NewNodeConnectionName);` — Create a node with the specified type, then connect it to the output of the specified UpstreamNode. If the specified output of the upstream node is already connected to another node downstream, we first break that connecttion, then insert the new node along the previous connection. We want to turn this: [UpstreamNode] ----> [DownstreamNode(s)] to this: [UpstreamNode] ----> [NewNode] ----> [DownstreamNode(s)] @param NewNodeTypeName The type of node to create, by name @param UpstreamNode Node to connect the new node to @param ConnectionTypeName The type of output of the upstream node to connect our new node to @param NewNodeConnectionName The name of the input/output connection on our new node that will be connected @return The newly-created node
- L228 _private prototype_ `void AddNode(FName NewNodeType);`
- L229 _private prototype_ `bool CanAddNode(FName NewNodeType) const;`
- L232 _private prototype_ `void InitializeContextObject();`
- L233 _private prototype_ `void UpdateContextObject(const TSharedPtr<FManagedArrayCollection>& Collection);`
- L234 _private prototype_ `void DeleteContextObject();`
- L236 _private prototype_ `bool IsComponentSelected(const UPrimitiveComponent* InComponent);`
- L240 _private member_ `TObjectPtr<UMeshElementsVisualizer> WireframeDraw = nullptr;` — `UPROPERTY()` — Rest space wireframe. They have to get ticked to be able to respond to setting changes.
- L243 _private member_ `TObjectPtr<UPreviewGeometry> ClothSeamDraw = nullptr;` — `UPROPERTY()`
- L246 _private member_ `TObjectPtr<UPreviewGeometry> SurfaceNormalDraw = nullptr;` — `UPROPERTY()`
- L249 _private member_ `UE::Chaos::ClothAsset::FChaosClothPreviewScene* PreviewScene = nullptr;` — Preview Scene, here largely for convenience to avoid having to pass it around functions. Owned by the ClothEditorToolkit.
- L253 _private member_ `TArray<TObjectPtr<UInteractiveToolPropertySet>> PropertyObjectsToTick;` — `UPROPERTY()` — Mode-level property objects (visible or not) that get ticked.
- L257 _private member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent = nullptr;` — `UPROPERTY()` — Rest space editable mesh
- L261 _private member_ `TObjectPtr<AActor> DynamicMeshComponentParentActor = nullptr;` — `UPROPERTY()` — Actor required for hit testing DynamicMeshComponent
- L263 _private member_ `TWeakPtr<UE::Chaos::ClothAsset::FChaosClothEditorRestSpaceViewportClient, ESPMode::ThreadSafe> RestSpaceViewportClient;`
- L266 _private member_ `bool bDynamicMeshComponentInitDeferred = false;` — The dynamic mesh component needs to be reinitialized on next tick.
- L268 _private member_ `bool bDynamicMeshUseInputCollection = false;` — Use the input collection to build the dynamic mesh component (used by tools).
- L271 _private member_ `bool bFirstValid2DMesh = true;` — The first time we get a valid mesh, refocus the camera on it
- L272 _private member_ `bool bFirstValid3DMesh = true;`
- L275 _private member_ `bool bShouldFocusRestSpaceView = true;` — Whether the rest space viewport should focus on the rest space mesh on the next tick
- L277 _private prototype_ `void RestSpaceViewportResized(FViewport* RestspaceViewport, uint32 Unused);`
- L279 _private member_ `UE::Chaos::ClothAsset::EClothPatternVertexType ConstructionViewMode;`
- L282 _private member_ `UE::Chaos::ClothAsset::EClothPatternVertexType SavedConstructionViewMode;` — The Construction view mode that was active before starting the current tool. When the tool ends, restore this view mode if bShouldRestoreSavedConstructionViewMode is true.
- L285 _private member_ `bool bShouldRestoreSavedConstructionViewMode = false;` — Whether we should restore the previous view mode when a tool ends
- L288 _private member_ `FName NodeTypeForPendingToolStart;` — Dataflow node type whose corresponding tool should be started on the next Tick
- L290 _private member_ `bool bConstructionViewWireframe = false;`
- L291 _private member_ `bool bShouldRestoreConstructionViewWireframe = false;`
- L293 _private member_ `bool bConstructionViewSeamsVisible = false;`
- L294 _private member_ `bool bShouldRestoreConstructionViewSeams = false;`
- L295 _private member_ `bool bConstructionViewSeamsCollapse = false;`
- L296 _private prototype_ `void InitializeSeamDraw();`
- L298 _private member_ `bool bConstructionViewNormalsVisible = false;`
- L299 _private prototype_ `void InitializeSurfaceNormalDraw();`
- L301 _private member_ `bool bPatternColors = false;`
- L302 _private member_ `bool bMeshStats = false;`
- L305 _private prototype_ `void ReinitializeDynamicMeshComponents();` — Create dynamic mesh components from the cloth component's rest space info
- L308 _private member_ `bool bShouldResetSimulation = false;` — Simulation controls
- L309 _private member_ `bool bHardReset = false;`
- L310 _private member_ `bool bShouldClearTeleportFlag = false;`
- L312 _private member_ `TWeakObjectPtr<UDataflow> DataflowGraph = nullptr;`
- L314 _private member_ `TWeakPtr<SDataflowGraphEditor> DataflowGraphEditor;`
- L317 _private member_ `TObjectPtr<UEditorInteractiveToolsContext> ActiveToolsContext = nullptr;` — `UPROPERTY()`
- L318 _private member_ `TWeakPtr<UE::Dataflow::FEngineContext> DataflowContext;`
- L319 _private member_ `TSharedPtr<FManagedArrayCollection> SelectedClothCollection = nullptr;`
- L320 _private member_ `TSharedPtr<FManagedArrayCollection> SelectedInputClothCollection = nullptr;`
- L323 _private member_ `TMap<FName, TSharedPtr<const FUICommandInfo>> NodeTypeToAddNodeCommandMap;` — Correspondence between node types and commands to add the node to the graph
- L326 _private member_ `TMap<FName, TSharedPtr<const FUICommandInfo>> NodeTypeToToolCommandMap;` — Correspondence between node types and commands to launch tools
- L329 _private member_ `FDateTime LastModeStartTimestamp;` — Timestamps for telemetry
- L330 _private member_ `FDateTime LastToolStartTimestamp;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L14 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace Chaos` (scope `UE`)
- L35 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorModeToolkit.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditorModeToolkit`  
`class FChaosClothAssetEditorModeToolkit : public FBaseCharacterFXEditorModeToolkit`  
_L22-44_
- inherits: `FBaseCharacterFXEditorModeToolkit`
- L26 _public prototype_ `void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode);`
- L28 _public prototype_ `virtual const FSlateBrush* GetActiveToolIcon(const FString& Identifier) const override;`
- L30 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L31 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L34 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit
- L35 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L37 _public prototype_ `void SetRestSpaceViewportWidget(TWeakPtr<SChaosClothAssetEditorRestSpaceViewport>);`
- L41 _private prototype_ `UEditorInteractiveToolsContext* GetCurrentToolsContext();`
- L43 _private member_ `TWeakPtr<SChaosClothAssetEditorRestSpaceViewport> RestSpaceViewportWidget;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Chaos` (scope `UE`)
- L20 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorModeUILayer.h` (Private)


#### class `UChaosClothAssetEditorUISubsystem`  
`class UChaosClothAssetEditorUISubsystem : public UAssetEditorUISubsystem`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditorUISubsystem`
- desc: Interchange layer to manage built in tab locations within the editor's layout.
- L17 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L18 _public prototype_ `virtual void Deinitialize() override;`
- L19 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`
- L22 _public member_ `static const FName EditorSidePanelAreaName;` — Identifier for the Layout extension in ChaosClothAssetEditorToolkit's StandaloneDefaultLayout

#### class `FChaosClothAssetEditorModeUILayer`  
`class FChaosClothAssetEditorModeUILayer : public FBaseCharacterFXEditorModeUILayer`  
_L27-31_
- inherits: `FBaseCharacterFXEditorModeUILayer`
- desc: Handles the hosting of additional toolkits, such as the mode toolkit, within the ChaosClothAssetEditor's toolkit.
- L30 _public function_ `FChaosClothAssetEditorModeUILayer(const IToolkitHost* InToolkitHost) : FBaseCharacterFXEditorModeUILayer(InToolkitHost)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorOptions.h` (Private)


#### enum `EConstructionViewportMousePanButton`  
`enum class EConstructionViewportMousePanButton : uint8`  
_L9-19_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `Right = 0` — Right Mouse Button
- L15 _public enumerator_ `Middle = 1` — Middle Mouse Button
- L18 _public enumerator_ `RightOrMiddle = 2` — Either Right or Middle Mouse Buttons

#### class `UChaosClothEditorOptions`  
`class UChaosClothEditorOptions : public UDeveloperSettings`  
_L24-45_
- reflection: `UCLASS(HideCategories = Object, Config = EditorPerProjectUserSettings, Meta = (DisplayName = "Chaos Cloth Editor"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: A settings class used to store and retreive user settings related to the Cloth Editor
- L32 _public member_ `bool bClothAssetsOpenInDataflowEditor;` — `UPROPERTY(Config)` — Whether Chaos Cloth Assets open in the Dataflow Editor (vs in the Cloth Editor)
- L36 _public member_ `EConstructionViewportMousePanButton ConstructionViewportMousePanButton;` — `UPROPERTY(Config, EditAnywhere, Category = UI)` — Which mouse button controls camera panning in the Construction Viewport in 2D view mode
- L39 _public prototype_ `virtual FName GetCategoryName() const override;` — UDeveloperSettings overrides
- L42 _public prototype_ `virtual FText GetSectionText() const override;`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorPreviewScene.h` (Private)


#### class `UChaosClothPreviewSceneDescription`  
`class UChaosClothPreviewSceneDescription : public UObject`  
_L30-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L35 _public member_ `FClothPreviewSceneDescriptionChanged ClothPreviewSceneDescriptionChanged;`
- L37 _public function_ `UChaosClothPreviewSceneDescription()`
- L42 _public prototype_ `void SetPreviewScene(UE::Chaos::ClothAsset::FChaosClothPreviewScene* PreviewScene);`
- L46 _public member_ `bool bPauseWhilePlayingInEditor = true;` — `UPROPERTY(EditAnywhere, Transient, Category = "Viewport")` — Whether the preview viewport should pause animation and simulation while Play In Editor (PIE) or Simulate In Editor is active
- L50 _public member_ `TObjectPtr<USkeletalMesh> SkeletalMeshAsset;` — `UPROPERTY(EditAnywhere, Transient, Category="SkeletalMesh")` — Skeletal Mesh source asset
- L53 _public member_ `TObjectPtr<UAnimationAsset> AnimationAsset;` — `UPROPERTY(EditAnywhere, Transient, Category = "SkeletalMesh")`
- L56 _public member_ `bool bPostProcessBlueprint;` — `UPROPERTY(EditAnywhere, Transient, Category = "SkeletalMesh")`
- L59 _public member_ `FVector3d Translation = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Transient, Category = "Transform", Meta = (EditCondition = "bValidSelectionForTransform", HideEditConditionToggle))`
- L62 _public member_ `FVector3d Rotation = FVector3d::ZeroVector;` — `UPROPERTY(EditAnywhere, Transient, Category = "Transform", Meta = (EditCondition = "bValidSelectionForTransform", HideEditConditionToggle))`
- L65 _public member_ `FVector3d Scale = FVector3d::OneVector;` — `UPROPERTY(EditAnywhere, Transient, Category = "Transform", Meta = (AllowPreserveRatio, EditCondition = "bValidSelectionForTransform", HideEditConditionToggle))`
- L68 _public member_ `float SolverGeometryScale = 1.f;` — `UPROPERTY(EditAnywhere, Transient, Category = "ClothComponent", Meta = (UIMin = 0.0, UIMax = 10.0, ClampMin = 0.0, ClampMax = 10000.0))`
- L75 _public member_ `float TeleportDistanceThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Transient, Category = ClothComponent)` — Conduct teleportation if the character's movement is greater than this threshold in 1 frame. Zero or negative values will skip the check.
- L83 _public member_ `float TeleportRotationThreshold = 0.f;` — `UPROPERTY(EditAnywhere, Transient, Category = ClothComponent)` — Rotation threshold in degrees, ranging from 0 to 180. Conduct teleportation if the character's rotation is greater than this threshold in 1 frame. Zero or negative values will skip the check.
- L86 _public member_ `bool bValidSelectionForTransform = false;` — `UPROPERTY(Transient)`
- L88 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L92 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L94 _private member_ `UE::Chaos::ClothAsset::FChaosClothPreviewScene* PreviewScene;`

#### class `UE::Chaos::ClothAsset::FChaosClothPreviewScene`  
`class FChaosClothPreviewScene : public FAdvancedPreviewScene`  
_L103-173_
- inherits: `FAdvancedPreviewScene`
- L107 _public prototype_ `FChaosClothPreviewScene(FPreviewScene::ConstructionValues ConstructionValues);`
- L108 _public prototype_ `virtual ~FChaosClothPreviewScene();`
- L110 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L112 _public function_ `const UChaosClothPreviewSceneDescription* GetPreviewSceneDescription() const`
- L113 _public function_ `UChaosClothPreviewSceneDescription* GetPreviewSceneDescription()`
- L115 _public prototype_ `void SetClothAsset(UChaosClothAsset* Asset);`
- L118 _public prototype_ `void SceneDescriptionPropertyChanged(const FName& PropertyName);` — Update Scene in response to the SceneDescription changing
- L120 _public prototype_ `UAnimSingleNodeInstance* GetPreviewAnimInstance();`
- L121 _public prototype_ `const UAnimSingleNodeInstance* const GetPreviewAnimInstance() const;`
- L123 _public prototype_ `UChaosClothComponent* GetClothComponent();`
- L124 _public prototype_ `const UChaosClothComponent* GetClothComponent() const;`
- L126 _public prototype_ `const USkeletalMeshComponent* GetSkeletalMeshComponent() const;`
- L129 _public prototype_ `void SetModeManager(const TSharedPtr<FAssetEditorModeManager>& InClothPreviewEditorModeManager);` — Set the scene's ModeManager, which is mainly used to track selected components
- L131 _public prototype_ `void SetGizmoDataBinder(TSharedPtr<FTransformGizmoDataBinder> InDataBinder);`
- L135 _private prototype_ `virtual void Tick(float DeltaT) override;`
- L138 _private prototype_ `void UpdateSkeletalMeshAnimation();` — Create the PreviewAnimationInstance if the AnimationAsset and SkeletalMesh both exist, and set the animation to run on the SkeletalMeshComponent
- L141 _private prototype_ `void UpdateClothComponentAttachment();` — Attach the cloth component to the skeletal mesh component, if it exists
- L143 _private prototype_ `bool IsComponentSelected(const UPrimitiveComponent* InComponent);`
- L145 _private prototype_ `void SaveAnimationState();`
- L146 _private prototype_ `void RestoreSavedAnimationState();`
- L147 _private prototype_ `void HandlePackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);`
- L148 _private prototype_ `void HandleReimportManagerPostReimport(UObject* ReimportedObject, bool bWasSuccessful);`
- L150 _private member_ `TObjectPtr<UChaosClothPreviewSceneDescription> PreviewSceneDescription;`
- L152 _private member_ `TSharedPtr<FAssetEditorModeManager> ClothPreviewEditorModeManager;`
- L154 _private member_ `TObjectPtr<AActor> SceneActor;`
- L156 _private member_ `TObjectPtr<UChaosClothComponent> ClothComponent;`
- L158 _private member_ `TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;`
- L160 _private member_ `TSharedPtr<FTransformGizmoDataBinder> DataBinder = nullptr;`
- L169 _private member_ `TOptional<FAnimState> SavedAnimState;`
- L171 _private member_ `FDelegateHandle OnPackageReloadedDelegateHandle;`
- L172 _private member_ `FDelegateHandle OnPostReimportDelegateHandle;`

#### struct `UE::Chaos::ClothAsset::FChaosClothPreviewScene::FAnimState`  
`struct FAnimState`  
_L162-168_
- L164 _public member_ `float Time;`
- L165 _public member_ `bool bIsReverse;`
- L166 _public member_ `bool bIsLooping;`
- L167 _public member_ `bool bIsPlaying;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Chaos` (scope `UE`)
- L19 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L24 _delegate_ `DECLARE_EVENT(UChaosClothPreviewSceneDescription, FClothPreviewSceneDescriptionChanged)`
- L98 _namespace_ `namespace UE`
- L98 _namespace_ `namespace Chaos` (scope `UE`)
- L98 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorRestSpaceViewportClient.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothEditorRestSpaceViewportClient`  
`class FChaosClothEditorRestSpaceViewportClient : public FEditorViewportClient, public IInputBehaviorSource`  
_L20-69_
- inherits: `FEditorViewportClient,IInputBehaviorSource`
- L24 _public prototype_ `FChaosClothEditorRestSpaceViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene = nullptr, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L26 _public prototype_ `virtual ~FChaosClothEditorRestSpaceViewportClient() = default;`
- L29 _public prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override;` — IInputBehaviorSource
- L32 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L34 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L36 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L38 _public prototype_ `void SetConstructionViewMode(EClothPatternVertexType InViewMode);`
- L39 _public prototype_ `EClothPatternVertexType GetConstructionViewMode() const;`
- L41 _public prototype_ `void SetEditorViewportWidget(TWeakPtr<SEditorViewport> InEditorViewportWidget);`
- L42 _public prototype_ `void SetToolCommandList(TWeakPtr<FUICommandList> ToolCommandList);`
- L44 _public prototype_ `float GetCameraPointLightIntensity() const;`
- L45 _public prototype_ `void SetCameraPointLightIntensity(float Intensity);`
- L49 _private prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L51 _private prototype_ `void UpdateBehaviorsForCurrentViewMode();`
- L53 _private member_ `TObjectPtr<UPointLightComponent> CameraPointLight;`
- L55 _private member_ `EClothPatternVertexType ConstructionViewMode = EClothPatternVertexType::Sim2D;`
- L57 _private member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;`
- L59 _private member_ `TArray<TObjectPtr<UInputBehavior>> BehaviorsFor2DMode;`
- L60 _private member_ `TArray<TObjectPtr<UInputBehavior>> BehaviorsFor3DMode;`
- L62 _private member_ `TUniquePtr<FEditor2DScrollBehaviorTarget> ScrollBehaviorTarget;`
- L63 _private member_ `TUniquePtr<FEditor2DMouseWheelZoomBehaviorTarget> ZoomBehaviorTarget;`
- L65 _private member_ `TWeakPtr<FUICommandList> ToolCommandList;`
- L68 _private member_ `FViewportCameraTransform SavedInactiveViewTransform;` — Saved view transform for the currently inactive view mode (i.e. store the 3D camera here while in 2D mode and vice-versa)

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Chaos` (scope `UE`)
- L17 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorSimulationVisualization.h` (Private)


#### class `UE::Chaos::ClothAsset::FClothEditorSimulationVisualization`  
`class FClothEditorSimulationVisualization`  
_L26-103_
- L29 _public prototype_ `FClothEditorSimulationVisualization();`
- L31 _public prototype_ `void ExtendViewportShowMenu(FMenuBuilder& MenuBuilder, const TSharedRef<FChaosClothAssetEditor3DViewportClient>& ViewportClient);`
- L32 _public prototype_ `void ExtendViewportShowMenu(FMenuBuilder& MenuBuilder, const TSharedRef<FDataflowSimulationViewportClient>& ViewportClient);`
- L34 _public prototype_ `void DebugDrawSimulation(const UChaosClothComponent* ClothComponent, FPrimitiveDrawInterface* PDI);`
- L35 _public prototype_ `void DebugDrawSimulationTexts(const UChaosClothComponent* ClothComponent, FCanvas* Canvas, const FSceneView* SceneView);`
- L36 _public prototype_ `FText GetDisplayString(const UChaosClothComponent* ClothComponent) const;`
- L37 _public prototype_ `void RefreshMenusForClothComponent(const UChaosClothComponent* ClothComponent);`
- L40 _public function_ `const FString* GetCurrentlySelectedWeightMap() const` — WeightMaps
- L41 _public prototype_ `void ExtendViewportShowMenuWeightMapSelector(FMenuBuilder& MenuBuilder);`
- L43 _public function_ `const FString* GetCurrentlySelectedMorphTarget() const` — Morph Targets
- L44 _public prototype_ `void ExtendViewportShowMenuMorphTargetSelector(FMenuBuilder& MenuBuilder);`
- L46 _public function_ `const FString* GetCurrentlySelectedAccessoryMesh() const` — Accessory Meshes
- L47 _public prototype_ `void ExtendViewportShowMenuAccessoryMeshSelector(FMenuBuilder& MenuBuilder);`
- L49 _public function_ `const FString* GetCurrentlySelectedFilterSetSelection() const` — DebugFilterSet
- L50 _public prototype_ `void ExtendViewportShowMenuFilterSetSelection(FMenuBuilder& MenuBuilder);`
- L52 _public prototype_ `void ExtendViewportShowMenuPointNormalsLength(FMenuBuilder& MenuBuilder);` — Normals
- L53 _public prototype_ `void ExtendViewportShowMenuAnimatedNormalsLength(FMenuBuilder& MenuBuilder);`
- L54 _public prototype_ `void ExtendViewportShowMenuAerodynamicsLengthScale(FMenuBuilder& MenuBuilder);`
- L55 _public prototype_ `void ExtendViewportShowMenuAccessoryMeshNormalsLength(FMenuBuilder& MenuBuilder);`
- L56 _public prototype_ `void ExtendViewportShowMenuWindVelocityLength(FMenuBuilder& MenuBuilder);`
- L57 _public prototype_ `void ExtendViewportShowMenuLocalSpaceLengthScale(FMenuBuilder& MenuBuilder);`
- L58 _public prototype_ `void ExtendViewportShowMenuVelocityScaleLength(FMenuBuilder& MenuBuilder);`
- L59 _public prototype_ `void ExtendViewportShowMenuSingleVertexSelection(FMenuBuilder& MenuBuilder);`
- L60 _public function_ `float GetPointNormalLength() const`
- L61 _public function_ `float GetAnimatedNormalLength() const`
- L62 _public function_ `float GetAccessoryMeshNormalLength() const`
- L63 _public function_ `float GetAerodynamicsLengthScale() const`
- L64 _public function_ `float GetWindVelocityLengthScale() const`
- L65 _public function_ `float GetVelocityScaleLength() const`
- L66 _public function_ `float GetLocalSpaceLengthScale() const`
- L67 _public function_ `int32 GetSingleVertexSelectionValue() const`
- L78 _private prototype_ `void ExtendViewportShowMenu(FMenuBuilder& MenuBuilder, FEditorViewportClient& ViewportClient, const TFunction<UChaosClothComponent*()>& GetClothComponentFunc);`
- L81 _private prototype_ `bool ShouldDisableSimulation() const;` — Return whether or not - given the current enabled options - the simulation should be disabled.
- L83 _private prototype_ `void ShowClothSections(UChaosClothComponent* ClothComponent, bool bIsClothSectionsVisible) const;` — Show/hide all cloth sections for the specified mesh compoment.
- L85 _private prototype_ `template<typename T> void ExtendViewportShowMenuSpinBox(FMenuBuilder& MenuBuilder, T& Value, const T MinValue, const T MaxValue, const T MinSliderValue, const T MaxSliderValue, const FText& ToolTipText);`
- L86 _private prototype_ `void ExtendViewportShowMenuNameSelector(FMenuBuilder& MenuBuilder, FNameSelectionData& SelectionData, const FText& ToolTipText);`
- L90 _private member_ `TBitArray<> Flags;` — Flags used to store the checked status for the visualization options.
- L91 _private member_ `FNameSelectionData WeightMapSelection;`
- L92 _private member_ `FNameSelectionData MorphTargetSelection;`
- L93 _private member_ `FNameSelectionData AccessoryMeshSelection;`
- L94 _private member_ `FNameSelectionData FilterSetSelection;`
- L95 _private member_ `float PointNormalLength = 7.f;`
- L96 _private member_ `float AnimatedNormalLength = 7.f;`
- L97 _private member_ `float AccessoryMeshNormalLength = 7.f;`
- L98 _private member_ `float AerodynamicsLengthScale = 10.f;`
- L99 _private member_ `float WindVelocityLengthScale = .1f;`
- L100 _private member_ `float VelocityScaleLength = .1f;`
- L101 _private member_ `float LocalSpaceLengthScale = 1.f;`
- L102 _private member_ `int32 SingleVertexSelection = 0;`

#### struct `UE::Chaos::ClothAsset::FClothEditorSimulationVisualization::FNameSelectionData`  
`struct FNameSelectionData`  
_L70-75_
- L72 _public member_ `TSharedPtr<STextComboBox> Selector;`
- L73 _public member_ `TArray<TSharedPtr<FString>> Names;`
- L74 _public member_ `TSharedPtr<FString> CurrentlySelectedName;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ESelectInfo`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Chaos` (scope `UE`)
- L21 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorStyle.h` (Private)


#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditorStyle`  
`class FChaosClothAssetEditorStyle : public FSlateStyleSet`  
_L15-27_
- inherits: `FSlateStyleSet`
- desc: Slate style set for Cloth Editor
- L19 _public member_ `const static FName StyleName;`
- L22 _public prototype_ `static FChaosClothAssetEditorStyle& Get();` — Access the singleton instance for this style set
- L25 _private prototype_ `FChaosClothAssetEditorStyle();`
- L26 _private prototype_ `~FChaosClothAssetEditorStyle();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Chaos` (scope `UE`)
- L10 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorToolkit.h` (Private)


#### class `UE::Dataflow::FClothAssetDataflowContext`  
`class FClothAssetDataflowContext final : public TEngineContext<FContextSingle>`  
_L32-40_
- inherits: `TEngineContext<FContextSingle>`
- L35 _public prototype_ `DATAFLOW_CONTEXT_INTERNAL(TEngineContext<FContextSingle>, FClothAssetDataflowContext);`
- L37 _public function_ `FClothAssetDataflowContext(UObject* InOwner, UDataflow* InGraph) : Super(InOwner)`

#### class `UE::Chaos::ClothAsset::FChaosClothAssetEditorToolkit`  
`class FChaosClothAssetEditorToolkit final : public FBaseCharacterFXEditorToolkit, public FTickableEditorObject, public FNotifyHook`  
_L53-189_
- inherits: `FBaseCharacterFXEditorToolkit,FTickableEditorObject,FNotifyHook`
- desc: The toolkit is supposed to act as the UI manager for the asset editor. It's responsible for setting up viewports and most toolbars, except for the internals of the mode panel. However, because the toolkit also sets up the mode manager, and much of the important state is held in the UChaosClothAssetEditorMode managed by the mode manager, the toolkit also ends up initializing the Cloth mode. Thus, the FChaosClothAssetEditorToolkit ends up being the central place for the Cloth Asset Editor setup.
- L57 _public prototype_ `explicit FChaosClothAssetEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L58 _public prototype_ `virtual ~FChaosClothAssetEditorToolkit();`
- L60 _public prototype_ `TSharedPtr<UE::Dataflow::FEngineContext> GetDataflowContext() const;`
- L61 _public prototype_ `const UDataflow* GetDataflow() const;`
- L65 _private member_ `static const FName ClothPreviewTabID;`
- L66 _private member_ `static const FName OutlinerTabID;`
- L67 _private member_ `static const FName PreviewSceneDetailsTabID;`
- L68 _private member_ `static const FName SimulationVisualizationTabID;`
- L71 _private prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject
- L72 _private function_ `virtual bool IsTickable() const override`
- L73 _private prototype_ `virtual TStatId GetStatId() const override;`
- L76 _private prototype_ `virtual FEditorModeID GetEditorModeId() const override;` — FBaseCharacterFXEditorToolkit
- L77 _private prototype_ `virtual void InitializeEdMode(UBaseCharacterFXEditorMode* EdMode) override;`
- L78 _private prototype_ `virtual void CreateEditorModeUILayer() override;`
- L81 _private prototype_ `virtual void CreateWidgets() override;` — FBaseAssetToolkit
- L82 _private prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L83 _private prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L86 _private prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget, int32 ZOrder = INDEX_NONE) override;` — FAssetEditorToolkit
- L87 _private prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;`
- L88 _private prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L89 _private prototype_ `virtual void OnClose() override;`
- L91 _private prototype_ `virtual void PostInitAssetEditor() override;`
- L92 _private prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L93 _private prototype_ `virtual void GetSaveableObjects(TArray<UObject*>& OutObjects) const override;`
- L94 _private prototype_ `virtual bool ShouldReopenEditorForSavedAsset(const UObject* Asset) const override;`
- L95 _private prototype_ `virtual void OnAssetsSaved(const TArray<UObject*>& SavedObjects) override;`
- L96 _private prototype_ `virtual void OnAssetsSavedAs(const TArray<UObject*>& SavedObjects) override;`
- L99 _private function_ `virtual bool IsPrimaryEditor() const override` — IAssetEditorInstance
- L102 _private prototype_ `virtual FText GetToolkitName() const override;` — IToolkit
- L103 _private prototype_ `virtual FName GetToolkitFName() const override;`
- L104 _private prototype_ `virtual FText GetBaseToolkitName() const override;`
- L105 _private prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L106 _private prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L107 _private prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L110 _private prototype_ `virtual void NotifyPreChange(class FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook
- L113 _private prototype_ `UChaosClothAsset* GetAsset() const;` — Return the cloth asset held by the Cloth Editor
- L114 _private prototype_ `UDataflow* GetDataflow();`
- L116 _private prototype_ `TSharedRef<SDockTab> SpawnTab_ClothPreview(const FSpawnTabArgs& Args);`
- L117 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Outliner(const FSpawnTabArgs& Args);`
- L118 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneDetails(const FSpawnTabArgs& Args);`
- L119 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);`
- L120 _private prototype_ `TSharedRef<SDockTab> SpawnTab_NodeDetails(const FSpawnTabArgs& Args);`
- L121 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimulationVisualization(const FSpawnTabArgs& Args);`
- L123 _private prototype_ `void InitDetailsViewPanel();`
- L124 _private prototype_ `void OnFinishedChangingAssetProperties(const FPropertyChangedEvent&);`
- L126 _private prototype_ `void OnClothAssetChanged();`
- L127 _private prototype_ `void InvalidateViews();`
- L130 _private prototype_ `void EvaluateNode(const FDataflowNode* Node, const FDataflowOutput* Output);` — Dataflow
- L131 _private prototype_ `TSharedRef<SDataflowGraphEditor> CreateGraphEditorWidget();`
- L132 _private prototype_ `void ReinitializeGraphEditorWidget();`
- L133 _private prototype_ `TSharedPtr<IStructureDetailsView> CreateNodeDetailsEditorWidget(UObject* ObjectToEdit);`
- L135 _private prototype_ `TSharedPtr<FManagedArrayCollection> GetClothCollectionIfPossible(const TSharedPtr<FDataflowNode> InDataflowNode, const TSharedPtr<UE::Dataflow::FEngineContext> Context);`
- L136 _private prototype_ `TSharedPtr<FManagedArrayCollection> GetInputClothCollectionIfPossible(const TSharedPtr<FDataflowNode> InDataflowNode, const TSharedPtr<UE::Dataflow::FEngineContext> Context);`
- L137 _private prototype_ `TSharedPtr<FDataflowNode> GetSelectedDataflowNode();`
- L138 _private prototype_ `TSharedPtr<const FDataflowNode> GetSelectedDataflowNode() const;`
- L141 _private prototype_ `void OnPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — DataflowEditorActions
- L142 _private prototype_ `bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* GraphNode, FText& OutErrorMessage) const;`
- L143 _private prototype_ `void OnNodeTitleCommitted(const FText& InNewText, ETextCommit::Type InCommitType, UEdGraphNode* GraphNode) const;`
- L144 _private prototype_ `void OnNodeSelectionChanged(const TSet<UObject*>& NewSelection);`
- L145 _private prototype_ `void OnNodeDeleted(const TSet<UObject*>& DeletedNodes);`
- L146 _private prototype_ `void OnNodeSingleClicked(UObject* ClickedNode) const;`
- L149 _private prototype_ `void HandlePackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);` — Delegates
- L152 _private member_ `TSharedPtr<FChaosClothPreviewScene> ClothPreviewScene;` — Scene in which the 3D sim space preview meshes live. Ownership shared with AdvancedPreviewSettingsWidget
- L154 _private member_ `TSharedPtr<class FEditorViewportTabContent> ClothPreviewTabContent;`
- L155 _private member_ `AssetEditorViewportFactoryFunction ClothPreviewViewportDelegate;`
- L156 _private member_ `TSharedPtr<FChaosClothAssetEditor3DViewportClient> ClothPreviewViewportClient;`
- L157 _private member_ `TSharedPtr<FAssetEditorModeManager> ClothPreviewEditorModeManager;`
- L158 _private member_ `TSharedPtr<FClothEditorSimulationVisualization> ClothEditorSimulationVisualization;`
- L160 _private member_ `TSharedPtr<SChaosClothAssetEditorRestSpaceViewport> RestSpaceViewportWidget;`
- L161 _private member_ `TSharedPtr<SChaosClothAssetEditor3DViewport> PreviewViewportWidget;`
- L163 _private member_ `TSharedPtr<SDockTab> PreviewSceneDockTab;`
- L164 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;`
- L166 _private member_ `TSharedPtr<SDockTab> SimulationVisualizationDockTab;`
- L168 _private member_ `TSharedPtr<SClothCollectionOutliner> Outliner;`
- L171 _private member_ `TSharedPtr<UE::Dataflow::FEngineContext> DataflowContext;` — Dataflow
- L172 _private member_ `UE::Dataflow::FTimestamp LastDataflowNodeTimestamp = UE::Dataflow::FTimestamp::Invalid;`
- L173 _private member_ `FDelegateHandle OnNodeInvalidatedDelegateHandle;`
- L174 _private member_ `FGuid SelectedDataflowNodeGuid;`
- L176 _private member_ `static const FName GraphCanvasTabId;`
- L177 _private member_ `TSharedPtr<SDockTab> GraphEditorTab;`
- L178 _private member_ `TSharedPtr<SDataflowGraphEditor> GraphEditor;`
- L180 _private member_ `static const FName NodeDetailsTabId;`
- L181 _private member_ `TSharedPtr<SDockTab> NodeDetailsTab;`
- L182 _private member_ `TSharedPtr<IStructureDetailsView> NodeDetailsEditor;`
- L183 _private member_ `TSharedPtr<FClothSimulationNodeDetailExtender> NodeDetailsExtender;`
- L185 _private member_ `FDelegateHandle OnPackageReloadedDelegateHandle;`
- L187 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FTickCommands) FTickCommands TickCommands;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Chaos` (scope `UE`)
- L23 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Dataflow` (scope `UE`)
- L43 _namespace_ `namespace UE`
- L43 _namespace_ `namespace Chaos` (scope `UE`)
- L43 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L187 _delegate_ `DECLARE_MULTICAST_DELEGATE(FTickCommands) FTickCommands TickCommands;`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothEditorViewportToolbarSections.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Chaos` (scope `UE`)
- L9 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
- L11 _prototype_ `FToolMenuEntry CreateDynamicLightIntensityItem();` (scope `UE::Chaos::ClothAsset`)
- L12 _prototype_ `FToolMenuEntry CreateDynamicSimulationMenuItem();` (scope `UE::Chaos::ClothAsset`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/ClothSimulationNodeDetailExtender.h` (Private)


#### struct `UE::Chaos::ClothAsset::FClothSimulationNodeDetailExtender`  
`struct FClothSimulationNodeDetailExtender : public UE::Dataflow::IDataflowNodeDetailExtension`  
_L9-20_
- inherits: `UE::Dataflow::IDataflowNodeDetailExtension`
- L11 _public prototype_ `FClothSimulationNodeDetailExtender() = default;`
- L12 _public member_ `static const FName Name;`
- L15 _public prototype_ `virtual FName GetName() const override;` — IDataflowNodeDetailExtension
- L18 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;` — IDetailPropertyExtensionHandler
- L19 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Chaos` (scope `UE`)
- L7 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/SClothAnimationScrubPanel.h` (Private)


#### class `SClothAnimationScrubPanel`  
`class SClothAnimationScrubPanel : public SCompoundWidget`  
_L19-72_
- inherits: `SCompoundWidget`
- L30 _private function_ `SLATE_BEGIN_ARGS(SClothAnimationScrubPanel)`
- L31 _private prototype_ `SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TWeakPtr<UE::Chaos::ClothAsset::FChaosClothPreviewScene> InPreviewScene );`
- L37 _private prototype_ `TSharedRef<SWidget> OnCreatePreviewPlaybackModeWidget();`
- L40 _private prototype_ `FReply OnClick_Forward_Step();` — notifiers
- L41 _private prototype_ `FReply OnClick_Forward_End();`
- L42 _private prototype_ `FReply OnClick_Backward_Step();`
- L43 _private prototype_ `FReply OnClick_Backward_End();`
- L44 _private prototype_ `FReply OnClick_Forward();`
- L45 _private prototype_ `FReply OnClick_Backward();`
- L46 _private prototype_ `FReply OnClick_PreviewPlaybackMode();`
- L48 _private prototype_ `void ApplyPlaybackSettings();`
- L50 _private prototype_ `void OnTickPlayback(double InCurrentTime, float InDeltaTime);`
- L52 _private prototype_ `void OnValueChanged(float NewValue);`
- L53 _private prototype_ `void OnBeginSliderMovement();`
- L55 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L56 _private prototype_ `float GetScrubValue() const;`
- L58 _private prototype_ `UAnimSingleNodeInstance* GetPreviewAnimationInstance();`
- L59 _private prototype_ `const UAnimSingleNodeInstance* GetPreviewAnimationInstance() const;`
- L61 _private prototype_ `uint32 GetNumberOfKeys() const;`
- L62 _private prototype_ `float GetSequenceLength() const;`
- L64 _private prototype_ `bool GetDisplayDrag() const;`
- L66 _private member_ `TWeakPtr<UE::Chaos::ClothAsset::FChaosClothPreviewScene> PreviewSceneWeakPtr;`
- L68 _private member_ `TSharedPtr<SScrubControlPanel> ScrubControlPanel;`
- L70 _private member_ `TSharedPtr<SButton> PreviewPlaybackModeButton;`
- L71 _private member_ `EClothPreviewPlaybackMode PreviewPlaybackMode = EClothPreviewPlaybackMode::Looping;`

#### enum `SClothAnimationScrubPanel::EClothPreviewPlaybackMode`  
`enum class EClothPreviewPlaybackMode : int32`  
_L23-28_
- L25 _public enumerator_ `Default`
- L26 _public enumerator_ `Looping`
- L27 _public enumerator_ `PingPong`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/SClothCollectionOutliner.h` (Private)


#### struct `FClothCollectionHeaderData`  
`struct FClothCollectionHeaderData`  
_L11-17_
- L13 _public member_ `TArray<FName> AttributeNames;`
- L16 _public member_ `static const FName ColumnZeroName;` — first column is used to display the numeric index of each element

#### struct `FClothCollectionItem`  
`struct FClothCollectionItem`  
_L19-22_
- L21 _public member_ `TArray<FString> AttributeValues;`

#### class `SClothCollectionOutlinerRow`  
`class SClothCollectionOutlinerRow : public SMultiColumnTableRow<TSharedPtr<const FClothCollectionItem>>`  
_L24-41_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFClothCollectionItem>>`
- L27 _public function_ `SLATE_BEGIN_ARGS(SClothCollectionOutlinerRow)`
- L28 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<const FClothCollectionHeaderData>, HeaderData) SLATE_ARGUMENT(TSharedPtr<const FClothCollectionItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, const TSharedPtr<const FClothCollectionHeaderData>& InHeaderData, const TSharedPtr<const FClothCollectionItem>& InItemToEdit);`
- L35 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — SMultiColumnTableRow
- L39 _private member_ `TSharedPtr<const FClothCollectionHeaderData> HeaderData;`
- L40 _private member_ `TSharedPtr<const FClothCollectionItem> Item;`

#### class `SClothCollectionOutliner`  
`class SClothCollectionOutliner : public SCompoundWidget`  
_L44-83_
- inherits: `SCompoundWidget`
- desc: Data visualizer for FClothCollection. Pulls out all Attribute names and values from a given Cloth Collection with a given Group name and adds them to a table
- L48 _public function_ `SLATE_BEGIN_ARGS(SClothCollectionOutliner)`
- L49 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FManagedArrayCollection>, ClothCollection) SLATE_ARGUMENT(FName, SelectedGroupName) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L55 _public prototype_ `void SetClothCollection(TSharedPtr<FManagedArrayCollection> ClothCollection);`
- L58 _public prototype_ `void SetSelectedGroupName(const FName& SelectedGroupName);` — Changing the selected group name will also automatically rebuild the header and all rows
- L60 _public prototype_ `const FName& GetSelectedGroupName() const;`
- L62 _public prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<const FClothCollectionItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L66 _private member_ `TSharedPtr<FManagedArrayCollection> ClothCollection;`
- L68 _private member_ `TSharedPtr<SComboBox<FName>> SelectedGroupNameComboBox;`
- L69 _private member_ `TArray<FName> ClothCollectionGroupNames;` — Data source for SelectedGroupNameComboBox
- L71 _private member_ `FName SelectedGroupName;`
- L72 _private member_ `FName SavedLastValidGroupName;`
- L74 _private member_ `TSharedPtr<SListView<TSharedPtr<const FClothCollectionItem>>> ListView;`
- L75 _private member_ `TArray<TSharedPtr<const FClothCollectionItem>> ListItems;`
- L77 _private member_ `TSharedPtr<FClothCollectionHeaderData> HeaderData;`
- L78 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L80 _private prototype_ `void RegenerateHeader();`
- L81 _private prototype_ `void RepopulateListView();`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/SClothEditor3DViewport.h` (Private)


#### class `SChaosClothAssetEditor3DViewport`  
`class SChaosClothAssetEditor3DViewport : public SBaseCharacterFXEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L21-65_
- inherits: `SBaseCharacterFXEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- desc: Viewport used for 3D preview in cloth editor. Has a custom toolbar overlay at the top.
- L26 _public function_ `SLATE_BEGIN_ARGS(SChaosClothAssetEditor3DViewport)`
- L27 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, ViewportSize);`
- L28 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FEditorViewportClient>, EditorViewportClient) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, ToolkitCommandList) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);`
- L35 _public prototype_ `virtual void BindCommands() override;` — SAssetEditorViewport
- L36 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L37 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L38 _public prototype_ `virtual bool IsVisible() const override;`
- L40 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L43 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider
- L44 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L45 _public function_ `virtual void OnFloatingButtonClicked() override`
- L51 _private member_ `TSharedPtr<FUICommandList> ToolkitCommandList;` — Use this command list if we want to enable editor-wide command chords/hotkeys. Use SEditorViewport::CommandList if we want command hotkeys to only be active when the mouse is in this viewport.
- L53 _private prototype_ `TWeakPtr<UE::Chaos::ClothAsset::FChaosClothPreviewScene> GetPreviewScene();`
- L54 _private prototype_ `TWeakPtr<const UE::Chaos::ClothAsset::FChaosClothPreviewScene> GetPreviewScene() const;`
- L56 _private prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L58 _private prototype_ `FText GetViewportDisplayString() const;`
- L60 _private prototype_ `float GetViewMinInput() const;`
- L61 _private prototype_ `float GetViewMaxInput() const;`
- L62 _private prototype_ `EVisibility GetAnimControlVisibility() const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Chaos` (scope `UE`)
- L12 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/SClothEditorAdvancedPreviewDetailsTab.h` (Private)


#### class `SChaosClothEditorAdvancedPreviewDetailsTab`  
`class SChaosClothEditorAdvancedPreviewDetailsTab : public SAdvancedPreviewDetailsTab`  
_L10-20_
- inherits: `SAdvancedPreviewDetailsTab`
- desc: Custom subclass of SAdvancedPreviewDetailsTab that allows invalidating the cached state of the SettingsView when the preview scene changes
- L14 _public prototype_ `SChaosClothEditorAdvancedPreviewDetailsTab();`
- L19 _private member_ `FDelegateHandle PropertyChangedDelegateHandle;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Private/ChaosClothAsset/SClothEditorRestSpaceViewport.h` (Private)


#### class `SChaosClothAssetEditorRestSpaceViewport`  
`class SChaosClothAssetEditorRestSpaceViewport : public SBaseCharacterFXEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L14-45_
- inherits: `SBaseCharacterFXEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L18 _public function_ `SLATE_BEGIN_ARGS(SChaosClothAssetEditorRestSpaceViewport)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, ViewportSize);`
- L20 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<UE::Chaos::ClothAsset::FChaosClothEditorRestSpaceViewportClient>, RestSpaceViewportClient) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);`
- L26 _public prototype_ `virtual void BindCommands() override;` — SEditorViewport
- L27 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L28 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L29 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L30 _public prototype_ `virtual bool IsVisible() const override;`
- L33 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider
- L34 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L35 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L39 _private prototype_ `UChaosClothAssetEditorMode* GetEdMode() const;`
- L41 _private prototype_ `FText GetDisplayString() const;`
- L43 _private member_ `TSharedPtr<UE::Chaos::ClothAsset::FChaosClothEditorRestSpaceViewportClient> RestSpaceViewportClient;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Chaos` (scope `UE`)
- L12 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Public/ChaosClothAsset/ChaosClothAssetThumbnailRenderer.h` (Public)
_(no declarations extracted)_

### `Plugins/ChaosClothAssetEditorCore/Source/ChaosClothAssetEditor/Public/ChaosClothAsset/LegacyClothingConverter.h` (Public)


#### struct `UE::Chaos::ClothAsset::FLegacyClothingConverterResult`  
`struct FLegacyClothingConverterResult`  
_L15-23_
- desc: Result of a legacy-to-ChaosClothAsset conversion.
- L18 _public member_ `UChaosClothAsset* CreatedAsset = nullptr;` — Newly created cloth asset; nullptr on failure.
- L20 _public member_ `FString CreatedAssetPath;` — Object path of the created asset, or empty on failure.
- L22 _public member_ `FText ErrorText;` — Populated on failure with the user-visible error.

#### class `UE::Chaos::ClothAsset::FLegacyClothingConverter`  
`class FLegacyClothingConverter`  
_L50-70_
- desc: Converts a legacy UClothingAssetCommon (the cloth asset driven by UChaosClothingSimulationFactory) into a new UChaosClothAsset built from the DF_LegacyClothingAssetTemplate Dataflow template. The new asset's Dataflow graph is baked from the legacy values so it is directly editable as if authored from scratch: - Geometry is one-shot baked: a cloth collection built from the legacy FClothPhysicalMeshData is stored on the new asset as the "ImportedSimClothCollection" Dataflow variable override (and the legacy asset's owning SkeletalMesh as "RenderSkeletalMesh"). The template consumes these via a Get-Variable node -- there is no per-asset import node and no live reference back to the source legacy asset, so the conversion is not re-evaluated on Reimport. - One WeightMapNode is appended per legacy weight map (values rescaled to [0,1] with the consuming Simulation node's Low/High adjusted by LegacyMax). - When the legacy asset has a TetherEndsMask weight map, LongRangeAttachmentsNode is switched into custom-tether generation: two SelectionNodes ("LegacyTetherEnds" for the fixed-end set, "LegacyAllSimVertices3D" for the dynamic-end set) are spliced upstream of LongRangeAttachmentsNode and wired into CustomTetherData[0]. When no TetherEndsMask is present, the template's default wiring (FixedEndSet = MaxDistanceConfig.KinematicVertices3D) is kept. - Scalar UChaosClothConfig / UChaosClothSharedSimConfig values are written onto the existing Simulation* config nodes via UProperty reflecti
- L57 _public prototype_ `static FLegacyClothingConverterResult Convert( const UClothingAssetCommon* SourceAsset, const FString& OutputPackagePath, const FString& AssetName);` — Create a new UChaosClothAsset at OutputPackagePath/AssetName from the legacy template and bake the legacy values onto it.
- L67 _public prototype_ `static FLegacyClothingConverterResult ConvertInto( const UClothingAssetCommon* SourceAsset, UChaosClothAsset* TargetAsset);` — Convert into an existing UChaosClothAsset (mutating it in place). The target's embedded Dataflow is reset to a duplicate of the legacy conversion template, then all legacy values are baked onto the graph + variable overrides as in Convert().

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API CHAOSCLOTHASSETEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Chaos` (scope `UE`)
- L12 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
