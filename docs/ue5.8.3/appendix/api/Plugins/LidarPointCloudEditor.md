# Plugins / LidarPointCloudEditor

- module root: `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor`
- headers: 14; symbols: 392
- symbol kinds: class=45, enum=1, enumerator=3, externvar=1, function=87, member=79, namespace=2, prototype=172, struct=1, variable=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, AssetDefinition, ContentBrowser, Core, CoreUObject, EditorFramework, EditorInteractiveToolsFramework, Engine, InputCore, InteractiveToolsFramework, KismetWidgets, LidarPointCloudRuntime, MainFrame, MeshDescription, Projects, PropertyEditor, RHI, RenderCore, Slate, SlateCore, StaticMeshDescription, StatusBar, ToolMenus, UMG, UnrealEd

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/ActorFactoryLidarPointCloud.h` (Private)


#### class `UActorFactoryLidarPointCloud`  
`class UActorFactoryLidarPointCloud : public UActorFactory`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L19 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L20 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L21 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L22 _private prototype_ `virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/AssetDefinition_LidarPointCloud.h` (Private)


#### class `UAssetDefinition_LidarPointCloud`  
`class UAssetDefinition_LidarPointCloud : public UAssetDefinitionDefault`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L20 _public function_ `virtual bool CanImport() const override`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEdMode.h` (Private)


#### class `ULidarEditorMode`  
`class ULidarEditorMode : public UBaseLegacyWidgetEdMode`  
_L17-35_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode`
- desc: Lidar editor mode
- L22 _public prototype_ `ULidarEditorMode();`
- L24 _public prototype_ `virtual void Enter() override;`
- L25 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;`
- L26 _public prototype_ `virtual void CreateToolkit() override;`
- L27 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L28 _public prototype_ `virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;`
- L29 _public prototype_ `virtual void BindCommands() override;`
- L30 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L31 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L32 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L34 _private prototype_ `void CancelActiveToolAction();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace FLidarEditorModes`
- L10 _externvar_ `extern const FEditorModeID EM_Lidar;` (scope `FLidarEditorModes`)

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEdModeToolkit.h` (Private)


#### class `SLidarEditorWidget`  
`class SLidarEditorWidget : public SCompoundWidget`  
_L16-48_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SLidarEditorWidget)`
- L23 _public prototype_ `void Construct(const FArguments& InArgs);`
- L25 _public prototype_ `bool IsActorSelection() const;`
- L26 _public prototype_ `bool IsPointSelection() const;`
- L27 _public prototype_ `bool IsAnySelection() const;`
- L28 _public function_ `bool IsBrushVisible() const`
- L30 _public function_ `EVisibility GetActorVisibility() const`
- L31 _public function_ `EVisibility GetPointVisibility() const`
- L32 _public function_ `EVisibility GetAnyVisibility() const`
- L33 _public function_ `EVisibility GetBrushVisibility() const`
- L36 _private member_ `float MaxCollisionError = 0.0f;`
- L37 _private member_ `float MaxMeshingError = 0.0f;`
- L38 _private member_ `bool bMergeMeshes = true;`
- L39 _private member_ `bool bRetainTransform = true;`
- L40 _private member_ `int32 NormalsQuality = 40;`
- L41 _private member_ `float NormalsNoiseTolerance = 1.0f;`
- L43 _private member_ `ULidarEditorMode* LidarEditorMode = nullptr;`
- L44 _private member_ `ULidarEditorToolPaintSelection* BrushTool = nullptr;`
- L45 _private member_ `bool bActorSelection = false;`

