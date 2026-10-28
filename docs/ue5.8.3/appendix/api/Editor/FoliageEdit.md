# Editor / FoliageEdit

- module root: `Source/Editor/FoliageEdit`
- headers: 24; symbols: 655
- symbol kinds: class=28, enum=3, enumerator=9, externvar=1, function=72, macro=1, member=125, namespace=5, prototype=394, struct=3, typedef=8, variable=6
- PrivateDependencyModuleNames: AssetTools, Core, CoreUObject, DataLayerEditor, DetailCustomizations, EditorFramework, EditorSubsystem, EditorWidgets, Engine, Foliage, InputCore, Landscape, LevelEditor, PropertyEditor, RenderCore, SceneOutliner, Slate, SlateCore, ToolWidgets, UnrealEd

### `Source/Editor/FoliageEdit/Private/ActorFactoryProceduralFoliage.h` (Private)


#### class `UActorFactoryProceduralFoliage`  
`class UActorFactoryProceduralFoliage : public UActorFactoryBoxVolume`  
_L19-29_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactoryBoxVolume`
- L24 _private prototype_ `virtual bool PreSpawnActor(UObject* Asset, FTransform& InOutLocation);`
- L25 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L26 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor) override;`
- L27 _private prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Source/Editor/FoliageEdit/Private/FoliageEdMode.h` (Private)


#### enum `EFoliagePaletteViewMode::Type`  
`enum Type`  
_L53-57_
- L55 _public enumerator_ `Thumbnail`
- L56 _public enumerator_ `Tree`

#### enum `EFoliageSingleInstantiationPlacementMode::Type`  
`enum class Type`  
_L63-68_
- L65 _public enumerator_ `All`
- L66 _public enumerator_ `CycleThrough`
- L67 _public enumerator_ `ModeCount`

#### struct `FFoliageUISettings`  
`struct FFoliageUISettings`  
_L74-217_
- desc: Current user settings in Foliage UI
- L76 _public prototype_ `void Load();`
- L77 _public prototype_ `void Save();`
- L80 _public function_ `void SetWindowSizePos(int32 NewX, int32 NewY, int32 NewWidth, int32 NewHeight)` — Window
- L81 _public function_ `void GetWindowSizePos(int32& OutX, int32& OutY, int32& OutWidth, int32& OutHeight)`
- L84 _public function_ `bool GetPaintToolSelected() const` — tool
- L85 _public function_ `void SetPaintToolSelected(bool InbPaintToolSelected)`
- L86 _public function_ `bool GetReapplyToolSelected() const`
- L87 _public function_ `void SetReapplyToolSelected(bool InbReapplyToolSelected)`
- L88 _public function_ `bool GetSelectToolSelected() const`
- L89 _public function_ `void SetSelectToolSelected(bool InbSelectToolSelected)`
- L90 _public function_ `bool GetLassoSelectToolSelected() const`
- L91 _public function_ `void SetLassoSelectToolSelected(bool InbLassoSelectToolSelected)`
- L92 _public function_ `bool GetPaintBucketToolSelected() const`
- L93 _public function_ `void SetPaintBucketToolSelected(bool InbPaintBucketToolSelected)`
- L94 _public function_ `bool GetReapplyPaintBucketToolSelected() const`
- L95 _public function_ `void SetReapplyPaintBucketToolSelected(bool InbReapplyPaintBucketToolSelected)`
- L96 _public function_ `bool GetEraseToolSelected() const`
- L97 _public function_ `void SetEraseToolSelected(bool InbEraseToolSelected)`
- L99 _public function_ `float GetRadius() const`
- L100 _public function_ `void SetRadius(float InRadius)`
- L101 _public function_ `float GetPaintDensity() const`
- L102 _public function_ `void SetPaintDensity(float InPaintDensity)`
- L103 _public function_ `float GetUnpaintDensity() const`
- L104 _public function_ `void SetUnpaintDensity(float InUnpaintDensity)`
- L105 _public function_ `bool GetFilterLandscape() const`
- L106 _public function_ `void SetFilterLandscape(bool InbFilterLandscape)`
- L107 _public function_ `bool GetFilterStaticMesh() const`
- L108 _public function_ `void SetFilterStaticMesh(bool InbFilterStaticMesh)`
- L109 _public function_ `bool GetFilterBSP() const`
- L110 _public function_ `void SetFilterBSP(bool InbFilterBSP)`
- L111 _public function_ `bool GetFilterFoliage() const`
- L112 _public function_ `void SetFilterFoliage(bool InbFilterFoliage)`
- L113 _public function_ `bool GetFilterTranslucent() const`
- L114 _public function_ `void SetFilterTranslucent(bool InbFilterTranslucent)`
- L116 _public function_ `bool IsInAnySingleInstantiationMode() const`
- L118 _public function_ `bool GetIsInSingleInstantiationMode() const`
- L119 _public function_ `void SetIsInSingleInstantiationMode(bool InIsInSingleInstantiationMode)`
- L121 _public function_ `bool GetIsInQuickSingleInstantiationMode() const`
- L122 _public function_ `void SetIsInQuickSingleInstantiationMode(bool InIsInQuickSingleInstantiationMode)`
- L124 _public function_ `bool IsInAnyEraseMode() const`
- L125 _public function_ `bool GetIsInQuickEraseMode() const`
- L126 _public function_ `void SetIsInQuickEraseMode(bool InIsInQuickEraseMode)`
- L128 _public function_ `EFoliageSingleInstantiationPlacementMode::Type GetSingleInstantiationPlacementMode() const`
- L129 _public function_ `void SetSingleInstantiationPlacementMode(EFoliageSingleInstantiationPlacementMode::Type InSingleInstantiationPlacementMode)`
- L131 _public function_ `int32 GetSingleInstantiationCycleThroughIndex() const`
- L132 _public function_ `void IncrementSingleInstantiationCycleThroughIndex()`
- L134 _public function_ `bool GetIsInSpawnInCurrentLevelMode() const`
- L135 _public function_ `void SetSpawnInCurrentLevelMode(bool InSpawnInCurrentLevelMode)`
- L137 _public function_ `bool GetShowPaletteItemDetails() const`
- L138 _public function_ `void SetShowPaletteItemDetails(bool InbShowPaletteItemDetails)`
- L139 _public function_ `bool GetShowPaletteItemTooltips() const`
- L140 _public function_ `void SetShowPaletteItemTooltips(bool InbShowPaletteItemTooltips)`
- L141 _public function_ `EFoliagePaletteViewMode::Type GetActivePaletteViewMode() const`
- L142 _public function_ `void SetActivePaletteViewMode(EFoliagePaletteViewMode::Type InActivePaletteViewMode)`
- L143 _public function_ `float GetPaletteThumbnailScale() const`
- L144 _public function_ `void SetPaletteThumbnailScale(float InThumbnailScale)`
- L146 _public function_ `FFoliageUISettings() : WindowX(-1) , WindowY(-1) , WindowWidth(284) , WindowHeight(400) , bPaintToolSelected(true) , bReapplyToolSelected(false) , bSelectToolSelected(false) , bLassoSelectToolSelected(false) , bPaintBucketToolSelected(false) , bReapplyPaintBucketToolSelected(false) , bEraseToolSelected(false) , bShowPaletteItemDetails(true) , bShowPaletteItemTooltips(true) , ActivePaletteViewMode(EFoliagePaletteViewMode::Thumbnail) , PaletteThumbnailScale(0.3f) , Radius(250.f) , PaintDensity(0.5f) , UnpaintDensity(0.f) , IsInSingleInstantiationMode(false) , IsInQuickSingleInstantiationMode(false) , IsInQuickEraseMode(false) , SingleInstantiationPlacementMode(EFoliageSingleInstantiationPlacementMode::Type::All) , SingleInstantiationCycleThroughIndex(0) , IsInSpawnInCurrentLevelMode(false) , bFilterLandscape(true) , bFilterStaticMesh(true) , bFilterBSP(true) , bFilterFoliage(false) , bFilterTranslucent(false)`
- L179 _public prototype_ `~FFoliageUISettings() = default;`
- L182 _private member_ `int32 WindowX;`
- L183 _private member_ `int32 WindowY;`
- L184 _private member_ `int32 WindowWidth;`
- L185 _private member_ `int32 WindowHeight;`
- L187 _private member_ `bool bPaintToolSelected;`
- L188 _private member_ `bool bReapplyToolSelected;`
- L189 _private member_ `bool bSelectToolSelected;`
- L190 _private member_ `bool bLassoSelectToolSelected;`
- L191 _private member_ `bool bPaintBucketToolSelected;`
- L192 _private member_ `bool bReapplyPaintBucketToolSelected;`
- L193 _private member_ `bool bEraseToolSelected;`
- L195 _private member_ `bool bShowPaletteItemDetails;`
- L196 _private member_ `bool bShowPaletteItemTooltips;`
- L197 _private member_ `EFoliagePaletteViewMode::Type ActivePaletteViewMode;`
- L198 _private member_ `float PaletteThumbnailScale;`
- L200 _private member_ `float Radius;`
- L201 _private member_ `float PaintDensity;`
- L202 _private member_ `float UnpaintDensity;`
- L204 _private member_ `bool IsInSingleInstantiationMode;`
- L205 _private member_ `bool IsInQuickSingleInstantiationMode;`
- L206 _private member_ `bool IsInQuickEraseMode;`
- L207 _private member_ `EFoliageSingleInstantiationPlacementMode::Type SingleInstantiationPlacementMode;`
- L208 _private member_ `int32 SingleInstantiationCycleThroughIndex;`
- L209 _private member_ `bool IsInSpawnInCurrentLevelMode;`
- L212 _public member_ `bool bFilterLandscape;`
- L213 _public member_ `bool bFilterStaticMesh;`
- L214 _public member_ `bool bFilterBSP;`
- L215 _public member_ `bool bFilterFoliage;`
- L216 _public member_ `bool bFilterTranslucent;`

#### struct `FFoliageMeshUIInfo`  
`struct FFoliageMeshUIInfo`  
_L220-234_
- L222 _public member_ `TObjectPtr<UFoliageType> Settings;`
- L223 _public member_ `int32 InstanceCountCurrentLevel;`
- L224 _public member_ `int32 InstanceCountTotal;`
- L226 _public prototype_ `FFoliageMeshUIInfo(UFoliageType* InSettings);`
- L228 _public function_ `bool operator == (const FFoliageMeshUIInfo& Other) const`
- L233 _public prototype_ `FText GetNameText() const;`

#### class `FMeshInfoSnapshot`  
`class FMeshInfoSnapshot`  
_L239-271_
- desc: Snapshot of current MeshInfo state. Created at start of a brush stroke to store the existing instance info.
- L241 _private member_ `FFoliageInstanceHash Hash;`
- L242 _private member_ `TArray<FVector> Locations;`
- L244 _public function_ `FMeshInfoSnapshot(FFoliageInfo* MeshInfo) : Hash(*MeshInfo->InstanceHash)`
- L256 _public function_ `int32 CountInstancesInsideSphere(const FSphere& Sphere) const`

#### struct `FFoliagePaintingGeometryFilter`  
`struct FFoliagePaintingGeometryFilter`  
_L276-303_
- desc: Painting filtering options
- L278 _public member_ `bool bAllowLandscape;`
- L279 _public member_ `bool bAllowStaticMesh;`
- L280 _public member_ `bool bAllowBSP;`
- L281 _public member_ `bool bAllowFoliage;`
- L282 _public member_ `bool bAllowTranslucent;`
- L284 _public function_ `FFoliagePaintingGeometryFilter(const FFoliageUISettings& InUISettings) : bAllowLandscape(InUISettings.bFilterLandscape) , bAllowStaticMesh(InUISettings.bFilterStaticMesh) , bAllowBSP(InUISettings.bFilterBSP) , bAllowFoliage(InUISettings.bFilterFoliage) , bAllowTranslucent(InUISettings.bFilterTranslucent)`
- L293 _public function_ `FFoliagePaintingGeometryFilter() : bAllowLandscape(false) , bAllowStaticMesh(false) , bAllowBSP(false) , bAllowFoliage(false) , bAllowTranslucent(false)`
- L302 _public prototype_ `bool operator() (const UPrimitiveComponent* Component) const;`

#### enum `EFoliageEditingState`  
`enum class EFoliageEditingState : uint8`  
_L309-315_
- L311 _public enumerator_ `Unknown`
- L312 _public enumerator_ `Enabled`
- L313 _public enumerator_ `PIEWorld`
- L314 _public enumerator_ `SIEWorld`

#### class `FEdModeFoliage`  
`class FEdModeFoliage : public FEdMode`  
_L319-738_
- inherits: `FEdMode`
- desc: Foliage editor mode
- L322 _public member_ `FFoliageUISettings UISettings;`
- L325 _public member_ `TSharedPtr<FUICommandList> UICommandList;` — Command list lives here so that the key bindings on the commands can be processed in the viewport.
- L328 _public prototype_ `FEdModeFoliage();` — Constructor
- L331 _public prototype_ `virtual ~FEdModeFoliage();` — Destructor
- L334 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L337 _public prototype_ `virtual void Enter() override;` — FEdMode: Called when the mode is entered
- L340 _public prototype_ `virtual void Exit() override;` — FEdMode: Called when the mode is exited
- L343 _public prototype_ `virtual void PostUndo() override;` — FEdMode: Called after an Undo operation
- L345 _public function_ `virtual bool UsesToolkits() const override`
- L348 _public prototype_ `void NotifyNewCurrentLevel();` — Called when the current level changes
- L349 _public prototype_ `void NotifyLevelAddedToWorld(ULevel* InLevel, UWorld* InWorld);`
- L350 _public prototype_ `void NotifyLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);`
- L353 _public prototype_ `void NotifyAssetRemoved(const FAssetData& AssetInfo);` — Called when asset is removed
- L356 _public prototype_ `void NotifyActorSelectionChanged(bool bSelect, const TArray<AActor*>& Selection);` — Called when actor foliage selection changes
- L368 _public prototype_ `virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;` — Called when the mouse is moved over the viewport @param	InViewportClient	Level editor viewport client that captured the mouse input @param	InViewport			Viewport that captured the mouse input @param	InMouseX			New mouse cursor X coordinate @param	InMouseY			New mouse cursor Y coordinate @return	true if input was handled
- L380 _public prototype_ `virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;` — FEdMode: Called when the mouse is moved while a window input capture is in effect @param	InViewportClient	Level editor viewport client that captured the mouse input @param	InViewport			Viewport that captured the mouse input @param	InMouseX			New mouse cursor X coordinate @param	InMouseY			New mouse cursor Y coordinate @return	true if input was handled
- L383 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode: Called when a mouse button is pressed
- L386 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode: Called when a mouse button is released
- L389 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;` — FEdMode: Called once per frame
- L392 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;` — FEdMode: Called when a key is pressed
- L395 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;` — FEdMode: Called when mouse drag input it applied
- L398 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;` — FEdMode: Render elements for the Foliage tool
- L401 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;` — FEdMode: Render HUD elements for this tool
- L404 _public prototype_ `virtual bool Select(AActor* InActor, bool bInSelected) override;` — FEdMode: Handling SelectActor
- L407 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;` — FEdMode: Check to see if an actor can be selected in this mode - no side effects
- L410 _public prototype_ `virtual void ActorSelectionChangeNotify() override;` — FEdMode: Called when the currently selected actor has changed
- L413 _public prototype_ `bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;` — Notifies all active modes of mouse click messages.
- L416 _public prototype_ `void MoveSelectedFoliageToLevel(ULevel* InTargetLevel);` — Moves selected foliage instances to the target level.
- L419 _public prototype_ `bool CanMoveSelectedFoliageToLevel(ULevel* InTargetLevel) const;` — Tell us if we can moves selected foliage instances to the target level.
- L422 _public prototype_ `void MoveSelectedFoliageToActorEditorContext();` — Moves selected foliage instances to the current actor editor context
- L425 _public prototype_ `bool EndTracking();` — Ends tracking and end potential transaction
- L428 _public prototype_ `virtual FVector GetWidgetLocation() const override;` — FEdMode: widget handling
- L429 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L430 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L431 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L432 _public prototype_ `virtual EAxisList::Type GetWidgetAxisToDraw(UE::Widget::EWidgetMode InWidgetMode) const override;`
- L434 _public prototype_ `virtual bool DisallowMouseDeltaTracking() const override;`
- L437 _public prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Called when objects are replaced (after a BP compile for instance)
- L440 _public prototype_ `void ForceRealTimeViewports(const bool bEnable);` — Forces real-time perspective viewports
- L443 _public prototype_ `void StartFoliageBrushTrace(FEditorViewportClient* ViewportClient, class UViewportInteractor* Interactor = nullptr);` — Start foliage tracing
- L446 _public prototype_ `void EndFoliageBrushTrace();` — End foliage tracing
- L449 _public prototype_ `void FoliageBrushTrace(FEditorViewportClient* ViewportClient, const FVector& InRayOrigin, const FVector& InRayDirection);` — Trace under the mouse cursor and update brush position
- L453 _public prototype_ `void GetRandomVectorInBrush(FVector& OutStart, FVector& OutEnd);` — Generate start/end points for a random trace inside the sphere brush. returns a line segment inside the sphere parallel to the view direction
- L456 _public prototype_ `void PreApplyBrush();` — Setup before call to ApplyBrush
- L459 _public prototype_ `void ApplyBrush(FEditorViewportClient* ViewportClient);` — Apply brush
- L462 _public prototype_ `TArray<FFoliageMeshUIInfoPtr>& GetFoliageMeshList();` — Get list of meshes for current level
- L465 _public prototype_ `void PopulateFoliageMeshList();` — Populate mesh with foliage mesh settings found across world
- L468 _public prototype_ `void OnFoliageMeshListSortModeChanged(EColumnSortMode::Type InSortMode);` — Handler for mesh list sort mode changes
- L471 _public prototype_ `EColumnSortMode::Type GetFoliageMeshListSortMode() const;` — Returns foliage mesh list sort mode
- L474 _public prototype_ `void OnInstanceCountUpdated(const UFoliageType* FoliageType);` — Handler for foliage mesh instance count changes
- L477 _public prototype_ `void CalcTotalInstanceCount(int32& OutInstanceCountTotal, int32& OutInstanceCountCurrentLevel);` — Counts total number of instances in current level and across whole world
- L480 _public prototype_ `bool CanPaint(const ULevel* InLevel);` — Whether any of the selected foliage types can be painted into level
- L483 _public prototype_ `static bool CanPaint(const UFoliageType* FoliageType, const ULevel* InLevel);` — Whether specified FoliageType can be painted into level
- L486 _public prototype_ `bool IsModifierButtonPressed(const FEditorViewportClient* ViewportClient) const;` — Shift or modifier button pressed
- L489 _public prototype_ `UFoliageType* AddFoliageAsset(UObject* InAsset, bool bInPlaceholderAsset = false);` — Add a new asset (FoliageType or StaticMesh)
- L492 _public prototype_ `bool RemoveFoliageType(UFoliageType** FoliageTypes, int32 Num);` — Remove a list of Foliage types
- L495 _public prototype_ `void ReallocateClusters(UFoliageType* Settings);` — Reapply cluster settings to all the instances
- L498 _public prototype_ `void BakeFoliage(UFoliageType* Settings, bool bSelectedOnly);` — Bake meshes to StaticMeshActors
- L507 _public prototype_ `UFoliageType* CopySettingsObject(UFoliageType* Settings);` — Copy the settings object for this static mesh @param StaticMesh	The static mesh to copy the settings of. @return The duplicated settings now assigned to the static mesh.
- L510 _public prototype_ `void ReplaceSettingsObject(UFoliageType* OldSettings, UFoliageType* NewSettings);` — Replace the settings object for this static mesh with the one specified
- L513 _public prototype_ `UFoliageType* SaveFoliageTypeObject(UFoliageType* Settings, bool bPlaceholderAsset = false);` — Save the foliage type object. If it isn't an asset, will prompt the user for a location to save the new asset.
- L515 _public prototype_ `void IncludeNonFoliageActors(const TArray<const UFoliageType*>& FoliageTypes, bool bOnlyCurrentLevel);`
- L517 _public prototype_ `void ExcludeFoliageActors(const TArray<const UFoliageType*>& FoliageTypes, bool bOnlyCurrentLevel);`
- L520 _public prototype_ `void SelectInstances(const TArray<const UFoliageType*>& FoliageTypes, bool bSelect);` — Set/Clear selection for foliage instances of a specific types
- L523 _public prototype_ `void SelectInstances(const UFoliageType* Settings, bool bSelect);` — Set/Clear selection for foliage instances of specific type
- L526 _public prototype_ `void FocusSelectedInstances() const;` — Focus on selected instances
- L529 _public prototype_ `void SelectInvalidInstances(const TArray<const UFoliageType*>& FoliageTypes);` — Find and select instances that don't have valid base or 'off-ground'
- L532 _public prototype_ `void SelectInvalidInstances(const UFoliageType* Settings);` — Find and select instances that don't have valid base or 'off-ground'
- L535 _public prototype_ `void GetSelectedInstanceFoliageTypes(TArray<const UFoliageType*>& OutFoliageTypes) const;` — Returns selected foliage types based on selected foliage instances
- L538 _public prototype_ `void AdjustBrushRadius(float Multiplier);` — Adjusts the radius of the foliage brush, using the given multiplier to adjust speed
- L541 _public prototype_ `void AdjustPaintDensity(float Multiplier);` — Adjusts the painting density of the foliage brush, using the given multiplier to adjust speed
- L544 _public prototype_ `void AdjustUnpaintDensity(float Multiplier);` — Adjusts the unpainting (erasing) density of the foliage brush, using the given multiplier to adjust speed
- L547 _public prototype_ `static void AddInstances(UWorld* InWorld, const TArray<FDesiredFoliageInstance>& DesiredInstances, const FFoliagePaintingGeometryFilter& OverrideGeometryFilter, bool InRebuildFoliageTree = true);` — Add desired instances. Uses foliage settings to determine location/scale/rotation and whether instances should be ignored
- L550 _public prototype_ `void OnEndPIE(const bool bIsSimulating);` — Called as PIE ends
- L553 _public prototype_ `EFoliageEditingState GetEditingState() const;` — Return the current foliage editing state
- L556 _public function_ `bool IsEditingEnabled() const` — Simgple wrapper to know if we can edit foliage based on edit state
- L561 _public typedef_ `typedef TMap<FName, TMap<ULandscapeComponent*, TArray<uint8> > > LandscapeLayerCacheData;`
- L563 _public member_ `FSimpleMulticastDelegate OnToolChanged;`
- L566 _public prototype_ `void OnSetPaint();` — Sets the tool mode to Paint.
- L569 _public prototype_ `void OnSetReapplySettings();` — Sets the tool mode to Reapply Settings.
- L572 _public prototype_ `void OnSetSelectInstance();` — Sets the tool mode to Select.
- L575 _public prototype_ `void OnSetLasso();` — Sets the tool mode to Lasso Select.
- L578 _public prototype_ `void OnSetPaintFill();` — Sets the tool mode to Paint Bucket.
- L581 _public prototype_ `void OnSetErase();` — Sets the tool mode to Erase
- L584 _public prototype_ `void OnSetPlace();` — Sets the tool mode to Place Single Instance
- L587 _public prototype_ `void OnReflectSelectionInPalette();` — Handle reflecting selected foliage types in the FoliagePalette
- L590 _public prototype_ `void RemoveSelectedInstances(UWorld* InWorld);` — Remove currently selected instances
- L593 _public prototype_ `void GetFoliageTypeFilters(TArray<const UClass*>& OutFilters) const;` — Returns the list of valid FoliageType class filters
- L596 _public prototype_ `static void ForEachFoliageInfo(UWorld* InWorld, const UFoliageType* FoliageType, const FSphere& BrushSphere, TFunctionRef<bool(AInstancedFoliageActor* IFA, FFoliageInfo* FoliageInfo, const UFoliageType* FoliageType)> InOperation);` — Find the relevant foliage actor with the foliage type and run the operation
- L600 _private prototype_ `void BindCommands();`
- L601 _private prototype_ `bool CurrentToolUsesBrush() const;`
- L604 _private prototype_ `void HandleToolChanged();` — Called when the user changes the current tool in the UI
- L607 _private prototype_ `void ClearAllToolSelection();` — Deselects all tools
- L610 _private prototype_ `void AddInstancesForBrush(UWorld* InWorld, const UFoliageType* Settings, const FSphere& BrushSphere, int32 DesiredInstanceCount, float Pressure);` — Add instances inside the brush to match DesiredInstanceCount
- L615 _private prototype_ `bool AddSingleInstanceForBrush(UWorld* InWorld, const UFoliageType* Settings, float Pressure);` — Add single instance inside the brush @return true if instance was added successfully
- L618 _private prototype_ `void RemoveInstancesForBrush(UWorld* InWorld, const UFoliageType* Settings, const FSphere& BrushSphere, int32 DesiredInstanceCount, float Pressure);` — Remove instances inside the brush to match DesiredInstanceCount.
- L621 _private prototype_ `void ApplyPaintBucket_Add(AActor* Actor);` — Apply paint bucket to actor
- L622 _private prototype_ `void ApplyPaintBucket_Remove(AActor* Actor);`
- L625 _private prototype_ `void ReapplyInstancesDensityForBrush(UWorld* InWorld, const UFoliageType* Settings, const FSphere& BrushSphere, float Pressure);` — Reapply instance settings to exiting instances
- L626 _private prototype_ `void ReapplyInstancesForBrush(UWorld* InWorld, const UFoliageType* Settings, const FSphere& BrushSphere, float Pressure, bool bSingleInstanceMode);`
- L627 _private prototype_ `void ReapplyInstancesForBrush(UWorld* InWorld, AInstancedFoliageActor* IFA, const UFoliageType* Settings, FFoliageInfo* MeshInfo, const FSphere& BrushSphere, float Pressure, bool bSingleInstanceMode);`
- L630 _private prototype_ `void SelectInstancesForBrush(UWorld* InWorld, const UFoliageType* Settings, const FSphere& BrushSphere, bool bSelect);` — Select instances inside the brush.
- L633 _private prototype_ `void SelectInstanceAtLocation(UWorld* InWorld, const UFoliageType* Settings, const FVector& BrushLocation, bool bSelect);` — Select instance closest to the brush.
- L636 _private prototype_ `void SelectInstances(UWorld* InWorld, bool bSelect);` — Set/Clear selection for all foliage instances
- L639 _private prototype_ `void SelectInstances(UWorld* InWorld, const UFoliageType* Settings, bool bSelect);` — Set/Clear selection for foliage instances of specific type
- L642 _private prototype_ `void ApplySelection(UWorld* InWorld, bool bApply);` — Propagate the selected foliage instances to the actual render foliage
- L645 _private prototype_ `void UpdateInstancePartitioning(UWorld* InWorld);` — Update Instances so that they are in the right partitioning level
- L648 _private prototype_ `void PostTransformSelectedInstances(UWorld* InWorld);` — Called when transform transaction is done
- L651 _private prototype_ `void TransformSelectedInstances(UWorld* InWorld, const FVector& InDrag, const FRotator& InRot, const FVector& InScale, bool bDuplicate);` — Applies relative transformation to selected instances
- L654 _private prototype_ `bool GetSelectionLocation(UWorld* InWorld, FVector& OutLocation) const;` — Return true if OutLocation is valid
- L657 _private prototype_ `void UpdateWidgetLocationToInstanceSelection();` — Updates ed mode widget location to currently selected instance
- L660 _private prototype_ `bool SnapInstanceToGround(AInstancedFoliageActor* InIFA, const UFoliageType* Settings, FFoliageInfo& Mesh, int32 InstanceIdx);` — Snap instance to the ground
- L661 _private prototype_ `void SnapSelectedInstancesToGround(UWorld* InWorld);`
- L664 _private prototype_ `void HandleOnActorSpawned(AActor* Actor);` — Callback for when an actor is spawned (to check if it's a new IFA)
- L667 _private prototype_ `void HandleOnFoliageTypeMeshChanged(UFoliageType* FoliageType);` — Callback for when the mesh assigned to a foliage type referenced by an IFA is changed
- L670 _private prototype_ `static bool AddInstancesImp(UWorld* InWorld, const UFoliageType* Settings, const TArray<FDesiredFoliageInstance>& DesiredInstances, const TArray<int32>& ExistingInstances = TArray<int32>(), const float Pressure = 1.f, LandscapeLayerCacheData* LandscapeLayerCaches = nullptr, const FFoliageUISettings* UISettings = nullptr, const FFoliagePaintingGeometryFilter* OverrideGeometryFilter = nullptr, bool InRebuildFoliageTree = true);` — Common code for adding instances to world based on settings
- L673 _private prototype_ `static void CalculatePotentialInstances(UWorld* InWorld, const UFoliageType* Settings, const TArray<FDesiredFoliageInstance>& DesiredInstances, TArray<FPotentialInstance> OutPotentialInstances[NUM_INSTANCE_BUCKETS], LandscapeLayerCacheData* LandscaleLayerCachesPtr, const FFoliageUISettings* UISettings, const FFoliagePaintingGeometryFilter* OverrideGeometryFilter = nullptr);` — Logic for determining which instances can be placed in the world
- L676 _private prototype_ `static void CalculatePotentialInstances_ThreadSafe(UWorld* InWorld, const UFoliageType* Settings, const TArray<FDesiredFoliageInstance>* DesiredInstances, TArray<FPotentialInstance> OutPotentialInstances[NUM_INSTANCE_BUCKETS], const FFoliageUISettings* UISettings, const int32 StartIdx, const int32 LastIdx, const FFoliagePaintingGeometryFilter* OverrideGeometryFilter = nullptr);` — Similar to CalculatePotentialInstances, but it doesn't do any overlap checks which are much harder to thread. Meant to be run in parallel for placing lots of instances
- L679 _private prototype_ `static bool GetStaticMeshVertexColorForHit(const UStaticMeshComponent* InStaticMeshComponent, int32 InTriangleIndex, const FVector& InHitLocation, FColor& OutVertexColor);` — Lookup the vertex color corresponding to a location traced on a static mesh
- L682 _private prototype_ `static bool IsUsingVertexColorMask(const UFoliageType* Settings);` — Returns true when at least one color channel is used by the vertex color mask
- L685 _private prototype_ `static bool VertexMaskCheck(const FHitResult& Hit, const UFoliageType* Settings);` — Does a filter based on the vertex color of a static mesh
- L688 _private prototype_ `void SetBrushOpacity(const float InOpacity);` — Set the brush mesh opacity
- L690 _private prototype_ `float GetPaintingBrushRadius() const;`
- L693 _private prototype_ `void RebuildFoliageTree(const UFoliageType* Settings);` — Called if the foliage tree is outdated
- L696 _private prototype_ `void BeginSelectionUpdate();` — Increments a counter that prevents sending out notifications until end selection is called  and counter reaches 0
- L699 _private prototype_ `void EndSelectionUpdate();` — Decrements counter and will notify editor of selection change if counter reaches 0
- L701 _private member_ `bool bBrushTraceValid;`
- L702 _private member_ `FVector BrushLocation;`
- L703 _private member_ `FVector BrushNormal;`
- L704 _private member_ `FVector BrushTraceDirection;`
- L705 _private member_ `TObjectPtr<UStaticMeshComponent> SphereBrushComponent;`
- L708 _private member_ `class UMaterialInstanceDynamic* BrushMID;` — The dynamic material of the sphere brush.
- L709 _private member_ `FColor BrushDefaultHighlightColor;`
- L710 _private member_ `FColor BrushCurrentHighlightColor;`
- L713 _private member_ `float DefaultBrushOpacity;` — Default opacity received from the brush material to reset it when closing.
- L716 _private member_ `LandscapeLayerCacheData LandscapeLayerCaches;` — Landscape layer cache data
- L719 _private member_ `TMultiMap<UFoliageType*, FMeshInfoSnapshot> InstanceSnapshot;` — Cache of instance positions at the start of the transaction
- L721 _private member_ `bool bToolActive;`
- L722 _private member_ `bool bCanAltDrag;`
- L724 _private member_ `TArray<FFoliageMeshUIInfoPtr> FoliageMeshList;`
- L725 _private member_ `EColumnSortMode::Type FoliageMeshListSortMode;`
- L727 _private member_ `FDelegateHandle OnActorSpawnedHandle;`
- L729 _private member_ `int32 UpdateSelectionCounter;`
- L730 _private member_ `bool bHasDeferredSelectionNotification;`
- L734 _private member_ `bool bMoving;` — When transforming instances
- L737 _private member_ `bool bTracking;` — Flag to know when we are tracking a transaction in mouse delta

#### Free symbols / members of external scopes

- L51 _namespace_ `namespace EFoliagePaletteViewMode`
- L61 _namespace_ `namespace EFoliageSingleInstantiationPlacementMode`
- L71 _variable_ `const float SingleInstanceModeBrushSize = 20.0f;`
- L236 _typedef_ `typedef TSharedPtr<FFoliageMeshUIInfo> FFoliageMeshUIInfoPtr;`
- L307 _macro_ `#define NUM_INSTANCE_BUCKETS 10` — Number of buckets for layer weight histogram distribution.

