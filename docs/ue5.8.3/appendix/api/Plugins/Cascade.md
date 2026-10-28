# Plugins / Cascade

- module root: `Plugins/FX/Cascade/Source/Cascade`
- headers: 13; symbols: 597
- symbol kinds: class=12, delegate=1, enum=4, enumerator=31, externvar=1, function=27, member=217, prototype=291, struct=12, typedef=1
- DynamicallyLoadedModuleNames: MainFrame, PropertyEditor
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, AssetDefinition, ContentBrowser, Core, CoreUObject, DistCurveEditor, EditorFramework, Engine, InputCore, PhysicsCore, RHI, RenderCore, Slate, SlateCore, ToolMenus, UnrealEd
- PublicIncludePathModuleNames: DistCurveEditor, UnrealEd

### `Plugins/FX/Cascade/Source/Cascade/Classes/CascadeConfiguration.h` (Public)


#### struct `FModuleMenuMapper`  
`struct FModuleMenuMapper`  
_L18-28_
- reflection: `USTRUCT()`
- desc: Module-to-TypeData mapping helper.
- L23 _public member_ `FString ObjName;` — `UPROPERTY()`
- L26 _public member_ `TArray<FString> InvalidObjNames;` — `UPROPERTY()`

#### class `UCascadeConfiguration`  
`class UCascadeConfiguration : public UObject`  
_L31-62_
- reflection: `UCLASS(hidecategories=Object, config=Editor)`
- inherits: `UObject`
- L40 _private member_ `TArray<struct FModuleMenuMapper> ModuleMenu_TypeDataToBaseModuleRejections;` — `UPROPERTY(EditAnywhere, config, Category=Configure)` — TypeData-to-base module mappings. These will disallow complete 'sub-menus' depending on the TypeData utilized.
- L44 _private member_ `TArray<struct FModuleMenuMapper> ModuleMenu_TypeDataToSpecificModuleRejections;` — `UPROPERTY(EditAnywhere, config, Category=Configure)` — Module-to-TypeData mappings.
- L48 _private member_ `TArray<FString> ModuleMenu_ModuleRejections;` — `UPROPERTY(EditAnywhere, config, Category=Configure)` — Modules that Cascade should ignore in the menu system.
- L51 _private prototype_ `bool IsModuleTypeValid(FName TypeDataName, FName ModuleName);` — Returns true if the given module class name is valid for the type data class name.
- L55 _private prototype_ `void CacheModuleRejections();` — Cache module rejections for fast runtime lookups.
- L58 _private member_ `TSet<FName> ModuleRejections;` — If a module class name is in this list it should be rejected.
- L61 _private member_ `TMap<FName,TSet<FName> > TypeDataModuleRejections;` — If a module class name is in the set associated with a type data class name it should be rejected.

### `Plugins/FX/Cascade/Source/Cascade/Classes/CascadeParticleSystemComponent.h` (Public)


#### class `UCascadeParticleSystemComponent`  
`class UCascadeParticleSystemComponent : public UParticleSystemComponent`  
_L14-41_
- reflection: `UCLASS(hidecategories=Object, hidecategories=Physics, hidecategories=Collision, editinlinenew)`
- inherits: `UParticleSystemComponent`
- desc: Used to provide an extended particle system component to allow collision to function in the preview window.
- L20 _public member_ `class FCascadeEdPreviewViewportClient* CascadePreviewViewportPtr;`
- L23 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L32 _public prototype_ `void CascadeTickComponent(float DeltaTime, enum ELevelTick TickType);` — Updates time dependent state for this component, called from within Cascade. Requires component to be registered @param DeltaTime - The time since the last tick. @param TickType - The kind of tick this is
- L35 _public prototype_ `virtual bool ParticleLineCheck(FHitResult& Hit, AActor* SourceActor, const FVector& End, const FVector& Start, const FVector& Extent, const FCollisionObjectQueryParams&) override;` — Collision Handling...
- L37 _public function_ `virtual bool Editor_CanBeTickManaged()const`
- L40 _protected prototype_ `virtual void UpdateLODInformation() override;`

### `Plugins/FX/Cascade/Source/Cascade/Private/AssetDefinition_ParticleSystem.h` (Private)