#### class `FLidarPointCloudEdModeToolkit`  
`class FLidarPointCloudEdModeToolkit : public FModeToolkit`  
_L53-80_
- inherits: `FModeToolkit`
- desc: Public interface to Lidar Edit mode.
- L56 _public function_ `FLidarPointCloudEdModeToolkit()`
- L57 _public prototype_ `~FLidarPointCloudEdModeToolkit();`
- L60 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — Initializes the Lidar mode toolkit
- L63 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L64 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L65 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const override;`
- L66 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L67 _public function_ `virtual bool HasIntegratedToolPalettes() const override`
- L68 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L69 _public prototype_ `virtual FText GetActiveToolMessage() const override;`
- L70 _public function_ `virtual TSharedPtr<SWidget> GetInlineContent() const override`
- L72 _public prototype_ `void SetActiveToolMessage(const FText& Message);`
- L73 _public prototype_ `void SetActorSelection(bool bNewActorSelection);`
- L74 _public prototype_ `void SetBrushTool(ULidarEditorToolPaintSelection* NewBrushTool);`
- L77 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L78 _private member_ `FText ActiveToolMessageCache;`
- L79 _private member_ `TSharedPtr<SLidarEditorWidget> EditorWidget;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace LidarEditorPalletes`
- L13 _variable_ `static const FName Manage(TEXT("Tool` (scope `LidarEditorPalletes`)

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditor.h` (Private)


#### class `FLidarPointCloudEditor`  
`class FLidarPointCloudEditor : public FAssetEditorToolkit, public FGCObject`  
_L19-69_
- inherits: `FAssetEditorToolkit,FGCObject`
- L22 _private member_ `TObjectPtr<ULidarPointCloud> PointCloudBeingEdited;`
- L24 _private member_ `TArray64<FLidarPointCloudPoint*> SelectedPoints;`
- L26 _private member_ `bool bEditMode;`
- L29 _private member_ `TSharedPtr<SLidarPointCloudEditorViewport> Viewport;` — Preview Viewport widget
- L32 _public prototype_ `FLidarPointCloudEditor();`
- L33 _public prototype_ `~FLidarPointCloudEditor();`
- L36 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;` — IToolkit interface
- L37 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L41 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit
- L42 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L43 _public prototype_ `virtual FText GetToolkitName() const override;`
- L44 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L45 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L46 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L48 _public function_ `virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override`
- L49 _public function_ `virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override`
- L53 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L54 _public function_ `virtual FString GetReferencerName() const override`
- L60 _public prototype_ `void InitPointCloudEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class ULidarPointCloud* InitPointCloud);`
- L62 _public function_ `ULidarPointCloud* GetPointCloudBeingEdited() const`
- L64 _public function_ `TSharedPtr<SLidarPointCloudEditorViewport> GetViewport()`
- L68 _private prototype_ `void ExtendToolBar();` — Builds the Point Cloud Editor toolbar.

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditorCommands.h` (Private)


#### class `FLidarPointCloudEditorCommands`  
`class FLidarPointCloudEditorCommands : public TCommands<FLidarPointCloudEditorCommands>`  
_L10-51_
- inherits: `TCommands<FLidarPointCloudEditorCommands>`
- L13 _public function_ `FLidarPointCloudEditorCommands() : TCommands<FLidarPointCloudEditorCommands>( TEXT("LidarPointCloudEditor"),`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — TCommand<> interface
- L27 _public function_ `static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetToolkitCommands()`
- L33 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> SetShowCollision;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> SetShowNodes;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ResetCamera;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> Center;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToolkitSelect;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ToolkitBoxSelection;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ToolkitPolygonalSelection;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ToolkitLassoSelection;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ToolkitPaintSelection;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> ToolktitCancelSelection;`
- L50 _private member_ `TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> ToolkitCommands;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditorHelper.h` (Private)


#### enum `ELidarPointCloudSelectionMode`  
`enum class ELidarPointCloudSelectionMode : uint8`  
_L13-18_
- L15 _public enumerator_ `None`
- L16 _public enumerator_ `Add`
- L17 _public enumerator_ `Subtract`

#### class `FLidarPointCloudEditorHelper`  
`class FLidarPointCloudEditorHelper`  
_L20-68_
- L23 _public prototype_ `static ULidarPointCloud* CreateNewAsset();`
- L25 _public prototype_ `static void AlignSelectionAroundWorldOrigin();`
- L26 _public prototype_ `static void SetOriginalCoordinateForSelection();`
- L27 _public prototype_ `static void CenterSelection();`
- L29 _public prototype_ `static void MergeLidar(ULidarPointCloud* TargetAsset, TArray<ULidarPointCloud*> SourceAssets);`
- L30 _public prototype_ `static void MergeSelectionByData(bool bReplaceSource);`
- L31 _public prototype_ `static void MergeSelectionByComponent(bool bReplaceSource);`
- L33 _public prototype_ `static void BuildCollisionForSelection();`
- L34 _public prototype_ `static void SetCollisionErrorForSelection(float Error);`
- L35 _public prototype_ `static void RemoveCollisionForSelection();`
- L37 _public prototype_ `static void MeshSelected(bool bMeshByPoints, float CellSize, bool bMergeMeshes, bool bRetainTransform);`
- L39 _public prototype_ `static void CalculateNormalsForSelection();`
- L40 _public prototype_ `static void SetNormalsQuality(int32 Quality, float NoiseTolerance);`
- L42 _public prototype_ `static void SelectPointsByConvexVolume(const FConvexVolume& ConvexVolume, ELidarPointCloudSelectionMode SelectionMode);`
- L43 _public prototype_ `static void SelectPointsBySphere(FSphere Sphere, ELidarPointCloudSelectionMode SelectionMode);`
- L44 _public prototype_ `static void HideSelected();`
- L45 _public prototype_ `static void DeleteSelected();`
- L46 _public prototype_ `static void InvertSelection();`
- L47 _public prototype_ `static void ClearSelection();`
- L49 _public prototype_ `static void InvertActorSelection();`
- L50 _public prototype_ `static void ClearActorSelection();`
- L52 _public prototype_ `static void ResetVisibility();`
- L53 _public prototype_ `static void DeleteHidden();`
- L54 _public prototype_ `static void Extract();`
- L55 _public prototype_ `static void ExtractAsCopy();`
- L56 _public prototype_ `static void CalculateNormals();`
- L58 _public prototype_ `static FConvexVolume BuildConvexVolumeFromCoordinates(FVector2d Start, FVector2d End, FEditorViewportClient* ViewportClient = nullptr);`
- L59 _public prototype_ `static TArray<FConvexVolume> BuildConvexVolumesFromPoints(TArray<FVector2d> Points, FEditorViewportClient* ViewportClient = nullptr);`
- L60 _public prototype_ `static FLidarPointCloudRay MakeRayFromScreenPosition(FVector2d Position, FEditorViewportClient* ViewportClient = nullptr);`
- L62 _public prototype_ `static bool RayTracePointClouds(const FLidarPointCloudRay& Ray, float RadiusMulti, FVector3f& OutHitLocation);`
- L64 _public prototype_ `static bool IsPolygonSelfIntersecting(const TArray<FVector2D>& Points, bool bAllowLooping);`
- L66 _public prototype_ `static bool AreLidarActorsSelected();`
- L67 _public prototype_ `static bool AreLidarPointsSelected();`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditorTools.h` (Private)


#### class `ULidarEditorToolBase`  
`class ULidarEditorToolBase : public UInteractiveTool`  
_L17-28_
- reflection: `UCLASS()`
- inherits: `UInteractiveTool`
- L21 _public prototype_ `virtual void Setup() override;`
- L22 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions()`
- L23 _public prototype_ `virtual FText GetToolMessage() const;`
- L24 _public function_ `virtual bool IsActorSelection() const`
- L27 _public member_ `TObjectPtr<UInteractiveToolPropertySet> ToolActions = nullptr;` — `UPROPERTY()`

#### class `ULidarEditorToolBuilderBase`  
`class ULidarEditorToolBuilderBase : public UInteractiveToolWithToolTargetsBuilder`  
_L31-38_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L36 _public function_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override`
- L37 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarEditorToolClickDragBase`  
`class ULidarEditorToolClickDragBase : public ULidarEditorToolBase, public IClickDragBehaviorTarget, public IHoverBehaviorTarget, public IInteractiveToolNestedAcceptCancelAPI`  
_L41-85_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase,IClickDragBehaviorTarget,IHoverBehaviorTarget,IInteractiveToolNestedAcceptCancelAPI`
- L50 _public prototype_ `virtual void Setup() override;`
- L51 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L53 _public function_ `virtual bool IsActorSelection() const override`
- L56 _public function_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override` — IClickDragBehaviorTarget implementation
- L57 _public function_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override`
- L58 _public function_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override`
- L59 _public function_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override`
- L60 _public function_ `virtual void OnTerminateDragSequence() override`
- L63 _public function_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override` — IHoverBehaviorTarget implementation
- L64 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L65 _public function_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override`
- L66 _public function_ `virtual void OnEndHover() override`
- L67 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L70 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI implementation
- L71 _public function_ `virtual bool CanCurrentlyNestedCancel() override`
- L72 _public function_ `virtual bool ExecuteNestedCancelCommand() override`
- L75 _public member_ `TObjectPtr<UClickDragInputBehavior> ClickDragBehavior = nullptr;` — `UPROPERTY()`
- L78 _public member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior = nullptr;` — `UPROPERTY()`
- L81 _protected member_ `FViewCameraState CameraState;`
- L83 _protected member_ `bool bShiftToggle = false;`
- L84 _protected member_ `bool bCtrlToggle = false;`

#### class `ULidarEditorToolBuilderSelect`  
`class ULidarEditorToolBuilderSelect : public ULidarEditorToolBuilderBase`  
_L90-93_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`

#### class `ULidarToolActionsAlign`  
`class ULidarToolActionsAlign : public UInteractiveToolPropertySet`  
_L96-109_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L102 _public prototype_ `void AlignAroundWorldOrigin();` — `UFUNCTION(CallInEditor, Category = Actions)`
- L105 _public prototype_ `void AlignAroundOriginalCoordinates();` — `UFUNCTION(CallInEditor, Category = Actions)`
- L108 _public prototype_ `void ResetAlignment();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `ULidarEditorToolAlign`  
`class ULidarEditorToolAlign : public ULidarEditorToolBase`  
_L112-117_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase`
- L116 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`

#### class `ULidarEditorToolBuilderAlign`  
`class ULidarEditorToolBuilderAlign : public ULidarEditorToolBuilderBase`  
_L120-125_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L124 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsMerge`  
`class ULidarToolActionsMerge : public UInteractiveToolPropertySet`  
_L128-141_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L134 _public member_ `bool bReplaceSourceActorsAfterMerging = false;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L137 _public prototype_ `void MergeActors();` — `UFUNCTION(CallInEditor, Category = Actions)`
- L140 _public prototype_ `void MergeData();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `ULidarEditorToolMerge`  
`class ULidarEditorToolMerge : public ULidarEditorToolBase`  
_L144-149_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase`
- L148 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`

#### class `ULidarEditorToolBuilderMerge`  
`class ULidarEditorToolBuilderMerge : public ULidarEditorToolBuilderBase`  
_L152-157_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L156 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsCollision`  
`class ULidarToolActionsCollision : public UInteractiveToolPropertySet`  
_L160-173_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L166 _public member_ `float OverrideMaxCollisionError = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "2000", ClampMin = "0"))`
- L169 _public prototype_ `void BuildCollision();` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "(Re-)Build Collision"))`
- L172 _public prototype_ `void RemoveCollision();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `ULidarEditorToolCollision`  
`class ULidarEditorToolCollision : public ULidarEditorToolBase`  
_L176-181_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase`
- L180 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`

#### class `ULidarEditorToolBuilderCollision`  
`class ULidarEditorToolBuilderCollision : public ULidarEditorToolBuilderBase`  
_L184-189_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L188 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsMeshing`  
`class ULidarToolActionsMeshing : public UInteractiveToolPropertySet`  
_L192-210_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L199 _public member_ `float MaxMeshingError = 0;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (UIMin = "0", UIMax = "2000", ClampMin = "0"))` — Max error around the meshed areas. Leave at 0 for max quality
- L202 _public member_ `bool bMergeMeshes = true;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L206 _public member_ `bool bRetainTransform = true;` — `UPROPERTY(EditAnywhere, Category = Options, meta=(EditCondition="!bMergeMeshes"))` — If not merging meshes, this will retain the transform of the original cloud
- L209 _public prototype_ `void BuildStaticMesh();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `ULidarEditorToolMeshing`  
`class ULidarEditorToolMeshing : public ULidarEditorToolBase`  
_L213-218_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase`
- L217 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`

#### class `ULidarEditorToolBuilderMeshing`  
`class ULidarEditorToolBuilderMeshing : public ULidarEditorToolBuilderBase`  
_L221-226_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L225 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsNormals`  
`class ULidarToolActionsNormals : public UInteractiveToolPropertySet`  
_L229-248_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L236 _public member_ `int32 Quality = 40;` — `UPROPERTY(EditAnywhere, Category = "Options", meta = (ClampMin = "1", ClampMax = "100"))` — Higher values will generally result in more accurate calculations, at the expense of time
- L244 _public member_ `float NoiseTolerance = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ClampMin = "0.0"))` — Higher values are less susceptible to noise, but will most likely lose finer details, especially around hard edges. Lower values retain more detail, at the expense of time. NOTE: setting this too low will cause visual artifacts and geometry holes in noisier datasets.
- L247 _public prototype_ `void CalculateNormals();` — `UFUNCTION(CallInEditor, Category = Actions, meta = (DisplayName = "(Re-)Build Normals"))`