### `Source/Editor/FoliageEdit/Private/FoliageEdModeToolkit.h` (Private)


#### class `FFoliageEdModeToolkit`  
`class FFoliageEdModeToolkit : public FModeToolkit`  
_L15-44_
- inherits: `FModeToolkit`
- desc: Public interface to Foliage Edit mode.
- L19 _public prototype_ `virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost) override;` — Initializes the foliage mode toolkit
- L22 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L23 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L24 _public prototype_ `virtual class FEdMode* GetEditorMode() const override;`
- L25 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L28 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& InPaletteName) const;` — Mode Toolbar Palettes
- L29 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const;`
- L30 _public prototype_ `virtual void BuildToolPalette(FName PaletteName, class FToolBarBuilder& ToolbarBuilder);`
- L33 _public prototype_ `virtual FText GetActiveToolDisplayName() const;` — Modes Panel Header Information
- L34 _public prototype_ `virtual FText GetActiveToolMessage() const;`
- L36 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L38 _public prototype_ `void RefreshFullList();`
- L39 _public prototype_ `void NotifyFoliageTypeMeshChanged(class UFoliageType* FoliageType);`
- L40 _public prototype_ `void ReflectSelectionInPalette();`
- L43 _private member_ `TSharedPtr< class SFoliageEdit > FoliageEdWidget;`

