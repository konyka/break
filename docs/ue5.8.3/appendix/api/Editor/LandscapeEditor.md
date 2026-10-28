# Editor / LandscapeEditor

- module root: `Source/Editor/LandscapeEditor`
- headers: 42; symbols: 1817
- symbol kinds: class=65, delegate=5, enum=25, enumerator=102, function=273, macro=3, member=421, namespace=7, prototype=858, struct=36, typedef=19, variable=3
- DynamicallyLoadedModuleNames: DesktopPlatform, MainFrame
- PrivateDependencyModuleNames: ApplicationCore, CQTest, Core, CoreUObject, DeveloperSettings, DirectoryWatcher, Documentation, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, Foliage, ImageCore, ImageWrapper, InputCore, Json, Landscape, LandscapeEditorUtilities, NavigationSystem, PlacementMode, PropertyEditor, RHI, RenderCore, Slate, SlateCore, SourceControl, ToolMenus, ToolWidgets, UnrealEd, VirtualTexturingEditor
- PrivateIncludePathModuleNames: AssetTools, DesktopPlatform, LevelEditor, MainFrame

### `Source/Editor/LandscapeEditor/Private/Classes/ActorFactoryLandscape.h` (Private)


#### class `UActorFactoryLandscape`  
`class UActorFactoryLandscape : public UActorFactory`  
_L15-22_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactory`
- L20 _private prototype_ `virtual AActor* SpawnActor( UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;`

### `Source/Editor/LandscapeEditor/Private/Classes/LandscapePlaceholder.h` (Private)


#### class `ALandscapePlaceholder`  
`class ALandscapePlaceholder : public AActor`  
_L11-19_
- reflection: `UCLASS(NotPlaceable)`
- inherits: `AActor`
- L16 _private prototype_ `virtual bool TeleportTo(const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest = false, bool bNoCheck = false) override;` — virtual void PostEditMove(bool bFinished) override;
- L18 _private prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeEdMode.h` (Private)


#### struct `FLandscapeToolMode`  
`struct FLandscapeToolMode`  
_L55-69_
- L57 _public member_ `const FName ToolModeName;`
- L58 _public member_ `ELandscapeToolTargetTypeFlags SupportedTargetTypes;`
- L60 _public member_ `TArray<FName> ValidTools;`
- L61 _public member_ `FName CurrentToolName;`
- L62 _public member_ `FName CurrentTargetLayerName;`
- L64 _public function_ `FLandscapeToolMode(FName InToolModeName, ELandscapeToolTargetTypeFlags InSupportedTargetTypes) : ToolModeName(InToolModeName) , SupportedTargetTypes(InSupportedTargetTypes)`

#### struct `FLandscapeTargetListInfo`  
`struct FLandscapeTargetListInfo`  
_L71-216_
- L73 _public member_ `FText TargetLayerDisplayName;` — UI Display Name
- L74 _public member_ `ELandscapeToolTargetType TargetType = ELandscapeToolTargetType::Invalid;`
- L75 _public member_ `TWeakObjectPtr<ULandscapeInfo> LandscapeInfo;`
- L77 _public member_ `TWeakObjectPtr<ULandscapeLayerInfoObject> LayerInfoObj;` — ignored for heightmap
- L78 _public member_ `FName LayerName;` — ignored for heightmap
- L79 _public member_ `TWeakObjectPtr<class ALandscapeProxy> Owner;` — ignored for heightmap
- L80 _public member_ `TWeakObjectPtr<class UMaterialInstanceConstant> ThumbnailMIC;` — ignored for heightmap
- L81 _public member_ `int32 DebugColorChannel = -1;` — ignored for heightmap
- L82 _public member_ `int32 LayerIndex = INDEX_NONE;`
- L83 _public member_ `bool bIsLayerReferencedByMaterial = false;`
- L85 _public function_ `FLandscapeTargetListInfo(FText InTargetLayerDisplayName, ELandscapeToolTargetType InTargetType, const FLandscapeInfoLayerSettings& InLayerSettings, int32 InLayerIndex, bool bInIsLayerReferencedByMaterial) : TargetLayerDisplayName(InTargetLayerDisplayName) , TargetType(InTargetType) , LandscapeInfo(InLayerSettings.Owner->GetLandscapeInfo()) , LayerInfoObj(InLayerSettings.LayerInfoObj) , LayerName(InLayerSettings.LayerName) , Owner(InLayerSettings.Owner) , ThumbnailMIC(InLayerSettings.ThumbnailMIC) , DebugColorChannel(InLayerSettings.DebugColorChannel) , LayerIndex(InLayerIndex) , bIsLayerReferencedByMaterial(bInIsLayerReferencedByMaterial)`
- L99 _public function_ `FLandscapeTargetListInfo(FText InTargetLayerDisplayName, ELandscapeToolTargetType InTargetType, ULandscapeInfo* InLandscapeInfo, int32 InLayerIndex, bool bInIsLayerReferencedByMaterial) : TargetLayerDisplayName(InTargetLayerDisplayName) , TargetType(InTargetType) , LandscapeInfo(InLandscapeInfo) , LayerInfoObj(nullptr) , LayerName(NAME_None) , Owner(nullptr) , ThumbnailMIC(nullptr) , LayerIndex(InLayerIndex) , bIsLayerReferencedByMaterial(bInIsLayerReferencedByMaterial)`
- L112 _public function_ `int32 GetLandscapeInfoLayerIndex() const`
- L131 _public function_ `FLandscapeInfoLayerSettings* GetLandscapeInfoLayerSettings() const`
- L143 _public function_ `const FLandscapeTargetLayerSettings* GetTargetLayerSettings() const`
- L163 _public prototype_ `FName GetLayerName() const;`
- L165 _public function_ `FString GetReimportFilePath() const`
- L189 _public function_ `void SetReimportFilePath(const FString& InNewPath)`

#### struct `FLandscapeListInfo`  
`struct FLandscapeListInfo`  
_L218-236_
- L220 _public member_ `FString LandscapeName;`
- L221 _public member_ `ULandscapeInfo* Info;`
- L222 _public member_ `int32 ComponentQuads;`
- L223 _public member_ `int32 NumSubsections;`
- L224 _public member_ `int32 Width;`
- L225 _public member_ `int32 Height;`
- L227 _public function_ `FLandscapeListInfo(const TCHAR* InName, ULandscapeInfo* InInfo, int32 InComponentQuads, int32 InNumSubsections, int32 InWidth, int32 InHeight) : LandscapeName(InName) , Info(InInfo) , ComponentQuads(InComponentQuads) , NumSubsections(InNumSubsections) , Width(InWidth) , Height(InHeight)`

#### enum `ENewLandscapePreviewMode`  
`enum class ENewLandscapePreviewMode : uint8`  
_L238-243_
- L240 _public enumerator_ `None`
- L241 _public enumerator_ `NewLandscape`
- L242 _public enumerator_ `ImportLandscape`

#### enum `EImportExportMode`  
`enum class EImportExportMode : uint8`  
_L245-249_
- L247 _public enumerator_ `Import`
- L248 _public enumerator_ `Export`

#### enum `ELandscapeEditingState`  
`enum class ELandscapeEditingState : uint8`  
_L251-259_
- L253 _public enumerator_ `Unknown`
- L254 _public enumerator_ `Enabled`
- L255 _public enumerator_ `BadFeatureLevel`
- L256 _public enumerator_ `PIEWorld`
- L257 _public enumerator_ `SIEWorld`
- L258 _public enumerator_ `NoLandscape`

#### class `FEdModeLandscape`  
`class FEdModeLandscape : public FEdMode , public ILandscapeEdModeInterface`  
_L264-720_
- inherits: `FEdMode,ILandscapeEdModeInterface`
- desc: Landscape editor mode
- L270 _public member_ `TObjectPtr<ULandscapeEditorObject> UISettings;`
- L272 _public member_ `FText ErrorReasonOnMouseUp;`
- L274 _public member_ `FLandscapeToolMode* CurrentToolMode;`
- L275 _public member_ `FLandscapeTool* CurrentTool;`
- L276 _public member_ `FLandscapeBrush* CurrentBrush;`
- L277 _public member_ `FLandscapeToolTarget CurrentToolTarget;`
- L280 _public member_ `FLandscapeBrush* GizmoBrush;` — GizmoBrush for Tick
- L282 _public member_ `int32 CurrentToolIndex;` — UI setting for additional UI Tools
- L284 _public member_ `int32 CurrentBrushSetIndex;` — UI setting for additional UI Tools
- L286 _public member_ `ELandscapeViewMode::Type CurrentLandscapeViewMode;` — Persistent View Mode when toggling landscape editor
- L288 _public member_ `int32 PendingRenameTargetLayerIndex;` — Persistent Target Layer index when entering a layer rename
- L290 _public member_ `ENewLandscapePreviewMode NewLandscapePreviewMode;`
- L291 _public member_ `EImportExportMode ImportExportMode;`
- L294 _public member_ `FLandscapeToolCopyPaste<FHeightmapToolTarget>* CopyPasteTool;` — UI callbacks for copy/paste tool
- L295 _public prototype_ `void CopyDataToGizmo();`
- L296 _public prototype_ `void PasteDataFromGizmo();`
- L299 _public member_ `FLandscapeToolSplines* SplinesTool;` — UI callbacks for splines tool
- L300 _public prototype_ `void ShowSplineProperties();`
- L301 _public prototype_ `bool HasSelectedSplineSegments() const;`
- L302 _public prototype_ `bool HasAdjacentLinearSplineConnection(ESplineNavigationFlags Flags) const;`
- L303 _public prototype_ `bool HasEndLinearSplineConnection(ESplineNavigationFlags Flags) const;`
- L304 _public prototype_ `void FlipSelectedSplineSegments();`
- L305 _public prototype_ `void GetSelectedSplineOwners(TSet<AActor*>& SelectedSplineOwners) const;`
- L306 _public prototype_ `virtual void SelectAllSplineControlPoints(ESplineNavigationFlags Flags);`
- L307 _public prototype_ `virtual void SelectAllSplineSegments(ESplineNavigationFlags Flags);`
- L308 _public prototype_ `virtual void SelectAllConnectedSplineControlPoints();`
- L309 _public prototype_ `virtual void SelectAllConnectedSplineSegments();`
- L310 _public prototype_ `virtual void SelectAdjacentLinearSplineElement(ESplineNavigationFlags Flags) const;`
- L311 _public prototype_ `virtual void SelectEndLinearSplineElement(ESplineNavigationFlags Flags) const;`
- L312 _public prototype_ `virtual void SelectSplineControlPointsFromCurrentSegmentSelection() const;`
- L313 _public prototype_ `virtual void SelectSplineSegmentsFromCurrentControlPointSelection() const;`
- L314 _public prototype_ `virtual void SplineMoveToCurrentLevel();`
- L315 _public prototype_ `virtual bool CanMoveSplineToCurrentLevel() const;`
- L316 _public prototype_ `virtual void UpdateSplineMeshLevels();`
- L317 _public prototype_ `void SetbUseAutoRotateOnJoin(bool InbAutoRotateOnJoin);`
- L318 _public prototype_ `bool GetbUseAutoRotateOnJoin();`
- L319 _public prototype_ `void SetbAlwaysRotateForward(bool InbAlwaysRotateForward);`
- L320 _public prototype_ `bool GetbAlwaysRotateForward();`
- L323 _public prototype_ `void ApplyRampTool();` — UI callbacks for ramp tool
- L324 _public prototype_ `bool CanApplyRampTool();`
- L325 _public prototype_ `void ResetRampTool();`
- L328 _public prototype_ `void ApplyMirrorTool();` — UI callbacks for mirror tool
- L329 _public prototype_ `void CenterMirrorTool();`
- L332 _public prototype_ `FEdModeLandscape();` — Constructor
- L335 _public prototype_ `void InitializeBrushes();` — Initialization
- L336 _public prototype_ `void InitializeTool_Paint();`
- L337 _public prototype_ `void InitializeTool_Smooth();`
- L338 _public prototype_ `void InitializeTool_Flatten();`
- L339 _public prototype_ `void InitializeTool_Erosion();`
- L340 _public prototype_ `void InitializeTool_HydraErosion();`
- L341 _public prototype_ `void InitializeTool_Noise();`
- L342 _public prototype_ `void InitializeTool_Retopologize();`
- L343 _public prototype_ `void InitializeTool_NewLandscape();`
- L344 _public prototype_ `void InitializeTool_ResizeLandscape();`
- L345 _public prototype_ `void InitializeTool_ImportExport();`
- L346 _public prototype_ `void InitializeTool_Select();`
- L347 _public prototype_ `void InitializeTool_AddComponent();`
- L348 _public prototype_ `void InitializeTool_DeleteComponent();`
- L349 _public prototype_ `void InitializeTool_MoveToLevel();`
- L350 _public prototype_ `void InitializeTool_Mask();`
- L351 _public prototype_ `void InitializeTool_CopyPaste();`
- L352 _public prototype_ `void InitializeTool_Visibility();`
- L353 _public prototype_ `void InitializeTool_Splines();`
- L354 _public prototype_ `void InitializeTool_Ramp();`
- L355 _public prototype_ `void InitializeTool_Mirror();`
- L356 _public prototype_ `void InitializeTool_BlueprintBrush();`
- L357 _public prototype_ `void UpdateToolModes();`
- L360 _public prototype_ `virtual ~FEdModeLandscape();` — Destructor
- L363 _public prototype_ `virtual void PostUpdateLayerContent() override;` — ILandscapeEdModeInterface
- L364 _public prototype_ `virtual ELandscapeToolTargetType GetLandscapeToolTargetType() const override;`
- L365 _public prototype_ `virtual const ULandscapeEditLayerBase* GetLandscapeSelectedLayer() const override;`
- L366 _public prototype_ `virtual ULandscapeLayerInfoObject* GetSelectedLandscapeLayerInfo() const override;`
- L369 _public function_ `virtual void OnCanHaveLayersContentChanged() final` — Deprecated
- L372 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L374 _public prototype_ `virtual bool UsesToolkits() const override;`
- L376 _public prototype_ `TSharedRef<FUICommandList> GetUICommandList() const;`
- L379 _public prototype_ `virtual void Enter() override;` — FEdMode: Called when the mode is entered
- L382 _public prototype_ `virtual void Exit() override;` — FEdMode: Called when the mode is exited
- L385 _public prototype_ `virtual bool MouseEnter(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 MouseX, int32 MouseY) override;` — FEdMode: Called when the mouse enters the viewport area
- L388 _public prototype_ `virtual bool MouseLeave(FEditorViewportClient* InViewportClient, FViewport* Viewport) override;` — FEdMode: Called when the mouse exits the viewport area
- L391 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;` — FEdMode: Called when the mouse is moved over the viewport
- L403 _public prototype_ `virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;` — FEdMode: Called when the mouse is moved while a window input capture is in effect @param	InViewportClient	Level editor viewport client that captured the mouse input @param	InViewport			Viewport that captured the mouse input @param	InMouseX			New mouse cursor X coordinate @param	InMouseY			New mouse cursor Y coordinate @return	true if input was handled
- L406 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode: Called when a mouse button is pressed
- L409 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode: Called when a mouse button is released
- L412 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;` — FEdMode: Called when a transform operation begins
- L415 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;` — FEdMode: Called when a transform operation ends
- L418 _public prototype_ `virtual bool DisallowMouseDeltaTracking() const override;` — FEdMode: Allow us to disable mouse delta tracking during painting
- L421 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — FEdMode: Called once per frame per viewport
- L424 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy* HitProxy, const FViewportClick& Click) override;` — FEdMode: Called when clicking on a hit proxy
- L427 _public prototype_ `bool IsAdjustingBrush(FEditorViewportClient* InViewportClient) const;` — True if we are interactively changing the brush size, falloff, or strength
- L428 _public prototype_ `void ChangeBrushSize(bool bIncrease);`
- L429 _public prototype_ `void ChangeBrushFalloff(bool bIncrease);`
- L430 _public prototype_ `void ChangeBrushStrength(bool bIncrease);`
- L431 _public prototype_ `void ChangeAlphaBrushRotation(bool bIncrease);`
- L434 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;` — FEdMode: Called when a key is pressed
- L437 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;` — FEdMode: Called when mouse drag input is applied
- L440 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode: Render elements for the landscape tool
- L443 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;` — FEdMode: Render HUD elements for this tool
- L446 _public prototype_ `virtual bool Select(AActor* InActor, bool bInSelected) override;` — FEdMode: Handling SelectActor
- L449 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;` — FEdMode: Check to see if an actor can be selected in this mode - no side effects
- L452 _public prototype_ `virtual void ActorSelectionChangeNotify() override;` — FEdMode: Called when the currently selected actor has changed
- L454 _public prototype_ `virtual void ActorMoveNotify() override;`
- L456 _public prototype_ `virtual void PostUndo() override;`
- L458 _public prototype_ `virtual EEditAction::Type GetActionEditDuplicate() override;`
- L459 _public prototype_ `virtual EEditAction::Type GetActionEditDelete() override;`
- L460 _public prototype_ `virtual EEditAction::Type GetActionEditCut() override;`
- L461 _public prototype_ `virtual EEditAction::Type GetActionEditCopy() override;`
- L462 _public prototype_ `virtual EEditAction::Type GetActionEditPaste() override;`
- L463 _public prototype_ `virtual bool ProcessEditDuplicate() override;`
- L464 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L465 _public prototype_ `virtual bool ProcessEditCut() override;`
- L466 _public prototype_ `virtual bool ProcessEditCopy() override;`
- L467 _public prototype_ `virtual bool ProcessEditPaste() override;`
- L470 _public function_ `virtual bool AllowWidgetMove() override` — FEdMode: If the EdMode is handling InputDelta (ie returning true from it), this allows a mode to indicated whether or not the Widget should also move.
- L473 _public prototype_ `virtual bool ShouldDrawWidget() const override;` — FEdMode: Draw the transform widget while in this mode?
- L476 _public prototype_ `virtual bool UsesTransformWidget() const override;` — FEdMode: Returns true if this mode uses the transform widget
- L478 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L480 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L482 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L483 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L484 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L486 _public prototype_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const override;`
- L489 _public prototype_ `virtual bool GetOverrideCursorVisibility(bool& bWantsOverride, bool& bHardwareCursorVisible, bool bSoftwareCursorVisible) const override;` — Get override cursor visibility settings
- L492 _public prototype_ `virtual bool PreConvertMouseMovement(FEditorViewportClient* InViewportClient) override;` — Called before mouse movement is converted to drag/rot
- L495 _public prototype_ `virtual bool PostConvertMouseMovement(FEditorViewportClient* InViewportClient) override;` — Called after mouse movement is converted to drag/rot
- L498 _public prototype_ `void ForceRealTimeViewports(const bool bEnable);` — Forces real-time perspective viewports
- L501 _public prototype_ `bool LandscapeMouseTrace(FEditorViewportClient* ViewportClient, float& OutHitX, float& OutHitY);` — Trace under the mouse cursor and return the landscape hit and the hit location (in landscape quad space)
- L502 _public prototype_ `bool LandscapeMouseTrace(FEditorViewportClient* ViewportClient, FVector& OutHitLocation);`
- L505 _public prototype_ `bool LandscapeMouseTrace(FEditorViewportClient* ViewportClient, int32 MouseX, int32 MouseY, float& OutHitX, float& OutHitY);` — Trace under the specified coordinates and return the landscape hit and the hit location (in landscape quad space)
- L506 _public prototype_ `bool LandscapeMouseTrace(FEditorViewportClient* ViewportClient, int32 MouseX, int32 MouseY, FVector& OutHitLocation);`
- L509 _public prototype_ `bool LandscapePlaneTrace(FEditorViewportClient* ViewportClient, const FPlane& Plane, FVector& OutHitLocation);` — Trace under the mouse cursor / specified screen coordinates against a world-space plane and return the hit location (in world space)
- L510 _public prototype_ `bool LandscapePlaneTrace(FEditorViewportClient* ViewportClient, int32 MouseX, int32 MouseY, const FPlane& Plane, FVector& OutHitLocation);`
- L513 _public prototype_ `bool LandscapeTrace(const FVector& InRayOrigin, const FVector& InRayEnd, const FVector& InDirection, FVector& OutHitLocation);` — Trace under the specified laser start and direction and return the landscape hit and the hit location (in landscape quad space)
- L518 _public prototype_ `bool ProcessLandscapeTraceHits(const TArray<FHitResult>& InResults, FProcessLandscapeTraceHitsResult& OutLandscapeTraceHitsResult);` — Check if we've collided with the currently edited landscape, OutHitLocation is in the space of the Landscape Actor
- L520 _public prototype_ `void SetCurrentToolMode(FName ToolModeName, bool bRestoreCurrentTool = true);`
- L523 _public prototype_ `void SetCurrentTool(FName ToolName, FName TargetLayerName = NAME_None);` — Change current tool
- L524 _public prototype_ `void SetCurrentTool(int32 ToolIdx, FName TargetLayerName = NAME_None);`
- L525 _public prototype_ `void SetCurrentTargetLayer(FName TargetLayerName, TWeakObjectPtr<ULandscapeLayerInfoObject> LayerInfo);`
- L527 _public prototype_ `void SetCurrentBrushSet(FName BrushSetName);`
- L528 _public prototype_ `void SetCurrentBrushSet(int32 BrushSetIndex);`
- L530 _public prototype_ `void SetCurrentBrush(FName BrushName);`
- L531 _public prototype_ `void SetCurrentBrush(int32 BrushIndex);`
- L533 _public prototype_ `void UpdateBrushList();`
- L534 _public prototype_ `const TArray<ALandscapeBlueprintBrushBase*>& GetBrushList() const;`
- L536 _public prototype_ `const TArray<TSharedRef<FLandscapeTargetListInfo>>& GetTargetList() const;`
- L537 _public function_ `UMaterialInterface* GetTargetLandscapeMaterial() const`
- L538 _public prototype_ `const TArray<FName>* GetTargetDisplayOrderList() const;`
- L539 _public prototype_ `int32 GetTargetLayerStartingIndex() const;`
- L540 _public prototype_ `const TArray<FLandscapeListInfo>& GetLandscapeList();`
- L541 _public prototype_ `const FString GetTargetLayerAssetPackagePath(const bool bIsEmptyPathValid = false) const;`
- L543 _public prototype_ `int32 UpdateLandscapeList();`
- L544 _public prototype_ `void UpdateTargetList(bool bRegenerateThumbnails = false);`
- L545 _public prototype_ `void SetTargetLandscape(const TWeakObjectPtr<ULandscapeInfo>& InLandscapeInfo);`
- L546 _public prototype_ `bool CanEditCurrentTarget(FText* Reason = nullptr) const;`
- L549 _public prototype_ `void UpdateTargetLayerDisplayOrder(ELandscapeLayerDisplayMode InTargetDisplayOrder, bool bInIsAscendingOrder);` — Update Display order list
- L550 _public prototype_ `void MoveTargetLayerDisplayOrder(int32 IndexToMove, int32 IndexToDestination);`
- L552 _public prototype_ `void RequestUpdateLayerUsageInformation();`
- L553 _public prototype_ `bool ShouldShowLayer(TSharedRef<FLandscapeTargetListInfo> Target) const;`
- L554 _public prototype_ `void UpdateLayerUsageInformation(TWeakObjectPtr<ULandscapeLayerInfoObject>* LayerInfoObjectThatChanged = nullptr);`
- L555 _public prototype_ `void OnLandscapeMaterialChangedDelegate(ALandscapeProxy* InProxyChanged, const FOnLandscapeProxyMaterialChangedParams& InParams);`
- L556 _public prototype_ `void RefreshDetailPanel();`
- L557 _public prototype_ `void RefreshInspectedObjectsDetailPanel();`
- L558 _public prototype_ `void RegenerateLayerThumbnails();`
- L560 _public prototype_ `bool IsGridBased() const;`
- L563 _public prototype_ `void ToggleSplinesTool(const ULandscapeEditLayerBase* InEditLayer);` — Edit Layers
- L564 _public prototype_ `int32 GetLayerCount() const;`
- L565 _public prototype_ `void SetSelectedEditLayer(int32 InLayerIndex);`
- L566 _public prototype_ `int32 GetSelectedEditLayerIndex() const;`
- L567 _public prototype_ `ALandscape* GetLandscape() const;`
- L568 _public prototype_ `bool CanRenameLayerTo(int32 InLayerIndex, const FName& InNewName) const;`
- L569 _public prototype_ `ULandscapeEditLayerBase* GetEditLayer(int32 InLayerIndex) const;`
- L570 _public prototype_ `const ULandscapeEditLayerBase* GetEditLayerConst(int32 InLayerIndex) const;`
- L571 _public prototype_ `bool IsLayerAlphaVisible(int32 InLayerIndex) const;`
- L572 _public prototype_ `const ULandscapeEditLayerBase* GetCurrentEditLayerConst() const;`
- L573 _public prototype_ `FGuid GetCurrentLayerGuid() const;`
- L574 _public prototype_ `void AutoUpdateDirtyLandscapeSplines();`
- L575 _public prototype_ `bool CanEditLayer(FText* Reason = nullptr, const ULandscapeEditLayerBase* InLayer = nullptr);`
- L576 _public prototype_ `bool CanEditSelectedTargetLayer(FText* Reason = nullptr, const ULandscapeEditLayerBase* InLayer = nullptr);`
- L577 _public prototype_ `bool CanEditTargetLayer(FText* Reason = nullptr, const ULandscapeLayerInfoObject* InLayerInfo = nullptr, const ULandscapeEditLayerBase* InLayer = nullptr);`
- L579 _public prototype_ `void AddBrushToCurrentLayer(class ALandscapeBlueprintBrushBase* InBrush);`
- L580 _public prototype_ `void RemoveBrushFromCurrentLayer(int32 InBrushIndex);`
- L581 _public prototype_ `class ALandscapeBlueprintBrushBase* GetBrushForCurrentLayer(int32 InBrushIndex) const;`
- L582 _public prototype_ `TArray<class ALandscapeBlueprintBrushBase*> GetBrushesForCurrentLayer();`
- L584 _public prototype_ `void ShowOnlySelectedBrush(class ALandscapeBlueprintBrushBase* InBrush);`
- L586 _public prototype_ `void DuplicateBrush(class ALandscapeBlueprintBrushBase* InBrush);`
- L588 _public prototype_ `void RequestLayersContentUpdate(ELandscapeLayerUpdateMode InUpdateMode);`
- L589 _public prototype_ `void RequestLayersContentUpdateForceAll(ELandscapeLayerUpdateMode InUpdateMode = ELandscapeLayerUpdateMode::Update_All);`
- L591 _public prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L592 _public prototype_ `void OnLevelActorRemoved(AActor* InActor);`
- L594 _public prototype_ `DECLARE_EVENT(FEdModeLandscape, FTargetsListUpdated);`
- L595 _public member_ `static FTargetsListUpdated TargetsListUpdated;`
- L597 _public prototype_ `void OnPreSaveWorld(class UWorld* InWorld, FObjectPreSaveContext ObjectSaveContext);`
- L600 _public prototype_ `void HandleLevelsChanged();` — Handle notification that visible levels may have changed and we should update the editable landscapes list
- L602 _public prototype_ `void ReimportData(const FLandscapeTargetListInfo& TargetInfo);`
- L603 _public prototype_ `void ImportData(const FLandscapeTargetListInfo& TargetInfo, const FString& Filename);`
- L604 _public prototype_ `void ImportHeightData(ULandscapeInfo* LandscapeInfo, const FGuid& LayerGuid, const FString& Filename, const FIntRect& ImportRegionVerts, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0,0), const ELandscapeLayerPaintingRestriction& PaintRestriction = ELandscapeLayerPaintingRestriction::None, bool bFlipYAxis = false);`
- L605 _public prototype_ `void ImportWeightData(ULandscapeInfo* LandscapeInfo, const FGuid& LayerGuid, ULandscapeLayerInfoObject* LayerInfo, const FString& Filename, const FIntRect& ImportRegionVerts, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0, 0), const ELandscapeLayerPaintingRestriction& PaintRestriction = ELandscapeLayerPaintingRestriction::None, bool bFlipYAxis = false);`
- L606 _public function_ `bool UseSingleFileImport() const`
- L609 _public prototype_ `ALandscape* ChangeComponentSetting(int32 NumComponentsX, int32 NumComponentsY, int32 InNumSubsections, int32 InSubsectionSizeQuads, bool bResample);` — Resample landscape to a different resolution or change the component size
- L612 _public prototype_ `void DeleteLandscapeComponents(ULandscapeInfo* LandscapeInfo, TSet<ULandscapeComponent*> ComponentsToDelete);` — Delete the specified landscape components
- L614 _public member_ `TArray<FLandscapeToolMode> LandscapeToolModes;`
- L615 _public member_ `TArray<TUniquePtr<FLandscapeTool>> LandscapeTools;`
- L616 _public member_ `TArray<FLandscapeBrushSet> LandscapeBrushSets;`
- L618 _public prototype_ `ELandscapeEditingState GetEditingState() const;`
- L620 _public function_ `bool IsEditingEnabled() const`
- L625 _public prototype_ `static bool IsLandscapeViewModeExclusiveToEditorMode(ELandscapeViewMode::Type ViewMode);`
- L627 _public prototype_ `void SetLandscapeInfo(ULandscapeInfo* InLandscapeInfo);`
- L630 _public prototype_ `int32 GetAccumulatedAllLandscapesResolution() const;` — Returns the sum of all landscape actors resolution.
- L633 _public prototype_ `bool IsLandscapeResolutionCompliant() const;` — Returns true if landscape resolution combined to the current tool action is still compliant to the currently applied limitations.
- L636 _public prototype_ `bool DoesCurrentToolAffectEditLayers() const;` — Returns true if the current landscape tool handles edit layers.
- L639 _public prototype_ `FText GetLandscapeResolutionErrorText() const;` — Returns the default Error Text when modifying or creating landscape would break the resolution limit.
- L641 _public prototype_ `int32 GetNewLandscapeResolutionX() const;`
- L642 _public prototype_ `int32 GetNewLandscapeResolutionY() const;`
- L644 _public function_ `TArray<TWeakObjectPtr<UObject>> GetInspectedObjects() const`
- L648 _public prototype_ `void SetInspectedObjects(const TArray<TWeakObjectPtr<UObject>>& InObjects);`
- L650 _public prototype_ `bool IsGlobalModifierPressed() const;`
- L651 _public prototype_ `bool IsGlobalAlternateModifierPressed() const;`
- L656 _public prototype_ `ELandscapeTargetLayerActionType GetEstimatedTargetLayerActionType(const TSharedRef<FLandscapeTargetListInfo> Target);` — See GetTargetLayerActionType, except it's a global function meant to be used in the UX, where there's no viewport, and the action type for a given layer depends on the pressed modifier buttons (only available per-viewport), so this will give an "estimate" of the result, based on the fact that the modifier button was pressed on at least one of the active viewports. Not pretty, I know...
- L659 _private member_ `TArray<TSharedRef<FLandscapeTargetListInfo>> LandscapeTargetList;`
- L660 _private member_ `TArray<FLandscapeListInfo> LandscapeList;`
- L661 _private member_ `TArray<ALandscapeBlueprintBrushBase*> BrushList;`
- L664 _private member_ `int32 TargetLayerStartingIndex;` — Represent the index offset of the target layer in LandscapeTargetList
- L666 _private member_ `UMaterialInterface* CachedLandscapeMaterial;`
- L668 _private member_ `const FViewport* ToolActiveViewport;`
- L670 _private member_ `FDelegateHandle OnWorldChangeDelegateHandle;`
- L671 _private member_ `FDelegateHandle OnLevelsChangedDelegateHandle;`
- L673 _private member_ `FDelegateHandle OnLevelActorDeletedDelegateHandle;`
- L674 _private member_ `FDelegateHandle OnLevelActorAddedDelegateHandle;`
- L675 _private member_ `FDelegateHandle PreSaveWorldHandle;`
- L676 _private member_ `FDelegateHandle OnIsEditingDisallowedChangedHandle;`
- L679 _private member_ `bool bIsPaintingInVR;` — Check if we are painting using the VREditor
- L682 _private member_ `class UViewportInteractor* InteractorPainting;` — The interactor that is currently painting, prevents multiple interactors from sculpting when one actually is
- L685 _private member_ `bool bNeedsUpdateLayerUsageInformation;` — Delayed refresh
- L686 _private member_ `bool bUpdatingLandscapeInfo;`
- L687 _private member_ `bool bNeedsUpdateTargetLayerList;`
- L690 _private member_ `bool bHasMapChanged;` — When the map is changed, use this flag to make sure Exit() does not overwrite saved UISettings with default data
- L694 _private member_ `TArray<TWeakObjectPtr<UObject>> InspectedObjects;` — The landscape mode panel has the ability to display the properties of certain UObjects if needed (to bypass the fact that the standard details panel is not able to display anything else than actors and components)
- L697 _private member_ `FName LastActiveToolModeName = FName("Too` — Stores last active tool info. Used to toggle between current and last editor modes (Eg. Toggle Splines Layer)
- L698 _private member_ `FName LastActiveToolName = FName("Scu`
- L719 _private member_ `TSharedRef<FInputProcessor> InputProcessor;`

#### struct `FEdModeLandscape::FInputProcessor`  
`struct FInputProcessor : public IInputProcessor, public TSharedFromThis<FInputProcessor>`  
_L701-718_
- inherits: `IInputProcessor,TSharedFromThis<FInputProcessor>`
- desc: Implement a IInputProcessor to be able to track the shift/ctrl modifier key's states globally (i.e. not per-viewport), in order to access it in the editor mode UX code
- L703 _public prototype_ `void StartTrackingInput();`
- L704 _public prototype_ `void StopTrackingInput();`
- L707 _public function_ `virtual void Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor) override`
- L708 _public prototype_ `virtual bool HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L709 _public prototype_ `virtual bool HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent) override;`
- L710 _public function_ `virtual const TCHAR* GetDebugName() const`
- L716 _public member_ `bool bIsShiftDown = false;`
- L717 _public member_ `bool bIsCtrlDown = false;`

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapeEdMode, Log, All);`
- L39 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapeEdMode, Log, All);`
- L47 _namespace_ `namespace ELandscapeViewMode`
- L594 _delegate_ `DECLARE_EVENT(FEdModeLandscape, FTargetsListUpdated);`

### `Source/Editor/LandscapeEditor/Private/LandscapeEdModeTools.h` (Private)


#### struct `FNoiseParameter`  
`struct FNoiseParameter`  
_L29-160_
- desc: FNoiseParameter - Perlin noise
- L31 _public member_ `float Base;`
- L32 _public member_ `float NoiseScale;`
- L33 _public member_ `float NoiseAmount;`
- L37 _public function_ `FNoiseParameter()`
- L40 _public function_ `FNoiseParameter(float InBase, float InScale, float InAmount) : Base(InBase), NoiseScale(InScale), NoiseAmount(InAmount)`
- L48 _public function_ `float Sample(int32 X, int32 Y) const` — Sample
- L68 _public function_ `bool TestGreater(int32 X, int32 Y, float TestValue) const` — TestGreater - Returns 1 if TestValue is greater than the parameter.
- L97 _public function_ `bool TestLess(int32 X, int32 Y, float TestValue) const` — TestLess
- L100 _private member_ `static const int32 Permutations[256];`
- L102 _private function_ `bool operator==(const FNoiseParameter& SrcNoise)`
- L114 _private function_ `void operator=(const FNoiseParameter& SrcNoise)`
- L122 _private function_ `float Fade(float T) const`
- L128 _private function_ `float Grad(int32 Hash, float X, float Y) const`
- L136 _private function_ `float PerlinNoise2D(float X, float Y) const`

#### struct `TLandscapeEditCache`  
`template<class Accessor, typename AccessorType> struct TLandscapeEditCache`  
_L286-751_
- desc: TLandscapeEditCache
- L289 _public typedef_ `typedef AccessorType DataType;`
- L290 _public typedef_ `typedef Accessor AccessorClass;`
- L292 _public member_ `Accessor DataAccess;`
- L293 _public member_ `ULandscapeLayerInfoObject* LayerInfo = nullptr;`
- L295 _public function_ `TLandscapeEditCache(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : DataAccess(InLandscapeInfo, InLayerInfo) , LayerInfo(InLayerInfo) , LandscapeInfo(InLandscapeInfo)`
- L306 _public function_ `void CacheData(int32 X1, int32 Y1, int32 X2, int32 Y2, bool bCacheOriginalData = false)` — X2/Y2 Coordinates are "inclusive" max values ...but can extend outside valid landscape coords.  GetData/GetDataFast will generate and store values for out-of-range coords and then return coords clamped to the valid range. Note that this should maybe be called "ExtendDataCache" because the region here will be combined with the existing cached region, not loaded independently, giving a cached region that is the bounding box of previous and new
- L412 _public function_ `void CacheDataDirect(FIntRect NewDataRect, FIntRect RequestedRect, FIntRect LandscapeExtent, TConstArrayView<AccessorType> Data)` — Store data in the cache from some external source. Rect is half-open (exclusive), not inclusive like CacheData.
- L469 _public function_ `AccessorType* GetValueRef(int32 LandscapeX, int32 LandscapeY)`
- L474 _public function_ `float GetValue(float LandscapeX, float LandscapeY)`
- L495 _public function_ `FVector GetNormal(int32 X, int32 Y)`
- L518 _public function_ `void SetValue(int32 LandscapeX, int32 LandscapeY, AccessorType Value)`
- L523 _public function_ `bool IsZeroValue(const FVector& Value)`
- L528 _public function_ `bool IsZeroValue(const FVector2D& Value)`
- L533 _public function_ `bool IsZeroValue(const uint16& Value)`
- L538 _public function_ `bool IsZeroValue(const uint8& Value)`
- L543 _public function_ `bool HasCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2) const`
- L548 _public function_ `bool GetDataAndCacheWithVisibilityOverride(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& OutData, TBitArray<> LayerVisibility, ALandscape* Landscape)`
- L618 _public function_ `bool GetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& OutData)` — X2/Y2 Coordinates are "inclusive" max values
- L655 _public function_ `void SetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& Data, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None, bool bUpdateData = true)` — X2/Y2 Coordinates are "inclusive" max values
- L679 _public function_ `void GetOriginalData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<AccessorType>& OutOriginalData)` — Get the original data before we made any changes with the SetCachedData interface. X2/Y2 Coordinates are "inclusive" max values
- L697 _public function_ `void Flush()`
- L705 _private function_ `void CacheOriginalData(int32 X1, int32 Y1, int32 X2, int32 Y2)` — X2/Y2 Coordinates are "inclusive" max values
- L723 _private function_ `void VisualizeLandscapeRegion(int32 InX1, int32 InY1, int32 InX2, int32 InY2, const FColor& InColor, const FString& InDescription, double InZOffset = 0.0f)` — X2/Y2 Coordinates are "inclusive" max values
- L739 _private member_ `TMap<FIntPoint, AccessorType> CachedData;`
- L740 _private member_ `TMap<FIntPoint, AccessorType> OriginalData;`
- L742 _private member_ `TWeakObjectPtr<ULandscapeInfo> LandscapeInfo;` — Keep the landscape info for visual logging purposes :
- L744 _private member_ `bool bIsValid = false;`
- L747 _private member_ `int32 CachedX1 = INDEX_NONE;` — Inclusive bounds of the current cached region (CachedData)
- L748 _private member_ `int32 CachedY1 = INDEX_NONE;`
- L749 _private member_ `int32 CachedX2 = INDEX_NONE;`
- L750 _private member_ `int32 CachedY2 = INDEX_NONE;`

#### struct `FHeightmapAccessorTool`  
`template<bool bInUseInterp> struct FHeightmapAccessorTool : public FHeightmapAccessor<bInUseInterp>`  
_L754-762_
- inherits: `FHeightmapAccessor<bInUseInterp>`
- L756 _public function_ `FHeightmapAccessorTool(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : FHeightmapAccessor<bInUseInterp>(InLandscapeInfo, InLayerInfo)`

#### struct `FLandscapeHeightCache`  
`struct FLandscapeHeightCache : public TLandscapeEditCache<FHeightmapAccessorTool< true>, uint16>`  
_L764-774_
- inherits: `TLandscapeEditCache<FHeightmapAccessorTool<true>,uint16>`
- L766 _public function_ `static uint16 ClampValue(int32 Value)`
- L768 _public function_ `FLandscapeHeightCache(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : TLandscapeEditCache<FHeightmapAccessorTool< true>, uint16>(InLandscapeInfo, nullptr)`

#### struct `TAlphamapAccessorTool`  
`template<bool bInUseInterp> struct TAlphamapAccessorTool : public TAlphamapAccessor<bInUseInterp>`  
_L777-782_
- inherits: `TAlphamapAccessor<bInUseInterp>`
- L779 _public function_ `TAlphamapAccessorTool(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : TAlphamapAccessor<bInUseInterp>(InLandscapeInfo, InLayerInfo)`

#### struct `FLandscapeAlphaCache`  
`struct FLandscapeAlphaCache : public TLandscapeEditCache<TAlphamapAccessorTool< true>, uint8>`  
_L784-792_
- inherits: `TLandscapeEditCache<TAlphamapAccessorTool<true>,uint8>`
- L786 _public function_ `static uint8 ClampValue(int32 Value)`
- L788 _public function_ `FLandscapeAlphaCache(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : TLandscapeEditCache<TAlphamapAccessorTool< true>, uint8>(InLandscapeInfo, InLayerInfo)`

#### struct `FLandscapeVisCache`  
`struct FLandscapeVisCache : public TLandscapeEditCache<TAlphamapAccessorTool< false>, uint8>`  
_L794-802_
- inherits: `TLandscapeEditCache<TAlphamapAccessorTool<false>,uint8>`
- L796 _public function_ `static uint8 ClampValue(int32 Value)`
- L798 _public function_ `FLandscapeVisCache(ULandscapeInfo* InLandscapeInfo) : TLandscapeEditCache<TAlphamapAccessorTool< false>, uint8>(InLandscapeInfo, ALandscapeProxy::VisibilityLayer)`

#### class `FLandscapeEditLayerStackDataCache`  
`template<class ToolTarget> class FLandscapeEditLayerStackDataCache`  
_L807-939_
- desc: Allows to cache data from the combined edit layer stack (from the bottom of the stack up to the specified edit layer if bCombinedLayerOperation, normal cache operation otherwise
- L810 _public function_ `FLandscapeEditLayerStackDataCache(ULandscapeInfo* InLandscapeInfo, ToolTarget::CacheClass& Cache) : LandscapeInfo(InLandscapeInfo) , Landscape(nullptr) , EditingLayerGuid() , EditingLayerIndex(MAX_uint8) , bIsInitialized(false) , bCombinedLayerOperation(false) , bTargetIsHeightmap(ToolTarget::TargetType == ELandscapeToolTargetType::Heightmap) , CacheUpToEditingLayer(Cache) , CacheBottomLayers(InLandscapeInfo, Cache.LayerInfo)`
- L823 _public function_ `void SetCacheEditingLayer(const FGuid& InEditLayerGUID)`
- L830 _public function_ `void Initialize(bool bInCombinedLayerOperation)`
- L856 _public function_ `void Read(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<typename ToolTarget::CacheClass::DataType>& Data)` — read values in the specified rectangle into the array
- L889 _public function_ `void Write(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<typename ToolTarget::CacheClass::DataType>& Data, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None)`
- L927 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L928 _private member_ `ALandscape* Landscape;`
- L929 _private member_ `TOptional<FGuid> EditingLayerGuid;`
- L930 _private member_ `uint8 EditingLayerIndex;`
- L931 _private member_ `TBitArray<> BackupLayerVisibility;`
- L932 _private member_ `TArray<typename ToolTarget::CacheClass::DataType> BottomLayersData;`
- L933 _private member_ `bool bIsInitialized;`
- L934 _private member_ `bool bCombinedLayerOperation;`
- L935 _private member_ `bool bTargetIsHeightmap;`
- L937 _private member_ `typename ToolTarget::CacheClass& CacheUpToEditingLayer;`
- L938 _private member_ `typename ToolTarget::CacheClass CacheBottomLayers;`

#### struct `FFullWeightmapAccessor`  
`template<bool bInUseInterp> struct FFullWeightmapAccessor`  
_L945-998_
- desc: FFullWeightmapAccessor
- L948 _public function_ `FFullWeightmapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : LandscapeInfo(InLandscapeInfo) , LandscapeEdit(InLandscapeInfo)`
- L955 _public function_ `void SetEditLayer(const FGuid& InEditLayerGUID)`
- L960 _public function_ `FGuid GetEditLayer() const`
- L965 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, TArray<uint8>>& Data)`
- L971 _public function_ `void GetDataFast(int32 X1, int32 Y1, int32 X2, int32 Y2, TMap<FIntPoint, TArray<uint8>>& Data)`
- L977 _public function_ `void SetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint8* Data, ELandscapeLayerPaintingRestriction PaintingRestriction)`
- L987 _public function_ `void Flush()`
- L992 _public member_ `TSet<ULandscapeLayerInfoObject*> DirtyLayerInfos;`
- L995 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L996 _private member_ `FLandscapeEditDataInterface LandscapeEdit;`
- L997 _private member_ `TSet<ULandscapeComponent*> ModifiedComponents;`

#### enum `FFullWeightmapAccessor::(anonymous)`  
`enum`  
_L947-947_

#### struct `FLandscapeFullWeightCache`  
`struct FLandscapeFullWeightCache : public TLandscapeEditCache<FFullWeightmapAccessor<false>, TArray<uint8>>`  
_L1000-1072_
- inherits: `TLandscapeEditCache<FFullWeightmapAccessor<false>,TArray<uint8>>`
- L1002 _public function_ `FLandscapeFullWeightCache(ULandscapeInfo* InLandscapeInfo) : TLandscapeEditCache<FFullWeightmapAccessor< false>, TArray<uint8>>(InLandscapeInfo, nullptr)`
- L1008 _public function_ `void GetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<uint8>& OutData, int32 ArraySize)` — Only for all weight case... the accessor type should be TArray<uint8>
- L1046 _public function_ `void SetCachedData(int32 X1, int32 Y1, int32 X2, int32 Y2, TArray<uint8>& Data, int32 ArraySize, ELandscapeLayerPaintingRestriction PaintingRestriction)` — Only for all weight case... the accessor type should be TArray<uint8>
- L1068 _public function_ `void AddDirtyLayer(ULandscapeLayerInfoObject* InLayerInfo)`

#### struct `FDatamapAccessor`  
`template<bool bInUseInterp> struct FDatamapAccessor`  
_L1078-1113_
- desc: FDatamapAccessor
- L1081 _public function_ `FDatamapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : LandscapeEdit(InLandscapeInfo)`
- L1088 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, uint8>& Data)`
- L1093 _public function_ `void GetDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint8>& Data)`
- L1098 _public function_ `void SetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint8* Data, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None)`
- L1106 _public function_ `void Flush()`
- L1112 _private member_ `FLandscapeEditDataInterface LandscapeEdit;`

#### enum `FDatamapAccessor::(anonymous)`  
`enum`  
_L1080-1080_

#### struct `FLandscapeDataCache`  
`struct FLandscapeDataCache : public TLandscapeEditCache<FDatamapAccessor< false>, uint8>`  
_L1115-1123_
- inherits: `TLandscapeEditCache<FDatamapAccessor<false>,uint8>`
- L1117 _public function_ `static uint8 ClampValue(int32 Value)`
- L1119 _public function_ `FLandscapeDataCache(ULandscapeInfo* InLandscapeInfo) : TLandscapeEditCache<FDatamapAccessor< false>, uint8>(InLandscapeInfo, nullptr)`

#### struct `FHeightmapToolTarget`  
`struct FHeightmapToolTarget`  
_L1129-1157_
- desc: Tool targets
- L1131 _public typedef_ `typedef FLandscapeHeightCache CacheClass;`
- L1132 _public member_ `static const ELandscapeToolTargetType TargetType = ELandscapeToolTargetType::Heightmap;`
- L1134 _public function_ `static float StrengthMultiplier(ULandscapeInfo* LandscapeInfo, float BrushRadius)`
- L1144 _public function_ `static FMatrix ToWorldMatrix(ULandscapeInfo* LandscapeInfo)`
- L1151 _public function_ `static FMatrix FromWorldMatrix(ULandscapeInfo* LandscapeInfo)`

#### struct `FWeightmapToolTarget`  
`struct FWeightmapToolTarget`  
_L1160-1172_
- L1162 _public typedef_ `typedef FLandscapeAlphaCache CacheClass;`
- L1163 _public member_ `static const ELandscapeToolTargetType TargetType = ELandscapeToolTargetType::Weightmap;`
- L1165 _public function_ `static float StrengthMultiplier(ULandscapeInfo* LandscapeInfo, float BrushRadius)`
- L1170 _public function_ `static FMatrix ToWorldMatrix(ULandscapeInfo* LandscapeInfo)`
- L1171 _public function_ `static FMatrix FromWorldMatrix(ULandscapeInfo* LandscapeInfo)`

#### class `FLandscapeToolStrokeBase`  
`class FLandscapeToolStrokeBase : protected FGCObject`  
_L1178-1221_
- inherits: `FGCObject`
- L1182 _public function_ `FLandscapeToolStrokeBase(FEdModeLandscape* InEdMode, FEditorViewportClient* InViewportClient, const FLandscapeToolTarget& InTarget) : EdMode(InEdMode) , LandscapeInfo(InTarget.LandscapeInfo.Get())` — This is also the expected signature of derived class constructor used by FLandscapeToolBase
- L1191 _public function_ `virtual void SetEditLayer(const FGuid& EditLayerGUID)`
- L1201 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L1206 _public function_ `virtual FString GetReferencerName() const override`
- L1211 _public function_ `bool GetUseContinuousApply() const`
- L1217 _protected member_ `FEdModeLandscape* EdMode = nullptr;`
- L1218 _protected member_ `TObjectPtr<ULandscapeInfo> LandscapeInfo = nullptr;`
- L1220 _protected member_ `bool bUseContinuousApply = false;` — Whether to call Apply() every frame even if the mouse hasn't moved.  May be overwritten by child classes.

#### class `FLandscapeToolBase`  
`template<class TStrokeClass> class FLandscapeToolBase : public FLandscapeTool`  
_L1229-1433_
- inherits: `FLandscapeTool`
- desc: FLandscapeToolBase - base class for painting tools ToolTarget - the target for the tool (weight or heightmap) StrokeClass - the class that implements the behavior for a mouse stroke applying the tool.
- L1231 _private typedef_ `using Super = FLandscapeTool;`
- L1234 _public function_ `FLandscapeToolBase(FEdModeLandscape* InEdMode) : LastInteractorPosition(FVector2D::ZeroVector) , TimeSinceLastInteractorMove(0.0f) , EdMode(InEdMode) , bCanToolBeActivated(true) , ToolStroke()`
- L1243 _public function_ `virtual bool ShouldUpdateEditingLayer() const`
- L1248 _public function_ `virtual ELandscapeLayerUpdateMode GetBeginToolContentUpdateFlag() const`
- L1254 _public function_ `virtual ELandscapeLayerUpdateMode GetTickToolContentUpdateFlag() const`
- L1259 _public function_ `virtual ELandscapeLayerUpdateMode GetEndToolContentUpdateFlag() const`
- L1265 _public function_ `virtual bool BeginTool(FEditorViewportClient* ViewportClient, const FLandscapeToolTarget& InTarget, const FVector& InHitLocation) override`
- L1303 _public function_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override`
- L1338 _public function_ `virtual void EndTool(FEditorViewportClient* ViewportClient) override`
- L1364 _public function_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override`
- L1404 _public function_ `virtual bool IsToolActive() const override`
- L1406 _public function_ `virtual void SetCanToolBeActivated(bool Value)`
- L1407 _public function_ `virtual bool CanToolBeActivated() const`
- L1409 _public function_ `virtual ELandscapeTargetLayerActionType GetTargetLayerActionType(const ULandscapeLayerInfoObject* InLayerInfo, bool bInIsModifierPressed, bool bInIsAlternateModifierPressed) const override`
- L1415 _protected member_ `TArray<FLandscapeToolInteractorPosition> InteractorPositions;`
- L1416 _protected member_ `FVector2D LastInteractorPosition;`
- L1417 _protected member_ `float TimeSinceLastInteractorMove;`
- L1418 _protected member_ `FEdModeLandscape* EdMode;`
- L1419 _protected member_ `bool bCanToolBeActivated;`
- L1420 _protected member_ `TOptional<TStrokeClass> ToolStroke;`
- L1422 _protected function_ `bool IsModifierPressed(const class FEditorViewportClient* ViewportClient)`
- L1428 _protected function_ `bool IsAlternateModifierPressed(const FEditorViewportClient* ViewportClient)`

#### Free symbols / members of external scopes

- L169 _function_ `template<typename DataType> inline void LowPassFilter(int32 X1, int32 Y1, int32 X2, int32 Y2, FLandscapeBrushData& BrushInfo, TArray<DataType>& Data, const float DetailScale, const float ApplyRatio = 1.0f)`
- L349 _function_ `` (scope `TLandscapeEditCache::CacheData`)
- L434 _function_ `` (scope `TLandscapeEditCache::CacheDataDirect`)
- L947 _enumerator_ `enum { bUseInterp = bInUseInterp }; FFullWeightmapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : LandscapeInfo(InLandscapeInfo)` (scope `FFullWeightmapAccessor::__anon768920770303`)
- L1080 _enumerator_ `enum { bUseInterp = bInUseInterp }; FDatamapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : LandscapeEdit(InLandscapeInfo) { check(InLayerInfo == nullptr); }` (scope `FDatamapAccessor::__anon768920770403`)

### `Source/Editor/LandscapeEditor/Private/LandscapeEditLayerObjectNameEditSink.h` (Private)


#### class `FLandscapeEditLayerObjectNameEditSink`  
`class FLandscapeEditLayerObjectNameEditSink : public UE::EditorWidgets::IObjectNameEditSink`  
_L11-44_
- inherits: `UE::EditorWidgets::IObjectNameEditSink`
- L13 _private function_ `virtual UClass* GetSupportedClass() const override`
- L18 _private function_ `virtual FText GetObjectDisplayName(UObject* Object) const override`
- L24 _private function_ `virtual bool IsObjectDisplayNameReadOnly(UObject* Object) const override`
- L29 _private function_ `virtual bool SetObjectDisplayName(UObject* Object, FString DisplayName) override`
- L40 _private function_ `virtual FText GetObjectNameTooltip(UObject* Object) const override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define LOCTEXT_NAMESPACE "LandscapeEditLayer"`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorCommands.h` (Private)


#### class `FLandscapeEditorCommands`  
`class FLandscapeEditorCommands : public TCommands<FLandscapeEditorCommands>`  
_L15-100_
- inherits: `TCommands<FLandscapeEditorCommands>`
- desc: Unreal landscape editor actions
- L19 _public prototype_ `FLandscapeEditorCommands();`
- L25 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L28 _public member_ `static FName LandscapeContext;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ManageMode;` — Mode Switch
- L32 _public member_ `TSharedPtr<FUICommandInfo> SculptMode;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> PaintMode;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> NewLandscape;` — Tools
- L37 _public member_ `TSharedPtr<FUICommandInfo> ResizeLandscape;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ImportExportTool;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> SculptTool;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> EraseTool;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> PaintTool;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> SmoothTool;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> FlattenTool;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> RampTool;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ErosionTool;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> HydroErosionTool;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> NoiseTool;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> VisibilityTool;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> BlueprintBrushTool;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> SelectComponentTool;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> AddComponentTool;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> DeleteComponentTool;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> MoveToLevelTool;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> RegionSelectTool;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> RegionCopyPasteTool;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> MirrorTool;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> SplineTool;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> CircleBrush;` — Brushes
- L65 _public member_ `TSharedPtr<FUICommandInfo> AlphaBrush;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> AlphaBrush_Pattern;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> ComponentBrush;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> GizmoBrush;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> CircleBrush_Smooth;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> CircleBrush_Linear;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> CircleBrush_Spherical;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> CircleBrush_Tip;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> ViewModeNormal;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLOD;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLayerDensity;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLayerDebug;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> ViewModeWireframeOnTop;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLayerUsage;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> ViewModeLayerContribution;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushSize;` — Adjusting brushes
- L85 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushSize;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushFalloff;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushFalloff;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> IncreaseBrushStrength;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> DecreaseBrushStrength;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> IncreaseAlphaBrushRotation;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> DecreaseAlphaBrushRotation;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> DragBrushSizeAndFalloff;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> DragBrushSize;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> DragBrushFalloff;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> DragBrushStrength;`
- L99 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> NameToCommandMap;` — Map

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_AlphaBrush.h` (Private)


#### class `FLandscapeEditorDetailCustomization_AlphaBrush`  
`class FLandscapeEditorDetailCustomization_AlphaBrush : public FLandscapeEditorDetailCustomization_Base`  
_L18-30_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L28 _protected prototype_ `static bool OnAssetDraggedOver(TArrayView<FAssetData> InAssets);`
- L29 _protected prototype_ `static void OnAssetDropped(const FDragDropEvent&, TArrayView<FAssetData> InAssets, TSharedRef<IPropertyHandle> PropertyHandle_AlphaTexture);`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_Base.h` (Private)


#### class `FLandscapeEditorDetailCustomization_Base`  
`class FLandscapeEditorDetailCustomization_Base : public IDetailCustomization`  
_L17-50_
- inherits: `IDetailCustomization`
- desc: Slate widgets customizers for the Landscape Editor
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override = 0;` — IDetailCustomization interface
- L24 _protected prototype_ `static FEdModeLandscape* GetEditorMode();`
- L25 _protected prototype_ `static bool IsToolActive(FName ToolName);`
- L26 _protected prototype_ `static bool IsBrushSetActive(FName BrushSetName);`
- L29 _protected prototype_ `template<typename type> static TOptional<type> OnGetValue(TSharedRef<IPropertyHandle> PropertyHandle);`
- L32 _protected prototype_ `template<typename type> static void OnValueChanged(type NewValue, TSharedRef<IPropertyHandle> PropertyHandle);`
- L35 _protected prototype_ `template<typename type> static void OnValueCommitted(type NewValue, ETextCommit::Type CommitType, TSharedRef<IPropertyHandle> PropertyHandle);`
- L38 _protected prototype_ `template<typename type> static type GetPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);`
- L41 _protected prototype_ `template<typename type> static TOptional<type> GetOptionalPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);`
- L44 _protected prototype_ `template<typename type> static type* GetObjectPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle);`
- L46 _protected prototype_ `static FText GetPropertyValueText(TSharedRef<IPropertyHandle> PropertyHandle);`
- L49 _protected prototype_ `template<typename type> static void SetPropertyValue(type NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle);`
- L53 _function_ `template<typename type> TOptional<type> FLandscapeEditorDetailCustomization_Base::OnGetValue(TSharedRef<IPropertyHandle> PropertyHandle)`
- L66 _function_ `template<typename type> void FLandscapeEditorDetailCustomization_Base::OnValueChanged(type NewValue, TSharedRef<IPropertyHandle> PropertyHandle)`
- L73 _function_ `template<typename type> void FLandscapeEditorDetailCustomization_Base::OnValueCommitted(type NewValue, ETextCommit::Type CommitType, TSharedRef<IPropertyHandle> PropertyHandle)`
- L79 _function_ `template<typename type> type FLandscapeEditorDetailCustomization_Base::GetPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)`
- L92 _function_ `template<typename type> TOptional<type> FLandscapeEditorDetailCustomization_Base::GetOptionalPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)`
- L105 _function_ `template<typename type> type* FLandscapeEditorDetailCustomization_Base::GetObjectPropertyValue(TSharedRef<IPropertyHandle> PropertyHandle)`
- L117 _function_ `inline FText FLandscapeEditorDetailCustomization_Base::GetPropertyValueText(TSharedRef<IPropertyHandle> PropertyHandle)`
- L129 _function_ `template<typename type> void FLandscapeEditorDetailCustomization_Base::SetPropertyValue(type NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle)`

#### class `FLandscapeEditorStructCustomization_Base`  
`class FLandscapeEditorStructCustomization_Base : public IPropertyTypeCustomization`  
_L134-139_
- inherits: `IPropertyTypeCustomization`
- L137 _protected prototype_ `static FEdModeLandscape* GetEditorMode();`
- L138 _protected prototype_ `static bool IsToolActive(FName ToolName);`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_Blueprint.h` (Private)