#### class `ULidarEditorToolNormals`  
`class ULidarEditorToolNormals : public ULidarEditorToolBase`  
_L251-256_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBase`
- L255 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`

#### class `ULidarEditorToolBuilderNormals`  
`class ULidarEditorToolBuilderNormals : public ULidarEditorToolBuilderBase`  
_L259-264_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L263 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsSelection`  
`class ULidarToolActionsSelection : public UInteractiveToolPropertySet`  
_L267-324_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L273 _public prototype_ `void ClearSelection();` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayName = "Clear"))`
- L276 _public prototype_ `void InvertSelection();` — `UFUNCTION(CallInEditor, Category = Selection, meta = (DisplayName = "Invert"))`
- L279 _public prototype_ `void DeleteSelected();` — `UFUNCTION(CallInEditor, Category = Cleanup)`
- L282 _public prototype_ `void DeleteHidden();` — `UFUNCTION(CallInEditor, Category = Cleanup)`
- L285 _public prototype_ `void HideSelected();` — `UFUNCTION(CallInEditor, Category = Cleanup)`
- L288 _public prototype_ `void ResetVisibility();` — `UFUNCTION(CallInEditor, Category = Cleanup)`
- L292 _public member_ `int32 Quality = 40;` — `UPROPERTY(EditAnywhere, Category = "Normals", meta = (ClampMin = "1", ClampMax = "100"))` — Higher values will generally result in more accurate calculations, at the expense of time
- L300 _public member_ `float NoiseTolerance = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normals", meta = (ClampMin = "0.0"))` — Higher values are less susceptible to noise, but will most likely lose finer details, especially around hard edges. Lower values retain more detail, at the expense of time. NOTE: setting this too low will cause visual artifacts and geometry holes in noisier datasets.
- L303 _public prototype_ `void CalculateNormals();` — `UFUNCTION(CallInEditor, Category = Normals)`
- L306 _public prototype_ `void Extract();` — `UFUNCTION(CallInEditor, Category = "Merge & Extract")`
- L309 _public prototype_ `void ExtractAsCopy();` — `UFUNCTION(CallInEditor, Category = "Merge & Extract")`
- L313 _public member_ `float MaxMeshingError = 0;` — `UPROPERTY(EditAnywhere, Category = Meshing, meta = (UIMin = "0", UIMax = "2000", ClampMin = "0"))` — Max error around the meshed areas. Leave at 0 for max quality
- L316 _public member_ `bool bMergeMeshes = true;` — `UPROPERTY(EditAnywhere, Category = Meshing)`
- L320 _public member_ `bool bRetainTransform = true;` — `UPROPERTY(EditAnywhere, Category = Meshing, meta=(EditCondition="!bMergeMeshes"))` — If not merging meshes, this will retain the transform of the original cloud
- L323 _public prototype_ `void BuildStaticMesh();` — `UFUNCTION(CallInEditor, Category = Meshing, meta = (DisplayName = "Create Static Mesh"))`