### `Source/Editor/FoliageEdit/Private/FoliageEditActions.h` (Private)


#### class `FFoliageEditCommands`  
`class FFoliageEditCommands : public TCommands<FFoliageEditCommands>`  
_L17-72_
- inherits: `TCommands<FFoliageEditCommands>`
- desc: Unreal Foliage Edit mode actions
- L21 _public function_ `FFoliageEditCommands() : TCommands<FFoliageEditCommands> ( "FoliageEditMode",`
- L36 _public member_ `TSharedPtr< FUICommandInfo > IncreaseBrushSize;` — Commands for the foliage brush settings.
- L37 _public member_ `TSharedPtr< FUICommandInfo > DecreaseBrushSize;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > IncreasePaintDensity;`
- L40 _public member_ `TSharedPtr< FUICommandInfo > DecreasePaintDensity;`
- L42 _public member_ `TSharedPtr< FUICommandInfo > IncreaseUnpaintDensity;`
- L43 _public member_ `TSharedPtr< FUICommandInfo > DecreaseUnpaintDensity;`
- L46 _public member_ `TSharedPtr< FUICommandInfo > SetPaint;` — Commands for the tools toolbar.
- L47 _public member_ `TSharedPtr< FUICommandInfo > SetReapplySettings;`
- L48 _public member_ `TSharedPtr< FUICommandInfo > SetSelect;`
- L49 _public member_ `TSharedPtr< FUICommandInfo > SetLassoSelect;`
- L50 _public member_ `TSharedPtr< FUICommandInfo > SetPaintBucket;`
- L53 _public member_ `TSharedPtr< FUICommandInfo > SetNoSettings;` — Commands for the foliage item toolbar.
- L54 _public member_ `TSharedPtr< FUICommandInfo > SetPaintSettings;`
- L55 _public member_ `TSharedPtr< FUICommandInfo > SetClusterSettings;`
- L58 _public member_ `TSharedPtr< FUICommandInfo > ReflectSelectionInPalette;` — FoliagePalette commands
- L61 _public member_ `TSharedPtr< FUICommandInfo > RemoveFoliageType;` — FoliageType commands
- L62 _public member_ `TSharedPtr< FUICommandInfo > ShowFoliageTypeInCB;`
- L63 _public member_ `TSharedPtr< FUICommandInfo > SelectAllInstances;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > DeselectAllInstances;`
- L65 _public member_ `TSharedPtr< FUICommandInfo > SelectInvalidInstances;`
- L69 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/FoliageEdit/Private/FoliagePaletteCommands.h` (Private)


#### class `FFoliagePaletteCommands`  
`class FFoliagePaletteCommands : public TCommands < FFoliagePaletteCommands >`  
_L16-41_
- inherits: `TCommands<FFoliagePaletteCommands>`
- desc: Foliage Mode Palette Actions
- L20 _public function_ `FFoliagePaletteCommands() : TCommands<FFoliagePaletteCommands> ( "FoliagePalette",`
- L31 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L34 _public member_ `TSharedPtr< FUICommandInfo > ActivateFoliageType;` — Foliage Palette Commands
- L35 _public member_ `TSharedPtr< FUICommandInfo > DeactivateFoliageType;`
- L36 _public member_ `TSharedPtr< FUICommandInfo > RemoveFoliageType;`
- L37 _public member_ `TSharedPtr< FUICommandInfo > ShowFoliageTypeInCB;`
- L38 _public member_ `TSharedPtr< FUICommandInfo > SelectAllInstances;`
- L39 _public member_ `TSharedPtr< FUICommandInfo > DeselectAllInstances;`
- L40 _public member_ `TSharedPtr< FUICommandInfo > SelectInvalidInstances;`

### `Source/Editor/FoliageEdit/Private/FoliagePaletteItem.h` (Private)


#### class `FFoliagePaletteItemModel`  
`class FFoliagePaletteItemModel : public TSharedFromThis<FFoliagePaletteItemModel>`  
_L38-110_
- inherits: `TSharedFromThis<FFoliagePaletteItemModel>`
- L41 _public prototype_ `FFoliagePaletteItemModel(FFoliageMeshUIInfoPtr InTypeInfo, TSharedRef<SFoliagePalette> InFoliagePalette, TSharedPtr<class FAssetThumbnailPool> InThumbnailPool, FEdModeFoliage* InFoliageEditMode);`
- L44 _public prototype_ `TSharedPtr<SFoliagePalette> GetFoliagePalette() const;` — @return The foliage palette that contains the item
- L46 _public prototype_ `FFoliageMeshUIInfoPtr GetTypeUIInfo() const;`
- L47 _public prototype_ `UFoliageType* GetFoliageType() const;`
- L48 _public prototype_ `const struct FFoliageUISettings& GetFoliageUISettings() const;`
- L51 _public prototype_ `TSharedRef<SWidget> GetThumbnailWidget() const;` — @return The thumbnail widget for this item
- L54 _public prototype_ `TSharedRef<class SToolTip> CreateTooltipWidget() const;` — @return The tooltip widget for this item
- L57 _public prototype_ `TSharedRef<class SCheckBox> CreateActivationCheckBox(TAttribute<bool> IsItemWidgetSelected, TAttribute<EVisibility> InVisibility = TAttribute<EVisibility>());` — @return The checkbox widget for activating/deactivating this type in the palette
- L60 _public prototype_ `TSharedRef<class SButton> CreateSaveAssetButton(TAttribute<EVisibility> InVisibility = TAttribute<EVisibility>());` — @return The save asset button
- L63 _public prototype_ `FName GetDisplayFName() const;` — Gets the FName version of the displayed name of this item
- L66 _public prototype_ `FText GetPaletteSearchText() const;` — Gets the current search filter text
- L69 _public prototype_ `FText GetInstanceCountText(bool bLevelOnly = true) const;` — Gets the number of instances of this foliage type
- L72 _public prototype_ `void SetTypeActiveInPalette(bool bSetActiveInPalette);` — Sets whether this foliage type is active in the palette
- L75 _public prototype_ `bool IsActive() const;` — Gets whether this foliage type is active in the palette
- L78 _public prototype_ `bool IsBlueprint() const;` — @return Whether this palette item represents an instance of a foliage type blueprint class
- L81 _public prototype_ `bool IsAsset() const;` — @return Whether this palette item represents a foliage type asset
- L85 _private prototype_ `void HandleCheckStateChanged(const ECheckBoxState NewCheckedState, TAttribute<bool> IsItemWidgetSelected);` — Handles the change in activation of the item in the palette
- L88 _private prototype_ `ECheckBoxState GetCheckBoxState() const;` — Gets whether the foliage type is active in the palette
- L91 _private prototype_ `bool IsSaveEnabled() const;` — Whether the save asset button is enabled
- L94 _private prototype_ `FReply HandleSaveAsset();` — Saves the foliage type
- L97 _private prototype_ `EVisibility GetTooltipVisibility() const;` — Gets the visibility of the entire tooltip
- L100 _private prototype_ `EVisibility GetTooltipThumbnailVisibility() const;` — Gets the visibility of the thumbnail in the tooltip
- L103 _private prototype_ `FText GetSourceAssetTypeText() const;` — Gets the source asset type text
- L105 _private member_ `TSharedPtr<SWidget> ThumbnailWidget;`
- L106 _private member_ `FName DisplayFName;`
- L107 _private member_ `FFoliageMeshUIInfoPtr TypeInfo;`
- L108 _private member_ `TWeakPtr<SFoliagePalette> FoliagePalette;`
- L109 _private member_ `FEdModeFoliage* FoliageEditMode;`

#### class `SFoliagePaletteItemTile`  
`class SFoliagePaletteItemTile : public STableRow<FFoliageMeshUIInfoPtr>`  
_L113-131_
- inherits: `STableRow<FFoliageMeshUIInfoPtr>`
- desc: A tile representing a foliage type in the palette
- L116 _public function_ `SLATE_BEGIN_ARGS(SFoliagePaletteItemTile)`
- L117 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> InOwnerTableView, TSharedPtr<FFoliagePaletteItemModel>& InModel);`
- L122 _private prototype_ `FLinearColor GetTileColorAndOpacity() const;`
- L123 _private prototype_ `EVisibility GetCheckBoxVisibility() const;`
- L124 _private prototype_ `EVisibility GetSaveButtonVisibility() const;`
- L125 _private prototype_ `EVisibility GetInstanceCountVisibility() const;`
- L126 _private prototype_ `bool CanShowOverlayItems() const;`
- L129 _private member_ `static const float MinScaleForOverlayItems;`
- L130 _private member_ `TSharedPtr<FFoliagePaletteItemModel> Model;`

#### class `SFoliagePaletteItemRow`  
`class SFoliagePaletteItemRow : public SMultiColumnTableRow<FFoliageMeshUIInfoPtr>`  
_L134-148_
- inherits: `SMultiColumnTableRow<FFoliageMeshUIInfoPtr>`
- desc: A tree row representing a foliage type in the palette
- L137 _public function_ `SLATE_BEGIN_ARGS(SFoliagePaletteItemRow)`
- L138 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> InOwnerTableView, TSharedPtr<FFoliagePaletteItemModel>& InModel);`
- L141 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L144 _private prototype_ `EVisibility GetSaveButtonVisibility() const;`
- L147 _private member_ `TSharedPtr<FFoliagePaletteItemModel> Model;`

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedPtr<FFoliageMeshUIInfo> FFoliageMeshUIInfoPtr;` — should match typedef in FoliageEdMode.h
- L29 _namespace_ `namespace FoliagePaletteTreeColumns`
- L32 _variable_ `static const FName ColumnID_ToggleActive("Tog` (scope `FoliagePaletteTreeColumns`) — IDs for list columns
- L33 _variable_ `static const FName ColumnID_Type("Typ` (scope `FoliagePaletteTreeColumns`)
- L34 _variable_ `static const FName ColumnID_InstanceCount("Ins` (scope `FoliagePaletteTreeColumns`)
- L35 _variable_ `static const FName ColumnID_Save("Sav` (scope `FoliagePaletteTreeColumns`)

