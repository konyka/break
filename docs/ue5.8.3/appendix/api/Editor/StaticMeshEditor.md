# Editor / StaticMeshEditor

- module root: `Source/Editor/StaticMeshEditor`
- headers: 15; symbols: 1114
- symbol kinds: class=21, delegate=11, enum=4, enumerator=20, externvar=1, function=67, macro=1, member=253, namespace=2, prototype=721, struct=10, typedef=3
- DynamicallyLoadedModuleNames: ClassViewer, ContentBrowser, MeshReductionInterface, SceneOutliner
- PrivateDependencyModuleNames: AdvancedPreviewScene, ApplicationCore, CommonMenuExtensions, Core, CoreUObject, DesktopPlatform, DesktopWidgets, DetailCustomizations, EditorFramework, EditorInteractiveToolsFramework, EditorSubsystem, Engine, InputCore, InteractiveToolsFramework, Json, JsonUtilities, MeshDescription, MeshUtilities, NaniteUtilities, PhysicsUtilities, PropertyEditor, RHI, RawMesh, RenderCore, Slate, SlateCore, StaticMeshDescription, StatusBar, TargetPlatform, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PrivateIncludePathModuleNames: AssetRegistry, MeshReductionInterface

### `Source/Editor/StaticMeshEditor/Private/SStaticMeshEditorViewport.h` (Private)


#### enum `EStaticMeshEditorAspectRatio`  
`enum class EStaticMeshEditorAspectRatio : int32`  
_L26-37_
- L28 _public enumerator_ `EFree = 0`
- L29 _public enumerator_ `EPlatform = 1`
- L31 _public enumerator_ `E6_13 = 100`
- L32 _public enumerator_ `E13_6`
- L33 _public enumerator_ `E1_1`
- L34 _public enumerator_ `E4_3`
- L35 _public enumerator_ `E16_10`
- L36 _public enumerator_ `E16_9`