#### class `ULidarEditorToolSelectionBase`  
`class ULidarEditorToolSelectionBase : public ULidarEditorToolClickDragBase`  
_L327-351_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolClickDragBase`
- L331 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L332 _public prototype_ `virtual TArray<FConvexVolume> GetSelectionConvexVolumes();`
- L333 _public prototype_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override;`
- L334 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L335 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L336 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L337 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L338 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L339 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L340 _public prototype_ `virtual FText GetToolMessage() const override;`
- L341 _public prototype_ `virtual FLinearColor GetHUDColor();`
- L342 _public prototype_ `virtual void FinalizeSelection();`
- L344 _public function_ `virtual void PostCurrentMousePosChanged()`
- L345 _public prototype_ `virtual ELidarPointCloudSelectionMode GetSelectionMode() const;`
- L348 _protected member_ `FVector2d CurrentMousePos;`
- L349 _protected member_ `TArray<FVector2d> Clicks;`
- L350 _protected member_ `bool bSelecting;`

#### class `ULidarEditorToolBoxSelection`  
`class ULidarEditorToolBoxSelection : public ULidarEditorToolSelectionBase`  
_L354-362_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolSelectionBase`
- L358 _public prototype_ `virtual TArray<FConvexVolume> GetSelectionConvexVolumes() override;`
- L359 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L360 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L361 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`