### `Source/Editor/FoliageEdit/Private/FoliageTypeCustomizationHelpers.h` (Private)


#### class `FFoliageTypeCustomizationHelpers`  
`class FFoliageTypeCustomizationHelpers`  
_L15-31_
- L20 _public prototype_ `static void ModifyFoliagePropertyRow(IDetailPropertyRow* PropertyRow, const TAttribute<EVisibility>& InVisibility, const TAttribute<bool>& InEnabled);` — Modifies the visibility and enabled attributes of an existing property row
- L22 _public prototype_ `static void AddBodyInstanceProperties(IDetailLayoutBuilder& LayoutBuilder);`
- L25 _public prototype_ `static void HideFoliageCategory(IDetailLayoutBuilder& DetailLayoutBuilder, FName CategoryName);` — Hides all properties in the given category
- L28 _public prototype_ `static void BindHiddenPropertyVisibilityGetter(const TSharedPtr<IPropertyHandle>& PropertyHandle, TAttribute<EVisibility>::FGetter& OutVisibilityGetter);` — Binds the appropriate visibility getter for the hidden property
- L30 _public prototype_ `static EVisibility GetScaleAxisVisibility(EAxis::Type Axis, const TSharedPtr<IPropertyHandle> ScalingPropertyHandle);`

### `Source/Editor/FoliageEdit/Private/FoliageTypeDetails.h` (Private)


