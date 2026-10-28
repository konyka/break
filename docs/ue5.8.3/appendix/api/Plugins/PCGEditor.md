# Plugins / PCGEditor

- module root: `Plugins/PCG/Source/PCGEditor`
- headers: 151; symbols: 3853
- symbol kinds: class=196, delegate=16, enum=19, enumerator=88, externvar=6, function=412, macro=10, member=1003, namespace=76, prototype=1838, struct=82, typedef=18, variable=89
- PrivateDependencyModuleNames: AdvancedPreviewScene, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ClassViewer, ComponentVisualizers, ContentBrowser, ContentBrowserData, DesktopWidgets, DetailCustomizations, DeveloperSettings, EditorFramework, EditorScriptingUtilities, EditorStyle, EditorSubsystem, EditorWidgets, GameProjectGeneration, GeometryCore, GeometryFramework, GraphEditor, InputCore, InteractiveToolsFramework, Kismet, KismetWidgets, Landscape, LevelEditor, ModelingComponents, ModelingComponentsEditorOnly, PropertyEditor, RHI, RenderCore, SceneOutliner, ScriptableEditorWidgets, Slate, SlateCore, SourceControl, StatusBar, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd, WidgetRegistration
- PublicDependencyModuleNames: Core, CoreUObject, DataHierarchyEditor, Engine, LevelEditor, PCG, PlacementMode, Projects, StructUtilsEditor

### `Plugins/PCG/Source/PCGEditor/Internal/ChangeTracking/PCGActorTracker.h` (Internal)


#### class `FPCGActorTracker`  
`class FPCGActorTracker : public IPCGChangeTracker`  
_L26-72_
- inherits: `IPCGChangeTracker`
- L29 _public prototype_ `virtual ~FPCGActorTracker();`
- L31 _public prototype_ `static TUniquePtr<IPCGChangeTracker> MakeInstance(FPCGTrackingManager* InOwner);`
- L32 _public prototype_ `static FName GetName();`
- L34 _public prototype_ `virtual void Tick() override;`
- L36 _public prototype_ `virtual bool OnObjectPropertyChanged(const UObject* InObject, FPropertyChangedEvent& InEvent) override;`
- L37 _public prototype_ `virtual bool OnNotifyObjectChanged(const UObject* InObject, const FPCGTrackingChangeID& InChangeID, const UObject* InOriginatingChangeObject) override;`
- L41 _private typedef_ `using FActorPreviousData = TTuple<FBox, TSet<FName>, double>;` — Typedef to store the previous position and previous tags of changed actors.
- L43 _private prototype_ `FPCGActorTracker(FPCGTrackingManager* InOwner);`
- L45 _private prototype_ `bool IsActorTracked(const AActor* InActor) const;`
- L46 _private prototype_ `bool ShouldDelayActor(const AActor* InActor) const;`
- L48 _private prototype_ `void OnLevelInstancesUpdated(const TArray<ILevelInstanceInterface*>& InLevelInstances);`
- L49 _private prototype_ `void OnLevelInstanceEditCancelled(ILevelInstanceInterface* InLevelInstance, bool bInHasDiscardedChanges);`
- L50 _private prototype_ `void OnActorLoaded(AActor& InActor);`
- L51 _private prototype_ `void OnActorAdded(AActor* InActor);`
- L52 _private prototype_ `void OnActorAdded_Internal(const AActor* InActor, bool bShouldDirty);`
- L53 _private prototype_ `void OnActorChanged_Internal(const AActor* InActor, const UObject* InOriginatingChangeObject, const FPCGTrackingChangeID& InChangeID);`
- L54 _private prototype_ `void OnActorChanged_Recursive(const AActor* InActor, const UObject* InOriginatingChangeObject, const FPCGTrackingChangeID& InChangeID);`
- L55 _private prototype_ `void OnActorChanged_Impl(const AActor* InActor, const UObject* InOriginatingChangeObject, const FPCGTrackingChangeID& InChangeID, FActorPreviousData* InPreviousData);`
- L56 _private prototype_ `void OnActorUnloaded(AActor& InActor);`
- L57 _private prototype_ `void OnActorDeleted(AActor* InActor);`
- L58 _private prototype_ `void OnActorDeleted_Internal(const AActor* InActor, bool bShouldDirty);`
- L59 _private prototype_ `void OnObjectModified(UObject* InObject);`
- L60 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& Event);`
- L62 _private member_ `static const FLazyName Name;`
- L65 _private member_ `TMap<TObjectKey<AActor>, TTuple<TObjectKey<UObject>, FPCGTrackingChangeID>> DelayedChangedActors;` — Keep track of actors that aren't yet ready (or if the subsystem is not yet ready), whether we should dirty them in next tick.
- L68 _private member_ `TMap<TObjectKey<AActor>, FActorPreviousData> ActorToPreviousDataMap;` — Transient map of owners and their previous data, it's set in the pre object change to be able to track changes (such as tags or positions)
- L71 _private member_ `double LastPreviousActorDataCleanup = -1.0;` — Time keeper for cleaning up cached previous actor data

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace PCGActorTracker`
- L21 _variable_ `static const FPCGTrackingChangeID ActorDeleted(0x99FF9E41, 0x3940482C, 0xBD5F0BA0, 0x7DAE68EE);` (scope `PCGActorTracker`)
- L22 _variable_ `static const FPCGTrackingChangeID ActorAdded(0x10A0FD3D, 0x9A8546B8, 0xA7D5FB5F, 0xCD398DC1);` (scope `PCGActorTracker`)
- L23 _variable_ `static const FPCGTrackingChangeID ActorChanged(0xD822BD05, 0xE0B94C35, 0xA8A36F1D, 0x7A05F444);` (scope `PCGActorTracker`)

### `Plugins/PCG/Source/PCGEditor/Internal/ChangeTracking/PCGComponentChangeHandler.h` (Internal)


#### class `FPCGComponentChangeHandler`  
`class FPCGComponentChangeHandler : public IPCGChangeHandler`  
_L13-45_
- inherits: `IPCGChangeHandler`
- L16 _public prototype_ `virtual ~FPCGComponentChangeHandler();`
- L18 _public prototype_ `static TUniquePtr<IPCGChangeHandler> MakeInstance(FPCGTrackingManager* InOwner);`
- L19 _public prototype_ `static FName GetName();`
- L21 _public prototype_ `virtual void BeginChangeHandling(const TSharedRef<FPCGChangeHandlerChange>& InChange) override;`
- L22 _public prototype_ `virtual void HandleChange(IPCGGraphExecutionSource* InExecutionSource) override;`
- L23 _public prototype_ `virtual void HandleBoundedChange(IPCGGraphExecutionSource* InExecutionSource, const FBox& InExecutionSourceBounds, const FBox& InChangeBounds) override;`
- L24 _public prototype_ `virtual void EndChangeHandling(bool bSkipRefresh) override;`
- L27 _private prototype_ `FPCGComponentChangeHandler(FPCGTrackingManager* InOwner);`
- L29 _private prototype_ `bool ShouldDiscardComponent(UPCGComponent* InComponent) const;`
- L42 _private member_ `TUniquePtr<FCurrentChange> CurrentChange;`
- L44 _private member_ `static const FLazyName Name;`

#### struct `FPCGComponentChangeHandler::FCurrentChange`  
`struct FCurrentChange`  
_L31-40_
- L33 _public member_ `TWeakPtr<FPCGChangeHandlerChange> Change;`
- L35 _public member_ `TArray<const UObject*> ChangedObjects;`
- L37 _public member_ `TOptional<FPCGDynamicTrackingPriority> ChangedObjectDynamicTrackingPriority;`
- L38 _public member_ `EPCGComponentDirtyFlag DirtyFlag = EPCGComponentDirtyFlag::None;`
- L39 _public member_ `TSet<UPCGComponent*> DirtyComponents;`

### `Plugins/PCG/Source/PCGEditor/Internal/ChangeTracking/PCGLandscapeTracker.h` (Internal)


#### class `FPCGLandscapeTracker`  
`class FPCGLandscapeTracker : public IPCGChangeTracker`  
_L18-48_
- inherits: `IPCGChangeTracker`
- L21 _public prototype_ `virtual ~FPCGLandscapeTracker();`
- L23 _public prototype_ `static TUniquePtr<IPCGChangeTracker> MakeInstance(FPCGTrackingManager* InOwner);`
- L24 _public prototype_ `static FName GetName();`
- L26 _public prototype_ `virtual void Tick() override;`
- L27 _public prototype_ `virtual bool ShouldSkipRefresh(const UObject* InChangedObject) override;`
- L30 _private prototype_ `FPCGLandscapeTracker(FPCGTrackingManager* InOwner);`
- L32 _private prototype_ `void OnLandscapeChanged(ALandscapeProxy* InLandscape, const FLandscapeProxyComponentDataChangedParams& InChangeParams);`
- L33 _private prototype_ `void ApplyLandscapeChanges(ALandscapeProxy* InLandscape);`
- L34 _private prototype_ `void OnEditorModeIDChanged(const FEditorModeID& EditorModeID, bool bIsEntering);`
- L35 _private prototype_ `void OnLandscapeEditModeExited();`
- L37 _private member_ `static const FLazyName Name;`
- L40 _private member_ `double LastLandscapeDirtyTime = -1.0;` — Part for the delayed landscape change update
- L41 _private member_ `TArray<TObjectKey<ALandscapeProxy>> DelayedModifiedLandscapes;`
- L44 _private member_ `TArray<TObjectKey<ALandscapeProxy>> DirtiedLandscapes;` — Keep track of all dirtied landscapes and force a refresh on them when exiting edit mode.
- L47 _private member_ `bool bIsCurrentlyExitingLandscapeEditMode = false;` — Temp boolean to indicate we are currently exiting the landscape edit mode

#### Free symbols / members of external scopes

- L16 _typedef_ `typedef FName FEditorModeID;`

### `Plugins/PCG/Source/PCGEditor/Internal/ChangeTracking/PCGMiscTracker.h` (Internal)


#### class `FPCGMiscTracker`  
`class FPCGMiscTracker : public IPCGChangeTracker`  
_L15-29_
- inherits: `IPCGChangeTracker`
- desc: For now this is a "everything" else tracker that tracks specific asset type saves
- L18 _public prototype_ `virtual ~FPCGMiscTracker();`
- L20 _public prototype_ `static TUniquePtr<IPCGChangeTracker> MakeInstance(FPCGTrackingManager* InOwner);`
- L21 _public prototype_ `static FName GetName();`
- L24 _private prototype_ `FPCGMiscTracker(FPCGTrackingManager* InOwner);`
- L26 _private prototype_ `void OnObjectSaved(UObject* InObject, FObjectPreSaveContext InObjectSaveContext);`
- L28 _private member_ `static const FLazyName Name;`

### `Plugins/PCG/Source/PCGEditor/Internal/ChangeTracking/PCGRuntimeGenChangeHandler.h` (Internal)


#### class `FPCGRuntimeGenChangeHandler`  
`class FPCGRuntimeGenChangeHandler : public IPCGChangeHandler`  
_L13-40_
- inherits: `IPCGChangeHandler`
- L16 _public prototype_ `static TUniquePtr<IPCGChangeHandler> MakeInstance(FPCGTrackingManager* InOwner);`
- L17 _public prototype_ `static FName GetName();`
- L20 _public prototype_ `virtual void BeginChangeHandling(const TSharedRef<FPCGChangeHandlerChange>& InChange) override;`
- L21 _public prototype_ `virtual void HandleChange(IPCGGraphExecutionSource* InExecutionSource) override;`
- L22 _public prototype_ `virtual void HandleBoundedChange(IPCGGraphExecutionSource* InExecutionSource, const FBox& InExecutionSourceBounds, const FBox& InChangeBounds) override;`
- L23 _public prototype_ `virtual void EndChangeHandling(bool bSkipRefresh) override;`
- L27 _private prototype_ `FPCGRuntimeGenChangeHandler(FPCGTrackingManager* InOwner);`
- L29 _private prototype_ `void HandleChangeInternal(IPCGGraphExecutionSource* InExecutionSource, const FBox* InExecutionSourceBounds = nullptr, const FBox* InChangeBounds = nullptr);`
- L30 _private prototype_ `bool ShouldDiscardExecutionSource(UPCGRuntimeGenExecutionSource* InExecutionSource) const;`
- L39 _private member_ `TUniquePtr<FCurrentChange> CurrentChange;`

#### struct `FPCGRuntimeGenChangeHandler::FCurrentChange`  
`struct FCurrentChange`  
_L32-37_
- L34 _public member_ `TWeakPtr<FPCGChangeHandlerChange> Change;`
- L35 _public member_ `TArray<const UObject*> ChangedObjects;`
- L36 _public member_ `TSet<UPCGRuntimeGenExecutionSource*> DirtyExecutionSources;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGAsset.h` (Private)


#### class `UAssetDefinition_PCGAsset`  
`class UAssetDefinition_PCGAsset : public UAssetDefinitionDefault`  
_L11-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset definition class for PCG Assets. Used to control asset name, color & categories in the content browser.
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGBuilderSettings.h` (Private)


#### class `UAssetDefinition_PCGBuilderSettings`  
`class UAssetDefinition_PCGBuilderSettings : public UAssetDefinitionDefault`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGComputeSource.h` (Private)


#### class `UAssetDefinition_PCGComputeSource`  
`class UAssetDefinition_PCGComputeSource : public UAssetDefinitionDefault`  
_L10-20_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGGraph.h` (Private)


#### class `UAssetDefinition_PCGGraph`  
`class UAssetDefinition_PCGGraph : public UAssetDefinition_PCGGraphInterface`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCGGraphInterface`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L18 _public prototype_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGGraphInstance.h` (Private)


#### class `UAssetDefinition_PCGGraphInstance`  
`class UAssetDefinition_PCGGraphInstance : public UAssetDefinition_PCGGraphInterface`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCGGraphInterface`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGGraphInterface.h` (Private)


#### class `UAssetDefinition_PCGGraphInterface`  
`class UAssetDefinition_PCGGraphInterface : public UAssetDefinitionDefault`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetDefinitions/AssetDefinition_PCGSettings.h` (Private)


#### class `UAssetDefinition_PCGSettings`  
`class UAssetDefinition_PCGSettings : public UAssetDefinitionDefault`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetEditorMode/PCGAssetEditorToolRegistry.h` (Private)


#### class `FPCGAssetEditorToolRegistry`  
`class FPCGAssetEditorToolRegistry`  
_L14-30_
- desc: Maps UPCGSettings subclasses to the interactive tool that handles them. Populated at module startup via GetDerivedClasses + CDO::GetSupportedSettingsClasses().
- L17 _public prototype_ `static FPCGAssetEditorToolRegistry& Get();`
- L18 _public prototype_ `static void TearDown();`
- L20 _public prototype_ `void RegisterTool(UClass* SettingsClass, TSubclassOf<UPCGAssetEditorInteractiveTool> ToolClass);`
- L23 _public prototype_ `const TSubclassOf<UPCGAssetEditorInteractiveTool>* FindToolForSettings(const UClass* SettingsClass) const;` — Walks the settings class hierarchy; returns null if no tool is registered.
- L26 _public prototype_ `TArray<TSubclassOf<UPCGAssetEditorInteractiveTool>> GetAllToolClasses() const;` — Returns deduplicated list of all registered tool classes, for tool-manager registration.
- L29 _private member_ `TMap<TObjectKey<UClass>, TSubclassOf<UPCGAssetEditorInteractiveTool>> SettingsToToolMap;`

### `Plugins/PCG/Source/PCGEditor/Private/AssetEditorMode/Tools/PCGEditPointsInteractiveTool.h` (Private)


#### class `UPCGEditPointsInteractiveTool`  
`class UPCGEditPointsInteractiveTool : public UPCGAssetEditorInteractiveTool, public IClickBehaviorTarget, public FSelfRegisteringEditorUndoClient`  
_L34-112_
- reflection: `UCLASS()`
- inherits: `UPCGAssetEditorInteractiveTool,IClickBehaviorTarget,FSelfRegisteringEditorUndoClient`
- desc: Interactive viewport tool for UPCGCreatePointsSettings. Renders a wire box for each point in the node's output. Clicking a box shows a combined transform gizmo; dragging it writes a FPCGPointTransformDelta into FPCGSourceDataContainer and triggers graph re-execution.
- L39 _public prototype_ `PCG_DECLARE_SUPPORTED_NODES( UPCGCreatePointsSettings, UPCGCreatePointsGridSettings, UPCGCreatePointsSphereSettings, UPCGEditPointsSettings );`
- L47 _public prototype_ `virtual void Setup() override;`
- L48 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L49 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L53 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L54 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L57 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L58 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L59 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L63 _protected prototype_ `virtual void OnAccept() override;`
- L64 _protected prototype_ `virtual void OnCancel() override;`
- L66 _protected prototype_ `virtual void OnNodeSettingsChanged(UPCGSettings* NodeSettings, EPCGChangeType ChangeType) override;`
- L70 _private prototype_ `void OnGraphExecuted(IPCGBaseSubsystem* InSubsystem, IPCGGraphExecutionSource* InExecutionSource, EPCGGenerationStatus InGenerationStatus);`
- L72 _private prototype_ `void OnGizmoTransformBegin(UTransformProxy* Proxy);`
- L73 _private prototype_ `void OnGizmoTransformChanged(UTransformProxy* Proxy, FTransform NewTransform);`
- L74 _private prototype_ `void OnGizmoTransformEnd(UTransformProxy* Proxy);`
- L76 _private prototype_ `void ShowGizmoAt(const FTransform& Transform);`
- L77 _private prototype_ `void HideGizmo();`
- L79 _private prototype_ `void BuildCachedMesh();`
- L82 _private prototype_ `void NotifyGraphChanged();` — Trigger graph re-execution after delta changes.
- L84 _private prototype_ `FPCGSourceDataContainer* GetDataContainer() const;`
- L85 _private prototype_ `bool MarkDataContainerDirty();`
- L87 _private prototype_ `FPCGDeltaCollection* GetCollection(const FPCGSourceDataStorageKey& StorageKey) const;`
- L88 _private prototype_ `FPCGDeltaCollection* GetOrCreateCollection(const FPCGSourceDataStorageKey& StorageKey) const;`
- L89 _private prototype_ `FPCGPointTransformDelta* GetTransformDelta(TInstancedStruct<FPCGDeltaBase>* InstancedStructDelta);`
- L90 _private prototype_ `const FPCGPointTransformDelta* GetTransformDelta(const TInstancedStruct<FPCGDeltaBase>* InstancedStructDelta) const;`
- L93 _private member_ `TObjectPtr<UCombinedTransformGizmo> CombinedGizmo = nullptr;` — `UPROPERTY()`
- L96 _private member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY()`
- L98 _private member_ `FPCGDeltaKey CurrentDeltaKey;`
- L99 _private member_ `FPCGSourceDataStorageKey CurrentStorageKey;`
- L100 _private member_ `FPCGDeltaCollection* CurrentCollection = nullptr;`
- L101 _private member_ `TInstancedStruct<FPCGDeltaBase>* CurrentEditDelta = nullptr;`
- L103 _private member_ `bool bIsTransforming = false;`
- L106 _private member_ `TWeakObjectPtr<UStaticMesh> CachedMesh;` — Mesh wireframe cache — parallels FCachedMeshWireframe in PCGComponentVisualizer.cpp
- L107 _private member_ `TArray<uint32> CachedMeshIndices;`
- L108 _private member_ `const FPositionVertexBuffer* CachedPositionBuffer = nullptr;`
- L111 _private member_ `TMap<TObjectKey<const UPCGNode>, TSet<FPCGGraphExecutionInspection::FNodeExecutedNotificationData>> CachedNodeStacks;` — Cached copy of executed node stacks, updated via OnGraphExecuted callback to avoid a per-frame copy.

### `Plugins/PCG/Source/PCGEditor/Private/DataVisualizations/PCGVisualizationTexture2D.h` (Private)


#### struct `FPCGVisualizationTexture2DParams`  
`struct FPCGVisualizationTexture2DParams`  
_L17-22_
- L19 _public member_ `FTextureRHIRef TextureRHI = nullptr;`
- L20 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;`
- L21 _public member_ `uint16 SliceIndex = 0;`

#### class `UPCGVisualizationTexture2D`  
`class UPCGVisualizationTexture2D : public UTexture`  
_L30-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTexture`
- desc: UTexture implementation for visualizing PCG texture data in the data viewport. This is necessary because some texture data do not have their own UTexture, so one needs to be created in order to override the texture parameter for the debug vis material.
- L36 _public function_ `virtual ETextureClass GetTextureClass() const`
- L37 _public prototype_ `virtual FTextureResource* CreateResource() override;`
- L38 _public function_ `virtual EMaterialValueType GetMaterialType() const override`
- L39 _public prototype_ `virtual float GetSurfaceWidth() const override;`
- L40 _public prototype_ `virtual float GetSurfaceHeight() const override;`
- L41 _public function_ `virtual float GetSurfaceDepth() const override`
- L42 _public function_ `virtual uint32 GetSurfaceArraySize() const override`
- L45 _public prototype_ `void Init(const FPCGVisualizationTexture2DParams& InParams);`
- L48 _public prototype_ `static UPCGVisualizationTexture2D* Create(const FPCGVisualizationTexture2DParams& InParams);` — Creates and initializes a new UPCGVisualizationTexture2D from the texture data.
- L50 _public prototype_ `FTextureRHIRef GetTextureRHI() const;`
- L51 _public prototype_ `uint16 GetSliceIndex() const;`
- L54 _protected member_ `FTextureRHIRef TextureRHI = nullptr;`
- L55 _protected member_ `FIntPoint Resolution = FIntPoint::ZeroValue;`
- L56 _protected member_ `uint16 SliceIndex;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PCGTextureVisualizationConstants`
- L13 _variable_ `static const FSoftObjectPath PlaneMeshPath(TEXT("/Eng` (scope `PCGTextureVisualizationConstants`)
- L14 _variable_ `static const FSoftObjectPath DebugMaterialPath(TEXT("Mate` (scope `PCGTextureVisualizationConstants`)

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGDeltaViewportExtensionHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PCG`
- L10 _namespace_ `namespace DeltaViewportExtension` (scope `PCG`)
- L10 _namespace_ `namespace Helpers` (scope `PCG::DeltaViewportExtension`)
- L13 _prototype_ `FPCGDeltaCollection* GetMutableCollection(const FPCGDeltaViewportContext& Context);` (scope `PCG::DeltaViewportExtension::Helpers`) — Returns the mutable delta collection for the context's active storage key, or nullptr if any step in the chain is invalid.
- L16 _prototype_ `void MarkComponentDirty(UPCGComponent* PCGComponent, FPCGSourceDataContainer* DataContainer);` (scope `PCG::DeltaViewportExtension::Helpers`) — Mark the PCG component and its source data container as dirty, then notify the graph editor.

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGPointDeletionViewportExtension.h` (Private)


#### struct `FPCGPointDeletionDeltaEntry`  
`struct FPCGPointDeletionDeltaEntry`  
_L12-17_
- L14 _public member_ `FPCGDeltaKey Key;`
- L15 _public member_ `int32 OriginalElementIndex = INDEX_NONE;`
- L16 _public member_ `FVector Location = FVector::ZeroVector;`

#### class `FPCGPointDeletionViewportExtension`  
`class FPCGPointDeletionViewportExtension : public IPCGDeltaViewportExtension`  
_L20-54_
- inherits: `IPCGDeltaViewportExtension`
- desc: Viewport extension for FPCGPointDeletionDelta.
- L24 _public function_ `virtual FText GetDisplayName() const override`
- L25 _public function_ `virtual FName GetDeltaName() const override`
- L26 _public function_ `virtual int32 GetSortPriority() const override`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget(FPCGDeltaViewportCallbacks Callbacks) override;`
- L28 _public function_ `virtual void UpdateContext(const FPCGDeltaViewportContext& Context) override`
- L29 _public prototype_ `virtual void RefreshLists(const FPCGDeltaViewportContext& Context) override;`
- L30 _public function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override`
- L31 _public prototype_ `virtual FLinearColor GetDisplayColor(const bool bIsSelected) const override;`
- L32 _public prototype_ `virtual FTransform GetDisplayTransform(const FTransform& SourceElementTransform, const FConstStructView DeltaStruct) const override;`
- L33 _public prototype_ `virtual bool MatchesSourceElement(const FTransform& SourceElementTransform, const FConstStructView DeltaStruct, const double SpatialTolerance) const override;`
- L34 _public function_ `virtual bool UsesTRSGizmo() const override`
- L35 _public prototype_ `virtual FTransform GetOriginalTransform(const FConstStructView DeltaStruct) const override;`
- L36 _public prototype_ `virtual void CollectRestorableKeys(const FPCGDeltaCollection& Collection, TArray<FPCGDeltaKey>& OutKeys) const override;`
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateDeletionRow(TSharedPtr<FPCGPointDeletionDeltaEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L43 _private prototype_ `bool IsSelectionDeletionDelta() const;` — Returns true if the current selection points to a deletion delta in the collection.
- L46 _private prototype_ `void HandleDeletePressed();` — Toggles deletion on the selected point: creates a deletion delta or restores an existing one.
- L48 _private member_ `FPCGDeltaViewportContext CachedContext;`
- L49 _private member_ `FPCGDeltaViewportCallbacks CachedCallbacks;`
- L51 _private member_ `TArray<TSharedPtr<FPCGPointDeletionDeltaEntry>> DeletionEntries;`
- L52 _private member_ `TSharedPtr<SVerticalBox> DeletionSection;`
- L53 _private member_ `TSharedPtr<SListView<TSharedPtr<FPCGPointDeletionDeltaEntry>>> DeletionListView;`

#### Free symbols / members of external scopes

- L30 _function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override` (scope `FPCGPointDeletionViewportExtension::GetKeyBindings`)

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGPointInsertionViewportExtension.h` (Private)


#### struct `FPCGPointInsertionDeltaEntry`  
`struct FPCGPointInsertionDeltaEntry`  
_L14-19_
- L16 _public member_ `FPCGDeltaKey DeltaKey;`
- L17 _public member_ `int32 Index = INDEX_NONE;`
- L18 _public member_ `FVector Location = FVector::ZeroVector;`

#### class `FPCGPointInsertionViewportExtension`  
`class FPCGPointInsertionViewportExtension : public IPCGDeltaViewportExtension`  
_L28-69_
- inherits: `IPCGDeltaViewportExtension`
- desc: Viewport extension for FPCGPointInsertionDelta: Insert button + insertions list + viewport policy.
- L32 _public function_ `virtual FText GetDisplayName() const override`
- L33 _public function_ `virtual FName GetDeltaName() const override`
- L34 _public function_ `virtual int32 GetSortPriority() const override`
- L35 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget(FPCGDeltaViewportCallbacks Callbacks) override;`
- L36 _public function_ `virtual void UpdateContext(const FPCGDeltaViewportContext& Context) override`
- L37 _public prototype_ `virtual void RefreshLists(const FPCGDeltaViewportContext& Context) override;`
- L38 _public function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override`
- L39 _public prototype_ `virtual FLinearColor GetDisplayColor(const bool bIsSelected) const override;`
- L40 _public prototype_ `virtual void GetInsertedElements(const FPCGDeltaCollection& Collection, TArray<FInsertedViewportElement>& OutElements) const override;`
- L41 _public prototype_ `virtual int32 OnAltDrag(FPCGDeltaCollection& Collection, const FTransform& SourceTransform, FPCGDeltaKey& OutDeltaKey) const override;`
- L42 _public prototype_ `virtual bool ApplyGizmoTransform(const FTransform& NewTransform, TInstancedStruct<FPCGDeltaBase>& DeltaStruct, const int32 ElementIndex) const override;`
- L47 _private prototype_ `FPCGDeltaCollection* GetOrCreateMutableCollection(FPCGSourceDataContainer* DataContainer);` — Get or create the mutable delta collection from the cached context.
- L50 _private prototype_ `static FPCGPointInsertionDelta* FindOrCreateInsertionDelta(FPCGDeltaCollection* Collection, FPCGDeltaKey* OutKey = nullptr);` — Find or create the single insertion delta within the collection.
- L52 _private prototype_ `FReply OnInsertPointClicked();`
- L53 _private prototype_ `FReply OnRemoveAllClicked();`
- L55 _private prototype_ `void HandleDeletePressed();`
- L56 _private prototype_ `void AddInsertedElement();`
- L57 _private prototype_ `void UpdateInsertedElementLocation(const FPCGDeltaKey& DeltaKey, const int32 Index, const FVector& NewLocation);`
- L58 _private prototype_ `void RemoveInsertedElement(int32 Index);`
- L59 _private prototype_ `void RemoveAllInsertedElements();`
- L60 _private prototype_ `void OnInsertionComponentCommitted(const int32 EntryIndex, const int32 AxisIndex, const double NewValue);`
- L61 _private prototype_ `TSharedRef<ITableRow> OnGenerateInsertionRow(TSharedPtr<FPCGPointInsertionDeltaEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L63 _private member_ `FPCGDeltaViewportContext CachedContext;`
- L64 _private member_ `FPCGDeltaViewportCallbacks CachedCallbacks;`
- L66 _private member_ `TArray<TSharedPtr<FPCGPointInsertionDeltaEntry>> InsertionEntries;`
- L67 _private member_ `TSharedPtr<SVerticalBox> InsertionListSection;`
- L68 _private member_ `TSharedPtr<SListView<TSharedPtr<FPCGPointInsertionDeltaEntry>>> InsertionListView;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace PCGInsertionConstants`
- L24 _variable_ `constexpr FXxHash64 DefaultInsertionKeyHash{1};` (scope `PCGInsertionConstants`) — @todo_pcg: Find an appropriate hash value for the insertion delta key. Currently an arbitrary non-zero constant.
- L38 _function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override` (scope `FPCGPointInsertionViewportExtension::GetKeyBindings`)

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGPointTransformOffsetViewportExtension.h` (Private)


#### class `FPCGPointTransformOffsetViewportExtension`  
`class FPCGPointTransformOffsetViewportExtension : public FPCGPointTransformViewportExtensionBase`  
_L8-37_
- inherits: `FPCGPointTransformViewportExtensionBase`
- desc: Viewport extension for FPCGPointTransformOffsetDelta.
- L12 _public function_ `virtual FText GetDisplayName() const override`
- L13 _public function_ `virtual FName GetDeltaName() const override`
- L14 _public function_ `virtual int32 GetSortPriority() const override`
- L15 _public prototype_ `virtual FLinearColor GetDisplayColor(bool bIsSelected) const override;`
- L16 _public prototype_ `virtual FTransform GetDisplayTransform(const FTransform& SourceElementTransform, FConstStructView DeltaStruct) const override;`
- L17 _public prototype_ `virtual bool ApplyGizmoTransform(const FTransform& NewTransform, TInstancedStruct<FPCGDeltaBase>& DeltaStruct, int32 ElementIndex) const override;`
- L18 _public prototype_ `virtual void CreateNewDelta( const FPCGDeltaKey& DeltaKey, FPCGDeltaCollection& Collection, const FTransform& OriginalTransform, const FTransform& NewTransform, const FPCGDeltaCreateContext& Context) const override;`
- L28 _protected prototype_ `virtual FText GetCheckboxGroupLabel() const override;`
- L29 _protected prototype_ `virtual FText GetListHeaderLabel() const override;`
- L30 _protected prototype_ `virtual FVector GetDisplayVector(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`
- L31 _protected prototype_ `virtual void SetDisplayVector(TInstancedStruct<FPCGDeltaBase>& Delta, const FVector& NewValue) const override;`
- L32 _protected prototype_ `virtual bool IsManagedDelta(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`
- L33 _protected prototype_ `virtual void SetDeltaOverrideFlags(TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const override;`
- L34 _protected prototype_ `virtual bool DeltaOverrideFlagsMatch(const TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const override;`
- L35 _protected prototype_ `virtual int32 GetElementIndex(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGPointTransformViewportExtension.h` (Private)


#### class `FPCGPointTransformViewportExtension`  
`class FPCGPointTransformViewportExtension : public FPCGPointTransformViewportExtensionBase`  
_L8-33_
- inherits: `FPCGPointTransformViewportExtensionBase`
- desc: Viewport extension for FPCGPointTransformDelta: overrides point transforms via gizmo manipulation.
- L12 _public function_ `virtual FText GetDisplayName() const override`
- L13 _public function_ `virtual FName GetDeltaName() const override`
- L14 _public function_ `virtual int32 GetSortPriority() const override`
- L15 _public prototype_ `virtual FLinearColor GetDisplayColor(bool bIsSelected) const override;`
- L16 _public prototype_ `virtual FTransform GetDisplayTransform(const FTransform& SourceElementTransform, FConstStructView DeltaStruct) const override;`
- L17 _public prototype_ `virtual bool ApplyGizmoTransform(const FTransform& NewTransform, TInstancedStruct<FPCGDeltaBase>& DeltaStruct, int32 ElementIndex) const override;`
- L18 _public prototype_ `virtual void CreateNewDelta(const FPCGDeltaKey& DeltaKey, FPCGDeltaCollection& Collection, const FTransform& OriginalTransform, const FTransform& NewTransform, const FPCGDeltaCreateContext& Context) const override;`
- L24 _protected prototype_ `virtual FText GetCheckboxGroupLabel() const override;`
- L25 _protected prototype_ `virtual FText GetListHeaderLabel() const override;`
- L26 _protected prototype_ `virtual FVector GetDisplayVector(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`
- L27 _protected prototype_ `virtual void SetDisplayVector(TInstancedStruct<FPCGDeltaBase>& Delta, const FVector& NewValue) const override;`
- L28 _protected prototype_ `virtual bool IsManagedDelta(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`
- L29 _protected prototype_ `virtual void SetDeltaOverrideFlags(TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const override;`
- L30 _protected prototype_ `virtual bool DeltaOverrideFlagsMatch(const TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const override;`
- L31 _protected prototype_ `virtual int32 GetElementIndex(const TInstancedStruct<FPCGDeltaBase>& Delta) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/DeltaViewportExtensions/PCGPointTransformViewportExtensionBase.h` (Private)


#### struct `FPCGPointTransformDeltaEntry`  
`struct FPCGPointTransformDeltaEntry`  
_L17-22_
- desc: Shared list entry for point-transform viewport extensions. Stores a display vector that might represents an absolute position (ex. Point Transform), a local offset (ex. Point Transform Offset), etc.
- L19 _public member_ `FPCGDeltaKey Key;`
- L20 _public member_ `int32 OriginalElementIndex = INDEX_NONE;`
- L21 _public member_ `FVector DisplayVector = FVector::ZeroVector;`

#### class `FPCGPointTransformViewportExtensionBase`  
`class FPCGPointTransformViewportExtensionBase : public IPCGDeltaViewportExtension`  
_L25-81_
- inherits: `IPCGDeltaViewportExtension`
- desc: Shared base class for viewport extensions that edit a point's transform via a TRS gizmo and display a vector in a list view.
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget(FPCGDeltaViewportCallbacks Callbacks) override;`
- L30 _public function_ `virtual void UpdateContext(const FPCGDeltaViewportContext& Context) override`
- L31 _public prototype_ `virtual void RefreshLists(const FPCGDeltaViewportContext& Context) override;`
- L32 _public function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override`
- L33 _public prototype_ `virtual bool MatchesSourceElement(const FTransform& SourceElementTransform, const FConstStructView DeltaStruct, const double SpatialTolerance) const override;`
- L34 _public prototype_ `virtual FTransform GetOriginalTransform(const FConstStructView DeltaStruct) const override;`
- L39 _protected prototype_ `virtual FText GetCheckboxGroupLabel() const = 0;` — Returns the label for the checkbox group row.
- L42 _protected prototype_ `virtual FText GetListHeaderLabel() const = 0;` — Returns the header label for the list section.
- L45 _protected prototype_ `virtual FVector GetDisplayVector(const TInstancedStruct<FPCGDeltaBase>& Delta) const = 0;` — Returns the display vector from the given delta.
- L48 _protected prototype_ `virtual void SetDisplayVector(TInstancedStruct<FPCGDeltaBase>& Delta, const FVector& NewValue) const = 0;` — Sets the display vector on the given delta.
- L51 _protected prototype_ `virtual bool IsManagedDelta(const TInstancedStruct<FPCGDeltaBase>& Delta) const = 0;` — Returns true if the instanced struct is the delta type managed by this extension.
- L54 _protected prototype_ `virtual void SetDeltaOverrideFlags(TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const = 0;` — Sets the override flags on the given delta.
- L57 _protected prototype_ `virtual bool DeltaOverrideFlagsMatch(const TInstancedStruct<FPCGDeltaBase>& Delta, bool bPosition, bool bRotation, bool bScale) const = 0;` — Returns true if the delta's override flags match the provided values.
- L60 _protected prototype_ `virtual int32 GetElementIndex(const TInstancedStruct<FPCGDeltaBase>& Delta) const = 0;` — Returns the editor-only element index from the given delta.
- L62 _protected member_ `bool bOverridePosition = true;`
- L63 _protected member_ `bool bOverrideRotation = true;`
- L64 _protected member_ `bool bOverrideScale = true;`
- L66 _protected member_ `FPCGDeltaViewportContext CachedContext;`
- L67 _protected member_ `FPCGDeltaViewportCallbacks CachedCallbacks;`
- L69 _protected member_ `TArray<TSharedPtr<FPCGPointTransformDeltaEntry>> Entries;`
- L70 _protected member_ `TSharedPtr<SVerticalBox> ListSection;`
- L71 _protected member_ `TSharedPtr<SListView<TSharedPtr<FPCGPointTransformDeltaEntry>>> ListView;`
- L74 _private prototype_ `void HandleDeletePressed();`
- L75 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FPCGPointTransformDeltaEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L76 _private prototype_ `void OnComponentCommitted(const FPCGDeltaKey& EntryKey, int32 AxisIndex, double NewValue);`
- L77 _private prototype_ `void UpdateDisplayVector(const FPCGDeltaKey& DeltaKey, const FVector& NewValue);`
- L78 _private prototype_ `void RemoveEntry(const FPCGDeltaKey& EntryKey);`
- L79 _private prototype_ `void RemoveAllEntries();`
- L80 _private prototype_ `void UpdateFlags();`

#### Free symbols / members of external scopes

- L32 _function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings() override` (scope `FPCGPointTransformViewportExtensionBase::GetKeyBindings`)

### `Plugins/PCG/Source/PCGEditor/Private/DeltaVisualizations/PCGDeltaBaseVisualization.h` (Private)


#### class `FPCGDeltaBaseVisualization`  
`class FPCGDeltaBaseVisualization : public IPCGDeltaVisualization`  
_L8-13_
- inherits: `IPCGDeltaVisualization`
- desc: Default visualizer registered to FPCGDeltaBase. Shows common delta metadata columns.
- L11 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const override;`
- L12 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/DeltaVisualizations/PCGDeltaPointVisualization.h` (Private)


#### class `FPCGPointTransformDeltaVisualization`  
`class FPCGPointTransformDeltaVisualization : public IPCGDeltaVisualization`  
_L8-13_
- inherits: `IPCGDeltaVisualization`
- desc: Visualizer for FPCGPointTransformDelta. Extends base columns with transform override info.
- L11 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const override;`
- L12 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const override;`

#### class `FPCGPointTransformOffsetDeltaVisualization`  
`class FPCGPointTransformOffsetDeltaVisualization : public IPCGDeltaVisualization`  
_L16-21_
- inherits: `IPCGDeltaVisualization`
- desc: Visualizer for FPCGPointTransformOffsetDelta. Extends base columns with offset transform info.
- L19 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const override;`
- L20 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const override;`

#### class `FPCGPointDeletionDeltaVisualization`  
`class FPCGPointDeletionDeltaVisualization : public IPCGDeltaVisualization`  
_L24-29_
- inherits: `IPCGDeltaVisualization`
- desc: Visualizer for FPCGPointDeletionDelta. Extends base columns with original transform.
- L27 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const override;`
- L28 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const override;`

#### class `FPCGPointInsertionDeltaVisualization`  
`class FPCGPointInsertionDeltaVisualization : public IPCGDeltaVisualization`  
_L32-37_
- inherits: `IPCGDeltaVisualization`
- desc: Visualizer for FPCGPointInsertionDelta. Extends base columns with inserted point count.
- L35 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const override;`
- L36 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/DeltaVisualizations/PCGDeltaVisualizationHelpers.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PCGDeltaVisualization`
- L9 _namespace_ `namespace Helpers` (scope `PCGDeltaVisualization`)
- L12 _prototype_ `void AppendBaseDeltaColumns(TArray<FPCGDeltaVisualizerColumnInfo>& OutColumns);` (scope `PCGDeltaVisualization::Helpers`) — Appends the common base delta columns (Delta Type).
- L15 _prototype_ `void AppendSignatureColumn(TArray<FPCGDeltaVisualizerColumnInfo>& OutColumns, const FText& Tooltip);` (scope `PCGDeltaVisualization::Helpers`) — Appends the shared signature column with the given value.
- L18 _prototype_ `FText GetBaseDeltaCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta);` (scope `PCGDeltaVisualization::Helpers`) — Returns cell text for the common base delta columns. Returns empty text if the column is not handled.

### `Plugins/PCG/Source/PCGEditor/Private/Details/PCGComputeSourceDetails.h` (Private)


#### class `FPCGComputeSourceDetails`  
`class FPCGComputeSourceDetails : public IDetailCustomization`  
_L17-37_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for PCG Compute Sources.
- L20 _public prototype_ `FPCGComputeSourceDetails();`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _protected prototype_ `FText GetSourceText() const;`
- L27 _protected prototype_ `void OnSourceTextChanged(const FText& InText);`
- L28 _protected prototype_ `void OnSourceTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L29 _protected prototype_ `void OnSourceTextChangesApplied() const;`
- L30 _protected prototype_ `void SetComputeSourceText() const;`
- L32 _protected member_ `TWeakObjectPtr<UPCGComputeSource> ComputeSourceWeakPtr;`
- L33 _protected member_ `TSharedRef<FPCGHLSLSyntaxHighlighter> SyntaxHighlighter;`
- L34 _protected member_ `TSharedPtr<SPCGCodeEditorTextBox> SourceTextBox;`
- L36 _protected member_ `FText SourceText;`

### `Plugins/PCG/Source/PCGEditor/Private/Details/PCGInstancedPropertyBagOverrideDetails.h` (Private)


#### class `FPCGOverrideInstancedPropertyBagDetails`  
`class FPCGOverrideInstancedPropertyBagDetails : public IPropertyTypeCustomization`  
_L19-31_
- inherits: `IPropertyTypeCustomization`
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

#### class `FPCGOverrideInstancedPropertyBagDataDetails`  
`class FPCGOverrideInstancedPropertyBagDataDetails : public FPropertyBagInstanceDataDetails`  
_L33-62_
- inherits: `FPropertyBagInstanceDataDetails`
- L36 _public prototype_ `FPCGOverrideInstancedPropertyBagDataDetails(TSharedPtr<IPropertyHandle> InStructProperty, const TSharedPtr<IPropertyUtilities>& InPropUtils);`
- L38 _public prototype_ `virtual void OnChildRowAdded(IDetailPropertyRow& ChildRow) override;`
- L41 _private prototype_ `FReply OnResetToDefaultValue(TSharedPtr<IPropertyHandle> InPropertyHandle) const;`
- L42 _private prototype_ `EVisibility IsResetVisible(TSharedPtr<IPropertyHandle> InPropertyHandle) const;`
- L43 _private prototype_ `bool IsPropertyOverriddenByPin(TSharedPtr<IPropertyHandle> InPropertyHandle) const;`
- L45 _private member_ `TWeakObjectPtr<UPCGGraphInstance> Owner;`
- L46 _private member_ `TWeakObjectPtr<UPCGSettings> SettingsOwner;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> PropertiesIDsOverriddenHandle;`
- L50 _public prototype_ `~FPCGOverrideInstancedPropertyBagDataDetails();`
- L52 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L53 _public function_ `void OnStructChange(const FInstancedPropertyBag& Instance)`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdMode.h` (Private)


#### class `UPCGEditorMode`  
`class UPCGEditorMode : public UBaseLegacyWidgetEdMode`  
_L15-86_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseLegacyWidgetEdMode`
- desc: The unique state for the editor to be in, specific to PCG's toolkits.
- L21 _public member_ `const static FEditorModeID EM_PCGEditorModeId;` — Unique name for PCG Editor Mode
- L23 _public prototype_ `UPCGEditorMode();`
- L25 _public prototype_ `static void RegisterEditorMode();`
- L26 _public prototype_ `static void UnregisterEditorMode();`
- L29 _public prototype_ `virtual bool ProcessEditDelete() override;`
- L30 _public prototype_ `virtual bool ProcessEditCut() override;`
- L31 _public prototype_ `virtual bool CanAutoSave() const override;`
- L33 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;` — Override the viewport pivot, if needed.
- L35 _public prototype_ `virtual void Enter() override;` — Focus event when the Editor enters PCG Editor Mode.
- L37 _public prototype_ `virtual void Exit() override;` — Focus event when the Editor leaves PCG Editor Mode.
- L39 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;` — Used to restrict starting a tool, if a certain state is required beforehand.
- L40 _public prototype_ `virtual bool HasCustomViewportFocus() const override;`
- L41 _public prototype_ `virtual FBox ComputeCustomViewportFocus() const override;`
- L42 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;`
- L43 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L46 _public prototype_ `UPCGInteractiveToolBaseSettings* GetCurrentToolSettings() const;`
- L49 _public prototype_ `bool ActiveToolUsesTransformGizmo() const;` — True when the active PCG tool opts into the standard transform gizmo.
- L52 _protected prototype_ `virtual void CreateToolkit() override;`
- L53 _protected prototype_ `virtual TSharedRef<FLegacyEdModeWidgetHelper> CreateWidgetHelper() override;`
- L55 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L56 _protected prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L57 _protected prototype_ `virtual void OnToolPostBuild(UInteractiveToolManager* InToolManager, EToolSide InSide, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& ToolState);`
- L59 _protected prototype_ `void OnEditorClosed() const;`
- L60 _protected prototype_ `void AcceptActiveToolActionOrTool() const;`
- L61 _protected prototype_ `void CancelActiveToolActionOrTool() const;`
- L64 _protected prototype_ `void RegisterToolWithSwitchConfirmation(TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder);` — Registers a tool like UEdMode::RegisterTool, then rebinds its command to confirm discarding unapplied changes before switching tools.
- L67 _protected prototype_ `bool ConfirmDiscardOfActiveToolChanges() const;` — Returns true if the active tool has no unapplied changes, or if the user confirms discarding them.
- L69 _protected prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L81 _private member_ `bool bIsToolActive = false;`
- L82 _private member_ `bool bEnteredToolSinceLastTick = false;`
- L85 _private member_ `EToolManagerToolSwitchMode ToolSwitchModeToRestoreOnExit = EToolManagerToolSwitchMode::CustomizableAcceptIfAble;` — Tool switch mode to restore when exiting the mode.

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeCommands.h` (Private)


#### class `FPCGEditorModeCommands`  
`class FPCGEditorModeCommands : public TCommands<FPCGEditorModeCommands>`  
_L9-17_
- inherits: `TCommands<FPCGEditorModeCommands>`
- desc: General actions related to the PCG Editor Mode.
- L12 _public prototype_ `FPCGEditorModeCommands();`
- L14 _public prototype_ `virtual void RegisterCommands() override;`

#### class `FPCGEditorModePaletteCommands`  
`class FPCGEditorModePaletteCommands : public TCommands<FPCGEditorModePaletteCommands>`  
_L20-37_
- inherits: `TCommands<FPCGEditorModePaletteCommands>`
- desc: Actions related to the PCG Editor Mode Toolkit Palette.
- L23 _public prototype_ `FPCGEditorModePaletteCommands();`
- L26 _public member_ `TSharedPtr<FUICommandInfo> LoadSplineContextPalette;` — PCG EDITOR CONTEXTS
- L27 _public member_ `TSharedPtr<FUICommandInfo> LoadPaintContextPalette;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> LoadVolumeContextPalette;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> LoadQueryContextPalette;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> LoadManualContextPalette;`
- L34 _public prototype_ `virtual void RegisterCommands() override;`

#### class `FPCGEditorModeToolCommands`  
`class FPCGEditorModeToolCommands : public TInteractiveToolCommands<FPCGEditorModeToolCommands>`  
_L40-85_
- inherits: `TInteractiveToolCommands<FPCGEditorModeToolCommands>`
- desc: Tool specific actions.
- L43 _public prototype_ `FPCGEditorModeToolCommands();`
- L45 _public prototype_ `virtual void RegisterCommands() override;`
- L48 _public prototype_ `static void RegisterAllToolCommands();` — Register all Tool command sets. Call this in module startup
- L51 _public prototype_ `static void UnregisterAllToolCommands();` — Unregister all Tool command sets. Call this from module shutdown.
- L54 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;` — Needed to retrieve the CDOs to call GetActionSet directly on the tool.
- L65 _public member_ `TSharedPtr<FUICommandInfo> EnableDrawSplineTool;` — PCG EDITOR MODE TOOLS - Line Context
- L66 _public member_ `TSharedPtr<FUICommandInfo> EnableDrawSurfaceTool;`
- L67 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetLineContextToolCommands();`
- L70 _public member_ `TSharedPtr<FUICommandInfo> EnablePaintTool;` — PCG EDITOR MODE TOOLS - Paint Context
- L71 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetPaintContextToolCommands();`
- L74 _public member_ `TSharedPtr<FUICommandInfo> EnableVolumeTool;` — PCG EDITOR MODE TOOLS - Volume Context
- L75 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetVolumeContextToolCommands();`
- L78 _public member_ `TSharedPtr<FUICommandInfo> EnableQueryTool;` — PCG EDITOR MODE TOOLS - Query Context
- L79 _public member_ `TSharedPtr<FUICommandInfo> EnableIsolateTool;`
- L80 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetQueryContextToolCommands();`
- L83 _public member_ `TSharedPtr<FUICommandInfo> EnableManualEditTool;` — PCG EDITOR MODE TOOLS - Manual Edit Context
- L84 _public prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetManualEditContextToolCommands();`

#### Free symbols / members of external scopes

- L92 _macro_ `#define DECLARE_TOOL_COMMANDS(ToolCommandClassName) \` — Macro for the class declaration for each tool as a TInteractiveToolCommands class @todo_pcg: This is basically done elsewhere for other toolkits, but can probably be modernized using C++ Concepts @param ToolCommandClassName The tool's class name
- L102 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGDrawSplineCommands);` — Define all tools commands here
- L103 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGDrawSurfaceCommands);`
- L104 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGPaintCommands);`
- L105 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGVolumeCommands);`
- L106 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGQueryCommands);`
- L107 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGIsolateCommands);`
- L108 _prototype_ `DECLARE_TOOL_COMMANDS(FPCGManualEditCommands);`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PCG`
- L8 _namespace_ `namespace EditorMode` (scope `PCG`)
- L10 _variable_ `static constexpr float DefaultNotificationDuration = 2.5f;` (scope `PCG::EditorMode`)
- L12 _function_ `inline void DispatchEditorNotification(const FText& Text, const FText& SubText = FText{}, const float Duration = DefaultNotificationDuration)` (scope `PCG::EditorMode`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeSettings.h` (Private)


#### struct `FPCGPerInteractiveToolSettingSettings`  
`struct FPCGPerInteractiveToolSettingSettings`  
_L13-24_
- reflection: `USTRUCT()`
- L18 _public member_ `TSoftClassPtr<UPCGInteractiveToolSettings> SettingsClass;` — `UPROPERTY(EditAnywhere, Config, Category = "Default")`
- L23 _public member_ `TSoftObjectPtr<UPCGGraphInterface> DefaultGraph;` — `UPROPERTY(EditAnywhere, Config, Category = "Default", meta=(GetAssetFilter = "FilterBySettingsClass"))` — `UPROPERTY(EditAnywhere, Config, Category = "Default")` — @todo_pcg GetAssetFilter only works on UClasses due to need for UFUNCTION. Will reenable this via details customization instead.

#### class `UPCGEditorModeSettings`  
`class UPCGEditorModeSettings : public UDeveloperSettings`  
_L28-77_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, DisplayName = "PCG Editor Mode Settings")`
- inherits: `UDeveloperSettings`
- desc: User preferences related to the PCG Editor Mode.
- L33 _public prototype_ `UPCGEditorModeSettings(const FObjectInitializer& ObjectInitializer);`
- L35 _public function_ `virtual FName GetContainerName() const override`
- L36 _public function_ `virtual FName GetCategoryName() const override`
- L37 _public function_ `virtual FName GetSectionName() const override`
- L41 _public member_ `bool bEnableEditorMode = true;` — `UPROPERTY(EditAnywhere, Config, Category = "General", meta = (DisplayName = "Enable the PCG Editor Mode Toolkit (requires restart)", ConfigRestartRequired = true))` — Editor Mode user configurations.
- L47 _public member_ `float GraphRefreshRate = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Component", meta = ( ForceUnits = "Seconds", ConsoleVariable = "pcg.editormode.GraphRefreshRate"))` — The rate at which PCG Graphs will be refreshed while actively editing with a tool.
- L54 _public member_ `bool bHideToolButtonsDuringActiveTool = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Tools", meta = ( EditCondition = "bEnableEditorMode", EditConditionHides, ConsoleVariable = "pcg.editormode.HideToolButtonsDuringActiveTool"))` — Hide the tool buttons from the UI when a tool is actively being used.
- L61 _public member_ `bool bShowEditorToastOnToolErrors = true;` — `UPROPERTY(EditAnywhere, Config, Category = "Tools", meta = ( EditCondition = "bEnableEditorMode", EditConditionHides, ConsoleVariable = "pcg.editormode.ShowEditorToastOnToolErrors"))` — Enable an editor toast issued when an Editor Mode tool has an error.
- L64 _public member_ `bool bDisableTemporalAntiAliasingWhenEnteringTool = false;` — `UPROPERTY(EditAnywhere, Config, Category = "Tools", meta = (EditCondition = "bEnableEditorMode", EditConditionHides))`
- L67 _public member_ `FName DefaultNewActorName = "PC` — `UPROPERTY(EditAnywhere, Category = "Tools|Output", meta = (EditCondition = "bEnableEditorMode", EditConditionHides))`
- L70 _public member_ `FName DefaultNewPCGComponentName = "PC` — `UPROPERTY(EditAnywhere, Category = "Tools|Output", meta = (EditCondition = "bEnableEditorMode", EditConditionHides))`
- L73 _public member_ `FName DefaultNewSplineComponentName = "PC` — `UPROPERTY(EditAnywhere, Category = "Tools|Output|Spline", meta = (EditCondition = "bEnableEditorMode", EditConditionHides))`
- L76 _public member_ `TArray<FPCGPerInteractiveToolSettingSettings> InteractiveToolSettings;` — `UPROPERTY(EditAnywhere, Config, Category = "Tools")`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeStyle.h` (Private)


#### class `FPCGEditorModeStyle`  
`class FPCGEditorModeStyle : public FSlateStyleSet`  
_L10-20_
- inherits: `FSlateStyleSet`
- desc: Style details specific to the PCG Editor Mode.
- L13 _public prototype_ `static void Register();`
- L14 _public prototype_ `static void Unregister();`
- L16 _public prototype_ `static const FPCGEditorModeStyle& Get();`
- L19 _private prototype_ `FPCGEditorModeStyle();`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/PCGEdModeToolkit.h` (Private)


#### class `FPCGEditorModeToolkitBuilder`  
`class FPCGEditorModeToolkitBuilder : public FToolkitBuilder`  
_L18-25_
- inherits: `FToolkitBuilder`
- desc: A customized Toolkit Builder used for the PCG Editor Mode
- L21 _public prototype_ `explicit FPCGEditorModeToolkitBuilder(FToolkitBuilderArgs& Args);`
- L24 _protected prototype_ `virtual void UpdateContentForCategory(FName InActiveCategoryName, FText InActiveCategoryText) override;`

#### struct `FPCGToolPalette`  
`struct FPCGToolPalette : FToolPalette`  
_L27-32_
- inherits: `FToolPalette`
- L29 _public prototype_ `FPCGToolPalette(TSharedPtr<FUICommandInfo> InLoadToolPaletteAction, const TArray<TSharedPtr<FUICommandInfo>>& InPaletteActions);`

#### class `FPCGEditorModeToolkit`  
`class FPCGEditorModeToolkit : public FModeToolkit`  
_L35-115_
- inherits: `FModeToolkit`
- desc: The basic toolkit needed to show the docked editor mode panel and set up the tool shelves and details views.
- L39 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> OwningMode) override;`
- L40 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L41 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L44 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;` — Returns the PCG Editor Mode specific tabs in the mode toolbar
- L45 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName PaletteName) const override;`
- L46 _public prototype_ `virtual void OnToolPaletteChanged(FName PaletteName) override;`
- L47 _public function_ `virtual bool HasIntegratedToolPalettes() const override`
- L48 _public prototype_ `virtual void BuildToolPalette(FName Palette, class FToolBarBuilder& ToolbarBuilder) override;`
- L50 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L51 _public prototype_ `virtual FText GetActiveToolMessage() const override;`
- L53 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L54 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L57 _public function_ `virtual TSharedPtr<SWidget> GetInlineContent() const override` — Keep track of the widget for customization.
- L60 _public prototype_ `virtual void PostToolNotification(const FText& Message);`
- L61 _public prototype_ `virtual void ClearToolNotification();`
- L63 _public prototype_ `virtual void PostToolWarning(const FText& Message);`
- L64 _public prototype_ `virtual void ClearToolWarning();`
- L66 _public prototype_ `virtual void ShowModeWarnings();`
- L69 _public prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport>, TSharedPtr<IAssetViewport>) const;` — UI Events
- L72 _public prototype_ `const FSlateBrush* GetActiveToolIcon() const;` — Accept/Cancel Window
- L73 _public prototype_ `bool IsAcceptButtonEnabled() const;`
- L74 _public prototype_ `bool IsCancelButtonEnabled() const;`
- L75 _public prototype_ `EVisibility GetAcceptButtonVisibility() const;`
- L76 _public prototype_ `EVisibility GetCancelButtonVisibility() const;`
- L77 _public prototype_ `FReply OnAcceptButtonClicked() const;`
- L78 _public prototype_ `FReply OnCancelButtonClicked() const;`
- L80 _public prototype_ `void UpdatePresets();`
- L82 _public prototype_ `TSharedPtr<FPCGToolPalette> GetActivePCGToolPalette() const;`
- L84 _private prototype_ `void RegisterToolkitCallbacks();`
- L85 _private prototype_ `void UnregisterToolkitCallbacks();`
- L87 _private prototype_ `void RegisterToolCallbacks(UInteractiveTool* CurrentTool);`
- L88 _private prototype_ `void UnregisterToolCallbacks(UInteractiveTool* CurrentTool) const;`
- L90 _private prototype_ `void OnEditorModeSettingsChanged(UObject* InObject, FPropertyChangedEvent& InChangedEvent);`
- L92 _private prototype_ `void UpdateActiveTool();`
- L93 _private prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject) const;`
- L96 _private prototype_ `void RegisterPalettes();` — A utility function to register the tool palettes with the ToolkitBuilder.
- L98 _private prototype_ `void CreateWidgets();` — A utility function to create additional widgets for the Toolkit.
- L100 _private prototype_ `void OnActivePaletteChanged();`
- L103 _private member_ `TSharedPtr<SPCGEdModeAcceptToolOverlay> AcceptToolWidget;` — UI overlay in the viewport to accept or cancel the current tool.
- L105 _private member_ `TSharedPtr<SPCGToolPresetSection> ToolPresetSection;`
- L108 _private member_ `FDelegateHandle ActivePaletteChangedHandle;` — Currently only used to cancel the current tool.
- L110 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L111 _private member_ `FText ActiveWarning{};`
- L112 _private member_ `FInteractiveToolInfo CachedActiveToolInfo;`
- L114 _private member_ `TOptional<FName> LastPaletteWithActiveTool;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Gizmos/PCGGizmos.h` (Private)


#### enum `EPCGBrushMode`  
`enum class EPCGBrushMode`  
_L24-28_
- reflection: `UENUM()`
- L26 _public enumerator_ `Sphere`
- L27 _public enumerator_ `Box`

#### class `UVolumetricBoxBrushStampIndicatorBuilder`  
`class UVolumetricBoxBrushStampIndicatorBuilder : public UInteractiveGizmoBuilder`  
_L31-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder`
- L35 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;`

#### class `UPCGVolumetricBrushStampIndicator`  
`class UPCGVolumetricBrushStampIndicator : public UBrushStampIndicator`  
_L39-73_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UBrushStampIndicator`
- L44 _public prototype_ `virtual void Setup() override;`
- L45 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L46 _public prototype_ `virtual void Shutdown() override;`
- L48 _public prototype_ `void SetVolumetricBrushVisible(bool bInVisible);`
- L50 _public prototype_ `bool IsVolumetricBrushVisible() const;`
- L52 _public prototype_ `void MakeBrushIndicatorMesh(UInteractiveTool* ParentTool, UWorld* World);`
- L54 _public prototype_ `UPreviewMesh* GetPreviewMesh() const;`
- L56 _public prototype_ `void AddYawRotation(float AddYawRotation);`
- L58 _public prototype_ `void SetBrushMode(EPCGBrushMode InBrushMode);`
- L60 _protected prototype_ `void GenerateMesh(EPCGBrushMode InBrushMode);`
- L63 _private member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L66 _private member_ `bool bDrawExtents = true;` — `UPROPERTY()`
- L69 _private member_ `bool bDrawDirections = true;` — `UPROPERTY()`
- L72 _private member_ `EPCGBrushMode BrushMode = EPCGBrushMode::Sphere;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace PCG` (scope `UE`)
- L13 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L13 _namespace_ `namespace Gizmos` (scope `UE::PCG::EditorMode`)
- L15 _namespace_ `namespace Constants` (scope `UE::PCG::EditorMode::Gizmos`)
- L17 _variable_ `const FString BrushIdentifier_VolumetricBox = "Vo` (scope `UE::PCG::EditorMode::Gizmos::Constants`)
- L20 _prototype_ `UMaterialInstanceDynamic* GetDefaultVolumeBrushMaterial(UInteractiveToolManager* ToolManager);` (scope `UE::PCG::EditorMode::Gizmos`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Helpers/PCGEdModeActorHelpers.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PCG` (scope `UE`)
- L7 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L9 _namespace_ `namespace Tags` (scope `UE::PCG::EditorMode`)
- L11 _variable_ `const FLazyName ToolGeneratedTag = "PC` (scope `UE::PCG::EditorMode::Tags`)
- L14 _namespace_ `namespace Actor` (scope `UE::PCG::EditorMode`)
- L17 _prototype_ `AActor* Spawn(const UPCGActorHelpers::FSpawnDefaultActorParams& SpawnParams);` (scope `UE::PCG::EditorMode::Actor`) — Spawn an actor for the toolkit with spawn parameters.
- L19 _prototype_ `AActor* Spawn(UWorld* World, FName ActorName, const FTransform& Transform = FTransform::Identity);` (scope `UE::PCG::EditorMode::Actor`) — Spawn an actor for the toolkit with explicit parameters.
- L21 _prototype_ `AActor* SpawnWorking(UWorld* World, const FTransform& Transform = FTransform::Identity, TSubclassOf<AActor> ActorClass = AActor::StaticClass());` (scope `UE::PCG::EditorMode::Actor`) — Helper to spawn a temporary working actor for a tool.
- L24 _namespace_ `namespace PCGComponent` (scope `UE::PCG::EditorMode`)
- L27 _prototype_ `UPCGComponent* Find(const AActor* Owner, const FName ToolTag);` (scope `UE::PCG::EditorMode::PCGComponent`) — Find a PCG Component on an actor if it exists.
- L29 _prototype_ `UPCGComponent* Create(AActor* Owner, FName ComponentName);` (scope `UE::PCG::EditorMode::PCGComponent`) — Spawn a PCG Component on an actor.
- L31 _prototype_ `UPCGComponent* CreateWorking(AActor* Owner);` (scope `UE::PCG::EditorMode::PCGComponent`) — Helper to spawn a temporary working PCG component for a tool.

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Helpers/PCGEdModeEditorUtilities.h` (Private)


#### struct `UE::PCG::EditorMode::Utility::FPCGGraphToolEditorData`  
`struct FPCGGraphToolEditorData`  
_L16-20_
- L18 _public member_ `FAssetData AssetData;`
- L19 _public member_ `FPCGGraphToolData GraphToolData;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace PCG` (scope `UE`)
- L14 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L14 _namespace_ `namespace Utility` (scope `UE::PCG::EditorMode`)
- L22 _prototype_ `TArray<FPCGGraphToolEditorData> GetGraphToolsWithToolTag(FName ToolTag);` (scope `UE::PCG::EditorMode::Utility`)
- L24 _prototype_ `bool DoesPCGGraphInterfaceHaveToolTag(FName ToolTag, const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L25 _prototype_ `bool IsPCGGraphInterfaceCompatibleWithActor(AActor* Actor, const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L27 _prototype_ `TOptional<FPCGGraphToolData> GetGraphToolDataFromPCGGraphInterface(const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L29 _prototype_ `TOptional<FPCGGraphToolData> GetARGraphToolDataFromPCGGraph(const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L30 _prototype_ `TOptional<FPCGGraphToolData> GetARGraphToolDataFromPCGGraphInstance(const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L32 _prototype_ `TOptional<FPCGGraphInstanceToolDataOverrides> GetARGraphToolDataOverridesFromPCGGraphInstance(const FAssetData& AssetData);` (scope `UE::PCG::EditorMode::Utility`)
- L34 _prototype_ `TArray<TSharedPtr<FUICommandInfo>> GetOrCreateUICommandsWithToolTag(TSharedRef<FBindingContext> BindingContext, FName ToolTag);` (scope `UE::PCG::EditorMode::Utility`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Helpers/PCGEdModeSceneQueryHelpers.h` (Private)


#### struct `FPCGRaycastFilterRule`  
`struct FPCGRaycastFilterRule`  
_L18-34_
- reflection: `USTRUCT()`
- L22 _public prototype_ `FPCGRaycastFilterRule();`
- L23 _public prototype_ `virtual ~FPCGRaycastFilterRule();`
- L29 _public function_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const` — If this returns false, the raycast hit is filtered out. If it returns true, this rule has determined is valid under this given rule. If it returns an empty TOptional, this rule doesn't apply to the hit.
- L33 _public member_ `bool bEnabled = true;` — `UPROPERTY()` — Whether this rule is enabled or not. Not exposed as editing is done via custom UI.

#### struct `FPCGRaycastFilterRule_Landscape`  
`struct FPCGRaycastFilterRule_Landscape : public FPCGRaycastFilterRule`  
_L37-42_
- reflection: `USTRUCT(DisplayName="Landscape")`
- inherits: `FPCGRaycastFilterRule`
- L41 _public prototype_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const override;`

#### struct `FPCGRaycastFilterRule_Meshes`  
`struct FPCGRaycastFilterRule_Meshes : public FPCGRaycastFilterRule`  
_L45-50_
- reflection: `USTRUCT(DisplayName="Meshes")`
- inherits: `FPCGRaycastFilterRule`
- L49 _public prototype_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const override;`

#### struct `FPCGRaycastFilterRule_IgnorePCGGeneratedComponents`  
`struct FPCGRaycastFilterRule_IgnorePCGGeneratedComponents : public FPCGRaycastFilterRule`  
_L53-58_
- reflection: `USTRUCT(DisplayName="Ignore PCG Components")`
- inherits: `FPCGRaycastFilterRule`
- L57 _public prototype_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const override;`

#### struct `FPCGRaycastFilterRule_ConstrainToActor`  
`struct FPCGRaycastFilterRule_ConstrainToActor : public FPCGRaycastFilterRule`  
_L61-69_
- reflection: `USTRUCT(DisplayName="Constrain to Actor")`
- inherits: `FPCGRaycastFilterRule`
- L65 _public prototype_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const override;`
- L68 _public member_ `TObjectPtr<AActor> SelectedActor;` — `UPROPERTY(EditAnywhere, Category= "Raycast")`

#### struct `FPCGRaycastFilterRule_AllowedClasses`  
`struct FPCGRaycastFilterRule_AllowedClasses : public FPCGRaycastFilterRule`  
_L73-81_
- reflection: `USTRUCT(DisplayName="Allowed Classes")`
- inherits: `FPCGRaycastFilterRule`
- desc: The Ray will only be valid when the hit actor belongs to any of the specified classes.
- L77 _public prototype_ `virtual TOptional<bool> IsRaycastHitValid(const FHitResult& HitResult) const override;`
- L80 _public member_ `TSet<TSubclassOf<AActor>> AllowedClasses;` — `UPROPERTY(EditAnywhere, Category= "Raycast")`

#### struct `FPCGRaycastFilterRuleCollection`  
`struct FPCGRaycastFilterRuleCollection`  
_L85-94_
- reflection: `USTRUCT()`
- desc: A collection struct used for details customization purposes. This allows us to add the collection to any PCGInteractiveToolSettings class where required.
- L89 _public prototype_ `TOptional<bool> IsRaycastHitValid(const FHitResult& RaycastHit) const;`
- L93 _public member_ `TArray<TInstancedStruct<FPCGRaycastFilterRule>> RaycastRules;` — `UPROPERTY(EditAnywhere, Category = "Raycast", meta=(ExcludeBaseStruct))` — The raycast rules for a given tool.

#### struct `UE::PCG::EditorMode::Scene::FViewRayParams`  
`struct FViewRayParams`  
_L99-108_
- desc: Custom parameters for UI ray casts from the current view into the scene.
- L101 _public member_ `const UWorld* World = nullptr;`
- L102 _public member_ `double Distance = UE_DOUBLE_BIG_NUMBER;`
- L103 _public member_ `const TArray<const UPrimitiveComponent*>* ComponentsToIgnore = nullptr;`
- L104 _public member_ `const TArray<const UPrimitiveComponent*>* AllowedInvisibleComponents = nullptr;`
- L105 _public member_ `const FPCGRaycastFilterRuleCollection* FilterRuleCollection = nullptr;`
- L106 _public member_ `const FViewCameraState* CameraState = nullptr;`
- L107 _public member_ `bool* bHitGroundPlanes = nullptr;`

#### struct `UE::PCG::EditorMode::Scene::FViewHitResult`  
`struct FViewHitResult`  
_L111-129_
- desc: The resulting data from a UI ray cast hit.
- L113 _public member_ `FVector ImpactPosition;`
- L114 _public member_ `FVector ImpactNormal;`
- L115 _public member_ `double Depth;`
- L117 _public function_ `FInputRayHit ToInputRayHit() const`

#### Free symbols / members of external scopes

- L96 _namespace_ `namespace UE`
- L96 _namespace_ `namespace PCG` (scope `UE`)
- L96 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L96 _namespace_ `namespace Scene` (scope `UE::PCG::EditorMode`)
- L132 _prototype_ `bool IsHitTargetVisible(const FHitResult& HitResult);` (scope `UE::PCG::EditorMode::Scene`) — The hit actor or primitive component is visible.
- L135 _prototype_ `TOptional<FHitResult> TraceToNearestObject(const FRay& WorldRay, const FViewRayParams& Params);` (scope `UE::PCG::EditorMode::Scene`) — Cast a ray and if a hit is recorded, return the hit result nearest object.
- L136 _prototype_ `TOptional<FHitResult> TraceToNearestObject(const FInputDeviceRay& Ray, const FViewRayParams& Params);` (scope `UE::PCG::EditorMode::Scene`)
- L139 _prototype_ `TOptional<FViewHitResult> ViewportRay(const FRay& WorldRay, const FViewRayParams& Params);` (scope `UE::PCG::EditorMode::Scene`) — Cast a ray from the view and if a hit is recorded, return a condensed view-related hit result.
- L140 _prototype_ `TOptional<FViewHitResult> ViewportRay(const FInputDeviceRay& Ray, const FViewRayParams& Params);` (scope `UE::PCG::EditorMode::Scene`)
- L143 _prototype_ `TOptional<FViewHitResult> ViewportRayAgainstPlane(const FRay& Ray, const FViewRayParams& Params, const FPlane& Plane, bool bTestAgainstWorld = true);` (scope `UE::PCG::EditorMode::Scene`) — Cast a ray from the view to a plane in space. If a hit is recorded, return a condensed view-related hit result.
- L144 _prototype_ `TOptional<FViewHitResult> ViewportRayAgainstPlane(const FInputDeviceRay& Ray, const FViewRayParams& Params, const FPlane& Plane, bool bTestAgainstWorld = true);` (scope `UE::PCG::EditorMode::Scene`)
- L147 _prototype_ `TOptional<FViewHitResult> ViewportRayAgainstCameraPlane(const FInputDeviceRay& Ray, const FViewRayParams& Params, const FViewCameraState& CameraState);` (scope `UE::PCG::EditorMode::Scene`) — Cast a ray from the view to a plane parallel to the user view. If a hit is recorded, return a condensed view-related hit result.

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Helpers/PCGEdModeSceneVisualizeHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PCG`
- L10 _namespace_ `namespace EditorMode` (scope `PCG`)
- L10 _namespace_ `namespace Scene` (scope `PCG::EditorMode`)
- L10 _namespace_ `namespace Visualize` (scope `PCG::EditorMode::Scene`)
- L13 _prototype_ `void Spline(const USplineComponent& Spline, IToolsContextRenderAPI& RenderAPI, int32 LatestIndex = INDEX_NONE, bool bShouldVisualizeScale = false, bool bShouldVisualizeTangents = true);` (scope `PCG::EditorMode::Scene::Visualize`) — Visualize a spline within the editor viewport.
- L16 _prototype_ `void SplineTangent(const USplineComponent& Spline, IToolsContextRenderAPI& RenderAPI, const int32 SplinePointIndex);` (scope `PCG::EditorMode::Scene::Visualize`) — Visualize a spline tangent within the editor viewport.

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Helpers/PCGEdModeSplineHelpers.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PCG` (scope `UE`)
- L10 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L10 _namespace_ `namespace Spline` (scope `UE::PCG::EditorMode`)
- L12 _prototype_ `USplineComponent* CreateComponent( AActor* Actor, FName ComponentName, const USplineComponent* TemplateComponent = nullptr, const bool bTransactional = false);` (scope `UE::PCG::EditorMode::Spline`)
- L18 _prototype_ `USplineComponent* CreateWorkingComponent(AActor* Actor);` (scope `UE::PCG::EditorMode::Spline`)
- L20 _prototype_ `USplineComponent* Find(const AActor* Actor, const int32 TargetIndex = INDEX_NONE);` (scope `UE::PCG::EditorMode::Spline`)
- L22 _prototype_ `void CopySplinePoints(const USplineComponent& Source, USplineComponent& Destination, const bool bTransactional = false);` (scope `UE::PCG::EditorMode::Spline`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Line/PCGDrawSplineTool.h` (Private)


#### enum `EPCGDrawSplineDrawMode`  
`enum class EPCGDrawSplineDrawMode : uint8`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `TangentDrag UMETA(ToolTip = "Click to place a point and then drag to set its tangent. Clicking without dragging will create sharp corners.")`
- L22 _public enumerator_ `ClickAutoTangent UMETA(ToolTip = "Click and drag new points, with the tangent set automatically.")`
- L23 _public enumerator_ `FreeDraw UMETA(ToolTip = "Drag to place multiple points, with spacing controlled by Min Point Spacing.")`
- L24 _public enumerator_ `None UMETA(Hidden)`

#### class `UPCGInteractiveToolSettings_SplineBase`  
`class UPCGInteractiveToolSettings_SplineBase : public UPCGInteractiveToolSettings`  
_L28-69_
- reflection: `UCLASS(Abstract)`
- inherits: `UPCGInteractiveToolSettings`
- L33 _public prototype_ `UPCGInteractiveToolSettings_SplineBase();`
- L35 _public prototype_ `USplineComponent* GetWorkingSplineComponent(FName DataInstanceIdentifier) const;`
- L36 _public prototype_ `TArray<USplineComponent*> GetWorkingSplineComponents() const;`
- L39 _public member_ `EPCGDrawSplineDrawMode DrawMode = EPCGDrawSplineDrawMode::FreeDraw;` — `UPROPERTY(EditAnywhere, Category = "Spline")`
- L47 _public member_ `double MinPointSpacing = 200.0;` — `UPROPERTY(EditAnywhere, Category = "Spline", meta = ( ClampMin = 0, UIMax = 1000, EditCondition = "DrawMode == EPCGDrawSplineDrawMode::FreeDraw", EditConditionHides))` — Minimum world distance to cover while free drawing before a point will be generated.
- L50 _public member_ `FName SplineName;` — `UPROPERTY(EditAnywhere, Category = "Spline", meta = (TransientToolProperty))`
- L55 _public member_ `FPCGRaycastFilterRuleCollection RaycastRuleCollection;` — `UPROPERTY(EditAnywhere, Category= "Raycast")` — The raycast rules that determine whether a raycast is valid or not. Used to determine different raycast targets such as landscapes, meshes, selected actor etc.
- L59 _public member_ `bool bHitGroundPlanes = true;` — `UPROPERTY(EditAnywhere, Category= "Raycast")` — Whether to place spline points on a plane through the origin aligned with the Z axis in perspective views, or facing the camera in othographic views
- L63 _public member_ `FPCGToolRaycastSettings Settings{};` — `UPROPERTY(EditAnywhere, Category = "Raycast", meta = (ShowOnlyInnerProperties))` — The settings to manipulate raycast results, such as normals or offsets of a spline point.
- L68 _protected prototype_ `virtual bool IsWorkingActorCompatibleInternal(const AActor* InActor) const override final;` — This function is called indirectly by the builder using UPCGInteractiveToolSettings_SplineBase default class which prohibits to have override implementation of this function by child classes. Mark it final for that reason, to be revisited if we change the tool classes hierarchy.

#### class `UPCGInteractiveToolSettings_Spline`  
`class UPCGInteractiveToolSettings_Spline : public UPCGInteractiveToolSettings_SplineBase`  
_L72-86_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveToolSettings_SplineBase`
- L77 _protected prototype_ `virtual const UScriptStruct* GetWorkingDataType() const override;`
- L78 _protected prototype_ `virtual FName GetToolTag() const override;`
- L79 _protected prototype_ `virtual void PostWorkingDataInitialized(FPCGInteractiveToolWorkingData* WorkingData) const override;`
- L80 _protected prototype_ `virtual void OnPropertyModified(UObject* Object, FProperty* Property) override;`
- L83 _public member_ `bool bClosedSpline = false;` — `UPROPERTY(EditAnywhere, Category = "Spline")`
- L85 _public prototype_ `static FName StaticGetToolTag();`

#### class `UPCGInteractiveToolSettings_SplineSurface`  
`class UPCGInteractiveToolSettings_SplineSurface : public UPCGInteractiveToolSettings_SplineBase`  
_L90-100_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveToolSettings_SplineBase`
- L95 _protected prototype_ `virtual const UScriptStruct* GetWorkingDataType() const override;`
- L96 _protected prototype_ `virtual FName GetToolTag() const override;`
- L99 _public prototype_ `static FName StaticGetToolTag();`

#### class `UPCGDrawSplineToolBase`  
`class UPCGDrawSplineToolBase : public UInteractiveTool, public IClickBehaviorTarget, public IClickDragBehaviorTarget`  
_L103-149_
- reflection: `UCLASS(Abstract, Experimental)`
- inherits: `UInteractiveTool,IClickBehaviorTarget,IClickDragBehaviorTarget`
- L109 _public prototype_ `virtual void Setup() override;`
- L110 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L111 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L113 _public function_ `virtual bool HasCancel() const override`
- L114 _public function_ `virtual bool HasAccept() const override`
- L115 _public prototype_ `virtual bool CanAccept() const override;`
- L116 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L120 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPosition) override;`
- L121 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPosition) override;`
- L125 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& DragPosition) override;`
- L126 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& ClickPosition) override;`
- L127 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPosition) override;`
- L128 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePosition) override;`
- L129 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L132 _public prototype_ `UPCGInteractiveToolSettings_SplineBase* GetSplineSettings() const;`
- L134 _private prototype_ `void AddSplinePoint(const FVector& HitLocation, const FVector& HitNormal) const;`
- L135 _private prototype_ `FVector GetNewPointNormal(const FVector& HitNormal) const;`
- L137 _private prototype_ `void ClearSplineOnFirstInteraction(UPCGInteractiveToolSettings_SplineBase* InSettings, const FVector& NewStartingLocation);`
- L140 _private member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior = nullptr;` — `UPROPERTY(Instanced)`
- L142 _private member_ `UE::PCG::EditorMode::Scene::FViewRayParams CachedRayParams{};`
- L143 _private member_ `FViewCameraState CachedCameraState;`
- L144 _private member_ `bool bDrawTangentForPreviousPoint = false;`
- L145 _private member_ `bool bFreeDrawPlacedPreviewPoint = false;`
- L146 _private member_ `int32 FreeDrawStrokeStartIndex = 0;`
- L148 _private member_ `EPCGDrawSplineDrawMode PreviousDrawMode = EPCGDrawSplineDrawMode::None;`

#### class `UPCGDrawSplineTool`  
`class UPCGDrawSplineTool : public UPCGDrawSplineToolBase`  
_L152-161_
- reflection: `UCLASS(Experimental)`
- inherits: `UPCGDrawSplineToolBase`
- L157 _public prototype_ `virtual void Setup() override;`
- L160 _public member_ `TObjectPtr<UPCGInteractiveToolSettings_Spline> ToolSettings;` — `UPROPERTY(Transient)`

#### class `UPCGDrawSplineSurfaceTool`  
`class UPCGDrawSplineSurfaceTool : public UPCGDrawSplineToolBase`  
_L164-173_
- reflection: `UCLASS(Experimental)`
- inherits: `UPCGDrawSplineToolBase`
- L169 _public prototype_ `virtual void Setup() override;`
- L172 _public member_ `TObjectPtr<UPCGInteractiveToolSettings_SplineSurface> ToolSettings;` — `UPROPERTY(Transient)`

#### class `UPCGDrawSplineToolBuilder`  
`class UPCGDrawSplineToolBuilder : public UPCGInteractiveToolBuilder`  
_L176-188_
- reflection: `UCLASS(Transient)`
- inherits: `UPCGInteractiveToolBuilder`
- L181 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L182 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L184 _public prototype_ `void SetSplineToolClass(TSubclassOf<UPCGDrawSplineToolBase> InClass);`
- L187 _private member_ `TSubclassOf<UPCGDrawSplineToolBase> SplineToolClass;` — `UPROPERTY()`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/ManualEdit/PCGManualEditTool.h` (Private)


#### class `UPCGInteractiveToolSettings_ManualEdit`  
`class UPCGInteractiveToolSettings_ManualEdit : public UPCGInteractiveToolBaseSettings`  
_L15-37_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UPCGInteractiveToolBaseSettings`
- L20 _public prototype_ `UPCGInteractiveToolSettings_ManualEdit() = default;`
- L22 _public prototype_ `static FName StaticGetToolTag();`
- L24 _public function_ `virtual FName GetToolTag() const override`
- L26 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;`
- L29 _public member_ `TWeakObjectPtr<AActor> SelectedActor;` — `UPROPERTY(VisibleAnywhere, Category = "Manual Edit")`
- L32 _public member_ `TArray<TWeakObjectPtr<UPCGComponent>> TrackedPCGComponents;` — `UPROPERTY(VisibleAnywhere, Category = "Manual Edit")`
- L36 _public member_ `int32 SpawnerNodeCount = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Manual Edit", DisplayName = "Static Mesh Spawner Nodes")` — The number of nodes with Static Mesh Spawners in the graph. Useful data to see in the tool properties panel.

#### class `UPCGManualEditTool`  
`class UPCGManualEditTool : public UPCGInteractiveTool`  
_L40-79_
- reflection: `UCLASS(Experimental)`
- inherits: `UPCGInteractiveTool`
- L45 _public prototype_ `virtual void Setup() override;`
- L46 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L48 _public function_ `virtual bool HasCancel() const override`
- L49 _public function_ `virtual bool HasAccept() const override`
- L50 _public prototype_ `virtual bool CanAccept() const override;`
- L52 _public function_ `virtual bool RequiresSettings() const override`
- L55 _public function_ `virtual bool UsesTransformGizmo() const override` — Manual Edit selects a PCG-spawned element and uses the standard transform gizmo to create an override.
- L57 _public prototype_ `static FName StaticGetToolTag();`
- L62 _private prototype_ `void RefreshFromSelectedActor();`
- L63 _private prototype_ `void EnableSpawnersOnComponent(UPCGComponent* InComponent);`
- L64 _private prototype_ `void RestoreEnabledSpawners();`
- L65 _private prototype_ `void OnEditorSelectionChanged(UObject* Object);`
- L66 _private prototype_ `void OnPostUndoRedo();`
- L69 _private member_ `TObjectPtr<UPCGInteractiveToolSettings_ManualEdit> ToolSettings;` — `UPROPERTY(Transient)`
- L71 _private member_ `TArray<TWeakObjectPtr<UPCGNode>> EnabledSpawnerNodes;`
- L72 _private member_ `FDelegateHandle SelectionChangedDelegateHandle;`
- L73 _private member_ `FDelegateHandle PostUndoRedoHandle;`
- L74 _private member_ `bool bReSyncingSelection = false;`
- L75 _private member_ `bool bClampingUndoRedo = false;`
- L78 _private member_ `int32 TransactionHistoryMarker = INDEX_NONE;` — Transactor queue length captured to revert all manual edit transactions on Cancel.

#### class `UPCGManualEditToolBuilder`  
`class UPCGManualEditToolBuilder : public UPCGInteractiveToolBuilder`  
_L82-89_
- reflection: `UCLASS(Transient)`
- inherits: `UPCGInteractiveToolBuilder`
- L87 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L88 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/PCGInteractiveToolBuilder.h` (Private)


#### class `UPCGInteractiveToolBuilder`  
`class UPCGInteractiveToolBuilder : public UInteractiveToolBuilder`  
_L16-31_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- L22 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L23 _public prototype_ `virtual void PostSetupTool(UInteractiveTool* InTool, const FToolBuilderState& SceneState) const override;`
- L26 _public function_ `void SetToolGraph(UPCGGraph* InGraph)`
- L27 _public function_ `UPCGGraph* GetToolGraph() const`
- L30 _private member_ `TObjectPtr<UPCGGraph> ToolGraph;` — `UPROPERTY()`

#### class `UPCGInteractiveToolWithToolTargetsBuilder`  
`class UPCGInteractiveToolWithToolTargetsBuilder : public UInteractiveToolWithToolTargetsBuilder`  
_L34-48_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolWithToolTargetsBuilder`
- L40 _public prototype_ `virtual void PostSetupTool(UInteractiveTool* InTool, const FToolBuilderState& SceneState) const override;`
- L43 _public function_ `void SetToolGraph(UPCGGraph* InGraph)`
- L44 _public function_ `UPCGGraph* GetToolGraph() const`
- L47 _private member_ `TObjectPtr<UPCGGraph> ToolGraph;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PCG` (scope `UE`)
- L10 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L10 _namespace_ `namespace Tool` (scope `UE::PCG::EditorMode`)
- L12 _prototype_ `bool BuildTool(UInteractiveTool* InTool);` (scope `UE::PCG::EditorMode::Tool`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/PCGInteractiveToolCommon.h` (Private)


#### enum `EPCGToolDrawTargetOffset`  
`enum class EPCGToolDrawTargetOffset : uint8`  
_L10-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `HitLocation` — Drawn points will be at the hit location.
- L15 _public enumerator_ `DistanceOffset` — Drawn points will be at the hit location with a distance offset.
- L17 _public enumerator_ `ExplicitOffset` — Drawn points will be at the hit location with a custom vector offset.

#### enum `EPCGToolDrawTargetNormal`  
`enum class EPCGToolDrawTargetNormal : uint8`  
_L21-31_
- reflection: `UENUM()`
- L24 _public enumerator_ `HitNormal` — Drawn points will adopt the impact normal.
- L26 _public enumerator_ `WorldUp` — Drawn points will adopt the world up normal.
- L28 _public enumerator_ `AlignToPrevious` — Align to the previous spline point's up vector.
- L30 _public enumerator_ `Explicit` — Drawn points will adopt an explicit normal.

#### struct `FPCGToolRaycastSettings`  
`struct FPCGToolRaycastSettings`  
_L34-57_
- reflection: `USTRUCT()`
- L40 _public member_ `EPCGToolDrawTargetOffset OffsetMode = EPCGToolDrawTargetOffset::HitLocation;` — `UPROPERTY(EditAnywhere, Category = "Draw Target")` — How to choose the direction to offset points from the drawn surface.
- L44 _public member_ `double OffsetDistance = 100.0;` — `UPROPERTY(EditAnywhere, Category = "Draw Target", DisplayName = "Offset", meta = (UIMin = 0, UIMax = 100, EditCondition = "OffsetMode == EPCGToolDrawTargetOffset::DistanceOffset", EditConditionHides))` — How far to offset drawn points from the clicked surface, along the normal.
- L48 _public member_ `FVector OffsetVector = FVector(0, 0, 100);` — `UPROPERTY(EditAnywhere, Category = "Draw Target", DisplayName = "Offset", meta = (UIMin = 0, UIMax = 100, EditCondition = "OffsetMode == EPCGToolDrawTargetOffset::ExplicitOffset", EditConditionHides))` — Manual vector to offset drawn points from the clicked surface.
- L52 _public member_ `EPCGToolDrawTargetNormal NormalMode = EPCGToolDrawTargetNormal::HitNormal;` — `UPROPERTY(EditAnywhere, Category = "Draw Target")` — How to choose the direction to offset points from the drawn surface.
- L56 _public member_ `FVector Normal = FVector::ZAxisVector;` — `UPROPERTY(EditAnywhere, Category = "Draw Target", meta = (UIMin = 0, UIMax = 100, EditCondition = "NormalMode == EPCGToolDrawTargetNormal::Explicit", EditConditionHides))` — Manual vector to offset drawn points from the clicked surface.

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/PCGInteractiveToolSettings.h` (Private)


#### class `UPCGInteractiveToolBaseSettings`  
`class UPCGInteractiveToolBaseSettings : public UInteractiveToolPropertySet`  
_L30-43_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveToolPropertySet`
- desc: Base class for interactive tool settings in PCG. It is useful to derive from this class instead of UPCGInteractiveToolSettings when the tool does not require to create an actor, use a graph or a PCG component.
- L35 _public prototype_ `virtual TValueOrError<bool, FText> Initialize(UInteractiveTool* InTool);`
- L36 _public function_ `virtual void Apply(UInteractiveTool* OwningTool)`
- L37 _public function_ `virtual void Cancel(UInteractiveTool* OwningTool)`
- L38 _public function_ `virtual void Shutdown()`
- L39 _public function_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const`
- L42 _public prototype_ `virtual FName GetToolTag() const PURE_VIRTUAL(UPCGInteractiveToolBaseSettings::GetToolTag, return NAME_None;);` — Tool tag for use with filtering compatible graphs.

#### class `UPCGInteractiveToolSettings`  
`class UPCGInteractiveToolSettings : public UPCGInteractiveToolBaseSettings, public FTickableEditorObject, public IKeyInputBehaviorTarget`  
_L49-307_
- reflection: `UCLASS(Abstract)`
- inherits: `UPCGInteractiveToolBaseSettings,FTickableEditorObject,IKeyInputBehaviorTarget`
- desc: Base class for tools that need to manage creating an actor, a pcg component and graph tool settings in PCG.
- L54 _public prototype_ `UPCGInteractiveToolSettings();`
- L55 _public prototype_ `virtual ~UPCGInteractiveToolSettings() override = default;`
- L57 _public prototype_ `virtual TValueOrError<bool, FText> Initialize(UInteractiveTool* InTool) override;`
- L58 _public prototype_ `virtual void Apply(UInteractiveTool* OwningTool) override;`
- L59 _public prototype_ `virtual void Cancel(UInteractiveTool* OwningTool) override;`
- L60 _public prototype_ `virtual void Shutdown() override;`
- L61 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L64 _public prototype_ `virtual void RestoreProperties(UInteractiveTool* RestoreToTool, const FString& CacheIdentifier = TEXT("")) override;`
- L68 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;` — By default, when a tool is active, we can only select the Edit Actor in the Outliner.
- L71 _public prototype_ `virtual bool CanResetToolData(FName DataInstanceIdentifier);` — Whether tool data can be reset. Controls visibility of the Reset button in the UI.
- L74 _public prototype_ `virtual void RegisterPropertyWatchers();` — Register property watchers and callbacks in here.
- L76 _public function_ `virtual bool CanHandleMultipleActorSelection() const`
- L83 _public prototype_ `bool InitializeWorkingData(FName DataInstanceIdentifier = NAME_None, bool bAllowRetryAfterInit = true);` — Initializes or finds the working data associated with the data instance identifier. If NAME_None, the ToolTag is used as identifier. If bAllowRetryAfterInit is true, if the data was properly initialized, it will retry (once) after. Otherwise, it will not. @returns Whether new working data was created and initialized. False does not imply working data is invalid; just that it didn't get created.
- L85 _public function_ `UPCGGraphInterface* GetToolGraph() const`
- L86 _public prototype_ `void SetToolGraph(UPCGGraphInterface* InGraph);`
- L88 _public prototype_ `void SetDataInstance(FName DataInstanceIdentifier);`
- L91 _public prototype_ `virtual FSoftObjectPath GetDefaultGraph() const;` — A soft object path to the graph asset to load by default for this tool.
- L94 _public prototype_ `virtual const UScriptStruct* GetWorkingDataType() const PURE_VIRTUAL(UPCGInteractiveToolSettings::GetWorkingDataType, return FPCGInteractiveToolWorkingData::StaticStruct(););` — The working data type for this settings class.
- L98 _public prototype_ `virtual TSubclassOf<AActor> GetWorkingActorClass() const;` — The actor to instantiate for edit-purposes when we aren't editing an existing actor. If your target actor has any special requirements, create an actor for that purpose and return it in your settings.
- L101 _public prototype_ `bool UsesExistingActor() const;` — Whether we are operating on a spawned or a previously-existing actor.
- L103 _public prototype_ `void SetActorClassToSpawn(TSubclassOf<AActor> Class);`
- L105 _public prototype_ `void SetActorLabel(FName InLabel);`
- L107 _public function_ `bool IsWorkingActorCompatible(const AActor* InActor) const`
- L108 _public function_ `bool IsActorClassCompatible(TSubclassOf<AActor> InClass) const`
- L112 _public prototype_ `virtual bool GraphAssetFilter(const FAssetData& AssetData) const;` — `UFUNCTION()` — Filter details view graph selection.
- L116 _public prototype_ `bool HasSpawnedActor() const;` — `UFUNCTION()` — Returns true if the actor being edited has been spawned by this tool.
- L120 _public prototype_ `bool HasGeneratedPCGComponent() const;` — `UFUNCTION()` — Returns true if the pcg component being edited has been spawned by this tool.
- L122 _public prototype_ `UPCGComponent* GetWorkingPCGComponent() const;`
- L123 _public prototype_ `UPCGGraphInstance* GetGraphInstance() const;`
- L126 _public prototype_ `TArray<FName> GetDataInstanceNamesForGraph() const;` — `UFUNCTION()`
- L129 _public prototype_ `TArray<FName> GetValidDataInstanceNamesForGraph() const;` — `UFUNCTION()`
- L130 _public prototype_ `FName GetDefaultDataInstanceName() const;`
- L133 _public function_ `template<typename T = AActor> T* GetTypedWorkingActor() const`
- L140 _public prototype_ `FName GetWorkingDataIdentifier(FName DataInstanceIdentifier = NAME_None) const;`
- L143 _public function_ `template<typename T = FPCGInteractiveToolWorkingData> T* GetMutableTypedWorkingData(FName DataInstanceIdentifier = NAME_None)`
- L158 _public function_ `template<typename T = FPCGInteractiveToolWorkingData> const T* GetTypedWorkingData(FName DataInstanceIdentifier = NAME_None) const`
- L173 _public function_ `template<typename T = FPCGInteractiveToolWorkingData> TMap<FName, T*> GetMutableTypedWorkingDataMap() const`
- L196 _public function_ `template<typename T = FPCGInteractiveToolWorkingData> TMap<FName, const T*> GetTypedWorkingDataMap() const`
- L220 _protected function_ `virtual bool IsWorkingActorCompatibleInternal(const AActor* InActor) const` — Tools can have a requirement on the working actor
- L221 _protected function_ `virtual bool IsActorClassCompatibleInternal(TSubclassOf<AActor> InClass) const`
- L222 _protected function_ `virtual TOptional<TSubclassOf<AActor>> GetFallbackActorClassToSpawn() const`
- L225 _protected prototype_ `virtual TValueOrError<bool, FText> TryLoadDefaults();` — Try to load the defaults (graph, actor class, ...) into the tool settings (ToolGraph, etc.).
- L226 _protected prototype_ `virtual TValueOrError<bool, FText> InitActorAndComponent();`
- L227 _protected prototype_ `virtual bool InitializeWorkingDataForGraph();`
- L229 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L230 _protected prototype_ `virtual bool IsTickable() const override;`
- L231 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L233 _protected prototype_ `void CommitPropertyChangedEvents();`
- L236 _protected prototype_ `virtual void OnKeyPressed(const FKey& KeyID) override;` — IKeyInputBehaviorTarget
- L239 _protected prototype_ `virtual void PostWorkingDataInitialized(FPCGInteractiveToolWorkingData* WorkingData) const;` — Allows to modify the just initialized working data from the editor. This can be used if the initialization of working data requires editor data access.
- L240 _protected prototype_ `virtual void OnPropertyModified(UObject* Object, FProperty* Property);`
- L241 _protected prototype_ `virtual void OnRefreshInternal();`
- L244 _private prototype_ `UPCGComponent* FindOrGeneratePCGComponent(AActor& OwningActor) const;`
- L246 _private prototype_ `void DeleteGeneratedResources() const;`
- L248 _private prototype_ `void OnRefresh();`
- L250 _private prototype_ `void CacheGraphInstance(UPCGGraphInstance* InGraphInstance);`
- L251 _private prototype_ `void RestoreGraphInstanceInitialState(UPCGGraphInstance* OutGraphInstance);`
- L252 _private prototype_ `TSubclassOf<AActor> GetCompatibleActorClassFromGraphOrFallback() const;`
- L256 _public member_ `TObjectPtr<UPCGGraphInterface> ToolGraph = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PCG", meta = (TransientToolProperty, NoResetToDefault, GetAssetFilter = "GraphAssetFilter"))` — Marked transient because the tool system will either fill this with a default or take the graph from the selected actor.
- L259 _public member_ `FName DataInstance = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PCG", meta = (NoResetToDefault, EditCondition="ToolGraph != nullptr", EditConditionHides, GetOptions="GetValidDataInstanceNamesForGraph"))`
- L264 _public member_ `TWeakObjectPtr<AActor> EditActor = nullptr;` — `UPROPERTY(meta = (TransientToolProperty))` — The actor to modify with the tool. Either a selected actor, or a newly spawned one.
- L268 _public member_ `FName NewActorName;` — `UPROPERTY(EditAnywhere, DisplayName="Actor Label", Category = "PCG", meta = (TransientToolProperty, EditCondition="HasSpawnedActor()", EditConditionHides))` — The name to be issued to a newly created actor when the tool is applied.
- L272 _public member_ `FName NewPCGComponentName;` — `UPROPERTY(EditAnywhere, DisplayName="Component Name", Category = "PCG", meta = (TransientToolProperty, EditCondition="HasGeneratedPCGComponent()", EditConditionHides))` — The name to be issued to a newly created PCG component when the tool is applied.
- L276 _public member_ `TSubclassOf<AActor> ActorClassToSpawn;` — `UPROPERTY(EditAnywhere, Category = "PCG", meta=(TransientToolProperty, EditCondition="HasSpawnedActor()", EditConditionHides, NoResetToDefault))` — The actor class to use when the tool works on a spawned actor opposed to a pre-existing one.
- L280 _public member_ `float GraphRefreshTimer = 0.f;` — `UPROPERTY(meta = (TransientToolProperty))` — The current time left before a graph refresh (in seconds).
- L283 _public member_ `mutable TWeakObjectPtr<UPCGComponent> WorkingComponentCache;` — `UPROPERTY(meta = (TransientToolProperty))`
- L285 _public member_ `TMap<TWeakObjectPtr<UObject>, FPropertyChangedEvent> PropertyChangedEventQueue;`
- L295 _public member_ `mutable FGeneratedResources GeneratedResources;`
- L297 _public member_ `bool bTryToGenerate = false;`
- L301 _private member_ `TObjectPtr<UPCGGraphInstance> GraphInstanceCache;` — `UPROPERTY(Transient, meta = (TransientToolProperty))`
- L304 _private member_ `TSet<FName> WorkingDataToolStartSet;` — `UPROPERTY(Transient, meta = (TransientToolProperty))`
- L306 _private member_ `TWeakObjectPtr<UInteractiveTool> Tool = nullptr;`

#### struct `UPCGInteractiveToolSettings::FGeneratedResources`  
`struct FGeneratedResources`  
_L287-293_
- L289 _public member_ `TWeakObjectPtr<AActor> SpawnedActor;`
- L290 _public member_ `TWeakObjectPtr<UPCGComponent> GeneratedPCGComponent;`
- L292 _public member_ `TArray<FName> AddedWorkingDataIdentifiers;` — A list of working data identifiers added this tool instantiation. Used to delete data on Cancel.

#### class `UPCGInteractiveTool`  
`class UPCGInteractiveTool : public UInteractiveTool`  
_L310-317_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveTool`
- L315 _public function_ `virtual bool RequiresSettings() const`
- L316 _public function_ `virtual bool UsesTransformGizmo() const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PCG` (scope `UE`)
- L17 _namespace_ `namespace EditorMode` (scope `UE::PCG`)
- L17 _namespace_ `namespace Tool` (scope `UE::PCG::EditorMode`)
- L19 _prototype_ `void Shutdown(UInteractiveTool* InTool, EToolShutdownType ShutdownType);` (scope `UE::PCG::EditorMode::Tool`)
- L21 _externvar_ `extern TAutoConsoleVariable<bool> CVarCommitPropertyChangedEventOnTimer;` (scope `UE::PCG::EditorMode::Tool`)

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Paint/PCGEdModeBrushBase.h` (Private)


#### class `UPCGEdModeBrushBase`  
`class UPCGEdModeBrushBase : public UBrushBaseProperties`  
_L10-16_
- reflection: `UCLASS()`
- inherits: `UBrushBaseProperties`
- L15 _public prototype_ `UPCGEdModeBrushBase() = default;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Paint/PCGPaintTool.h` (Private)


#### class `UPCGInteractiveToolSettings_PaintTool`  
`class UPCGInteractiveToolSettings_PaintTool : public UPCGInteractiveToolSettings`  
_L16-58_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveToolSettings`
- L21 _public prototype_ `UPCGInteractiveToolSettings_PaintTool();`
- L23 _public prototype_ `static FName StaticGetToolTag();`
- L26 _public prototype_ `virtual FName GetToolTag() const override;`
- L27 _public prototype_ `virtual const UScriptStruct* GetWorkingDataType() const override;`
- L28 _public prototype_ `virtual void RegisterPropertyWatchers() override;`
- L33 _public member_ `EPCGBrushMode BrushMode = EPCGBrushMode::Sphere;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paint")` — The brush shape to use.
- L37 _public member_ `bool bErasePointsOfSelectedDataInstance = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paint")` — If false, will erase points on all paint data instances.
- L41 _public member_ `float RotateYawStepSize = 10.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paint")` — The step size for rotation of the brush. Moving the mouse wheel up or down will add or subtract from the brush rotation.
- L45 _public member_ `double MinPointSpacing = 50.0;` — `UPROPERTY(EditAnywhere, Category = "Paint", meta = (ClampMin = 0, UIMax = 1000))` — The minimum amount of distance to pass before drawing another point while dragging the mouse.
- L48 _public member_ `FPCGRaycastFilterRuleCollection RaycastRuleCollection;` — `UPROPERTY(EditAnywhere, Category= "Raycast")`
- L51 _public member_ `double CachedMinPointSpacingSquared = 0;` — Helper property so we can avoid sqrt.
- L54 _public member_ `TOptional<FTransform> LastPointTransform;` — Tracks the last point that was added. Used for min-spacing during drag.
- L57 _protected prototype_ `virtual bool IsWorkingActorCompatibleInternal(const AActor* InActor) const override final;`

#### class `UPCGPaintTool`  
`class UPCGPaintTool : public UBaseBrushTool, public IMouseWheelBehaviorTarget`  
_L61-112_
- reflection: `UCLASS(Transient)`
- inherits: `UBaseBrushTool,IMouseWheelBehaviorTarget`
- L67 _public prototype_ `virtual void Setup() override;`
- L68 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L69 _public prototype_ `virtual bool HasAccept() const override;`
- L70 _public prototype_ `virtual bool CanAccept() const override;`
- L71 _public prototype_ `virtual bool HasCancel() const override;`
- L72 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L75 _public prototype_ `virtual bool HitTest(const FRay& Ray, FHitResult& OutHit) override;`
- L78 _protected prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L79 _protected prototype_ `virtual void OnUpdateDrag(const FRay& Ray) override;`
- L82 _protected prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos) override;` — IMouseWheelBehaviorTarget
- L83 _protected prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos) override;`
- L84 _protected prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos) override;`
- L86 _protected prototype_ `virtual void SetupBrushStampIndicator() override;`
- L87 _protected prototype_ `virtual void UpdateBrushStampIndicator() override;`
- L88 _protected prototype_ `virtual void ShutdownBrushStampIndicator() override;`
- L90 _protected prototype_ `void RestartBrushStampIndicator();`
- L93 _protected prototype_ `virtual double EstimateMaximumTargetDimension() override;` — This will be used as the brush base, if not specifying a radius directly
- L96 _private prototype_ `void AddSinglePointFromBrush();`
- L97 _private prototype_ `void TryDeletePointsFromBrush();`
- L99 _private prototype_ `void NotifyDataChanged(UPCGData* InData);`
- L103 _private member_ `TObjectPtr<UPCGInteractiveToolSettings_PaintTool> ToolSettings;` — `UPROPERTY(Transient)`
- L106 _private member_ `TObjectPtr<UMouseWheelInputBehavior> MouseWheelInputBehavior;` — `UPROPERTY(Transient)`
- L109 _private member_ `bool bShiftPressedLastTick = false;` — `UPROPERTY(Transient)`
- L111 _private member_ `UE::PCG::EditorMode::Scene::FViewRayParams CachedRayParams{};`

#### class `UPCGPaintToolBuilder`  
`class UPCGPaintToolBuilder : public UPCGInteractiveToolBuilder`  
_L115-122_
- reflection: `UCLASS(Transient)`
- inherits: `UPCGInteractiveToolBuilder`
- L120 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L121 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Query/PCGQueryTool.h` (Private)


#### class `UPCGBaseQueryTool`  
`class UPCGBaseQueryTool : public UPCGInteractiveTool, public IClickBehaviorTarget`  
_L25-54_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveTool,IClickBehaviorTarget`
- desc: Simple editor tool to gather information from a picked object in the world. By default logs visited hierarchy tags (from touched component, to actor, ...) but can be reimplemented in a derived class.
- L31 _public prototype_ `virtual void Setup() override;`
- L32 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L36 _public function_ `virtual bool RequiresSettings() const override`
- L40 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPosition) override;`
- L41 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPosition) override;`
- L45 _protected prototype_ `HHitProxy* GetHitProxy(const FInputDeviceRay& ClickPosition) const;`
- L46 _protected prototype_ `UActorComponent* GetHitComponent(HHitProxy* HitProxy) const;`
- L47 _protected prototype_ `UActorComponent* GetHitComponent(const FInputDeviceRay& ClickPosition) const;`
- L48 _protected function_ `virtual void OnHitProxy(HHitProxy* HitProxy, UActorComponent* HitComponent, int InstanceIndex)`
- L49 _protected prototype_ `void VisitHierarchy(UActorComponent* HitComponent, int32 InstanceIndex, TFunctionRef<void(UActorComponent*, AActor*, int32)> Func);`
- L53 _private member_ `TObjectPtr<USingleClickInputBehavior> ClickBehavior = nullptr;` — `UPROPERTY(Instanced)`

#### class `UPCGQueryTool`  
`class UPCGQueryTool : public UPCGBaseQueryTool`  
_L60-85_
- reflection: `UCLASS()`
- inherits: `UPCGBaseQueryTool`
- desc: Simple editor tool to gather information from a picked object in the world. By default logs visited hierarchy tags (from touched component, to actor, ...) but can be reimplemented in a derived class.
- L66 _public function_ `virtual bool HasCancel() const override`
- L67 _public function_ `virtual bool HasAccept() const override`
- L68 _public function_ `virtual bool CanAccept() const override`
- L72 _public function_ `virtual bool RequiresSettings() const override`
- L75 _public prototype_ `static FName StaticGetToolTag();`
- L78 _public member_ `TArray<FString> SelectedTags;` — `UPROPERTY()`
- L81 _public member_ `FString FoundActorLabel;` — `UPROPERTY()`
- L84 _protected prototype_ `virtual void OnHitProxy(HHitProxy* HitProxy, UActorComponent* HitComponent, int InstanceIndex);`

#### class `UPCGQueryToolBuilder`  
`class UPCGQueryToolBuilder : public UPCGInteractiveToolBuilder`  
_L90-103_
- reflection: `UCLASS(Transient)`
- inherits: `UPCGInteractiveToolBuilder`
- L95 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L96 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L98 _public prototype_ `void SetToolClass(TSubclassOf<UPCGBaseQueryTool> InClass);`
- L102 _private member_ `TSubclassOf<UPCGBaseQueryTool> ToolClass = nullptr;` — `UPROPERTY()`

#### class `UPCGInteractiveToolSettings_Isolate`  
`class UPCGInteractiveToolSettings_Isolate : public UPCGInteractiveToolBaseSettings`  
_L106-139_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveToolBaseSettings`
- L111 _public prototype_ `virtual void Apply(UInteractiveTool* OwningTool) override;`
- L112 _public prototype_ `virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;`
- L113 _public prototype_ `virtual FName GetToolTag() const override;`
- L117 _public member_ `TWeakObjectPtr<AActor> SelectedActor;` — `UPROPERTY(VisibleAnywhere, Category = PCG)`
- L120 _public member_ `TSet<FName> Tags;` — `UPROPERTY(VisibleAnywhere, Category = PCG)`
- L123 _public member_ `int32 InstanceIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = PCG)`
- L126 _public member_ `TArray<FName> SelectedTags;` — `UPROPERTY(EditAnywhere, Category = PCG)`
- L129 _public member_ `TArray<FName> ExcludedTags;` — `UPROPERTY(EditAnywhere, Category = PCG)`
- L132 _public member_ `bool bExtractToSelf = false;` — `UPROPERTY(EditAnywhere, Category = PCG)`
- L135 _public member_ `bool bAttachToActor = false;` — `UPROPERTY(EditAnywhere, Category = PCG, meta = (EditCondition = "!bExtractToSelf"))`
- L138 _public member_ `FName IsolatedActorLabel = NAME_None;` — `UPROPERTY(EditAnywhere, Category = PCG, meta = (EditCondition = "!bExtractToSelf"))`

#### class `UPCGIsolateTool`  
`class UPCGIsolateTool : public UPCGBaseQueryTool`  
_L146-173_
- reflection: `UCLASS()`
- inherits: `UPCGBaseQueryTool`
- desc: Tool that extracts the artifacts (through Clear PCG Link) from an actor with a PCG component according to selected tags. Tags are gathered through picking (from the Query tool), and listed so the user can choose a combination.
- L152 _public prototype_ `virtual void Setup() override;`
- L153 _public function_ `virtual bool HasCancel() const override`
- L154 _public function_ `virtual bool HasAccept() const override`
- L155 _public prototype_ `virtual bool CanAccept() const override;`
- L159 _public function_ `virtual bool RequiresSettings() const override`
- L162 _public prototype_ `static FName StaticGetToolTag();`
- L166 _protected prototype_ `virtual void OnHitProxy(HHitProxy* HitProxy, UActorComponent* HitComponent, int InstanceIndex) override;`
- L169 _protected prototype_ `UPCGInteractiveToolSettings_Isolate* GetSettings() const;`
- L172 _protected member_ `TObjectPtr<UPCGInteractiveToolSettings_Isolate> ToolSettings;` — `UPROPERTY(Transient)`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Tools/Volume/PCGVolumeTool.h` (Private)


#### class `UPCGInteractiveToolSettings_Volume`  
`class UPCGInteractiveToolSettings_Volume : public UPCGInteractiveToolSettings`  
_L18-51_
- reflection: `UCLASS()`
- inherits: `UPCGInteractiveToolSettings`
- L23 _public prototype_ `UPCGInteractiveToolSettings_Volume();`
- L25 _public prototype_ `static FName StaticGetToolTag();`
- L28 _public prototype_ `virtual FName GetToolTag() const override;`
- L29 _public prototype_ `virtual const UScriptStruct* GetWorkingDataType() const override;`
- L30 _public function_ `virtual bool CanResetToolData(FName DataInstanceIdentifier) override`
- L33 _public prototype_ `AVolume* GetWorkingVolume(FName DataInstanceIdentifier) const;`
- L34 _public prototype_ `UBoxComponent* GetWorkingBoxComponent(FName DataInstanceIdentifier) const;`
- L39 _public member_ `FPCGRaycastFilterRuleCollection RaycastRuleCollection;` — `UPROPERTY(EditAnywhere, Category = Raycast)`
- L43 _public member_ `bool bHitGroundPlanes = true;` — `UPROPERTY(EditAnywhere, Category = "Raycast")` — Whether to place the volume base on a plane through the origin aligned with the Z axis in perspective views.
- L48 _protected prototype_ `virtual bool IsWorkingActorCompatibleInternal(const AActor* InActor) const override final;` — This function is called by the builder using UPCGInteractiveToolSettings_Volume default class which prohibits to have override implementation of this function by child classes. Mark it final for that reason, to be revisited if we change the tool classes hierarchy.
- L49 _protected prototype_ `virtual bool IsActorClassCompatibleInternal(TSubclassOf<AActor> InClass) const override final;`
- L50 _protected prototype_ `virtual TOptional<TSubclassOf<AActor>> GetFallbackActorClassToSpawn() const override final;`

#### class `UPCGVolumeTool`  
`class UPCGVolumeTool : public UInteractiveTool, public IClickBehaviorTarget, public IClickDragBehaviorTarget, public IHoverBehaviorTarget`  
_L59-120_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UInteractiveTool,IClickBehaviorTarget,IClickDragBehaviorTarget,IHoverBehaviorTarget`
- desc: Tool class to create 3d volumes. Current implementation only creates cubes. Click + drag -> creates the base. Second click -> creates the height.
- L65 _public function_ `virtual bool HasCancel() const override`
- L66 _public function_ `virtual bool HasAccept() const override`
- L68 _public prototype_ `virtual void Setup() override;`
- L69 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L70 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L71 _public prototype_ `virtual bool CanAccept() const override;`
- L75 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPosition) override;`
- L76 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPosition) override;`
- L80 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& DragPosition) override;`
- L81 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& ClickPosition) override;`
- L82 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPosition) override;`
- L83 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePosition) override;`
- L84 _public function_ `virtual void OnTerminateDragSequence() override`
- L88 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L89 _public function_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override`
- L90 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L91 _public function_ `virtual void OnEndHover() override`
- L95 _private prototype_ `FBox GetCurrentBox() const;`
- L96 _private prototype_ `void UpdateVolumeFromBox();`
- L97 _private prototype_ `FVector GetBaseDragPosition(const FInputDeviceRay& DragPosition) const;`
- L99 _private member_ `UE::PCG::EditorMode::Scene::FViewRayParams CachedRayParams;`
- L102 _private member_ `TObjectPtr<USingleClickOrDragInputBehavior> ClickOrDragBehavior = nullptr;` — `UPROPERTY(Instanced)`
- L105 _private member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior = nullptr;` — `UPROPERTY(Instanced)`
- L108 _private member_ `TObjectPtr<UPCGInteractiveToolSettings_Volume> ToolSettings;` — `UPROPERTY(Transient)`
- L110 _private member_ `bool bIsDraggingBase = false;`
- L111 _private member_ `bool bIsDraggingHeight = false;`
- L112 _private member_ `bool bBaseSelectionDone = false;`
- L113 _private member_ `FVector FirstPoint = FVector::ZeroVector;`
- L114 _private member_ `FVector SecondPoint = FVector::ZeroVector;`
- L115 _private member_ `FVector InteractiveSecondPoint = FVector::ZeroVector;`
- L116 _private member_ `double DefaultHalfHeight = 0;`
- L118 _private member_ `FRay LastRay;`
- L119 _private member_ `FBox LastBox = FBox(EForceInit::ForceInit);`

#### class `UPCGVolumeToolBuilder`  
`class UPCGVolumeToolBuilder : public UPCGInteractiveToolWithToolTargetsBuilder`  
_L123-130_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UPCGInteractiveToolWithToolTargetsBuilder`
- L128 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L129 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Widgets/SPCGEdModeAcceptToolOverlay.h` (Private)


#### class `SPCGEdModeAcceptToolOverlay`  
`class SPCGEdModeAcceptToolOverlay : public SCompoundWidget`  
_L10-41_
- inherits: `SCompoundWidget`
- desc: A simple Accept/Cancel widget for the PCG Editor Mode Toolkit.
- L12 _private function_ `SLATE_BEGIN_ARGS(SPCGEdModeAcceptToolOverlay) : _ActiveToolDisplayName(FText::GetEmpty()) , _ActiveToolIcon(nullptr) , _IsAcceptButtonEnabled(false) , _IsCancelButtonEnabled(false) , _GetAcceptButtonVisibility(EVisibility::Collapsed) , _GetCancelButtonVisibility(EVisibility::Collapsed)`
- L20 _private prototype_ `SLATE_ATTRIBUTE(FText, ActiveToolDisplayName) SLATE_ATTRIBUTE(const FSlateBrush*, ActiveToolIcon) SLATE_ATTRIBUTE(FText, AcceptButtonLabel) SLATE_ATTRIBUTE(FText, CancelButtonLabel) SLATE_ATTRIBUTE(FText, AcceptButtonTooltip) SLATE_ATTRIBUTE(FText, CancelButtonTooltip) SLATE_ATTRIBUTE(bool, IsAcceptButtonEnabled) SLATE_ATTRIBUTE(bool, IsCancelButtonEnabled) SLATE_ATTRIBUTE(EVisibility, GetAcceptButtonVisibility) SLATE_ATTRIBUTE(EVisibility, GetCancelButtonVisibility) SLATE_EVENT(FOnClicked, OnAcceptButtonClicked) SLATE_EVENT(FOnClicked, OnCancelButtonClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private member_ `FArguments Args;`

### `Plugins/PCG/Source/PCGEditor/Private/EditorMode/Widgets/SPCGToolPresetSection.h` (Private)


#### class `UPCGToolPresetMenuContext`  
`class UPCGToolPresetMenuContext : public UObject`  
_L18-24_
- reflection: `UCLASS()`
- inherits: `UObject`
- L23 _public member_ `TWeakPtr<class SPCGToolPresetSection> ThisSection;`

#### class `SPCGToolPresetSection`  
`class SPCGToolPresetSection : public SCompoundWidget`  
_L26-70_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SPCGToolPresetSection)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdMode& InOwningEditorMode);`
- L36 _public prototype_ `void UpdatePresets();`
- L38 _public function_ `void HidePresets(bool bInHide)`
- L40 _public prototype_ `bool HasPresets() const;`
- L49 _public typedef_ `using FPresetItemPtr = TSharedPtr<FPresetItem, ESPMode::ThreadSafe>;`
- L51 _public function_ `const TArray<FPresetItemPtr>& GetPresets() const`
- L54 _private prototype_ `TSharedPtr<SWidget> MakePresetToolbar() const;`
- L55 _private prototype_ `static void OnGeneratePresetMenu(UToolMenu* ToolMenu);`
- L57 _private prototype_ `static bool CanActivatePreset(TWeakPtr<FPresetItem> PresetItem, const UPCGToolPresetMenuContext* Context);`
- L58 _private prototype_ `static void ActivatePreset(TWeakPtr<FPresetItem> PresetItem, const UPCGToolPresetMenuContext* Context);`
- L59 _private prototype_ `static FText GetPresetTooltip(TWeakPtr<FPresetItem> PresetItem, const UPCGToolPresetMenuContext* Context);`
- L60 _private prototype_ `static ECheckBoxState IsPresetActive(TWeakPtr<FPresetItem> PresetItem, const UPCGToolPresetMenuContext* Context);`
- L62 _private prototype_ `EVisibility OnGetVisibility() const;`
- L64 _private member_ `TStrongObjectPtr<UPCGToolPresetMenuContext> ThisContext;`
- L66 _private member_ `TWeakObjectPtr<UEdMode> OwningEditorMode;`
- L67 _private member_ `TArray<FPresetItemPtr> Presets;`
- L69 _private member_ `bool bHidePresets = false;`

#### struct `SPCGToolPresetSection::FPresetItem`  
`struct FPresetItem`  
_L42-47_
- L44 _public member_ `TSoftObjectPtr<UPCGGraphInterface> Item;`
- L45 _public member_ `FText Name;`
- L46 _public member_ `FText Tooltip;`

### `Plugins/PCG/Source/PCGEditor/Private/Factories/PCGBuilderSettingsFactory.h` (Private)


#### class `UPCGBuilderSettingsFactory`  
`class UPCGBuilderSettingsFactory : public UFactory`  
_L10-20_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L15 _public prototype_ `UPCGBuilderSettingsFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/Factories/PCGComputeSourceFactory.h` (Private)


#### class `UPCGComputeSourceFactory`  
`class UPCGComputeSourceFactory : public UFactory`  
_L10-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UPCGComputeSourceFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _public function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeComment.h` (Private)


#### class `UPCGEditorGraphNodeComment`  
`class UPCGEditorGraphNodeComment : public UEdGraphNode_Comment`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode_Comment`
- L19 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L22 _public prototype_ `void InitializeFromNodeData(const FPCGGraphCommentNodeData& NodeData);`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeFactory.h` (Private)


#### class `FPCGEditorGraphNodeFactory`  
`class FPCGEditorGraphNodeFactory : public FGraphPanelNodeFactory`  
_L10-13_
- inherits: `FGraphPanelNodeFactory`
- L12 _private prototype_ `virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* InNode) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeGetUserParameter.h` (Private)


#### class `UPCGEditorGraphGetUserParameter`  
`class UPCGEditorGraphGetUserParameter : public UPCGEditorGraphNode`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNode`
- L18 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L19 _public prototype_ `virtual bool OnValidateNodeTitle(const FText& NewName, FText& OutErrorMessage) override;`
- L20 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeInput.h` (Private)


#### class `UPCGEditorGraphNodeInput`  
`class UPCGEditorGraphNodeInput : public UPCGEditorGraphNode`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNode`
- L17 _public function_ `UPCGEditorGraphNodeInput(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _public function_ `virtual bool CanUserDeleteNode() const override`
- L27 _public function_ `virtual bool CanDuplicateNode() const override`
- L28 _public prototype_ `virtual void ReconstructNode() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeOutput.h` (Private)


#### class `UPCGEditorGraphNodeOutput`  
`class UPCGEditorGraphNodeOutput : public UPCGEditorGraphNode`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNode`
- L17 _public function_ `UPCGEditorGraphNodeOutput(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)`
- L24 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L25 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L26 _public function_ `virtual bool CanUserDeleteNode() const override`
- L27 _public function_ `virtual bool CanDuplicateNode() const override`
- L28 _public prototype_ `virtual void ReconstructNode() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/PCGEditorGraphNodeReroute.h` (Private)


#### class `UPCGEditorGraphNodeReroute`  
`class UPCGEditorGraphNodeReroute : public UPCGEditorGraphNode`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNode`
- L17 _public prototype_ `UPCGEditorGraphNodeReroute(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L21 _public prototype_ `virtual bool ShouldOverridePinNames() const override;`
- L22 _public prototype_ `virtual FText GetPinNameOverride(const UEdGraphPin& Pin) const override;`
- L23 _public prototype_ `virtual bool CanSplitPin(const UEdGraphPin* Pin) const override;`
- L24 _public prototype_ `virtual bool ShouldDrawNodeAsControlPointOnly(int32& OutInputPinIndex, int32& OutOutputPinIndex) const override;`
- L25 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual UEdGraphPin* GetPassThroughPin(const UEdGraphPin* FromPin) const override;`
- L27 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L30 _public prototype_ `UEdGraphPin* GetInputPin() const;`
- L31 _public prototype_ `UEdGraphPin* GetOutputPin() const;`

#### class `UPCGEditorGraphNodeNamedRerouteBase`  
`class UPCGEditorGraphNodeNamedRerouteBase : public UPCGEditorGraphNode`  
_L35-48_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNode`
- L41 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L42 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L46 _public prototype_ `virtual bool OnValidateNodeTitle(const FText& NewName, FText& OutErrorMessage) override;`

#### class `UPCGEditorGraphNodeNamedRerouteUsage`  
`class UPCGEditorGraphNodeNamedRerouteUsage : public UPCGEditorGraphNodeNamedRerouteBase`  
_L51-67_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNodeNamedRerouteBase`
- L57 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L59 _public prototype_ `void InheritRename(const FString& NewName);`
- L62 _protected prototype_ `virtual void RebuildEdgesFromPins_Internal() override;`
- L63 _protected function_ `virtual bool CanPickColor() const override`
- L64 _protected prototype_ `virtual FText GetPinFriendlyName(const UPCGPin* InPin) const override;`
- L66 _protected prototype_ `void ApplyToDeclarationNode(TFunctionRef<void(UPCGEditorGraphNodeNamedRerouteDeclaration*)> Action) const;`

#### class `UPCGEditorGraphNodeNamedRerouteDeclaration`  
`class UPCGEditorGraphNodeNamedRerouteDeclaration : public UPCGEditorGraphNodeNamedRerouteBase`  
_L70-92_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNodeNamedRerouteBase`
- L76 _public prototype_ `virtual void PostPaste() override;`
- L80 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L83 _public prototype_ `FString GenerateNodeName(const UPCGNode* FromNode, FName FromPinName);`
- L84 _public prototype_ `void FixNodeNameCollision();`
- L87 _protected prototype_ `virtual FText GetPinFriendlyName(const UPCGPin* InPin) const override;`
- L88 _protected prototype_ `virtual void OnColorPicked(FLinearColor NewColor) override;`
- L89 _protected prototype_ `virtual void ReconstructNodeOnChange() override;`
- L91 _protected prototype_ `void ApplyToUsageNodes(TFunctionRef<void(UPCGEditorGraphNodeNamedRerouteUsage*)> Action);`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/SPCGEditorGraphNode.h` (Private)


#### class `SPCGEditorGraphNode`  
`class SPCGEditorGraphNode : public SGraphNode`  
_L14-97_
- inherits: `SGraphNode`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphNode)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UPCGEditorGraphNodeBase* InNode);`
- L23 _public prototype_ `virtual void UpdateGraphNode() override;`
- L24 _public prototype_ `virtual const FSlateBrush* GetNodeBodyBrush() const override;`
- L25 _public function_ `virtual void RequestRenameOnSpawn() override`
- L26 _public prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> InNodeTitle) override;`
- L28 _public prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L29 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L30 _public prototype_ `virtual EVisibility IsAddPinButtonVisible() const override;`
- L31 _public prototype_ `virtual FReply OnAddPin() override;`
- L32 _public prototype_ `virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;`
- L36 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L37 _public prototype_ `virtual void GetOverlayBrushes(bool bSelected, const FVector2f& WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;`
- L41 _protected prototype_ `void OnNodeChanged();`
- L44 _protected prototype_ `virtual bool UsesHiGenOverlay() const;` — Will add the Hierarchical Generation overlay to the node.
- L46 _protected prototype_ `virtual bool UsesGPUOverlay() const;` — Will add the GPU icon overlay to the node.
- L48 _protected prototype_ `virtual bool UsesInspectBrush() const;` — Will add the inspect brush to the node.
- L50 _protected prototype_ `virtual bool UsesDebugBrush() const;` — Will add the debug brush to the node.
- L52 _protected prototype_ `void CreateDynamicPinButton(EPCGPinDirection Direction);`
- L53 _protected prototype_ `FReply OnAddDynamicPin(EPCGPinDirection Direction);`
- L54 _protected prototype_ `EVisibility IsDynamicPinButtonVisible(EPCGPinDirection Direction) const;`
- L55 _protected prototype_ `void OnRequestPinRename(UEdGraphPin* InPin);`
- L58 _private prototype_ `FLinearColor GetGridLabelColor(uint32 NodeGrid) const;`
- L61 _private prototype_ `void AddHiGenOverlayWidget(TArray<FOverlayWidgetInfo>& OverlayWidgets) const;` — Adds the Hierarchical Generation overlay to the array, displaying the HiGen grid size on the node.
- L64 _private prototype_ `void AddGPUOverlayWidget(TArray<FOverlayWidgetInfo>& OverlayWidgets) const;` — Adds the "GPU" tag to the node to indicate the node will execute on the GPU.
- L67 _private prototype_ `void AddGPUUploadWidget(TArray<FOverlayWidgetInfo>& OverlayWidgets) const;` — Indicates an upload of data to the GPU occurred as a result of this node.
- L70 _private prototype_ `void AddGPUReadbackWidget(TArray<FOverlayWidgetInfo>& OverlayWidgets) const;` — Indicates a readback of data from the GPU occurred as a result of this node.
- L76 _private prototype_ `const FSlateBrush* GetBorderBrush(uint32 InspectedGrid, uint32 NodeGrid) const;` — Get the border brush for the given combination of grid sizes and enabled state. All a big workaround for FSlateRoundedBoxBrush not respecting the tint colour.
- L81 _private prototype_ `TSharedRef<SWidget> CreateNodeToolButtonWidget();` — Creates the interact button widget displayed in the node's title area, providing access to node-specific interaction actions.
- L84 _private prototype_ `TSharedRef<SWidget> CreateDataOverrideButton() const;` — Creates the pencil button that opens the Data Overrides panel and inspects this node.
- L87 _private prototype_ `TSharedRef<SWidget> CreateManualEditButton() const;` — Creates the wrench button that selects the parent actor and focuses the level viewport.
- L89 _private member_ `UPCGEditorGraphNodeBase* PCGEditorGraphNode = nullptr;`
- L95 _private member_ `TSharedPtr<SWidget> GPUUploadIndicatorWidget;` — Stable widget instances for GPU transfer indicators. Must be the same pointer across GetOverlayWidgets() calls (Paint vs OnArrangeChildren) so that Slate can track hover state and show tooltips.
- L96 _private member_ `TSharedPtr<SWidget> GPUReadbackIndicatorWidget;`

### `Plugins/PCG/Source/PCGEditor/Private/Nodes/SPCGEditorGraphNodeCompact.h` (Private)


#### class `SPCGEditorGraphNodeCompact`  
`class SPCGEditorGraphNodeCompact : public SPCGEditorGraphNode`  
_L9-29_
- inherits: `SPCGEditorGraphNode`
- L12 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphNodeCompact)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UPCGEditorGraphNodeBase* InNode);`
- L18 _public prototype_ `virtual void UpdateGraphNode() override;`
- L19 _public prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> InNodeTitle) override;`
- L20 _public prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L21 _public prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L25 _private prototype_ `FSlateColor GetSubduedSpillColor() const;`
- L27 _private member_ `UPCGEditorGraphNode* PCGEditorGraphNode = nullptr;`
- L28 _private member_ `TSharedPtr<SNodeTitle> NodeTitle = nullptr;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorDefaultMode.h` (Private)


#### class `FPCGEditorDefaultMode`  
`class FPCGEditorDefaultMode : public FApplicationMode`  
_L18-33_
- inherits: `FApplicationMode`
- L21 _public prototype_ `static FName StaticName();`
- L23 _public prototype_ `FPCGEditorDefaultMode(TSharedPtr<FPCGEditor> InPCGEditor);`
- L26 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L27 _public prototype_ `virtual void PreDeactivateMode() override;`
- L28 _public prototype_ `virtual void PostActivateMode() override;`
- L31 _private member_ `FWorkflowAllowedTabSet TabFactories;`
- L32 _private member_ `FWorkflowAllowedTabSet ExtraTabFactories;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PCGEditorDefaultMode`
- L15 _prototype_ `TSharedPtr<FTabManager::FLayout> GetTabLayout();` (scope `PCGEditorDefaultMode`)

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorGraph.h` (Private)


#### class `UPCGEditorGraph`  
`class UPCGEditorGraph : public UEdGraph, public IPropertyBagEdGraph`  
_L27-92_
- reflection: `UCLASS()`
- inherits: `UEdGraph,IPropertyBagEdGraph`
- L33 _public prototype_ `virtual void BeginDestroy() override;`
- L37 _public prototype_ `void InitFromNodeGraph(UPCGGraph* InPCGGraph);` — Initialize the editor graph from a PCGGraph
- L40 _public prototype_ `void ReconstructGraph();` — If the underlying graph changed without UI interaction, use this function to reconstruct the UI elements.
- L43 _public prototype_ `void SaveState();` — When the editor is closing
- L46 _public prototype_ `void CreateLinks(UPCGEditorGraphNodeBase* InGraphNode, bool bCreateInbound, bool bCreateOutbound);` — Creates the links for a given node
- L49 _public prototype_ `void ReplicateExtraNodes() const;` — To be called everytime we need to replicate our extra nodes to the underlying PCGGraph
- L51 _public function_ `UPCGGraph* GetPCGGraph() const`
- L53 _public function_ `void SetEditor(TWeakPtr<FPCGEditor> InEditor)`
- L54 _public function_ `TWeakPtr<FPCGEditor> GetEditor() const`
- L56 _public prototype_ `FText GetDisplayName() const;`
- L59 _public prototype_ `void UpdateVisualizations(IPCGGraphExecutionSource* PCGSourceBeingInspected, const FPCGStack* PCGStackBeingInspected);` — Updates the grid size visualization in the editor.
- L62 _public prototype_ `const UPCGEditorGraphNodeBase* GetEditorNodeFromPCGNode(const UPCGNode* InPCGNode) const;` — Returns the PCG editor graph node corresponding to the given PCG node.
- L63 _public prototype_ `UPCGEditorGraphNodeBase* GetEditorNodeFromPCGNode(const UPCGNode* InPCGNode);`
- L66 _public prototype_ `bool IsEdgeUsedByExecution(const UPCGEdge* InEdge) const;` — Returns whether the edge is used by the downstream node's execution. Cached per graph change.
- L69 _public prototype_ `static TSubclassOf<UPCGEditorGraphNodeBase> GetGraphNodeClassFromPCGSettings(const UPCGSettings* Settings);` — Returns the PCG Editor Graph Node that should be spawned from any given PCG Settings.
- L72 _protected prototype_ `void CreateLinks(UPCGEditorGraphNodeBase* InGraphNode, bool bCreateInbound, bool bCreateOutbound, const TMap<UPCGNode*, UPCGEditorGraphNodeBase*>& InPCGNodeToPCGEditorNodeMap);`
- L74 _protected prototype_ `void OnGraphChanged(UPCGGraphInterface* InGraph, EPCGChangeType ChangeType);`
- L75 _protected prototype_ `void OnGraphUserParametersChanged(UPCGGraphInterface* InGraph, EPCGGraphParameterEvent ChangeType, FName ChangedPropertyName);`
- L78 _protected prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraphPin(const UEdGraphPin* Pin) const override;`
- L79 _protected prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraphNode(const UEdGraphNode* Node) const override;`
- L80 _protected prototype_ `virtual bool CanReceivePropertyBagDetailsDropOnGraph(const UEdGraph* Graph) const override;`
- L81 _protected prototype_ `virtual FReply OnPropertyBagDetailsDropOnGraphPin(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraphPin* Pin, const FVector2f& GraphPosition) const override;`
- L82 _protected prototype_ `virtual FReply OnPropertyBagDetailsDropOnGraph(const FPropertyBagPropertyDesc& PropertyDesc, UEdGraph* Graph, const FVector2f& GraphPosition) const override;`
- L87 _private member_ `TWeakObjectPtr<UPCGGraph> WeakPCGGraph;` — `UPROPERTY()`
- L89 _private member_ `TWeakPtr<FPCGEditor> PCGEditor = nullptr;`
- L91 _private member_ `mutable TMap<TObjectKey<UPCGEdge>, bool> CachedEdgeUsedByExecution;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace PCGEditorGraphUtils`
- L23 _prototype_ `void GetInspectablePin(const UPCGNode* InNode, const UPCGPin* InPin, const UPCGNode*& OutNode, const UPCGPin*& OutPin);` (scope `PCGEditorGraphUtils`) — Goes up the graph to the first non-reroute node it can, assuming it's properly connected.

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorMenuContext.h` (Private)


#### class `UPCGEditorMenuContext`  
`class UPCGEditorMenuContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<FPCGEditor> PCGEditor;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorProgressNotification.h` (Private)


#### class `FPCGEditorProgressNotification`  
`class FPCGEditorProgressNotification : public IPCGEditorProgressNotification`  
_L11-40_
- inherits: `IPCGEditorProgressNotification`
- L14 _public prototype_ `FPCGEditorProgressNotification(const FTextFormat& InTextFormat, bool bInCanCancel);`
- L15 _public prototype_ `virtual ~FPCGEditorProgressNotification();`
- L17 _public prototype_ `virtual void Update(uint32 InNumRemainingTasks) override;`
- L19 _public prototype_ `DECLARE_DERIVED_EVENT(FPCGEditorProgressNotification, IPCGEditorProgressNotification::FCancelTasksEvent, FCancelTasksEvent);`
- L20 _public function_ `virtual FCancelTasksEvent& OnCancelTasks() override`
- L22 _public function_ `virtual uint32 GetNumTasks() const override`
- L23 _public function_ `virtual uint32 GetNumTasksDone() const override`
- L24 _public function_ `virtual const FTextFormat& GetTextFormat() const override`
- L26 _public function_ `virtual void Cancel() override`
- L27 _public function_ `virtual bool CanCancel() const override`
- L30 _private member_ `uint32 NumTasks = 0;`
- L31 _private member_ `uint32 NumTasksDone = 0;`
- L32 _private member_ `uint32 NumTasksRemaining = 0;`
- L34 _private member_ `bool bCanCancel = false;`
- L35 _private member_ `bool bIsCompleted = false;`
- L37 _private member_ `FTextFormat TextFormat;`
- L38 _private member_ `FCancelTasksEvent CancelTasksEvent;`
- L39 _private member_ `TSharedPtr<SNotificationItem> NotificationItem;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DERIVED_EVENT(FPCGEditorProgressNotification, IPCGEditorProgressNotification::FCancelTasksEvent, FCancelTasksEvent);`

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorStyle.h` (Private)


#### class `FPCGEditorStyle`  
`class FPCGEditorStyle : public FSlateStyleSet`  
_L7-17_
- inherits: `FSlateStyleSet`
- L10 _public prototype_ `static void Register();`
- L11 _public prototype_ `static void Unregister();`
- L13 _public prototype_ `static const FPCGEditorStyle& Get();`
- L16 _private prototype_ `FPCGEditorStyle();`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace PCGEditorStyleConstants`
- L21 _variable_ `const FName Pin_SD_SC_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L22 _variable_ `const FName Pin_SD_SC_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L23 _variable_ `const FName Pin_SD_SC_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L24 _variable_ `const FName Pin_SD_SC_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L26 _variable_ `const FName Pin_SD_MC_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L27 _variable_ `const FName Pin_SD_MC_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L28 _variable_ `const FName Pin_SD_MC_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L29 _variable_ `const FName Pin_SD_MC_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L31 _variable_ `const FName Pin_MD_SC_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L32 _variable_ `const FName Pin_MD_SC_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L33 _variable_ `const FName Pin_MD_SC_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L34 _variable_ `const FName Pin_MD_SC_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L36 _variable_ `const FName Pin_MD_MC_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L37 _variable_ `const FName Pin_MD_MC_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L38 _variable_ `const FName Pin_MD_MC_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L39 _variable_ `const FName Pin_MD_MC_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L41 _variable_ `const FName Pin_Param_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L42 _variable_ `const FName Pin_Param_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L43 _variable_ `const FName Pin_Param_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L44 _variable_ `const FName Pin_Param_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L46 _variable_ `const FName Pin_Composite_IN_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L47 _variable_ `const FName Pin_Composite_IN_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L48 _variable_ `const FName Pin_Composite_OUT_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L49 _variable_ `const FName Pin_Composite_OUT_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L51 _variable_ `const FName Pin_Required = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L52 _variable_ `const FName Pin_Graph_Dependency_C = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L53 _variable_ `const FName Pin_Graph_Dependency_DC = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L55 _variable_ `const FName Node_Overlay_Inactive = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L57 _variable_ `const FName Node_Overlay_GridSizeLabel_Active_Border = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L59 _variable_ `const FName NodeFilter = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L60 _variable_ `const FName NodeConvert = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L62 _variable_ `const FName Node_ToolStart = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L63 _variable_ `const FName Node_DataOverride = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L64 _variable_ `const FName Node_ManualEdit = TEXT("PCG` (scope `PCGEditorStyleConstants`)
- L66 _variable_ `const float Node_Overlay_GridSizeLabel_BorderRadius = 11.0f;` (scope `PCGEditorStyleConstants`)
- L67 _variable_ `const float Node_Overlay_GridSizeLabel_BorderStroke = 1.5f;` (scope `PCGEditorStyleConstants`)

### `Plugins/PCG/Source/PCGEditor/Private/PCGEditorUtils.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace PCGEditorUtils`
- L17 _prototype_ `bool IsAssetPCGBlueprint(const FAssetData& InAssetData);` (scope `PCGEditorUtils`)
- L24 _prototype_ `void GetParentPackagePathAndUniqueName(const UObject* OriginalObject, const FString& NewAssetTentativeName, FString& OutPackagePath, FString& OutUniqueName);` (scope `PCGEditorUtils`) — From an object, get its parent package and a unique name For example, if you want to create a new asset next to the original object, it will return the parent package of the original package and a unique name for the new asset.
- L27 _prototype_ `void ForEachAssetData(const FARFilter& Filter, TFunctionRef<bool(const FAssetData&)> InFunc);` (scope `PCGEditorUtils`) — Methods related to visiting asset data. Ends early if InFunc returns false
- L29 _prototype_ `void ForEachPCGBlueprintAssetData(TFunctionRef<bool(const FAssetData&)> InFunc);` (scope `PCGEditorUtils`)
- L30 _prototype_ `void ForEachPCGSettingsAssetData(TFunctionRef<bool(const FAssetData&)> InFunc);` (scope `PCGEditorUtils`)
- L31 _prototype_ `void ForEachPCGGraphAssetData(TFunctionRef<bool(const FAssetData&)> InFunc);` (scope `PCGEditorUtils`)
- L32 _prototype_ `void ForEachPCGAssetData(TFunctionRef<bool(const FAssetData&)> InFunc);` (scope `PCGEditorUtils`)
- L35 _prototype_ `void ForcePCGBlueprintVariableVisibility();` (scope `PCGEditorUtils`) — Asset deprecation methods
- L38 _prototype_ `bool PickGraphTemplate(FAssetData& OutData, const FText& InTitleOverride = FText());` (scope `PCGEditorUtils`) — Opens a template picker dialog. Returns true if user selected 'ok'.
- L41 _prototype_ `void OpenAssetOrMoveToActorOrComponent(const FSoftObjectPath& InPath);` (scope `PCGEditorUtils`) — Open an asset or jumps to an actor/component and select it. Will load it, and won't load a new level
- L43 _function_ `void OpenConfirmationDialog(FText InMessage, TFunction<void()> OnOk, TFunction<void()> OnCancel = [] {}, TSharedPtr<SWidget> InAdditionalContent = SNullWidget::NullWidget);` (scope `PCGEditorUtils`)
- L43 _prototype_ `void OpenConfirmationDialog(FText InMessage, TFunction<void()> OnOk, TFunction<void()> OnCancel = [] {}, TSharedPtr<SWidget> InAdditionalContent = SNullWidget::NullWidget);` (scope `PCGEditorUtils`)

### `Plugins/PCG/Source/PCGEditor/Private/PCGGraphFactory.h` (Private)


#### class `UPCGGraphFactory`  
`class UPCGGraphFactory : public UFactory`  
_L13-31_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L18 _public prototype_ `UPCGGraphFactory(const FObjectInitializer& ObjectInitializer);`
- L21 _public member_ `TObjectPtr<UPCGGraph> TemplateGraph;` — `UPROPERTY()`
- L25 _public member_ `bool bSkipTemplateSelection = false;` — `UPROPERTY()` — Disables template selection, even if some exist. Useful when creating a graph from a standalone factory.
- L28 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L29 _public prototype_ `virtual bool ConfigureProperties() override;`
- L30 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### class `UPCGGraphInstanceFactory`  
`class UPCGGraphInstanceFactory : public UFactory`  
_L34-47_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- L39 _public prototype_ `UPCGGraphInstanceFactory(const FObjectInitializer& ObjectInitializer);`
- L42 _public member_ `TObjectPtr<UPCGGraphInterface> ParentGraph;` — `UPROPERTY()`
- L45 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L46 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGHLSLSyntaxHighlighter.h` (Private)


#### class `FPCGHLSLSyntaxHighlighter`  
`class FPCGHLSLSyntaxHighlighter : public FHLSLSyntaxHighlighterMarshaller, public FTickableEditorObject`  
_L20-46_
- inherits: `FHLSLSyntaxHighlighterMarshaller,FTickableEditorObject`
- desc: Get/set the raw text to/from a text layout, and also inject syntax highlighting for our rich-text markup
- L23 _public prototype_ `static TSharedRef<FPCGHLSLSyntaxHighlighter> Create(const FSyntaxTextStyle& InSyntaxTextStyle = GetSyntaxTextStyle());`
- L24 _public prototype_ `static FSyntaxTextStyle GetSyntaxTextStyle();`
- L26 _public prototype_ `void SetCompilerMessages(const FPCGCompilerDiagnostics& InCompilerMessages);`
- L27 _public prototype_ `void ClearCompilerMessages();`
- L31 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L32 _public prototype_ `virtual TStatId GetStatId() const override;`
- L36 _protected prototype_ `FPCGHLSLSyntaxHighlighter(TSharedPtr<ISyntaxTokenizer> InTokenizer, const FSyntaxTextStyle& InSyntaxTextStyle);`
- L38 _protected prototype_ `virtual void ParseTokens(const FString& SourceString, FTextLayout& TargetTextLayout, TArray<ISyntaxTokenizer::FTokenizedLine> TokenizedLines) override;`
- L39 _protected prototype_ `virtual FTextLayout::FNewLineData ProcessTokenizedLine(const ISyntaxTokenizer::FTokenizedLine& TokenizedLine, const int32& LineNumber, const FString& SourceString, EParseState& CurrentParseState) override;`
- L41 _protected member_ `TMultiMap<int32 , FPCGCompilerDiagnostic> CompilerMessages;`
- L44 _private member_ `int32 CachedFontSize = 0;`
- L45 _private member_ `TArray<FTextLineHighlight> LineHighlightsToAdd;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGManualEditPanelManager.h` (Private)


#### class `FPCGManualEditPanelManager`  
`class FPCGManualEditPanelManager`  
_L20-48_
- desc: Manages the lifecycle of the manual edit panel viewport overlay, including selection tracking, panel creation/destruction, delegates, etc.
- L23 _public prototype_ `FPCGManualEditPanelManager();`
- L24 _public prototype_ `~FPCGManualEditPanelManager();`
- L26 _public prototype_ `FPCGManualEditPanelManager(const FPCGManualEditPanelManager&) = delete;`
- L27 _public prototype_ `FPCGManualEditPanelManager& operator=(const FPCGManualEditPanelManager&) = delete;`
- L30 _public function_ `TSharedPtr<SPCGManualEditPanel> GetManualEditPanel() const` — Returns the manual edit panel if one is currently active.
- L33 _public prototype_ `void UpdateManualEditPanelVisibility();` — Checks the tracked component and shows/hides the panel as needed.
- L36 _private prototype_ `void OnEditorSelectionChanged(UObject* Object);`
- L37 _private prototype_ `void ShowManualEditPanel(UPCGGraph* InGraph);`
- L38 _private prototype_ `void HideManualEditPanel();`
- L41 _private prototype_ `void DismissManualEditPanel();` — Removes the panel overlay and clears transient editing flags, but preserves TrackedPCGComponent so the panel can reappear if a new node is marked.
- L43 _private member_ `TSharedPtr<SPCGManualEditPanel> ManualEditPanel;`
- L44 _private member_ `TSharedPtr<SWidget> ManualEditOverlayWidget;`
- L45 _private member_ `TWeakPtr<SLevelViewport> OverlayViewport;`
- L46 _private member_ `FDelegateHandle SelectionChangedDelegateHandle;`
- L47 _private member_ `TWeakObjectPtr<UPCGComponent> TrackedPCGComponent;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGSettingsDragDropAction.h` (Private)


#### class `FPCGSettingsDragDropAction`  
`class FPCGSettingsDragDropAction : public FGraphSchemaActionDragDropAction`  
_L12-34_
- inherits: `FGraphSchemaActionDragDropAction`
- L15 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FPCGSettingsDragDropAction, FGraphSchemaActionDragDropAction)`
- L21 _public function_ `static TSharedRef<FPCGSettingsDragDropAction> New(TSharedPtr<FEdGraphSchemaAction> InAction, const FSoftObjectPath& InSettingsObjectPath)`
- L31 _protected prototype_ `FPCGSettingsDragDropAction() = default;`
- L33 _protected member_ `FSoftObjectPath SettingsObjectPath;`

### `Plugins/PCG/Source/PCGEditor/Private/PCGVolumeFactory.h` (Private)


#### class `UPCGVolumeFactory`  
`class UPCGVolumeFactory : public UActorFactoryBoxVolume`  
_L13-26_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UActorFactoryBoxVolume`
- L18 _public prototype_ `UPCGVolumeFactory(const FObjectInitializer& ObjectInitializer);`
- L21 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L22 _public prototype_ `virtual bool PreSpawnActor(UObject* Asset, FTransform& InOutLocation) override;`
- L23 _public prototype_ `virtual void PostPlaceAsset(TArrayView<const FTypedElementHandle> InElementHandles, const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`
- L24 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphNodePin.h` (Private)


#### class `SPCGEditorGraphNodePin`  
`class SPCGEditorGraphNodePin : public SGraphPin`  
_L12-58_
- inherits: `SGraphPin`
- desc: PCG pin primarily to give more control over pin coloring.
- L15 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphNodePin) : _PinLabelStyle(NAME_DefaultPinLabelStyle) , _SideToSideMargin(5.0f) , _UsePinColorForText(false) , _ShowLabel(true) , _IsRenameable(false)`
- L23 _public prototype_ `SLATE_ARGUMENT(FName, PinLabelStyle) SLATE_ARGUMENT(float, SideToSideMargin) SLATE_ARGUMENT(bool, UsePinColorForText) SLATE_ARGUMENT(bool, ShowLabel) SLATE_ARGUMENT(bool, IsRenameable) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L33 _public prototype_ `virtual FSlateColor GetPinColor() const override;`
- L34 _public prototype_ `virtual FSlateColor GetPinTextColor() const override;`
- L35 _public prototype_ `FName GetLabelStyle(FName DefaultLabelStyle) const;`
- L36 _public prototype_ `bool GetExtraIcon(FName& OutExtraIcon, FText& OutTooltip) const;`
- L39 _public prototype_ `bool ShouldDisplayAsRequiredForExecution() const;` — Whether pin is required to be connected for execution.
- L42 _public prototype_ `void EnterLabelEditMode();` — Enters inline edit mode on the pin label. Only valid for renameable dynamic pins.
- L46 _protected prototype_ `bool SetPinDefaultValue(const FString& NewValue);` — Sets pin default value inside a scoped transaction if the value changed. Returns true if the value was set.
- L48 _protected member_ `FSimpleDelegate OnModifyDelegate;`
- L51 _private prototype_ `void ApplyUnusedPinStyle(FSlateColor& InOutColor) const;`
- L52 _private prototype_ `void GetPCGNodeAndPin(const UPCGNode*& OutNode, const UPCGPin*& OutPin) const;`
- L54 _private prototype_ `bool OnVerifyPinLabelChanged(const FText& InText, FText& OutErrorMessage);`
- L55 _private prototype_ `void OnPinLabelCommitted(const FText& InText, ETextCommit::Type CommitType);`
- L57 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableLabel;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinBool.h` (Private)


#### class `SPCGEditorGraphPinBool`  
`class SPCGEditorGraphPinBool final : public SPCGEditorGraphNodePin`  
_L13-65_
- inherits: `SPCGEditorGraphNodePin`
- L16 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinBool)`
- L17 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L27 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L39 _protected function_ `ECheckBoxState IsDefaultValueChecked() const` — Determine if the checkbox should be checked or not
- L46 _protected function_ `void OnDefaultValueCheckBoxChanged(const ECheckBoxState InIsChecked) const` — Called when check box is changed
- L64 _private member_ `FSimpleDelegate OnModifyDelegate;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinNumSlider.h` (Private)


#### class `SPCGEditorGraphPinNumSlider`  
`template <typename NumericType> class SPCGEditorGraphPinNumSlider final : public SPCGEditorGraphNodePin`  
_L17-172_
- inherits: `SPCGEditorGraphNodePin`
- L20 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinNumSlider) : _PinProperty(nullptr) , _MinDesiredBoxWidth(60.0f) , _MaxDesiredBoxWidth(400.f) , _ShouldShowDisabledWhenConnected(true)`
- L27 _public function_ `SLATE_ARGUMENT(FProperty*, PinProperty) SLATE_ARGUMENT(float, MinDesiredBoxWidth) SLATE_ARGUMENT(float, MaxDesiredBoxWidth) SLATE_ARGUMENT(bool, ShouldShowDisabledWhenConnected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L45 _public function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L83 _private function_ `void OnValueChanged(NumericType NewValue)`
- L88 _private function_ `void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitInfo)`
- L108 _private function_ `void OnBeginSliderMovement()` — Called when the slider begins to move.
- L119 _private function_ `void OnEndSliderMovement(NumericType NewValue)` — Called when the slider stops moving.
- L125 _private function_ `TOptional<NumericType> GetNumericValue() const`
- L132 _private function_ `virtual EVisibility GetDefaultValueVisibility() const override`
- L165 _private member_ `NumericType CachedValue = 0;`
- L166 _private member_ `NumericType SliderValue = 0;`
- L167 _private member_ `float MinDesiredBoxWidth = 0;`
- L168 _private member_ `float MaxDesiredBoxWidth = 0;`
- L169 _private member_ `bool bIsUsingSlider = false;`
- L170 _private member_ `bool bShouldHideWhenConnected = false;`
- L171 _private member_ `FSimpleDelegate OnModifyDelegate;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinQuaternion.h` (Private)


#### class `SPCGEditorGraphPinQuaternion`  
`class SPCGEditorGraphPinQuaternion final : public SPCGEditorGraphNodePin`  
_L13-106_
- inherits: `SPCGEditorGraphNodePin`
- desc: Quaternion pin widget. Displays rotator inputs (Roll, Pitch, Yaw) that are converted to/from FQuat for storage. Note: Derived from SPCGEditorGraphPinVectorSlider pattern.
- L16 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinQuaternion)`
- L19 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L28 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L43 _private function_ `FString GetCurrentStringValue(const int32 Index) const` — --- Getter (index: 0=Roll, 1=Pitch, 2=Yaw) ---
- L53 _private function_ `void OnValueCommitted(const double NewValue, ETextCommit::Type, const int32 Index)` — --- Setter (the component index is passed along with the value) ---
- L59 _private function_ `void UpdateFromDefaultValue() const`
- L80 _private function_ `void SetDefaultValue()`
- L88 _private function_ `void SetComponent(double& Component, const double NewValue)`
- L104 _private member_ `mutable FRotator CachedRotator = FRotator::ZeroRotator;`
- L105 _private member_ `mutable uint32 DefaultValueHash = 0;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinSoftClassPath.h` (Private)


#### class `SPCGEditorGraphPinSoftClassPath`  
`class SPCGEditorGraphPinSoftClassPath final : public SPCGEditorGraphNodePin`  
_L23-170_
- inherits: `SPCGEditorGraphNodePin`
- L26 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinSoftClassPath)`
- L29 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L38 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L98 _private function_ `FText GetDisplayText() const`
- L109 _private function_ `FText GetFullPathText() const`
- L114 _private function_ `TSharedRef<SWidget> GenerateClassPicker()`
- L136 _private function_ `void OnClassPicked(UClass* ChosenClass)`
- L145 _private function_ `FReply OnClickUse()`
- L157 _private function_ `FReply OnClickBrowse()`
- L169 _private member_ `TSharedPtr<SComboButton> ClassPickerAnchor;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinSoftObjectPath.h` (Private)


#### class `SPCGEditorGraphPinSoftObjectPath`  
`class SPCGEditorGraphPinSoftObjectPath final : public SPCGEditorGraphNodePin`  
_L25-187_
- inherits: `SPCGEditorGraphNodePin`
- desc: Note: Based on KismetPins/SGraphPinObject.h
- L28 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinSoftObjectPath)`
- L31 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L40 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L100 _private function_ `FText GetDisplayText() const`
- L111 _private function_ `FText GetFullPathText() const`
- L116 _private function_ `TSharedRef<SWidget> GenerateAssetPicker()`
- L139 _private function_ `void OnAssetSelected(const FAssetData& AssetData)`
- L148 _private function_ `void OnAssetEnterPressed(const TArray<FAssetData>& InSelectedAssets)`
- L156 _private function_ `FReply OnClickUse()`
- L168 _private function_ `FReply OnClickBrowse()`
- L186 _private member_ `TSharedPtr<SComboButton> AssetPickerAnchor;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinString.h` (Private)


#### class `SPCGEditorGraphPinString`  
`class SPCGEditorGraphPinString final : public SPCGEditorGraphNodePin`  
_L14-96_
- inherits: `SPCGEditorGraphNodePin`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinString) : _MinDesiredBoxWidth(60.f) , _MaxDesiredBoxWidth(300.f) , _IsMultiline(false) , _OverflowPolicy(ETextOverflowPolicy::Ellipsis)`
- L23 _public function_ `SLATE_ARGUMENT(float, MinDesiredBoxWidth) SLATE_ARGUMENT(float, MaxDesiredBoxWidth) SLATE_ARGUMENT(bool, IsMultiline) SLATE_ARGUMENT(ETextOverflowPolicy, OverflowPolicy) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L42 _public function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L63 _public function_ `FText GetTypeInValue() const`
- L68 _public function_ `void SetTypeInValue(const FText& NewTypeInValue, ETextCommit::Type CommitInfo) const`
- L84 _public function_ `bool GetDefaultValueIsReadOnly() const`
- L90 _private member_ `TArray<TSharedPtr<FString>> ComboBoxOptions;`
- L91 _private member_ `float MinDesiredBoxWidth = 0;`
- L92 _private member_ `float MaxDesiredBoxWidth = 0;`
- L93 _private member_ `bool bIsMultiline = false;`
- L94 _private member_ `ETextOverflowPolicy OverflowPolicy = ETextOverflowPolicy::Clip;`
- L95 _private member_ `FSimpleDelegate OnModifyDelegate;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinTransform.h` (Private)


#### class `SPCGEditorGraphPinTransform`  
`class SPCGEditorGraphPinTransform final : public SPCGEditorGraphNodePin`  
_L16-205_
- inherits: `SPCGEditorGraphNodePin`
- desc: Transform pin widget. Displays Location (XYZ), Rotation (Roll/Pitch/Yaw), and Scale (XYZ). Note: Derived from SPCGEditorGraphPinVectorSlider pattern.
- L19 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinTransform)`
- L22 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L31 _protected function_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override`
- L121 _private function_ `FString GetLocation(const int32 Index) const` — --- Getters (index: 0=X/Roll, 1=Y/Pitch, 2=Z/Yaw) ---
- L133 _private function_ `FString GetRotation(const int32 Index) const`
- L139 _private function_ `FString GetScale(const int32 Index) const`
- L142 _private function_ `void OnLocationCommitted(const double NewValue, ETextCommit::Type, const int32 Index)` — --- Setters (the component index is passed along with the value) ---
- L144 _private function_ `void OnRotationCommitted(const double NewValue, ETextCommit::Type, const int32 Index)`
- L151 _private function_ `void OnScaleCommitted(const double NewValue, ETextCommit::Type, const int32 Index)`
- L153 _private function_ `void SetComponent(double& Component, const double NewValue)`
- L169 _private function_ `void UpdateFromDefaultValue() const`
- L193 _private function_ `void SetDefaultValue()`
- L201 _private member_ `mutable FVector CachedLocation = FVector::ZeroVector;`
- L202 _private member_ `mutable FRotator CachedRotation = FRotator::ZeroRotator;`
- L203 _private member_ `mutable FVector CachedScale = FVector::OneVector;`
- L204 _private member_ `mutable uint32 DefaultValueHash = 0;`

### `Plugins/PCG/Source/PCGEditor/Private/Pins/SPCGEditorGraphPinVectorSlider.h` (Private)


#### class `SPCGEditorGraphPinVectorSlider`  
`template <typename T> class SPCGEditorGraphPinVectorSlider final : public SPCGEditorGraphNodePin`  
_L36-303_
- inherits: `SPCGEditorGraphNodePin`
- L38 _private typedef_ `using TVectorTrait = PCGEditorGraphPinVectorSlider::TVectorTrait<T>;`
- L40 _private typedef_ `using DataType = typename TVectorTrait::DataType;`
- L43 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphPinVectorSlider)`
- L48 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin, TDelegate<void()>&& OnModify)`
- L57 _protected function_ `TSharedRef<SWidget> GetDefaultValueWidget() override`
- L112 _private function_ `FString GetCurrentStringValue_0() const` — Text Box 0: Rotator->Roll, Vector->X
- L120 _private function_ `FString GetCurrentStringValue_1() const` — Text Box 1: Rotator->Pitch, Vector->Y
- L126 _private function_ `FString GetCurrentStringValue_2() const` — Text Box 2: Rotator->Yaw, Vector->Z
- L132 _private function_ `FString GetCurrentStringValue_3() const` — Text Box 3: FVector4 only
- L138 _private function_ `void OnCommittedValueTextBox_0(DataType NewValue, const ETextCommit::Type CommitInfo)`
- L144 _private function_ `void OnCommittedValueTextBox_1(DataType NewValue, const ETextCommit::Type CommitInfo)`
- L149 _private function_ `void OnCommittedValueTextBox_2(DataType NewValue, const ETextCommit::Type CommitInfo)`
- L154 _private function_ `void OnCommittedValueTextBox_3(DataType NewValue, const ETextCommit::Type CommitInfo)`
- L160 _private function_ `void UpdateFromDefaultValue() const`
- L184 _private function_ `void SetDefaultValue() const`
- L194 _private function_ `void SetNewComponentValue(const EVectorAxis Axis, const DataType NewComponentValue, const bool bUpdate)`
- L215 _private function_ `static double& GetComponentRefAlongAxis(T& Value, const EVectorAxis Axis)`
- L257 _private function_ `static const double& GetComponentRefAlongAxis(const T& Value, const EVectorAxis Axis)`
- L263 _private function_ `FString GetComponentStringAlongAxis(const EVectorAxis Axis) const`
- L269 _private function_ `FString GetSerializedString() const`
- L276 _private function_ `T ConvertDefaultValueStringToRotator(const FString& InDefaultValueString) const`
- L291 _private function_ `T ConvertDefaultValueStringToVector(const FString& InDefaultValueString) const`
- L300 _private member_ `mutable T CachedValue = PCG::Private::MetadataTraits<T>::ZeroValue();`
- L301 _private member_ `mutable uint32 DefaultValueHash = 0;`
- L302 _private member_ `FSimpleDelegate OnModifyDelegate;`

#### enum `SPCGEditorGraphPinVectorSlider::EVectorAxis`  
`enum EVectorAxis`  
_L103-109_
- L105 _public enumerator_ `Axis_0`
- L106 _public enumerator_ `Axis_1`
- L107 _public enumerator_ `Axis_2`
- L108 _public enumerator_ `Axis_3`

#### struct `PCGEditorGraphPinVectorSlider::TVectorTrait`  
`template <typename T> struct TVectorTrait<UE::Math::TVector<T>> : std::true_type`  
_L308-312_
- inherits: `std::true_type`
- L310 _public typedef_ `using DataType = T;`
- L311 _public member_ `static constexpr bool bIsRotator = false;`
- L325 _public member_ `static constexpr bool bIsRotator = true;`
- L331 _public typedef_ `using DataType = void;`

#### struct `PCGEditorGraphPinVectorSlider::TVectorTrait`  
`template <typename T> struct TVectorTrait<UE::Math::TVector2<T>> : TVectorTrait<UE::Math::TVector<T>>`  
_L315-316_
- inherits: `TVectorTrait<UE::Math::TVector<T>>`
- L310 _public typedef_ `using DataType = T;`
- L311 _public member_ `static constexpr bool bIsRotator = false;`
- L325 _public member_ `static constexpr bool bIsRotator = true;`
- L331 _public typedef_ `using DataType = void;`

#### struct `PCGEditorGraphPinVectorSlider::TVectorTrait`  
`template <typename T> struct TVectorTrait<UE::Math::TVector4<T>> : TVectorTrait<UE::Math::TVector<T>>`  
_L319-320_
- inherits: `TVectorTrait<UE::Math::TVector<T>>`
- L310 _public typedef_ `using DataType = T;`
- L311 _public member_ `static constexpr bool bIsRotator = false;`
- L325 _public member_ `static constexpr bool bIsRotator = true;`
- L331 _public typedef_ `using DataType = void;`

#### struct `PCGEditorGraphPinVectorSlider::TVectorTrait`  
`template <typename T> struct TVectorTrait<UE::Math::TRotator<T>> : TVectorTrait<UE::Math::TVector<T>>`  
_L323-326_
- inherits: `TVectorTrait<UE::Math::TVector<T>>`
- L310 _public typedef_ `using DataType = T;`
- L311 _public member_ `static constexpr bool bIsRotator = false;`
- L325 _public member_ `static constexpr bool bIsRotator = true;`
- L331 _public typedef_ `using DataType = void;`

#### struct `PCGEditorGraphPinVectorSlider::TVectorTrait`  
`template <typename> struct TVectorTrait : std::false_type`  
_L329-333_
- inherits: `std::false_type`
- L310 _public typedef_ `using DataType = T;`
- L311 _public member_ `static constexpr bool bIsRotator = false;`
- L325 _public member_ `static constexpr bool bIsRotator = true;`
- L331 _public typedef_ `using DataType = void;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace PCGEditorGraphPinVectorSlider`
- L305 _namespace_ `namespace PCGEditorGraphPinVectorSlider`

### `Plugins/PCG/Source/PCGEditor/Private/SPCGManualEditPanel.h` (Private)


#### enum `EPCGManualEditPanelMode`  
`enum class EPCGManualEditPanelMode : uint8`  
_L27-31_
- desc: Controls whether the panel node selection is via the user or an external system.
- L29 _public enumerator_ `UserControlled`
- L30 _public enumerator_ `ExternallyControlled`

#### struct `FPCGManualEditNodeEntry`  
`struct FPCGManualEditNodeEntry`  
_L33-40_
- L35 _public member_ `TWeakObjectPtr<const UPCGNode> Node;`
- L36 _public member_ `FText DisplayName;`
- L37 _public member_ `bool bIsMarked = false;`
- L38 _public member_ `bool bIsTemporary = false;`
- L39 _public member_ `bool bIsActive = false;`

#### struct `FPCGManualEditNodeConfiguration`  
`struct FPCGManualEditNodeConfiguration`  
_L43-50_
- desc: Per-node transient configuration for the manual edit panel. Controls delta creation behavior in the viewport.
- L46 _public member_ `bool bSignaturePosition = true;` — Signature controls. I.e. transform components that are used to match source points.
- L47 _public member_ `bool bSignatureRotation = false;`
- L48 _public member_ `bool bSignatureScale = false;`
- L49 _public member_ `double SignatureTolerance = PCG::DataOverride::Constants::SpatialToleranceDefault;`

#### class `SPCGManualEditPanel`  
`class SPCGManualEditPanel : public SCompoundWidget`  
_L52-195_
- inherits: `SCompoundWidget`
- L55 _public function_ `SLATE_BEGIN_ARGS(SPCGManualEditPanel)`
- L56 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UPCGGraph>, Graph) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L62 _public prototype_ `void RefreshNodeList();` — Refresh the node list from the graph.
- L65 _public prototype_ `void SelectNodeInList(const UPCGNode* InNode);` — Selects the given node in the panel's list.
- L68 _public prototype_ `TSharedPtr<SWidget> GetOverlayWidget() const;` — Get the overlay wrapper widget.
- L71 _public prototype_ `TSharedRef<SWidget> CreateOverlayWidget();` — Create the overlay wrapper around this panel for viewport integration.
- L74 _public prototype_ `TSharedPtr<const FPCGManualEditNodeConfiguration> GetConfigurationForActiveNode() const;` — Returns the configuration for the currently selected node, or nullptr if none.
- L77 _public prototype_ `TSharedPtr<FPCGManualEditNodeConfiguration> GetOrCreateConfigurationForNode(const UPCGNode* InNode);` — Returns the configuration for the specified node, creating it on demand.
- L80 _public prototype_ `void SetDeltaContext(UPCGComponent* InComponent, const FPCGSourceDataStorageKey& InStorageKey);` — Sets the active delta context for querying the collection.
- L83 _public prototype_ `void SetSelectionState( bool bHasSelection, const FPCGDeltaKey& SelectedKey, const FTransform& InSelectionTransform = FTransform::Identity, int32 InSelectedElementIndex = INDEX_NONE, int32 InOriginalElementIndex = INDEX_NONE);` — Update the panel and visualizer's current selection.
- L91 _public prototype_ `void RefreshActiveExtensionLists();` — Refresh the active extension's lists from the current delta context.
- L94 _public prototype_ `void SetVisualizerActions(const FPCGDeltaViewportCallbacks& InActions);` — Provide the visualizer callbacks for extensions to invoke.
- L97 _public member_ `FOnPCGManualEditPanelNodeSelected OnNodeSelected;` — Delegate fired when a node is selected in the panel.
- L100 _public member_ `FOnPCGJumpToNode OnJumpToNode;` — Jump to node in the graph editor.
- L103 _public prototype_ `const UPCGNode* GetActiveNode() const;` — Returns the currently selected node or nullptr if none.
- L106 _public prototype_ `void SelectNode(const UPCGNode* InNode);` — Drives the node list selection.
- L109 _public function_ `EPCGManualEditPanelMode GetMode() const` — Returns the current panel mode.
- L112 _public function_ `void SetMode(const EPCGManualEditPanelMode InMode)` — Switches the panel's mode. While ExternallyControlled, external owners control lifetime and temp-flag state.
- L115 _public function_ `const UScriptStruct* GetActiveDeltaType() const` — Returns the delta type. Persists across node selection changes.
- L118 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FPCGManualEditNodeEntry> Entry, const TSharedRef<STableViewBase>& OwnerTable);`
- L119 _private prototype_ `void OnListSelectionChanged(TSharedPtr<FPCGManualEditNodeEntry> SelectedEntry, ESelectInfo::Type SelectInfo);`
- L120 _private prototype_ `void OnDeltaTypeChanged(const UScriptStruct* InType, ESelectInfo::Type SelectInfo);`
- L121 _private prototype_ `TSharedRef<SWidget> GenerateDeltaTypeMenu();`
- L122 _private prototype_ `FText GetCurrentDeltaTypeLabel() const;`
- L125 _private prototype_ `void UpdateConfigurationSection();` — Rebuilds the configuration section visibility and content.
- L128 _private prototype_ `void SwapActiveExtensionIfChanged();` — Swap the active extension (and its widget) when the active delta type changes.
- L131 _private prototype_ `void UpdateAndRefreshActiveExtension();` — Push the current panel state into the active extension and refresh its lists.
- L134 _private prototype_ `FPCGDeltaViewportContext BuildExtensionContext();` — Builds an FPCGDeltaViewportContext from current panel state.
- L137 _private prototype_ `FPCGDeltaViewportCallbacks CreateForwardingCallbacks();` — Builds the callbacks to be forwarded to the extensions.
- L140 _private member_ `TWeakObjectPtr<UPCGGraph> Graph;` — Graph owning the nodes shown in the panel. Used to discover overridable nodes and observe structural changes.
- L143 _private member_ `TArray<TSharedPtr<FPCGManualEditNodeEntry>> NodeEntries;` — Cached list of nodes eligible for manual editing, rebuilt by RefreshNodeList.
- L146 _private member_ `TMap<TWeakObjectPtr<const UPCGNode>, TSharedPtr<FPCGManualEditNodeConfiguration>> NodeConfigurationMap;` — Per-node transient configuration map.
- L149 _private member_ `TArray<const UScriptStruct*> DeltaTypeOptions;` — Available delta types for the combo box.
- L152 _private member_ `TSharedPtr<SListView<TSharedPtr<FPCGManualEditNodeEntry>>> NodeListView;` — Node list widget for selecting the active editing node.
- L155 _private member_ `TSharedPtr<UE::ToolWidgets::SDraggableBoxOverlay> OverlayWidget;` — Draggable overlay for viewport handles.
- L158 _private member_ `TSharedPtr<SVerticalBox> ConfigurationSection;` — Collapsible section containing node specific configuration widgets.
- L161 _private member_ `TSharedPtr<SVerticalBox> DeltaTypeWidgetSlot;` — Container for the active delta type extension's widget. Swapped when the delta type combo changes.
- L164 _private member_ `IPCGDeltaViewportExtension* ActiveExtension = nullptr;` — The currently active viewport extension (owned by the registry).
- L167 _private member_ `FPCGDeltaViewportCallbacks VisualizerCallbacks;` — Callbacks provided by the visualizer for extensions to invoke.
- L170 _private member_ `TWeakObjectPtr<UPCGComponent> ActivePCGComponent;` — The PCG component currently being edited.
- L173 _private member_ `FPCGSourceDataStorageKey ActiveStorageKey;` — Storage key identifying the delta collection on the active component.
- L176 _private member_ `bool bSelectionActive = false;` — True when the visualizer has an active element selection.
- L179 _private member_ `int32 SelectedElementIndex = INDEX_NONE;` — Index of the selected element within an insertion delta, or INDEX_NONE.
- L182 _private member_ `int32 OriginalElementIndex = INDEX_NONE;` — Index of the selected point in the original source data, or INDEX_NONE.
- L185 _private member_ `FPCGDeltaKey SelectionDeltaKey;` — The delta key of the currently selected element.
- L188 _private member_ `FTransform SelectionTransform = FTransform::Identity;` — World-space transform of the currently selected element.
- L190 _private member_ `EPCGManualEditPanelMode CurrentMode = EPCGManualEditPanelMode::UserControlled;`
- L192 _private member_ `TWeakObjectPtr<const UPCGNode> ActiveNode;`
- L194 _private member_ `const UScriptStruct* ActiveDeltaType = nullptr;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace ToolWidgets` (scope `UE`)
- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPCGManualEditPanelNodeSelected, const UPCGNode* );`
- L23 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPCGManualEditPanelNodeSelected, const UPCGNode* );`
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPCGJumpToNode, const UPCGNode* );`
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPCGJumpToNode, const UPCGNode* );`

### `Plugins/PCG/Source/PCGEditor/Private/Templates/PCGClassTemplate.h` (Private)


#### class `UPCGNativeSettingsClassTemplate`  
`class UPCGNativeSettingsClassTemplate : public UPluginClassTemplate`  
_L13-19_
- reflection: `UCLASS(Hidden)`
- inherits: `UPluginClassTemplate`
- L18 _protected prototype_ `virtual FString GetFilename() const override;`

#### class `UPCGNativeNodeClassTemplate`  
`class UPCGNativeNodeClassTemplate : public UPluginClassTemplate`  
_L22-28_
- reflection: `UCLASS(Hidden)`
- inherits: `UPluginClassTemplate`
- L27 _protected prototype_ `virtual FString GetFilename() const override;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGCodeEditor.h` (Private)


#### class `SPCGCodeEditor`  
`class SPCGCodeEditor : public SCompoundWidget`  
_L19-77_
- inherits: `SCompoundWidget`
- desc: Window for editing source code.
- L22 _public function_ `SLATE_BEGIN_ARGS(SPCGCodeEditor)`
- L25 _public prototype_ `SPCGCodeEditor();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `void SetTextProviderObject(UObject* InProviderObject);`
- L30 _public function_ `const UObject* GetTextProviderObject() const`
- L32 _public prototype_ `void OnDiagnosticsUpdated(const FPCGCompilerDiagnostics& InDiagnostics) const;`
- L34 _public prototype_ `static TSharedRef<SWidget> MakeMenuButton();`
- L37 _private prototype_ `void Refresh();`
- L39 _private prototype_ `SSplitter::ESizeRule GetDeclarationsSectionSizeRule() const;`
- L40 _private prototype_ `SSplitter::ESizeRule GetFunctionsSectionSizeRule() const;`
- L41 _private prototype_ `IPCGCodeEditorTextProvider* GetTextProviderInterface() const;`
- L43 _private prototype_ `FText GetDeclarationsText() const;`
- L44 _private prototype_ `FText GetFunctionsText() const;`
- L45 _private prototype_ `FText GetSourceText() const;`
- L47 _private prototype_ `bool IsReadOnly() const;`
- L49 _private prototype_ `void OnFunctionsTextChanged(const FText& InText);`
- L50 _private prototype_ `void OnSourceTextChanged(const FText& InText);`
- L52 _private prototype_ `void OnFunctionsTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L53 _private prototype_ `void OnSourceTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);`
- L55 _private prototype_ `void OnFunctionsTextChangesApplied() const;`
- L56 _private prototype_ `void OnSourceTextChangesApplied() const;`
- L58 _private prototype_ `void SetFunctionsText() const;`
- L59 _private prototype_ `void SetSourceText() const;`
- L61 _private prototype_ `TSharedRef<SWidget> ConstructNonExpandableHeaderWidget(const SExpandableArea::FArguments& InArgs) const;`
- L63 _private member_ `TSharedRef<FPCGHLSLSyntaxHighlighter> SyntaxHighlighterDeclarations;`
- L64 _private member_ `TSharedRef<FPCGHLSLSyntaxHighlighter> SyntaxHighlighterText;`
- L66 _private member_ `TWeakObjectPtr<UObject> TextProviderObject;`
- L68 _private member_ `TSharedPtr<SExpandableArea> DeclarationsExpandableArea;`
- L69 _private member_ `TSharedPtr<SExpandableArea> FunctionsExpandableArea;`
- L71 _private member_ `TSharedPtr<SPCGCodeEditorTextBox> DeclarationsTextBox;`
- L72 _private member_ `TSharedPtr<SPCGCodeEditorTextBox> FunctionsTextBox;`
- L73 _private member_ `TSharedPtr<SPCGCodeEditorTextBox> SourceTextBox;`
- L75 _private member_ `FText FunctionsText;`
- L76 _private member_ `FText SourceText;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGCodeEditorTextBox.h` (Private)


#### class `FPCGCodeEditorTextBoxCommands`  
`class FPCGCodeEditorTextBoxCommands : public TCommands<FPCGCodeEditorTextBoxCommands>`  
_L17-32_
- inherits: `TCommands<FPCGCodeEditorTextBoxCommands>`
- L21 _public prototype_ `FPCGCodeEditorTextBoxCommands();`
- L24 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> overrides
- L26 _public member_ `TSharedPtr<FUICommandInfo> Search;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> NextOccurrence;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> PreviousOccurrence;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ApplyChanges;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ToggleComment;`

#### class `SPCGCodeEditorTextBox`  
`class SPCGCodeEditorTextBox : public SCompoundWidget`  
_L35-124_
- inherits: `SCompoundWidget`
- desc: Text box for editing code.
- L38 _public prototype_ `SPCGCodeEditorTextBox();`
- L41 _public prototype_ `DECLARE_DELEGATE(FOnTextChangesApplied);`
- L43 _public function_ `SLATE_BEGIN_ARGS(SPCGCodeEditorTextBox)`
- L45 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, SearchText) SLATE_ARGUMENT(TSharedPtr<ITextLayoutMarshaller>, Marshaller) SLATE_ATTRIBUTE(bool, IsReadOnly) SLATE_EVENT(FOnTextChanged, OnTextChanged) SLATE_EVENT(FOnTextCommitted, OnTextCommitted) SLATE_EVENT(FOnTextChangesApplied, OnTextChangesApplied) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The initial text that will appear in the widget.
- L68 _public prototype_ `void Refresh() const;`
- L70 _public prototype_ `void SetTextProviderObject(UObject* InProviderObject);`
- L75 _private prototype_ `virtual FReply OnPreviewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Use Preview Key Down so that the commands related to this tab is given the priority
- L78 _private prototype_ `void RegisterCommands();`
- L80 _private prototype_ `bool HandleEscape();`
- L82 _private prototype_ `void ShowSearchBar();`
- L83 _private prototype_ `bool HideSearchBar();`
- L85 _private prototype_ `void OnTriggerSearch();`
- L86 _private prototype_ `void OnSearchTextChanged(const FText& InTextToSearch);`
- L87 _private prototype_ `void OnSearchTextCommitted(const FText& InTextToSearch, ETextCommit::Type InCommitType);`
- L88 _private prototype_ `TOptional<SSearchBox::FSearchResultData> GetSearchResultData() const;`
- L89 _private prototype_ `void OnSearchResultNavigationButtonClicked(SSearchBox::SearchDirection InDirection);`
- L90 _private prototype_ `void OnGoToNextOccurrence();`
- L91 _private prototype_ `void OnGoToPreviousOccurrence();`
- L93 _private prototype_ `FReply OnTextKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InCharacterEvent) const;`
- L95 _private prototype_ `void OnApplyChanges() const;`
- L97 _private prototype_ `void OnToggleComment() const;`
- L99 _private prototype_ `FReply OnTextKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent) const;`
- L102 _private prototype_ `void HandleAutoIndent() const;` — Figure out if we need to auto-indent.
- L104 _private prototype_ `bool IsReadOnly() const;`
- L105 _private prototype_ `FSlateColor GetBorderBackgroundColor() const;`
- L108 _private member_ `TSharedPtr<SVerticalBox> TabBody;`
- L110 _private member_ `TSharedPtr<SMultiLineEditableText> Text;`
- L112 _private member_ `TSharedPtr<SPCGShaderTextSearchWidget> SearchBar;`
- L113 _private member_ `bool bIsSearchBarHidden = true;`
- L117 _private member_ `TSharedRef<FUICommandList> TopLevelCommandList;` — Top level command list is processed during preview key down such that its commands are given the priority
- L119 _private member_ `TSharedRef<FUICommandList> TextCommandList;`
- L121 _private member_ `FOnTextChangesApplied OnTextChangesAppliedCallback;`
- L123 _private member_ `TWeakObjectPtr<UObject> ShaderTextProviderObject;`

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DELEGATE(FOnTextChangesApplied);`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphActionWidget.h` (Private)


#### class `SPCGGraphActionWidget`  
`class SPCGGraphActionWidget : public SCompoundWidget`  
_L16-114_
- inherits: `SCompoundWidget`
- L18 _private function_ `SLATE_BEGIN_ARGS(SPCGGraphActionWidget)`
- L19 _private function_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, NameWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCreateWidgetForActionData* const InCreateData)`
- L100 _private function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L111 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The action that we want to display with this widget
- L113 _private member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate executed when mouse button goes down

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphAttributeListView.h` (Private)


#### struct `FPCGListViewItem`  
`struct FPCGListViewItem`  
_L51-54_
- L53 _public member_ `int32 Index = INDEX_NONE;`

#### struct `FPCGColumnData`  
`struct FPCGColumnData`  
_L56-61_
- L58 _public member_ `TSharedPtr<const IPCGAttributeAccessor> DataAccessor;`
- L59 _public member_ `TSharedPtr<const IPCGAttributeAccessorKeys> DataKeys;`
- L60 _public member_ `const FPCGMetadataAttributeBase* UnderlyingAttribute = nullptr;`

#### struct `FTextAsNumberIsValid`  
`template <typename T, typename = void> struct FTextAsNumberIsValid : std::false_type`  
_L66-66_
- inherits: `std::false_type`

#### struct `FTextAsNumberIsValid`  
`template <typename T> struct FTextAsNumberIsValid<T, std::void_t<decltype(FText::AsNumber(std::declval<T>()))>> : std::true_type`  
_L70-70_
- inherits: `std::true_type`
- desc: Utility to see if a value type is supported by FText::AsNumber

#### class `FPCGListViewUpdater`  
`class FPCGListViewUpdater : public TSharedFromThis<FPCGListViewUpdater>`  
_L73-106_
- inherits: `TSharedFromThis<FPCGListViewUpdater>`
- desc: Class used for threaded filtering and sorting of list view items
- L76 _public function_ `FPCGListViewUpdater( const TArrayView<const PCGListViewItemPtr>& InListViewItems, const TMap<FName, FPCGColumnData>& InColumnData, const EColumnSortMode::Type InSortMode, const FName InSortingColumn, const TSharedPtr<FTextFilterExpressionEvaluator>& InTextFilter) : ListViewItems(InListViewItems) , ColumnData(InColumnData) , SortMode(InSortMode) , SortingColumn(InSortingColumn) , TextFilter(InTextFilter)`
- L89 _public prototype_ `bool IsCompleted() const;`
- L90 _public prototype_ `void Launch();`
- L92 _public member_ `TArray<PCGListViewItemPtr> ListViewItems;`
- L95 _private prototype_ `void AsyncSort();`
- L96 _private prototype_ `void AsyncFilter();`
- L98 _private member_ `TMap<FName, FPCGColumnData> ColumnData;`
- L100 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::Ascending;`
- L101 _private member_ `FName SortingColumn = NAME_None;`
- L103 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L105 _private member_ `UE::Tasks::FTask UpdateTask;`

#### class `SPCGListViewItemRow`  
`class SPCGListViewItemRow : public SMultiColumnTableRow<PCGListViewItemPtr>`  
_L108-125_
- inherits: `SMultiColumnTableRow<PCGListViewItemPtr>`
- L111 _public function_ `SLATE_BEGIN_ARGS(SPCGListViewItemRow)`
- L112 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SPCGEditorGraphAttributeListView>, AttributeListView) SLATE_ARGUMENT(PCGListViewItemPtr, ListViewItem) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L118 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;`
- L120 _public prototype_ `static void OnSoftObjectPathHyperlinkClicked(const FText& InText);`
- L123 _private member_ `TWeakPtr<SPCGEditorGraphAttributeListView> AttributeListView;`
- L124 _private member_ `PCGListViewItemPtr InternalItem;`

#### class `FPCGPointFilterExpressionContext`  
`class FPCGPointFilterExpressionContext : public ITextFilterExpressionContext`  
_L127-140_
- inherits: `ITextFilterExpressionContext`
- L130 _public prototype_ `explicit FPCGPointFilterExpressionContext(const FPCGListViewItem* InRowItem, const TMap<FName, FPCGColumnData>* InPCGColumnData);`
- L133 _public prototype_ `virtual bool TestBasicStringExpression(const FTextFilterString& InValue, const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L134 _public prototype_ `virtual bool TestComplexExpression(const FName& InKey, const FTextFilterString& InValue, const ETextFilterComparisonOperation InComparisonOperation, const ETextFilterTextComparisonMode InTextComparisonMode) const override;`
- L138 _private member_ `const FPCGListViewItem* RowItem = nullptr;`
- L139 _private member_ `const TMap<FName, FPCGColumnData>* PCGColumnData = nullptr;`

#### class `SPCGEditorGraphAttributeListView`  
`class SPCGEditorGraphAttributeListView : public SCompoundWidget`  
_L142-361_
- inherits: `SCompoundWidget`
- L147 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphAttributeListView)`
- L148 _public prototype_ `SLATE_ARGUMENT(int32, WidgetEntryNumber) SLATE_END_ARGS() virtual ~SPCGEditorGraphAttributeListView();`
- L153 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L155 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L157 _public prototype_ `void RequestRefresh();`
- L158 _public prototype_ `void RequestViewportRefresh();`
- L160 _public prototype_ `UPCGEditorGraphNodeBase* GetNodeBeingInspected() const;`
- L161 _public prototype_ `void SetNodeBeingInspected(UPCGEditorGraphNodeBase* InNode);`
- L163 _public function_ `bool IsLocked() const`
- L164 _public function_ `void SetIsLocked(bool bInIsLocked)`
- L166 _public function_ `TSharedPtr<SPCGEditorViewport> GetViewportWidget() const`
- L167 _public prototype_ `void SetViewportWidget(TSharedPtr<SPCGEditorViewport> InViewportWidget, FName InViewportEditorPanel);`
- L170 _public prototype_ `void ResetViewport();` — Resets/clears the viewport scene.
- L173 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Add UObject references for GC
- L175 _private prototype_ `void OnTick();`
- L176 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRowWidget() const;`
- L179 _private prototype_ `bool ReadbackGPUData() const;` — Read back any GPU data in the inspection data. Returns true when read backs complete.
- L181 _private prototype_ `void OnInspectedStackChanged(const FPCGStack& InPCGStack);`
- L183 _private prototype_ `void ResizeColumnToMaxWidth(FName InColumnId);`
- L184 _private prototype_ `void ResetColumnsWidthToDefault();`
- L185 _private prototype_ `void ExpendAllColumnToMaxWidth();`
- L186 _private prototype_ `void CacheColumnWidthVisibility();`
- L187 _private prototype_ `void RestoreColumnWidthVisibility();`
- L189 _private prototype_ `void RefreshAttributeList();`
- L190 _private prototype_ `void RefreshPinComboBox(bool bKeepSelection, bool& bOutSelectionChanged);`
- L191 _private prototype_ `void RefreshDataComboBox(bool bKeepSelection);`
- L192 _private prototype_ `void RefreshDomainComboBox(bool bKeepSelection);`
- L193 _private prototype_ `void RefreshViewport();`
- L195 _private prototype_ `void LaunchUpdateTask();`
- L211 _private prototype_ `TSharedPtr<FPCGInspectionData> GetInspectionDataPtr(const TSharedPtr<FPinComboBoxItem>& EditorPin) const;`
- L212 _private prototype_ `bool InspectData(const TSharedPtr<FPinComboBoxItem>& EditorPin, TFunctionRef<void(const FPCGDataCollection&)> InspectFunc) const;`
- L213 _private prototype_ `const FPCGDataCollection* GetInspectionData() const;`
- L215 _private prototype_ `FText OnGenerateSelectedPinText() const;`
- L216 _private prototype_ `void OnSelectionChangedPin(TSharedPtr<FPinComboBoxItem> InItem, ESelectInfo::Type InSelectInfo);`
- L217 _private prototype_ `TSharedRef<SWidget> OnGeneratePinWidget(TSharedPtr<FPinComboBoxItem> InItem) const;`
- L219 _private prototype_ `const FSlateBrush* GetFilterBadgeIcon() const;`
- L220 _private prototype_ `TSharedRef<SWidget> OnGenerateFilterMenu();`
- L221 _private prototype_ `TSharedRef<SWidget> OnGenerateAdditionalOperationsMenu();`
- L222 _private prototype_ `TSharedRef<SWidget> OnGenerateDataWidget(TSharedPtr<FString> InItem) const;`
- L223 _private prototype_ `void OnSelectionChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);`
- L224 _private prototype_ `FText OnGenerateSelectedDataText() const;`
- L225 _private prototype_ `FText OnGenerateSelectedDomainText() const;`
- L226 _private prototype_ `int32 GetSelectedDataIndex() const;`
- L227 _private prototype_ `int32 GetSelectedDomainIndex() const;`
- L229 _private prototype_ `void ToggleAllAttributes();`
- L230 _private prototype_ `void ToggleAttribute(FName InAttributeName);`
- L231 _private prototype_ `ECheckBoxState GetAnyAttributeEnabledState() const;`
- L232 _private prototype_ `bool IsAttributeEnabled(FName InAttributeName) const;`
- L234 _private prototype_ `bool BuildDataCollectionForSave(bool bUsePinComboIndex, bool bUseDataComboIndex, FPCGDataCollection* OutData) const;`
- L235 _private prototype_ `void SaveData(bool bUsePinIndex, bool bUseDataIndex);`
- L236 _private prototype_ `bool CanSaveData(bool bUsePinIndex, bool bUseDataIndex) const;`
- L238 _private prototype_ `void OnToggleShowDefaultValue();`
- L239 _private prototype_ `bool IsShowingDefaultValue() const;`
- L241 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(PCGListViewItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L242 _private prototype_ `void OnItemDoubleClicked(PCGListViewItemPtr Item) const;`
- L243 _private prototype_ `TSharedPtr<SWidget> OnItemsContextMenu();`
- L245 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);`
- L246 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName InColumnId) const;`
- L247 _private prototype_ `TSharedRef<SWidget> GenerateColumnMenu(FName ColumnId);`
- L249 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L250 _private prototype_ `void OnFilterTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L252 _private prototype_ `FReply OnListViewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) const;`
- L254 _private prototype_ `void AddColumn(const FPCGTableVisualizerColumnInfo& InColumnInfo);`
- L256 _private prototype_ `void CopySelectionToClipboard() const;`
- L257 _private prototype_ `bool CanCopySelectionToClipboard() const;`
- L260 _private prototype_ `const FSlateBrush* OnGetLockButtonImageResource() const;` — @return the Slate brush to use for the lock image
- L262 _private prototype_ `FReply OnLockClick();`
- L263 _private prototype_ `FReply OnNodeNameClicked();`
- L265 _private prototype_ `FReply OnFocusOnDataClicked() const;`
- L266 _private prototype_ `bool IsFocusOnDataEnabled() const;`
- L268 _private prototype_ `void FocusOnSelection() const;`
- L269 _private prototype_ `bool CanFocusOnSelection() const;`
- L271 _private prototype_ `bool IsViewportOpen() const;`
- L272 _private prototype_ `bool IsOpen() const;`
- L275 _private prototype_ `TWeakInterfacePtr<IPCGGraphExecutionSource> GetExecutionSource() const;` — Returns the current PCG component
- L278 _private member_ `int32 WidgetEntryNumber = 0;` — Index of the entry of this widget, to know which entry to query.
- L281 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;` — Pointer back to the PCG editor that owns us
- L284 _private member_ `TSharedPtr<SPCGEditorViewport> ViewportWidget;` — Data visualization viewport.
- L287 _private member_ `FName ViewportEditorPanel;` — Data visualization viewport editor panel id.
- L290 _private member_ `TWeakObjectPtr<UPCGEditorGraphNodeBase> PCGEditorGraphNode;` — Cached PCGGraphNode being viewed
- L291 _private member_ `bool bPCGEditorGraphNodeChanged = false;`
- L293 _private member_ `TSharedPtr<FUICommandList> ListViewCommands;`
- L295 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;`
- L297 _private member_ `TSharedPtr<SSearchBox> SearchBoxWidget;`
- L298 _private member_ `TSharedPtr<SHeaderRow> ListViewHeader;`
- L299 _private member_ `TSharedPtr<SListView<PCGListViewItemPtr>> ListView;`
- L300 _private member_ `TArray<PCGListViewItemPtr> ListViewItems;`
- L301 _private member_ `TArray<PCGListViewItemPtr> FilteredListViewItems;`
- L303 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FPinComboBoxItem>>> PinComboBox;`
- L304 _private member_ `TArray<TSharedPtr<FPinComboBoxItem>> PinComboBoxItems;`
- L306 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> DataComboBox;`
- L307 _private member_ `TArray<TSharedPtr<FString>> DataComboBoxItems;`
- L310 _private member_ `int32 DataComboBoxItemsSelectedIndex = INDEX_NONE;` — Cached Selected Data ComboBox Item
- L312 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> DomainsComboBox;`
- L313 _private member_ `TArray<TSharedPtr<FString>> DomainsComboBoxItems;`
- L314 _private member_ `TArray<FPCGMetadataDomainID> DomainsComboBoxIds;`
- L317 _private member_ `FPCGMetadataDomainID DomainsComboBoxItemsSelectedDomain = PCGMetadataDomainID::Invalid;` — Cached Selected Domain
- L319 _private member_ `TSharedPtr<STextBlock> NodeNameTextBlock;`
- L320 _private member_ `TSharedPtr<STextBlock> InfoTextBlock;`
- L322 _private member_ `TArray<FName> HiddenAttributes;`
- L324 _private member_ `TMap<FName, FPCGColumnData> PCGColumnData;`
- L327 _private member_ `TMap<FName, float> ColumnsMaxWidthMapping;` — Contains info of the max width to display the full content of the column. Computed only for string types.
- L330 _private typedef_ `using FNodeKeyToColumnWidthVisibilityMap = TTuple<TObjectKey<UPCGEditorGraphNodeBase>, TMap<FName, TTuple<float, bool>>>;` — Ring buffer to keep the latest inspected nodes column width and visibility.
- L331 _private member_ `TRingBuffer<FNodeKeyToColumnWidthVisibilityMap> ColumnWidthVisibilityCache;`
- L333 _private member_ `FText ActiveFilterText;`
- L335 _private member_ `FName SortingColumn = NAME_None;`
- L336 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::Ascending;`
- L337 _private member_ `TFunction<void(const UPCGData*, TArrayView<const int>)> FocusOnDataCallback;`
- L339 _private member_ `bool bNeedsRefresh : 1 = false;`
- L340 _private member_ `bool bViewportNeedsRefresh : 1 = false;`
- L341 _private member_ `bool bTickForced : 1 = false;`
- L343 _private member_ `bool bKeepDataComboBoxSelection = true;`
- L346 _private member_ `bool bIsLocked : 1 = false;` — True if this property view is currently locked (i.e. The objects being observed are not changed automatically due to user selection)
- L348 _private member_ `bool bShowDefaultValue : 1 = false;`
- L350 _private member_ `TSharedPtr<FPCGListViewUpdater> CurrentUpdateTask = nullptr;`
- L356 _private member_ `TObjectPtr<const UPCGData> DataPtr = nullptr;` — In some cases, like when inspecting temporary collapsed point data, there is no owner of the data. Since the ALV needs the data for visualization and double-click functionality, it stores a reference to the data to keep it alive during inspection.
- L359 _private member_ `TArray<TSharedPtr<FStreamableHandle>> LoadHandles;` — Handles for any resources the data needs to load before visualization.
- L360 _private member_ `bool bRefreshLoadHandles : 1 = false;`

#### struct `SPCGEditorGraphAttributeListView::FPinComboBoxItem`  
`struct FPinComboBoxItem`  
_L198-209_
- desc: Only connected input pins are added to combo box, so keep track of the node pin index for each item.
- L200 _public function_ `explicit FPinComboBoxItem(FName InName, int32 InPinIndex, bool bInIsOutputPin) : Name(InName) , PinIndex(InPinIndex) , bIsOutputPin(bInIsOutputPin)`
- L206 _public member_ `FName Name;`
- L207 _public member_ `int32 PinIndex = INDEX_NONE;`
- L208 _public member_ `bool bIsOutputPin = true;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace PCGEditorGraphAttributeListView`
- L47 _variable_ `constexpr float MaxColumnWidth = 200.0f;` (scope `PCGEditorGraphAttributeListView`)
- L48 _variable_ `constexpr int32 MaxNodeColumnWidthCachedItems = 256;` (scope `PCGEditorGraphAttributeListView`)
- L63 _typedef_ `typedef TSharedPtr<FPCGListViewItem> PCGListViewItemPtr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphDataOverrides.h` (Private)


#### enum `EPCGDeltaOrphanStatus`  
`enum class EPCGDeltaOrphanStatus : uint8`  
_L19-24_
- desc: Whether the delta was consumed. Used for override detection.
- L21 _public enumerator_ `Unknown`
- L22 _public enumerator_ `Resolved`
- L23 _public enumerator_ `Orphaned`

#### struct `FPCGDeltaOverrideItem`  
`struct FPCGDeltaOverrideItem`  
_L27-36_
- desc: View model for a single row in the Data Overrides table. Pairs a delta key/struct with its resolved visualizer.
- L29 _public member_ `FPCGDeltaKey DeltaKey;`
- L30 _public member_ `TInstancedStruct<FPCGDeltaBase> DeltaStruct;`
- L31 _public member_ `const IPCGDeltaVisualization* Visualizer = nullptr;`
- L32 _public member_ `FName PinLabel;`
- L33 _public member_ `EPCGDeltaOrphanStatus OrphanStatus = EPCGDeltaOrphanStatus::Unknown;`
- L35 _public member_ `FPCGSourceDataStorageKey StorageKey;` — Data storage key for the collection that owns this delta.

#### class `SPCGDataOverrideRow`  
`class SPCGDataOverrideRow : public SMultiColumnTableRow<FPCGDeltaOverrideItemPtr>`  
_L41-53_
- inherits: `SMultiColumnTableRow<FPCGDeltaOverrideItemPtr>`
- desc: Table row widget. Populated by a registered IPCGDeltaVisualization.
- L44 _public function_ `SLATE_BEGIN_ARGS(SPCGDataOverrideRow)`
- L45 _public prototype_ `SLATE_ARGUMENT(FPCGDeltaOverrideItemPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L49 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnID) override;`
- L52 _private member_ `FPCGDeltaOverrideItemPtr Item;`

#### class `SPCGEditorGraphDataOverridesView`  
`class SPCGEditorGraphDataOverridesView : public SCompoundWidget`  
_L59-102_
- inherits: `SCompoundWidget`
- desc: Data Overrides tab widget. Displays a table of delta overrides (manual edits) for the currently inspected node. Reads delta collections from the execution source's data container using an identical key signature.
- L62 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDataOverridesView)`
- L63 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L68 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L71 _public prototype_ `void SetNodeBeingInspected(UPCGEditorGraphNodeBase* InNode);` — To mirror the ALV
- L72 _public prototype_ `UPCGEditorGraphNodeBase* GetNodeBeingInspected() const;`
- L74 _public prototype_ `void ClearItems();`
- L75 _public prototype_ `void RequestRefresh();`
- L78 _private prototype_ `FReply OnClearNodeOverrides();`
- L79 _private prototype_ `FReply OnClearOrphanedOverrides();`
- L80 _private prototype_ `bool HasOrphanedDeltas() const;`
- L81 _private prototype_ `const FSlateBrush* GetClearOrphanedOverridesBrush() const;`
- L82 _private prototype_ `void OnClearSelectedOverrides(TArray<FPCGDeltaOverrideItemPtr> InItems);`
- L83 _private prototype_ `void RemoveDeltaItems(TArray<FPCGDeltaOverrideItemPtr> InItems, const FText& InTransactionText);`
- L85 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPCGDeltaOverrideItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L86 _private prototype_ `TSharedPtr<SWidget> OnListViewContextMenuOpening();`
- L88 _private prototype_ `void OnInspectedStackChanged(const FPCGStack& InPCGStack);`
- L89 _private prototype_ `void RefreshDataOverrides();`
- L90 _private prototype_ `void RebuildHeaderRow();`
- L92 _private member_ `TWeakObjectPtr<UPCGEditorGraphNodeBase> PCGEditorGraphNode;`
- L93 _private member_ `bool bNeedsRefresh = false;`
- L95 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;`
- L96 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L97 _private member_ `TSharedPtr<SListView<FPCGDeltaOverrideItemPtr>> ListView;`
- L98 _private member_ `TArray<FPCGDeltaOverrideItemPtr> ListViewItems;`
- L101 _private member_ `TArray<FPCGDeltaVisualizerColumnInfo> ActiveColumns;` — Merged column set from all visualizers active in the current view.

#### Free symbols / members of external scopes

- L38 _typedef_ `typedef TSharedPtr<FPCGDeltaOverrideItem> FPCGDeltaOverrideItemPtr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphDebugObjectTree.h` (Private)


#### class `FPCGEditorGraphDebugObjectItem`  
`class FPCGEditorGraphDebugObjectItem : public TSharedFromThis<FPCGEditorGraphDebugObjectItem>`  
_L22-77_
- inherits: `TSharedFromThis<FPCGEditorGraphDebugObjectItem>`
- L25 _public prototype_ `FPCGEditorGraphDebugObjectItem() = default;`
- L27 _public function_ `explicit FPCGEditorGraphDebugObjectItem(bool bInGrayedOut) : bGrayedOut(bInGrayedOut)`
- L32 _public prototype_ `virtual ~FPCGEditorGraphDebugObjectItem() = default;`
- L34 _public prototype_ `void AddChild(TSharedRef<FPCGEditorGraphDebugObjectItem> InChild);`
- L35 _public prototype_ `const TSet<TSharedPtr<FPCGEditorGraphDebugObjectItem>>& GetChildren() const;`
- L36 _public prototype_ `FPCGEditorGraphDebugObjectItemPtr GetParent() const;`
- L37 _public prototype_ `void SortChildren(bool bIsAscending, bool bIsRecursive);`
- L39 _public function_ `bool IsExpanded() const`
- L40 _public function_ `void SetExpanded(bool bInIsExpanded)`
- L42 _public function_ `bool IsGrayedOut() const`
- L43 _public function_ `bool UpdateGrayedOut(bool bInGrayedOut)`
- L50 _public function_ `bool IsSelected() const`
- L51 _public function_ `void SetSelected(bool bInSelected)`
- L54 _public function_ `virtual int32 GetSortPriority() const` — Optional sort priority, if returns INDEX_NONE then sort will fall back to alphabetical.
- L57 _public function_ `virtual bool IsDebuggable() const` — Whether this item represents a currently debuggable object for the current edited graph.
- L59 _public function_ `virtual bool IsDynamic() const` — Whether this item represents a dynamically executed element (as in dynamic subgraph).
- L61 _public function_ `virtual bool IsRootGenerationItem() const` — Whether this is an actor/root item, which doesn't have stack information to its components.
- L63 _public prototype_ `virtual FString GetLabel(bool bForSorting = false) const = 0;`
- L64 _public function_ `virtual const FPCGStack* GetPCGStack() const`
- L65 _public function_ `virtual const UPCGGraph* GetPCGGraph() const`
- L66 _public function_ `virtual bool IsLoopIteration() const`
- L67 _public prototype_ `virtual const FSlateBrush* GetIcon() const;`
- L70 _protected function_ `virtual FPCGStack* GetMutablePCGStack()`
- L72 _protected member_ `TWeakPtr<FPCGEditorGraphDebugObjectItem> Parent;`
- L73 _protected member_ `TSet<TSharedPtr<FPCGEditorGraphDebugObjectItem>> Children;`
- L74 _protected member_ `bool bIsExpanded = false;`
- L75 _protected member_ `bool bGrayedOut = false;`
- L76 _protected member_ `bool bSelected = false;`

#### class `FPCGEditorGraphDebugObjectItem_Actor`  
`class FPCGEditorGraphDebugObjectItem_Actor : public FPCGEditorGraphDebugObjectItem`  
_L79-100_
- inherits: `FPCGEditorGraphDebugObjectItem`
- L82 _public function_ `explicit FPCGEditorGraphDebugObjectItem_Actor(TWeakObjectPtr<AActor> InActor, bool bInHasInspectionData) : FPCGEditorGraphDebugObjectItem(bInHasInspectionData) , Actor(InActor)`
- L89 _public prototype_ `virtual FString GetLabel(bool bForSorting = false) const override;`
- L90 _public function_ `virtual const FPCGStack* GetPCGStack() const override`
- L91 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;`
- L92 _public function_ `virtual bool IsRootGenerationItem() const override`
- L95 _protected function_ `virtual FPCGStack* GetMutablePCGStack() override`
- L97 _protected member_ `TWeakObjectPtr<AActor> Actor = nullptr;`
- L99 _protected member_ `FPCGStack PCGStack;`

#### class `FPCGEditorGraphDebugObjectItem_PCGSource`  
`class FPCGEditorGraphDebugObjectItem_PCGSource : public FPCGEditorGraphDebugObjectItem`  
_L102-136_
- inherits: `FPCGEditorGraphDebugObjectItem`
- L105 _public function_ `explicit FPCGEditorGraphDebugObjectItem_PCGSource( IPCGGraphExecutionSource* InSource, const UPCGGraph* InPCGGraph, const FPCGStack& InPCGStack, bool bInIsDebuggable, bool bInHasInspectionData, bool bInUseHierarchicalLabel) : FPCGEditorGraphDebugObjectItem(bInHasInspectionData) , PCGSource(InSource) , PCGGraph(InPCGGraph) , PCGStack(InPCGStack) , bIsDebuggable(bInIsDebuggable) , bUseHierarchicalLabel(bInUseHierarchicalLabel)`
- L120 _public prototype_ `virtual FString GetLabel(bool bForSorting = false) const override;`
- L121 _public function_ `void SetLabel(const FString& InLabel)`
- L122 _public function_ `virtual const FPCGStack* GetPCGStack() const override`
- L123 _public function_ `virtual bool IsDebuggable() const override`
- L124 _public function_ `virtual const UPCGGraph* GetPCGGraph() const override`
- L127 _protected function_ `virtual FPCGStack* GetMutablePCGStack() override`
- L129 _protected member_ `FPCGSoftGraphExecutionSource PCGSource;`
- L130 _protected member_ `TSoftObjectPtr<const UPCGGraph> PCGGraph;`
- L132 _protected member_ `FPCGStack PCGStack;`
- L133 _protected member_ `bool bIsDebuggable = false;`
- L134 _protected member_ `bool bUseHierarchicalLabel = false;`
- L135 _protected member_ `TOptional<FString> LabelOverride;`

#### enum `EPCGEditorSubgraphNodeType`  
`enum class EPCGEditorSubgraphNodeType : uint8`  
_L138-143_
- L140 _public enumerator_ `StaticSubgraph = 0`
- L141 _public enumerator_ `DynamicSubgraph`
- L142 _public enumerator_ `LoopSubgraph`

#### class `FPCGEditorGraphDebugObjectItem_PCGSubgraph`  
`class FPCGEditorGraphDebugObjectItem_PCGSubgraph : public FPCGEditorGraphDebugObjectItem`  
_L145-179_
- inherits: `FPCGEditorGraphDebugObjectItem`
- L148 _public function_ `explicit FPCGEditorGraphDebugObjectItem_PCGSubgraph( TWeakObjectPtr<const UPCGNode> InPCGNode, TWeakObjectPtr<const UPCGGraph> InPCGGraph, const FPCGStack& InPCGStack, bool bInIsDebuggable, bool bInHasInspectionData, EPCGEditorSubgraphNodeType InSubgraphType) : FPCGEditorGraphDebugObjectItem(bInHasInspectionData) , PCGNode(InPCGNode) , PCGGraph(InPCGGraph) , PCGStack(InPCGStack) , bIsDebuggable(bInIsDebuggable) , SubgraphType(InSubgraphType)`
- L163 _public prototype_ `virtual FString GetLabel(bool bForSorting = false) const override;`
- L164 _public function_ `virtual const FPCGStack* GetPCGStack() const override`
- L165 _public function_ `virtual bool IsDebuggable() const override`
- L166 _public function_ `virtual bool IsDynamic() const override`
- L167 _public function_ `virtual const UPCGGraph* GetPCGGraph() const override`
- L168 _public prototype_ `virtual const FSlateBrush* GetIcon() const override;`
- L171 _protected function_ `virtual FPCGStack* GetMutablePCGStack() override`
- L173 _protected member_ `TWeakObjectPtr<const UPCGNode> PCGNode = nullptr;`
- L174 _protected member_ `TWeakObjectPtr<const UPCGGraph> PCGGraph = nullptr;`
- L176 _protected member_ `FPCGStack PCGStack;`
- L177 _protected member_ `bool bIsDebuggable = false;`
- L178 _protected member_ `EPCGEditorSubgraphNodeType SubgraphType = EPCGEditorSubgraphNodeType::StaticSubgraph;`

#### class `FPCGEditorGraphDebugObjectItem_PCGLoopIndex`  
`class FPCGEditorGraphDebugObjectItem_PCGLoopIndex : public FPCGEditorGraphDebugObjectItem`  
_L181-214_
- inherits: `FPCGEditorGraphDebugObjectItem`
- L184 _public function_ `explicit FPCGEditorGraphDebugObjectItem_PCGLoopIndex( int32 InLoopIndex, TWeakObjectPtr<const UObject> InLoopedPCGGraph, const FPCGStack& InPCGStack, bool bInIsDebuggable, bool bInHasInspectionData) : FPCGEditorGraphDebugObjectItem(bInHasInspectionData) , LoopIndex(InLoopIndex) , LoopedPCGGraph(InLoopedPCGGraph) , PCGStack(InPCGStack) , bIsDebuggable(bInIsDebuggable)`
- L197 _public function_ `virtual int32 GetLoopIndex() const`
- L199 _public prototype_ `virtual FString GetLabel(bool bForSorting = false) const override;`
- L200 _public function_ `virtual const FPCGStack* GetPCGStack() const override`
- L201 _public function_ `virtual int32 GetSortPriority() const override`
- L202 _public function_ `virtual bool IsDebuggable() const override`
- L203 _public function_ `virtual bool IsLoopIteration() const override`
- L204 _public function_ `virtual const UPCGGraph* GetPCGGraph() const override`
- L207 _protected function_ `virtual FPCGStack* GetMutablePCGStack() override`
- L209 _protected member_ `int32 LoopIndex = INDEX_NONE;`
- L210 _protected member_ `TWeakObjectPtr<const UObject> LoopedPCGGraph = nullptr;`
- L212 _protected member_ `FPCGStack PCGStack;`
- L213 _protected member_ `bool bIsDebuggable = false;`

#### class `SPCGEditorGraphDebugObjectItemRow`  
`class SPCGEditorGraphDebugObjectItemRow : public SCompoundWidget`  
_L216-255_
- inherits: `SCompoundWidget`
- L219 _public prototype_ `DECLARE_DELEGATE_OneParam(FPCGDebugObjectItemRowAction, const FPCGEditorGraphDebugObjectItemPtr&);`
- L220 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPCGDebugObjectItemRowPredicate, const FPCGEditorGraphDebugObjectItemPtr&);`
- L222 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDebugObjectItemRow)`
- L224 _public prototype_ `SLATE_EVENT(FPCGDebugObjectItemRowAction, OnDoubleClick) SLATE_EVENT(FPCGDebugObjectItemRowAction, OnJumpTo) SLATE_EVENT(FPCGDebugObjectItemRowPredicate, CanJumpTo) SLATE_EVENT(FPCGDebugObjectItemRowAction, OnFocus) SLATE_EVENT(FPCGDebugObjectItemRowPredicate, CanFocus) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, FPCGEditorGraphDebugObjectItemPtr InItem);`
- L234 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L237 _public prototype_ `FReply FocusClicked() const;`
- L238 _public prototype_ `FReply JumpToClicked() const;`
- L239 _public prototype_ `bool IsJumpToEnabled() const;`
- L240 _public prototype_ `bool IsFocusEnabled() const;`
- L243 _private member_ `FPCGEditorGraphDebugObjectItemPtr Item;`
- L246 _private member_ `FPCGDebugObjectItemRowAction OnDoubleClick;` — Invoked when the user double clicks on the row.
- L248 _private member_ `FPCGDebugObjectItemRowAction OnJumpTo;` — Invoked when the 'Jump To' action is clicked on the row buttons.
- L250 _private member_ `FPCGDebugObjectItemRowAction OnFocus;` — Invoked when the 'Go to node' action is clicked on the row buttons.
- L252 _private member_ `FPCGDebugObjectItemRowPredicate CanJumpTo;` — Controls whether the jump to button will be enabled or not.
- L254 _private member_ `FPCGDebugObjectItemRowPredicate CanFocus;` — Controls whether the 'go to node' button will be enabled or not.

#### class `SPCGEditorGraphDebugObjectTree`  
`class SPCGEditorGraphDebugObjectTree : public SCompoundWidget`  
_L257-412_
- inherits: `SCompoundWidget`
- L260 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDebugObjectTree)`
- L263 _public prototype_ `virtual ~SPCGEditorGraphDebugObjectTree();`
- L265 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L267 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L270 _public prototype_ `void RequestRefresh(bool bForce = false);` — Request a refresh of the widget. If bForce is true, will ask for refresh even if the widget is closed.
- L272 _public prototype_ `void SetNodeBeingInspected(const UPCGNode* InPCGNode);`
- L275 _public prototype_ `bool SetDebugObjectFromStackFromAnotherEditor(const FPCGStack& InStack);` — If the stack matches to an item, Expands the tree view to make that item visible and select it, and return true. Otherwise, return false.
- L278 _public prototype_ `bool GetFirstStackFromSelection(const UPCGNode* InNode, const UPCGGraph* InGraph, FPCGStack& OutStack) const;` — Return the first stack downstream of the currently selected stack with the provided node & graph. Return false if nothing is found.
- L281 _private prototype_ `void OnTick(double InCurrentTime, bool bForceRefresh = false);`
- L283 _private prototype_ `bool IsOpen() const;`
- L285 _private prototype_ `FReply FocusOnDebugObject_OnClicked() const;`
- L286 _private prototype_ `bool IsFocusOnDebugObjectButtonEnabled() const;`
- L288 _private prototype_ `FPCGEditorGraphDebugObjectItemPtr GetFirstDebugObjectFromSelection() const;`
- L289 _private prototype_ `void SetDebugObjectFromSelection_OnClicked();`
- L290 _private function_ `bool IsSetDebugObjectFromSelectionButtonEnabled() const`
- L291 _private prototype_ `void UpdateIsSetDebugObjectFromSelectionEnabled();`
- L293 _private prototype_ `void RefreshTree();`
- L294 _private prototype_ `void SortTreeItems(bool bIsAscending = true, bool bIsRecursive = true);`
- L295 _private prototype_ `void RestoreTreeState();`
- L304 _private function_ `friend bool operator==(const FSourceItemKey& A, const FSourceItemKey& B)`
- L309 _private function_ `friend uint32 GetTypeHash(const FSourceItemKey& Key)`
- L331 _private prototype_ `void AddStacksToTree(const TArray<FPCGStackSharedPtr>& Stacks, FHierarchyContext& InOutContext);`
- L332 _private prototype_ `void AddStacksToTree(const TArray<FPCGStack>& Stacks, FHierarchyContext& InOutContext);`
- L333 _private prototype_ `void AddStackToTree(const FPCGStack& Stack, const UPCGGraph* GraphBeingEdited, FHierarchyContext& InOutContext);`
- L335 _private prototype_ `void OnEditorSelectionChanged(UObject* InObject);`
- L337 _private prototype_ `UPCGGraph* GetFocusedGraph() const;`
- L338 _private prototype_ `UPCGGraph* GetMainGraph() const;`
- L339 _private prototype_ `bool IsMainOrEmbeddedGraph(const UPCGGraph* InGraph) const;`
- L341 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FPCGEditorGraphDebugObjectItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L342 _private prototype_ `void OnGetChildren(FPCGEditorGraphDebugObjectItemPtr InItem, TArray<FPCGEditorGraphDebugObjectItemPtr>& OutChildren) const;`
- L343 _private prototype_ `void OnSelectionChanged(FPCGEditorGraphDebugObjectItemPtr InItem, ESelectInfo::Type InSelectInfo);`
- L344 _private prototype_ `void OnExpansionChanged(FPCGEditorGraphDebugObjectItemPtr InItem, bool bInIsExpanded);`
- L345 _private prototype_ `void OnSetExpansionRecursive(FPCGEditorGraphDebugObjectItemPtr InItem, bool bInExpand) const;`
- L348 _private prototype_ `FPCGEditorGraphDebugObjectItemPtr GetItemFromStack(const FPCGStack& InStack) const;` — Returns the matching item from the AllGraphItems array if any.
- L350 _private prototype_ `void ExpandAndSelectDebugObject(const FPCGEditorGraphDebugObjectItemPtr& InItem);` — Expands the tree view to make an item visible and select it.
- L353 _private prototype_ `void ExpandAndSelectFirstGraphDebugObject(const FPCGEditorGraphDebugObjectItemPtr& InItem);` — Expand the given row and select the next occurrence of the current graph.
- L355 _private prototype_ `TSharedRef<SWidget> OpenFilterMenu();`
- L356 _private prototype_ `const FSlateBrush* GetFilterBadgeIcon() const;`
- L358 _private prototype_ `TSharedPtr<SWidget> OpenContextMenu();`
- L361 _private prototype_ `void ContextMenu_JumpToGraphInTree();` — Jump-to context menu command.
- L362 _private prototype_ `bool ContextMenu_JumpToGraphInTree_CanExecute() const;`
- L364 _private prototype_ `void JumpToGraphInTree(const FPCGEditorGraphDebugObjectItemPtr& Item);`
- L365 _private prototype_ `bool CanJumpToGraphInTree(const FPCGEditorGraphDebugObjectItemPtr& Item) const;`
- L366 _private prototype_ `void FocusOnItem(const FPCGEditorGraphDebugObjectItemPtr& Item);`
- L367 _private prototype_ `bool CanFocusOnItem(const FPCGEditorGraphDebugObjectItemPtr& Item) const;`
- L369 _private prototype_ `void ToggleShowOnlyErrorsAndWarnings();`
- L370 _private prototype_ `ECheckBoxState IsShowingOnlyErrorsAndWarnings() const;`
- L371 _private prototype_ `void ToggleShowDownstream();`
- L372 _private prototype_ `ECheckBoxState IsShowingDownstream() const;`
- L373 _private prototype_ `void ToggleHierarchicalView();`
- L374 _private prototype_ `ECheckBoxState IsUsingHierarchicalView() const;`
- L376 _private member_ `TWeakPtr<FPCGEditor> PCGEditor;`
- L378 _private member_ `TSharedPtr<STreeView<FPCGEditorGraphDebugObjectItemPtr>> DebugObjectTreeView;`
- L379 _private member_ `TArray<FPCGEditorGraphDebugObjectItemPtr> RootItems;`
- L380 _private member_ `TArray<FPCGEditorGraphDebugObjectItemPtr> AllGraphItems;`
- L382 _private member_ `bool bNeedsRefresh = false;`
- L383 _private member_ `bool bShouldSelectStackOnNextRefresh = false;`
- L385 _private member_ `double NextRefreshTime = 0.0;`
- L388 _private member_ `TOptional<bool> IsSetDebugObjectFromSelectionEnabled;` — Latest value for IsSetDebugObjectFromSelectionButtonEnabled
- L391 _private member_ `TSet<FPCGStack> ExpandedStacks;` — Used to retain item expansion state across tree refreshes.
- L394 _private member_ `FPCGStack SelectedStack;` — Used to retain item selection state across tree refreshes.
- L397 _private member_ `TSoftObjectPtr<const UPCGGraph> SelectedGraph = nullptr;` — Used to retain item selection state across tree refreshes if the SelectedStack is invalidated (e.g. through BP reconstruction).
- L398 _private member_ `TSoftObjectPtr<const AActor> SelectedOwner = nullptr;`
- L399 _private member_ `uint32 SelectedGridSize = PCGHiGenGrid::UnboundedGridSize();`
- L400 _private member_ `FIntVector SelectedGridCoord = FIntVector::ZeroValue;`
- L401 _private member_ `FPCGSoftGraphExecutionSource SelectedOriginalSource;`
- L402 _private member_ `TSoftObjectPtr<const UPCGNode> PCGNodeBeingInspected = nullptr;`
- L405 _private member_ `bool bShowOnlyErrorsAndWarnings = false;` — Controls whether only stacks containing errors/warnings should be shown.
- L408 _private member_ `bool bShowDownstream = true;` — Controls whether downstream graphs are going to be shown.
- L411 _private member_ `bool bUseHierarchicalView = false;` — Controls whether sources are grouped by original actor with nested grid hierarchy or shown flat with partition actors.

#### struct `SPCGEditorGraphDebugObjectTree::FSourceItemKey`  
`struct FSourceItemKey`  
_L298-313_
- desc: Key for looking up source items by original owner, grid size, and grid coordinates.
- L300 _public member_ `TObjectKey<UObject> OriginalOwner;`
- L301 _public member_ `uint32 GridSize = 0;`
- L302 _public member_ `FIntVector GridCoords = FIntVector::ZeroValue;`

#### struct `SPCGEditorGraphDebugObjectTree::FHierarchyContext`  
`struct FHierarchyContext`  
_L317-329_
- desc: Accumulated state used while building the tree in RefreshTree/AddStackToTree. Tracks owner items, stack-to-item mappings, and per-actor grid size information needed for hierarchical grid nesting.
- L320 _public member_ `bool bHierarchical = true;` — When true, sources are grouped by original actor with grid nesting. When false, flat view with partition actors.
- L322 _public member_ `TMap<TObjectKey<UObject>, FPCGEditorGraphDebugObjectItemPtr> OwnerItems;` — Maps owner to root tree item. In hierarchical mode, keyed by original owner. In legacy mode, keyed by direct actor (including PAs).
- L324 _public member_ `TMap<const FPCGStack, FPCGEditorGraphDebugObjectItemPtr> StackToItem;` — Maps stack to tree item.
- L326 _public member_ `TMap<FSourceItemKey, FPCGEditorGraphDebugObjectItemPtr> SourceItems;` — Maps (OriginalOwner, GridSize, GridCoords) to source tree item for parent lookup. Hierarchical mode only.
- L328 _public member_ `TMap<TObjectKey<UObject>, TArray<uint32>> OwnerGridSizes;` — Sorted (ascending) grid sizes per original owner. Pre-collected before processing stacks. Hierarchical mode only.

#### Free symbols / members of external scopes

- L20 _typedef_ `typedef TSharedPtr<FPCGEditorGraphDebugObjectItem> FPCGEditorGraphDebugObjectItemPtr;`
- L219 _delegate_ `DECLARE_DELEGATE_OneParam(FPCGDebugObjectItemRowAction, const FPCGEditorGraphDebugObjectItemPtr&);`
- L220 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FPCGDebugObjectItemRowPredicate, const FPCGEditorGraphDebugObjectItemPtr&);`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphDetailsView.h` (Private)


#### class `SPCGEditorGraphDetailsView`  
`class SPCGEditorGraphDetailsView : public SCompoundWidget`  
_L13-66_
- inherits: `SCompoundWidget`
- desc: Thin wrapper on top of a SDetailsView to add some PCG-specific logic around locking and improve layout
- L16 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDetailsView)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L24 _public function_ `void SetEditor(TWeakPtr<FPCGEditor> InEditorPtr)` — Sets the editor associated to this details view, used for interaction from the details view to the editor
- L27 _public function_ `TSharedPtr<IDetailsView> GetDetailsView() const` — Returns the details view under this widget
- L31 _public function_ `bool IsLocked() const` — Returns the lock state of the details view, e.g. whether the selected object should change on a new selection
- L34 _public prototype_ `void SetObject(UObject* InObject, bool bForceRefresh = false);` — Changes the selected objects in the details view. Will unlock automatically.
- L37 _public prototype_ `void SetObjects(const TArray<TWeakObjectPtr<UObject>>& InObjects, bool bForceRefresh = false, bool bOverrideLock = false);` — Changes the selected objects in the details view. Will unlock automatically.
- L40 _public prototype_ `const TArray<TWeakObjectPtr<UObject>>& GetSelectedObjects() const;` — Retrieves the list of objects currently shown in the details view
- L44 _public function_ `void SetIsLocked(bool bInIsLocked)` — Controls lock from the editor
- L48 _protected prototype_ `bool IsReadOnlyProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns whether a property should be readonly (used for instances)
- L50 _protected prototype_ `bool IsVisibleProperty(const FPropertyAndParent& InPropertyAndParent) const;` — Returns whether a property should be visible (used for instance vs. settings properties)
- L52 _protected prototype_ `FReply OnLockButtonClicked();`
- L53 _protected prototype_ `FReply OnNameClicked();`
- L54 _protected prototype_ `const FSlateBrush* GetLockIcon() const;`
- L57 _protected prototype_ `EVisibility GetNameVisibility() const;` — Gets the current visibility state of the name section, which is related to whether the details view is locked.
- L59 _protected prototype_ `FText GetName() const;` — Returns the name to show in the details-view name section, e.g. the settings title most of the time.
- L61 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`
- L62 _protected member_ `bool bIsLocked : 1 = false;`
- L64 _protected member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L65 _protected member_ `TWeakPtr<FPCGEditor> EditorPtr = nullptr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphDeterminism.h` (Private)


#### struct `FTestColumnInfo`  
`struct FTestColumnInfo`  
_L16-28_
- L18 _public function_ `FTestColumnInfo(FName ColumnID, FText ColumnLabel, float Width = 0.f, EHorizontalAlignment HAlign = HAlign_Left) : ColumnID(ColumnID), ColumnLabel(ColumnLabel), Width(Width), HAlign(HAlign)`
- L24 _public member_ `FName ColumnID = TEXT("Unn`
- L25 _public member_ `FText ColumnLabel = NSLOCTEXT("PCGDetermin`
- L26 _public member_ `float Width = 0.f;`
- L27 _public member_ `EHorizontalAlignment HAlign = HAlign_Left;`

#### class `SPCGEditorGraphDeterminismRow`  
`class SPCGEditorGraphDeterminismRow final : public SMultiColumnTableRow<FPCGNodeTestResultPtr>`  
_L30-43_
- inherits: `SMultiColumnTableRow<FPCGNodeTestResultPtr>`
- L32 _private function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDeterminismRow)`
- L33 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const FPCGNodeTestResultPtr& Item, int32 ItemIndex);`
- L39 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — Generates a column, given the column's ID
- L42 _protected member_ `FPCGNodeTestResultPtr CurrentItem;`

#### class `SPCGEditorGraphDeterminismListView`  
`class SPCGEditorGraphDeterminismListView final : public SCompoundWidget`  
_L45-90_
- inherits: `SCompoundWidget`
- L48 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDeterminismListView)`
- L49 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FPCGEditor> InPCGEditor);`
- L54 _public prototype_ `void AddItem(const FPCGNodeTestResultPtr& Item);` — Add an item to the ListView
- L56 _public prototype_ `void ClearItems();` — Clear all items from the ListView
- L58 _public prototype_ `void RefreshItems();` — Refreshes the ListView
- L60 _public prototype_ `void AddColumn(const FTestColumnInfo& ColumnInfo);` — Adds a test column to the ListView
- L62 _public prototype_ `void BuildBaseColumns();` — Builds the default columns for the widget
- L64 _public prototype_ `void AddDetailsColumn();` — Adds the additional details column
- L67 _public prototype_ `bool WidgetIsConstructed() const;` — Validates if the ListView has been constructed
- L71 _private prototype_ `void ClearColumns();` — Clears the columns of the widget
- L73 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(const FPCGNodeTestResultPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;` — Generate the row widget
- L74 _private prototype_ `void OnSortColumnHeader(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L75 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L77 _private member_ `TSharedPtr<SHeaderRow> GeneratedHeaderRow;`
- L79 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;`
- L81 _private member_ `TSharedPtr<SListView<FPCGNodeTestResultPtr>> ListView;`
- L82 _private member_ `TArray<FPCGNodeTestResultPtr> ListViewItems;`
- L85 _private member_ `FName SortingColumn = NAME_None;` — To allow sorting
- L86 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;`
- L88 _private member_ `bool bIsConstructed = false;`
- L89 _private member_ `mutable int32 ItemIndexCounter = -1;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr<FDeterminismTestResult> FPCGNodeTestResultPtr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphDiff.h` (Private)


#### struct `FPCGDiffResultItem`  
`struct FPCGDiffResultItem : public TSharedFromThis<FPCGDiffResultItem>`  
_L26-36_
- inherits: `TSharedFromThis<FPCGDiffResultItem>`
- L28 _public function_ `explicit FPCGDiffResultItem(const FDiffSingleResult& InResult) : Result(InResult)`
- L33 _public prototype_ `TSharedRef<SWidget> GenerateWidget() const;`
- L35 _public member_ `const FDiffSingleResult Result;`

#### class `SPCGEditorGraphDiff`  
`class SPCGEditorGraphDiff : public SCompoundWidget`  
_L39-162_
- inherits: `SCompoundWidget`
- desc: Visual diff between two PCG Graphs.
- L42 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, const UPCGGraph*, const UPCGGraph*);`
- L44 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphDiff)`
- L45 _public prototype_ `SLATE_ARGUMENT(const UPCGGraph*, GraphOld) SLATE_ARGUMENT(const UPCGGraph*, GraphNew) SLATE_ARGUMENT(FRevisionInfo, OldRevision) SLATE_ARGUMENT(FRevisionInfo, NewRevision) SLATE_ARGUMENT(bool, ShowAssetNames) SLATE_EVENT(FOpenInDefaults, OpenInDefaults) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L54 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _public prototype_ `static TSharedPtr<SWindow> CreateDiffWindow( const UPCGGraph* OldGraph, const UPCGGraph* NewGraph, const FRevisionInfo& OldRevision, const FRevisionInfo& NewRevision);` — Create a diff window for two PCG graph interfaces.
- L87 _private typedef_ `using FSharedDiffOnGraph = TSharedPtr<FPCGDiffResultItem>;`
- L88 _private typedef_ `using SDiffListViewType = SListView<FSharedDiffOnGraph>;`
- L91 _private prototype_ `static UPCGEditorGraph* CreateEditorGraphForDiff(UPCGGraph* InPCGGraph);` — Construct a UPCGEditorGraph from a UPCGGraph for diff purposes.
- L102 _private prototype_ `void ShowSettingsForNodes(UEdGraphNode* OldNode, UEdGraphNode* NewNode);` — Update the details splitter to show settings for the given node pair.
- L105 _private prototype_ `void ShowGraphSettingsDetails();` — Point the details splitter at the two UPCGGraph objects with the UserParameters bag hidden.
- L108 _private prototype_ `void ShowGraphParametersDetails();` — Point the details splitter at the two UPCGGraph objects filtered to the UserParameters bag.
- L111 _private prototype_ `bool IsPropertyVisibleInCurrentMode(const FPropertyAndParent& PropertyAndParent) const;` — Visibility filter applied to both details views; driven by CurrentDetailsMode.
- L114 _private prototype_ `void BuildGraphSettingsDiffs();` — Append graph-level UPROPERTY diffs (HiGen, cooking, runtime flags, etc.) to FoundDiffs.
- L117 _private prototype_ `void BuildGraphParameterDiffs();` — Append per-parameter diffs from the two graphs' UserParameters property bags to FoundDiffs.
- L119 _private prototype_ `FReply OnOpenInDefaults();`
- L120 _private prototype_ `TSharedRef<SWidget> GenerateDiffListWidget();`
- L121 _private prototype_ `void BuildDiffSourceArray();`
- L123 _private prototype_ `void NextDiff();`
- L124 _private prototype_ `void PrevDiff();`
- L125 _private prototype_ `int32 GetCurrentDiffIndex() const;`
- L128 _private prototype_ `void OnToggleLockView();` — Toggle handler hooked up to the lock toolbar button.
- L131 _private prototype_ `FSlateIcon GetLockViewImage() const;` — Icon attribute — Lock when locked, Unlock when unlocked.
- L134 _private prototype_ `void ApplyViewLockState();` — Apply the current bLockViews state to both panels' SGraphEditors.
- L136 _private prototype_ `void OnSelectionChanged(FSharedDiffOnGraph Item, ESelectInfo::Type SelectionType);`
- L137 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FSharedDiffOnGraph Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L138 _private prototype_ `SGraphEditor* GetGraphEditorForGraph(UEdGraph* Graph) const;`
- L140 _private member_ `FOpenInDefaults OpenInDefaults;`
- L141 _private member_ `FPCGDiffPanel PanelOld;`
- L142 _private member_ `FPCGDiffPanel PanelNew;`
- L144 _private member_ `TArray<FSharedDiffOnGraph> DiffListSource;`
- L145 _private member_ `TSharedPtr<TArray<FDiffSingleResult>> FoundDiffs;`
- L146 _private member_ `TSharedPtr<FUICommandList> KeyCommands;`
- L147 _private member_ `TSharedPtr<SDiffListViewType> DiffList;`
- L150 _private member_ `TSharedPtr<IDetailsView> OldDetailsView;` — Details diff infrastructure.
- L151 _private member_ `TSharedPtr<IDetailsView> NewDetailsView;`
- L152 _private member_ `TSharedPtr<SDetailsSplitter> DetailsSplitter;`
- L153 _private member_ `TSharedPtr<FAsyncDetailViewDiff> DetailViewDiff;`
- L155 _private member_ `UEdGraphPin* LastPinTarget = nullptr;`
- L156 _private member_ `UEdGraphPin* LastOtherPinTarget = nullptr;`
- L158 _private member_ `EDetailsMode CurrentDetailsMode = EDetailsMode::Node;`
- L161 _private member_ `bool bLockViews = true;` — When true, panning/zooming either graph editor mirrors the other. Default on, matches Blueprint Diff.

#### struct `SPCGEditorGraphDiff::FPCGDiffPanel`  
`struct FPCGDiffPanel`  
_L65-85_
- desc: Panel displaying one side of the diff.
- L67 _public prototype_ `FPCGDiffPanel();`
- L70 _public prototype_ `void GeneratePanel(UEdGraph* Graph, TSharedPtr<TArray<FDiffSingleResult>> DiffResults);` — Generate the graph editor panel with diff highlighting.
- L73 _public prototype_ `FText GetTitle() const;` — Get a title describing this revision.
- L76 _public member_ `const UPCGGraph* Graph = nullptr;` — The PCG graph being displayed.
- L79 _public member_ `TStrongObjectPtr<UPCGEditorGraph> EditorGraph = nullptr;` — The editor graph constructed for diff visualization.
- L81 _public member_ `FRevisionInfo RevisionInfo;`
- L82 _public member_ `TSharedPtr<SBorder> GraphEditorBorder;`
- L83 _public member_ `TWeakPtr<SGraphEditor> GraphEditor;`
- L84 _public member_ `bool bShowAssetName = false;`

#### enum `SPCGEditorGraphDiff::EDetailsMode`  
`enum class EDetailsMode : uint8`  
_L94-99_
- desc: What the details splitter is currently showing — drives the visibility filter applied to OldDetailsView/NewDetailsView.
- L96 _public enumerator_ `Node` — Showing per-node settings UObjects. No filter applied.
- L97 _public enumerator_ `GraphSettings` — Showing UPCGGraph itself, with the UserParameters bag hidden.
- L98 _public enumerator_ `GraphParameters` — Showing UPCGGraph itself, filtered to only the UserParameters bag.

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_DELEGATE_TwoParams(FOpenInDefaults, const UPCGGraph*, const UPCGGraph*);`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphEmbeddedSubgraphsView.h` (Private)


#### class `SPCGEditorGraphEmbeddedSubgraphsView`  
`class SPCGEditorGraphEmbeddedSubgraphsView final : public SCompoundWidget`  
_L24-49_
- inherits: `SCompoundWidget`
- desc: Displays a PCGGraph's Local graphs.
- L27 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphEmbeddedSubgraphsView)`
- L28 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FPCGEditor>& InPCGEditor);`
- L31 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L32 _public function_ `void RequestRefresh()`
- L35 _private prototype_ `void OnFilterTextChanged(const FText& InText);`
- L36 _private prototype_ `FReply NewEmbeddedSubgraphClicked();`
- L37 _private prototype_ `TSharedRef<ITableRow> GenerateEmbeddedSubgraphRow(TSharedPtr<PCGEditorGraphEmbeddedSubgraphsView::FEmbeddedSubgraphItem> InItem, const TSharedRef<STableViewBase>& InOwner);`
- L38 _private prototype_ `void OnEmbeddedSubgraphItemDoubleClick(TSharedPtr<PCGEditorGraphEmbeddedSubgraphsView::FEmbeddedSubgraphItem> InItem);`
- L39 _private prototype_ `FReply OnEmbeddedSubgraphItemKeyDownHandler(const FGeometry&, const FKeyEvent& InKeyEvent) const;`
- L40 _private prototype_ `UPCGGraph* GetEditorGraph() const;`
- L41 _private prototype_ `void RefreshEmbeddedSubgraphsList();`
- L42 _private prototype_ `TSharedPtr<SWidget> OpenContextMenu();`
- L44 _private member_ `TArray<TSharedPtr<PCGEditorGraphEmbeddedSubgraphsView::FEmbeddedSubgraphItem>> Items;`
- L45 _private member_ `TSharedPtr<SListView<TSharedPtr<PCGEditorGraphEmbeddedSubgraphsView::FEmbeddedSubgraphItem>>> ListView;`
- L46 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;`
- L47 _private member_ `bool bRefreshRequested = false;`
- L48 _private member_ `FText FilterText;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace PCGEditorGraphEmbeddedSubgraphsView`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphFind.h` (Private)


#### struct `FPCGEditorGraphFindResult`  
`struct FPCGEditorGraphFindResult`  
_L21-76_
- L24 _public prototype_ `FPCGEditorGraphFindResult(const FString& InValue);` — Create a root (or only text) result
- L27 _public prototype_ `FPCGEditorGraphFindResult(const FText& InValue);` — Create a root (or only text) result
- L30 _public prototype_ `FPCGEditorGraphFindResult(const FString& InValue, const TSharedPtr<FPCGEditorGraphFindResult>& InParent, UEdGraphNode* InNode);` — Create a listing for a node result
- L33 _public prototype_ `FPCGEditorGraphFindResult(const FString& InValue, const TSharedPtr<FPCGEditorGraphFindResult>& InParent, UEdGraphPin* InPin);` — Create a listing for a pin result
- L36 _public prototype_ `FReply OnClick(TWeakPtr<FPCGEditor> InPCGEditorPtr);` — Called when user clicks on the search item
- L39 _public prototype_ `FReply OnDoubleClick(TWeakPtr<FPCGEditor> InPCGEditorPtr);` — Called when user double-clicks on the search item
- L42 _public prototype_ `FText GetToolTip() const;` — Get ToolTip for this search result
- L45 _public prototype_ `FText GetCategory() const;` — Get Category for this search result
- L48 _public prototype_ `FText GetComment() const;` — Get Comment for this search result
- L51 _public prototype_ `TSharedRef<SWidget> CreateIcon() const;` — Create an icon to represent the result
- L54 _public member_ `UPCGEditorGraph* ParentGraph = nullptr;` — ParentGraph if not current
- L57 _public member_ `TWeakPtr<FPCGEditorGraphFindResult> Parent;` — Search result parent
- L60 _public member_ `TArray<TSharedPtr<FPCGEditorGraphFindResult>> Children;` — Any children listed under this category
- L63 _public member_ `FString Value;` — The string value for this result
- L66 _public member_ `TWeakObjectPtr<UEdGraphNode> GraphNode;` — The graph node that this search result refers to
- L69 _public member_ `TWeakObjectPtr<UEdGraphNode> RootGraphNode;` — The graph node that`s in the current editor graph upstream.
- L72 _public member_ `FEdGraphPinReference Pin;` — The pin that this search result refers to
- L75 _public member_ `bool bIsMatch = false;` — Whether this result contains a found token or not.

#### enum `EPCGGraphFindMode`  
`enum class EPCGGraphFindMode : uint8`  
_L78-83_
- L80 _public enumerator_ `ShowMinimumTree`
- L81 _public enumerator_ `ShowFullTree`
- L82 _public enumerator_ `ShowFlatList`

#### class `SPCGEditorGraphFind`  
`class SPCGEditorGraphFind : public SCompoundWidget`  
_L85-169_
- inherits: `SCompoundWidget`
- L88 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphFind)`
- L91 _public prototype_ `~SPCGEditorGraphFind();`
- L92 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L95 _public prototype_ `void FocusForUse();` — Focuses this widget's search box
- L98 _private typedef_ `typedef TSharedPtr<FPCGEditorGraphFindResult> FPCGEditorGraphFindResultPtr;`
- L99 _private typedef_ `typedef STreeView<FPCGEditorGraphFindResultPtr> STreeViewType;`
- L102 _private prototype_ `void OnSearchTextChanged(const FText& InText);` — Called when user changes the text they are searching for
- L105 _private prototype_ `void OnSearchTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Called when user changes commits text to the search box
- L108 _private prototype_ `void OnInspectedStackChanged(const FPCGStack& InPCGStack);` — Called when the debug object selected changes, which should trigger a new search
- L111 _private prototype_ `void OnGetChildren(FPCGEditorGraphFindResultPtr InItem, TArray<FPCGEditorGraphFindResultPtr>& OutChildren);` — Get the children of a row
- L114 _private prototype_ `void OnTreeSelectionChanged(FPCGEditorGraphFindResultPtr Item, ESelectInfo::Type);` — Called when user clicks on a new result
- L117 _private prototype_ `void OnTreeDoubleClick(FPCGEditorGraphFindResultPtr InItem);` — Called when an element is double-clicked
- L120 _private prototype_ `FReply OnTreeViewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) const;` — Called when keys are entered when in the tree selection
- L123 _private prototype_ `TSharedRef<SWidget> OnFindFilterMenu();` — Called when the user clicks on the filter icon
- L126 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FPCGEditorGraphFindResultPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — Called when a new row is being generated
- L129 _private prototype_ `void InitiateSearch();` — Begins the search based on the SearchValue
- L132 _private prototype_ `void MatchTokens(const TArray<FString>& InTokens);` — Find any results that contain all of the tokens
- L135 _private prototype_ `void MatchTokensInternal(const TArray<FString>& InTokens, UPCGEditorGraph* PCGEditorGraph, TFunctionRef<FPCGEditorGraphFindResultPtr()> GetParentFunc) const;` — Recursive internal implementation of the MatchTokens
- L138 _private prototype_ `static bool StringMatchesSearchTokens(const TArray<FString>& InTokens, const FString& InComparisonString);` — Determines if a string matches the search tokens
- L141 _private prototype_ `void SetFindMode(EPCGGraphFindMode InFindMode);` — Called when the find mode is changed
- L144 _private prototype_ `bool IsCurrentFindMode(EPCGGraphFindMode InFindMode) const;` — Returns true if the current find mode is the same as the one provided
- L147 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;` — Pointer back to the PCG editor that owns us
- L150 _private member_ `TSharedPtr<STreeViewType> TreeView;` — The tree view displays the results
- L153 _private member_ `TSharedPtr<SSearchBox> SearchTextField;` — The search text box
- L156 _private member_ `TArray<FPCGEditorGraphFindResultPtr> ItemsFound;` — This buffer stores the currently displayed results
- L159 _private member_ `FText HighlightText;` — The string to highlight in the results
- L162 _private member_ `FString SearchValue;` — The string to search for
- L165 _private member_ `EPCGGraphFindMode FindMode = EPCGGraphFindMode::ShowMinimumTree;` — Controls the way find results are presented.
- L168 _private member_ `bool bShowPinResults = false;` — Controls whether pin names are show in the find results.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ESelectInfo`
- L12 _namespace_ `namespace ETextCommit`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphLogView.h` (Private)


#### struct `FPCGLogListViewItem`  
`struct FPCGLogListViewItem`  
_L24-35_
- L26 _public member_ `const UPCGNode* PCGNode = nullptr;`
- L27 _public member_ `const UPCGEditorGraphNode* EditorNode = nullptr;`
- L29 _public member_ `int32 Order = 0;`
- L30 _public member_ `FName NodeName;`
- L31 _public member_ `FName Namespace;`
- L32 _public member_ `FString Message;`
- L34 _public member_ `ELogVerbosity::Type Verbosity = ELogVerbosity::NoLogging;`

#### class `SPCGLogListViewItemRow`  
`class SPCGLogListViewItemRow : public SMultiColumnTableRow<PCGLogListViewItemPtr>`  
_L39-51_
- inherits: `SMultiColumnTableRow<PCGLogListViewItemPtr>`
- L42 _public function_ `SLATE_BEGIN_ARGS(SPCGLogListViewItemRow)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const PCGLogListViewItemPtr& Item);`
- L47 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;`
- L50 _protected member_ `PCGLogListViewItemPtr InternalItem;`

#### class `SPCGEditorGraphLogView`  
`class SPCGEditorGraphLogView : public SCompoundWidget`  
_L53-97_
- inherits: `SCompoundWidget`
- L56 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphLogView)`
- L59 _public prototype_ `~SPCGEditorGraphLogView();`
- L61 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L62 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L63 _public function_ `void RequestRefresh()`
- L66 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRowWidget();`
- L67 _private prototype_ `void CreateAndAddItem(const UPCGEditorGraphNode* InPCGEditorNode, const UPCGNode* InPCGNode, const FName& InName);`
- L69 _private prototype_ `void OnDebugStackChanged(const FPCGStack& InPCGStack);`
- L72 _private prototype_ `FReply Refresh();` — Callbacks
- L73 _private prototype_ `FReply Clear();`
- L74 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(PCGLogListViewItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L75 _private prototype_ `void OnItemDoubleClicked(PCGLogListViewItemPtr Item);`
- L76 _private prototype_ `void OnSortColumnHeader(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L77 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L80 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;` — Pointer back to the PCG editor that owns us
- L83 _private member_ `UPCGEditorGraph* PCGEditorGraph = nullptr;` — Cached PCGGraph being viewed
- L86 _private prototype_ `IPCGGraphExecutionSource* GetExecutionSource() const;` — Cached PCG Execution source being viewed
- L88 _private member_ `TSharedPtr<SHeaderRow> ListViewHeader;`
- L89 _private member_ `TSharedPtr<SListView<PCGLogListViewItemPtr>> ListView;`
- L90 _private member_ `TArray<PCGLogListViewItemPtr> ListViewItems;`
- L92 _private member_ `bool bNeedsRefresh : 1 = false;`
- L95 _private member_ `FName SortingColumn = PCGEditorGraphLogView::NAME_Order;` — To allow sorting
- L96 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::Ascending;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace PCGEditorGraphLogView`
- L21 _externvar_ `extern const FName NAME_Order;` (scope `PCGEditorGraphLogView`) — Names of the columns in the attribute list
- L37 _typedef_ `typedef TSharedPtr<FPCGLogListViewItem> PCGLogListViewItemPtr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphNodePalette.h` (Private)


#### class `SPCGEditorGraphNodePaletteItem`  
`class SPCGEditorGraphNodePaletteItem : public SGraphPaletteItem`  
_L11-23_
- inherits: `SGraphPaletteItem`
- L14 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphNodePaletteItem)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData);`
- L21 _protected prototype_ `virtual FText GetItemTooltip() const override;`

#### class `SPCGEditorGraphNodePalette`  
`class SPCGEditorGraphNodePalette : public SGraphPalette`  
_L26-58_
- inherits: `SGraphPalette`
- L29 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphNodePalette)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L33 _public prototype_ `virtual ~SPCGEditorGraphNodePalette();`
- L35 _public prototype_ `void RequestRefresh();`
- L39 _protected prototype_ `virtual TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData) override;`
- L40 _protected prototype_ `virtual FReply OnActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent) override;`
- L41 _protected prototype_ `virtual void CollectAllActions(FGraphActionListBuilderBase& OutAllActions) override;`
- L45 _protected prototype_ `void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L49 _private prototype_ `void OnAssetChanged(const FAssetData& InAssetData);`
- L50 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& InNewAssetName);`
- L51 _private prototype_ `void OnTypeSelectionChanged(int32, ESelectInfo::Type SelectInfo);`
- L53 _private prototype_ `int32 GetTypeValue() const;`
- L55 _private member_ `TWeakPtr<FPCGEditor> PCGEditor;`
- L56 _private member_ `EPCGElementType ElementType = EPCGElementType::All;`
- L57 _private member_ `bool bNeedsRefresh = false;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphParamsView.h` (Private)


#### class `SPCGEditorGraphUserParametersView`  
`class SPCGEditorGraphUserParametersView final : public SCompoundWidget`  
_L15-25_
- inherits: `SCompoundWidget`
- desc: Displays a PCGGraph's User Parameters details view.
- L18 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphUserParametersView)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<FPCGEditor>& InPCGEditor);`
- L22 _public prototype_ `void SetGraph(UPCGGraph* InGraph);`
- L24 _private member_ `TSharedPtr<IDetailsView> DetailsView;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphProfilingView.h` (Private)


#### struct `FPCGProfilingListViewItem`  
`struct FPCGProfilingListViewItem`  
_L19-32_
- L21 _public prototype_ `FText GetTextForColumn(FName ColumnId, bool bNoGrouping) const;`
- L23 _public member_ `const UPCGNode* PCGNode = nullptr;`
- L24 _public member_ `const UPCGEditorGraphNode* EditorNode = nullptr;`
- L26 _public member_ `FString Name;`
- L28 _public member_ `PCGUtils::FCallTime CallTime;`
- L29 _public member_ `int32 NumberOfTasks = 0;`
- L31 _public member_ `bool bHasCPUTimingData = false;`

#### struct `FPCGProfilingTotalData`  
`struct FPCGProfilingTotalData`  
_L34-58_
- L36 _public member_ `bool bShowTotalTime = true;`
- L37 _public member_ `bool bShowTotalWallTime = true;`
- L38 _public member_ `bool bShowTotalCPUDataSize = true;`
- L39 _public member_ `bool bShowTotalGPUDataSize = true;`
- L40 _public member_ `bool bShowTotalTasks = true;`
- L42 _public member_ `int32 TotalNumTasks = 0;`
- L43 _public member_ `double TotalTime = 0.0;`
- L44 _public member_ `double TotalWallTime = 0.0;`
- L45 _public member_ `double TotalCPUDataSizeInMB = 0.0;`
- L46 _public member_ `double TotalGPUDataSizeInMB = 0.0;`
- L48 _public prototype_ `FText GetTotalTimeLabel() const;`
- L49 _public prototype_ `FText GetTotalWallTimeLabel() const;`
- L50 _public prototype_ `FText GetTotalCPUDataSizeInMBLabel() const;`
- L51 _public prototype_ `FText GetTotalGPUDataSizeInMBLabel() const;`
- L52 _public prototype_ `FText GetTotalNumTasksLabel() const;`
- L54 _public prototype_ `TSharedRef<SWidget> MakeOptionsWidget();`
- L55 _public prototype_ `TSharedRef<SWidget> OnOptionsMenu();`
- L57 _public prototype_ `void Reset();`

#### class `SPCGProfilingListViewItemRow`  
`class SPCGProfilingListViewItemRow : public SMultiColumnTableRow<PCGProfilingListViewItemPtr>`  
_L62-74_
- inherits: `SMultiColumnTableRow<PCGProfilingListViewItemPtr>`
- L65 _public function_ `SLATE_BEGIN_ARGS(SPCGProfilingListViewItemRow)`
- L66 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const PCGProfilingListViewItemPtr& Item);`
- L70 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;`
- L73 _protected member_ `PCGProfilingListViewItemPtr InternalItem;`

#### class `SPCGEditorGraphProfilingView`  
`class SPCGEditorGraphProfilingView : public SCompoundWidget`  
_L76-143_
- inherits: `SCompoundWidget`
- L79 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorGraphProfilingView)`
- L82 _public prototype_ `~SPCGEditorGraphProfilingView();`
- L84 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FPCGEditor> InPCGEditor);`
- L85 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L88 _private prototype_ `TSharedRef<SHeaderRow> CreateHeaderRowWidget();`
- L90 _private function_ `int32 GetSubgraphExpandDepth() const`
- L91 _private prototype_ `void OnSubgraphExpandDepthChanged(int32 NewValue);`
- L93 _private prototype_ `void OnDebugStackChanged(const FPCGStack& InPCGStack);`
- L96 _private prototype_ `void RequestRefresh();` — Callbacks
- L97 _private prototype_ `FReply Refresh();`
- L98 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(PCGProfilingListViewItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L99 _private prototype_ `void OnItemDoubleClicked(PCGProfilingListViewItemPtr Item);`
- L100 _private prototype_ `void OnSortColumnHeader(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type NewSortMode);`
- L101 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;`
- L103 _private prototype_ `FReply OnListViewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) const;`
- L104 _private prototype_ `void CopySelectionToClipboard() const;`
- L105 _private prototype_ `bool CanCopySelectionToClipboard() const;`
- L108 _private prototype_ `void OnSearchTextChanged(const FText& InText);` — Called when user changes the text they are searching for
- L111 _private prototype_ `void OnSearchTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Called when user changes commits text to the search box
- L114 _private prototype_ `IPCGGraphExecutionSource* GetExecutionSource() const;` — Returns the current PCG execution source
- L117 _private member_ `TWeakPtr<FPCGEditor> PCGEditorPtr;` — Pointer back to the PCG editor that owns us
- L120 _private member_ `UPCGEditorGraph* PCGEditorGraph = nullptr;` — Cached PCGGraph being viewed
- L123 _private member_ `FPCGStack PCGStack;` — Current stack being viewed
- L125 _private member_ `TSharedPtr<SHeaderRow> ListViewHeader;`
- L126 _private member_ `TSharedPtr<SListView<PCGProfilingListViewItemPtr>> ListView;`
- L127 _private member_ `TArray<PCGProfilingListViewItemPtr> ListViewItems;`
- L128 _private member_ `TSharedPtr<FUICommandList> ListViewCommands;`
- L131 _private member_ `FName SortingColumn = NAME_None;` — To allow sorting
- L132 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::Type::None;`
- L134 _private member_ `FPCGProfilingTotalData ProfilingTotalData;`
- L136 _private member_ `bool bNeedsRefresh = false;`
- L139 _private member_ `int32 ExpandSubgraphDepth = 0;` — Currently depth of entry exposition - if 0, only the nodes in the currently debugged graph will be shown.
- L142 _private member_ `FString SearchValue;` — The string to search for

#### Free symbols / members of external scopes

- L60 _typedef_ `typedef TSharedPtr<FPCGProfilingListViewItem> PCGProfilingListViewItemPtr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGEditorGraphTitleBar.h` (Private)


#### class `SPCGGraphEditorTitleBar`  
`class SPCGGraphEditorTitleBar : public SCompoundWidget`  
_L12-46_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SPCGGraphEditorTitleBar) : _Graph(nullptr) , _Editor()`
- L20 _public prototype_ `SLATE_ARGUMENT(UPCGEditorGraph*, Graph) SLATE_ARGUMENT(TWeakPtr<FPCGEditor>, Editor) SLATE_ARGUMENT(TSharedPtr<SWidget>, HistoryNavigationWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _protected prototype_ `void RebuildBreadcrumbTrail();`
- L35 _protected prototype_ `void OnBreadcrumbClicked(const FBreadcrumbItem& Crumb);`
- L37 _protected prototype_ `static FText GetTitleForOneCrumb(TWeakObjectPtr<const UPCGEditorGraph> InWeakEditorGraph);`
- L40 _protected member_ `TWeakObjectPtr<UPCGEditorGraph> EditorGraph = nullptr;` — Edited graph
- L42 _protected member_ `TSharedPtr<SScrollBox> BreadcrumbTrailScrollBox;`
- L45 _protected member_ `TSharedPtr<SBreadcrumbTrail<FBreadcrumbItem>> BreadcrumbTrail;` — Breadcrumb trail widget

#### struct `SPCGGraphEditorTitleBar::FBreadcrumbItem`  
`struct FBreadcrumbItem`  
_L29-32_
- L31 _public member_ `TWeakObjectPtr<const UPCGEditorGraph> EditorGraph;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGMetadataAttributeGenericViewer.h` (Private)


#### class `FPCGMetadataAttributeGenericViewerDetailCustomization`  
`class FPCGMetadataAttributeGenericViewerDetailCustomization final : public IDetailCustomization`  
_L25-35_
- inherits: `IDetailCustomization`
- desc: Header customization for when multiple objects are displayed in the details panel.
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<SPCGMetadataAttributeGenericViewer> Viewer);`
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L33 _private prototype_ `FPCGMetadataAttributeGenericViewerDetailCustomization(TSharedPtr<SPCGMetadataAttributeGenericViewer> Viewer);`
- L34 _private member_ `TWeakPtr<SPCGMetadataAttributeGenericViewer> WeakViewer;`

#### class `SPCGMetadataAttributeGenericViewer`  
`class SPCGMetadataAttributeGenericViewer : public SCompoundWidget`  
_L38-69_
- inherits: `SCompoundWidget`
- desc: Thin wrapper on top of a SDetailsView to add some PCG-specific logic around locking and improve layout
- L41 _public function_ `SLATE_BEGIN_ARGS(SPCGMetadataAttributeGenericViewer)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L49 _public function_ `void SetEditor(TWeakPtr<FPCGEditor> InEditorPtr)` — Sets the editor associated to this details view, used for interaction from the details view to the editor
- L52 _public function_ `TSharedPtr<IDetailsView> GetDetailsView() const` — Returns the details view under this widget
- L54 _public prototype_ `void Refresh();`
- L57 _public prototype_ `void Setup(TWeakObjectPtr<const UPCGData> InData, const FPCGMetadataAttributeBase* InAttr, PCGMetadataEntryKey InEntryKey);` — Controls lock from the editor
- L61 _protected member_ `TSharedPtr<IDetailsView> DetailsView;`
- L63 _protected member_ `FInstancedPropertyBag TempStruct;`
- L65 _protected member_ `TWeakObjectPtr<const UPCGData> Data;`
- L66 _protected member_ `const FPCGMetadataAttributeBase* Attr;`
- L67 _protected member_ `PCGMetadataEntryKey EntryKey;`
- L68 _protected member_ `TWeakPtr<FPCGEditor> EditorPtr = nullptr;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGShaderTextSearchWidget.h` (Private)


#### class `SPCGShaderTextSearchWidget`  
`class SPCGShaderTextSearchWidget : public SCompoundWidget`  
_L16-50_
- inherits: `SCompoundWidget`
- desc: Search text field.
- L19 _public prototype_ `SPCGShaderTextSearchWidget();`
- L22 _public function_ `SLATE_BEGIN_ARGS(SPCGShaderTextSearchWidget)`
- L24 _public prototype_ `SLATE_EVENT(FOnTextChanged, OnTextChanged ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_EVENT(SSearchBox::FOnSearch, OnResultNavigationButtonClicked ) SLATE_ATTRIBUTE(TOptional<SSearchBox::FSearchResultData>, SearchResultData ) SLATE_EVENT(FOnKeyDown, OnKeyDownHandler) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Invoked whenever the text changes
- L41 _public prototype_ `void FocusSearchBox() const;`
- L43 _public prototype_ `void TriggerSearch(const FText& InNewSearchText) const;`
- L45 _public prototype_ `void ClearSearchText();`
- L48 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L49 _private member_ `FText LastSearchedText;`

### `Plugins/PCG/Source/PCGEditor/Private/Widgets/SPCGTextureSliceSelector.h` (Private)


#### class `SPCGTextureSliceSelector`  
`class SPCGTextureSliceSelector : public SCompoundWidget`  
_L17-43_
- inherits: `SCompoundWidget`
- desc: Toolbar widget for the PCG data viewport that lets the user pick which slice of a UPCGTexture2DArrayData is displayed.
- L20 _public function_ `SLATE_BEGIN_ARGS(SPCGTextureSliceSelector) : _ViewportClient(nullptr)`
- L23 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<const UPCGTexture2DArrayData>, WeakData) SLATE_ARGUMENT(TWeakObjectPtr<UMaterialInstanceDynamic>, WeakMaterial) SLATE_ARGUMENT(FEditorViewportClient*, ViewportClient) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `void OnSliceValueChanged(int32 NewSlice);`
- L32 _private prototype_ `void ApplySlice(int32 NewSlice);`
- L34 _private member_ `TWeakObjectPtr<const UPCGTexture2DArrayData> WeakData;`
- L35 _private member_ `TWeakObjectPtr<UMaterialInstanceDynamic> WeakMaterial;`
- L36 _private member_ `FEditorViewportClient* ViewportClient = nullptr;`
- L37 _private member_ `EPCGTextureResourceType ResourceType = EPCGTextureResourceType::TextureObject;`
- L38 _private member_ `int32 ArraySize = 1;`
- L39 _private member_ `int32 CurrentSlice = 0;`
- L42 _private member_ `TStrongObjectPtr<UPCGVisualizationTexture2D> CurrentWrapper;` — Holds the currently-displayed wrapper texture alive for the ExportedTexture path. Replaced each time the slice changes.

### `Plugins/PCG/Source/PCGEditor/Private/WorldPartitionBuilder/PCGBuilderSettings.h` (Private)


#### class `UPCGBuilderSettings`  
`class UPCGBuilderSettings : public UObject`  
_L14-72_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UObject`
- L19 _public prototype_ `UPCGBuilderSettings();`
- L23 _public member_ `TArray<TSoftObjectPtr<UPCGGraphInterface>> Graphs;` — `UPROPERTY(EditAnywhere, Category = Build)` — Graphs that will be generated in the specified order. When left empty, all Graphs will get generated in the order they are discovered.
- L27 _public member_ `TArray<EPCGEditorDirtyMode> EditingModes;` — `UPROPERTY(EditAnywhere, Category = Build)` — Include components which have the following editing mode.
- L31 _public member_ `TArray<FString> FilterByActorNames;` — `UPROPERTY(EditAnywhere, Category = Filter)` — Filter generated components by owner actor name.
- L35 _public member_ `bool bLoadEditorOnlyDataLayers = true;` — `UPROPERTY(EditAnywhere, Category = DataLayers)` — Will load editor only data layers without having to specify them as included
- L39 _public member_ `bool bLoadActivatedRuntimeDataLayers = true;` — `UPROPERTY(EditAnywhere, Category = DataLayers)` — Will load runtime data layers that are default activated without having to specify them as included
- L43 _public member_ `TArray<TObjectPtr<UDataLayerAsset>> IncludedDataLayers;` — `UPROPERTY(EditAnywhere, Category = DataLayers)` — Data layers that need to be loaded when running builder.
- L47 _public member_ `TArray<TObjectPtr<UDataLayerAsset>> ExcludedDataLayers;` — `UPROPERTY(EditAnywhere, Category = DataLayers)` — Data layers that need to be unloaded when running builder.
- L51 _public member_ `bool bIterativeCellLoading = false;` — `UPROPERTY(EditAnywhere, Category = Advanced)` — Run builder iteratively loading cell regions instead of the whole map at once. Useful for large maps.
- L55 _public member_ `int32 IterativeCellSize = 25600;` — `UPROPERTY(EditAnywhere, Category = Advanced, meta = (EditCondition=bIterativeCellLoading, EditConditionHides, ClampMin=12800, UIMin=12800))` — Cell size when using iterative cell loading.
- L59 _public member_ `bool bIgnoreGenerationErrors = false;` — `UPROPERTY(EditAnywhere, Category = Advanced)` — Submit dirty files even if errors occurred during generation.
- L63 _public member_ `bool bOneComponentAtATime = false;` — `UPROPERTY(EditAnywhere, Category = Advanced, meta = (DisplayName = "One Component at a Time"))` — Call generate on each component and wait until completion and any async processes before generating the next.
- L67 _public member_ `bool bRevertUnchangedActors = false;` — `UPROPERTY(EditAnywhere, Category = Experimental)` — Experimental feature that will try and revert PCG Component Actors which haven't changed from their previous generation.
- L71 _public member_ `TArray<FString> OutputsToIgnoreForRevert;` — `UPROPERTY(EditAnywhere, Category = Experimental, meta= (EditCondition=bRevertUnchangedActors, EditConditionHides))` — Outputs that can change on every generation but do not have an impact on final result should be listed here so they can be ignored when comparing results for revert.

### `Plugins/PCG/Source/PCGEditor/Private/WorldPartitionBuilder/PCGWorldPartitionBuilder.h` (Private)


#### struct `FPCGWorldPartitionCommandlineArgs`  
`struct FPCGWorldPartitionCommandlineArgs`  
_L20-51_
- L23 _public member_ `TOptional<bool> bGenerateEditingModeLoadAsPreviewComponents;` — Include components which have editing mode set to LoadAsPreview.
- L26 _public member_ `TOptional<bool> bGenerateEditingModeNormalComponents;` — Include components which have editing mode set to Normal.
- L29 _public member_ `TOptional<bool> bGenerateEditingModePreviewComponents;` — Include components which have editing mode set to Preview.
- L32 _public member_ `TOptional<TArray<FString>> IncludeGraphNames;` — If non empty, components with each graph name will be generated (if editing mode is included), in order.
- L35 _public member_ `TOptional<bool> bOneComponentAtATime;` — Call generate on each component and wait until completion and any async processes before generating the next.
- L38 _public member_ `TOptional<TArray<FString>> IncludeActorIDs;` — If non empty, only components on actors with given ID(s) will be generated.
- L41 _public member_ `TOptional<bool> bIgnoreGenerationErrors;` — Submit dirty files even if errors occurred during generation.
- L44 _public member_ `TOptional<TSoftObjectPtr<UPCGBuilderSettings>> SettingAsset;` — Path to builder settings asset
- L47 _public member_ `TOptional<bool> bIterativeCellLoading;` — Flag to generate using an iterative cell loading. Useful for large maps to limit memory consumption.
- L50 _public member_ `TOptional<int32> IterativeCellSize;` — Cell size for iterative cell loading

#### struct `FPCGWorldPartitionBuilderArgs`  
`struct FPCGWorldPartitionBuilderArgs`  
_L53-104_
- L56 _public member_ `bool bGenerateEditingModeLoadAsPreviewComponents = true;` — Include components which have editing mode set to LoadAsPreview.
- L59 _public member_ `bool bGenerateEditingModeNormalComponents = false;` — Include components which have editing mode set to Normal.
- L62 _public member_ `bool bGenerateEditingModePreviewComponents = false;` — Include components which have editing mode set to Preview.
- L65 _public member_ `TArray<FString> IncludeGraphNames;` — If non empty, components with each graph name will be generated (if editing mode is included), in order.
- L68 _public member_ `TArray<TSoftObjectPtr<UPCGGraphInterface>> IncludeGraphs;` — If non empty, components with each graph asset will be generated (if editing mode is included), in order
- L71 _public member_ `bool bOneComponentAtATime = false;` — Call generate on each component and wait until completion and any async processes before generating the next.
- L74 _public member_ `TArray<FString> IncludeActorIDs;` — If non empty, only components on actors with given ID(s) will be generated.
- L77 _public member_ `bool bIgnoreGenerationErrors = false;` — Submit dirty files even if errors occurred during generation.
- L80 _public member_ `bool bIterativeCellLoading = false;` — Flag to generate using an iterative cell loading. Useful for large maps to limit memory consumption.
- L83 _public member_ `int32 IterativeCellSize = 25600;` — Cell size for iterative cell loading
- L86 _public member_ `bool bLoadEditorOnlyDataLayers = true;` — Will load editor only data layers without having to specify them as included
- L89 _public member_ `bool bLoadActivatedRuntimeDataLayers = true;` — Will load runtime data layers that are default activated without having to specify them as included
- L92 _public member_ `TArray<TObjectPtr<UDataLayerAsset>> IncludedDataLayers;` — Data layers that need to be loaded when running builder.
- L95 _public member_ `TArray<TObjectPtr<UDataLayerAsset>> ExcludedDataLayers;` — Data layers that need to be unloaded when running builder.
- L98 _public member_ `bool bRevertUnchangedActors = false;` — Experimental feature that will try and revert PCG Component Actors which haven't changed from their previous generation.
- L101 _public member_ `TArray<FString> OutputsToIgnoreForRevert;` — Outputs that can change on every generation but do not have an impact on final result should be listed here so they can be ignored when comparing results for revert.
- L103 _public prototype_ `static bool InitializeFrom(const FPCGWorldPartitionCommandlineArgs& CommandlineArgs, FPCGWorldPartitionBuilderArgs& OutArgs);`

#### class `UPCGWorldPartitionBuilderHelper`  
`class UPCGWorldPartitionBuilderHelper : public UBlueprintFunctionLibrary`  
_L107-114_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L113 _private prototype_ `static void AddAssetToSubmitAllowList(const TSoftObjectPtr<UObject>& InPath);` — `UFUNCTION(BlueprintCallable, Category = "PCG|Builder")` — Notify the running PCG Builder that this asset can be saved/submitted as part of the builder execution if it is dirty

#### class `UPCGWorldPartitionBuilder`  
`class UPCGWorldPartitionBuilder : public UWorldPartitionBuilder`  
_L136-204_
- reflection: `UCLASS()`
- inherits: `UWorldPartitionBuilder`
- desc: Builder that triggers generation on PCG components. Example command line: ProjectName MapName -Unattended -AllowCommandletRendering -run=WorldPartitionBuilderCommandlet -Builder=PCGWorldPartitionBuilder -SCCProvider=[ProviderName] -AllowCommandletRendering -AllowSoftwareRendering -AssetGatherAll=true Optional switches: -PCGBuilderSettings=/Game/Path/BuilderSettingsAssetName (default: none) -IncludeGraphNames=PCG_GraphA;PCG_GraphB (default: all graphs) -GenerateComponentEditingModeLoadAsPreview (default: true) -GenerateComponentEditingModeNormal (default: false) -GenerateComponentEditingModePreview (default: false) -IgnoreGenerationErrors (default: false) -IncludeActorIDs=MyActor1_UAID1234678;MyActor2_UAID1234678 (default: all actors) -OneComponentAtATime (default: false) -IterativeCellLoading (default: false) -IterativeCellSize=25600 (default: 25600)
- L145 _public function_ `virtual bool RequiresCommandletRendering() const override` — Whether to require initialization of rendering, for now default to true. Requires a GPU present. Get Texture Data benefits from rendering - means the GPU will be available as a fallback sampling method so that the "CPU sampling" option does not have to be enabled on the texture. This may expand to other nodes if we use GPU resources or compute more in the future.
- L148 _public function_ `virtual ELoadingMode GetLoadingMode() const override` — In the future we may load a world in stages, but for now load everything to make sure we have the complete level.
- L150 _public prototype_ `void AddAssetToSubmitAllowList(const TSoftObjectPtr<UObject>& SoftObjectPath);`
- L153 _protected prototype_ `virtual bool PreWorldInitialization(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;`
- L154 _protected prototype_ `virtual bool PreRun(UWorld* World, FPackageSourceControlHelper& PackageHelper) override;`
- L155 _protected prototype_ `virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper) override;`
- L156 _protected prototype_ `virtual bool PostRun(UWorld* World, FPackageSourceControlHelper& PackageHelper, const bool bInRunSuccess) override;`
- L158 _protected prototype_ `bool RunEntireWorld(UWorld* World, FPackageSourceControlHelper& PackageHelper);`
- L159 _protected prototype_ `bool RunPerCell(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper);`
- L161 _protected function_ `virtual bool CanProcessNonPartitionedWorlds() const override`
- L164 _protected prototype_ `bool SaveEntireWorldPackages(UWorld* World, FPackageSourceControlHelper& PackageHelper, TArray<UPackage*> DirtyPackages, TSet<FString> DeletedPackages);` — Save all the pending dirty and deleted packages.
- L167 _protected prototype_ `bool SavePerCellPackages(UWorld* World, FPackageSourceControlHelper& PackageHelper, TSet<FString> CellDeletedPackages);` — Save all the cell packages
- L170 _protected prototype_ `static bool CanBuild(const UWorld* InWorld, FName InBuildOption);`
- L171 _protected prototype_ `static EEditorBuildResult Build(UWorld* InWorld, FName InBuildOption);`
- L174 _private member_ `FName PreviousProviderName;` — Track file states to build changelist in PostRun
- L175 _private member_ `TSet<FString> NewPackageNames;`
- L176 _private member_ `TSet<FString> ModifiedPackageNames;`
- L177 _private member_ `TSet<FString> DeletedPackageNames;`
- L180 _private member_ `TSet<TSoftObjectPtr<const UPCGComponent>> GeneratedComponents;` — Track the generated components to avoid multiple generations when cells overlap
- L182 _private member_ `TMap<TSoftObjectPtr<UPCGComponent>, FWorldPartitionReference> PartitionedComponents;` — Processed Original Partitioned Components + Reference to owning actor to avoid unloading Original Components and causing destructive changes to Partition Actors, we keep them loaded until PostRun
- L184 _private member_ `FPCGWorldPartitionCommandlineArgs CommandlineArgs;`
- L185 _private member_ `FPCGWorldPartitionBuilderArgs Args;`
- L188 _private member_ `TSet<FString> AllowedAssetPackages;` — Non Actor assets that are allowed to be submitted by the builder
- L191 _private member_ `TMap<TSoftObjectPtr<AActor>, FPCGCrc> RevertableActors;` — Revertable Actors
- L194 _private member_ `TSet<TSoftObjectPtr<AActor>> RevertedActors;` — Reverted Actors : when using the builder in per cell iteration, it is possible that one cell reverts an actor because it doesn't modify it but the next one will so keep track for stats
- L197 _private member_ `int32 NumNewPackages = 0;` — Final stats
- L198 _private member_ `int32 NumModifiedPackages = 0;`
- L199 _private member_ `int32 NumDeletedPackages = 0;`
- L200 _private member_ `int32 NumRevertedPackages = 0;`
- L203 _private member_ `bool bErrorOccurredWhileGenerating = false;` — Flag to register if any error occurred during generation.

### `Plugins/PCG/Source/PCGEditor/Private/WorldPartitionBuilder/SPCGBuilderDialog.h` (Private)


#### struct `FPCGBuilderDialogParams`  
`struct FPCGBuilderDialogParams`  
_L17-23_
- reflection: `USTRUCT()`
- L22 _public member_ `TSoftObjectPtr<UPCGBuilderSettings> BuilderSetting;` — `UPROPERTY(EditAnywhere, Category = Default)`

#### class `SPCGBuilderDialog`  
`class SPCGBuilderDialog : public SCompoundWidget`  
_L28-68_
- inherits: `SCompoundWidget`
- L37 _public function_ `SLATE_BEGIN_ARGS(SPCGBuilderDialog)`
- L39 _public prototype_ `SLATE_ATTRIBUTE(TSharedPtr<SWindow>, ParentWindow) SLATE_END_ARGS() ~SPCGBuilderDialog() = default;` — A pointer to the parent window
- L49 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget.  Called by the SNew() Slate macro. @param	InArgs				Declaration used by the SNew() macro to construct this widget
- L51 _public member_ `static const FVector2D DEFAULT_WINDOW_SIZE;`
- L53 _public function_ `DialogResult GetDialogResult() const`
- L54 _public function_ `TSoftObjectPtr<UPCGBuilderSettings> GetBuilderSetting() const`
- L57 _private prototype_ `FReply OnBuildClicked();`
- L58 _private prototype_ `FReply OnCancelClicked();`
- L61 _private member_ `TWeakPtr<SWindow> ParentWindowPtr;` — Pointer to the parent window, so we know to destroy it when done
- L64 _private member_ `DialogResult Result;` — Dialog Result
- L67 _private member_ `FPCGBuilderDialogParams Params;` — Dialog Params

#### enum `SPCGBuilderDialog::DialogResult`  
`enum DialogResult`  
_L31-35_
- L33 _public enumerator_ `Build`
- L34 _public enumerator_ `Cancel`

### `Plugins/PCG/Source/PCGEditor/Public/AssetEditorMode/PCGAssetEdMode.h` (Public)


#### class `UPCGAssetEditorMode`  
`class UPCGAssetEditorMode : public UEdMode`  
_L21-74_
- reflection: `UCLASS(Transient)`
- inherits: `UEdMode`
- desc: Editor mode used exclusively within the PCG Asset Editor window (FPCGEditor). Unlike UPCGEditorMode, which is a globally registered level-editor mode with viewport focus customization, auto-save control, and per-tick updates, this mode is instantiated and owned directly by the asset editor. It holds a back-reference to the owning FPCGEditor and has no static Register/Unregister lifecycle — it is activated and deactivated alongside the editor tab.
- L27 _public member_ `const static FEditorModeID EM_PCGAssetEditorModeId;` — Unique name for PCG Asset Editor Mode
- L29 _public prototype_ `UPCGAssetEditorMode();`
- L32 _public prototype_ `virtual void Enter() override;` — Focus event when the Asset Editor enters PCG Editor Mode.
- L35 _public prototype_ `virtual void Exit() override;` — Focus event when the Asset Editor leaves PCG Editor Mode.
- L38 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;` — Tool exclusivity
- L41 _public prototype_ `bool IsAnyToolActive() const;` — Check if any tool is currently active
- L44 _public function_ `void SetPCGEditor(TWeakPtr<class FPCGEditor> InPCGEditor)` — Set the PCG editor this mode is associated with
- L47 _public function_ `TSharedPtr<class FPCGEditor> GetPCGEditor() const` — Get the PCG editor this mode is associated with
- L50 _protected prototype_ `void ConfigureRealTimeViewportsOverride(bool bEnable);`
- L53 _protected member_ `TWeakPtr<class FPCGEditor> PCGEditor;` — Reference to the PCG editor this mode is associated with

### `Plugins/PCG/Source/PCGEditor/Public/AssetEditorMode/Tools/PCGAssetEditorInteractiveTool.h` (Public)


#### class `UPCGNodeToolContext`  
`class UPCGNodeToolContext : public UObject`  
_L48-65_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Generic context object stored in UContextObjectStore to pass data from FPCGEditor into a tool. Populated by FPCGEditor::OnNodeToolStarted before activating any node tool.
- L54 _public member_ `TObjectPtr<UPCGSettings> NodeSettings = nullptr;` — `UPROPERTY()`
- L58 _public member_ `TObjectPtr<UObject> ExecutionSourceObject = nullptr;` — `UPROPERTY()` — The UObject that implements IPCGGraphExecutionSource (e.g. UPCGComponent). Kept alive via UPROPERTY.
- L62 _public member_ `TObjectPtr<UPCGGraphInstance> GraphInstance = nullptr;` — `UPROPERTY()` — The graph instance being edited, used to trigger re-execution notifications.
- L64 _public prototype_ `IPCGGraphExecutionSource* GetExecutionSource() const;`

#### class `UPCGAssetEditorInteractiveToolSettings`  
`class UPCGAssetEditorInteractiveToolSettings : public UInteractiveToolPropertySet`  
_L71-79_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- desc: Settings for PCG Asset Editor Interactive Tool

#### class `UPCGAssetEditorInteractiveTool`  
`class UPCGAssetEditorInteractiveTool : public UInteractiveTool`  
_L86-128_
- reflection: `UCLASS(Abstract)`
- inherits: `UInteractiveTool`
- desc: Base interactive tool for PCG Asset Editor Provides viewport coordination and node inspection integration
- L92 _public prototype_ `virtual void Setup() override;`
- L93 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L95 _public function_ `virtual bool HasCancel() const override`
- L97 _public function_ `virtual bool HasAccept() const override`
- L99 _public function_ `virtual bool CanAccept() const override`
- L103 _public function_ `virtual void PostBuild(const FToolBuilderState& SceneState)` — Called by the builder immediately after construction, before Setup(). Override for custom builder-time initialization.
- L110 _protected function_ `virtual void OnTick(float DeltaTime) override` — Called when tool ticks
- L113 _protected function_ `virtual void OnAccept()` — Called when the tool is accepted
- L116 _protected function_ `virtual void OnCancel()` — Called when the tool is cancelled
- L119 _protected function_ `virtual void OnNodeSettingsChanged(UPCGSettings* NodeSettings, EPCGChangeType ChangeType)` — Called when tool's respective node settings is changed
- L122 _protected member_ `TObjectPtr<UPCGNodeToolContext> NodeToolContext = nullptr;` — `UPROPERTY()`
- L125 _protected member_ `TObjectPtr<UPCGAssetEditorInteractiveToolSettings> ToolSettings = nullptr;` — `UPROPERTY()`
- L127 _protected member_ `IPCGGraphExecutionSource* ExecutionSource = nullptr;`

#### class `UPCGAssetEditorInteractiveToolBuilder`  
`class UPCGAssetEditorInteractiveToolBuilder : public UInteractiveToolBuilder`  
_L135-148_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- desc: Generic builder for PCG Asset Editor Interactive Tools. Set ToolClass to the desired tool subclass; the builder instantiates it and calls PostBuild.
- L142 _public member_ `TSubclassOf<UPCGAssetEditorInteractiveTool> ToolClass = nullptr;` — `UPROPERTY()` — The concrete tool class to instantiate. Set this when registering a tool.
- L145 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L146 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`

#### Free symbols / members of external scopes

- L21 _function_ `template <typename... TSettings> TArray<UClass*> PCGMakeSupportedSettingsArray()` — Expands each TSettings type into its StaticClass() pointer.
- L36 _macro_ `#define PCG_DECLARE_SUPPORTED_NODES(...) \` — Declare the UPCGSettings subclasses that activate this tool. Pass bare class names — ::StaticClass() is added automatically. Place inside the tool class body. Example: PCG_DECLARE_SUPPORTED_NODES( UPCGCreatePointsSettings, UPCGCreatePointsGridSettings )

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGBaseTextureDataVisualization.h` (Public)


#### class `FPCGBaseTextureDataVisualization`  
`class FPCGBaseTextureDataVisualization : public IPCGSpatialDataVisualization`  
_L12-19_
- inherits: `IPCGSpatialDataVisualization`
- L16 _public prototype_ `virtual TArray<TSharedPtr<FStreamableHandle>> LoadRequiredResources(const UPCGData* Data) const override;`
- L17 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGCollisionVisComponent.h` (Public)


#### class `UPCGCollisionVisComponent`  
`class UPCGCollisionVisComponent : public UPrimitiveComponent`  
_L10-33_
- reflection: `UCLASS(MinimalAPI, NotPlaceable)`
- inherits: `UPrimitiveComponent`
- L16 _public member_ `TArray<TObjectPtr<UBodySetup>> BodySetups;` — `UPROPERTY()`
- L19 _public member_ `TArray<FTransform> BodyTransforms;` — `UPROPERTY()`
- L22 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L26 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L27 _public function_ `virtual UBodySetup* GetBodySetup() override`
- L28 _public function_ `virtual bool IsEditorOnly() const override`
- L31 _public prototype_ `void SetBodySetup(UBodySetup* InBodySetup);`
- L32 _public prototype_ `void AddBodySetup(UBodySetup* InBodySetup, const FTransform& InTransform);`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGDataViewVisualization.h` (Public)


#### class `FPCGDataViewVisualization`  
`class FPCGDataViewVisualization : public IPCGDataVisualization`  
_L9-18_
- inherits: `IPCGDataVisualization`
- L13 _public prototype_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override;`
- L14 _public prototype_ `virtual ~FPCGDataViewVisualization() override = default;`
- L15 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L16 _public prototype_ `virtual FString GetDomainDisplayNameForInspection(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGDataVisualizationHelpers.h` (Public)


#### struct `PCGDataVisualizationHelpers::FColumnInfoOverrides`  
`struct FColumnInfoOverrides`  
_L18-27_
- L20 _public member_ `FText LabelOverride;`
- L21 _public member_ `FText TooltipOverride;`
- L22 _public member_ `bool bAddTypeToTooltip = true;`
- L23 _public member_ `bool bIsConstantValueCompressed = false;`
- L24 _public member_ `EPCGMetadataTypes TypeOverride = EPCGMetadataTypes::Unknown;`
- L25 _public member_ `TFunction<TSharedPtr<const IPCGAttributeAccessor>()> CreateAccessorFuncOverride;`
- L26 _public member_ `TFunction<TSharedPtr<const IPCGAttributeAccessorKeys>()> CreateAccessorKeysFuncOverride;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PCGDataVisualizationConstants`
- L13 _variable_ `const FName NAME_Index = FName(TEXT("$Ind` (scope `PCGDataVisualizationConstants`) — Names of the columns in the attribute list.
- L16 _namespace_ `namespace PCGDataVisualizationHelpers`
- L37 _prototype_ `void AddColumnInfo(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides = {});` (scope `PCGDataVisualizationHelpers`) — Add a new column to the VisualizerInfo, using the Data and Selector. By default, it will create a column with the label extracted from the selector, with accessor and keys created from the data and selector, but you can provide overrides. @param OutInfo @param Data @param InSelector @param Overrides
- L39 _prototype_ `void CreateMetadataColumnInfos(const UPCGData* Data, FPCGTableVisualizerInfo& OutInfo, const FPCGMetadataDomainID& DomainID = PCGMetadataDomainID::Default);` (scope `PCGDataVisualizationHelpers`)
- L41 _prototype_ `FPCGTableVisualizerInfo CreateDefaultMetadataColumnInfos(const UPCGData* Data, const FPCGMetadataDomainID& DomainID = PCGMetadataDomainID::Default);` (scope `PCGDataVisualizationHelpers`)
- L44 _function_ `template <typename T> void AddTypedColumnInfo_Impl(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides = {})` (scope `PCGDataVisualizationHelpers`)
- L50 _function_ `template <typename T> void AddTypedColumnInfo(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides = {})` (scope `PCGDataVisualizationHelpers`)
- L65 _function_ `template <typename T> void AddPropertyEnumColumnInfo(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const UEnum* EnumClass, int64 EnumValue, const FColumnInfoOverrides& Overrides = {})` (scope `PCGDataVisualizationHelpers`)
- L96 _function_ `template <typename T, typename EnumType> void AddPropertyEnumColumnInfo(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, EnumType EnumValue, const FColumnInfoOverrides& Overrides = {})` (scope `PCGDataVisualizationHelpers`)
- L103 _prototype_ `template <> void AddTypedColumnInfo_Impl<FVector2D>(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides);` (scope `PCGDataVisualizationHelpers`)
- L107 _prototype_ `template <> void AddTypedColumnInfo_Impl<FVector>(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides);` (scope `PCGDataVisualizationHelpers`)
- L108 _prototype_ `template <> void AddTypedColumnInfo_Impl<FVector4>(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides);` (scope `PCGDataVisualizationHelpers`)
- L109 _prototype_ `template <> void AddTypedColumnInfo_Impl<FLinearColor>(FPCGTableVisualizerInfo& OutInfo, const UPCGData* Data, const FPCGAttributePropertySelector& InSelector, const FColumnInfoOverrides& Overrides);` (scope `PCGDataVisualizationHelpers`)

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGLandscapeDataVisualization.h` (Public)


#### class `IPCGLandscapeDataVisualization`  
`class IPCGLandscapeDataVisualization : public IPCGSpatialDataVisualization`  
_L14-20_
- inherits: `IPCGSpatialDataVisualization`
- desc: Overrides collapse behavior to target a given number of points generated, to avoid too coarse debug (points way bigger than data) or enormous amount of points (points way smaller than data).
- L18 _public prototype_ `virtual const UPCGBasePointData* CollapseToDebugBasePointData(FPCGContext* Context, const UPCGData* Data) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGParamDataVisualization.h` (Public)


#### class `IPCGParamDataVisualization`  
`class IPCGParamDataVisualization : public IPCGDataVisualization`  
_L11-16_
- inherits: `IPCGDataVisualization`
- L14 _public function_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const`
- L15 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGPolygon2DDataVisualization.h` (Public)


#### class `FPCGPolygon2DDataVisualization`  
`class FPCGPolygon2DDataVisualization : public IPCGSpatialDataVisualization`  
_L10-17_
- inherits: `IPCGSpatialDataVisualization`
- L14 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L15 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGRawBufferDataVisualization.h` (Public)


#### class `FPCGRawBufferDataVisualization`  
`class FPCGRawBufferDataVisualization : public IPCGDataVisualization`  
_L9-14_
- inherits: `IPCGDataVisualization`
- L12 _public prototype_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override;`
- L13 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGSpatialDataVisualization.h` (Public)


#### class `IPCGSpatialDataVisualization`  
`class IPCGSpatialDataVisualization : public IPCGDataVisualization`  
_L18-44_
- inherits: `IPCGDataVisualization`
- desc: Default implementation for spatial data. Collapses to a PointData representation.
- L22 _public prototype_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override;`
- L23 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L26 _public function_ `virtual FPCGMetadataDomainID GetDefaultDomainForInspection(const UPCGData* Data) const override` — Show the sampled points by default
- L27 _public prototype_ `virtual FString GetDomainDisplayNameForInspection(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L28 _public prototype_ `virtual TArray<FPCGMetadataDomainID> GetAllSupportedDomainsForInspection(const UPCGData* Data) const override;`
- L29 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`
- L33 _public prototype_ `virtual const UPCGPointData* CollapseToDebugPointData(FPCGContext* Context, const UPCGData* Data) const;` — `UE_DEPRECATED(5.6, "Implement CollapseToDebugBasePointData instead")`
- L35 _public prototype_ `virtual const UPCGBasePointData* CollapseToDebugBasePointData(FPCGContext* Context, const UPCGData* Data) const;`
- L37 _public prototype_ `virtual void ExecuteDebugDisplayHelper( const UPCGData* Data, const FPCGDebugVisualizationSettings& DebugSettings, FPCGContext* Context, AActor* TargetActor, const FPCGCrc& Crc, const TFunction<void(class UInstancedStaticMeshComponent*)>& OnISMCCreatedCallback) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGSplineDataVisualization.h` (Public)


#### class `IPCGSplineDataVisualization`  
`class IPCGSplineDataVisualization : public IPCGSpatialDataVisualization`  
_L13-25_
- inherits: `IPCGSpatialDataVisualization`
- L17 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L18 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`
- L23 _public prototype_ `virtual const UPCGBasePointData* CollapseToDebugBasePointData(FPCGContext* Context, const UPCGData* Data) const override;` — Overrides collapse behavior to show the spline control points.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGStaticMeshDataVisualization.h` (Public)


#### class `IPCGStaticMeshDataVisualization`  
`class IPCGStaticMeshDataVisualization : public IPCGDataVisualization`  
_L11-20_
- inherits: `IPCGDataVisualization`
- L15 _public function_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override`
- L16 _public prototype_ `virtual FPCGTableVisualizerInfo GetTableVisualizerInfoWithDomain(const UPCGData* Data, const FPCGMetadataDomainID& DomainID) const override;`
- L17 _public prototype_ `virtual TArray<TSharedPtr<FStreamableHandle>> LoadRequiredResources(const UPCGData* Data) const override;`
- L18 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGTexture2DArrayDataVisualization.h` (Public)


#### class `FPCGTexture2DArrayDataVisualization`  
`class FPCGTexture2DArrayDataVisualization : public IPCGSpatialDataVisualization`  
_L10-17_
- inherits: `IPCGSpatialDataVisualization`
- L14 _public prototype_ `virtual TArray<TSharedPtr<FStreamableHandle>> LoadRequiredResources(const UPCGData* Data) const override;`
- L15 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`

### `Plugins/PCG/Source/PCGEditor/Public/DataVisualizations/PCGVolumeDataVisualization.h` (Public)


#### class `FPCGPrimitiveDataVisualization`  
`class FPCGPrimitiveDataVisualization : public IPCGSpatialDataVisualization`  
_L13-23_
- inherits: `IPCGSpatialDataVisualization`
- desc: Overrides collapse behavior to target a given number of points generated, to avoid too coarse debug (points way bigger than data) or enormous amount of points (points way smaller than data).
- L17 _public prototype_ `virtual const UPCGBasePointData* CollapseToDebugBasePointData(FPCGContext* Context, const UPCGData* Data) const override;`
- L18 _public prototype_ `FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`
- L22 _protected prototype_ `virtual void GetComponentsAndTransforms(const UPCGData* InData, TArray<TObjectPtr<UPrimitiveComponent>>& OutComponents, TArray<FTransform>& OutComponentTransforms) const;`

#### class `FPCGVolumeDataVisualization`  
`class FPCGVolumeDataVisualization : public FPCGPrimitiveDataVisualization`  
_L26-30_
- inherits: `FPCGPrimitiveDataVisualization`
- desc: Specialization for volumes that don't always rely on their primitive component
- L29 _protected prototype_ `virtual void GetComponentsAndTransforms(const UPCGData* InData, TArray<TObjectPtr<UPrimitiveComponent>>& OutComponents, TArray<FTransform>& OutComponentTransforms) const override;`

#### class `FPCGCollisionShapeDataVisualization`  
`class FPCGCollisionShapeDataVisualization : public FPCGPrimitiveDataVisualization`  
_L33-37_
- inherits: `FPCGPrimitiveDataVisualization`
- desc: Specialization for simple collision shapes
- L36 _protected prototype_ `virtual void GetComponentsAndTransforms(const UPCGData* InData, TArray<TObjectPtr<UPrimitiveComponent>>& OutComponents, TArray<FTransform>& OutComponentTransforms) const override;`

#### class `FPCGCollisionWrapperDataVisualization`  
`class FPCGCollisionWrapperDataVisualization : public FPCGPrimitiveDataVisualization`  
_L40-44_
- inherits: `FPCGPrimitiveDataVisualization`
- desc: Specialization for collision wrappers
- L43 _protected prototype_ `virtual void GetComponentsAndTransforms(const UPCGData* InData, TArray<TObjectPtr<UPrimitiveComponent>>& OutComponents, TArray<FTransform>& OutComponentTransforms) const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/DeltaViewportExtensions/PCGDeltaViewportExtension.h` (Public)


#### struct `FPCGDeltaCreateContext`  
`struct FPCGDeltaCreateContext`  
_L16-20_
- desc: Context passed to extensions when creating a new delta on first gizmo release.
- L18 _public member_ `FBox ComponentBounds = FBox(ForceInit);`
- L19 _public member_ `int32 OriginalElementIndex = INDEX_NONE;`

#### struct `FPCGDeltaViewportContext`  
`struct FPCGDeltaViewportContext`  
_L23-37_
- desc: Snapshot of panel state passed to extensions when the selection or configuration changes.
- L25 _public member_ `bool bSelectionActive = false;`
- L26 _public member_ `FPCGDeltaKey SelectionDeltaKey;`
- L27 _public member_ `FTransform SelectionTransform = FTransform::Identity;`
- L28 _public member_ `TWeakObjectPtr<UPCGComponent> ActivePCGComponent;`
- L29 _public member_ `FPCGSourceDataStorageKey ActiveStorageKey;`
- L30 _public member_ `TSharedPtr<const FPCGManualEditNodeConfiguration> NodeConfiguration;`
- L33 _public member_ `int32 SelectedElementIndex = INDEX_NONE;` — Index of the selected element within an insertion delta, or INDEX_NONE.
- L36 _public member_ `int32 OriginalElementIndex = INDEX_NONE;` — Index of the selected point in the original source data, or INDEX_NONE.

#### struct `FPCGDeltaViewportCallbacks`  
`struct FPCGDeltaViewportCallbacks`  
_L40-47_
- desc: Generic actions provided by the framework to extensions to subscribe to on creation.
- L42 _public member_ `TFunction<void(const FPCGDeltaKey&)> RevertDelta;`
- L43 _public member_ `TFunction<void()> RevertAllRestorableDeltas;`
- L44 _public member_ `TFunction<void()> RequestListRefresh;`
- L45 _public member_ `TFunction<void()> ClearSelection;`
- L46 _public member_ `TFunction<void(const FPCGDeltaKey&, int32)> SelectElement;`

#### struct `FPCGDeltaKeyBinding`  
`struct FPCGDeltaKeyBinding`  
_L50-54_
- desc: A key binding requested by an extension for an input action.
- L52 _public member_ `FKey Key;`
- L53 _public member_ `TFunction<void()> Action;`

#### struct `FInsertedViewportElement`  
`struct FInsertedViewportElement`  
_L57-62_
- desc: An element inserted by an extension that has no corresponding source point. Drawn and hit-tested by the visualizer.
- L59 _public member_ `FPCGDeltaKey DeltaKey;`
- L60 _public member_ `int32 ElementIndex = INDEX_NONE;`
- L61 _public member_ `FTransform Transform = FTransform::Identity;`

#### class `IPCGDeltaViewportExtension`  
`class IPCGDeltaViewportExtension`  
_L69-145_
- desc: Interface for manual editing viewport behavior and panel UI. Implement this to control: - What UI appears in the manual edit panel for a given delta type. - How elements with this delta type are drawn, selected, and manipulated in the viewport.
- L72 _public prototype_ `virtual ~IPCGDeltaViewportExtension() = default;`
- L75 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Returns the display name for this delta type.
- L78 _public function_ `virtual FName GetDeltaName() const` — The delta name used for key computation.
- L81 _public function_ `virtual int32 GetSortPriority() const` — Sort priority for the delta type selector. Lower values appear first.
- L84 _public prototype_ `virtual TSharedRef<SWidget> CreateWidget(FPCGDeltaViewportCallbacks Callbacks) = 0;` — Build the Slate widget section for this delta type. Called when the extension is swapped in.
- L87 _public prototype_ `virtual void UpdateContext(const FPCGDeltaViewportContext& Context) = 0;` — Called when the panel context changes. Update buttons, labels, etc.
- L90 _public prototype_ `virtual void RefreshLists(const FPCGDeltaViewportContext& Context) = 0;` — Called when the delta context changes and lists need refreshing.
- L93 _public function_ `virtual TArray<FPCGDeltaKeyBinding> GetKeyBindings()` — Returns key bindings this extension wants the visualizer to route. Called when the extension becomes active.
- L96 _public prototype_ `virtual FLinearColor GetDisplayColor(bool bIsSelected) const = 0;` — Color for drawing elements with this delta type in the viewport.
- L99 _public function_ `virtual FTransform GetDisplayTransform(const FTransform& SourceElementTransform, const FConstStructView DeltaStruct) const` — Given a source element transform and the delta struct, return the transform to display.
- L105 _public function_ `virtual bool MatchesSourceElement(const FTransform& SourceElementTransform, const FConstStructView DeltaStruct, const double SpatialTolerance) const` — Given a source element's transform and a delta, return true if this delta corresponds to that source element.
- L111 _public function_ `virtual void GetInsertedElements(const FPCGDeltaCollection& Collection, TArray<FInsertedViewportElement>& OutElements) const` — Collect elements inserted by this extension that have no corresponding source point. The visualizer draws and hit-tests these.
- L114 _public function_ `virtual bool UsesTRSGizmo() const` — Returns true if this delta type uses a TRS gizmo when selected.
- L117 _public function_ `virtual int32 OnAltDrag(FPCGDeltaCollection& Collection, const FTransform& SourceTransform, FPCGDeltaKey& OutDeltaKey) const` — Alt+drag handler. Usually used to create/insert new elements. Returns the new element index, or INDEX_NONE.
- L123 _public function_ `virtual bool ApplyGizmoTransform(const FTransform& NewTransform, TInstancedStruct<FPCGDeltaBase>& DeltaStruct, int32 ElementIndex) const` — Apply the final gizmo transform to the delta struct. Returns true on success.
- L129 _public function_ `virtual void CreateNewDelta( const FPCGDeltaKey& DeltaKey, FPCGDeltaCollection& Collection, const FTransform& OriginalTransform, const FTransform& NewTransform, const FPCGDeltaCreateContext& Context) const` — Create a new delta struct in the collection on first gizmo release (deferred creation).
- L138 _public function_ `virtual FTransform GetOriginalTransform(const FConstStructView DeltaStruct) const` — Returns the original transform stored in the delta struct.
- L144 _public function_ `virtual void CollectRestorableKeys(const FPCGDeltaCollection& Collection, TArray<FPCGDeltaKey>& OutKeys) const` — Collect all delta keys in the collection that this extension considers restorable.

#### struct `FPCGDeltaViewportExtensionRegistry`  
`struct FPCGDeltaViewportExtensionRegistry`  
_L148-184_
- desc: Register a delta struct type with an IPCGDeltaViewportExtension to control viewport behavior and panel UI.
- L150 _public prototype_ `FPCGDeltaViewportExtensionRegistry() = default;`
- L151 _public prototype_ `FPCGDeltaViewportExtensionRegistry(const FPCGDeltaViewportExtensionRegistry&) = delete;`
- L152 _public prototype_ `FPCGDeltaViewportExtensionRegistry(FPCGDeltaViewportExtensionRegistry&&) = default;`
- L153 _public prototype_ `FPCGDeltaViewportExtensionRegistry& operator=(const FPCGDeltaViewportExtensionRegistry&) = delete;`
- L154 _public prototype_ `FPCGDeltaViewportExtensionRegistry& operator=(FPCGDeltaViewportExtensionRegistry&&) = default;`
- L155 _public prototype_ `~FPCGDeltaViewportExtensionRegistry() = default;`
- L158 _public prototype_ `void RegisterInternalExtension(const UScriptStruct* DeltaStruct, TUniquePtr<IPCGDeltaViewportExtension> Extension);` — Register an internal viewport extension. Internal extensions are provided by the PCG plugin itself.
- L161 _public prototype_ `void UnregisterAllInternalExtensions();` — Unregister all internal viewport extensions.
- L164 _public prototype_ `void RegisterExtension(const UScriptStruct* DeltaStruct, TUniquePtr<IPCGDeltaViewportExtension> Extension);` — Register an external viewport extension. External registrations take priority over internal ones.
- L167 _public prototype_ `void UnregisterExtension(const UScriptStruct* DeltaStruct);` — Unregister an external viewport extension.
- L171 _public function_ `template <typename DeltaType> IPCGDeltaViewportExtension* GetExtension() const` — Look up an extension for the given delta struct type, walking the struct hierarchy toward FPCGDeltaBase.
- L173 _public prototype_ `IPCGDeltaViewportExtension* GetExtension(const UScriptStruct* DeltaStruct) const;`
- L176 _public prototype_ `TArray<const UScriptStruct*> GetRegisteredDeltaTypes() const;` — Returns all registered delta struct types (from both internal and external registries, deduplicated).
- L180 _private member_ `TMap<const UScriptStruct*, TUniquePtr<IPCGDeltaViewportExtension>> InternalRegistry;` — Registry for extensions defined inside the PCG Plugin.
- L183 _private member_ `TMap<const UScriptStruct*, TUniquePtr<IPCGDeltaViewportExtension>> ExternalRegistry;` — Registry for extensions defined outside the PCG Plugin. These take priority, allowing users to override default behavior.

### `Plugins/PCG/Source/PCGEditor/Public/DeltaVisualizations/PCGDeltaVisualization.h` (Public)


#### struct `FPCGDeltaVisualizerColumnInfo`  
`struct FPCGDeltaVisualizerColumnInfo`  
_L13-20_
- desc: Lightweight column descriptor for the delta overrides table.
- L15 _public member_ `FName Id;`
- L16 _public member_ `FText Label;`
- L17 _public member_ `FText Tooltip;`
- L18 _public member_ `float Width = -1.0f;` — Calculated automatically if < 0
- L19 _public member_ `EPCGTableVisualizerCellAlignment CellAlignment = EPCGTableVisualizerCellAlignment::Left;`

#### class `IPCGDeltaVisualization`  
`class IPCGDeltaVisualization`  
_L33-49_
- desc: Interface for delta type visualizers. If implemented, this controls how a specific delta struct type is displayed in the Data Overrides panel.
- L36 _public prototype_ `virtual ~IPCGDeltaVisualization() = default;`
- L39 _public prototype_ `virtual TArray<FPCGDeltaVisualizerColumnInfo> GetColumnInfos() const = 0;` — Returns the column descriptors this visualizer provides.
- L42 _public prototype_ `virtual FText GetCellText(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const = 0;` — Returns the text content for a specific cell.
- L48 _public function_ `virtual TSharedPtr<SWidget> CreateCellWidget(FName ColumnId, const FPCGDeltaKey& DeltaKey, FConstStructView Delta) const` — Returns a custom widget for a cell. Returns nullptr by default to fall back to GetCellText wrapped in STextBlock. Note: Optional.

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace PCGDeltaVisualization`
- L23 _namespace_ `namespace Constants` (scope `PCGDeltaVisualization`)
- L25 _variable_ `static const FName DeltaTypeId = TEXT("Del` (scope `PCGDeltaVisualization::Constants`)
- L26 _variable_ `static const FName SignatureId = TEXT("Sig` (scope `PCGDeltaVisualization::Constants`)

### `Plugins/PCG/Source/PCGEditor/Public/DeltaVisualizations/PCGDeltaVisualizationRegistry.h` (Public)


#### struct `FPCGDeltaVisualizationRegistry`  
`struct FPCGDeltaVisualizationRegistry`  
_L10-38_
- desc: Register a delta struct type with an IPCGDeltaVisualization to implement custom visualization behavior. Mirrors FPCGDataVisualizationRegistry.
- L12 _public prototype_ `FPCGDeltaVisualizationRegistry() = default;`
- L13 _public prototype_ `FPCGDeltaVisualizationRegistry(const FPCGDeltaVisualizationRegistry&) = delete;`
- L14 _public prototype_ `FPCGDeltaVisualizationRegistry(FPCGDeltaVisualizationRegistry&&) = default;`
- L15 _public prototype_ `FPCGDeltaVisualizationRegistry& operator=(const FPCGDeltaVisualizationRegistry&) = delete;`
- L16 _public prototype_ `FPCGDeltaVisualizationRegistry& operator=(FPCGDeltaVisualizationRegistry&&) = default;`
- L17 _public prototype_ `~FPCGDeltaVisualizationRegistry() = default;`
- L20 _public prototype_ `void RegisterDeltaVisualization(const UScriptStruct* DeltaStruct, TUniquePtr<const IPCGDeltaVisualization> Visualization);` — Register an external delta visualization.
- L23 _public prototype_ `void UnregisterDeltaVisualization(const UScriptStruct* DeltaStruct);` — Unregister an external delta visualization.
- L26 _public function_ `template <typename DeltaType> const IPCGDeltaVisualization* GetDeltaVisualization() const`
- L28 _public prototype_ `const IPCGDeltaVisualization* GetDeltaVisualization(const UScriptStruct* DeltaStruct) const;`
- L32 _private member_ `TMap<const UScriptStruct*, TUniquePtr<const IPCGDeltaVisualization>> InternalRegistry;` — Registry for delta visualizations defined inside the PCG Plugin.
- L35 _private member_ `TMap<const UScriptStruct*, TUniquePtr<const IPCGDeltaVisualization>> ExternalRegistry;` — Registry for delta visualizations defined outside the PCG Plugin. These take priority, allowing the user to override default visualization behavior for internal types.

### `Plugins/PCG/Source/PCGEditor/Public/Details/EnumSelectorDetails.h` (Public)


#### class `FEnumSelectorDetails`  
`class FEnumSelectorDetails : public IPropertyTypeCustomization`  
_L14-87_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for an enum selector allowing the user to easily select from a list of available enum classes and then also select a value from that class's options.
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L25 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L33 _public prototype_ `static FText StripEnumClassName(FName EnumValueName);` — Strips the enum class from the enum value name: EnumClass::EnumValue -> EnumValue.
- L36 _protected prototype_ `FEnumSelector* GetEnumSelector();`
- L38 _protected prototype_ `const FEnumSelector* GetEnumSelector() const;`
- L41 _protected prototype_ `UEnum* GetSelectedEnumClass() const;` — Helper to convert the drop down selection into an enum class.
- L44 _protected prototype_ `int64 GetSelectedEnumValue() const;` — Helper to convert the drop down selection into an enum value.
- L47 _protected prototype_ `void SetSelectorEnumClass(UEnum* Class);` — Sets the selector enum class and calls the property update functions.
- L50 _protected prototype_ `void SetSelectorEnumValue(const int64 Value);` — Sets the selector enum value and calls the property update functions.
- L53 _protected prototype_ `void UpdateEnumClass(const TSharedPtr<FString>& EnumString);` — Updates the enum class from the SSearchableComboBox item type.
- L56 _protected prototype_ `void UpdateEnumValue(FName ValueName);` — Updates the enum value from the SComboBox item type.
- L58 _protected prototype_ `void InitializeClassComboBox();`
- L59 _protected prototype_ `void InitializeClassComboBoxSelection();`
- L61 _protected prototype_ `void OnClassComboSelectionChanged(TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo);`
- L62 _protected prototype_ `void OnValueComboSelectionChanged(FName InSelectedItem, ESelectInfo::Type SelectInfo);`
- L65 _protected prototype_ `void ReloadValueOptions();` — Reloads the enum values associated with an enum class, once a different enum class has been selected.
- L68 _protected prototype_ `EVisibility IsValueSelectionVisible() const;` — Returns true only if the selector and enum class are both valid, false otherwise.
- L71 _protected prototype_ `FText GetSelectedEnumClassText() const;` — Gets the display text for the currently selected enum class.
- L74 _protected prototype_ `FText GetSelectedEnumValueText() const;` — Gets the display text for the currently selected enum value.
- L76 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L78 _protected member_ `TArray<TSharedPtr<FString>> EnumClassSourceOptions;`
- L79 _protected member_ `TArray<FName> EnumValueSourceOptions;`
- L81 _protected member_ `TMap<TSharedPtr<FString>, UEnum*> NameStringToEnumClassMap;`
- L83 _protected member_ `TSharedPtr<SComboBox<FName>> EnumValueComboBox;`
- L85 _protected member_ `TSharedPtr<FString> ClassSelection;`
- L86 _protected member_ `FName ValueSelection;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGAttributePropertySelectorDetails.h` (Public)


#### class `FPCGAttributePropertySelectorDetails`  
`class FPCGAttributePropertySelectorDetails : public IPropertyTypeCustomization`  
_L17-48_
- inherits: `IPropertyTypeCustomization`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L27 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L30 _public prototype_ `void AddExtractor(FName InExtractor);`
- L34 _protected prototype_ `TTuple<FPropertyAccess::Result, const FPCGAttributePropertySelector*> GetStruct() const;` — Return the result of GetValueData on the PropertyHandle. The output struct will be the first valid selector.
- L36 _protected prototype_ `TSharedRef<SWidget> GenerateExtraMenu();`
- L37 _protected prototype_ `EVisibility ExtraMenuVisibility() const;`
- L38 _protected prototype_ `bool IsEnabled() const;`
- L40 _protected prototype_ `FText GetText() const;`
- L41 _protected prototype_ `void SetText(const FText& NewText, ETextCommit::Type CommitInfo);`
- L42 _protected prototype_ `void SetPointProperty(EPCGPointProperties EnumValue);`
- L43 _protected prototype_ `void SetAttributeName(FName NewName);`
- L44 _protected prototype_ `void SetExtraProperty(EPCGExtraProperties EnumValue);`
- L45 _protected prototype_ `void SetSelector(FPCGAttributePropertySelector InSelector);`
- L47 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace ETextCommit`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGBlueprintSettingsDetails.h` (Public)


#### class `FPCGBlueprintSettingsDetails`  
`class FPCGBlueprintSettingsDetails : public IDetailCustomization`  
_L15-33_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ~Begin IDetailCustomization interface
- L26 _private prototype_ `void AddCallInEditorMethods(IDetailLayoutBuilder& DetailBuilder);` — Creates a button strip in each category that contains reflected functions marked as CallInEditor
- L29 _private prototype_ `FReply OnExecuteCallInEditorFunction(TWeakObjectPtr<UFunction> WeakFunctionPtr);` — Executes the specified method on the selected objects
- L32 _private member_ `TWeakObjectPtr<UPCGBlueprintBaseElement> SelectedObject;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGComponentDetails.h` (Public)


#### class `FPCGComponentDetails`  
`class FPCGComponentDetails : public IDetailCustomization`  
_L12-24_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ~Begin IDetailCustomization interface
- L22 _protected prototype_ `virtual TArray<TWeakInterfacePtr<IPCGGraphExecutionSource>> GatherExecutionSourcesFromSelection(const TArray<TWeakObjectPtr<UObject>>& InObjectSelected) const;`
- L23 _protected function_ `virtual bool AddDefaultProperties() const`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGCustomHLSLSettingsDetails.h` (Public)


#### class `FPCGCustomHLSLSettingsDetails`  
`class FPCGCustomHLSLSettingsDetails : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the Custom HLSL node settings.
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _private prototype_ `TWeakPtr<FPCGEditor> GetPCGEditor(const TArray<TWeakObjectPtr<UObject>>& InObjectsBeingCustomized);`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGDataTypeIdentifierDetails.h` (Public)


#### class `FPCGDataTypeIdentifierDetails`  
`class FPCGDataTypeIdentifierDetails : public IPropertyTypeCustomization`  
_L13-39_
- inherits: `IPropertyTypeCustomization`
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L23 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L27 _protected prototype_ `FPCGDataTypeIdentifier* GetStruct();`
- L28 _protected prototype_ `const FPCGDataTypeIdentifier* GetStruct() const;`
- L30 _protected prototype_ `FText GetText() const;`
- L31 _protected prototype_ `FText GetTooltip() const;`
- L32 _protected prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L34 _protected member_ `TArray<FPCGDataTypeBaseId> HiddenTypes;`
- L35 _protected member_ `TArray<TTuple<FPCGDataTypeBaseId, int32>> VisibleTypes;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L38 _protected member_ `bool bSupportComposition = false;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGEditableUserParameterDetails.h` (Public)


#### class `FPCGEditableUserParameterDetails`  
`class FPCGEditableUserParameterDetails : public IDetailCustomization, public FTickableEditorObject`  
_L15-35_
- inherits: `IDetailCustomization,FTickableEditorObject`
- desc: A simple Details Customization that will provide a single property from the graph's FInstancePropertyBag
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L23 _public function_ `virtual bool IsAllowedToTick() const override`
- L24 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L25 _public prototype_ `virtual TStatId GetStatId() const override;`
- L29 _private member_ `TWeakPtr<IDetailsView> ParentDetailsView;`
- L30 _private member_ `FPropertyBagPropertyDesc CachedPropertyDesc;`
- L31 _private member_ `TWeakObjectPtr<UPCGGraphInterface> CachedGraphInterface;`
- L34 _private member_ `float TimeUntilRefresh = -1.f;` — Time left until the next details refresh.

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGGraphDetails.h` (Public)


#### class `FPCGGraphDetails`  
`class FPCGGraphDetails : public IDetailCustomization`  
_L10-26_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _public member_ `static const FName DiffViewIdentifier;` — Identifier the diff view sets on its details views (via FDetailsViewArgs::ViewIdentifier) to ask this customization to skip editor-action buttons (Open Graph Parameters, Run Determinism Test) that don't make sense in a read-only diff context.
- L25 _private member_ `TArray<TWeakObjectPtr<UPCGGraph>> SelectedGraphs;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGGraphInstanceDetails.h` (Public)


#### class `FPCGGraphInstanceDetails`  
`class FPCGGraphInstanceDetails : public IDetailCustomization`  
_L13-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L21 _private prototype_ `bool SaveInstanceButtonEnabled() const;`
- L22 _private prototype_ `FReply OnSaveInstanceClicked();`
- L24 _private member_ `TArray<TWeakObjectPtr<UPCGGraphInstance>> SelectedGraphInstances;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGInteractiveToolSettingsDetails.h` (Public)


#### class `FPCGInteractiveToolSettingsDetails`  
`class FPCGInteractiveToolSettingsDetails : public IDetailCustomization`  
_L13-36_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `FPCGInteractiveToolSettingsDetails();`
- L21 _public prototype_ `void RegisterDelegates();`
- L22 _public prototype_ `void UnregisterDelegates();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L27 _private prototype_ `void Rebuild(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L29 _private prototype_ `FText GetResetToolDataButtonText() const;`
- L30 _private prototype_ `EVisibility IsResetToolDataButtonVisible() const;`
- L31 _private prototype_ `FReply ResetToolData() const;`
- L34 _private member_ `TWeakObjectPtr<UPCGInteractiveToolSettings> ToolSettings;`
- L35 _private member_ `TWeakPtr<IDetailLayoutBuilder> DetailLayoutBuilder;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGRaycastFilterRuleCollectionDetails.h` (Public)


#### class `FPCGRaycastFilterRuleCollectionDetails`  
`class FPCGRaycastFilterRuleCollectionDetails : public IPropertyTypeCustomization`  
_L10-30_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — ~Begin IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L24 _protected prototype_ `void OnGenerateRaycastRuleElement(TSharedRef<IPropertyHandle> RaycastRuleArrayElementHandle, int32 ArrayIndex, IDetailChildrenBuilder& DetailChildrenBuilder, TSharedPtr<IPropertyUtilities> PropertyUtilities) const;`
- L26 _protected prototype_ `FPCGRaycastFilterRuleCollection* GetStruct();`
- L27 _protected prototype_ `const FPCGRaycastFilterRuleCollection* GetStruct() const;`
- L29 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

### `Plugins/PCG/Source/PCGEditor/Public/Details/PCGVolumeDetails.h` (Public)


#### class `FPCGVolumeDetails`  
`class FPCGVolumeDetails : public FPCGComponentDetails`  
_L9-19_
- inherits: `FPCGComponentDetails`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _protected prototype_ `virtual TArray<TWeakInterfacePtr<IPCGGraphExecutionSource>> GatherExecutionSourcesFromSelection(const TArray<TWeakObjectPtr<UObject>>& InObjectSelected) const override;` — ~Begin FPCGComponentDetails interface
- L17 _protected function_ `virtual bool AddDefaultProperties() const override`

### `Plugins/PCG/Source/PCGEditor/Public/Managers/PCGEditorInspectionDataManager.h` (Public)


#### struct `FPCGEditorInspectionDataEntry`  
`struct FPCGEditorInspectionDataEntry`  
_L12-22_
- L14 _public member_ `FPCGDataCollection InspectionData;`
- L15 _public member_ `TWeakObjectPtr<const UPCGEditorGraphNodeBase> Node;`
- L16 _public member_ `FName PinName = NAME_None;`
- L17 _public member_ `bool bIsOutputPin = true;`
- L18 _public member_ `FPCGStack Stack;`
- L20 _public prototype_ `bool IsValid() const;`
- L21 _public prototype_ `void Clear();`

#### struct `FPCGEditorInspectionDataEntrySetupParams`  
`struct FPCGEditorInspectionDataEntrySetupParams`  
_L24-47_
- L26 _public function_ `FPCGEditorInspectionDataEntrySetupParams(int32 InEntryIndex, const UPCGEditorGraphNodeBase* InNode, FName InPinName = NAME_None, bool bInIsOutputPin = true) : EntryIndex(InEntryIndex) , Node(InNode) , PinName(InPinName) , bIsOutputPin(bInIsOutputPin)`
- L33 _public function_ `FPCGEditorInspectionDataEntrySetupParams(int32 InEntryIndex, const UPCGEditorGraphNodeBase* InNode, int32 InPinIndex = INDEX_NONE, bool bInIsOutputPin = true) : EntryIndex(InEntryIndex) , Node(InNode) , PinIndex(InPinIndex) , bIsOutputPin(bInIsOutputPin)`
- L40 _public member_ `int32 EntryIndex = INDEX_NONE;`
- L41 _public member_ `const UPCGEditorGraphNodeBase* Node = nullptr;`
- L44 _public member_ `FName PinName = NAME_None;` — If left to NAME_None and PinIndex is INDEX_NONE, by default it will take the first output pin.
- L45 _public member_ `int32 PinIndex = INDEX_NONE;`
- L46 _public member_ `bool bIsOutputPin = true;`

#### class `FPCGEditorInspectionDataManager`  
`class FPCGEditorInspectionDataManager : public TSharedFromThis<FPCGEditorInspectionDataManager>`  
_L57-101_
- inherits: `TSharedFromThis<FPCGEditorInspectionDataManager>`
- desc: Central class that will handle everything related to Inspection Data. Other widgets can ask the manager to get the inspection data for a given node, or change which Execution Source is currently inspected.
- L61 _public member_ `static constexpr int32 NumberOfEntries = 4;` — Hard-coded to 4, as it is how many attribute list view widgets we can have at maximum.
- L63 _public prototype_ `void Cleanup();`
- L65 _public function_ `const FPCGStack& GetStackBeingInspected() const`
- L66 _public prototype_ `void SetStackBeingInspected(const FPCGStack& FullStack);`
- L68 _public function_ `IPCGGraphExecutionSource* GetPCGSourceBeingInspected() const`
- L70 _public prototype_ `void OnSourceGenerated(IPCGGraphExecutionSource* InSource) const;`
- L73 _public function_ `const FPCGDataCollection* GetInspectionData(const FPCGEditorInspectionDataEntrySetupParams& InParams) const` — `UE_DEPRECATED(5.8, "Use GetInspectionDataPtr/InspectData instead")`
- L75 _public prototype_ `const TSharedPtr<FPCGInspectionData> GetInspectionDataPtr(const FPCGEditorInspectionDataEntrySetupParams& InParams) const;`
- L76 _public prototype_ `bool InspectData(const FPCGEditorInspectionDataEntrySetupParams& InParams, TFunctionRef<void(const FPCGDataCollection&)> InspectFunc) const;`
- L78 _public prototype_ `void SetupInspectionEntry(const FPCGEditorInspectionDataEntrySetupParams& InParams);`
- L82 _public prototype_ `const FPCGEditorInspectionDataEntry& GetInspectionEntry(int32 EntryIndex);` — Return the entry at EntryIndex. Must be within 0 and NumberOfEntries - 1. If the entry is invalid at this index, return the first one (so multiple widget would show the same thing).
- L85 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Add UObject references for GC
- L87 _public member_ `FOnInspectedStackChanged OnInspectedStackChangedDelegate;`
- L88 _public member_ `FOnInspectionEntryChanged OnInspectionEntryChangedDelegate;`
- L91 _private prototype_ `void ConstructEntry(const FPCGEditorInspectionDataEntrySetupParams& InParams, FPCGEditorInspectionDataEntry& OutEntry) const;`
- L93 _private prototype_ `bool GetInspectionDataParams(const FPCGEditorInspectionDataEntrySetupParams& InParams, FPCGStack& OutStack, UPCGPin const*& OutPin) const;`
- L95 _private member_ `FPCGSoftGraphExecutionSource PCGSourceBeingInspected;`
- L97 _private member_ `FPCGSoftGraphExecutionSource LastValidPCGSourceBeingInspected;` — Implementation note: we'll keep the last valid source inspected so we don't un-inspect on spurious selection changes
- L98 _private member_ `FPCGStack StackBeingInspected;`
- L100 _private member_ `TStaticArray<FPCGEditorInspectionDataEntry, NumberOfEntries> InspectionEntries;`

#### Free symbols / members of external scopes

- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInspectedStackChanged, const FPCGStack&);`
- L49 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInspectedStackChanged, const FPCGStack&);`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInspectionEntryChanged, const FPCGEditorInspectionDataEntry&, int32);`
- L50 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInspectionEntryChanged, const FPCGEditorInspectionDataEntry&, int32);`

### `Plugins/PCG/Source/PCGEditor/Public/Nodes/PCGEditorGraphNode.h` (Public)


#### class `UPCGEditorGraphNode`  
`class UPCGEditorGraphNode : public UPCGEditorGraphNodeBase`  
_L14-40_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphNodeBase`
- L19 _public member_ `static constexpr int32 MaxNodeNameCharacterCount = 128;`
- L20 _public member_ `static constexpr float MaxNodeTitleWidth = 256.f;`
- L22 _public prototype_ `virtual void Construct(UPCGNode* InPCGNode) override;`
- L25 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L26 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L27 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L28 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L29 _public prototype_ `virtual void OnRenameNode(const FString& NewName) override;`
- L33 _public prototype_ `bool ShouldDrawCompact() const;` — Puts node title on node body, reducing overall node size
- L36 _public prototype_ `bool GetCompactNodeIcon(FName& OutCompactNodeIcon) const;` — Returns custom compact node icon if available
- L39 _public prototype_ `virtual bool OnValidateNodeTitle(const FText& NewName, FText& OutErrorMessage);` — Validate that this is an acceptable name to rename this node.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ENodeTitleType`

### `Plugins/PCG/Source/PCGEditor/Public/Nodes/PCGEditorGraphNodeBase.h` (Public)


#### class `UPCGEditorGraphNodeBase`  
`class UPCGEditorGraphNodeBase : public UEdGraphNode`  
_L33-262_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L38 _public prototype_ `UPCGEditorGraphNodeBase(const FObjectInitializer& ObjectInitializer);`
- L39 _public prototype_ `virtual void Construct(UPCGNode* InPCGNode);`
- L42 _public prototype_ `virtual void BeginDestroy() override;`
- L43 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L44 _public prototype_ `virtual void PostLoad() override;`
- L48 _public prototype_ `virtual void GetNodeContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L49 _public prototype_ `virtual void AutowireNewNode(UEdGraphPin* FromPin) override;`
- L50 _public prototype_ `virtual void PrepareForCopying() override;`
- L51 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const override;`
- L52 _public prototype_ `virtual void ReconstructNode() override;`
- L53 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L54 _public prototype_ `virtual FLinearColor GetNodeBodyTintColor() const override;`
- L55 _public prototype_ `virtual void PostPasteNode() override;`
- L56 _public prototype_ `virtual FText GetTooltipText() const override;`
- L57 _public prototype_ `virtual void GetPinHoverText(const UEdGraphPin& Pin, FString& HoverTextOut) const override;`
- L58 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L59 _public prototype_ `virtual void OnUpdateCommentText(const FString& NewComment) override;`
- L60 _public prototype_ `virtual void OnCommentBubbleToggled(bool bInCommentBubbleVisible) override;`
- L61 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L62 _public prototype_ `virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;`
- L63 _public prototype_ `virtual void FindDiffs(UEdGraphNode* OtherNode, FDiffResults& Results) override;`
- L66 _public prototype_ `bool CanUserAddRemoveDynamicPins(EPCGPinDirection Direction) const;`
- L67 _public prototype_ `void OnUserAddDynamicPin(EPCGPinDirection Direction);`
- L68 _public prototype_ `bool CanUserRemoveDynamicPin(UEdGraphPin* InPinToRemove, EPCGPinDirection Direction) const;`
- L69 _public prototype_ `void OnUserRemoveDynamicPin(UEdGraphPin* InRemovedPin, EPCGPinDirection Direction);`
- L72 _public prototype_ `bool CanUserRenameDynamicPin(UEdGraphPin* InPin) const;` — @todo_pcg: Supports the dynamic pin providers only, not the soon to be deprecated PCGSettingsWithDynamicInputs.
- L73 _public prototype_ `void OnUserRenameDynamicPin(UEdGraphPin* InPin, FName NewLabel);`
- L76 _public prototype_ `void OnUserAddDynamicInputPin();` — @todo_pcg: To be removed with deprecated PCGSettingsWithDynamicInputs
- L77 _public prototype_ `bool CanUserRemoveDynamicInputPin(UEdGraphPin* InPinToRemove) const;`
- L78 _public prototype_ `void OnUserRemoveDynamicInputPin(UEdGraphPin* InRemovedPin);`
- L80 _public prototype_ `void OnConvertNode(const FPCGPreconfiguredInfo& ConversionInfo);`
- L82 _public function_ `UPCGNode* GetPCGNode()`
- L83 _public function_ `const UPCGNode* GetPCGNode() const`
- L84 _public prototype_ `void PostCopy();`
- L85 _public prototype_ `void RebuildAfterPaste();`
- L86 _public prototype_ `virtual void PostPaste();`
- L87 _public prototype_ `void InitNodeGuid();`
- L89 _public prototype_ `void SetInspected(bool bInIsInspecting);`
- L90 _public prototype_ `bool GetInspected() const;`
- L93 _public function_ `void SetIsCulledFromExecution(bool bInIsCulledFromExecution)` — Whether node was culled either during compilation or at execution time.
- L94 _public function_ `bool IsCulledFromExecution() const`
- L96 _public function_ `void SetTriggeredGPUUpload(bool bInTriggeredGPUUpload)`
- L97 _public function_ `bool GetTriggeredGPUUpload() const`
- L99 _public function_ `void SetTriggeredGPUReadback(bool bInTriggeredGPUReadback)`
- L100 _public function_ `bool GetTriggeredGPUReadback() const`
- L102 _public function_ `void SetAppliedDataOverrides(const bool bInAppliedDataOverrides)`
- L103 _public function_ `bool GetAppliedDataOverrides() const`
- L105 _public function_ `void SetHasDefinedOverrides(const bool bInHasDefinedOverrides)`
- L106 _public function_ `bool GetHasDefinedOverrides() const`
- L108 _public function_ `void SetHasOrphanedOverrides(const bool bInHasOrphanedOverrides)`
- L109 _public function_ `bool GetHasOrphanedOverrides() const`
- L112 _public prototype_ `void EnableDeferredReconstruct();` — Increase deferred reconstruct counter, calls to ReconstructNode will flag reconstruct to happen when count hits zero
- L114 _public prototype_ `void DisableDeferredReconstruct();` — Decrease deferred reconstruct counter, ReconstructNode will be called if counter hits zero and the node is flagged for reconstruction
- L117 _public prototype_ `EPCGChangeType UpdateErrorsAndWarnings();` — Pulls current errors/warnings state from PCG subsystem.
- L120 _public prototype_ `EPCGChangeType UpdateStructuralVisualization(const IPCGGraphExecutionSource* InSourceBeingDebugged, const FPCGStack* InStackBeingInspected, bool bNewlyPlaced = false);` — If the currently inspected grid size is smaller than the grid size of this node, display transparent.
- L122 _public prototype_ `EPCGChangeType UpdateGPUVisualization(const IPCGGraphExecutionSource* InSourceBeingDebugged, const FPCGStack* InStackBeingInspected);`
- L124 _public prototype_ `EPCGChangeType UpdateOverrideVisualization(const IPCGGraphExecutionSource* InSourceBeingDebugged, const FPCGStack* InStackBeingInspected);`
- L126 _public prototype_ `bool IsInteractiveNode() const;`
- L129 _public prototype_ `bool IsSettingsDefaultValuesEnabled() const;` — The settings support default value inline constants.
- L132 _public prototype_ `bool IsPinDefaultValueEnabled(FName PinLabel) const;` — The pin has default value inline constants enabled.
- L135 _public prototype_ `bool IsPinDefaultValueActivated(FName PinLabel) const;` — The pin has a default value and is currently active.
- L138 _public prototype_ `void OnUserSetPinDefaultValueActivated(FName PinLabel, bool bIsActivated) const;` — User activated or deactivated the inline constant value.
- L141 _public prototype_ `void ConvertPinDefaultValueMetadataType(FName PinLabel, EPCGMetadataTypes DataType) const;` — User is converting the default value type on the pin.
- L144 _public prototype_ `bool CanConvertToDefaultValueMetadataType(FName PinLabel, EPCGMetadataTypes DataType) const;` — The target type is valid for this pin's default value and this pin is not already this type.
- L147 _public prototype_ `void OnUserResetPinDefaultValue(FName PinLabel, UEdGraphPin* OutPin) const;` — User is resetting the inline constant value back to the default.
- L150 _public prototype_ `bool CanResetPinDefaultValue(FName PinLabel) const;` — The pin can be reset back to the default value.
- L153 _public prototype_ `EPCGMetadataTypes GetPinDefaultValueType(FName PinLabel) const;` — Get the default value type on the pin.
- L156 _public prototype_ `bool HasFlippedTitleLines() const;` — Whether to flip the order of the title lines - display generated title first and authored second.
- L159 _public prototype_ `FText GetAuthoredTitleLine() const;` — Authored part of node title (like "Create Attribute X").
- L162 _public prototype_ `FText GetGeneratedTitleLine() const;` — Generated part of node title, not user editable (like "X = 5.0").
- L165 _public function_ `uint64 GetInactiveOutputPinMask() const` — Bitmask of inactive output pins. Bit N will be set if output pin index N is inactive.
- L168 _public function_ `uint32 GetGenerationGridSize() const` — The grid that this node executes on if higen is enabled, otherwise UninitializedGridSize().
- L171 _public function_ `uint32 GetInspectedGridSize() const` — The higen grid currently being inspected if any, otherwise UninitializedGridSize().
- L174 _public prototype_ `bool IsOutputPinActive(const UEdGraphPin* InOutputPin) const;` — Whether the given output pin was active in the previous execution.
- L177 _public prototype_ `virtual bool IsCompatible(const UPCGPin* InputPin, const UPCGPin* OutputPin, FText& OutReason) const;` — Whether this OutputPin can be connected to this InputPin
- L179 _public prototype_ `UPCGSettings* GetSettings() const;`
- L180 _public prototype_ `IPCGSettingsDefaultValueProvider* GetDefaultValueInterface() const;`
- L181 _public prototype_ `IPCGDynamicPinsProvider* GetDynamicPinsInterface() const;`
- L183 _public prototype_ `DECLARE_DELEGATE(FOnPCGEditorGraphNodeChanged);`
- L184 _public member_ `FOnPCGEditorGraphNodeChanged OnNodeChangedDelegate;`
- L186 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnRequestPinRename, UEdGraphPin*);`
- L187 _public member_ `FOnRequestPinRename OnRequestPinRenameDelegate;`
- L190 _public prototype_ `FLinearColor GetCachedPinColor(const UPCGPin* PCGPin) const;` — Returns the cached wire color for the given pin. Recomputes on first call after any graph change.
- L191 _public function_ `void ClearPinColorCache()`
- L194 _protected prototype_ `static FEdGraphPinType GetPinType(const UPCGPin* InPin);`
- L197 _protected prototype_ `void RebuildEdgesFromPins();` — Create PCG-side edges from editor pins/edges.
- L198 _protected prototype_ `virtual void RebuildEdgesFromPins_Internal();`
- L200 _protected prototype_ `void OnNodeChanged(UPCGNode* InNode, EPCGChangeType ChangeType);`
- L201 _protected prototype_ `void OnPickColor();`
- L202 _protected function_ `virtual bool CanPickColor() const`
- L203 _protected prototype_ `virtual void OnColorPicked(FLinearColor NewColor);`
- L204 _protected prototype_ `void UpdateCommentBubblePinned();`
- L205 _protected prototype_ `void UpdatePosition();`
- L207 _protected prototype_ `void CreatePins(const TArray<UPCGPin*>& InInputPins, const TArray<UPCGPin*>& InOutputPins);`
- L210 _protected function_ `virtual void ReconstructNodeOnChange()` — Performs potentially custom logic when there's a change that would trigger a reconstruct (needed for linked nodes like the named reroutes)
- L214 _protected prototype_ `virtual bool ShouldCreatePin(const UPCGPin* InPin) const;` — Custom logic to hide some pins to the user (by not creating a UI pin, even if the model pin exists). Useful for deprecation
- L217 _protected prototype_ `virtual FText GetPinFriendlyName(const UPCGPin* InPin) const;` — Returns the appropriate pin name to allow for some flexibility
- L220 _protected member_ `TObjectPtr<UPCGNode> PCGNode = nullptr;` — `UPROPERTY()`
- L224 _protected member_ `bool bHasEverBeenConnected = false;` — `UPROPERTY()` — A flag if the node has ever been connected with an edge.
- L226 _protected member_ `int32 DeferredReconstructCounter = 0;`
- L227 _protected member_ `bool bDeferredReconstruct = false;`
- L228 _protected member_ `bool bDisableReconstructFromNode = false;`
- L231 _protected member_ `bool bIsCulledFromExecution = false;` — Whether this node was culled in the last execution.
- L233 _protected member_ `bool bTriggeredGPUUpload = false;`
- L234 _protected member_ `bool bTriggeredGPUReadback = false;`
- L235 _protected member_ `bool bAppliedDataOverrides = false;`
- L236 _protected member_ `bool bHasDefinedOverrides = false;`
- L237 _protected member_ `bool bHasOrphanedOverrides = false;`
- L240 _protected member_ `uint64 InactiveOutputPinMask = 0;` — Bitmask of inactive output pins. Bit N will be set if output pin index N is inactive.
- L243 _protected member_ `uint32 GenerationGridSize = PCGHiGenGrid::UninitializedGridSize();` — The grid that this node executes on if higen is enabled, otherwise UninitializedGridSize().
- L246 _protected member_ `uint32 InspectedGridSize = PCGHiGenGrid::UninitializedGridSize();` — The higen grid currently being inspected if any, otherwise UninitializedGridSize().
- L249 _private member_ `mutable TMap<TObjectKey<UPCGPin>, FLinearColor> CachedPinColors;`
- L254 _public function_ `EPCGHiGenGrid GetGenerationGrid() const` — `UE_DEPRECATED(5.8, "Use GenerationGridSize")`
- L256 _public function_ `EPCGHiGenGrid GetInspectedGenerationGrid() const` — `UE_DEPRECATED(5.8, "Use GetInspectedGridSize")`
- L259 _protected member_ `EPCGHiGenGrid GenerationGrid = EPCGHiGenGrid::Uninitialized;` — `UE_DEPRECATED(5.8, "Use GenerationGridSize")`
- L261 _protected member_ `EPCGHiGenGrid InspectedGenerationGrid = EPCGHiGenGrid::Uninitialized;` — `UE_DEPRECATED(5.8, "Use InspectedGridSize")`

#### struct `FPCGDeferNodeReconstructScope`  
`struct FPCGDeferNodeReconstructScope`  
_L265-310_
- desc: Disables reconstruct on nodes (or from a pin) and re-enables in destructor.
- L267 _public function_ `explicit FPCGDeferNodeReconstructScope(UEdGraphPin* FromPin) : Node(FromPin ? Cast<UPCGEditorGraphNodeBase>(FromPin->GetOwningNode()) : nullptr)`
- L276 _public function_ `explicit FPCGDeferNodeReconstructScope(UPCGEditorGraphNodeBase* InNode) : Node(InNode)`
- L285 _public prototype_ `FPCGDeferNodeReconstructScope(const FPCGDeferNodeReconstructScope&) = delete;`
- L286 _public function_ `FPCGDeferNodeReconstructScope(FPCGDeferNodeReconstructScope&& Other)`
- L292 _public prototype_ `FPCGDeferNodeReconstructScope& operator=(const FPCGDeferNodeReconstructScope&) = delete;`
- L293 _public function_ `FPCGDeferNodeReconstructScope& operator=(FPCGDeferNodeReconstructScope&& Other)`
- L299 _public function_ `~FPCGDeferNodeReconstructScope()`
- L309 _private member_ `UPCGEditorGraphNodeBase* Node = nullptr;`

#### Free symbols / members of external scopes

- L183 _delegate_ `DECLARE_DELEGATE(FOnPCGEditorGraphNodeChanged);`
- L186 _delegate_ `DECLARE_DELEGATE_OneParam(FOnRequestPinRename, UEdGraphPin*);`

### `Plugins/PCG/Source/PCGEditor/Public/PCGComponentVisualizer.h` (Public)


#### struct `HPCGComponentVisualizerHitProxy`  
`struct HPCGComponentVisualizerHitProxy : public HComponentVisProxy`  
_L30-48_
- inherits: `HComponentVisProxy`
- L32 _public prototype_ `DECLARE_HIT_PROXY();`
- L35 _public prototype_ `HPCGComponentVisualizerHitProxy(const UActorComponent* InComponent, const FPCGStack& InPinStack, int32 InDataIndex, int32 InPointIndex);` — Regular point constructor.
- L38 _public prototype_ `HPCGComponentVisualizerHitProxy(const UActorComponent* InComponent, const FPCGStack& InPinStack, const FPCGDeltaKey& InInsertedDeltaKey, int32 InInsertedElementIndex);` — Inserted element constructor.
- L40 _public member_ `FPCGStack PinStack;`
- L41 _public member_ `int32 DataIndex = INDEX_NONE;`
- L42 _public member_ `int32 PointIndex = INDEX_NONE;`
- L45 _public member_ `bool bIsInsertedElement = false;` — Inserted element fields
- L46 _public member_ `int32 InsertedElementIndex = INDEX_NONE;`
- L47 _public member_ `FPCGDeltaKey InsertedDeltaKey;`

#### class `FPCGComponentVisualizer`  
`class FPCGComponentVisualizer : public FComponentVisualizer`  
_L53-213_
- inherits: `FComponentVisualizer`
- L56 _public prototype_ `FPCGComponentVisualizer();`
- L60 _public prototype_ `virtual void OnRegister() override;`
- L61 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L62 _public prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L63 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L64 _public prototype_ `virtual void EndEditing() override;`
- L65 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L66 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;`
- L67 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L68 _public prototype_ `virtual bool HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L69 _public prototype_ `virtual TSharedPtr<SWidget> GenerateContextMenu() const override;`
- L73 _public prototype_ `void RestoreDelta(const FPCGDeltaKey& Key);` — Removes a specific delta by key.
- L76 _public prototype_ `void RestoreAllDeltas();` — Removes all restorable deltas from the active collection (delegates to each extension's CollectRestorableKeys).
- L79 _public prototype_ `void SelectElement(const FPCGDeltaKey& DeltaKey, int32 ElementIndex = INDEX_NONE);` — Selects a delta element by key and optional sub-index. Looks up the extension from the registry.
- L82 _public prototype_ `void ClearActiveSelection();` — Clears the current selection (EditTarget + gizmo). Call before switching active editing nodes.
- L86 _protected prototype_ `void OnGizmoDragged(const FTransform& NewTransform);` — Called each frame while the TRS gizmo is being dragged. Updates the cached selection transform.
- L89 _protected prototype_ `void OnGizmoReleased(const FTransform& FinalTransform);` — Called when the TRS gizmo drag ends. Materializes deferred deltas and applies the final transform.
- L92 _protected prototype_ `void RemoveAllDeltas();` — Removes all deltas from the active editing node's collection and clears the selection.
- L95 _protected prototype_ `void RemoveSelectedDeltas();` — Removes the currently selected delta and clears the selection.
- L98 _protected prototype_ `bool HasSelection() const;` — Returns true if there is a valid PCG component and an active edit target.
- L101 _protected prototype_ `void ResetGizmo();` — Hides and destroys the active TRS gizmo.
- L104 _protected prototype_ `void SetupGizmo(UInteractiveGizmoManager* GizmoManager, const FTransform& InitialTransform);` — Creates a TRS gizmo at the given transform with drag/release callbacks bound to this visualizer.
- L107 _protected prototype_ `void RefreshKeyBindings(IPCGDeltaViewportExtension* Extension);` — Rebuilds the active key bindings from the extension's registered input actions.
- L110 _protected member_ `TSharedPtr<FUICommandList> ComponentVisualizerActions;` — Registered Menu commands
- L112 _protected member_ `TWeakObjectPtr<UPCGNode> ActiveEditingNode;`
- L114 _protected member_ `TWeakObjectPtr<UPCGComponent> LastPCGComponent;`
- L128 _protected member_ `FPCGCachedDeltaContext CachedDeltaContext;`
- L163 _protected member_ `TOptional<FEditState> EditTarget = {};` — Active viewport selection. Set when a delta element is clicked. Reset on deselect or node change.
- L165 _protected member_ `TWeakObjectPtr<UCombinedTransformGizmo> Gizmo;`
- L168 _protected member_ `bool bRegisteredGizmoContextObject = false;` — True if PCG registered the shared transform gizmo context object.
- L171 _protected member_ `TArray<FPCGDeltaKeyBinding> ActiveKeyBindings;` — Key bindings from the active extension, cached when the extension changes.
- L174 _protected member_ `TUniquePtr<PCG::ComponentVisualizer::FCachedMeshWireframe> CachedWireframe;` — Persists across frames to avoid per-frame index buffer copies.
- L177 _protected member_ `TWeakObjectPtr<UStaticMesh> CachedDefaultPointMesh;` — Resolved default point mesh, cached to avoid per-frame LoadSynchronous.
- L201 _protected prototype_ `FManualEditComponentCache* FindOrCreateManualEditComponentCache(const UPCGComponent* InComponent);` — Returns a pointer to the cache entry for InComponent, creating one if it does not exist. NOTE: Pointer may become stale and should be used in scope only.
- L204 _protected prototype_ `void SetupManualEditComponentCacheCallbacks(FManualEditComponentCache& Cache, const UPCGComponent* InComponent);` — Binds component delegate bindings that mark the cache dirty.
- L207 _protected prototype_ `void TeardownManualEditComponentCacheCallbacks(FManualEditComponentCache& Cache, const UPCGComponent* InComponent);` — Releases component delegate bindings. Safe to call even if the component is no longer valid.
- L210 _protected prototype_ `void BuildExecutedNodeStacksCache(FManualEditComponentCache& Cache, const UPCGComponent* InComponent);` — Rebuilds the cache from the component's executed stacks map.
- L212 _protected member_ `TMap<TWeakObjectPtr<const UPCGComponent>, FManualEditComponentCache> ComponentCaches;`

#### struct `FPCGComponentVisualizer::FPCGCachedDeltaContext`  
`struct FPCGCachedDeltaContext`  
_L117-126_
- desc: Cached result of resolving the mutable delta collection for the active editing node. Invalidated when the active node changes.
- L119 _public member_ `FPCGSourceDataContainer* DataContainer = nullptr;`
- L120 _public member_ `FPCGSourceDataStorageKey StorageKey;`
- L121 _public member_ `FPCGStack PinStack;`
- L122 _public member_ `TWeakObjectPtr<UPCGComponent> PCGComponent;`
- L124 _public function_ `bool IsValid() const`
- L125 _public function_ `void Reset()`

#### struct `FPCGComponentVisualizer::FEditState`  
`struct FEditState`  
_L131-160_
- desc: Tracks the state of the currently selected delta element in the viewport, including the owning component, delta key, gizmo transform, and per-extension metadata.
- L133 _public member_ `TWeakObjectPtr<UPCGComponent> PCGComponent;`
- L134 _public member_ `FPCGStack Stack;`
- L135 _public member_ `FPCGSourceDataStorageKey StorageKey;`
- L136 _public member_ `FPCGDeltaKey DeltaKey;`
- L137 _public member_ `bool bWasInDelta = false;`
- L138 _public member_ `FTransform Transform;`
- L139 _public member_ `FTransform OriginalTransform;`
- L141 _public member_ `bool bModified = false;`
- L144 _public member_ `bool bGizmoDragging = false;` — True while the gizmo is actively being dragged. Used to gate the drag wireframe.
- L147 _public member_ `bool bDeltaDeferred = false;` — True when this is a new edit delta that hasn't been stored in the collection yet (deferred until first gizmo move).
- L150 _public member_ `IPCGDeltaViewportExtension* ActiveExtension = nullptr;` — Extension governing this selection's viewport behavior. Null when no delta is active yet (deferred).
- L153 _public member_ `const UScriptStruct* DeltaStructType = nullptr;` — UScriptStruct of the delta type, for registry re-lookups when ActiveExtension is null.
- L156 _public member_ `int32 SelectedElementIndex = INDEX_NONE;` — Index of the selected element within an insertion delta (e.g. which inserted point is selected).
- L159 _public member_ `int32 OriginalPointIndex = INDEX_NONE;` — Original index into the point data array at creation time (for ElementIndex debug field).

#### struct `FPCGComponentVisualizer::FManualEditComponentCache`  
`struct FManualEditComponentCache`  
_L180-195_
- desc: Component derived state cached across frames. Rebuilt when the executed stacks generation changes.
- L188 _public member_ `FDelegateHandle GraphGeneratedHandle;`
- L189 _public member_ `FDelegateHandle GraphCleanedHandle;`
- L191 _public member_ `uint64 PreviousStacksGeneration = 0;`
- L192 _public member_ `bool bDirty = true;`
- L194 _public member_ `TArray<FNodeStacks> ExecutedNodeStacks;`

#### struct `FPCGComponentVisualizer::FManualEditComponentCache::FNodeStacks`  
`struct FNodeStacks`  
_L182-186_
- L184 _public member_ `TWeakObjectPtr<const UPCGNode> Node;`
- L185 _public member_ `TArray<FPCGStack> Stacks;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace PCG`
- L21 _namespace_ `namespace ComponentVisualizer` (scope `PCG`)
- L25 _externvar_ `extern bool GEnableCulling;` (scope `PCG::ComponentVisualizer`)
- L26 _externvar_ `extern float GCullingDistance2D;` (scope `PCG::ComponentVisualizer`)
- L27 _externvar_ `extern bool GFrustumCulling;` (scope `PCG::ComponentVisualizer`)

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditor.h` (Public)


#### enum `EPCGEditorPanel`  
`enum class UE_DEPRECATED(5.8, "Use PCGEditorTabs instead") EPCGEditorPanel`  
_L53-76_
- L55 _public enumerator_ `Attributes1`
- L56 _public enumerator_ `Attributes2`
- L57 _public enumerator_ `Attributes3`
- L58 _public enumerator_ `Attributes4`
- L59 _public enumerator_ `DebugObjectTree`
- L60 _public enumerator_ `Determinism`
- L61 _public enumerator_ `Find`
- L62 _public enumerator_ `GraphEditor`
- L63 _public enumerator_ `Log`
- L64 _public enumerator_ `NodePalette`
- L65 _public enumerator_ `NodeSource`
- L66 _public enumerator_ `Profiling`
- L67 _public enumerator_ `PropertyDetails1`
- L68 _public enumerator_ `PropertyDetails2`
- L69 _public enumerator_ `PropertyDetails3`
- L70 _public enumerator_ `PropertyDetails4`
- L71 _public enumerator_ `UserParams`
- L72 _public enumerator_ `Viewport1`
- L73 _public enumerator_ `Viewport2`
- L74 _public enumerator_ `Viewport3`
- L75 _public enumerator_ `Viewport4`

#### enum `EPCGToolbarButtons`  
`enum class EPCGToolbarButtons`  
_L78-89_
- L80 _public enumerator_ `Find`
- L81 _public enumerator_ `PauseRegen`
- L82 _public enumerator_ `ForceRegen`
- L83 _public enumerator_ `AutoLayoutNodes`
- L84 _public enumerator_ `CancelExecution`
- L85 _public enumerator_ `OpenDebugObjectTreeTab`
- L86 _public enumerator_ `GraphParams`
- L87 _public enumerator_ `GraphSettings`
- L88 _public enumerator_ `Graph`

#### class `FPCGEditor`  
`class FPCGEditor : public FWorkflowCentricApplication, public FGCObject, public FSelfRegisteringEditorUndoClient`  
_L128-714_
- inherits: `FWorkflowCentricApplication,FGCObject,FSelfRegisteringEditorUndoClient`
- L135 _public prototype_ `void InitializePCGEditorGraph(UPCGGraph* InPCGGraph);` — Edits the specified PCGGraph
- L136 _public prototype_ `UPCGEditorGraph* GetOrCreatePCGEditorGraph(UPCGGraph* InPCGGraph);`
- L137 _public prototype_ `void Initialize(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UPCGGraph* InPCGGraph, UObject* InObjectToEdit = nullptr);`
- L141 _public prototype_ `void NavigateTab(FDocumentTracker::EOpenDocumentCause InCause);` — Open a document tab
- L142 _public prototype_ `TSharedPtr<SDockTab> OpenDocument(UPCGGraph* InPCGGraph, FDocumentTracker::EOpenDocumentCause InCause);`
- L143 _public prototype_ `void CloseDocument(UPCGGraph* InPCGGraph);`
- L144 _public prototype_ `FPCGEditor* OpenEditorForGraph(UPCGGraph* InPCGGraph);`
- L145 _public prototype_ `static void OpenAssets(const FAssetOpenArgs& OpenArgs);`
- L148 _public function_ `UPCGEditorGraph* GetPCGEditorGraph()` — `UE_DEPRECATED(5.8, "Use GetMainEditorGraph/GetFocusedEditorGraph instead")`
- L151 _public prototype_ `UPCGEditorGraph* GetMainEditorGraph() const;` — Get the root PCG editor graph being edited.
- L154 _public prototype_ `UPCGEditorGraph* GetFocusedEditorGraph() const;` — Get the focused PCG editor graph being edited. (root or embedded subgraph)
- L157 _public prototype_ `static UPCGEditorGraph* GetPCGEditorGraph(UPCGGraph* InGraph);` — Gets/Creates the PCG graph editor for a given PCG graph
- L158 _public prototype_ `static UPCGEditorGraph* GetPCGEditorGraph(const UPCGNode* InNode);`
- L159 _public prototype_ `static UPCGEditorGraph* GetPCGEditorGraph(const UPCGSettings* InSettings);`
- L162 _public function_ `const UPCGGraph* GetPCGGraph()` — `UE_DEPRECATED(5.8, "Use GetMainGraph/GetFocusedGraph instead")`
- L165 _public prototype_ `UPCGGraph* GetMainGraph() const;` — Get the root PCG graph being edited
- L168 _public prototype_ `UPCGGraph* GetFocusedGraph() const;` — Get the focused PCG graph being edited. (root or embedded subgraph)
- L170 _public prototype_ `virtual UPCGAssetEditorMode* GetAssetEditorMode(int32 Index) const;`
- L173 _public prototype_ `void SetStackBeingInspected(const FPCGStack& FullStack);` — Sets the execution stack that want to inspect.
- L176 _public prototype_ `void SetStackBeingInspectedFromAnotherEditor(const FPCGStack& FullStack);` — Sets the execution stack from another editor, which will set directly in the debug object tree view.
- L179 _public prototype_ `void ClearStackBeingInspected();` — Clear current inspection.
- L183 _public prototype_ `UPCGComponent* GetPCGComponentBeingInspected() const;` — `UE_DEPRECATED(5.7, "Use GetPCGSourceBeingInspected instead")` — Gets the PCG source we are debugging
- L185 _public prototype_ `IPCGGraphExecutionSource* GetPCGSourceBeingInspected() const;`
- L188 _public prototype_ `const FPCGStack* GetStackBeingInspected() const;` — Gets the PCG stack we are inspecting
- L190 _public function_ `FPCGEditorInspectionDataManager& GetInspectionDataManager()`
- L191 _public function_ `const FPCGEditorInspectionDataManager& GetInspectionDataManager() const`
- L193 _public prototype_ `void SetSourceEditorTargetObject(UObject* InObject);`
- L196 _public prototype_ `void JumpToNode(const UEdGraphNode* InNode);` — Focus the graph view on a specific node
- L197 _public prototype_ `void JumpToNode(const UPCGNode* InNode);`
- L202 _public prototype_ `FName GetPanelID(EPCGEditorPanel Panel) const;` — `UE_DEPRECATED(5.8, "Use PCGEditorTabs directly")` — Get the TabID of the editor panel.
- L206 _public prototype_ `void BringFocusToPanel(const FName PanelID) const;` — Focuses the user on a specific panel and flashes the tab.
- L208 _public prototype_ `void CloseGraphPanel(const FName PanelID) const;` — Attempts to close the specific panel if it's open.
- L210 _public prototype_ `bool IsPanelCurrentlyOpen(const FName PanelID) const;` — Returns true if the selected tab is currently open.
- L212 _public prototype_ `bool IsPanelCurrentlyForeground(const FName PanelID) const;` — Returns true if the selected tab is currently open and focused.
- L215 _public prototype_ `virtual bool IsPanelAvailable(const FName PanelID) const;` — Returns true if the panel is available.
- L218 _public prototype_ `virtual IPCGBaseSubsystem* GetSubsystem() const;` — Helper to get to the subsystem.
- L219 _public prototype_ `static UPCGSubsystem* GetWorldSubsystem();`
- L222 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L226 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L227 _public function_ `virtual FString GetReferencerName() const override`
- L234 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;`
- L235 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L236 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L240 _public prototype_ `virtual FText GetToolkitName() const override;`
- L241 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L242 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L243 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L244 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L245 _public prototype_ `virtual void OnClose() override;`
- L246 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L249 _public prototype_ `void SaveEditedObjectState();`
- L250 _public prototype_ `void RestoreEditedObjectState();`
- L262 _public prototype_ `FReply OnSpawnNodeByShortcut(FInputChord InChord, const FVector2D& InPosition, UPCGEditorGraph* InGraph);` — `UE_DEPRECATED(5.6, "Please use the version of the function accepting FVector2f.")` — Handles spawning a graph node in the current graph using the passed in chord. @param	InChord		Chord that was just performed. @param	InPosition	Current cursor position. @param	InGraph		Graph that chord was performed in. @return	FReply	Whether chord was handled.
- L263 _public prototype_ `FReply OnSpawnNodeByShortcut(FInputChord InChord, const FVector2f& InPosition, UPCGEditorGraph* InGraph);`
- L265 _public prototype_ `FActionMenuContent OnCreateActionMenu(UEdGraph* InGraph, const FVector2f& Location, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed OnMenuClosed);`
- L268 _public prototype_ `PCGActionsHelpers::ECompatibilityMask GetContextualCompatibilityMask() const;` — Returns contextual menu filtering mask (no mask, compatible only, accept filtering and/or conversions).
- L271 _public prototype_ `bool CanRunDeterminismGraphTest() const;` — Can determinism be tested on the current graph
- L273 _public prototype_ `void OnDeterminismGraphTest() const;` — Run the determinism test on the current graph
- L276 _public prototype_ `virtual TSubclassOf<UPCGEditorGraphSchema> GetSchemaClass() const;` — Can override the schema used for this editor. By default, it's UPCGEditorSchema.
- L278 _public function_ `UPCGDefaultExecutionSource* GetDefaultExecutionSource() const`
- L280 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreatePaletteTabFactory();`
- L281 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateDebugObjectTreeTabFactory();`
- L282 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateFindTabFactory();`
- L283 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateAttributesTabFactory(int32 Index, TSharedRef<FWorkspaceItem> Group);`
- L284 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateDeterminismTabFactory();`
- L285 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateProfilingTabFactory();`
- L286 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateLogTabFactory();`
- L287 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateCodeEditorTabFactory();`
- L288 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateGraphParamsTabFactory();`
- L289 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreatePropertyDetailsTabFactory(int32 Index, TSharedRef<FWorkspaceItem> Group);`
- L290 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateViewportTabFactory(int32 Index, TSharedRef<FWorkspaceItem> Group);`
- L291 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateEmbeddedSubgraphsTabFactory();`
- L292 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateDataOverridesTabFactory();`
- L295 _public prototype_ `TSharedPtr<FWorkflowTabFactory> CreateNodeSourceTabFactory();` — `UE_DEPRECATED(5.8, "Use CreateCodeEditorTabFactory() instead")`
- L298 _public prototype_ `void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);` — Called when graph editor focus is changed
- L301 _public prototype_ `void OnGraphEditorBackgrounded(const TSharedRef<SGraphEditor>& InGraphEditor);` — Called when the graph editor tab is backgrounded
- L303 _public prototype_ `virtual void OnNodeToolStarted(UPCGEditorGraphNodeBase* InteractiveNode);`
- L304 _public prototype_ `virtual void OnNodeToolEnded(UPCGEditorGraphNodeBase* InteractiveNode);`
- L306 _public prototype_ `void OnGraphPreSave(const UPCGGraph* InGraph);`
- L309 _public prototype_ `void OpenDataOverridesAndInspect(UPCGEditorGraphNodeBase* InNode);` — Brings focus to the Data Overrides tab and sets it to inspect the given node.
- L312 _public prototype_ `void FocusOwningActorInLevelViewport() const;` — Selects the owner actor of the currently inspected PCG component and brings focus to the level viewport.
- L315 _public prototype_ `void SelectManualEditNode(UPCGEditorGraphNodeBase* InNode);` — Selects the given node in the level viewport's manual edit panel.
- L318 _protected prototype_ `virtual void CreateEditorModeManager() override;`
- L320 _protected prototype_ `virtual TAttribute<FGraphAppearanceInfo> GetAppearanceInfo() const;`
- L323 _protected function_ `virtual void RegisterToolbarInternal(FToolMenuSection& PCGSection) const` — `UE_DEPRECATED(5.8, "Implement version with FToolbarBuilder parameter instead")`
- L326 _protected prototype_ `virtual void RegisterToolbarInternal(FToolBarBuilder& ToolbarBuilder) const;` — Register PCG specific toolbar for the editor
- L329 _protected function_ `void RegisterToolbarButton(FToolMenuSection& Section, EPCGToolbarButtons Button) const` — `UE_DEPRECATED(5.8, "Use version with FToolBarBuilder parameter instead")`
- L332 _protected prototype_ `void RegisterToolbarButton(FToolBarBuilder& ToolbarBuilder, EPCGToolbarButtons Button) const;` — Register PCG default editor toolbar button
- L335 _protected prototype_ `virtual void BindCommands();` — Bind commands to delegates
- L337 _protected prototype_ `virtual void OnGraphChanged(UPCGGraphInterface* InGraph, EPCGChangeType ChangeType);`
- L340 _protected prototype_ `virtual void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);` — Called when the selection changes in the GraphEditor
- L347 _protected prototype_ `virtual void OnNodeDoubleClicked(UEdGraphNode* Node);` — Called when a node is double clicked @param Node - The Node that was clicked
- L350 _protected prototype_ `void OnToggleInspected();` — Toggle node inspection state for selected nodes.
- L353 _protected prototype_ `void SetNodeInspected(UPCGEditorGraphNodeBase* InspectedNode, bool bValue);` — Set inspection state for node. Can be null, in that case it will clear inspection.
- L356 _protected prototype_ `virtual bool CanToggleInspected() const;` — Whether we can toggle inspection of selected nodes
- L359 _protected prototype_ `virtual bool CanToggleDebug() const;` — Whether we can toggle debug state of selected nodes
- L362 _protected prototype_ `virtual bool CanToggleEnabled() const;` — Whether we can toggle enabled state of selected nodes
- L365 _protected prototype_ `virtual TSharedRef<SPCGEditorViewport> CreateViewportWidget(int32 Index = 0);` — Create a new viewport widget for the given index. Can be subclassed to have customization around the viewport.
- L368 _protected prototype_ `virtual void SetupModeTools(FAssetEditorModeManager* InModeTools);` — Set up AssetEditorModeManager with required Tool Contexts.
- L371 _protected prototype_ `TSharedPtr<SPCGEditorViewport> GetViewportWidget(int32 Index) const;` — Returns viewport at specified index if it exists, nullptr otherwise
- L374 _protected prototype_ `FAssetEditorModeManager* GetViewportModeManager(int32 Index) const;` — Returns the mode manager for the viewport at specified index, nullptr if not yet created
- L377 _protected prototype_ `bool AutoLayoutFullGraph();` — Auto layout the nodes for better visualization. Returns true if a node has moved.
- L383 _protected member_ `bool bForceRefreshAttributeEvenIfClosed = false;` — `UE_DEPRECATED(all, "Do not use.")` — TO BE REMOVED IN 5.8 @todo_pcg Temporary boolean to force the Attribute List view to Update even if it is closed. To be set in the Editor Ctor.
- L390 _private prototype_ `void RegisterToolbar(FToolBarBuilder& InToolbarBuilder) const;` — Register PCG specific toolbar for the editor
- L393 _private prototype_ `void OnFind();` — Bring up the find tab
- L396 _private prototype_ `void OpenDetailsView();` — Bring up the first free details view, or if they are all locked, the first details view
- L399 _private prototype_ `void OnDetailsViewTabClosed(FName Id, int32 Index);` — Called when a details view tab is closed
- L402 _private prototype_ `void OnAttributeListViewTabClosed(FName Id, int32 Index);` — Called when an attribute list view tab is closed
- L405 _private prototype_ `void OnViewportViewTabClosed(FName Id, int32 Index);` — Called when a viewport view tab is closed
- L408 _private prototype_ `void OnPauseAutomaticRegeneration_Clicked();` — Enable/Disable automatic PCG node generation
- L410 _private prototype_ `bool IsAutomaticRegenerationPaused() const;` — Has the user paused automatic regeneration in the Graph Editor
- L413 _private prototype_ `void OnForceGraphRegeneration_Clicked();` — Force a regeneration by invoking the graph notifications
- L416 _private prototype_ `void OnAutoLayoutNodes_Clicked();` — Auto-Layout nodes in the graph for better layout
- L419 _private prototype_ `ECheckBoxState GetInspectedCheckState() const;` — Whether selected nodes are inspected or not
- L422 _private prototype_ `void OnPermissionChanged(EPCGEditorPermissionMode InPermissionMode);` — Called when editor module permission mode changes
- L424 _private prototype_ `void UpdateAfterInspectedStackChanged(const FPCGStack& FullStack);`
- L427 _private prototype_ `void RefreshEditorNodeVisualization(const IPCGGraphExecutionSource* InSource, const FPCGStack* InStack, EPCGChangeType InitialChangeType) const;` — Refresh visualization on every editor node in the main graph and its embedded subgraphs.
- L430 _private prototype_ `void OnToggleEnabled();` — Toggle node enabled state for selected nodes
- L432 _private prototype_ `ECheckBoxState GetEnabledCheckState() const;` — Whether selected nodes are enabled or not
- L435 _private prototype_ `void OnToggleDebug();` — Toggle node debug state for selected nodes
- L437 _private prototype_ `ECheckBoxState GetDebugCheckState() const;` — Whether selected nodes are being debugged or not
- L440 _private prototype_ `void OnContextualFilteringChanged(ECheckBoxState NewState, const TWeakPtr<SGraphEditorActionMenu> WeakActionMenu, PCGActionsHelpers::ECompatibilityMask AffectedMask);` — Called when the contextual menu filtering toggle is changed.
- L443 _private prototype_ `bool IsContextualFilteringEnabled(PCGActionsHelpers::ECompatibilityMask AffectedMask) const;` — Whether the contextual menu filtering is enabled or not.
- L444 _private prototype_ `ECheckBoxState IsContextualFilteringChecked(PCGActionsHelpers::ECompatibilityMask AffectedMask) const;`
- L447 _private prototype_ `void OnDebugOnlySelected();` — Enable node debug state for selected nodes and disable for others
- L450 _private prototype_ `void OnDisableDebugOnAllNodes();` — Disable node debug state for all nodes
- L453 _private prototype_ `void OnEditInViewport();` — Enable manual viewport editing for the selected node, then select its owning actor and frame the viewport on it.
- L455 _private prototype_ `bool CanToggleViewportEditing() const;` — Returns true if the selected node supports viewport editing.
- L458 _private prototype_ `void OnMarkForViewportEditing();` — Mark/unmark a node for persistent viewport editing.
- L460 _private prototype_ `ECheckBoxState GetMarkForViewportEditingCheckState() const;` — Returns the check box state for whether the selected node is marked for viewport editing.
- L463 _private prototype_ `void NotifyModuleManualEditStateChanged();` — Notify the module to re-evaluate manual edit panel visibility after node state changes
- L466 _private prototype_ `void OnCancelExecution_Clicked();` — Cancels the current execution of the selected graph
- L469 _private prototype_ `bool IsCurrentlyGenerating() const;` — Returns true if inspected graph is currently scheduled or executing
- L472 _private prototype_ `bool IsDebugObjectTreeTabClosed() const;` — Returns true if the debug object tree tab is not currently open.
- L475 _private prototype_ `void OnOpenDebugObjectTreeTab_Clicked();` — Opens the debug object tree tab if it is not open already.
- L478 _private prototype_ `bool CanRunDeterminismNodeTest() const;` — Can determinism be tested on the selected node(s)
- L480 _private prototype_ `void OnDeterminismNodeTest() const;` — Run the determinism test on the selected node(s)
- L483 _private prototype_ `void OnEditGraphSettings();` — Open details view for the PCG object being edited
- L485 _private prototype_ `bool IsEditGraphSettingsToggled() const;` — Whether the PCG object being edited is opened in details view or not
- L488 _private prototype_ `void OnEditGraph_Clicked();` — Open main graph editor
- L490 _private prototype_ `bool IsEditGraphTabClosed() const;` — Whether the main graph editor is opened
- L493 _private prototype_ `void OnToggleGraphParamsPanel() const;` — Open panel to view and edit the graph parameters.
- L495 _private prototype_ `bool IsToggleGraphParamsToggled() const;` — Is the graph params panel open.
- L498 _private prototype_ `void SelectAllNodes();` — Select every node in the graph
- L500 _private prototype_ `bool CanSelectAllNodes() const;` — Whether we can select every node
- L503 _private prototype_ `void DeleteSelectedNodes();` — Delete all selected nodes in the graph
- L505 _private prototype_ `bool CanDeleteSelectedNodes() const;` — Whether we can delete all selected nodes
- L508 _private prototype_ `void CopySelectedNodes();` — Copy all selected nodes in the graph
- L510 _private prototype_ `bool CanCopySelectedNodes() const;` — Whether we can copy all selected nodes
- L513 _private prototype_ `void CutSelectedNodes();` — Cut all selected nodes in the graph
- L515 _private prototype_ `bool CanCutSelectedNodes() const;` — Whether we can cut all selected nodes
- L518 _private prototype_ `void PasteNodes();` — Paste nodes in the graph
- L520 _private prototype_ `void PasteNodesHere(const FVector2D& Location);` — Paste nodes in the graph at location
- L522 _private prototype_ `bool CanPasteNodes() const;` — Whether we can paste nodes
- L525 _private prototype_ `void DuplicateNodes();` — Duplicate the currently selected nodes
- L527 _private prototype_ `bool CanDuplicateNodes() const;` — Whether we are able to duplicate the currently selected nodes
- L530 _private prototype_ `void OnExportNodes();` — Exports node settings to assets
- L533 _private prototype_ `bool CanExportNodes() const;` — Whether we are able to export the currently selected nodes
- L536 _private prototype_ `void OnConvertToStandaloneNodes();` — Converts instanced nodes to independent nodes
- L539 _private prototype_ `bool CanConvertToStandaloneNodes() const;` — Whether we are able to convert the selected nodes to standalone
- L542 _private prototype_ `void OnCollapseNodesInSubgraph(bool bCollapseToEmbeddedSubgraph);` — Collapse the currently selected nodes in a subgraph
- L544 _private prototype_ `bool CanCollapseNodesInSubgraph(bool bCollapseToEmbeddedSubgraph) const;` — Whether we can collapse nodes in a subgraph
- L547 _private prototype_ `void OnAddDynamicPin(EPCGPinDirection Direction);` — User is attempting to add a dynamic pin in the given direction to a node.
- L549 _private prototype_ `bool CanAddDynamicPin(EPCGPinDirection Direction) const;` — Returns true if the user can add a dynamic pin in the given direction to the selected node.
- L552 _private prototype_ `void OnRenameNode();` — User is attempting to rename a node
- L554 _private prototype_ `bool CanRenameNode() const;` — Whether the user can rename the selected node
- L557 _private prototype_ `void OnSelectNamedRerouteUsages();` — Selects the associated usages of a given reroute declaration
- L559 _private prototype_ `bool CanSelectNamedRerouteUsages() const;` — Whether the user can find the usages from the selection
- L562 _private prototype_ `void OnSelectNamedRerouteDeclaration();` — Selects the associated declaration of a given reroute usage
- L564 _private prototype_ `bool CanSelectNamedRerouteDeclaration() const;` — Whether the user can find the declaration from the selection
- L567 _private prototype_ `void OnJumpToSource();` — Jumps to source definition for the selected nodes.
- L570 _private prototype_ `bool InternalValidationOnAction();` — Internal method that validates a few things (& logs errors) prior to executing actions.
- L573 _private prototype_ `UPCGEditorGraphNodeBase* GetEditorNode(const UPCGNode* InNode);` — Finds editor graph node that matches the provided PCG node
- L575 _private prototype_ `void OnAlignTop();`
- L576 _private prototype_ `void OnAlignMiddle();`
- L577 _private prototype_ `void OnAlignBottom();`
- L578 _private prototype_ `void OnAlignLeft();`
- L579 _private prototype_ `void OnAlignCenter();`
- L580 _private prototype_ `void OnAlignRight();`
- L581 _private prototype_ `void OnStraightenConnections();`
- L582 _private prototype_ `void OnDistributeNodesH();`
- L583 _private prototype_ `void OnDistributeNodesV();`
- L584 _private prototype_ `void OnCreateComment();`
- L587 _private prototype_ `TSharedPtr<SGraphEditor> GetFocusedGraphEditorWidget() const;` — Get or Create new Graph editor widget
- L588 _private prototype_ `void CreateGraphEditorCommands();`
- L589 _private prototype_ `TSharedRef<SGraphEditor> CreateGraphEditorWidget(TSharedPtr<FTabInfo> InTabInfo, UPCGEditorGraph* InGraph);`
- L592 _private prototype_ `TSharedRef<SPCGEditorGraphNodePalette> GetOrCreatePaletteWidget();` — Get or Create palette widget
- L595 _private prototype_ `TSharedRef<SPCGEditorGraphDebugObjectTree> GetOrCreateDebugObjectTreeWidget();` — Get or Create new debug object tree widget
- L598 _private prototype_ `TSharedRef<SPCGEditorGraphFind> GetOrCreateFindWidget();` — Get or Create new find widget
- L601 _private prototype_ `TSharedRef<SPCGEditorGraphAttributeListView> GetOrCreateAttributesWidget(int32 Index);` — Get or Create new attributes widget
- L604 _private prototype_ `TSharedRef<SPCGEditorGraphDeterminismListView> GetOrCreateDeterminismWidget();` — Get or Create a new determinism tab widget
- L607 _private prototype_ `TSharedRef<SPCGEditorGraphProfilingView> GetOrCreateProfilingWidget();` — Get or Create a new profiling tab widget
- L610 _private prototype_ `TSharedRef<SPCGEditorGraphLogView> GetOrCreateLogWidget();` — Get or Create a new log capture tab widget
- L613 _private prototype_ `TSharedRef<SPCGCodeEditor> GetOrCreateCodeEditorWidget();` — Get or Create a new code editor tab widget
- L616 _private prototype_ `TSharedRef<SPCGEditorGraphUserParametersView> GetOrCreateGraphParamsWidget();` — Get or Create a new user graph parameters tab widget
- L619 _private prototype_ `TSharedRef<SPCGEditorGraphDetailsView> GetOrCreatePropertyDetailsWidget(int32 Index);` — Get or Create a new details tab widget
- L622 _private prototype_ `TSharedRef<SPCGEditorViewport> GetOrCreateViewportWidget(int32 Index);` — Get or Create a new viewport tab widget
- L625 _private prototype_ `TSharedRef<SPCGEditorGraphEmbeddedSubgraphsView> GetOrCreateEmbeddedSubgraphsWidget();` — Get or Create a new embedded subgraphs tab widget
- L628 _private prototype_ `TSharedRef<SPCGEditorGraphDataOverridesView> GetOrCreateDataOverridesWidget();` — Get or Create a new data overrides tab widget
- L631 _private prototype_ `void OnSourceGenerated(IPCGGraphExecutionSource* InSource);` — Called when the component inspected is generated/cleaned
- L634 _private prototype_ `bool OnValidateNodeTitle(const FText& NewName, UEdGraphNode* GraphNode, FText& OutErrorMessage);` — Called to validate a node title change.
- L637 _private prototype_ `void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);` — Called when the title of a node is changed
- L644 _private prototype_ `void JumpToDefinition(const UClass* Class) const;` — Try to jump to a given class (if allowed) @param Class - The Class to jump to
- L647 _private prototype_ `void OnSourceUnregistered(IPCGGraphExecutionSource* Source);` — Called when a PCG execution source unregisters.
- L650 _private prototype_ `void OnSourceGenerationDone(IPCGBaseSubsystem* Subsystem, IPCGGraphExecutionSource* Source, EPCGGenerationStatus Status);` — Called when a component finishes executing. Useful for updating debugging tools/UIs.
- L653 _private prototype_ `void UpdateDebugAfterSourceSelection(IPCGGraphExecutionSource* InOldSource, IPCGGraphExecutionSource* InNewSource, bool bNewSourceStartedInspecting);` — Trigger any generation required to ensure debug display is up to date.
- L655 _private prototype_ `void RegisterDelegatesForWorld(UWorld* World);`
- L656 _private prototype_ `void UnregisterDelegatesForWorld(UWorld* World);`
- L658 _private prototype_ `void OnNodeSourceCompiled(const UPCGNode* InNode, const FPCGCompilerDiagnostics& InDiagnostics);`
- L660 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InMapChangedType);`
- L661 _private prototype_ `void OnPostPIEStarted(bool bIsSimulating);`
- L662 _private prototype_ `void OnEndPIE(bool bIsSimulating);`
- L663 _private prototype_ `void OnGraphExecutionSourcesChanged();`
- L665 _private prototype_ `void RefreshViews();`
- L667 _private prototype_ `void UpdateDefaultExecutionSource();`
- L668 _private prototype_ `void ReleaseDefaultExecutionSource(bool bCollectGarbage = false);`
- L670 _private prototype_ `void CloseInvalidDocuments();`
- L672 _private prototype_ `virtual TSharedRef<FTabManager::FLayout> GetDefaultLayout() const;`
- L673 _private function_ `virtual void RegisterExtraTabFactories(FWorkflowAllowedTabSet& TabSet)`
- L675 _private member_ `TSharedPtr<SGraphEditor> GraphEditorWidget;`
- L676 _private member_ `TSharedPtr<SPCGEditorGraphDetailsView> PropertyDetailsWidgets[PCGEditorTabs::NumPropertyDetailTabs];`
- L677 _private member_ `TSharedPtr<SPCGEditorGraphNodePalette> PaletteWidget;`
- L678 _private member_ `TSharedPtr<SPCGEditorGraphDebugObjectTree> DebugObjectTreeWidget;`
- L679 _private member_ `TSharedPtr<SPCGEditorGraphFind> FindWidget;`
- L680 _private member_ `TSharedPtr<SPCGEditorGraphAttributeListView> AttributesWidgets[PCGEditorTabs::NumAttributeTabs];`
- L681 _private member_ `TSharedPtr<SPCGEditorGraphDeterminismListView> DeterminismWidget;`
- L682 _private member_ `TSharedPtr<SPCGEditorGraphProfilingView> ProfilingWidget;`
- L683 _private member_ `TSharedPtr<SPCGEditorGraphLogView> LogWidget;`
- L684 _private member_ `TSharedPtr<SPCGCodeEditor> CodeEditorWidget;`
- L685 _private member_ `TSharedPtr<SPCGEditorGraphUserParametersView> UserParamsWidget;`
- L686 _private member_ `TSharedPtr<SPCGEditorViewport> ViewportWidgets[PCGEditorTabs::NumViewportTabs];`
- L687 _private member_ `TSharedPtr<FAssetEditorModeManager> ViewportModeManagers[PCGEditorTabs::NumViewportTabs];`
- L688 _private member_ `TSharedPtr<SPCGEditorGraphEmbeddedSubgraphsView> EmbeddedSubgraphsWidget;`
- L689 _private member_ `TSharedPtr<SPCGEditorGraphDataOverridesView> DataOverridesWidget;`
- L691 _private member_ `int32 ActiveToolViewportIndex = INDEX_NONE;`
- L693 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;`
- L695 _private member_ `TObjectPtr<UPCGDefaultExecutionSource> PCGDefaultExecutionSource = nullptr;`
- L697 _private member_ `TObjectPtr<UPCGGraph> MainGraph = nullptr;`
- L698 _private member_ `TWeakPtr<SGraphEditor> FocusedGraphEditor = nullptr;`
- L700 _private member_ `FPCGEditorInspectionDataManager InspectionDataManager;`
- L704 _private member_ `TOptional<TPair<const IPCGGraphExecutionSource*, EPCGGenerationStatus>> LastExecutionStatus;` — Keep track of the last execution status to be able to break infinite loop when a source is triggered to be generated by inspection aborted and re-triggered.
- L707 _private member_ `TSharedPtr<FDocumentTracker> DocumentManager;` — Document manager for workflow tabs
- L710 _private member_ `TWeakPtr<FDocumentTabFactory> DocumentTabFactory;` — Factory that spawns graph editors; used to look up all tabs spawned by it.
- L713 _private member_ `PCGActionsHelpers::ECompatibilityMask ContextualActionMask = PCGActionsHelpers::ECompatibilityMask::Compatible;` — Contextual menu filter toggle state variable. Starts as compatible only to show more likely choices.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ETextCommit`
- L51 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInspectedNodeChanged, UPCGEditorGraphNodeBase*);`
- L51 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnInspectedNodeChanged, UPCGEditorGraphNodeBase*);`
- L91 _namespace_ `namespace PCGEditorTabs`
- L93 _variable_ `constexpr FLazyName GraphEditorID = TEXT("Gra` (scope `PCGEditorTabs`)
- L94 _variable_ `constexpr FLazyName PropertyDetailsID[] = { TEXT("PropertyDetails"), TEXT("PropertyDetails2"), TEXT("PropertyDetails3"), TEXT("Prope` (scope `PCGEditorTabs`)
- L99 _variable_ `constexpr FLazyName PaletteID = TEXT("Pal` (scope `PCGEditorTabs`)
- L100 _variable_ `constexpr FLazyName DebugObjectID = TEXT("Deb` (scope `PCGEditorTabs`)
- L101 _variable_ `constexpr FLazyName AttributesID[] = { TEXT("Attributes"), TEXT("Attributes2"), TEXT("Attributes3"), TEXT("Attri` (scope `PCGEditorTabs`)
- L106 _variable_ `constexpr FLazyName FindID = TEXT("Fin` (scope `PCGEditorTabs`)
- L107 _variable_ `constexpr FLazyName DeterminismID = TEXT("Det` (scope `PCGEditorTabs`)
- L108 _variable_ `constexpr FLazyName ProfilingID = TEXT("Pro` (scope `PCGEditorTabs`)
- L109 _variable_ `constexpr FLazyName LogID = TEXT("Log` (scope `PCGEditorTabs`)
- L110 _variable_ `constexpr FLazyName UserParamsID = TEXT("Use` (scope `PCGEditorTabs`)
- L111 _variable_ `constexpr FLazyName ViewportID[] = { TEXT("Viewport"), TEXT("Viewport2"), TEXT("Viewport3"), TEXT("Viewp` (scope `PCGEditorTabs`)
- L116 _variable_ `constexpr FLazyName EmbeddedSubgraphsID = TEXT("Emb` (scope `PCGEditorTabs`)
- L117 _variable_ `constexpr FLazyName CodeEditorID = TEXT("Cod` (scope `PCGEditorTabs`)
- L118 _variable_ `constexpr FLazyName DataOverridesID = TEXT("Dat` (scope `PCGEditorTabs`)
- L120 _variable_ `constexpr int32 NumPropertyDetailTabs = sizeof(PropertyDetailsID) / sizeof(FLazyName);` (scope `PCGEditorTabs`)
- L121 _variable_ `constexpr int32 NumAttributeTabs = sizeof(AttributesID) / sizeof(FLazyName);` (scope `PCGEditorTabs`)
- L122 _variable_ `constexpr int32 NumViewportTabs = sizeof(ViewportID) / sizeof(FLazyName);` (scope `PCGEditorTabs`)
- L125 _variable_ `constexpr FLazyName HLSLSourceID = TEXT("HLS` (scope `PCGEditorTabs`) — `UE_DEPRECATED(5.8, "Use CodeEditorID instead.")`

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorCommands.h` (Public)


#### class `FPCGEditorCommands`  
`class FPCGEditorCommands : public TCommands<FPCGEditorCommands>`  
_L13-52_
- inherits: `TCommands<FPCGEditorCommands>`
- L16 _public prototype_ `FPCGEditorCommands();`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> CollapseNodes;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> CollapseNodesToEmbeddedSubgraph;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> ExportNodes;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ConvertToStandaloneNodes;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> Find;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ShowSelectedDetails;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> PauseAutoRegeneration;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ForceGraphRegeneration;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> AutoLayoutNodes;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> OpenDebugObjectTreeTab;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> RunDeterminismNodeTest;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> RunDeterminismGraphTest;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> EditGraphSettings;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> EditGraph;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ToggleGraphParams;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CancelExecution;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleEnabled;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ToggleDebug;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> DebugOnlySelected;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> DisableDebugOnAllNodes;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleInspect;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> AddInputPin;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> AddOutputPin;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> RenameNode;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> SelectNamedRerouteUsages;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> SelectNamedRerouteDeclaration;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> JumpToSource;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> AutoFocusViewport;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> EditInViewport;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> MarkForViewportEditing;`

#### struct `FPCGSpawnNodeCommandInfo`  
`struct FPCGSpawnNodeCommandInfo`  
_L54-81_
- L56 _public function_ `explicit FPCGSpawnNodeCommandInfo(TSubclassOf<UPCGSettings> PCGSettingsClass) : PCGSettingsClass(PCGSettingsClass)`
- L59 _public member_ `FPCGPreConfiguredSettingsInfo PreconfiguredInfo;` — Optional preconfigured settings info for a specific configuration of the node.
- L62 _public member_ `TSharedPtr<FUICommandInfo> CommandInfo;` — Holds the UI Command to verify chords for this action are held.
- L69 _public prototype_ `TSharedPtr<FEdGraphSchemaAction> GetAction() const;` — Creates an action to be used for placing a node into the graph. @return A fully prepared action containing the information to spawn the node.
- L76 _public function_ `UClass* GetClass() const` — Gets the PCG Settings class of the spawn node action. @return The PCG Settings class of the spawn node action.
- L80 _private member_ `TSubclassOf<UPCGSettings> PCGSettingsClass;` — Type of settings class (node) to spawn.

#### class `FPCGEditorSpawnNodeCommands`  
`class FPCGEditorSpawnNodeCommands : public TCommands<FPCGEditorSpawnNodeCommands>`  
_L84-106_
- inherits: `TCommands<FPCGEditorSpawnNodeCommands>`
- desc: Handles spawn node commands for the PCG Graph Editor.
- L87 _public function_ `FPCGEditorSpawnNodeCommands() : TCommands(TEXT("PCGEditorSpawnNodes"), NSLOCTEXT("PCGEditorSpawnNodes", "PCGEditorSpawnNodes", "PCG Editor - Spawn Nodes"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L92 _public prototype_ `virtual void RegisterCommands() override;`
- L101 _public prototype_ `TSharedPtr<FEdGraphSchemaAction> GetGraphActionByChord(const FInputChord& InChord) const;` — Returns a graph action assigned to the passed in chord @param InChord		The chord to use for lookup. @return				A shared pointer to the schema action.
- L105 _private member_ `TArray<TSharedPtr<FPCGSpawnNodeCommandInfo>> SpawnNodeCommands;` — An array of all the possible commands for spawning nodes.

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorCommon.h` (Public)


#### enum `EPCGElementType`  
`enum class EPCGElementType : uint8`  
_L13-22_
- reflection: `UENUM()`
- L15 _public enumerator_ `Native = 1 << 0`
- L16 _public enumerator_ `Blueprint = 1 << 1`
- L17 _public enumerator_ `Subgraph = 1 << 2`
- L18 _public enumerator_ `Settings = 1 << 3`
- L19 _public enumerator_ `Asset = 1 << 4`
- L20 _public enumerator_ `Other = 1 << 5`
- L21 _public enumerator_ `All = (1 << 6) - 1`

#### struct `FPCGEditorCommonDummyStruct`  
`struct FPCGEditorCommonDummyStruct`  
_L27-30_
- reflection: `USTRUCT()`
- desc: Used to make sure UHT generates properly

#### Free symbols / members of external scopes

- L10 _macro_ `#define LOCTEXT_NAMESPACE "PCGEditorCommon"`
- L23 _prototype_ `ENUM_CLASS_FLAGS(EPCGElementType);`
- L32 _namespace_ `namespace FPCGEditorCommon`
- L34 _variable_ `const FString ContextIdentifier = TEXT("PCG` (scope `FPCGEditorCommon`)
- L36 _variable_ `const FName SpatialDataType = FName(TEXT("Spat` (scope `FPCGEditorCommon`)
- L37 _variable_ `const FName ParamDataType = FName(TEXT("Attr` (scope `FPCGEditorCommon`)
- L38 _variable_ `const FName SettingsDataType = FName(TEXT("Sett` (scope `FPCGEditorCommon`)
- L39 _variable_ `const FName OtherDataType = FName(TEXT("Othe` (scope `FPCGEditorCommon`)
- L41 _variable_ `const FName ConcreteDataType = FName(TEXT("Conc` (scope `FPCGEditorCommon`)
- L42 _variable_ `const FName PointDataType = FName(TEXT("Poin` (scope `FPCGEditorCommon`)
- L43 _variable_ `const FName PolyLineDataType = FName(TEXT("Poly` (scope `FPCGEditorCommon`)
- L44 _variable_ `const FName SurfaceDataType = FName(TEXT("Surf` (scope `FPCGEditorCommon`)
- L45 _variable_ `const FName LandscapeDataType = FName(TEXT("Land` (scope `FPCGEditorCommon`)
- L46 _variable_ `const FName BaseTextureDataType = FName(TEXT("Base` (scope `FPCGEditorCommon`)
- L47 _variable_ `const FName TextureDataType = FName(TEXT("Text` (scope `FPCGEditorCommon`)
- L48 _variable_ `const FName RenderTargetDataType = FName(TEXT("Rend` (scope `FPCGEditorCommon`)
- L49 _variable_ `const FName VirtualTextureDataType = FName(TEXT("Virt` (scope `FPCGEditorCommon`)
- L50 _variable_ `const FName VolumeDataType = FName(TEXT("Volu` (scope `FPCGEditorCommon`)
- L51 _variable_ `const FName PrimitiveDataType = FName(TEXT("Prim` (scope `FPCGEditorCommon`)
- L52 _variable_ `const FName DynamicMeshDataType = FName(TEXT("Dyna` (scope `FPCGEditorCommon`)
- L53 _variable_ `const FName StaticMeshResourceDataType = FName(TEXT("Stat` (scope `FPCGEditorCommon`)
- L55 _externvar_ `extern TAutoConsoleVariable<bool> CVarShowAdvancedAttributesFields;` (scope `FPCGEditorCommon`)
- L57 _variable_ `const FAssetCategoryPath PCGAssetCategoryPath(LOCTEXT("PCGCateg` (scope `FPCGEditorCommon`)
- L58 _variable_ `const FAssetCategoryPath PCGAssetSubCategoryPath(FPCGEditorCommon::PCGAssetCategoryPath, LOCTEXT("PCGSubCategory", "PCG"), ECategoryMe` (scope `FPCGEditorCommon`)
- L59 _variable_ `const FAssetCategoryPath PCGAdvancedAssetCategoryPath(FPCGEditorCommon::PCGAssetCategoryPath, LOCTEXT("PCGAvanc` (scope `FPCGEditorCommon`)
- L61 _namespace_ `namespace Helpers` (scope `FPCGEditorCommon`)
- L63 _prototype_ `void DispatchEditorToast(const FText& Text, const FText& SubText = FText{}, const float Duration = 3.f);` (scope `FPCGEditorCommon::Helpers`)

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorMenuUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PCGEditorMenuUtils`
- L10 _prototype_ `FToolMenuSection& CreatePCGSection(UToolMenu* Menu);` (scope `PCGEditorMenuUtils`)
- L11 _prototype_ `void CreateOrUpdatePCGAssetFromMenu(UToolMenu* Menu, TArray<FAssetData>& Assets);` (scope `PCGEditorMenuUtils`)

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorModule.h` (Public)


#### class `FPCGEditorModule`  
`class FPCGEditorModule : public IPCGEditorModule`  
_L31-148_
- inherits: `IPCGEditorModule`
- L35 _public prototype_ `virtual void StartupModule() override;`
- L36 _public prototype_ `virtual void ShutdownModule() override;`
- L37 _public prototype_ `virtual bool SupportsDynamicReloading() override;`
- L41 _public prototype_ `virtual TWeakPtr<IPCGEditorProgressNotification> CreateProgressNotification(const FTextFormat& TextFormat, bool bCanCancel) override;`
- L42 _public prototype_ `virtual void ReleaseProgressNotification(TWeakPtr<IPCGEditorProgressNotification> InNotification) override;`
- L43 _public prototype_ `virtual void SetOutlinerUIRefreshDelay(float InDelay) override;`
- L44 _public function_ `virtual const FPCGNodeVisualLogs& GetNodeVisualLogs() const override`
- L45 _public function_ `virtual FPCGNodeVisualLogs& GetNodeVisualLogsMutable() override`
- L46 _public prototype_ `virtual bool CanSelectPartitionActors() const override;`
- L47 _public prototype_ `virtual void SetPermissionMode(EPCGEditorPermissionMode InPermissionMode) override;`
- L48 _public function_ `virtual EPCGEditorPermissionMode GetPermissionMode() const`
- L49 _public prototype_ `virtual void TransferPropertyBagMetadataIntoHierarchy(UPCGGraph* Graph) const override;`
- L50 _public prototype_ `virtual UObject* CreatePropertyBagHierarchyRootObject(UPCGGraph* Graph) const override;`
- L51 _public prototype_ `virtual void ConnectPropertyBagHierarchyRootObjectModifyDelegate(UPCGGraph* Graph) const override;`
- L52 _public prototype_ `virtual void GraphIsBeingDestroyed(UPCGGraph* Graph) const override;`
- L54 _public prototype_ `static const FPCGDeltaVisualizationRegistry& GetConstDeltaVisualizationRegistry();`
- L55 _public prototype_ `static FPCGDeltaVisualizationRegistry& GetMutableDeltaVisualizationRegistry();`
- L56 _public prototype_ `static const FPCGDeltaViewportExtensionRegistry& GetConstDeltaViewportExtensionRegistry();`
- L57 _public prototype_ `static FPCGDeltaViewportExtensionRegistry& GetMutableDeltaViewportExtensionRegistry();`
- L59 _public prototype_ `DECLARE_DERIVED_EVENT(FPCGEditorModule, IPCGEditorModule::FPermissionModeChanged, FPermissionModeChanged);`
- L60 _public function_ `virtual FPermissionModeChanged& OnPermissionModeChanged() override`
- L62 _public prototype_ `void UpdateManualEditPanelVisibility();`
- L65 _public prototype_ `TSharedPtr<SPCGManualEditPanel> GetManualEditPanel() const;` — Returns the manual edit panel if one is currently active, or nullptr.
- L68 _protected prototype_ `virtual void OnScheduleGraph(const FPCGStackContext& StackContext) override;`
- L69 _protected prototype_ `virtual void OnGraphPreSave(UPCGGraph* Graph, FObjectPreSaveContext ObjectSaveContext) override;`
- L70 _protected prototype_ `virtual void ClearExecutionMetadata(IPCGGraphExecutionSource* InSource) override;`
- L71 _protected prototype_ `virtual void ClearExecutedStacks(const IPCGGraphExecutionSource* InRootSource) override;`
- L72 _protected prototype_ `virtual void ClearExecutedStacks(const UPCGGraph* InContainingGraph) override;`
- L73 _protected prototype_ `virtual TArray<FPCGStackSharedPtr> GetExecutedStacksPtrs(const FPCGStack& BeginningWithStack) override;`
- L74 _protected prototype_ `virtual TArray<FPCGStackSharedPtr> GetExecutedStacksPtrs(const IPCGGraphExecutionSource* InSource, const UPCGGraph* InSubgraph, bool bOnlyWithSubgraphAsCurrentFrame) override;`
- L75 _protected prototype_ `virtual void NotifyGraphChanged(UPCGGraph* InGraph, EPCGChangeType ChangeType) override;`
- L78 _protected prototype_ `void RegisterDetailsCustomizations();`
- L79 _protected prototype_ `void UnregisterDetailsCustomizations();`
- L80 _protected prototype_ `void RegisterMenuExtensions();`
- L81 _protected prototype_ `void UnregisterMenuExtensions();`
- L82 _protected prototype_ `void PopulateMenuActions(FMenuBuilder& MenuBuilder);`
- L83 _protected prototype_ `void RegisterSettings();`
- L84 _protected prototype_ `void UnregisterSettings();`
- L85 _protected prototype_ `void RegisterPCGDataVisualizations();`
- L86 _protected prototype_ `void UnregisterPCGDataVisualizations();`
- L87 _protected prototype_ `void RegisterDeltaVisualizations();`
- L88 _protected prototype_ `void UnregisterDeltaVisualizations();`
- L89 _protected prototype_ `void RegisterDeltaViewportExtensions();`
- L90 _protected prototype_ `void UnregisterDeltaViewportExtensions();`
- L91 _protected prototype_ `void RegisterPinColorAndIcons();`
- L92 _protected prototype_ `void UnregisterPinColorAndIcons();`
- L93 _protected prototype_ `void RegisterTrackerFactories();`
- L94 _protected prototype_ `void UnregisterTrackerFactories();`
- L96 _protected prototype_ `void OnLevelEditorCreated(TSharedPtr<ILevelEditor> InLevelEditor);`
- L97 _protected prototype_ `void RegisterOnEditorModeChange();`
- L100 _protected prototype_ `void OnEditorInitialized(double Duration);` — Discovers all UPCGAssetEditorInteractiveTool subclasses and registers them. Bound to FEditorDelegates::OnEditorInitialized so all plugins are loaded first.
- L102 _protected prototype_ `void OnPostEngineInit();`
- L103 _protected prototype_ `void OnPreExit();`
- L105 _protected prototype_ `void ExtendShowFlagsMenu();`
- L106 _protected prototype_ `static int32 GetTreatEditorViewportAsGenerationSourceValue();`
- L107 _protected prototype_ `static void OnTreatEditorViewportAsGenerationSourceValueChanged(int32 Value, ESelectInfo::Type SelectInfo);`
- L112 _protected prototype_ `void OnSceneMaterialsModified();` — [EXPERIMENTAL] Used to refresh procedural instances when materials are modified which can otherwise be lost. Note: This function subject to change/removal without deprecation.
- L114 _protected prototype_ `bool ShouldDisableCPUThrottling();`
- L116 _protected prototype_ `virtual bool ShouldTreatViewportAsGenerationSourceInternal(const APCGWorldActor* InPCGWorldActor) const override;`
- L118 _protected member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L119 _protected member_ `static EAssetTypeCategories::Type PCGAssetCategory;`
- L121 _protected member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L122 _protected member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L124 _protected member_ `TSharedPtr<FPCGEditorGraphNodeFactory> GraphNodeFactory;`
- L126 _protected member_ `FDelegateHandle ShouldDisableCPUThrottlingDelegateHandle;`
- L128 _protected member_ `TSet<TSharedPtr<IPCGEditorProgressNotification>> ActiveNotifications;`
- L130 _protected member_ `FPCGNodeVisualLogs NodeVisualLogs;`
- L133 _protected member_ `TSet<FPCGStackSharedPtr> ExecutedStacks;` — A record of stacks that were executed. Used to populate debugging tool UIs.
- L134 _protected member_ `TMap<FPCGSoftGraphExecutionSource, TSet<FPCGStackSharedPtr>> ExecutedStacksPerSource;`
- L135 _protected member_ `mutable PCG::FSharedLock ExecutedStacksLock;`
- L137 _protected member_ `EPCGEditorPermissionMode PermissionMode = EPCGEditorPermissionMode::All;`
- L138 _protected member_ `FPermissionModeChanged PermissionModeChangedEvent;`
- L140 _protected member_ `TUniquePtr<FPCGLoadDataAssetChangeTracker> LoadDataAssetChangeTracker;`
- L142 _protected member_ `TArray<FName> VisualizersToUnregisterOnShutdown;`
- L144 _protected member_ `TUniquePtr<FPCGManualEditPanelManager> ManualEditPanelManager;`
- L146 _protected member_ `FPCGDeltaVisualizationRegistry DeltaVisualizationRegistry;`
- L147 _protected member_ `FPCGDeltaViewportExtensionRegistry DeltaViewportExtensionRegistry;`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGEditor, Log, All);` — Logs
- L25 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGEditor, Log, All);` — Logs
- L59 _delegate_ `DECLARE_DERIVED_EVENT(FPCGEditorModule, IPCGEditorModule::FPermissionModeChanged, FPermissionModeChanged);`

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorSettings.h` (Public)


#### enum `EPCGEditorDoubleClickAction`  
`enum class EPCGEditorDoubleClickAction : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `DoNothing`
- L20 _public enumerator_ `ToggleInspectNode UMETA(DisplayName = "Toggle Inspection on Node")`
- L21 _public enumerator_ `ToggleDebugNode UMETA(DisplayName = "Toggle Debug on Node")`
- L22 _public enumerator_ `JumpToSourceFile UMETA(DisplayName = "View Source File (C++)")`

#### enum `EPCGTreatViewportAsGenerationSource`  
`enum class EPCGTreatViewportAsGenerationSource : uint8`  
_L26-31_
- reflection: `UENUM()`
- L28 _public enumerator_ `PCGWorldActor UMETA(DisplayName = "Use PCG World Actor flag")`
- L29 _public enumerator_ `Always`
- L30 _public enumerator_ `Never`

#### class `UPCGEditorProjectSettings`  
`class UPCGEditorProjectSettings : public UDeveloperSettings`  
_L34-53_
- reflection: `UCLASS(MinimalAPI, config=Editor, meta=(DisplayName="PCG"))`
- inherits: `UDeveloperSettings`
- L39 _public prototype_ `UPCGEditorProjectSettings(const FObjectInitializer& ObjectInitializer);`
- L43 _public member_ `TSoftObjectPtr<UPCGBuilderSettings> DefaultBuilderSetting;` — `UPROPERTY(EditAnywhere, config, Category = Builder)` — Default Builder Settings to use when running the PCGWorldPartitionBuilder
- L47 _public member_ `TArray<TSubclassOf<AActor>> PCGLevelToAssetExcludedActorClasses;` — `UPROPERTY(EditAnywhere, config, Category = "PCG Level to Asset", meta=(DisplayName = "Excluded Actor Classes"))` — Actor classes to ignore for the PCG Level to Asset export
- L52 _public member_ `bool bAutoRefreshGPUStaticMeshSpawners = true;` — `UE_DEPRECATED(5.8, "Use UPCGGraph::bAutoRefreshOnRenderStateRefresh / bAutoRefreshOnQualitySettingsChanged on each graph instead.")` — `UPROPERTY(Config)` — Deprecated. Replaced by per-graph UPCGGraph::bAutoRefreshOnRenderStateRefresh (and bAutoRefreshOnQualitySettingsChanged for quality events).

#### struct `FPCGEditorAttributeListViewSettings`  
`struct FPCGEditorAttributeListViewSettings`  
_L56-79_
- reflection: `USTRUCT()`
- L62 _public member_ `ETextOverflowPolicy ColumnNameOverflowPolicy = ETextOverflowPolicy::Ellipsis;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View")` — Overflow policy for column headers in the Attribute List View.
- L66 _public member_ `ETextOverflowPolicy GeneralOverflowPolicy = ETextOverflowPolicy::Ellipsis;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View")` — Overflow policy for non-string types in the Attribute List View.
- L70 _public member_ `ETextOverflowPolicy StringOverflowPolicy = ETextOverflowPolicy::Ellipsis;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View")` — Overflow policy for 'FString' in the Attribute List View.
- L74 _public member_ `ETextOverflowPolicy NameOverflowPolicy = ETextOverflowPolicy::Ellipsis;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View")` — Overflow policy for 'FName' in the Attribute List View.
- L78 _public member_ `ETextOverflowPolicy HyperLinkOverflowPolicy = ETextOverflowPolicy::MiddleEllipsis;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View")` — Overflow policy for 'FSoftObjectPath' and 'FSoftClassPath', which are HyperLinked in the Attribute List View.

#### class `UPCGEditorSettings`  
`class UPCGEditorSettings : public UObject`  
_L82-358_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L87 _public prototype_ `UPCGEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L89 _public prototype_ `FLinearColor GetColor(UPCGSettings* InSettings) const;`
- L92 _public prototype_ `FLinearColor GetPinColor(const FEdGraphPinType& InPinType) const;` — `UE_DEPRECATED(5.7, "Not used anymore, Pin Colors are queried from the PCG Data Type Registry.")`
- L96 _public member_ `FLinearColor DefaultNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Default node color
- L100 _public member_ `FLinearColor InstancedNodeBodyTintColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Instanced node body tint color
- L104 _public member_ `FLinearColor InputOutputNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for input & output nodes
- L108 _public member_ `FLinearColor SetOperationNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for Difference, Intersection, Projection, Union
- L112 _public member_ `FLinearColor DensityOperationNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for density remap
- L116 _public member_ `FLinearColor BlueprintNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for blueprints
- L120 _public member_ `FLinearColor MetadataNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for metadata operations
- L124 _public member_ `FLinearColor FilterNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for filter-like operations
- L128 _public member_ `FLinearColor SamplerNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for sampler operations
- L132 _public member_ `FLinearColor SpawnerNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for artifact-generating operations
- L136 _public member_ `FLinearColor SubgraphNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for subgraph-like operations
- L140 _public member_ `FLinearColor EmbeddedSubgraphNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for embedded subgraph-like operations
- L144 _public member_ `FLinearColor ParamDataNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel, DisplayName = "Attribute Set Node Color"))` — Color used for Attribute Set operations
- L148 _public member_ `FLinearColor DebugNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for debug operations
- L152 _public member_ `FLinearColor ControlFlowNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for control flow operations
- L156 _public member_ `FLinearColor PointOpsNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for point operations
- L160 _public member_ `FLinearColor HierarchicalGenerationNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for hierarchical generation operations
- L164 _public member_ `FLinearColor GraphParametersNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for graph parameters operations
- L168 _public member_ `FLinearColor RerouteNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for reroute nodes
- L172 _public member_ `FLinearColor DynamicMeshNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for dynamic mesh nodes
- L176 _public member_ `FLinearColor ResourceNodeColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for resource nodes
- L180 _public member_ `FLinearColor DefaultPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Default pin color
- L184 _public member_ `FLinearColor SpatialDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for spatial data pins
- L188 _public member_ `FLinearColor ConcreteDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for concrete/simple spatial data pins
- L192 _public member_ `FLinearColor PointDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Point
- L196 _public member_ `FLinearColor PolyLineDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Spline
- L200 _public member_ `FLinearColor Polygon2DDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Polygon2D
- L204 _public member_ `FLinearColor SurfaceDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Surface
- L208 _public member_ `FLinearColor LandscapeDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Landscape
- L212 _public member_ `FLinearColor BaseTextureDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Base Texture
- L216 _public member_ `FLinearColor TextureDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Texture
- L220 _public member_ `FLinearColor DataViewPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Data View
- L224 _public member_ `FLinearColor RenderTargetDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Render Target
- L228 _public member_ `FLinearColor VirtualTextureDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Virtual Texture
- L232 _public member_ `FLinearColor VolumeDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Volume
- L236 _public member_ `FLinearColor PrimitiveDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Primitive
- L240 _public member_ `FLinearColor ParamDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel, DisplayName = "Attribute Set Pin Color"))` — Color used for data pins of type Attribute Set
- L244 _public member_ `FLinearColor DynamicMeshPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Dynamic Mesh
- L248 _public member_ `FLinearColor StaticMeshResourcePinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Static Mesh Resource
- L252 _public member_ `FLinearColor RawBufferPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type Raw Buffer
- L256 _public member_ `FLinearColor UnknownDataPinColor;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for other/unknown data types
- L260 _public member_ `TMap<TSubclassOf<UPCGSettings>, FLinearColor> OverrideNodeColorByClass;` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — User-driven color overrides
- L264 _public member_ `float DefaultWireThickness = 1.5f;` — `UPROPERTY(EditAnywhere, config, Category = Wire, meta = (ClampMin="1", ClampMap="9"))` — Default wire thickness
- L268 _public member_ `float HoverEdgeEmphasis = 1.5f;` — `UPROPERTY(EditAnywhere, config, Category = Wire, meta = (ClampMin="1", ClampMax="5"))` — Hover edge size emphasis
- L272 _public member_ `float MultiDataEdgeDebugEmphasis = 2.5f;` — `UPROPERTY(EditAnywhere, config, Category = Wire, meta = (ClampMin="1", ClampMax="5"))` — Debug mode edge emphasis on multi-data
- L276 _public member_ `float EmptyEdgeDebugDesaturateFactor = 0.5f;` — `UPROPERTY(EditAnywhere, config, Category = Wire, meta = (ClampMin="0", ClampMax="1"))` — Debug mode edge desaturation with empty data
- L280 _public member_ `EPCGEditorDoubleClickAction NodeDoubleClickAction = EPCGEditorDoubleClickAction::ToggleInspectNode;` — `UPROPERTY(EditAnywhere, Config, Category = "Workflow")` — Specify an action to take upon double-clicking a native PCG node.
- L284 _public member_ `bool bConfirmLocalGraphParameterNameChanges = true;` — `UPROPERTY(EditAnywhere, config, Category = Workflow)` — Verify renaming graph parameters via their local getter nodes with a pop-up confirmation window.
- L288 _public member_ `bool bCanSelectPartitionActors = true;` — `UPROPERTY(EditAnywhere, config, Category = "Workflow")` — Allow selecting PCG partition actors in the viewport/outliner.
- L292 _public member_ `EPCGTreatViewportAsGenerationSource TreatViewportAsGenerationSource = EPCGTreatViewportAsGenerationSource::PCGWorldActor;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance")` — Controls if we want to treat the viewport as a runtime generation source
- L296 _public member_ `bool bDisableCPUThrottlingDuringGraphExecution = false;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Disable CPU throttling during graph execution"))` — Specify if we want to disable CPU Throttling when a PCG Graph is executing, this will improve execution time when app is out of focus/minimized
- L300 _public member_ `bool bShowPauseButton = false;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Show PCG pause button in the editor", ConfigRestartRequired = true))` — Controls whether the "Pause PCG" button will be display in the editor menu
- L304 _public member_ `bool bUnpauseCancelsAll = false;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Unpausing cancels all PCG tasks"))` — Controls whether PCG tasks will be cancelled when unpausing PCG, which might result in dirty/stale content, but will not require significant time.
- L308 _public member_ `bool bUseAlternatePauseButton = false;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Use alternate pause button icon", EditCondition = "bShowPauseButton", EditConditionHides))` — Controls whether the alternate PCG pause button is shown instead of the default PCG icon.
- L312 _public member_ `FName OverridePausedButtonLabel = NAME_None;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Overrides default name for the 'currently paused' button", EditCondition = "bShowPauseButton", EditConditionHides))` — Overrides the label of the pause button while PCG is not currently being paused. The default is empty or None, which will use the default label then.
- L316 _public member_ `FName OverrideNotPausedButtonLabel = NAME_None;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (DisplayName = "Overrides default name for the 'not currently paused' button", EditCondition = "bShowPauseButton", EditConditionHides))` — Overrides the label of the pause button while PCG is currently paused. The default is empty or None, which will use the default label then.
- L320 _public member_ `FString OverridePausedButtonTooltip = FString();` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance", meta = (MultiLine = true, DisplayName = "Overrides default tooltip on the pause button", EditCondition = "bShowPauseButton", EditConditionHides))` — Overrides the tooltip on the pause button. The default is empty, which will use the default tooltip then.
- L324 _public member_ `int32 TargetNumPointsForDebug = 64000;` — `UPROPERTY(EditAnywhere, config, Category = "Editor Performance")` — Target number of points when trying to debug volume data or landscape data, to avoid exploding the number of points if the volume/landscape is big, and to have a good representation if the volume/landscape is small.
- L328 _public member_ `bool bShowTemplatePickerOnNewGraph = true;` — `UPROPERTY(EditAnywhere, config, Category = "Content Browser")` — Controls whether the template picker dialog will be shown when creating a new PCG graph, both in the contextual menu and in the PCG graph pickers.
- L332 _public member_ `bool bShowNodeGeneralActionsRightClickContextMenu = true;` — `UPROPERTY(EditAnywhere, config, Category = "Graph UI")` — Display node 'General' actions on the right click context menu.
- L336 _public member_ `bool bShowNodeOrganizationalActionsRightClickContextMenu = true;` — `UPROPERTY(EditAnywhere, config, Category = "Graph UI")` — Display node 'Organizational' actions on the right click context menu.
- L340 _public member_ `bool bShowNodeDeterminismActionsRightClickContext = true;` — `UPROPERTY(EditAnywhere, config, Category = "Graph UI")` — Display node 'Determinism' actions on the right click context menu.
- L344 _public member_ `FPCGEditorAttributeListViewSettings AttributeListViewSettings;` — `UPROPERTY(EditAnywhere, Config, Category = "Attribute List View", meta = (ShowOnlyInnerProperties))` — Attribute List View user configurations.
- L348 _public member_ `bool bAutoFocusViewport = true;` — `UPROPERTY(EditAnywhere, config, Category = "Viewport")` — When inspection updates the viewport will re-focus to the data.
- L352 _public member_ `int32 CodeEditorFontSize = 9;` — `UPROPERTY(EditAnywhere, config, Category = "Code Editor", meta = (ClampMin = 6, ClampMax = 32))` — Font size used in the HLSL Code Editor.
- L357 _public member_ `bool bEnableNavigateToNativeNodes = true;` — `UE_DEPRECATED(5.6, "bEnableNavigateToNativeNodes has been replaced by NodeDoubleClickAction.")` — `UPROPERTY()`

### `Plugins/PCG/Source/PCGEditor/Public/PCGEditorTabFactories.h` (Public)


#### struct `FPCGGenericTabFactoryParams`  
`struct FPCGGenericTabFactoryParams`  
_L20-40_
- L22 _public function_ `FPCGGenericTabFactoryParams(FName InId, TSharedPtr<FPCGEditor> InEditor, TFunction<TSharedRef<SWidget>()> InCreateTabBodyFunc) : Id(InId) , Editor(InEditor) , CreateTabBodyFunc(InCreateTabBodyFunc)`
- L28 _public member_ `FName Id;`
- L29 _public member_ `TSharedPtr<FPCGEditor> Editor;`
- L30 _public member_ `TFunction<TSharedRef<SWidget>()> CreateTabBodyFunc;`
- L31 _public member_ `FPCGGenericTabClosed OnTabClosed;`
- L33 _public member_ `bool bSingleton = true;`
- L35 _public member_ `TOptional<ETabRole> Role;`
- L36 _public member_ `TOptional<FSlateIcon> Icon;`
- L37 _public member_ `TOptional<FText> Label;`
- L39 _public member_ `TSharedPtr<FWorkspaceItem> Group;`

#### struct `FPCGGenericTabFactory`  
`struct FPCGGenericTabFactory : public FWorkflowTabFactory`  
_L42-55_
- inherits: `FWorkflowTabFactory`
- L45 _public prototype_ `FPCGGenericTabFactory(const FPCGGenericTabFactoryParams& InParams);`
- L47 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const;`
- L48 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L51 _private prototype_ `void OnTabClosed(TSharedRef<SDockTab> DockTab) const;`
- L53 _private member_ `TFunction<TSharedRef<SWidget>()> CreateTabBodyFunc;`
- L54 _private member_ `FPCGGenericTabClosed OnTabClosedDelegate;`

#### struct `FPCGGraphEditorDocumentTabFactory`  
`struct FPCGGraphEditorDocumentTabFactory : public FDocumentTabFactoryForObjects<UPCGEditorGraph>`  
_L56-80_
- inherits: `FDocumentTabFactoryForObjects<UPCGEditorGraph>`
- L59 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedPtr<FTabInfo>, UPCGEditorGraph*);`
- L61 _public prototype_ `FPCGGraphEditorDocumentTabFactory(TSharedPtr<FPCGEditor> InEditorPtr, FOnCreateGraphEditorWidget InCreateGraphEditorWidgetCallback);`
- L63 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> InTab) const override;`
- L64 _public prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> InTab) const override;`
- L65 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> InTab) const override;`
- L66 _public prototype_ `virtual void SaveState(TSharedPtr<SDockTab> InTab, TSharedPtr<FTabPayload> InPayload) const override;`
- L67 _public prototype_ `virtual bool SupportsObjectType(UObject* InDocumentID) const override;`
- L70 _protected prototype_ `static FText GetTabTitle(TWeakObjectPtr<UPCGEditorGraph> InWeakEditorGraph);`
- L72 _protected prototype_ `TSharedPtr<FPCGEditor> GetPCGEditor() const;`
- L74 _protected prototype_ `virtual TAttribute<FText> ConstructTabNameForObject(UPCGEditorGraph* InEditorGraph) const override;`
- L75 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& InInfo, UPCGEditorGraph* InEditorGraph) const override;`
- L76 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& InInfo, UPCGEditorGraph* InEditorGraph) const override;`
- L79 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_OneParam(FPCGGenericTabClosed, FName);`
- L18 _prototype_ `DECLARE_DELEGATE_OneParam(FPCGGenericTabClosed, FName);`
- L59 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedPtr<FTabInfo>, UPCGEditorGraph*);`

### `Plugins/PCG/Source/PCGEditor/Public/PCGLevelToAsset.h` (Public)


#### class `UPCGLevelToAsset`  
`class UPCGLevelToAsset : public UPCGAssetExporter`  
_L16-51_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (ShowWorldContextPin))`
- inherits: `UPCGAssetExporter`
- L22 _public prototype_ `static void CreateOrUpdatePCGAssets(const TArray<FAssetData>& WorldAssets, const FPCGAssetExporterParameters& Parameters = FPCGAssetExporterParameters(), TSubclassOf<UPCGLevelToAsset> Subclass = {});` — Creates/updates a PCG Asset per given world. Allows exporter subclassing by passing in a Subclass.
- L25 _public prototype_ `static UPackage* CreateOrUpdatePCGAsset(TSoftObjectPtr<UWorld> World, const FPCGAssetExporterParameters& Parameters = FPCGAssetExporterParameters(), TSubclassOf<UPCGLevelToAsset> Subclass = {});` — Creates/Updates a PCG Asset for a specific world. Allows exporter subclassing by passing in a Subclass. Will return null if it fails, or the package that was modified on success.
- L28 _public prototype_ `static UPackage* CreateOrUpdatePCGAsset(UWorld* World, const FPCGAssetExporterParameters& Parameters = FPCGAssetExporterParameters(), TSubclassOf<UPCGLevelToAsset> Subclass = {});` — Creates/Updates a PCG Asset for a specific world. Allows exporter subclassing (and settings creation by extension). Will return null if it fails, or the package that was modified on success.
- L32 _public prototype_ `bool BP_ExportWorld(UWorld* World, const FString& PackageName, UPCGDataAsset* Asset);` — `UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Export World", ForceAsFunction))` — Parses the world and fills in the provided data asset. Implement this in BP to drive the generation in a custom manner.
- L35 _public prototype_ `void SetWorld(UWorld* World);` — `UFUNCTION(BlueprintCallable, Category="PCG|IO")`
- L39 _public prototype_ `bool SetWorldObject(UObject* WorldObject);` — `UFUNCTION(BlueprintCallable, Category = "PCG|IO")` — Set the world to export from a UObject. The WorldObject must be a World. Return false if the object is not a world or null.
- L42 _public prototype_ `UWorld* GetWorld() const;` — `UFUNCTION(BlueprintCallable, Category = "PCG|IO")`
- L46 _protected prototype_ `virtual bool ExportAsset(const FString& PackageName, UPCGDataAsset* Asset) override;`
- L47 _protected prototype_ `virtual UPackage* UpdateAsset(const FAssetData& PCGAsset) override;`
- L50 _protected member_ `UWorld* WorldToExport = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PCGEDITOR_API`

### `Plugins/PCG/Source/PCGEditor/Public/Schema/PCGEditorGraphSchema.h` (Public)


#### enum `PCGActionsHelpers::ECompatibilityMask`  
`enum class ECompatibilityMask`  
_L25-33_
- L27 _public enumerator_ `NoMask = 0`
- L28 _public enumerator_ `Compatible = 1 << std::underlying_type_t<EPCGDataTypeCompatibilityResult>(EPCGDataTypeCompatibilityResult::Compatible)`
- L29 _public enumerator_ `Filter = 1 << std::underlying_type_t<EPCGDataTypeCompatibilityResult>(EPCGDataTypeCompatibilityResult::RequireFilter)`
- L30 _public enumerator_ `Conversion = 1 << std::underlying_type_t<EPCGDataTypeCompatibilityResult>(EPCGDataTypeCompatibilityResult::RequireConversion)`
- L32 _public enumerator_ `SubtypeNotCompatible = 1 << std::underlying_type_t<EPCGDataTypeCompatibilityResult>(EPCGDataTypeCompatibilityResult::TypeCompatibleSubtypeNotCompatible)` — note: SubtypeNotCompatible isn't used yet, but we'll keep it here for completeness

#### struct `FPCGActionsFilter`  
`struct FPCGActionsFilter`  
_L37-46_
- L39 _public prototype_ `FPCGActionsFilter(const UEdGraph* InEdGraph, EPCGElementType InElementFilterType, FPCGGraphEditorCustomization InCustomization);`
- L41 _public prototype_ `bool Accepts(const FText& InCategory) const;`
- L43 _public member_ `EPCGElementType FilterType = EPCGElementType::All;`
- L44 _public member_ `const UPCGEditorGraph* Graph = nullptr;`
- L45 _public member_ `FPCGGraphEditorCustomization Customization;`

#### class `UPCGEditorGraphSchema`  
`class UPCGEditorGraphSchema : public UEdGraphSchema`  
_L49-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L54 _public prototype_ `void GetPaletteActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L57 _public function_ `virtual EPCGElementType GetElementTypeFiltering() const` — Return the element type filtering for the current editor. By default it is all.
- L60 _public prototype_ `virtual TSubclassOf<UPCGBaseSubgraphSettings> GetSubgraphSettingsClass() const;` — Returns the settings class to use when creating a subgraph node. Override in derived schemas to provide a custom subgraph settings class.
- L63 _public prototype_ `virtual const FPCGGraphEditorCustomization& GetGraphEditorCustomization(const UEdGraph* InEdGraph) const;` — Return the graph customization for this editor. By default it is the one provided by the graph.
- L66 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L67 _public prototype_ `virtual FLinearColor GetPinColor(const UEdGraphPin* InPin) const override;`
- L68 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L69 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const override;`
- L70 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotification) const override;`
- L71 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L72 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L73 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L74 _public prototype_ `virtual void DroppedAssetsOnNode(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L75 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L76 _public prototype_ `virtual void GetAssetsNodeHoverMessage(const TArray<struct FAssetData>& Assets, const UEdGraphNode* HoverNode, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L77 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L78 _public prototype_ `virtual void GetGraphDisplayInformation(const UEdGraph& Graph, FGraphDisplayInfo& DisplayInfo) const override;`
- L81 _public prototype_ `virtual const FSlateBrush* GetMetadataTypeSlateBrush(EPCGContainerType ContainerType) const;`
- L82 _public prototype_ `virtual FLinearColor GetMetadataTypeColor(EPCGMetadataTypes Type) const;`
- L84 _public prototype_ `virtual const FSlateBrush* GetPropertyBagTypeSlateBrush(EPropertyBagContainerType ContainerType) const;`
- L85 _public prototype_ `virtual FLinearColor GetPropertyBagTypeColor(const FPropertyBagPropertyDesc& Desc) const;`
- L88 _public function_ `virtual bool ShouldAddInspectBrushOnNode() const` — To customize if we want to have special brushes for Inspect and Debug on the nodes.
- L89 _public function_ `virtual bool ShouldAddDebugBrushOnNode() const`
- L90 _public function_ `virtual bool ShouldAddViewportEditBrushOnNode() const`
- L93 _protected prototype_ `virtual void GetGraphActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter, bool bIsContextual) const;`
- L94 _protected prototype_ `virtual void GetNativeElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L95 _protected prototype_ `virtual void GetBlueprintElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L96 _protected prototype_ `virtual void GetSubgraphElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L97 _protected prototype_ `virtual void GetSettingsElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter, bool bIsContextual) const;`
- L98 _protected prototype_ `virtual void GetExtraElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L99 _protected prototype_ `virtual void GetNamedRerouteUsageActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L100 _protected prototype_ `virtual void GetDataAssetActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const;`
- L102 _protected prototype_ `virtual bool TryCreateConnectionInternal(UEdGraphPin* A, UEdGraphPin* B, bool bAddConversionNodeIfNeeded) const;`
- L104 _protected prototype_ `virtual bool DroppedAssetsOnNodeInternal(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, const UEdGraphNode* Node, bool bValidate, FString& OutTooltipText) const;`
- L107 _private prototype_ `static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`

#### class `FPCGEditorConnectionDrawingPolicy`  
`class FPCGEditorConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L110-120_
- inherits: `FConnectionDrawingPolicy`
- L113 _public prototype_ `FPCGEditorConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraph);`
- L114 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`
- L117 _protected prototype_ `bool UpdateParamsIfDebugging(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params);`
- L119 _protected member_ `UPCGEditorGraph* Graph;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace PCGActionsHelpers`
- L34 _prototype_ `ENUM_CLASS_FLAGS(ECompatibilityMask);` (scope `PCGActionsHelpers`)

### `Plugins/PCG/Source/PCGEditor/Public/Schema/PCGEditorGraphSchemaActions.h` (Public)


#### enum `EPCGEditorNewSettingsBehavior`  
`enum class EPCGEditorNewSettingsBehavior : uint8`  
_L21-26_
- reflection: `UENUM()`
- L23 _public enumerator_ `Normal = 0`
- L24 _public enumerator_ `ForceCopy`
- L25 _public enumerator_ `ForceInstance`

#### enum `EPCGEditorNewPCGGraphBehavior`  
`enum class EPCGEditorNewPCGGraphBehavior : uint8`  
_L29-34_
- reflection: `UENUM()`
- L31 _public enumerator_ `Normal = 0`
- L32 _public enumerator_ `SubgraphNode`
- L33 _public enumerator_ `LoopNode`

#### struct `FPCGEditorGraphSchemaActionBase`  
`struct FPCGEditorGraphSchemaActionBase : public FEdGraphSchemaAction`  
_L37-50_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FEdGraphSchemaAction`
- L43 _public prototype_ `virtual FText GetMenuDescriptionOverride() const;`
- L45 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L46 _public prototype_ `void SetPaletteIcon(TSharedPtr<FSlateBrush>& InPaletteIcon);`
- L49 _protected member_ `mutable TSharedPtr<FSlateBrush> PaletteIcon = nullptr;`

#### struct `FPCGEditorGraphSchemaAction_NewNativeElement`  
`struct FPCGEditorGraphSchemaAction_NewNativeElement : public FPCGEditorGraphSchemaActionBase`  
_L53-82_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L61 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L68 _public member_ `TSubclassOf<UPCGSettings> SettingsClass;` — `UPROPERTY()`
- L71 _public member_ `FPCGPreConfiguredSettingsInfo PreconfiguredInfo;` — `UPROPERTY()`
- L74 _public function_ `virtual FName GetTypeId() const override`
- L76 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L77 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L81 _protected function_ `virtual void PostCreation(UPCGNode* NewNode)`

#### struct `FPCGEditorGraphSchemaAction_NewGetParameterElement`  
`struct FPCGEditorGraphSchemaAction_NewGetParameterElement : public FPCGEditorGraphSchemaAction_NewNativeElement`  
_L85-99_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaAction_NewNativeElement`
- L93 _public member_ `FPropertyBagPropertyDesc PropertyDesc;` — `UPROPERTY()`
- L95 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L98 _protected prototype_ `virtual void PostCreation(UPCGNode* NewNode) override;`

#### struct `FPCGEditorGraphSchemaAction_NewSettingsElement`  
`struct FPCGEditorGraphSchemaAction_NewSettingsElement : public FPCGEditorGraphSchemaActionBase`  
_L102-136_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L110 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L117 _public member_ `FSoftObjectPath SettingsObjectPath;` — `UPROPERTY()`
- L120 _public member_ `EPCGEditorNewSettingsBehavior Behavior = EPCGEditorNewSettingsBehavior::Normal;` — `UPROPERTY()`
- L123 _public prototype_ `virtual FText GetMenuDescriptionOverride() const override;`
- L127 _public function_ `virtual FName GetTypeId() const override`
- L129 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L130 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L133 _public prototype_ `static void MakeSettingsNodesOrContextualMenu(const TSharedRef<class SWidget>& InPanel, const FVector2D& InScreenPosition, UEdGraph* InGraph, const TArray<FSoftObjectPath>& InSettingsPaths, const TArray<FVector2D>& InLocations, bool bInSelectNewNodes);`
- L134 _public prototype_ `static void MakeSettingsNodes(UPCGEditorGraph* InEditorGraph, TArray<UPCGSettings*> InSettings, TArray<FVector2D> InSettingsLocations, bool bInSelectNewNodes, bool bInCreateInstances);`
- L135 _public prototype_ `static UEdGraphNode* MakeSettingsNode(UPCGEditorGraph* InEditorGraph, UEdGraphPin* InFromPin, UPCGSettings* InSettings, FVector2D InLocation, bool bInSelectNewNode, bool bInCreateInstance);`

#### struct `FPCGEditorGraphSchemaAction_NewBlueprintElement`  
`struct FPCGEditorGraphSchemaAction_NewBlueprintElement : public FPCGEditorGraphSchemaActionBase`  
_L139-165_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L147 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L154 _public member_ `FSoftClassPath BlueprintClassPath;` — `UPROPERTY()`
- L157 _public member_ `FPCGPreConfiguredSettingsInfo PreconfiguredInfo;` — `UPROPERTY()`
- L160 _public function_ `virtual FName GetTypeId() const override`
- L162 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L163 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`

#### struct `FPCGEditorGraphSchemaAction_NewLoadAssetElement`  
`struct FPCGEditorGraphSchemaAction_NewLoadAssetElement : public FPCGEditorGraphSchemaActionBase`  
_L168-193_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L176 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L183 _public member_ `FAssetData Asset;` — `UPROPERTY()`
- L186 _public member_ `TSubclassOf<UPCGSettings> SettingsClass;` — `UPROPERTY()`
- L189 _public function_ `virtual FName GetTypeId() const override`
- L191 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FPCGEditorGraphSchemaAction_NewSubgraphElement`  
`struct FPCGEditorGraphSchemaAction_NewSubgraphElement : public FPCGEditorGraphSchemaActionBase`  
_L197-226_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- desc: Creates a new subgraph element and allows choosing whether it can be a subgraph node or a loop node.
- L205 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L212 _public member_ `FSoftObjectPath SubgraphObjectPath;` — `UPROPERTY()`
- L215 _public member_ `EPCGEditorNewPCGGraphBehavior Behavior = EPCGEditorNewPCGGraphBehavior::Normal;` — `UPROPERTY()`
- L218 _public function_ `virtual FName GetTypeId() const override`
- L220 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L223 _public prototype_ `static void MakeGraphNodesOrContextualMenu(const TSharedRef<class SWidget>& InPanel, const FVector2D& InScreenPosition, UEdGraph* InGraph, const TArray<FSoftObjectPath>& InGraphPaths, const TArray<FVector2D>& InLocations, bool bInSelectNewNodes);`
- L224 _public prototype_ `static void MakeGraphNodes(UPCGEditorGraph* InEditorGraph, TArray<UPCGGraphInterface*> InGraph, TArray<FVector2D> InGraphLocations, bool bInSelectNewNodes, bool bInCreateLoop);`
- L225 _public prototype_ `static UEdGraphNode* MakeGraphNode(UPCGEditorGraph* InEditorGraph, UEdGraphPin* InFromPin, UPCGGraphInterface* InGraph, const FVector2D& InLocation, bool bInSelectNewNode, bool bInCreateLoop);`

#### struct `FPCGEditorGraphSchemaAction_NewComment`  
`struct FPCGEditorGraphSchemaAction_NewComment : public FPCGEditorGraphSchemaActionBase`  
_L230-249_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- desc: Action to add a 'comment' node to the graph
- L238 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L245 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L247 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FPCGEditorGraphSchemaAction_NewReroute`  
`struct FPCGEditorGraphSchemaAction_NewReroute : public FPCGEditorGraphSchemaActionBase`  
_L252-271_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L260 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L267 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L269 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FPCGEditorGraphSchemaAction_NewNamedRerouteUsage`  
`struct FPCGEditorGraphSchemaAction_NewNamedRerouteUsage : public FPCGEditorGraphSchemaActionBase`  
_L274-297_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L283 _public member_ `TObjectPtr<const UPCGNode> DeclarationNode = nullptr;` — `UPROPERTY()` — Declaration that we want to add an usage of
- L286 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L293 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L295 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

#### struct `FPCGEditorGraphSchemaAction_NewNamedRerouteDeclaration`  
`struct FPCGEditorGraphSchemaAction_NewNamedRerouteDeclaration : public FPCGEditorGraphSchemaActionBase`  
_L300-319_
- reflection: `USTRUCT()`
- inherits: `FPCGEditorGraphSchemaActionBase`
- L308 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L315 _public function_ `virtual FName GetTypeId() const override` — FEdGraphSchemaAction interface
- L317 _public prototype_ `virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`

### `Plugins/PCG/Source/PCGEditor/Public/Schema/PCGGraphParametersSchema.h` (Public)


#### class `UPCGPropertyBagHierarchyRoot`  
`class UPCGPropertyBagHierarchyRoot : public UPropertyBagHierarchyRoot`  
_L11-16_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBagHierarchyRoot`

#### class `UPCGPropertyBagHierarchyCategory`  
`class UPCGPropertyBagHierarchyCategory : public UPropertyBagHierarchyCategory`  
_L19-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBagHierarchyCategory`

#### class `UPCGPropertyBagHierarchySection`  
`class UPCGPropertyBagHierarchySection : public UPropertyBagHierarchySection`  
_L27-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBagHierarchySection`

#### class `UPCGGraphParametersSchema`  
`class UPCGGraphParametersSchema : public UPropertyBagSchema`  
_L38-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPropertyBagSchema`
- desc: Specific property bag schema to allow only arrays and set as containers.
- L42 _public prototype_ `virtual bool SupportsPinTypeContainer(TWeakPtr<const FEdGraphSchemaAction> SchemaAction, const FEdGraphPinType& PinType, const EPinContainerType& ContainerType) const override;`
- L44 _public prototype_ `virtual UPropertyBagHierarchyRoot* GetHierarchyRoot(const TArray<UObject*>& ObjectsWithProperty) const override;`
- L46 _public prototype_ `virtual TArray<UScriptStruct*> GetHierarchyPropertyMetaDataTypes(const FPropertyBagPropertyDesc& Desc) const override;`
- L48 _public prototype_ `virtual TSubclassOf<UPropertyBagHierarchyCategory> GetHierarchyCategoryType() const override;`
- L50 _public prototype_ `virtual TSubclassOf<UPropertyBagHierarchySection> GetHierarchySectionType() const override;`

### `Plugins/PCG/Source/PCGEditor/Public/Widgets/AssetEditorViewport/PCGEditorViewportToolbarSections.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PCGEditor` (scope `UE`)
- L9 _prototype_ `FToolMenuEntry CreatePCGViewportSubmenu();` (scope `UE::PCGEditor`)

### `Plugins/PCG/Source/PCGEditor/Public/Widgets/AssetEditorViewport/SPCGEditorViewport.h` (Public)


#### class `SPCGEditorViewport`  
`class SPCGEditorViewport : public SAssetEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L14-84_
- inherits: `SAssetEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L17 _public function_ `SLATE_BEGIN_ARGS(SPCGEditorViewport) : _ModeTools(nullptr)`
- L21 _public prototype_ `SLATE_ARGUMENT(FEditorModeTools*, ModeTools) SLATE_END_ARGS() SPCGEditorViewport();`
- L25 _public prototype_ `virtual ~SPCGEditorViewport();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L30 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;`
- L31 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L32 _public function_ `virtual void OnFloatingButtonClicked() override`
- L36 _public prototype_ `void SetupScene(const TArray<UObject*>& InResources, const FPCGSetupSceneFunc& SetupFunc);` — Rebuilds the scene using the provided resources and setup callback.
- L37 _public prototype_ `void ResetScene();`
- L38 _public function_ `FAdvancedPreviewScene* GetAdvancedPreviewScene()`
- L41 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Add UObject references for GC.
- L44 _public prototype_ `void OnNewNodeInspected();` — Call when a new node is selected. The next ResetScene will restore the viewport type to default and SetupScene will auto-focus.
- L48 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L49 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L50 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L51 _protected prototype_ `virtual void BindCommands() override;`
- L52 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L55 _protected prototype_ `void ReleaseManagedResources();`
- L57 _protected prototype_ `void ToggleAutoFocusViewport();`
- L58 _protected prototype_ `bool IsAutoFocusViewportChecked() const;`
- L60 _protected function_ `virtual void OnSetupScene()`
- L61 _protected function_ `virtual void OnResetScene()`
- L64 _protected member_ `TSharedPtr<FPCGEditorViewportClient> EditorViewportClient = nullptr;`
- L65 _protected member_ `TSharedPtr<FAdvancedPreviewScene> AdvancedPreviewScene = nullptr;`
- L67 _protected member_ `FEditorModeTools* ModeTools = nullptr;`
- L70 _protected member_ `TArray<TObjectPtr<UObject>> ManagedResources;` — Objects used by the scene. Must be managed for GC.
- L73 _protected member_ `FBoxSphereBounds FocusBounds = FBoxSphereBounds(EForceInit::ForceInit);` — Used when focusing the data viewport to the visualization.
- L76 _protected member_ `TOptional<float> FocusOrthoZoom;` — Used when focusing the data viewport to the visualization for orthographic views. If not set then FocusBounds is used to determin zoom.
- L79 _protected member_ `TSharedPtr<SBox> DynamicToolbarSlot;` — Slot in the viewport toolbar populated by the active visualization with its ViewportToolbarWidget.
- L83 _private member_ `bool bPendingViewportReset = false;` — Set by OnNewNodeInspected(); consumed by ResetScene() to restore viewport type and trigger auto-focus.

### `Plugins/PCG/Source/PCGEditor/Public/Widgets/SPCGExecutionSourceActionWidget.h` (Public)


#### class `SPCGExecutionSourceActionWidget`  
`class SPCGExecutionSourceActionWidget : public SCompoundWidget`  
_L13-36_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SPCGExecutionSourceActionWidget)`
- L17 _public prototype_ `SLATE_ATTRIBUTE(TArray<TWeakInterfacePtr<IPCGGraphExecutionSource>>, ExecutionSources) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _private prototype_ `EVisibility GetGenerateButtonVisibility() const;`
- L24 _private prototype_ `EVisibility GetCancelButtonVisibility() const;`
- L25 _private prototype_ `EVisibility GetCleanupButtonVisibility() const;`
- L26 _private prototype_ `EVisibility GetRefreshButtonVisibility() const;`
- L27 _private prototype_ `EVisibility GetClearPCGLinkButtonVisibility() const;`
- L29 _private prototype_ `FReply OnGenerateClicked();`
- L30 _private prototype_ `FReply OnCancelClicked();`
- L31 _private prototype_ `FReply OnCleanupClicked();`
- L32 _private prototype_ `FReply OnRefreshClicked();`
- L33 _private prototype_ `FReply OnClearPCGLinkClicked();`
- L35 _private member_ `TArray<TWeakInterfacePtr<IPCGGraphExecutionSource>> ExecutionSources;`