#### class `ULidarEditorToolBuilderBoxSelection`  
`class ULidarEditorToolBuilderBoxSelection : public ULidarEditorToolBuilderBase`  
_L365-370_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L369 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarEditorToolPolygonalSelection`  
`class ULidarEditorToolPolygonalSelection : public ULidarEditorToolSelectionBase`  
_L373-383_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolSelectionBase`
- L377 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L378 _public prototype_ `virtual FLinearColor GetHUDColor() override;`
- L379 _public prototype_ `virtual void PostCurrentMousePosChanged() override;`
- L382 _private prototype_ `bool IsWithinSnap();`

#### class `ULidarEditorToolBuilderPolygonalSelection`  
`class ULidarEditorToolBuilderPolygonalSelection : public ULidarEditorToolBuilderBase`  
_L386-391_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L390 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarEditorToolLassoSelection`  
`class ULidarEditorToolLassoSelection : public ULidarEditorToolSelectionBase`  
_L394-401_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolSelectionBase`
- L398 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L399 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L400 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`

#### class `ULidarEditorToolBuilderLassoSelection`  
`class ULidarEditorToolBuilderLassoSelection : public ULidarEditorToolBuilderBase`  
_L404-409_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L408 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

#### class `ULidarToolActionsPaintSelection`  
`class ULidarToolActionsPaintSelection : public ULidarToolActionsSelection`  
_L412-419_
- reflection: `UCLASS()`
- inherits: `ULidarToolActionsSelection`
- L418 _public member_ `float BrushRadius = 250;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = "0", UIMax = "8196", ClampMin = "0", DisplayPriority = 1))`

#### class `ULidarEditorToolPaintSelection`  
`class ULidarEditorToolPaintSelection : public ULidarEditorToolSelectionBase`  
_L422-445_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolSelectionBase`
- L426 _public prototype_ `virtual void Setup() override;`
- L427 _public function_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override`
- L428 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L429 _public prototype_ `virtual void PostCurrentMousePosChanged() override;`
- L430 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L431 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L432 _public function_ `virtual TObjectPtr<UInteractiveToolPropertySet> CreateToolActions() override`
- L433 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L436 _private prototype_ `void Paint();`
- L439 _public member_ `float BrushRadius;`
- L442 _private member_ `FVector3f HitLocation;`
- L443 _private member_ `float LastHitDistance;`
- L444 _private member_ `bool bHasHit;`

#### class `ULidarEditorToolBuilderPaintSelection`  
`class ULidarEditorToolBuilderPaintSelection : public ULidarEditorToolBuilderBase`  
_L448-453_
- reflection: `UCLASS()`
- inherits: `ULidarEditorToolBuilderBase`
- L452 _public function_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditorViewport.h` (Private)