#### class `FFoliageTypeDetails`  
`class FFoliageTypeDetails : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `virtual ~FFoliageTypeDetails()= default;`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder );` — IDetailCustomization interface

### `Source/Editor/FoliageEdit/Private/FoliageTypeFactory.h` (Private)


#### class `UFoliageType_InstancedStaticMeshFactory`  
`class UFoliageType_InstancedStaticMeshFactory : public UFactory`  
_L24-33_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L29 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L30 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L31 _private prototype_ `virtual FText GetToolTip() const override;`

#### class `UFoliageType_ActorFactory`  
`class UFoliageType_ActorFactory : public UFactory`  
_L36-45_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L41 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L42 _private prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L43 _private prototype_ `virtual FText GetToolTip() const override;`

### `Source/Editor/FoliageEdit/Private/FoliageTypeObjectCustomization.h` (Private)


#### class `FFoliageTypeObjectCustomization`  
`class FFoliageTypeObjectCustomization : public IPropertyTypeCustomization`  
_L11-26_
- inherits: `IPropertyTypeCustomization`
- L15 _public function_ `static TSharedRef<class IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L25 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& AssetData) const;`

### `Source/Editor/FoliageEdit/Private/FoliageTypePaintingCustomization.h` (Private)


#### class `FFoliageTypePaintingCustomization`  
`class FFoliageTypePaintingCustomization : public IDetailCustomization`  
_L23-62_
- inherits: `IDetailCustomization`
- desc: FFoliageTypePaintingCustomization
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FEdModeFoliage* InFoliageEditMode);` — Makes a new instance of this detail layout class
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L33 _private prototype_ `FFoliageTypePaintingCustomization(FEdModeFoliage* InFoliageEditMode);`
- L35 _private prototype_ `EVisibility GetScaleVisibility(EAxis::Type Axis) const;`
- L36 _private prototype_ `EVisibility GetNonReapplyPropertyVisibility() const;`
- L37 _private prototype_ `EVisibility GetReapplyModeVisibility() const;`
- L39 _private prototype_ `ECheckBoxState GetReapplyPropertyState(TSharedPtr<IPropertyHandle> ReapplyProperty) const;`
- L40 _private prototype_ `void OnReapplyPropertyStateChanged(ECheckBoxState CheckState, TSharedPtr<IPropertyHandle> ReapplyProperty);`
- L41 _private prototype_ `bool IsReapplyPropertyEnabled(TSharedPtr<IPropertyHandle> ReapplyProperty) const;`
- L44 _private prototype_ `IDetailPropertyRow& AddFoliageProperty( IDetailCategoryBuilder& Category, TSharedPtr<IPropertyHandle>& Property, TSharedPtr<IPropertyHandle>& ReapplyProperty, const TAttribute<EVisibility>& InVisibility, const TAttribute<bool>& InEnabled);` — Adds a property that can optionally be hidden behind another when the reapply tool is active
- L51 _private prototype_ `void ShowFoliagePropertiesForCategory(IDetailLayoutBuilder& DetailLayoutBuilder, const FName CategoryName, TMap<const FName, IDetailPropertyRow*>& OutDetailRowsByPropertyName);`
- L54 _private prototype_ `void GetHiddenPropertyVisibility(const TSharedPtr<IPropertyHandle>& PropertyHandle, bool bHideInReapplyTool, TAttribute<EVisibility>& OutVisibility) const;` — Gets the visibility attribute for property that is hidden behind another
- L58 _private member_ `FEdModeFoliage* FoliageEditMode;` — Pointer to the foliage edit mode.
- L60 _private member_ `TSharedPtr<IPropertyHandle> Scaling;`
- L61 _private member_ `TSharedPtr<IPropertyHandle> ReapplyScaling;`

### `Source/Editor/FoliageEdit/Private/FoliageType_InstancedStaticMeshPaintingCustomization.h` (Private)


#### class `FFoliageType_InstancedStaticMeshPaintingCustomization`  
`class FFoliageType_InstancedStaticMeshPaintingCustomization : public IDetailCustomization`  
_L15-34_
- inherits: `IDetailCustomization`
- desc: FFoliageTypePaintingCustomization
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(FEdModeFoliage* InFoliageEditMode);` — Makes a new instance of this detail layout class
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L26 _private prototype_ `FFoliageType_InstancedStaticMeshPaintingCustomization(FEdModeFoliage* InFoliageEditMode);`
- L27 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& AssetData) const;`
- L30 _private member_ `FEdModeFoliage* FoliageEditMode;` — Pointer to the foliage edit mode.
- L33 _private member_ `TArray<FName> UnavailableMeshNames;` — The static meshes that are not available to local foliage types (because they are already assigned to a local foliage type)

### `Source/Editor/FoliageEdit/Private/LandscapeGrassTypeFactory.h` (Private)


#### class `ULandscapeGrassTypeFactory`  
`class ULandscapeGrassTypeFactory : public UFactory`  
_L21-28_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L26 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Source/Editor/FoliageEdit/Private/ProceduralFoliageComponentDetails.h` (Private)