#### class `FLandscapeEditorDetailCustomization_Blueprint`  
`class FLandscapeEditorDetailCustomization_Blueprint : public FLandscapeEditorDetailCustomization_Base`  
_L14-22_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- desc: Slate widgets customizer for the "Blueprint Brush" Landscape tool
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_CopyPaste.h` (Private)


#### class `FLandscapeEditorDetailCustomization_CopyPaste`  
`class FLandscapeEditorDetailCustomization_CopyPaste : public FLandscapeEditorDetailCustomization_Base`  
_L18-45_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L28 _public prototype_ `FReply OnCopyToGizmoButtonClicked();`
- L29 _public prototype_ `FReply OnFitGizmoToSelectionButtonClicked();`
- L30 _public prototype_ `FReply OnFitHeightsToGizmoButtonClicked();`
- L31 _public prototype_ `FReply OnClearGizmoDataButtonClicked();`
- L32 _public prototype_ `FReply OnGizmoHeightmapFilenameButtonClicked(TSharedRef<IPropertyHandle> HeightmapPropertyHandle);`
- L34 _public prototype_ `bool GetGizmoImportButtonIsEnabled() const;`
- L35 _public prototype_ `bool GetGizmoGuessSizeButtonIsEnabled() const;`
- L37 _public prototype_ `FReply OnGizmoImportButtonClicked();`
- L38 _public prototype_ `FReply OnGizmoExportButtonClicked();`
- L41 _private member_ `TArray<TSharedPtr<FString>> GuessedDimensionComboList;`
- L42 _private member_ `FString CurrentGuessedDimension;`
- L44 _private prototype_ `void GenerateGuessDimensionList();`

#### class `FLandscapeEditorStructCustomization_FGizmoImportLayer`  
`class FLandscapeEditorStructCustomization_FGizmoImportLayer : public FLandscapeEditorStructCustomization_Base`  
_L47-57_
- inherits: `FLandscapeEditorStructCustomization_Base`
- L50 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L52 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L53 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L56 _public prototype_ `FReply OnGizmoImportLayerFilenameButtonClicked(TSharedRef<IPropertyHandle> PropertyHandle_LayerFilename);`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_EditLayers.h` (Private)