#### class `SLidarPointCloudEditorViewport`  
`class SLidarPointCloudEditorViewport : public SEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider`  
_L22-117_
- inherits: `SEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider`
- desc: PointCloud Editor Preview viewport widget
- L25 _public function_ `SLATE_BEGIN_ARGS(SLidarPointCloudEditorViewport)`
- L26 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FLidarPointCloudEditor>, PointCloudEditor) SLATE_ARGUMENT(ULidarPointCloud*, ObjectToEdit) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `SLidarPointCloudEditorViewport();`
- L32 _public prototype_ `~SLidarPointCloudEditorViewport();`
- L35 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L36 _public function_ `virtual FString GetReferencerName() const override`
- L42 _public prototype_ `void RefreshViewport();`
- L44 _public prototype_ `void ResetCamera();`
- L47 _public member_ `TObjectPtr<ULidarPointCloudComponent> PreviewCloudComponent;` — Component for the preview point cloud.
- L54 _public prototype_ `void SetPreviewCloud(ULidarPointCloud* InPointCloud);` — Sets up the point cloud that the Point Cloud editor is viewing. @param	InPointCloud		The point cloud being viewed in the editor.
- L57 _public function_ `void SetParentTab(TSharedRef<SDockTab> InParentTab)` — Set the parent tab of the viewport for determining visibility
- L71 _public prototype_ `void PopulateOverlayText(const TArray<FOverlayTextItem>& TextItems);` — Specifies an array of text items which will be added to the viewport overlay
- L74 _public function_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override` — ICommonEditorViewportToolbarInfoProvider interface
- L75 _public function_ `virtual TSharedPtr<FExtender> GetExtenders() const override`
- L76 _public function_ `virtual void OnFloatingButtonClicked() override`
- L79 _public function_ `TSharedPtr<FLidarPointCloudEditorViewportClient> GetEditorViewportClient()`
- L83 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L84 _protected function_ `virtual EVisibility OnGetViewportContentVisibility() const override`
- L85 _protected prototype_ `virtual void BindCommands() override;`
- L86 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L87 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L91 _private prototype_ `virtual bool IsVisible() const override;` — Determines the visibility of the viewport.
- L95 _private member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L98 _private member_ `TWeakPtr<FLidarPointCloudEditor> PointCloudEditorPtr;` — Pointer back to the PointCloud editor tool that owns us
- L101 _private member_ `FPreviewScene PreviewScene;` — The scene for this viewport.
- L104 _private member_ `TSharedPtr<FLidarPointCloudEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L107 _private member_ `TObjectPtr<ULidarPointCloud> PointCloud;` — Point Cloud being edited
- L110 _private member_ `EViewModeIndex CurrentViewMode;` — The currently selected view mode.
- L113 _private member_ `TSharedPtr<SVerticalBox> OverlayTextVerticalBox;` — Pointer to the vertical box into which the overlay text items are added
- L116 _private member_ `TSharedPtr<SBorder> OverlayTextBackground;` — Pointer to the background of the overlay text