#### class `SStaticMeshEditorViewport`  
`class SStaticMeshEditorViewport : public SAssetEditorViewport, public FGCObject, public ICommonEditorViewportToolbarInfoProvider, public IPreviewLODController`  
_L42-266_
- inherits: `SAssetEditorViewport,FGCObject,ICommonEditorViewportToolbarInfoProvider,IPreviewLODController`
- desc: StaticMesh Editor Preview viewport widget
- L45 _public function_ `SLATE_BEGIN_ARGS( SStaticMeshEditorViewport )`
- L46 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<IStaticMeshEditor>, StaticMeshEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `SStaticMeshEditorViewport();`
- L54 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L55 _public function_ `virtual FString GetReferencerName() const override`
- L62 _public prototype_ `void UpdatePreviewSocketMeshes();` — Constructs, destroys, and updates preview mesh components based on the preview static mesh's sockets.
- L64 _public prototype_ `void RefreshViewport();`
- L67 _public member_ `TObjectPtr<UStaticMeshComponent> PreviewMeshComponent;` — Component for the preview static mesh.
- L70 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> SocketPreviewMeshComponents;` — Component for the preview static mesh.
- L77 _public prototype_ `void ForceLODLevel(int32 InForcedLOD);` — Forces a specific LOD level onto the static mesh component. @param	InForcedLOD			The desired LOD to be forced to.
- L86 _public prototype_ `virtual int32 GetCurrentLOD() const override;` — Query LOD level of static mesh component
- L87 _public prototype_ `virtual int32 GetLODCount() const override;`
- L88 _public prototype_ `virtual bool IsLODSelected(int32 LODIndex) const override;`
- L89 _public prototype_ `virtual void SetLODLevel(int32 LODIndex) override;`
- L90 _public prototype_ `virtual void FillLODCommands(TArray<TSharedPtr<FUICommandInfo>>& Commands) override;`
- L91 _public function_ `virtual int32 GetAutoLODStartingIndex() const override`
- L94 _public prototype_ `void OnLODModelChanged();`
- L96 _public prototype_ `void SetCurrentScreenPercentage(float ScreenPercentage);`
- L97 _public prototype_ `float GetScreenPercentageForLOD(int LODIndex);`
- L98 _public prototype_ `int32 GetCurrentMinimumLOD() const;`
- L101 _public prototype_ `UStaticMeshComponent* GetStaticMeshComponent() const;` — Retrieves the static mesh component.
- L108 _public prototype_ `void SetPreviewMesh(UStaticMesh* InStaticMesh);` — Sets up the static mesh that the Static Mesh editor is viewing. @param	InStaticMesh		The static mesh being viewed in the editor.
- L115 _public prototype_ `void UpdatePreviewMesh(UStaticMesh* InStaticMesh, bool bResetCamera=true);` — Updates the preview mesh and other viewport specfic settings that go with it. @param	InStaticMesh		The static mesh being viewed in the editor.
- L118 _public prototype_ `TSet< int32 >& GetSelectedEdges();` — Retrieves the selected edge set.
- L121 _public prototype_ `class FStaticMeshEditorViewportClient& GetViewportClient();` — @return The editor viewport client
- L124 _public function_ `void SetParentTab( TSharedRef<SDockTab> InParentTab )` — Set the parent tab of the viewport for determining visibility
- L139 _public prototype_ `void PopulateOverlayText( const TArrayView<FOverlayTextItem> TextItems );` — Specifies an array of text items which will be added to the viewport overlay
- L142 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider interface
- L143 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L144 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L148 _public function_ `TSharedRef<FAdvancedPreviewScene> GetPreviewScene()` — Returns the preview scene being renderd in the viewport
- L150 _public function_ `TSharedPtr<SOverlay> GetViewportOverlay()`
- L154 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L155 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L156 _protected prototype_ `virtual void BindCommands() override;`
- L157 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L158 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L159 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L160 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L165 _public prototype_ `void SetViewModeVertexColor();` — Callback for toggling the vertex color show flag.
- L168 _public prototype_ `bool IsInViewModeVertexColorChecked() const;` — Callback for checking the vertex color show flag.
- L171 _public prototype_ `void SetViewModeWireframe();` — Callback for toggling the wireframe mode.
- L174 _public prototype_ `bool IsInViewModeWireframeChecked() const;` — Callback for checking the wireframe flag.
- L179 _private prototype_ `virtual bool IsVisible() const override;` — Determines the visibility of the viewport.
- L182 _private prototype_ `void SetViewModeVertexColorImplementation(bool bValue);` — Implementation of the SetViewModeVertexColor, used to apply the vertex color show flag.
- L185 _private prototype_ `void SetViewModeVertexColorSubImplementation(bool bValue);` — Applies the vertex color show flag only.
- L188 _private prototype_ `void SetViewModePhysicalMaterialMasks();` — Callback for toggling the physical material mask show flag.
- L191 _private prototype_ `void SetViewModePhysicalMaterialMasksImplementation(bool bValue);` — Implementation of the SetViewModeVertexColor, used to apply the physical material mask show flag.
- L194 _private prototype_ `void SetViewModePhysicalMaterialMasksSubImplementation(bool bValue);` — Applies the physical material mask show flag only.
- L197 _private prototype_ `bool IsInViewModePhysicalMaterialMasksChecked() const;` — Callback for checking the physical material mask show flag.
- L200 _private prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — Callback for updating preview socket meshes if the static mesh or socket has been modified.
- L203 _private prototype_ `bool PreviewComponentSelectionOverride(const UPrimitiveComponent* InComponent) const;` — Override for preview component selection to inform the editor we consider it selected.
- L205 _private prototype_ `void ToggleShowNaniteFallback();`
- L207 _private prototype_ `bool IsShowNaniteFallbackChecked() const;`
- L209 _private prototype_ `bool IsShowNaniteFallbackVisible() const;`
- L211 _private prototype_ `void ToggleShowDistanceField();`
- L213 _private prototype_ `bool IsShowDistanceFieldChecked() const;`
- L215 _private prototype_ `bool IsShowDistanceFieldVisible() const;`
- L217 _private prototype_ `void ToggleShowRayTracingFallback();`
- L219 _private prototype_ `bool IsShowRayTracingFallbackChecked() const;`
- L221 _private prototype_ `bool IsShowRayTracingFallbackVisible() const;`
- L223 _private prototype_ `void SetFloorAndEnvironmentVisibility(bool bVisible);`
- L225 _private prototype_ `void SetAspectRatioState(EStaticMeshEditorAspectRatio TestAspectRatio);`
- L227 _private prototype_ `bool IsAspectRatio(EStaticMeshEditorAspectRatio TestAspectRatio) const;`
- L232 _private member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L235 _private member_ `TWeakPtr<IStaticMeshEditor> StaticMeshEditorPtr;` — Pointer back to the StaticMesh editor tool that owns us
- L238 _private member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene;` — The scene for this viewport.
- L241 _private member_ `TSharedPtr<class FStaticMeshEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L244 _private member_ `TObjectPtr<UStaticMesh> StaticMesh;` — Static mesh being edited
- L247 _private member_ `EViewModeIndex CurrentViewMode;` — The currently selected view mode.
- L250 _private member_ `TSharedPtr<SRichTextBlock> OverlayText;` — Pointer to the box into which the overlay text items are added
- L253 _private member_ `TSharedPtr<SStaticMeshLODVisualizerWidget> LODVisualizer;` — Pointer to a LOD visualizer widget to display in the viewport
- L256 _private member_ `float CurrentScreenPercentage = 0.f;` — The current screen percentage occupied by the asset in the viewport
- L259 _private member_ `int32 LODSelection;` — Current LOD Selection where 0 is Auto
- L262 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L265 _private member_ `EStaticMeshEditorAspectRatio CurrentAspectRatioMode = EStaticMeshEditorAspectRatio::EPlatform;` — Current aspect ratio the viewport is set to.

#### struct `SStaticMeshEditorViewport::FOverlayTextItem`  
`struct FOverlayTextItem`  
_L127-136_
- desc: Struct defining the text and its style of each item in the overlay widget
- L129 _public function_ `explicit FOverlayTextItem(const FText& InText, bool bInIsWarning = false, bool bInIsCustomFormat=false) : Text(InText), bIsWarning(bInIsWarning), bIsCustomFormat(bInIsCustomFormat)`
- L133 _public member_ `FText Text;`
- L134 _public member_ `bool bIsWarning;`
- L135 _public member_ `bool bIsCustomFormat;`

### `Source/Editor/StaticMeshEditor/Private/SStaticMeshLODVisualizerWidget.h` (Private)


#### struct `FLODVisualizationData`  
`struct FLODVisualizationData`  
_L10-19_
- L12 _public member_ `float ScreenPercentage = 0.0;`
- L13 _public member_ `TAttribute<float> ActivationPercentage;`
- L14 _public member_ `TAttribute<EVisibility> Visibility;`
- L15 _public member_ `TAttribute<EVisibility> MinimalLODVisibility;`
- L16 _public member_ `TAttribute<FSlateColor> Color;`
- L17 _public member_ `TAttribute<const FSlateBrush*> ActiveBorder;`
- L18 _public member_ `TAttribute<FText> ToolTip;`

#### class `SStaticMeshLODVisualizerWidget`  
`class SStaticMeshLODVisualizerWidget : public SCompoundWidget`  
_L23-73_
- inherits: `SCompoundWidget`
- L27 _public function_ `SLATE_BEGIN_ARGS(SStaticMeshLODVisualizerWidget)`
- L28 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments & InArgs);`
- L33 _public prototype_ `void SetScreenPercentage(float NewScreenPercentageIn);`
- L35 _public prototype_ `void SetLODPercentage(int32 LODIndex, float NewLODPercentageIn);`
- L37 _public prototype_ `void SetNumLODs(int NumLods);`
- L39 _public prototype_ `void SetActiveLOD(int LODIndexIn);`
- L41 _public prototype_ `void SetNaniteEnabled(bool bNaniteEnabledIn);`
- L43 _public prototype_ `void SetNaniteActive(bool bNaniteActiveIn);`
- L45 _public prototype_ `void SetMinimumLOD(int LODIndexIn);`
- L47 _public prototype_ `void SetCurrentPlatform(FString PlatformName);`
- L51 _protected member_ `float ScreenPercentage = 1.f;`
- L52 _protected member_ `int32 NumLODs = 1;`
- L53 _protected member_ `int32 ActiveLOD = 0;`
- L54 _protected member_ `int32 MinimumLOD = 0;`
- L55 _protected member_ `FString CurrentPlatform = "NO`
- L57 _protected member_ `bool bNaniteEnabled = false;`
- L58 _protected member_ `bool bNaniteActive = false;`
- L60 _protected member_ `TSharedPtr<SVerticalBox> LODSlotDisplay;`
- L62 _protected member_ `TAttribute<float> SliderValue;`
- L63 _protected member_ `TAttribute<float> PercentAbove;`
- L64 _protected member_ `TAttribute<float> PercentBelow;`
- L66 _protected member_ `TAttribute<EVisibility> NaniteOverlayVisibility;`
- L68 _protected member_ `TArray<FLODVisualizationData> PerLODData;`
- L70 _protected prototype_ `float ComputeLODSectionFill(int32 LODIndex);`
- L72 _protected prototype_ `bool IsNaniteOverlayActive() const;`

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditor.h` (Private)


#### class `FStaticMeshEditor`  
`class FStaticMeshEditor : public IStaticMeshEditor, public FGCObject, public FEditorUndoClient, public FNotifyHook, public FTickableEditorObject`  
_L43-634_
- inherits: `IStaticMeshEditor,FGCObject,FEditorUndoClient,FNotifyHook,FTickableEditorObject`
- desc: StaticMesh Editor class
- L46 _public function_ `FStaticMeshEditor() : StaticMesh(nullptr) , MinPrimSize(0.5f) , OverlapNudge(10.0f) , CurrentViewedUVChannel(0) , SecondaryToolbarEntry(nullptr) , bDrawNormals(false) , bDrawTangents(false) , bDrawBinormals(false) , bDrawPivots(false) , bDrawVertices(false) , bDrawGrids(false) , bDrawBounds(false) , bDrawSimpleCollisions(false) , bDrawComplexCollisions(false) , bDrawSockets(false) , bDrawWireframes(false) , bDrawVertexColors(false) , bDrawAdditionalData(true)`
- L67 _public prototype_ `~FStaticMeshEditor();`
- L71 _private prototype_ `void InitEditorForStaticMesh(UStaticMesh* ObjectToEdit);` — Initializes the editor to use a static mesh. Should be the first thing called.
- L73 _private prototype_ `virtual void PostInitAssetEditor() override;`
- L74 _private prototype_ `virtual void OnBuildViewportInteractions(UViewportInteractionsBehaviorSource* Source) override;`
- L77 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L78 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L81 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;` — IToolkitHost Interface
- L82 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L91 _public prototype_ `void InitStaticMeshEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UStaticMesh* ObjectToEdit);` — Edits the specified static mesh object @param	Mode					Asset editing mode for this editor (standalone or world-centric) @param	InitToolkitHost			When Mode is WorldCentric, this is the level editor instance to spawn this editor within @param	ObjectToEdit			The static mesh to edit
- L94 _public prototype_ `TSharedRef<class IDetailCustomization> MakeStaticMeshDetails();` — Creates details for a static mesh
- L97 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L98 _public function_ `virtual FString GetReferencerName() const override`
- L105 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L106 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L107 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L110 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L116 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;` — @return Returns the color and opacity to use for the color that appears behind the tab text for this toolkit's tab in world-centric mode.
- L119 _public function_ `virtual UStaticMesh* GetStaticMesh() override` — IStaticMeshEditor interface
- L120 _public prototype_ `virtual UStaticMeshComponent* GetStaticMeshComponent() const override;`
- L122 _public prototype_ `virtual UStaticMeshSocket* GetSelectedSocket() const override;`
- L123 _public prototype_ `virtual TArray<UStaticMeshSocket*> GetSelectedSockets() const override;`
- L124 _public prototype_ `virtual bool HasSelectedSockets() const override;`
- L125 _public prototype_ `virtual void SetSelectedSocket(UStaticMeshSocket* InSelectedSocket) override;`
- L126 _public prototype_ `virtual void AddSelectedSocket(UStaticMeshSocket* InSelectedSocket) override;`
- L127 _public prototype_ `virtual void RemoveSelectedSocket(const UStaticMeshSocket* InSelectedSocket) override;`
- L128 _public prototype_ `virtual void DuplicateSelectedSocket() override;`
- L129 _public prototype_ `virtual void DuplicateSelectedSockets() override;`
- L130 _public prototype_ `virtual void RequestRenameSelectedSocket() override;`
- L132 _public prototype_ `virtual bool IsPrimValid(const FPrimData& InPrimData) const override;`
- L133 _public prototype_ `virtual bool HasSelectedPrims() const override;`
- L134 _public prototype_ `virtual const TArray<FPrimData>& GetSelectedPrims() const override;`
- L135 _public prototype_ `virtual void AddSelectedPrim(const FPrimData& InPrimData, bool bClearSelection) override;`
- L136 _public prototype_ `virtual void RemoveSelectedPrim(const FPrimData& InPrimData) override;`
- L137 _public prototype_ `virtual void RemoveInvalidPrims() override;`
- L138 _public prototype_ `virtual bool IsSelectedPrim(const FPrimData& InPrimData) const override;`
- L139 _public prototype_ `virtual void ClearSelectedPrims() override;`
- L140 _public prototype_ `virtual void DuplicateSelectedPrims(const FVector* InOffset) override;`
- L141 _public prototype_ `virtual int32 CopySelectedPrims() const override;`
- L142 _public prototype_ `virtual int32 PasteCopiedPrims() override;`
- L143 _public prototype_ `virtual void TranslateSelectedPrims(const FVector& InDrag) override;`
- L144 _public prototype_ `virtual void RotateSelectedPrims(const FRotator& InRot) override;`
- L145 _public prototype_ `virtual void ScaleSelectedPrims(const FVector& InScale) override;`
- L146 _public prototype_ `virtual bool CalcSelectedPrimsAABB(FBox &OutBox) const override;`
- L147 _public prototype_ `virtual bool GetLastSelectedPrimTransform(FTransform& OutTransform) const override;`
- L148 _public prototype_ `FTransform GetPrimTransform(const FPrimData& InPrimData) const override;`
- L149 _public prototype_ `void SetPrimTransform(const FPrimData& InPrimData, const FTransform& InPrimTransform) const override;`
- L150 _public prototype_ `bool OverlapsExistingPrim(const FPrimData& InPrimData) const;`
- L152 _public prototype_ `virtual int32 GetNumTriangles(int32 LODLevel = 0) const override;`
- L153 _public prototype_ `virtual int32 GetNumVertices(int32 LODLevel = 0) const override;`
- L154 _public prototype_ `virtual int32 GetNumUVChannels(int32 LODLevel = 0) const override;`
- L156 _public prototype_ `virtual int32 GetCurrentUVChannel() override;`
- L157 _public prototype_ `virtual int32 GetCurrentLODLevel() override;`
- L158 _public prototype_ `virtual int32 GetCurrentLODIndex() override;`
- L160 _public prototype_ `virtual int32 GetCustomData(const int32 Key) const override;`
- L161 _public prototype_ `virtual void SetCustomData(const int32 Key, const int32 CustomData) override;`
- L163 _public prototype_ `virtual void RefreshTool() override;`
- L164 _public prototype_ `virtual void RefreshViewport() override;`
- L165 _public prototype_ `virtual bool IsShowSimpleCollisionChecked() const override;`
- L166 _public prototype_ `virtual void ToggleShowSimpleCollision() override;`
- L167 _public prototype_ `virtual void DoDecomp(uint32 InHullCount, int32 InMaxHullVerts, uint32 InHullPrecision) override;`
- L169 _public prototype_ `virtual TSet< int32 >& GetSelectedEdges() override;`
- L171 _public prototype_ `virtual FEditorViewportClient& GetViewportClient() override;`
- L173 _public prototype_ `virtual void SetSecondaryToolbarDisplayName(FText DisplayName) override;`
- L177 _public prototype_ `void ExtendMenu();` — Extends the toolbar menu to include static mesh editor options
- L180 _public prototype_ `virtual void RegisterOnPostUndo(const FOnPostUndo& Delegate) override;` — Registers a delegate to be called after an Undo operation
- L183 _public prototype_ `virtual void UnregisterOnPostUndo(SWidget* Widget) override;` — Unregisters a delegate to be called after an Undo operation
- L186 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — From FNotifyHook
- L189 _public prototype_ `virtual EViewModeIndex GetViewMode() const override;` — Get the active view mode
- L191 _public function_ `virtual void RegisterOnSelectedLODChanged(const FOnSelectedLODChanged &Delegate, bool UnregisterOnRefresh) override`
- L203 _public function_ `virtual void UnRegisterOnSelectedLODChanged(FDelegateUserObject Thing) override`
- L209 _public function_ `virtual void BroadcastOnSelectedLODChanged() override`
- L219 _public function_ `virtual bool IsTickableInEditor() const final` — For asynchronous convex decomposition support, this class is tickable in the editor to be able to confirm that the process is completed
- L225 _public function_ `virtual ETickableTickType GetTickableTickType() const final` — This is a tickable class
- L233 _public prototype_ `virtual void Tick(float DeltaTime) final;` — Performs the main 'tick' operation on this class.  The 'tick' step checks to see if there is currently an active asynchronous convex decomopsition task running and, if so, checks to see if it is completed and, if so, gathers the results and releases the interface
- L236 _public prototype_ `virtual TStatId GetStatId() const final;` — Returns the stat ID for this tickable class
- L239 _public prototype_ `void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE) override;` — Add a widget to the StaticMeshViewport's ViewportOverlay
- L242 _public prototype_ `void RemoveViewportOverlayWidget(TSharedRef<SWidget> InViewportOverlayWidget) override;` — Remove a widget from the StaticMeshViewport's ViewportOverlay
- L244 _public prototype_ `void CreateEditorModeManager() override;`
- L247 _public member_ `static const FName ViewportTabId;` — The tab ids for all the tabs used
- L248 _public member_ `static const FName PropertiesTabId;`
- L249 _public member_ `static const FName SocketManagerTabId;`
- L250 _public member_ `static const FName CollisionTabId;`
- L251 _public member_ `static const FName PreviewSceneSettingsTabId;`
- L252 _public member_ `static const FName SecondaryToolbarTabId;`
- L255 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);`
- L256 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L257 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SocketManager(const FSpawnTabArgs& Args);`
- L258 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Collision(const FSpawnTabArgs& Args);`
- L259 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args);`
- L260 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SecondaryToolbar(const FSpawnTabArgs& Args);`
- L264 _private prototype_ `void ToggleShowNormals();` — Callback for toggling the normals show flag.
- L267 _private prototype_ `bool IsShowNormalsChecked() const;` — Callback for checking the normals show flag.
- L270 _private prototype_ `void ToggleShowTangents();` — Callback for toggling the tangents show flag.
- L273 _private prototype_ `bool IsShowTangentsChecked() const;` — Callback for checking the tangents show flag.
- L276 _private prototype_ `void ToggleShowBinormals();` — Callback for toggling the binormals show flag.
- L279 _private prototype_ `bool IsShowBinormalsChecked() const;` — Callback for checking the binormals show flag.
- L282 _private prototype_ `void ToggleShowPivots();` — Callback for toggling the pivots show flag.
- L285 _private prototype_ `bool IsShowPivotsChecked() const;` — Callback for checking the pivots show flag.
- L288 _private prototype_ `void ToggleShowVertices();` — Callback for toggling the vertices show flag.
- L291 _private prototype_ `bool IsShowVerticesChecked() const;` — Callback for checking the vertices show flag.
- L294 _private prototype_ `void ToggleShowGrids();` — Callback for toggling the grid show flag.
- L297 _private prototype_ `bool IsShowGridsChecked() const;` — Callback for checking the grid show flag.
- L300 _private prototype_ `void ToggleShowBounds();` — Callback for toggling the bounds show flag.
- L303 _private prototype_ `bool IsShowBoundsChecked() const;` — Callback for checking the bounds show flag.
- L306 _private prototype_ `void ToggleShowSimpleCollisions();` — Callback for toggling the simple collisions show flag.
- L309 _private prototype_ `bool IsShowSimpleCollisionsChecked() const;` — Callback for checking the simple collisions show flag.
- L312 _private prototype_ `void ToggleShowComplexCollisions();` — Callback for toggling the complex collisions show flag.
- L315 _private prototype_ `bool IsShowComplexCollisionsChecked() const;` — Callback for checking the complex collisions show flag.
- L318 _private prototype_ `void ToggleShowSockets();` — Callback for toggling the sockets show flag.
- L321 _private prototype_ `bool IsShowSocketsChecked() const;` — Callback for checking the sockets show flag.
- L324 _private prototype_ `void ToggleShowWireframes();` — Callback for toggling the wireframes show flag.
- L327 _private prototype_ `bool IsShowWireframesChecked() const;` — Callback for checking the wireframes show flag.
- L330 _private prototype_ `void ToggleShowVertexColors();` — Callback for toggling the vertex colors show flag.
- L333 _private prototype_ `bool IsShowVertexColorsChecked() const;` — Callback for checking the vertex colors show flag.
- L336 _private prototype_ `void ResetCamera();` — Reset the viewport camera to look at the mesh.
- L339 _private prototype_ `void ToggleDrawAdditionalData();` — Callback for toggling the draw additional data flag.
- L342 _private prototype_ `bool IsDrawAdditionalDataChecked() const;` — Callback for checking the draw additional data flag.
- L345 _private prototype_ `void BakeMaterials();` — Bake out Materials for give LOD(s).
- L351 _private prototype_ `TSharedPtr<class SStaticMeshEditorViewport> GetStaticMeshViewport() const;` — Gets First Viewport from layout.
- L353 _private member_ `FAdvancedPreviewSceneModule::FOnPreviewSceneChanged OnPreviewSceneChangedDelegate;`
- L356 _private prototype_ `void OnEditorLayoutChanged();` — Called when the Viewport Layout has changed.
- L359 _private prototype_ `void BindCommands();` — Binds commands associated with the Static Mesh Editor.
- L362 _private prototype_ `void ExtendToolBar();` — Builds the Static Mesh Editor toolbar.
- L365 _private prototype_ `void BuildSubTools();` — Builds the sub-tools that are a part of the static mesh editor.
- L370 _private prototype_ `void UpdateLODStats(int32 CurrentLOD);` — Updates NumTriangles, NumVertices and NumUVChannels for the given LOD
- L373 _private prototype_ `void ComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — A general callback for the combo boxes in the Static Mesh Editor to force a viewport refresh when a selection changes.
- L387 _private prototype_ `void HandleReimportMesh(const FReimportParameters ReimportParameters);` — Callback to reimport the base mesh
- L390 _private prototype_ `void HandleReimportAllMesh(const FReimportParameters ReimportParameters);` — Callback to reimport the base mesh and also all custom LODs
- L397 _private prototype_ `void SetEditorMesh(UStaticMesh* InStaticMesh, bool bResetCamera = true);` — Sets the editor's current mesh and refreshes various settings to correspond with the new data. @param	InStaticMesh		The static mesh to use for the editor.
- L400 _private prototype_ `void GenerateKDop(const FVector* Directions, uint32 NumDirections);` — Helper function for generating K-DOP collision geometry.
- L403 _private prototype_ `void OnCollisionBox();` — Callback for creating box collision.
- L406 _private prototype_ `void OnCollisionSphere();` — Callback for creating sphere collision.
- L409 _private prototype_ `void OnCollisionSphyl();` — Callback for creating sphyl collision.
- L418 _private prototype_ `void CreateBoxVertsFromBoxCollision(const struct FKBoxElem& BoxElem, TArray<FVector>& Verts, float Scale);` — Quick and dirty way of creating box vertices from a box collision representation Grossly inefficient, but not time critical @param BoxElem - Box collision to get the vertices for @param Verts - output listing of vertex data from the box collision @param Scale - scale to create this box at
- L421 _private prototype_ `void OnConvertBoxToConvexCollision(void);` — Converts the collision data for the static mesh
- L424 _private prototype_ `void OnCopyCollisionFromSelectedStaticMesh(void);` — Copy the collision data from the selected static mesh in Content Browser
- L427 _private prototype_ `bool CanCopyCollisionFromSelectedStaticMesh() const;` — Whether there is a valid static mesh to copy collision from selected in the content browser
- L430 _private prototype_ `UStaticMesh* GetFirstSelectedStaticMeshInContentBrowser() const;` — Get the first static mesh selected in the content browser
- L433 _private prototype_ `void OnRemoveCollision(void);` — Clears the collision data for the static mesh
- L436 _private prototype_ `bool CanRemoveCollision();` — Whether there is collision to remove from the static mesh
- L439 _private prototype_ `void OnChangeMesh();` — Change the mesh the editor is viewing.
- L442 _private prototype_ `bool CanChangeMesh() const;` — Whether there is a static mesh selected in the content browser to change to
- L445 _private prototype_ `void OnSaveGeneratedLODs();` — Replace the generated LODs in the original source mesh with the reduced versions.
- L448 _private prototype_ `void GenerateUVChannelComboList(UToolMenu* InMenu);` — Rebuilds the UV Channel combo list and attempts to set it to the same channel.
- L451 _private prototype_ `void DeleteSelected();` — Delete whats currently selected
- L454 _private prototype_ `bool CanDeleteSelected() const;` — Whether we currently have any selected that can be deleted
- L457 _private prototype_ `void InitSocketManager();` — Init SocketManager (does nothing if it already exists)
- L460 _private prototype_ `void DeleteSelectedSockets();` — Delete the currently selected sockets
- L463 _private prototype_ `void DeleteSelectedPrims();` — Delete the currently selected prims
- L466 _private prototype_ `void DuplicateSelected();` — Duplicate whats currently selected
- L469 _private prototype_ `bool CanDuplicateSelected() const;` — Whether we currently have any selected that can be duplicated
- L472 _private prototype_ `void CopySelected();` — Copy what's currently selected to the clipboard
- L475 _private prototype_ `bool CanCopySelected() const;` — Whether we currently have anything selected that can be copied to the clipboard
- L478 _private prototype_ `void PasteCopied();` — Paste what's current on the clipboard
- L481 _private prototype_ `bool CanPasteCopied() const;` — Whether we can paste what's currently on the clipboard
- L484 _private prototype_ `bool CanRenameSelected() const;` — Whether we currently have any selected that can be renamed
- L487 _private prototype_ `void ExecuteFindInExplorer();` — Handler for when FindInExplorer is selected
- L490 _private prototype_ `bool CanExecuteSourceCommands() const;` — Returns true to allow execution of source file commands
- L493 _private prototype_ `void OnObjectReimported(UObject* InObject);` — Callback when an object is reimported, handles steps needed to keep the editor up-to-date.
- L496 _private prototype_ `void OnConvexDecomposition();` — Opens the convex decomposition tab.
- L499 _private prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L500 _private prototype_ `virtual void SetupReadOnlyMenuProfiles(FReadOnlyAssetEditorCustomization& OutReadOnlyCustomization) override;`
- L505 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L506 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L510 _private prototype_ `void UndoAction();` — Undo Action
- L513 _private prototype_ `void RedoAction();` — Redo Action
- L516 _private prototype_ `void OnMeshChanged();` — Callback when the mesh change
- L519 _private prototype_ `void OnSocketSelectionChanged();` — Called when socket selection changes
- L522 _private prototype_ `void OnPostReimport(UObject* InObject, bool bSuccess);` — Callback when an object has been reimported, and whether it worked
- L524 _private prototype_ `void SetCurrentViewedUVChannel(int32 InNewUVChannel);`
- L526 _private prototype_ `ECheckBoxState GetUVChannelCheckState(int32 TestUVChannel) const;`
- L529 _private prototype_ `bool CanRemoveUVChannel();` — Callbacks for UV edition
- L530 _private prototype_ `void RemoveCurrentUVChannel();`
- L533 _private prototype_ `void AddSecondaryToolbarExtender(TSharedPtr<FExtender> Extender);` — Adds or removes extenders to the secondary toolbar
- L534 _private prototype_ `void RemoveSecondaryToolbarExtender(TSharedPtr<FExtender> Extender);`
- L536 _private prototype_ `void GenerateSecondaryToolbar();`
- L540 _private member_ `TSharedPtr<class FEditorViewportTabContent> ViewportTabContent;` — Tracking the active viewports in this editor.
- L543 _private member_ `TSharedPtr<class IDetailsView> StaticMeshDetailsView;` — Property View
- L546 _private member_ `TSharedPtr< class ISocketManager> SocketManager;` — Socket Manager widget.
- L549 _private member_ `TSharedPtr< class SConvexDecomposition> ConvexDecomposition;` — Convex Decomposition widget
- L552 _private member_ `TWeakPtr<class FStaticMeshDetails> StaticMeshDetails;` — Static mesh editor detail customization
- L555 _private member_ `TObjectPtr<UStaticMesh> StaticMesh;` — The currently viewed Static Mesh.
- L558 _private member_ `TArray<int32> NumTriangles;` — The number of triangles associated with the static mesh LOD.
- L561 _private member_ `TArray<int32> NumVertices;` — The number of vertices associated with the static mesh LOD.
- L564 _private member_ `TArray<int32> NumUVChannels;` — The number of used UV channels.
- L567 _private member_ `FOnPostUndoMulticaster OnPostUndo;` — Delegates called after an undo operation for child widgets to refresh
- L570 _private member_ `TArray<FPrimData> SelectedPrims;` — Information on the selected collision primitives
- L573 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;` — Scene preview settings widget
- L576 _private member_ `const float MinPrimSize;` — Misc consts
- L577 _private member_ `const FVector OverlapNudge;`
- L580 _private member_ `int32 CurrentViewedUVChannel;` — The current UV Channel we are viewing
- L583 _private member_ `FOnSelectedLODChangedMulticaster OnSelectedLODChanged;` — Selected LOD changed delegates
- L584 _private member_ `FOnSelectedLODChangedMulticaster OnSelectedLODChangedResetOnRefresh;`
- L588 _private member_ `IDecomposeMeshToHullsAsync *DecomposeMeshToHullsAsync{ nullptr };` — Instance of the active asynchronous convex decomposition interface.
- L592 _private member_ `TMap<int32, int32> CustomEditorData;` — Allow custom data for this editor
- L595 _private member_ `TSharedPtr<FExtender> EditorToolbarExtender;` — A local reference to the private Extender set in FAssetEditorToolkit so that we can extend our Toolbar sub-menus
- L598 _private member_ `TSharedPtr<SWidget> SecondaryToolbar;` — Static Mesh Editor Secondary Toolbar
- L601 _private member_ `TSharedPtr<SBorder> SecondaryToolbarWidgetContent;` — The widget that will house the secondary toolbar widget
- L604 _private member_ `TArray<TSharedPtr<FExtender>> SecondaryToolbarExtenders;` — The extenders to populate the secondary toolbar with
- L607 _private member_ `TWeakPtr<SDockTab> PreviewSceneDockTab;` — The tab that the preview scene settings widget goes in
- L610 _private member_ `FTabSpawnerEntry* SecondaryToolbarEntry;` — Spawner entry for the secondary toolbar tab
- L613 _private member_ `FText SecondaryToolbarDisplayName;` — The text display name to override the default display name of the secondary toolbar
- L616 _private member_ `AssetEditorViewportFactoryFunction MakeViewportFunc;` — Storage for our viewport creation function that will be passed to the viewport layout system
- L619 _private member_ `bool bDrawNormals;` — Toolbar toggles
- L620 _private member_ `bool bDrawTangents;`
- L621 _private member_ `bool bDrawBinormals;`
- L622 _private member_ `bool bDrawPivots;`
- L623 _private member_ `bool bDrawVertices;`
- L624 _private member_ `bool bDrawGrids;`
- L625 _private member_ `bool bDrawBounds;`
- L626 _private member_ `bool bDrawSimpleCollisions;`
- L627 _private member_ `bool bDrawComplexCollisions;`
- L628 _private member_ `bool bDrawSockets;`
- L629 _private member_ `bool bDrawWireframes;`
- L630 _private member_ `bool bDrawVertexColors;`
- L631 _private member_ `bool bDrawAdditionalData;`
- L633 _private member_ `TSharedPtr<FStaticMeshEditorModeUILayer> ModeUILayer;`