#### class `UAssetDefinition_ParticleSystem`  
`class UAssetDefinition_ParticleSystem : public UAssetDefinitionDefault`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/FX/Cascade/Source/Cascade/Private/Cascade.h` (Private)


#### struct `FParticleEmitterThumbnail`  
`struct FParticleEmitterThumbnail`  
_L62-72_
- L64 _public function_ `FParticleEmitterThumbnail() : Material(nullptr) , Texture(nullptr)`
- L69 _public member_ `TWeakObjectPtr<UMaterialInterface> Material;`
- L71 _public member_ `TObjectPtr<UTextureRenderTarget2D> Texture;` — Texture holding the material thumbnail for canvas.  Note it is the only thing we hold onto

#### class `FCascade`  
`class FCascade : public ICascade, public FGCObject, public FTickableEditorObject, public FNotifyHook, public FCurveEdNotifyInterface, public FEditorUndoClient`  
_L80-526_
- inherits: `ICascade,FGCObject,FTickableEditorObject,FNotifyHook,FCurveEdNotifyInterface,FEditorUndoClient`
- L83 _public prototype_ `FCascade();`
- L85 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L86 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L87 _public prototype_ `TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& SpawnTabArgs, FName TabIdentifier);`
- L90 _public prototype_ `virtual ~FCascade();` — Destructor
- L93 _public prototype_ `void InitCascade(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit);` — Edits the specified ParticleSystem object
- L96 _public prototype_ `UParticleSystem* GetParticleSystem() const;` — Returns the ParticleSystem asset inspected by the editor
- L99 _public prototype_ `UCascadeParticleSystemComponent* GetParticleSystemComponent() const;` — Returns the particle system component
- L102 _public prototype_ `UVectorFieldComponent* GetLocalVectorFieldComponent() const;` — Returns the vector field component
- L105 _public prototype_ `FFXSystemInterface* GetFXSystem() const;` — Returns the FX system
- L108 _public prototype_ `UParticleEmitter* GetSelectedEmitter() const;` — Returns the currently selected emitter
- L111 _public prototype_ `UParticleModule* GetSelectedModule() const;` — Returns the currently selected module
- L114 _public prototype_ `int32 GetSelectedModuleIndex();` — Returns the index of the currently selected module
- L117 _public prototype_ `int32 GetCurrentlySelectedLODLevelIndex() const;` — Return the index of the currently selected LOD level
- L120 _public prototype_ `UParticleLODLevel* GetCurrentlySelectedLODLevel() const;` — Return the currently selected LOD level
- L123 _public prototype_ `UParticleLODLevel* GetCurrentlySelectedLODLevel(UParticleEmitter* InEmitter);` — Return the currently selected LOD level
- L126 _public prototype_ `UCascadeOptions* GetEditorOptions() const;` — Returns the Cascade editor options
- L129 _public prototype_ `UCascadeConfiguration* GetEditorConfiguration() const;` — Returns the Cascade editor configuration
- L132 _public prototype_ `TSharedPtr<IDistributionCurveEditor> GetCurveEditor();` — Returns the curve editor
- L135 _public prototype_ `TSharedPtr<SCascadePreviewViewport> GetPreviewViewport();` — Returns the preview viewport
- L138 _public prototype_ `bool GetIsSoloing() const;` — IsSoloing accesors
- L139 _public prototype_ `void SetIsSoloing(bool bIsSoloing);`
- L142 _public prototype_ `int32 GetDetailMode() const;` — Returns the current detail mode
- L145 _public prototype_ `EParticleSignificanceLevel GetRequiredSignificance()const;` — Returns the required significance for the fx in the cascade viewport.
- L148 _public prototype_ `bool GetIsModuleShared(UParticleModule* Module);` — Returns true if the module is shared
- L151 _public prototype_ `void ToggleEnableOnSelectedEmitter(UParticleEmitter* InEmitter);` — Toggle the enabled setting on the given emitter
- L154 _public prototype_ `void ForceUpdate();` — Refreshes all viewports and controls
- L163 _public prototype_ `bool AddSelectedToGraph(TArray<const FCurveEdEntry*>& OutCurveEntries);` — Adds curves belonging to the selected module to the curve editor @param	OutCurveEntries	Adds the curves which are for this graph node @return	true, if new curves were added to the graph, otherwise they were already present
- L170 _public prototype_ `void ShowDesiredCurvesOnly(const TArray<const FCurveEdEntry*>& InCurveEntries);` — Makes sure only the specified curves are shown in the graph, all others are hidden @param	InCurveEntries	The curves which should be visible
- L173 _public prototype_ `void SetSelectedEmitter(UParticleEmitter* NewSelectedEmitter, bool bIsSimpleAssignment = false);` — Methods for setting the currently selected object
- L174 _public prototype_ `void SetSelectedModule(UParticleModule* NewSelectedModule);`
- L175 _public prototype_ `void SetSelectedModule(UParticleEmitter* NewSelectedEmitter, UParticleModule* NewSelectedModule);`
- L178 _public prototype_ `void SetSelection(TArray<UObject*> SelectedObjects);` — Assigns the currently selected nodes to the property control
- L181 _public prototype_ `TArray<UClass*>& GetParticleModuleBaseClasses();` — Return module class info
- L182 _public prototype_ `TArray<UClass*>& GetParticleModuleClasses();`
- L185 _public prototype_ `void SetCopyEmitter(UParticleEmitter* NewEmitter);` — Caches the emitter/module to be copied
- L186 _public prototype_ `void SetCopyModule(UParticleEmitter* NewEmitter, UParticleModule* NewModule);`
- L189 _public prototype_ `TArray<UParticleModule*>& GetDraggedModuleList();` — Returns the dragged module list
- L192 _public prototype_ `void MoveSelectedEmitter(int32 MoveAmount);` — Move the selected emitter by MoveAmount in the array of emitters
- L195 _public prototype_ `bool InsertModule(UParticleModule* Module, UParticleEmitter* TargetEmitter, int32 TargetIndex, bool bSetSelected);` — Inserts a module at the specified index
- L198 _public prototype_ `void CopyModuleToEmitter(UParticleModule* pkSourceModule, UParticleEmitter* pkTargetEmitter, UParticleSystem* pkTargetSystem, int32 TargetIndex);` — Copies a module to an emitter
- L201 _public prototype_ `void OnCustomModuleOption(int32 Idx);` — Toolbar/menu command methods
- L202 _public prototype_ `void OnNewModule(int32 Idx);`
- L203 _public prototype_ `void OnNewEmitter();`
- L204 _public prototype_ `void OnRestartInLevel();`
- L205 _public prototype_ `void OnDeleteEmitter();`
- L206 _public prototype_ `void OnDeleteModule(bool bConfirm);`
- L207 _public prototype_ `void OnJumpToHigherLOD();`
- L208 _public prototype_ `void OnJumpToLowerLOD();`
- L209 _public prototype_ `void OnUndo();`
- L210 _public prototype_ `void OnRedo();`
- L213 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L214 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L215 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L216 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L219 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L225 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L226 _public prototype_ `virtual FString GetReferencerName() const override;`
- L229 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L230 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L231 _public prototype_ `virtual TStatId GetStatId() const override;`
- L236 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L237 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyChain) override;`
- L238 _public prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FEditPropertyChain* PropertyChain) override;`
- L241 _public prototype_ `virtual void PreEditCurve(TArray<UObject*> CurvesAboutToChange) override;` — FCurveEdNotifyInterface
- L242 _public prototype_ `virtual void PostEditCurve() override;`
- L243 _public prototype_ `virtual void MovedKey() override;`
- L244 _public prototype_ `virtual void DesireUndo() override;`
- L245 _public prototype_ `virtual void DesireRedo() override;`
- L252 _public prototype_ `static bool ConvertAllModulesToSeeded(UParticleSystem* ParticleSystem);` — Convert all the modules in this particle system to their random seed variant if available @return	bool			true if successful, false if not
- L254 _public prototype_ `static void OnComponentActivationChange(UParticleSystemComponent* PSC, bool bActivated);`
- L256 _public function_ `FParticleEmitterThumbnailMap& GetEmitterToThumbnailMap()`
- L260 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L261 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L265 _private prototype_ `static TSharedRef<SWidget> GenerateAnimSpeedMenuContent(TSharedRef<FUICommandList> InCommandList);` — Generates menu for the AnimSpeed sub menu
- L268 _private prototype_ `void CreateInternalWidgets();` — Creates all internal widgets for the tabs to point at
- L271 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the ParticleSystem editor
- L274 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L286 _private prototype_ `static bool ConvertModuleToSeeded(UParticleSystem* ParticleSystem, UParticleEmitter* InEmitter, int32 InModuleIdx, UClass* InSeededClass, bool bInUpdateModuleLists);` — Convert the given module to its random seed variant. @param	InEmitter				The emitter to convert @param	InModuleIdx				The index of the module to convert @param	InSeededClass			The seeded variant class @param	bInUpdateModuleLists	If true, update the module lists after the conversion @return	bool					true if successful, false if not
- L289 _private prototype_ `void InitParticleModuleClasses();` — Initializes the lists of module classes
- L292 _private prototype_ `TOptional<int32> GetMaxLOD() const;` — Delegate callbacks for the LOD toolbar spinbox
- L293 _private prototype_ `TOptional<int32> GetCurrentLOD() const;`
- L294 _private prototype_ `void OnCurrentLODChanged(int32 NewLOD);`
- L297 _private prototype_ `void MotionRadiusCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);` — Callback for committing a motion radius
- L300 _private prototype_ `void SphereRadiusCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);` — Callback for committing a sphere radius
- L303 _private prototype_ `void EmitterNameCommitted(const FText& CommentText, ETextCommit::Type CommitInfo);` — Callback for renaming an emitter
- L306 _private prototype_ `void UpdateLODLevel();` — Sets the LOD level to the currently selected LOD index
- L309 _private prototype_ `void SetLODValue(int32 LODSetting);` — Changes the LOD level
- L312 _private prototype_ `void ReassociateParticleSystem() const;` — Removes and then Readds the particle system to the preview scene
- L315 _private prototype_ `void RestartParticleSystem();` — Restarts the particle system
- L318 _private prototype_ `bool PromptForCancellingSoloingMode( const FText& InOperationDesc);` — Prompt the user for canceling soloing mode to perform the selected operation
- L321 _private prototype_ `bool DuplicateEmitter(UParticleEmitter* SourceEmitter, UParticleSystem* DestSystem, bool bShare);` — Duplicates an existing emitter
- L324 _private prototype_ `void AddNewEmitter(int32 PositionOffset);` — Adds a new emitter
- L327 _private prototype_ `void DuplicateModule(bool bDoShare, bool bUseHighest);` — Duplicates an existing module
- L330 _private prototype_ `void ExportSelectedEmitter();` — Export the selected emitter for importing into another particle system
- L333 _private prototype_ `void RegenerateLowestLOD(bool bDupeHighest);` — Regenerates the lowest LOD
- L336 _private prototype_ `void AddLOD(bool bBeforeCurrent);` — Adds a new LOD
- L339 _private prototype_ `void SetSelectedInCurveEditor();` — Sets the selection in the curve editor
- L342 _private prototype_ `bool BeginTransaction(const FText& Description);` — Undo/Redo support
- L343 _private prototype_ `bool EndTransaction(const FText& Description);`
- L346 _private prototype_ `void ModifySelectedObjects();` — Modify methods
- L347 _private prototype_ `void ModifyParticleSystem(bool bInModifyEmitters = false);`
- L348 _private prototype_ `void ModifyEmitter(UParticleEmitter* Emitter);`
- L351 _private prototype_ `static TSharedRef<SWidget> GenerateBoundsMenuContent(TSharedRef<FUICommandList> InCommandList);` — Generates menus for the Bounds toolbar button
- L354 _private prototype_ `void ToggleDrawOption(int32 Element);` — View option helper methods
- L355 _private prototype_ `bool IsDrawOptionEnabled(int32 Element) const;`
- L358 _private prototype_ `void OnViewOriginAxis();` — Toolbar/menu command methods
- L359 _private prototype_ `bool IsViewOriginAxisChecked() const;`
- L360 _private prototype_ `void OnViewParticleCounts();`
- L361 _private prototype_ `bool IsViewParticleCountsChecked() const;`
- L362 _private prototype_ `void OnViewParticleEventCounts();`
- L363 _private prototype_ `bool IsViewParticleEventCountsChecked() const;`
- L364 _private prototype_ `void OnViewParticleTimes();`
- L365 _private prototype_ `bool IsViewParticleTimesChecked() const;`
- L366 _private prototype_ `void OnViewParticleMemory();`
- L367 _private prototype_ `bool IsViewParticleMemoryChecked() const;`
- L368 _private prototype_ `void OnViewSystemCompleted();`
- L369 _private prototype_ `bool IsViewSystemCompletedChecked() const;`
- L370 _private prototype_ `void OnViewEmitterTickTimes();`
- L371 _private prototype_ `bool IsViewEmitterTickTimesChecked() const;`
- L372 _private prototype_ `void OnViewGeometry();`
- L373 _private prototype_ `bool IsViewGeometryChecked() const;`
- L374 _private prototype_ `void OnViewGeometryProperties();`
- L375 _private prototype_ `bool IsViewGeometryPropertiesChecked() const;`
- L376 _private prototype_ `void OnViewLocalVectorFields();`
- L377 _private prototype_ `bool IsViewLocalVectorFieldsChecked() const;`
- L378 _private prototype_ `void OnRestartSimulation();`
- L379 _private prototype_ `void OnSaveThumbnailImage();`
- L380 _private prototype_ `void OnToggleOrbitMode();`
- L381 _private prototype_ `bool IsToggleOrbitModeChecked() const;`
- L382 _private prototype_ `void OnToggleMotion();`
- L383 _private prototype_ `bool IsToggleMotionChecked() const;`
- L384 _private prototype_ `void OnSetMotionRadius();`
- L385 _private prototype_ `void OnViewMode(EViewModeIndex ViewMode);`
- L386 _private prototype_ `bool IsViewModeChecked(EViewModeIndex ViewMode) const;`
- L387 _private prototype_ `void OnToggleBounds();`
- L388 _private prototype_ `bool IsToggleBoundsChecked() const;`
- L389 _private prototype_ `void OnToggleBoundsSetFixedBounds();`
- L390 _private prototype_ `void OnTogglePostProcess();`
- L391 _private prototype_ `bool IsTogglePostProcessChecked() const;`
- L392 _private prototype_ `void OnToggleGrid();`
- L393 _private prototype_ `bool IsToggleGridChecked() const;`
- L394 _private prototype_ `void OnPlay();`
- L395 _private prototype_ `bool IsPlayChecked() const;`
- L396 _private prototype_ `void OnAnimSpeed(float Speed);`
- L397 _private prototype_ `bool IsAnimSpeedChecked(float Speed) const;`
- L398 _private prototype_ `void OnToggleLoopSystem();`
- L399 _private prototype_ `bool IsToggleLoopSystemChecked() const;`
- L400 _private prototype_ `void OnToggleRealtime();`
- L401 _private prototype_ `bool IsToggleRealtimeChecked() const;`
- L402 _private prototype_ `void OnBackgroundColor();`
- L403 _private prototype_ `void OnToggleWireframeSphere();`
- L404 _private prototype_ `bool IsToggleWireframeSphereChecked() const;`
- L405 _private prototype_ `void OnRegenerateLowestLODDuplicatingHighest();`
- L406 _private prototype_ `void OnRegenerateLowestLOD();`
- L407 _private prototype_ `void OnDetailMode(EDetailMode DetailMode);`
- L408 _private prototype_ `bool IsDetailModeChecked(EDetailMode DetailMode) const;`
- L409 _private prototype_ `void OnSignificance(EParticleSignificanceLevel InSignificance);`
- L410 _private prototype_ `bool IsSignificanceChecked(EParticleSignificanceLevel InSignificance) const;`
- L411 _private prototype_ `void OnJumpToHighestLOD();`
- L412 _private prototype_ `void OnAddLODAfterCurrent();`
- L413 _private prototype_ `void OnAddLODBeforeCurrent();`
- L414 _private prototype_ `void OnJumpToLowestLOD();`
- L415 _private prototype_ `void OnDeleteLOD();`
- L416 _private prototype_ `void OnJumpToLODIndex(int32 LODLevel);`
- L417 _private prototype_ `void OnRefreshModule();`
- L418 _private prototype_ `void OnSyncMaterial();`
- L419 _private prototype_ `void OnUseMaterial();`
- L420 _private prototype_ `void OnDupeFromHigher();`
- L421 _private prototype_ `void OnShareFromHigher();`
- L422 _private prototype_ `void OnDupeFromHighest();`
- L423 _private prototype_ `void OnSetRandomSeed();`
- L424 _private prototype_ `void OnConvertToSeeded();`
- L425 _private prototype_ `void OnRenameEmitter();`
- L426 _private prototype_ `void OnDuplicateEmitter(bool bIsShared);`
- L427 _private prototype_ `void OnExportEmitter();`
- L428 _private prototype_ `void OnExportAll();`
- L429 _private prototype_ `void OnSelectParticleSystem();`
- L430 _private prototype_ `void OnNewEmitterBefore();`
- L431 _private prototype_ `void OnNewEmitterAfter();`
- L432 _private prototype_ `void OnRemoveDuplicateModules();`
- L434 _private prototype_ `void CloseEntryPopup();`
- L438 _private member_ `TObjectPtr<UParticleSystem> ParticleSystem;` — The ParticleSystem asset being inspected
- L441 _private member_ `TSharedPtr<SCascadePreviewViewport> PreviewViewport;` — Preview Viewport
- L444 _private member_ `TSharedPtr<SCascadeEmitterCanvas> EmitterCanvas;` — Emitter Canvas
- L447 _private member_ `TSharedPtr<class IDetailsView> Details;` — Properties Tab
- L450 _private member_ `TSharedPtr<IDistributionCurveEditor> CurveEditor;` — Curve Editor
- L453 _private member_ `TWeakPtr<class IMenu> EntryMenu;` — Reference to owner of the current popup
- L456 _private member_ `TObjectPtr<UCascadeParticleSystemComponent> ParticleSystemComponent;` — Components used for drawing the particle system in the preview viewport
- L457 _private member_ `TObjectPtr<UVectorFieldComponent> LocalVectorFieldPreviewComponent;`
- L460 _private member_ `int32 CurrentLODIdx;` — Currently selected LOD index
- L463 _private member_ `TObjectPtr<UCascadeOptions> EditorOptions;` — Config options
- L464 _private member_ `TObjectPtr<UCascadeConfiguration> EditorConfig;`
- L467 _private member_ `bool bTransactionInProgress;` — Undo/redo support
- L468 _private member_ `FText TransactionDescription;`
- L471 _private member_ `int32 SelectedModuleIndex;` — Selection info
- L472 _private member_ `TObjectPtr<UParticleModule> SelectedModule;`
- L473 _private member_ `TObjectPtr<UParticleEmitter> SelectedEmitter;`
- L476 _private member_ `bool bIsSoloing;` — True if an emitter is "soloing"
- L479 _private member_ `TObjectPtr<UParticleModule> CopyModule;` — Cached copy info
- L480 _private member_ `TObjectPtr<UParticleEmitter> CopyEmitter;`
- L483 _private member_ `bool bIsToggleMotion;` — View/draw info
- L484 _private member_ `float MotionModeRadius;`
- L485 _private member_ `float AccumulatedMotionTime;`
- L486 _private member_ `float TimeScale;`
- L487 _private member_ `float CachedTimeScale;`
- L488 _private member_ `bool bIsToggleLoopSystem;`
- L489 _private member_ `bool bIsPendingReset;`
- L490 _private member_ `double TotalTime;`
- L491 _private member_ `double ResetTime;`
- L492 _private member_ `float ParticleMemoryUpdateTime;`
- L495 _private member_ `int32 DetailMode;` — Cascade specific detail mode
- L498 _private member_ `EParticleSignificanceLevel RequiredSignificance;` — Required significance for cascade.
- L501 _private member_ `int32 GlobalDetailMode;` — Used to track changes in the global detail mode setting
- L504 _private member_ `TArray<UClass*> ParticleModuleBaseClasses;` — List of all ParticleModule subclasses
- L505 _private member_ `TArray<UClass*> ParticleModuleClasses;`
- L506 _private member_ `bool bParticleModuleClassesInitialized;`
- L509 _private member_ `TArray<UParticleModule*> DraggedModuleList;` — List of modules currently being dragged
- L512 _private member_ `EParticleSubUVInterpMethod PreviousInterpolationMethod;` — Used to enforce that all LODLevels in an emitter are either SubUV or not...
- L515 _private member_ `TObjectPtr<UObject> CurveToReplace;` — For handling curves/distribution data
- L516 _private member_ `TArray<FParticleCurvePair> DynParamCurves;`
- L519 _private member_ `TWeakPtr<SWindow> GeometryPropertiesWindow;` — The geometry properties window, if it exists
- L522 _private member_ `FParticleEmitterThumbnailMap EmitterToThumbnailMap;` — Maps particle emitters to rendered thumbnails for the emitter UI
- L525 _private member_ `static FRandomStream RandomStream;` — Random stream used to seed particle modules

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCascade, Log, All);`
- L60 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCascade, Log, All);`
- L74 _typedef_ `typedef TMap<TWeakObjectPtr<UParticleEmitter>, FParticleEmitterThumbnail> FParticleEmitterThumbnailMap;`

### `Plugins/FX/Cascade/Source/Cascade/Private/CascadeActions.h` (Private)


#### class `FCascadeCommands`  
`class FCascadeCommands : public TCommands<FCascadeCommands>`  
_L18-106_
- inherits: `TCommands<FCascadeCommands>`
- L22 _public function_ `FCascadeCommands() : TCommands<FCascadeCommands>("Cascade", NSLOCTEXT("Contexts", "Cascade", "Cascade"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L29 _public member_ `TSharedPtr<FUICommandInfo> ToggleOriginAxis;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> View_ParticleCounts;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> View_ParticleEventCounts;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> View_ParticleTimes;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> View_ParticleMemory;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> View_SystemCompleted;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> View_EmitterTickTimes;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ToggleGeometry;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ToggleGeometry_Properties;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleLocalVectorFields;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> RestartSimulation;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> RestartInLevel;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> SaveThumbnailImage;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleOrbitMode;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ToggleMotion;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> SetMotionRadius;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ViewMode_Wireframe;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ViewMode_Unlit;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> ViewMode_Lit;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> ViewMode_ShaderComplexity;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> ToggleBounds;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> ToggleBounds_SetFixedBounds;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> TogglePostProcess;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> ToggleGrid;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> CascadePlay;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> AnimSpeed_100;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> AnimSpeed_50;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> AnimSpeed_25;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> AnimSpeed_10;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> AnimSpeed_1;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> ToggleLoopSystem;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> ToggleRealtime;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> CascadeBackgroundColor;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> ToggleWireframeSphere;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> RegenerateLowestLODDuplicatingHighest;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> RegenerateLowestLOD;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> DetailMode_Low;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> DetailMode_Medium;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> DetailMode_High;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> DetailMode_Epic;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> Significance_Critical;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> Significance_High;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> Significance_Medium;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> Significance_Low;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> JumpToHighestLOD;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> JumpToHigherLOD;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> AddLODAfterCurrent;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> AddLODBeforeCurrent;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> JumpToLowerLOD;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> JumpToLowestLOD;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> JumpToLOD0;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> JumpToLOD1;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> JumpToLOD2;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> JumpToLOD3;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> DeleteLOD;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> DeleteModule;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> RefreshModule;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> SyncMaterial;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> UseMaterial;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> DupeFromHigher;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> ShareFromHigher;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> DupeFromHighest;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> SetRandomSeed;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> ConvertToSeeded;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> RenameEmitter;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> DuplicateEmitter;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> DuplicateShareEmitter;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> DeleteEmitter;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> ExportEmitter;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> ExportAllEmitters;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> SelectParticleSystem;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> NewEmitterBefore;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> NewEmitterAfter;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> RemoveDuplicateModules;`
- L105 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/FX/Cascade/Source/Cascade/Private/CascadeEmitterCanvasClient.h` (Private)


#### class `FCascadeEmitterCanvasClient`  
`class FCascadeEmitterCanvasClient : public FEditorViewportClient`  
_L31-208_
- inherits: `FEditorViewportClient`
- L35 _public prototype_ `FCascadeEmitterCanvasClient(TSharedPtr<FCascade> InCascade, TWeakPtr<SCascadeEmitterCanvas> InCascadeViewport);` — Constructor
- L36 _public prototype_ `~FCascadeEmitterCanvasClient();`
- L39 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — FViewportClient interface
- L40 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L41 _public prototype_ `virtual void CapturedMouseMove(FViewport* Viewport, int32 X, int32 Y) override;`
- L44 _public prototype_ `float GetViewportVerticalScrollBarRatio() const;` — Returns the ratio of the size of the particle emitters to the size of the viewport
- L45 _public prototype_ `float GetViewportHorizontalScrollBarRatio() const;`
- L48 _public prototype_ `UParticleModule* GetDraggedModule();` — Accessors
- L49 _public prototype_ `TArray<UParticleModule*>& GetDraggedModules();`
- L88 _private prototype_ `void UpdateScrollBars();` — Updates the states of the scrollbars
- L91 _private prototype_ `void ChangeViewportScrollBarPosition(EScrollDirection Direction);` — Changes the position of the vertical scrollbar (on a mouse scrollwheel event)
- L94 _private prototype_ `FVector2D GetViewportScrollBarPositions() const;` — Returns the positions of the scrollbars relative to the Particle Particles
- L97 _private prototype_ `void DrawEmitter(int32 Index, int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);` — Custom draw methods for various emitter/module elements
- L98 _private prototype_ `void DrawHeaderBlock(int32 Index, int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);`
- L99 _private prototype_ `void DrawCollapsedHeaderBlock(int32 Index, int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);`
- L100 _private prototype_ `void DrawTypeDataBlock(int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);`
- L101 _private prototype_ `void DrawRequiredBlock(int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);`
- L102 _private prototype_ `void DrawSpawnBlock(int32 XPos, UParticleEmitter* Emitter, FViewport* Viewport, FCanvas* Canvas);`
- L103 _private prototype_ `void DrawModule(int32 XPos, int32 YPos, UParticleEmitter* Emitter, UParticleModule* Module, FViewport* Viewport, FCanvas* Canvas, bool bDrawEnableButton = true);`
- L104 _private prototype_ `void DrawModule(FCanvas* Canvas, UParticleModule* Module, FColor ModuleBkgColor, UParticleEmitter* Emitter);`
- L105 _private prototype_ `void DrawDraggedModule(UParticleModule* Module, FViewport* Viewport, FCanvas* Canvas);`
- L106 _private prototype_ `void DrawCurveButton(UParticleEmitter* Emitter, UParticleModule* Module, bool bHitTesting, FCanvas* Canvas);`
- L107 _private prototype_ `void DrawColorButton(int32 XPos, UParticleEmitter* Emitter, UParticleModule* Module, bool bHitTesting, FCanvas* Canvas);`
- L108 _private prototype_ `void Draw3DDrawButton(UParticleEmitter* Emitter, UParticleModule* Module, bool bHitTesting, FCanvas* Canvas);`
- L109 _private prototype_ `void DrawEnableButton(UParticleEmitter* Emitter, UParticleModule* Module, bool bHitTesting, FCanvas* Canvas);`
- L110 _private prototype_ `void DrawModuleDump(FViewport* Viewport, FCanvas* Canvas);`
- L113 _private prototype_ `void FindDesiredModulePosition(const FIntPoint& Pos, class UParticleEmitter* &OutEmitter, int32 &OutIndex);` — Helper methods
- L114 _private prototype_ `FIntPoint FindModuleTopLeft(class UParticleEmitter* Emitter, class UParticleModule* Module, FViewport* Viewport);`
- L117 _private prototype_ `void RemoveFromDraggedList(UParticleModule* Module);` — Removes the specified module from the dragged module list
- L120 _private prototype_ `FTexture* GetIconTexture(ECascadeIcons eIcon);` — Returns an icon texture
- L123 _private prototype_ `void OpenModuleMenu();` — Methods for building the various context menus
- L124 _private prototype_ `void OpenEmitterMenu();`
- L125 _private prototype_ `void OpenBackgroundMenu();`
- L126 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetModule();`
- L127 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetEmitter();`
- L128 _private prototype_ `TSharedRef<SWidget> BuildMenuWidgetBackround();`
- L129 _private prototype_ `void BuildNewModuleDataTypeMenu(FMenuBuilder& Menu);`
- L130 _private prototype_ `void BuildNewModuleSubMenu(FMenuBuilder& Menu, int32 i);`
- L133 _private prototype_ `bool HasValidChildModules(int32 i) const;` — Checks to see if the base module [i] has any valid children
- L136 _private prototype_ `void InitializeModuleEntries();` — Initializes the data used in building the module type context menu options
- L139 _private prototype_ `bool IsModuleSuitableForModuleMenu(FString& InModuleName) const;` — Is the module of the given name suitable for the right-click module menu?
- L142 _private prototype_ `bool IsBaseModuleTypeDataPairSuitableForModuleMenu(FString& InModuleName) const;` — Is the base module of the given name suitable for the right-click module menu given the currently selected emitter TypeData?
- L145 _private prototype_ `bool IsModuleTypeDataPairSuitableForModuleMenu(FString& InModuleName) const;` — Is the base module of the given name suitable for the right-click module menu given the currently selected emitter TypeData?
- L148 _private prototype_ `virtual float UpdateViewportClientWindowDPIScale() const override;` — FViewport interface
- L151 _private member_ `TWeakPtr<FCascade> CascadePtr;` — Pointer back to the Particle editor tool that owns us
- L154 _private member_ `TWeakPtr<SCascadeEmitterCanvas> CascadeViewportPtr;` — Pointer back to the Particle viewport control that owns us
- L157 _private member_ `FIntPoint CanvasDimensions;` — Size of the viewport canvas
- L160 _private member_ `ECascadeModuleMoveMode CurrentMoveMode;` — User input state info
- L161 _private member_ `FIntPoint MouseHoldOffset;`
- L162 _private member_ `FIntPoint MousePressPosition;`
- L163 _private member_ `bool bMouseDragging;`
- L164 _private member_ `bool bMouseDown;`
- L167 _private member_ `FIntPoint Origin2D;` — Canvas offset
- L170 _private member_ `UParticleModule* DraggedModule;` — Currently dragged module.
- L171 _private member_ `TArray<UParticleModule*> DraggedModules;`
- L172 _private member_ `bool bDrawDraggedModule;`
- L175 _private member_ `int32 ResetDragModIndex;` — If we abort a drag - here is where put the module back to (in the selected Emitter)
- L178 _private member_ `UTexture2D* IconTex[Icon_COUNT];` — Textures/icons
- L179 _private member_ `UTexture2D* TexModuleDisabledBackground;`
- L182 _private member_ `const int32 EmitterWidth;` — Miscellaneous draw info
- L183 _private member_ `const int32 EmitterCollapsedWidth;`
- L184 _private member_ `const int32 EmitterHeadHeight;`
- L185 _private member_ `const int32 EmitterThumbBorder;`
- L186 _private member_ `int32 ModuleHeight;`
- L187 _private member_ `FColor ModuleColors[EPMT_MAX][Selection_COUNT];`
- L188 _private member_ `FColor EmptyBackgroundColor;`
- L189 _private member_ `FColor EmitterBackgroundColor;`
- L190 _private member_ `FColor EmitterSelectedColor;`
- L191 _private member_ `FColor EmitterUnselectedColor;`
- L192 _private member_ `const FColor RenderModeSelected;`
- L193 _private member_ `const FColor RenderModeUnselected;`
- L194 _private member_ `const FColor Module3DDrawModeEnabledColor;`
- L195 _private member_ `const FColor Module3DDrawModeDisabledColor;`
- L196 _private member_ `const int32 RequiredModuleOffset;`
- L197 _private member_ `const int32 SpawnModuleOffset;`
- L198 _private member_ `const int32 ModulesOffset;`
- L199 _private member_ `int32 NumRejectedModulesDrawn;`
- L200 _private member_ `TArray<FString> ModuleErrorStrings;`
- L203 _private member_ `bool bInitializedModuleEntries;` — Data used in building the module type context menu options
- L204 _private member_ `TArray<FString> TypeDataModuleEntries;`
- L205 _private member_ `TArray<int32> TypeDataModuleIndices;`
- L206 _private member_ `TArray<FString> ModuleEntries;`
- L207 _private member_ `TArray<int32> ModuleIndices;`

#### enum `FCascadeEmitterCanvasClient::ECascadeModuleMoveMode`  
`enum ECascadeModuleMoveMode`  
_L53-59_
- desc: Type of move operation
- L55 _public enumerator_ `MoveMode_None`
- L56 _public enumerator_ `MoveMode_Move`
- L57 _public enumerator_ `MoveMode_Instance`
- L58 _public enumerator_ `MoveMode_Copy`

#### enum `FCascadeEmitterCanvasClient::ECascadeIcons`  
`enum ECascadeIcons`  
_L62-77_
- desc: Emitter/module icon types
- L64 _public enumerator_ `Icon_RenderNormal = 0`
- L65 _public enumerator_ `Icon_RenderCross`
- L66 _public enumerator_ `Icon_RenderPoint`
- L67 _public enumerator_ `Icon_RenderNone`
- L68 _public enumerator_ `Icon_RenderLights`
- L69 _public enumerator_ `Icon_CurveEdit`
- L70 _public enumerator_ `Icon_3DDrawEnabled`
- L71 _public enumerator_ `Icon_3DDrawDisabled`
- L72 _public enumerator_ `Icon_ModuleEnabled`
- L73 _public enumerator_ `Icon_ModuleDisabled`
- L74 _public enumerator_ `Icon_SoloEnabled`
- L75 _public enumerator_ `Icon_SoloDisabled`
- L76 _public enumerator_ `Icon_COUNT`

#### enum `FCascadeEmitterCanvasClient::ECascadeModuleSelection`  
`enum ECascadeModuleSelection`  
_L80-85_
- desc: Module selection type
- L82 _public enumerator_ `Selection_Unselected = 0`
- L83 _public enumerator_ `Selection_Selected = 1`
- L84 _public enumerator_ `Selection_COUNT = 2`

### `Plugins/FX/Cascade/Source/Cascade/Private/CascadeEmitterHitProxies.h` (Private)


#### struct `HCascadeEdEmitterProxy`  
`struct HCascadeEdEmitterProxy : public HHitProxy`  
_L12-22_
- inherits: `HHitProxy`
- L14 _public prototype_ `DECLARE_HIT_PROXY();`
- L16 _public member_ `class UParticleEmitter* Emitter;`
- L18 _public function_ `HCascadeEdEmitterProxy(class UParticleEmitter* InEmitter) : HHitProxy(HPP_UI), Emitter(InEmitter)`

#### struct `HCascadeEdModuleProxy`  
`struct HCascadeEdModuleProxy : public HHitProxy`  
_L24-36_
- inherits: `HHitProxy`
- L26 _public prototype_ `DECLARE_HIT_PROXY();`
- L28 _public member_ `class UParticleEmitter* Emitter;`
- L29 _public member_ `class UParticleModule* Module;`
- L31 _public function_ `HCascadeEdModuleProxy(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

#### struct `HCascadeEdEmitterEnableProxy`  
`struct HCascadeEdEmitterEnableProxy : public HHitProxy`  
_L38-48_
- inherits: `HHitProxy`
- L40 _public prototype_ `DECLARE_HIT_PROXY();`
- L42 _public member_ `class UParticleEmitter* Emitter;`
- L44 _public function_ `HCascadeEdEmitterEnableProxy(class UParticleEmitter* InEmitter) : HHitProxy(HPP_UI), Emitter(InEmitter)`

#### struct `HCascadeEdDrawModeButtonProxy`  
`struct HCascadeEdDrawModeButtonProxy : public HHitProxy`  
_L50-62_
- inherits: `HHitProxy`
- L52 _public prototype_ `DECLARE_HIT_PROXY();`
- L54 _public member_ `class UParticleEmitter* Emitter;`
- L55 _public member_ `int32 DrawMode;`
- L57 _public function_ `HCascadeEdDrawModeButtonProxy(class UParticleEmitter* InEmitter, int32 InDrawMode) : HHitProxy(HPP_UI), Emitter(InEmitter), DrawMode(InDrawMode)`

#### struct `HCascadeEdSoloButtonProxy`  
`struct HCascadeEdSoloButtonProxy : public HHitProxy`  
_L64-74_
- inherits: `HHitProxy`
- L66 _public prototype_ `DECLARE_HIT_PROXY();`
- L68 _public member_ `class UParticleEmitter* Emitter;`
- L70 _public function_ `HCascadeEdSoloButtonProxy(class UParticleEmitter* InEmitter) : HHitProxy(HPP_UI), Emitter(InEmitter)`

#### struct `HCascadeEdGraphButton`  
`struct HCascadeEdGraphButton : public HHitProxy`  
_L76-88_
- inherits: `HHitProxy`
- L78 _public prototype_ `DECLARE_HIT_PROXY();`
- L80 _public member_ `class UParticleEmitter* Emitter;`
- L81 _public member_ `class UParticleModule* Module;`
- L83 _public function_ `HCascadeEdGraphButton(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

#### struct `HCascadeEdColorButtonProxy`  
`struct HCascadeEdColorButtonProxy : public HHitProxy`  
_L90-102_
- inherits: `HHitProxy`
- L92 _public prototype_ `DECLARE_HIT_PROXY();`
- L94 _public member_ `class UParticleEmitter* Emitter;`
- L95 _public member_ `class UParticleModule* Module;`
- L97 _public function_ `HCascadeEdColorButtonProxy(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

#### struct `HCascadeEd3DDrawModeButtonProxy`  
`struct HCascadeEd3DDrawModeButtonProxy : public HHitProxy`  
_L104-116_
- inherits: `HHitProxy`
- L106 _public prototype_ `DECLARE_HIT_PROXY();`
- L108 _public member_ `class UParticleEmitter* Emitter;`
- L109 _public member_ `class UParticleModule* Module;`
- L111 _public function_ `HCascadeEd3DDrawModeButtonProxy(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

#### struct `HCascadeEdEnableButtonProxy`  
`struct HCascadeEdEnableButtonProxy : public HHitProxy`  
_L118-130_
- inherits: `HHitProxy`
- L120 _public prototype_ `DECLARE_HIT_PROXY();`
- L122 _public member_ `class UParticleEmitter* Emitter;`
- L123 _public member_ `class UParticleModule* Module;`
- L125 _public function_ `HCascadeEdEnableButtonProxy(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

#### struct `HCascadeEd3DDrawModeOptionsButtonProxy`  
`struct HCascadeEd3DDrawModeOptionsButtonProxy : public HHitProxy`  
_L132-144_
- inherits: `HHitProxy`
- L134 _public prototype_ `DECLARE_HIT_PROXY();`
- L136 _public member_ `class UParticleEmitter* Emitter;`
- L137 _public member_ `class UParticleModule* Module;`
- L139 _public function_ `HCascadeEd3DDrawModeOptionsButtonProxy(class UParticleEmitter* InEmitter, class UParticleModule* InModule) : HHitProxy(HPP_UI), Emitter(InEmitter), Module(InModule)`

### `Plugins/FX/Cascade/Source/Cascade/Private/CascadePreviewViewportClient.h` (Private)


#### class `FCascadeEdPreviewViewportClient`  
`class FCascadeEdPreviewViewportClient : public FEditorViewportClient`  
_L32-134_
- inherits: `FEditorViewportClient`
- L36 _public prototype_ `FCascadeEdPreviewViewportClient(TWeakPtr<FCascade> InCascade, const TSharedRef<SCascadePreviewViewport>& InCascadeViewport);` — Constructor
- L40 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;` — FEditorViewportClient interface
- L41 _public prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L42 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& InEventArgs) override;`
- L43 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& InEventArgs) override;`
- L44 _public prototype_ `virtual FSceneInterface* GetScene() const override;`
- L45 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;`
- L46 _public prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L47 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L48 _public prototype_ `virtual bool CanCycleWidgetMode() const override;`
- L51 _public prototype_ `void SetPreviewCamera(const FRotator& NewPreviewAngle, float NewPreviewDistance);` — Sets the position and orientation of the preview camera
- L54 _public prototype_ `void UpdateMemoryInformation();` — Update the memory information of the particle system
- L57 _public prototype_ `void CreateThumbnail();` — Generates a new thumbnail image for the content browser
- L76 _public prototype_ `FPreviewScene& GetPreviewScene();` — Accessors
- L77 _public prototype_ `bool GetDrawElement(EDrawElements Element) const;`
- L78 _public prototype_ `void ToggleDrawElement(EDrawElements Element);`
- L79 _public prototype_ `FColor GetPreviewBackgroundColor() const;`
- L80 _public prototype_ `UStaticMeshComponent* GetFloorComponent();`
- L81 _public prototype_ `FEditorCommonDrawHelper& GetDrawHelper();`
- L82 _public prototype_ `float& GetWireSphereRadius();`
- L84 _public function_ `FCascade* GetCascade()`
- L87 _private member_ `TWeakPtr<FCascade> CascadePtr;` — Pointer back to the ParticleSystem editor tool that owns us
- L90 _private member_ `UStaticMeshComponent* FloorComponent;` — Preview mesh
- L93 _private member_ `FRotator PreviewAngle;` — Camera potition/rotation
- L94 _private member_ `float PreviewDistance;`
- L97 _private member_ `float bCaptureScreenShot;` — If true, will take screenshot for thumbnail on next draw call
- L100 _private member_ `FVector WorldManipulateDir;` — User input state info
- L101 _private member_ `FVector LocalManipulateDir;`
- L102 _private member_ `float DragX;`
- L103 _private member_ `float DragY;`
- L104 _private member_ `EAxisList::Type WidgetAxis;`
- L105 _private member_ `EWidgetMovementMode WidgetMM;`
- L106 _private member_ `bool bManipulatingVectorField;`
- L109 _private member_ `int32 DrawFlags;` — Draw flags (see EDrawElements)
- L112 _private member_ `float WireSphereRadius;` — Radius of the wireframe sphere
- L115 _private member_ `FColor BackgroundColor;` — Veiwport background color
- L118 _private member_ `FPreviewScene CascadePreviewScene;` — The scene used for the viewport. Owned externally
- L121 _private member_ `int32 ParticleSystemRootSize;` — The size of the ParticleSystem via FArchive memory counting
- L123 _private member_ `int32 ParticleModuleMemSize;` — The size the particle modules take for the system
- L125 _private member_ `int32 PSysCompRootSize;` — The size of the ParticleSystemComponent via FArchive memory counting
- L127 _private member_ `int32 PSysCompResourceSize;` — The size of the ParticleSystemComponent resource size
- L130 _private member_ `const int32 VectorFieldHitproxyInfo;` — Draw info index for vector fields
- L133 _private member_ `const float LightRotSpeed;` — Speed multiplier used when moving the scene light around

#### enum `FCascadeEdPreviewViewportClient::EDrawElements`  
`enum EDrawElements`  
_L60-73_
- desc: Draw flag types
- L62 _public enumerator_ `ParticleCounts = 0x001`
- L63 _public enumerator_ `ParticleEvents = 0x002`
- L64 _public enumerator_ `ParticleTimes = 0x004`
- L65 _public enumerator_ `ParticleMemory = 0x008`
- L66 _public enumerator_ `VectorFields = 0x010`
- L67 _public enumerator_ `Bounds = 0x020`
- L68 _public enumerator_ `WireSphere = 0x040`
- L69 _public enumerator_ `OriginAxis = 0x080`
- L70 _public enumerator_ `Orbit = 0x100`
- L71 _public enumerator_ `ParticleSystemCompleted = 0x200`
- L72 _public enumerator_ `EmitterTickTimes = 0x400`

### `Plugins/FX/Cascade/Source/Cascade/Private/SCascadeEmitterCanvas.h` (Private)


#### class `SCascadeEmitterCanvas`  
`class SCascadeEmitterCanvas : public SCompoundWidget`  
_L21-77_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCascadeEmitterCanvas)`
- L27 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FCascade>, Cascade) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `void RefreshViewport();` — Refreshes the viewport
- L37 _public prototype_ `bool IsVisible() const;` — Returns true if the viewport is visible
- L40 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport() const;` — Accessors
- L41 _public prototype_ `TSharedPtr<FCascadeEmitterCanvasClient> GetViewportClient() const;`
- L42 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget() const;`
- L43 _public prototype_ `TSharedPtr<SScrollBar> GetVerticalScrollBar() const;`
- L44 _public prototype_ `TSharedPtr<SScrollBar> GetHorizontalScrollBar() const;`
- L48 _public member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L52 _protected prototype_ `EVisibility GetViewportVerticalScrollBarVisibility() const;` — Returns the visibility of the viewport scrollbars
- L53 _protected prototype_ `EVisibility GetViewportHorizontalScrollBarVisibility() const;`
- L56 _protected prototype_ `void OnViewportVerticalScrollBarScrolled(float InScrollOffsetFraction);` — Called when the viewport scrollbars are scrolled
- L57 _protected prototype_ `void OnViewportHorizontalScrollBarScrolled(float InScrollOffsetFraction);`
- L61 _private member_ `TWeakPtr<FCascade> CascadePtr;` — Pointer back to the Texture editor tool that owns us
- L64 _private member_ `TSharedPtr<FCascadeEmitterCanvasClient> ViewportClient;` — Level viewport client
- L67 _private member_ `TSharedPtr<FSceneViewport> Viewport;` — Slate viewport for rendering and I/O
- L70 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — Viewport widget
- L73 _private member_ `TSharedPtr<SScrollBar> ViewportVerticalScrollBar;` — Vertical scrollbar
- L76 _private member_ `TSharedPtr<SScrollBar> ViewportHorizontalScrollBar;` — Horizontal scrollbar

### `Plugins/FX/Cascade/Source/Cascade/Private/SCascadePreviewToolbar.h` (Private)


#### class `SCascadePreviewViewportToolBar`  
`class SCascadePreviewViewportToolBar : public SViewportToolBar`  
_L17-36_
- inherits: `SViewportToolBar`
- L20 _public function_ `SLATE_BEGIN_ARGS(SCascadePreviewViewportToolBar)`
- L21 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FCascade>, CascadePtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private prototype_ `TSharedRef<SWidget> GenerateViewMenu() const;` — Generates the toolbar view menu content
- L31 _private prototype_ `TSharedRef<SWidget> GenerateTimeMenu() const;` — Generates the toolbar time menu content
- L35 _private member_ `TWeakPtr<FCascade> CascadePtr;` — The viewport that we are in

### `Plugins/FX/Cascade/Source/Cascade/Private/SCascadePreviewViewport.h` (Private)


#### class `SCascadePreviewViewport`  
`class SCascadePreviewViewport : public SEditorViewport`  
_L24-73_
- inherits: `SEditorViewport`
- L27 _public function_ `SLATE_BEGIN_ARGS(SCascadePreviewViewport)`
- L30 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FCascade>, Cascade) SLATE_END_ARGS() ~SCascadePreviewViewport();`
- L37 _public prototype_ `void Construct(const FArguments& InArgs);` — SCompoundWidget interface
- L40 _public prototype_ `void RefreshViewport();` — Refreshes the viewport
- L43 _public prototype_ `bool IsVisible() const override;` — Returns true if the viewport is visible
- L46 _public prototype_ `TSharedPtr<FSceneViewport> GetViewport() const;` — Accessors
- L47 _public prototype_ `TSharedPtr<FCascadeEdPreviewViewportClient> GetViewportClient() const;`
- L48 _public prototype_ `TSharedPtr<SViewport> GetViewportWidget() const;`
- L50 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L52 _public function_ `bool HasJustTicked()`
- L53 _public function_ `void ClearTickFlag()`
- L55 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L56 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L57 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L60 _public member_ `TWeakPtr<SDockTab> ParentTab;` — The parent tab where this viewport resides
- L64 _private member_ `TWeakPtr<FCascade> CascadePtr;` — Pointer back to the ParticleSystem editor tool that owns us
- L67 _private member_ `TSharedPtr<FCascadeEdPreviewViewportClient> ViewportClient;` — Level viewport client
- L70 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L72 _private member_ `bool JustTicked;`

### `Plugins/FX/Cascade/Source/Cascade/Public/CascadeModule.h` (Public)


#### class `ICascadeModule`  
`class ICascadeModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L24-39_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L29 _public prototype_ `virtual TSharedRef<ICascade> CreateCascade(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UParticleSystem* ParticleSystem) = 0;` — Creates a new Cascade instance
- L32 _public prototype_ `virtual void CascadeClosed(FCascade* CascadeInstance) = 0;` — Removes the specified instance from the list of open Cascade toolkits
- L35 _public prototype_ `virtual void RefreshCascade(UParticleSystem* ParticleSystem) = 0;` — Refreshes the toolkit inspecting the specified particle system
- L38 _public prototype_ `virtual void ConvertModulesToSeeded(UParticleSystem* ParticleSystem) = 0;` — Converts all the modules in the specified particle system to seeded modules

#### Free symbols / members of external scopes

- L18 _externvar_ `extern const FName CascadeAppIdentifier;`

### `Plugins/FX/Cascade/Source/Cascade/Public/ICascade.h` (Public)


#### class `ICascade`  
`class ICascade : public FAssetEditorToolkit`  
_L13-16_
- inherits: `FAssetEditorToolkit`