#### class `FProceduralFoliageComponentDetails`  
`class FProceduralFoliageComponentDetails : public IDetailCustomization`  
_L14-34_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `virtual ~FProceduralFoliageComponentDetails()= default;`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder );` — IDetailCustomization interface
- L25 _private prototype_ `FReply OnResimulateClicked();`
- L26 _private prototype_ `FReply OnLoadUnloadedAreas();`
- L27 _private prototype_ `bool IsResimulateEnabled() const;`
- L28 _private prototype_ `bool IsResimulateEnabledWithReason(FText& OutReason) const;`
- L29 _private prototype_ `FText GetResimulateTooltipText() const;`
- L30 _private prototype_ `bool HasUnloadedAreas() const;`
- L32 _private member_ `TArray< TWeakObjectPtr<class UProceduralFoliageComponent> > SelectedComponents;`

### `Source/Editor/FoliageEdit/Private/ProceduralFoliageComponentVisualizer.h` (Private)


#### class `FProceduralFoliageComponentVisualizer`  
`class FProceduralFoliageComponentVisualizer : public FComponentVisualizer`  
_L11-17_
- inherits: `FComponentVisualizer`
- L15 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

### `Source/Editor/FoliageEdit/Private/ProceduralFoliageSpawnerFactory.h` (Private)


#### class `UProceduralFoliageSpawnerFactory`  
`class UProceduralFoliageSpawnerFactory : public UFactory`  
_L21-29_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L26 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L27 _private prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Source/Editor/FoliageEdit/Private/SFoliageEdit.h` (Private)


#### class `SFoliageEdit`  
`class SFoliageEdit : public SCompoundWidget`  
_L27-266_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SFoliageEdit)`
- L35 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget functions
- L38 _public prototype_ `void RefreshFullList();` — Does a full refresh on the list.
- L41 _public prototype_ `void NotifyFoliageTypeMeshChanged(UFoliageType* FoliageType);` — Notifies the widget that the mesh assigned to a foliage type in the list has changed
- L44 _public prototype_ `void ReflectSelectionInPalette();` — Notifies the widget to reflect its selected foliage types based on the selected foliage instances
- L47 _public function_ `class FEdModeFoliage* GetFoliageEditMode() const` — Gets FoliageEditMode. Used by the cluster details to notify changes
- L50 _public prototype_ `bool IsFoliageEditorEnabled() const;` — Will return the status of editing mode
- L53 _public prototype_ `FText GetFoliageEditorErrorText() const;` — Get the error message for this editing mode
- L56 _public prototype_ `void CustomizeToolBarPalette(FToolBarBuilder& ToolBarBuilder);` — Modes Panel Header Information
- L57 _public prototype_ `FText GetActiveToolName() const;`
- L58 _public prototype_ `FText GetActiveToolMessage() const;`
- L63 _private prototype_ `TSharedRef<SWidget> BuildToolBar();` — Creates the toolbar.
- L66 _private prototype_ `bool IsPaintTool() const;` — Checks if the tool mode is Paint.
- L69 _private prototype_ `bool IsReapplySettingsTool() const;` — Checks if the tool mode is Reapply Settings.
- L72 _private prototype_ `bool IsSelectTool() const;` — Checks if the tool mode is Select.
- L74 _private prototype_ `bool IsLassoSelectTool() const;`
- L77 _private prototype_ `bool IsPaintFillTool() const;` — Checks if the tool mode is Paint Bucket.
- L80 _private prototype_ `bool IsEraseTool() const;` — Checks if the tool mode is Erase
- L83 _private prototype_ `bool IsPlaceTool() const;` — Checks if the tool mode is Place Single Instance
- L88 _public prototype_ `void SetRadius(float InRadius);` — Sets the brush Radius for the brush.
- L92 _public prototype_ `TOptional<float> GetRadius() const;` — TOptional<float> GetRadius() const;
- L95 _public prototype_ `bool IsEnabled_BrushSize() const;` — Checks if the brush size should appear. Dependant on the current tool being used.
- L98 _public prototype_ `void SetPaintDensity(float InDensity);` — Sets the Paint Density for the brush.
- L101 _public prototype_ `TOptional<float> GetPaintDensity() const;` — Retrieves the Paint Density for the brush.
- L104 _public prototype_ `bool IsEnabled_PaintDensity() const;` — Checks if the paint density should appear. Dependant on the current tool being used.
- L107 _public prototype_ `void SetEraseDensity(float InDensity);` — Sets the Erase Density for the brush.
- L110 _public prototype_ `TOptional<float> GetEraseDensity() const;` — Retrieves the Erase Density for the brush.
- L113 _public prototype_ `bool IsEnabled_EraseDensity() const;` — Checks if the erase density should appear. Dependant on the current tool being used.
- L116 _public prototype_ `FText GetFilterText() const;` — Retrieves the text for the filters option
- L119 _public prototype_ `TSharedRef<SWidget> MakeFilterMenu();` — Create a menu for the filter options
- L122 _public prototype_ `TSharedRef<SWidget> MakeSettingsMenu();` — Create a menu for the settings option
- L125 _public prototype_ `void OnCheckStateChanged_Landscape(ECheckBoxState InState);` — Sets the filter settings for if painting will occur on Landscapes.
- L128 _public prototype_ `ECheckBoxState GetCheckState_Landscape() const;` — Retrieves the filter settings for painting on Landscapes.
- L131 _public prototype_ `void OnCheckStateChanged_SingleInstantiationMode(bool InState);` — Sets the instantiation mode settings
- L134 _public prototype_ `bool GetCheckState_SingleInstantiationMode() const;` — Retrieves the instantiation mode settings
- L137 _public prototype_ `void OnCheckStateChanged_SpawnInCurrentLevelMode(ECheckBoxState InState);` — Sets the instantiation mode settings
- L140 _public prototype_ `ECheckBoxState GetCheckState_SpawnInCurrentLevelMode() const;` — Retrieves the instantiation mode settings
- L143 _public prototype_ `FText GetTooltipText_Landscape() const;` — Retrieves the tooltip text for the landscape filter
- L146 _public prototype_ `void OnCheckStateChanged_StaticMesh(ECheckBoxState InState);` — Sets the filter settings for if painting will occur on Static Meshes.
- L149 _public prototype_ `ECheckBoxState GetCheckState_StaticMesh() const;` — Retrieves the filter settings for painting on Static Meshes.
- L152 _public prototype_ `FText GetTooltipText_StaticMesh() const;` — Retrieves the tooltip text for the static mesh filter
- L155 _public prototype_ `void OnCheckStateChanged_BSP(ECheckBoxState InState);` — Sets the filter settings for if painting will occur on BSPs.
- L158 _public prototype_ `ECheckBoxState GetCheckState_BSP() const;` — Retrieves the filter settings for painting on BSPs.
- L161 _public prototype_ `FText GetTooltipText_BSP() const;` — Retrieves the tooltip text for the BSP filter
- L164 _public prototype_ `void OnCheckStateChanged_Foliage(ECheckBoxState InState);` — Sets the filter settings for if painting will occur on foliage meshes.
- L167 _public prototype_ `ECheckBoxState GetCheckState_Foliage() const;` — Retrieves the filter settings for painting on foliage meshes.
- L170 _public prototype_ `FText GetTooltipText_Foliage() const;` — Retrieves the tooltip text for the foliage meshes filter
- L173 _public prototype_ `void OnCheckStateChanged_Translucent(ECheckBoxState InState);` — Sets the filter settings for if painting will occur on translucent meshes.
- L176 _public prototype_ `ECheckBoxState GetCheckState_Translucent() const;` — Retrieves the filter settings for painting on translucent meshes.
- L179 _public prototype_ `FText GetTooltipText_Translucent() const;` — Retrieves the tooltip text for the translucent filter
- L182 _public prototype_ `EVisibility GetVisibility_DataLayer() const;` — Checks if the Data Layer should appear.
- L185 _public prototype_ `EVisibility GetVisibility_Radius() const;` — Checks if the radius spinbox should appear. Dependant on the current tool being used.
- L188 _public prototype_ `EVisibility GetVisibility_PaintDensity() const;` — Checks if the paint density spinbox should appear. Dependant on the current tool being used.
- L191 _public prototype_ `EVisibility GetVisibility_EraseDensity() const;` — Checks if the erase density spinbox should appear. Dependant on the current tool being used.
- L194 _public prototype_ `EVisibility GetVisibility_Filters() const;` — Checks if the filters should appear. Dependant on the current tool being used.
- L197 _public prototype_ `EVisibility GetVisibility_LandscapeFilter() const;` — Checks if the Landscape filter should appear. Hidden for the Fill tool as it's not supported there.
- L200 _public prototype_ `EVisibility GetVisibility_Actions() const;` — Checks if the actions should appear. Dependant on the current tool being used.
- L203 _public prototype_ `EVisibility GetVisibility_EmptyList() const;` — Checks if the text in the empty list overlay should appear. If the list is has items but the the drag and drop override is true, it will return EVisibility::Visible.
- L206 _public prototype_ `EVisibility GetVisibility_SelectionOptions() const;` — @return Whether selecting instances is currently possible
- L209 _public prototype_ `EVisibility GetVisibility_Options() const;` — Checks if the Options section should be displayed. Dependant on the current tool being used.
- L212 _public prototype_ `EVisibility GetVisibility_SingleInstantiationMode() const;` — Checks if the SingleInstantiationMode checkbox should appear. Dependant on the current tool being used.
- L215 _public prototype_ `EVisibility GetVisibility_SingleInstantiationPlacementMode() const;` — Checks if the SingleInstantiationPlacement mode combobutton should appear. Dependant on the current tool being used.
- L218 _public prototype_ `bool GetIsEnabled_SingleInstantiationPlacementMode() const;` — Checks if the SingleInstantiationPlacement mode combobutton should be enabled. Dependant on if single instantiation mode is enabled.
- L221 _public prototype_ `EVisibility GetVisibility_SpawnInCurrentLevelMode() const;` — Checks if the SpawnInCurrentLevelMode checkbox should appear. Dependant on the current tool being used.
- L224 _public prototype_ `void OnSingleInstantiationPlacementModeChanged(int32 InMode);` — Sets the single instantiation placement mode
- L227 _public prototype_ `FText GetSingleInstantiationPlacementModeText(EFoliageSingleInstantiationPlacementMode::Type InMode) const;` — @return display text for the placement type
- L230 _public prototype_ `TSharedRef<SWidget> GetSingleInstantiationModeMenuContent();` — @return menu of all single instantiation modes
- L233 _public prototype_ `FText GetCurrentSingleInstantiationPlacementModeText() const;` — @return display text for current placement type
- L238 _public prototype_ `void OnSelectAllInstances();` — Handler for 'Select All' command
- L241 _public prototype_ `void OnSelectInvalidInstances();` — Handler for 'Select Invalid Instances' command
- L244 _public prototype_ `void OnDeselectAllInstances();` — Handler for 'Deselect All' command
- L247 _public prototype_ `void OnMoveSelectedInstancesToActorEditorContext();` — Handler for 'Move to Current Editor Context' command
- L250 _public prototype_ `FText GetTotalInstanceCountTooltipText() const;` — Tooltip text for 'Instance Count" column
- L253 _public prototype_ `void HandleOnToolChanged();` — Handler to trigger a refresh of the details view when the active tool changes
- L255 _public prototype_ `void ExecuteOnAllCurrentLevelFoliageTypes(TFunctionRef<void(const TArray<const UFoliageType*>&)> ExecuteFunc);`
- L259 _private member_ `TSharedPtr<class SFoliagePalette> FoliagePalette;` — Palette of available foliage types
- L262 _private member_ `TSharedPtr<class SErrorText> ErrorText;` — Current error message
- L265 _private member_ `FEdModeFoliage* FoliageEditMode;` — Pointer to the foliage edit mode.

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace EFoliageSingleInstantiationPlacementMode`
- L25 _typedef_ `typedef TSharedPtr<FFoliageMeshUIInfo> FFoliageMeshUIInfoPtr;` — should match typedef in FoliageEdMode.h