#### struct `FStaticMeshEditor::FReimportParameters`  
`struct FReimportParameters`  
_L375-384_
- L377 _public function_ `FReimportParameters(bool bInWithNewFile, bool bInWithDialog) : bWithNewFile(bInWithNewFile) , bWithDialog(bInWithDialog)`
- L382 _public member_ `bool bWithNewFile = false;`
- L383 _public member_ `bool bWithDialog = false;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define USE_ASYNC_DECOMP 1`

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorEdMode.h` (Private)


#### class `FStaticMeshEditorEdMode`  
`class FStaticMeshEditorEdMode : public FEdMode`  
_L10-20_
- inherits: `FEdMode`
- desc: EdMode for the StaticMeshEditor, that enables various ITF functionality.
- L13 _public member_ `static inline const FEditorModeID Id = TEXT("Sta`
- L15 _public function_ `virtual bool ShouldDrawWidget() const override`
- L16 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L19 _public function_ `virtual EEditAction::Type GetActionEditDuplicate() override` — Explicitly handle duplication. Reconsider when sockets have TypedElement handlers.

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorModeUILayer.h` (Private)


#### class `UStaticMeshEditorUISubsystem`  
`class UStaticMeshEditorUISubsystem : public UAssetEditorUISubsystem`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- L14 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L15 _public prototype_ `virtual void Deinitialize() override;`
- L16 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

#### class `FStaticMeshEditorModeUILayer`  
`class FStaticMeshEditorModeUILayer : public FAssetEditorModeUILayer`  
_L20-30_
- inherits: `FAssetEditorModeUILayer`
- L24 _public prototype_ `FStaticMeshEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L26 _public prototype_ `void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L27 _public prototype_ `void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L29 _public prototype_ `TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorStyle.h` (Private)


#### class `FStaticMeshEditorStyle`  
`class FStaticMeshEditorStyle : public FSlateStyleSet`  
_L11-24_
- inherits: `FSlateStyleSet`
- desc: Slate style set for Static Mesh Editor
- L15 _public member_ `static FName StyleName;`
- L18 _public prototype_ `static FStaticMeshEditorStyle& Get();` — Access the singleton instance for this style set
- L22 _private prototype_ `FStaticMeshEditorStyle();`
- L23 _private prototype_ `~FStaticMeshEditorStyle();`

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorTools.h` (Private)


#### enum `ECreationModeChoice`  
`enum ECreationModeChoice`  
_L36-40_
- L38 _public enumerator_ `CreateNew`
- L39 _public enumerator_ `UseChannel0`

#### enum `ELimitModeChoice`  
`enum ELimitModeChoice`  
_L42-46_
- L44 _public enumerator_ `Stretching`
- L45 _public enumerator_ `Charts`

#### class `FStaticMeshDetails`  
`class FStaticMeshDetails : public IDetailCustomization`  
_L48-90_
- inherits: `IDetailCustomization`
- L51 _public prototype_ `FStaticMeshDetails( class FStaticMeshEditor& InStaticMeshEditor );`
- L52 _public prototype_ `~FStaticMeshDetails();`
- L55 _public prototype_ `virtual void CustomizeDetails( class IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L58 _public prototype_ `bool IsApplyNeeded() const;` — @return true if settings have been changed and need to be applied to the static mesh
- L61 _public prototype_ `void ApplyChanges();` — Applies changes to the static mesh
- L65 _private member_ `TSharedPtr<FLevelOfDetailSettingsLayout> LevelOfDetailSettings;` — Level of detail settings for the details panel
- L68 _private member_ `TSharedPtr<FNaniteStaticMeshLayout> NaniteSettings;` — Nanite settings for the details panel.
- L71 _private member_ `TSharedPtr<FRayTracingProxySettingsLayout> RayTracingProxySettings;` — Nanite settings for the details panel.
- L74 _private member_ `class FStaticMeshEditor& StaticMeshEditor;` — Static mesh editor
- L77 _private member_ `TSharedPtr<IPropertyHandle> VertexColorImportOptionHandle;` — Property handle used to determine if the VertexColorImportOverride property should be enabled.
- L80 _private member_ `TSharedPtr<IPropertyHandle> VertexColorImportOverrideHandle;` — Property handle used during UI construction
- L83 _private prototype_ `void OnInstancedFbxStaticMeshImportDataPropertyIteration(IDetailCategoryBuilder& BaseCategory, IDetailGroup* PropertyGroup, TSharedRef<IPropertyHandle>& Property) const;` — Delegate implementation of FOnInstancedPropertyIteration used during DataImport UI construction
- L86 _private prototype_ `void OnLightmapSettingsChanged();` — Delegate to ensure the lightmap settings are always valid.
- L89 _private prototype_ `bool GetVertexOverrideColorEnabledState() const;` — Delegate used at runtime to determine the state of the VertexOverrideColor property

#### class `SConvexDecomposition`  
`class SConvexDecomposition : public SCompoundWidget`  
_L96-172_
- inherits: `SCompoundWidget`
- desc: Window handles convex decomposition, settings and controls.
- L99 _public function_ `SLATE_BEGIN_ARGS( SConvexDecomposition ) : _StaticMeshEditorPtr()`
- L104 _public prototype_ `SLATE_ARGUMENT( TWeakPtr< IStaticMeshEditor >, StaticMeshEditorPtr ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The Static Mesh Editor this tool is associated with.
- L110 _public prototype_ `virtual ~SConvexDecomposition();`
- L114 _private prototype_ `FReply OnApplyDecomp();` — Callback when the "Apply" button is clicked.
- L117 _private prototype_ `FReply OnDefaults();` — Callback when the "Defaults" button is clicked.
- L120 _private prototype_ `void OnHullCountCommitted(uint32 InNewValue, ETextCommit::Type CommitInfo);` — Assigns the accuracy of hulls based on the spinbox's value.
- L123 _private prototype_ `void OnHullCountChanged(uint32 InNewValue);` — Assigns the accuracy of hulls based on the spinbox's value.
- L126 _private prototype_ `uint32 GetHullPrecision() const;` — Retrieves the precision of hulls created.
- L129 _private prototype_ `void OnHullPrecisionCommitted(uint32 InNewValue, ETextCommit::Type CommitInfo);` — Assigns the precision of hulls based on the spinbox's value.
- L132 _private prototype_ `void OnHullPrecisionChanged(uint32 InNewValue);` — Assigns the precision of hulls based on the spinbox's value.
- L135 _private prototype_ `uint32 GetHullCount() const;` — Retrieves the accuracy of hulls created.
- L138 _private prototype_ `void OnVertsPerHullCountCommitted(int32 InNewValue, ETextCommit::Type CommitInfo);` — Assigns the max number of hulls based on the spinbox's value.
- L141 _private prototype_ `void OnVertsPerHullCountChanged(int32 InNewValue);` — Assigns the max number of hulls based on the spinbox's value.
- L148 _private prototype_ `int32 GetVertsPerHullCount() const;` — Retrieves the max number of verts per hull allowed. @return			The max number of verts per hull selected.
- L152 _private member_ `TWeakPtr<IStaticMeshEditor> StaticMeshEditorPtr;` — The Static Mesh Editor this tool is associated with.
- L155 _private member_ `TSharedPtr< SSpinBox<uint32> > HullCount;` — Spinbox for the max number of hulls allowed.
- L158 _private member_ `TSharedPtr< SSpinBox<uint32> > HullPrecision;` — Spinbox for the convex decomposition precision allowed.
- L161 _private member_ `uint32 CurrentHullCount;` — The current number of max number of hulls selected.
- L164 _private member_ `uint32 CurrentHullPrecision;` — The current precision level for convex decomposition
- L167 _private member_ `TSharedPtr< SSpinBox<int32> > MaxVertsPerHull;` — Spinbox for the max number of verts per hulls allowed.
- L170 _private member_ `int32 CurrentMaxVertsPerHullCount;` — The current number of max verts per hull selected.

#### class `FMeshBuildSettingsLayout`  
`class FMeshBuildSettingsLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FMeshBuildSettingsLayout>`  
_L175-244_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMeshBuildSettingsLayout>`
- L178 _public prototype_ `FMeshBuildSettingsLayout( TSharedRef<FLevelOfDetailSettingsLayout> InParentLODSettings, int32 InLODIndex );`
- L179 _public prototype_ `virtual ~FMeshBuildSettingsLayout();`
- L181 _public function_ `const FMeshBuildSettings& GetSettings() const`
- L182 _public prototype_ `void UpdateSettings(const FMeshBuildSettings& InSettings);`
- L186 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L187 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L188 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L189 _private function_ `virtual void Tick( float DeltaTime ) override`
- L190 _private function_ `virtual bool RequiresTick() const override`
- L191 _private function_ `virtual FName GetName() const override`
- L192 _private function_ `virtual bool InitiallyCollapsed() const override`
- L194 _private prototype_ `FReply OnApplyChanges();`
- L195 _private prototype_ `ECheckBoxState ShouldRecomputeNormals() const;`
- L196 _private prototype_ `ECheckBoxState ShouldRecomputeTangents() const;`
- L197 _private prototype_ `ECheckBoxState ShouldUseMikkTSpace() const;`
- L198 _private prototype_ `ECheckBoxState ShouldComputeWeightedNormals() const;`
- L199 _private prototype_ `ECheckBoxState ShouldRemoveDegenerates() const;`
- L200 _private prototype_ `ECheckBoxState ShouldBuildReversedIndexBuffer() const;`
- L201 _private prototype_ `ECheckBoxState ShouldUseHighPrecisionTangentBasis() const;`
- L202 _private prototype_ `ECheckBoxState ShouldUseFullPrecisionUVs() const;`
- L203 _private prototype_ `ECheckBoxState ShouldUseBackwardsCompatibleF16TruncUVs() const;`
- L204 _private prototype_ `ECheckBoxState ShouldGenerateLightmapUVs() const;`
- L205 _private prototype_ `ECheckBoxState ShouldGenerateDistanceFieldAsIfTwoSided() const;`
- L206 _private prototype_ `bool IsRemoveDegeneratesDisabled() const;`
- L207 _private prototype_ `int32 GetMinLightmapResolution() const;`
- L208 _private prototype_ `int32 GetSrcLightmapIndex() const;`
- L209 _private prototype_ `int32 GetDstLightmapIndex() const;`
- L210 _private prototype_ `TOptional<float> GetBuildScaleX() const;`
- L211 _private prototype_ `TOptional<float> GetBuildScaleY() const;`
- L212 _private prototype_ `TOptional<float> GetBuildScaleZ() const;`
- L213 _private prototype_ `float GetDistanceFieldResolutionScale() const;`
- L214 _private prototype_ `int32 GetMaxLumenMeshCards() const;`
- L216 _private prototype_ `void OnRecomputeNormalsChanged(ECheckBoxState NewState);`
- L217 _private prototype_ `void OnRecomputeTangentsChanged(ECheckBoxState NewState);`
- L218 _private prototype_ `void OnUseMikkTSpaceChanged(ECheckBoxState NewState);`
- L219 _private prototype_ `void OnComputeWeightedNormalsChanged(ECheckBoxState NewState);`
- L220 _private prototype_ `void OnRemoveDegeneratesChanged(ECheckBoxState NewState);`
- L221 _private prototype_ `void OnBuildReversedIndexBufferChanged(ECheckBoxState NewState);`
- L222 _private prototype_ `void OnUseHighPrecisionTangentBasisChanged(ECheckBoxState NewState);`
- L223 _private prototype_ `void OnUseFullPrecisionUVsChanged(ECheckBoxState NewState);`
- L224 _private prototype_ `void OnUseBackwardsCompatibleF16TruncUVsChanged(ECheckBoxState NewState);`
- L225 _private prototype_ `void OnGenerateLightmapUVsChanged(ECheckBoxState NewState);`
- L226 _private prototype_ `void OnGenerateDistanceFieldAsIfTwoSidedChanged(ECheckBoxState NewState);`
- L227 _private prototype_ `void OnMinLightmapResolutionChanged( int32 NewValue );`
- L228 _private prototype_ `void OnSrcLightmapIndexChanged( int32 NewValue );`
- L229 _private prototype_ `void OnDstLightmapIndexChanged( int32 NewValue );`
- L230 _private prototype_ `void OnBuildScaleXChanged( float NewScaleX, ETextCommit::Type TextCommitType );`
- L231 _private prototype_ `void OnBuildScaleYChanged( float NewScaleY, ETextCommit::Type TextCommitType );`
- L232 _private prototype_ `void OnBuildScaleZChanged( float NewScaleZ, ETextCommit::Type TextCommitType );`
- L233 _private prototype_ `void OnDistanceFieldResolutionScaleChanged(float NewValue);`
- L234 _private prototype_ `void OnDistanceFieldResolutionScaleCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L235 _private prototype_ `FString GetCurrentDistanceFieldReplacementMeshPath() const;`
- L236 _private prototype_ `void OnDistanceFieldReplacementMeshSelected(const FAssetData& AssetData);`
- L237 _private prototype_ `void OnMaxLumenMeshCardsChanged(int32 NewValue);`
- L238 _private prototype_ `void OnMaxLumenMeshCardsCommitted(int32 NewValue, ETextCommit::Type TextCommitType);`
- L241 _private member_ `TWeakPtr<FLevelOfDetailSettingsLayout> ParentLODSettings;`
- L242 _private member_ `FMeshBuildSettings BuildSettings;`
- L243 _private member_ `int32 LODIndex;`

#### class `FMeshReductionSettingsLayout`  
`class FMeshReductionSettingsLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FMeshReductionSettingsLayout>`  
_L246-343_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMeshReductionSettingsLayout>`
- L249 _public prototype_ `FMeshReductionSettingsLayout(TSharedRef<FLevelOfDetailSettingsLayout> InParentLODSettings, int32 InCurrentLODIndex, bool InCanReduceMyself);`
- L250 _public prototype_ `virtual ~FMeshReductionSettingsLayout();`
- L252 _public prototype_ `const FMeshReductionSettings& GetSettings() const;`
- L253 _public prototype_ `void UpdateSettings(const FMeshReductionSettings& InSettings);`
- L256 _private function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override` — IDetailCustomNodeBuilder Interface
- L257 _private prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L258 _private prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L259 _private function_ `virtual void Tick( float DeltaTime ) override`
- L260 _private function_ `virtual bool RequiresTick() const override`
- L261 _private function_ `virtual FName GetName() const override`
- L262 _private function_ `virtual bool InitiallyCollapsed() const override`
- L264 _private prototype_ `FReply OnApplyChanges();`
- L267 _private prototype_ `float GetPercentTriangles() const;` — used by native tool and simplygon
- L268 _private prototype_ `uint32 GetMaxNumOfPercentTriangles() const;`
- L271 _private prototype_ `float GetPercentVertices() const;` — used by native quadric simplifier
- L272 _private prototype_ `uint32 GetMaxNumOfPercentVertices() const;`
- L275 _private prototype_ `float GetMaxDeviation() const;` — used by simplygon only
- L276 _private prototype_ `float GetPixelError() const;`
- L277 _private prototype_ `float GetWeldingThreshold() const;`
- L278 _private prototype_ `ECheckBoxState ShouldRecalculateNormals() const;`
- L279 _private prototype_ `float GetHardAngleThreshold() const;`
- L282 _private prototype_ `void OnPercentTrianglesChanged(float NewValue);` — used by native tool and simplygon
- L283 _private prototype_ `void OnPercentTrianglesCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L284 _private prototype_ `void OnMaxNumOfPercentTrianglesChanged(uint32 NewValue);`
- L285 _private prototype_ `void OnMaxNumOfPercentTrianglesCommitted(uint32 NewValue, ETextCommit::Type TextCommitType);`
- L288 _private prototype_ `void OnPercentVerticesChanged(float NewValue);` — Used by native code only
- L289 _private prototype_ `void OnPercentVerticesCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L290 _private prototype_ `void OnMaxNumOfPercentVerticesChanged(uint32 NewValue);`
- L291 _private prototype_ `void OnMaxNumOfPercentVerticesCommitted(uint32 NewValue, ETextCommit::Type TextCommitType);`
- L295 _private prototype_ `void OnMaxDeviationChanged(float NewValue);` — used by simplygon only
- L296 _private prototype_ `void OnMaxDeviationCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L297 _private prototype_ `void OnPixelErrorChanged(float NewValue);`
- L298 _private prototype_ `void OnPixelErrorCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L299 _private prototype_ `void OnRecalculateNormalsChanged(ECheckBoxState NewValue);`
- L302 _private prototype_ `void OnWeldingThresholdChanged(float NewValue);` — used by native tool and simplygon
- L303 _private prototype_ `void OnWeldingThresholdCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L306 _private prototype_ `void OnHardAngleThresholdChanged(float NewValue);` — used by simplygon only
- L307 _private prototype_ `void OnHardAngleThresholdCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L309 _private prototype_ `void OnSilhouetteImportanceChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L310 _private prototype_ `void OnTextureImportanceChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L311 _private prototype_ `void OnShadingImportanceChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L314 _private prototype_ `void OnTerminationCriterionChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);` — Used by native tool only.
- L317 _private prototype_ `bool UseNativeToolLayout() const;` — Are we using our tool, or simplygon?  The tool is only changed during editor restarts
- L319 _private prototype_ `EVisibility GetTriangleCriterionVisibility() const;`
- L320 _private prototype_ `EVisibility GetVertexCriterionVisibility() const;`
- L322 _private prototype_ `TOptional<int32> GetBaseLODIndex() const;`
- L323 _private prototype_ `void SetBaseLODIndex(int32 NewLODBaseIndex);`
- L326 _private member_ `TWeakPtr<FLevelOfDetailSettingsLayout> ParentLODSettings;`
- L327 _private member_ `FMeshReductionSettings ReductionSettings;`
- L328 _private member_ `int32 CurrentLODIndex;`
- L329 _private member_ `bool bCanReduceMyself;`
- L332 _private member_ `TArray<TSharedPtr<FString> > ImportanceOptions;` — Used by simplygon
- L333 _private member_ `TSharedPtr<STextComboBox> SilhouetteCombo;`
- L334 _private member_ `TSharedPtr<STextComboBox> TextureCombo;`
- L335 _private member_ `TSharedPtr<STextComboBox> ShadingCombo;`
- L338 _private member_ `TSharedPtr<STextComboBox> TerminationCriterionCombo;` — Used by quadric simplifier
- L339 _private member_ `TArray<TSharedPtr<FString> > TerminationOptions;`
- L342 _private member_ `bool bUseQuadricSimplifier;` — Identify the actual that this UI drives

#### class `FMeshSectionSettingsLayout`  
`class FMeshSectionSettingsLayout : public TSharedFromThis<FMeshSectionSettingsLayout>`  
_L345-433_
- inherits: `TSharedFromThis<FMeshSectionSettingsLayout>`
- L348 _public function_ `FMeshSectionSettingsLayout( IStaticMeshEditor& InStaticMeshEditor, int32 InLODIndex, TArray<class IDetailCategoryBuilder*> &InLodCategories) : StaticMeshEditor( InStaticMeshEditor ) , LODIndex( InLODIndex ) , LodCategoriesPtr(&InLodCategories)`
- L354 _public prototype_ `virtual ~FMeshSectionSettingsLayout();`
- L356 _public prototype_ `void AddToCategory( IDetailCategoryBuilder& CategoryBuilder );`
- L358 _public prototype_ `void SetCurrentLOD(int32 NewLodIndex);`
- L362 _private prototype_ `UStaticMesh& GetStaticMesh() const;`
- L364 _private prototype_ `void OnCopySectionList(int32 CurrentLODIndex);`
- L365 _private prototype_ `bool OnCanCopySectionList(int32 CurrentLODIndex) const;`
- L366 _private prototype_ `void OnPasteSectionList(int32 CurrentLODIndex);`
- L368 _private prototype_ `void OnCopySectionItem(int32 CurrentLODIndex, int32 SectionIndex);`
- L369 _private prototype_ `bool OnCanCopySectionItem(int32 CurrentLODIndex, int32 SectionIndex) const;`
- L370 _private prototype_ `void OnPasteSectionItem(int32 CurrentLODIndex, int32 SectionIndex);`
- L377 _private prototype_ `void OnGetSectionsForView(class ISectionListBuilder& OutSections, int32 ForLODIndex);` — Called by the material list widget when we need to get new materials for the list @param OutMaterials	Handle to a material list builder that materials should be added to
- L387 _private prototype_ `void OnSectionChanged(int32 ForLODIndex, int32 SectionIndex, int32 NewMaterialSlotIndex, FName NewMaterialSlotName);` — Called when a user drags a new material over a list item to replace it @param NewMaterial	The material that should replace the existing material @param PrevMaterial	The material that should be replaced @param SlotIndex		The index of the slot on the component where materials should be replaces @param bReplaceAll	If true all materials in the slot should be replaced not just ones using PrevMaterial
- L395 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomNameWidgetsForSection(int32 ForLODIndex, int32 SectionIndex);` — Called by the material list widget on generating each name widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L403 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomSectionWidgetsForSection(int32 ForLODIndex, int32 SectionIndex);` — Called by the material list widget on generating each thumbnail widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L405 _private prototype_ `ECheckBoxState IsSectionVisibleInRayTracing(int32 SectionIndex) const;`
- L406 _private prototype_ `void OnSectionVisibleInRayTracingChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L408 _private prototype_ `ECheckBoxState DoesSectionAffectDistanceFieldLighting(int32 SectionIndex) const;`
- L409 _private prototype_ `void OnSectionAffectDistanceFieldLightingChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L411 _private prototype_ `ECheckBoxState IsSectionOpaque(int32 SectionIndex) const;`
- L412 _private prototype_ `void OnSectionForceOpaqueFlagChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L414 _private prototype_ `ECheckBoxState DoesSectionCastShadow(int32 SectionIndex) const;`
- L415 _private prototype_ `void OnSectionCastShadowChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L416 _private prototype_ `ECheckBoxState DoesSectionCollide(int32 SectionIndex) const;`
- L417 _private prototype_ `bool SectionCollisionEnabled() const;`
- L418 _private prototype_ `FText GetCollisionEnabledToolTip() const;`
- L419 _private prototype_ `void OnSectionCollisionChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L421 _private prototype_ `ECheckBoxState IsSectionHighlighted(int32 SectionIndex) const;`
- L422 _private prototype_ `void OnSectionHighlightedChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L423 _private prototype_ `ECheckBoxState IsSectionIsolatedEnabled(int32 SectionIndex) const;`
- L424 _private prototype_ `void OnSectionIsolatedChanged(ECheckBoxState NewState, int32 SectionIndex);`
- L426 _private prototype_ `void CallPostEditChange(FProperty* PropertyChanged=nullptr);`
- L427 _private prototype_ `void UpdateLODCategoryVisibility();`
- L429 _private member_ `IStaticMeshEditor& StaticMeshEditor;`
- L430 _private member_ `int32 LODIndex;`
- L432 _private member_ `TArray<class IDetailCategoryBuilder*> *LodCategoriesPtr;`

#### struct `FSectionLocalizer`  
`struct FSectionLocalizer`  
_L435-454_
- L437 _public function_ `FSectionLocalizer(int32 InLODIndex, int32 InSectionIndex) : LODIndex(InLODIndex) , SectionIndex(InSectionIndex)`
- L442 _public function_ `bool operator==(const FSectionLocalizer& Other) const`
- L447 _public function_ `bool operator!=(const FSectionLocalizer& Other) const`
- L452 _public member_ `int32 LODIndex;`
- L453 _public member_ `int32 SectionIndex;`

#### class `FMeshMaterialsLayout`  
`class FMeshMaterialsLayout : public TSharedFromThis<FMeshMaterialsLayout>`  
_L457-542_
- inherits: `TSharedFromThis<FMeshMaterialsLayout>`
- L460 _public function_ `FMeshMaterialsLayout(IStaticMeshEditor& InStaticMeshEditor) : StaticMeshEditor(InStaticMeshEditor)`
- L466 _public prototype_ `virtual ~FMeshMaterialsLayout();`
- L468 _public prototype_ `void AddToCategory(IDetailCategoryBuilder& CategoryBuilder, const TArray<FAssetData>& AssetDataArray);`
- L471 _private prototype_ `UStaticMesh& GetStaticMesh() const;`
- L472 _private prototype_ `FReply AddMaterialSlot();`
- L473 _private prototype_ `FText GetMaterialArrayText() const;`
- L475 _private prototype_ `void GetMaterials(class IMaterialListBuilder& ListBuilder);`
- L476 _private prototype_ `void OnMaterialChanged(UMaterialInterface* NewMaterial, UMaterialInterface* PrevMaterial, int32 SlotIndex, bool bReplaceAll);`
- L477 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetsForMaterial(UMaterialInterface* Material, int32 SlotIndex);`
- L478 _private prototype_ `TSharedRef<SWidget> OnGenerateNameWidgetsForMaterial(UMaterialInterface* Material, int32 SlotIndex);`
- L487 _private prototype_ `TSharedRef<SWidget> OnGenerateMaterialListExtraBottomWidget(UMaterialInterface* Material, int32 SlotIndex);` — Called by the material list widget on generating each thumbnail widget Those generated widget will be stack under the material list row @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L490 _private prototype_ `void OnMaterialSlotOverlayMaterialChanged(UMaterialInterface* NewOverlayMaterial, int32 MaterialIndex);` — Call when user change the material slot overlay material.
- L492 _private prototype_ `void OnResetMaterialToDefaultClicked(UMaterialInterface* Material, int32 SlotIndex);`
- L494 _private prototype_ `ECheckBoxState IsMaterialHighlighted(int32 SlotIndex) const;`
- L495 _private prototype_ `void OnMaterialHighlightedChanged(ECheckBoxState NewState, int32 SlotIndex);`
- L496 _private prototype_ `ECheckBoxState IsMaterialIsolatedEnabled(int32 SlotIndex) const;`
- L497 _private prototype_ `void OnMaterialIsolatedChanged(ECheckBoxState NewState, int32 SlotIndex);`
- L499 _private prototype_ `FText GetOriginalImportMaterialNameText(int32 MaterialIndex) const;`
- L500 _private prototype_ `FText GetMaterialNameText(int32 MaterialIndex) const;`
- L501 _private prototype_ `void OnMaterialNameCommitted(const FText& InValue, ETextCommit::Type CommitType, int32 MaterialIndex);`
- L502 _private prototype_ `bool CanDeleteMaterialSlot(int32 MaterialIndex) const;`
- L503 _private prototype_ `void OnDeleteMaterialSlot(int32 MaterialIndex);`
- L504 _private prototype_ `TSharedRef<SWidget> OnGetMaterialSlotUsedByMenuContent(int32 MaterialIndex);`
- L505 _private prototype_ `FText GetFirstMaterialSlotUsedBySection(int32 MaterialIndex) const;`
- L508 _private prototype_ `bool OnMaterialListDirty();` — If the material list is dirty this function will return true
- L510 _private prototype_ `ECheckBoxState IsShadowCastingEnabled(int32 SlotIndex) const;`
- L511 _private prototype_ `void OnShadowCastingChanged(ECheckBoxState NewState, int32 SlotIndex);`
- L513 _private prototype_ `EVisibility GetOverrideUVDensityVisibililty() const;`
- L514 _private prototype_ `ECheckBoxState IsUVDensityOverridden(int32 SlotIndex) const;`
- L515 _private prototype_ `void OnOverrideUVDensityChanged(ECheckBoxState NewState, int32 SlotIndex);`
- L517 _private prototype_ `EVisibility GetUVDensityVisibility(int32 SlotIndex, int32 UVChannelIndex) const;`
- L518 _private prototype_ `TOptional<float> GetUVDensityValue(int32 SlotIndex, int32 UVChannelIndex) const;`
- L519 _private prototype_ `void SetUVDensityValue(float InDensity, ETextCommit::Type CommitType, int32 SlotIndex, int32 UVChannelIndex);`
- L521 _private prototype_ `SVerticalBox::FSlot& GetUVDensitySlot(int32 SlotIndex, int32 UVChannelIndex) const;`
- L523 _private prototype_ `void CallPostEditChange(FProperty* PropertyChanged = nullptr);`
- L525 _private prototype_ `void OnCopyMaterialList();`
- L526 _private prototype_ `bool OnCanCopyMaterialList() const;`
- L527 _private prototype_ `void OnPasteMaterialList();`
- L529 _private prototype_ `void OnCopyMaterialItem(int32 CurrentSlot);`
- L530 _private prototype_ `bool OnCanCopyMaterialItem(int32 CurrentSlot) const;`
- L531 _private prototype_ `void OnPasteMaterialItem(int32 CurrentSlot);`
- L533 _private member_ `IStaticMeshEditor& StaticMeshEditor;`
- L536 _private member_ `TMap<int32, TArray<FSectionLocalizer>> MaterialUsedMap;` — This is to know if material are used by any LODs sections.
- L541 _private member_ `bool bDeleteWarningConsumed;` — This prevent showing the delete material slot warning dialog more then once per editor session

#### class `FLevelOfDetailSettingsLayout`  
`class FLevelOfDetailSettingsLayout : public TSharedFromThis<FLevelOfDetailSettingsLayout>`  
_L547-694_
- inherits: `TSharedFromThis<FLevelOfDetailSettingsLayout>`
- desc: Window for adding and removing LOD.
- L550 _public prototype_ `FLevelOfDetailSettingsLayout( FStaticMeshEditor& StaticMeshEditor );`
- L551 _public prototype_ `virtual ~FLevelOfDetailSettingsLayout();`
- L553 _public prototype_ `void AddToDetailsPanel( IDetailLayoutBuilder& DetailBuilder );`
- L556 _public prototype_ `bool IsApplyNeeded() const;` — Returns true if settings have been changed and an Apply is needed to update the asset.
- L559 _public prototype_ `void ApplyChanges();` — Apply current LOD settings to the mesh.
- L562 _public prototype_ `bool IsNaniteEnabled() const;` — Returns true if the LOD's static mesh has Nanite enabled
- L567 _private prototype_ `void AddLODLevelCategories( class IDetailLayoutBuilder& DetailBuilder );` — Creates the UI for Current LOD panel
- L570 _private prototype_ `FReply OnApply();` — Callbacks.
- L571 _private prototype_ `void OnLODCountChanged(int32 NewValue);`
- L572 _private prototype_ `void OnLODCountCommitted(int32 InValue, ETextCommit::Type CommitInfo);`
- L573 _private prototype_ `int32 GetLODCount() const;`
- L575 _private prototype_ `void OnSelectedLODChanged(int32 NewLodIndex);`
- L577 _private prototype_ `void OnMinLODChanged(int32 NewValue, FName Platform);`
- L578 _private prototype_ `void OnMinLODCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName Platform);`
- L579 _private prototype_ `int32 GetMinLOD(FName Platform) const;`
- L580 _private prototype_ `FPerPlatformInt GetMinLOD() const;`
- L581 _private prototype_ `TSharedRef<SWidget> GetMinLODWidget(FName PlatformGroupName) const;`
- L582 _private prototype_ `bool AddMinLODPlatformOverride(FName PlatformGroupName);`
- L583 _private prototype_ `bool RemoveMinLODPlatformOverride(FName PlatformGroupName);`
- L584 _private prototype_ `TArray<FName> GetMinLODPlatformOverrideNames() const;`
- L586 _private prototype_ `void OnMinQualityLevelLODChanged(int32 NewValue, FName QualityLevel);`
- L587 _private prototype_ `void OnMinQualityLevelLODCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName QualityLevel);`
- L588 _private prototype_ `int32 GetMinQualityLevelLOD(FName QualityLevel) const;`
- L589 _private prototype_ `TSharedRef<SWidget> GetMinQualityLevelLODWidget(FName QualityLevelName) const;`
- L590 _private prototype_ `bool AddMinLODQualityLevelOverride(FName QualityLevelName);`
- L591 _private prototype_ `bool RemoveMinLODQualityLevelOverride(FName QualityLevelName);`
- L592 _private prototype_ `TArray<FName> GetMinQualityLevelLODOverrideNames() const;`
- L593 _private prototype_ `FReply ResetToDefault();`
- L595 _private prototype_ `void OnNoRefStreamingLODBiasChanged(int32 NewValue, FName QualityLevel);`
- L596 _private prototype_ `void OnNoRefStreamingLODBiasCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName QualityLevel);`
- L597 _private prototype_ `int32 GetNoRefStreamingLODBias(FName QualityLevel) const;`
- L598 _private prototype_ `TSharedRef<SWidget> GetNoRefStreamingLODBiasWidget(FName QualityLevelName) const;`
- L599 _private prototype_ `bool AddNoRefStreamingLODBiasOverride(FName QualityLevelName);`
- L600 _private prototype_ `bool RemoveNoRefStreamingLODBiasOverride(FName QualityLevelName);`
- L601 _private prototype_ `TArray<FName> GetNoRefStreamingLODBiasOverrideNames() const;`
- L603 _private prototype_ `void OnNumStreamedLODsChanged(int32 NewValue, FName Platform);`
- L604 _private prototype_ `void OnNumStreamedLODsCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName Platform);`
- L605 _private prototype_ `int32 GetNumStreamedLODs(FName Platform) const;`
- L606 _private prototype_ `TSharedRef<SWidget> GetNumStreamedLODsWidget(FName PlatformGroupName) const;`
- L607 _private prototype_ `bool AddNumStreamedLODsPlatformOverride(FName PlatformGroupName);`
- L608 _private prototype_ `bool RemoveNumStreamedLODsPlatformOverride(FName PlatformGroupName);`
- L609 _private prototype_ `TArray<FName> GetNumStreamedLODsPlatformOverrideNames() const;`
- L611 _private prototype_ `bool CanRemoveLOD(int32 LODIndex) const;`
- L612 _private prototype_ `FReply OnRemoveLOD(int32 LODIndex);`
- L614 _private prototype_ `float GetLODScreenSize(FName PlatformGroupName, int32 LODIndex)const;`
- L615 _private prototype_ `FText GetLODScreenSizeTitle(int32 LODIndex) const;`
- L616 _private prototype_ `bool CanChangeLODScreenSize() const;`
- L617 _private prototype_ `TSharedRef<SWidget> GetLODScreenSizeWidget(FName PlatformGroupName, int32 LODIndex) const;`
- L618 _private prototype_ `TArray<FName> GetLODScreenSizePlatformOverrideNames(int32 LODIndex) const;`
- L619 _private prototype_ `bool AddLODScreenSizePlatformOverride(FName PlatformGroupName, int32 LODIndex);`
- L620 _private prototype_ `bool RemoveLODScreenSizePlatformOverride(FName PlatformGroupName, int32 LODIndex);`
- L621 _private prototype_ `void OnLODScreenSizeChanged(float NewValue, FName PlatformGroupName, int32 LODIndex);`
- L622 _private prototype_ `void OnLODScreenSizeCommitted(float NewValue, ETextCommit::Type CommitType, FName PlatformGroupName, int32 LODIndex);`
- L623 _private prototype_ `float GetScreenSizeWidgetWidth(int32 LODIndex) const;`
- L625 _private prototype_ `FString GetSourceImportFilename(int32 LODIndex) const;`
- L626 _private prototype_ `void SetSourceImportFilename(const FString& SourceFileName, int32 LODIndex) const;`
- L628 _private prototype_ `void OnBuildSettingsExpanded(bool bIsExpanded, int32 LODIndex);`
- L629 _private prototype_ `void OnReductionSettingsExpanded(bool bIsExpanded, int32 LODIndex);`
- L630 _private prototype_ `void OnSectionSettingsExpanded(bool bIsExpanded, int32 LODIndex);`
- L631 _private prototype_ `void OnLODGroupChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L632 _private prototype_ `bool IsAutoLODEnabled() const;`
- L633 _private prototype_ `ECheckBoxState IsAutoLODChecked() const;`
- L634 _private prototype_ `void OnAutoLODChanged(ECheckBoxState NewState);`
- L635 _private prototype_ `void OnImportLOD(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);`
- L636 _private prototype_ `void UpdateLODNames();`
- L637 _private prototype_ `FText GetLODCountTooltip() const;`
- L638 _private prototype_ `FText GetMinLODTooltip() const;`
- L639 _private prototype_ `FText GetNoRefStreamingLODBiasTooltip() const;`
- L640 _private prototype_ `FText GetNumStreamedLODsTooltip() const;`
- L642 _private prototype_ `FText GetLODCustomModeNameContent(int32 LODIndex) const;`
- L643 _private prototype_ `ECheckBoxState IsLODCustomModeCheck(int32 LODIndex) const;`
- L644 _private prototype_ `void SetLODCustomModeCheck(ECheckBoxState NewState, int32 LODIndex);`
- L645 _private prototype_ `bool IsLODCustomModeEnable(int32 LODIndex) const;`
- L647 _private prototype_ `TSharedRef<SWidget> OnGenerateLodComboBoxForLodPicker();`
- L648 _private prototype_ `EVisibility LodComboBoxVisibilityForLodPicker() const;`
- L649 _private prototype_ `bool IsLodComboBoxEnabledForLodPicker() const;`
- L650 _private prototype_ `TSharedRef<SWidget> OnGenerateLodMenuForLodPicker();`
- L651 _private prototype_ `FText GetCurrentLodName() const;`
- L652 _private prototype_ `FText GetCurrentLodTooltip() const;`
- L657 _private member_ `FStaticMeshEditor& StaticMeshEditor;` — The Static Mesh Editor this tool is associated with.
- L660 _private member_ `TArray<FName> LODGroupNames;` — LOD group options.
- L661 _private member_ `TArray<TSharedPtr<FString> > LODGroupOptions;`
- L664 _private member_ `TArray<TSharedPtr<FString> > LODNames;` — LOD import options
- L667 _private member_ `TSharedPtr<FMeshReductionSettingsLayout> ReductionSettingsWidgets[MAX_STATIC_MESH_LODS];` — Simplification options for each LOD level (in the LOD Chain tool).
- L668 _private member_ `TSharedPtr<FMeshBuildSettingsLayout> BuildSettingsWidgets[MAX_STATIC_MESH_LODS];`
- L669 _private member_ `TSharedPtr<FMeshSectionSettingsLayout> SectionSettingsWidgets[MAX_STATIC_MESH_LODS];`
- L671 _private member_ `TSharedPtr<FMeshMaterialsLayout> MaterialsLayoutWidget;`
- L674 _private member_ `TSharedPtr<STextComboBox> LODGroupComboBox;` — ComboBox widget for the LOD Group property
- L677 _private member_ `FPerPlatformFloat LODScreenSizes[MAX_STATIC_MESH_LODS];` — The display factors at which LODs swap
- L680 _private member_ `int32 LODCount;` — Helper value that corresponds to the 'Number of LODs' spinbox.
- L684 _private member_ `bool bBuildSettingsExpanded[MAX_STATIC_MESH_LODS];` — Whether certain parts of the UI are expanded so changes persist across recreating the UI.
- L685 _private member_ `bool bReductionSettingsExpanded[MAX_STATIC_MESH_LODS];`
- L686 _private member_ `bool bSectionSettingsExpanded[MAX_STATIC_MESH_LODS];`
- L688 _private member_ `TArray<class IDetailCategoryBuilder*> LodCategories;`
- L689 _private member_ `IDetailCategoryBuilder* LodCustomCategory;`
- L691 _private member_ `bool DetailDisplayLODs[MAX_STATIC_MESH_LODS];`
- L693 _private member_ `FDelegateHandle OnAssetPostLODImportDelegateHandle;`