#### struct `SLidarPointCloudEditorViewport::FOverlayTextItem`  
`struct FOverlayTextItem`  
_L60-68_
- desc: Struct defining the text and its style of each item in the overlay widget
- L62 _public function_ `explicit FOverlayTextItem(const FText& InText, const FName& InStyle = "TextBlock.ShadowedText") : Text(InText), Style(InStyle)`
- L66 _public member_ `FText Text;`
- L67 _public member_ `FName Style;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudEditorViewportClient.h` (Private)


#### class `FLidarPointCloudEditorViewportClient`  
`class FLidarPointCloudEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FLidarPointCloudEditorViewportClient>`  
_L20-64_
- inherits: `FEditorViewportClient,TSharedFromThis<FLidarPointCloudEditorViewportClient>`
- desc: Viewport Client for the preview viewport
- L23 _public prototype_ `FLidarPointCloudEditorViewportClient(TWeakPtr<FLidarPointCloudEditor> InPointCloudEditor, const TSharedRef<SLidarPointCloudEditorViewport>& InPointCloudEditorViewport, FPreviewScene* InPreviewScene, ULidarPointCloudComponent* InPreviewPointCloudComponent);`
- L24 _public prototype_ `~FLidarPointCloudEditorViewportClient();`
- L27 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;` — FEditorViewportClient interface
- L28 _public function_ `virtual bool InputWidgetDelta(FViewport* InViewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale) override`
- L29 _public function_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge) override`
- L30 _public function_ `virtual void TrackingStopped() override`
- L31 _public function_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override`
- L32 _public function_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override`
- L33 _public function_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override`
- L34 _public function_ `virtual bool CanCycleWidgetMode() const override`
- L35 _public function_ `virtual FVector GetWidgetLocation() const override`
- L36 _public function_ `virtual FMatrix GetWidgetCoordSystem() const override`
- L37 _public function_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override`
- L38 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L40 _public prototype_ `void ResetCamera();`
- L43 _public prototype_ `void ToggleShowNodes();` — Callback for toggling the nodes show flag.
- L46 _public prototype_ `bool IsSetShowNodesChecked() const;` — Callback for checking the nodes show flag.
- L50 _protected prototype_ `virtual void PerspectiveCameraMoved() override;` — FEditorViewportClient interface
- L53 _protected prototype_ `void SetAdvancedShowFlagsForScene(const bool bAdvancedShowFlags);` — Used to (re)-set the viewport show flags related to post processing
- L57 _private member_ `TWeakObjectPtr<ULidarPointCloudComponent> PointCloudComponent;` — Component for the point cloud.
- L60 _private member_ `TWeakPtr<FLidarPointCloudEditor> PointCloudEditorPtr;` — Pointer back to the PointCloud editor tool that owns us
- L63 _private member_ `TWeakPtr<SLidarPointCloudEditorViewport> PointCloudEditorViewportPtr;` — Pointer back to the PointCloudEditor viewport control that owns us

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudFactory.h` (Private)


#### class `ULidarPointCloudFactory`  
`class ULidarPointCloudFactory : public UFactory, public FReimportHandler`  
_L12-37_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- L17 _private member_ `TSharedPtr<struct FLidarPointCloudImportSettings> ImportSettings;`
- L18 _private member_ `bool bImportingAll;`
- L21 _public prototype_ `ULidarPointCloudFactory();`
- L24 _public prototype_ `virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override;`
- L25 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L26 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L27 _public prototype_ `virtual bool DoesSupportClass(UClass* Class) override;`
- L28 _public function_ `virtual bool FactoryCanImport(const FString& Filename) override`
- L29 _public function_ `virtual FText GetDisplayName() const override`
- L33 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L34 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L35 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudImportUI.h` (Private)