#### class `FLandscapeEditLayerCustomizationCommon`  
`class FLandscapeEditLayerCustomizationCommon`  
_L16-42_
- desc: Edit layer common editor functionality
- L19 _protected prototype_ `static FEdModeLandscape* GetEditorMode();`
- L21 _protected prototype_ `bool CanDeleteLayer(int32 InLayerIndex, FText& OutReason) const;`
- L22 _protected prototype_ `void DeleteLayer(int32 InLayerIndex);`
- L24 _protected prototype_ `bool CanCollapseLayer(int32 InLayerIndex, FText& OutReason) const;`
- L25 _protected prototype_ `void CollapseLayer(int32 InLayerIndex);`
- L27 _protected prototype_ `bool CanCollapseAllLayers(FText& OutReason) const;`
- L28 _protected prototype_ `void CollapseAllEditLayers();`
- L30 _protected prototype_ `bool CanToggleVisibility(int32 InLayerIndex, FText& OutReason) const;`
- L31 _protected prototype_ `FReply OnToggleVisibility(int32 InLayerIndex);`
- L32 _protected prototype_ `const FSlateBrush* GetVisibilityBrushForLayer(int32 InLayerIndex) const;`
- L34 _protected prototype_ `void OnLayerSelectionChanged(int32 LayerIndex);`
- L35 _protected prototype_ `void ShowOnlySelectedLayer(int32 InLayerIndex);`
- L36 _protected prototype_ `void ShowAllLayers();`
- L38 _protected prototype_ `TOptional<float> GetLayerAlpha(int32 InLayerIndex) const;`
- L39 _protected prototype_ `float GetLayerAlphaMinValue() const;`
- L40 _protected prototype_ `bool CanSetLayerAlpha(int32 InLayerIndex, FText& OutReason) const;`
- L41 _protected prototype_ `void SetLayerAlpha(float InAlpha, int32 InLayerIndex, bool bCommit, int32 InSliderIndex);`

#### class `FLandscapeEditLayerContextMenuCustomization_Base`  
`class FLandscapeEditLayerContextMenuCustomization_Base : public IEditLayerCustomization, public FLandscapeEditLayerCustomizationCommon`  
_L45-52_
- inherits: `IEditLayerCustomization,FLandscapeEditLayerCustomizationCommon`
- desc: Edit layer customizations for ULandscapeEditLayerBase
- L48 _public prototype_ `static TSharedRef<IEditLayerCustomization> MakeInstance();`
- L51 _public prototype_ `virtual void CustomizeContextMenu(ULandscapeEditLayerBase* InEditLayer, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) override;` — IEditLayerCustomization interface

#### class `FLandscapeEditLayerContextMenuCustomization_Layer`  
`class FLandscapeEditLayerContextMenuCustomization_Layer : public IEditLayerCustomization, public FLandscapeEditLayerCustomizationCommon`  
_L55-67_
- inherits: `IEditLayerCustomization,FLandscapeEditLayerCustomizationCommon`
- desc: Edit layer customizations for ULandscapeEditLayer
- L58 _public prototype_ `static TSharedRef<IEditLayerCustomization> MakeInstance();`
- L61 _public prototype_ `virtual void CustomizeContextMenu(ULandscapeEditLayerBase* InEditLayer, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) override;` — IEditLayerCustomization interface
- L65 _private prototype_ `void FillUnassignedBrushMenu(FMenuBuilder& MenuBuilder, TArray<ALandscapeBlueprintBrushBase*> Brushes, int32 InLayerIndex);` — Add Existing BP Brush (Brushes with no landscape actor assigned)
- L66 _private prototype_ `void AssignBrushToEditLayer(ALandscapeBlueprintBrushBase* Brush, int32 InLayerIndex);`

#### class `FLandscapeEditLayerContextMenuCustomization_Persistent`  
`class FLandscapeEditLayerContextMenuCustomization_Persistent : public IEditLayerCustomization, public FLandscapeEditLayerCustomizationCommon`  
_L70-82_
- inherits: `IEditLayerCustomization,FLandscapeEditLayerCustomizationCommon`
- desc: Edit layer customizations for ULandscapeEditLayerPersistent
- L73 _public prototype_ `static TSharedRef<IEditLayerCustomization> MakeInstance();`
- L76 _public prototype_ `virtual void CustomizeContextMenu(ULandscapeEditLayerBase* InEditLayer, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) override;` — IEditLayerCustomization interface
- L80 _private prototype_ `void ClearEditLayerData(int32 InEditLayerIndex, ELandscapeToolTargetType InClearMode);` — Weightmap/Heightmap related functions
- L81 _private prototype_ `bool CanClearEditLayerData(int32 InEditLayerIndex, ELandscapeToolTargetType InClearMode, FText& OutToolTip) const;`

#### class `FLandscapeEditLayerContextMenuCustomization_Splines`  
`class FLandscapeEditLayerContextMenuCustomization_Splines : public IEditLayerCustomization, public FLandscapeEditLayerCustomizationCommon`  
_L85-92_
- inherits: `IEditLayerCustomization,FLandscapeEditLayerCustomizationCommon`
- desc: Edit layer customizations for ULandscapeEditLayerSplines
- L88 _public prototype_ `static TSharedRef<IEditLayerCustomization> MakeInstance();`
- L91 _public prototype_ `virtual void CustomizeContextMenu(ULandscapeEditLayerBase* InEditLayer, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) override;` — IEditLayerCustomization interface

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_EditLayersStack.h` (Private)


#### class `FLandscapeEditorDetailCustomization_EditLayersStack`  
`class FLandscapeEditorDetailCustomization_EditLayersStack : public FLandscapeEditorDetailCustomization_Base`  
_L37-49_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L41 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L44 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L47 _protected prototype_ `static bool ShouldShowLayersErrorMessageTip();`
- L48 _protected prototype_ `static FText GetLayersErrorMessageText();`

#### class `FLandscapeEditorCustomNodeBuilder_Layers`  
`class FLandscapeEditorCustomNodeBuilder_Layers : public IDetailCustomNodeBuilder, public TSharedFromThis<FLandscapeEditorCustomNodeBuilder_Layers>, public FLandscapeEditLayerCustomizationCommon`  
_L51-115_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FLandscapeEditorCustomNodeBuilder_Layers>,FLandscapeEditLayerCustomizationCommon`
- L54 _public prototype_ `FLandscapeEditorCustomNodeBuilder_Layers();`
- L55 _public prototype_ `~FLandscapeEditorCustomNodeBuilder_Layers();`
- L57 _public prototype_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override;`
- L58 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L59 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L60 _public function_ `virtual void Tick( float DeltaTime ) override`
- L61 _public function_ `virtual bool RequiresTick() const override`
- L62 _public function_ `virtual bool InitiallyCollapsed() const override`
- L63 _public function_ `virtual FName GetName() const override`
- L66 _protected prototype_ `static class FEdModeLandscape* GetEditorMode();`
- L68 _protected prototype_ `TSharedPtr<SWidget> GenerateRow(int32 InLayerIndex);`
- L71 _protected prototype_ `int32 SlotIndexToLayerIndex(int32 SlotIndex);` — Drag/Drop handling
- L72 _protected prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L73 _protected prototype_ `TOptional<SDragAndDropVerticalBox::EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L74 _protected prototype_ `FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L76 _protected prototype_ `bool IsLayerSelected(int32 LayerIndex) const;`
- L77 _protected prototype_ `void OnLayerDoubleClick(int32 LayerIndex) const;`
- L78 _protected prototype_ `TSharedPtr<SWidget> OnLayerContextMenuOpening(int32 InLayerIndex);`
- L80 _protected prototype_ `FText GetNumLayersText() const;`
- L82 _protected prototype_ `bool CanCreateLayer(FText& OutReason) const;`
- L83 _protected prototype_ `void CreateLayer();`
- L85 _protected prototype_ `const FSlateBrush* GetEditLayerIconBrush(int32 InLayerIndex) const;`
- L87 _protected prototype_ `bool CanRenameLayerTo(const FText& NewText, FText& OutErrorMessage, int32 InLayerIndex);`
- L88 _protected prototype_ `bool CanRenameLayer(int32 InLayerIndex, FText& OutReason) const;`
- L89 _protected prototype_ `void RenameLayer(int32 InLayerIndex);`
- L91 _protected prototype_ `void SetLayerName(const FText& InText, ETextCommit::Type InCommitType, int32 InLayerIndex);`
- L92 _protected prototype_ `FText GetLayerText(int32 InLayerIndex) const;`
- L93 _protected prototype_ `FSlateColor GetLayerTextColor(int32 InLayerIndex) const;`
- L94 _protected prototype_ `FText GetLayerDisplayName(int32 InLayerIndex) const;`
- L95 _protected prototype_ `EVisibility GetLayerAlphaVisibility(int32 InLayerIndex) const;`
- L96 _protected prototype_ `FText GetEditLayerShortTooltipText(int32 InEditLayerIndex) const;`
- L97 _protected prototype_ `FReply OnEditLayerIconClicked(int32 InEditLayerIndex) const;`
- L99 _protected prototype_ `TSubclassOf<ULandscapeEditLayerBase> PickEditLayerClass() const;`
- L101 _protected prototype_ `void OnSetInspectedDetailsToEditLayer(int32 InLayerIndex) const;`
- L103 _protected prototype_ `FReply OnToggleLock(int32 InLayerIndex);`
- L104 _protected prototype_ `const FSlateBrush* GetLockBrushForLayer(int32 InLayerIndex) const;`
- L109 _private member_ `TArray< TSharedPtr< SInlineEditableTextBlock > > InlineTextBlocks;` — Widgets for displaying and editing the layer name
- L112 _private member_ `TArray<TSharedRef<IEditLayerCustomization>> EditLayerCustomizationClassInstances;` — The edit layer customization class instances active in this view
- L114 _private member_ `int32 CurrentSlider;`

#### class `FLandscapeListElementDragDropOp`  
`class FLandscapeListElementDragDropOp : public FDragAndDropVerticalBoxOp`  
_L117-130_
- inherits: `FDragAndDropVerticalBoxOp`
- L120 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FLandscapeListElementDragDropOp, FDragAndDropVerticalBoxOp) TSharedPtr<SWidget> WidgetToShow;`
- L124 _public prototype_ `static TSharedRef<FLandscapeListElementDragDropOp> New(int32 InSlotIndexBeingDragged, SVerticalBox::FSlot* InSlotBeingDragged, TSharedPtr<SWidget> InWidgetToShow);`
- L127 _public prototype_ `virtual ~FLandscapeListElementDragDropOp() = default;`
- L129 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_ImportExport.h` (Private)


#### class `FLandscapeEditorDetailCustomization_ImportExport`  
`class FLandscapeEditorDetailCustomization_ImportExport : public FLandscapeEditorDetailCustomization_Base`  
_L26-72_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L31 _public function_ `FLandscapeEditorDetailCustomization_ImportExport()`
- L35 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L38 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L40 _public prototype_ `static void FormatFilename(TSharedRef<IPropertyHandle> PropertyHandle_Filename, bool bForExport);`
- L42 _private prototype_ `static bool GetExportSingleFileIsEnabled();`
- L43 _private prototype_ `static ECheckBoxState GetExportSingleFileCheckState();`
- L44 _private prototype_ `static void OnExportSingleFileCheckStateChanged(ECheckBoxState NewCheckState);`
- L45 _private prototype_ `static EVisibility GetImportExportVisibility(bool bImport);`
- L46 _private prototype_ `static bool IsHeightmapEnabled();`
- L47 _private prototype_ `static ECheckBoxState GetHeightmapSelectedCheckState();`
- L48 _private prototype_ `static void OnHeightmapSelectedCheckStateChanged(ECheckBoxState CheckState);`
- L49 _private prototype_ `static ECheckBoxState ModeIsChecked(EImportExportMode Value);`
- L50 _private prototype_ `static void OnModeChanged(ECheckBoxState NewCheckedState, EImportExportMode Value);`
- L52 _private prototype_ `static EVisibility GetImportResultErrorVisibility(TSharedRef<IPropertyHandle> PropertyHandle_ImportResult);`
- L53 _private prototype_ `static FSlateColor GetImportResultErrorColor(TSharedRef<IPropertyHandle> PropertyHandle_ImportResult);`
- L54 _private prototype_ `static void SetFilename(const FText& NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle_Filename);`
- L55 _private prototype_ `static FReply OnBrowseFilenameButtonClicked(TSharedRef<IPropertyHandle> PropertyHandle_Filename);`
- L57 _private prototype_ `static FText GetImportExportButtonText();`
- L58 _private prototype_ `static FReply OnImportExportButtonClicked();`
- L59 _private prototype_ `static bool GetImportExportButtonIsEnabled();`
- L61 _private prototype_ `EVisibility GetImportExportLandscapeErrorVisibility() const;`
- L62 _private prototype_ `EVisibility GetImportingVisibility() const;`
- L63 _private prototype_ `FText GetImportExportLandscapeErrorText() const;`
- L65 _private prototype_ `static TSharedRef<SWidget> GetImportLandscapeResolutionMenu();`
- L66 _private prototype_ `static void OnChangeImportLandscapeResolution(int32 DescriptorIndex);`
- L67 _private prototype_ `static FText GetImportLandscapeResolution();`
- L69 _private prototype_ `static void OnImportHeightmapFilenameChanged();`
- L71 _private prototype_ `static bool IsImporting();`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace LandscapeTestUtils`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_ImportLayers.h` (Private)


#### class `FLandscapeEditorStructCustomization_FLandscapeImportLayer`  
`class FLandscapeEditorStructCustomization_FLandscapeImportLayer : public FLandscapeEditorStructCustomization_Base`  
_L14-47_
- inherits: `FLandscapeEditorStructCustomization_Base`
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _private prototype_ `static void OnImportWeightmapFilenameChanged();`
- L24 _private prototype_ `static FReply OnLayerFilenameButtonClicked(TSharedRef<IPropertyHandle> PropertyHandle_LayerFilename);`
- L25 _private prototype_ `static bool ShouldFilterLayerInfo(const struct FAssetData& AssetData, FName LayerName);`
- L27 _private prototype_ `static EVisibility GetImportLayerCreateVisibility(TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo);`
- L28 _private prototype_ `static TSharedRef<SWidget> OnGetImportLayerCreateMenu(TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo, FName LayerName);`
- L29 _private prototype_ `static FReply OnImportLayerCreateClicked(const TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo, FName LayerName);`
- L30 _private prototype_ `static EVisibility GetImportLayerSelectionVisibility();`
- L31 _private prototype_ `static EVisibility GetImportExportVisibility(bool bImport);`
- L33 _private prototype_ `static EVisibility GetLayerInfoAssignVisibility();`
- L34 _private prototype_ `static EVisibility GetImportLayerVisibility();`
- L35 _private prototype_ `static EVisibility GetErrorVisibility(TSharedRef<IPropertyHandle> PropertyHandle_ImportResult);`
- L36 _private prototype_ `static FSlateColor GetErrorColor(TSharedRef<IPropertyHandle> PropertyHandle_ImportResult);`
- L37 _private prototype_ `static FText GetErrorText(TSharedRef<IPropertyHandle> PropertyHandle_ErrorMessage);`
- L39 _private prototype_ `static void OnResetFilePathButtonClicked(TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo, TSharedRef<IPropertyHandle> PropertyHandle_Selected, TSharedRef<IPropertyHandle> PropertyHandle_SourceFilePath, TSharedRef<IPropertyHandle> PropertyHandle_ExportFilePath);`
- L40 _private prototype_ `static bool IsResetFilePathButtonShown(TSharedRef<IPropertyHandle> PropertyHandle_Selected, TSharedRef<IPropertyHandle> PropertyHandle_SourceFilePath, TSharedRef<IPropertyHandle> PropertyHandle_ExportFilePath);`
- L41 _private prototype_ `static bool IsImportLayerSelected(TSharedRef<IPropertyHandle> PropertyHandle_Selected, TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo);`
- L42 _private prototype_ `static ECheckBoxState GetImportLayerSelectedCheckState(TSharedRef<IPropertyHandle> PropertyHandle_Selected, TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo);`
- L43 _private prototype_ `static void OnImportLayerSelectedCheckStateChanged(ECheckBoxState CheckState, TSharedRef<IPropertyHandle> PropertyHandle_Selected);`
- L44 _private prototype_ `static FText GetImportLayerSelectedToolTip(TSharedRef<IPropertyHandle> PropertyHandle_Selected, TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo);`
- L45 _private prototype_ `static bool IsValidLayerInfo(TSharedRef<IPropertyHandle> PropertyHandle_LayerInfo);`
- L46 _private prototype_ `static bool IsImporting();`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_LayersBrushStack.h` (Private)


#### class `FLandscapeEditorDetailCustomization_LayersBrushStack`  
`class FLandscapeEditorDetailCustomization_LayersBrushStack : public FLandscapeEditorDetailCustomization_Base`  
_L32-40_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L36 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `FLandscapeEditorCustomNodeBuilder_LayersBrushStack`  
`class FLandscapeEditorCustomNodeBuilder_LayersBrushStack : public IDetailCustomNodeBuilder, public TSharedFromThis<FLandscapeEditorCustomNodeBuilder_LayersBrushStack>`  
_L42-94_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FLandscapeEditorCustomNodeBuilder_LayersBrushStack>`
- L45 _public prototype_ `FLandscapeEditorCustomNodeBuilder_LayersBrushStack(TSharedRef<FAssetThumbnailPool> ThumbnailPool);`
- L46 _public prototype_ `~FLandscapeEditorCustomNodeBuilder_LayersBrushStack();`
- L48 _public prototype_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override;`
- L49 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L50 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L51 _public function_ `virtual void Tick( float DeltaTime ) override`
- L52 _public function_ `virtual bool RequiresTick() const override`
- L53 _public function_ `virtual bool InitiallyCollapsed() const override`
- L54 _public function_ `virtual FName GetName() const override`
- L57 _protected member_ `TSharedRef<FAssetThumbnailPool> ThumbnailPool;`
- L59 _protected prototype_ `static class FEdModeLandscape* GetEditorMode();`
- L61 _protected prototype_ `TSharedPtr<SWidget> GenerateRow(int32 InBrushIndex);`
- L62 _protected prototype_ `TSharedPtr<SWidget> OnBrushContextMenuOpening(int32 InBrushIndex);`
- L64 _protected prototype_ `FReply OnToggleVisibility(int32 InBrushIndex);`
- L65 _protected prototype_ `void OnToggleAffectsHeightmap(ECheckBoxState InCheckBoxState, int32 InBrushIndex);`
- L66 _protected prototype_ `void OnToggleAffectsWeightmap(ECheckBoxState InCheckBoxState, int32 InBrushIndex);`
- L67 _protected prototype_ `void OnToggleAffectsVisibilityLayer(ECheckBoxState InCheckBoxState, int32 InBrushIndex);`
- L69 _protected prototype_ `void OnToggleVisibility(ALandscapeBlueprintBrushBase* Brush);`
- L71 _protected prototype_ `const FSlateBrush* GetAffectsHeightmapBrush(int32 InBrushIndex) const;`
- L72 _protected prototype_ `bool IsAffectingHeightmap(int32 InBrushIndex) const;`
- L74 _protected prototype_ `const FSlateBrush* GetAffectsWeightmapBrush(int32 InBrushIndex) const;`
- L75 _protected prototype_ `bool IsAffectingWeightmap(int32 InBrushIndex) const;`
- L77 _protected prototype_ `const FSlateBrush* GetAffectsVisibilityLayerBrush(int32 InBrushIndex) const;`
- L78 _protected prototype_ `bool IsAffectingVisibilityLayer(int32 InBrushIndex) const;`
- L80 _protected prototype_ `const FSlateBrush* GetVisibilityBrush(int32 InBrushIndex) const;`
- L82 _protected prototype_ `bool IsBrushSelected(int32 InBrushIndex) const;`
- L83 _protected prototype_ `bool IsBrushEnabled(int32 InBrushIndex) const;`
- L84 _protected prototype_ `void OnBrushSelectionChanged(int32 InBrushIndex);`
- L85 _protected prototype_ `FText GetBrushText(int32 InBrushIndex) const;`
- L86 _protected prototype_ `FSlateColor GetBrushTextColor(int32 InBrushIndex) const;`
- L87 _protected prototype_ `ALandscapeBlueprintBrushBase* GetBrush(int32 InBrushIndex) const;`
- L88 _protected prototype_ `TArray<ALandscapeBlueprintBrushBase*> GetBrushes() const;`
- L91 _protected prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, int32 SlotIndex, SVerticalBox::FSlot* Slot);` — Drag/Drop handling
- L92 _protected prototype_ `TOptional<SDragAndDropVerticalBox::EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L93 _protected prototype_ `FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`