#### class `FRayTracingProxySettingsLayout`  
`class FRayTracingProxySettingsLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FRayTracingProxySettingsLayout>`  
_L699-749_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FRayTracingProxySettingsLayout>`
- desc: Window for Ray Tracing Proxy settings.
- L702 _public prototype_ `FRayTracingProxySettingsLayout(FStaticMeshEditor& StaticMeshEditor);`
- L703 _public prototype_ `virtual ~FRayTracingProxySettingsLayout();`
- L705 _public prototype_ `const FMeshRayTracingProxySettings& GetSettings() const;`
- L706 _public prototype_ `void UpdateSettings(const FMeshRayTracingProxySettings& InSettings);`
- L709 _public prototype_ `bool IsApplyNeeded() const;` — Returns true if settings have been changed and an Apply is needed to update the asset.
- L712 _public prototype_ `void ApplyChanges();` — Apply current Nanite settings to the mesh.
- L715 _private prototype_ `FReply OnApply();`
- L717 _private prototype_ `ECheckBoxState IsEnabledChecked() const;`
- L718 _private prototype_ `void OnEnabledChanged(ECheckBoxState NewState);`
- L720 _private prototype_ `float GetFallbackPercentTriangles() const;`
- L721 _private prototype_ `void OnFallbackPercentTrianglesChanged(float NewValue);`
- L722 _private prototype_ `void OnFallbackPercentTrianglesCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L724 _private prototype_ `float GetFallbackRelativeError() const;`
- L725 _private prototype_ `void OnFallbackRelativeErrorChanged(float NewValue);`
- L726 _private prototype_ `void OnFallbackRelativeErrorCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L728 _private prototype_ `float GetFoliageOverOcclusionBias() const;`
- L729 _private prototype_ `void OnFoliageOverOcclusionBiasChanged(float NewValue);`
- L730 _private prototype_ `void OnFoliageOverOcclusionBiasCommitted(float NewValue, ETextCommit::Type TextCommitType);`
- L732 _private prototype_ `bool ShouldEnable() const;`
- L733 _private prototype_ `bool CanToggleEnabled() const;`
- L736 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L737 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L738 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L739 _private function_ `virtual void Tick(float DeltaTime) override`
- L740 _private function_ `virtual bool RequiresTick() const override`
- L741 _private function_ `virtual FName GetName() const override`
- L742 _private function_ `virtual bool InitiallyCollapsed() const override`
- L746 _private member_ `FStaticMeshEditor& StaticMeshEditor;` — The Static Mesh Editor this tool is associated with.
- L748 _private member_ `FMeshRayTracingProxySettings RayTracingProxySettings;`

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorViewportClient.h` (Private)