### `Source/Editor/FoliageEdit/Private/SFoliagePalette.h` (Private)


#### class `SFoliagePalette`  
`class SFoliagePalette : public SCompoundWidget`  
_L58-328_
- inherits: `SCompoundWidget`
- desc: The palette of foliage types available for use by the foliage edit mode
- L61 _public function_ `SLATE_BEGIN_ARGS(SFoliagePalette)`
- L62 _public prototype_ `SLATE_ARGUMENT(FEdModeFoliage*, FoliageEdMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L66 _public prototype_ `~SFoliagePalette();`
- L69 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L72 _public prototype_ `void UpdatePalette(bool bRebuildItems = false);` — Updates the foliage palette, optionally doing a full rebuild of the items in the palette as well
- L75 _public prototype_ `void UpdateThumbnailForType(UFoliageType* FoliageType);` — Updates the thumbnail for the given foliage type in the palette
- L77 _public prototype_ `bool AnySelectedTileHovered() const;`
- L78 _public prototype_ `void ActivateAllSelectedTypes(bool bActivate) const;`
- L81 _public prototype_ `bool IsActiveViewMode(EFoliagePaletteViewMode::Type ViewMode) const;` — @return True if the given view mode is the active view mode
- L84 _public prototype_ `bool ShouldShowTooltips() const;` — @return True if tooltips should be shown when hovering over foliage type items in the palette
- L87 _public prototype_ `FText GetSearchText() const;` — @return The current search filter text
- L90 _public prototype_ `UFoliageType* AddFoliageType(const FAssetData& AssetData, bool bPlaceholderAsset = false);` — Adds the foliage type asset to the instanced foliage actor's list of types.
- L93 _public prototype_ `void ReflectSelectionInPalette();` — Updates the selection of foliage types in the palette based on the selected foliage instances.
- L96 _private prototype_ `void AddFoliageTypePicker(const FAssetData& AssetData);`
- L99 _private prototype_ `void BindCommands();` — Binds commands used by the palette
- L102 _private prototype_ `void RefreshActivePaletteViewWidget();` — Refreshes the active palette view widget
- L105 _private prototype_ `TSharedRef<class SWidgetSwitcher> CreatePaletteViews();` — Creates the palette views
- L108 _private prototype_ `void GetPaletteItemFilterString(FFoliagePaletteItemModelPtr PaletteItemModel, TArray<FString>& OutArray) const;` — Adds the displayed name of the foliage type for filtering
- L111 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);` — Handles changes to the search filter text
- L114 _private prototype_ `TSharedRef<SWidget> GetAddFoliageTypePicker();` — Gets the asset picker for adding a foliage type.
- L117 _private prototype_ `EVisibility GetAddFoliageTypeButtonTextVisibility() const;` — Gets the visibility of the Add Foliage Type text in the header row button
- L120 _private prototype_ `ECheckBoxState GetState_AllMeshes() const;` — Toggle whether all foliage types are active
- L121 _private prototype_ `void OnCheckStateChanged_AllMeshes(ECheckBoxState InState);`
- L124 _private prototype_ `void HandleOnToolChanged();` — Handler to trigger a refresh of the details view when the active tool changes
- L126 _private prototype_ `void OnExternalContentResolved(const FGuid& Identifier, const FAssetData& PlaceholderAsset, const FAssetData& ResolvedAsset);`
- L129 _private prototype_ `void SetViewMode(EFoliagePaletteViewMode::Type NewViewMode);` — Sets the view mode of the palette
- L132 _private prototype_ `void ToggleShowTooltips();` — Sets whether to show tooltips when hovering over foliage type items in the palette
- L135 _private prototype_ `FReply OnToggleViewModeClicked();` — Switches the palette display between the tile and tree view
- L138 _private prototype_ `int32 GetActiveViewIndex() const;` — @return The index of the view widget to display
- L141 _private prototype_ `void OnSelectionChanged(FFoliagePaletteItemModelPtr Item, ESelectInfo::Type SelectInfo);` — Handler for selection changes in either view
- L144 _private prototype_ `void OnItemDoubleClicked(FFoliagePaletteItemModelPtr Item) const;` — Toggle the activation state of a type on a double-click
- L147 _private prototype_ `TSharedRef<SWidget> GetViewOptionsMenuContent();` — Creates the view options menu
- L149 _private prototype_ `TSharedPtr<SListView<FFoliagePaletteItemModelPtr>> GetActiveViewWidget() const;`
- L152 _private prototype_ `EVisibility GetDropFoliageHintVisibility() const;` — Gets the visibility of the "Drop Foliage Here" prompt for when the palette is empty
- L155 _private prototype_ `EVisibility GetFoliageDropTargetVisibility() const;` — Gets the visibility of the drag-drop zone overlay
- L158 _private prototype_ `FReply HandleFoliageDropped(const FGeometry& DropZoneGeometry, const FDragDropEvent& DragDropEvent);` — Handles dropping of a mesh or foliage type into the palette
- L163 _private prototype_ `void OnIncludeNonFoliageActors(bool bOnlyCurrentLevel);` — Finds actors with class matching foliage type and merges them into foliage instances
- L166 _private prototype_ `void OnExcludeFoliageActors(bool bOnlyCurrentLevel);` — Excludes actors from matching foliage type and make them regular actors.
- L169 _private prototype_ `TSharedPtr<SWidget> ConstructFoliageTypeContextMenu();` — @return the SWidget containing the context menu
- L172 _private prototype_ `void OnSaveSelected();` — Saves a temporary non-asset foliage type (created from a static mesh) as a foliage type asset
- L175 _private prototype_ `bool OnCanSaveAnySelectedAssets() const;` — @return True if all selected types are non-assets
- L178 _private prototype_ `bool AreAnyNonAssetTypesSelected() const;` — @return True if any of the selected types are non-assets
- L181 _private prototype_ `void OnActivateFoliageTypes();` — Handler for the 'Activate' command
- L182 _private prototype_ `bool OnCanActivateFoliageTypes() const;`
- L185 _private prototype_ `void OnDeactivateFoliageTypes();` — Handler for the 'Deactivate' command
- L186 _private prototype_ `bool OnCanDeactivateFoliageTypes() const;`
- L189 _private prototype_ `void FillReplaceFoliageTypeSubmenu(FMenuBuilder& MenuBuilder);` — Fills 'Replace' menu command
- L192 _private prototype_ `void OnReplaceFoliageTypeSelected(const struct FAssetData& AssetData);` — Handler for 'Replace' command
- L195 _private prototype_ `void OnRemoveFoliageType();` — Handler for 'Remove' command
- L198 _private prototype_ `void OnShowFoliageTypeInCB();` — Handler for 'Show in CB' command
- L201 _private prototype_ `void OnSelectAllInstances();` — Handler for 'Select All' command
- L204 _private prototype_ `void OnDeselectAllInstances();` — Handler for 'Deselect All' command
- L207 _private prototype_ `void OnSelectInvalidInstances();` — Handler for 'Select Invalid Instances' command
- L210 _private prototype_ `void ExecuteOnSelectedItemFoliageTypes(TFunctionRef<void(const TArray<const UFoliageType*>&)> ExecuteFunc);` — Executes Function on gathered list of foliage types from the selected palette items
- L213 _private prototype_ `bool CanSelectInstances() const;` — @return Whether selecting instances is currently possible
- L216 _private prototype_ `void SelectFoliageTypesInPalette(const TArray<const UFoliageType*>& FoliageTypes);` — Selects Foliage Type in palette
- L221 _private prototype_ `TSharedRef<ITableRow> GenerateTile(FFoliagePaletteItemModelPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Creates a thumbnail tile for the given foliage type
- L224 _private prototype_ `float GetScaledThumbnailSize() const;` — Gets the scaled thumbnail tile size
- L227 _private prototype_ `float GetThumbnailScale() const;` — Gets the current scale of the thumbnail tiles
- L230 _private prototype_ `void SetThumbnailScale(float InScale);` — Sets the current scale of the thumbnail tiles
- L233 _private prototype_ `bool GetThumbnailScaleSliderEnabled() const;` — Gets whether the thumbnail scaling slider is visible
- L238 _private prototype_ `TSharedRef<ITableRow> TreeViewGenerateRow(FFoliagePaletteItemModelPtr Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row widget for foliage mesh item
- L241 _private prototype_ `void TreeViewGetChildren(FFoliagePaletteItemModelPtr Item, TArray<FFoliagePaletteItemModelPtr>& OutChildren);` — Generates a list of children items for foliage item
- L244 _private prototype_ `FText GetMeshesHeaderText() const;` — Text for foliage meshes list header
- L247 _private prototype_ `EColumnSortMode::Type GetMeshColumnSortMode() const;` — Mesh list sorting support
- L248 _private prototype_ `void OnMeshesColumnSortModeChanged(EColumnSortPriority::Type InPriority, const FName& InColumnName, EColumnSortMode::Type InSortMode);`
- L251 _private prototype_ `FText GetTotalInstanceCountTooltipText() const;` — Tooltip text for 'Instance Count" column
- L256 _private prototype_ `void RefreshDetailsWidget();` — Refreshes the mesh details widget to match the current selection
- L259 _private prototype_ `bool GetIsPropertyEditingEnabled() const;` — Gets whether property editing is enabled
- L262 _private prototype_ `FText GetDetailsNameAreaText() const;` — Gets the text for the details area header
- L265 _private prototype_ `FText GetShowHideDetailsTooltipText() const;` — Gets the text for the show/hide details button tooltip
- L268 _private prototype_ `const FSlateBrush* GetShowHideDetailsImage() const;` — Gets the image for the show/hide details button
- L271 _private prototype_ `void OnShowHideDetailsClicked(const ECheckBoxState ) const;` — Handles the show/hide details button click
- L274 _private prototype_ `EVisibility GetUneditableFoliageTypeWarningVisibility() const;` — Gets the visibility of the uneditable blueprint foliage type warning
- L277 _private prototype_ `void OnEditFoliageTypeBlueprintHyperlinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata);` — Handles the click for the uneditable blueprint foliage type warning
- L281 _private prototype_ `EActiveTimerReturnType UpdatePaletteItems(double InCurrentTime, float InDeltaTime);` — Active timer handler to update the items in the palette
- L284 _private typedef_ `typedef TTextFilter<FFoliagePaletteItemModelPtr> FoliageTypeTextFilter;`
- L285 _private member_ `TSharedPtr<FoliageTypeTextFilter> TypeFilter;`
- L288 _private member_ `TArray<FFoliagePaletteItemModelPtr> PaletteItems;` — All the items in the palette (unfiltered)
- L291 _private member_ `TArray<FFoliagePaletteItemModelPtr> FilteredItems;` — The filtered list of types to display in the palette
- L294 _private member_ `TSharedPtr<class SWidgetSwitcher> WidgetSwitcher;` — Switches between the thumbnail and tree views
- L297 _private member_ `TSharedPtr<class SPositiveActionButton> AddFoliageTypeCombo;` — The Add Foliage Type combo button
- L300 _private member_ `TSharedPtr<class SHeaderRow> TreeViewHeaderRow;` — The header row of the foliage mesh tree
- L303 _private member_ `TSharedPtr<SFoliageTypeTileView> TileViewWidget;` — Foliage type thumbnails widget
- L306 _private member_ `TSharedPtr<SFoliageTypeTreeView> TreeViewWidget;` — Foliage type tree widget
- L309 _private member_ `TSharedPtr<class IDetailsView> DetailsWidget;` — Foliage mesh details widget
- L312 _private member_ `TSharedPtr<class SSearchBox> SearchBoxPtr;` — Foliage items search box widget
- L315 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Command list for binding functions for the context menu.
- L318 _private member_ `TSharedPtr<class FAssetThumbnailPool> ThumbnailPool;` — Thumbnail pool for rendering mesh thumbnails
- L320 _private member_ `FEdModeFoliage* FoliageEditMode;`
- L322 _private member_ `TMap<FGuid, TArray<TWeakObjectPtr<UFoliageType>>> ExternalContentFoliageTypes;`
- L324 _private member_ `bool bItemsNeedRebuild : 1;`
- L325 _private member_ `bool bIsUneditableFoliageTypeSelected : 1;`
- L327 _private member_ `bool bIsRebuildTimerRegistered : 1;`

#### Free symbols / members of external scopes

- L48 _typedef_ `typedef TSharedPtr<FFoliagePaletteItemModel> FFoliagePaletteItemModelPtr;`
- L49 _typedef_ `typedef STreeView<FFoliagePaletteItemModelPtr> SFoliageTypeTreeView;`
- L50 _typedef_ `typedef STileView<FFoliagePaletteItemModelPtr> SFoliageTypeTileView;`
- L52 _namespace_ `namespace FoliagePaletteConstants`
- L54 _variable_ `const FInt32Interval ThumbnailSizeRange(32, 128);` (scope `FoliagePaletteConstants`)

### `Source/Editor/FoliageEdit/Public/FoliageEditModule.h` (Public)


#### class `IFoliageEditModule`  
`class IFoliageEditModule : public IFoliageEditModuleBase`  
_L17-20_
- inherits: `IFoliageEditModuleBase`
- desc: Foliage Edit mode module interface

#### Free symbols / members of external scopes

- L10 _externvar_ `extern const FName FoliageEditAppIdentifier;`

### `Source/Editor/FoliageEdit/Public/FoliageEditUtility.h` (Public)


#### class `FFoliageEditUtility`  
`class FFoliageEditUtility`  
_L19-36_
- L23 _public prototype_ `static UFoliageType* SaveFoliageTypeObject(UFoliageType* Settings, bool bPlaceholderAsset = false);` — Save the foliage type object. If it isn't an asset, will prompt the user for a location to save the new asset.
- L31 _public prototype_ `static UFoliageType* DuplicateFoliageTypeToNewPackage(const FString& InPackageName, UFoliageType* InFoliageType);` — Copies the provided FoliageType to a new asset @param 	InPackageName 	The name of the new asset @param 	InFoliageType 	The FoliageType to copy @return 	The new FoliageType
- L33 _public prototype_ `static void ReplaceFoliageTypeObject(UWorld* InWorld, UFoliageType* OldType, UFoliageType* NewType);`
- L35 _public prototype_ `static void MoveActorFoliageInstancesToLevel(ULevel* InTargetLevel, AActor* InIFA = nullptr);`

### `Source/Editor/FoliageEdit/Public/FoliageEditorSubsystem.h` (Public)


#### class `UFoliageEditorSubsystem`  
`class UFoliageEditorSubsystem : public UEditorSubsystem`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L17 _private prototype_ `UFoliageEditorSubsystem();`
- L19 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L20 _public prototype_ `virtual void Deinitialize() override;`
- L23 _private prototype_ `void OnActorMoved(AActor* InActor);`
- L24 _private prototype_ `void OnActorOuterChanged(AActor* InActor, UObject* OldOuter);`
- L25 _private prototype_ `void OnActorDeleted(AActor* InActor);`
- L26 _private prototype_ `void OnPostApplyLevelOffset(ULevel* InLevel, UWorld* InWorld, const FVector& InOffset, bool bWorldShift);`
- L27 _private prototype_ `void OnPostApplyLevelTransform(ULevel* InLevel, const FTransform& InTransform);`
- L28 _private prototype_ `void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS);`

### `Source/Editor/FoliageEdit/Public/FoliageType_ActorThumbnailRenderer.h` (Public)


#### class `UFoliageType_ActorThumbnailRenderer`  
`class UFoliageType_ActorThumbnailRenderer : public UBlueprintThumbnailRenderer`  
_L22-33_
- reflection: `UCLASS(CustomConstructor, Config = Editor)`
- inherits: `UBlueprintThumbnailRenderer`
- L26 _private function_ `UFoliageType_ActorThumbnailRenderer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L31 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;` — UThumbnailRenderer implementation
- L32 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`

### `Source/Editor/FoliageEdit/Public/FoliageType_ISMThumbnailRenderer.h` (Public)


#### class `UFoliageType_ISMThumbnailRenderer`  
`class UFoliageType_ISMThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L22-39_
- reflection: `UCLASS(CustomConstructor, Config=Editor)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L26 _private function_ `UFoliageType_ISMThumbnailRenderer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) , ThumbnailScene(nullptr)`
- L32 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;` — UThumbnailRenderer implementation
- L33 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L35 _private prototype_ `virtual void BeginDestroy() override;` — UObject implementation
- L38 _private member_ `class FStaticMeshThumbnailScene* ThumbnailScene;`

### `Source/Editor/FoliageEdit/Public/ProceduralFoliageEditorLibrary.h` (Public)


#### class `UProceduralFoliageEditorLibrary`  
`class UProceduralFoliageEditorLibrary : public UBlueprintFunctionLibrary`  
_L23-39_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L29 _public prototype_ `static void ResimulateProceduralFoliageVolumes(const TArray<AProceduralFoliageVolume*>& ProceduralFoliageVolumes);` — `UFUNCTION(BlueprintCallable, Category="Foliage")`
- L32 _public prototype_ `static void ResimulateProceduralFoliageComponents(const TArray<UProceduralFoliageComponent*>& ProceduralFoliageComponents);` — `UFUNCTION(BlueprintCallable, Category="Foliage")`
- L35 _public prototype_ `static void ClearProceduralFoliageVolumes(const TArray<AProceduralFoliageVolume*>& ProceduralFoliageVolumes);` — `UFUNCTION(BlueprintCallable, Category="Foliage")`
- L38 _public prototype_ `static void ClearProceduralFoliageComponents(const TArray<UProceduralFoliageComponent*>& ProceduralFoliageComponents);` — `UFUNCTION(BlueprintCallable, Category = "Foliage")`