#### class `FLandscapeBrushDragDropOp`  
`class FLandscapeBrushDragDropOp : public FLandscapeListElementDragDropOp`  
_L96-106_
- inherits: `FLandscapeListElementDragDropOp`
- L99 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FLandscapeBrushDragDropOp, FLandscapeListElementDragDropOp) static TSharedRef<FLandscapeBrushDragDropOp> New(int32 InSlotIndexBeingDragged, SVerticalBox::FSlot* InSlotBeingDragged, TSharedPtr<SWidget> InWidgetToShow);`
- L105 _public prototype_ `virtual ~FLandscapeBrushDragDropOp() = default;`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_MiscTools.h` (Private)


#### class `FLandscapeEditorDetailCustomization_MiscTools`  
`class FLandscapeEditorDetailCustomization_MiscTools : public FLandscapeEditorDetailCustomization_Base`  
_L22-77_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L36 _protected prototype_ `static EVisibility GetClearComponentSelectionVisibility();` — Component Selection Tool
- L37 _protected prototype_ `static FReply OnClearComponentSelectionButtonClicked();`
- L40 _protected prototype_ `static EVisibility GetClearRegionSelectionVisibility();` — Mask Tool
- L41 _protected prototype_ `static FReply OnClearRegionSelectionButtonClicked();`
- L44 _protected prototype_ `static FReply OnSelectAllControlPointsButtonClicked();` — Splines Tool
- L45 _protected prototype_ `static FReply OnSelectAllSegmentsButtonClicked();`
- L46 _protected prototype_ `void OnbUseAutoRotateControlPointChanged(ECheckBoxState NewState);`
- L47 _protected prototype_ `ECheckBoxState GetbUseAutoRotateControlPoint() const;`
- L48 _protected prototype_ `void OnbAlwaysRotateForwardChanged(ECheckBoxState NewState);`
- L49 _protected prototype_ `ECheckBoxState GetbAlwaysRotateForward() const;`
- L52 _protected prototype_ `static FReply OnApplyRampButtonClicked();` — Ramp Tool
- L53 _protected prototype_ `static bool GetApplyRampButtonIsEnabled();`
- L54 _protected prototype_ `static FReply OnResetRampButtonClicked();`
- L57 _protected prototype_ `static FReply OnApplyMirrorButtonClicked();` — Mirror Tool
- L58 _protected prototype_ `static FReply OnResetMirrorPointButtonClicked();`
- L61 _protected prototype_ `void HandleFlattenValueChanged(float NewValue);` — Flatten Tool
- L62 _protected prototype_ `void OnBeginFlattenToolEyeDrop();`
- L63 _protected prototype_ `void OnCompletedFlattenToolEyeDrop(bool Canceled);`
- L64 _protected prototype_ `TOptional<float> GetFlattenValue() const;`
- L65 _protected prototype_ `TOptional<float> GetFlattenTargetValueMin() const;`
- L66 _protected prototype_ `float GetFlattenTargetValueMid() const;`
- L67 _protected prototype_ `TOptional<float> GetFlattenTargetValueMax() const;`
- L68 _protected prototype_ `TOptional<float> GetFlattenTerraceIntervalValueMax() const;`
- L71 _protected prototype_ `EVisibility GetMiscLandscapeErrorVisibility() const;` — Common Error handling
- L72 _protected prototype_ `FText GetMiscLandscapeErrorText() const;`
- L75 _protected prototype_ `static bool IsResetGizmoButtonShown(TSharedPtr<IPropertyHandle> InProperty = nullptr);` — Current Gizmo customization (Import, Copy tools)
- L76 _protected prototype_ `static void ResetGizmoToOrigin(TSharedPtr<IPropertyHandle> InProperty = nullptr);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace LandscapeTestUtils`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_NewLandscape.h` (Private)


#### class `FLandscapeEditorArrayBuilder_NewTargetLayer`  
`class FLandscapeEditorArrayBuilder_NewTargetLayer : public FDetailArrayBuilder`  
_L27-41_
- inherits: `FDetailArrayBuilder`
- L30 _public function_ `FLandscapeEditorArrayBuilder_NewTargetLayer(TSharedRef<IPropertyHandle> InBaseProperty) : FDetailArrayBuilder(InBaseProperty)`
- L35 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L38 _private prototype_ `static FReply ShowAutoFillTargetLayerDialog();`
- L39 _private prototype_ `static FReply HandleAutoFillTargetLayers(const bool bCreateAssetForEmptyLayers);`
- L40 _private prototype_ `static bool HasWeightmapTargetLayers();`

#### class `FLandscapeEditorDetailCustomization_NewLandscape`  
`class FLandscapeEditorDetailCustomization_NewLandscape : public FLandscapeEditorDetailCustomization_Base`  
_L43-128_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L46 _public function_ `FLandscapeEditorDetailCustomization_NewLandscape() : bUsingSlider(false)`
- L51 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L54 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L57 _public prototype_ `static void SetScale(FVector::FReal NewValue, ETextCommit::Type, TSharedRef<IPropertyHandle> PropertyHandle);`
- L59 _public prototype_ `static TSharedRef<SWidget> GetSectionSizeMenu(TSharedRef<IPropertyHandle> PropertyHandle);`
- L60 _public prototype_ `static void OnChangeSectionSize(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize);`
- L61 _public prototype_ `static FText GetSectionSize(TSharedRef<IPropertyHandle> PropertyHandle);`
- L63 _public prototype_ `static TSharedRef<SWidget> GetSectionsPerComponentMenu(TSharedRef<IPropertyHandle> PropertyHandle);`
- L64 _public prototype_ `static void OnChangeSectionsPerComponent(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize);`
- L65 _public prototype_ `static FText GetSectionsPerComponent(TSharedRef<IPropertyHandle> PropertyHandle);`
- L67 _public prototype_ `TOptional<int32> GetLandscapeResolutionX() const;`
- L68 _public prototype_ `void OnChangeLandscapeResolutionX(int32 NewValue, bool bCommit);`
- L70 _public prototype_ `TOptional<int32> GetLandscapeResolutionY() const;`
- L71 _public prototype_ `void OnChangeLandscapeResolutionY(int32 NewValue, bool bCommit);`
- L73 _public prototype_ `TOptional<int32> GetMinLandscapeResolution() const;`
- L74 _public prototype_ `TOptional<int32> GetMaxLandscapeResolution() const;`
- L76 _public prototype_ `FText GetTotalComponentCount() const;`
- L78 _public prototype_ `bool IsCreateButtonEnabled() const;`
- L79 _public prototype_ `EVisibility GetNewLandscapeErrorVisibility() const;`
- L80 _public prototype_ `FText GetNewLandscapeErrorText() const;`
- L82 _public prototype_ `FReply OnCreateButtonClicked();`
- L83 _public prototype_ `FReply OnFillWorldButtonClicked();`
- L85 _public prototype_ `static EVisibility GetVisibilityOnlyInNewLandscapeMode(ENewLandscapePreviewMode value);`
- L88 _public prototype_ `void GenerateLayersArrayElementWidget(TSharedRef<IPropertyHandle> InPropertyHandle, int32 InArrayIndex, IDetailChildrenBuilder& InChildrenBuilder);` — Called to generate ImportLayer children
- L89 _public prototype_ `EVisibility GetLayerVisibility(TSharedRef<IPropertyHandle> InPropertyHandle) const;`
- L92 _public prototype_ `static EVisibility GetHeightmapErrorVisibility(TSharedRef<IPropertyHandle> PropertyHandle_HeightmapImportResult);` — Import
- L93 _public prototype_ `static FSlateColor GetHeightmapErrorColor(TSharedRef<IPropertyHandle> PropertyHandle_HeightmapImportResult);`
- L94 _public prototype_ `static void SetImportHeightmapFilenameString(const FText& NewValue, ETextCommit::Type CommitInfo, TSharedRef<IPropertyHandle> PropertyHandle_HeightmapFilename);`
- L95 _public prototype_ `void OnImportHeightmapFilenameChanged();`
- L96 _public prototype_ `static FReply OnImportHeightmapFilenameButtonClicked(TSharedRef<IPropertyHandle> PropertyHandle_HeightmapFilename);`
- L98 _public prototype_ `TSharedRef<SWidget> GetImportLandscapeResolutionMenu();`
- L99 _public prototype_ `void OnChangeImportLandscapeResolution(int32 NewConfigIndex);`
- L100 _public prototype_ `FText GetImportLandscapeResolution() const;`
- L102 _public prototype_ `bool GetImportButtonIsEnabled() const;`
- L103 _public prototype_ `FReply OnFitImportDataButtonClicked();`
- L105 _public prototype_ `FText GetOverallResolutionTooltip() const;`
- L108 _public prototype_ `EVisibility GetMaterialTipVisibility() const;` — Import layers
- L110 _public prototype_ `void ResetMaterialToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L111 _public prototype_ `bool ShouldShowResetMaterialToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L113 _public prototype_ `void ResetLocationToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L114 _public prototype_ `bool ShouldShowResetLocationlToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L116 _public prototype_ `void ResetRotationToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L117 _public prototype_ `bool ShouldShowResetRotationToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L119 _public prototype_ `void ResetScaleToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L120 _public prototype_ `bool ShouldShowResetScaleToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);`
- L124 _protected member_ `bool bUsingSlider;`
- L127 _private prototype_ `static void AddComponents(ULandscapeInfo* InLandscapeInfo, ULandscapeSubsystem* InLandscapeSubsystem, const TArray<FIntPoint>& InComponentCoordinates, TArray<ALandscapeProxy*>& OutCreatedStreamingProxies);`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_ResizeLandscape.h` (Private)


#### class `FLandscapeEditorDetailCustomization_ResizeLandscape`  
`class FLandscapeEditorDetailCustomization_ResizeLandscape : public FLandscapeEditorDetailCustomization_Base`  
_L18-56_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L28 _public prototype_ `static FText GetOriginalSectionSize();`
- L29 _public prototype_ `static TSharedRef<SWidget> GetSectionSizeMenu(TSharedRef<IPropertyHandle> PropertyHandle);`
- L30 _public prototype_ `static void OnChangeSectionSize(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize);`
- L31 _public prototype_ `static FText GetSectionSize(TSharedRef<IPropertyHandle> PropertyHandle);`
- L32 _public prototype_ `static bool IsSectionSizeResetToDefaultVisible(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L33 _public prototype_ `static void OnSectionSizeResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L35 _public prototype_ `static FText GetOriginalSectionsPerComponent();`
- L36 _public prototype_ `static TSharedRef<SWidget> GetSectionsPerComponentMenu(TSharedRef<IPropertyHandle> PropertyHandle);`
- L37 _public prototype_ `static void OnChangeSectionsPerComponent(TSharedRef<IPropertyHandle> PropertyHandle, int32 NewSize);`
- L38 _public prototype_ `static FText GetSectionsPerComponent(TSharedRef<IPropertyHandle> PropertyHandle);`
- L39 _public prototype_ `static bool IsSectionsPerComponentResetToDefaultVisible(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L40 _public prototype_ `static void OnSectionsPerComponentResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L42 _public prototype_ `static FText GetOriginalComponentCount();`
- L43 _public prototype_ `static FText GetComponentCount(TSharedRef<IPropertyHandle> PropertyHandle_ComponentCount_X, TSharedRef<IPropertyHandle> PropertyHandle_ComponentCount_Y);`
- L45 _public prototype_ `static FText GetOriginalLandscapeResolution();`
- L46 _public prototype_ `static FText GetLandscapeResolution();`
- L48 _public prototype_ `static FText GetOriginalTotalComponentCount();`
- L49 _public prototype_ `static FText GetTotalComponentCount();`
- L51 _public prototype_ `FReply OnApplyButtonClicked();`
- L54 _protected member_ `static const int32 SectionSizes[];`
- L55 _protected member_ `static const int32 NumSections[];`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomization_TargetLayers.h` (Private)


#### class `FLandscapeEditorStructCustomization_FTargetLayerAssetPath`  
`class FLandscapeEditorStructCustomization_FTargetLayerAssetPath : public FLandscapeEditorStructCustomization_Base`  
_L30-45_
- inherits: `FLandscapeEditorStructCustomization_Base`
- L33 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L35 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L36 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L39 _private prototype_ `static FText GetTargetLayerAssetFilePath();`
- L40 _private prototype_ `static FReply OnSetTargetLayerAssetFilePath();`
- L42 _private prototype_ `static bool IsUseTargetLayerAssetPathEnabled();`
- L43 _private prototype_ `static ECheckBoxState GetUseTargetLayerAssetPathCheckState();`
- L44 _private prototype_ `static void OnUseTargetLayerAssetPathCheckStateChanged(ECheckBoxState NewCheckedState);`

#### class `FLandscapeEditorDetailCustomization_TargetLayers`  
`class FLandscapeEditorDetailCustomization_TargetLayers : public FLandscapeEditorDetailCustomization_Base`  
_L47-64_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L51 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L54 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L57 _protected prototype_ `static bool ShouldShowTargetLayers();`
- L58 _protected prototype_ `static EVisibility GetPaintingRestrictionVisibility();`
- L59 _protected prototype_ `static EVisibility GetWeightBlendedTargetLayerPaintModeVisibility();`
- L60 _protected prototype_ `static EVisibility GetVisibilityMaskTipVisibility();`
- L61 _protected prototype_ `static EVisibility GetPopulateTargetLayersInfoTipVisibility();`
- L62 _protected prototype_ `static EVisibility GetTargetLayersInvalidInfoAssetTipVisibility();`
- L63 _protected prototype_ `static EVisibility GetFilteredTargetLayersListInfoTipVisibility();`

#### class `FLandscapeEditorCustomNodeBuilder_TargetLayers`  
`class FLandscapeEditorCustomNodeBuilder_TargetLayers : public IDetailCustomNodeBuilder, public TSharedFromThis<FLandscapeEditorCustomNodeBuilder_TargetLayers>`  
_L66-172_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FLandscapeEditorCustomNodeBuilder_TargetLayers>`
- L69 _public prototype_ `FLandscapeEditorCustomNodeBuilder_TargetLayers(TSharedRef<FAssetThumbnailPool> ThumbnailPool, TSharedRef<IPropertyHandle> InTargetDisplayOrderPropertyHandle, TSharedRef<IPropertyHandle> InTargetDisplayOrderIsAscendingPropertyHandle, TSharedRef<IPropertyHandle> InTargetShowUnusedLayersPropertyHandle);`
- L71 _public prototype_ `~FLandscapeEditorCustomNodeBuilder_TargetLayers();`
- L73 _public prototype_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override;`
- L74 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L75 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L76 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L77 _public function_ `virtual bool RequiresTick() const override`
- L78 _public function_ `virtual bool InitiallyCollapsed() const override`
- L79 _public function_ `virtual FName GetName() const override`
- L81 _public prototype_ `static TArray<TSharedRef<FLandscapeTargetListInfo>> PrepareTargetLayerList(bool bInSort, bool bInFilter);`
- L84 _protected member_ `TSharedRef<FAssetThumbnailPool> ThumbnailPool;`
- L85 _protected member_ `TSharedRef<IPropertyHandle> TargetDisplayOrderPropertyHandle;`
- L86 _protected member_ `TSharedRef<IPropertyHandle> TargetDisplayOrderIsAscendingPropertyHandle;`
- L87 _protected member_ `TSharedRef<IPropertyHandle> TargetShowUnusedLayersPropertyHandle;`
- L88 _protected member_ `TSharedPtr<SSearchBox> LayersFilterSearchBox;`
- L90 _protected member_ `TArray<TSharedPtr<SInlineEditableTextBlock>> InlineTextBlocks;` — Widgets for displaying and editing the target layer name
- L92 _protected prototype_ `static class FEdModeLandscape* GetEditorMode();`
- L94 _protected prototype_ `TSharedPtr<SWidget> GenerateRow(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L96 _protected prototype_ `static ELandscapeTargetLayerActionType GetTargetLayerActionType(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L97 _protected prototype_ `static const FSlateBrush* GetTargetLayerActionTypeBrush(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L98 _protected prototype_ `static FLinearColor GetTargetLayerBlendGroupStripColor(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L99 _protected prototype_ `static EVisibility GetTargetLayerBlendGroupStripVisibility(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L100 _protected prototype_ `static bool GetTargetLayerIsSelected(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L101 _protected prototype_ `static void OnTargetSelectionChanged(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L102 _protected prototype_ `TSharedPtr<SWidget> OnTargetLayerContextMenuOpening(const TSharedRef<FLandscapeTargetListInfo> Target, const int32 InLayerIndex);`
- L103 _protected prototype_ `void OnRenameLayer(const int32 InLayerIndex);`
- L104 _protected prototype_ `static void OnExportLayer(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L105 _protected prototype_ `static void OnImportLayer(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L106 _protected prototype_ `static void OnReimportLayer(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L107 _protected prototype_ `static void OnHeightmapLayerContextMenu(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L108 _protected prototype_ `static void OnFillLayer(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L109 _protected prototype_ `static void OnClearLayer(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L110 _protected prototype_ `static bool CanClearLayer(const TSharedRef<FLandscapeTargetListInfo> Target, FText& OutToolTip);`
- L111 _protected prototype_ `static void OnRebuildMICs(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L112 _protected prototype_ `static bool ShouldFilterLayerInfo(const struct FAssetData& AssetData, FName LayerName);`
- L113 _protected prototype_ `static void OnTargetLayerSetObject(const FAssetData& AssetData, const TSharedRef<FLandscapeTargetListInfo> Target);`
- L114 _protected prototype_ `static EVisibility GetTargetLayerInfoSelectorVisibility(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L115 _protected prototype_ `static bool GetTargetLayerCreateEnabled(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L116 _protected prototype_ `static void OnTargetLayerCreateClicked(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L117 _protected prototype_ `static void CreateTargetLayerInfoAsset(const TSharedRef<FLandscapeTargetListInfo> Target, const FString& PackageName, const FString& FileName);`
- L118 _protected prototype_ `static void OnTargetLayerDeleteClicked(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L119 _protected prototype_ `static FSlateColor GetLayerUsageDebugColor(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L120 _protected prototype_ `static EVisibility GetDebugModeLayerUsageVisibility(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L121 _protected prototype_ `static EVisibility GetDebugModeLayerUsageVisibility_Invert(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L122 _protected prototype_ `static EVisibility GetDebugModeColorChannelVisibility(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L123 _protected prototype_ `static ECheckBoxState DebugModeColorChannelIsChecked(const TSharedRef<FLandscapeTargetListInfo> Target, int32 Channel);`
- L124 _protected prototype_ `static void OnDebugModeColorChannelChanged(ECheckBoxState NewCheckedState, const TSharedRef<FLandscapeTargetListInfo> Target, int32 Channel);`
- L125 _protected prototype_ `static FText GetTargetBlendMethodText(const TSharedRef<FLandscapeTargetListInfo> InTarget, bool bInIncludeBlendGroup);`
- L126 _protected prototype_ `static FText GetTargetBlendGroupText(const TSharedRef<FLandscapeTargetListInfo> InTarget, bool bInAllowNoName);`
- L127 _protected prototype_ `static FText GetTargetBlendMethodTooltipText(const TSharedRef<FLandscapeTargetListInfo> InTarget);`
- L128 _protected prototype_ `static FSlateColor GetTargetTextColor(const TSharedRef<FLandscapeTargetListInfo> InTarget);`
- L130 _protected prototype_ `static EVisibility GetLayersSubstractiveBlendVisibility(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L131 _protected prototype_ `static ECheckBoxState IsLayersSubstractiveBlendChecked(const TSharedRef<FLandscapeTargetListInfo> Target);`
- L132 _protected prototype_ `static void OnLayersSubstractiveBlendChanged(ECheckBoxState NewCheckedState, const TSharedRef<FLandscapeTargetListInfo> Target);`
- L135 _protected prototype_ `FReply HandleDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, int32 SlotIndex, SVerticalBox::FSlot* Slot);` — Drag/Drop handling
- L136 _protected prototype_ `TOptional<SDragAndDropVerticalBox::EItemDropZone> HandleCanAcceptDrop(const FDragDropEvent& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L137 _protected prototype_ `FReply HandleAcceptDrop(FDragDropEvent const& DragDropEvent, SDragAndDropVerticalBox::EItemDropZone DropZone, int32 SlotIndex, SVerticalBox::FSlot* Slot);`
- L140 _protected prototype_ `const TArray<const TSharedRef<FLandscapeTargetListInfo>> GetUnassignedTargetLayersFromMaterial() const;` — Create Layers From Materials
- L141 _protected prototype_ `bool HasUnassignedTargetLayers() const;`
- L142 _protected prototype_ `FReply HandleCreateLayersFromMaterials() const;`
- L145 _protected prototype_ `FReply ShowAutoFillTargetLayerDialog() const;` — Auto-Fill Target layers
- L146 _protected prototype_ `FReply HandleAutoFillTargetLayers(const bool bUpdateAllLayers, const bool bCreateTargetLayers) const;`
- L148 _protected prototype_ `void HandleCreateLayer();`
- L149 _protected prototype_ `const FSlateBrush* GetTargetLayerDisplayOrderBrush() const;`
- L150 _protected prototype_ `TSharedRef<SWidget> GetTargetLayerDisplayOrderButtonMenuContent();`
- L151 _protected prototype_ `void SetSelectedDisplayOrder(ELandscapeLayerDisplayMode InDisplayOrder);`
- L152 _protected prototype_ `void SetAscendingDisplayOrder(bool bInIsAscending);`
- L153 _protected prototype_ `bool IsSelectedDisplayOrder(ELandscapeLayerDisplayMode InDisplayOrder) const;`
- L154 _protected prototype_ `bool IsAscendingDisplayOrder() const;`
- L155 _protected prototype_ `bool IsDescendingDisplayOrder() const;`
- L156 _protected prototype_ `bool CanChangeDisplayOrderSortType() const;`
- L158 _protected prototype_ `TSharedRef<SWidget> GetTargetLayerShowUnusedButtonMenuContent();`
- L159 _protected prototype_ `const FSlateBrush* GetShowUnusedBrush() const;`
- L160 _protected prototype_ `void ShowUnusedLayers(bool Result);`
- L161 _protected prototype_ `bool ShouldShowUnusedLayers(bool Result) const;`
- L162 _protected prototype_ `EVisibility ShouldShowLayer(TSharedRef<FLandscapeTargetListInfo> Target) const;`
- L164 _protected prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L165 _protected prototype_ `void OnFilterTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L166 _protected prototype_ `int32 GetWeightmapTargetLayerCount() const;`
- L167 _protected prototype_ `bool HasWeightmapTargetLayers() const;`
- L168 _protected prototype_ `EVisibility GetLayersFilterVisibility() const;`
- L169 _protected prototype_ `EVisibility GetLayersDisplayOptionsVisibility() const;`
- L170 _protected prototype_ `FText GetLayersFilterText() const;`
- L171 _protected prototype_ `FText GetNumWeightmapTargetLayersText() const;`

#### class `SLandscapeEditorSelectableBorder`  
`class SLandscapeEditorSelectableBorder : public SBorder`  
_L174-206_
- inherits: `SBorder`
- L177 _public function_ `SLATE_BEGIN_ARGS(SLandscapeEditorSelectableBorder) : _Content() , _HAlign(HAlign_Fill) , _VAlign(VAlign_Fill) , _Padding(FMargin(2.0f))`
- L183 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(EHorizontalAlignment, HAlign) SLATE_ARGUMENT(EVerticalAlignment, VAlign) SLATE_ATTRIBUTE(FMargin, Padding) SLATE_EVENT(FOnContextMenuOpening, OnContextMenuOpening) SLATE_EVENT(FSimpleDelegate, OnSelected) SLATE_EVENT(FSimpleDelegate, OnDoubleClick) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L197 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L198 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L199 _public prototype_ `const FSlateBrush* GetBorder() const;`
- L202 _protected member_ `FOnContextMenuOpening OnContextMenuOpening;`
- L203 _protected member_ `FSimpleDelegate OnSelected;`
- L204 _protected member_ `TAttribute<bool> IsSelected;`
- L205 _protected member_ `FSimpleDelegate OnDoubleClick;`

#### class `FTargetLayerDragDropOp`  
`class FTargetLayerDragDropOp : public FDragAndDropVerticalBoxOp`  
_L208-221_
- inherits: `FDragAndDropVerticalBoxOp`
- L211 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FTargetLayerDragDropOp, FDragAndDropVerticalBoxOp) TSharedPtr<SWidget> WidgetToShow;`
- L215 _public prototype_ `static TSharedRef<FTargetLayerDragDropOp> New(int32 InSlotIndexBeingDragged, SVerticalBox::FSlot* InSlotBeingDragged, TSharedPtr<SWidget> InWidgetToShow);`
- L218 _public prototype_ `virtual ~FTargetLayerDragDropOp();`
- L220 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetailCustomizations.h` (Private)
_(no declarations extracted)_

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorDetails.h` (Private)


#### class `FLandscapeEditorDetails`  
`class FLandscapeEditorDetails : public FLandscapeEditorDetailCustomization_Base`  
_L39-77_
- inherits: `FLandscapeEditorDetailCustomization_Base`
- L43 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L46 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L49 _protected prototype_ `static EVisibility GetTargetLandscapeSelectorVisibility();`
- L50 _protected prototype_ `static FText GetLandscapeDisplayName(ALandscape* InLandscape);`
- L51 _protected prototype_ `static FText GetTargetLandscapeName();`
- L52 _protected prototype_ `static TSharedRef<SWidget> GetTargetLandscapeMenu();`
- L53 _protected prototype_ `static void OnChangeTargetLandscape(TWeakObjectPtr<ULandscapeInfo> LandscapeInfo);`
- L55 _protected prototype_ `FName GetCurrentBrushFName() const;`
- L56 _protected prototype_ `bool GetBrushSelectorIsVisible() const;`
- L57 _protected prototype_ `EVisibility GetBrushSelectorVisibility() const;`
- L59 _protected prototype_ `FName GetCurrentBrushFalloffFName() const;`
- L60 _protected prototype_ `bool GetBrushFalloffSelectorIsVisible() const;`
- L61 _protected prototype_ `EVisibility GetBrushFalloffSelectorVisibility() const;`
- L63 _protected prototype_ `void SetBrushCommand(FName);`
- L65 _protected prototype_ `bool IsBrushSetEnabled() const;`
- L67 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_NewLandscape> Customization_NewLandscape;`
- L68 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_ResizeLandscape> Customization_ResizeLandscape;`
- L69 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_ImportExport> Customization_ImportExport;`
- L70 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_CopyPaste> Customization_CopyPaste;`
- L71 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_MiscTools> Customization_MiscTools;`
- L72 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_AlphaBrush> Customization_AlphaBrush;`
- L73 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_Blueprint> Customization_Blueprint;`
- L74 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_TargetLayers> Customization_TargetLayers;`
- L75 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_EditLayersStack> Customization_EditLayersStack;`
- L76 _protected member_ `TSharedPtr<FLandscapeEditorDetailCustomization_LayersBrushStack> Customization_LayersBrushStack;`

### `Source/Editor/LandscapeEditor/Private/LandscapeEditorPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapeTools, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapeTools, Log, All);`

### `Source/Editor/LandscapeEditor/Private/LandscapeFileFormatPng.h` (Private)


#### class `FLandscapeHeightmapFileFormat_Png`  
`class FLandscapeHeightmapFileFormat_Png : public ILandscapeHeightmapFileFormat`  
_L11-27_
- inherits: `ILandscapeHeightmapFileFormat`
- desc: Implement .png file format
- L14 _private member_ `FLandscapeFileTypeInfo FileTypeInfo;`
- L17 _public prototype_ `FLandscapeHeightmapFileFormat_Png();`
- L19 _public function_ `virtual const FLandscapeFileTypeInfo& GetInfo() const override`
- L24 _public prototype_ `virtual FLandscapeFileInfo Validate(const TCHAR* HeightmapFilename, FName LayerName) const override;`
- L25 _public prototype_ `virtual FLandscapeImportData<uint16> Import(const TCHAR* HeightmapFilename, FName LayerName, FLandscapeFileResolution ExpectedResolution) const override;`
- L26 _public prototype_ `virtual void Export(const TCHAR* HeightmapFilename, FName LayerName, TArrayView<const uint16> Data, FLandscapeFileResolution DataResolution, FVector Scale) const override;`

#### class `FLandscapeWeightmapFileFormat_Png`  
`class FLandscapeWeightmapFileFormat_Png : public ILandscapeWeightmapFileFormat`  
_L31-47_
- inherits: `ILandscapeWeightmapFileFormat`
- L34 _private member_ `FLandscapeFileTypeInfo FileTypeInfo;`
- L37 _public prototype_ `FLandscapeWeightmapFileFormat_Png();`
- L39 _public function_ `virtual const FLandscapeFileTypeInfo& GetInfo() const override`
- L44 _public prototype_ `virtual FLandscapeFileInfo Validate(const TCHAR* WeightmapFilename, FName LayerName) const override;`
- L45 _public prototype_ `virtual FLandscapeImportData<uint8> Import(const TCHAR* WeightmapFilename, FName LayerName, FLandscapeFileResolution ExpectedResolution) const override;`
- L46 _public prototype_ `virtual void Export(const TCHAR* WeightmapFilename, FName LayerName, TArrayView<const uint8> Data, FLandscapeFileResolution DataResolution, FVector Scale) const override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeFileFormatRaw.h` (Private)


#### class `FLandscapeHeightmapFileFormat_Raw`  
`class FLandscapeHeightmapFileFormat_Raw : public ILandscapeHeightmapFileFormat`  
_L11-27_
- inherits: `ILandscapeHeightmapFileFormat`
- desc: Implement .raw file format
- L14 _private member_ `FLandscapeFileTypeInfo FileTypeInfo;`
- L17 _public prototype_ `FLandscapeHeightmapFileFormat_Raw();`
- L19 _public function_ `virtual const FLandscapeFileTypeInfo& GetInfo() const override`
- L24 _public prototype_ `virtual FLandscapeFileInfo Validate(const TCHAR* HeightmapFilename, FName LayerName) const override;`
- L25 _public prototype_ `virtual FLandscapeImportData<uint16> Import(const TCHAR* HeightmapFilename, FName LayerName, FLandscapeFileResolution ExpectedResolution) const override;`
- L26 _public prototype_ `virtual void Export(const TCHAR* HeightmapFilename, FName LayerName, TArrayView<const uint16> Data, FLandscapeFileResolution DataResolution, FVector Scale) const override;`

#### class `FLandscapeWeightmapFileFormat_Raw`  
`class FLandscapeWeightmapFileFormat_Raw : public ILandscapeWeightmapFileFormat`  
_L31-47_
- inherits: `ILandscapeWeightmapFileFormat`
- L34 _private member_ `FLandscapeFileTypeInfo FileTypeInfo;`
- L37 _public prototype_ `FLandscapeWeightmapFileFormat_Raw();`
- L39 _public function_ `virtual const FLandscapeFileTypeInfo& GetInfo() const override`
- L44 _public prototype_ `virtual FLandscapeFileInfo Validate(const TCHAR* WeightmapFilename, FName LayerName) const override;`
- L45 _public prototype_ `virtual FLandscapeImportData<uint8> Import(const TCHAR* WeightmapFilename, FName LayerName, FLandscapeFileResolution ExpectedResolution) const override;`
- L46 _public prototype_ `virtual void Export(const TCHAR* WeightmapFilename, FName Layername, TArrayView<const uint8> Data, FLandscapeFileResolution DataResolution, FVector Scale) const override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeGrassTypeDetails.h` (Private)


#### class `FLandscapeGrassTypeDetails`  
`class FLandscapeGrassTypeDetails : public IDetailCustomization`  
_L21-31_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `virtual ~FLandscapeGrassTypeDetails();`
- L30 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

#### class `FLandscapeGrassNameCustomization`  
`class FLandscapeGrassNameCustomization : public IPropertyTypeCustomization`  
_L36-51_
- inherits: `IPropertyTypeCustomization`
- L40 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L43 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L46 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden to do nothing
- L50 _private member_ `TArray<FName> ComboBoxOptions;`

### `Source/Editor/LandscapeEditor/Private/LandscapeImageFileCache.h` (Private)


#### struct `FLandscapeImageDataRef`  
`struct FLandscapeImageDataRef`  
_L21-28_
- L23 _public member_ `TSharedPtr<TArray<uint8>> Data;`
- L24 _public member_ `FIntPoint Resolution;`
- L25 _public member_ `ELandscapeImportResult Result;`
- L26 _public member_ `FText ErrorMessage;`
- L27 _public member_ `int32 BytesPerPixel;`

#### class `FLandscapeImageFileCache`  
`class FLandscapeImageFileCache`  
_L30-92_
- L33 _public prototype_ `FLandscapeImageFileCache();`
- L34 _public prototype_ `~FLandscapeImageFileCache();`
- L37 _public prototype_ `template<typename T> FLandscapeFileInfo FindImage(const TCHAR* InImageFilename, FLandscapeImageDataRef& OutImageData);`
- L39 _public prototype_ `void SetMaxSize(uint64 InNewMaxSize);`
- L41 _public prototype_ `void Clear();`
- L60 _private prototype_ `void OnLandscapeSettingsChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L62 _private prototype_ `bool MonitorFile(const FString& InFullyQualifiedFileName);`
- L63 _private prototype_ `void UnmonitorFile(const FString& InFullyQualifiedFileName);`
- L65 _private prototype_ `void MonitorCallback(const TArray<struct FFileChangeData>& Changes);`
- L67 _private typedef_ `using CacheType = TMap<FString, FCacheEntry>;`
- L70 _private prototype_ `template<typename T> CacheType& ChooseCache();`
- L79 _private member_ `TStaticArray<CacheType, 2> CachedImages;`
- L81 _private member_ `TMap<FString, FDirectoryMonitor> MonitoredDirs;`
- L84 _private prototype_ `template <typename T> void Add(const FString& InFullyQualifiedFileName, FLandscapeImageDataRef NewImageData);`
- L85 _private prototype_ `void Remove(const FString& InFullyQualifiedFileName);`
- L87 _private prototype_ `void Trim();`
- L89 _private member_ `uint64 MaxCacheSize = 32 * 1024 * 1024;`
- L90 _private member_ `uint64 CacheSize = 0;`
- L91 _private member_ `FDelegateHandle SettingsChangedHandle;`

#### struct `FLandscapeImageFileCache::FCacheEntry`  
`struct FCacheEntry`  
_L45-51_
- L47 _public function_ `FCacheEntry(FLandscapeImageDataRef ImageData) : ImageData(ImageData)`
- L49 _public member_ `uint32 UsageCount = 1;`
- L50 _public member_ `FLandscapeImageDataRef ImageData;`

#### struct `FLandscapeImageFileCache::FDirectoryMonitor`  
`struct FDirectoryMonitor`  
_L53-58_
- L55 _public function_ `FDirectoryMonitor(FDelegateHandle Handle)`
- L56 _public member_ `int32 NumFiles = 1;`
- L57 _public member_ `FDelegateHandle MonitorHandle;`

#### enum `FLandscapeImageFileCache::(anonymous)`  
``  
_L75-78_

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "LandscapeEditor"`
- L76 _enumerator_ `Cache8 = 0` (scope `FLandscapeImageFileCache::__anon4959e7cf0103`)
- L77 _enumerator_ `Cache16 = 1` (scope `FLandscapeImageFileCache::__anon4959e7cf0103`)

### `Source/Editor/LandscapeEditor/Private/LandscapeProxyUIDetails.h` (Private)


#### class `FLandscapeProxyUIDetails`  
`class FLandscapeProxyUIDetails : public IDetailCustomization`  
_L14-44_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L26 _private prototype_ `FLandscapeProxyUIDetails();` — Use MakeInstance to create an instance of this class
- L29 _private prototype_ `bool IsCreateRuntimeVirtualTextureVolumeEnabled(ALandscape* InLandscapeActor) const;` — Returns true if SetBounds button is enabled
- L32 _private prototype_ `ECheckBoxState IsOverriddenPropertyChecked(TArray<TWeakObjectPtr<ALandscapeStreamingProxy>> InEditingStreamingProxies, FName InPropertyName) const;` — Callbacks for the override property checkbox
- L33 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InNewState, TArray<TWeakObjectPtr<ALandscapeStreamingProxy>> InEditingStreamingProxies, FName InPropertyName);`
- L36 _private prototype_ `FReply CreateRuntimeVirtualTextureVolume(ALandscape* InLandscapeActor);` — Callback for Set Bounds button
- L38 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;`
- L41 _private member_ `TArray<TSharedPtr<FString>> PositionPrecisionOptions;` — Nanite Position Precision Options
- L42 _private member_ `static constexpr int MinNanitePrecision = -6;`
- L43 _private member_ `static constexpr int MaxNanitePrecision = 13;`

### `Source/Editor/LandscapeEditor/Private/LandscapeRegionUtils.h` (Private)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace LandscapeRegionUtils`
- L20 _prototype_ `ALocationVolume* CreateLandscapeRegionVolume(UWorld* World, ALandscapeProxy* ParentLandscapeActor, const FIntPoint& RegionCoordinate, double RegionSize);` (scope `LandscapeRegionUtils`) — Create a LocationVolume for a Region located at RegionCoordinate with a Box shape of dimension RegionSize
- L23 _prototype_ `void ForEachComponentByRegion(int32 RegionSize, const TArray<FIntPoint>& ComponentCoordinates, TFunctionRef<bool(const FIntPoint&, const TArray<FIntPoint>&)> RegionFn);` (scope `LandscapeRegionUtils`) — Iterate over all Components grouping by Region
- L26 _prototype_ `void ForEachRegion_LoadProcessUnload(ULandscapeInfo* LandscapeInfo, UWorld* World, TFunctionRef<bool(const FBox&, const TArray<ALandscapeProxy*>)> RegionFn);` (scope `LandscapeRegionUtils`) — Load, Process (call RegionFn) and Unload the Region
- L29 _prototype_ `int32 NumLandscapeRegions(ULandscapeInfo* InLandscapeInfo);` (scope `LandscapeRegionUtils`) — Number of landscape regions in this landscape.

### `Source/Editor/LandscapeEditor/Private/LandscapeSplineDetails.h` (Private)


#### class `FLandscapeSplineDetails`  
`class FLandscapeSplineDetails : public IDetailCustomization`  
_L13-42_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L23 _private prototype_ `FEdModeLandscape* GetEditorMode() const;`
- L24 _private prototype_ `FText OnGetSplineOwningLandscapeText() const;`
- L25 _private prototype_ `FReply OnMoveToCurrentLevelButtonClicked();`
- L26 _private prototype_ `bool IsMoveToCurrentLevelButtonEnabled() const;`
- L27 _private prototype_ `bool IsSegmentSelectModeEnabled() const;`
- L29 _private prototype_ `FReply OnUpdateSplineMeshLevelsButtonClicked();`
- L30 _private prototype_ `bool IsUpdateSplineMeshLevelsButtonEnabled() const;`
- L32 _private prototype_ `FReply OnFlipSegmentButtonClicked();`
- L33 _private prototype_ `bool IsFlipSegmentButtonEnabled() const;`
- L35 _private prototype_ `bool HasAdjacentLinearSplineElement(ESplineNavigationFlags Flags) const;`
- L36 _private prototype_ `bool HasEndLinearSplineElement(ESplineNavigationFlags Flags) const;`
- L37 _private prototype_ `FReply OnSelectAdjacentLinearSplineElementButtonClicked(ESplineNavigationFlags Flags) const;`
- L38 _private prototype_ `FReply OnSelectEndLinearSplineElementButtonClicked(ESplineNavigationFlags Flags) const;`
- L40 _private prototype_ `FReply OnSelectAllConnectedSplineElementsButtonClicked() const;`
- L41 _private prototype_ `FReply OnToggleSplineSelectionTypeButtonClicked() const;`

### `Source/Editor/LandscapeEditor/Private/LandscapeSplineImportExport.h` (Private)


#### class `FLandscapeSplineTextObjectFactory`  
`class FLandscapeSplineTextObjectFactory : protected FCustomizableTextObjectFactory`  
_L8-27_
- inherits: `FCustomizableTextObjectFactory`
- L11 _public prototype_ `FLandscapeSplineTextObjectFactory(FFeedbackContext* InWarningContext = GWarn);`
- L13 _public prototype_ `TArray<UObject*> ImportSplines(UObject* InParent, const TCHAR* TextBuffer);`
- L15 _public member_ `static const FString SplineLocationTag;`
- L16 _public member_ `static const FString SplineBeginTag;`
- L17 _public member_ `static const FString SplineEndTag;`
- L19 _public member_ `FVector SplineLocation;`
- L21 _protected member_ `TArray<UObject*> OutObjects;`
- L22 _protected member_ `bool bProcessedEnd = false;`
- L24 _protected prototype_ `virtual void ProcessConstructedObject(UObject* CreatedObject) override;`
- L25 _protected prototype_ `virtual bool CanCreateClass(UClass* ObjectClass, bool& bOmitSubObjs) const override;`
- L26 _protected prototype_ `virtual void ProcessUnidentifiedLine(const FString& StrLine) override;`

### `Source/Editor/LandscapeEditor/Private/LandscapeSplineSelection.h` (Private)


#### enum `ESplineNavigationFlags`  
`enum class ESplineNavigationFlags : uint8`  
_L14-28_
- L16 _public enumerator_ `None = 0`
- L17 _public enumerator_ `DirectionForward = 1 << 0`
- L18 _public enumerator_ `DirectionBackward = 1 << 1`
- L20 _public enumerator_ `SegmentSelectModeEnabled = 1 << 2`
- L21 _public enumerator_ `ControlPointSelectModeEnabled = 1 << 3`
- L23 _public enumerator_ `AddToSelection = 1 << 4`
- L24 _public enumerator_ `UpdatePropertiesWindows = 1 << 5`
- L26 _public enumerator_ `SelectModeMask = SegmentSelectModeEnabled | ControlPointSelectModeEnabled`
- L27 _public enumerator_ `DirectionMask = DirectionForward | DirectionBackward`

#### class `ULandscapeSplineSelection`  
`class ULandscapeSplineSelection : public UObject`  
_L35-103_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: ULandscapeSplineSelection
- L40 _private prototype_ `void SelectSegment(ULandscapeSplineSegment* Segment, ESplineNavigationFlags Flags = ESplineNavigationFlags::None);` — Spline Selection
- L41 _private prototype_ `void SelectControlPoint(ULandscapeSplineControlPoint* ControlPoint, ESplineNavigationFlags Flags = ESplineNavigationFlags::None);`
- L43 _private prototype_ `void ClearSelectedControlPoints();`
- L44 _private prototype_ `void ClearSelectedSegments();`
- L45 _private prototype_ `void ClearSelection();`
- L46 _private prototype_ `void DeselectControlPoint(ULandscapeSplineControlPoint* ControlPoint, ESplineNavigationFlags Flags);`
- L47 _private prototype_ `void DeSelectSegment(ULandscapeSplineSegment* Segment, ESplineNavigationFlags Flags);`
- L49 _private prototype_ `void SelectConnected();`
- L50 _private prototype_ `void SelectAllSplineSegments(const ULandscapeInfo& InLandscapeInfo);`
- L51 _private prototype_ `void SelectAllControlPoints(const ULandscapeInfo& InLandscapeInfo);`
- L52 _private prototype_ `void SelectAdjacentControlPoints();`
- L53 _private prototype_ `void SelectAdjacentSegments();`
- L55 _private prototype_ `const bool IsSegmentSelected(ULandscapeSplineSegment* Segment) const;`
- L56 _private prototype_ `const bool IsControlPointSelected(ULandscapeSplineControlPoint* ControlPoint) const;`
- L58 _private prototype_ `void UpdatePropertiesWindows() const;`
- L61 _private prototype_ `void ResetNavigationPath();` — Spline Navigation (path traversal based on current selection)
- L63 _private prototype_ `void SelectNavigationSegment(ULandscapeSplineSegment* Segment);`
- L64 _private prototype_ `void SelectNavigationControlPoint(ULandscapeSplineControlPoint* ControlPoint);`
- L65 _private prototype_ `bool IsSelectionValidForNavigation() const;`
- L67 _private prototype_ `ULandscapeSplineSegment* GetEndSegmentInLinearPath(ESplineNavigationFlags Flags) const;`
- L68 _private prototype_ `ULandscapeSplineControlPoint* GetEndControlPointInLinearPath(ESplineNavigationFlags Flags) const;`
- L69 _private prototype_ `ULandscapeSplineSegment* GetAdjacentSegmentInLinearPath(ESplineNavigationFlags Flags) const;`
- L70 _private prototype_ `ULandscapeSplineControlPoint* GetAdjacentControlPointInPath(ESplineNavigationFlags Flags) const;`
- L72 _private prototype_ `bool HasAdjacentSegmentInLinearPath(ESplineNavigationFlags Flags) const;`
- L73 _private prototype_ `bool HasAdjacentControlPointInLinearPath(ESplineNavigationFlags Flags) const;`
- L75 _private function_ `TArray<ULandscapeSplineControlPoint*> GetSelectedSplineControlPoints() const`
- L80 _private function_ `TArray<ULandscapeSplineSegment*> GetSelectedSplineSegments() const`
- L87 _private prototype_ `void BuildLinearPathFromLastSelectedPointInternal();` — Spline navigation
- L88 _private prototype_ `ULandscapeSplineControlPoint* GetLinearEndControlPointInternal(ULandscapeSplineControlPoint* SelectedControlPoint);`
- L91 _private member_ `TArray<TObjectPtr<ULandscapeSplineControlPoint>> SelectedSplineControlPoints;` — `UPROPERTY(Transient)`
- L93 _private member_ `TArray<TObjectPtr<ULandscapeSplineSegment>> SelectedSplineSegments;` — `UPROPERTY(Transient)`
- L97 _private member_ `TArray<TObjectPtr<ULandscapeSplineControlPoint>> LinearControlPoints;` — `UPROPERTY(Transient)` — Linear representation of the current spline based on the last selected point/segment
- L99 _private member_ `TArray<TObjectPtr<ULandscapeSplineSegment>> LinearSegments;` — `UPROPERTY(Transient)`
- L102 _private member_ `TOptional<UE::Widget::EWidgetMode> ControlPointWidgetMode;` — Persistent control point mode

#### Free symbols / members of external scopes

- L29 _prototype_ `ENUM_CLASS_FLAGS(ESplineNavigationFlags);`

### `Source/Editor/LandscapeEditor/Private/LandscapeTiledImage.h` (Private)


#### class `LandscapeImageTraits`  
`template<typename T> class LandscapeImageTraits`  
_L12-16_
- L15 _public function_ `static T DefaultValue()`
- L22 _public function_ `static uint16 DefaultValue()`

#### class `LandscapeImageTraits`  
`template<> class LandscapeImageTraits<uint16>`  
_L19-23_
- L15 _public function_ `static T DefaultValue()`
- L22 _public function_ `static uint16 DefaultValue()`

#### class `FLandscapeTiledImage`  
`class FLandscapeTiledImage`  
_L25-127_
- L28 _public prototype_ `FLandscapeTiledImage();`
- L31 _public prototype_ `template<typename T> FLandscapeFileInfo Load(const TCHAR* Filename);`
- L33 _public function_ `FIntPoint GetTileResolution() const`
- L34 _public function_ `FIntPoint GetSizeInTiles() const`
- L36 _public function_ `FIntPoint GetResolution() const`
- L39 _public prototype_ `static void FindFiles(const TCHAR* FilenamePattern, TArray<FString>& OutPaths);`
- L42 _public function_ `template<typename T> void Read(TArray<T>& OutImageData, bool bFlipYAxis = false) const`
- L48 _public prototype_ `static bool CheckTiledNamePath(const FString& Filename, FString& OutTiledFilenamePattern);`
- L51 _public function_ `template<typename T> FLandscapeFileInfo ReadRegion(const FIntRect& Region, TArray<T>& OutImageData, bool bFlipYAxis = false, T DefaultValue = LandscapeImageTraits<T>::DefaultValue()) const`
- L120 _private member_ `static TMap<FString, FString> Tokens;`
- L121 _private prototype_ `static FString GetTokenRegex(const FString& Prefix);`
- L123 _private member_ `TMap<FIntPoint, FString> TileFilenames;`
- L125 _private member_ `FIntPoint TileResolution = FIntPoint::NoneValue;`
- L126 _private member_ `FIntPoint SizeInTiles = FIntPoint::NoneValue;`

### `Source/Editor/LandscapeEditor/Private/SFlattenHeightEyeDropperButton.h` (Private)


#### class `SFlattenHeightEyeDropperButton`  
`class SFlattenHeightEyeDropperButton : public SButton`  
_L15-56_
- inherits: `SButton`
- L18 _public prototype_ `virtual ~SFlattenHeightEyeDropperButton();`
- L20 _public function_ `SLATE_BEGIN_ARGS(SFlattenHeightEyeDropperButton) : _OnBegin() , _OnComplete()`
- L26 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Invoked when the dropper goes from inactive to active
- L37 _private prototype_ `FReply OnClicked();`
- L38 _private prototype_ `void OnMouseHovered();`
- L39 _private prototype_ `void OnMouseUnhovered();`
- L41 _private prototype_ `EVisibility GetEscapeTextVisibility() const;`
- L43 _private prototype_ `void OnApplicationPreInputKeyDownListener(const FKeyEvent& InKeyEvent);`
- L44 _private prototype_ `void OnApplicationMousePreInputButtonDownListener(const FPointerEvent& MouseEvent);`
- L49 _private member_ `FSimpleDelegate OnBegin;` — Invoked when the dropper goes from inactive to active
- L52 _private member_ `FOnDropperComplete OnComplete;` — Invoked when the dropper goes from active to inactive - can be used to commit colors by the owning picker
- L54 _private member_ `bool bWasClickActivated;`
- L55 _private member_ `bool bIsOverButton;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDropperComplete, bool) class SFlattenHeightEyeDropperButton : public SButton { public: virtual ~SFlattenHeightEyeDropperButton(); SLATE_BEGIN_ARGS(SFlattenHeightEyeDropperButton) : _OnBegin() , _OnComplete() {} SLATE_EVENT(FSimpleDelegate, OnBegin) SLATE_EVENT(FOnDropperComplete, OnComplete) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: FReply OnClicked(); void OnMouseHovered(); void OnMouseUnhovered(); EVisibility GetEscapeTextVisibility() const; void OnApplicationPreInputKeyDownListener(const FKeyEvent& InKeyEvent); void OnApplicationMousePreInputButtonDownListener(const FPointerEvent& MouseEvent); private: FSimpleDelegate OnBegin; FOnDropperComplete OnComplete;`

### `Source/Editor/LandscapeEditor/Private/SLandscapeEditor.h` (Private)


#### class `SLandscapeAssetThumbnail`  
`class SLandscapeAssetThumbnail : public SCompoundWidget`  
_L25-45_
- inherits: `SCompoundWidget`
- desc: Slate widget wrapping an FAssetThumbnail and Viewport
- L28 _public function_ `SLATE_BEGIN_ARGS( SLandscapeAssetThumbnail ) : _ThumbnailSize( 64,64 )`
- L30 _public prototype_ `SLATE_ARGUMENT(FIntPoint, ThumbnailSize) SLATE_EVENT(FAccessAsset, OnAccessAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UObject* Asset, TSharedRef<FAssetThumbnailPool> ThumbnailPool, const FName& ClassThumbnailBrushOverride);`
- L35 _public prototype_ `~SLandscapeAssetThumbnail();`
- L37 _public prototype_ `void SetAsset(UObject* Asset);`
- L38 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L41 _private prototype_ `void OnMaterialCompilationFinished(UMaterialInterface* MaterialInterface);`
- L43 _private member_ `FAccessAsset OnAccessAsset;`
- L44 _private member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`

#### class `FLandscapeToolKit`  
`class FLandscapeToolKit : public FModeToolkit`  
_L57-117_
- inherits: `FModeToolkit`
- desc: Mode Toolkit for the Landscape Editor Mode
- L61 _public prototype_ `virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost) override;` — Initializes the landscape mode toolkit
- L64 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L65 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L66 _public prototype_ `virtual FEdModeLandscape* GetEditorMode() const override;`
- L67 _public prototype_ `virtual TSharedPtr<SWidget> GetInlineContent() const override;`
- L69 _public prototype_ `void NotifyToolChanged();`
- L70 _public prototype_ `void NotifyBrushChanged();`
- L71 _public prototype_ `void RefreshDetailPanel();`
- L72 _public prototype_ `void RefreshInspectedObjectsDetailPanel();`
- L75 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const;` — Mode Toolbar Palettes
- L76 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const;`
- L77 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder);`
- L78 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L81 _public prototype_ `virtual FText GetActiveToolDisplayName() const;` — Modes Panel Header Information
- L82 _public prototype_ `virtual FText GetActiveToolMessage() const;`
- L84 _public prototype_ `bool GetIsPropertyVisibleFromProperty(const FProperty& Property) const;`
- L87 _protected prototype_ `void OnChangeMode(FName ModeName);`
- L88 _protected prototype_ `bool IsModeEnabled(FName ModeName) const;`
- L89 _protected prototype_ `bool IsModeActive(FName ModeName) const;`
- L91 _protected prototype_ `void OnChangeTool(FName ToolName);`
- L92 _protected prototype_ `bool IsToolEnabled(FName ToolName) const;`
- L93 _protected prototype_ `bool IsToolActive(FName ToolName) const;`
- L95 _protected prototype_ `void OnChangeBrushSet(FName BrushSetName);`
- L96 _protected prototype_ `bool IsBrushSetEnabled(FName BrushSetName) const;`
- L97 _protected prototype_ `bool IsBrushSetActive(FName BrushSetName) const;`
- L99 _protected prototype_ `void OnChangeBrush(FName BrushName);`
- L100 _protected prototype_ `bool IsBrushActive(FName BrushName) const;`
- L103 _protected prototype_ `virtual void RequestModeUITabs() override;` — FModeToolkit interface
- L104 _protected prototype_ `virtual void InvokeUI() override;`
- L106 _protected prototype_ `TSharedRef<SDockTab> CreateInspectedObjectsDetailsViewTab(const FSpawnTabArgs& Args);`
- L109 _private member_ `TSharedPtr<SLandscapeEditor> LandscapeEditorWidgets;`
- L110 _private member_ `TSharedPtr<FLandscapeEditorDetails> BrushesWidgets;`
- L112 _private member_ `TWeakPtr<SDockTab> InspectedObjectsTab;`
- L113 _private member_ `FMinorTabConfig InspectedObjectsTabInfo;`
- L114 _private member_ `TSharedPtr<SLandscapeEditorInspectedDetailsView> InspectedObjectsDetailsView;`
- L116 _private member_ `const static TArray<FName> PaletteNames;`

#### class `SLandscapeEditor`  
`class SLandscapeEditor : public SCompoundWidget`  
_L122-148_
- inherits: `SCompoundWidget`
- desc: Slate widgets for the Landscape Editor Mode
- L125 _public function_ `SLATE_BEGIN_ARGS( SLandscapeEditor )`
- L126 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FLandscapeToolKit> InParentToolkit);`
- L130 _public prototype_ `void NotifyToolChanged();`
- L131 _public prototype_ `void NotifyBrushChanged();`
- L132 _public prototype_ `void RefreshDetailPanel();`
- L135 _protected prototype_ `class FEdModeLandscape* GetEditorMode() const;`
- L137 _protected prototype_ `FText GetErrorText() const;`
- L139 _protected prototype_ `bool GetLandscapeEditorIsEnabled() const;`
- L140 _protected prototype_ `bool GetInspectedObjectsDetailsIsVisible() const;`
- L142 _protected prototype_ `bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;`
- L145 _protected member_ `TSharedPtr<SErrorText> Error;`
- L146 _protected member_ `TSharedPtr<IDetailsView> DetailsPanel;`
- L147 _protected member_ `TWeakPtr<FLandscapeToolKit> ParentToolkit;`

#### class `SLandscapeEditorInspectedDetailsView`  
`class SLandscapeEditorInspectedDetailsView : public SCompoundWidget`  
_L153-169_
- inherits: `SCompoundWidget`
- desc: Slate widget for the Landscape Editor Inspected Objects Details View
- L156 _public function_ `SLATE_BEGIN_ARGS(SLandscapeEditorInspectedDetailsView)`
- L159 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L162 _public prototype_ `void RefreshDetailPanel();`
- L165 _protected prototype_ `class FEdModeLandscape* GetEditorMode() const;`
- L168 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace LandscapeEditorNames`
- L49 _variable_ `static const FName Manage(TEXT("Tool` (scope `LandscapeEditorNames`)
- L50 _variable_ `static const FName Sculpt(TEXT("Tool` (scope `LandscapeEditorNames`)
- L51 _variable_ `static const FName Paint(TEXT("Tool` (scope `LandscapeEditorNames`)

### `Source/Editor/LandscapeEditor/Public/LandscapeEditLayerCustomization.h` (Public)


#### struct `FEditLayerMenuBlock`  
`struct FEditLayerMenuBlock`  
_L11-15_
- L13 _public member_ `TArray<FMenuEntryParams> Entries;`
- L14 _public member_ `FText SectionLabel;`

#### class `IEditLayerCustomization`  
`class IEditLayerCustomization : public TSharedFromThis<IEditLayerCustomization>`  
_L23-30_
- inherits: `TSharedFromThis<IEditLayerCustomization>`
- desc: Interface for Edit Layer classes that expand on customizations not covered by IDetailsView (Context Menu, Dialog, etc.)
- L26 _public prototype_ `virtual ~IEditLayerCustomization() = default;`
- L29 _public prototype_ `virtual void CustomizeContextMenu(ULandscapeEditLayerBase* InEditLayer, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) = 0;` — Called when building edit layer context menus

#### Free symbols / members of external scopes

- L18 _typedef_ `using FEditLayerCategoryToEntryMap = TMap<FName, FEditLayerMenuBlock>;` — Map of context menu Category Names to their entries

### `Source/Editor/LandscapeEditor/Public/LandscapeEditorModule.h` (Public)


#### class `ILandscapeEditorModule`  
`class ILandscapeEditorModule : public IModuleInterface`  
_L33-78_
- inherits: `IModuleInterface`
- desc: LandscapeEditor module interface
- L37 _public prototype_ `virtual void RegisterHeightmapFileFormat(TSharedRef<ILandscapeHeightmapFileFormat> FileFormat) = 0;` — Register / unregister a landscape file format plugin
- L38 _public prototype_ `virtual void RegisterWeightmapFileFormat(TSharedRef<ILandscapeWeightmapFileFormat> FileFormat) = 0;`
- L39 _public prototype_ `virtual void UnregisterHeightmapFileFormat(TSharedRef<ILandscapeHeightmapFileFormat> FileFormat) = 0;`
- L40 _public prototype_ `virtual void UnregisterWeightmapFileFormat(TSharedRef<ILandscapeWeightmapFileFormat> FileFormat) = 0;`
- L43 _public prototype_ `virtual const TCHAR* GetHeightmapImportDialogTypeString() const = 0;` — Gets the type string used by the import/export file dialog
- L44 _public prototype_ `virtual const TCHAR* GetWeightmapImportDialogTypeString() const = 0;`
- L45 _public prototype_ `virtual const TCHAR* GetHeightmapExportDialogTypeString() const = 0;`
- L46 _public prototype_ `virtual const TCHAR* GetWeightmapExportDialogTypeString() const = 0;`
- L49 _public prototype_ `virtual void RegisterCustomEditLayerClassLayout(FName ClassName, FOnGetLandscapeEditLayerCustomizationInstance EditLayerLayoutDelegate) = 0;` — Edit layer customizations
- L50 _public prototype_ `virtual void UnregisterCustomEditLayerClassLayout(FName ClassName) = 0;`
- L52 _public prototype_ `virtual TArray<TSharedRef<IEditLayerCustomization>> QueryCustomEditLayerLayoutRecursive(UStruct* InClass) = 0;`
- L53 _public prototype_ `virtual TSharedPtr<IEditLayerCustomization> QueryCustomEditLayerLayoutForClass(UStruct* InClass) = 0;`
- L55 _public prototype_ `virtual void ApplyEditLayerContextMenuCustomizations(ULandscapeEditLayerBase* InEditLayer, const TArray<TSharedRef<IEditLayerCustomization>>& InCustomizations, FEditLayerCategoryToEntryMap& OutContextMenuEntryMap) = 0;`
- L58 _public prototype_ `virtual const ILandscapeHeightmapFileFormat* GetHeightmapFormatByExtension(const TCHAR* Extension) const = 0;` — Gets the heightmap/weightmap format associated with a given extension (null if no plugin is registered for this extension)
- L59 _public prototype_ `virtual const ILandscapeWeightmapFileFormat* GetWeightmapFormatByExtension(const TCHAR* Extension) const = 0;`
- L62 _public function_ `template<typename T> typename TEnableIf<std::is_same_v<T, uint16>, const ILandscapeHeightmapFileFormat*>::Type GetFormatByExtension(const TCHAR* Extension)`
- L68 _public function_ `template<typename T> typename TEnableIf<std::is_same_v<T, uint8>, const ILandscapeWeightmapFileFormat*>::Type GetFormatByExtension(const TCHAR* Extension)`
- L73 _public prototype_ `virtual TSharedPtr<FUICommandList> GetLandscapeLevelViewportCommandList() const = 0;`
- L75 _public prototype_ `virtual FLandscapeImageFileCache& GetImageFileCache() const = 0;`

#### Free symbols / members of external scopes

- L15 _typedef_ `using ILandscapeHeightmapFileFormat = ILandscapeFileFormat<uint16>;`
- L16 _typedef_ `using ILandscapeWeightmapFileFormat = ILandscapeFileFormat<uint8>;`
- L23 _typedef_ `using FEditLayerCategoryToEntryMap = TMap<FName, FEditLayerMenuBlock>;`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<IEditLayerCustomization>, FOnGetLandscapeEditLayerCustomizationInstance);` — Delegate called to get customizations for a specific edit layer class
- L26 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<IEditLayerCustomization>, FOnGetLandscapeEditLayerCustomizationInstance);` — Delegate called to get customizations for a specific edit layer class
- L28 _typedef_ `using FCustomEditLayerLayoutNameMap = TMap<FName, FOnGetLandscapeEditLayerCustomizationInstance>;`

### `Source/Editor/LandscapeEditor/Public/LandscapeEditorObject.h` (Public)


#### enum `ELandscapeToolFlattenMode`  
`enum class ELandscapeToolFlattenMode : int8`  
_L22-40_
- reflection: `UENUM()`
- L24 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L27 _public enumerator_ `Both = 0` — Flatten may both raise and lower values
- L30 _public enumerator_ `Raise = 1` — Flatten may only raise values, values above the clicked point will be left unchanged
- L33 _public enumerator_ `Lower = 2` — Flatten may only lower values, values below the clicked point will be left unchanged
- L36 _public enumerator_ `Interval = 3` — Flatten to closest specific terrace interval at the clicked point
- L39 _public enumerator_ `Terrace = 4` — Flatten to specific terrace height intervals

#### enum `ELandscapeToolErosionMode`  
`enum class ELandscapeToolErosionMode : int8`  
_L43-55_
- reflection: `UENUM()`
- L45 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L48 _public enumerator_ `Both = 0` — Apply all erosion effects, both raising and lowering the heightmap
- L51 _public enumerator_ `Raise = 1` — Only applies erosion effects that result in raising the heightmap
- L54 _public enumerator_ `Lower = 2` — Only applies erosion effects that result in lowering the heightmap

#### enum `ELandscapeToolHydroErosionMode`  
`enum class ELandscapeToolHydroErosionMode : int8`  
_L58-67_
- reflection: `UENUM()`
- L60 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L63 _public enumerator_ `Both = 0` — Rains in some places and not others, randomly
- L66 _public enumerator_ `Positive = 1` — Rain is applied to the entire area

#### enum `ELandscapeToolNoiseMode`  
`enum class ELandscapeToolNoiseMode : int8`  
_L70-82_
- reflection: `UENUM()`
- L72 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L75 _public enumerator_ `Both = 0` — Noise will both raise and lower the heightmap
- L78 _public enumerator_ `Add = 1` — Noise will only raise the heightmap
- L81 _public enumerator_ `Sub = 2` — Noise will only lower the heightmap

#### enum `ELandscapeToolPasteMode`  
`enum class ELandscapeToolPasteMode : int8`  
_L103-115_
- reflection: `UENUM()`
- L105 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L108 _public enumerator_ `Both = 0` — Paste may both raise and lower values
- L111 _public enumerator_ `Raise = 1` — Paste may only raise values, places where the pasted data would be below the heightmap are left unchanged. Good for copy/pasting mountains
- L114 _public enumerator_ `Lower = 2` — Paste may only lower values, places where the pasted data would be above the heightmap are left unchanged. Good for copy/pasting valleys or pits

#### enum `ELandscapeConvertMode`  
`enum class ELandscapeConvertMode : int8`  
_L118-130_
- reflection: `UENUM()`
- L120 _public enumerator_ `Invalid = -1 UMETA(Hidden)`
- L123 _public enumerator_ `Expand = 0` — Will round up the number of components for the new world size, which might expand the world size compared to previous settings
- L126 _public enumerator_ `Clip = 1` — Will floor the number of components for the new world size, which might reduce the world size compared to previous settings
- L129 _public enumerator_ `Resample = 2` — The landscape will have the same overall size in the world, and have the same number of components. Existing landscape geometry and layer data will be resampled to match the new resolution.

#### enum `ELandscapeTextureColorChannel`  
`enum class ELandscapeTextureColorChannel : int32`  
_L133-139_
- reflection: `UENUM()`
- L135 _public enumerator_ `Red`
- L136 _public enumerator_ `Green`
- L137 _public enumerator_ `Blue`
- L138 _public enumerator_ `Alpha`

#### enum `ELandscapeMirrorOperation`  
`enum class ELandscapeMirrorOperation : uint8`  
_L142-152_
- reflection: `UENUM()`
- L144 _public enumerator_ `MinusXToPlusX UMETA(DisplayName="-X to +X")`
- L145 _public enumerator_ `PlusXToMinusX UMETA(DisplayName="+X to -X")`
- L146 _public enumerator_ `MinusYToPlusY UMETA(DisplayName="-Y to +Y")`
- L147 _public enumerator_ `PlusYToMinusY UMETA(DisplayName="+Y to -Y")`
- L148 _public enumerator_ `RotateMinusXToPlusX UMETA(DisplayName="Rotate -X to +X")`
- L149 _public enumerator_ `RotatePlusXToMinusX UMETA(DisplayName="Rotate +X to -X")`
- L150 _public enumerator_ `RotateMinusYToPlusY UMETA(DisplayName="Rotate -Y to +Y")`
- L151 _public enumerator_ `RotatePlusYToMinusY UMETA(DisplayName="Rotate +Y to -Y")`

#### struct `FGizmoImportLayer`  
`struct FGizmoImportLayer`  
_L155-174_
- reflection: `USTRUCT()`
- L160 _public member_ `FString LayerFilename;` — `UPROPERTY(Category="Import", EditAnywhere, meta = (DisplayName = "Target Layer Filename"))`
- L163 _public member_ `FString LayerName;` — `UPROPERTY(Category="Import", EditAnywhere, meta = (DisplayName = "Target Layer Name", ToolTip = "Layer Name must match an existing target layer on the Landscape or the import will fail."))`
- L166 _public member_ `bool bNoImport;` — `UPROPERTY(Category="Import", EditAnywhere)`
- L168 _public function_ `FGizmoImportLayer() : LayerFilename("") , LayerName("") , bNoImport(false)`

#### enum `ELandscapeImportHeightmapError`  
`enum class ELandscapeImportHeightmapError`  
_L177-185_
- reflection: `UENUM()`
- L179 _public enumerator_ `None`
- L180 _public enumerator_ `FileNotFound`
- L181 _public enumerator_ `InvalidSize`
- L182 _public enumerator_ `CorruptFile`
- L183 _public enumerator_ `ColorPng`
- L184 _public enumerator_ `LowBitDepth`

#### enum `ELandscapeImportLayerError`  
`enum class ELandscapeImportLayerError : uint8`  
_L188-196_
- reflection: `UENUM()`
- L190 _public enumerator_ `None`
- L191 _public enumerator_ `MissingLayerInfo`
- L192 _public enumerator_ `FileNotFound`
- L193 _public enumerator_ `FileSizeMismatch`
- L194 _public enumerator_ `CorruptFile`
- L195 _public enumerator_ `ColorPng`

#### struct `FLandscapeImportLayer`  
`struct FLandscapeImportLayer : public FLandscapeImportLayerInfo`  
_L199-228_
- reflection: `USTRUCT()`
- inherits: `FLandscapeImportLayerInfo`
- L204 _public member_ `TObjectPtr<ULandscapeMaterialInstanceConstant> ThumbnailMIC;` — `UPROPERTY(Category="Import", VisibleAnywhere)`
- L207 _public member_ `ELandscapeImportResult ImportResult;` — `UPROPERTY(Category = "Import", VisibleAnywhere)`
- L210 _public member_ `FText ErrorMessage;` — `UPROPERTY(Category = "Import", VisibleAnywhere)`
- L213 _public member_ `FString ExportFilePath;` — `UPROPERTY(Category="Export", EditAnywhere, meta = (DisplayName = "Layer File"))`
- L216 _public member_ `bool bSelected;` — `UPROPERTY(Category="Import", EditAnywhere)`
- L218 _public member_ `FLandscapeImportDescriptor ImportDescriptor;`
- L220 _public function_ `FLandscapeImportLayer() : FLandscapeImportLayerInfo() , ThumbnailMIC(nullptr) , ImportResult(ELandscapeImportResult::Success) , ErrorMessage(FText()) , bSelected(false)`

#### struct `FLandscapePatternBrushWorldSpaceSettings`  
`struct FLandscapePatternBrushWorldSpaceSettings`  
_L231-262_
- reflection: `USTRUCT()`
- L236 _public member_ `FVector2D Origin;` — `UPROPERTY(Category="World-Space", EditAnywhere)`
- L239 _public member_ `float Rotation;` — `UPROPERTY(Category = "World-Space", EditAnywhere, Meta = (ClampMin = "-360", ClampMax = "360", UIMin = "-180", UIMax = "180"))`
- L244 _public member_ `bool bCenterTextureOnOrigin;` — `UPROPERTY(Category = "World-Space", EditAnywhere)` — if true, the texture used for the pattern is centered on the PatternOrigin. if false, the corner of the texture is placed at the PatternOrigin
- L247 _public member_ `float RepeatSize;` — `UPROPERTY(Category = "World-Space", EditAnywhere)`
- L249 _public function_ `FLandscapePatternBrushWorldSpaceSettings() : Origin(ForceInit) , Rotation(0.0f) , bCenterTextureOnOrigin(false) , RepeatSize(0.0f)`
- L256 _public function_ `FLandscapePatternBrushWorldSpaceSettings(const FVector2D& InOrigin, float InRotation, bool bInCenterTextureOnOrigin, float bRepeatSize) : Origin(InOrigin) , Rotation(InRotation) , bCenterTextureOnOrigin(bInCenterTextureOnOrigin) , RepeatSize(bRepeatSize)`

#### struct `FLandscapeTargetLayerAssetFilePath`  
`struct FLandscapeTargetLayerAssetFilePath`  
_L265-280_
- reflection: `USTRUCT()`
- L270 _public member_ `bool bUseAssetDirectoryPath = false;` — `UPROPERTY(Category = "Target Layers", EditAnywhere, NonTransactional, meta=(InlineEditConditionToggle))`
- L273 _public member_ `FDirectoryPath DirectoryPath;` — `UPROPERTY(Category = "Target Layers", EditAnywhere, NonTransactional, meta = (EditCondition = bUseAssetDirectoryPath, LongPackageName))`
- L275 _public function_ `FLandscapeTargetLayerAssetFilePath() : bUseAssetDirectoryPath(false) , DirectoryPath()`

#### enum `ELandscapeImportExportMode`  
`enum class ELandscapeImportExportMode`  
_L283-291_
- reflection: `UENUM()`
- L286 _public enumerator_ `LoadedOnly` — Import and export only loaded landscape proxies
- L288 _public enumerator_ `All` — Import and export the whole world loading & unloading regions as required.

#### enum `ELandscapeWeightBlendPaintMode`  
`enum class ELandscapeWeightBlendPaintMode`  
_L294-313_
- reflection: `UENUM()`
- L300 _public enumerator_ `ExclusiveRequiresCtrl UMETA(DisplayName = "Hold Ctrl")` — Exclusive Mode for weight-blended layers will be active only when the Ctrl key is held. Non-Exclusive Mode is used otherwise. Note : this mode is incompatible with LandscapeEditorControlType "RequireCtrl" since the Ctrl key is then reserved for activating the landscape tools in that case. Use one of the manual modes in that case.
- L306 _public enumerator_ `ExclusiveRequiresNoCtrl UMETA(DisplayName = "Don't Hold Ctrl")` — Exclusive Mode for weight-blended layers will be active only when the Ctrl key is not held. Non-Exclusive Mode is used otherwise. Note : this mode is incompatible with LandscapeEditorControlType "RequireNoCtrl" since the Ctrl key is then reserved for activating the landscape tools in that case. Use one of the manual modes in that case.
- L309 _public enumerator_ `ForceExclusive UMETA(DisplayName = "Exclusive")` — Force use Exclusive Mode for weight-blended layers. The Ctrl key is ineffective in that mode.
- L312 _public enumerator_ `ForceNonExclusive UMETA(DisplayName = "Non-Exclusive")` — Force use Non-Exclusive Mode for weight-blended layers. The Ctrl key is ineffective in that mode.

#### class `ULandscapeEditorObject`  
`class ULandscapeEditorObject : public UObject`  
_L317-907_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L321 _private member_ `FEdModeLandscape* ParentMode;`
- L328 _private member_ `float ToolStrength;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Tool Strength", ShowForTools="Paint,Sculpt,Erase,Smooth,Flatten,Erosion,HydraErosion,Noise,Mask,CopyPaste", ShowForTargetTypes = "Heightmap,Visibility", ClampMin="0", ClampMax="10", UIMin="0", UIMax="1"))` — Strength of the Sculpt tool. If you're using a pen/tablet with pressure-sensing, the pressure used affects the strength of the tool.
- L332 _private member_ `float PaintToolStrength;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Tool Strength", ShowForTools="Paint,Sculpt,Erase,Smooth,Flatten,Erosion,HydraErosion,Noise,Mask,CopyPaste", ShowForTargetTypes = "Weightmap", ClampMin="0", ClampMax="10", UIMin="0", UIMax="1"))` — Strength of the Paint tool. If you're using a pen/tablet with pressure-sensing, the pressure used affects the strength of the tool.
- L336 _private member_ `bool bUseWeightTargetValue;` — `UPROPERTY(Category = "Tool Settings", NonTransactional, EditAnywhere, meta = (InlineEditConditionToggle))` — Enable to make tools blend towards a target value
- L340 _private member_ `float WeightTargetValue;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Use Target Value", EditCondition="bUseWeightTargetValue", ShowForTools="Paint,Sculpt,Noise", ShowForTargetTypes = "Weightmap", ClampMin="0", ClampMax="10", UIMin="0", UIMax="1"))` — Enable to make tools blend towards a target value
- L344 _private member_ `float MaximumValueRadius;` — `UPROPERTY(NonTransactional)` — I have no idea what this is for but it's used by the noise and erosion tools, and isn't exposed to the UI
- L348 _private member_ `bool bCombinedLayersOperation;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Flatten,Smooth,Erosion,HydraErosion,Ramp", ShowForTargetTypes="Heightmap"))` — Use the combined result of the underlying layers as input to the operation.  When not checked, it will use only the data in the currently selected layer as input.
- L354 _private member_ `ELandscapeToolFlattenMode FlattenMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Flatten"))` — Whether to flatten by lowering, raising, both or terracing
- L358 _private member_ `bool bUseSlopeFlatten;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Flatten", ShowForTargetTypes="Heightmap"))` — Flattens to the angle of the clicked point, instead of horizontal
- L362 _private member_ `bool bPickValuePerApply;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Flatten", ShowForTargetTypes="Heightmap"))` — Constantly picks new values to flatten towards when dragging around, instead of only using the first clicked point
- L366 _private member_ `bool bUseFlattenTarget;` — `UPROPERTY(Category = "Tool Settings", NonTransactional, EditAnywhere, meta = (InlineEditConditionToggle))` — Enable to flatten towards a target height
- L370 _private member_ `float FlattenTarget;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Flatten", ShowForTargetTypes="Heightmap", EditCondition="bUseFlattenTarget", UIMin="-32768", UIMax="32768"))` — Target height to flatten towards (in Unreal Units)
- L374 _private member_ `bool bShowFlattenTargetPreview;` — `UPROPERTY(Category = "Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta = (DisplayName = "Show Preview Grid", ShowForTools = "Flatten", ShowForTargetTypes = "Heightmap", EditCondition = "bUseFlattenTarget", HideEditConditionToggle))` — Whether to show the preview grid for the flatten target height
- L378 _private member_ `float TerraceInterval;` — `UPROPERTY(Category = "Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta = (DisplayName = "Terrace Interval", ShowForTools = "Flatten", ShowForTargetTypes = "Heightmap", UIMin = "1", UIMax = "32768"))` — Height of the terrace intervals in unreal units, for the terrace flatten mode
- L382 _private member_ `float TerraceSmooth;` — `UPROPERTY(Category = "Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta = (DisplayName = "Terrace Smoothing", ShowForTools = "Flatten", ShowForTargetTypes = "Heightmap", UIMin = "0.0001", UIMax = "1.0"))` — Smoothing value for terrace flatten mode
- L386 _private member_ `bool bFlattenEyeDropperModeActivated;` — `UPROPERTY(NonTransactional, Transient)` — Whether the Eye Dropper mode is activated
- L390 _private member_ `bool bFlattenEyeDropperModeMousingOverViewport;` — `UPROPERTY(NonTransactional, Transient)` — When in Eye Dropper mode, indicates whether we're currently mousing over the viewport
- L393 _private member_ `float FlattenEyeDropperModeDesiredTarget;` — `UPROPERTY(NonTransactional, Transient)`
- L399 _private member_ `float RampWidth;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Ramp", ClampMin="1", UIMin="1", UIMax="8192", SliderExponent=3))` — Width of ramp
- L403 _private member_ `float RampSideFalloff;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Side Falloff", ShowForTools="Ramp", ClampMin="0", ClampMax="1", UIMin="0", UIMax="1"))` — Falloff on side of ramp
- L410 _private member_ `int32 SmoothFilterKernelSize;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Filter Kernel Radius", ShowForTools="Smooth", ClampMin="1", ClampMax="31", UIMin="0", UIMax="7"))` — The radius smoothing is performed over Higher values smooth out bigger details, lower values only smooth out smaller details
- L414 _private member_ `bool bDetailSmooth;` — `UPROPERTY(Category = "Tool Settings", NonTransactional, EditAnywhere, meta = (InlineEditConditionToggle))` — If checked, performs a detail preserving smooth using the specified detail smoothing value
- L418 _private member_ `float DetailScale;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Detail Smooth", EditCondition="bDetailSmooth", ShowForTools="Smooth", ClampMin="0", ClampMax="0.99"))` — Larger detail smoothing values remove more details, while smaller values preserve more details
- L424 _private member_ `int32 ErodeThresh;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Threshold", ShowForTools="Erosion", ClampMin="0", ClampMax="256", UIMin="0", UIMax="128"))` — The minimum height difference necessary for the erosion effects to be applied. Smaller values will result in more erosion being applied
- L428 _private member_ `int32 ErodeSurfaceThickness;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Surface Thickness", ShowForTools="Erosion", ClampMin="128", ClampMax="1024", UIMin="128", UIMax="512"))` — The thickness of the surface for the layer weight erosion effect
- L432 _private member_ `int32 ErodeIterationNum;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Iterations", ShowForTools="Erosion", ClampMin="1", ClampMax="300", UIMin="1", UIMax="150"))` — Number of erosion iterations, more means more erosion but is slower
- L436 _private member_ `ELandscapeToolErosionMode ErosionNoiseMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Noise Mode", ShowForTools="Erosion"))` — Whether to erode by lowering, raising, or both
- L440 _private member_ `float ErosionNoiseScale;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Noise Scale", ShowForTools="Erosion", ClampMin="1", ClampMax="512", UIMin="1.1", UIMax="256"))` — The size of the perlin noise filter used
- L444 _private member_ `bool bErosionUseLayerHardness;` — `UPROPERTY(Category = "Tool Settings", EditAnywhere, NonTransactional, meta = (DisplayName = "Use Layer Hardness", ShowForTools = "Erosion"))` — Whether the erosion tool should take into account the paint layer's hardness parameter (a hardness of 0 means the layer is fully affected by erosion, while 1 means fully unaffected)
- L450 _private member_ `int32 RainAmount;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="HydraErosion", ClampMin="1", ClampMax="512", UIMin="1", UIMax="256"))` — The amount of rain to apply to the surface. Larger values will result in more erosion
- L454 _private member_ `float SedimentCapacity;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Sediment Capacity", ShowForTools="HydraErosion", ClampMin="0.1", ClampMax="1.0"))` — The amount of sediment that the water can carry. Larger values will result in more erosion
- L458 _private member_ `int32 HErodeIterationNum;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Iterations", ShowForTools="HydraErosion", ClampMin="1", ClampMax="300", UIMin="1", UIMax="150"))` — Number of erosion iterations, more means more erosion but is slower
- L462 _private member_ `ELandscapeToolHydroErosionMode RainDistMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Initial Rain Distribution", ShowForTools="HydraErosion"))` — Selects how rain is distributed over the brush area for hydro erosion
- L466 _private member_ `float RainDistScale;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="HydraErosion", ClampMin="1", ClampMax="512", UIMin="1.1", UIMax="256"))` — The size of the noise filter for applying initial rain to the surface
- L470 _private member_ `bool bHErosionDetailSmooth;` — `UPROPERTY(Category = "Tool Settings", NonTransactional, EditAnywhere, meta = (InlineEditConditionToggle))` — If checked, performs a detail-preserving smooth to the erosion effect using the specified detail smoothing value
- L474 _private member_ `float HErosionDetailScale;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Detail Smooth", EditCondition="bHErosionDetailSmooth", ShowForTools="HydraErosion", ClampMin="0", ClampMax="0.99"))` — Larger detail smoothing values remove more details, while smaller values preserve more details
- L480 _private member_ `ELandscapeToolNoiseMode NoiseMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Noise Mode", ShowForTools="Noise"))` — Whether to apply noise that raises, lowers, or both
- L484 _private member_ `float NoiseScale;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Noise Scale", ShowForTools="Noise", ClampMin="1", ClampMax="512", UIMin="1.1", UIMax="256"))` — The size of the perlin noise filter used
- L490 _private member_ `bool bUseSelectedRegion;` — `UPROPERTY(Category="Select Mask", EditAnywhere, NonTransactional, meta=(DisplayName="Use Region as Mask", ShowForTools="Mask", ShowForMask))` — Uses selected region as a mask for other tools
- L495 _private member_ `bool bUseNegativeMask;` — `UPROPERTY(Category="Select Mask", EditAnywhere, NonTransactional, meta=(DisplayName="Negative Mask", ShowForTools="Mask", ShowForMask))` — If enabled, protects the selected region from changes If disabled, only allows changes in the selected region
- L501 _private member_ `ELandscapeToolPasteMode PasteMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="CopyPaste"))` — Whether to paste will only raise, only lower, or both
- L505 _private member_ `bool bApplyToAllTargets;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Gizmo copy/paste all layers", ShowForTools="CopyPaste"))` — If set, copies/pastes all layers, otherwise only copy/pastes the layer selected in the targets panel
- L509 _private member_ `TWeakObjectPtr<ALandscapeGizmoActiveActor> CurrentGizmoActor;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, Transient, meta=(ShowForTools="ImportExport,CopyPaste"))` — The current gizmo actor. Only the gizmo location is revealed to the user interface
- L513 _private member_ `ELandscapeGizmoSnapType SnapMode;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Snap Gizmo to Landscape grid", ShowForTools="CopyPaste,ImportExport"))` — Allows to snap the copied/imported data to a grid
- L517 _private member_ `bool bSmoothGizmoBrush;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Use Smooth Gizmo Brush", ShowForTools="CopyPaste"))` — Smooths the edges of the gizmo data into the landscape. Without this, the edges of the pasted data will be sharp
- L520 _private member_ `FString GizmoHeightmapFilenameString;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta=(DisplayName="Heightmap", ShowForTools="CopyPaste"))`
- L523 _private member_ `FIntPoint GizmoImportSize;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta=(DisplayName="Heightmap Size", ShowForTools="CopyPaste"))`
- L526 _private member_ `TArray<FGizmoImportLayer> GizmoImportLayers;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, AdvancedDisplay, meta=(DisplayName="Target Layers", ShowForTools="CopyPaste"))`
- L532 _private member_ `FVector2D MirrorPoint;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, Transient, meta=(DisplayName="Mirror Point", ShowForTools="Mirror"))` — Location of the mirror plane, defaults to the center of the landscape. Doesn't normally need to be changed!
- L536 _private member_ `ELandscapeMirrorOperation MirrorOp;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Operation", ShowForTools="Mirror"))` — Type of mirroring operation to perform e.g. "Minus X To Plus X" copies and flips the -X half of the landscape onto the +X half
- L540 _private member_ `int32 MirrorSmoothingWidth;` — `UPROPERTY(Category="Tool Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Smoothing Width", ShowForTools="Mirror", ClampMin="0", UIMin="0", UIMax="20"))` — Number of vertices either side of the mirror plane to smooth over
- L544 _private member_ `TSubclassOf<ALandscapeBlueprintBrushBase> BlueprintBrush;` — `UPROPERTY(Category = "Tool Settings", EditAnywhere, Transient, meta = (DisplayName = "Blueprint Brush", ShowForTools = "BlueprintBrush"))` — Selects the blueprint brush to apply to the current edit layer. Click on the landscape to apply it.
- L550 _private member_ `int32 ResizeLandscape_QuadsPerSection;` — `UPROPERTY(Category="Change Component Size", EditAnywhere, NonTransactional, meta=(DisplayName="Section Size", ShowForTools="ResizeLandscape"))` — Number of quads per landscape component section
- L554 _private member_ `int32 ResizeLandscape_SectionsPerComponent;` — `UPROPERTY(Category="Change Component Size", EditAnywhere, NonTransactional, meta=(DisplayName="Sections Per Component", ShowForTools="ResizeLandscape"))` — Number of sections per landscape component
- L558 _private member_ `FIntPoint ResizeLandscape_ComponentCount;` — `UPROPERTY(Category="Change Component Size", EditAnywhere, NonTransactional, meta=(DisplayName="Number of Components", ShowForTools="ResizeLandscape"))` — Number of components in resulting landscape
- L562 _private member_ `ELandscapeConvertMode ResizeLandscape_ConvertMode;` — `UPROPERTY(Category="Change Component Size", EditAnywhere, NonTransactional, meta=(DisplayName="Resize Mode", ShowForTools="ResizeLandscape"))` — Determines how the new component size will be applied to the existing landscape geometry.
- L564 _private member_ `int32 ResizeLandscape_Original_QuadsPerSection;`
- L565 _private member_ `int32 ResizeLandscape_Original_SectionsPerComponent;`
- L566 _private member_ `FIntPoint ResizeLandscape_Original_ComponentCount;`
- L572 _private member_ `TWeakObjectPtr<UMaterialInterface> NewLandscape_Material;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Material", ShowForTools="NewLandscape"))` — Material initially applied to the landscape. Setting a material here exposes properties for setting up layer info based on the landscape blend nodes in the material.
- L576 _private member_ `int32 NewLandscape_QuadsPerSection;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Section Size", ShowForTools="NewLandscape"))` — The number of quads in a single landscape section. One section is the unit of LOD transition for landscape rendering.
- L580 _private member_ `int32 NewLandscape_SectionsPerComponent;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Sections Per Component", ShowForTools="NewLandscape"))` — The number of sections in a single landscape component. This along with the section size determines the size of each landscape component. A component is the base unit of rendering and culling.
- L584 _private member_ `FIntPoint NewLandscape_ComponentCount;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Number of Components", ShowForTools="NewLandscape"))` — The number of components in the X and Y direction, determining the overall size of the landscape.
- L586 _private member_ `static const FVector NewLandscape_DefaultLocation;`
- L590 _private member_ `FVector NewLandscape_Location;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Location", ShowForTools="NewLandscape"))` — The location of the new landscape
- L592 _private member_ `static const FRotator NewLandscape_DefaultRotation;`
- L596 _private member_ `FRotator NewLandscape_Rotation;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Rotation", ShowForTools="NewLandscape"))` — The rotation of the new landscape
- L598 _private member_ `static const FVector NewLandscape_DefaultScale;`
- L602 _private member_ `FVector NewLandscape_Scale;` — `UPROPERTY(Category="New Landscape", EditAnywhere, meta=(DisplayName="Scale", ShowForTools="NewLandscape"))` — The scale of the new landscape. This is the distance between each vertex on the landscape, defaulting to 100 units.
- L605 _private member_ `ELandscapeImportResult ImportLandscape_HeightmapImportResult;` — `UPROPERTY(Category="New Landscape", VisibleAnywhere, NonTransactional, meta=(ShowForTools="NewLandscape,ImportExport"))`
- L608 _private member_ `FText ImportLandscape_HeightmapErrorMessage;` — `UPROPERTY(Category="New Landscape", VisibleAnywhere, NonTransactional, meta=(ShowForTools="NewLandscape,ImportExport"))`
- L612 _private member_ `FString ImportLandscape_HeightmapFilename;` — `UPROPERTY(Category="New Landscape", EditAnywhere, NonTransactional, meta=(DisplayName="Heightmap File", ShowForTools="NewLandscape,ImportExport"))` — Specify a height map file in 16-bit RAW or PNG format
- L614 _private member_ `uint32 ImportLandscape_Width;` — `UPROPERTY(NonTransactional)`
- L616 _private member_ `uint32 ImportLandscape_Height;` — `UPROPERTY(NonTransactional)`
- L619 _private member_ `FString HeightmapExportFilename;` — `UPROPERTY(Category="Import / Export", EditAnywhere, NonTransactional, meta=(DisplayName="Heightmap File", ShowForTools="ImportExport"))`
- L622 _private member_ `FIntPoint ImportLandscape_GizmoLocalPosition;` — `UPROPERTY(NonTransactional)`
- L626 _private member_ `ELandscapeImportTransformType ImportType;` — `UPROPERTY(Category = "Import / Export", EditAnywhere, NonTransactional, meta =(ShowForTools = "ImportExport"))` — Describes the transform that should be applied to the import data
- L629 _private member_ `bool bHeightmapSelected = false;` — `UPROPERTY(NonTransactional)`
- L632 _private member_ `bool bExportEditLayer = true;` — `UPROPERTY(Category = "Import / Export", EditAnywhere, NonTransactional, meta = (DisplayName="Export Selected Edit Layer", ShowForTools = "ImportExport", ToolTip="When true exports the selected edit layer, if false exports the blended result"))`
- L635 _private member_ `bool bExportSingleFile = false;` — `UPROPERTY(Category = "Import / Export", EditAnywhere, NonTransactional, meta = (ShowForTools = "ImportExport", ToolTip = "(World Partition only) When true, exports the landscape as a single file, if false exports each grid tile individually."))`
- L638 _private member_ `ELandscapeImportExportMode ImportExportMode = ELandscapeImportExportMode::LoadedOnly;` — `UPROPERTY(Category = "Import / Export", EditAnywhere, NonTransactional, meta = (ShowForTools = "ImportExport"))`
- L641 _private member_ `FLandscapeImportDescriptor HeightmapImportDescriptor;` — `UPROPERTY(NonTransactional)`
- L644 _private member_ `int32 HeightmapImportDescriptorIndex;` — `UPROPERTY(NonTransactional)`
- L647 _private member_ `TArray<uint16> ImportLandscape_Data;` — `UPROPERTY(NonTransactional)`
- L651 _public member_ `bool bCanHaveLayersContent_DEPRECATED = true;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")` — `UPROPERTY(NonTransactional)`
- L654 _public member_ `bool bFlipYAxis = false;` — `UPROPERTY(Category = "New Landscape", EditAnywhere, NonTransactional, meta = (DisplayName = "Flip Y Axis", ToolTip = "Whether to flip Y coordinate of imported files.", ShowForTools = "NewLandscape,ImportExport"))`
- L657 _public member_ `uint32 WorldPartitionGridSize = 2;` — `UPROPERTY(Category = "New Landscape", EditAnywhere, NonTransactional, meta = (DisplayName= "World Partition Grid Size", ToolTip="Number of components per landscape streaming proxies per axis", ShowForTools="NewLandscape", ClampMin=1, ClampMax=16, UIMin=1, UIMax=16))`
- L660 _public member_ `uint32 WorldPartitionRegionSize = 16;` — `UPROPERTY(Category = "New Landscape", EditAnywhere, NonTransactional, meta = (DisplayName= "World Partition Region Size", ToolTip="Number of components per Landscape World Partition Region per axis.", ShowForTools="NewLandscape", ClampMin=4, ClampMax=64, UIMin=4, UIMax=64))`
- L664 _public member_ `ELandscapeImportAlphamapType ImportLandscape_AlphamapType;` — `UPROPERTY(Category="New Landscape", EditAnywhere, NonTransactional, meta=(DisplayName="Layer Alphamap Type", ShowForTools="NewLandscape,ImportExport"))` — Whether the imported alpha maps are to be interpreted as "layered" or "additive" (UE uses additive internally)
- L668 _public member_ `TArray<FLandscapeImportLayer> ImportLandscape_Layers;` — `UPROPERTY(Category="New Landscape", EditAnywhere, NonTransactional, EditFixedSize, meta=(DisplayName="Layers", ShowForTools="ImportExport"))` — The landscape layers that will be created via Import tab. Only layer names referenced in the material assigned above are shown here. Modify the material to add more layers.
- L672 _public member_ `TArray<FLandscapeImportLayer> NewLandscape_Layers;` — `UPROPERTY(Category="New Landscape", EditAnywhere, NonTransactional, EditFixedSize, meta=(DisplayName="Layers", ShowForTools="NewLandscape"))` — The landscape layers that will be created via New tab. Only layer names referenced in the material assigned above are shown here. Modify the material to add more layers.
- L678 _public member_ `float BrushRadius;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Brush Size", ShowForBrushes="BrushSet_Circle,BrushSet_Alpha,BrushSet_Pattern", ShowForTargetTypes = "Heightmap,Visibility", ClampMin="1", ClampMax="65536", UIMin="1", UIMax="8192", SliderExponent="3", MaxFractionalDigits="2", ToolTip = "Radius of the sculpt editing brush. The maximum slider/clamp value can be set with the BrushSizeUIMax/BrushSizeClampMax values in the Landscape project settings."))` — The radius of the sculpt brush, in unreal units
- L682 _public member_ `float PaintBrushRadius;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Brush Size", ShowForBrushes="BrushSet_Circle,BrushSet_Alpha,BrushSet_Pattern", ShowForTargetTypes = "Weightmap", ClampMin="1", ClampMax="65536", UIMin="1", UIMax="8192", SliderExponent="3", ToolTip = "Radius of the paint editing brush. The maximum slider/clamp value can be set with the BrushSizeUIMax/BrushSizeClampMax values in the Landscape project settings."))` — The radius of the paint brush, in unreal units
- L686 _public member_ `float BrushFalloff;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Brush Falloff", ShowForBrushes="BrushSet_Circle,BrushSet_Gizmo,BrushSet_Pattern", ShowForTargetTypes = "Heightmap,Visibility", ClampMin="0", ClampMax="1", UIMin = "0", UIMax = "1"))` — The falloff at the edge of the sculpt brush, as a fraction of the brush's size. 0 = no falloff, 1 = all falloff
- L690 _public member_ `float PaintBrushFalloff;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Brush Falloff", ShowForBrushes="BrushSet_Circle,BrushSet_Gizmo,BrushSet_Pattern", ShowForTargetTypes = "Weightmap", ClampMin="0", ClampMax="1", UIMin = "0", UIMax = "1"))` — The falloff at the edge of the paint brush, as a fraction of the brush's size. 0 = no falloff, 1 = all falloff
- L694 _public member_ `bool bUseClayBrush;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(ShowForTools="Sculpt", ShowForBrushes="BrushSet_Circle,BrushSet_Alpha,BrushSet_Pattern"))` — Selects the Clay Brush painting mode
- L698 _public member_ `bool bApplyWithoutMovingSculpt;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName = "Apply Without Moving", ShowForTargetTypes = "Heightmap", ShowForTools = "Sculpt,Erase,Smooth,Flatten,Erosion,HydraErosion,Noise,Mask,CopyPaste", ShowForBrushes = "BrushSet_Circle,BrushSet_Alpha,BrushSet_Gizmo,BrushSet_Pattern,BrushSet_Component"))` — Apply brush continuously while held stationary, after a small delay
- L702 _public member_ `bool bApplyWithoutMovingPaint;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName = "Apply Without Moving", ShowForTargetTypes = "Weightmap", ShowForTools = "Paint,Smooth,Flatten,Noise,Mask", ShowForBrushes = "BrushSet_Circle,BrushSet_Alpha,BrushSet_Pattern,BrushSet_Component"))` — Apply brush continuously while held stationary, after a small delay
- L708 _public member_ `float AlphaBrushScale;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture Scale", ShowForBrushes="BrushSet_Pattern", ClampMin="0.005", ClampMax="5", SliderExponent="3"))` — Scale of the brush texture. A scale of 1.000 maps the brush texture to the landscape at a 1 pixel = 1 vertex size
- L712 _public member_ `bool bAlphaBrushAutoRotate;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta = (DisplayName = "Auto-Rotate", ShowForBrushes = "BrushSet_Alpha"))` — Rotate brush to follow mouse
- L716 _public member_ `float AlphaBrushRotation;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture Rotation", ShowForBrushes="BrushSet_Alpha,BrushSet_Pattern", ClampMin="-360", ClampMax="360", UIMin="-180", UIMax="180"))` — Rotates the brush mask texture
- L720 _public member_ `float AlphaBrushPanU;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture Pan U", ShowForBrushes="BrushSet_Pattern", ClampMin="0", ClampMax="1"))` — Horizontally offsets the brush mask texture
- L724 _public member_ `float AlphaBrushPanV;` — `UPROPERTY(Category="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture Pan V", ShowForBrushes="BrushSet_Pattern", ClampMin="0", ClampMax="1"))` — Vertically offsets the brush mask texture
- L728 _public member_ `bool bUseWorldSpacePatternBrush;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta = (DisplayName = "Use World-Space", ShowForBrushes = "BrushSet_Pattern"))` — Tile the pattern in world space (this only takes scale and position into account, not rotation)
- L731 _public member_ `FLandscapePatternBrushWorldSpaceSettings WorldSpacePatternBrushSettings;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta = (DisplayName = "World-Space Settings", ShowForBrushes = "BrushSet_Pattern", EditCondition = "bUseWorldSpacePatternBrush"))`
- L735 _public member_ `TObjectPtr<UTexture2D> AlphaTexture;` — `UPROPERTY(Category ="Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture", ShowForBrushes="BrushSet_Alpha,BrushSet_Pattern"))` — Mask texture to use
- L739 _public member_ `ELandscapeTextureColorChannel AlphaTextureChannel;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Texture Channel", ShowForBrushes="BrushSet_Alpha,BrushSet_Pattern"))` — Channel of Mask Texture to use
- L742 _public member_ `int32 AlphaTextureSizeX;` — `UPROPERTY(NonTransactional)`
- L744 _public member_ `int32 AlphaTextureSizeY;` — `UPROPERTY(NonTransactional)`
- L746 _public member_ `TArray<uint8> AlphaTextureData;` — `UPROPERTY(NonTransactional)`
- L752 _public member_ `int32 BrushComponentSize;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta=(DisplayName="Brush Size", ShowForBrushes="BrushSet_Component", ClampMin="1", ClampMax="128", UIMin="1", UIMax="64", SliderExponent="3"))` — Number of components X/Y to affect at once. 1 means 1x1, 2 means 2x2, etc
- L755 _public member_ `bool bBrushComponentIncludeBorder = true;` — `UPROPERTY(Category = "Brush Settings", EditAnywhere, NonTransactional, meta = (DisplayName = "Include Border", ShowForBrushes = "BrushSet_Component", ShowForTools = "Paint,Sculpt", ToolTip = "When true, the brush will affect all pixels within the component, including those on the border, which means neightboring components (which share a line/row with their neighbor) will be affected as well"))`
- L766 _public member_ `ELandscapeLayerPaintingRestriction PaintingRestriction;` — `UPROPERTY(Category = "Target Layers", EditAnywhere, NonTransactional, meta=(ShowForTargetTypes="Weightmap,Visibility"))` — Limits painting to only the components that already have the selected layer. Use the '=' key and activate the landscape brush to add the selected layer to the painted components' allow list. Use the '-' key and activate the landscape brush to remove the selected layer from the painted components' allow list.
- L775 _public member_ `ELandscapeWeightBlendPaintMode WeightBlendedTargetLayerPaintMode = ELandscapeWeightBlendPaintMode::ExclusiveRequiresNoCtrl;` — `UPROPERTY(Category = "Target Layers", EditAnywhere, NonTransactional, meta = (DisplayName = "Exclusive Paint Mode", ShowForTools="Paint", ShowForTargetTypes = "Weightmap"))` — Defines how to activate the Exclusive Paint mode for weight-blended target layers. Exclusive Paint mode allows all weight-blended target layers from the same blend group to be painted in the same brush stroke. The selected target layer is painted while the unselected ones are "inversely" painted (erased). This allows the painted target layer to "override" the other ones instead of being merely being "blended" with them. It therefore (destructively) removes the weight from the other target layers.
- L778 _public member_ `FLandscapeTargetLayerAssetFilePath TargetLayerAssetFilePath;` — `UPROPERTY(Category = "Target Layers", EditAnywhere, NonTransactional, meta = (ShowForTargetTypes = "Weightmap"))`
- L782 _public member_ `FString TargetLayersFilterString;` — `UPROPERTY(Transient)` — This allows to hide layer names that do not match the filter
- L786 _public member_ `ELandscapeLayerDisplayMode TargetDisplayOrder;` — `UPROPERTY(Category = "Target Layers", EditAnywhere)` — Display order of the targets
- L789 _public member_ `bool bTargetDisplayOrdersAscending;` — `UPROPERTY(Category = "Target Layers", EditAnywhere)`
- L793 _public member_ `bool ShowUnusedLayers;` — `UPROPERTY(Category = "Target Layers", EditAnywhere)` — Show layers that are not currently being painted anywhere
- L797 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L801 _public prototype_ `void Load();`
- L802 _public prototype_ `void Save();`
- L805 _public prototype_ `void SetbUseSelectedRegion(bool InbUseSelectedRegion);` — Region
- L806 _public prototype_ `void SetbUseNegativeMask(bool InbUseNegativeMask);`
- L809 _public prototype_ `void SetPasteMode(ELandscapeToolPasteMode InPasteMode);` — Copy/Paste
- L812 _public prototype_ `void SetAlphaTexture(UTexture2D* InTexture, ELandscapeTextureColorChannel InTextureChannel);` — Alpha/Pattern Brush
- L813 _public prototype_ `bool HasValidAlphaTextureData() const;`
- L816 _public member_ `FString LastImportPath;` — New Landscape
- L818 _public function_ `const TArray<uint16>& GetImportLandscapeData() const`
- L819 _public function_ `void ClearImportLandscapeData()`
- L820 _public prototype_ `void ChooseBestComponentSizeForImport();`
- L821 _public prototype_ `void ImportLandscapeData();`
- L822 _public prototype_ `void RefreshImportLayersList(bool bRefreshFromTarget = false, bool bRegenerateThumbnails = false);`
- L823 _public prototype_ `void AutoFillTargetLayers(const FString& DefaultTargetLayerAssetPath, const bool bCreateAssetForEmptyLayers);`
- L824 _public prototype_ `ELandscapeImportResult CreateImportLayersInfo(TArray<FLandscapeImportLayerInfo>& OutImportLayerInfos);`
- L825 _public prototype_ `ELandscapeImportResult CreateNewLayersInfo(TArray<FLandscapeImportLayerInfo>& OutNewLayerInfos);`
- L826 _public prototype_ `void InitializeDefaultHeightData(TArray<uint16>& OutData);`
- L827 _public prototype_ `void ExpandImportData(TArray<uint16>& OutHeightData, TArray<FLandscapeImportLayerInfo>& OutImportLayerInfos);`
- L828 _public prototype_ `void UpdateComponentLayerAllowList();`
- L829 _public prototype_ `bool UseSingleFileImport() const;`
- L830 _public prototype_ `void OnChangeImportLandscapeResolution(int32 DescriptorIndex);`
- L831 _public function_ `void OnImportHeightmapFilenameChanged()`
- L832 _public prototype_ `void RefreshImports();`
- L833 _public function_ `void OnImportWeightmapFilenameChanged()`
- L834 _public prototype_ `void RefreshLayerImports();`
- L835 _public prototype_ `void RefreshLayerImport(FLandscapeImportLayer& ImportLayer);`
- L837 _public function_ `int32 ClampLandscapeSize(int32 InComponentsCount) const`
- L843 _public function_ `int32 CalcComponentsCount(int32 InResolution) const`
- L848 _public function_ `void NewLandscape_ClampSize()`
- L854 _public function_ `void UpdateComponentCount()`
- L882 _public prototype_ `void SetGizmoSnapMode(ELandscapeGizmoSnapType SnapMode);`
- L884 _public function_ `void SetParent(FEdModeLandscape* LandscapeParent)`
- L889 _public prototype_ `void UpdateTargetLayerDisplayOrder();`
- L891 _public prototype_ `float GetCurrentToolStrength() const;`
- L892 _public prototype_ `void SetCurrentToolStrength(float NewToolStrength);`
- L894 _public prototype_ `float GetCurrentToolBrushRadius() const;`
- L895 _public prototype_ `void SetCurrentToolBrushRadius(float NewBrushStrength);`
- L897 _public prototype_ `float GetCurrentToolBrushFalloff() const;`
- L898 _public prototype_ `void SetCurrentToolBrushFalloff(float NewBrushFalloff);`
- L900 _public prototype_ `float GetFlattenTarget(bool bInReturnPreviewValueIfActive) const;`
- L904 _private prototype_ `bool IsWeightmapTarget() const;`
- L906 _private prototype_ `static bool LoadAlphaTextureSourceData(UTexture2D* InTexture, TArray<uint8>& OutSourceData, int32& OutSourceDataSizeX, int32& OutSourceDataSizeY, ELandscapeTextureColorChannel& InOutTextureChannel);`

#### Free symbols / members of external scopes

- L85 _function_ `inline float NoiseModeConversion(ELandscapeToolNoiseMode Mode, float NoiseAmount, float OriginalValue)`

### `Source/Editor/LandscapeEditor/Public/LandscapeEditorUtils.h` (Public)


#### Free symbols / members of external scopes

- L14 _typedef_ `using FEditLayerCategoryToEntryMap = TMap<FName, FEditLayerMenuBlock>;`
- L16 _namespace_ `namespace LandscapeEditorUtils`
- L18 _prototype_ `bool SetHeightmapData(ALandscapeProxy* Landscape, const TArray<uint16>& Data);` (scope `LandscapeEditorUtils`)
- L19 _prototype_ `bool SetWeightmapData(ALandscapeProxy* Landscape, ULandscapeLayerInfoObject* LayerObject, const TArray<uint8>& Data);` (scope `LandscapeEditorUtils`)
- L21 _prototype_ `int32 GetMaxSizeInComponents();` (scope `LandscapeEditorUtils`)
- L22 _prototype_ `TOptional<FString> GetImportExportFilename(const FString& InDialogTitle, const FString& InStartPath, const FString& InDialogTypeString, bool bInImporting);` (scope `LandscapeEditorUtils`)
- L25 _function_ `template<typename T> void SaveObjects(TArrayView<T*> InObjects)` (scope `LandscapeEditorUtils`)
- L28 _function_ `Algo::Transform(InObjects, Packages, [](UObject* InObject) { return InObject->GetPackage(); });` (scope `LandscapeEditorUtils::SaveObjects`)
- L32 _prototype_ `void SaveLandscapeProxies(UWorld* InWorld, TArrayView<ALandscapeProxy*> Proxies);` (scope `LandscapeEditorUtils`)
- L34 _prototype_ `TArray<FAssetData> GetLandscapeTargetLayerInfoAssets();` (scope `LandscapeEditorUtils`)
- L35 _prototype_ `TOptional<FAssetData> FindLandscapeTargetLayerInfoAsset(const FName& LayerName, const FString& TargetLayerAssetPackagePath);` (scope `LandscapeEditorUtils`)
- L38 _prototype_ `void BuildContextMenuFromCategoryEntryMap(const FEditLayerCategoryToEntryMap& InMap, FMenuBuilder& OutMenuBuilder);` (scope `LandscapeEditorUtils`) — Edit layer context menu customization

### `Source/Editor/LandscapeEditor/Public/LandscapeFileFormatInterface.h` (Public)


#### struct `FLandscapeFileTypeInfo`  
`struct FLandscapeFileTypeInfo`  
_L13-24_
- L16 _public member_ `FText Description;` — Description of file type for the file selector
- L19 _public member_ `TArray<FString, TInlineAllocator<2>> Extensions;` — Extensions for this type, with leading dot, e.g. ".png"
- L23 _public member_ `bool bSupportsExport = false;` — Whether this file type supports exporting from the editor back to file (All file types must support *importing*, but exporting is optional)

#### enum `ELandscapeImportResult`  
`enum class ELandscapeImportResult : uint8`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `Success = 0`
- L30 _public enumerator_ `Warning`
- L31 _public enumerator_ `Error`

#### struct `FLandscapeFileResolution`  
`struct FLandscapeFileResolution`  
_L35-47_
- reflection: `USTRUCT()`
- L39 _public function_ `FLandscapeFileResolution()`
- L40 _public function_ `FLandscapeFileResolution(uint32 InWidth, uint32 InHeight) : Width(InWidth), Height(InHeight)`
- L43 _public member_ `uint32 Width = 0;` — `UPROPERTY()`
- L46 _public member_ `uint32 Height = 0;` — `UPROPERTY()`

#### struct `FLandscapeFileInfo`  
`struct FLandscapeFileInfo`  
_L59-73_
- L62 _public member_ `ELandscapeImportResult ResultCode = ELandscapeImportResult::Success;` — Whether the the file is usable or has errors/warnings
- L65 _public member_ `FText ErrorMessage;` — Message to show as the warning/error result
- L68 _public member_ `TArray<FLandscapeFileResolution> PossibleResolutions;` — Normally contains a single resolution, but .raw is awful
- L72 _public member_ `TOptional<FVector> DataScale;` — The inherent scale of the data format, if it has one, in centimeters The default for data with no inherent scale is 100,100,0.78125 (100.0/128, shown as 100 in the editor UI)

#### struct `FLandscapeImportData`  
`template< class T > struct FLandscapeImportData`  
_L76-86_
- L79 _public member_ `ELandscapeImportResult ResultCode = ELandscapeImportResult::Success;` — Whether the import data is usable or has errors/warnings
- L82 _public member_ `FText ErrorMessage;` — Message to show as the warning/error result
- L85 _public member_ `TArray<T> Data;` — The Data

#### class `ILandscapeFileFormat`  
`template< class T > class ILandscapeFileFormat`  
_L96-146_
- desc: Interface
- L102 _public prototype_ `virtual const FLandscapeFileTypeInfo& GetInfo() const = 0;` — Gets info about this format @return information about the file types supported by this file format plugin
- L111 _public prototype_ `virtual FLandscapeFileInfo Validate(const TCHAR* Filename, FName LayerName) const = 0;` — Validate a file for Import Gives the file format the opportunity to reject a file or return warnings as well as return information about the file for the import UI (e.g. resolution and scale) @param Filename path to the file to validate for import @param LayerName name of layer that is being imported (in case of Heightmap this will be NAME_None) @return information about the file and (optional) error message
- L113 _public function_ `virtual FLandscapeFileInfo Validate(const TCHAR* Filename) const`
- L121 _public prototype_ `virtual FLandscapeImportData<T> Import(const TCHAR* Filename, FName LayerName, FLandscapeFileResolution ExpectedResolution) const = 0;` — Import a file @param Filename path to the file to import @param LayerName name of layer being imported (in case of Heightmap this will be NAME_None) @param ExpectedResolution resolution selected in the import UI (mostly for the benefit of .raw) @return imported data and (optional) error message
- L123 _public function_ `virtual FLandscapeImportData<T> Import(const TCHAR* Filename, FLandscapeFileResolution ExpectedResolution) const`
- L132 _public function_ `virtual void Export(const TCHAR* Filename, FName LayerName, TArrayView<const T> Data, FLandscapeFileResolution DataResolution, FVector Scale) const` — Export a file (if supported) @param Filename path to the file to export to @param LayerName name of layer being exported (in case of Heightmap this will be NAME_None) @param Data raw data to export @param DataResolution resolution of Data @param Scale scale of the landscape data, in centimeters
- L137 _public function_ `virtual void Export(const TCHAR* Filename, TArrayView<const T> Data, FLandscapeFileResolution DataResolution, FVector Scale)`
- L145 _public prototype_ `virtual ~ILandscapeFileFormat() = default;` — Note: Even though this is an interface class we need a virtual destructor as derived objects are deleted via a pointer to this interface

#### Free symbols / members of external scopes

- L49 _function_ `FORCEINLINE bool operator==(const FLandscapeFileResolution& Lhs, const FLandscapeFileResolution& Rhs)`
- L54 _function_ `FORCEINLINE bool operator!=(const FLandscapeFileResolution& Lhs, const FLandscapeFileResolution& Rhs)`
- L88 _typedef_ `using FLandscapeHeightmapImportData = FLandscapeImportData<uint16>;`
- L89 _typedef_ `using FLandscapeWeightmapImportData = FLandscapeImportData<uint8>;`
- L91 _typedef_ `using FLandscapeHeightmapInfo = FLandscapeFileInfo;`
- L92 _typedef_ `using FLandscapeWeightmapInfo = FLandscapeFileInfo;`
- L148 _typedef_ `using ILandscapeHeightmapFileFormat = ILandscapeFileFormat<uint16>;`
- L149 _typedef_ `using ILandscapeWeightmapFileFormat = ILandscapeFileFormat<uint8>;`

### `Source/Editor/LandscapeEditor/Public/LandscapeImportHelper.h` (Public)


#### struct `FLandscapeImportFileDescriptor`  
`struct FLandscapeImportFileDescriptor`  
_L15-31_
- reflection: `USTRUCT()`
- L19 _public function_ `FLandscapeImportFileDescriptor(const FString& InFilePath, const FIntPoint& InCoord) : Coord(InCoord), FilePath(InFilePath)`
- L22 _public function_ `FLandscapeImportFileDescriptor() : Coord(EForceInit::ForceInit)`
- L27 _public member_ `FIntPoint Coord;` — `UPROPERTY()` — Which tile does that descriptor represent
- L30 _public member_ `FString FilePath;` — `UPROPERTY()` — File path

#### struct `FLandscapeImportResolution`  
`struct FLandscapeImportResolution`  
_L34-46_
- reflection: `USTRUCT()`
- L38 _public function_ `FLandscapeImportResolution(uint32 InWidth, uint32 InHeight) : Width(InWidth), Height(InHeight)`
- L40 _public function_ `FLandscapeImportResolution()`
- L43 _public member_ `uint32 Width = 0;` — `UPROPERTY()`
- L45 _public member_ `uint32 Height = 0;` — `UPROPERTY()`

#### enum `ELandscapeImportTransformType`  
`enum class ELandscapeImportTransformType : int8`  
_L49-57_
- reflection: `UENUM()`
- L52 _public enumerator_ `None UMETA(DisplayName="Original", ToolTip="Import the data at the gizmo location in the original size")`
- L53 _public enumerator_ `ExpandOffset UMETA(DisplayName="Expand", ToolTip="Import the data at the gizmo location and expand the data to fill the landscape")`
- L54 _public enumerator_ `ExpandCentered UMETA(Hidden)`
- L55 _public enumerator_ `Resample UMETA(ToolTip="Resample import data to fit landscape")`
- L56 _public enumerator_ `Subregion UMETA(ToolTip="Import sub-region of the image to landscape")`

#### struct `FLandscapeImportDescriptor`  
`struct FLandscapeImportDescriptor`  
_L70-110_
- reflection: `USTRUCT()`
- L74 _public function_ `FLandscapeImportDescriptor() : Scale(100, 100, 100)`
- L77 _public function_ `void Reset()`
- L85 _public function_ `int32 FindDescriptorIndex(int32 ImportWidth, int32 ImportHeight)`
- L100 _public member_ `TArray<FLandscapeImportResolution> ImportResolutions;` — `UPROPERTY()` — Landscape Import Resolution based on File Coords + Resolutions
- L103 _public member_ `TArray<FLandscapeFileResolution> FileResolutions;` — `UPROPERTY()` — Single File Resolutions
- L106 _public member_ `TArray<FLandscapeImportFileDescriptor> FileDescriptors;` — `UPROPERTY()` — Files contributing to this descriptor
- L109 _public member_ `FVector Scale;` — `UPROPERTY()` — Scale of Import data

#### class `FLandscapeImportHelper`  
`class FLandscapeImportHelper`  
_L112-178_
- L122 _public prototype_ `static ELandscapeImportResult GetHeightmapImportDescriptor(const FString& FilePath, bool bSingleFile, bool bFlipYAxis, FLandscapeImportDescriptor& OutImportDescriptor, FText& OutMessage);` — @param FilePath File to import when bSingleFile is true. @param bSingleFile If false FilePath will be used as the seed to find matching "_xA_yB" files in the same directory. @param OutImportDescriptor Descriptor output which contains all the information needed to call GetHeightmapImportData. @param OutMessage In case the result of the operation is  an error or warning, this will contain the reason. @return If the operation was a Success/Error/Warning.
- L132 _public prototype_ `static ELandscapeImportResult GetWeightmapImportDescriptor(const FString& FilePath, bool bSingleFile, bool bFlipYAxis, FName LayerName, FLandscapeImportDescriptor& OutImportDescriptor, FText& OutMessage);` — @param FilePath File to import when bSingleFile is true. @param bSingleFile If false FilePath will be used as the seed to find matching "_xA_yB" files in the same directory. @param LayerName Name of the Weightmap layer being imported. This can be used by the file formats. @param OutImportDescriptor Descriptor output which contains all the information needed to call GetHeightmapImportData. @param OutMessage In case the result of the operation is  an error or warning, this will contain the reason. @return If the operation was a Success/Error/Warning.
- L134 _public prototype_ `static ELandscapeImportResult GetHeightmapImportData(const FLandscapeImportDescriptor& ImportDescriptor, int32 DescriptorIndex, TArray<uint16>& OutData, FText& OutMessage);`
- L135 _public prototype_ `static ELandscapeImportResult GetWeightmapImportData(const FLandscapeImportDescriptor& ImportDescriptor, int32 DescriptorIndex, FName LayerName, TArray<uint8>& OutData, FText& OutMessage);`
- L137 _public prototype_ `static void TransformWeightmapImportData(const TArray<uint8>& InData, TArray<uint8>& OutData, const FLandscapeImportResolution& CurrentResolution, const FLandscapeImportResolution& RequiredResolution, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0,0));`
- L138 _public prototype_ `static void TransformHeightmapImportData(const TArray<uint16>& InData, TArray<uint16>& OutData, const FLandscapeImportResolution& CurrentResolution, const FLandscapeImportResolution& RequiredResolution, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0, 0));`
- L140 _public prototype_ `static void ChooseBestComponentSizeForImport(int32 Width, int32 Height, int32& InOutQuadsPerSection, int32& InOutSectionsPerComponent, FIntPoint& OutComponentCount);`
- L142 _public prototype_ `static bool ExtractCoordinates(const FString& BaseFilename, FIntPoint& OutCoord, FString& OutBaseFilePattern);`
- L143 _public prototype_ `static void GetMatchingFiles(const FString& FilePathPattern, TArray<FString>& OutFilePaths);`
- L147 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint16>, ELandscapeImportResult>::Type GetImportDescriptor(const FString& FilePath, bool bSingleFile, bool bFlipYAxis, FName LayerName, FLandscapeImportDescriptor& OutImportDescriptor, FText& OutMessage)`
- L153 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint16>, ELandscapeImportResult>::Type GetImportData(const FLandscapeImportDescriptor& ImportDescriptor, int32 DescriptorIndex, FName LayerName, TArray<T>& OutData, FText& OutMessage)`
- L158 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint16>, void>::Type TransformImportData(const TArray<T>& InData, TArray<T>& OutData, const FLandscapeImportResolution& CurrentResolution, const FLandscapeImportResolution& RequiredResolution, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0, 0))`
- L164 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint8>, ELandscapeImportResult>::Type GetImportDescriptor(const FString& FilePath, bool bSingleFile, bool bFlipYAxis, FName LayerName, FLandscapeImportDescriptor& OutImportDescriptor, FText& OutMessage)`
- L169 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint8>, ELandscapeImportResult>::Type GetImportData(const FLandscapeImportDescriptor& ImportDescriptor, int32 DescriptorIndex, FName LayerName, TArray<T>& OutData, FText& OutMessage)`
- L174 _public function_ `template<typename T> static typename TEnableIf<std::is_same_v<T, uint8>, void>::Type TransformImportData(const TArray<T>& InData, TArray<T>& OutData, const FLandscapeImportResolution& CurrentResolution, const FLandscapeImportResolution& RequiredResolution, ELandscapeImportTransformType TransformType = ELandscapeImportTransformType::ExpandCentered, FIntPoint Offset = FIntPoint(0, 0))`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LANDSCAPEEDITOR_API`
- L59 _function_ `FORCEINLINE bool operator==(const FLandscapeImportResolution& Lhs, const FLandscapeImportResolution& Rhs)`
- L64 _function_ `FORCEINLINE bool operator!=(const FLandscapeImportResolution& Lhs, const FLandscapeImportResolution& Rhs)`

### `Source/Editor/LandscapeEditor/Public/LandscapeToolInterface.h` (Public)


#### struct `FLandscapeToolInteractorPosition`  
`struct FLandscapeToolInteractorPosition`  
_L25-38_
- desc: FLandscapeToolMousePosition - Struct to store mouse positions since the last time we applied the brush
- L28 _public member_ `FVector2D Position = FVector2D::Zero();` — Stored in heightmap space.
- L29 _public member_ `bool bModifierPressed = false;`
- L30 _public member_ `bool bAlternateModifierPressed = false;`
- L32 _public function_ `FLandscapeToolInteractorPosition(FVector2D InPosition, const bool bInModifierPressed, const bool bInAlternateModifierPressed) : Position(InPosition) , bModifierPressed(bInModifierPressed) , bAlternateModifierPressed(bInAlternateModifierPressed)`

#### enum `ELandscapeBrushType`  
`enum class ELandscapeBrushType`  
_L40-47_
- L42 _public enumerator_ `Normal = 0`
- L43 _public enumerator_ `Alpha`
- L44 _public enumerator_ `Component`
- L45 _public enumerator_ `Gizmo`
- L46 _public enumerator_ `Splines`

#### class `FLandscapeBrushData`  
`class FLandscapeBrushData`  
_L49-99_
- L52 _protected member_ `FIntRect Bounds;`
- L53 _protected member_ `TArray<float> BrushAlpha;`
- L56 _public function_ `FLandscapeBrushData() : Bounds()`
- L61 _public function_ `FLandscapeBrushData(FIntRect InBounds) : Bounds(InBounds)`
- L67 _public function_ `FIntRect GetBounds() const`
- L73 _public function_ `void GetInclusiveBounds(int32& X1, int32& Y1, int32& X2, int32& Y2) const` — For compatibility with older landscape code that uses inclusive bounds in 4 int32s
- L81 _public function_ `float* GetDataPtr(FIntPoint Position)`
- L85 _public function_ `const float* GetDataPtr(FIntPoint Position) const`
- L90 _public function_ `FORCEINLINE explicit operator bool() const`
- L95 _public function_ `FORCEINLINE bool operator!() const`

#### class `FLandscapeBrush`  
`class FLandscapeBrush : public FGCObject`  
_L101-145_
- inherits: `FGCObject`
- L104 _public prototype_ `virtual void MouseMove(float LandscapeX, float LandscapeY) = 0;`
- L105 _public function_ `virtual TOptional<FVector2D> GetLastMousePosition() const`
- L106 _public prototype_ `virtual FLandscapeBrushData ApplyBrush(const TArray<FLandscapeToolInteractorPosition>& InteractorPositions) = 0;`
- L125 _public function_ `virtual FOverlapInfo GetOverlapInfo(const TArray<FLandscapeToolInteractorPosition>& InteractorPositions) const` — @return landscape overlap information about the components being overlapped by the tool interactor positions.
- L127 _public function_ `virtual TOptional<bool> InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent)`
- L128 _public function_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime)`
- L129 _public prototype_ `virtual void BeginStroke(float LandscapeX, float LandscapeY, class FLandscapeTool* CurrentTool);`
- L130 _public prototype_ `virtual void EndStroke();`
- L131 _public function_ `virtual void EnterBrush()`
- L132 _public function_ `virtual void LeaveBrush()`
- L133 _public prototype_ `virtual ~FLandscapeBrush() = default;`
- L134 _public function_ `virtual UMaterialInterface* GetBrushMaterial()`
- L135 _public prototype_ `virtual const TCHAR* GetBrushName() = 0;`
- L136 _public prototype_ `virtual FText GetDisplayName() = 0;`
- L137 _public function_ `virtual ELandscapeBrushType GetBrushType()`
- L140 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override` — FGCObject interface
- L141 _public function_ `virtual FString GetReferencerName() const override`

#### struct `FLandscapeBrush::FOverlapInfo`  
`struct FOverlapInfo`  
_L108-123_
- L110 _public function_ `FORCEINLINE explicit operator bool() const`
- L115 _public function_ `FORCEINLINE bool operator!() const`
- L120 _public member_ `FIntRect ExclusiveBounds;`
- L121 _public member_ `bool bOverlapsUnloadedComponents = false;`
- L122 _public member_ `TSet<ULandscapeComponent*> OverlappedLoadedComponents;`

#### struct `FLandscapeBrushSet`  
`struct FLandscapeBrushSet`  
_L147-166_
- L149 _public function_ `FLandscapeBrushSet(const TCHAR* InBrushSetName) : BrushSetName(InBrushSetName) , PreviousBrushIndex(0)`
- L155 _public member_ `const FName BrushSetName;`
- L156 _public member_ `TArray<FLandscapeBrush*> Brushes;`
- L157 _public member_ `int32 PreviousBrushIndex;`
- L159 _public function_ `virtual ~FLandscapeBrushSet()`

#### enum `ELandscapeToolTargetTypeMask::Type`  
`enum UE_DEPRECATED(5.7, "Use ELandscapeToolTargetTypeFlags instead.") Type : uint8`  
_L170-178_
- L172 _public enumerator_ `Heightmap = 1 << static_cast<uint8>(ELandscapeToolTargetType::Heightmap)`
- L173 _public enumerator_ `Weightmap = 1 << static_cast<uint8>(ELandscapeToolTargetType::Weightmap)`
- L174 _public enumerator_ `Visibility = 1 << static_cast<uint8>(ELandscapeToolTargetType::Visibility)`
- L176 _public enumerator_ `NA = 0`
- L177 _public enumerator_ `All = 0xFF`

#### struct `FLandscapeToolTarget`  
`struct FLandscapeToolTarget`  
_L193-214_
- L195 _public member_ `TWeakObjectPtr<ULandscapeInfo> LandscapeInfo;`
- L196 _public member_ `ELandscapeToolTargetType TargetType;`
- L199 _public member_ `TWeakObjectPtr<ULandscapeLayerInfoObject> LayerInfo;` — TODO [jonathan.bard] : eventually, will become multiple layers (multi-paint) : don't assume there will be a single one of these
- L200 _public member_ `FName LayerName;`
- L202 _public function_ `TArray<ULandscapeLayerInfoObject*> GetLayerInfos() const`
- L207 _public function_ `FLandscapeToolTarget() : LandscapeInfo() , TargetType(ELandscapeToolTargetType::Heightmap) , LayerInfo() , LayerName(NAME_None)`

#### enum `ELandscapeToolType`  
`enum class ELandscapeToolType`  
_L216-220_
- L218 _public enumerator_ `Normal = 0`
- L219 _public enumerator_ `Mask`

#### enum `ELandscapeTargetLayerActionType`  
`enum class ELandscapeTargetLayerActionType`  
_L223-228_
- desc: Describes the type of action that a landscape tool will perform on a given target layer
- L225 _public enumerator_ `None` — The target layer will not be affected by any action
- L226 _public enumerator_ `Normal` — The target layer will be affected by the action (e.g. the paint action by the Paint brush)
- L227 _public enumerator_ `Inverted` — The target layer will be inversely affected by the action (e.g. the inverse paint action by the Paint brush in exclusive mode)

#### class `FLandscapeTool`  
`class FLandscapeTool : public FGCObject`  
_L233-336_
- inherits: `FGCObject`
- desc: FLandscapeTool
- L236 _public function_ `virtual void EnterTool()`
- L237 _public function_ `virtual bool IsToolActive() const`
- L238 _public function_ `virtual void ExitTool()`
- L239 _public prototype_ `virtual bool BeginTool(FEditorViewportClient* ViewportClient, const FLandscapeToolTarget& Target, const FVector& InHitLocation) = 0;`
- L240 _public prototype_ `virtual void EndTool(FEditorViewportClient* ViewportClient) = 0;`
- L241 _public function_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime)`
- L242 _public function_ `virtual bool MouseEnter(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 MouseX, int32 MouseY)`
- L243 _public function_ `virtual bool MouseLeave(FEditorViewportClient* InViewportClient, FViewport* InViewport)`
- L244 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) = 0;`
- L245 _public function_ `virtual bool HandleClick(HHitProxy* HitProxy, const FViewportClick& Click)`
- L246 _public function_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent)`
- L247 _public function_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale)`
- L248 _public function_ `virtual bool GetCursor(EMouseCursor::Type& OutCursor) const`
- L251 _public function_ `virtual bool BeginTransform(const FGizmoState& InState)` — FEdMode: Called when a transform operation begins
- L254 _public function_ `virtual bool EndTransform(const FGizmoState& InState)` — FEdMode: Called when a transform operation ends
- L256 _public function_ `FLandscapeTool()`
- L257 _public prototype_ `virtual ~FLandscapeTool() = default;`
- L258 _public prototype_ `virtual const TCHAR* GetToolName() const = 0;`
- L259 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L260 _public prototype_ `virtual FText GetDisplayMessage() const = 0;`
- L261 _public prototype_ `virtual void SetEditRenderType();`
- L262 _public function_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)`
- L263 _public function_ `virtual bool HitTrace(const FVector& TraceStart, const FVector& TraceEnd, FVector& OutHitLocation)`
- L264 _public function_ `virtual bool UseSphereTrace() const`
- L265 _public function_ `virtual bool SupportsMask() const`
- L266 _public function_ `virtual bool OverrideSelection() const`
- L267 _public function_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const`
- L268 _public function_ `virtual bool UsesTransformWidget() const`
- L269 _public function_ `virtual EAxisList::Type GetWidgetAxisToDraw(UE::Widget::EWidgetMode InWidgetMode) const`
- L270 _public function_ `virtual bool AffectsEditLayers() const`
- L272 _public function_ `virtual bool OverrideWidgetLocation() const`
- L273 _public function_ `virtual bool OverrideWidgetRotation() const`
- L274 _public function_ `virtual FVector GetWidgetLocation() const`
- L275 _public function_ `virtual FMatrix GetWidgetRotation() const`
- L276 _public function_ `virtual bool DisallowMouseDeltaTracking() const`
- L279 _public function_ `virtual bool GetOverrideCursorVisibility(bool& bWantsOverride, bool& bHardwareCursorVisible, bool bSoftwareCursorVisible) const` — Get override cursor visibility settings
- L282 _public function_ `virtual bool PreConvertMouseMovement(FEditorViewportClient* InViewportClient)` — Called before mouse movement is converted to drag/rot
- L285 _public function_ `virtual bool PostConvertMouseMovement(FEditorViewportClient* InViewportClient)` — Called after mouse movement is converted to drag/rot
- L287 _public function_ `virtual void SetCanToolBeActivated(bool Value)`
- L288 _public function_ `virtual bool CanToolBeActivated() const`
- L290 _public function_ `virtual EEditAction::Type GetActionEditDuplicate()`
- L291 _public function_ `virtual EEditAction::Type GetActionEditDelete()`
- L292 _public function_ `virtual EEditAction::Type GetActionEditCut()`
- L293 _public function_ `virtual EEditAction::Type GetActionEditCopy()`
- L294 _public function_ `virtual EEditAction::Type GetActionEditPaste()`
- L295 _public function_ `virtual bool ProcessEditDuplicate()`
- L296 _public function_ `virtual bool ProcessEditDelete()`
- L297 _public function_ `virtual bool ProcessEditCut()`
- L298 _public function_ `virtual bool ProcessEditCopy()`
- L299 _public function_ `virtual bool ProcessEditPaste()`
- L302 _public function_ `virtual int32 GetToolActionResolutionDelta() const` — Returns the resolution difference when the Tool action is applied.
- L305 _public function_ `virtual void Process(int32 Index, int32 Arg)` — Functions which doesn't need Viewport data...
- L306 _public function_ `virtual ELandscapeToolType GetToolType() const`
- L312 _public function_ `virtual ELandscapeToolTargetType GetSupportedTargetType() const` — @return the type of target type that this tool supports. Some tools might support both heightmaps and weightmaps, for example, but they should be specialized to return only one type (e.g. FLandscapeToolSmooth, that is templated to either FHeightmapToolTarget (ELandscapeToolTargetType::Heightmap) or FWeightmapToolTarget (ELandscapeToolTargetType::Weightmap) That is the reason why we return ELandscapeToolTargetType here, rather than ELandscapeToolTargetTypeFlags
- L321 _public function_ `virtual ELandscapeTargetLayerActionType GetTargetLayerActionType(const ULandscapeLayerInfoObject* InLayerInfo, bool bInIsModifierPressed, bool bInIsAlternateModifierPressed) const` — Returns the type of action that this tool will perform on the target layer @param InLayerInfo - the target layer for which to return the action type @param bInIsModifierPressed indicates the status of the standard modifier key (Shift) : some tools might return a different action type depending on the modifier pressed @param bInIsAlternateModifierPressed indicates the status of the alternate modifier key (Ctrl) : some tools might return a different action type depending on the modifier pressed @return the action type
- L327 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override` — FGCObject interface
- L328 _public function_ `virtual FString GetReferencerName() const override`
- L334 _public member_ `int32 PreviousBrushIndex = INDEX_NONE;`
- L335 _public member_ `TArray<FName> ValidBrushes;`

#### Free symbols / members of external scopes

- L168 _namespace_ `namespace ELandscapeToolTargetTypeMask`
- L182 _function_ `inline ELandscapeToolTargetTypeMask::Type FromType(ELandscapeToolTargetType TargetType)` (scope `ELandscapeToolTargetTypeMask`) — `UE_DEPRECATED(5.7, "Use UE::Landscape::GetLandscapeToolTargetTypeAsFlags with ELandscapeToolTargetType instead.")`

### `Source/Editor/LandscapeEditor/Public/SLandscapeLayerListDialog.h` (Public)


#### class `SLandscapeLayerListDialog`  
`class SLandscapeLayerListDialog : public SCustomDialog`  
_L18-56_
- inherits: `SCustomDialog`
- desc: Displays a list of layers with drag + drop support for layer reordering outside of landscape mode. Can be directly constructed in editor code or can be constructed indirectly through ILandscapeEditorServices.
- L21 _public prototype_ `virtual ~SLandscapeLayerListDialog() = default;`
- L23 _public function_ `SLATE_BEGIN_ARGS( SLandscapeLayerListDialog )`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<ALandscape>& InLandscape);`
- L33 _public function_ `int32 GetInsertedLayerIndex() const`
- L37 _private prototype_ `void OnLayerListUpdated();` — Called when LayerList is changed to update WidgetLayerList and the dialog window.
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow( TSharedPtr<FWidgetLayerListItem> InListItem, const TSharedRef< STableViewBase >& InOwnerTableView ) const;` — Called when a new row is being generated. Converts FWidgetLayerListItem to ITableRow.
- L43 _private prototype_ `void OnComplete();` — Called when Complete button is pressed
- L46 _private member_ `TSharedPtr<SWidgetLayerListView> LayerListView;` — The list view of WidgetLayerList.
- L50 _private member_ `TArray<TSharedPtr<FWidgetLayerListItem>> WidgetLayerList;` — Array of FWidgetLayerListItem, which contains ULandscapeEditLayerBase* in addition to intermediate data. Note: This array is a UI reflection of LayerList but the order is the reverse order of LayerList
- L52 _private member_ `TWeakObjectPtr<ALandscape> Landscape;`
- L55 _private member_ `int InsertedLayerIndex = -1;` — Index of the layer which is being inserted into the layer stack

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef SListView<TSharedPtr<FWidgetLayerListItem> > SWidgetLayerListView;`