#### class `FStaticMeshEditorViewportClient`  
`class FStaticMeshEditorViewportClient : public FEditorViewportClient, public TSharedFromThis<FStaticMeshEditorViewportClient>`  
_L21-237_
- inherits: `FEditorViewportClient,TSharedFromThis<FStaticMeshEditorViewportClient>`
- desc: Viewport Client for the preview viewport
- L24 _public prototype_ `FStaticMeshEditorViewportClient(TWeakPtr<IStaticMeshEditor> InStaticMeshEditor, const TSharedRef<SStaticMeshEditorViewport>& InStaticMeshEditorViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene, UStaticMesh* InPreviewStaticMesh, UStaticMeshComponent* InPreviewStaticMeshComponent);`
- L25 _public prototype_ `~FStaticMeshEditorViewportClient();`
- L28 _public prototype_ `virtual void MouseMove(FViewport* Viewport,int32 x, int32 y) override;` — FEditorViewportClient interface
- L29 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L30 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& Args) override;`
- L31 _public prototype_ `virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L32 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L33 _public prototype_ `virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;`
- L34 _public prototype_ `virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;`
- L35 _public prototype_ `virtual bool InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale ) override;`
- L36 _public prototype_ `virtual void TrackingStarted( const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge ) override;`
- L37 _public prototype_ `virtual void TrackingStopped() override;`
- L38 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L39 _public prototype_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;`
- L40 _public prototype_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;`
- L41 _public prototype_ `virtual bool CanCycleWidgetMode() const override;`
- L42 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L43 _public prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L44 _public prototype_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override;`
- L45 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L47 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L48 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L56 _public prototype_ `void SetPreviewMesh(UStaticMesh* InStaticMesh, UStaticMeshComponent* InPreviewStaticMeshComponent, bool bResetCamera=true);` — Updates the static mesh and static mesh component being used in the Static Mesh Editor. @param	InStaticMesh				The static mesh handled by the editor. @param	InStaticMeshComponent		The static mesh component component from the viewport's scene.
- L59 _public prototype_ `TSet< int32 >& GetSelectedEdges();` — Retrieves the selected edge set.
- L62 _public prototype_ `void OnMeshChanged();` — Called when the mesh changes
- L69 _public prototype_ `void OnSocketSelectionChanged( UStaticMeshSocket* SelectedSocket );` — Called when the selected socket changes @param SelectedSocket	The newly selected socket or NULL if no socket is selected
- L78 _public prototype_ `void DrawUVsForMesh(FViewport* InViewport, FCanvas* InCanvas, int32 InTextYPos );` — Draws the UV overlay for the current LOD. @param	InViewport					The viewport to draw to @param	InCanvas					The canvas to draw to @param	InTextYPos					The Y-position to begin drawing the UV-Overlay at (due to text displayed above it).
- L81 _public prototype_ `void ToggleDrawUVOverlay();` — Callback for toggling the UV overlay show flag.
- L83 _public prototype_ `void SetDrawUVOverlay(bool bShouldDraw);`
- L86 _public prototype_ `bool IsDrawUVOverlayChecked() const;` — Callback for checking the UV overlay show flag.
- L90 _public prototype_ `void SetShowNormals(bool bShowOn);` — Set the normals show flag.
- L93 _public prototype_ `void SetShowTangents(bool bShowOn);` — Set the tangents show flag.
- L96 _public prototype_ `void SetShowBinormals(bool bShowOn);` — Set the binormals show flag.
- L99 _public prototype_ `void SetShowSimpleCollisions(bool bShowOn);` — Set the simple collisions show flag.
- L102 _public prototype_ `void SetShowComplexCollisions(bool bShowOn);` — Set the complex collisions show flag.
- L105 _public prototype_ `void SetShowPivots(bool bShowOn);` — Set the pivots show flag.
- L108 _public prototype_ `void SetShowGrids(bool bShowOn);` — Set the grids show flag.
- L111 _public prototype_ `void SetShowVertices(bool bShowOn);` — Set the vertices show flag.
- L114 _public prototype_ `void SetShowWireframes(bool bShowOn);` — Set the wireframes show flag.
- L117 _public prototype_ `void SetShowVertexColors(bool bShowOn);` — Set the vertex colors show flag.
- L120 _public prototype_ `void ToggleShowNormals();` — Callback for toggling the normals show flag.
- L123 _public prototype_ `bool IsShowNormalsChecked() const;` — Callback for checking the normals show flag.
- L126 _public prototype_ `void ToggleShowTangents();` — Callback for toggling the tangents show flag.
- L129 _public prototype_ `bool IsShowTangentsChecked() const;` — Callback for checking the tangents show flag.
- L132 _public prototype_ `void ToggleShowBinormals();` — Callback for toggling the binormals show flag.
- L135 _public prototype_ `bool IsShowBinormalsChecked() const;` — Callback for checking the binormals show flag.
- L138 _public prototype_ `void ToggleShowSimpleCollision();` — Callback for toggling simple collision drawing.
- L141 _public prototype_ `bool IsShowSimpleCollisionChecked() const;` — Callback for checking simple collision drawing.
- L144 _public prototype_ `void ToggleShowComplexCollision();` — Callback for toggling complex collision drawing.
- L147 _public prototype_ `bool IsShowComplexCollisionChecked() const;` — Callback for checking complex collision drawing.
- L150 _public prototype_ `void ToggleShowSockets();` — Callback for toggling the socket show flag.
- L153 _public prototype_ `bool IsShowSocketsChecked() const;` — Callback for checking the socket show flag.
- L156 _public prototype_ `void ToggleShowPivot();` — Callback for toggling the pivot show flag.
- L159 _public prototype_ `bool IsShowPivotChecked() const;` — Callback for checking the pivot show flag.
- L162 _public prototype_ `void ToggleDrawAdditionalData();` — Callback for toggling the additional data drawing flag.
- L165 _public prototype_ `bool IsDrawAdditionalDataChecked() const;` — Callback for checking the additional data drawing flag.
- L168 _public prototype_ `void ToggleDrawVertices();` — Callback for toggling the vertices drawing flag.
- L171 _public prototype_ `bool IsDrawVerticesChecked() const;` — Callback for checking the vertices drawing flag.
- L174 _public prototype_ `void SetFloorAndEnvironmentVisibility(const bool bVisible);` — Used to toggle the floor when vertex colours should be shown
- L177 _protected prototype_ `virtual void PerspectiveCameraMoved() override;` — FEditorViewportClient interface
- L180 _protected prototype_ `void UpdateSimpleCollisionDisplay();` — Used to update the display of simple collision
- L182 _protected prototype_ `void UpdateComplexCollisionDisplay();` — Used to update the display of complex collision
- L184 _private prototype_ `bool IsCustomModeUsingWidget() const;`
- L186 _private prototype_ `void BeginManipulation(bool bDuplicate);`
- L189 _private member_ `UTexture2D* SimplygonLogo;` — The Simplygon logo to be drawn when Simplygon has been used on the static mesh.
- L192 _private member_ `UStaticMeshComponent* StaticMeshComponent;` — Component for the static mesh.
- L195 _private member_ `UStaticMesh* StaticMesh;` — The static mesh being used in the editor.
- L197 _private member_ `FTriMeshCollisionData CollisionMeshData;`
- L200 _private member_ `TWeakPtr<IStaticMeshEditor> StaticMeshEditorPtr;` — Pointer back to the StaticMesh editor tool that owns us
- L203 _private member_ `bool bDrawUVs;` — Flags for various options in the editor.
- L204 _private member_ `bool bShowSimpleCollision;`
- L205 _private member_ `bool bShowComplexCollision;`
- L206 _private member_ `bool bShowSockets;`
- L207 _private member_ `bool bDrawNormals;`
- L208 _private member_ `bool bDrawTangents;`
- L209 _private member_ `bool bDrawBinormals;`
- L210 _private member_ `bool bShowPivot;`
- L211 _private member_ `bool bDrawAdditionalData;`
- L212 _private member_ `bool bDrawVertices;`
- L215 _private member_ `bool bManipulating;` — true when the user is manipulating a socket widget.
- L217 _private member_ `UE::Widget::EWidgetMode WidgetMode;`
- L220 _private member_ `EAxis::Type SocketManipulateAxis;` — The current widget axis the mouse is highlighting.
- L223 _private typedef_ `typedef TSet< int32 > FSelectedEdgeSet;` — Holds the currently selected edges.
- L224 _private member_ `FSelectedEdgeSet SelectedEdgeIndices;`
- L227 _private member_ `TArray<FVector> SelectedEdgeVertices;` — Cached vertex positions for the currently selected edges. Used for rendering
- L230 _private member_ `TArray<FVector2D> SelectedEdgeTexCoords[MAX_STATIC_TEXCOORDS];` — Cached tex coords for the currently selected edges. Used for rendering UV coordinates
- L233 _private member_ `TWeakPtr<SStaticMeshEditorViewport> StaticMeshEditorViewportPtr;` — Pointer back to the StaticMeshEditor viewport control that owns us
- L236 _private member_ `FAdvancedPreviewScene* AdvancedPreviewScene;` — Stored pointer to the preview scene in which the static mesh is shown

### `Source/Editor/StaticMeshEditor/Private/StaticMeshEditorViewportToolbarSections.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StaticMeshEditor` (scope `UE`)
- L13 _prototype_ `FToolMenuEntry CreateLODSubmenu();` (scope `UE::StaticMeshEditor`)
- L14 _prototype_ `FToolMenuEntry CreateShowSubmenu();` (scope `UE::StaticMeshEditor`)
- L15 _prototype_ `FToolMenuEntry CreateAspectRatioSubmenu();` (scope `UE::StaticMeshEditor`)
- L17 _prototype_ `TSharedRef<SWidget> GenerateLODMenuWidget(const TSharedPtr<SStaticMeshEditorViewport>& InStaticMeshEditorViewport);` (scope `UE::StaticMeshEditor`)
- L18 _prototype_ `TSharedRef<SWidget> GenerateShowMenuWidget(const TSharedPtr<SStaticMeshEditorViewport>& InStaticMeshEditorViewport);` (scope `UE::StaticMeshEditor`)
- L20 _prototype_ `void FillShowSubmenu(UToolMenu *InMenu);` (scope `UE::StaticMeshEditor`)
- L21 _prototype_ `void FillAspectRatioSubmenu(UToolMenu* InMenu);` (scope `UE::StaticMeshEditor`)
- L23 _prototype_ `FText GetLODMenuLabel(const TSharedPtr<SStaticMeshEditorViewport>& InStaticMeshEditorViewport);` (scope `UE::StaticMeshEditor`)
- L25 _prototype_ `void ExtendViewModesSubmenu(FName InViewModesSubmenuName);` (scope `UE::StaticMeshEditor`)

### `Source/Editor/StaticMeshEditor/Private/StaticMeshViewportLODCommands.h` (Private)


#### class `FStaticMeshViewportLODCommands`  
`class FStaticMeshViewportLODCommands : public TCommands<FStaticMeshViewportLODCommands>`  
_L18-41_
- inherits: `TCommands<FStaticMeshViewportLODCommands>`
- desc: Class containing commands for static mesh editor viewport LOD actions
- L21 _public function_ `FStaticMeshViewportLODCommands() : TCommands<FStaticMeshViewportLODCommands> ( TEXT("StaticMeshViewportLODCmd"),`
- L33 _public member_ `TSharedPtr< FUICommandInfo > LODAuto;` — LOD Auto
- L36 _public member_ `TSharedPtr< FUICommandInfo > LOD0;` — LOD 0
- L40 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Source/Editor/StaticMeshEditor/Public/IStaticMeshEditor.h` (Public)


#### class `IStaticMeshEditor`  
`class IStaticMeshEditor : public FAssetEditorToolkit`  
_L23-363_
- inherits: `FAssetEditorToolkit`
- desc: Public interface to Static Mesh Editor
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPostUndoMulticaster);` — Called after an undo is performed to give child widgets a chance to refresh.
- L49 _public typedef_ `typedef FOnPostUndoMulticaster::FDelegate FOnPostUndo;` — Post undo
- L52 _public prototype_ `virtual UStaticMesh* GetStaticMesh() = 0;` — Retrieves the current static mesh displayed in the Static Mesh Editor.
- L55 _public prototype_ `virtual UStaticMeshComponent* GetStaticMeshComponent() const = 0;` — Retrieves the static mesh component.
- L59 _public prototype_ `virtual UStaticMeshSocket* GetSelectedSocket() const = 0;` — `UE_DEPRECATED(5.6, "GetSelectedSocket is deprecated, use GetSelectedSockets instead.")` — Retrieves the first currently selected socket from the Socket Manager.
- L62 _public prototype_ `virtual TArray<UStaticMeshSocket*> GetSelectedSockets() const = 0;` — Retrieves the currently selected sockets from the Socket Manager.
- L65 _public prototype_ `virtual bool HasSelectedSockets() const = 0;` — Returns true if at least one socket is selected.
- L72 _public prototype_ `virtual void SetSelectedSocket(UStaticMeshSocket* InSelectedSocket) = 0;` — Set the currently selected socket in the Socket Manager. @param	InSelectedSocket			The selected socket to pass on to the Socket Manager.
- L79 _public prototype_ `virtual void AddSelectedSocket(UStaticMeshSocket* InSelectedSocket) = 0;` — Adds a socket to the currently selected sockets in the Socket Manager. @param	InSelectedSocket		The socket to add to the current selection in the Socket Manager.
- L86 _public prototype_ `virtual void RemoveSelectedSocket(const UStaticMeshSocket* InSelectedSocket) = 0;` — Removes a socket form the currently selected sockets in the Socket Manager. @param	InSelectedSocket		The socket to removed from the current selection in the Socket Manager.
- L90 _public prototype_ `virtual void DuplicateSelectedSocket() = 0;` — `UE_DEPRECATED(5.6, "DuplicateSelectedSocket is deprecated, use DuplicateSelectedSockets instead.")` — Duplicate the first selected socket
- L93 _public prototype_ `virtual void DuplicateSelectedSockets() = 0;` — Duplicate the selected sockets
- L96 _public prototype_ `virtual void RequestRenameSelectedSocket() = 0;` — Requests to rename selected socket
- L103 _public prototype_ `virtual bool IsPrimValid(const FPrimData& InPrimData) const = 0;` — Checks to see if the prim data is valid compared with the static mesh @param  InPrimData			The data to check
- L106 _public prototype_ `virtual bool HasSelectedPrims() const = 0;` — Checks to see if any prims are selected
- L109 _public prototype_ `virtual const TArray<FPrimData>& GetSelectedPrims() const = 0;` — Get selected prims
- L117 _public prototype_ `virtual void AddSelectedPrim(const FPrimData& InPrimData, bool bClearSelection) = 0;` — Adds primitive information to the selected prims list @param  InPrimData			The data to add @param  bClearSelection		If true, clears the current selection
- L124 _public prototype_ `virtual void RemoveSelectedPrim(const FPrimData& InPrimData) = 0;` — Removes primitive information to the selected prims list @param  InPrimData			The data to remove
- L127 _public prototype_ `virtual void RemoveInvalidPrims() = 0;` — Removes all invalid primitives from the list
- L135 _public prototype_ `virtual bool IsSelectedPrim(const FPrimData& InPrimData) const = 0;` — Checks to see if the parsed primitive data is selected @param  InPrimData			The data to compare @returns					True, if the prim is selected
- L138 _public prototype_ `virtual void ClearSelectedPrims() = 0;` — Removes all primitive data from the list
- L145 _public prototype_ `virtual void DuplicateSelectedPrims(const FVector* InOffset) = 0;` — Duplicates all the selected primitives and selects them @param  InOffset			[optional] Allows the duplicate to be offset by this factor
- L150 _public prototype_ `virtual int32 CopySelectedPrims() const = 0;` — Copy all the selected primitives to clipboard
- L155 _public prototype_ `virtual int32 PasteCopiedPrims() = 0;` — Paste all the selected primitives from clipboard
- L162 _public prototype_ `virtual void TranslateSelectedPrims(const FVector& InDrag) = 0;` — Translates the selected primitives by the specified amount @param  InDrag				The amount to translate
- L169 _public prototype_ `virtual void RotateSelectedPrims(const FRotator& InRot) = 0;` — Rotates the selected primitives by the specified amount @param  InRot				The amount to rotate
- L176 _public prototype_ `virtual void ScaleSelectedPrims(const FVector& InScale) = 0;` — Scales the selected primitives by the specified amount @param  InScale				The amount to scale
- L184 _public prototype_ `virtual bool CalcSelectedPrimsAABB(FBox& OutBox) const = 0;` — Calculates the bounding box of our selected primitives @param  OutBox				The bounding data for our selection @returns					True, if there are any prims selected
- L192 _public prototype_ `virtual bool GetLastSelectedPrimTransform(FTransform& OutTransform) const = 0;` — Fetches the transform of the last primitive to be selected @param  OutTransform		The transform of the last selected primitive @returns					True, if there was a prim selected
- L200 _public prototype_ `virtual FTransform GetPrimTransform(const FPrimData& InPrimData) const = 0;` — Gets the transform of the specified primitive @param  InPrimData			The data about the primitive @returns					The transform of the specified primitive
- L208 _public prototype_ `virtual void SetPrimTransform(const FPrimData& InPrimData, const FTransform& InPrimTransform) const = 0;` — Sets the transform of the specified primitive @param  InPrimData			The data about the primitive @param  InPrimTransform		The transform to apply to the primitive
- L216 _public prototype_ `virtual int32 GetNumTriangles(int32 LODLevel = 0) const = 0;` — Retrieves the number of triangles in the current static mesh or it's forced LOD. @param  LODLevel			The desired LOD to retrieve the number of triangles for. @returns					The number of triangles for the specified LOD level.
- L224 _public prototype_ `virtual int32 GetNumVertices(int32 LODLevel = 0) const = 0;` — Retrieves the number of vertices in the current static mesh or it's forced LOD. @param  LODLevel			The desired LOD to retrieve the number of vertices for. @returns					The number of vertices for the specified LOD level.
- L232 _public prototype_ `virtual int32 GetNumUVChannels(int32 LODLevel = 0) const = 0;` — Retrieves the number of UV channels available. @param  LODLevel			The desired LOD to retrieve the number of UV channels for. @returns					The number of triangles for the specified LOD level.
- L235 _public prototype_ `virtual int32 GetCurrentUVChannel() = 0;` — Retrieves the currently selected UV channel.
- L238 _public prototype_ `virtual int32 GetCurrentLODLevel() = 0;` — Retrieves the current LOD level. 0 is auto, 1 is base.
- L241 _public prototype_ `virtual int32 GetCurrentLODIndex() = 0;` — Retrieves the current LOD index
- L244 _public function_ `virtual int32 GetCustomData(const int32 Key) const` — Retrieve editor custom data. Return INDEX_NONE if the key is invalid
- L252 _public function_ `virtual void SetCustomData(const int32 Key, const int32 CustomData)` — Store the custom data using the key. Remark: The custom data memory should be clear when the editor is close by the user, this is not persistent data. Currently we use it to store the state of the editor UI to restore it properly when a refresh happen.
- L255 _public prototype_ `virtual void RefreshViewport() = 0;` — Refreshes the Static Mesh Editor's viewport.
- L258 _public prototype_ `virtual bool IsShowSimpleCollisionChecked() const = 0;` — Returns whether simple collision is currently shown in the viewport.
- L261 _public prototype_ `virtual void ToggleShowSimpleCollision() = 0;` — Toggles simple collision visibility in the viewport.
- L264 _public prototype_ `virtual void RefreshTool() = 0;` — Refreshes everything in the Static Mesh Editor.
- L273 _public prototype_ `virtual void DoDecomp(uint32 InHullCount, int32 InMaxHullVerts, uint32 InHullPrecision) = 0;` — This is called when Apply is pressed in the dialog. Does the actual processing. @param    InHullCount               The max number of convex hulls allowed @param    InMaxHullVerts            The max number of verts per hull allowed. @param    InHullPrecision           The voxel precision to use for V-HACD
- L277 _public prototype_ `virtual TSet< int32 >& GetSelectedEdges() = 0;` — Retrieves the selected edge set.
- L280 _public prototype_ `virtual void RegisterOnPostUndo(const FOnPostUndo& Delegate) = 0;` — Registers a delegate to be called after an Undo operation
- L283 _public prototype_ `virtual void UnregisterOnPostUndo(SWidget* Widget) = 0;` — Unregisters a delegate to be called after an Undo operation
- L286 _public prototype_ `virtual EViewModeIndex GetViewMode() const = 0;` — Get the active view mode
- L289 _public prototype_ `virtual void RegisterOnSelectedLODChanged(const FOnSelectedLODChanged& Delegate, bool UnregisterOnRefresh) = 0;` — Register callback to be able to be notify when the select LOD is change
- L291 _public prototype_ `virtual void UnRegisterOnSelectedLODChanged(FDelegateUserObject Thing) = 0;` — Unregister callback to free up the ressources
- L294 _public prototype_ `virtual void BroadcastOnSelectedLODChanged() = 0;` — Broadcast when selected LOD changes
- L297 _public prototype_ `virtual class FEditorViewportClient& GetViewportClient() = 0;` — Get the Static Mesh Editor's the viewport client
- L300 _public prototype_ `virtual void SetSecondaryToolbarDisplayName(FText DisplayName) = 0;` — Set the display name for the secondary toolbar and its associated menu item
- L302 _public function_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FStaticMeshEditorDockingExtentionTabsEvent, const TSharedRef<FTabManager::FStack>&) virtual FStaticMeshEditorDockingExtentionTabsEvent& OnStaticMeshEditorDockingExtentionTabs()`
- L305 _public prototype_ `DECLARE_EVENT(IStaticMeshEditor, FStaticMeshEditorClosedEvent);`
- L306 _public function_ `virtual FStaticMeshEditorClosedEvent& OnStaticMeshEditorClosed()`
- L309 _public prototype_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FRegisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being registered
- L310 _public function_ `virtual FRegisterTabSpawnersEvent& OnRegisterTabSpawners()`
- L313 _public prototype_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FUnregisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being unregistered
- L314 _public function_ `virtual FUnregisterTabSpawnersEvent& OnUnregisterTabSpawners()`
- L316 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAddSaveAssetValidator, FString&);`
- L317 _public function_ `virtual FDelegateHandle AddSaveAssetValidator(const FAddSaveAssetValidator& Validator)`
- L324 _public function_ `virtual bool RemoveSaveAssetValidator(const FDelegateHandle& ValidatorHandle)`
- L331 _protected function_ `virtual void SaveAsset_Execute() override`
- L357 _private member_ `FStaticMeshEditorDockingExtentionTabsEvent StaticMeshEditorDockingExtentionTabsEvent;`
- L358 _private member_ `FStaticMeshEditorClosedEvent StaticMeshEditorClosedEvent;`
- L359 _private member_ `FRegisterTabSpawnersEvent RegisterTabSpawnersEvent;`
- L360 _private member_ `FUnregisterTabSpawnersEvent UnregisterTabSpawnersEvent;`
- L362 _private member_ `TMap<FDelegateHandle, FAddSaveAssetValidator> SaveAssetValidators;`

#### struct `IStaticMeshEditor::FPrimData`  
`struct FPrimData`  
_L29-43_
- desc: Primitive data use to track which aggregate geometry is selected
- L31 _public member_ `EAggCollisionShape::Type PrimType;`
- L32 _public member_ `int32 PrimIndex;`
- L34 _public function_ `FPrimData(EAggCollisionShape::Type InPrimType, int32 InPrimIndex) : PrimType(InPrimType), PrimIndex(InPrimIndex)`
- L39 _public function_ `bool operator==(const FPrimData& Other) const`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedLODChangedMulticaster);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedLODChangedMulticaster);`
- L18 _typedef_ `typedef FOnSelectedLODChangedMulticaster::FDelegate FOnSelectedLODChanged;`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPostUndoMulticaster);` — Called after an undo is performed to give child widgets a chance to refresh.
- L302 _delegate_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FStaticMeshEditorDockingExtentionTabsEvent, const TSharedRef<FTabManager::FStack>&) virtual FStaticMeshEditorDockingExtentionTabsEvent& OnStaticMeshEditorDockingExtentionTabs() { return StaticMeshEditorDockingExtentionTabsEvent; };`
- L305 _delegate_ `DECLARE_EVENT(IStaticMeshEditor, FStaticMeshEditorClosedEvent);`
- L309 _delegate_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FRegisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being registered
- L313 _delegate_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FUnregisterTabSpawnersEvent, const TSharedRef<class FTabManager>&);` — Delegate to be called when the tabs are being unregistered
- L316 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAddSaveAssetValidator, FString&);`