#### class `SLidarPointCloudOptionWindow`  
`class SLidarPointCloudOptionWindow : public SCompoundWidget`  
_L14-91_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SLidarPointCloudOptionWindow) : _ImportUI(nullptr) , _WidgetWindow() , _FullPath() , _IsReimport() , _MaxWindowHeight(0.0f) , _MaxWindowWidth(0.0f)`
- L35 _public member_ `bool bCancelled;`
- L38 _private member_ `bool bImportAll;`
- L39 _private member_ `TSharedPtr<FLidarPointCloudImportSettings> ImportUI;`
- L40 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L41 _private member_ `TSharedPtr<SButton> ImportButton;`
- L42 _private member_ `TSharedPtr<SButton> ImportAllButton;`
- L43 _private member_ `TSharedPtr<SButton> CancelButton;`
- L46 _public function_ `SLidarPointCloudOptionWindow() : bCancelled(true), bImportAll(false), ImportUI(nullptr)`
- L48 _public prototype_ `void Construct(const FArguments& InArgs);`
- L49 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L51 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L61 _public function_ `FReply OnImport()`
- L71 _public function_ `FReply OnImportAll()`
- L77 _public function_ `FReply OnCancel()`
- L87 _public function_ `bool ShouldImportAll()`
- L90 _private function_ `bool CanImport() const`

#### class `FLidarPointCloudImportUI`  
`class FLidarPointCloudImportUI`  
_L93-107_
- L100 _public prototype_ `static TSharedPtr<FLidarPointCloudImportSettings> ShowImportDialog(const FString& Filename, bool bIsReimport);` — This version queries the default ImportSettings based on the Filename provided Returns the ImportSettings object
- L106 _public prototype_ `static bool ShowImportDialog(TSharedPtr<FLidarPointCloudImportSettings> ImportSettings, bool bIsReimport);` — This version uses existing ImportSettings Returns true if ImportSettings are valid and the action has been accepted by the user

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Private/LidarPointCloudStyle.h` (Private)


#### class `FLidarPointCloudStyle`  
`class FLidarPointCloudStyle`  
_L9-22_
- L12 _public prototype_ `static void Initialize();`
- L14 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _private member_ `static TSharedPtr<class FSlateStyleSet> StyleSet;`

### `Plugins/Enterprise/LidarPointCloud/Source/LidarPointCloudEditor/Public/ILidarPointCloudEditorModule.h` (Public)


#### class `ILidarPointCloudEditorModule`  
`class ILidarPointCloudEditorModule : public IModuleInterface`  
_L13-40_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L17 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetMenuExtensibilityManager()`
- L18 _public function_ `virtual TSharedPtr<class FExtensibilityManager> GetToolBarExtensibilityManager()`
- L26 _public function_ `static inline ILidarPointCloudEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L36 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