### `Source/Editor/StaticMeshEditor/Public/StaticMeshEditorActions.h` (Public)


#### class `FStaticMeshEditorCommands`  
`class FStaticMeshEditorCommands : public TCommands<FStaticMeshEditorCommands>`  
_L19-124_
- inherits: `TCommands<FStaticMeshEditorCommands>`
- desc: Unreal StaticMesh editor actions
- L23 _public function_ `FStaticMeshEditorCommands() : TCommands<FStaticMeshEditorCommands> ( "StaticMeshEditor",`
- L38 _public member_ `TSharedPtr<FUICommandInfo> SetShowNaniteFallback;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> SetShowDistanceField;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SetShowRayTracingFallback;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> SetShowWireframe;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> SetShowVertexColor;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> SetShowPhysicalMaterialMasks;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> SetDrawUVs;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> SetShowGrid;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> SetShowBounds;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> SetShowSimpleCollision;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> SetShowComplexCollision;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> ResetCamera;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> SetShowSockets;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> SetDrawAdditionalData;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> ReimportMesh;` — Mesh toolbar Commands
- L55 _public member_ `TSharedPtr<FUICommandInfo> ReimportMeshWithNewFile;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMesh;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMeshWithNewFile;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> ReimportMeshWithDialog;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> ReimportMeshWithNewFileWithDialog;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMeshWithDialog;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> ReimportAllMeshWithNewFileWithDialog;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowNormals;` — toolbar commands
- L65 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowTangents;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowBinormals;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowPivots;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowVertices;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowGrids;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowBounds;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowSimpleCollisions;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowComplexCollisions;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowSockets;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowWireframes;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowVertexColors;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> SetShowNormals;` — View Menu Commands
- L79 _public member_ `TSharedPtr<FUICommandInfo> SetShowTangents;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> SetShowBinormals;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> SetShowPivot;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> SetShowVertices;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> CreateDOP10X;` — Collision Menu Commands
- L86 _public member_ `TSharedPtr<FUICommandInfo> CreateDOP10Y;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> CreateDOP10Z;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> CreateDOP18;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> CreateDOP26;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> CreateBoxCollision;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> CreateSphereCollision;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> CreateSphylCollision;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> CreateAutoConvexCollision;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> RemoveCollision;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> ConvertBoxesToConvex;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> CopyCollisionFromSelectedMesh;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> FindSource;` — Mesh Menu Commands
- L101 _public member_ `TSharedPtr<FUICommandInfo> ChangeMesh;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> BakeMaterials;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> SaveGeneratedLODs;`
- L109 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_Free;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_Platform;`
- L111 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_6_13;`
- L112 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_13_6;`
- L113 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_1_1;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_4_3;`
- L115 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_16_10;`
- L116 _public member_ `TSharedPtr<FUICommandInfo> SetAspectRatio_16_9;`
- L121 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/StaticMeshEditor/Public/StaticMeshEditorModule.h` (Public)


#### class `IStaticMeshEditorModule`  
`class IStaticMeshEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L17-40_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Static mesh editor module interface
- L24 _public prototype_ `virtual TSharedRef<IStaticMeshEditor> CreateStaticMeshEditor( const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UStaticMesh* StaticMesh ) = 0;` — Creates a new static mesh editor.
- L27 _public prototype_ `DECLARE_EVENT_OneParam(IStaticMeshEditorModule, FStaticMeshEditorOpenedEvent, TWeakPtr<IStaticMeshEditor>);` — Delegate to be called when a Material Editor is created, for toolbar, tab, and menu extension
- L28 _public function_ `virtual FStaticMeshEditorOpenedEvent& OnStaticMeshEditorOpened()`
- L30 _public prototype_ `virtual TSharedPtr<FExtensibilityManager> GetSecondaryToolBarExtensibilityManager() = 0;`
- L32 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FStaticMeshEditorToolbarExtender, const TSharedRef<FUICommandList>, TSharedRef<IStaticMeshEditor>);`
- L33 _public prototype_ `virtual TArray<FStaticMeshEditorToolbarExtender>& GetAllStaticMeshEditorToolbarExtenders() = 0;`
- L35 _public prototype_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L36 _public prototype_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions() = 0;`
- L39 _private member_ `FStaticMeshEditorOpenedEvent StaticMeshEditorOpenedEvent;`

#### Free symbols / members of external scopes

- L12 _externvar_ `extern const FName StaticMeshEditorAppIdentifier;`
- L27 _delegate_ `DECLARE_EVENT_OneParam(IStaticMeshEditorModule, FStaticMeshEditorOpenedEvent, TWeakPtr<IStaticMeshEditor>);` — Delegate to be called when a Material Editor is created, for toolbar, tab, and menu extension
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<FExtender>, FStaticMeshEditorToolbarExtender, const TSharedRef<FUICommandList>, TSharedRef<IStaticMeshEditor>);`
- L35 _delegate_ `DECLARE_EVENT_OneParam(IStaticMeshEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`

### `Source/Editor/StaticMeshEditor/Public/StaticMeshEditorSubsystem.h` (Public)


#### class `UStaticMeshEditorSubsystem`  
`class UStaticMeshEditorSubsystem : public UEditorSubsystem`  
_L25-640_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: UStaticMeshEditorSubsystem Subsystem for exposing static mesh functionality to scripts
- L30 _public prototype_ `UStaticMeshEditorSubsystem();`
- L45 _public prototype_ `int32 SetLodsWithNotification(UStaticMesh* StaticMesh, const FStaticMeshReductionOptions& ReductionOptions, bool bApplyChanges);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Remove then add LODs on a static mesh. The static mesh must have at least LOD 0. The LOD 0 of the static mesh is kept after removal. The build settings of LOD 0 will be applied to all subsequent LODs. @param	StaticMesh				Mesh to process. @param	ReductionOptions		Options on how to generate LODs on the mesh. @param	bApplyChanges				Indicates if change must be notified. @return the number of LODs generated on the input mesh. An negative value indicates that the reduction could not be performed. See log for explanation. No action will be performed if ReductionOptions.ReductionSettings is empty
- L51 _public function_ `int32 SetLods(UStaticMesh* StaticMesh, const FStaticMeshReductionOptions& ReductionOptions)` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Same as SetLodsWithNotification but changes are applied.
- L63 _public prototype_ `void GetLodReductionSettings(const UStaticMesh* StaticMesh, const int32 LodIndex, FMeshReductionSettings& OutReductionOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Copy the reduction options with the specified LOD reduction settings. @param StaticMesh - Mesh to process. @param LodIndex - The LOD we get the reduction settings. @param OutReductionOptions - The reduction settings where we copy the reduction options.
- L72 _public prototype_ `void SetLodReductionSettings(UStaticMesh* StaticMesh, const int32 LodIndex, const FMeshReductionSettings& ReductionOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Set the LOD reduction for the specified LOD index. @param StaticMesh - Mesh to process. @param LodIndex - The LOD we will apply the reduction settings. @param ReductionOptions - The reduction settings we want to apply to the LOD.
- L81 _public prototype_ `void GetLodBuildSettings(const UStaticMesh* StaticMesh, const int32 LodIndex, FMeshBuildSettings& OutBuildOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Copy the build options with the specified LOD build settings. @param StaticMesh - Mesh to process. @param LodIndex - The LOD we get the reduction settings. @param OutBuildOptions - The build settings where we copy the build options.
- L90 _public prototype_ `void SetLodBuildSettings(UStaticMesh* StaticMesh, const int32 LodIndex, const FMeshBuildSettings& BuildOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Set the LOD build options for the specified LOD index. @param StaticMesh - Mesh to process. @param LodIndex - The LOD we will apply the build settings. @param BuildOptions - The build settings we want to apply to the LOD.
- L98 _public prototype_ `FName GetLODGroup(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable,Category = "Editor Scripting | StaticMesh")` — Get the LODGroup for the specified static mesh @param StaticMesh @return LODGroup
- L108 _public prototype_ `bool SetLODGroup(UStaticMesh* StaticMesh, FName LODGroup, bool bRebuildImmediately=true);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Set the LODGroup for the specified static mesh @param StaticMesh - Mesh to process. @param LODGroup - Name of the LODGroup to apply @param bRebuildImmediately - If true, rebuild the static mesh immediately @return Success
- L120 _public prototype_ `int32 ImportLOD(UStaticMesh* BaseStaticMesh, const int32 LODIndex, const FString& SourceFilename);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Import or re-import a LOD into the specified base mesh. If the LOD do not exist it will import it and add it to the base static mesh. If the LOD already exist it will re-import the specified LOD. @param BaseStaticMesh: The static mesh we import or re-import a LOD. @param LODIndex: The index of the LOD to import or re-import. Valid value should be between 0 and the base static mesh LOD number. Invalid value will return INDEX_NONE @param SourceFilename: The fbx source filename. If we are re-importing an existing LOD, it can be empty in this case it will use the last import file. Otherwise it must be an existing fbx file. @return the index of the LOD that was imported or re-imported. Will return INDEX_NONE if anything goes bad.
- L130 _public prototype_ `bool ReimportAllCustomLODs(UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh", meta=(ScriptName="ReimportAllCustomLods;ReimportAllCustomLODs"))` — Re-import all the custom LODs present in the specified static mesh. @param StaticMesh: is the static mesh we import or re-import all LODs. @return true if re-import all LODs works, false otherwise see log for explanation.
- L143 _public prototype_ `int32 SetLodFromStaticMesh(UStaticMesh* DestinationStaticMesh, int32 DestinationLodIndex, UStaticMesh* SourceStaticMesh, int32 SourceLodIndex, bool bReuseExistingMaterialSlots);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Adds or create a LOD at DestinationLodIndex using the geometry from SourceStaticMesh SourceLodIndex @param	DestinationStaticMesh		The static mesh to set the LOD in. @param	DestinationLodIndex			The index of the LOD to set. @param	SourceStaticMesh			The static mesh to get the LOD from. @param	SourceLodIndex				The index of the LOD to get. @param	bReuseExistingMaterialSlots	If true, sections from SourceStaticMesh will be remapped to match the material slots of DestinationStaticMesh when they have the same material assigned. If false, all material slots of SourceStaticMesh will be appended in DestinationStaticMesh. @return	The index of the LOD that was set. It can be different than DestinationLodIndex if it wasn't a valid index. A negative value indicates that the LOD was not set. See log for explanation.
- L152 _public prototype_ `int32 GetLodCount(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Get number of LODs present on a static mesh. @param	StaticMesh				Mesh to process. @return the number of LODs present on the input mesh. An negative value indicates that the command could not be executed. See log for explanation.
- L160 _public prototype_ `bool RemoveLods(UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Remove LODs on a static mesh except LOD 0. @param	StaticMesh			Mesh to remove LOD from. @return A boolean indicating if the removal was successful, true, or not.
- L168 _public prototype_ `TArray<float> GetLodScreenSizes(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Get an array of LOD screen sizes for evaluation. @param	StaticMesh			Mesh to process. @return array of LOD screen sizes.
- L177 _public prototype_ `bool SetLodScreenSizes(UStaticMesh* StaticMesh, const TArray<float>& ScreenSizes);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Set LOD screen sizes. @param	StaticMesh			Mesh to process. @param	ScreenSizes			Array of LOD screen sizes to set. @return A boolean indicating if setting the screen sizes was successful.
- L192 _public prototype_ `bool ImportNaniteHiResMesh(UStaticMesh* StaticMesh, const FString& SourceFilename, bool bShowDialogWhenFileMissing);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Import or re-import the nanite hi-res mesh into the specified base mesh. @param StaticMesh:	The static mesh we import or re-import the nanite hi-res mesh. @param SourceFilename:	The source filename containing the hi-res mesh data. If we are re-importing an existing nanite hi-res mesh, it can be empty, in this case it will use the last import file. Otherwise it must be an existing file. @param bShowDialogWhenFileMissing: If true a file picker will show in case the provided filename and the existing source filename are empty or do not exist. @return true if the nanite hi-res mesh import/re-import is successful, false otherwise.
- L200 _public prototype_ `FString GetNaniteSourceFilename(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Get the Nanite hi-res source filename @param StaticMesh        Mesh to access @return the source filename use by the static mesh nanite hi-res.
- L209 _public prototype_ `bool UpdateNaniteSourceFilename(UStaticMesh* StaticMesh, const FString& NewSourceFilename);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | StaticMesh")` — Update the Nanite hi-res source filename. @param StaticMesh			Mesh to update the nanite source filename @param NewSourceFilename	The source filename we want to set. If empty, imported nanite mesh will be remove. If not empty, the file must exist otherwise nothing will be done. @return true if the source filename was updated (cleared or replace by an existing filename), false otherwise.
- L217 _public prototype_ `FMeshNaniteSettings GetNaniteSettings(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Get the Nanite Settings for the mesh @param StaticMesh        Mesh to access @return FMeshNaniteSettings struct for the given static mesh
- L226 _public prototype_ `void SetNaniteSettings(UStaticMesh* StaticMesh, FMeshNaniteSettings NaniteSettings, bool bApplyChanges=true);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Get the Nanite Settings for the mesh @param StaticMesh        Mesh to update nanite settings for @param NaniteSettings    Settings with which to update the mesh @param bApplyChanges     Indicates if changes must be applied or not.
- L241 _public prototype_ `int32 AddSimpleCollisionsWithNotification(UStaticMesh* StaticMesh, const EScriptCollisionShapeType ShapeType, bool bApplyChanges);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Add simple collisions to a static mesh. This method replicates what is done when invoking menu entries "Collision > Add [...] Simplified Collision" in the Mesh Editor. @param	StaticMesh			Mesh to generate simple collision for. @param	ShapeType			Options on which simple collision to add to the mesh. @param	bApplyChanges		Indicates if changes must be apply or not. @return An integer indicating the index of the collision newly created. A negative value indicates the addition failed.
- L247 _public function_ `int32 AddSimpleCollisions(UStaticMesh* StaticMesh, const EScriptCollisionShapeType ShapeType)` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Same as AddSimpleCollisionsWithNotification but changes are automatically applied.
- L259 _public prototype_ `int32 GetSimpleCollisionCount(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Get number of simple collisions present on a static mesh. @param	StaticMesh				Mesh to query on. @return An integer representing the number of simple collisions on the input static mesh. An negative value indicates that the command could not be executed. See log for explanation.
- L267 _public prototype_ `TEnumAsByte<ECollisionTraceFlag> GetCollisionComplexity(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Get the Collision Trace behavior of a static mesh @param	StaticMesh				Mesh to query on. @return the Collision Trace behavior.
- L276 _public prototype_ `int32 GetConvexCollisionCount(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Get number of convex collisions present on a static mesh. @param	StaticMesh				Mesh to query on. @return An integer representing the number of convex collisions on the input static mesh. An negative value indicates that the command could not be executed. See log for explanation.
- L290 _public prototype_ `bool SetConvexDecompositionCollisionsWithNotification(UStaticMesh* StaticMesh, int32 HullCount, int32 MaxHullVerts, int32 HullPrecision, bool bApplyChanges);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Add a convex collision to a static mesh. Any existing collisions will be removed from the static mesh. This method replicates what is done when invoking menu entry "Collision > Auto Convex Collision" in the Mesh Editor. @param	StaticMesh				Static mesh to add convex collision on. @param	HullCount				Maximum number of convex pieces that will be created. Must be positive. @param	MaxHullVerts			Maximum number of vertices allowed for any generated convex hull. @param	HullPrecision			Number of voxels to use when generating collision. Must be positive. @param	bApplyChanges			Indicates if changes must be apply or not. @return A boolean indicating if the addition was successful or not.
- L304 _public prototype_ `bool BulkSetConvexDecompositionCollisionsWithNotification(const TArray<UStaticMesh*>& StaticMeshes, int32 HullCount, int32 MaxHullVerts, int32 HullPrecision, bool bApplyChanges);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Compute convex collisions for a set of static meshes. Any existing collisions will be removed from the static meshes. This method replicates what is done when invoking menu entry "Collision > Auto Convex Collision" in the Mesh Editor. @param	StaticMeshes			Set of Static mesh to add convex collision on. @param	HullCount				Maximum number of convex pieces that will be created. Must be positive. @param	MaxHullVerts			Maximum number of vertices allowed for any generated convex hull. @param	HullPrecision			Number of voxels to use when generating collision. Must be positive. @param	bApplyChanges			Indicates if changes must be apply or not. @return A boolean indicating if the addition was successful or not.
- L310 _public function_ `bool SetConvexDecompositionCollisions(UStaticMesh* StaticMesh, int32 HullCount, int32 MaxHullVerts, int32 HullPrecision)` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Same as SetConvexDecompositionCollisionsWithNotification but changes are automatically applied.
- L319 _public function_ `bool BulkSetConvexDecompositionCollisions(const TArray<UStaticMesh*>& StaticMeshes, int32 HullCount, int32 MaxHullVerts, int32 HullPrecision)` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Same as SetConvexDecompositionCollisionsWithNotification but changes are automatically applied.
- L332 _public prototype_ `bool RemoveCollisionsWithNotification(UStaticMesh* StaticMesh, bool bApplyChanges);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Remove collisions from a static mesh. This method replicates what is done when invoking menu entries "Collision > Remove Collision" in the Mesh Editor. @param	StaticMesh			Static mesh to remove collisions from. @param	bApplyChanges		Indicates if changes must be apply or not. @return A boolean indicating if the removal was successful or not.
- L338 _public function_ `bool RemoveCollisions(UStaticMesh* StaticMesh)` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Same as RemoveCollisionsWithNotification but changes are applied.
- L347 _private prototype_ `static bool CanModifyStaticMeshSection(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex, const FString& LogFunctionName);` — Checks if section and lod indices are valid indices.
- L358 _public prototype_ `void EnableSectionCastShadow(UStaticMesh* StaticMesh, bool bCastShadow, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Enables/disables mesh section shadow casting for a specific LOD. @param	StaticMesh			Static mesh to enable/disable section's shadow casting from. @param	bCastShadow			If the section should cast shadow. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L367 _public prototype_ `bool IsSectionCastShadowEnabled(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Checks if a specific LOD mesh section can cast shadows. @param	StaticMesh			Static mesh to check if its section is casting shadows. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L377 _public prototype_ `void EnableSectionCollision(UStaticMesh* StaticMesh, bool bCollisionEnabled, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Enables/disables mesh section collision for a specific LOD. @param	StaticMesh			Static mesh to Enables/disables collisions from. @param	bCollisionEnabled	If the collision is enabled or not. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L387 _public prototype_ `bool IsSectionCollisionEnabled(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Checks if a specific LOD mesh section has collision. @param	StaticMesh			Static mesh to check section collisions from. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section. @return True if the collision is enabled for the specified LOD of the StaticMesh section.
- L397 _public prototype_ `void EnableSectionVisibleInRayTracing(UStaticMesh* StaticMesh, bool bVisibleInRayTracing, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Enables/disables mesh section's visibility in ray tracing for a specific LOD. @param	StaticMesh				Static mesh to enable/disable section's visibility in ray tracing from. @param	bVisibleInRayTracing	If the section visible in ray tracing. @param	LODIndex				Index of the StaticMesh LOD. @param	SectionIndex			Index of the StaticMesh Section.
- L406 _public prototype_ `bool IsSectionVisibleInRayTracingEnabled(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Checks if a specific LOD mesh section is visible in ray tracing. @param	StaticMesh			Static mesh to check if its section is visible in ray tracing. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L416 _public prototype_ `void EnableSectionAffectDistanceFieldLighting(UStaticMesh* StaticMesh, bool bAffectDistanceFieldLighting, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Enables/disables mesh section affects distance field lighting for a specific LOD. @param	StaticMesh						Static mesh to enable/disable section affecting distance field lighting from. @param	bAffectDistanceFieldLighting	If the section affects distance field lighting. @param	LODIndex						Index of the StaticMesh LOD. @param	SectionIndex					Index of the StaticMesh Section.
- L425 _public prototype_ `bool IsSectionAffectDistanceFieldLightingEnabled(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Checks if a specific LOD mesh section affects distance field lighting. @param	StaticMesh			Static mesh to check if its section affects distance field lighting. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L436 _public prototype_ `void EnableSectionForceOpaque(UStaticMesh* StaticMesh, bool bForceOpaque, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Set/unset mesh section to be forcefully opaque for a specific LOD. @param	StaticMesh			Static mesh to make section forcefully opaque from. @param	bForceOpaque		If the section is forced to be opaque. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L445 _public prototype_ `bool IsSectionForceOpaqueEnabled(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Checks if a specific LOD mesh section is forced to be opaque. @param	StaticMesh			Static mesh to is forced to be opaque. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L456 _public prototype_ `void SetLODMaterialSlot(UStaticMesh* StaticMesh, int32 MaterialSlotIndex, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Sets the material slot for a specific LOD. @param	StaticMesh			Static mesh to Enables/disables shadow casting from. @param	MaterialSlotIndex	Index of the material slot to use. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section.
- L466 _public prototype_ `int32 GetLODMaterialSlot(const UStaticMesh* StaticMesh, int32 LODIndex, int32 SectionIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Gets the material slot used for a specific LOD section. @param	StaticMesh			Static mesh to get the material index from. @param	LODIndex			Index of the StaticMesh LOD. @param	SectionIndex		Index of the StaticMesh Section. @return  MaterialSlotIndex	Index of the material slot used by the section or INDEX_NONE in case of error.
- L470 _public prototype_ `bool HasVertexColors(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Check whether a static mesh has vertex colors
- L474 _public prototype_ `bool HasInstanceVertexColors(const UStaticMeshComponent* StaticMeshComponent);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Check whether a static mesh component has vertex colors
- L478 _public prototype_ `bool SetGenerateLightmapUVs(UStaticMesh* StaticMesh, bool bGenerateLightmapUVs);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities", meta = (ScriptName = "SetGenerateLightmapUv"))` — Set Generate Lightmap UVs for StaticMesh
- L482 _public prototype_ `int32 GetNumberVerts(const UStaticMesh* StaticMesh, int32 LODIndex);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Get number of StaticMesh verts for an LOD
- L486 _public prototype_ `int32 GetNumberMaterials(const UStaticMesh* StaticMesh);` — `UFUNCTION(BlueprintPure, Category = "Static Mesh Utilities")` — Get number of Materials for a StaticMesh
- L490 _public prototype_ `void SetAllowCPUAccess(UStaticMesh* StaticMesh, bool bAllowCPUAccess);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Sets StaticMeshFlag bAllowCPUAccess
- L501 _public prototype_ `int32 GetNumUVChannels(const UStaticMesh* StaticMesh, int32 LODIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Returns the number of UV channels for the given LOD of a StaticMesh. @param	StaticMesh			Static mesh to query. @param	LODIndex			Index of the StaticMesh LOD. @return the number of UV channels.
- L510 _public prototype_ `bool AddUVChannel(UStaticMesh* StaticMesh, int32 LODIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Adds an empty UV channel at the end of the existing channels on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to add a UV channel. @param	LODIndex			Index of the StaticMesh LOD. @return true if a UV channel was added.
- L520 _public prototype_ `bool InsertUVChannel(UStaticMesh* StaticMesh, int32 LODIndex, int32 UVChannelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Inserts an empty UV channel at the specified channel index on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to insert a UV channel. @param	LODIndex			Index of the StaticMesh LOD. @param	UVChannelIndex		Index where to insert the UV channel. @return true if a UV channel was added.
- L530 _public prototype_ `bool RemoveUVChannel(UStaticMesh* StaticMesh, int32 LODIndex, int32 UVChannelIndex);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Removes the UV channel at the specified channel index on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to remove the UV channel. @param	LODIndex			Index of the StaticMesh LOD. @param	UVChannelIndex		Index where to remove the UV channel. @return true if the UV channel was removed.
- L543 _public prototype_ `bool GeneratePlanarUVChannel(UStaticMesh* StaticMesh, int32 LODIndex, int32 UVChannelIndex, const FVector& Position, const FRotator& Orientation, const FVector2D& Tiling);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Generates planar UV mapping in the specified UV channel on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to generate the UV mapping. @param	LODIndex			Index of the StaticMesh LOD. @param	UVChannelIndex		Channel where to save the UV mapping. @param	Position			Position of the center of the projection gizmo. @param	Orientation			Rotation to apply to the projection gizmo. @param	Tiling				The UV tiling to use to generate the UV mapping. @return true if the UV mapping was generated.
- L556 _public prototype_ `bool GenerateCylindricalUVChannel(UStaticMesh* StaticMesh, int32 LODIndex, int32 UVChannelIndex, const FVector& Position, const FRotator& Orientation, const FVector2D& Tiling);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Generates cylindrical UV mapping in the specified UV channel on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to generate the UV mapping. @param	LODIndex			Index of the StaticMesh LOD. @param	UVChannelIndex		Channel where to save the UV mapping. @param	Position			Position of the center of the projection gizmo. @param	Orientation			Rotation to apply to the projection gizmo. @param	Tiling				The UV tiling to use to generate the UV mapping. @return true if the UV mapping was generated.
- L569 _public prototype_ `bool GenerateBoxUVChannel(UStaticMesh* StaticMesh, int32 LODIndex, int32 UVChannelIndex, const FVector& Position, const FRotator& Orientation, const FVector& Size);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Generates box UV mapping in the specified UV channel on the given LOD of a StaticMesh. @param	StaticMesh			Static mesh on which to generate the UV mapping. @param	LODIndex			Index of the StaticMesh LOD. @param	UVChannelIndex		Channel where to save the UV mapping. @param	Position			Position of the center of the projection gizmo. @param	Orientation			Rotation to apply to the projection gizmo. @param	Size				The size of the box projection gizmo. @return true if the UV mapping was generated.
- L578 _public prototype_ `void ReplaceMeshComponentsMaterials(const TArray<class UMeshComponent*>& MeshComponents, class UMaterialInterface* MaterialToBeReplaced, class UMaterialInterface* NewMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Find the references of the material MaterialToReplaced on all the MeshComponents provided and replace it by NewMaterial. @param	MeshComponents			List of MeshComponent to search from. @param	MaterialToBeReplaced	Material we want to replace. @param	NewMaterial				Material to replace MaterialToBeReplaced by.
- L587 _public prototype_ `void ReplaceMeshComponentsMaterialsOnActors(const TArray<class AActor*>& Actors, class UMaterialInterface* MaterialToBeReplaced, class UMaterialInterface* NewMaterial);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Find the references of the material MaterialToReplaced on all the MeshComponents of all the Actors provided and replace it by NewMaterial. @param	Actors					List of Actors to search from. @param	MaterialToBeReplaced	Material we want to replace. @param	NewMaterial				Material to replace MaterialToBeReplaced by.
- L597 _public prototype_ `void ReplaceMeshComponentsMeshes(const TArray<class UStaticMeshComponent*>& MeshComponents, class UStaticMesh* MeshToBeReplaced, class UStaticMesh* NewMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Find the references of the mesh MeshToBeReplaced on all the MeshComponents provided and replace it by NewMesh. The editor should not be in play in editor mode. @param	MeshComponents			List of MeshComponent to search from. @param	MeshToBeReplaced		Mesh we want to replace. @param	NewMesh					Mesh to replace MeshToBeReplaced by.
- L606 _public prototype_ `void ReplaceMeshComponentsMeshesOnActors(const TArray<class AActor*>& Actors, class UStaticMesh* MeshToBeReplaced, class UStaticMesh* NewMesh);` — `UFUNCTION(BlueprintCallable, Category = "Static Mesh Utilities")` — Find the references of the mesh MeshToBeReplaced on all the MeshComponents of all the Actors provided and replace it by NewMesh. @param	Actors					List of Actors to search from. @param	MeshToBeReplaced		Mesh we want to replace. @param	NewMesh					Mesh to replace MeshToBeReplaced by.
- L617 _public prototype_ `class AActor* JoinStaticMeshActors(const TArray<class AStaticMeshActor*>& ActorsToJoin, const FJoinStaticMeshActorsOptions& JoinOptions);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Dataprep")` — Create a new Actor in the level that contains a duplicate of all the Actors Static Meshes Component. The ActorsToJoin need to be in the same Level. This will have a low impact on performance but may help the edition by grouping the meshes under a single Actor. @param	ActorsToJoin			List of Actors to join. @param	JoinOptions				Options on how to join the actors. @return The new created actor.
- L629 _public prototype_ `bool MergeStaticMeshActors(const TArray<class AStaticMeshActor*>& ActorsToMerge, const FMergeStaticMeshActorsOptions& MergeOptions, class AStaticMeshActor*& OutMergedActor);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Dataprep")` — Merge the meshes into a unique mesh with the provided StaticMeshActors. There are multiple options on how to merge the meshes and their materials. The ActorsToMerge need to be in the same Level. This may have a high impact on performance depending of the MeshMergingSettings options. @param	ActorsToMerge			List of Actors to merge. @param	MergeOptions			Options on how to merge the actors. @param	OutMergedActor			The new created actor, if requested. @return	if the operation is successful.
- L639 _public prototype_ `bool CreateProxyMeshActor(const TArray<class AStaticMeshActor*>& ActorsToMerge, const FCreateProxyMeshActorOptions& MergeOptions, class AStaticMeshActor*& OutMergedActor);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Dataprep")` — Build a proxy mesh actor that can replace a set of mesh actors. @param   ActorsToMerge  List of actors to build a proxy for. @param   MergeOptions @param   OutMergedActor generated actor if requested @return  Success of the proxy creation

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshEditorSubsystem, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStaticMeshEditorSubsystem, Log, All);`

### `Source/Editor/StaticMeshEditor/Public/StaticMeshEditorSubsystemHelpers.h` (Public)


#### struct `FStaticMeshReductionSettings`  
`struct FStaticMeshReductionSettings`  
_L18-34_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public function_ `FStaticMeshReductionSettings() : PercentTriangles(0.5f) , ScreenSize(0.5f)`
- L29 _public member_ `float PercentTriangles;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Percentage of triangles to keep. Ranges from 0.0 to 1.0: 1.0 = no reduction, 0.0 = no triangles.
- L33 _public member_ `float ScreenSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — ScreenSize to display this LOD. Ranges from 0.0 to 1.0.

#### struct `FStaticMeshReductionOptions`  
`struct FStaticMeshReductionOptions`  
_L37-53_
- reflection: `USTRUCT(BlueprintType)`
- L41 _public function_ `FStaticMeshReductionOptions() : bAutoComputeLODScreenSize(true)`
- L48 _public member_ `bool bAutoComputeLODScreenSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — If true, the screen sizes at which LODs swap are computed automatically @note that this is displayed as 'Auto Compute LOD Distances' in the UI
- L52 _public member_ `TArray<FStaticMeshReductionSettings> ReductionSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Array of reduction settings to apply to each new LOD mesh.

#### enum `EScriptCollisionShapeType`  
`enum class EScriptCollisionShapeType : uint8`  
_L57-67_
- reflection: `UENUM(BlueprintType)`
- desc: Types of Collision Construct that are generated
- L59 _public enumerator_ `Box`
- L60 _public enumerator_ `Sphere`
- L61 _public enumerator_ `Capsule`
- L62 _public enumerator_ `NDOP10_X`
- L63 _public enumerator_ `NDOP10_Y`
- L64 _public enumerator_ `NDOP10_Z`
- L65 _public enumerator_ `NDOP18`
- L66 _public enumerator_ `NDOP26`

#### struct `FJoinStaticMeshActorsOptions`  
`struct FJoinStaticMeshActorsOptions`  
_L71-91_
- reflection: `USTRUCT(BlueprintType)`
- L75 _public function_ `FJoinStaticMeshActorsOptions() : bDestroySourceActors(true) , bRenameComponentsFromSource(true)`
- L82 _public member_ `bool bDestroySourceActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Destroy the provided Actors after the operation.
- L86 _public member_ `FString NewActorLabel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Name of the new spawned Actor to replace the provided Actors.
- L90 _public member_ `bool bRenameComponentsFromSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Rename StaticMeshComponents based on source Actor's name.

#### struct `FMergeStaticMeshActorsOptions`  
`struct FMergeStaticMeshActorsOptions : public FJoinStaticMeshActorsOptions`  
_L94-112_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FJoinStaticMeshActorsOptions`
- L98 _public function_ `FMergeStaticMeshActorsOptions() : bSpawnMergedActor(true)`
- L104 _public member_ `bool bSpawnMergedActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Spawn the new merged actors
- L108 _public member_ `FString BasePackageName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The package path you want to save to. ie: /Game/MyFolder
- L111 _public member_ `FMeshMergingSettings MeshMergingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`

#### struct `FCreateProxyMeshActorOptions`  
`struct FCreateProxyMeshActorOptions : public FJoinStaticMeshActorsOptions`  
_L115-133_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FJoinStaticMeshActorsOptions`
- L119 _public function_ `FCreateProxyMeshActorOptions() : bSpawnMergedActor(true)`
- L125 _public member_ `bool bSpawnMergedActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — Spawn the new merged actors
- L129 _public member_ `FString BasePackageName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)` — The package path you want to save to. ie: /Game/MyFolder
- L132 _public member_ `FMeshProxySettings MeshProxySettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Options)`
